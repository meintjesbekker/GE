/*--------------------------------------------------------------------------*/
/*					GeospatialModelGeneralPage.h   							*/
/*                            												*/
/*	Purpose	: General page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General". 						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELGENERALPAGE_H__7A82C274_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELGENERALPAGE_H__7A82C274_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#include "GeospatialModel.h"
#include "GeospatialModelGeneralGrid.h"
#include "Model.h"
#pragma once
#endif // _MSC_VER > 1000

class CGeospatialModelGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGeospatialModelGeneralPage)

// public operations
public:
	CGeospatialModelGeneralPage(CModel*	pcModel = NULL,	
								CGeospatialModel* pcGeospatialModel = NULL);
	~CGeospatialModelGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelGeneralPage)
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CGeospatialModelGeneralPage)
	enum { IDD = IDD_GEOSPATIAL_MODEL_GENERAL };
	CString	m_sDescription;
	CGeospatialModelGeneralGrid m_cMSFlexGrid;
	//}}AFX_DATA
	
// private attributes
private:
	CModel*	m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELGENERALPAGE_H__7A82C274_CCB9_11D3_B161_0060084B410C__INCLUDED_)
