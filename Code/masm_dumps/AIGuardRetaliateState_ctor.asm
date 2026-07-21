.386
.model flat

; ??0AIGuardRetaliateState@@QAE@PAVStateMachine@@@Z
; Exact 53B @ 0x00171750. Drift 0x1868F8 was mid-insn inside AIStateMachine
; ctor (inlined newInstance sequence; c6 44 24 20 33 ...). True body is
; string-anchored on "AIGuardRetaliateState" @ VA 0x109829c (xrefs 0x17175c,
; 0x1717a1 getName-style, 0x186906 inlined). Builds State debug-name via
; StringBase/AsciiString(char*) @ 0x888BC0, then base State ctor, stores own
; vtable + m_guardRetaliateMachine=NULL at +0x24. Sibling: AIDeadState_ctor.asm.
_TEXT SEGMENT
public ??0AIGuardRetaliateState@@QAE@PAVStateMachine@@@Z
??0AIGuardRetaliateState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,9Ch,82h,09h,01h
    db 0E8h,5Bh,74h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,41h,1Eh,0E9h
    db 0FFh,0C7h,06h,48h,82h,09h,01h,0C7h,46h,24h,00h,00h,00h,00h,8Bh,0C6h
    db 5Eh,59h,0C2h,04h,00h
??0AIGuardRetaliateState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
