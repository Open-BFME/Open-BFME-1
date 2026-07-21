.386
.model flat

; ?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
; Exact 144 retail bytes @ 0x002F95A0
; Queue RVA 0x003992C6 was INSIDE already-matched logicMessageDispatcher (misplaced drift).
; True body sits between createUnitOnTeamAt and doDisplayCounter; switch case TEAM_ATTACK_NAMED.
_TEXT SEGMENT
public ?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z
?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z PROC
    db 51h,53h,55h,8Bh,6Ch,24h,10h,56h
    db 57h,6Ah,00h,51h,89h,64h,24h,18h
    db 8Bh,0CCh,55h,0E8h,0A8h,0E5h,58h,00h
    db 8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh,01h
    db 0FFh,50h,44h,8Bh,0F8h,85h,0FFh,74h
    db 5Fh,8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh
    db 44h,24h,1Ch,8Bh,11h,50h,0FFh,52h
    db 68h,8Bh,0D8h,85h,0DBh,74h,49h,8Bh
    db 0Dh,14h,0F2h,2Eh,01h,0E8h,86h,1Fh
    db 0D4h,0FFh,8Bh,0F0h,85h,0F6h,74h,38h
    db 56h,8Bh,0CFh,0E8h,0C9h,98h,0D2h,0FFh
    db 68h,08h,03h,0Dh,01h,8Bh,0CDh,0E8h
    db 16h,1Ah,0D5h,0FFh,85h,0C0h,75h,0Fh
    db 50h,68h,0FFh,0FFh,0FFh,7Fh,53h,50h
    db 8Bh,0CEh,0E8h,0BAh,86h,0D4h,0FFh,6Ah
    db 01h,68h,0FFh,0FFh,0FFh,7Fh,53h,6Ah
    db 00h,8Bh,0CEh,0E8h,0A9h,86h,0D4h,0FFh
    db 5Fh,5Eh,5Dh,5Bh,59h,0C2h,08h,00h
?doTeamAttackNamed@ScriptActions@@IAEXABVAsciiString@@0@Z ENDP
_TEXT ENDS
END
