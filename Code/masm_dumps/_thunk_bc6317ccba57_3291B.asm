.386
.model flat

; ?freeBlock@MemoryPool@@QAEXPAX@Z
; Retail @ 0x03291b size 5
_TEXT SEGMENT
public ?freeBlock@MemoryPool@@QAEXPAX@Z
?freeBlock@MemoryPool@@QAEXPAX@Z PROC
    db 0E9h, 0B0h, 042h, 075h, 000h
?freeBlock@MemoryPool@@QAEXPAX@Z ENDP
_TEXT ENDS
END
