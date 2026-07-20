.386
.model flat
; ?Log_DX8_ErrorCode@@YAXI@Z
; Exact 25B @ 0x87CAC0; Open-BFME4+Grok
_TEXT SEGMENT
public ?Log_DX8_ErrorCode@@YAXI@Z
?Log_DX8_ErrorCode@@YAXI@Z PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 50h, 0E8h, 0E3h, 0D5h, 0FEh, 0FFh, 56h, 0FFh, 15h
    db 0D4h, 93h, 35h, 01h, 83h, 0C4h, 08h, 5Eh, 0C3h
?Log_DX8_ErrorCode@@YAXI@Z ENDP
_TEXT ENDS
END
