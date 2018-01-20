
#include "stdafx.h"
#include "ViewTree.h"
#include "HelpViewerDoc.h"
#include "MainFrm.h"
#include "HelpViewer.h"
#include "HelpViewerView.h"
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

bool CViewTree::LoadFromXML( const CString& a_strFile )
{
	TiXmlNode* pXML = NULL;
	TiXmlDocument xmlDoc;

	TCHAR szBuf[ _MAX_PATH + 1 ];
	CString strTemp = a_strFile;

	_tgetcwd( szBuf, _countof( szBuf ) );
	_tcscat( szBuf, _T("\\") );
	_tcscat( szBuf, strTemp.GetBuffer( 1 ) );

	if( xmlDoc.LoadFile( szBuf ) )
	{
		// XML root
		pXML = xmlDoc.FirstChild( _T("XML") );

		if( NULL == pXML )
			return false;

		// Load our tree control
		Load( pXML );

		// Expand all entries
		Expand( GetRootItem(), TVE_EXPAND );

		return true;
	}

	return false;
}


bool CViewTree::SaveToXML( const CString& a_strFile )
{
	// Save XML
	TiXmlNode* pXML = NULL;
	TiXmlDocument xmlDoc;

	// XML header
	xmlDoc.InsertEndChild( TiXmlDeclaration( _T("1.0"), _T("UTF-8"), _T("yes") ) );

	// XML root
	pXML = xmlDoc.InsertEndChild( TiXmlElement( _T("XML") ) );

	// Save our tree control
	Save( pXML );

	// Save XML
	CString strFile = a_strFile;

	return xmlDoc.SaveFile( CString(strFile.GetBuffer( 1 )) );
}

void CViewTree::Load( TiXmlNode* a_pNode )
{
	ASSERT( NULL != a_pNode );

	// Get node "Items"
	TiXmlNode* pItems = a_pNode->FirstChild( _T("Items") );
	TiXmlNode* pItem = NULL;
	
	if( NULL == pItems )
		return;

	// Get first item
	pItem = pItems->FirstChild( _T("Item") );
	
	// Iterate all siblings
	while( NULL != pItem )
	{
		LoadItem( pItem, NULL );
		pItem = pItem->NextSibling( _T("Item") );
	}
}

void CViewTree::Save( TiXmlNode* a_pNode )
{
	ASSERT( NULL != a_pNode );

	TiXmlNode* pItems = a_pNode->InsertEndChild( TiXmlElement( _T("Items") ) );
	TiXmlNode* pParent = pItems;
	TiXmlNode* pNewNode = NULL;
	HTREEITEM hItem = GetRootItem();
	int iIndent = 0; int iLastIndent = 0;

	while( hItem )
	{
		iIndent = GetIndentLevel( hItem );

		int iDiff = iIndent - iLastIndent;
		if( iDiff > 0 )
		{
			ASSERT( NULL != pNewNode );

			while( iDiff-- )
				pNewNode = pNewNode->InsertEndChild( TiXmlElement( _T("Item") ) );

			ASSERT( NULL != pNewNode );
			pParent = pNewNode->Parent();
		}
		else if( iDiff < 0 )
		{
			iDiff--;					// Correct difference to get the right parent
			pParent = pNewNode;

			while( iDiff++ < 0 )
				pParent = pParent->Parent();

			ASSERT( NULL != pParent );
			pNewNode = pParent->InsertEndChild( TiXmlElement(_T("Item") ) );
		}
		else 
		{
			ASSERT( NULL != pParent );
			pNewNode = pParent->InsertEndChild( TiXmlElement( _T("Item") ) );
		}

		iLastIndent = iIndent;			

		// Save current item
		TiXmlElement* pElement = pNewNode->ToElement();
		ASSERT( NULL != pElement );

		pElement->SetValue( _T("Item") );
		pElement->SetAttribute( _T("Title"), GetItemText( hItem ) );

		// The next item, please ...
		hItem = GetNextItem( hItem );
	}
}

