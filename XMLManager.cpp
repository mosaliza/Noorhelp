//------------------------------------------------------------------//
//      File:  XMLManager.cpp                                       //
//   Classes:  XMLManager                                           //
//             the class for processing an xml documetnt            //
//                                                                  //
//   Copyright CRCIS, 1368-1385, Qom, Iran                          //
//------------------------------------------------------------------//

#include <Stdafx.h>

#include "XMLManager.h"


CCXmlNode::CCXmlNode()
{
}


CCXmlNode::CCXmlNode( XMLNODEPTR pNode, BOOL bAutoRelease )
{
	pocNode = pNode;
	bAutoRelease = bAutoRelease;
}


void CCXmlNode::operator=( XMLNODEPTR pNode )
{
	if ( IsValid() )
		pocNode -> Release();
	pocNode = pNode;
}


CCXmlNode::~CCXmlNode()
{
	if ( !bAutoRelease )
		pocNode.Detach();
}


bstr_t CCXmlNode::GetValue( LPCTSTR valueName )
{
	XMLNODEPTR pocAttribute;

	if ( !IsValid() )
		return "";

	pocAttribute = pocNode -> Getattributes() -> getNamedItem( valueName );

	if ( pocAttribute )
		return pocAttribute -> Gettext();
	return "";
}


BOOL CCXmlNode::IsValid()
{
	if ( pocNode  ==  NULL )
		return FALSE;

	if ( pocNode.GetInterfacePtr()  ==  NULL )
		return FALSE;

	return TRUE;
}


XMLNODE *CCXmlNode::GetPrevSibling()
{
	if ( !IsValid() )
		return NULL;
	return pocNode -> GetpreviousSibling().Detach();
}


XMLNODE *CCXmlNode::GetNextSibling()
{
	if ( !IsValid() )
		return NULL;

	return pocNode -> GetnextSibling().Detach();
}


XMLNODE *CCXmlNode::GetNode( LPCTSTR nodeName )
{
	if ( !IsValid() )
		return NULL;

	try
	{
		return pocNode -> selectSingleNode( nodeName ).Detach();
	}
	catch ( _com_error e )
	{
		CString err = e.ErrorMessage();
	}
	return NULL;
}


XMLNODE *CCXmlNode::GetNode( int nodeIndex )
{
	if ( !IsValid() )
		return NULL;
	return pocNode -> GetchildNodes() -> Getitem( nodeIndex ).Detach();
}


XMLNODE *CCXmlNode::FindNode( LPCTSTR searchString )
{
	if ( !IsValid() )
		return NULL;
	try
	{
		return pocNode -> selectSingleNode( searchString ).Detach();
	}
	catch ( _com_error e )
	{
		CString err = e.ErrorMessage();
	}
	return NULL;
}


XMLNODE *CCXmlNode::Detach()
{
	if ( IsValid() )
	{
		return pocNode.Detach();
	}
	else
		return NULL;
}


long CCXmlNode::NumNodes()
{
	if ( IsValid() )
	{
		return pocNode -> GetchildNodes() -> Getlength();
	}
	else
		return 0;
}


void CCXmlNode::SetValue( LPCTSTR valueName, LPCTSTR value )
{
	XMLDOCUMENTPTR pocXMLDocument;
	XMLNODEMAPPTR pocAttributes;
	XMLATTRPTR pocAttribute;

	pocXMLDocument = pocNode -> GetownerDocument();
	if ( pocXMLDocument )
	{
		pocAttributes = pocNode -> Getattributes();
		if ( pocAttributes )
		{
			pocAttribute = pocXMLDocument -> createAttribute( valueName );
			if ( pocAttribute )
			{
				pocAttribute -> Puttext( value );
				pocAttributes -> setNamedItem( pocAttribute );
			}
		}
	}
}


void CCXmlNode::SetValue( LPCTSTR valueName, int value )
{
	CString str;

	str.Format( _T( "%ld" ), value );
	SetValue( valueName, str );
}


void CCXmlNode::SetValue( LPCTSTR valueName, short value )
{
	CString str;

	str.Format( _T( "%hd" ), value );
	SetValue( valueName, str );
}


void CCXmlNode::SetValue( LPCTSTR valueName, double value )
{
	CString str;

	str.Format( _T( "%f" ), value );
	SetValue( valueName, str );
}


void CCXmlNode::SetValue( LPCTSTR valueName, float value )
{
	CString str;

	str.Format( _T( "%f" ), value );
	SetValue( valueName, str );
}


void CCXmlNode::SetValue( LPCTSTR valueName, bool value )
{
	CString str;

	if ( value )
		str = _T( "True" );
	else
		str = _T( "False" );

	SetValue( valueName, str );
}


