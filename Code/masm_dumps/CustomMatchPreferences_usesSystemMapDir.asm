.386
.model flat

; ?usesSystemMapDir@CustomMatchPreferences@@QAE_NXZ
; Exact 95 retail bytes @ 0x004AC480; reads the UseSystemMapDir preference.
_TEXT SEGMENT
public ?usesSystemMapDir@CustomMatchPreferences@@QAE_NXZ
?usesSystemMapDir@CustomMatchPreferences@@QAE_NXZ PROC
    db 051h,056h,057h,08Bh,0F1h,068h,070h,0C7h,007h,001h,08Dh,04Ch,024h,00Ch,0E8h,02Dh
    db 0C7h,07Dh,000h,08Dh,044h,024h,008h,083h,0C6h,004h,050h,08Bh,0CEh,0E8h,00Ah,0EAh
    db 0F5h,0FFh,08Dh,04Ch,024h,008h,08Bh,0F8h,0E8h,093h,0B4h,07Dh,000h,03Bh,03Eh,075h
    db 006h,05Fh,0B0h,001h,05Eh,059h,0C3h,08Bh,07Fh,014h,085h,0FFh,08Dh,047h,008h,075h
    db 005h,0B8h,08Bh,038h,007h,001h,068h,0C0h,00Fh,008h,001h,050h,0FFh,015h,03Ch,093h
    db 035h,001h,083h,0C4h,008h,0F7h,0D8h,01Ah,0C0h,05Fh,0FEh,0C0h,05Eh,059h,0C3h
?usesSystemMapDir@CustomMatchPreferences@@QAE_NXZ ENDP
_TEXT ENDS
END
