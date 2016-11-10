//DlgName.h
#pragma once

class CDlgName : public CDialog
{
public:
    CDlgName(CWnd* pParent = NULL);
// Dialog Data
    //{{AFX_DATA(CDlgName)
    enum { IDD = IDD_INPUTNAME };
    CString    m_Name;
    CString    m_Prompt;
    //}}AFX_DATA
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgName)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgName)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
