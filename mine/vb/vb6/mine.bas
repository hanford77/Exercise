Attribute VB_Name = "Module1"
Option Explicit
Public filename As String      '初始化文件名
Type minefiled
 totalmines As Byte
 flag As Byte
End Type
Public frm1 As Form
Public frm3 As Form
Public state As Byte                      '状态
Public Const conReady As Byte = 1         '状态-就绪
Public Const conBusy As Byte = 2          '状态-忙
Public Const conMouseDown As Byte = 3     '状态-鼠标按下
Public Const conMouseDownEnd As Byte = 4  '状态-鼠标按下结束
Public Const conMouseUp As Byte = 5       '状态-鼠标弹起
Dim minearea() As minefiled             '地雷数组
Public row, col As Integer              '行、列数
Public diff As Integer                  '难度系数:0-初级,1-中级,2-高级,其它-自定义
Public mines As Integer                 '总雷数
Public mark As Boolean                  '是否标记
Public times(0 To 2) As Integer         '英雄榜时间
Public heroname(0 To 2) As String       '英雄名
Public IsWorking As Boolean             '是否在挖雷
Public OldIsWorking As Boolean          '刚才是否在挖雷
Public Const blockwidth As Integer = 15        '块宽(像素)
Public Const blockheight As Integer = 15       '块高(像素)
Public gameover As Boolean              '是否结束
Const conIsMine As Byte = 1             '是地雷
Const conDiscovered As Byte = 2         '被打开
Const conMarked As Byte = 4             '被标上?号
Const conFounded As Byte = 8            '被发现(插上红旗)
Const conChoosed As Byte = 16           '被选中
Public colortable(1 To 8) As Long          '颜色表
Public choiceblock As String            '被选中的块
Public choicerow As Integer             '中心块的行
Public choicecol As Integer             '中心块的列
Public choicex0 As Integer              '中心块的X坐标
Public choicey0 As Integer              '中心块的Y坐标
Public choice As Byte                   '中心块周围满足条件的选项
Dim openblocks As Integer               '已经打开的块
Public protect As Boolean               '是否被保护
Public helpchoice As Boolean            '是否在选择帮助状态
Public shiftchoice As Boolean           '是否在块选择帮助
Public oldx As Integer
Public oldy As Integer
Public formcolor As Byte
Public labelcolor As Byte
Public Sub begin()
 Dim i As Integer, j As Integer
 Dim tp As Single
 colortable(1) = &HFF0000
 colortable(2) = &H18000
 colortable(3) = &H100FF
 colortable(4) = &H800000
 colortable(5) = &H10080
 colortable(6) = &H1FF80
 colortable(7) = &H180FF
 colortable(8) = &H1FFFF
 gameover = False             '游戏未结束
 IsWorking = False            '未开始挖雷
 openblocks = 0
 helpchoice = False
 shiftchoice = False
  '调整窗口、图片框大小、位置
 frm1.ScaleMode = vbPixels
 frm1.Picture1.Height = row * blockheight + 4
 frm1.Picture1.Width = col * blockwidth + 4
 frm1.ScaleMode = vbTwips
 frm1.Picture1.Top = 600
 frm1.Picture1.Left = 150
 frm1.Height = frm1.Picture1.Height + 2 * frm1.Picture1.Top + 210
 frm1.Width = frm1.Picture1.Width + 2 * frm1.Picture1.Left + 100
 '背景色
 frm1.BackColor = colortable(formcolor)
 frm1.Label1.BackColor = colortable(labelcolor)
 frm1.Label2.BackColor = colortable(labelcolor)
 '调整控件大小、位置
 tp = (frm1.Width - frm1.Command1.Width - 2 * frm1.Label1.Width - 350) / 2
 frm1.Label1.Left = 125
 frm1.Command1.Left = frm1.Label1.Left + frm1.Label1.Width + tp
 frm1.Label2.Left = frm1.Command1.Left + frm1.Command1.Width + tp
 '设置控件属性
 frm1.Command1.Caption = "开 局"
 frm1.Label1.Caption = Mid(Str$(mines + 1000), 3, 3)
 frm1.Label2.Caption = "000"
 frm1.Timer2.Enabled = False
 frm1.mnuhelponce.Enabled = True
 frm1.mnuhelpchoice.Enabled = True
 frm1.mnuhelpall.Enabled = True
 frm1.mnuhelpchoice.Checked = False
 frm1.Picture1.MousePointer = 0
 frm1.Picture1.DrawMode = vbCopyPen
 frm1.Picture1.FillStyle = 0
 '画地雷区
 frm1.ScaleMode = vbPixels
 For i = 1 To row
   For j = 1 To col
     drawblock i, j
   Next
 Next
 '随机埋下地雷
 Dim count As Integer
 ReDim minearea(1 To row, 1 To col)
 Randomize Timer
 count = 0
 While count < mines
   i = Int(row * Rnd + 1)
   j = Int(col * Rnd + 1)
   If minearea(i, j).flag <> conIsMine Then   '如果无雷
     minearea(i, j).flag = conIsMine
     count = count + 1
   End If
 Wend
 '计算单元格周围地雷个数
 For i = 1 To row
   For j = 1 To col
     minearea(i, j).totalmines = total(i, j, conIsMine)
   Next
 Next
