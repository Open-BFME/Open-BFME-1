.386
.model flat

; ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
; Exact 204 retail bytes @ 0x002F54C0
; Identity: getTeamNamed(SE+0x44), createGroup(TheAI), getTeamAsAIGroup,
; findCommandButton, SP/source branch, getUnitNamed(SE+0x68), isValidToUseOn,
; groupDoCommandButtonAtObject; ret 0xC. Queue RVA 0x614F9B was inside
; mislocated NearestKindof MASM claim (INI parser).
_TEXT SEGMENT
public ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z PROC
    db 51h,8Bh,44h,24h,08h,53h,55h,56h
    db 57h,6Ah,00h,51h,89h,64h,24h,18h
    db 8Bh,0CCh,50h,0E8h,88h,26h,59h,00h
    db 8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh,11h
    db 0FFh,52h,44h,8Bh,0F0h,85h,0F6h,0Fh
    db 84h,97h,00h,00h,00h,8Bh,0Dh,14h
    db 0F2h,2Eh,01h,0E8h,78h,60h,0D4h,0FFh
    db 8Bh,0E8h,55h,8Bh,0CEh,0E8h,0BFh,0D9h
    db 0D2h,0FFh,8Bh,44h,24h,1Ch,8Bh,0Dh
    db 0F8h,33h,2Fh,01h,50h,0E8h,8Bh,60h
    db 0D4h,0FFh,8Bh,0D8h,85h,0DBh,74h,6Ch
    db 8Bh,4Bh,34h,85h,0C9h,74h,22h,8Bh
    db 41h,04h,85h,0C0h,74h,0Eh,8Bh,48h
    db 04h,85h,0C9h,74h,05h,0E8h,2Fh,37h
    db 0D5h,0FFh,8Bh,0C8h,8Bh,41h,10h,50h
    db 8Bh,0CDh,0E8h,0D7h,39h,0D2h,0FFh,0EBh
    db 0Bh,8Bh,43h,10h,50h,8Bh,0CDh,0E8h
    db 80h,77h,0D4h,0FFh,8Bh,0F8h,85h,0FFh
    db 74h,32h,8Bh,0Dh,6Ch,07h,2Fh,01h
    db 8Bh,44h,24h,20h,8Bh,11h,50h,0FFh
    db 52h,68h,8Bh,0F0h,85h,0F6h,74h,1Ch
    db 6Ah,01h,6Ah,00h,56h,57h,8Bh,0CBh
    db 0E8h,0D5h,06h,0D1h,0FFh,84h,0C0h,74h
    db 0Bh,6Ah,01h,56h,53h,8Bh,0CDh,0E8h
    db 4Ch,6Bh,0D2h,0FFh,5Fh,5Eh,5Dh,5Bh
    db 59h,0C2h,0Ch,00h
?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z ENDP
_TEXT ENDS
END
