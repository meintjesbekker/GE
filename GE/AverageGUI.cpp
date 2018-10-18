/*--------------------------------------------------------------------------*/
/*								AverageGUI.cpp              				*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for Average page of	*/
/*	          GUI, used by Geospatial Model, Potentiometric Surface,  		*/
/*	          XYZ Surface and Hydraulic Components visualization objects.   */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide sections 3.3.3, 3.4.2, 3.7.2 "Average",			*/
/*			  3.5.2 "Decimate and Smooth". 									*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "AverageGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                												*/
/*--------------------------------------------------------------------------*/
CAverageGUI::CAverageGUI()
{
	m_bAverage = TRUE;
}

/*--------------------------------------------------------------------------*/
/* Destruction                 												*/
/*--------------------------------------------------------------------------*/
CAverageGUI::~CAverageGUI()
{
}