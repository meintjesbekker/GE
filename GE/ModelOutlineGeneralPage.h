/*--------------------------------------------------------------------------*/
/*						ModelOutlineGeneralPage.h   						*/
/*                            												*/
/*	Purpose	: General page for Model Outline GUI.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.2 "Model Outline".                    */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MODELOUTLINEGENERALPAGE_H__84C0BFC3_20D9_11D4_B1FA_0060084B410C__INCLUDED_)
#define AFX_MODELOUTLINEGENERALPAGE_H__84C0BFC3_20D9_11D4_B1FA_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ModelOutline.h"
#include "XYZCoordinate.h"
#endif // _MSC_VER > 1000

class CModelOutlineGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CModelOutlineGeneralPage)

// public operations
public:
	// construction and destruction
	CModelOutlineGeneralPage(CModel* pcModel = NULL, CModelOutline* pcModelOutline = NULL);
	~CModelOutlineGeneralPage();

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CModelOutlineGeneralPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CModelOutlineGeneralPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CModelOutlineGeneralPage)
	enum { IDD = IDD_MODEL_OUTLINE_GENERAL };
	CString	m_sDescription;
	CXYZCoordinate m_cMinimum;
	CXYZCoordinate m_cMaximum;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pcModel;
	CModelOutline* m_pcModelOutline;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MODELOUTLINEGENERALPAGE_H__84C0BFC3_20D9_11D4_B1FA_0060084B410C__INCLUDED_)