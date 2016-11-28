DECLARE SUB PAUSE (TM!)
DIM char AS STRING * 1
DIM BOL AS INTEGER
ENDCH$ = CHR$(26)
CR$ = CHR$(13)
LF$ = CHR$(10)
DIM PATH$(200), MC$(200)
SCREEN 0
DO
FLAG% = 0
CLS : COLOR 13: LOCATE 5, 25: PRINT "PC-E500 <===> IBM PC 数据通讯"
COLOR 12: LOCATE 7, 21: PRINT "(PC-E500上OPEN$='1200,N,8,1,,L,&H1A')"
COLOR 2
LOCATE 10, 29: PRINT "1. 程序到微机"
LOCATE 11, 29: PRINT "2. 程序到PC-E500"
LOCATE 12, 29: PRINT "3. 文件到微机"
LOCATE 13, 29: PRINT "4. 文件到PC-E500"
LOCATE 14, 29: PRINT "5. 文件到微机(双向)"
LOCATE 15, 29: PRINT "6. 文件到PC-E500(双向)"
COLOR 14: LOCATE 18, 27: INPUT "请选择:(0--退出)"; C$: C$ = UCASE$(C$)
COLOR 7
SELECT CASE C$
 CASE "0"
  CLS : SYSTEM
 CASE "1"
  FLAG% = -1
  CLS : COLOR 13: LOCATE 7, 20: PRINT " *********** 程序到微机 *********"
  OPEN "COM1:1200,N,8,1,DS,RS" FOR INPUT AS 1
  COLOR 14: LOCATE 10, 30: INPUT "文件名: "; NAME$
  IF INSTR(NAME$, "\") = 0 THEN
    NAME$ = "FILE\" + NAME$
  END IF
  OPEN NAME$ FOR OUTPUT AS 2
  LOCATE 13, 29: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入:"
  LOCATE 14, 29: COLOR 13: PRINT "SAVE 'COM:'"
  LOCATE 16, 29: COLOR 7: PRINT "或者:"
  LOCATE 17, 29: COLOR 13: PRINT "OPEN"
  LOCATE 18, 29: PRINT "LLIST 行号--行号"
  LOCATE 19, 29: PRINT "CLOSE"
  COLOR 14: PRINT
  BOL = -1
  CH$ = INPUT$(1, 1)
  TM0 = TIMER
  WHILE CH$ <> ENDCH$
   IF CH$ < "0" OR CH$ > "9" THEN
    IF CH$ = ":" AND BOL THEN
     BOL = 0: PRINT #2, " "; : PRINT " ";
    ELSEIF CH$ = CR$ OR CH$ = LF$ THEN
     IF BOL = 0 THEN BOL = -1: PRINT #2, : PRINT
    ELSE
     BOL = 0: PRINT #2, CH$; : PRINT CH$;
    END IF
   ELSE
    PRINT #2, CH$; : PRINT CH$;
   END IF
  CH$ = INPUT$(1, 1)
  WEND
 CASE "2"
  FLAG% = -1
  CLS : COLOR 13: LOCATE 7, 20: PRINT " *********** 程序到 PC-E500 **********"
  LOCATE 11, 32: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入:"
  LOCATE 12, 32: COLOR 13: PRINT "LOAD 'COM:' "
  LOCATE 13, 32: COLOR 7: PRINT "或"
  LOCATE 14, 32: COLOR 13: PRINT "MERGE 'COM:'"
  COLOR 14: LOCATE 17, 33: INPUT "文件名:"; NAME$
  OPEN "COM1:1200,N,8,1,DS,RS,TB512" FOR OUTPUT AS 1
  IF INSTR(NAME$, "\") = 0 THEN
    NAME$ = "FILE\" + NAME$
  END IF
  OPEN NAME$ FOR INPUT AS 2
  CLS : COLOR 14
  TM0 = TIMER
  WHILE NOT EOF(2)
   LINE INPUT #2, LN$
   LN$ = LTRIM$(LN$): LN$ = RTRIM$(LN$)
   IF LEN(LN$) <> 0 THEN
    PRINT LN$
    CALL PAUSE(1)
    PRINT #1, LN$
   END IF
  WEND
  PRINT #1, ENDCH$;
  CALL PAUSE(1)
 CASE "3"
  FLAG% = -1
  CLS : COLOR 13: LOCATE 7, 22: PRINT "*********** 文件到微机 ***********"
  OPEN "COM1:1200,N,8,1,DS,RS" FOR INPUT AS 1
  COLOR 14: LOCATE 10, 30: INPUT "文件名:"; NAME$
  IF INSTR(NAME$, "\") = 0 THEN
    NAME$ = "FILE\" + NAME$
  END IF
  OPEN NAME$ FOR OUTPUT AS 2
  LOCATE 13, 32: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入";
  LOCATE 15, 27: COLOR 13: PRINT "COPY '设备:文件名' TO 'COM:' "
  COLOR 14
  CH$ = INPUT$(1, 1): LAST$ = ""
  TM0 = TIMER
  WHILE CH$ <> ENDCH$
   IF CH$ = CR$ THEN
    PRINT #2, : PRINT
   ELSEIF CH$ = LF$ THEN
    IF LAST$ <> CR$ THEN PRINT #2, : PRINT
   ELSE
    PRINT #2, CH$; : PRINT CH$;
   END IF
  LAST$ = CH$
  CH$ = INPUT$(1, 1)
  WEND
 CASE "4"
  FLAG% = -1
  CLS : COLOR 13
  LOCATE 7, 20: PRINT "********* 文件到 PC-E500 *********"
  LOCATE 11, 30: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入:"
  LOCATE 13, 25: COLOR 13: PRINT "COPY 'COM:' TO '设备:文件名'"
  COLOR 14: LOCATE 17, 32: INPUT "文件名:"; NAME$
  OPEN "COM1:1200,N,8,1,DS,RS,TB512" FOR RANDOM AS 1
  IF INSTR(NAME$, "\") = 0 THEN
    NAME$ = "FILE\" + NAME$
  END IF
  OPEN NAME$ FOR INPUT AS 2
  CLS : COLOR 14
  TM0 = TIMER
  WHILE NOT EOF(2)
   LINE INPUT #2, LN$
   PRINT LN$
   CALL PAUSE(1)
   PRINT #1, LN$
  WEND
  PRINT #1, ENDCH$;
  CALL PAUSE(1)
 CASE "5"
  FLAG% = -1
  CLS : COLOR 13: LOCATE 7, 22: PRINT "*********** 文件到微机(双向) ***********"
  OPEN "COM1:1200,N,8,1,DS,RS" FOR RANDOM AS 1
  COLOR 14: LOCATE 13, 32: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入";
  LOCATE 15, 30: COLOR 13: PRINT "G. *OUT  或  G. *E"
  COLOR 14
  TM0 = TIMER
  CH$ = INPUT$(1, 1)
   WHILE CH$ <> CHR$(129)
    IF CH$ = CHR$(130) THEN
     NAME$ = ""
     K = 1
     CH$ = INPUT$(1, 1)
     WHILE CH$ <> CHR$(13)
      NAME$ = NAME$ + CH$
      IF CH$ = ":" THEN K = LEN(NAME$) + 1
      CH$ = INPUT$(1, 1)
     WEND
     NAME$ = MID$(NAME$, K)
     CLOSE 2
     OPEN "FILE\" + NAME$ FOR OUTPUT AS 2
    ELSE
     CH$ = INPUT$(ASC(CH$), 1)
     PRINT #2, CH$;
     PRINT CH$;
     END IF
   CH$ = INPUT$(1, 1)
   WEND
   CH$ = INPUT$(1, 1)
 CASE "6"
  FLAG% = -1
  CLS : COLOR 13
  LOCATE 7, 20: PRINT "********* 文件到 PC-E500(双向) *********"
  LOCATE 11, 30: COLOR 7: PRINT "在";
  COLOR 14: PRINT "PC-E500";
  COLOR 7: PRINT "上输入:"
  LOCATE 13, 34: COLOR 13: PRINT "G. *IN"
  COLOR 14: LOCATE 17, 25: INPUT "显示OK后在微机上输入回车键:", NAME$
  OPEN "COM1:1200,N,8,1,DS,RS" FOR RANDOM AS 1
  COLOR 14
  TM0 = TIMER
  PH$ = ""
  NO = 0
  OPEN "FLIST.TXT" FOR INPUT AS 3
  WHILE NOT EOF(3)
   LINE INPUT #3, LN$
   LN$ = RTRIM$(LTRIM$(LN$))
   IF INSTR(LN$, "\") THEN
    PH$ = LN$ + "\"
   ELSEIF MID$(LN$, 1, 4) <> "REM " AND LN$ <> "" THEN
    NO = NO + 1
    PATH$(NO) = PH$
    MC$(NO) = UCASE$(LN$)
   END IF
  WEND
  CLOSE 3
  FOR I = 1 TO NO
   OPEN PATH$(I) + MC$(I) FOR RANDOM AS 2 LEN = 1
   PRINT #1, CHR$(130); MC$(I); "*";
   CH$ = INPUT$(1, 1)
   K = LOF(2)
   M = INT(K / 128)
   N = K - 128 * M
   FOR II = 1 TO M
    PRINT #1, CHR$(128);
    LN$ = ""
    FOR J = 1 TO 128
     GET #2, , char
     LN$ = LN$ + char
    NEXT
    PRINT #1, LN$;
    PRINT LN$;
    CH$ = INPUT$(1, 1)
   NEXT
   IF N <> 0 THEN
    PRINT #1, CHR$(N);
    LN$ = ""
    FOR J = 1 TO N
     GET #2, , char
     LN$ = LN$ + char
    NEXT
    PRINT #1, LN$;
    PRINT LN$;
    CH$ = INPUT$(1, 1)
   END IF
   CLOSE 2
  NEXT
  PRINT #1, CHR$(129);
  CH$ = INPUT$(1, 1)
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

SUB PAUSE (TM)
DO
LOOP WHILE LOF(1) < 512
TM0 = TIMER
DO
PT = TIMER - TM0
IF PT < 0 THEN PT = PT + 86400
LOOP WHILE PT < TM
END SUB

