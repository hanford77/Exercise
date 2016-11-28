DECLARE FUNCTION lc$ (l AS DOUBLE)
DECLARE FUNCTION sjl# (bcl$)
DECLARE FUNCTION dms$ (rad#)
OPTION BASE 1
DIM SHARED xl$
lc0# = 0
TYPE pt
 lc AS DOUBLE
 h AS DOUBLE
END TYPE
OPEN "in.txt" FOR INPUT AS 1
INPUT #1, xl$
xl$ = UCASE$(xl$)
INPUT #1, ds
ds = INT(ds)
IF ds < 3 THEN END
DIM SHARED pi AS DOUBLE
DIM lcc(ds) AS DOUBLE, h(ds) AS DOUBLE, l$(ds)
DIM zy(ds) AS pt, yz(ds) AS pt, o(ds) AS pt, r(ds) AS DOUBLE
DIM a(ds) AS DOUBLE, da(ds) AS DOUBLE, d(ds) AS DOUBLE
DIM t(ds), l(ds), e(ds)
pi = ATN(1#) * 4#
INPUT #1, l$(1), h(1)
lcc(1) = sjl(l$(1))
FOR i = 2 TO ds - 1
 INPUT #1, l$(i), h(i), r(i)
 lcc(i) = sjl(l$(i))
NEXT
INPUT #1, l$(ds), h(ds)
lcc(ds) = sjl(l$(ds))
CLOSE
FOR i = 2 TO ds
 a(i - 1) = ATN((h(i) - h(i - 1)) / (lcc(i) - lcc(i - 1)))
 d(i - 1) = SQR((lcc(i) - lcc(i - 1)) ^ 2 + (h(i) - h(i - 1)) ^ 2)
NEXT
yz(1).lc = lc0#
FOR i = 2 TO ds - 1
 da(i) = a(i) - a(i - 1)
 a# = ABS(da(i))
 t(i) = r(i) * TAN(a# / 2#)
 l(i) = r(i) * a#
 e(i) = r(i) * (1 / COS(a# / 2#) - 1)
 zy(i).lc = lcc(i) - t(i) * COS(a(i - 1))
 zy(i).h = h(i) - t(i) * SIN(a(i - 1))
 yz(i).lc = lcc(i) + t(i) * COS(a(i))
 yz(i).h = h(i) + t(i) * SIN(a(i))
 a# = a(i - 1) + .5 * SGN(da(i)) * pi
 o(i).lc = zy(i).lc + r(i) * COS(a#)
 o(i).h = zy(i).h + r(i) * SIN(a#)
NEXT
OPEN "out.txt" FOR OUTPUT AS 1
PRINT #1, "JD 1:  "; lc$(lcc(1));
PRINT #1, USING "#####.###"; h(1);
PRINT #1, USING "####.#####"; TAN(a(1)) * 100;
PRINT #1, "%"
PRINT #1,
FOR i = 2 TO ds - 1
 PRINT #1, "JD"; i; ":  "; lc$(lcc(i));
 PRINT #1, USING "#####.###"; h(i);
 PRINT #1, USING "####.#####"; TAN(a(i)) * 100;
 PRINT #1, "%"
 PRINT #1, "T=";
 PRINT #1, USING "###.###"; t(i);
 PRINT #1, " E=";
 PRINT #1, USING "###.###"; e(i);
 PRINT #1, " L=";
 PRINT #1, USING "####.###"; l(i)
 PRINT #1, "A= ";
 IF da(i) < 0 THEN
  PRINT #1, "-"; dms$(-da(i))
 ELSE
  PRINT #1, dms$(da(i))
 END IF
 PRINT #1, "ZY K";
 PRINT #1, USING "#####.###"; zy(i).lc; zy(i).h
 PRINT #1, "YZ K";
 PRINT #1, USING "#####.###"; yz(i).lc; yz(i).h
 PRINT #1, "O: K";
 PRINT #1, USING "#####.####"; o(i).lc; o(i).h;
 IF da(i) > 0 THEN
  PRINT #1, USING "######.###"; r(i);
  PRINT #1, "  S"
 ELSE
  PRINT #1, USING "######.###"; -r(i);
  PRINT #1, "  X"
 END IF
 PRINT #1,
NEXT
PRINT #1, "JD"; ds; ":   "; lc$(lcc(ds))
PRINT #1, USING "#####.###"; lcc(ds); h(ds)
PRINT #1,
PRINT #1, USING "#####.###"; lc0#;
PRINT #1, " Z";
PRINT #1, USING "#######.###"; lcc(1); h(1);
PRINT #1, USING "####.#####"; TAN(a(1)) * 100;
PRINT #1, "%"
FOR i = 2 TO ds - 1
  PRINT #1, USING "#####.###"; zy(i).lc;
  PRINT #1, " Y";
  PRINT #1, USING "######.####"; o(i).lc; o(i).h;
  PRINT #1, USING "######.###"; SGN(da(i)) * r(i)
  PRINT #1, USING "#####.###"; yz(i).lc;
  PRINT #1, " Z";
  PRINT #1, USING "#######.###"; yz(i).lc; yz(i).h;
  PRINT #1, USING "####.#####"; TAN(a(i)) * 100;
  PRINT #1, "%"
NEXT
PRINT #1, USING "#####.###"; yz(ds - 1).lc - t(ds - 1) + d(ds - 1)
GOSUB E500
SYSTEM

E500:
PRINT #1, "****************************"
k = 5000
PRINT #1, LTRIM$(STR$(k)); "*SQ:DATA"; 2 * ds - 3
PRINT #1, LTRIM$(STR$(k + 10)); "DATA";
PRINT #1, USING "#####.###"; lc0#;
PRINT #1, ",Z,,";
PRINT #1, USING "#######.###"; h(1);
PRINT #1, ",";
PRINT #1, USING "####.########"; TAN(a(1))
k = k - 20
FOR i = 2 TO ds - 1
  PRINT #1, LTRIM$(STR$(k + i * 20)); "DATA";
  PRINT #1, USING "#####.###"; zy(i).lc;
  PRINT #1, ",Y,";
  PRINT #1, USING "######.####"; o(i).lc;
  PRINT #1, ",";
  PRINT #1, USING "######.####"; o(i).h;
  PRINT #1, ",";
  PRINT #1, USING "######.###"; SGN(da(i)) * r(i)
  PRINT #1, LTRIM$(STR$(k + i * 20 + 10)); "DATA";
  PRINT #1, USING "#####.###"; yz(i).lc;
  PRINT #1, ",Z,,";
  PRINT #1, USING "#######.###"; yz(i).h;
  PRINT #1, ",";
  PRINT #1, USING "####.########"; TAN(a(i))
NEXT
RETURN

FUNCTION dms$ (a#)
rad# = a# - 2 * pi * INT(.5 * a# / pi)
rad# = rad# * 180 / pi
d = INT(rad#)
rad# = (rad# - d) * 60
m = INT(rad#)
s = (rad# - m) * 60
s = INT(s * 10 + .5) / 10
IF s = 60 THEN
 s = 0
 m = m + 1
 IF m = 60 THEN
  m = 0
  d = d + 1
  IF d = 360 THEN d = 0
 END IF
END IF
dms$ = MID$(STR$(d), 2) + "-" + MID$(STR$(m + 100), 3) + "-" + MID$(STR$(s + 100.001), 3, 4)
END FUNCTION

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

