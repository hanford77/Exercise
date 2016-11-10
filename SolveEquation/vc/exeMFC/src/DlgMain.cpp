//DlgMain.cpp
#include "stdafx.h"
#include <math.h>
#include <float.h>
#include "solveequation.h"
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
    ON_EN_CHANGE(IDC_TXT_ZX0, OnChangeTxt)
	ON_WM_CTLCOLOR()
    ON_EN_CHANGE(IDC_TXT_ZX1, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZX2, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZX3, OnChangeTxt)
	ON_EN_CHANGE(IDC_TXT_ZX4, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZY0, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZY1, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZY2, OnChangeTxt)
    ON_EN_CHANGE(IDC_TXT_ZY3, OnChangeTxt)
	ON_EN_CHANGE(IDC_TXT_ZY4, OnChangeTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    SetIcon(hIcon,TRUE);
    SetIcon(hIcon,FALSE);
	return TRUE;
}

void CDlgMain::OnChangeTxt() 
{
    TCHAR   szText[512];
    HWND    hWnd    =   ::GetDlgItem(m_hWnd,IDC_TXT_ZX4);
    double  x       =   0.0;
    double  y       =   0.0;
    int     i       =   0;

    for(i = 0;i < 5;++i)
    {
        //读取实部
        ::GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
        x           =   _tcstod(szText,NULL);
        //读取虚部
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        ::GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
        y           =   _tcstod(szText,NULL);
        //下一行
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        //
        m_z[2 * (4 - i)    ]    =   x;
        m_z[2 * (4 - i) + 1]    =   y;
    }
    //求解方程
    int n   =   SolveEquation(m_z,m_x);
    //填写结果
    hWnd    =   ::GetDlgItem(m_hWnd,IDC_TXT_X1);
    hWnd    =   ::GetWindow(hWnd,GW_HWNDPREV);
    bool    bOK =   false;
    CString s;

    for(i = 0;i < 4;++i)
    {
        bOK =   i < n;
        s.Empty();
        if(bOK)
        {//计算
            s.Format(_T("%.0le"),m_x[3 * i + 2]);
        }
        ::SetWindowText(hWnd,s);
        //实部
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        if(bOK)
        {
            s.Format(_T("%.13lg"),m_x[3 * i]);
        }
        ::SetWindowText(hWnd,s);
        //虚部
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        if(bOK)
        {
            s.Format(_T("%.13lg"),m_x[3 * i + 1]);
        }
        ::SetWindowText(hWnd,s);
        //下一行
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
        hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
    }
}

HBRUSH CDlgMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH  hbr =   CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    UINT    uID =   pWnd->GetDlgCtrlID();

    if(IDC_LBL_X1 == uID
    || IDC_LBL_X2 == uID
    || IDC_LBL_X3 == uID
    || IDC_LBL_X4 == uID)
    {
        CString s;
        pWnd->GetWindowText(s);
        if(!s.IsEmpty()
        && s[0] >= _T('0') && s[0] <= _T('9'))
        {//不是方程的根，以红色显示。
            pDC->SetTextColor(fabs(_tcstod(s,NULL)) < 1e-10 ? RGB(0,0,255) : RGB(255,0,0));
        }
    }
	return hbr;
}
