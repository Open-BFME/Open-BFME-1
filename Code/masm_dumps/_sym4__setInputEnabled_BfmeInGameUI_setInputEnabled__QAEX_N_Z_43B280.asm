.386
.model flat
; ?setInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z
; Exact 20B @ 0x43B280; Open-BFME4+Grok
_TEXT SEGMENT
public ?setInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z
?setInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z PROC
    db 8Bh, 01h, 8Dh, 51h, 0Eh, 52h, 8Bh, 54h, 24h, 08h, 52h, 0FFh, 90h, 20h, 01h, 00h
    db 00h, 0C2h, 04h, 00h
?setInputEnabled@BfmeInGameUI_setInputEnabled@@QAEX_N@Z ENDP
_TEXT ENDS
END
