//WinNLS.cpp
#include "stdafx.h"
#include "WinNLS.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWinNLSApp, CWinApp)
    //{{AFX_MSG_MAP(CWinNLSApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CWinNLSApp::CWinNLSApp()
:CWinApp(_T("WinNLS"))
{
}

CWinNLSApp theApp;

BOOL CWinNLSApp::InitInstance()
{
    CWinApp::InitInstance();
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
