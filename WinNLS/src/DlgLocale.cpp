//DlgLocale.cpp
#include "stdafx.h"
#include "winnls.h"
#include "DlgLocale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgLocale::CDlgLocale(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLocale::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgLocale)
    //}}AFX_DATA_INIT
}

void CDlgLocale::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLocale)
    DDX_Control(pDX, IDC_LIST_DETAIL, m_lstDetail);
    DDX_Control(pDX, IDC_LIST_MAIN, m_lstMain);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgLocale, CDialog)
    //{{AFX_MSG_MAP(CDlgLocale)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_MAIN, OnGetdispinfoListMain)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MAIN, OnItemchangedListMain)
    ON_WM_SIZE()    
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgLocale::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_lstMain.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_lstMain.InsertColumn(0,_T("LCID"),LVCFMT_LEFT, 100);
    {//填充列标题
#if 0
        int nCol    =   0;    
        m_vType.resize(CLocale::s_mapStrType.size() + 1);
        for(CLocale::StrType::iterator it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
        {        
            m_lst.InsertColumn(++nCol,it->first,LVCFMT_LEFT,200);
            m_vType[nCol]   =   it->second;
        }
#else
        m_vType.clear();
        m_vType.push_back(0);
        m_lstMain.InsertColumn(1,_T("LOCALE_SCOUNTRY"),LVCFMT_LEFT,200);
        m_vType.push_back(LOCALE_SCOUNTRY);
        m_lstMain.InsertColumn(2,_T("LOCALE_SLANGUAGE"),LVCFMT_LEFT,200);
        m_vType.push_back(LOCALE_SLANGUAGE);
#endif
    }
    {//填充行
        int nRows   =   CLocale::s_mapLocale.size();
        m_vID.resize(nRows);
        int nRow    =   0;
        for(CLocale::IdTypeStr::iterator it = CLocale::s_mapLocale.begin();it != CLocale::s_mapLocale.end();++it)
        {
            m_vID[nRow++]   =   it->first;
        }
        m_lstMain.SetItemCount(nRows);
    }
    {//详细信息表
        m_lstDetail.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
        m_lstDetail.InsertColumn(0,_T("项")  ,LVCFMT_LEFT,200);
        m_lstDetail.InsertColumn(1,_T("说明"),LVCFMT_LEFT,200);
        m_lstDetail.InsertColumn(2,_T("值")  ,LVCFMT_LEFT,200);
        int nRow = 0;
        for(CLocale::StrType::iterator it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
        {
            m_lstDetail.InsertItem(nRow,it->first);
            m_lstDetail.SetItemText(nRow,1,it->second.m_sCHS.IsEmpty() ? (LPCTSTR)it->second.m_sENU : (LPCTSTR)it->second.m_sCHS);
            ++nRow;
        }
    }
    OutputToFile(); //输出到文件
    return TRUE;
}

void CDlgLocale::OnItemchangedListMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->uChanged & LVIF_STATE)
    {
        int nSel    =   m_lstMain.GetNextItem(-1,LVNI_SELECTED);
        if(nSel >= 0)
        {//详细信息表
            LCID    id      =   m_vID[nSel];
            int     nRow    =   0;
            for(CLocale::StrType::iterator it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
            {
                m_lstDetail.SetItemText(nRow++,2,CLocale::Value(id,it->second.m_nType));
            }
        }
    }

    *pResult = 0;
}


void CDlgLocale::OnGetdispinfoListMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO*pDispInfo   =   (LV_DISPINFO*)pNMHDR;    
    LV_ITEM*    pItem       =   &(pDispInfo)->item;    
    if(pItem->mask & LVIF_TEXT)
    {
        int     nRow    =   pItem->iItem;       //行
        int     nCol    =   pItem->iSubItem;    //列
        LCID    id      =   m_vID[nRow];
        m_sCellText.Empty();
        if(nCol)
        {
            m_sCellText =   CLocale::Value(id,m_vType[nCol]);
        }
        else
        {//LCID
            m_sCellText.Format(_T("0x%04X(%u)"),id,id);
        }
        pItem->pszText  =   (LPTSTR)(LPCTSTR)m_sCellText;
    }
    *pResult = 0;
}

void CDlgLocale::OnSize(UINT nType, int cx, int cy) 
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

        ::MoveWindow(hWndChild,6,5,269+dx/2,303+dy,FALSE);//IDC_LIST_MAIN
        hWndChild=::GetWindow(hWndChild,GW_HWNDNEXT);::MoveWindow(hWndChild,282+dx/2,5,269+dx/2,303+dy,FALSE);//IDC_LIST_DETAIL
        Invalidate();
    }
}

void CDlgLocale::OutputToFile()
{
    CString sFile;
    GetModuleFileName(NULL,sFile.GetBuffer(MAX_PATH),MAX_PATH);
    sFile.ReleaseBuffer();
    sFile  +=   _T("\\..\\..\\Locale.txt");
    CFile   f;
    if(GetFileAttributes(sFile) == 0xFFFFFFFF   //文件不存在
    && f.Open(sFile,CFile::modeCreate | CFile::modeWrite))
    {
        f.Write("\xFF\xFE",2);  //使用 Unicode，否则某些字符将无法显示
        CString sLine;
        {//输出标题
            CLocale::StrType::iterator it;
            //第一行
            sLine   =   _T("LCID");
            for(it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
            {
                sLine  +=   _T('\t') + it->first;
            }
            sLine  +=   _T("\r\n");
            f.Write((LPCTSTR)sLine,sLine.GetLength() * sizeof(wchar_t));
            //第二行
            sLine.Empty();
            for(it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
            {
                sLine  +=   _T('\t') + it->second.m_sENU;
            }
            sLine  +=   _T("\r\n");
            f.Write((LPCTSTR)sLine,sLine.GetLength() * sizeof(wchar_t));
            //第三行
            sLine.Empty();
            for(it = CLocale::s_mapStrType.begin();it != CLocale::s_mapStrType.end();++it)
            {
                sLine  +=   _T('\t') + it->second.m_sCHS;
            }
            sLine  +=   _T("\r\n");
            f.Write((LPCTSTR)sLine,sLine.GetLength() * sizeof(wchar_t));
        }
        {//输出内容
            TCHAR   szNum[32];           
            
            for(CLocale::IdTypeStr::iterator it1 = CLocale::s_mapLocale.begin();it1 != CLocale::s_mapLocale.end();++it1)
            {
                const LCID&id   =   it1->first;
                _stprintf(szNum,_T("0x%04X(%u)"),id,id);
                sLine   =   szNum;
                for(CLocale::StrType::iterator it2 = CLocale::s_mapStrType.begin();it2 != CLocale::s_mapStrType.end();++it2)
                {
                    sLine  +=   _T('\t') + CLocale::Value(id,it2->second.m_nType);
                }
                sLine  +=   _T("\r\n");
                f.Write((LPCTSTR)sLine,sLine.GetLength() * sizeof(wchar_t));
            }
        }
        f.Close();
    }
}
