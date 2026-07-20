.386
.model flat
; ?validateAudio@ThingTemplate@@IAEXXZ
; Exact 60B @ 0x13E2F0; Open-BFME4+Grok
_TEXT SEGMENT
public ?validateAudio@ThingTemplate@@IAEXXZ
?validateAudio@ThingTemplate@@IAEXXZ PROC
    db 8Bh, 41h, 4Ch, 85h, 0C0h, 56h, 8Dh, 71h, 4Ch, 74h, 07h, 66h, 83h, 78h, 04h, 00h
    db 75h, 28h, 83h, 0C1h, 60h, 0E8h, 0C6h, 05h, 74h, 00h, 84h, 0C0h, 8Bh, 0CEh, 74h, 0Eh
    db 6Ah, 07h, 68h, 0ECh, 40h, 09h, 01h, 0E8h, 04h, 9Ah, 74h, 00h, 5Eh, 0C3h, 6Ah, 06h
    db 68h, 0E4h, 40h, 09h, 01h, 0E8h, 0F6h, 99h, 74h, 00h, 5Eh, 0C3h
?validateAudio@ThingTemplate@@IAEXXZ ENDP
_TEXT ENDS
END
