/*--------------------------------------------------------------------------*/
/*							Geometry.cpp									*/
/*                            												*/
/*	Purpose	: Create geometry.                                        		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, Chapter 5.                 							*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "Geometry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction              			                                    */
/*--------------------------------------------------------------------------*/
CGeometry::CGeometry(CModel* pcModel /* = NULL */) 
	: CIndexes(pcModel)
{
	m_fMinimumValue = 0;
	m_fMaximumValue = 0;
	m_pcScalars = NULL;
	m_pcFloatPoints = NULL;	
}

/*--------------------------------------------------------------------------*/
/* Destruction               			                                    */
/*--------------------------------------------------------------------------*/
CGeometry::~CGeometry()
{
	if (m_pcFloatPoints)
		m_pcFloatPoints->Delete();
	if (m_pcScalars)
		m_pcScalars->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateNormalGeometry                                                     */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateNormalGeometry(int iLayer)
{
	// Create a point array.
	CreatePointArray();

	// 8 = 2 * 2 * 2 = iN_CELL_POINTS
	// 2 for top and bottom
	// 2 sides of column, left and right
	// 2 sides of row, bottom and top
	// Set the size of the point array = 2 * 2 * number of rows * 2 * number of columns.
	m_pcFloatPoints->SetNumberOfPoints(iN_CELL_POINTS * m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns());
	CreateNormalGeometryForLayer(iLayer);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalGeometryForLayer		                                        */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateNormalGeometryForLayer(int iLayer, int iLayerStartCellIndex /* = 0 */, int iLayerStartPointIndex /* = 0 */)
{
	// Read the top elevation for all cells into a top elevation array.
	float* pfTopArray = ReadTimeIndependentData("top", iLayer);
	float fZTopValue = 0;
	
	// Read the bottom elevation for all cells into a bottom elevation array.
	float* pfBottomArray = ReadTimeIndependentData("bot", iLayer);
	float fZBottomValue = 0;
	
	// For number of rows.
	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
		{
			// If it is an active cell.
			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j + iLayerStartCellIndex])
			{
				// Get top elevation of cell from top elevation array for current row and column.
				fZTopValue = pfTopArray[i * m_pcModelInfo->GetNumberOfColumns() + j];

				// Get bottom elevation of cell from bottom elevation array for current row and column.
				fZBottomValue = pfBottomArray[i * m_pcModelInfo->GetNumberOfColumns() + j];
			}
			else
			{
				// Use minimum elevation of all bottom and top elevations as top elevation.
				fZTopValue = m_fMinimumValue;

				// Use minimum elevation of all bottom and top elevations as bottom elevation.
				fZBottomValue = m_fMinimumValue;
			}

			// Insert 4 points into point array, using the 4 bottom point indexes, row and column coordinates and bottom elevation.
			InsertNormalPoints(i, j, fZTopValue, fZBottomValue, iLayerStartPointIndex);
		}
	delete [] pfTopArray;
	delete [] pfBottomArray;
}

/*--------------------------------------------------------------------------*/
/* CreateAverageGeometry	                                                */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateAverageGeometry(int iLayer)
{
	// Create average points.
	CreateAveragePoints(iLayer);

	// Create a point array.
	CreatePointArray();

	// Set the size of the point array = 2 * (number of rows + 1) * (number of columns + 1).
	m_pcFloatPoints->SetNumberOfPoints(2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1));
	
	// For indexes of point array.
	for (int i = 0; i < 2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1); i++)
		// Calculate row and column indexes using the point array index.
		// Insert a point into the point array where:
		//	point.x = Get the column coordinate for column index.
		//	point.y = Get the row coordinate for row index.
		//	point.z = Get the average elevation from average point array.
		m_pcFloatPoints->InsertPoint(	i,
										m_pcModelInfo->GetColumnCoordinate(CalculateColumnIndex(i)),
										m_pcModelInfo->GetRowCoordinate(CalculateRowIndex(i)),
										m_pcAverageArray.GetAt(i)->GetAverage());
}

