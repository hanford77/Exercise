//mfcSocket.h
#pragma once

#ifndef _WIN32_WCE
    #include <locale.h>
#endif

#include "resource.h"

class CDlgMain;
class CmfcSocketApp : public CWinApp
{
public:
    CmfcSocketApp();
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CmfcSocketApp)
	public:
    virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
// Implementation
    //{{AFX_MSG(CmfcSocketApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    CDlgMain*m_pMain;
};

extern CmfcSocketApp theApp;
