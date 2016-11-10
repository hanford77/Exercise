//HexToNumDlg.cpp
#include "stdafx.h"
#include "HexToNum.h"
#include "HexToNumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef char    int8;
typedef short   int16;
typedef long    int32;
typedef __int64 int64;

typedef unsigned char    uint8;
typedef unsigned short   uint16;
typedef unsigned long    uint32;
typedef unsigned __int64 uint64;

/******************************************************************************\
获得字符串的 int32 数值
szStr   [in]    字符串
val     [out]   int32数值
nBase   [in]    几进制[2,36]
\******************************************************************************/
BOOL StringToInt32(LPCTSTR szStr,long& val,int nBase)
{
    if(nBase < 2 || nBase > 36)
    {
        return FALSE;
    }
	if(!szStr || !szStr[0])
	{
		val	=	0;
		return TRUE;
	}
	long	i32     =   0;
    int		nSign   =   0;  //符号，0：未读到 1：正 -1：负
	int     d;              //某一位数值
    TCHAR   ch;
    long    mMax    =   LONG_MAX / nBase;   //LONG_MAX = +2147483647
    int     nMax    =   (int)(LONG_MAX % nBase);
    long    mMin    =   LONG_MIN / nBase;   //LONG_MIN = -2147483648
    int     nMin    =   (int)(LONG_MIN % nBase);

	while(1)
	{//去掉前面的空格
		if(*szStr==_T('\0'))
		{
			val	=	0;
			return TRUE;
		}
		if(*szStr!=_T(' '))
		{
			break;
		}
		szStr++;
	}
	while(ch = *szStr++)
	{
		if(ch >= _T('0') && ch <= _T('9'))
		{//如果为数字
            d   =   ch - _T('0');
            goto num;
		}
		if(ch >= _T('A') && ch <= _T('Z'))
		{//如果为数字
            d   =   ch - _T('A') + 10;
            goto num;
		}
		if(ch >= _T('a') && ch <= _T('z'))
		{//如果为数字
            d   =   ch - _T('a') + 10;
            goto num;
		}

		if(ch==_T('-'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   -1;
            continue;
		}
		if(ch==_T('+'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   1;
            continue;
		}
		if(ch==_T(' '))
		{//如果为空格,则后面的都应该为空格
			while(ch = *szStr++)
			{
				if(ch!=_T(' '))
				{
					return FALSE;
				}
			}
			break;
		}
		//其它字符都是非法字符
		return FALSE;
num:
        if(d >= nBase)
        {
            return FALSE;
        }
        if(!nSign)
        {
            nSign   =   1;
        }
        if(nSign > 0)
        {//i32 * nBase + d <= LONG_MAX
            if(nMax < d)
            {
                if(i32 > mMax - 1)
                {
                    return FALSE;
                }
            }
            else
            {
                if(i32 > mMax)
                {
                    return FALSE;
                }
            }
            i32 = i32 * nBase + d;
        }
        else
        {//i32 * nBase - d >= LONG_MIN
            if(nMin + d > 0)
            {
                if(i32 < mMin + 1)
                {
                    return FALSE;
                }
            }
            else
            {
                if(i32 < mMin)
                {
                    return FALSE;
                }
            }
            i32 = i32 * nBase - d;
        }
	}
	val	=	i32;
	return TRUE;
}

/******************************************************************************\
获得字符串的 uint32 数值
szStr   [in]    字符串
val     [out]   uint32数值
nBase   [in]    几进制[2,36]
\******************************************************************************/
BOOL StringToUInt32(LPCTSTR szStr,unsigned long& val,int nBase)
{
    if(nBase < 2 || nBase > 36)
    {
        return FALSE;
    }
	if(!szStr || !szStr[0])
	{
		val	=	0;
		return TRUE;
	}
	unsigned long   i32     =   0;
    int             nSign   =   0;  //符号，0：未读到 1：正 -1：负
	int             d;              //某一位数值
    TCHAR           ch;
    unsigned long   mMax    =   ULONG_MAX / nBase;  //ULONG_MAX = 4294967295
    int             nMax    =   (int)(ULONG_MAX % nBase);

	while(1)
	{//去掉前面的空格
		if(*szStr==_T('\0'))
		{
			val	=	0;
			return TRUE;
		}
		if(*szStr!=_T(' '))
		{
			break;
		}
		szStr++;
	}
	while(ch = *szStr++)
	{
		if(ch >= _T('0') && ch <= _T('9'))
		{//如果为数字
            d   =   ch - _T('0');
            goto num;
		}
		if(ch >= _T('A') && ch <= _T('Z'))
		{//如果为数字
            d   =   ch - _T('A') + 10;
            goto num;
		}
		if(ch >= _T('a') && ch <= _T('z'))
		{//如果为数字
            d   =   ch - _T('a') + 10;
            goto num;
		}

		if(ch==_T('-'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   -1;
            continue;
		}
		if(ch==_T('+'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   1;
            continue;
		}
		if(ch==_T(' '))
		{//如果为空格,则后面的都应该为空格
			while(ch = *szStr++)
			{
				if(ch!=_T(' '))
				{
					return FALSE;
				}
			}
			break;
		}
		//其它字符都是非法字符
		return FALSE;
num:
        if(d >= nBase)
        {
            return FALSE;
        }
        if(!nSign)
        {
            nSign   =   1;
        }
        if(nMax < d)
        {
            if(i32 > mMax - 1)
            {
                return FALSE;
            }
        }
        else
        {
            if(i32 > mMax)
            {
                return FALSE;
            }
        }
        i32 = i32 * nBase + d;
	}
    if(nSign < 0 && i32)
    {
        return FALSE;
    }
	val	=	i32;
	return TRUE;
}

/******************************************************************************\
获得字符串的 int64 数值
szStr   [in]    字符串
val     [out]   int64数值
nBase   [in]    几进制[2,36]
\******************************************************************************/
BOOL StringToInt64(LPCTSTR szStr,__int64& val,int nBase)
{
    if(nBase < 2 || nBase > 36)
    {
        return FALSE;
    }
	if(!szStr || !szStr[0])
	{
		val	=	0;
		return TRUE;
	}
	__int64	i64     =   0;
    int		nSign   =   0;  //符号，0：未读到 1：正 -1：负
	int     d;              //某一位数值
    TCHAR   ch;
    __int64 mMax    =   _I64_MAX / nBase;   //_I64_MAX = +9223372036854775807
    int     nMax    =   (int)(_I64_MAX % nBase);
    __int64 mMin    =   _I64_MIN / nBase;   //_I64_MIN = -9223372036854775808
    int     nMin    =   (int)(_I64_MIN % nBase);

	while(1)
	{//去掉前面的空格
		if(*szStr==_T('\0'))
		{
			val	=	0;
			return TRUE;
		}
		if(*szStr!=_T(' '))
		{
			break;
		}
		szStr++;
	}
	while(ch = *szStr++)
	{
		if(ch >= _T('0') && ch <= _T('9'))
		{//如果为数字
            d   =   ch - _T('0');
            goto num;
		}
		if(ch >= _T('A') && ch <= _T('Z'))
		{//如果为数字
            d   =   ch - _T('A') + 10;
            goto num;
		}
		if(ch >= _T('a') && ch <= _T('z'))
		{//如果为数字
            d   =   ch - _T('a') + 10;
            goto num;
		}

		if(ch==_T('-'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   -1;
            continue;
		}
		if(ch==_T('+'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   1;
            continue;
		}
		if(ch==_T(' '))
		{//如果为空格,则后面的都应该为空格
			while(ch = *szStr++)
			{
				if(ch!=_T(' '))
				{
					return FALSE;
				}
			}
			break;
		}
		//其它字符都是非法字符
		return FALSE;
num:
        if(d >= nBase)
        {
            return FALSE;
        }
        if(!nSign)
        {
            nSign   =   1;
        }
        if(nSign > 0)
        {//i64 * nBase + d <= LONG_MAX
            if(nMax < d)
            {
                if(i64 > mMax - 1)
                {
                    return FALSE;
                }
            }
            else
            {
                if(i64 > mMax)
                {
                    return FALSE;
                }
            }
            i64 = i64 * nBase + d;
        }
        else
        {//i64 * nBase - d >= LONG_MIN
            if(nMin + d > 0)
            {
                if(i64 < mMin + 1)
                {
                    return FALSE;
                }
            }
            else
            {
                if(i64 < mMin)
                {
                    return FALSE;
                }
            }
            i64 = i64 * nBase - d;
        }
	}
	val	=	i64;
	return TRUE;
}

/******************************************************************************\
获得字符串的 uint64 数值
szStr   [in]    字符串
val     [out]   uint64数值
nBase   [in]    几进制[2,36]
\******************************************************************************/
BOOL StringToUInt64(LPCTSTR szStr,unsigned __int64& val,int nBase)
{
    if(nBase < 2 || nBase > 36)
    {
        return FALSE;
    }
	if(!szStr || !szStr[0])
	{
		val	=	0;
		return TRUE;
	}
	unsigned __int64    i64     =   0;
    int                 nSign   =   0;  //符号，0：未读到 1：正 -1：负
	int                 d;              //某一位数值
    TCHAR               ch;
    unsigned __int64    mMax    =   _UI64_MAX / nBase;  //_UI64_MAX = 18446744073709551615
    int                 nMax    =   (int)(_UI64_MAX % nBase);

	while(1)
	{//去掉前面的空格
		if(*szStr==_T('\0'))
		{
			val	=	0;
			return TRUE;
		}
		if(*szStr!=_T(' '))
		{
			break;
		}
		szStr++;
	}
	while(ch = *szStr++)
	{
		if(ch >= _T('0') && ch <= _T('9'))
		{//如果为数字
            d   =   ch - _T('0');
            goto num;
		}
		if(ch >= _T('A') && ch <= _T('Z'))
		{//如果为数字
            d   =   ch - _T('A') + 10;
            goto num;
		}
		if(ch >= _T('a') && ch <= _T('z'))
		{//如果为数字
            d   =   ch - _T('a') + 10;
            goto num;
		}

		if(ch==_T('-'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   -1;
            continue;
		}
		if(ch==_T('+'))
		{//如果为符号
			if(nSign)
			{
				return FALSE;
			}
			nSign   =   1;
            continue;
		}
		if(ch==_T(' '))
		{//如果为空格,则后面的都应该为空格
			while(ch = *szStr++)
			{
				if(ch!=_T(' '))
				{
					return FALSE;
				}
			}
			break;
		}
		//其它字符都是非法字符
		return FALSE;
num:
        if(d >= nBase)
        {
            return FALSE;
        }
        if(!nSign)
        {
            nSign   =   1;
        }
        if(nMax < d)
        {
            if(i64 > mMax - 1)
            {
                return FALSE;
            }
        }
        else
        {
            if(i64 > mMax)
            {
                return FALSE;
            }
        }
        i64 = i64 * nBase + d;
	}
    if(nSign < 0 && i64)
    {
        return FALSE;
    }
	val	=	i64;
	return TRUE;
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxVal(CEdit* txt,long& val)
{
	CString s;
	txt->GetWindowText(s);
	return StringToInt32(s,val,10);
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxValMinMax(CEdit* txt, long Min, long Max,long& val)
{
	return GetTextBoxVal(txt,val) && val >= Min && val <= Max;
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxVal(CEdit* txt,unsigned long& val)
{
	CString s;
	txt->GetWindowText(s);
	return StringToUInt32(s,val,10);
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxValMinMax(CEdit* txt,unsigned long Min,unsigned long Max,unsigned long& val)
{
	return GetTextBoxVal(txt,val) && val >= Min && val <= Max;
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxVal(CEdit* txt,__int64& val)
{
	CString s;
	txt->GetWindowText(s);
	return StringToInt64(s,val,10);
}

/******************************************************************************\
从txt文本框中获得输入值
\******************************************************************************/
BOOL GetTextBoxVal(CEdit* txt,unsigned __int64& val)
{
	CString s;
	txt->GetWindowText(s);
	return StringToUInt64(s,val,10);
}

/******************************************************************************\
设置变量
pBuf    [in]    内存
nSize   [in]    内存大小
var     [out]   变量
bBig    [in]    是否高位在前
\******************************************************************************/
template<class T>
void SetVar(BYTE*pBuf,int nSize,T&var,BOOL bBig)
{
    int nLen = sizeof(T);
    if(nSize < nLen)
    {
        ZeroMemory(&var,nLen);
    }
    else
    {
        nSize = nLen;
    }
    if(nSize > 0)
    {
        if(bBig)
        {//高位在前
            BYTE*pVar   =   (BYTE*)&var;
            for(int i = 0;i < nSize;i++)
            {
                pVar[nLen - 1 - i] =   pBuf[i];
            }
        }
        else
        {//低位在前
            memcpy(&var,pBuf,nSize);
        }
    }
}

template<class T>
void GetVar(BYTE*pBuf,T&var,BOOL bBig)
{
    int nLen = sizeof(T);
    if(bBig)
    {//高位在前
        BYTE*pVar   =   (BYTE*)&var;
        for(int i = 0;i < nLen;i++)
        {
            pBuf[i] =   pVar[nLen - 1 - i];
        }
    }
    else
    {//低位在前
        memcpy(pBuf,&var,nLen);
    }
}

CHexToNumDlg::CHexToNumDlg(CWnd* pParent /*=NULL*/)
:CDialog(CHexToNumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHexToNumDlg)
	m_iOptCode = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bLock = FALSE;
}

void CHexToNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHexToNumDlg)
	DDX_Control(pDX, IDC_CBO_DOUBLE, m_cboDouble);
	DDX_Control(pDX, IDC_CBO_FLOAT, m_cboFloat);
	DDX_Radio(pDX, IDC_OPT_MBCS, m_iOptCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHexToNumDlg, CDialog)
	//{{AFX_MSG_MAP(CHexToNumDlg)
	ON_EN_CHANGE(IDC_TXT_HEX, OnChangeTxtHex)
	ON_EN_CHANGE(IDC_TXT_DOUBLE_B, OnChangeTxtDoubleB)
	ON_EN_CHANGE(IDC_TXT_DOUBLE_L, OnChangeTxtDoubleL)
	ON_EN_CHANGE(IDC_TXT_FLOAT_L, OnChangeTxtFloatL)
	ON_EN_CHANGE(IDC_TXT_FLOAT_B, OnChangeTxtFloatB)
	ON_EN_CHANGE(IDC_TXT_INT8_L, OnChangeTxtInt8L)
	ON_EN_CHANGE(IDC_TXT_INT8_B, OnChangeTxtInt8B)
	ON_EN_CHANGE(IDC_TXT_INT16_L, OnChangeTxtInt16L)
	ON_EN_CHANGE(IDC_TXT_INT16_B, OnChangeTxtInt16B)
	ON_EN_CHANGE(IDC_TXT_INT32_L, OnChangeTxtInt32L)
	ON_EN_CHANGE(IDC_TXT_INT32_B, OnChangeTxtInt32B)
	ON_EN_CHANGE(IDC_TXT_INT64_L, OnChangeTxtInt64L)
	ON_EN_CHANGE(IDC_TXT_INT64_B, OnChangeTxtInt64B)
	ON_EN_CHANGE(IDC_TXT_UINT8_L, OnChangeTxtUint8L)
	ON_EN_CHANGE(IDC_TXT_UINT8_B, OnChangeTxtUint8B)
	ON_EN_CHANGE(IDC_TXT_UINT16_L, OnChangeTxtUint16L)
	ON_EN_CHANGE(IDC_TXT_UINT16_B, OnChangeTxtUint16B)
	ON_EN_CHANGE(IDC_TXT_UINT32_L, OnChangeTxtUint32L)
	ON_EN_CHANGE(IDC_TXT_UINT32_B, OnChangeTxtUint32B)
	ON_EN_CHANGE(IDC_TXT_UINT64_L, OnChangeTxtUint64L)
	ON_EN_CHANGE(IDC_TXT_UINT64_B, OnChangeTxtUint64B)
	ON_CBN_SELENDOK(IDC_CBO_DOUBLE, OnSelendokCboDouble)
	ON_CBN_SELENDOK(IDC_CBO_FLOAT, OnSelendokCboFloat)
	ON_BN_CLICKED(IDC_OPT_MBCS, OnOptCode)
	ON_BN_CLICKED(IDC_OPT_UNICODE, OnOptCode)
	ON_BN_CLICKED(IDC_OPT_UNICODE_BIG, OnOptCode)
	ON_BN_CLICKED(IDC_OPT_UTF7, OnOptCode)
	ON_BN_CLICKED(IDC_OPT_UTF8, OnOptCode)
	ON_EN_CHANGE(IDC_TXT_STRING, OnChangeTxtString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHexToNumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
    ((CEdit*)GetDlgItem(IDC_TXT_HEX     ))->LimitText(-1);
    ((CEdit*)GetDlgItem(IDC_TXT_STRING  ))->LimitText(-1);
    CString s;
    m_cboFloat.ResetContent();
    m_cboDouble.ResetContent();
    int     i;
    for(i = 1;i <= 20;i++)
    {
        s.Format(_T("%d"),i);
        m_cboFloat.AddString(s);
        m_cboDouble.AddString(s);
    }
    m_cboFloat.SetCurSel(7);
    m_cboDouble.SetCurSel(15);
	return TRUE;
}

void CHexToNumDlg::OnChangeTxtHex() 
{
    if(!m_bLock)
    {
        DoChangeTxtHex(IDC_TXT_HEX);
    }
}

void CHexToNumDlg::DoChangeTxtHex(UINT uID)
{
    HWND    hwndHex =   ::GetDlgItem(m_hWnd,IDC_TXT_HEX);    
    int     nLenA   =   ::GetWindowTextLengthA(hwndHex);
    BYTE*   szHex   =   NULL;
    int     nLen    =   0;      //二进制字符串长度

    if(nLenA)
    {//将十六进制的字符串转换为二进制字符串
        szHex       =   new BYTE[nLenA + 4];
        ::GetWindowTextA(hwndHex,(LPSTR)szHex,nLenA + 1);
        BOOL bFill  =   FALSE;  //一个字符的高4位是否已经填充
        BYTE nHex   =   255;

        for(int i = 0;i < nLenA;i++)
        {
            if(szHex[i] >= '0' && szHex[i] <= '9')
            {
                nHex = szHex[i] - '0';
            }
            else if(szHex[i] >= 'A' && szHex[i] <= 'F')
            {
                nHex = szHex[i] - 'A' + 10;
            }
            else if(szHex[i] >= 'a' && szHex[i] <= 'f')
            {
                nHex = szHex[i] - 'a' + 10;
            }
            else
            {
                nHex    =   255;
            }
            if(nHex < 16)
            {
                if(bFill)
                {//高4位已经填充
                    szHex[nLen] =   szHex[nLen] << 4 | nHex;
                    nLen++;
                }
                else
                {//高4位还未填充
                    szHex[nLen] =   nHex;
                }
                bFill   =   !bFill;
            }
            else
            {
                if(bFill)
                {//高4位已经填充
                    nLen++;
                    bFill   =   FALSE;
                }
            }
        }
        if(bFill)
        {//高4位已经填充
            nLen++;
            bFill   =   FALSE;
        }
    }
    {//显示字节数
        CString s;
        s.Format(_T("计算机内码(%d)"),nLen);
        GetDlgItem(IDC_TXT_HEX)->GetWindow(GW_HWNDNEXT)->SetWindowText(s);
    }
    m_bLock = TRUE;
    if(nLen)
    {
        char    szNum[32];
        int8    i8;
        SetVar(szHex,nLen,i8,FALSE);
        if(uID!=IDC_TXT_INT8_L)SetDlgItemInt(IDC_TXT_INT8_L  ,i8,TRUE);
        if(uID!=IDC_TXT_UINT8_L)SetDlgItemInt(IDC_TXT_UINT8_L ,(uint8)i8,FALSE);
        SetVar(szHex,nLen,i8,TRUE);
        if(uID!=IDC_TXT_INT8_B)SetDlgItemInt(IDC_TXT_INT8_B  ,i8,TRUE);
        if(uID!=IDC_TXT_UINT8_B)SetDlgItemInt(IDC_TXT_UINT8_B ,(uint8)i8,FALSE);
        int16   i16;
        SetVar(szHex,nLen,i16,FALSE);
        if(uID!=IDC_TXT_INT16_L)SetDlgItemInt(IDC_TXT_INT16_L ,i16,TRUE);
        if(uID!=IDC_TXT_UINT16_L)SetDlgItemInt(IDC_TXT_UINT16_L,(uint16)i16,FALSE);
        SetVar(szHex,nLen,i16,TRUE);
        if(uID!=IDC_TXT_INT16_B)SetDlgItemInt(IDC_TXT_INT16_B ,i16,TRUE);
        if(uID!=IDC_TXT_UINT16_B)SetDlgItemInt(IDC_TXT_UINT16_B,(uint16)i16,FALSE);
        int32   i32;
        SetVar(szHex,nLen,i32,FALSE);
        if(uID!=IDC_TXT_INT32_L)SetDlgItemInt(IDC_TXT_INT32_L ,i32,TRUE);
        if(uID!=IDC_TXT_UINT32_L)SetDlgItemInt(IDC_TXT_UINT32_L,i32,FALSE);
        SetVar(szHex,nLen,i32,TRUE);
        if(uID!=IDC_TXT_INT32_B)SetDlgItemInt(IDC_TXT_INT32_B ,i32,TRUE);
        if(uID!=IDC_TXT_UINT32_B)SetDlgItemInt(IDC_TXT_UINT32_B,i32,FALSE);
        int64   i64;
        SetVar(szHex,nLen,i64,FALSE);
        if(uID!=IDC_TXT_INT64_L)::SetDlgItemTextA(m_hWnd,IDC_TXT_INT64_L ,_i64toa(i64,szNum,10));
        if(uID!=IDC_TXT_UINT64_L)::SetDlgItemTextA(m_hWnd,IDC_TXT_UINT64_L,_ui64toa(i64,szNum,10));
        SetVar(szHex,nLen,i64,TRUE);
        if(uID!=IDC_TXT_INT64_B)::SetDlgItemTextA(m_hWnd,IDC_TXT_INT64_B ,_i64toa(i64,szNum,10));
        if(uID!=IDC_TXT_UINT64_B)::SetDlgItemTextA(m_hWnd,IDC_TXT_UINT64_B,_ui64toa(i64,szNum,10));
        float   real32;
        int     nFmtFloat   =   m_cboFloat.GetCurSel() + 1;
        int     nFmtDouble  =   m_cboDouble.GetCurSel() + 1;
        SetVar(szHex,nLen,real32,FALSE);
        sprintf(szNum,"%.*G",nFmtFloat,real32);
        if(uID!=IDC_TXT_FLOAT_L)::SetDlgItemTextA(m_hWnd,IDC_TXT_FLOAT_L ,szNum);
        SetVar(szHex,nLen,real32,TRUE);
        sprintf(szNum,"%.*G",nFmtFloat,real32);
        if(uID!=IDC_TXT_FLOAT_B)::SetDlgItemTextA(m_hWnd,IDC_TXT_FLOAT_B ,szNum);
        double  real64;
        SetVar(szHex,nLen,real64,FALSE);
        sprintf(szNum,"%.*lG",nFmtDouble,real64);
        if(uID!=IDC_TXT_DOUBLE_L)::SetDlgItemTextA(m_hWnd,IDC_TXT_DOUBLE_L ,szNum);
        SetVar(szHex,nLen,real64,TRUE);
        sprintf(szNum,"%.*lG",nFmtDouble,real64);
        if(uID!=IDC_TXT_DOUBLE_B)::SetDlgItemTextA(m_hWnd,IDC_TXT_DOUBLE_B ,szNum);

        if(uID!=IDC_TXT_STRING)
        {
            switch(m_iOptCode)
            {
            case 0://MBCS
                szHex[nLen] = '\0';
                ::SetDlgItemTextA(m_hWnd,IDC_TXT_STRING,(LPCSTR)szHex);
                break;
            case 1://Unicode
                {
                    int nLenW = (nLen >> 1);
                    if(nLenW)
                    {
                        nLen = nLenW << 1;
                        memset(szHex + nLen,0,2);
                        ::SetDlgItemTextW(m_hWnd,IDC_TXT_STRING,(LPCWSTR)szHex);
                    }
                    else
                    {
                        szHex[0] = '\0';
                        ::SetDlgItemTextA(m_hWnd,IDC_TXT_STRING,(LPCSTR)szHex);
                    }
                }
                break;
            case 2://Unicode Big
                {
                    int nLenW = (nLen >> 1);
                    if(nLenW)
                    {
                        nLen = nLenW << 1;
                        memset(szHex + nLen,0,2);
                        BYTE t;
                        for(int i = 0;i < nLen;i+=2)
                        {
                            t           =   szHex[i];
                            szHex[i]    =   szHex[i+1];
                            szHex[i+1]  =   t;
                        }
                        ::SetDlgItemTextW(m_hWnd,IDC_TXT_STRING,(LPCWSTR)szHex);
                    }
                    else
                    {
                        szHex[0] = '\0';
                        ::SetDlgItemTextA(m_hWnd,IDC_TXT_STRING,(LPCSTR)szHex);
                    }
                }
                break;
            case 3://UTF-7
            case 4://UTF-8
                {
                    UINT    uPage   =   CP_UTF8;
                    if(3==m_iOptCode)
                    {
                        uPage   =   CP_UTF7;
                    }
                    //先将UTF转换为Unicode
                    int nLenW   =   MultiByteToWideChar(uPage,0,(LPCSTR)szHex,nLen,NULL,0);
                    if(nLenW > 0)
                    {
                        wchar_t*wzStr   =   new wchar_t[nLenW + 1];
                        MultiByteToWideChar(uPage,0,(LPCSTR)szHex,nLen,wzStr,nLenW);
                        wzStr[nLenW]    =   L'\0';
                        ::SetDlgItemTextW(m_hWnd,IDC_TXT_STRING,wzStr);
                        delete[] wzStr;
                    }
                    else
                    {
                        szHex[0] = '\0';
                        ::SetDlgItemTextA(m_hWnd,IDC_TXT_STRING,(LPCSTR)szHex);
                    }
                }
                break;
            }
        }
    }
    else
    {
        TCHAR szNull[]={0};        
        if(uID!=IDC_TXT_INT8_L  )SetDlgItemText(IDC_TXT_INT8_L  ,szNull);
        if(uID!=IDC_TXT_INT16_L )SetDlgItemText(IDC_TXT_INT16_L ,szNull);
        if(uID!=IDC_TXT_INT32_L )SetDlgItemText(IDC_TXT_INT32_L ,szNull);
        if(uID!=IDC_TXT_INT64_L )SetDlgItemText(IDC_TXT_INT64_L ,szNull);
        if(uID!=IDC_TXT_UINT8_L )SetDlgItemText(IDC_TXT_UINT8_L ,szNull);
        if(uID!=IDC_TXT_UINT16_L)SetDlgItemText(IDC_TXT_UINT16_L,szNull);
        if(uID!=IDC_TXT_UINT32_L)SetDlgItemText(IDC_TXT_UINT32_L,szNull);
        if(uID!=IDC_TXT_UINT64_L)SetDlgItemText(IDC_TXT_UINT64_L,szNull);
        if(uID!=IDC_TXT_FLOAT_L )SetDlgItemText(IDC_TXT_FLOAT_L ,szNull);
        if(uID!=IDC_TXT_DOUBLE_L)SetDlgItemText(IDC_TXT_DOUBLE_L,szNull);
        if(uID!=IDC_TXT_INT8_B  )SetDlgItemText(IDC_TXT_INT8_B  ,szNull);
        if(uID!=IDC_TXT_INT16_B )SetDlgItemText(IDC_TXT_INT16_B ,szNull);
        if(uID!=IDC_TXT_INT32_B )SetDlgItemText(IDC_TXT_INT32_B ,szNull);
        if(uID!=IDC_TXT_INT64_B )SetDlgItemText(IDC_TXT_INT64_B ,szNull);
        if(uID!=IDC_TXT_UINT8_B )SetDlgItemText(IDC_TXT_UINT8_B ,szNull);
        if(uID!=IDC_TXT_UINT16_B)SetDlgItemText(IDC_TXT_UINT16_B,szNull);
        if(uID!=IDC_TXT_UINT32_B)SetDlgItemText(IDC_TXT_UINT32_B,szNull);
        if(uID!=IDC_TXT_UINT64_B)SetDlgItemText(IDC_TXT_UINT64_B,szNull);
        if(uID!=IDC_TXT_FLOAT_B )SetDlgItemText(IDC_TXT_FLOAT_B ,szNull);
        if(uID!=IDC_TXT_DOUBLE_B)SetDlgItemText(IDC_TXT_DOUBLE_B,szNull);
        if(uID!=IDC_TXT_STRING  )SetDlgItemText(IDC_TXT_STRING  ,szNull);
    }
    m_bLock = FALSE;
    if(szHex)
    {
        delete[] szHex;
    }
    {//显示字符数
        CString s;
        GetDlgItemText(IDC_TXT_STRING,s);
        int     nChar   =   _tcsclen(s);
        s.Format(_T("字符串(%d)"),nChar);
        GetDlgItem(IDC_TXT_STRING)->GetWindow(GW_HWNDNEXT)->SetWindowText(s);
    }
}

void CHexToNumDlg::OnChangeTxtDoubleL() 
{
    if(m_bLock)
    {
        return;
    }
    
    CString s;
    GetDlgItemText(IDC_TXT_DOUBLE_L,s);
    double  real = _tcstod(s,NULL);
    BYTE    pBuf[sizeof(real)];
    GetVar(pBuf,real,FALSE);
    CString sHex;
    for(int i=0;i<sizeof(real);i++)
    {
        s.Format(_T(" %02X"),pBuf[i]);
        sHex += s;
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex.Mid(1));
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_DOUBLE_L);
}

void CHexToNumDlg::OnChangeTxtDoubleB() 
{
    if(m_bLock)
    {
        return;
    }
    
    CString s;
    GetDlgItemText(IDC_TXT_DOUBLE_B,s);
    double  real = _tcstod(s,NULL);
    BYTE    pBuf[sizeof(real)];
    GetVar(pBuf,real,TRUE);
    CString sHex;
    for(int i=0;i<sizeof(real);i++)
    {
        s.Format(_T(" %02X"),pBuf[i]);
        sHex += s;
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex.Mid(1));
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_DOUBLE_B);
}

void CHexToNumDlg::OnChangeTxtFloatL() 
{
    if(m_bLock)
    {
        return;
    }
    
    CString s;
    GetDlgItemText(IDC_TXT_FLOAT_L,s);
    float   real = (float)_tcstod(s,NULL);
    BYTE    pBuf[sizeof(real)];
    GetVar(pBuf,real,FALSE);
    CString sHex;
    for(int i=0;i<sizeof(real);i++)
    {
        s.Format(_T(" %02X"),pBuf[i]);
        sHex += s;
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex.Mid(1));
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_FLOAT_L);
}

void CHexToNumDlg::OnChangeTxtFloatB() 
{
    if(m_bLock)
    {
        return;
    }
    
    CString s;
    GetDlgItemText(IDC_TXT_FLOAT_B,s);
    float   real = (float)_tcstod(s,NULL);
    BYTE    pBuf[sizeof(real)];
    GetVar(pBuf,real,TRUE);
    CString sHex;
    for(int i=0;i<sizeof(real);i++)
    {
        s.Format(_T(" %02X"),pBuf[i]);
        sHex += s;
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex.Mid(1));
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_FLOAT_B);
}

void CHexToNumDlg::OnChangeTxtInt8L()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    long    lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_INT8_L),-128,127,lng))
    {
        int8    i8  =   (int8)lng;
        BYTE    pBuf[sizeof(i8)];
        GetVar(pBuf,i8,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i8);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT8_L);
}

void CHexToNumDlg::OnChangeTxtInt8B()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    long    lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_INT8_B),-128,127,lng))
    {
        int8    i8  =   (int8)lng;
        BYTE    pBuf[sizeof(i8)];
        GetVar(pBuf,i8,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i8);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT8_B);
}

