.386
.model flat
; ?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z
; Exact 61B @ 0x5A4BA0; Open-BFME4+Grok
_TEXT SEGMENT
public ?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z
?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z PROC
    db 8Ah, 81h, 0A5h, 4Dh, 00h, 00h, 84h, 0C0h, 74h, 1Fh, 8Ah, 81h, 0A3h, 4Dh, 00h, 00h
    db 8Ah, 91h, 0A4h, 4Dh, 00h, 00h, 88h, 81h, 0A1h, 4Dh, 00h, 00h, 88h, 91h, 0A2h, 4Dh
    db 00h, 00h, 0C6h, 81h, 0A5h, 4Dh, 00h, 00h, 00h, 8Bh, 01h, 8Dh, 91h, 0A2h, 4Dh, 00h
    db 00h, 52h, 8Bh, 54h, 24h, 08h, 52h, 0FFh, 50h, 5Ch, 0C2h, 04h, 00h
?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z ENDP
_TEXT ENDS
END
