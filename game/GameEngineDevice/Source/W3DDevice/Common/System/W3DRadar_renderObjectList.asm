.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??1W3DRadarResetSurface@@QAE@XZ:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ?DrawPixel@SurfaceClass@@QAEXIII@Z:NEAR
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?Rva006C0890@@YAHHH@Z:NEAR
EXTERN ?TheBfmeGenAE@@3PAVBfmeGenAE@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?d_006c1d00@@YAXXZ:NEAR
EXTERN ?g_Va012F7FD8@@3IA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeLimitEK@@3MB:BYTE
EXTERN ?getSurfaceLevel@W3DRadarResetTexture@@QAE?AVW3DRadarResetSurface@@XZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000dd14@@YAXXZ:NEAR
EXTERN ?j_0001bd88@@YAXXZ:NEAR
EXTERN ?j_0001e52e@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_00024ca8@@YAXXZ:NEAR
EXTERN ?j_0002ae23@@YAXXZ:NEAR
EXTERN ?j_0002b81e@@YAXXZ:NEAR
EXTERN ?j_0002e8d4@@YAXXZ:NEAR
EXTERN ?j_000330dc@@YAXXZ:NEAR
EXTERN ?j_00033a1e@@YAXXZ:NEAR
EXTERN ?j_0003add7@@YAXXZ:NEAR
EXTERN ?j_00047bb3@@YAXXZ:NEAR
EXTERN ?rva006C2A20@@YAXPAVSurfaceClass@@HHHHHPBE@Z:NEAR
EXTERN ?rva006C2DD0@@YAXPAVSurfaceClass@@HHHHHQAY01$$CBE@Z:NEAR
EXTERN ?rva006C42B0@@YA_NPBVObject@@PAH@Z:NEAR
EXTERN __ftol2:NEAR
EXTERN __real@40000000:BYTE
EXTERN g_Va01049FDE:NEAR
EXTERN g_Va01083C50:BYTE
EXTERN g_Va0111D854:BYTE
EXTERN g_Va0111D858:BYTE
EXTERN g_Va012F7F44:BYTE
EXTERN g_Va012F7FD4:BYTE

