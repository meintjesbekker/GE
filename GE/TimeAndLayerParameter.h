/*--------------------------------------------------------------------------*/
/*						TimeAndLayerParameter.h								*/
/*                            												*/
/*	Purpose	: Handles stress periods for layers.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.4 "Potentiometric Surface".					*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_TIMEANDLAYERPARAMETER_H__A936F3F1_E907_11D3_B1A3_0060084B410C__INCLUDED_)
#define AFX_TIMEANDLAYERPARAMETER_H__A936F3F1_E907_11D3_B1A3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "StressPeriod.h"
#endif // _MSC_VER > 1000

class CTimeAndLayerParameter
{
// public operations
public:
	CTimeAndLayerParameter();
	virtual ~CTimeAndLayerParameter();
	CStressPeriod* GetStressPeriod(int iStressPeriod);
	int FindStressPeriod(int iStressPeriod);
	void AddStressPeriod(int iStressPeriod, int iTimeStep, int iLayer);
	int GetStressPeriodArraySize() const {return m_pcStressPeriodArray.GetSize();};
	int GetStressPeriodFromIndex(int iIndex) const {return m_pcStressPeriodArray[iIndex]->GetStressPeriod();};

// private attributes
private:
	CArray<CStressPeriod*, CStressPeriod*> m_pcStressPeriodArray;
};

#endif // !defined(AFX_TIMEANDLAYERPARAMETER_H__A936F3F1_E907_11D3_B1A3_0060084B410C__INCLUDED_)
