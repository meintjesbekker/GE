/*--------------------------------------------------------------------------*/
/*						XYZSurfaceDecSmoothPage.cpp							*/
/*                            												*/
/*	Purpose	: Decimate and Smooth page for XYZ Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5.2 "Decimate and Smooth".            */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZSurfaceDecSmoothPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CXYZSurfaceDecSmoothPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CXYZSurfaceDecSmoothPage::CXYZSurfaceDecSmoothPage(CXYZSurface* pcXYZSurface /* = NULL */) 
	: CPropertyPage(CXYZSurfaceDecSmoothPage::IDD)
{
	m_pcXYZSurface = pcXYZSurface;
	//{{AFX_DATA_INIT(CXYZSurfaceDecSmoothPage)
	m_bDecimate = FALSE;
	m_fTargetReduction = 0.0f;
	m_bSmooth = FALSE;
	m_fNumberOfIterations = 0.0f;
	m_fRelaxationFactor = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CXYZSurfaceDecSmoothPage::~CXYZSurfaceDecSmoothPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CXYZSurfaceDecSmoothPage, CPropertyPage)
	//{{AFX_MSG_MAP(CXYZSurfaceDecSmoothPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CXYZSurfaceDecSmoothPage::OnOK() 
{
	m_pcXYZSurface->SetDecimate(m_cDecimateCheck.GetCheck());
	m_pcXYZSurface->SetTargetReduction(m_fTargetReduction);
	m_pcXYZSurface->SetSmooth(m_cSmoothCheck.GetCheck());
	m_pcXYZSurface->SetNumberOfIterations(m_fNumberOfIterations);
	m_pcXYZSurface->SetRelaxationFactor(m_fRelaxationFactor);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CXYZSurfaceDecSmoothPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXYZSurfaceDecSmoothPage)
	DDX_Control(pDX, IDC_CHECK_SMOOTH, m_cSmoothCheck);
	DDX_Control(pDX, IDC_CHECK_DECIMATE, m_cDecimateCheck);
	DDX_Check(pDX, IDC_CHECK_DECIMATE, m_bDecimate);
	DDX_Text(pDX, IDC_EDIT_REDUCTION, m_fTargetReduction);
	DDX_Check(pDX, IDC_CHECK_SMOOTH, m_bSmooth);
	DDX_Text(pDX, IDC_EDIT_ITERATIONS, m_fNumberOfIterations);
	DDX_Text(pDX, IDC_EDIT_RELAXATION, m_fRelaxationFactor);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CXYZSurfaceDecSmoothPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_cDecimateCheck.SetCheck(m_pcXYZSurface->GetDecimate());
	m_cSmoothCheck.SetCheck(m_pcXYZSurface->GetSmooth());
	UpdateData(TRUE);
	m_fTargetReduction = m_pcXYZSurface->GetTargetReduction();
	m_fRelaxationFactor = m_pcXYZSurface->GetRelaxationFactor();
	m_fNumberOfIterations = m_pcXYZSurface->GetNumberOfIterations();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}