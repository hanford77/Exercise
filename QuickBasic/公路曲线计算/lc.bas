DECLARE FUNCTION lc$ (l AS DOUBLE)
DECLARE FUNCTION sjl# (bcl$)

FUNCTION lc$ (l AS DOUBLE)
zh = l
a$ = " "
IF xl$ = "1" THEN
 IF zh > 1914.98 THEN zh = zh + 2.9
END IF
IF xl$ = "3X" THEN
 IF zh >= 2868.18 THEN
  IF zh <= 3217.66 THEN
   a$ = "Y"
  ELSEIF zh < 3449.1 THEN
   zh = zh - 11.29
  ELSEIF zh <= 3820.09 THEN
   a$ = "Y"
   zh = zh - 11.29
  ELSEIF zh > 3820.09 THEN
   zh = zh - 23.49
  END IF
 END IF
END IF
n = INT((zh + .001) / 1000)
a$ = a$ + "K" + MID$(STR$(n), 2) + "+" + MID$(STR$(zh - n * 1000 + 1000.001), 3, 6)
IF RIGHT$(a$, 3) = ".00" THEN a$ = MID$(a$, 1, LEN(a$) - 3) + "   "
lc$ = a$
END FUNCTION

FUNCTION sjl# (bcl$)
 d$ = UCASE$(MID$(bcl$, 1, 1))
 IF d$ = "Y" THEN
  lcc = VAL(MID$(bcl$, 2))
 ELSE
  lcc = VAL(bcl$)
 END IF
 IF xl$ = "1" THEN
  IF lcc > 1917.88 THEN
   sjl = lcc - 2.9
   EXIT FUNCTION
  END IF
 END IF
 IF xl$ = "3X" THEN
  IF d$ <> "Y" THEN
   IF lcc <= 2868.18 THEN
    sjl = lcc
    EXIT FUNCTION
   ELSEIF lcc < 3206.37 THEN
    PRINT "error:3X L$:"; bcl$
    SYSTEM
   ELSEIF lcc <= 3437.81 THEN
    sjl = lcc + 11.29
    EXIT FUNCTION
   ELSEIF lcc >= 3796.6 THEN
    sjl = lcc + 23.49
    EXIT FUNCTION
   ELSE
    PRINT "error 3X L$:"; bcl$
    SYSTEM
   END IF
  ELSE
   IF lcc >= 2868.18 AND lcc <= 3217.66 THEN sjl = lcc: EXIT FUNCTION
   IF lcc >= 3437.81 AND lcc <= 3808.8 THEN sjl = lcc + 11.29: EXIT FUNCTION
   PRINT "error:3X L$:"; bcl$
   SYSTEM
  END IF
 END IF
sjl = lcc
END FUNCTION

