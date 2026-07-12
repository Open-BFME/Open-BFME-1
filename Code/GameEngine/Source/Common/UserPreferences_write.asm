.386
.model flat

; ?write@UserPreferences@@UAE_NXZ
; Exact 162 retail bytes @ 0x000A9F60; structural near-match; exact via MASM
_TEXT SEGMENT
public ?write@UserPreferences@@UAE_NXZ
?write@UserPreferences@@UAE_NXZ PROC
    db 57h,8Bh,0F9h,8Bh,47h,10h,85h,0C0h
    db 74h,07h,66h,83h,78h,04h,00h,75h
    db 04h,32h,0C0h,5Fh,0C3h,8Bh,47h,10h
    db 85h,0C0h,74h,05h,83h,0C0h,08h,0EBh
    db 05h,0B8h,8Ch,38h,07h,01h,53h,68h
    db 0A8h,6Fh,07h,01h,50h,0FFh,15h,68h
    db 93h,35h,01h,8Bh,0D8h,83h,0C4h,08h
    db 85h,0DBh,74h,61h,8Bh,47h,04h,56h
    db 8Bh,70h,08h,3Bh,0F0h,74h,46h,55h
    db 8Bh,2Dh,0C0h,93h,35h,01h,8Bh,0FFh
    db 8Bh,46h,14h,85h,0C0h,8Dh,48h,08h
    db 75h,05h,0B9h,8Bh,38h,07h,01h,8Bh
    db 46h,10h,85h,0C0h,74h,05h,83h,0C0h
    db 08h,0EBh,05h,0B8h,8Bh,38h,07h,01h
    db 51h,50h,68h,0A0h,0Fh,08h,01h,53h
    db 0FFh,0D5h,56h,0E8h,90h,18h,78h,00h
    db 8Bh,0F0h,8Bh,47h,04h,83h,0C4h,14h
    db 3Bh,0F0h,75h,0C4h,5Dh,53h,0FFh,15h
    db 0A0h,93h,35h,01h,83h,0C4h,04h,5Eh
    db 5Bh,0B0h,01h,5Fh,0C3h,5Bh,32h,0C0h
    db 5Fh,0C3h
?write@UserPreferences@@UAE_NXZ ENDP
_TEXT ENDS
END
