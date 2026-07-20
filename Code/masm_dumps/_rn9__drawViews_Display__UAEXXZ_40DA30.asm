.386
.model flat
; ?drawViews@Display@@UAEXXZ
; Exact 38B @ 0x40DA30; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?drawViews@Display@@UAEXXZ
?drawViews@Display@@UAEXXZ PROC
    db 56h, 8Bh, 71h, 18h, 85h, 0F6h, 74h, 22h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 78h, 01h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h
    db 3Ch, 02h, 00h, 00h, 8Bh, 0F0h
?drawViews@Display@@UAEXXZ ENDP
_TEXT ENDS
END
