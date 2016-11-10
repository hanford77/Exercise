//HexToNum.cpp
#include "stdafx.h"
#ifndef _WIN32_WCE
    #include <locale.h>
#endif
#include "HexToNum.h"
#include "HexToNumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CHexToNumApp, CWinApp)
	//{{AFX_MSG_MAP(CHexToNumApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

CHexToNumApp::CHexToNumApp()
{
}

CHexToNumApp theApp;

BOOL CHexToNumApp::InitInstance()
{
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
	CHexToNumDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
