// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "HelpViewer.h"
#include "SearchTask.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPane

BEGIN_MESSAGE_MAP(CSearchTask, CMFCTasksPane)
ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPane construction/destruction

CSearchTask::CSearchTask()
{
	m_nDocumentsGroup = -1;

	m_nUserColorGroup = -1;
	m_nUserColorTask = -1;
	// TODO: add one-time construction code here

}

CSearchTask::~CSearchTask()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTaskPane message handlers

int CSearchTask::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetCaption (_T(""));

	EnableNavigationToolbar (FALSE);

	EnableWrapLabels (TRUE);
	EnableOffsetCustomControls (FALSE);


	int nPage2 = AddPage (_T("Search"));



	const int nControlHeight = 15;


	int nPage2Gr2 = AddGroup (nPage2, _T("Look For:"));

	if (!CreateEditControl())
	{
		TRACE0("Failed to create the custom window\n");
		return -1;      // fail to create
	}

	AddWindow (nPage2Gr2, m_wndEdit.GetSafeHwnd (),nControlHeight);


	return 0;
}

void CSearchTask::UpdateMRUFilesList ()
{
	AddMRUFilesList (m_nDocumentsGroup);
	RedrawWindow ();
}




BOOL CSearchTask::CreateEditControl()
{
	CRect rectDummy (0, 0, 0, 0);
	DWORD dwEditStyle = WS_CHILD | WS_VISIBLE |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL;

	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	if (!m_wndEdit.Create (dwEditStyle, rectDummy, this, (UINT)-1))
	{
		TRACE0("Failed to create the edit window\n");
		return FALSE;
	}

	//m_wndEdit.ModifyStyleEx (0, WS_EX_CLIENTEDGE);

	m_wndEdit.SetFont (&m_Font);
	//m_wndEdit.SetWindowText(_T("This is the standard multiline Edit Box.\r\nHere you can type your text."));

	return TRUE;
}

