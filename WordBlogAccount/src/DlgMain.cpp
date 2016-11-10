//DlgMain.cpp
#include "stdafx.h"
#include "wordblogaccount.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
:CDialog(CDlgMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMain)
	//}}AFX_DATA_INIT
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain)
	DDX_Control(pDX, IDC_LIST, m_lst);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
	//{{AFX_MSG_MAP(CDlgMain)
    ON_WM_SIZE()
	ON_WM_CLOSE()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackup)
	ON_BN_CLICKED(IDC_BTN_RESTORE, OnBtnRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_lst.InsertColumn(0,_T("Name"),LVCFMT_LEFT,100);
    m_lst.InsertColumn(1,_T("URL") ,LVCFMT_LEFT,300);
    FillList();
	return TRUE;
}

void CDlgMain::OnOK() 
{
}

void CDlgMain::OnCancel() 
{	
}

void CDlgMain::OnClose() 
{
	CDialog::OnCancel();
}

void CDlgMain::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int nSel = m_lst.GetNextItem(-1,LVNI_SELECTED);
    if(nSel >= 0)
    {//鼠标双击列表某一行，开始编辑名称
        m_lst.EditLabel(nSel);
    }
	*pResult = 0;
}

void CDlgMain::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    *pResult = m_Account.ModifyFriendlyName(pDispInfo->item.iItem,pDispInfo->item.pszText) ? 1 : 0;	
}

tstring CDlgMain::GetBackupFileName()
{
    TCHAR szPath[MAX_PATH + 32];
    GetModuleFileName(NULL,szPath,sizeof(szPath) / sizeof(szPath[0]));
    lstrcpy(_tcsrchr(szPath,_T('\\')) + 1,_T("bak.reg"));
    return szPath;
}

void CDlgMain::OnBtnBackup() 
{
    tstring sFile(GetBackupFileName());
    if(m_Account.m_vItem.empty())
    {
        DeleteFile(sFile.c_str());    //直接删除备份文件
    }
    else
    {
        if(m_Account.Backup(sFile.c_str()))
        {
            AfxMessageBox(_T("备份成功"));
        }
        else
        {
            AfxMessageBox(_T("备份失败"));
        }
    }
}

void CDlgMain::OnBtnRestore() 
{
    tstring sFile(GetBackupFileName());
    if(m_Account.Restore(sFile.c_str()))
    {
        AfxMessageBox(_T("还原成功"));
    }
    else
    {
        AfxMessageBox(_T("还原失败"));
    }
    FillList();
}

void CDlgMain::FillList()
{
    m_lst.DeleteAllItems();
    m_Account.Query();
    int n = m_Account.m_vItem.size();
    for(int i = 0;i < n;++i)
    {
        const CAccount::Item&t = m_Account.m_vItem[i];
        m_lst.InsertItem(i,t.sName.c_str());
        m_lst.SetItemText(i,1,t.sUrl.c_str());
    }
}

void CDlgMain::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
    if(nType == SIZE_MINIMIZED)
    {
        return;
    }
    HWND hWndChild  =   ::GetWindow(m_hWnd,GW_CHILD);
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