void CHexToNumDlg::OnChangeTxtInt16L()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    long    lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_INT16_L),-32768,32767,lng))
    {
        int16   i16  =   (int16)lng;
        BYTE    pBuf[sizeof(i16)];
        GetVar(pBuf,i16,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i16);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT16_L);
}

void CHexToNumDlg::OnChangeTxtInt16B()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    long    lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_INT16_B),-32768,32767,lng))
    {
        int16   i16  =   (int16)lng;
        BYTE    pBuf[sizeof(i16)];
        GetVar(pBuf,i16,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i16);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT16_B);
}

void CHexToNumDlg::OnChangeTxtInt32L()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    int32   i32;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_INT32_L),i32))
    {
        BYTE    pBuf[sizeof(i32)];
        GetVar(pBuf,i32,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i32);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT32_L);
}

void CHexToNumDlg::OnChangeTxtInt32B()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    int32   i32;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_INT32_B),i32))
    {
        BYTE    pBuf[sizeof(i32)];
        GetVar(pBuf,i32,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i32);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT32_B);
}

void CHexToNumDlg::OnChangeTxtInt64L()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    int64   i64;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_INT64_L),i64))
    {
        BYTE    pBuf[sizeof(i64)];
        GetVar(pBuf,i64,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i64);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT64_L);
}

