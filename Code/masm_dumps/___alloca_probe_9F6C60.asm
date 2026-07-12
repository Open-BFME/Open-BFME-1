.386
.model flat

; __alloca_probe
; Retail @ 0x009F6C60 size 159
_TEXT SEGMENT
public __alloca_probe
__alloca_probe PROC
    db 3Dh, 00h, 10h, 00h, 00h, 73h, 0Eh, 0F7h
    db 0D8h, 03h, 0C4h, 83h, 0C0h, 04h, 85h, 00h
    db 94h, 8Bh, 00h, 50h, 0C3h, 51h, 8Dh, 4Ch
    db 24h, 08h, 81h, 0E9h, 00h, 10h, 00h, 00h
    db 2Dh, 00h, 10h, 00h, 00h, 85h, 01h, 3Dh
    db 00h, 10h, 00h, 00h, 73h, 0ECh, 2Bh, 0C8h
    db 8Bh, 0C4h, 85h, 01h, 8Bh, 0E1h, 8Bh, 08h
    db 8Bh, 40h, 04h, 50h, 0C3h
__alloca_probe ENDP
_TEXT ENDS
END
