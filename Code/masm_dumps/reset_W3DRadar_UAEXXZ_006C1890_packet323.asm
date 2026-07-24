.386
.model flat

; ?reset@W3DRadar@@UAEXXZ
; Exact 205 retail bytes @ 0x006C1890; certified packet 323
_TEXT SEGMENT
public ?reset@W3DRadar@@UAEXXZ
?reset@W3DRadar@@UAEXXZ PROC
    db 6Ah,0FFh,68h,50h,9Dh,04h,01h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,08h,56h,57h,8Bh,0F1h,0E8h,0A2h,2Fh,95h
    db 0FFh,0E8h,0DAh,17h,24h,00h,8Dh,44h,24h,08h,50h,8Dh,8Eh,74h,14h,00h
    db 00h,0E8h,0AAh,0CDh,24h,00h,6Ah,00h,8Bh,0C8h,0C7h,44h,24h,1Ch,00h,00h
    db 00h,00h,0E8h,59h,0AFh,23h,00h,83h,0CFh,0FFh,8Dh,4Ch,24h,08h,89h,7Ch
    db 24h,18h,0E8h,0C9h,0ACh,23h,00h,8Dh,4Ch,24h,0Ch,51h,8Dh,8Eh,84h,14h
    db 00h,00h,0E8h,79h,0CDh,24h,00h,6Ah,00h,8Bh,0C8h,0C7h,44h,24h,1Ch,01h
    db 00h,00h,00h,0E8h,28h,0AFh,23h,00h,8Dh,4Ch,24h,0Ch,89h,7Ch,24h,18h
    db 0E8h,9Bh,0ACh,23h,00h,8Bh,8Eh,78h,14h,00h,00h,85h,0C9h,74h,0Fh,0E8h
    db 7Ch,9Eh,32h,00h,0C7h,86h,78h,14h,00h,00h,00h,00h,00h,00h,8Bh,56h
    db 0FCh,8Dh,7Eh,0FCh,8Bh,0CFh,0FFh,52h,20h,8Bh,07h,8Bh,0CFh,0FFh,50h,28h
    db 0C6h,86h,68h,14h,00h,00h,01h,0E8h,0C4h,41h,24h,00h,8Bh,4Ch,24h,10h
    db 5Fh,5Eh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,14h,0C3h
?reset@W3DRadar@@UAEXXZ ENDP
_TEXT ENDS
END
