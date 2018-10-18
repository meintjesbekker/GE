/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorTable.cpp            			*/
/*                            												*/
/*	Purpose	: Table contains concentration and color for each interval.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorSpectrum.h"
#include "MT3DMSContourAndColorTable.h"
#include "MT3DMSContourAndColorRow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorTable::CMT3DMSContourAndColorTable()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CMT3DMSContourAndColorTable::~CMT3DMSContourAndColorTable()
{
}

/*--------------------------------------------------------------------------*/
/* AddMT3DMSContourAndColorRowToArray                                       */
/*--------------------------------------------------------------------------*/
int CMT3DMSContourAndColorTable::AddMT3DMSContourAndColorRowToArray(CMT3DMSContourAndColorRow* pcMT3DMSContourAndColorRow)
{
	return m_pcMT3DMSContourAndColorRowArray.Add(pcMT3DMSContourAndColorRow);
}

/*--------------------------------------------------------------------------*/
/* RemoveMT3DMSContourAndColorRowFromArray                                  */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorTable::RemoveMT3DMSContourAndColorFromArray(int iIndex)
{
	delete m_pcMT3DMSContourAndColorRowArray[iIndex];
	m_pcMT3DMSContourAndColorRowArray.RemoveAt(iIndex);
}

/*--------------------------------------------------------------------------*/
/* CreateValueAndColorRows                                                  */
/*--------------------------------------------------------------------------*/
void CMT3DMSContourAndColorTable::CreateValueAndColorRows()
{
	if (m_pcMT3DMSContourAndColorRowArray.GetSize() > 0)
	{
		for (int i = 0; i < m_pcMT3DMSContourAndColorRowArray.GetSize(); i++)
			delete m_pcMT3DMSContourAndColorRowArray[i];
		m_pcMT3DMSContourAndColorRowArray.RemoveAll();	
	}

	if ((m_fMaximumScalarValue == m_fMinimumScalarValue) || (m_fInterval == 0))
		m_iNumberOfValuesAndColors = 1;
	else
		// rounds
		m_iNumberOfValuesAndColors = floor((m_fMaximumScalarValue - m_fMinimumScalarValue) / float(m_fInterval) + 0.5) + 1;
	m_pcMT3DMSContourAndColorRowArray.SetSize(m_iNumberOfValuesAndColors, 1);
	CColorSpectrum colorSpectrum(	m_cMinimumScalarColor,
									m_cMaximumScalarColor);
	for (int i = 0; i < m_iNumberOfValuesAndColors; i++)
	{
		CMT3DMSContourAndColorRow* colorRow = new CMT3DMSContourAndColorRow();
		colorRow->SetValue(m_fMinimumScalarValue + m_fInterval * i);
		colorRow->SetColor(colorSpectrum.GetSpectrumColor(m_iNumberOfValuesAndColors, i + 1));
		SetContourAndColorRow(i, colorRow);
	}	
	GetContourAndColorRow(m_iNumberOfValuesAndColors - 1)->SetValue(m_fMaximumScalarValue);
}