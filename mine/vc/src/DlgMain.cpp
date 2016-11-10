//DlgMain.cpp
#include "stdafx.h"
#include "Mine.h"
#include "DlgMain.h"
#include "DlgUserDef.h"
#include "DlgHero.h"
#include "DlgName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgMain::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgMine)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_x0        =   12;
    m_y0        =   55;
    m_Rows      =   8;//16;
    m_Cols      =   8;//30;
    m_hBmp1     =   ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1));
    m_hBmp2     =   ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP2));
    m_hMem1     =   ::CreateCompatibleDC(NULL);
    m_hMem2     =   ::CreateCompatibleDC(NULL);
    ::SelectObject(m_hMem1,m_hBmp1);
    ::SelectObject(m_hMem2,m_hBmp2);
    m_brush0.CreateSolidBrush(RGB(0xc0,0xc0,0xc0));
    m_hAccTable     =   ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR1)); 
    m_iStatus       =   STA_NONE;
    m_iOpenedBlocks =   0;
    m_fMouseCapture =   FALSE;
    m_iMouseStatus  =   0;
    m_block         =   NULL;
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMine)
    DDX_Control(pDX, IDC_BTN, m_btn);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
    //{{AFX_MSG_MAP(CDlgMine)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
    ON_WM_CTLCOLOR()
    ON_COMMAND(IDM_EXIT, OnExit)
    ON_COMMAND(IDM_ABOUT, OnAbout)
    ON_COMMAND(IDM_BEGIN, OnBegin)
    ON_COMMAND(IDM_HELPONCE, OnHelponce)
    ON_WM_TIMER()
    ON_COMMAND(IDM_GRADE0, OnGrade0)
    ON_COMMAND(IDM_PROTECT, OnProtect)
    ON_COMMAND(IDM_GRADE1, OnGrade1)
    ON_COMMAND(IDM_GRADE2, OnGrade2)
    ON_COMMAND(IDM_USERDEFINE, OnUserdefine)
    ON_COMMAND(IDM_MARK, OnMark)
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(IDC_BTN, OnBtn)
    ON_WM_MOUSEMOVE()
    ON_COMMAND(IDM_HERO, OnHero)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    ::SetClassLong(GetSafeHwnd(),GCL_STYLE,::GetClassLong(GetSafeHwnd(),GCL_STYLE) & ~CS_DBLCLKS);
    RECT r;
    LoadIniInfo();
    UpdateMenuItemChecked();
    GetWindowRect(&r);
    r.right+=m_IniInfo.Xpos-r.left;
    r.left =m_IniInfo.Xpos;
    r.bottom+=m_IniInfo.Ypos-r.top;
    r.top =m_IniInfo.Ypos;
    MoveWindow(&r,FALSE);
    OnBegin();
    SetTimer(IDC_TIMER,1000,NULL);
    return TRUE;
}

void CDlgMain::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CPaintDC dc(this);
        int        i;
        RECT    r;
        GetClientRect(&r);
        CPen *pOldPen,p1(PS_SOLID,0,RGB(255,255,255));
        CPen p2(PS_SOLID,0,0x808080);
        pOldPen=dc.SelectObject(&p1);
        for(i=0;i<3;i++)
        {
            //白色外边线
            dc.MoveTo(i,r.bottom-i-2);
            dc.LineTo(i,i);
            dc.LineTo(r.right-i-1,i);
            //白色下边线
            dc.MoveTo(i+10,r.bottom-i-10);
            dc.LineTo(r.right-i-10,r.bottom-i-10);
            dc.LineTo(r.right-i-10,i+52);
        }
        for(i=0;i<2;i++)
        {
            //白色上边线
            dc.MoveTo(i+10,45-i);
            dc.LineTo(r.right-i-10,45-i);
            dc.LineTo(r.right-i-10,i+9);
        }
        //        
        dc.MoveTo(17,39);
        dc.LineTo(56,39);
        dc.LineTo(56,15); 
        //
        dc.MoveTo(r.right-56,39);
        dc.LineTo(r.right-17,39);
        dc.LineTo(r.right-17,15); 
        dc.SelectObject(&p2);
        for(i=0;i<3;i++)
        {
            //灰色外边线
            dc.MoveTo(i+1,r.bottom-i-1);
            dc.LineTo(r.right-i-1,r.bottom-i-1);
            dc.LineTo(r.right-i-1,i);
            //灰色下边线
            dc.MoveTo(i+9,r.bottom-i-11);
            dc.LineTo(i+9,i+52);
            dc.LineTo(r.right-i-10,i+52);
        }
        for(i=0;i<2;i++)
        {
            //灰色上边线
            dc.MoveTo(i+9,44-i);
            dc.LineTo(i+9,i+9);
            dc.LineTo(r.right-i-10,i+9);
        }
        //
        dc.MoveTo(16,38);
        dc.LineTo(16,15);
        dc.LineTo(56,15); 
        //
        dc.MoveTo(r.right-57,38);
        dc.LineTo(r.right-57,15);
        dc.LineTo(r.right-17,15); 
        dc.SelectObject(pOldPen);
        //
        UpdateMineArea();
        //数码
        UpdateDisMines();
        UpdateWorkedTimes();
    }
}

