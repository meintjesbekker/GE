/*--------------------------------------------------------------------------*/
/*						MT3DMSContourAndColorEditBox.h   					*/
/*                            												*/
/*	Purpose	: Edit box for contour in Contour and Color dialog box.			*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: User's Guide, section 3.6.2 "Contour and Color".				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_MT3DMSCONTOURANDCOLOREDITBOX_H__B0FC3EA3_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
#define AFX_MT3DMSCONTOURANDCOLOREDITBOX_H__B0FC3EA3_0AB7_11D4_B1DC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMT3DMSContourAndColorEditBox : public CEdit
{
// public operations
public:
	CMT3DMSContourAndColorEditBox();
	virtual ~CMT3DMSContourAndColorEditBox();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMT3DMSContourAndColorEditBox)
	//}}AFX_VIRTUAL

// protected operations
protected:
	//{{AFX_MSG(CMT3DMSContourAndColorEditBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MT3DMSCONTOURANDCOLOREDITBOX_H__B0FC3EA3_0AB7_11D4_B1DC_0060084B410C__INCLUDED_)