End Sub
Public Sub action(Button As Integer, x As Single, y As Single)
 Dim i As Integer, j As Integer
 i = Int(y / blockheight) + 1
 j = Int(x / blockwidth) + 1
 choicerow = 0         '未选中中心块
 Select Case Button
   Case vbLeftButton      '鼠标左键
     If (minearea(i, j).flag And conDiscovered) = 0 Then   '该块未打开
       actionleft i, j
     End If
   Case vbRightButton     '鼠标右键
     If (minearea(i, j).flag And conDiscovered) = 0 Then   '该块未打开
       actionright i, j
     Else      '该块已打开
       actionboth i, j
     End If
  End Select
End Sub
Private Function total(i As Integer, j As Integer, filter As Byte, _
                    Optional choice As Byte, Optional inside As Byte) As Byte
    total = 0
    choice = 0
    inside = 0
    If i > 1 Then
      If j > 1 Then
        If (minearea(i - 1, j - 1).flag And filter) = filter Then
          total = total + 1
          choice = (choice Or 1)
        End If
        inside = (inside Or 1)
      End If
      If (minearea(i - 1, j).flag And filter) = filter Then
        total = total + 1
        choice = (choice Or 2)
      End If
      inside = (inside Or 2)
      If j < col Then
        If (minearea(i - 1, j + 1).flag And filter) = filter Then
          total = total + 1
          choice = (choice Or 4)
        End If
        inside = (inside Or 4)
      End If
    End If
    If j > 1 Then
      If (minearea(i, j - 1).flag And filter) = filter Then
        total = total + 1
        choice = (choice Or 8)
      End If
      inside = (inside Or 8)
    End If
    If j < col Then
      If (minearea(i, j + 1).flag And filter) = filter Then
        total = total + 1
        choice = (choice Or 16)
      End If
      inside = (inside Or 16)
    End If
    If i < row Then
      If j > 1 Then
        If (minearea(i + 1, j - 1).flag And filter) = filter Then
          total = total + 1
          choice = (choice Or 32)
        End If
        inside = (inside Or 32)
      End If
      If (minearea(i + 1, j).flag And filter) = filter Then
        total = total + 1
        choice = (choice Or 64)
      End If
      inside = (inside Or 64)
      If j < col Then
         If (minearea(i + 1, j + 1).flag And filter) = filter Then
           total = total + 1
           choice = (choice Or 128)
         End If
         inside = (inside Or 128)
      End If
    End If
End Function
Private Sub findtoopen()
  Dim i As Integer, j As Integer, k As Integer, l As Integer
  Dim p As Integer, tp As Byte
  Dim pos As String
  Dim inside As Byte
  Dim choice1 As Byte
  Dim begin As Integer
  p = 1
  Do
    l = Len(choiceblock)
    begin = p
    While p < l
      i = AscW(Mid(choiceblock, p, 1))
      p = p + 1
      j = AscW(Mid(choiceblock, p, 1))
      p = p + 1
      minearea(i, j).flag = conDiscovered
      drawpress i, j
      drawdigit i, j
      openblocks = openblocks + 1
      If minearea(i, j).totalmines = 0 Then
         tp = total(i, j, conIsMine, choice1, inside)
         tp = total(i, j, conDiscovered, choice)
         choice = (Not choice) And (Not choice1)
         tp = total(i, j, conFounded, choice1)
         choice = choice And (Not choice1) And inside
         If (choice And 1) <> 0 Then
           pos = ChrW(i - 1) & ChrW(j - 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 2) <> 0 Then
           pos = ChrW(i - 1) & ChrW(j)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 4) <> 0 Then
           pos = ChrW(i - 1) & ChrW(j + 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 8) <> 0 Then
           pos = ChrW(i) & ChrW(j - 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 16) <> 0 Then
           pos = ChrW(i) & ChrW(j + 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 32) <> 0 Then
           pos = ChrW(i + 1) & ChrW(j - 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 64) <> 0 Then
           pos = ChrW(i + 1) & ChrW(j)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
         If (choice And 128) <> 0 Then
           pos = ChrW(i + 1) & ChrW(j + 1)
           If WherePos(pos, begin) = 0 Then choiceblock = choiceblock & pos
         End If
      End If
    Wend
  DoEvents
  Loop Until l = Len(choiceblock)
  If openblocks + mines = row * col Then
    gamecomplete
  End If
