/*--------------------------------------------------------------------------*/
/*							ColorLevelDlg.h    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Color Level GUI.           */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.4.3 and 3.6.2 "Color".  				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORLEVELDLG_H__6CCCDEB2_D3BA_11D3_B173_0060084B410C__INCLUDED_)
#define AFX_COLORLEVELDLG_H__6CCCDEB2_D3BA_11D3_B173_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "resource.h"
#endif // _MSC_VER > 1000

class CColorLevelDlg : public CDialog
{
// public operations
public:
	CColorLevelDlg(CWnd* pParent = NULL); // standard constructor
	float GetInterval() const {return m_fInterval;};
	void SetInterval(float fInterval) {m_fInterval = fInterval;};
	float GetMinimumScalarValue() const {return m_fMinimumScalarValue;};
	void SetMinimumScalarValue(float fMinimumScalarValue) {m_fMinimumScalarValue = fMinimumScalarValue;};
	float GetMaximumScalarValue() const {return m_fMaximumScalarValue;};
	void SetMaximumScalarValue(float fMaximumScalarValue) {m_fMaximumScalarValue = fMaximumScalarValue;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorLevelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorLevelDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CColorLevelDlg)
	enum { IDD = IDD_COLOR_LEVEL };
	float m_fInterval;
	float m_fMaximumScalarValue;
	float m_fMinimumScalarValue;
	//}}AFX_DATA
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLORLEVELDLG_H__6CCCDEB2_D3BA_11D3_B173_0060084B410C__INCLUDED_)
