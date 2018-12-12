// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__2893D377_BC03_11D2_B7A5_0060084B410C__INCLUDED_)
#define AFX_STDAFX_H__2893D377_BC03_11D2_B7A5_0060084B410C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
#include "vtkActor.h"
#include "vtkActorCollection.h"
#include "vtkAppendPolyData.h"
#include "vtkAxes.h"
#include "vtkAxisActor2D.h"
#include "vtkCellArray.h"
#include "vtkCleanPolyData.h"
#include "vtkClipPolyData.h"
#include "vtkContourFilter.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkDataSetMapper.h"
#include "vtkDecimatePro.h"
#include "vtkDelaunay2D.h"
#include "vtkPoints.h"
#include "vtkDoubleArray.h"
#include "vtkGeometryFilter.h"
#include "vtkLODActor.h"
#include "vtkLookupTable.h"
#include "vtkOpenGLRenderer.h"
#include "vtkOutlineFilter.h"
#include "vtkOutlineSource.h"
#include "vtkPlane.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataNormals.h"
#include "vtkProp3D.h"
#include "vtkPropCollection.h"
#include "vtkWin32OpenGLRenderWindow.h"
//#include "vtkScalars.h"
#include "vtkProperty.h"
#include "vtkCellData.h"
#include "vtkPointData.h"
#include "vtkProperty2D.h"
#include "vtkCamera.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkStructuredGrid.h"
#include "vtkTriangleFilter.h"
#include "vtkTubeFilter.h"
#include "vtkUnstructuredGrid.h"
#include "vtkVRMLExporter.h"
#include "vtkWin32RenderWindowInteractor.h"

typedef enum parametertype
{
	EMPTYPARAMETER,
	HORIZONTAL_HYDRAULIC_CONDUCTIVITY,
	VERTICAL_HYDRAULIC_CONDUCTIVITY,
	SPECIFIC_STORAGE,
	TRANSMISSIVITY,
	VERTICAL_LEAKANCE,
	STORAGE_COEFFICIENT,
	EFFECTIVE_POROSITY,
	SPECIFIC_YIELD
} PARAMETERTYPE;

typedef enum hydrauliccomponenttype
{
	EMPTYHYDRAULICCOMPONENT,
	FIXED_CONCENTRATION,
	FIXED_HEADS,
	HORIZONTAL_FLOW_BARRIER,
	RESERVOIR,
	DISCHARGE_WELL,
	DRAIN,
	GENERAL_HEAD_BOUNDARY,
	RECHARGE_WELL,
	RIVER,
	TIME_VARIANT_SPECIFIED_CONCENTRATION,
	TIME_VARIANT_SPECIFIED_HEAD
} HYDRAULICCOMPONENTTYPE;

// constants
const int iN_CELL_POINTS = 8;
const int iN_EDGE_POINTS = 2;
const int iN_POINTS = 4;

#endif // !defined(AFX_STDAFX_H__2893D377_BC03_11D2_B7A5_0060084B410C__INCLUDED_)