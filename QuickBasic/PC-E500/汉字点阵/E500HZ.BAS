DECLARE SUB TRIM (A$)
REM ½«ºº×ÖµãÕó¸øPC-E500
DIM HM%(3)
DIM DOT(16, 16) AS INTEGER
DIM A$(2)
SCREEN 9
COLOR 14
OPEN "E:\YHF\COM\E500.HZK" FOR OUTPUT AS 1
OPEN "E:\YHF\COM\E500.HZ" FOR INPUT AS 2
WHILE NOT EOF(2)
LINE INPUT #2, CH$
CH$ = LTRIM$(CH$): CH$ = RTRIM$(CH$)
L = LEN(CH$)
FOR III = 1 TO L STEP 2
PRINT MID$(CH$, III, 2)
II = 1: JJ = 1
FOR ROW = 0 TO 15
I = 0
FOR K = 1 TO 2
FOR KK = 1 TO 8
GET (I, ROW)-(I, ROW), HM%
IF HM%(2) <> 0 OR HM%(3) <> 0 THEN
DOT(II, JJ) = 1
ELSE
DOT(II, JJ) = 0
END IF
JJ = JJ + 1
IF JJ = 17 THEN JJ = 1: II = II + 1
I = I + 1
NEXT KK
NEXT K
NEXT ROW
A$(1) = ""
A$(2) = ""
FOR K = 1 TO 2
FOR J = 1 TO 16
FOR I = 1 TO 2
JJ = J: S = 0: T = 1
IF K = 1 AND I = 1 THEN II = 5
IF K = 1 AND I = 2 THEN II = 1
IF K = 2 AND I = 1 THEN II = 13
IF K = 2 AND I = 2 THEN II = 9
FOR KK = 1 TO 4
S = S + T * DOT(II, JJ)
II = II + 1
T = T * 2
NEXT KK
A$(K) = A$(K) + HEX$(S)
AA$ = AA$ + HEX$(S)
NEXT I
NEXT J
NEXT K
CALL TRIM(A$(1))
CALL TRIM(A$(2))
PRINT #1, A$(1); ","; A$(2)
CLS
NEXT III
WEND
CLOSE
END

SUB TRIM (A$)
L = 32
B$ = MID$(A$, L, 1)
WHILE B$ = "0"
L = L - 1
B$ = MID$(A$, L, 1)
WEND
A$ = MID$(A$, 1, L)
END SUB

