//WordBlogAccount.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CWordBlogAccountApp : public CWinApp
{
public:
    CWordBlogAccountApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWordBlogAccountApp)
	public:
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CWordBlogAccountApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
