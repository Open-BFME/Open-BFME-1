.386
.model flat
; ?CreditsMenuInit@@YAXPAVWindowLayout@@PAX@Z
; Exact 407B @ 0x004C6C60; unique CreditsMenu.wnd:ParentCreditsWindow and Credits audio event.
_TEXT SEGMENT
public ?CreditsMenuInit@@YAXPAVWindowLayout@@PAX@Z
?CreditsMenuInit@@YAXPAVWindowLayout@@PAX@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Bh, 0Dh, 58h, 4Bh, 2Fh, 01h, 6Ah, 0FFh, 68h, 36h
    db 96h, 02h, 01h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 78h, 6Ah, 00h
    db 0E8h, 6Dh, 0F7h, 0B3h, 0FFh, 8Bh, 0Dh, 60h, 12h, 2Fh, 01h, 85h, 0C9h, 74h, 06h, 8Bh
    db 01h, 6Ah, 01h, 0FFh, 10h, 6Ah, 44h, 0E8h, 94h, 0B2h, 3Bh, 00h, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 04h, 85h, 0C0h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 74h, 09h, 8Bh, 0C8h, 0E8h, 7Eh, 0A8h, 0B3h, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 60h, 12h
    db 2Fh, 01h, 8Bh, 10h, 8Bh, 0C8h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 52h, 08h, 8Bh, 0Dh, 60h, 12h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h, 04h, 68h
    db 64h, 0E0h, 0Fh, 01h, 8Dh, 4Ch, 24h, 04h, 0E8h, 0D3h, 1Eh, 3Ch, 00h, 8Bh, 04h, 24h
    db 85h, 0C0h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 74h, 05h, 83h
    db 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 50h
    db 0E8h, 0C2h, 40h, 0B7h, 0FFh, 8Dh, 0Ch, 24h, 0A3h, 3Ch, 39h, 2Fh, 01h, 0C7h, 84h, 24h
    db 80h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 13h, 0Ch, 3Ch, 00h, 0A1h, 3Ch, 39h
    db 2Fh, 01h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 50h, 6Ah, 00h, 0FFh, 92h, 0DCh
    db 00h, 00h, 00h, 8Bh, 8Ch, 24h, 88h, 00h, 00h, 00h, 8Bh, 11h, 6Ah, 00h, 0A3h, 40h
    db 39h, 2Fh, 01h, 0FFh, 52h, 10h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 15h, 40h, 39h
    db 2Fh, 01h, 8Bh, 01h, 52h, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 0Dh, 68h, 0D6h, 2Eh
    db 01h, 8Bh, 01h, 6Ah, 00h, 6Ah, 01h, 6Ah, 02h, 0FFh, 50h, 6Ch, 68h, 58h, 0E0h, 0Fh
    db 01h, 8Dh, 4Ch, 24h, 08h, 0E8h, 36h, 1Eh, 3Ch, 00h, 6Ah, 02h, 8Dh, 4Ch, 24h, 08h
    db 51h, 8Dh, 4Ch, 24h, 10h, 0C7h, 84h, 24h, 88h, 00h, 00h, 00h, 02h, 00h, 00h, 00h
    db 0E8h, 61h, 0E5h, 0B5h, 0FFh, 8Dh, 4Ch, 24h, 04h, 0C6h, 84h, 24h, 80h, 00h, 00h, 00h
    db 04h, 0E8h, 8Ah, 0Bh, 3Ch, 00h, 6Ah, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0Eh, 58h, 0B6h
    db 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 08h, 50h, 0FFh, 52h
    db 44h, 8Dh, 4Ch, 24h, 08h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 50h, 01h, 0B6h, 0FFh, 8Bh, 4Ch, 24h, 78h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 84h, 00h, 00h, 00h, 0C3h
?CreditsMenuInit@@YAXPAVWindowLayout@@PAX@Z ENDP
_TEXT ENDS
END
