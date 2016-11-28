VERSION 5.00
Begin VB.Form frmInputL 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   2220
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   5250
   Icon            =   "frmInputL.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2220
   ScaleWidth      =   5250
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdCancel 
      Caption         =   "取消(&C)"
      Height          =   375
      Left            =   4080
      TabIndex        =   11
      Top             =   1800
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定(&O)"
      Height          =   375
      Left            =   2880
      TabIndex        =   10
      Top             =   1800
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   9
      Left            =   4080
      TabIndex        =   9
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   8
      Left            =   2880
      TabIndex        =   8
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   7
      Left            =   4080
      TabIndex        =   7
      Top             =   1095
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   6
      Left            =   2880
      TabIndex        =   6
      Top             =   1095
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   5
      Left            =   4080
      TabIndex        =   5
      Top             =   750
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   4
      Left            =   2880
      TabIndex        =   4
      Top             =   750
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   3
      Left            =   4080
      TabIndex        =   3
      Top             =   405
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   2
      Left            =   2880
      TabIndex        =   2
      Top             =   405
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   1
      Left            =   4080
      TabIndex        =   1
      Top             =   60
      Width           =   1095
   End
   Begin VB.TextBox txtLL 
      Height          =   300
      Index           =   0
      Left            =   2880
      TabIndex        =   0
      Top             =   60
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   $"frmInputL.frx":000C
      ForeColor       =   &H00FF0000&
      Height          =   1695
      Left            =   60
      TabIndex        =   12
      Top             =   263
      Width           =   2715
      WordWrap        =   -1  'True
   End
End
Attribute VB_Name = "frmInputL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public gblnOK As Boolean
Public gidxLL As Integer
Public gLL As Double

Private Sub cmdCancel_Click()
  Unload Me
End Sub

Private Sub cmdOK_Click()
  If InputIsGood() Then
    gblnOK = True
    Unload Me
  End If
End Sub

Private Sub Form_Activate()
  MoveFocusTo txtLL(0)
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
  If KeyAscii = 27 Then
    Call cmdCancel_Click
  End If
End Sub

Private Sub Form_Load()
  gblnOK = False
  MoveFocusTo txtLL(0)
End Sub

Private Sub txtLL_KeyPress(Index As Integer, KeyAscii As Integer)
  If GoodChar(KeyAscii) Then
    Exit Sub
  End If
  If KeyAscii = 13 Then
    If Index < 9 Then
      MoveFocusTo txtLL(Index + 1)
    Else
      Call cmdOK_Click
    End If
  End If
  KeyAscii = 0
End Sub

Private Function InputIsGood() As Boolean
  Dim i As Integer
  Dim LL(9) As Double
  InputIsGood = False
  For i = 0 To 9
    If Not GetTextBoxVal(txtLL(i), vbDouble, LL(i)) Then
      Exit Function
    End If
  Next
  gLL = 0
  For i = 0 To 9
    g_LLL(gidxLL, i) = LL(i)
    gLL = gLL + LL(i)
  Next
  gLL = gLL / 10
  gLL = Int(gLL * 100000 + 0.5) / 100000
  InputIsGood = True
End Function
