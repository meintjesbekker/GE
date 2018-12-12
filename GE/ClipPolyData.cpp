/*--------------------------------------------------------------------------*/
/*								ClipPolyData.cpp   							*/
/*                            												*/
/*	Purpose	: Clip polygonal data with plane.                           	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.3.2.2.3 "Clip Polygonal Data". 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ClipPolyData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction           													*/
/*--------------------------------------------------------------------------*/
CClipPolyData::CClipPolyData(CModel* pcModel /* = NULL */) 
	: CMapper(pcModel)
{
	// vtk
	m_pcPlane = NULL;
	m_pcClipPolyData = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction             													*/
/*--------------------------------------------------------------------------*/
CClipPolyData::~CClipPolyData()
{
	if (m_pcPlane)
		m_pcPlane->Delete();
	if (m_pcClipPolyData)
		m_pcClipPolyData->Delete();
}

/*--------------------------------------------------------------------------*/
/* DoClipPolyData         													*/
/*--------------------------------------------------------------------------*/
void CClipPolyData::DoClipPolyData(vtkPolyData* pcPolyData)
{
	if (m_pcModel->GetClip())
	{
		// cut plane
		if (m_pcPlane) 
			m_pcPlane->Delete();
		m_pcPlane = vtkPlane::New();
		m_pcPlane->SetOrigin(	m_pcModel->GetXCutPlaneOrigin(), 
								m_pcModel->GetYCutPlaneOrigin(), 
								m_pcModel->GetZCutPlaneOrigin());
		m_pcPlane->SetNormal(	m_pcModel->GetXCutPlaneNormal(), 
								m_pcModel->GetYCutPlaneNormal(), 
								m_pcModel->GetZCutPlaneNormal());
		
		// clip poly data
		if (m_pcClipPolyData) 
			m_pcClipPolyData->Delete();
		m_pcClipPolyData = vtkClipPolyData::New();
		m_pcClipPolyData->SetInputData(pcPolyData);
		m_pcClipPolyData->SetClipFunction(m_pcPlane);
		m_pcClipPolyData->GenerateClippedOutputOn();
		m_pcClipPolyData->Update();
	}
}