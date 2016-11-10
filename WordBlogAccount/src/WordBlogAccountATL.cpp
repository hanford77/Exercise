//WordBlogAccountATL.cpp
#include "StdAfx.h"
#include <math.h>
#include <atlbase.h>
#if _MSC_VER < 1310  //VC++6.0/EVC3.0/EVC4.0
    CComModule _Module;
#endif
#include <atlwin.h>
#include "resource.h"
#include "Account.h"

class CDlgMain : public CSimpleDialog<IDD_MAIN>
{
public:
    typedef CSimpleDialog<IDD_MAIN> base;
	BEGIN_MSG_MAP(CDlgMain)
      //CHAIN_MSG_MAP(base)
        MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
        MESSAGE_HANDLER(WM_SIZE      ,OnSize)
        MESSAGE_HANDLER(WM_CLOSE     ,OnClose)
        COMMAND_HANDLER(IDC_BTN_BACKUP ,BN_CLICKED,OnBtnBackup )
        COMMAND_HANDLER(IDC_BTN_RESTORE,BN_CLICKED,OnBtnRestore)
        NOTIFY_HANDLER(IDC_LIST,NM_DBLCLK       ,OnDblclkList       )
        NOTIFY_HANDLER(IDC_LIST,LVN_ENDLABELEDIT,OnEndLabelEditList )
	END_MSG_MAP()
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        base::OnInitDialog(uMsg,wParam,lParam,bHandled);
        m_hWndLst   =   ::GetDlgItem(m_hWnd,IDC_LIST);
        LVCOLUMN    c;
        memset(&c,0,sizeof(c));
        c.mask      =   LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
        c.fmt       =   LVCFMT_LEFT;
        ListView_SetExtendedListViewStyle(m_hWndLst,LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
        c.cx        =   100;
        c.pszText   =   _T("Name");
        ListView_InsertColumn(m_hWndLst,0,&c);
        c.cx        =   300;
        c.pszText   =   _T("URL");
        ListView_InsertColumn(m_hWndLst,1,&c);
        FillList();
        return TRUE;
    }
    LRESULT OnSize(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        if(wParam != SIZE_MINIMIZED)
        {
            HWND    hWndChild   =   ::GetWindow(m_hWnd,GW_CHILD);
            if(hWndChild)
            {
                RECT    r;
                GetClientRect(&r);
                int     dx  =   r.right  - 442;
                int     dy  =   r.bottom - 310;

                ::MoveWindow(hWndChild,0,0,444 + dx,270 + dy,FALSE);//IDC_LIST
                hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild, 8,276 + dy,66,28,FALSE);//IDC_BTN_BACKUP
                hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild,82,276 + dy,66,28,FALSE);//IDC_BTN_RESTORE
                Invalidate();
            }
        }
        return 0;
    }
    LRESULT OnClose(UINT uMsg, WPARAM wParam,LPARAM lParam,BOOL&bHandled)
    {
        EndDialog(m_hWnd,0);
        return 0;
    }
    LRESULT OnDblclkList(int wParam,LPNMHDR lp,BOOL&bHandled)
    {
        int nSel    =   ::SendMessage(m_hWndLst, LVM_GETNEXTITEM,-1,LVNI_SELECTED);
        if(nSel >= 0)
        {//鼠标双击列表某一行，开始编辑名称
            ::SendMessage(m_hWndLst,LVM_EDITLABEL,nSel,0);
        }
        return 0;
    }
    LRESULT OnEndLabelEditList(int wParam,LPNMHDR lp,BOOL&bHandled)
    {
	    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)lp;
        return m_Account.ModifyFriendlyName(pDispInfo->item.iItem,pDispInfo->item.pszText) ? 1 : 0;	
    }
    tstring GetBackupFileName()
    {
        TCHAR szPath[MAX_PATH + 32];
        GetModuleFileName(NULL,szPath,sizeof(szPath) / sizeof(szPath[0]));
        lstrcpy(_tcsrchr(szPath,_T('\\')) + 1,_T("bak.reg"));
        return szPath;
    }
	LRESULT OnBtnBackup(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL&bHandled)
	{
        tstring sFile(GetBackupFileName());
        if(m_Account.m_vItem.empty())
        {
            DeleteFile(sFile.c_str());  //直接删除备份文件
        }
        else
        {
            if(m_Account.Backup(sFile.c_str()))
            {
                MessageBox(_T("备份成功"));
            }
            else
            {
                MessageBox(_T("备份失败"));
            }
        }
        return 0;
	}
	LRESULT OnBtnRestore(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL&bHandled)
	{
        tstring sFile(GetBackupFileName());
        if(m_Account.Restore(sFile.c_str()))
        {
            MessageBox(_T("还原成功"));
        }
        else
        {
            MessageBox(_T("还原失败"));
        }
        FillList();
        return 0;
	}
protected:
    void FillList()
    {
        ListView_DeleteAllItems(m_hWndLst);
        m_Account.Query();
        int n = m_Account.m_vItem.size();
        LVITEM vi;
        memset(&vi,0,sizeof(vi));
        vi.mask     =   LVIF_TEXT;
        for(int i = 0;i < n;++i)
        {
            const CAccount::Item&t = m_Account.m_vItem[i];
            vi.iItem    =   i;
            vi.pszText  =   (LPTSTR)t.sName.c_str();
            ListView_InsertItem(m_hWndLst,&vi);
            ListView_SetItemText(m_hWndLst,i,1,(LPTSTR)t.sUrl.c_str());
        }
    }
protected:
    HWND        m_hWndLst;
    CAccount    m_Account;
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
