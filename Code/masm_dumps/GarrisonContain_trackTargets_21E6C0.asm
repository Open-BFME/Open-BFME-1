.386
.model flat

; ?trackTargets@GarrisonContain@@IAEXXZ
; Exact 379 retail bytes @ 0x0021E6C0
; Identity: matchObjects/update@0x21F920 calls thunk 0xD526->body; inlined findConditionIndex;
; contain-list walk + getCurrentVictim/Pos + findClosestFree + inlined calcDistSqr + remove/put.
; Queue 0x49DE40/452 MISPLACED (ghidra FUN 147B SEH ret4; not thiscall trackTargets).
_TEXT SEGMENT
public ?trackTargets@GarrisonContain@@IAEXXZ
?trackTargets@GarrisonContain@@IAEXXZ PROC
    db 083h,0ECh,014h,053h,08Bh,0D9h,08Bh,043h,008h,08Bh,088h,000h,002h,000h,000h,08Bh
    db 011h,0C7h,044h,024h,004h,0FFh,0FFh,0FFh,0FFh,0FFh,052h,020h,083h,0F8h,003h,077h
    db 023h,0FFh,024h,085h,03Ch,0E8h,061h,000h,0C7h,044h,024h,004h,000h,000h,000h,000h
    db 0EBh,012h,0C7h,044h,024h,004h,001h,000h,000h,000h,0EBh,008h,0C7h,044h,024h,004h
    db 002h,000h,000h,000h,08Bh,043h,038h,08Bh,008h,03Bh,0C8h,089h,04Ch,024h,008h,00Fh
    db 084h,021h,001h,000h,000h,055h,056h,057h,0EBh,006h,08Dh,09Bh,000h,000h,000h,000h
    db 08Bh,044h,024h,014h,08Bh,078h,008h,08Bh,047h,074h,08Bh,013h,050h,08Bh,0CBh,0FFh
    db 052h,068h,083h,0F8h,0FFh,089h,044h,024h,01Ch,00Fh,084h,0E1h,000h,000h,000h,08Bh
    db 0B7h,004h,002h,000h,000h,085h,0F6h,00Fh,084h,0D3h,000h,000h,000h,08Bh,0CEh,0E8h
    db 04Eh,07Ah,0E0h,0FFh,08Bh,0E8h,08Bh,0CEh,089h,06Ch,024h,020h,0E8h,0D3h,01Eh,0E1h
    db 0FFh,085h,0EDh,08Bh,0F0h,075h,00Ah,085h,0F6h,00Fh,084h,0B1h,000h,000h,000h,0EBh
    db 003h,08Dh,075h,038h,08Bh,044h,024h,010h,056h,050h,08Bh,0CBh,0E8h,08Eh,02Bh,0E0h
    db 0FFh,08Bh,0E8h,083h,0FDh,0FFh,00Fh,084h,094h,000h,000h,000h,0D9h,006h,08Bh,044h
    db 024h,010h,0D8h,067h,038h,08Dh,00Ch,080h,0D9h,046h,004h,08Dh,044h,0CDh,055h,0D8h
    db 067h,03Ch,08Dh,014h,040h,0D9h,046h,008h,08Dh,004h,093h,0D8h,067h,040h,0D9h,006h
    db 0D8h,020h,0D9h,046h,004h,0D8h,060h,004h,0D9h,046h,008h,0D8h,060h,008h,0D9h,054h
    db 024h,018h,0D8h,04Ch,024h,018h,0D9h,0C1h,0D8h,0CAh,0DEh,0C1h,0D9h,0C2h,0D8h,0CBh
    db 0DEh,0C1h,0D9h,0C3h,0D8h,0CCh,0D9h,0C5h,0D8h,0CEh,0DEh,0C1h,0D9h,0C6h,0D8h,0CFh
    db 0DEh,0C1h,0DEh,0D9h,0DDh,0D8h,0DDh,0D8h,0DDh,0D8h,0DFh,0E0h,0DDh,0D8h,0F6h,0C4h
    db 041h,0DDh,0D8h,075h,02Bh,08Bh,044h,024h,01Ch,050h,057h,08Bh,0CBh,0E8h,073h,00Eh
    db 0E2h,0FFh,08Bh,044h,024h,020h,085h,0C0h,074h,005h,08Bh,040h,074h,0EBh,002h,033h
    db 0C0h,08Bh,04Ch,024h,010h,055h,051h,050h,057h,08Bh,0CBh,0E8h,0CAh,0A4h,0E0h,0FFh
    db 08Bh,054h,024h,014h,08Bh,002h,03Bh,043h,038h,089h,044h,024h,014h,00Fh,085h,0EDh
    db 0FEh,0FFh,0FFh,05Fh,05Eh,05Dh,05Bh,083h,0C4h,014h,0C3h
?trackTargets@GarrisonContain@@IAEXXZ ENDP
_TEXT ENDS
END
