VERSION 5.00
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "自定义雷区"
   ClientHeight    =   1905
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4320
   ControlBox      =   0   'False
   Icon            =   "mine2.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1905
   ScaleWidth      =   4320
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   2940
      TabIndex        =   3
      Top             =   465
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   300
      Left            =   773
      TabIndex        =   0
      Top             =   465
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   300
      Left            =   773
      TabIndex        =   2
      Top             =   1222
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   300
      Left            =   773
      TabIndex        =   1
      Top             =   843
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   375
      Left            =   2940
      TabIndex        =   4
      Top             =   1147
      Width           =   1095
   End
   Begin VB.Label Label3 
      Caption         =   "雷数:"
      Height          =   375
      Left            =   240
      TabIndex        =   7
      Top             =   1320
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "列数:"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   900
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "行数:"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   480
      Width           =   615
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
 Dim tp As Integer
 tp = Val(Text1.Text)
 If tp < 2 Then
  row = 2
 ElseIf tp > 30 Then
  row = 30
 Else
  row = tp
 End If
 tp = Val(Text2.Text)
 If tp < 8 Then
  col = 8
 ElseIf tp > 50 Then
  col = 50
 Else
  col = tp
 End If
 tp = Val(Text3.Text)
 If tp >= row * col Then
  mines = row * col / 2
 ElseIf tp < 0 Then
  mines = 0
 Else
  mines = tp
 End If
  Unload Form2
  Form1.Enabled = True
  Form1.Show
  begin
  state = conReady
End Sub
Private Sub Command2_Click()
  Unload Form2
  Form1.Enabled = True
  Form1.Show
  IsWorking = OldIsWorking
  state = conReady
End Sub

Private Sub Form_Load()
 Form2.ScaleMode = vbTwips
 Form2.Left = Form1.Left + (Form1.Width - Form2.Width) / 2
 Form2.Top = Form1.Top + (Form1.Height - Form2.Height) / 2
 Text1.Text = LTrim$(Str$(row))
 Text2.Text = LTrim$(Str$(col))
 Text3.Text = LTrim$(Str$(mines))
 Text1.SelStart = 0
 Text1.SelLength = Len(Text1.Text)
End Sub
Private Sub Text1_KeyPress(KeyAscii As Integer)
  If KeyAscii < Asc("0") Or KeyAscii > Asc("9") Then KeyAscii = 0: Beep
End Sub
Private Sub Text2_KeyPress(KeyAscii As Integer)
  If KeyAscii < Asc("0") Or KeyAscii > Asc("9") Then KeyAscii = 0: Beep
End Sub
Private Sub Text3_KeyPress(KeyAscii As Integer)
  If KeyAscii < Asc("0") Or KeyAscii > Asc("9") Then KeyAscii = 0: Beep
End Sub

