//DlgName.cpp
#include "stdafx.h"
#include "Mine.h"
#include "DlgName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgName::CDlgName(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgName::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgName)
    m_Name        =    _T("ÄäÃû");
    m_Prompt    =    _T("");
    //}}AFX_DATA_INIT
}

void CDlgName::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgName)
    DDX_Text(pDX, IDC_EDIT1, m_Name);
    DDX_Text(pDX, IDC_STATIC1, m_Prompt);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgName, CDialog)
    //{{AFX_MSG_MAP(CDlgName)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()