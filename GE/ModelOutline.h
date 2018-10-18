/*--------------------------------------------------------------------------*/
/*							ModelOutline.h									*/
/*                            												*/
/*	Purpose	: Construct a model outline visualization object.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.2 "Model Outline".                          */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MODELOUTLINE_H__84C0BFC2_20D9_11D4_B1FA_0060084B410C__INCLUDED_)
#define AFX_MODELOUTLINE_H__84C0BFC2_20D9_11D4_B1FA_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Mapper.h"
#include "Model.h"
#include "VisualizationObject.h"
#include "XYZCoordinate.h"
#endif // _MSC_VER > 1000

class CModelOutline :	public CMapper,
						public CVisualizationObject
{
// public operations
public:
	CModelOutline(CModel* pcModel);
	virtual ~CModelOutline();

	// general page
	void SetMinimumCornerCoordinate(float fX, float fY, float fZ);
	void SetMaximumCornerCoordinate(float fX, float fY, float fZ);
	
	// create pipeline
	virtual void Initialize() {};
	virtual void Create();
	virtual void Update() {};
	virtual void Clip() {};

	// create dialog sheet and pages
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();

	// serialize
	virtual void Serialize(CArchive& ar);

// private operations
private:
	void CreateOutlineSource();
	void CreateActor();

// public attributes
public:
	// general page
	CXYZCoordinate m_cMinimumCornerCoordinate;
	CXYZCoordinate m_cMaximumCornerCoordinate;

// private attributes
private:
	// vtk
	vtkOutlineSource* m_pcOutlineSource;
};

#endif // !defined(AFX_MODELOUTLINE_H__84C0BFC2_20D9_11D4_B1FA_0060084B410C__INCLUDED_)