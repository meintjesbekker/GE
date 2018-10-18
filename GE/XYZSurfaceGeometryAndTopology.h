/*--------------------------------------------------------------------------*/
/*						XYZSurfaceGeometryAndTopology.h						*/
/*                            												*/
/*	Purpose	: Create geometry and topology for XYZ Surface visualization	*/
/*			  object.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.5 "XYZ Surface".               				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACEGEOMETRYANDTOPOLOGY_H__E83F3E31_82F3_11D4_B304_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACEGEOMETRYANDTOPOLOGY_H__E83F3E31_82F3_11D4_B304_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Color.h"
#endif // _MSC_VER > 1000

class CXYZSurfaceGeometryAndTopology  
{
// public operations
public:
	CXYZSurfaceGeometryAndTopology();
	virtual ~CXYZSurfaceGeometryAndTopology();

// protected operations
protected:
	void CreateGeometryAndScalarDatasetAttribute(CString sPathName, CColor* pcColor);
	void Triangulate(vtkPolyData* pcPolyData);

// protected attributes
protected:
	float m_fMinimumValue;
	float m_fMaximumValue;

	// vtk
	vtkFloatPoints* m_pcFloatPoints;
	vtkScalars* m_pcScalars;
	vtkDelaunay2D* m_pcDelaunay2D;
};

#endif // !defined(AFX_XYZSURFACEGEOMETRYANDTOPOLOGY_H__E83F3E31_82F3_11D4_B304_0060084B410C__INCLUDED_)
