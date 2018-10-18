/*--------------------------------------------------------------------------*/
/*								ClipDlg.cpp    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Clip dialog box.          	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.3 Interact.            				*/
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ClipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                      		*/
/*--------------------------------------------------------------------------*/
CClipDlg::CClipDlg(CWnd* pParent, /* = NULL */ 
				   CModel* pModel /* = NULL */) 
	: CDialog(CClipDlg::IDD, pParent)
{
	m_pModel = pModel;

	//{{AFX_DATA_INIT(CClipDlg)
	m_bClip = FALSE;
	m_fXOrigin = 0.0f;
	m_fYOrigin = 0.0f;
	m_fZOrigin = 0.0f;
	m_fXNormal = 0.0f;
	m_fYNormal = 0.0f;
	m_fZNormal = 0.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* DoDataExchange                                                   		*/
/*--------------------------------------------------------------------------*/
void CClipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CClipDlg)
	DDX_Control(pDX, IDC_SLD_Z_NORMAL, m_cZNormalSlider);
	DDX_Control(pDX, IDC_SLD_Y_NORMAL, m_cYNormalSlider);
	DDX_Control(pDX, IDC_SLD_X_NORMAL, m_cXNormalSlider);
	DDX_Check(pDX, IDC_CHECK_CLIP, m_bClip);
	DDX_Text(pDX, IDC_EDIT_XORIGIN, m_fXOrigin);
	DDX_Text(pDX, IDC_EDIT_YORIGIN, m_fYOrigin);
	DDX_Text(pDX, IDC_EDIT_ZORIGIN, m_fZOrigin);
	DDX_Text(pDX, IDC_EDIT_XNORMAL, m_fXNormal);
	DDV_MinMaxFloat(pDX, m_fXNormal, -1.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_YNORMAL, m_fYNormal);
	DDV_MinMaxFloat(pDX, m_fYNormal, -1.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_ZNORMAL, m_fZNormal);
	DDV_MinMaxFloat(pDX, m_fZNormal, -1.f, 1.f);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                      		*/
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CClipDlg, CDialog)
	//{{AFX_MSG_MAP(CClipDlg)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                        		*/
/*--------------------------------------------------------------------------*/
BOOL CClipDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bClip = m_pModel->GetClip();
	m_fXOrigin = m_pModel->GetXCutPlaneOrigin();
	m_fYOrigin = m_pModel->GetYCutPlaneOrigin();
	m_fZOrigin = m_pModel->GetZCutPlaneOrigin();
	m_fXNormal = m_pModel->GetXCutPlaneNormal();
	m_fYNormal = m_pModel->GetYCutPlaneNormal();
	m_fZNormal = m_pModel->GetZCutPlaneNormal();
	UpdateData(FALSE);

	// x normal slider
	m_cXNormalSlider.SetRange(-1000, 1000, TRUE);
	m_cXNormalSlider.SetPos((int)(m_fXNormal * 1000.0f));
	m_cXNormalSlider.SetTicFreq(200);
	m_cXNormalSlider.SetPageSize(200);

	// y normal slider
	m_cYNormalSlider.SetRange(-1000, 1000, TRUE);
	m_cYNormalSlider.SetPos((int)(m_fYNormal * 1000.0f));
	m_cYNormalSlider.SetTicFreq(200);
	m_cYNormalSlider.SetPageSize(200);

	// x normal slider
	m_cZNormalSlider.SetRange(-1000, 1000, TRUE );
	m_cZNormalSlider.SetPos((int)(m_fZNormal * 1000.0f));
	m_cZNormalSlider.SetTicFreq(200);
	m_cZNormalSlider.SetPageSize(200);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*--------------------------------------------------------------------------*/
/* OnHScroll                                                                */
/*--------------------------------------------------------------------------*/
void CClipDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	float fNormal;
	fNormal = (float)(((CSliderCtrl*)pScrollBar)->GetPos()) / 1000.0f;
	if (nSBCode == SB_ENDSCROLL)
		return;

	// x normal slider
	if ((CSliderCtrl*)pScrollBar == &m_cXNormalSlider)
		m_fXNormal = fNormal;

	// y normal slider
	if ((CSliderCtrl*)pScrollBar == &m_cYNormalSlider)
		m_fYNormal = fNormal;

	// z normal slider
	if ((CSliderCtrl*)pScrollBar == &m_cZNormalSlider)
		m_fZNormal = fNormal;
	
	// update data
	UpdateData(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}