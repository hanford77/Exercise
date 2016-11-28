DECLARE FUNCTION NO! (A$)
DECLARE SUB GETH0 ()
DECLARE SUB JZNI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DECLARE SUB TRINI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
OPTION BASE 1
DIM SHARED NT AS INTEGER
DIM SHARED N AS INTEGER
DIM SHARED YZDS AS INTEGER
DIM SHARED DS AS INTEGER
OPEN "PC.TXT" FOR INPUT AS 1
INPUT #1, A$
K = INSTR(1, A$, ":")
IF K = 0 THEN
 PRINT "ERROR"
 SYSTEM
END IF
DS = VAL(MID$(A$, K + 1))
DIM SHARED CD$(DS)
DIM SHARED H(DS) AS DOUBLE
INPUT #1, A$
K = INSTR(1, A$, ":")
IF K = 0 THEN
 PRINT "ERROR"
 SYSTEM
END IF
YZDS = VAL(MID$(A$, K + 1))
FOR I = 1 TO YZDS
 INPUT #1, CD$(I), H(I)
NEXT
INPUT #1, A$
K = INSTR(1, A$, ":")
IF K = 0 THEN
 PRINT "ERROR"
 SYSTEM
END IF
NT = VAL(MID$(A$, K + 1))
IF DS <> YZDS + NT THEN
 PRINT "ERROR:DS"
 SYSTEM
END IF
FOR I = YZDS + 1 TO DS
 INPUT #1, CD$(I)
NEXT
INPUT #1, A$
K = INSTR(1, A$, ":")
IF K = 0 THEN
 PRINT "ERROR"
 SYSTEM
END IF
N = VAL(MID$(A$, K + 1))
DIM SHARED PT1(N) AS INTEGER
DIM SHARED PT2(N) AS INTEGER
DIM SHARED GC(N) AS DOUBLE
DIM P(N) AS DOUBLE
DIM HP$(4)
FOR I = 1 TO N
 FOR J = 1 TO 4
  INPUT #1, HP$(J)
 NEXT
 PT1(I) = NO(HP$(1))
 PT2(I) = NO(HP$(2))
 GC(I) = VAL(HP$(3))
 P(I) = 1# / VAL(HP$(4))
NEXT
CALL GETH0
DIM B(N, NT) AS DOUBLE
DIM L(N) AS DOUBLE
DIM PVV AS DOUBLE
FOR I = 1 TO N
IF PT1(I) > YZDS THEN B(I, PT1(I) - YZDS) = -1
IF PT2(I) > YZDS THEN B(I, PT2(I) - YZDS) = 1
L(I) = H(PT2(I)) - H(PT1(I)) - GC(I)
PVV = PVV + P(I) * L(I) * L(I)
NEXT
CLOSE
ERASE PT1, PT2, GC, HP$
DIM NN(NT * NT) AS DOUBLE
DIM T AS DOUBLE, U(N) AS DOUBLE
DIM SHARED Q(NT * NT) AS DOUBLE, M0 AS DOUBLE
FOR I = 1 TO NT
FOR J = 1 TO I
T = 0#
FOR K = 1 TO N
T = T + B(K, I) * B(K, J) * P(K)
NEXT K
NN((I - 1) * NT + J) = T
NN((J - 1) * NT + I) = T
NEXT J
NEXT I
FOR I = 1 TO NT
T = 0#
FOR K = 1 TO N
T = T + B(K, I) * P(K) * L(K)
NEXT K
U(I) = T
NEXT I
CALL JZNI(NN(), Q(), NT)
OPEN "JG.TXT" FOR OUTPUT AS 2
FOR I = 1 TO NT
 FOR J = 1 TO I
  PRINT #2, "Q("; I; ","; J; ")="; Q((I - 1) * NT + J)
 NEXT
NEXT
FOR I = 1 TO NT
 T = 0#
 FOR J = 1 TO NT
  T = T - Q((I - 1) * NT + J) * U(J)
 NEXT J
 H(I + YZDS) = H(I + YZDS) + T
 PRINT #2, CD$(I + YZDS); SPACE$(10 - LEN(CD$(I + YZDS)));
 PRINT #2, "H("; I; ")="; H(I + YZDS)
 PVV = PVV + T * U(I)
NEXT I
PRINT #2, "[PVV]="; PVV
PRINT #2, "r="; N - NT
M0 = SQR(PVV / (N - NT))
PRINT #2, "M0="; M0
FOR I = 1 TO NT
T = M0 * SQR(Q((I - 1) * NT + I)) * 1000#
T = .1# * INT(T * 10 + .5)
PRINT #2, CD$(I + YZDS); SPACE$(10 - LEN(CD$(I + YZDS)));
PRINT #2, "M("; I; ")=";
PRINT #2, USING "####.#"; T;
PRINT #2, "mm"
NEXT I
CLOSE
PRINT "Output in file:JG.TXT"
SYSTEM

