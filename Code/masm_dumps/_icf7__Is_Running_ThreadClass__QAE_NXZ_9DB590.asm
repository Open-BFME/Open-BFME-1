.386
.model flat
; ?Is_Running@ThreadClass@@QAE_NXZ
; Exact 11B @ 0x9DB590; Open-BFME4+Grok
_TEXT SEGMENT
public ?Is_Running@ThreadClass@@QAE_NXZ
?Is_Running@ThreadClass@@QAE_NXZ PROC
    db 8Bh, 51h, 48h, 33h, 0C0h, 85h, 0D2h, 0Fh, 95h, 0C0h, 0C3h
?Is_Running@ThreadClass@@QAE_NXZ ENDP
_TEXT ENDS
END
