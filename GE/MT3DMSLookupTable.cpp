/*--------------------------------------------------------------------------*/
/*							MT3DMSLookupTable.cpp  							*/
/*                            												*/
/*	Purpose	: Lookup table to color map Isosurface value.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.6 "Isosurface".                             */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "MT3DMSLookupTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                     		*/
/*--------------------------------------------------------------------------*/
CMT3DMSLookupTable::CMT3DMSLookupTable()
{
	m_pcContourAndColorTable = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                      		*/
/*--------------------------------------------------------------------------*/
CMT3DMSLookupTable::~CMT3DMSLookupTable()
{
}

/*--------------------------------------------------------------------------*/
/* SetColorTable                                                     		*/
/*--------------------------------------------------------------------------*/
void CMT3DMSLookupTable::SetColorTable(CMT3DMSContourAndColorTable* pcContourAndColorTable)
{
	m_pcContourAndColorTable = pcContourAndColorTable;
	for (int i = 0; i < m_pcContourAndColorTable->GetSize(); i++)
	{
		float fRed = GetRValue(m_pcContourAndColorTable->GetColor(i)) / 255.0;
		float fGreen = GetGValue(m_pcContourAndColorTable->GetColor(i)) / 255.0;
		float fBlue	= GetBValue(m_pcContourAndColorTable->GetColor(i)) / 255.0;
		SetTableValue(i, fRed, fGreen, fBlue, 1);
	}
	m_pcContourAndColorTable->GetMinimumScalarValue();
	SetTableRange(m_pcContourAndColorTable->GetMinimumScalarValue(), m_pcContourAndColorTable->GetMaximumScalarValue());
}

/*--------------------------------------------------------------------------*/
/* MapValue                                                         		*/
/*--------------------------------------------------------------------------*/
unsigned char* CMT3DMSLookupTable::MapValue(float v)
{
	int index = 0;
	for (int i = 0; i < m_pcContourAndColorTable->GetSize(); i++)
	{
		if (v <= 1E-05)
		{
			if (v == m_pcContourAndColorTable->GetValue(i))
			{
				index = i;
				return Table->GetPointer(index*4);
			}
		}
		else
			if (fabs(v - m_pcContourAndColorTable->GetValue(i)) < 1E-5)
			{
				index = i;
				return Table->GetPointer(index*4);
			}
	}

	if (v < m_pcContourAndColorTable->GetMinimumScalarValue())
	{
		index = 0;
		return Table->GetPointer(index*4);
	}

	if (v >= m_pcContourAndColorTable->GetMaximumScalarValue())
	{
		index = m_pcContourAndColorTable->GetSize() - 1;
		return Table->GetPointer(index*4);
	}	
	return Table->GetPointer(index*4);
}

/*--------------------------------------------------------------------------*/
/* SetTableRange                                                    		*/
/*--------------------------------------------------------------------------*/
void CMT3DMSLookupTable::SetTableRange(float min, float max)
{
	TableRange[0] = min;
	TableRange[1] = max;
}

/*--------------------------------------------------------------------------*/
/* GetTableIndex                                                    		*/
/*--------------------------------------------------------------------------*/
int CMT3DMSLookupTable::GetTableIndex(float fValue)
{
	int iIndex = 0;
	for (int i = 0; i < m_pcContourAndColorTable->GetSize(); i++)
		if (fValue == m_pcContourAndColorTable->GetValue(i))
			iIndex = i;
	if (fValue < m_pcContourAndColorTable->GetMaximumScalarValue())
		iIndex = 0;
	if (fValue >= m_pcContourAndColorTable->GetMaximumScalarValue())
		iIndex = m_pcContourAndColorTable->GetSize() - 1;
	return iIndex;
}