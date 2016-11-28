DIM dot(16, 16)
DIM ch AS STRING * 24
OPEN "e:\yhf\bas\hzk12" FOR RANDOM AS 1 LEN = 24
a$ = "¶È"
kh = ASC(a$): kl = ASC(MID$(a$, 2))
GET #1, (kh - &HA1) * 94 + kl - &HA0, ch
SCREEN 9, 14
cx = 100: cy = 100
l = 0
FOR i = 1 TO 12
FOR j = 1 TO 2
kk = 128: l = l + 1
FOR k = 1 TO 8
IF kk AND ASC(MID$(ch, l, 1)) THEN
PSET (cx + j * 8 - 9 + k, cy + i), 14
END IF
kk = kk / 2
NEXT

GOTO lp
DO
LOOP WHILE INKEY$ = ""
lp:

NEXT
NEXT
END



