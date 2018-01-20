
#pragma once
/////////////////////////////////////////////////////////////////////////////
// CViewTree window
#include"tinyxml.h"

class CViewTree : public CTreeCtrl
{
// Construction
public:
	CViewTree();
//Attributes
public:

// Overrides
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	virtual ~CViewTree();
public:

	bool LoadFromXML( const CString& a_strFile );

	bool SaveToXML( const CString& a_strFile );

public:

	void Load( TiXmlNode* a_pNode );

	void Save( TiXmlNode* a_pNode );

protected:

	void LoadItem( TiXmlNode* a_pNode, HTREEITEM a_hTreeParent );
	int GetIndentLevel( HTREEITEM hItem );

	HTREEITEM GetNextItem( HTREEITEM hItem );


protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
