//StdAfxUser.h
#pragma once

#pragma warning(disable : 4786)

#include <commctrl.h>
#include <string>

#ifdef _UNICODE
    typedef std::wstring  tstring;
#else
    typedef std::string   tstring;
#endif
