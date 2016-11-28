VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "六段解析法"
   ClientHeight    =   4950
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5940
   LinkTopic       =   "Form1"
   ScaleHeight     =   4950
   ScaleWidth      =   5940
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   20
      Left            =   4530
      TabIndex        =   20
      Top             =   3120
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   19
      Left            =   2565
      TabIndex        =   19
      Top             =   3120
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   18
      Left            =   600
      TabIndex        =   18
      Top             =   3120
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   17
      Left            =   4530
      TabIndex        =   17
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   16
      Left            =   2565
      TabIndex        =   16
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   15
      Left            =   600
      TabIndex        =   15
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   14
      Left            =   4530
      TabIndex        =   14
      Top             =   2160
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   13
      Left            =   2565
      TabIndex        =   13
      Top             =   2160
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   12
      Left            =   600
      TabIndex        =   12
      Top             =   2160
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   11
      Left            =   4530
      TabIndex        =   11
      Top             =   1680
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   10
      Left            =   2565
      TabIndex        =   10
      Top             =   1680
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   9
      Left            =   600
      TabIndex        =   9
      Top             =   1680
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   8
      Left            =   4530
      TabIndex        =   8
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   7
      Left            =   2565
      TabIndex        =   7
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   6
      Left            =   600
      TabIndex        =   6
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   5
      Left            =   4530
      TabIndex        =   5
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   4
      Left            =   2565
      TabIndex        =   4
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   3
      Left            =   600
      TabIndex        =   3
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   2
      Left            =   4530
      TabIndex        =   2
      Top             =   240
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   1
      Left            =   2565
      TabIndex        =   1
      Top             =   240
      Width           =   1215
   End
   Begin VB.TextBox txtDij 
      Height          =   375
      Index           =   0
      Left            =   600
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton cmdData 
      Caption         =   "示例数据"
      Height          =   495
      Left            =   383
      TabIndex        =   21
      Top             =   4400
      Width           =   1215
   End
   Begin VB.CommandButton cmdCal 
      Caption         =   "计算"
      Height          =   495
      Left            =   2363
      TabIndex        =   22
      Top             =   4400
      Width           =   1215
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "退出"
      Height          =   495
      Left            =   4343
      TabIndex        =   23
      Top             =   4400
      Width           =   1215
   End
   Begin VB.Label lblTip 
      AutoSize        =   -1  'True
      Caption         =   "提示：将鼠标移动到前 6 段的文本框中，可显示平差值和精度。"
      Height          =   180
      Left            =   240
      TabIndex        =   46
      Top             =   4080
      Width           =   5130
   End
   Begin VB.Label lblK 
      AutoSize        =   -1  'True
      Caption         =   "K=1.23mm+12.3mm"
      Height          =   180
      Left            =   240
      TabIndex        =   45
      Top             =   3720
      Width           =   1350
   End
   Begin VB.Label Label21 
      AutoSize        =   -1  'True
      Caption         =   "5-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   44
      Top             =   3210
      Width           =   315
   End
   Begin VB.Label Label20 
      AutoSize        =   -1  'True
      Caption         =   "0-3"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   43
      Top             =   330
      Width           =   315
   End
   Begin VB.Label Label19 
      AutoSize        =   -1  'True
      Caption         =   "0-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   42
      Top             =   810
      Width           =   315
   End
   Begin VB.Label Label18 
      AutoSize        =   -1  'True
      Caption         =   "1-4"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   41
      Top             =   1290
      Width           =   315
   End
   Begin VB.Label Label17 
      AutoSize        =   -1  'True
      Caption         =   "2-3"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   40
      Top             =   1770
      Width           =   315
   End
   Begin VB.Label Label16 
      AutoSize        =   -1  'True
      Caption         =   "2-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   39
      Top             =   2250
      Width           =   315
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      Caption         =   "3-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   4155
      TabIndex        =   38
      Top             =   2730
      Width           =   315
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "4-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   37
      Top             =   3210
      Width           =   315
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "3-5"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   36
      Top             =   2730
      Width           =   315
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      Caption         =   "3-4"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   35
      Top             =   2730
      Width           =   315
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      Caption         =   "2-4"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   34
      Top             =   2250
      Width           =   315
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      Caption         =   "1-5"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   33
      Top             =   1770
      Width           =   315
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      Caption         =   "1-2"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   32
      Top             =   1290
      Width           =   315
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      Caption         =   "0-4"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   31
      Top             =   810
      Width           =   315
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      Caption         =   "0-1"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   30
      Top             =   330
      Width           =   315
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      Caption         =   "2-5"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   29
      Top             =   2250
      Width           =   315
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      Caption         =   "1-6"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   28
      Top             =   1770
      Width           =   315
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      Caption         =   "1-3"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   27
      Top             =   1290
      Width           =   315
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "0-5"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   26
      Top             =   810
      Width           =   315
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "0-2"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   2160
      TabIndex        =   25
      Top             =   330
      Width           =   315
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "4-5"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Left            =   240
      TabIndex        =   24
      Top             =   3210
      Width           =   315
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'----------------------------------------------------------
'          六段解析法计算
'
'编制：Hanford
'时间：2002-06-20
'
'----------------------------------------------------------

