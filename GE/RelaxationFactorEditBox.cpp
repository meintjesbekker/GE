/*--------------------------------------------------------------------------*/
/*						RelaxationFactorEditBox.cpp 						*/
/*                            												*/
/*	Purpose	: Edit box for relaxation factor.                      			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.3 "Average".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "RelaxationFactorEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                												*/
/*--------------------------------------------------------------------------*/
CRelaxationFactorEditBox::CRelaxationFactorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                												*/
/*--------------------------------------------------------------------------*/
CRelaxationFactorEditBox::~CRelaxationFactorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                 												*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CRelaxationFactorEditBox, CEdit)
	//{{AFX_MSG_MAP(CRelaxationFactorEditBox)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnChar                     												*/
/*--------------------------------------------------------------------------*/
void CRelaxationFactorEditBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// ignore enter key
	if (nChar != 13)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/*--------------------------------------------------------------------------*/
/* OnKeyDown                   												*/
/*--------------------------------------------------------------------------*/
void CRelaxationFactorEditBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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