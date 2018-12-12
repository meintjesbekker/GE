/*--------------------------------------------------------------------------*/
/*							HydraulicComponents.cpp							*/
/*                            												*/
/*	Purpose	: Create Hydraulic Components.                                  */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorPage.h"
#include "HydraulicComponents.h"
#include "HydraulicComponentsSheet.h"
#include "HydraulicComponentsGeneralPage.h"
#include "HydraulicComponentsGeneralPageTD.h"
#include "HydraulicComponentsAveragePage.h"
#include "ReadFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponents::CHydraulicComponents(CModel* pcModel /* = NULL */)  
	: CVisualizationObject()
{
	m_pcModel = pcModel;
	SetDescription(_T("Hydraulic Components"));
	m_bVisible = TRUE;
	m_bAverage = TRUE;
	m_iStressPeriod = 1;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponents::~CHydraulicComponents()
{
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		delete m_pcHydraulicComponentArray[i];
	m_pcHydraulicComponentArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* SetAverage                                                               */
/*--------------------------------------------------------------------------*/
void CHydraulicComponents::SetAverage(BOOL bAverage)
{
	m_bAverage = bAverage;
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		m_pcHydraulicComponentArray[i]->SetAverage(m_bAverage);
}

/*--------------------------------------------------------------------------*/
/* ReadTimeParameterFile                                                    */
/*--------------------------------------------------------------------------*/
void CHydraulicComponents::ReadTimeParameterFile()
{
	FILE* pFile;
	pFile = fopen(m_pcModel->GetFolderAndFileName().SpanExcluding(".") + ".trn", "r");
	CString str;
	if (!pFile)
	{
		str.Format("Can not open the time parameter file.");
		AfxMessageBox(str);		
	}
	else
	{
		int iThousandHeader;
		int iTimeUnit;
		fscanf(pFile, "%i %i", &iThousandHeader, &iTimeUnit); 
		int iActive; // active, -1 stress period in use, 1 not used
		int iLength; // length
		int iTimeSteps; // time steps
		int iMultiplier; // multiplier (flow)
		int iTransport; // transport stepsize
		int iMax; // max. no. of transport steps
		int iMultiplierTransport; // multiplier (transport)
		m_iNumberOfStressPeriods = 0;
		for (int i = 1; i <= 1000; i++)
		{
			fscanf(pFile, "%i %i %i %i %i %i %i", &iActive, &iLength, &iTimeSteps, &iMultiplier, &iTransport, &iMax, &iMultiplierTransport);
			if (iActive == -1) // stress period in use
				m_iNumberOfStressPeriods += 1;
		}
		fclose(pFile);
	}
}

/*--------------------------------------------------------------------------*/
/* Clip                                                                     */
/*--------------------------------------------------------------------------*/
void CHydraulicComponents::Clip()
{
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		m_pcHydraulicComponentArray[i]->Clip();
	RemoveActors();
	for (int i = 0; i < m_pcHydraulicComponentArray.GetSize(); i++)
		AddActor(m_pcHydraulicComponentArray[i]->GetLODActor());
}