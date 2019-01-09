/*--------------------------------------------------------------------------*/
/*						PotentiometricSurface.cpp							*/
/*                            												*/
/*	Purpose	: Create a potentiometric surface visualization object for a    */
/*			  specified stress period and time step or for the groundwater  */
/*			  heads in the highest active cells.					 		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorPage.h"
#include "ColorSpectrum.h"
#include "PotentiometricSurface.h"
#include "PotentiometricSurfaceSheet.h"
#include "PotentiometricSurfaceGeneralPage.h"
#include "PotentiometricSurfaceAveragePage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction								                                */
/*--------------------------------------------------------------------------*/
CPotentiometricSurface::CPotentiometricSurface(CModel* pcModel /* = NULL */) 
	: CPotentiometricSurfaceGUI(pcModel),
	  CGeometry(pcModel),
	  CTopQuadTopology(pcModel),
	  CVisualizationObject()
{
	CIndexes::m_pcModelInfo = pcModel;
	SetDescription(_T("Potentiometric Surface"));

	// heads
	m_pfHeads = NULL;

	// derived vtk class
	m_pcLookupTable = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction 								                                */
/*--------------------------------------------------------------------------*/
CPotentiometricSurface::~CPotentiometricSurface()
{
	// Delete member function has to be used for vtk objects.
	if (m_pcLookupTable)
		m_pcLookupTable->Delete();
	if (m_pfHeads)
		delete [] m_pfHeads;
}

/*--------------------------------------------------------------------------*/
/* Create                                                                   */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::Create()
{
	ReadFile();
	CreateActiveCellsArray();
	CreateMinimumAndMaximumHeads();
	CreateColor();
	Update();
}

/*--------------------------------------------------------------------------*/
/* Update						                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::Update()
{
	CreateGeometry();
	CreateTopolgy();
	CreatePolyData(m_pcFloatPoints, m_pcCellArray, m_pcScalars);
	CleanPolygonalData(m_pcPolyData);
	Triangulate(m_bAverage);
	Decimate(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
				m_bDecimate, 
				m_fTargetReduction);
	SmoothPolyData(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
					m_bSmooth, 
					m_bDecimate, 
					m_iNumberOfIterations, 
					m_fRelaxationFactor);
	ComputePolyDataNormals(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
							m_pcCleanPolyData->GetOutputPort(), 
							m_bSmooth, 
							m_bDecimate, 
							m_bAverage);
	Clip();
}

/*--------------------------------------------------------------------------*/
/* Clip								                                        */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::Clip()
{
	// if clip is check
	DoClipPolyData(m_pcPolyDataNormals->GetOutputPort());
	CreateLookupTable();
	CreateMapper();
	RemoveActors();
	CreateLODActor(m_pcPolyDataMapper, m_bVisible, m_pcColor->GetOpacity());
	AddActor(m_pcLODActor);
}

/*--------------------------------------------------------------------------*/
/* ReadHeadTimes                                                            */
/*--------------------------------------------------------------------------*/
int CPotentiometricSurface::ReadHeadTimes()
{
	// file name         
	char cName[180];
	GetHeadsFileName(cName);
	long int liNumberOfTimeIntervals = 1000;
	long int* pliPeriods = new long int[liNumberOfTimeIntervals];
	long int* pliTimeSteps = new long int[liNumberOfTimeIntervals];
	long int* pliNumberOfLayers	= new long int[liNumberOfTimeIntervals];
	long int liNX = m_pcModel->GetNumberOfColumns();
	long int liNY = m_pcModel->GetNumberOfRows();	
	long int liLayerNumber = m_pcModel->GetNumberOfLayers();
	long int liError = 0;
	HEADTIME(	cName, 
				&liNumberOfTimeIntervals, 
				pliPeriods,
				pliTimeSteps,
				pliNumberOfLayers,
				&liNX, 
				&liNY,
				&liLayerNumber, 
				&liError);

	// repeat for number of time intervals
	for (int i = 0; i < liNumberOfTimeIntervals; i++)
	{
		int iIndex = m_cTimeAndLayerParameter.FindStressPeriod(pliPeriods[i]);
		if (iIndex == -1) // stress period doesn't exist, add it
			m_cTimeAndLayerParameter.AddStressPeriod(pliPeriods[i], pliTimeSteps[i], pliNumberOfLayers[i]);
		else
		{
			iIndex = m_cTimeAndLayerParameter.GetStressPeriod(pliPeriods[i])->FindTimeStep(pliTimeSteps[i]);
			if (iIndex == -1) // time step doesn't exist for stress period, add it 
				m_cTimeAndLayerParameter.GetStressPeriod(pliPeriods[i])->AddTimeStep(pliTimeSteps[i], pliNumberOfLayers[i]);
			else
			{
				iIndex = m_cTimeAndLayerParameter.GetStressPeriod(pliPeriods[i])->GetTimeStep(pliTimeSteps[i])->FindLayer(pliNumberOfLayers[i]);
				if (iIndex == -1) // layer doesn't exist for stress period and time step, add it
					m_cTimeAndLayerParameter.GetStressPeriod(pliPeriods[i])->GetTimeStep(pliTimeSteps[i])->AddLayer(pliNumberOfLayers[i]);
			}
		}
	}
	m_iStressPeriod = pliPeriods[0];
	m_iTimeStep = pliTimeSteps[0];
	m_iLayer = pliNumberOfLayers[0];
	delete [] pliPeriods;
	delete [] pliTimeSteps;
	delete [] pliNumberOfLayers;
	return liNumberOfTimeIntervals;
}

/*--------------------------------------------------------------------------*/
/* ReadHeadFile                                                             */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::ReadHeadFile()
{
	// one dimensional array containing the data to be read
	CreateHeadsArray();
	m_pfHeads = ReadHeadFileForLayer(m_iLayer);
}

/*--------------------------------------------------------------------------*/
/* ReadHighestHeadFile                                                      */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::ReadHighestHeadFile()
{
	// one dimensional array containing the data read
	CreateHeadsArray();
	
	// intialize heads array
	for (int i = 0; i < m_pcModel->GetNumberOfColumns() * m_pcModel->GetNumberOfRows(); i++)
		m_pfHeads[i] = m_pcModel->GetHeadsNoFlow();
	
	// from bottom up
	for (int layer = m_pcModel->GetNumberOfLayers(); layer >= 1; layer--)
	{
		float* pfHeads = ReadHeadFileForLayer(layer);
		for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
			for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
				if (pfHeads[i * m_pcModel->GetNumberOfColumns() + j] != m_pcModel->GetHeadsNoFlow()
					&& pfHeads[i * m_pcModel->GetNumberOfColumns() + j] != m_pcModel->GetHeadsDry())  		
					m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j] = pfHeads[i * m_pcModel->GetNumberOfColumns() + j];		
		delete [] pfHeads;
	}
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate                                                 */
/*--------------------------------------------------------------------------*/
BOOL CPotentiometricSurface::DoSheetAndPagesForCreate()
{
	CPotentiometricSurfaceSheet dlg(_T("Potentiometric Surface"));
	CPotentiometricSurfaceGeneralPage generalPage(this);
	dlg.AddPage(&generalPage);
	if (dlg.DoModal() == IDOK)
	{
		Create();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForChange                                                 */
/*--------------------------------------------------------------------------*/
BOOL CPotentiometricSurface::DoSheetAndPagesForChange()
{
	CPotentiometricSurfaceSheet dlg(_T("Potentiometric Surface"));
	CPotentiometricSurfaceGeneralPage generalPage(this, FALSE);
	CPotentiometricSurfaceAveragePage averagePage(this);
	CColorPage colorPage(m_pcColor);
	dlg.AddPage(&generalPage);
	dlg.AddPage(&averagePage);
	dlg.AddPage(&colorPage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* ReadFile                                                                 */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::ReadFile()
{
	if (!m_bUseHighestHeads)
		ReadHeadFile();
	else
		ReadHighestHeadFile();
}

/*--------------------------------------------------------------------------*/
/* CreateMinimumAndMaximumHeads                                             */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateMinimumAndMaximumHeads()
{
	BOOL bFirstInactive = FALSE;
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
		{
			if (m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j])
			{
				float fHead = m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j];
				if (!bFirstInactive)
				{
					m_fMinimumValue = fHead;
					m_fMaximumValue = fHead;
				}
				else
				{
					if (fHead < m_fMinimumValue)
						m_fMinimumValue = fHead;
					if (fHead > m_fMaximumValue)
						m_fMaximumValue = fHead;
				}
				bFirstInactive = TRUE;
			}
		}
}

/*--------------------------------------------------------------------------*/
/* TestIfActivateCell		                                                */
/*--------------------------------------------------------------------------*/
BOOL CPotentiometricSurface::TestIfActiveCell(int iRowIndex, int iColumnIndex)
{
	return (m_pfHeads[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex] != m_pcModel->GetHeadsNoFlow()
			&& m_pfHeads[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex] != m_pcModel->GetHeadsDry());
}

/*--------------------------------------------------------------------------*/
/* CreateActivateCellsArray                                                 */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateActiveCellsArray()
{
	m_bActiveCellsArray.SetSize(m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns(), 1);
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
			// TRUE for active FALSE for inactive cells
			m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j] = TestIfActiveCell(i, j);
}

/*--------------------------------------------------------------------------*/
/* InsertNormalPointsAndScalars                                             */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::InsertNormalPointsAndScalars(int iRowIndex, int iColumnIndex, float fHead)
{
	// Create 2 column coordinates for current row and column.
	float fXP02 = m_pcModel->GetColumnCoordinate(iColumnIndex);
	float fXP13 = m_pcModel->GetColumnCoordinate(iColumnIndex + 1);

	// Create 2 row coordinates for current row and column.
	float fYP02 = m_pcModel->GetRowCoordinate(iRowIndex);
	float fYP13 = m_pcModel->GetRowCoordinate(iRowIndex + 1);

	// Calculate 4 point indexes into point array for 4 points of cell.
	int iTopPoint[4];
	CalculateTopIndexes(iTopPoint, GetP0NormalIndex(iRowIndex, iColumnIndex), GetP2NormalIndex(iRowIndex, iColumnIndex));
	
	// Insert 4 points into point array, using the 4, point indexes, row and column coordinates and head value.
	m_pcFloatPoints->InsertPoint(iTopPoint[0], fXP02, fYP02, fHead);
	m_pcFloatPoints->InsertPoint(iTopPoint[1], fXP13, fYP02, fHead);
	m_pcFloatPoints->InsertPoint(iTopPoint[2], fXP02, fYP13, fHead);
	m_pcFloatPoints->InsertPoint(iTopPoint[3], fXP13, fYP13, fHead);

	// Insert 4 scalars into scalar array, using the 4, point indexes and head value.
	for (int iIndex = 0; iIndex < 4; iIndex++)
		m_pcScalars->SetValue(iTopPoint[iIndex], fHead);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalGeometryAndScalarDatasetAttribute                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateNormalGeometryAndScalarDatasetAttribute()
{
	// Create a point array.
	CreatePointArray();
	
	// Set the size of the point array = 4 * number of rows * number of columns.
	m_pcFloatPoints->SetNumberOfPoints(4 * m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns());
	
	// Create a scalar array.
	CreateScalarArray();

	// Set the size of the scalar array = 4 * number of rows * number of columns.
	m_pcScalars->SetNumberOfValues(4 * m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns());
	
	// head
	float fHead;
	
	// For number of rows.
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
		{
			// If it is an active cell and head value is in Color Table range.
			if (m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j]
				&& m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j] >= m_pcColor->m_cColorTable.GetMinimumScalarValue()
				&& m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j] <= m_pcColor->m_cColorTable.GetMaximumScalarValue())
				// Get groundwater head of cell from groundwater head array for current row and column.
				fHead = m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j];
			else
				// Use minimum groundwater head of all groundwater heads as groundwater head.
				fHead = m_pcColor->m_cColorTable.GetMinimumScalarValue();

			// Insert normal points and scalars.
			InsertNormalPointsAndScalars(i, j, fHead);
		}
}

