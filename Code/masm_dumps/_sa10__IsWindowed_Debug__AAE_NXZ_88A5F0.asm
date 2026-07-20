.386
.model flat
; ?IsWindowed@Debug@@AAE_NXZ
; Exact 78B @ 0x0088A5F0; Open-BFME4
_TEXT SEGMENT
public ?IsWindowed@Debug@@AAE_NXZ
?IsWindowed@Debug@@AAE_NXZ PROC
    db 55h, 8Bh, 0ECh, 51h, 8Bh, 45h, 04h, 89h, 45h, 0FCh, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h
    db 8Bh, 55h, 0FCh, 8Bh, 01h, 6Ah, 01h, 52h, 0FFh, 50h, 5Ch, 8Bh, 0Dh, 5Ch, 6Eh, 33h
    db 01h, 8Bh, 01h, 0FFh, 50h, 60h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 6Ah, 00h
    db 6Ah, 00h, 0FFh, 52h, 6Ch, 8Bh, 10h, 68h, 50h, 31h, 13h, 01h, 8Bh, 0C8h, 0FFh, 52h
    db 38h, 8Bh, 10h, 6Ah, 01h, 8Bh, 0C8h, 0FFh, 52h, 4Ch, 8Bh, 0E5h, 5Dh, 0C3h
?IsWindowed@Debug@@AAE_NXZ ENDP
_TEXT ENDS
END
