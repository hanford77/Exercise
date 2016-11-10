//DlgMain.h
#pragma once

#include "DataStruct.h"
#include "ButtonBmp.h"

class CDlgMain : public CDialog
{
public:
    CDlgMain(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgMine)
    enum { IDD = IDD_MINE_DIALOG };
    CButtonBmp    m_btn;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgMine)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CDlgMine)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnClose();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnExit();
    afx_msg void OnAbout();
    afx_msg void OnBegin();
    afx_msg void OnHelponce();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnGrade0();
    afx_msg void OnProtect();
    afx_msg void OnGrade1();
    afx_msg void OnGrade2();
    afx_msg void OnUserdefine();
    afx_msg void OnMark();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnBtn();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnHero();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    void UpdateWorkedTimes();
    void UpdateDisMines();
    void UpdateMenuItemChecked();
    void CheckIniInfo();
    void SaveIniInfo();
    void LoadIniInfo();
    BYTE Total(int i,int j,BYTE filter,BYTE& choice, BYTE& inside);
    void ResizeWindow();
    void DrawTheBlock(int r,int c);
    BOOL GetRowCol(int x,int y,int& r,int& c);
private:
    void UpdateMineArea();
    void DrawAroundBlocks(int r,int c,BOOL fRestore);
    void DrawAroundOneBlock(int r,int c,BOOL fRestore);
    void OpenTheBlock(int i,int j);
    void ActionLDown(CPoint& pt);
    void ActionLMove(CPoint& pt);
    void ActionLUp(CPoint& pt);
    void ActionRDown(CPoint& pt);
    void ActionLRDown(CPoint& pt);
    void ActionLRMove(CPoint& pt);
    void ActionLRUp(CPoint& pt);
    
    int     m_x0,m_y0;
    int     m_Rows,m_Cols;
    HBITMAP m_hBmp1,m_hBmp2,m_hBmp3;
    HDC     m_hMem1,m_hMem2,m_hMem3;
    BLOCK*  m_block;
    CBrush  m_brush0;            //窗口背景刷子
    HACCEL  m_hAccTable;        //快捷键句柄
    int     m_iStatus;                //当前状态
    int     m_iOpenedBlocks;  //已经打开的块数    
    INIINFO m_IniInfo;    //初始化信息
    int     m_iWorkedTimes;   //已经工作时间
    int     m_iDisMines;      //显示的雷数(剩余的雷数)
    int     m_iClientWidth;   //客户区宽度
    BOOL    m_fMouseCapture;
    int     m_iMouseStatus;
    int     m_PrevRow,m_PrevCol;
    BOOL    m_fPrevIsGood;
};
