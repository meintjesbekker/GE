/*--------------------------------------------------------------------------*/
/* ParameterColorPage.cpp                                                   */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "ParameterColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterColorPage property page

IMPLEMENT_DYNCREATE(CParameterColorPage, CPropertyPage)

CParameterColorPage::CParameterColorPage(CParameter* pParameter /* = NULL */) : CPropertyPage(CParameterColorPage::IDD)
{
	m_pParameter = pParameter;
	//{{AFX_DATA_INIT(CParameterColorPage)
	m_Opacity = 0.0f;
	m_SolidColorRadio = -1;
	//}}AFX_DATA_INIT
}

CParameterColorPage::~CParameterColorPage()
{
}

void CParameterColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterColorPage)
	DDX_Control(pDX, IDC_RADIO_SOLID_COLOR, m_SolidColorButton);
	DDX_Control(pDX, IDC_STATIC_SOLID_COLOR, m_SolidColorPicture);
	DDX_Control(pDX, IDC_EDIT_OPACITY, m_OpacityEdit);
	DDX_Text(pDX, IDC_EDIT_OPACITY, m_Opacity);
	DDX_Radio(pDX, IDC_RADIO_SOLID_COLOR, m_SolidColorRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParameterColorPage)
	ON_BN_CLICKED(IDC_BUTTON_SOLID_COLOR, OnButtonSolidColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterColorPage message handlers

void CParameterColorPage::OnButtonSolidColor() 
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_SolidColor = dlg.GetColor();
		RedrawSolidColorPicture();
	}	
}

void CParameterColorPage::OnOK() 
{
	m_pParameter->SetOpacity(m_Opacity);	
	m_pParameter->SetSolidColor(m_SolidColor);
	if (m_SolidColorRadio == 0)
		m_pParameter->SetSolidOrFillColor(TRUE);
	else
		m_pParameter->SetSolidOrFillColor(FALSE);
	
	CPropertyPage::OnOK();
}

BOOL CParameterColorPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_Opacity		= m_pParameter->GetOpacity();
	m_SolidColor	= m_pParameter->GetSolidColor();
	
	if (m_pParameter->GetSolidOrFillColor())
		m_SolidColorRadio = 0;
	else
		m_SolidColorRadio = 1;
		
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameterColorPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// 1 - Get placeholder coordinates
	CRect rect; // Placeholder rectangle
	m_SolidColorPicture.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// 2 - Draw inside placeholder rectangle
	CBrush Brush;
	Brush.CreateSolidBrush(m_SolidColor);
	dc.FillRect(&rect, &Brush);

	// Do not call CPropertyPage::OnPaint() for painting messages
}

/*--------------------------------------------------------------------------*/
/* RedrawSolidColorPicture                                                  */
/*--------------------------------------------------------------------------*/
void CParameterColorPage::RedrawSolidColorPicture()
{
	// 1 - Get placeholder coordinates
	CRect rect; // Placeholder rectangle
	m_SolidColorPicture.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// 2 - Force update of drawing area
	InvalidateRect(rect);
	UpdateWindow();
}

