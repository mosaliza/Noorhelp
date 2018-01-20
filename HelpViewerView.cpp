
// HelpViewerView.cpp : implementation of the CHelpViewerView class
//

#include "stdafx.h"
#include "HelpViewer.h"

#include "HelpViewerDoc.h"
#include "HelpViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelpViewerView

IMPLEMENT_DYNCREATE(CHelpViewerView, CHtmlView)

BEGIN_MESSAGE_MAP(CHelpViewerView, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
	ON_COMMAND_RANGE(ID_WEBBROWSER_BACK,ID_WEBBROWSER_HOME,OnWebBrowser)
END_MESSAGE_MAP()

// CHelpViewerView construction/destruction

CHelpViewerView::CHelpViewerView()
{
	// TODO: add construction code here

}

CHelpViewerView::~CHelpViewerView()
{
}

BOOL CHelpViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CHelpViewerView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("file://H:/Test/1.htm"),NULL,NULL);
	
}


// CHelpViewerView printing


void CHelpViewerView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}


void CHelpViewerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHelpViewerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CHelpViewerView diagnostics

#ifdef _DEBUG
void CHelpViewerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHelpViewerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHelpViewerDoc* CHelpViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelpViewerDoc)));
	return (CHelpViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelpViewerView message handlers



void CHelpViewerView::OnTitleChange(LPCTSTR lpszText)
{
	// TODO: Add your specialized code here and/or call the base class
	AfxGetMainWnd ()->SetWindowText (lpszText);
	CHtmlView::OnTitleChange(lpszText);
	

}

void CHelpViewerView::OnWebBrowser(UINT id)
{
	switch(id)
	{
	
	case ID_WEBBROWSER_BACK:
	GoBack();
	break;
	case ID_WEBBROWSER_FORWARD:
	GoForward();
	break;
	case ID_WEBBROWSER_HOME:
	GoHome();
	break;
	default:
	GoHome();
	break;
	}

}