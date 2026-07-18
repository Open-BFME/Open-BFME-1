.386
.model flat

; ?getMaxMessagesPerUpdate@GameSpyInfo@@UAEHXZ
; Exact 7 retail bytes @ 0x00A307B0; returns the BFME-layout value at offset 0x250.
_TEXT SEGMENT
public ?getMaxMessagesPerUpdate@GameSpyInfo@@UAEHXZ
?getMaxMessagesPerUpdate@GameSpyInfo@@UAEHXZ PROC
    db 08Bh,081h,050h,002h,000h,000h,0C3h
?getMaxMessagesPerUpdate@GameSpyInfo@@UAEHXZ ENDP
_TEXT ENDS
END
