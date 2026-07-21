.386
.model flat
; ?setMinPoints@QuickMatchPreferences@@QAEXH@Z
; Exact 169B @ 0xAD420; MinPoints string-anchor sibling of setMaxPoints/setMaxDisconnects
_TEXT SEGMENT
public ?setMinPoints@QuickMatchPreferences@@QAEXH@Z
?setMinPoints@QuickMatchPreferences@@QAEXH@Z PROC
    db 6Ah, 0FFh, 68h, 0A0h, 79h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 18h, 50h, 51h, 89h, 64h, 24h, 20h, 8Bh, 0CCh, 68h, 0B4h, 0C7h
    db 07h, 01h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 61h, 0B7h, 7Dh, 00h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 0E8h, 87h, 0BBh, 7Dh, 00h, 83h, 0C4h, 0Ch, 68h, 0A4h, 11h, 08h
    db 01h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 46h, 0B7h, 7Dh, 00h, 8Dh, 54h, 24h, 18h, 52h, 8Dh
    db 4Eh, 04h, 0C6h, 44h, 24h, 14h, 01h, 0E8h, 4Eh, 12h, 0F9h, 0FFh, 8Dh, 4Ch, 24h, 04h
    db 51h, 8Bh, 0C8h, 0E8h, 0F8h, 0A7h, 7Dh, 00h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 10h
    db 00h, 0E8h, 9Ah, 0A4h, 7Dh, 00h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 89h, 0A4h, 7Dh, 00h, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Eh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?setMinPoints@QuickMatchPreferences@@QAEXH@Z ENDP
_TEXT ENDS
END
