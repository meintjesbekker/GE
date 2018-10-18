/*--------------------------------------------------------------------------*/
/*						PotentiometricSurface.h								*/
/*                            												*/
/*	Purpose	: Create a potentiometric surface visualization object for a    */
/*			  specified stress period and time step or for the groundwater  */
/*			  heads in the highest active cells.					 		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_POTENTIOMETRICSURFACE_H__0CB205F1_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)
#define AFX_POTENTIOMETRICSURFACE_H__0CB205F1_EDB4_11D3_B1AC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "Average.h"
#include "Geometry.h"
#include "LookupTable.h"
#include "Model.h"
#include "PotentiometricSurfaceGUI.h"
#include "ReadFile.h"
#include "TimeAndLayerParameter.h"
#include "TopQuadTopology.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

// function defintion to read fortran95 file for heads and time
extern "C" { void __stdcall HEADTIME(	char cName[180], 
										long int* pliNumberOfTimeIntervals, 
										long int* pliPeriods,
										long int* pliTimeSteps,
										long int* pliNumberOfLayers,
										long int* pliNX, 
										long int* pliNY,
										long int* pliLayerNumber, 
										long int* pliError);}

// function defintion to read fortran95 file for heads
extern "C" { void __stdcall READHEAD(	char cName[180],
										long int* pliPeriod,
										long int* pliTimeStep,
										float* pfHead,
										long int* pliNX, 
										long int* pliNY, 
										long int* pliNZ,
										long int* pliLayerNumber, 
										long int* pliError);}

class CPotentiometricSurface :	public CPotentiometricSurfaceGUI,
								public CGeometry,
								public CTopQuadTopology,
								public CVisualizationObject
{
// public operations
public:
	CPotentiometricSurface(CModel* pcModel = NULL);
	virtual ~CPotentiometricSurface();

	// create, update and clip
	virtual void Create();
	virtual void Update();
	virtual void Clip();

	// other
	int ReadHeadTimes();
	void ReadHeadFile();
	void ReadHighestHeadFile();

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();

// private operations
private:
	void ReadFile();
	void CreateMinimumAndMaximumHeads();
	BOOL TestIfActiveCell(int iRowIndex, int iColumnIndex);
	void InsertNormalPointsAndScalars(int iRowIndex, int iColumnIndex, float fHead);
	void CreateNormalGeometryAndScalarDatasetAttribute();
	void InsertAveragePoints(int iRowIndex, int iColumnIndex);
	void CreateAveragePoints();
	void CreateAverageGeometryAndScalarDatasetAttribute();
	void CreateGeometry();
	void CreateTopolgy();
	void CreateColor();
	void CreateLookupTable();
	void CreateMapper();
	void CreateScalarArray();
	void GetHeadsFileName(char cName[180]);
	void CreateHeadsArray();
	float* ReadHeadFileForLayer(int iLayer);
	void CreateActiveCellsArray();

// public attributes
public:
	CTimeAndLayerParameter m_cTimeAndLayerParameter;

// private attributes
private:
	// heads
	float* m_pfHeads;

	// derived vtk class
	CLookupTable* m_pcLookupTable;
};

#endif // !defined(AFX_POTENTIOMETRICSURFACE_H__0CB205F1_EDB4_11D3_B1AC_0060084B410C__INCLUDED_)