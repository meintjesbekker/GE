/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorGrid.cpp 						*/
/*                            												*/
/*	Purpose	: Grid which contains contour and color fields.                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "MT3DMSContourAndColorGrid.h"
#include "ColorLevelDlg.h"
#include "ColorSpectrumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorGrid::CMT3DMSContourAndColorGrid()
{
	m_lBorderWidth = 0;
	m_lBorderHeight = 0;
	m_iLogPixelsX = 0;
	m_iLogPixelsY = 0;
	m_iRowSelected = 1;
	m_pcMT3DMSContourAndColorTable = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorGrid::~CMT3DMSContourAndColorGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSContourAndColorGrid, CWnd)
	//{{AFX_MSG_MAP(CMT3DMSContourAndColorGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CMT3DMSContourAndColorGrid, CMSFlexGrid)
	//{{AFX_EVENTSINK_MAP(CColorGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CMT3DMSContourAndColorGrid, -600 /* Click */, OnClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CMT3DMSContourAndColorGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CMT3DMSContourAndColorGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CMT3DMSContourAndColorGrid, 72   /* LeaveCell */, OnLeaveCellGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* GetSize                                                                  */
/*--------------------------------------------------------------------------*/
int CMT3DMSContourAndColorGrid::GetSize()
{
	return m_pcMT3DMSContourAndColorTable->GetSize();
}

/*--------------------------------------------------------------------------*/
/* OnInitializeGrid                                                         */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::InitializeGrid(CMT3DMSContourAndColorTable* pcMT3DMSContourAndColorTable)
{
	m_pcMT3DMSContourAndColorTable =  pcMT3DMSContourAndColorTable;
	SetCols(3);
	SetFixedCols(1);
	SetRows(m_pcMT3DMSContourAndColorTable->GetSize() + 1);
	SetFixedRows(1);

	// column width
	SetColWidth(0, int(GetColWidth(0) / 3));
	SetColWidth(1, int(GetColWidth(1) * 1.6));
	SetColWidth(2, int(GetColWidth(2)));
	
	// initialize headers
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Contour...");
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Color...");
	for (int i = 1; i <= m_pcMT3DMSContourAndColorTable->GetSize(); i++)
	{
		SetCol(2);
		SetRow(i);
		unsigned long color = (m_pcMT3DMSContourAndColorTable->GetColor(i - 1) != 0) ? m_pcMT3DMSContourAndColorTable->GetColor(i - 1) : 1;
		SetCellBackColor(color);
		SetCol(1);
		SetRow(i);
		CString str;
		str.Format("%1.5G", m_pcMT3DMSContourAndColorTable->GetValue(i - 1));
		SetText(str);
	}

	// selected row
	SetRow(m_iRowSelected);
	SetCol(0);
	SetCellPictureAlignment(4);
	m_cPictureHolder.CreateFromBitmap(IDB_BITMAP_SELECT);
	SetRefCellPicture(m_cPictureHolder.GetPictureDispatch());
}

/*--------------------------------------------------------------------------*/
/* Remove      																*/
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::Remove()
{
	m_pcMT3DMSContourAndColorTable->RemoveMT3DMSContourAndColorFromArray(m_iRowSelected - 1);
	UpdateGrid();
}

/*--------------------------------------------------------------------------*/
/* Add         																*/
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::Add(CMT3DMSContourAndColorRow* pcMT3DMSContourAndColorRow)
{
	m_pcMT3DMSContourAndColorTable->AddMT3DMSContourAndColorRowToArray(pcMT3DMSContourAndColorRow);
	UpdateGrid();
}

