/*--------------------------------------------------------------------------*/
/*								ObjectList.h   								*/
/*                            												*/
/*	Purpose	: Element of visualization object list.							*/
/*	Author	: Meintjes Bekker                                  				*/
/*	Date	: Copyright (C) 2000                               				*/
/*	Project	: Groundwater Explorer                             				*/
/*	Version	: 1					                             				*/
/*	Notes	: Thesis, section 5.9 "Summary".                  				*/
/*--------------------------------------------------------------------------*/
#if !defined(AFX_OBJECTLIST_H__9104ED92_38FE_11D3_B80E_0060084B410C__INCLUDED_)
#define AFX_OBJECTLIST_H__9104ED92_38FE_11D3_B80E_0060084B410C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObjectList  
{
// public operations
public:
	CObjectList(BOOL bVisible, int iIndex);
	virtual ~CObjectList();
	BOOL GetVisibility() const {return m_bVisible;};
	void SetVisibility(BOOL bVisibility) {m_bVisible = bVisibility;};
	int	GetIndex() const {return m_iIndex;};
	void SetIndex(int iIndex) {m_iIndex = iIndex;};

// private attributes
private:
	BOOL m_bVisible;
	int m_iIndex;
};

#endif // !defined(AFX_OBJECTLIST_H__9104ED92_38FE_11D3_B80E_0060084B410C__INCLUDED_)
