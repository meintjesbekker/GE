/*--------------------------------------------------------------------------*/
/*								Average.cpp    								*/
/*                            												*/
/*	Purpose	: Used to calculate average of number of values added.        	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model". Figure 5.8.          	*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Average.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CAverage::CAverage()
{
	m_Summation = 0;
	m_NumberOfValues = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction 				                                                */
/*--------------------------------------------------------------------------*/
CAverage::~CAverage()
{
}

/*--------------------------------------------------------------------------*/
/* AddToSum    				                                                */
/*--------------------------------------------------------------------------*/
void CAverage::AddToSum(float value)
{
	m_Summation += value;
	m_NumberOfValues += 1;
}

/*--------------------------------------------------------------------------*/
/* GetAverage  				                                                */
/*--------------------------------------------------------------------------*/
float CAverage::GetAverage()
{
	return (m_NumberOfValues > 0) ? (m_Summation / m_NumberOfValues) : 0;
}