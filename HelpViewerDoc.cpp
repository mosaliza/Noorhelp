
// HelpViewerDoc.cpp : implementation of the CHelpViewerDoc class
//

#include "stdafx.h"
#include "HelpViewer.h"

#include "HelpViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelpViewerDoc

IMPLEMENT_DYNCREATE(CHelpViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelpViewerDoc, CDocument)
END_MESSAGE_MAP()


// CHelpViewerDoc construction/destruction

CHelpViewerDoc::CHelpViewerDoc()
{
	// TODO: add one-time construction code here
	m_pHtmlView=NULL;
}

CHelpViewerDoc::~CHelpViewerDoc()
{
}

BOOL CHelpViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CHelpViewerDoc serialization

void CHelpViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CHelpViewerDoc diagnostics

#ifdef _DEBUG
void CHelpViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelpViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHelpViewerDoc commands
