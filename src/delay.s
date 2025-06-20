   .syntax unified
   .cpu cortex-m0plus
   .fpu softvfp

   .equ cycles_1ms, 3999
   .global delay_ms

   .text
   .thumb

// Assumes 16Mhz Clock
delay_ms:
   PUSH {LR}
loop_ms:
   CMP R0, #0
   BEQ done_ms
   SUBS R0, #1
   BL delay_one_ms
   B loop_ms
done_ms:
   POP {PC}



delay_one_ms:
   PUSH {R0, R1, LR}
   MOVS R0, #0
   LDR R1, =cycles_1ms
loop_one_ms:
   CMP R0, R1
   BEQ done_one_ms
   ADDS R0, #1
   B loop_one_ms
done_one_ms:
   POP {R0, R1}
   POP {PC}
