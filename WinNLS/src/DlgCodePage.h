//DlgCodePage.h
#pragma once

#include "CodePage.h"

class CDlgCodePage : public CDialog
{
public:
    CDlgCodePage(CWnd* pParent = NULL);
// Dialog Data
    //{{AFX_DATA(CDlgCodePage)
    enum { IDD = IDD_CODE_PAGE };
    CListCtrl    m_lst;
    //}}AFX_DATA
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgCodePage)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CDlgCodePage)
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeTxtCodePage();    
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
protected:
    CCodePage           m_CodePage;
    CString             m_sCellText;
    std::vector<UINT>   m_vCodePage;
};
