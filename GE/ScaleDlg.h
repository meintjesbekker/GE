/*--------------------------------------------------------------------------*/
/*								ScaleDlg.h    								*/
/*                            												*/
/*	Purpose	: Member variables and functions for Scale dialog box.          */
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright 2000                                   				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.3 "Interact".                       */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_SCALEDLG_H__1BB63D11_D551_11D3_B176_0060084B410C__INCLUDED_)
#define AFX_SCALEDLG_H__1BB63D11_D551_11D3_B176_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#endif // _MSC_VER > 1000

class CScaleDlg : public CDialog
{
// public operations
public:
	CScaleDlg(	CWnd* pParent = NULL, 
				CModel* pcModel = NULL);
	float GetXScale() const {return m_fXScale;};
	float GetYScale() const {return m_fYScale;};
	float GetZScale() const {return m_fZScale;};

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// protected operations
protected:
	// Generated message map functions
	//{{AFX_MSG(CScaleDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// public attributes
public:
	//{{AFX_DATA(CScaleDlg)
	enum { IDD = IDD_SCALE };
	float m_fXScale;
	float m_fYScale;
	float m_fZScale;
	//}}AFX_DATA

// private attributes
private:
	CModel* m_pModel;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SCALEDLG_H__1BB63D11_D551_11D3_B176_0060084B410C__INCLUDED_)