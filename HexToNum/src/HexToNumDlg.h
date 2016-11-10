//HexToNumDlg.h
#pragma once

class CHexToNumDlg : public CDialog
{
public:
	CHexToNumDlg(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CHexToNumDlg)
	enum { IDD = IDD_HEXTONUM_DIALOG };
	CComboBox	m_cboDouble;
	CComboBox	m_cboFloat;
	int		m_iOptCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexToNumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CHexToNumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeTxtHex();
	afx_msg void OnChangeTxtDoubleB();
	afx_msg void OnChangeTxtDoubleL();
	afx_msg void OnChangeTxtFloatL();
	afx_msg void OnChangeTxtFloatB();
	afx_msg void OnChangeTxtInt8L();
	afx_msg void OnChangeTxtInt8B();
	afx_msg void OnChangeTxtInt16L();
	afx_msg void OnChangeTxtInt16B();
	afx_msg void OnChangeTxtInt32L();
	afx_msg void OnChangeTxtInt32B();
	afx_msg void OnChangeTxtInt64L();
	afx_msg void OnChangeTxtInt64B();
	afx_msg void OnChangeTxtUint8L();
	afx_msg void OnChangeTxtUint8B();
	afx_msg void OnChangeTxtUint16L();
	afx_msg void OnChangeTxtUint16B();
	afx_msg void OnChangeTxtUint32L();
	afx_msg void OnChangeTxtUint32B();
	afx_msg void OnChangeTxtUint64L();
	afx_msg void OnChangeTxtUint64B();
	afx_msg void OnSelendokCboDouble();
	afx_msg void OnSelendokCboFloat();
	afx_msg void OnOptCode();
	afx_msg void OnChangeTxtString();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    void DoChangeTxtHex(UINT uID);
private:
    BOOL m_bLock;
};
