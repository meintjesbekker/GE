/*--------------------------------------------------------------------------*/
/*								Model.cpp 									*/
/*                            												*/
/*	Purpose	: Contains PMWIN model information.                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "GeospatialModel.h"
#include "Model.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Implement Serial       													*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_SERIAL(CModel, CObject, 1);

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CModel::CModel()
{
	m_iNumbColumns = 0; 
	m_iNumbRows = 0;
	m_iNumbLayers = 0;

	// bClip
	m_bClip = FALSE;
	m_fXClipPlaneOrigin = 0;
	m_fYClipPlaneOrigin = 0;
	m_fZClipPlaneOrigin = 0;
	m_fXClipPlaneNormal = 1;
	m_fYClipPlaneNormal = 0;
	m_fZClipPlaneNormal = 0;

	// scale
	m_fXScale = 1;
	m_fYScale = 1;
	m_fZScale = 1;

	// label axes
	m_bXVisible = TRUE;
	m_bYVisible = TRUE;
	m_bZVisible = FALSE;
	m_iNumberOfLabels = 3;
	m_fFontFactor = 0.8;
	m_cColor = RGB(0, 0, 0);

	// cColor axes
	m_bColorAxesVisible = TRUE;
	m_fColumnsOrigin = 0;
	m_fRowsOrigin = 0;

	m_sFolderAndFileName = "";
	
	// flag for no flow head cells
	m_fHeadsNoFlow = 0;	
	
	// flag for dry head cells
	m_fHeadsDry = 0;

	// flag for concentration inactive cells
	m_fConcentrationInactive = 0;
	m_pfColumnSpacing = NULL;
	m_pfRowSpacing = NULL;
	m_pfColumnCoordinates = NULL;
	m_pfRowCoordinates = NULL;
	m_pfMiddleColumnCoordinates = NULL;
	m_pfMiddleRowCoordinates = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CModel::~CModel()
{
	if (m_pfColumnSpacing)
		delete [] m_pfColumnSpacing;
	if (m_pfRowSpacing)
		delete [] m_pfRowSpacing;
	if (m_pfColumnCoordinates)
		delete [] m_pfColumnCoordinates;
	if (m_pfRowCoordinates)
		delete [] m_pfRowCoordinates;
	if (m_pfMiddleColumnCoordinates)
		delete [] m_pfMiddleColumnCoordinates;
	if (m_pfMiddleRowCoordinates)
		delete [] m_pfMiddleRowCoordinates;
}

/*--------------------------------------------------------------------------*/
/* ReadPM5File                                                              */
/*--------------------------------------------------------------------------*/
void CModel::ReadPM5File()
{
	CString sString;
	FILE* pFile;
	char cBufferArray[256];
	pFile = fopen(m_sFolderAndFileName.SpanExcluding(".") + ".pm5", "r");
	if (!pFile)
	{
		sString.Format("Cann't open the *.PM5 file.");
		AfxMessageBox(sString);		
	}
	else
	{
		while (fgets(cBufferArray, 255, pFile) != NULL)
		{
			sString.Format(cBufferArray);
			sString.TrimLeft();
			sString.TrimRight();

			// columns origin
			if (sString.Find("LEFT", 0) != -1)
				m_fColumnsOrigin = atof(sString.Mid(sString.Find('=')+1));

			// rows origin
			if (sString.Find("TOP", 0) != -1)
				m_fRowsOrigin = atof(sString.Mid(sString.Find('=')+1));
		
			// flag for no flow head cells
			if (sString.Find("HNOFLO", 0) != -1)
				m_fHeadsNoFlow = atof(sString.Mid(sString.Find('=')+1));

			// flag for dry head cells
			if (sString.Find("HDRY", 0) != -1)
				m_fHeadsDry = atof(sString.Mid(sString.Find('=')+1));

			// flag for concentration inactive cells
			if (sString.Find("CINACT", 0) != -1)
				m_fConcentrationInactive = atof(sString.Mid(sString.Find('=')+1));
		}
		fclose(pFile);
	}
}

