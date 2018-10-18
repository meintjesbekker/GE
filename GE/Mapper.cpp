/*--------------------------------------------------------------------------*/
/*								Mapper.cpp   								*/
/*                            												*/
/*	Purpose	: Create mapper.                                            	*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 4.5.8 "Mapper".                               */
/*--------------------------------------------------------------------------*/
#include "stdafx.h"
#include "GE.h"
#include "Mapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*--------------------------------------------------------------------------*/
/* Construction            													*/
/*--------------------------------------------------------------------------*/
CMapper::CMapper(CModel* pcModel /* = NULL */) 
	: CActor(pcModel)
{
	// vtk
	m_pcDataSetMapper = NULL;
	m_pcPolyDataMapper = NULL;
}

/*--------------------------------------------------------------------------*/
/* Destruction             													*/
/*--------------------------------------------------------------------------*/
CMapper::~CMapper()
{
	if (m_pcDataSetMapper)
		m_pcDataSetMapper->Delete();
	if (m_pcPolyDataMapper)
		m_pcPolyDataMapper->Delete();
}

/*--------------------------------------------------------------------------*/
/* CreateMapper            													*/
/*--------------------------------------------------------------------------*/
void CMapper::CreateMapper(vtkPolyData* pcPolyData, 
						   vtkLookupTable* pcLookupTable /* = NULL */,
						   float fMinimum /* = 0 */, 
						   float fMaximum /* = 0 */)
{
	if (m_pcPolyDataMapper) 
		m_pcPolyDataMapper->Delete();
	m_pcPolyDataMapper = vtkPolyDataMapper::New();
	m_pcPolyDataMapper->SetInput(pcPolyData);
	if (pcLookupTable)
	{
		m_pcPolyDataMapper->SetScalarModeToUsePointData();
		m_pcPolyDataMapper->SetLookupTable(pcLookupTable);
		m_pcPolyDataMapper->SetScalarRange(fMinimum, fMaximum);
	}
	m_pcPolyDataMapper->Update();
}

/*--------------------------------------------------------------------------*/
/* CreateDataSetMapper     													*/
/*--------------------------------------------------------------------------*/
void CMapper::CreateDataSetMapper(	vtkDataSet* pcDataSet, 
									vtkLookupTable* pcLookupTable /* = NULL */, 
									float fMinimum  /* = 0 */, 
									float fMaximum  /* = 0 */)
{
	if (m_pcDataSetMapper) 
		m_pcDataSetMapper->Delete();
	m_pcDataSetMapper = vtkDataSetMapper::New();
	m_pcDataSetMapper->SetInput(pcDataSet);
	if (pcLookupTable)
	{
		m_pcDataSetMapper->SetScalarModeToUsePointData();
		m_pcDataSetMapper->SetLookupTable(pcLookupTable);
		m_pcDataSetMapper->SetScalarRange(fMinimum, fMaximum);
	}
	m_pcDataSetMapper->Update();
}