/*--------------------------------------------------------------------------*/
/* InsertAveragePoints                                                      */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::InsertAveragePoints(int iRowIndex, int iColumnIndex)
{
	// Calculate 4 point indexes into average point array for cell.
	int iTopPoint[4];
	CalculateTopIndexes(iTopPoint, GetP0AverageIndex(iRowIndex, iColumnIndex), GetP2AverageIndex(iRowIndex, iColumnIndex));

	// Insert 4 points into average point array, using the point indexes and head.
	for (int iPointIndex = 0; iPointIndex < 4; iPointIndex++)
		m_pcAverageArray[iTopPoint[iPointIndex]]->AddToSum(m_pfHeads[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex]);
}

/*--------------------------------------------------------------------------*/
/* CreateAveragePoints														*/
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateAveragePoints()
{
	// Set the size of the average point array = (number of rows + 1) * (number of columns + 1).
	m_pcAverageArray.SetSize((m_pcModel->GetNumberOfRows() + 1) * (m_pcModel->GetNumberOfColumns() + 1), 1);
	
	// Initialize the average point array.
	for (int i = 0; i < (m_pcModel->GetNumberOfRows() + 1) * (m_pcModel->GetNumberOfColumns() + 1); i++)
	{
		CAverage* bAverage = new CAverage();
		m_pcAverageArray[i] = bAverage;
	}

	// For number of rows.
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
			// If it is an active cell and head value is in Color Table range.
			if (m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j]
				&& m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j] >= m_pcColor->m_cColorTable.GetMinimumScalarValue()
				&& m_pfHeads[i * m_pcModel->GetNumberOfColumns() + j] <= m_pcColor->m_cColorTable.GetMaximumScalarValue())
				InsertAveragePoints(i, j);
}

