// SixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Six.h"
#include "SixDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSixDlg dialog

CSixDlg::CSixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSixDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
	int i;
	for(i=0;i<21;i++)
	{
		m_DD[i]=0;
    m_LL[i]=0;
	}
}

CSixDlg::~CSixDlg()
{
}

void CSixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSixDlg)
	//}}AFX_DATA_MAP
	int i;
	BOOL f;
	f=pDX->m_bSaveAndValidate;
	for(i=0;i<21;i++)
	{
		DDX_Text(pDX,IDC_D0+i,m_DD[i]);
		if(pDX->m_bSaveAndValidate!=f)break;
    DDX_Text(pDX,IDC_L0+i,m_LL[i]);
		if(pDX->m_bSaveAndValidate!=f)break;
	}
}

BEGIN_MESSAGE_MAP(CSixDlg, CDialog)
	//{{AFX_MSG_MAP(CSixDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CAL, OnCal)
	ON_BN_CLICKED(IDC_BTNLOAD, OnBtnLoad)
	ON_BN_CLICKED(IDC_BTNSAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTNCLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSixDlg message handlers

BOOL CSixDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int i;
	for(i=0;i<21;i++)
  {
    m_MyEdit[i].SubclassDlgItem(IDC_D0+i,this);
    m_MyEdit[i+21].SubclassDlgItem(IDC_L0+i,this);
		GetDlgItem(IDC_NAME0+i)->SetWindowText(GetSegmentName(i));
	}	
	m_DD[0]= 24.0219;
  m_DD[1]= 72.0749;
	m_DD[2]= 168.1593;
  m_DD[3]= 336.2846;
  m_DD[4]= 600.0579;
  m_DD[5]= 959.7475;
  m_DD[6]= 48.053;
  m_DD[7]= 144.1374;
  m_DD[8]= 312.2627;
  m_DD[9]= 576.036;
  m_DD[10]= 935.7256;
  m_DD[11]= 98.0844;
  m_DD[12]= 264.2097;
  m_DD[13]= 527.983;
  m_DD[14]= 887.6726;
  m_DD[15]= 168.1253;
  m_DD[16]= 431.8986;
  m_DD[17]= 791.5882;
  m_DD[18]= 263.7733;
  m_DD[19]= 623.4629;
  m_DD[20]= 359.6896;
  
  m_LL[0]= 24.0253;
  m_LL[1]= 72.0767;
  m_LL[2]= 168.1623;
  m_LL[3]= 336.2901;
  m_LL[4]= 600.0616;
  m_LL[5]= 959.7378;
  m_LL[6]= 48.0585;
  m_LL[7]= 144.1426;
  m_LL[8]= 312.2694;
  m_LL[9]= 576.0459;
  m_LL[10]= 935.7379;
  m_LL[11]= 98.0905;
  m_LL[12]= 264.2114;
  m_LL[13]= 527.9867;
  m_LL[14]= 887.6771;
  m_LL[15]= 168.1299;
  m_LL[16]= 431.9028;
  m_LL[17]= 791.5931;
  m_LL[18]= 263.7757;
  m_LL[19]= 623.4676;
  m_LL[20]= 359.693;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSixDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSixDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSixDlg::OnOK() 
{
	// TODO: Add extra validation here
}

void CSixDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
}

void CSixDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnCancel();
}

