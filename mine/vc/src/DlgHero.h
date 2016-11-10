//DlgHero.h
#pragma once

class CDlgHero : public CDialog
{
public:
    BOOL m_f;
    CDlgHero(CWnd* pParent = NULL);
// Dialog Data
    //{{AFX_DATA(CDlgHero)
    enum { IDD = IDD_HERO };
    CString    m_Name1;
    CString    m_Name2;
    CString    m_Name3;
    CString    m_Time1;
    CString    m_Time2;
    CString    m_Time3;
    //}}AFX_DATA
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgHero)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgHero)
    afx_msg void OnBtn();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
