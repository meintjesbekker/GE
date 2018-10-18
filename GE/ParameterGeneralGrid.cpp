/*--------------------------------------------------------------------------*/
/*						ParameterGeneralGrid.cpp							*/
/*                            												*/
/*	Purpose	: Grid which contains layer and visible fields.                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.8.1 "General".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ParameterGeneralGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CParameterGeneralGrid::CParameterGeneralGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
CParameterGeneralGrid::~CParameterGeneralGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CParameterGeneralGrid, CWnd)
	//{{AFX_MSG_MAP(CParameterGeneralGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CParameterGeneralGrid, CWnd)
    //{{AFX_EVENTSINK_MAP(CParameterGeneralGrid)
	ON_EVENT(CParameterGeneralGrid, IDC_MSFLEXGRID, -601 /* DblClick */, OnDblClickMsFlexGrid, VTS_NONE)
	ON_EVENT(CParameterGeneralGrid, IDC_MSFLEXGRID, -603 /* KeyPress */, OnKeyPressMsFlexGrid, VTS_PI2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CParameterGeneralGrid::InitializeGrid()
{
	m_bVisible.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	SetCols(2);
	SetRows(m_pcModel->GetNumberOfLayers() + 1);

	// column width
	SetColWidth(0, int(GetColWidth(0)));
	SetColWidth(1, int(GetColWidth(1)));

	// column 0
  	SetRow(0);
	SetCol(0);
	SetCellAlignment(4);
	SetTextArray(0, "Layer");

	// column 1
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Visible");
	CString str;
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		// iLayer labels
		str.Format("%i", iLayer);
		SetTextArray(2*iLayer, str);

		// set visibility
		SetRow(iLayer);
		SetCol(1);
		SetCellPictureAlignment(4);
		if (m_pcParameter->m_bVisibleLayersArray.GetAt(iLayer-1))
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibility(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibility(iLayer, FALSE);
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickMsFlexGrid                                                     */
/*--------------------------------------------------------------------------*/
void CParameterGeneralGrid::OnDblClickMsFlexGrid() 
{
	short i = 13;
	OnKeyPressMsFlexGrid(&i); // Simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressMsFlexGrid                                                     */
/*--------------------------------------------------------------------------*/
void CParameterGeneralGrid::OnKeyPressMsFlexGrid(short FAR* KeyAscii) 
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
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CParameterGeneralGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}