/*--------------------------------------------------------------------------*/
/* CreateMiddleGeometry                                                     */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateMiddleGeometry(int iNumberOfPoints /* = 1 */)
{
	// Create a point array.
	if (m_pcFloatPoints) 
		m_pcFloatPoints->Delete();
	m_pcFloatPoints = vtkPoints::New();

	// For all the model layers.
	for (int iLayer = 1; iLayer <= m_pcModelInfo->GetNumberOfLayers(); iLayer++)
	{
		// Read the top elevation for all cells into the top elevation array.
		float* pfTopArray = ReadTimeIndependentData("top", iLayer);

		// Read the bottom elevation for all cells into the bottom elevation array.
		float* pfBottomArray = ReadTimeIndependentData("bot", iLayer);		
		
		// For number of rows.
		for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
			// For number of columns.
			for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
			{
				// Insert the point into the point array, using the middle row and column coordinates and the middle of the top and bottom elevation.
				float zIncrement = (pfTopArray[i * m_pcModelInfo->GetNumberOfColumns() + j] - pfBottomArray[i * m_pcModelInfo->GetNumberOfColumns() + j]) / (1 + iNumberOfPoints);
				for (int k = 1; k <= iNumberOfPoints; k++)
					m_pcFloatPoints->InsertNextPoint(	m_pcModelInfo->GetMiddleColumnCoordinate(j), 
														m_pcModelInfo->GetMiddleRowCoordinate(i),
														pfBottomArray[i * m_pcModelInfo->GetNumberOfColumns() + j] + k * zIncrement);
			 }
		delete [] pfTopArray;
		delete [] pfBottomArray;
	}
}

/*--------------------------------------------------------------------------*/
/* CreateNormalGeometryForAllLayers                                         */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateNormalGeometryForAllLayers()
{
	// Create a point array.
	CreatePointArray();

	// 8 = 2 * 2 * 2 = iN_CELL_POINTS
	// 2 for top and bottom
	// 2 sides of column, left and right
	// 2 sides of row, bottom and top 
	m_pcFloatPoints->SetNumberOfPoints(iN_CELL_POINTS * m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns() * m_pcModelInfo->GetNumberOfLayers()); 
	for (int iLayer = 1; iLayer <= m_pcModelInfo->GetNumberOfLayers(); iLayer++)
	{
		int iLayerStartCellIndex = GetLayerStartCellIndex(iLayer);
		int iLayerStartPointIndex = GetNormalLayerStartPointIndex(iLayer);
		CreateNormalGeometryForLayer(iLayer, iLayerStartCellIndex, iLayerStartPointIndex);
	}
}

/*--------------------------------------------------------------------------*/
/* CreateAverageGeometryForAllLayers                                        */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateAverageGeometryForAllLayers()
{
	// Create a point array.
	CreatePointArray();

	// Set the size of the point array = 2 * (number of rows + 1) * (number of columns + 1) * number of layers
	m_pcFloatPoints->SetNumberOfPoints(2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1) * m_pcModelInfo->GetNumberOfLayers());
	
	// repeat for all layers
	for (int iLayer = 1; iLayer <= m_pcModelInfo->GetNumberOfLayers(); iLayer++)
	{
		int iLayerStartCellIndex = GetLayerStartCellIndex(iLayer);
		int iLayerStartPointIndex = GetAverageLayerStartPointIndex(iLayer);

		// Create average points.
		CreateAveragePoints(iLayer, iLayerStartCellIndex);

		// insert the points
		for (int i = 0; i < 2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1); i++)
			// Calculate row and column indexes using the point array index.
			// Insert a point into the point array where:
			//	point.x = Get the column coordinate for column index.
			//	point.y = Get the row coordinate for row index.
			//	point.z = Get the average elevation from average point array.
			m_pcFloatPoints->InsertPoint(	i + iLayerStartPointIndex, 
											m_pcModelInfo->GetColumnCoordinate(CalculateColumnIndex(i)), 
											m_pcModelInfo->GetRowCoordinate(CalculateRowIndex(i)),
											m_pcAverageArray.GetAt(i)->GetAverage());
	}
}

/*--------------------------------------------------------------------------*/
/* CreateAveragePoints  	                                                */
/*--------------------------------------------------------------------------*/
void CGeometry::CreateAveragePoints(int iLayer, int iLayerStartCellIndex /* = 0 */)
{
	// Set the size of the average point array = 2 * (number of rows + 1) * (number of columns + 1).
	m_pcAverageArray.SetSize(2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1), 1);
	
	// Initialize the average point array.
	for (int i = 0; i < 2 * (m_pcModelInfo->GetNumberOfRows() + 1) * (m_pcModelInfo->GetNumberOfColumns() + 1); i++)
	{
		CAverage* pcAverage = new CAverage();
		m_pcAverageArray[i] = pcAverage;
	}

	// Read the top elevation for all cells into a top elevation array.
	float* pfTopArray = ReadTimeIndependentData("top", iLayer);

	// Read the bottom elevation for all cells into a bottom elevation array.
	float* pfBottomArray = ReadTimeIndependentData("bot", iLayer);

	// For number of rows.
	for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
		// For number of columns.
		for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
			// If it is an active cell.
			if (m_bActiveCellsArray[i * m_pcModelInfo->GetNumberOfColumns() + j + iLayerStartCellIndex])
				InsertAveragePoints(i, j, pfTopArray, pfBottomArray);

	// clean
	delete [] pfTopArray;
	delete [] pfBottomArray;
}

