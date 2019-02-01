/*--------------------------------------------------------------------------*/
/*								QuadIndexes.h   							*/
/*                            												*/
/*	Purpose	: Point indexes for quadrilateral.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".                       */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_QUADINDEXES_H__FE5A77B1_893C_11D4_B310_0060084B410C__INCLUDED_)
#define AFX_QUADINDEXES_H__FE5A77B1_893C_11D4_B310_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQuadIndexes  
{
// public operations
public:
	CQuadIndexes();
	virtual ~CQuadIndexes();

// public attributes
public:
	int iP[iN_POINTS] = {0};
};

#endif // !defined(AFX_QUADINDEXES_H__FE5A77B1_893C_11D4_B310_0060084B410C__INCLUDED_)
