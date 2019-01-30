/*--------------------------------------------------------------------------*/
/*								vtkView.h   								*/
/*                            												*/
/*	Purpose	: MFC view class.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	:                                                 				*/
/*--------------------------------------------------------------------------*/
#include "vtkDoc.h"

class CVtkView : public CView
{
// protected operations
protected:
	CVtkView();
	DECLARE_DYNCREATE(CVtkView)

// public operations
public:
	virtual ~CVtkView();
	CVtkDoc* GetDocument();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVtkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

// protected operations
protected:
	//{{AFX_MSG(CVtkView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditCreateVRML();
	afx_msg void OnInteractScale();
	afx_msg void OnInteractClip();
	afx_msg void OnOptionsAxes();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// private operations
private:
	void CreateLabeledAxes();
	void CreateColoredAxes();
	void InitializeVTK();

// private attributes		
private:
	BOOL m_Scaled;
	double m_Focalpoint[3];
	double m_Position[3];
	double m_Viewup[3];
	double m_ViewAngle;

	// outline and labeled axes
	vtkOutlineSource* m_OutlineSource;
	vtkPolyDataMapper* m_OutlinePolyDataMapper;
	vtkActor* m_OutlineActor;
	vtkCubeAxesActor2D* m_CubeAxesActor2D;

	// colored axes
	vtkAxes* m_pAxes;
	vtkTubeFilter* m_pTubeFilter;
	vtkPolyDataMapper* m_pPolyDataMapper;
	vtkActor* m_pAxesActor;

	// graphics black box
	vtkWin32RenderWindowInteractor*	m_Interactor;
	vtkOpenGLRenderer* m_Renderer;
	vtkWin32OpenGLRenderWindow* m_RenderWindow;
	
	// handle to window and DC
	HWND hWnd;
	HDC hDC;

	// printing
	int m_iPrintDPI;
};

#ifndef _DEBUG  // debug version in ugviewView.cpp
	inline CVtkDoc* CVtkView::GetDocument()
	{ 
		return (CVtkDoc*)m_pDocument; 
	}
#endif