/*--------------------------------------------------------------------------*/
/* PreSubclassWindow                                                        */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::PreSubclassWindow() 
{
	//Calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// To convert grid rect from twips to DC units. We need pixels per inch
	CDC* pDC = GetDC();
	m_iLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_iLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	//Create invisible edit control
	m_cEdit.Create(	WS_CHILD|ES_WANTRETURN, 
							CRect(0,0,0,0), 
							this, 
							GetDlgCtrlID());
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CMT3DMSContourAndColorGrid::OnGetDlgCode() 
{
	return CWnd::OnGetDlgCode();
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
}

/*--------------------------------------------------------------------------*/
/* OnClickGrid                                                              */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::OnClickGrid()
{
	if (GetMouseCol() == 0)
	{
		int newSelection = GetMouseRow();

		// unselect previous row
		SetRow(m_iRowSelected);
		SetCol(0);
		SetCellPictureAlignment(4);
		m_cPictureHolder.CreateFromBitmap(IDB_BITMAP_UNSELECT);
		SetRefCellPicture(m_cPictureHolder.GetPictureDispatch());

		// select new row
		SetRow(newSelection);
		SetCol(0);
		SetCellPictureAlignment(4);
		m_cPictureHolder.CreateFromBitmap(IDB_BITMAP_SELECT);
		SetRefCellPicture(m_cPictureHolder.GetPictureDispatch());
		SetCol(1);
		m_iRowSelected = newSelection;
	}

	if (GetMouseRow() == 0 && GetMouseCol() == 1)
	{
		CColorLevelDlg dlg;
		dlg.SetInterval(m_pcMT3DMSContourAndColorTable->GetInterval());
		dlg.SetMinimumScalarValue(m_pcMT3DMSContourAndColorTable->GetMinimumScalarValue());
		dlg.SetMaximumScalarValue(m_pcMT3DMSContourAndColorTable->GetMaximumScalarValue());
		if (dlg.DoModal() == IDOK)
		{
			m_pcMT3DMSContourAndColorTable->SetMinimumScalarValue(dlg.GetMinimumScalarValue());
			m_pcMT3DMSContourAndColorTable->SetMaximumScalarValue(dlg.GetMaximumScalarValue());
			m_pcMT3DMSContourAndColorTable->SetInterval(dlg.GetInterval());
			m_pcMT3DMSContourAndColorTable->CreateValueAndColorRows();
			UpdateGrid();
		}
	}

	if (GetMouseRow() == 0 && GetMouseCol() == 2)
	{
		CColorSpectrumDlg dlg;
		dlg.SetMinimumColor(m_pcMT3DMSContourAndColorTable->GetMinimumScalarColor());
		dlg.SetMaximumColor(m_pcMT3DMSContourAndColorTable->GetMaximumScalarColor());
		if (dlg.DoModal() == IDOK)
		{
			m_pcMT3DMSContourAndColorTable->SetMinimumScalarColor(dlg.GetMinimumColor());
			m_pcMT3DMSContourAndColorTable->SetMaximumScalarColor(dlg.GetMaximumColor());
			for (int i = 1; i <= m_pcMT3DMSContourAndColorTable->GetNumberOfValuesAndColors(); i++)
			{
				SetRow(i);
				SetCol(2);
				m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(i - 1)->SetColor(dlg.GetSpectrumColor(m_pcMT3DMSContourAndColorTable->GetNumberOfValuesAndColors(), i));
				unsigned long color = (m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(i - 1)->GetColor() != 0) ? m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(i - 1)->GetColor() : 1;
				SetCellBackColor(color);
			}					
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	ASSERT (KeyAscii != NULL);
	if (GetCol() == 1)
	{
		m_cEdit.SetWindowText(GetText());
		if (*KeyAscii == 13)
			m_cEdit.SetSel(0,-1);
		else
		{
			char buf[] = " ";
			buf[0] = (char)*KeyAscii;
			m_cEdit.SetSel(-1,-1);
			m_cEdit.ReplaceSel(buf);
		}
			
		// adjust for border heigth and convert from twips to screen units
		m_cEdit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_iLogPixelsX)/1440, 
								((GetCellTop() - m_lBorderHeight) * m_iLogPixelsY)/1440,
								(GetCellWidth()* m_iLogPixelsX)/1440, 
								(GetCellHeight()* m_iLogPixelsY)/1440, 
								FALSE);
		m_cEdit.ShowWindow(SW_SHOW);
		m_cEdit.SetFocus();
	}
	if (GetCol() == 2)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			unsigned long color = (dlg.GetColor() != 0) ? dlg.GetColor() : 1;
			SetCellBackColor(color);
			m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(GetRow() - 1)->SetColor(dlg.GetColor());
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::OnDblClickGrid() 
{
	short i = 13;
	if (GetMouseCol() > 0)
		OnKeyPressGrid(&i); //Simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnLeaveCellGrid                                                          */
/*--------------------------------------------------------------------------*/
void  CMT3DMSContourAndColorGrid::OnLeaveCellGrid() 
{
	// check to see if edit is visible
	BOOL bVisible = ::GetWindowLong(m_cEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cEdit.GetWindowText(cStr);
		SetText(cStr);
		m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(GetRow() - 1)->SetValue(float(atof(cStr)));
		m_cEdit.SetWindowText("");
		m_cEdit.ShowWindow(SW_HIDE);
	}	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateGrid																*/
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorGrid::UpdateGrid()
{
	// unselect previous row
	SetRow(m_iRowSelected);
	SetCol(0);
	SetCellPictureAlignment(4);
	m_cPictureHolder.CreateFromBitmap(IDB_BITMAP_UNSELECT);
	SetRefCellPicture(m_cPictureHolder.GetPictureDispatch());
	SetCols(3);
	SetRows(m_pcMT3DMSContourAndColorTable->GetNumberOfValuesAndColors() + 1);

	// select first row
	m_iRowSelected = 1;
	SetRow(m_iRowSelected);
	SetCol(0);
	SetCellPictureAlignment(4);
	m_cPictureHolder.CreateFromBitmap(IDB_BITMAP_SELECT);
	SetRefCellPicture(m_cPictureHolder.GetPictureDispatch());
	SetCol(1);

	// initialize headers
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Contour...");
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Color...");
	CString str;
	for (int index = 1; index <= m_pcMT3DMSContourAndColorTable->GetNumberOfValuesAndColors(); index++)
	{
		// contour 
		str.Format("%1.5G", m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(index - 1)->GetValue());
		SetTextArray(3 * index + 1, str);

		// colors
		SetRow(index);
		SetCol(2);
		unsigned long color = (m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(index - 1)->GetColor() != 0) ? m_pcMT3DMSContourAndColorTable->GetContourAndColorRow(index - 1)->GetColor() : 1;
		SetCellBackColor(color);
	}
}