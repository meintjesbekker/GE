/*--------------------------------------------------------------------------*/
/*							HydraulicComponent.h  							*/
/*                            												*/
/*	Purpose	: Create a Hydraulic Component.                                 */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENT_H__77D54951_806D_11D3_B107_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENT_H__77D54951_806D_11D3_B107_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ClipPolyData.h"
#include "Geometry.h"
#include "HydraulicComponentGUI.h"
#include "Model.h"
#include "ReadFile.h"
#include "SidesQuadTopology.h"
#endif // _MSC_VER > 1000

class CHydraulicComponent : public CHydraulicComponentGUI,
							public CGeometry,
							public CSidesQuadTopology
{
// public operations
public:
	CHydraulicComponent(CModel* pcModel = NULL);
	virtual ~CHydraulicComponent();
	HYDRAULICCOMPONENTTYPE GetHydraulicComponentType() const {return m_cHydraulicComponentType;};
	void SetHydraulicComponentType(HYDRAULICCOMPONENTTYPE cHydraulicComponentType) {m_cHydraulicComponentType = cHydraulicComponentType;};

	void AppendTimeIndependentPolyData(HYDRAULICCOMPONENTTYPE cHydraulicComponentType);
	void AppendTimeDependentPolyData(HYDRAULICCOMPONENTTYPE cHydraulicComponentType, int iStressPeriod);

	// time independent hydraulic components
	void CreateFixedHeadCell();
	void CreateFixedConcentrationCell();
	void CreateHorizontalFlowBarrier();
	void CreateReservoir();

	// time dependent hydraulic components
	void CreateGeneralHeadBoundaryCell(int iStressPeriod);
	void CreateDischargeWell(int iStressPeriod);
	void CreateRechargeWell(int iStressPeriod);
	void CreateDrain(int iStressPeriod);
	void CreateRiver(int iStressPeriod);
	void CreateTimeVariantSpecifiedHead(int iStressPeriod);
	void CreateTimeVariantSpecifiedConcentration(int iStressPeriod);
	
	// update
	void UpdateTimeIndependentHydraulicComponent();
	void UpdateTimeDependentHydraulicComponent(int iStressPeriod);
	
	// interact 
	void Clip();
	void UpdateActor();	

// private operations
private:
	// create active cells array
	void CreateActiveCellsArray(CString sFileExtension, int iLayer, BOOL (CHydraulicComponent::*pFunc)(float*, int, int));
	void CreateTimeDependentActiveCellsArray(CString sFileExtension, int iLayer, int iStressPeriod, BOOL (CHydraulicComponent::*pFunc)(float*, int, int));

	// time independent hydraulic components
	void CreateActiveCellsArrayForFixedHeads(int iLayer);
	void CreateActiveCellsArrayForFixedConcentration(int iLayer);
	void CreateActiveCellsArrayForHorizontalFlowBarrier(int iLayer);
	void CreateActiveCellsArrayForReservoir(int iLayer);

	// time dependent hydraulic components
	void CreateActiveCellsArrayForGeneralHeadBoundary(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForDischargeWell(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForRechargeWell(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForDrain(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForRiver(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForTimeVariantSpecifiedHead(int iLayer, int iStressPeriod);
	void CreateActiveCellsArrayForTimeVariantSpecifiedConcentration(int iLayer, int iStressPeriod);

	// test if it is an active cell
	BOOL TestIfActiveCellSmaller(float* pfArray, int iRowIndex, int iColumnIndex);
	BOOL TestIfActiveCellNotEqual(float* pfArray, int iRowIndex, int iColumnIndex);
	BOOL TestIfActiveCellGreater(float* pfArray, int iRowIndex, int iColumnIndex);
	
	// create
	void ComputePointNormals();
	void CreateMapper();

// private attributes
private:
	// type
	HYDRAULICCOMPONENTTYPE m_cHydraulicComponentType;

	// vtk
	vtkAppendPolyData* m_pcAppendPolyData;
	vtkPolyDataNormals* m_pcPolyDataNormals;
};

#endif // !defined(AFX_HYDRAULICCOMPONENT_H__77D54951_806D_11D3_B107_0060084B410C__INCLUDED_)