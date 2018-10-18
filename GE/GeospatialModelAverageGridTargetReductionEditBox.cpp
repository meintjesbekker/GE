/*--------------------------------------------------------------------------*/
/*			GeospatialModelAverageGridTargetReductionEditBox.cpp 			*/
/*                            												*/
/*	Purpose	: Edit box for target reduction.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelAverageGridTargetReductionEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                        						*/
/*--------------------------------------------------------------------------*/
CGeospatialModelAverageGridTargetReductionEditBox::CGeospatialModelAverageGridTargetReductionEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                         						*/
/*--------------------------------------------------------------------------*/
CGeospatialModelAverageGridTargetReductionEditBox::~CGeospatialModelAverageGridTargetReductionEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelAverageGridTargetReductionEditBox, CEdit)
	//{{AFX_MSG_MAP(CGeospatialModelAverageGridTargetReductionEditBox)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnChar                                              						*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGridTargetReductionEditBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar != 13) // ignore Enter key
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/*--------------------------------------------------------------------------*/
/* OnKeyDown                                           						*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelAverageGridTargetReductionEditBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// esc key, cancel
	if (nChar == 27)
	{
		SetWindowText("");
		ShowWindow(SW_HIDE);
		GetParent()->SetFocus();
	}
	else 
	// enter key, ok
	if (nChar == 13)
		GetParent()->SetFocus();
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}