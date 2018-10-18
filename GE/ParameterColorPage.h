/*--------------------------------------------------------------------------*/
/* ParameterColorPage.h                                                     */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERCOLORPAGE_H__662EF392_A623_11D3_B12F_0060084B410C__INCLUDED_)
#define AFX_PARAMETERCOLORPAGE_H__662EF392_A623_11D3_B12F_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Parameter.h"
#endif // _MSC_VER > 1000
// ParameterColorPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameterColorPage dialog

class CParameterColorPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParameterColorPage)

// Construction
public:
	CParameterColorPage(CParameter* pParameter = NULL);
	~CParameterColorPage();

// Dialog Data
	//{{AFX_DATA(CParameterColorPage)
	enum { IDD = IDD_PARAMETER_COLOR };
	CButton	m_SolidColorButton;
	CStatic	m_SolidColorPicture;
	CEdit	m_OpacityEdit;
	float	m_Opacity;
	int		m_SolidColorRadio;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParameterColorPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParameter* m_pParameter;
	COLORREF m_SolidColor;
	void RedrawSolidColorPicture();

	// Generated message map functions
	//{{AFX_MSG(CParameterColorPage)
	afx_msg void OnButtonSolidColor();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERCOLORPAGE_H__662EF392_A623_11D3_B12F_0060084B410C__INCLUDED_)
