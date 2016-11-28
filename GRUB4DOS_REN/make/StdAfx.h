//StdAfx.h
#pragma once

#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

//包含系统头文件----------------------------------------------------------------
#ifdef _WIN32_WCE
    //智能设备
    #if _MSC_VER==1200        //EVC3.0
        #include "evc3/StdAfx3.h"
    #elif _MSC_VER==1201      //EVC4.0
        #include "evc4/StdAfx4.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "vc2005/StdAfx2005CE.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "vc2008/StdAfx2008CE.h"
    #endif
#else
    //PC 程序
    #if _MSC_VER==1200        //VC++6.0
        #include "vc6/StdAfx6.h"
    #elif _MSC_VER==1300      //VC++7.0(VC2002)
        #include "vc2002/StdAfx2002.h"
    #elif _MSC_VER==1310      //VC++7.1(VC2003)
        #include "vc2003/StdAfx2003.h"
    #elif _MSC_VER==1400      //VC++8.0(VC2005)
        #include "vc2005/StdAfx2005.h"
    #elif _MSC_VER==1500      //VC++9.0(VC2008)
        #include "vc2008/StdAfx2008.h"
    #elif _MSC_VER==1600      //VC++10.0(VC2010)
        #include "vc2010/StdAfx2010.h"
    #elif _MSC_VER==1700      //VC++11.0(VC2012)
        #include "vc2012/StdAfx2012.h"
    #elif _MSC_VER==1800      //VC++12.0(VC2013)
        #include "vc2013/StdAfx2013.h"        
    #endif
#endif

#include "ON_WM_XXX.h"        //升级宏 ON_WM_XXX()

//包含自定义头文件--------------------------------------------------------------
#include "../src/StdAfxUser.h"
