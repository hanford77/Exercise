//DlgMain.cpp
#include "stdafx.h"
#include "resource.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
:CDialog(CDlgMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_IconType		=	2;
	m_Grade			=	0;
	m_hOldBmpMem	=	NULL;
	m_hOldBmpFore	=	NULL;
	m_hOldBmpBack	=	NULL;
	m_bMusic		=	FALSE;
	m_bSound		=	TRUE;
	GetModuleFileName(NULL,m_sAppPath.GetBuffer(MAX_PATH),MAX_PATH);
	m_sAppPath.ReleaseBuffer();
	m_sAppPath=m_sAppPath.Left(1 + m_sAppPath.ReverseFind(_T('\\')));
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
	//{{AFX_MSG_MAP(CDlgMain)
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_BEGIN_0, OnBegin0)
	ON_COMMAND(IDM_BEGIN_1, OnBegin1)
	ON_COMMAND(IDM_BEGIN_2, OnBegin2)
	ON_COMMAND(IDM_BEGIN_3, OnBegin3)
	ON_COMMAND(IDM_BEGIN_DEF, OnBeginDef)
	ON_COMMAND(IDM_CHANGE, OnChange)
	ON_COMMAND(IDM_PROMPT, OnPrompt)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_SOUND, OnSound)
	ON_COMMAND(IDM_MUSIC, OnMusic)
	ON_COMMAND(IDM_UNDO, OnUndo)
	ON_COMMAND(IDM_REDO, OnRedo)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDM_ICON_0,IDM_ICON_4,OnIcon)
	ON_COMMAND_RANGE(IDM_MOVE_00,IDM_MOVE_00 + CLinkMatrix::MOVE_COUNT - 1,OnMoveMode)
	ON_MESSAGE(MM_MCINOTIFY, OnMciNotify)
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog()
{
	CDialog::OnInitDialog();
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	srand(time(NULL) + GetTickCount());
	m_Midi.SetOwner(m_hWnd);
	BeginGame(!LoadFromFile(m_sAppPath + AfxGetAppName() + _T(".ini")));
	if(m_bMusic)
	{
		FindSongs();
		PlayMusic();
	}
	return TRUE;
}

void CDlgMain::Redraw(BOOL bDrawMem)
{
	int	cxPic	=	(m_Matrix.m_iCols + 2) * FRONTWIDTH + 5;
	int	cyPic	=	(m_Matrix.m_iRows + 2) * FRONTHEIGHT + 5;
	if(bDrawMem)
	{//更新内存图片
		const int yBack	=	BKHEIGHT * 5;
		m_dcMem.FillSolidRect(0,0,cxPic,cyPic,BKCOLOR);
		int iIndex;
		for(int y=1;y<=m_Matrix.m_iRows;y++)
		{
			for(int x=1;x<=m_Matrix.m_iCols;x++)
			{
				iIndex	=	m_Matrix(x,y) - 1;
				if(iIndex >= 0)
				{
					m_dcMem.BitBlt(x * FRONTWIDTH	 ,y * FRONTHEIGHT	 ,BKWIDTH	  ,BKHEIGHT		 ,&m_dcIconBack,0				,yBack					,SRCCOPY);
					m_dcMem.BitBlt(x * FRONTWIDTH + 2,y * FRONTHEIGHT + 6,FRONTWIDTH-2,FRONTHEIGHT-12,&m_dcIconFore,m_IconType*78+39,iIndex*(FRONTHEIGHT-12),SRCAND);
					m_dcMem.BitBlt(x * FRONTWIDTH + 2,y * FRONTHEIGHT + 6,FRONTWIDTH-2,FRONTHEIGHT-12,&m_dcIconFore,m_IconType*78   ,iIndex*(FRONTHEIGHT-12),SRCPAINT);
				}
			}
		}
		{//画选中的牌
			int&	x	=	m_Matrix.m_xSel;
			int&	y	=	m_Matrix.m_ySel;
			if(x > 0 && x <= m_Matrix.m_iCols
			&& y > 0 && y <= m_Matrix.m_iRows
			&& m_Matrix(x,y))
			{
				RECT r;
				r.left		=	x * FRONTWIDTH;
				r.top		=	y * FRONTHEIGHT;
				r.right		=	r.left + FRONTWIDTH;
				r.bottom	=	r.top + FRONTHEIGHT;
				InvertRect(m_dcMem.m_hDC,&r);
			}
		}
		HGDIOBJ	hOldFont=::SelectObject(m_dcMem.m_hDC,GetFont()->m_hObject);
		m_dcMem.SetTextColor(RGB(0,255,0));
		m_dcMem.TextOut(3,3,_T("消牌模式：") + m_Matrix.GetMoveModeStr());
		::SelectObject(m_dcMem.m_hDC,hOldFont);
	}
	CClientDC dc(this);
	dc.BitBlt(0,0,cxPic,cyPic,&m_dcMem,0,0,SRCCOPY);
}

