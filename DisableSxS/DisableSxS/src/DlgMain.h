//DlgMain.h
#pragma once

#include <SET>

struct lessKey
{
    bool operator()(const CString&a, const CString&b) const
    {
        return a.CompareNoCase(b) < 0;
    }
};

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
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
    void ProcessFile(const std::set<CString,lessKey>&setFile);
};
