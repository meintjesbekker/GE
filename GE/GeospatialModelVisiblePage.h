/*--------------------------------------------------------------------------*/
/*						GeospatialModelVisiblePage.h   						*/
/*                            												*/
/*	Purpose	: Visible page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.2 "Visible".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELVISIBLEPAGE_H__7A82C277_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELVISIBLEPAGE_H__7A82C277_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "GeospatialModel.h"
#include "Model.h"
#include "GeospatialModelVisibleGrid.h"
#endif // _MSC_VER > 1000

class CGeospatialModelVisiblePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGeospatialModelVisiblePage)

// public operations
public:
	CGeospatialModelVisiblePage(CModel*	pcModel = NULL,	
								CGeospatialModel* pcGeospatialModel = NULL);
	~CGeospatialModelVisiblePage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelVisiblePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CGeospatialModelVisiblePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CGeospatialModelVisiblePage)
	enum { IDD = IDD_GEOSPATIAL_MODEL_VISIBLE };
	CGeospatialModelVisibleGrid m_cMSFlexGrid;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELVISIBLEPAGE_H__7A82C277_CCB9_11D3_B161_0060084B410C__INCLUDED_)
