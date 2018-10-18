/*--------------------------------------------------------------------------*/
/*						VisualizationObject.h								*/
/*                            												*/
/*	Purpose	: Class used for polymorphism. CVisualization contains an arry	*/
/*			  of this class.												*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_VISUALIZATIONOBJECT_H__84AAFDA5_5D3D_11D4_B2AC_0060084B410C__INCLUDED_)
#define AFX_VISUALIZATIONOBJECT_H__84AAFDA5_5D3D_11D4_B2AC_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#endif // _MSC_VER > 1000

class CVisualizationObject : public CObject  
{
	DECLARE_SERIAL(CVisualizationObject)

public:
	CVisualizationObject();
	virtual ~CVisualizationObject();

	// visibility
	BOOL GetVisibility() const {return m_bVisible;};
	void SetVisibility(BOOL bVisible) {m_bVisible = bVisible;};
	
	// description
	CString GetDescription() const {return m_sDescription;};
	void SetDescription(CString sDescription) {m_sDescription = sDescription;};
	
	// remove actors
	void RemoveActors() {m_pActorCollection->RemoveAllItems();};
	
	// add actor
	void AddActor(vtkActor* pActor) {m_pActorCollection->AddItem(pActor);};
	void AddActor(vtkLODActor* pLODActor) {m_pActorCollection->AddItem(pLODActor);};
	
	// get actors
	vtkActorCollection* GetActorCollection() const {return m_pActorCollection;};

	// intitialize, create, update, clip
	virtual void Initialize() {};
	virtual void Create() {};
	virtual void Update() {};
	virtual void Clip() {};

	// dialogs
	virtual BOOL DoSheetAndPagesForCreate() {return FALSE;};
	virtual BOOL DoSheetAndPagesForChange() {return FALSE;};

	// serialize
	virtual void Serialize(CArchive& ar);

// protected attributes
protected:
	BOOL m_bVisible;

// private attributes
private:
	CString m_sDescription;
	vtkActorCollection* m_pActorCollection;
};

#endif // !defined(AFX_VISUALIZATIONOBJECT_H__84AAFDA5_5D3D_11D4_B2AC_0060084B410C__INCLUDED_)
