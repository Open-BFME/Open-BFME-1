.386
.model flat
; _IsStatsConnected
; Exact 15B @ 0x9D2B60; Open-BFME4+Grok
_TEXT SEGMENT
public _IsStatsConnected
_IsStatsConnected PROC
    db 8Bh, 0Dh, 38h, 90h, 2Dh, 01h, 33h, 0C0h, 83h, 0F9h, 0FFh, 0Fh, 95h, 0C0h, 0C3h
_IsStatsConnected ENDP
_TEXT ENDS
END
