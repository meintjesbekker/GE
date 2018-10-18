/*--------------------------------------------------------------------------*/
/*								ClipDlg.h    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Clip dialog box.          	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.3 Interact.            				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_CLIPDLG_H__93328BC1_D7C7_11D3_B17A_0060084B410C__INCLUDED_)
#define AFX_CLIPDLG_H__93328BC1_D7C7_11D3_B17A_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#endif // _MSC_VER > 1000

class CClipDlg : public CDialog
{
// public operations
public:
	CClipDlg(	CWnd* pParent = NULL, 
				CModel* pModel = NULL); // standard constructor
	BOOL GetClip() const {return m_bClip;};
	float GetXOrigin() const {return m_fXOrigin;};
	float GetYOrigin() const {return m_fYOrigin;};
	float GetZOrigin() const {return m_fZOrigin;};
	float GetXNormal() const {return m_fXNormal;};
	float GetYNormal() const {return m_fYNormal;};
	float GetZNormal() const {return m_fZNormal;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CClipDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:	
	//{{AFX_DATA(CClipDlg)
	enum { IDD = IDD_CLIP };
	CSliderCtrl	m_cZNormalSlider;
	CSliderCtrl	m_cYNormalSlider;
	CSliderCtrl	m_cXNormalSlider;
	BOOL m_bClip;
	float m_fXOrigin;
	float m_fYOrigin;
	float m_fZOrigin;
	float m_fXNormal;
	float m_fYNormal;
	float m_fZNormal;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CLIPDLG_H__93328BC1_D7C7_11D3_B17A_0060084B410C__INCLUDED_)
