'将PC-E500程序(E500.PRG)中的标号查出(放在LB.TXT)
DECLARE FUNCTION isnum% (a$)
DECLARE FUNCTION label$ (a$)
OPEN "e:\yhf\com\e500.prg" FOR INPUT AS 1
DIM d$(1000)
count = 0
WHILE NOT EOF(1)
LINE INPUT #1, ln$
k = INSTR(ln$, " *")
IF k <> 0 THEN
 IF isnum(MID$(ln$, 1, k - 1)) THEN
  lb$ = label$(MID$(ln$, k + 1))
  d$(count) = lb$
  count = count + 1
 END IF
END IF
WEND
OPEN "lb.txt" FOR OUTPUT AS 2
FOR i = 0 TO count - 2
 a$ = CHR$(255)
 FOR j = i TO count - 1
  IF a$ > d$(j) THEN l = j: a$ = d$(j)
 NEXT
 IF i <> l THEN
  SWAP d$(i), d$(l)
 END IF
NEXT
FOR i = 1 TO count
 PRINT #2, d$(i - 1); " ";
 IF (i AND 15) = 0 THEN PRINT #2,
NEXT
CLOSE
END

FUNCTION isnum% (a$)
l = LEN(a$)
FOR i = 1 TO l
 k = ASC(MID$(a$, i, 1))
 IF k < 48 OR k > 59 THEN
  EXIT FUNCTION
 END IF
NEXT
isnum% = -1
END FUNCTION

FUNCTION label$ (a$)
k = INSTR(a$, ":")
IF k = 0 THEN
 label$ = a$
ELSE
 label$ = MID$(a$, 1, k - 1)
END IF
END FUNCTION

