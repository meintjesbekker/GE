/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorAddDlg.cpp  					*/
/*                            												*/
/*	Purpose	: Dialog to add a new contour and color.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSContourAndColorAddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction									                            */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorAddDlg::CMT3DMSContourAndColorAddDlg(CWnd* pParent /* = NULL */)
								: CDialog(CMT3DMSContourAndColorAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMT3DMSContourAndColorAddDlg)
	m_fValue = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Message Map  								                            */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSContourAndColorAddDlg, CDialog)
	//{{AFX_MSG_MAP(CMT3DMSContourAndColorAddDlg)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Destruction 									                            */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMT3DMSContourAndColorAddDlg)
	DDX_Control(pDX, IDC_STATIC_COLOR, m_cColorPicture);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_fValue);
	DDV_MinMaxFloat(pDX, m_fValue, -1.e+006f, 1.e+006f);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnButtonColor								                            */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorAddDlg::OnButtonColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_cColor = dlg.GetColor();
		RedrawColorPicture();
	}	
}

/*--------------------------------------------------------------------------*/
/* OnPaint     									                            */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorAddDlg::OnPaint() 
{
	// Device context for painting
	CPaintDC dc(this); 
	
	// Get placeholder coordinates
	CRect rect;
	m_cColorPicture.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// Draw inside placeholder rectangle
	CBrush brush;
	brush.CreateSolidBrush(m_cColor);
	dc.FillRect(&rect, &brush);
}

/*--------------------------------------------------------------------------*/
/* RedrawColorPicture							                            */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorAddDlg::RedrawColorPicture()
{
	// Get placeholder coordinates
	CRect rect;
	m_cColorPicture.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// Force update of drawing area
	InvalidateRect(rect);
	UpdateWindow();
}