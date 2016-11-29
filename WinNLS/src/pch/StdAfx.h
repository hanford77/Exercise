//StdAfx.h
#pragma once

#define _CRT_NONSTDC_NO_WARNINGS           //使用 POSIX 函数时不产生警告信息
#define _CRT_NON_CONFORMING_SWPRINTFS      //沿用老版本的 swprintf 函数
#define _CRT_SECURE_NO_WARNINGS            //使用不安全函数时不产生警告信息

//包含系统头文件----------------------------------------------------------------
#ifdef _WIN32_WCE
    //智能设备
    #if _MSC_VER==1200        //EVC3.0
        #include "StdAfx3.h"
    #elif _MSC_VER==1201      //EVC4.0
        #include "StdAfx4.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "StdAfx2005CE.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "StdAfx2008CE.h"
    #endif
#else
    //PC 程序
    #if _MSC_VER==1200        //VC++6.0
        #define WINVER  0x0500
        #include "StdAfx6.h"
    #elif _MSC_VER==1300      //VC++7.0(VC2002)
        #define WINVER  0x0500
        #include "StdAfx2002.h"
    #elif _MSC_VER==1310      //VC++7.1(VC2003)
        #define WINVER  0x0500
        #include "StdAfx2003.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "StdAfx2005.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "StdAfx2008.h"
    #elif _MSC_VER==1600      //VC++10.0(VC2010)
        #include "StdAfx2010.h"
    #elif _MSC_VER==1700      //VC++11.0(VC2012)
        #include "StdAfx2012.h"
    #elif _MSC_VER==1800      //VC++12.0(VC2013)
        #include "StdAfx2013.h"
    #elif _MSC_VER==1900      //VC++14.0(VC2015)
        #include "StdAfx2015.h"
    #endif
#endif

#include "ON_WM_XXX.h"        //升级宏 ON_WM_XXX()

//包含自定义头文件--------------------------------------------------------------
#include "../StdAfxUser.h"
