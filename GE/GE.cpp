/*--------------------------------------------------------------------------*/
/*								GE.cpp    									*/
/*                            												*/
/*	Purpose	: Main application file.										*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MainFrm.h"
#include "Splash.h"
#include "vtkDoc.h"
#include "vtkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction																*/
/*--------------------------------------------------------------------------*/
CGEApp::CGEApp()
{
	pDocTemplate = NULL;
}

/*--------------------------------------------------------------------------*/
/* Message Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGEApp, CWinApp)
	//{{AFX_MSG_MAP(CGEApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* The one and only CGEApp object. 											*/
/*--------------------------------------------------------------------------*/
CGEApp theApp;

/*--------------------------------------------------------------------------*/
/* InitInstance																*/
/*--------------------------------------------------------------------------*/
BOOL CGEApp::InitInstance()
{
	AfxEnableControlContainer(); // enable support for containment of OLE controls

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need.
	#ifdef _AFXDLL
		Enable3dControls(); // Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic(); // Call this when linking to MFC statically
	#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("GE"));

	// not loading MRU files
	LoadStdProfileSettings();	// enable and load the list of most recently used (MRU) files 
								// and last preview state. If nMaxMRU is 0, no MRU list will 
								// be maintained.

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.
	pDocTemplate = new CSingleDocTemplate(	IDR_MAINFRAME,
											RUNTIME_CLASS(CVtkDoc),
											RUNTIME_CLASS(CMainFrame), // main SDI frame window
											RUNTIME_CLASS(CVtkView));
	if (!pDocTemplate)
		return FALSE;

	// add a document template to the list of available document templates which the application maintains
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo; // class aids in parsing the command line at application startup
	ParseCommandLine(cmdInfo);

	// The following lines were added by the Splash Screen component
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) // nonzero if the shell command is processed successfully
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
    if (!((CMainFrame*) m_pMainWnd)->RestoreWindowState())
        m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/*--------------------------------------------------------------------------*/
/* PreTranslateMessage                										*/
/*--------------------------------------------------------------------------*/
BOOL CGEApp::PreTranslateMessage(MSG* pMsg)
{
	// The following lines were added by the Splash Screen component
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;
	return CWinApp::PreTranslateMessage(pMsg);
}

/*--------------------------------------------------------------------------*/
/* CAboutDlg class.                     									*/
/*--------------------------------------------------------------------------*/
class CAboutDlg : public CDialog
{
// public operations
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*--------------------------------------------------------------------------*/
/* Construction                       										*/
/*--------------------------------------------------------------------------*/
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                         										*/
/*--------------------------------------------------------------------------*/
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* Message Map                        										*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnAppAbout                         										*/
/*--------------------------------------------------------------------------*/
void CGEApp::OnAppAbout()
{
	CAboutDlg cAboutDlg;
	cAboutDlg.DoModal();
}

/*--------------------------------------------------------------------------*/
/* OnFileOpen                         										*/
/*--------------------------------------------------------------------------*/
void CGEApp::OnFileOpen() 
{
	CFileDialog cFileDlg(	TRUE,
						    _T("GE"),
							NULL,
							OFN_HIDEREADONLY,
							_T("Groundwater Explorer (*.gwe)|*.gwe|PMWIN Model (*.pm5)|*.pm5|All Files|*.*||"),
							NULL);
	if (cFileDlg.DoModal() == IDOK)
		m_pDocManager->OpenDocumentFile(cFileDlg.GetPathName());
}