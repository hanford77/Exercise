DECLARE SUB outhz (CX!, CY!, a$)
SCREEN 9, 14
CALL outhz(30, 20, "Òó")
CALL outhz(70, 20, "º£")
CALL outhz(110, 20, "·å")
CALL outhz(30, 60, "³Â")
END

SUB outhz (CX, CY, a$)
DIM ch AS STRING * 72
OPEN "e:\yhf\bas\hzk24k" FOR RANDOM AS 1 LEN = 72
kh = ASC(a$): kl = ASC(MID$(a$, 2))
GET #1, (kh - &HA1 - 15) * 94 + kl - &HA0, ch
l = 0
FOR i = 1 TO 24
FOR j = 1 TO 3
kk = 128: l = l + 1
FOR k = 1 TO 8
IF kk AND ASC(MID$(ch, l, 1)) THEN
PSET (CX + i, CY + j * 8 - 9 + k), 14
END IF
kk = kk / 2
NEXT
NEXT
NEXT
CLOSE
END SUB

