/*--------------------------------------------------------------------------*/
/*								Parameter.h									*/
/*                            												*/
/*	Purpose	: Color map model cells which contains parameter information. 	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.8 "Parameter".                              */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_PARAMETER_H__5881C985_A0C9_11D3_B129_0060084B410C__INCLUDED_)
#define AFX_PARAMETER_H__5881C985_A0C9_11D3_B129_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Average.h"
#include "Geometry.h"
#include "HexahedronTopology.h"
#include "LookupTable.h"
#include "Model.h"
#include "ParameterGUI.h"
#include "ReadFile.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

class CParameter :  public CParameterGUI,
					public CGeometry,
					public CHexahedronTopology,
					public CVisualizationObject 
{
// public operations
public:
	CParameter(CModel* pModel = NULL);
	virtual ~CParameter();

	// create, update and clip
	void CreateParameter(PARAMETERTYPE cParameter = EMPTYPARAMETER);
	virtual void Create();
	virtual void Update();
	virtual void Clip();

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();

// private operations
private:
	void CreateActiveCellsArray();
	void DoPipeline();
	void SetDescriptions();
	void SetFolderAndFileNames();
	void SetFolderAndFileName(CString sFileExtension);
	void CreateParameterMinimumAndMaximum();
	void CreateGeometry();
	void CreateDataSet();
	void CreateColor();
	void CreateLookupTable();
	void CreateMapper();

	// interact 
	void ClipParameter();

	// other
	float* ReadTimeIndependentData(CString sFileExtension, int iLayer);

// private attributes
private:
	// parameter type
	PARAMETERTYPE m_cParameter;

	// path and file name
	CString	m_sFolderAndFileName;

	// vtk
	vtkUnstructuredGrid* m_pcUnstructuredGrid;
	CLookupTable* m_pcLookupTable;
	vtkGeometryFilter* m_pcGeometryFilter;

	// other    
	CReadFile m_cReadFile;
};

#endif // !defined(AFX_PARAMETER_H__5881C985_A0C9_11D3_B129_0060084B410C__INCLUDED_)