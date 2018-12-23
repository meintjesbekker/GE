/*--------------------------------------------------------------------------*/
/*								vtkView.cpp   								*/
/*                            												*/
/*	Purpose	: MFC view class.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "resource.h"
#include "vtkView.h"
#include "AxesDlg.h"
#include "ClipDlg.h"
#include "ScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Dynamic Create        													*/
/*--------------------------------------------------------------------------*/
IMPLEMENT_DYNCREATE(CVtkView, CView)

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CVtkView::CVtkView()
{
	m_Scaled = FALSE;

	// labeled axes
	m_OutlineSource = NULL;
	m_OutlinePolyDataMapper = NULL;
	m_OutlineActor = NULL;
	m_CubeAxesActor2D = NULL;

	// colored axes
	m_pAxes = NULL;
	m_pTubeFilter = NULL;
	m_pPolyDataMapper = NULL;
	m_pAxesActor = NULL;

	// black box
	m_Renderer = NULL;
	m_RenderWindow = NULL;
	m_Interactor = NULL;

	// printing
	m_iPrintDPI = 100;
	InitializeVTK();
}

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
CVtkView::~CVtkView()
{
	// colored axes
	if (m_pAxes) m_pAxes->Delete();
	if (m_pTubeFilter) m_pTubeFilter->Delete();
	if (m_pPolyDataMapper) m_pPolyDataMapper->Delete();
	if (m_pAxesActor) m_pAxesActor->Delete();

	// labeled axes
	if (m_OutlineSource) m_OutlineSource->Delete();
	if (m_OutlinePolyDataMapper) m_OutlinePolyDataMapper->Delete();
	if (m_OutlineActor) m_OutlineActor->Delete();
	if (m_CubeAxesActor2D) m_CubeAxesActor2D->Delete();

	// graphics black box
	if (m_Renderer) m_Renderer->Delete();
	if (m_RenderWindow) m_RenderWindow->Delete();
	if (m_Interactor) m_Interactor->Delete();
}

/*--------------------------------------------------------------------------*/
/* Message Map           													*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CVtkView, CView)
	//{{AFX_MSG_MAP(CVtkView)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_CREATEVRML, OnEditCreateVRML)
	ON_COMMAND(ID_INTERACT_SCALE, OnInteractScale)
	ON_COMMAND(ID_INTERACT_CLIP, OnInteractClip)
	ON_COMMAND(ID_OPTIONS_AXES, OnOptionsAxes)
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CVtkView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CVtkView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CVtkView::OnFilePrintPreview)
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnDraw                                                                   */
/*--------------------------------------------------------------------------*/
void CVtkView::OnDraw(CDC* pDC)
{ 
	if (!m_Interactor->GetInitialized())
	{
		CRect rect;
		this->GetClientRect(&rect);
		this->m_Interactor->Initialize();
		this->m_RenderWindow->SetSize(rect.right - rect.left, rect.bottom - rect.top);
		this->m_Renderer->ResetCamera();
	}

	// do printing and print preview
	if (pDC->IsPrinting())
	{
		// TODO.
	}
	else
	{
		m_RenderWindow->Render();
	}
	CView::OnDraw(pDC);
}

/*--------------------------------------------------------------------------*/
/* PreCreateWindow                                                          */
/*--------------------------------------------------------------------------*/
BOOL CVtkView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_OWNDC | WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

