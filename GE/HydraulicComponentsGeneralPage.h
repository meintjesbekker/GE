/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralPage.h 						*/
/*                            												*/
/*	Purpose	: General page for Hydraulic Components GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTSGENERALPAGE_H__6CCCDEB3_D3BA_11D3_B173_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTSGENERALPAGE_H__6CCCDEB3_D3BA_11D3_B173_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "resource.h"
#include "HydraulicComponents.h"
#include "HydraulicComponentsGeneralGrid.h"
#endif 

class CHydraulicComponentsGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CHydraulicComponentsGeneralPage)

// public operations
public:
	CHydraulicComponentsGeneralPage(CHydraulicComponents* pcHydraulicComponents = NULL);
	CHydraulicComponentsGeneralPage(UINT nIDTemplate, CHydraulicComponents* pcHydraulicComponents = NULL);
	~CHydraulicComponentsGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHydraulicComponentsGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CHydraulicComponentsGeneralPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CHydraulicComponentsGeneralPage)
	enum { IDD = IDD_HYDRAULIC_COMPONENTS_GENERAL };
	CString	m_sDescription;
	CHydraulicComponentsGeneralGrid m_cMSFlexGrid;
	//}}AFX_DATA

// protected attributes
protected:
	CHydraulicComponents* m_pcHydraulicComponents;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HYDRAULICCOMPONENTSGENERALPAGE_H__6CCCDEB3_D3BA_11D3_B173_0060084B410C__INCLUDED_)