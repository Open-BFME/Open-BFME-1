.386
.model flat

; ?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
; Exact 90 retail bytes @ 0x004FFB10; BFME omits the ZH browser teardown
_TEXT SEGMENT
public ?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z PROC
    db 08Bh,00Dh,040h,01Bh,02Fh,001h,08Bh,001h
    db 056h,0C6h,005h,080h,046h,02Fh,001h,001h
    db 0C6h,005h,020h,047h,02Fh,001h,000h,0FFh
    db 090h,0A0h,000h,000h,000h,08Bh,04Ch,024h
    db 00Ch,080h,039h,000h,074h,00Bh,08Bh,074h
    db 024h,008h,0E8h,001h,0FFh,0FFh,0FFh,05Eh
    db 0C3h,08Bh,00Dh,058h,04Bh,02Fh,001h,0E8h
    db 0A2h,0E1h,0B3h,0FFh,051h,089h,064h,024h
    db 010h,08Bh,0CCh,068h,0A4h,035h,010h,001h
    db 0E8h,063h,090h,038h,000h,08Bh,00Dh,030h
    db 033h,02Fh,001h,0E8h,0C4h,046h,0B1h,0FFh
    db 05Eh,0C3h
?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z ENDP
_TEXT ENDS
END
