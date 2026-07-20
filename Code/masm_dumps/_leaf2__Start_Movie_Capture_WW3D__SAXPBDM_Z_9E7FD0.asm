.386
.model flat
; ?Start_Movie_Capture@WW3D@@SAXPBDM@Z
; Exact 53B @ 0x009E7FD0; present-unmatched Open-BFME4
_TEXT SEGMENT
public ?Start_Movie_Capture@WW3D@@SAXPBDM@Z
?Start_Movie_Capture@WW3D@@SAXPBDM@Z PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 44h, 24h, 08h, 33h, 0C9h, 8Ah, 0Ah, 84h, 0C9h, 0F7h, 0D0h
    db 74h, 2Bh, 56h, 0EBh, 0Bh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 33h, 0C8h, 81h, 0E1h, 0FFh, 00h, 00h, 00h, 8Bh, 34h, 8Dh, 0F0h, 9Dh, 2Dh, 01h, 8Ah
    db 4Ah, 01h, 0C1h, 0E8h, 08h
?Start_Movie_Capture@WW3D@@SAXPBDM@Z ENDP
_TEXT ENDS
END
