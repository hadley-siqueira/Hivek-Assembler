main:
    addi %25, %0, 1
    addi a0, %0, 10
    jal fib
    halt
    add %0, %0, %0
    add %0, %0, %0
    add %0, %0, %0
    


fib:
    blt %25, a0, recurse
    add v0, a0, %0
    jr

recurse:
    addi sp, sp, -24
    sd ra, sp, 0
    sd a0, sp, 8

    addi a0, a0, -1
    jal fib
    sd v0, sp, 16

    ld a0, sp, 8
    addi a0, a0, -2
    jal fib

    ld t0, sp, 16
    add v0, v0, t0
    ld ra, sp, 0
    addi sp, sp, 24
    jr 
