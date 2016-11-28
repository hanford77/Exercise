DECLARE FUNCTION isalnum! (a$)
DECLARE SUB change (a$)
maxno = 5000
path$ = "e:\yhf\bas\"
OPTION BASE 1
DIM SHARED lno(maxno, 2), ch(50, 3), chg(50)
DIM SHARED kno, nno
CLS
PRINT "input L1-L2"
INPUT "L1="; l1
INPUT "L2="; l2
PRINT "input L0"
INPUT "L0="; l0
INPUT "d="; dno
no = l0
OPEN path$ + "e500.prg" FOR INPUT AS 1
OPEN path$ + "e500.tmp" FOR OUTPUT AS 2
WHILE NOT EOF(1)
LINE INPUT #1, a$
a$ = LTRIM$(a$): a$ = RTRIM$(a$)
IF a$ = "" THEN GOTO lp
k = ASC(a$)
IF k > ASC("9") OR k < ASC("1") THEN GOTO lp
k = INSTR(a$, " ")
IF k = 0 THEN GOTO lp
kno = kno + 1
lno(kno, 1) = VAL(MID$(a$, 1, k - 1))
a$ = MID$(a$, k)
IF lno(kno, 1) >= l1 AND lno(kno, 1) <= l2 THEN
lno(kno, 2) = no: no = no + dno
ELSE
lno(kno, 2) = lno(kno, 1)
END IF
PRINT #2, MID$(STR$(lno(kno, 2)), 2); a$
lp:
WEND
CLOSE
OPEN path$ + "e500.tmp" FOR INPUT AS 1
OPEN path$ + "e500.bak" FOR OUTPUT AS 2
WHILE NOT EOF(1)
LINE INPUT #1, a$
nno = nno + 1
LOCATE 10, 35: PRINT nno
CALL change(a$)
PRINT #2, a$
WEND
CLOSE
KILL path$ + "e500.tmp"
END

SUB change (a$)
kch = 0
kfd = 0
p = 1
l1:
k = INSTR(p, a$, "GOTO")
IF k <> 0 THEN
p = k + 4: kfd = kfd + 1: chg(kfd) = p
GOTO l1
END IF
p = 1
l2:
k = INSTR(p, a$, "THEN")
IF k <> 0 THEN
p = k + 4: kfd = kfd + 1: chg(kfd) = p
GOTO l2
END IF
p = 1
l3:
k = INSTR(p, a$, "GOSUB")
IF k <> 0 THEN
p = k + 5: kfd = kfd + 1: chg(kfd) = p
GOTO l3
END IF
p = 1
l4:
k = INSTR(p, a$, "ELSE")
IF k <> 0 THEN
p = k + 4: kfd = kfd + 1: chg(kfd) = p
GOTO l4
END IF
IF kfd = 0 THEN EXIT SUB
FOR i = 1 TO kfd - 1
min = chg(i): l = i
FOR j = i + 1 TO kfd
IF min > chg(j) THEN min = chg(j): l = j
NEXT
IF l <> i THEN SWAP chg(i), chg(l)
NEXT
chg(kfd + 1) = LEN(a$) + 1
FOR i = 1 TO kfd
p = chg(i)
WHILE p < chg(i + 1)
b$ = MID$(a$, p, 1)
IF b$ >= "0" AND b$ <= "9" THEN
kch = kch + 1
ch(kch, 2) = p
DO
p = p + 1
b$ = MID$(a$, p, 1)
LOOP WHILE b$ >= "0" AND b$ <= "9"
ch(kch, 1) = VAL(MID$(a$, ch(kch, 2), p - ch(kch, 2)))
ch(kch, 3) = p - 1
fd = 0
FOR j = 1 TO kno
IF ch(kch, 1) = lno(j, 1) THEN ch(kch, 1) = lno(j, 2): fd = -1: j = kno + 1
NEXT
IF fd = 0 THEN
PRINT "error:"; nno; "no lno"; ch(kch, 1)
END
END IF
ELSEIF b$ = " " OR b$ = "," THEN
p = p + 1
ELSEIF b$ = ":" THEN
GOTO l5
ELSEIF b$ = "*" THEN
DO
p = p + 1
b$ = MID$(a$, p, 1)
LOOP WHILE isalnum(b$)
ELSE
GOTO l5
END IF
WEND
l5:
NEXT
IF kch = 0 THEN EXIT SUB
b$ = MID$(a$, 1, ch(1, 2) - 1) + MID$(STR$(ch(1, 1)), 2)
FOR i = 2 TO kch
b$ = b$ + MID$(a$, ch(i - 1, 3) + 1, ch(i, 2) - ch(i - 1, 3) - 1) + MID$(STR$(ch(i, 1)), 2)
NEXT
a$ = b$
END SUB

FUNCTION isalnum (a$)
IF a$ = "" THEN
isalnum = 0
EXIT FUNCTION
END IF
b$ = MID$(a$, 1, 1)
IF b$ >= "0" AND b$ <= "9" THEN
isalnum = -1
EXIT FUNCTION
END IF
IF b$ >= "A" AND b$ <= "Z" THEN
isalnum = -1
EXIT FUNCTION
END IF
END FUNCTION

