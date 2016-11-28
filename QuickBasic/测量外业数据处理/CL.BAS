DECLARE FUNCTION GETSS# ()
DECLARE FUNCTION RAD# (A AS DOUBLE)
DECLARE SUB OUTSHV (SD#, HA#, VA#, HT#, CD$)
DIM SHARED COL$
DIM SHARED NOFOR$            '点号输出格式
DIM SHARED SXFOR$            '测站坐标输出格式
DIM SHARED SYFOR$
DIM SHARED SGFOR$
DIM SHARED XFOR$             '实测坐标输出格式
DIM SHARED YFOR$
DIM SHARED ZFOR$             '测得高程输出格式
DIM SHARED HFOR$             '所需高程输出格式
DIM SHARED HTFOR$            '棱镜高的输出格式
DIM SHARED ANGFOR$           '角度的输出格式
DIM SHARED SJFOR$            '视距的输出格式
DIM SHARED SDFOR$            '斜距的输出格式
DIM SHARED NO AS INTEGER
DIM SHARED SX AS DOUBLE
DIM SHARED SY AS DOUBLE
DIM SHARED SG AS DOUBLE
DIM SHARED XMIN AS DOUBLE
DIM SHARED YMIN AS DOUBLE
DIM SHARED XMAX AS DOUBLE
DIM SHARED YMAX AS DOUBLE
DIM SHARED MINX AS DOUBLE
DIM SHARED MINY AS DOUBLE
DIM SHARED MAXX AS DOUBLE
DIM SHARED MAXY AS DOUBLE
COL$ = SPACE$(2)
NOFOR$ = "###"
SXFOR$ = "#####.###"
SYFOR$ = "####.###"
SGFOR$ = "###.###"
XFOR$ = "#####.##"
YFOR$ = "####.##"
ZFOR$ = "###.###"
HFOR$ = "###.##"
HTFOR$ = "##.###"
ANGFOR$ = "###.####"
SJFOR$ = "###.#"
SDFOR$ = "####.###"
SSFOR$ = "#.##"
SCREEN 0
DO
FG% = 0
CLS : LOCATE 9, 25: COLOR 12: PRINT "测 量 外 业 数 据 处 理"
COLOR 2: LOCATE 11, 30: PRINT "1.测    图"
LOCATE 12, 30: PRINT "2.水下地形"
COLOR 14: LOCATE 14, 28: INPUT "请选择(0--退出)"; C$
SELECT CASE C$
 CASE "0"
  CLS : SYSTEM
 CASE "1"                    '测图
  FG% = -1
  DO
  SING% = -1
  CLS : LOCATE 9, 25: COLOR 12: PRINT "测  图  数  据  处  理"
  COLOR 2: LOCATE 13, 30: PRINT "1.PC-E500"
  LOCATE 14, 30: PRINT "2.DTM-450"
  COLOR 14: LOCATE 11, 27: INPUT "请选择数据记录器"; CC$
  SELECT CASE CC$
   CASE "1"                  '数据记录器为PC-E500
    SING% = 0
    OPEN "E:\YHF\COM\CL.DAT" FOR INPUT AS 1
    OPEN "E:\YHF\COM\CT.PRN" FOR OUTPUT AS 2
    XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
    MINX = 1E+10: MINY = MINX: MAXX = -MINX: MAXY = -MINX
    FLAG% = 0: STN% = 0
    WHILE NOT EOF(1)
     LINE INPUT #1, DATA$
     K = INSTR(DATA$, ",")
     IF K <> 0 THEN
      CD$ = MID$(DATA$, 1, K - 1)
      DATA$ = MID$(DATA$, K + 1)
      SELECT CASE MID$(DATA$, 1, 1)
       CASE "T"
        IF FLAG% = 0 THEN
         FLAG% = 2
         PRINT #2, " 点号   X         Y        Z        ΔL      H    说明"
         PRINT " 点号   X         Y        Z        ΔL      H    说明"
         NO = 1
        END IF
        X# = VAL(MID$(DATA$, 2, 9)) * .001
        Y# = VAL(MID$(DATA$, 11, 9)) * .001
        Z# = VAL(MID$(DATA$, 20, 9)) * .001
        HT# = VAL(MID$(DATA$, 30))
        PRINT #2, USING NOFOR$; NO; : PRINT #2, COL$;
        PRINT #2, USING XFOR$; X#; : PRINT #2, COL$;
        PRINT #2, USING YFOR$; Y#; : PRINT #2, COL$;
        PRINT #2, USING ZFOR$; Z#; : PRINT #2, COL$;
        PRINT #2, USING HTFOR$; HT#; : PRINT #2, COL$;
        PRINT #2, USING HFOR$; Z# - HT#; : PRINT #2, COL$; CD$
        PRINT USING NOFOR$; NO; : PRINT COL$; : NO = NO + 1
        PRINT USING XFOR$; X#; : PRINT COL$;
        PRINT USING YFOR$; Y#; : PRINT COL$;
        PRINT USING ZFOR$; Z#; : PRINT COL$;
        PRINT USING HTFOR$; HT#; : PRINT COL$;
        PRINT USING HFOR$; Z# - HT#; : PRINT COL$; CD$
        IF X# < XMIN THEN XMIN = X#
        IF Y# < YMIN THEN YMIN = Y#
        IF X# > XMAX THEN XMAX = X#
        IF Y# > YMAX THEN YMAX = Y#
       CASE "t"
        IF MID$(DATA$, 1, 2) = "tz" THEN       '测站坐标
         IF FLAG% = 2 THEN
          PRINT #2, "该测站所测数据中"
          PRINT #2, "最小X:  "; : PRINT #2, USING XFOR$; XMIN;
          PRINT #2, "         最小Y:  "; : PRINT #2, USING YFOR$; YMIN
          PRINT #2, "最大X:  "; : PRINT #2, USING XFOR$; XMAX;
          PRINT #2, "         最大Y:  "; : PRINT #2, USING YFOR$; YMAX
          PRINT #2,
          IF MINX > XMIN THEN MINX = XMIN
          IF MINY > YMIN THEN MINY = YMIN
          IF MAXX < XMAX THEN MAXX = XMAX
          IF MAXY < YMAX THEN MAXY = YMAX
          XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
         END IF
         FLAG% = 1
         K = INSTR(DATA$, ",")
         SX = VAL(MID$(DATA$, 3, K - 3))
         DATA$ = MID$(DATA$, K + 1)
         K = INSTR(DATA$, ",")
         SY = VAL(MID$(DATA$, 1, K - 1))
         SG = VAL(MID$(DATA$, K + 1))
        ELSEIF MID$(DATA$, 1, 2) = "t2" THEN
         IF FLAG% = 0 THEN
          PRINT "错误:无测站坐标": SYSTEM
         ELSE
          IF FLAG% = 1 THEN
           PRINT #2, "测站坐标(X,Y,SG):  "; : PRINT #2, USING SXFOR$; SX;
           PRINT #2, " , "; : PRINT #2, USING SYFOR$; SY;
           PRINT #2, " , "; : PRINT #2, USING SGFOR$; SG
           PRINT "测站坐标(X,Y,SG):  "; : PRINT USING SXFOR$; SX;
           PRINT " , "; : PRINT USING SYFOR$; SY;
           PRINT " , "; : PRINT USING SGFOR$; SG
           PRINT #2, "点号  视距    中丝     方位角    立角       X         Y        H   说明"
           PRINT "点号  视距    中丝     方位角    立角       X         Y        H   说明"
           FLAG% = 2: STN% = STN% + 1: NO = 1
          END IF
         END IF
         S# = VAL(MID$(DATA$, 3, 4)) * .1
         HA# = VAL(MID$(DATA$, 7, 7)) * .0001
         VA# = VAL(MID$(DATA$, 14, 7)) * .0001
         HT# = VAL(MID$(DATA$, 21)) * .001
         PRINT #2, USING NOFOR$; NO; : PRINT #2, COL$;
         PRINT #2, USING SJFOR$; S#; : PRINT #2, COL$;
         PRINT #2, USING HTFOR$; HT#; : PRINT #2, COL$;
         PRINT #2, USING ANGFOR$; HA#; : PRINT #2, COL$;
         PRINT #2, USING ANGFOR$; VA#; : PRINT #2, COL$;
         PRINT USING NOFOR$; NO; : PRINT COL$; : NO = NO + 1
         PRINT USING SJFOR$; S#; : PRINT COL$;
         PRINT USING HTFOR$; HT#; : PRINT COL$;
         PRINT USING ANGFOR$; HA#; : PRINT COL$;
         PRINT USING ANGFOR$; VA#; : PRINT COL$;
         HA# = RAD(HA#): VA# = RAD(VA#)
         IF VA# > 3.14159265# THEN VA# = -VA#
         HD# = S# * (SIN(VA#)) ^ 2
         X# = SX + HD# * COS(HA#)
         Y# = SY + HD# * SIN(HA#)
         Z# = SG + HD# * TAN(1.570796326794897# - VA#) - HT#
         PRINT #2, USING XFOR$; X#; : PRINT #2, COL$;
         PRINT #2, USING YFOR$; Y#; : PRINT #2, COL$;
         PRINT #2, USING HFOR$; Z#; : PRINT #2, COL$; CD$
         PRINT USING XFOR$; X#; : PRINT COL$;
         PRINT USING YFOR$; Y#; : PRINT COL$;
         PRINT USING HFOR$; Z#; : PRINT COL$; CD$
         IF XMIN > X# THEN XMIN = X#
         IF YMIN > Y# THEN YMIN = Y#
         IF XMAX < X# THEN XMAX = X#
         IF YMAX < Y# THEN YMAX = Y#
        ELSE
         IF FLAG% = 0 THEN
          PRINT "错误:无测站坐标": SYSTEM
         ELSE
          IF FLAG% = 1 THEN
           PRINT #2, "测站坐标(X,Y,SG):  "; : PRINT #2, USING SXFOR$; SX;
           PRINT #2, " , "; : PRINT #2, USING SYFOR$; SY;
           PRINT #2, " , "; : PRINT #2, USING SGFOR$; SG
           PRINT "测站坐标(X,Y,SG):  "; : PRINT USING SXFOR$; SX;
           PRINT " , "; : PRINT USING SYFOR$; SY;
           PRINT " , "; : PRINT USING SGFOR$; SG
           PRINT #2, "点号   斜距      方位角     立角    棱镜高     X         Y        H   说明"
           PRINT "点号   斜距      方位角     立角    棱镜高     X         Y        H   说明"
           FLAG% = 2: STN% = STN% + 1: NO = 1
          END IF
         END IF
         SD# = VAL(MID$(DATA$, 3, 7)) * .001
         HA# = VAL(MID$(DATA$, 10, 7)) * .0001
         VA# = VAL(MID$(DATA$, 17, 7)) * .0001
         HT# = VAL(MID$(DATA$, 24))
         CALL OUTSHV(SD#, HA#, VA#, HT#, CD$)
        END IF
      END SELECT
     END IF
    WEND
   CASE "2"
    SING% = 0
    OPEN "E:\YHF\COM\DTM.DAT" FOR INPUT AS 1
    OPEN "E:\YHF\COM\CT.PRN" FOR OUTPUT AS 2
    PRINT #2, "仪器:Nikon DTM-450 编号:111496"
    FLAG% = 0: STN% = 0
    XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
    MINX = 1E+10: MINY = MINX: MAXX = -MINX: MAXY = -MINX
    WHILE NOT EOF(1)
     INPUT #1, DATA$
     IF DATA$ = "0" THEN
      IF FLAG% = 2 THEN
       PRINT #2, "该测站所测数据中"
       PRINT #2, "最小X:  "; : PRINT #2, USING XFOR$; XMIN;
       PRINT #2, "         最小Y:  "; : PRINT #2, USING YFOR$; YMIN
       PRINT #2, "最大X:  "; : PRINT #2, USING XFOR$; XMAX;
       PRINT #2, "         最大Y:  "; : PRINT #2, USING YFOR$; YMAX
       PRINT #2,
       IF MINX > XMIN THEN MINX = XMIN
       IF MINY > YMIN THEN MINY = YMIN
       IF MAXX < XMAX THEN MAXX = XMAX
       IF MAXY < YMAX THEN MAXY = YMAX
       XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
      END IF
      FLAG% = 1: INPUT #1, SX, SY, SG
     ELSE
      IF FLAG% = 0 THEN
       PRINT "错误:测图前未设站": SYSTEM
      ELSE
       IF FLAG% = 1 THEN
        PRINT #2, "测站坐标(X,Y,SG):  "; : PRINT #2, USING SXFOR$; SX;
        PRINT #2, " , "; : PRINT #2, USING SYFOR$; SY;
        PRINT #2, " , "; : PRINT #2, USING SGFOR$; SG
        PRINT "测站坐标(X,Y,SG):  "; : PRINT USING SXFOR$; SX;
        PRINT " , "; : PRINT USING SYFOR$; SY;
        PRINT " , "; : PRINT USING SGFOR$; SG
        PRINT #2, "点号   斜距      方位角     立角    棱镜高     X         Y        H   说明"
        PRINT "点号   斜距      方位角     立角    棱镜高     X         Y        H   说明"
        FLAG% = 2: STN% = STN% + 1: NO = 1
       END IF
       INPUT #1, CD$, SD#, HA#, VA#, HT#
       CALL OUTSHV(SD#, HA#, VA#, HT#, CD$)
      END IF
     END IF
    WEND
   END SELECT
   IF FLAG% = 2 THEN
    PRINT #2, "该测站所测数据中"
    PRINT #2, "最小X:  "; : PRINT #2, USING XFOR$; XMIN;
    PRINT #2, "         最小Y:  "; : PRINT #2, USING YFOR$; YMIN
    PRINT #2, "最大X:  "; : PRINT #2, USING XFOR$; XMAX;
    PRINT #2, "         最大Y:  "; : PRINT #2, USING YFOR$; YMAX
    PRINT #2,
    IF MINX > XMIN THEN MINX = XMIN
    IF MINY > YMIN THEN MINY = YMIN
    IF MAXX < XMAX THEN MAXX = XMAX
    IF MAXY < YMAX THEN MAXY = YMAX
    XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
   END IF
   IF STN% > 1 THEN
    PRINT #2, "所有数据中"
    PRINT #2, "最小X:  "; : PRINT #2, USING XFOR$; MINX;
    PRINT #2, "         最小Y:  "; : PRINT #2, USING YFOR$; MINY
    PRINT #2, "最大X:  "; : PRINT #2, USING XFOR$; MAXX;
    PRINT #2, "         最大Y:  "; : PRINT #2, USING YFOR$; MAXY
   END IF
   CLOSE
   LOOP WHILE SING%
  CASE "2"                    '水下地形
   FG% = -1
   OPEN "E:\YHF\COM\CL.DAT" FOR INPUT AS 1
   OPEN "E:\YHF\COM\DTM.DAT" FOR INPUT AS 2
   OPEN "E:\YHF\COM\SX.DAT" FOR INPUT AS 4
   OPEN "E:\YHF\COM\SX.PRN" FOR OUTPUT AS 3
   HW# = GETSS#
   PRINT #3, "仪器A:Topcon GTS-301D 编号 GU1169"
   PRINT #3, "仪器B:Nikon DTM-450   编号 111496"
   PRINT #3, "水面高:";
   PRINT #3, USING ZFOR$; HW#
   FGA% = 0: FGB% = 0
   XMIN = 1E+10: YMIN = XMIN: XMAX = -XMIN: YMAX = -XMIN
   DO
    DA% = 0
    DO
     IF EOF(1) THEN
      DA% = -1
     ELSE
      LINE INPUT #1, DATA$
      K = INSTR(DATA$, ",")
      IF K <> 0 THEN
       DATA$ = MID$(DATA$, K + 1)
       IF ASC(DATA$) = 83 THEN
        IF MID$(DATA$, 1, 2) = "Sz" THEN
         FGA% = 1
         K = INSTR(DATA$, ",")
         XA# = VAL(MID$(DATA$, 3, K - 3))
         YA# = VAL(MID$(DATA$, K + 1))
        ELSE
         IF FGA% = 1 THEN
          FGA% = 2
         ELSEIF FGA% = 0 THEN
          PRINT "错误:A无测站坐标": SYSTEM
         ELSE
          FGA% = 3
         END IF
         HA# = VAL(MID$(DATA$, 2)) * .0001
         DA% = 1
         END IF
       END IF
      END IF
     END IF
    LOOP WHILE DA% = 0
    DB% = 0
    DO
     IF EOF(2) THEN
      DB% = -1
     ELSE
      INPUT #2, DATA$
      IF DATA$ = "0" THEN
       FGB% = 1
       INPUT #2, XB#, YB#, SG
      ELSE
       IF FGB% = 1 THEN
        FGB% = 2
       ELSEIF FGB% = 0 THEN
        PRINT "错误:B无测站坐标": SYSTEM
       ELSE
        FGB% = 3
       END IF
      INPUT #2, CD$, SD#, HB#, VA#, HT#
      DB% = 1
      END IF
     END IF
    LOOP WHILE DB% = 0
    IF DA% = 1 AND DB% = 1 THEN
     IF FGA% + FGB% < 6 THEN
      PRINT #3,
      PRINT #3, "A测站坐标(X,Y):  "; : PRINT #3, USING SXFOR$; XA#;
      PRINT #3, " , "; : PRINT #3, USING SYFOR$; YA#
      PRINT #3, "B测站坐标(X,Y):  "; : PRINT #3, USING SXFOR$; XB#;
      PRINT #3, " , "; : PRINT #3, USING SYFOR$; YB#
      PRINT #3, "点号  方位角A   方位角B  水深     X        Y         H"
      PRINT "A测站坐标(X,Y):  "; : PRINT USING SXFOR$; XA#;
      PRINT " , "; : PRINT USING SYFOR$; YA#
      PRINT "B测站坐标(X,Y):  "; : PRINT USING SXFOR$; XB#;
      PRINT " , "; : PRINT USING SYFOR$; YB#
      PRINT "点号  方位角A   方位角B  水深     X        Y         H"
      NO = 1
     END IF
     SS# = GETSS#
     PRINT #3, USING NOFOR$; NO; : PRINT #3, COL$;
     PRINT #3, USING ANGFOR$; HA#; : PRINT #3, COL$;
     PRINT #3, USING ANGFOR$; HB#; : PRINT #3, COL$;
     PRINT #3, USING SSFOR$; SS#; : PRINT #3, COL$;
     PRINT USING NOFOR$; NO; : PRINT COL$;
     PRINT USING ANGFOR$; HA#; : PRINT COL$;
     PRINT USING ANGFOR$; HB#; : PRINT COL$;
     PRINT USING SSFOR$; SS#; : PRINT COL$;
     HA# = RAD(HA#): HB# = RAD(HB#)
     SA# = ((YB# - YA#) * COS(HB#) - (XB# - XA#) * SIN(HB#)) / SIN(HA# - HB#)
     X# = XA# + SA# * COS(HA#): Y# = YA# + SA# * SIN(HA#): H# = HW# - SS#
     PRINT #3, USING XFOR$; X#; : PRINT #3, COL$;
     PRINT #3, USING YFOR$; Y#; : PRINT #3, COL$;
     PRINT #3, USING HFOR$; H#
     PRINT USING XFOR$; X#; : PRINT COL$;
     PRINT USING YFOR$; Y#; : PRINT COL$;
     PRINT USING HFOR$; H#
     IF XMIN > X# THEN XMIN = X#
     IF YMIN > Y# THEN YMIN = Y#
     IF XMAX < X# THEN XMAX = X#
     IF YMAX < Y# THEN YMAX = Y#
     NO = NO + 1
    END IF
   LOOP UNTIL DA% = -1 OR DB% = -1
   IF FGA% <> 0 THEN
    PRINT #3,
    PRINT #3, "最小X:  "; : PRINT #3, USING XFOR$; XMIN;
    PRINT #3, "         最小Y:  "; : PRINT #3, USING YFOR$; YMIN
    PRINT #3, "最大X:  "; : PRINT #3, USING XFOR$; XMAX;
    PRINT #3, "         最大Y:  "; : PRINT #3, USING YFOR$; YMAX
   END IF
   CLOSE
 END SELECT
IF FG% THEN
 COLOR 13: PRINT
 PRINT "   按 任 意 键 返 回 主 菜 单"
 DO
 LOOP WHILE INKEY$ = ""
END IF
LOOP

FUNCTION GETSS#
FG% = 0
DO
 IF EOF(4) THEN
  COLOR 12: PRINT "错误:水深数据不够(文件SX.DAT中)": SYSTEM
 ELSE
  LINE INPUT #4, DATA$
  DATA$ = LTRIM$(DATA$): DATA$ = RTRIM$(DATA$)
  IF DATA$ <> "" THEN
   FG% = 1
   GETSS# = VAL(DATA$)
  END IF
 END IF
LOOP WHILE FG% = 0
END FUNCTION

SUB OUTSHV (SD#, HA#, VA#, HT#, CD$)
PRINT #2, USING NOFOR$; NO; : PRINT #2, COL$;
PRINT #2, USING SDFOR$; SD#; : PRINT #2, COL$;
PRINT #2, USING ANGFOR$; HA#; : PRINT #2, COL$;
PRINT #2, USING ANGFOR$; VA#; : PRINT #2, COL$;
PRINT #2, USING HTFOR$; HT#; : PRINT #2, COL$;
PRINT USING NOFOR$; NO; : PRINT COL$; : NO = NO + 1
PRINT USING SDFOR$; SD#; : PRINT COL$;
PRINT USING ANGFOR$; HA#; : PRINT COL$;
PRINT USING ANGFOR$; VA#; : PRINT COL$;
PRINT USING HTFOR$; HT#; : PRINT COL$;
HA# = RAD(HA#): VA# = RAD(VA#)
HD# = SD# * ABS(SIN(VA#))
X# = SX + HD# * COS(HA#)
Y# = SY + HD# * SIN(HA#)
H# = SG + SD# * COS(VA#) - HT#
PRINT #2, USING XFOR$; X#; : PRINT #2, COL$;
PRINT #2, USING YFOR$; Y#; : PRINT #2, COL$;
PRINT #2, USING HFOR$; H#; : PRINT #2, COL$; CD$
PRINT USING XFOR$; X#; : PRINT COL$;
PRINT USING YFOR$; Y#; : PRINT COL$;
PRINT USING HFOR$; H#; : PRINT COL$; CD$
IF XMIN > X# THEN XMIN = X#
IF YMIN > Y# THEN YMIN = Y#
IF XMAX < X# THEN XMAX = X#
IF YMAX < Y# THEN YMAX = Y#
END SUB

FUNCTION RAD# (A AS DOUBLE)
S# = ABS(A): D# = INT(S# + .1)
S# = 100# * (S# - D#): M# = INT(S# + .1)
S# = 100# * (S# - M#): S# = INT(S# + .5)
RAD# = SGN(A) * .0174532925199433# * ((S# / 60# + M#) / 60# + D#)
END FUNCTION

