
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "IndexView.h"
#include "ContentsView.h"
#include "SearchTask.h"
#include "OutputWnd.h"
class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CIndexView         m_wndIndexView;
	CContentsView     m_wndContentsView;
	CSearchTask       m_wndSearchTask;
	COutputWnd			m_wndOutput;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnLanguage(UINT id);
	afx_msg void OnUpdateLanguage(CCmdUI* pCmdUI);
	
	DECLARE_MESSAGE_MAP()
public:
	void SetLanguage(UINT id, BOOL bSaveInReg = TRUE, BOOL bForceSet = FALSE, BOOL bLoadAccelTable = TRUE);
	void ChangeMyTexts(void);
private:
	void SetLanguage_(int nLanguage, BOOL bLoadAccelTable = TRUE);
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


