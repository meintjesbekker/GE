/*--------------------------------------------------------------------------*/
/*								ColorGrid.h   								*/
/*                            												*/
/*	Purpose	: Grid which contains interval/s and color. 			        */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorGrid.h"
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
CColorGrid::CColorGrid()
{
	m_pColor = NULL;
	m_lBorderWidth = 0.0;
	m_lBorderHeight = 0.0;
	m_iNumberOfLogPixelsX = 0;
	m_iNumberOfLogPixelsY = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CColorGrid::~CColorGrid()
{
	if (m_pColor != NULL)
		delete m_pColor;
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CColorGrid, CWnd)
	//{{AFX_MSG_MAP(CColorGrid)
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                                                               */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CColorGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CColorGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CColorGrid, -600 /* Click */, OnClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CColorGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CColorGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CColorGrid, 72 /* LeaveCell */, OnLeaveCellGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CColorGrid::InitializeGrid()
{
	SetCols(3);

	// column width
	SetColWidth(0, int(GetColWidth(0)) * 1.6);
	SetColWidth(1, int(GetColWidth(1)) * 1.6);
	SetColWidth(2, int(GetColWidth(2)));

	// set scalar value
	m_cColorTable.SetMinimumScalarValue(m_pColor->m_cColorTable.GetMinimumScalarValue());
	m_cColorTable.SetMaximumScalarValue(m_pColor->m_cColorTable.GetMaximumScalarValue());

	// set scalar color
	m_cColorTable.SetMinimumScalarColor(m_pColor->m_cColorTable.GetMinimumScalarColor());
	m_cColorTable.SetMaximumScalarColor(m_pColor->m_cColorTable.GetMaximumScalarColor());

	// create color table
	m_cColorTable.SetInterval(m_pColor->m_cColorTable.GetInterval());
	m_cColorTable.CreateColorRows();
	for (int i = 0; i < m_cColorTable.GetNumberOfColors(); i++)
		m_cColorTable.GetColorRow(i)->SetColor(m_pColor->m_cColorTable.GetColorRow(i)->GetColor());

	// use functionality of UpdateGrid
	UpdateGrid();
}

/*--------------------------------------------------------------------------*/
/* UpdateGrid                                                               */
/*--------------------------------------------------------------------------*/
void CColorGrid::UpdateGrid()
{
	SetRows(m_cColorTable.GetNumberOfColors() + 1);
	
	// minimum header
	SetRow(0);
	SetCol(0);
	SetCellAlignment(4);
	SetTextArray(0, "Minimum...");

	// maximum header
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Maximum...");

	// color header
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(2, "Color...");

	// assign cell values
	CString str;
	for (int index = 1; index <= m_cColorTable.GetNumberOfColors(); index++)
	{
		// minimum 
		str.Format("%1.5G", m_cColorTable.GetColorRow(index - 1)->GetMinimum());
		SetTextArray(3 * index, str);

		// maximum 
		str.Format("%1.5G", m_cColorTable.GetColorRow(index - 1)->GetMaximum());
		SetTextArray(3 * index + 1, str);

		// colors
		SetRow(index);
		SetCol(2);
		unsigned long color = (m_cColorTable.GetColorRow(index - 1)->GetColor() != 0) ? m_cColorTable.GetColorRow(index - 1)->GetColor() : 1;
		SetCellBackColor(color);
	}
}

/*--------------------------------------------------------------------------*/
/* SetColorPointer                                                          */
/*--------------------------------------------------------------------------*/
void CColorGrid::SetColorPointer(CColor* pColor)
{
	m_pColor = pColor;
}

/*--------------------------------------------------------------------------*/
/* PreSubclassWindow                                                        */
/*--------------------------------------------------------------------------*/
void CColorGrid::PreSubclassWindow() 
{
	// calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// convert grid rect from twips to dc units, need pixels per inch
	CDC* pDC = GetDC();
	m_iNumberOfLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_iNumberOfLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);

	// create edit box
	m_cColorEdit.Create(	WS_CHILD|ES_WANTRETURN,
 							CRect(0, 0, 0, 0),
							this,
							GetDlgCtrlID());
}

/*--------------------------------------------------------------------------*/
/* OnClickGrid                                                              */
/*--------------------------------------------------------------------------*/
void CColorGrid::OnClickGrid() 
{
	// click on minimum or maximum header button
	if (GetMouseRow() == 0 && (GetMouseCol() == 0 || GetMouseCol() == 1))
	{
		CColorLevelDlg dlg;
		dlg.SetInterval(m_cColorTable.GetInterval());
		dlg.SetMinimumScalarValue(m_cColorTable.GetMinimumScalarValue());
		dlg.SetMaximumScalarValue(m_cColorTable.GetMaximumScalarValue());

		// display dialog box
		if (dlg.DoModal() == IDOK)
		{
			m_cColorTable.SetMinimumScalarValue(dlg.GetMinimumScalarValue());
			m_cColorTable.SetMaximumScalarValue(dlg.GetMaximumScalarValue());
			m_cColorTable.SetInterval(dlg.GetInterval());
			m_cColorTable.CreateColorRows();
			UpdateGrid();
		}
	}

	// click on color header button
	if (GetMouseRow() == 0 && GetMouseCol() == 2)
	{
		CColorSpectrumDlg dlg;
		dlg.SetMinimumColor(m_cColorTable.GetMinimumScalarColor());
		dlg.SetMaximumColor(m_cColorTable.GetMaximumScalarColor());

		// display dialog box
		if (dlg.DoModal() == IDOK)
		{
			m_cColorTable.SetMinimumScalarColor(dlg.GetMinimumColor());
			m_cColorTable.SetMaximumScalarColor(dlg.GetMaximumColor());
			for (int i = 1; i <= m_cColorTable.GetNumberOfColors(); i++)
			{
				SetRow(i);
				SetCol(2);
				unsigned long ulColor = (dlg.GetSpectrumColor(m_cColorTable.GetNumberOfColors(), i) != 0) ? dlg.GetSpectrumColor(m_cColorTable.GetNumberOfColors(), i) : 1;
				SetCellBackColor(ulColor);
				m_cColorTable.GetColorRow(i - 1)->SetColor(dlg.GetSpectrumColor(m_cColorTable.GetNumberOfColors(), i));
			}					
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CColorGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	ASSERT (KeyAscii != NULL);
	if (GetCol() == 2)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			unsigned long color = (dlg.GetColor() != 0) ? dlg.GetColor() : 1;
			SetCellBackColor(color);
			m_cColorTable.GetColorRow(GetRow() - 1)->SetColor(dlg.GetColor());
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CColorGrid::OnDblClickGrid() 
{
	short i = 13;
	OnKeyPressGrid(&i); // simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnLeaveCellGrid                                                          */
/*--------------------------------------------------------------------------*/
void  CColorGrid::OnLeaveCellGrid()
{
	// check to see if edit is visible
	BOOL bVisible = ::GetWindowLong(m_cColorEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cColorEdit.GetWindowText(cStr);
		SetText(cStr);
		m_cColorEdit.SetWindowText("");
		m_cColorEdit.ShowWindow(SW_HIDE);
	}
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CColorGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;	
}