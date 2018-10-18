/*--------------------------------------------------------------------------*/
/*								MT3DMSSheet.cpp 							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Isosurface.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6 "Isosurface".                       */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create 															*/	
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CMT3DMSSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction																*/	
/*--------------------------------------------------------------------------*/
CMT3DMSSheet::CMT3DMSSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage) 
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction																*/	
/*--------------------------------------------------------------------------*/
CMT3DMSSheet::CMT3DMSSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage) 
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destruction    															*/	
/*--------------------------------------------------------------------------*/
CMT3DMSSheet::~CMT3DMSSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map     															*/	
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CMT3DMSSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMT3DMSSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()