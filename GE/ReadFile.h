/*--------------------------------------------------------------------------*/
/*								ReadFile.h   								*/
/*                            												*/
/*	Purpose	: Read PMWIN files.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_READFILE_H__B3ADC812_FA35_11D2_B7D6_0060084B410C__INCLUDED_)
#define AFX_READFILE_H__B3ADC812_FA35_11D2_B7D6_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReadFile  
{
// public operations
public:
	CReadFile();
	virtual ~CReadFile();
	void ReadTimeIndependentData(	CString sFolderAndFileName, 
									float* pfArray, 
									int iNumberOfRows, 
									int iNumberOfColumns, 
									int iLayer);
	void ReadTimeDependentData(	CString sFolderAndFileName, 
								int iStressPeriod, 
								float* pfArray, 
								int iNumberOfRows, 
								int iNumberOfColumns, 
								int iNumberOfLayers, 
								int iLayer);
	static BOOL FileExists(CString sFolderAndFileName);
};

#endif // !defined(AFX_READFILE_H__B3ADC812_FA35_11D2_B7D6_0060084B410C__INCLUDED_)
