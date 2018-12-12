/*--------------------------------------------------------------------------*/
/*							XYZSurface.cpp									*/
/*                            												*/
/*	Purpose	: Create 2D Delaunay triangulation of input points.             */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.5 "XYZ Surface".              				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Color.h"
#include "ColorPage.h"
#include "ColorSpectrum.h"
#include "XYZSurface.h"
#include "XYZSurfaceSheet.h"
#include "XYZSurfaceGeneralPage.h"
#include "XYZSurfaceDecSmoothPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction				                                                */
/*--------------------------------------------------------------------------*/
CXYZSurface::CXYZSurface(CModel* pcModel /* = NULL */) 
	: CXYZSurfaceGUI(pcModel),
	  CXYZSurfaceGeometryAndTopology(),
	  CVisualizationObject()
{
	// general page
	SetDescription(_T("XYZ Surface"));
	
	// vtk
	m_pcPolyData = NULL;
	m_pcLookupTable	= NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction				                                                */
/*--------------------------------------------------------------------------*/
CXYZSurface::~CXYZSurface()
{
	if (m_pcPolyData) 
		m_pcPolyData->Delete();
	if (m_pcLookupTable)
		m_pcLookupTable->Delete();
}

/*--------------------------------------------------------------------------*/
/* Create           		                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::Create()
{
	CreateMinimumMaximumElevationFromFile();
	CreateColor();
	Update();
}

/*--------------------------------------------------------------------------*/
/* Update					                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::Update()
{
	CreateGeometryAndScalarDatasetAttribute(m_sPathName, m_pcColor);
	CreateDataSet();
	Triangulate(m_pcPolyData);
	Decimate(	m_pcDelaunay2D->GetOutput(),
				m_bDecimate, 
				m_fTargetReduction);
	SmoothPolyData(	m_pcDelaunay2D->GetOutput(), 
					m_bSmooth, 
					m_bDecimate, 
					m_iNumberOfIterations, 
					m_fRelaxationFactor);
	ComputePolyDataNormals(	m_pcDelaunay2D->GetOutput(), 
							m_pcDelaunay2D->GetOutput(), 
							m_bSmooth, 
							m_bDecimate, 
							TRUE);
	Clip();
}

/*--------------------------------------------------------------------------*/
/* Clip						                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::Clip()
{
	// if clip is check
	DoClipPolyData(m_pcPolyDataNormals->GetOutput());
	CreateMapper();
	CreateActor();
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate			                                        */
/*--------------------------------------------------------------------------*/
BOOL CXYZSurface::DoSheetAndPagesForCreate()
{
	CXYZSurfaceSheet dlg(_T("XYZ Surface"));
	CXYZSurfaceGeneralPage generalPage(this);
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
/* DoSheetAndPagesForChange			                                        */
/*--------------------------------------------------------------------------*/
BOOL CXYZSurface::DoSheetAndPagesForChange()
{
	CXYZSurfaceSheet dlg(_T("XYZ Surface"));
	CXYZSurfaceGeneralPage generalPage(this, FALSE);
	CXYZSurfaceDecSmoothPage decSmoothPage(this);
	CColorPage colorPage(m_pcColor);
	dlg.AddPage(&generalPage);
	dlg.AddPage(&decSmoothPage);
	dlg.AddPage(&colorPage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* CreateMinimumMaximumElevationFromFile                                    */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateMinimumMaximumElevationFromFile()
{
	// if it is the first value of the file assign it to minimum and maximum
	BOOL firstValue = FALSE;

	// open file for input
	ifstream waterLevelFile(m_sPathName, ios::in);
	
	// xyz coordinate
	float xyz[3];

	// loop through file
	while (!waterLevelFile.eof())
	{
		// read xyz coordinate from file
		waterLevelFile >> xyz[0] >> xyz[1] >> xyz[2];

		// if it is the first xyz coordinate read, assign to minimum and 
		// maximum elevation
		if (!firstValue)
		{
			m_fMinimumValue = xyz[2];
			m_fMaximumValue = xyz[2];

			firstValue = TRUE;
		}
		else
		{
			// if value is smaller than current minimum
			if (xyz[2] < m_fMinimumValue)
				m_fMinimumValue = xyz[2];

			// if value is bigger than current maximum
			if (xyz[2] > m_fMaximumValue)
				m_fMaximumValue = xyz[2];
		}
	}
	waterLevelFile.close();
}

/*--------------------------------------------------------------------------*/
/* CreateDataSet			                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateDataSet()
{
	if (m_pcPolyData) 
		m_pcPolyData->Delete();
	m_pcPolyData = vtkPolyData::New();
	m_pcPolyData->SetPoints(m_pcFloatPoints);
	m_pcPolyData->GetPointData()->SetScalars(m_pcScalars);
	m_pcPolyData->Modified();
}

/*--------------------------------------------------------------------------*/
/* CreateColor                                                              */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateColor()
{
	if (m_pcColor) 
		delete m_pcColor;
	m_pcColor = new CColor();
	m_pcColor->m_cColorTable.SetMinimumScalarValue(m_fMinimumValue);
	m_pcColor->m_cColorTable.SetMaximumScalarValue(m_fMaximumValue);
	m_pcColor->m_cColorTable.SetMinimumScalarColor(RGB(0, 255, 0));
	m_pcColor->m_cColorTable.SetMaximumScalarColor(RGB(0, 0, 255));
	float interval = (m_fMaximumValue - m_fMinimumValue) / 5;
	m_pcColor->m_cColorTable.SetInterval(interval);
	m_pcColor->m_cColorTable.CreateColorRows();
}

/*--------------------------------------------------------------------------*/
/* CreateLookupTable                                                        */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateLookupTable()
{
	if (m_pcLookupTable) 
		m_pcLookupTable->Delete();
	m_pcLookupTable = CLookupTable::New();
	m_pcLookupTable->SetColorTable(&m_pcColor->m_cColorTable);
	m_pcLookupTable->SetNumberOfColors(m_pcColor->m_cColorTable.GetNumberOfColors());
	m_pcLookupTable->Build();
}

/*--------------------------------------------------------------------------*/
/* CreateMapper				                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateMapper()
{
	CreateLookupTable();
	if (m_pcModel->GetClip())
		CMapper::CreateMapper(	m_pcClipPolyData->GetOutput(),
								m_pcLookupTable,
								m_pcColor->m_cColorTable.GetMinimumScalarValue(),
								m_pcColor->m_cColorTable.GetMaximumScalarValue());
	else
		CMapper::CreateMapper(	m_pcDelaunay2D->GetOutput(),
								m_pcLookupTable,
								m_pcColor->m_cColorTable.GetMinimumScalarValue(),
								m_pcColor->m_cColorTable.GetMaximumScalarValue());
}

/*--------------------------------------------------------------------------*/
/* CreateActor 				                                                */
/*--------------------------------------------------------------------------*/
void CXYZSurface::CreateActor()
{
	CActor::CreateLODActor(m_pcPolyDataMapper, m_bVisible, m_pcColor->GetOpacity());
	RemoveActors();
	AddActor(m_pcLODActor);
}