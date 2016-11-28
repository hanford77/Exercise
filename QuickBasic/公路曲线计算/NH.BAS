'ÇúÏßÄâºÏy=a0+a1*(x-x0)+a2*(x-x0)^2...
DEFDBL A-Z
DEFINT I-N
CLS
DIM max AS DOUBLE
OPEN "nh.dat" FOR INPUT AS 1
LINE INPUT #1, d$
k = INSTR(d$, "=")
n = VAL(MID$(d$, k + 1))
LINE INPUT #1, d$
k = INSTR(d$, "=")
x0 = VAL(MID$(d$, k + 1))
LINE INPUT #1, d$
k = INSTR(d$, "=")
m = VAL(MID$(d$, k + 1))
DIM x(m) AS DOUBLE, y(m) AS DOUBLE
FOR i = 1 TO m
 INPUT #1, x(i), y(i)
NEXT
CLOSE
DIM dt(2 * n) AS DOUBLE
dt(0) = m
FOR i = 1 TO m
 d = x(i) - x0
 dd = d
 FOR j = 1 TO n + n
  dt(j) = dt(j) + dd
  dd = dd * d
 NEXT
NEXT
DIM nn(n, n) AS DOUBLE, A(n) AS DOUBLE, w(n) AS DOUBLE
FOR i = 0 TO n
 FOR j = 0 TO n
  nn(i, j) = dt(i + j)
 NEXT
NEXT
FOR i = 1 TO m
 w(0) = w(0) + y(i)
NEXT
FOR i = 1 TO m
 d = x(i) - x0
 dd = y(i) * d
 FOR j = 1 TO n
  w(j) = w(j) + dd
  dd = dd * d
 NEXT
NEXT
FOR i = 0 TO n
 max = ABS(nn(i, i))
 l = i
 FOR k = i + 1 TO n
  IF ABS(nn(k, i)) > max THEN
   max = ABS(nn(k, i))
   l = k
  END IF
 NEXT
 IF l <> i THEN
  FOR j = i TO n
   SWAP nn(i, j), nn(l, j)
  NEXT
  SWAP w(i), w(l)
 END IF
 FOR k = i + 1 TO n
  d = -nn(k, i) / nn(i, i)
  FOR j = i + 1 TO n
   nn(k, j) = nn(k, j) + nn(i, j) * d
  NEXT
 w(k) = w(k) + w(i) * d
 NEXT
NEXT
FOR i = n TO 0 STEP -1
 d = w(i)
 FOR j = i + 1 TO n
  d = d - A(j) * nn(i, j)
 NEXT
 A(i) = d / nn(i, i)
NEXT
OPEN "nh.txt" FOR OUTPUT AS 1
FOR i = 0 TO n
 PRINT #1, "a"; i; "=  ";
  IF A(i) < 0 THEN
   PRINT #1, "-";
  ELSE
   PRINT #1, "+";
  END IF
 IF i < 2 THEN
  PRINT #1, USING "######.#######"; ABS(A(i))
 ELSE
  dd = ABS(A(i))
  d = 1# / i
  PRINT #1, USING "######.#######"; dd ^ d
 END IF
NEXT
PRINT #1, "*"
max = 0
FOR i = 1 TO m
 d = x(i) - x0
 dd = 0
 FOR j = n TO 0 STEP -1
  dd = dd * d + A(j)
 NEXT
 d = dd - y(i)
 vv = vv + d * d
 PRINT #1, i;
 PRINT #1, USING "######.###"; d
 IF ABS(d) > max THEN
  max = ABS(d)
  l = i
 END IF
NEXT
PRINT #1, l; "MAX:";
PRINT #1, USING "######.###"; max
PRINT #1, "*"
PRINT #1, USING "######.###"; SQR(vv / m)
PRINT "ok! output in NH.TXT"
SYSTEM

