/*--------------------------------------------------------------------------*/
/*								MT3DMSSheet.h   							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Isosurface.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6 "Isosurface".                       */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSSHEET_H__01F6ED13_C33D_11D3_B152_0060084B410C__INCLUDED_)
#define AFX_MT3DMSSHEET_H__01F6ED13_C33D_11D3_B152_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMT3DMSSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMT3DMSSheet)

// public operations
public:
	CMT3DMSSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMT3DMSSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMT3DMSSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CMT3DMSSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSSHEET_H__01F6ED13_C33D_11D3_B152_0060084B410C__INCLUDED_)
