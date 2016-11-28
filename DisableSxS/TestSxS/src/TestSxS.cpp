//TestSxS.cpp
#include "stdafx.h"
#include "TestSxS.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTestSxSApp, CWinApp)
    //{{AFX_MSG_MAP(CTestSxSApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CTestSxSApp::CTestSxSApp()
:CWinApp(_T("TestSxS"))
{
}

CTestSxSApp theApp;

BOOL CTestSxSApp::InitInstance()
{
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
