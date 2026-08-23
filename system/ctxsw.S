/*----------------------------------------------------------------------------------------*/
/*   ctxsw -- actually perform context switch, saving and loading registers               */
/*----------------------------------------------------------------------------------------*/
	
	.set __SREG__,0x3f	        ; Status register
	.set __SP_H__,0x3e	        ; Stack pointer high
	.set __SP_L__,0x3d	        ; Stack pointer low

	.global ctxsw
	
ctxsw:
;;; Save old context
    push    r31
    in      r31, __SREG__
    cli
    push    r31
    push    r30
    push    r29
    push    r28
    push    r27
    push    r26
    push    r25
    push    r24
    push    r23
    push    r22
    push    r21
    push    r20
    push    r19
    push    r18
    push    r17
    push    r16
    push    r15
    push    r14
    push    r13
    push    r12
    push    r11
    push    r10
    push    r9
    push    r8
    push    r7
    push    r6
    push    r5
    push    r4
    push    r3
    push    r2
    push    r1
    push    r0
    movw    r30, r24            ; get first argument
    in      r0, __SP_L__        ; get SP_L
    st      Z+, r0              ; save SP_L
    in      r0, __SP_H__        ; get SP_H
    st      Z, r0               ; save SP_H

;;; Restore new context
    movw    r30,r22             ; get argument
    ld      r16, Z+              ; load SP_L
    ld      r17, Z               ; load SP_H
    out     __SP_H__, r17        ; put SP_H
    out     __SP_L__, r16        ; put SP_L

    pop     r0
    pop     r1
    pop     r2
    pop     r3
    pop     r4
    pop     r5
    pop     r6
    pop     r7
    pop     r8
    pop     r9
    pop     r10
    pop     r11
    pop     r12
    pop     r13
    pop     r14
    pop     r15
    pop     r16
    pop     r17
    pop     r18
    pop     r19
    pop     r20
    pop     r21
    pop     r22
    pop     r23
    pop     r24
    pop     r25
    pop     r26
    pop     r27
    pop     r28
    pop     r29
    pop     r30
    pop     r31
    out     __SREG__, r31
    pop     r31

    ret


