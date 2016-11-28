'DTM-450 CKS(Check sum)
A$ = "CT" + CHR$(2) + "$REC" + CHR$(3)
L = LEN(A$)
K = 0
FOR I = 1 TO L
  K = K + ASC(MID$(A$, I, 1))
NEXT
K = (K AND 63) + 32
PRINT "check sum="; K, CHR$(K)
END

