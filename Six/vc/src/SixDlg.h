// SixDlg.h : header file
//

#if !defined(AFX_SIXDLG_H__3E230922_F9F3_424A_BFFB_CBDE554BB68A__INCLUDED_)
#define AFX_SIXDLG_H__3E230922_F9F3_424A_BFFB_CBDE554BB68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CSixDlg dialog

class CSixDlg : public CDialog
{
// Construction
public:
	CSixDlg(CWnd* pParent = NULL);	// standard constructor
  ~CSixDlg();
// Dialog Data
	//{{AFX_DATA(CSixDlg)
	enum { IDD = IDD_SIX_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSixDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSixDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnCal();
	afx_msg void OnBtnLoad();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetK(int i,int j);
	void GetIJ(int k,int &i,int &j);
	CString GetSegmentName(int i);
	double m_DD[21];
    double m_LL[21];
	CMyEdit m_MyEdit[42];
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIXDLG_H__3E230922_F9F3_424A_BFFB_CBDE554BB68A__INCLUDED_)
