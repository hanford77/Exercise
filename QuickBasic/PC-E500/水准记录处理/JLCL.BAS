'将 PC--E500 记录的一等水准测量数据(数据文件中)处理至指定文件
DECLARE FUNCTION CEIL$ (XY AS DOUBLE, N AS INTEGER)
DECLARE FUNCTION NM$ (A$)
DECLARE FUNCTION FIND$ (A$)
DIM DD AS DOUBLE
DIM ED AS DOUBLE
DIM HH AS DOUBLE
XLS = 10
DIM L1(255), L2(255), L3(255), L4(255), L5(255), L6(255), L7(255), L8(255), D$(255)
DIM P$(XLS), B$(XLS), X$(XLS), M(XLS), T$(XLS, 1), Z$(XLS)
I = 1: K = 0: Z$(1) = CHR$(0): B = 0
INPUT "请输入数据文件名:", DN$
X = CSRLIN
DN$ = FIND$(DN$)
IF DN$ = "" THEN LOCATE X, 1: PRINT "没有发现该文件!": SYSTEM
L1:
PRINT "是文件 "; DN$;
INPUT " 吗?(Y/N)", A$
A$ = UCASE$(A$)
IF A$ = "N" THEN SYSTEM
IF A$ <> "Y" THEN GOTO L1
NAME$ = DN$ + "X"
OPEN DN$ FOR INPUT AS 2
WHILE NOT EOF(2)
 INPUT #2, A$
 B$ = RIGHT$(A$, 2)
 IF B$ = "'S" THEN
  B = -1
  K = K + 1
  INPUT #2, Q$, R$, G$, J$, X$(K), T$(K, 0), T$(K, 1), B$(K)
 ELSEIF B$ = "'C" THEN
  INPUT #2, A$
  IF B THEN
   B = 0
   M(K) = 1
   P$(K) = A$
   IF K > 1 THEN
    Z$(K) = RIGHT$(Z$(K - 1), 1)
   END IF
  ELSE
   M(K) = M(K) + 1
   Z$(K) = Z$(K) + CHR$(I - 1)
   D$(I - 1) = A$
  END IF
 ELSE
  INPUT #2, L1(I), L2(I), L3(I), L4(I), L5(I), L6(I), L7(I), L8(I)
  I = I + 1
 END IF
WEND
CLOSE
IF K < 1 THEN SYSTEM
G$ = NM$(G$)
J$ = NM$(J$)
SELECT CASE Q$
 CASE "QING"
  Q$ = "晴"
 CASE "YIN"
  Q$ = "阴"
 CASE "YU"
  Q$ = "雨"
