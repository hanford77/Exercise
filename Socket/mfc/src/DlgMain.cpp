//DlgMain.cpp
#include "stdafx.h"
#include "mfcsocket.h"
#include "DlgMain.h"
#include "DlgTcpServerSync.h"
#include "DlgTcpClientSync.h"
#include "DlgUdpSync.h"
#include "DlgTcpServerAsync.h"
#include "DlgTcpClientAsync.h"
#include "DlgUdpAsync.h"

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
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SYNC_TCP_SERVER, OnBtnSyncTcpServer)
	ON_BN_CLICKED(IDC_BTN_SYNC_TCP_CLIENT, OnBtnSyncTcpClient)
	ON_BN_CLICKED(IDC_BTN_SYNC_UDP, OnBtnSyncUdp)
	ON_BN_CLICKED(IDC_BTN_ASYNC_TCP_SERVER, OnBtnAsyncTcpServer)
	ON_BN_CLICKED(IDC_BTN_ASYNC_TCP_CLIENT, OnBtnAsyncTcpClient)
	ON_BN_CLICKED(IDC_BTN_ASYNC_UDP, OnBtnAsyncUdp)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgMain::OnOK() 
{
}

void CDlgMain::OnCancel() 
{
}

void CDlgMain::OnClose() 
{
    DestroyWindow();
}

void CDlgMain::OnDestroy() 
{
    std::set<CDialog*>::iterator it;
    for(;;)
    {
        it = m_setDlg.begin();
        if(it == m_setDlg.end())
        {
            break;
        }
        (*it)->SendMessage(WM_CLOSE);
    }
	CDialog::OnDestroy();	
}

void CDlgMain::RemoveDialog(CDialog*pDlg)
{
    if(pDlg)
    {
        m_setDlg.erase(pDlg);
        delete pDlg;
    }
}

//同步 TCP 服务器
void CDlgMain::OnBtnSyncTcpServer() 
{
    CDlgTcpServerSync*pDlg  =   new CDlgTcpServerSync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);
    m_setDlg.insert(pDlg);
}

//同步 TCP 客户端
void CDlgMain::OnBtnSyncTcpClient() 
{
    CDlgTcpClientSync*pDlg =   new CDlgTcpClientSync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);    
    m_setDlg.insert(pDlg);
}

//同步 UDP
void CDlgMain::OnBtnSyncUdp() 
{
    CDlgUdpSync*pDlg =   new CDlgUdpSync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);    
    m_setDlg.insert(pDlg);
}

//异步 TCP 服务器
void CDlgMain::OnBtnAsyncTcpServer() 
{
    CDlgTcpServerAsync*pDlg =   new CDlgTcpServerAsync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);    
    m_setDlg.insert(pDlg);
}

//异步 TCP 客户端
void CDlgMain::OnBtnAsyncTcpClient() 
{
    CDlgTcpClientAsync*pDlg =   new CDlgTcpClientAsync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);    
    m_setDlg.insert(pDlg);
}

//异步 UDP
void CDlgMain::OnBtnAsyncUdp() 
{
    CDlgUdpAsync*pDlg =   new CDlgUdpAsync();
    pDlg->Create(pDlg->IDD,GetDesktopWindow());
    pDlg->ShowWindow(SW_SHOW);    
    m_setDlg.insert(pDlg);
}
