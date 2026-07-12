.386
.model flat

; ?DebugAllocMemory@@YAPAXI@Z
; Retail @ 0x00C8EB30 size 82
_TEXT SEGMENT
public ?DebugAllocMemory@@YAPAXI@Z
?DebugAllocMemory@@YAPAXI@Z PROC
    db 55h,8Bh,0ECh,8Bh,45h,08h,56h,50h
    db 6Ah,00h,0FFh,15h,28h,8Eh,35h,01h
    db 8Bh,0F0h,85h,0F6h,75h,37h,6Ah,01h
    db 0E8h,53h,0ABh,0FFh,0FFh,8Bh,0Dh,5Ch
    db 6Eh,33h,01h,8Bh,11h,83h,0C4h,04h
    db 0FFh,52h,60h,8Bh,0Dh,5Ch,6Eh,33h
    db 01h,8Bh,01h,56h,56h,0FFh,50h,6Ch
    db 8Bh,10h,68h,0A0h,44h,13h,01h,8Bh
    db 0C8h,0FFh,52h,38h,8Bh,10h,6Ah,01h
    db 8Bh,0C8h,0FFh,52h,4Ch,8Bh,0C6h,5Eh
    db 5Dh,0C3h
?DebugAllocMemory@@YAPAXI@Z ENDP
_TEXT ENDS
END
