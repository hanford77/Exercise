//Mine.h
#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CMineApp : public CWinApp
{
public:
    CMineApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMineApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CMineApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
