//DlgMain.cpp
#include "stdafx.h"
#include "grub4dos_ren.h"
#include "DlgMain.h"
#include "Replacer.h"

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
    m_sOldEXE   =   _T("grub.exe");
    m_sOldMBR   =   _T("grldr.mbr");
    m_sOldGRLDR =   _T("grldr");
    m_sOldMENU  =   _T("menu.lst");
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
    SetDlgItemText(IDC_TXT_EXE  ,m_sOldEXE  );
    SetDlgItemText(IDC_TXT_MBR  ,m_sOldMBR  );
    SetDlgItemText(IDC_TXT_GRLDR,m_sOldGRLDR);
    SetDlgItemText(IDC_TXT_MENU ,m_sOldMENU );
	return TRUE;
}

void CDlgMain::OnOK() 
{
    if(GetNewName())
    {
        CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,_T("grldr|grldr||"),this);
        if(dlg.DoModal() == IDOK)
        {//
            DoRename(dlg.GetPathName());
        }
    }
}

void CDlgMain::OnDropFiles(HDROP hDrop) 
{
    if(::DragQueryFile(hDrop,0xFFFFFFFF,NULL,0) > 0
    && GetNewName())
    {
        TCHAR szFile[MAX_PATH]  =   {_T('\0')};
        ::DragQueryFile(hDrop,0,szFile,MAX_PATH);
        DoRename(szFile);
    }
    ::DragFinish(hDrop);
	CDialog::OnDropFiles(hDrop);
}

/******************************************************************************\
从一个文本框内读取名称
uID     [in]    文本框ID
sName   [out]   读取到的名称
nLen    [in]    名称长度限制，0 表示无限制
\******************************************************************************/
bool CDlgMain::GetName(UINT uID,CString&sName,int nLen)
{
    CString sErr;
    GetDlgItemText(uID,sName);
    sName.TrimLeft();
    sName.TrimRight();
    LPCTSTR szName  =   (LPCTSTR)sName;
    int     i       =   0;
    if(sName.IsEmpty())
    {
        sErr    =   _T("请输入名称");
        goto out;
    }
    if(nLen > 0 && sName.GetLength() != nLen)
    {
        sErr.Format(_T("长度必须为 %d"),nLen);
        goto out;
    }    
    for(i = sName.GetLength() - 1;i >= 0;--i)
    {
        if(szName[i] < 0x20
        || szName[i] > 0x7F
        || szName[i] == _T('\\')
        || szName[i] == _T('/')
        || szName[i] == _T(':')
        || szName[i] == _T('*')
        || szName[i] == _T('?')
        || szName[i] == _T('\"')
        || szName[i] == _T('<')
        || szName[i] == _T('>')
        || szName[i] == _T('|')
        )
        {
            sErr    =   _T("含有非法字符");
            goto out;
        }
    }
out:
    if(!sErr.IsEmpty())
    {
        AfxMessageBox(sErr);
        GotoDlgCtrl(GetDlgItem(uID));
        return false;
    }
    return true;
}

bool CDlgMain::GetNewName()
{
    return GetName(IDC_TXT_EXE  ,m_sNewEXE)
        && GetName(IDC_TXT_MBR  ,m_sNewMBR)
        && GetName(IDC_TXT_GRLDR,m_sNewGRLDR,m_sOldGRLDR.GetLength())
        && GetName(IDC_TXT_MENU ,m_sNewMENU ,m_sOldMENU.GetLength());    
}

void CDlgMain::DoRename(LPCTSTR szFile)
{
    if(szFile && szFile[0])
    {
        CString sPath(szFile);
        DWORD   dwAttr  =   GetFileAttributes(sPath);
        if(dwAttr != 0xFFFFFFFF && (dwAttr & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {//szFile 是一个文件
            int nFind   =   sPath.ReverseFind(_T('\\'));
            if(nFind >= 0)
            {
                sPath   =   sPath.Left(nFind + 1);
            }
        }
        else
        {//szFile 是一个目录
            if(sPath.GetLength() > 0 && sPath[sPath.GetLength() - 1] != _T('\\'))
            {
                sPath  +=   _T('\\');
            }
        }
        //把 grub.exe 里的 grldr 替换掉，然后重命名
        ProcessOneFile(sPath,m_sOldEXE,m_sNewEXE,m_sOldGRLDR,m_sNewGRLDR);
        //把 grldr.mbr 里的 grldr 替换掉，然后重命名
        ProcessOneFile(sPath,m_sOldMBR,m_sNewMBR,m_sOldGRLDR,m_sNewGRLDR);
        //把 grldr 里的 menu.lst 替换掉，然后重命名
        ProcessOneFile(sPath,m_sOldGRLDR,m_sNewGRLDR,m_sOldMENU,m_sNewMENU);
        //重命名 menu.lst
        ProcessOneFile(sPath,m_sOldMENU,m_sNewMENU,NULL,NULL);
        AfxMessageBox(_T("完成重命名工作"));
    }
}

void CDlgMain::ProcessOneFile(CString sPath,LPCTSTR szOldFilename,LPCTSTR szNewFilename,LPCTSTR szOldStr,LPCTSTR szNewStr)
{
    CReplacer r;
    if(r.Load(sPath + szOldFilename))
    {
        if(szOldStr && szNewStr)
        {//替换文件内容
            r.Replace(szOldStr,szNewStr);
        }
        DeleteFile(sPath + szOldFilename);
        r.Save(sPath + szNewFilename);
    }
}
