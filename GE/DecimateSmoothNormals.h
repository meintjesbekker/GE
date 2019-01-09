/*--------------------------------------------------------------------------*/
/*							DecimateSmoothNormals.h   						*/
/*                            												*/
/*	Purpose	: Decimate, smooth and calculate normals for polygonal data.	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, sections 4.3.2.2.5 "Decimation",       				*/
/*			  4.3.2.2.10 "Smooth Polygonal Data" and						*/
/*  		  4.3.2.2.9 "Polygonal Data Normals"							*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_DECIMATESMOOTHNORMALS_H__BD72A487_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_DECIMATESMOOTHNORMALS_H__BD72A487_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ClipPolyData.h"
#endif // _MSC_VER > 1000

class CDecimateSmoothNormals : public CClipPolyData  
{
// public operations
public:
	CDecimateSmoothNormals(CModel* pcModel = NULL);
	virtual ~CDecimateSmoothNormals();

// protected operations
protected:
	virtual void Decimate(vtkAlgorithmOutput* pcPolyData, BOOL bDecimate, float fTargetReduction);
	virtual void SmoothPolyData(vtkAlgorithmOutput* pcPolyData, BOOL bSmooth, BOOL bDecimate, int iNumberOfIterations, float fRelaxationFactor);
	virtual void ComputePolyDataNormals(vtkAlgorithmOutput* pcPolyData, vtkAlgorithmOutput* pcCleanPolyData, BOOL bSmooth, BOOL bDecimate, BOOL bAverage);

// protected attributes
protected:
	// vtk
	vtkDecimatePro*	m_pcDecimatePro;
	vtkSmoothPolyDataFilter* m_pcSmoothPolyDataFilter;
	vtkPolyDataNormals*	m_pcPolyDataNormals;
};

#endif // !defined(AFX_DECIMATESMOOTHNORMALS_H__BD72A487_798C_11D4_B2EF_0060084B410C__INCLUDED_)
