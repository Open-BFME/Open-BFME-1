.386
.model flat
; ?setSDEnabled@StealthDetectorUpdate@@QAEX_N@Z
; Exact 34B @ 0x2AB650; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?setSDEnabled@StealthDetectorUpdate@@QAEX_N@Z
?setSDEnabled@StealthDetectorUpdate@@QAEX_N@Z PROC
    db 8Ah, 44h, 24h, 04h, 88h, 41h, 20h, 0F6h, 0D8h, 1Bh, 0C0h, 25h, 02h, 00h, 00h, 0C0h
    db 05h, 0FFh, 0FFh, 0FFh, 3Fh, 50h, 8Bh, 41h, 08h, 50h, 0E8h, 6Bh, 0A1h, 0D6h, 0FFh, 0C2h
    db 04h, 00h
?setSDEnabled@StealthDetectorUpdate@@QAEX_N@Z ENDP
_TEXT ENDS
END
