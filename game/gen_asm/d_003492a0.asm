.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@@_STL@@QAE@XZ:NEAR
EXTERN ??1SubsystemInterface@@UAE@XZ:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_7?$BasicTimerClass@VSystemTimerClass@@@@6B@:BYTE
EXTERN ??_7BfmeDualVtableReleaseDtor@@6B@:BYTE
EXTERN ??_7BfmeOwnVUQ@@6B@:BYTE
EXTERN ??_7Rva0033C070TailDtor@@6B@:BYTE
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:NEAR
EXTERN ?BfmeDefeatScreenTable@@3PAEA:BYTE
EXTERN ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A:BYTE
EXTERN ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A:BYTE
EXTERN ?TheScriptDebugWindowDLL@@3PAXA:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?g_rva00339a80Node@@3PAVRva00339A80ParticleNode@@A:BYTE
EXTERN ?g_rva00339a80Sink@@3PAVRva00339A80ParticleSink@@A:BYTE
EXTERN ?j_000035d5@@YAXXZ:NEAR
EXTERN ?j_00003747@@YAXXZ:NEAR
EXTERN ?j_00003a44@@YAXXZ:NEAR
EXTERN ?j_00005277@@YAXXZ:NEAR
EXTERN ?j_00005a56@@YAXXZ:NEAR
EXTERN ?j_0000a20e@@YAXXZ:NEAR
EXTERN ?j_0000ce50@@YAXXZ:NEAR
EXTERN ?j_0000d152@@YAXXZ:NEAR
EXTERN ?j_0000f74f@@YAXXZ:NEAR
EXTERN ?j_0001053c@@YAXXZ:NEAR
EXTERN ?j_000183bd@@YAXXZ:NEAR
EXTERN ?j_0001900b@@YAXXZ:NEAR
EXTERN ?j_000191af@@YAXXZ:NEAR
EXTERN ?j_0001af00@@YAXXZ:NEAR
EXTERN ?j_0001cd7d@@YAXXZ:NEAR
EXTERN ?j_00020ba3@@YAXXZ:NEAR
EXTERN ?j_000220c5@@YAXXZ:NEAR
EXTERN ?j_0002240d@@YAXXZ:NEAR
EXTERN ?j_00024b81@@YAXXZ:NEAR
EXTERN ?j_000268f5@@YAXXZ:NEAR
EXTERN ?j_0002720f@@YAXXZ:NEAR
EXTERN ?j_0002842f@@YAXXZ:NEAR
EXTERN ?j_00028ce0@@YAXXZ:NEAR
EXTERN ?j_00029b6d@@YAXXZ:NEAR
EXTERN ?j_0003263c@@YAXXZ:NEAR
EXTERN ?j_00034f72@@YAXXZ:NEAR
EXTERN ?j_00036336@@YAXXZ:NEAR
EXTERN ?j_0003de8d@@YAXXZ:NEAR
EXTERN ?j_00040a39@@YAXXZ:NEAR
EXTERN ?j_000444ea@@YAXXZ:NEAR
EXTERN ?j_00044c2e@@YAXXZ:NEAR
EXTERN ?j_0004772b@@YAXXZ:NEAR
EXTERN ?j_00047b59@@YAXXZ:NEAR
EXTERN ?j_0004B01A@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN __imp__FreeLibrary@4:BYTE
EXTERN __imp__GetProcAddress@8:BYTE
EXTERN g_Va0101894B:NEAR
EXTERN g_Va01019158:NEAR
EXTERN g_Va010E1FD0:BYTE
EXTERN g_Va010E7A18:BYTE
EXTERN g_Va010E7A30:BYTE
EXTERN g_Va010E7C38:BYTE
EXTERN g_Va010E7F50:BYTE
EXTERN g_Va012F0774:BYTE
EXTERN g_Va012F0788:BYTE
_TEXT SEGMENT

; ghidra: FUN_007492a0  retail @ 0x003492A0 size 928
_TEXT ENDS
_TEXT$d007492a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007492A0 size 928
public ?d_003492a0@@YAXXZ
?d_003492a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0101894B
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 014h, 053h, 056h, 08Bh, 0F1h, 057h, 089h, 074h, 024h, 010h, 0C7h, 006h
    dd g_Va010E7A30
    db 0C7h, 046h, 008h
    dd g_Va010E7A18
    db 08Bh, 00Dh
    dd ?g_rva00339a80Sink@@3PAVRva00339A80ParticleSink@@A
    db 0A1h
    dd g_Va012F0774
    db 033h, 0DBh, 089h, 04Ch, 024h, 01Ch, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 028h, 01Ah, 000h
    db 000h, 000h, 089h, 01Dh
    dd ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A
    db 0C7h, 044h, 024h, 014h
    dd ??_7BfmeDualVtableReleaseDtor@@6B@
    db 089h, 044h, 024h, 018h, 089h, 01Dh
    dd g_Va012F0774
    db 089h, 01Dh
    dd ?g_rva00339a80Sink@@3PAVRva00339A80ParticleSink@@A
    call ?j_0002842f@@YAXXZ
    db 08Bh, 00Dh
    dd ?g_rva00339a80Node@@3PAVRva00339A80ParticleNode@@A
    db 03Bh, 0CBh, 08Bh, 0F9h, 074h, 014h, 0C7h, 001h
    dd ??_7Rva0033C070TailDtor@@6B@
    call ?j_00020ba3@@YAXXZ
    db 057h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0A1h
    dd ?TheScriptDebugWindowDLL@@3PAXA
    db 03Bh, 0C3h, 089h, 01Dh
    dd ?g_rva00339a80Node@@3PAVRva00339A80ParticleNode@@A
    db 074h, 025h, 068h
    dd g_Va010E7C38
    db 050h, 0FFh, 015h
    dd __imp__GetProcAddress@8
    db 03Bh, 0C3h, 074h, 002h, 0FFh, 0D0h, 08Bh, 015h
    dd ?TheScriptDebugWindowDLL@@3PAXA
    db 052h, 0FFh, 015h
    dd __imp__FreeLibrary@4
    db 089h, 01Dh
    dd ?TheScriptDebugWindowDLL@@3PAXA
    db 08Bh, 0CEh
    call ?j_0000ce50@@YAXXZ
    db 08Bh, 08Eh, 028h, 076h, 001h, 000h, 03Bh, 0CBh, 0C6h, 044h, 024h, 028h, 019h, 074h, 02Ah, 08Bh
    db 086h, 030h, 076h, 001h, 000h, 02Bh, 0C1h, 0C1h, 0F8h, 002h, 0C1h, 0E0h, 002h, 03Dh, 080h, 000h
    db 000h, 000h, 076h, 00Bh, 051h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0EBh, 00Ah, 050h, 051h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Dh, 08Eh, 0F8h, 075h, 001h, 000h, 0C6h, 044h, 024h, 028h, 018h
    call ?j_0004772b@@YAXXZ
    db 08Dh, 0BEh, 0F4h, 075h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 017h
    call ?j_0002240d@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 018h, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 068h
    dd ?j_00005277@@YAXXZ
    db 06Ah, 020h, 06Ah, 00Ch, 08Dh, 086h, 074h, 074h, 001h, 000h, 050h, 0C6h, 044h, 024h, 038h, 016h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 068h
    dd ?j_000183bd@@YAXXZ
    db 06Ah, 020h, 06Ah, 004h, 08Dh, 08Eh, 0F4h, 073h, 001h, 000h, 051h, 0C6h, 044h, 024h, 038h, 015h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 068h
    dd ?j_000183bd@@YAXXZ
    db 06Ah, 020h, 06Ah, 004h, 08Dh, 096h, 074h, 073h, 001h, 000h, 052h, 0C6h, 044h, 024h, 038h, 014h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 068h
    dd ?j_000183bd@@YAXXZ
    db 06Ah, 020h, 06Ah, 004h, 08Dh, 086h, 0F4h, 072h, 001h, 000h, 050h, 0C6h, 044h, 024h, 038h, 013h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 068h
    dd ?j_000183bd@@YAXXZ
    db 06Ah, 020h, 06Ah, 004h, 08Dh, 08Eh, 074h, 072h, 001h, 000h, 051h, 0C6h, 044h, 024h, 038h, 012h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 08Dh, 0BEh, 070h, 072h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 011h
    call ?j_0001900b@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 00Ch, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Dh, 0BEh, 06Ch, 072h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 010h
    call ?j_0001900b@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 00Ch, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Dh, 0BEh, 068h, 072h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 00Fh
    call ?j_000191af@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 010h, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Dh, 0BEh, 064h, 072h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 00Eh
    call ?j_000191af@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 010h, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Dh, 0BEh, 060h, 072h, 001h, 000h, 08Bh, 0CFh, 0C6h, 044h, 024h, 028h, 00Dh
    call ?j_0001900b@@YAXXZ
    db 08Bh, 03Fh, 03Bh, 0FBh, 074h, 00Bh, 06Ah, 00Ch, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 068h
    dd ?j_0001af00@@YAXXZ
    db 06Ah, 020h, 06Ah, 00Ch, 08Dh, 096h, 0E0h, 070h, 001h, 000h, 052h, 0C6h, 044h, 024h, 038h, 00Ch
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 08Dh, 08Eh, 09Ch, 070h, 001h, 000h, 0C6h, 044h, 024h, 028h, 00Bh
    call ?j_000035d5@@YAXXZ
    db 08Dh, 08Eh, 088h, 070h, 001h, 000h, 0C6h, 044h, 024h, 028h, 00Ah
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 068h
    dd ?j_000268f5@@YAXXZ
    db 068h, 000h, 001h, 000h, 000h, 06Ah, 010h, 08Dh, 086h, 07Ch, 060h, 001h, 000h, 050h, 0C6h, 044h
    db 024h, 038h, 009h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 08Dh, 08Eh, 070h, 060h, 001h, 000h, 0C6h, 044h, 024h, 028h, 008h
    call ??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@_N@_STL@@@3@@_STL@@QAE@XZ
    db 08Dh, 08Eh, 064h, 060h, 001h, 000h, 0C6h, 044h, 024h, 028h, 007h
    call ?j_0000d152@@YAXXZ
    db 08Dh, 08Eh, 058h, 060h, 001h, 000h, 0C6h, 044h, 024h, 028h, 006h
    call ?j_0001cd7d@@YAXXZ
    db 08Dh, 08Eh, 04Ch, 060h, 001h, 000h, 0C6h, 044h, 024h, 028h, 005h
    call ?j_00005a56@@YAXXZ
    db 08Dh, 08Eh, 040h, 060h, 001h, 000h, 0C6h, 044h, 024h, 028h, 004h
    call ?j_00003a44@@YAXXZ
    db 068h
    dd ?j_0001053c@@YAXXZ
    db 068h, 0B8h, 000h, 000h, 000h, 06Ah, 07Ch, 08Dh, 08Eh, 020h, 007h, 001h, 000h, 051h, 0C6h, 044h
    db 024h, 038h, 003h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 068h
    dd ?j_00034f72@@YAXXZ
    db 068h, 01Fh, 002h, 000h, 000h, 06Ah, 07Ch, 08Dh, 056h, 01Ch, 052h, 0C6h, 044h, 024h, 038h, 002h
    call ??_M@YGXPAXIHP6EX0@Z@Z
    db 08Bh, 046h, 00Ch, 03Bh, 0C3h, 0C6h, 044h, 024h, 028h, 001h, 074h, 028h, 08Bh, 04Eh, 014h, 02Bh
    db 0C8h, 0C1h, 0F9h, 002h, 0C1h, 0E1h, 002h, 081h, 0F9h, 080h, 000h, 000h, 000h, 076h, 00Bh, 050h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0EBh, 00Ah, 051h, 050h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Bh, 0CEh, 0C7h, 046h, 008h
    dd ??_7?$BasicTimerClass@VSystemTimerClass@@@@6B@
    db 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1SubsystemInterface@@UAE@XZ
    db 08Bh, 04Ch, 024h, 020h, 05Fh, 05Eh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 020h, 0C3h
?d_003492a0@@YAXXZ ENDP
_TEXT$d007492a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_0074b8d0  retail @ 0x0034B8D0 size 121
_TEXT ENDS
_TEXT$d0074b8d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0074B8D0 size 121
public ?d_0034b8d0@@YAXXZ
?d_0034b8d0@@YAXXZ PROC
    db 053h, 08Bh, 05Ch, 024h, 00Ch, 055h, 08Bh, 06Ch, 024h, 01Ch, 056h, 057h, 08Bh, 07Ch, 024h, 014h
    db 06Ah, 000h, 06Ah, 000h, 055h, 053h, 057h
    call ?j_0000f74f@@YAXXZ
    db 08Bh, 044h, 024h, 030h, 083h, 0C4h, 014h, 03Bh, 0D8h, 08Bh, 0F3h, 073h, 040h, 08Dh, 0A4h, 024h
    db 000h, 000h, 000h, 000h, 08Bh, 007h, 08Bh, 00Eh, 050h, 051h, 08Dh, 04Ch, 024h, 02Ch
    call ?j_00024b81@@YAXXZ
    db 084h, 0C0h, 074h, 01Bh, 08Bh, 006h, 08Bh, 017h, 055h, 050h, 08Bh, 0C3h, 02Bh, 0C7h, 0C1h, 0F8h
    db 002h, 050h, 06Ah, 000h, 057h, 089h, 016h
    call ?j_0000a20e@@YAXXZ
    db 083h, 0C4h, 014h, 08Bh, 044h, 024h, 01Ch, 083h, 0C6h, 004h, 03Bh, 0F0h, 072h, 0C7h, 055h, 053h
    db 057h
    call ?j_0002720f@@YAXXZ
    db 083h, 0C4h, 00Ch, 05Fh, 05Eh, 05Dh, 05Bh, 0C3h
?d_0034b8d0@@YAXXZ ENDP
_TEXT$d0074b8d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_0074bfc0  retail @ 0x0034BFC0 size 140
public ?d_0034bfc0@@YAXXZ
?d_0034bfc0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0C7h, 2Bh, 0C3h, 83h, 0E0h
    db 0FCh, 83h, 0F8h, 40h, 7Eh, 73h, 55h, 8Bh, 6Ch, 24h, 20h, 56h, 8Dh, 64h, 24h, 00h
    db 8Bh, 44h, 24h, 20h, 85h, 0C0h, 55h, 74h, 51h, 8Bh, 0C8h, 8Bh, 0C7h, 2Bh, 0C3h, 0C1h
    db 0F8h, 02h, 99h, 49h, 2Bh, 0C2h, 89h, 4Ch, 24h, 24h, 8Dh, 4Fh, 0FCh, 0D1h, 0F8h, 51h
    db 8Dh, 14h, 83h, 52h, 53h, 0E8h, 25h, 22h, 0CFh, 0FFh, 8Bh, 00h, 55h, 50h, 57h, 53h
    db 0E8h, 38h, 0F6h, 0CDh, 0FFh, 8Bh, 4Ch, 24h, 40h, 55h, 51h, 6Ah, 00h, 8Bh, 0F0h, 57h
    db 56h, 0E8h, 16h, 0D2h, 0CBh, 0FFh, 8Bh, 0FEh, 2Bh, 0F3h, 83h, 0E6h, 0FCh, 83h, 0C4h, 34h
    db 83h, 0FEh, 40h, 7Fh, 0ABh, 5Eh, 5Dh, 5Fh, 5Bh, 0C3h, 6Ah, 00h, 57h, 57h, 53h, 0E8h
    db 16h, 0A8h, 0CDh, 0FFh, 83h, 0C4h, 14h, 5Eh, 5Dh, 5Fh, 5Bh, 0C3h
?d_0034bfc0@@YAXXZ ENDP

; ghidra: FUN_0074c4d0  retail @ 0x0034C4D0 size 69
public ?d_0034c4d0@@YAXXZ
?d_0034c4d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 0Ch, 85h, 0C0h, 74h, 34h, 56h, 8Bh, 74h, 24h, 18h
    db 85h, 0F6h, 74h, 2Ah, 8Bh, 16h, 57h, 89h, 54h, 24h, 08h, 8Bh, 56h, 04h, 8Dh, 7Ch
    db 24h, 08h, 57h, 89h, 54h, 24h, 10h, 8Bh, 11h, 50h, 0FFh, 92h, 0C8h, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 0Ch, 89h, 06h, 89h, 4Eh, 04h, 5Fh, 5Eh, 83h
    db 0C4h, 0Ch, 0C2h, 08h, 00h
?d_0034c4d0@@YAXXZ ENDP

; ghidra: FUN_0074c5e0  retail @ 0x0034C5E0 size 84
public ?d_0034c5e0@@YAXXZ
?d_0034c5e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D3h, 8Dh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 33h, 0D2h, 8Dh
    db 4Eh, 04h, 0C7h, 06h, 00h, 7Dh, 0Eh, 01h, 89h, 54h, 24h, 10h, 89h, 11h, 0B8h, 01h
    db 00h, 00h, 00h, 88h, 44h, 24h, 10h, 89h, 46h, 08h, 89h, 56h, 0Ch, 0E8h, 1Eh, 0B3h
    db 53h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_0034c5e0@@YAXXZ ENDP

; ghidra: FUN_0074c670  retail @ 0x0034C670 size 125
public ?d_0034c670@@YAXXZ
?d_0034c670@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 00h, 8Eh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Dh, 44h, 24h, 18h, 50h, 8Dh, 54h, 24h, 08h
    db 52h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 0E8h, 98h, 9Ch, 0CEh, 0FFh, 8Dh, 44h
    db 24h, 18h, 50h, 8Dh, 4Ch, 24h, 08h, 51h, 8Bh, 0Dh, 10h, 0D8h, 2Eh, 01h, 0C6h, 44h
    db 24h, 18h, 01h, 0E8h, 81h, 43h, 0CFh, 0FFh, 8Dh, 4Ch, 24h, 04h, 8Bh, 0F0h, 0C6h, 44h
    db 24h, 10h, 00h, 0E8h, 78h, 0B2h, 53h, 00h, 8Dh, 4Ch, 24h, 18h, 0C7h, 44h, 24h, 10h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 67h, 0B2h, 53h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_0034c670@@YAXXZ ENDP

; ghidra: FUN_0074c830  retail @ 0x0034C830 size 90
public ?d_0034c830@@YAXXZ
?d_0034c830@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 7Ch, 4Dh, 83h, 0F8h, 20h, 7Dh, 48h, 8Dh, 04h, 40h
    db 8Bh, 94h, 81h, 78h, 74h, 01h, 00h, 8Dh, 8Ch, 81h, 74h, 74h, 01h, 00h, 8Bh, 01h
    db 3Bh, 0C2h, 56h, 74h, 16h, 8Bh, 74h, 24h, 0Ch, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 39h, 30h, 74h, 0Dh, 83h, 0C0h, 04h, 3Bh, 0C2h, 75h, 0F5h, 32h, 0C0h, 5Eh, 0C2h, 0Ch
    db 00h, 8Ah, 54h, 24h, 10h, 84h, 0D2h, 74h, 06h, 50h, 0E8h, 28h, 0DAh, 0CDh, 0FFh, 0B0h
    db 01h, 5Eh, 0C2h, 0Ch, 00h, 32h, 0C0h, 0C2h, 0Ch, 00h
?d_0034c830@@YAXXZ ENDP

; ghidra: FUN_0074c9b0  retail @ 0x0034C9B0 size 82
public ?d_0034c9b0@@YAXXZ
?d_0034c9b0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 08h, 74h, 3Ah
    db 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0EFh, 58h, 0CBh, 0FFh, 8Bh, 76h, 0Ch, 85h
    db 0F6h, 89h, 44h, 24h, 10h, 74h, 23h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 1Ch, 8Dh, 44h
    db 24h, 10h, 50h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0E8h, 16h, 35h, 0CDh, 0FFh, 8Bh
    db 44h, 24h, 08h, 3Bh, 06h, 74h, 03h, 8Bh, 78h, 14h, 8Bh, 0C7h, 5Fh, 5Eh, 59h, 0C2h
    db 04h, 00h
