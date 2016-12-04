//DlgTcpServerSync.h
#pragma once

#include "SocketMFC.h"

class CDlgTcpServerSync : public CDialog
                         , public ISocketEventHandler
{
public:
	CDlgTcpServerSync(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgTcpServerSync)
	enum { IDD = IDD_TCP_SERVER };
	CListBox	m_lstClient;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTcpServerSync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgTcpServerSync)
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
    virtual void OnAccept (CAsyncSocket*pSender,int nErrorCode);
    virtual void OnReceive(CAsyncSocket*pSender,int nErrorCode);
    virtual void OnClose  (CAsyncSocket*pSender,int nErrorCode);
protected:
    void    EnableControls();
    void    Disconnect();
protected:
    typedef std::map<CSocketSync*,CString> MapClient;
    CSocketTcpListen    m_SocketListen;
    MapClient           m_mapClient;    //所有的客户端
    CString             m_sRecv;
};
