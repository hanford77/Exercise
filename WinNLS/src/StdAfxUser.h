//StdAfxUser.h
#pragma once

#pragma warning(disable : 4786)

#include <map>
#include <vector>

/******************************************************************************\
必须使用 Unicode，因为
1、GetLocaleInfoA 获取的一些信息是乱码
2、CDlgLocale::OutputToFile 必须使用 Unicode
\******************************************************************************/
#ifndef _UNICODE
#error must use unicode
#endif
