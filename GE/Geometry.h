/*--------------------------------------------------------------------------*/
/*							Geometry.h										*/
/*                            												*/
/*	Purpose	: Create geometry.                                        		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, Chapter 5.                 							*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOMETRY_H__F98F40A4_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
#define AFX_GEOMETRY_H__F98F40A4_7B81_11D4_B2F3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "Indexes.h"
#include "Model.h"
#include "ReadFile.h"
#endif // _MSC_VER > 1000

class CGeometry : virtual public CIndexes
{
// public operations
public:
	CGeometry(CModel* pcModel = NULL);
	virtual ~CGeometry();

// protected operations
protected:
	void CreatePointArray();

	// geometry
	void CreateNormalGeometry(int iLayer);
	void CreateNormalGeometryForLayer(int iLayer, int iLayerStartCellIndex = 0, int iLayerStartPointIndex = 0);
	void CreateAverageGeometry(int iLayer);
	void CreateNormalGeometryForAllLayers();
	void CreateAverageGeometryForAllLayers();
	void CreateMiddleGeometry(int iNumberOfPoints = 1);
	
	// get the float points
	vtkFloatPoints* GetFloatPoints() {return m_pcFloatPoints;};

// private operations
private:
	void CreateAveragePoints(int iLayer, int iLayerStartCellIndex = 0);
	void InsertNormalPoints(int iRowIndex, int iColumnIndex, float fZTopValue, float fZBottomValue, int iLayerStartPointIndex);
	void InsertAveragePoints(int iRowIndex, int iColumnIndex, float* pfTopArray, float* pfBottomArray);

// protected attributes
protected:
	// mininum and maximum value
	float m_fMinimumValue;
	float m_fMaximumValue;

	// vtk
	vtkScalars*	m_pcScalars;
	vtkFloatPoints*	m_pcFloatPoints;
};

#endif // !defined(AFX_GEOMETRY_H__F98F40A4_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
