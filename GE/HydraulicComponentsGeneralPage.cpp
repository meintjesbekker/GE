/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralPage.cpp						*/
/*                            												*/
/*	Purpose	: General page for Hydraulic Components GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CHydraulicComponentsGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralPage::CHydraulicComponentsGeneralPage(CHydraulicComponents* pcHydraulicComponents /* = NULL */) : CPropertyPage(CHydraulicComponentsGeneralPage::IDD)
{
	m_pcHydraulicComponents = pcHydraulicComponents;

	//{{AFX_DATA_INIT(CHydraulicComponentsGeneralPage)
	m_sDescription = _T("");
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralPage::CHydraulicComponentsGeneralPage(UINT nIDTemplate, CHydraulicComponents* pcHydraulicComponents /* = NULL */) : CPropertyPage(nIDTemplate)
{
	m_pcHydraulicComponents = pcHydraulicComponents;
	m_sDescription = _T("");
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralPage::~CHydraulicComponentsGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CHydraulicComponentsGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CHydraulicComponentsGeneralPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralPage::OnOK() 
{
	m_pcHydraulicComponents->SetDescription(m_sDescription);
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
void CHydraulicComponentsGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHydraulicComponentsGeneralPage)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponentsGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcHydraulicComponents->GetDescription();
	UpdateData(FALSE);
	m_cMSFlexGrid.SetHydraulicComponentsPointer(m_pcHydraulicComponents);
	m_cMSFlexGrid.InitializeGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}