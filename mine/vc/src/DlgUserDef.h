//DlgUserDef.h
#pragma once

class CDlgUserDef : public CDialog
{
public:
    CDlgUserDef(CWnd* pParent = NULL);
// Dialog Data
    //{{AFX_DATA(CDlgUserDef)
    enum { IDD = IDD_USERDEFINE };
    int        m_Rows;
    int        m_Mines;
    int        m_Cols;
    //}}AFX_DATA
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgUserDef)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDlgUserDef)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