?d_0034c9b0@@YAXXZ ENDP

; ghidra: FUN_0074cb60  retail @ 0x0034CB60 size 635
public ?d_0034cb60@@YAXXZ
?d_0034cb60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 8Eh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 53h, 55h
    db 56h, 57h, 89h, 4Ch, 24h, 14h, 74h, 03h, 0C6h, 00h, 01h, 8Bh, 0Dh, 6Ch, 07h, 2Fh
    db 01h, 8Bh, 01h, 0FFh, 50h, 4Ch, 85h, 0C0h, 75h, 18h, 66h, 33h, 0C0h, 8Bh, 4Ch, 24h
    db 1Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 18h, 0C2h
    db 08h, 00h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 11h, 33h, 0F6h, 0FFh, 52h, 4Ch, 8Bh
    db 58h, 24h, 8Bh, 3Dh, 48h, 0D7h, 2Eh, 01h, 8Bh, 47h, 0Ch, 8Bh, 6Ch, 24h, 2Ch, 89h
    db 44h, 24h, 18h, 8Bh, 40h, 24h, 68h, 4Ch, 7Eh, 0Eh, 01h, 8Bh, 0CDh, 89h, 44h, 24h
    db 14h, 0E8h, 34h, 0E4h, 0CFh, 0FFh, 85h, 0C0h, 75h, 12h, 50h, 6Ah, 04h, 53h, 8Bh, 0CFh
    db 0E8h, 6Bh, 80h, 0CFh, 0FFh, 8Bh, 0F0h, 0E9h, 0C7h, 01h, 00h, 00h, 68h, 24h, 7Eh, 0Eh
    db 01h, 8Bh, 0CDh, 0E8h, 12h, 0E4h, 0CFh, 0FFh, 85h, 0C0h, 75h, 12h, 50h, 6Ah, 03h, 53h
    db 8Bh, 0CFh, 0E8h, 49h, 80h, 0CFh, 0FFh, 8Bh, 0F0h, 0E9h, 0A5h, 01h, 00h, 00h, 68h, 08h
    db 7Eh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 0F0h, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 12h, 50h, 6Ah
    db 02h, 53h, 8Bh, 0CFh, 0E8h, 27h, 80h, 0CFh, 0FFh, 8Bh, 0F0h, 0E9h, 83h, 01h, 00h, 00h
    db 68h, 0F8h, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 0CEh, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 18h
    db 8Bh, 4Ch, 24h, 14h, 8Bh, 11h, 0FFh, 52h, 4Ch, 8Bh, 48h, 24h, 0BEh, 01h, 00h, 00h
    db 00h, 0D3h, 0E6h, 0E9h, 5Bh, 01h, 00h, 00h, 68h, 0DCh, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h
    db 0A6h, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 18h, 8Bh, 4Ch, 24h, 14h, 8Bh, 01h, 0FFh, 50h
    db 48h, 8Bh, 48h, 24h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 0E9h, 33h, 01h, 00h, 00h
    db 68h, 0C8h, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 7Eh, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 13h
    db 8Bh, 4Ch, 24h, 18h, 8Bh, 49h, 24h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 0E9h, 10h
    db 01h, 00h, 00h, 68h, 0A8h, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 5Bh, 0E3h, 0CFh, 0FFh, 85h
    db 0C0h, 75h, 16h, 8Bh, 54h, 24h, 10h, 50h, 6Ah, 04h, 52h, 8Bh, 0CFh, 0E8h, 8Eh, 7Fh
    db 0CFh, 0FFh, 8Bh, 0F0h, 0E9h, 0EAh, 00h, 00h, 00h, 68h, 80h, 7Dh, 0Eh, 01h, 8Bh, 0CDh
    db 0E8h, 35h, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 16h, 50h, 8Bh, 44h, 24h, 14h, 6Ah, 03h
    db 50h, 8Bh, 0CFh, 0E8h, 68h, 7Fh, 0CFh, 0FFh, 8Bh, 0F0h, 0E9h, 0C4h, 00h, 00h, 00h, 68h
    db 64h, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 0Fh, 0E3h, 0CFh, 0FFh, 85h, 0C0h, 75h, 16h, 8Bh
    db 4Ch, 24h, 10h, 50h, 6Ah, 02h, 51h, 8Bh, 0CFh, 0E8h, 42h, 7Fh, 0CFh, 0FFh, 8Bh, 0F0h
    db 0E9h, 9Eh, 00h, 00h, 00h, 68h, 54h, 7Dh, 0Eh, 01h, 8Bh, 0CDh, 0E8h, 0E9h, 0E2h, 0CFh
    db 0FFh, 85h, 0C0h, 75h, 0Eh, 8Bh, 0CFh, 0E8h, 0A5h, 66h, 0CBh, 0FFh, 8Bh, 0F0h, 0E9h, 80h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 30h, 33h, 0FFh, 3Bh, 0C7h, 74h, 03h, 0C6h, 00h, 00h
    db 55h, 0E8h, 0CCh, 54h, 0CEh, 0FFh, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 83h, 0C4h, 04h, 50h
    db 0E8h, 21h, 28h, 0CEh, 0FFh, 3Bh, 0C7h, 0Fh, 85h, 0ECh, 0FEh, 0FFh, 0FFh, 89h, 7Ch, 24h
    db 30h, 8Bh, 6Dh, 00h, 3Bh, 0EFh, 89h, 7Ch, 24h, 24h, 8Dh, 45h, 08h, 75h, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 50h, 51h, 89h, 64h, 24h, 34h, 8Bh, 0CCh, 68h, 2Ch, 7Dh, 0Eh
    db 01h, 0E8h, 2Ah, 0BEh, 53h, 00h, 8Dh, 54h, 24h, 38h, 52h, 0E8h, 50h, 0C2h, 53h, 00h
    db 8Bh, 4Ch, 24h, 20h, 83h, 0C4h, 0Ch, 57h, 8Dh, 44h, 24h, 34h, 50h, 0E8h, 2Eh, 0BFh
    db 0CDh, 0FFh, 8Dh, 4Ch, 24h, 30h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 7Dh
    db 0ABh, 53h, 00h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 66h, 8Bh, 0C6h, 5Eh, 5Dh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 18h, 0C2h, 08h, 00h
?d_0034cb60@@YAXXZ ENDP

; ghidra: FUN_0074d200  retail @ 0x0034D200 size 226
public ?d_0034d200@@YAXXZ
?d_0034d200@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0A9h, 0F8h, 75h, 01h, 00h, 8Bh, 89h, 0FCh, 75h, 01h, 00h, 3Bh
    db 0E9h, 56h, 57h, 89h, 4Ch, 24h, 10h, 0Fh, 84h, 0BDh, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 18h, 8Bh, 38h, 89h, 7Ch, 24h, 18h, 0EBh, 07h, 8Bh, 7Ch, 24h, 18h, 8Dh, 49h, 00h
    db 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0DBh, 0BFh
    db 8Bh, 38h, 07h, 01h, 8Bh, 45h, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh
    db 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh
    db 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h
    db 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 74h, 13h, 8Bh, 44h
    db 24h, 10h, 83h, 0C5h, 10h, 3Bh, 0E8h, 75h, 0A0h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h
    db 00h, 51h, 8Dh, 55h, 04h, 89h, 64h, 24h, 1Ch, 8Bh, 0CCh, 52h, 0E8h, 0BFh, 0A8h, 53h
    db 00h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 0FFh, 50h, 7Ch, 8Bh, 0F0h, 85h, 0F6h
    db 74h, 28h, 6Ah, 00h, 8Dh, 4Dh, 0Ch, 51h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 0E8h, 0CDh
    db 0DFh, 0CFh, 0FFh, 8Bh, 0Dh, 0BCh, 0D5h, 2Eh, 01h, 0Fh, 0B7h, 0D0h, 8Bh, 45h, 08h, 52h
    db 50h, 83h, 0C6h, 0Ch, 56h, 0E8h, 0A6h, 0A3h, 5Ah, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_0034d200@@YAXXZ ENDP

; ghidra: FUN_0074d440  retail @ 0x0034D440 size 217
public ?d_0034d440@@YAXXZ
?d_0034d440@@YAXXZ PROC
    db 83h, 0ECh, 08h, 55h, 8Bh, 0A9h, 0F8h, 75h, 01h, 00h, 89h, 4Ch, 24h, 08h, 8Bh, 89h
    db 0FCh, 75h, 01h, 00h, 3Bh, 0E9h, 89h, 4Ch, 24h, 04h, 0Fh, 84h, 0B2h, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 10h, 53h, 56h, 57h, 8Bh, 38h, 89h, 7Ch, 24h, 1Ch, 0EBh, 04h, 8Bh
    db 7Ch, 24h, 1Ch, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h
    db 33h, 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 45h, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h
    db 50h, 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h
    db 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h
    db 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 74h
    db 15h, 8Bh, 44h, 24h, 10h, 83h, 0C5h, 10h, 3Bh, 0E8h, 75h, 0A3h, 5Fh, 5Eh, 5Bh, 5Dh
    db 83h, 0C4h, 08h, 0C2h, 04h, 00h, 8Bh, 74h, 24h, 14h, 8Bh, 86h, 0FCh, 75h, 01h, 00h
    db 8Dh, 4Dh, 10h, 3Bh, 0C8h, 74h, 12h, 6Ah, 00h, 8Dh, 54h, 24h, 20h, 52h, 55h, 50h
    db 51h, 0E8h, 0F1h, 0CCh, 0CFh, 0FFh, 83h, 0C4h, 14h, 8Bh, 86h, 0FCh, 75h, 01h, 00h, 83h
    db 0C0h, 0F0h, 8Bh, 0C8h, 89h, 86h, 0FCh, 75h, 01h, 00h, 0E8h, 0CEh, 6Fh, 0CDh, 0FFh, 5Fh
    db 5Eh, 5Bh, 5Dh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_0034d440@@YAXXZ ENDP

; ghidra: FUN_0074db40  retail @ 0x0034DB40 size 215
public ?d_0034db40@@YAXXZ
?d_0034db40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 8Eh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h
    db 4Ch, 85h, 0C0h, 75h, 14h, 66h, 33h, 0C0h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 8Bh
    db 47h, 20h, 33h, 0F6h, 85h, 0C0h, 74h, 1Ch, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 50h, 0E8h
    db 51h, 02h, 0CDh, 0FFh, 85h, 0C0h, 74h, 69h, 8Bh, 48h, 24h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 0EBh, 5Dh, 8Dh, 4Fh, 10h, 51h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0AFh, 9Fh, 53h
    db 00h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Dh, 54h, 24h, 1Ch, 52h, 8Dh, 44h, 24h, 0Ch
    db 50h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 0C2h, 0D6h, 0CFh, 0FFh, 8Bh, 0F0h
    db 8Ah, 44h, 24h, 1Ch, 84h, 0C0h, 75h, 18h, 68h, 0F8h, 7Dh, 0Eh, 01h, 8Dh, 4Ch, 24h
    db 0Ch, 0E8h, 34h, 0D4h, 0CFh, 0FFh, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 0CEh, 89h, 4Fh, 20h
    db 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 3Fh, 9Dh, 53h
    db 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 66h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_0034db40@@YAXXZ ENDP

; ghidra: FUN_0074ddc0  retail @ 0x0034DDC0 size 52
public ?d_0034ddc0@@YAXXZ
?d_0034ddc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Dh, 4Eh, 04h, 0E8h, 74h, 9Bh, 53h, 00h, 8Bh, 7Eh, 0Ch, 85h
    db 0FFh, 0C7h, 46h, 08h, 01h, 00h, 00h, 00h, 74h, 17h, 8Bh, 0CFh, 0E8h, 0ECh, 0EFh, 0CCh
    db 0FFh, 57h, 0E8h, 0C9h, 40h, 53h, 00h, 83h, 0C4h, 04h, 0C7h, 46h, 0Ch, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 0C3h
?d_0034ddc0@@YAXXZ ENDP

; ghidra: FUN_0074de60  retail @ 0x0034DE60 size 52
public ?d_0034de60@@YAXXZ
?d_0034de60@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0B9h, 6Ch, 72h, 01h, 00h, 6Ah, 0Ch, 0E8h, 0D1h, 06h, 4Eh, 00h, 8Bh
    db 0F0h, 8Bh, 44h, 24h, 10h, 50h, 8Dh, 4Eh, 08h, 51h, 0E8h, 0D5h, 96h, 0CBh, 0FFh, 8Bh
    db 47h, 04h, 89h, 3Eh, 89h, 46h, 04h, 83h, 0C4h, 0Ch, 89h, 30h, 89h, 77h, 04h, 5Fh
    db 5Eh, 0C2h, 04h, 00h
?d_0034de60@@YAXXZ ENDP

; ghidra: FUN_0074deb0  retail @ 0x0034DEB0 size 144
public ?d_0034deb0@@YAXXZ
?d_0034deb0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 8Fh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 8Bh, 44h, 24h, 1Ch, 56h, 57h, 8Bh, 0F1h
    db 50h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 86h, 9Ch, 53h, 00h, 8Bh, 4Ch, 24h, 28h, 89h, 4Ch
    db 24h, 0Ch, 8Bh, 54h, 24h, 20h, 8Bh, 0BCh, 96h, 74h, 72h, 01h, 00h, 6Ah, 10h, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 44h, 06h, 4Eh, 00h, 8Bh, 0F0h, 8Dh, 44h
    db 24h, 0Ch, 50h, 8Dh, 4Eh, 08h, 51h, 0E8h, 5Ch, 0B0h, 0CFh, 0FFh, 8Bh, 47h, 04h, 89h
    db 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 08h, 89h, 77h, 04h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 13h, 9Ah, 53h, 00h, 8Bh, 4Ch, 24h
    db 10h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_0034deb0@@YAXXZ ENDP

; ghidra: FUN_0074df70  retail @ 0x0034DF70 size 144
public ?d_0034df70@@YAXXZ
?d_0034df70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 8Fh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 8Bh, 44h, 24h, 1Ch, 56h, 57h, 8Bh, 0F1h
    db 50h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0C6h, 9Bh, 53h, 00h, 8Bh, 4Ch, 24h, 28h, 89h, 4Ch
    db 24h, 0Ch, 8Bh, 54h, 24h, 20h, 8Bh, 0BCh, 96h, 0F4h, 72h, 01h, 00h, 6Ah, 10h, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 84h, 05h, 4Eh, 00h, 8Bh, 0F0h, 8Dh, 44h
    db 24h, 0Ch, 50h, 8Dh, 4Eh, 08h, 51h, 0E8h, 9Ch, 0AFh, 0CFh, 0FFh, 8Bh, 47h, 04h, 89h
    db 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 08h, 89h, 77h, 04h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 53h, 99h, 53h, 00h, 8Bh, 4Ch, 24h
    db 10h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_0034df70@@YAXXZ ENDP

; ghidra: FUN_0074e030  retail @ 0x0034E030 size 144
public ?d_0034e030@@YAXXZ
?d_0034e030@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Fh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 8Bh, 44h, 24h, 1Ch, 56h, 57h, 8Bh, 0F1h
    db 50h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 06h, 9Bh, 53h, 00h, 8Bh, 4Ch, 24h, 28h, 89h, 4Ch
    db 24h, 0Ch, 8Bh, 54h, 24h, 20h, 8Bh, 0BCh, 96h, 74h, 73h, 01h, 00h, 6Ah, 10h, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 0C4h, 04h, 4Eh, 00h, 8Bh, 0F0h, 8Dh, 44h
    db 24h, 0Ch, 50h, 8Dh, 4Eh, 08h, 51h, 0E8h, 0DCh, 0AEh, 0CFh, 0FFh, 8Bh, 47h, 04h, 89h
    db 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 08h, 89h, 77h, 04h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 93h, 98h, 53h, 00h, 8Bh, 4Ch, 24h
    db 10h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_0034e030@@YAXXZ ENDP

; ghidra: FUN_0074e0f0  retail @ 0x0034E0F0 size 144
public ?d_0034e0f0@@YAXXZ
?d_0034e0f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 8Fh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 8Bh, 44h, 24h, 1Ch, 56h, 57h, 8Bh, 0F1h
    db 50h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 46h, 9Ah, 53h, 00h, 8Bh, 4Ch, 24h, 28h, 89h, 4Ch
    db 24h, 0Ch, 8Bh, 54h, 24h, 20h, 8Bh, 0BCh, 96h, 0F4h, 73h, 01h, 00h, 6Ah, 10h, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 04h, 04h, 4Eh, 00h, 8Bh, 0F0h, 8Dh, 44h
    db 24h, 0Ch, 50h, 8Dh, 4Eh, 08h, 51h, 0E8h, 1Ch, 0AEh, 0CFh, 0FFh, 8Bh, 47h, 04h, 89h
    db 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 08h, 89h, 77h, 04h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D3h, 97h, 53h, 00h, 8Bh, 4Ch, 24h
    db 10h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_0034e0f0@@YAXXZ ENDP

; ghidra: FUN_0074e2e0  retail @ 0x0034E2E0 size 110
public ?d_0034e2e0@@YAXXZ
?d_0034e2e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C3h, 8Fh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 0C7h, 06h
    db 00h, 7Dh, 0Eh, 01h, 8Bh, 7Eh, 0Ch, 85h, 0FFh, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h
    db 00h, 74h, 10h, 8Bh, 0CFh, 0E8h, 03h, 0F3h, 0CEh, 0FFh, 57h, 0E8h, 90h, 3Bh, 53h, 00h
    db 83h, 0C4h, 04h, 8Dh, 4Eh, 04h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 0C6h, 44h, 24h
    db 14h, 00h, 0E8h, 09h, 96h, 53h, 00h, 8Bh, 4Ch, 24h, 0Ch, 0C7h, 06h, 44h, 37h, 07h
    db 01h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0034e2e0@@YAXXZ ENDP

; ghidra: FUN_0074e490  retail @ 0x0034E490 size 110
public ?d_0034e490@@YAXXZ
?d_0034e490@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 86h, 60h, 72h, 01h, 00h, 8Bh, 08h, 8Dh, 54h, 24h, 10h
    db 52h, 8Bh, 54h, 24h, 10h, 52h, 51h, 8Bh, 0D4h, 89h, 02h, 51h, 8Bh, 0C4h, 89h, 08h
    db 8Dh, 44h, 24h, 1Ch, 50h, 0E8h, 0B4h, 0F1h, 0CDh, 0FFh, 8Bh, 7Ch, 24h, 20h, 8Bh, 86h
    db 60h, 72h, 01h, 00h, 83h, 0C4h, 14h, 3Bh, 0F8h, 74h, 2Ch, 8Ah, 44h, 24h, 10h, 84h
    db 0C0h, 74h, 1Dh, 8Bh, 4Fh, 04h, 8Bh, 07h, 89h, 01h, 89h, 48h, 04h, 8Dh, 4Fh, 08h
    db 0E8h, 43h, 0F3h, 0CBh, 0FFh, 6Ah, 0Ch, 57h, 0E8h, 03h, 01h, 4Eh, 00h, 83h, 0C4h, 08h
    db 0B0h, 01h, 5Fh, 5Eh, 0C2h, 08h, 00h, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 08h, 00h
?d_0034e490@@YAXXZ ENDP

; ghidra: FUN_0074e520  retail @ 0x0034E520 size 110
public ?d_0034e520@@YAXXZ
?d_0034e520@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 86h, 6Ch, 72h, 01h, 00h, 8Bh, 08h, 8Dh, 54h, 24h, 10h
    db 52h, 8Bh, 54h, 24h, 10h, 52h, 51h, 8Bh, 0D4h, 89h, 02h, 51h, 8Bh, 0C4h, 89h, 08h
    db 8Dh, 44h, 24h, 1Ch, 50h, 0E8h, 24h, 0F1h, 0CDh, 0FFh, 8Bh, 7Ch, 24h, 20h, 8Bh, 86h
    db 6Ch, 72h, 01h, 00h, 83h, 0C4h, 14h, 3Bh, 0F8h, 74h, 2Ch, 8Ah, 44h, 24h, 10h, 84h
    db 0C0h, 74h, 1Dh, 8Bh, 4Fh, 04h, 8Bh, 07h, 89h, 01h, 89h, 48h, 04h, 8Dh, 4Fh, 08h
    db 0E8h, 0B3h, 0F2h, 0CBh, 0FFh, 6Ah, 0Ch, 57h, 0E8h, 73h, 00h, 4Eh, 00h, 83h, 0C4h, 08h
    db 0B0h, 01h, 5Fh, 5Eh, 0C2h, 08h, 00h, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 08h, 00h
