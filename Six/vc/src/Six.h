// Six.h : main header file for the SIX application
//

#if !defined(AFX_SIX_H__3099BD15_42F4_49A4_B3DC_9FEFEFA1EF92__INCLUDED_)
#define AFX_SIX_H__3099BD15_42F4_49A4_B3DC_9FEFEFA1EF92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSixApp:
// See Six.cpp for the implementation of this class
//

class CSixApp : public CWinApp
{
public:
	CSixApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSixApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSixApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIX_H__3099BD15_42F4_49A4_B3DC_9FEFEFA1EF92__INCLUDED_)
