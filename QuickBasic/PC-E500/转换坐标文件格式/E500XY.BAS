OPEN "e:\yhf\com\e500.xy" FOR INPUT AS 1
OPEN "e:\yhf\com\e500.xyh" FOR OUTPUT AS 2
lp:
WHILE NOT EOF(1)
LINE INPUT #1, a$
a$ = LTRIM$(a$): a$ = RTRIM$(a$)
IF a$ = "" THEN GOTO lp
k = INSTR(1, a$, " ")
cd$ = MID$(a$, 1, k - 1) + ","
a$ = LTRIM$(MID$(a$, k))
k = INSTR(1, a$, " ")
x$ = MID$(a$, 1, k - 1) + ","
a$ = LTRIM$(MID$(a$, k))
k = INSTR(1, a$, " ")
y$ = MID$(a$, 1, k - 1) + ","
z$ = LTRIM$(MID$(a$, k))
k = INSTR(1, z$, ".")
IF k <> 0 THEN
l = LEN(z$)
WHILE RIGHT$(z$, 1) = "0"
l = l - 1
z$ = LEFT$(z$, l)
WEND
IF RIGHT$(z$, 1) = "." THEN z$ = LEFT$(z$, l - 1)
END IF
PRINT #2, cd$ + x$ + y$ + z$
WEND
END


