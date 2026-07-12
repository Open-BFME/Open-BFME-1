.386
.model flat

; _atexit
; Retail @ 0x00DF6E26 size 18
_TEXT SEGMENT
public _atexit
_atexit PROC
    db 0FFh,74h,24h,04h,0E8h,0D1h,0FFh,0FFh
    db 0FFh,0F7h,0D8h,1Bh,0C0h,0F7h,0D8h,59h
    db 48h,0C3h
_atexit ENDP
_TEXT ENDS
END
