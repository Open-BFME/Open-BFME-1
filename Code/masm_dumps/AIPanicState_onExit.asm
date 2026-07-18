.386
.model flat

; ?onExit@AIPanicState@@UAEXW4StateExitType@@@Z
; Exact 84 retail bytes @ 0x0057F1E0; clears BFME panic state and forwards the exit status.
_TEXT SEGMENT
public ?onExit@AIPanicState@@UAEXW4StateExitType@@@Z
?onExit@AIPanicState@@UAEXW4StateExitType@@@Z PROC
    db 056h,057h,08Bh,0F9h,08Bh,047h,01Ch,08Bh,070h,010h,085h,0F6h,074h,035h,08Bh,086h
    db 098h,000h,000h,000h,0F6h,0C4h,020h,074h,02Ah,06Ah,04Dh,08Bh,0CEh,0E8h,078h,02Dh
    db 0EBh,0FFh,06Ah,003h,08Bh,0CEh,0E8h,06Fh,02Dh,0EBh,0FFh,06Ah,06Ch,08Bh,0CEh,0E8h
    db 00Bh,033h,0EBh,0FFh,084h,0C0h,074h,00Bh,06Ah,000h,06Ah,003h,08Bh,0CEh,0E8h,031h
    db 0AAh,0E9h,0FFh,08Bh,04Ch,024h,00Ch,051h,08Bh,0CFh,0E8h,0E2h,0A0h,0EAh,0FFh,05Fh
    db 05Eh,0C2h,004h,000h
?onExit@AIPanicState@@UAEXW4StateExitType@@@Z ENDP
_TEXT ENDS
END
