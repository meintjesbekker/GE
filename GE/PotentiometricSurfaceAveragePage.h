/*--------------------------------------------------------------------------*/
/*					PotentiometricSurfaceAveragePage.h  					*/
/*                            												*/
/*	Purpose	: Average page for Potentiometric Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4.2 "Average".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POTENTIOMETRICSURFACEAVERAGEPAGE_H__0CB205F3_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
#define AFX_POTENTIOMETRICSURFACEAVERAGEPAGE_H__0CB205F3_EDB4_11D3_B1AC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "PotentiometricSurface.h"
#endif // _MSC_VER > 1000

class CPotentiometricSurfaceAveragePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPotentiometricSurfaceAveragePage)

// public operations
public:
	CPotentiometricSurfaceAveragePage(CPotentiometricSurface* pcPotentiometricSurface = NULL);
	~CPotentiometricSurfaceAveragePage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPotentiometricSurfaceAveragePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CPotentiometricSurfaceAveragePage)
	afx_msg void OnCheckAverage();
	afx_msg void OnCheckDecimate();
	afx_msg void OnCheckSmooth();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CPotentiometricSurfaceAveragePage)
	enum { IDD = IDD_POTENTIOMETRIC_SURFACE_AVERAGE };
	CEdit m_cRelaxationFactorEdit;
	CEdit m_cTargetReductionEdit;
	CEdit m_cNumberOfIterationsEdit;
	CButton	m_cSmoothCheck;
	CButton	m_cDecimateCheck;
	CButton m_cAverageCheck;
	BOOL m_bAverage;
	BOOL m_bDecimate;
	BOOL m_bSmooth;
	int m_iNumberOfIterations;
	float m_fTargetReduction;
	float m_fRelaxationFactor;
	//}}AFX_DATA

// private attributes
private:
	CPotentiometricSurface* m_pcPotentiometricSurface;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_POTENTIOMETRICSURFACEAVERAGEPAGE_H__0CB205F3_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)