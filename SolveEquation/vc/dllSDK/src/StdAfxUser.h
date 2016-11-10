//StdAfxUser.h
#pragma once

#if defined(_LIB)   //编译生成静态库
    //导出一般的函数、类
    #define SolveEquationDllI
#else               //编译生成动态库
    //导出一般的函数、类
    #define SolveEquationDllI __declspec(dllexport)
#endif

#include "../inc/+inc.h"
