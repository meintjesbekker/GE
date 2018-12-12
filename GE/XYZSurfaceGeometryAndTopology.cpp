/*--------------------------------------------------------------------------*/
/*						XYZSurfaceGeometryAndTopology.cpp					*/
/*                            												*/
/*	Purpose	: Create geometry and topology for XYZ Surface visualization	*/
/*			  object.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.5 "XYZ Surface".               				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZSurfaceGeometryAndTopology.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CXYZSurfaceGeometryAndTopology::CXYZSurfaceGeometryAndTopology()
{
	m_fMinimumValue = 0;
	m_fMaximumValue = 0;

	// vtk
	m_pcFloatPoints = NULL;
	m_pcScalars = NULL;
	m_pcDelaunay2D = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction 																*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceGeometryAndTopology::~CXYZSurfaceGeometryAndTopology()
{
	if (m_pcFloatPoints)
		m_pcFloatPoints->Delete();
	if (m_pcScalars) 
		m_pcScalars->Delete();
	if (m_pcDelaunay2D)	
		m_pcDelaunay2D->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateGeometryAndScalarDatasetAttribute									*/
/*--------------------------------------------------------------------------*/
void CXYZSurfaceGeometryAndTopology::CreateGeometryAndScalarDatasetAttribute(CString sPathName, CColor* pcColor)
{
	// Create a point array.
	if (m_pcFloatPoints) 
		m_pcFloatPoints->Delete();
	m_pcFloatPoints = vtkPoints::New();
	
	// Create a scalar array.
	if (m_pcScalars) 
		m_pcScalars->Delete();
	m_pcScalars = vtkDoubleArray::New();
	
	ifstream waterLevelFile(sPathName, ios::in);
	float xyz[3];
	
	// While not end of file.
	while (!waterLevelFile.eof())
	{
		// Read x, y and z coordinate from file.
		waterLevelFile >> xyz[0] >> xyz[1] >> xyz[2];

		// If z coordinate is in Color Table range.
		if (xyz[2] >= pcColor->m_cColorTable.GetMinimumScalarValue() 
			&& xyz[2] <= pcColor->m_cColorTable.GetMaximumScalarValue())
		{
			// Insert x, y and z coordinate as a point into point array.
			m_pcFloatPoints->InsertNextPoint(xyz);
			
			// Insert z coordinate as a scalar into scalar array.
			m_pcScalars->InsertNextValue(xyz[2]);
		}
	}
	waterLevelFile.close();
}

/*--------------------------------------------------------------------------*/
/* Triangulate                                                              */
/*--------------------------------------------------------------------------*/
void CXYZSurfaceGeometryAndTopology::Triangulate(vtkPolyData* pcPolyData)
{
	if (m_pcDelaunay2D) 
		m_pcDelaunay2D->Delete();
	m_pcDelaunay2D = vtkDelaunay2D::New();
	m_pcDelaunay2D->SetInputData(pcPolyData);
	m_pcDelaunay2D->Update();
}