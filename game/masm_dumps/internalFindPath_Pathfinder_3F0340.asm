.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?j_000059c0@@YAXXZ:NEAR
EXTERN ?j_00005e48@@YAXXZ:NEAR
EXTERN ?j_00010ea1@@YAXXZ:NEAR
EXTERN ?j_0001264d@@YAXXZ:NEAR
EXTERN ?j_000127a6@@YAXXZ:NEAR
EXTERN ?j_000171e8@@YAXXZ:NEAR
EXTERN ?j_0001a36b@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_0001fbbd@@YAXXZ:NEAR
EXTERN ?j_00020671@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_00021da0@@YAXXZ:NEAR
EXTERN ?j_00024ef1@@YAXXZ:NEAR
EXTERN ?j_0002f798@@YAXXZ:NEAR
EXTERN ?j_00032b5f@@YAXXZ:NEAR
EXTERN ?j_00036642@@YAXXZ:NEAR
EXTERN ?j_00036b33@@YAXXZ:NEAR
EXTERN ?j_0003a17a@@YAXXZ:NEAR
EXTERN ?j_0003a391@@YAXXZ:NEAR
EXTERN ?j_0003a828@@YAXXZ:NEAR
EXTERN ?j_0003b359@@YAXXZ:NEAR
EXTERN ?j_0003d1a9@@YAXXZ:NEAR
EXTERN ?j_0003d3ed@@YAXXZ:NEAR
EXTERN ?j_0003e9f5@@YAXXZ:NEAR
EXTERN ?j_00041bff@@YAXXZ:NEAR
EXTERN ?j_00042a37@@YAXXZ:NEAR
EXTERN ?j_0004375c@@YAXXZ:NEAR
EXTERN ?j_0004596c@@YAXXZ:NEAR
EXTERN ?j_000461ff@@YAXXZ:NEAR
EXTERN ?j_00047384@@YAXXZ:NEAR
EXTERN ?j_0004850e@@YAXXZ:NEAR
EXTERN ?j_00049f3f@@YAXXZ:NEAR
EXTERN ?j_0004a980@@YAXXZ:NEAR
EXTERN ?j_0004b3b7@@YAXXZ:NEAR
EXTERN __bfmeNullNameXZ:BYTE
EXTERN g_01075344:BYTE
EXTERN g_01075350:BYTE
EXTERN g_01099D80:BYTE
EXTERN g_010EF088:BYTE
EXTERN g_010EF0D4:BYTE
EXTERN g_010EF118:BYTE
EXTERN g_010EF16C:BYTE
EXTERN g_010EF1B8:BYTE
EXTERN g_010EF1F8:BYTE
EXTERN g_010EF238:BYTE
EXTERN g_010EF278:BYTE
EXTERN g_010EF2C8:BYTE
EXTERN g_010EF314:BYTE
EXTERN g_010EF354:BYTE
EXTERN g_010EF3A0:BYTE
EXTERN g_010EF3E0:BYTE
EXTERN g_010EF420:BYTE
EXTERN g_010EF460:BYTE
EXTERN g_010EF4A0:BYTE
EXTERN g_010EF4EC:BYTE
EXTERN g_010EF538:BYTE
EXTERN g_010EF584:BYTE
EXTERN g_010EF5C4:BYTE
EXTERN g_010EF610:BYTE
EXTERN g_010EF65C:BYTE
EXTERN g_010EF69C:BYTE
EXTERN g_012ED4FC:BYTE
EXTERN g_012EF4CC:BYTE
EXTERN g_012F0239:BYTE
EXTERN g_012F1060:BYTE
EXTERN g_012F1094:BYTE

