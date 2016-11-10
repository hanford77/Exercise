//StdAfxUser.h
#pragma once

#define _ATL_APARTMENT_THREADED

#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本
    #define _ATL_NO_AUTOMATIC_NAMESPACE                     //atlbase.h 里不会 using namespace ATL;
    #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS              //部分 CString 构造函数将使用关键字 explicit
    #define _ATL_ALL_WARNINGS
    #define  ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
#else
  //#define _ATL_DLL                //使用 ATL.dll 动态库
  //#define _ATL_MIN_CRT
  //#define _ATL_STATIC_REGISTRY    //Statically linking to Registry Ponent
#endif

#include "resource.h"
#include "SolveEquationCom.h"

#include <atlbase.h>
#if _MSC_VER >= 1300 //VC++7.0(2002) 及其以上的版本    
    class CTestModule : public ATL::CAtlDllModuleT< CTestModule >
    {
    public :
	    DECLARE_LIBID(LIBID_SolveEquationLib)
	    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_REG_APP, "{FE827129-645A-436F-A1E4-4A933F19BA17}")
    };
    //#include <atlctl.h>
    extern CTestModule      _AtlModule;
#else
    extern ATL::CComModule  _Module;
#endif
#include <atlcom.h>

//PATH1 是 dllSDK 静态库文件相对于 vc 项目文件(*.vcproj/*.vcxproj)的相对路径
#define PATH1    "../../../dllSDK/bin/"
#if _MSC_VER==1200        //VC++6.0
    #define PATH2   "vc6"
#elif _MSC_VER==1300      //VC++7.0(VC2002)
    #define PATH2   "vc2002"
#elif _MSC_VER==1310      //VC++7.1(VC2003)
    #define PATH2   "vc2003"
#elif _MSC_VER==1400      //VC++8.0(VC2005)
    #define PATH2   "vc2005"
#elif _MSC_VER==1500      //VC++9.0(VC2008)
    #define PATH2   "vc2008"
#elif _MSC_VER==1600      //VC++10.0(VC2010)
    #define PATH2   "vc2010"
#elif _MSC_VER==1700      //VC++11.0(VC2012)
    #define PATH2   "vc2012"
#elif _MSC_VER==1800      //VC++12.0(VC2013)
    #define PATH2   "vc2013"
#elif _MSC_VER==1900      //VC++14.0(VC2015)
    #define PATH2   "vc2015"
#else
    #error Unknown VC++ compiler
#endif
#ifdef _WIN64
    #ifdef _M_IA64
        #define PATH3   "-Itanium"
    #else
        #define PATH3   "-x64"
    #endif
#else
    #define PATH3   "-Win32"
#endif
#ifdef _DEBUG
    #ifdef _UNICODE
        #define PATH4   "-DU/"
    #else
        #define PATH4   "-DA/"
    #endif
#else
    #ifdef _UNICODE
        #define PATH4   "-RU/"
    #else
        #define PATH4   "-RA/"
    #endif
#endif
#define SolveEquationDllI PATH1 PATH2 PATH3 PATH4
#include "../../dllSDK/inc/_Static.inl"
#undef  PATH1
#undef  PATH2
#undef  PATH3
#undef  PATH4

#include "../../dllSDK/inc/_Static.h"