/*--------------------------------------------------------------------------*/
/* CreateAverageGeometryAndScalarDatasetAttribute							*/
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateAverageGeometryAndScalarDatasetAttribute()
{
	// Create average points.
	CreateAveragePoints();

	// Create a point array.
	CreatePointArray();
	
	// Set the size of the point array = (number of rows + 1) * (number of columns + 1).
	m_pcFloatPoints->SetNumberOfPoints((m_pcModel->GetNumberOfRows() + 1) * (m_pcModel->GetNumberOfColumns() + 1));
	
	// Create the scalar array.
	CreateScalarArray();
	
	// Set the size of the scalar array = (number of rows + 1) * (number of columns + 1).
	m_pcScalars->SetNumberOfValues((m_pcModel->GetNumberOfRows() + 1) * (m_pcModel->GetNumberOfColumns() + 1));

	// For indexes in point array.
	for (int i = 0; i < (m_pcModel->GetNumberOfRows() + 1) * (m_pcModel->GetNumberOfColumns() + 1); i++)
	{
		// Calculate row and column indexes using the point array index.
		// Insert a point into the point array where:
		//  point.x = Get column coordinate for column index.
		//  point.y = Get row coordinate for row index.
		//  point.z = Get average groundwater head from average point array.
		m_pcFloatPoints->InsertPoint(	i,
										m_pcModel->GetColumnCoordinate(CalculateColumnIndex(i)),
										m_pcModel->GetRowCoordinate(CalculateRowIndex(i)),
										m_pcAverageArray.GetAt(i)->GetAverage());

		// Insert average groundwater head into the scalar array.
		m_pcScalars->SetValue(i, m_pcAverageArray.GetAt(i)->GetAverage());
	}
}

