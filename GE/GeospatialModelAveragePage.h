/*--------------------------------------------------------------------------*/
/*						GeospatialModelAveragePage.h   						*/
/*                            												*/
/*	Purpose	: Average page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide section 3.3.3 "Average".           				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELAVERAGEPAGE_H__7A82C276_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELAVERAGEPAGE_H__7A82C276_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "GeospatialModel.h"
#include "GeospatialModelAverageGrid.h"
#include "Model.h"
#endif // _MSC_VER > 1000

class CGeospatialModelAveragePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGeospatialModelAveragePage)

// public operations
public:
	CGeospatialModelAveragePage(CModel* pcModel = NULL,	
								CGeospatialModel* pGeospatialModel = NULL);
	~CGeospatialModelAveragePage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelAveragePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CGeospatialModelAveragePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CGeospatialModelAveragePage)
	enum { IDD = IDD_GEOSPATIAL_MODEL_AVERAGE };
	CGeospatialModelAverageGrid	m_cMSFlexGrid;
	//}}AFX_DATA

// private attributes
private:
	CModel*	m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELAVERAGEPAGE_H__7A82C276_CCB9_11D3_B161_0060084B410C__INCLUDED_)
