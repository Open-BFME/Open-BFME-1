.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_7?$LatchRestore@_N@@6B@:BYTE
EXTERN ??_7W3DRenderObjectSnapshot@@6B@:BYTE
EXTERN ?ClientAt012F1464@@3PAVClient0009A580@@A:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Create_Render_Obj@@YAPAVRenderObjClass@@PBDMH@Z:NEAR
EXTERN ?EngineGlobal007629F0@@3PAUEngine007629F0@@A:BYTE
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012F8058@@3PAVRva00712F60@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?g_Va012F779C@@3IA:BYTE
EXTERN ?g_guardTargetTypeThrowInfo@@3HA:BYTE
EXTERN ?j_00001005@@YAXXZ:NEAR
EXTERN ?j_00001eb5@@YAXXZ:NEAR
EXTERN ?j_00002f13@@YAXXZ:NEAR
EXTERN ?j_00003071@@YAXXZ:NEAR
EXTERN ?j_00007ce3@@YAXXZ:NEAR
EXTERN ?j_00008a99@@YAXXZ:NEAR
EXTERN ?j_00008ca1@@YAXXZ:NEAR
EXTERN ?j_0000914c@@YAXXZ:NEAR
EXTERN ?j_00009b01@@YAXXZ:NEAR
EXTERN ?j_0000bd75@@YAXXZ:NEAR
EXTERN ?j_0000c30b@@YAXXZ:NEAR
EXTERN ?j_0000c9b4@@YAXXZ:NEAR
EXTERN ?j_0000d33c@@YAXXZ:NEAR
EXTERN ?j_0000f9e8@@YAXXZ:NEAR
EXTERN ?j_0000fe93@@YAXXZ:NEAR
EXTERN ?j_0001079e@@YAXXZ:NEAR
EXTERN ?j_00015a69@@YAXXZ:NEAR
EXTERN ?j_00017f85@@YAXXZ:NEAR
EXTERN ?j_00019dad@@YAXXZ:NEAR
EXTERN ?j_0001ae2e@@YAXXZ:NEAR
EXTERN ?j_0001e961@@YAXXZ:NEAR
EXTERN ?j_00022c96@@YAXXZ:NEAR
EXTERN ?j_00023321@@YAXXZ:NEAR
EXTERN ?j_00023a38@@YAXXZ:NEAR
EXTERN ?j_00029695@@YAXXZ:NEAR
EXTERN ?j_000298e8@@YAXXZ:NEAR
EXTERN ?j_0002c5cf@@YAXXZ:NEAR
EXTERN ?j_0002e6ae@@YAXXZ:NEAR
EXTERN ?j_0002f1d5@@YAXXZ:NEAR
EXTERN ?j_0002f68f@@YAXXZ:NEAR
EXTERN ?j_00030576@@YAXXZ:NEAR
EXTERN ?j_000317aa@@YAXXZ:NEAR
EXTERN ?j_0003834d@@YAXXZ:NEAR
EXTERN ?j_0003bead@@YAXXZ:NEAR
EXTERN ?j_0003c1cd@@YAXXZ:NEAR
EXTERN ?j_0003d7d0@@YAXXZ:NEAR
EXTERN ?j_0003e63a@@YAXXZ:NEAR
EXTERN ?j_000405e8@@YAXXZ:NEAR
EXTERN ?j_00041006@@YAXXZ:NEAR
EXTERN ?j_00044661@@YAXXZ:NEAR
EXTERN ?j_00044be3@@YAXXZ:NEAR
EXTERN ?j_00044e27@@YAXXZ:NEAR
EXTERN ?j_00047cee@@YAXXZ:NEAR
EXTERN ?j_00048c84@@YAXXZ:NEAR
EXTERN ?j_0004ac82@@YAXXZ:NEAR
EXTERN ?ji_009f6d00@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXPBDH@Z:NEAR
EXTERN __imp__ReleaseMutex@4:BYTE
EXTERN __imp__Sleep@4:BYTE
EXTERN __imp__WaitForSingleObject@8:BYTE
EXTERN __imp___time64:BYTE
EXTERN _bfmeFormatText:NEAR
EXTERN g_Va01049320:NEAR
EXTERN g_Va0104934E:NEAR
EXTERN g_Va0104972B:NEAR
EXTERN g_Va0111BB9C:BYTE
EXTERN g_Va012F7798:BYTE
EXTERN g_Va012F77A0:BYTE
EXTERN g_Va01359054:BYTE
_TEXT SEGMENT

; ghidra: FUN_00ab9500  retail @ 0x006B9500 size 1071
_TEXT ENDS
_TEXT$d00ab9500 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB9500 size 1071
public ?d_006b9500@@YAXXZ
?d_006b9500@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01049320
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 01Ch, 053h, 055h, 056h, 057h, 08Bh, 0D9h, 08Bh, 0ABh, 05Ch, 009h, 000h, 000h, 06Ah, 0FFh, 055h
    db 0C6h, 044h, 024h, 020h, 000h, 089h, 06Ch, 024h, 01Ch, 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 074h, 005h, 0C6h, 044h, 024h, 018h, 001h, 08Bh, 074h, 024h, 03Ch
    db 08Bh, 046h, 014h, 085h, 0C0h, 08Dh, 04Eh, 014h, 0C7h, 044h, 024h, 034h, 000h, 000h, 000h, 000h
    db 00Fh, 084h, 0AAh, 003h, 000h, 000h, 066h, 083h, 078h, 004h, 000h, 00Fh, 084h, 09Fh, 003h, 000h
    db 000h, 068h
    dd g_Va0111BB9C
    call ?j_000405e8@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 08Dh, 003h, 000h, 000h, 08Bh, 04Eh, 008h, 085h, 0C9h, 075h, 038h, 08Bh
    db 003h, 056h, 08Bh, 0CBh, 0FFh, 090h, 0ACh, 000h, 000h, 000h, 08Bh, 04Eh, 008h, 085h, 0C9h, 075h
    db 026h, 08Ah, 044h, 024h, 018h, 084h, 0C0h, 074h, 007h, 055h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 033h, 0C0h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh
    db 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Bh, 011h, 08Bh, 07Eh, 028h, 0FFh, 052h, 004h, 08Dh
    db 00Ch, 07Fh, 08Bh, 0BCh, 08Bh, 098h, 009h, 000h, 000h, 08Dh, 08Ch, 08Bh, 098h, 009h, 000h, 000h
    db 050h
    call ?j_00003071@@YAXXZ
    db 033h, 0D2h, 03Bh, 0C7h, 00Fh, 095h, 0C2h, 085h, 0D2h, 00Fh, 087h, 020h, 003h, 000h, 000h, 08Bh
    db 046h, 008h, 08Bh, 080h, 084h, 000h, 000h, 000h, 083h, 0F8h, 003h, 075h, 02Ah, 056h, 08Bh, 0CBh
    call ?j_00023321@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 08Bh, 0F0h
    call ?j_0001e961@@YAXXZ
    db 08Bh, 0C6h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh
    db 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Bh, 03Bh, 08Bh, 0CEh
    call ?j_00015a69@@YAXXZ
    db 050h, 08Bh, 0CBh, 0FFh, 097h, 0B8h, 000h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 0C3h, 002h, 000h
    db 000h, 08Bh, 046h, 008h, 083h, 0B8h, 084h, 000h, 000h, 000h, 001h, 075h, 016h, 08Bh, 04Eh, 028h
    db 0B8h, 001h, 000h, 000h, 000h, 0D3h, 0E0h, 085h, 083h, 024h, 006h, 000h, 000h, 00Fh, 085h, 0A1h
    db 002h, 000h, 000h, 056h, 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CBh
    call ?j_00041006@@YAXXZ
    db 08Bh, 06Ch, 024h, 040h, 083h, 0FDh, 001h, 0C6h, 044h, 024h, 034h, 001h, 00Fh, 085h, 0B3h, 000h
    db 000h, 000h, 08Bh, 07Ch, 024h, 010h, 08Bh, 04Fh, 008h
    call ?j_00001005@@YAXXZ
    db 084h, 0C0h, 075h, 030h, 08Dh, 04Ch, 024h, 010h, 088h, 044h, 024h, 034h
    call ?j_00008a99@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0001e961@@YAXXZ
    db 0B8h, 004h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Bh, 047h, 060h, 085h, 0C0h, 075h
    db 00Bh, 08Bh, 0CFh
    call ?j_0001079e@@YAXXZ
    db 08Bh, 07Ch, 024h, 010h, 08Bh, 07Fh, 00Ch, 08Bh, 054h, 024h, 048h, 08Dh, 044h, 024h, 01Ch, 050h
    db 08Dh, 04Ch, 024h, 028h, 051h, 08Dh, 08Bh, 0F4h, 00Ah, 000h, 000h, 089h, 054h, 024h, 024h, 089h
    db 07Ch, 024h, 028h
    call ?j_000317aa@@YAXXZ
    db 08Ah, 044h, 024h, 028h, 084h, 0C0h, 075h, 035h, 08Bh, 054h, 024h, 024h, 08Bh, 072h, 014h, 08Dh
    db 04Ch, 024h, 010h, 0C6h, 044h, 024h, 034h, 000h
    call ?j_00008a99@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0001e961@@YAXXZ
    db 08Bh, 0C6h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh
    db 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Bh, 044h, 024h, 010h, 050h, 08Bh, 0CBh
    call ?j_00001eb5@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 08Ah, 041h, 043h, 084h, 0C0h, 075h, 040h, 051h, 08Bh, 0CBh
    call ?j_00029695@@YAXXZ
    db 084h, 0C0h, 075h, 030h, 08Dh, 04Ch, 024h, 010h, 088h, 044h, 024h, 034h
    call ?j_00008a99@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0001e961@@YAXXZ
    db 0B8h, 003h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 041h
    db 008h, 0F6h, 040h, 03Ch, 020h, 074h, 007h, 06Ah, 001h
    call ?j_0002c5cf@@YAXXZ
    db 08Bh, 076h, 008h, 08Bh, 086h, 084h, 000h, 000h, 000h, 085h, 0C0h, 08Bh, 074h, 024h, 044h, 075h
    db 00Fh, 055h, 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CBh
    call ?j_00044e27@@YAXXZ
    db 0EBh, 00Eh, 056h, 055h, 08Dh, 054h, 024h, 018h, 052h, 08Bh, 0CBh
    call ?j_0003bead@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 024h, 001h, 000h, 000h, 085h, 0F6h, 08Bh, 054h, 024h, 010h, 08Bh, 042h
    db 00Ch, 089h, 044h, 024h, 048h, 00Fh, 085h, 0E1h, 000h, 000h, 000h, 08Dh, 06Bh, 04Ch, 090h, 08Bh
    db 075h, 000h, 08Bh, 00Eh, 03Bh, 0F1h, 00Fh, 084h, 0D0h, 000h, 000h, 000h, 08Bh, 046h, 004h, 08Bh
    db 078h, 008h, 083h, 03Fh, 000h, 075h, 005h, 039h, 057h, 004h, 074h, 004h, 08Bh, 0F0h, 0EBh, 0E4h
    db 08Bh, 046h, 004h, 08Bh, 048h, 008h, 08Bh, 051h, 00Ch, 085h, 0D2h, 0C6h, 044h, 024h, 03Ch, 001h
    db 074h, 05Eh, 08Bh, 0D1h, 083h, 0C2h, 00Ch, 052h, 08Dh, 04Ch, 024h, 044h
    call ?j_0003834d@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0003e63a@@YAXXZ
    db 08Bh, 035h
    dd __imp__Sleep@4
    db 08Bh, 044h, 024h, 040h, 085h, 0C0h, 074h, 014h, 08Ah, 048h, 041h, 084h, 0C9h, 075h, 00Dh, 08Ah
    db 048h, 042h, 084h, 0C9h, 075h, 006h, 06Ah, 001h, 0FFh, 0D6h, 0EBh, 0E4h, 08Bh, 083h, 05Ch, 009h
    db 000h, 000h, 06Ah, 0FFh, 050h, 08Dh, 04Ch, 024h, 01Ch
    call ?j_0000f9e8@@YAXXZ
    db 08Dh, 04Ch, 024h, 040h
    call ?j_000298e8@@YAXXZ
    db 08Bh, 054h, 024h, 010h, 0E9h, 06Fh, 0FFh, 0FFh, 0FFh, 08Bh, 046h, 004h, 08Bh, 050h, 008h, 06Ah
    db 000h, 08Dh, 04Ch, 024h, 040h, 051h, 052h, 08Bh, 0CBh
    call ?j_0000bd75@@YAXXZ
    db 08Ah, 044h, 024h, 03Ch, 084h, 0C0h, 074h, 02Fh, 08Bh, 076h, 004h, 08Bh, 07Eh, 008h, 051h, 08Bh
    db 0C4h, 089h, 030h, 08Dh, 044h, 024h, 040h, 089h, 064h, 024h, 040h, 050h, 08Bh, 0CDh
    call ?j_00007ce3@@YAXXZ
    db 085h, 0FFh, 074h, 010h, 08Bh, 0CFh
    call ?j_0001ae2e@@YAXXZ
    db 057h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 034h, 000h
    call ?j_00008a99@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0001e961@@YAXXZ
    db 08Bh, 044h, 024h, 048h, 08Bh, 04Ch, 024h, 02Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h, 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h
    db 034h, 000h
    call ?j_00008a99@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_0001e961@@YAXXZ
    db 0EBh, 00Fh, 08Ah, 044h, 024h, 018h, 084h, 0C0h, 074h, 007h, 055h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 08Bh, 04Ch, 024h, 02Ch, 05Fh, 05Eh, 05Dh, 0B8h, 001h, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 05Bh, 083h, 0C4h, 028h, 0C2h, 010h, 000h
?d_006b9500@@YAXXZ ENDP
_TEXT$d00ab9500 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab9a60  retail @ 0x006B9A60 size 19
public ?d_006b9a60@@YAXXZ
?d_006b9a60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 6Ah, 01h, 6Ah, 00h, 6Ah, 00h, 50h, 0E8h, 98h, 70h, 96h, 0FFh
    db 0C2h, 04h, 00h
?d_006b9a60@@YAXXZ ENDP

; ghidra: FUN_00ab9aa0  retail @ 0x006B9AA0 size 391
_TEXT ENDS
_TEXT$d00ab9aa0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB9AA0 size 391
public ?d_006b9aa0@@YAXXZ
?d_006b9aa0@@YAXXZ PROC
    db 083h, 0ECh, 010h, 053h, 08Bh, 0D9h, 08Bh, 043h, 04Ch, 056h, 08Bh, 030h, 03Bh, 0F0h, 057h, 089h
    db 05Ch, 024h, 010h, 074h, 069h, 08Bh, 07Eh, 008h, 085h, 0FFh, 075h, 019h, 08Bh, 03Eh, 08Bh, 046h
    db 004h, 06Ah, 00Ch, 089h, 038h, 056h, 089h, 047h, 004h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Bh, 0F7h, 0EBh, 044h, 06Ah, 001h, 08Dh, 044h, 024h, 013h, 050h, 057h, 08Bh
    db 0CBh, 0C6h, 044h, 024h, 01Bh, 001h
    call ?j_0000bd75@@YAXXZ
    db 08Ah, 044h, 024h, 00Fh, 084h, 0C0h, 074h, 026h, 08Bh, 0CFh
    call ?j_0001ae2e@@YAXXZ
    db 057h
    call ??3@YAXPAX@Z
    db 08Bh, 03Eh, 08Bh, 046h, 004h, 06Ah, 00Ch, 089h, 038h, 056h, 089h, 047h, 004h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 00Ch, 08Bh, 0F7h, 0EBh, 002h, 08Bh, 036h, 03Bh, 073h, 04Ch, 075h, 097h, 08Dh, 054h
    db 024h, 014h, 08Dh, 04Bh, 050h, 052h
    call ?j_0000fe93@@YAXXZ
    db 08Bh, 07Ch, 024h, 014h, 085h, 0FFh, 08Bh, 074h, 024h, 018h, 00Fh, 084h, 0E5h, 000h, 000h, 000h
    db 055h, 08Dh, 064h, 024h, 000h, 08Bh, 06Fh, 004h, 085h, 0EDh, 0C6h, 044h, 024h, 013h, 001h, 074h
    db 017h, 06Ah, 001h, 08Dh, 044h, 024h, 017h, 050h, 055h, 08Bh, 0CBh
    call ?j_0000bd75@@YAXXZ
    db 08Ah, 044h, 024h, 013h, 084h, 0C0h, 074h, 071h, 08Bh, 007h, 085h, 0C0h, 08Bh, 0CFh, 074h, 004h
    db 08Bh, 0F8h, 0EBh, 03Ah, 08Bh, 07Fh, 004h, 085h, 0FFh, 075h, 004h, 033h, 0C0h, 0EBh, 003h, 08Bh
    db 047h, 008h, 08Bh, 05Eh, 004h, 08Bh, 07Eh, 008h, 02Bh, 0FBh, 0C1h, 0FFh, 002h, 033h, 0D2h, 0F7h
    db 0F7h, 08Bh, 046h, 008h, 02Bh, 0C3h, 0C1h, 0F8h, 002h, 033h, 0FFh, 042h, 03Bh, 0D0h, 073h, 00Ah
    db 08Bh, 07Eh, 004h, 08Bh, 03Ch, 097h, 085h, 0FFh, 074h, 0F1h, 08Bh, 05Ch, 024h, 014h, 089h, 04Ch
    db 024h, 018h, 08Dh, 04Ch, 024h, 018h, 051h, 08Dh, 04Bh, 050h, 089h, 074h, 024h, 020h
    call ?j_00023a38@@YAXXZ
    db 085h, 0EDh, 074h, 055h, 08Bh, 0CDh
    call ?j_0001ae2e@@YAXXZ
    db 055h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0EBh, 043h, 08Bh, 007h, 085h, 0C0h, 074h, 004h, 08Bh, 0F8h, 0EBh, 039h, 08Bh
    db 07Fh, 004h, 085h, 0FFh, 075h, 004h, 033h, 0C0h, 0EBh, 003h, 08Bh, 047h, 008h, 08Bh, 056h, 004h
    db 08Bh, 04Eh, 008h, 08Bh, 07Eh, 004h, 02Bh, 0CAh, 0C1h, 0F9h, 002h, 033h, 0D2h, 0F7h, 0F1h, 08Bh
    db 046h, 008h, 02Bh, 0C7h, 0C1h, 0F8h, 002h, 033h, 0FFh, 042h, 03Bh, 0D0h, 073h, 00Ah, 08Bh, 04Eh
    db 004h, 08Bh, 03Ch, 091h, 085h, 0FFh, 074h, 0F1h, 085h, 0FFh, 00Fh, 085h, 021h, 0FFh, 0FFh, 0FFh
    db 05Dh, 05Fh, 05Eh, 05Bh, 083h, 0C4h, 010h, 0C3h
