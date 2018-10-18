/*--------------------------------------------------------------------------*/
/*							MT3DMSGeneralPage.h	   							*/
/*                            												*/
/*	Purpose	: General page for Isosurface GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.1 "General".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSGENERALPAGE_H__01F6ED12_C33D_11D3_B152_0060084B410C__INCLUDED_)
#define AFX_MT3DMSGENERALPAGE_H__01F6ED12_C33D_11D3_B152_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "MT3DMS.h"
#endif // _MSC_VER > 1000

class CMT3DMSGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMT3DMSGeneralPage)

// public operations
public:
	CMT3DMSGeneralPage(	CModel* pcModel = NULL, 
						CMT3DMS* pcMT3DMS = NULL, 
						BOOL bControlsEnabled = TRUE);
	~CMT3DMSGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected attributes
protected:
	// Generated message map functions
	//{{AFX_MSG(CMT3DMSGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSpeciesNumber();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CMT3DMSGeneralPage)
	enum { IDD = IDD_MT3DMS_GENERAL };
	CString	m_cDescription;
	CComboBox m_cSpeciesNumberComboBox;
	CComboBox m_cTotalElapsedTimeComboBox;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pcModel;
	CMT3DMS* m_pcMT3DMS;
	BOOL m_bControlsEnabled;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSGENERALPAGE_H__01F6ED12_C33D_11D3_B152_0060084B410C__INCLUDED_)