void CSixDlg::OnCal() 
{
  double B[21][2],L[21];
  double N[2][2], U[2],Q[2][2];
  double KK, RR;
  int i,j,k;
  double t,VTV;
  double mD, mK, mR;
	CString str;
  CString s;
	double MaxDiff;
	int idxMaxDiff;

	if(!UpdateData())return;
  
  MaxDiff=0;
	idxMaxDiff=0;
  for(i=0;i<21;i++)
	{
    B[i][0]= -1;
    B[i][1]= -m_LL[i] / 1000;
    L[i]= (m_DD[i] - m_LL[i]) * 1000;
		if (fabs(MaxDiff) < fabs(L[i]))
		{
			MaxDiff = L[i];
			idxMaxDiff=i;
		}
  }
  for(i=0;i<2;i++)
	{
    for(j = i;j<2;j++)
		{
      t = 0;
      for(k = 0;k<21;k++)
        t += B[k][i] * B[k][j];
      N[i][j]= t;
      if( i != j)N[j][i]= t;
    }
    t = 0;
    for(k = 0;k<21;k++)
      t += B[k][i] * L[k];
    U[i]= t;
  }
	//无乘常数-----------------------
  Q[0][0]= 1 / N[0][0];
  KK = -Q[0][0] * U[0];
  RR = 0;
  VTV = 0;
  for(i = 0;i<21;i++)
	{
    t = -KK + B[i][1] * RR + L[i];
    VTV = VTV + t * t;
  }
	str.Format(_T("最大差值 %s: %.2lfmm\r\n**** 无乘常数 ****\r\n"),
		         GetSegmentName(idxMaxDiff),MaxDiff);
  mD = sqrt(VTV / 20);
  mK = mD * sqrt(Q[0][0]);
	s.Format(_T("加常数 K=%.2lfmm\r\n单位权中误差 Md=%.2lf\r\n加常数中误差 Mk=%.2lfmm"),
		         KK,mD,mK);
	str+=s;
	//有乘常数-----------------------
	str+=_T("\r\n**** 有乘常数 ****\r\n");
  t = N[0][0] * N[1][1] - N[0][1] * N[1][0];
	if(fabs(t)<1e-11)
	{
		s=_T("无法计算!");
	}
	else
	{
		t = 1 / t;
		Q[0][0]= N[1][1] * t;
		Q[0][1]= -N[1][0] * t;
		Q[1][0]= Q[0][1];
		Q[1][1]= N[0][0] * t;
		KK = -Q[0][0] * U[0] - Q[0][1] * U[1];
		RR = -Q[1][0] * U[0] - Q[1][1] * U[1];
		VTV = 0;
		for(i = 0;i<21;i++)
		{
			t = -KK + B[i][1] * RR + L[i];
			VTV = VTV + t * t;
		}
		mD = sqrt(VTV / 19);
		mK = mD * sqrt(Q[0][0]);
		mR = mD * sqrt(Q[1][1]);
		s.Format(_T("加常数 K=%.2lfmm\r\n乘常数 R=%.2lfppm\r\n单位权中误差 Md=%.2lf\r\n加常数中误差 Mk=%.2lfmm\r\n乘常数中误差 Mr=%.2lfppm"),
							 KK,RR,mD,mK,mR);
	}
	str+=s;
	GetDlgItem(IDC_TXT)->SetWindowText(str);	
}

void CSixDlg::OnBtnLoad() 
{
	CFileDialog dlg(TRUE,NULL,NULL);
	dlg.m_ofn.Flags |=OFN_FILEMUSTEXIST; 
	if(dlg.DoModal()!=IDOK)return;
	TRY
	{
		CFile f(dlg.GetPathName(),CFile::modeRead);
		f.Read(m_DD,sizeof(m_DD));
		f.Read(m_LL,sizeof(m_LL));
		f.Close();
	}
	CATCH( CFileException, e )
	{
		AfxMessageBox(_T("打开文件时出错！"));
		return;
	}
	END_CATCH
  UpdateData(FALSE);
}

int CSixDlg::GetK(int i,int j)
{
	 return 6 * i - i * (i + 1) / 2 + j - 1;
}

void CSixDlg::GetIJ(int k,int &i,int &j)
{
  int m;
  i = 0;
  for(m = 4;m>=0;m--)
	{
    if(k > GetK(m, 6))
		{
      i = m + 1;
      break;
    }
  }
  j = 6 + k - GetK(i, 6);
	return;
}

CString CSixDlg::GetSegmentName(int k)
{
	int i,j;
	CString str;
	GetIJ(k,i,j);
  str.Format(_T("%d-%d"),i,j);
	return str;
}

void CSixDlg::OnBtnSave() 
{
	CFileDialog dlg(FALSE,NULL,NULL);
	if(!UpdateData())return;
	if(dlg.DoModal()!=IDOK)return;
	TRY
	{
		CFile f(dlg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
		f.Write(m_DD,sizeof(m_DD));
		f.Write(m_LL,sizeof(m_LL));
		f.Close();		
	}
	CATCH( CFileException, e )
	{
		AfxMessageBox(_T("保存文件时出错！"));
	}
	END_CATCH
}

void CSixDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}
