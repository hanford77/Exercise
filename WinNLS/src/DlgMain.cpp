//DlgMain.cpp
#include "stdafx.h"
#include "winnls.h"
#include "DlgMain.h"
#include "DlgLocale.h"
#include "DlgCodePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
:CDialog(CDlgMain::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgMain)        
    //}}AFX_DATA_INIT
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMain)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
    //{{AFX_MSG_MAP(CDlgMain)
    ON_BN_CLICKED(IDC_BTN_CODE_PAGE, OnBtnCodePage)
    ON_BN_CLICKED(IDC_BTN_LOCALE, OnBtnLocale)
	ON_BN_CLICKED(IDC_BTN_SORT, OnBtnSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgMain::OnBtnLocale() 
{
    CDlgLocale dlg;
    dlg.DoModal();
}

void CDlgMain::OnBtnCodePage() 
{
    CDlgCodePage dlg;
    dlg.DoModal();
}

void CDlgMain::OnBtnSort() 
{
    LCID    idLoc   =   GetThreadLocale();
    LANGID  idLang  =   LANGIDFROMLCID(idLoc);
    if(idLang == MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED))
    {//简体中文
        static bool bPinYin =   true;   //是否拼音排序        
        WORD        idSort  =   bPinYin ? SORT_CHINESE_PRCP/*拼音排序*/ : SORT_CHINESE_PRC/*笔画数排序*/;
        SetDlgItemText(IDC_GRP_SORT,bPinYin ? _T("排序(拼音)") : _T("排序(笔画数)"));
        CListBox*   pBox    =   (CListBox*)GetDlgItem(IDC_LIST);
        pBox->SetLocale(MAKELCID(idLang,idSort));
        pBox->ResetContent();
        pBox->AddString(_T("排"));
        pBox->AddString(_T("序"));
        pBox->AddString(_T("张三"));
        pBox->AddString(_T("李四"));
        bPinYin =   !bPinYin;   //切换排序方法
    }    
}
