/*--------------------------------------------------------------------------*/
/*							MT3DMSLookupTable.h    							*/
/*                            												*/
/*	Purpose	: Lookup table to color map Isosurface value.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".                             */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSLOOKUPTABLE_H__E36276E1_1032_11D4_B1E4_0060084B410C__INCLUDED_)
#define AFX_MT3DMSLOOKUPTABLE_H__E36276E1_1032_11D4_B1E4_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "MT3DMSContourAndColorTable.h"
#endif // _MSC_VER > 1000

class CMT3DMSLookupTable : public vtkLookupTable
{
// public operations
public:
	CMT3DMSLookupTable();
	virtual ~CMT3DMSLookupTable();
	static CMT3DMSLookupTable* New() {return new CMT3DMSLookupTable;};
	const char *GetClassName() {return "CMT3DMSLookupTable";};
	void SetNumberOfColors(int iNumberOfColors) {vtkLookupTable::SetNumberOfColors(iNumberOfColors);};
	void SetColorTable(CMT3DMSContourAndColorTable* pcContourAndColorTable);
	virtual unsigned char* MapValue(float v);
	virtual void SetTableRange(float min, float max);
	int GetTableIndex(float fValue);

// private attribute
private:
	CMT3DMSContourAndColorTable* m_pcContourAndColorTable;
};

#endif // !defined(AFX_MT3DMSLOOKUPTABLE_H__E36276E1_1032_11D4_B1E4_0060084B410C__INCLUDED_)