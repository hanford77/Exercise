DECLARE FUNCTION DMS# (A AS DOUBLE, N AS INTEGER)
DECLARE SUB WCTY (NO%, E#, F#, A#)
DECLARE FUNCTION ATN2# (X AS DOUBLE, Y AS DOUBLE)
DECLARE SUB JZNI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DECLARE SUB TRINI (A() AS DOUBLE, B() AS DOUBLE, N AS INTEGER)
DIM SHARED NT AS INTEGER, N AS INTEGER
INPUT "N=", N
INPUT "T=", NT
INPUT "R=", R
OPTION BASE 1
DIM B(N, NT) AS DOUBLE, L(N) AS DOUBLE, NN(NT * NT) AS DOUBLE
DIM P(N) AS DOUBLE, T AS DOUBLE, U(N) AS DOUBLE
DIM SHARED Q(NT * NT) AS DOUBLE, M0 AS DOUBLE
DIM PVV AS DOUBLE
FOR I = 1 TO N
FOR J = 1 TO NT
PRINT "B("; I; ","; J;
INPUT ")=", B(I, J)
NEXT J
PRINT "L("; I;
INPUT ")=", L(I)
NEXT I
FOR I = 1 TO N
PRINT "P("; I;
INPUT ")=", P(I)
PVV = PVV + P(I) * L(I) * L(I)
NEXT I

FOR I = 1 TO N
FOR J = 1 TO NT
PRINT B(I, J); "      ";
NEXT J
PRINT L(I); "    "; P(I)
NEXT I


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
FOR J = 1 TO I
PRINT "N("; I; ","; J; ")="; NN((I - 1) * NT + J)
NEXT J
NEXT I


FOR I = 1 TO NT
T = 0#
FOR K = 1 TO N
T = T + B(K, I) * P(K) * L(K)
NEXT K
U(I) = T
PRINT "U("; I; ")="; T
NEXT I

CALL JZNI(NN(), Q(), NT)


FOR I = 1 TO NT
FOR J = 1 TO I
PRINT "Q("; I; ","; J; ")="; Q((I - 1) * NT + J)
NEXT J
NEXT I

FOR I = 1 TO NT
T = 0#
FOR J = 1 TO NT
T = T - Q((I - 1) * NT + J) * U(J)
NEXT J
PRINT "X("; I; ")="; T
PVV = PVV + T * U(I)
NEXT I
PRINT PVV
M0 = SQR(PVV / R)
PRINT "M0="; M0
CALL WCTY(1, E#, F#, A#)
PRINT "NO.1", "E="; E#, "F="; F#, "A="; DMS(A#, 4)
CALL WCTY(2, E#, F#, A#)
PRINT "NO.2", "E="; E#, "F="; F#, "A="; DMS(A#, 4)
SYSTEM

FUNCTION ATN2# (X AS DOUBLE, Y AS DOUBLE)
HALFPI# = 1.570796326794897#
IF ABS(X) > ABS(Y) THEN
A# = HALFPI# * (1 - SGN(X)) + ATN(Y / X)
ELSEIF Y <> 0# THEN
A# = HALFPI# * (2 - SGN(Y)) - ATN(X / Y)
ELSE
A# = 0
END IF
IF A# > 2 * HALFPI# THEN
ATN2# = A# - 4 * HALFPI#
ELSE
ATN2# = A#
END IF
END FUNCTION

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
FUNCTION DMS# (A AS DOUBLE, N AS INTEGER)
DEFDBL A-Z
PI = 3.141592653589793#
S = A * 180 / PI - 360 * INT(.5 * A / PI): D = FIX(S)
IF N <= 1 THEN
DMS# = D: EXIT FUNCTION
END IF
S = 60 * (S - D): M = FIX(S)
IF N <= 3 THEN
DMS# = D + .01 * M: EXIT FUNCTION
END IF
K = 10# ^ (N - 4): S = INT(.5 + 60 * (S - M) * K) / K
IF S = 60# THEN
M = M + 1: S = 0
IF M = 60# THEN
D = D + 1: M = 0
IF D = 360# THEN
D = 0
END IF
END IF
END IF
DMS# = (S * .01 + M) * .01 + D
END FUNCTION

DEFSNG A-Z
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

DEFSNG A-Z
SUB WCTY (NO%, E#, F#, A#)
P = 2 * (NO% - 1) * NT + 2 * NO% - 1
QX# = Q(P) * .5#
QY# = Q(P + NT + 1) * .5#
QXY# = Q(P + 1)
K# = SQR((QX# - QY#) ^ 2 + QXY# ^ 2)
E# = M0 * SQR(QX# + QY# + K#)
F# = M0 * SQR(QX# + QY# - K#)
A# = .5# * ATN2(QX# - QY#, QXY#)
END SUB