?d_006b9aa0@@YAXXZ ENDP
_TEXT$d00ab9aa0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab9c90  retail @ 0x006B9C90 size 588
_TEXT ENDS
_TEXT$d00ab9c90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB9C90 size 588
public ?d_006b9c90@@YAXXZ
?d_006b9c90@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0104934E
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 018h, 053h, 056h, 057h, 08Bh, 0F1h, 08Bh, 0BEh, 05Ch, 009h, 000h, 000h, 06Ah, 0FFh, 033h, 0DBh
    db 057h, 089h, 07Ch, 024h, 014h, 088h, 05Ch, 024h, 01Ch, 089h, 07Ch, 024h, 018h, 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 074h, 005h, 0C6h, 044h, 024h, 014h, 001h, 038h, 01Dh
    dd g_Va012F77A0
    db 089h, 05Ch, 024h, 02Ch, 074h, 010h, 038h, 05Ch, 024h, 014h, 00Fh, 084h, 0DEh, 001h, 000h, 000h
    db 057h, 0E9h, 0D2h, 001h, 000h, 000h, 0C7h, 044h, 024h, 018h
    dd ??_7?$LatchRestore@_N@@6B@
    db 0C7h, 044h, 024h, 020h
    dd g_Va012F77A0
    db 088h, 05Ch, 024h, 01Ch, 0C6h, 005h
    dd g_Va012F77A0
    db 001h, 08Bh, 046h, 00Ch, 039h, 058h, 070h, 0C6h, 044h, 024h, 02Ch, 001h, 07Eh, 064h, 053h, 0FFh
    db 015h
    dd __imp___time64
    db 08Bh, 0CAh, 08Bh, 096h, 068h, 00Bh, 000h, 000h, 08Bh, 0F8h, 08Bh, 086h, 06Ch, 00Bh, 000h, 000h
    db 083h, 0C4h, 004h, 02Bh, 0FAh, 08Bh, 056h, 00Ch, 01Bh, 0C8h, 08Bh, 042h, 070h, 099h, 03Bh, 0CAh
    db 07Ch, 03Bh, 07Fh, 004h, 03Bh, 0F8h, 076h, 035h, 0F6h, 005h
    dd ?g_Va012F779C@@3IA
    db 001h, 075h, 01Dh, 083h, 00Dh
    dd ?g_Va012F779C@@3IA
    db 001h, 08Bh, 0CEh, 0C6h, 044h, 024h, 02Ch, 002h
    call ?j_0002f1d5@@YAXXZ
    db 0A2h
    dd g_Va012F7798
    db 0C6h, 044h, 024h, 02Ch, 001h, 038h, 01Dh
    dd g_Va012F7798
    db 074h, 007h, 08Bh, 0CEh
    call ?j_00044661@@YAXXZ
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 08Ch, 001h, 000h, 000h, 0D9h, 05Eh, 044h, 038h, 09Eh, 036h
    db 006h, 000h, 000h, 075h, 01Dh, 08Bh, 08Eh, 0DCh, 00Ah, 000h, 000h, 03Bh, 08Eh, 0E0h, 00Ah, 000h
    db 000h, 074h, 016h, 0A1h
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 03Bh, 0C3h, 074h, 00Dh, 083h, 078h, 030h, 001h, 075h, 007h, 0C6h, 086h, 035h, 006h, 000h, 000h
    db 001h, 08Bh, 0CEh, 088h, 05Ch, 024h, 02Ch, 088h, 01Dh
    dd g_Va012F77A0
    call ?j_0000c30b@@YAXXZ
    db 08Bh, 056h, 044h, 052h, 08Dh, 08Eh, 040h, 004h, 000h, 000h
    call ?j_0002f68f@@YAXXZ
    db 083h, 0BEh, 004h, 006h, 000h, 000h, 002h, 074h, 02Fh, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 03Bh, 0CBh, 074h, 025h
    call ?j_00022c96@@YAXXZ
    db 084h, 0C0h, 075h, 01Ch, 08Bh, 08Eh, 004h, 006h, 000h, 000h, 08Bh, 046h, 044h, 069h, 0C9h, 0C4h
    db 001h, 000h, 000h, 050h, 08Dh, 08Ch, 031h, 0B8h, 000h, 000h, 000h
    call ?j_0002f68f@@YAXXZ
    db 055h, 08Bh, 0CEh
    call ?j_00048c84@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00002f13@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00019dad@@YAXXZ
    db 08Bh, 0CEh
    call ?j_0002e6ae@@YAXXZ
    db 08Dh, 054h, 024h, 01Ch, 052h, 08Bh, 0CEh
    call ?j_0004ac82@@YAXXZ
    db 08Dh, 044h, 024h, 01Ch, 050h, 08Bh, 0CEh
    call ?j_00044be3@@YAXXZ
    db 08Bh, 0CEh
    call ?j_0003d7d0@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00017f85@@YAXXZ
    db 088h, 09Eh, 031h, 006h, 000h, 000h, 088h, 09Eh, 034h, 006h, 000h, 000h, 088h, 09Eh, 035h, 006h
    db 000h, 000h, 088h, 09Eh, 036h, 006h, 000h, 000h, 08Dh, 0BEh, 0B8h, 000h, 000h, 000h, 0BDh, 003h
    db 000h, 000h, 000h, 08Bh, 0CFh
    call ?j_00047cee@@YAXXZ
    db 081h, 0C7h, 0C4h, 001h, 000h, 000h, 04Dh, 075h, 0F0h, 08Bh, 0BEh, 058h, 00Bh, 000h, 000h, 03Bh
    db 0FBh, 074h, 029h, 083h, 07Fh, 014h, 001h, 075h, 023h, 08Bh, 04Fh, 00Ch, 02Bh, 04Fh, 008h, 0C1h
    db 0F9h, 003h, 085h, 0C9h, 077h, 016h, 08Bh, 0CFh
    call ?j_0000d33c@@YAXXZ
    db 057h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 089h, 09Eh, 058h, 00Bh, 000h, 000h, 038h, 05Ch, 024h, 018h, 05Dh, 074h, 00Bh
    db 08Bh, 054h, 024h, 00Ch, 052h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 08Bh, 04Ch, 024h, 024h, 05Fh, 05Eh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 024h, 0C3h
?d_006b9c90@@YAXXZ ENDP
_TEXT$d00ab9c90 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab9f70  retail @ 0x006B9F70 size 153
public ?d_006b9f70@@YAXXZ
?d_006b9f70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 83h, 93h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 33h, 0DBh, 89h, 5Eh, 04h, 89h
    db 74h, 24h, 08h, 0B8h, 01h, 00h, 00h, 00h, 0C7h, 06h, 0C4h, 0C8h, 11h, 01h, 0C7h, 46h
    db 0Ch, 04h, 00h, 00h, 00h, 89h, 46h, 10h, 89h, 5Ch, 24h, 14h, 89h, 5Eh, 14h, 8Dh
    db 4Eh, 18h, 88h, 44h, 24h, 14h, 0E8h, 33h, 96h, 94h, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 89h
    db 5Eh, 1Ch, 89h, 5Eh, 20h, 89h, 5Eh, 24h, 89h, 5Eh, 28h, 88h, 5Eh, 34h, 88h, 5Eh
    db 35h, 88h, 5Eh, 36h, 88h, 5Eh, 37h, 88h, 5Eh, 38h, 88h, 5Eh, 39h, 88h, 5Eh, 3Ah
    db 88h, 5Eh, 3Bh, 88h, 5Eh, 3Ch, 88h, 5Eh, 3Dh, 88h, 5Eh, 3Eh, 0C7h, 46h, 2Ch, 00h
    db 00h, 80h, 3Fh, 0C7h, 46h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006b9f70@@YAXXZ ENDP

; ghidra: FUN_00aba030  retail @ 0x006BA030 size 137
public ?d_006ba030@@YAXXZ
?d_006ba030@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BEh, 93h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0C4h
    db 0C8h, 11h, 01h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 02h
    db 00h, 00h, 00h, 74h, 06h, 56h, 0E8h, 37h, 67h, 96h, 0FFh, 8Dh, 4Eh, 18h, 0C6h, 44h
    db 24h, 10h, 01h, 0E8h, 3Eh, 0B1h, 97h, 0FFh, 8Bh, 46h, 14h, 85h, 0C0h, 0C6h, 44h, 24h
    db 10h, 00h, 74h, 1Fh, 57h, 8Dh, 78h, 70h, 8Dh, 47h, 04h, 50h, 0FFh, 15h, 54h, 8Eh
    db 35h, 01h, 85h, 0C0h, 7Fh, 0Ch, 85h, 0FFh, 74h, 08h, 8Bh, 17h, 6Ah, 01h, 8Bh, 0CFh
    db 0FFh, 12h, 5Fh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 0ACh, 17h, 08h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006ba030@@YAXXZ ENDP

; ghidra: FUN_00aba120  retail @ 0x006BA120 size 9
public ?d_006ba120@@YAXXZ
?d_006ba120@@YAXXZ PROC
    db 0C6h, 41h, 41h, 00h, 0C6h, 41h, 42h, 01h, 0C3h
?d_006ba120@@YAXXZ ENDP

; ghidra: FUN_00aba130  retail @ 0x006BA130 size 15
public ?d_006ba130@@YAXXZ
?d_006ba130@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 3Bh, 41h, 3Ch, 7Eh, 03h, 89h, 41h, 3Ch, 0C2h, 04h, 00h
?d_006ba130@@YAXXZ ENDP

; ghidra: FUN_00aba1d0  retail @ 0x006BA1D0 size 53
public ?d_006ba1d0@@YAXXZ
?d_006ba1d0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 78h, 48h, 6Ah, 0FFh, 57h, 32h, 0DBh
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 02h, 0B3h, 01h, 8Bh
    db 4Eh, 34h, 41h, 84h, 0DBh, 89h, 4Eh, 34h, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h
    db 01h, 5Fh, 5Eh, 5Bh, 0C3h
?d_006ba1d0@@YAXXZ ENDP

; ghidra: FUN_00aba220  retail @ 0x006BA220 size 136
public ?d_006ba220@@YAXXZ
?d_006ba220@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 93h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 46h, 04h
    db 8Bh, 78h, 48h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 4Eh, 34h, 49h, 89h, 4Eh, 34h, 8Bh, 46h, 34h, 85h, 0C0h, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 75h, 12h, 0FFh, 15h, 0CCh, 95h, 35h, 01h, 8Bh
    db 4Eh, 04h, 56h, 89h, 46h, 38h, 0E8h, 0D7h, 0E7h, 94h, 0FFh, 84h, 0DBh, 74h, 07h, 57h
    db 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_006ba220@@YAXXZ ENDP

; ghidra: FUN_00aba2d0  retail @ 0x006BA2D0 size 83
public ?d_006ba2d0@@YAXXZ
?d_006ba2d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 50h, 8Bh, 0F1h, 0E8h, 83h, 0D8h, 1Ch, 00h, 8Bh, 4Ch, 24h
    db 08h, 33h, 0C0h, 89h, 46h, 34h, 89h, 46h, 38h, 88h, 46h, 41h, 89h, 46h, 2Ch, 89h
    db 46h, 30h, 89h, 46h, 3Ch, 88h, 46h, 40h, 88h, 46h, 42h, 89h, 4Eh, 04h, 33h, 0D2h
    db 8Dh, 46h, 08h, 89h, 10h, 89h, 50h, 04h, 89h, 50h, 08h, 89h, 50h, 0Ch, 89h, 50h
    db 10h, 89h, 50h, 14h, 89h, 50h, 18h, 89h, 50h, 1Ch, 89h, 50h, 20h, 8Bh, 0C6h, 5Eh
    db 0C2h, 08h, 00h
?d_006ba2d0@@YAXXZ ENDP

; ghidra: FUN_00aba340  retail @ 0x006BA340 size 202
public ?d_006ba340@@YAXXZ
?d_006ba340@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 08h, 94h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 46h, 34h
    db 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 59h, 0E8h, 5Fh, 0F3h, 1Ch
    db 00h, 84h, 0C0h, 74h, 50h, 6Ah, 01h, 0E8h, 24h, 0F3h, 1Ch, 00h, 8Bh, 0Dh, 5Ch, 6Eh
    db 33h, 01h, 8Bh, 01h, 83h, 0C4h, 04h, 0FFh, 50h, 60h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h
    db 8Bh, 11h, 6Ah, 00h, 6Ah, 00h, 0FFh, 52h, 6Ch, 8Bh, 10h, 68h, 0F4h, 0C8h, 11h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 4Eh, 34h, 8Bh, 10h, 51h, 8Bh, 0C8h, 0FFh, 52h, 34h
    db 8Bh, 10h, 68h, 0C8h, 0C8h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah, 02h
    db 8Bh, 0C8h, 0FFh, 52h, 4Ch, 8Bh, 46h, 2Ch, 85h, 0C0h, 74h, 1Fh, 8Ah, 4Eh, 40h, 84h
    db 0C9h, 50h, 74h, 08h, 0FFh, 15h, 0C8h, 95h, 35h, 01h, 0EBh, 08h, 0E8h, 0Fh, 7Bh, 1Ch
    db 00h, 83h, 0C4h, 04h, 0C7h, 46h, 2Ch, 00h, 00h, 00h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 46h, 0D5h, 1Ch, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006ba340@@YAXXZ ENDP

; ghidra: FUN_00aba440  retail @ 0x006BA440 size 18
public ?d_006ba440@@YAXXZ
?d_006ba440@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 4Fh, 45h, 97h, 0FFh, 0C7h, 06h, 38h, 0C9h, 11h, 01h, 8Bh, 0C6h
    db 5Eh, 0C3h
?d_006ba440@@YAXXZ ENDP

; ghidra: FUN_00aba460  retail @ 0x006BA460 size 11
public ?d_006ba460@@YAXXZ
?d_006ba460@@YAXXZ PROC
    db 0C7h, 01h, 38h, 0C9h, 11h, 01h, 0E9h, 5Bh, 0CBh, 96h, 0FFh
?d_006ba460@@YAXXZ ENDP

; ghidra: FUN_00aba470  retail @ 0x006BA470 size 18
public ?d_006ba470@@YAXXZ
?d_006ba470@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0A4h, 0A4h, 94h, 0FFh, 0C7h, 06h, 50h, 0C9h, 11h, 01h, 8Bh, 0C6h
    db 5Eh, 0C3h
?d_006ba470@@YAXXZ ENDP

; ghidra: FUN_00aba490  retail @ 0x006BA490 size 11
public ?d_006ba490@@YAXXZ
?d_006ba490@@YAXXZ PROC
    db 0C7h, 01h, 50h, 0C9h, 11h, 01h, 0E9h, 0DAh, 93h, 97h, 0FFh
?d_006ba490@@YAXXZ ENDP

; ghidra: FUN_00aba610  retail @ 0x006BA610 size 207
public ?d_006ba610@@YAXXZ
?d_006ba610@@YAXXZ PROC
    db 81h, 0ECh, 00h, 04h, 00h, 00h, 53h, 56h, 8Bh, 0F1h, 8Bh, 56h, 20h, 8Bh, 46h, 1Ch
    db 83h, 0FAh, 0FEh, 0Fh, 95h, 0C3h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 68h, 0FFh
    db 03h, 00h, 00h, 8Dh, 4Ch, 24h, 20h, 51h, 50h, 0FFh, 15h, 24h, 8Eh, 35h, 01h, 85h
    db 0C0h, 74h, 34h, 8Dh, 44h, 24h, 08h, 8Dh, 50h, 01h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 50h, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh
    db 4Eh, 18h, 0E8h, 0A9h, 0D6h, 1Ch, 00h, 0C7h, 46h, 20h, 0FDh, 0FFh, 0FFh, 0FFh, 5Eh, 5Bh
    db 81h, 0C4h, 00h, 04h, 00h, 00h, 0C3h, 8Dh, 4Eh, 18h, 0E8h, 0B1h, 0D2h, 1Ch, 00h, 84h
    db 0DBh, 0C7h, 46h, 20h, 0FEh, 0FFh, 0FFh, 0FFh, 74h, 3Ch, 0A1h, 48h, 0CBh, 34h, 01h, 85h
    db 0C0h, 74h, 33h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 74h, 29h, 8Bh, 01h, 0FFh
    db 90h, 3Ch, 01h, 00h, 00h, 84h, 0C0h, 74h, 1Dh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 52h, 28h, 8Bh, 0Dh, 50h, 0CCh, 34h, 01h, 8Bh, 01h, 68h, 0B0h
    db 0BFh, 11h, 01h, 0FFh, 50h, 0Ch, 5Eh, 5Bh, 81h, 0C4h, 00h, 04h, 00h, 00h, 0C3h
?d_006ba610@@YAXXZ ENDP

; ghidra: FUN_00aba820  retail @ 0x006BA820 size 29
public ?d_006ba820@@YAXXZ
?d_006ba820@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 07h, 0F4h, 97h, 0FFh, 6Ah, 01h, 0C7h, 06h, 0A8h, 0C9h, 11h, 01h
    db 0FFh, 15h, 08h, 8Fh, 35h, 01h, 89h, 46h, 5Ch, 8Bh, 0C6h, 5Eh, 0C3h
?d_006ba820@@YAXXZ ENDP

; ghidra: FUN_00aba850  retail @ 0x006BA850 size 89
public ?d_006ba850@@YAXXZ
?d_006ba850@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 8Bh, 94h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 1Ch, 01h, 00h, 00h, 0E8h, 0C0h, 76h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 16h, 8Bh, 0C8h, 0E8h, 0C9h, 0CBh, 97h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006ba850@@YAXXZ ENDP

; ghidra: FUN_00aba8c0  retail @ 0x006BA8C0 size 86
public ?d_006ba8c0@@YAXXZ
?d_006ba8c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0ABh, 94h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 24h, 0E8h, 53h, 76h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 16h, 8Bh
    db 0C8h, 0E8h, 0E8h, 39h, 98h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006ba8c0@@YAXXZ ENDP

; ghidra: FUN_00abaa10  retail @ 0x006BAA10 size 89
public ?d_006baa10@@YAXXZ
?d_006baa10@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Bh, 95h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 08h, 15h, 00h, 00h, 0E8h, 00h, 75h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 16h, 8Bh, 0C8h, 0E8h, 51h, 0B9h, 97h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006baa10@@YAXXZ ENDP

; ghidra: FUN_00abaa90  retail @ 0x006BAA90 size 89
public ?d_006baa90@@YAXXZ
?d_006baa90@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Bh, 95h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 0C8h, 01h, 00h, 00h, 0E8h, 80h, 74h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 16h, 8Bh, 0C8h, 0E8h, 5Bh, 85h, 96h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006baa90@@YAXXZ ENDP

; ghidra: FUN_00abab00  retail @ 0x006BAB00 size 27
public ?d_006bab00@@YAXXZ
?d_006bab00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 5Ch, 50h, 0C7h, 06h, 0A8h, 0C9h, 11h, 01h, 0FFh, 15h, 08h
    db 8Fh, 35h, 01h, 8Bh, 0CEh, 5Eh, 0E9h, 0DDh, 0EAh, 98h, 0FFh
?d_006bab00@@YAXXZ ENDP