?d_0034e520@@YAXXZ ENDP

; ghidra: FUN_0074e5b0  retail @ 0x0034E5B0 size 482
public ?d_0034e5b0@@YAXXZ
?d_0034e5b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 27h, 90h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 80h, 00h, 00h, 00h, 53h, 8Bh, 0D9h, 8Bh, 83h
    db 64h, 72h, 01h, 00h, 55h, 8Bh, 28h, 3Bh, 0E8h, 56h, 57h, 89h, 5Ch, 24h, 18h, 89h
    db 44h, 24h, 10h, 74h, 7Ah, 8Bh, 84h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 38h, 89h, 7Ch
    db 24h, 1Ch, 0EBh, 04h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h
    db 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 45h, 08h, 85h
    db 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h
    db 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h
    db 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h
    db 8Bh, 0C2h, 85h, 0C0h, 74h, 09h, 8Bh, 6Dh, 00h, 3Bh, 6Ch, 24h, 10h, 75h, 0A5h, 8Bh
    db 44h, 24h, 10h, 3Bh, 0E8h, 8Bh, 5Ch, 24h, 18h, 0Fh, 85h, 0DCh, 00h, 00h, 00h, 33h
    db 0C0h, 89h, 44h, 24h, 10h, 89h, 44h, 24h, 14h, 8Bh, 0BCh, 24h, 0A0h, 00h, 00h, 00h
    db 50h, 57h, 8Dh, 4Ch, 24h, 28h, 89h, 84h, 24h, 0A0h, 00h, 00h, 00h, 0E8h, 84h, 6Ch
    db 0CDh, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 20h, 50h, 0C6h
    db 84h, 24h, 9Ch, 00h, 00h, 00h, 01h, 0FFh, 92h, 30h, 01h, 00h, 00h, 0D8h, 0Dh, 4Ch
    db 7Fh, 0Eh, 01h, 0E8h, 90h, 87h, 6Ah, 00h, 57h, 8Dh, 4Ch, 24h, 14h, 8Bh, 0F0h, 0E8h
    db 0DCh, 95h, 53h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 41h, 3Ch, 8Bh, 93h, 64h
    db 72h, 01h, 00h, 03h, 0C6h, 89h, 44h, 24h, 14h, 8Bh, 2Ah, 6Ah, 10h, 0E8h, 6Eh, 0FEh
    db 4Dh, 00h, 8Bh, 0F0h, 8Dh, 7Eh, 08h, 83h, 0C4h, 04h, 89h, 7Ch, 24h, 1Ch, 89h, 7Ch
    db 24h, 18h, 85h, 0FFh, 0C6h, 84h, 24h, 98h, 00h, 00h, 00h, 02h, 74h, 13h, 8Dh, 44h
    db 24h, 10h, 50h, 8Bh, 0CFh, 0E8h, 66h, 94h, 53h, 00h, 8Bh, 4Ch, 24h, 14h, 89h, 4Fh
    db 04h, 8Bh, 45h, 04h, 89h, 2Eh, 89h, 46h, 04h, 89h, 30h, 89h, 75h, 04h, 8Bh, 93h
    db 64h, 72h, 01h, 00h, 8Bh, 2Ah, 8Dh, 4Ch, 24h, 20h, 0C6h, 84h, 24h, 98h, 00h, 00h
    db 00h, 00h, 0E8h, 0Eh, 88h, 0CDh, 0FFh, 8Dh, 4Ch, 24h, 10h, 0C7h, 84h, 24h, 98h, 00h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 05h, 92h, 53h, 00h, 0A1h, 98h, 08h, 2Fh, 01h
    db 8Bh, 48h, 3Ch, 3Bh, 4Dh, 0Ch, 72h, 2Dh, 8Ah, 84h, 24h, 0A4h, 00h, 00h, 00h, 84h
    db 0C0h, 74h, 1Eh, 8Bh, 4Dh, 04h, 8Bh, 45h, 00h, 89h, 01h, 89h, 48h, 04h, 8Dh, 4Dh
    db 08h, 0E8h, 0DAh, 91h, 53h, 00h, 6Ah, 10h, 55h, 0E8h, 82h, 0FEh, 4Dh, 00h, 83h, 0C4h
    db 08h, 0B0h, 01h, 0EBh, 02h, 32h, 0C0h, 8Bh, 8Ch, 24h, 90h, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 8Ch, 00h, 00h, 00h, 0C2h
    db 08h, 00h
?d_0034e5b0@@YAXXZ ENDP

; ghidra: FUN_0074e810  retail @ 0x0034E810 size 482
public ?d_0034e810@@YAXXZ
?d_0034e810@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 67h, 90h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 80h, 00h, 00h, 00h, 53h, 8Bh, 0D9h, 8Bh, 83h
    db 68h, 72h, 01h, 00h, 55h, 8Bh, 28h, 3Bh, 0E8h, 56h, 57h, 89h, 5Ch, 24h, 18h, 89h
    db 44h, 24h, 10h, 74h, 7Ah, 8Bh, 84h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 38h, 89h, 7Ch
    db 24h, 1Ch, 0EBh, 04h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h
    db 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 45h, 08h, 85h
    db 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h
    db 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h
    db 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h
    db 8Bh, 0C2h, 85h, 0C0h, 74h, 09h, 8Bh, 6Dh, 00h, 3Bh, 6Ch, 24h, 10h, 75h, 0A5h, 8Bh
    db 44h, 24h, 10h, 3Bh, 0E8h, 8Bh, 5Ch, 24h, 18h, 0Fh, 85h, 0DCh, 00h, 00h, 00h, 33h
    db 0C0h, 89h, 44h, 24h, 10h, 89h, 44h, 24h, 14h, 8Bh, 0BCh, 24h, 0A0h, 00h, 00h, 00h
    db 50h, 57h, 8Dh, 4Ch, 24h, 28h, 89h, 84h, 24h, 0A0h, 00h, 00h, 00h, 0E8h, 24h, 6Ah
    db 0CDh, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 20h, 50h, 0C6h
    db 84h, 24h, 9Ch, 00h, 00h, 00h, 01h, 0FFh, 92h, 30h, 01h, 00h, 00h, 0D8h, 0Dh, 4Ch
    db 7Fh, 0Eh, 01h, 0E8h, 30h, 85h, 6Ah, 00h, 57h, 8Dh, 4Ch, 24h, 14h, 8Bh, 0F0h, 0E8h
    db 7Ch, 93h, 53h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 41h, 3Ch, 8Bh, 93h, 68h
    db 72h, 01h, 00h, 03h, 0C6h, 89h, 44h, 24h, 14h, 8Bh, 2Ah, 6Ah, 10h, 0E8h, 0Eh, 0FCh
    db 4Dh, 00h, 8Bh, 0F0h, 8Dh, 7Eh, 08h, 83h, 0C4h, 04h, 89h, 7Ch, 24h, 1Ch, 89h, 7Ch
    db 24h, 18h, 85h, 0FFh, 0C6h, 84h, 24h, 98h, 00h, 00h, 00h, 02h, 74h, 13h, 8Dh, 44h
    db 24h, 10h, 50h, 8Bh, 0CFh, 0E8h, 06h, 92h, 53h, 00h, 8Bh, 4Ch, 24h, 14h, 89h, 4Fh
    db 04h, 8Bh, 45h, 04h, 89h, 2Eh, 89h, 46h, 04h, 89h, 30h, 89h, 75h, 04h, 8Bh, 93h
    db 68h, 72h, 01h, 00h, 8Bh, 2Ah, 8Dh, 4Ch, 24h, 20h, 0C6h, 84h, 24h, 98h, 00h, 00h
    db 00h, 00h, 0E8h, 0AEh, 85h, 0CDh, 0FFh, 8Dh, 4Ch, 24h, 10h, 0C7h, 84h, 24h, 98h, 00h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A5h, 8Fh, 53h, 00h, 0A1h, 98h, 08h, 2Fh, 01h
    db 8Bh, 48h, 3Ch, 3Bh, 4Dh, 0Ch, 72h, 2Dh, 8Ah, 84h, 24h, 0A4h, 00h, 00h, 00h, 84h
    db 0C0h, 74h, 1Eh, 8Bh, 4Dh, 04h, 8Bh, 45h, 00h, 89h, 01h, 89h, 48h, 04h, 8Dh, 4Dh
    db 08h, 0E8h, 7Ah, 8Fh, 53h, 00h, 6Ah, 10h, 55h, 0E8h, 22h, 0FCh, 4Dh, 00h, 83h, 0C4h
    db 08h, 0B0h, 01h, 0EBh, 02h, 32h, 0C0h, 8Bh, 8Ch, 24h, 90h, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 8Ch, 00h, 00h, 00h, 0C2h
    db 08h, 00h
?d_0034e810@@YAXXZ ENDP

; ghidra: FUN_0074ea70  retail @ 0x0034EA70 size 451
public ?d_0034ea70@@YAXXZ
?d_0034ea70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 99h, 90h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 8Bh, 44h, 24h, 30h, 8Bh, 00h, 85h, 0C0h
    db 53h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 1Ch, 89h, 44h, 24h, 10h, 0Fh, 84h
    db 0BEh, 00h, 00h, 00h, 33h, 0C9h, 66h, 8Bh, 48h, 04h, 66h, 85h, 0C9h, 89h, 4Ch, 24h
    db 14h, 0Fh, 84h, 0ABh, 00h, 00h, 00h, 8Bh, 96h, 0F4h, 75h, 01h, 00h, 8Bh, 1Ah, 3Bh
    db 0DAh, 89h, 54h, 24h, 18h, 0Fh, 85h, 0B5h, 00h, 00h, 00h, 33h, 0EDh, 89h, 6Ch, 24h
    db 20h, 8Bh, 4Ch, 24h, 40h, 51h, 8Dh, 4Ch, 24h, 24h, 89h, 6Ch, 24h, 3Ch, 0E8h, 0ADh
    db 91h, 53h, 00h, 8Bh, 54h, 24h, 44h, 8Bh, 02h, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 89h
    db 44h, 24h, 24h, 8Bh, 86h, 0F4h, 75h, 01h, 00h, 89h, 4Ch, 24h, 28h, 89h, 54h, 24h
    db 2Ch, 8Bh, 18h, 6Ah, 18h, 0E8h, 36h, 0FAh, 4Dh, 00h, 8Bh, 0F0h, 8Dh, 7Eh, 08h, 83h
    db 0C4h, 04h, 89h, 7Ch, 24h, 40h, 89h, 7Ch, 24h, 44h, 3Bh, 0FDh, 0C6h, 44h, 24h, 38h
    db 01h, 74h, 21h, 8Dh, 4Ch, 24h, 20h, 51h, 8Bh, 0CFh, 0E8h, 31h, 90h, 53h, 00h, 8Bh
    db 54h, 24h, 24h, 89h, 57h, 04h, 8Bh, 44h, 24h, 28h, 89h, 47h, 08h, 8Bh, 4Ch, 24h
    db 2Ch, 89h, 4Fh, 0Ch, 8Bh, 43h, 04h, 89h, 1Eh, 89h, 46h, 04h, 89h, 30h, 8Dh, 4Ch
    db 24h, 20h, 89h, 73h, 04h, 0C7h, 44h, 24h, 38h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0DEh, 8Dh
    db 53h, 00h, 8Bh, 4Ch, 24h, 30h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh
    db 5Bh, 83h, 0C4h, 2Ch, 0C2h, 08h, 00h, 8Bh, 44h, 24h, 10h, 8Bh, 4Ch, 24h, 14h, 90h
    db 8Dh, 78h, 08h, 8Bh, 43h, 08h, 85h, 0C0h, 0Fh, 0B7h, 0E9h, 74h, 06h, 0Fh, 0B7h, 50h
    db 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h
    db 01h, 3Bh, 0D5h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CDh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh
    db 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D5h, 8Bh, 0C2h, 85h, 0C0h, 74h, 11h
    db 8Bh, 1Bh, 3Bh, 5Ch, 24h, 18h, 75h, 0AFh, 8Bh, 74h, 24h, 1Ch, 0E9h, 0FAh, 0FEh, 0FFh
    db 0FFh, 8Bh, 44h, 24h, 44h, 85h, 0C0h, 74h, 28h, 8Bh, 08h, 83h, 0C3h, 0Ch, 89h, 0Bh
    db 8Bh, 50h, 04h, 89h, 53h, 04h, 8Bh, 40h, 08h, 89h, 43h, 08h, 8Bh, 4Ch, 24h, 30h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 2Ch, 0C2h, 08h
    db 00h, 8Bh, 4Bh, 04h, 8Bh, 03h, 89h, 01h, 89h, 48h, 04h, 8Dh, 4Bh, 08h, 0E8h, 2Dh
    db 8Dh, 53h, 00h, 6Ah, 18h, 53h, 0E8h, 0D5h, 0F9h, 4Dh, 00h, 8Bh, 4Ch, 24h, 38h, 83h
    db 0C4h, 08h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 2Ch
    db 0C2h, 08h, 00h
?d_0034ea70@@YAXXZ ENDP

; ghidra: FUN_0074ece0  retail @ 0x0034ECE0 size 146
public ?d_0034ece0@@YAXXZ
?d_0034ece0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0BBh, 90h, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 57h, 8Bh, 7Ch, 24h, 18h, 85h, 0FFh, 8Bh, 0F1h, 74h
    db 5Eh, 8Bh, 46h, 0Ch, 85h, 0C0h, 75h, 30h, 6Ah, 0Ch, 0E8h, 21h, 32h, 53h, 00h, 83h
    db 0C4h, 04h, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 09h, 8Bh, 0C8h, 0E8h, 0FFh, 0DBh, 0CBh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0C7h, 44h, 24h
    db 10h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 46h, 0Ch, 8Bh, 4Fh, 04h, 85h, 0C9h, 74h, 07h, 0E8h
    db 77h, 35h, 0CBh, 0FFh, 0EBh, 02h, 8Bh, 0C7h, 8Bh, 4Eh, 0Ch, 89h, 44h, 24h, 18h, 8Dh
    db 44h, 24h, 18h, 50h, 0E8h, 0B8h, 83h, 0CCh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 89h, 08h, 8Bh
    db 4Ch, 24h, 08h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h
?d_0034ece0@@YAXXZ ENDP

; ghidra: FUN_0074ef80  retail @ 0x0034EF80 size 379
public ?d_0034ef80@@YAXXZ
?d_0034ef80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 19h, 91h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 1Ch, 53h, 55h, 8Bh, 0A9h, 0F8h, 75h, 01h, 00h
    db 56h, 8Dh, 0B1h, 0F8h, 75h, 01h, 00h, 8Bh, 89h, 0FCh, 75h, 01h, 00h, 3Bh, 0E9h, 57h
    db 89h, 74h, 24h, 18h, 89h, 4Ch, 24h, 14h, 74h, 77h, 8Bh, 44h, 24h, 3Ch, 8Bh, 38h
    db 89h, 7Ch, 24h, 10h, 0EBh, 0Ah, 8Bh, 7Ch, 24h, 10h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0DBh, 0BFh
    db 8Bh, 38h, 07h, 01h, 8Bh, 45h, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh
    db 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh
    db 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h
    db 0D8h, 0FFh, 85h, 0C0h, 75h, 0Ch, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 0Fh, 84h, 0C4h, 00h
    db 00h, 00h, 8Bh, 44h, 24h, 14h, 83h, 0C5h, 10h, 3Bh, 0E8h, 75h, 99h, 8Bh, 74h, 24h
    db 18h, 33h, 0FFh, 89h, 7Ch, 24h, 1Ch, 89h, 7Ch, 24h, 20h, 89h, 7Ch, 24h, 28h, 8Bh
    db 4Ch, 24h, 48h, 51h, 8Dh, 4Ch, 24h, 2Ch, 89h, 7Ch, 24h, 38h, 0E8h, 3Fh, 8Ch, 53h
    db 00h, 8Bh, 44h, 24h, 3Ch, 8Bh, 54h, 24h, 44h, 50h, 8Dh, 4Ch, 24h, 20h, 89h, 54h
    db 24h, 28h, 0E8h, 29h, 8Ch, 53h, 00h, 8Bh, 4Ch, 24h, 40h, 51h, 8Dh, 4Ch, 24h, 24h
    db 0E8h, 1Bh, 8Ch, 53h, 00h, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 74h, 23h, 89h, 44h, 24h
    db 3Ch, 89h, 44h, 24h, 48h, 3Bh, 0C7h, 0C6h, 44h, 24h, 34h, 01h, 74h, 0Ch, 8Dh, 54h
    db 24h, 1Ch, 52h, 8Bh, 0C8h, 0E8h, 96h, 18h, 0CFh, 0FFh, 83h, 46h, 04h, 10h, 0EBh, 16h
    db 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 44h, 51h, 8Dh, 54h, 24h, 28h, 52h, 50h, 8Bh
    db 0CEh, 0E8h, 0A2h, 0FBh, 0CDh, 0FFh, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 34h, 03h, 00h
    db 00h, 00h, 0E8h, 79h, 88h, 53h, 00h, 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 34h, 02h
    db 0E8h, 6Bh, 88h, 53h, 00h, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 44h, 24h, 34h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 5Ah, 88h, 53h, 00h, 8Bh, 4Ch, 24h, 2Ch, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 28h, 0C2h, 10h, 00h
?d_0034ef80@@YAXXZ ENDP

