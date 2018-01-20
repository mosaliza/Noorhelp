
// HelpViewerDoc.h : interface of the CHelpViewerDoc class
//


#pragma once
class CHelpViewerView;

class CHelpViewerDoc : public CDocument
{
protected: // create from serialization only
	CHelpViewerDoc();
	DECLARE_DYNCREATE(CHelpViewerDoc)

// Attributes
public:
	CHelpViewerView* m_pHtmlView;


// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CHelpViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


