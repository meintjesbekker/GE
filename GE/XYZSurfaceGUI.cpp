/*--------------------------------------------------------------------------*/
/*							XYZSurfaceGUI.cpp								*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of the	*/
/*   		  XYZSurface visualization object.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5 "XYZ Surface".        				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZSurfaceGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CXYZSurfaceGUI::CXYZSurfaceGUI(CModel* pcModel /* = NULL */) 
	: CDecimateSmoothNormals(pcModel)
{
	// general page
	m_sPathName = _T("");

	// color page
	m_pcColor = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction				                                                */
/*--------------------------------------------------------------------------*/
CXYZSurfaceGUI::~CXYZSurfaceGUI()
{
	if (m_pcColor)
		delete m_pcColor;
}