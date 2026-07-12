.386
.model flat

; __ftol2
; Retail @ 0x009F6E38 size 117
_TEXT SEGMENT
public __ftol2
__ftol2 PROC
    db 55h,8Bh,0ECh,83h,0ECh,20h,83h,0E4h
    db 0F0h,0D9h,0C0h,0D9h,54h,24h,18h,0DFh
    db 7Ch,24h,10h,0DFh,6Ch,24h,10h,8Bh
    db 54h,24h,18h,8Bh,44h,24h,10h,85h
    db 0C0h,74h,3Ch,0DEh,0E9h,85h,0D2h,79h
    db 1Eh,0D9h,1Ch,24h,8Bh,0Ch,24h,81h
    db 0F1h,00h,00h,00h,80h,81h,0C1h,0FFh
    db 0FFh,0FFh,7Fh,83h,0D0h,00h,8Bh,54h
    db 24h,14h,83h,0D2h,00h,0EBh,2Ch,0D9h
    db 1Ch,24h,8Bh,0Ch,24h,81h,0C1h,0FFh
    db 0FFh,0FFh,7Fh,83h,0D8h,00h,8Bh,54h
    db 24h,14h,83h,0DAh,00h,0EBh,14h,8Bh
    db 54h,24h,14h,0F7h,0C2h,0FFh,0FFh,0FFh
    db 7Fh,75h,0B8h,0D9h,5Ch,24h,18h,0D9h
    db 5Ch,24h,18h,0C9h,0C3h
__ftol2 ENDP
_TEXT ENDS
END
