//ButtonBmp.cpp
#include "stdafx.h"
#include "Mine.h"
#include "ButtonBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CButtonBmp::CButtonBmp()
{
    m_hBmp=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP3));
    m_hMem=::CreateCompatibleDC(NULL);
    ::SelectObject(m_hMem,m_hBmp);
    m_idxBmp=4;
}

CButtonBmp::~CButtonBmp()
{
    ::DeleteDC(m_hMem);
    ::DeleteObject(m_hBmp);
}

BEGIN_MESSAGE_MAP(CButtonBmp, CButton)
    //{{AFX_MSG_MAP(CBMPButton)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CButtonBmp::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    if(lpDrawItemStruct->itemState & ODS_SELECTED)
    {
        ::BitBlt(lpDrawItemStruct->hDC,0,0,24,24,m_hMem,0,0,SRCCOPY);
    }
    else
    {
        ::BitBlt(lpDrawItemStruct->hDC,0,0,24,24,m_hMem,0,m_idxBmp*24,SRCCOPY);     
    }
}

void CButtonBmp::SetBtnBitmap(int i)
{
    m_idxBmp=i;
    Invalidate();
}