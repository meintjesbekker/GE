/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralGrid.h   						*/
/*                            												*/
/*	Purpose	: Grid which contains description, visible and color fields.    */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTSGENERALGRID_H__6CCCDEB5_D3BA_11D3_B173_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTSGENERALGRID_H__6CCCDEB5_D3BA_11D3_B173_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxctl.h>
#include "HydraulicComponents.h"
#include "Model.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CHydraulicComponentsGeneralGrid : public CMSFlexGrid
{
// public operations
public:
	CHydraulicComponentsGeneralGrid();
	virtual ~CHydraulicComponentsGeneralGrid();
	void SetHydraulicComponentsPointer(CHydraulicComponents* pcHydraulicComponents) {m_pcHydraulicComponents = pcHydraulicComponents;};
	BOOL GetVisibility(int iIndex) const {return m_bVisibleArray[iIndex - 1];};
	COLORREF GetColor(int iIndex) const {return m_cColorArray[iIndex - 1];};
	void InitializeGrid();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHydraulicComponentsGeneralGrid)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CHydraulicComponentsGeneralGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	DECLARE_EVENTSINK_MAP()

// private operations
private:
	void SetVisibility(int iIndex, BOOL bVisible) {m_bVisibleArray[iIndex - 1] = bVisible;};
	void SetColor(int iIndex, COLORREF cColor) {m_cColorArray[iIndex - 1] = cColor;};

// public attributes
public:
	CArray<BOOL, BOOL> m_bVisibleArray;
	CArray<COLORREF, COLORREF> m_cColorArray;
	
// private attributes
private:
	CHydraulicComponents* m_pcHydraulicComponents;
	CPictureHolder m_cPictureUnCheck; // uncheck bitmap holder
	CPictureHolder m_cPictureCheck; // check bitmap bolder
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HYDRAULICCOMPONENTSGENERALGRID_H__6CCCDEB5_D3BA_11D3_B173_0060084B410C__INCLUDED_)
