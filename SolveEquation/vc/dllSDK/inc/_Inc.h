//_Inc.h
/******************************************************************************\
客户端程序动态连接 SolveEquationDll 时，请包含此头文件
\******************************************************************************/
#pragma once

//导入一般的函数、类
#define SolveEquationDllI __declspec(dllimport)
//导入含有成员模板函数的类
#define SolveEquationDllT

#include "+inc.h"
