/*--------------------------------------------------------------------------*/
/*							ColorTable.cpp              					*/
/*                            												*/
/*	Purpose	: Table contains range and color for each interval.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorTable.h"
#include "ColorSpectrum.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorTable::CColorTable()
{
	m_fInterval = 0.0;
	m_iNumberOfColors = 0;	
	m_fMinimumScalarValue = 0;
	m_fMaximumScalarValue = 0;
	m_cMinimumScalarColor = COLORREF();
	m_cMaximumScalarColor = COLORREF();
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CColorTable::~CColorTable()
{
	for (int i = 0; i < m_pColorRowArray.GetSize(); i++)
		delete m_pColorRowArray[i];
	m_pColorRowArray.RemoveAll();
}

/*--------------------------------------------------------------------------*/
/* CreateColorRows                                                          */
/*--------------------------------------------------------------------------*/
void CColorTable::CreateColorRows()
{
	// clean
	if (m_pColorRowArray.GetSize() > 0)
	{
		for (int i = 0; i < m_pColorRowArray.GetSize(); i++)
			delete m_pColorRowArray[i];
		m_pColorRowArray.RemoveAll();	
	}

	// calculate number of colors
	if ((m_fMaximumScalarValue == m_fMinimumScalarValue) || (m_fInterval == 0))
		m_iNumberOfColors = 1;
	else
	{
		CString cStr;
		cStr.Format("%1.5G", ((m_fMaximumScalarValue - m_fMinimumScalarValue) / m_fInterval));
		m_iNumberOfColors = atoi(cStr);
	}
	
	// create the array
	m_pColorRowArray.SetSize(m_iNumberOfColors, 1);
	CColorSpectrum cColorSpectrum(	m_cMinimumScalarColor,
									m_cMaximumScalarColor);
	for (int i = 0; i < m_iNumberOfColors; i++)
	{
		CColorRow* cColorRow = new CColorRow();
		cColorRow->SetMinimum(m_fMinimumScalarValue + m_fInterval * i);
		cColorRow->SetMaximum(m_fMinimumScalarValue + m_fInterval * (i + 1));
		cColorRow->SetColor(cColorSpectrum.GetSpectrumColor(m_iNumberOfColors, i + 1));
		SetColorRow(i, cColorRow);
	}	
	GetColorRow(m_iNumberOfColors - 1)->SetMaximum(m_fMaximumScalarValue);
}

/*--------------------------------------------------------------------------*/
/* ChangeMinimumColorLevel                                                  */
/*--------------------------------------------------------------------------*/
void CColorTable::ChangeMinimumColorLevel(int iIndex, float fMinimumColorLevel)
{
	GetColorRow(iIndex)->SetMinimum(fMinimumColorLevel);
}

/*--------------------------------------------------------------------------*/
/* ChangeMaximumColorLevel                                                  */
/*--------------------------------------------------------------------------*/
void CColorTable::ChangeMaximumColorLevel(int iIndex, float fMaximumColorLevel)
{
	GetColorRow(iIndex)->SetMaximum(fMaximumColorLevel);
}