.386
.model flat

; ?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z
; Exact 169 retail bytes @ 0x002F9F10
; Identity: getUnitNamed(SE vtbl+0x68), getWaypointByName(TerrainLogic vtbl+0x7c),
; getCommandSetString+findCommandSet, loop MAX_COMMANDS=0x14, name non-empty + compare,
; doCommandButtonAtPosition(button, waypoint+0xC, CMD_FROM_SCRIPT=1); ret 0xC.
; Queue RVA 0x5AF3BD was INSIDE mega FUN_009ade90 (mid-call residual), not this body.
_TEXT SEGMENT
public ?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z
?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z PROC
    db 8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh,54h
    db 24h,04h,8Bh,01h,53h,55h,56h,57h
    db 52h,0FFh,50h,68h,51h,8Bh,0F8h,8Bh
    db 44h,24h,20h,89h,64h,24h,18h,8Bh
    db 0CCh,50h,0E8h,29h,0DCh,58h,00h,8Bh
    db 0Dh,0CCh,0F4h,2Eh,01h,8Bh,11h,0FFh
    db 52h,7Ch,85h,0FFh,8Bh,0E8h,74h,6Ah
    db 85h,0EDh,74h,66h,8Bh,0CFh,0E8h,6Dh
    db 0FEh,0D2h,0FFh,8Bh,0Dh,0F8h,33h,2Fh
    db 01h,50h,0E8h,6Bh,0EDh,0D4h,0FFh,85h
    db 0C0h,89h,44h,24h,14h,74h,4Bh,33h
    db 0DBh,0EBh,05h,8Bh,44h,24h,14h,90h
    db 53h,8Bh,0C8h,0E8h,08h,0A0h,0D0h,0FFh
    db 8Bh,0F0h,85h,0F6h,74h,2Eh,8Bh,46h
    db 0Ch,85h,0C0h,8Dh,4Eh,0Ch,74h,24h
    db 66h,83h,78h,04h,00h,74h,1Dh,8Bh
    db 44h,24h,18h,50h,0E8h,2Ch,81h,0D2h
    db 0FFh,85h,0C0h,75h,0Fh,50h,6Ah,01h
    db 8Dh,4Dh,0Ch,51h,56h,8Bh,0CFh,0E8h
    db 48h,0CFh,0D2h,0FFh,43h,83h,0FBh,14h
    db 7Ch,0B9h,5Fh,5Eh,5Dh,5Bh,0C2h,0Ch
    db 00h
?doNamedUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z ENDP
_TEXT ENDS
END
