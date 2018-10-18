/*--------------------------------------------------------------------------*/
/*					PotentiometricSurfaceGeneralPage.h  					*/
/*                            												*/
/*	Purpose	: General page for Potentiometric Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4.1 "General".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POTENTIOMETRICSURFACEGENERALPAGE_H__0CB205F4_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
#define AFX_POTENTIOMETRICSURFACEGENERALPAGE_H__0CB205F4_EDB4_11D3_B1AC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "PotentiometricSurface.h"
#endif // _MSC_VER > 1000

class CPotentiometricSurfaceGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPotentiometricSurfaceGeneralPage)

// public operations
public:
	CPotentiometricSurfaceGeneralPage(	CPotentiometricSurface* pPotentiometricSurface = NULL,
										BOOL timeParametersEnabled = TRUE);
	~CPotentiometricSurfaceGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPotentiometricSurfaceGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CPotentiometricSurfaceGeneralPage)
	afx_msg void OnSelChangeComboStressPeriod();
	afx_msg void OnSelChangeComboTimeStep();
	afx_msg void OnSelChangeComboLayer();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckHighestHeads();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CPotentiometricSurfaceGeneralPage)
	enum { IDD = IDD_POTENTIOMETRIC_SURFACE_GENERAL };
	CButton	m_cUseHighestHeadsCheck;
	CComboBox m_cComboLayer;
	CComboBox m_cComboTimeStep;
	CComboBox m_cComboStressPeriod;
	CString m_sDescription;
	BOOL m_bUseHighestHeads;
	//}}AFX_DATA

// private operations
private:
	CPotentiometricSurface*	m_pcPotentiometricSurface;
	BOOL m_bTimeParametersEnabled;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_POTENTIOMETRICSURFACEGENERALPAGE_H__0CB205F4_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
