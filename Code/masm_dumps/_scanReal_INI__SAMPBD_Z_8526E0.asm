.386
.model flat

; ?scanReal@INI@@SAMPBD@Z
; Retail @ 0x00C526E0 size 86
_TEXT SEGMENT
public ?scanReal@INI@@SAMPBD@Z
?scanReal@INI@@SAMPBD@Z PROC
    db 8Bh,44h,24h,04h,83h,0ECh,0Ch,56h
    db 50h,0E8h,0C2h,0FDh,0FFh,0FFh,8Dh,4Ch
    db 24h,08h,51h,8Bh,0F0h,68h,4Ch,2Fh
    db 08h,01h,56h,0FFh,15h,94h,94h,35h
    db 01h,83h,0C4h,10h,83h,0F8h,01h,74h
    db 24h,56h,68h,0B0h,07h,13h,01h,8Dh
    db 54h,24h,10h,6Ah,03h,52h,0E8h,0E5h
    db 0DEh,0FFh,0FFh,83h,0C4h,10h,68h,30h
    db 0FCh,1Dh,01h,8Dh,44h,24h,0Ch,50h
    db 0E8h,0D3h,45h,1Ah,00h,0D9h,44h,24h
    db 04h,5Eh,83h,0C4h,0Ch,0C3h
?scanReal@INI@@SAMPBD@Z ENDP
_TEXT ENDS
END
