/*--------------------------------------------------------------------------*/
/*						HexahedronTopology.cpp  							*/
/*                            												*/
/*	Purpose	: Create hexahedron topology.                               	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:																*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "ge.h"
#include "HexahedronTopology.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CHexahedronTopology::CHexahedronTopology(CModel* pcModel /* = NULL */)
	: CIndexes(pcModel)
{
	// vtk
	m_pcCellArray = NULL;

	// other
	m_bVisibleLayersArray.SetSize(pcModel->GetNumberOfLayers(), 1);
	for (int iLayer = 1; iLayer <= pcModel->GetNumberOfLayers(); iLayer++)
		m_bVisibleLayersArray[iLayer - 1] = TRUE;
}

/*--------------------------------------------------------------------------*/
/* Destruction             													*/
/*--------------------------------------------------------------------------*/
CHexahedronTopology::~CHexahedronTopology()
{
	if (m_pcCellArray)
		m_pcCellArray->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateTopolgy                                                            */
/*--------------------------------------------------------------------------*/
void CHexahedronTopology::CreateTopolgy(BOOL bAverage, vtkScalars* pcScalars, CString sFolderAndFileName, CColor* pcColor)
{
	if (bAverage)
		CreateAverageTopologyAndScalarDatasetAttribute(pcScalars, sFolderAndFileName, pcColor);
	else
		CreateNormalTopologyAndScalarDatasetAttribute(pcScalars, sFolderAndFileName, pcColor);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalTopologyAndScalarDatasetAttribute                            */
/*--------------------------------------------------------------------------*/
void CHexahedronTopology::CreateNormalTopologyAndScalarDatasetAttribute(vtkScalars* pcScalars, CString sFolderAndFileName, CColor* pcColor)
{
	CreateNormalOrAverageTopology(	pcScalars,
									sFolderAndFileName,
									pcColor,
									&CIndexes::GetP0NormalIndex,
									&CIndexes::GetP2NormalIndex,
									&CIndexes::GetNormalLayerStartPointIndex,
									GetNormalNumberOfLayerPoints());
}

/*--------------------------------------------------------------------------*/
/* CreateAverageTopologyAndScalarDatasetAttribute                           */
/*--------------------------------------------------------------------------*/
void CHexahedronTopology::CreateAverageTopologyAndScalarDatasetAttribute(vtkScalars* pcScalars, CString	sFolderAndFileName, CColor* pcColor)
{
	CreateNormalOrAverageTopology(	pcScalars,
									sFolderAndFileName,
									pcColor,
									&CIndexes::GetP0AverageIndex,
									&CIndexes::GetP2AverageIndex,
									&CIndexes::GetAverageLayerStartPointIndex,
									GetAverageNumberOfLayerPoints());
}

/*--------------------------------------------------------------------------*/
/* InsertHexahedronCell                                                     */
/*--------------------------------------------------------------------------*/
void CHexahedronTopology::InsertHexahedronCell(int iPTop[4], int iPBottom[4])
{
	// Insert hexahedron into cell pfParameterArray, using the 8, point indexes.
	m_pcCellArray->InsertNextCell(8);
	m_pcCellArray->InsertCellPoint(iPTop[0]);
	m_pcCellArray->InsertCellPoint(iPTop[1]);
	m_pcCellArray->InsertCellPoint(iPTop[3]);
	m_pcCellArray->InsertCellPoint(iPTop[2]);
	m_pcCellArray->InsertCellPoint(iPBottom[0]);
	m_pcCellArray->InsertCellPoint(iPBottom[1]);
	m_pcCellArray->InsertCellPoint(iPBottom[3]);
	m_pcCellArray->InsertCellPoint(iPBottom[2]);
}

/*--------------------------------------------------------------------------*/
/* CreateNormalOrAverageTopology                                            */
/*--------------------------------------------------------------------------*/
void CHexahedronTopology::CreateNormalOrAverageTopology(vtkScalars* pcScalars, 
														CString sFolderAndFileName, 
														CColor* pcColor, 
														int (CIndexes::*pFuncP0Index)(int, int) const,
														int (CIndexes::*pFuncP2Index)(int, int) const, 
														int (CIndexes::*pFuncLayerStartPointIndex)(int) const, 
														int iNumberOfLayerPoints)
{
	// Create a cell array.
	if (m_pcCellArray)
		m_pcCellArray->Delete();
	m_pcCellArray = vtkCellArray::New();
	
	// For all the model layers.
	for (int iLayer = 1; iLayer <= m_pcModelInfo->GetNumberOfLayers(); iLayer++)
	{
		if (m_bVisibleLayersArray[iLayer - 1])
		{
			float* pfParameterArray = new float[m_pcModelInfo->GetNumberOfRows() * m_pcModelInfo->GetNumberOfColumns()];

			// Read parameter value for all cells into parameter pfParameterArray for specific layer.
			m_cReadFile.ReadTimeIndependentData(sFolderAndFileName, 
												pfParameterArray, 
												m_pcModelInfo->GetNumberOfRows(),
												m_pcModelInfo->GetNumberOfColumns(),
												iLayer);

			// For number of rows.
 			for (int i = 0; i < m_pcModelInfo->GetNumberOfRows(); i++)
				// For number of columns.
				for (int j = 0; j < m_pcModelInfo->GetNumberOfColumns(); j++)
					// If it is an active cell and parameter value is in Color Table range.
 					if (m_bActiveCellsArray[GetLayerStartCellIndex(iLayer) + i * m_pcModelInfo->GetNumberOfColumns() + j]
						&& pfParameterArray[i * m_pcModelInfo->GetNumberOfColumns() + j] >= pcColor->m_cColorTable.GetMinimumScalarValue()
						&& pfParameterArray[i * m_pcModelInfo->GetNumberOfColumns() + j] <= pcColor->m_cColorTable.GetMaximumScalarValue())
					{
						// Calculate 4 top point indexes into point array for 4 top points of cell.
						int iPTop[4];
						CalculateTopIndexes(iPTop, (this->*pFuncP0Index)(i, j), (this->*pFuncP2Index)(i, j), (this->*pFuncLayerStartPointIndex)(iLayer));

						// Calculate 4 bottom point indexes into the point array for 4 bottom points of cell.
						int iPBottom[4];
						CalculateBottomIndexes(iPTop, iPBottom, iNumberOfLayerPoints);

						// Insert hexahedron into cell pfParameterArray, using the 8, point indexes.
						InsertHexahedronCell(iPTop, iPBottom);
						
						// Insert parameter value into scalar pfParameterArray.
						pcScalars->InsertNextScalar(pfParameterArray[i * m_pcModelInfo->GetNumberOfColumns() + j]);
					}
			delete [] pfParameterArray;
		}
	}
}