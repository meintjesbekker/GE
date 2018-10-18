/*--------------------------------------------------------------------------*/
/*								TimeStep.h									*/
/*                            												*/
/*	Purpose	: Time step.													*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_TIMESTEP_H__A936F3F4_E907_11D3_B1A3_0060084B410C__INCLUDED_)
#define AFX_TIMESTEP_H__A936F3F4_E907_11D3_B1A3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#endif // _MSC_VER > 1000

class CTimeStep  
{
// public operations
public:
	CTimeStep();
	virtual ~CTimeStep();
	void SetTimeStep(int iTimeStep) {m_iTimeStep = iTimeStep;};
	int	GetTimeStep() const {return m_iTimeStep;};
	int FindLayer(int iLayer);
	void AddLayer(int iLayer) {m_LayerArray.Add(iLayer);};
	int GetLayerArraySize() const {return m_LayerArray.GetSize();};
	int GetLayerFromIndex(int iIndex) const {return m_LayerArray[iIndex];};

// protected attributes
protected:
	int m_iTimeStep;
	CArray<int, int> m_LayerArray;
};

#endif // !defined(AFX_TIMESTEP_H__A936F3F4_E907_11D3_B1A3_0060084B410C__INCLUDED_)
