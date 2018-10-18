/*--------------------------------------------------------------------------*/
/*						ParameterAveragePage.h	   							*/
/*                            												*/
/*	Purpose	: Average page for Parameter GUI.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.2 "Average".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERAVERAGEPAGE_H__662EF393_A623_11D3_B12F_0060084B410C__INCLUDED_)
#define AFX_PARAMETERAVERAGEPAGE_H__662EF393_A623_11D3_B12F_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Parameter.h"
#endif // _MSC_VER > 1000

class CParameterAveragePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParameterAveragePage)

// public operations
public:
	CParameterAveragePage(CParameter* pcParameter = NULL);
	~CParameterAveragePage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParameterAveragePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CParameterAveragePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CParameterAveragePage)
	enum { IDD = IDD_PARAMETER_AVERAGE };
	BOOL m_bAverage;
	//}}AFX_DATA

// private attributes
public:
	CParameter* m_pParameter;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PARAMETERAVERAGEPAGE_H__662EF393_A623_11D3_B12F_0060084B410C__INCLUDED_)
