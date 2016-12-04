//DlgUdpAsync.cpp
#include "stdafx.h"
#include "mfcsocket.h"
#include "DlgMain.h"
#include "DlgUdpSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgUdpSync::CDlgUdpSync(CWnd* pParent /*=NULL*/)
: CDialog(CDlgUdpSync::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgUdpSync)
    //}}AFX_DATA_INIT
    m_Socket.SetEventHandler(this);
}

void CDlgUdpSync::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgUdpSync)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgUdpSync, CDialog)
    //{{AFX_MSG_MAP(CDlgUdpSync)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
    ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)
    ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
    ON_BN_CLICKED(IDC_CHK_BIND, OnChkBind)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDlgUdpSync::OnInitDialog() 
{
    CDialog::OnInitDialog();
    SetWindowText(_T("UDP 同步通讯"));    
    SetDlgItemInt(IDC_TXT_PORT,2001);
    ((CButton*)GetDlgItem(IDC_CHK_BIND))->SetCheck(1);
    SetDlgItemText(IDC_TXT_REMOTE,_T("127.0.0.1:2001"));
    EnableControls();
    return TRUE;
}

void CDlgUdpSync::OnOK() 
{
}

void CDlgUdpSync::OnCancel() 
{
}

void CDlgUdpSync::OnClose() 
{
    DestroyWindow();
}

void CDlgUdpSync::PostNcDestroy() 
{
    Disconnect();
    theApp.m_pMain->RemoveDialog(this);    
}

void CDlgUdpSync::OnBtnConnect() 
{
    {//断开连接
        Disconnect();
        m_sRecv.Empty();
        SetDlgItemText(IDC_TXT_LOCAL,_T(""));
        SetDlgItemText(IDC_TXT_RECV ,_T(""));
    }
    BOOL bOK    =   FALSE;
    if(((CButton*)GetDlgItem(IDC_CHK_BIND))->GetCheck())
    {//绑定
        int nPort   =   GetDlgItemInt(IDC_TXT_PORT);
        bOK =   m_Socket.Create(nPort,SOCK_DGRAM);
    }
    else
    {//不绑定
        bOK =   m_Socket.Socket(SOCK_DGRAM);
    }
    if(bOK)
    {
        SetDlgItemText(IDC_TXT_LOCAL,GetSockName(&m_Socket));
        EnableControls();
    }
    else
    {
        m_Socket.Close();
        SetDlgItemText(IDC_TXT_LOCAL,_T("创建套接字失败"));
    }
}

void CDlgUdpSync::Disconnect()
{
    m_Socket.Close();
}

void CDlgUdpSync::OnBtnDisconnect() 
{
    Disconnect();
    EnableControls();
}

void CDlgUdpSync::OnBtnSend() 
{
    CString sRemote;
    GetDlgItemText(IDC_TXT_REMOTE,sRemote);
    int     nFind   =   sRemote.ReverseFind(_T(':'));
    if(nFind > 0)
    {
        std::string s   =   GetWndText(::GetDlgItem(m_hWnd,IDC_TXT_SEND));
        if(!s.empty())
        {
            UINT    nPort   =   _tcstoul((LPCTSTR)sRemote + (nFind + 1),NULL,10);
            CString sIP     =   sRemote.Left(nFind);
            m_Socket.SendTo(s.c_str(),s.length(),nPort,sIP);
        }
    }
}

void CDlgUdpSync::EnableControls()
{
    bool bSocket    =   m_Socket.m_hSocket != INVALID_SOCKET;    
    ((CEdit*)GetDlgItem(IDC_TXT_PORT  ))->SetReadOnly(bSocket || ((CButton*)GetDlgItem(IDC_CHK_BIND))->GetCheck() == 0 ? TRUE  : FALSE);
    ((CEdit*)GetDlgItem(IDC_TXT_SEND  ))->SetReadOnly(bSocket ? FALSE : TRUE );
    ((CEdit*)GetDlgItem(IDC_TXT_REMOTE))->SetReadOnly(bSocket ? FALSE : TRUE );
    GetDlgItem(IDC_CHK_BIND      )->EnableWindow(bSocket ? FALSE: TRUE );
    GetDlgItem(IDC_BTN_CONNECT   )->EnableWindow(bSocket ? FALSE: TRUE );
    GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(bSocket ? TRUE : FALSE);
    GetDlgItem(IDC_BTN_SEND      )->EnableWindow(bSocket ? TRUE : FALSE);
}

void CDlgUdpSync::OnReceive(CAsyncSocket*pSender,int nErrorCode)
{
    char        buf[64 * 1024];
    int         nRead   =   0;    
    CString     sIP;
    UINT        nPort   =   0;
    CString     sFrom;
    std::map<CString,std::string>
                mapRecv;
    SOCKADDR_IN sockAddr;
    int         nAddrLen    =   sizeof(sockAddr);
    memset(&sockAddr,0,sizeof(sockAddr));
    
    while((nRead = recvfrom(m_Socket.m_hSocket,buf,sizeof(buf),0,(struct sockaddr*)&sockAddr,&nAddrLen)) > 0)
    {
        nPort   =   ntohs(sockAddr.sin_port);
        sIP     =   inet_ntoa(sockAddr.sin_addr);
        sFrom.Format(_T("%s:%d"),sIP,nPort);
        mapRecv[sFrom] +=   std::string((const char*)buf,nRead);
    }
    if(!mapRecv.empty())
    {
        for(std::map<CString,std::string>::iterator it = mapRecv.begin();it != mapRecv.end();++it)
        {
            const std::string&s =   it->second;
            m_sRecv +=  it->first + _T(" > ") + CString(s.c_str(),s.length()) + _T("\r\n");
        }
        if(m_sRecv.GetLength() > MAXRECV)
        {
            m_sRecv =   m_sRecv.Right(MAXRECV);
        }
        SetEditText(::GetDlgItem(m_hWnd,IDC_TXT_RECV),m_sRecv);
    }
}

void CDlgUdpSync::OnChkBind() 
{
    EnableControls();
}
