/*--------------------------------------------------------------------------*/
/*								MenuButton.h   								*/
/*                            												*/
/*	Purpose	: Menu Button for Visualize dialog.                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 2.1.4 "Options".                        */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MENUBUTTON_H__870C3C33_B140_11D3_B13C_0060084B410C__INCLUDED_)
#define AFX_MENUBUTTON_H__870C3C33_B140_11D3_B13C_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMenuButton : public CButton
{
// public operations
public:
	CMenuButton();
	virtual ~CMenuButton();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CMenuButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENUBUTTON_H__870C3C33_B140_11D3_B13C_0060084B410C__INCLUDED_)