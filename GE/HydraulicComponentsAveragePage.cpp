/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsAveragePage.cpp						*/
/*                            												*/
/*	Purpose	: Average page for Hydraulic Components GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.2 "Avarage".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsAveragePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                    										*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CHydraulicComponentsAveragePage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                      										*/
/*--------------------------------------------------------------------------*/
CHydraulicComponentsAveragePage::CHydraulicComponentsAveragePage(CHydraulicComponents* pcHydraulicComponents /* = NULL */) : CPropertyPage(CHydraulicComponentsAveragePage::IDD)
{
	m_pcHydraulicComponents = pcHydraulicComponents;

	//{{AFX_DATA_INIT(CHydraulicComponentsAveragePage)
	m_bAverage = FALSE;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                       										*/
/*--------------------------------------------------------------------------*/
CHydraulicComponentsAveragePage::~CHydraulicComponentsAveragePage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                        										*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CHydraulicComponentsAveragePage, CPropertyPage)
	//{{AFX_MSG_MAP(CHydraulicComponentsAveragePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                              										*/
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsAveragePage::OnOK() 
{
	m_pcHydraulicComponents->SetAverage(m_cAverageCheck.GetCheck());
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                    										*/
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsAveragePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHydraulicComponentsAveragePage)
	DDX_Control(pDX, IDC_CHECK_AVERAGE, m_cAverageCheck);
	DDX_Check(pDX, IDC_CHECK_AVERAGE, m_bAverage);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                      										*/
/*--------------------------------------------------------------------------*/
BOOL CHydraulicComponentsAveragePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_cAverageCheck.SetCheck(m_pcHydraulicComponents->GetAverage());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}