/*--------------------------------------------------------------------------*/
/* OnUpdate                                                                 */
/*--------------------------------------------------------------------------*/
void CVtkView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetDocument()->m_pcModel == NULL || !GetDocument()->GetViewOpened())
	{
		m_Renderer->RemoveAllViewProps();
		//m_RenderWindow->RemoveRenderer(m_Renderer);
		//if (m_Renderer)
		//	m_Renderer->Delete();
		//m_Renderer = vtkOpenGLRenderer::New();
		//m_Renderer->SetBackground(1, 0, 1);
		//m_Renderer->TwoSidedLightingOn();
		//m_Renderer->ResetCamera();
		//m_RenderWindow->AddRenderer(m_Renderer);
	}

	if (GetDocument()->m_pcModel)
	{
		m_Renderer->RemoveAllViewProps();

		// visualization object
		for (int i = 0; i < GetDocument()->m_pcVisualization->m_pcVisualizationObjectArray.GetSize(); i++)
		{
			if (GetDocument()->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(i)->GetVisibility())
			{
				vtkActor* anActor;
				for (GetDocument()->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(i)->GetActorCollection()->InitTraversal();
					(anActor = GetDocument()->m_pcVisualization->m_pcVisualizationObjectArray.GetAt(i)->GetActorCollection()->GetNextActor());)
						m_Renderer->AddViewProp(anActor);
			}
		}
	}

	// if scaled
	if (m_Scaled || GetDocument()->m_pcModel == NULL || !GetDocument()->GetViewOpened())
	{
		m_Renderer->ResetCamera();
		m_Renderer->ResetCameraClippingRange();
		m_Renderer->GetActiveCamera()->GetFocalPoint(focalpoint);
		m_Renderer->GetActiveCamera()->GetPosition(position);
		m_Renderer->GetActiveCamera()->GetViewUp(viewup);
		viewangle = m_Renderer->GetActiveCamera()->GetViewAngle();
		m_Scaled = FALSE;
	}

	// m_Renderer->GetActiveCamera()->SetFocalPoint(focalpoint);
	// m_Renderer->GetActiveCamera()->SetPosition(position);
	// m_Renderer->GetActiveCamera()->SetViewUp(viewup);
	// m_Renderer->GetActiveCamera()->SetViewAngle(viewangle);
	// m_Renderer->ResetCameraClippingRange();

	// create the axes
	if (GetDocument()->m_pcModel)
	{
		// label axes
		if (   GetDocument()->m_pcModel->GetXVisible()
			|| GetDocument()->m_pcModel->GetYVisible()
			|| GetDocument()->m_pcModel->GetZVisible())
			CreateLabeledAxes();

		// color axes
		if (GetDocument()->m_pcModel->GetColorAxesVisibility())
			CreateColoredAxes();
	}

	// TODO: Remove it is for debugging only.
	vtkActorCollection* debugactor = this->m_Renderer->GetActors();
	
	CView::OnUpdate(pSender, lHint, pHint);
}

/*--------------------------------------------------------------------------*/
/* WindowProc                                                               */
/*--------------------------------------------------------------------------*/
LRESULT CVtkView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	//	case	WM_PAINT: 
		case	WM_LBUTTONDOWN: 
		case	WM_LBUTTONUP:
		case	WM_MBUTTONDOWN: 
		case	WM_MBUTTONUP:
		case	WM_RBUTTONDOWN: 
		case	WM_RBUTTONUP:
		case	WM_MOUSEMOVE:
		case	WM_CHAR:
		case	WM_TIMER:
				{	
					if (m_Interactor->GetInitialized())
					{
						return vtkHandleMessage2(this->m_hWnd, message, wParam, lParam, this->m_Interactor);
					}
				}
		break;
	}

  return CView::WindowProc(message, wParam, lParam);
}

/*--------------------------------------------------------------------------*/
/* Diagnostics                                                              */
/*--------------------------------------------------------------------------*/
#ifdef _DEBUG
void CVtkView::AssertValid() const
{
	CView::AssertValid();
}

void CVtkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVtkDoc* CVtkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVtkDoc)));
	return (CVtkDoc*)m_pDocument;
}
#endif //_DEBUG

/*--------------------------------------------------------------------------*/
/* OnCreate                                                                 */
/*--------------------------------------------------------------------------*/
int CVtkView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->m_RenderWindow->AddRenderer(this->m_Renderer);
	
	// setup the parent window
	this->m_RenderWindow->SetParentId(this->m_hWnd);
	this->m_Interactor->SetRenderWindow(this->m_RenderWindow);

	return 0;
}

/*--------------------------------------------------------------------------*/
/* OnEditCreateVRML                                                         */
/*--------------------------------------------------------------------------*/
void CVtkView::OnEditCreateVRML() 
{
	CFileDialog fileDlg(FALSE,
					    _T("*.wrl"),
					    NULL,
					    OFN_HIDEREADONLY,
					    _T("VRML File (*.wrl)|*.wrl|All Files|*.*||"),
					    NULL
					    );
	if (fileDlg.DoModal() == IDOK)
	{
		vtkVRMLExporter* vrml = vtkVRMLExporter::New();
		vrml->SetInput(m_RenderWindow);
		vrml->SetFileName(LPTSTR(LPCTSTR(fileDlg.GetPathName())));
		vrml->Write();
		vrml->Delete();
	}	
}

