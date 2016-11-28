DECLARE FUNCTION FIND% (NO AS LONG)
DECLARE FUNCTION TAKE$ (DATA$, N%)
DECLARE SUB OUTLN (OUT$)
DECLARE FUNCTION CHG% (A$)

TYPE XYH
 NO AS LONG
 X AS DOUBLE
 Y AS DOUBLE
 Z AS DOUBLE
END TYPE

DIM SHARED YZD(1 TO 2000) AS XYH
DIM SHARED YZDS
DIM SHARED ACK$
DIM SHARED LNO AS INTEGER
DIM DATE AS STRING

ACK$ = CHR$(6) + ",R,"
ENDCH$ = CHR$(26)
LF$ = CHR$(10)

SCREEN 0
DO
  FLAG% = 0
  CLS : COLOR 13: LOCATE 6, 25: PRINT "IBM PC <===>   DTM-450 数据通讯"
  LOCATE 8, 22: COLOR 14: PRINT "DTM的设置:";
  COLOR 7: PRINT " 波特率:";
  COLOR 13: PRINT "4800";
  COLOR 7: PRINT " 记录格式:";
  COLOR 13: PRINT "SET";
  LOCATE 11, 26: COLOR 2
  PRINT "1. DTM-450 ==> 微机(";
  COLOR 13: PRINT "DTM.DN";
  COLOR 2: PRINT ")"
  LOCATE 13, 26
  PRINT "2. 微机(";
  COLOR 13: PRINT "DTM.UP";
  COLOR 2: PRINT ") ==> DTM-450"
  COLOR 14
  LOCATE 16, 27: INPUT "请选择:(0--退出)"; C$
  COLOR 7
  SELECT CASE C$
    CASE "0"
      FLAG% = -1
      CLS : LOCATE 10, 20
      COLOR 12: PRINT "请等待,正在将DTM.DN中的数据整理至DTM.DAT"
      OPEN "DTM.DN" FOR INPUT AS 1
      OPEN "DTM.TMP" FOR OUTPUT AS 2
      DATE = CHR$(0)
      WHILE NOT EOF(1)
        LINE INPUT #1, LN$
        TY$ = MID$(LN$, 1, 3)
        IF TY$ = "1,1" OR TY$ = "1,4" THEN
          YZDS = YZDS + 1
          YZD(YZDS).NO = VAL(TAKE$(LN$, 4))
          YZD(YZDS).X = VAL(TAKE$(LN$, 6))
          YZD(YZDS).Y = VAL(TAKE$(LN$, 7))
          YZD(YZDS).Z = VAL(TAKE$(LN$, 8))
        ELSEIF MID$(TY$, 1, 2) = "1," THEN
          PRINT #2, LN$
        END IF
        IF MID$(TY$, 1, 2) = "1," THEN DATE = MID$(LN$, LEN(LN$) - 18, 10)
      WEND
      CLOSE
      OPEN "DTM.TMP" FOR INPUT AS 1
      OPEN "DTM.DAT" FOR OUTPUT AS 2
      WHILE NOT EOF(1)
        LINE INPUT #1, LN$
        P2% = INSTR(LN$, DATE)
        IF P2% <> 0 THEN
          TY$ = MID$(LN$, 1, 3)
          IF TY$ = "1,0" THEN
            SG# = VAL(TAKE$(LN$, 6))
            FD% = FIND(VAL(TAKE$(LN$, 4)))
            SX# = YZD(FD%).X
            SY# = YZD(FD%).Y
            SG# = SG# + YZD(FD%).Z
            PRINT #2, "0,"; SX#; ","; SY#; ","; SG#
          END IF
          IF TY$ = "1,2" THEN
            P1% = INSTR(8, LN$, ",") + 1
            PRINT #2, "2,"; MID$(LN$, P1%, P2% - P1% - 1)
          END IF
        END IF
      WEND
      CLOSE
      KILL "DTM.TMP"
      CLS : SYSTEM
    CASE "1"
      FLAG% = -1
      CLS : COLOR 13
      LOCATE 7, 20: PRINT "*********** DTM-450 ==> 微机 ***********"
      LOCATE 10, 34: COLOR 7: PRINT "联结通讯线"
      LOCATE 12, 27: PRINT "在";
      COLOR 14: PRINT "DTM-450";
      COLOR 7: PRINT "上选择";
      COLOR 13: PRINT "Download";
      COLOR 7: PRINT "项"
      OPEN "COM2:4800,N,8,1,DS,RS" FOR INPUT AS 1
      OPEN "E:\YHF\COM\DTM.DN" FOR OUTPUT AS 2
      COLOR 14
      CH$ = INPUT$(1, 1)
      TM0 = TIMER
      WHILE CH$ <> ENDCH$
        PRINT #2, CH$;
        IF CH$ <> LF$ THEN PRINT CH$;
        CH$ = INPUT$(1, 1)
      WEND
    CASE "2"
      FLAG% = -1
      CLS : COLOR 13: LOCATE 7, 18
      PRINT "*********** 微机 ==> DTM-450 **********"
      LOCATE 12, 20
      COLOR 7: PRINT "联结通讯线,在";
      COLOR 14: PRINT "DTM-450";
      COLOR 7: PRINT "上选择";
      COLOR 13: PRINT "Upload";
      COLOR 7: PRINT "项"
      LOCATE 14, 27: PRINT "然后在微机上按任意键"
      OPEN "COM2:4800,N,8,1,DS,RS" FOR RANDOM AS 1
      OPEN "E:\YHF\COM\DTM.UP" FOR INPUT AS 2
      COLOR 14: LNO = 0
      DO
      LOOP WHILE INKEY$ = ""
      TM0 = TIMER
      CALL OUTLN("A,01,Z,")
      WHILE NOT EOF(2)
        LINE INPUT #2, LN$: LNO = LNO + 1
        IF CHG(LN$) THEN CALL OUTLN(LN$): PRINT LN$
      WEND
      LNO = -1
      CALL OUTLN("Z,&,")
    END SELECT
  IF FLAG% THEN
    CLOSE
    PT = INT(TIMER - TM0): IF PT < 0 THEN PT = PT + 86400
    COLOR 13: PRINT CHR$(10); "              通讯完成(历时"; PT; "秒)"
    COLOR 12: PRINT CHR$(10); "            按 任 意 键 返 回 主 菜 单"
    DO
    LOOP WHILE INKEY$ = ""
  END IF
