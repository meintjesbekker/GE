/*--------------------------------------------------------------------------*/
/*							VisualizeGrid.h   								*/
/*                            												*/
/*	Purpose	: Grid which contains visible and object fields.                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_VISUALIZEGRID_H__BC465D48_2DE6_11D3_B80D_0060084B410C__INCLUDED_)
#define AFX_VISUALIZEGRID_H__BC465D48_2DE6_11D3_B80D_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxctl.h>
#include <afxtempl.h>
#include "MSFlexGrid.h"
#include "ObjectList.h"
#include "vtkdoc.h"
#endif // _MSC_VER > 1000

class CVisualizeGrid : public CMSFlexGrid
{
// public operations
public:
	CVisualizeGrid();
	virtual ~CVisualizeGrid();
	int GetRowHighLighted() const {return m_iRowHighLighted;};
	int GetNumberOfObjects() const {return m_iNumberOfObjects;};
	BOOL GetVisibility(int iGridIndex) const {return m_pcObjectListArray[iGridIndex - 1]->GetVisibility();};
	void SetVisibility(int iGridIndex, BOOL bVisible) {m_pcObjectListArray[iGridIndex - 1]->SetVisibility(bVisible);};
	void InitializeObjectList();
	void InitializeGrid();
	void SetDocumentPointer(CVtkDoc* pcDoc) {m_pcDoc = pcDoc;};
	void AddObjectToList(BOOL bVisible, int iArrayIndex);
	void RemoveObject();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizeGrid)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CVisualizeGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	afx_msg void OnLeaveCellGrid();
	afx_msg void OnEnterCellGrid();
	DECLARE_EVENTSINK_MAP()

// private attributes
private:
	CVtkDoc* m_pcDoc;
	int	m_iPrevRowHighLighted;
	int	m_iRowHighLighted;
	int	m_iNumberOfObjects;
	int	m_iColumn;
	BOOL m_bHighLight;
	CPictureHolder m_cPictureCheck;
	CPictureHolder m_cPictureUnCheck;
	CArray<CObjectList*, CObjectList*> m_pcObjectListArray;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_VISUALIZEGRID_H__BC465D48_2DE6_11D3_B80D_0060084B410C__INCLUDED_)
