/*--------------------------------------------------------------------------*/
/*								FilesExist.h   								*/
/*                            												*/
/*	Purpose	: Tests to see if files exist.                               	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_FILESEXIST_H__5E6EE0F1_2D6C_11D4_B21E_0060084B410C__INCLUDED_)
#define AFX_FILESEXIST_H__5E6EE0F1_2D6C_11D4_B21E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#endif // _MSC_VER > 1000

class CFilesExist  
{
// public operations
public:
	CFilesExist();
	virtual ~CFilesExist();
	void SearchForFiles(CString sFolderPath, CString sPathName);
	BOOL FileExists(CString sPathAndFileName);
	BOOL GetHeadsFileExists() const {return m_bHeadsFileExists;};
	BOOL GetIBDFileExists() const {return m_bIBDFileExists;};
	BOOL GetTICFileExists() const {return m_bTICFileExists;};
	BOOL GetGHBFileExists() const {return m_bGHBFileExists;};
	BOOL GetWELFileExists() const {return m_bWELFileExists;};
	BOOL GetDRCFileExists() const {return m_bDRCFileExists;};
	BOOL GetRICFileExists() const {return m_bRICFileExists;};
	BOOL GetWACFileExists() const {return m_bWACFileExists;};
	BOOL GetC85FileExists() const {return m_bC85FileExists;};
	BOOL GetCH1FileExists() const {return m_bCH1FileExists;};
	BOOL GetC55FileExists() const {return m_bC55FileExists;};
	BOOL GetMT3DMSSpecyFileExists(int iIndex) const {return m_bMT3DMSSpecyExistsArray[iIndex];};
	BOOL GetPHT3DSpecyFileExists(int iIndex) const {return m_bPHT3DSpecyExistsArray[iIndex];};
	BOOL GetRT3DSpecyFileExists(int iIndex) const {return m_bRT3DSpecyExistsArray[iIndex];};
	BOOL GetCONFileExists() const {return m_bCONFileExists;};
	BOOL GetLEAFileExists() const {return m_bLEAFileExists;};
	BOOL GetSTOFileExists() const {return m_bSTOFileExists;};
	BOOL GetHTCFileExists() const {return m_bHTCFileExists;};
	BOOL GetLKNFileExists() const {return m_bLKNFileExists;};
	BOOL GetSCCFileExists() const {return m_bSCCFileExists;};
	BOOL GetPORFileExists() const {return m_bPORFileExists;};
	BOOL GetYLDFileExists() const {return m_bYLDFileExists;};
	BOOL GetMT3DMSFileExists() const {return m_bMT3DMSFileExists;};
	BOOL GetPHT3DFileExists() const {return m_bPHT3DFileExists;};
	BOOL GetRT3DFileExists() const {return m_bRT3DFileExists;};

// private operations 
private:
	void SearchForHydraulicComponentsFiles(CString sPathName);
	void SearchForMT3DMSFiles(CString sFolderPath, CString sPathName);
	void SearchForPHT3DFiles(CString sFolderPath, CString sPathName);
	void SearchForRT3DFiles(CString sFolderPath, CString sPathName);
	void SearchForParameterFiles(CString sPathName);
	CString GetFolderAndFileName(CString sFolderPath, CString sPathName, int iSpecyNumber, CString sFilePrefix);

// private attributes
private:
	BOOL m_bHeadsFileExists;
	BOOL m_bIBDFileExists;
	BOOL m_bTICFileExists;
	BOOL m_bGHBFileExists;
	BOOL m_bWELFileExists;
	BOOL m_bDRCFileExists;
	BOOL m_bRICFileExists;
	BOOL m_bWACFileExists;
	BOOL m_bC85FileExists;
	BOOL m_bCH1FileExists;
	BOOL m_bC55FileExists;
	CArray<BOOL, BOOL> m_bMT3DMSSpecyExistsArray;
	CArray<BOOL, BOOL> m_bPHT3DSpecyExistsArray;
	CArray<BOOL, BOOL> m_bRT3DSpecyExistsArray;
	BOOL m_bCONFileExists;
	BOOL m_bLEAFileExists;
	BOOL m_bSTOFileExists;
	BOOL m_bHTCFileExists;
	BOOL m_bLKNFileExists;
	BOOL m_bSCCFileExists;
	BOOL m_bPORFileExists;
	BOOL m_bYLDFileExists;
	BOOL m_bMT3DMSFileExists;
	BOOL m_bPHT3DFileExists;
	BOOL m_bRT3DFileExists;
};

#endif // !defined(AFX_FILESEXIST_H__5E6EE0F1_2D6C_11D4_B21E_0060084B410C__INCLUDED_)