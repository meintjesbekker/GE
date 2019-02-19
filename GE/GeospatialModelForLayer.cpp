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
	Decimate(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
				m_bDecimate, 
				m_fTargetReduction);
	SmoothPolyData(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
					m_bSmooth, 
					m_bDecimate, 
					m_iNumberOfIterations, 
					m_fRelaxationFactor);
	ComputePolyDataNormals(	(m_pcTriangleFilter) ? m_pcTriangleFilter->GetOutputPort() : NULL, 
							m_pcCleanPolyData->GetOutputPort(), 
							m_bSmooth, 
							m_bDecimate, 
							m_bAverage);
	Clip();
	// TODO: Figure a way to display the outlines of the cubes. 
	// Extracting the edges do not work for it shows triangles of all quads.
	// ExtractEdges();
}

/*--------------------------------------------------------------------------*/
/* Clip																		*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::Clip()
{
	DoClipPolyData(m_pcPolyDataNormals->GetOutputPort());
	CreateMapper();
	CreateLODActor(m_pcPolyDataMapper, m_bVisible, m_fOpacity, m_cColor);
	CreateScalarBarActor(m_pcPolyDataMapper);
}

/*--------------------------------------------------------------------------*/
/* ExtractEdges  															*/
/* TODO:	This is not going to work. Eges are going to be triangular. 
			Will need to create the grid lines explicity like you've done   
			each grid cell.
			There is also the problem that each pipeline one has got one 
			actor. You therefore cannot just go and another actor.
			You don't even need to do this. You can just switch it on.
			Look for another TODO.
			*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::ExtractEdges()
{
	vtkSmartPointer<vtkExtractEdges> extractEdges = vtkSmartPointer<vtkExtractEdges>::New();
	if (m_pcModel->GetClip())
		extractEdges->SetInputConnection(m_pcClipPolyData->GetOutputPort());
	else
		extractEdges->SetInputConnection(m_pcPolyDataNormals->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(extractEdges->GetOutputPort());
	CreateLODActor(mapper, m_bVisible, m_fOpacity, RGB(255, 0, 0));
}

/*--------------------------------------------------------------------------*/
/* CreateMapper																*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelForLayer::CreateMapper()
{
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(m_pcClipPolyData->GetOutputPort());
	else
		CMapper::CreateMapper(m_pcPolyDataNormals->GetOutputPort());
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

///*--------------------------------------------------------------------------*/
///* CreateScalarBarActor                                                     */
///*--------------------------------------------------------------------------*/
//void CGeospatialModelForLayer::CreateScalarBarActor()
//{
//	vtkSmartPointer<vtkScalarBarActor> scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
//	scalarBar->SetLookupTable(m_pcPolyDataMapper->GetLookupTable());
//	scalarBar->SetTitle("Title");
//	scalarBar->SetNumberOfLabels(4);
//	// m_Renderer->AddActor2D(scalarBar);
//}