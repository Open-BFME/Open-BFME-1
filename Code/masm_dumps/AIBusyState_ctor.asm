.386
.model flat

; ??0AIBusyState@@QAE@PAVStateMachine@@@Z
; Exact 46B @ 0x00170FC0. Drift 0x186BB8 was inside AIStateMachine ctor (inlined
; newInstance sequence after operator new). True body is string-anchored on
; "AIBusyState" and builds the State debug-name via StringBase/AsciiString(char*)
; @ 0x888BC0. Sibling pattern: AIDeadState_ctor.asm / ContinueState MASM.
_TEXT SEGMENT
public ??0AIBusyState@@QAE@PAVStateMachine@@@Z
??0AIBusyState@@QAE@PAVStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,90h,7Ah,09h,01h
    db 0E8h,0EBh,7Bh,71h,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,0D1h,25h,0E9h
    db 0FFh,0C7h,06h,0A0h,7Ah,09h,01h,8Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0AIBusyState@@QAE@PAVStateMachine@@@Z ENDP
_TEXT ENDS
END
