/*--------------------------------------------------------------------------*/
/*							CleanTriangulate.cpp 							*/
/*                            												*/
/*	Purpose	: Clean and triangulate polygonal data.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, sections 4.3.2.2.2 "Clean Polygonal Data" and			*/
/*			  4.3.2.2.11 "Triangulation".                      				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "CleanTriangulate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CCleanTriangulate::CCleanTriangulate(CModel* pcModel /* = NULL */) 
	: CDecimateSmoothNormals(pcModel)
{
	// vtk
	m_pcCleanPolyData = NULL;
	m_pcTriangleFilter = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction            													*/
/*--------------------------------------------------------------------------*/
CCleanTriangulate::~CCleanTriangulate()
{
	if (m_pcCleanPolyData)
		m_pcCleanPolyData->Delete();
	if (m_pcTriangleFilter)
		m_pcTriangleFilter->Delete();
}

/*--------------------------------------------------------------------------*/
/* CleanPolygonalData                                                       */
/*--------------------------------------------------------------------------*/
void CCleanTriangulate::CleanPolygonalData(vtkPolyData* pcPolyData)
{
	if (m_pcCleanPolyData) 
		m_pcCleanPolyData->Delete();
  	m_pcCleanPolyData = vtkCleanPolyData::New();
	m_pcCleanPolyData->SetInput(pcPolyData);
	m_pcCleanPolyData->Update();
}

/*--------------------------------------------------------------------------*/
/* Triangulate                                                              */
/*--------------------------------------------------------------------------*/
void CCleanTriangulate::Triangulate(BOOL bAverage)
{
	if (bAverage)
	{
		if (m_pcTriangleFilter) 
			m_pcTriangleFilter->Delete();
		m_pcTriangleFilter = vtkTriangleFilter::New();
		m_pcTriangleFilter->SetInput(m_pcCleanPolyData->GetOutput());
		m_pcTriangleFilter->Update();
	}
}