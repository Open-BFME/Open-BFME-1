.386
.model flat

; ??1GenericObjectCreationNugget@@MAE@XZ
; Exact 144B retail @ 0x001D8220.
; Identity: ctor @ 0x001D7D70 stores vtbl 0x109F5E8; slot0 scalar-deleting dtor @ 0x001D81F0
; calls this body (thunk 0x0004706E). Queue 0x000FB453 was INSIDE another fn (ret 8 @ 0xFB4AD).
; sizeof class 0x148 (parseDebris); member teardown +0x94,+0x80,+0x24,+0x14,+0x10,+0x4 then base vtbl.
_TEXT SEGMENT
public ??1GenericObjectCreationNugget@@MAE@XZ
??1GenericObjectCreationNugget@@MAE@XZ PROC
    db 06Ah, 0FFh, 068h, 002h, 09Ch, 000h, 001h, 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 051h, 056h, 08Bh, 0F1h, 089h, 074h, 024h, 004h, 0C7h, 006h, 0E8h
    db 0F5h, 009h, 001h, 08Dh, 08Eh, 094h, 000h, 000h, 000h, 0C7h, 044h, 024h, 010h, 005h, 000h, 000h
    db 000h, 0E8h, 0DFh, 0ECh, 0E4h, 0FFh, 08Dh, 08Eh, 080h, 000h, 000h, 000h, 0C6h, 044h, 024h, 010h
    db 004h, 0E8h, 0DAh, 0F6h, 06Ah, 000h, 08Dh, 04Eh, 024h, 0C6h, 044h, 024h, 010h, 003h, 0E8h, 0CDh
    db 0F6h, 06Ah, 000h, 08Dh, 04Eh, 014h, 0C6h, 044h, 024h, 010h, 002h, 0E8h, 0F5h, 0E0h, 0E2h, 0FFh
    db 08Dh, 04Eh, 010h, 0C6h, 044h, 024h, 010h, 001h, 0E8h, 0B3h, 0F6h, 06Ah, 000h, 08Dh, 04Eh, 004h
    db 0C6h, 044h, 024h, 010h, 000h, 0E8h, 018h, 0E8h, 0E4h, 0FFh, 08Bh, 04Ch, 024h, 008h, 0C7h, 006h
    db 0C4h, 0F0h, 009h, 001h, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C3h
??1GenericObjectCreationNugget@@MAE@XZ ENDP
_TEXT ENDS
END
