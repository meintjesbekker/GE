/*--------------------------------------------------------------------------*/
/*							ModelOutline.cpp								*/
/*                            												*/
/*	Purpose	: Construct a model outline visualization object.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.2 "Model Outline".                          */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ModelOutline.h"
#include "ModelOutlineSheet.h"
#include "ModelOutlineGeneralPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CModelOutline::CModelOutline(CModel* pcModel) : CMapper(pcModel),
												CVisualizationObject()
{
	// general page
	SetDescription(_T("Model Outline"));
	m_cMinimumCornerCoordinate.SetX(m_pcModel->GetMinimumXBound());
	m_cMaximumCornerCoordinate.SetX(m_pcModel->GetMaximumXBound());
	m_cMinimumCornerCoordinate.SetY(m_pcModel->GetMinimumYBound());
	m_cMaximumCornerCoordinate.SetY(m_pcModel->GetMaximumYBound());
	m_cMinimumCornerCoordinate.SetZ(m_pcModel->GetMinimumZBound());
	m_cMaximumCornerCoordinate.SetZ(m_pcModel->GetMaximumZBound());

	// vtk
	m_pcOutlineSource = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction 				                                                */
/*--------------------------------------------------------------------------*/
CModelOutline::~CModelOutline()
{
	// outline 
	if (m_pcOutlineSource)
		m_pcOutlineSource->Delete();
}

/*--------------------------------------------------------------------------*/
/* SetCornerCoordinate														*/
/*--------------------------------------------------------------------------*/
void CModelOutline::SetMinimumCornerCoordinate(float fX, float fY, float fZ)
{
	m_cMinimumCornerCoordinate.SetX(fX);
	m_cMinimumCornerCoordinate.SetY(fY);
	m_cMinimumCornerCoordinate.SetZ(fZ);
}

/*--------------------------------------------------------------------------*/
/* SetMaximumCornerCoordinate												*/
/*--------------------------------------------------------------------------*/
void CModelOutline::SetMaximumCornerCoordinate(float fX, float fY, float fZ)
{
	m_cMaximumCornerCoordinate.SetX(fX);
	m_cMaximumCornerCoordinate.SetY(fY);
	m_cMaximumCornerCoordinate.SetZ(fZ);
}

/*--------------------------------------------------------------------------*/
/* Create              				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutline::Create()
{
	CreateOutlineSource();
	CreateMapper(m_pcOutlineSource->GetOutput());
	CreateActor();
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate			                                        */
/*--------------------------------------------------------------------------*/
BOOL CModelOutline::DoSheetAndPagesForCreate()
{
	CModelOutlineSheet dlg(_T("Model Outline"));
	CModelOutlineGeneralPage generalPage(m_pcModel, this);
	dlg.AddPage(&generalPage);
	
	if (dlg.DoModal() == IDOK)
		return TRUE;
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForChange			                                        */
/*--------------------------------------------------------------------------*/
BOOL CModelOutline::DoSheetAndPagesForChange()
{
	CModelOutlineSheet dlg(_T("Model Outline"));
	CModelOutlineGeneralPage generalPage(m_pcModel, this);
	dlg.AddPage(&generalPage);
	if (dlg.DoModal() == IDOK)
	{
		Create();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* Serialize           				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutline::Serialize(CArchive& ar)
{
	CVisualizationObject::Serialize(ar);
	m_cMinimumCornerCoordinate.Serialize(ar);
	m_cMaximumCornerCoordinate.Serialize(ar);

	if (!ar.IsStoring())
		Create();
}

/*--------------------------------------------------------------------------*/
/* CreateOutlineSource 				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutline::CreateOutlineSource()
{
	if (m_pcOutlineSource) 
		m_pcOutlineSource->Delete();
	m_pcOutlineSource = vtkOutlineSource::New();
	m_pcOutlineSource->SetBounds(	m_cMinimumCornerCoordinate.GetX(),
									m_cMaximumCornerCoordinate.GetX(),
									m_cMinimumCornerCoordinate.GetY(),
									m_cMaximumCornerCoordinate.GetY(),
									m_cMinimumCornerCoordinate.GetZ(),
									m_cMaximumCornerCoordinate.GetZ());
	m_pcOutlineSource->Update();
}

/*--------------------------------------------------------------------------*/
/* CreateActor        				                                        */
/*--------------------------------------------------------------------------*/
void CModelOutline::CreateActor()
{
	COLORREF cColor = RGB(0, 0, 0);
	CActor::CreateActor(m_pcPolyDataMapper, TRUE, 1.0, cColor);
	RemoveActors();
	AddActor(m_pcActor);
}