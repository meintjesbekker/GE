/*--------------------------------------------------------------------------*/
/*							ModelOutlineSheet.cpp							*/
/*                            												*/
/*	Purpose	: Sheet for GUI pages of Model Outline.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.2 "Model Outline".                    */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ModelOutlineSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create   				                                        */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC(CModelOutlineSheet, CPropertySheet)

/*--------------------------------------------------------------------------*/
/* Construction     				                                        */
/*--------------------------------------------------------------------------*/
CModelOutlineSheet::CModelOutlineSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Construction       				                                        */
/*--------------------------------------------------------------------------*/
CModelOutlineSheet::CModelOutlineSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

/*--------------------------------------------------------------------------*/
/* Destruction       				                                        */
/*--------------------------------------------------------------------------*/
CModelOutlineSheet::~CModelOutlineSheet()
{
}

/*--------------------------------------------------------------------------*/
/* Message Map        				                                        */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CModelOutlineSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModelOutlineSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()