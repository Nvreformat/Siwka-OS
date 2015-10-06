#include <Kernel/sysconfig.h>

.section .init

.globl _start
_start:
	cps	#0x13
	ldr	sp, =MEM_SVC_STACK
	cps	#0x12
	ldr	sp, =MEM_IRQ_STACK
	cps	#0x1F
	ldr	sp, =MEM_KERNEL_STACK
	b	SystemInit

.section .text

.globl Write32
Write32:
	str r1,[r0]
	bx lr

.globl Read32
Read32:
	ldr r0,[r0]
	bx lr
	
.globl DelayLoop
DelayLoop:
	subs	r0, r0, #1
	bhi	DelayLoop
	mov	pc, lr

.globl IRQStub
IRQStub:
	sub	lr, lr, #4
	stmfd	sp!, {r0-r12, lr}
	bl	InterruptHandler
	ldmfd	sp!, {r0-r12, pc}^
	
.globl SVCStub
SVCStub:

	
.globl memcpy2
memcpy2:
	
	push {r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}

    loop$:
		ldmia r0!,{r3,r4,r5,r6,r7,r8,r9,r10,r11}
		stmia r1!,{r3,r4,r5,r6,r7,r8,r9,r10,r11}
		
		subs r2, r2, #36
		cmp r2, #36
		bge loop$
		cmp r2, #0
		beq end$
		
	loop2$:
		ldrb r3, [r0, #1]
		strb r3, [r1, #1]
		
		add r0, r0, #1
		add r1, r1, #1
		subs r2, r2, #1
		cmp r2, #0
		bne loop2$
		
	
	end$:
		
	pop {r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
	
	mov pc, lr

.globl Led
Led:
	ldr r0,=0x20200000 

	mov r1,#1
	lsl r1,#21
	str r1,[r0,#16]

	mov r1,#1
	lsl r1,#15
	str r1,[r0,#32]
	
	mov pc, lr
	
.globl BranchTo
BranchTo:
	push {r1-r12, lr}
	
	blx r0
	
	pop {r1-r12, lr}
	
	mov pc, lr
	
.globl GetSP
GetSP:
	mov r0, sp
	
	mov pc, lr


