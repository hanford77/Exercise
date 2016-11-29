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
    afx_msg void OnBtnCodePage();
    afx_msg void OnBtnLocale();
	afx_msg void OnBtnSort();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
