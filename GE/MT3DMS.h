/*--------------------------------------------------------------------------*/
/*								MT3DMS.h   									*/
/*                            												*/
/*	Purpose	: Create isosurfaces for MT3DMS, PHT3D or RT3D concentrations.	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".                             */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMS_H__C8641701_AD3F_11D3_B137_0060084B410C__INCLUDED_)
#define AFX_MT3DMS_H__C8641701_AD3F_11D3_B137_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Color.h"
#include "Geometry.h"
#include "Model.h"
#include "MT3DMSGUI.h"
#include "MT3DMSLookupTable.h"
#include "MT3DMSTopology.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

extern "C" { void __stdcall CONTIME(	char pcName[180],
										long int* pliNumberOfTimeIntervals,
										float* pfTimeIntervals,
										long int* liNX,
										long int* liNY,
										long int* liLayer,
										long int* liError);}

extern "C" { void __stdcall READCON(	char pcName[180],
										float* pfTime,
										float* pfCon,
										long int* liNX,
										long int* liNY,
										long int* liLayer,
										long int* layern,
										long int* liError);}

class CMT3DMS : public CMT3DMSGUI,
				public CGeometry,
				public CMT3DMSTopology,
				public CVisualizationObject
{
// public operations
public:
	CMT3DMS(CModel* pcModel = NULL);
	virtual ~CMT3DMS();
	virtual void Initialize(CString sFilePrefix = _T("mt3d"));
	virtual void Create();
	virtual void Update();
	virtual void Clip();

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();
	
	// total elapsed times
	void ReadTotalElapsedTimesFromFile();

// private operations
private:
	void CreateScalarDatasetAttribute();

	// read files
	void ReadSpeciesFromFile();
	void GetConcentrationFileName(char cName[180]);
	
	// create
	void CreateDataSet();
	void CreateContourAndColorTable();
	void CreateLookupTable();
	void CalculatePointNormals();
	void ClipMT3DMS();
	void CreateMapper();

// private attributes
private:
	// file prefix
	CString m_sFilePrefix;
	
	// number of points used in cell depth
	int m_iNumberOfPoints;

	// vtk
	vtkStructuredGrid* m_pcStructuredGrid;
	vtkPolyDataNormals* m_pcPolyDataNormals;
	vtkGeometryFilter* m_pcGeometryFilter;
	CMT3DMSLookupTable* m_pcLookupTable;
};

#endif // !defined(AFX_MT3DMS_H__C8641701_AD3F_11D3_B137_0060084B410C__INCLUDED_)