/*--------------------------------------------------------------------------*/
/*							VisualizeDlg.h    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Visualize dialog box.      */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_VISUALIZEDLG_H__7A82C27A_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_VISUALIZEDLG_H__7A82C27A_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "MenuButton.h"
#include "VisualizeGrid.h"
#include "VtkDoc.h"
#endif // _MSC_VER > 1000

class CVisualizeDlg : public CDialog
{
// Construction
public:
	CVisualizeDlg(CWnd* pParent = NULL, CVtkDoc* pDoc = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisualizeDlg)
	enum { IDD = IDD_VISUALIZE };
	CButton	m_ButtonRemove;
	CMenuButton	m_ButtonAdd;
	CVisualizeGrid m_VisualizeGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateMenuUI(CWnd* pOwner, CMenu* pMenu, BOOL bAutoMenuEnable = TRUE);
	void AddParameter(PARAMETERTYPE parameter);

	// Generated message map functions
	//{{AFX_MSG(CVisualizeDlg)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnAddGeospatialModel();
	afx_msg void OnAddXYZSsurface();
	afx_msg void OnAddParameterHorizontalHydraulicConductivity();
	afx_msg void OnAddParameterVerticalHydraulicConductivity();
	afx_msg void OnAddParameterSpecificStorage();
	afx_msg void OnAddParameterTransmissivity();
	afx_msg void OnAddParameterVerticalLeakance();
	afx_msg void OnAddParameterStorageCoefficient();
	afx_msg void OnAddParameterEffectivePorosity();
	afx_msg void OnAddParameterSpecificYield();
	afx_msg void OnAddIsosurfaceMT3DMS();
	afx_msg void OnUpdateAddParameterHorizontalHydraulicConductivity(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterVerticalHydraulicConductivity(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterSpecificStorage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterTransmissivity(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterVerticalLeakance(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterStorageCoefficient(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterEffectivePorosity(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddParameterSpecificYield(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnAddPotentiometricSurface();
	afx_msg void OnUpdateAddPotentiometricSurface(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddIsosurfaceMT3DMS(CCmdUI* pCmdUI);
	afx_msg void OnAddModelOutline();
	afx_msg void OnAddTimeIndependantHydraulicComponents();
	afx_msg void OnAddTimeDependentHydraulicComponents();
	afx_msg void OnAddIsosurfacePHT3D();
	afx_msg void OnUpdateAddIsosurfacePHT3D(CCmdUI* pCmdUI);
	afx_msg void OnAddIsosurfaceRT3D();
	afx_msg void OnUpdateAddIsosurfaceRT3D(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddHydraulicComponentsTimeindependant(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddHydraulicComponentsTimedependent(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CVtkDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALIZEDLG_H__7A82C27A_CCB9_11D3_B161_0060084B410C__INCLUDED_)
