/*--------------------------------------------------------------------------*/
/*								Color.h   									*/
/*                            												*/
/*	Purpose	: Handle color table and opacity.			                    */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLOR_H__B2965653_D483_11D3_B174_0060084B410C__INCLUDED_)
#define AFX_COLOR_H__B2965653_D483_11D3_B174_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxtempl.h>
#include "ColorTable.h"
#endif // _MSC_VER > 1000

class CColor  
{
// public operations
public:
	CColor();
	virtual ~CColor();
	float GetOpacity() const {return m_fOpacity;};
	void SetOpacity(float fOpacity) {m_fOpacity = fOpacity;};

// public attributes
public:
	CColorTable m_cColorTable;

// private attributes
private:
	float m_fOpacity;
};

#endif // !defined(AFX_COLOR_H__B2965653_D483_11D3_B174_0060084B410C__INCLUDED_)
