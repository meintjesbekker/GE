/*--------------------------------------------------------------------------*/
/*								ClipPolyData.h   							*/
/*                            												*/
/*	Purpose	: Clip polygonal data with plane.                           	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.3.2.2.3 "Clip Polygonal Data". 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_CLIPPOLYDATA_H__BD72A486_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_CLIPPOLYDATA_H__BD72A486_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Mapper.h"
#endif // _MSC_VER > 1000

class CClipPolyData : public CMapper
{
// public operations
public:
	CClipPolyData(CModel* pcModel = NULL);
	virtual ~CClipPolyData();

// protected operations
protected:
	virtual void DoClipPolyData(vtkAlgorithmOutput* pcPolyData);

// protected attributes
protected:
	// vtk
	vtkPlane* m_pcPlane;
	vtkClipPolyData* m_pcClipPolyData;
};

#endif // !defined(AFX_CLIPPOLYDATA_H__BD72A486_798C_11D4_B2EF_0060084B410C__INCLUDED_)