End Sub
Private Function WherePos(pos As String, Optional begin As Integer = 1) As Integer
 Dim i As Integer, j As Integer, l As Integer
 Dim p As Integer
 l = Len(choiceblock)
 i = AscW(Left$(pos, 1))
 j = AscW(Right$(pos, 1))
 WherePos = 0
 p = begin
 Do While p < l
   If AscW(Mid(choiceblock, p, 1)) = i Then
     If AscW(Mid(choiceblock, p + 1, 1)) = j Then
       WherePos = p
       Exit Do
     End If
     p = p + 2
   Else
     p = p + 2
   End If
 Loop
End Function
Private Sub drawblock(i As Integer, j As Integer, _
                  Optional bkcolor As Long = &HC0C0C0)
  Dim x As Integer, y As Integer
  x = blockwidth * (j - 1)
  y = blockheight * (i - 1)
  frm1.Picture1.Line (x, y)-(x + blockwidth - 1, y + blockheight - 1), bkcolor, BF
  frm1.Picture1.Line (x, y)-(x, y + blockheight - 1), &H80000014, BF
  frm1.Picture1.Line (x, y)-(x + blockwidth - 1, y), &H80000014, BF
  frm1.Picture1.Line (x + blockwidth - 1, y + blockheight - 1)-(x, y + blockheight - 1), &H80000010, BF
  frm1.Picture1.Line (x + blockwidth - 1, y + blockheight - 1)-(x + blockwidth - 1, y), &H80000010, BF
End Sub
Private Sub drawpress(i As Integer, j As Integer, _
                    Optional bkcolor As Long = &H80000016)
  Dim x As Integer, y As Integer, k As Integer
  x = blockwidth * j
  y = blockheight * i
  frm1.Picture1.Line (x - blockwidth, y - blockheight)-(x - 1, y - 1), bkcolor, BF
  For k = 1 To 15 Step 2
    frm1.Picture1.PSet (x - k, y), &H80000015
    frm1.Picture1.PSet (x - k, y - 15), &H80000015
    frm1.Picture1.PSet (x, y - k), &H80000015
    frm1.Picture1.PSet (x - 15, y - k), &H80000015
    Next
End Sub
Private Sub drawdigit(i As Integer, j As Integer)
  If minearea(i, j).totalmines > 0 Then
    frm1.Picture1.ForeColor = colortable(minearea(i, j).totalmines)
    frm1.Picture1.CurrentX = blockwidth * j - 14
    frm1.Picture1.CurrentY = blockheight * i - 16
    frm1.Picture1.Print minearea(i, j).totalmines
  End If
End Sub
Private Sub drawflag(i As Integer, j As Integer)
 Dim x As Integer, y As Integer
 x = blockwidth * j
 y = blockheight * i
 frm1.Picture1.Line (x - blockwidth + 1, y - blockheight + 1)-(x - 2, y - 2), &HC0C0C0, BF
 frm1.Picture1.Line (x - 12, y - 12)-(x - 6, y - 8), vbRed, BF
 frm1.Picture1.Line (x - 7, y - 8)-(x - 6, y - 3), vbBlack, BF
End Sub
Private Sub drawmark(i As Integer, j As Integer)
 Dim x As Integer, y As Integer
 x = blockwidth * j
 y = blockheight * i
 frm1.Picture1.Line (x - blockwidth + 1, y - blockheight + 1)-(x - 2, y - 2), &HC0C0C0, BF
 frm1.Picture1.ForeColor = &HFF0000
 frm1.Picture1.CurrentX = x - 11
 frm1.Picture1.CurrentY = y - 16
 frm1.Picture1.Print "?"
