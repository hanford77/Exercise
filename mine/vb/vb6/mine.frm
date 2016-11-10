VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   BackColor       =   &H8000000B&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "扫雷"
   ClientHeight    =   3495
   ClientLeft      =   3990
   ClientTop       =   3450
   ClientWidth     =   4905
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   233
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   327
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   3240
      Top             =   840
   End
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   2400
      Top             =   840
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      Caption         =   "开 局"
      Height          =   360
      Left            =   2040
      MaskColor       =   &H8000000F&
      Style           =   1  'Graphical
      TabIndex        =   1
      ToolTipText     =   "左击开局"
      Top             =   75
      Width           =   750
   End
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000013&
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   10.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   1095
      Left            =   480
      ScaleHeight     =   1035
      ScaleWidth      =   3915
      TabIndex        =   0
      Top             =   1920
      Width           =   3975
   End
   Begin VB.Label Label1 
      BackColor       =   &H0000FFFF&
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000007&
      Height          =   300
      Left            =   120
      TabIndex        =   3
      ToolTipText     =   "剩余雷数"
      Top             =   105
      Width           =   450
   End
   Begin VB.Label Label2 
      BackColor       =   &H0000FFFF&
      Caption         =   "000"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000007&
      Height          =   300
      Left            =   3480
      TabIndex        =   2
      ToolTipText     =   "时间"
      Top             =   105
      Width           =   450
   End
   Begin VB.Menu mnugame 
      Caption         =   "游戏(&G)"
      NegotiatePosition=   1  'Left
      Begin VB.Menu mnubegin 
         Caption         =   "开局(&N)"
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnublank1 
         Caption         =   "-"
      End
      Begin VB.Menu mnueasy 
         Caption         =   "初级(&B)"
      End
      Begin VB.Menu mnuhard 
         Caption         =   "中级(&I)"
      End
      Begin VB.Menu mnuhardest 
         Caption         =   "高级(&E)"
      End
      Begin VB.Menu mnudefine 
         Caption         =   "自定义(&C)..."
      End
      Begin VB.Menu mnublank2 
         Caption         =   "-"
      End
      Begin VB.Menu mnumark 
         Caption         =   "标记(?)(&M)"
      End
      Begin VB.Menu mnucolor 
         Caption         =   "颜色(&L)..."
      End
      Begin VB.Menu mnublank3 
         Caption         =   "-"
      End
      Begin VB.Menu mnutable 
         Caption         =   "扫雷英雄榜(&T)..."
      End
      Begin VB.Menu mnublank4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuexit 
         Caption         =   "退出(&X)"
      End
   End
   Begin VB.Menu mnuhelp 
      Caption         =   "帮助(&H)"
      NegotiatePosition=   1  'Left
      Begin VB.Menu mnuprotect 
         Caption         =   "保护"
         Shortcut        =   ^P
      End
      Begin VB.Menu mnublank5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuhelponce 
         Caption         =   "小帮一次"
         Shortcut        =   ^B
      End
      Begin VB.Menu mnuhelpchoice 
         Caption         =   "选择帮助"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuhelpall 
         Caption         =   "帮忙到底"
         Shortcut        =   ^E
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub Command1_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  begin
  state = conReady
End Sub
Private Sub Form_Unload(Cancel As Integer)
  mnuexit_Click
End Sub
Private Sub mnucolor_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  OldIsWorking = IsWorking
  IsWorking = False
  Form1.Enabled = False
  Form4.Show
End Sub
Private Sub mnuhelpall_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  gamecomplete
  state = conReady
End Sub
Private Sub mnuhelpchoice_Click()
  If state <> conReady Then Exit Sub
  If helpchoice Then
    doHelpchoice
    mnuhelponce.Enabled = True
    mnuhelpall.Enabled = True
  Else
    choiceblock = ""
    shiftchoice = False
    helpchoice = True
    mnuhelponce.Enabled = False
    mnuhelpall.Enabled = False
    Picture1.MousePointer = vbCrosshair
  End If
  mnuhelpchoice.Checked = helpchoice
  state = conReady
End Sub
Private Sub mnuhelponce_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  helponce
  state = conReady
End Sub
Private Sub mnuprotect_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  protect = Not protect
  mnuprotect.Checked = protect
  state = conReady
End Sub
Private Sub mnutable_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  Form1.Enabled = False
  Form3.Show
  OldIsWorking = IsWorking
  IsWorking = False
  state = conReady
End Sub
Private Sub picture1_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
  If state <> conReady Then Exit Sub
  state = conMouseDown
  If Not gameover Then
    IsWorking = True
    Command1.Caption = "排 雷"
    If helpchoice Then
      choosehelp Button + Shift * 10, x, y
    Else
      action Button, x, y
    End If
  End If
  state = conMouseDownEnd
