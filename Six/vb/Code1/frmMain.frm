VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "六段比较法"
   ClientHeight    =   5475
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   8595
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   ScaleHeight     =   5475
   ScaleWidth      =   8595
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton cmdExit 
      Caption         =   "关闭(&X)"
      Height          =   435
      Left            =   7500
      TabIndex        =   73
      Top             =   4980
      Width           =   1035
   End
   Begin MSComDlg.CommonDialog ComDlg 
      Left            =   7140
      Top             =   2280
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton cmdSave 
      Caption         =   "保存(&S)"
      Height          =   435
      Left            =   7500
      TabIndex        =   72
      Top             =   4320
      Width           =   1035
   End
   Begin VB.CommandButton cmdLoad 
      Caption         =   "载入(&L)"
      Height          =   435
      Left            =   7500
      TabIndex        =   71
      Top             =   3660
      Width           =   1035
   End
   Begin VB.TextBox txtJG 
      Height          =   2415
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   43
      Text            =   "frmMain.frx":0000
      Top             =   3000
      Width           =   7335
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   20
      Left            =   7440
      TabIndex        =   20
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   17
      Left            =   7440
      TabIndex        =   17
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   14
      Left            =   7440
      TabIndex        =   14
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   11
      Left            =   7440
      TabIndex        =   11
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   8
      Left            =   7440
      TabIndex        =   8
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   5
      Left            =   7440
      TabIndex        =   5
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   2
      Left            =   7440
      TabIndex        =   2
      Top             =   300
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   19
      Left            =   4545
      TabIndex        =   19
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   18
      Left            =   1650
      TabIndex        =   18
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   20
      Left            =   6195
      TabIndex        =   41
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   19
      Left            =   3300
      TabIndex        =   40
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   18
      Left            =   420
      TabIndex        =   39
      Top             =   2580
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   16
      Left            =   4545
      TabIndex        =   16
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   15
      Left            =   1650
      TabIndex        =   15
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   17
      Left            =   6195
      TabIndex        =   38
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   16
      Left            =   3300
      TabIndex        =   37
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   15
      Left            =   420
      TabIndex        =   36
      Top             =   2205
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   13
      Left            =   4545
      TabIndex        =   13
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   12
      Left            =   1650
      TabIndex        =   12
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   14
      Left            =   6195
      TabIndex        =   35
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   13
      Left            =   3300
      TabIndex        =   34
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   12
      Left            =   420
      TabIndex        =   33
      Top             =   1815
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   10
      Left            =   4545
      TabIndex        =   10
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   9
      Left            =   1650
      TabIndex        =   9
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   11
      Left            =   6195
      TabIndex        =   32
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   10
      Left            =   3300
      TabIndex        =   31
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   9
      Left            =   420
      TabIndex        =   30
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   7
      Left            =   4545
      TabIndex        =   7
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   6
      Left            =   1650
      TabIndex        =   6
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   8
      Left            =   6195
      TabIndex        =   29
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   7
      Left            =   3300
      TabIndex        =   28
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   6
      Left            =   420
      TabIndex        =   27
      Top             =   1065
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   4
      Left            =   4545
      TabIndex        =   4
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   3
      Left            =   1650
      TabIndex        =   3
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   5
      Left            =   6195
      TabIndex        =   26
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   4
      Left            =   3300
      TabIndex        =   25
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   3
      Left            =   420
      TabIndex        =   24
      Top             =   675
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   1
      Left            =   4545
      TabIndex        =   1
      Top             =   300
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   0
      Left            =   1650
      TabIndex        =   0
      Top             =   300
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   2
      Left            =   6195
      TabIndex        =   23
      Top             =   300
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   1
      Left            =   3300
      TabIndex        =   22
      Top             =   300
      Width           =   1095
   End
   Begin VB.TextBox txtDD 
      Height          =   300
      Index           =   0
      Left            =   420
      TabIndex        =   21
      Top             =   300
      Width           =   1095
   End
   Begin VB.CommandButton cmdCal 
      Caption         =   "计算(&C)"
      Height          =   435
      Left            =   7500
      TabIndex        =   42
      Top             =   3000
      Width           =   1035
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   20
      Left            =   5850
      TabIndex        =   70
      Top             =   2640
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   19
      Left            =   2955
      TabIndex        =   69
      Top             =   2640
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   18
      Left            =   60
      TabIndex        =   68
      Top             =   2640
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   17
      Left            =   5850
      TabIndex        =   67
      Top             =   2265
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   16
      Left            =   2955
      TabIndex        =   66
      Top             =   2265
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   15
      Left            =   60
      TabIndex        =   65
      Top             =   2265
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   14
      Left            =   5850
      TabIndex        =   64
      Top             =   1875
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   13
      Left            =   2955
      TabIndex        =   63
      Top             =   1875
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   12
      Left            =   60
      TabIndex        =   62
      Top             =   1875
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   11
      Left            =   5850
      TabIndex        =   61
      Top             =   1500
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   10
      Left            =   2955
      TabIndex        =   60
      Top             =   1500
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   9
      Left            =   60
      TabIndex        =   59
      Top             =   1500
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   8
      Left            =   5850
      TabIndex        =   58
      Top             =   1125
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   7
      Left            =   2955
      TabIndex        =   57
      Top             =   1125
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   6
      Left            =   60
      TabIndex        =   56
      Top             =   1125
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   5
      Left            =   5850
      TabIndex        =   55
      Top             =   735
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   4
      Left            =   2955
      TabIndex        =   54
      Top             =   735
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   3
      Left            =   60
      TabIndex        =   53
      Top             =   735
      Width           =   270
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "测量值"
      Height          =   180
      Left            =   4815
      TabIndex        =   52
      Top             =   60
      Width           =   540
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "测量值"
      Height          =   180
      Left            =   1920
      TabIndex        =   51
      Top             =   60
      Width           =   540
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      Caption         =   "测量值"
      Height          =   180
      Left            =   7710
      TabIndex        =   50
      Top             =   60
      Width           =   540
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "基线长"
      Height          =   180
      Left            =   6465
      TabIndex        =   49
      Top             =   60
      Width           =   540
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "基线长"
      Height          =   180
      Left            =   3570
      TabIndex        =   48
      Top             =   60
      Width           =   540
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   2
      Left            =   5850
      TabIndex        =   47
      Top             =   360
      Width           =   270
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   1
      Left            =   2955
      TabIndex        =   46
      Top             =   360
      Width           =   270
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "基线长"
      Height          =   180
      Left            =   690
      TabIndex        =   45
      Top             =   60
      Width           =   540
   End
   Begin VB.Label lblSegmentName 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      Height          =   180
      Index           =   0
      Left            =   60
      TabIndex        =   44
      Top             =   360
      Width           =   270
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim m_DD(20) As Double, m_LL(20) As Double

