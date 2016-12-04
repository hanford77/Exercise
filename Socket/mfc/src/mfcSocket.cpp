//mfcSocket.cpp
#include "stdafx.h"
#include "mfcSocket.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CmfcSocketApp, CWinApp)
    //{{AFX_MSG_MAP(CmfcSocketApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CmfcSocketApp::CmfcSocketApp()
:CWinApp(_T("mfcSocket"))
,m_pMain(NULL)
{
}

CmfcSocketApp theApp;

BOOL CmfcSocketApp::InitInstance()
{
    CWinApp::InitInstance();
#ifndef _WIN32_WCE
    _tsetlocale(LC_ALL,_T(""));
#endif
    AfxSocketInit();    //³õÊ¼»¯ Socket ¿â
    m_pMain     =   new CDlgMain();
    m_pMainWnd  =   m_pMain;
    m_pMain->Create(m_pMain->IDD);
    m_pMain->ShowWindow(m_nCmdShow);
    m_pMain->UpdateWindow();
    return TRUE;
}

int CmfcSocketApp::ExitInstance() 
{
	if(m_pMain)
    {
        delete m_pMain;
        m_pMain =   NULL;
    }
	return CWinApp::ExitInstance();
}
