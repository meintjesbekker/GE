/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorPage.h   						*/
/*                            												*/
/*	Purpose	: Contour and Color page for Isosurface GUI.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLORPAGE_H__B0FC3EA5_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLORPAGE_H__B0FC3EA5_0AB7_11D4_B1DC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "MT3DMSContourAndColorGrid.h"
#include "Model.h"
#include "MT3DMS.h"
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMT3DMSContourAndColorPage)

// public operations
public:
	CMT3DMSContourAndColorPage(	CModel* pcModel = NULL,	
								CMT3DMS* pcMT3DMS = NULL);
	~CMT3DMSContourAndColorPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSContourAndColorPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CMT3DMSContourAndColorPage)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CMT3DMSContourAndColorPage)
	enum { IDD = IDD_MT3DMS_CONTOUR_COLOR };
	CSliderCtrl	m_cSlider;
	CButton	m_cButtonRemove;
	float m_fOpacity;
	CMT3DMSContourAndColorGrid m_cMSFlexGrid;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pcModel;
	CMT3DMS* m_pcMT3DMS;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSCONTOURANDCOLORPAGE_H__B0FC3EA5_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)