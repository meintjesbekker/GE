/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsAveragePage.h 						*/
/*                            												*/
/*	Purpose	: Average page for Hydraulic Components GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.2 "Avarage".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTSAVERAGEPAGE_H__02913B61_F0FE_11D3_B1AF_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTSAVERAGEPAGE_H__02913B61_F0FE_11D3_B1AF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "HydraulicComponents.h"
#endif // _MSC_VER > 1000

class CHydraulicComponentsAveragePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CHydraulicComponentsAveragePage)

// public operations
public:
	CHydraulicComponentsAveragePage(CHydraulicComponents* pcHydraulicComponents = NULL);
	~CHydraulicComponentsAveragePage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHydraulicComponentsAveragePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations 
protected:
	// Generated message map functions
	//{{AFX_MSG(CHydraulicComponentsAveragePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public operations
public:
	//{{AFX_DATA(CHydraulicComponentsAveragePage)
	enum { IDD = IDD_HYDRAULIC_COMPONENTS_AVERAGE };
	CButton	m_cAverageCheck;
	BOOL m_bAverage;
	//}}AFX_DATA

// private attributes
private:
	CHydraulicComponents* m_pcHydraulicComponents;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HYDRAULICCOMPONENTSAVERAGEPAGE_H__02913B61_F0FE_11D3_B1AF_0060084B410C__INCLUDED_)
