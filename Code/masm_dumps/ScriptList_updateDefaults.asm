.386
.model flat

; ?updateDefaults@ScriptList@@SAXXZ
; Exact 183 retail bytes @ 0x0035C8A0
; ScriptList::updateDefaults: loop TheSidesList sides; if m_scripts null,
; allocate 0x4c ScriptList (inline ctor) and setScriptList. WorldBuilder-only caller.
_TEXT SEGMENT
public ?updateDefaults@ScriptList@@SAXXZ
?updateDefaults@ScriptList@@SAXXZ PROC
    db 08Bh,00Dh,028h,0F4h,02Eh,001h,08Bh,041h,028h,053h,056h,033h,0F6h,033h,0DBh,03Bh
    db 0C6h,00Fh,08Eh,09Dh,000h,000h,000h,055h,057h,033h,0FFh,083h,0CDh,0FFh,08Bh,0FFh
    db 03Bh,0FEh,07Ch,00Ah,03Bh,0D8h,07Dh,006h,08Dh,044h,00Fh,02Ch,0EBh,002h,033h,0C0h
    db 039h,070h,008h,075h,06Eh,06Ah,04Ch,0E8h,054h,056h,052h,000h,083h,0C4h,004h,03Bh
    db 0C6h,074h,03Eh,089h,070h,004h,089h,070h,008h,0C7h,000h,0A8h,08Ch,00Eh,001h,089h
    db 070h,00Ch,089h,070h,010h,089h,070h,014h,089h,070h,018h,089h,070h,01Ch,089h,070h
    db 020h,089h,068h,024h,089h,068h,028h,089h,070h,02Ch,089h,070h,030h,089h,070h,034h
    db 089h,070h,038h,089h,070h,03Ch,089h,070h,040h,089h,068h,044h,089h,068h,048h,0EBh
    db 002h,033h,0C0h,03Bh,0FEh,07Ch,011h,08Bh,00Dh,028h,0F4h,02Eh,001h,03Bh,059h,028h
    db 07Dh,006h,08Dh,04Ch,00Fh,02Ch,0EBh,002h,033h,0C9h,089h,041h,008h,08Bh,00Dh,028h
    db 0F4h,02Eh,001h,08Bh,041h,028h,043h,083h,0C7h,018h,03Bh,0D8h,00Fh,08Ch,06Eh,0FFh
    db 0FFh,0FFh,05Fh,05Dh,05Eh,05Bh,0C3h
?updateDefaults@ScriptList@@SAXXZ ENDP
_TEXT ENDS
END
