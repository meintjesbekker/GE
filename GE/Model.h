/*--------------------------------------------------------------------------*/
/*								Model.h   									*/
/*                            												*/
/*	Purpose	: Contains PMWIN model information.                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MODEL_H__91F964D2_FA17_11D2_B7D6_0060084B410C__INCLUDED_)
#define AFX_MODEL_H__91F964D2_FA17_11D2_B7D6_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxtempl.h>
#include "Average.h"
#include "FilesExist.h"
#include "ReadFile.h"
#include "XYZCoordinate.h"
#endif // _MSC_VER > 1000

class CModel : public CObject
{
// public operations
public:
	CModel();
	virtual ~CModel();

	// file
	void ReadPM5File();
	CString	GetFolderAndFileName() const {return m_sFolderAndFileName;};
	void SetFolderAndFileName(CString sFolderAndFileName) {m_sFolderAndFileName = sFolderAndFileName;};
	CString	GetFolder() const {return m_sFolder;};
	void SetFolder(CString sFolder) {m_sFolder = sFolder;};
	void ReadGeometryFile();
	void SearchForFiles();
	
	// model
	int GetNumberOfRows() const {return m_iNumbRows;};
	int	GetNumberOfColumns() const {return m_iNumbColumns;};
	int	GetNumberOfLayers() const {return m_iNumbLayers;};

	// geometry
	void CreateCoordinates();
	float GetRowCoordinate(int iIndex) const {return m_pfRowCoordinates[iIndex];}; 
	float GetColumnCoordinate(int iIndex) const {return m_pfColumnCoordinates[iIndex];};	
	void CreateMiddleCoordinates();
	float GetMiddleRowCoordinate(int iIndex) const {return m_pfMiddleRowCoordinates[iIndex];}; 
	float GetMiddleColumnCoordinate(int iIndex) const {return m_pfMiddleColumnCoordinates[iIndex];};

	// flags
	float GetHeadsNoFlow() const {return m_fHeadsNoFlow;};
	float GetHeadsDry() const {return m_fHeadsDry;};
	float GetConcentrationInactive() const {return m_fConcentrationInactive;};

	// clip
	BOOL GetClip() const {return m_bClip;};
	void SetClip(BOOL bClip) {m_bClip = bClip;};
	float GetXCutPlaneOrigin() const {return m_fXClipPlaneOrigin;};
	void SetXCutPlaneOrigin(float fXCutPlaneOrigin) {m_fXClipPlaneOrigin = fXCutPlaneOrigin;};
	float GetYCutPlaneOrigin() const {return m_fYClipPlaneOrigin;};
	void SetYCutPlaneOrigin(float fYCutPlaneOrigin) {m_fYClipPlaneOrigin = fYCutPlaneOrigin;};
	float GetZCutPlaneOrigin() const {return m_fZClipPlaneOrigin;};
	void SetZCutPlaneOrigin(float fZCutPlaneOrigin) {m_fZClipPlaneOrigin = fZCutPlaneOrigin;};
	float GetXCutPlaneNormal() const {return m_fXClipPlaneNormal;};
	void SetXCutPlaneNormal(float fXCutPlaneNormal) {m_fXClipPlaneNormal = fXCutPlaneNormal;};
	float GetYCutPlaneNormal() const {return m_fYClipPlaneNormal;};
	void SetYCutPlaneNormal(float fYCutPlaneNormal) {m_fYClipPlaneNormal = fYCutPlaneNormal;};
	float GetZCutPlaneNormal() const {return m_fZClipPlaneNormal;};
	void SetZCutPlaneNormal(float fZCutPlaneNormal) {m_fZClipPlaneNormal = fZCutPlaneNormal;};

	// scale
	float GetXScale() const {return m_fXScale;};
	void SetXScale(float fXScale) {m_fXScale = fXScale;};
	float GetYScale() const {return m_fYScale;};
	void SetYScale(float fYScale) {m_fYScale = fYScale;};
	float GetZScale() const {return m_fZScale;};
	void SetZScale(float fZScale) {m_fZScale = fZScale;};

	// label axes
	BOOL GetXVisible() const {return m_bXVisible;};
	void SetXVisible(BOOL bXVisible) {m_bXVisible = bXVisible;};
	BOOL GetYVisible() const {return m_bYVisible;};
	void SetYVisible(BOOL bYVisible) {m_bYVisible = bYVisible;};
	BOOL GetZVisible() const {return m_bZVisible;};
	void SetZVisible(BOOL bZVisible) {m_bZVisible = bZVisible;};
	int GetNumberOfLabels() const {return m_iNumberOfLabels;};
	void SetNumberOfLabels(int iNumberOfLabels) {m_iNumberOfLabels = iNumberOfLabels;};
	float GetFontFactor() const {return m_fFontFactor;};
	void SetFontFactor(float fFontFactor) {m_fFontFactor = fFontFactor;};
	COLORREF GetColor() const {return m_cColor;};
	void SetColor(COLORREF cColor) {m_cColor = cColor;};

	// color axes
	BOOL GetColorAxesVisibility() const {return m_bColorAxesVisible;};
	void SetColorAxesVisibility(BOOL bColorAxesVisible) {m_bColorAxesVisible = bColorAxesVisible;};

	// model bounds
	void CreateModelBounds();
	float GetMinimumXBound() {return m_cMinimumBound.GetX();};
	float GetMaximumXBound() {return m_cMaximumBound.GetX();};
	float GetMinimumYBound() {return m_cMinimumBound.GetY();};
	float GetMaximumYBound() {return m_cMaximumBound.GetY();};
	float GetMinimumZBound() {return m_cMinimumBound.GetZ();};
	float GetMaximumZBound() {return m_cMaximumBound.GetZ();};

	// serialize
	virtual void Serialize(CArchive& ar);

// private operations
private:
	void CreateRowCoordinates();
	void CreateMiddleRowCoordinates();
	void CreateColumnCoordinates();
	void CreateMiddleColumnCoordinates();

// public attributes
public:
	CFilesExist m_cFilesExist;

// private attributes
private:
	CString	m_sFolderAndFileName; // "c:\model\model.pm5"
	CString m_sFolder; // "c:\model\"
    
	// model
	int m_iNumbColumns;
	int m_iNumbRows;
	int	m_iNumbLayers;

	// geometry
	float m_fColumnsOrigin;
	float m_fRowsOrigin;
	float* m_pfColumnSpacing;
	float* m_pfRowSpacing;
	float* m_pfColumnCoordinates;
	float* m_pfRowCoordinates;
	float* m_pfMiddleColumnCoordinates;
	float* m_pfMiddleRowCoordinates;

	// topology
	float m_fConcentrationInactive; // flag for inactive concentration cells
	float m_fHeadsNoFlow; // flag for no flow head cells
	float m_fHeadsDry; // flag for dry head cells

	// clip
	BOOL m_bClip;
	float m_fXClipPlaneOrigin;
	float m_fYClipPlaneOrigin;
	float m_fZClipPlaneOrigin;
	float m_fXClipPlaneNormal;
	float m_fYClipPlaneNormal;
	float m_fZClipPlaneNormal;

	// scale
	float m_fXScale;
	float m_fYScale;
	float m_fZScale;

	// label axes
	BOOL m_bXVisible;
	BOOL m_bYVisible;
	BOOL m_bZVisible;
	int m_iNumberOfLabels;
	float m_fFontFactor;
	COLORREF m_cColor;

	// color axes
	BOOL m_bColorAxesVisible;

	// model bounds
	CXYZCoordinate m_cMinimumBound;
	CXYZCoordinate m_cMaximumBound;

	// other
	CReadFile m_cReadFile;

public:
	// serialize
	DECLARE_SERIAL(CModel)
};

#endif // !defined(AFX_MODEL_H__91F964D2_FA17_11D2_B7D6_0060084B410C__INCLUDED_)