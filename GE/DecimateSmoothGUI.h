/*--------------------------------------------------------------------------*/
/*							DecimateSmoothGUI.h								*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for Decimate and		*/
/*			  Smooth GUI page.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, sections 3.3.3 "Average" and					*/
/*			  3.5.2 "Decimate and Smooth"                                   */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_DECIMATESMOOTHGUI_H__144E3951_7B22_11D4_B2F3_0060084B410C__INCLUDED_)
#define AFX_DECIMATESMOOTHGUI_H__144E3951_7B22_11D4_B2F3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "AverageGUI.h"
#endif // _MSC_VER > 1000

class CDecimateSmoothGUI : public CAverageGUI
{
// public operations
public:
	CDecimateSmoothGUI();
	virtual ~CDecimateSmoothGUI();

	// decimate and smooth page
	BOOL GetDecimate() const {return m_bDecimate;};
	void SetDecimate(BOOL bDecimate) {m_bDecimate = bDecimate;};
	float GetTargetReduction() const {return m_fTargetReduction;};
	void SetTargetReduction(float fTargetReduction) {m_fTargetReduction = fTargetReduction;};
	BOOL GetSmooth() const {return m_bSmooth;};
	void SetSmooth(BOOL bSmooth) {m_bSmooth = bSmooth;};
	int GetNumberOfIterations() const {return m_iNumberOfIterations;};
	void SetNumberOfIterations(int iNumberOfIterations) {m_iNumberOfIterations = iNumberOfIterations;};
	float GetRelaxationFactor() const {return m_fRelaxationFactor;};
	void SetRelaxationFactor(float fRelaxationFactor) {m_fRelaxationFactor = fRelaxationFactor;};

// protected attributes
protected:
	BOOL m_bDecimate;
	float m_fTargetReduction;
	BOOL m_bSmooth;
	int m_iNumberOfIterations;
	float m_fRelaxationFactor;
};

#endif // !defined(AFX_DECIMATESMOOTHGUI_H__144E3951_7B22_11D4_B2F3_0060084B410C__INCLUDED_)