Private Sub cmdCal_Click()
  Dim B(20, 1) As Double
  Dim L(20) As Double
  Dim N(1, 1) As Double
  Dim U(1) As Double
  Dim Q(1, 1) As Double
  Dim KK As Double, RR As Double
  Dim MaxDiff As Double, idxMaxDiff As Integer
  Dim str As String
  Dim i As Integer, j As Integer, k As Integer
  Dim t As Double
  Dim VTV As Double
  Dim mD As Double, mK As Double, mR As Double
      
  If Not GetInput() Then
    Exit Sub
  End If
  
  On Error GoTo Err
  MaxDiff = 0
  idxMaxDiff = 0
  For i = 0 To 20
    B(i, 0) = -1
    B(i, 1) = -m_LL(i) / 1000
    L(i) = (m_DD(i) - m_LL(i)) * 1000
    If Abs(MaxDiff) < Abs(L(i)) Then
      MaxDiff = L(i)
      idxMaxDiff = i
    End If
  Next
  For i = 0 To 1
    For j = i To 1
      t = 0
      For k = 0 To 20
        t = t + B(k, i) * B(k, j)
      Next
      N(i, j) = t
      If i <> j Then
        N(j, i) = t
      End If
    Next
    t = 0
    For k = 0 To 20
      t = t + B(k, i) * L(k)
    Next
    U(i) = t
  Next
  GetIJ idxMaxDiff, i, j
  str = "最大较差段 " & i & "-" & j & " : " & FormatNumber(MaxDiff, 2, vbTrue, vbFalse, vbFalse) & "mm"
  '---------------------------
  str = str & vbCrLf & "**** 无乘常数 ****"
  Q(0, 0) = 1 / N(0, 0)
  KK = -Q(0, 0) * U(0)
  RR = 0
  VTV = 0
  For i = 0 To 20
    t = -KK + B(i, 1) * RR + L(i)
    VTV = VTV + t * t
  Next
  mD = Sqr(VTV / 20)
  mK = mD * Sqr(Q(0, 0))
  str = str & vbCrLf & "加常数 = " & FormatNumber(KK, 2, vbTrue, vbFalse, vbFalse) & "mm"
  str = str & vbCrLf & "单位权中误差 = " & FormatNumber(mD, 2, vbTrue, vbFalse, vbFalse)
  str = str & vbCrLf & "加常数中误差 = " & FormatNumber(mK, 2, vbTrue, vbFalse, vbFalse) & "mm"
  '----------------------------------------
  str = str & vbCrLf & "**** 有乘常数 ****"
  t = N(0, 0) * N(1, 1) - N(0, 1) * N(1, 0)
  If Abs(t) < 0.0000000001 Then
    str = str & vbCrLf & "无法计算！"
  Else
    t = 1 / t
    Q(0, 0) = N(1, 1) * t
    Q(0, 1) = -N(1, 0) * t
    Q(1, 0) = Q(0, 1)
    Q(1, 1) = N(0, 0) * t
    KK = -Q(0, 0) * U(0) - Q(0, 1) * U(1)
    RR = -Q(1, 0) * U(0) - Q(1, 1) * U(1)
    VTV = 0
    For i = 0 To 20
      t = -KK + B(i, 1) * RR + L(i)
      VTV = VTV + t * t
    Next
    mD = Sqr(VTV / 19)
    mK = mD * Sqr(Q(0, 0))
    mR = mD * Sqr(Q(1, 1))
    str = str & vbCrLf & "加常数 = " & FormatNumber(KK, 2, vbTrue, vbFalse, vbFalse) & "mm"
    str = str & vbCrLf & "乘常数 = " & FormatNumber(RR, 2, vbTrue, vbFalse, vbFalse) & "ppm"
    str = str & vbCrLf & "单位权中误差 = " & FormatNumber(mD, 2, vbTrue, vbFalse, vbFalse)
    str = str & vbCrLf & "加常数中误差 = " & FormatNumber(mK, 2, vbTrue, vbFalse, vbFalse) & "mm"
    str = str & vbCrLf & "乘常数中误差 = " & FormatNumber(mR, 2, vbTrue, vbFalse, vbFalse) & "ppm"
  End If
  txtJG.Text = str
  Exit Sub
