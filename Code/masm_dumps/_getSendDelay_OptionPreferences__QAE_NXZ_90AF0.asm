.386
.model flat
; ?getSendDelay@OptionPreferences@@QAE_NXZ
; Exact 105B @ 0x90AF0; string-anchor SendDelay true body (queue 0x561DDD was OptionsMenuInit interior)
_TEXT SEGMENT
public ?getSendDelay@OptionPreferences@@QAE_NXZ
?getSendDelay@OptionPreferences@@QAE_NXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F1h, 68h, 4Ch, 0FAh, 07h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0BDh
    db 80h, 7Fh, 00h, 8Dh, 44h, 24h, 08h, 83h, 0C6h, 04h, 50h, 8Bh, 0CEh, 0E8h, 9Ah, 0A3h
    db 0F7h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Bh, 0F8h, 0E8h, 23h, 6Eh, 7Fh, 00h, 3Bh, 3Eh, 75h
    db 10h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 81h, 18h, 0Bh, 00h, 00h, 5Fh, 5Eh, 59h
    db 0C3h, 8Bh, 7Fh, 14h, 85h, 0FFh, 8Dh, 47h, 08h, 75h, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 68h, 6Ch, 0C7h, 07h, 01h, 50h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 0F7h
    db 0D8h, 1Ah, 0C0h, 5Fh, 0FEh, 0C0h, 5Eh, 59h, 0C3h
?getSendDelay@OptionPreferences@@QAE_NXZ ENDP
_TEXT ENDS
END
