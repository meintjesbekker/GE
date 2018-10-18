/*--------------------------------------------------------------------------*/
/*						ParameterGeneralGrid.h   							*/
/*                            												*/
/*	Purpose	: Grid which contains layer and visible fields.                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.1 "General".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERGENERALGRID_H__662EF396_A623_11D3_B12F_0060084B410C__INCLUDED_)
#define AFX_PARAMETERGENERALGRID_H__662EF396_A623_11D3_B12F_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxctl.h> // CPictureHolder
#include <Afxtempl.h> // CArray
#include "Model.h"
#include "MSFlexGrid.h"
#include "Parameter.h"
#endif // _MSC_VER > 1000

class CParameterGeneralGrid : public CMSFlexGrid
{
// public operations
public:
	CParameterGeneralGrid();
	virtual ~CParameterGeneralGrid();
	void SetModelPointer(CModel* pModel) {m_pcModel = pModel;};
	void SetParameterPointer(CParameter* pcParameter) {m_pcParameter = pcParameter;};
	BOOL GetVisibility(int iLayer) const {return m_bVisible[iLayer - 1];};
	void SetVisibility(int iLayer, BOOL bVisible) {m_bVisible[iLayer - 1] = bVisible;};
	void InitializeGrid();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterGeneralGrid)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CParameterGeneralGrid)
	afx_msg void OnDblClickMsFlexGrid();
	afx_msg void OnKeyPressMsFlexGrid(short FAR* KeyAscii);
	afx_msg UINT OnGetDlgCode();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	CArray<BOOL, BOOL> m_bVisible;
	CPictureHolder m_cPictureUnCheck; // uncheck bitmap holder
	CPictureHolder m_cPictureCheck; // check bitmap bolder
	
// private attributes
private:
	CModel*	m_pcModel;
	CParameter*	m_pcParameter;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PARAMETERGENERALGRID_H__662EF396_A623_11D3_B12F_0060084B410C__INCLUDED_)
