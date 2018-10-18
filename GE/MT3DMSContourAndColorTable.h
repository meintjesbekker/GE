/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorTable.h              			*/
/*                            												*/
/*	Purpose	: Table contains concentration and color for each interval.		*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLORTABLE_H__B0FC3EA2_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLORTABLE_H__B0FC3EA2_0AB7_11D4_B1DC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <Afxtempl.h>
#include "MT3DMSContourAndColorRow.h"
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorTable
{
// public operations
public:
	CMT3DMSContourAndColorTable();
	virtual ~CMT3DMSContourAndColorTable();
	COLORREF GetColor(int iIndex) const {return m_pcMT3DMSContourAndColorRowArray[iIndex]->GetColor();};
	float GetValue(int iIndex) const {return m_pcMT3DMSContourAndColorRowArray[iIndex]->GetValue();};
	int	GetSize() const {return m_pcMT3DMSContourAndColorRowArray.GetSize();};
	int AddMT3DMSContourAndColorRowToArray(CMT3DMSContourAndColorRow* pcMT3DMSContourAndColorRow);
	void RemoveMT3DMSContourAndColorFromArray(int iIndex);
	float GetInterval() const {return m_fInterval;};
	void SetInterval(float fInterval) {m_fInterval = fInterval;};
	float GetMinimumScalarValue() const {return m_fMinimumScalarValue;};
	void SetMinimumScalarValue(float fMinimumScalarValue) {m_fMinimumScalarValue = fMinimumScalarValue;};
	float GetMaximumScalarValue() const {return m_fMaximumScalarValue;};
	void SetMaximumScalarValue(float fMaximumScalarValue) {m_fMaximumScalarValue = fMaximumScalarValue;};
	int GetNumberOfValuesAndColors() const {return m_pcMT3DMSContourAndColorRowArray.GetSize();};
	COLORREF GetMinimumScalarColor() const {return m_cMinimumScalarColor;};
	void SetMinimumScalarColor(COLORREF cMinimumScalarColor) {m_cMinimumScalarColor = cMinimumScalarColor;};
	COLORREF GetMaximumScalarColor() const {return m_cMaximumScalarColor;};
	void SetMaximumScalarColor(COLORREF cMaximumScalarColor) {m_cMaximumScalarColor = cMaximumScalarColor;};
	CMT3DMSContourAndColorRow* GetContourAndColorRow(int iIndex) const {return m_pcMT3DMSContourAndColorRowArray[iIndex];};
	void CreateValueAndColorRows();

// private operations
private:
	void SetContourAndColorRow(int iIndex, CMT3DMSContourAndColorRow* pcMT3DMSContourAndColorRow) {m_pcMT3DMSContourAndColorRowArray[iIndex] = pcMT3DMSContourAndColorRow;};

// private attributes
private:
	float m_fInterval;
	int m_iNumberOfValuesAndColors;
	float m_fMinimumScalarValue;
	float m_fMaximumScalarValue;
	COLORREF m_cMinimumScalarColor;
	COLORREF m_cMaximumScalarColor;
	CArray<CMT3DMSContourAndColorRow*, CMT3DMSContourAndColorRow*> m_pcMT3DMSContourAndColorRowArray;
};

#endif // !defined(AFX_MT3DMSCONTOURANDCOLORTABLE_H__B0FC3EA2_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
