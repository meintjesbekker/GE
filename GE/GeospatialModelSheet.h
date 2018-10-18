/*--------------------------------------------------------------------------*/
/*						GeospatialModelSheet.h   							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Geospatial Model.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3 "Geospatial Model".					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELSHEET_H__7A82C275_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELSHEET_H__7A82C275_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeospatialModelSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CGeospatialModelSheet)

// public operations
public:
	CGeospatialModelSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGeospatialModelSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CGeospatialModelSheet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelSheet)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELSHEET_H__7A82C275_CCB9_11D3_B161_0060084B410C__INCLUDED_)