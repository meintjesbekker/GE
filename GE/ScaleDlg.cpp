/*--------------------------------------------------------------------------*/
/*								ScaleDlg.cpp  								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Scale dialog box.          */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.3 "Interact".                       */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*--------------------------------------------------------------------------*/
/* Construction                                                             */
/*--------------------------------------------------------------------------*/
CScaleDlg::CScaleDlg(CWnd* pParent, /* = NULL */ 
					 CModel* pcModel /* = NULL */) 
	: CDialog(CScaleDlg::IDD, pParent)
{
	m_pModel = pcModel;

	//{{AFX_DATA_INIT(CScaleDlg)
	m_fXScale = 1.0f;
	m_fYScale = 1.0f;
	m_fZScale = 1.0f;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------*/
/* Message Map                                                              */
/*--------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CScaleDlg, CDialog)
	//{{AFX_MSG_MAP(CScaleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*--------------------------------------------------------------------------*/
/* Destruction                                                              */
/*--------------------------------------------------------------------------*/
void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg)
	DDX_Text(pDX, IDC_EDIT_XSCALE, m_fXScale);
	DDV_MinMaxFloat(pDX, m_fXScale, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_EDIT_YSCALE, m_fYScale);
	DDV_MinMaxFloat(pDX, m_fYScale, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_EDIT_ZSCALE, m_fZScale);
	DDV_MinMaxFloat(pDX, m_fZScale, -1000.f, 1000.f);
	//}}AFX_DATA_MAP
}

/*--------------------------------------------------------------------------*/
/* OnInitDialog                                                             */
/*--------------------------------------------------------------------------*/
BOOL CScaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_fXScale = m_pModel->GetXScale();
	m_fYScale = m_pModel->GetYScale();
	m_fZScale = m_pModel->GetZScale();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}