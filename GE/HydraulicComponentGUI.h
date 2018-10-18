/*--------------------------------------------------------------------------*/
/*						HydraulicComponentGUI.h  							*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages			*/
/*			  of Hydraulic Components visualization object.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7 "Hydraulic Components".             */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTGUI_H__BE0B4961_7D92_11D4_B2F8_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTGUI_H__BE0B4961_7D92_11D4_B2F8_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "AverageGUI.h"
#include "ClipPolyData.h"
#endif // _MSC_VER > 1000

class CHydraulicComponentGUI : public CClipPolyData,
							   public CAverageGUI
{
// public operations
public:
	CHydraulicComponentGUI(CModel* pcModel /* = NULL*/);
	virtual ~CHydraulicComponentGUI();
	
	// general page
	CString GetDescription() const {return m_sDescription;};
	void SetDescription(CString sDescription) {m_sDescription = sDescription;};
	BOOL GetVisibility() const {return m_bVisible;};
	void SetVisibility(BOOL bVisible) {m_bVisible = bVisible;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor) {m_cColor = cColor;};

// protected attributes
protected:
	// general
	CString m_sDescription;
	BOOL m_bVisible;
	COLORREF m_cColor;
};

#endif // !defined(AFX_HYDRAULICCOMPONENTGUI_H__BE0B4961_7D92_11D4_B2F8_0060084B410C__INCLUDED_)
