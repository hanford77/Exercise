//DlgMain.cpp
#include "stdafx.h"
#include <math.h>
#include "GPSTime.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR  szErr[]        =    _T("*");
static TCHAR* szWeekName[]    =
{
    _T("星期日"),
    _T("星期一"),
    _T("星期二"),
    _T("星期三"),
    _T("星期四"),
    _T("星期五"),
    _T("星期六"),
};

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgMain::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgMain)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bLockEdit    =    FALSE;
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
    ON_EN_CHANGE(IDC_TXT_YEAR, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_MONTH, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_DAY, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_HOUR, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_MINUTE, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_SECOND, OnChangeTxtYear)
    ON_EN_CHANGE(IDC_TXT_WEEK, OnChangeTxtGPS)
    ON_EN_CHANGE(IDC_TXT_WEEK_SEC, OnChangeTxtGPS)
    ON_EN_CHANGE(IDC_TXT_YEAR_DAY, OnChangeTxtYearDay)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMain::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    m_bLockEdit    =    TRUE;
    BOOL    bOK    =    TRUE;        
    __try
    {
        COleDateTime    tm    =    COleDateTime::GetCurrentTime();
        double            time=    tm-COleDateTime(1980,1,6,0,0,0);
        if(tm.m_status!=tm.valid || time < 0.0)
        {
            bOK    =    FALSE;
        }
        else
        {
            SYSTEMTIME sysTime;
            tm.GetAsSystemTime(sysTime);
            SetDlgItemInt(IDC_TXT_YEAR,sysTime.wYear);
            SetDlgItemInt(IDC_TXT_MONTH,sysTime.wMonth);
            SetDlgItemInt(IDC_TXT_DAY,sysTime.wDay);
            SetDlgItemInt(IDC_TXT_HOUR,sysTime.wHour);
            SetDlgItemInt(IDC_TXT_MINUTE,sysTime.wMinute);
            SetDlgItemInt(IDC_TXT_SECOND,sysTime.wSecond);

            int    wn     =    (int)floor(time / 7.0);
            time    -=    wn*7.0;
            time    *=    86400.0;
            TCHAR szStr[32];

            _stprintf(szStr,_T("%.0lf"),time);
            SetDlgItemInt(IDC_TXT_WEEK,wn);
            SetDlgItemText(IDC_TXT_WEEK_SEC,szStr);
            SetDlgItemInt(IDC_TXT_YEAR_DAY,tm.GetDayOfYear());
            SetDlgItemText(IDC_LBL_WEEK,szWeekName[tm.GetDayOfWeek()-1]);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        bOK    =    FALSE;
    }
    if(!bOK)
    {
        SetDlgItemText(IDC_TXT_WEEK,szErr);
        SetDlgItemText(IDC_TXT_WEEK_SEC,szErr);
        SetDlgItemText(IDC_TXT_YEAR_DAY,szErr);
        SetDlgItemText(IDC_LBL_WEEK,_T(""));
    }
    m_bLockEdit    =    FALSE;        
    return TRUE;
}

void CDlgMain::OnChangeTxtYear() 
{
    if(m_bLockEdit)
    {
        return;
    }
    int y,m,d,H,M,S;
    y=GetDlgItemInt(IDC_TXT_YEAR);
    m=GetDlgItemInt(IDC_TXT_MONTH);
    d=GetDlgItemInt(IDC_TXT_DAY);
    H=GetDlgItemInt(IDC_TXT_HOUR);
    M=GetDlgItemInt(IDC_TXT_MINUTE);
    S=GetDlgItemInt(IDC_TXT_SECOND);

    m_bLockEdit    =    TRUE;
    COleDateTime tm(y,m,d,H,M,S);
    if(tm.m_status==tm.valid)
    {//时间有效
        double    time    =    tm-COleDateTime(1980,1,6,0,0,0);
        int        wn        =    (int)floor(time / 7.0);
        TCHAR    szStr[32];

        time    -=    wn*7.0;
        time    *=    86400.0;        

        _stprintf(szStr,_T("%.0lf"),time);
        SetDlgItemInt(IDC_TXT_WEEK,wn);
        SetDlgItemText(IDC_TXT_WEEK_SEC,szStr);
        SetDlgItemInt(IDC_TXT_YEAR_DAY,tm.GetDayOfYear());
        SetDlgItemText(IDC_LBL_WEEK,szWeekName[tm.GetDayOfWeek()-1]);
    }
    else
    {//时间无效
        SetDlgItemText(IDC_TXT_WEEK,szErr);
        SetDlgItemText(IDC_TXT_WEEK_SEC,szErr);
        SetDlgItemText(IDC_TXT_YEAR_DAY,szErr);
        SetDlgItemText(IDC_LBL_WEEK,_T(""));
    }
    m_bLockEdit    =    FALSE;
}

