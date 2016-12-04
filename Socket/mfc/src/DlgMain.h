//DlgMain.h
#pragma once

class CDlgMain : public CDialog               
{
public:
	CDlgMain(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgMain)
	enum { IDD = IDD_MAIN };
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgMain)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnBtnSyncTcpServer();
	afx_msg void OnBtnSyncTcpClient();
	afx_msg void OnBtnSyncUdp();
	afx_msg void OnBtnAsyncTcpServer();
	afx_msg void OnBtnAsyncTcpClient();
	afx_msg void OnBtnAsyncUdp();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void RemoveDialog(CDialog*pDlg);
protected:    
    std::set<CDialog*>   m_setDlg;
};
