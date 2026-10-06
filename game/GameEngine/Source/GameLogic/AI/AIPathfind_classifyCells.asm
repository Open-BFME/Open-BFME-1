.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?forward@Rva0000DAADBridgeThunk@@QAE_NPBURegion2D@@@Z:NEAR
EXTERN ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z:NEAR
EXTERN ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z:NEAR
EXTERN ?j_00017e27@@YAXXZ:NEAR
EXTERN ?j_00019e9d@@YAXXZ:NEAR
EXTERN ?j_0001cf49@@YAXXZ:NEAR
EXTERN ?j_0002c106@@YAXXZ:NEAR
EXTERN ?j_00041862@@YAXXZ:NEAR
EXTERN __imp__floor:BYTE
EXTERN g_01075334:BYTE
EXTERN g_01075344:BYTE
EXTERN g_01075350:BYTE
EXTERN g_01075C70:BYTE
EXTERN g_01075C74:BYTE
EXTERN g_0109C34C:BYTE
EXTERN g_012EF214:BYTE
EXTERN g_012EF4CC:BYTE

; ?classifyCells@PathfindLayer@@QAEXXZ
; Exact 1405 retail bytes @ 0x003FC790
; True ENTRY (queue 0x73F191 was mid-body of unrelated host).
; C++ blocked by PathfindCell 0x10 packing + PathfindLayer m_bridge@+0x38.
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d007fc790 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007FC790 size 1405
public ?classifyCells@PathfindLayer@@QAEXXZ
?classifyCells@PathfindLayer@@QAEXXZ PROC
    db 055h, 08Bh, 0ECh, 083h, 0E4h, 0F8h, 081h, 0ECh, 0E8h, 000h, 000h, 000h, 083h, 0C8h, 0FFh, 053h
    db 08Bh, 0D9h, 055h, 089h, 043h, 018h, 089h, 043h, 01Ch, 089h, 043h, 020h, 089h, 043h, 024h, 08Bh
    db 043h, 008h, 033h, 0EDh, 03Bh, 0C5h, 056h, 057h, 089h, 06Ch, 024h, 01Ch, 00Fh, 08Eh, 09Bh, 004h
    db 000h, 000h, 039h, 06Bh, 00Ch, 089h, 06Ch, 024h, 030h, 00Fh, 08Eh, 01Bh, 003h, 000h, 000h, 089h
    db 06Ch, 024h, 02Ch, 08Bh, 043h, 004h, 08Bh, 04Ch, 024h, 01Ch, 08Bh, 034h, 088h, 08Bh, 044h, 024h
    db 02Ch, 08Bh, 06Ch, 006h, 00Ch, 003h, 0F0h, 081h, 0E5h, 0FFh, 00Fh, 0FCh, 0FFh, 089h, 06Eh, 00Ch
    db 08Bh, 053h, 028h, 08Bh, 0C5h, 0C1h, 0E2h, 006h, 033h, 0D0h, 081h, 0E2h, 0C0h, 00Fh, 000h, 000h
    db 033h, 0D0h, 08Bh, 044h, 024h, 030h, 089h, 056h, 00Ch, 08Bh, 07Bh, 014h, 08Bh, 06Bh, 010h, 003h
    db 0F8h, 089h, 07Ch, 024h, 018h, 0DBh, 044h, 024h, 018h, 003h, 0E9h, 08Bh, 04Bh, 038h, 089h, 06Ch
    db 024h, 014h, 0D8h, 00Dh
    dd g_01075C74
    db 08Dh, 044h, 024h, 020h, 050h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 0D9h, 054h, 024h
    db 028h, 0D8h, 005h
    dd g_01075C74
    db 0D9h, 05Ch, 024h, 048h, 0DBh, 044h, 024h, 018h, 0D8h, 00Dh
    dd g_01075C74
    db 0D9h, 054h, 024h, 024h, 0D8h, 005h
    dd g_01075C74
    db 0D9h, 05Ch, 024h, 044h
    call ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
    db 084h, 0C0h, 074h, 008h, 0C7h, 044h, 024h, 018h, 001h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 020h
    db 08Bh, 054h, 024h, 024h, 08Bh, 044h, 024h, 028h, 089h, 04Ch, 024h, 034h, 08Bh, 04Ch, 024h, 044h
    db 089h, 054h, 024h, 038h, 08Dh, 054h, 024h, 034h, 089h, 04Ch, 024h, 038h, 08Bh, 04Bh, 038h, 052h
    db 089h, 044h, 024h, 040h
    call ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
    db 084h, 0C0h, 074h, 004h, 0FFh, 044h, 024h, 018h, 08Bh, 04Bh, 038h, 08Dh, 044h, 024h, 040h, 050h
    call ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
    db 084h, 0C0h, 074h, 004h, 0FFh, 044h, 024h, 018h, 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 024h
    db 08Bh, 044h, 024h, 028h, 089h, 04Ch, 024h, 034h, 08Bh, 04Ch, 024h, 040h, 089h, 054h, 024h, 038h
    db 08Dh, 054h, 024h, 034h, 089h, 04Ch, 024h, 034h, 08Bh, 04Bh, 038h, 052h, 089h, 044h, 024h, 040h
    call ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
    db 084h, 0C0h, 074h, 004h, 0FFh, 044h, 024h, 018h, 08Bh, 0CEh
    call ?j_0002c106@@YAXXZ
    db 08Bh, 043h, 028h, 08Bh, 04Eh, 00Ch, 0C1h, 0E0h, 006h, 033h, 0C1h, 025h, 0C0h, 00Fh, 000h, 000h
    db 033h, 0C8h, 089h, 04Eh, 00Ch, 06Ah, 005h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 083h, 0F8h, 004h, 075h, 00Eh, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 0E9h, 0DCh, 000h, 000h, 000h, 085h, 0C0h, 074h, 009h, 06Ah, 006h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 024h, 08Bh, 044h, 024h, 040h, 089h, 04Ch, 024h, 074h
    db 08Bh, 04Ch, 024h, 044h, 089h, 054h, 024h, 078h, 08Dh, 054h, 024h, 074h, 089h, 08Ch, 024h, 080h
    db 000h, 000h, 000h, 08Bh, 04Bh, 038h, 052h, 089h, 084h, 024h, 080h, 000h, 000h, 000h
    call ?j_00041862@@YAXXZ
    db 084h, 0C0h, 074h, 00Eh, 06Ah, 006h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 0E9h, 08Ah, 000h, 000h, 000h, 08Bh, 04Bh, 038h, 08Dh, 044h, 024h, 074h, 050h
    call ?forward@Rva0000DAADBridgeThunk@@QAE_NPBURegion2D@@@Z
    db 084h, 0C0h, 074h, 009h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 08Dh, 08Ch, 024h, 084h, 000h, 000h, 000h, 051h, 08Bh, 04Bh, 038h, 08Dh, 054h, 024h, 078h, 052h
    call ?j_0001cf49@@YAXXZ
    db 084h, 0C0h, 074h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00017e27@@YAXXZ
    db 08Bh, 046h, 00Ch, 025h, 0FFh, 01Fh, 0FCh, 0FFh, 00Dh, 000h, 010h, 000h, 000h, 089h, 046h, 00Ch
    db 08Bh, 00Dh
    dd g_012EF214
    db 08Bh, 049h, 00Ch, 03Bh, 069h, 014h, 07Ch, 01Ch, 03Bh, 069h, 01Ch, 07Fh, 017h, 03Bh, 079h, 018h
    db 07Ch, 012h, 03Bh, 079h, 020h, 07Fh, 00Dh, 08Bh, 051h, 010h, 08Bh, 0CFh, 0C1h, 0E1h, 004h, 003h
    db 00Ch, 0AAh, 0EBh, 002h, 033h, 0C9h, 08Bh, 051h, 00Ch, 0C1h, 0E0h, 006h, 033h, 0C2h, 025h, 000h
    db 0F0h, 003h, 000h, 033h, 0D0h, 089h, 051h, 00Ch, 0D9h, 044h, 024h, 020h, 08Bh, 044h, 024h, 028h
    db 0D8h, 005h
    dd g_01075344
    db 089h, 044h, 024h, 05Ch, 0D9h, 05Ch, 024h, 054h, 0D9h, 044h, 024h, 024h, 0D8h, 005h
    dd g_01075344
    db 0D9h, 05Ch, 024h, 058h, 08Bh, 076h, 00Ch, 08Bh, 0CEh, 083h, 0E1h, 007h, 080h, 0F9h, 005h, 00Fh
    db 084h, 091h, 000h, 000h, 000h, 081h, 0E6h, 000h, 0F0h, 003h, 000h, 081h, 0FEh, 000h, 010h, 000h
    db 000h, 00Fh, 084h, 07Fh, 000h, 000h, 000h, 08Bh, 044h, 024h, 058h, 08Bh, 00Dh
    dd g_012EF4CC
    db 08Bh, 011h, 06Ah, 001h, 06Ah, 000h, 06Ah, 001h, 050h, 08Bh, 044h, 024h, 064h, 050h, 0FFh, 052h
    db 01Ch, 0D8h, 005h
    dd g_01075C74
    db 06Ah, 000h, 08Dh, 04Ch, 024h, 058h, 051h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 04Bh, 038h
    call ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
    db 0D8h, 05Ch, 024h, 014h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 040h, 08Bh, 015h
    dd g_012EF214
    db 08Bh, 042h, 00Ch, 03Bh, 068h, 014h, 07Ch, 01Ch, 03Bh, 068h, 01Ch, 07Fh, 017h, 03Bh, 078h, 018h
    db 07Ch, 012h, 03Bh, 078h, 020h, 07Fh, 00Dh, 08Bh, 040h, 010h, 08Bh, 00Ch, 0A8h, 0C1h, 0E7h, 004h
    db 003h, 0F9h, 0EBh, 002h, 033h, 0FFh, 08Bh, 04Fh, 00Ch, 080h, 0E1h, 007h, 080h, 0F9h, 004h, 074h
    db 009h, 06Ah, 006h, 08Bh, 0CFh
    call ?j_00017e27@@YAXXZ
    db 08Bh, 044h, 024h, 030h, 08Bh, 054h, 024h, 02Ch, 08Bh, 04Bh, 00Ch, 040h, 083h, 0C2h, 010h, 03Bh
    db 0C1h, 089h, 044h, 024h, 030h, 089h, 054h, 024h, 02Ch, 00Fh, 08Ch, 0EBh, 0FCh, 0FFh, 0FFh, 033h
    db 0EDh, 08Dh, 08Ch, 024h, 088h, 000h, 000h, 000h
    call ?j_00019e9d@@YAXXZ
    db 08Bh, 043h, 038h, 08Dh, 070h, 00Ch, 0B9h, 01Bh, 000h, 000h, 000h, 08Dh, 0BCh, 024h, 088h, 000h
    db 000h, 000h, 0F3h, 0A5h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 0A4h, 024h, 088h, 000h
    db 000h, 000h, 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 0A4h, 024h, 08Ch, 000h, 000h, 000h
    db 0D9h, 084h, 024h, 09Ch, 000h, 000h, 000h, 0D8h, 0A4h, 024h, 090h, 000h, 000h, 000h, 0D9h, 0C0h
    db 0DEh, 0C9h, 0D9h, 0C1h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh
    db 0D9h, 005h
    dd g_01075350
    db 0D9h, 0C1h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Eh, 0D8h, 03Dh
    dd g_01075334
    db 0D9h, 0C0h, 0DEh, 0CBh, 0DEh, 0C9h, 0EBh, 002h, 0DDh, 0D8h, 0D9h, 0C9h, 083h, 0ECh, 008h, 0D8h
    db 00Dh
    dd g_0109C34C
    db 0D9h, 05Ch, 024h, 06Ch, 0D8h, 00Dh
    dd g_0109C34C
    db 0D9h, 05Ch, 024h, 070h, 0D9h, 084h, 024h, 090h, 000h, 000h, 000h, 0D8h, 064h, 024h, 06Ch, 0D8h
    db 00Dh
    dd g_01075C70
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 014h, 0DBh, 05Ch, 024h, 050h, 0D9h
    db 084h, 024h, 08Ch, 000h, 000h, 000h, 0D8h, 064h, 024h, 068h, 08Bh, 054h, 024h, 050h, 083h, 0ECh
    db 008h, 089h, 053h, 018h, 0D8h, 00Dh
    dd g_01075C70
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 014h, 0DBh, 05Ch, 024h, 060h, 0D9h
    db 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 044h, 024h, 064h, 08Bh, 044h, 024h, 060h, 083h, 0ECh
    db 008h, 089h, 043h, 01Ch, 0D8h, 00Dh
    dd g_01075C70
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 014h, 0DBh, 05Ch, 024h, 070h, 0D9h
    db 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 044h, 024h, 068h, 08Bh, 04Ch, 024h, 070h, 083h, 0ECh
    db 008h, 089h, 04Bh, 020h, 0D8h, 00Dh
    dd g_01075C70
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 014h, 0DBh, 05Ch, 024h, 04Ch, 08Bh
    db 054h, 024h, 04Ch, 08Bh, 044h, 024h, 01Ch, 089h, 053h, 024h, 08Bh, 04Bh, 008h, 040h, 03Bh, 0C1h
    db 089h, 044h, 024h, 01Ch, 00Fh, 08Ch, 065h, 0FBh, 0FFh, 0FFh, 08Ah, 043h, 034h, 084h, 0C0h, 00Fh
    db 084h, 09Dh, 000h, 000h, 000h, 039h, 06Bh, 008h, 089h, 06Ch, 024h, 01Ch, 00Fh, 08Eh, 090h, 000h
    db 000h, 000h, 08Bh, 043h, 00Ch, 033h, 0FFh, 03Bh, 0C5h, 07Eh, 073h, 08Bh, 0FFh, 08Bh, 043h, 004h
    db 08Bh, 04Ch, 024h, 01Ch, 08Bh, 00Ch, 088h, 08Bh, 044h, 029h, 00Ch, 003h, 0CDh, 0C1h, 0E8h, 00Ch
    db 083h, 0E0h, 03Fh, 083h, 0F8h, 001h, 074h, 005h, 083h, 0F8h, 010h, 07Ch, 03Dh, 08Bh, 015h
    dd g_012EF214
    db 08Bh, 072h, 00Ch, 08Bh, 053h, 010h, 08Bh, 043h, 014h, 003h, 054h, 024h, 01Ch, 003h, 0C7h, 03Bh
    db 056h, 014h, 07Ch, 023h, 03Bh, 056h, 01Ch, 07Fh, 01Eh, 03Bh, 046h, 018h, 07Ch, 019h, 03Bh, 046h
    db 020h, 07Fh, 014h, 08Bh, 076h, 010h, 0C1h, 0E0h, 004h, 003h, 004h, 096h, 085h, 0C0h, 074h, 007h
    db 081h, 060h, 00Ch, 0FFh, 00Fh, 0FCh, 0FFh, 06Ah, 006h
    call ?j_00017e27@@YAXXZ
    db 08Bh, 043h, 00Ch, 047h, 083h, 0C5h, 010h, 03Bh, 0F8h, 07Ch, 091h, 033h, 0EDh, 08Bh, 044h, 024h
    db 01Ch, 08Bh, 04Bh, 008h, 040h, 03Bh, 0C1h, 089h, 044h, 024h, 01Ch, 00Fh, 08Ch, 070h, 0FFh, 0FFh
    db 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 0E5h, 05Dh, 0C3h
?classifyCells@PathfindLayer@@QAEXXZ ENDP
_TEXT$d007fc790 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
