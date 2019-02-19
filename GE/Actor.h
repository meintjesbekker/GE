/*--------------------------------------------------------------------------*/
/*								Actor.h   									*/
/*                            												*/
/*	Purpose	: Create an actor.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.6 "Actor".                   				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_ACTOR_H__BD72A481_798C_11D4_B2EF_0060084B410C__INCLUDED_)
#define AFX_ACTOR_H__BD72A481_798C_11D4_B2EF_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Model.h"
#endif // _MSC_VER > 1000

class CActor  
{
// public operations
public:
	CActor(CModel* pcModel = NULL);
	virtual ~CActor();
	vtkActor* GetActor() const {return m_pcActor;};
	vtkLODActor* GetLODActor() const {return m_pcLODActor;};
	vtkActor2D* GetActor2D() const { return m_pcActor2D; };

// protected operations
protected:
	virtual void CreateActor(vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor = -1);
	virtual void UpdateActor(BOOL bVisible, COLORREF cColor);
	virtual void CreateLODActor(vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor = -1);
	virtual void UpdateLODActor(BOOL bVisible, COLORREF cColor);
	virtual void CreateScalarBarActor(vtkMapper* pcMapper);

// private operations
private:
	void SetActorProperties(vtkActor* pcActor, vtkMapper* pcMapper, BOOL bVisible, float fOpacity, COLORREF cColor);
	virtual void UpdateActor(vtkActor* pcActor, BOOL bVisible, COLORREF cColor);

// protected attributes
protected:
	// vtk 
	vtkActor* m_pcActor;
	vtkLODActor* m_pcLODActor;
	vtkScalarBarActor* m_pcActor2D;

	// pointer to model object
	CModel*	m_pcModel;
};

#endif // !defined(AFX_ACTOR_H__BD72A481_798C_11D4_B2EF_0060084B410C__INCLUDED_)