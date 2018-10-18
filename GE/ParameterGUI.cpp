/*--------------------------------------------------------------------------*/
/*							ParameterGUI.cpp  								*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of      */
/*			  Parameter visualization object.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8 "Parameter".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ParameterGUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CParameterGUI::CParameterGUI(CModel* pcModel /* = NULL */)
	: CClipPolyData(pcModel)
{
	m_bAverage = TRUE;
	m_pcColor = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
CParameterGUI::~CParameterGUI()
{
	if (m_pcColor)
		delete m_pcColor;
}