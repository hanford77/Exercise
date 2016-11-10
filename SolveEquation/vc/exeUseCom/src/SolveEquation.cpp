//SolveEquation.cpp
#include "stdafx.h"
#include "SolveEquation.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSolveEquationApp, CWinApp)
    //{{AFX_MSG_MAP(CSolveEquationApp)
    //}}AFX_MSG
END_MESSAGE_MAP()

CSolveEquationApp::CSolveEquationApp()
:CWinApp(_T("SolveEquation"))
{
}

CSolveEquationApp theApp;

BOOL CSolveEquationApp::InitInstance()
{
    CWinApp::InitInstance();
    AfxOleInit();
    CDlgMain dlg;
    m_pMainWnd  =   &dlg;
    dlg.DoModal();
    return FALSE;
}