End Sub
Private Sub actionleft(i As Integer, j As Integer)
  If (minearea(i, j).flag And conIsMine) <> 0 Then     '踩雷
    If protect Then    '保护状态
      Beep
    Else
      gameend i, j
    End If
  ElseIf (minearea(i, j).flag And conDiscovered) = 0 Then  '该块未打开
     '打开此块
    choiceblock = ChrW(i) & ChrW(j)
    findtoopen
  End If
End Sub
Private Sub actionright(i As Integer, j As Integer)
  If (minearea(i, j).flag And conMarked) <> 0 Then   '标记为?号时
    drawblock i, j
    '修改该块状态
    minearea(i, j).flag = minearea(i, j).flag And (Not conFounded)
    minearea(i, j).flag = minearea(i, j).flag And (Not conMarked)
  ElseIf (minearea(i, j).flag And conFounded) <> 0 Then  '标记为红旗时
    If mark = True Then               '允许标记？号时
     drawmark i, j           '标记?号
     '修改该块状态(使之有?标记)
     minearea(i, j).flag = minearea(i, j).flag Or conMarked
    Else
     drawblock i, j           '擦除红旗
    End If
     '修改该块状态(使之无红旗)
    minearea(i, j).flag = minearea(i, j).flag And (Not conFounded)
     '显示的雷数加一
    labeladd 1, frm1.Label1
  Else                           '无标记、未打开
     drawflag i, j    '标红旗
      '修改该块状态(有红旗、无?号)
     minearea(i, j).flag = minearea(i, j).flag Or conFounded
     minearea(i, j).flag = minearea(i, j).flag And (Not conMarked)
     '显示的雷数减一
     labeladd -1, frm1.Label1
  End If
End Sub
Private Sub actionboth(i As Integer, j As Integer)
  Dim fd As Byte
  Dim tp As Byte
  Dim choice1 As Byte
  Dim inside As Byte
  fd = total(i, j, conFounded, choice, inside)
  tp = total(i, j, conDiscovered, choice1)
  choice = (Not choice) And (Not choice1) And inside
  If minearea(i, j).totalmines > fd Then      '周围雷未排完
    choicerow = i
    choicecol = j
    If (choice And 1) <> 0 Then drawpress i - 1, j - 1
    If (choice And 2) <> 0 Then drawpress i - 1, j
    If (choice And 4) <> 0 Then drawpress i - 1, j + 1
    If (choice And 8) <> 0 Then drawpress i, j - 1
    If (choice And 16) <> 0 Then drawpress i, j + 1
    If (choice And 32) <> 0 Then drawpress i + 1, j - 1
    If (choice And 64) <> 0 Then drawpress i + 1, j
    If (choice And 128) <> 0 Then drawpress i + 1, j + 1
  ElseIf minearea(i, j).totalmines < fd Then  '周围排雷数>周围雷数
    Beep
  Else       '周围排雷数=周围雷数
    choice1 = findmineerr(i, j)   '寻找标错的雷(插红旗、不是雷)
    If choice1 <> 0 Then          '有标错的雷
      If protect Then
        Beep
      Else
        gameend i, j, False
      End If
    Else
      findtoopen
    End If
  End If
