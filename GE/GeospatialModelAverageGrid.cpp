/*--------------------------------------------------------------------------*/
/*						GeospatialModelAverageGrid.cpp 						*/
/*                            												*/
/*	Purpose	: Grid which contains average, decimate, reduction, smooth,     */
/*			  iterations and relaxation fields.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelAverageGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction		    				                                    */
/*--------------------------------------------------------------------------*/
CGeospatialModelAverageGrid::CGeospatialModelAverageGrid()
{
	m_pcModel = NULL;
	m_pcGeospatialModel = NULL;
	m_lBorderWidth = 0;
	m_lBorderHeight = 0;
	m_iNumberOfLogPixelsX = 0;
	m_iNumberOfLogPixelsY = 0;
}

/*--------------------------------------------------------------------------*/
/* Destruction 		    				                                    */
/*--------------------------------------------------------------------------*/
CGeospatialModelAverageGrid::~CGeospatialModelAverageGrid()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map 		    				                                    */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelAverageGrid, CWnd)
	//{{AFX_MSG_MAP(CGeospatialModelAverageGrid)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Events Map  		    				                                    */
/*--------------------------------------------------------------------------*/
BEGIN_EVENTSINK_MAP(CGeospatialModelAverageGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CGeospatialModelAverageGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CGeospatialModelAverageGrid, -603 /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CGeospatialModelAverageGrid, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CGeospatialModelAverageGrid, 72 /* LeaveCell */, OnLeaveCellGrid, VTS_NONE)
END_EVENTSINK_MAP()

/*--------------------------------------------------------------------------*/
/* InitializeGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::InitializeGrid()
{
	m_bAverageArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_bDecimateArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_fTargetReductionArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_bSmoothArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_fRelaxationFactorArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	m_fIterationsArray.SetSize(m_pcModel->GetNumberOfLayers(), 1);
	SetCols(7);
	SetRows(m_pcModel->GetNumberOfLayers()+1);

	// column width
	SetColWidth(0, int(GetColWidth(0)));
	SetColWidth(1, int(GetColWidth(1)));
	SetColWidth(2, int(GetColWidth(2)));
	SetColWidth(3, int(GetColWidth(3)));
	SetColWidth(4, int(GetColWidth(4)));
	SetColWidth(5, int(GetColWidth(5)));
	SetColWidth(6, int(GetColWidth(6)));

	// column 0
	SetRow(0);
	SetCol(0);
	SetCellAlignment(4);
	SetTextArray(0, "Layer");

	// column 1
	SetRow(0);
	SetCol(1);
	SetCellAlignment(4);
	SetTextArray(1, "Average");

	// column 2
	SetRow(0);
	SetCol(2);
	SetCellAlignment(4);
	SetTextArray(2, "Decimate");

	// column 3
	SetRow(0);
	SetCol(3);
	SetCellAlignment(4);
	SetTextArray(3, "Reduction");

	// column 4
	SetRow(0);
	SetCol(4);
	SetCellAlignment(4);
	SetTextArray(4, "Smooth");

	// column 5
	SetRow(0);
	SetCol(5);
	SetCellAlignment(4);
	SetTextArray(5, "Iterations");

	// column 6
	SetRow(0);
	SetCol(6);
	SetCellAlignment(4);
	SetTextArray(6, "Relaxation");

	CString str;
	for (int iLayer = 1; iLayer <= m_pcModel->GetNumberOfLayers(); iLayer++)
	{
		// iLayer labels
		str.Format("%i", iLayer);
		SetTextArray(7*iLayer, str);

		// bDecimate      
		SetRow(iLayer);
		SetCol(2);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetDecimate())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetDecimate(iLayer, TRUE);
			SetAverage(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetDecimate(iLayer, FALSE);
		}
		str.Format("%1.2f", m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetTargetReduction());
		SetTextArray(7 * iLayer + 3, str);
		SetTargetReduction(iLayer, m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetTargetReduction());

		// smooth        
		SetRow(iLayer);
		SetCol(4);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetSmooth())
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetSmooth(iLayer, TRUE);
			SetAverage(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetSmooth(iLayer, FALSE);
		}
		str.Format("%i", m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetNumberOfIterations());
		SetTextArray(7 * iLayer + 5, str);
		SetIterations(iLayer, m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetNumberOfIterations());
		str.Format("%1.3f", m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetRelaxationFactor());
		SetTextArray(7 * iLayer + 6, str);
		SetRelaxationFactor(iLayer, m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetRelaxationFactor());

		// bAverage        
		SetRow(iLayer);
		SetCol(1);
		SetCellPictureAlignment(4);
		if (m_pcGeospatialModel->m_pLayerArray.GetAt(iLayer-1)->GetAverage() 
			|| GetSmooth(iLayer) 
			|| GetDecimate(iLayer))
		{
			m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetAverage(iLayer, TRUE);
		}
		else
		{
			m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetAverage(iLayer, FALSE);
		}
	}
}

/*--------------------------------------------------------------------------*/
/* PreSubclassWindow					                                    */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::PreSubclassWindow() 
{
	// Calculate border size
	SetRow(0);
	SetCol(0);
	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// To convert grid rect from twips to DC units. We need pixels per inch
	CDC* pDC = GetDC();
	m_iNumberOfLogPixelsX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_iNumberOfLogPixelsY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	// Create invisible edit controls
	// target reduction
	m_cTargetReductionEdit.Create(	WS_CHILD|ES_WANTRETURN, 
									CRect(0,0,0,0), 
									this, 
									GetDlgCtrlID());

	// iterations
	m_cIterationsEdit.Create(WS_CHILD|ES_WANTRETURN, 
							 CRect(0,0,0,0), 
							 this, 
							 GetDlgCtrlID());
	
	// relaxation factor
	m_cRelaxationFactorEdit.Create(	WS_CHILD|ES_WANTRETURN, 
 									CRect(0,0,0,0), 
									this, 
									GetDlgCtrlID());
}

