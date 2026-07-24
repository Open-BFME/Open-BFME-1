.386
.model flat
; ?removeMilitarySubtitle@InGameUI@@UAEXXZ
; Exact 154B @ 0x004431B0; certified retail InGameUI subtitle cleanup
_TEXT SEGMENT
public ?removeMilitarySubtitle@InGameUI@@UAEXXZ
?removeMilitarySubtitle@InGameUI@@UAEXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 18h, 08h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 87h, 00h, 00h
    db 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 53h, 57h, 0FFh, 90h, 90h, 01h, 00h
    db 00h, 33h, 0DBh, 0BFh, 08h, 00h, 00h, 00h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 86h, 18h, 08h, 00h, 00h, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 04h, 07h, 8Bh
    db 11h, 50h, 0FFh, 52h, 28h, 8Bh, 8Eh, 18h, 08h, 00h, 00h, 0C7h, 04h, 0Fh, 00h, 00h
    db 00h, 00h, 8Bh, 96h, 18h, 08h, 00h, 00h, 8Bh, 42h, 2Ch, 43h, 83h, 0C7h, 04h, 3Bh
    db 0D8h, 76h, 0CDh, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 52h, 28h, 8Bh, 01h, 52h, 0FFh
    db 50h, 28h, 8Bh, 0BEh, 18h, 08h, 00h, 00h, 85h, 0FFh, 74h, 10h, 8Bh, 0CFh, 0E8h, 0AEh
    db 5Ah, 0BDh, 0FFh, 57h, 0E8h, 77h, 0ECh, 43h, 00h, 83h, 0C4h, 04h, 5Fh, 0C7h, 86h, 18h
    db 08h, 00h, 00h, 00h, 00h, 00h, 00h, 5Bh, 5Eh, 0C3h
?removeMilitarySubtitle@InGameUI@@UAEXXZ ENDP
_TEXT ENDS
END
