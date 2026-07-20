.386
.model flat

; ?playerTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
; Exact 1517 retail bytes @ 0x004FA800; WOLLobbyMenuInit installs this tooltip callback.
_TEXT SEGMENT
public ?playerTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
?playerTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h, 008h, 0D1h, 002h, 001h, 050h, 08Bh, 044h
    db 024h, 018h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 034h, 053h, 055h, 056h, 08Bh
    db 074h, 024h, 050h, 057h, 08Dh, 054h, 024h, 02Ch, 052h, 08Bh, 0C8h, 08Dh, 054h, 024h, 038h, 052h
    db 0C1h, 0E8h, 010h, 050h, 081h, 0E1h, 0FFh, 0FFh, 000h, 000h, 051h, 056h, 0E8h, 044h, 07Bh, 0B3h
    db 0FFh, 08Bh, 044h, 024h, 048h, 083h, 0CFh, 0FFh, 083h, 0C4h, 014h, 03Bh, 0C7h, 00Fh, 084h, 063h
    db 005h, 000h, 000h, 039h, 07Ch, 024h, 02Ch, 00Fh, 084h, 059h, 005h, 000h, 000h, 06Ah, 002h, 050h
    db 08Dh, 044h, 024h, 018h, 056h, 050h, 0E8h, 068h, 0AEh, 0B4h, 0FFh, 083h, 0C4h, 010h, 033h, 0EDh
    db 089h, 06Ch, 024h, 04Ch, 089h, 06Ch, 024h, 014h, 08Dh, 04Ch, 024h, 010h, 051h, 08Dh, 04Ch, 024h
    db 018h, 0C6h, 044h, 024h, 050h, 001h, 0E8h, 0C5h, 0E7h, 038h, 000h, 08Bh, 044h, 024h, 014h, 03Bh
    db 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Bh, 038h, 007h, 001h, 08Bh, 00Dh, 094h
    db 071h, 02Fh, 001h, 08Bh, 011h, 050h, 0FFh, 052h, 04Ch, 08Bh, 0F0h, 03Bh, 0F5h, 074h, 075h, 08Bh
    db 00Dh, 094h, 071h, 02Fh, 001h, 08Bh, 001h, 08Dh, 054h, 024h, 038h, 052h, 0FFh, 050h, 068h, 08Dh
    db 04Eh, 004h, 051h, 08Bh, 0C8h, 0E8h, 0A7h, 0CBh, 0B2h, 0FFh, 08Bh, 0D8h, 0F7h, 0DBh, 01Ah, 0DBh
    db 08Dh, 04Ch, 024h, 038h, 0FEh, 0C3h, 0E8h, 065h, 0D0h, 038h, 000h, 039h, 06Ch, 024h, 02Ch, 075h
    db 071h, 039h, 06Eh, 030h, 068h, 000h, 000h, 080h, 03Fh, 055h, 057h, 074h, 01Bh, 08Bh, 00Dh, 07Ch
    db 014h, 02Fh, 001h, 08Bh, 011h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 04Ch, 055h, 068h, 088h, 030h
    db 010h, 001h, 050h, 0FFh, 052h, 028h, 0EBh, 011h, 051h, 089h, 064h, 024h, 04Ch, 08Bh, 0CCh, 068h
    db 054h, 06Eh, 033h, 001h, 0E8h, 0E7h, 0DAh, 038h, 000h, 08Bh, 00Dh, 05Ch, 04Ch, 02Fh, 001h, 0E8h
    db 0C5h, 09Dh, 0B3h, 0FFh, 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 04Ch, 000h, 0E8h, 00Eh, 0D0h
    db 038h, 000h, 08Dh, 04Ch, 024h, 010h, 089h, 07Ch, 024h, 04Ch, 0E8h, 091h, 0D8h, 038h, 000h, 08Bh
    db 04Ch, 024h, 044h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h
    db 040h, 0C3h, 08Dh, 04Eh, 008h, 051h, 08Dh, 04Ch, 024h, 034h, 0E8h, 001h, 0D2h, 038h, 000h, 089h
    db 06Ch, 024h, 028h, 08Bh, 044h, 024h, 030h, 03Bh, 0C5h, 0C6h, 044h, 024h, 04Ch, 003h, 074h, 005h
    db 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Bh, 038h, 007h, 001h, 050h, 0FFh, 015h, 084h, 093h, 035h
    db 001h, 083h, 0C4h, 004h, 050h, 051h, 089h, 064h, 024h, 044h, 08Bh, 0CCh, 068h, 07Ch, 00Fh, 010h
    db 001h, 0E8h, 02Ah, 0E2h, 038h, 000h, 08Dh, 054h, 024h, 030h, 052h, 0E8h, 050h, 0E6h, 038h, 000h
    db 08Bh, 046h, 00Ch, 08Bh, 04Eh, 010h, 083h, 0C4h, 00Ch, 089h, 06Ch, 024h, 024h, 051h, 050h, 055h
    db 051h, 08Dh, 044h, 024h, 038h, 089h, 064h, 024h, 04Ch, 08Bh, 0CCh, 050h, 0C6h, 044h, 024h, 060h
    db 004h, 0E8h, 09Ah, 0D1h, 038h, 000h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 08Bh, 011h, 08Dh, 044h
    db 024h, 048h, 050h, 0FFh, 052h, 024h, 08Bh, 000h, 03Bh, 0C5h, 0C6h, 044h, 024h, 054h, 005h, 074h
    db 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h, 007h, 001h, 08Bh, 00Dh, 07Ch, 014h, 02Fh
    db 001h, 08Bh, 011h, 050h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 04Ch, 055h, 068h, 070h, 030h, 010h
    db 001h, 050h, 0FFh, 052h, 028h, 08Dh, 04Ch, 024h, 034h, 051h, 0E8h, 081h, 0E7h, 038h, 000h, 083h
    db 0C4h, 014h, 08Dh, 04Ch, 024h, 038h, 0C6h, 044h, 024h, 04Ch, 004h, 0E8h, 0B0h, 0D7h, 038h, 000h
    db 068h, 054h, 06Eh, 033h, 001h, 08Dh, 04Ch, 024h, 060h, 0E8h, 0D2h, 0D9h, 038h, 000h, 084h, 0DBh
    db 0C6h, 044h, 024h, 04Ch, 006h, 074h, 02Bh, 08Bh, 044h, 024h, 010h, 03Bh, 0C5h, 074h, 005h, 083h
    db 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h, 007h, 001h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 050h
    db 051h, 08Bh, 0C4h, 089h, 064h, 024h, 044h, 055h, 068h, 0C4h, 028h, 010h, 001h, 0E9h, 0A4h, 000h
    db 000h, 000h, 08Bh, 00Dh, 094h, 071h, 02Fh, 001h, 08Bh, 011h, 0FFh, 052h, 054h, 08Bh, 00Dh, 094h
    db 071h, 02Fh, 001h, 08Bh, 018h, 08Bh, 001h, 0FFh, 050h, 054h, 08Dh, 07Eh, 014h, 057h, 08Dh, 04Ch
    db 024h, 03Ch, 051h, 08Bh, 0C8h, 0E8h, 03Ch, 010h, 0B3h, 0FFh, 039h, 05Ch, 024h, 038h, 074h, 028h
    db 08Bh, 044h, 024h, 010h, 03Bh, 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h
    db 007h, 001h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 050h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 044h
    db 055h, 068h, 0ACh, 028h, 010h, 001h, 0EBh, 04Eh, 039h, 02Fh, 08Bh, 044h, 024h, 010h, 074h, 024h
    db 03Bh, 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h, 007h, 001h, 08Bh, 00Dh
    db 07Ch, 014h, 02Fh, 001h, 050h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 044h, 055h, 068h, 090h, 028h
    db 010h, 001h, 0EBh, 022h, 03Bh, 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h
    db 007h, 001h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 050h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 044h
    db 055h, 068h, 074h, 028h, 010h, 001h, 08Bh, 011h, 050h, 0FFh, 052h, 028h, 08Dh, 04Ch, 024h, 064h
    db 051h, 0E8h, 07Ah, 0E6h, 038h, 000h, 08Bh, 046h, 014h, 083h, 0C4h, 00Ch, 03Bh, 0C5h, 074h, 013h
    db 08Bh, 00Dh, 094h, 071h, 02Fh, 001h, 08Bh, 011h, 050h, 0FFh, 092h, 02Ch, 001h, 000h, 000h, 084h
    db 0C0h, 075h, 01Fh, 051h, 089h, 064h, 024h, 040h, 08Bh, 0CCh, 056h, 0E8h, 020h, 0D0h, 038h, 000h
    db 08Bh, 00Dh, 094h, 071h, 02Fh, 001h, 08Bh, 001h, 0FFh, 090h, 044h, 001h, 000h, 000h, 084h, 0C0h
    db 074h, 033h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 08Bh, 011h, 055h, 068h, 054h, 030h, 010h, 001h
    db 08Dh, 044h, 024h, 040h, 050h, 0FFh, 052h, 028h, 050h, 08Dh, 04Ch, 024h, 060h, 0C6h, 044h, 024h
    db 050h, 007h, 0E8h, 02Bh, 0DFh, 0B1h, 0FFh, 08Dh, 04Ch, 024h, 038h, 0C6h, 044h, 024h, 04Ch, 006h
    db 0E8h, 04Bh, 0D6h, 038h, 000h, 039h, 06Eh, 014h, 074h, 00Eh, 08Dh, 04Ch, 024h, 024h, 051h, 08Dh
    db 04Ch, 024h, 060h, 0E8h, 00Ah, 0DFh, 0B1h, 0FFh, 08Bh, 00Dh, 01Ch, 040h, 02Fh, 001h, 08Bh, 046h
    db 01Ch, 08Bh, 051h, 004h, 083h, 0C1h, 004h, 033h, 0FFh, 03Bh, 0C2h, 07Ch, 00Eh, 08Dh, 049h, 000h
    db 08Bh, 051h, 004h, 083h, 0C1h, 004h, 047h, 03Bh, 0C2h, 07Dh, 0F5h, 068h, 040h, 030h, 010h, 001h
    db 08Dh, 04Ch, 024h, 024h, 0E8h, 0F7h, 0DFh, 038h, 000h, 08Bh, 076h, 02Ch, 03Bh, 0F5h, 0C6h, 044h
    db 024h, 04Ch, 008h, 07Eh, 040h, 08Bh, 00Dh, 050h, 0D7h, 02Eh, 001h, 056h, 0E8h, 0F1h, 0CFh, 0B3h
    db 0FFh, 03Bh, 0C5h, 074h, 030h, 08Bh, 040h, 008h, 03Bh, 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh
    db 005h, 0B8h, 08Bh, 038h, 007h, 001h, 050h, 051h, 089h, 064h, 024h, 044h, 08Bh, 0CCh, 068h, 028h
    db 00Eh, 010h, 001h, 0E8h, 0B8h, 0DFh, 038h, 000h, 08Dh, 054h, 024h, 028h, 052h, 0E8h, 0DEh, 0E3h
    db 038h, 000h, 083h, 0C4h, 00Ch, 089h, 06Ch, 024h, 01Ch, 057h, 051h, 089h, 064h, 024h, 044h, 08Bh
    db 0CCh, 068h, 0E0h, 00Ch, 010h, 001h, 0C6h, 044h, 024h, 058h, 009h, 0E8h, 090h, 0DFh, 038h, 000h
    db 08Dh, 044h, 024h, 024h, 050h, 0E8h, 0B6h, 0E3h, 038h, 000h, 083h, 0C4h, 00Ch, 089h, 06Ch, 024h
    db 018h, 055h, 051h, 08Dh, 054h, 024h, 024h, 089h, 064h, 024h, 044h, 08Bh, 0CCh, 052h, 0C6h, 044h
    db 024h, 058h, 00Ah, 0E8h, 008h, 0CFh, 038h, 000h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 08Bh, 001h
    db 08Dh, 054h, 024h, 044h, 052h, 0FFh, 050h, 024h, 08Bh, 000h, 03Bh, 0C5h, 0B3h, 00Bh, 088h, 05Ch
    db 024h, 04Ch, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h, 08Ch, 038h, 007h, 001h, 050h, 055h
    db 051h, 08Dh, 044h, 024h, 02Ch, 089h, 064h, 024h, 04Ch, 08Bh, 0CCh, 050h, 0E8h, 0CFh, 0CEh, 038h
    db 000h, 08Bh, 00Dh, 07Ch, 014h, 02Fh, 001h, 08Bh, 011h, 08Dh, 044h, 024h, 044h, 050h, 0FFh, 052h
    db 024h, 08Bh, 000h, 03Bh, 0C5h, 0C6h, 044h, 024h, 050h, 00Ch, 074h, 005h, 083h, 0C0h, 008h, 0EBh
    db 005h, 0B8h, 08Ch, 038h, 007h, 001h, 050h, 051h, 089h, 064h, 024h, 04Ch, 08Bh, 0CCh, 068h, 028h
    db 030h, 010h, 001h, 0E8h, 018h, 0E1h, 038h, 000h, 08Dh, 04Ch, 024h, 024h, 051h, 0E8h, 0BEh, 0E4h
    db 038h, 000h, 083h, 0C4h, 010h, 08Dh, 04Ch, 024h, 038h, 088h, 05Ch, 024h, 04Ch, 0E8h, 0EEh, 0D4h
    db 038h, 000h, 08Dh, 04Ch, 024h, 03Ch, 0C6h, 044h, 024h, 04Ch, 00Ah, 0E8h, 0E0h, 0D4h, 038h, 000h
    db 08Dh, 054h, 024h, 018h, 052h, 08Dh, 04Ch, 024h, 060h, 0E8h, 0A4h, 0DDh, 0B1h, 0FFh, 068h, 000h
    db 000h, 0C0h, 03Fh, 055h, 06Ah, 0FFh, 051h, 08Dh, 044h, 024h, 06Ch, 089h, 064h, 024h, 050h, 08Bh
    db 0CCh, 050h, 0E8h, 0E9h, 0D6h, 038h, 000h, 08Bh, 00Dh, 05Ch, 04Ch, 02Fh, 001h, 0E8h, 0C7h, 099h
    db 0B3h, 0FFh, 08Dh, 04Ch, 024h, 018h, 0C6h, 044h, 024h, 04Ch, 009h, 0E8h, 0A0h, 0D4h, 038h, 000h
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 044h, 024h, 04Ch, 008h, 0E8h, 002h, 0CCh, 038h, 000h, 08Dh, 04Ch
    db 024h, 020h, 0C6h, 044h, 024h, 04Ch, 006h, 0E8h, 0F4h, 0CBh, 038h, 000h, 08Dh, 04Ch, 024h, 05Ch
    db 0C6h, 044h, 024h, 04Ch, 004h, 0E8h, 076h, 0D4h, 038h, 000h, 08Dh, 04Ch, 024h, 024h, 0C6h, 044h
    db 024h, 04Ch, 003h, 0E8h, 068h, 0D4h, 038h, 000h, 08Dh, 04Ch, 024h, 028h, 0C6h, 044h, 024h, 04Ch
    db 002h, 0E8h, 0CAh, 0CBh, 038h, 000h, 08Dh, 04Ch, 024h, 030h, 0C6h, 044h, 024h, 04Ch, 001h, 0E8h
    db 0BCh, 0CBh, 038h, 000h, 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 04Ch, 000h, 0E8h, 0AEh, 0CBh
    db 038h, 000h, 08Dh, 04Ch, 024h, 010h, 0C7h, 044h, 024h, 04Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 02Dh
    db 0D4h, 038h, 000h, 08Bh, 04Ch, 024h, 044h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh
    db 05Dh, 05Bh, 083h, 0C4h, 040h, 0C3h, 068h, 000h, 000h, 080h, 03Fh, 06Ah, 000h, 057h, 051h, 089h
    db 064h, 024h, 050h, 08Bh, 0CCh, 068h, 054h, 06Eh, 033h, 001h, 0E8h, 031h, 0D6h, 038h, 000h, 08Bh
    db 00Dh, 05Ch, 04Ch, 02Fh, 001h, 0E8h, 00Fh, 099h, 0B3h, 0FFh, 08Bh, 04Ch, 024h, 044h, 05Fh, 05Eh
    db 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 040h, 0C3h
?playerTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z ENDP
_TEXT ENDS
END
