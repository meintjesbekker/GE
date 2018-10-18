/*--------------------------------------------------------------------------*/
/*					GeospatialModelVisibleGrid.cpp 							*/
/*                            												*/
/*	Purpose	: Grid which contains top, sides and bottom.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.2 "Visible".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelVisibleGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction																*/
/*--------------------------------------------------------------------------*/
CGeospatialModelVisibleGrid::CGeospatialModelVisibleGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction 																*/
/*--------------------------------------------------------------------------*/
CGeospatialModelVisibleGrid::~CGeospatialModelVisibleGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map 																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelVisibleGrid, CWnd)
	//{{AFX_MSG_MAP(CGeospatialModelVisibleGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map   															*/
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CGeospatialModelVisibleGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CGeospatialModelVisibleGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CGeospatialModelVisibleGrid, -603 /* KeyPress  */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CGeospatialModelVisibleGrid, -601 /* DblClick  */, OnDblClickGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisibleGrid::InitializeGrid()
{
	SetCols(4);
	SetRows(m_pcModel->GetNumberOfLayers() + 1);

	// column width
	SetColWidth(0, int(GetColWidth(0)));
	SetColWidth(1, int(GetColWidth(1)));
	SetColWidth(2, int(GetColWidth(2)));
	SetColWidth(3, int(GetColWidth(3)));

	m_bVisibleTopArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_bVisibleSidesArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_bVisibleBottomArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);

	// column 0
	SetRow(0);
	SetCol(0);
	SetCellAlignment(4);
	SetTextArray(0, "Layer");

	// column 1
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Top");

	// column 2
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Sides");

	// column 3
	SetRow(0);
	SetCol(3);
	SetCellAlignment(4);
	SetTextArray(3, "Bottom");

	// initialize contents
	CString str;
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		// iLayer labels
		str.Format("%i", iLayer);
		SetTextArray(4*iLayer, str);

		// set top visibility
		SetRow(iLayer);
		SetCol(1);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetVisibilityTop())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilityTop(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilityTop(iLayer, FALSE);
		}

		// set sides visibility
		SetRow(iLayer);
		SetCol(2);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetVisibilitySides())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilitySides(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilitySides(iLayer, FALSE);
		}

		// set bottom visibility
		SetRow(iLayer);
		SetCol(3);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetVisibilityBottom())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilityBottom(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilityBottom(iLayer, FALSE);
		}
	}
}

/*--------------------------------------------------------------------------*/
/* PreSubclassWindow														*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisibleGrid::PreSubclassWindow() 
{
	// Calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth	= GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// To convert grid rect from twips to DC units. We need pixels per inch
	CDC* pDC = GetDC();
	m_iNumberOfLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_iNumberOfLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CGeospatialModelVisibleGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisibleGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CMSFlexGrid::OnSetFocus(pOldWnd);
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisibleGrid::OnKeyPressGrid(short FAR* KeyAscii)
{
	ASSERT (KeyAscii != NULL);

	// column 1
	if (GetCol() == 1)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetVisibilityTop(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilityTop(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilityTop(GetRow(), TRUE);			
		}
	}

	// column 2
	if (GetCol() == 2)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetVisibilitySides(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilitySides(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilitySides(GetRow(), TRUE);			
		}
	}

	// column 3
	if (GetCol() == 3)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetVisibilityBottom(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetVisibilityBottom(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetVisibilityBottom(GetRow(), TRUE);			
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelVisibleGrid::OnDblClickGrid()
{
	short i = 13;
	OnKeyPressGrid(&i); // simulate a return
}