/*--------------------------------------------------------------------------*/
/*							ColorLevelDlg.cpp  								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Color Level GUI.           */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.4.3 and 3.6.2 "Color".  				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorLevelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorLevelDlg::CColorLevelDlg(CWnd* pParent /* = NULL */) 
	: CDialog(CColorLevelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorLevelDlg)
	m_fInterval = 0.0f;
	m_fMaximumScalarValue = 0.0f;
	m_fMinimumScalarValue = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CColorLevelDlg, CDialog)
	//{{AFX_MSG_MAP(CColorLevelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* DDV_Interval                                                             */
/*--------------------------------------------------------------------------*/
void AFXAPI DDV_Interval(HWND hWnd, CDataExchange* pDX, float fMinimum, float fMaximum, float fInterval)
{
	if (fInterval < 0 || fInterval > (fMaximum - fMinimum))
	{
		CString str;
		str.Format(_T("Please enter a value from 0 to %f."), double(fMaximum) - double(fMinimum));
		::MessageBox(hWnd, str, "Error", MB_ICONEXCLAMATION);
		pDX->Fail();
	}
}

/*--------------------------------------------------------------------------*/
/* DDV_Maximum                                                              */
/*--------------------------------------------------------------------------*/
void AFXAPI DDV_Maximum(HWND hWnd, CDataExchange* pDX, float fMinimum, float fMaximum)
{
	if (fMaximum < fMinimum)
	{
		CString str;
		str.Format(_T("Please enter a value equal or greater than %f."), fMinimum);
		::MessageBox(hWnd, str, "Error", MB_ICONEXCLAMATION);
		pDX->Fail();
	}
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CColorLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorLevelDlg)
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_fInterval);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM, m_fMaximumScalarValue);
	DDX_Text(pDX, IDC_EDIT_MINIMUM, m_fMinimumScalarValue);
	//}}AFX_DATA_MAP
	pDX->PrepareEditCtrl(IDC_EDIT_MAXIMUM);
	DDV_Maximum(GetSafeHwnd(), pDX, m_fMinimumScalarValue, m_fMaximumScalarValue);
	pDX->PrepareEditCtrl(IDC_EDIT_INTERVAL);
	DDV_Interval(GetSafeHwnd(), pDX, m_fMinimumScalarValue, m_fMaximumScalarValue, m_fInterval);
}