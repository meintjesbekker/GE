/*--------------------------------------------------------------------------*/
/*							XYZCoordinate.h									*/
/*                            												*/
/*	Purpose	: 3D coordinate.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_XYZCOORDINATE_H__8ED4BCE3_313D_11D4_B231_0060084B410C__INCLUDED_)
#define AFX_XYZCOORDINATE_H__8ED4BCE3_313D_11D4_B231_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXYZCoordinate : public CObject
{
	DECLARE_SERIAL(CXYZCoordinate)

// public operations
public:
	CXYZCoordinate();
	virtual ~CXYZCoordinate();
	float GetX() const {return m_fX;};
	void SetX(float fX) {m_fX = fX;};
	float GetY() const {return m_fY;};
	void SetY(float fY) {m_fY = fY;};
	float GetZ() const {return m_fZ;};
	void SetZ(float fZ) {m_fZ = fZ;};
	void SetXYZ(float fX, float fY, float fZ);
	virtual void Serialize(CArchive& ar);

// public attributes	
public:
	float m_fX;
	float m_fY;
	float m_fZ;
};

#endif // !defined(AFX_XYZCOORDINATE_H__8ED4BCE3_313D_11D4_B231_0060084B410C__INCLUDED_)
