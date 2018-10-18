/*--------------------------------------------------------------------------*/
/*							XYZCoordinate.cpp								*/
/*                            												*/
/*	Purpose	: 3D coordinate.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "XYZCoordinate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Implement Serial       													*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_SERIAL(CXYZCoordinate, CObject, 1);

/*--------------------------------------------------------------------------*/
/* Construction    															*/
/*--------------------------------------------------------------------------*/
CXYZCoordinate::CXYZCoordinate()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction     															*/
/*--------------------------------------------------------------------------*/
CXYZCoordinate::~CXYZCoordinate()
{
}

/*--------------------------------------------------------------------------*/
/* SetXYZ          															*/
/*--------------------------------------------------------------------------*/
void CXYZCoordinate::SetXYZ(float fX, float fY, float fZ)
{
	m_fX = fX;
	m_fY = fY;
	m_fZ = fZ;
}

/*--------------------------------------------------------------------------*/
/* Serialize       															*/
/*--------------------------------------------------------------------------*/
void CXYZCoordinate::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_fX << m_fY << m_fZ;
	else
		ar >> m_fX >> m_fY >> m_fZ;
}