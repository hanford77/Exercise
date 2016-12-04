//DlgTcpClientAsync.h
#pragma once

#include "SocketMFC.h"

class CDlgTcpClientAsync : public CDialog
                         , public ISocketEventHandler
{
public:
	CDlgTcpClientAsync(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgTcpClientAsync)
	enum { IDD = IDD_TCP_CLIENT };
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTcpClientAsync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgTcpClientAsync)
    virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
    afx_msg void OnClose();
	afx_msg void OnBtnConnect();
    afx_msg void OnBtnDisconnect();
	afx_msg void OnBtnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected://ISocketEventHandler
    virtual void OnConnect(CAsyncSocket*pSender,int nErrorCode);
    virtual void OnReceive(CAsyncSocket*pSender,int nErrorCode);
    virtual void OnClose  (CAsyncSocket*pSender,int nErrorCode);
protected:
    void    EnableControls();
    void    Disconnect();
protected:
    CSocketAsync    m_Socket;
    std::string     m_sRecv;
    bool            m_bConn;    //是否已经连接
};