HCURSOR CDlgMain::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CDlgMain::OnOK() 
{
}

void CDlgMain::OnCancel() 
{
}

void CDlgMain::OnClose() 
{
    KillTimer(IDC_TIMER);    
    ::DeleteDC(m_hMem1);
    ::DeleteObject(m_hBmp1);
    ::DeleteDC(m_hMem2);
    ::DeleteObject(m_hBmp2);
    if(m_block)
    {
        delete[] m_block;
        m_block =   NULL;
    }
    SaveIniInfo();
    CDialog::OnCancel();
}

BOOL CDlgMain::GetRowCol(int x, int y, int &r, int &c)
{
    if(x<m_x0 || y<m_y0)return FALSE;
    r=(y-m_y0)>>4;
    c=(x-m_x0)>>4;
    if(r>m_Rows-1 || c>m_Cols-1)return FALSE;
    return TRUE;
}

void CDlgMain::DrawTheBlock(int r, int c)
{
    int k=0,idx=r*m_Cols+c;
    HDC hdc;
    switch(m_iStatus)
    {
        //case STA_NONE:            //还没有开始挖雷
            //k=0;
            //break;
        case STA_WORKING:   //正在挖雷
            if(m_block[idx].Flag & conDiscovered)
                k=15-m_block[idx].Totalmines;
            else if(m_block[idx].Flag & conFounded)
              k=1;
            else if(m_block[idx].Flag & conMarked)
                k=2;
            break;
        case STA_OK:                //已经挖好
            if(m_block[idx].Flag & conDiscovered)
                k=15-m_block[idx].Totalmines;
            else
                k=1;
            break;
        case STA_DIED:      //死亡
            if(m_block[idx].Flag & conDiscovered)
            {
                if(m_block[idx].Flag & conIsMine)
                  k=3;
                else
                  k=15-m_block[idx].Totalmines;
            }            
            else if(m_block[idx].Flag & conFounded)
            {
                if(m_block[idx].Flag & conIsMine)
                  k=1;
                else
                  k=4;
            }
            else if(m_block[idx].Flag & conIsMine)
                k=5;
            break;
    }
    hdc=::GetDC(GetSafeHwnd());
    ::BitBlt(hdc,m_x0+c*16,m_y0+r*16,16,16,m_hMem1,0,k*16,SRCCOPY); 
    ::ReleaseDC(GetSafeHwnd(),hdc);
}

void CDlgMain::ResizeWindow()
{
    RECT r,rWin;
    GetWindowRect(&rWin);        
    GetClientRect(&r);
    rWin.right+=16*m_Cols-r.right+23+1;
    rWin.bottom+=16*m_Rows-r.bottom+66+1;
    MoveWindow(&rWin);
    GetClientRect(&r);
    GetDlgItem(IDC_BTN)->MoveWindow((r.right-25)>>1,15,25,25);
    m_iClientWidth=r.right;
}

HBRUSH CDlgMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if(nCtlColor==CTLCOLOR_DLG)
    {
        return (HBRUSH)m_brush0;
    }
    return hbr;
}

void CDlgMain::OnExit() 
{
    OnClose();
}

void CDlgMain::OnAbout() 
{
    CDialog dlg(IDD_ABOUTBOX);
    dlg.DoModal(); 
}

