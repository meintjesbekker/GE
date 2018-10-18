/*--------------------------------------------------------------------------*/
/*							TopQuadTopology.h								*/
/*                            												*/
/*	Purpose	: Create top quad topology.                               		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_TOPQUADTOPOLOGY_H__F98F40A1_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
#define AFX_TOPQUADTOPOLOGY_H__F98F40A1_7B81_11D4_B2F3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "Indexes.h"
#include "Model.h"
#include "ReadFile.h"
#include "QuadIndexes.h"
#endif // _MSC_VER > 1000

class CTopQuadTopology : virtual public CIndexes
{
// private operations
public:
	CTopQuadTopology(CModel* pcModel = NULL);
	virtual ~CTopQuadTopology();

// proctected operations
protected:

	// normal top or bottom topology
	void CreateNormalTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iNumberOfNormalLayerPoints = 0); // 0 for top topology
	void CreateNormalRightVerticalTopology(vtkCellArray* pcCellArray, int iNumberOfNormalLayerPoints = 0); // 0 for top topology
	void CreateNormalFrontVerticalTopology(vtkCellArray* pcCellArray, int iNumberOfNormalLayerPoints = 0); // 0 for top topology

	// normal or average horizontal topology
	void CreateHorizontalTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iNumberOfNormalLayerPoints = 0); // 0 for top topology

	// insert next cell
	void InsertNextCell(vtkCellArray* pcCellArray, CQuadIndexes cQuadIndexes);

// protected attributes
protected:
	// vtk
	vtkCellArray* m_pcCellArray;
};

#endif // !defined(AFX_TOPQUADTOPOLOGY_H__F98F40A1_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