/*--------------------------------------------------------------------------*/
/* CreateGeometry				                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateGeometry()
{
	if (m_bAverage)
		CreateAverageGeometryAndScalarDatasetAttribute();
	else
		CreateNormalGeometryAndScalarDatasetAttribute();
}

/*--------------------------------------------------------------------------*/
/* CreateTopology				                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateTopolgy()
{
	if (m_pcCellArray) 
		m_pcCellArray->Delete();
	m_pcCellArray = vtkCellArray::New();
	if (m_bAverage)
		CreateHorizontalTopology(m_pcCellArray, m_bAverage);
	else
		CreateNormalTopology(m_pcCellArray, m_bAverage);
}

/*--------------------------------------------------------------------------*/
/* CreateColor                                                              */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateColor()
{
	if (m_pcColor) 
		delete m_pcColor;
	m_pcColor = new CColor();
	m_pcColor->m_cColorTable.SetMinimumScalarValue(m_fMinimumValue);
	m_pcColor->m_cColorTable.SetMaximumScalarValue(m_fMaximumValue);
	m_pcColor->m_cColorTable.SetMinimumScalarColor(RGB(0, 255, 0));
	m_pcColor->m_cColorTable.SetMaximumScalarColor(RGB(0, 0, 255));
	float interval = (m_fMaximumValue - m_fMinimumValue) / 5;
	m_pcColor->m_cColorTable.SetInterval(interval);
	m_pcColor->m_cColorTable.CreateColorRows();
}

