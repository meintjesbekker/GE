/*--------------------------------------------------------------------------*/
/*						HexahedronTopology.h  								*/
/*                            												*/
/*	Purpose	: Create hexahedron topology.                               	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:																*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HEXAHEDRONTOPOLOGY_H__6B60A0E1_9440_11D4_B31E_0060084B410C__INCLUDED_)
#define AFX_HEXAHEDRONTOPOLOGY_H__6B60A0E1_9440_11D4_B31E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxtempl.h> // CArray
#include "Color.h"
#include "Indexes.h"
#endif // _MSC_VER > 1000

class CHexahedronTopology : virtual public CIndexes  
{
// public operations
public:
	CHexahedronTopology(CModel* pcModel = NULL);
	virtual ~CHexahedronTopology();

// protected operations
protected:
	void CreateTopolgy(BOOL bAverage, vtkDoubleArray* pcScalars, CString sFolderAndFileName, CColor* pcColor);
	void CreateNormalTopologyAndScalarDatasetAttribute(vtkDoubleArray* pcScalars, CString sFolderAndFileName, CColor* pcColor);
	void CreateAverageTopologyAndScalarDatasetAttribute(vtkDoubleArray* pcScalars, CString sFolderAndFileName, CColor* pcColor);
	void InsertHexahedronCell(int iPTop[4], int iPBottom[4]);

// private operations
private:
	void CreateNormalOrAverageTopology(	vtkDoubleArray* pcScalars, 
										CString sFolderAndFileName, 
										CColor* pcColor, 
										int (CIndexes::*pFuncP0Index)(int, int) const, 
										int (CIndexes::*pFuncP2Index)(int, int) const, 
										int (CIndexes::*pFuncLayerStartPointIndex)(int) const, 
										int iNumberOfLayerPoints);
// public attributes
public:
	CArray<BOOL, BOOL> m_bVisibleLayersArray;

// protected attributes
protected:
	// vtk
	vtkCellArray* m_pcCellArray;

// private attributes
private:
	// other    
	CReadFile m_cReadFile;
};

#endif // !defined(AFX_HEXAHEDRONTOPOLOGY_H__6B60A0E1_9440_11D4_B31E_0060084B410C__INCLUDED_)
