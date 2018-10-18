/*--------------------------------------------------------------------------*/
/*							SidesQuadTopology.h								*/
/*                            												*/
/*	Purpose	: Create sides quad topology.									*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_SIDESQUADTOPOLOGY_H__0C8832B2_8874_11D4_B30E_0060084B410C__INCLUDED_)
#define AFX_SIDESQUADTOPOLOGY_H__0C8832B2_8874_11D4_B30E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "TopQuadTopology.h"
#endif // _MSC_VER > 1000

class CSidesQuadTopology : public CTopQuadTopology
{
// public operations
public:
	CSidesQuadTopology(CModel* pcModel = NULL);
	virtual ~CSidesQuadTopology();

// proctected operations
protected:
	// normal or average sides topology
	void CreateSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage);
	void CreateLeftSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex);
	void CreateRightSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex);
	void CreateBackSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex);
	void CreateFrontSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex);
};

#endif // !defined(AFX_SIDESQUADTOPOLOGY_H__0C8832B2_8874_11D4_B30E_0060084B410C__INCLUDED_)
