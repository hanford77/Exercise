//StdAfxUser.h
#pragma once

#pragma warning(disable : 4786)
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include <afxsock.h>

#define MAXRECV 8192

//读取某个窗口内的文本，返回窄字符串
inline std::string GetWndText(HWND hWnd)
{
    std::string s;
    if(hWnd)
    {        
        int nA  =   GetWindowTextLengthA(hWnd);
        if(nA > 0)
        {
            char*pA =   (char*)malloc(nA + 1);
            if(pA)
            {
                GetWindowTextA(hWnd,pA,nA + 1);
                s.assign(pA,nA);
                free(pA);
            }
        }
    }
    return s;
}

//给文本框设置文本
inline void SetEditText(HWND hWnd,const CString&s)
{    
    if(hWnd)
    {
        SetWindowText(hWnd,s);        
        SendMessage(hWnd,EM_SETSEL,0,s.GetLength());
        SendMessage(hWnd,EM_SCROLLCARET,0,0);
    }
}

//获取套接字远程地址
inline CString GetPeerName(CAsyncSocket*p)
{
    CString s;
    if(p)
    {
        CString sIP;
        UINT    nPort;
        if(p->GetPeerName(sIP,nPort))
        {            
            s.Format(_T("%s:%u"),sIP,nPort);
        }
    }
    return s;
}

//获取套接字本地地址
inline CString GetSockName(CAsyncSocket*p)
{
    CString s;
    if(p)
    {
        CString sIP;
        UINT    nPort;
        if(p->GetSockName(sIP,nPort))
        {            
            s.Format(_T("%s:%u"),sIP,nPort);
        }
    }
    return s;
}
