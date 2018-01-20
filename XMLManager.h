//------------------------------------------------------------------//
//      File:  XMLManager.h                                         //
//   Classes:  XMLManager                                           //
//             the class for processing an xml documetnt            //
//                                                                  //
//   Copyright CRCIS,  1368-1385,  Qom,  Iran                       //
//------------------------------------------------------------------//

#pragma once

#define XMLNODE MSXML2::IXMLDOMNode
#define XMLNODEPTR MSXML2::IXMLDOMNodePtr
#define XMLNODELIST MSXML2::IXMLDOMNodeList
#define XMLNODELISTPTR MSXML2::IXMLDOMNodeListPtr
#define XMLDOCUMENT MSXML2::IXMLDOMDocument2
#define XMLDOCUMENTPTR MSXML2::IXMLDOMDocument2Ptr
#define CLSIDXMLDOCUMENT MSXML2::CLSID_DOMDocument
#define XMLATTRPTR MSXML2::IXMLDOMAttributePtr
#define XMLNODEMAPPTR MSXML2::IXMLDOMNamedNodeMapPtr
#define XMLNODETYPE MSXML2::DOMNodeType
#define XMLPARSERROR MSXML2::IXMLDOMParseError
#define XMLNODEELEMENTTYPE MSXML2::NODE_ELEMENT

#define CHECKHR( x ) { hr = x; if ( FAILED( hr ) ) goto CleanUp; }

class CCXmlNode  
{
public:
	bstr_t NodeType();
	bstr_t GetAttribVal( int index );
	bstr_t GetAttribName( int index );
	int NumAttributes();
	void ReplaceNode( XMLNODE *pOldNode, XMLNODE *pNewNode );
	bstr_t GetText();
	void SetText( LPCTSTR text );
	XMLNODE *InsertAfter( XMLNODE *refNode,  XMLNODE *pNode );
	bstr_t Name();
	XMLNODELIST *FindNodes( LPCTSTR searchStr );
	XMLNODE *Parent();
	void RemoveNodes( LPCTSTR searchStr );
	XMLNODE *InsertAfter( XMLNODE *refNode,  LPCTSTR nodeName );
	XMLNODE *InsertBefore( XMLNODE *refNode,  LPCTSTR nodeName );
	XMLNODE *Interface();
	XMLDOCUMENT *ParentDocument();
	bstr_t GetXML();
	XMLNODE *RemoveNode( XMLNODEPTR pNode );
	XMLNODE *InsertNode( int index, LPCTSTR nodeName );
	XMLNODE *InsertNode( int index, XMLNODEPTR pNode );
	long NumNodes();
	XMLNODE *Detach();
	XMLNODE *GetNode( LPCTSTR nodeName );
	XMLNODE *GetNode( int nodeIndex );
	XMLNODE *FindNode( LPCTSTR searchString );
	XMLNODE *GetPrevSibling();
	XMLNODE *GetNextSibling();
	void SetValue( LPCTSTR valueName, LPCTSTR value );
	void SetValue( LPCTSTR valueName, int value );
	void SetValue( LPCTSTR valueName, short value );
	void SetValue( LPCTSTR valueName, double value );
	void SetValue( LPCTSTR valueName, float value );
	void SetValue( LPCTSTR valueName, bool value );
	BOOL IsValid();
	bstr_t GetValue( LPCTSTR valueName );

	CCXmlNode();
	CCXmlNode( XMLNODEPTR pNode, BOOL bAutoRelease = TRUE );
	void operator=( XMLNODEPTR pNode );
	virtual ~CCXmlNode();

private:
	BOOL bAutoRelease;
	XMLNODEPTR pocNode;
};


class CCXmlDocument
{
public:
	bstr_t GetUrl();
	bstr_t GetXML();
	BOOL IsValid();
	BOOL Load( LPCTSTR path );
	BOOL LoadXML( LPCTSTR xml );
	HRESULT ReportError( XMLPARSERROR *pocXMLError );
	BOOL Save( LPCTSTR path = _T( "" ) );
	XMLDOCUMENT *Detach();
	XMLDOCUMENT *Clone();
	CCXmlDocument( LPCTSTR Property = NULL );
	CCXmlDocument( XMLDOCUMENTPTR pDoc );
	XMLNODE *AsNode();
	XMLNODE *GetRoot();
	virtual ~CCXmlDocument();

private:
	XMLDOCUMENTPTR pocXMLDoc;
};


class CCXmlNodeList
{
public:
	XMLDOCUMENT *AsDocument();
	XMLNODE *Node( int index );
	void Start();
	XMLNODE *Next();
	BOOL IsValid();
	int Count();
	CCXmlNodeList();
	CCXmlNodeList( XMLNODELISTPTR pList );
	void operator=( XMLNODELISTPTR pList );
	virtual ~CCXmlNodeList();

private:
	XMLNODELISTPTR pocNodelist;
};
