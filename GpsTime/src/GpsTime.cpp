// GPSTime.cpp
#include "stdafx.h"
#include "GPSTime.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CGPSTimeApp, CWinApp)
	//{{AFX_MSG_MAP(CGPSTimeApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

CGPSTimeApp::CGPSTimeApp()
{
}

CGPSTimeApp theApp;

BOOL CGPSTimeApp::InitInstance()
{
	CDlgMain dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