BOOL CDlgMain::PreTranslateMessage(MSG* pMsg) 
{
    ::TranslateAccelerator(GetSafeHwnd(),m_hAccTable,pMsg); 
    return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMain::OnTimer(UINT_PTR nIDEvent) 
{
    if(nIDEvent==IDC_TIMER)
    {
        if(m_iStatus==STA_WORKING)
        {
            UpdateWorkedTimes();
            if(++m_iWorkedTimes>999)
                m_iWorkedTimes=999;
        }
    }
    CDialog::OnTimer(nIDEvent);
}

void CDlgMain::OnBegin() 
{
    int i,j,count;
    BYTE t1,t2;

    m_iStatus        =    STA_NONE;
    m_iOpenedBlocks    =    0;
    m_iWorkedTimes    =    0;
    m_iDisMines        =    m_IniInfo.Mines;
    m_iMouseStatus    =    0;
    //随机埋下地雷 
    if(m_block)
    {
        delete[] m_block;
    }
    m_block            =    new BLOCK[m_Rows*m_Cols]; 
    ::ZeroMemory(m_block,sizeof(BLOCK)*m_Rows*m_Cols);
    srand((unsigned int)time(NULL)); 
    count    =    0;
    j        =    m_Rows *  m_Cols;
    while(count < m_IniInfo.Mines)
    {
        i = rand() % j;
        if(m_block[i].Flag != conIsMine)  //如果无雷
        {
            m_block[i].Flag = conIsMine;
            count++;
        }   
    }
    //计算单元格周围地雷个数
    for(i=0;i<m_Rows;i++)
        for(j=0;j<m_Cols;j++)
            m_block[i*m_Cols+j].Totalmines = Total(i, j, conIsMine,t1,t2);
    m_btn.SetBtnBitmap(FACE_WAIT);
    ResizeWindow(); 
    Invalidate();
}

//以I，J为中心块，统计其周围满足条件FILTER的块数
//CHOICE返回满足条件的块
//INSIDE返回周围块
BYTE CDlgMain::Total(int i, int j, BYTE filter, BYTE &choice, BYTE &inside)
{
    BYTE t    =    0;
    choice    =
    inside    =    0;  
    if(i > 0)
    {
        if(j > 0)
        {
            if((m_block[(i-1)*m_Cols+j-1].Flag & filter) == filter)
            {
                t++;
                choice |=1;
            }
            inside |= 1;
        }
        if((m_block[(i-1)*m_Cols+j].Flag & filter) == filter)
        {
            t++;
            choice |= 2;
        }
        inside |=2;
        if(j < m_Cols-1)
        {
            if((m_block[(i-1)*m_Cols+j+1].Flag & filter) == filter)
            {
                t++;
                choice |= 4;
            }
            inside |=4;
        }
    }
    if(j > 0)
    {
        if((m_block[i*m_Cols+j-1].Flag & filter) == filter)
        {
            t++;
            choice |=8;
        }
        inside |=8;
    }
    if(j < m_Cols-1)
    {
        if((m_block[i*m_Cols+j+1].Flag & filter) == filter)
        {
            t++;
            choice |= 16;
        }
        inside |=16;
    }
    if(i < m_Rows-1)
    {
        if(j > 0)
        {
            if((m_block[(i+1)*m_Cols+j-1].Flag & filter) == filter)
            {
                t++;
                choice |=32;
            }
            inside |=32;
        }
        if((m_block[(i+1)*m_Cols+j].Flag & filter) == filter)
        {
            t++;
            choice |=64;
        }
        inside |=64;
        if(j < m_Cols-1)
        {
            if((m_block[(i+1)*m_Cols+j+1].Flag & filter) == filter)
            {
                t++;
                choice |=128;
            }
            inside |=128;
        }
    }
    return t;
}

void CDlgMain::LoadIniInfo()
{
    m_IniInfo.Difficulty    =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Difficulty"),0); 
    m_IniInfo.Height        =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Height"),8); 
    m_IniInfo.Width         =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Width"),8); 
    m_IniInfo.Mines         =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Mines"),10); 
    m_IniInfo.Mark          =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Mark"),0); 
    m_IniInfo.Xpos          =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Xpos"),100); 
    m_IniInfo.Ypos          =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Ypos"),100); 
    m_IniInfo.Time1         =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Time1"),999); 
    m_IniInfo.Time2         =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Time2"),999); 
    m_IniInfo.Time3         =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Time3"),999); 
    m_IniInfo.Protect       =   AfxGetApp()->GetProfileInt(_T("扫雷"),_T("Protect"),0); 
    m_IniInfo.Name1         =   AfxGetApp()->GetProfileString(_T("扫雷"),_T("Name1"),_T("匿名")); 
    m_IniInfo.Name2         =   AfxGetApp()->GetProfileString(_T("扫雷"),_T("Name2"),_T("匿名")); 
    m_IniInfo.Name3         =   AfxGetApp()->GetProfileString(_T("扫雷"),_T("Name3"),_T("匿名")); 
    CheckIniInfo();
    if(m_IniInfo.Mark)
    {
        m_IniInfo.Mark=1;
    }
    if(m_IniInfo.Time1 < 0 || m_IniInfo.Time1 > 999)
    {
        m_IniInfo.Time1=999;
    }
    if(m_IniInfo.Time2 < 0 || m_IniInfo.Time2 > 999)
    {
        m_IniInfo.Time2=999;
    }
    if(m_IniInfo.Time3 < 0 || m_IniInfo.Time3 > 999)
    {
        m_IniInfo.Time3=999;
    }
    if(m_IniInfo.Protect)
    {
        m_IniInfo.Protect=1;
    }
    HDC hScreenDC=::CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
    if(m_IniInfo.Xpos < 0
    || m_IniInfo.Xpos + 160 >= ::GetDeviceCaps(hScreenDC,HORZRES)
    || m_IniInfo.Ypos < 0
    || m_IniInfo.Ypos + 240 >= ::GetDeviceCaps(hScreenDC,VERTRES))
    {
         m_IniInfo.Xpos=m_IniInfo.Ypos=100;
    }
    ::DeleteDC(hScreenDC);
}

void CDlgMain::SaveIniInfo()
{
    RECT r;
    m_IniInfo.Height    =   m_Rows;
    m_IniInfo.Width     =   m_Cols;
    GetWindowRect(&r);
    m_IniInfo.Xpos      =   r.left;
    m_IniInfo.Ypos      =   r.top;
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Difficulty"),m_IniInfo.Difficulty); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Height"),m_IniInfo.Height); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Width"),m_IniInfo.Width); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Mines"),m_IniInfo.Mines); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Mark"),m_IniInfo.Mark); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Xpos"),m_IniInfo.Xpos); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Ypos"),m_IniInfo.Ypos); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Time1"),m_IniInfo.Time1); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Time2"),m_IniInfo.Time2); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Time3"),m_IniInfo.Time3); 
    AfxGetApp()->WriteProfileInt(_T("扫雷"),_T("Protect"),m_IniInfo.Protect); 
    AfxGetApp()->WriteProfileString(_T("扫雷"),_T("Name1"),m_IniInfo.Name1); 
    AfxGetApp()->WriteProfileString(_T("扫雷"),_T("Name2"),m_IniInfo.Name2); 
    AfxGetApp()->WriteProfileString(_T("扫雷"),_T("Name3"),m_IniInfo.Name3); 
}

