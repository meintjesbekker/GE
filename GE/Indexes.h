/*--------------------------------------------------------------------------*/
/*								Indexes.h									*/
/*                            												*/
/*	Purpose	: Indexes for creating geometry and topology.             		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:																*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_INDEXES_H__F98F40A5_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
#define AFX_INDEXES_H__F98F40A5_7B81_11D4_B2F3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#include "QuadIndexes.h"
#endif // _MSC_VER > 1000

class CIndexes  
{
public:
	CIndexes(CModel* pcModel = NULL);
	virtual ~CIndexes();

	// indexes
	void CalculateTopIndexes(int iTopPoint[4], int iP0, int iP2, int iLayerStartPointIndex = 0);
	void CalculateBottomIndexes(const int iTopPoint[4], int iBottomPoint[4], int iNumberOfLayerPoints);
	int GetP0Index(BOOL bAverage, int iRowIndex, int iColumnIndex) const;
	int GetP2Index(BOOL bAverage, int iRowIndex, int iColumnIndex) const;
	int GetP0NormalIndex(int iRowIndex, int iColumnIndex) const;
	int GetP0AverageIndex(int iRowIndex, int iColumnIndex) const;
	int GetP2NormalIndex(int iRowIndex, int iColumnIndex) const;
	int GetP2AverageIndex(int iRowIndex, int iColumnIndex) const;
	int GetLayerStartCellIndex(int iLayer) const;
	int GetNormalLayerStartPointIndex(int iLayer) const;
	int GetAverageLayerStartPointIndex(int iLayer) const;
	int CalculateRowIndex(int iPointIndex) const;
	int CalculateColumnIndex(int iPointIndex) const;

	// get quad indexes
	CQuadIndexes GetNormalRightVerticalQuadIndexes(int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints);
	CQuadIndexes GetNormalFrontVerticalQuadIndexes(int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints);
	CQuadIndexes GetHorizontalTopQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints);
	CQuadIndexes GetLeftSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex);
	CQuadIndexes GetRightSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex);
	CQuadIndexes GetBackSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex);
	CQuadIndexes GetFrontSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex);

	// number of points
	int GetNumberOfLayerPoints(BOOL bAverage) const;
	int GetNormalNumberOfLayerPoints() const;
	int GetNormalNumberOfPointsForAllLayers() const;
	int GetAverageNumberOfLayerPoints() const;

	// general
	float* ReadTimeIndependentData(CString sFileExtension, int iLayer);

	// active cell array
	void CreateIBDActiveCellsArray(int iLayer);

// protected attributes
protected:
	// pointer to model object
	CModel*	m_pcModelInfo;

	// other
	CReadFile m_cReadFile;
	CArray<BOOL, BOOL> m_bActiveCellsArray;
	CArray<CAverage*, CAverage*> m_pcAverageArray;
};

#endif // !defined(AFX_INDEXES_H__F98F40A5_7B81_11D4_B2F3_0060084B410C__INCLUDED_)
