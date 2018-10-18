/*--------------------------------------------------------------------------*/
/*							HydraulicComponents.h  							*/
/*                            												*/
/*	Purpose	: Create Hydraulic Components.                                  */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICCOMPONENTS_H__77D54952_806D_11D3_B107_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICCOMPONENTS_H__77D54952_806D_11D3_B107_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "HydraulicComponent.h"
#include "VisualizationObject.h"
#endif // _MSC_VER > 1000

class CHydraulicComponents 
	: public CVisualizationObject
{
// public operations
public:
	CHydraulicComponents(CModel* pcModel = NULL);
	virtual ~CHydraulicComponents();
	CHydraulicComponent* GetHydraulicComponent(int iIndex) const {return m_pcHydraulicComponentArray[iIndex];};
	int GetArraySize() const {return m_pcHydraulicComponentArray.GetSize();};

	// average page
	BOOL GetAverage() const {return m_bAverage;};
	void SetAverage(BOOL bAverage);

	// other
	void ReadTimeParameterFile();
	int GetNumberOfStressPeriods() const {return m_iNumberOfStressPeriods;};
	int GetStressPeriod() const {return m_iStressPeriod;};
	void SetStressPeriod(int iStressPeriod) {m_iStressPeriod = iStressPeriod;};

	// clip
	virtual void Clip();

// protected attributes
protected:
	CModel*	m_pcModel;
	int m_iStressPeriod;
	CArray<CHydraulicComponent*, CHydraulicComponent*> m_pcHydraulicComponentArray;

// private attributes
private:
	// number of stress periods from time parameter file *.trn
	int m_iNumberOfStressPeriods;

	// average
	BOOL m_bAverage;
};

#endif // !defined(AFX_HYDRAULICCOMPONENTS_H__77D54952_806D_11D3_B107_0060084B410C__INCLUDED_)