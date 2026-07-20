.386
.model flat
; ?doSetRallyPoint@@YAXPAVObject@@ABUCoord3D@@@Z
; Exact 880B @ 0x00396D40; string-anchored RallyPointNoPath/Set Open-BFME4
_TEXT SEGMENT
public ?doSetRallyPoint@@YAXPAVObject@@ABUCoord3D@@@Z
?doSetRallyPoint@@YAXPAVObject@@ABUCoord3D@@@Z PROC
    db 6Ah, 0FFh, 68h, 0C4h, 0C7h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 34h, 53h, 56h, 57h, 8Bh, 7Ch, 24h, 50h, 8Bh
    db 0CFh, 0E8h, 2Bh, 92h, 0C8h, 0FFh, 8Ah, 0D8h, 8Bh, 44h, 24h, 54h, 8Bh, 08h, 8Bh, 50h
    db 04h, 8Bh, 40h, 08h, 89h, 4Ch, 24h, 10h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 4Ch
    db 0BBh, 0Eh, 01h, 89h, 54h, 24h, 18h, 89h, 44h, 24h, 1Ch, 0E8h, 47h, 40h, 0CAh, 0FFh
    db 8Dh, 4Ch, 24h, 1Ch, 8Bh, 0F0h, 0E8h, 0EFh, 61h, 0C8h, 0FFh, 8Bh, 0Dh, 04h, 0F5h, 2Eh
    db 01h, 56h, 0C7h, 44h, 24h, 4Ch, 00h, 00h, 00h, 00h, 0E8h, 5Bh, 2Fh, 0CBh, 0FFh, 50h
    db 8Dh, 4Ch, 24h, 20h, 0E8h, 47h, 59h, 0C9h, 0FFh, 8Bh, 44h, 24h, 5Ch, 85h, 0C0h, 0Fh
    db 85h, 1Dh, 01h, 00h, 00h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 8Dh, 54h
    db 24h, 1Ch, 52h, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 77h, 38h, 56h, 57h, 0E8h, 45h, 35h
    db 0CBh, 0FFh, 84h, 0C0h, 0Fh, 85h, 0Fh, 01h, 00h, 00h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h
    db 8Bh, 49h, 0Ch, 8Dh, 54h, 24h, 10h, 52h, 8Bh, 0C2h, 50h, 56h, 0E8h, 0A0h, 81h, 0C8h
    db 0FFh, 84h, 0C0h, 0Fh, 85h, 0F0h, 00h, 00h, 00h, 84h, 0DBh, 0Fh, 84h, 0ACh, 00h, 00h
    db 00h, 8Ah, 44h, 24h, 58h, 84h, 0C0h, 0Fh, 84h, 0A0h, 00h, 00h, 00h, 8Bh, 0Dh, 7Ch
    db 14h, 2Fh, 01h, 8Bh, 11h, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 58h, 6Ah, 00h, 68h, 30h
    db 0BBh, 0Eh, 01h, 50h, 0FFh, 52h, 28h, 0A1h, 8Ch, 14h, 2Fh, 01h, 8Bh, 08h, 50h, 0FFh
    db 51h, 34h, 0A0h, 0F8h, 0Ch, 2Fh, 01h, 83h, 0C4h, 08h, 0A8h, 01h, 75h, 50h, 83h, 0Dh
    db 0F8h, 0Ch, 2Fh, 01h, 01h, 68h, 14h, 0BBh, 0Eh, 01h, 8Dh, 4Ch, 24h, 58h, 0C6h, 44h
    db 24h, 4Ch, 01h, 0E8h, 58h, 1Dh, 4Fh, 00h, 6Ah, 00h, 8Dh, 54h, 24h, 58h, 52h, 0B9h
    db 70h, 0Ch, 2Fh, 01h, 0C6h, 44h, 24h, 50h, 02h, 0E8h, 88h, 0E4h, 0C8h, 0FFh, 8Dh, 4Ch
    db 24h, 54h, 0C6h, 44h, 24h, 48h, 01h, 0E8h, 0B4h, 0Ah, 4Fh, 00h, 68h, 90h, 0FEh, 06h
    db 01h, 0E8h, 90h, 0FFh, 65h, 00h, 83h, 0C4h, 04h, 0C6h, 44h, 24h, 48h, 00h, 8Dh, 44h
    db 24h, 10h, 50h, 0B9h, 70h, 0Ch, 2Fh, 01h, 0E8h, 0DBh, 0AFh, 0C6h, 0FFh, 8Bh, 0Dh, 68h
    db 0D6h, 2Eh, 01h, 8Bh, 11h, 68h, 70h, 0Ch, 2Fh, 01h, 0FFh, 52h, 44h, 8Dh, 4Ch, 24h
    db 1Ch, 0C7h, 44h, 24h, 48h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0E5h, 0BFh, 0C7h, 0FFh, 32h, 0C0h
    db 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 40h, 0C3h, 83h, 0C0h, 38h, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 4Ch, 24h
    db 10h, 89h, 54h, 24h, 14h, 89h, 44h, 24h, 18h, 8Bh, 0CFh, 0E8h, 4Eh, 0CEh, 0C8h, 0FFh
    db 85h, 0C0h, 74h, 0B9h, 8Bh, 10h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0C8h, 0FFh, 52h, 1Ch
    db 84h, 0DBh, 0Fh, 84h, 73h, 01h, 00h, 00h, 8Ah, 44h, 24h, 58h, 84h, 0C0h, 0Fh, 84h
    db 67h, 01h, 00h, 00h, 0C7h, 44h, 24h, 5Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 54h
    db 00h, 00h, 00h, 00h, 8Bh, 17h, 8Bh, 0CFh, 0C6h, 44h, 24h, 48h, 04h, 0FFh, 52h, 28h
    db 8Bh, 0F0h, 85h, 0F6h, 74h, 16h, 8Dh, 44h, 24h, 54h, 50h, 8Bh, 0CEh, 0E8h, 25h, 0CBh
    db 0CAh, 0FFh, 84h, 0C0h, 74h, 06h, 8Bh, 44h, 24h, 54h, 0EBh, 16h, 8Bh, 47h, 04h, 85h
    db 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 4Ch, 0B3h, 0C6h, 0FFh, 8Bh
    db 40h, 0Ch, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Ch, 38h, 07h, 01h
    db 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 11h, 50h, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 14h
    db 6Ah, 00h, 68h, 0FCh, 0BAh, 0Eh, 01h, 50h, 0FFh, 52h, 28h, 8Dh, 4Ch, 24h, 64h, 51h
    db 0E8h, 0EBh, 21h, 4Fh, 00h, 83h, 0C4h, 08h, 8Dh, 54h, 24h, 60h, 89h, 64h, 24h, 10h
    db 8Bh, 0CCh, 52h, 0E8h, 48h, 14h, 4Fh, 00h, 0A1h, 8Ch, 14h, 2Fh, 01h, 8Bh, 08h, 50h
    db 0FFh, 51h, 34h, 8Ah, 0Dh, 0F8h, 0Ch, 2Fh, 01h, 0B8h, 02h, 00h, 00h, 00h, 83h, 0C4h
    db 08h, 84h, 0C8h, 75h, 4Fh, 09h, 05h, 0F8h, 0Ch, 2Fh, 01h, 0B3h, 05h, 68h, 0ECh, 0BAh
    db 0Eh, 01h, 8Dh, 4Ch, 24h, 10h, 88h, 5Ch, 24h, 4Ch, 0E8h, 0D1h, 1Bh, 4Fh, 00h, 6Ah
    db 00h, 8Dh, 54h, 24h, 10h, 52h, 0B9h, 0E8h, 0Bh, 2Fh, 01h, 0C6h, 44h, 24h, 50h, 06h
    db 0E8h, 01h, 0E3h, 0C8h, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 88h, 5Ch, 24h, 48h, 0E8h, 2Eh, 09h
    db 4Fh, 00h, 68h, 80h, 0FEh, 06h, 01h, 0E8h, 0Ah, 0FEh, 65h, 00h, 83h, 0C4h, 04h, 0C6h
    db 44h, 24h, 48h, 04h, 8Dh, 44h, 24h, 10h, 50h, 0B9h, 0E8h, 0Bh, 2Fh, 01h, 0E8h, 55h
    db 0AEh, 0C6h, 0FFh, 8Bh, 0CFh, 0E8h, 0EAh, 97h, 0C8h, 0FFh, 8Bh, 40h, 24h, 50h, 0B9h, 0E8h
    db 0Bh, 2Fh, 01h, 0E8h, 40h, 3Ch, 0CAh, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h
    db 68h, 0E8h, 0Bh, 2Fh, 01h, 0FFh, 52h, 44h, 85h, 0F6h, 74h, 13h, 8Ah, 86h, 0ACh, 03h
    db 00h, 00h, 84h, 0C0h, 74h, 09h, 0A1h, 0F8h, 33h, 2Fh, 01h, 0C6h, 40h, 24h, 01h, 8Dh
    db 4Ch, 24h, 54h, 0C6h, 44h, 24h, 48h, 03h, 0E8h, 53h, 11h, 4Fh, 00h, 8Dh, 4Ch, 24h
    db 5Ch, 0C6h, 44h, 24h, 48h, 00h, 0E8h, 45h, 11h, 4Fh, 00h, 8Dh, 4Ch, 24h, 1Ch, 0C7h
    db 44h, 24h, 48h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 17h, 0BEh, 0C7h, 0FFh, 8Bh, 4Ch, 24h, 40h
    db 5Fh, 5Eh, 0B0h, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 40h, 0C3h
?doSetRallyPoint@@YAXPAVObject@@ABUCoord3D@@@Z ENDP
_TEXT ENDS
END
