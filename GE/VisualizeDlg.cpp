/*--------------------------------------------------------------------------*/
/*							VisualizeDlg.cpp  								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Visualize dialog box.      */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "VisualizeDlg.h"
#include "ModelOutline.h"
#include "GeospatialModel.h"
#include "XYZSurface.h"
#include "HydraulicTDComponents.h"
#include "HydraulicTIComponents.h"
#include "PotentiometricSurface.h"
#include "Parameter.h"
#include "MT3DMS.h"
#include "ReadFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction     														*/
/*--------------------------------------------------------------------------*/
CVisualizeDlg::CVisualizeDlg(CWnd* pParent /* = NULL */, 
							 CVtkDoc* pDoc /* = NULL */) 
	: CDialog(CVisualizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualizeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDoc = pDoc;
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualizeDlg)
	DDX_Control(pDX, IDC_BUTTON_REMOVE, m_ButtonRemove);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_ButtonAdd);
	DDX_Control(pDX, IDC_VISUALIZEGRID, m_VisualizeGrid);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* Message Map   															*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CVisualizeDlg, CDialog)
	//{{AFX_MSG_MAP(CVisualizeDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_COMMAND(ID_ADD_GEOSPATIAL_MODEL, OnAddGeospatialModel)
	ON_COMMAND(ID_ADD_XYZSURFACE, OnAddXYZSsurface)
	ON_COMMAND(ID_ADD_PARAMETER_HORIZONTAL_HYDRAULIC_CONDUCTIVITY, OnAddParameterHorizontalHydraulicConductivity)
	ON_COMMAND(ID_ADD_PARAMETER_VERTICAL_HYDRAULIC_CONDUCTIVITY, OnAddParameterVerticalHydraulicConductivity)
	ON_COMMAND(ID_ADD_PARAMETER_SPECIFIC_STORAGE, OnAddParameterSpecificStorage)
	ON_COMMAND(ID_ADD_PARAMETER_TRANSMISSIVITY, OnAddParameterTransmissivity)
	ON_COMMAND(ID_ADD_PARAMETER_VERTICAL_LEAKANCE, OnAddParameterVerticalLeakance)
	ON_COMMAND(ID_ADD_PARAMETER_STORAGE_COEFFICIENT, OnAddParameterStorageCoefficient)
	ON_COMMAND(ID_ADD_PARAMETER_EFFECTIVE_POROSITY, OnAddParameterEffectivePorosity)
	ON_COMMAND(ID_ADD_PARAMETER_SPECIFIC_YIELD, OnAddParameterSpecificYield)
	ON_COMMAND(ID_ADD_ISOSURFACE_MT3DMS, OnAddIsosurfaceMT3DMS)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_HORIZONTAL_HYDRAULIC_CONDUCTIVITY, OnUpdateAddParameterHorizontalHydraulicConductivity)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_VERTICAL_HYDRAULIC_CONDUCTIVITY, OnUpdateAddParameterVerticalHydraulicConductivity)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_SPECIFIC_STORAGE, OnUpdateAddParameterSpecificStorage)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_TRANSMISSIVITY, OnUpdateAddParameterTransmissivity)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_VERTICAL_LEAKANCE, OnUpdateAddParameterVerticalLeakance)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_STORAGE_COEFFICIENT, OnUpdateAddParameterStorageCoefficient)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_EFFECTIVE_POROSITY, OnUpdateAddParameterEffectivePorosity)
	ON_UPDATE_COMMAND_UI(ID_ADD_PARAMETER_SPECIFIC_YIELD, OnUpdateAddParameterSpecificYield)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_ADD_POTENTIOMETRIC_SURFACE, OnAddPotentiometricSurface)
	ON_UPDATE_COMMAND_UI(ID_ADD_POTENTIOMETRIC_SURFACE, OnUpdateAddPotentiometricSurface)
	ON_UPDATE_COMMAND_UI(ID_ADD_ISOSURFACE_MT3DMS, OnUpdateAddIsosurfaceMT3DMS)
	ON_COMMAND(ID_ADD_MODEL_OUTLINE, OnAddModelOutline)
	ON_COMMAND(ID_ADD_HYDRAULICCOMPONENTS_TIMEINDEPENDANT, OnAddTimeIndependantHydraulicComponents)
	ON_COMMAND(ID_ADD_HYDRAULICCOMPONENTS_TIMEDEPENDENT, OnAddTimeDependentHydraulicComponents)
	ON_COMMAND(ID_ADD_ISOSURFACE_PHT3D, OnAddIsosurfacePHT3D)
	ON_UPDATE_COMMAND_UI(ID_ADD_ISOSURFACE_PHT3D, OnUpdateAddIsosurfacePHT3D)
	ON_COMMAND(ID_ADD_ISOSURFACE_RT3D, OnAddIsosurfaceRT3D)
	ON_UPDATE_COMMAND_UI(ID_ADD_ISOSURFACE_RT3D, OnUpdateAddIsosurfaceRT3D)
	ON_UPDATE_COMMAND_UI(ID_ADD_HYDRAULICCOMPONENTS_TIMEINDEPENDANT, OnUpdateAddHydraulicComponentsTimeindependant)
	ON_UPDATE_COMMAND_UI(ID_ADD_HYDRAULICCOMPONENTS_TIMEDEPENDENT, OnUpdateAddHydraulicComponentsTimedependent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnButtonAdd                                                              */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnButtonAdd() 
{
	CRect rect;
	m_ButtonAdd.GetWindowRect(&rect);
	CMenu menu;
	CMenu* pMenu;
	menu.LoadMenu(IDR_ADD);
	pMenu = menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, rect.right, rect.top, this);	
}

