/*--------------------------------------------------------------------------*/
/*							ColorSpectrum.cpp              					*/
/*                            												*/
/*	Purpose	: Get the index color betweeen the maximum and minimum color. 	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ColorSpectrum.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CColorSpectrum::CColorSpectrum(COLORREF cMinimumColor, COLORREF cMaximumColor)
{
	m_cMinimumColor = cMinimumColor;
	m_cMaximumColor = cMaximumColor;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CColorSpectrum::~CColorSpectrum()
{
}

/*--------------------------------------------------------------------------*/
/* GetSpectrumColor                                                         */
/*--------------------------------------------------------------------------*/
COLORREF CColorSpectrum::GetSpectrumColor(int iNumberOfColorLevels, int iLevel)
{
	COLORREF cColor(NULL);

	if (iLevel == 1)
		cColor = m_cMinimumColor;
	else 
		if (iLevel == iNumberOfColorLevels)
			cColor = m_cMaximumColor;

	// if more than 2 colors
	if (iNumberOfColorLevels > 2)
	{
		float deltaRed = (GetRValue(m_cMaximumColor) - GetRValue(m_cMinimumColor)) / (iNumberOfColorLevels - 1);
		float deltaGreen = (GetGValue(m_cMaximumColor) - GetGValue(m_cMinimumColor)) / (iNumberOfColorLevels - 1);
		float deltaBlue = (GetBValue(m_cMaximumColor) - GetBValue(m_cMinimumColor)) / (iNumberOfColorLevels - 1);
		cColor = RGB(	GetRValue(m_cMinimumColor) + (iLevel - 1) * deltaRed,
						GetGValue(m_cMinimumColor) + (iLevel - 1) * deltaGreen,
						GetBValue(m_cMinimumColor) + (iLevel - 1) * deltaBlue);
	}
	
	return cColor;
}