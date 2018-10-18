/*--------------------------------------------------------------------------*/
/*							DecimateSmoothGUI.cpp							*/
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
#include "stdafx.h"
#include "GE.h"
#include "DecimateSmoothGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction       				                                        */
/*--------------------------------------------------------------------------*/
CDecimateSmoothGUI::CDecimateSmoothGUI() : CAverageGUI()
{
	m_bDecimate = FALSE;
	m_fTargetReduction = 0.5;
	m_bSmooth = FALSE;
	m_iNumberOfIterations = 10;
	m_fRelaxationFactor = 0.05;
}

/*--------------------------------------------------------------------------*/
/* Destruction						                                        */
/*--------------------------------------------------------------------------*/
CDecimateSmoothGUI::~CDecimateSmoothGUI()
{
}