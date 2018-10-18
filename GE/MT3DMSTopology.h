/*--------------------------------------------------------------------------*/
/*							MT3DMSTopology.h   								*/
/*                            												*/
/*	Purpose	: Create topology for MT3DMS, PHT3D or RT3D isosurfaces.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".          					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSTOPOLOGY_H__219AF481_8489_11D4_B307_0060084B410C__INCLUDED_)
#define AFX_MT3DMSTOPOLOGY_H__219AF481_8489_11D4_B307_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxpriv.h> // for WM_SETMESSAGESTRING message
#include "MT3DMSContourAndColorTable.h"
#endif // _MSC_VER > 1000

class CMT3DMSTopology  
{
// public operations
public:
	CMT3DMSTopology();
	virtual ~CMT3DMSTopology();

// protected operations
protected:
	void Contour(vtkStructuredGrid* pcStructuredGrid, CMT3DMSContourAndColorTable* pMT3DMSContourAndColorTable);

// private operations
protected:
	// operations for displaying micro help
	static void StartContouring(void* pArgument);
	static void EndContouring(void* pArgument);
	
// protected attributes
protected:	
	// vtk
	vtkContourFilter* m_pcContourFilter;
};

#endif // !defined(AFX_MT3DMSTOPOLOGY_H__219AF481_8489_11D4_B307_0060084B410C__INCLUDED_)
