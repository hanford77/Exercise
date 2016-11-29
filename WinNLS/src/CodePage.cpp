//CodePage.cpp
#include "StdAfx.h"
#include "WinNLS.h"
#include "winnls.h"
#include "CodePage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCodePage::UintInfo CCodePage::s_mapCodePage;

CCodePage::CCodePage()
{
    if(s_mapCodePage.empty())
    {
        Enum();
    }
}

BOOL CALLBACK CCodePage::EnumCodePagesProc(LPTSTR szCodePageStr)
{
    s_mapCodePage[_tcstoul(szCodePageStr,NULL,10)];
    return TRUE;
}

//枚举代码页至 s_mapCodePage
void CCodePage::Enum()
{
    {//枚举
        s_mapCodePage.clear();
        EnumSystemCodePages(CCodePage::EnumCodePagesProc,CP_INSTALLED);
      //EnumSystemCodePages(EnumCodePagesProc,CP_SUPPORTED);
    }
    {//获取每个代码页的信息        
        for(UintInfo::iterator it = s_mapCodePage.begin();it != s_mapCodePage.end();++it)
        {
            CPINFOEX&   ci  =   it->second;
            if(!GetCPInfoEx(it->first,0,&it->second))
            {
                memset(&ci,0,sizeof(ci));
                _stprintf(ci.CodePageName,_T("%u"),it->first);
            }
        }
    }
}

//获取某个代码页的编码字节数、每个字节的编码范围
CString CCodePage::GetCodeRange(UINT nCodePage)
{
    const int   N       =   32; //多字节字符，最多字节数    
    wchar_t     w       =   0;  //UTF-16 字符
    BYTE        s[N];           //多字节字符
    int         nA      =   0;  //多字节字符字节数
    int         nAMin   =   100;//多字节字符字节数的最小值
    int         nAMax   =   0;  //多字节字符字节数的最大值
    int         i       =   0;
    struct
    {
        int     nCount;
        BYTE    Min[N];
        BYTE    Max[N];
    }Range[N + 1];
    
    memset(Range,0,sizeof(Range));
    do
    {
        nA   =   WideCharToMultiByte(nCodePage,0,&w,1,(char*)s,sizeof(s),NULL,NULL);
        if(nA > 0)
        {
            if(nAMin > nA)
            {
                nAMin   =   nA;
            }
            if(nAMax < nA)
            {
                nAMax   =   nA;
            }
            if(Range[nA].nCount++)
            {
                for(i = 0;i < nA;++i)
                {
                    if(Range[nA].Min[i] > s[i])
                    {
                        Range[nA].Min[i]    =   s[i];
                    }
                    else if(Range[nA].Max[i] < s[i])
                    {
                        Range[nA].Max[i]    =   s[i];
                    }
                }
            }
            else
            {
                for(i = 0;i < nA;++i)
                {
                    Range[nA].Min[i]    =
                    Range[nA].Max[i]    =   s[i];
                }
            }
        }
    }while(++w);
    CString sText;
    CString sLine;
    TCHAR   szRange[32];
    for(nA = nAMin;nA <= nAMax;++nA)
    {
        if(Range[nA].nCount)
        {
            sLine.Format(_T("%d 字节 %5d 个："),nA,Range[nA].nCount);
            for(i = 0;i < nA;++i)
            {
                _stprintf(szRange,_T("\r\n    [0x%02X,0x%02X]"),Range[nA].Min[i],Range[nA].Max[i]);
                sLine  +=   szRange;
            }
            sText  +=   sLine + _T("\r\n");
        }
    }
    return sText;    
}
