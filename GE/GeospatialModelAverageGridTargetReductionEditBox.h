/*--------------------------------------------------------------------------*/
/*			GeospatialModelAverageGridTargetReductionEditBox.h   			*/
/*                            												*/
/*	Purpose	: Edit box for target reduction.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELAVERAGEGRIDTARGETREDUCTIONEDITBOX_H__ABCF6066_CE58_11D3_B167_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELAVERAGEGRIDTARGETREDUCTIONEDITBOX_H__ABCF6066_CE58_11D3_B167_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeospatialModelAverageGridTargetReductionEditBox : public CEdit
{
// public operations
public:
	CGeospatialModelAverageGridTargetReductionEditBox();
	virtual ~CGeospatialModelAverageGridTargetReductionEditBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelAverageGridTargetReductionEditBox)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelAverageGridTargetReductionEditBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELAVERAGEGRIDTARGETREDUCTIONEDITBOX_H__ABCF6066_CE58_11D3_B167_0060084B410C__INCLUDED_)
