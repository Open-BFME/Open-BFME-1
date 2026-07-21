.386
.model flat

; ??0AIDeadState@@QAE@PAVStateMachine@@@Z
; Exact 46B @ 0x001713C0. Drift 0x1865CF was inside AIStateMachine ctor (inlined
; newInstance sequence). True body is string-anchored on "AIDeadState" and
; builds the State debug-name via StringBase/AsciiString(char*) @ 0x888BC0.
_TEXT SEGMENT
public ??0AIDeadState@@QAE@PAVStateMachine@@@Z
??0AIDeadState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0F4h,7Eh,09h,01h
    db 0E8h,0EBh,77h,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0D1h,21h,0E9h
    db 0FFh,0C7h,06h,0A0h,7Eh,09h,01h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0AIDeadState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
