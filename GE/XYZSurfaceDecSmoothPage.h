/*--------------------------------------------------------------------------*/
/*						XYZSurfaceDecSmoothPage.h  							*/
/*                            												*/
/*	Purpose	: Decimate and Smooth page for XYZ Surface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5.2 "Decimate and Smooth".            */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACEDECSMOOTHPAGE_H__9594B755_579D_11D3_B81E_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACEDECSMOOTHPAGE_H__9594B755_579D_11D3_B81E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "XYZSurface.h"
#endif // _MSC_VER > 1000

class CXYZSurfaceDecSmoothPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CXYZSurfaceDecSmoothPage)

// public operations
public:
	CXYZSurfaceDecSmoothPage(CXYZSurface* pcXYZSurface = NULL);
	~CXYZSurfaceDecSmoothPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CXYZSurfaceDecSmoothPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// public attributes
public:
	//{{AFX_DATA(CXYZSurfaceDecSmoothPage)
	enum { IDD = IDD_XYZ_SURFACE_DECSMOOTH };
	CButton	m_cSmoothCheck;
	CButton	m_cDecimateCheck;
	BOOL m_bDecimate;
	float m_fTargetReduction;
	BOOL m_bSmooth;
	float m_fNumberOfIterations;
	float m_fRelaxationFactor;
	//}}AFX_DATA

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CXYZSurfaceDecSmoothPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private attributes
private:
	CXYZSurface* m_pcXYZSurface;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_XYZSURFACEDECSMOOTHPAGE_H__9594B755_579D_11D3_B81E_0060084B410C__INCLUDED_)
