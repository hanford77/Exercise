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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
