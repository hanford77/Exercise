//TestSxS.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CTestSxSApp : public CWinApp
{
public:
    CTestSxSApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTestSxSApp)
	public:
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CTestSxSApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
