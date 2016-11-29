//DlgCodePage.cpp
#include "stdafx.h"
#include "winnls.h"
#include "DlgCodePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgCodePage::CDlgCodePage(CWnd* pParent /*=NULL*/)
: CDialog(CDlgCodePage::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgCodePage)
    //}}AFX_DATA_INIT
}

void CDlgCodePage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgCodePage)
    DDX_Control(pDX, IDC_LIST, m_lst);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgCodePage, CDialog)
    //{{AFX_MSG_MAP(CDlgCodePage)
    ON_EN_CHANGE(IDC_TXT_CODE_PAGE, OnChangeTxtCodePage)    
    ON_WM_SIZE()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define UINT_NAME(x)    x,_T(#x),

BOOL CDlgCodePage::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_lst.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_lst.InsertColumn(0,_T("代码页")               ,LVCFMT_LEFT, 50);
    m_lst.InsertColumn(1,_T("CodePageName")         ,LVCFMT_LEFT,150);
    m_lst.InsertColumn(2,_T("MaxCharSize")          ,LVCFMT_LEFT,150);
    m_lst.InsertColumn(3,_T("DefaultChar")          ,LVCFMT_LEFT,150);
    m_lst.InsertColumn(4,_T("LeadByte")             ,LVCFMT_LEFT,150);
    m_lst.InsertColumn(5,_T("UnicodeDefaultChar")   ,LVCFMT_LEFT,150);
    m_lst.InsertColumn(6,_T("CodePage")             ,LVCFMT_LEFT,150);//应该与第 0 列相等    
    OnChangeTxtCodePage();  //填充代码页列表
    {//获取 ACP、OEMCP、……的信息
        CString     sText;
        CString     sLine;
        CPINFOEX    ci;
        struct  
        {
            UINT    nCP;
            LPCTSTR szName;
        }CodePage[]   =
        {
            UINT_NAME(CP_ACP        )
            UINT_NAME(CP_OEMCP      )
            UINT_NAME(CP_MACCP      )
            UINT_NAME(CP_THREAD_ACP )        
        };
        sLine.Format(_T("GetACP()   = %u\r\n"),GetACP()  );sText  +=   sLine;
        sLine.Format(_T("GetOEMCP() = %u\r\n"),GetOEMCP());sText  +=   sLine;        
        int n   =   sizeof(CodePage) / sizeof(CodePage[0]);
        for(int i = 0;i < n;++i)
        {
            if(GetCPInfoEx(CodePage[i].nCP,0,&ci))
            {            
                sLine.Format(_T("%s = %u\r\n"),CodePage[i].szName,ci.CodePage);
                sText  +=   sLine;
            }
        }
        SetDlgItemText(IDC_TXT_INFO,sText);
    }
    return TRUE;
}

void CDlgCodePage::OnChangeTxtCodePage() 
{
    CString     sText;
    GetDlgItemText(IDC_TXT_CODE_PAGE,sText);
    sText.MakeUpper();    
    CString     s;    
    
    m_vCodePage.clear();
    for(CCodePage::UintInfo::iterator it = CCodePage::s_mapCodePage.begin();it != CCodePage::s_mapCodePage.end();++it)
    {
        s   =   it->second.CodePageName;        
        s.MakeUpper();
        if(sText.IsEmpty() || s.Find(sText) >= 0)
        {
            m_vCodePage.push_back(it->first);            
        }
    }
    SetDlgItemText(IDC_TXT_INFO,_T(""));
    m_lst.SetItemCount(m_vCodePage.size());
}

void CDlgCodePage::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    if(nType == SIZE_MINIMIZED)
    {
        return;
    }
    HWND hWndChild  =   ::GetWindow(m_hWnd,GW_CHILD);
    if(hWndChild)
    {
        RECT    r;
        GetClientRect(&r);
        int     dx  =   r.right  - 557;
        int     dy  =   r.bottom - 314;

        ::MoveWindow(hWndChild,6,9,26,12,FALSE);//IDC_STATIC
        hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild,47,5,503+dx,21,FALSE);//IDC_TXT_CODE_PAGE
        hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild,6,32,371+dx,275+dy,FALSE);//IDC_LIST
        hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild,386+dx,32,164,275+dy,FALSE);//IDC_TXT_INFO
        Invalidate();
    }
}

void CDlgCodePage::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO*pDispInfo   =   (LV_DISPINFO*)pNMHDR;    
    LV_ITEM*    pItem       =   &(pDispInfo)->item;    
    if(pItem->mask & LVIF_TEXT)
    {
        int         nRow    =   pItem->iItem;       //行
        int         nCol    =   pItem->iSubItem;    //列
        UINT        nCP     =   m_vCodePage[nRow];
        CPINFOEX*   pInfo   =   NULL;
        CCodePage::UintInfo::iterator
                    it      =   CCodePage::s_mapCodePage.find(nCP);
        if(it != CCodePage::s_mapCodePage.end())
        {
            pInfo   =   &it->second;
        }
        m_sCellText.Empty();
        switch(nCol)
        {
        case 0://代码页
            m_sCellText.Format(_T("%u"),nCP);
            break;
        case 1://CodePageName
            if(pInfo)
            {
                m_sCellText =   pInfo->CodePageName;
            }
            break;
        case 2://MaxCharSize
            if(pInfo)
            {
                m_sCellText.Format(_T("%u"),pInfo->MaxCharSize);
            }
            break;
        case 3://DefaultChar
            if(pInfo)
            {                
                m_sCellText.Format(_T("0x%02X 0x%02X "),pInfo->DefaultChar[0],pInfo->DefaultChar[1]);
                char    szStr[3];
                szStr[0]        =   pInfo->DefaultChar[0];
                szStr[1]        =   pInfo->DefaultChar[1];
                szStr[2]        =   '\0';
                m_sCellText    +=   szStr;
            }
            break;
        case 4://LeadByte
            if(pInfo)
            {
                //m_sCellText.Empty();
                TCHAR szNum[32];
                for(int i = 1;i < MAX_LEADBYTES;i += 2)
                {
                    if(pInfo->LeadByte[i-1] || pInfo->LeadByte[i])
                    {
                        _stprintf(szNum,_T("[0x%02X,0x%02X] "),pInfo->LeadByte[i-1],pInfo->LeadByte[i]);
                        m_sCellText    +=   szNum;
                    }
                    else
                    {
                        break;
                    }
                }                
            }
            break;
        case 5://UnicodeDefaultChar
            if(pInfo)
            {
                m_sCellText.Format(_T("0x%04X "),pInfo->UnicodeDefaultChar);
                m_sCellText    +=   pInfo->UnicodeDefaultChar;
            }
            break;
        case 6://CodePage
            if(pInfo)
            {
                m_sCellText.Format(_T("%u"),pInfo->CodePage);
            }
            break;
        }
        pItem->pszText  =   (LPTSTR)(LPCTSTR)m_sCellText;
    }
    *pResult = 0;
}

//获取每个代码页的编码字节数、每个字节的编码范围
void CDlgCodePage::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->uChanged & LVIF_STATE)
    {
        int nSel    =   m_lst.GetNextItem(-1,LVNI_SELECTED);
        if(nSel >= 0)
        {
            UINT    nCP =   m_vCodePage[nSel];
            SetDlgItemText(IDC_TXT_INFO,CCodePage::GetCodeRange(nCP));
        }
    }
    *pResult = 0;
}
