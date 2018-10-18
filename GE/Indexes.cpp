/*--------------------------------------------------------------------------*/
/*								Indexes.cpp									*/
/*                            												*/
/*	Purpose	: Indexes for creating geometry and topology.             		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:																*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Indexes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction       														*/
/*--------------------------------------------------------------------------*/
CIndexes::CIndexes(CModel* pcModel /* = NULL */)
{
	m_pcModelInfo = pcModel;
}

/*--------------------------------------------------------------------------*/
/* Destruction        														*/
/*--------------------------------------------------------------------------*/
CIndexes::~CIndexes()
{
	m_bActiveCellsArray.RemoveAll();
	for (int i = 0; i < m_pcAverageArray.GetSize(); i++)
		delete m_pcAverageArray[i];
	m_pcAverageArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* CalculateTopIndexes														*/
/*--------------------------------------------------------------------------*/
void CIndexes::CalculateTopIndexes(int iTopPoint[4], int iP0, int iP2, int iLayerStartPointIndex /* = 0 */)
{
	iTopPoint[0] = iP0 + iLayerStartPointIndex;
	iTopPoint[1] = iTopPoint[0] + 1;
	iTopPoint[2] = iP2 + iLayerStartPointIndex;
	iTopPoint[3] = iTopPoint[2] + 1;
}

/*--------------------------------------------------------------------------*/
/* CalculateBottomIndexes                                                   */
/*--------------------------------------------------------------------------*/
void CIndexes::CalculateBottomIndexes(const int iPTop[4], int iPBottom[4], int iNumberOfLayerPoints)
{
	iPBottom[0] = iPTop[0] + iNumberOfLayerPoints;
	iPBottom[1] = iPBottom[0] + 1;
	iPBottom[2] = iPTop[2] + iNumberOfLayerPoints;
	iPBottom[3] = iPBottom[2] + 1;
}

/*--------------------------------------------------------------------------*/
/* GetP0NormalIndex															*/
/*--------------------------------------------------------------------------*/
int CIndexes::GetP0NormalIndex(int iRowIndex, int iColumnIndex) const
{
	return (iRowIndex * m_pcModelInfo->GetNumberOfColumns() * iN_POINTS
		+ iColumnIndex * iN_EDGE_POINTS);
}

/*--------------------------------------------------------------------------*/
/* GetP0AverageIndex														*/
/*--------------------------------------------------------------------------*/
int CIndexes::GetP0AverageIndex(int iRowIndex, int iColumnIndex) const
{
	return (iRowIndex * (m_pcModelInfo->GetNumberOfColumns() + 1) + iColumnIndex);
}

/*--------------------------------------------------------------------------*/
/* GetP2NormalIndex															*/
/*--------------------------------------------------------------------------*/
int CIndexes::GetP2NormalIndex(int iRowIndex, int iColumnIndex) const
{
	return (((iRowIndex * iN_EDGE_POINTS + 1) 
			* m_pcModelInfo->GetNumberOfColumns() + iColumnIndex) * iN_EDGE_POINTS);
}

/*--------------------------------------------------------------------------*/
/* GetP2AverageIndex                                                        */
/*--------------------------------------------------------------------------*/
int CIndexes::GetP2AverageIndex(int iRowIndex, int iColumnIndex) const
{
	return ((iRowIndex + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1) + iColumnIndex);
}

/*--------------------------------------------------------------------------*/
/* GetLayerStartCellIndex                                                   */
/*--------------------------------------------------------------------------*/
int CIndexes::GetLayerStartCellIndex(int iLayer) const
{
	return (m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns() * (iLayer - 1));
}

/*--------------------------------------------------------------------------*/
/* GetNormalLayerStartPointIndex                                            */
/*--------------------------------------------------------------------------*/
int CIndexes::GetNormalLayerStartPointIndex(int iLayer) const
{
	return (iN_CELL_POINTS * m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns() * (iLayer - 1));
}

/*--------------------------------------------------------------------------*/
/* GetAverageLayerStartPointIndex                                           */
/*--------------------------------------------------------------------------*/
int CIndexes::GetAverageLayerStartPointIndex(int iLayer) const
{
	return (iN_EDGE_POINTS * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1) * (iLayer - 1));
}

