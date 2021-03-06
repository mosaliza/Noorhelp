
#include "stdafx.h"
#include "mainfrm.h"
#include "IndexView.h"
#include "Resource.h"
#include "HelpViewer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CIndexView::CIndexView()
{
}

CIndexView::~CIndexView()
{
}

BEGIN_MESSAGE_MAP(CIndexView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//ON_WM_CONTEXTMENU()
// 	ON_COMMAND(ID_PROPERTIES, OnProperties)
// 	ON_COMMAND(ID_OPEN, OnFileOpen)
// 	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
// 	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
// 	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
// 	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
// 	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CIndexView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
 	
	//Create ListBox View
  	const DWORD dwListBoxStyle=WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|LBS_HASSTRINGS|LBS_NOTIFY;
   	if(! m_ListBox.Create(dwListBoxStyle,rectDummy,this,5))
  	{
  		TRACE0("Failed to create ListBox");
  		return -1;//Fail to Create
  	}
	
 
//   	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_LINESATROOT ;
//    
//    	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
//    	{
//    		TRACE0("Failed to create file view\n");
//    		return -1;      // fail to create
//    	}

	// Load view images:
//	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
//  m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

// 	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
// 	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);
// 
// 	OnChangeVisualStyle();
// 
// 	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
// 
// 	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
// 
// 	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	//m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	FillFileView();
	AdjustLayout();


	return 0;
}

void CIndexView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

 void CIndexView::FillFileView()
 {	
	 m_ListBox.LoadMyXML(_T("Index.xml"));

	// m_wndFileView.LoadFromXML(_T("Index.xml"));
 //	/*HTREEITEM hRoot = m_wndFileView.InsertItem(_T("FakeApp files"), 0, 0);
 //	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
 //
 //	HTREEITEM hSrc = m_wndFileView.InsertItem(_T("FakeApp Source Files"), 0, 0, hRoot);
 //
 //	m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
 //	m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
 //	m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
 //	m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
 //	m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
 //	m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);
 //
 //	HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp Header Files"), 0, 0, hRoot);
 //
 //	m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
 //	m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
 //	m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
 //	m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
 //	m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
 //	m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);
 //
 //	HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp Resource Files"), 0, 0, hRoot);
 //
 //	m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
 //	m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
 //	m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
 //	m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);
 //
 //	m_wndFileView.Expand(hRoot, TVE_EXPAND);
 //	m_wndFileView.Expand(hSrc, TVE_EXPAND);
 //	m_wndFileView.Expand(hInc, TVE_EXPAND);*/
 }

// void CIndexView::OnContextMenu(CWnd* pWnd, CPoint point)
// {
// 	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
// 	ASSERT_VALID(pWndTree);
// 
// 	if (pWnd != pWndTree)
// 	{
// 		CDockablePane::OnContextMenu(pWnd, point);
// 		return;
// 	}
// 
// 	if (point != CPoint(-1, -1))
// 	{
// 		// Select clicked item:
// 		CPoint ptTree = point;
// 		pWndTree->ScreenToClient(&ptTree);
// 
// 		UINT flags = 0;
// 		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
// 		if (hTreeItem != NULL)
// 		{
// 			pWndTree->SelectItem(hTreeItem);
// 		}
// 	}
// 
// 	pWndTree->SetFocus();
// 	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
// }

void CIndexView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndFileView.SetWindowPos(NULL,rectClient.left , rectClient.top /*+ cyTlb*/, rectClient.Width() , rectClient.Height() /*- cyTlb*/ , SWP_NOACTIVATE | SWP_NOZORDER);
	m_ListBox.SetWindowPos(NULL, rectClient.left , rectClient.top /*+ cyTlb*/ , rectClient.Width(), rectClient.Height()/* - cyTlb*/ , SWP_NOACTIVATE | SWP_NOZORDER);
}

//void CIndexView::OnProperties()
//{
//	AfxMessageBox(_T("Properties...."));
//
//}
//
//void CIndexView::OnFileOpen()
//{
//	// TODO: Add your command handler code here
//}
//
//void CIndexView::OnFileOpenWith()
//{
//	// TODO: Add your command handler code here
//}
//
//void CIndexView::OnDummyCompile()
//{
//	// TODO: Add your command handler code here
//}
//
//void CIndexView::OnEditCut()
//{
//	// TODO: Add your command handler code here
//}
//
//void CIndexView::OnEditCopy()
//{
//	// TODO: Add your command handler code here
//}
//
//void CIndexView::OnEditClear()
//{
//	// TODO: Add your command handler code here
//}

// void CIndexView::OnPaint()
// {
// 	CPaintDC dc(this); // device context for painting
// 
// 	CRect rectTree;
// 	//m_wndFileView.GetWindowRect(rectTree);
// 	m_wndFileView.GetWindowRect(rectTree);
// 	ScreenToClient(rectTree);
// 
// 	rectTree.InflateRect(1, 1);
// 	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
// }

void CIndexView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	//m_wndFileView.SetFocus();
	m_ListBox.SetFocus();
}

void CIndexView::OnChangeVisualStyle()
{
// 	m_wndToolBar.CleanUpLockedImages();
// 	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	//m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

// 	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
// 	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	//m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}


