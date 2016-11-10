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
    #undef  ON_WM_NCHITTEST
    #define ON_WM_NCHITTEST() {WM_NCHITTEST,0,0,0,AfxSig_wp,(AFX_PMSG)(AFX_PMSGW)(static_cast< LRESULT (AFX_MSG_CALL CWnd::*)(CPoint) > (OnNcHitTest))},
#endif

/******************************************************************************\
定义宏 MODIFY_MESSAGE_MAP，用来修改消息映射表的内容
注意：重新定义了宏 DECLARE_MESSAGE_MAP 和 BEGIN_MESSAGE_MAP
示例代码如下：
BEGIN_MESSAGE_MAP(CDlgMain,CDialog)
    ON_MESSAGE(-1,OnMsg)
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog() 
{
    //下面的语句将消息 ID 由 -1 更改为 WM_USER + 100
    MODIFY_MESSAGE_MAP(CDlgMain,-1,WM_USER + 100)
    CDialog::OnInitDialog();
    return TRUE;
}
#if _MSC_VER >= 1400  //VC++8.0(VC2005)及其以上版本
    #undef  BEGIN_MESSAGE_MAP
    #define BEGIN_MESSAGE_MAP(theClass, baseClass) \
    PTM_WARNING_DISABLE \
    const AFX_MSGMAP* theClass::GetMessageMap() const\
        { return GetThisMessageMap(); }\
    const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap()\
    {\
        typedef theClass ThisClass;\
        typedef baseClass TheBaseClass;\
        static AFX_MSGMAP_ENTRY _messageEntries[] =\
        {

    #define MODIFY_MESSAGE_MAP(theClass,uOld,uNew) \
    {\
        const AFX_MSGMAP_ENTRY* lpEntries =   theClass::GetThisMessageMap()->lpEntries;\
        if(lpEntries)\
        {\
            for(int i = 0;;){\
                const UINT&uMsg   =   lpEntries[i++].nMessage;\
                if(!uMsg) { break; }\
                if(uMsg == (UINT)(uOld)){ (UINT&)uMsg = (UINT)(uNew); break; }\
            }\
        }\
    }\

#else
    #undef DECLARE_MESSAGE_MAP
    #undef BEGIN_MESSAGE_MAP
    #ifdef _AFXDLL
        #define DECLARE_MESSAGE_MAP() \
        private: \
            static AFX_MSGMAP_ENTRY _messageEntries[]; \
        protected: \
            static AFX_DATA const AFX_MSGMAP messageMap; \
            static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
            virtual const AFX_MSGMAP* GetMessageMap() const; \

        #define BEGIN_MESSAGE_MAP(theClass, baseClass) \
            const AFX_MSGMAP* PASCAL theClass::_GetBaseMessageMap() \
                { return &baseClass::messageMap; } \
            const AFX_MSGMAP* theClass::GetMessageMap() const \
                { return &theClass::messageMap; } \
            AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = \
            { &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
            AFX_COMDAT AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
            { \

    #else
        #define DECLARE_MESSAGE_MAP() \
        private: \
            static AFX_MSGMAP_ENTRY _messageEntries[]; \
        protected: \
            static AFX_DATA const AFX_MSGMAP messageMap; \
            virtual const AFX_MSGMAP* GetMessageMap() const; \

        #define BEGIN_MESSAGE_MAP(theClass, baseClass) \
            const AFX_MSGMAP* theClass::GetMessageMap() const \
                { return &theClass::messageMap; } \
            AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = \
            { &baseClass::messageMap, &theClass::_messageEntries[0] }; \
            AFX_COMDAT AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
            { \

    #endif
    #define MODIFY_MESSAGE_MAP(theClass,uOld,uNew) \
    {\
        const AFX_MSGMAP_ENTRY* lpEntries =   theClass::_messageEntries;\
        if(lpEntries)\
        {\
            for(int i = 0;;){\
                const UINT&uMsg   =   lpEntries[i++].nMessage;\
                if(!uMsg) { break; }\
                if(uMsg == (UINT)(uOld)){ (UINT&)uMsg = (UINT)(uNew); break; }\
            }\
        }\
    }\

#endif
\******************************************************************************/
