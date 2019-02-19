/*--------------------------------------------------------------------------*/
/*							GeospatialModel.cpp 							*/
/*                            												*/
/*	Purpose	: Construct a geostpatial model visualization object for all	*/
/*			  layers.														*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".         				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModel.h"
#include "GeospatialModelSheet.h"
#include "GeospatialModelGeneralPage.h"
#include "GeospatialModelVisiblePage.h"
#include "GeospatialModelAveragePage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CGeospatialModel::CGeospatialModel(CModel* pModel /* = NULL */) : CVisualizationObject()
{
	m_pcModel = pModel;
	SetDescription(_T("Geospatial Model"));
	m_cMinimumColor = RGB(100, 190, 5);
	m_cMaximumColor = RGB(255, 130, 0);
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CGeospatialModel::~CGeospatialModel()
{
	for (int i = 0; i < m_pLayerArray.GetSize(); i++)
		delete m_pLayerArray[i];
	m_pLayerArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* GetMaximumColor                                                          */
/*--------------------------------------------------------------------------*/
COLORREF CGeospatialModel::GetMaximumColor()
{
	return m_cMaximumColor;
}

/*--------------------------------------------------------------------------*/
/* SetMaximumColor                                                          */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::SetMaximumColor(COLORREF cColor)
{
	m_cMaximumColor = cColor;
}

/*--------------------------------------------------------------------------*/
/* GetMinimumColor                                                          */
/*--------------------------------------------------------------------------*/
COLORREF CGeospatialModel::GetMinimumColor()
{
	return m_cMinimumColor;
}

/*--------------------------------------------------------------------------*/
/* SetMinimumColor                                                          */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::SetMinimumColor(COLORREF cColor)
{
	m_cMinimumColor = cColor;
}

/*--------------------------------------------------------------------------*/
/* GetSpectrumColor                                                         */
/*--------------------------------------------------------------------------*/
COLORREF CGeospatialModel::GetSpectrumColor(int iLayer)
{	
	COLORREF cColor(NULL);

	if (iLayer == 1)
		cColor = m_cMinimumColor;
	else 
		if (iLayer == m_pcModel->GetNumberOfLayers())
			cColor = m_cMaximumColor;
	if (m_pcModel->GetNumberOfLayers() > 2)
	{
		float deltaRed = (GetRValue(m_cMaximumColor) - GetRValue(m_cMinimumColor))/(m_pcModel->GetNumberOfLayers()-1);
		float deltaGreen = (GetGValue(m_cMaximumColor) - GetGValue(m_cMinimumColor))/(m_pcModel->GetNumberOfLayers()-1);
		float deltaBlue = (GetBValue(m_cMaximumColor) - GetBValue(m_cMinimumColor))/(m_pcModel->GetNumberOfLayers()-1);
		
		// assign color
		cColor =  RGB(	GetRValue(m_cMinimumColor) + (iLayer - 1) * deltaRed,
						GetGValue(m_cMinimumColor) + (iLayer - 1) * deltaGreen,
						GetBValue(m_cMinimumColor) + (iLayer - 1) * deltaBlue);
	}
	return cColor;
}

/*--------------------------------------------------------------------------*/
/* Create                                                                   */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::Create()
{
	// get a pointer to main frame
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		
	// create progress bar
	CProgressCtrl wndProgress;
	pMainFrame->CreateProgressBar(	&wndProgress,
									_T("Creating Geospatial Model..."));

	// initialize progress control range and step size
	wndProgress.SetRange(0, 2 * m_pcModel->GetNumberOfLayers());
	wndProgress.SetStep(1);

	// create the geospatial objects
	for (int numbLayers = 1; numbLayers <= m_pcModel->GetNumberOfLayers(); numbLayers++)
	{
		wndProgress.StepIt();
	    CGeospatialModelForLayer* iLayer = new CGeospatialModelForLayer(m_pcModel, numbLayers);
		iLayer->SetColor(GetSpectrumColor(numbLayers));
		m_pLayerArray.Add(iLayer);
	}

	// step and create for each layer
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		wndProgress.StepIt();
		m_pLayerArray.GetAt(iLayer - 1)->Create();
	}
	
	// remove actors
	RemoveActors();
	for (int i = 0; i < m_pLayerArray.GetSize(); i++)
	{
		AddActor(m_pLayerArray[i]->GetLODActor());
		AddActor2D(m_pLayerArray[i]->GetActor2D());
	}

	// ensures that idle message is displayed again
	pMainFrame->PostMessage(WM_SETMESSAGESTRING, (WPARAM) AFX_IDS_IDLEMESSAGE, 0L);
}

/*--------------------------------------------------------------------------*/
/* Update               				                                    */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::Update()
{
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
		m_pLayerArray.GetAt(iLayer - 1)->Update();

	// remove actors
	RemoveActors();
	for (int i = 0; i < m_pLayerArray.GetSize(); i++)
		AddActor(m_pLayerArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* Clip						                                                */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::Clip()
{
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
		m_pLayerArray.GetAt(iLayer - 1)->Clip();

	// remove actors
	RemoveActors();
	for (int i = 0; i < m_pLayerArray.GetSize(); i++)
		AddActor(m_pLayerArray[i]->GetLODActor());
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForCreate                                                 */
/*--------------------------------------------------------------------------*/
BOOL CGeospatialModel::DoSheetAndPagesForCreate()
{
	CGeospatialModelSheet dlg(_T("Geospatial Model"));
	CGeospatialModelGeneralPage generalPage(m_pcModel, this);
	dlg.AddPage(&generalPage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* DoSheetAndPagesForChange                                                 */
/*--------------------------------------------------------------------------*/
BOOL CGeospatialModel::DoSheetAndPagesForChange()
{
	CGeospatialModelSheet dlg(_T("Geospatial Model"));
	CGeospatialModelGeneralPage generalPage(m_pcModel, this);
	CGeospatialModelVisiblePage	visiblePage(m_pcModel, this);
	CGeospatialModelAveragePage averagePage(m_pcModel, this);
	dlg.AddPage(&generalPage);
	dlg.AddPage(&visiblePage);
	dlg.AddPage(&averagePage);
	if (dlg.DoModal() == IDOK)
	{
		Update();
		return TRUE;
	}
	else
		return FALSE;
}

/*--------------------------------------------------------------------------*/
/* Serialize                                                                */
/*--------------------------------------------------------------------------*/
void CGeospatialModel::Serialize(CArchive& ar)
{
	CVisualizationObject::Serialize(ar);
}