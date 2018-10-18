/*--------------------------------------------------------------------------*/
/*							SidesQuadTopology.cpp							*/
/*                            												*/
/*	Purpose	: Create sides quad topology.									*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "SidesQuadTopology.h"

/*--------------------------------------------------------------------------*/
/* Construction              			                                    */
/*--------------------------------------------------------------------------*/
CSidesQuadTopology::CSidesQuadTopology(CModel* pcModel /* = NULL */)
	: CTopQuadTopology(pcModel)
{
}

/*--------------------------------------------------------------------------*/
/* Destruction               			                                    */
/*--------------------------------------------------------------------------*/
CSidesQuadTopology::~CSidesQuadTopology()
{
}

/*--------------------------------------------------------------------------*/
/* CreateSidesTopology														*/
/*--------------------------------------------------------------------------*/
void CSidesQuadTopology::CreateSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage)
{
 	// For number of rows.
	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
 			// If it is an active cell.
			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j])
			{
				// left
				CreateLeftSidesTopology(pcCellArray, bAverage, i, j);
				
				// right
				CreateRightSidesTopology(pcCellArray, bAverage, i, j);
				
				// back
				CreateBackSidesTopology(pcCellArray, bAverage, i, j);
				
				// front
				CreateFrontSidesTopology(pcCellArray, bAverage, i, j);
			}
}

/*--------------------------------------------------------------------------*/
/* CreateLeftSidesTopology													*/
/*--------------------------------------------------------------------------*/
void CSidesQuadTopology::CreateLeftSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	// If it is the first column or if the cell to the left of cell is inactive.
	if ((iColumnIndex == 0) 
		|| (!m_bActiveCellsArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex - 1]))
		// Insert the next quadrilateral into the cell array, using the 4, point array indexes.
		InsertNextCell(pcCellArray, GetLeftSidesQuadIndexes(bAverage, iRowIndex, iColumnIndex));
}

/*--------------------------------------------------------------------------*/
/* CreateRightSidesTopology													*/
/*--------------------------------------------------------------------------*/
void CSidesQuadTopology::CreateRightSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	// If it is the last column or if the cell to the right of cell is inactive.
	if ((iColumnIndex == m_pcModelInfo->GetNumberOfColumns() - 1)
		|| (!m_bActiveCellsArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex + 1]))
		// Insert the next quadrilateral into the cell array, using the 4, point array indexes.
		InsertNextCell(pcCellArray, GetRightSidesQuadIndexes(bAverage, iRowIndex, iColumnIndex));
}

/*--------------------------------------------------------------------------*/
/* CreateBackSidesTopology													*/
/*--------------------------------------------------------------------------*/
void CSidesQuadTopology::CreateBackSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	// If it is the first row or if the cell to the back of cell is inactive.
	if ((iRowIndex == 0)
		|| (!m_bActiveCellsArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex - m_pcModelInfo->GetNumberOfColumns()]))
		// Insert the next quadrilateral into the cell array, using the 4, point array indexes.
		InsertNextCell(pcCellArray, GetBackSidesQuadIndexes(bAverage, iRowIndex, iColumnIndex));
}

/*--------------------------------------------------------------------------*/
/* CreateFrontSidesTopology													*/
/*--------------------------------------------------------------------------*/
void CSidesQuadTopology::CreateFrontSidesTopology(vtkCellArray* pcCellArray, BOOL bAverage, int iRowIndex, int iColumnIndex)
{
	// front
	// If it is the last row or if the cell to front of the cell is inactive.
	if ((iRowIndex == m_pcModelInfo->GetNumberOfRows() - 1)
		|| (!m_bActiveCellsArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex + m_pcModelInfo->GetNumberOfColumns()]))
		// Insert the next quadrilateral into the cell array, using the 4, point array indexes.
		InsertNextCell(pcCellArray, GetFrontSidesQuadIndexes(bAverage, iRowIndex, iColumnIndex));
}