Err:
  txtJG.Text = "发生计算错误!"
End Sub

'根据i,j计算k
Private Function GetK(i As Integer, j As Integer) As Integer
  GetK = 6 * i - i * (i + 1) / 2 + j - 1
End Function

'根据k计算i,j
Private Sub GetIJ(k As Integer, i As Integer, j As Integer)
  Dim m As Integer
  i = 0
  For m = 4 To 0 Step -1
    If k > GetK(m, 6) Then
      i = m + 1
      Exit For
    End If
  Next
  j = 6 + k - GetK(i, 6)
End Sub

Private Sub cmdExit_Click()
  Unload Me
End Sub

Private Sub cmdLoad_Click()
  Dim hFile As Long
  Dim r As Long
  Dim fname As String
  Dim i As Integer, j As Integer
  
  With ComDlg
    .DialogTitle = "打开文件"
    .FileName = ""
    .Flags = cdlOFNFileMustExist
    .ShowOpen
    fname = .FileName
  End With
  If Len(fname) = 0 Then
    Exit Sub
  End If
  
  hFile = CreateFile(fname, &H80000000, 0, 0, 3, &H80, 0)
  If hFile <> -1 Then
    ReadFile hFile, VarPtr(m_DD(0)), 168, r, 0
    ReadFile hFile, VarPtr(m_LL(0)), 168, r, 0
    For i = 0 To 20
      For j = 0 To 9
        ReadFile hFile, VarPtr(g_LLL(i, j)), 8, r, 0
      Next
    Next
    CloseHandle hFile
    For i = 0 To 20
      txtDD(i).Text = m_DD(i)
      txtLL(i).Text = m_LL(i)
    Next
    MoveFocusTo txtLL(0)
  End If
End Sub

Private Sub cmdSave_Click()
  Dim hFile As Long
  Dim w As Long
  Dim fname As String
  Dim i As Integer, j As Integer
  
  If Not GetInput() Then
    Exit Sub
  End If
  
  With ComDlg
    .DialogTitle = "保存到文件"
    .FileName = ""
    .Flags = cdlOFNOverwritePrompt + cdlOFNPathMustExist
    .ShowSave
    fname = .FileName
    If Len(fname) = 0 Then
      Exit Sub
    End If
  End With

  hFile = CreateFile(fname, &H40000000, 0, 0, 2, &H80, 0)
  If hFile <> -1 Then
    WriteFile hFile, VarPtr(m_DD(0)), 168, w, 0
    WriteFile hFile, VarPtr(m_LL(0)), 168, w, 0
    For i = 0 To 20
      For j = 0 To 9
        WriteFile hFile, VarPtr(g_LLL(i, j)), 8, w, 0
      Next
    Next
    CloseHandle hFile
  End If
