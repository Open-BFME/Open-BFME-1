.386
.model flat

; ?GadgetListBoxAddEntryText@@YAHPAVGameWindow@@VUnicodeString@@HHH_N@Z
; Retail @ 0x004BB4B0 size 357
; Identity: SEH UnicodeString-by-value prologue; empty -> UnicodeString(L" ")+set;
; GLM_ADD_ENTRY 0x4011; ListboxData endPos +0x2C; scrollIfAtEnd +0x0D;
; winSendSystemMsg vtbl+0xD4; calls IsFull@0x4B78E0 / SetBottom@0x4B8550 via ILT.
; C++ blocked on empty-string temp using listbox arg home + lea rematerialize (MSVC 7.1 emits local+push eax).
_TEXT SEGMENT
public ?GadgetListBoxAddEntryText@@YAHPAVGameWindow@@VUnicodeString@@HHH_N@Z
?GadgetListBoxAddEntryText@@YAHPAVGameWindow@@VUnicodeString@@HHH_N@Z PROC
    db 06Ah,0FFh,068h,010h,08Dh,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,020h,055h,057h,08Bh,07Ch,024h,038h,033h,0EDh
    db 03Bh,0FDh,089h,06Ch,024h,030h,075h,025h,08Dh,04Ch,024h,03Ch,0C7h,044h,024h,030h
    db 0FFh,0FFh,0FFh,0FFh,0E8h,0E7h,0CCh,03Ch,000h,05Fh,083h,0C8h,0FFh,05Dh,08Bh,04Ch
    db 024h,020h,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,02Ch,0C3h,08Bh,044h,024h
    db 03Ch,03Bh,0C5h,053h,0BBh,001h,000h,000h,000h,074h,006h,066h,039h,068h,004h,075h
    db 02Eh,068h,034h,04Ch,008h,001h,08Dh,04Ch,024h,040h,0E8h,0C1h,0D8h,03Ch,000h,08Dh
    db 044h,024h,03Ch,050h,08Dh,04Ch,024h,044h,088h,05Ch,024h,038h,0E8h,0FFh,0CFh,03Ch
    db 000h,08Dh,04Ch,024h,03Ch,0C6h,044h,024h,034h,000h,0E8h,091h,0CCh,03Ch,000h,08Bh
    db 04Ch,024h,048h,08Bh,054h,024h,04Ch,089h,04Ch,024h,010h,08Ah,04Ch,024h,050h,08Dh
    db 044h,024h,040h,089h,044h,024h,018h,083h,0C8h,0FFh,088h,04Ch,024h,020h,056h,08Bh
    db 0CFh,089h,054h,024h,018h,089h,05Ch,024h,020h,089h,044h,024h,02Ch,089h,044h,024h
    db 028h,0E8h,0C2h,0AFh,0B8h,0FFh,08Bh,0F0h,066h,08Bh,016h,066h,03Bh,056h,02Ch,08Bh
    db 0CFh,00Fh,09Eh,0C0h,033h,0DBh,084h,0C0h,00Fh,094h,0C3h,0E8h,0A8h,0AFh,0B8h,0FFh
    db 03Bh,0C5h,075h,006h,089h,06Ch,024h,010h,0EBh,00Bh,08Bh,0C8h,0E8h,0FFh,0B5h,0FFh
    db 0FFh,089h,044h,024h,010h,08Bh,054h,024h,048h,08Bh,00Dh,040h,01Bh,02Fh,001h,08Bh
    db 001h,052h,08Dh,054h,024h,018h,052h,068h,011h,040h,000h,000h,057h,0FFh,090h,0D4h
    db 000h,000h,000h,08Bh,0E8h,08Ah,046h,00Dh,084h,0C0h,05Eh,074h,023h,08Bh,054h,024h
    db 00Ch,08Bh,0C5h,02Bh,0C2h,03Bh,0C3h,075h,017h,057h,0E8h,0AEh,0A7h,0B6h,0FFh,083h
    db 0C4h,004h,084h,0C0h,074h,00Ah,055h,057h,0E8h,0C4h,0A4h,0B8h,0FFh,083h,0C4h,008h
    db 08Dh,04Ch,024h,040h,0C7h,044h,024h,034h,0FFh,0FFh,0FFh,0FFh,0E8h,0CFh,0CBh,03Ch
    db 000h,08Bh,04Ch,024h,02Ch,05Bh,05Fh,08Bh,0C5h,05Dh,064h,089h,00Dh,000h,000h,000h
    db 000h,083h,0C4h,02Ch,0C3h
?GadgetListBoxAddEntryText@@YAHPAVGameWindow@@VUnicodeString@@HHH_N@Z ENDP
_TEXT ENDS
END
