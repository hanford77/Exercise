//GRUB4DOS_REN.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CGRUB4DOS_RENApp : public CWinApp
{
public:
    CGRUB4DOS_RENApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGRUB4DOS_RENApp)
	public:
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CGRUB4DOS_RENApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
