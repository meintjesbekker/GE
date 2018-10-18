/*--------------------------------------------------------------------------*/
/*							IterationsEditBox.h   							*/
/*                            												*/
/*	Purpose	: Edit box for number of iterations of smooth filter.			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".                       	*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_ITERATIONSEDITBOX_H__842B8203_5146_11D3_B819_0060084B410C__INCLUDED_)
#define AFX_ITERATIONSEDITBOX_H__842B8203_5146_11D3_B819_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIterationsEditBox : public CEdit
{
// public operations
public:
	CIterationsEditBox();
	virtual ~CIterationsEditBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIterationsEditBox)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CIterationsEditBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ITERATIONSEDITBOX_H__842B8203_5146_11D3_B819_0060084B410C__INCLUDED_)