/*--------------------------------------------------------------------------*/
/* OnInteractScale                                                          */
/*--------------------------------------------------------------------------*/
void CVtkView::OnInteractScale() 
{
	CScaleDlg dlg(NULL, GetDocument()->m_pcModel);
	if (dlg.DoModal() == IDOK)
 	{
		GetDocument()->m_pcModel->SetXScale(dlg.GetXScale());
		GetDocument()->m_pcModel->SetYScale(dlg.GetYScale());
		GetDocument()->m_pcModel->SetZScale(dlg.GetZScale());
		vtkActorCollection* actors = m_Renderer->GetActors();
		actors->InitTraversal();
		vtkActor* anActor;
		for (actors->InitTraversal(); (anActor = actors->GetNextItem());)
			anActor->SetScale(	GetDocument()->m_pcModel->GetXScale(), 
								GetDocument()->m_pcModel->GetYScale(), 
								GetDocument()->m_pcModel->GetZScale());
		m_Scaled = TRUE;
		OnUpdate(NULL, 0, NULL);
	}
}

/*--------------------------------------------------------------------------*/
/* OnInteractClip                                                           */
/*--------------------------------------------------------------------------*/
void CVtkView::OnInteractClip() 
{
	CClipDlg dlg(NULL, GetDocument()->m_pcModel);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument()->m_pcModel->SetClip(dlg.GetClip());
		GetDocument()->m_pcModel->SetXCutPlaneOrigin(dlg.GetXOrigin());
		GetDocument()->m_pcModel->SetYCutPlaneOrigin(dlg.GetYOrigin());
		GetDocument()->m_pcModel->SetZCutPlaneOrigin(dlg.GetZOrigin());
		GetDocument()->m_pcModel->SetXCutPlaneNormal(dlg.GetXNormal());
		GetDocument()->m_pcModel->SetYCutPlaneNormal(dlg.GetYNormal());
		GetDocument()->m_pcModel->SetZCutPlaneNormal(dlg.GetZNormal());
		GetDocument()->m_pcVisualization->Clip();
	}
	OnUpdate(NULL, 0, NULL);
}

/*--------------------------------------------------------------------------*/
/* OnOptionsAxes                                                            */
/*--------------------------------------------------------------------------*/
void CVtkView::OnOptionsAxes() 
{
	CAxesDlg dlg(NULL, GetDocument()->m_pcModel);
	if (dlg.DoModal() == IDOK)
	{
		GetDocument()->m_pcModel->SetXVisible(dlg.GetXVisible());
		GetDocument()->m_pcModel->SetYVisible(dlg.GetYVisible());
		GetDocument()->m_pcModel->SetZVisible(dlg.GetZVisible());
		GetDocument()->m_pcModel->SetFontFactor(dlg.GetFontFactor());
		GetDocument()->m_pcModel->SetNumberOfLabels(dlg.GetNumberOfLabels());
		GetDocument()->m_pcModel->SetColor(dlg.GetColor());
		GetDocument()->m_pcModel->SetColorAxesVisibility(dlg.GetColorAxesVisibilty());
	}
	OnUpdate(NULL, 0, NULL);	
}

/*--------------------------------------------------------------------------*/
/* OnSize                                                                   */
/*--------------------------------------------------------------------------*/
void CVtkView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	this->m_RenderWindow->SetSize(rect.right - rect.left, rect.bottom - rect.top);
}

/*--------------------------------------------------------------------------*/
/* OnEraseBkgnd                                                             */
/*--------------------------------------------------------------------------*/
BOOL CVtkView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

