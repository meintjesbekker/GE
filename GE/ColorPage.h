/*--------------------------------------------------------------------------*/
/*								ColorPage.h                					*/
/*                            												*/
/*	Purpose	: Color GUI page.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.4.3, 3.5.3 and 3.8.3 "Color".		*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORPAGE_H__49EA9971_D614_11D3_B177_0060084B410C__INCLUDED_)
#define AFX_COLORPAGE_H__49EA9971_D614_11D3_B177_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "resource.h"
#include "Color.h"
#include "ColorGrid.h"
#endif // _MSC_VER > 1000

class CColorPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CColorPage)

// public operations
public:
	CColorPage(CColor* pColor = NULL);
	~CColorPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CColorPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// proctected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private attributes
private:
	//{{AFX_DATA(CColorPage)
	enum { IDD = IDD_COLOR_PAGE };
	CSliderCtrl	m_cSlider;
	float m_fOpacity;
	CEdit m_cOpacityEdit;
	CColorGrid m_cMSFlexGrid;
	//}}AFX_DATA
	CColor* m_pColor;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_COLORPAGE_H__49EA9971_D614_11D3_B177_0060084B410C__INCLUDED_)
