/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorRow.h                			*/
/*                            												*/
/*	Purpose	: Contour and color row in MT3DMS color table.               	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLORROW_H__B0FC3EA1_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLORROW_H__B0FC3EA1_0AB7_11D4_B1DC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorRow  
{
// public operations
public:
	CMT3DMSContourAndColorRow();
	virtual ~CMT3DMSContourAndColorRow();
	float GetValue() const {return m_fValue;};
	void SetValue(float fValue) {m_fValue = fValue;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor) {m_cColor = cColor;};

// private attributes
private:
	float m_fValue;
	COLORREF m_cColor;
};

#endif // !defined(AFX_MT3DMSCONTOURANDCOLORROW_H__B0FC3EA1_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