; ?renderObjectList@W3DRadar@@IAEXPBVRadarObject@@PAVTextureClass@@_N@Z
; Exact 1296 retail bytes @ 0x006C43F0
; Identity: ILT thunk 0x272A5 is called twice by W3DRadar::draw at 0x6C4E0A/0x6C4E17;
; body traverses RadarObject nodes, handles shroud/stealth, and emits legal-point-guarded pixels.
; Queue RVA 0x78D467 was inside unrelated code; true boundary ends at ret 0Ch then 0xCC pad.
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d00ac43f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AC43F0 size 1296
public ?renderObjectList@W3DRadar@@IAEXPBVRadarObject@@PAVTextureClass@@_N@Z
?renderObjectList@W3DRadar@@IAEXPBVRadarObject@@PAVTextureClass@@_N@Z PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01049FDE
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 03Ch, 056h, 057h, 08Bh, 07Ch, 024h, 054h, 085h, 0FFh, 08Bh, 0F1h, 089h, 074h, 024h, 014h, 00Fh
    db 084h, 0D1h, 004h, 000h, 000h, 08Bh, 04Ch, 024h, 058h, 083h, 039h, 000h, 00Fh, 084h, 0C4h, 004h
    db 000h, 000h, 08Dh, 044h, 024h, 00Ch, 050h
    call ?getSurfaceLevel@W3DRadarResetTexture@@QAE?AVW3DRadarResetSurface@@XZ
    db 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 041h, 00Ch, 085h, 0C0h, 0C7h, 044h, 024h, 04Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h
    db 020h, 000h, 000h, 000h, 000h, 074h, 007h, 08Bh, 050h, 024h, 089h, 054h, 024h, 020h, 0D9h, 086h
    db 048h, 014h, 000h, 000h, 053h, 0D8h, 0A6h, 03Ch, 014h, 000h, 000h, 089h, 07Ch, 024h, 01Ch, 055h
    db 0D8h, 03Dh
    dd ?g_bfmeLimitEK@@3MB
    db 0D9h, 05Ch, 024h, 02Ch, 0D9h, 086h, 04Ch, 014h, 000h, 000h, 0D8h, 0A6h, 040h, 014h, 000h, 000h
    db 0D8h, 03Dh
    dd ?g_bfmeLimitEK@@3MB
    db 0D9h, 05Ch, 024h, 034h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 074h, 024h, 020h, 08Bh
    db 0CEh
    call ?j_00033a1e@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 024h, 004h, 000h, 000h, 08Bh, 076h, 004h, 08Bh, 046h, 004h, 085h, 0C0h
    db 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 098h, 0D4h, 000h, 000h, 000h, 08Bh, 044h, 024h, 028h, 0C1h, 0EBh, 017h, 050h, 08Bh, 0CEh
    db 080h, 0E3h, 001h
    call ?j_0002b81e@@YAXXZ
    db 083h, 0F8h, 002h, 00Fh, 09Fh, 0C0h, 084h, 0DBh, 088h, 044h, 024h, 012h, 075h, 03Bh, 084h, 0C0h
    db 00Fh, 085h, 0E0h, 003h, 000h, 000h, 08Bh, 0CEh
    call ?j_0001e52e@@YAXXZ
    db 083h, 0F8h, 004h, 075h, 027h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 079h, 00Ch, 08Bh, 0CEh
    call ?j_00020824@@YAXXZ
    db 03Bh, 0C7h, 074h, 013h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    call ?j_000330dc@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0ADh, 003h, 000h, 000h, 0D9h, 044h, 024h, 02Ch, 0D8h, 04Eh, 038h
    call __ftol2
    db 0D9h, 044h, 024h, 034h, 0D8h, 04Eh, 03Ch, 08Bh, 0F8h
    call __ftol2
    db 08Bh, 0E8h, 08Ah, 044h, 024h, 012h, 084h, 0C0h, 075h, 009h, 08Bh, 054h, 024h, 020h, 08Bh, 042h
    db 00Ch, 0EBh, 042h, 08Bh, 044h, 024h, 01Ch, 08Bh, 088h, 0ACh, 014h, 000h, 000h, 085h, 0C9h, 075h
    db 02Ah, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 041h, 014h, 085h, 0C0h, 00Fh, 084h, 061h, 003h, 000h, 000h, 08Bh, 080h, 0C4h, 001h, 000h
    db 000h, 050h
    call ?j_00024ca8@@YAXXZ
    db 08Bh, 054h, 024h, 020h, 083h, 0C4h, 004h, 089h, 082h, 0ACh, 014h, 000h, 000h, 08Bh, 044h, 024h
    db 01Ch, 08Bh, 080h, 0ACh, 014h, 000h, 000h, 08Bh, 04Ch, 024h, 064h, 051h, 050h
    call ?Rva006C0890@@YAHHH@Z
    db 089h, 044h, 024h, 020h, 08Bh, 046h, 004h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h
    db 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0D0h, 000h, 000h, 000h, 000h, 000h, 000h, 002h, 00Fh, 084h, 0D7h, 000h, 000h, 000h
    db 08Dh, 05Ch, 024h, 018h
    call ?rva006C42B0@@YA_NPBVObject@@PAH@Z
    db 084h, 0C0h, 00Fh, 084h, 0F8h, 002h, 000h, 000h, 08Dh, 054h, 024h, 013h, 052h, 08Dh, 044h, 024h
    db 015h, 050h, 08Bh, 044h, 024h, 020h, 08Dh, 04Ch, 024h, 068h, 051h, 08Dh, 054h, 024h, 068h, 052h
    db 050h
    call ?j_0001bd88@@YAXXZ
    db 08Ah, 044h, 024h, 070h, 00Fh, 0B6h, 0C8h, 0BAh, 0FFh, 000h, 000h, 000h, 02Bh, 0D1h, 08Ah, 04Ch
    db 024h, 074h, 0D1h, 0FAh, 002h, 0C2h, 00Fh, 0B6h, 0D1h, 0BBh, 0FFh, 000h, 000h, 000h, 02Bh, 0DAh
    db 08Ah, 054h, 024h, 025h, 0D1h, 0FBh, 002h, 0CBh, 00Fh, 0B6h, 0F2h, 0BBh, 0FFh, 000h, 000h, 000h
    db 02Bh, 0DEh, 08Bh, 074h, 024h, 030h, 0D1h, 0FBh, 002h, 0D3h, 033h, 0DBh, 08Ah, 07Ch, 024h, 027h
    db 088h, 044h, 024h, 070h, 088h, 04Ch, 024h, 074h, 068h
    dd g_Va0111D858
    db 088h, 054h, 024h, 029h, 08Ah, 0D8h, 00Fh, 0B6h, 0C1h, 00Fh, 0B6h, 0CAh, 08Bh, 054h, 024h, 030h
    db 052h, 08Bh, 096h, 0A4h, 014h, 000h, 000h, 0C1h, 0E3h, 008h, 00Bh, 0D8h, 08Bh, 086h, 0A8h, 014h
    db 000h, 000h, 055h, 0C1h, 0E3h, 008h, 057h, 00Bh, 0D9h, 050h, 08Dh, 04Ch, 024h, 03Ch, 051h
    call ?rva006C2A20@@YAXPAVSurfaceClass@@HHHHHPBE@Z
    db 08Bh, 096h, 0A8h, 014h, 000h, 000h, 08Bh, 08Eh, 0A4h, 014h, 000h, 000h, 068h
    dd g_Va0111D854
    db 053h, 055h, 057h, 052h, 08Dh, 044h, 024h, 054h, 050h
    call ?rva006C2DD0@@YAXPAVSurfaceClass@@HHHHHQAY01$$CBE@Z
    db 083h, 0C4h, 044h, 0E9h, 032h, 002h, 000h, 000h, 084h, 0DBh, 00Fh, 084h, 0AEh, 001h, 000h, 000h
    db 0F6h, 005h
    dd ?g_Va012F7FD8@@3IA
    db 001h, 075h, 026h, 083h, 00Dh
    dd ?g_Va012F7FD8@@3IA
    db 001h, 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 068h
    dd g_Va01083C50
    db 0C6h, 044h, 024h, 058h, 001h
    call ?j_0003add7@@YAXXZ
    db 0A3h
    dd g_Va012F7FD4
    db 0C6h, 044h, 024h, 054h, 000h, 08Bh, 00Dh
    dd g_Va012F7FD4
    db 051h, 08Bh, 0CEh
    call ?j_0002ae23@@YAXXZ
    db 08Bh, 0D8h, 085h, 0DBh, 00Fh, 084h, 0E3h, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_00020824@@YAXXZ
    db 050h, 08Bh, 0CBh
    call ?j_0002e8d4@@YAXXZ
    db 0D8h, 04Ch, 024h, 02Ch, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D8h, 005h
    dd __real@40000000
    call __ftol2
    db 050h, 055h, 057h, 08Dh, 04Ch, 024h, 044h
    call ?j_0000dd14@@YAXXZ
    db 08Bh, 044h, 024h, 03Ch, 08Bh, 054h, 024h, 018h, 08Dh, 05Ch, 02Dh, 000h, 08Bh, 06Ch, 024h, 038h
    db 03Bh, 0E8h, 08Bh, 0FDh, 0C6h, 044h, 024h, 054h, 002h, 089h, 015h
    dd g_Va012F7F44
    db 089h, 05Ch, 024h, 030h, 089h, 07Ch, 024h, 024h, 074h, 04Fh, 08Dh, 049h, 000h, 08Bh, 075h, 000h
    db 08Bh, 07Dh, 008h, 08Bh, 045h, 004h, 08Dh, 05Ch, 024h, 014h
    call ?d_006c1d00@@YAXXZ
    db 08Bh, 04Dh, 000h, 08Bh, 074h, 024h, 030h, 08Bh, 07Dh, 008h, 08Bh, 045h, 004h, 02Bh, 0F1h
    call ?d_006c1d00@@YAXXZ
    db 08Bh, 044h, 024h, 024h, 08Bh, 008h, 03Bh, 04Dh, 000h, 07Dh, 004h, 089h, 06Ch, 024h, 024h, 08Bh
    db 044h, 024h, 03Ch, 083h, 0C5h, 00Ch, 03Bh, 0E8h, 075h, 0C0h, 08Bh, 06Ch, 024h, 038h, 08Bh, 07Ch
    db 024h, 024h, 08Bh, 05Ch, 024h, 030h, 08Bh, 077h, 004h, 08Bh, 047h, 008h, 046h, 03Bh, 0F0h, 07Dh
    db 06Ah, 085h, 0F6h, 08Bh, 007h, 07Ch, 027h, 085h, 0C0h, 07Ch, 023h, 081h, 0FEh, 080h, 000h, 000h
    db 000h, 07Dh, 01Bh, 03Dh, 080h, 000h, 000h, 000h, 07Dh, 014h, 08Bh, 054h, 024h, 018h, 052h, 050h
    db 056h, 08Dh, 04Ch, 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 08Bh, 06Ch, 024h, 038h, 08Bh, 00Fh, 08Bh, 0C3h, 02Bh, 0C1h, 085h, 0F6h, 07Ch, 02Bh, 085h, 0C0h
    db 07Ch, 027h, 081h, 0FEh, 080h, 000h, 000h, 000h, 07Dh, 01Fh, 03Dh, 080h, 000h, 000h, 000h, 07Dh
    db 018h, 08Bh, 044h, 024h, 018h, 050h, 08Bh, 0D3h, 02Bh, 0D1h, 052h, 056h, 08Dh, 04Ch, 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 08Bh, 06Ch, 024h, 038h, 08Bh, 047h, 008h, 046h, 03Bh, 0F0h, 07Ch, 096h, 085h, 0EDh, 0C6h, 044h
    db 024h, 054h, 000h, 00Fh, 084h, 0B9h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 040h, 02Bh, 0CDh, 0B8h
    db 0ABh, 0AAh, 0AAh, 02Ah, 0F7h, 0E9h, 0D1h, 0FAh, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 08Dh
    db 004h, 040h, 0C1h, 0E0h, 002h, 03Dh, 080h, 000h, 000h, 000h, 076h, 00Eh, 055h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0E9h, 088h, 000h, 000h, 000h, 050h, 055h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 0EBh, 07Ch, 08Dh, 05Ch, 024h, 018h
    call ?rva006C42B0@@YA_NPBVObject@@PAH@Z
    db 084h, 0C0h, 074h, 06Fh, 055h, 057h
    call ?j_00047bb3@@YAXXZ
    db 08Bh, 074h, 024h, 020h, 083h, 0C4h, 008h, 084h, 0C0h, 074h, 00Ch, 056h, 055h, 057h, 08Dh, 04Ch
    db 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 04Fh, 055h, 057h
    call ?j_00047bb3@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 074h, 00Ch, 056h, 055h, 057h, 08Dh, 04Ch, 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 04Dh, 055h, 057h
    call ?j_00047bb3@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 074h, 00Ch, 056h, 055h, 057h, 08Dh, 04Ch, 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 047h, 055h, 057h
    call ?j_00047bb3@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 074h, 00Ch, 056h, 055h, 057h, 08Dh, 04Ch, 024h, 020h
    call ?DrawPixel@SurfaceClass@@QAEXIII@Z
    db 08Bh, 044h, 024h, 020h, 08Bh, 040h, 008h, 085h, 0C0h, 089h, 044h, 024h, 020h, 00Fh, 085h, 0B6h
    db 0FBh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 054h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1W3DRadarResetSurface@@QAE@XZ
    db 05Dh, 05Bh, 08Bh, 04Ch, 024h, 044h, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 048h, 0C2h, 00Ch, 000h
?renderObjectList@W3DRadar@@IAEXPBVRadarObject@@PAVTextureClass@@_N@Z ENDP
_TEXT$d00ac43f0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
