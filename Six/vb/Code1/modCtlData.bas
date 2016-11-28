Attribute VB_Name = "modCtlData"
Option Explicit
Public Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" ( _
               ByVal lpFileName As String, _
               ByVal dwDesiredAccess As Long, _
               ByVal dwShareMode As Long, _
               ByVal lpSecurityAttributes As Long, _
               ByVal dwCreationDisposition As Long, _
               ByVal dwFlagsAndAttributes As Long, _
               ByVal hTemplateFile As Long) As Long
Public Declare Function ReadFile Lib "kernel32" ( _
               ByVal hFile As Long, _
               ByVal lpBuffer As Long, _
               ByVal nNumberOfBytesToRead As Long, _
               lpNumberOfBytesRead As Long, _
               ByVal lpOverlapped As Long) As Long
Public Declare Function WriteFile Lib "kernel32" ( _
               ByVal hFile As Long, _
               ByVal lpBuffer As Long, _
               ByVal nNumberOfBytesToWrite As Long, _
               lpNumberOfBytesWritten As Long, _
               ByVal lpOverlapped As Long) As Long
Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Public g_LLL(20, 9) As Double

'将焦点移动到文本框txt
Public Sub MoveFocusTo(txt As TextBox)
  Dim p1 As Long, p2 As Long
  On Error Resume Next
  p1 = InStr(1, txt.Text, ".")
  If p1 <= 0 Then
    txt.Text = txt.Text & "."
    p1 = Len(txt.Text)
    p2 = p1
  Else
    p2 = Len(txt.Text)
  End If
  txt.SelStart = p1
  txt.SelLength = p2 - p1
  txt.SetFocus
End Sub

'从txt文本框中获得输入值
Public Function GetTextBoxVal(txt As TextBox, ValType As VbVarType, Value As Variant) As Boolean
  GetTextBoxVal = GetStringVal(txt.Text, ValType, Value)
  If Not GetTextBoxVal Then
    MsgBox "输入错误", vbExclamation, "警告"
    MoveFocusTo txt
  End If
End Function

'从txt文本框中获得输入值
Public Function GetTextBoxValMinMax(txt As TextBox, Min As Variant, Max As Variant, ValType As VbVarType, Value As Variant) As Boolean
  GetTextBoxValMinMax = False
  If GetStringVal(txt.Text, ValType, Value) Then
    If Value < Min Or Value > Max Then
      MsgBox "范围超限:[" & Min & "," & Max & "]", vbExclamation, "警告"
      MoveFocusTo txt
    Else
      GetTextBoxValMinMax = True
    End If
  Else
    MsgBox "输入错误", vbExclamation, "警告"
    MoveFocusTo txt
  End If
End Function

'获得字符串的数值
Public Function GetStringVal(ByVal str As String, ValType As VbVarType, Value As Variant) As Boolean
  str = Trim(str)
  If Len(str) = 0 Then
    str = "0"
  End If
  On Error Resume Next
  Err.Clear
  Select Case ValType
    Case vbDouble
      Value = CDbl(str)
    Case vbInteger
      Value = CInt(str)
    Case vbLong
      Value = CLng(str)
  End Select
  GetStringVal = (Err.Number = 0)
End Function

Public Function GoodChar(KeyAscii As Integer) As Boolean
  GoodChar = False
  If KeyAscii >= Asc("0") And KeyAscii <= Asc("9") Then
    GoodChar = True
  ElseIf KeyAscii = Asc(".") Then
    GoodChar = True
  ElseIf KeyAscii = 8 Then
    GoodChar = True
  End If
End Function


