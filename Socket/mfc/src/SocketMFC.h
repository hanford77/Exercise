//SocketMFC.h：对 CSocket（同步套接字类）、CAsyncSocket（异步套接字类）的封装
#pragma once

#include <atlconv.h>
#include "ISocketEventHandler.h"

/******************************************************************************\
套接字异步 TCP/UDP 通讯
\******************************************************************************/
class CSocketAsync : public CAsyncSocket
{
protected:
    enum { UDP_MAX_PKG = 65507 };   //UDP 数据包最大字节数
    class SendToData
    {
    public:
        std::string sAddr;
        std::string sData;
    };
    ISocketEventHandler*   m_pEventHandler;       //套接字事件处理器
    std::string     m_sSend;        //Send   函数缓存的发送数据
    std::list<SendToData>
                    m_lstSendTo;    //SendTo 函数缓存的发送数据
public:
    CSocketAsync(ISocketEventHandler*pEvent = NULL)
    {
        m_pEventHandler    =   pEvent;
    }
    void SetEventHandler(ISocketEventHandler*pEvent)
    {
        m_pEventHandler    =   pEvent;
    }
    /**************************************************************************\
    转换 IP 地址格式
    szIP    [in]    字符串格式的 IP 地址。如：192.168.1.200
    nPort   [in]    端口，范围 [0,65535]。如：2001
    addr    [out]   地址
    \**************************************************************************/
    static bool IpAddress(LPCTSTR szIP,UINT nPort,SOCKADDR_IN&addr)
    {
        USES_CONVERSION;        
        memset(&addr,0,sizeof(addr));
        char*szIpA  =   T2A((LPTSTR)szIP);
        if(szIpA)
        {
            addr.sin_addr.s_addr    =   inet_addr(szIpA);
            if(addr.sin_addr.s_addr == INADDR_NONE)
            {
                LPHOSTENT lphost    =   gethostbyname(szIpA);
                if(lphost)
                {
                    addr.sin_addr.s_addr    =   ((LPIN_ADDR)lphost->h_addr)->s_addr;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            addr.sin_addr.s_addr    =   htonl(INADDR_BROADCAST);
        }
        addr.sin_family =   AF_INET;
        addr.sin_port   =   htons((u_short)nPort);
        return true;
    }
public:
    //用于发送 TCP 数据
    virtual int Send(const void*pData,int nLen,int nFlags = 0)
    {
        if(pData)
        {
            if(nLen < 0)
            {
                nLen    =   strlen((const char*)pData);
            }
            if(nLen > 0)
            {
                if(m_sSend.empty())
                {//缓存数据 m_sSend 为空，发送数据
                    int n       =   0;  //单次发送的字节数
                    int nSum    =   0;  //发送的累计字节数

                    for(;;)
                    {
                        n   =   nLen - nSum;
                        n   =   send(m_hSocket,(const char*)pData + nSum,n,0);
                        if(n > 0)
                        {
                            nSum   +=   n;
                            if(nSum >= nLen)
                            {
                                return nLen;
                            }
                        }
                        else if(n == SOCKET_ERROR)
                        {
                            if(WSAGetLastError() == WSAEWOULDBLOCK)
                            {//将数据加入缓存
                                m_sSend    +=   std::string((const char*)pData + nSum,nLen - nSum);
                                return nLen;
                            }
                            else
                            {
                                return nSum;
                            }
                        }
                    }
                }
                else
                {//缓存数据 m_sSend 不为空，直接将数据加入缓存
                    m_sSend    +=   std::string((const char*)pData,nLen);
                    return nLen;
                }
            }
        }
        return 0;
    }
    //用于发送 UDP 数据
    int SendTo(const void* lpBuf, int nBufLen,UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0)
    {        
        SOCKADDR_IN sockAddr;
        if(IpAddress(lpszHostAddress,nHostPort,sockAddr))
        {
            return SendTo(lpBuf,nBufLen,(SOCKADDR*)&sockAddr,sizeof(sockAddr), nFlags);
        }
        return 0;
    }
    //用于发送 UDP 数据
    int SendTo(const void*pData,int nLen,const SOCKADDR*lpSockAddr,int nSockAddrLen,int nFlags = 0)
    {
        if(pData && lpSockAddr && nSockAddrLen > 0)
        {
            if(nLen < 0)
            {
                nLen    =   strlen((const char*)pData);
            }
            if(nLen > 0)
            {
                SendToData  data;
                if(m_lstSendTo.empty())
                {//无缓存数据，发送
                    int n       =   0;  //单次发送的字节数
                    int nSum    =   0;  //发送的累计字节数
                    for(;;)
                    {
                        n   =   nLen - nSum;    //待发送的字节数
                        if(n > UDP_MAX_PKG)
                        {//待发送的字节数不能太大
                            n   =   UDP_MAX_PKG;
                        }
                        n   =   CAsyncSocket::SendTo((const char*)pData + nSum,n,lpSockAddr,nSockAddrLen,nFlags);
                        if(n > 0)
                        {
                            nSum  +=   n;   //累计
                            if(nSum >= nLen)
                            {//发送完毕
                                return nLen;
                            }
                        }
                        else if(n == SOCKET_ERROR)
                        {
                            switch(GetLastError())
                            {
                          //case WSAEMSGSIZE:       //超过 65507 个字节
                            case WSAEWOULDBLOCK:    //操作被挂起
                                data.sAddr.assign((const char*)lpSockAddr,nSockAddrLen);    //地址
                                data.sData.assign((const char*)pData + nSum,nLen - nSum);   //数据
                                m_lstSendTo.push_back(data);                                //缓存地址和数据
                                return nLen;
                            default:
                                return nSum;
                            }
                        }
                    }
                }
                else
                {//有缓存数据，直接缓存
                    data.sAddr.assign((const char*)lpSockAddr,nSockAddrLen);    //地址
                    data.sData.assign((const char*)pData,nLen);                 //数据
                    m_lstSendTo.push_back(data);                                //缓存地址和数据
                    return nLen;
                }
            }
        }
        return 0;
    }
protected:
    virtual void OnConnect(int nErrorCode)
    {//连接上服务器了
        if(m_pEventHandler)
        {
            m_pEventHandler->OnConnect(this,nErrorCode);
        }
    }
    virtual void OnReceive(int nErrorCode)
    {//接收到数据
        if(m_pEventHandler)
        {
            m_pEventHandler->OnReceive(this,nErrorCode);
        }
    }
    virtual void OnSend(int nErrorCode)
    {//发送缓冲区空了，可以发送数据了
        if(m_sSend.length() > 0)
        {//发送缓存数据 m_sSend
            int n       =   0;                  //单次发送的字节数
            int nSum    =   0;                  //发送的累计字节数
            int nTotal  =   m_sSend.length();   //待发送的总字节数

            for(;;)
            {
                n   =   nTotal - nSum;  //待发送的字节数
                n   =   send(m_hSocket,m_sSend.c_str() + nSum,n,0);
                if(n > 0)
                {                    
                    nSum   +=   n;
                    if(nSum >= nTotal)
                    {
                        break;
                    }
                }
                else if(n == SOCKET_ERROR)
                {
                    //WSAGetLastError() == WSAEWOULDBLOCK
                    break;
                }
            }
            if(nSum > 0)
            {
                m_sSend =   m_sSend.substr(nSum);
            }
        }
        if(!m_lstSendTo.empty())
        {//发送缓存数据 m_lstSendTo
            for(std::list<SendToData>::iterator it = m_lstSendTo.begin();it != m_lstSendTo.end();)
            {
                if(DoSendToData(*it))
                {
                    it  =   m_lstSendTo.erase(it);
                }
                else
                {
                    break;
                }
            }
        }
    }
    virtual void OnClose(int nErrorCode)
    {//连接断了
        if(m_pEventHandler)
        {
            m_pEventHandler->OnClose(this,nErrorCode);
        }
    }
protected:
    //发送一包数据
    bool DoSendToData(SendToData&data)
    {
        int nTotal  =   data.sData.length();    //总字节数
        int nSum    =   0;  //发送字节数的累计值        
        int n       =   0;  //单次发送的字节数

        for(;;)
        {
            n   =   nTotal - nSum;
            if(n <= 0)
            {
                return true;    //这一包数据发送完毕了
            }
            if(n > UDP_MAX_PKG)
            {//每次发送的字节数不能过大
                n    =   UDP_MAX_PKG;
            }
            n   =   sendto(m_hSocket,data.sData.c_str() + nSum,n,0
                          ,(const struct sockaddr*)data.sAddr.c_str(),data.sAddr.length());
            if(n > 0)
            {                
                nSum  +=   n;
            }
            else if(n == SOCKET_ERROR)
            {
                data.sData  =   data.sData.substr(nSum);
                //WSAGetLastError() == WSAEWOULDBLOCK
                break;
            }
        }
        return false;   //这一包数据没有发送完毕
    }
};

/******************************************************************************\
套接字同步 TCP/UDP 通讯
\******************************************************************************/
class CSocketSync : public CSocket
{
protected:
    enum { UDP_MAX_PKG = 65507 };       //UDP 数据包最大字节数
    ISocketEventHandler*   m_pEventHandler;    //套接字事件处理器
public:
    CSocketSync(ISocketEventHandler*pEvent = NULL)
    {
        m_pEventHandler    =   pEvent;
    }
    void SetEventHandler(ISocketEventHandler*pEvent)
    {
        m_pEventHandler    =   pEvent;
    }
public:
    //用于发送 UDP 数据
    int SendTo(const void* lpBuf, int nBufLen,UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0)
    {        
        SOCKADDR_IN sockAddr;
        if(CSocketAsync::IpAddress(lpszHostAddress,nHostPort,sockAddr))
        {
            return SendTo(lpBuf,nBufLen,(SOCKADDR*)&sockAddr,sizeof(sockAddr),nFlags);
        }
        return 0;
    }
    //用于发送 UDP 数据
    int SendTo(const void*pData,int nLen,const SOCKADDR*lpSockAddr,int nSockAddrLen,int nFlags = 0)
    {
        if(pData && lpSockAddr && nSockAddrLen > 0)
        {
            if(nLen < 0)
            {
                nLen    =   strlen((const char*)pData);
            }
            if(nLen > 0)
            {
                int n       =   0;  //单次发送的字节数
                int nSum    =   0;  //发送的累计字节数
                for(;;)
                {
                    n   =   nLen - nSum;    //待发送的字节数
                    if(n > UDP_MAX_PKG)
                    {//待发送的字节数不能太大
                        n   =   UDP_MAX_PKG;
                    }
                    n   =   CSocket::SendTo(pData,n,lpSockAddr,nSockAddrLen,nFlags);
                    if(n > 0)
                    {
                        nSum  +=   n;   //累计
                        if(nSum >= nLen)
                        {//发送完毕
                            return nLen;
                        }
                    }
                    else if(n == SOCKET_ERROR)
                    {
                        return nSum;
                    }
                }
            }
        }
        return 0;
    }
protected:
    virtual void OnReceive(int nErrorCode)
    {//接收到数据时，会触发该事件
        if(m_pEventHandler)
        {
            m_pEventHandler->OnReceive(this,nErrorCode);
        }
    }
    virtual void OnClose(int nErrorCode)
    {//连接断了，会触发该事件
        if(m_pEventHandler)
        {
            m_pEventHandler->OnClose(this,nErrorCode);
        }
    }
};

/******************************************************************************\
TCP 套接字之监听，用来监听客户端发来的 TCP 连接请求
\******************************************************************************/
class CSocketTcpListen : public CAsyncSocket
{
public:
    CSocketTcpListen(ISocketEventHandler*pEvent = NULL)
    {
        m_pEventHandler    =   pEvent;
    }
    void SetEventHandler(ISocketEventHandler*pEvent)
    {
        m_pEventHandler    =   pEvent;
    }
protected:
    virtual void OnAccept(int nErrorCode)
    {//客户端发送连接请求时，会触发该事件
        if(m_pEventHandler)
        {
            m_pEventHandler->OnAccept(this,nErrorCode);
        }
    }
public:
    ISocketEventHandler*m_pEventHandler;  //套接字事件处理器
};
