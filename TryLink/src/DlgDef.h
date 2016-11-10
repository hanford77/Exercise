//DlgDef.h
#pragma once

class CDlgDef : public CDialog
{
public:
	CDlgDef(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgDef)
	enum { IDD = IDD_DLG_DEF };
	int		m_iCols;
	int		m_iIcons;
	int		m_iRows;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDef)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDef)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int	m_MaxRows;
	int	m_MaxCols;
};
