.386
.model flat

; ??0AIDockState@@QAE@PAVStateMachine@@@Z
; Exact 54B @ 0x00171420. Drift 0x18661D was mid-insn inside AIStateMachine
; ctor (inlined newInstance sequence; c6 44 24 20 2a ...). True body is
; string-anchored on "AIDockState" @ VA 0x1097f5c (xrefs 0x17142b ctor,
; 0x17146b getName-style, 0x18662a inlined). Builds State debug-name via
; StringBase/AsciiString(char*) @ 0x888BC0, then base State ctor, stores own
; vtable + m_dockMachine=NULL at +0x24 + m_usingPrecisionMovement=FALSE at +0x28.
; Sibling: AIAttackAreaState_ctor.asm / AIGuardRetaliateState_ctor.asm.
_TEXT SEGMENT
public ??0AIDockState@@QAE@PAVStateMachine@@@Z
??0AIDockState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,5Ch,7Fh,09h,01h
    db 0E8h,8Bh,77h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,71h,21h,0E9h
    db 0FFh,33h,0C0h,89h,46h,24h,88h,46h,28h,0C7h,06h,08h,7Fh,09h,01h,8Bh
    db 0C6h,5Eh,59h,0C2h,04h,00h
??0AIDockState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
