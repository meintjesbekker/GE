/*--------------------------------------------------------------------------*/
/*						PotentiometricSurfaceGUI.h    						*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of      */
/*			  Potentiometric visualization object.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4 "Potentiometric Surface".           */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POTENTIOMETRICSURFACEGUI_H__BCB5A2D1_779E_11D4_B2E9_0060084B410C__INCLUDED_)
#define AFX_POTENTIOMETRICSURFACEGUI_H__BCB5A2D1_779E_11D4_B2E9_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "DecimateSmoothGUI.h"
#include "Color.h"
#include "PolyData.h"
#endif // _MSC_VER > 1000

class CPotentiometricSurfaceGUI : public CPolyData,
								  public CDecimateSmoothGUI
{
public:
	CPotentiometricSurfaceGUI(CModel* pcModel = NULL);
	virtual ~CPotentiometricSurfaceGUI();

	// general page
	int GetStressPeriod() const {return m_iStressPeriod;};
	void SetStressPeriod(int iStressPeriod) {m_iStressPeriod = iStressPeriod;};
	int GetTimeStep() const {return m_iTimeStep;};
	void SetTimeStep(int iTimeStep) {m_iTimeStep = iTimeStep;};
	BOOL GetUseHighestHeads() const {return m_bUseHighestHeads;};
	void SetUseHighestHeads(BOOL bUseHighestHeads) {m_bUseHighestHeads = bUseHighestHeads;};
	int GetLayer() const {return m_iLayer;};
	void SetLayer(int iLayer) {m_iLayer = iLayer;};

	// color page
	CColor*	GetColorPointer() const {return m_pcColor;};

protected:
	// general page
	int m_iStressPeriod;
	int m_iTimeStep;
	BOOL m_bUseHighestHeads;
	int m_iLayer;

	// color page
	CColor* m_pcColor;
};

#endif // !defined(AFX_POTENTIOMETRICSURFACEGUI_H__BCB5A2D1_779E_11D4_B2E9_0060084B410C__INCLUDED_)