/*--------------------------------------------------------------------------*/
/* CreateLabeledAxes                                                        */
/*--------------------------------------------------------------------------*/
void CVtkView::CreateLabeledAxes()
{
	if (m_OutlineSource)
	{
		m_OutlineSource->Delete();
		m_OutlineSource = NULL;
	}
	m_OutlineSource = vtkOutlineSource::New();
	m_OutlineSource->SetBounds(	GetDocument()->m_pcModel->GetMinimumXBound(),
								GetDocument()->m_pcModel->GetMaximumXBound(), 
								GetDocument()->m_pcModel->GetMinimumYBound(), 
								GetDocument()->m_pcModel->GetMaximumYBound(), 
								GetDocument()->m_pcModel->GetMinimumZBound(), 
								GetDocument()->m_pcModel->GetMaximumZBound());
	if (m_OutlinePolyDataMapper)
	{
		m_OutlinePolyDataMapper->Delete();
		m_OutlinePolyDataMapper = NULL;
	}
	m_OutlinePolyDataMapper = vtkPolyDataMapper::New();
	m_OutlinePolyDataMapper->SetInputData(m_OutlineSource->GetOutput());
	m_OutlineActor = vtkActor::New();
	m_OutlineActor->SetMapper(m_OutlinePolyDataMapper);
	// TODO: Set the color back.
	m_OutlineActor->GetProperty()->SetColor(0, 1, 0);
	m_OutlineActor->SetScale(	GetDocument()->m_pcModel->GetXScale(), 
								GetDocument()->m_pcModel->GetYScale(),
								GetDocument()->m_pcModel->GetZScale());
	// axes
	if (m_CubeAxesActor2D)
	{
		m_CubeAxesActor2D->Delete();
		m_CubeAxesActor2D = NULL;
	}
	m_CubeAxesActor2D = vtkCubeAxesActor2D::New();
	m_CubeAxesActor2D->SetViewProp(m_OutlineActor);
	m_CubeAxesActor2D->SetCamera(m_Renderer->GetActiveCamera());
	// TODO: m_CubeAxesActor2D->ShadowOn();
	m_CubeAxesActor2D->SetFlyModeToClosestTriad();
	m_CubeAxesActor2D->SetXAxisVisibility(GetDocument()->m_pcModel->GetXVisible());
	m_CubeAxesActor2D->SetYAxisVisibility(GetDocument()->m_pcModel->GetYVisible());
	m_CubeAxesActor2D->SetZAxisVisibility(GetDocument()->m_pcModel->GetZVisible());
	m_CubeAxesActor2D->SetNumberOfLabels(GetDocument()->m_pcModel->GetNumberOfLabels());
	m_CubeAxesActor2D->SetFontFactor(GetDocument()->m_pcModel->GetFontFactor());

	// color
	float red = GetRValue(GetDocument()->m_pcModel->GetColor()) / 255.0;
	float green = GetGValue(GetDocument()->m_pcModel->GetColor()) / 255.0;
	float blue = GetBValue(GetDocument()->m_pcModel->GetColor()) / 255.0;
	m_CubeAxesActor2D->GetProperty()->SetColor(red, green, blue);
	// TODO: Undo not adding the outline.
	m_Renderer->AddViewProp(m_CubeAxesActor2D);
}

/*--------------------------------------------------------------------------*/
/* CreateColoredAxes                                                        */
/*--------------------------------------------------------------------------*/
void CVtkView::CreateColoredAxes()
{
	if (m_pAxes)
	{
		m_pAxes->Delete();
		m_pAxes = NULL;
	}
	m_pAxes = vtkAxes::New();
	m_pAxes->SetOrigin(GetDocument()->m_pcModel->GetMinimumXBound(),
    					GetDocument()->m_pcModel->GetMinimumYBound(),
	    				GetDocument()->m_pcModel->GetMinimumZBound());

    //m_pAxes->SetOrigin(	GetDocument()->m_pcModel->GetMinimumXBound() * GetDocument()->m_pcModel->GetXScale(), 
	//					GetDocument()->m_pcModel->GetMinimumYBound() * GetDocument()->m_pcModel->GetYScale(), 
	//					GetDocument()->m_pcModel->GetMinimumZBound() * GetDocument()->m_pcModel->GetZScale());
    //m_pAxes->SetScaleFactor(fabs(GetDocument()->m_pcModel->GetMaximumXBound() - GetDocument()->m_pcModel->GetMinimumXBound()) / 7.0);
	if (m_pTubeFilter)
	{
		m_pTubeFilter->Delete();
		m_pTubeFilter = NULL;
	}
	m_pTubeFilter = vtkTubeFilter::New();
    m_pTubeFilter->SetInputData(m_pAxes->GetOutput());
	m_pTubeFilter->SetRadius(m_pAxes->GetScaleFactor());
    //m_pTubeFilter->SetRadius(m_pAxes->GetScaleFactor()/25.0);
    //m_pTubeFilter->SetNumberOfSides(6);
	
	if (m_pPolyDataMapper)
	{
		m_pPolyDataMapper->Delete();
		m_pPolyDataMapper = NULL;
	}
	m_pPolyDataMapper = vtkPolyDataMapper::New();
	m_pPolyDataMapper->SetInputData(m_pTubeFilter->GetOutput());
	
	if (m_pAxesActor)
	{
		m_pAxesActor->Delete();
		m_pAxesActor = NULL;
	}
	m_pAxesActor = vtkActor::New();
	m_pAxesActor->SetMapper(m_pPolyDataMapper);
	// TODO: Set the scale back to what it is supposed to be.
	// m_pAxesActor->SetScale(1, 1, 1);
	// TODO: Set Modified on the actor. Works for outline!
	// m_pAxesActor->Modified();
	m_Renderer->AddViewProp(m_pAxesActor);
	// TODO: Is this Modified necassary, and the Render?
	//m_Renderer->DebugOn();
	//m_Renderer->Modified();
	//m_RenderWindow->Render();
}