; ghidra: FUN_00abab60  retail @ 0x006BAB60 size 165
public ?d_006bab60@@YAXXZ
?d_006bab60@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 77h, 76h, 94h, 0FFh, 0A1h, 38h, 0D2h, 2Eh, 01h, 85h, 0C0h, 0Fh
    db 84h, 88h, 00h, 00h, 00h, 53h, 8Bh, 1Dh, 20h, 90h, 35h, 01h, 50h, 0FFh, 0D3h, 85h
    db 0C0h, 74h, 79h, 0A1h, 38h, 0D2h, 2Eh, 01h, 85h, 0C0h, 74h, 70h, 57h, 8Bh, 3Dh, 30h
    db 8Fh, 35h, 01h, 55h, 50h, 0FFh, 0D3h, 85h, 0C0h, 74h, 5Fh, 6Ah, 05h, 0FFh, 0D7h, 8Bh
    db 06h, 8Bh, 0CEh, 0FFh, 50h, 40h, 0A1h, 30h, 77h, 2Fh, 01h, 85h, 0C0h, 74h, 1Eh, 8Bh
    db 16h, 8Bh, 28h, 8Bh, 0CEh, 0FFh, 52h, 44h, 8Bh, 0Dh, 30h, 77h, 2Fh, 01h, 50h, 0FFh
    db 55h, 24h, 8Bh, 0Dh, 30h, 77h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h, 14h, 8Bh, 0Dh, 24h
    db 0D5h, 2Eh, 01h, 8Bh, 11h, 0FFh, 52h, 38h, 84h, 0C0h, 75h, 1Eh, 0A1h, 98h, 08h, 2Fh
    db 01h, 8Bh, 80h, 0Ch, 01h, 00h, 00h, 83h, 0F8h, 05h, 74h, 0Eh, 83h, 0F8h, 01h, 74h
    db 09h, 0A1h, 38h, 0D2h, 2Eh, 01h, 85h, 0C0h, 75h, 9Ah, 5Dh, 5Fh, 5Bh, 8Bh, 16h, 8Bh
    db 0CEh, 5Eh, 0FFh, 62h, 40h
?d_006bab60@@YAXXZ ENDP

; ghidra: FUN_00abac30  retail @ 0x006BAC30 size 124
public ?d_006bac30@@YAXXZ
?d_006bac30@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 56h, 8Bh, 35h, 44h, 90h, 35h, 01h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h
    db 6Ah, 00h, 8Dh, 44h, 24h, 14h, 50h, 0FFh, 0D6h, 85h, 0C0h, 74h, 5Ah, 53h, 8Bh, 1Dh
    db 98h, 90h, 35h, 01h, 55h, 8Bh, 2Dh, 0C8h, 8Fh, 35h, 01h, 57h, 8Bh, 3Dh, 0Ch, 90h
    db 35h, 01h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 8Dh, 4Ch, 24h, 1Ch, 51h, 0FFh, 0D7h, 8Bh
    db 54h, 24h, 20h, 8Dh, 44h, 24h, 10h, 50h, 89h, 15h, 44h, 0D2h, 2Eh, 01h, 0FFh, 0D3h
    db 8Dh, 4Ch, 24h, 10h, 51h, 0FFh, 0D5h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 8Dh
    db 54h, 24h, 20h, 52h, 0C7h, 05h, 44h, 0D2h, 2Eh, 01h, 00h, 00h, 00h, 00h, 0FFh, 0D6h
    db 85h, 0C0h, 75h, 0BEh, 5Fh, 5Dh, 5Bh, 5Eh, 83h, 0C4h, 1Ch, 0C3h
?d_006bac30@@YAXXZ ENDP

; ghidra: FUN_00abaee0  retail @ 0x006BAEE0 size 87
public ?d_006baee0@@YAXXZ
?d_006baee0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0CBh, 95h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 24h, 0E8h, 32h, 70h, 1Ch, 00h, 8Bh, 0F0h
    db 83h, 0C4h, 04h, 89h, 74h, 24h, 04h, 33h, 0C0h, 3Bh, 0F0h, 89h, 44h, 24h, 10h, 74h
    db 16h, 8Bh, 0CEh, 0E8h, 0E5h, 0E7h, 97h, 0FFh, 0C7h, 06h, 0ACh, 0CAh, 11h, 01h, 0C7h, 46h
    db 08h, 98h, 0CAh, 11h, 01h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006baee0@@YAXXZ ENDP

; ghidra: FUN_00abb2c0  retail @ 0x006BB2C0 size 69
public ?d_006bb2c0@@YAXXZ
?d_006bb2c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 20h, 0Eh, 00h, 00h, 85h, 0C0h, 74h, 1Ch, 8Bh, 08h, 50h
    db 0FFh, 51h, 20h, 8Bh, 86h, 20h, 0Eh, 00h, 00h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0C7h
    db 86h, 20h, 0Eh, 00h, 00h, 00h, 00h, 00h, 00h, 8Bh, 86h, 1Ch, 0Eh, 00h, 00h, 85h
    db 0C0h, 74h, 10h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 0C7h, 86h, 1Ch, 0Eh, 00h, 00h, 00h
    db 00h, 00h, 00h, 5Eh, 0C3h
?d_006bb2c0@@YAXXZ ENDP

; ghidra: FUN_00abb320  retail @ 0x006BB320 size 187
public ?d_006bb320@@YAXXZ
?d_006bb320@@YAXXZ PROC
    db 83h, 0ECh, 14h, 56h, 57h, 8Bh, 7Ch, 24h, 20h, 8Bh, 0F1h, 0C7h, 47h, 04h, 00h, 00h
    db 00h, 00h, 0C6h, 07h, 00h, 8Bh, 86h, 20h, 0Eh, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 90h
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 01h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 51h
    db 1Ch, 85h, 0C0h, 74h, 05h, 83h, 0F8h, 01h, 75h, 1Ah, 8Bh, 86h, 20h, 0Eh, 00h, 00h
    db 8Bh, 10h, 6Ah, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 4Ch, 24h, 10h, 51h, 6Ah, 14h
    db 50h, 0FFh, 52h, 28h, 3Dh, 0Ch, 00h, 07h, 80h, 74h, 40h, 3Dh, 1Eh, 00h, 07h, 80h
    db 74h, 39h, 85h, 0C0h, 75h, 4Dh, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 74h, 45h, 8Ah, 4Ch
    db 24h, 0Ch, 8Ah, 54h, 24h, 08h, 8Bh, 44h, 24h, 14h, 0F6h, 0C1h, 80h, 0B9h, 00h, 00h
    db 00h, 00h, 0Fh, 95h, 0C1h, 88h, 17h, 89h, 47h, 04h, 0C6h, 47h, 01h, 00h, 41h, 66h
    db 89h, 4Fh, 02h, 5Fh, 5Eh, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 8Bh, 0B6h, 20h, 0Eh, 00h
    db 00h, 8Bh, 16h, 56h, 0FFh, 52h, 1Ch, 85h, 0C0h, 7Ch, 08h, 83h, 0F8h, 01h, 7Fh, 03h
    db 0C6h, 07h, 0FFh, 5Fh, 5Eh, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006bb320@@YAXXZ ENDP

; ghidra: FUN_00abb410  retail @ 0x006BB410 size 54
public ?d_006bb410@@YAXXZ
?d_006bb410@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 30h, 0DDh, 98h, 0FFh, 33h, 0C0h, 6Ah, 14h, 0C7h, 06h, 0CCh, 0CDh
    db 11h, 01h, 89h, 86h, 1Ch, 0Eh, 00h, 00h, 89h, 86h, 20h, 0Eh, 00h, 00h, 0FFh, 15h
    db 04h, 90h, 35h, 01h, 0A8h, 01h, 8Bh, 0C6h, 74h, 06h, 80h, 4Eh, 09h, 02h, 5Eh, 0C3h
    db 80h, 66h, 09h, 0FDh, 5Eh, 0C3h
?d_006bb410@@YAXXZ ENDP

; ghidra: FUN_00abb460  retail @ 0x006BB460 size 138
public ?d_006bb460@@YAXXZ
?d_006bb460@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0CCh
    db 0CDh, 11h, 01h, 8Bh, 86h, 20h, 0Eh, 00h, 00h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 74h, 1Ch, 8Bh, 08h, 50h, 0FFh, 51h, 20h, 8Bh, 86h, 20h, 0Eh, 00h
    db 00h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0C7h, 86h, 20h, 0Eh, 00h, 00h, 00h, 00h, 00h
    db 00h, 8Bh, 86h, 1Ch, 0Eh, 00h, 00h, 85h, 0C0h, 74h, 10h, 8Bh, 08h, 50h, 0FFh, 51h
    db 08h, 0C7h, 86h, 1Ch, 0Eh, 00h, 00h, 00h, 00h, 00h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B4h, 6Bh, 96h, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bb460@@YAXXZ ENDP

; ghidra: FUN_00abb540  retail @ 0x006BB540 size 207
public ?d_006bb540@@YAXXZ
?d_006bb540@@YAXXZ PROC
    db 0A1h, 34h, 0D2h, 2Eh, 01h, 83h, 0ECh, 14h, 53h, 57h, 6Ah, 00h, 8Bh, 0F9h, 8Dh, 9Fh
    db 1Ch, 0Eh, 00h, 00h, 53h, 68h, 0F4h, 0B4h, 1Bh, 01h, 68h, 00h, 08h, 00h, 00h, 50h
    db 0E8h, 8Bh, 0E5h, 33h, 00h, 85h, 0C0h, 7Dh, 0Dh, 8Bh, 0CFh, 0E8h, 0CDh, 0EBh, 98h, 0FFh
    db 5Fh, 5Bh, 83h, 0C4h, 14h, 0C3h, 8Bh, 03h, 8Bh, 08h, 56h, 6Ah, 00h, 8Dh, 0B7h, 20h
    db 0Eh, 00h, 00h, 56h, 68h, 84h, 0B3h, 1Bh, 01h, 50h, 0FFh, 51h, 0Ch, 85h, 0C0h, 7Dh
    db 0Eh, 8Bh, 0CFh, 0E8h, 0A5h, 0EBh, 98h, 0FFh, 5Eh, 5Fh, 5Bh, 83h, 0C4h, 14h, 0C3h, 8Bh
    db 06h, 8Bh, 10h, 68h, 0B4h, 60h, 14h, 01h, 50h, 0FFh, 52h, 2Ch, 85h, 0C0h, 7Ch, 0E1h
    db 8Bh, 15h, 38h, 0D2h, 2Eh, 01h, 8Bh, 06h, 8Bh, 08h, 6Ah, 06h, 52h, 50h, 0FFh, 51h
    db 34h, 85h, 0C0h, 7Ch, 0CCh, 8Bh, 06h, 8Dh, 54h, 24h, 0Ch, 52h, 6Ah, 01h, 0C7h, 44h
    db 24h, 14h, 14h, 00h, 00h, 00h, 0C7h, 44h, 24h, 18h, 10h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 24h, 00h, 01h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 51h, 18h, 85h, 0C0h, 7Ch, 91h
    db 8Bh, 36h, 8Bh, 06h, 56h, 0FFh, 50h, 1Ch, 5Eh, 5Fh, 5Bh, 83h, 0C4h, 14h, 0C3h
?d_006bb540@@YAXXZ ENDP

; ghidra: FUN_00abb680  retail @ 0x006BB680 size 16
public ?d_006bb680@@YAXXZ
?d_006bb680@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 61h, 4Fh, 97h, 0FFh, 8Bh, 0CEh, 5Eh, 0E9h, 0DAh, 65h, 96h, 0FFh
?d_006bb680@@YAXXZ ENDP

; ghidra: FUN_00abba90  retail @ 0x006BBA90 size 7
_TEXT ENDS
_TEXT$d00abba90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00ABBA90 size 7
public ?d_006bba90@@YAXXZ
?d_006bba90@@YAXXZ PROC
    db 0FFh, 015h
    dd g_Va01359054
    db 0CCh
?d_006bba90@@YAXXZ ENDP
_TEXT$d00abba90 ENDS
_TEXT SEGMENT

; ghidra: FUN_00abbd80  retail @ 0x006BBD80 size 475
public ?d_006bbd80@@YAXXZ
?d_006bbd80@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 8Bh, 44h, 24h, 10h, 53h, 55h, 8Bh, 0E9h, 0C1h, 0E0h, 04h, 8Bh, 8Ch
    db 28h, 14h, 4Eh, 00h, 00h, 8Bh, 94h, 28h, 18h, 4Eh, 00h, 00h, 03h, 0C5h, 89h, 4Ch
    db 24h, 08h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 56h, 33h, 0DBh, 3Bh, 0CBh, 57h, 8Bh, 0B8h
    db 1Ch, 4Eh, 00h, 00h, 89h, 54h, 24h, 18h, 74h, 0Ch, 8Bh, 01h, 0FFh, 50h, 68h, 0BAh
    db 01h, 00h, 00h, 00h, 0EBh, 07h, 0BAh, 01h, 00h, 00h, 00h, 8Bh, 0C2h, 8Bh, 74h, 24h
    db 24h, 8Bh, 4Ch, 24h, 20h, 81h, 0C1h, 0E2h, 04h, 00h, 00h, 0C1h, 0E1h, 04h, 89h, 5Eh
    db 24h, 89h, 5Eh, 30h, 89h, 5Eh, 18h, 89h, 5Eh, 2Ch, 89h, 5Eh, 38h, 89h, 5Eh, 20h
    db 89h, 5Eh, 0Ch, 89h, 5Eh, 04h, 89h, 1Eh, 8Bh, 0Ch, 29h, 89h, 4Eh, 08h, 8Bh, 4Ch
    db 24h, 10h, 81h, 0C1h, 00h, 0FEh, 0FFh, 0FFh, 83h, 0F9h, 0Ah, 0Fh, 87h, 40h, 01h, 00h
    db 00h, 0FFh, 24h, 8Dh, 5Ch, 0BFh, 0ABh, 00h, 89h, 56h, 18h, 0Fh, 0B7h, 0D7h, 0C1h, 0EFh
    db 10h, 89h, 7Eh, 04h, 5Fh, 89h, 46h, 20h, 89h, 16h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch
    db 0C2h, 08h, 00h, 89h, 46h, 20h, 0Fh, 0B7h, 0C7h, 0C1h, 0EFh, 10h, 89h, 7Eh, 04h, 5Fh
    db 89h, 5Eh, 18h, 89h, 06h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0Fh, 0B7h
    db 0CFh, 0C1h, 0EFh, 10h, 89h, 7Eh, 04h, 5Fh, 0C7h, 46h, 18h, 02h, 00h, 00h, 00h, 89h
    db 46h, 20h, 89h, 0Eh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 89h, 56h, 30h
    db 0Fh, 0B7h, 0D7h, 0C1h, 0EFh, 10h, 89h, 7Eh, 04h, 5Fh, 89h, 46h, 38h, 89h, 16h, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 89h, 46h, 38h, 0Fh, 0B7h, 0C7h, 0C1h, 0EFh
    db 10h, 89h, 7Eh, 04h, 5Fh, 89h, 5Eh, 30h, 89h, 06h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch
    db 0C2h, 08h, 00h, 0Fh, 0B7h, 0CFh, 0C1h, 0EFh, 10h, 89h, 7Eh, 04h, 5Fh, 0C7h, 46h, 30h
    db 02h, 00h, 00h, 00h, 89h, 46h, 38h, 89h, 0Eh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 89h, 56h, 24h, 89h, 46h, 2Ch, 0Fh, 0B7h, 0D7h, 0C1h, 0EFh, 10h, 89h, 7Eh
    db 04h, 5Fh, 89h, 16h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 89h, 46h, 2Ch
    db 0Fh, 0B7h, 0C7h, 0C1h, 0EFh, 10h, 89h, 7Eh, 04h, 5Fh, 89h, 5Eh, 24h, 89h, 06h, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0Fh, 0B7h, 0CFh, 0C1h, 0EFh, 10h, 89h, 7Eh
    db 04h, 5Fh, 0C7h, 46h, 24h, 02h, 00h, 00h, 00h, 89h, 46h, 2Ch, 89h, 0Eh, 5Eh, 5Dh
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 15h, 38h, 0D2h, 2Eh, 01h, 0Fh, 0B7h, 0C7h
    db 8Dh, 4Ch, 24h, 10h, 51h, 0C1h, 0EFh, 10h, 52h, 89h, 44h, 24h, 18h, 89h, 7Ch, 24h
    db 1Ch, 0FFh, 15h, 5Ch, 90h, 35h, 01h, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 10h, 8Bh
    db 54h, 24h, 14h, 0C1h, 0E8h, 10h, 0Fh, 0BFh, 0C0h, 89h, 46h, 0Ch, 89h, 56h, 04h, 89h
    db 0Eh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_006bbd80@@YAXXZ ENDP

; ghidra: FUN_00abc010  retail @ 0x006BC010 size 79
public ?d_006bc010@@YAXXZ
?d_006bc010@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 0E8h, 0A4h, 0E8h, 98h, 0FFh, 33h, 0C0h, 33h, 0D2h, 0C7h, 06h, 80h
    db 0CEh, 11h, 01h, 8Dh, 0BEh, 14h, 4Eh, 00h, 00h, 0B9h, 00h, 04h, 00h, 00h, 0F3h, 0ABh
    db 89h, 96h, 14h, 5Eh, 00h, 00h, 89h, 96h, 18h, 5Eh, 00h, 00h, 89h, 96h, 1Ch, 5Eh
    db 00h, 00h, 0B9h, 90h, 01h, 00h, 00h, 0BFh, 0A8h, 77h, 2Fh, 01h, 0F3h, 0ABh, 5Fh, 89h
    db 96h, 20h, 5Eh, 00h, 00h, 88h, 96h, 24h, 5Eh, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_006bc010@@YAXXZ ENDP

; ghidra: FUN_00abc080  retail @ 0x006BC080 size 21
public ?d_006bc080@@YAXXZ
?d_006bc080@@YAXXZ PROC
    db 0C7h, 01h, 80h, 0CEh, 11h, 01h, 0C7h, 05h, 40h, 0D2h, 2Eh, 01h, 00h, 00h, 00h, 00h
    db 0E9h, 5Dh, 77h, 98h, 0FFh
?d_006bc080@@YAXXZ ENDP

; ghidra: FUN_00abc0a0  retail @ 0x006BC0A0 size 17
public ?d_006bc0a0@@YAXXZ
?d_006bc0a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0B2h, 63h, 94h, 0FFh, 0C6h, 86h, 0A0h, 4Dh, 00h, 00h, 01h, 5Eh
    db 0C3h
?d_006bc0a0@@YAXXZ ENDP

; ghidra: FUN_00abc0e0  retail @ 0x006BC0E0 size 129
public ?d_006bc0e0@@YAXXZ
?d_006bc0e0@@YAXXZ PROC
    db 8Bh, 81h, 14h, 5Eh, 00h, 00h, 0C1h, 0E0h, 04h, 8Bh, 94h, 08h, 14h, 4Eh, 00h, 00h
    db 85h, 0D2h, 8Dh, 84h, 08h, 14h, 4Eh, 00h, 00h, 75h, 63h, 8Bh, 54h, 24h, 04h, 89h
    db 10h, 8Bh, 81h, 14h, 5Eh, 00h, 00h, 8Bh, 54h, 24h, 08h, 0C1h, 0E0h, 04h, 89h, 94h
    db 08h, 18h, 4Eh, 00h, 00h, 8Bh, 81h, 14h, 5Eh, 00h, 00h, 8Bh, 54h, 24h, 0Ch, 0C1h
    db 0E0h, 04h, 89h, 94h, 08h, 1Ch, 4Eh, 00h, 00h, 8Bh, 81h, 14h, 5Eh, 00h, 00h, 8Bh
    db 54h, 24h, 10h, 05h, 0E2h, 04h, 00h, 00h, 0C1h, 0E0h, 04h, 89h, 14h, 08h, 8Bh, 91h
    db 14h, 5Eh, 00h, 00h, 42h, 8Bh, 0C2h, 3Dh, 00h, 01h, 00h, 00h, 89h, 91h, 14h, 5Eh
    db 00h, 00h, 72h, 0Ah, 0C7h, 81h, 14h, 5Eh, 00h, 00h, 00h, 00h, 00h, 00h, 0C2h, 10h
    db 00h
