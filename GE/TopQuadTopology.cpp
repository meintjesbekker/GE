/*--------------------------------------------------------------------------*/
/*						TopQuadTopology.cpp									*/
/*                            												*/
/*	Purpose	: Create top quad topology.                               		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "TopQuadTopology.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CTopQuadTopology::CTopQuadTopology(CModel* pcModel /* = NULL */) 
	: CIndexes(pcModel)
{
	// vtk
	m_pcCellArray = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction             													*/
/*--------------------------------------------------------------------------*/
CTopQuadTopology::~CTopQuadTopology()
{
	if (m_pcCellArray)
		m_pcCellArray->Delete();
}

/*--------------------------------------------------------------------------*/
/* InsertNextCell                                                           */
/*--------------------------------------------------------------------------*/
void CTopQuadTopology::InsertNextCell(vtkCellArray* pcCellArray, CQuadIndexes cQuadIndexes)
{
	pcCellArray->InsertNextCell(4);
	pcCellArray->InsertCellPoint(cQuadIndexes.iP[0]);
	pcCellArray->InsertCellPoint(cQuadIndexes.iP[1]);
	pcCellArray->InsertCellPoint(cQuadIndexes.iP[3]);
	pcCellArray->InsertCellPoint(cQuadIndexes.iP[2]);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalTopology														*/
/*--------------------------------------------------------------------------*/
void CTopQuadTopology::CreateNormalTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iNumberOfNormalLayerPoints /* = 0 */)
{
	// Horizontal top.
	CreateHorizontalTopology(pcCellArray, bAverage, iNumberOfNormalLayerPoints);
	
	// Right vertical.
	CreateNormalRightVerticalTopology(pcCellArray, iNumberOfNormalLayerPoints);
	
	// Front vertical.
	CreateNormalFrontVerticalTopology(pcCellArray, iNumberOfNormalLayerPoints);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalRightVerticalTopology                                        */
/*--------------------------------------------------------------------------*/
void CTopQuadTopology::CreateNormalRightVerticalTopology(vtkCellArray* pcCellArray, int iNumberOfNormalLayerPoints /* = 0 */)
{
	// For number of rows.
 	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		// For number of columns - 1.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns() - 1; j++)
			// If it is an active cell and cell to right is an active cell.
 			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j]
				&& m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j + 1])
				// Insert the next quadrilateral into the cell array, using the 4 right vertical, point array indexes.
				InsertNextCell(pcCellArray, GetNormalRightVerticalQuadIndexes(i, j, iNumberOfNormalLayerPoints));
}

/*--------------------------------------------------------------------------*/
/* CreateNormalFrontVerticalTopology                                        */
/*--------------------------------------------------------------------------*/
void CTopQuadTopology::CreateNormalFrontVerticalTopology(vtkCellArray* pcCellArray, int iNumberOfNormalLayerPoints /* = 0 */)
{
	// Front vertical.
	// For number of rows - 1.
 	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows() - 1; i++)
		// For number of columns.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
			// If it is an active cell and cell in front is an active cell.
 			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j] 
				&& m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j + m_pcModelInfo->GetNumberOfColumns()])
				// Insert the next quadrilateral into the cell array, using the 4 front vertical, point array indexes.
				InsertNextCell(pcCellArray, GetNormalFrontVerticalQuadIndexes(i, j, iNumberOfNormalLayerPoints));
}

/*--------------------------------------------------------------------------*/
/* CreateNormalHorizontalTopology                                           */
/*--------------------------------------------------------------------------*/
void CTopQuadTopology::CreateHorizontalTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iNumberOfNormalLayerPoints /* = 0 */)
{
 	// For number of rows.
	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
			// If it is an active cell.
 			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j])
				// Insert the next quadrilateral into the cell array, using the 4 horizontal, point array indexes.
				InsertNextCell(pcCellArray, GetHorizontalTopQuadIndexes(bAverage, i, j, iNumberOfNormalLayerPoints));
}