.386
.model flat

; ?getChatSizeSlider@CustomMatchPreferences@@QAEHXZ
; Exact 92 retail bytes @ 0x004AC330; reads and validates the chat-size slider.
_TEXT SEGMENT
public ?getChatSizeSlider@CustomMatchPreferences@@QAEHXZ
?getChatSizeSlider@CustomMatchPreferences@@QAEHXZ PROC
    db 051h,056h,057h,08Bh,0F1h,068h,0D8h,011h,008h,001h,08Dh,04Ch,024h,00Ch,0E8h,07Dh
    db 0C8h,07Dh,000h,08Dh,044h,024h,008h,083h,0C6h,004h,050h,08Bh,0CEh,0E8h,05Ah,0EBh
    db 0F5h,0FFh,08Dh,04Ch,024h,008h,08Bh,0F8h,0E8h,0E3h,0B5h,07Dh,000h,03Bh,03Eh,074h
    db 022h,08Bh,07Fh,014h,085h,0FFh,08Dh,047h,008h,075h,005h,0B8h,08Bh,038h,007h,001h
    db 050h,0FFh,015h,084h,093h,035h,001h,083h,0C4h,004h,085h,0C0h,07Ch,005h,083h,0F8h
    db 064h,07Eh,005h,0B8h,02Dh,000h,000h,000h,05Fh,05Eh,059h,0C3h
?getChatSizeSlider@CustomMatchPreferences@@QAEHXZ ENDP
_TEXT ENDS
END
