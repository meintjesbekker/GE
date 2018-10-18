/*--------------------------------------------------------------------------*/
/*							XYZSurface.h									*/
/*                            												*/
/*	Purpose	: Create 2D Delaunay triangulation of input points.             */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.5 "XYZ Surface".               				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZSURFACE_H__9594B751_579D_11D3_B81E_0060084B410C__INCLUDED_)
#define AFX_XYZSURFACE_H__9594B751_579D_11D3_B81E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#include "Color.h"
#include "LookupTable.h"
#include "VisualizationObject.h"
#include "XYZSurfaceGeometryAndTopology.h"
#include "XYZSurfaceGUI.h"
#endif // _MSC_VER > 1000

class CXYZSurface : public CXYZSurfaceGUI,
					public CXYZSurfaceGeometryAndTopology,
					public CVisualizationObject
{
// public operations
public:
	CXYZSurface(CModel* pcModel = NULL);
	virtual ~CXYZSurface();

	// create, update, clip
	virtual void Create();
	virtual void Update();
	virtual void Clip();

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();

// private operations
private:
	void CreateMinimumMaximumElevationFromFile();
	void CreateDataSet();
	void CreateColor();
	void CreateLookupTable();
	void CreateMapper();
	void CreateActor();

// private attributes
private:
	// vtk
	vtkPolyData* m_pcPolyData;
	CLookupTable* m_pcLookupTable;
};

#endif // !defined(AFX_XYZSURFACE_H__9594B751_579D_11D3_B81E_0060084B410C__INCLUDED_)