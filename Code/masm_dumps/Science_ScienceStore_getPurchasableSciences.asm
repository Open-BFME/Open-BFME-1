.386
.model flat

; ?getPurchasableSciences@ScienceStore@@QBEXPBVPlayer@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@1@Z
; Exact 479B @ 0x000E7D30; true body in Science cluster (queue 0x77B125 was INSIDE FUN_00b7b090 SEH ctor).
; BFME rewrite: SEH + temp list; hasScience@0xCE340; playerHasPrereqs@0xE6E50; 3-arg helper@0xE7C20; ret 0xc.
; C++ ZH 284B shape blocked (no SEH/temp-list/game-mode branch). Prior rootPrereqs attempt also named 0xE7D30.
_TEXT SEGMENT
public ?getPurchasableSciences@ScienceStore@@QBEXPBVPlayer@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@1@Z
?getPurchasableSciences@ScienceStore@@QBEXPBVPlayer@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@1@Z PROC
    db 06Ah,0FFh,068h,088h,0B2h,0FFh,000h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,014h,053h,055h,056h,057h,08Bh,0E9h,033h,0DBh
    db 06Ah,018h,089h,06Ch,024h,018h,089h,05Ch,024h,01Ch,0E8h,0E1h,067h,074h,000h,089h
    db 044h,024h,01Ch,089h,05Ch,024h,020h,088h,018h,08Bh,044h,024h,01Ch,089h,058h,004h
    db 08Bh,044h,024h,01Ch,089h,040h,008h,08Bh,044h,024h,01Ch,083h,0C4h,004h,089h,040h
    db 00Ch,08Bh,074h,024h,038h,08Bh,056h,004h,08Bh,00Eh,08Bh,0C2h,02Bh,0C2h,0C1h,0F8h
    db 002h,03Bh,0C3h,089h,05Ch,024h,02Ch,07Eh,012h,02Bh,0D1h,0EBh,003h,08Dh,049h,000h
    db 08Bh,03Ch,00Ah,089h,039h,083h,0C1h,004h,048h,075h,0F5h,089h,04Eh,004h,08Bh,074h
    db 024h,03Ch,08Bh,056h,004h,08Bh,00Eh,08Bh,0C2h,02Bh,0C2h,0C1h,0F8h,002h,03Bh,0C3h
    db 07Eh,00Dh,02Bh,0D1h,08Bh,03Ch,00Ah,089h,039h,083h,0C1h,004h,048h,075h,0F5h,089h
    db 04Eh,004h,08Bh,045h,008h,08Bh,07Dh,00Ch,03Bh,0C7h,089h,044h,024h,010h,00Fh,084h
    db 005h,001h,000h,000h,0EBh,002h,033h,0DBh,08Bh,000h,08Bh,048h,004h,03Bh,0CBh,074h
    db 005h,0E8h,0C5h,0A4h,0F1h,0FFh,08Bh,075h,008h,03Bh,0F7h,08Dh,058h,00Ch,00Fh,084h
    db 0CBh,000h,000h,000h,08Bh,006h,08Bh,048h,004h,085h,0C9h,074h,005h,0E8h,0A9h,0A4h
    db 0F1h,0FFh,08Bh,0E8h,08Bh,003h,039h,045h,00Ch,074h,00Ch,083h,0C6h,004h,03Bh,0F7h
    db 075h,0E2h,0E9h,0A8h,000h,000h,000h,08Bh,00Dh,098h,008h,02Fh,001h,08Bh,081h,00Ch
    db 001h,000h,000h,083h,0F8h,001h,074h,027h,083h,0F8h,005h,074h,022h,083h,0F8h,002h
    db 074h,01Dh,083h,0F8h,003h,075h,013h,08Bh,00Dh,02Ch,0D6h,02Eh,001h,085h,0C9h,074h
    db 009h,0E8h,04Fh,029h,0F6h,0FFh,084h,0C0h,075h,005h,08Bh,06Dh,024h,0EBh,003h,08Bh
    db 06Dh,028h,085h,0EDh,074h,069h,08Bh,013h,08Bh,074h,024h,034h,052h,08Bh,0CEh,0E8h
    db 0CBh,015h,0F2h,0FFh,084h,0C0h,075h,057h,08Bh,003h,08Bh,07Ch,024h,014h,050h,056h
    db 08Bh,0CFh,0E8h,056h,05Eh,0F2h,0FFh,084h,0C0h,074h,006h,08Bh,04Ch,024h,038h,0EBh
    db 018h,08Bh,00Bh,08Dh,044h,024h,018h,050h,051h,056h,08Bh,0CFh,0E8h,0FEh,062h,0F4h
    db 0FFh,084h,0C0h,074h,02Ah,08Bh,04Ch,024h,03Ch,08Bh,041h,004h,03Bh,041h,008h,074h
    db 00Eh,085h,0C0h,074h,004h,08Bh,013h,089h,010h,083h,041h,004h,004h,0EBh,010h,06Ah
    db 001h,06Ah,001h,08Dh,054h,024h,040h,052h,053h,050h,0E8h,0B9h,0B6h,0F3h,0FFh,08Bh
    db 044h,024h,010h,08Bh,06Ch,024h,014h,08Bh,07Dh,00Ch,083h,0C0h,004h,03Bh,0C7h,089h
    db 044h,024h,010h,00Fh,085h,0FDh,0FEh,0FFh,0FFh,08Dh,04Ch,024h,018h,0C7h,044h,024h
    db 02Ch,0FFh,0FFh,0FFh,0FFh,0E8h,068h,055h,0F3h,0FFh,08Bh,04Ch,024h,024h,05Fh,05Eh
    db 05Dh,05Bh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,020h,0C2h,00Ch,000h
?getPurchasableSciences@ScienceStore@@QBEXPBVPlayer@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@1@Z ENDP
_TEXT ENDS
END
