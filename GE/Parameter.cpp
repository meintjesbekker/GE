/*--------------------------------------------------------------------------*/
/*								Parameter.cpp								*/
/*                            												*/
/*	Purpose	: Color map model cells which contains parameter information. 	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.8 "Parameter".                              */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorPage.h"
#include "ColorSpectrum.h"
#include "Parameter.h"
#include "ParameterSheet.h"
#include "ParameterGeneralPage.h"
#include "ParameterAveragePage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CParameter::CParameter(CModel* pcModel /* = NULL */) 
	: CParameterGUI(pcModel),
	  CGeometry(pcModel),
	  CHexahedronTopology(pcModel),
	  CVisualizationObject()
{
	CIndexes::m_pcModelInfo = pcModel;
	m_cParameter = EMPTYPARAMETER;

	// vtk
	m_pcUnstructuredGrid = NULL;
	m_pcLookupTable = NULL;
	m_pcGeometryFilter = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CParameter::~CParameter()
{
	if (m_pcUnstructuredGrid)
		m_pcUnstructuredGrid->Delete();
	if (m_pcLookupTable)
		m_pcLookupTable->Delete();
	if (m_pcGeometryFilter)
		m_pcGeometryFilter->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateParameter                                                          */
/*--------------------------------------------------------------------------*/
void CParameter::CreateParameter(PARAMETERTYPE cParameter /* = EMPTYPARAMETER */)
{
	m_cParameter = cParameter;
	Create();
}

/*--------------------------------------------------------------------------*/
/* Create                                                                   */
/*--------------------------------------------------------------------------*/
void CParameter::Create()
{
	SetDescriptions();
	SetFolderAndFileNames();
	CreateActiveCellsArray();
	CreateParameterMinimumAndMaximum();
	CreateColor();
	DoPipeline();
}

/*--------------------------------------------------------------------------*/
/* Update                                                                   */
/*--------------------------------------------------------------------------*/
void CParameter::Update()
{
	SetFolderAndFileNames();
	DoPipeline();
}

/*--------------------------------------------------------------------------*/
/* Clip                                                                     */
/*--------------------------------------------------------------------------*/
void CParameter::Clip()
{
	// if clip is check
	ClipParameter();
	CreateMapper();
	RemoveActors();
	CreateLODActor(m_pcDataSetMapper, m_bVisible, m_pcColor->GetOpacity());
	AddActor(m_pcLODActor);
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate                                                 */
/*--------------------------------------------------------------------------*/
BOOL CParameter::DoSheetAndPagesForCreate()
{
	CParameterSheet cDlg(_T("Parameter"));
	CParameterGeneralPage cGeneralPage(m_pcModel, this);
	cDlg.AddPage(&cGeneralPage);

	// do modal dialog box
	if (cDlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForChange                                                 */
/*--------------------------------------------------------------------------*/
BOOL CParameter::DoSheetAndPagesForChange()
{
	CParameterSheet cDlg(_T("Parameter"));
	CParameterGeneralPage cGeneralPage(m_pcModel, this);
	CParameterAveragePage cAveragePage(this);
	CColorPage cColorPage(m_pcColor);
	cDlg.AddPage(&cGeneralPage);
	cDlg.AddPage(&cAveragePage);
	cDlg.AddPage(&cColorPage);

	// do modal dialog box
	if (cDlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* CreateActivateCellsArray                                                 */
/*--------------------------------------------------------------------------*/
void CParameter::CreateActiveCellsArray()
{
	m_bActiveCellsArray.SetSize(GetNormalNumberOfPointsForAllLayers(), 1);
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		float* pfArray = ReadTimeIndependentData("ibd", iLayer);
		for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
			for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
				//    0 = inactive cells
				//  > 0 = active cells
				//  < 0 = fixed head cells
				// TRUE for active FALSE for inactive cells
				m_bActiveCellsArray[GetLayerStartCellIndex(iLayer) + i * m_pcModel->GetNumberOfColumns() + j] = (pfArray[i * m_pcModel->GetNumberOfColumns() + j] != 0);
		delete [] pfArray;
	}
}

/*--------------------------------------------------------------------------*/
/* DoPipeline                                                               */
/*--------------------------------------------------------------------------*/
void CParameter::DoPipeline()
{
	CreateGeometry();
	if (m_pcScalars) 
		m_pcScalars->Delete();
  	m_pcScalars = vtkDoubleArray::New();
	CreateTopolgy(m_bAverage, m_pcScalars, m_sFolderAndFileName, m_pcColor);
	CreateDataSet();
	CreateLookupTable();
	Clip();
}

/*--------------------------------------------------------------------------*/
/* SetDescriptions                                                          */
/*--------------------------------------------------------------------------*/
void CParameter::SetDescriptions()
{
	switch (m_cParameter)
	{
	case HORIZONTAL_HYDRAULIC_CONDUCTIVITY:
		SetDescription(_T("Horizontal Hydraulic Conductivity"));
		break;
	case VERTICAL_HYDRAULIC_CONDUCTIVITY:
		SetDescription(_T("Vertical Hydraulic Conductivity"));
		break;
	case SPECIFIC_STORAGE:
		SetDescription(_T("Specific Storage"));
		break;
	case TRANSMISSIVITY:
		SetDescription(_T("Transmissivity"));
		break;
	case VERTICAL_LEAKANCE:
		SetDescription(_T("Vertical Leakance"));
		break;
	case STORAGE_COEFFICIENT:
		SetDescription(_T("Storage Coefficient"));
		break;
	case EFFECTIVE_POROSITY:
		SetDescription(_T("Effective Pororisty"));
		break;
	case SPECIFIC_YIELD:
		SetDescription(_T("Specific Yield"));
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* SetFolderAndFileNames                                                    */
/*--------------------------------------------------------------------------*/
void CParameter::SetFolderAndFileNames()
{
	switch (m_cParameter)
	{
	case HORIZONTAL_HYDRAULIC_CONDUCTIVITY:
		SetFolderAndFileName("con"); // horizontal hydrualic conductivity
		break;
	case VERTICAL_HYDRAULIC_CONDUCTIVITY:
		SetFolderAndFileName("lea"); // vertical hydraulic conductivity
		break;
	case SPECIFIC_STORAGE:
		SetFolderAndFileName("sto"); // specific storage
		break;
	case TRANSMISSIVITY:
		SetFolderAndFileName("htc"); // transmissivity
		break;
	case VERTICAL_LEAKANCE:
		SetFolderAndFileName("lkn"); // vertical leakance
		break;
	case STORAGE_COEFFICIENT:
		SetFolderAndFileName("scc"); // storage coefficient
		break;
	case EFFECTIVE_POROSITY:
		SetFolderAndFileName("por"); // effective porosity
		break;
	case SPECIFIC_YIELD:
		SetFolderAndFileName("yld"); // specific yield
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* SetFolderAndFileName                                                     */
/*--------------------------------------------------------------------------*/
void CParameter::SetFolderAndFileName(CString sFileExtension)
{
	m_sFolderAndFileName = m_pcModel->GetFolderAndFileName().SpanExcluding(".") + "." + sFileExtension;
}

/*--------------------------------------------------------------------------*/
/* CreateParameterMinimumAndMaximum                                         */
/*--------------------------------------------------------------------------*/
void CParameter::CreateParameterMinimumAndMaximum()
{
	BOOL firstValue = FALSE;
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		float* pfParameterArray = new float[m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns()];

		// read the cParameter file
		m_cReadFile.ReadTimeIndependentData(m_sFolderAndFileName, 
											pfParameterArray, 
											m_pcModel->GetNumberOfRows(),
											m_pcModel->GetNumberOfColumns(),
											iLayer);
 		
		// index through matrix
		for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
			for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
 				if (m_bActiveCellsArray[GetLayerStartCellIndex(iLayer) + i * m_pcModel->GetNumberOfColumns() + j])
				{
					if (!firstValue)
					{
						m_fMinimumValue = pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j];
						m_fMaximumValue = pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j];
						firstValue = TRUE;
					}
					else
					{
						if (pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j] < m_fMinimumValue)
							m_fMinimumValue = pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j];
						if (pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j] > m_fMaximumValue)
							m_fMaximumValue = pfParameterArray[i * m_pcModel->GetNumberOfColumns() + j];
					}
				}
		delete [] pfParameterArray;
	}
}

/*--------------------------------------------------------------------------*/
/* CreateGeometry                                                           */
/*--------------------------------------------------------------------------*/
void CParameter::CreateGeometry()
{
	if (m_bAverage)
		CreateAverageGeometryForAllLayers();
	else
		CreateNormalGeometryForAllLayers();
}

/*--------------------------------------------------------------------------*/
/* CreateDataSet                                                            */
/*--------------------------------------------------------------------------*/
void CParameter::CreateDataSet()
{
	if (m_pcUnstructuredGrid) 
		m_pcUnstructuredGrid->Delete();
	m_pcUnstructuredGrid = vtkUnstructuredGrid::New();
	m_pcUnstructuredGrid->SetPoints(this->m_pcFloatPoints);
	int* cellTypes = new int[m_pcCellArray->GetSize()];
	for (int i = 0; i < m_pcCellArray->GetSize(); i++)
		cellTypes[i] = VTK_HEXAHEDRON;
	m_pcUnstructuredGrid->SetCells(cellTypes, m_pcCellArray);
	m_pcUnstructuredGrid->GetCellData()->SetScalars(m_pcScalars);
	m_pcUnstructuredGrid->Modified();
	delete [] cellTypes;
 }

/*--------------------------------------------------------------------------*/
/* CreateColor                                                              */
/*--------------------------------------------------------------------------*/
void CParameter::CreateColor()
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
void CParameter::CreateLookupTable()
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
void CParameter::CreateMapper()
{	
	if (m_pcModel->GetClip())
		CMapper::CreateDataSetMapper(	m_pcClipPolyData->GetOutput(),
										m_pcLookupTable,
										m_pcColor->m_cColorTable.GetMinimumScalarValue(),
										m_pcColor->m_cColorTable.GetMaximumScalarValue());
	else 
		CMapper::CreateDataSetMapper(	m_pcUnstructuredGrid,
										m_pcLookupTable,
										m_pcColor->m_cColorTable.GetMinimumScalarValue(),
										m_pcColor->m_cColorTable.GetMaximumScalarValue());
	CMapper::m_pcDataSetMapper->SetScalarModeToUseCellData();
	CMapper::m_pcDataSetMapper->Update();
}

/*--------------------------------------------------------------------------*/
/* ClipParameter                                                            */
/*--------------------------------------------------------------------------*/
void CParameter::ClipParameter()
{
	if (m_pcModel->GetClip())
	{
		if (m_pcGeometryFilter)
			m_pcGeometryFilter->Delete();
		m_pcGeometryFilter = vtkGeometryFilter::New();
		m_pcGeometryFilter->SetInputData(m_pcUnstructuredGrid);
		m_pcGeometryFilter->MergingOn();
		m_pcGeometryFilter->Update();
		DoClipPolyData(m_pcGeometryFilter->GetOutputPort());
	}
}

/*--------------------------------------------------------------------------*/
/* ReadTimeIndependentData                                                  */
/*--------------------------------------------------------------------------*/
float* CParameter::ReadTimeIndependentData(CString sFileExtension, int iLayer)
{
	float* pfArray = new float[m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns()];
	m_cReadFile.ReadTimeIndependentData(m_pcModelInfo->GetFolderAndFileName().SpanExcluding(".") + "." + sFileExtension,
										pfArray,
										m_pcModelInfo->GetNumberOfRows(),
										m_pcModelInfo->GetNumberOfColumns(),
										iLayer);
	return pfArray;
}