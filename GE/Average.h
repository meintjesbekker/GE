/*--------------------------------------------------------------------------*/
/*								Average.h      								*/
/*                            												*/
/*	Purpose	: Used to calculate average of number of values added.        	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.3 "Geospatial Model". Figure 5.8.          	*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_AVERAGE_H__71197A61_6035_11D3_B82C_0060084B410C__INCLUDED_)
#define AFX_AVERAGE_H__71197A61_6035_11D3_B82C_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAverage  
{
// public operations
public:
	CAverage();
	virtual ~CAverage();
	void AddToSum(float value);
	float GetAverage();

// private attributes
private:
	float m_Summation; // sum of all values
	int m_NumberOfValues; // number of values added to get sum
};

#endif // !defined(AFX_AVERAGE_H__71197A61_6035_11D3_B82C_0060084B410C__INCLUDED_)