/*--------------------------------------------------------------------------*/
/* ReadGeometryFile                                                         */
/*--------------------------------------------------------------------------*/
void CModel::ReadGeometryFile()
{
	// open the geometry file - basic1.xy
	ifstream gridGeometryFile(m_sFolderAndFileName.SpanExcluding(".") + ".xy", ios::in);
	float fSpaceValue;
	gridGeometryFile >> m_iNumbColumns >> m_iNumbRows >> m_iNumbLayers;

	// initialize column spacing
	if (m_pfColumnSpacing)
	{
		delete [] m_pfColumnSpacing;
		m_pfColumnSpacing = NULL;
	}
	m_pfColumnSpacing = new float[m_iNumbColumns];
	for (int i = 0; i < m_iNumbColumns; i++)
	{
		gridGeometryFile >> fSpaceValue;
		m_pfColumnSpacing[i] = fSpaceValue;
	}
	
	// initialize row spacing
	if (m_pfRowSpacing)
	{
		delete [] m_pfRowSpacing;
		m_pfRowSpacing = NULL;
	}
	m_pfRowSpacing = new float[m_iNumbRows];
	for (int i = 0; i < m_iNumbRows; i++)
	{
		gridGeometryFile >> fSpaceValue;
		m_pfRowSpacing[i] = fSpaceValue;
	}
	gridGeometryFile.close();
	CreateCoordinates();
	CreateMiddleCoordinates();
}

/*--------------------------------------------------------------------------*/
/* SearchForFiles                                                           */
/*--------------------------------------------------------------------------*/
void CModel::SearchForFiles()
{
	m_cFilesExist.SearchForFiles(m_sFolder, m_sFolderAndFileName);
}

/*--------------------------------------------------------------------------*/
/* CreateCoordinates                                                        */
/*--------------------------------------------------------------------------*/
void CModel::CreateCoordinates()
{
	CreateRowCoordinates();
	CreateColumnCoordinates();
}

/*--------------------------------------------------------------------------*/
/* CreateMiddleCoordinates                                                  */
/*--------------------------------------------------------------------------*/
void CModel::CreateMiddleCoordinates()
{
	CreateMiddleRowCoordinates();
	CreateMiddleColumnCoordinates();
}

/*--------------------------------------------------------------------------*/
/* CreateModelBounds                                                        */
/*--------------------------------------------------------------------------*/
void CModel::CreateModelBounds()
{
	m_cMinimumBound.SetX(m_fColumnsOrigin);
	m_cMaximumBound.SetX(m_pfColumnCoordinates[m_iNumbColumns]);
	m_cMinimumBound.SetY(m_pfRowCoordinates[m_iNumbRows]); 
	m_cMaximumBound.SetY(m_fRowsOrigin);
	BOOL bFirst = FALSE;
	for (int iLayer = 1; iLayer <= m_iNumbLayers; iLayer++)
	{
		float* pfArray = new float[m_iNumbRows * m_iNumbColumns];
		float* pfTopArray = new float[m_iNumbRows * m_iNumbColumns];
		float* pfBottomArray = new float[m_iNumbRows * m_iNumbColumns];
		m_cReadFile.ReadTimeIndependentData(	m_sFolderAndFileName.SpanExcluding(".") + ".ibd", 
												pfArray, 
												m_iNumbRows,
												m_iNumbColumns,
												iLayer);
		m_cReadFile.ReadTimeIndependentData(	m_sFolderAndFileName.SpanExcluding(".") + ".top", 
												pfTopArray,
												m_iNumbRows,
												m_iNumbColumns,
												iLayer);
		m_cReadFile.ReadTimeIndependentData(	m_sFolderAndFileName.SpanExcluding(".") + ".bot", 
												pfBottomArray,
												m_iNumbRows,
												m_iNumbColumns,
												iLayer);
		for (int i = 0; i < m_iNumbRows; i++)
			for (int j = 0; j < m_iNumbColumns; j++)
				//    0 = inactive cells
				//  > 0 = active cells
				//  < 0 = fixed head cells
				if (pfArray[i * m_iNumbColumns + j] != 0)
				{
					if (!bFirst)
					{
						if (pfBottomArray[i * m_iNumbColumns + j] < pfTopArray[i * m_iNumbColumns + j])
						{
							m_cMinimumBound.SetZ(pfBottomArray[i * m_iNumbColumns + j]);
							m_cMaximumBound.SetZ(pfTopArray[i * m_iNumbColumns + j]);
						}
						else
						{
							m_cMinimumBound.SetZ(pfTopArray[i * m_iNumbColumns + j]);
							m_cMaximumBound.SetZ(pfBottomArray[i * m_iNumbColumns + j]);
						}
						bFirst = TRUE;
					}
					if (pfBottomArray[i * m_iNumbColumns + j] < m_cMinimumBound.GetZ())
						m_cMinimumBound.SetZ(pfBottomArray[i * m_iNumbColumns + j]);
					if (pfTopArray[i * m_iNumbColumns + j] < m_cMinimumBound.GetZ())
						m_cMinimumBound.SetZ(pfTopArray[i * m_iNumbColumns + j]);
					if (pfBottomArray[i * m_iNumbColumns + j] > m_cMaximumBound.GetZ())
						m_cMaximumBound.SetZ(pfBottomArray[i * m_iNumbColumns + j]);
					if (pfTopArray[i * m_iNumbColumns + j] > m_cMaximumBound.GetZ())
						m_cMaximumBound.SetZ(pfTopArray[i * m_iNumbColumns + j]);
				}
		delete [] pfArray;
		delete [] pfTopArray;
		delete [] pfBottomArray;
	}
	m_fXClipPlaneOrigin = m_cMaximumBound.GetX() / 2.0;
	m_fYClipPlaneOrigin = m_cMaximumBound.GetY() / 2.0;
	m_fZClipPlaneOrigin = m_cMaximumBound.GetZ() / 2.0;
}

