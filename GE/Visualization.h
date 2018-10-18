/*--------------------------------------------------------------------------*/
/*							Visualization.h									*/
/*                            												*/
/*	Purpose	: Contains visualization objects.                          		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_VISUALIZATION_H__65B83061_53DB_11D3_B819_0060084B410C__INCLUDED_)
#define AFX_VISUALIZATION_H__65B83061_53DB_11D3_B819_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ModelOutline.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

class CVisualization : public CObject
{
// public operations
public:
	CVisualization();
	virtual ~CVisualization();
	CVisualizationObject* GetVisualizationObject(int iIndex);
	int	CreateModelOutline(CModel* pcModel = NULL);
	int AddVisualizationObjectToArray(CVisualizationObject* pcVisualizationObject);
	BOOL VisualizationExist();
	void Clip();
	virtual void Serialize(CArchive& ar);

	// serialize
	DECLARE_SERIAL(CVisualization)

// public attributes
public:
	CArray<CVisualizationObject*, CVisualizationObject*> m_pcVisualizationObjectArray;
};

#endif // !defined(AFX_VISUALIZATION_H__65B83061_53DB_11D3_B819_0060084B410C__INCLUDED_)