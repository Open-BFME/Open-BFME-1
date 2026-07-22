.386
.model flat

; ??1GameSpyGameSlot@@QAE@XZ
; Exact 128B @ 0x004FA000; Open-BFME; proved via GameSpyStagingRoom dtor
; vecdtor(arr@+0x58, size=0x78, count=8) -> ILT 0x7D92 -> body; 5x AsciiString + GameSlot base
_TEXT SEGMENT
public ??1GameSpyGameSlot@@QAE@XZ
??1GameSpyGameSlot@@QAE@XZ PROC
    db 06Ah,0FFh,068h,054h,0CFh,002h,001h,064h,0A1h,000h,000h,000h,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,051h,056h,08Bh,0F1h,089h,074h,024h,004h,08Dh,04Eh,074h
    db 0C7h,044h,024h,010h,004h,000h,000h,000h,0E8h,013h,0D9h,038h,000h,08Dh,04Eh,070h
    db 0C6h,044h,024h,010h,003h,0E8h,006h,0D9h,038h,000h,08Dh,04Eh,050h,0C6h,044h,024h
    db 010h,002h,0E8h,0F9h,0D8h,038h,000h,08Dh,04Eh,04Ch,0C6h,044h,024h,010h,001h,0E8h
    db 0ECh,0D8h,038h,000h,08Dh,04Eh,048h,0C6h,044h,024h,010h,000h,0E8h,0DFh,0D8h,038h
    db 000h,08Bh,0CEh,0C7h,044h,024h,010h,0FFh,0FFh,0FFh,0FFh,0E8h,018h,019h,0B1h,0FFh
    db 08Bh,04Ch,024h,008h,05Eh,064h,089h,00Dh,000h,000h,000h,000h,083h,0C4h,010h,0C3h
??1GameSpyGameSlot@@QAE@XZ ENDP
_TEXT ENDS
END
