//DlgMain.h
#pragma once

class CDlgMain : public CDialog
{
public:
	CDlgMain(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgMain)
	enum { IDD = IDD_MAIN };
		// NOTE: the ClassWizard will add data members here
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
	virtual void OnOK();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    void    DoRename(LPCTSTR szFile);
    bool    GetNewName();
    bool    GetName(UINT uID,CString&sName,int nLen = 0);
    void    ProcessOneFile(CString sPath,LPCTSTR szOldFilename,LPCTSTR szNewFilename,LPCTSTR szOldStr,LPCTSTR szNewStr);
private:
    CString m_sOldEXE,m_sNewEXE;
    CString m_sOldMBR,m_sNewMBR;
    CString m_sOldGRLDR,m_sNewGRLDR;
    CString m_sOldMENU,m_sNewMENU;
};
