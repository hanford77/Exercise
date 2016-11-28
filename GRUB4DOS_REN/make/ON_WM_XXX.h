//ON_WM_XXX.h
#pragma once

//本文件用来升级宏 ON_WM_XXX()

/******************************************************************************\
ON_WM_ACTIVATEAPP()
vc6 的响应函数为 void OnActivateApp(BOOL bActive, HTASK hTask) 
从 vc2002 开始第二个参数由 HTASK 改为 DWORD
调用基类函数 CWnd::OnActivateApp
#if _MSC_VER >= 1300
    CWnd::OnActivateApp(BOOL.DWORD);
#else
    CWnd::OnActivateApp(BOOL.HTASK);
#endif
\******************************************************************************/

/******************************************************************************\
ON_WM_TIMER()
vc6 的响应函数为 void OnTimer(UINT nIDEvent) 
从 vc2002 开始第一个参数由 UINT 改为 UINT_PTR
\******************************************************************************/

/******************************************************************************\
ON_WM_NCHITTEST()
vc6 的响应函数为 UINT OnNcHitTest(CPoint point)
从 vc2005 开始，返回值由 UINT 更改为 LRESULT
\******************************************************************************/
#if _MSC_VER == 1300 || _MSC_VER == 1310
    #undef  ON_WM_NCHITTEST()
    #define ON_WM_NCHITTEST() {WM_NCHITTEST,0,0,0,AfxSig_wp,(AFX_PMSG)(AFX_PMSGW)(static_cast< LRESULT (AFX_MSG_CALL CWnd::*)(CPoint) > (OnNcHitTest))},
#endif
