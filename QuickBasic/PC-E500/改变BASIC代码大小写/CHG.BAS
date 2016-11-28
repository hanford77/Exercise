DIM S AS INTEGER
INPUT "Filename:", F$
DO
INPUT "Type(Upper/Low):", C$
C$ = UCASE$(C$)
LOOP WHILE C$ <> "U" AND C$ <> "L"
OPEN F$ FOR INPUT AS 1
OPEN "TMP.TXT" FOR OUTPUT AS 2
WHILE NOT EOF(1)
LINE INPUT #1, A$
B$ = UCASE$(LTRIM$(A$))
IF INSTR(B$, "REM") = 1 OR INSTR(B$, CHR$(39)) = 1 THEN
PRINT #2, A$
GOTO LP
END IF
A$ = A$ + CHR$(34)
S = 1: L = LEN(A$)
P2 = INSTR(A$, CHR$(34))
IF C$ = "U" THEN
B$ = UCASE$(MID$(A$, 1, P2 - 1))
ELSE
B$ = LCASE$(MID$(A$, 1, P2 - 1))
END IF
WHILE P2 < L
P1 = P2: S = -S
P2 = INSTR(P1 + 1, A$, CHR$(34))
IF S = 1 THEN
IF C$ = "U" THEN
B$ = B$ + UCASE$(MID$(A$, P1, P2 - P1))
ELSE
B$ = B$ + LCASE$(MID$(A$, P1, P2 - P1))
END IF
ELSE
B$ = B$ + MID$(A$, P1, P2 - P1)
END IF
WEND
PRINT #2, B$
LP:
WEND
CLOSE
END