void CDlgMain::CheckIniInfo()
{
    switch(m_IniInfo.Difficulty)
    {
    case 0:
        m_IniInfo.Height    =   8;
        m_IniInfo.Width     =   8;
        m_IniInfo.Mines     =   10;
        break;
    case 1:
        m_IniInfo.Height    =   16;
        m_IniInfo.Width     =   16;
        m_IniInfo.Mines     =   40;
        break;
    case 2:
        m_IniInfo.Height    =   16;
        m_IniInfo.Width     =   30;
        m_IniInfo.Mines     =   99;
        break;
    default:
        m_IniInfo.Difficulty=    3;
        if(m_IniInfo.Height<2)
        {
            m_IniInfo.Height=8;
        }
        else if(m_IniInfo.Height>40)
        {
            m_IniInfo.Height=40;
        }
        if(m_IniInfo.Width<8)
        {
            m_IniInfo.Width=8;
        }
        else if(m_IniInfo.Width>60) 
        {
            m_IniInfo.Width=60;
        }
        if(m_IniInfo.Mines<0)
        {
            m_IniInfo.Mines=0;
        }
        if(m_IniInfo.Mines>(m_IniInfo.Height-1) * (m_IniInfo.Width-1))
        {
            m_IniInfo.Mines=(m_IniInfo.Height-1) * (m_IniInfo.Width-1);
        }
        if(m_IniInfo.Mines > 999)
        {
            m_IniInfo.Mines=999;
        }
    }
    m_Rows=m_IniInfo.Height;
    m_Cols=m_IniInfo.Width;
}

void CDlgMain::OnGrade0() 
{
    m_IniInfo.Difficulty=0;    
    UpdateMenuItemChecked();
    CheckIniInfo();
    OnBegin();
}

void CDlgMain::OnGrade1() 
{
    m_IniInfo.Difficulty=1;    
    UpdateMenuItemChecked();    
    CheckIniInfo();
    OnBegin();
}

void CDlgMain::OnGrade2() 
{
    m_IniInfo.Difficulty=2;    
    UpdateMenuItemChecked();    
    CheckIniInfo();
    OnBegin();
}

void CDlgMain::OnUserdefine() 
{
    CDlgUserDef dlg;
    dlg.m_Rows  =   m_Rows;
    dlg.m_Cols  =   m_Cols;
    dlg.m_Mines =   m_IniInfo.Mines; 
    if(dlg.DoModal()!=IDOK)
    {
        return; 
    }
    m_IniInfo.Height        =   dlg.m_Rows;
    m_IniInfo.Width         =   dlg.m_Cols;
    m_IniInfo.Mines         =   dlg.m_Mines; 
    m_IniInfo.Difficulty    =   3;    
    UpdateMenuItemChecked();    
    CheckIniInfo();
    OnBegin();
}

void CDlgMain::UpdateMenuItemChecked()
{
    CMenu* pMenu=GetMenu();
    pMenu->CheckMenuItem(IDM_GRADE0,MF_BYCOMMAND | MF_UNCHECKED); 
    pMenu->CheckMenuItem(IDM_GRADE1,MF_BYCOMMAND | MF_UNCHECKED); 
    pMenu->CheckMenuItem(IDM_GRADE2,MF_BYCOMMAND | MF_UNCHECKED); 
    pMenu->CheckMenuItem(IDM_USERDEFINE,MF_BYCOMMAND | MF_UNCHECKED); 
    switch(m_IniInfo.Difficulty)
    {
    case 0:
        pMenu->CheckMenuItem(IDM_GRADE0,MF_BYCOMMAND | MF_CHECKED); 
        break;
    case 1:
        pMenu->CheckMenuItem(IDM_GRADE1,MF_BYCOMMAND | MF_CHECKED); 
        break;
    case 2:
        pMenu->CheckMenuItem(IDM_GRADE2,MF_BYCOMMAND | MF_CHECKED); 
        break;
    default:
        pMenu->CheckMenuItem(IDM_USERDEFINE,MF_BYCOMMAND | MF_CHECKED); 
    }    
    pMenu->CheckMenuItem(IDM_MARK,MF_BYCOMMAND | (m_IniInfo.Mark==0? MF_UNCHECKED:MF_CHECKED)); 
    pMenu->CheckMenuItem(IDM_PROTECT,MF_BYCOMMAND | (m_IniInfo.Protect==0? MF_UNCHECKED:MF_CHECKED)); 
}

