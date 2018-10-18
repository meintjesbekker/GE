/*--------------------------------------------------------------------------*/
/*								ColorRow.h                					*/
/*                            												*/
/*	Purpose	: Color row in color table.                                  	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORROW_H__CFD991C1_E437_11D3_B199_0060084B410C__INCLUDED_)
#define AFX_COLORROW_H__CFD991C1_E437_11D3_B199_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorRow  
{
// public operations
public:
	CColorRow();
	virtual ~CColorRow();
	float GetMinimum() const {return m_fMinimum;};
	void SetMinimum(float fMinimum) {m_fMinimum = fMinimum;};
	float GetMaximum() const {return m_fMaximum;};
	void SetMaximum(float fMaximum){m_fMaximum = fMaximum;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor){m_cColor = cColor;};

// private attributes
private:
	float m_fMinimum;
	float m_fMaximum;
	COLORREF m_cColor;
};

#endif // !defined(AFX_COLORROW_H__CFD991C1_E437_11D3_B199_0060084B410C__INCLUDED_)
