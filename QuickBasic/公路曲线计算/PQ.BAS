DECLARE FUNCTION e500dms$ (a#)
DECLARE FUNCTION dms$ (rad#)
DECLARE FUNCTION ATN2# (x AS DOUBLE, y AS DOUBLE)
OPTION BASE 1
lc0# = 0
TYPE pt
 x AS DOUBLE
 y AS DOUBLE
 lc AS DOUBLE
END TYPE
OPEN "in.txt" FOR INPUT AS 1
INPUT #1, ds
ds = INT(ds)
IF ds < 3 THEN END
DIM SHARED pi AS DOUBLE
DIM x(ds) AS DOUBLE, y(ds) AS DOUBLE
DIM zy(ds) AS pt, yz(ds) AS pt, qz(ds) AS pt, r(ds) AS DOUBLE
DIM a(ds) AS DOUBLE, da(ds) AS DOUBLE, d(ds) AS DOUBLE
DIM t(ds), l(ds), e(ds)
pi = ATN(1#) * 4#
INPUT #1, x(1), y(1)
FOR i = 2 TO ds - 1
 INPUT #1, x(i), y(i), r(i)
NEXT
INPUT #1, x(ds), y(ds)
CLOSE
FOR i = 2 TO ds
 a(i - 1) = ATN2(x(i) - x(i - 1), y(i) - y(i - 1))
 d(i - 1) = SQR((x(i) - x(i - 1)) ^ 2 + (y(i) - y(i - 1)) ^ 2)
NEXT
FOR i = 2 TO ds - 1
 da(i) = a(i) - a(i - 1)
 da(i) = da(i) - 2 * pi * INT(da(i) / (2 * pi) + .5)
NEXT
FOR i = 2 TO ds - 1
 IF r(i) < 0 THEN
  d(i - 1) = SQR(d(i - 1) ^ 2 - r(i) ^ 2)
  d(i) = SQR(d(i) ^ 2 - r(i) ^ 2)
  a(i - 1) = a(i - 1) + SGN(da(i)) * ATN(r(i) / d(i - 1))
  a(i) = a(i) - SGN(da(i)) * ATN(r(i) / d(i))
  da(i - 1) = a(i - 1) - a(i - 2)
  da(i - 1) = da(i - 1) - 2 * pi * INT(da(i - 1) / (2 * pi) + .5)
  da(i + 1) = a(i + 1) - a(i)
  da(i + 1) = da(i + 1) - 2 * pi * INT(da(i + 1) / (2 * pi) + .5)
  da(i) = a(i) - a(i - 1)
  da(i) = da(i) + 2 * pi * INT(1 - .5 * da(i) / pi)
  IF da(i) < pi THEN da(i) = da(i) - 2 * pi
 END IF
NEXT
yz(1).lc = lc0#
FOR i = 2 TO ds - 1
  a# = ABS(da(i))
  l(i) = ABS(r(i)) * a#
 IF r(i) > 0 THEN
  t(i) = r(i) * TAN(a# / 2#)
  e(i) = r(i) * (1 / COS(a# / 2#) - 1)
 END IF
 zy(i).lc = yz(i - 1).lc - t(i - 1) + d(i - 1) - t(i)
 qz(i).lc = zy(i).lc + .5 * l(i)
 yz(i).lc = zy(i).lc + l(i)
 IF r(i) < 0 THEN
  a# = SGN(da(i)) * pi / 2
  zy(i).x = x(i) - r(i) * COS(a(i - 1) - a#)
  zy(i).y = y(i) - r(i) * SIN(a(i - 1) - a#)
  yz(i).x = x(i) - r(i) * COS(a(i) - a#)
  yz(i).y = y(i) - r(i) * SIN(a(i) - a#)
  qz(i).x = x(i)
  qz(i).y = y(i)
 ELSE
  zy(i).x = x(i) - t(i) * COS(a(i - 1))
  zy(i).y = y(i) - t(i) * SIN(a(i - 1))
  yz(i).x = x(i) + t(i) * COS(a(i))
  yz(i).y = y(i) + t(i) * SIN(a(i))
  a# = a(i - 1) + .5 * SGN(da(i)) * pi
  qz(i).x = zy(i).x + r(i) * COS(a#)
  qz(i).y = zy(i).y + r(i) * SIN(a#)
 END IF
NEXT
OPEN "out.txt" FOR OUTPUT AS 1
PRINT #1, "JD 1:   K"; lc0#;
PRINT #1, USING "#######.###"; x(1); y(1)
PRINT #1, dms$(a(1)); "    ";
PRINT #1, USING "#####.###"; d(1)
PRINT #1,
FOR i = 2 TO ds - 1
 PRINT #1, "JD"; i; ":";
 PRINT #1, USING "#######.###"; x(i); y(i)
 PRINT #1, dms$(a(i)); "    ";
 PRINT #1, USING "#####.###"; d(i)
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
 PRINT #1, USING "#####.###"; zy(i).lc;
 PRINT #1, USING "#######.###"; zy(i).x; zy(i).y
 PRINT #1, "YZ K";
 PRINT #1, USING "#####.###"; yz(i).lc;
 PRINT #1, USING "#######.###"; yz(i).x; yz(i).y
 PRINT #1, "O:";
 PRINT #1, USING "#######.####"; qz(i).x; qz(i).y;
 IF da(i) > 0 THEN
  PRINT #1, USING "######.###"; ABS(r(i));
  PRINT #1, "  Y"
 ELSE
  PRINT #1, USING "######.###"; -ABS(r(i));
  PRINT #1, "  Z"
 END IF
 PRINT #1,
NEXT
PRINT #1, "JD"; ds; ":   K";
PRINT #1, USING "#####.###"; yz(ds - 1).lc - t(ds - 1) + d(ds - 1);
PRINT #1, USING "#######.###"; x(ds); y(ds)
PRINT #1,
PRINT #1, USING "#####.###"; lc0#;
PRINT #1, " Z";
PRINT #1, USING "#######.###"; x(1); y(1);
PRINT #1, "  "; dms$(a(1));
PRINT #1, USING "#####.###"; lc0#
FOR i = 2 TO ds - 1
  PRINT #1, USING "#####.###"; zy(i).lc;
  PRINT #1, " Y";
  PRINT #1, USING "#######.####"; qz(i).x; qz(i).y;
  PRINT #1, "  "; dms$(a(i) - .5 * da(i));
  PRINT #1, USING "#####.###"; qz(i).lc;
  PRINT #1, USING "######.###"; SGN(da(i)) * ABS(r(i));
  PRINT #1, USING "####.###"; .5 * l(i)
  PRINT #1, USING "#####.###"; yz(i).lc;
  PRINT #1, " Z";
  PRINT #1, USING "#######.###"; yz(i).x; yz(i).y;
  PRINT #1, "  "; dms$(a(i));
  PRINT #1, USING "#####.###"; yz(i).lc
NEXT
PRINT #1, USING "#####.###"; yz(ds - 1).lc - t(ds - 1) + d(ds - 1)
GOSUB e500
SYSTEM

e500:
PRINT #1, "*********************"
k = 1000
PRINT #1, k; "*FD:DATA"; STR$(2 * ds - 4)
k = k - 30
FOR i = 2 TO ds - 1
  PRINT #1, k + i * 20; "DATA";
  PRINT #1, USING "#####.###"; zy(i).lc;
  PRINT #1, ",";
  PRINT #1, USING "#######.###"; zy(i).x;
  PRINT #1, ",";
  PRINT #1, USING "#######.###"; zy(i).y;
  PRINT #1, ","; e500dms(a(i - 1)); ",Y"; STR$(i - 1)
  PRINT #1, k + i * 20 + 10; "DATA";
  PRINT #1, USING "#####.###"; yz(i).lc;
  PRINT #1, ",";
  PRINT #1, USING "#######.###"; yz(i).x;
  PRINT #1, ",";
  PRINT #1, USING "#######.###"; yz(i).y;
  PRINT #1, ","; e500dms(a(i)); ",Z"; STR$(i)
NEXT
k = 2000
PRINT #1, k; "*Z:DATA"; STR$(ds - 1)
PRINT #1, k + 10; "DATA";
PRINT #1, USING "#######.###"; zy(2).x;
PRINT #1, ",";
PRINT #1, USING "#######.###"; zy(2).y;
PRINT #1, ","; e500dms(a(1)); ",";
PRINT #1, USING "#####.###"; zy(2).lc
FOR i = 2 TO ds - 1
  PRINT #1, k + i * 10; "DATA";
  PRINT #1, USING "#######.###"; yz(i).x;
  PRINT #1, ",";
  PRINT #1, USING "#######.###"; yz(i).y;
  PRINT #1, ","; e500dms(a(i)); ",";
  PRINT #1, USING "#####.###"; yz(i).lc
NEXT
k = 3000
PRINT #1, k; "*Y:DATA"; STR$(ds - 2)
k = k - 10
FOR i = 2 TO ds - 1
  PRINT #1, k + i * 10; "DATA";
  PRINT #1, USING "#######.####"; qz(i).x;
  PRINT #1, ",";
  PRINT #1, USING "#######.####"; qz(i).y;
  PRINT #1, ","; e500dms(a(i) - .5 * da(i)); ",";
  PRINT #1, USING "#####.###"; qz(i).lc;
  PRINT #1, ",";
  PRINT #1, USING "######.###"; SGN(da(i)) * ABS(r(i))
NEXT
k = 4000
PRINT #1, k; "*H:DATA0"
RETURN

FUNCTION ATN2# (x AS DOUBLE, y AS DOUBLE)
HALFPI# = 1.570796326794897#
IF ABS(x) > ABS(y) THEN
a# = HALFPI# * (1 - SGN(x)) + ATN(y / x)
ELSEIF y <> 0# THEN
a# = HALFPI# * (2 - SGN(y)) - ATN(x / y)
ELSE
a# = 0
END IF
IF a# > 2 * HALFPI# THEN
ATN2# = a# - 4 * HALFPI#
ELSE
ATN2# = a#
END IF
END FUNCTION

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

FUNCTION e500dms$ (a#)
rad# = a# - 2 * pi * INT(.5 * a# / pi)
rad# = rad# * 180# / pi
d = INT(rad#)
rad# = (rad# - d) * 60
m = INT(rad#)
s = (rad# - m) * 60
s = INT(s * 10 + .5#) / 10
IF s = 60 THEN
 s = 0
 m = m + 1
 IF m = 60 THEN
  m = 0
  d = d + 1
  IF d = 360 THEN d = 0
 END IF
END IF
e500dms$ = MID$(STR$(d), 2) + "." + MID$(STR$(m + 100), 3) + MID$(STR$(s * 10 + 1000), 3, 3)
END FUNCTION

