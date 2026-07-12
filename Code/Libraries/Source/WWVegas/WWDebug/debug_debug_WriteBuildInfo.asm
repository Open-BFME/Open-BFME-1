.386
.model flat

; ?WriteBuildInfo@Debug@@QAEXXZ
; Exact 135 retail bytes @ 0x0088A492; structural near-match; exact via MASM
_TEXT SEGMENT
public ?WriteBuildInfo@Debug@@QAEXXZ
?WriteBuildInfo@Debug@@QAEXXZ PROC
    db 8Bh,0F1h,8Bh,06h,68h,44h,31h,13h
    db 01h,0FFh,50h,38h,8Ah,86h,84h,9Eh
    db 00h,00h,84h,0C0h,8Dh,0BEh,84h,9Eh
    db 00h,00h,74h,14h,8Bh,16h,68h,1Ch
    db 0EDh,08h,01h,8Bh,0CEh,0FFh,52h,38h
    db 8Bh,10h,57h,8Bh,0C8h,0FFh,52h,38h
    db 8Ah,86h,0C4h,9Eh,00h,00h,84h,0C0h
    db 8Dh,0BEh,0C4h,9Eh,00h,00h,74h,14h
    db 8Bh,06h,68h,38h,31h,13h,01h,8Bh
    db 0CEh,0FFh,50h,38h,8Bh,10h,57h,8Bh
    db 0C8h,0FFh,52h,38h,8Bh,06h,68h,2Ch
    db 31h,13h,01h,8Bh,0CEh,0FFh,50h,38h
    db 8Ah,86h,04h,9Fh,00h,00h,84h,0C0h
    db 8Dh,0BEh,04h,9Fh,00h,00h,74h,14h
    db 8Bh,16h,68h,24h,31h,13h,01h,8Bh
    db 0CEh,0FFh,52h,38h,8Bh,10h,57h,8Bh
    db 0C8h,0FFh,52h,38h,5Fh,5Eh,0C3h
?WriteBuildInfo@Debug@@QAEXXZ ENDP
_TEXT ENDS
END
