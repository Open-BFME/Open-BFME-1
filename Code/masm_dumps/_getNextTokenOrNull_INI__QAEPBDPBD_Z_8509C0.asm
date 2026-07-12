.386
.model flat

; ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
; Retail @ 0x00C509C0 size 29
_TEXT SEGMENT
public ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
?getNextTokenOrNull@INI@@QAEPBDPBD@Z PROC
    db 8Bh,44h,24h,04h,85h,0C0h,75h,06h
    db 8Bh,81h,14h,04h,00h,00h,50h,6Ah
    db 00h,0FFh,15h,0D8h,94h,35h,01h,83h
    db 0C4h,08h,0C2h,04h,00h
?getNextTokenOrNull@INI@@QAEPBDPBD@Z ENDP
_TEXT ENDS
END
