.386
.model flat

; ?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z
; Exact 554B @ 0x00111980; caller-anchored from addGameToAvailableList@0x111C40 via ILT 0x83D7
; Drift 0x145970 was INSIDE parseModuleName@ThingTemplate; BFME FileSystem path not ZH XferLoad; returns Bool
_TEXT SEGMENT
public ?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z
?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z PROC
    db 55h,8Bh,0ECh,6Ah,0FFh,68h,0D3h,0DDh,0FFh,00h,64h,0A1h,00h,00h,00h,00h
    db 50h,64h,89h,25h,00h,00h,00h,00h,81h,0ECh,94h,00h,00h,00h,53h,56h
    db 57h,89h,65h,0F0h,89h,4Dh,0E4h,8Bh,45h,08h,33h,0FFh,32h,0DBh,3Bh,0C7h
    db 89h,7Dh,0FCh,74h,55h,66h,39h,78h,04h,74h,4Fh,39h,7Dh,0Ch,74h,4Ah
    db 8Bh,0Dh,48h,0CBh,34h,01h,83h,0C0h,08h,6Ah,41h,50h,0E8h,8Fh,6Eh,8Bh
    db 00h,8Bh,0F0h,3Bh,0F7h,74h,33h,57h,57h,57h,8Dh,4Dh,0C4h,0E8h,0BEh,72h
    db 8Ch,00h,8Dh,45h,0E8h,50h,56h,8Dh,4Dh,0C4h,0C6h,45h,0FCh,01h,0E8h,0EDh
    db 6Fh,8Ch,00h,84h,0C0h,75h,37h,8Bh,16h,8Bh,0CEh,0FFh,52h,08h,8Dh,4Dh
    db 0C4h,0C6h,45h,0FCh,00h,0E8h,0F6h,72h,8Ch,00h,8Dh,4Dh,08h,0C7h,45h,0FCh
    db 0FFh,0FFh,0FFh,0FFh,0E8h,27h,5Fh,77h,00h,32h,0C0h,8Bh,4Dh,0F4h,64h,89h
    db 0Dh,00h,00h,00h,00h,5Fh,5Eh,5Bh,8Bh,0E5h,5Dh,0C2h,08h,00h,83h,7Dh
    db 0E8h,01h,76h,0Ch,8Bh,06h,8Bh,0CEh,0FFh,50h,08h,0EBh,0C1h,8Dh,49h,00h
    db 84h,0DBh,0Fh,85h,23h,01h,00h,00h,89h,7Dh,0ECh,8Bh,55h,0C4h,8Dh,4Dh
    db 0ECh,51h,8Dh,4Dh,0C4h,0C6h,45h,0FCh,02h,0FFh,52h,68h,0A1h,0B0h,0BFh,2Ah
    db 01h,50h,8Dh,4Dh,0ECh,0E8h,7Eh,0EBh,0F2h,0FFh,85h,0C0h,75h,0Fh,0B3h,01h
    db 8Dh,4Dh,0ECh,88h,5Dh,0FCh,0E8h,0C5h,5Eh,77h,00h,0EBh,0C3h,57h,51h,8Dh
    db 55h,0ECh,89h,65h,0C0h,8Bh,0CCh,52h,0E8h,0D3h,60h,77h,00h,8Bh,4Dh,0E4h
    db 0E8h,10h,8Ch,0EFh,0FFh,3Bh,0C7h,75h,1Ch,57h,8Dh,45h,0B8h,57h,50h,0E8h
    db 7Ch,47h,8Ch,00h,83h,0C4h,0Ch,68h,5Ch,0FEh,1Dh,01h,8Dh,4Dh,0B8h,51h
    db 0E8h,4Bh,52h,8Eh,00h,8Bh,45h,0ECh,3Bh,0C7h,74h,05h,83h,0C0h,08h,0EBh
    db 05h,0B8h,8Bh,38h,07h,01h,68h,40h,93h,08h,01h,50h,0FFh,15h,3Ch,93h
    db 35h,01h,83h,0C4h,08h,85h,0C0h,75h,74h,8Dh,8Dh,60h,0FFh,0FFh,0FFh,0E8h
    db 0E6h,07h,0EFh,0FFh,68h,14h,6Ch,07h,01h,8Dh,4Dh,0C4h,0C6h,45h,0FCh,04h
    db 0E8h,1Bh,72h,8Ch,00h,8Bh,45h,0C4h,8Dh,95h,68h,0FFh,0FFh,0FFh,52h,8Dh
    db 4Dh,0C4h,0FFh,50h,30h,8Dh,4Dh,0C4h,0E8h,0A3h,6Fh,8Ch,00h,8Dh,8Dh,78h
    db 0FFh,0FFh,0FFh,51h,8Bh,4Dh,0Ch,0C7h,45h,0FCh,03h,00h,00h,00h,0E8h,31h
    db 76h,0F1h,0FFh,8Dh,8Dh,60h,0FFh,0FFh,0FFh,0B3h,01h,0C6h,45h,0FCh,02h,0E8h
    db 0B3h,23h,0F2h,0FFh,8Dh,4Dh,0ECh,88h,5Dh,0FCh,0E8h,01h,5Eh,77h,00h,0E9h
    db 0FCh,0FEh,0FFh,0FFh,6Ah,00h,6Ah,00h,0E8h,0B3h,51h,8Eh,00h,68h,14h,6Ch
    db 07h,01h,8Dh,4Dh,0C4h,0E8h,0E6h,72h,8Ch,00h,8Dh,4Dh,0ECh,0C6h,45h,0FCh
    db 01h,0E8h,0DAh,5Dh,77h,00h,0E9h,0D5h,0FEh,0FFh,0FFh,8Dh,4Dh,0C4h,0E8h,2Dh
    db 6Fh,8Ch,00h,8Bh,16h,8Bh,0CEh,0FFh,52h,08h,8Dh,4Dh,0C4h,0C6h,45h,0FCh
    db 00h,0E8h,7Ah,71h,8Ch,00h,8Dh,4Dh,08h,0C7h,45h,0FCh,0FFh,0FFh,0FFh,0FFh
    db 0E8h,0ABh,5Dh,77h,00h,8Bh,4Dh,0F4h,5Fh,5Eh,0B0h,01h,64h,89h,0Dh,00h
    db 00h,00h,00h,5Bh,8Bh,0E5h,5Dh,0C2h,08h,00h
?getSaveGameInfoFromFile@GameState@@QAEXVAsciiString@@PAVSaveGameInfo@@@Z ENDP
_TEXT ENDS
END