; ghidra: FUN_0074f160  retail @ 0x0034F160 size 829
_TEXT ENDS
_TEXT$d0074f160 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0074F160 size 829
public ?d_0034f160@@YAXXZ
?d_0034f160@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01019158
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 010h, 053h, 056h, 057h, 08Bh, 0F1h, 033h, 0DBh, 068h
    dd g_Va010E1FD0
    db 08Dh, 04Ch, 024h, 030h, 089h, 05Ch, 024h, 028h
    call ?j_0004B01A@@YAXXZ
    db 085h, 0C0h, 075h, 03Bh, 08Bh, 0BEh, 08Ch, 070h, 001h, 000h, 03Bh, 0FBh, 08Dh, 04Ch, 024h, 02Ch
    db 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh, 00Fh, 085h, 094h, 000h, 000h, 000h, 08Bh, 0B6h
    db 094h, 070h, 001h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Dh, 044h, 024h, 02Ch, 050h, 08Dh, 04Ch, 024h, 010h, 051h
    db 08Bh, 0CEh
    call ?j_00036336@@YAXXZ
    db 08Bh, 0BEh, 08Ch, 070h, 001h, 000h, 03Bh, 0FBh, 0C6h, 044h, 024h, 024h, 001h, 074h, 06Eh, 08Bh
    db 047h, 004h, 03Bh, 0C3h, 0B9h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 074h, 003h, 08Dh, 048h, 010h, 08Dh, 054h, 024h, 00Ch, 052h
    call ?j_000220c5@@YAXXZ
    db 085h, 0C0h, 075h, 051h, 08Bh, 047h, 004h, 03Bh, 0C3h, 0B9h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 074h, 003h, 08Dh, 048h, 014h, 08Dh, 044h, 024h, 02Ch, 050h
    call ?j_000220c5@@YAXXZ
    db 085h, 0C0h, 075h, 034h, 08Dh, 04Ch, 024h, 00Ch, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 02Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 0C7h, 05Fh, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Bh, 0BEh, 094h, 070h, 001h, 000h, 03Bh, 0FBh, 074h, 03Ah
    db 08Bh, 047h, 004h, 03Bh, 0C3h, 0B9h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 074h, 003h, 08Dh, 048h, 010h, 08Dh, 054h, 024h, 00Ch, 052h
    call ?j_000220c5@@YAXXZ
    db 085h, 0C0h, 075h, 01Dh, 08Bh, 047h, 004h, 03Bh, 0C3h, 0B9h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 074h, 003h, 08Dh, 048h, 014h, 08Dh, 044h, 024h, 02Ch, 050h
    call ?j_000220c5@@YAXXZ
    db 085h, 0C0h, 074h, 088h, 08Dh, 04Ch, 024h, 02Ch, 051h, 08Dh, 054h, 024h, 010h, 052h, 08Dh, 04Ch
    db 024h, 01Ch
    call ?j_00047b59@@YAXXZ
    db 08Dh, 044h, 024h, 014h, 08Dh, 0BEh, 064h, 060h, 001h, 000h, 050h, 08Bh, 0CFh, 0C6h, 044h, 024h
    db 028h, 002h
    call ?j_0003263c@@YAXXZ
    db 03Bh, 007h, 074h, 053h, 08Bh, 048h, 018h, 051h, 08Bh, 00Dh
    dd ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A
    call ?j_00044c2e@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 08Bh, 0F0h, 0C6h, 044h, 024h, 024h, 001h
    call ?j_000444ea@@YAXXZ
    db 08Dh, 04Ch, 024h, 00Ch, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 024h, 001h
    call ?j_000444ea@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A
    db 08Dh, 054h, 024h, 02Ch, 052h, 08Dh, 044h, 024h, 010h, 050h
    call ?j_00040a39@@YAXXZ
    db 08Bh, 0F8h, 03Bh, 0FBh, 00Fh, 084h, 019h, 001h, 000h, 000h, 0F6h, 047h, 018h, 001h, 074h, 034h
    db 08Bh, 0B7h, 074h, 002h, 000h, 000h, 03Bh, 0F3h, 00Fh, 084h, 005h, 001h, 000h, 000h, 08Ah, 046h
    db 031h, 03Ah, 0C3h, 075h, 084h, 038h, 05Ch, 024h, 030h, 00Fh, 084h, 0F4h, 000h, 000h, 000h, 03Ah
    db 0C3h, 00Fh, 085h, 0B8h, 000h, 000h, 000h, 0C6h, 046h, 032h, 001h, 0C6h, 046h, 031h, 001h, 0E9h
    db 0ABh, 000h, 000h, 000h, 08Bh, 0CFh
    call ?j_0003de8d@@YAXXZ
    db 083h, 0F8h, 001h, 07Eh, 074h, 0A1h
    dd g_Va012F0788
    db 083h, 0F8h, 00Ah, 07Dh, 06Ah, 08Bh, 0D0h, 042h, 068h
    dd g_Va010E7F50
    db 08Dh, 04Ch, 024h, 014h, 089h, 015h
    dd g_Va012F0788
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 053h, 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CEh, 0C6h, 044h, 024h, 02Ch, 003h
    call ?j_00028ce0@@YAXXZ
    db 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 024h, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 054h, 024h, 02Ch, 052h, 08Dh, 044h, 024h, 010h, 050h, 08Dh, 04Ch, 024h, 018h, 051h
    call ?j_00029b6d@@YAXXZ
    db 083h, 0C4h, 00Ch, 053h, 050h, 08Bh, 0CEh, 0C6h, 044h, 024h, 02Ch, 004h
    call ?j_00028ce0@@YAXXZ
    db 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 024h, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 0BFh, 074h, 002h, 000h, 000h, 03Bh, 0FBh, 00Fh, 085h, 012h, 0FEh, 0FFh, 0FFh, 038h, 05Ch
    db 024h, 030h, 074h, 04Bh, 08Bh, 00Dh
    dd ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A
    db 08Dh, 054h, 024h, 02Ch, 052h, 08Dh, 044h, 024h, 010h, 050h
    call ?j_00003747@@YAXXZ
    db 08Bh, 0F0h, 08Dh, 04Ch, 024h, 00Ch, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Dh, 04Ch, 024h, 00Ch, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 01Ch, 05Fh, 05Eh, 033h, 0C0h, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h
?d_0034f160@@YAXXZ ENDP
_TEXT$d0074f160 ENDS
_TEXT SEGMENT

; ghidra: FUN_0074f570  retail @ 0x0034F570 size 420
public ?d_0034f570@@YAXXZ
?d_0034f570@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 90h, 91h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 0F1h, 68h, 94h, 7Fh, 0Eh
    db 01h, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0E8h, 78h, 0BAh
    db 0CFh, 0FFh, 85h, 0C0h, 75h, 3Ah, 8Bh, 0BEh, 90h, 70h, 01h, 00h, 85h, 0FFh, 8Dh, 4Ch
    db 24h, 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0Fh, 85h, 3Ah, 01h, 00h, 00h
    db 8Bh, 0B6h, 98h, 70h, 01h, 00h, 0E8h, 75h, 83h, 53h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
    db 8Dh, 44h, 24h, 24h, 50h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0E8h, 45h, 6Dh, 0CEh
    db 0FFh, 8Dh, 54h, 24h, 08h, 52h, 8Dh, 4Ch, 24h, 10h, 0C6h, 44h, 24h, 20h, 01h, 0E8h
    db 5Ch, 85h, 53h, 00h, 8Dh, 44h, 24h, 24h, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h
    db 20h, 02h, 0E8h, 49h, 85h, 53h, 00h, 8Dh, 4Ch, 24h, 0Ch, 8Dh, 0BEh, 58h, 60h, 01h
    db 00h, 51h, 8Bh, 0CFh, 0E8h, 70h, 0ECh, 0CDh, 0FFh, 3Bh, 07h, 74h, 53h, 8Bh, 50h, 18h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 52h, 0E8h, 17h, 0FCh, 0CCh, 0FFh, 8Dh, 4Ch, 24h, 0Ch
    db 8Bh, 0F0h, 0C6h, 44h, 24h, 1Ch, 01h, 0E8h, 9Eh, 4Eh, 0CFh, 0FFh, 8Dh, 4Ch, 24h, 08h
    db 0C6h, 44h, 24h, 1Ch, 00h, 0E8h, 0E6h, 82h, 53h, 00h, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h
    db 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D5h, 82h, 53h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
    db 8Dh, 4Ch, 24h, 0Ch, 0C6h, 44h, 24h, 1Ch, 01h, 0E8h, 5Ch, 4Eh, 0CFh, 0FFh, 8Dh, 4Ch
    db 24h, 08h, 0C6h, 44h, 24h, 1Ch, 00h, 0E8h, 0A4h, 82h, 53h, 00h, 8Bh, 0BEh, 9Ch, 70h
    db 01h, 00h, 8Bh, 0B6h, 0A0h, 70h, 01h, 00h, 3Bh, 0FEh, 74h, 19h, 8Dh, 64h, 24h, 00h
    db 57h, 8Dh, 4Ch, 24h, 28h, 0E8h, 0Bh, 2Ah, 0CDh, 0FFh, 85h, 0C0h, 74h, 2Dh, 83h, 0C7h
    db 08h, 3Bh, 0FEh, 75h, 0EBh, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 6Ah, 82h, 53h, 00h, 5Fh, 33h, 0C0h, 5Eh, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 8Bh, 7Fh, 04h, 0C7h, 44h
    db 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 24h, 0E8h, 41h, 82h, 53h, 00h, 8Bh
    db 4Ch, 24h, 14h, 8Bh, 0C7h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 18h, 0C2h, 04h, 00h
?d_0034f570@@YAXXZ ENDP

; ghidra: FUN_0074f7b0  retail @ 0x0034F7B0 size 165
public ?d_0034f7b0@@YAXXZ
?d_0034f7b0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0B8h, 91h, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 74h, 75h, 8Bh
    db 44h, 24h, 18h, 83h, 0C0h, 10h, 50h, 8Dh, 4Ch, 24h, 20h, 0E8h, 80h, 83h, 53h, 00h
    db 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 43h
    db 66h, 83h, 78h, 04h, 00h, 74h, 3Ch, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 11h, 8Dh
    db 44h, 24h, 1Ch, 50h, 0FFh, 52h, 50h, 8Bh, 0F0h, 85h, 0F6h, 75h, 0Eh, 8Dh, 4Ch, 24h
    db 1Ch, 51h, 8Bh, 0CFh, 0E8h, 35h, 5Bh, 0CBh, 0FFh, 0EBh, 18h, 8Dh, 56h, 04h, 8Dh, 4Fh
    db 04h, 52h, 0E8h, 69h, 84h, 53h, 00h, 83h, 0C6h, 08h, 56h, 8Dh, 4Fh, 08h, 0E8h, 30h
    db 82h, 0CBh, 0FFh, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 0FCh, 80h, 53h, 00h, 8Bh, 4Ch, 24h, 08h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Eh, 83h, 0C4h, 0Ch, 0C3h
?d_0034f7b0@@YAXXZ ENDP

; ghidra: FUN_0074f950  retail @ 0x0034F950 size 95
public ?d_0034f950@@YAXXZ
?d_0034f950@@YAXXZ PROC
    db 8Bh, 15h, 28h, 0F4h, 2Eh, 01h, 85h, 0D2h, 74h, 54h, 8Bh, 42h, 28h, 57h, 33h, 0FFh
    db 85h, 0C0h, 7Eh, 49h, 56h, 33h, 0F6h, 85h, 0F6h, 7Ch, 0Ah, 3Bh, 0F8h, 7Dh, 06h, 8Dh
    db 4Ch, 16h, 2Ch, 0EBh, 02h, 33h, 0C9h, 85h, 0F6h, 8Bh, 49h, 08h, 7Ch, 0Ah, 3Bh, 0F8h
    db 7Dh, 06h, 8Dh, 44h, 16h, 2Ch, 0EBh, 02h, 33h, 0C0h, 85h, 0C9h, 0C7h, 40h, 08h, 00h
    db 00h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 15h, 28h, 0F4h, 2Eh
    db 01h, 8Bh, 42h, 28h, 47h, 83h, 0C6h, 18h, 3Bh, 0F8h, 7Ch, 0BBh, 5Eh, 5Fh, 0C3h
?d_0034f950@@YAXXZ ENDP

; ghidra: FUN_0074fa20  retail @ 0x0034FA20 size 19
public ?d_0034fa20@@YAXXZ
?d_0034fa20@@YAXXZ PROC
    db 8Bh, 41h, 08h, 0C7h, 01h, 0D0h, 0C7h, 07h, 01h, 8Bh, 49h, 04h, 50h, 0E8h, 0E8h, 8Ch
    db 0CBh, 0FFh, 0C3h
?d_0034fa20@@YAXXZ ENDP

; ghidra: FUN_0074fa40  retail @ 0x0034FA40 size 19
public ?d_0034fa40@@YAXXZ
?d_0034fa40@@YAXXZ PROC
    db 8Bh, 41h, 08h, 0C7h, 01h, 0D0h, 0C7h, 07h, 01h, 8Bh, 49h, 04h, 50h, 0E8h, 0C8h, 8Ch
    db 0CBh, 0FFh, 0C3h
?d_0034fa40@@YAXXZ ENDP

; ghidra: FUN_0074fc90  retail @ 0x0034FC90 size 60
public ?d_0034fc90@@YAXXZ
?d_0034fc90@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 85h, 0C9h, 0C7h, 06h, 0D8h, 84h, 0Eh, 01h, 74h, 0Dh
    db 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 4Eh, 04h
    db 85h, 0C9h, 74h, 16h, 8Bh, 71h, 04h, 0C7h, 41h, 04h, 00h, 00h, 00h, 00h, 8Bh, 11h
    db 6Ah, 01h, 0FFh, 12h, 85h, 0F6h, 8Bh, 0CEh, 75h, 0EAh, 5Eh, 0C3h
?d_0034fc90@@YAXXZ ENDP

; ghidra: FUN_0074fe00  retail @ 0x0034FE00 size 83
public ?d_0034fe00@@YAXXZ
?d_0034fe00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 89h, 06h, 8Ah, 4Fh, 04h, 88h
    db 4Eh, 04h, 8Bh, 57h, 08h, 8Dh, 4Fh, 10h, 89h, 56h, 08h, 8Bh, 47h, 0Ch, 51h, 8Dh
    db 4Eh, 10h, 89h, 46h, 0Ch, 0E8h, 66h, 7Eh, 53h, 00h, 8Dh, 57h, 14h, 8Bh, 0Ah, 8Dh
    db 46h, 14h, 89h, 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 89h, 50h, 08h
    db 8Bh, 47h, 20h, 89h, 46h, 20h, 8Bh, 4Fh, 24h, 5Fh, 89h, 4Eh, 24h, 8Bh, 0C6h, 5Eh
    db 0C2h, 04h, 00h
?d_0034fe00@@YAXXZ ENDP

; ghidra: FUN_0074fee0  retail @ 0x0034FEE0 size 41
public ?d_0034fee0@@YAXXZ
?d_0034fee0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 33h, 0D2h, 89h, 50h, 08h, 89h, 50h, 04h, 89h, 10h, 83h, 39h
    db 10h, 75h, 13h, 83h, 0C1h, 14h, 8Bh, 11h, 89h, 10h, 8Bh, 51h, 04h, 89h, 50h, 04h
    db 8Bh, 49h, 08h, 89h, 48h, 08h, 0C2h, 04h, 00h
?d_0034fee0@@YAXXZ ENDP

; ghidra: FUN_00750e00  retail @ 0x00350E00 size 38
public ?d_00350e00@@YAXXZ
?d_00350e00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 29h, 12h, 0CDh, 0FFh
    db 0F6h, 44h, 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 93h, 10h, 53h, 00h, 83h, 0C4h, 04h
    db 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00350e00@@YAXXZ ENDP

; ghidra: FUN_00750e30  retail @ 0x00350E30 size 38
public ?d_00350e30@@YAXXZ
?d_00350e30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 0F8h, 14h, 0CBh, 0FFh
    db 0F6h, 44h, 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 63h, 10h, 53h, 00h, 83h, 0C4h, 04h
    db 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00350e30@@YAXXZ ENDP

; ghidra: FUN_00751230  retail @ 0x00351230 size 8
public ?d_00351230@@YAXXZ
?d_00351230@@YAXXZ PROC
    db 83h, 0C1h, 10h, 0E9h, 08h, 67h, 53h, 00h
?d_00351230@@YAXXZ ENDP

; ghidra: FUN_00751970  retail @ 0x00351970 size 8
public ?d_00351970@@YAXXZ
?d_00351970@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0C8h, 5Fh, 53h, 00h
?d_00351970@@YAXXZ ENDP

; ghidra: FUN_00751980  retail @ 0x00351980 size 8
public ?d_00351980@@YAXXZ
?d_00351980@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0B8h, 5Fh, 53h, 00h
?d_00351980@@YAXXZ ENDP

; ghidra: FUN_00752550  retail @ 0x00352550 size 109
public ?d_00352550@@YAXXZ
?d_00352550@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 92h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 0A1h, 6Ch, 07h, 2Fh, 01h, 85h, 0C0h, 74h, 3Fh, 8Bh
    db 44h, 24h, 14h, 8Bh, 04h, 85h, 0C0h, 3Dh, 2Bh, 01h, 50h, 8Dh, 4Ch, 24h, 04h, 0E8h
    db 3Ch, 66h, 53h, 00h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 11h, 8Dh, 04h, 24h, 50h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0FFh, 92h, 0A0h, 00h, 00h, 00h, 8Dh, 0Ch
    db 24h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 92h, 53h, 53h, 00h, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00352550@@YAXXZ ENDP

; ghidra: FUN_007525e0  retail @ 0x003525E0 size 160
public ?d_003525e0@@YAXXZ
?d_003525e0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 6Ah, 0FFh, 68h, 0A6h, 92h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h
    db 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 75h, 08h
    db 83h, 3Eh, 00h, 57h, 8Bh, 0F9h, 89h, 65h, 0F0h, 89h, 7Dh, 0ECh, 74h, 24h, 6Ah, 0Ch
    db 0E8h, 1Bh, 0F9h, 52h, 00h, 83h, 0C4h, 04h, 89h, 45h, 08h, 85h, 0C0h, 0C7h, 45h, 0FCh
    db 00h, 00h, 00h, 00h, 74h, 0Ch, 8Bh, 0Eh, 51h, 8Bh, 0C8h, 0E8h, 0DDh, 6Ah, 0CEh, 0FFh
    db 0EBh, 02h, 33h, 0C0h, 89h, 07h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 45h, 0FCh, 01h, 00h
    db 00h, 00h, 74h, 4Ah, 6Ah, 0Ch, 0E8h, 0E5h, 0F8h, 52h, 00h, 8Bh, 0C8h, 83h, 0C4h, 04h
    db 89h, 4Dh, 08h, 85h, 0C9h, 0C6h, 45h, 0FCh, 02h, 74h, 33h, 8Bh, 56h, 04h, 52h, 0E8h
    db 79h, 0A9h, 0CEh, 0FFh, 0EBh, 2Ah, 8Bh, 45h, 0ECh, 8Bh, 30h, 85h, 0F6h, 74h, 16h, 8Bh
    db 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 0BDh, 0F9h, 0CCh, 0FFh, 56h, 0E8h, 2Eh, 0F8h
?d_003525e0@@YAXXZ ENDP

; ghidra: FUN_007526e0  retail @ 0x003526E0 size 64
public ?d_003526e0@@YAXXZ
?d_003526e0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 04h, 85h, 0F6h, 74h, 16h, 8Bh, 0Eh, 85h, 0C9h, 74h
    db 07h, 6Ah, 01h, 0E8h, 40h, 0FCh, 0CAh, 0FFh, 56h, 0E8h, 0B2h, 0F7h, 52h, 00h, 83h, 0C4h
    db 04h, 8Bh, 37h, 85h, 0F6h, 74h, 16h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h
    db 25h, 0F9h, 0CCh, 0FFh, 56h, 0E8h, 96h, 0F7h, 52h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 0C3h
?d_003526e0@@YAXXZ ENDP

; ghidra: FUN_007527b0  retail @ 0x003527B0 size 71
public ?d_003527b0@@YAXXZ
?d_003527b0@@YAXXZ PROC
    db 8Bh, 41h, 28h, 83h, 0F8h, 0FFh, 53h, 0B3h, 01h, 74h, 1Ah, 8Bh, 51h, 18h, 8Bh, 0FFh
    db 8Dh, 04h, 80h, 0C1h, 0E0h, 02h, 88h, 5Ch, 10h, 0Ch, 8Bh, 51h, 18h, 8Bh, 04h, 10h
    db 83h, 0F8h, 0FFh, 75h, 0EBh, 8Bh, 41h, 48h, 83h, 0F8h, 0FFh, 74h, 18h, 8Bh, 51h, 38h
    db 8Dh, 04h, 80h, 0C1h, 0E0h, 02h, 88h, 5Ch, 10h, 0Ch, 8Bh, 51h, 38h, 8Bh, 04h, 10h
    db 83h, 0F8h, 0FFh, 75h, 0EBh, 5Bh, 0C3h
?d_003527b0@@YAXXZ ENDP

; ghidra: FUN_00752a00  retail @ 0x00352A00 size 134
public ?d_00352a00@@YAXXZ
?d_00352a00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0EBh, 92h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 6Ah, 10h, 8Bh, 0F9h, 0E8h, 0Fh, 0F5h, 52h
    db 00h, 8Bh, 0F0h, 83h, 0C4h, 04h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h
    db 00h, 00h, 00h, 00h, 74h, 3Dh, 85h, 0FFh, 74h, 05h, 8Dh, 47h, 04h, 0EBh, 02h, 33h
    db 0C0h, 50h, 8Dh, 4Eh, 04h, 0E8h, 0C8h, 21h, 0CDh, 0FFh, 0C7h, 06h, 5Ch, 85h, 0Eh, 01h
    db 8Ah, 47h, 0Ch, 88h, 46h, 0Ch, 8Ah, 4Fh, 0Dh, 5Fh, 88h, 4Eh, 0Dh, 0C6h, 46h, 0Eh
    db 00h, 8Bh, 0C6h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 33h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00352a00@@YAXXZ ENDP

