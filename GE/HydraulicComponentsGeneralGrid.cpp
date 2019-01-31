/*--------------------------------------------------------------------------*/
/*					HydraulicComponentsGeneralGrid.cpp 						*/
/*                            												*/
/*	Purpose	: Grid which contains description, visible and color fields.    */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7.1 "General".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsGeneralGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralGrid::CHydraulicComponentsGeneralGrid()
{
	m_pcHydraulicComponents = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsGeneralGrid::~CHydraulicComponentsGeneralGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CHydraulicComponentsGeneralGrid, CWnd)
	//{{AFX_MSG_MAP(CHydraulicComponentsGeneralGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CHydraulicComponentsGeneralGrid, CWnd)
    //{{AFX_EVENTSINK_MAP(CHydraulicComponentsGeneralGrid)
	ON_EVENT(CHydraulicComponentsGeneralGrid, IDC_MSFLEXGRID, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT(CHydraulicComponentsGeneralGrid, IDC_MSFLEXGRID, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralGrid::InitializeGrid()
{
	m_bVisibleArray.SetSize(m_pcHydraulicComponents->GetArraySize(), 1);
	m_cColorArray.SetSize(m_pcHydraulicComponents->GetArraySize(), 1);
	SetCols(3);
	SetRows(m_pcHydraulicComponents->GetArraySize()+1);

	// column width
	SetColWidth(0, int(GetColWidth(0) * 2.9));
	SetColWidth(1, int(GetColWidth(1)));
	SetColWidth(2, int(GetColWidth(2)));

	// initialize headers
	// column 1
	SetRow(0);
	SetCol(0);
	SetCellAlignment(4);
	SetTextArray(0, "Description");

	// column 2
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Visible");

	// column 3
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Color");

	// for all components
	for (int i = 1; i <= m_pcHydraulicComponents->GetArraySize(); i++)
	{
		// set description
		SetTextArray(i*3, m_pcHydraulicComponents->GetHydraulicComponent(i-1)->GetDescription());

		// set visibility
		SetRow(i);
		SetCol(1);
		SetCellPictureAlignment(4);
		if (m_pcHydraulicComponents->GetHydraulicComponent(i-1)->GetVisibility())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			m_pcHydraulicComponents->GetHydraulicComponent(i-1)->SetVisibility(TRUE);
			SetVisibility(i, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			m_pcHydraulicComponents->GetHydraulicComponent(i-1)->SetVisibility(FALSE);
			SetVisibility(i, FALSE);
		}

		// set cColor
		SetRow(i);
		SetCol(2);
		unsigned long cColor = (m_pcHydraulicComponents->GetHydraulicComponent(i-1)->GetColor() != 0) ? m_pcHydraulicComponents->GetHydraulicComponent(i-1)->GetColor() : 1;
		SetCellBackColor(cColor);
		SetColor(i, m_pcHydraulicComponents->GetHydraulicComponent(i-1)->GetColor());
	}
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CHydraulicComponentsGeneralGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{
	ASSERT (KeyAscii != NULL);
	if (GetCol() == 1)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);

		SetCellPictureAlignment(4);

		if (GetVisibility(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibility(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibility(GetRow(), TRUE);			
		}
	}
	if (GetCol() == 2)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			unsigned long cColor = (dlg.GetColor() != 0) ? dlg.GetColor() : 1;
			SetCellBackColor(cColor);
			SetColor(GetRow(), dlg.GetColor());
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CHydraulicComponentsGeneralGrid::OnDblClickGrid() 
{
	short i = 13;
	OnKeyPressGrid(&i); // Simulate a return
}