void CDlgMain::OnProtect() 
{
    m_IniInfo.Protect^=1;
    UpdateMenuItemChecked();     
}

void CDlgMain::OnMark() 
{
    m_IniInfo.Mark^=1;
    UpdateMenuItemChecked(); 
}

void CDlgMain::OnBtn() 
{
    OnBegin();
}

//更新剩余的雷数
void CDlgMain::UpdateDisMines()
{
    int k1,k2,k3;
    k3    =    m_iDisMines;
    if(k3 >= 0)
    {
        k1    =    k3 % 10;
        k3    =    (k3-k1)/10;
        k2    =    k3 % 10;
        k3    =    (k3-k2)/10;
    }
    else
    {
        k3    =    -k3;
        k1    =    k3 % 10;
        k3    =    (k3-k1)/10;
        k2    =    k3 % 10;
        k3    =    11;
    }
    HDC hdc=::GetDC(GetSafeHwnd());
    ::BitBlt(hdc,17,16,13,23,m_hMem2,0,(11-k3)*23,SRCCOPY); 
    ::BitBlt(hdc,30,16,13,23,m_hMem2,0,(11-k2)*23,SRCCOPY); 
    ::BitBlt(hdc,43,16,13,23,m_hMem2,0,(11-k1)*23,SRCCOPY); 
    ::ReleaseDC(GetSafeHwnd(),hdc);
}

//更新已经工作的时间
void CDlgMain::UpdateWorkedTimes()
{
    int k1,k2,k3;
    k3    =    m_iWorkedTimes;
    k1    =    k3 % 10;
    k3    =    (k3-k1)/10;
    k2    =    k3 % 10;
    k3    =    (k3-k2)/10;
    HDC hdc=::GetDC(GetSafeHwnd());
    ::BitBlt(hdc,m_iClientWidth-56,16,13,23,m_hMem2,0,(11-k3)*23,SRCCOPY); 
    ::BitBlt(hdc,m_iClientWidth-43,16,13,23,m_hMem2,0,(11-k2)*23,SRCCOPY); 
    ::BitBlt(hdc,m_iClientWidth-30,16,13,23,m_hMem2,0,(11-k1)*23,SRCCOPY); 
    ::ReleaseDC(GetSafeHwnd(),hdc);    
}

void CDlgMain::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if(!m_fMouseCapture)
    {
        SetCapture();    
        m_fMouseCapture=TRUE;
    }
    m_iMouseStatus|=MK_LBUTTON;
    if(m_iStatus==STA_NONE)  //工程在等待的话，就运行
    {
        m_iWorkedTimes    =    0;
        m_iStatus        =    STA_WORKING;
        OnTimer(IDC_TIMER);
    }
    else if(m_iStatus!=STA_WORKING)
    {//如果不在运行就退出
        return;
    }
    m_btn.SetBtnBitmap(FACE_WORK);
    if(m_iMouseStatus & MK_RBUTTON)
    {//双键同时按下
        ActionLRDown(point);
    }
    else
    {//左键单击
        ActionLDown(point);
    }
}

void CDlgMain::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if(!m_fMouseCapture)
    {
        SetCapture();    
        m_fMouseCapture=TRUE;
    }
    m_iMouseStatus|=MK_RBUTTON;
    if(m_iStatus==STA_NONE)
    {
        m_iWorkedTimes    =    0;
        m_iStatus        =    STA_WORKING;
        OnTimer(IDC_TIMER);
    }
    else if(m_iStatus!=STA_WORKING)
    {
        return;
    }
    if(m_iMouseStatus & MK_LBUTTON)
    {//双键同时按下
        ActionLRDown(point);
    }
    else
    {//右键单击
        ActionRDown(point);
    }
}

void CDlgMain::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(m_fMouseCapture)
    {
        ReleaseCapture();
        m_fMouseCapture=FALSE;
    }    
    if(m_iStatus==STA_WORKING)  //如果在运行
    {
        m_btn.SetBtnBitmap(FACE_WAIT);
        if(m_iMouseStatus & MK_RBUTTON)
        {
            ActionLRUp(point);
        }
        else
        {
            ActionLUp(point);
        }
    }
    if(m_iMouseStatus & MK_LBUTTON)
    {
        m_iMouseStatus ^= MK_LBUTTON;    
    }
}

