/*--------------------------------------------------------------------------*/
/*							XYZSurfaceGUI.h									*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of the	*/
/*   		  XYZSurface visualization object.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5 "XYZ Surface".        				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACEGUI_H__144E3952_7B22_11D4_B2F3_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACEGUI_H__144E3952_7B22_11D4_B2F3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Color.h"
#include "DecimateSmoothGUI.h"
#include "DecimateSmoothNormals.h"
#endif // _MSC_VER > 1000

class CXYZSurfaceGUI :	public CDecimateSmoothNormals,
						public CDecimateSmoothGUI
{
// public operations
public:
	CXYZSurfaceGUI(CModel* pcModel = NULL);
	virtual ~CXYZSurfaceGUI();

	// general page
	CString	GetFolderAndFileName() const {return m_sPathName;};
	void SetPathName(CString sPathName) {m_sPathName = sPathName;};

	// color page
	CColor* GetColorPointer() const {return m_pcColor;};

// protected attributes
protected:
	// general page
	CString	m_sPathName;
	
	// color page
	CColor*	m_pcColor;
};

#endif // !defined(AFX_XYZSURFACEGUI_H__144E3952_7B22_11D4_B2F3_0060084B410C__INCLUDED_)
