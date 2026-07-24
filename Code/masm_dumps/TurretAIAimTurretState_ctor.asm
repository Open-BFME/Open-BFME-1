.386
.model flat

; ??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z
; Exact 46B @ 0x0018DA10. Queue RVA 0x0018DCAB was mid-instruction inside
; the matched TurretStateMachine constructor. The true body is anchored by
; the "TurretAIAimTurretState" string, TurretState base ctor, and vtable store.
_TEXT SEGMENT
public ??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z
??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z PROC
    db 51h,56h,51h,8Bh,0F1h,89h,64h,24h,08h,8Bh,0CCh,68h,0A4h,0BDh,09h,01h
    db 0E8h,09Bh,0B1h,06Fh,00h,08Bh,44h,24h,10h,50h,08Bh,0CEh,0E8h,26h,60h,0E8h
    db 0FFh,0C7h,06h,50h,0BDh,09h,01h,08Bh,0C6h,5Eh,59h,0C2h,04h,00h
??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z ENDP
_TEXT ENDS
END