End Sub
Private Sub gameend(i As Integer, j As Integer, _
             Optional leftclick As Boolean = True)
  Dim m As Integer, n As Integer
  Dim tp As Byte
  Dim choice1 As Byte
  Dim inside As Byte
  frm1.Command1.Caption = "触 雷"
  frm1.mnuhelponce.Enabled = False
  frm1.mnuhelpchoice.Enabled = False
  frm1.mnuhelpall.Enabled = False
  gameover = True
  IsWorking = False
  For m = 1 To row
    For n = 1 To col
      If (minearea(m, n).flag And conIsMine) <> 0 Then
        If (minearea(m, n).flag And conFounded) = 0 Then  '有雷、未发现
          drawpress m, n
          drawmine m, n      '画雷
        End If
      Else
        If (minearea(m, n).flag And conFounded) <> 0 Then  '发现错误
          drawpress m, n
          drawcross m, n    '画叉号
        End If
      End If
    Next
  Next
  If leftclick Then  '左键触雷
    drawpress i, j, vbRed
    drawmine i, j
  Else
    tp = total(i, j, conFounded, choice, inside)
    tp = total(i, j, conIsMine, choice1)
    choice = choice1 And (Not choice) And inside
    If (choice And 1) <> 0 Then
      drawpress i - 1, j - 1, vbRed
      drawmine i - 1, j - 1
    End If
    If (choice And 2) <> 0 Then
      drawpress i - 1, j, vbRed
      drawmine i - 1, j
    End If
    If (choice And 4) <> 0 Then
      drawpress i - 1, j + 1, vbRed
      drawmine i - 1, j + 1
    End If
    If (choice And 8) <> 0 Then
      drawpress i, j - 1, vbRed
      drawmine i, j - 1
    End If
    If (choice And 16) <> 0 Then
      drawpress i, j + 1, vbRed
      drawmine i, j + 1
    End If
    If (choice And 32) <> 0 Then
      drawpress i + 1, j - 1, vbRed
      drawmine i + 1, j - 1
    End If
    If (choice And 64) <> 0 Then
      drawpress i + 1, j, vbRed
      drawmine i + 1, j
    End If
    If (choice And 128) <> 0 Then
      drawpress i + 1, j + 1, vbRed
      drawmine i + 1, j + 1
    End If
  End If
End Sub

Public Sub drawchoiceblock()
  If choicerow <= 0 Or choicecol <= 0 Then Exit Sub
  Dim i As Integer, j As Integer
  i = choicerow
  j = choicecol
  If (choice And 1) <> 0 Then
    drawblock i - 1, j - 1
    If (minearea(i - 1, j - 1).flag And conMarked) <> 0 Then drawmark i - 1, j - 1
  End If
  If (choice And 2) <> 0 Then
    drawblock i - 1, j
    If (minearea(i - 1, j).flag And conMarked) <> 0 Then drawmark i - 1, j
  End If
  If (choice And 4) <> 0 Then
    drawblock i - 1, j + 1
    If (minearea(i - 1, j + 1).flag And conMarked) <> 0 Then drawmark i - 1, j + 1
  End If
  If (choice And 8) <> 0 Then
    drawblock i, j - 1
    If (minearea(i, j - 1).flag And conMarked) <> 0 Then drawmark i, j - 1
  End If
  If (choice And 16) <> 0 Then
    drawblock i, j + 1
    If (minearea(i, j + 1).flag And conMarked) <> 0 Then drawmark i, j + 1
  End If
  If (choice And 32) <> 0 Then
    drawblock i + 1, j - 1
    If (minearea(i + 1, j - 1).flag And conMarked) <> 0 Then drawmark i + 1, j - 1
  End If
  If (choice And 64) <> 0 Then
    drawblock i + 1, j
    If (minearea(i + 1, j).flag And conMarked) <> 0 Then drawmark i + 1, j
  End If
  If (choice And 128) <> 0 Then
    drawblock i + 1, j + 1
    If (minearea(i + 1, j + 1).flag And conMarked) <> 0 Then drawmark i + 1, j + 1
  End If
End Sub
Private Sub labeladd(value As Integer, Label As Object)
  Dim cap As Integer
  cap = Val(Label.Caption) + value
  If cap < 0 Then
    Label.Caption = "-" & Mid(Str$(1000 - cap), 4, 2)
  Else
    Label.Caption = Mid(Str$(cap + 1000), 3, 3)
  End If
End Sub

