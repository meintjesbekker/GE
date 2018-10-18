/*--------------------------------------------------------------------------*/
/*							ColorSpectrum.h                					*/
/*                            												*/
/*	Purpose	: Get the index color betweeen the maximum and minimum color. 	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORSPECTRUM_H__6CCCDEB1_D3BA_11D3_B173_0060084B410C__INCLUDED_)
#define AFX_COLORSPECTRUM_H__6CCCDEB1_D3BA_11D3_B173_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorSpectrum  
{
// public operations
public:
	CColorSpectrum(COLORREF cMinimumColor, COLORREF cMaximumColor);
	virtual ~CColorSpectrum();
	COLORREF GetSpectrumColor(int iNumberOfColorLevels, int iLevel);

// private attributes
private:
	COLORREF m_cMinimumColor;
	COLORREF m_cMaximumColor;
};

#endif // !defined(AFX_COLORSPECTRUM_H__6CCCDEB1_D3BA_11D3_B173_0060084B410C__INCLUDED_)