End Sub

Private Sub Form_Load()
  Dim i As Integer, j As Integer, k As Integer
  
  m_DD(0) = 24.0219
  m_DD(1) = 72.0749
  m_DD(2) = 168.1593
  m_DD(3) = 336.2846
  m_DD(4) = 600.0579
  m_DD(5) = 959.7475
  m_DD(6) = 48.053
  m_DD(7) = 144.1374
  m_DD(8) = 312.2627
  m_DD(9) = 576.036
  m_DD(10) = 935.7256
  m_DD(11) = 98.0844
  m_DD(12) = 264.2097
  m_DD(13) = 527.983
  m_DD(14) = 887.6726
  m_DD(15) = 168.1253
  m_DD(16) = 431.8986
  m_DD(17) = 791.5882
  m_DD(18) = 263.7733
  m_DD(19) = 623.4629
  m_DD(20) = 359.6896
  
  m_LL(0) = 24.0253
  m_LL(1) = 72.0767
  m_LL(2) = 168.1623
  m_LL(3) = 336.2901
  m_LL(4) = 600.0616
  m_LL(5) = 959.7378
  m_LL(6) = 48.0585
  m_LL(7) = 144.1426
  m_LL(8) = 312.2694
  m_LL(9) = 576.0459
  m_LL(10) = 935.7379
  m_LL(11) = 98.0905
  m_LL(12) = 264.2114
  m_LL(13) = 527.9867
  m_LL(14) = 887.6771
  m_LL(15) = 168.1299
  m_LL(16) = 431.9028
  m_LL(17) = 791.5931
  m_LL(18) = 263.7757
  m_LL(19) = 623.4676
  m_LL(20) = 359.693
  
  For i = 0 To 20
    For j = 0 To 9
      g_LLL(i, j) = m_LL(i)
    Next
  Next
  
  k = 0
  For i = 0 To 5
    For j = i + 1 To 6
      lblSegmentName(k).Caption = i & "-" & j
      txtDD(k).Text = m_DD(k)
      txtLL(k).Text = m_LL(k)
      k = k + 1
    Next
  Next
  MoveFocusTo txtLL(0)
End Sub

Private Sub txtDD_KeyPress(Index As Integer, KeyAscii As Integer)
  If GoodChar(KeyAscii) Then
    Exit Sub
  End If
  If KeyAscii = 13 Then
    If Index < 20 Then
      MoveFocusTo txtDD(Index + 1)
    Else
      MoveFocusTo txtLL(0)
    End If
  End If
  KeyAscii = 0
End Sub

Private Sub InputLLL(Index As Integer)
  Dim i As Integer, j As Integer
  Load frmInputL
  GetIJ Index, i, j
  frmInputL.Caption = i & "-" & j & " 距离测量值"
  For i = 0 To 9
    frmInputL.txtLL(i).Text = g_LLL(Index, i)
  Next
  frmInputL.gidxLL = Index
  frmInputL.Show vbModal
  If frmInputL.gblnOK Then
    txtLL(Index).Text = frmInputL.gLL
  End If
  MoveFocusTo txtLL(Index)
End Sub

Private Sub txtLL_KeyPress(Index As Integer, KeyAscii As Integer)
  If GoodChar(KeyAscii) Then
    Exit Sub
  End If
  If KeyAscii = 13 Then
    If Index < 20 Then
      MoveFocusTo txtLL(Index + 1)
    Else
      MoveFocusTo txtDD(0)
    End If
  End If
  If KeyAscii = 32 Then
    InputLLL Index
  End If
  KeyAscii = 0
End Sub

Private Function GetInput() As Boolean
  Dim i As Integer
  GetInput = False
  For i = 0 To 20
    If Not GetTextBoxVal(txtDD(i), vbDouble, m_DD(i)) Then
      Exit Function
    End If
    If Not GetTextBoxVal(txtLL(i), vbDouble, m_LL(i)) Then
      Exit Function
    End If
  Next
  GetInput = True
End Function