XMLNODE *CCXmlNode::InsertNode( int index, LPCTSTR nodeName )
{
	XMLDOCUMENTPTR pocXMLDocument;
	XMLNODEPTR pocNewNode;
	XMLNODE *pocRefNode;

	pocXMLDocument = pocNode -> GetownerDocument();
	if ( pocXMLDocument )
	{
		pocNewNode = pocXMLDocument -> createNode( _variant_t( ( short )XMLNODEELEMENTTYPE ), nodeName, "" );
		pocRefNode = GetNode( index );
		if ( pocRefNode )
			pocNewNode = pocNode -> insertBefore( pocNewNode.Detach(), pocRefNode );
		else
			pocNewNode = pocNode -> appendChild( pocNewNode.Detach() );
		return pocNewNode.Detach();
	}
	return NULL;
}


XMLNODE *CCXmlNode::InsertNode( int index, XMLNODEPTR pNode )
{
	XMLNODEPTR pocNewNode;
	XMLNODE *pocRefNode;

	pocNewNode = pNode -> cloneNode( VARIANT_TRUE );
	if ( pocNewNode )
	{
		pocRefNode = GetNode( index );
		if ( pocRefNode )
			pocNewNode = pocNode -> insertBefore( pocNewNode.Detach(), pocRefNode );
		else
			pocNewNode = pocNode -> appendChild( pocNewNode.Detach() );
		return pocNewNode.Detach();
	}
	else
		return NULL;
}


bstr_t CCXmlNode::GetXML()
{
	if ( IsValid() )
		return pocNode -> Getxml();
	else
		return "";
}


XMLNODE *CCXmlNode::RemoveNode( XMLNODEPTR pNode )
{
	if ( !IsValid() )
		return NULL;

	return pocNode -> removeChild( pNode ).Detach();
}


CCXmlDocument::CCXmlDocument( LPCTSTR Property )
{
	pocXMLDoc.CreateInstance( CLSIDXMLDOCUMENT );

	//set XPath as SelectionLanguage
	pocXMLDoc -> setProperty( "SelectionLanguage", "XPath" );

	//set the namespace for XPath
	if ( Property )
		pocXMLDoc -> setProperty( "SelectionNamespaces", _bstr_t( Property ) );
}


CCXmlDocument::CCXmlDocument( XMLDOCUMENTPTR pDoc )
{
	pocXMLDoc = pDoc;
}


CCXmlDocument::~CCXmlDocument()
{
}


BOOL CCXmlDocument::IsValid()
{
	if ( pocXMLDoc  ==  NULL )
		return FALSE;
	if ( pocXMLDoc.GetInterfacePtr()  ==  NULL )
		return FALSE;

	return TRUE;
}


XMLDOCUMENT *CCXmlDocument::Detach()
{
	if ( !IsValid() )
		return NULL;

	return pocXMLDoc.Detach();
}


XMLDOCUMENT *CCXmlDocument::Clone()
{
	XMLDOCUMENTPTR pocXMLDocument;

	if ( !IsValid() )
		return NULL;

	pocXMLDocument.CreateInstance( CLSIDXMLDOCUMENT );
	_variant_t v( pocXMLDocument.GetInterfacePtr() );
	pocXMLDoc -> save( v );

	return pocXMLDocument.Detach();
}


BOOL CCXmlDocument::Load( LPCTSTR path )
{
	VARIANT_BOOL success;
	XMLPARSERROR *pocXMLError;
	LONG errorCode = E_FAIL;
	HRESULT hr;

	if ( !IsValid() )
		return FALSE;


	_variant_t v( path );
	pocXMLError = NULL;
	pocXMLDoc -> put_async( VARIANT_FALSE );
	success = pocXMLDoc -> load( v );
	if ( !success )
	{
		/*CHECKHR*/( pocXMLDoc -> get_parseError( &pocXMLError ) );
		/*CHECKHR*/( pocXMLError -> get_errorCode( &errorCode ) );
		if ( errorCode != 0 )
			hr = ReportError( pocXMLError );
	}
	pocXMLDoc  ->  setProperty( "SelectionLanguage", "XPath" ); 

	//CleanUp:
	//   SAFERELEASE( pocXMLError );
	if ( success  ==  VARIANT_TRUE )
		return TRUE;
	else
		return FALSE;
}

