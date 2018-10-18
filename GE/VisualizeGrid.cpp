/*--------------------------------------------------------------------------*/
/*							VisualizeGrid.h   								*/
/*                            												*/
/*	Purpose	: Grid which contains visible and object fields.                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "VisualizeGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CVisualizeGrid::CVisualizeGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CVisualizeGrid::~CVisualizeGrid()
{
	for (int i = 0; i < m_pcObjectListArray.GetSize(); i++)
		delete m_pcObjectListArray[i];
	m_pcObjectListArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CVisualizeGrid,  CMSFlexGrid)
	//{{AFX_MSG_MAP(CVisualizeGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CVisualizeGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CVisualizeGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CVisualizeGrid, -603 /* KeyPress  */, OnKeyPressGrid,  VTS_PI2)
	ON_EVENT_REFLECT(CVisualizeGrid, -601 /* DblClick  */, OnDblClickGrid,  VTS_NONE)
	ON_EVENT_REFLECT(CVisualizeGrid, 72   /* LeaveCell */, OnLeaveCellGrid, VTS_NONE)
	ON_EVENT_REFLECT(CVisualizeGrid, 71   /* EnterCell */, OnEnterCellGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeObjectList                                                     */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::InitializeObjectList()
{
	m_iNumberOfObjects = 0;
	m_pcObjectListArray.RemoveAll();
	
	// visualization object
	for (int i = 0; i < m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray.GetSize(); i++)
		AddObjectToList(m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(i)->GetVisibility(), i);
}

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::InitializeGrid()
{
	SetRedraw(FALSE);
	SetRows(1);
	SetCols(2);
	SetRow(0);
	SetCol(0);
	SetCellAlignment(4); // centre
	SetTextArray(0, "Visible");
	SetRow(0);
	SetCol(1);
	SetColWidth(1, int(GetColWidth(0) * 3.8));
	SetCellAlignment(4); // centre
	SetTextArray(1, "Object");
	m_bHighLight = FALSE;
	m_iColumn	= 0;
	m_iRowHighLighted = 0;
	m_iPrevRowHighLighted	= 0;
	InitializeObjectList();
	SetRedraw(TRUE);
}

/*--------------------------------------------------------------------------*/
/* AddObjectToList                                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::AddObjectToList(BOOL bVisible, int iArrayIndex)
{
	SetRedraw(FALSE);
	m_iNumberOfObjects += 1;
	long index = m_iNumberOfObjects;
	COleVariant intVariant(index, VT_I4);
	AddItem(NULL, intVariant);
	CObjectList* object = new CObjectList(bVisible, iArrayIndex);
	m_pcObjectListArray.Add(object);
	m_bHighLight = FALSE;
	SetCol(0);
	SetRow(m_iNumberOfObjects);
	m_iRowHighLighted	= m_iNumberOfObjects;
	SetCellPictureAlignment(4);
	if (bVisible)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
	}
	else
	{
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
	}
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
	
	// visualization object
	SetTextArray(m_iNumberOfObjects * 2 + 1, m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(iArrayIndex)->GetDescription());
	SetRedraw(TRUE);
}

/*--------------------------------------------------------------------------*/
/* RemoveObject                                                             */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::RemoveObject()
{
	// visualization object
	delete m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray[m_pcObjectListArray.GetAt(m_iRowHighLighted-1)->GetIndex()];
	m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray.RemoveAt(m_pcObjectListArray.GetAt(m_iRowHighLighted-1)->GetIndex());
	
	// remove the item from the grid
	RemoveItem(m_iRowHighLighted);
	m_pcObjectListArray.RemoveAt(m_iRowHighLighted - 1);
	m_iNumberOfObjects -= 1;

	// highlight the first row of the grid
	SetRedraw(FALSE);
	SetRow(1);
	SetCol(1);
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
	m_bHighLight = FALSE;
	m_iColumn	= 0;
	SetRow(1);
	SetCol(0);
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
	SetRedraw(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CVisualizeGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CMSFlexGrid::OnSetFocus(pOldWnd);
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_WINDOW)));
}

/*--------------------------------------------------------------------------*/
/* OnKillFocus                                                              */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnKillFocus(CWnd* pNewWnd) 
{
	CMSFlexGrid::OnKillFocus(pNewWnd);
	SetRedraw(FALSE);
	int col = GetCol();
	SetRow(m_iRowHighLighted);
	SetCol(1-col);
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
	SetRow(m_iRowHighLighted);
	SetCol(col);
	SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
	SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
	SetRedraw(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	ASSERT (KeyAscii != NULL);
	if (!m_bHighLight && GetCol() == 0)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		
		// visibility
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

		// visualization object
		m_pcDoc->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(m_pcObjectListArray.GetAt(GetRow()-1)->GetIndex())->SetVisibility(GetVisibility(GetRow()));
	}
	
	// edit visualization object
	if (!m_bHighLight && GetCol() == 1)
	{
		if (m_pcDoc->m_pcVisualization->GetVisualizationObject(m_pcObjectListArray.GetAt(GetRow()-1)->GetIndex())->DoSheetAndPagesForChange())
			InitializeGrid();
		return;
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnDblClickGrid() 
{
	short i = 13;
	OnKeyPressGrid(&i); // simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnLeaveCellGrid                                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnLeaveCellGrid()
{
	if (!m_bHighLight && GetRow() > 0)
		m_iPrevRowHighLighted = GetRow();
}

/*--------------------------------------------------------------------------*/
/* OnEnterCellGrid                                                          */
/*--------------------------------------------------------------------------*/
void CVisualizeGrid::OnEnterCellGrid() 
{
	if (!m_bHighLight && GetRow() > 0)
	{
		m_iColumn = GetCol();
		m_iRowHighLighted = GetRow();
		m_bHighLight = TRUE;
		SetRedraw(FALSE);
		SetRow(m_iPrevRowHighLighted);
		SetCol(0);
		SetCellForeColor(COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
		SetCellBackColor(COLORREF(::GetSysColor(COLOR_WINDOW)));
		SetRow(m_iPrevRowHighLighted);
		SetCol(1);
		SetCellForeColor(COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
		SetCellBackColor(COLORREF(::GetSysColor(COLOR_WINDOW)));
		SetRow(m_iRowHighLighted);
		SetCol(1 - m_iColumn);
		SetCellForeColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHTTEXT)));
		SetCellBackColor(COLORREF(::GetSysColor(COLOR_HIGHLIGHT)));
		SetRow(m_iRowHighLighted);
		SetCol(m_iColumn);
		SetCellForeColor(COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
		SetCellBackColor(COLORREF(::GetSysColor(COLOR_WINDOW)));
		m_bHighLight = FALSE;
		SetRedraw(TRUE);
	}
}