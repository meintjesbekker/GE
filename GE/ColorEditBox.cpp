/*--------------------------------------------------------------------------*/
/*							ColorEditBox.cpp  								*/
/*                            												*/
/*	Purpose	: Edit box to change color on grid.   			                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                        						*/
/*--------------------------------------------------------------------------*/
CColorEditBox::CColorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                        						*/
/*--------------------------------------------------------------------------*/
CColorEditBox::~CColorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                        						*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CColorEditBox, CEdit)
	//{{AFX_MSG_MAP(CColorEditBox)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnChar                                             						*/
/*--------------------------------------------------------------------------*/
void CColorEditBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// ignore enter key
	if (nChar != 13)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/*--------------------------------------------------------------------------*/
/* OnKeyDown                                          						*/
/*--------------------------------------------------------------------------*/
void CColorEditBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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