/*--------------------------------------------------------------------------*/
/*							XYZSurfaceSheet.h	   							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of XYZ Surface.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5 "XYZ Surface".        				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACESHEET_H__9594B756_579D_11D3_B81E_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACESHEET_H__9594B756_579D_11D3_B81E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXYZSurfaceSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CXYZSurfaceSheet)

// public operations
public:
	CXYZSurfaceSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CXYZSurfaceSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CXYZSurfaceSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXYZSurfaceSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CXYZSurfaceSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_XYZSURFACESHEET_H__9594B756_579D_11D3_B81E_0060084B410C__INCLUDED_)
