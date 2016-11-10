//TryLink.cpp
#include "stdafx.h"
#include "TryLink.h"
#include "resource.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTryLinkApp::CTryLinkApp()
:CWinApp(_T("TryLink"))
{
}

CTryLinkApp theApp;

BOOL CTryLinkApp::InitInstance()
{
	AfxEnableControlContainer();
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif
	CDlgMain dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
