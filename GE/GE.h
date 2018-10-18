/*--------------------------------------------------------------------------*/
/*								GE.h      									*/
/*                            												*/
/*	Purpose	: Main application file.										*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GE_H__2893D375_BC03_11D2_B7A5_0060084B410C__INCLUDED_)
#define AFX_GE_H__2893D375_BC03_11D2_B7A5_0060084B410C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // main symbols

class CGEApp : public CWinApp
{
// public operations
public:
	CGEApp();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGEApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	CSingleDocTemplate* pDocTemplate;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GE_H__2893D375_BC03_11D2_B7A5_0060084B410C__INCLUDED_)
