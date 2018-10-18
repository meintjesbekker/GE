/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorAddDlg.h    					*/
/*                            												*/
/*	Purpose	: Dialog to add a new contour and color.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLORADDDLG_H__127836F4_0C4A_11D4_B1E0_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLORADDDLG_H__127836F4_0C4A_11D4_B1E0_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorAddDlg : public CDialog
{
// public operations
public:
	CMT3DMSContourAndColorAddDlg(CWnd* pParent = NULL);   // standard constructor
	float GetValue() const {return m_fValue;};
	COLORREF GetColor() const {return m_cColor;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSContourAndColorAddDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CMT3DMSContourAndColorAddDlg)
	afx_msg void OnButtonColor();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private operations
private:
	void RedrawColorPicture();

// public attributes
public:
	//{{AFX_DATA(CMT3DMSContourAndColorAddDlg)
	enum { IDD = IDD_MT3DMS_ADD_CONTOUR_COLOR };
	float m_fValue;
	CStatic	m_cColorPicture;
	//}}AFX_DATA

// private attributes
private:
	COLORREF m_cColor;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSCONTOURANDCOLORADDDLG_H__127836F4_0C4A_11D4_B1E0_0060084B410C__INCLUDED_)
