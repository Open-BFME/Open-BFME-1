.386
.model flat
; ?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ
; Exact 17B @ 0x77F6B0; Open-BFME4+Grok
_TEXT SEGMENT
public ?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ
?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ PROC
    db 8Bh, 81h, 38h, 01h, 00h, 00h, 85h, 0C0h, 74h, 04h, 83h, 0C0h, 3Ch, 0C3h, 33h, 0C0h
    db 0C3h
?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ ENDP
_TEXT ENDS
END
