/*--------------------------------------------------------------------------*/
/*						ModelOutlineGeneralPage.cpp 						*/
/*                            												*/
/*	Purpose	: General page for Model Outline GUI.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.2 "Model Outline".                    */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ModelOutlineGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create     				                                        */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CModelOutlineGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction       				                                        */
/*--------------------------------------------------------------------------*/
CModelOutlineGeneralPage::CModelOutlineGeneralPage(CModel* pcModel, /* = NULL */
												   CModelOutline* pcModelOutline /* = NULL */) 
	: CPropertyPage(CModelOutlineGeneralPage::IDD)
{
	m_pcModel = pcModel;
	m_pcModelOutline = pcModelOutline;

	//{{AFX_DATA_INIT(CModelOutlineGeneralPage)
	m_sDescription = _T("Model Outline");
	m_cMinimum.SetX(0.0f);
	m_cMinimum.SetY(0.0f);
	m_cMinimum.SetZ(0.0f);
	m_cMaximum.SetX(0.0f);
	m_cMaximum.SetY(0.0f);
	m_cMaximum.SetZ(0.0f);
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction        				                                        */
/*--------------------------------------------------------------------------*/
CModelOutlineGeneralPage::~CModelOutlineGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map        				                                        */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CModelOutlineGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CModelOutlineGeneralPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK               				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutlineGeneralPage::OnOK() 
{
	UpdateData(TRUE);
	m_pcModelOutline->SetDescription(m_sDescription);
	m_pcModelOutline->SetMinimumCornerCoordinate(	m_cMinimum.GetX(),
													m_cMinimum.GetY(),
													m_cMinimum.GetZ());
	m_pcModelOutline->SetMaximumCornerCoordinate(	m_cMaximum.GetX(),
													m_cMaximum.GetY(),
													m_cMaximum.GetZ());
	m_pcModelOutline->Create();
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange     				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutlineGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelOutlineGeneralPage)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDV_MaxChars(pDX, m_sDescription, 200);
	DDX_Text(pDX, IDC_EDIT_X_MINIMUM, m_cMinimum.m_fX);
	DDX_Text(pDX, IDC_EDIT_Y_MINIMUM, m_cMinimum.m_fY);
	DDX_Text(pDX, IDC_EDIT_Z_MINIMUM, m_cMinimum.m_fZ);
	DDX_Text(pDX, IDC_EDIT_X_MAXIMUM, m_cMaximum.m_fX);
	DDX_Text(pDX, IDC_EDIT_Y_MAXIMUM, m_cMaximum.m_fY);
	DDX_Text(pDX, IDC_EDIT_Z_MAXIMUM, m_cMaximum.m_fZ);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog       				                                        */
/*--------------------------------------------------------------------------*/
BOOL CModelOutlineGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcModelOutline->GetDescription();
	m_cMinimum.SetX(m_pcModelOutline->m_cMinimumCornerCoordinate.GetX());
	m_cMinimum.SetY(m_pcModelOutline->m_cMinimumCornerCoordinate.GetY());
	m_cMinimum.SetZ(m_pcModelOutline->m_cMinimumCornerCoordinate.GetZ());
	m_cMaximum.SetX(m_pcModelOutline->m_cMaximumCornerCoordinate.GetX());
	m_cMaximum.SetY(m_pcModelOutline->m_cMaximumCornerCoordinate.GetY());
	m_cMaximum.SetZ(m_pcModelOutline->m_cMaximumCornerCoordinate.GetZ());
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}