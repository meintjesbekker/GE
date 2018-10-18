/*--------------------------------------------------------------------------*/
/*						ParameterGeneralPage.h	   							*/
/*                            												*/
/*	Purpose	: General page for Parameter GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.1 "General".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERGENERALPAGE_H__662EF394_A623_11D3_B12F_0060084B410C__INCLUDED_)
#define AFX_PARAMETERGENERALPAGE_H__662EF394_A623_11D3_B12F_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#include "Parameter.h"
#include "ParameterGeneralGrid.h"
#endif // _MSC_VER > 1000

class CParameterGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParameterGeneralPage)

// public operations
public:
	CParameterGeneralPage(CModel* pcModel = NULL, CParameter* pcParameter = NULL);
	~CParameterGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParameterGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// public attributes
public:
	//{{AFX_DATA(CParameterGeneralPage)
	enum { IDD = IDD_PARAMETER_GENERAL };
	CString	m_Description;
	CParameterGeneralGrid m_FlexGrid;
	//}}AFX_DATA

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CParameterGeneralPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private attributes
private:
	CModel* m_pcModel;
	CParameter* m_pcParameter;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PARAMETERGENERALPAGE_H__662EF394_A623_11D3_B12F_0060084B410C__INCLUDED_)
