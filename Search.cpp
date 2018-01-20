// Search.cpp : implementation file
//

#include "stdafx.h"
#include "HelpViewer.h"
#include "Search.h"


// CSearch dialog

IMPLEMENT_DYNAMIC(CSearch, CDialog)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSearch::IDD, pParent)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearch, CDialog)
	ON_BN_CLICKED(IDSEARCH, &CSearch::OnBnClickedSearch)
END_MESSAGE_MAP()


// CSearch message handlers

void CSearch::OnBnClickedSearch()
{
	// TODO: Add your control notification handler code here
}
