//DlgUdpAsync.h
#pragma once

#include "SocketMFC.h"

class CDlgUdpAsync : public CDialog
                   , public ISocketEventHandler
{
public:
	CDlgUdpAsync(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgUdpAsync)
	enum { IDD = IDD_UDP };
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUdpAsync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgUdpAsync)
    virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
    afx_msg void OnClose();
	afx_msg void OnBtnConnect();
    afx_msg void OnBtnDisconnect();
	afx_msg void OnBtnSend();
	afx_msg void OnChkBind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected://ISocketEventHandler    
    virtual void OnReceive(CAsyncSocket*pSender,int nErrorCode);    
protected:
    void    EnableControls();
    void    Disconnect();
protected:
    CSocketAsync    m_Socket;
    CString         m_sRecv;
};