?d_006bc0e0@@YAXXZ ENDP

; ghidra: FUN_00abc190  retail @ 0x006BC190 size 83
public ?d_006bc190@@YAXXZ
?d_006bc190@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 82h, 23h, 95h, 0FFh, 8Ah, 86h
    db 24h, 5Eh, 00h, 00h, 84h, 0C0h, 75h, 36h, 85h, 0FFh, 74h, 1Eh, 8Bh, 0CEh, 0E8h, 0F3h
    db 7Dh, 96h, 0FFh, 84h, 0C0h, 74h, 13h, 8Bh, 86h, 20h, 5Eh, 00h, 00h, 8Dh, 0Ch, 0F8h
    db 8Bh, 14h, 8Dh, 0A8h, 77h, 2Fh, 01h, 52h, 0EBh, 02h, 6Ah, 00h, 0FFh, 15h, 6Ch, 90h
    db 35h, 01h, 89h, 0BEh, 0A8h, 4Dh, 00h, 00h, 89h, 0BEh, 1Ch, 5Eh, 00h, 00h, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_006bc190@@YAXXZ ENDP

; ghidra: FUN_00abc220  retail @ 0x006BC220 size 70
public ?d_006bc220@@YAXXZ
?d_006bc220@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 74h, 24h, 14h, 57h, 8Bh, 7Ch, 24h, 14h, 56h, 57h, 0E8h
    db 0BAh, 56h, 98h, 0FFh, 8Bh, 0Dh, 38h, 0D2h, 2Eh, 01h, 8Dh, 44h, 24h, 08h, 50h, 51h
    db 89h, 7Ch, 24h, 10h, 89h, 74h, 24h, 14h, 0FFh, 15h, 0ACh, 8Fh, 35h, 01h, 8Bh, 54h
    db 24h, 0Ch, 8Bh, 44h, 24h, 08h, 52h, 50h, 0FFh, 15h, 70h, 90h, 35h, 01h, 5Fh, 5Eh
    db 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_006bc220@@YAXXZ ENDP

; ghidra: FUN_00abc360  retail @ 0x006BC360 size 367
public ?d_006bc360@@YAXXZ
?d_006bc360@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 7Bh, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 08h, 01h, 00h, 00h, 53h, 55h, 56h, 0BDh, 0C8h
    db 77h, 2Fh, 01h, 57h, 89h, 6Ch, 24h, 14h, 8Dh, 99h, 0ACh, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 03h, 33h, 0FFh, 85h, 0C0h, 0Fh, 8Eh, 04h, 01h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 83h, 7Dh, 00h, 00h, 0Fh, 85h, 0E4h, 00h, 00h, 00h, 8Bh, 4Bh, 0D8h, 85h, 0C9h, 8Dh
    db 43h, 0D8h, 0Fh, 84h, 0D6h, 00h, 00h, 00h, 66h, 83h, 79h, 04h, 00h, 0Fh, 84h, 0CBh
    db 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 14h, 0BEh, 38h, 0CFh, 11h, 01h, 0E8h, 8Eh, 0B7h
    db 1Ch, 00h, 6Ah, 04h, 68h, 30h, 0CFh, 11h, 01h, 8Dh, 4Ch, 24h, 18h, 0C7h, 84h, 24h
    db 28h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 93h, 0B2h, 1Ch, 00h, 84h, 0C0h, 74h
    db 29h, 8Dh, 4Ch, 24h, 10h, 0BEh, 2Ch, 0CFh, 11h, 01h, 0E8h, 81h, 0BBh, 1Ch, 00h, 8Dh
    db 4Ch, 24h, 10h, 0E8h, 78h, 0BBh, 1Ch, 00h, 8Dh, 4Ch, 24h, 10h, 0E8h, 6Fh, 0BBh, 1Ch
    db 00h, 8Dh, 4Ch, 24h, 10h, 0E8h, 66h, 0BBh, 1Ch, 00h, 83h, 3Bh, 01h, 8Bh, 44h, 24h
    db 10h, 7Eh, 26h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h
    db 01h, 56h, 57h, 50h, 8Dh, 44h, 24h, 24h, 68h, 10h, 0CFh, 11h, 01h, 50h, 0FFh, 15h
    db 8Ch, 94h, 35h, 01h, 83h, 0C4h, 14h, 0EBh, 23h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h
    db 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 56h, 50h, 8Dh, 4Ch, 24h, 20h, 68h, 0F8h, 0CEh
    db 11h, 01h, 51h, 0FFh, 15h, 8Ch, 94h, 35h, 01h, 83h, 0C4h, 10h, 8Dh, 54h, 24h, 18h
    db 52h, 0FFh, 15h, 34h, 90h, 35h, 01h, 8Dh, 4Ch, 24h, 10h, 89h, 45h, 00h, 0C7h, 84h
    db 24h, 20h, 01h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B2h, 0B4h, 1Ch, 00h, 8Bh, 03h
    db 47h, 83h, 0C5h, 04h, 3Bh, 0F8h, 0Fh, 8Ch, 04h, 0FFh, 0FFh, 0FFh, 8Bh, 6Ch, 24h, 14h
    db 83h, 0C5h, 20h, 83h, 0C3h, 54h, 81h, 0FDh, 0E8h, 7Dh, 2Fh, 01h, 89h, 6Ch, 24h, 14h
    db 0Fh, 8Ch, 0DAh, 0FEh, 0FFh, 0FFh, 8Bh, 8Ch, 24h, 18h, 01h, 00h, 00h, 5Fh, 5Eh, 5Dh
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 14h, 01h, 00h, 00h, 0C3h
?d_006bc360@@YAXXZ ENDP

; ghidra: FUN_00abc530  retail @ 0x006BC530 size 25
public ?d_006bc530@@YAXXZ
?d_006bc530@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0E2h, 0CAh, 95h, 0FFh, 0C7h, 06h, 68h, 0CFh, 11h, 01h, 0C7h, 46h
    db 04h, 3Ch, 0CFh, 11h, 01h, 8Bh, 0C6h, 5Eh, 0C3h
?d_006bc530@@YAXXZ ENDP

; ghidra: FUN_00abc560  retail @ 0x006BC560 size 18
public ?d_006bc560@@YAXXZ
?d_006bc560@@YAXXZ PROC
    db 0C7h, 01h, 68h, 0CFh, 11h, 01h, 0C7h, 41h, 04h, 3Ch, 0CFh, 11h, 01h, 0E9h, 4Fh, 0C1h
    db 98h, 0FFh
?d_006bc560@@YAXXZ ENDP

; ghidra: FUN_00abc5c0  retail @ 0x006BC5C0 size 8
public ?d_006bc5c0@@YAXXZ
?d_006bc5c0@@YAXXZ PROC
    db 83h, 0E9h, 04h, 0E9h, 61h, 0A3h, 94h, 0FFh
?d_006bc5c0@@YAXXZ ENDP

; ghidra: FUN_00abc6e0  retail @ 0x006BC6E0 size 48
public ?d_006bc6e0@@YAXXZ
?d_006bc6e0@@YAXXZ PROC
    db 8Bh, 41h, 08h, 0C7h, 01h, 0B8h, 0CFh, 11h, 01h, 0C7h, 41h, 04h, 0A4h, 0CFh, 11h, 01h
    db 8Bh, 50h, 04h, 0C7h, 44h, 0Ah, 08h, 8Ch, 0CFh, 11h, 01h, 8Bh, 41h, 08h, 8Bh, 40h
    db 04h, 8Dh, 90h, 0ECh, 0FEh, 0FFh, 0FFh, 89h, 54h, 08h, 04h, 0E9h, 40h, 87h, 97h, 0FFh
?d_006bc6e0@@YAXXZ ENDP

; ghidra: FUN_00abc750  retail @ 0x006BC750 size 72
public ?d_006bc750@@YAXXZ
?d_006bc750@@YAXXZ PROC
    db 8Bh, 41h, 0Ch, 85h, 0C0h, 74h, 40h, 8Bh, 0C8h, 8Bh, 01h, 56h, 0FFh, 50h, 28h, 8Bh
    db 0F0h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 14h, 01h, 95h, 0FFh, 8Bh, 0CEh, 0E8h, 01h, 4Dh, 96h
    db 0FFh, 8Bh, 0F0h, 8Bh, 0Eh, 85h, 0C9h, 74h, 1Dh, 8Bh, 11h, 0FFh, 92h, 0B8h, 00h, 00h
    db 00h, 85h, 0C0h, 74h, 07h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 40h, 8Bh, 4Eh, 04h, 83h
    db 0C6h, 04h, 85h, 0C9h, 75h, 0E3h, 5Eh, 0C3h
?d_006bc750@@YAXXZ ENDP

; ghidra: FUN_00abc820  retail @ 0x006BC820 size 35
public ?d_006bc820@@YAXXZ
?d_006bc820@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0B4h, 81h, 80h, 00h, 00h, 00h, 85h, 0F6h, 74h, 0Fh
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 0FFh, 52h, 40h, 8Bh, 76h, 08h, 85h, 0F6h, 75h, 0F1h, 5Eh
    db 0C2h, 04h, 00h
?d_006bc820@@YAXXZ ENDP

; ghidra: FUN_00abc8f0  retail @ 0x006BC8F0 size 192
public ?d_006bc8f0@@YAXXZ
?d_006bc8f0@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 57h, 8Bh, 7Bh, 10h, 85h, 0FFh, 0Fh, 84h, 0AEh, 00h, 00h, 00h, 55h
    db 8Bh, 6Ch, 24h, 10h, 56h, 0EBh, 09h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 43h, 04h, 8Bh, 0B4h, 87h, 80h, 00h, 00h, 00h, 85h, 0F6h, 74h, 11h, 8Bh, 0FFh
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 0FFh, 52h, 40h, 8Bh, 76h, 08h, 85h, 0F6h, 75h, 0F1h, 8Bh
    db 84h, 0AFh, 80h, 00h, 00h, 00h, 85h, 0C0h, 74h, 3Fh, 8Bh, 43h, 04h, 8Bh, 8Ch, 87h
    db 80h, 00h, 00h, 00h, 85h, 0C9h, 75h, 0Eh, 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 07h, 8Bh
    db 0CFh, 0E8h, 0F6h, 0C7h, 94h, 0FFh, 8Bh, 0B4h, 0AFh, 80h, 00h, 00h, 00h, 85h, 0F6h, 74h
    db 34h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Bh, 46h, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 08h
    db 8Bh, 76h, 08h, 85h, 0F6h, 75h, 0EAh, 0EBh, 1Ch, 8Bh, 4Bh, 04h, 8Bh, 84h, 8Fh, 80h
    db 00h, 00h, 00h, 85h, 0C0h, 74h, 0Eh, 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 07h, 8Bh, 0CFh
    db 0E8h, 0D8h, 0C0h, 98h, 0FFh, 8Bh, 0BFh, 10h, 01h, 00h, 00h, 85h, 0FFh, 0Fh, 85h, 6Dh
    db 0FFh, 0FFh, 0FFh, 5Eh, 89h, 6Bh, 04h, 5Dh, 5Fh, 5Bh, 0C2h, 04h, 00h, 8Bh, 54h, 24h
?d_006bc8f0@@YAXXZ ENDP

; ghidra: FUN_00abcb70  retail @ 0x006BCB70 size 212
public ?d_006bcb70@@YAXXZ
?d_006bcb70@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 08h, 85h, 0EDh, 0Fh, 84h, 0C5h, 00h, 00h, 00h, 8Bh, 45h, 00h
    db 8Bh, 0CDh, 0FFh, 50h, 0Ch, 83h, 0F8h, 19h, 0Fh, 85h, 0B4h, 00h, 00h, 00h, 8Bh, 55h
    db 00h, 56h, 33h, 0F6h, 8Bh, 0CDh, 89h, 74h, 24h, 0Ch, 0FFh, 52h, 6Ch, 85h, 0C0h, 0Fh
    db 8Eh, 9Ch, 00h, 00h, 00h, 53h, 57h, 8Bh, 45h, 00h, 56h, 8Bh, 0CDh, 0FFh, 50h, 74h
    db 8Bh, 0F0h, 85h, 0F6h, 74h, 70h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 85h, 0C0h, 75h
    db 5Ah, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 50h, 01h, 00h, 00h, 8Bh, 0F8h, 85h, 0FFh, 74h
    db 4Ah, 8Bh, 47h, 18h, 33h, 0DBh, 85h, 0C0h, 7Eh, 36h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 0Ch, 8Bh, 14h, 99h, 8Bh, 4Ah, 20h, 85h, 0C9h, 74h, 1Bh, 8Bh, 01h, 0FFh
    db 50h, 08h, 83h, 0F8h, 01h, 75h, 11h, 8Bh, 16h, 6Ah, 00h, 68h, 94h, 0A3h, 2Bh, 01h
    db 8Bh, 0CEh, 0FFh, 92h, 54h, 01h, 00h, 00h, 8Bh, 47h, 18h, 43h, 3Bh, 0D8h, 7Ch, 0D0h
    db 0FFh, 4Fh, 04h, 75h, 06h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 10h, 0FFh, 4Eh, 04h, 75h, 06h
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h, 8Bh, 74h, 24h, 14h, 8Bh, 45h, 00h, 46h, 8Bh, 0CDh
    db 89h, 74h, 24h, 14h, 0FFh, 50h, 6Ch, 3Bh, 0F0h, 0Fh, 8Ch, 68h, 0FFh, 0FFh, 0FFh, 5Fh
    db 5Bh, 5Eh, 5Dh, 0C3h
?d_006bcb70@@YAXXZ ENDP

; ghidra: FUN_00abcc80  retail @ 0x006BCC80 size 196
public ?d_006bcc80@@YAXXZ
?d_006bcc80@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 04h, 85h, 0C9h, 74h, 1Ch, 8Bh, 01h
    db 0FFh, 50h, 40h, 8Bh, 4Fh, 04h, 85h, 0C9h, 74h, 10h, 0FFh, 49h, 04h, 75h, 04h, 8Bh
    db 11h, 0FFh, 12h, 0C7h, 47h, 04h, 00h, 00h, 00h, 00h, 80h, 7Ch, 24h, 1Ch, 01h, 75h
    db 72h, 8Bh, 74h, 24h, 14h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 08h, 89h, 47h, 04h, 8Bh
    db 4Eh, 4Ch, 89h, 48h, 4Ch, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 50h, 8Bh, 4Fh, 04h, 8Bh
    db 01h, 8Dh, 56h, 18h, 52h, 0FFh, 50h, 54h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 0Ch, 83h
    db 0F8h, 19h, 75h, 46h, 8Bh, 16h, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 0Ch, 51h
    db 8Dh, 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0CEh, 0FFh, 92h, 0Ch, 02h
    db 00h, 00h, 8Bh, 74h, 24h, 1Ch, 8Bh, 4Fh, 04h, 8Bh, 11h, 6Ah, 00h, 56h, 50h, 0FFh
    db 92h, 0B0h, 00h, 00h, 00h, 8Bh, 47h, 04h, 50h, 0E8h, 58h, 38h, 97h, 0FFh, 83h, 0C4h
    db 04h, 0EBh, 07h, 8Bh, 4Ch, 24h, 14h, 89h, 4Fh, 04h, 8Bh, 4Fh, 04h, 8Bh, 44h, 24h
    db 18h, 8Bh, 11h, 6Ah, 00h, 50h, 0FFh, 92h, 54h, 01h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h
    db 08h, 0C2h, 0Ch, 00h
?d_006bcc80@@YAXXZ ENDP

; ghidra: FUN_00abcd80  retail @ 0x006BCD80 size 89
public ?d_006bcd80@@YAXXZ
?d_006bcd80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 4Ch, 24h
    db 1Ch, 8Bh, 54h, 24h, 18h, 33h, 0C0h, 89h, 44h, 24h, 10h, 89h, 46h, 04h, 89h, 46h
    db 08h, 8Bh, 44h, 24h, 20h, 50h, 51h, 52h, 8Bh, 0CEh, 0C7h, 06h, 24h, 0D0h, 11h, 01h
    db 0E8h, 7Ch, 75h, 98h, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_006bcd80@@YAXXZ ENDP

; ghidra: FUN_00abce40  retail @ 0x006BCE40 size 100
public ?d_006bce40@@YAXXZ
?d_006bce40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 24h
    db 0D0h, 11h, 01h, 8Bh, 4Eh, 04h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 05h, 8Bh, 01h, 0FFh, 50h, 40h, 8Bh, 4Eh, 04h, 85h, 0C9h, 74h, 10h, 0FFh, 49h
    db 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh, 4Ch
    db 24h, 08h, 0C7h, 06h, 44h, 37h, 07h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_006bce40@@YAXXZ ENDP

; ghidra: FUN_00abcec0  retail @ 0x006BCEC0 size 343
public ?d_006bcec0@@YAXXZ
?d_006bcec0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 57h, 33h, 0FFh, 3Bh, 0C7h, 8Bh, 0F1h, 74h, 11h, 0C7h, 46h
    db 08h, 54h, 0D0h, 11h, 01h, 0C7h, 86h, 1Ch, 01h, 00h, 00h, 0D8h, 0CDh, 09h, 01h, 57h
    db 8Bh, 0CEh, 0E8h, 0BBh, 36h, 98h, 0FFh, 8Bh, 46h, 08h, 0C7h, 06h, 0B8h, 0CFh, 11h, 01h
    db 0C7h, 46h, 04h, 0A4h, 0CFh, 11h, 01h, 8Bh, 48h, 04h, 0C7h, 44h, 31h, 08h, 8Ch, 0CFh
    db 11h, 01h, 8Bh, 56h, 08h, 8Bh, 42h, 04h, 33h, 0D2h, 8Dh, 88h, 0ECh, 0FEh, 0FFh, 0FFh
    db 89h, 4Ch, 30h, 04h, 89h, 0BEh, 00h, 01h, 00h, 00h, 89h, 0BEh, 04h, 01h, 00h, 00h
    db 89h, 0BEh, 08h, 01h, 00h, 00h, 89h, 0BEh, 0Ch, 01h, 00h, 00h, 89h, 96h, 80h, 00h
    db 00h, 00h, 89h, 96h, 84h, 00h, 00h, 00h, 89h, 96h, 88h, 00h, 00h, 00h, 89h, 96h
    db 8Ch, 00h, 00h, 00h, 89h, 96h, 90h, 00h, 00h, 00h, 89h, 96h, 94h, 00h, 00h, 00h
    db 89h, 96h, 98h, 00h, 00h, 00h, 89h, 96h, 9Ch, 00h, 00h, 00h, 89h, 96h, 0A0h, 00h
    db 00h, 00h, 89h, 96h, 0A4h, 00h, 00h, 00h, 89h, 96h, 0A8h, 00h, 00h, 00h, 89h, 96h
    db 0ACh, 00h, 00h, 00h, 89h, 96h, 0B0h, 00h, 00h, 00h, 89h, 96h, 0B4h, 00h, 00h, 00h
    db 89h, 96h, 0B8h, 00h, 00h, 00h, 89h, 96h, 0BCh, 00h, 00h, 00h, 89h, 96h, 0C0h, 00h
    db 00h, 00h, 89h, 96h, 0C4h, 00h, 00h, 00h, 89h, 96h, 0C8h, 00h, 00h, 00h, 89h, 96h
    db 0CCh, 00h, 00h, 00h, 89h, 96h, 0D0h, 00h, 00h, 00h, 89h, 96h, 0D4h, 00h, 00h, 00h
    db 89h, 96h, 0D8h, 00h, 00h, 00h, 89h, 96h, 0DCh, 00h, 00h, 00h, 89h, 96h, 0E0h, 00h
    db 00h, 00h, 89h, 96h, 0E4h, 00h, 00h, 00h, 89h, 96h, 0E8h, 00h, 00h, 00h, 89h, 96h
    db 0ECh, 00h, 00h, 00h, 89h, 96h, 0F0h, 00h, 00h, 00h, 89h, 96h, 0F4h, 00h, 00h, 00h
    db 89h, 96h, 0F8h, 00h, 00h, 00h, 89h, 96h, 0FCh, 00h, 00h, 00h, 89h, 0BEh, 04h, 01h
    db 00h, 00h, 89h, 0BEh, 0Ch, 01h, 00h, 00h, 89h, 0BEh, 08h, 01h, 00h, 00h, 89h, 0BEh
    db 00h, 01h, 00h, 00h, 89h, 0BEh, 10h, 01h, 00h, 00h, 89h, 0BEh, 14h, 01h, 00h, 00h
    db 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_006bcec0@@YAXXZ ENDP

