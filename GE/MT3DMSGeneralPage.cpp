/*--------------------------------------------------------------------------*/
/*							MT3DMSGeneralPage.cpp  							*/
/*                            												*/
/*	Purpose	: General page for Isosurface GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.1 "General".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CMT3DMSGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Constuction                                                              */
/*--------------------------------------------------------------------------*/
CMT3DMSGeneralPage::CMT3DMSGeneralPage(CModel* pcModel,	/* = NULL */
									   CMT3DMS* pcMT3DMS, /* = NULL */
									   BOOL bControlsEnabled /* = TRUE */)
	: CPropertyPage(CMT3DMSGeneralPage::IDD)
{
	m_pcModel = pcModel;
	m_pcMT3DMS = pcMT3DMS;
	m_bControlsEnabled = bControlsEnabled;

	//{{AFX_DATA_INIT(CMT3DMSGeneralPage)
	m_cDescription = _T("");
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CMT3DMSGeneralPage::~CMT3DMSGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMT3DMSGeneralPage)
	ON_CBN_SELCHANGE(IDC_SPECIES_NUMBER, OnSelchangeSpeciesNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CMT3DMSGeneralPage::OnOK() 
{
	m_pcMT3DMS->SetDescription(m_cDescription);
	m_pcMT3DMS->SetSpecy(m_cSpeciesNumberComboBox.GetCurSel());
	m_pcMT3DMS->SetSpecyIndex(m_cSpeciesNumberComboBox.GetCurSel());
	m_pcMT3DMS->SetTotalElapsedTime(m_cTotalElapsedTimeComboBox.GetCurSel());
	m_pcMT3DMS->SetTotalElapsedTimeIndex(m_cTotalElapsedTimeComboBox.GetCurSel());
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CMT3DMSGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMT3DMSGeneralPage)
	DDX_Control(pDX, IDC_TOTAL_ELAPSED_TIME, m_cTotalElapsedTimeComboBox);
	DDX_Control(pDX, IDC_SPECIES_NUMBER, m_cSpeciesNumberComboBox);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_cDescription);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CMT3DMSGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_cDescription = m_pcMT3DMS->GetDescription();
	UpdateData(FALSE);
	for (int i = 0; i < m_pcMT3DMS->GetNumberOfSpecies(); i++)
	{
		CString str;
		str.Format("%i", m_pcMT3DMS->GetSpecy(i));
		m_cSpeciesNumberComboBox.AddString(str);
	}
	m_cSpeciesNumberComboBox.SetCurSel(m_pcMT3DMS->GetSpecyIndex());
	for (int i = 0; i < m_pcMT3DMS->GetNumberOfTimeIntervals(); i++)
	{
		CString str;
		str.Format("%lf", m_pcMT3DMS->GetTotalElapsedTime(i));
		m_cTotalElapsedTimeComboBox.AddString(str);
	}
	m_cTotalElapsedTimeComboBox.SetCurSel(m_pcMT3DMS->GetTotalElapsedTimeIndex());
	if (!m_bControlsEnabled)
	{
		m_cSpeciesNumberComboBox.EnableWindow(FALSE);
		m_cTotalElapsedTimeComboBox.EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnSelChangeSpeciesNumber                                                 */
/*--------------------------------------------------------------------------*/
void CMT3DMSGeneralPage::OnSelchangeSpeciesNumber() 
{
	UpdateData(TRUE);
	m_pcMT3DMS->SetSpecy(m_cSpeciesNumberComboBox.GetCurSel());
	m_pcMT3DMS->SetSpecyIndex(m_cSpeciesNumberComboBox.GetCurSel());
	m_pcMT3DMS->ReadTotalElapsedTimesFromFile();
	m_cTotalElapsedTimeComboBox.ResetContent();
	for (int i = 0; i < m_pcMT3DMS->GetNumberOfTimeIntervals(); i++)
	{
		CString str;
		str.Format("%lf", m_pcMT3DMS->GetTotalElapsedTime(i));
		m_cTotalElapsedTimeComboBox.AddString(str);
	}
	m_cTotalElapsedTimeComboBox.SetCurSel(m_pcMT3DMS->GetTotalElapsedTimeIndex());
}