Private Function findmineerr(i As Integer, j As Integer) As Byte
    findmineerr = 0     '排错雷数初始化
    choiceblock = ""    '选中块初始化
    If (choice And 1) <> 0 Then
      choiceblock = choiceblock & ChrW(i - 1) & ChrW(j - 1)
      If (minearea(i - 1, j - 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 1
      End If
    End If
    If (choice And 2) <> 0 Then
      choiceblock = choiceblock & ChrW(i - 1) & ChrW(j)
      If (minearea(i - 1, j).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 2
      End If
    End If
    If (choice And 4) <> 0 Then
      choiceblock = choiceblock & ChrW(i - 1) & ChrW(j + 1)
      If (minearea(i - 1, j + 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 4
      End If
    End If
    If (choice And 8) <> 0 Then
      choiceblock = choiceblock & ChrW(i) & ChrW(j - 1)
      If (minearea(i, j - 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 8
      End If
    End If
    If (choice And 16) <> 0 Then
      choiceblock = choiceblock & ChrW(i) & ChrW(j + 1)
      If (minearea(i, j + 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 16
      End If
    End If
    If (choice And 32) <> 0 Then
      choiceblock = choiceblock & ChrW(i + 1) & ChrW(j - 1)
      If (minearea(i + 1, j - 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 32
      End If
    End If
    If (choice And 64) <> 0 Then
      choiceblock = choiceblock & ChrW(i + 1) & ChrW(j)
      If (minearea(i + 1, j).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 64
      End If
    End If
    If (choice And 128) <> 0 Then
      choiceblock = choiceblock & ChrW(i + 1) & ChrW(j + 1)
      If (minearea(i + 1, j + 1).flag And conIsMine) <> 0 Then
        findmineerr = findmineerr Or 128
      End If
    End If
End Function

Private Sub drawmine(i As Integer, j As Integer)
  Dim x As Integer
  Dim y As Integer
  x = blockwidth * j - 8
  y = blockheight * i - 8
  frm1.Picture1.Line (x + 5, y)-(x - 6, y), vbBlack
  frm1.Picture1.Line (x, y + 5)-(x, y - 6), vbBlack
  frm1.Picture1.Circle (x, y), 3, vbBlack
  frm1.Picture1.PSet (x - 1, y - 1), vbWhite
End Sub
Private Sub drawcross(i As Integer, j As Integer)
  Dim x As Integer
  Dim y As Integer
  x = blockwidth * j - 12
  y = blockheight * i - 13
  frm1.Picture1.Line (x, y)-(x + 10, y + 10), vbRed
  frm1.Picture1.Line (x - 1, y + 1)-(x + 9, y + 11), vbRed
  frm1.Picture1.Line (x, y + 10)-(x + 10, y), vbRed
  frm1.Picture1.Line (x - 1, y + 9)-(x + 9, y - 1), vbRed
End Sub
Public Sub gamecomplete()
  Dim i As Integer, j As Integer
  Dim tm As Integer
  Dim name As String
  Dim prompt As String
  Dim dif(0 To 2) As String
  gameover = True
  IsWorking = False
  frm1.Command1.Caption = "结 束"
  frm1.Label1.Caption = "000"
  frm1.mnuhelponce.Enabled = False
  frm1.mnuhelpall.Enabled = False
  frm1.mnuhelpchoice.Enabled = False
  For i = 1 To row
    DoEvents
    For j = 1 To col
      If (minearea(i, j).flag And conIsMine) <> 0 Then
        If (minearea(i, j).flag And conFounded) = 0 Then
          drawflag i, j
        End If
      Else
        drawpress i, j
        drawdigit i, j
      End If
    Next
  Next
  If diff < 3 Then
    tm = Val(frm1.Label2.Caption)
    If tm < times(diff) Then
      dif(0) = "初级"
      dif(1) = "中级"
      dif(2) = "高级"
      prompt = "您已成为" & dif(diff) & "第一高手" & Chr(13) & Chr(10) _
               & Chr(13) & Chr(10) & "请输入您的大名:"
      name = InputBox(prompt, "恭喜恭喜", heroname(diff))
      If name <> "" Then
        heroname(diff) = name
        times(diff) = tm
        frm1.Enabled = False
        frm3.Show
      End If
    End If
  End If
End Sub
Public Sub helponce()
  Dim i As Integer
  Dim j As Integer
  Dim l As Integer
  Dim tp As Integer
  Randomize Timer
  choiceblock = ""
  For i = 1 To row
    For j = 1 To col
      If (minearea(i, j).flag And conIsMine) = 0 Then
        If (minearea(i, j).flag And conDiscovered) = 0 Then
          choiceblock = choiceblock & ChrW(i) & ChrW(j)
        End If
      End If
    Next
  Next
  l = Len(choiceblock) / 2
  tp = Int(l * Rnd + 1)
  choiceblock = Mid(choiceblock, 2 * tp - 1, 2)
  findtoopen
End Sub
Public Sub choosehelp(Button As Integer, x As Single, y As Single)
 Dim i As Integer, j As Integer
 i = Int(y / blockheight) + 1
 j = Int(x / blockwidth) + 1
 Select Case Button
   Case vbLeftButton      '鼠标左键
     If shiftchoice Then  'SHIFT+鼠标键的起点已经选中
       EndChoiceHelp      '结束SHIFT+鼠标键选择
     ElseIf (minearea(i, j).flag And conDiscovered) = 0 Then   '该块未打开
       If (minearea(i, j).flag And conChoosed) = 0 Then   '该块未选中
         addablock i, j
       Else
         deleteablock i, j
       End If
     End If
   Case vbRightButton     '鼠标右键
     If shiftchoice Then  'SHIFT+鼠标键的起点已经选中
       EndChoiceHelp      '结束SHIFT+鼠标键选择
     Else
       doHelpchoice
     End If
 End Select
 If Button > 10 And Button < 13 Then    'SHIFT+鼠标键
     If shiftchoice Then                '起点已经选中
       EndChoiceHelp                    '结束SHIFT+鼠标键选择
       choicex0 = i
       choicey0 = j
       choice = Button - 10
       modifychoice
     Else      '起点未选中
       shiftchoice = True
       frm1.Picture1.DrawMode = vbXorPen
       choicerow = i
       choicecol = j
       choicex0 = choicecol * blockwidth - blockwidth / 2
       choicey0 = choicerow * blockheight - blockheight / 2
       oldx = choicex0
       oldy = choicey0
       frm1.Picture1.Line (choicex0, choicey0)-(oldx, oldy), &HC0C03F, B
     End If
 End If
 If Button > 20 And Button < 23 Then   'CTRL+鼠标键
    If shiftchoice Then
      EndChoiceHelp      '结束SHIFT+鼠标键选择
    End If
    If minearea(i, j).flag = conDiscovered Then  '该块未打开
      choicex0 = i
      choicey0 = j
      choice = Button - 20
      choosebordery       '增加或删除边界
    End If
 End If
End Sub
Public Sub doHelpchoice()
  Dim i As Integer, j As Integer
  Dim l As Integer
  Dim p As Integer
  Dim ch As String
  helpchoice = False      '停止选择帮助
  choicerow = 0           '使PICTURE_MOUSEUP事件无效
  frm1.mnuhelpchoice.Checked = False
  frm1.Picture1.MousePointer = 0    '恢复鼠标形状
  frm1.mnuhelponce.Enabled = True
  frm1.mnuhelpall.Enabled = True
  ch = choiceblock
  choiceblock = ""
  l = Len(ch)
  For p = 1 To l - 1 Step 2
    i = AscW(Mid(ch, p, 1))
    j = AscW(Mid(ch, p + 1, 1))
    If (minearea(i, j).flag And conIsMine) <> 0 Then    '若有雷
      drawflag i, j
      If (minearea(i, j).flag And conFounded) = 0 Then
        labeladd -1, frm1.Label1             '显示雷数减一
      End If
      minearea(i, j).flag = conFounded Or conIsMine
    Else      '若无雷
      choiceblock = choiceblock & ChrW(i) & ChrW(j)
    End If
  Next
  findtoopen   '打开无雷区(根据choiceblock)
End Sub
Private Sub modifychoice()
  Dim i As Integer, j As Integer
  Dim tp As Integer
  If choicex0 < choicerow Then
    tp = choicerow
    choicerow = choicex0
    choicex0 = tp
  End If
  If choicey0 < choicecol Then
    tp = choicecol
    choicecol = choicey0
    choicey0 = tp
  End If
  For i = choicerow To choicex0
      For j = choicecol To choicey0
        If choice = vbLeftButton Then
          addablock i, j
        Else
          deleteablock i, j
        End If
      Next
  Next
End Sub
Private Sub deleteablock(i As Integer, j As Integer)
  Dim tp As Integer
  If (minearea(i, j).flag And conChoosed) = 0 Then Exit Sub
  If (minearea(i, j).flag And conFounded) <> 0 Then
     drawflag i, j
  ElseIf (minearea(i, j).flag And conMarked) <> 0 Then
     drawmark i, j
  Else
     drawblock i, j
  End If
  '删除该块
  tp = WherePos(ChrW(i) & ChrW(j))
  If tp > 0 Then
    choiceblock = Left(choiceblock, tp - 1) & Mid(choiceblock, tp + 2)
  End If
  minearea(i, j).flag = minearea(i, j).flag And (Not conChoosed)
End Sub
Private Sub addablock(i As Integer, j As Integer)
   If (minearea(i, j).flag And conDiscovered) <> 0 Then Exit Sub
   If (minearea(i, j).flag And conChoosed) <> 0 Then Exit Sub
   choiceblock = choiceblock & ChrW(i) & ChrW(j)
   drawblock i, j, vbYellow
   minearea(i, j).flag = minearea(i, j).flag Or conChoosed
End Sub
Private Sub EndChoiceHelp()
   shiftchoice = False
   frm1.Picture1.Line (choicex0, choicey0)-(oldx, oldy), &HC0C03F, B
   frm1.Picture1.DrawMode = vbCopyPen
End Sub
'增加或删除边界
Private Sub choosebordery()
'查找打开块(存入choiceblock)
Dim openarea As String
Dim i As Integer, j As Integer, k As Integer, l As Integer
Dim p As Integer, tp As Byte
Dim pos As String
Dim choice1 As Byte
Dim inside As Byte
Dim begin As Integer
openarea = choiceblock  '备份choiceblock
choiceblock = ChrW(choicex0) & ChrW(choicey0)
p = 1
While p < Len(choiceblock)
  i = AscW(Mid(choiceblock, p, 1))
  p = p + 1
  j = AscW(Mid(choiceblock, p, 1))
  p = p + 1
  drawblock i, j, vbGreen
  tp = total(i, j, conDiscovered, choice1)    '寻找打开块
  If (choice1 And 1) <> 0 Then
    pos = ChrW(i - 1) & ChrW(j - 1)
    If WherePos(pos) = 0 Then
     choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 2) <> 0 Then
    pos = ChrW(i - 1) & ChrW(j)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 4) <> 0 Then
    pos = ChrW(i - 1) & ChrW(j + 1)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 8) <> 0 Then
    pos = ChrW(i) & ChrW(j - 1)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 16) <> 0 Then
    pos = ChrW(i) & ChrW(j + 1)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 32) <> 0 Then
    pos = ChrW(i + 1) & ChrW(j - 1)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 64) <> 0 Then
    pos = ChrW(i + 1) & ChrW(j)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
  If (choice1 And 128) <> 0 Then
    pos = ChrW(i + 1) & ChrW(j + 1)
    If WherePos(pos) = 0 Then
      choiceblock = choiceblock & pos
    End If
  End If
DoEvents
Wend
pos = openarea
openarea = choiceblock
choiceblock = pos
'查找边界（存入POS）
pos = ""
p = 1
l = Len(openarea)
While p < l
  i = AscW(Mid(openarea, p, 1))
  p = p + 1
  j = AscW(Mid(openarea, p, 1))
  p = p + 1
  tp = total(i, j, conDiscovered, choice1, inside)
  choice1 = (Not choice1) And inside
  If (choice1 And 1) <> 0 Then
      pos = pos & ChrW(i - 1) & ChrW(j - 1)
  End If
  If (choice1 And 2) <> 0 Then
      pos = pos & ChrW(i - 1) & ChrW(j)
  End If
  If (choice1 And 4) <> 0 Then
      pos = pos & ChrW(i - 1) & ChrW(j + 1)
  End If
  If (choice1 And 8) <> 0 Then
      pos = pos & ChrW(i) & ChrW(j - 1)
  End If
  If (choice1 And 16) <> 0 Then
      pos = pos & ChrW(i) & ChrW(j + 1)
  End If
  If (choice1 And 32) <> 0 Then
      pos = pos & ChrW(i + 1) & ChrW(j - 1)
  End If
  If (choice1 And 64) <> 0 Then
      pos = pos & ChrW(i + 1) & ChrW(j)
  End If
  If (choice1 And 128) <> 0 Then
      pos = pos & ChrW(i + 1) & ChrW(j + 1)
  End If
  DoEvents
Wend
'增加或删除选项
p = 1
l = Len(pos)
While p < l
  i = AscW(Mid(pos, p, 1))
  p = p + 1
  j = AscW(Mid(pos, p, 1))
  p = p + 1
  If choice = vbLeftButton Then
    addablock i, j
  Else
    deleteablock i, j
  End If
  DoEvents
Wend
'恢复已经打开的区域
p = 1
l = Len(openarea)
While p < l
  i = AscW(Mid(openarea, p, 1))
  p = p + 1
  j = AscW(Mid(openarea, p, 1))
  p = p + 1
  drawpress i, j
  drawdigit i, j
  DoEvents
Wend
End Sub

