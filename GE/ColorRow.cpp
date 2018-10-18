/*--------------------------------------------------------------------------*/
/*								ColorRow.cpp              					*/
/*                            												*/
/*	Purpose	: Color row in color table.                                  	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorRow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorRow::CColorRow()
{
	m_fMinimum = 0;
	m_fMaximum = 0;
	m_cColor = RGB(0, 255, 0);
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CColorRow::~CColorRow()
{
}