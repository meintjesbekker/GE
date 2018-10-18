/*--------------------------------------------------------------------------*/
/*								AxesDlg.cpp    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Axes GUI.                	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide section 2.1.4 "Options".            				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "AxesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                       		*/
/*--------------------------------------------------------------------------*/
CAxesDlg::CAxesDlg(CWnd* pParent, /* = NULL */ 
				   CModel* pModel /* = NULL */) 
	: CDialog(CAxesDlg::IDD, pParent)
{
	m_pModel = pModel;
	m_cColor = NULL;

	//{{AFX_DATA_INIT(CAxesDlg)
	m_bXVisible = FALSE;
	m_bYVisible = FALSE;
	m_bZVisible = FALSE;
	m_fFontFactor = 0.0f;
	m_iNumberOfLabels = 0;
	m_bColorAxesVisible = FALSE;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                     		*/
/*--------------------------------------------------------------------------*/
void CAxesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAxesDlg)
	DDX_Control(pDX, IDC_STATIC_COLOR, m_cColorPicture);
	DDX_Check(pDX, IDC_CHECK_X, m_bXVisible);
	DDX_Check(pDX, IDC_CHECK_Y, m_bYVisible);
	DDX_Check(pDX, IDC_CHECK_Z, m_bZVisible);
	DDX_Text(pDX, IDC_EDIT_FONT_FACTOR, m_fFontFactor);
	DDV_MinMaxFloat(pDX, m_fFontFactor, 0.2f, 10.f);
	DDX_Text(pDX, IDC_EDIT_NUMBER_OF_LABELS, m_iNumberOfLabels);
	DDV_MinMaxInt(pDX, m_iNumberOfLabels, 2, 1000);
	DDX_Check(pDX, IDC_CHECK_X2, m_bColorAxesVisible);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                        		*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CAxesDlg, CDialog)
	//{{AFX_MSG_MAP(CAxesDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                        		*/
/*--------------------------------------------------------------------------*/
BOOL CAxesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bXVisible = m_pModel->GetXVisible();
	m_bYVisible = m_pModel->GetYVisible();
	m_bZVisible = m_pModel->GetZVisible();
	m_fFontFactor = m_pModel->GetFontFactor();
	m_iNumberOfLabels	= m_pModel->GetNumberOfLabels();
	m_bColorAxesVisible = m_pModel->GetColorAxesVisibility();
	UpdateData(FALSE);
	m_cColor = m_pModel->GetColor();
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* RedrawMinimumColorPicture                                                */
/*--------------------------------------------------------------------------*/
void CAxesDlg::RedrawColorPicture()
{
	// Get placeholder coordinates
	CRect cRect;
	m_cColorPicture.GetWindowRect(&cRect);
	ScreenToClient(&cRect);

	// Force update of drawing area
	InvalidateRect(cRect);
	UpdateWindow();
}

/*--------------------------------------------------------------------------*/
/* OnPaint                                                          		*/
/*--------------------------------------------------------------------------*/
void CAxesDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Get placeholder coordinates
	CRect cRectMinimum;
	m_cColorPicture.GetWindowRect(&cRectMinimum);
	ScreenToClient(&cRectMinimum);

	// Draw inside placeholder rectangle
	CBrush cBrushMinimum;
	cBrushMinimum.CreateSolidBrush(m_cColor);
	dc.FillRect(&cRectMinimum, &cBrushMinimum);
}

/*--------------------------------------------------------------------------*/
/* OnButtonColor                                                    		*/
/*--------------------------------------------------------------------------*/
void CAxesDlg::OnButtonColor() 
{
	CColorDialog cDlg;
	if (cDlg.DoModal() == IDOK)
	{
		m_cColor = cDlg.GetColor();
		RedrawColorPicture();
	}	
}