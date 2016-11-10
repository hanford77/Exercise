// DlgDef.cpp
#include "stdafx.h"
#include "resource.h"
#include "DlgDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgDef::CDlgDef(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDef::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDef)
	m_iRows		=	7;
	m_iCols		=	12;
	m_iIcons	=	21;
	//}}AFX_DATA_INIT
}

void CDlgDef::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDef)
	DDX_Text(pDX, IDC_TXT_ROWS, m_iRows);
	DDX_Text(pDX, IDC_TXT_COLS, m_iCols);
	DDX_Text(pDX, IDC_TXT_ICONS, m_iIcons);
	DDV_MinMaxInt(pDX, m_iIcons, 1, 42);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDef, CDialog)
	//{{AFX_MSG_MAP(CDlgDef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgDef::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_MaxRows	=	GetSystemMetrics(SM_CYSCREEN) / FRONTHEIGHT - 3;
	m_MaxCols	=	GetSystemMetrics(SM_CXSCREEN) / FRONTWIDTH - 2;

	CString s;
	s.Format(_T("行数(1~%d)"),m_MaxRows);
	SetDlgItemText(IDC_LBL_ROWS,s);
	s.Format(_T("列数(1~%d)"),m_MaxCols);
	SetDlgItemText(IDC_LBL_COLS,s);
	return TRUE;
}

void CDlgDef::OnOK() 
{
	if(UpdateData())
	{
		if(m_iRows < 1 || m_iRows > m_MaxRows)
		{
			AfxMessageBox(_T("行数不合理!"));
			GotoDlgCtrl(GetDlgItem(IDC_TXT_ROWS));
			return;
		}
		if(m_iCols < 1 || m_iCols > m_MaxCols)
		{
			AfxMessageBox(_T("列数不合理!"));
			GotoDlgCtrl(GetDlgItem(IDC_TXT_COLS));
			return;
		}
		if((m_iRows & 1) && (m_iCols & 1))
		{
			AfxMessageBox(_T("行数与列数不能同时为奇数!"));
			return;
		}
		CDialog::OnOK();
	}
}