; ghidra: FUN_00752c20  retail @ 0x00352C20 size 156
public ?d_00352c20@@YAXXZ
?d_00352c20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 54h, 93h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 8Ch
    db 85h, 0Eh, 01h, 8Bh, 4Eh, 1Ch, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 04h, 00h, 00h, 00h
    db 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 06h, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 4Eh, 24h, 85h, 0C9h, 74h, 06h, 8Bh, 01h, 6Ah, 01h
    db 0FFh, 10h, 8Dh, 4Eh, 30h, 0C6h, 44h, 24h, 10h, 03h, 0E8h, 0C1h, 4Ch, 53h, 00h, 8Dh
    db 4Eh, 0Ch, 0C6h, 44h, 24h, 10h, 02h, 0E8h, 0B4h, 4Ch, 53h, 00h, 8Dh, 4Eh, 08h, 0C6h
    db 44h, 24h, 10h, 01h, 0E8h, 0A7h, 4Ch, 53h, 00h, 8Dh, 4Eh, 04h, 0C6h, 44h, 24h, 10h
    db 00h, 0E8h, 9Ah, 4Ch, 53h, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 44h, 37h, 07h, 01h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00352c20@@YAXXZ ENDP

; ghidra: FUN_00752d20  retail @ 0x00352D20 size 106
public ?d_00352d20@@YAXXZ
?d_00352d20@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 08h, 33h, 0DBh, 85h, 0C0h, 0C7h, 07h, 0DCh, 84h
    db 0Eh, 01h, 7Eh, 2Ch, 8Dh, 77h, 0Ch, 55h, 8Bh, 2Eh, 85h, 0EDh, 74h, 10h, 8Bh, 0CDh
    db 0E8h, 0F5h, 18h, 0CEh, 0FFh, 55h, 0E8h, 65h, 0F1h, 52h, 00h, 83h, 0C4h, 04h, 0C7h, 06h
    db 00h, 00h, 00h, 00h, 8Bh, 47h, 08h, 43h, 83h, 0C6h, 04h, 3Bh, 0D8h, 7Ch, 0D9h, 5Dh
    db 8Bh, 7Fh, 3Ch, 85h, 0FFh, 74h, 1Fh, 8Bh, 0CFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 71h, 3Ch, 0C7h, 41h, 3Ch, 00h, 00h, 00h, 00h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h
    db 85h, 0F6h, 8Bh, 0CEh, 75h, 0EAh, 5Fh, 5Eh, 5Bh, 0C3h
?d_00352d20@@YAXXZ ENDP

; ghidra: FUN_00754220  retail @ 0x00354220 size 215
public ?d_00354220@@YAXXZ
?d_00354220@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 33h, 0DBh, 33h, 0EDh, 3Bh, 0C3h, 57h
    db 7Eh, 2Fh, 8Dh, 7Eh, 0Ch, 8Bh, 07h, 3Bh, 0C3h, 89h, 44h, 24h, 10h, 74h, 15h, 8Dh
    db 48h, 10h, 0E8h, 0F9h, 36h, 53h, 00h, 8Bh, 44h, 24h, 10h, 50h, 0E8h, 5Fh, 0DCh, 52h
    db 00h, 83h, 0C4h, 04h, 89h, 1Fh, 8Bh, 46h, 08h, 45h, 83h, 0C7h, 04h, 3Bh, 0E8h, 7Ch
    db 0D4h, 8Bh, 44h, 24h, 18h, 89h, 46h, 04h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 11h
    db 50h, 0FFh, 52h, 28h, 8Bh, 0C8h, 8Bh, 41h, 44h, 33h, 0FFh, 3Bh, 0C3h, 89h, 4Ch, 24h
    db 10h, 89h, 46h, 08h, 7Eh, 69h, 83h, 0C1h, 48h, 8Dh, 6Eh, 0Ch, 89h, 4Ch, 24h, 18h
    db 6Ah, 28h, 0E8h, 99h, 0DCh, 52h, 00h, 83h, 0C4h, 04h, 3Bh, 0C3h, 74h, 36h, 3Bh, 0FBh
    db 7Ch, 11h, 8Bh, 4Ch, 24h, 10h, 3Bh, 79h, 44h, 7Dh, 08h, 8Bh, 54h, 24h, 18h, 8Bh
    db 0Ah, 0EBh, 02h, 33h, 0C9h, 89h, 08h, 88h, 58h, 04h, 89h, 58h, 08h, 89h, 58h, 0Ch
    db 89h, 58h, 10h, 89h, 58h, 20h, 89h, 58h, 24h, 89h, 58h, 14h, 89h, 58h, 18h, 89h
    db 58h, 1Ch, 0EBh, 02h, 33h, 0C0h, 8Bh, 54h, 24h, 18h, 89h, 45h, 00h, 8Bh, 46h, 08h
    db 47h, 83h, 0C2h, 04h, 83h, 0C5h, 04h, 3Bh, 0F8h, 89h, 54h, 24h, 18h, 7Ch, 0A1h, 5Fh
    db 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_00354220@@YAXXZ ENDP

; ghidra: FUN_00754330  retail @ 0x00354330 size 106
public ?d_00354330@@YAXXZ
?d_00354330@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 08h, 33h, 0DBh, 85h, 0C0h, 0C7h, 07h, 0E0h, 84h
    db 0Eh, 01h, 7Eh, 2Ch, 8Dh, 77h, 0Ch, 55h, 8Bh, 2Eh, 85h, 0EDh, 74h, 10h, 8Bh, 0CDh
    db 0E8h, 0E5h, 02h, 0CEh, 0FFh, 55h, 0E8h, 55h, 0DBh, 52h, 00h, 83h, 0C4h, 04h, 0C7h, 06h
    db 00h, 00h, 00h, 00h, 8Bh, 47h, 08h, 43h, 83h, 0C6h, 04h, 3Bh, 0D8h, 7Ch, 0D9h, 5Dh
    db 8Bh, 7Fh, 3Ch, 85h, 0FFh, 74h, 1Fh, 8Bh, 0CFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 71h, 3Ch, 0C7h, 41h, 3Ch, 00h, 00h, 00h, 00h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h
    db 85h, 0F6h, 8Bh, 0CEh, 75h, 0EAh, 5Fh, 5Eh, 5Bh, 0C3h
?d_00354330@@YAXXZ ENDP

; ghidra: FUN_00754530  retail @ 0x00354530 size 65
public ?d_00354530@@YAXXZ
?d_00354530@@YAXXZ PROC
    db 56h, 8Bh, 31h, 85h, 0F6h, 74h, 38h, 8Bh, 49h, 08h, 2Bh, 0CEh, 0B8h, 67h, 66h, 66h
    db 66h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 80h
    db 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 50h, 0D9h, 52h, 00h
    db 83h, 0C4h, 04h, 5Eh, 0C3h, 50h, 56h, 0E8h, 84h, 0A0h, 4Dh, 00h, 83h, 0C4h, 08h, 5Eh
    db 0C3h
?d_00354530@@YAXXZ ENDP

; ghidra: FUN_007545c0  retail @ 0x003545C0 size 65
public ?d_003545c0@@YAXXZ
?d_003545c0@@YAXXZ PROC
    db 56h, 8Bh, 31h, 85h, 0F6h, 74h, 38h, 8Bh, 49h, 08h, 2Bh, 0CEh, 0B8h, 67h, 66h, 66h
    db 66h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 80h
    db 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 0C0h, 0D8h, 52h, 00h
    db 83h, 0C4h, 04h, 5Eh, 0C3h, 50h, 56h, 0E8h, 0F4h, 9Fh, 4Dh, 00h, 83h, 0C4h, 08h, 5Eh
    db 0C3h
?d_003545c0@@YAXXZ ENDP

; ghidra: FUN_007546e0  retail @ 0x003546E0 size 203
public ?d_003546e0@@YAXXZ
?d_003546e0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0C1h, 0EBh, 05h, 43h, 55h, 8Dh, 43h, 02h
    db 56h, 89h, 44h, 24h, 0Ch, 83h, 0F8h, 08h, 57h, 8Bh, 0F1h, 0C7h, 44h, 24h, 14h, 08h
    db 00h, 00h, 00h, 8Dh, 44h, 24h, 10h, 77h, 04h, 8Dh, 44h, 24h, 14h, 8Bh, 00h, 85h
    db 0C0h, 89h, 46h, 24h, 74h, 1Fh, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h
    db 0Ah, 0E8h, 0Ah, 0D8h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 10h, 9Eh, 4Dh, 00h
    db 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Eh, 24h, 2Bh, 0CBh, 0D1h, 0E9h, 8Dh, 3Ch
    db 88h, 8Dh, 2Ch, 9Fh, 3Bh, 0FDh, 89h, 46h, 20h, 8Bh, 0DFh, 73h, 19h, 8Dh, 49h, 00h
    db 68h, 80h, 00h, 00h, 00h, 0E8h, 0E6h, 9Dh, 4Dh, 00h, 89h, 03h, 83h, 0C3h, 04h, 83h
    db 0C4h, 04h, 3Bh, 0DDh, 72h, 0EAh, 8Bh, 44h, 24h, 1Ch, 89h, 7Eh, 0Ch, 8Bh, 3Fh, 89h
    db 7Eh, 04h, 83h, 0C5h, 0FCh, 81h, 0C7h, 80h, 00h, 00h, 00h, 89h, 7Eh, 08h, 89h, 6Eh
    db 1Ch, 8Bh, 6Dh, 00h, 89h, 6Eh, 14h, 81h, 0C5h, 80h, 00h, 00h, 00h, 89h, 6Eh, 18h
    db 8Bh, 56h, 04h, 8Bh, 4Eh, 14h, 89h, 16h, 83h, 0E0h, 1Fh, 5Fh, 8Dh, 14h, 81h, 89h
    db 56h, 10h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_003546e0@@YAXXZ ENDP

; ghidra: FUN_00754890  retail @ 0x00354890 size 203
public ?d_00354890@@YAXXZ
?d_00354890@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0C1h, 0EBh, 05h, 43h, 55h, 8Dh, 43h, 02h
    db 56h, 89h, 44h, 24h, 0Ch, 83h, 0F8h, 08h, 57h, 8Bh, 0F1h, 0C7h, 44h, 24h, 14h, 08h
    db 00h, 00h, 00h, 8Dh, 44h, 24h, 10h, 77h, 04h, 8Dh, 44h, 24h, 14h, 8Bh, 00h, 85h
    db 0C0h, 89h, 46h, 24h, 74h, 1Fh, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h
    db 0Ah, 0E8h, 5Ah, 0D6h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 60h, 9Ch, 4Dh, 00h
    db 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Eh, 24h, 2Bh, 0CBh, 0D1h, 0E9h, 8Dh, 3Ch
    db 88h, 8Dh, 2Ch, 9Fh, 3Bh, 0FDh, 89h, 46h, 20h, 8Bh, 0DFh, 73h, 19h, 8Dh, 49h, 00h
    db 68h, 80h, 00h, 00h, 00h, 0E8h, 36h, 9Ch, 4Dh, 00h, 89h, 03h, 83h, 0C3h, 04h, 83h
    db 0C4h, 04h, 3Bh, 0DDh, 72h, 0EAh, 8Bh, 44h, 24h, 1Ch, 89h, 7Eh, 0Ch, 8Bh, 3Fh, 89h
    db 7Eh, 04h, 83h, 0C5h, 0FCh, 81h, 0C7h, 80h, 00h, 00h, 00h, 89h, 7Eh, 08h, 89h, 6Eh
    db 1Ch, 8Bh, 6Dh, 00h, 89h, 6Eh, 14h, 81h, 0C5h, 80h, 00h, 00h, 00h, 89h, 6Eh, 18h
    db 8Bh, 56h, 04h, 8Bh, 4Eh, 14h, 89h, 16h, 83h, 0E0h, 1Fh, 5Fh, 8Dh, 14h, 81h, 89h
    db 56h, 10h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_00354890@@YAXXZ ENDP

; ghidra: FUN_00754a00  retail @ 0x00354A00 size 72
public ?d_00354a00@@YAXXZ
?d_00354a00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 0C7h, 46h, 04h, 44h, 37h, 07h, 01h, 8Bh, 7Eh, 0Ch, 85h, 0FFh
    db 74h, 16h, 8Bh, 0Fh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 19h, 0D9h, 0CAh, 0FFh, 57h
    db 0E8h, 8Bh, 0D4h, 52h, 00h, 83h, 0C4h, 04h, 8Bh, 76h, 08h, 85h, 0F6h, 74h, 16h, 8Bh
    db 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 0FDh, 0D5h, 0CCh, 0FFh, 56h, 0E8h, 6Eh, 0D4h
    db 52h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 0C3h
?d_00354a00@@YAXXZ ENDP

; ghidra: FUN_00754a60  retail @ 0x00354A60 size 8
public ?d_00354a60@@YAXXZ
?d_00354a60@@YAXXZ PROC
    db 83h, 0C1h, 04h, 0E9h, 0E7h, 0AEh, 0CEh, 0FFh
?d_00354a60@@YAXXZ ENDP

; ghidra: FUN_00754bc0  retail @ 0x00354BC0 size 58
public ?d_00354bc0@@YAXXZ
?d_00354bc0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 8Bh, 0F1h, 74h, 05h, 8Dh, 47h, 04h, 0EBh
    db 02h, 33h, 0C0h, 50h, 8Dh, 4Eh, 08h, 0E8h, 36h, 00h, 0CDh, 0FFh, 0C7h, 46h, 04h, 5Ch
    db 85h, 0Eh, 01h, 8Ah, 47h, 0Ch, 88h, 46h, 10h, 8Ah, 4Fh, 0Dh, 5Fh, 88h, 4Eh, 11h
    db 0C6h, 46h, 12h, 00h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00354bc0@@YAXXZ ENDP

; ghidra: FUN_00754c10  retail @ 0x00354C10 size 76
_TEXT ENDS
_TEXT$d00754c10 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00754C10 size 76
public ?d_00354c10@@YAXXZ
?d_00354c10@@YAXXZ PROC
    db 08Bh, 0C1h, 033h, 0C9h, 089h, 008h, 0C7h, 040h, 004h
    dd ??_7BfmeOwnVUQ@@6B@
    db 089h, 048h, 008h, 089h, 048h, 00Ch, 089h, 048h, 010h, 0B2h, 001h, 089h, 048h, 014h, 088h, 050h
    db 018h, 088h, 050h, 019h, 088h, 050h, 01Ah, 088h, 048h, 01Bh, 088h, 050h, 01Ch, 088h, 050h, 01Dh
    db 088h, 050h, 01Eh, 089h, 048h, 020h, 089h, 048h, 024h, 089h, 048h, 028h, 089h, 048h, 02Ch, 088h
    db 048h, 030h, 089h, 048h, 034h, 089h, 048h, 038h, 089h, 048h, 03Ch, 089h, 048h, 040h, 0C3h
?d_00354c10@@YAXXZ ENDP
_TEXT$d00754c10 ENDS
_TEXT SEGMENT

; ghidra: FUN_00754d50  retail @ 0x00354D50 size 203
public ?d_00354d50@@YAXXZ
?d_00354d50@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0C1h, 0EBh, 05h, 43h, 55h, 8Dh, 43h, 02h
    db 56h, 89h, 44h, 24h, 0Ch, 83h, 0F8h, 08h, 57h, 8Bh, 0F1h, 0C7h, 44h, 24h, 14h, 08h
    db 00h, 00h, 00h, 8Dh, 44h, 24h, 10h, 77h, 04h, 8Dh, 44h, 24h, 14h, 8Bh, 00h, 85h
    db 0C0h, 89h, 46h, 24h, 74h, 1Fh, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h
    db 0Ah, 0E8h, 9Ah, 0D1h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 0A0h, 97h, 4Dh, 00h
    db 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Eh, 24h, 2Bh, 0CBh, 0D1h, 0E9h, 8Dh, 3Ch
    db 88h, 8Dh, 2Ch, 9Fh, 3Bh, 0FDh, 89h, 46h, 20h, 8Bh, 0DFh, 73h, 19h, 8Dh, 49h, 00h
    db 68h, 80h, 00h, 00h, 00h, 0E8h, 76h, 97h, 4Dh, 00h, 89h, 03h, 83h, 0C3h, 04h, 83h
    db 0C4h, 04h, 3Bh, 0DDh, 72h, 0EAh, 8Bh, 44h, 24h, 1Ch, 89h, 7Eh, 0Ch, 8Bh, 3Fh, 89h
    db 7Eh, 04h, 83h, 0C5h, 0FCh, 81h, 0C7h, 80h, 00h, 00h, 00h, 89h, 7Eh, 08h, 89h, 6Eh
    db 1Ch, 8Bh, 6Dh, 00h, 89h, 6Eh, 14h, 81h, 0C5h, 80h, 00h, 00h, 00h, 89h, 6Eh, 18h
    db 8Bh, 56h, 04h, 8Bh, 4Eh, 14h, 89h, 16h, 83h, 0E0h, 1Fh, 5Fh, 8Dh, 14h, 81h, 89h
    db 56h, 10h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_00354d50@@YAXXZ ENDP

; ghidra: FUN_00754f00  retail @ 0x00354F00 size 203
public ?d_00354f00@@YAXXZ
?d_00354f00@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0C1h, 0EBh, 05h, 43h, 55h, 8Dh, 43h, 02h
    db 56h, 89h, 44h, 24h, 0Ch, 83h, 0F8h, 08h, 57h, 8Bh, 0F1h, 0C7h, 44h, 24h, 14h, 08h
    db 00h, 00h, 00h, 8Dh, 44h, 24h, 10h, 77h, 04h, 8Dh, 44h, 24h, 14h, 8Bh, 00h, 85h
    db 0C0h, 89h, 46h, 24h, 74h, 1Fh, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h
    db 0Ah, 0E8h, 0EAh, 0CFh, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 0F0h, 95h, 4Dh, 00h
    db 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Eh, 24h, 2Bh, 0CBh, 0D1h, 0E9h, 8Dh, 3Ch
    db 88h, 8Dh, 2Ch, 9Fh, 3Bh, 0FDh, 89h, 46h, 20h, 8Bh, 0DFh, 73h, 19h, 8Dh, 49h, 00h
    db 68h, 80h, 00h, 00h, 00h, 0E8h, 0C6h, 95h, 4Dh, 00h, 89h, 03h, 83h, 0C3h, 04h, 83h
    db 0C4h, 04h, 3Bh, 0DDh, 72h, 0EAh, 8Bh, 44h, 24h, 1Ch, 89h, 7Eh, 0Ch, 8Bh, 3Fh, 89h
    db 7Eh, 04h, 83h, 0C5h, 0FCh, 81h, 0C7h, 80h, 00h, 00h, 00h, 89h, 7Eh, 08h, 89h, 6Eh
    db 1Ch, 8Bh, 6Dh, 00h, 89h, 6Eh, 14h, 81h, 0C5h, 80h, 00h, 00h, 00h, 89h, 6Eh, 18h
    db 8Bh, 56h, 04h, 8Bh, 4Eh, 14h, 89h, 16h, 83h, 0E0h, 1Fh, 5Fh, 8Dh, 14h, 81h, 89h
    db 56h, 10h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_00354f00@@YAXXZ ENDP

; ghidra: FUN_00755050  retail @ 0x00355050 size 107
public ?d_00355050@@YAXXZ
?d_00355050@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C1h, 93h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 74h, 24h, 18h, 89h, 74h, 24h, 04h, 85h
    db 0F6h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 30h, 57h, 8Bh, 7Ch, 24h, 20h
    db 8Bh, 07h, 89h, 06h, 8Bh, 4Fh, 04h, 8Dh, 57h, 08h, 89h, 4Eh, 04h, 52h, 8Dh, 4Eh
    db 08h, 0E8h, 0CAh, 2Ah, 53h, 00h, 8Ah, 47h, 0Ch, 88h, 46h, 0Ch, 66h, 8Bh, 4Fh, 0Eh
    db 66h, 89h, 4Eh, 0Eh, 8Bh, 57h, 10h, 89h, 56h, 10h, 5Fh, 8Bh, 4Ch, 24h, 08h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00355050@@YAXXZ ENDP

