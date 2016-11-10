//DlgHero.cpp
#include "stdafx.h"
#include "Mine.h"
#include "DlgHero.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgHero::CDlgHero(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgHero::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgHero)
    m_Name1 = _T("");
    m_Name2 = _T("");
    m_Name3 = _T("");
    m_Time1 = _T("");
    m_Time2 = _T("");
    m_Time3 = _T("");
    //}}AFX_DATA_INIT
    m_f        =    FALSE;
}

void CDlgHero::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgHero)
    DDX_Text(pDX, IDC_NAME1, m_Name1);
    DDX_Text(pDX, IDC_NAME2, m_Name2);
    DDX_Text(pDX, IDC_NAME3, m_Name3);
    DDX_Text(pDX, IDC_TIME1, m_Time1);
    DDX_Text(pDX, IDC_TIME2, m_Time2);
    DDX_Text(pDX, IDC_TIME3, m_Time3);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgHero, CDialog)
    //{{AFX_MSG_MAP(CDlgHero)
    ON_BN_CLICKED(IDC_BTN, OnBtn)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgHero::OnBtn() 
{
    m_Name1=m_Name2=m_Name3=_T("ÄäÃû");
    m_Time1=m_Time2=m_Time3=_T("999");
    m_f=TRUE;
    UpdateData(FALSE);
}