/*--------------------------------------------------------------------------*/
/*						HydraulicComponentGUI.cpp							*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages			*/
/*			  of Hydraulic Components visualization object.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7 "Hydraulic Components".             */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction							                                    */
/*--------------------------------------------------------------------------*/
CHydraulicComponentGUI::CHydraulicComponentGUI(CModel* pcModel /* = NULL */) 
	: CClipPolyData(pcModel),
	  CAverageGUI()
{
	m_sDescription = "";
	m_bVisible = TRUE;
	m_cColor = RGB(0, 0, 255);	
}

/*--------------------------------------------------------------------------*/
/* Destruction							                                    */
/*--------------------------------------------------------------------------*/
CHydraulicComponentGUI::~CHydraulicComponentGUI()
{
}