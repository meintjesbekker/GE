/*--------------------------------------------------------------------------*/
/*						GeospatialModelSheet.cpp 							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Geospatial Model.						*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.3 "Geospatial Model".					*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModelSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create															*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CGeospatialModelSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction  															*/
/*--------------------------------------------------------------------------*/
CGeospatialModelSheet::CGeospatialModelSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage) : CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction  															*/
/*--------------------------------------------------------------------------*/
CGeospatialModelSheet::CGeospatialModelSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destructor      															*/
/*--------------------------------------------------------------------------*/
CGeospatialModelSheet::~CGeospatialModelSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map     															*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CGeospatialModelSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGeospatialModelSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()