/*--------------------------------------------------------------------------*/
/* InitializeVTK                                                            */
/*--------------------------------------------------------------------------*/
void CVtkView::InitializeVTK()
{
	// renderer
	if (m_Renderer)
		m_Renderer->Delete();
	m_Renderer = vtkOpenGLRenderer::New();
	m_Renderer->SetBackground(1, 0, 1);
	// TODO: Set back to white.
	// m_Renderer->SetBackground(1, 0, 0);
	// m_Renderer->TwoSidedLightingOn();
	// m_Renderer->ResetCamera();

	// renderwindow
	if (m_RenderWindow)
		m_RenderWindow->Delete();
	// TODO: Try vtkMFCWindow.
	m_RenderWindow = vtkWin32OpenGLRenderWindow::New();
	// m_RenderWindow->AddRenderer(m_Renderer);
	// m_RenderWindow->SwapBuffersOn();

	// interactor
	if (m_Interactor)
		m_Interactor->Delete();
	m_Interactor = vtkWin32RenderWindowInteractor::New();
	// m_Interactor->LightFollowCameraOn();
}

/*--------------------------------------------------------------------------*/
/* OnPreparePrinting                                                        */
/*--------------------------------------------------------------------------*/
BOOL CVtkView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

/*--------------------------------------------------------------------------*/
/* OnEditCopy                                                               */
/*--------------------------------------------------------------------------*/
void CVtkView::OnEditCopy() 
{
	LPBITMAPINFOHEADER lpbi; // pointer to BITMAPINFOHEADER
	DWORD dwLen; // size of memory block
	HANDLE hDIB = NULL; // handle to DIB, temp handle
	vtkWindow* vtkWin = m_RenderWindow;
	int* size = vtkWin->GetSize();
	int dataWidth = ((size[0] * 3 + 3) / 4) * 4;

	// open clipboard
	if (OpenClipboard())
	{
		// TODO: Fix copy.
		/*
		BeginWaitCursor();
		EmptyClipboard();
		dwLen = sizeof(BITMAPINFOHEADER) + dataWidth*size[1];
		hDIB = ::GlobalAlloc(GHND, dwLen);
		lpbi = (LPBITMAPINFOHEADER) ::GlobalLock(hDIB);
		lpbi->biSize = sizeof(BITMAPINFOHEADER);
		lpbi->biWidth = size[0];
		lpbi->biHeight = size[1];
		lpbi->biPlanes = 1;
		lpbi->biBitCount = 24;
		lpbi->biCompression = BI_RGB;
		lpbi->biClrUsed = 0;
		lpbi->biClrImportant = 0;
		lpbi->biSizeImage = dataWidth*size[1];
		m_RenderWindow->SetupMemoryRendering(	size[0],
												size[1],
												GetDC()->GetSafeHdc());
		vtkWin->Render();
		memcpy(	(LPSTR)lpbi + lpbi->biSize,
				 m_RenderWindow->GetMemoryData(),
				 dataWidth * size[1]);
		SetClipboardData (CF_DIB, hDIB);
		::GlobalUnlock(hDIB);
		CloseClipboard();
		m_RenderWindow->ResumeScreenRendering();
		EndWaitCursor();
		*/
	}			
}