void CHexToNumDlg::OnChangeTxtInt64B()
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    int64   i64;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_INT64_B),i64))
    {
        BYTE    pBuf[sizeof(i64)];
        GetVar(pBuf,i64,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i64);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_INT64_B);
}

void CHexToNumDlg::OnChangeTxtUint8L() 
{
    if(m_bLock)
    {
        return;
    }
    CString         sHex;
    unsigned long   lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_UINT8_L),0,255,lng))
    {
        uint8   i8  =   (uint8)lng;
        BYTE    pBuf[sizeof(i8)];
        GetVar(pBuf,i8,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i8);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT8_L);
}

void CHexToNumDlg::OnChangeTxtUint8B() 
{
    if(m_bLock)
    {
        return;
    }
    CString         sHex;
    unsigned long   lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_UINT8_B),0,255,lng))
    {
        uint8   i8  =   (uint8)lng;
        BYTE    pBuf[sizeof(i8)];
        GetVar(pBuf,i8,TRUE);
        CString s;
        for(int i=0;i<sizeof(i8);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT8_B);
}

void CHexToNumDlg::OnChangeTxtUint16L() 
{
    if(m_bLock)
    {
        return;
    }
    CString         sHex;
    unsigned long   lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_UINT16_L),0,65535,lng))
    {
        uint16  i16 =   (uint16)lng;
        BYTE    pBuf[sizeof(i16)];
        GetVar(pBuf,i16,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i16);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT16_L);
}

