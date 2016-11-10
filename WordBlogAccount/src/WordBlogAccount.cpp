//WordBlogAccount.cpp
#include "stdafx.h"
#include "WordBlogAccount.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWordBlogAccountApp, CWinApp)
    //{{AFX_MSG_MAP(CWordBlogAccountApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CWordBlogAccountApp::CWordBlogAccountApp()
:CWinApp(_T("WordBlogAccount"))
{
}

CWordBlogAccountApp theApp;

BOOL CWordBlogAccountApp::InitInstance()
{
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    CWinApp::InitInstance();
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
