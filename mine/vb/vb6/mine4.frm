VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "颜色"
   ClientHeight    =   1950
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   ControlBox      =   0   'False
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   4680
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command4 
      Caption         =   "标签"
      Height          =   375
      Left            =   1800
      TabIndex        =   6
      Top             =   1440
      Width           =   855
   End
   Begin VB.CommandButton Command3 
      Caption         =   "窗体"
      Height          =   375
      Left            =   480
      TabIndex        =   5
      Top             =   1440
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   375
      Left            =   3360
      TabIndex        =   4
      Top             =   840
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   3360
      TabIndex        =   3
      Top             =   240
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      Height          =   975
      Left            =   480
      ScaleHeight     =   915
      ScaleWidth      =   2115
      TabIndex        =   0
      Top             =   240
      Width           =   2175
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "000"
         Height          =   170
         Left            =   1560
         TabIndex        =   2
         Top             =   120
         Width           =   300
      End
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         Caption         =   "000"
         Height          =   170
         Left            =   120
         TabIndex        =   1
         Top             =   120
         Width           =   300
      End
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim fcolor As Byte
Dim lcolor As Byte

Private Sub Command1_Click()
  formcolor = fcolor
  labelcolor = lcolor
  Form1.Enabled = True
  Unload Form4
  begin
  state = conReady
End Sub

Private Sub Command2_Click()
  IsWorking = OldIsWorking
  Form1.Enabled = True
  Unload Form4
  state = conReady
End Sub
Private Sub Command3_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
 If Button = 1 Then
  fcolor = (fcolor And 7) + 1
 Else
  fcolor = ((fcolor + 6) And 7) + 1
 End If
  Me.Picture1.BackColor = colortable(fcolor)
End Sub
Private Sub Command4_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
 If Button = 1 Then
  lcolor = (lcolor And 7) + 1
 Else
  lcolor = ((lcolor + 6) And 7) + 1
 End If
  Me.Label1.BackColor = colortable(lcolor)
  Me.Label2.BackColor = colortable(lcolor)
End Sub
Private Sub Form_Activate()
  Form_Load
End Sub
Private Sub Form_Load()
  fcolor = formcolor
  lcolor = labelcolor
  Form4.ScaleMode = vbTwips
  Form4.Left = Form1.Left + (Form1.Width - Form4.Width) / 2
  Form4.Top = Form1.Top + (Form1.Height - Form4.Height) / 2
  Me.Picture1.BackColor = colortable(fcolor)
  Me.Label1.BackColor = colortable(labelcolor)
  Me.Label2.BackColor = colortable(labelcolor)
End Sub
