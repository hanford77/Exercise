//Replacer.cpp
#include "StdAfx.h"
#include "Replacer.h"

CReplacer::CReplacer()
{
    m_pData     =   NULL;
    m_nBytes    =   0;
}

CReplacer::~CReplacer()
{
    Empty();
}

void CReplacer::Empty()
{
    if(m_pData)
    {
        delete[] m_pData;
        m_pData =   NULL;
    }
    m_nBytes    =   0;
}

/******************************************************************************\
载入文件
\******************************************************************************/
bool CReplacer::Load(LPCTSTR szFile)
{
    bool bOK    =   false;
    if(szFile && szFile[0])
    {
        CFile f;
        if(f.Open(szFile,CFile::modeRead | CFile::shareDenyWrite))
        {
            Empty();
            m_nBytes    =   f.GetLength();
            if(m_pData = new char[m_nBytes + 1])
            {
                f.Read(m_pData,m_nBytes);
                bOK =   true;
            }
            f.Close();            
        }
    }
    if(!bOK)
    {
        Empty();
    }
    return bOK;
}

/******************************************************************************\
保存文件
\******************************************************************************/
bool CReplacer::Save(LPCTSTR szFile)
{
    bool    bOK =   false;
    if(szFile && szFile[0] && m_pData)
    {
        CFile f;
        if(f.Open(szFile,CFile::modeCreate | CFile::modeWrite))
        {
            f.Write(m_pData,m_nBytes);
            f.Close();
            bOK =   true;
        }
    }
    return bOK;
}

/******************************************************************************\
替换文件内容
szOld   [in]    旧字符串
szNew   [in]    新字符串
\******************************************************************************/
void CReplacer::Replace(LPCTSTR szOld,LPCTSTR szNew)
{
    if(m_pData && szOld && szNew)
    {
        int n   =   lstrlen(szOld);
        if(n > 0 && lstrlen(szNew) == n)
        {
            char*   pMem   =   (char*)malloc(n + n);
            char*   pOld   =   pMem;
            char*   pNew   =   pMem + n;
            int     i       =   0;

            for(i = 0;i < n;++i)
            {
                pOld[i] =   (char)szOld[i];
                pNew[i] =   (char)szNew[i];
            }
            if(_memicmp(pOld,pNew,n))
            {
                for(i = 0;i + n <= m_nBytes;)
                {
                    if(_memicmp(m_pData + i,pOld,n) == 0)
                    {
                        memcpy(m_pData + i,pNew,n);
                        i  +=   n;
                    }
                    else
                    {
                        ++i;
                    }
                }
            }
            free(pMem);
        }
    }
}