// Report parsing error information
HRESULT CCXmlDocument::ReportError( XMLPARSERROR *pocXMLError )
{
	WCHAR achBuf[ 100 ];
	long line,
		linePos;
	LONG errorCode;
	BSTR pBURL,
		pBReason;
	HRESULT hr;

	CHECKHR( pocXMLError -> get_line( &line ) );
	CHECKHR( pocXMLError -> get_linepos( &linePos ) );
	CHECKHR( pocXMLError -> get_errorCode( &errorCode ) );
	CHECKHR( pocXMLError -> get_url( &pBURL ) );
	CHECKHR( pocXMLError -> get_reason( &pBReason ) );

	if ( line > 0 )
	{
		wsprintf( achBuf, _T( "Error on line %d, position %d in \"%S\".\n" ), line, linePos, pBURL );
		AfxMessageBox( achBuf );
	}

CleanUp:
	SysFreeString( pBURL );
	SysFreeString( pBReason );

	return E_FAIL;
}


BOOL CCXmlDocument::LoadXML( LPCTSTR xml )
{
	if ( !IsValid() )
		return FALSE;

	VARIANT_BOOL success = pocXMLDoc -> loadXML( xml );
	if ( success  ==  VARIANT_TRUE )
		return TRUE;
	else
		return FALSE;
}


BOOL CCXmlDocument::Save( LPCTSTR path )
{
	try
	{
		if ( !IsValid() )
			return FALSE;
		CString szPath( path );
		if ( szPath  ==  "" )
		{
			_bstr_t curPath = pocXMLDoc -> Geturl();
			szPath = ( LPSTR )curPath;
		}
		_variant_t v( szPath );
		if ( FAILED( pocXMLDoc -> save( v ) ) )
			return FALSE;
		else
			return TRUE;
	}
	catch( ... )
	{
		return FALSE;
	}
}


XMLNODE *CCXmlDocument::GetRoot()
{
	return AsNode();
}


XMLNODE *CCXmlDocument::AsNode()
{
	if ( !IsValid() )
		return NULL;

	return pocXMLDoc -> GetdocumentElement().Detach();
}


bstr_t CCXmlDocument::GetXML()
{
	if ( IsValid() )
		return pocXMLDoc -> Getxml();
	else
		return "";
}


bstr_t CCXmlDocument::GetUrl()
{
	return pocXMLDoc -> Geturl();
}


XMLDOCUMENT *CCXmlNode::ParentDocument()
{
	return (  XMLDOCUMENTPTR  )pocNode -> GetownerDocument().Detach();
}


XMLNODE *CCXmlNode::Interface()
{
	if ( IsValid() )
		return pocNode;

	return NULL;
}


XMLNODE *CCXmlNode::InsertBefore( XMLNODE *pocRefNode,  LPCTSTR nodeName )
{
	XMLDOCUMENTPTR pocXMLDocument;
	XMLNODEPTR pocNewNode;

	pocXMLDocument = pocNode -> GetownerDocument();
	if ( pocXMLDocument )
	{
		pocNewNode = pocXMLDocument -> createNode( _variant_t( ( short )XMLNODEELEMENTTYPE ), nodeName, "" );
		pocNewNode = pocNode -> insertBefore( pocNewNode.Detach(), ( IUnknown* )pocRefNode );
		return pocNewNode.Detach();
	}
	return NULL;
}


XMLNODE *CCXmlNode::InsertAfter( XMLNODE *pocRefNode,  LPCTSTR nodeName )
{
	XMLDOCUMENTPTR pocXMLDocument;
	XMLNODEPTR pocNewNode,
		pocNextNode;

	pocXMLDocument = pocNode -> GetownerDocument();
	if ( pocXMLDocument )
	{
		pocNewNode = pocXMLDocument -> createNode( _variant_t( ( short )XMLNODEELEMENTTYPE ), nodeName, "" );
		pocNextNode = pocRefNode -> GetnextSibling();
		if ( pocNextNode.GetInterfacePtr() != NULL )
			pocNewNode = pocNode -> insertBefore( pocNewNode.Detach(), ( IUnknown* )pocNextNode );
		else
			pocNewNode = pocNode -> appendChild( pocNewNode.Detach() );

		return pocNewNode.Detach();
	}

	return NULL;
}


void CCXmlNode::RemoveNodes( LPCTSTR searchStr )
{
	int nIndex;
	XMLNODELISTPTR pocNodeList;
	XMLNODE *pocNodeItem;

	if ( !IsValid() )
		return;

	pocNodeList = pocNode -> selectNodes( searchStr );
	for ( nIndex = 0; nIndex < pocNodeList -> Getlength(); nIndex++ )
	{
		try
		{
			pocNodeItem = pocNodeList -> Getitem( nIndex ).Detach();
			pocNodeItem -> GetparentNode() -> removeChild( pocNodeItem );
		}
		catch ( _com_error er )
		{
			AfxMessageBox( er.ErrorMessage() );
		}
	}
}


