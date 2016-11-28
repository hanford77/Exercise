'将PC-E500S程序(E500.PRG)中的不能改变的行号查出来(放在LNO.TXT)
DECLARE FUNCTION ch34% (a$, k!)
DECLARE SUB insert (lno!)
DECLARE FUNCTION isnum% (ch$)
OPEN "e:\yhf\com\e500.prg" FOR INPUT AS 1
OPEN "lno.txt" FOR OUTPUT AS 2
DIM SHARED lno(1 TO 1000) AS INTEGER   '不能改变的行号数组
DIM SHARED no AS INTEGER               '不能改变的行号数目
WHILE NOT EOF(1)
LINE INPUT #1, ln$
kk = 1
DO
k = INSTR(kk, ln$, "GOTO")
IF k > 0 THEN k = k + 4: kk = k: a$ = "goto": GOSUB getlno
LOOP WHILE k > 0
kk = 1
DO
k = INSTR(kk, ln$, "THEN")
IF k > 0 THEN k = k + 4: kk = k: a$ = "then": GOSUB getlno
LOOP WHILE k > 0
kk = 1
DO
k = INSTR(kk, ln$, "ELSE")
IF k > 0 THEN k = k + 4: kk = k: a$ = "else": GOSUB getlno
LOOP WHILE k > 0
kk = 1
DO
k = INSTR(kk, ln$, "GOSUB")
IF k > 0 THEN k = k + 5: kk = k: a$ = "gosub": GOSUB getlno
LOOP WHILE k > 0
WEND
FOR i = 1 TO no
PRINT #2, USING "#####"; lno(i);
IF (i AND 15) = 0 THEN PRINT #2,
NEXT
CLOSE
END

getlno:
'如果GOTO,THEN,ELSE,GOSUB在双引号内则返回
IF ch34(ln$, k) AND 1 THEN RETURN
'去掉空格
WHILE MID$(ln$, k, 1) = " "
 k = k + 1
WEND
sing = 0    '有连续的行号为假
IF MID$(ln$, k, 1) = "*" THEN
 IF MID$(a$, 1, 2) = "go" THEN sing = -1
ELSE
 p = k
 WHILE isnum(MID$(ln$, p, 1))
  p = p + 1
 WEND
 IF p = k THEN RETURN    '如果<行号>不为数字字符串则返回
 lno = VAL(MID$(ln$, k, p - k))
 CALL insert(lno)        '记下该行号
 IF MID$(a$, 1, 2) = "go" THEN sing = -1
END IF
IF sing THEN
 p = INSTR(k, ln$, ":")
 q = INSTR(k, ln$, ",")
 IF q <> 0 THEN
  IF p = 0 OR q < p THEN
   k = q + 1: GOTO getlno
  END IF
 END IF
END IF
RETURN

FUNCTION ch34% (a$, k)
p% = 0: c% = 0
DO
p% = INSTR(p% + 1, a$, CHR$(34))
c% = c% + 1
LOOP WHILE p% < k AND p% <> 0
ch34% = c% - 1
END FUNCTION

SUB insert (lno)
IF lno = 0 THEN EXIT SUB
IF no = 0 THEN
 no = no + 1
 lno(1) = lno
 EXIT SUB
END IF
IF lno < lno(1) THEN
 FOR i = no TO 1 STEP -1
  lno(i + 1) = lno(i)
 NEXT
 no = no + 1
 lno(1) = lno
 EXIT SUB
END IF
IF lno > lno(no) THEN
 no = no + 1
 lno(no) = lno
 EXIT SUB
END IF
top = 1
bot = no
WHILE bot - top > 1
mid = INT((top + bot) / 2)
IF lno > lno(mid) THEN
 top = mid
ELSE
 bot = mid
END IF
WEND
IF lno = lno(bot) OR lno = lno(top) THEN EXIT SUB
FOR i = no TO bot STEP -1
 lno(i + 1) = lno(i)
NEXT
no = no + 1
lno(bot) = lno
END SUB

FUNCTION isnum% (ch$)
IF ch$ >= "0" AND ch$ <= "9" THEN
 isnum% = -1
 EXIT FUNCTION
END IF
END FUNCTION