LOOP

FUNCTION CHG% (A$)
  A$ = LTRIM$(A$)
  A$ = RTRIM$(A$)
  L = LEN(A$)
  IF L > 125 THEN
    COLOR 12
    PRINT "第"; LNO; "行数据太长"
    SYSTEM
  END IF
  IF L <> 0 THEN
    A$ = "G," + A$ + ","
    L = L + 3: K = 0
    FOR I = 1 TO L
      K = K + ASC(MID$(A$, I, 1))
    NEXT
    A$ = A$ + CHR$((K AND 63) + 32) + ","
    CHG = -1
  END IF
END FUNCTION

FUNCTION FIND% (NO AS LONG)
  FOR I = 1 TO YZDS
    IF YZD(I).NO = NO THEN FIND% = I: I = YZDS + 1
  NEXT
END FUNCTION

SUB OUTLN (OUT$)
  COUNT = 0
  DO
    PRINT #1, OUT$
    LINE INPUT #1, REP$
    COUNT = COUNT + 1
  LOOP WHILE INSTR(REP$, ACK$) = 0 AND COUNT < 3
  IF INSTR(REP$, ACK$) = 0 THEN
    COLOR 12
    IF LNO = 0 THEN
      PRINT "起始通信有误"
    ELSEIF LNO <> -1 THEN
      PRINT "DTM.UP中第"; LNO; "行数据有误"
    ELSE
      PRINT "终止通信有误"
    END IF
    SYSTEM
  END IF
END SUB

FUNCTION TAKE$ (DATA$, N%)
  P1% = 1
  FOR I = 1 TO N% - 1
    P1% = INSTR(P1%, DATA$, ",") + 1
  NEXT
  P2% = INSTR(P1%, DATA$, ",")
  TAKE$ = MID$(DATA$, P1%, P2% - P1%)
END FUNCTION

