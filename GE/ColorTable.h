/*--------------------------------------------------------------------------*/
/*							ColorTable.h                					*/
/*                            												*/
/*	Purpose	: Table contains range and color for each interval.				*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_COLORTABLE_H__27A2EF11_E36D_11D3_B197_0060084B410C__INCLUDED_)
#define AFX_COLORTABLE_H__27A2EF11_E36D_11D3_B197_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxtempl.h>
#include "ColorRow.h"
#endif // _MSC_VER > 1000

class CColorTable  
{
// public operations
public:
	CColorTable();
	virtual ~CColorTable();
	float GetInterval() const {return m_fInterval;};
	void SetInterval(float fInterval) {m_fInterval = fInterval;};
	int GetNumberOfColors() const {return m_iNumberOfColors;};
	void SetNumberOfColors(int iNumberOfColors) {m_iNumberOfColors = iNumberOfColors;};
	float GetMinimumScalarValue() const {return m_fMinimumScalarValue;};
	void SetMinimumScalarValue(float fMinimumScalarValue) {m_fMinimumScalarValue = fMinimumScalarValue;};
	float GetMaximumScalarValue() const {return m_fMaximumScalarValue;};
	void SetMaximumScalarValue(float fMaximumScalarValue) {m_fMaximumScalarValue = fMaximumScalarValue;};
	COLORREF GetMinimumScalarColor() const {return m_cMinimumScalarColor;};
	void SetMinimumScalarColor(COLORREF cColor) {m_cMinimumScalarColor = cColor;};
	COLORREF GetMaximumScalarColor() const {return m_cMaximumScalarColor;};
	void SetMaximumScalarColor(COLORREF cColor) {m_cMaximumScalarColor = cColor;};
	CColorRow* GetColorRow(int iIndex) const {return m_pColorRowArray[iIndex];};
	void SetColorRow(int iIndex, CColorRow* cColorRow) {m_pColorRowArray[iIndex] = cColorRow;};
	void CreateColorRows();
	void ChangeMinimumColorLevel(int iIndex, float fMinimumColorLevel);
	void ChangeMaximumColorLevel(int iIndex, float fMaximumColorLevel);

// private attributes
private:
	float m_fInterval;
	int	m_iNumberOfColors;	
	float m_fMinimumScalarValue;
	float m_fMaximumScalarValue;
	COLORREF m_cMinimumScalarColor;
	COLORREF m_cMaximumScalarColor;
	CArray<CColorRow*, CColorRow*> m_pColorRowArray;
};

#endif // !defined(AFX_COLORTABLE_H__27A2EF11_E36D_11D3_B197_0060084B410C__INCLUDED_)
