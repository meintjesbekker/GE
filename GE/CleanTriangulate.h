/*--------------------------------------------------------------------------*/
/*							CleanTriangulate.h   							*/
/*                            												*/
/*	Purpose	: Clean and triangulate polygonal data.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, sections 4.3.2.2.2 "Clean Polygonal Data" and			*/
/*			  4.3.2.2.11 "Triangulation".                      				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_CLEANTRIANGULATE_H__BD72A488_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_CLEANTRIANGULATE_H__BD72A488_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "DecimateSmoothNormals.h"
#endif // _MSC_VER > 1000

class CCleanTriangulate : public CDecimateSmoothNormals
{
// public operations
public:
	CCleanTriangulate(CModel* pcModel = NULL);
	virtual ~CCleanTriangulate();

// protected operations
protected:
	virtual void CleanPolygonalData(vtkPolyData* pcPolyData);
	virtual void Triangulate(BOOL bAverage);

// protected attributes
protected:
	vtkCleanPolyData* m_pcCleanPolyData;
	vtkTriangleFilter* m_pcTriangleFilter;
};

#endif // !defined(AFX_CLEANTRIANGULATE_H__BD72A488_798C_11D4_B2EF_0060084B410C__INCLUDED_)
