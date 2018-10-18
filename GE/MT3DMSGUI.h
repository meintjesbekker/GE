/*--------------------------------------------------------------------------*/
/*								MT3DMSGUI.h									*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for GUI pages of the	*/
/*   		  Isosurface visualization objects.								*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                                   			*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6 "Isosurface".						*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSGUI_H__6651FFE2_7E3C_11D4_B2FB_0060084B410C__INCLUDED_)
#define AFX_MT3DMSGUI_H__6651FFE2_7E3C_11D4_B2FB_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ClipPolyData.h"
#include "Model.h"
#include "MT3DMSContourAndColorTable.h"
#endif // _MSC_VER > 1000

class CMT3DMSGUI : public CClipPolyData
{
// public operations
public:
	CMT3DMSGUI(CModel* pcModel = NULL);
	virtual ~CMT3DMSGUI();

	// operations for attributes used on general page
	int GetSpecy(int iIndex) const {return m_piSpecies[iIndex];};
	void SetSpecy(int iIndex) {m_iSpecy = m_piSpecies[iIndex];};
	int GetSpecyIndex() const {return m_iSpecyIndex;};
	void SetSpecyIndex(int iIndex) {m_iSpecyIndex = iIndex;};
	int GetNumberOfSpecies() const {return m_iNumberOfSpecies;};
	double GetTotalElapsedTime(int iIndex) const {return m_pdTotalElapsedTimes[iIndex];};
	void SetTotalElapsedTime(int iIndex) {m_dTotalElapsedTime = m_pdTotalElapsedTimes[iIndex];};
	int GetTotalElapsedTimeIndex() const {return m_iTotalElapsedTimeIndex;};
	void SetTotalElapsedTimeIndex(int iIndex) {m_iTotalElapsedTimeIndex = iIndex;};
	int	GetNumberOfTimeIntervals() const {return m_lNumberOfTimeIntervals;};
	
	//  operations for attributes used on contour and color page
	float GetOpacity() const {return m_fOpacity;};
	void SetOpacity(float fOpacity) {m_fOpacity = fOpacity;};
	CMT3DMSContourAndColorTable* GetMT3DMSContourAndColorTablePointer() const {return m_pMT3DMSContourAndColorTable;};

// private attributes
public:
	// general page
	int	m_iSpecy;
	int* m_piSpecies;
	int	m_iNumberOfSpecies;
	int	m_iSpecyIndex;
	double m_dTotalElapsedTime;
	double* m_pdTotalElapsedTimes;
	long int m_lNumberOfTimeIntervals;
	int m_iTotalElapsedTimeIndex;

	// color and contour page
	float m_fOpacity;
	CMT3DMSContourAndColorTable* m_pMT3DMSContourAndColorTable;
};

#endif // !defined(AFX_MT3DMSGUI_H__6651FFE2_7E3C_11D4_B2FB_0060084B410C__INCLUDED_)
