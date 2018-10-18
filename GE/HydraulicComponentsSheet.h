/*--------------------------------------------------------------------------*/
/*						HydraulicComponentsSheet.h   						*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Hydraulic Components.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7 "Hydraulic Components".             */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTSSHEET_H__6CCCDEB4_D3BA_11D3_B173_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTSSHEET_H__6CCCDEB4_D3BA_11D3_B173_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHydraulicComponentsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CHydraulicComponentsSheet)

// public operations
public:
	CHydraulicComponentsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CHydraulicComponentsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CHydraulicComponentsSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHydraulicComponentsSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CHydraulicComponentsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HYDRAULICCOMPONENTSSHEET_H__6CCCDEB4_D3BA_11D3_B173_0060084B410C__INCLUDED_)
