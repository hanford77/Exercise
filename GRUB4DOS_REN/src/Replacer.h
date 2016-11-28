//Replacer.h
#pragma once

class CReplacer
{
public:
    CReplacer();
   ~CReplacer();
public:
    bool Load(LPCTSTR szFile);
    bool Save(LPCTSTR szFile);
    void Replace(LPCTSTR szOld,LPCTSTR szNew);
    void Empty();
protected:
    char*   m_pData;    //数据
    int     m_nBytes;   //字节数
};
