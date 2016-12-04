//ISocketEventHandler.h
#pragma once

/******************************************************************************\
CAsyncSocket、CSocket 事件处理器
\******************************************************************************/
class ISocketEventHandler
{
public:
    virtual void OnAccept (CAsyncSocket*pSender,int nErrorCode){}
    virtual void OnClose  (CAsyncSocket*pSender,int nErrorCode){}
    virtual void OnConnect(CAsyncSocket*pSender,int nErrorCode){}
    virtual void OnReceive(CAsyncSocket*pSender,int nErrorCode){}
    virtual void OnSend   (CAsyncSocket*pSender,int nErrorCode){}
};