/*--------------------------------------------------------------------------*/
/* InsertNormalPoints                                                       */
/*--------------------------------------------------------------------------*/
void CGeometry::InsertNormalPoints(int iRowIndex, int iColumnIndex, float fZTopValue, float fZBottomValue, int iLayerStartPointIndex /* = 0 */)
{
	// Create 2 column coordinates for current row and column.
	float fXP02 = m_pcModelInfo->GetColumnCoordinate(iColumnIndex);
	float fXP13 = m_pcModelInfo->GetColumnCoordinate(iColumnIndex + 1);

	// Create 2 row coordinates for current row and column.
	float fYP01 = m_pcModelInfo->GetRowCoordinate(iRowIndex);
	float fYP23 = m_pcModelInfo->GetRowCoordinate(iRowIndex + 1);

	// Calculate 4 top point indexes into point array for 4 top points of cell.
	int iPTop[4];
	CalculateTopIndexes(iPTop, GetP0NormalIndex(iRowIndex, iColumnIndex), GetP2NormalIndex(iRowIndex, iColumnIndex), iLayerStartPointIndex);

	// Insert 4 points into the point array, using the 4 top point indexes, row and column coordinates and top elevation.
	m_pcFloatPoints->InsertPoint(iPTop[0], fXP02, fYP01, fZTopValue);
	m_pcFloatPoints->InsertPoint(iPTop[1], fXP13, fYP01, fZTopValue);
	m_pcFloatPoints->InsertPoint(iPTop[2], fXP02, fYP23, fZTopValue);
	m_pcFloatPoints->InsertPoint(iPTop[3], fXP13, fYP23, fZTopValue);

	// Calculate 4 bottom point indexes into the point array for 4 bottom points of cell.
	int iPBottom[4];
	CalculateBottomIndexes(iPTop, iPBottom, GetNormalNumberOfLayerPoints());

	// Insert 4 points into point array, using the 4 bottom point indexes, row and column coordinates and bottom elevation.
	m_pcFloatPoints->InsertPoint(iPBottom[0], fXP02, fYP01, fZBottomValue);
	m_pcFloatPoints->InsertPoint(iPBottom[1], fXP13, fYP01, fZBottomValue);
	m_pcFloatPoints->InsertPoint(iPBottom[2], fXP02, fYP23, fZBottomValue);
	m_pcFloatPoints->InsertPoint(iPBottom[3], fXP13, fYP23, fZBottomValue);
}

/*--------------------------------------------------------------------------*/
/* InsertAveragePoints                                                      */
/*--------------------------------------------------------------------------*/
void CGeometry::InsertAveragePoints(int iRowIndex, int iColumnIndex, float* pfTopArray, float* pfBottomArray)
{
	// Calculate 4 top average point indexes into average point array for cell.
	int iPTop[4];
	CalculateTopIndexes(iPTop, GetP0AverageIndex(iRowIndex, iColumnIndex), GetP2AverageIndex(iRowIndex, iColumnIndex));

	// Add the top elevation to the average point array, using the 4 top average point indexes.
	for (int iPointIndex = 0; iPointIndex < 4; iPointIndex++)
		m_pcAverageArray[iPTop[iPointIndex]]->AddToSum(pfTopArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex]);

	// Calculate 4 bottom average point indexes into average point array for cell.
	int iPBottom[4];
	CalculateBottomIndexes(iPTop, iPBottom, GetAverageNumberOfLayerPoints());

	// Add the bottom elevation to the average point array, using the 4 bottom average point indexes.
	for (int iPointIndex = 0; iPointIndex < 4; iPointIndex++)
		m_pcAverageArray[iPBottom[iPointIndex]]->AddToSum(pfBottomArray[iRowIndex * m_pcModelInfo->GetNumberOfColumns() + iColumnIndex]);
}

/*--------------------------------------------------------------------------*/
/* CreatePointArray                                                         */
/*--------------------------------------------------------------------------*/
void CGeometry::CreatePointArray()
{
	if (m_pcFloatPoints) 
		m_pcFloatPoints->Delete();
	m_pcFloatPoints = vtkPoints::New();
}