/*--------------------------------------------------------------------------*/
/*						XYZSurfaceGeneralPage.h 							*/
/*                            												*/
/*	Purpose	: General page for XYZ Surface GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5.1 "General".           				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACEGENERALPAGE_H__9594B754_579D_11D3_B81E_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACEGENERALPAGE_H__9594B754_579D_11D3_B81E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "XYZSurface.h"
#endif // _MSC_VER > 1000

class CXYZSurfaceGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CXYZSurfaceGeneralPage)

// public operations
public:
	CXYZSurfaceGeneralPage(CXYZSurface* pcXYZSurface = NULL, BOOL bPathAndFileNameEnabled = TRUE);
	~CXYZSurfaceGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CXYZSurfaceGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CXYZSurfaceGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOpenXYZFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CXYZSurfaceGeneralPage)
	enum { IDD = IDD_XYZ_SURFACE_GENERAL };
	CButton	m_cOpenButton;
	CEdit m_cPathNameEdit;
	CEdit m_cDescriptionEdit;
	CString	m_sDescription;
	CString	m_sPathName;
	//}}AFX_DATA

// private attributes
private:
	CXYZSurface* m_pcXYZSurface;
	BOOL m_bOnInitDialog;
	BOOL m_bPathAndFilenameEnabled;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_XYZSURFACEGENERALPAGE_H__9594B754_579D_11D3_B81E_0060084B410C__INCLUDED_)