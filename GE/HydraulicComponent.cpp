/*--------------------------------------------------------------------------*/
/*							HydraulicComponent.cpp							*/
/*                            												*/
/*	Purpose	: Create a Hydraulic Component.                                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponent::CHydraulicComponent(CModel* pcModel /* = NULL */) 
	: CHydraulicComponentGUI(pcModel),
	  CGeometry(pcModel),	
	  CSidesQuadTopology(pcModel)
{
	CIndexes::m_pcModelInfo = pcModel;
	m_cHydraulicComponentType = EMPTYHYDRAULICCOMPONENT;
	m_pcAppendPolyData = NULL;
	m_pcPolyDataNormals = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponent::~CHydraulicComponent()
{
	if (m_pcAppendPolyData)
		m_pcAppendPolyData->Delete();
	if (m_pcPolyDataNormals)
		m_pcPolyDataNormals->Delete();
}

/*--------------------------------------------------------------------------*/
/* AppendTimeIndependentPolyData                                            */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::AppendTimeIndependentPolyData(HYDRAULICCOMPONENTTYPE cHydraulicComponentType)
{
	if (m_pcAppendPolyData) 
		m_pcAppendPolyData->Delete();
	m_pcAppendPolyData = vtkAppendPolyData::New();  
	for (int i = 1; i <= m_pcModel->GetNumberOfLayers(); i++)
	{
		CreateIBDActiveCellsArray(i);
		if (m_bAverage)
			CreateAverageGeometry(i);
		else
			CreateNormalGeometry(i);

		// do for hydraulic component
		switch (cHydraulicComponentType)
		{
		case FIXED_CONCENTRATION:
			CreateActiveCellsArrayForFixedConcentration(i);
			break;
		case FIXED_HEADS:
			CreateActiveCellsArrayForFixedHeads(i);
			break;
		case HORIZONTAL_FLOW_BARRIER:
			CreateActiveCellsArrayForHorizontalFlowBarrier(i);
			break;
		case RESERVOIR:
			CreateActiveCellsArrayForReservoir(i);
			break;
		}

		// create topology
		vtkCellArray* pcCellArray = vtkCellArray::New();
		if (m_bAverage)
		{
			CreateHorizontalTopology(pcCellArray, m_bAverage);
			CreateHorizontalTopology(pcCellArray, m_bAverage, GetAverageNumberOfLayerPoints());
		}
		else
		{
			CreateNormalTopology(pcCellArray, m_bAverage);
			CreateNormalTopology(pcCellArray, m_bAverage, GetNormalNumberOfLayerPoints());
		}
		CreateSidesTopology(pcCellArray, m_bAverage);
		vtkPolyData* pcPolyData = vtkPolyData::New();
		pcPolyData->SetPoints(GetFloatPoints());
		pcPolyData->SetPolys(pcCellArray);
		m_pcAppendPolyData->AddInputData(pcPolyData);
		m_pcAppendPolyData->Update();
		if (pcCellArray)
			pcCellArray->Delete();
		if (pcPolyData)
			pcPolyData->Delete();
	}
	ComputePointNormals();
	Clip();
}

/*--------------------------------------------------------------------------*/
/* AppendTimeDependentPolyData                                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::AppendTimeDependentPolyData(HYDRAULICCOMPONENTTYPE cHydraulicComponentType, 
													  int iStressPeriod)
{
	if (m_pcAppendPolyData) 
		m_pcAppendPolyData->Delete();
	m_pcAppendPolyData = vtkAppendPolyData::New();  
	for (int i = 1; i <= m_pcModel->GetNumberOfLayers(); i++)
	{
		CreateIBDActiveCellsArray(i);
		if (m_bAverage)
			CreateAverageGeometry(i);
		else
			CreateNormalGeometry(i);

		// do for hydraulic component
		switch (cHydraulicComponentType)
		{
		case GENERAL_HEAD_BOUNDARY:
			CreateActiveCellsArrayForGeneralHeadBoundary(i, iStressPeriod);
			break;
		case DISCHARGE_WELL:
			CreateActiveCellsArrayForDischargeWell(i, iStressPeriod);
			break;
		case RECHARGE_WELL:
			CreateActiveCellsArrayForRechargeWell(i, iStressPeriod);
			break;
		case DRAIN:
			CreateActiveCellsArrayForDrain(i, iStressPeriod);
			break;
		case RIVER:
			CreateActiveCellsArrayForRiver(i, iStressPeriod);
			break;
		case TIME_VARIANT_SPECIFIED_CONCENTRATION:
			CreateActiveCellsArrayForTimeVariantSpecifiedConcentration(i, iStressPeriod);
			break;
		case TIME_VARIANT_SPECIFIED_HEAD:
			CreateActiveCellsArrayForTimeVariantSpecifiedHead(i, iStressPeriod);
			break;
		}

		// create topology
		vtkCellArray* pcCellArray = vtkCellArray::New();
		if (m_bAverage)
		{
			CreateHorizontalTopology(pcCellArray, m_bAverage);
			CreateHorizontalTopology(pcCellArray, m_bAverage, GetAverageNumberOfLayerPoints());
		}
		else
		{
			CreateHorizontalTopology(pcCellArray, m_bAverage);
			CreateNormalTopology(pcCellArray, m_bAverage);
			CreateNormalTopology(pcCellArray, m_bAverage, GetNormalNumberOfLayerPoints());
		}
		CreateSidesTopology(pcCellArray, m_bAverage);
		vtkPolyData* pcPolyData = vtkPolyData::New();
		pcPolyData->SetPoints(GetFloatPoints());
		pcPolyData->SetPolys(pcCellArray);
		m_pcAppendPolyData->AddInputData(pcPolyData);
		m_pcAppendPolyData->Update();
		if (pcCellArray)
			pcCellArray->Delete();
		if (pcPolyData)
			pcPolyData->Delete();
	}
	ComputePointNormals();
	Clip();
}

/*--------------------------------------------------------------------------*/
/* CreateFixedHeadCell                                                      */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateFixedHeadCell()
{
	m_cHydraulicComponentType = FIXED_HEADS;
	SetDescription(_T("Fixed head cell (IBOUND<0)"));
	SetVisibility(TRUE);
	SetColor(RGB(0, 0, 125));
	AppendTimeIndependentPolyData(FIXED_HEADS);
}

/*--------------------------------------------------------------------------*/
/* CreateFixedConcentrationCell                                             */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateFixedConcentrationCell()
{
	m_cHydraulicComponentType = FIXED_CONCENTRATION;
	SetDescription(_T("Fixed concentration cell (ICBOUND<0)"));
	SetVisibility(TRUE);
	SetColor(RGB(125, 0, 0));
	AppendTimeIndependentPolyData(FIXED_CONCENTRATION);
}

/*--------------------------------------------------------------------------*/
/* CreateHorizontalFlowBarrier                                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateHorizontalFlowBarrier()
{
	m_cHydraulicComponentType = HORIZONTAL_FLOW_BARRIER;
	SetDescription(_T("Horizontal flow barrier (slurry wall)"));
	SetVisibility(TRUE);
	SetColor(RGB(255, 100, 0));
	AppendTimeIndependentPolyData(HORIZONTAL_FLOW_BARRIER);
}

/*--------------------------------------------------------------------------*/
/* CreateReservoir                                                          */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateReservoir()
{
	m_cHydraulicComponentType = RESERVOIR;
	SetDescription(_T("Reservoir"));
	SetVisibility(TRUE);
	SetColor(RGB(100, 0, 255));
	AppendTimeIndependentPolyData(RESERVOIR);
}

/*--------------------------------------------------------------------------*/
/* CreateGeneralHeadBoundaryCell                                            */
/*--------------------------------------------------------------------------*/
void  CHydraulicComponent::CreateGeneralHeadBoundaryCell(int iStressPeriod)
{
	m_cHydraulicComponentType = GENERAL_HEAD_BOUNDARY;
	SetDescription(_T("General-head boundary cell"));
	SetVisibility(TRUE);
	SetColor(RGB(125, 125, 125));
	AppendTimeDependentPolyData(GENERAL_HEAD_BOUNDARY, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateDischargeWell                                                      */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateDischargeWell(int iStressPeriod)
{
	m_cHydraulicComponentType = DISCHARGE_WELL;
	SetDescription(_T("Discharge well"));
	SetVisibility(TRUE);
	SetColor(RGB(255, 0, 0));
	AppendTimeDependentPolyData(DISCHARGE_WELL, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateRechargeWell                                                       */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateRechargeWell(int iStressPeriod)
{
	m_cHydraulicComponentType = RECHARGE_WELL;
	SetDescription(_T("Recharge well"));
	SetVisibility(TRUE);
	SetColor(RGB(0, 0, 255));
	AppendTimeDependentPolyData(RECHARGE_WELL, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateDrain                                                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateDrain(int iStressPeriod)
{
	m_cHydraulicComponentType = DRAIN;
	SetDescription(_T("Drain"));
	SetVisibility(TRUE);
	SetColor(RGB(255, 255, 0));
	AppendTimeDependentPolyData(DRAIN, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateRiver                                                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateRiver(int iStressPeriod)
{
	m_cHydraulicComponentType = RIVER;
	SetDescription(_T("River"));
	SetVisibility(TRUE);
	SetColor(RGB(105, 255, 255));
	AppendTimeDependentPolyData(RIVER, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateIimeVariantSpecifiedHead                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateTimeVariantSpecifiedHead(int iStressPeriod)
{
	m_cHydraulicComponentType = TIME_VARIANT_SPECIFIED_HEAD;
	SetDescription(_T("Time-variant specified-head"));
	SetVisibility(TRUE);
	SetColor(RGB(100, 255, 100));
	AppendTimeDependentPolyData(TIME_VARIANT_SPECIFIED_HEAD, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* CreateTimeVariantSpecifiedConcentration                                  */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateTimeVariantSpecifiedConcentration(int iStressPeriod)
{
	m_cHydraulicComponentType = TIME_VARIANT_SPECIFIED_CONCENTRATION;
	SetDescription(_T("Drain"));
	SetVisibility(TRUE);
	SetColor(RGB(255, 255, 0));
	AppendTimeDependentPolyData(TIME_VARIANT_SPECIFIED_CONCENTRATION, iStressPeriod);
}

/*--------------------------------------------------------------------------*/
/* UpdateTimeIndependentHydraulicComponent                                  */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::UpdateTimeIndependentHydraulicComponent()
{
	SetVisibility(m_bVisible);
	SetColor(m_cColor);
	switch (GetHydraulicComponentType())
	{
	case FIXED_CONCENTRATION:
		AppendTimeIndependentPolyData(FIXED_CONCENTRATION);
		break;
	case FIXED_HEADS:
		AppendTimeIndependentPolyData(FIXED_HEADS);
		break;
	case HORIZONTAL_FLOW_BARRIER:
		AppendTimeIndependentPolyData(HORIZONTAL_FLOW_BARRIER);
		break;
	case RESERVOIR:
		AppendTimeIndependentPolyData(RESERVOIR);
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* UpdateTimeDependentHydraulicComponent		                            */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::UpdateTimeDependentHydraulicComponent(int iStressPeriod)
{
	SetVisibility(m_bVisible);
	SetColor(m_cColor);
	switch (GetHydraulicComponentType())
	{
	case GENERAL_HEAD_BOUNDARY:
		AppendTimeDependentPolyData(GENERAL_HEAD_BOUNDARY, iStressPeriod);
		break;
	case DISCHARGE_WELL:
		AppendTimeDependentPolyData(DISCHARGE_WELL, iStressPeriod);
		break;
	case RECHARGE_WELL:
		AppendTimeDependentPolyData(RECHARGE_WELL, iStressPeriod);
		break;
	case DRAIN:
		AppendTimeDependentPolyData(DRAIN, iStressPeriod);
		break;
	case RIVER:
		AppendTimeDependentPolyData(RIVER, iStressPeriod); 
		break;
	case TIME_VARIANT_SPECIFIED_HEAD:
		AppendTimeDependentPolyData(TIME_VARIANT_SPECIFIED_HEAD, iStressPeriod);
		break;
	case TIME_VARIANT_SPECIFIED_CONCENTRATION:
		AppendTimeDependentPolyData(TIME_VARIANT_SPECIFIED_CONCENTRATION, iStressPeriod);
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* ComputePointNormals                                                      */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::ComputePointNormals()
{
	// files can exist, but can be without data
	if (m_pcAppendPolyData->GetOutput()->GetNumberOfPolys() > 0
		|| m_pcAppendPolyData->GetOutput()->GetNumberOfStrips() > 0)
	{
		if (m_pcPolyDataNormals) 
			m_pcPolyDataNormals->Delete();
		m_pcPolyDataNormals = vtkPolyDataNormals::New();
		m_pcPolyDataNormals->SetInputData(m_pcAppendPolyData->GetOutput());
	}
}

/*--------------------------------------------------------------------------*/
/* Clip                                                                     */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::Clip()
{
	if (m_pcAppendPolyData->GetOutput()->GetNumberOfPolys() > 0
		|| m_pcAppendPolyData->GetOutput()->GetNumberOfStrips() > 0)
		DoClipPolyData(m_pcPolyDataNormals->GetOutput());
	else
		DoClipPolyData(m_pcAppendPolyData->GetOutput());
	CreateMapper();
	CreateLODActor(m_pcPolyDataMapper, m_bVisible, 1, m_cColor);
}

/*--------------------------------------------------------------------------*/
/* UpdateActor                                                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::UpdateActor()
{
	UpdateLODActor(m_bVisible, m_cColor);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArray                                                   */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArray(CString sFileExtension, int iLayer, BOOL (CHydraulicComponent::*pFunc)(float*, int, int))
{
	// read CBC data for IBOUND (modflow)
	float* array = new float[m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns()];
	m_cReadFile.ReadTimeIndependentData(	m_pcModel->GetFolderAndFileName().SpanExcluding(".") + "." + sFileExtension,
											array, 
											m_pcModel->GetNumberOfRows(),
											m_pcModel->GetNumberOfColumns(),
											iLayer);
	m_bActiveCellsArray.RemoveAll();
	m_bActiveCellsArray.SetSize(m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns(), 1);
	CreateIBDActiveCellsArray(iLayer);
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
			// TRUE for active FALSE for inactive
			m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j] = (this->*pFunc)(array, i, j);
	delete [] array;
}

/*--------------------------------------------------------------------------*/
/* CreateTimeDependentActiveCellsArray                                      */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateTimeDependentActiveCellsArray(CString sFileExtension, int iLayer, int iStressPeriod, BOOL (CHydraulicComponent::*pFunc)(float*, int, int))
{
	// read CBC data for IBOUND (modflow)
	float* array = new float[m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns()];
	m_cReadFile.ReadTimeDependentData(	m_pcModel->GetFolderAndFileName().SpanExcluding(".") + "." + sFileExtension,
										iStressPeriod,
										array, 
										m_pcModel->GetNumberOfRows(),
										m_pcModel->GetNumberOfColumns(),
										m_pcModel->GetNumberOfLayers(),
										iLayer);
	m_bActiveCellsArray.RemoveAll();
	m_bActiveCellsArray.SetSize(m_pcModel->GetNumberOfRows() * m_pcModel->GetNumberOfColumns(), 1);
	CreateIBDActiveCellsArray(iLayer);
	for (int i = 0; i < m_pcModel->GetNumberOfRows(); i++)
		for (int j = 0; j < m_pcModel->GetNumberOfColumns(); j++)
			// TRUE for active FALSE for inactive
			m_bActiveCellsArray[i * m_pcModel->GetNumberOfColumns() + j] = (this->*pFunc)(array, i, j);
	delete [] array;
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForFixedHeads                                      */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForFixedHeads(int iLayer)
{
	CreateActiveCellsArray("ibd", iLayer, &CHydraulicComponent::TestIfActiveCellSmaller);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForFixedConcentration                              */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForFixedConcentration(int iLayer)
{
	CreateActiveCellsArray("tic", iLayer, &CHydraulicComponent::TestIfActiveCellSmaller);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForHorizontalFlowBarrier                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForHorizontalFlowBarrier(int iLayer)
{
	CreateActiveCellsArray("wac", iLayer, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForReservoir                                       */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForReservoir(int iLayer)
{
	CreateActiveCellsArray("c85", iLayer, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForGeneralHeadBoundary                             */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForGeneralHeadBoundary(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("ghc", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForDischargeWell                                   */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForDischargeWell(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("wel", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellSmaller);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForRechargeWell                                    */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForRechargeWell(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("wel", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForDrain                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForDrain(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("drc", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForRiver                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForRiver(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("ric", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForTimeVariantSpecifiedHead                        */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForTimeVariantSpecifiedHead(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("ch1", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellNotEqual);
}

/*--------------------------------------------------------------------------*/
/* CreateActiveCellsArrayForTimeVariantSpecifiedConcentration               */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateActiveCellsArrayForTimeVariantSpecifiedConcentration(int iLayer, int iStressPeriod)
{
	CreateTimeDependentActiveCellsArray("c55", iLayer, iStressPeriod, &CHydraulicComponent::TestIfActiveCellGreater);
}

/*--------------------------------------------------------------------------*/
/* TestIfActiveCellSmaller                                                  */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponent::TestIfActiveCellSmaller(float* pfArray, int iRowIndex, int iColumnIndex)
{
	return (pfArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex] < 0
	&& m_bActiveCellsArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex]);
}

/*--------------------------------------------------------------------------*/
/* TestIfActiveCellNotEqual                                                 */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponent::TestIfActiveCellNotEqual(float* pfArray, int iRowIndex, int iColumnIndex)
{
	return (pfArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex] != 0
	&& m_bActiveCellsArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex]);
}

/*--------------------------------------------------------------------------*/
/* TestIfActiveCellGreater                                                  */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponent::TestIfActiveCellGreater(float* pfArray, int iRowIndex, int iColumnIndex)
{
	return (pfArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex] > 0
	&& m_bActiveCellsArray[iRowIndex * m_pcModel->GetNumberOfColumns() + iColumnIndex]);
}

/*--------------------------------------------------------------------------*/
/* CreateMapper                                                             */
/*--------------------------------------------------------------------------*/
void CHydraulicComponent::CreateMapper()
{
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(m_pcClipPolyData->GetOutput());
	else
		if (m_pcAppendPolyData->GetOutput()->GetNumberOfPolys() > 0
			|| m_pcAppendPolyData->GetOutput()->GetNumberOfStrips() > 0)
			CMapper::CreateMapper(m_pcPolyDataNormals->GetOutput());
		else
			CMapper::CreateMapper(m_pcAppendPolyData->GetOutput());
}