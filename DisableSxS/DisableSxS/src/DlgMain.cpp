//DlgMain.cpp
#include "stdafx.h"
#include "disablesxs.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
: CDialog(CDlgMain::IDD, pParent)
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
	ON_WM_DROPFILES()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void AddFile(std::set<CString,lessKey>&setFile,CString sFile)
{
    DWORD   dwAttr  =   GetFileAttributes(sFile);
    if(dwAttr != 0xFFFFFFFF)
    {
        if(dwAttr & FILE_ATTRIBUTE_DIRECTORY)
        {//目录
            if(sFile.Right(1) != _T('\\'))
            {
                sFile  +=   _T('\\');
            }
            WIN32_FIND_DATA wfd;
            HANDLE          hFind   =   FindFirstFile(sFile + _T("*.*"),&wfd);
            if(hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {//目录
                        if(_tcscmp(wfd.cFileName,_T(".")) != 0
                        && _tcscmp(wfd.cFileName,_T("..")) != 0)
                        {
                            AddFile(setFile,sFile + wfd.cFileName);
                        }
                    }
                    else
                    {//文件
                        setFile.insert(sFile + wfd.cFileName);
                    }
                }while(FindNextFile(hFind,&wfd));
                FindClose(hFind);
            }
        }
        else
        {//文件
            setFile.insert(sFile);
        }
    }
}

bool SplitFileName(CString sFull,CString*pFile,CString*pExt)
{
    int nFind   =   sFull.ReverseFind(_T('\\'));
    if(nFind < 0)
    {
        return false;
    }
    ++nFind;
    sFull   =   sFull.Mid(nFind);
    if(pFile)
    {
        *pFile  =   sFull;
    }
    nFind   =   sFull.ReverseFind(_T('.'));
    if(nFind >= 0)
    {
        if(pExt)
        {
            *pExt   =   sFull.Mid(nFind);
        }
    }
    else
    {
        if(pExt)
        {
            pExt->Empty();
        }
    }
    return true;
}

int Find(const char*pData,int nLen,char*szFind,int nStart)
{
    int nFind   =   -1;
    int n       =   strlen(szFind);
    if(n > 0)
    {
        int nEnd    =   nLen - n;
        for(int i = nStart;i <= nEnd;++i)
        {
            if(memcmp(pData + i,szFind,n) == 0)
            {
                nFind   =   i;
                break;
            }
        }
    }
    return nFind;
}

//<dependency>  </dependency>
bool RemoveDependency(CFile&f,char*pData,int nLen)
{
    int nStart  =   0;
    int nEnd    =   0;
    int nMin    =  -1;
    int nMax    =  -1;

    for(;;)
    {
        nStart  =   Find(pData,nLen,"<dependency>",nStart);
        if(nStart < 0)
        {
            break;
        }
        nEnd    =   Find(pData,nLen,"</dependency>",nStart);
        if(nEnd < 0)
        {
            break;
        }
        nEnd   +=   13;
        if(nMin < 0)
        {
            nMin    =   nStart;
        }
        nMax    =   nEnd;
        memset(pData + nStart,' ',nEnd - nStart);
        nStart  =   nEnd;
    }
    if(nMax > nMin)
    {
        f.Seek(nMin,CFile::begin);
        f.Write(pData + nMin,nMax - nMin);
        return true;
    }
    return false;
}

bool RemoveDependency(LPCTSTR szFile)
{
    bool    bOK =   false;
    CFile   f;
    if(f.Open(szFile,CFile::modeReadWrite))
    {
        DWORD   dwSize  =   f.GetLength();
        if(dwSize > 0)
        {
            char*   pData   =   (char*)malloc(dwSize);
            if(f.Read(pData,dwSize) == dwSize)
            {
                bOK =   RemoveDependency(f,pData,dwSize);
            }
            free(pData);
        }
        f.Close();
    }
    return bOK;
}

bool RemoveFindActCtxSectionStringW(LPCTSTR szFile)
{
    bool    bOK =   false;
    CFile   f;
    if(f.Open(szFile,CFile::modeReadWrite))
    {
        DWORD   dwSize  =   f.GetLength();
        if(dwSize > 0)
        {
            char*   pData   =   (char*)malloc(dwSize);
            if(f.Read(pData,dwSize) == dwSize)
            {
                int nFind   =   Find(pData,dwSize,"FindActCtxSectionStringW",0);
                if(nFind >= 0)
                {
                    f.Seek(nFind,CFile::begin);
                    memset(pData,0,24);
                    f.Write(pData,24);
                    bOK =   true;
                }
            }
            free(pData);
        }
        f.Close();
    }
    return bOK;
}

void CDlgMain::ProcessFile(const std::set<CString,lessKey>&setFile)
{
    CString sText;
    CString sFile,sExt;
    for(std::set<CString,lessKey>::const_iterator it = setFile.begin();it != setFile.end();++it)
    {
        const CString&  sFull   =   *it;
        if(SplitFileName(sFull,&sFile,&sExt))
        {
            if(sFile.CompareNoCase(_T("msvcr80.dll"))  == 0
            || sFile.CompareNoCase(_T("msvcr80d.dll")) == 0
            || sFile.CompareNoCase(_T("msvcr90.dll"))  == 0
            || sFile.CompareNoCase(_T("msvcr90d.dll")) == 0)
            {
                if(RemoveFindActCtxSectionStringW(sFull))
                {
                    sText  +=   sFull + _T("\r\n");
                }
            }
            else if(sExt.CompareNoCase(_T(".exe")) == 0
                 || sExt.CompareNoCase(_T(".dll")) == 0
                 || sExt.CompareNoCase(_T(".ocx")) == 0)
            {
                if(RemoveDependency(sFull))
                {
                    sText  +=   sFull + _T("\r\n");
                }
            }
        }
    }
    sText  +=   _T("处理完毕");
    SetDlgItemText(IDC_TXT,sText);
}

void CDlgMain::OnDropFiles(HDROP hDrop) 
{
    std::set<CString,lessKey>
            setFile;
    UINT    nCount  =   DragQueryFile(hDrop,0xFFFFFFFF,NULL,0);
    TCHAR   szFile[MAX_PATH];

    for(UINT i = 0;i < nCount;++i)
    {
        DragQueryFile(hDrop,i,szFile,MAX_PATH);
        AddFile(setFile,szFile);
    }
    DragFinish(hDrop);
    ProcessFile(setFile);
	CDialog::OnDropFiles(hDrop);
}

void CDlgMain::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
    HWND    hWnd    =   ::GetWindow(m_hWnd,GW_CHILD);
    if(hWnd)
    {
        RECT rc;
        GetClientRect(&rc);
        ::MoveWindow(hWnd,0,0,rc.right,rc.bottom,FALSE);
        Invalidate(TRUE);
    }
}

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
    ((CEdit*)GetDlgItem(IDC_TXT))->LimitText(-1);
	return TRUE;
}
