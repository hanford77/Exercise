//DisableSxS.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CDisableSxSApp : public CWinApp
{
public:
    CDisableSxSApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDisableSxSApp)
	public:
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CDisableSxSApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
