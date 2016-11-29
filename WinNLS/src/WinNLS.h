//WinNLS.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CWinNLSApp : public CWinApp
{
public:
    CWinNLSApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWinNLSApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CWinNLSApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