void CDlgMain::OnRButtonUp(UINT nFlags, CPoint point) 
{
    if(m_fMouseCapture)
    {
        ReleaseCapture();
        m_fMouseCapture=FALSE;
    }
    if(m_iStatus==STA_WORKING)  //如果在运行
    {
        if(m_iMouseStatus & MK_LBUTTON)
        {
            ActionLRUp(point);
        }
    }
    if(m_iMouseStatus & MK_RBUTTON)
    {
        m_iMouseStatus ^= MK_RBUTTON;
    }
}

void CDlgMain::OnMouseMove(UINT nFlags, CPoint point) 
{
    if((m_iMouseStatus    & (MK_LBUTTON | MK_RBUTTON))==(MK_LBUTTON | MK_RBUTTON))
    {
        if(m_iStatus==STA_WORKING)
        {//如果在运行
            ActionLRMove(point);
        }
    }
    else if((m_iMouseStatus    & MK_LBUTTON)==MK_LBUTTON)
    {
        if(m_iStatus==STA_WORKING)
        {//如果在运行
            ActionLMove(point);
        }
    }
}

void CDlgMain::ActionRDown(CPoint &pt)
{
    int i,j,idx;
    if(GetRowCol(pt.x,pt.y,i,j))
    {
        idx=i*m_Cols+j;
        if(m_block[idx].Flag & conDiscovered)
        {//如果已经打开
            return;
        }
        if(m_block[idx].Flag & conFounded)
        {//已经标上地雷
            m_block[idx].Flag ^=conFounded;  //去掉地雷标志
            m_iDisMines++;
            UpdateDisMines();
            if(m_IniInfo.Mark)
            {//允许标记，则标记?
                m_block[idx].Flag |= conMarked;
            }
        }
        else if(m_block[idx].Flag & conMarked)
        {//已经标上问号
            m_block[idx].Flag ^= conMarked;
        }
        else  //空白状态
        {
            m_block[idx].Flag |=conFounded;          
            m_iDisMines--;
            UpdateDisMines();
        }
        DrawTheBlock(i,j);
    }
}

void CDlgMain::ActionLDown(CPoint &pt)
{
    m_fPrevIsGood=GetRowCol(pt.x,pt.y,m_PrevRow,m_PrevCol);
    if(m_fPrevIsGood)
    {
        DrawAroundOneBlock(m_PrevRow,m_PrevCol,FALSE);
    }
}

void CDlgMain::ActionLMove(CPoint &pt)
{
    BOOL fOK;
    int r,c;
    if(m_fPrevIsGood)
    {
        DrawAroundOneBlock(m_PrevRow,m_PrevCol,TRUE);
    }
    fOK    =    GetRowCol(pt.x,pt.y,r,c);
    if(fOK)
    {
        DrawAroundOneBlock(r,c,FALSE);
    }
    m_fPrevIsGood    =    fOK;
    m_PrevRow        =    r;
    m_PrevCol        =    c;
}

void CDlgMain::ActionLUp(CPoint &pt)
{
    int i,j,idx;
    if(GetRowCol(pt.x,pt.y,i,j))
    {
        idx=i*m_Cols+j;
        if(m_block[idx].Flag & conDiscovered)return;  //如果已经打开
        if(m_block[idx].Flag & conFounded)return;     //已经标上地雷
        if(m_block[idx].Flag & conIsMine)
        {//如果是地雷
            if(m_IniInfo.Protect)
            {//如果保护
                ::MessageBeep(0);
            }
            else
            {
                m_block[idx].Flag |=conDiscovered;
                m_iStatus=STA_DIED;  //死亡
                m_btn.SetBtnBitmap(FACE_DIED);
                UpdateMineArea();
            }
        }
        else
        {//如果不是地雷,打开该块
            OpenTheBlock(i,j);
        }
    }
}

void CDlgMain::ActionLRDown(CPoint &pt)
{
    m_fPrevIsGood=GetRowCol(pt.x,pt.y,m_PrevRow,m_PrevCol);
    if(m_fPrevIsGood)
    {
        DrawAroundBlocks(m_PrevRow,m_PrevCol,FALSE);
    }
}

void CDlgMain::ActionLRMove(CPoint &pt)
{
    BOOL fOK;
    int r,c;
    if(m_fPrevIsGood)
        DrawAroundBlocks(m_PrevRow,m_PrevCol,TRUE);
    fOK=GetRowCol(pt.x,pt.y,r,c);
    if(fOK)
        DrawAroundBlocks(r,c,FALSE);
    m_fPrevIsGood=fOK;
    m_PrevRow=r;
    m_PrevCol=c;
}

