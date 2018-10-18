/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorEditBox.cpp   					*/
/*                            												*/
/*	Purpose	: Edit box for contour in Contour and Color dialog box.			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSContourAndColorEditBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                  			                                */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorEditBox::CMT3DMSContourAndColorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                   			                                */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorEditBox::~CMT3DMSContourAndColorEditBox()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                    			                                */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSContourAndColorEditBox, CEdit)
	//{{AFX_MSG_MAP(CMT3DMSContourAndColorEditBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()