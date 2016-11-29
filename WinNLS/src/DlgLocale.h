//DlgLocale.h
#pragma once

#include "Locale.h"

class CDlgLocale : public CDialog
{
public:
    CDlgLocale(CWnd* pParent = NULL);
// Dialog Data
    //{{AFX_DATA(CDlgLocale)
    enum { IDD = IDD_LOCALE };
    CListCtrl    m_lstDetail;
    CListCtrl    m_lstMain;
    //}}AFX_DATA
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgLocale)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CDlgLocale)
    virtual BOOL OnInitDialog();
    afx_msg void OnGetdispinfoListMain(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnItemchangedListMain(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSize(UINT nType, int cx, int cy);    
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
    void    OutputToFile();
protected:
    CLocale             m_Locale;
    std::vector<LCID>   m_vID;
    std::vector<LCTYPE> m_vType;
    CString             m_sCellText;
};
