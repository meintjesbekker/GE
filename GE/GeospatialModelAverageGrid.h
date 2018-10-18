/*--------------------------------------------------------------------------*/
/*						GeospatialModelAverageGrid.h   						*/
/*                            												*/
/*	Purpose	: Grid which contains average, decimate, reduction, smooth,     */
/*			  iterations and relaxation fields.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".          				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELAVERAGEGRID_H__ABCF6067_CE58_11D3_B167_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELAVERAGEGRID_H__ABCF6067_CE58_11D3_B167_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxctl.h>
#include <Afxtempl.h>
#include "GeospatialModel.h"
#include "GeospatialModelAverageGridRelaxationFactorEditBox.h"
#include "GeospatialModelAverageGridTargetReductionEditBox.h"
#include "IterationsEditBox.h"
#include "Model.h"
#include "MSFlexGrid.h"
#endif // _MSC_VER > 1000

class CGeospatialModelAverageGrid : public CMSFlexGrid
{
// public operations
public:
	CGeospatialModelAverageGrid();
	virtual ~CGeospatialModelAverageGrid();
	void SetModelPointer(CModel* pcModel) {m_pcModel = pcModel;};
	void SetGeospatialModelPointer(CGeospatialModel* pcGeospatialModel) {m_pcGeospatialModel = pcGeospatialModel;};
	void InitializeGrid();
	BOOL GetAverage(int iLayer) const {return m_bAverageArray[iLayer - 1];};
	void SetAverage(int iLayer, BOOL bAverage) {m_bAverageArray[iLayer - 1] = bAverage;};
	BOOL GetDecimate(int iLayer) const {return m_bDecimateArray[iLayer - 1];};
	void SetDecimate(int iLayer, BOOL bDecimate) {m_bDecimateArray[iLayer - 1] = bDecimate;};
	float GetTargetReduction(int iLayer) const {return m_fTargetReductionArray[iLayer - 1];};
	void SetTargetReduction(int iLayer, float fTargetReduction) {m_fTargetReductionArray[iLayer - 1] = fTargetReduction;};
	BOOL GetSmooth(int iLayer) const {return m_bSmoothArray[iLayer - 1];};
	void SetSmooth(int iLayer, BOOL bVisible) {m_bSmoothArray[iLayer - 1] = bVisible;};
	float GetIterations(int iLayer) const {return m_fIterationsArray[iLayer - 1];};
	void SetIterations(int iLayer, float fIterations) {m_fIterationsArray[iLayer - 1] = fIterations;};
	float GetRelaxationFactor(int iLayer) const {return m_fRelaxationFactorArray[iLayer - 1];};
	void SetRelaxationFactor(int iLayer, float fRelaxationFactor) {m_fRelaxationFactorArray[iLayer - 1] = fRelaxationFactor;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeospatialModelAverageGrid)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CGeospatialModelAverageGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
	afx_msg void OnDblClickGrid();
	afx_msg void OnLeaveCellGrid();
	DECLARE_EVENTSINK_MAP()

// private attributes
private:
	CModel* m_pcModel;
	CGeospatialModel* m_pcGeospatialModel;
	long m_lBorderWidth; 
	long m_lBorderHeight;
	int m_iNumberOfLogPixelsX;
	int m_iNumberOfLogPixelsY;
	CPictureHolder m_cPictureUnCheck; // uncheck bitmap holder
	CPictureHolder m_cPictureCheck; // check bitmap bolder
	CArray<BOOL, BOOL> m_bAverageArray;
	CArray<BOOL, BOOL> m_bDecimateArray;
	CArray<float, float> m_fTargetReductionArray;
	CGeospatialModelAverageGridTargetReductionEditBox m_cTargetReductionEdit;
	CArray<BOOL, BOOL> m_bSmoothArray;
	CArray<float, float> m_fIterationsArray;
	CArray<float, float> m_fRelaxationFactorArray;
	CIterationsEditBox m_cIterationsEdit;
	CGeospatialModelAverageGridRelaxationFactorEditBox m_cRelaxationFactorEdit;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GEOSPATIALMODELAVERAGEGRID_H__ABCF6067_CE58_11D3_B167_0060084B410C__INCLUDED_)
