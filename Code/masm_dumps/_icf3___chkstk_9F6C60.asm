.386
.model flat
; __chkstk
; Exact 61B @ 0x9F6C60; Open-BFME4+Grok
_TEXT SEGMENT
public __chkstk
__chkstk PROC
    db 3Dh, 00h, 10h, 00h, 00h, 73h, 0Eh, 0F7h, 0D8h, 03h, 0C4h, 83h, 0C0h, 04h, 85h, 00h
    db 94h, 8Bh, 00h, 50h, 0C3h, 51h, 8Dh, 4Ch, 24h, 08h, 81h, 0E9h, 00h, 10h, 00h, 00h
    db 2Dh, 00h, 10h, 00h, 00h, 85h, 01h, 3Dh, 00h, 10h, 00h, 00h, 73h, 0ECh, 2Bh, 0C8h
    db 8Bh, 0C4h, 85h, 01h, 8Bh, 0E1h, 8Bh, 08h, 8Bh, 40h, 04h, 50h, 0C3h
__chkstk ENDP
_TEXT ENDS
END
