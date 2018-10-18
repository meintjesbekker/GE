/*--------------------------------------------------------------------------*/
/*							ColorEditBox.h   								*/
/*                            												*/
/*	Purpose	: Edit box to change color on grid.   			                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLOREDITBOX_H__BD683D81_09F0_11D4_B1DA_0060084B410C__INCLUDED_)
#define AFX_COLOREDITBOX_H__BD683D81_09F0_11D4_B1DA_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorEditBox : public CEdit
{
// public operations
public:
	CColorEditBox();
	virtual ~CColorEditBox();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEditBox)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CColorEditBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLOREDITBOX_H__BD683D81_09F0_11D4_B1DA_0060084B410C__INCLUDED_)