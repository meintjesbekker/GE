/*--------------------------------------------------------------------------*/
/*					GeospatialModelVisibleGrid.h   							*/
/*                            												*/
/*	Purpose	: Grid which contains top, sides and bottom.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.2 "Visible".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELVISIBLEGRID_H__ABCF6069_CE58_11D3_B167_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELVISIBLEGRID_H__ABCF6069_CE58_11D3_B167_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxctl.h>
#include <Afxtempl.h>
#include "GeospatialModel.h"
#include "Model.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CGeospatialModelVisibleGrid : public CMSFlexGrid
{
// public operations
public:
	CGeospatialModelVisibleGrid();
	virtual ~CGeospatialModelVisibleGrid();
	void SetModelPointer(CModel* pcModel) {m_pcModel = pcModel;};
	void SetGeospatialModelPointer(CGeospatialModel* pcGeospatialModel) {m_pcGeospatialModel = pcGeospatialModel;};
	void InitializeGrid();
	BOOL GetVisibilityTop(int iLayer) const {return m_bVisibleTopArray[iLayer - 1];};
	BOOL GetVisibilitySides(int iLayer) const {return m_bVisibleSidesArray[iLayer - 1];};
	BOOL GetVisibilityBottom(int iLayer) const {return m_bVisibleBottomArray[iLayer - 1];};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelVisibleGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelVisibleGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	DECLARE_EVENTSINK_MAP()

// private operations
private:
	void SetVisibilityTop(int iLayer, BOOL bVisible) {m_bVisibleTopArray[iLayer - 1] = bVisible;};
	void SetVisibilitySides(int iLayer, BOOL bVisible) {m_bVisibleSidesArray[iLayer - 1] = bVisible;};
	void SetVisibilityBottom(int iLayer, BOOL bVisible) {m_bVisibleBottomArray[iLayer - 1] = bVisible;};

// public attributes
public:
	long m_lBorderWidth; 
	long m_lBorderHeight;
	int m_iNumberOfLogPixelsX;
	int m_iNumberOfLogPixelsY;
	CPictureHolder m_cPictureUnCheck; // uncheck bitmap holder
	CPictureHolder m_cPictureCheck; // check bitmap bolder
	CArray<BOOL, BOOL> m_bVisibleTopArray;
	CArray<BOOL, BOOL> m_bVisibleSidesArray;
	CArray<BOOL, BOOL> m_bVisibleBottomArray;

// private attributes
private:
	CModel* m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELVISIBLEGRID_H__ABCF6069_CE58_11D3_B167_0060084B410C__INCLUDED_)
