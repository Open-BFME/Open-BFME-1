.386
.model flat

; ?getColor@QuickMatchPreferences@@QAEHXZ
; Exact 33 retail bytes @ 0x004A97C0; reads the QuickMatch Color preference with a zero default.
_TEXT SEGMENT
public ?getColor@QuickMatchPreferences@@QAEHXZ
?getColor@QuickMatchPreferences@@QAEHXZ PROC
    db 051h,056h,06Ah,000h,051h,08Bh,0F1h,089h,064h,024h,00Ch,08Bh,0CCh,068h,050h,0C7h
    db 007h,001h,0E8h,0E9h,0F3h,07Dh,000h,08Bh,0CEh,0E8h,0DBh,0ABh,0F9h,0FFh,05Eh,059h
    db 0C3h
?getColor@QuickMatchPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
