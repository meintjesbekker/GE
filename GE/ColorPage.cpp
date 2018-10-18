/*--------------------------------------------------------------------------*/
/*								ColorPage.cpp              					*/
/*                            												*/
/*	Purpose	: Color GUI page.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.4.3, 3.5.3 and 3.8.3 "Color".		*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CColorPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorPage::CColorPage(CColor* pColor /* = NULL */) : CPropertyPage(CColorPage::IDD)
{
	m_pColor = pColor;

	//{{AFX_DATA_INIT(CColorPage)
	m_fOpacity = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CColorPage::~CColorPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CColorPage)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CColorPage::OnOK() 
{
	UpdateData(TRUE);
	m_pColor->SetOpacity(m_fOpacity);	
	m_pColor->m_cColorTable.SetInterval(m_cMSFlexGrid.m_cColorTable.GetInterval());
	m_pColor->m_cColorTable.SetNumberOfColors(m_cMSFlexGrid.m_cColorTable.GetNumberOfColors());
	m_pColor->m_cColorTable.SetMinimumScalarValue(m_cMSFlexGrid.m_cColorTable.GetMinimumScalarValue());
	m_pColor->m_cColorTable.SetMaximumScalarValue(m_cMSFlexGrid.m_cColorTable.GetMaximumScalarValue());
	m_pColor->m_cColorTable.SetMinimumScalarColor(m_cMSFlexGrid.m_cColorTable.GetMinimumScalarColor());
	m_pColor->m_cColorTable.SetMaximumScalarColor(m_cMSFlexGrid.m_cColorTable.GetMaximumScalarColor());
	m_pColor->m_cColorTable.CreateColorRows();
	for (int i = 0; i < m_cMSFlexGrid.m_cColorTable.GetNumberOfColors(); i++)
		m_pColor->m_cColorTable.GetColorRow(i)->SetColor(m_cMSFlexGrid.m_cColorTable.GetColorRow(i)->GetColor());
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPage)
	DDX_Control(pDX, IDC_SLD_OPACITY, m_cSlider);
	DDX_Text(pDX, IDC_EDIT_OPACITY, m_fOpacity);
	DDX_Control(pDX, IDC_EDIT_OPACITY, m_cOpacityEdit);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OninitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CColorPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_fOpacity = m_pColor->GetOpacity();
	UpdateData(FALSE);
	m_cMSFlexGrid.SetColorPointer(m_pColor);
	m_cMSFlexGrid.InitializeGrid();
	
	// initialize slider
	char cBuff[16];
	m_cSlider.SetRange(0, 1000, TRUE );
	m_cSlider.SetPos((int)(m_fOpacity * 1000.0f));
	m_cSlider.SetTicFreq(100);
	m_cSlider.SetPageSize(100);
	sprintf(cBuff, "%.2f", m_fOpacity);
	SetDlgItemText(IDC_EDIT_OPACITY, cBuff);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnHScroll                                                                */
/*--------------------------------------------------------------------------*/
void CColorPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	float fOpacity;
	char cBuff[16];
	fOpacity = (float)(((CSliderCtrl *)pScrollBar)->GetPos()) / 1000.0f;
	sprintf(cBuff, "%.2f", fOpacity);
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