End Sub
Private Sub Picture1_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
  If Not shiftchoice Then Exit Sub
  Picture1.Line (choicex0, choicey0)-(oldx, oldy), &HC0C03F, B
  Picture1.Line (choicex0, choicey0)-(x, y), &HC0C03F, B
  oldx = x
  oldy = y
End Sub

Private Sub picture1_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
  If state = conMouseDown Then
    Timer2.Enabled = True
  End If
  If state <> conMouseDownEnd Then Exit Sub
  Timer2.Enabled = False
  state = conMouseUp
  If Not gameover Then
   Command1.Caption = "开 局"
   If Not helpchoice Then drawchoiceblock
  End If
  state = conReady
End Sub
Private Sub Form_Load()
  state = conBusy
  Set frm1 = Form1
  Set frm3 = Form3
  Picture1.ScaleMode = vbPixels
  Picture1.BackColor = &HC0C0C0
  filename = App.Path & "\mine.ini"
  init
  state = conReady
End Sub
Private Sub mnubegin_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  begin
  state = conReady
End Sub
Private Sub mnudefine_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  OldIsWorking = IsWorking
  IsWorking = False
  diff = 3
  mnueasy.Checked = False
  mnuhard.Checked = False
  mnuhardest.Checked = False
  mnudefine.Checked = True
  Form1.Enabled = False
  Form2.Show
End Sub
Private Sub mnueasy_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  diff = 0
  row = 8
  col = 8
  mines = 10
  mnueasy.Checked = True
  mnuhard.Checked = False
  mnuhardest.Checked = False
  mnudefine.Checked = False
  begin
  state = conReady
End Sub
Private Sub mnuexit_Click()
  Dim i As Integer
  If state <> conReady Then Exit Sub
  Me.ScaleMode = vbTwips
  On Error GoTo nosave
  Open filename For Output As 1
  Print #1, "[扫雷]"
  Print #1, "Difficulty = "; diff
  Print #1, "Height ="; row
  Print #1, "Width ="; col
  Print #1, "Mines ="; mines
  Print #1, "Mark ="; Switch(mark, 1, Not mark, 0)
  Print #1, "Color = 1"
  Print #1, "Xpos ="; Me.Left / Screen.TwipsPerPixelX
  Print #1, "Ypos ="; Me.Top / Screen.TwipsPerPixelY
  For i = 0 To 2
    Print #1, "Time"; Mid(Str$(11 + i), 3, 1); "="; times(i)
  Next
  For i = 0 To 2
    Print #1, "Name"; Mid(Str$(11 + i), 3, 1); "="; heroname(i)
  Next
  Print #1, "Protect ="; Switch(protect, 1, Not protect, 0)
  Print #1, "FormColor ="; formcolor
  Print #1, "LabelColor ="; labelcolor
 Close
nosave:
 End
End Sub

Private Sub mnuhard_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  diff = 1
  row = 16
  col = 16
  mines = 40
  mnueasy.Checked = False
  mnuhard.Checked = True
  mnuhardest.Checked = False
  mnudefine.Checked = False
  begin
  state = conReady
End Sub
Private Sub mnuhardest_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  diff = 2
  row = 16
  col = 30
  mines = 99
  mnueasy.Checked = False
  mnuhard.Checked = False
  mnuhardest.Checked = True
  mnudefine.Checked = False
  begin
  state = conReady
End Sub
Private Sub mnumark_Click()
  If state <> conReady Then Exit Sub
  state = conBusy
  mark = Not mark
  mnumark.Checked = mark
  state = conReady
