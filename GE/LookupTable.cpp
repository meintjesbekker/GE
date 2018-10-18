/*--------------------------------------------------------------------------*/
/*							LookupTable.cpp 								*/
/*                            												*/
/*	Purpose	: Lookup table to color map range.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.9 "Lookup Table".                         */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "LookupTable.h"

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CLookupTable::CLookupTable() : vtkLookupTable()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CLookupTable::~CLookupTable()
{
}

/*--------------------------------------------------------------------------*/
/* SetNumberOfColors                                                        */
/*--------------------------------------------------------------------------*/
void CLookupTable::SetNumberOfColors(int iNumberOfColors)
{
	m_cColorTable->SetNumberOfColors(iNumberOfColors);
	vtkLookupTable::SetNumberOfColors(iNumberOfColors);
}

/*--------------------------------------------------------------------------*/
/* SetColorTable                                                            */
/*--------------------------------------------------------------------------*/
void CLookupTable::SetColorTable(CColorTable* pcColorTable)
{
	m_cColorTable = pcColorTable;
	for (int i = 0; i < m_cColorTable->GetNumberOfColors(); i++)
	{
		float red	= GetRValue(m_cColorTable->GetColorRow(i)->GetColor())/255.0;
		float green	= GetGValue(m_cColorTable->GetColorRow(i)->GetColor())/255.0;
		float blue	= GetBValue(m_cColorTable->GetColorRow(i)->GetColor())/255.0;
		SetTableValue(i, red, green, blue, 1);
	}
}

/*--------------------------------------------------------------------------*/
/* MapValue                                                                 */
/*--------------------------------------------------------------------------*/
unsigned char* CLookupTable::MapValue(float v)
{
	int index = 0;
	for (int i = 0; i < m_cColorTable->GetNumberOfColors(); i++)
		if (v >= m_cColorTable->GetColorRow(i)->GetMinimum() && v < m_cColorTable->GetColorRow(i)->GetMaximum())
			index = i;
	if (v < m_cColorTable->GetMinimumScalarValue())
		index = 0;
	if (v >= m_cColorTable->GetMaximumScalarValue())
		index = m_cColorTable->GetNumberOfColors() - 1;
	return Table->GetPointer(index * 4);
}

/*--------------------------------------------------------------------------*/
/* SetTableRange                                                    		*/
/*--------------------------------------------------------------------------*/
void CLookupTable::SetTableRange(float min, float max)
{
	TableRange[0] = min;
	TableRange[1] = max;
}

/*--------------------------------------------------------------------------*/
/* GetTableIndex                                                            */
/*--------------------------------------------------------------------------*/
int CLookupTable::GetTableIndex(float fValue)
{
	int index = 0;
	for (int i = 0; i < m_cColorTable->GetNumberOfColors(); i++)
		if (fValue >= m_cColorTable->GetColorRow(i)->GetMinimum() && fValue < m_cColorTable->GetColorRow(i)->GetMaximum())
			index = i;
	if (fValue < m_cColorTable->GetMinimumScalarValue())
		index = 0;
	if (fValue >= m_cColorTable->GetMaximumScalarValue())
		index = m_cColorTable->GetNumberOfColors() - 1;
	return index;
}