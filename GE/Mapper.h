/*--------------------------------------------------------------------------*/
/*								Mapper.h   									*/
/*                            												*/
/*	Purpose	: Create mapper.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.8 "Mapper".                               */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MAPPER_H__BD72A483_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_MAPPER_H__BD72A483_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Actor.h"
#endif // _MSC_VER > 1000

class CMapper : public CActor  
{
// public operations
public:
	CMapper(CModel* pcModel = NULL);
	virtual ~CMapper();

// protected operations
protected:
	virtual void CreateDataSetMapper(vtkDataSet* pcDataSet, vtkLookupTable* pcLookupTable = NULL, float fMinimum = 0, float fMaximum = 0);
	virtual void CreateMapper(vtkAlgorithmOutput* pcPolyData, vtkLookupTable* pcLookupTable = NULL, float fMinimum = 0, float fMaximum = 0);

// protected attributes
protected:
	// vtk
	vtkDataSetMapper* m_pcDataSetMapper;
	vtkPolyDataMapper* m_pcPolyDataMapper;
};

#endif // !defined(AFX_MAPPER_H__BD72A483_798C_11D4_B2EF_0060084B410C__INCLUDED_)
