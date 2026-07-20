.386
.model flat
; ?isAnimFinished@Shell@@QAE_NXZ
; Exact 61B @ 0x57F3C0; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?isAnimFinished@Shell@@QAE_NXZ
?isAnimFinished@Shell@@QAE_NXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Dh, 30h, 33h, 2Fh, 01h, 0E8h, 0A1h, 3Ah, 0ACh, 0FFh, 84h, 0C0h
    db 75h, 02h, 5Eh, 0C3h, 8Bh, 46h, 5Ch, 85h, 0C0h, 74h, 1Eh, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh
    db 01h, 8Ah, 91h, 0C4h, 0Bh, 00h, 00h, 84h, 0D2h, 74h, 0Eh, 8Ah, 48h, 10h, 33h, 0D2h
    db 84h, 0C9h, 0Fh, 94h, 0C2h, 8Ah, 0C2h, 5Eh, 0C3h, 0B0h, 01h, 5Eh, 0C3h
?isAnimFinished@Shell@@QAE_NXZ ENDP
_TEXT ENDS
END