; ghidra: FUN_00abd1a0  retail @ 0x006BD1A0 size 179
public ?d_006bd1a0@@YAXXZ
?d_006bd1a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 57h, 8Bh, 0F9h, 0Fh, 84h, 9Eh, 00h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 0ACh, 4Bh, 97h, 0FFh, 8Bh, 47h, 10h, 85h, 0C0h, 0Fh, 84h, 8Ch, 00h
    db 00h, 00h, 3Bh, 0C6h, 74h, 0Fh, 8Bh, 80h, 10h, 01h, 00h, 00h, 85h, 0C0h, 75h, 0F2h
    db 5Fh, 5Eh, 0C2h, 04h, 00h, 85h, 0C0h, 74h, 75h, 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 14h
    db 3Bh, 0C6h, 74h, 0Ch, 8Bh, 80h, 10h, 01h, 00h, 00h, 85h, 0C0h, 75h, 0F2h, 0EBh, 04h
    db 85h, 0C0h, 75h, 5Ah, 8Bh, 86h, 10h, 01h, 00h, 00h, 85h, 0C0h, 74h, 0Ch, 8Bh, 8Eh
    db 14h, 01h, 00h, 00h, 89h, 88h, 14h, 01h, 00h, 00h, 8Bh, 86h, 14h, 01h, 00h, 00h
    db 85h, 0C0h, 74h, 0Eh, 8Bh, 96h, 10h, 01h, 00h, 00h, 89h, 90h, 10h, 01h, 00h, 00h
    db 0EBh, 09h, 8Bh, 86h, 10h, 01h, 00h, 00h, 89h, 47h, 10h, 0C7h, 86h, 14h, 01h, 00h
    db 00h, 00h, 00h, 00h, 00h, 8Bh, 4Fh, 0Ch, 89h, 8Eh, 10h, 01h, 00h, 00h, 8Bh, 47h
    db 0Ch, 85h, 0C0h, 74h, 06h, 89h, 0B0h, 14h, 01h, 00h, 00h, 89h, 77h, 0Ch, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_006bd1a0@@YAXXZ ENDP

; ghidra: FUN_00abd280  retail @ 0x006BD280 size 203
public ?d_006bd280@@YAXXZ
?d_006bd280@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Ah, 46h, 08h, 84h, 0C0h, 0Fh, 85h
    db 93h, 00h, 00h, 00h, 8Ah, 46h, 09h, 84h, 0C0h, 0Fh, 85h, 88h, 00h, 00h, 00h, 8Bh
    db 46h, 0Ch, 85h, 0C0h, 74h, 0Bh, 8Bh, 88h, 10h, 01h, 00h, 00h, 89h, 4Eh, 0Ch, 0EBh
    db 2Ah, 68h, 20h, 01h, 00h, 00h, 0E8h, 65h, 4Ch, 1Ch, 00h, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 0Bh, 6Ah, 01h
    db 8Bh, 0C8h, 0E8h, 0DEh, 05h, 98h, 0FFh, 0EBh, 02h, 33h, 0C0h, 0C7h, 80h, 14h, 01h, 00h
    db 00h, 00h, 00h, 00h, 00h, 8Bh, 56h, 10h, 89h, 90h, 10h, 01h, 00h, 00h, 8Bh, 4Eh
    db 10h, 85h, 0C9h, 74h, 06h, 89h, 81h, 14h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h
    db 46h, 10h, 89h, 48h, 0Ch, 0C7h, 80h, 04h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 89h
    db 80h, 08h, 01h, 00h, 00h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh, 4Ch, 24h, 08h, 33h, 0C0h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_006bd280@@YAXXZ ENDP

; ghidra: FUN_00abd380  retail @ 0x006BD380 size 665
public ?d_006bd380@@YAXXZ
?d_006bd380@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 96h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 40h, 53h, 55h, 56h, 8Bh, 0D9h, 57h, 8Bh, 7Ch
    db 24h, 60h, 8Bh, 07h, 8Dh, 4Ch, 24h, 18h, 51h, 8Bh, 0CFh, 0C6h, 44h, 24h, 1Ch, 01h
    db 0C6h, 44h, 24h, 1Dh, 01h, 0FFh, 50h, 28h, 8Bh, 73h, 04h, 8Bh, 16h, 8Bh, 0CEh, 0FFh
    db 52h, 50h, 8Bh, 46h, 18h, 89h, 44h, 24h, 20h, 8Bh, 4Eh, 1Ch, 89h, 4Ch, 24h, 24h
    db 8Bh, 56h, 20h, 89h, 54h, 24h, 28h, 8Bh, 46h, 24h, 89h, 44h, 24h, 2Ch, 8Bh, 4Eh
    db 28h, 89h, 4Ch, 24h, 30h, 8Bh, 56h, 2Ch, 89h, 54h, 24h, 34h, 8Bh, 46h, 30h, 89h
    db 44h, 24h, 38h, 8Bh, 4Eh, 34h, 89h, 4Ch, 24h, 3Ch, 8Bh, 56h, 38h, 89h, 54h, 24h
    db 40h, 8Bh, 46h, 3Ch, 89h, 44h, 24h, 44h, 8Bh, 4Eh, 40h, 8Dh, 44h, 24h, 20h, 89h
    db 4Ch, 24h, 48h, 8Bh, 56h, 44h, 50h, 57h, 89h, 54h, 24h, 54h, 0E8h, 0F4h, 73h, 97h
    db 0FFh, 8Bh, 17h, 83h, 0C4h, 08h, 8Bh, 0CFh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 0Dh, 8Bh
    db 4Bh, 04h, 8Bh, 01h, 8Dh, 54h, 24h, 20h, 52h, 0FFh, 50h, 54h, 8Bh, 4Bh, 04h, 8Bh
    db 01h, 0FFh, 50h, 6Ch, 8Bh, 17h, 89h, 44h, 24h, 14h, 8Dh, 44h, 24h, 14h, 50h, 8Bh
    db 0CFh, 0FFh, 52h, 78h, 33h, 0EDh, 89h, 6Ch, 24h, 10h, 39h, 6Ch, 24h, 14h, 89h, 6Ch
    db 24h, 58h, 89h, 6Ch, 24h, 1Ch, 0Fh, 8Eh, 7Dh, 01h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 08h, 84h, 0C0h, 74h, 45h, 8Bh, 4Bh, 04h, 8Bh, 01h
    db 55h, 0FFh, 50h, 74h, 8Bh, 0F0h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 18h, 85h, 0C0h, 74h
    db 14h, 8Bh, 0C8h, 8Dh, 69h, 01h, 8Ah, 11h, 41h, 84h, 0D2h, 75h, 0F9h, 2Bh, 0CDh, 8Bh
    db 6Ch, 24h, 1Ch, 0EBh, 02h, 33h, 0C9h, 51h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 6Eh, 0A8h
    db 1Ch, 00h, 8Bh, 07h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CFh, 0FFh, 50h, 68h, 0EBh, 2Bh
    db 8Bh, 17h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CFh, 0FFh, 52h, 68h, 8Bh, 44h, 24h, 10h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 4Bh
    db 04h, 8Bh, 11h, 6Ah, 00h, 50h, 0FFh, 52h, 7Ch, 8Bh, 0F0h, 85h, 0F6h, 74h, 13h, 8Bh
    db 06h, 8Bh, 0CEh, 0FFh, 90h, 80h, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 95h, 0C1h, 88h, 4Ch
    db 24h, 60h, 8Bh, 17h, 8Dh, 44h, 24h, 60h, 50h, 8Bh, 0CFh, 0FFh, 92h, 8Ch, 00h, 00h
    db 00h, 85h, 0F6h, 74h, 7Ch, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 16h
    db 8Ah, 54h, 24h, 60h, 8Bh, 06h, 33h, 0C9h, 84h, 0D2h, 0Fh, 94h, 0C1h, 51h, 8Bh, 0CEh
    db 0FFh, 90h, 90h, 01h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 50h, 8Bh, 46h, 18h
    db 89h, 44h, 24h, 20h, 8Bh, 4Eh, 1Ch, 89h, 4Ch, 24h, 24h, 8Bh, 56h, 20h, 89h, 54h
    db 24h, 28h, 8Bh, 46h, 24h, 89h, 44h, 24h, 2Ch, 8Bh, 4Eh, 28h, 89h, 4Ch, 24h, 30h
    db 8Bh, 56h, 2Ch, 89h, 54h, 24h, 34h, 8Bh, 46h, 30h, 89h, 44h, 24h, 38h, 8Bh, 4Eh
    db 34h, 89h, 4Ch, 24h, 3Ch, 8Bh, 56h, 38h, 89h, 54h, 24h, 40h, 8Bh, 46h, 3Ch, 89h
    db 44h, 24h, 44h, 8Bh, 4Eh, 40h, 89h, 4Ch, 24h, 48h, 8Bh, 56h, 44h, 89h, 54h, 24h
    db 4Ch, 8Dh, 44h, 24h, 20h, 50h, 57h, 0E8h, 79h, 72h, 97h, 0FFh, 83h, 0C4h, 08h, 85h
    db 0F6h, 74h, 35h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 0Ch, 8Bh, 06h
    db 8Dh, 4Ch, 24h, 20h, 51h, 8Bh, 0CEh, 0FFh, 50h, 54h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h
    db 0Ch, 83h, 0F8h, 19h, 75h, 07h, 0C6h, 86h, 0F8h, 00h, 00h, 00h, 01h, 0FFh, 4Eh, 04h
    db 75h, 06h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 10h, 8Bh, 44h, 24h, 14h, 45h, 3Bh, 0E8h, 89h
    db 6Ch, 24h, 1Ch, 0Fh, 8Ch, 87h, 0FEh, 0FFh, 0FFh, 8Bh, 43h, 04h, 81h, 60h, 10h, 0FFh
    db 0FFh, 0DFh, 0FFh, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 58h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 3Ch, 0A3h, 1Ch, 00h, 8Bh, 4Ch, 24h, 50h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 04h, 00h
?d_006bd380@@YAXXZ ENDP

; ghidra: FUN_00abd6e0  retail @ 0x006BD6E0 size 840
_TEXT ENDS
_TEXT$d00abd6e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00ABD6E0 size 840
public ?d_006bd6e0@@YAXXZ
?d_006bd6e0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0104972B
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 028h, 055h, 056h, 08Bh, 074h, 024h, 040h, 08Bh, 0E9h, 056h, 089h, 06Ch, 024h, 020h
    call ?j_0003c1cd@@YAXXZ
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 010h, 084h, 0C0h, 00Fh, 085h, 0BCh, 002h, 000h, 000h, 08Bh
    db 016h, 0B0h, 001h, 088h, 044h, 024h, 020h, 088h, 044h, 024h, 021h, 057h, 08Dh, 044h, 024h, 024h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 028h, 08Dh, 085h, 000h, 001h, 000h, 000h, 050h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Dh, 085h, 00Ch, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 078h, 08Bh, 08Dh, 004h, 001h, 000h, 000h, 033h, 0FFh, 03Bh, 0CFh, 074h, 00Bh
    call ?j_00009b01@@YAXXZ
    db 089h, 044h, 024h, 014h, 0EBh, 004h, 089h, 07Ch, 024h, 014h, 08Dh, 04Ch, 024h, 014h, 051h, 056h
    call ?j_00008ca1@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 016h, 08Bh, 00Dh
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 08Bh, 054h, 024h, 014h, 08Bh, 001h, 052h, 0FFh, 050h, 02Ch, 089h, 085h, 004h, 001h, 000h, 000h
    db 089h, 07Ch, 024h, 028h, 08Dh, 0BDh, 080h, 000h, 000h, 000h, 089h, 07Ch, 024h, 024h, 053h, 08Bh
    db 007h, 085h, 0C0h, 0C6h, 044h, 024h, 048h, 000h, 074h, 00Bh, 0FEh, 044h, 024h, 048h, 08Bh, 040h
    db 008h, 085h, 0C0h, 075h, 0F5h, 08Bh, 006h, 08Dh, 04Ch, 024h, 048h, 051h, 08Bh, 0CEh, 0FFh, 090h
    db 084h, 000h, 000h, 000h, 08Ah, 044h, 024h, 048h, 084h, 0C0h, 075h, 009h, 083h, 03Fh, 000h, 00Fh
    db 085h, 00Bh, 002h, 000h, 000h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 08Bh, 016h, 08Bh
    db 0CEh, 0C7h, 044h, 024h, 040h, 000h, 000h, 000h, 000h, 0FFh, 052h, 008h, 084h, 0C0h, 00Fh, 084h
    db 083h, 000h, 000h, 000h, 08Bh, 03Fh, 085h, 0FFh, 00Fh, 084h, 06Fh, 001h, 000h, 000h, 08Bh, 04Fh
    db 004h, 08Bh, 001h, 0FFh, 050h, 018h, 085h, 0C0h, 074h, 014h, 08Bh, 0C8h, 08Dh, 069h, 001h, 08Ah
    db 011h, 041h, 084h, 0D2h, 075h, 0F9h, 02Bh, 0CDh, 08Bh, 06Ch, 024h, 024h, 0EBh, 002h, 033h, 0C9h
    db 051h, 050h, 08Dh, 04Ch, 024h, 01Ch
    call ?set@?$StringBase@D@@QAEXPBDH@Z
    db 08Bh, 016h, 08Dh, 044h, 024h, 014h, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 04Fh, 004h, 08Bh
    db 051h, 048h, 08Bh, 006h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CEh, 089h, 054h, 024h, 024h, 0FFh
    db 050h, 06Ch, 08Bh, 057h, 004h, 08Bh, 042h, 04Ch, 08Bh, 016h, 089h, 044h, 024h, 01Ch, 08Dh, 044h
    db 024h, 01Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh, 016h, 057h, 08Bh, 0CEh, 0FFh, 052h, 030h
    db 08Bh, 07Fh, 008h, 085h, 0FFh, 075h, 08Ch, 0E9h, 0F6h, 000h, 000h, 000h, 08Ah, 044h, 024h, 048h
    db 033h, 0DBh, 084h, 0C0h, 088h, 05Ch, 024h, 013h, 00Fh, 086h, 0E4h, 000h, 000h, 000h, 08Bh, 006h
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CEh, 0FFh, 050h, 068h, 08Bh, 016h, 08Dh, 044h, 024h, 020h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 016h, 08Dh, 044h, 024h, 01Ch, 050h, 08Bh, 0CEh, 0FFh
    db 052h, 074h, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 04Ch, 024h, 01Ch, 08Bh, 054h, 024h, 020h, 051h, 052h, 050h
    call ?Create_Render_Obj@@YAPAVRenderObjClass@@PBDMH@Z
    db 08Bh, 0E8h, 083h, 0C4h, 00Ch, 085h, 0EDh, 00Fh, 084h, 024h, 001h, 000h, 000h, 055h
    call ?j_00030576@@YAXXZ
    db 06Ah, 00Ch
    call ??2@YAPAXI@Z
    db 08Bh, 0F8h, 083h, 0C4h, 008h, 089h, 07Ch, 024h, 030h, 085h, 0FFh, 074h, 02Eh, 08Bh, 044h, 024h
    db 024h, 06Ah, 000h, 005h, 000h, 001h, 000h, 000h, 0C7h, 007h
    dd ??_7W3DRenderObjectSnapshot@@6B@
    db 0C7h, 047h, 008h, 000h, 000h, 000h, 000h, 089h, 06Fh, 004h, 08Bh, 055h, 000h, 050h, 08Bh, 0CDh
    db 0C6h, 044h, 024h, 048h, 002h, 0FFh, 092h, 054h, 001h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 085h
    db 0DBh, 0C6h, 044h, 024h, 040h, 000h, 074h, 005h, 089h, 07Bh, 008h, 0EBh, 006h, 08Bh, 044h, 024h
    db 028h, 089h, 038h, 08Bh, 016h, 057h, 08Bh, 0CEh, 08Bh, 0DFh, 0FFh, 052h, 030h, 08Bh, 00Dh
    dd ?Rva012F8058@@3PAVRva00712F60@@A
    db 08Bh, 057h, 004h, 08Bh, 001h, 052h, 0FFh, 050h, 008h, 08Ah, 044h, 024h, 013h, 08Ah, 04Ch, 024h
    db 048h, 0FEh, 0C0h, 03Ah, 0C1h, 088h, 044h, 024h, 013h, 00Fh, 082h, 020h, 0FFh, 0FFh, 0FFh, 08Bh
    db 06Ch, 024h, 024h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 040h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 044h, 024h, 02Ch, 08Bh, 07Ch, 024h, 028h, 040h, 083h, 0C7h, 004h, 083h, 0F8h, 020h, 089h
    db 044h, 024h, 02Ch, 089h, 07Ch, 024h, 028h, 00Fh, 08Ch, 004h, 0FEh, 0FFh, 0FFh, 08Bh, 045h, 00Ch
    db 085h, 0C0h, 074h, 029h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 051h, 00Ch, 08Bh, 042h, 024h, 08Bh, 08Ch, 085h, 080h, 000h, 000h, 000h, 085h, 0C9h, 074h
    db 012h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 007h, 08Bh, 0CDh
    call ?j_0000914c@@YAXXZ
    db 05Bh, 05Fh, 08Bh, 04Ch, 024h, 030h, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 034h, 0C2h, 004h, 000h, 06Ah, 000h, 08Dh, 044h, 024h, 034h, 06Ah, 004h, 050h
    call _bfmeFormatText
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_guardTargetTypeThrowInfo@@3HA
    db 08Dh, 04Ch, 024h, 034h, 051h
    call ?ji_009f6d00@@YAXXZ
    db 06Ah, 000h, 08Dh, 054h, 024h, 034h, 06Ah, 004h, 052h
    call _bfmeFormatText
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_guardTargetTypeThrowInfo@@3HA
    db 08Dh, 044h, 024h, 034h, 050h
    call ?ji_009f6d00@@YAXXZ
