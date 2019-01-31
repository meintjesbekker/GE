/*--------------------------------------------------------------------------*/
/*								ReadFile.cpp 								*/
/*                            												*/
/*	Purpose	: Read PMWIN files.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "ReadFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CReadFile::CReadFile()
{
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CReadFile::~CReadFile()
{
}

/*--------------------------------------------------------------------------*/
/* ReadTimeIndependentData                                                  */
/*--------------------------------------------------------------------------*/
void CReadFile::ReadTimeIndependentData(CString sFolderAndFileName, float* pfArray, int iNumberOfRows, int iNumberOfColumns, int iLayer)
{
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, sFolderAndFileName, "rb");
	CString str;
	if (err)
	{
		str.Format("Can not open the time independent data file.\nFile: %s.", sFolderAndFileName.GetString());
		AfxMessageBox(str);		
	}
	else
	{
		if (pFile != NULL) 
		{
			// skip the stress period and position header = 4000 bytes
			// number of bytes for each iLayer = NI*NJ*4
			fseek(pFile, 4000 + ((iLayer - 1)*iNumberOfRows*iNumberOfColumns * 4), SEEK_SET);
			fread(pfArray, 4, iNumberOfRows*iNumberOfColumns, pFile);
			fclose(pFile);
		}
	}
}

/*--------------------------------------------------------------------------*/
/* ReadTimeDependentData                                                    */
/*--------------------------------------------------------------------------*/
void CReadFile::ReadTimeDependentData(CString sFolderAndFileName, int iStressPeriod, float* pfArray, int iNumberOfRows, int iNumberOfColumns, int iNumberOfLayers, int iLayer)
{
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, sFolderAndFileName, "rb");
	CString str;
	if (err)
	{
		str.Format("Can not open the time independent data file.\nFile: %s.", sFolderAndFileName.GetString());
		AfxMessageBox(str);
	}
	
	if (pFile)
	{
		short int* ipStressPeriod = new short int[1000];
		short int* ipPositionHeader = new short int[1000];
		fread(ipStressPeriod, 2, 1000, pFile);
		fread(ipPositionHeader, 2, 1000, pFile);

		// stress period is the index into the ipStressPeriod pfArray and iStressPeriod
		// is the actual stress period used
		int iStressPeriodUsed = ipStressPeriod[iStressPeriod - 1];
		int iPosition = 0;
		for (int i = 0; i < 1000; i++)
			if (ipPositionHeader[i] == iStressPeriodUsed)
				iPosition = i;
		fseek(pFile, 4000 + (iPosition * iNumberOfLayers + (iLayer - 1)) * iNumberOfRows * iNumberOfColumns * 4, SEEK_SET);
		fread(pfArray, 4, iNumberOfRows * iNumberOfColumns, pFile);
		if (pFile != NULL)
			fclose(pFile);
	}
}

/*--------------------------------------------------------------------------*/
/* FileExists                                                               */
/*--------------------------------------------------------------------------*/
BOOL CReadFile::FileExists(CString sFolderAndFileName)
{
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, sFolderAndFileName, "r");
	if (err)
		return FALSE;
	else
	{
		if (pFile != NULL)
			fclose(pFile);
		return TRUE;
	}
}