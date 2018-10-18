/*--------------------------------------------------------------------------*/
/*							LookupTable.h   								*/
/*                            												*/
/*	Purpose	: Lookup table to color map range.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.9 "Lookup Table".                         */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_LOOKUPTABLE_H__371A2B05_E2AB_11D3_B196_0060084B410C__INCLUDED_)
#define AFX_LOOKUPTABLE_H__371A2B05_E2AB_11D3_B196_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxtempl.h>
#include "ColorTable.h"
#endif // _MSC_VER > 1000

class CLookupTable : public vtkLookupTable
{
// public operations
public:
	CLookupTable();
	virtual ~CLookupTable();
	static CLookupTable* New() {return new CLookupTable;};
	const char* GetClassName() {return "CLookupTable";};
	void SetNumberOfColors(int iNumberOfColors);
	void SetColorTable(CColorTable* pcColorTable);
	virtual unsigned char* MapValue(float v);
	virtual void SetTableRange(float min, float max);
	int GetTableIndex(float fValue);

// private attributes
private:
	CColorTable* m_cColorTable;
};

#endif // !defined(AFX_LOOKUPTABLE_H__371A2B05_E2AB_11D3_B196_0060084B410C__INCLUDED_)