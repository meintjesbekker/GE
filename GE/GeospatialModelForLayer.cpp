/*--------------------------------------------------------------------------*/
/*						GeospatialModelForLayer.cpp							*/
/*                            												*/
/*	Purpose	: Construct a geospatial model visualization object for a		*/
/*			  single layer.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelForLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction              			                                    */
/*--------------------------------------------------------------------------*/
CGeospatialModelForLayer::CGeospatialModelForLayer(	CModel* pcModel /* = NULL */, 
													int	iLayerNumber /* = 0 */) 
	: CGeospatialModelForLayerGUI(pcModel),
	  CGeometry(pcModel),
	  CSidesQuadTopology(pcModel)
{
	CIndexes::m_pcModelInfo = pcModel;
	m_iLayerNumber = iLayerNumber;
}

/*--------------------------------------------------------------------------*/
/* Destruction              			                                    */
/*--------------------------------------------------------------------------*/
CGeospatialModelForLayer::~CGeospatialModelForLayer()
{
}

/*--------------------------------------------------------------------------*/
/* Create                                                                   */
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::Create()
{
	Update();
}

/*--------------------------------------------------------------------------*/
/* Update						                                            */
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::Update()
{
	CreateIBDActiveCellsArray(m_iLayerNumber);
	CreateGeometry();
	CreateTopology();
	CreatePolyData(m_pcFloatPoints, m_pcCellArray);
	CleanPolygonalData(m_pcPolyData);
	Triangulate(m_bAverage);
	Decimate(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutput() : NULL, 
				m_bDecimate, 
				m_fTargetReduction);
	SmoothPolyData(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutput() : NULL, 
					m_bSmooth, 
					m_bDecimate, 
					m_iNumberOfIterations, 
					m_fRelaxationFactor);
	ComputePolyDataNormals(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutput() : NULL, 
							m_pcCleanPolyData->GetOutput(), 
							m_bSmooth, 
							m_bDecimate, 
							m_bAverage);
	Clip();
}

/*--------------------------------------------------------------------------*/
/* Clip																		*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::Clip()
{
	DoClipPolyData(m_pcPolyDataNormals->GetOutput());
	CreateMapper();
	CreateLODActor(m_pcPolyDataMapper, m_bVisible, m_fOpacity, m_cColor);
}

/*--------------------------------------------------------------------------*/
/* CreateMapper																*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::CreateMapper()
{
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(m_pcClipPolyData->GetOutput());
	else
		CMapper::CreateMapper(m_pcPolyDataNormals->GetOutput());
}

/*--------------------------------------------------------------------------*/
/* CreateGeometry                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::CreateGeometry()
{
	if (m_bAverage)
		CreateAverageGeometry(m_iLayerNumber);
	else
		CreateNormalGeometry(m_iLayerNumber);
}

/*--------------------------------------------------------------------------*/
/* CreateTopology                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::CreateTopology()
{
	if (m_pcCellArray) 
		m_pcCellArray->Delete();
	m_pcCellArray = vtkCellArray::New();

	// average option is used
	if (m_bAverage)
	{
		if (GetVisibilityTop())
			CreateHorizontalTopology(m_pcCellArray, m_bAverage);
		if (GetVisibilityBottom())
			CreateHorizontalTopology(m_pcCellArray, m_bAverage, GetAverageNumberOfLayerPoints());
	}
	else
	{
		if (GetVisibilityTop())
			CreateNormalTopology(m_pcCellArray, m_bAverage);
		if (GetVisibilityBottom())
			CreateNormalTopology(m_pcCellArray, m_bAverage, GetNormalNumberOfLayerPoints());
	}
	if (GetVisibilitySides())
		CreateSidesTopology(m_pcCellArray, m_bAverage);
}