/*--------------------------------------------------------------------------*/
/*								StressPeriod.cpp							*/
/*                            												*/
/*	Purpose	: Stress period with time steps for each stress period.			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "StressPeriod.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CStressPeriod::CStressPeriod()
{
	m_iStressPeriod = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CStressPeriod::~CStressPeriod()
{
	for (int i = 0; i < m_pcTimeStepArray.GetSize(); i++)
		delete m_pcTimeStepArray[i];
	m_pcTimeStepArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* GetTimeStep                                                              */
/*--------------------------------------------------------------------------*/
CTimeStep* CStressPeriod::GetTimeStep(int iTimeStep)
{
	for (int i = 0; i < m_pcTimeStepArray.GetSize(); i++)
		if (m_pcTimeStepArray[i]->GetTimeStep() == iTimeStep)
			return m_pcTimeStepArray[i];
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* FindTimeStep                                                             */
/*--------------------------------------------------------------------------*/
int CStressPeriod::FindTimeStep(int iTimeStep)
{
	for (int i = 0; i < m_pcTimeStepArray.GetSize(); i++)
	if (m_pcTimeStepArray[i]->GetTimeStep() == iTimeStep)
		return i;
	return -1;
}

/*--------------------------------------------------------------------------*/
/* AddTimeStep                                                              */
/*--------------------------------------------------------------------------*/
void CStressPeriod::AddTimeStep(int iTimeStep, int iLayer)
{	
	CTimeStep* newTimeStep = new CTimeStep();
	newTimeStep->SetTimeStep(iTimeStep);
	newTimeStep->AddLayer(iLayer);
	m_pcTimeStepArray.Add(newTimeStep);
}