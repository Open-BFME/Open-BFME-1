.386
.model flat
; _InitStatsConnection
; Exact 47B @ 0x9D58C0; Open-BFME4+Grok
_TEXT SEGMENT
public _InitStatsConnection
_InitStatsConnection PROC
    db 8Bh, 44h, 24h, 04h, 6Ah, 00h, 50h, 0E8h, 34h, 0EDh, 0FFh, 0FFh, 83h, 0C4h, 08h, 83h
    db 0F8h, 06h, 75h, 1Ah, 56h, 0E8h, 96h, 0FDh, 0FFh, 0FFh, 6Ah, 05h, 8Bh, 0F0h, 0E8h, 8Dh
    db 0EAh, 0E7h, 0FFh, 83h, 0C4h, 04h, 83h, 0FEh, 06h, 74h, 0EAh, 8Bh, 0C6h, 5Eh, 0C3h
_InitStatsConnection ENDP
_TEXT ENDS
END
