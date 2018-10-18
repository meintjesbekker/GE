/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralPageTD.cpp					*/
/*                            												*/
/*	Purpose	: General page for Time Dependent Hydraulic Components GUI.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsGeneralPageTD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CHydraulicComponentsGeneralPageTD, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralPageTD::CHydraulicComponentsGeneralPageTD(CHydraulicComponents* pcHydraulicComponents /* = NULL */) :  CHydraulicComponentsGeneralPage(CHydraulicComponentsGeneralPageTD::IDD, pcHydraulicComponents)
{
	//{{AFX_DATA_INIT(CHydraulicComponentsGeneralPageTD)
	m_iStressPeriod = -1;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CHydraulicComponentsGeneralPageTD, CPropertyPage)
	//{{AFX_MSG_MAP(CHydraulicComponentsGeneralPageTD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralPageTD::~CHydraulicComponentsGeneralPageTD()
{
}

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralPageTD::OnOK() 
{
	m_pcHydraulicComponents->SetDescription(m_sDescription);
	m_pcHydraulicComponents->SetStressPeriod(m_cStressPeriod.GetCurSel() + 1);	
	for (int i = 0; i < m_pcHydraulicComponents->GetArraySize(); i++)
	{
		m_pcHydraulicComponents->GetHydraulicComponent(i)->SetVisibility(m_cMSFlexGrid.GetVisibility(i + 1));
		m_pcHydraulicComponents->GetHydraulicComponent(i)->SetColor(m_cMSFlexGrid.GetColor(i + 1));
		m_pcHydraulicComponents->GetHydraulicComponent(i)->UpdateActor();
	}
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralPageTD::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHydraulicComponentsGeneralPageTD)
	DDX_Control(pDX, IDC_COMBO_STRESS_PERIOD, m_cStressPeriod);
	DDX_CBIndex(pDX, IDC_COMBO_STRESS_PERIOD, m_iStressPeriod);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponentsGeneralPageTD::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcHydraulicComponents->GetDescription();
	UpdateData(FALSE);
	for (int i = 1; i <= m_pcHydraulicComponents->GetNumberOfStressPeriods(); i++)
	{
		CString str;
		str.Format("%i", i);
		m_cStressPeriod.AddString(str);
	}
	m_cStressPeriod.SetCurSel(m_pcHydraulicComponents->GetStressPeriod() - 1);
	m_cMSFlexGrid.SetHydraulicComponentsPointer(m_pcHydraulicComponents);
	m_cMSFlexGrid.InitializeGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}