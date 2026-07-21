.386
.model flat

; ??0FailureState@@QAE@PAVStateMachine@@@Z
; Exact 46B @ 0x00170E10. Drift 0x180D10 was inside AIStateMachine ctor (inlined
; newInstance sequence after operator new; SEH state byte at [esp+0x28]=0x0a).
; True body is string-anchored on "FailureState" and builds the State debug-name
; via StringBase/AsciiString(char*) @ 0x888BC0. Sibling: AIDeadState/AIBusyState.
_TEXT SEGMENT
public ??0FailureState@@QAE@PAVStateMachine@@@Z
??0FailureState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0A4h,79h,09h,01h
    db 0E8h,9Bh,7Dh,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,81h,27h,0E9h
    db 0FFh,0C7h,06h,50h,79h,09h,01h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0FailureState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
