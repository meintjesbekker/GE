/*--------------------------------------------------------------------------*/
/*						HydraulicComponentsSheet.cpp 						*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Hydraulic Components.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.7 "Hydraulic Components".             */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "HydraulicComponentsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* HydraulicComponentsSheet.h                                               */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CHydraulicComponentsSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsSheet::CHydraulicComponentsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
													:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsSheet::CHydraulicComponentsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage) 
													: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CHydraulicComponentsSheet::~CHydraulicComponentsSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CHydraulicComponentsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CHydraulicComponentsSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()