; ghidra: FUN_007550f0  retail @ 0x003550F0 size 107
public ?d_003550f0@@YAXXZ
?d_003550f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F1h, 93h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 74h, 24h, 18h, 89h, 74h, 24h, 04h, 85h
    db 0F6h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 30h, 57h, 8Bh, 7Ch, 24h, 20h
    db 8Bh, 07h, 89h, 06h, 8Bh, 4Fh, 04h, 8Dh, 57h, 08h, 89h, 4Eh, 04h, 52h, 8Dh, 4Eh
    db 08h, 0E8h, 2Ah, 2Ah, 53h, 00h, 8Ah, 47h, 0Ch, 88h, 46h, 0Ch, 66h, 8Bh, 4Fh, 0Eh
    db 66h, 89h, 4Eh, 0Eh, 8Bh, 57h, 10h, 89h, 56h, 10h, 5Fh, 8Bh, 4Ch, 24h, 08h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_003550f0@@YAXXZ ENDP

; ghidra: FUN_00755320  retail @ 0x00355320 size 97
public ?d_00355320@@YAXXZ
?d_00355320@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 26h, 8Dh, 04h, 80h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 0F2h, 0CBh, 52h, 00h, 83h, 0C4h
    db 04h, 8Bh, 0E8h, 0EBh, 0Eh, 0E8h, 0F6h, 91h, 4Dh, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh
    db 02h, 33h, 0EDh, 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h
    db 8Bh, 0FDh, 2Bh, 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 0BFh, 18h, 0CEh, 0FFh, 83h, 0C6h
    db 14h, 83h, 0C4h, 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch
    db 00h
?d_00355320@@YAXXZ ENDP

; ghidra: FUN_007553a0  retail @ 0x003553A0 size 97
public ?d_003553a0@@YAXXZ
?d_003553a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 26h, 8Dh, 04h, 80h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 72h, 0CBh, 52h, 00h, 83h, 0C4h
    db 04h, 8Bh, 0E8h, 0EBh, 0Eh, 0E8h, 76h, 91h, 4Dh, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh
    db 02h, 33h, 0EDh, 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h
    db 8Bh, 0FDh, 2Bh, 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 64h, 8Ah, 0CDh, 0FFh, 83h, 0C6h
    db 14h, 83h, 0C4h, 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch
    db 00h
?d_003553a0@@YAXXZ ENDP

; ghidra: FUN_007558a0  retail @ 0x003558A0 size 23
public ?d_003558a0@@YAXXZ
?d_003558a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 04h, 8Dh, 14h, 80h, 8Bh, 41h, 18h, 8Bh, 44h, 90h
    db 10h, 83h, 0C0h, 04h, 0C2h, 04h, 00h
?d_003558a0@@YAXXZ ENDP

; ghidra: FUN_007558c0  retail @ 0x003558C0 size 29
public ?d_003558c0@@YAXXZ
?d_003558c0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 42h, 04h, 8Bh, 49h, 18h, 8Dh, 04h, 80h, 0Fh, 0BFh, 44h
    db 81h, 0Eh, 2Bh, 42h, 08h, 0F7h, 0D8h, 1Bh, 0C0h, 40h, 0C2h, 04h, 00h
?d_003558c0@@YAXXZ ENDP

; ghidra: FUN_00755930  retail @ 0x00355930 size 23
public ?d_00355930@@YAXXZ
?d_00355930@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 04h, 8Dh, 14h, 80h, 8Bh, 41h, 38h, 8Bh, 44h, 90h
    db 10h, 83h, 0C0h, 04h, 0C2h, 04h, 00h
?d_00355930@@YAXXZ ENDP

; ghidra: FUN_00755950  retail @ 0x00355950 size 29
public ?d_00355950@@YAXXZ
?d_00355950@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 42h, 04h, 8Bh, 49h, 38h, 8Dh, 04h, 80h, 0Fh, 0BFh, 44h
    db 81h, 0Eh, 2Bh, 42h, 08h, 0F7h, 0D8h, 1Bh, 0C0h, 40h, 0C2h, 04h, 00h
?d_00355950@@YAXXZ ENDP

; ghidra: FUN_007559c0  retail @ 0x003559C0 size 228
public ?d_003559c0@@YAXXZ
?d_003559c0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 0Ch, 83h, 7Dh, 00h, 00h, 56h, 57h, 8Bh, 0D9h, 8Bh, 0FDh
    db 74h, 7Ch, 8Bh, 37h, 8Bh, 46h, 04h, 8Bh, 4Bh, 18h, 8Bh, 56h, 08h, 8Dh, 04h, 80h
    db 8Dh, 0Ch, 81h, 0Fh, 0BFh, 41h, 0Eh, 3Bh, 0C2h, 8Bh, 49h, 10h, 7Eh, 07h, 2Bh, 0C2h
    db 48h, 8Bh, 09h, 75h, 0FBh, 8Dh, 41h, 04h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 04h, 0EBh
    db 02h, 33h, 0C0h, 50h, 8Bh, 0CBh, 0E8h, 48h, 0B1h, 0CCh, 0FFh, 8Bh, 46h, 04h, 8Dh, 14h
    db 80h, 8Bh, 43h, 18h, 0Fh, 0BFh, 4Ch, 90h, 0Eh, 3Bh, 4Eh, 08h, 74h, 22h, 8Bh, 16h
    db 89h, 17h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h
    db 0E8h, 04h, 0C6h, 0CCh, 0FFh, 56h, 0E8h, 75h, 0C4h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 09h
    db 0C7h, 46h, 08h, 01h, 00h, 00h, 00h, 8Bh, 0FEh, 83h, 3Fh, 00h, 75h, 84h, 8Bh, 45h
    db 04h, 85h, 0C0h, 8Dh, 7Dh, 04h, 74h, 45h, 8Bh, 37h, 8Bh, 46h, 04h, 8Bh, 4Bh, 38h
    db 8Dh, 04h, 80h, 0Fh, 0BFh, 54h, 81h, 0Eh, 3Bh, 56h, 08h, 74h, 22h, 8Bh, 06h, 89h
    db 07h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h
    db 0B4h, 0C8h, 0CAh, 0FFh, 56h, 0E8h, 26h, 0C4h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 09h, 0C7h
    db 46h, 08h, 01h, 00h, 00h, 00h, 8Bh, 0FEh, 83h, 3Fh, 00h, 75h, 0BBh, 5Fh, 5Eh, 5Dh
    db 5Bh, 0C2h, 04h, 00h
?d_003559c0@@YAXXZ ENDP

; ghidra: FUN_00755ae0  retail @ 0x00355AE0 size 262
public ?d_00355ae0@@YAXXZ
?d_00355ae0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 0Ch, 83h, 7Dh, 00h, 00h, 56h, 57h, 8Bh, 0D9h, 8Bh, 0FDh
    db 0Fh, 84h, 8Ah, 00h, 00h, 00h, 8Bh, 37h, 8Bh, 46h, 04h, 8Bh, 4Bh, 18h, 8Bh, 56h
    db 08h, 8Dh, 04h, 80h, 8Dh, 0Ch, 81h, 0Fh, 0BFh, 41h, 0Eh, 3Bh, 0C2h, 8Bh, 49h, 10h
    db 7Eh, 07h, 2Bh, 0C2h, 48h, 8Bh, 09h, 75h, 0FBh, 8Dh, 41h, 04h, 85h, 0C0h, 74h, 05h
    db 83h, 0C0h, 04h, 0EBh, 02h, 33h, 0C0h, 50h, 8Bh, 0CBh, 0E8h, 3Ch, 32h, 0CEh, 0FFh, 8Bh
    db 46h, 04h, 8Dh, 14h, 80h, 8Bh, 43h, 18h, 0Fh, 0BFh, 4Ch, 90h, 0Eh, 8Dh, 04h, 90h
    db 3Bh, 4Eh, 08h, 75h, 07h, 8Ah, 48h, 0Ch, 84h, 0C9h, 74h, 22h, 8Bh, 16h, 89h, 17h
    db 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 0D6h
    db 0C4h, 0CCh, 0FFh, 56h, 0E8h, 47h, 0C3h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 09h, 0C7h, 46h
    db 08h, 01h, 00h, 00h, 00h, 8Bh, 0FEh, 83h, 3Fh, 00h, 0Fh, 85h, 76h, 0FFh, 0FFh, 0FFh
    db 8Bh, 45h, 04h, 85h, 0C0h, 8Dh, 7Dh, 04h, 74h, 55h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 37h, 8Bh, 46h, 04h, 8Bh, 4Bh, 38h, 8Dh, 04h, 80h, 0Fh, 0BFh, 54h, 81h, 0Eh
    db 8Dh, 04h, 81h, 3Bh, 56h, 08h, 75h, 07h, 8Ah, 48h, 0Ch, 84h, 0C9h, 74h, 22h, 8Bh
    db 06h, 89h, 07h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 0Eh, 85h, 0C9h, 74h, 07h, 6Ah
    db 01h, 0E8h, 72h, 0C7h, 0CAh, 0FFh, 56h, 0E8h, 0E4h, 0C2h, 52h, 00h, 83h, 0C4h, 04h, 0EBh
    db 09h, 0C7h, 46h, 08h, 01h, 00h, 00h, 00h, 8Bh, 0FEh, 83h, 3Fh, 00h, 75h, 0B1h, 5Fh
    db 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h
?d_00355ae0@@YAXXZ ENDP

; ghidra: FUN_00755e20  retail @ 0x00355E20 size 395
public ?d_00355e20@@YAXXZ
?d_00355e20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 4Ch, 94h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 40h, 53h, 55h, 56h, 57h, 33h, 0FFh, 8Bh, 0E9h
    db 89h, 7Ch, 24h, 1Ch, 89h, 6Ch, 24h, 14h, 89h, 7Ch, 24h, 10h, 68h, 28h, 0D8h, 40h
    db 00h, 68h, 0D9h, 7Bh, 41h, 00h, 6Ah, 0Ch, 6Ah, 04h, 8Dh, 44h, 24h, 30h, 50h, 0C7h
    db 44h, 24h, 6Ch, 01h, 00h, 00h, 00h, 0E8h, 78h, 10h, 6Ah, 00h, 8Bh, 0Dh, 6Ch, 07h
    db 2Fh, 01h, 8Bh, 45h, 04h, 8Bh, 11h, 50h, 0C6h, 44h, 24h, 5Ch, 02h, 0FFh, 52h, 2Ch
    db 8Bh, 0F0h, 39h, 7Eh, 10h, 7Eh, 23h, 8Dh, 6Ch, 24h, 20h, 8Dh, 5Eh, 14h, 8Bh, 0FFh
    db 53h, 8Bh, 0CDh, 0E8h, 0F8h, 1Dh, 53h, 00h, 8Bh, 46h, 10h, 47h, 83h, 0C5h, 04h, 83h
    db 0C3h, 04h, 3Bh, 0F8h, 7Ch, 0EAh, 8Bh, 6Ch, 24h, 14h, 8Bh, 45h, 40h, 85h, 0C0h, 8Bh
    db 4Eh, 10h, 89h, 4Ch, 24h, 14h, 74h, 10h, 6Ah, 05h, 68h, 0E4h, 8Ah, 0Eh, 01h, 8Dh
    db 4Ch, 24h, 18h, 0E8h, 58h, 1Eh, 53h, 00h, 33h, 0FFh, 8Dh, 75h, 0Ch, 0B3h, 03h, 90h
    db 3Bh, 7Ch, 24h, 14h, 7Dh, 29h, 8Bh, 44h, 0BCh, 20h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h
    db 48h, 04h, 0EBh, 02h, 33h, 0C9h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 51h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 61h, 1Eh, 53h, 00h, 3Bh
    db 7Dh, 08h, 7Dh, 45h, 8Bh, 0Eh, 8Dh, 54h, 24h, 18h, 52h, 0E8h, 0DAh, 6Dh, 0CEh, 0FFh
    db 8Bh, 00h, 85h, 0C0h, 88h, 5Ch, 24h, 58h, 74h, 06h, 0Fh, 0B7h, 48h, 04h, 0EBh, 02h
    db 33h, 0C9h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 51h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 25h, 1Eh, 53h, 00h, 8Dh, 4Ch, 24h, 18h, 0C6h
    db 44h, 24h, 58h, 02h, 0E8h, 0F7h, 19h, 53h, 00h, 47h, 83h, 0C6h, 04h, 83h, 0FFh, 0Ch
    db 0Fh, 8Ch, 7Ah, 0FFh, 0FFh, 0FFh, 8Bh, 74h, 24h, 60h, 8Dh, 44h, 24h, 10h, 50h, 8Bh
    db 0CEh, 0E8h, 0FAh, 1Bh, 53h, 00h, 68h, 28h, 0D8h, 40h, 00h, 6Ah, 0Ch, 6Ah, 04h, 8Dh
    db 4Ch, 24h, 2Ch, 51h, 0C7h, 44h, 24h, 2Ch, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 68h
    db 01h, 0E8h, 0F0h, 0Dh, 6Ah, 00h, 8Dh, 4Ch, 24h, 10h, 0C6h, 44h, 24h, 58h, 00h, 0E8h
    db 0ACh, 19h, 53h, 00h, 8Bh, 4Ch, 24h, 50h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 04h, 00h
?d_00355e20@@YAXXZ ENDP

; ghidra: FUN_00756040  retail @ 0x00356040 size 77
public ?d_00356040@@YAXXZ
?d_00356040@@YAXXZ PROC
    db 33h, 0C0h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 0E0h, 84h, 0Eh, 01h, 89h
    db 46h, 08h, 89h, 46h, 3Ch, 88h, 46h, 40h, 89h, 46h, 44h, 89h, 46h, 0Ch, 89h, 46h
    db 10h, 89h, 46h, 14h, 89h, 46h, 18h, 89h, 46h, 1Ch, 89h, 46h, 20h, 89h, 46h, 24h
    db 89h, 46h, 28h, 89h, 46h, 2Ch, 89h, 46h, 30h, 89h, 46h, 34h, 51h, 8Bh, 0CEh, 89h
    db 46h, 38h, 0E8h, 0BFh, 29h, 0CEh, 0FFh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00356040@@YAXXZ ENDP

; ghidra: FUN_00756830  retail @ 0x00356830 size 110
public ?d_00356830@@YAXXZ
?d_00356830@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0Fh, 89h, 0Eh, 89h, 07h
    db 8Bh, 46h, 04h, 8Bh, 57h, 04h, 89h, 56h, 04h, 89h, 47h, 04h, 8Dh, 47h, 08h, 50h
    db 8Dh, 4Eh, 08h, 51h, 0E8h, 68h, 68h, 0CBh, 0FFh, 8Bh, 57h, 0Ch, 8Bh, 46h, 0Ch, 89h
    db 56h, 0Ch, 89h, 47h, 0Ch, 8Bh, 46h, 10h, 8Bh, 4Fh, 10h, 89h, 4Eh, 10h, 8Dh, 57h
    db 14h, 89h, 47h, 10h, 52h, 8Dh, 46h, 14h, 50h, 0E8h, 0A9h, 0Bh, 0CCh, 0FFh, 8Bh, 46h
    db 18h, 8Bh, 4Fh, 18h, 89h, 4Eh, 18h, 89h, 47h, 18h, 8Bh, 57h, 1Ch, 8Bh, 46h, 1Ch
    db 83h, 0C4h, 10h, 89h, 56h, 1Ch, 89h, 47h, 1Ch, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00356830@@YAXXZ ENDP

; ghidra: FUN_007568c0  retail @ 0x003568C0 size 208
public ?d_003568c0@@YAXXZ
?d_003568c0@@YAXXZ PROC
    db 83h, 0ECh, 10h, 8Bh, 11h, 53h, 55h, 8Bh, 69h, 04h, 2Bh, 0EAh, 0C1h, 0FDh, 02h, 85h
    db 0EDh, 56h, 57h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h, 54h, 24h, 14h, 0Fh
    db 8Eh, 9Dh, 00h, 00h, 00h, 8Bh, 41h, 0Ch, 8Bh, 4Ch, 24h, 24h, 8Bh, 31h, 89h, 44h
    db 24h, 1Ch, 89h, 74h, 24h, 18h, 0EBh, 08h, 8Bh, 54h, 24h, 14h, 8Bh, 74h, 24h, 18h
    db 8Bh, 44h, 24h, 10h, 03h, 0C5h, 0D1h, 0F8h, 8Bh, 0Ch, 82h, 8Bh, 54h, 24h, 1Ch, 8Dh
    db 0Ch, 89h, 8Dh, 4Ch, 8Ah, 08h, 8Bh, 09h, 33h, 0DBh, 3Bh, 0CBh, 74h, 0Ah, 0Fh, 0B7h
    db 51h, 04h, 89h, 54h, 24h, 24h, 0EBh, 06h, 89h, 5Ch, 24h, 24h, 8Bh, 0D3h, 3Bh, 0CBh
    db 8Dh, 79h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h, 3Bh, 0F3h, 74h, 09h, 0Fh, 0B7h
    db 5Eh, 04h, 83h, 0C6h, 08h, 0EBh, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0DAh, 8Bh, 0CBh
    db 7Ch, 02h, 8Bh, 0CAh, 33h, 0D2h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0D2h, 83h, 0DAh, 0FFh, 85h
    db 0D2h, 75h, 0Ah, 2Bh, 5Ch, 24h, 24h, 8Bh, 0D3h, 85h, 0D2h, 74h, 19h, 7Dh, 04h, 8Bh
    db 0E8h, 0EBh, 05h, 40h, 89h, 44h, 24h, 10h, 3Bh, 6Ch, 24h, 10h, 0Fh, 8Fh, 76h, 0FFh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_003568c0@@YAXXZ ENDP

; ghidra: FUN_007569d0  retail @ 0x003569D0 size 110
public ?d_003569d0@@YAXXZ
?d_003569d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0Fh, 89h, 0Eh, 89h, 07h
    db 8Bh, 46h, 04h, 8Bh, 57h, 04h, 89h, 56h, 04h, 89h, 47h, 04h, 8Dh, 47h, 08h, 50h
    db 8Dh, 4Eh, 08h, 51h, 0E8h, 0C8h, 66h, 0CBh, 0FFh, 8Bh, 57h, 0Ch, 8Bh, 46h, 0Ch, 89h
    db 56h, 0Ch, 89h, 47h, 0Ch, 8Bh, 46h, 10h, 8Bh, 4Fh, 10h, 89h, 4Eh, 10h, 8Dh, 57h
    db 14h, 89h, 47h, 10h, 52h, 8Dh, 46h, 14h, 50h, 0E8h, 0B7h, 49h, 0CFh, 0FFh, 8Bh, 46h
    db 18h, 8Bh, 4Fh, 18h, 89h, 4Eh, 18h, 89h, 47h, 18h, 8Bh, 57h, 1Ch, 8Bh, 46h, 1Ch
    db 83h, 0C4h, 10h, 89h, 56h, 1Ch, 89h, 47h, 1Ch, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_003569d0@@YAXXZ ENDP

