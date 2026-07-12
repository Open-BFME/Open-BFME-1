.386
.model flat

; __CIpow
; Retail @ 0x00DF6FB2 size 6
_TEXT SEGMENT
public __CIpow
__CIpow PROC
    db 0FFh,25h,44h,92h,35h,01h
__CIpow ENDP
_TEXT ENDS
END
