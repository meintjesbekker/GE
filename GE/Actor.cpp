/*--------------------------------------------------------------------------*/
/*								Actor.cpp 									*/
/*                            												*/
/*	Purpose	: Create an actor.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.6 "Actor".                   				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Actor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CActor::CActor(CModel* pcModel /* = NULL */)
{
	m_pcModel = pcModel;

	// vtk
	m_pcActor = NULL;
	m_pcLODActor = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction             													*/
/*--------------------------------------------------------------------------*/
CActor::~CActor()
{
	if (m_pcActor)
		m_pcActor->Delete();
	if (m_pcLODActor)
		m_pcLODActor->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateActor         														*/
/*--------------------------------------------------------------------------*/
void CActor::CreateActor(vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor /* = NULL */)
{
	if (m_pcActor) 
		m_pcActor->Delete();
	m_pcActor = vtkActor::New();
	SetActorProperties(m_pcActor, pcMapper, bVisible, fOpacity, cColor);
}

/*--------------------------------------------------------------------------*/
/* UpdateActor            													*/
/*--------------------------------------------------------------------------*/
void CActor::UpdateActor(BOOL bVisible, COLORREF cColor)
{
	UpdateActor(m_pcActor, bVisible, cColor);
}

/*--------------------------------------------------------------------------*/
/* CreateLODActor         													*/
/*--------------------------------------------------------------------------*/
void CActor::CreateLODActor(vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor /* = -1 */)
{
	if (m_pcLODActor) 
		m_pcLODActor->Delete();
	m_pcLODActor = vtkLODActor::New();
	m_pcLODActor->SetNumberOfCloudPoints(2000);
	SetActorProperties(m_pcLODActor, pcMapper, bVisible, fOpacity, cColor);
}

/*--------------------------------------------------------------------------*/
/* SetActorProperties     													*/
/*--------------------------------------------------------------------------*/
void CActor::SetActorProperties(vtkActor* pcActor, vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor)
{
	pcActor->SetMapper(pcMapper);
	pcActor->SetVisibility(bVisible);
	pcActor->GetProperty()->SetOpacity(fOpacity);
	pcActor->GetProperty()->SetInterpolationToPhong();
	pcActor->SetScale(	m_pcModel->GetXScale(),
						m_pcModel->GetYScale(),
						m_pcModel->GetZScale());
	if (cColor != -1)
	{
		float fRed = GetRValue(cColor) / 255.0;
		float fGreen = GetGValue(cColor) / 255.0;
		float fBlue = GetBValue(cColor) / 255.0;
		pcActor->GetProperty()->SetColor(fRed, fGreen, fBlue);
	}
	pcActor->Modified();
}

/*--------------------------------------------------------------------------*/
/* UpdateLODActor            												*/
/*--------------------------------------------------------------------------*/
void CActor::UpdateLODActor(BOOL bVisible, COLORREF cColor)
{
	UpdateActor(m_pcLODActor, bVisible, cColor);
}

/*--------------------------------------------------------------------------*/
/* UpdateActor            													*/
/*--------------------------------------------------------------------------*/
void CActor::UpdateActor(vtkActor* pcActor, BOOL bVisible, COLORREF cColor)
{
	pcActor->SetVisibility(bVisible);
	float fRed = GetRValue(cColor) / 255.0;
	float fGreen = GetGValue(cColor) / 255.0;
	float fBlue = GetBValue(cColor) / 255.0;
	pcActor->GetProperty()->SetColor(fRed, fGreen, fBlue);
	pcActor->Modified();
}