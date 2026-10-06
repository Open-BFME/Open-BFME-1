.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?R3FieldSlope1096CF4@@3MA:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheMixFileInfoPool@@3HA:BYTE
EXTERN ?j_0000145b@@YAXXZ:NEAR
EXTERN ?j_00005e48@@YAXXZ:NEAR
EXTERN ?j_0000ca68@@YAXXZ:NEAR
EXTERN ?j_0000dbe8@@YAXXZ:NEAR
EXTERN ?j_00010ea1@@YAXXZ:NEAR
EXTERN ?j_00010fa5@@YAXXZ:NEAR
EXTERN ?j_000114f5@@YAXXZ:NEAR
EXTERN ?j_0001264d@@YAXXZ:NEAR
EXTERN ?j_000169c3@@YAXXZ:NEAR
EXTERN ?j_000171e8@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_0001fa14@@YAXXZ:NEAR
EXTERN ?j_0001fbbd@@YAXXZ:NEAR
EXTERN ?j_00020671@@YAXXZ:NEAR
EXTERN ?j_00020da1@@YAXXZ:NEAR
EXTERN ?j_00021da0@@YAXXZ:NEAR
EXTERN ?j_00024ef1@@YAXXZ:NEAR
EXTERN ?j_00032b5f@@YAXXZ:NEAR
EXTERN ?j_00035a2b@@YAXXZ:NEAR
EXTERN ?j_00036b33@@YAXXZ:NEAR
EXTERN ?j_0003a828@@YAXXZ:NEAR
EXTERN ?j_0003d1a9@@YAXXZ:NEAR
EXTERN ?j_0003d3ed@@YAXXZ:NEAR
EXTERN ?j_0003e9f5@@YAXXZ:NEAR
EXTERN ?j_00040313@@YAXXZ:NEAR
EXTERN ?j_00041bff@@YAXXZ:NEAR
EXTERN ?j_0004375c@@YAXXZ:NEAR
EXTERN ?j_00043d15@@YAXXZ:NEAR
EXTERN ?j_00047384@@YAXXZ:NEAR
EXTERN ?j_00048d29@@YAXXZ:NEAR
EXTERN ?j_0004b3b7@@YAXXZ:NEAR
EXTERN __ftol2:NEAR
EXTERN __real@4f800000:BYTE
EXTERN g_Va012B4B10:BYTE
EXTERN g_Va012B4B38:BYTE

