/*--------------------------------------------------------------------------*/
/*							StressPeriod.h									*/
/*                            												*/
/*	Purpose	: Stress period with time steps for each stress period.			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_STRESSPERIOD_H__A936F3F3_E907_11D3_B1A3_0060084B410C__INCLUDED_)
#define AFX_STRESSPERIOD_H__A936F3F3_E907_11D3_B1A3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "TimeStep.h"
#endif // _MSC_VER > 1000

class CStressPeriod  
{
// public operations
public:
	CStressPeriod();
	virtual ~CStressPeriod();
	int GetStressPeriod() const {return m_iStressPeriod;};
	void SetStressPeriod(int iStressPeriod) {m_iStressPeriod = iStressPeriod;};
	CTimeStep* GetTimeStep(int iTimeStep);
	int FindTimeStep(int iTimeStep);
	void AddTimeStep(int iTimeStep, int iLayer);
	int GetTimeStepArraySize() const {return m_pcTimeStepArray.GetSize();};
	int GetTimeStepFromIndex(int iIndex) const {return m_pcTimeStepArray[iIndex]->GetTimeStep();};

// private attributes
private:
	int m_iStressPeriod;
	CArray<CTimeStep*, CTimeStep*> m_pcTimeStepArray;
};

#endif // !defined(AFX_STRESSPERIOD_H__A936F3F3_E907_11D3_B1A3_0060084B410C__INCLUDED_)