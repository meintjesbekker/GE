/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralPageTD.h 						*/
/*                            												*/
/*	Purpose	: General page for Time Dependent Hydraulic Components GUI.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTSGENERALPAGETD_H__9BB1F734_3781_11D4_B243_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTSGENERALPAGETD_H__9BB1F734_3781_11D4_B243_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "HydraulicComponentsGeneralPage.h"
#endif // _MSC_VER > 1000

class CHydraulicComponentsGeneralPageTD : public CHydraulicComponentsGeneralPage
{
	DECLARE_DYNCREATE(CHydraulicComponentsGeneralPageTD)

// public ooperations
public:
	CHydraulicComponentsGeneralPageTD(CHydraulicComponents* pcHydraulicComponents = NULL);
	~CHydraulicComponentsGeneralPageTD();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHydraulicComponentsGeneralPageTD)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// proctected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CHydraulicComponentsGeneralPageTD)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CHydraulicComponentsGeneralPageTD)
	enum { IDD = IDD_HYDRAULIC_COMPONENTS_GENERAL_TD };
	CComboBox m_cStressPeriod;
	int	m_iStressPeriod;
	//}}AFX_DATA
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HYDRAULICCOMPONENTSGENERALPAGETD_H__9BB1F734_3781_11D4_B243_0060084B410C__INCLUDED_)
