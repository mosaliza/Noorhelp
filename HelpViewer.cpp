
// HelpViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "HelpViewer.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "HelpViewerDoc.h"
#include "HelpViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelpViewerApp

BEGIN_MESSAGE_MAP(CHelpViewerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHelpViewerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CHelpViewerApp construction

CHelpViewerApp::CHelpViewerApp()
{

	m_bHiColorIcons = TRUE;
	m_hInstEnglish = NULL;
	m_hInstFarsi = NULL;
	m_hInstArabic = NULL;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
CHelpViewerApp::~CHelpViewerApp()
{
		if(m_hInstFarsi)
			FreeLibrary(m_hInstFarsi);
		if(m_hInstArabic)
			FreeLibrary(m_hInstArabic);
	
}

// The one and only CHelpViewerApp object

CHelpViewerApp theApp;


// CHelpViewerApp initialization

BOOL CHelpViewerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("HelpViewer"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	::AfxOleInit();
	CoInitialize( NULL );

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
	//---
	LCID lcid = GetThreadLocale();
	m_nLanguage = ConvertLangID( lcid );
	m_nLanguage = GetInt(_T("ApplicationLanguage"), m_nLanguage);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_HelpViewerTYPE,
		RUNTIME_CLASS(CHelpViewerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHelpViewerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CHelpViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
int CHelpViewerApp::ConvertLangID( LCID lcid )
{
	lcid &= 0xFF; // We only want the low order 8 bits
	switch(lcid)
	{
	case LANG_ENGLISH:
		return ID_LANGUAGE_ENGLISH;
	case LANG_FARSI:
		return ID_LANGUAGE_FARSI;
	case LANG_ARABIC:
		return ID_LANGUAGE_ARABIC;
	default:
		return ID_LANGUAGE_ENGLISH;
	}
}


// CHelpViewerApp customization load/save methods

void CHelpViewerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CHelpViewerApp::LoadCustomState()
{
}

void CHelpViewerApp::SaveCustomState()
{
}

// CHelpViewerApp message handlers



