/*--------------------------------------------------------------------------*/
/*							GeospatialModel.h   							*/
/*                            												*/
/*	Purpose	: Construct a geostpatial model visualization object for all	*/
/*			  layers.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".         				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODEL_H__7A82C273_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODEL_H__7A82C273_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxpriv.h> // for WM_SETMESSAGESTRING message
#include "GeospatialModelForLayer.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

class CGeospatialModel : public CVisualizationObject
{
public:
	CGeospatialModel(CModel* pModel = NULL);
	virtual ~CGeospatialModel();

	// create, update
	virtual void Create();
	virtual void Update();

	// color
	COLORREF GetMinimumColor();
	void SetMinimumColor(COLORREF cColor);
	COLORREF GetMaximumColor();
	void SetMaximumColor(COLORREF cColor);
	COLORREF GetSpectrumColor(int iLayer);

	// interact
	virtual void Clip();

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();

	// serialize
	virtual void Serialize(CArchive& ar);

// public attributes
public:
	CArray<CGeospatialModelForLayer*, CGeospatialModelForLayer*> m_pLayerArray;

// private attributes
private:
	CModel*	m_pcModel;

	COLORREF m_cMinimumColor;
	COLORREF m_cMaximumColor;
};

#endif // !defined(AFX_GEOSPATIALMODEL_H__7A82C273_CCB9_11D3_B161_0060084B410C__INCLUDED_)