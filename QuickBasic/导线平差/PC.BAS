DECLARE SUB WCTY (NO!, E#, F#, M#, A#)
DECLARE SUB MAKEQQ ()
DECLARE SUB MAKELL ()
DECLARE SUB MAKENN ()
DECLARE SUB MAKEUU ()
DECLARE SUB MAKEDX ()
DECLARE SUB MAKEBB ()
DECLARE FUNCTION RAD# (A$)
DECLARE FUNCTION NO! (A$)
DECLARE FUNCTION DMS$ (A AS DOUBLE)
DECLARE FUNCTION ATN2# (X AS DOUBLE, Y AS DOUBLE)
DDXC# = .00001#
OPTION BASE 1
TYPE PNT
 X AS DOUBLE
 Y AS DOUBLE
 ZB AS STRING * 1
END TYPE
TYPE PJ
 A1 AS STRING * 1
 A2 AS STRING * 1
 S AS DOUBLE
 P AS DOUBLE
END TYPE
TYPE SPJ
 A1 AS STRING * 1
 A2 AS STRING * 1
 A3 AS STRING * 1
 J AS DOUBLE
 P AS DOUBLE
END TYPE
DIM SHARED DS. AS INTEGER
DIM SHARED YZDS. AS INTEGER
DIM SHARED WZDS. AS INTEGER
DIM SHARED GCS. AS INTEGER
DIM SHARED JS. AS INTEGER
DIM SHARED BCS. AS INTEGER
OPEN "PC.TXT" FOR INPUT AS 1
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
DS. = VAL(MID$(D$, K))
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
YZDS. = VAL(MID$(D$, K))
DIM SHARED PT(DS.) AS PNT
DIM SHARED CD$(DS.)
FOR I = 1 TO YZDS.
 INPUT #1, CD$(I), PT(I).X, PT(I).Y
 PT(I).ZB = "Y"
NEXT
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
WZDS. = VAL(MID$(D$, K))
IF DS. <> YZDS. + WZDS. THEN
 PRINT "ERROR: DS"
 END
END IF
FOR I = YZDS. + 1 TO DS.
 LINE INPUT #1, D$
 K = INSTR(D$, ",")
 IF K = 0 THEN
  CD$(I) = D$
  PT(I).ZB = "N"
 ELSE
  CD$(I) = LEFT$(D$, K - 1)
  D$ = MID$(D$, K + 1)
  K = INSTR(D$, ",")
  PT(I).X = VAL(LEFT$(D$, K - 1))
  PT(I).Y = VAL(MID$(D$, K + 1))
  PT(I).ZB = "Y"
 END IF
NEXT
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
GCS. = VAL(MID$(D$, K))
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
JS. = VAL(MID$(D$, K))
DIM SHARED JD(JS.) AS SPJ
DIM SHARED PI AS DOUBLE
PI = ATN(1#) * 4#
FOR I = 1 TO JS.
 INPUT #1, D$
 JD(I).A1 = CHR$(NO(D$))
 INPUT #1, D$
 JD(I).A2 = CHR$(NO(D$))
 INPUT #1, D$
 JD(I).A3 = CHR$(NO(D$))
 INPUT #1, D$
 JD(I).J = RAD(D$)
 INPUT #1, T#
 JD(I).P = 1# / (T# * T#)
NEXT
LINE INPUT #1, D$
K = INSTR(D$, ":") + 1
BCS. = VAL(MID$(D$, K))
IF JS. + BCS. <> GCS. THEN
 PRINT "ERROR:GCS"
END IF
DIM SHARED BC(BCS.) AS PJ
FOR I = 1 TO BCS.
 INPUT #1, D$
 BC(I).A1 = CHR$(NO(D$))
 INPUT #1, D$
 BC(I).A2 = CHR$(NO(D$))
 INPUT #1, BC(I).S
 INPUT #1, D$
 K = INSTR(D$, "+")
 IF K <> 0 THEN
  ADD# = VAL(LEFT$(D$, K - 1))
  PPM# = VAL(MID$(D$, K + 1))
 ELSE
  ADD# = VAL(D$)
  PPM# = 0
 END IF
 T# = ADD# + PPM# * BC(I).S * .001#
 BC(I).P = 1# / (T# * T#)
NEXT
DIM SHARED T. AS INTEGER
T. = 2 * WZDS.
DIM SHARED NN(T., T.) AS DOUBLE
DIM SHARED QQ(T., T.) AS DOUBLE
DIM SHARED BB(GCS., T.) AS DOUBLE
DIM SHARED UU(T.) AS DOUBLE
DIM SHARED DX(T.) AS DOUBLE
DIM SHARED LL(GCS.) AS DOUBLE
DIM SHARED ROU AS DOUBLE
DIM SHARED MAXDX AS DOUBLE
DIM SHARED M0 AS DOUBLE
ROU = 648000# / PI
LPS = 1
DO
CLS
PRINT "LPS="; LPS
PRINT
PRINT "V=B*DX+L"
PRINT "N*DX+U=0"
PRINT
IF LPS = 1 THEN CALL MAKEBB
CALL MAKELL
IF LPS = 1 THEN CALL MAKENN
CALL MAKEUU
IF LPS = 1 THEN CALL MAKEQQ
CALL MAKEDX
FOR I = 1 TO WZDS.
 PT(I + YZDS.).X = PT(I + YZDS.).X + DX(2 * I - 1)
 PT(I + YZDS.).Y = PT(I + YZDS.).Y + DX(2 * I)
NEXT
PRINT "MAXDX="; MAXDX
LPS = LPS + 1
LOOP WHILE MAXDX > DDXC#
CLS
PRINT "DDXC="; DDXC#; "m"
PRINT "LPS="; LPS - 1
CALL MAKELL
CALL MAKENN
CALL MAKEQQ
PVV# = 0
FOR I = 1 TO JS.
 PVV# = PVV# + LL(I) * LL(I) * JD(I).P
NEXT
FOR I = 1 TO BCS.
 PVV# = PVV# + LL(I + JS.) * LL(I + JS.) * BC(I).P
NEXT
M0 = SQR(PVV# / (GCS. - T.))
CLOSE
OPEN "JG.TXT" FOR OUTPUT AS 1
PRINT #1, "观测数:"; GCS.
PRINT #1, "角度观测数:"; JS.
PRINT #1, "边长观测数:"; BCS.
PRINT #1, "*************************"
PRINT #1, "角度观测值改正数"
T# = 0
FOR I = 1 TO JS.
 PRINT #1, CD$(ASC(JD(I).A1)); SPACE$(8 - LEN(CD$(ASC(JD(I).A1))));
 PRINT #1, CD$(ASC(JD(I).A2)); SPACE$(8 - LEN(CD$(ASC(JD(I).A2))));
 PRINT #1, CD$(ASC(JD(I).A3)); SPACE$(8 - LEN(CD$(ASC(JD(I).A3)))); "V=";
 PRINT #1, USING "###.##"; LL(I);
 PRINT #1, "    M=";
 PRINT #1, USING "###.##"; M0 * SQR(1# / JD(I).P)
 IF T# < ABS(LL(I)) THEN
  F = I
  T# = ABS(LL(I))
 END IF
NEXT
PRINT #1, "角度最大改正值为:";
PRINT #1, USING "###.##"; LL(F)
PRINT #1, "*************************"
PRINT #1, "边长观测值改正数"
T# = 0
FOR I = 1 TO BCS.
 PRINT #1, CD$(ASC(BC(I).A1)); SPACE$(8 - LEN(CD$(ASC(BC(I).A1))));
 PRINT #1, CD$(ASC(BC(I).A2)); SPACE$(8 - LEN(CD$(ASC(BC(I).A2)))); "V=";
 PRINT #1, USING "####.#"; LL(I + JS.);
 PRINT #1, "    M=";
 PRINT #1, USING "###.##"; M0 * SQR(1# / BC(I).P)
 IF T# < ABS(LL(I + JS.)) THEN
  F = I + JS.
  T# = ABS(LL(I + JS.))
 END IF
NEXT
PRINT #1, "边长最大改正值为:";
PRINT #1, USING "####.#"; LL(F)
PRINT #1, "*************************"
PRINT #1, "单位权中误差:"; M0
PRINT #1, "*************************"
PRINT #1, "平差坐标"
FOR I = YZDS. + 1 TO DS.
 PRINT #1, CD$(I); SPACE$(10 - LEN(CD$(I)));
 PRINT #1, USING "###########.###"; PT(I).X; PT(I).Y
NEXT
PRINT #1, "*************************"
PRINT #1, "误差椭圆"
FOR I = YZDS. + 1 TO DS.
 CALL WCTY(I, E#, F#, M#, T#)
 PRINT #1, CD$(I); SPACE$(8 - LEN(CD$(I)));
 PRINT #1, USING "#######.##"; E#; F#; M#;
 PRINT #1, "       "; DMS(T#)
NEXT
PRINT "Output in file:JG.TXT"
SYSTEM

FUNCTION ATN2# (X AS DOUBLE, Y AS DOUBLE)
IF ABS(X) > ABS(Y) THEN
 ATN2# = .5# * PI * (1 - SGN(X)) + ATN(Y / X)
ELSEIF Y <> 0# THEN
 ATN2# = .5# * PI# * (2 - SGN(Y)) - ATN(X / Y)
ELSE
 ATN2# = 0
END IF
END FUNCTION

FUNCTION DMS$ (A AS DOUBLE)
 J# = A * 180# / PI
 J# = J# - 360# * INT(J# / 360#)
 D% = INT(J#)
 J# = (J# - D%) * 60#
 M% = INT(J#)
 J# = (J# - M%) * 600#
 S% = INT(J# + .5#)
 IF S% = 600 THEN
  M% = M% + 1
  S% = 0
  IF M% = 60 THEN
   M% = 0
   D% = D% + 1
   IF D% = 360 THEN
    D% = 0
   END IF
  END IF
 END IF
 B$ = STR$(S% + 1000)
 B$ = "    " + STR$(D%) + "-" + MID$(STR$(M% + 100), 3) + "-" + MID$(B$, 3, 2) + "." + RIGHT$(B$, 1)
 DMS$ = RIGHT$(B$, 11)
END FUNCTION

SUB MAKEBB
 PRINT "Making... B"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO JS.
  P1 = ASC(JD(I).A1)
  P2 = ASC(JD(I).A2)
  P3 = ASC(JD(I).A3)
  DX1# = PT(P1).X - PT(P2).X
  DY1# = PT(P1).Y - PT(P2).Y
  D12# = DX1# * DX1# + DY1# * DY1#
  DX2# = PT(P3).X - PT(P2).X
  DY2# = PT(P3).Y - PT(P2).Y
  D23# = DX2# * DX2# + DY2# * DY2#
  DX1# = DX1# * ROU
  DY1# = DY1# * ROU
  DX2# = DX2# * ROU
  DY2# = DY2# * ROU
  IF P1 > YZDS. THEN
   K = 2 * (P1 - YZDS.)
   BB(I, K - 1) = DY1# / D12#
   BB(I, K) = -DX1# / D12#
  END IF
  IF P2 > YZDS. THEN
   K = 2 * (P2 - YZDS.)
   BB(I, K - 1) = -DY1# / D12# + DY2# / D23#
   BB(I, K) = DX1# / D12# - DX2# / D23#
  END IF
  IF P3 > YZDS. THEN
   K = 2 * (P3 - YZDS.)
   BB(I, K - 1) = -DY2# / D23#
   BB(I, K) = DX2# / D23#
  END IF
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * I / GCS.));
 NEXT
 FOR I = 1 TO BCS.
  P1 = ASC(BC(I).A1)
  P2 = ASC(BC(I).A2)
  DX# = PT(P1).X - PT(P2).X
  DY# = PT(P1).Y - PT(P2).Y
  D# = SQR(DX# * DX# + DY# * DY#)
  IF P1 > YZDS. THEN
   K = 2 * (P1 - YZDS.)
   BB(I + JS., K - 1) = 1000# * DX# / D#
   BB(I + JS., K) = 1000# * DY# / D#
  END IF
  IF P2 > YZDS. THEN
   K = 2 * (P2 - YZDS.)
   BB(I + JS., K - 1) = -1000# * DX# / D#
   BB(I + JS., K) = -1000# * DY# / D#
  END IF
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * (I + JS.) / GCS.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

SUB MAKEDX
 MAXDX = 0
 PRINT "Making... DX"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO T.
  T# = 0
  FOR J = 1 TO T.
   T# = T# + QQ(I, J) * UU(J)
  NEXT
  DX(I) = -T#
  IF MAXDX < ABS(T#) THEN MAXDX = T#
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * I / T.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

SUB MAKELL
 PRINT "Making... L"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO JS.
  P1 = ASC(JD(I).A1)
  P2 = ASC(JD(I).A2)
  P3 = ASC(JD(I).A3)
  A1# = ATN2(PT(P1).X - PT(P2).X, PT(P1).Y - PT(P2).Y)
  A2# = ATN2(PT(P3).X - PT(P2).X, PT(P3).Y - PT(P2).Y)
  T# = A2# - A1# - JD(I).J
  T# = T# + 2# * PI * INT((PI - T#) / (2# * PI))
  LL(I) = ROU * T#
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * I / GCS.));
 NEXT
 FOR I = 1 TO BCS.
  P1 = ASC(BC(I).A1)
  P2 = ASC(BC(I).A2)
  DX# = PT(P1).X - PT(P2).X
  DY# = PT(P1).Y - PT(P2).Y
  D# = SQR(DX# * DX# + DY# * DY#)
  LL(I + JS.) = 1000# * (D# - BC(I).S)
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * (I + JS.) / GCS.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

SUB MAKENN
 PRINT "Making... N"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO T.
  FOR J = I TO T.
   T# = 0
   FOR K = 1 TO JS.
    T# = T# + BB(K, I) * BB(K, J) * JD(K).P
   NEXT
   FOR K = 1 TO BCS.
    T# = T# + BB(K + JS., I) * BB(K + JS., J) * BC(K).P
   NEXT
   NN(I, J) = T#
   NN(J, I) = T#
  NEXT
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * I / T.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

SUB MAKEQQ
REDIM QQ(T., T.) AS DOUBLE
 PRINT "Making... Q"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO T.
  QQ(I, I) = 1#
 NEXT
 FOR K = 1 TO T.
  T# = 1# / NN(K, K)
  FOR J = K + 1 TO T.
   NN(K, J) = NN(K, J) * T#
  NEXT
  FOR J = 1 TO T.
   QQ(K, J) = QQ(K, J) * T#
  NEXT
  FOR I = 1 TO K - 1
   T# = -NN(I, K)
   FOR J = K + 1 TO T.
    NN(I, J) = NN(I, J) + T# * NN(K, J)
   NEXT
   FOR J = 1 TO T.
    QQ(I, J) = QQ(I, J) + T# * QQ(K, J)
   NEXT
  NEXT
  FOR I = K + 1 TO T.
   T# = -NN(I, K)
   FOR J = K + 1 TO T.
    NN(I, J) = NN(I, J) + T# * NN(K, J)
   NEXT
   FOR J = 1 TO T.
    QQ(I, J) = QQ(I, J) + T# * QQ(K, J)
   NEXT
  NEXT
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * K / T.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

SUB MAKEUU
 PRINT "Making... U"
 FOR I = 1 TO 7
  PRINT "XXXXXXXXXX";
 NEXT
 FOR I = 1 TO T.
   T# = 0
   FOR K = 1 TO JS.
    T# = T# + BB(K, I) * LL(K) * JD(K).P
   NEXT
   FOR K = 1 TO BCS.
    T# = T# + BB(K + JS., I) * LL(K + JS.) * BC(K).P
   NEXT
   UU(I) = T#
  LOCATE CSRLIN, 1
  PRINT SPACE$(INT(71 * I / T.));
 NEXT
 LOCATE CSRLIN, 1
END SUB

FUNCTION NO (A$)
 FOR I = 1 TO DS.
  IF A$ = CD$(I) THEN
   F = I
   I = DS. + 1
  END IF
 NEXT
 IF F = 0 THEN
  PRINT "ERROR: CODE$  "; A$
  END
 END IF
 NO = F
END FUNCTION

FUNCTION RAD# (A$)
 K = INSTR(A$, ".")
 IF K <> 0 THEN
  B$ = A$ + "00000"
  D$ = LEFT$(B$, K - 1)
  M$ = MID$(B$, K + 1, 2)
  S$ = MID$(B$, K + 3, 3)
 ELSE
  D$ = A$
 END IF
 RAD# = PI * (VAL(D$) + VAL(M$) / 60# + VAL(S$) / 36000) / 180#
END FUNCTION

SUB WCTY (NO, E#, F#, M#, A#)
N = (NO - YZDS.) * 2
QX# = .5# * QQ(N - 1, N - 1)
QY# = .5# * QQ(N, N)
QXY# = QQ(N - 1, N)
K# = SQR((QX# - QY#) ^ 2 + QXY# ^ 2)
E# = M0 * SQR(QX# + QY# + K#) * 1000#
F# = M0 * SQR(QX# + QY# - K#) * 1000#
M# = SQR(E# * E# + F# * F#)
A# = .5# * ATN2(QX# - QY#, QXY#)
END SUB

