/*--------------------------------------------------------------------------*/
/*								PolyData.cpp 								*/
/*                            												*/
/*	Purpose	: Create polygonal data, from geometry, topology and			*/
/*	       	: scalars if it is defined.										*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".                 */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "PolyData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CPolyData::CPolyData(CModel* pcModel /* = NULL */) : CCleanTriangulate(pcModel)
{
	// vtk
	m_pcPolyData = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CPolyData::~CPolyData()
{
	// Delete member function has to be used for vtk objects.
	if (m_pcPolyData)
		m_pcPolyData->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreatePolyData                                                           */
/*--------------------------------------------------------------------------*/
void CPolyData::CreatePolyData(vtkPoints* pcFloatPoints, vtkCellArray* pcCellArray,  vtkDoubleArray* pcScalars /* = NULL */)
{
	if (m_pcPolyData) 
		m_pcPolyData->Delete();
	m_pcPolyData = vtkPolyData::New();
	m_pcPolyData->SetPoints(pcFloatPoints);
	m_pcPolyData->SetPolys(pcCellArray);
	if (pcScalars)
		m_pcPolyData->GetPointData()->SetScalars(pcScalars);
	m_pcPolyData->Modified();
}