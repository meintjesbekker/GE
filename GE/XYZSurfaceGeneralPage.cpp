/*--------------------------------------------------------------------------*/
/*						XYZSurfaceGeneralPage.cpp							*/
/*                            												*/
/*	Purpose	: General page for XYZ Surface GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5.1 "General".           				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZSurfaceGeneralPage.h"
#include "ReadFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create															*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CXYZSurfaceGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction             												*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceGeneralPage::CXYZSurfaceGeneralPage(	CXYZSurface* pcXYZSurface,	/* = NULL */
											    BOOL bPathAndFileNameEnabled /* = TRUE */) 
	: CPropertyPage(CXYZSurfaceGeneralPage::IDD)
{
	m_pcXYZSurface = pcXYZSurface;
	m_bOnInitDialog = FALSE;
	m_bPathAndFilenameEnabled = bPathAndFileNameEnabled;

	//{{AFX_DATA_INIT(CXYZSurfaceGeneralPage)
	m_sDescription = _T("");
	m_sPathName = _T("");
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceGeneralPage::~CXYZSurfaceGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CXYZSurfaceGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CXYZSurfaceGeneralPage)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_XYZFILE, OnButtonOpenXYZFile)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CXYZSurfaceGeneralPage::OnOK() 
{
	m_pcXYZSurface->SetDescription(m_sDescription);
	m_pcXYZSurface->SetPathName(m_sPathName);
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DDV_XYZFile                                                              */
/*--------------------------------------------------------------------------*/
void AFXAPI DDV_XYZFile(HWND hWnd, CDataExchange* pDX, CString pathName)
{
	if (pathName.IsEmpty())
	{
		CString str;
		str.Format(_T("Please enter a XYZ File."));
		::MessageBox(hWnd, str, "GE", MB_ICONEXCLAMATION);
		pDX->Fail();
	}
	else
		if (!CReadFile::FileExists(pathName))
		{
			CString str;
			str.Format(_T("The XYZ File does not exist. Please enter a correct XYZ File."));
			::MessageBox(hWnd, str, "GE", MB_ICONEXCLAMATION);
			pDX->Fail();
		}
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange           												*/
/*--------------------------------------------------------------------------*/
void CXYZSurfaceGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXYZSurfaceGeneralPage)
	DDX_Control(pDX, IDC_BUTTON_OPEN_XYZFILE, m_cOpenButton);
	DDX_Control(pDX, IDC_EDIT_PATHNAME, m_cPathNameEdit);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_cDescriptionEdit);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDV_MaxChars(pDX, m_sDescription, 255);
	DDX_Text(pDX, IDC_EDIT_PATHNAME, m_sPathName);
	//}}AFX_DATA_MAP
	if (m_bOnInitDialog)
	{
		pDX->PrepareEditCtrl(IDC_EDIT_PATHNAME);
		DDV_XYZFile(GetSafeHwnd(), pDX, m_sPathName);
	}
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CXYZSurfaceGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcXYZSurface->GetDescription();
	m_sPathName = m_pcXYZSurface->GetFolderAndFileName();
	if (!m_bPathAndFilenameEnabled)
	{
		m_cPathNameEdit.EnableWindow(FALSE);
		m_cOpenButton.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	m_bOnInitDialog = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnButtonOpenXYZFile                                                      */
/*--------------------------------------------------------------------------*/
void CXYZSurfaceGeneralPage::OnButtonOpenXYZFile() 
{
	CFileDialog fileDlg(TRUE,
					    _T("*.xyz"),
					    NULL,
					    OFN_HIDEREADONLY,
					    _T("XYZ Files (*.xyz)|*.xyz|All Files|*.*||"),
					    NULL
					    );
	if (fileDlg.DoModal() == IDOK)
		m_cPathNameEdit.SetWindowText(fileDlg.GetPathName());
}