/*--------------------------------------------------------------------------*/
/*						GeospatialModelForLayerGUI.cpp						*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for General and		*/
/*			  Visible page of GUI for Geospatial Model visualization		*/
/*			  object.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide 3.3 "Geospatial Model".							*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelForLayerGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CGeospatialModelForLayerGUI::CGeospatialModelForLayerGUI(CModel* pcModel /* = NULL */) 
	: CPolyData(pcModel), 
	  CDecimateSmoothGUI()
{
	m_bVisible = TRUE;
	m_cColor = RGB(0, 255, 0);
	m_fOpacity = 1.0;
	m_bVisibleTop = TRUE;
	m_bVisibleSides = TRUE;
	m_bVisibleBottom = TRUE;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CGeospatialModelForLayerGUI::~CGeospatialModelForLayerGUI()
{
}