.386
.model flat
; ?sendAProbe@NAT@@IAEXIGH@Z
; Exact 179B @ 0x671020; Open-BFME4+Grok
_TEXT SEGMENT
public ?sendAProbe@NAT@@IAEXIGH@Z
?sendAProbe@NAT@@IAEXIGH@Z PROC
    db 6Ah, 0FFh, 68h, 0B8h, 4Dh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 0C7h, 44h, 24h, 04h, 00h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 28h, 50h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h
    db 0CCh, 0A3h, 11h, 01h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0E8h, 5Fh, 7Bh, 21h
    db 00h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h, 85h, 7Fh, 21h, 00h, 8Bh, 44h, 24h, 10h, 83h
    db 0C4h, 0Ch, 85h, 0C0h, 74h, 09h, 0Fh, 0B7h, 48h, 04h, 83h, 0C0h, 08h, 0EBh, 07h, 33h
    db 0C9h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 54h, 24h, 20h, 41h, 51h, 8Bh, 4Eh, 04h, 50h
    db 89h, 54h, 24h, 10h, 66h, 8Bh, 54h, 24h, 2Ch, 8Dh, 44h, 24h, 10h, 50h, 66h, 89h
    db 54h, 24h, 18h, 0E8h, 0D8h, 8Eh, 9Dh, 0FFh, 8Bh, 4Eh, 04h, 0E8h, 8Eh, 4Ch, 9Ah, 0FFh
    db 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 7Fh, 68h, 21h
    db 00h, 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 18h
    db 0C2h, 0Ch, 00h
?sendAProbe@NAT@@IAEXIGH@Z ENDP
_TEXT ENDS
END