Option Explicit

Private Sub cmdCal_Click()
  Dim i As Integer, j As Integer, k As Integer
  Dim dbl As Double
  
  If InputIsGood() Then
    Call CalK    '求加常数
    Call ChgDis  '更新显示
  End If
End Sub

Private Sub cmdData_Click()
  txtDij(0).Text = 50.059
  txtDij(1).Text = 150.065
  txtDij(2).Text = 500.46
  txtDij(3).Text = 550.472
  txtDij(4).Text = 800.632
  txtDij(5).Text = 1500.841
  txtDij(6).Text = 100.005
  txtDij(7).Text = 450.4
  txtDij(8).Text = 500.411
  txtDij(9).Text = 750.57
  txtDij(10).Text = 1450.781
  txtDij(11).Text = 350.394
  txtDij(12).Text = 400.405
  txtDij(13).Text = 650.565
  txtDij(14).Text = 1350.773
  txtDij(15).Text = 50.01
  txtDij(16).Text = 300.171
  txtDij(17).Text = 1000.379
  txtDij(18).Text = 250.159
  txtDij(19).Text = 950.368
  txtDij(20).Text = 700.204
  MoveFocusTo txtDij(0)
End Sub

Private Sub cmdExit_Click()
  Unload Me
End Sub

Private Sub Form_Load()
  lblK.Caption = ""
  lblTip.Visible = False
End Sub

Private Sub txtDij_KeyPress(Index As Integer, KeyAscii As Integer)
  If KeyAscii < Asc("0") Or KeyAscii > Asc("9") Then
    If KeyAscii = 8 Then
    ElseIf KeyAscii = Asc(".") Then
    ElseIf KeyAscii = 13 Then
      If Index < 20 Then
        MoveFocusTo txtDij(Index + 1)
      Else
        MoveFocusTo txtDij(0)
      End If
    Else
      Beep
      KeyAscii = 0
    End If
  End If
End Sub

Private Sub MoveFocusTo(txt As TextBox)
  With txt
    .SelStart = 0
    .SelLength = Len(.Text)
    .SetFocus
  End With
End Sub

Private Function InputIsGood() As Boolean
  Dim i As Integer
  
  On Error GoTo Err
  
  For i = 0 To 20
    gDij(i + 1) = CDbl(txtDij(i).Text)
  Next
  InputIsGood = True
  Exit Function
Err:
  MsgBox "数据输入错误！", vbExclamation, "警告"
  MoveFocusTo txtDij(i)
  InputIsGood = False
End Function

Private Sub ChgDis()
  Dim i As Integer
  lblK.Caption = "加常数 K=" & FormatNumber(gX(7) * 1000, 2, vbTrue, vbFalse, vbFalse) & "mm(中误差 " & _
                 FormatNumber(gM0 * Sqr(gQ(7, 7)) * 1000, 2, vbTrue, vbFalse, vbFalse) & "mm)"
  For i = 1 To 6
  txtDij(i - 1).ToolTipText = "平差值=" & FormatNumber(gX(i), 4, vbTrue, vbFalse, vbFalse) & "m(中误差 " & _
                 FormatNumber(gM0 * Sqr(gQ(i, i)) * 1000, 2, vbTrue, vbFalse, vbFalse) & "mm)"
  Next
  lblTip.Visible = True
End Sub
