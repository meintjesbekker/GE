/*--------------------------------------------------------------------------*/
/*								FilesExist.cpp 								*/
/*                            												*/
/*	Purpose	: Tests to see if files exist.                               	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
//#include "GE.h"
#include "FilesExist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CFilesExist::CFilesExist()
{
	m_bHeadsFileExists = FALSE;
	m_bIBDFileExists = FALSE;
	m_bTICFileExists = FALSE;
	m_bGHBFileExists = FALSE;
	m_bWELFileExists = FALSE;
	m_bDRCFileExists = FALSE;
	m_bRICFileExists = FALSE;
	m_bWACFileExists = FALSE;
	m_bC85FileExists = FALSE;
	m_bCH1FileExists = FALSE;
	m_bC55FileExists = FALSE;
	m_bCONFileExists = FALSE;
	m_bLEAFileExists = FALSE;
	m_bSTOFileExists = FALSE;
	m_bHTCFileExists = FALSE;
	m_bLKNFileExists = FALSE;
	m_bSCCFileExists = FALSE;
	m_bPORFileExists = FALSE;
	m_bYLDFileExists = FALSE;
	m_bMT3DMSFileExists = FALSE;
	m_bPHT3DFileExists = FALSE;
	m_bRT3DFileExists = FALSE;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CFilesExist::~CFilesExist()
{
}

/*--------------------------------------------------------------------------*/
/* SearchForFiles                                                           */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForFiles(CString sFolderPath, CString sPathName)
{
	// potentiometric surface
	// heads.dat
	if (FileExists(sFolderPath + "heads.dat"))
		m_bHeadsFileExists = TRUE;

	// search for hydraulic components
	SearchForHydraulicComponentsFiles(sPathName);
	
	// MT3DMS files
	SearchForMT3DMSFiles(sFolderPath, sPathName);

	// PHT3D files
	SearchForPHT3DFiles(sFolderPath, sPathName);

	// RT3D files
	SearchForRT3DFiles(sFolderPath, sPathName);

	// parameter files
	SearchForParameterFiles(sPathName);
}

/*--------------------------------------------------------------------------*/
/* FilesExist                                                               */
/*--------------------------------------------------------------------------*/
BOOL CFilesExist::FileExists(CString sPathAndFileName)
{
	FILE* pFile;
	errno_t err= fopen_s(&pFile, sPathAndFileName, "r");
	if (err)
		return FALSE;
	else
	{
		if (pFile != NULL)
			fclose(pFile);
		return TRUE;
	}
}

/*--------------------------------------------------------------------------*/
/* SearchForHydraulicComponentsFiles			                            */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForHydraulicComponentsFiles(CString sPathName)
{
	// hydraulic components
	// *.ibd
	if (FileExists(sPathName.SpanExcluding(".") + ".ibd"))
		m_bIBDFileExists = TRUE;
	
	// *.tic
	if (FileExists(sPathName.SpanExcluding(".") + ".tic"))
		m_bTICFileExists = TRUE;
	
	// *.ghb
	if (FileExists(sPathName.SpanExcluding(".") + ".ghb"))
		m_bGHBFileExists = TRUE;
	
	// *.wel
	if (FileExists(sPathName.SpanExcluding(".") + ".wel"))
		m_bWELFileExists = TRUE;
	
	// *.drc
	if (FileExists(sPathName.SpanExcluding(".") + ".drc"))
		m_bDRCFileExists = TRUE;
	
	// *.ric
	if (FileExists(sPathName.SpanExcluding(".") + ".ric"))
		m_bRICFileExists = TRUE;
	
	// *.wac
	if (FileExists(sPathName.SpanExcluding(".") + ".wac"))
		m_bWACFileExists = TRUE;
	
	// *.c85 
	if (FileExists(sPathName.SpanExcluding(".") + ".c85"))
		m_bC85FileExists = TRUE;
	
	// *.ch1
	if (FileExists(sPathName.SpanExcluding(".") + ".ch1"))
		m_bCH1FileExists = TRUE;
	
	// *.c55
	if (FileExists(sPathName.SpanExcluding(".") + ".c55"))
		m_bC55FileExists = TRUE;
}

