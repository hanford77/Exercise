VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "求解一元四次方程"
   ClientHeight    =   5370
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7515
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5370
   ScaleWidth      =   7515
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "方程的解"
      Height          =   2295
      Left            =   120
      TabIndex        =   34
      Top             =   2940
      Width           =   7275
      Begin VB.TextBox txtIA 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   4110
         Locked          =   -1  'True
         TabIndex        =   11
         Top             =   300
         Width           =   2775
      End
      Begin VB.TextBox txtRA 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   930
         Locked          =   -1  'True
         TabIndex        =   10
         Top             =   300
         Width           =   2775
      End
      Begin VB.TextBox txtRB 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   930
         Locked          =   -1  'True
         TabIndex        =   12
         Top             =   780
         Width           =   2775
      End
      Begin VB.TextBox txtIB 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   4110
         Locked          =   -1  'True
         TabIndex        =   13
         Top             =   780
         Width           =   2775
      End
      Begin VB.TextBox txtRC 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   930
         Locked          =   -1  'True
         TabIndex        =   14
         Top             =   1260
         Width           =   2775
      End
      Begin VB.TextBox txtIC 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   4110
         Locked          =   -1  'True
         TabIndex        =   15
         Top             =   1260
         Width           =   2775
      End
      Begin VB.TextBox txtRD 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   930
         Locked          =   -1  'True
         TabIndex        =   16
         Top             =   1740
         Width           =   2775
      End
      Begin VB.TextBox txtID 
         BackColor       =   &H80000004&
         Height          =   375
         Left            =   4110
         Locked          =   -1  'True
         TabIndex        =   17
         Top             =   1740
         Width           =   2775
      End
      Begin VB.Label Label30 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   46
         Top             =   390
         Width           =   30
      End
      Begin VB.Label Label29 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   45
         Top             =   390
         Width           =   90
      End
      Begin VB.Label lblA 
         AutoSize        =   -1  'True
         Caption         =   "x1"
         Height          =   195
         Left            =   120
         TabIndex        =   44
         Top             =   390
         Width           =   165
      End
      Begin VB.Label lblB 
         AutoSize        =   -1  'True
         Caption         =   "x2"
         Height          =   195
         Left            =   120
         TabIndex        =   43
         Top             =   870
         Width           =   165
      End
      Begin VB.Label Label26 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   42
         Top             =   870
         Width           =   90
      End
      Begin VB.Label Label25 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   41
         Top             =   870
         Width           =   30
      End
      Begin VB.Label lblC 
         AutoSize        =   -1  'True
         Caption         =   "x3"
         Height          =   195
         Left            =   120
         TabIndex        =   40
         Top             =   1350
         Width           =   165
      End
      Begin VB.Label Label23 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   39
         Top             =   1350
         Width           =   90
      End
      Begin VB.Label Label22 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   38
         Top             =   1350
         Width           =   30
      End
      Begin VB.Label lblD 
         AutoSize        =   -1  'True
         Caption         =   "x4"
         Height          =   195
         Left            =   120
         TabIndex        =   37
         Top             =   1830
         Width           =   165
      End
      Begin VB.Label Label20 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   36
         Top             =   1830
         Width           =   90
      End
      Begin VB.Label Label19 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   35
         Top             =   1830
         Width           =   30
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "一元四次方程系数"
      Height          =   2775
      Left            =   120
      TabIndex        =   18
      Top             =   60
      Width           =   7275
      Begin VB.TextBox txtI0 
         Height          =   375
         Left            =   4110
         TabIndex        =   9
         Top             =   2220
         Width           =   2775
      End
      Begin VB.TextBox txtR0 
         Height          =   375
         Left            =   930
         TabIndex        =   8
         Top             =   2220
         Width           =   2775
      End
      Begin VB.TextBox txtI1 
         Height          =   375
         Left            =   4110
         TabIndex        =   7
         Top             =   1740
         Width           =   2775
      End
      Begin VB.TextBox txtR1 
         Height          =   375
         Left            =   930
         TabIndex        =   6
         Top             =   1740
         Width           =   2775
      End
      Begin VB.TextBox txtI2 
         Height          =   375
         Left            =   4110
         TabIndex        =   5
         Top             =   1260
         Width           =   2775
      End
      Begin VB.TextBox txtR2 
         Height          =   375
         Left            =   930
         TabIndex        =   4
         Top             =   1260
         Width           =   2775
      End
      Begin VB.TextBox txtI3 
         Height          =   375
         Left            =   4110
         TabIndex        =   3
         Top             =   780
         Width           =   2775
      End
      Begin VB.TextBox txtR3 
         Height          =   375
         Left            =   930
         TabIndex        =   2
         Top             =   780
         Width           =   2775
      End
      Begin VB.TextBox txtR4 
         Height          =   375
         Left            =   930
         TabIndex        =   0
         Top             =   300
         Width           =   2775
      End
      Begin VB.TextBox txtI4 
         Height          =   375
         Left            =   4110
         TabIndex        =   1
         Top             =   300
         Width           =   2775
      End
      Begin VB.Label Label15 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   33
         Top             =   2310
         Width           =   30
      End
      Begin VB.Label Label14 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   32
         Top             =   2310
         Width           =   90
      End
      Begin VB.Label Label13 
         AutoSize        =   -1  'True
         Caption         =   "0 次项"
         Height          =   195
         Left            =   120
         TabIndex        =   31
         Top             =   2310
         Width           =   495
      End
      Begin VB.Label Label12 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   30
         Top             =   1830
         Width           =   30
      End
      Begin VB.Label Label11 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   29
         Top             =   1830
         Width           =   90
      End
      Begin VB.Label Label10 
         AutoSize        =   -1  'True
         Caption         =   "1 次项"
         Height          =   195
         Left            =   120
         TabIndex        =   28
         Top             =   1830
         Width           =   495
      End
      Begin VB.Label Label9 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   27
         Top             =   1350
         Width           =   30
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   26
         Top             =   1350
         Width           =   90
      End
      Begin VB.Label Label7 
         AutoSize        =   -1  'True
         Caption         =   "2 次项"
         Height          =   195
         Left            =   120
         TabIndex        =   25
         Top             =   1350
         Width           =   495
      End
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   24
         Top             =   870
         Width           =   30
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   23
         Top             =   870
         Width           =   90
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "3 次项"
         Height          =   195
         Left            =   120
         TabIndex        =   22
         Top             =   870
         Width           =   495
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "4 次项"
         Height          =   195
         Left            =   120
         TabIndex        =   21
         Top             =   390
         Width           =   495
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "+"
         Height          =   195
         Left            =   3825
         TabIndex        =   20
         Top             =   390
         Width           =   90
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "i"
         Height          =   195
         Left            =   7080
         TabIndex        =   19
         Top             =   390
         Width           =   30
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function SolveEquation Lib "SolveEquationDll.dll" (ByRef z As Double, ByRef x As Double) As Long

