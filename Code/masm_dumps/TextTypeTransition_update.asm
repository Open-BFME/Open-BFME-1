.386
.model flat

; ?update@TextTypeTransition@@UAEXH@Z
; Exact 180 retail bytes @ 0x005A0910; TextType vtable@0x110CCFC slot2 (update);
; queue 0x4A2737 was wrong (not this class). C++ blocked: BFME +0x10/+0x14 start/end
; members before m_pos (m_drawState@+0x28) + no GUITypeText audio.
_TEXT SEGMENT
public ?update@TextTypeTransition@@UAEXH@Z
?update@TextTypeTransition@@UAEXH@Z PROC
    db 056h,08Bh,0F1h,08Bh,046h,010h,057h,08Bh,07Ch,024h,00Ch,03Bh,0F8h,0C7h,046h,028h
    db 0FFh,0FFh,0FFh,0FFh,00Fh,08Ch,095h,000h,000h,000h,08Bh,04Eh,014h,03Bh,0F9h,00Fh
    db 08Fh,08Ah,000h,000h,000h,03Bh,0F8h,075h,012h,08Ah,046h,009h,084h,0C0h,075h,028h
    db 08Bh,04Eh,00Ch,085h,0C9h,074h,021h,06Ah,001h,0EBh,014h,03Bh,0F9h,075h,019h,08Ah
    db 046h,009h,084h,0C0h,074h,012h,08Bh,04Eh,00Ch,085h,0C9h,074h,00Bh,06Ah,000h,0E8h
    db 0C6h,075h,0A8h,0FFh,0C6h,046h,008h,001h,03Bh,07Eh,004h,07Ch,00Ah,08Bh,04Eh,00Ch
    db 06Ah,000h,0E8h,0B3h,075h,0A8h,0FFh,03Bh,07Eh,010h,07Eh,043h,03Bh,07Eh,004h,07Dh
    db 03Eh,08Bh,04Eh,00Ch,06Ah,001h,0E8h,09Fh,075h,0A8h,0FFh,08Ah,046h,009h,084h,0C0h
    db 089h,07Eh,028h,074h,022h,04Fh,057h,08Dh,04Eh,02Ch,0E8h,0EFh,04Eh,0A7h,0FFh,06Ah
    db 001h,08Dh,04Eh,030h,089h,044h,024h,010h,08Dh,044h,024h,010h,050h,0E8h,04Eh,07Ch
    db 02Eh,000h,05Fh,05Eh,0C2h,004h,000h,08Dh,04Eh,030h,0E8h,081h,07Eh,02Eh,000h,05Fh
    db 05Eh,0C2h,004h,000h
?update@TextTypeTransition@@UAEXH@Z ENDP
_TEXT ENDS
END
