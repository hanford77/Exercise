//SolveEquation.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CSolveEquationApp : public CWinApp
{
public:
    CSolveEquationApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSolveEquationApp)
	public:
    virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CSolveEquationApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