void CDlgMain::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int	x	=	point.x / FRONTWIDTH;
	int	y	=	point.y / FRONTHEIGHT;

	if(x > 0 && x <= m_Matrix.m_iCols
	&& y > 0 && y <= m_Matrix.m_iRows
	&& m_Matrix(x,y))
	{
		if(m_Matrix.m_xSel < 1)
		{
			m_Matrix.m_xSel	=	x;
			m_Matrix.m_ySel	=	y;
		}
		else
		{
			if((m_Matrix.m_xSel != x || m_Matrix.m_ySel != y))
			{
				if(m_Matrix(x,y)==m_Matrix(m_Matrix.m_xSel,m_Matrix.m_ySel))
				{
					CLinkPath path;
					if(m_Matrix.FindPath(m_Matrix.m_xSel,m_Matrix.m_ySel,x,y,&path))
					{
						CUndo::CState*pState=	new CUndo::CState();
						pState->m_path		=	path;
						m_Matrix.RemoveIcon(m_Matrix.m_xSel,m_Matrix.m_ySel,x,y);
						DrawPath(path,300);
						switch(m_Matrix.GetHelp(&path))
						{
						case -1:
							delete pState;
							AfxMessageBox(_T("恭喜过关!"));
							m_Matrix.SetMoveMode(m_Matrix.m_iMoveMode + 1);
							BeginGame();
							return;
						case 0:		//无牌可消,程序将重新洗牌
							OnChange();
							pState->m_Matrix	=	m_Matrix;
							m_Undo.AddState(pState);
							UpdateMenu();
							PlaySound(IDR_WAVE_XIPAI);
							return;
						default:
							pState->m_Matrix	=	m_Matrix;
							m_Undo.AddState(pState);
							UpdateMenu();
							PlaySound(IDR_WAVE_OK);
						}
					}
					else
					{
//						m_Matrix.m_xSel	=	x;
//						m_Matrix.m_ySel	=	y;
						m_Matrix.m_xSel	=
						m_Matrix.m_ySel	=	0;
						PlaySound(IDR_WAVE_OH);
					}
				}
				else
				{
//					m_Matrix.m_xSel	=	x;
//					m_Matrix.m_ySel	=	y;
					m_Matrix.m_xSel	=
					m_Matrix.m_ySel	=	0;
					PlaySound(IDR_WAVE_ERR);
				}
			}
		}
		Redraw();
	}
}

