/*--------------------------------------------------------------------------*/
/*								vtkDoc.h   									*/
/*                            												*/
/*	Purpose	: MFC document class.							                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#include "Visualization.h"
#endif // _MSC_VER > 1000

class CVtkDoc : public CDocument
{
// protected operations
protected: // create from serialization only
	CVtkDoc();
	DECLARE_DYNCREATE(CVtkDoc)

// public operations
public:
	virtual ~CVtkDoc();
	BOOL GetViewOpened();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVtkDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif


// protected operations
protected:
	//{{AFX_MSG(CVtkDoc)
	afx_msg void OnUpdateInteractScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsVisualize(CCmdUI* pCmdUI);
	afx_msg void OnOptionsVisualize();
	afx_msg void OnUpdateEditCreateVRML(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInteractClip(CCmdUI* pCmdUI);
	afx_msg void OnButtonVisualize();
	afx_msg void OnUpdateButtonVisualize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsAxes(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private operations
private:
	void OnFileOpenPMWIN(CString sFolderAndFileName);

// public attributes
public:
	CModel*	m_pcModel; // model information
	CVisualization* m_pcVisualization; // visualization

// private attributes
private:
	BOOL m_bViewOpened;
	BOOL m_bModelOpened; // to see if model is opened
};
