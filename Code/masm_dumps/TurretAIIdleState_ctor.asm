.386
.model flat

; ??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z
; Exact 53B @ 0x0018D930. Drift 0x18DC07 was INSIDE matched TurretStateMachine
; ctor (0x18DB84+658) — mid-instruction of the inlined newInstance sequence
; (shape ratio 36% was coincidence on surrounding defineState code). True body
; is string-anchored on "TurretAIIdleState" and builds the State debug-name
; via StringBase/AsciiString(char*) @ 0x888BC0; stores m_nextIdleScan=0 at +0x24.
; Sibling pattern: TurretAIIdleScanState_ctor.asm / TurretAIRecenterTurretState_ctor.asm.
_TEXT SEGMENT
public ??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z
??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0C4h,0BCh,09h,01h
    db 0E8h,7Bh,0B2h,6Fh,00h,8Bh,44h,24h,10h,50h,8Bh,0CEh,0E8h,06h,61h,0E8h
    db 0FFh,0C7h,06h,70h,0BCh,09h,01h,0C7h,46h,24h,00h,00h,00h,00h,8Bh,0C6h
    db 5Eh,59h,0C2h,04h,00h
??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z ENDP
_TEXT ENDS
END
