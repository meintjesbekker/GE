/*--------------------------------------------------------------------------*/
/*						TimeAndLayerParameter.cpp							*/
/*                            												*/
/*	Purpose	: Handles stress periods for layers.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "TimeAndLayerParameter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CTimeAndLayerParameter::CTimeAndLayerParameter()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction 				                                                */
/*--------------------------------------------------------------------------*/
CTimeAndLayerParameter::~CTimeAndLayerParameter()
{
	for (int i = 0; i < m_pcStressPeriodArray.GetSize(); i++)
		delete m_pcStressPeriodArray[i];
	m_pcStressPeriodArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* GetStressPeriod			                                                */
/*--------------------------------------------------------------------------*/
CStressPeriod* CTimeAndLayerParameter::GetStressPeriod(int iStressPeriod)
{
	for (int i = 0; i < m_pcStressPeriodArray.GetSize(); i++)
		if (m_pcStressPeriodArray[i]->GetStressPeriod() == iStressPeriod)
			return m_pcStressPeriodArray[i];
	return NULL;
}

/*--------------------------------------------------------------------------*/
/* FindStressPeriod															*/
/*--------------------------------------------------------------------------*/
int CTimeAndLayerParameter::FindStressPeriod(int iStressPeriod)
{
	for (int i = 0; i < m_pcStressPeriodArray.GetSize(); i++)
		if (m_pcStressPeriodArray[i]->GetStressPeriod() == iStressPeriod)
			return i;
	return -1;
}

/*--------------------------------------------------------------------------*/
/* AddStressPeriod			                                                */
/*--------------------------------------------------------------------------*/
void CTimeAndLayerParameter::AddStressPeriod(int iStressPeriod, int iTimeStep, int iLayer)
{
	CStressPeriod* newStressPeriod = new CStressPeriod();
	newStressPeriod->SetStressPeriod(iStressPeriod);
	newStressPeriod->AddTimeStep(iTimeStep, iLayer);
	
	m_pcStressPeriodArray.Add(newStressPeriod);
}