/*--------------------------------------------------------------------------*/
/* Serialize                                                                */
/*--------------------------------------------------------------------------*/
void CModel::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_sFolderAndFileName;
		ar << m_sFolder;
	}
	else
	{
		ar >> m_sFolderAndFileName;
		ar >> m_sFolder;

		ReadPM5File();
		ReadGeometryFile();
		SearchForFiles();
		CreateModelBounds();
	}
}

/*--------------------------------------------------------------------------*/
/* CreateRowCoordinates                                                     */
/*--------------------------------------------------------------------------*/
void CModel::CreateRowCoordinates()
{
	if (m_pfRowCoordinates)
		delete [] m_pfRowCoordinates;
	m_pfRowCoordinates = new float[m_iNumbRows + 1];
	float rowCoordinatesSum = m_fRowsOrigin;
	m_pfRowCoordinates[0] = rowCoordinatesSum;
	for (int i = 1; i <= m_iNumbRows; i++)
	{
		rowCoordinatesSum -= m_pfRowSpacing[i - 1];
		m_pfRowCoordinates[i] = rowCoordinatesSum;
	}	
}

/*--------------------------------------------------------------------------*/
/* CreateMiddleRowCoordinates                                               */
/*--------------------------------------------------------------------------*/
void CModel::CreateMiddleRowCoordinates()
{
	if (m_pfMiddleRowCoordinates)
		delete [] m_pfMiddleRowCoordinates;
	m_pfMiddleRowCoordinates = new float[m_iNumbRows];
	float fMiddleRowCoordinatesSum = m_fRowsOrigin;
	for (int i = 0; i < m_iNumbRows; i++)
	{
		m_pfMiddleRowCoordinates[i] = fMiddleRowCoordinatesSum - (0.5 * m_pfRowSpacing[i]);
		fMiddleRowCoordinatesSum -= m_pfRowSpacing[i];
	}	
}

/*--------------------------------------------------------------------------*/
/* CreateColumnCoordinates                                                  */
/*--------------------------------------------------------------------------*/
void CModel::CreateColumnCoordinates()
{
	if (m_pfColumnCoordinates)
		delete [] m_pfColumnCoordinates;
	m_pfColumnCoordinates = new float[m_iNumbColumns + 1];
	float fColumnCoordinatesSum = m_fColumnsOrigin;
	m_pfColumnCoordinates[0] = fColumnCoordinatesSum;
	for (int i = 1; i <= m_iNumbColumns; i++)
	{
		fColumnCoordinatesSum += m_pfColumnSpacing[i - 1];
		m_pfColumnCoordinates[i] = fColumnCoordinatesSum;
	}	
}

/*--------------------------------------------------------------------------*/
/* CreateMiddleColumnCoordinates                                            */
/*--------------------------------------------------------------------------*/
void CModel::CreateMiddleColumnCoordinates()
{
	if (m_pfMiddleColumnCoordinates)
		delete [] m_pfMiddleColumnCoordinates;
	m_pfMiddleColumnCoordinates = new float[m_iNumbColumns];
	float fMiddleColumnCoordinatesSum = m_fColumnsOrigin;
	for (int i = 0; i < m_iNumbColumns; i++)
	{
		m_pfMiddleColumnCoordinates[i] = fMiddleColumnCoordinatesSum + (0.5 * m_pfColumnSpacing[i]);
		fMiddleColumnCoordinatesSum += m_pfColumnSpacing[i];
	}	
}