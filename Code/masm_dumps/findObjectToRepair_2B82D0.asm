.386
.model flat

; ?findObjectToRepair@@YAPAVObject@@PAV1@@Z
; Exact 505B @ 0x002B82D0; certified DozerPrimaryIdleState repair-search callee.
_TEXT SEGMENT
public ?findObjectToRepair@@YAPAVObject@@PAV1@@Z
?findObjectToRepair@@YAPAVObject@@PAV1@@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 60h, 34h, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 68h, 53h, 33h, 0DBh, 3Bh, 0FBh, 74h, 0Ah, 8Bh
    db 8Fh, 04h, 02h, 00h, 00h, 3Bh, 0CBh, 75h, 12h, 33h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 68h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 74h, 0C3h, 8Bh, 01h, 55h, 56h, 0FFh
    db 90h, 3Ch, 01h, 00h, 00h, 8Bh, 0F0h, 89h, 5Ch, 24h, 0Ch, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 89h, 5Ch, 24h, 34h, 0C7h, 44h, 24h, 30h, 0D0h, 5Dh, 08h, 01h, 89h
    db 7Ch, 24h, 38h, 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch, 24h, 1Ch, 89h, 4Ch, 24h, 20h, 89h
    db 4Ch, 24h, 24h, 89h, 4Ch, 24h, 28h, 68h, 0B8h, 0D8h, 2Eh, 01h, 8Dh, 54h, 24h, 1Ch
    db 89h, 4Ch, 24h, 30h, 0Dh, 80h, 00h, 00h, 00h, 52h, 8Dh, 4Ch, 24h, 44h, 89h, 9Ch
    db 24h, 84h, 00h, 00h, 00h, 89h, 44h, 24h, 20h, 0E8h, 8Fh, 0FFh, 0D7h, 0FFh, 8Bh, 0E8h
    db 8Bh, 0CFh, 0C6h, 44h, 24h, 7Ch, 01h, 0E8h, 0A8h, 84h, 0D6h, 0FFh, 89h, 5Ch, 24h, 1Ch
    db 0C7h, 44h, 24h, 18h, 44h, 71h, 09h, 01h, 89h, 44h, 24h, 20h, 6Ah, 00h, 8Dh, 44h
    db 24h, 34h, 50h, 8Bh, 0CDh, 0C6h, 84h, 24h, 84h, 00h, 00h, 00h, 02h, 8Dh, 5Fh, 38h
    db 0E8h, 3Bh, 0A7h, 73h, 00h, 50h, 8Dh, 4Ch, 24h, 20h, 0E8h, 31h, 0A7h, 73h, 00h, 8Bh
    db 16h, 50h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 51h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h
    db 0D9h, 1Ch, 24h, 53h, 8Dh, 44h, 24h, 28h, 50h, 0E8h, 92h, 0A5h, 73h, 00h, 0B8h, 5Ch
    db 3Bh, 08h, 01h, 89h, 44h, 24h, 18h, 89h, 44h, 24h, 3Ch, 0C6h, 44h, 24h, 7Ch, 04h
    db 89h, 44h, 24h, 30h, 0EBh, 0Ah, 0DDh, 0D8h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 14h, 8Bh, 48h, 04h, 8Bh, 50h, 0Ch, 3Bh, 0D1h, 74h, 67h, 8Bh, 0CAh
    db 8Bh, 31h, 83h, 0C1h, 08h, 85h, 0F6h, 89h, 48h, 0Ch, 74h, 55h, 8Bh, 0Dh, 00h, 0D7h
    db 2Eh, 01h, 6Ah, 02h, 56h, 57h, 0E8h, 0B9h, 0B4h, 0D7h, 0FFh, 84h, 0C0h, 74h, 0D1h, 0D9h
    db 03h, 8Bh, 44h, 24h, 0Ch, 85h, 0C0h, 0D8h, 66h, 38h, 0D9h, 43h, 04h, 0D8h, 66h, 3Ch
    db 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 75h, 0Ch, 0D9h, 5Ch, 24h, 10h
    db 89h, 74h, 24h, 0Ch, 0DDh, 0D8h, 0EBh, 9Eh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 54h, 24h, 10h
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 8Fh, 0D9h, 5Ch, 24h, 10h, 89h, 74h, 24h, 0Ch, 0EBh
    db 8Fh, 8Bh, 44h, 24h, 14h, 0FFh, 48h, 10h, 8Bh, 44h, 24h, 14h, 8Bh, 48h, 10h, 85h
    db 0C9h, 0C7h, 44h, 24h, 7Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 38h, 8Bh, 08h, 85h, 0C9h, 8Bh
    db 0F0h, 74h, 27h, 8Bh, 40h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh, 80h
    db 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 15h, 9Ah, 5Ch, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah
    db 50h, 51h, 0E8h, 49h, 61h, 57h, 00h, 83h, 0C4h, 08h, 56h, 0E8h, 00h, 9Ah, 5Ch, 00h
    db 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 74h, 8Bh, 44h, 24h, 0Ch, 5Eh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 74h, 0C3h
?findObjectToRepair@@YAPAVObject@@PAV1@@Z ENDP
_TEXT ENDS
END
