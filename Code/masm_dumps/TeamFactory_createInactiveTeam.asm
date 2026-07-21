.386
.model flat

; ?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z
; Exact 390 retail bytes @ 0x000F7AB0
; Identity: public thunk 0x0000D15C -> this body; createTeam@0xF7CA0 calls thunk then setActive
; (Team+0x31/+0x32). findTeamPrototype 2-arg map lookup; Team sizeof 0x110; m_uniqueTeamID@+0x1c.
; Queue RVA 0x00853F0F was int3-padded *.ini path helper (string 0x1118150) — wrong function.
; BFME signature is 2x AsciiString const& (ret 8); ZH 1-arg C++ cannot emit matching shape.
_TEXT SEGMENT
public ?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z
?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z PROC
    db 64h,0A1h,00h,00h,00h,00h,6Ah,0FFh,68h,0DBh,0BFh,0FFh,00h,50h,8Bh,44h
    db 24h,14h,64h,89h,25h,00h,00h,00h,00h,55h,56h,57h,8Bh,0F9h,8Bh,4Ch
    db 24h,1Ch,50h,51h,8Bh,0CFh,0E8h,5Eh,8Fh,0F4h,0FFh,8Bh,0F0h,85h,0F6h,75h
    db 17h,68h,04h,00h,1Eh,01h,8Dh,54h,24h,24h,52h,0C7h,44h,24h,28h,03h
    db 00h,0ADh,0DEh,0E8h,08h,0F2h,8Fh,00h,0F6h,46h,18h,01h,0Fh,84h,83h,00h
    db 00h,00h,8Bh,0AEh,74h,02h,00h,00h,85h,0EDh,74h,79h,8Ah,86h,0ECh,01h
    db 00h,00h,84h,0C0h,74h,59h,0C7h,44h,24h,20h,00h,00h,00h,00h,8Bh,0Dh
    db 6Ch,07h,2Fh,01h,8Bh,01h,8Dh,54h,24h,20h,52h,8Dh,96h,0E8h,01h,00h
    db 00h,52h,83h,0C6h,10h,56h,0C7h,44h,24h,20h,00h,00h,00h,00h,0FFh,90h
    db 0D4h,00h,00h,00h,85h,0C0h,74h,16h,8Bh,40h,20h,8Bh,0Dh,6Ch,07h,2Fh
    db 01h,8Bh,11h,6Ah,00h,50h,8Dh,44h,24h,28h,50h,0FFh,52h,64h,8Dh,4Ch
    db 24h,20h,0C7h,44h,24h,14h,0FFh,0FFh,0FFh,0FFh,0E8h,0D1h,0FDh,78h,00h,8Bh
    db 0C5h,8Bh,4Ch,24h,0Ch,64h,89h,0Dh,00h,00h,00h,00h,5Fh,5Eh,5Dh,83h
    db 0C4h,0Ch,0C2h,08h,00h,68h,10h,01h,00h,00h,0E8h,0A1h,0A3h,78h,00h,83h
    db 0C4h,04h,89h,44h,24h,20h,85h,0C0h,0C7h,44h,24h,14h,01h,00h,00h,00h
    db 74h,16h,8Bh,6Fh,1Ch,45h,89h,6Fh,1Ch,8Bh,0FDh,57h,56h,8Bh,0C8h,0E8h
    db 84h,9Ah,0F3h,0FFh,8Bh,0F8h,0EBh,02h,33h,0FFh,8Ah,86h,0ECh,01h,00h,00h
    db 83h,0CDh,0FFh,84h,0C0h,89h,6Ch,24h,14h,74h,55h,0C7h,44h,24h,1Ch,00h
    db 00h,00h,00h,8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh,11h,8Dh,44h,24h,1Ch,50h
    db 8Dh,86h,0E8h,01h,00h,00h,50h,83h,0C6h,10h,56h,0C7h,44h,24h,20h,02h
    db 00h,00h,00h,0FFh,92h,0D4h,00h,00h,00h,85h,0C0h,74h,16h,8Bh,40h,20h
    db 8Bh,0Dh,6Ch,07h,2Fh,01h,8Bh,11h,6Ah,00h,50h,8Dh,44h,24h,24h,50h
    db 0FFh,52h,64h,8Dh,4Ch,24h,1Ch,89h,6Ch,24h,14h,0E8h,20h,0FDh,78h,00h
    db 8Bh,4Ch,24h,0Ch,8Bh,0C7h,5Fh,5Eh,64h,89h,0Dh,00h,00h,00h,00h,5Dh
    db 83h,0C4h,0Ch,0C2h,08h,00h
?createInactiveTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z ENDP
_TEXT ENDS
END
