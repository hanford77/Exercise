//DlgMain.cpp
#include "stdafx.h"
#include "testsxs.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
: CDialog(CDlgMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMain)
	//}}AFX_DATA_INIT
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
	//{{AFX_MSG_MAP(CDlgMain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
    LPCTSTR arrFile[]   =
    {
        //vc2005
        _T("msvcr80.dll"),
        _T("msvcr80d.dll"),
        _T("mfc80.dll"),
        _T("mfc80d.dll"),
        _T("mfc80u.dll"),
        _T("mfc80ud.dll"),
        //vc2008
        _T("msvcr90.dll"),
        _T("msvcr90d.dll"),
        _T("mfc90.dll"),
        _T("mfc90d.dll"),
        _T("mfc90u.dll"),
        _T("mfc90ud.dll"),
    };
    int     n       =   sizeof(arrFile) / sizeof(arrFile[0]);
    HMODULE hMod    =   NULL;
    TCHAR   szFile[MAX_PATH];
    CString sFile;
    for(int i = 0;i < n;++i)
    {
        if(hMod = GetModuleHandle(arrFile[i]))
        {
            GetModuleFileName(hMod,szFile,MAX_PATH);
            sFile  +=   szFile;
            sFile  +=   _T("\r\n");
        }
    }
    if(sFile.IsEmpty())
    {
        sFile=  _T('?');
    }
    SetDlgItemText(IDC_TXT_FILE,sFile);
	return TRUE;
}
