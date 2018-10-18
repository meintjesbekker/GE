/*--------------------------------------------------------------------------*/
/*								MT3DMSGUI.cpp								*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of the	*/
/*   		  Isosurface visualization objects.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6 "Isosurface".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CMT3DMSGUI::CMT3DMSGUI(CModel* pcModel /* = NULL */) : CClipPolyData(pcModel)
{
	// general page
	m_iSpecy = 1;
	m_piSpecies = NULL;
	m_iNumberOfSpecies = 0;
	m_iSpecyIndex = 0;
	m_dTotalElapsedTime = 0;
	m_pdTotalElapsedTimes = NULL;
	m_lNumberOfTimeIntervals = 0;
	m_iTotalElapsedTimeIndex = 0;

	// color and contour page
	m_fOpacity = 1;
	m_pMT3DMSContourAndColorTable = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction 				                                                */
/*--------------------------------------------------------------------------*/
CMT3DMSGUI::~CMT3DMSGUI()
{
	if (m_piSpecies) 
		delete [] m_piSpecies;
	if (m_pdTotalElapsedTimes) 
		delete [] m_pdTotalElapsedTimes;
	if (m_pMT3DMSContourAndColorTable) 
		delete m_pMT3DMSContourAndColorTable;
}