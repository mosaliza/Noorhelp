
// HelpViewer.h : main header file for the HelpViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHelpViewerApp:
// See HelpViewer.cpp for the implementation of this class
//

class CHelpViewerApp : public CWinAppEx
{
public:
	CHelpViewerApp();
	~CHelpViewerApp();

//Operations
int ConvertLangID( LCID lcid );
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	UINT m_nLanguage;
	HINSTANCE m_hInstEnglish,
		m_hInstFarsi,
		m_hInstArabic;
	BOOL m_bIsRTL;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


};

extern CHelpViewerApp theApp;
