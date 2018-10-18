/*--------------------------------------------------------------------------*/
/*						ParameterAveragePage.cpp	   						*/
/*                            												*/
/*	Purpose	: Average page for Parameter GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.2 "Average".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ParameterAveragePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create															*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CParameterAveragePage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CParameterAveragePage::CParameterAveragePage(CParameter* pcParameter /* = NULL */) 
	: CPropertyPage(CParameterAveragePage::IDD)
{
	m_pParameter = pcParameter;

	//{{AFX_DATA_INIT(CParameterAveragePage)
	m_bAverage = FALSE;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CParameterAveragePage::~CParameterAveragePage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CParameterAveragePage, CPropertyPage)
	//{{AFX_MSG_MAP(CParameterAveragePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CParameterAveragePage::OnOK() 
{
	UpdateData(TRUE);
	m_pParameter->SetAverage(m_bAverage);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CParameterAveragePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterAveragePage)
	DDX_Check(pDX, IDC_CHECK_AVERAGE, m_bAverage);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CParameterAveragePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_bAverage = m_pParameter->GetAverage();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}