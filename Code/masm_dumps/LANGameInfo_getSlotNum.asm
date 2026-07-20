.386
.model flat

; ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z
; Exact 179 retail bytes @ RVA 0x0068EB10; LAN slot username search
_TEXT SEGMENT
public ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z
?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z PROC
    db 06Ah,0FFh,068h,0E8h,06Dh,004h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,053h,056h,057h,08Ah,041h,00Ch,084h,0C0h,0C7h,044h
    db 024h,018h,000h,000h,000h,000h,074h,03Ch,033h,0F6h,08Dh,059h,058h,08Dh,049h,000h
    db 085h,0F6h,07Ch,009h,083h,0FEh,008h,07Dh,004h,08Bh,0FBh,0EBh,002h,033h,0FFh,051h
    db 08Dh,044h,024h,024h,089h,064h,024h,010h,08Bh,0CCh,050h,0E8h,0A0h,098h,01Fh,000h
    db 08Bh,0CFh,0E8h,06Fh,033h,099h,0FFh,084h,0C0h,075h,031h,046h,083h,0C3h,068h,083h
    db 0FEh,008h,07Ch,0CCh,08Dh,04Ch,024h,020h,0C7h,044h,024h,018h,0FFh,0FFh,0FFh,0FFh
    db 0E8h,04Bh,096h,01Fh,000h,083h,0C8h,0FFh,08Bh,04Ch,024h,010h,064h,089h,00Dh,000h
    db 000h,000h,000h,05Fh,05Eh,05Bh,083h,0C4h,010h,0C2h,004h,000h,08Dh,04Ch,024h,020h
    db 0C7h,044h,024h,018h,0FFh,0FFh,0FFh,0FFh,0E8h,023h,096h,01Fh,000h,08Bh,04Ch,024h
    db 010h,05Fh,08Bh,0C6h,05Eh,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,010h
    db 0C2h,004h,000h
?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z ENDP
_TEXT ENDS
END