/*--------------------------------------------------------------------------*/
/* OnGetDlgCode                                                             */
/*--------------------------------------------------------------------------*/
UINT CGeospatialModelAverageGrid::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;	
}

/*--------------------------------------------------------------------------*/
/* OnSetFocus                                                               */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::OnSetFocus(CWnd* pOldWnd) 
{
	CMSFlexGrid::OnSetFocus(pOldWnd);
	OnLeaveCellGrid();
}

/*--------------------------------------------------------------------------*/
/* OnKeyPressGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	ASSERT (KeyAscii != NULL);
	
	// column 1
	if (GetCol() == 1)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetAverage(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetAverage(GetRow(), FALSE);
			SetSmooth(GetRow(), FALSE);

			// column 2
			SetCol(2);
			SetCellPictureAlignment(4);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetCol(1);
			SetDecimate(GetRow(), FALSE);
			
			// column 4
			SetCol(4);
			SetCellPictureAlignment(4);
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetCol(1);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetAverage(GetRow(), TRUE);
		}
	}

	// column 2
	if (GetCol() == 2)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetDecimate(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetDecimate(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetDecimate(GetRow(), TRUE);
			SetAverage(GetRow(), TRUE);			
			SetCol(1);
			SetCellPictureAlignment(4);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetCol(2);
		}
	}

	// column 3
	if (GetCol() == 3)
	{
		m_cTargetReductionEdit.SetWindowText(GetText());
		if (*KeyAscii == 13)
			m_cTargetReductionEdit.SetSel(0,-1);
		else
		{
			char buf[] = " ";
			buf[0] = (char)*KeyAscii;
			m_cTargetReductionEdit.SetSel(-1, -1);
			m_cTargetReductionEdit.ReplaceSel(buf);
		}
			
		// adjust for border heigth and convert from twips to screen units
		m_cTargetReductionEdit.MoveWindow(	((GetCellLeft() - m_lBorderWidth) * m_iNumberOfLogPixelsX) / 1440,
											((GetCellTop() - m_lBorderHeight) * m_iNumberOfLogPixelsY) / 1440,
											(GetCellWidth()* m_iNumberOfLogPixelsX) / 1440, 
											(GetCellHeight()* m_iNumberOfLogPixelsY) / 1440, FALSE);
		m_cTargetReductionEdit.ShowWindow(SW_SHOW);
		m_cTargetReductionEdit.SetFocus();
	}

	// column 4
	if (GetCol() == 4)
	{
		m_cPictureCheck.CreateFromBitmap(IDB_BITMAP_CHECK);
		m_cPictureUnCheck.CreateFromBitmap(IDB_BITMAP_UNCHECK);
		SetCellPictureAlignment(4);
		if (GetSmooth(GetRow()))
		{
			SetRefCellPicture(m_cPictureUnCheck.GetPictureDispatch());
			SetSmooth(GetRow(), FALSE);
		}
		else
		{
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetSmooth(GetRow(), TRUE);
			SetAverage(GetRow(), TRUE);
			SetCol(1);
			SetCellPictureAlignment(4);
			SetRefCellPicture(m_cPictureCheck.GetPictureDispatch());
			SetCol(4);
		}
	}

	// column 5
	if (GetCol() == 5)
	{
		m_cIterationsEdit.SetWindowText(GetText());
		if (*KeyAscii == 13)
			m_cIterationsEdit.SetSel(0, -1);
		else
		{
			char buf[] = " ";
			buf[0] = (char)*KeyAscii;
			m_cIterationsEdit.SetSel(-1, -1);
			m_cIterationsEdit.ReplaceSel(buf);
		}
			
		// adjust for border heigth and convert from twips to screen units
		m_cIterationsEdit.MoveWindow(	((GetCellLeft() - m_lBorderWidth) * m_iNumberOfLogPixelsX) / 1440, 
										((GetCellTop() - m_lBorderHeight) * m_iNumberOfLogPixelsY) / 1440,
										(GetCellWidth()* m_iNumberOfLogPixelsX) / 1440, 
										(GetCellHeight()* m_iNumberOfLogPixelsY) / 1440, FALSE);
		m_cIterationsEdit.ShowWindow(SW_SHOW);
		m_cIterationsEdit.SetFocus();
	}

	// column 6
	if (GetCol() == 6)
	{
		m_cRelaxationFactorEdit.SetWindowText(GetText());
		if (*KeyAscii == 13)
			m_cRelaxationFactorEdit.SetSel(0,-1);
		else
		{
			char buf[] = " ";
			buf[0] = (char)*KeyAscii;
			m_cRelaxationFactorEdit.SetSel(-1,-1);
			m_cRelaxationFactorEdit.ReplaceSel(buf);
		}
			
		// adjust for border heigth and convert from twips to screen units
		m_cRelaxationFactorEdit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_iNumberOfLogPixelsX)/1440, 
												((GetCellTop() - m_lBorderHeight) * m_iNumberOfLogPixelsY)/1440,
												(GetCellWidth()* m_iNumberOfLogPixelsX)/1440, 
												(GetCellHeight()* m_iNumberOfLogPixelsY)/1440, FALSE);
		m_cRelaxationFactorEdit.ShowWindow(SW_SHOW);
		m_cRelaxationFactorEdit.SetFocus();
	}
}

/*--------------------------------------------------------------------------*/
/* OnDblClickGrid                                                           */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::OnDblClickGrid() 
{
	short i = 13;
	OnKeyPressGrid(&i); // simulate a return
}