/*--------------------------------------------------------------------------*/
/* GetNumberOfLayerPoints                                                   */
/*--------------------------------------------------------------------------*/
int CIndexes::GetNumberOfLayerPoints(BOOL bAverage) const
{
	if (bAverage)
		return GetAverageNumberOfLayerPoints();
	else
		return GetNormalNumberOfLayerPoints();
}

/*--------------------------------------------------------------------------*/
/* GetNormalNumberOfLayerPoints                                             */
/*--------------------------------------------------------------------------*/
int CIndexes::GetNormalNumberOfLayerPoints() const
{
	return (iN_POINTS * m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns());
}

/*--------------------------------------------------------------------------*/
/* GetNormalNumberOfPointsForAllLayers                                      */
/*--------------------------------------------------------------------------*/
int CIndexes::GetNormalNumberOfPointsForAllLayers() const
{
	return (iN_POINTS * m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns() * m_pcModelInfo->GetNumberOfLayers());
}

/*--------------------------------------------------------------------------*/
/* GetAverageNumberOfLayerPoints                                            */
/*--------------------------------------------------------------------------*/
int CIndexes::GetAverageNumberOfLayerPoints() const
{
	return (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1);
}

/*--------------------------------------------------------------------------*/
/* CalculateRowIndex   														*/
/*--------------------------------------------------------------------------*/
int CIndexes::CalculateRowIndex(int iPointIndex) const
{
	if (iPointIndex < (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1))
		return (int(iPointIndex / (m_pcModelInfo->GetNumberOfColumns() + 1)));
	else
		return (int(iPointIndex / (m_pcModelInfo->GetNumberOfColumns() + 1)) - (m_pcModelInfo->GetNumberOfRows() + 1));
}

/*--------------------------------------------------------------------------*/
/* CalculateColumnIndex														*/
/*--------------------------------------------------------------------------*/
int CIndexes::CalculateColumnIndex(int iPointIndex) const
{
	return (int(iPointIndex % (m_pcModelInfo->GetNumberOfColumns() + 1)));
}

/*--------------------------------------------------------------------------*/
/* GetNormalRightVerticalQuadIndexes										*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetNormalRightVerticalQuadIndexes(int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4 right vertical, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP0NormalIndex(iRowIndex, iColumnIndex) + 1 + iNumberOfNormalLayerPoints;
	cQuadIndexes.iP[1] = cQuadIndexes.iP[0] + 1;
	cQuadIndexes.iP[2] = GetP2NormalIndex(iRowIndex, iColumnIndex) + 1 + iNumberOfNormalLayerPoints;
	cQuadIndexes.iP[3] = cQuadIndexes.iP[2] + 1;
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetNormalFrontVerticalQuadIndexes										*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetNormalFrontVerticalQuadIndexes(int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4 front vertical, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP2NormalIndex(iRowIndex, iColumnIndex) + iNumberOfNormalLayerPoints;
	cQuadIndexes.iP[1] = cQuadIndexes.iP[0] + 1;
	cQuadIndexes.iP[2] = cQuadIndexes.iP[0] + iN_EDGE_POINTS * m_pcModelInfo->GetNumberOfColumns();
	cQuadIndexes.iP[3] = cQuadIndexes.iP[1] + iN_EDGE_POINTS * m_pcModelInfo->GetNumberOfColumns();
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetHorizontalQuadIndexes													*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetHorizontalTopQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex, int iNumberOfNormalLayerPoints)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4 horizontal top or bottom, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP0Index(bAverage, iRowIndex, iColumnIndex) + iNumberOfNormalLayerPoints;
	cQuadIndexes.iP[1] = cQuadIndexes.iP[0] + 1;
	cQuadIndexes.iP[2] = GetP2Index(bAverage, iRowIndex, iColumnIndex) + iNumberOfNormalLayerPoints;
	cQuadIndexes.iP[3] = cQuadIndexes.iP[2] + 1;
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetLeftSidesQuadIndexes													*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetLeftSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP0Index(bAverage, iRowIndex, iColumnIndex);
	cQuadIndexes.iP[1] = GetP2Index(bAverage, iRowIndex, iColumnIndex);
	cQuadIndexes.iP[2] = cQuadIndexes.iP[0] + GetNumberOfLayerPoints(bAverage);
	cQuadIndexes.iP[3] = cQuadIndexes.iP[1] + GetNumberOfLayerPoints(bAverage);
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetRightSidesQuadIndexes													*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetRightSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP0Index(bAverage, iRowIndex, iColumnIndex) + 1;
	cQuadIndexes.iP[1] = GetP2Index(bAverage, iRowIndex, iColumnIndex) + 1;
	cQuadIndexes.iP[2] = cQuadIndexes.iP[0] + GetNumberOfLayerPoints(bAverage);
	cQuadIndexes.iP[3] = cQuadIndexes.iP[1] + GetNumberOfLayerPoints(bAverage);
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetBackSidesQuadIndexes													*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetBackSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	CQuadIndexes cQuadIndexes;
	
	// Calculate 4, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP0Index(bAverage, iRowIndex, iColumnIndex);
	cQuadIndexes.iP[1] = cQuadIndexes.iP[0] + 1;
	cQuadIndexes.iP[2] = cQuadIndexes.iP[0] + GetNumberOfLayerPoints(bAverage);
	cQuadIndexes.iP[3] = cQuadIndexes.iP[2] + 1;
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetFrontSidesQuadIndexes													*/
/*--------------------------------------------------------------------------*/
CQuadIndexes CIndexes::GetFrontSidesQuadIndexes(BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	CQuadIndexes cQuadIndexes;

	// Calculate 4, point array indexes for quadrilateral.
	cQuadIndexes.iP[0] = GetP2Index(bAverage, iRowIndex, iColumnIndex);
	cQuadIndexes.iP[1] = cQuadIndexes.iP[0] + 1;
	cQuadIndexes.iP[2] = cQuadIndexes.iP[0] + GetNumberOfLayerPoints(bAverage);
	cQuadIndexes.iP[3] = cQuadIndexes.iP[2] + 1;
	return cQuadIndexes;
}

