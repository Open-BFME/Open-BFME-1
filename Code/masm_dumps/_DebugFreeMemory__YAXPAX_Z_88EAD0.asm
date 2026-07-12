.386
.model flat

; ?DebugFreeMemory@@YAXPAX@Z
; Retail @ 0x00C8EAD0 size 19
_TEXT SEGMENT
public ?DebugFreeMemory@@YAXPAX@Z
?DebugFreeMemory@@YAXPAX@Z PROC
    db 55h,8Bh,0ECh,8Bh,45h,08h,85h,0C0h
    db 74h,07h,50h,0FFh,15h,2Ch,8Eh,35h
    db 01h,5Dh,0C3h
?DebugFreeMemory@@YAXPAX@Z ENDP
_TEXT ENDS
END
