/*--------------------------------------------------------------------------*/
/*				GeospatialModelGeneralGridOpacityEditBox.h   				*/
/*                            												*/
/*	Purpose	: Edit box for opacity.											*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELGENERALGRIDOPACITYEDITBOX_H__ABCF6061_CE58_11D3_B167_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELGENERALGRIDOPACITYEDITBOX_H__ABCF6061_CE58_11D3_B167_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeospatialModelGeneralGridOpacityEditBox : public CEdit
{
// Construction
public:
	CGeospatialModelGeneralGridOpacityEditBox();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelGeneralGridOpacityEditBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGeospatialModelGeneralGridOpacityEditBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGeospatialModelGeneralGridOpacityEditBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOSPATIALMODELGENERALGRIDOPACITYEDITBOX_H__ABCF6061_CE58_11D3_B167_0060084B410C__INCLUDED_)