End Sub
Private Sub init()
'从初始化文件中获取游戏信息
 Dim lndata As String
 Dim eq As Integer
 Dim i As Integer
 Dim getdata As Byte
 getdata = False
 mark = False
 protect = False
 diff = 2
 row = 16
 col = 30
 mines = 99
 mark = True
 Me.Left = 0
 Me.Top = 0
 formcolor = 2
 labelcolor = 8
 For i = 0 To 2
   times(i) = 999
   heroname(i) = "匿名"
 Next
 protect = False
 On Error GoTo nofile
 Open filename For Input As 1
 Do Until EOF(1)
  Line Input #1, lndata
  If InStr(lndata, "Diff") <> 0 Then          '难度
    eq = InStr(lndata, "=")
    diff = Int(Val(Mid(lndata, eq + 1)))
  ElseIf InStr(1, lndata, "Height") <> 0 Then  '行数
   eq = InStr(lndata, "=")
   eq = Int(Val(Mid(lndata, eq + 1)))
   If eq < 2 Then
     row = 2
   ElseIf eq > 30 Then
     row = 30
   Else
     row = eq
   End If
  ElseIf InStr(lndata, "Width") <> 0 Then      '列数
   eq = InStr(lndata, "=")
   eq = Int(Val(Mid(lndata, eq + 1)))
   If eq < 8 Then
     col = 8
   ElseIf eq > 50 Then
     col = 50
   Else
     col = eq
   End If
  ElseIf InStr(lndata, "Mines") <> 0 Then      '雷数
   eq = InStr(lndata, "=")
   eq = Int(Val(Mid(lndata, eq + 1)))
   If eq >= row * col Then
     mines = row * col / 2
   ElseIf eq < 0 Then
     mines = 0
   Else
     mines = eq
   End If
  ElseIf InStr(lndata, "Mark") <> 0 Then       '是否标记
   eq = InStr(lndata, "=")
   eq = Val(Mid(lndata, eq + 1))
   mark = (eq <> 0)
  ElseIf InStr(lndata, "Xpos") <> 0 Then        '窗口初始位置
   eq = InStr(lndata, "=")
   eq = Abs(Int(Val(Mid(lndata, eq + 1)))) * Screen.TwipsPerPixelX
   If eq > Screen.Width Or eq < 0 Then
     Me.Left = 0
   Else
     Me.Left = eq
   End If
  ElseIf InStr(lndata, "Ypos") <> 0 Then
   eq = InStr(lndata, "=")
   eq = Abs(Int(Val(Mid(lndata, eq + 1)))) * Screen.TwipsPerPixelY
   If eq > Screen.Height Or eq < 0 Then
     Me.Top = 0
   Else
     Me.Top = eq
   End If
  ElseIf InStr(lndata, "Time1") <> 0 Then       '游戏最好成绩记录
   eq = InStr(lndata, "=")
   times(0) = Val(Mid(lndata, eq + 1))
  ElseIf InStr(lndata, "Time2") <> 0 Then
   eq = InStr(lndata, "=")
   times(1) = Val(Mid(lndata, eq + 1))
  ElseIf InStr(lndata, "Time3") <> 0 Then
   eq = InStr(lndata, "=")
   times(2) = Val(Mid(lndata, eq + 1))
  ElseIf InStr(lndata, "Name1") <> 0 Then
   eq = InStr(lndata, "=")
   heroname(0) = Mid(lndata, eq + 1)
  ElseIf InStr(lndata, "Name2") <> 0 Then
   eq = InStr(lndata, "=")
   heroname(1) = Mid(lndata, eq + 1)
  ElseIf InStr(lndata, "Name3") <> 0 Then
   eq = InStr(lndata, "=")
   heroname(2) = Mid(lndata, eq + 1)
  ElseIf InStr(lndata, "Protect") <> 0 Then
   eq = InStr(lndata, "=")
   eq = Val(Mid(lndata, eq + 1))
   protect = (eq <> 0)
   mnuprotect.Checked = protect
  ElseIf InStr(lndata, "FormColor") <> 0 Then
   eq = InStr(lndata, "=")
   formcolor = Val(Mid(lndata, eq + 1))
  ElseIf InStr(lndata, "LabelColor") <> 0 Then
   eq = InStr(lndata, "=")
   labelcolor = Val(Mid(lndata, eq + 1))
  End If
 Loop
 getdata = True
nofile:
 Close
 If Not getdata Then
   mark = False
   protect = False
   diff = 2
   row = 16
   col = 30
   mines = 99
   mark = True
   Me.Left = 0
   Me.Top = 0
   formcolor = 2
   labelcolor = 8
 End If
 On Error GoTo 0
 Select Case diff
  Case 0          '初级
    mnueasy.Checked = True
    mnuhard.Checked = False
    mnuhardest.Checked = False
    mnudefine.Checked = False
  Case 1          '中级
     mnueasy.Checked = False
     mnuhard.Checked = True
     mnuhardest.Checked = False
     mnudefine.Checked = False
  Case 2          '高级
      mnueasy.Checked = False
      mnuhard.Checked = False
      mnuhardest.Checked = True
      mnudefine.Checked = False
  Case Else
   diff = 3       '自定义
   mnueasy.Checked = False
   mnuhard.Checked = False
   mnuhardest.Checked = False
   mnudefine.Checked = True
 End Select
 If mark Then mnumark.Checked = mark
 begin
End Sub
Private Sub Timer1_Timer()
 Dim tm As Integer
 If IsWorking Then
  tm = Val(Label2.Caption) + 1
  If tm >= 999 Then tm = 999
  Label2.Caption = Mid(Str$(tm + 1000), 3, 3)
 End If
End Sub
Private Sub Timer2_Timer()
  picture1_MouseUp 0, 0, 0, 0
End Sub
