/*--------------------------------------------------------------------------*/
/*						ParameterGeneralPage.cpp  							*/
/*                            												*/
/*	Purpose	: General page for Parameter GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.1 "General".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ParameterGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CParameterGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CParameterGeneralPage::CParameterGeneralPage(CModel* pcModel, /* = NULL */
											 CParameter* pcParameter /* = NULL */) 
	: CPropertyPage(CParameterGeneralPage::IDD)
{
	m_pcModel = pcModel;
	m_pcParameter = pcParameter;

	//{{AFX_DATA_INIT(CParameterGeneralPage)
	m_Description = _T("");
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CParameterGeneralPage::~CParameterGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CParameterGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParameterGeneralPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CParameterGeneralPage::OnOK() 
{
	UpdateData(TRUE);
	m_pcParameter->SetDescription(m_Description);
	for (int layer = 1; layer <= m_pcModel->GetNumberOfLayers(); layer++)
		m_pcParameter->m_bVisibleLayersArray[layer-1] = m_FlexGrid.GetVisibility(layer);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CParameterGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterGeneralPage)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_FlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CParameterGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_Description = m_pcParameter->GetDescription();
	UpdateData(FALSE);
	m_FlexGrid.SetModelPointer(m_pcModel);
	m_FlexGrid.SetParameterPointer(m_pcParameter);
	m_FlexGrid.InitializeGrid();
	return TRUE; // return TRUE unless you set the focus to a control
	             // EXCEPTION: OCX Property Pages should return FALSE
}