/*--------------------------------------------------------------------------*/
/* OnLeaveCellGrid                                                          */
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGrid::OnLeaveCellGrid() 
{
	// check to see if edit is visible
	BOOL bVisible = ::GetWindowLong(m_cTargetReductionEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cTargetReductionEdit.GetWindowText(cStr);
		if (float(atof(cStr)) < 0 || float(atof(cStr)) > 1)
		{
			SetText("");
			m_cTargetReductionEdit.ShowWindow(SW_HIDE);
			MessageBox(_T("Please enter a value from 0 to 1."), "Number of Iterations", MB_ICONEXCLAMATION);
		}
		else
		{
			SetText(cStr);
			SetTargetReduction(GetRow(), float(atof(cStr)));
			m_cTargetReductionEdit.SetWindowText("");
			m_cTargetReductionEdit.ShowWindow(SW_HIDE);
		}
	}
	bVisible = ::GetWindowLong(m_cIterationsEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cIterationsEdit.GetWindowText(cStr);
		if (float(atof(cStr)) < 0 || float(atof(cStr)) > 100)
		{
			SetText("");
			m_cIterationsEdit.ShowWindow(SW_HIDE);
			MessageBox(_T("Please enter a value from 0 to 100."), "Number of Iterations", MB_ICONEXCLAMATION);
		}
		else
		{
			SetText(cStr);
			SetIterations(GetRow(), float(atof(cStr)));
			m_cIterationsEdit.SetWindowText("");
			m_cIterationsEdit.ShowWindow(SW_HIDE);
		}
	}	
	bVisible = ::GetWindowLong(m_cRelaxationFactorEdit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;
	if (bVisible)
	{
		CString cStr;
		m_cRelaxationFactorEdit.GetWindowText(cStr);
		if (float(atof(cStr)) < 0 || float(atof(cStr)) > 1)
		{
			SetText("");
			m_cRelaxationFactorEdit.ShowWindow(SW_HIDE);
			MessageBox(_T("Please enter a value from 0 to 1."), "Opacity", MB_ICONEXCLAMATION);
		}
		else
		{
			SetText(cStr);
			SetRelaxationFactor(GetRow(), float(atof(cStr)));
			m_cRelaxationFactorEdit.SetWindowText("");
			m_cRelaxationFactorEdit.ShowWindow(SW_HIDE);
		}
	}	
}