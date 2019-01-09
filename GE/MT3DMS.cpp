/*--------------------------------------------------------------------------*/
/*								MT3DMS.cpp 									*/
/*                            												*/
/*	Purpose	: Create isosurfaces for MT3DMS, PHT3D or RT3D concentrations.	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".                             */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Color.h"
#include "ColorSpectrum.h"
#include "MT3DMS.h"
#include "MT3DMSSheet.h"
#include "MT3DMSGeneralPage.h"
#include "MT3DMSContourAndColorPage.h"
#include "ReadFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction  				                                            */
/*--------------------------------------------------------------------------*/
CMT3DMS::CMT3DMS(CModel* pcModel /* = NULL */) 
	: CMT3DMSGUI(pcModel),
	  CGeometry(pcModel),
	  CMT3DMSTopology(),
	  CVisualizationObject()
{
	CIndexes::m_pcModelInfo = pcModel;
	// file prefix
	m_sFilePrefix = _T("mt3d");

	// general page
	SetDescription(_T("Concentration Isosurface (MT3DMS)"));

	// number of points used in cell depth
	m_iNumberOfPoints = 1;

	// vtk
	m_pcStructuredGrid = NULL;
	m_pcPolyDataNormals = NULL;
	m_pcGeometryFilter = NULL;
	m_pcLookupTable = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction   				                                            */
/*--------------------------------------------------------------------------*/
CMT3DMS::~CMT3DMS()
{
	if (m_pcStructuredGrid) 
		m_pcStructuredGrid->Delete();
	if (m_pcPolyDataNormals) 
		m_pcPolyDataNormals->Delete();
	if (m_pcGeometryFilter) 
		m_pcGeometryFilter->Delete();
	if (m_pcLookupTable) 
		m_pcLookupTable->Delete();
}

/*--------------------------------------------------------------------------*/
/* Initialize                                                               */
/*--------------------------------------------------------------------------*/
void CMT3DMS::Initialize(CString sFilePrefix /* = _T("mt3d") */)
{
	m_sFilePrefix = sFilePrefix;

	// mt3dms
	if (m_sFilePrefix == _T("mt3d"))
		SetDescription(_T("Concentration Isosurface (MT3DMS)"));
	
	// pht3d
	if (m_sFilePrefix == _T("pht3d"))
		SetDescription(_T("Concentration Isosurface (PHT3D)"));

	// rt3d
	if (m_sFilePrefix == _T("rt3d"))
		SetDescription(_T("Concentration Isosurface (RT3D)"));

	ReadSpeciesFromFile();
	ReadTotalElapsedTimesFromFile();
}

/*--------------------------------------------------------------------------*/
/* Create			                                                        */
/*--------------------------------------------------------------------------*/
void CMT3DMS::Create()
{
	CreateMiddleGeometry(m_iNumberOfPoints);
	CreateScalarDatasetAttribute();
	CreateDataSet();
	CreateContourAndColorTable();
	Update();
}

/*--------------------------------------------------------------------------*/
/* Update                                                                   */
/*--------------------------------------------------------------------------*/
void CMT3DMS::Update()
{
	Contour(m_pcStructuredGrid, m_pMT3DMSContourAndColorTable);
	CalculatePointNormals();
	Clip();
}

/*--------------------------------------------------------------------------*/
/* Clip                                                                     */
/*--------------------------------------------------------------------------*/
void CMT3DMS::Clip()
{
	ClipMT3DMS();
	CreateMapper();
	RemoveActors();
	CreateActor(m_pcPolyDataMapper, m_bVisible, m_fOpacity);
	AddActor(m_pcActor);
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate                                                 */
/*--------------------------------------------------------------------------*/
BOOL CMT3DMS::DoSheetAndPagesForCreate()
{
	CString sWindowName;
	// mt3dms
	if (m_sFilePrefix == _T("mt3d"))
		sWindowName = _T("Concentration Isosurface (MT3DMS)");
	
	// pht3d
	if (m_sFilePrefix == _T("pht3d"))
		sWindowName = _T("Concentration Isosurface (PHT3D)");

	// rt3d
	if (m_sFilePrefix == _T("rt3d"))
		sWindowName = _T("Concentration Isosurface (RT3D)");
	
	CMT3DMSSheet dlg(sWindowName);
	CMT3DMSGeneralPage generalPage(m_pcModel, this);
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
BOOL CMT3DMS::DoSheetAndPagesForChange()
{
	CString sWindowName;
	// mt3dms
	if (m_sFilePrefix == _T("mt3d"))
		sWindowName = _T("Concentration Isosurface (MT3DMS)");
	
	// pht3d
	if (m_sFilePrefix == _T("pht3d"))
		sWindowName = _T("Concentration Isosurface (PHT3D)");

	// rt3d
	if (m_sFilePrefix == _T("rt3d"))
		sWindowName = _T("Concentration Isosurface (RT3D)");
	
	CMT3DMSSheet dlg(sWindowName);
	CMT3DMSGeneralPage generalPage(m_pcModel, this, FALSE);
	CMT3DMSContourAndColorPage contourAndColorPage(m_pcModel, this);
	dlg.AddPage(&generalPage);
	dlg.AddPage(&contourAndColorPage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* ReadTotalElapsedTimesFromFile                                            */
/*--------------------------------------------------------------------------*/
void CMT3DMS::ReadTotalElapsedTimesFromFile()
{
	// contime parameters
	char cName[180];
	GetConcentrationFileName(cName);
	long int pliNumberOfTimeIntervals = 100;
	float* pfTimeIntervals = new float[pliNumberOfTimeIntervals];
	long int liNX = m_pcModel->GetNumberOfColumns();
	long int liNY = m_pcModel->GetNumberOfRows();
	long int liNZ = m_pcModel->GetNumberOfLayers();
	long int liError = 0;

	// initialize array
	for (int i = 0; i < pliNumberOfTimeIntervals; i++)
		pfTimeIntervals[i] = -1;

	// get the concentration times
	CONTIME(	cName, 
				&pliNumberOfTimeIntervals,
				pfTimeIntervals,
				&liNX, 
				&liNY, 
				&liNZ, 
				&liError);
	
	// actual number of pfTime intervals
	m_lNumberOfTimeIntervals = pliNumberOfTimeIntervals;
	
	// create array for pfTime intervals
	if (m_pdTotalElapsedTimes)
		delete [] m_pdTotalElapsedTimes;
	m_pdTotalElapsedTimes = new double[m_lNumberOfTimeIntervals];
	
	// assign array values
	for (int i = 0; i < m_lNumberOfTimeIntervals; i++)
		m_pdTotalElapsedTimes[i] = pfTimeIntervals[i];
	
	// delete tempory array
	delete [] pfTimeIntervals;
	
	// initialize index and assign index elapsed pfTime 
	m_iTotalElapsedTimeIndex = 0;
	if (m_pdTotalElapsedTimes)
		m_dTotalElapsedTime = GetTotalElapsedTime(m_iTotalElapsedTimeIndex);
	else 
		m_dTotalElapsedTime = 0;
}

/*--------------------------------------------------------------------------*/
/* ClipPointNormals                                                         */
/*--------------------------------------------------------------------------*/
void CMT3DMS::CalculatePointNormals()
{
	// normals can not be calculated for lines, only surfaces
	if (m_pcModel->GetNumberOfLayers() > 1)
	{
		// initialize poly data normals
		if (m_pcPolyDataNormals) 
			m_pcPolyDataNormals->Delete();
		m_pcPolyDataNormals = vtkPolyDataNormals::New();

		// assign parameters
		m_pcPolyDataNormals->SetInputData(m_pcContourFilter->GetOutput());
		m_pcPolyDataNormals->Update();
	}
}

/*--------------------------------------------------------------------------*/
/* ClipMT3DMS                                                               */
/*--------------------------------------------------------------------------*/
void CMT3DMS::ClipMT3DMS()
{
	if (m_pcModel->GetClip())
	{
		// initialize geometry filter
		if (m_pcGeometryFilter) 
			m_pcGeometryFilter->Delete();
		m_pcGeometryFilter = vtkGeometryFilter::New();

		// assign input
		if (m_pcModel->GetNumberOfLayers() > 1)
			m_pcGeometryFilter->SetInputData(m_pcPolyDataNormals->GetOutput());
		else
			m_pcGeometryFilter->SetInputData(m_pcContourFilter->GetOutput());
		m_pcGeometryFilter->MergingOn();
		m_pcGeometryFilter->Update();
		DoClipPolyData(m_pcGeometryFilter->GetOutputPort());
	}
}

/*--------------------------------------------------------------------------*/
/* CreateScalarDatasetAttribute											    */
/*--------------------------------------------------------------------------*/
void CMT3DMS::CreateScalarDatasetAttribute()
{
	// Create a scalar array.
	if (m_pcScalars) 
		m_pcScalars->Delete();
	m_pcScalars = vtkDoubleArray::New();

	// BOOL to mark the first value which can be used for minimum and maximum
	BOOL bFirst = TRUE;
	
	// For all the model layers.
	for (int layer = 1; layer <= m_pcModel->GetNumberOfLayers(); layer++)
	{
		// file name         
		char cName[180];
		GetConcentrationFileName(cName);
		float pfTime = m_dTotalElapsedTime;
		long int liNX = m_pcModel->GetNumberOfColumns();
		long int liNY = m_pcModel->GetNumberOfRows();
		long int liNZ = m_pcModel->GetNumberOfLayers();
		long int liLayer = layer;
		long int liError = 0;
		float* pfCon = new float[liNX * liNY];
		
		// Read the concentration for all cells into concentration array.
		READCON(cName, // file to read data from
				&pfTime, // output pfTime
				pfCon, // one dimensional array for concentration
				&liNX, // number of columns
				&liNY, // number of rows
				&liNZ, // number of layers
				&liLayer, // layer to read from
				&liError); // error

		// get the minimum and maximum concentration and assign scalar values
		// For number of rows.
		for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
			// For number of columns.
			for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
			{
				// If it is an inactive concentration cell.
				if (m_pcModel->GetConcentrationInactive() != pfCon[i * m_pcModel->GetNumberOfColumns() + j])
				{
					if (bFirst)
					{
						bFirst = FALSE;
						m_fMinimumValue = pfCon[i * m_pcModel->GetNumberOfColumns() + j];
						m_fMaximumValue = pfCon[i * m_pcModel->GetNumberOfColumns() + j];
					}
					else
					{
						if (pfCon[i * m_pcModel->GetNumberOfColumns() + j] < m_fMinimumValue)
							m_fMinimumValue = pfCon[i * m_pcModel->GetNumberOfColumns() + j];
						if (pfCon[i * m_pcModel->GetNumberOfColumns() + j] > m_fMaximumValue)
							m_fMaximumValue = pfCon[i * m_pcModel->GetNumberOfColumns() + j];
					}
				}
				for (int k = 1; k <= m_iNumberOfPoints; k++)
					if (m_pcModel->GetConcentrationInactive() == pfCon[i * m_pcModel->GetNumberOfColumns() + j])
						// Insert next scalar with a value of 0.
						m_pcScalars->InsertNextValue(0);
					else
						// Insert next scalar using the cell concentration.
						m_pcScalars->InsertNextValue(pfCon[i * m_pcModel->GetNumberOfColumns() + j]);
			}
		delete [] pfCon;
	}
}

/*--------------------------------------------------------------------------*/
/* ReadSpeciesFromFile                                                      */
/*--------------------------------------------------------------------------*/
void CMT3DMS::ReadSpeciesFromFile()
{
	m_iNumberOfSpecies = 0;

	// temporary species array
	CArray<int, int> temporySpeciesArray;

	// search for specy files
	for (int i = 1; i <= 999; i++)
	{
		// test if files exist for MT3DMS
		if (m_sFilePrefix == _T("mt3d"))
			if (m_pcModel->m_cFilesExist.GetMT3DMSSpecyFileExists(i - 1))
			{
				m_iNumberOfSpecies += 1;
				temporySpeciesArray.Add(i);
			}

		// test if files exist for PHT3D
		if (m_sFilePrefix == _T("pht3d"))
			if (m_pcModel->m_cFilesExist.GetPHT3DSpecyFileExists(i - 1))
			{
				m_iNumberOfSpecies += 1;
				temporySpeciesArray.Add(i);
			}

		// test if files exist for RT3D
		if (m_sFilePrefix == _T("rt3d"))
			if (m_pcModel->m_cFilesExist.GetRT3DSpecyFileExists(i - 1))
			{
				m_iNumberOfSpecies += 1;
				temporySpeciesArray.Add(i);
			}
	}
	
	// initialize array which contains all the species
	if (m_piSpecies)
		delete [] m_piSpecies;
	m_piSpecies = new int[m_iNumberOfSpecies];

	// assign all the species from temporary array
	for (int i = 0; i < m_iNumberOfSpecies; i++)
		m_piSpecies[i] = temporySpeciesArray[i];
	
	// clean the array
	temporySpeciesArray.RemoveAll();
	
	// initialize specy index and get the value
	m_iSpecyIndex = 0;
	m_iSpecy = m_piSpecies[m_iSpecyIndex];
}

/*--------------------------------------------------------------------------*/
/* GetHeadsFileName                                                         */
/*--------------------------------------------------------------------------*/
void CMT3DMS::GetConcentrationFileName(char cName[180])
{
	CString sSpecyString;
	sSpecyString.Format("%i", m_iSpecy);
	sSpecyString = "00" + sSpecyString;
	sSpecyString = sSpecyString.Right(3);
	CString	str	= m_pcModel->GetFolder() + m_sFilePrefix + sSpecyString +".ucn";
	
	// initialize pcName
	for (int iIndex = 0; iIndex < 180; iIndex++)
		cName[iIndex] = ' ';
	
	// assign string to char
	for (int iIndex = 0; iIndex < str.GetLength(); iIndex++)
		cName[iIndex] = str[iIndex];
}

/*--------------------------------------------------------------------------*/
/* CreateDataSet                                                            */
/*--------------------------------------------------------------------------*/
void CMT3DMS::CreateDataSet()
{
	// initialize structured grid dataset
	if (m_pcStructuredGrid) 
		m_pcStructuredGrid->Delete();
	m_pcStructuredGrid = vtkStructuredGrid::New();

	// assign parameters
	m_pcStructuredGrid->SetDimensions(	m_pcModel->GetNumberOfColumns(),
										m_pcModel->GetNumberOfRows(),
										m_pcModel->GetNumberOfLayers());
	m_pcStructuredGrid->SetPoints(m_pcFloatPoints);
	m_pcStructuredGrid->GetPointData()->SetScalars(m_pcScalars);
	m_pcStructuredGrid->Modified();
}

/*--------------------------------------------------------------------------*/
/* CreateContourAndColorTable												*/
/*--------------------------------------------------------------------------*/
void CMT3DMS::CreateContourAndColorTable()
{
	// initialize contour and color table
	if (m_pMT3DMSContourAndColorTable)
		delete m_pMT3DMSContourAndColorTable;
	m_pMT3DMSContourAndColorTable = new CMT3DMSContourAndColorTable();

	// assign parameters
	m_pMT3DMSContourAndColorTable->SetMinimumScalarValue(m_fMinimumValue);
	m_pMT3DMSContourAndColorTable->SetMaximumScalarValue(m_fMaximumValue);
	
	// calculate the initial contour interval
	float interval = (m_fMaximumValue - m_fMinimumValue) / 10;

	// assign parameters
	m_pMT3DMSContourAndColorTable->SetInterval(interval);
	m_pMT3DMSContourAndColorTable->SetMinimumScalarColor(RGB(255, 255, 0));
	m_pMT3DMSContourAndColorTable->SetMaximumScalarColor(RGB(255, 0, 0));
	
	// create contour and color rows
	m_pMT3DMSContourAndColorTable->CreateValueAndColorRows();
}

/*--------------------------------------------------------------------------*/
/* CreateLookupTable         												*/
/*--------------------------------------------------------------------------*/
void CMT3DMS::CreateLookupTable()
{
	// initialize lookup table
	if (m_pcLookupTable) 
		m_pcLookupTable->Delete();
	m_pcLookupTable = CMT3DMSLookupTable::New();

	// assign parameters
	m_pcLookupTable->SetColorTable(m_pMT3DMSContourAndColorTable);
	m_pcLookupTable->Build();
}

/*--------------------------------------------------------------------------*/
/* CreateMapper                                                             */
/*--------------------------------------------------------------------------*/
void CMT3DMS::CreateMapper()
{
	CreateLookupTable();
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(	m_pcClipPolyData->GetOutputPort(),
								m_pcLookupTable,
								m_pMT3DMSContourAndColorTable->GetMaximumScalarValue(),
								m_pMT3DMSContourAndColorTable->GetMaximumScalarValue());
	else
		if (m_pcModel->GetNumberOfLayers() > 1)
			CMapper::CreateMapper(	m_pcPolyDataNormals->GetOutputPort(),
									m_pcLookupTable,
									m_pMT3DMSContourAndColorTable->GetMaximumScalarValue(),
									m_pMT3DMSContourAndColorTable->GetMaximumScalarValue());
		else
			CMapper::CreateMapper(	m_pcContourFilter->GetOutputPort(),
									m_pcLookupTable,
									m_pMT3DMSContourAndColorTable->GetMaximumScalarValue(),
									m_pMT3DMSContourAndColorTable->GetMaximumScalarValue());
}
