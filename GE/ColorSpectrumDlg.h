/*--------------------------------------------------------------------------*/
/*							ColorSpectrumDlg.h    							*/
/*                            												*/
/*	Purpose	: Member variables and functions for Color Spectrum GUI.        */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.3.1 "General" and 3.4.3 "Color".     */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORSPECTRUMDLG_H__0A6A5EE4_CD6E_11D3_B165_0060084B410C__INCLUDED_)
#define AFX_COLORSPECTRUMDLG_H__0A6A5EE4_CD6E_11D3_B165_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "resource.h"
#endif // _MSC_VER > 1000

class CColorSpectrumDlg : public CDialog
{
// public operations
public:
	CColorSpectrumDlg(CWnd* pParent = NULL); // standard constructor
	COLORREF GetMinimumColor() const {return m_cMinimumColor;};
	void SetMinimumColor(COLORREF cColor) {m_cMinimumColor = cColor;};
	COLORREF GetMaximumColor() const {return m_cMaximumColor;};
	void SetMaximumColor(COLORREF cColor) {m_cMaximumColor = cColor;};
	COLORREF GetSpectrumColor(int iNumberOfLayers, int iLayer);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSpectrumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorSpectrumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonMinimumColor();
	afx_msg void OnButtonMaximumColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private operations
private:
	void RedrawMinimumColorPicture();
	void RedrawMaximumColorPicture();

// public attributes
public:
	//{{AFX_DATA(CColorSpectrumDlg)
	enum { IDD = IDD_COLOR_SPECTRUM };
	CStatic	m_MaximumColorPicture;
	CStatic	m_MinimumColorPicture;
	//}}AFX_DATA

// private attributes
private:
	COLORREF m_cMinimumColor;
	COLORREF m_cMaximumColor;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLORSPECTRUMDLG_H__0A6A5EE4_CD6E_11D3_B165_0060084B410C__INCLUDED_)
