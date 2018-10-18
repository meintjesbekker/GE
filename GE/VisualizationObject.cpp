/*--------------------------------------------------------------------------*/
/*						VisualizationObject.cpp								*/
/*                            												*/
/*	Purpose	: Class used for polymorphism. CVisualization contains an arry	*/
/*			  of this class.												*/	
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "VisualizationObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Implement Serial       													*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_SERIAL(CVisualizationObject, CObject, 1);

/*--------------------------------------------------------------------------*/
/* Construction           													*/
/*--------------------------------------------------------------------------*/
CVisualizationObject::CVisualizationObject()
{
	m_bVisible = TRUE;
	m_sDescription = _T("");
	m_pActorCollection = vtkActorCollection::New();
}

/*--------------------------------------------------------------------------*/
/* Destruction            													*/
/*--------------------------------------------------------------------------*/
CVisualizationObject::~CVisualizationObject()
{
	if (m_pActorCollection)
		m_pActorCollection->Delete();
}

/*--------------------------------------------------------------------------*/
/* Serialize               													*/
/*--------------------------------------------------------------------------*/
void CVisualizationObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
}