/*--------------------------------------------------------------------------*/
/* SearchForMT3DMSFiles                                                     */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForMT3DMSFiles(CString sFolderPath, CString sPathName)
{
	// MT3DMS
	m_bMT3DMSFileExists = FALSE;
	m_bMT3DMSSpecyExistsArray.SetSize(999);
	for (int i = 1; i <= 999; i++)
	{
		// test if file exists
		if (FileExists(GetFolderAndFileName(sFolderPath, sPathName, i, "mt3d")))
		{
			m_bMT3DMSSpecyExistsArray[i - 1] = TRUE;
			m_bMT3DMSFileExists = TRUE;
		}
		else
			m_bMT3DMSSpecyExistsArray[i - 1] = FALSE;
	}
}

/*--------------------------------------------------------------------------*/
/* SearchForPHT3DFiles                                                      */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForPHT3DFiles(CString sFolderPath, CString sPathName)
{
	// PHT3D
	m_bPHT3DFileExists = FALSE;
	m_bPHT3DSpecyExistsArray.SetSize(999);
	for (int i = 1; i <= 999; i++)
	{
		// test if file exists
		if (FileExists(GetFolderAndFileName(sFolderPath, sPathName, i, "pht3d")))
		{
			m_bPHT3DSpecyExistsArray[i - 1] = TRUE;
			m_bPHT3DFileExists = TRUE;
		}
		else
			m_bPHT3DSpecyExistsArray[i - 1] = FALSE;
	}
}

/*--------------------------------------------------------------------------*/
/* SearchForRT3DFiles                                                       */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForRT3DFiles(CString sFolderPath, CString sPathName)
{
	// RT3D
	m_bRT3DFileExists = FALSE;
	m_bRT3DSpecyExistsArray.SetSize(999);
	for (int i = 1; i <= 999; i++)
	{
		// test if file exists
		if (FileExists(GetFolderAndFileName(sFolderPath, sPathName, i, "rt3d")))
		{
			m_bRT3DSpecyExistsArray[i - 1] = TRUE;
			m_bRT3DFileExists = TRUE;
		}
		else
			m_bRT3DSpecyExistsArray[i - 1] = FALSE;
	}
}


/*--------------------------------------------------------------------------*/
/* SearchForRT3DFiles                                                       */
/*--------------------------------------------------------------------------*/
void CFilesExist::SearchForParameterFiles(CString sPathName)
{
	// parameters
	// *.con
	if (FileExists(sPathName.SpanExcluding(".") + ".con"))
		m_bCONFileExists = TRUE;
	
	// *.lea
	if (FileExists(sPathName.SpanExcluding(".") + ".lea"))
		m_bLEAFileExists = TRUE;
	
	// *.sto
	if (FileExists(sPathName.SpanExcluding(".") + ".sto"))
		m_bSTOFileExists = TRUE;
	
	// *.htc	
	if (FileExists(sPathName.SpanExcluding(".") + ".htc"))
		m_bHTCFileExists = TRUE;
	
	// *.lkn	
	if (FileExists(sPathName.SpanExcluding(".") + ".lkn"))
		m_bLKNFileExists = TRUE;
	
	// *.scc
	if (FileExists(sPathName.SpanExcluding(".") + ".scc"))
		m_bSCCFileExists = TRUE;
	
	// *.por
	if (FileExists(sPathName.SpanExcluding(".") + ".por"))
		m_bPORFileExists = TRUE;

	// *.yld
	if (FileExists(sPathName.SpanExcluding(".") + ".yld"))
		m_bYLDFileExists = TRUE;
}

/*--------------------------------------------------------------------------*/
/* SearchForRT3DFiles                                                       */
/*--------------------------------------------------------------------------*/
CString CFilesExist::GetFolderAndFileName(CString sFolderPath, CString sPathName, int iSpecyNumber, CString sFilePrefix)
{
		CString cSpecyStr;
		cSpecyStr.Format("%i", iSpecyNumber);
		cSpecyStr = "00" + cSpecyStr;
		cSpecyStr = cSpecyStr.Right(3);
		CString cTempStr;
		cTempStr = sFolderPath + sFilePrefix + cSpecyStr + ".ucn";
		return cTempStr;
}