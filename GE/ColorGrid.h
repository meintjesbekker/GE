/*--------------------------------------------------------------------------*/
/*								ColorGrid.h   								*/
/*                            												*/
/*	Purpose	: Grid which contains interval/s and color. 			        */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORGRID_H__49EA9972_D614_11D3_B177_0060084B410C__INCLUDED_)
#define AFX_COLORGRID_H__49EA9972_D614_11D3_B177_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxctl.h>
#include <Afxtempl.h>
#include "Color.h"
#include "ColorEditBox.h"
#include "Model.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CColorGrid : public CMSFlexGrid
{
// public operations
public:
	CColorGrid();
	virtual ~CColorGrid();
	void InitializeGrid();
	void UpdateGrid();
	void SetColorPointer(CColor* pColor);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// protected operations
protected:
	afx_msg void OnClickGrid();
	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	afx_msg void OnLeaveCellGrid();
	DECLARE_EVENTSINK_MAP()

	//{{AFX_MSG(CColorGrid)
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	CColorTable m_cColorTable;
	long m_lBorderWidth; 
	long m_lBorderHeight;
	int m_iNumberOfLogPixelsX;
	int m_iNumberOfLogPixelsY;

// private attributes
private:
	CColor* m_pColor;
	CColorEditBox m_cColorEdit;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLORGRID_H__49EA9972_D614_11D3_B177_0060084B410C__INCLUDED_)
