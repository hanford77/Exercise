//DlgUserDef.cpp
#include "stdafx.h"
#include "Mine.h"
#include "DlgUserDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgUserDef::CDlgUserDef(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgUserDef::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgUserDef)
    m_Rows = 0;
    m_Mines = 0;
    m_Cols = 0;
    //}}AFX_DATA_INIT
}

void CDlgUserDef::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgUserDef)
    DDX_Text(pDX, IDC_HEIGHT, m_Rows);
    DDX_Text(pDX, IDC_MINES, m_Mines);
    DDX_Text(pDX, IDC_WIDTH, m_Cols);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgUserDef, CDialog)
    //{{AFX_MSG_MAP(CDlgUserDef)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()