/*--------------------------------------------------------------------------*/
/* OnButtonRemove                                                           */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnButtonRemove() 
{
	if (m_VisualizeGrid.GetNumberOfObjects() == 2) 
		m_ButtonRemove.EnableWindow(FALSE); 	// disable Remove Button
	m_VisualizeGrid.RemoveObject();
	m_VisualizeGrid.InitializeGrid();
	SetFocus();
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CVisualizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_VisualizeGrid.SetDocumentPointer(m_pDoc);
	m_VisualizeGrid.InitializeGrid();
	if (m_VisualizeGrid.GetNumberOfObjects() == 1) 
		m_ButtonRemove.EnableWindow(FALSE);		// disable Remove Button
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnAddModelOutline                                                        */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddModelOutline() 
{
	CModelOutline* pModelOutline = new CModelOutline(m_pDoc->m_pcModel);
	pModelOutline->Create();
	if (pModelOutline->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pModelOutline);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pModelOutline;	
}

/*--------------------------------------------------------------------------*/
/* OnAddGeospatialModel                                                     */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddGeospatialModel()
{
	CGeospatialModel* pGeospatialModel = new CGeospatialModel(m_pDoc->m_pcModel);
	pGeospatialModel->Create();
	if (pGeospatialModel->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pGeospatialModel);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pGeospatialModel;		
}

/*--------------------------------------------------------------------------*/
/* OnAddXYZSurface                                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddXYZSsurface() 
{
	CXYZSurface* xyzSurface = new CXYZSurface(m_pDoc->m_pcModel);
	if (xyzSurface->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(xyzSurface);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete xyzSurface;	
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterHydraulicConductivity                                      */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterHorizontalHydraulicConductivity() 
{
	AddParameter(HORIZONTAL_HYDRAULIC_CONDUCTIVITY);	
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterVerticalHydraulicConductivity                              */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterVerticalHydraulicConductivity() 
{
	AddParameter(VERTICAL_HYDRAULIC_CONDUCTIVITY);	
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterSpecificStorage                                            */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterSpecificStorage() 
{
	AddParameter(SPECIFIC_STORAGE);
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterTransmissivity                                             */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterTransmissivity() 
{
	AddParameter(TRANSMISSIVITY);
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterVerticalLeakance                                           */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterVerticalLeakance() 
{
	AddParameter(VERTICAL_LEAKANCE);
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterStorageCoefficient                                         */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterStorageCoefficient() 
{
	AddParameter(STORAGE_COEFFICIENT);	
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterEffectivePorosity                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterEffectivePorosity() 
{
	AddParameter(EFFECTIVE_POROSITY);	
}

/*--------------------------------------------------------------------------*/
/* OnAddParameterSpecificYield                                              */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddParameterSpecificYield() 
{
	AddParameter(SPECIFIC_YIELD);	
}

/*--------------------------------------------------------------------------*/
/* OnAddIsosurfaceMT3DMS                                                    */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddIsosurfaceMT3DMS() 
{
	CMT3DMS* pMT3DMS = new CMT3DMS(m_pDoc->m_pcModel);
	pMT3DMS->Initialize("mt3d");
	if (pMT3DMS->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pMT3DMS);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pMT3DMS;		
}

/*--------------------------------------------------------------------------*/
/* OnAddIsosurfacePHT3D                                                     */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddIsosurfacePHT3D() 
{
	CMT3DMS* pMT3DMS = new CMT3DMS(m_pDoc->m_pcModel);
	pMT3DMS->Initialize("pht3d");
	if (pMT3DMS->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pMT3DMS);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pMT3DMS;			
}

/*--------------------------------------------------------------------------*/
/* OnAddIsosurfaceRT3D														*/
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddIsosurfaceRT3D() 
{
	CMT3DMS* pMT3DMS = new CMT3DMS(m_pDoc->m_pcModel);
	pMT3DMS->Initialize("rt3d");
	if (pMT3DMS->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pMT3DMS);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pMT3DMS;	
}

/*--------------------------------------------------------------------------*/
/* UpdateMenuUI                                                             */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::UpdateMenuUI(CWnd* pOwner, CMenu* pMenu, BOOL bAutoMenuEnable /* = TRUE */)
{
	// Checks the enabled/checked state of various menu items
	// (adapted from MFC's own CFrameWnd::OnInitMenuPopup() function - WinFrm.cpp)
	ASSERT_VALID( pOwner );
	ASSERT( pMenu != NULL );

	// Create and initialize the famous CCmdUI object
	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(pOwner->m_hWnd)) != NULL)
	{
		CWnd* pParent = pOwner->GetTopLevelParent();
		// child windows don't have menus -- need to go to the top!
		if (pParent != NULL 
			&& (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pMenu->GetMenuItemCount();

	// For each menu item...
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		// Get menu item ID
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Maybe a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue; // first item of popup can't be routed to
			}
			state.DoUpdate(pOwner, FALSE);	// popups are never auto disabled
		}
		else
		{
			// Normal menu item:
			// Auto enable/disable if 'bAutoMenuEnable' argument is set
			// and command is _not_ a system command
			state.m_pSubMenu = NULL;
			state.DoUpdate(pOwner, bAutoMenuEnable && state.m_nID < 0xF000);
		}

		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (	state.m_nIndex < nCount 
					&& pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterHorizontalHydraulicConductivity                      */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterHorizontalHydraulicConductivity(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetCONFileExists())
		pCmdUI->Enable(TRUE);	
}


/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterVerticalHydraulicConductivity                        */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterVerticalHydraulicConductivity(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetLEAFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterSpecificStorage                                      */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterSpecificStorage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetSTOFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterTransmissivity                                       */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterTransmissivity(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetHTCFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateParameterVerticalLeakance                                        */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterVerticalLeakance(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetLKNFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterStorageCoefficient                                   */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterStorageCoefficient(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetSCCFileExists())
		pCmdUI->Enable(TRUE);	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterEffectivePorosity                                    */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterEffectivePorosity(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetPORFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddParameterSpecificYield                                        */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddParameterSpecificYield(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetYLDFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnInitMenuPopup                                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// Delegate the real work to UpdateMenuUI() function
	UpdateMenuUI(this, pPopupMenu);
}

/*--------------------------------------------------------------------------*/
/* AddParameter                                                             */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::AddParameter(PARAMETERTYPE parameter)
{
	CParameter* pParameter = new CParameter(m_pDoc->m_pcModel);
	pParameter->CreateParameter(parameter);
	if (pParameter->DoSheetAndPagesForCreate())
	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pParameter);
		m_VisualizeGrid.InitializeGrid();
		m_ButtonRemove.EnableWindow(TRUE);
		SetFocus();
	}
	else
		delete pParameter;
}

/*--------------------------------------------------------------------------*/
/* OnAddPotentiometricSurface                                               */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddPotentiometricSurface() 
{
	CPotentiometricSurface* pPotentiometricSurface = new CPotentiometricSurface(m_pDoc->m_pcModel);
	int iNumberOfTimes = pPotentiometricSurface->ReadHeadTimes();
	if (iNumberOfTimes > 0)
	{
		if (pPotentiometricSurface->DoSheetAndPagesForCreate())
		{
			m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pPotentiometricSurface);
			m_VisualizeGrid.InitializeGrid();
			m_ButtonRemove.EnableWindow(TRUE);
			SetFocus();
		}
		else
			delete pPotentiometricSurface;
	}
	else 
	{
		delete pPotentiometricSurface;
		CString str;
		str.Format("The 'heads.dat' file contains no data.");
		AfxMessageBox(str);
	}	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddPotentiometricSurface                                        */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddPotentiometricSurface(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetHeadsFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddIsosurfaceMT3DMS                                              */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddIsosurfaceMT3DMS(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetMT3DMSFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddIsosurfacePHT3D                                               */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddIsosurfacePHT3D(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetPHT3DFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddIsosurfaceRT3D                                                */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddIsosurfaceRT3D(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_pDoc->m_pcModel->m_cFilesExist.GetRT3DFileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnAddTimeIndependentHydraulicComponents                                  */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddTimeIndependantHydraulicComponents() 
{
 	CHydraulicTIComponents* pHydraulicTIComponents = new CHydraulicTIComponents(m_pDoc->m_pcModel);
 	pHydraulicTIComponents->Create();
	if (pHydraulicTIComponents->DoSheetAndPagesForCreate())
 	{
 		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pHydraulicTIComponents);
 		m_VisualizeGrid.InitializeGrid();
 		m_ButtonRemove.EnableWindow(TRUE);
 		SetFocus();
 	}
 	else 
 		delete pHydraulicTIComponents;
}

/*--------------------------------------------------------------------------*/
/* OnAddTimeDependentHydraulicComponents                                    */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnAddTimeDependentHydraulicComponents() 
{
 	CHydraulicTDComponents* pHydraulicTDComponents = new CHydraulicTDComponents(m_pDoc->m_pcModel);
 	pHydraulicTDComponents->Create();
 	if (pHydraulicTDComponents->DoSheetAndPagesForCreate())
 	{
		m_pDoc->m_pcVisualization->AddVisualizationObjectToArray(pHydraulicTDComponents);
 		m_VisualizeGrid.InitializeGrid();
 		m_ButtonRemove.EnableWindow(TRUE);
 		SetFocus();
 	}
 	else 
 		delete pHydraulicTDComponents;	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddHydraulicComponentsTimeindependant                            */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddHydraulicComponentsTimeindependant(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	
	// Fixed head cell, when value < 0.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetIBDFileExists())
		pCmdUI->Enable(TRUE);

	// Fixed concentration cell, when value < 0.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetTICFileExists())
		pCmdUI->Enable(TRUE);

	// Horizontal flow barrier.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetWACFileExists())
		pCmdUI->Enable(TRUE);

	// Reservoir
	if (m_pDoc->m_pcModel->m_cFilesExist.GetC85FileExists())
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateAddHydraulicComponentsTimedependent	                            */
/*--------------------------------------------------------------------------*/
void CVisualizeDlg::OnUpdateAddHydraulicComponentsTimedependent(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	
	// General head boundary.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetGHBFileExists())
		pCmdUI->Enable(TRUE);

	// Discharge and Recharge wells.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetWELFileExists())
		pCmdUI->Enable(TRUE);

	// Drain
	if (m_pDoc->m_pcModel->m_cFilesExist.GetDRCFileExists())
		pCmdUI->Enable(TRUE);

	// River
	if (m_pDoc->m_pcModel->m_cFilesExist.GetRICFileExists())
		pCmdUI->Enable(TRUE);

	// Time variant specified head.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetCH1FileExists())
		pCmdUI->Enable(TRUE);

	// Time variant specified concentration.
	if (m_pDoc->m_pcModel->m_cFilesExist.GetC55FileExists())
		pCmdUI->Enable(TRUE);
}