; ?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z
; Exact 2045 retail bytes @ 0x003F2160
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d007f2160 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007F2160 size 2045
public ?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z
?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z PROC
    db 083h, 0ECh, 064h, 053h, 055h, 056h, 08Bh, 0F1h, 057h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_0000145b@@YAXXZ
    db 08Bh, 08Eh, 00Ch, 047h, 002h, 000h, 08Bh, 086h, 010h, 047h, 002h, 000h, 06Ah, 000h, 08Dh, 054h
    db 024h, 07Ch, 052h, 051h, 050h, 050h
    call ?j_0000dbe8@@YAXXZ
    db 08Bh, 0BCh, 024h, 094h, 000h, 000h, 000h, 08Bh, 09Ch, 024h, 090h, 000h, 000h, 000h, 083h, 0C4h
    db 014h, 06Ah, 000h, 06Ah, 000h, 057h, 053h, 089h, 086h, 010h, 047h, 002h, 000h, 08Bh, 084h, 024h
    db 088h, 000h, 000h, 000h, 050h, 06Ah, 001h, 06Ah, 001h, 08Bh, 0CEh
    call ?j_0001fa14@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 074h, 012h, 08Bh, 0CDh
    call ?j_0000ca68@@YAXXZ
    db 055h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0EBh, 00Bh, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_00010fa5@@YAXXZ
    db 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 007h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 016h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 047h, 004h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 00Fh, 08Bh, 0C3h, 003h, 000h, 000h
    db 08Ah, 046h, 008h, 084h, 0C0h, 00Fh, 084h, 0B8h, 003h, 000h, 000h, 08Bh, 00Fh, 08Bh, 057h, 004h
    db 08Bh, 047h, 008h, 089h, 04Ch, 024h, 038h, 08Bh, 00Bh, 089h, 054h, 024h, 03Ch, 08Bh, 053h, 004h
    db 089h, 04Ch, 024h, 024h, 08Dh, 04Ch, 024h, 038h, 089h, 054h, 024h, 028h, 051h, 089h, 044h, 024h
    db 044h, 08Bh, 043h, 008h, 08Dh, 054h, 024h, 028h, 052h, 08Bh, 0CEh, 089h, 044h, 024h, 034h
    call ?j_00041bff@@YAXXZ
    db 08Bh, 04Ch, 024h, 078h, 08Dh, 044h, 024h, 038h, 050h, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 000h
    db 051h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    call ?j_0001c675@@YAXXZ
    db 08Bh, 0F8h, 08Dh, 054h, 024h, 014h, 052h, 08Dh, 044h, 024h, 03Ch, 050h, 08Bh, 0CEh, 089h, 07Ch
    db 024h, 018h
    call ?j_000171e8@@YAXXZ
    db 08Bh, 09Ch, 024h, 084h, 000h, 000h, 000h, 08Bh, 06Ch, 024h, 018h, 06Ah, 001h, 053h, 057h, 08Bh
    db 07Ch, 024h, 020h, 055h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0D8h, 00Fh, 084h, 071h, 001h, 000h, 000h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 001h
    db 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 094h, 024h, 080h, 000h, 000h, 000h, 06Ah, 001h
    db 053h, 051h, 055h, 089h, 07Ch, 024h, 02Ch, 003h, 0FAh, 057h, 06Ah, 000h, 08Bh, 0CEh, 089h, 06Ch
    db 024h, 038h
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 024h, 001h, 000h, 000h, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 08Bh
    db 054h, 024h, 010h, 06Ah, 001h, 053h, 052h, 003h, 0E8h, 055h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 000h, 001h, 000h, 000h, 08Bh, 044h, 024h, 010h, 08Bh, 094h, 024h, 080h
    db 000h, 000h, 000h, 06Ah, 001h, 053h, 050h, 055h, 02Bh, 0FAh, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 0DCh, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 094h, 024h, 080h
    db 000h, 000h, 000h, 06Ah, 001h, 053h, 051h, 055h, 02Bh, 0FAh, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 0B8h, 000h, 000h, 000h, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 08Bh
    db 054h, 024h, 010h, 06Ah, 001h, 053h, 052h, 02Bh, 0E8h, 055h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 094h, 000h, 000h, 000h, 08Bh, 094h, 024h, 080h, 000h, 000h, 000h, 08Bh
    db 044h, 024h, 010h, 06Ah, 001h, 053h, 050h, 02Bh, 0EAh, 055h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 074h, 074h, 08Bh, 04Ch, 024h, 010h, 08Bh, 094h, 024h, 080h, 000h, 000h, 000h, 06Ah
    db 001h, 053h, 051h, 055h, 003h, 0FAh, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 074h, 054h, 08Bh, 054h, 024h, 010h, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 06Ah
    db 001h, 053h, 052h, 055h, 003h, 0F8h, 057h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 03Bh, 0C3h, 074h, 034h, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 08Bh, 07Ch, 024h, 01Ch, 08Bh
    db 06Ch, 024h, 020h, 040h, 083h, 0F8h, 008h, 089h, 084h, 024h, 080h, 000h, 000h, 000h, 00Fh, 08Ch
    db 0C4h, 0FEh, 0FFh, 0FFh, 089h, 07Ch, 024h, 014h, 05Fh, 05Eh, 089h, 06Ch, 024h, 010h, 05Dh, 033h
    db 0C0h, 05Bh, 083h, 0C4h, 064h, 0C2h, 010h, 000h, 083h, 0BCh, 024h, 080h, 000h, 000h, 000h, 008h
    db 089h, 06Ch, 024h, 018h, 089h, 07Ch, 024h, 014h, 00Fh, 08Dh, 0B5h, 001h, 000h, 000h, 08Bh, 044h
    db 024h, 010h, 055h, 057h, 050h, 08Bh, 0CEh
    call ?j_00020671@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 089h, 06Ch, 024h, 010h, 00Fh, 084h, 099h, 001h, 000h, 000h, 08Bh, 045h
    db 000h, 085h, 0C0h, 075h, 026h, 0A1h
    dd ?TheMixFileInfoPool@@3HA
    db 085h, 0C0h, 075h, 005h
    call ?j_0003d1a9@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 051h, 055h, 068h
    dd ?TheMixFileInfoPool@@3HA
    call ?j_00021da0@@YAXXZ
    db 083h, 0C4h, 00Ch, 089h, 045h, 000h, 0EBh, 007h, 0C7h, 040h, 00Ch, 000h, 000h, 000h, 000h, 08Bh
    db 054h, 024h, 07Ch, 08Bh, 044h, 024h, 078h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 052h, 050h
    call ?j_0001c675@@YAXXZ
    db 08Dh, 04Ch, 024h, 024h, 051h, 050h, 08Bh, 0CEh
    call ?j_00047384@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 039h, 001h, 000h, 000h, 03Bh, 0FDh, 074h, 043h, 08Dh, 054h
    db 024h, 030h, 052h, 08Dh, 044h, 024h, 028h, 050h, 08Bh, 0CEh
    call ?j_000171e8@@YAXXZ
    db 08Bh, 007h, 085h, 0C0h, 075h, 025h, 0A1h
    dd ?TheMixFileInfoPool@@3HA
    db 085h, 0C0h, 075h, 005h
    call ?j_0003d1a9@@YAXXZ
    db 08Dh, 04Ch, 024h, 030h, 051h, 057h, 068h
    dd ?TheMixFileInfoPool@@3HA
    call ?j_00021da0@@YAXXZ
    db 083h, 0C4h, 00Ch, 089h, 007h, 0EBh, 007h, 0C7h, 040h, 00Ch, 000h, 000h, 000h, 000h, 08Bh, 04Ch
    db 024h, 078h
    call ?j_00010ea1@@YAXXZ
    db 08Bh, 04Ch, 024h, 078h, 088h, 084h, 024h, 080h, 000h, 000h, 000h
    call ?j_0001fbbd@@YAXXZ
    db 08Bh, 04Ch, 024h, 078h, 048h, 089h, 084h, 024h, 084h, 000h, 000h, 000h
    call ?j_00036b33@@YAXXZ
    db 08Ah, 094h, 024h, 080h, 000h, 000h, 000h, 0F6h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h
    db 048h, 08Bh, 084h, 024h, 084h, 000h, 000h, 000h, 089h, 044h, 024h, 04Ch, 033h, 0C0h, 0C7h, 044h
    db 024h, 044h, 001h, 000h, 000h, 000h, 088h, 054h, 024h, 049h, 066h, 08Bh, 047h, 008h, 08Dh, 04Ch
    db 024h, 044h, 050h, 051h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_0004375c@@YAXXZ
    db 00Fh, 0B7h, 0D0h, 033h, 0C0h, 066h, 08Bh, 045h, 008h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h, 089h
    db 054h, 024h, 078h, 050h, 08Dh, 044h, 024h, 048h, 050h
    call ?j_0004375c@@YAXXZ
    db 00Fh, 0B7h, 0C8h, 039h, 04Ch, 024h, 078h, 074h, 01Ah, 08Bh, 0CDh
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CFh
    call ?j_0004b3b7@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 033h, 0C0h, 05Bh, 083h, 0C4h, 064h, 0C2h, 010h, 000h, 055h, 08Bh, 0CFh
    call ?j_0003e9f5@@YAXXZ
    db 055h, 057h, 08Bh, 0CEh
    call ?j_0003a828@@YAXXZ
    db 08Bh, 017h, 057h, 08Bh, 0CEh, 066h, 089h, 042h, 010h
    call ?j_00024ef1@@YAXXZ
    db 08Bh, 0CEh
    call ?j_0003d3ed@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 089h, 0BCh, 024h, 084h, 000h, 000h, 000h, 075h, 029h, 08Bh, 0CDh, 0C6h
    db 086h, 03Ch, 008h, 000h, 000h, 000h
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00032b5f@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 033h, 0C0h, 05Bh, 083h, 0C4h, 064h, 0C2h, 010h, 000h, 08Bh, 0BCh, 024h, 084h
    db 000h, 000h, 000h, 090h, 03Bh, 0FDh, 00Fh, 084h, 042h, 003h, 000h, 000h, 08Dh, 086h, 038h, 008h
    db 000h, 000h, 050h, 08Bh, 0CFh
    call ?j_00005e48@@YAXXZ
    db 06Ah, 000h, 057h, 08Bh, 0CEh
    call ?j_0001264d@@YAXXZ
    db 08Bh, 007h, 00Fh, 0B7h, 008h, 00Fh, 0B7h, 050h, 004h, 08Bh, 045h, 000h, 089h, 04Ch, 024h, 030h
    db 00Fh, 0B7h, 008h, 089h, 04Ch, 024h, 024h, 08Bh, 04Fh, 00Ch, 089h, 054h, 024h, 034h, 00Fh, 0B7h
    db 050h, 004h, 0C1h, 0E9h, 006h, 08Dh, 044h, 024h, 050h, 050h, 083h, 0E1h, 03Fh, 051h, 089h, 054h
    db 024h, 030h, 08Dh, 054h, 024h, 02Ch, 052h, 08Dh, 044h, 024h, 03Ch, 050h, 08Bh, 0CEh, 089h, 074h
    db 024h, 060h, 0C6h, 044h, 024h, 064h, 000h, 089h, 06Ch, 024h, 068h, 089h, 05Ch, 024h, 06Ch
    call ?j_00035a2b@@YAXXZ
    db 033h, 0C9h, 089h, 04Ch, 024h, 060h, 0C7h, 044h, 024h, 064h, 001h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 068h, 002h, 000h, 000h, 000h, 0C7h, 044h, 024h, 06Ch, 003h, 000h, 000h, 000h, 089h, 04Ch
    db 024h, 070h, 088h, 04Ch, 024h, 014h, 088h, 04Ch, 024h, 015h, 088h, 04Ch, 024h, 016h, 088h, 04Ch
    db 024h, 017h, 088h, 04Ch, 024h, 018h, 088h, 04Ch, 024h, 019h, 088h, 04Ch, 024h, 01Ah, 088h, 04Ch
    db 024h, 01Bh, 089h, 08Ch, 024h, 080h, 000h, 000h, 000h, 0EBh, 011h, 08Bh, 08Ch, 024h, 080h, 000h
    db 000h, 000h, 08Bh, 0BCh, 024h, 084h, 000h, 000h, 000h, 08Dh, 049h, 000h, 08Bh, 007h, 08Bh, 014h
    db 08Dh
    dd g_Va012B4B38
    db 00Fh, 0B7h, 028h, 00Fh, 0B7h, 040h, 004h, 003h, 0EAh, 08Bh, 014h, 08Dh
    dd g_Va012B4B10
    db 0C6h, 044h, 00Ch, 014h, 000h, 08Bh, 04Fh, 00Ch, 003h, 0C2h, 050h, 0C1h, 0E9h, 006h, 083h, 0E1h
    db 03Fh, 055h, 051h, 08Bh, 0CEh, 089h, 06Ch, 024h, 028h, 089h, 044h, 024h, 02Ch
    call ?j_00020671@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 0FEh, 001h, 000h, 000h, 08Bh, 057h, 00Ch, 081h, 0E2h, 0C0h
    db 00Fh, 000h, 000h, 083h, 0FAh, 040h, 00Fh, 085h, 0A4h, 000h, 000h, 000h, 08Bh, 044h, 024h, 020h
    db 050h, 055h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_000114f5@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 08Bh, 000h, 000h, 000h, 088h, 044h, 024h, 078h, 08Bh, 044h, 024h, 020h
    db 083h, 0C0h, 003h, 08Dh, 04Dh, 003h, 050h, 051h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_00043d15@@YAXXZ
    db 084h, 0C0h, 074h, 005h, 0C6h, 044h, 024h, 078h, 001h, 08Bh, 04Ch, 024h, 020h, 083h, 0C1h, 003h
    db 051h, 08Dh, 045h, 0FDh, 050h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_00043d15@@YAXXZ
    db 084h, 0C0h, 074h, 005h, 0C6h, 044h, 024h, 078h, 001h, 08Bh, 044h, 024h, 020h, 083h, 0C0h, 0FDh
    db 050h, 08Dh, 045h, 003h, 050h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_00043d15@@YAXXZ
    db 084h, 0C0h, 074h, 005h, 0C6h, 044h, 024h, 078h, 001h, 08Bh, 044h, 024h, 020h, 083h, 0C0h, 0FDh
    db 050h, 08Dh, 045h, 0FDh, 050h, 08Dh, 08Eh, 09Ch, 00Ch, 000h, 000h
    call ?j_00043d15@@YAXXZ
    db 084h, 0C0h, 075h, 00Ch, 08Ah, 044h, 024h, 078h, 084h, 0C0h, 00Fh, 084h, 048h, 001h, 000h, 000h
    db 08Bh, 017h, 085h, 0D2h, 074h, 01Dh, 08Bh, 042h, 024h, 08Bh, 0C8h, 0C1h, 0E9h, 003h, 0F6h, 0C1h
    db 001h, 00Fh, 085h, 031h, 001h, 000h, 000h, 0C1h, 0E8h, 004h, 083h, 0E0h, 001h, 00Fh, 085h, 025h
    db 001h, 000h, 000h, 03Bh, 07Ch, 024h, 010h, 074h, 071h, 08Bh, 08Ch, 024h, 080h, 000h, 000h, 000h
    db 083h, 0F9h, 004h, 07Ch, 01Ah, 08Bh, 044h, 08Ch, 050h, 080h, 07Ch, 004h, 014h, 000h, 075h, 00Fh
    db 08Bh, 044h, 08Ch, 054h, 080h, 07Ch, 004h, 014h, 000h, 00Fh, 084h, 000h, 001h, 000h, 000h, 08Bh
    db 047h, 00Ch, 0A8h, 007h, 00Fh, 085h, 0F5h, 000h, 000h, 000h, 0C1h, 0E8h, 012h, 0A8h, 001h, 00Fh
    db 085h, 0EAh, 000h, 000h, 000h, 085h, 0D2h, 0C6h, 044h, 00Ch, 014h, 001h, 075h, 025h, 0A1h
    dd ?TheMixFileInfoPool@@3HA
    db 085h, 0C0h, 075h, 005h
    call ?j_0003d1a9@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 051h, 057h, 068h
    dd ?TheMixFileInfoPool@@3HA
    call ?j_00021da0@@YAXXZ
    db 083h, 0C4h, 00Ch, 089h, 007h, 0EBh, 007h, 0C7h, 042h, 00Ch, 000h, 000h, 000h, 000h, 08Bh, 057h
    db 00Ch, 08Bh, 044h, 024h, 020h, 06Ah, 000h, 053h, 0C1h, 0EAh, 006h, 083h, 0E2h, 03Fh, 052h, 050h
    db 055h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00048d29@@YAXXZ
    db 08Bh, 08Ch, 024h, 084h, 000h, 000h, 000h, 051h, 08Bh, 0CFh, 089h, 044h, 024h, 07Ch
    call ?j_000169c3@@YAXXZ
    db 08Bh, 04Ch, 024h, 078h, 03Bh, 0CBh, 08Bh, 0E8h, 07Dh, 032h, 08Bh, 0C3h, 02Bh, 0C1h, 08Dh, 014h
    db 080h, 0D1h, 0E2h, 085h, 0EDh, 089h, 054h, 024h, 078h, 0DBh, 044h, 024h, 078h, 089h, 06Ch, 024h
    db 078h, 0D8h, 00Dh
    dd ?R3FieldSlope1096CF4@@3MA
    db 0DBh, 044h, 024h, 078h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0DEh, 0C1h
    call __ftol2
    db 08Bh, 0E8h, 08Bh, 007h, 083h, 060h, 024h, 0FEh, 08Bh, 044h, 024h, 010h, 050h, 057h, 08Bh, 0CEh
    call ?j_0003a828@@YAXXZ
    db 08Bh, 00Fh, 08Bh, 094h, 024h, 084h, 000h, 000h, 000h, 066h, 089h, 069h, 012h, 052h, 08Bh, 0CFh
    db 089h, 044h, 024h, 07Ch
    call ?j_00040313@@YAXXZ
    db 08Bh, 007h, 066h, 08Bh, 048h, 012h, 066h, 003h, 04Ch, 024h, 078h, 057h, 066h, 089h, 048h, 010h
    db 08Bh, 0CEh
    call ?j_00024ef1@@YAXXZ
    db 08Bh, 08Ch, 024h, 080h, 000h, 000h, 000h, 041h, 083h, 0F9h, 008h, 089h, 08Ch, 024h, 080h, 000h
    db 000h, 000h, 00Fh, 08Ch, 094h, 0FDh, 0FFh, 0FFh, 08Bh, 0CEh
    call ?j_0003d3ed@@YAXXZ
    db 085h, 0C0h, 08Bh, 06Ch, 024h, 010h, 089h, 084h, 024h, 084h, 000h, 000h, 000h, 00Fh, 085h, 0B3h
    db 0FCh, 0FFh, 0FFh, 0E9h, 08Dh, 0FCh, 0FFh, 0FFh, 08Bh, 054h, 024h, 07Ch, 053h, 06Ah, 000h, 055h
    db 052h, 08Bh, 0CEh, 0C6h, 086h, 03Ch, 008h, 000h, 000h, 000h
    call ?j_00020da1@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0D8h
    call ?j_0004b3b7@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00032b5f@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 08Bh, 0C3h, 05Bh, 083h, 0C4h, 064h, 0C2h, 010h, 000h
?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z ENDP
_TEXT$d007f2160 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
