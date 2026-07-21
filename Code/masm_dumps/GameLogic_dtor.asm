.386
.model flat
; ??1GameLogic@@UAE@XZ
; Exact 821B @ 0x0038F080; true body (queue 0x9F265F was int3 pad near PartitionManager dtor cluster);
; dual SubsystemInterface+Snapshot vtbls 0x10EB574/0x10EB560; deletes same globals as init@0x38A1F0;
; SEH member teardown 0x16..0; ret @ 0x38F3B4; ctor twin stores same vtbls @ 0x392915
_TEXT SEGMENT
public ??1GameLogic@@UAE@XZ
??1GameLogic@@UAE@XZ PROC
    db 06Ah, 0FFh, 068h, 01Bh, 0C0h, 001h, 001h, 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 008h, 056h, 08Bh, 0F1h, 057h, 089h, 074h, 024h, 00Ch
    db 0C7h, 006h, 074h, 0B5h, 00Eh, 001h, 0C7h, 046h, 008h, 060h, 0B5h, 00Eh, 001h, 08Bh, 086h, 0A0h
    db 001h, 000h, 000h, 033h, 0FFh, 03Bh, 0C7h, 0C7h, 044h, 024h, 018h, 016h, 000h, 000h, 000h, 075h
    db 005h, 0E8h, 0FAh, 0D3h, 056h, 000h, 08Bh, 08Eh, 0A0h, 001h, 000h, 000h, 041h, 053h, 089h, 08Eh
    db 0A0h, 001h, 000h, 000h, 08Dh, 09Eh, 0ACh, 001h, 000h, 000h, 08Bh, 0CBh, 0E8h, 007h, 0A6h, 0CBh
    db 0FFh, 08Bh, 08Eh, 0A4h, 000h, 000h, 000h, 03Bh, 0CFh, 074h, 01Ch, 08Bh, 001h, 0FFh, 050h, 020h
    db 08Bh, 08Eh, 0A4h, 000h, 000h, 000h, 03Bh, 0CFh, 074h, 007h, 08Bh, 011h, 06Ah, 001h, 0FFh, 052h
    db 004h, 089h, 0BEh, 0A4h, 000h, 000h, 000h, 08Bh, 0CEh, 0E8h, 033h, 025h, 0CBh, 0FFh, 08Bh, 00Dh
    db 0CCh, 0F4h, 02Eh, 001h, 03Bh, 0CFh, 074h, 006h, 08Bh, 001h, 06Ah, 001h, 0FFh, 010h, 08Bh, 00Dh
    db 0FCh, 0F4h, 02Eh, 001h, 03Bh, 0CFh, 089h, 03Dh, 0CCh, 0F4h, 02Eh, 001h, 074h, 006h, 08Bh, 011h
    db 06Ah, 001h, 0FFh, 012h, 08Bh, 00Dh, 0B8h, 0D5h, 02Eh, 001h, 03Bh, 0CFh, 089h, 03Dh, 0FCh, 0F4h
    db 02Eh, 001h, 074h, 006h, 08Bh, 001h, 06Ah, 001h, 0FFh, 010h, 08Bh, 00Dh, 0BCh, 0D5h, 02Eh, 001h
    db 03Bh, 0CFh, 089h, 03Dh, 0B8h, 0D5h, 02Eh, 001h, 074h, 006h, 08Bh, 011h, 06Ah, 001h, 0FFh, 012h
    db 08Bh, 00Dh, 0C4h, 0D5h, 02Eh, 001h, 03Bh, 0CFh, 089h, 03Dh, 0BCh, 0D5h, 02Eh, 001h, 074h, 006h
    db 08Bh, 001h, 06Ah, 001h, 0FFh, 010h, 08Bh, 00Dh, 020h, 006h, 02Fh, 001h, 03Bh, 0CFh, 089h, 03Dh
    db 0C4h, 0D5h, 02Eh, 001h, 074h, 006h, 08Bh, 011h, 06Ah, 001h, 0FFh, 012h, 08Bh, 00Dh, 0B0h, 006h
    db 02Fh, 001h, 03Bh, 0CFh, 089h, 03Dh, 020h, 006h, 02Fh, 001h, 074h, 006h, 08Bh, 001h, 06Ah, 001h
    db 0FFh, 010h, 08Bh, 00Dh, 044h, 010h, 02Fh, 001h, 03Bh, 0CFh, 089h, 03Dh, 0B0h, 006h, 02Fh, 001h
    db 074h, 006h, 08Bh, 011h, 06Ah, 001h, 0FFh, 012h, 08Bh, 00Dh, 0F0h, 0F4h, 02Eh, 001h, 03Bh, 0CFh
    db 089h, 03Dh, 044h, 010h, 02Fh, 001h, 074h, 006h, 08Bh, 001h, 06Ah, 001h, 0FFh, 010h, 08Bh, 0CEh
    db 089h, 03Dh, 0F0h, 0F4h, 02Eh, 001h, 0E8h, 071h, 040h, 0C7h, 0FFh, 08Bh, 0CEh, 0E8h, 0A4h, 042h
    db 0C7h, 0FFh, 068h, 0E2h, 0A8h, 042h, 000h, 06Ah, 008h, 06Ah, 01Ch, 08Dh, 08Eh, 0B0h, 001h, 000h
    db 000h, 051h, 089h, 03Dh, 098h, 008h, 02Fh, 001h, 0C6h, 044h, 024h, 02Ch, 015h, 0E8h, 074h, 07Bh
    db 066h, 000h, 08Bh, 0CBh, 0C6h, 044h, 024h, 01Ch, 014h, 0E8h, 0DAh, 0A4h, 0CBh, 0FFh, 08Bh, 003h
    db 03Bh, 0C7h, 05Bh, 074h, 00Bh, 06Ah, 010h, 050h, 0E8h, 0D3h, 0F3h, 049h, 000h, 083h, 0C4h, 008h
    db 08Dh, 08Eh, 070h, 001h, 000h, 000h, 0C6h, 044h, 024h, 018h, 013h, 0E8h, 09Dh, 0C3h, 0C7h, 0FFh
    db 08Bh, 08Eh, 05Ch, 001h, 000h, 000h, 03Bh, 0CFh, 0C6h, 044h, 024h, 018h, 012h, 074h, 02Ah, 08Bh
    db 086h, 064h, 001h, 000h, 000h, 02Bh, 0C1h, 0C1h, 0F8h, 002h, 0C1h, 0E0h, 002h, 03Dh, 080h, 000h
    db 000h, 000h, 076h, 00Bh, 051h, 0E8h, 056h, 02Ch, 04Fh, 000h, 083h, 0C4h, 004h, 0EBh, 00Ah, 050h
    db 051h, 0E8h, 08Ah, 0F3h, 049h, 000h, 083h, 0C4h, 008h, 08Dh, 08Eh, 004h, 001h, 000h, 000h, 0C6h
    db 044h, 024h, 018h, 011h, 0E8h, 014h, 0F4h, 0C7h, 0FFh, 08Bh, 08Eh, 0F4h, 000h, 000h, 000h, 03Bh
    db 0CFh, 0C6h, 044h, 024h, 018h, 010h, 074h, 02Ah, 08Bh, 086h, 0FCh, 000h, 000h, 000h, 02Bh, 0C1h
    db 0C1h, 0F8h, 002h, 0C1h, 0E0h, 002h, 03Dh, 080h, 000h, 000h, 000h, 076h, 00Bh, 051h, 0E8h, 00Dh
    db 02Ch, 04Fh, 000h, 083h, 0C4h, 004h, 0EBh, 00Ah, 050h, 051h, 0E8h, 041h, 0F3h, 049h, 000h, 083h
    db 0C4h, 008h, 068h, 0ACh, 092h, 043h, 000h, 06Ah, 004h, 06Ah, 00Ch, 08Dh, 096h, 0C4h, 000h, 000h
    db 000h, 052h, 0C6h, 044h, 024h, 028h, 00Fh, 0E8h, 0AAh, 07Ah, 066h, 000h, 08Dh, 08Eh, 0B0h, 000h
    db 000h, 000h, 0C6h, 044h, 024h, 018h, 00Eh, 0E8h, 042h, 07Eh, 0CAh, 0FFh, 08Dh, 08Eh, 088h, 000h
    db 000h, 000h, 0C6h, 044h, 024h, 018h, 00Dh, 0E8h, 054h, 086h, 04Fh, 000h, 08Dh, 08Eh, 084h, 000h
    db 000h, 000h, 0C6h, 044h, 024h, 018h, 00Ch, 0E8h, 044h, 086h, 04Fh, 000h, 08Dh, 08Eh, 080h, 000h
    db 000h, 000h, 0C6h, 044h, 024h, 018h, 00Bh, 0E8h, 034h, 086h, 04Fh, 000h, 08Dh, 04Eh, 07Ch, 0C6h
    db 044h, 024h, 018h, 00Ah, 0E8h, 027h, 086h, 04Fh, 000h, 08Dh, 04Eh, 078h, 0C6h, 044h, 024h, 018h
    db 009h, 0E8h, 01Ah, 086h, 04Fh, 000h, 08Dh, 04Eh, 070h, 0C6h, 044h, 024h, 018h, 008h, 0E8h, 00Dh
    db 086h, 04Fh, 000h, 08Dh, 04Eh, 064h, 0C6h, 044h, 024h, 018h, 007h, 0E8h, 000h, 086h, 04Fh, 000h
    db 08Dh, 04Eh, 060h, 0C6h, 044h, 024h, 018h, 006h, 0E8h, 0F3h, 085h, 04Fh, 000h, 08Dh, 04Eh, 054h
    db 0C6h, 044h, 024h, 018h, 005h, 0E8h, 058h, 077h, 0C9h, 0FFh, 08Dh, 04Eh, 050h, 0C6h, 044h, 024h
    db 018h, 004h, 0E8h, 0D9h, 085h, 04Fh, 000h, 08Dh, 04Eh, 04Ch, 0C6h, 044h, 024h, 018h, 003h, 0E8h
    db 0ABh, 0D9h, 0C7h, 0FFh, 08Dh, 04Eh, 020h, 0C6h, 044h, 024h, 018h, 002h, 0E8h, 081h, 04Dh, 0CBh
    db 0FFh, 08Dh, 04Eh, 00Ch, 0C6h, 044h, 024h, 018h, 001h, 0E8h, 002h, 0A2h, 0CAh, 0FFh, 08Bh, 0CEh
    db 0C7h, 046h, 008h, 044h, 037h, 007h, 001h, 0C7h, 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 09Ch, 026h, 061h, 000h, 08Bh, 04Ch, 024h, 010h, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 083h, 0C4h, 014h, 0C3h
??1GameLogic@@UAE@XZ ENDP
_TEXT ENDS
END