void CDlgMain::ActionLRUp(CPoint &pt)
{
    int r,c,idx;
    if(m_fPrevIsGood)
        DrawAroundBlocks(m_PrevRow,m_PrevCol,TRUE);
    if(GetRowCol(pt.x,pt.y,r,c))
    {
        idx=r*m_Cols+c;
        if(m_block[idx].Flag & conDiscovered)
        {
            BYTE cNotFound,inside,cErr;
            if(Total(r,c,conFounded,cNotFound,inside)==m_block[idx].Totalmines)
            {
                cNotFound=~cNotFound & inside;
                cErr=0;
                if(cNotFound&1)
                {
                    idx=(r-1)*m_Cols+c-1;
                    if(m_block[idx].Flag & conIsMine)cErr|=1;
                }
                if(cNotFound&2)
                {
                    idx=(r-1)*m_Cols+c;
                    if(m_block[idx].Flag & conIsMine)cErr|=2;
                }
                if(cNotFound&4)
                {
                    idx=(r-1)*m_Cols+c+1;
                    if(m_block[idx].Flag & conIsMine)cErr|=4;
                }
                if(cNotFound&8)
                {
                    idx=r*m_Cols+c-1;
                    if(m_block[idx].Flag & conIsMine)cErr|=8;
                }
                if(cNotFound&16)
                {
                    idx=r*m_Cols+c+1;
                    if(m_block[idx].Flag & conIsMine)cErr|=16;
                }
                if(cNotFound&32)
                {
                    idx=(r+1)*m_Cols+c-1;
                    if(m_block[idx].Flag & conIsMine)cErr|=32;
                }
                if(cNotFound&64)
                {
                    idx=(r+1)*m_Cols+c;
                    if(m_block[idx].Flag & conIsMine)cErr|=64;
                }
                if(cNotFound&128)
                {
                    idx=(r+1)*m_Cols+c+1;
                    if(m_block[idx].Flag & conIsMine)cErr|=128;
                }
                if(cErr)  //如果有错误
                {
                    if(m_IniInfo.Protect)
                        ::MessageBeep(0);
                    else
                    {
                        if(cErr&1)m_block[(r-1)*m_Cols+c-1].Flag |=conDiscovered;
                        if(cErr&2)m_block[(r-1)*m_Cols+c].Flag |=conDiscovered;
                        if(cErr&4)m_block[(r-1)*m_Cols+c+1].Flag |=conDiscovered;
                        if(cErr&8)m_block[(r)*m_Cols+c-1].Flag |=conDiscovered;
                        if(cErr&16)m_block[(r)*m_Cols+c+1].Flag |=conDiscovered;
                        if(cErr&32)m_block[(r+1)*m_Cols+c-1].Flag |=conDiscovered;
                        if(cErr&64)m_block[(r+1)*m_Cols+c].Flag |=conDiscovered;
                        if(cErr&128)m_block[(r+1)*m_Cols+c+1].Flag |=conDiscovered;
                        m_iStatus=STA_DIED;  //死亡
                        m_btn.SetBtnBitmap(FACE_DIED);
                        UpdateMineArea();
                    }
                }
                else
                {
                    if(cNotFound&1)OpenTheBlock(r-1,c-1);
                    if(cNotFound&2)OpenTheBlock(r-1,c);
                    if(cNotFound&4)OpenTheBlock(r-1,c+1);
                    if(cNotFound&8)OpenTheBlock(r,c-1);
                    if(cNotFound&16)OpenTheBlock(r,c+1);
                    if(cNotFound&32)OpenTheBlock(r+1,c-1);
                    if(cNotFound&64)OpenTheBlock(r+1,c);
                    if(cNotFound&128)OpenTheBlock(r+1,c+1);
                }
            }
        }        
    }
}

void CDlgMain::OpenTheBlock(int i, int j)
{
    int idx=i*m_Cols+j;
    TRACE(_T("open=%d,%d\n"),i,j);
  if(m_block[idx].Flag & conDiscovered)return;
    m_block[idx].Flag |=conDiscovered;
  DrawTheBlock(i,j);
    if(++m_iOpenedBlocks>=m_Rows*m_Cols-m_IniInfo.Mines)
    {
        BOOL fNewRec=FALSE;
        CString s;

        m_iStatus=STA_OK;  //成功
        m_btn.SetBtnBitmap(FACE_OK);
        UpdateMineArea();
        switch(m_IniInfo.Difficulty)
        {
        case 0:
            if(m_iWorkedTimes<m_IniInfo.Time1)
            {
                m_IniInfo.Time1=m_iWorkedTimes;
                fNewRec=TRUE;
                s=_T("初级");
            }
            break;
        case 1:
            if(m_iWorkedTimes<m_IniInfo.Time2)
            {
                m_IniInfo.Time2=m_iWorkedTimes;
                fNewRec=TRUE;
                s=_T("中级");
            }
            break;
        case 2:
            if(m_iWorkedTimes<m_IniInfo.Time3)
            {
                m_IniInfo.Time3=m_iWorkedTimes;
                fNewRec=TRUE;
                s=_T("高级");
            }
            break;
        }
        if(fNewRec)
        {
            CDlgName dlg;
            dlg.m_Prompt=_T("您已经成为")+s+_T("第一高手，请输入您的大名：");
            dlg.DoModal(); 
            switch(m_IniInfo.Difficulty)
            {
            case 0:
                m_IniInfo.Name1=dlg.m_Name;
                break;
            case 1:
                m_IniInfo.Name2=dlg.m_Name;
                break;
            case 2:
                m_IniInfo.Name3=dlg.m_Name;
            }
            OnHero();
        }
        return;
    }    
    if(m_block[idx].Totalmines==0)
    {
        BYTE cNotMine,cNotFound,cNotDiscovered,inside,c;
        Total(i,j,conIsMine,cNotMine,inside);
        Total(i,j,conFounded,cNotFound,inside);
        Total(i,j,conDiscovered,cNotDiscovered,inside);        
        cNotMine=~cNotMine;
        cNotFound=~cNotFound;
        cNotDiscovered=~cNotDiscovered;
        c=cNotMine & cNotFound & cNotDiscovered & inside;
        if(c&1)OpenTheBlock(i-1,j-1);
        if(c&2)OpenTheBlock(i-1,j);
        if(c&4)OpenTheBlock(i-1,j+1);
        if(c&8)OpenTheBlock(i,j-1);
        if(c&16)OpenTheBlock(i,j+1);
        if(c&32)OpenTheBlock(i+1,j-1);
        if(c&64)OpenTheBlock(i+1,j);
        if(c&128)OpenTheBlock(i+1,j+1);
    }
}

