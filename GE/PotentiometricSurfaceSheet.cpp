/*--------------------------------------------------------------------------*/
/*						PotentiometricSurfaceSheet.cpp 						*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Potentiometric Surface.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.4 "Potentiometric Surface".           */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "PotentiometricSurfaceSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create              												*/	
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CPotentiometricSurfaceSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction                 											*/	
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceSheet::CPotentiometricSurfaceSheet(	UINT nIDCaption, 
															CWnd* pParentWnd, 
															UINT iSelectPage) 
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction                												*/	
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceSheet::CPotentiometricSurfaceSheet(LPCTSTR pszCaption, 
														 CWnd* pParentWnd, 
														 UINT iSelectPage) 
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destruction                 												*/	
/*--------------------------------------------------------------------------*/
CPotentiometricSurfaceSheet::~CPotentiometricSurfaceSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map                 												*/	
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CPotentiometricSurfaceSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPotentiometricSurfaceSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()