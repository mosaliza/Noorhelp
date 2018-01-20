
// HelpViewerView.h : interface of the CHelpViewerView class
//


#pragma once


class CHelpViewerView : public CHtmlView
{
protected: // create from serialization only
	CHelpViewerView();
	DECLARE_DYNCREATE(CHelpViewerView)

// Attributes
public:
	CHelpViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHelpViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnWebBrowser(UINT id);
	DECLARE_MESSAGE_MAP()
public:

	virtual void OnTitleChange(LPCTSTR lpszText);
};

#ifndef _DEBUG  // debug version in HelpViewerView.cpp
inline CHelpViewerDoc* CHelpViewerView::GetDocument() const
   { return reinterpret_cast<CHelpViewerDoc*>(m_pDocument); }
#endif

