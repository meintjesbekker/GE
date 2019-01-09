/*--------------------------------------------------------------------------*/
/*							DecimateSmoothNormals.cpp 						*/
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
#include "stdafx.h"
#include "GE.h"
#include "DecimateSmoothNormals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CDecimateSmoothNormals::CDecimateSmoothNormals(CModel* pcModel /* = NULL */) 
	: CClipPolyData(pcModel)
{
	// vtk
	m_pcDecimatePro = NULL;
	m_pcSmoothPolyDataFilter = NULL;
	m_pcPolyDataNormals = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction            													*/
/*--------------------------------------------------------------------------*/
CDecimateSmoothNormals::~CDecimateSmoothNormals()
{
	if (m_pcDecimatePro)
		m_pcDecimatePro->Delete();
	if (m_pcSmoothPolyDataFilter)
		m_pcSmoothPolyDataFilter->Delete();
	if (m_pcPolyDataNormals)
		m_pcPolyDataNormals->Delete();
}

/*--------------------------------------------------------------------------*/
/* Decimate                                                                 */
/*--------------------------------------------------------------------------*/
void CDecimateSmoothNormals::Decimate(vtkAlgorithmOutput* pcPolyData, BOOL bDecimate, float fTargetReduction)
{
	if (bDecimate)
	{
		if (m_pcDecimatePro) 
			m_pcDecimatePro->Delete();
		m_pcDecimatePro = vtkDecimatePro::New();
		m_pcDecimatePro->GlobalWarningDisplayOff();
		m_pcDecimatePro->SetInputConnection(pcPolyData); 
		m_pcDecimatePro->SetTargetReduction(fTargetReduction);
		m_pcDecimatePro->Update();
	}
}

/*--------------------------------------------------------------------------*/
/* Smooth                                                                   */
 /*--------------------------------------------------------------------------*/
void CDecimateSmoothNormals::SmoothPolyData(vtkAlgorithmOutput* pcPolyData, BOOL bSmooth, BOOL bDecimate, int iNumberOfIterations, float fRelaxationFactor)
{
	if (bSmooth)
	{
		if (m_pcSmoothPolyDataFilter) 
			m_pcSmoothPolyDataFilter->Delete();
		m_pcSmoothPolyDataFilter = vtkSmoothPolyDataFilter::New();
		if (bDecimate)
			m_pcSmoothPolyDataFilter->SetInputConnection(m_pcDecimatePro->GetOutputPort());
		else
			m_pcSmoothPolyDataFilter->SetInputConnection(pcPolyData);
		m_pcSmoothPolyDataFilter->SetNumberOfIterations(iNumberOfIterations);
		m_pcSmoothPolyDataFilter->SetRelaxationFactor(fRelaxationFactor);
		m_pcSmoothPolyDataFilter->Update();
	}
}

/*--------------------------------------------------------------------------*/
/* ComputePointNormals                                                      */
/*--------------------------------------------------------------------------*/
void CDecimateSmoothNormals::ComputePolyDataNormals(vtkAlgorithmOutput* pcPolyData, vtkAlgorithmOutput* pcCleanPolyData, BOOL bSmooth, BOOL bDecimate, BOOL bAverage)
{
	if (m_pcPolyDataNormals) 
		m_pcPolyDataNormals->Delete();
	m_pcPolyDataNormals = vtkPolyDataNormals::New();
	m_pcPolyDataNormals->GlobalWarningDisplayOff();
	if (bSmooth)
		m_pcPolyDataNormals->SetInputConnection(m_pcSmoothPolyDataFilter->GetOutputPort());
	else 
		if (bDecimate)
			m_pcPolyDataNormals->SetInputConnection(m_pcDecimatePro->GetOutputPort());
		else 
			if (bAverage)
				m_pcPolyDataNormals->SetInputConnection(pcPolyData);
			else
				m_pcPolyDataNormals->SetInputConnection(pcCleanPolyData);
}