void CHexToNumDlg::OnChangeTxtUint16B() 
{
    if(m_bLock)
    {
        return;
    }
    CString         sHex;
    unsigned long   lng;
    if(GetTextBoxValMinMax((CEdit*)GetDlgItem(IDC_TXT_UINT16_B),0,65535,lng))
    {
        uint16  i16 =   (uint16)lng;
        BYTE    pBuf[sizeof(i16)];
        GetVar(pBuf,i16,TRUE);
        CString s;
        for(int i=0;i<sizeof(i16);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT16_B);
}

void CHexToNumDlg::OnChangeTxtUint32L() 
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    uint32  i32;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_UINT32_L),i32))
    {
        BYTE    pBuf[sizeof(i32)];
        GetVar(pBuf,i32,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i32);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT32_L);
}

void CHexToNumDlg::OnChangeTxtUint32B() 
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    uint32  i32;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_UINT32_B),i32))
    {
        BYTE    pBuf[sizeof(i32)];
        GetVar(pBuf,i32,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i32);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT32_B);
}

void CHexToNumDlg::OnChangeTxtUint64L() 
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    uint64  i64;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_UINT64_L),i64))
    {
        BYTE    pBuf[sizeof(i64)];
        GetVar(pBuf,i64,FALSE);    
        CString s;
        for(int i=0;i<sizeof(i64);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT64_L);
}

