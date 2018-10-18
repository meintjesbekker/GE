/*--------------------------------------------------------------------------*/
/*							XYZSurfaceSheet.cpp  							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of XYZ Surface.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.5 "XYZ Surface".        				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZSurfaceSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create   														*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CXYZSurfaceSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction     														*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceSheet::CXYZSurfaceSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction     														*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceSheet::CXYZSurfaceSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destruction      														*/
/*--------------------------------------------------------------------------*/
CXYZSurfaceSheet::~CXYZSurfaceSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map     															*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CXYZSurfaceSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CXYZSurfaceSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()