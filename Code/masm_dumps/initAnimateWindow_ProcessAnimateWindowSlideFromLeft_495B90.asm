.386
.model flat

; ?initAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@@Z
; Exact 235 retail bytes @ 0x00495B90
; Identity: SlideFromLeft ctor @0x495AC0 stores vtbl 0x10FA270; slot1 ILT 0x1D61F -> this body.
; Semantics: winGetPos, TheDisplay getWidth@+0x2c, winSetPos(x-width), m_maxVel, timeGetTime+delay, setAnimData.
; Queue 0x589443 was junk (mid tiny-thunk cluster); C++ blocked by Display getWidth slot 0x2c vs ZH 0x20 + setAnimData Coord2D stack-temp shape.
_TEXT SEGMENT
public ?initAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@@Z
?initAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@@Z PROC
    db 083h,0ECh,028h,033h,0C0h,053h,08Bh,05Ch,024h,030h,03Bh,0D8h,055h,056h,057h,08Bh
    db 0E9h,089h,044h,024h,010h,089h,044h,024h,014h,089h,044h,024h,030h,089h,044h,024h
    db 034h,089h,044h,024h,028h,089h,044h,024h,02Ch,089h,044h,024h,018h,089h,044h,024h
    db 01Ch,00Fh,084h,0AAh,000h,000h,000h,08Bh,07Bh,028h,03Bh,0F8h,00Fh,084h,09Fh,000h
    db 000h,000h,08Dh,044h,024h,014h,050h,08Dh,04Ch,024h,014h,051h,08Bh,0CFh,0E8h,0ABh
    db 009h,0BAh,0FFh,08Bh,054h,024h,010h,08Bh,00Dh,070h,012h,02Fh,001h,08Bh,044h,024h
    db 014h,089h,054h,024h,018h,08Bh,011h,089h,044h,024h,01Ch,0FFh,052h,02Ch,08Bh,074h
    db 024h,010h,02Bh,0F0h,08Bh,044h,024h,014h,050h,056h,08Bh,0CFh,089h,044h,024h,034h
    db 089h,044h,024h,03Ch,0E8h,084h,038h,0B8h,0FFh,08Bh,045h,004h,08Bh,04Dh,008h,08Bh
    db 07Bh,004h,06Ah,000h,089h,044h,024h,024h,089h,04Ch,024h,028h,0E8h,0B3h,025h,0BBh
    db 0FFh,08Bh,054h,024h,024h,08Bh,04Ch,024h,028h,003h,0C7h,050h,083h,0ECh,008h,08Bh
    db 0C4h,089h,064h,024h,04Ch,089h,048h,004h,08Bh,04Ch,024h,03Ch,089h,010h,08Bh,054h
    db 024h,024h,08Bh,044h,024h,020h,052h,08Bh,054h,024h,030h,050h,08Bh,044h,024h,030h
    db 051h,08Bh,04Ch,024h,050h,056h,052h,050h,051h,056h,08Bh,0CBh,0E8h,048h,079h,0BAh
    db 0FFh,05Fh,05Eh,05Dh,05Bh,083h,0C4h,028h,0C2h,004h,000h
?initAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAEXPAVAnimateWindow@@@Z ENDP
_TEXT ENDS
END
