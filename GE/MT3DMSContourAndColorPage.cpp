/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorPage.cpp  						*/
/*                            												*/
/*	Purpose	: Contour and Color page for Isosurface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSContourAndColorPage.h"
#include "MT3DMSContourAndColorAddDlg.h"
#include "MT3DMSContourAndColorRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CMT3DMSContourAndColorPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorPage::CMT3DMSContourAndColorPage(	CModel* pcModel /* = NULL */,	
														CMT3DMS* pcMT3DMS /* = NULL */) 
	: CPropertyPage(CMT3DMSContourAndColorPage::IDD)
{
	m_pcModel = pcModel;
	m_pcMT3DMS = pcMT3DMS;

	//{{AFX_DATA_INIT(CMT3DMSContourAndColorPage)
	m_fOpacity = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorPage::~CMT3DMSContourAndColorPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSContourAndColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMT3DMSContourAndColorPage)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorPage::OnOK() 
{
	UpdateData(TRUE);
	m_pcMT3DMS->SetOpacity(m_fOpacity);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMT3DMSContourAndColorPage)
	DDX_Control(pDX, IDC_SLD_OPACITY, m_cSlider);
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_cButtonRemove);
	DDX_Text(pDX, IDC_EDIT_OPACITY, m_fOpacity);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnButtonAdd                                                              */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorPage::OnButtonAdd() 
{
	CMT3DMSContourAndColorAddDlg dlg;
	if (dlg.DoModal())
	{
		CMT3DMSContourAndColorRow* MT3DMSContourAndColorRow = new CMT3DMSContourAndColorRow();
		MT3DMSContourAndColorRow->SetValue(dlg.GetValue());
		MT3DMSContourAndColorRow->SetColor(dlg.GetColor());
		m_cMSFlexGrid.Add(MT3DMSContourAndColorRow);
		if (m_cMSFlexGrid.GetSize() > 1) 
			m_cButtonRemove.EnableWindow(TRUE); 	// disable Remove Button
	}
}

/*--------------------------------------------------------------------------*/
/* OnButtonRemove                                                           */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorPage::OnButtonRemove() 
{
	if (m_cMSFlexGrid.GetSize() == 2) 
		m_cButtonRemove.EnableWindow(FALSE); 	// disable Remove Button
	m_cMSFlexGrid.Remove();
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CMT3DMSContourAndColorPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_fOpacity = m_pcMT3DMS->GetOpacity();
	UpdateData(FALSE);
	m_cMSFlexGrid.InitializeGrid(m_pcMT3DMS->GetMT3DMSContourAndColorTablePointer());
	char cBuff[16];
	m_cSlider.SetRange(0, 1000, TRUE );
	m_cSlider.SetPos((int)(m_fOpacity * 1000.0f));
	m_cSlider.SetTicFreq(100);
	m_cSlider.SetPageSize(100);
	sprintf_s(cBuff, "%.2f", m_fOpacity);
	SetDlgItemText(IDC_EDIT_OPACITY, cBuff);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnHScroll                                                                */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	float fOpacity;
	char cBuff[16];
	fOpacity = (float)(((CSliderCtrl *)pScrollBar)->GetPos()) / 1000.0f;
	sprintf_s(cBuff, "%.2f", fOpacity);
	if(nSBCode == SB_ENDSCROLL)
		return;

	// opacity value
	if((CSliderCtrl *)pScrollBar == &m_cSlider)
	{
		m_fOpacity = fOpacity;
		SetDlgItemText(IDC_EDIT_OPACITY, cBuff);
	}
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}