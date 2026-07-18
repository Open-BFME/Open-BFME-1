.386
.model flat

; ?setAudioPriority@AudioEventRTS@@QAEXW4AudioPriority@@@Z
; Exact 10 retail bytes @ RVA 0x000B23A0; audio-priority member assignment
_TEXT SEGMENT
public ?setAudioPriority@AudioEventRTS@@QAEXW4AudioPriority@@@Z
?setAudioPriority@AudioEventRTS@@QAEXW4AudioPriority@@@Z PROC
    db 08Bh,044h,024h,004h,089h,041h,020h,0C2h,004h,000h
?setAudioPriority@AudioEventRTS@@QAEXW4AudioPriority@@@Z ENDP
_TEXT ENDS
END
