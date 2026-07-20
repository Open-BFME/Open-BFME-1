.386
.model flat

; ?setLocale@GameSpyMiscPreferences@@QAEXH@Z
; Exact 36 retail bytes @ 0x004A99D0; writes the Locale preference.
_TEXT SEGMENT
public ?setLocale@GameSpyMiscPreferences@@QAEXH@Z
?setLocale@GameSpyMiscPreferences@@QAEXH@Z PROC
    db 08Bh,044h,024h,004h,056h,050h,051h,08Bh,0F1h,089h,064h,024h,010h,08Bh,0CCh,068h
    db 06Ch,00Fh,008h,001h,0E8h,0D7h,0F1h,07Dh,000h,08Bh,0CEh,0E8h,04Dh,001h,0F6h,0FFh
    db 05Eh,0C2h,004h,000h
?setLocale@GameSpyMiscPreferences@@QAEXH@Z ENDP
_TEXT ENDS
END
