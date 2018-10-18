/*--------------------------------------------------------------------------*/
/*								AxesDlg.h      								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Axes GUI.                	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide section 2.1.4 "Options".            				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_AXESDLG_H__055DBDE1_054B_11D4_B1D3_0060084B410C__INCLUDED_)
#define AFX_AXESDLG_H__055DBDE1_054B_11D4_B1D3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#endif // _MSC_VER > 1000

class CAxesDlg : public CDialog
{
// public operations
public:
	CAxesDlg(	CWnd* pParent = NULL, 
				CModel* pModel = NULL); // standard constructor
	
	// label axes
	BOOL GetXVisible() const {return m_bXVisible;};
	BOOL GetYVisible() const {return m_bYVisible;};
	BOOL GetZVisible() const {return m_bZVisible;};
	float GetFontFactor() const {return m_fFontFactor;};
	int GetNumberOfLabels() const {return m_iNumberOfLabels;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor) {m_cColor = cColor;};

	// color axes
	BOOL GetColorAxesVisibilty() const {return m_bColorAxesVisible;};

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// private operations
private:
	void RedrawColorPicture();

	// Generated message map functions
	//{{AFX_MSG(CAxesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CAxesDlg)
	enum { IDD = IDD_AXES };
	BOOL m_bXVisible;
	BOOL m_bYVisible;
	BOOL m_bZVisible;
	float m_fFontFactor;
	int m_iNumberOfLabels;
	CStatic	m_cColorPicture;
	BOOL m_bColorAxesVisible;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pModel;
	COLORREF m_cColor;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_AXESDLG_H__055DBDE1_054B_11D4_B1D3_0060084B410C__INCLUDED_)
