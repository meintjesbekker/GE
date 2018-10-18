/*--------------------------------------------------------------------------*/
/*							MT3DMSTopology.h   								*/
/*                            												*/
/*	Purpose	: Create topology for MT3DMS, PHT3D or RT3D isosurfaces.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".          					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MainFrm.h"
#include "MT3DMSTopology.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction  				                                            */
/*--------------------------------------------------------------------------*/
CMT3DMSTopology::CMT3DMSTopology()
{
	// vtk
	m_pcContourFilter = NULL;
}

/*--------------------------------------------------------------------------*/
/* Desctuction   				                                            */
/*--------------------------------------------------------------------------*/
CMT3DMSTopology::~CMT3DMSTopology()
{
	if (m_pcContourFilter) 
		m_pcContourFilter->Delete();
}

/*--------------------------------------------------------------------------*/
/* Contour                      											*/
/*--------------------------------------------------------------------------*/
void CMT3DMSTopology::Contour(vtkStructuredGrid* pcStructuredGrid, CMT3DMSContourAndColorTable* pMT3DMSContourAndColorTable)
{
	// initialize contour filter
	if (m_pcContourFilter) 
		m_pcContourFilter->Delete();
	m_pcContourFilter = vtkContourFilter::New();

	// assign parameters
	m_pcContourFilter->SetInput(pcStructuredGrid);
	m_pcContourFilter->SetStartMethod(StartContouring, NULL);
	m_pcContourFilter->SetEndMethod(EndContouring, NULL);
	for (int i = 0; i < pMT3DMSContourAndColorTable->GetSize(); i++)
		m_pcContourFilter->SetValue(i, pMT3DMSContourAndColorTable->GetValue(i));
	m_pcContourFilter->Update();
}

/*--------------------------------------------------------------------------*/
/* StartContouring            												*/
/*--------------------------------------------------------------------------*/
void CMT3DMSTopology::StartContouring(void* pArgument)
{
	// get a pointer to main frame
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	// post message
	pMainFrame->PostMessage(WM_SETMESSAGESTRING, (WPARAM) AFX_IDS_IDLEMESSAGE, 0L);

	// create progress bar
	CProgressCtrl wndProgress;
	pMainFrame->CreateProgressBar(	&wndProgress,
									_T("Contouring..."));

	// initialize progress control range and step size
	wndProgress.SetRange(0, 1);
	wndProgress.SetStep(1);
}

/*--------------------------------------------------------------------------*/
/* EndContouring             												*/
/*--------------------------------------------------------------------------*/
void CMT3DMSTopology::EndContouring(void* pArgument)
{
	// get a pointer to main frame
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	// ensures that idle message is displayed again
	pMainFrame->PostMessage(WM_SETMESSAGESTRING, (WPARAM) AFX_IDS_IDLEMESSAGE, 0L);
}