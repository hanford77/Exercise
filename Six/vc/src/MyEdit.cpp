// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Six.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{	

}

CMyEdit::~CMyEdit()
{
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_RETURN)
	{
		int ID;
		CEdit *txt;
		ID=this->GetDlgCtrlID(); 
		if(ID>=IDC_D0 && ID<IDC_D20)
		{
			txt=(CEdit *)GetParent()->GetDlgItem(ID+1);
			txt->SetSel(0,-1); 
			txt->SetFocus(); 
		}
    else if(ID==IDC_D20)
		{
			txt=(CEdit *)GetParent()->GetDlgItem(IDC_L0);
			txt->SetSel(0,-1); 
			txt->SetFocus(); 
		}
		else if(ID>=IDC_L0 && ID<IDC_L20)
		{
			txt=(CEdit *)GetParent()->GetDlgItem(ID+1);
			txt->SetSel(0,-1); 
			txt->SetFocus(); 
		}
		else if(ID==IDC_L20)
		{
			txt=(CEdit *)GetParent()->GetDlgItem(IDC_D0);
			txt->SetSel(0,-1); 
			txt->SetFocus(); 
		}
	}
	else
	  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL fOK=FALSE;
	if(nChar>=(UINT)'0' && nChar<=(UINT)'9')
		fOK=TRUE;
	else if(nChar==(UINT)'.')
		fOK=TRUE;
  else if(nChar==8)
		fOK=TRUE;
	if(fOK)
	  CEdit::OnChar(nChar, nRepCnt, nFlags);
}
