/*--------------------------------------------------------------------------*/
/*								ObjectList.cpp 								*/
/*                            												*/
/*	Purpose	: Element of visualization object list.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ObjectList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CObjectList::CObjectList(BOOL bVisible, int iIndex)
{
	m_bVisible = bVisible;
	m_iIndex = iIndex;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CObjectList::~CObjectList()
{
}