/*--------------------------------------------------------------------------*/
/*					GeospatialModelGeneralPage.cpp							*/
/*                            												*/
/*	Purpose	: General page for Geospatial Model GUI.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General". 						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelGeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create															*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CGeospatialModelGeneralPage, CPropertyPage)

/*--------------------------------------------------------------------------*/
/* Construction  															*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralPage::CGeospatialModelGeneralPage(	CModel*	pcModel, /* = NULL */      
															CGeospatialModel* pcGeospatialModel	/* = NULL */) : CPropertyPage(CGeospatialModelGeneralPage::IDD)
{
	m_pcModel = pcModel;
	m_pcGeospatialModel = pcGeospatialModel;

	//{{AFX_DATA_INIT(CGeospatialModelGeneralPage)
	m_sDescription = _T("");
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Destruction   															*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralPage::~CGeospatialModelGeneralPage()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGeospatialModelGeneralPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Evenets Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CGeospatialModelGeneralPage, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CGeospatialModelGeneralPage)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* OnOK                                                                     */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralPage::OnOK() 
{
	UpdateData(TRUE);
	m_pcGeospatialModel->SetDescription(m_sDescription);
	for (int layer = 1; layer <= m_pcModel->GetNumberOfLayers(); layer++)
	{
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetVisibility(m_cMSFlexGrid.GetVisibility(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetColor(m_cMSFlexGrid.GetColor(layer));
		m_pcGeospatialModel->m_pLayerArray.GetAt(layer-1)->SetOpacity(m_cMSFlexGrid.GetOpacity(layer));
	}	
	CPropertyPage::OnOK();
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange															*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeospatialModelGeneralPage)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_sDescription);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_cMSFlexGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CGeospatialModelGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_sDescription = m_pcGeospatialModel->GetDescription();
	UpdateData(FALSE);
	m_cMSFlexGrid.SetModelPointer(m_pcModel);
	m_cMSFlexGrid.SetGeospatialModelPointer(m_pcGeospatialModel);
	m_cMSFlexGrid.InitializeGrid();
	return TRUE; // return TRUE unless you set the focus to a control
	             // EXCEPTION: OCX Property Pages should return FALSE
}