?d_006bd6e0@@YAXXZ ENDP
_TEXT$d00abd6e0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00abdb00  retail @ 0x006BDB00 size 54
public ?d_006bdb00@@YAXXZ
?d_006bdb00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 2Ah, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 48h, 0Ch, 85h, 0C9h, 75h, 0Eh, 8Bh, 48h, 7Ch, 85h, 0C9h, 74h, 07h, 0E8h, 9Dh
    db 0B0h, 23h, 00h, 0EBh, 08h, 50h, 8Bh, 0CEh, 0E8h, 16h, 65h, 94h, 0FFh, 8Bh, 46h, 10h
    db 85h, 0C0h, 75h, 0DCh, 5Eh, 0C3h
?d_006bdb00@@YAXXZ ENDP

; ghidra: FUN_00abe030  retail @ 0x006BE030 size 39
public ?d_006be030@@YAXXZ
?d_006be030@@YAXXZ PROC
    db 8Bh, 41h, 08h, 0Fh, 0AFh, 44h, 24h, 08h, 03h, 44h, 24h, 04h, 78h, 13h, 3Bh, 41h
    db 20h, 7Dh, 0Eh, 8Bh, 49h, 24h, 85h, 0C9h, 74h, 07h, 66h, 8Bh, 04h, 41h, 0C2h, 08h
    db 00h, 66h, 33h, 0C0h, 0C2h, 08h, 00h
?d_006be030@@YAXXZ ENDP

; ghidra: FUN_00abe070  retail @ 0x006BE070 size 46
public ?d_006be070@@YAXXZ
?d_006be070@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 27h, 82h, 98h, 0FFh, 33h, 0C0h, 89h, 86h, 0FCh, 18h, 00h, 00h
    db 89h, 46h, 0Ch, 0C7h, 06h, 90h, 0D0h, 11h, 01h, 0C7h, 46h, 04h, 64h, 0D0h, 11h, 01h
    db 0C7h, 86h, 00h, 19h, 00h, 00h, 00h, 00h, 80h, 3Fh, 8Bh, 0C6h, 5Eh, 0C3h
?d_006be070@@YAXXZ ENDP

; ghidra: FUN_00abe0c0  retail @ 0x006BE0C0 size 18
public ?d_006be0c0@@YAXXZ
?d_006be0c0@@YAXXZ PROC
    db 0C7h, 01h, 90h, 0D0h, 11h, 01h, 0C7h, 41h, 04h, 64h, 0D0h, 11h, 01h, 0E9h, 60h, 0ACh
    db 94h, 0FFh
?d_006be0c0@@YAXXZ ENDP

; ghidra: FUN_00abe0e0  retail @ 0x006BE0E0 size 34
public ?d_006be0e0@@YAXXZ
?d_006be0e0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0ACh, 98h, 96h, 0FFh, 33h, 0C0h, 89h, 46h, 0Ch, 89h, 46h, 10h
    db 89h, 86h, 0F8h, 18h, 00h, 00h, 0C7h, 86h, 0FCh, 18h, 00h, 00h, 00h, 00h, 80h, 3Fh
    db 5Eh, 0C3h
?d_006be0e0@@YAXXZ ENDP

; ghidra: FUN_00abe110  retail @ 0x006BE110 size 38
public ?d_006be110@@YAXXZ
?d_006be110@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0EFh, 0D5h, 95h, 0FFh, 33h, 0C0h, 89h, 46h, 0Ch, 89h, 46h, 10h
    db 89h, 86h, 0F8h, 18h, 00h, 00h, 0C7h, 86h, 0FCh, 18h, 00h, 00h, 00h, 00h, 80h, 3Fh
    db 5Eh, 0E9h, 0F1h, 8Fh, 98h, 0FFh
?d_006be110@@YAXXZ ENDP

; ghidra: FUN_00abe210  retail @ 0x006BE210 size 20
public ?d_006be210@@YAXXZ
?d_006be210@@YAXXZ PROC
    db 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 85h, 0C9h, 74h, 05h, 0E9h, 04h, 27h, 96h, 0FFh, 32h
    db 0C0h, 0C2h, 08h, 00h
?d_006be210@@YAXXZ ENDP

; ghidra: FUN_00abe2a0  retail @ 0x006BE2A0 size 267
public ?d_006be2a0@@YAXXZ
?d_006be2a0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 74h, 24h, 20h, 85h, 0F6h, 74h, 14h, 0C7h, 06h, 00h, 00h
    db 00h, 00h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0C7h, 46h, 08h, 00h, 00h, 80h, 3Fh
    db 0A1h, 0E0h, 7Fh, 2Fh, 01h, 85h, 0C0h, 75h, 0Dh, 0D9h, 05h, 50h, 53h, 07h, 01h, 5Eh
    db 83h, 0C4h, 0Ch, 0C2h, 14h, 00h, 53h, 8Bh, 5Ch, 24h, 1Ch, 55h, 8Bh, 6Ch, 24h, 1Ch
    db 57h, 8Bh, 7Ch, 24h, 28h, 83h, 0FFh, 01h, 0Fh, 84h, 0A6h, 00h, 00h, 00h, 83h, 0FFh
    db 10h, 8Bh, 0C5h, 8Bh, 0D3h, 89h, 44h, 24h, 10h, 89h, 54h, 24h, 14h, 0C7h, 44h, 24h
    db 18h, 00h, 00h, 00h, 00h, 7Ch, 1Eh, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 56h
    db 8Dh, 54h, 24h, 14h, 52h, 57h, 0E8h, 21h, 0BCh, 96h, 0FFh, 5Fh, 5Dh, 5Bh, 5Eh, 83h
    db 0C4h, 0Ch, 0C2h, 14h, 00h, 8Bh, 54h, 24h, 30h, 8Bh, 01h, 52h, 57h, 8Dh, 54h, 24h
    db 18h, 52h, 0FFh, 90h, 9Ch, 00h, 00h, 00h, 85h, 0C0h, 74h, 3Bh, 56h, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0C8h, 0E8h, 0B9h, 0D4h, 94h, 0FFh, 0D9h, 5Ch, 24h, 20h, 8Bh, 0Dh, 0E0h
    db 7Fh, 2Fh, 01h, 8Bh, 11h, 56h, 53h, 55h, 0FFh, 92h, 48h, 02h, 00h, 00h, 0D8h, 5Ch
    db 24h, 20h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 26h, 0D9h, 44h, 24h, 20h, 5Fh, 5Dh, 5Bh
    db 5Eh, 83h, 0C4h, 0Ch, 0C2h, 14h, 00h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 57h
    db 0E8h, 76h, 9Dh, 96h, 0FFh, 5Fh, 5Dh, 5Bh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 14h, 00h, 0A1h
    db 0E0h, 7Fh, 2Fh, 01h, 8Bh, 10h, 56h, 53h, 55h, 8Bh, 0C8h, 0FFh, 92h, 48h, 02h, 00h
    db 00h, 5Fh, 5Dh, 5Bh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 14h, 00h
?d_006be2a0@@YAXXZ ENDP

; ghidra: FUN_00abe400  retail @ 0x006BE400 size 11
public ?d_006be400@@YAXXZ
?d_006be400@@YAXXZ PROC
    db 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 0E9h, 7Ah, 08h, 97h, 0FFh
?d_006be400@@YAXXZ ENDP

; ghidra: FUN_00abe630  retail @ 0x006BE630 size 83
public ?d_006be630@@YAXXZ
?d_006be630@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 85h, 0C9h, 7Ch, 42h, 8Bh, 54h, 24h, 0Ch, 85h
    db 0D2h, 7Ch, 3Ah, 3Bh, 56h, 0Ch, 7Dh, 35h, 3Bh, 4Eh, 08h, 7Dh, 30h, 8Bh, 46h, 34h
    db 0Fh, 0AFh, 0C2h, 8Bh, 0D1h, 0C1h, 0FAh, 03h, 03h, 0C2h, 8Bh, 56h, 60h, 2Bh, 56h, 5Ch
    db 3Bh, 0C2h, 73h, 19h, 83h, 0E1h, 07h, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 8Bh, 4Eh
    db 5Ch, 8Ah, 04h, 08h, 5Eh, 84h, 0D0h, 0Fh, 95h, 0C0h, 0C2h, 08h, 00h, 32h, 0C0h, 5Eh
    db 0C2h, 08h, 00h
?d_006be630@@YAXXZ ENDP

; ghidra: FUN_00abe6a0  retail @ 0x006BE6A0 size 84
public ?d_006be6a0@@YAXXZ
?d_006be6a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 33h, 0D2h, 56h, 89h, 10h, 89h, 50h, 04h, 8Bh, 71h, 24h, 3Bh
    db 71h, 28h, 74h, 24h, 8Bh, 51h, 30h, 0DBh, 04h, 0D6h, 0D8h, 0Dh, 74h, 5Ch, 07h, 01h
    db 0D9h, 58h, 0Ch, 8Bh, 51h, 30h, 8Bh, 71h, 24h, 0DBh, 44h, 0D6h, 04h, 0D8h, 0Dh, 74h
    db 5Ch, 07h, 01h, 0D9h, 58h, 10h, 0EBh, 06h, 89h, 50h, 0Ch, 89h, 50h, 10h, 8Bh, 91h
    db 0FCh, 18h, 00h, 00h, 89h, 50h, 08h, 8Bh, 89h, 00h, 19h, 00h, 00h, 89h, 48h, 14h
    db 5Eh, 0C2h, 04h, 00h
?d_006be6a0@@YAXXZ ENDP

; ghidra: FUN_00abe710  retail @ 0x006BE710 size 171
public ?d_006be710@@YAXXZ
?d_006be710@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 33h, 0C0h, 57h, 8Bh, 7Ch, 24h, 14h, 89h, 07h, 89h, 47h, 04h
    db 8Bh, 51h, 24h, 3Bh, 51h, 28h, 74h, 73h, 8Bh, 0C2h, 0DBh, 00h, 0BEh, 01h, 00h, 00h
    db 00h, 0D9h, 5Ch, 24h, 08h, 0DBh, 40h, 04h, 8Bh, 41h, 28h, 2Bh, 0C2h, 0C1h, 0F8h, 03h
    db 3Bh, 0C6h, 76h, 3Fh, 83h, 0C2h, 08h, 0DBh, 02h, 0D8h, 54h, 24h, 08h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 06h, 0D9h, 5Ch, 24h, 08h, 0EBh, 02h, 0DDh, 0D8h, 0DBh, 42h, 04h, 0D9h
    db 54h, 24h, 14h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0DDh, 0D8h, 0D9h, 44h
    db 24h, 14h, 8Bh, 41h, 28h, 2Bh, 41h, 24h, 46h, 0C1h, 0F8h, 03h, 83h, 0C2h, 08h, 3Bh
    db 0F0h, 72h, 0C4h, 0D9h, 44h, 24h, 08h, 0D8h, 0Dh, 74h, 5Ch, 07h, 01h, 0D9h, 5Fh, 0Ch
    db 0D8h, 0Dh, 74h, 5Ch, 07h, 01h, 0D9h, 5Fh, 10h, 0EBh, 06h, 89h, 47h, 0Ch, 89h, 47h
    db 10h, 8Bh, 91h, 0FCh, 18h, 00h, 00h, 89h, 57h, 08h, 8Bh, 81h, 00h, 19h, 00h, 00h
    db 89h, 47h, 14h, 5Fh, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_006be710@@YAXXZ ENDP

; ghidra: FUN_00abe7f0  retail @ 0x006BE7F0 size 127
public ?d_006be7f0@@YAXXZ
?d_006be7f0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 56h, 33h, 0F6h, 89h, 32h, 89h, 72h, 04h, 89h, 72h, 0Ch, 89h
    db 72h, 10h, 8Bh, 41h, 28h, 2Bh, 41h, 24h, 0C1h, 0F8h, 03h, 85h, 0C0h, 76h, 4Ah, 90h
    db 8Bh, 41h, 24h, 0DBh, 04h, 0F0h, 0D8h, 0Dh, 74h, 5Ch, 07h, 01h, 0D8h, 52h, 0Ch, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 05h, 0D9h, 5Ah, 0Ch, 0EBh, 02h, 0DDh, 0D8h, 8Bh, 41h, 24h
    db 0DBh, 44h, 0F0h, 04h, 0D8h, 0Dh, 74h, 5Ch, 07h, 01h, 0D8h, 52h, 10h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 05h, 0D9h, 5Ah, 10h, 0EBh, 02h, 0DDh, 0D8h, 8Bh, 41h, 28h, 2Bh, 41h
    db 24h, 46h, 0C1h, 0F8h, 03h, 3Bh, 0F0h, 72h, 0B7h, 8Bh, 81h, 0FCh, 18h, 00h, 00h, 89h
    db 42h, 08h, 8Bh, 89h, 00h, 19h, 00h, 00h, 89h, 4Ah, 14h, 5Eh, 0C2h, 04h, 00h
?d_006be7f0@@YAXXZ ENDP

; ghidra: FUN_00abe890  retail @ 0x006BE890 size 239
public ?d_006be890@@YAXXZ
?d_006be890@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 2Ch, 0D9h, 0C0h, 8Bh, 44h, 24h
    db 10h, 0D8h, 00h, 0D9h, 5Ch, 24h, 10h, 0D8h, 40h, 04h, 0D9h, 44h, 24h, 10h, 0D8h, 1Dh
    db 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 0EBh, 1Eh, 0DBh, 46h, 10h, 0D8h, 0Dh, 74h, 5Ch, 07h, 01h, 0D9h, 44h
    db 24h, 10h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 5Ch, 24h, 10h, 0EBh
    db 02h, 0DDh, 0D8h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah
    db 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0EBh, 1Eh, 0DBh, 46h, 14h, 0D8h, 0Dh, 74h
    db 5Ch, 07h, 01h, 0D9h, 5Ch, 24h, 04h, 0D8h, 54h, 24h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 06h, 0DDh, 0D8h, 0D9h, 44h, 24h, 04h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h, 83h, 0ECh
    db 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 0D9h, 5Ch, 24h, 0Ch, 83h, 0C4h
    db 08h, 0D9h, 44h, 24h, 04h, 0DBh, 5Ch, 24h, 08h, 0D9h, 44h, 24h, 10h, 0D8h, 0Dh, 70h
    db 5Ch, 07h, 01h, 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 0D9h
    db 5Ch, 24h, 18h, 83h, 0C4h, 08h, 0D9h, 44h, 24h, 10h, 0DBh, 5Ch, 24h, 04h, 8Bh, 4Ch
    db 24h, 08h, 8Bh, 54h, 24h, 04h, 0A1h, 0E0h, 7Fh, 2Fh, 01h, 51h, 8Bh, 88h, 0F4h, 2Fh
    db 00h, 00h, 52h, 0E8h, 0C4h, 66h, 95h, 0FFh, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_006be890@@YAXXZ ENDP

; ghidra: FUN_00abe9c0  retail @ 0x006BE9C0 size 94
public ?d_006be9c0@@YAXXZ
?d_006be9c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 1Fh, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h
    db 50h, 76h, 0Ah, 0E8h, 58h, 35h, 1Ch, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 5Eh, 0FBh
    db 16h, 00h, 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Ch, 24h, 08h, 57h, 8Bh, 7Ch
    db 24h, 10h, 3Bh, 0CFh, 74h, 24h, 53h, 56h, 8Bh, 0F0h, 2Bh, 0F1h, 8Dh, 64h, 24h, 00h
    db 8Dh, 14h, 0Eh, 85h, 0D2h, 74h, 0Ah, 8Bh, 19h, 89h, 1Ah, 8Bh, 59h, 04h, 89h, 5Ah
    db 04h, 83h, 0C1h, 08h, 3Bh, 0CFh, 75h, 0E8h, 5Eh, 5Bh, 5Fh, 0C2h, 0Ch, 00h
?d_006be9c0@@YAXXZ ENDP

