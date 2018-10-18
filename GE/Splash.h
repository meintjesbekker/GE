/*--------------------------------------------------------------------------*/
/*								Splash.h									*/
/*                            												*/
/*	Purpose	: Splash window.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:																*/
/*--------------------------------------------------------------------------*/
#ifndef _SPLASH_SCRN_
#define _SPLASH_SCRN_

class CSplashWnd : public CWnd
{
// protected operations
protected:
	CSplashWnd();

// public operations
public:
	static void EnableSplashScreen(BOOL bEnable = TRUE);
	static void ShowSplashScreen(CWnd* pParentWnd = NULL);
	static BOOL PreTranslateAppMessage(MSG* pMsg);
	~CSplashWnd();
	virtual void PostNcDestroy();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	//}}AFX_VIRTUAL

// protected operations
protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	static BOOL c_bShowSplashWnd;
	static CSplashWnd* c_pSplashWnd;

	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	CBitmap m_bitmap;
};

#endif
