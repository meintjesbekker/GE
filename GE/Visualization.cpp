/*--------------------------------------------------------------------------*/
/*							Visualization.cpp								*/
/*                            												*/
/*	Purpose	: Contains visualization objects.                          		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Visualization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Implement Serial       													*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_SERIAL(CVisualization, CObject, 1);

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CVisualization::CVisualization()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CVisualization::~CVisualization()
{
	// visualization object
	for (int i = 0; i < m_pcVisualizationObjectArray.GetSize(); i++)
		delete m_pcVisualizationObjectArray[i];
	m_pcVisualizationObjectArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* CreateModelOutline                                                       */
/*--------------------------------------------------------------------------*/
int	CVisualization::CreateModelOutline(CModel* pcModel /* = NULL */)
{
	CModelOutline* pcModelOutline = new CModelOutline(pcModel);
	pcModelOutline->Create();
	return AddVisualizationObjectToArray(pcModelOutline);
}

/*--------------------------------------------------------------------------*/
/* GetVisualizationObject                                                   */
/*--------------------------------------------------------------------------*/
CVisualizationObject* CVisualization::GetVisualizationObject(int iIndex)
{
	return m_pcVisualizationObjectArray.GetAt(iIndex);
}

/*--------------------------------------------------------------------------*/
/* AddVisualizationObjectToArray                                            */
/*--------------------------------------------------------------------------*/
int CVisualization::AddVisualizationObjectToArray(CVisualizationObject* pcVisualizationObject)
{
	return m_pcVisualizationObjectArray.Add(pcVisualizationObject);
}

/*--------------------------------------------------------------------------*/
/* VisualizationExist                                                       */
/*--------------------------------------------------------------------------*/
BOOL CVisualization::VisualizationExist()
{
	if (m_pcVisualizationObjectArray.GetSize() > 0)
		return TRUE;
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* Clip                                                                     */
/*--------------------------------------------------------------------------*/
void CVisualization::Clip()
{
	// visualization objects
	for (int i = 0; i < m_pcVisualizationObjectArray.GetSize(); i++)
		m_pcVisualizationObjectArray[i]->Clip();
}

/*--------------------------------------------------------------------------*/
/* Serialize                                                                */
/*--------------------------------------------------------------------------*/
void CVisualization::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
}