; ghidra: FUN_00abeb90  retail @ 0x006BEB90 size 607
public ?d_006beb90@@YAXXZ
?d_006beb90@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 96h, 97h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 14h, 02h, 00h, 00h, 53h, 55h, 56h, 57h, 8Bh
    db 0E9h, 0A1h, 94h, 15h, 2Fh, 01h, 33h, 0DBh, 3Bh, 0C3h, 89h, 9Ch, 24h, 2Ch, 02h, 00h
    db 00h, 0Fh, 84h, 0F4h, 01h, 00h, 00h, 8Bh, 84h, 24h, 34h, 02h, 00h, 00h, 3Bh, 0C3h
    db 8Dh, 48h, 08h, 75h, 05h, 0B9h, 8Bh, 38h, 07h, 01h, 8Dh, 54h, 24h, 1Ch, 8Bh, 0FFh
    db 8Ah, 01h, 41h, 88h, 02h, 42h, 3Ah, 0C3h, 75h, 0F6h, 8Dh, 44h, 24h, 1Ch, 8Dh, 50h
    db 01h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh, 0C2h, 8Bh, 0D0h, 83h, 0FAh, 04h, 7Ch
    db 2Ah, 33h, 0C0h, 0B9h, 41h, 00h, 00h, 00h, 8Dh, 0BCh, 24h, 20h, 01h, 00h, 00h, 0F3h
    db 0ABh, 83h, 0C2h, 0FCh, 52h, 8Dh, 44h, 24h, 20h, 50h, 8Dh, 8Ch, 24h, 28h, 01h, 00h
    db 00h, 51h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 8Bh, 0BCh, 24h, 38h, 02h
    db 00h, 00h, 8Bh, 17h, 53h, 8Bh, 0CFh, 0FFh, 52h, 08h, 68h, 0F0h, 20h, 01h, 00h, 0E8h
    db 0ECh, 32h, 1Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 3Bh, 0C3h, 0C6h, 84h, 24h
    db 2Ch, 02h, 00h, 00h, 01h, 74h, 0Eh, 6Ah, 01h, 57h, 8Bh, 0C8h, 0E8h, 42h, 30h, 94h
    db 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 3Bh, 0F3h, 88h, 9Ch, 24h, 2Ch, 02h, 00h, 00h
    db 0Fh, 84h, 45h, 01h, 00h, 00h, 8Bh, 46h, 08h, 89h, 45h, 10h, 8Bh, 46h, 0Ch, 89h
    db 45h, 14h, 8Dh, 46h, 14h, 50h, 8Dh, 4Dh, 24h, 0E8h, 12h, 0CBh, 97h, 0FFh, 8Bh, 45h
    db 14h, 33h, 0C9h, 3Bh, 0C3h, 89h, 5Dh, 30h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 00h, 00h
    db 89h, 5Ch, 24h, 18h, 89h, 4Ch, 24h, 10h, 7Eh, 6Ah, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 45h, 10h, 85h, 0C0h, 7Eh, 51h, 8Bh, 46h, 08h, 8Bh, 7Dh, 10h, 0Fh, 0AFh, 0C1h
    db 8Bh, 0C8h, 8Dh, 14h, 00h, 85h, 0C9h, 7Ch, 12h, 3Bh, 4Eh, 20h, 7Dh, 0Dh, 8Bh, 46h
    db 24h, 85h, 0C0h, 74h, 06h, 66h, 8Bh, 04h, 02h, 0EBh, 02h, 33h, 0C0h, 8Bh, 5Ch, 24h
    db 14h, 0Fh, 0B7h, 0C0h, 3Bh, 0C3h, 7Dh, 04h, 89h, 44h, 24h, 14h, 39h, 44h, 24h, 18h
    db 7Dh, 04h, 89h, 44h, 24h, 18h, 83h, 0C2h, 02h, 41h, 4Fh, 75h, 0C8h, 8Bh, 4Ch, 24h
    db 10h, 8Bh, 0BCh, 24h, 38h, 02h, 00h, 00h, 8Bh, 45h, 14h, 41h, 3Bh, 0C8h, 89h, 4Ch
    db 24h, 10h, 7Ch, 9Ch, 0DBh, 44h, 24h, 14h, 0D8h, 0Dh, 3Ch, 65h, 0Fh, 01h, 0D9h, 9Dh
    db 0FCh, 18h, 00h, 00h, 0DBh, 44h, 24h, 18h, 0D8h, 0Dh, 3Ch, 65h, 0Fh, 01h, 0D9h, 9Dh
    db 00h, 19h, 00h, 00h, 8Bh, 46h, 04h, 48h, 89h, 46h, 04h, 75h, 06h, 8Bh, 16h, 8Bh
    db 0CEh, 0FFh, 12h, 8Bh, 84h, 24h, 40h, 02h, 00h, 00h, 8Bh, 8Ch, 24h, 3Ch, 02h, 00h
    db 00h, 50h, 51h, 57h, 51h, 8Dh, 94h, 24h, 44h, 02h, 00h, 00h, 89h, 64h, 24h, 20h
    db 8Bh, 0CCh, 52h, 0E8h, 0F8h, 8Dh, 1Ch, 00h, 8Bh, 0CDh, 0E8h, 0FAh, 44h, 95h, 0FFh, 84h
    db 0C0h, 74h, 48h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Bh, 81h, 18h, 02h, 00h, 00h, 50h
    db 0E8h, 0DFh, 0CCh, 94h, 0FFh, 84h, 0C0h, 74h, 17h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Bh, 0Dh
    db 64h, 14h, 2Fh, 01h, 8Bh, 80h, 18h, 02h, 00h, 00h, 8Bh, 11h, 50h, 0FFh, 52h, 64h
    db 8Dh, 8Ch, 24h, 34h, 02h, 00h, 00h, 0C7h, 84h, 24h, 2Ch, 02h, 00h, 00h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 89h, 8Bh, 1Ch, 00h, 0B0h, 01h, 0EBh, 19h, 8Dh, 8Ch, 24h, 34h, 02h
    db 00h, 00h, 0C7h, 84h, 24h, 2Ch, 02h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 6Eh, 8Bh
    db 1Ch, 00h, 32h, 0C0h, 8Bh, 8Ch, 24h, 24h, 02h, 00h, 00h, 5Fh, 5Eh, 5Dh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 20h, 02h, 00h, 00h, 0C2h, 10h, 00h
?d_006beb90@@YAXXZ ENDP

; ghidra: FUN_00abee90  retail @ 0x006BEE90 size 63
public ?d_006bee90@@YAXXZ
?d_006bee90@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D8h, 05h, 34h, 53h, 07h, 01h, 0DAh, 4Ch, 24h, 14h, 0D8h, 0Dh
    db 3Ch, 53h, 07h, 01h, 0E8h, 8Fh, 7Fh, 33h, 00h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h
    db 64h, 24h, 08h, 8Bh, 4Ch, 24h, 0Ch, 0DAh, 4Ch, 24h, 18h, 89h, 01h, 0D8h, 0Dh, 3Ch
    db 53h, 07h, 01h, 0E8h, 70h, 7Fh, 33h, 00h, 8Bh, 54h, 24h, 10h, 89h, 02h, 0C3h
?d_006bee90@@YAXXZ ENDP

; ghidra: FUN_00abefc0  retail @ 0x006BEFC0 size 96
public ?d_006befc0@@YAXXZ
?d_006befc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 97h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 14h, 0E8h, 53h, 2Fh, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 0EDh, 0AFh, 94h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006befc0@@YAXXZ ENDP

; ghidra: FUN_00abf040  retail @ 0x006BF040 size 99
public ?d_006bf040@@YAXXZ
?d_006bf040@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 97h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 7Ch, 02h, 00h, 00h, 0E8h, 0D0h, 2Eh, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 69h
    db 95h, 96h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bf040@@YAXXZ ENDP

; ghidra: FUN_00abf0c0  retail @ 0x006BF0C0 size 110
public ?d_006bf0c0@@YAXXZ
?d_006bf0c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 68h, 5Ch, 01h, 00h, 00h, 0E8h, 4Fh, 2Eh, 1Ch
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 0A1h, 37h, 94h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 0Bh, 68h, 84h, 25h, 42h, 00h, 56h, 0E8h, 14h, 30h, 19h, 00h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf0c0@@YAXXZ ENDP

; ghidra: FUN_00abf150  retail @ 0x006BF150 size 96
public ?d_006bf150@@YAXXZ
?d_006bf150@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Bh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 5Ch, 0E8h, 0C3h, 2Dh, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 8Ah, 0F4h, 94h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf150@@YAXXZ ENDP

; ghidra: FUN_00abf260  retail @ 0x006BF260 size 99
public ?d_006bf260@@YAXXZ
?d_006bf260@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 7Bh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 7Ch, 02h, 00h, 00h, 0E8h, 0B0h, 2Ch, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 96h
    db 0C0h, 94h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bf260@@YAXXZ ENDP

; ghidra: FUN_00abf360  retail @ 0x006BF360 size 99
public ?d_006bf360@@YAXXZ
?d_006bf360@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BBh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 84h, 02h, 00h, 00h, 0E8h, 0B0h, 2Bh, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 0F9h
    db 3Ah, 98h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bf360@@YAXXZ ENDP

; ghidra: FUN_00abf3e0  retail @ 0x006BF3E0 size 110
public ?d_006bf3e0@@YAXXZ
?d_006bf3e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 68h, 60h, 01h, 00h, 00h, 0E8h, 2Fh, 2Bh, 1Ch
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 52h, 0F3h, 95h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 0Bh, 68h, 0CDh, 00h, 41h, 00h, 56h, 0E8h, 0F4h, 2Ch, 19h, 00h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf3e0@@YAXXZ ENDP

; ghidra: FUN_00abf470  retail @ 0x006BF470 size 99
public ?d_006bf470@@YAXXZ
?d_006bf470@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 98h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 0ECh, 03h, 00h, 00h, 0E8h, 0A0h, 2Ah, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 3Ah
    db 76h, 97h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bf470@@YAXXZ ENDP

; ghidra: FUN_00abf4f0  retail @ 0x006BF4F0 size 110
public ?d_006bf4f0@@YAXXZ
?d_006bf4f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 68h, 0C4h, 01h, 00h, 00h, 0E8h, 1Fh, 2Ah, 1Ch
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 44h, 6Ch, 97h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 0Bh, 68h, 33h, 0DFh, 42h, 00h, 56h, 0E8h, 0E4h, 2Bh, 19h, 00h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf4f0@@YAXXZ ENDP

; ghidra: FUN_00abf580  retail @ 0x006BF580 size 99
public ?d_006bf580@@YAXXZ
?d_006bf580@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Bh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 0F8h, 02h, 00h, 00h, 0E8h, 90h, 29h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 6Ch
    db 0D6h, 94h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bf580@@YAXXZ ENDP

; ghidra: FUN_00abf600  retail @ 0x006BF600 size 110
public ?d_006bf600@@YAXXZ
?d_006bf600@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Bh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 68h, 70h, 01h, 00h, 00h, 0E8h, 0Fh, 29h, 1Ch
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 16h, 0DEh, 97h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 0Bh, 68h, 0E3h, 0DAh, 41h, 00h, 56h, 0E8h, 0D4h, 2Ah, 19h, 00h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf600@@YAXXZ ENDP

; ghidra: FUN_00abf690  retail @ 0x006BF690 size 96
public ?d_006bf690@@YAXXZ
?d_006bf690@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 7Bh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 10h, 0E8h, 83h, 28h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 55h, 55h, 97h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf690@@YAXXZ ENDP

; ghidra: FUN_00abf7a0  retail @ 0x006BF7A0 size 96
public ?d_006bf7a0@@YAXXZ
?d_006bf7a0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BBh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 10h, 0E8h, 73h, 27h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 0F9h, 4Ch, 95h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf7a0@@YAXXZ ENDP

; ghidra: FUN_00abf820  retail @ 0x006BF820 size 107
public ?d_006bf820@@YAXXZ
?d_006bf820@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 10h, 0E8h, 0F2h, 26h, 1Ch, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h
    db 0Bh, 8Bh, 0C8h, 0E8h, 0A5h, 0FFh, 95h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 4Ch
    db 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 0Bh, 68h, 2Ch
    db 0ABh, 41h, 00h, 56h, 0E8h, 0B7h, 28h, 19h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf820@@YAXXZ ENDP

; ghidra: FUN_00abf8b0  retail @ 0x006BF8B0 size 96
public ?d_006bf8b0@@YAXXZ
?d_006bf8b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 99h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 10h, 0E8h, 63h, 26h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 80h, 9Eh, 97h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf8b0@@YAXXZ ENDP

; ghidra: FUN_00abf930  retail @ 0x006BF930 size 107
public ?d_006bf930@@YAXXZ
?d_006bf930@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 0Ch, 0E8h, 0E2h, 25h, 1Ch, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h
    db 0Bh, 8Bh, 0C8h, 0E8h, 0CEh, 0EDh, 95h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 4Ch
    db 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 0Bh, 68h, 0F0h
    db 0B7h, 43h, 00h, 56h, 0E8h, 0A7h, 27h, 19h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf930@@YAXXZ ENDP

; ghidra: FUN_00abf9c0  retail @ 0x006BF9C0 size 96
public ?d_006bf9c0@@YAXXZ
?d_006bf9c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Bh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 14h, 0E8h, 53h, 25h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 0D9h, 0AFh, 94h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bf9c0@@YAXXZ ENDP

; ghidra: FUN_00abfa40  retail @ 0x006BFA40 size 107
public ?d_006bfa40@@YAXXZ
?d_006bfa40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Bh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 14h, 0E8h, 0D2h, 24h, 1Ch, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h
    db 0Bh, 8Bh, 0C8h, 0E8h, 2Fh, 0B6h, 97h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 4Ch
    db 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 0Bh, 68h, 0AAh
    db 4Bh, 41h, 00h, 56h, 0E8h, 97h, 26h, 19h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bfa40@@YAXXZ ENDP

; ghidra: FUN_00abfb50  retail @ 0x006BFB50 size 107
public ?d_006bfb50@@YAXXZ
?d_006bfb50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 9Bh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 48h, 0E8h, 0C2h, 23h, 1Ch, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h
    db 0Bh, 8Bh, 0C8h, 0E8h, 16h, 92h, 96h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 4Ch
    db 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 0Bh, 68h, 0D9h
    db 0B5h, 43h, 00h, 56h, 0E8h, 87h, 25h, 19h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bfb50@@YAXXZ ENDP

; ghidra: FUN_00abfbe0  retail @ 0x006BFBE0 size 99
public ?d_006bfbe0@@YAXXZ
?d_006bfbe0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BBh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 88h, 02h, 00h, 00h, 0E8h, 30h, 23h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 55h
    db 87h, 94h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_006bfbe0@@YAXXZ ENDP

; ghidra: FUN_00abfc60  retail @ 0x006BFC60 size 110
public ?d_006bfc60@@YAXXZ
?d_006bfc60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 68h, 98h, 01h, 00h, 00h, 0E8h, 0AFh, 22h, 1Ch
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 0ECh, 74h, 97h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 0Bh, 68h, 79h, 71h, 42h, 00h, 56h, 0E8h, 74h, 24h, 19h, 00h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bfc60@@YAXXZ ENDP

; ghidra: FUN_00abfcf0  retail @ 0x006BFCF0 size 96
public ?d_006bfcf0@@YAXXZ
?d_006bfcf0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 9Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 14h, 0E8h, 23h, 22h, 1Ch, 00h, 83h, 0C4h, 04h
    db 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh, 0C8h, 0E8h, 0D4h, 1Ah, 97h, 0FFh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bfcf0@@YAXXZ ENDP

; ghidra: FUN_00abfd70  retail @ 0x006BFD70 size 107
public ?d_006bfd70@@YAXXZ
?d_006bfd70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 9Bh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 24h, 0E8h, 0A2h, 21h, 1Ch, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h
    db 0Bh, 8Bh, 0C8h, 0E8h, 44h, 05h, 97h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 4Ch
    db 24h, 18h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 0Bh, 68h, 0B6h
    db 0DAh, 41h, 00h, 56h, 0E8h, 67h, 23h, 19h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006bfd70@@YAXXZ ENDP

; ghidra: FUN_00abffe0  retail @ 0x006BFFE0 size 1136
public ?d_006bffe0@@YAXXZ
?d_006bffe0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 10h, 9Ch, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 57h, 8Bh, 0F1h, 0E8h, 0D9h, 38h, 96h
    db 0FFh, 68h, 8Ch, 49h, 09h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0B1h, 8Bh, 1Ch, 00h, 68h
    db 00h, 04h, 00h, 00h, 8Dh, 44h, 24h, 0Ch, 50h, 6Ah, 01h, 6Ah, 00h, 68h, 0FAh, 0F0h
    db 41h, 00h, 68h, 0BBh, 63h, 40h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 00h, 00h, 00h
    db 00h, 0E8h, 0C2h, 0Eh, 98h, 0FFh, 83h, 0CFh, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h
    db 18h, 0E8h, 0FAh, 78h, 1Ch, 00h, 68h, 0DCh, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h
    db 6Ch, 8Bh, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 4Ch, 24h, 0Ch, 51h, 6Ah, 01h
    db 6Ah, 00h, 68h, 0FAh, 0F0h, 41h, 00h, 68h, 0Bh, 23h, 40h, 00h, 8Bh, 0CEh, 0C7h, 44h
    db 24h, 30h, 01h, 00h, 00h, 00h, 0E8h, 7Dh, 0Eh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h
    db 7Ch, 24h, 18h, 0E8h, 0B8h, 78h, 1Ch, 00h, 68h, 0C0h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h
    db 0Ch, 0E8h, 2Ah, 8Bh, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h
    db 6Ah, 01h, 68h, 0FFh, 0DDh, 40h, 00h, 68h, 5Dh, 6Fh, 42h, 00h, 68h, 06h, 9Ah, 41h
    db 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 02h, 00h, 00h, 00h, 0E8h, 38h, 0Eh, 98h, 0FFh
    db 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 73h, 78h, 1Ch, 00h, 68h, 0A8h, 0D2h
    db 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0E5h, 8Ah, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h
    db 8Dh, 44h, 24h, 0Ch, 50h, 6Ah, 01h, 68h, 15h, 49h, 42h, 00h, 68h, 7Fh, 34h, 42h
    db 00h, 68h, 68h, 0F4h, 43h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 03h, 00h, 00h, 00h
    db 0E8h, 0F3h, 0Dh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 2Eh, 78h
    db 1Ch, 00h, 68h, 98h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0A0h, 8Ah, 1Ch, 00h
    db 68h, 00h, 04h, 00h, 00h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 1Ch, 04h, 00h, 00h
    db 00h, 51h, 6Ah, 01h, 6Ah, 00h, 68h, 3Fh, 0D0h, 40h, 00h, 68h, 0CEh, 98h, 43h, 00h
    db 8Bh, 0CEh, 0E8h, 0B1h, 0Dh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h
    db 0ECh, 77h, 1Ch, 00h, 68h, 84h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 5Eh, 8Ah
    db 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 6Ah, 01h, 68h, 0A0h
    db 5Bh, 40h, 00h, 68h, 33h, 0FDh, 42h, 00h, 68h, 22h, 82h, 42h, 00h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 30h, 05h, 00h, 00h, 00h, 0E8h, 6Ch, 0Dh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h
    db 89h, 7Ch, 24h, 18h, 0E8h, 0A7h, 77h, 1Ch, 00h, 68h, 74h, 0D2h, 11h, 01h, 8Dh, 4Ch
    db 24h, 0Ch, 0E8h, 19h, 8Ah, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 44h, 24h, 0Ch
    db 50h, 6Ah, 01h, 6Ah, 00h, 68h, 0FAh, 0F0h, 41h, 00h, 68h, 7Ch, 0B6h, 40h, 00h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 30h, 06h, 00h, 00h, 00h, 0E8h, 2Ah, 0Dh, 98h, 0FFh, 8Dh, 4Ch
    db 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 65h, 77h, 1Ch, 00h, 68h, 64h, 0D2h, 11h, 01h
    db 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0D7h, 89h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 4Ch
    db 24h, 0Ch, 51h, 6Ah, 01h, 68h, 22h, 17h, 44h, 00h, 68h, 0E8h, 5Eh, 40h, 00h, 68h
    db 33h, 57h, 43h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 07h, 00h, 00h, 00h, 0E8h, 0E5h
    db 0Ch, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 20h, 77h, 1Ch, 00h
    db 68h, 54h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 92h, 89h, 1Ch, 00h, 68h, 00h
    db 04h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 6Ah, 01h, 68h, 82h, 82h, 41h, 00h, 68h
    db 48h, 24h, 43h, 00h, 68h, 0E5h, 0B5h, 41h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 08h
    db 00h, 00h, 00h, 0E8h, 0A0h, 0Ch, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h
    db 0E8h, 0DBh, 76h, 1Ch, 00h, 68h, 44h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 4Dh
    db 89h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 44h, 24h, 0Ch, 50h, 6Ah, 01h, 68h
    db 73h, 0C3h, 41h, 00h, 68h, 0FAh, 4Ah, 42h, 00h, 68h, 44h, 04h, 44h, 00h, 8Bh, 0CEh
    db 0C7h, 44h, 24h, 30h, 09h, 00h, 00h, 00h, 0E8h, 5Bh, 0Ch, 98h, 0FFh, 8Dh, 4Ch, 24h
    db 08h, 89h, 7Ch, 24h, 18h, 0E8h, 96h, 76h, 1Ch, 00h, 68h, 34h, 0D2h, 11h, 01h, 8Dh
    db 4Ch, 24h, 0Ch, 0E8h, 08h, 89h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 4Ch, 24h
    db 0Ch, 51h, 6Ah, 01h, 68h, 0CCh, 0BDh, 43h, 00h, 68h, 53h, 77h, 44h, 00h, 68h, 0F7h
    db 0ABh, 43h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 0Ah, 00h, 00h, 00h, 0E8h, 16h, 0Ch
    db 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 51h, 76h, 1Ch, 00h, 68h
    db 24h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0C3h, 88h, 1Ch, 00h, 68h, 00h, 04h
    db 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 6Ah, 01h, 68h, 93h, 0B2h, 41h, 00h, 68h, 0D3h
    db 87h, 40h, 00h, 68h, 0A2h, 74h, 43h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 0Bh, 00h
    db 00h, 00h, 0E8h, 0D1h, 0Bh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h
    db 0Ch, 76h, 1Ch, 00h, 68h, 14h, 0D2h, 11h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 7Eh, 88h
    db 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 44h, 24h, 0Ch, 50h, 6Ah, 01h, 68h, 3Dh
    db 58h, 42h, 00h, 68h, 0E6h, 26h, 43h, 00h, 68h, 12h, 5Eh, 44h, 00h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 30h, 0Ch, 00h, 00h, 00h, 0E8h, 8Ch, 0Bh, 98h, 0FFh, 8Dh, 4Ch, 24h, 08h
    db 89h, 7Ch, 24h, 18h, 0E8h, 0C7h, 75h, 1Ch, 00h, 68h, 04h, 0D2h, 11h, 01h, 8Dh, 4Ch
    db 24h, 0Ch, 0E8h, 39h, 88h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 4Ch, 24h, 0Ch
    db 51h, 6Ah, 01h, 6Ah, 00h, 68h, 33h, 5Eh, 41h, 00h, 68h, 0B7h, 4Eh, 40h, 00h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 30h, 0Dh, 00h, 00h, 00h, 0E8h, 4Ah, 0Bh, 98h, 0FFh, 8Dh, 4Ch
    db 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 85h, 75h, 1Ch, 00h, 68h, 0F4h, 0D1h, 11h, 01h
    db 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0F7h, 87h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h, 8Dh, 54h
    db 24h, 0Ch, 52h, 6Ah, 01h, 6Ah, 00h, 68h, 0E6h, 3Dh, 40h, 00h, 68h, 3Ah, 82h, 43h
    db 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 0Eh, 00h, 00h, 00h, 0E8h, 08h, 0Bh, 98h, 0FFh
    db 8Dh, 4Ch, 24h, 08h, 89h, 7Ch, 24h, 18h, 0E8h, 43h, 75h, 1Ch, 00h, 68h, 0E4h, 0D1h
    db 11h, 01h, 8Dh, 4Ch, 24h, 10h, 0E8h, 0B5h, 87h, 1Ch, 00h, 68h, 00h, 04h, 00h, 00h
    db 8Dh, 44h, 24h, 10h, 50h, 6Ah, 01h, 6Ah, 00h, 68h, 74h, 49h, 42h, 00h, 68h, 0C1h
    db 91h, 43h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 0Fh, 00h, 00h, 00h, 0E8h, 0C6h, 0Ah
    db 98h, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 89h, 7Ch, 24h, 18h, 0E8h, 01h, 75h, 1Ch, 00h, 8Bh
    db 4Ch, 24h, 10h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_006bffe0@@YAXXZ ENDP

