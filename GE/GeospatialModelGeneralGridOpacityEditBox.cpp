/*--------------------------------------------------------------------------*/
/*				GeospatialModelGeneralGridOpacityEditBox.h   				*/
/*                            												*/
/*	Purpose	: Edit box for opacity.											*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3.1 "General".          				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelGeneralGridOpacityEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction																*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralGridOpacityEditBox::CGeospatialModelGeneralGridOpacityEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction																*/
/*--------------------------------------------------------------------------*/
CGeospatialModelGeneralGridOpacityEditBox::~CGeospatialModelGeneralGridOpacityEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map 																*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelGeneralGridOpacityEditBox, CEdit)
	//{{AFX_MSG_MAP(CGeospatialModelGeneralGridOpacityEditBox)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnChar        															*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGridOpacityEditBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar != 13) // ignore Enter key
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

/*--------------------------------------------------------------------------*/
/* OnKeyDown  																*/
/*--------------------------------------------------------------------------*/
void CGeospatialModelGeneralGridOpacityEditBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == 27) // Esc means "Cancel"
	{
		SetWindowText("");
		ShowWindow(SW_HIDE);
		GetParent()->SetFocus();
	}
	else 
	if (nChar == 13) // Enter means "OK"
		GetParent()->SetFocus();
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}