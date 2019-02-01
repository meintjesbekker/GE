/*--------------------------------------------------------------------------*/
/*								QuadIndexes.cpp 							*/
/*                            												*/
/*	Purpose	: Point indexes for quadrilateral.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".                       */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "QuadIndexes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                 											*/
/*--------------------------------------------------------------------------*/
CQuadIndexes::CQuadIndexes()
{
	// TODO: Not necassary anymore for done in header.
	//for (int i = 0; i < iN_POINTS; i++)
	//	iP[i] = 0;
}

/*--------------------------------------------------------------------------*/
/* Desctruction                 											*/
/*--------------------------------------------------------------------------*/
CQuadIndexes::~CQuadIndexes()
{
}
