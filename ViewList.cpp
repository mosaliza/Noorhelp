// ViewList.cpp : implementation file
//

#include "stdafx.h"
#include "HelpViewer.h"
#include "ViewList.h"
#include "HelpViewerDoc.h"
#include "MainFrm.h"
#include "HelpViewerView.h"


// CViewList

IMPLEMENT_DYNAMIC(CViewList, CListBox)
CViewList::CViewList()
{

}

CViewList::~CViewList()
{
}
bool CViewList::LoadMyXML( const CString& a_strFile )
{
	
	CCXmlNode*pXML;
	//CCXmlNodeList *pXmlNodeList;
	//CCXmlNodeList XmlNodeList;
	CCXmlDocument *pXmlDoc;
	TCHAR szBuf[ _MAX_PATH + 1 ];
	CString strTemp = a_strFile;
	_tgetcwd( szBuf, _countof( szBuf ) );
	_tcscat( szBuf, _T("\\") );
	_tcscat( szBuf, strTemp.GetBuffer( 1 ) );
	
	pXmlDoc = new CCXmlDocument();
	if(pXmlDoc->Load(szBuf))
	{	
		//XML Root
		pXML=new CCXmlNode(pXmlDoc->AsNode());
		if(pXML==NULL)
			return false;
		//Load our Index List
		LoadList(pXML);
		
		return true;

	}
	
	return false;	
	
}
void CViewList::LoadList(CCXmlNode* a_pNode)
{
	CCXmlNodeList XmlNodeList;
	ASSERT( NULL != a_pNode );

	// Get node "Items"
	CCXmlNode* pItems=new CCXmlNode(a_pNode->GetNode(0));
	if(pItems==NULL)return;
	//Here we could reach the Items Node
	//_bstr_t str=pItems->GetAttribName(0);
	
	// Get first item
	XmlNodeList=pItems->FindNodes(_T("Item"));
	int nCount=XmlNodeList.Count();
	for(int i=0;i<nCount;i++)
	{
		CCXmlNode* pItem=new CCXmlNode(XmlNodeList.Node(i));
		
		
		_bstr_t strVal=pItem->GetValue(_T("Title"));//Title Attribute
		_bstr_t strID=(pItem->GetValue(_T("ID")));//ID Attribute
		BSTR& bstrX = strID.GetBSTR();
		int nID = _wtoi(bstrX);
		AddString(strVal);
		int nLastItem=GetCount()-1;
		SetItemData(nLastItem,nID);//Associate data with every Index in the Index list
		LoadItem(pItem);
		delete pItem;
	
	}

}
void CViewList::LoadItem( CCXmlNode* a_pNode )
{
	CCXmlNodeList XmlNodeList;
	XmlNodeList=a_pNode->FindNodes(_T("Item"));
	int nCount=XmlNodeList.Count();
	for(int j=0;j<nCount;j++)
	{
		CCXmlNode* pItem=new CCXmlNode(XmlNodeList.Node(j));
		_bstr_t strVal=pItem->GetValue(_T("Title"));//Title Attribute
		BSTR& bstrVaL=strVal.GetBSTR();
		
		_bstr_t strID=(pItem->GetValue(_T("ID")));//ID Attribute
		BSTR& bstrX = strID.GetBSTR();
		int nID = _wtoi(bstrX);
		AddString( CString("   ") + bstrVaL);
		int nLastItem=GetCount()-1;
		SetItemData(nLastItem,nID);//Associate data with every Index in the Index list
		
	}


}

BEGIN_MESSAGE_MAP(CViewList, CListBox)
	ON_CONTROL_REFLECT(LBN_SELCHANGE, &CViewList::OnLbnSelchange)

END_MESSAGE_MAP()



// CViewList message handlers



void CViewList::OnLbnSelchange()
{
	// TODO: Add your control notification handler code here
	
	int nIndex=GetCurSel();
	int nID=GetItemData(nIndex);
	CMDIFrameWnd* pMain = (CMDIFrameWnd*)theApp.m_pMainWnd;
	if(!pMain) return;
	//CHelpViewerDoc* pDoc = (CHelpViewerDoc*) pMain->GetActiveView()
	CFrameWnd* pFrame = pMain->GetActiveFrame();
	if(!pFrame) return;
	CHelpViewerView* pView = (CHelpViewerView*)pFrame->GetActiveView();
	if(!pView) return;
	pView->Refresh();
	TCHAR buf[100]={0};
	_stprintf(buf,_T("file://H:/Test/%d.htm"),nID);
	pView->Navigate(buf,NULL,NULL);

	//CHelpViewerDoc* pDoc = (CHelpViewerDoc*) pView->GetDocument();
	//ASSERT(pDoc);
	//if(pDoc->m_pHtmlView) return;
	//pDoc->m_pHtmlView->Refresh();
}

