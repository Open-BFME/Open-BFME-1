.386
.model flat

; ?scanUnsignedInt@INI@@SAIPBD@Z
; Retail @ 0x00C52680 size 86
_TEXT SEGMENT
public ?scanUnsignedInt@INI@@SAIPBD@Z
?scanUnsignedInt@INI@@SAIPBD@Z PROC
    db 8Bh,44h,24h,04h,83h,0ECh,0Ch,56h
    db 50h,0E8h,22h,0FEh,0FFh,0FFh,8Dh,4Ch
    db 24h,08h,51h,8Bh,0F0h,68h,2Ch,5Eh
    db 10h,01h,56h,0FFh,15h,94h,94h,35h
    db 01h,83h,0C4h,10h,83h,0F8h,01h,74h
    db 24h,56h,68h,68h,07h,13h,01h,8Dh
    db 54h,24h,10h,6Ah,03h,52h,0E8h,45h
    db 0DFh,0FFh,0FFh,83h,0C4h,10h,68h,30h
    db 0FCh,1Dh,01h,8Dh,44h,24h,0Ch,50h
    db 0E8h,33h,46h,1Ah,00h,8Bh,44h,24h
    db 04h,5Eh,83h,0C4h,0Ch,0C3h
?scanUnsignedInt@INI@@SAIPBD@Z ENDP
_TEXT ENDS
END
