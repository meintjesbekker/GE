/*--------------------------------------------------------------------------*/
/*								vtkDoc.cpp 									*/
/*                            												*/
/*	Purpose	: MFC document class.							                */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include <conio.h>
#include "stdafx.h"
#include "vtkDoc.h"
#include "resource.h"
#include "VisualizeDlg.h"
#include "ReadFile.h"
#include "MT3DMS.h"
#include "ColorTable.h"
#include "LookupTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create                                                           */
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CVtkDoc, CDocument)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CVtkDoc::CVtkDoc()
{
	m_pcModel = NULL;
	m_pcVisualization = NULL;
	m_bViewOpened = FALSE;
	m_bModelOpened = FALSE;
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CVtkDoc::~CVtkDoc()
{
	if (m_pcModel) 
		delete m_pcModel;
	if (m_pcVisualization) 
		delete m_pcVisualization;
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CVtkDoc, CDocument)
	//{{AFX_MSG_MAP(CVtkDoc)
	ON_UPDATE_COMMAND_UI(ID_INTERACT_SCALE, OnUpdateInteractScale)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VISUALIZE, OnUpdateOptionsVisualize)
	ON_COMMAND(ID_OPTIONS_VISUALIZE, OnOptionsVisualize)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CREATEVRML, OnUpdateEditCreateVRML)
	ON_UPDATE_COMMAND_UI(ID_INTERACT_CLIP, OnUpdateInteractClip)
	ON_COMMAND(ID_BUTTON_VISUALIZE, OnButtonVisualize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_VISUALIZE, OnUpdateButtonVisualize)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_AXES, OnUpdateOptionsAxes)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* GetViewOpened                                                            */
/*--------------------------------------------------------------------------*/
BOOL CVtkDoc::GetViewOpened()
{
	return m_bViewOpened;
}

/*--------------------------------------------------------------------------*/
/* Serialize                                                                */
/*--------------------------------------------------------------------------*/
void CVtkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_pcModel->Serialize(ar);
		m_pcVisualization->Serialize(ar);
	}
	else
	{
		m_pcModel = new CModel();
		m_pcModel->Serialize(ar);
		m_pcVisualization = new CVisualization();
		m_pcVisualization->Serialize(ar); 
		m_pcVisualization->CreateModelOutline(m_pcModel);
		m_bModelOpened = TRUE;
		m_bViewOpened = FALSE;
		UpdateAllViews(NULL);
		m_bViewOpened = TRUE;
	}
}

/*--------------------------------------------------------------------------*/
/* Diagnostics                                                              */
/*--------------------------------------------------------------------------*/
#ifdef _DEBUG
void CVtkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVtkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/*--------------------------------------------------------------------------*/
/* OnUpdateInteractScale                                                    */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateInteractScale(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateOptionsVisualize                                                 */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateOptionsVisualize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnOptionsVisualize                                                       */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnOptionsVisualize() 
{
	CVisualizeDlg dlg(NULL, this);
	if (dlg.DoModal() == IDOK)
		UpdateAllViews(NULL);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateEditCreateVRML                                                   */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateEditCreateVRML(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateInteractClip                                                     */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateInteractClip(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);	
}

/*--------------------------------------------------------------------------*/
/* OnButtonVisualize                                                        */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnButtonVisualize() 
{
	OnOptionsVisualize();
}

/*--------------------------------------------------------------------------*/
/* OnUpdateButtonVisualize                                                  */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateButtonVisualize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);	
}

/*--------------------------------------------------------------------------*/
/* OnUpdateOptionsAxes                                                      */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateOptionsAxes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);	
}

/*--------------------------------------------------------------------------*/
/* OnFileOpenPMWIN                                                          */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnFileOpenPMWIN(CString sFolderAndFileName)
{
	if (m_pcModel)
	{
		delete m_pcModel;
		m_pcModel = NULL;
	}	
	m_pcModel = new CModel();
	m_pcModel->SetFolderAndFileName(sFolderAndFileName);
	m_pcModel->SetFolder(sFolderAndFileName.Left(sFolderAndFileName.ReverseFind('\\') + 1));
	m_pcModel->ReadPM5File();
	m_pcModel->ReadGeometryFile();
	m_pcModel->SearchForFiles();
	m_pcModel->CreateModelBounds();
	if (m_pcVisualization)
		delete m_pcVisualization;
	m_pcVisualization = new CVisualization();

	// default objects
	m_pcVisualization->CreateModelOutline(m_pcModel);
	m_bModelOpened = TRUE;
	m_bViewOpened = FALSE;
	UpdateAllViews(NULL);
	m_bViewOpened = TRUE;
}

/*--------------------------------------------------------------------------*/
/* OnOpenDocument                                                           */
/*--------------------------------------------------------------------------*/
BOOL CVtkDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CString sFolderAndFileName;
	sFolderAndFileName = lpszPathName;

	CString sFileExtension;
	sFileExtension = sFolderAndFileName.Mid(sFolderAndFileName.ReverseFind('.') + 1, 3);

	if (sFileExtension.CompareNoCase(_T("gwe")) != 0 && sFileExtension.CompareNoCase(_T("pm5")) != 0)
	{
		CString sMessage;
		sMessage.Format("File format is not supported.");
		AfxMessageBox(sMessage);
		return FALSE;
	}
	else
		DeleteContents();

	if (sFileExtension.CompareNoCase(_T("pm5")) == 0)
	{
		OnFileOpenPMWIN(sFolderAndFileName);
		return FALSE;
	}

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	 // 0 if strings are indentical
	if (sFileExtension.CompareNoCase(_T("gwe")) == 0)
		return TRUE;

	return FALSE;
}

/*--------------------------------------------------------------------------*/
/* OnUpdateFileSave                                                         */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* DeleteContents                                                           */
/*--------------------------------------------------------------------------*/
void CVtkDoc::DeleteContents()
{
	// delete model
	if (m_pcModel)
	{
		delete m_pcModel;
		m_pcModel = NULL;
	}

	// delete visualization
	if (m_pcVisualization)
	{
		delete m_pcVisualization;
		m_pcVisualization = NULL;
	}

	m_bModelOpened = FALSE;
	m_bViewOpened = FALSE;
	CDocument::DeleteContents();
}

/*--------------------------------------------------------------------------*/
/* OnUpdateFileSaveAs                                                       */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateFilePrint                                                        */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateFilePrintPreview                                                 */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateFilePrintSetup                                                   */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}

/*--------------------------------------------------------------------------*/
/* OnUpdateEditCopy                                                         */
/*--------------------------------------------------------------------------*/
void CVtkDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	if (m_bModelOpened)
		pCmdUI->Enable(TRUE);
}
