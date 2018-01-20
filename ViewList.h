#pragma once


// CViewList
#include "XMLManager.h"
#include <wctype.h>

class CViewList : public CListBox
{
	DECLARE_DYNAMIC(CViewList)
private:

public:
	CViewList();
	virtual ~CViewList();
	bool LoadMyXML( const CString& a_strFile );
	void LoadList (CCXmlNode* a_pNode);
	void LoadItem( CCXmlNode* a_pNode );
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchange();
};


