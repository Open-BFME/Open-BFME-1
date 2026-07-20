.386
.model flat
; ?changeVisualDisguise@StealthUpdate@@
; Exact 433B @ 0x00267D80; Open-BFME4
_TEXT SEGMENT
public ?changeVisualDisguise@StealthUpdate@@
?changeVisualDisguise@StealthUpdate@@ PROC
    db 6Ah, 0FFh, 68h, 33h, 0FDh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 7Ch, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 10h
    db 0E8h, 8Bh, 7Ch, 0DDh, 0FFh, 8Bh, 77h, 08h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 8Bh, 01h
    db 0FFh, 90h, 80h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 5Ch, 01h, 00h, 00h, 8Bh, 47h
    db 24h, 53h, 0BBh, 01h, 00h, 00h, 00h, 3Bh, 0C3h, 0Fh, 85h, 4Ah, 01h, 00h, 00h, 8Bh
    db 86h, 30h, 01h, 00h, 00h, 0F6h, 0C4h, 08h, 74h, 2Fh, 25h, 0FFh, 0F7h, 0FFh, 0FFh, 8Bh
    db 0CEh, 89h, 86h, 30h, 01h, 00h, 00h, 0E8h, 31h, 9Bh, 0DBh, 0FFh, 53h, 8Bh, 0CFh, 0E8h
    db 53h, 8Ah, 0DBh, 0FFh, 5Bh, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 7Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h
    db 0C9h, 74h, 1Eh, 8Bh, 11h, 6Ah, 00h, 0FFh, 92h, 00h, 01h, 00h, 00h, 85h, 0C0h, 76h
    db 10h, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 8Bh, 01h, 6Ah, 00h, 0FFh, 90h, 94h, 00h, 00h
    db 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 0F8h, 85h, 0FFh, 74h, 18h, 68h, 00h
    db 00h, 00h, 40h, 68h, 33h, 33h, 33h, 3Fh, 68h, 0CDh, 0CCh, 4Ch, 3Eh, 6Ah, 02h, 8Bh
    db 0CFh, 0E8h, 0Dh, 79h, 0DAh, 0FFh, 8Bh, 86h, 30h, 01h, 00h, 00h, 0F6h, 0C4h, 08h, 75h
    db 12h, 0Dh, 00h, 08h, 00h, 00h, 8Bh, 0CEh, 89h, 86h, 30h, 01h, 00h, 00h, 0E8h, 0AAh
    db 9Ah, 0DBh, 0FFh, 0A1h, 48h, 0D7h, 2Eh, 01h, 55h, 8Bh, 68h, 0Ch, 8Bh, 0CEh, 88h, 5Ch
    db 24h, 10h, 0E8h, 9Dh, 89h, 0DBh, 0FFh, 3Bh, 0C5h, 5Dh, 74h, 06h, 32h, 0DBh, 88h, 5Ch
    db 24h, 0Ch, 8Bh, 4Ch, 24h, 0Ch, 51h, 8Bh, 4Ch, 24h, 18h, 0E8h, 0A7h, 89h, 0DBh, 0FFh
    db 84h, 0DBh, 74h, 75h, 85h, 0FFh, 74h, 71h, 68h, 0C4h, 77h, 0Bh, 01h, 8Dh, 4Ch, 24h
    db 14h, 0E8h, 0Ah, 0Dh, 62h, 00h, 8Dh, 54h, 24h, 10h, 52h, 8Bh, 0CFh, 0C7h, 84h, 24h
    db 94h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 77h, 7Eh, 0DAh, 0FFh, 50h, 8Dh, 4Ch
    db 24h, 1Ch, 0E8h, 50h, 0FCh, 0DDh, 0FFh, 8Dh, 4Ch, 24h, 10h, 0C6h, 84h, 24h, 90h, 00h
    db 00h, 00h, 02h, 0E8h, 58h, 0FAh, 61h, 00h, 8Bh, 76h, 74h, 56h, 8Dh, 4Ch, 24h, 1Ch
    db 0E8h, 75h, 1Bh, 0DBh, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 8Dh, 54h, 24h
    db 18h, 52h, 0FFh, 50h, 44h, 8Dh, 4Ch, 24h, 18h, 0C7h, 84h, 24h, 90h, 00h, 00h, 00h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 1Ch, 0F0h, 0DBh, 0FFh, 5Bh, 8Bh, 8Ch, 24h, 84h, 00h, 00h
    db 00h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h
    db 0C3h
?changeVisualDisguise@StealthUpdate@@ ENDP
_TEXT ENDS
END
