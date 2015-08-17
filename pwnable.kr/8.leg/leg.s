	.arch armv5t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"leg.c"
	.text
	.align	2
	.global	key1
	.type	key1, %function
key1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
#APP
@ 4 "leg.c" 1
	mov r3, pc
@ 0 "" 2
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	key1, .-key1
	.align	2
	.global	key2
	.type	key2, %function
key2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
#APP
@ 7 "leg.c" 1
	push	{r6}
add	r6, pc, $1
bx	r6
.code   16
mov	r3, pc
add	r3, $0x4
push	{r3}
pop	{pc}
.code	32
pop	{r6}

@ 0 "" 2
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	key2, .-key2
	.align	2
	.global	key3
	.type	key3, %function
key3:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
#APP
@ 21 "leg.c" 1
	mov r3, lr

@ 0 "" 2
	mov	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	key3, .-key3
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Daddy has very strong arm! : \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"Congratz!\000"
	.align	2
.LC3:
	.ascii	"flag\000"
	.align	2
.LC4:
	.ascii	"I have strong leg :P\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 120
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #124
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-128]
	ldr	r0, .L9+4
	bl	printf
	sub	r3, fp, #128
	ldr	r0, .L9+8
	mov	r1, r3
	bl	__isoc99_scanf
	bl	key1
	mov	r4, r0
	bl	key2
	mov	r3, r0
	add	r4, r4, r3
	bl	key3
	mov	r3, r0
	add	r2, r4, r3
	ldr	r3, [fp, #-128]
	cmp	r2, r3
	bne	.L5
	ldr	r0, .L9+12
	bl	puts
	ldr	r0, .L9+16
	mov	r1, #0
	bl	open
	str	r0, [fp, #-124]
	sub	r3, fp, #116
	ldr	r0, [fp, #-124]
	mov	r1, r3
	mov	r2, #100
	bl	read
	str	r0, [fp, #-120]
	sub	r3, fp, #116
	mov	r0, #0
	mov	r1, r3
	ldr	r2, [fp, #-120]
	bl	write
	b	.L6
.L5:
	ldr	r0, .L9+20
	bl	puts
.L6:
	mov	r3, #0
	mov	r0, r3
	ldr	r3, .L9
	ldr	r2, [fp, #-16]
	ldr	r3, [r3, #0]
	cmp	r2, r3
	beq	.L8
	bl	__stack_chk_fail
.L8:
	sub	sp, fp, #8
	ldmfd	sp!, {r4, fp, pc}
.L10:
	.align	2
.L9:
	.word	__stack_chk_guard
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.4-2ubuntu1) 4.7.4"
	.section	.note.GNU-stack,"",%progbits