Private Sub txtR0_Change()
  Call OnTextChange
End Sub

Private Sub txtI0_Change()
  Call OnTextChange
End Sub

Private Sub txtR1_Change()
  Call OnTextChange
End Sub

Private Sub txtI1_Change()
  Call OnTextChange
End Sub

Private Sub txtR2_Change()
  Call OnTextChange
End Sub

Private Sub txtI2_Change()
  Call OnTextChange
End Sub

Private Sub txtR3_Change()
  Call OnTextChange
End Sub

Private Sub txtI3_Change()
  Call OnTextChange
End Sub

Private Sub txtR4_Change()
  Call OnTextChange
End Sub

Private Sub txtI4_Change()
  Call OnTextChange
End Sub

Private Sub OnTextChange()
  Dim z(10) As Double
  On Error Resume Next
  z(0) = CDbl(txtR0.Text)
  z(1) = CDbl(txtI0.Text)
  z(2) = CDbl(txtR1.Text)
  z(3) = CDbl(txtI1.Text)
  z(4) = CDbl(txtR2.Text)
  z(5) = CDbl(txtI2.Text)
  z(6) = CDbl(txtR3.Text)
  z(7) = CDbl(txtI3.Text)
  z(8) = CDbl(txtR4.Text)
  z(9) = CDbl(txtI4.Text)
  Dim x(12) As Double
  Dim n As Long                 '有效解的个数
  n = SolveEquation(z(0), x(0)) '解方程
  Dim d As Double
  d = 0.0000000001
  If n >= 1 Then
    txtRA.Text = x(0)
    txtIA.Text = x(1)
    'lblA.Text = x(2)
    If Abs(x(2)) > d Then
      lblA.ForeColor = vbRed
    Else
      lblA.ForeColor = vbBlue
    End If
  Else
    txtRA.Text = ""
    txtIA.Text = ""
    'lblA.Text = ""
    lblA.ForeColor = vbBlack
  End If
  If n >= 2 Then
    txtRB.Text = x(3)
    txtIB.Text = x(4)
    'lblB.Caption = x(5)
    If Abs(x(5)) > d Then
      lblB.ForeColor = vbRed
    Else
      lblB.ForeColor = vbBlue
    End If
  Else
    txtRB.Text = ""
    txtIB.Text = ""
    'lblB.Caption = ""
    lblB.ForeColor = vbBlack
  End If
  If n >= 3 Then
    txtRC.Text = x(6)
    txtIC.Text = x(7)
    'lblC.Caption = x(8)
    If Abs(x(8)) > d Then
      lblC.ForeColor = vbRed
    Else
      lblC.ForeColor = vbBlue
    End If
  Else
    txtRC.Text = ""
    txtIC.Text = ""
    'lblC.Caption = ""
    lblC.ForeColor = vbBlack
  End If
  If n >= 4 Then
    txtRD.Text = x(9)
    txtID.Text = x(10)
    'lblD.Caption = x(11)
    If Abs(x(11)) > d Then
      lblD.ForeColor = vbRed
    Else
      lblD.ForeColor = vbBlue
    End If
  Else
    txtRD.Text = ""
    txtID.Text = ""
    'lblD.Caption = ""
    lblD.ForeColor = vbBlack
  End If
End Sub
