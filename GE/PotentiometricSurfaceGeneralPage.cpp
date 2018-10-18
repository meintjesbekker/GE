/*--------------------------------------------------------------------------*/
/*					PotentiometricSurfaceGeneralPage.cpp					*/
/*                            												*/
/*	Purpose	: General page for Potentiometric Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4.1 "General".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "PotentiometricSurfaceGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Creation                                                         */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CPotentiometricSurfaceGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceGeneralPage::CPotentiometricSurfaceGeneralPage(	CPotentiometricSurface* pPotentiometricSurface, /* = NULL */
																		BOOL timeParametersEnabled /* = TRUE */) 
	: CPropertyPage(CPotentiometricSurfaceGeneralPage::IDD)
{
	m_pcPotentiometricSurface = pPotentiometricSurface;
	m_bTimeParametersEnabled = timeParametersEnabled;

	//{{AFX_DATA_INIT(CPotentiometricSurfaceGeneralPage)
	m_sDescription = _T("Potentiometric Surface");
	m_bUseHighestHeads = FALSE;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceGeneralPage::~CPotentiometricSurfaceGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* MessageMap                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CPotentiometricSurfaceGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPotentiometricSurfaceGeneralPage)
	ON_CBN_SELCHANGE(IDC_COMBO_STRESS_PERIOD, OnSelChangeComboStressPeriod)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME_STEP, OnSelChangeComboTimeStep)
	ON_CBN_SELCHANGE(IDC_COMBO_LAYER, OnSelChangeComboLayer)
	ON_BN_CLICKED(IDC_CHECK_HIGHEST_HEADS, OnCheckHighestHeads)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK			                                                            */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::OnOK() 
{
	m_pcPotentiometricSurface->SetDescription(m_sDescription);
	m_pcPotentiometricSurface->SetUseHighestHeads(m_bUseHighestHeads);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPotentiometricSurfaceGeneralPage)
	DDX_Control(pDX, IDC_CHECK_HIGHEST_HEADS, m_cUseHighestHeadsCheck);
	DDX_Control(pDX, IDC_COMBO_LAYER, m_cComboLayer);
	DDX_Control(pDX, IDC_COMBO_TIME_STEP, m_cComboTimeStep);
	DDX_Control(pDX, IDC_COMBO_STRESS_PERIOD, m_cComboStressPeriod);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDX_Check(pDX, IDC_CHECK_HIGHEST_HEADS, m_bUseHighestHeads);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnSelChangeComboStressPeriod			                                    */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::OnSelChangeComboStressPeriod() 
{
	m_pcPotentiometricSurface->SetStressPeriod(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriodFromIndex(m_cComboStressPeriod.GetCurSel()));
	m_cComboTimeStep.ResetContent();
	for (int i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepFromIndex(i));
		m_cComboTimeStep.AddString(str);
	}
	m_pcPotentiometricSurface->SetTimeStep(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepFromIndex(0));
	m_cComboTimeStep.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->FindTimeStep(m_pcPotentiometricSurface->GetTimeStep()));
	m_cComboLayer.ResetContent();
	for (i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(i));
		m_cComboLayer.AddString(str);
	}
	m_pcPotentiometricSurface->SetLayer(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(0));
	m_cComboLayer.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->FindLayer(m_pcPotentiometricSurface->GetLayer()));
}

/*--------------------------------------------------------------------------*/
/* OnSelChangeComboTimeStep				                                    */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::OnSelChangeComboTimeStep() 
{
	m_pcPotentiometricSurface->SetTimeStep(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepFromIndex(m_cComboTimeStep.GetCurSel()));
	m_cComboLayer.ResetContent();
	for (int i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(i));
		m_cComboLayer.AddString(str);
	}
	m_pcPotentiometricSurface->SetLayer(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(0));
	m_cComboLayer.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->FindLayer(m_pcPotentiometricSurface->GetLayer()));
}

/*--------------------------------------------------------------------------*/
/* OnSelChangeComboLayer				                                    */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::OnSelChangeComboLayer() 
{
	m_pcPotentiometricSurface->SetLayer(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(m_cComboLayer.GetCurSel()));
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CPotentiometricSurfaceGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcPotentiometricSurface->GetDescription();
	m_bUseHighestHeads = m_pcPotentiometricSurface->GetUseHighestHeads();
	UpdateData(FALSE);
	for (int i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriodArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriodFromIndex(i));
		m_cComboStressPeriod.AddString(str);
	}
	m_cComboStressPeriod.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.FindStressPeriod(m_pcPotentiometricSurface->GetStressPeriod()));
	for (i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStepFromIndex(i));
		m_cComboTimeStep.AddString(str);
	}
	m_cComboTimeStep.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->FindTimeStep(m_pcPotentiometricSurface->GetTimeStep()));
	for (i = 0; i < m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerArraySize(); i++)
	{
		CString str;
		str.Format("%i", m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->GetLayerFromIndex(i));
		m_cComboLayer.AddString(str);
	}
	m_cComboLayer.SetCurSel(m_pcPotentiometricSurface->m_cTimeAndLayerParameter.GetStressPeriod(m_pcPotentiometricSurface->GetStressPeriod())->GetTimeStep(m_pcPotentiometricSurface->GetTimeStep())->FindLayer(m_pcPotentiometricSurface->GetLayer()));
	if (!m_bTimeParametersEnabled)
	{
		m_cComboStressPeriod.EnableWindow(FALSE);
		m_cComboTimeStep.EnableWindow(FALSE);
		m_cUseHighestHeadsCheck.EnableWindow(FALSE);
		m_cComboLayer.EnableWindow(FALSE);
	}
	else
		if (m_bUseHighestHeads)
			m_cComboLayer.EnableWindow(FALSE);
		else
			m_cComboLayer.EnableWindow(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnCheckHighestHeads                                                      */
/*--------------------------------------------------------------------------*/
void CPotentiometricSurfaceGeneralPage::OnCheckHighestHeads() 
{
	UpdateData(TRUE);
	if (m_bUseHighestHeads)
		m_cComboLayer.EnableWindow(FALSE);
	else
		m_cComboLayer.EnableWindow(TRUE);
}