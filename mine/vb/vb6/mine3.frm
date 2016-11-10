VERSION 5.00
Begin VB.Form Form3 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "扫雷英雄榜"
   ClientHeight    =   2670
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6090
   ControlBox      =   0   'False
   Icon            =   "mine3.frx":0000
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2670
   ScaleWidth      =   6090
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command2 
      Caption         =   "确   定"
      Height          =   375
      Left            =   3818
      TabIndex        =   0
      Top             =   2040
      Width           =   1815
   End
   Begin VB.CommandButton Command1 
      Caption         =   "重新计分(&R)"
      Height          =   375
      Left            =   458
      TabIndex        =   1
      Top             =   2040
      Width           =   1815
   End
   Begin VB.Frame Frame1 
      Caption         =   "扫雷英雄榜"
      Height          =   1455
      Left            =   458
      TabIndex        =   2
      Top             =   225
      Width           =   5175
      Begin VB.Label Label 
         Caption         =   "高级: "
         Height          =   375
         Index           =   2
         Left            =   120
         TabIndex        =   5
         Top             =   960
         Width           =   4695
      End
      Begin VB.Label Label 
         Caption         =   "中级: "
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   4
         Top             =   660
         Width           =   4695
      End
      Begin VB.Label Label 
         Caption         =   "初级:"
         Height          =   375
         Index           =   0
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Width           =   4695
      End
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
 Dim i As Integer
 For i = 0 To 2
  heroname(i) = "匿名"
  times(i) = 999
 Next
 Form_Activate
 IsWorking = OldIsWorking
End Sub

Private Sub Command2_Click()
 Unload Form3
 Form1.Enabled = True
 Form1.Show
 IsWorking = OldIsWorking
End Sub

Private Sub Form_Activate()
 Dim i As Integer
 Form3.ScaleMode = vbTwips
 Form3.Left = Form1.Left + (Form1.Width - Form3.Width) / 2
 Form3.Top = Form1.Top + (Form1.Height - Form3.Height) / 2
 For i = 0 To 2
  Label(i).Caption = Left$(Label(i).Caption, 3) & _
                     Space$(18 - Len(Str$(times(i)))) & _
                     times(i) & " 秒" & Space$(15) & heroname(i)
                     
 Next
End Sub

