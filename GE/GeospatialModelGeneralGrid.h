/*--------------------------------------------------------------------------*/
/*						GeospatialModelGeneralGrid.h   						*/
/*                            												*/
/*	Purpose	: Grid which contains visible, color and opacity.               */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELGENERALGRID_H__ABCF6068_CE58_11D3_B167_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELGENERALGRID_H__ABCF6068_CE58_11D3_B167_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxctl.h>
#include <Afxtempl.h>
#include "GeospatialModel.h"
#include "GeospatialModelGeneralGridOpacityEditBox.h"
#include "Model.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CGeospatialModelGeneralGrid : public CMSFlexGrid
{
// public operations
public:
	CGeospatialModelGeneralGrid();
	virtual ~CGeospatialModelGeneralGrid();
	void SetModelPointer(CModel* pcModel) {m_pcModel = pcModel;};
	void SetGeospatialModelPointer(CGeospatialModel* pcGeospatialModel) {m_pcGeospatialModel = pcGeospatialModel;};
	void InitializeGrid();
	BOOL GetVisibility(int iLayer) const {return m_bVisibleArray[iLayer - 1];};
	void SetVisibility(int iLayer, BOOL bVisible) {m_bVisibleArray[iLayer - 1] = bVisible;};
	COLORREF GetColor(int iLayer) const {return m_cColorArray[iLayer - 1];};
	void SetColor(int iLayer, COLORREF cColor) {m_cColorArray[iLayer - 1] = cColor;};
	float GetOpacity(int iLayer) const {return m_fOpacityArray[iLayer - 1];};
	void SetOpacity(int iLayer, float fOpacity) {m_fOpacityArray[iLayer - 1] = fOpacity;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelGeneralGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelGeneralGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnClickGrid();
	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	afx_msg void OnUpdateGrid();
	DECLARE_EVENTSINK_MAP()

// public atttributes
public:
	CGeospatialModelGeneralGridOpacityEditBox m_cOpacityEdit;
	long m_lBorderWidth; 
	long m_lBorderHeight;
	int m_iNumberOfLogPixelsX;
	int m_iNumberOfLogPixelsY;
	CPictureHolder m_cPictureUnCheck; // uncheck bitmap holder
	CPictureHolder m_cPictureCheck; // check bitmap bolder
	CArray<BOOL, BOOL> m_bVisibleArray;
	CArray<COLORREF, COLORREF> m_cColorArray;
	CArray<float, float> m_fOpacityArray;

// private attributes
private:
	CModel*	m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELGENERALGRID_H__ABCF6068_CE58_11D3_B167_0060084B410C__INCLUDED_)
