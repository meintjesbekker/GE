/*--------------------------------------------------------------------------*/
/*						HydraulicTIComponents.cpp 							*/
/*                            												*/
/*	Purpose	: Create Time Independent, Hydraulic Components.                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsSheet.h"
#include "HydraulicComponentsGeneralPage.h"
#include "HydraulicComponentsAveragePage.h"
#include "HydraulicTIComponents.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction           													*/
/*--------------------------------------------------------------------------*/
CHydraulicTIComponents::CHydraulicTIComponents(CModel* pcModel /* = NULL */) 
	: CHydraulicComponents(pcModel)
{
}

/*--------------------------------------------------------------------------*/
/* Destruction            													*/
/*--------------------------------------------------------------------------*/
CHydraulicTIComponents::~CHydraulicTIComponents()
{
}

/*--------------------------------------------------------------------------*/
/* Create                                                                   */
/*--------------------------------------------------------------------------*/
void CHydraulicTIComponents::Create()
{
	SetDescription(_T("Hydraulic Components (Time Independent)"));

	CHydraulicComponent* pHydraulicComponent;

	// *.ibd
	if (m_pcModel->m_cFilesExist.GetIBDFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateFixedHeadCell();
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.tic
	if (m_pcModel->m_cFilesExist.GetTICFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateFixedConcentrationCell();
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.wac
	if (m_pcModel->m_cFilesExist.GetWACFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateHorizontalFlowBarrier();
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.c85 
	if (m_pcModel->m_cFilesExist.GetC85FileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateReservoir();
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}
	RemoveActors();
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		AddActor(m_pcHydraulicComponentArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* Update                                                                   */
/*--------------------------------------------------------------------------*/
void CHydraulicTIComponents::Update()
{
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		m_pcHydraulicComponentArray[i]->UpdateTimeIndependentHydraulicComponent();
	RemoveActors();
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		AddActor(m_pcHydraulicComponentArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreateTI                                               */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicTIComponents::DoSheetAndPagesForCreate()
{
 	CHydraulicComponentsSheet dlg(_T("Hydraulic Components (Time Independent)"));
 	CHydraulicComponentsGeneralPage generalPage(this);
 	dlg.AddPage(&generalPage);
  	if (dlg.DoModal() == IDOK)
 	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForChangeTI                                               */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicTIComponents::DoSheetAndPagesForChange()
{
	CHydraulicComponentsSheet dlg(_T("Hydraulic Components (Time Independent)"));
	CHydraulicComponentsGeneralPage generalPage(this);
	CHydraulicComponentsAveragePage averagePage(this);
	dlg.AddPage(&generalPage);
	dlg.AddPage(&averagePage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}