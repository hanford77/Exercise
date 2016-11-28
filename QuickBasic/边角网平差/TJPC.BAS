DECLARE SUB JZNI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DECLARE SUB TRINI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DIM R AS INTEGER, N AS INTEGER
OPEN "TJPC.DAT" FOR INPUT AS 1
OPEN "TJPC.TXT" FOR OUTPUT AS 2
LINE INPUT #1, AA$
INPUT #1, N
LINE INPUT #1, AA$
INPUT #1, R
PRINT #2, "n="; N
PRINT #2, "r="; R
LINE INPUT #1, AA$
OPTION BASE 1
DIM A(R, N) AS DOUBLE, W(R) AS DOUBLE, NK(R * R) AS DOUBLE, NNK(R * R) AS DOUBLE
DIM P(N) AS DOUBLE, K(R) AS DOUBLE, T AS DOUBLE, PVV AS DOUBLE
FOR I = 1 TO R
FOR J = 1 TO N
INPUT #1, A(I, J)
NEXT J
INPUT #1, W(I)
NEXT I
LINE INPUT #1, AA$
FOR I = 1 TO N
INPUT #1, P(I)
NEXT I
CLOSE 1
FOR I = 1 TO R
FOR J = 1 TO I
T = 0#
FOR K = 1 TO N
T = T + A(I, K) * A(J, K) * P(K)
NEXT K
NK((I - 1) * R + J) = T
NK((J - 1) * R + I) = T
NEXT J
NEXT I
PRINT #2, "法方程"
FOR I = 1 TO R
FOR J = 1 TO R
PRINT #2, NK((I - 1) * R + J)
NEXT J
NEXT I
CALL JZNI(NK(), NNK(), R)
PRINT #2, CHR$(13) + "法方程系数阵之逆"
FOR I = 1 TO R
FOR J = 1 TO R
PRINT #2, NNK((I - 1) * R + J)
NEXT J
NEXT I
PRINT #2, CHR$(13) + "联系数K"
FOR I = 1 TO R
T = 0#
FOR J = 1 TO R
T = T - NNK((I - 1) * R + J) * W(J)
NEXT J
K(I) = T
PRINT #2, "K"; I; "="; T
NEXT I
PRINT #2, CHR$(13) + "改正数V"
FOR I = 1 TO N
T = 0#
FOR J = 1 TO R
T = T + K(J) * A(J, I) * P(I)
NEXT J
PRINT #2, "V"; I; "="; T
PVV = PVV + T * T / P(I)
NEXT I
PRINT #2, "[PVV]="; PVV
SYSTEM

SUB DCNI (Q() AS DOUBLE, R() AS DOUBLE, N AS INTEGER)
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
CALL TRINI(A(), R(), N)
P = N * (N + 1) / 2: P1 = P
FOR I = N TO 1 STEP -1
P2 = P1: P1 = P1 - I
FOR J = I TO 1 STEP -1
T = 0: P2 = P2 - J
FOR K = 1 TO J
T = T + R(P1 + K) * R(P2 + K)
NEXT K
R(P) = T: P = P - 1
NEXT J
NEXT I
END SUB

DEFSNG I-K, P
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

