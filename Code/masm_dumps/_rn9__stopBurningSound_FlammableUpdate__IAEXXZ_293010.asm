.386
.model flat
; ?stopBurningSound@FlammableUpdate@@IAEXXZ
; Exact 31B @ 0x293010; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?stopBurningSound@FlammableUpdate@@IAEXXZ
?stopBurningSound@FlammableUpdate@@IAEXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 34h, 85h, 0C0h, 74h, 13h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h
    db 8Bh, 11h, 50h, 0FFh, 52h, 4Ch, 0C7h, 46h, 34h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?stopBurningSound@FlammableUpdate@@IAEXXZ ENDP
_TEXT ENDS
END
