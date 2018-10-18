/*--------------------------------------------------------------------------*/
/*								MenuButton.cpp 								*/
/*                            												*/
/*	Purpose	: Menu Button for Visualize dialog.                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".                        */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MenuButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction      														*/
/*--------------------------------------------------------------------------*/
CMenuButton::CMenuButton()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction        														*/
/*--------------------------------------------------------------------------*/
CMenuButton::~CMenuButton()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map        														*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMenuButton, CButton)
	//{{AFX_MSG_MAP(CMenuButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* DrawItem            														*/
/*--------------------------------------------------------------------------*/
void CMenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct != NULL);
    CRect cRect = lpDrawItemStruct->rcItem;
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    UINT uiState = lpDrawItemStruct->itemState;
    CPen cPen;
    CPen* pcPenOld = NULL;
    if( (uiState&ODS_DISABLED) )
        cPen.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_GRAYTEXT));
    else
        cPen.CreatePen(PS_SOLID, 0, ::GetSysColor(COLOR_BTNTEXT));

    // select the cPen into the DC
    pcPenOld = pDC->SelectObject(&cPen);

    // draw the border
    if( (uiState&ODS_SELECTED) )
        pDC->DrawFrameControl(cRect, DFC_BUTTON, DFCS_BUTTONPUSH|DFCS_PUSHED);
    else
        pDC->DrawFrameControl(cRect, DFC_BUTTON, DFCS_BUTTONPUSH);

	// get window text for later use
	CString strText;
	GetWindowText(strText);
	BOOL bNoText = strText.IsEmpty();

    // Draw the Arrow...
    // Something like:
    // X
    // XX
    // XXX
    // XXXX
    // XXX
    // XX
    // X
    // In the Center of the button.
    CSize cSizeArrow(4, 7); // (5,9) was (4,7), now matches Microsoft Outlook 2000
    CSize cSizeOffsetTop(1, +1); // size of the top stairsteps
    CSize cSizeOffsetBottom(1, -1); // size of the bottom stairsteps
	CPoint cPointStart; // if no text, center arrow in button
	CPoint cPointStop; // if no text, center arrow in button
	if (bNoText)
	{
		CPoint pointCenter((cRect.Width()/2), (cRect.Height()/2));
		cPointStart.x = pointCenter.x - (cSizeArrow.cx/2);
		cPointStart.y = pointCenter.y - (cSizeArrow.cy/2);
		cPointStop.x = cPointStart.x;
		cPointStop.y = cPointStart.y + cSizeArrow.cy;
	} 
	//	if button has text, place arrow at right of button
	else 
	{
		CPoint ptArrow(	cRect.right-6, // 2 pixels for border + 4 pixels margin
						cRect.Height()/2);
		cPointStart.x = ptArrow.x - cSizeArrow.cx;
		cPointStart.y = ptArrow.y - (cSizeArrow.cy/2);
		cPointStop.x = cPointStart.x;
		cPointStop.y = cPointStart.y + cSizeArrow.cy;
	}
    
    // start at the left and work to the right...
    for(int iInd = 0; iInd < cSizeArrow.cx; iInd++)
    {
        // draw the lines
        pDC->MoveTo(cPointStart);
        pDC->LineTo(cPointStop);

        // offset our points. (going right!)
        cPointStart.Offset(cSizeOffsetTop);
        cPointStop.Offset(cSizeOffsetBottom);
    }

    // Draw the focus rectangle if necessary.
    if( (uiState&ODS_FOCUS) )
    {
        CRect rectFocus(cRect);
        rectFocus.DeflateRect(3, 3);
        pDC->DrawFocusRect(rectFocus);
    }

	//	Draw button text (if any) - jjszucs, 14 July 1999
	if (!bNoText)
	{
		CRect rectText(cRect);
		cRect.DeflateRect(	5,	// left:	3 pixels for focus + 2 pixels margin
							4,	// top:		3 pixels for focus + 1 pixels margin
							15, // right:	2 pixels right border + 4 pixels margin between
								//			arrow and border + 5 pixels for arrow + 4 pixels between
								//			arrow and text
							4);	// bottom:	3 pixels for focus + 1 pixels margin
		pDC->DrawText(strText, &cRect, DT_CENTER | DT_VCENTER);
	}

    // clean up and return
    pDC->SelectObject(pcPenOld); // restore the cPen	
}