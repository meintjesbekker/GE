/*--------------------------------------------------------------------------*/
/*						HydraulicTDComponents.h  							*/
/*                            												*/
/*	Purpose	: Create Time Dependent, Hydraulic Components.					*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.7 "Hydraulic Components".                   */
/*--------------------------------------------------------------------------*/
#if !defined(AFX_HYDRAULICTDCOMPONENTS_H__C3CBE781_57BC_11D4_B2A3_0060084B410C__INCLUDED_)
#define AFX_HYDRAULICTDCOMPONENTS_H__C3CBE781_57BC_11D4_B2A3_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "HydraulicComponents.h"
#endif // _MSC_VER > 1000

class CHydraulicTDComponents : public CHydraulicComponents  
{
// public operations
public:
	CHydraulicTDComponents(CModel* pcModel = NULL);
	virtual ~CHydraulicTDComponents();

	// create, update
	virtual void Create();
	virtual void Update();

	// dialogs
	virtual BOOL DoSheetAndPagesForCreate();
	virtual BOOL DoSheetAndPagesForChange();
};

#endif // !defined(AFX_HYDRAULICTDCOMPONENTS_H__C3CBE781_57BC_11D4_B2A3_0060084B410C__INCLUDED_)
