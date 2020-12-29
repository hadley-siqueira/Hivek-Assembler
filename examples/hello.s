main:
    addi %1, %0, 0
    addi %2, %0, 10

L0:
    addi %1, %1, 1
    bne  %1, %2, L0

L1:
    addi %1, %0, 0
