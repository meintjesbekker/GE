/*--------------------------------------------------------------------------*/
/*						PotentiometricSurfaceSheet.h   						*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Potentiometric Surface.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4 "Potentiometric Surface".           */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POTENTIOMETRICSURFACESHEET_H__0CB205F2_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
#define AFX_POTENTIOMETRICSURFACESHEET_H__0CB205F2_EDB4_11D3_B1AC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPotentiometricSurfaceSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPotentiometricSurfaceSheet)

// public operations
public:
	CPotentiometricSurfaceSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPotentiometricSurfaceSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPotentiometricSurfaceSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPotentiometricSurfaceSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CPotentiometricSurfaceSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_POTENTIOMETRICSURFACESHEET_H__0CB205F2_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