BOOL CDlgMain::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYUP)
	{
		switch(pMsg->wParam)
		{
		case VK_F1:
			OnBegin0();
			break;
		case VK_F2:
			OnBegin1();
			break;
		case VK_F3:
			OnBegin2();
			break;
		case VK_F4:
			OnBegin3();
			break;
		case VK_F5:
			OnPrompt();
			break;
		case VK_F6:
			OnChange();
			break;
		case VK_F7:
			if(GetKeyState(VK_SHIFT) < 0)
			{
				m_IconType--;
			}
			else
			{
				m_IconType++;
			}
			m_IconType	%=	5;
			if(m_IconType < 0)
			{
				m_IconType += 5;
			}
			UpdateMenu();
			Redraw();
			break;
		case VK_F8:
			if(GetKeyState(VK_SHIFT) < 0)
			{
				m_Matrix.SetMoveMode(m_Matrix.m_iMoveMode - 1);
			}
			else
			{
				m_Matrix.SetMoveMode(m_Matrix.m_iMoveMode + 1);
			}
			UpdateMenu();
			Redraw();
			break;
		case 'Z':
			if(GetKeyState(VK_CONTROL) < 0)
			{
				OnUndo();
			}
			break;
		case 'Y':
			if(GetKeyState(VK_CONTROL) < 0)
			{
				OnRedo();
			}
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMain::OnOK() 
{
}

void CDlgMain::OnCancel() 
{
}

void CDlgMain::OnClose() 
{	
	CDialog::OnCancel();
}

void CDlgMain::OnRButtonDown(UINT nFlags, CPoint point) 
{
	OnMouseMove(MK_RBUTTON,point);
}

void CDlgMain::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(nFlags & MK_RBUTTON)
	{
		int x=point.x / FRONTWIDTH;
		int y=point.y / FRONTHEIGHT;

		if(x > 0 && x <= m_Matrix.m_iCols
		&& y > 0 && y <= m_Matrix.m_iRows
		&& m_Matrix(x,y))
		{
			Redraw();
			CLinkPath	path;
			if(m_Matrix.GetHelp(x,y,&path))
			{
				DrawPath(path,0,RGB(0,255,0));
			}
		}
	}
}

void CDlgMain::DrawPath(CLinkPath&path,DWORD dwSleep,COLORREF clDraw)
{
	CClientDC	dc(this);
	CPen		pen(PS_SOLID,5,clDraw);
	CPen		*pOldPen	=	dc.SelectObject(&pen);
	int			i,c			=	path.m_Count;
	for(i=0;i<c;i++)
	{
		if(i)
		{
			dc.LineTo(path.m_x[i] * FRONTWIDTH + FRONTWIDTH / 2
					 ,path.m_y[i] * FRONTHEIGHT + FRONTHEIGHT / 2);
		}
		else
		{
			dc.MoveTo(path.m_x[i] * FRONTWIDTH + FRONTWIDTH / 2
					 ,path.m_y[i] * FRONTHEIGHT + FRONTHEIGHT / 2);

		}							
	}
	dc.SelectObject(pOldPen);
	Sleep(dwSleep);
}

void CDlgMain::OnChange() 
{
	m_Matrix.ChangeLayout();
	Redraw();
}

void CDlgMain::OnPrompt() 
{
	CLinkPath	path;
	if(m_Matrix.GetHelp(&path) > 0)
	{
		DrawPath(path,0,RGB(0,255,0));
	}
}

void CDlgMain::OnExit() 
{
	OnClose();	
}

void CDlgMain::UpdateMenu()
{
	m_IconType	%=	5;
	if(m_IconType < 0)
	{
		m_IconType += 5;
	}
	CMenu*pMenu	=	GetMenu();
	pMenu->CheckMenuRadioItem(IDM_ICON_0,IDM_ICON_4,IDM_ICON_0 + m_IconType,MF_BYCOMMAND);
	pMenu->CheckMenuRadioItem(IDM_MOVE_00,IDM_MOVE_00 + CLinkMatrix::MOVE_COUNT - 1,IDM_MOVE_00 + m_Matrix.m_iMoveMode,MF_BYCOMMAND);
	pMenu->CheckMenuItem(IDM_MUSIC,(m_bMusic ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	pMenu->CheckMenuItem(IDM_SOUND,(m_bSound ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	pMenu->EnableMenuItem(IDM_UNDO,(m_Undo.CanUndo() ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
	pMenu->EnableMenuItem(IDM_REDO,(m_Undo.CanRedo() ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
}

void CDlgMain::OnIcon(UINT uID)
{
	m_IconType	=	uID - IDM_ICON_0;
	UpdateMenu();
	Redraw();
}

void CDlgMain::OnBegin0() 
{
	m_Grade		=	0;
	BeginGame();
}

void CDlgMain::OnBegin1() 
{
	m_Grade		=	1;
	BeginGame();
}

void CDlgMain::OnBegin2() 
{
	m_Grade		=	2;
	BeginGame();
}

void CDlgMain::OnBegin3() 
{
	m_Grade		=	3;
	BeginGame();
}

void CDlgMain::OnBeginDef() 
{
	if(IDOK==m_dlgDef.DoModal())
	{
		m_Grade		=	4;
		BeginGame();
	}
}

void CDlgMain::BeginGame(BOOL bInitMatrix)
{
	if(bInitMatrix)
	{
		switch(m_Grade)
		{
		case 0:
			m_Matrix.Init(7,12,21);
			break;
		case 1:
			m_Matrix.Init(8,14,28);
			break;
		case 2:
			m_Matrix.Init(9,16,36);
			break;
		case 3:
			m_Matrix.Init(10,18,42);
			break;
		case 4:
			m_Matrix.Init(m_dlgDef.m_iRows,m_dlgDef.m_iCols,m_dlgDef.m_iIcons);
			break;
		}
	}
	m_Undo.Empty();
	CUndo::CState*pState=	new CUndo::CState();
	pState->m_Matrix	=	m_Matrix;
	m_Undo.AddState(pState,TRUE);

	CClientDC	dc(this);
	RECT		r;
	r.left		=	0;
	r.top		=	0;
	r.right		=	(m_Matrix.m_iCols + 2) * FRONTWIDTH + 5;
	r.bottom	=	(m_Matrix.m_iRows + 2) * FRONTHEIGHT + 5;
	
	if(NULL==m_hOldBmpFore)
	{
		m_bmpIconFore.LoadBitmap(IDB_BMP_ICON_FORE);
		m_dcIconFore.CreateCompatibleDC(&dc);
		m_hOldBmpFore	=	::SelectObject(m_dcIconFore.m_hDC,m_bmpIconFore.m_hObject);
	}
	if(NULL==m_hOldBmpBack)
	{
		m_bmpIconBack.LoadBitmap(IDB_BMP_ICON_BACK);
		m_dcIconBack.CreateCompatibleDC(&dc);
		m_hOldBmpBack	=	::SelectObject(m_dcIconBack.m_hDC,m_bmpIconBack.m_hObject);
	}
	if(m_hOldBmpMem)
	{
		::SelectObject(m_dcMem.m_hDC,m_hOldBmpMem);
		m_bmpMem.DeleteObject();
		m_bmpMem.CreateCompatibleBitmap(&dc,r.right,r.bottom);
		::SelectObject(m_dcMem.m_hDC,m_bmpMem.m_hObject);
	}
	else
	{
		m_dcMem.CreateCompatibleDC(&dc);
		m_bmpMem.CreateCompatibleBitmap(&dc,r.right,r.bottom);
		m_hOldBmpMem = ::SelectObject(m_dcMem.m_hDC,m_bmpMem.m_hObject);
	}

	ClientToScreen(&r);
	AdjustWindowRectEx(&r,GetWindowLong(m_hWnd,GWL_STYLE),TRUE,GetWindowLong(m_hWnd,GWL_EXSTYLE));
	MoveWindow(&r,TRUE);
	UpdateMenu();
	Redraw();
}

void CDlgMain::OnMoveMode(UINT uID)
{
	m_Matrix.SetMoveMode(uID - IDM_MOVE_00);
	UpdateMenu();
	Redraw();
}

void CDlgMain::OnDestroy() 
{
	m_Midi.Close();
	if(m_hOldBmpFore)
	{
		::SelectObject(m_dcIconFore.m_hDC,m_hOldBmpFore);
	}
	if(m_hOldBmpBack)
	{
		::SelectObject(m_dcIconBack.m_hDC,m_hOldBmpBack);
	}
	if(m_hOldBmpMem)
	{
		::SelectObject(m_dcMem.m_hDC,m_hOldBmpMem);
	}
	SaveToFile(m_sAppPath + AfxGetAppName() + _T(".ini"));
	CDialog::OnDestroy();	
}

BOOL CDlgMain::OnEraseBkgnd(CDC* pDC) 
{
	Redraw(FALSE);
	return TRUE;
}

void CDlgMain::OnAbout() 
{
	CDialog dlg(IDD_ABOUTBOX);
	dlg.DoModal();
}

LRESULT CDlgMain::OnMciNotify(WPARAM wp,LPARAM lp)
{
	switch(wp) 
	{
	case MCI_NOTIFY_SUCCESSFUL:
	case MCI_NOTIFY_FAILURE:
		PlayMusic();	//更换歌曲
		break;
	}	
	return 0;
}

void CDlgMain::FindSongs()
{
	m_arrSong.SetSize(0,256);
	WIN32_FIND_DATA	fdData;
	HANDLE			hFind	=	FindFirstFile(m_sAppPath + _T("Music\\*.*"),&fdData);

	if(hFind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if((fdData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)==0)
			{
				m_arrSong.Add(fdData.cFileName);
			}
		}while(FindNextFile(hFind,&fdData));
		FindClose(hFind);
	}
}

void CDlgMain::OnSound() 
{
	m_bSound	=	!m_bSound;
	UpdateMenu();
}

void CDlgMain::PlaySound(UINT uID)
{
	if(m_bSound)
	{
		::PlaySound(MAKEINTRESOURCE(uID),
			AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}
}

void CDlgMain::OnMusic() 
{
	m_bMusic	=	!m_bMusic;
	UpdateMenu();
	if(m_bMusic)
	{
		FindSongs();
		PlayMusic();
	}
	else
	{
		m_Midi.Close();
	}
}

void CDlgMain::PlayMusic()
{
	if(m_bMusic)
	{
		int	count;
		int iSel;
		while(1)
		{
			count=m_arrSong.GetSize();
			if(count < 1)
			{
				break;
			}
			iSel	=	rand() % count;
			if(m_Midi.Open(m_sAppPath + _T("Music\\") + m_arrSong[iSel]))
			{
				m_Midi.Play();
				break;
			}
			m_arrSong.RemoveAt(iSel);
		}
	}
}

BOOL CDlgMain::SaveToFile(LPCTSTR szFile)
{
	CFile f;
	if(!f.Open(szFile,CFile::modeCreate|CFile::modeWrite))
	{
		return FALSE;
	}
	DWORD dwVer=1;	//版本
	f.Write(&dwVer,sizeof(dwVer));
	f.Write(&m_IconType,sizeof(m_IconType));
	f.Write(&m_Grade,sizeof(m_Grade));
	f.Write(&m_bSound,sizeof(m_bSound));
	f.Write(&m_bMusic,sizeof(m_bMusic));
	f.Write(&m_dlgDef.m_iRows,sizeof(m_dlgDef.m_iRows));
	f.Write(&m_dlgDef.m_iCols,sizeof(m_dlgDef.m_iCols));
	f.Write(&m_dlgDef.m_iIcons,sizeof(m_dlgDef.m_iIcons));
	f.Write(&m_Matrix.m_iRows,sizeof(m_Matrix.m_iRows));
	f.Write(&m_Matrix.m_iCols,sizeof(m_Matrix.m_iCols));
	f.Write(m_Matrix.m_pMatrix,sizeof(ICONDATA)*(m_Matrix.m_iRows + 2)*(m_Matrix.m_iCols + 2));
	f.Write(&m_Matrix.m_xSel,sizeof(m_Matrix.m_xSel));
	f.Write(&m_Matrix.m_ySel,sizeof(m_Matrix.m_ySel));
	f.Write(&m_Matrix.m_iMoveMode,sizeof(m_Matrix.m_iMoveMode));
	f.Close();
	return TRUE;
}

BOOL CDlgMain::LoadFromFile(LPCTSTR szFile)
{
	CFile f;
	if(!f.Open(szFile,CFile::modeRead | CFile::shareDenyWrite))
	{
		return FALSE;
	}
	DWORD dwVer=0;	//版本
	f.Read(&dwVer,sizeof(dwVer));
	f.Read(&m_IconType,sizeof(m_IconType));
	f.Read(&m_Grade,sizeof(m_Grade));
	f.Read(&m_bSound,sizeof(m_bSound));
	f.Read(&m_bMusic,sizeof(m_bMusic));
	f.Read(&m_dlgDef.m_iRows,sizeof(m_dlgDef.m_iRows));
	f.Read(&m_dlgDef.m_iCols,sizeof(m_dlgDef.m_iCols));
	f.Read(&m_dlgDef.m_iIcons,sizeof(m_dlgDef.m_iIcons));
	f.Read(&m_Matrix.m_iRows,sizeof(m_Matrix.m_iRows));
	f.Read(&m_Matrix.m_iCols,sizeof(m_Matrix.m_iCols));
	m_Matrix.Init(m_Matrix.m_iRows,m_Matrix.m_iCols);
	f.Read(m_Matrix.m_pMatrix,sizeof(ICONDATA)*(m_Matrix.m_iRows + 2)*(m_Matrix.m_iCols + 2));
	f.Read(&m_Matrix.m_xSel,sizeof(m_Matrix.m_xSel));
	f.Read(&m_Matrix.m_ySel,sizeof(m_Matrix.m_ySel));
	f.Read(&m_Matrix.m_iMoveMode,sizeof(m_Matrix.m_iMoveMode));
	f.Close();
	return TRUE;
}

void CDlgMain::OnUndo() 
{
	if(m_Undo.CanUndo())
	{
		CLinkPath	path;
		CUndo::CState*pState=m_Undo.Undo(&path);
		m_Matrix	=	pState->m_Matrix;
		UpdateMenu();
		Redraw();
		if(path.m_Count)
		{
			DrawPath(path,0,RGB(255,0,0));
		}
	}
}

void CDlgMain::OnRedo() 
{
	if(m_Undo.CanRedo())
	{
		CLinkPath	path;
		CUndo::CState*pState=m_Undo.Redo(&path);
		m_Matrix	=	pState->m_Matrix;
		UpdateMenu();
		Redraw();
		if(path.m_Count)
		{
			DrawPath(path,0,RGB(255,0,0));
		}
	}
}