END SELECT
OPEN NAME$ FOR OUTPUT AS 1
FOR T = 1 TO K
 IF B$(T) = "W" THEN
  A$ = "往 测"
  S = 1
 ELSE
  A$ = "返 测"
  S = -1
 END IF
 PRINT "                       一 等 水 准 记 录"
 PRINT
 PRINT "       天 气  :  "; Q$; SPACE$(25 - LEN(Q$)); "日 期  :  "; R$
 PRINT "       温 度  :  "; X$(T); "℃"; SPACE$(23 - LEN(X$(T))); "时 间  :  "; T$(T, 0); "--"; T$(T, 1)
 PRINT "       观 测  :  "; G$; SPACE$(25 - LEN(G$)); "记 录  :  "; J$
 PRINT "       测 向  :  "; A$
 PRINT
 PRINT "    ----------------------------------------------------------------"
 PRINT
 PRINT #1, "                       一 等 水 准 记 录"
 PRINT #1,
 PRINT #1, "       天 气  :  "; Q$; SPACE$(25 - LEN(Q$)); "日 期  :  "; R$
 PRINT #1, "       温 度  :  "; X$(T); "℃"; SPACE$(23 - LEN(X$(T))); "时 间  :  "; T$(T, 0); "--"; T$(T, 1)
 PRINT #1, "       观 测  :  "; G$; SPACE$(25 - LEN(G$)); "记 录  :  "; J$
 PRINT #1, "       测 向  :  "; A$
 PRINT #1,
 PRINT #1, "    ----------------------------------------------------------------"
 PRINT #1,
 P = ASC(Z$(T))
 FOR X = 1 TO M(T) - 1
  M = ASC(MID$(Z$(T), X, 1)) + 1
  N = ASC(MID$(Z$(T), X + 1, 1))
  IF X = 1 THEN
   PRINT "                      "; P$(T); "----------------"; D$(ASC(MID$(Z$(T), 2, 1)))
   PRINT #1, "                      "; P$(T); "----------------"; D$(ASC(MID$(Z$(T), 2, 1)))
  ELSE
   PRINT "                      "; D$(M - 1); "----------------"; D$(N)
   PRINT #1, "                      "; D$(M - 1); "----------------"; D$(N)
  END IF
   PRINT
   PRINT #1,
   ED = 0
   DD = 0
   HH = 0
   FOR J = M TO N
    PRINT "   ";
    PRINT USING "####"; J - P;
    PRINT USING "#######"; L1(J); L2(J); L3(J); L4(J); L5(J); L6(J); L7(J); L8(J)
    PRINT #1, "   ";
    PRINT #1, USING "####"; J - P;
    PRINT #1, USING "#######"; L1(J); L2(J); L3(J); L4(J); L5(J); L6(J); L7(J); L8(J)
    AD = S * (L1(J) - L2(J) - L5(J) + L6(J)) / 20
    ED = ED + AD
    D = (L1(J) - L2(J) + L5(J) - L6(J)) / 20
    DD = D + DD
    H = S * (L3(J) - L4(J) - L7(J) + L8(J)) / 40
    HH = H + HH
    PRINT "          D= ";
    PRINT USING "##.##"; D;
    PRINT "m        H=";
    PRINT USING "#####.###"; H;
    PRINT "mm     d=";
    PRINT USING "##.##"; AD;
    PRINT "m"
    PRINT #1, "          D= ";
    PRINT #1, USING "##.##"; D;
    PRINT #1, "m        H=";
    PRINT #1, USING "#####.###"; H;
    PRINT #1, "mm     d=";
    PRINT #1, USING "##.##"; AD;
    PRINT #1, "m"
    S = -S
   NEXT
  PRINT
  U = ASC(MID$(Z$(T), X + 1, 1)) - ASC(MID$(Z$(T), X, 1))
  DDS$ = CEIL$(DD, 2): EDS$ = CEIL$(ED, 2): HHS$ = CEIL$(HH, 3)
  PRINT "      N=";
  PRINT USING "##"; U;
  PRINT "       [D]="; DDS$; "m       [d]="; EDS$; "m        [H]="; HHS$; "mm"
  PRINT
  PRINT #1,
  PRINT #1, "      N=";
  PRINT #1, USING "##"; U;
  PRINT #1, "       [D]="; DDS$; "m       [d]="; EDS$; "m        [H]="; HHS$; "mm"
  PRINT #1,
 NEXT
 PRINT "    ----------------------------------------------------------------"
 PRINT
 PRINT #1, "    ----------------------------------------------------------------"
 PRINT #1,
NEXT
PRINT "结果存放在文件 "; NAME$
SYSTEM

FUNCTION CEIL$ (XY AS DOUBLE, N AS INTEGER)
X# = XY: S$ = " "
IF X# < 0 THEN
S$ = "-": X# = -X#
END IF
IF ABS(X#) < 1 THEN
 A$ = STR$(1.0005# + X#)
 CEIL$ = S$ + "0." + MID$(A$, 4, N)
ELSE
 A$ = STR$(.0005# + X#)
 K = INSTR(A$, ".")
 CEIL$ = S$ + MID$(A$, 2, K - 1) + MID$(A$, K + 1, N)
END IF
END FUNCTION

FUNCTION FIND$ (A$)
SHELL ("DIR " + A$ + "/S>TMP")
OPEN "TMP" FOR INPUT AS 10
FOR I = 1 TO 5
 LINE INPUT #10, PATH$
NEXT
LINE INPUT #10, T$
IF NOT EOF(10) THEN
 PATH$ = MID$(PATH$, 14)
 T$ = UCASE$(A$)
 IF MID$(T$, 2, 1) = ":" THEN T$ = MID$(T$, 3)
 DO
  P = INSTR(T$, "\")
  IF P THEN T$ = MID$(T$, P + 1)
 LOOP UNTIL P = 0
 P = INSTR(T$, ".")
 IF P <> 0 AND LEN(T$) - P < 3 THEN FIND$ = PATH$ + "\" + T$
END IF
CLOSE 10
KILL "TMP"
END FUNCTION

FUNCTION NM$ (A$)
NM$ = A$
SELECT CASE A$
 CASE "CXY"
  NM$ = "陈向阳"
 CASE "ZHS"
  NM$ = "张洪升"
 CASE "YHF"
  NM$ = "殷海峰"
 CASE "LH"
  NM$ = "罗  华"
 CASE "ZZL"
  NM$ = "张子灵"
END SELECT
END FUNCTION