; ?internalFindPath@Pathfinder@@MAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z
; Exact 2347 retail bytes @ 0x003F0340; Ghidra ENTRY 2347.
; Identity: embedded Pathfinder::InternalFindPath checkpoints, ret 10h, packed-cell A* loop.
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d007f0340 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007F0340 size 2347
public ?internalFindPath@Pathfinder@@MAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z
?internalFindPath@Pathfinder@@MAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z PROC
    db 0A1h
    dd g_012ED4FC
    db 081h, 0ECh, 088h, 000h, 000h, 000h, 055h, 056h, 057h, 033h, 0FFh, 03Bh, 0C7h, 08Bh, 0F1h, 074h
    db 00Eh, 068h
    dd g_010EF69C
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0ACh, 024h, 098h, 000h, 000h, 000h, 08Dh, 044h, 024h, 00Ch, 050h, 08Dh
    db 04Ch, 024h, 020h, 051h, 055h, 08Bh, 0CEh, 089h, 03Dh
    dd g_012F1060
    db 0C6h, 044h, 024h, 018h, 001h, 089h, 07Ch, 024h, 028h
    call ?j_000461ff@@YAXXZ
    db 08Bh, 0CDh, 0C6h, 044h, 024h, 044h, 001h
    call ?j_00020824@@YAXXZ
    db 085h, 0C0h, 074h, 03Bh, 08Bh, 0CDh
    call ?j_00020824@@YAXXZ
    db 083h, 078h, 02Ch, 001h, 075h, 02Eh, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 08Bh, 015h
    dd g_012ED4FC
    db 074h, 018h, 03Bh, 0D7h, 074h, 014h, 068h
    dd g_010EF65C
    db 052h
    call ?j_0003a17a@@YAXXZ
    db 08Bh, 015h
    dd g_012ED4FC
    db 083h, 0C4h, 008h, 0C6h, 044h, 024h, 044h, 000h, 0EBh, 006h, 08Bh, 015h
    dd g_012ED4FC
    db 0D9h, 005h
    dd g_01075350
    db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h, 0D9h, 001h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h
    db 07Ah, 03Bh, 0D9h, 005h
    dd g_01075350
    db 0D9h, 041h, 004h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 029h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 042h, 03Bh, 0D7h, 074h, 03Eh, 068h
    dd g_010EF610
    db 052h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 05Fh, 05Eh, 033h, 0C0h, 05Dh, 081h, 0C4h, 088h, 000h, 000h, 000h, 0C2h, 010h
    db 000h, 08Ah, 046h, 008h, 084h, 0C0h, 075h, 029h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 012h, 03Bh, 0D7h, 074h, 00Eh, 068h
    dd g_010EF5C4
    db 052h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 05Fh, 05Eh, 033h, 0C0h, 05Dh, 081h, 0C4h, 088h, 000h, 000h, 000h, 0C2h, 010h
    db 000h, 08Bh, 041h, 004h, 08Bh, 011h, 08Bh, 049h, 008h, 089h, 044h, 024h, 030h, 08Bh, 084h, 024h
    db 0A0h, 000h, 000h, 000h, 089h, 054h, 024h, 02Ch, 08Bh, 010h, 089h, 04Ch, 024h, 034h, 08Bh, 048h
    db 004h, 089h, 054h, 024h, 048h, 08Bh, 050h, 008h, 089h, 04Ch, 024h, 04Ch, 08Dh, 044h, 024h, 02Ch
    db 050h, 08Dh, 04Ch, 024h, 04Ch, 051h, 08Bh, 0CEh, 089h, 054h, 024h, 058h
    call ?j_00041bff@@YAXXZ
    db 08Ah, 044h, 024h, 00Ch, 084h, 0C0h, 075h, 03Ch, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 03Bh, 0C7h, 074h, 00Eh, 068h
    dd g_010EF584
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0D9h, 044h, 024h, 02Ch, 0D8h, 005h
    dd g_01075344
    db 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 030h, 0D8h, 005h
    dd g_01075344
    db 0D9h, 05Ch, 024h, 030h, 053h, 08Dh, 054h, 024h, 030h, 052h, 0C6h, 086h, 03Ch, 008h, 000h, 000h
    db 000h, 08Bh, 00Dh
    dd g_012EF4CC
    db 057h
    call ?j_0001c675@@YAXXZ
    db 08Bh, 0F8h, 08Dh, 044h, 024h, 028h, 050h, 08Dh, 04Ch, 024h, 034h, 051h, 08Bh, 0CEh, 089h, 07Ch
    db 024h, 060h
    call ?j_000171e8@@YAXXZ
    db 084h, 0C0h, 075h, 018h, 08Bh, 054h, 024h, 02Ch, 08Bh, 044h, 024h, 028h, 052h, 050h, 057h, 08Bh
    db 0CEh
    call ?j_00020671@@YAXXZ
    db 08Bh, 0D8h, 085h, 0DBh, 075h, 024h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 00Fh, 084h, 01Fh, 007h, 000h, 000h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 00Fh, 084h, 012h, 007h, 000h, 000h, 068h
    dd g_010EF538
    db 0E9h, 0FFh, 006h, 000h, 000h, 08Dh, 04Ch, 024h, 028h, 051h, 08Dh, 054h, 024h, 034h, 052h, 08Bh
    db 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 054h, 024h, 020h, 06Ah, 001h, 08Dh, 044h, 024h, 02Ch, 050h, 08Bh
    db 044h, 024h, 034h, 051h, 08Bh, 04Ch, 024h, 034h, 052h, 057h, 050h, 051h, 055h, 08Bh, 0CEh
    call ?j_00049f3f@@YAXXZ
    db 084h, 0C0h, 075h, 024h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 00Fh, 084h, 0C2h, 006h, 000h, 000h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 00Fh, 084h, 0B5h, 006h, 000h, 000h, 068h
    dd g_010EF4EC
    db 0E9h, 0A2h, 006h, 000h, 000h, 08Dh, 054h, 024h, 05Ch, 052h, 08Dh, 044h, 024h, 050h, 050h, 08Bh
    db 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Bh, 0CDh
    call ?j_0003a391@@YAXXZ
    db 08Dh, 04Ch, 024h, 04Ch, 051h, 050h, 08Bh, 0CEh, 089h, 044h, 024h, 030h
    call ?j_00047384@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 075h, 024h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 00Fh, 084h, 06Fh, 006h, 000h, 000h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 00Fh, 084h, 062h, 006h, 000h, 000h, 068h
    dd g_010EF4A0
    db 0E9h, 04Fh, 006h, 000h, 000h, 08Dh, 054h, 024h, 018h, 052h, 08Dh, 044h, 024h, 034h, 050h, 08Bh
    db 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Bh, 003h, 085h, 0C0h, 075h, 025h, 0A1h
    dd g_012F1094
    db 085h, 0C0h, 075h, 005h
    call ?j_0003d1a9@@YAXXZ
    db 08Dh, 04Ch, 024h, 018h, 051h, 053h, 068h
    dd g_012F1094
    call ?j_00021da0@@YAXXZ
    db 083h, 0C4h, 00Ch, 089h, 003h, 0EBh, 007h, 0C7h, 040h, 00Ch, 000h, 000h, 000h, 000h, 03Bh, 0FBh
    db 074h, 063h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF460
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Dh, 054h, 024h, 018h, 052h, 08Dh, 044h, 024h, 050h, 050h, 08Bh, 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Bh, 007h, 085h, 0C0h, 075h, 025h, 0A1h
    dd g_012F1094
    db 085h, 0C0h, 075h, 005h
    call ?j_0003d1a9@@YAXXZ
    db 08Dh, 04Ch, 024h, 018h, 051h, 057h, 068h
    dd g_012F1094
    call ?j_00021da0@@YAXXZ
    db 083h, 0C4h, 00Ch, 089h, 007h, 0EBh, 007h, 0C7h, 040h, 00Ch, 000h, 000h, 000h, 000h, 08Bh, 057h
    db 00Ch, 080h, 0E2h, 007h, 080h, 0FAh, 004h, 075h, 03Eh, 08Bh, 007h, 085h, 0C0h, 074h, 005h, 08Bh
    db 040h, 020h, 0EBh, 002h, 033h, 0C0h, 03Bh, 086h, 044h, 008h, 000h, 000h, 074h, 029h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF420
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 001h, 0EBh, 027h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF3E0
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 000h, 08Bh, 0CDh
    call ?j_00042a37@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 0B1h, 000h, 000h, 000h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF3A0
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 053h, 08Bh, 0CFh
    call ?j_0003e9f5@@YAXXZ
    db 053h, 057h, 08Bh, 0CEh
    call ?j_0003a828@@YAXXZ
    db 08Bh, 00Fh, 066h, 089h, 041h, 010h, 057h, 08Bh, 0CEh
    call ?j_00024ef1@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 094h, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 042h, 010h, 08Bh, 094h
    db 024h, 0A4h, 000h, 000h, 000h, 06Ah, 000h, 051h, 053h, 052h, 050h, 055h, 08Bh, 0CEh
    call ?j_000059c0@@YAXXZ
    db 08Bh, 0CBh, 08Bh, 0F8h
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00032b5f@@YAXXZ
    db 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 027h, 08Bh, 00Dh
    dd g_012ED4FC
    db 085h, 0C9h, 074h, 01Dh, 085h, 0FFh, 0B8h
    dd g_01099D80
    db 075h, 005h, 0B8h
    dd __bfmeNullNameXZ
    db 050h, 068h
    dd g_010EF354
    db 051h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 00Ch, 05Bh, 08Bh, 0C7h, 05Fh, 05Eh, 05Dh, 081h, 0C4h, 088h, 000h, 000h, 000h, 0C2h
    db 010h, 000h, 08Bh, 0CDh
    call ?j_00010ea1@@YAXXZ
    db 08Bh, 0CDh, 088h, 044h, 024h, 014h
    call ?j_0001fbbd@@YAXXZ
    db 048h, 08Bh, 0CDh, 089h, 044h, 024h, 018h
    call ?j_00036b33@@YAXXZ
    db 08Bh, 08Ch, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 051h, 010h, 08Bh, 04Ch, 024h, 018h, 0F6h, 0D8h
    db 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 040h, 08Ah, 044h, 024h, 014h, 088h, 044h, 024h, 041h
    db 089h, 054h, 024h, 03Ch, 089h, 04Ch, 024h, 044h, 033h, 0C0h, 066h, 08Bh, 047h, 008h, 08Dh, 054h
    db 024h, 03Ch, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h, 050h, 052h
    call ?j_0004375c@@YAXXZ
    db 00Fh, 0B7h, 0C0h, 089h, 044h, 024h, 018h, 033h, 0C0h, 066h, 08Bh, 043h, 008h, 08Dh, 04Ch, 024h
    db 03Ch, 050h, 051h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_0004375c@@YAXXZ
    db 00Fh, 0B7h, 0D0h, 08Bh, 086h, 044h, 008h, 000h, 000h, 050h, 08Bh, 0CBh, 089h, 054h, 024h, 028h
    call ?j_0004850e@@YAXXZ
    db 084h, 0C0h, 075h, 020h, 08Bh, 086h, 044h, 008h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?j_0004850e@@YAXXZ
    db 084h, 0C0h, 075h, 00Eh, 08Ah, 086h, 03Ch, 008h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 080h, 000h
    db 000h, 000h, 08Bh, 044h, 024h, 024h, 050h, 08Dh, 04Ch, 024h, 040h, 051h, 08Dh, 08Eh, 09Ch, 00Ch
    db 000h, 000h
    call ?j_0004596c@@YAXXZ
    db 00Fh, 0B7h, 0C0h, 050h, 08Dh, 054h, 024h, 040h, 052h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_0004375c@@YAXXZ
    db 08Bh, 04Ch, 024h, 018h, 00Fh, 0B7h, 0C0h, 051h, 08Dh, 054h, 024h, 040h, 052h, 08Dh, 08Eh, 09Ch
    db 00Ch, 000h, 000h, 089h, 044h, 024h, 02Ch
    call ?j_0004596c@@YAXXZ
    db 00Fh, 0B7h, 0C0h, 050h, 08Dh, 044h, 024h, 040h, 050h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_0004375c@@YAXXZ
    db 00Fh, 0B7h, 0C8h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 089h, 04Ch, 024h, 018h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF314
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 054h, 024h, 024h, 039h, 054h, 024h, 018h, 074h, 048h, 08Bh, 04Ch, 024h
    db 018h, 06Ah, 000h, 08Bh, 0C2h, 050h, 051h, 055h, 08Bh, 0CEh
    call ?j_0002f798@@YAXXZ
    db 084h, 0C0h, 075h, 032h, 08Bh, 0CBh
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CFh
    call ?j_0004b3b7@@YAXXZ
    db 0A0h
    dd g_012F0239
    db 084h, 0C0h, 00Fh, 084h, 00Fh, 003h, 000h, 000h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 00Fh, 084h, 002h, 003h, 000h, 000h, 068h
    dd g_010EF2C8
    db 0E9h, 0EFh, 002h, 000h, 000h, 08Bh, 094h, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 042h, 010h, 055h
    db 050h, 08Bh, 044h, 024h, 060h, 050h, 08Dh, 04Ch, 024h, 03Ch, 051h, 08Bh, 0CEh
    call ?j_0003b359@@YAXXZ
    db 084h, 0C0h, 075h, 038h, 08Bh, 0CBh, 088h, 086h, 03Ch, 008h, 000h, 000h
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CFh
    call ?j_0004b3b7@@YAXXZ
    db 0A0h
    dd g_012F0239
    db 084h, 0C0h, 00Fh, 084h, 0B6h, 002h, 000h, 000h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 00Fh, 084h, 0A9h, 002h, 000h, 000h, 068h
    dd g_010EF278
    db 0E9h, 096h, 002h, 000h, 000h, 08Bh, 094h, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 042h, 010h, 08Bh
    db 08Ch, 024h, 0A4h, 000h, 000h, 000h, 055h, 050h, 08Bh, 044h, 024h, 030h, 050h, 051h, 08Bh, 0CEh
    call ?j_0003b359@@YAXXZ
    db 084h, 0C0h, 075h, 027h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF238
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 001h, 08Ah, 086h, 03Ch, 008h, 000h, 000h
    db 084h, 0C0h, 00Fh, 085h, 0B9h, 000h, 000h, 000h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF1F8
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Dh, 04Ch, 024h, 064h
    call ?j_00036642@@YAXXZ
    db 08Bh, 04Ch, 024h, 020h, 08Bh, 057h, 00Ch, 08Ah, 044h, 024h, 010h, 0C1h, 0EAh, 006h, 089h, 04Ch
    db 024h, 070h, 08Bh, 08Dh, 004h, 002h, 000h, 000h, 083h, 0E2h, 03Fh, 085h, 0C9h, 089h, 054h, 024h
    db 06Ch, 088h, 044h, 024h, 074h, 0C7h, 044h, 024h, 078h, 000h, 000h, 000h, 000h, 074h, 00Bh
    call ?j_0001a36b@@YAXXZ
    db 089h, 044h, 024h, 07Ch, 0EBh, 008h, 0C7h, 044h, 024h, 07Ch, 000h, 000h, 000h, 000h, 08Dh, 054h
    db 024h, 064h, 052h, 08Dh, 044h, 024h, 050h, 050h, 08Bh, 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Dh, 04Ch, 024h, 064h, 051h, 055h, 08Bh, 0CEh, 0C6h, 044h, 024h, 07Dh, 001h
    call ?j_0004a980@@YAXXZ
    db 084h, 0C0h, 075h, 027h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF1B8
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 001h, 053h, 08Bh, 0CFh
    call ?j_0003e9f5@@YAXXZ
    db 053h, 057h, 08Bh, 0CEh
    call ?j_0003a828@@YAXXZ
    db 08Bh, 017h, 057h, 08Bh, 0CEh, 066h, 089h, 042h, 010h
    call ?j_00024ef1@@YAXXZ
    db 08Bh, 0CEh, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h
    call ?j_0003d3ed@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 000h, 001h, 000h, 000h, 03Bh, 0FBh, 074h, 063h, 08Dh, 086h
    db 038h, 008h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?j_00005e48@@YAXXZ
    db 081h, 07Ch, 024h, 018h, 098h, 03Ah, 000h, 000h, 00Fh, 08Fh, 0C0h, 000h, 000h, 000h, 055h, 057h
    db 08Bh, 0CEh
    call ?j_0001264d@@YAXXZ
    db 08Bh, 054h, 024h, 020h, 08Bh, 044h, 024h, 010h, 06Ah, 000h, 055h, 08Dh, 04Ch, 024h, 064h, 051h
    db 08Bh, 04Ch, 024h, 054h, 052h, 08Bh, 094h, 024h, 0B0h, 000h, 000h, 000h, 050h, 051h, 052h, 053h
    db 057h, 08Bh, 0CEh
    call ?j_000127a6@@YAXXZ
    db 001h, 044h, 024h, 018h, 08Bh, 0CEh
    call ?j_0003d3ed@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 075h, 09Eh, 0E9h, 099h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh
    db 094h, 024h, 0A4h, 000h, 000h, 000h, 08Bh, 084h, 024h, 0A0h, 000h, 000h, 000h, 06Ah, 000h, 051h
    db 053h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 000h, 08Bh, 040h, 010h, 052h, 050h, 055h, 08Bh, 0CEh
    call ?j_000059c0@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0D8h
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00032b5f@@YAXXZ
    db 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 027h, 08Bh, 00Dh
    dd g_012ED4FC
    db 085h, 0C9h, 074h, 01Dh, 085h, 0DBh, 0B8h
    dd g_01099D80
    db 075h, 005h, 0B8h
    dd __bfmeNullNameXZ
    db 050h, 068h
    dd g_010EF16C
    db 051h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 00Ch, 08Bh, 0C3h, 05Bh, 05Fh, 05Eh, 05Dh, 081h, 0C4h, 088h, 000h, 000h, 000h, 0C2h
    db 010h, 000h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 037h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF118
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF0D4
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0CEh, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 000h
    call ?j_00032b5f@@YAXXZ
    db 08Bh, 0CBh
    call ?j_0004b3b7@@YAXXZ
    db 0A0h
    dd g_012F0239
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd g_012ED4FC
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_010EF088
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 05Bh, 05Fh, 05Eh, 033h, 0C0h, 05Dh, 081h, 0C4h, 088h, 000h, 000h, 000h, 0C2h
    db 010h, 000h
?internalFindPath@Pathfinder@@MAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z ENDP
_TEXT$d007f0340 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
