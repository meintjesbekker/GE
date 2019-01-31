/*--------------------------------------------------------------------------*/
/*						PotentiometricSurfaceGUI.cpp  						*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of      */
/*			  Potentiometric visualization object.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4 "Potentiometric Surface".           */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "PotentiometricSurfaceGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction               												*/
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceGUI::CPotentiometricSurfaceGUI(CModel* pcModel /* = NULL */) 
	: CPolyData(pcModel),
	  CDecimateSmoothGUI()
{
	// general page
	m_iStressPeriod = 1;
	m_iTimeStep = 1;
	m_bUseHighestHeads = TRUE;
	m_iLayer = 1;

	// color page
	m_pcColor = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction              												*/
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceGUI::~CPotentiometricSurfaceGUI()
{
	if (m_pcColor)
		delete [] m_pcColor;
}