//GRUB4DOS_REN.cpp
#include "stdafx.h"
#include "GRUB4DOS_REN.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CGRUB4DOS_RENApp, CWinApp)
    //{{AFX_MSG_MAP(CGRUB4DOS_RENApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CGRUB4DOS_RENApp::CGRUB4DOS_RENApp()
:CWinApp(_T("GRUB4DOS_REN"))
{
}

CGRUB4DOS_RENApp theApp;

BOOL CGRUB4DOS_RENApp::InitInstance()
{
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
