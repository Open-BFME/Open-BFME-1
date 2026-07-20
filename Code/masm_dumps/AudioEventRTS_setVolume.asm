.386
.model flat

; ?setVolume@AudioEventRTS@@QAEXM@Z
; Exact 10 retail bytes @ RVA 0x000B23B0; audio-volume member assignment
_TEXT SEGMENT
public ?setVolume@AudioEventRTS@@QAEXM@Z
?setVolume@AudioEventRTS@@QAEXM@Z PROC
    db 08Bh,044h,024h,004h,089h,041h,024h,0C2h,004h,000h
?setVolume@AudioEventRTS@@QAEXM@Z ENDP
_TEXT ENDS
END
