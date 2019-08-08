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
//#include "GE.h"
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
	m_pcActor2D = NULL;
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
	if (m_pcActor2D)
		m_pcActor2D->Delete();
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
/* CreateLODActor         													*/
/*--------------------------------------------------------------------------*/
void CActor::CreateScalarBarActor(vtkMapper* pcMapper)
{
	vtkSmartPointer <vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();

	// Make the lookup table.
	vtkSmartPointer<vtkColorSeries> colorSeries = vtkSmartPointer<vtkColorSeries>::New();
	// Select a color scheme.
	int colorSeriesEnum;
	// colorSeriesEnum = colorSeries->BREWER_DIVERGING_BROWN_BLUE_GREEN_9;
	// colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_10;
	// colorSeriesEnum = colorSeries->BREWER_DIVERGING_SPECTRAL_3;
	// colorSeriesEnum = colorSeries->BREWER_DIVERGING_PURPLE_ORANGE_9;
	// colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_PURPLE_9;
	// colorSeriesEnum = colorSeries->BREWER_SEQUENTIAL_BLUE_GREEN_9;
	colorSeriesEnum = colorSeries->BREWER_QUALITATIVE_SET3;
	// colorSeriesEnum = colorSeries->CITRUS;
	colorSeries->SetColorScheme(colorSeriesEnum);
	colorSeries->BuildLookupTable(lut);
	lut->SetNanColor(1, 0, 0, 1);

	if (m_pcActor2D)
		m_pcActor2D->Delete();
	m_pcActor2D = vtkScalarBarActor::New();
	m_pcActor2D->SetLookupTable(pcMapper->GetLookupTable());
	//m_pcActor2D->SetLookupTable(lut);
	m_pcActor2D->SetTitle("Legend");
	m_pcActor2D->SetNumberOfLabels(2);
	m_pcActor2D->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
	m_pcActor2D->GetPositionCoordinate()->SetValue(0.1, 0.01);
	m_pcActor2D->SetOrientationToHorizontal();
	m_pcActor2D->SetWidth(0.8);
	m_pcActor2D->SetHeight(0.1);
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

	// TODO: Try this out to see what it looks like. This unfortunately does triangles and not quads!
	// pcActor->GetProperty()->SetEdgeVisibility(1);
	// pcActor->GetProperty()->SetEdgeColor(0.9, 0.9, 0.4);

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