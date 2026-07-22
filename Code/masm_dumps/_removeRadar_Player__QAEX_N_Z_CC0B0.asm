.386
.model flat

; ?removeRadar@Player@@QAEX_N@Z
; Exact 215 retail bytes @ 0x000CC0B0; sibling of addRadar@0xCBFA0 /
; disableRadar body@0xCC1C0 / enableRadar body@0xCC2C0 (field cluster
; m_radarCount@+0x58 m_disableProofRadarCount@+0x5c m_radarDisabled@+0x60).
_TEXT SEGMENT
public ?removeRadar@Player@@QAEX_N@Z
?removeRadar@Player@@QAEX_N@Z PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 18h, 96h, 0FFh, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 70h, 56h, 8Bh, 0F1h, 8Ah, 56h, 60h, 84h, 0D2h
    db 74h, 0Bh, 8Bh, 46h, 5Ch, 85h, 0C0h, 75h, 04h, 32h, 0C0h, 0EBh, 08h, 8Bh, 46h, 58h
    db 85h, 0C0h, 0Fh, 9Fh, 0C0h, 8Bh, 4Eh, 58h, 53h, 8Ah, 9Ch, 24h, 88h, 00h, 00h, 00h
    db 49h, 84h, 0DBh, 89h, 4Eh, 58h, 74h, 03h, 0FFh, 4Eh, 5Ch, 84h, 0C0h, 5Bh, 74h, 75h
    db 84h, 0D2h, 74h, 07h, 8Bh, 46h, 5Ch, 85h, 0C0h, 74h, 09h, 85h, 0C9h, 0Fh, 9Fh, 0C0h
    db 84h, 0C0h, 75h, 61h, 8Bh, 0CEh, 0E8h, 0D5h, 80h, 0F4h, 0FFh, 84h, 0C0h, 74h, 56h, 8Bh
    db 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 0FFh, 90h, 24h, 01h, 00h, 00h, 05h, 0C0h, 01h
    db 00h, 00h, 50h, 8Dh, 4Ch, 24h, 08h, 0E8h, 0EBh, 0B9h, 0F7h, 0FFh, 8Bh, 76h, 24h, 56h
    db 8Dh, 4Ch, 24h, 08h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h
    db 34h, 0EBh, 0F6h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 04h
    db 50h, 0FFh, 52h, 44h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 7Ch, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0C0h, 0ADh, 0F5h, 0FFh, 8Bh, 4Ch, 24h, 74h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 7Ch, 0C2h, 04h, 00h
?removeRadar@Player@@QAEX_N@Z ENDP
_TEXT ENDS
END