/*--------------------------------------------------------------------------*/
/* CreateLookupTable                                                        */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateLookupTable()
{
	if (m_pcLookupTable) 
		m_pcLookupTable->Delete();
	m_pcLookupTable = CLookupTable::New();
	m_pcLookupTable->SetColorTable(&m_pcColor->m_cColorTable);
	m_pcLookupTable->SetNumberOfColors(m_pcColor->m_cColorTable.GetNumberOfColors());
	m_pcLookupTable->Build();
}

/*--------------------------------------------------------------------------*/
/* CreateMapper                                                             */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateMapper()
{	
	CreateLookupTable();
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(	m_pcClipPolyData->GetOutputPort(),
								m_pcLookupTable,
								m_pcColor->m_cColorTable.GetMinimumScalarValue(),
								m_pcColor->m_cColorTable.GetMaximumScalarValue());
	else
		CMapper::CreateMapper(	m_pcPolyDataNormals->GetOutputPort(),
								m_pcLookupTable,
								m_pcColor->m_cColorTable.GetMinimumScalarValue(),
								m_pcColor->m_cColorTable.GetMaximumScalarValue());
}

/*--------------------------------------------------------------------------*/
/* CreateScalarArray   														*/
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateScalarArray()
{
	if (m_pcScalars)
		m_pcScalars->Delete();
	m_pcScalars = vtkDoubleArray::New();
}

/*--------------------------------------------------------------------------*/
/* GetHeadsFileName                                                         */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::GetHeadsFileName(char cName[180])
{
 	CString	str = m_pcModel->GetFolder() + "heads.dat";

	// initialize pcName
	for (int iIndex = 0; iIndex < 180; iIndex++)
		cName[iIndex] = ' ';
	
	// assign string to char
	for (int iIndex = 0; iIndex < str.GetLength(); iIndex++)
		cName[iIndex] = str[iIndex];
}

/*--------------------------------------------------------------------------*/
/* GetHeadsArray                                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurface::CreateHeadsArray()
{
	if (m_pfHeads)
		delete [] m_pfHeads;
	m_pfHeads = new float[m_pcModel->GetNumberOfColumns() * m_pcModel->GetNumberOfRows()];	
}

/*--------------------------------------------------------------------------*/
/* ReadHeadFile                                                             */
/*--------------------------------------------------------------------------*/
float* CPotentiometricSurface::ReadHeadFileForLayer(int iLayer)
{
	float* pfHeads = new float[m_pcModel->GetNumberOfColumns() * m_pcModel->GetNumberOfRows()];

	// file name
	char cName[180];
	GetHeadsFileName(cName);
	long int liNumbRows = m_pcModel->GetNumberOfRows(); // number of rows
	long int liNumbColumns = m_pcModel->GetNumberOfColumns(); // number of columns
	long int liNumbLayers = m_pcModel->GetNumberOfLayers(); // number of pliNumberOfLayers
	long int liPeriods = m_iStressPeriod; // stress period to read from
	long int liTimeStep = m_iTimeStep; // time step to read from
	long int liError = 0; // error
	long int liLayerNumber = iLayer; // layer to read from
	
	READHEAD(	cName, // file to read data from
				&liPeriods, // stress period
				&liTimeStep, // time step
				pfHeads, // one dimensional array
				&liNumbColumns, // number of columns
				&liNumbRows, // number of rows
				&liNumbLayers, // number of pliNumberOfLayers
				&liLayerNumber, // layer to read from
				&liError); // error
	return pfHeads;
}