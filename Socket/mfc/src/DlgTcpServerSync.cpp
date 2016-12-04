//DlgTcpServerSync.cpp
#include "stdafx.h"
#include "mfcsocket.h"
#include "DlgMain.h"
#include "DlgTcpServerSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgTcpServerSync::CDlgTcpServerSync(CWnd* pParent /*=NULL*/)
: CDialog(CDlgTcpServerSync::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTcpServerSync)
	//}}AFX_DATA_INIT
    m_SocketListen.SetEventHandler(this);
}

void CDlgTcpServerSync::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTcpServerSync)
	DDX_Control(pDX, IDC_LIST_CLIENT, m_lstClient);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgTcpServerSync, CDialog)
	//{{AFX_MSG_MAP(CDlgTcpServerSync)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgTcpServerSync::OnInitDialog() 
{
	CDialog::OnInitDialog();
    SetWindowText(_T("TCP 同步通讯服务端"));    
    SetDlgItemInt(IDC_TXT_PORT,2001);	
    EnableControls();
	return TRUE;
}

void CDlgTcpServerSync::OnOK() 
{
}

void CDlgTcpServerSync::OnCancel() 
{
}

void CDlgTcpServerSync::OnClose() 
{
    DestroyWindow();
}

void CDlgTcpServerSync::PostNcDestroy() 
{
    Disconnect();
	theApp.m_pMain->RemoveDialog(this);	
}

void CDlgTcpServerSync::OnBtnConnect() 
{
    {//先断开连接
        Disconnect();
        m_sRecv.Empty();
        SetDlgItemText(IDC_TXT_RECV,_T(""));
        m_lstClient.ResetContent();
    }
    int                 nPort   =   GetDlgItemInt(IDC_TXT_PORT);
    CSocketTcpListen&   s       =   m_SocketListen;
    
    if(s.Create(nPort) && s.Listen())
    {//监听成功
        EnableControls();
    }
    else
    {//监听失败
        s.Close();
        AfxMessageBox(_T("监听失败，可能是端口被占用"));
        GotoDlgCtrl(GetDlgItem(IDC_TXT_PORT));
    }    
}

void CDlgTcpServerSync::Disconnect()
{
    CSocketSync*pClient =   NULL;
    for(MapClient::iterator it = m_mapClient.begin();it != m_mapClient.end();++it)
    {//断开所有与客户端的 TCP 连接
        if(pClient = it->first)
        {
            pClient->ShutDown(CAsyncSocket::both);
            pClient->Close();
            delete pClient;
        }
    }
    m_mapClient.clear();
    //停止监听
    if(m_SocketListen.m_hSocket != INVALID_SOCKET)
    {
        m_SocketListen.ShutDown(CAsyncSocket::both);
        m_SocketListen.Close();        
    }
}

void CDlgTcpServerSync::OnBtnDisconnect() 
{
    Disconnect();
    EnableControls();
}

void CDlgTcpServerSync::OnBtnSend() 
{
    std::string s   =   GetWndText(::GetDlgItem(m_hWnd,IDC_TXT_SEND));
    if(!s.empty())
    {
        CSocketSync*pClient =   NULL;
        for(int i = m_lstClient.GetCount() - 1;i >= 0;--i)        
        {//发送给列表中选中的客户端
            if(m_lstClient.GetSel(i)
            && (pClient = (CSocketSync*)m_lstClient.GetItemData(i))
            )
            {//发送是同步的，效率比异步的低
                pClient->Send(s.c_str(),s.length());
            }
        }
    }
}

void CDlgTcpServerSync::EnableControls()
{
    bool bSocket    =   m_SocketListen.m_hSocket != INVALID_SOCKET;
    ((CEdit*)GetDlgItem(IDC_TXT_PORT))->SetReadOnly(bSocket ? TRUE  : FALSE);
    ((CEdit*)GetDlgItem(IDC_TXT_SEND))->SetReadOnly(bSocket ? FALSE : TRUE );
    GetDlgItem(IDC_BTN_CONNECT   )->EnableWindow(bSocket ? FALSE : TRUE );
    GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(bSocket ? TRUE  : FALSE);
    GetDlgItem(IDC_BTN_SEND      )->EnableWindow(bSocket ? TRUE  : FALSE);
}

//客户端上线
void CDlgTcpServerSync::OnAccept(CAsyncSocket*pSender,int nErrorCode)
{
    if(0 == nErrorCode
  //&& pSender == &m_SocketListen
    )
    {
        CSocketSync*pClient =   new CSocketSync(this);
        if(m_SocketListen.Accept(*pClient))
        {
            CString sPeer           =   GetPeerName(pClient);
            m_mapClient[pClient]    =   sPeer;
            {//客户端加入列表
                int nIndex  =   m_lstClient.AddString(sPeer);
                m_lstClient.SetItemData(nIndex,(UINT_PTR)pClient);
                m_lstClient.SetSel(nIndex,1);
            }
            m_sRecv                +=   sPeer + _T(" > 上线\r\n");
            SetEditText(::GetDlgItem(m_hWnd,IDC_TXT_RECV),m_sRecv);            
        }
        else
        {
            delete pClient;
        }
    }
}

//客户端发送数据过来
void CDlgTcpServerSync::OnReceive(CAsyncSocket*pSender,int nErrorCode)
{
    if(pSender)
    {
        CSocketSync*pClient    =   (CSocketSync*)pSender;
        char            buf[1024];
        int             nRead   =   0;
        std::string     s;

        while((nRead = pClient->CAsyncSocket::Receive(buf,sizeof(buf))) > 0)
        {//读取还是异步的
            s  +=   std::string((const char*)buf,nRead);
        }
        if(!s.empty())
        {
            m_sRecv +=  GetPeerName(pClient) + _T(" > ") + CString(s.c_str(),s.length()) + _T("\r\n");
            if(m_sRecv.GetLength() > MAXRECV)
            {
                m_sRecv =   m_sRecv.Right(MAXRECV);
            }
            SetEditText(::GetDlgItem(m_hWnd,IDC_TXT_RECV),m_sRecv);
        }
    }
}

//客户端下线
void CDlgTcpServerSync::OnClose(CAsyncSocket*pSender,int nErrorCode)
{
    if(pSender)
    {
        CSocketSync*pClient    =   (CSocketSync*)pSender;
        {//从列表中删除客户端
            for(int i = m_lstClient.GetCount() - 1;i >= 0;--i)
            {
                if(m_lstClient.GetItemData(i) == (UINT_PTR)pClient)
                {
                    m_lstClient.DeleteString(i);
                    break;
                }
            }        
        }
        MapClient::iterator it = m_mapClient.find(pClient);
        if(it != m_mapClient.end())
        {
            m_sRecv +=  it->second + _T(" > 下线\r\n");
            m_mapClient.erase(pClient);
            SetEditText(::GetDlgItem(m_hWnd,IDC_TXT_RECV),m_sRecv);
        }
        pClient->ShutDown(CAsyncSocket::both);
        pClient->Close();
        delete pClient;        
    }
}
