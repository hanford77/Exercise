//DlgMain.h
#pragma once

#include "LinkMatrix.h"
#include "DlgDef.h"
#include "Midi.h"
#include "Undo.h"

class CDlgMain : public CDialog
{
public:
	CDlgMain(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CDlgMain)
	enum { IDD = IDD_MAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMain)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBegin0();
	afx_msg void OnBegin1();
	afx_msg void OnBegin2();
	afx_msg void OnBegin3();
	afx_msg void OnBeginDef();
	afx_msg void OnChange();
	afx_msg void OnPrompt();
	afx_msg void OnExit();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAbout();
	afx_msg void OnSound();
	afx_msg void OnMusic();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	//}}AFX_MSG
	afx_msg void	OnIcon(UINT uID);
	afx_msg void	OnMoveMode(UINT uID);
	afx_msg LRESULT	OnMciNotify(WPARAM wp,LPARAM lp);
	DECLARE_MESSAGE_MAP()
private:
	void	Redraw(BOOL bDrawMem=TRUE);
	void	DrawPath(CLinkPath&path,DWORD dwSleep=0,COLORREF clDraw=RGB(255,128,0));
	void	BeginGame(BOOL bInitMatrix=TRUE);
	void	UpdateMenu();
	void	FindSongs();
	void	PlaySound(UINT uID);
	void	PlayMusic();
	BOOL	SaveToFile(LPCTSTR szFile);
	BOOL	LoadFromFile(LPCTSTR szFile);
private:
	//
	CDC				m_dcMem;
	CBitmap			m_bmpMem;
	HGDIOBJ			m_hOldBmpMem;
	//
	CDC				m_dcIconFore;
	CBitmap			m_bmpIconFore;
	HGDIOBJ			m_hOldBmpFore;
	//
	CDC				m_dcIconBack;
	CBitmap			m_bmpIconBack;
	HGDIOBJ			m_hOldBmpBack;
	//	
	CLinkMatrix		m_Matrix;
	int				m_IconType;		//显示的图案 0-4
	int				m_Grade;		//级别
	BOOL			m_bSound;		//是否播放音乐
	BOOL			m_bMusic;		//是否播放音效
	CDlgDef			m_dlgDef;
	CMidi			m_Midi;
	CString			m_sAppPath;		//应用程序所在目录
	CStringArray	m_arrSong;		//所有的歌曲名
	CUndo			m_Undo;
};
