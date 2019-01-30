/*--------------------------------------------------------------------------*/
/*								TimeStep.cpp								*/
/*                            												*/
/*	Purpose	: Time step.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "TimeStep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction			 				                                    */
/*--------------------------------------------------------------------------*/
CTimeStep::CTimeStep()
{
	m_iTimeStep = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction            				                                    */
/*--------------------------------------------------------------------------*/
CTimeStep::~CTimeStep()
{
}

/*--------------------------------------------------------------------------*/
/* FindLayer   							                                    */
/*--------------------------------------------------------------------------*/
int CTimeStep::FindLayer(int iLayer)
{
	for (int i = 0; i < m_LayerArray.GetSize(); i++)
		if (m_LayerArray[i] == iLayer)
			return i;
	return -1;
}
