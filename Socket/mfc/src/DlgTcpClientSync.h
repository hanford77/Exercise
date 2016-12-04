//DlgTcpClientSync.h
#pragma once

#include "SocketMFC.h"

class CDlgTcpClientSync : public CDialog
                        , public ISocketEventHandler
{
public:
	CDlgTcpClientSync(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgTcpClientSync)
	enum { IDD = IDD_TCP_CLIENT };
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTcpClientSync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgTcpClientSync)
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
    virtual void OnReceive(CAsyncSocket*pSender,int nErrorCode);
    virtual void OnClose  (CAsyncSocket*pSender,int nErrorCode);
protected:
    void    EnableControls();
    void    Disconnect();
protected:
    CSocketSync m_Socket;
    std::string m_sRecv;    
};
