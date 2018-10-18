/*--------------------------------------------------------------------------*/
/*							ModelOutlineSheet.h   							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Model Outline.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.2 "Model Outline".                    */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MODELOUTLINESHEET_H__84C0BFC4_20D9_11D4_B1FA_0060084B410C__INCLUDED_)
#define AFX_MODELOUTLINESHEET_H__84C0BFC4_20D9_11D4_B1FA_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModelOutlineSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CModelOutlineSheet)

// public operations
public:
	CModelOutlineSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CModelOutlineSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CModelOutlineSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelOutlineSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CModelOutlineSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MODELOUTLINESHEET_H__84C0BFC4_20D9_11D4_B1FA_0060084B410C__INCLUDED_)
