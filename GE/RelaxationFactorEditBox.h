/*--------------------------------------------------------------------------*/
/*						RelaxationFactorEditBox.h   						*/
/*                            												*/
/*	Purpose	: Edit box for relaxation factor.                      			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_RELAXATIONFACTOREDITBOX_H__842B8202_5146_11D3_B819_0060084B410C__INCLUDED_)
#define AFX_RELAXATIONFACTOREDITBOX_H__842B8202_5146_11D3_B819_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRelaxationFactorEditBox : public CEdit
{
// public operations
public:
	CRelaxationFactorEditBox();
	virtual ~CRelaxationFactorEditBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelaxationFactorEditBox)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CRelaxationFactorEditBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_RELAXATIONFACTOREDITBOX_H__842B8202_5146_11D3_B819_0060084B410C__INCLUDED_)
