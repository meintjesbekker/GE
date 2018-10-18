/*--------------------------------------------------------------------------*/
/*						GeospatialModelVisiblePage.cpp 						*/
/*                            												*/
/*	Purpose	: Visible page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.2 "Visible".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelVisiblePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CGeospatialModelVisiblePage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CGeospatialModelVisiblePage::CGeospatialModelVisiblePage(	CModel*	pcModel, /* = NULL */      
															CGeospatialModel* pcGeospatialModel	/* = NULL */) : CPropertyPage(CGeospatialModelVisiblePage::IDD)
{
	m_pcModel	= pcModel;
	m_pcGeospatialModel = pcGeospatialModel;
	
	//{{AFX_DATA_INIT(CGeospatialModelVisiblePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CGeospatialModelVisiblePage::~CGeospatialModelVisiblePage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelVisiblePage, CPropertyPage)
	//{{AFX_MSG_MAP(CGeospatialModelVisiblePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisiblePage::OnOK() 
{
	for (int layer = 1; layer <= m_pcModel->GetNumberOfLayers(); layer++)
	{
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetVisibilityTop(m_cMSFlexGrid.GetVisibilityTop(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetVisibilitySides(m_cMSFlexGrid.GetVisibilitySides(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetVisibilityBottom(m_cMSFlexGrid.GetVisibilityBottom(layer));
	}	
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisiblePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeospatialModelVisiblePage)
	DDX_Control(pDX, IDC_MSFLEXGRID_VISIBLE, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CGeospatialModelVisiblePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_cMSFlexGrid.SetModelPointer(m_pcModel);
	m_cMSFlexGrid.SetGeospatialModelPointer(m_pcGeospatialModel);
	m_cMSFlexGrid.InitializeGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}