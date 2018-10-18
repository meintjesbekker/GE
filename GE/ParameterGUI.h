/*--------------------------------------------------------------------------*/
/*							ParameterGUI.h    								*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of      */
/*			  Parameter visualization object.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8 "Parameter".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETERGUI_H__97024741_7F67_11D4_B2FE_0060084B410C__INCLUDED_)
#define AFX_PARAMETERGUI_H__97024741_7F67_11D4_B2FE_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ClipPolyData.h"
#include "Color.h"
#include "Model.h"
#endif // _MSC_VER > 1000

class CParameterGUI : public CClipPolyData
{
// public operations
public:
	CParameterGUI(CModel* pcModel = NULL);
	virtual ~CParameterGUI();

	// average page
	BOOL GetAverage() const {return m_bAverage;};
	void SetAverage(BOOL bAverage) {m_bAverage = bAverage;};

	// color page
	CColor*	GetColorPointer() const {return m_pcColor;};

// protected attributes
protected:
	// average page
	BOOL m_bAverage;

	// color page
	CColor* m_pcColor;
};

#endif // !defined(AFX_PARAMETERGUI_H__97024741_7F67_11D4_B2FE_0060084B410C__INCLUDED_)