// Mine.cpp
#include "stdafx.h"
#include "Mine.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMineApp, CWinApp)
    //{{AFX_MSG_MAP(CMineApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMineApp::CMineApp()
{
}

CMineApp theApp;

BOOL CMineApp::InitInstance()
{
#ifdef _AFXDLL
    Enable3dControls();
#else
    Enable3dControlsStatic();
#endif
    SetRegistryKey(_T("yhf"));
    CDlgMain    dlg;
    m_pMainWnd = &dlg;
    dlg.DoModal();
    return FALSE;
}
