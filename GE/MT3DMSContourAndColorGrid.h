/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorGrid.h   						*/
/*                            												*/
/*	Purpose	: Grid which contains contour and color fields.                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLORGRID_H__B0FC3EA8_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLORGRID_H__B0FC3EA8_0AB7_11D4_B1DC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxctl.h>
#include "MT3DMSContourAndColorEditBox.h"
#include "MT3DMSContourAndColorRow.h"
#include "MT3DMSContourAndColorTable.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorGrid : public CMSFlexGrid
{
// public operations
public:
	CMT3DMSContourAndColorGrid();
	virtual ~CMT3DMSContourAndColorGrid();
	int GetSize();
	void InitializeGrid(CMT3DMSContourAndColorTable* pcMT3DMSContourAndColorTable);
	void Remove();
	void Add(CMT3DMSContourAndColorRow* pcMT3DMSContourAndColorRow);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSContourAndColorGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CMT3DMSContourAndColorGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnClickGrid();
	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	afx_msg void OnLeaveCellGrid();
	DECLARE_EVENTSINK_MAP()

// private operation
private:
	void UpdateGrid();

// private attributes
private:
	long m_lBorderWidth; 
	long m_lBorderHeight;
	int m_iLogPixelsX;
	int m_iLogPixelsY;
	int m_iRowSelected;
	CMT3DMSContourAndColorTable* m_pcMT3DMSContourAndColorTable;
	CMT3DMSContourAndColorEditBox m_cEdit;
	CPictureHolder m_cPictureHolder;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSCONTOURANDCOLORGRID_H__B0FC3EA8_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
