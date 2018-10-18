/*--------------------------------------------------------------------------*/
/*						GeospatialModelForLayerGUI.h   						*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for General and		*/
/*			  Visible page of GUI for Geospatial Model visualization		*/
/*			  object.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide 3.3 "Geospatial Model".							*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELFORLAYERGUI_H__31F4C1C1_77F4_11D4_B2EA_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELFORLAYERGUI_H__31F4C1C1_77F4_11D4_B2EA_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "DecimateSmoothGUI.h"
#include "PolyData.h"
#endif // _MSC_VER > 1000

class CGeospatialModelForLayerGUI : public CPolyData,
									public CDecimateSmoothGUI
{
// public operations
public:
	CGeospatialModelForLayerGUI(CModel* pcModel = NULL);
	virtual ~CGeospatialModelForLayerGUI();

	// general
	BOOL GetVisibility() const {return m_bVisible;};
	void SetVisibility(BOOL bVisible) {m_bVisible = bVisible;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor) {m_cColor = cColor;};
	float GetOpacity() const {return m_fOpacity;};
	void SetOpacity(float fOpacity) {m_fOpacity = fOpacity;};
	
	// visible
	BOOL GetVisibilityTop() const {return m_bVisibleTop;};
	void SetVisibilityTop(BOOL bVisible) {m_bVisibleTop = bVisible;};
	BOOL GetVisibilitySides() const {return m_bVisibleSides;};
	void SetVisibilitySides(BOOL bVisible) {m_bVisibleSides = bVisible;};
	BOOL GetVisibilityBottom() const {return m_bVisibleBottom;};
	void SetVisibilityBottom(BOOL bVisible) {m_bVisibleBottom = bVisible;};

// protected attributes
protected:
	// general
	BOOL m_bVisible;
	COLORREF m_cColor;
	float m_fOpacity;

	// visible
	BOOL m_bVisibleTop;
	BOOL m_bVisibleSides;
	BOOL m_bVisibleBottom;
};

#endif // !defined(AFX_GEOSPATIALMODELFORLAYERGUI_H__31F4C1C1_77F4_11D4_B2EA_0060084B410C__INCLUDED_)