; ghidra: FUN_00756a60  retail @ 0x00356A60 size 208
public ?d_00356a60@@YAXXZ
?d_00356a60@@YAXXZ PROC
    db 83h, 0ECh, 10h, 8Bh, 11h, 53h, 55h, 8Bh, 69h, 04h, 2Bh, 0EAh, 0C1h, 0FDh, 02h, 85h
    db 0EDh, 56h, 57h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h, 54h, 24h, 14h, 0Fh
    db 8Eh, 9Dh, 00h, 00h, 00h, 8Bh, 41h, 0Ch, 8Bh, 4Ch, 24h, 24h, 8Bh, 31h, 89h, 44h
    db 24h, 1Ch, 89h, 74h, 24h, 18h, 0EBh, 08h, 8Bh, 54h, 24h, 14h, 8Bh, 74h, 24h, 18h
    db 8Bh, 44h, 24h, 10h, 03h, 0C5h, 0D1h, 0F8h, 8Bh, 0Ch, 82h, 8Bh, 54h, 24h, 1Ch, 8Dh
    db 0Ch, 89h, 8Dh, 4Ch, 8Ah, 08h, 8Bh, 09h, 33h, 0DBh, 3Bh, 0CBh, 74h, 0Ah, 0Fh, 0B7h
    db 51h, 04h, 89h, 54h, 24h, 24h, 0EBh, 06h, 89h, 5Ch, 24h, 24h, 8Bh, 0D3h, 3Bh, 0CBh
    db 8Dh, 79h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h, 3Bh, 0F3h, 74h, 09h, 0Fh, 0B7h
    db 5Eh, 04h, 83h, 0C6h, 08h, 0EBh, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0DAh, 8Bh, 0CBh
    db 7Ch, 02h, 8Bh, 0CAh, 33h, 0D2h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0D2h, 83h, 0DAh, 0FFh, 85h
    db 0D2h, 75h, 0Ah, 2Bh, 5Ch, 24h, 24h, 8Bh, 0D3h, 85h, 0D2h, 74h, 19h, 7Dh, 04h, 8Bh
    db 0E8h, 0EBh, 05h, 40h, 89h, 44h, 24h, 10h, 3Bh, 6Ch, 24h, 10h, 0Fh, 8Fh, 76h, 0FFh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00356a60@@YAXXZ ENDP

; ghidra: FUN_00756fa0  retail @ 0x00356FA0 size 367
public ?d_00356fa0@@YAXXZ
?d_00356fa0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 0Ch
    db 8Bh, 0EAh, 2Bh, 0E9h, 0C1h, 0FDh, 02h, 45h, 57h, 8Dh, 3Ch, 28h, 8Bh, 46h, 24h, 8Dh
    db 1Ch, 3Fh, 3Bh, 0C3h, 76h, 65h, 8Ah, 5Ch, 24h, 1Ch, 2Bh, 0C7h, 8Bh, 7Ch, 24h, 18h
    db 0D1h, 0E8h, 0F6h, 0DBh, 1Bh, 0DBh, 23h, 0DFh, 8Bh, 7Eh, 20h, 03h, 0C3h, 8Dh, 3Ch, 87h
    db 3Bh, 0F9h, 73h, 1Eh, 8Dh, 42h, 04h, 3Bh, 0C1h, 0Fh, 84h, 0F4h, 00h, 00h, 00h, 2Bh
    db 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0E1h, 00h
    db 00h, 00h, 2Bh, 0D1h, 83h, 0C2h, 04h, 85h, 0D2h, 0Fh, 8Eh, 0D4h, 00h, 00h, 00h, 52h
    db 51h, 8Dh, 0Ch, 0ADh, 00h, 00h, 00h, 00h, 2Bh, 0CAh, 03h, 0CFh, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0B8h, 00h, 00h, 00h, 8Bh, 56h, 24h, 3Bh, 54h
    db 24h, 18h, 8Dh, 4Eh, 24h, 73h, 04h, 8Dh, 4Ch, 24h, 18h, 8Bh, 09h, 8Dh, 5Ch, 08h
    db 02h, 85h, 0DBh, 74h, 2Bh, 8Dh, 04h, 9Dh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h
    db 00h, 50h, 76h, 0Eh, 0E8h, 0D7h, 0AEh, 52h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h
    db 0EBh, 16h, 0E8h, 0D9h, 74h, 4Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Ah, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 0D3h, 2Bh, 0D7h, 0D1h, 0EAh, 0F6h, 0D8h, 1Bh, 0C0h, 23h, 0C1h, 8Bh, 4Ch, 24h, 10h
    db 03h, 0D0h, 8Bh, 46h, 1Ch, 8Dh, 3Ch, 91h, 8Bh, 4Eh, 0Ch, 83h, 0C0h, 04h, 3Bh, 0C1h
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 22h, 8Bh, 46h, 24h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0E6h, 0ADh, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h
    db 51h, 0E8h, 1Ah, 75h, 4Dh, 00h, 83h, 0C4h, 08h, 8Bh, 54h, 24h, 10h, 89h, 56h, 20h
    db 89h, 5Eh, 24h, 89h, 7Eh, 0Ch, 8Bh, 07h, 89h, 46h, 04h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 08h, 8Dh, 44h, 0AFh, 0FCh, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 5Fh
    db 05h, 80h, 00h, 00h, 00h, 89h, 46h, 18h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_00356fa0@@YAXXZ ENDP

; ghidra: FUN_00757170  retail @ 0x00357170 size 367
public ?d_00357170@@YAXXZ
?d_00357170@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 0Ch
    db 8Bh, 0EAh, 2Bh, 0E9h, 0C1h, 0FDh, 02h, 45h, 57h, 8Dh, 3Ch, 28h, 8Bh, 46h, 24h, 8Dh
    db 1Ch, 3Fh, 3Bh, 0C3h, 76h, 65h, 8Ah, 5Ch, 24h, 1Ch, 2Bh, 0C7h, 8Bh, 7Ch, 24h, 18h
    db 0D1h, 0E8h, 0F6h, 0DBh, 1Bh, 0DBh, 23h, 0DFh, 8Bh, 7Eh, 20h, 03h, 0C3h, 8Dh, 3Ch, 87h
    db 3Bh, 0F9h, 73h, 1Eh, 8Dh, 42h, 04h, 3Bh, 0C1h, 0Fh, 84h, 0F4h, 00h, 00h, 00h, 2Bh
    db 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0E1h, 00h
    db 00h, 00h, 2Bh, 0D1h, 83h, 0C2h, 04h, 85h, 0D2h, 0Fh, 8Eh, 0D4h, 00h, 00h, 00h, 52h
    db 51h, 8Dh, 0Ch, 0ADh, 00h, 00h, 00h, 00h, 2Bh, 0CAh, 03h, 0CFh, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0B8h, 00h, 00h, 00h, 8Bh, 56h, 24h, 3Bh, 54h
    db 24h, 18h, 8Dh, 4Eh, 24h, 73h, 04h, 8Dh, 4Ch, 24h, 18h, 8Bh, 09h, 8Dh, 5Ch, 08h
    db 02h, 85h, 0DBh, 74h, 2Bh, 8Dh, 04h, 9Dh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h
    db 00h, 50h, 76h, 0Eh, 0E8h, 07h, 0ADh, 52h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h
    db 0EBh, 16h, 0E8h, 09h, 73h, 4Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Ah, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 0D3h, 2Bh, 0D7h, 0D1h, 0EAh, 0F6h, 0D8h, 1Bh, 0C0h, 23h, 0C1h, 8Bh, 4Ch, 24h, 10h
    db 03h, 0D0h, 8Bh, 46h, 1Ch, 8Dh, 3Ch, 91h, 8Bh, 4Eh, 0Ch, 83h, 0C0h, 04h, 3Bh, 0C1h
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 22h, 8Bh, 46h, 24h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Bh, 51h, 0E8h, 16h, 0ACh, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h
    db 51h, 0E8h, 4Ah, 73h, 4Dh, 00h, 83h, 0C4h, 08h, 8Bh, 54h, 24h, 10h, 89h, 56h, 20h
    db 89h, 5Eh, 24h, 89h, 7Eh, 0Ch, 8Bh, 07h, 89h, 46h, 04h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 08h, 8Dh, 44h, 0AFh, 0FCh, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 5Fh
    db 05h, 80h, 00h, 00h, 00h, 89h, 46h, 18h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_00357170@@YAXXZ ENDP

; ghidra: FUN_007573a0  retail @ 0x003573A0 size 367
public ?d_003573a0@@YAXXZ
?d_003573a0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 0Ch
    db 8Bh, 0EAh, 2Bh, 0E9h, 0C1h, 0FDh, 02h, 45h, 57h, 8Dh, 3Ch, 28h, 8Bh, 46h, 24h, 8Dh
    db 1Ch, 3Fh, 3Bh, 0C3h, 76h, 65h, 8Ah, 5Ch, 24h, 1Ch, 2Bh, 0C7h, 8Bh, 7Ch, 24h, 18h
    db 0D1h, 0E8h, 0F6h, 0DBh, 1Bh, 0DBh, 23h, 0DFh, 8Bh, 7Eh, 20h, 03h, 0C3h, 8Dh, 3Ch, 87h
    db 3Bh, 0F9h, 73h, 1Eh, 8Dh, 42h, 04h, 3Bh, 0C1h, 0Fh, 84h, 0F4h, 00h, 00h, 00h, 2Bh
    db 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0E1h, 00h
    db 00h, 00h, 2Bh, 0D1h, 83h, 0C2h, 04h, 85h, 0D2h, 0Fh, 8Eh, 0D4h, 00h, 00h, 00h, 52h
    db 51h, 8Dh, 0Ch, 0ADh, 00h, 00h, 00h, 00h, 2Bh, 0CAh, 03h, 0CFh, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0B8h, 00h, 00h, 00h, 8Bh, 56h, 24h, 3Bh, 54h
    db 24h, 18h, 8Dh, 4Eh, 24h, 73h, 04h, 8Dh, 4Ch, 24h, 18h, 8Bh, 09h, 8Dh, 5Ch, 08h
    db 02h, 85h, 0DBh, 74h, 2Bh, 8Dh, 04h, 9Dh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h
    db 00h, 50h, 76h, 0Eh, 0E8h, 0D7h, 0AAh, 52h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h
    db 0EBh, 16h, 0E8h, 0D9h, 70h, 4Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Ah, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 0D3h, 2Bh, 0D7h, 0D1h, 0EAh, 0F6h, 0D8h, 1Bh, 0C0h, 23h, 0C1h, 8Bh, 4Ch, 24h, 10h
    db 03h, 0D0h, 8Bh, 46h, 1Ch, 8Dh, 3Ch, 91h, 8Bh, 4Eh, 0Ch, 83h, 0C0h, 04h, 3Bh, 0C1h
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 22h, 8Bh, 46h, 24h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0E6h, 0A9h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h
    db 51h, 0E8h, 1Ah, 71h, 4Dh, 00h, 83h, 0C4h, 08h, 8Bh, 54h, 24h, 10h, 89h, 56h, 20h
    db 89h, 5Eh, 24h, 89h, 7Eh, 0Ch, 8Bh, 07h, 89h, 46h, 04h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 08h, 8Dh, 44h, 0AFh, 0FCh, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 5Fh
    db 05h, 80h, 00h, 00h, 00h, 89h, 46h, 18h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_003573a0@@YAXXZ ENDP

; ghidra: FUN_00757570  retail @ 0x00357570 size 367
public ?d_00357570@@YAXXZ
?d_00357570@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 0Ch
    db 8Bh, 0EAh, 2Bh, 0E9h, 0C1h, 0FDh, 02h, 45h, 57h, 8Dh, 3Ch, 28h, 8Bh, 46h, 24h, 8Dh
    db 1Ch, 3Fh, 3Bh, 0C3h, 76h, 65h, 8Ah, 5Ch, 24h, 1Ch, 2Bh, 0C7h, 8Bh, 7Ch, 24h, 18h
    db 0D1h, 0E8h, 0F6h, 0DBh, 1Bh, 0DBh, 23h, 0DFh, 8Bh, 7Eh, 20h, 03h, 0C3h, 8Dh, 3Ch, 87h
    db 3Bh, 0F9h, 73h, 1Eh, 8Dh, 42h, 04h, 3Bh, 0C1h, 0Fh, 84h, 0F4h, 00h, 00h, 00h, 2Bh
    db 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0E1h, 00h
    db 00h, 00h, 2Bh, 0D1h, 83h, 0C2h, 04h, 85h, 0D2h, 0Fh, 8Eh, 0D4h, 00h, 00h, 00h, 52h
    db 51h, 8Dh, 0Ch, 0ADh, 00h, 00h, 00h, 00h, 2Bh, 0CAh, 03h, 0CFh, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0B8h, 00h, 00h, 00h, 8Bh, 56h, 24h, 3Bh, 54h
    db 24h, 18h, 8Dh, 4Eh, 24h, 73h, 04h, 8Dh, 4Ch, 24h, 18h, 8Bh, 09h, 8Dh, 5Ch, 08h
    db 02h, 85h, 0DBh, 74h, 2Bh, 8Dh, 04h, 9Dh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h
    db 00h, 50h, 76h, 0Eh, 0E8h, 07h, 0A9h, 52h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h
    db 0EBh, 16h, 0E8h, 09h, 6Fh, 4Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Ah, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 0D3h, 2Bh, 0D7h, 0D1h, 0EAh, 0F6h, 0D8h, 1Bh, 0C0h, 23h, 0C1h, 8Bh, 4Ch, 24h, 10h
    db 03h, 0D0h, 8Bh, 46h, 1Ch, 8Dh, 3Ch, 91h, 8Bh, 4Eh, 0Ch, 83h, 0C0h, 04h, 3Bh, 0C1h
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 57h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 22h, 8Bh, 46h, 24h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Bh, 51h, 0E8h, 16h, 0A8h, 52h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h
    db 51h, 0E8h, 4Ah, 6Fh, 4Dh, 00h, 83h, 0C4h, 08h, 8Bh, 54h, 24h, 10h, 89h, 56h, 20h
    db 89h, 5Eh, 24h, 89h, 7Eh, 0Ch, 8Bh, 07h, 89h, 46h, 04h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 08h, 8Dh, 44h, 0AFh, 0FCh, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 5Fh
    db 05h, 80h, 00h, 00h, 00h, 89h, 46h, 18h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_00357570@@YAXXZ ENDP

; ghidra: FUN_00757800  retail @ 0x00357800 size 70
public ?d_00357800@@YAXXZ
?d_00357800@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 8Bh, 0F1h, 74h, 05h, 8Dh, 47h, 04h, 0EBh
    db 02h, 33h, 0C0h, 8Bh, 10h, 8Bh, 4Eh, 04h, 89h, 56h, 04h, 89h, 08h, 8Bh, 50h, 04h
    db 8Bh, 4Eh, 08h, 89h, 56h, 08h, 89h, 48h, 04h, 8Dh, 47h, 0Ch, 50h, 8Dh, 4Eh, 0Ch
    db 0E8h, 3Dh, 8Bh, 0CEh, 0FFh, 83h, 0C7h, 2Ch, 57h, 8Dh, 4Eh, 2Ch, 0E8h, 0A2h, 77h, 0CBh
    db 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00357800@@YAXXZ ENDP

; ghidra: FUN_00757cc0  retail @ 0x00357CC0 size 83
public ?d_00357cc0@@YAXXZ
?d_00357cc0@@YAXXZ PROC
    db 33h, 0C0h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 89h, 4Eh, 04h, 0C7h, 06h, 0DCh, 84h
    db 0Eh, 01h, 89h, 46h, 08h, 89h, 46h, 3Ch, 89h, 46h, 40h, 89h, 46h, 44h, 89h, 46h
    db 48h, 89h, 46h, 0Ch, 89h, 46h, 10h, 89h, 46h, 14h, 89h, 46h, 18h, 89h, 46h, 1Ch
    db 89h, 46h, 20h, 89h, 46h, 24h, 89h, 46h, 28h, 89h, 46h, 2Ch, 89h, 46h, 30h, 89h
    db 46h, 34h, 51h, 8Bh, 0CEh, 89h, 46h, 38h, 0E8h, 0DBh, 93h, 0CDh, 0FFh, 8Bh, 0C6h, 5Eh
    db 0C2h, 04h, 00h
?d_00357cc0@@YAXXZ ENDP

; ghidra: FUN_00757d30  retail @ 0x00357D30 size 514
public ?d_00357d30@@YAXXZ
?d_00357d30@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 76h, 95h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 6Ah, 4Ch
    db 89h, 74h, 24h, 18h, 0E8h, 0D7h, 0A1h, 52h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch
    db 33h, 0FFh, 3Bh, 0C7h, 89h, 7Ch, 24h, 28h, 74h, 11h, 8Bh, 4Eh, 04h, 51h, 8Bh, 0C8h
    db 0E8h, 0B3h, 62h, 0CDh, 0FFh, 89h, 44h, 24h, 10h, 0EBh, 06h, 89h, 7Ch, 24h, 10h, 8Bh
    db 0C7h, 8Bh, 4Eh, 08h, 33h, 0DBh, 3Bh, 0CFh, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh
    db 7Eh, 77h, 8Bh, 0CEh, 2Bh, 0C8h, 8Dh, 68h, 0Ch, 89h, 4Ch, 24h, 18h, 0EBh, 04h, 8Bh
    db 4Ch, 24h, 18h, 3Bh, 58h, 08h, 7Dh, 61h, 8Bh, 34h, 29h, 8Bh, 7Dh, 00h, 8Bh, 16h
    db 89h, 17h, 8Ah, 46h, 04h, 88h, 47h, 04h, 8Bh, 4Eh, 08h, 89h, 4Fh, 08h, 8Bh, 56h
    db 0Ch, 8Dh, 46h, 10h, 8Dh, 4Fh, 10h, 50h, 89h, 57h, 0Ch, 0E8h, 0C0h, 0FEh, 52h, 00h
    db 8Dh, 4Eh, 14h, 8Bh, 01h, 8Dh, 57h, 14h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h
    db 8Bh, 49h, 08h, 89h, 4Ah, 08h, 8Bh, 56h, 20h, 8Bh, 4Ch, 24h, 14h, 89h, 57h, 20h
    db 8Bh, 46h, 24h, 89h, 47h, 24h, 8Bh, 41h, 08h, 43h, 83h, 0C5h, 04h, 33h, 0FFh, 3Bh
    db 0D8h, 8Bh, 44h, 24h, 10h, 8Bh, 0F1h, 7Ch, 96h, 8Bh, 6Eh, 3Ch, 3Bh, 0EFh, 8Bh, 0D8h
    db 0Fh, 84h, 09h, 01h, 00h, 00h, 0EBh, 08h, 8Bh, 5Ch, 24h, 18h, 8Dh, 64h, 24h, 00h
    db 6Ah, 4Ch, 0E8h, 09h, 0A1h, 52h, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h, 89h, 74h, 24h, 1Ch
    db 3Bh, 0F7h, 0C7h, 44h, 24h, 28h, 01h, 00h, 00h, 00h, 74h, 4Bh, 8Bh, 45h, 04h, 0C7h
    db 06h, 0DCh, 84h, 0Eh, 01h, 89h, 46h, 04h, 89h, 7Eh, 08h, 89h, 7Eh, 3Ch, 89h, 7Eh
    db 40h, 89h, 7Eh, 44h, 89h, 7Eh, 48h, 33h, 0D2h, 89h, 56h, 0Ch, 89h, 56h, 10h, 89h
    db 56h, 14h, 89h, 56h, 18h, 89h, 56h, 1Ch, 89h, 56h, 20h, 89h, 56h, 24h, 89h, 56h
    db 28h, 89h, 56h, 2Ch, 89h, 56h, 30h, 89h, 56h, 34h, 50h, 8Bh, 0CEh, 89h, 56h, 38h
    db 0E8h, 63h, 92h, 0CDh, 0FFh, 0EBh, 02h, 33h, 0F6h, 89h, 73h, 3Ch, 39h, 7Dh, 08h, 0C7h
    db 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 74h, 24h, 18h, 89h, 7Ch, 24h, 14h, 7Eh
    db 6Fh, 8Bh, 0C5h, 2Bh, 0C6h, 8Dh, 5Eh, 0Ch, 89h, 44h, 24h, 1Ch, 0EBh, 04h, 8Bh, 44h
    db 24h, 1Ch, 8Bh, 34h, 18h, 8Bh, 3Bh, 8Bh, 06h, 89h, 07h, 8Ah, 4Eh, 04h, 88h, 4Fh
    db 04h, 8Bh, 56h, 08h, 8Dh, 4Eh, 10h, 89h, 57h, 08h, 8Bh, 46h, 0Ch, 51h, 8Dh, 4Fh
    db 10h, 89h, 47h, 0Ch, 0E8h, 0B7h, 0FDh, 52h, 00h, 8Dh, 56h, 14h, 8Bh, 0Ah, 8Dh, 47h
    db 14h, 89h, 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 89h, 50h, 08h, 8Bh
    db 46h, 20h, 89h, 47h, 20h, 8Bh, 4Eh, 24h, 8Bh, 44h, 24h, 14h, 89h, 4Fh, 24h, 8Bh
    db 4Dh, 08h, 40h, 83h, 0C3h, 04h, 3Bh, 0C1h, 89h, 44h, 24h, 14h, 7Ch, 0A0h, 33h, 0FFh
    db 8Bh, 6Dh, 3Ch, 3Bh, 0EFh, 0Fh, 85h, 0FDh, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 8Bh
    db 4Ch, 24h, 20h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 1Ch, 0C3h
