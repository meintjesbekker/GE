/*--------------------------------------------------------------------------*/
/*								AverageGUI.h                				*/
/*                            												*/
/*	Purpose	: Contains member variables and functions for Average page of	*/
/*	          GUI, used by Geospatial Model, Potentiometric Surface,  		*/
/*	          XYZ Surface and Hydraulic Components visualization objects.   */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide sections 3.3.3, 3.4.2, 3.7.2 "Average",			*/
/*			  3.5.2 "Decimate and Smooth". 									*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_AVERAGEGUI_H__DEE28041_78BD_11D4_B2EC_0060084B410C__INCLUDED_)
#define AFX_AVERAGEGUI_H__DEE28041_78BD_11D4_B2EC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAverageGUI
{
// public operations
public:
	CAverageGUI();
	virtual ~CAverageGUI();

	// average page
	BOOL GetAverage() const {return m_bAverage;};
	void SetAverage(BOOL bAverage) {m_bAverage = bAverage;};

// protected attributes
protected:
	BOOL m_bAverage;
};

#endif // !defined(AFX_AVERAGEGUI_H__DEE28041_78BD_11D4_B2EC_0060084B410C__INCLUDED_)