void CViewTree::LoadItem( TiXmlNode* a_pNode, HTREEITEM a_hTreeParent )
{
	ASSERT( NULL != a_pNode );

	TiXmlElement* pEl = a_pNode->ToElement();
	ASSERT( NULL != pEl );

	HTREEITEM hItem = NULL;

	TiXmlNode* pChild = NULL;
	TVINSERTSTRUCT lpInsertStruct;
	if( NULL == a_hTreeParent )
	{	
		lpInsertStruct.hParent=TVI_ROOT;
		lpInsertStruct.hInsertAfter=TVI_LAST;
		lpInsertStruct.item.pszText=(LPTSTR)(pEl->Attribute(_T("Title")));
		lpInsertStruct.item.lParam=_tstoi(CString(pEl->Attribute(_T("ID"))));
		lpInsertStruct.item.mask=TVIF_PARAM|TVIF_TEXT;
		hItem=InsertItem(&lpInsertStruct);
		//hItem = InsertItem( pEl->Attribute( _T("ID") ), TVI_ROOT );
		//hItem = InsertItem( pEl->Attribute( _T("Title") ), TVI_ROOT );

	}
	else
	{	
		lpInsertStruct.hParent=a_hTreeParent;
		lpInsertStruct.hInsertAfter=TVI_LAST;
		lpInsertStruct.item.pszText=(LPTSTR)pEl->Attribute(_T("Title"));
		lpInsertStruct.item.lParam=_tstoi(CString(pEl->Attribute(_T("ID"))));
		lpInsertStruct.item.mask=TVIF_PARAM|TVIF_TEXT;
		hItem=InsertItem(&lpInsertStruct);
		//hItem = InsertItem( pEl->Attribute( _T("ID") ), a_hTreeParent );
		//hItem = InsertItem( pEl->Attribute( _T("Title") ), a_hTreeParent );
	}	
	
	
	pChild = a_pNode->IterateChildren( _T("Item"), NULL );

	while( pChild )
	{
		LoadItem( pChild, hItem );
		pChild = a_pNode->IterateChildren(_T("Item"), pChild );
	}
}


int CViewTree::GetIndentLevel( HTREEITEM hItem )
{
	int iIndent = 0;

	while( (hItem = GetParentItem( hItem )) != NULL )
		iIndent++;

	return iIndent;
}

HTREEITEM CViewTree::GetNextItem( HTREEITEM hItem )
{
	HTREEITEM hItemRet = NULL;

	if( false == ItemHasChildren( hItem ) )
	{
		while( ( hItemRet = GetNextSiblingItem( hItem ) ) == NULL )
		{
			if( ( hItem = GetParentItem( hItem ) ) == NULL )
				return NULL;
		}
	}
	else
	{
		return GetChildItem( hItem );
	}

	return hItemRet;
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)

	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CViewTree::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CViewTree::OnNMRClick)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree message handlers

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	HTREEITEM hmyItem = GetSelectedItem();
	TVITEM TreeItem;
	TreeItem.hItem = hmyItem;
	TreeItem.mask = TVIF_PARAM | TVIF_HANDLE;
	BOOL x = GetItem(&TreeItem);
	UINT nID=(UINT)(TreeItem.lParam);


	CMDIFrameWnd* pMain = (CMDIFrameWnd*)theApp.m_pMainWnd;
	if(!pMain) return;
	//CHelpViewerDoc* pDoc = (CHelpViewerDoc*) pMain->GetActiveView()
	CFrameWnd* pFrame = pMain->GetActiveFrame();
	if(!pFrame) return;
	CHelpViewerView* pView = (CHelpViewerView*)pFrame->GetActiveView();
	if(!pView) return;
	pView->Refresh();
	TCHAR buf[100];
	_stprintf(buf,_T("file://H:/Test/%d.htm"),nID);
	pView->Navigate(buf,NULL,NULL);
	
	//CHelpViewerDoc* pDoc = (CHelpViewerDoc*) pView->GetDocument();
	//ASSERT(pDoc);
	//if(pDoc->m_pHtmlView) return;
	//pDoc->m_pHtmlView->Refresh();
	*pResult = 0;
}



void CViewTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CViewTree::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CViewTree::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CTreeCtrl::OnRButtonUp(nFlags, point);
}