/*--------------------------------------------------------------------------*/
/* GetP0Index																*/
/*--------------------------------------------------------------------------*/
int CIndexes::GetP0Index(BOOL bAverage, int iRowIndex, int iColumnIndex) const
{
	if (bAverage)
		return	GetP0AverageIndex(iRowIndex, iColumnIndex);
	else
		return GetP0NormalIndex(iRowIndex, iColumnIndex);
}

/*--------------------------------------------------------------------------*/
/* GetP2Index																*/	
/*--------------------------------------------------------------------------*/
int CIndexes::GetP2Index(BOOL bAverage, int iRowIndex, int iColumnIndex) const
{
	if (bAverage)
		return GetP2AverageIndex(iRowIndex, iColumnIndex);
	else
		return GetP2NormalIndex(iRowIndex, iColumnIndex);
}

/*--------------------------------------------------------------------------*/
/* ReadTimeIndependentData                                                  */
/*--------------------------------------------------------------------------*/
float* CIndexes::ReadTimeIndependentData(CString sFileExtension, int iLayer)
{
	float* pfArray = new float[m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns()];
	m_cReadFile.ReadTimeIndependentData(m_pcModelInfo->GetFolderAndFileName().SpanExcluding(".") + "." + sFileExtension,
										pfArray,
										m_pcModelInfo->GetNumberOfRows(),
										m_pcModelInfo->GetNumberOfColumns(),
										iLayer);
	return pfArray;
}

/*--------------------------------------------------------------------------*/
/* CreateActivateCellsArray                                                 */
/*--------------------------------------------------------------------------*/
void CIndexes::CreateIBDActiveCellsArray(int iLayer)
{
	// read CBC data for IBOUND (modflow)
	m_bActiveCellsArray.RemoveAll();
	float* arrayIBOUND = ReadTimeIndependentData("ibd", iLayer);
	m_bActiveCellsArray.SetSize(m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns(), 1);
	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
			//    0 = inactive cells
			//  > 0 = active cells
			//  < 0 = fixed head cells
			// TRUE for active FALSE for inactive cells
			m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j] = (arrayIBOUND[i * m_pcModelInfo->GetNumberOfColumns() + j] != 0);
	delete [] arrayIBOUND;
}