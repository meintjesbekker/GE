/*--------------------------------------------------------------------------*/
/*							ColorSpectrumDlg.cpp  							*/
/*                            												*/
/*	Purpose	: Member variables and functions for Color Spectrum GUI.        */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.3.1 "General" and 3.4.3 "Color".     */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorSpectrumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorSpectrumDlg::CColorSpectrumDlg(CWnd* pParent /* = NULL */)
	: CDialog(CColorSpectrumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorSpectrumDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CColorSpectrumDlg, CDialog)
	//{{AFX_MSG_MAP(CColorSpectrumDlg)
	ON_BN_CLICKED(IDC_BUTTON_MINIMUM_COLOR, OnButtonMinimumColor)
	ON_BN_CLICKED(IDC_BUTTON_MAXIMUM_COLOR, OnButtonMaximumColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* GetSpectrumColor                                                         */
/*--------------------------------------------------------------------------*/
COLORREF CColorSpectrumDlg::GetSpectrumColor(int iNumberOfLayers, int iLayer)
{	
	COLORREF cColor(NULL);
	if (iLayer == 1)
		cColor = m_cMinimumColor;
	else 
		if (iLayer == iNumberOfLayers)
			cColor = m_cMaximumColor;

	// if number of layers > 2
	if (iNumberOfLayers > 2)
	{
		float fDeltaRed = (GetRValue(m_cMaximumColor) - GetRValue(m_cMinimumColor)) / (iNumberOfLayers - 1);
		float fDeltaGreen = (GetGValue(m_cMaximumColor) - GetGValue(m_cMinimumColor)) / (iNumberOfLayers - 1);
		float fDeltaBlue = (GetBValue(m_cMaximumColor) - GetBValue(m_cMinimumColor)) / (iNumberOfLayers - 1);
		cColor =  RGB(	GetRValue(m_cMinimumColor) + (iLayer - 1) * fDeltaRed,
						GetGValue(m_cMinimumColor) + (iLayer - 1) * fDeltaGreen,
						GetBValue(m_cMinimumColor) + (iLayer - 1) * fDeltaBlue);
	}
	return cColor;
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorSpectrumDlg)
	DDX_Control(pDX, IDC_STATIC_MAXIMUM_COLOR, m_MaximumColorPicture);
	DDX_Control(pDX, IDC_STATIC_MINIMUM_COLOR, m_MinimumColorPicture);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CColorSpectrumDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnPaint                                                                  */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::OnPaint() 
{
	// Device context for painting
	CPaintDC cDC(this); 
	
	// Get placeholder coordinates
	CRect cRectMinimum;
	m_MinimumColorPicture.GetWindowRect(&cRectMinimum);
	ScreenToClient(&cRectMinimum);

	// Draw inside placeholder rectangle
	CBrush cBrushMinimum;
	cBrushMinimum.CreateSolidBrush(m_cMinimumColor);
	cDC.FillRect(&cRectMinimum, &cBrushMinimum);

	// Get placeholder coordinates
	CRect cRectMaximum;
	m_MaximumColorPicture.GetWindowRect(&cRectMaximum);
	ScreenToClient(&cRectMaximum);

	// Draw inside placeholder rectangle
	CBrush cBrushMaximum;
	cBrushMaximum.CreateSolidBrush(m_cMaximumColor);
	cDC.FillRect(&cRectMaximum, &cBrushMaximum);
}

/*--------------------------------------------------------------------------*/
/* OnButtonMinimumColor                                                     */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::OnButtonMinimumColor() 
{
	CColorDialog cDlg;
	if (cDlg.DoModal() == IDOK)
	{
		m_cMinimumColor = cDlg.GetColor();
		RedrawMinimumColorPicture();
	}	
}

/*--------------------------------------------------------------------------*/
/* OnButtonMaximumColor                                                     */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::OnButtonMaximumColor() 
{
	CColorDialog cDlg;
	if (cDlg.DoModal() == IDOK)
	{
		m_cMaximumColor = cDlg.GetColor();
		RedrawMaximumColorPicture();
	}
}

/*--------------------------------------------------------------------------*/
/* RedrawMinimumColorPicture                                                */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::RedrawMinimumColorPicture()
{
	// Get placeholder coordinates
	CRect cRect;
	m_MinimumColorPicture.GetWindowRect(&cRect);
	ScreenToClient(&cRect);

	// Force update of drawing area
	InvalidateRect(cRect);
	UpdateWindow();
}

/*--------------------------------------------------------------------------*/
/* RedrawMaximumColorPicture                                                */
/*--------------------------------------------------------------------------*/
void CColorSpectrumDlg::RedrawMaximumColorPicture()
{
	// Get placeholder coordinates
	CRect cRect;
	m_MaximumColorPicture.GetWindowRect(&cRect);
	ScreenToClient(&cRect);

	// Force update of drawing area
	InvalidateRect(cRect);
	UpdateWindow();
}