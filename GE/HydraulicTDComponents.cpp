/*--------------------------------------------------------------------------*/
/*						HydraulicTDComponents.cpp							*/
/*                            												*/
/*	Purpose	: Create Time Dependent, Hydraulic Components.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicTDComponents.h"
#include "HydraulicComponentsSheet.h"
#include "HydraulicComponentsGeneralPageTD.h"
#include "HydraulicComponentsAveragePage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction           													*/
/*--------------------------------------------------------------------------*/
CHydraulicTDComponents::CHydraulicTDComponents(CModel* pcModel /* = NULL */) 
	: CHydraulicComponents(pcModel)
{
}

/*--------------------------------------------------------------------------*/
/* Destruction            													*/
/*--------------------------------------------------------------------------*/
CHydraulicTDComponents::~CHydraulicTDComponents()
{
}

/*--------------------------------------------------------------------------*/
/* Create									                                */
/*--------------------------------------------------------------------------*/
void CHydraulicTDComponents::Create()
{
	SetDescription(_T("Hydraulic Components (Time Dependent)"));
	ReadTimeParameterFile();
	CHydraulicComponent* pHydraulicComponent;
	
	// *.ghb
	if (m_pcModel->m_cFilesExist.GetGHBFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateGeneralHeadBoundaryCell(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.wel
	if (m_pcModel->m_cFilesExist.GetWELFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateDischargeWell(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.wel
	if (m_pcModel->m_cFilesExist.GetWELFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateRechargeWell(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.drc
	if (m_pcModel->m_cFilesExist.GetDRCFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateDrain(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.ric
	if (m_pcModel->m_cFilesExist.GetRICFileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateRiver(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}
	
	// *.ch1
	if (m_pcModel->m_cFilesExist.GetCH1FileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateTimeVariantSpecifiedHead(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}

	// *.c55
	if (m_pcModel->m_cFilesExist.GetC55FileExists())
	{
		pHydraulicComponent = new CHydraulicComponent(m_pcModel);
		pHydraulicComponent->CreateTimeVariantSpecifiedConcentration(m_iStressPeriod);
		m_pcHydraulicComponentArray.Add(pHydraulicComponent);
	}
	RemoveActors();
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		AddActor(m_pcHydraulicComponentArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* Update																	*/
/*--------------------------------------------------------------------------*/
void CHydraulicTDComponents::Update()
{
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		m_pcHydraulicComponentArray[i]->UpdateTimeDependentHydraulicComponent(m_iStressPeriod);
	RemoveActors();
	for (i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		AddActor(m_pcHydraulicComponentArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreateTD                                               */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicTDComponents::DoSheetAndPagesForCreate()
{
 	CHydraulicComponentsSheet dlg(_T("Hydraulic Components (Time Dependent)"));
 	CHydraulicComponentsGeneralPageTD generalPage(this);
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
/* DoSheetAndPagesForChangeTD                                               */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicTDComponents::DoSheetAndPagesForChange()
{
	CHydraulicComponentsSheet dlg(_T("Hydraulic Components (Time Dependent)"));
	CHydraulicComponentsGeneralPageTD generalPage(this);
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