void CHexToNumDlg::OnChangeTxtUint64B() 
{
    if(m_bLock)
    {
        return;
    }
    CString sHex;
    uint64  i64;
    if(GetTextBoxVal((CEdit*)GetDlgItem(IDC_TXT_UINT64_B),i64))
    {
        BYTE    pBuf[sizeof(i64)];
        GetVar(pBuf,i64,TRUE);    
        CString s;
        for(int i=0;i<sizeof(i64);i++)
        {
            s.Format(_T(" %02X"),pBuf[i]);
            sHex += s;
        }
        sHex = sHex.Mid(1);
    }
    m_bLock = TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock = FALSE;
    DoChangeTxtHex(IDC_TXT_UINT64_B);
}

void CHexToNumDlg::OnSelendokCboDouble() 
{
	OnChangeTxtHex();
}

void CHexToNumDlg::OnSelendokCboFloat() 
{
	OnChangeTxtHex();
}

void CHexToNumDlg::OnOptCode() 
{
    int nOldCode = m_iOptCode;
	UpdateData();
    if(nOldCode != m_iOptCode)
    {
        OnChangeTxtString();
    }
}

void CHexToNumDlg::OnChangeTxtString() 
{
    CString sHex;
    HWND    hwndStr =   ::GetDlgItem(m_hWnd,IDC_TXT_STRING);
    switch(m_iOptCode)
    {
    case 0://MBCS
        {
            int nLenA   =   ::GetWindowTextLengthA(hwndStr);            
            if(nLenA)
            {
                BYTE*szStr  =   new BYTE[nLenA + 1];
                ::GetWindowTextA(hwndStr,(LPSTR)szStr,nLenA + 1);
                TCHAR*pBuf  =   sHex.GetBuffer(3 * (nLenA + 1));
                for(int i=0;i<nLenA;i++)
                {
                    _stprintf(pBuf + 3 * i,_T("%02X "),szStr[i]);
                }
                sHex.ReleaseBuffer(3 * nLenA - 1);
                delete[] szStr;
            }
        }
        break;
    case 1://Unicode
        {
            int     nLenW   =   ::GetWindowTextLengthW(hwndStr);            
            if(nLenW)
            {                
                int  nLenA  =   nLenW << 1;
                BYTE*szStr  =   new BYTE[(nLenW + 1) << 1];
                ::GetWindowTextW(hwndStr,(LPWSTR)szStr,nLenW + 1);
                TCHAR*pBuf  =   sHex.GetBuffer(3 * (nLenA + 1));
                for(int i=0;i < nLenA;i++)
                {
                    _stprintf(pBuf + 3 * i,_T("%02X "),szStr[i]);
                }
                sHex.ReleaseBuffer(3 * nLenA - 1);
                delete[] szStr;
            }
        }
        break;
    case 2://Unicode Big
        {
            int     nLenW   =   ::GetWindowTextLengthW(hwndStr);
            BYTE*   szStr   =   NULL;
            //int     nLen    =   0;      //二进制字符串长度

            if(nLenW)
            {//将十六进制的字符串转换为二进制字符串
                int nLenA   =   nLenW << 1;
                szStr       =   new BYTE[(nLenW + 1) << 1];
                ::GetWindowTextW(hwndStr,(LPWSTR)szStr,nLenW + 1);
                TCHAR*pBuf  =   sHex.GetBuffer(3 * (nLenA + 1));
                int   p     =   0;
                for(int i=0;i < nLenW;i++)
                {
                    _stprintf(pBuf + 6 * i,_T("%02X %02X "),szStr[p + 1],szStr[p]);
                    p  +=  2;
                }
                sHex.ReleaseBuffer(3 * nLenA - 1);
                delete[] szStr;
            }
        }
        break;
    case 3://UTF-7
    case 4://UTF-8
        {
            int nLenW = ::GetWindowTextLengthW(hwndStr);            
            if(nLenW)
            {
                wchar_t*wzStr   =   new wchar_t[nLenW + 1];
                UINT    uPage   =   CP_UTF8;
                if(3==m_iOptCode)
                {
                    uPage   =   CP_UTF7;
                }
                ::GetWindowTextW(hwndStr,wzStr,nLenW + 1);
                //将Unicode转换为UTF-8
                int     nLenA   =   WideCharToMultiByte(uPage,0,wzStr,nLenW,NULL,0,NULL,NULL); 
                if(nLenA > 0)
                {
                    BYTE*   szUTF  =   new BYTE[nLenA];
                    WideCharToMultiByte(uPage,0,wzStr,nLenW,(char*)szUTF,nLenA,NULL,NULL);
                    TCHAR*  pBuf    =   sHex.GetBuffer(3 * (nLenA + 1));
                    for(int i = 0;i < nLenA;i++)
                    {
                        _stprintf(pBuf + 3 * i,_T("%02X "),szUTF[i]);
                    }
                    sHex.ReleaseBuffer(3 * nLenA - 1);
                    delete[] szUTF;
                }
                delete[] wzStr;
            }
        }
        break;
    }
    m_bLock =   TRUE;
    SetDlgItemText(IDC_TXT_HEX,sHex);
    m_bLock =   FALSE;
    DoChangeTxtHex(IDC_TXT_STRING);
}
