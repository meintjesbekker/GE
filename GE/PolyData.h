/*--------------------------------------------------------------------------*/
/*								PolyData.h   								*/
/*                            												*/
/*	Purpose	: Create polygonal data, from geometry, topology and			*/
/*	       	: scalars if it is defined.										*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".                 */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POLYDATA_H__BD72A489_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_POLYDATA_H__BD72A489_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "CleanTriangulate.h"
#endif // _MSC_VER > 1000

class CPolyData : public CCleanTriangulate
{
public:
	CPolyData(CModel* pcModel = NULL);
	virtual ~CPolyData();

// protected operations
protected:
	virtual void CreatePolyData(vtkFloatPoints* pcFloatPoints, vtkCellArray* pcCellArray, vtkScalars* pcScalars = NULL);

// protected attribute
protected:
	// vtk
	vtkPolyData* m_pcPolyData;
};

#endif // !defined(AFX_POLYDATA_H__BD72A489_798C_11D4_B2EF_0060084B410C__INCLUDED_)