; ghidra: FUN_00ac0570  retail @ 0x006C0570 size 18
public ?d_006c0570@@YAXXZ
?d_006c0570@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0EAh, 0D2h, 96h, 0FFh, 0C7h, 06h, 0ECh, 0D2h, 11h, 01h, 8Bh, 0C6h
    db 5Eh, 0C3h
?d_006c0570@@YAXXZ ENDP

; ghidra: FUN_00ac0590  retail @ 0x006C0590 size 11
public ?d_006c0590@@YAXXZ
?d_006c0590@@YAXXZ PROC
    db 0C7h, 01h, 0ECh, 0D2h, 11h, 01h, 0E9h, 48h, 8Ch, 98h, 0FFh
?d_006c0590@@YAXXZ ENDP

; ghidra: FUN_00ac05f0  retail @ 0x006C05F0 size 11
public ?d_006c05f0@@YAXXZ
?d_006c05f0@@YAXXZ PROC
    db 0C7h, 01h, 40h, 0D7h, 11h, 01h, 0E9h, 68h, 81h, 96h, 0FFh
?d_006c05f0@@YAXXZ ENDP

; ghidra: FUN_00ac0600  retail @ 0x006C0600 size 52
public ?d_006c0600@@YAXXZ
?d_006c0600@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 70h, 5Ch, 97h, 0FFh, 6Ah, 03h, 68h, 50h, 0A4h, 2Bh, 01h, 8Bh
    db 0CEh, 0E8h, 67h, 9Dh, 97h, 0FFh, 6Ah, 08h, 68h, 28h, 7Fh, 2Fh, 01h, 8Bh, 0CEh, 0E8h
    db 59h, 9Dh, 97h, 0FFh, 6Ah, 05h, 68h, 34h, 7Fh, 2Fh, 01h, 8Bh, 0CEh, 0E8h, 4Bh, 9Dh
    db 97h, 0FFh, 5Eh, 0C3h
?d_006c0600@@YAXXZ ENDP

; ghidra: FUN_00ac07a0  retail @ 0x006C07A0 size 22
public ?d_006c07a0@@YAXXZ
?d_006c07a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Eh, 85h, 0C9h, 74h, 0Bh, 0E8h, 0F2h, 0AFh, 32h, 00h, 0C7h, 06h
    db 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_006c07a0@@YAXXZ ENDP

; ghidra: FUN_00ac0890  retail @ 0x006C0890 size 224
public ?d_006c0890@@YAXXZ
?d_006c0890@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Dh, 44h, 24h, 05h, 50h, 8Dh, 4Ch, 24h, 0Fh, 51h, 8Bh, 4Ch
    db 24h, 18h, 8Dh, 54h, 24h, 11h, 52h, 8Dh, 44h, 24h, 13h, 50h, 51h, 0E8h, 0D6h, 0B4h
    db 95h, 0FFh, 8Dh, 54h, 24h, 18h, 52h, 8Dh, 44h, 24h, 22h, 50h, 8Bh, 44h, 24h, 30h
    db 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 54h, 24h, 26h, 52h, 50h, 0E8h, 0B8h, 0B4h, 95h, 0FFh
    db 0Fh, 0B6h, 54h, 24h, 2Dh, 0Fh, 0B6h, 4Ch, 24h, 2Ch, 0Fh, 0AFh, 0CAh, 0Fh, 0B6h, 74h
    db 24h, 2Eh, 0B8h, 81h, 80h, 80h, 80h, 0F7h, 0E9h, 03h, 0D1h, 0C1h, 0FAh, 07h, 8Bh, 0C2h
    db 0C1h, 0E8h, 1Fh, 03h, 0C2h, 0Fh, 0B6h, 54h, 24h, 2Fh, 0Fh, 0AFh, 0F2h, 33h, 0C9h, 8Ah
    db 0E8h, 0B8h, 81h, 80h, 80h, 80h, 0F7h, 0EEh, 03h, 0D6h, 0Fh, 0B6h, 74h, 24h, 30h, 0C1h
    db 0FAh, 07h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 0Fh, 0B6h, 54h, 24h, 31h, 0Fh, 0AFh
    db 0F2h, 8Ah, 0C8h, 0B8h, 81h, 80h, 80h, 80h, 0F7h, 0EEh, 03h, 0D6h, 0Fh, 0B6h, 74h, 24h
    db 32h, 0C1h, 0FAh, 07h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 0Fh, 0B6h, 0D0h, 0Fh, 0B6h
    db 44h, 24h, 33h, 0Fh, 0AFh, 0F0h, 0C1h, 0E1h, 08h, 0Bh, 0CAh, 0B8h, 81h, 80h, 80h, 80h
    db 0F7h, 0EEh, 03h, 0D6h, 0C1h, 0FAh, 07h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 0Fh, 0B6h
    db 0D0h, 83h, 0C4h, 28h, 0C1h, 0E1h, 08h, 0Bh, 0CAh, 8Bh, 0C1h, 5Eh, 83h, 0C4h, 08h, 0C3h
?d_006c0890@@YAXXZ ENDP

; ghidra: FUN_00ac09b0  retail @ 0x006C09B0 size 58
public ?d_006c09b0@@YAXXZ
?d_006c09b0@@YAXXZ PROC
    db 8Bh, 03h, 56h, 57h, 33h, 0FFh, 85h, 0C0h, 74h, 25h, 8Bh, 0C3h, 8Bh, 0F3h, 8Bh, 0FFh
    db 8Bh, 00h, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 50h, 0E8h, 22h, 0ABh, 25h, 00h, 84h, 0C0h
    db 75h, 12h, 8Bh, 4Eh, 04h, 83h, 0C6h, 04h, 47h, 85h, 0C9h, 8Bh, 0C6h, 75h, 0E1h, 5Fh
    db 33h, 0C0h, 5Eh, 0C3h, 8Bh, 04h, 0BBh, 5Fh, 5Eh, 0C3h
?d_006c09b0@@YAXXZ ENDP

; ghidra: FUN_00ac0a00  retail @ 0x006C0A00 size 157
public ?d_006c0a00@@YAXXZ
?d_006c0a00@@YAXXZ PROC
    db 83h, 0ECh, 38h, 53h, 33h, 0C0h, 56h, 0BAh, 15h, 00h, 00h, 00h, 8Bh, 0F1h, 0B9h, 1Ah
    db 00h, 00h, 00h, 8Dh, 5Ch, 24h, 2Ch, 0C7h, 44h, 24h, 2Ch, 14h, 00h, 00h, 00h, 0C7h
    db 44h, 24h, 30h, 16h, 00h, 00h, 00h, 0C7h, 44h, 24h, 34h, 17h, 00h, 00h, 00h, 0C7h
    db 44h, 24h, 38h, 18h, 00h, 00h, 00h, 89h, 44h, 24h, 3Ch, 89h, 54h, 24h, 08h, 89h
    db 4Ch, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h, 54h, 24h, 14h, 89h, 4Ch, 24h, 18h, 89h
    db 44h, 24h, 1Ch, 89h, 54h, 24h, 20h, 89h, 4Ch, 24h, 24h, 89h, 44h, 24h, 28h, 0E8h
    db 4Ch, 0FFh, 0FFh, 0FFh, 8Dh, 5Ch, 24h, 08h, 89h, 86h, 70h, 14h, 00h, 00h, 0E8h, 3Dh
    db 0FFh, 0FFh, 0FFh, 8Dh, 5Ch, 24h, 14h, 89h, 86h, 80h, 14h, 00h, 00h, 0E8h, 2Eh, 0FFh
    db 0FFh, 0FFh, 8Dh, 5Ch, 24h, 20h, 89h, 86h, 8Ch, 14h, 00h, 00h, 0E8h, 1Fh, 0FFh, 0FFh
    db 0FFh, 89h, 86h, 98h, 14h, 00h, 00h, 5Eh, 5Bh, 83h, 0C4h, 38h, 0C3h
?d_006c0a00@@YAXXZ ENDP

; ghidra: FUN_00ac0ad0  retail @ 0x006C0AD0 size 235
public ?d_006c0ad0@@YAXXZ
?d_006c0ad0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 8Eh, 78h, 14h, 00h, 00h, 33h, 0DBh, 3Bh, 0CBh, 57h, 74h
    db 0Bh, 0E8h, 0BAh, 0ACh, 32h, 00h, 89h, 9Eh, 78h, 14h, 00h, 00h, 8Bh, 8Eh, 74h, 14h
    db 00h, 00h, 3Bh, 0CBh, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 89h, 9Eh, 74h, 14h
    db 00h, 00h, 8Bh, 8Eh, 88h, 14h, 00h, 00h, 3Bh, 0CBh, 74h, 0Bh, 0E8h, 8Fh, 0ACh, 32h
    db 00h, 89h, 9Eh, 88h, 14h, 00h, 00h, 8Bh, 8Eh, 84h, 14h, 00h, 00h, 3Bh, 0CBh, 74h
    db 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h, 9Eh, 84h, 14h, 00h, 00h, 8Bh, 8Eh, 94h
    db 14h, 00h, 00h, 3Bh, 0CBh, 74h, 0Bh, 0E8h, 64h, 0ACh, 32h, 00h, 89h, 9Eh, 94h, 14h
    db 00h, 00h, 8Bh, 8Eh, 90h, 14h, 00h, 00h, 3Bh, 0CBh, 74h, 06h, 8Bh, 01h, 6Ah, 01h
    db 0FFh, 10h, 89h, 9Eh, 90h, 14h, 00h, 00h, 8Bh, 8Eh, 0A0h, 14h, 00h, 00h, 3Bh, 0CBh
    db 74h, 0Bh, 0E8h, 39h, 0ACh, 32h, 00h, 89h, 9Eh, 0A0h, 14h, 00h, 00h, 8Bh, 8Eh, 9Ch
    db 14h, 00h, 00h, 3Bh, 0CBh, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h, 9Eh, 9Ch
    db 14h, 00h, 00h, 8Bh, 8Eh, 7Ch, 14h, 00h, 00h, 3Bh, 0CBh, 74h, 0Bh, 0E8h, 0Eh, 0ACh
    db 32h, 00h, 89h, 9Eh, 7Ch, 14h, 00h, 00h, 81h, 0C6h, 0B0h, 14h, 00h, 00h, 0BFh, 0Bh
    db 00h, 00h, 00h, 8Bh, 0Eh, 3Bh, 0CBh, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 89h
    db 1Eh, 83h, 0C6h, 04h, 4Fh, 75h, 0ECh, 5Fh, 5Eh, 5Bh, 0C3h
?d_006c0ad0@@YAXXZ ENDP

; ghidra: FUN_00ac0c00  retail @ 0x006C0C00 size 574
public ?d_006c0c00@@YAXXZ
?d_006c0c00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 66h, 9Ch, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 60h, 53h, 56h, 68h, 4Ch, 36h, 41h, 00h, 68h
    db 93h, 6Ch, 41h, 00h, 6Ah, 04h, 6Ah, 0Ch, 8Dh, 44h, 24h, 48h, 50h, 8Bh, 0F1h, 0E8h
    db 0B0h, 62h, 33h, 00h, 68h, 0B8h, 0EAh, 43h, 00h, 68h, 10h, 17h, 42h, 00h, 6Ah, 04h
    db 6Ah, 08h, 8Dh, 4Ch, 24h, 28h, 33h, 0DBh, 51h, 89h, 9Ch, 24h, 84h, 00h, 00h, 00h
    db 0E8h, 8Fh, 62h, 33h, 00h, 8Bh, 56h, 18h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 8Bh, 01h
    db 52h, 89h, 54h, 24h, 0Ch, 8Dh, 54h, 24h, 60h, 52h, 8Dh, 54h, 24h, 58h, 52h, 8Dh
    db 54h, 24h, 50h, 52h, 8Dh, 54h, 24h, 48h, 52h, 0C6h, 84h, 24h, 84h, 00h, 00h, 00h
    db 01h, 0FFh, 50h, 34h, 0D9h, 86h, 48h, 14h, 00h, 00h, 0D8h, 0A6h, 3Ch, 14h, 00h, 00h
    db 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D8h, 7Ch, 24h, 38h, 0D9h, 5Ch, 24h, 18h, 0D9h, 86h
    db 4Ch, 14h, 00h, 00h, 0D8h, 0A6h, 40h, 14h, 00h, 00h, 89h, 9Eh, 0E8h, 14h, 00h, 00h
    db 89h, 9Eh, 0ECh, 14h, 00h, 00h, 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D8h, 7Ch, 24h, 3Ch
    db 0D9h, 5Ch, 24h, 1Ch, 0D9h, 86h, 48h, 14h, 00h, 00h, 0D8h, 0A6h, 3Ch, 14h, 00h, 00h
    db 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D8h, 7Ch, 24h, 44h, 0D9h, 5Ch, 24h, 20h, 0D9h, 86h
    db 4Ch, 14h, 00h, 00h, 0D8h, 0A6h, 40h, 14h, 00h, 00h, 0D8h, 0Dh, 0F4h, 88h, 08h, 01h
    db 0D8h, 7Ch, 24h, 48h, 0D9h, 5Ch, 24h, 24h, 0D9h, 44h, 24h, 20h, 0D8h, 64h, 24h, 18h
    db 0D9h, 9Eh, 0F0h, 14h, 00h, 00h, 0D9h, 44h, 24h, 24h, 0D8h, 64h, 24h, 1Ch, 0D9h, 9Eh
    db 0F4h, 14h, 00h, 00h, 0D9h, 86h, 48h, 14h, 00h, 00h, 0D8h, 0A6h, 3Ch, 14h, 00h, 00h
    db 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D8h, 7Ch, 24h, 50h, 0D9h, 5Ch, 24h, 28h, 0D9h, 86h
    db 4Ch, 14h, 00h, 00h, 0D8h, 0A6h, 40h, 14h, 00h, 00h, 0D8h, 0Dh, 0F4h, 88h, 08h, 01h
    db 0D8h, 7Ch, 24h, 54h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 44h, 24h, 28h, 0D8h, 64h, 24h, 20h
    db 0D9h, 9Eh, 0F8h, 14h, 00h, 00h, 0D9h, 44h, 24h, 2Ch, 0D8h, 64h, 24h, 24h, 0D9h, 9Eh
    db 0FCh, 14h, 00h, 00h, 0D9h, 86h, 48h, 14h, 00h, 00h, 0D8h, 0A6h, 3Ch, 14h, 00h, 00h
    db 0D8h, 0Dh, 0F4h, 88h, 08h, 01h, 0D8h, 7Ch, 24h, 5Ch, 0D9h, 5Ch, 24h, 30h, 0D9h, 86h
    db 4Ch, 14h, 00h, 00h, 0D8h, 0A6h, 40h, 14h, 00h, 00h, 0D8h, 0Dh, 0F4h, 88h, 08h, 01h
    db 0D8h, 7Ch, 24h, 60h, 0D9h, 5Ch, 24h, 34h, 0D9h, 44h, 24h, 30h, 0D8h, 64h, 24h, 28h
    db 0D9h, 9Eh, 00h, 15h, 00h, 00h, 0D9h, 44h, 24h, 34h, 0D8h, 64h, 24h, 2Ch, 0D9h, 9Eh
    db 04h, 15h, 00h, 00h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 8Bh, 01h, 0FFh, 90h, 0FCh, 00h
    db 00h, 00h, 0D9h, 9Eh, 0E0h, 14h, 00h, 00h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 8Bh, 11h
    db 8Dh, 44h, 24h, 0Ch, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 00h, 16h, 2Fh
    db 01h, 8Bh, 11h, 0FFh, 92h, 20h, 01h, 00h, 00h, 0D9h, 9Eh, 0E4h, 14h, 00h, 00h, 68h
    db 0B8h, 0EAh, 43h, 00h, 6Ah, 04h, 6Ah, 08h, 8Dh, 44h, 24h, 24h, 50h, 88h, 9Eh, 0DCh
    db 14h, 00h, 00h, 88h, 9Ch, 24h, 80h, 00h, 00h, 00h, 0E8h, 67h, 5Fh, 33h, 00h, 68h
    db 4Ch, 36h, 41h, 00h, 6Ah, 04h, 6Ah, 0Ch, 8Dh, 4Ch, 24h, 44h, 51h, 0C7h, 84h, 24h
    db 80h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 49h, 5Fh, 33h, 00h, 8Bh, 4Ch, 24h
    db 68h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 6Ch, 0C3h
?d_006c0c00@@YAXXZ ENDP
_TEXT ENDS
END