SUB DCNI (Q() AS DOUBLE, NT() AS DOUBLE, N AS INTEGER)
DEFINT I-K, P
DIM U AS DOUBLE, T AS DOUBLE
P = N * (N + 1) / 2
DIM A(P) AS DOUBLE
FOR I = N TO 1 STEP -1
T = Q(P): P1 = P + I
FOR K = I + 1 TO N
T = T - A(P1) ^ 2: P1 = P1 + K
NEXT K
A(P) = SQR(T): U = 1 / A(P): P = P - 1
FOR J = I - 1 TO 1 STEP -1
T = Q(P): P1 = P + I
FOR K = I + 1 TO N
T = T - A(P1 - J + I) * A(P1): P1 = P1 + K
NEXT K
A(P) = T * U: P = P - 1
NEXT J
NEXT I
CALL TRINI(A(), NT(), N)
P = N * (N + 1) / 2: P1 = P
FOR I = N TO 1 STEP -1
P2 = P1: P1 = P1 - I
FOR J = I TO 1 STEP -1
T = 0: P2 = P2 - J
FOR K = 1 TO J
T = T + NT(P1 + K) * NT(P2 + K)
NEXT K
NT(P) = T: P = P - 1
NEXT J
NEXT I
END SUB

DEFSNG I-K, P
SUB GETH0
 YZ$ = SPACE$(DS)
 FOR I = 1 TO YZDS
  MID$(YZ$, I, 1) = "Y"
 NEXT
 COUNT = 0
 DO
  FLAG = 0
  FOR I = YZDS + 1 TO NT
   IF MID$(YZ$, I, 1) <> "Y" THEN
   FOR J = 1 TO N
    IF PT1(J) = I THEN
    IF MID$(YZ$, PT2(J), 1) = "Y" THEN
     COUNT = COUNT + 1
     H(I) = H(PT2(J)) - GC(J)
     MID$(YZ$, I, 1) = "Y"
     FLAG = -1
    END IF
   END IF
   IF PT2(J) = I THEN
   IF MID$(YZ$, PT1(J), 1) = "Y" THEN
   COUNT = COUNT + 1
   H(I) = H(PT1(J)) + GC(J)
   FLAG = -1
   MID$(YZ$, I, 1) = "Y"
   END IF
  END IF
 NEXT
END IF
NEXT
LOOP WHILE FLAG <> 0
IF COUNT < NT THEN
PRINT "错误:高差数据不够!"
SYSTEM
END IF
END SUB

SUB JZNI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DEFDBL A-Z
DEFINT I-K, P
P = 1: P2 = 0
FOR I = 1 TO N
B(P) = 1: P = P + N + 1
NEXT I
FOR J = 1 TO N
P = P2 + 1: U = ABS(A(P)): L = J
FOR I = J + 1 TO N
P = P + N: T = ABS(A(P))
IF U < T THEN
U = T: L = I
END IF
NEXT I
IF U < 10 ^ -10 THEN
PRINT "SUB JZNI:DET A=0": SYSTEM
END IF
IF L <> J THEN
P = P2: P1 = N * (L - J)
FOR K = J TO N
P = P + 1
SWAP A(P), A(P + P1): SWAP B(P), B(P + P1)
NEXT K
P = P2
FOR K = J - 1 TO 1 STEP -1
SWAP B(P), B(P + P1): P = P - 1
NEXT K
END IF
P = P2 + 1: T = 1 / A(P)
FOR K = J + 1 TO N
P = P + 1: A(P) = T * A(P): B(P) = T * B(P)
NEXT K
P = P2 + 1
FOR K = J TO 1 STEP -1
B(P) = T * B(P): P = P - 1
NEXT K
P = J
FOR I = 1 TO N
IF I <> J THEN
T = -A(P): P1 = P: P3 = P2 + 2
FOR K = J + 1 TO N
P1 = P1 + 1: A(P1) = A(P1) + A(P3) * T
B(P1) = B(P1) + B(P3) * T: P3 = P3 + 1
NEXT K
P3 = P2 - J + 2: P1 = P1 - N
FOR K = 1 TO J
P1 = P1 + 1: B(P1) = B(P1) + B(P3) * T: P3 = P3 + 1
NEXT K
END IF
P = P + N
NEXT I
P2 = P2 + N + 1
NEXT J
END SUB

DEFSNG A-Z
FUNCTION NO (A$)
 K = 0
 FOR I = 1 TO DS
  IF CD$(I) = A$ THEN
   K = I
  END IF
 NEXT
 IF K = 0 THEN
  PRINT "ERROR: CODE$"
 END IF
 NO = K
END FUNCTION

SUB TRINI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DEFDBL A-Z
DEFINT I-K, P
P1 = 0
FOR I = 1 TO N
P1 = P1 + I: B(P1) = 1# / A(P1)
FOR J = I - 1 TO 1 STEP -1
T = 0: P2 = P1 - I + J
FOR K = I - 1 TO J STEP -1
P2 = P2 - K: T = T + A(P1 - I + K) * B(P2)
NEXT K
B(P1 - I + J) = -T * B(P1)
NEXT J
NEXT I
END SUB

