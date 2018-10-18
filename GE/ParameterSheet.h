/*--------------------------------------------------------------------------*/
/*							ParameterSheet.h   								*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Parameter.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8 "Parameter".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERSHEET_H__662EF395_A623_11D3_B12F_0060084B410C__INCLUDED_)
#define AFX_PARAMETERSHEET_H__662EF395_A623_11D3_B12F_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParameterSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CParameterSheet)

// public operations
public:
	CParameterSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CParameterSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CParameterSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CParameterSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PARAMETERSHEET_H__662EF395_A623_11D3_B12F_0060084B410C__INCLUDED_)
