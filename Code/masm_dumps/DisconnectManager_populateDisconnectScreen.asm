.386
.model flat

; ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
; Exact 189 retail bytes @ 0x00A6BEF0; populates the disconnect-player menu rows.
_TEXT SEGMENT
public ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z PROC
    db 06Ah,0FFh,068h,0F8h,047h,004h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,0A1h,064h,049h,02Fh,001h,085h,0C0h,053h,055h,056h
    db 057h,08Bh,0E9h,00Fh,084h,07Fh,000h,000h,000h,08Bh,05Ch,024h,024h,033h,0F6h,090h
    db 056h,08Dh,044h,024h,028h,050h,08Bh,0CBh,0E8h,035h,06Bh,09Ah,0FFh,08Bh,0CBh,0C7h
    db 044h,024h,01Ch,000h,000h,000h,000h,0E8h,055h,0E3h,09Dh,0FFh,03Bh,0F0h,07Dh,004h
    db 08Bh,0FEh,0EBh,005h,074h,03Bh,08Dh,07Eh,0FFh,083h,0FFh,0FFh,074h,033h,051h,08Dh
    db 054h,024h,028h,089h,064h,024h,014h,08Bh,0CCh,052h,0E8h,0A1h,0C4h,021h,000h,08Bh
    db 00Dh,064h,049h,02Fh,001h,057h,0E8h,01Ch,03Eh,09Dh,0FFh,053h,056h,08Bh,0CDh,0E8h
    db 0DDh,077h,099h,0FFh,08Bh,00Dh,064h,049h,02Fh,001h,050h,057h,0E8h,037h,05Eh,09Ch
    db 0FFh,08Dh,04Ch,024h,024h,0C7h,044h,024h,01Ch,0FFh,0FFh,0FFh,0FFh,0E8h,03Eh,0C2h
    db 021h,000h,046h,083h,0FEh,008h,07Ch,088h,08Bh,04Ch,024h,014h,05Fh,05Eh,05Dh,064h
    db 089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,010h,0C2h,004h,000h
?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z ENDP
_TEXT ENDS
END