void CDlgMain::OnHelponce() 
{
  int i,j,k;
    if(m_iStatus==STA_NONE)  //工程在等待的话，就运行
    {
        m_iWorkedTimes=0;
        m_iStatus=STA_WORKING;
        OnTimer(IDC_TIMER);
    }
    if(m_iStatus!=STA_WORKING)return;
    k=0;
    for(i=0;i<m_Rows;i++)
    {
        for(j=0;j<m_Cols;j++)
        {
      if((m_block[k].Flag & conIsMine)==0)  //不是雷
            {
                if((m_block[k].Flag & conDiscovered)==0)
                {
                    OpenTheBlock(i,j);
                  return;
                }
            }
            k++;
        }
    }
}

void CDlgMain::DrawAroundBlocks(int r, int c, BOOL fRestore)
{
  int idx=r*m_Cols+c;
    BYTE cNotFound,cNotDiscovered,inside,cc;
    Total(r,c,conDiscovered,cNotDiscovered,inside);
    Total(r,c,conFounded,cNotFound,inside);    
    cNotDiscovered=~cNotDiscovered;
    cNotFound=~cNotFound;
    cc=cNotFound & cNotDiscovered & inside;
    if(cc&1)DrawAroundOneBlock(r-1,c-1,fRestore);
    if(cc&2)DrawAroundOneBlock(r-1,c,fRestore);
    if(cc&4)DrawAroundOneBlock(r-1,c+1,fRestore);
    if(cc&8)DrawAroundOneBlock(r,c-1,fRestore);
    DrawAroundOneBlock(r,c,fRestore);
    if(cc&16)DrawAroundOneBlock(r,c+1,fRestore);
    if(cc&32)DrawAroundOneBlock(r+1,c-1,fRestore);
    if(cc&64)DrawAroundOneBlock(r+1,c,fRestore);
    if(cc&128)DrawAroundOneBlock(r+1,c+1,fRestore);
}

void CDlgMain::DrawAroundOneBlock(int r, int c, BOOL fRestore)
{
    int k,idx=r*m_Cols+c;
    HDC hdc;
    if(m_block[idx].Flag & (conDiscovered | conFounded))return;
    if(fRestore)
    {
        k=0;
        if(m_block[idx].Flag & conMarked)k=2;
    }
    else
        k=15;
    hdc=::GetDC(GetSafeHwnd());
    ::BitBlt(hdc,m_x0+c*16,m_y0+r*16,16,16,m_hMem1,0,k*16,SRCCOPY); 
    ::ReleaseDC(GetSafeHwnd(),hdc);
}

void CDlgMain::OnHero() 
{
    CDlgHero dlg;
    dlg.m_Name1=m_IniInfo.Name1;
    dlg.m_Name2=m_IniInfo.Name2;
    dlg.m_Name3=m_IniInfo.Name3;
    dlg.m_Time1.Format(_T("%d"),m_IniInfo.Time1);  
    dlg.m_Time2.Format(_T("%d"),m_IniInfo.Time2);  
    dlg.m_Time3.Format(_T("%d"),m_IniInfo.Time3);  
    dlg.DoModal(); 
    if(dlg.m_f)
    {
        m_IniInfo.Name1=m_IniInfo.Name2=m_IniInfo.Name3=dlg.m_Name1;
        m_IniInfo.Time1=m_IniInfo.Time2=m_IniInfo.Time3=999;
    }
}

void CDlgMain::UpdateMineArea()
{
    int i,j;
    for(i=0;i<m_Rows;i++)
    {
        for(j=0;j<m_Cols;j++)
        {
            DrawTheBlock(i,j);
        }
    }
}