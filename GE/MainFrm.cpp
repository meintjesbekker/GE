/*--------------------------------------------------------------------------*/
/*								MainFrm.cpp 								*/
/*                            												*/
/*	Purpose	: Main frame.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create     														*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

/*--------------------------------------------------------------------------*/
/* Indicators        														*/
/*--------------------------------------------------------------------------*/
static UINT indicators[] =
{
	ID_SEPARATOR, // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
};

/*--------------------------------------------------------------------------*/
/* Construction      														*/
/*--------------------------------------------------------------------------*/
CMainFrame::CMainFrame()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction       														*/
/*--------------------------------------------------------------------------*/
CMainFrame::~CMainFrame()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map       														*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_ENDSESSION()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Diagnostics																*/
/*--------------------------------------------------------------------------*/
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/*--------------------------------------------------------------------------*/
/* OnCreate          														*/
/*--------------------------------------------------------------------------*/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// tool bar
	if (!m_cToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_cToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// status bar
	if (!m_cStatusBar.Create(this) 
		|| !m_cStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Remove this if you don't want tool tips or a resizeable toolbar
	m_cToolBar.SetBarStyle(m_cToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// Delete these three lines if you don't want the toolbar to be dockable
	m_cToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_cToolBar);

	// splash screen
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

/*--------------------------------------------------------------------------*/
/* PreCreateWindow   														*/
/*--------------------------------------------------------------------------*/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// Size the window to 1/3 screen size and center it     
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 1.3;     
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 1.3;     
	cs.y = ((cs.cy * 1.3) - cs.cy) / 2;     
	cs.x = ((cs.cx * 1.3) - cs.cx) / 2;    
	return CFrameWnd::PreCreateWindow(cs);
}

/*--------------------------------------------------------------------------*/
/* CreateProgressBar 														*/
/*--------------------------------------------------------------------------*/
BOOL  CMainFrame::CreateProgressBar(CProgressCtrl*	pProgressCtrl,
									LPCTSTR sMessage,
									int iPaneIndex,
									int iMargin,
									int iMaxWidth,
									UINT uiIDControl)
{
	ASSERT_VALID(pProgressCtrl);

	// Calculate destination rectangle for progress control
    CRect rc;
    m_cStatusBar.GetItemRect( iPaneIndex, &rc );

	// Define progress bar horizontal offset
	if (sMessage != NULL)
	{
		// Compute message text extent
		CClientDC dc(&m_cStatusBar);
		CFont* pFont = m_cStatusBar.GetFont();
		CFont* pOldFont = dc.SelectObject(pFont);
		CSize sizeText = dc.GetTextExtent(sMessage);
		dc.SelectObject(pOldFont);
		rc.left += sizeText.cx + iMargin;
	}

	// Compute progress bar width
	if (iMaxWidth != -1)
		rc.right = rc.left + min(iMaxWidth, rc.Width());

	// Display message text
	m_cStatusBar.SetPaneText(iPaneIndex, sMessage);
	m_cStatusBar.RedrawWindow();

	// Create progress control
    return pProgressCtrl->Create(	WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
									rc, 
									&m_cStatusBar, 
									uiIDControl);
}

/*--------------------------------------------------------------------------*/
/* OnGetMinMaxInfo   														*/
/*--------------------------------------------------------------------------*/
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x = ::GetSystemMetrics(SM_CXSCREEN)/2.8;
	lpMMI->ptMinTrackSize.y = ::GetSystemMetrics(SM_CYSCREEN)/2.8;
}

/*--------------------------------------------------------------------------*/
/* RestoreWindowState														*/
/*--------------------------------------------------------------------------*/
BOOL CMainFrame::RestoreWindowState()
{
    CString version = _T ("Version 1.0");
    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    GetWindowPlacement (&wp);
	CWinApp* pApp = AfxGetApp();
    if (((wp.flags = pApp->GetProfileInt(version, _T ("flags"), -1)) != -1) 
		&& ((wp.showCmd = pApp->GetProfileInt(version, _T ("showCmd"), -1)) != -1) 
		&& ((wp.rcNormalPosition.left = pApp->GetProfileInt(version, _T ("x1"), -1)) != -1) 
		&& ((wp.rcNormalPosition.top = pApp->GetProfileInt(version, _T ("y1"), -1)) != -1) 
		&& ((wp.rcNormalPosition.right = pApp->GetProfileInt(version, _T ("x2"), -1)) != -1) 
		&& ((wp.rcNormalPosition.bottom = pApp->GetProfileInt(version, _T ("y2"), -1)) != -1)) 
	{
        wp.rcNormalPosition.left = min(	wp.rcNormalPosition.left,
										::GetSystemMetrics (SM_CXSCREEN) - ::GetSystemMetrics (SM_CXICON));
        wp.rcNormalPosition.top = min(	wp.rcNormalPosition.top,
										::GetSystemMetrics (SM_CYSCREEN) - ::GetSystemMetrics (SM_CYICON));
        SetWindowPlacement (&wp);
        return TRUE;
    }
    return FALSE;
}

/*--------------------------------------------------------------------------*/
/* SaveWindowState															*/
/*--------------------------------------------------------------------------*/
void CMainFrame::SaveWindowState()
{
    CString version = _T("Version 1.0");
    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    GetWindowPlacement(&wp);
	CWinApp* pApp = AfxGetApp();
    pApp->WriteProfileInt(version, _T("flags"), wp.flags);
    pApp->WriteProfileInt(version, _T("showCmd"), wp.showCmd);
    pApp->WriteProfileInt(version, _T("x1"), wp.rcNormalPosition.left);
    pApp->WriteProfileInt(version, _T("y1"), wp.rcNormalPosition.top);
    pApp->WriteProfileInt(version, _T("x2"), wp.rcNormalPosition.right);
    pApp->WriteProfileInt(version, _T("y2"), wp.rcNormalPosition.bottom);
}

/*--------------------------------------------------------------------------*/
/* OnClose        															*/
/*--------------------------------------------------------------------------*/
void CMainFrame::OnClose() 
{
    SaveWindowState();	
	CFrameWnd::OnClose();
}

/*--------------------------------------------------------------------------*/
/* OnEndSession   															*/
/*--------------------------------------------------------------------------*/
void CMainFrame::OnEndSession(BOOL bEnding) 
{
    if (bEnding)
        SaveWindowState ();
	CFrameWnd::OnEndSession(bEnding);
}
