//SolveEquation.cpp
#include "StdAfx.h"
#include <math.h>
#include <atlbase.h>
#if _MSC_VER < 1310  //VC++6.0/EVC3.0/EVC4.0
    CComModule _Module;
#endif
#include <atlwin.h>
#include "resource.h"

class CDlgMain : public CSimpleDialog<IDD_MAIN>
{
public:
    typedef CSimpleDialog<IDD_MAIN> base;
	BEGIN_MSG_MAP(CDlgMain)
      //CHAIN_MSG_MAP(base)
        MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
        MESSAGE_HANDLER(WM_CLOSE,OnClose)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,OnColorStatic)
        COMMAND_RANGE_HANDLER(IDC_TXT_ZX4,IDC_TXT_ZY0,OnTextChange)
	END_MSG_MAP()
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        base::OnInitDialog(uMsg,wParam,lParam,bHandled);
        //设置图标
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上版本
        HINSTANCE   hInst   =   _AtlBaseModule.GetResourceInstance();
#else
        HINSTANCE   hInst   =   _Module.GetResourceInstance();
#endif
        HICON       hIcon   =   LoadIcon(hInst,MAKEINTRESOURCE(IDR_MAINFRAME));
        SendMessage(this->m_hWnd,WM_SETICON,TRUE ,(LPARAM)hIcon);
        SendMessage(this->m_hWnd,WM_SETICON,FALSE,(LPARAM)hIcon);        
        return TRUE;
    }
    LRESULT OnClose(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        EndDialog(m_hWnd,0);
        return 0;
    }
	LRESULT OnTextChange(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL&bHandled)
	{
        if(wNotifyCode == EN_CHANGE)
        {
            TCHAR   szText[512];
            HWND    hWnd    =   ::GetDlgItem(this->m_hWnd,IDC_TXT_ZX4);
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
            hWnd    =   ::GetDlgItem(this->m_hWnd,IDC_TXT_X1);
            hWnd    =   ::GetWindow(hWnd,GW_HWNDPREV);
            bool    bOK =   false;

            for(i = 0;i < 4;++i)
            {
                bOK         =   i < n;
                szText[0]   =   _T('\0');
                if(bOK)
                {//计算
                    _stprintf(szText,_T("%.0le"),m_x[3 * i + 2]);
                }
                ::SetWindowText(hWnd,szText);
                //实部
                hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
                if(bOK)
                {
                    _stprintf(szText,_T("%.13lg"),m_x[3 * i]);
                }
                ::SetWindowText(hWnd,szText);
                //虚部
                hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
                if(bOK)
                {
                    _stprintf(szText,_T("%.13lg"),m_x[3 * i + 1]);
                }
                ::SetWindowText(hWnd,szText);
                //下一行
                hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
                hWnd        =   ::GetWindow(hWnd,GW_HWNDNEXT);
            }
        }
        return 0;
	}
    LRESULT OnColorStatic(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        LRESULT hBrush  =   ::DefWindowProc(this->m_hWnd,uMsg,wParam,lParam);
        HWND    hWnd    =   (HWND)lParam;
        UINT    uID     =   ::GetDlgCtrlID(hWnd);
        if(IDC_LBL_X1 == uID
        || IDC_LBL_X2 == uID
        || IDC_LBL_X3 == uID
        || IDC_LBL_X4 == uID)
        {
            TCHAR   szText[512];
            ::GetWindowText(hWnd,szText,sizeof(szText) / sizeof(szText[0]));
            if(szText[0] >= _T('0') && szText[0] <= _T('9'))
            {//不是方程的根，以红色显示。
                HDC hDC =   (HDC)wParam;
                SetTextColor(hDC,fabs(_tcstod(szText,NULL)) < 1e-10 ? RGB(0,0,255) : RGB(255,0,0));
            }
        }
        return (INT_PTR)hBrush;
    }
protected:
    double m_z[10]; //方程的系数
    double m_x[12]; //方程的根
};

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow) 
{
#if _MSC_VER < 1310  //VC++6.0/EVC3.0/EVC4.0
    _Module.Init(NULL,hInstance);
#endif
    CDlgMain    dlg;
    dlg.DoModal();
#if _MSC_VER < 1310  //VC++6.0/EVC3.0/EVC4.0
    _Module.Term();
#endif
    return 0;
}
