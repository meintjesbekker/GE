/*--------------------------------------------------------------------------*/
/*						GeospatialModelGeneralGrid.cpp 						*/
/*                            												*/
/*	Purpose	: Grid which contains visible, color and opacity.               */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "ColorSpectrum.h"
#include "ColorSpectrumDlg.h"

#include "GeospatialModelGeneralGrid.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                												*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralGrid::CGeospatialModelGeneralGrid()
{
	m_pcModel = NULL;
	m_pcGeospatialModel = NULL;
	m_lBorderWidth = 0;
	m_lBorderHeight = 0;
	m_iNumberOfLogPixelsX = 0;
	m_iNumberOfLogPixelsY = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralGrid::~CGeospatialModelGeneralGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelGeneralGrid, CMSFlexGrid)
	//{{AFX_MSG_MAP(CGeospatialModelGeneralGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map                   											*/
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CGeospatialModelGeneralGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CGeospatialModelGeneralGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CGeospatialModelGeneralGrid, -600 /* Click */, OnClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CGeospatialModelGeneralGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CGeospatialModelGeneralGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CGeospatialModelGeneralGrid, 72 /* LeaveCell */, OnUpdateGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::InitializeGrid()
{
	m_bVisibleArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_cColorArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_fOpacityArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	SetCols(4);
	SetRows(m_pcModel->GetNumberOfLayers() + 1);

	// column width
	SetColWidth(0, int(GetColWidth(0)));
	SetColWidth(1, int(GetColWidth(1)));
	SetColWidth(2, int(GetColWidth(2)));
	SetColWidth(3, int(GetColWidth(3)));

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

	// column 2
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Color...");

	// column 3
	SetRow(0);
	SetCol(3);
	SetCellAlignment(4);
	SetTextArray(3, "Opacity");
	
	// repeat for each layer
	CString str;
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		// iLayer labels
		str.Format("%i", iLayer);
		SetTextArray(4 * iLayer, str);

		// set visibility
		SetRow(iLayer);
		SetCol(1);
		SetCellPictureAlignment(4);

		// if visible
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetVisibility())
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

		// create default colors
		SetRow(iLayer);
		SetCol(2);
		unsigned long cColor = (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetColor() != 0) ? m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetColor() : 1;
		SetCellBackColor(cColor);
		SetColor(iLayer, m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetColor());

		// create default fOpacity
		str.Format("%1.1f", m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetOpacity());
		SetTextArray(4*iLayer+3, str);
		SetOpacity(iLayer, m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetOpacity());
	}
}

/*--------------------------------------------------------------------------*/
/* PreSubClassWindow                                                        */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::PreSubclassWindow() 
{
	// calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// convert grid rect from twips to DC units, pixels per inch are needed
	CDC* pDC = GetDC();
	m_iNumberOfLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_iNumberOfLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	// create invisible edit control
	m_cOpacityEdit.Create(WS_CHILD|ES_WANTRETURN, 
								CRect(0,0,0,0), 
								this, 
								GetDlgCtrlID());
}

/*--------------------------------------------------------------------------*/
/* OnDlgCode                                                                */
/*--------------------------------------------------------------------------*/
UINT CGeospatialModelGeneralGrid::OnGetDlgCode() 
{	
	return DLGC_WANTALLKEYS;
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CMSFlexGrid::OnSetFocus(pOldWnd);
	OnUpdateGrid();	
}

/*--------------------------------------------------------------------------*/
/* OnClickGrid                                                              */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::OnClickGrid() 
{
	if (GetMouseRow() == 0 && GetMouseCol() == 2)
	{
		CColorSpectrumDlg dlg;
		dlg.SetMinimumColor(m_pcGeospatialModel->GetMinimumColor());
		dlg.SetMaximumColor(m_pcGeospatialModel->GetMaximumColor());
		if (dlg.DoModal() == IDOK)
		{
			m_pcGeospatialModel->SetMinimumColor(dlg.GetMinimumColor());
			m_pcGeospatialModel->SetMaximumColor(dlg.GetMaximumColor());
			CColorSpectrum colorSpectrum(dlg.GetMinimumColor(), dlg.GetMaximumColor());
			for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
			{
				SetRow(iLayer);
				SetCol(2);
				unsigned long cColor = (colorSpectrum.GetSpectrumColor(m_pcModel->GetNumberOfLayers(), iLayer) != 0) ? colorSpectrum.GetSpectrumColor(m_pcModel->GetNumberOfLayers(), iLayer) : 1;
				SetCellBackColor(cColor);
				SetColor(iLayer, colorSpectrum.GetSpectrumColor(m_pcModel->GetNumberOfLayers(), iLayer));
			}					
		}
	}
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	ASSERT (KeyAscii != NULL);
	
	// column 1
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

	// column 2
	if (GetCol() == 2)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			unsigned long cColor = (dlg.GetColor() != 0) ? dlg.GetColor() : 1; // cColor = 0, not accepted by MSFlexGrid
			SetCellBackColor(cColor);
			SetColor(GetRow(), dlg.GetColor());
		}
	}

	// column 3
	if (GetCol() == 3)
	{
		m_cOpacityEdit.SetWindowText(GetText());
		if (*KeyAscii == 13)
			m_cOpacityEdit.SetSel(0,-1);
		else
		{
			char buf[] = " ";
			buf[0] = (char)*KeyAscii;
			m_cOpacityEdit.SetSel(-1,-1);
			m_cOpacityEdit.ReplaceSel(buf);
		}
			
		// adjust for border heigth and convert from twips to screen units
		m_cOpacityEdit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_iNumberOfLogPixelsX)/1440,
										((GetCellTop() - m_lBorderHeight) * m_iNumberOfLogPixelsY)/1440,
										(GetCellWidth()* m_iNumberOfLogPixelsX)/1440,
										(GetCellHeight()* m_iNumberOfLogPixelsY)/1440,
										FALSE);
		m_cOpacityEdit.ShowWindow(SW_SHOW);
		m_cOpacityEdit.SetFocus();
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::OnDblClickGrid() 
{
	short i = 13;
	OnKeyPressGrid(&i); // simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnUpdateGrid                                                             */
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGrid::OnUpdateGrid() 
{
	// check to see if m_cOpacityEdit is bVisible
	BOOL bVisible = ::GetWindowLong(m_cOpacityEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cOpacityEdit.GetWindowText(cStr);
		if (float(atof(cStr)) < 0 || float(atof(cStr)) > 1)
		{
			SetText("");
			m_cOpacityEdit.ShowWindow(SW_HIDE);
			MessageBox(_T("Please enter a value from 0 to 1."), "Opacity", MB_ICONEXCLAMATION);
		}
		else
		{
			SetText(cStr);
			SetOpacity(GetRow(), float(atof(cStr)));
			m_cOpacityEdit.SetWindowText("");
			m_cOpacityEdit.ShowWindow(SW_HIDE);
		}
	}	
}