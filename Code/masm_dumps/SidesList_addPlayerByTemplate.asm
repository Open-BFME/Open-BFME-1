.386
.model flat

; ?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z
; Exact 722 retail bytes @ 0x0019C590; validateSides calls thunk 0x0003892E.
_TEXT SEGMENT
public ?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z
?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z PROC
    db 06Ah, 0FFh, 068h, 0A8h, 077h, 000h, 001h, 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 014h, 053h, 057h, 08Bh, 0F9h, 033h, 0DBh, 089h, 05Ch
    db 024h, 024h, 089h, 05Ch, 024h, 00Ch, 089h, 05Ch, 024h, 014h, 08Bh, 044h, 024h, 02Ch, 03Bh, 0C3h
    db 0C6h, 044h, 024h, 024h, 002h, 074h, 006h, 066h, 039h, 058h, 004h, 075h, 031h, 053h, 068h, 01Ch
    db 030h, 007h, 001h, 08Dh, 04Ch, 024h, 014h, 0E8h, 044h, 0B7h, 06Eh, 000h, 068h, 0D0h, 0C1h, 009h
    db 001h, 0FFh, 015h, 024h, 095h, 035h, 001h, 083h, 0C4h, 004h, 050h, 068h, 0D0h, 0C1h, 009h, 001h
    db 08Dh, 04Ch, 024h, 01Ch, 0E8h, 0C7h, 0BFh, 06Eh, 000h, 0E9h, 09Bh, 000h, 000h, 000h, 06Ah, 004h
    db 068h, 0C8h, 0C1h, 009h, 001h, 08Dh, 04Ch, 024h, 014h, 0E8h, 012h, 0B7h, 06Eh, 000h, 06Ah, 007h
    db 068h, 0BCh, 0C1h, 009h, 001h, 08Dh, 04Ch, 024h, 034h, 0E8h, 082h, 0AFh, 06Eh, 000h, 084h, 0C0h
    db 08Bh, 044h, 024h, 02Ch, 074h, 02Fh, 03Bh, 0C3h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    db 08Bh, 038h, 007h, 001h, 08Dh, 050h, 007h, 03Bh, 0D3h, 074h, 014h, 08Bh, 0C2h, 056h, 08Dh, 070h
    db 001h, 08Ah, 008h, 040h, 03Ah, 0CBh, 075h, 0F9h, 02Bh, 0C6h, 05Eh, 050h, 052h, 0EBh, 01Ch, 033h
    db 0C0h, 050h, 052h, 0EBh, 016h, 03Bh, 0C3h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h, 0C0h, 008h
    db 0EBh, 007h, 033h, 0C9h, 0B8h, 08Bh, 038h, 007h, 001h, 051h, 050h, 08Dh, 04Ch, 024h, 014h, 0E8h
    db 0ECh, 0B6h, 06Eh, 000h, 08Dh, 044h, 024h, 00Ch, 050h, 08Dh, 04Ch, 024h, 018h, 0E8h, 06Eh, 0CBh
    db 06Eh, 000h, 068h, 0ACh, 0C1h, 009h, 001h, 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 01Ch, 001h
    db 0E8h, 085h, 0E9h, 0EAh, 0FFh, 085h, 0C0h, 075h, 004h, 088h, 05Ch, 024h, 018h, 053h, 08Dh, 04Ch
    db 024h, 00Ch, 0E8h, 026h, 068h, 0E6h, 0FFh, 08Dh, 04Ch, 024h, 008h, 0C6h, 044h, 024h, 024h, 003h
    db 0E8h, 091h, 078h, 0E9h, 0FFh, 08Dh, 04Ch, 024h, 00Ch, 051h, 0B9h, 018h, 079h, 02Ah, 001h, 0E8h
    db 040h, 0CCh, 0E6h, 0FFh, 050h, 08Dh, 04Ch, 024h, 010h, 0E8h, 0C2h, 0E8h, 0E8h, 0FFh, 08Bh, 054h
    db 024h, 018h, 052h, 0B9h, 020h, 079h, 02Ah, 001h, 0E8h, 027h, 0CCh, 0E6h, 0FFh, 050h, 08Dh, 04Ch
    db 024h, 010h, 0E8h, 07Dh, 0A8h, 0E6h, 0FFh, 08Dh, 044h, 024h, 014h, 050h, 0B9h, 030h, 079h, 02Ah
    db 001h, 0E8h, 00Eh, 0CCh, 0E6h, 0FFh, 050h, 08Dh, 04Ch, 024h, 010h, 0E8h, 087h, 0BAh, 0E8h, 0FFh
    db 08Dh, 04Ch, 024h, 02Ch, 051h, 0B9h, 038h, 079h, 02Ah, 001h, 0E8h, 0F5h, 0CBh, 0E6h, 0FFh, 050h
    db 08Dh, 04Ch, 024h, 010h, 0E8h, 077h, 0E8h, 0E8h, 0FFh, 068h, 050h, 06Eh, 033h, 001h, 0B9h, 048h
    db 079h, 02Ah, 001h, 0E8h, 0DCh, 0CBh, 0E6h, 0FFh, 050h, 08Dh, 04Ch, 024h, 010h, 0E8h, 05Eh, 0E8h
    db 0E8h, 0FFh, 068h, 050h, 06Eh, 033h, 001h, 0B9h, 040h, 079h, 02Ah, 001h, 0E8h, 0C3h, 0CBh, 0E6h
    db 0FFh, 050h, 08Dh, 04Ch, 024h, 010h, 0E8h, 045h, 0E8h, 0E8h, 0FFh, 08Bh, 047h, 028h, 083h, 0F8h
    db 020h, 07Dh, 017h, 08Dh, 050h, 001h, 089h, 057h, 028h, 08Dh, 04Ch, 024h, 008h, 08Dh, 014h, 040h
    db 051h, 08Dh, 04Ch, 0D7h, 02Ch, 0E8h, 097h, 0B3h, 0E8h, 0FFh, 089h, 05Ch, 024h, 010h, 06Ah, 004h
    db 068h, 01Ch, 03Eh, 008h, 001h, 08Dh, 04Ch, 024h, 018h, 0C6h, 044h, 024h, 02Ch, 004h, 0E8h, 09Dh
    db 0B5h, 06Eh, 000h, 08Bh, 044h, 024h, 00Ch, 03Bh, 0C3h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h
    db 0C0h, 008h, 0EBh, 007h, 033h, 0C9h, 0B8h, 08Bh, 038h, 007h, 001h, 051h, 050h, 08Dh, 04Ch, 024h
    db 018h, 0E8h, 0BAh, 0B5h, 06Eh, 000h, 08Dh, 04Ch, 024h, 008h, 0E8h, 097h, 077h, 0E9h, 0FFh, 08Dh
    db 044h, 024h, 010h, 050h, 0B9h, 0B8h, 075h, 02Ah, 001h, 0E8h, 046h, 0CBh, 0E6h, 0FFh, 050h, 08Dh
    db 04Ch, 024h, 010h, 0E8h, 0C8h, 0E7h, 0E8h, 0FFh, 08Dh, 04Ch, 024h, 00Ch, 051h, 0B9h, 0C0h, 075h
    db 02Ah, 001h, 0E8h, 02Dh, 0CBh, 0E6h, 0FFh, 050h, 08Dh, 04Ch, 024h, 010h, 0E8h, 0AFh, 0E7h, 0E8h
    db 0FFh, 06Ah, 001h, 0B9h, 0C8h, 075h, 02Ah, 001h, 0E8h, 017h, 0CBh, 0E6h, 0FFh, 050h, 08Dh, 04Ch
    db 024h, 010h, 0E8h, 06Dh, 0A7h, 0E6h, 0FFh, 08Dh, 054h, 024h, 008h, 052h, 08Dh, 08Fh, 030h, 006h
    db 000h, 000h, 0E8h, 0C0h, 095h, 0EAh, 0FFh, 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 024h, 003h
    db 0E8h, 02Bh, 0B1h, 06Eh, 000h, 08Dh, 04Ch, 024h, 008h, 0C6h, 044h, 024h, 024h, 002h, 0E8h, 052h
    db 07Ch, 0E7h, 0FFh, 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 024h, 001h, 0E8h, 09Fh, 0B9h, 06Eh
    db 000h, 08Dh, 04Ch, 024h, 00Ch, 088h, 05Ch, 024h, 024h, 0E8h, 002h, 0B1h, 06Eh, 000h, 08Dh, 04Ch
    db 024h, 02Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F1h, 0B0h, 06Eh, 000h, 08Bh
    db 04Ch, 024h, 01Ch, 05Fh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 020h, 0C2h
    db 004h, 000h
?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z ENDP
_TEXT ENDS
END
