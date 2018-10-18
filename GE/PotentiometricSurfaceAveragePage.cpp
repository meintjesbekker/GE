/*--------------------------------------------------------------------------*/
/*					PotentiometricSurfaceAveragePage.cpp					*/
/*                            												*/
/*	Purpose	: Average page for Potentiometric Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4.2 "Average".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "PotentiometricSurfaceAveragePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CPotentiometricSurfaceAveragePage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceAveragePage::CPotentiometricSurfaceAveragePage(CPotentiometricSurface* pcPotentiometricSurface /* = NULL */) 
	: CPropertyPage(CPotentiometricSurfaceAveragePage::IDD)
{
	m_pcPotentiometricSurface = pcPotentiometricSurface;

	//{{AFX_DATA_INIT(CPotentiometricSurfaceAveragePage)
	m_bAverage = FALSE;
	m_bDecimate = FALSE;
	m_bSmooth = FALSE;
	m_iNumberOfIterations = 10;
	m_fTargetReduction = 0.0f;
	m_fRelaxationFactor	= 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceAveragePage::~CPotentiometricSurfaceAveragePage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CPotentiometricSurfaceAveragePage, CPropertyPage)
	//{{AFX_MSG_MAP(CPotentiometricSurfaceAveragePage)
	ON_BN_CLICKED(IDC_CHECK_AVERAGE, OnCheckAverage)
	ON_BN_CLICKED(IDC_CHECK_DECIMATE, OnCheckDecimate)
	ON_BN_CLICKED(IDC_CHECK_SMOOTH, OnCheckSmooth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceAveragePage::OnOK() 
{
	m_pcPotentiometricSurface->SetAverage(m_cAverageCheck.GetCheck());
	m_pcPotentiometricSurface->SetDecimate(m_cDecimateCheck.GetCheck());
	m_pcPotentiometricSurface->SetTargetReduction(m_fTargetReduction);
	m_pcPotentiometricSurface->SetSmooth(m_cSmoothCheck.GetCheck());
	m_pcPotentiometricSurface->SetRelaxationFactor(m_fRelaxationFactor);
	m_pcPotentiometricSurface->SetNumberOfIterations(m_iNumberOfIterations);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceAveragePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPotentiometricSurfaceAveragePage)
	DDX_Control(pDX, IDC_EDIT_RELAXATION, m_cRelaxationFactorEdit);
	DDX_Control(pDX, IDC_EDIT_REDUCTION, m_cTargetReductionEdit);
	DDX_Control(pDX, IDC_EDIT_ITERATIONS, m_cNumberOfIterationsEdit);
	DDX_Control(pDX, IDC_CHECK_SMOOTH, m_cSmoothCheck);
	DDX_Control(pDX, IDC_CHECK_DECIMATE, m_cDecimateCheck);
	DDX_Control(pDX, IDC_CHECK_AVERAGE, m_cAverageCheck);
	DDX_Check(pDX, IDC_CHECK_AVERAGE, m_bAverage);
	DDX_Check(pDX, IDC_CHECK_DECIMATE, m_bDecimate);
	DDX_Check(pDX, IDC_CHECK_SMOOTH, m_bSmooth);
	DDX_Text(pDX, IDC_EDIT_ITERATIONS, m_iNumberOfIterations);
	DDX_Text(pDX, IDC_EDIT_REDUCTION, m_fTargetReduction);
	DDX_Text(pDX, IDC_EDIT_RELAXATION, m_fRelaxationFactor);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnCheckAverage                                                           */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceAveragePage::OnCheckAverage() 
{
	if (!m_cAverageCheck.GetCheck())
	{
		m_cDecimateCheck.SetCheck(FALSE);
		m_cSmoothCheck.SetCheck(FALSE);
	}
}

/*--------------------------------------------------------------------------*/
/* OnCheckDecimate                                                          */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceAveragePage::OnCheckDecimate() 
{
	if (m_cDecimateCheck.GetCheck())
		m_cAverageCheck.SetCheck(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnCheckSmooth                                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceAveragePage::OnCheckSmooth() 
{
	if (m_cSmoothCheck.GetCheck())
		m_cAverageCheck.SetCheck(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CPotentiometricSurfaceAveragePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_fTargetReduction = m_pcPotentiometricSurface->GetTargetReduction();
	m_fRelaxationFactor	= m_pcPotentiometricSurface->GetRelaxationFactor();
	m_iNumberOfIterations = m_pcPotentiometricSurface->GetNumberOfIterations();
	UpdateData(FALSE);
	m_cAverageCheck.SetCheck(m_pcPotentiometricSurface->GetAverage());
	m_cDecimateCheck.SetCheck(m_pcPotentiometricSurface->GetDecimate());
	m_cSmoothCheck.SetCheck(m_pcPotentiometricSurface->GetSmooth());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}