?d_00357d30@@YAXXZ ENDP

; ghidra: FUN_007592a0  retail @ 0x003592A0 size 108
public ?d_003592a0@@YAXXZ
?d_003592a0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 41h, 1Ch, 83h, 0F8h, 0FFh, 89h, 0Ch, 24h, 74h, 5Ah, 53h, 55h
    db 56h, 57h, 8Bh, 69h, 0Ch, 8Dh, 1Ch, 80h, 0C1h, 0E3h, 02h, 8Bh, 74h, 1Dh, 10h, 8Bh
    db 06h, 03h, 0EBh, 85h, 0C0h, 74h, 2Ch, 8Bh, 3Eh, 85h, 0FFh, 8Bh, 07h, 89h, 44h, 24h
    db 14h, 74h, 14h, 8Bh, 0CFh, 0E8h, 58h, 97h, 0CEh, 0FFh, 57h, 0E8h, 0D0h, 8Bh, 52h, 00h
    db 8Bh, 4Ch, 24h, 14h, 83h, 0C4h, 04h, 8Bh, 54h, 24h, 14h, 8Bh, 0C2h, 85h, 0C0h, 89h
    db 16h, 75h, 0D4h, 66h, 0C7h, 45h, 0Eh, 01h, 00h, 8Bh, 41h, 0Ch, 8Bh, 04h, 03h, 83h
    db 0F8h, 0FFh, 75h, 0AEh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C3h
?d_003592a0@@YAXXZ ENDP

; ghidra: FUN_00759330  retail @ 0x00359330 size 153
public ?d_00359330@@YAXXZ
?d_00359330@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0Ch, 8Dh, 04h, 80h, 66h, 0FFh, 4Ch
    db 81h, 0Eh, 57h, 8Dh, 3Ch, 81h, 8Bh, 47h, 10h, 85h, 0C0h, 0C6h, 47h, 0Ch, 01h, 75h
    db 73h, 53h, 55h, 8Dh, 5Fh, 08h, 53h, 8Bh, 0CEh, 0E8h, 9Eh, 96h, 0CDh, 0FFh, 8Bh, 0E8h
    db 8Bh, 07h, 83h, 0F8h, 0FFh, 74h, 0Dh, 8Bh, 4Fh, 04h, 8Dh, 14h, 80h, 8Bh, 46h, 0Ch
    db 89h, 4Ch, 90h, 04h, 8Bh, 47h, 04h, 83h, 0F8h, 0FFh, 74h, 0Dh, 8Bh, 0Fh, 8Dh, 14h
    db 80h, 8Bh, 46h, 0Ch, 89h, 0Ch, 90h, 0EBh, 05h, 8Bh, 17h, 89h, 56h, 1Ch, 8Bh, 46h
    db 18h, 8Bh, 4Ch, 24h, 14h, 89h, 07h, 89h, 4Eh, 18h, 8Bh, 0CBh, 0E8h, 9Fh, 0E5h, 52h
    db 00h, 8Bh, 16h, 8Bh, 46h, 04h, 8Dh, 14h, 0AAh, 8Dh, 4Ah, 04h, 3Bh, 0C1h, 5Dh, 5Bh
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 52h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 83h, 46h, 04h, 0FCh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00359330@@YAXXZ ENDP

; ghidra: FUN_007593f0  retail @ 0x003593F0 size 54
public ?d_003593f0@@YAXXZ
?d_003593f0@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 8Bh, 47h, 10h, 85h, 0C0h, 74h, 28h, 56h, 8Dh, 49h, 00h
    db 8Bh, 77h, 10h, 85h, 0F6h, 8Bh, 06h, 89h, 47h, 10h, 74h, 10h, 8Bh, 0CEh, 0E8h, 1Fh
    db 96h, 0CEh, 0FFh, 56h, 0E8h, 97h, 8Ah, 52h, 00h, 83h, 0C4h, 04h, 8Bh, 47h, 10h, 85h
    db 0C0h, 75h, 0DDh, 5Eh, 5Fh, 0C3h
?d_003593f0@@YAXXZ ENDP

; ghidra: FUN_007594a0  retail @ 0x003594A0 size 108
public ?d_003594a0@@YAXXZ
?d_003594a0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 41h, 1Ch, 83h, 0F8h, 0FFh, 89h, 0Ch, 24h, 74h, 5Ah, 53h, 55h
    db 56h, 57h, 8Bh, 69h, 0Ch, 8Dh, 1Ch, 80h, 0C1h, 0E3h, 02h, 8Bh, 74h, 1Dh, 10h, 8Bh
    db 06h, 03h, 0EBh, 85h, 0C0h, 74h, 2Ch, 8Bh, 3Eh, 85h, 0FFh, 8Bh, 07h, 89h, 44h, 24h
    db 14h, 74h, 14h, 8Bh, 0CFh, 0E8h, 0E6h, 0F9h, 0CCh, 0FFh, 57h, 0E8h, 0D0h, 89h, 52h, 00h
    db 8Bh, 4Ch, 24h, 14h, 83h, 0C4h, 04h, 8Bh, 54h, 24h, 14h, 8Bh, 0C2h, 85h, 0C0h, 89h
    db 16h, 75h, 0D4h, 66h, 0C7h, 45h, 0Eh, 01h, 00h, 8Bh, 41h, 0Ch, 8Bh, 04h, 03h, 83h
    db 0F8h, 0FFh, 75h, 0AEh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C3h
?d_003594a0@@YAXXZ ENDP

; ghidra: FUN_00759530  retail @ 0x00359530 size 153
public ?d_00359530@@YAXXZ
?d_00359530@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0Ch, 8Dh, 04h, 80h, 66h, 0FFh, 4Ch
    db 81h, 0Eh, 57h, 8Dh, 3Ch, 81h, 8Bh, 47h, 10h, 85h, 0C0h, 0C6h, 47h, 0Ch, 01h, 75h
    db 73h, 53h, 55h, 8Dh, 5Fh, 08h, 53h, 8Bh, 0CEh, 0E8h, 99h, 0DDh, 0CAh, 0FFh, 8Bh, 0E8h
    db 8Bh, 07h, 83h, 0F8h, 0FFh, 74h, 0Dh, 8Bh, 4Fh, 04h, 8Dh, 14h, 80h, 8Bh, 46h, 0Ch
    db 89h, 4Ch, 90h, 04h, 8Bh, 47h, 04h, 83h, 0F8h, 0FFh, 74h, 0Dh, 8Bh, 0Fh, 8Dh, 14h
    db 80h, 8Bh, 46h, 0Ch, 89h, 0Ch, 90h, 0EBh, 05h, 8Bh, 17h, 89h, 56h, 1Ch, 8Bh, 46h
    db 18h, 8Bh, 4Ch, 24h, 14h, 89h, 07h, 89h, 4Eh, 18h, 8Bh, 0CBh, 0E8h, 9Fh, 0E3h, 52h
    db 00h, 8Bh, 16h, 8Bh, 46h, 04h, 8Dh, 14h, 0AAh, 8Dh, 4Ah, 04h, 3Bh, 0C1h, 5Dh, 5Bh
    db 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 52h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 83h, 46h, 04h, 0FCh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00359530@@YAXXZ ENDP

; ghidra: FUN_007595f0  retail @ 0x003595F0 size 54
public ?d_003595f0@@YAXXZ
?d_003595f0@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 8Bh, 47h, 10h, 85h, 0C0h, 74h, 28h, 56h, 8Dh, 49h, 00h
    db 8Bh, 77h, 10h, 85h, 0F6h, 8Bh, 06h, 89h, 47h, 10h, 74h, 10h, 8Bh, 0CEh, 0E8h, 0ADh
    db 0F8h, 0CCh, 0FFh, 56h, 0E8h, 97h, 88h, 52h, 00h, 83h, 0C4h, 04h, 8Bh, 47h, 10h, 85h
    db 0C0h, 75h, 0DDh, 5Eh, 5Fh, 0C3h
?d_003595f0@@YAXXZ ENDP

; ghidra: FUN_00759980  retail @ 0x00359980 size 98
public ?d_00359980@@YAXXZ
?d_00359980@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0B5h, 0EEh, 0CEh, 0FFh, 83h, 0C6h, 14h, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 3Ah, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 67h, 66h, 66h, 66h, 0F7h, 0E9h
    db 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 80h, 0C1h, 0E0h, 02h
    db 3Dh, 80h, 00h, 00h, 00h, 76h, 0Dh, 56h, 0E8h, 0E3h, 84h, 52h, 00h, 83h, 0C4h, 04h
    db 5Fh, 5Eh, 5Bh, 0C3h, 50h, 56h, 0E8h, 15h, 4Ch, 4Dh, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh
    db 5Bh, 0C3h
?d_00359980@@YAXXZ ENDP

; ghidra: FUN_00759a00  retail @ 0x00359A00 size 98
public ?d_00359a00@@YAXXZ
?d_00359a00@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0F5h, 62h, 0CCh, 0FFh, 83h, 0C6h, 14h, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 3Ah, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 67h, 66h, 66h, 66h, 0F7h, 0E9h
    db 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 80h, 0C1h, 0E0h, 02h
    db 3Dh, 80h, 00h, 00h, 00h, 76h, 0Dh, 56h, 0E8h, 63h, 84h, 52h, 00h, 83h, 0C4h, 04h
    db 5Fh, 5Eh, 5Bh, 0C3h, 50h, 56h, 0E8h, 95h, 4Bh, 4Dh, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh
    db 5Bh, 0C3h
?d_00359a00@@YAXXZ ENDP

; ghidra: FUN_00759a80  retail @ 0x00359A80 size 160
public ?d_00359a80@@YAXXZ
?d_00359a80@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Eh, 8Bh, 56h, 08h, 2Bh, 0D1h, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h
    db 3Bh, 0C5h, 73h, 77h, 53h, 8Bh, 5Eh, 04h, 8Bh, 0D3h, 2Bh, 0D1h, 0B8h, 67h, 66h, 66h
    db 66h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 57h, 8Bh, 0FAh, 0C1h, 0EFh, 1Fh, 03h, 0FAh, 85h, 0C9h
    db 74h, 15h, 53h, 51h, 55h, 8Bh, 0CEh, 0E8h, 0BBh, 0ABh, 0CBh, 0FFh, 8Bh, 0CEh, 8Bh, 0D8h
    db 0E8h, 76h, 0BEh, 0CCh, 0FFh, 0EBh, 2Dh, 85h, 0EDh, 74h, 27h, 8Dh, 44h, 0ADh, 00h, 0C1h
    db 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 41h, 84h, 52h, 00h, 83h
    db 0C4h, 04h, 8Bh, 0D8h, 0EBh, 0Eh, 0E8h, 45h, 4Ah, 4Dh, 00h, 83h, 0C4h, 04h, 8Bh, 0D8h
    db 0EBh, 02h, 33h, 0DBh, 8Dh, 0Ch, 0BFh, 8Dh, 14h, 8Bh, 8Dh, 44h, 0ADh, 00h, 8Dh, 0Ch
    db 83h, 5Fh, 89h, 1Eh, 89h, 56h, 04h, 89h, 4Eh, 08h, 5Bh, 5Eh, 5Dh, 0C2h, 04h, 00h
?d_00359a80@@YAXXZ ENDP

; ghidra: FUN_00759b50  retail @ 0x00359B50 size 160
public ?d_00359b50@@YAXXZ
?d_00359b50@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Eh, 8Bh, 56h, 08h, 2Bh, 0D1h, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h
    db 3Bh, 0C5h, 73h, 77h, 53h, 8Bh, 5Eh, 04h, 8Bh, 0D3h, 2Bh, 0D1h, 0B8h, 67h, 66h, 66h
    db 66h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 57h, 8Bh, 0FAh, 0C1h, 0EFh, 1Fh, 03h, 0FAh, 85h, 0C9h
    db 74h, 15h, 53h, 51h, 55h, 8Bh, 0CEh, 0E8h, 3Dh, 0B4h, 0CAh, 0FFh, 8Bh, 0CEh, 8Bh, 0D8h
    db 0E8h, 0B1h, 0C2h, 0CBh, 0FFh, 0EBh, 2Dh, 85h, 0EDh, 74h, 27h, 8Dh, 44h, 0ADh, 00h, 0C1h
    db 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 71h, 83h, 52h, 00h, 83h
    db 0C4h, 04h, 8Bh, 0D8h, 0EBh, 0Eh, 0E8h, 75h, 49h, 4Dh, 00h, 83h, 0C4h, 04h, 8Bh, 0D8h
    db 0EBh, 02h, 33h, 0DBh, 8Dh, 0Ch, 0BFh, 8Dh, 14h, 8Bh, 8Dh, 44h, 0ADh, 00h, 8Dh, 0Ch
    db 83h, 5Fh, 89h, 1Eh, 89h, 56h, 04h, 89h, 4Eh, 08h, 5Bh, 5Eh, 5Dh, 0C2h, 04h, 00h
?d_00359b50@@YAXXZ ENDP

; ghidra: FUN_00759d40  retail @ 0x00359D40 size 101
public ?d_00359d40@@YAXXZ
?d_00359d40@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 57h, 8Dh, 79h, 0Ch, 89h, 4Ch, 24h, 10h
    db 55h, 8Bh, 0CFh, 0E8h, 0A4h, 8Ch, 0CDh, 0FFh, 8Bh, 0Fh, 8Bh, 57h, 04h, 2Bh, 0D1h, 0C1h
    db 0FAh, 02h, 3Bh, 0C2h, 73h, 35h, 8Bh, 1Ch, 81h, 8Bh, 47h, 0Ch, 8Dh, 34h, 9Bh, 0C1h
    db 0E6h, 02h, 55h, 8Dh, 4Ch, 30h, 08h, 0E8h, 49h, 83h, 0CCh, 0FFh, 85h, 0C0h, 75h, 1Bh
    db 83h, 0FBh, 0FFh, 74h, 16h, 8Bh, 4Ch, 24h, 10h, 8Bh, 51h, 18h, 8Bh, 44h, 32h, 10h
    db 5Fh, 5Eh, 5Dh, 83h, 0C0h, 04h, 5Bh, 59h, 0C2h, 04h, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h
    db 5Bh, 59h, 0C2h, 04h, 00h
?d_00359d40@@YAXXZ ENDP

; ghidra: FUN_00759dc0  retail @ 0x00359DC0 size 101
public ?d_00359dc0@@YAXXZ
?d_00359dc0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 57h, 8Dh, 79h, 2Ch, 89h, 4Ch, 24h, 10h
    db 55h, 8Bh, 0CFh, 0E8h, 1Fh, 0D5h, 0CAh, 0FFh, 8Bh, 0Fh, 8Bh, 57h, 04h, 2Bh, 0D1h, 0C1h
    db 0FAh, 02h, 3Bh, 0C2h, 73h, 35h, 8Bh, 1Ch, 81h, 8Bh, 47h, 0Ch, 8Dh, 34h, 9Bh, 0C1h
    db 0E6h, 02h, 55h, 8Dh, 4Ch, 30h, 08h, 0E8h, 0C9h, 82h, 0CCh, 0FFh, 85h, 0C0h, 75h, 1Bh
    db 83h, 0FBh, 0FFh, 74h, 16h, 8Bh, 4Ch, 24h, 10h, 8Bh, 51h, 38h, 8Bh, 44h, 32h, 10h
    db 5Fh, 5Eh, 5Dh, 83h, 0C0h, 04h, 5Bh, 59h, 0C2h, 04h, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h
    db 5Bh, 59h, 0C2h, 04h, 00h
?d_00359dc0@@YAXXZ ENDP

; ghidra: FUN_00759e40  retail @ 0x00359E40 size 121
public ?d_00359e40@@YAXXZ
?d_00359e40@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 33h, 0DBh, 3Bh, 0FBh, 74h, 05h, 8Dh, 47h, 04h, 0EBh, 02h
    db 33h, 0C0h, 50h, 8Bh, 0CFh, 0E8h, 0F9h, 6Ch, 0CCh, 0FFh, 8Dh, 77h, 0Ch, 8Bh, 0CEh, 0E8h
    db 0C5h, 0F5h, 0CCh, 0FFh, 8Bh, 46h, 1Ch, 83h, 0F8h, 0FFh, 74h, 19h, 8Bh, 4Eh, 0Ch, 90h
    db 8Dh, 04h, 80h, 0C1h, 0E0h, 02h, 88h, 5Ch, 08h, 0Ch, 8Bh, 4Eh, 0Ch, 8Bh, 04h, 08h
    db 83h, 0F8h, 0FFh, 75h, 0EBh, 8Dh, 77h, 2Ch, 8Bh, 0CEh, 0E8h, 41h, 20h, 0CEh, 0FFh, 8Bh
    db 46h, 1Ch, 83h, 0F8h, 0FFh, 74h, 1Eh, 8Bh, 4Eh, 0Ch, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Dh, 04h, 80h, 0C1h, 0E0h, 02h, 88h, 5Ch, 08h, 0Ch, 8Bh, 4Eh, 0Ch, 8Bh, 04h, 08h
    db 83h, 0F8h, 0FFh, 75h, 0EBh, 5Fh, 5Eh, 5Bh, 0C3h
?d_00359e40@@YAXXZ ENDP

; ghidra: FUN_00759fe0  retail @ 0x00359FE0 size 91
public ?d_00359fe0@@YAXXZ
?d_00359fe0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 8Bh, 74h, 24h, 10h, 57h, 83h, 0C6h, 0Ch, 55h
    db 8Bh, 0CEh, 0E8h, 05h, 8Ah, 0CDh, 0FFh, 8Bh, 0Eh, 8Bh, 56h, 04h, 2Bh, 0D1h, 0C1h, 0FAh
    db 02h, 3Bh, 0C2h, 73h, 2Fh, 8Bh, 1Ch, 81h, 8Bh, 46h, 0Ch, 8Dh, 3Ch, 9Bh, 0C1h, 0E7h
    db 02h, 55h, 8Dh, 4Ch, 38h, 08h, 0E8h, 0AAh, 80h, 0CCh, 0FFh, 85h, 0C0h, 75h, 15h, 83h
    db 0FBh, 0FFh, 74h, 10h, 8Bh, 4Ch, 24h, 14h, 8Bh, 51h, 18h, 8Ah, 44h, 3Ah, 0Ch, 5Fh
    db 5Eh, 5Dh, 5Bh, 0C3h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 0C3h
?d_00359fe0@@YAXXZ ENDP

; ghidra: FUN_0075a980  retail @ 0x0035A980 size 167
public ?d_0035a980@@YAXXZ
?d_0035a980@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 96h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 0Fh
    db 8Dh, 4Eh, 08h, 0E8h, 88h, 0CFh, 52h, 00h, 83h, 0C6h, 14h, 3Bh, 0F3h, 75h, 0F1h, 8Bh
    db 37h, 85h, 0F6h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 48h, 8Bh, 4Fh, 08h
    db 2Bh, 0CEh, 0B8h, 67h, 66h, 66h, 66h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h
    db 1Fh, 03h, 0C2h, 8Dh, 04h, 80h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Bh
    db 56h, 0E8h, 0BAh, 74h, 52h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h, 56h, 0E8h, 0DEh, 3Bh
    db 4Dh, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0035a980@@YAXXZ ENDP
_TEXT ENDS
END
