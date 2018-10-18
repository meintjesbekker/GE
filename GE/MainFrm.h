/*--------------------------------------------------------------------------*/
/*								MainFrm.h   								*/
/*                            												*/
/*	Purpose	: Main frame.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MAINFRM_H__2893D379_BC03_11D2_B7A5_0060084B410C__INCLUDED_)
#define AFX_MAINFRM_H__2893D379_BC03_11D2_B7A5_0060084B410C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWnd
{
// protected operations
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnClose();
	afx_msg void OnEndSession(BOOL bEnding);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public operations
public:
	virtual ~CMainFrame();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif
	BOOL CreateProgressBar(	CProgressCtrl* pProgressCtrl,
							LPCTSTR sMessage = NULL,
							int iPaneIndex = 0,
							int iMargin = 10,
							int iMaxWidth = -1,
							UINT uiIDControl = 1);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	BOOL RestoreWindowState();

// private operations
private:
	void SaveWindowState();

// protected attributes
protected:
	CToolBar m_cToolBar;
	CStatusBar m_cStatusBar;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__2893D379_BC03_11D2_B7A5_0060084B410C__INCLUDED_)