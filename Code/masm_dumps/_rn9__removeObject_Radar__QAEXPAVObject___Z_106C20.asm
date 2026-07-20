.386
.model flat
; ?removeObject@Radar@@QAEXPAVObject@@@Z
; Exact 49B @ 0x106C20; reloc-needle Open-BFME4+Grok
_TEXT SEGMENT
public ?removeObject@Radar@@QAEXPAVObject@@@Z
?removeObject@Radar@@QAEXPAVObject@@@Z PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 87h, 0Ch, 02h, 00h, 00h, 85h, 0C0h, 8Bh, 0F1h
    db 74h, 1Ah, 8Dh, 46h, 14h, 50h, 57h, 0E8h, 0C0h, 0ADh, 0F3h, 0FFh, 3Ch, 01h, 74h, 0Ch
    db 8Dh, 4Eh, 10h, 51h, 57h, 8Bh, 0CEh, 0E8h, 0B0h, 0ADh, 0F3h, 0FFh, 5Fh, 5Eh, 0C2h, 04h
    db 00h
?removeObject@Radar@@QAEXPAVObject@@@Z ENDP
_TEXT ENDS
END
