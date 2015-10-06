.section .text

.globl __PROGRAM_START
.globl __PROGRAM_END

__PROGRAM_STARTA:
.incbin "/data/Desktop/Siwka OS/Common/Programs/Init.swx"
.incbin "/data/Desktop/Siwka OS/Common/Programs/Leprog.swx"
.incbin "/data/Desktop/Siwka OS/Common/Programs/Snake.swx"
__PROGRAM_ENDA:

__PROGRAM_START: .word __PROGRAM_STARTA
__PROGRAM_END: .word __PROGRAM_ENDA
