.386
.model flat

; ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
; Exact 130 retail bytes @ 0x00486900
; Identity: gameWindowFieldList INPUTCALLBACK strptr @ 0xeb5ad8 -> 0x486900.
; Queue RVA 0x4877E5 was wrong (mid-body of unrelated strtok/StringBase helper cluster).
_TEXT SEGMENT
public ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z PROC
    db 08Bh,044h,024h,00Ch,080h,038h,022h,074h,010h,08Dh,0A4h,024h,000h,000h,000h,000h
    db 08Ah,048h,001h,040h,080h,0F9h,022h,075h,0F7h,040h,068h,0A4h,094h,00Fh,001h,050h
    db 0FFh,015h,0D8h,094h,035h,001h,083h,0C4h,008h,085h,0C0h,074h,012h,08Bh,0C8h,056h
    db 08Dh,071h,001h,08Ah,011h,041h,084h,0D2h,075h,0F9h,02Bh,0CEh,05Eh,0EBh,002h,033h
    db 0C9h,051h,050h,0B9h,074h,025h,02Fh,001h,0E8h,0D3h,013h,040h,000h,0A1h,074h,025h
    db 02Fh,001h,085h,0C0h,074h,005h,083h,0C0h,008h,0EBh,005h,0B8h,08Bh,038h,007h,001h
    db 08Bh,00Dh,000h,0D6h,02Eh,001h,050h,0E8h,06Bh,044h,0BBh,0FFh,08Bh,00Dh,08Ch,0D8h
    db 02Eh,001h,06Ah,001h,050h,0E8h,05Ah,0F3h,0B9h,0FFh,0A3h,05Ch,025h,02Fh,001h,0B0h
    db 001h,0C3h
?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z ENDP
_TEXT ENDS
END