XMLNODE *CCXmlNode::Parent()
{
	if ( IsValid() )
		return pocNode -> GetparentNode().Detach();

	return NULL;
}


CCXmlNodeList::CCXmlNodeList()
{
}


CCXmlNodeList::CCXmlNodeList( XMLNODELISTPTR pList )
{
	pocNodelist = pList;
}


void CCXmlNodeList::operator=( XMLNODELISTPTR pList )
{
	if ( IsValid() )
		pocNodelist -> Release();
	pocNodelist = pList;
}


CCXmlNodeList::~CCXmlNodeList()
{
}


int CCXmlNodeList::Count()
{
	if ( IsValid() )
		return pocNodelist -> Getlength();
	else
		return 0;
}


BOOL CCXmlNodeList::IsValid()
{
	if ( pocNodelist  ==  NULL )
		return FALSE;
	if ( pocNodelist.GetInterfacePtr()  ==  NULL )
		return FALSE;

	return TRUE;
}


XMLNODE *CCXmlNodeList::Next()
{
	if ( IsValid() )
		return pocNodelist -> nextNode().Detach();
	else
		return NULL;
}


void CCXmlNodeList::Start()
{
	if ( IsValid() )
		pocNodelist -> reset();
}


XMLNODE *CCXmlNodeList::Node( int index )
{
	if ( IsValid() )
		return pocNodelist -> Getitem( index ).Detach();
	else
		return NULL;
}


XMLDOCUMENT *CCXmlNodeList::AsDocument()
{
	if ( IsValid() )
	{
		CCXmlDocument doc;
		doc.LoadXML( _T( "<NodeList></NodeList>" ) );
		CCXmlNode root( doc.AsNode() );

		for ( int i = 0; i < pocNodelist -> Getlength(); i++ )
		{
			root.InsertNode( root.NumNodes(), pocNodelist -> Getitem( i ) -> cloneNode( VARIANT_TRUE ) );
		}
		return doc.Detach();
	}
	else 
		return NULL;
}


XMLNODELIST *CCXmlNode::FindNodes( LPCTSTR searchStr )
{
	if( IsValid() )
	{
		try{
			return pocNode -> selectNodes( searchStr ).Detach();
		}
		catch ( _com_error e )
		{
			CString err = e.ErrorMessage();
			return NULL;
		}
	}
	else
		return NULL;
}

bstr_t CCXmlNode::Name()
{
	if ( IsValid() )
		return pocNode -> GetbaseName();

	return "";
}


XMLNODE *CCXmlNode::InsertAfter( XMLNODE *pocRefNode,  XMLNODE *pNode )
{
	XMLNODEPTR pocNextNode,
		pocNewNode;

	pocNextNode = pocRefNode -> GetnextSibling();
	if ( pocNextNode.GetInterfacePtr() != NULL )
		pocNewNode = pocNode -> insertBefore( pNode, ( IUnknown* )pocNextNode );
	else
		pocNewNode = pocNode -> appendChild( pNode );

	return pocNewNode.Detach();
}


void CCXmlNode::SetText( LPCTSTR text )
{
	if ( IsValid() )
		pocNode -> Puttext( text );
}

bstr_t CCXmlNode::GetText()
{
	if ( IsValid() )
		return pocNode -> Gettext();
	else
		return "";
}

void CCXmlNode::ReplaceNode( XMLNODE *pOldNode,  XMLNODE *pNewNode )
{
	if ( IsValid() )
	{
		pocNode -> replaceChild( pNewNode, pOldNode );
	}
}

int CCXmlNode::NumAttributes()
{
	if ( IsValid() )
	{
		XMLNODEMAPPTR pocAttributes = pocNode -> Getattributes();
		if ( pocAttributes )
			return pocAttributes -> Getlength();
	}

	return 0;
}

bstr_t CCXmlNode::GetAttribName( int index )
{
	if ( IsValid() )
	{
		XMLNODEMAPPTR pocAttributes = pocNode -> Getattributes();
		if ( pocAttributes )
		{
			XMLATTRPTR attrib = pocAttributes -> Getitem( index );
			if ( attrib )
				return attrib -> Getname();
		}
	}
	return "";
}


bstr_t CCXmlNode::GetAttribVal( int index )
{
	if ( IsValid() )
	{
		XMLNODEMAPPTR pocAttributes = pocNode -> Getattributes();
		if ( pocAttributes )
		{
			XMLATTRPTR pocAttribute = pocAttributes -> Getitem( index );
			if ( pocAttribute )
				return pocAttribute -> Gettext();
		}
	}
	return "";
}


bstr_t CCXmlNode::NodeType()
{
	if ( IsValid() )
		return pocNode -> GetnodeTypeString();
	return "";
}