void CDlgMain::OnChangeTxtGPS() 
{
    if(m_bLockEdit)
    {
        return;
    }
    int wn    =    GetDlgItemInt(IDC_TXT_WEEK);
    int sec    =    GetDlgItemInt(IDC_TXT_WEEK_SEC);

    m_bLockEdit    =    TRUE;
    BOOL    bOK    =    TRUE;

//    if(sec < 0 || sec >= 604800)
//    {
//        bOK        =    FALSE;
//    }
//    else
    {
        COleDateTime tm(1980,1,6,0,0,0);
        tm  +=  (DATE)(wn * 7.0 + sec / 86400.0);
        if(tm.m_status==tm.valid)
        {
            SYSTEMTIME sysTime;
            tm.GetAsSystemTime(sysTime);
            SetDlgItemInt(IDC_TXT_YEAR,sysTime.wYear);
            SetDlgItemInt(IDC_TXT_MONTH,sysTime.wMonth);
            SetDlgItemInt(IDC_TXT_DAY,sysTime.wDay);
            SetDlgItemInt(IDC_TXT_HOUR,sysTime.wHour);
            SetDlgItemInt(IDC_TXT_MINUTE,sysTime.wMinute);
            SetDlgItemInt(IDC_TXT_SECOND,sysTime.wSecond);
            SetDlgItemText(IDC_LBL_WEEK,szWeekName[tm.GetDayOfWeek()-1]);
            SetDlgItemInt(IDC_TXT_YEAR_DAY,tm.GetDayOfYear());
        }
        else
        {
            bOK    =    FALSE;
        }        
    }
    if(!bOK)
    {
        SetDlgItemText(IDC_TXT_YEAR,szErr);
        SetDlgItemText(IDC_TXT_MONTH,szErr);
        SetDlgItemText(IDC_TXT_DAY,szErr);
        SetDlgItemText(IDC_TXT_HOUR,szErr);
        SetDlgItemText(IDC_TXT_MINUTE,szErr);
        SetDlgItemText(IDC_TXT_SECOND,szErr);
        SetDlgItemText(IDC_LBL_WEEK,_T(""));
        SetDlgItemText(IDC_TXT_YEAR_DAY,szErr);
    }
    m_bLockEdit    =    FALSE;
}

void CDlgMain::OnChangeTxtYearDay() 
{
    if(m_bLockEdit)
    {
        return;
    }
    int y   =   GetDlgItemInt(IDC_TXT_YEAR);
    int Days=   GetDlgItemInt(IDC_TXT_YEAR_DAY);
    COleDateTime tm(y,1,1,0,0,0);
    tm     +=   (DATE)(Days - 1);
    m_bLockEdit    =    TRUE;
    if(tm.m_status==tm.valid)
    {
        SYSTEMTIME sysTime;
        tm.GetAsSystemTime(sysTime);
        SetDlgItemInt(IDC_TXT_YEAR,sysTime.wYear);
        SetDlgItemInt(IDC_TXT_MONTH,sysTime.wMonth);
        SetDlgItemInt(IDC_TXT_DAY,sysTime.wDay);
        int H  =  GetDlgItemInt(IDC_TXT_HOUR);
        int M  =  GetDlgItemInt(IDC_TXT_MINUTE);
        int S  =  GetDlgItemInt(IDC_TXT_SECOND);
        tm     +=   ((S / 60.0 + M) / 60.0 + H) / 24.0;
        double    time    =    tm - COleDateTime(1980,1,6,0,0,0);
        int        wn        =    (int)floor(time / 7.0);
        TCHAR    szStr[32];

        time    -=    wn*7.0;
        time    *=    86400.0;        

        _stprintf(szStr,_T("%.0lf"),time);
        SetDlgItemInt(IDC_TXT_WEEK,wn);
        SetDlgItemText(IDC_TXT_WEEK_SEC,szStr);
        SetDlgItemText(IDC_LBL_WEEK,szWeekName[tm.GetDayOfWeek()-1]);
    }
    else
    {
        SetDlgItemText(IDC_TXT_MONTH,szErr);
        SetDlgItemText(IDC_TXT_DAY,szErr);
    }
    m_bLockEdit    =    FALSE;
}