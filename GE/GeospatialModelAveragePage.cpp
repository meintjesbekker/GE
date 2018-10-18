/*--------------------------------------------------------------------------*/
/*						GeospatialModelAveragePage.cpp 						*/
/*                            												*/
/*	Purpose	: Average page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide section 3.3.3 "Average".           				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelAveragePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                 											*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CGeospatialModelAveragePage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction                  											*/
/*--------------------------------------------------------------------------*/
CGeospatialModelAveragePage::CGeospatialModelAveragePage(	CModel* pcModel, /* = NULL */      
															CGeospatialModel* pcGeospatialModel	/* = NULL */) : CPropertyPage(CGeospatialModelAveragePage::IDD)
{
	m_pcModel	= pcModel;
	m_pcGeospatialModel = pcGeospatialModel;

	//{{AFX_DATA_INIT(CGeospatialModelAveragePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destrcution						               							*/
/*--------------------------------------------------------------------------*/
CGeospatialModelAveragePage::~CGeospatialModelAveragePage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                   											*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelAveragePage, CPropertyPage)
	//{{AFX_MSG_MAP(CGeospatialModelAveragePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAveragePage::OnOK() 
{
	for (int layer = 1; layer <= m_pcModel->GetNumberOfLayers(); layer++)
	{
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetAverage(m_cMSFlexGrid.GetAverage(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetDecimate(m_cMSFlexGrid.GetDecimate(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetTargetReduction(m_cMSFlexGrid.GetTargetReduction(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetSmooth(m_cMSFlexGrid.GetSmooth(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetNumberOfIterations(m_cMSFlexGrid.GetIterations(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetRelaxationFactor(m_cMSFlexGrid.GetRelaxationFactor(layer));
	}		
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                											*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelAveragePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CGeospatialModelAveragePage)
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CGeospatialModelAveragePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_cMSFlexGrid.SetModelPointer(m_pcModel);
	m_cMSFlexGrid.SetGeospatialModelPointer(m_pcGeospatialModel);
	m_cMSFlexGrid.InitializeGrid();
	return TRUE; // return TRUE unless you set the focus to a control
	             // EXCEPTION: OCX Property Pages should return FALSE
}
