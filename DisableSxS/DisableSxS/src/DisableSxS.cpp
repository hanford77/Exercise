//DisableSxS.cpp
#include "stdafx.h"
#include "DisableSxS.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDisableSxSApp, CWinApp)
    //{{AFX_MSG_MAP(CDisableSxSApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CDisableSxSApp::CDisableSxSApp()
:CWinApp(_T("DisableSxS"))
{
}

CDisableSxSApp theApp;


BOOL CDisableSxSApp::InitInstance()
{
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
