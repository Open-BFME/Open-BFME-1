.386
.model flat

; ??0AIMoveOutOfTheWayState@@QAE@PAVStateMachine@@@Z
; Exact 46B @ 0x0017F350. Drift 0x185BBF was INSIDE AIStateMachine ctor (inlined
; newInstance after operator new(0x50); SEH state 6). True body is string-anchored
; on "AIMoveOutOfTheWayState" and builds State debug-name via StringBase/AsciiString
; (char*) @ 0x888BC0, then AIInternalMoveToState @ 0x32182 + vtbl 0x109A278.
; Sibling pattern: AIBusyState_ctor.asm / AIDeadState_ctor.asm.
_TEXT SEGMENT
public ??0AIMoveOutOfTheWayState@@QAE@PAVStateMachine@@@Z
??0AIMoveOutOfTheWayState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0D0h,0A2h,09h,01h
    db 0E8h,5Bh,98h,70h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,11h,2Eh,0EBh
    db 0FFh,0C7h,06h,78h,0A2h,09h,01h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0AIMoveOutOfTheWayState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
