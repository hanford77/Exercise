//DlgTcpClientSync.cpp
#include "stdafx.h"
#include "mfcsocket.h"
#include "DlgMain.h"
#include "DlgTcpClientSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgTcpClientSync::CDlgTcpClientSync(CWnd* pParent /*=NULL*/)
: CDialog(CDlgTcpClientSync::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTcpClientSync)		
	//}}AFX_DATA_INIT
    m_Socket.SetEventHandler(this);
}

void CDlgTcpClientSync::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTcpClientSync)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgTcpClientSync, CDialog)
	//{{AFX_MSG_MAP(CDlgTcpClientSync)
    ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)	
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgTcpClientSync::OnInitDialog() 
{
	CDialog::OnInitDialog();
    SetWindowText(_T("TCP 同步通讯客户端"));
    SetDlgItemText(IDC_TXT_IP,_T("127.0.0.1"));
    SetDlgItemInt(IDC_TXT_PORT,2001);	
    EnableControls();
	return TRUE;
}

void CDlgTcpClientSync::OnOK() 
{
}

void CDlgTcpClientSync::OnCancel() 
{
}

void CDlgTcpClientSync::OnClose() 
{
    DestroyWindow();
}

void CDlgTcpClientSync::PostNcDestroy() 
{
    Disconnect();
	theApp.m_pMain->RemoveDialog(this);	
}

void CDlgTcpClientSync::OnBtnConnect() 
{
    {//断开连接
        Disconnect();
        m_sRecv =   "";
        SetDlgItemText(IDC_TXT_LOCAL,_T(""));
        SetDlgItemText(IDC_TXT_RECV ,_T(""));
    }
    CString sIP;    
    GetDlgItemText(IDC_TXT_IP,sIP);
    int     nPort   =   GetDlgItemInt(IDC_TXT_PORT);
    
    if(m_Socket.Socket()            //创建套接字成功
    && m_Socket.Connect(sIP,nPort)  //连接服务器成功
    )
    {//连接成功
        SetDlgItemText(IDC_TXT_LOCAL,GetSockName(&m_Socket));
        EnableControls();
    }
    else
    {
        m_Socket.Close();
        SetDlgItemText(IDC_TXT_LOCAL,_T("连接失败"));
    }
}

void CDlgTcpClientSync::Disconnect()
{
    if(m_Socket.m_hSocket != INVALID_SOCKET)
    {
        m_Socket.ShutDown(CAsyncSocket::both);
        m_Socket.Close();
    }
}

void CDlgTcpClientSync::OnBtnDisconnect() 
{
    Disconnect();
    EnableControls();
}

void CDlgTcpClientSync::OnBtnSend() 
{
    std::string s   =   GetWndText(::GetDlgItem(m_hWnd,IDC_TXT_SEND));
    if(!s.empty())
    {
        m_Socket.Send(s.c_str(),s.length());
    }
}

void CDlgTcpClientSync::EnableControls()
{
    bool bSocket    =   m_Socket.m_hSocket != INVALID_SOCKET;
    ((CEdit*)GetDlgItem(IDC_TXT_IP  ))->SetReadOnly(bSocket ? TRUE  : FALSE);
    ((CEdit*)GetDlgItem(IDC_TXT_PORT))->SetReadOnly(bSocket ? TRUE  : FALSE);
    ((CEdit*)GetDlgItem(IDC_TXT_SEND))->SetReadOnly(bSocket ? FALSE : TRUE );
    GetDlgItem(IDC_BTN_CONNECT   )->EnableWindow(bSocket ? FALSE : TRUE );
    GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(bSocket ? TRUE  : FALSE);
    GetDlgItem(IDC_BTN_SEND      )->EnableWindow(bSocket ? TRUE  : FALSE);
}

void CDlgTcpClientSync::OnReceive(CAsyncSocket*pSender,int nErrorCode)
{
    char    buf[1024];
    int     nRead   =   0;
    
    while((nRead = m_Socket.CAsyncSocket::Receive(buf,sizeof(buf))) > 0)
    {//读取还是异步的
        m_sRecv +=  std::string((const char*)buf,nRead);
    }
    if(m_sRecv.length() > MAXRECV)
    {
        m_sRecv =   m_sRecv.substr(m_sRecv.length() - MAXRECV);
    }
    SetEditText(::GetDlgItem(m_hWnd,IDC_TXT_RECV)
               ,CString(m_sRecv.c_str(),m_sRecv.length()));
}

void CDlgTcpClientSync::OnClose(CAsyncSocket*pSender,int nErrorCode)
{
    OnBtnDisconnect();
}
