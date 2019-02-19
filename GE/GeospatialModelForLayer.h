/*--------------------------------------------------------------------------*/
/*						GeospatialModelForLayer.h							*/
/*                            												*/
/*	Purpose	: Construct a geospatial model visualization object for a		*/
/*			  single layer.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_GEOSPATIALMODELFORLAYER_H__7A82C279_CCB9_11D3_B161_0060084B410C__INCLUDED_)
#define AFX_GEOSPATIALMODELFORLAYER_H__7A82C279_CCB9_11D3_B161_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Average.h"
#include "Model.h"
#include "Geometry.h"
#include "GeospatialModelForLayerGUI.h"
#include "ReadFile.h"
#include "SidesQuadTopology.h"
#endif // _MSC_VER > 1000

class CGeospatialModelForLayer : public CGeospatialModelForLayerGUI,
								 public CGeometry,
								 public CSidesQuadTopology
{
// public operations
public:
	CGeospatialModelForLayer(CModel* pcModel = NULL, int iLayerNumber = 0);
	virtual ~CGeospatialModelForLayer();
	void Create();
	void Update();
	void Clip();

// private operations
private:
	void ExtractEdges();
	void CreateMapper();
	void CreateGeometry();
	void CreateTopology();
	// void CreateScalarBarActor();

// private attributes
private:
	// number of the layer
	int	m_iLayerNumber;
};

#endif // !defined(AFX_GEOSPATIALMODELFORLAYER_H__7A82C279_CCB9_11D3_B161_0060084B410C__INCLUDED_)