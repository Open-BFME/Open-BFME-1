.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ?Control0040F780@@3PAUMovieControl0040F780@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A:BYTE
EXTERN ?Rva00933810StencilStateA@@YAXXZ:NEAR
EXTERN ?Rva00933B80StencilBlendA@@YAXXZ:NEAR
EXTERN ?Rva00933BF0StencilBlendB@@YAXXZ:NEAR
EXTERN ?TheMappedImageCollection@@3PAVImageCollection@@A:BYTE
EXTERN ?d_007986c0@@YAXXZ:NEAR
EXTERN ?d_00933af0@@YAXXZ:NEAR
EXTERN ?drawButtonText@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z:NEAR
EXTERN ?drawRadioButtonText@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z:NEAR
EXTERN ?g_Va01306CE4@@3IA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?j_00002e69@@YAXXZ:NEAR
EXTERN ?j_00004002@@YAXXZ:NEAR
EXTERN ?j_00006758@@YAXXZ:NEAR
EXTERN ?j_0000a114@@YAXXZ:NEAR
EXTERN ?j_0000a128@@YAXXZ:NEAR
EXTERN ?j_00016e73@@YAXXZ:NEAR
EXTERN ?j_00019961@@YAXXZ:NEAR
EXTERN ?j_0001d606@@YAXXZ:NEAR
EXTERN ?j_00023dda@@YAXXZ:NEAR
EXTERN ?j_0002965e@@YAXXZ:NEAR
EXTERN ?j_0002a5d1@@YAXXZ:NEAR
EXTERN ?j_0002c55c@@YAXXZ:NEAR
EXTERN ?j_0002d4e8@@YAXXZ:NEAR
EXTERN ?j_0002d7ea@@YAXXZ:NEAR
EXTERN ?j_0002f94b@@YAXXZ:NEAR
EXTERN ?j_000327a4@@YAXXZ:NEAR
EXTERN ?j_00034338@@YAXXZ:NEAR
EXTERN ?j_00036ebc@@YAXXZ:NEAR
EXTERN ?j_00044026@@YAXXZ:NEAR
EXTERN ?j_00046538@@YAXXZ:NEAR
EXTERN ?j_00048e87@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN g_Va010517CA:NEAR
EXTERN g_Va010F73D0:BYTE
EXTERN g_Va010F73E8:BYTE
EXTERN g_Va010FBF48:BYTE
EXTERN g_Va010FBF58:BYTE
EXTERN g_Va010FBF68:BYTE
EXTERN g_Va0112757C:BYTE
EXTERN g_Va01127580:BYTE
EXTERN g_Va01127584:BYTE
EXTERN g_Va01127594:BYTE
EXTERN g_Va01306CC0:BYTE
EXTERN g_Va01306CC4:BYTE
EXTERN g_Va01306CC8:BYTE
EXTERN g_Va01306CCC:BYTE
EXTERN g_Va01306CD0:BYTE
EXTERN g_Va01306CD4:BYTE
EXTERN g_Va01306CD8:BYTE
EXTERN g_Va01306CDC:BYTE
EXTERN g_Va01306CE0:BYTE
_TEXT SEGMENT

; ghidra: FUN_00b93520  retail @ 0x00793520 size 203
_TEXT ENDS
_TEXT$d00b93520 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B93520 size 203
public ?d_00793520@@YAXXZ
?d_00793520@@YAXXZ PROC
    db 083h, 0ECh, 014h, 053h, 056h, 08Bh, 074h, 024h, 020h, 08Bh, 0CEh
    call ?j_00046538@@YAXXZ
    db 08Bh, 0D8h, 08Dh, 044h, 024h, 010h, 050h, 08Dh, 04Ch, 024h, 010h, 051h, 08Bh, 0CEh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 018h, 052h, 08Dh, 044h, 024h, 018h, 050h, 08Bh, 0CEh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 086h, 090h, 000h, 000h, 000h, 085h, 0C0h, 089h, 044h, 024h, 008h, 00Fh, 084h, 07Fh, 000h
    db 000h, 000h, 08Bh, 08Eh, 084h, 000h, 000h, 000h, 085h, 0C9h, 074h, 075h, 08Bh, 04Eh, 048h, 085h
    db 0C9h, 074h, 06Eh, 08Bh, 04Eh, 054h, 085h, 0C9h, 074h, 067h, 08Bh, 04Eh, 060h, 085h, 0C9h, 074h
    db 060h, 00Fh, 0AFh, 05Ch, 024h, 014h, 057h, 08Bh, 078h, 024h, 0B8h, 01Fh, 085h, 0EBh, 051h, 0F7h
    db 0EBh, 0C1h, 0FAh, 005h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 099h, 0F7h, 0FFh, 08Bh, 054h
    db 024h, 010h, 085h, 0C0h, 07Eh, 03Ah, 089h, 044h, 024h, 024h, 055h, 090h, 08Bh, 044h, 024h, 018h
    db 08Bh, 06Ch, 024h, 020h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 019h, 06Ah, 0FFh, 003h, 0E8h, 055h, 08Dh, 034h, 03Ah, 056h, 050h, 052h, 08Bh, 054h, 024h
    db 024h, 052h, 0FFh, 093h, 0F4h, 000h, 000h, 000h, 08Bh, 044h, 024h, 028h, 048h, 08Bh, 0D6h, 089h
    db 044h, 024h, 028h, 075h, 0CDh, 05Dh, 05Fh, 05Eh, 05Bh, 083h, 0C4h, 014h, 0C3h
?d_00793520@@YAXXZ ENDP
_TEXT$d00b93520 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b93a70  retail @ 0x00793A70 size 14
public ?d_00793a70@@YAXXZ
?d_00793a70@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 51h, 0E8h, 0CAh, 94h, 87h, 0FFh, 83h, 0C4h, 08h
?d_00793a70@@YAXXZ ENDP

; ghidra: FUN_00b93a70  retail @ 0x00793A7E size 8
public ?d_00793a7e@@YAXXZ
?d_00793a7e@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00793a7e@@YAXXZ ENDP

; ghidra: FUN_00b93c20  retail @ 0x00793C20 size 60
public ?d_00793c20@@YAXXZ
?d_00793c20@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 18h, 8Bh
    db 4Ch, 24h, 14h, 8Bh, 16h, 50h, 8Bh, 44h, 24h, 14h, 51h, 8Bh, 4Ch, 24h, 14h, 50h
    db 8Bh, 44h, 24h, 14h, 51h, 50h, 8Bh, 0CEh, 0FFh, 92h, 0C4h, 00h, 00h, 00h, 8Bh, 16h
    db 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 5Eh, 0C2h, 14h, 00h
?d_00793c20@@YAXXZ ENDP

; ghidra: FUN_00b93c70  retail @ 0x00793C70 size 65
public ?d_00793c70@@YAXXZ
?d_00793c70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 16h, 50h, 8Bh, 44h, 24h, 18h, 51h, 8Bh, 4Ch, 24h, 18h, 50h
    db 8Bh, 44h, 24h, 18h, 51h, 8Bh, 4Ch, 24h, 18h, 50h, 51h, 8Bh, 0CEh, 0FFh, 92h, 0C8h
    db 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 5Eh, 0C2h, 18h
    db 00h
?d_00793c70@@YAXXZ ENDP

; ghidra: FUN_00b93cd0  retail @ 0x00793CD0 size 65
public ?d_00793cd0@@YAXXZ
?d_00793cd0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 16h, 50h, 8Bh, 44h, 24h, 18h, 51h, 8Bh, 4Ch, 24h, 18h, 50h
    db 8Bh, 44h, 24h, 18h, 51h, 8Bh, 4Ch, 24h, 18h, 50h, 51h, 8Bh, 0CEh, 0FFh, 92h, 0CCh
    db 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 5Eh, 0C2h, 18h
    db 00h
?d_00793cd0@@YAXXZ ENDP

; ghidra: FUN_00b93d30  retail @ 0x00793D30 size 25
public ?d_00793d30@@YAXXZ
?d_00793d30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 41h, 33h, 8Ah, 0FFh, 0C7h, 06h, 14h
    db 75h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00793d30@@YAXXZ ENDP

; ghidra: FUN_00b93db0  retail @ 0x00793DB0 size 27
public ?d_00793db0@@YAXXZ
?d_00793db0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 50h, 8Bh, 44h, 24h, 08h, 52h, 50h, 51h
    db 0E8h, 43h, 0C2h, 89h, 0FFh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_00793db0@@YAXXZ ENDP

; ghidra: FUN_00b93e00  retail @ 0x00793E00 size 25
public ?d_00793e00@@YAXXZ
?d_00793e00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 71h, 32h, 8Ah, 0FFh, 0C7h, 06h, 48h
    db 75h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00793e00@@YAXXZ ENDP

; ghidra: FUN_00b93e50  retail @ 0x00793E50 size 108
public ?d_00793e50@@YAXXZ
?d_00793e50@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 0CEh, 0E8h, 7Eh, 0FFh, 88h, 0FFh, 0A8h, 08h, 75h, 1Ch
    db 8Bh, 0CEh, 0E8h, 81h, 96h, 89h, 0FFh, 8Bh, 4Ch, 24h, 10h, 89h, 01h, 8Bh, 0CEh, 0E8h
    db 0E8h, 86h, 89h, 0FFh, 8Bh, 54h, 24h, 14h, 89h, 02h, 5Eh, 0C3h, 8Bh, 44h, 24h, 0Ch
    db 0F6h, 40h, 08h, 02h, 8Bh, 0CEh, 74h, 1Ah, 0E8h, 9Bh, 62h, 87h, 0FFh, 8Bh, 4Ch, 24h
    db 10h, 89h, 01h, 8Bh, 0CEh, 0E8h, 0C7h, 5Ah, 88h, 0FFh, 8Bh, 54h, 24h, 14h, 89h, 02h
    db 5Eh, 0C3h, 0E8h, 2Ah, 67h, 89h, 0FFh, 8Bh, 4Ch, 24h, 10h, 89h, 01h, 8Bh, 0CEh, 0E8h
    db 36h, 99h, 89h, 0FFh, 8Bh, 54h, 24h, 14h, 89h, 02h, 5Eh, 0C3h
?d_00793e50@@YAXXZ ENDP

; ghidra: FUN_00b93ee0  retail @ 0x00793EE0 size 273
public ?d_00793ee0@@YAXXZ
?d_00793ee0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 53h, 56h, 8Bh, 0D8h, 8Bh, 0B3h, 9Ch, 01h, 00h, 00h, 85h, 0F6h, 57h
    db 8Bh, 0F9h, 0Fh, 84h, 0F2h, 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 0Ch, 85h
    db 0C0h, 0Fh, 84h, 0E3h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 28h, 51h, 8Dh, 54h, 24h, 28h
    db 52h, 8Bh, 0CFh, 0E8h, 33h, 0BAh, 89h, 0FFh, 8Dh, 44h, 24h, 20h, 50h, 8Dh, 4Ch, 24h
    db 20h, 51h, 8Bh, 0CFh, 0E8h, 93h, 2Fh, 8Ah, 0FFh, 8Bh, 43h, 10h, 8Bh, 16h, 0C1h, 0E8h
    db 12h, 25h, 01h, 0FFh, 0FFh, 0FFh, 50h, 8Bh, 0CEh, 0FFh, 52h, 24h, 8Bh, 44h, 24h, 1Ch
    db 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 20h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 54h, 24h
    db 1Ch, 52h, 53h, 57h, 0E8h, 82h, 4Ah, 87h, 0FFh, 8Bh, 06h, 83h, 0C4h, 10h, 8Bh, 0CEh
    db 0FFh, 50h, 1Ch, 8Bh, 0CFh, 8Bh, 0D8h, 0E8h, 11h, 9Ch, 89h, 0FFh, 3Bh, 0D8h, 74h, 0Fh
    db 8Bh, 1Eh, 8Bh, 0CFh, 0E8h, 04h, 9Ch, 89h, 0FFh, 50h, 8Bh, 0CEh, 0FFh, 53h, 18h, 8Bh
    db 16h, 8Dh, 44h, 24h, 10h, 50h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CEh, 0FFh, 52h, 3Ch
    db 8Bh, 44h, 24h, 0Ch, 99h, 2Bh, 0C2h, 8Bh, 0C8h, 8Bh, 44h, 24h, 1Ch, 99h, 2Bh, 0C2h
    db 8Bh, 54h, 24h, 24h, 8Bh, 0F8h, 8Bh, 44h, 24h, 10h, 0D1h, 0F9h, 0D1h, 0FFh, 2Bh, 0F9h
    db 03h, 0FAh, 99h, 2Bh, 0C2h, 8Bh, 0C8h, 8Bh, 44h, 24h, 20h, 99h, 2Bh, 0C2h, 8Bh, 54h
    db 24h, 28h, 8Bh, 0D8h, 8Bh, 44h, 24h, 14h, 0D1h, 0F9h, 0D1h, 0FBh, 2Bh, 0D9h, 8Bh, 4Ch
    db 24h, 18h, 50h, 03h, 0DAh, 8Bh, 16h, 51h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 16h, 6Ah
    db 01h, 6Ah, 01h, 53h, 57h, 8Bh, 0CEh, 0FFh, 52h, 38h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 20h
    db 0C3h
?d_00793ee0@@YAXXZ ENDP

; ghidra: FUN_00b94040  retail @ 0x00794040 size 170
_TEXT ENDS
_TEXT$d00b94040 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B94040 size 170
public ?d_00794040@@YAXXZ
?d_00794040@@YAXXZ PROC
    db 083h, 0ECh, 010h, 0DBh, 000h, 056h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0DBh, 040h, 004h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0DBh, 001h, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 00Ch, 0DBh, 041h, 004h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 08Bh, 0F1h, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 004h, 0DBh, 047h, 024h, 0D8h, 0CAh, 0D8h
    db 00Dh
    dd g_Va0112757C
    db 0D9h, 05Ch, 024h, 010h, 0DBh, 047h, 028h, 0D8h, 0C9h, 0D8h, 00Dh
    dd g_Va0112757C
    db 0D9h, 05Ch, 024h, 008h, 0DDh, 0D8h, 0DDh, 0D8h, 0FFh, 090h, 0B0h, 000h, 000h, 000h, 08Bh, 044h
    db 024h, 018h, 0D9h, 044h, 024h, 004h, 0D8h, 044h, 024h, 008h, 08Bh, 016h, 06Ah, 002h, 050h, 083h
    db 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 08Bh, 0CEh, 0D9h, 044h, 024h, 024h, 0D8h, 044h, 024h, 028h
    db 0D9h, 05Ch, 024h, 008h, 0D9h, 044h, 024h, 01Ch, 0D8h, 064h, 024h, 020h, 0D9h, 05Ch, 024h, 004h
    db 0D9h, 044h, 024h, 024h, 0D8h, 064h, 024h, 028h, 0D9h, 01Ch, 024h, 057h, 0FFh, 092h, 0D4h, 000h
    db 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 05Eh, 083h, 0C4h, 010h, 0FFh, 0A2h, 0DCh, 000h, 000h, 000h
?d_00794040@@YAXXZ ENDP
_TEXT$d00b94040 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b94120  retail @ 0x00794120 size 1314
public ?d_00794120@@YAXXZ
?d_00794120@@YAXXZ PROC
    db 83h, 0ECh, 58h, 53h, 8Bh, 5Ch, 24h, 60h, 55h, 56h, 57h, 8Dh, 44h, 24h, 3Ch, 50h
    db 8Dh, 4Ch, 24h, 3Ch, 51h, 8Bh, 0CBh, 0E8h, 0Fh, 0B8h, 89h, 0FFh, 8Dh, 54h, 24h, 34h
    db 52h, 8Dh, 44h, 24h, 34h, 50h, 8Bh, 0CBh, 0E8h, 6Fh, 2Dh, 8Ah, 0FFh, 8Bh, 6Ch, 24h
    db 70h, 8Bh, 0B5h, 7Ch, 01h, 00h, 00h, 8Bh, 0BDh, 80h, 01h, 00h, 00h, 8Bh, 0CBh, 89h
    db 74h, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 6Eh, 0FCh, 88h, 0FFh, 0A8h, 08h, 75h, 41h
    db 0F6h, 45h, 08h, 04h, 74h, 1Fh, 8Bh, 8Bh, 0C0h, 00h, 00h, 00h, 8Bh, 93h, 0E4h, 00h
    db 00h, 00h, 8Bh, 9Bh, 0D8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 10h, 89h, 54h, 24h, 14h
    db 0E9h, 85h, 00h, 00h, 00h, 8Bh, 83h, 0B4h, 00h, 00h, 00h, 8Bh, 8Bh, 0FCh, 00h, 00h
    db 00h, 8Bh, 9Bh, 0F0h, 00h, 00h, 00h, 89h, 44h, 24h, 10h, 89h, 4Ch, 24h, 14h, 0EBh
    db 69h, 8Bh, 45h, 08h, 0A8h, 02h, 74h, 34h, 0A8h, 04h, 74h, 14h, 8Bh, 93h, 2Ch, 01h
    db 00h, 00h, 8Bh, 83h, 50h, 01h, 00h, 00h, 8Bh, 9Bh, 44h, 01h, 00h, 00h, 0EBh, 42h
    db 8Bh, 8Bh, 20h, 01h, 00h, 00h, 8Bh, 93h, 68h, 01h, 00h, 00h, 8Bh, 9Bh, 5Ch, 01h
    db 00h, 00h, 89h, 4Ch, 24h, 10h, 89h, 54h, 24h, 14h, 0EBh, 2Eh, 0A8h, 04h, 74h, 13h
    db 8Bh, 43h, 54h, 8Bh, 4Bh, 78h, 8Bh, 5Bh, 6Ch, 89h, 44h, 24h, 10h, 89h, 4Ch, 24h
    db 14h, 0EBh, 17h, 8Bh, 53h, 48h, 8Bh, 83h, 90h, 00h, 00h, 00h, 8Bh, 9Bh, 84h, 00h
    db 00h, 00h, 89h, 54h, 24h, 10h, 89h, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h
    db 0Fh, 84h, 17h, 04h, 00h, 00h, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 0Fh, 84h, 0Bh, 04h
    db 00h, 00h, 85h, 0DBh, 0Fh, 84h, 03h, 04h, 00h, 00h, 8Bh, 50h, 24h, 8Bh, 69h, 24h
    db 8Bh, 44h, 24h, 34h, 8Bh, 4Ch, 24h, 38h, 03h, 0C7h, 8Bh, 7Ch, 24h, 3Ch, 03h, 0EEh
    db 03h, 0C7h, 2Bh, 0F2h, 89h, 54h, 24h, 50h, 8Bh, 54h, 24h, 30h, 89h, 44h, 24h, 4Ch
    db 8Bh, 44h, 24h, 18h, 03h, 0F2h, 03h, 0F1h, 03h, 0F8h, 03h, 0E9h, 8Bh, 0C6h, 2Bh, 0C5h
    db 85h, 0C0h, 7Fh, 49h, 8Bh, 6Ch, 24h, 20h, 8Bh, 0C2h, 99h, 2Bh, 0C2h, 8Bh, 0F0h, 8Bh
    db 44h, 24h, 4Ch, 6Ah, 0FFh, 0D1h, 0FEh, 50h, 8Bh, 44h, 24h, 18h, 03h, 0F5h, 03h, 0F1h
    db 56h, 8Dh, 1Ch, 29h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 57h, 53h, 89h, 5Ch, 24h, 3Ch
    db 89h, 7Ch, 24h, 40h, 8Bh, 11h, 50h, 0FFh, 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 38h, 8Bh, 54h, 24h, 30h, 8Dh, 04h, 0Ah, 0E9h, 31h, 01h, 00h, 00h, 99h, 0F7h, 7Bh
    db 24h, 8Bh, 54h, 24h, 18h, 89h, 6Ch, 24h, 28h, 89h, 44h, 24h, 1Ch, 8Bh, 0C7h, 89h
    db 44h, 24h, 2Ch, 03h, 0C2h, 03h, 44h, 24h, 34h, 89h, 44h, 24h, 44h, 8Bh, 44h, 24h
    db 1Ch, 85h, 0C0h, 8Bh, 0D5h, 7Eh, 4Eh, 89h, 44h, 24h, 1Ch, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 43h, 24h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 6Ah, 0FFh, 0FFh, 74h, 24h
    db 48h, 03h, 0C2h, 50h, 8Bh, 44h, 24h, 38h, 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh
    db 01h, 52h, 53h, 0FFh, 90h, 0F4h, 00h, 00h, 00h, 8Bh, 54h, 24h, 28h, 8Bh, 4Bh, 24h
    db 8Bh, 44h, 24h, 1Ch, 03h, 0D1h, 48h, 89h, 54h, 24h, 28h, 89h, 44h, 24h, 1Ch, 75h
    db 0BFh, 8Bh, 4Ch, 24h, 38h, 8Bh, 44h, 24h, 2Ch, 89h, 44h, 24h, 5Ch, 8Bh, 44h, 24h
    db 44h, 89h, 44h, 24h, 64h, 8Bh, 0C6h, 2Bh, 0C2h, 85h, 0C0h, 89h, 54h, 24h, 58h, 89h
    db 74h, 24h, 60h, 7Eh, 57h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 8Dh, 44h, 24h
    db 58h, 50h, 0FFh, 92h, 88h, 00h, 00h, 00h, 8Bh, 54h, 24h, 28h, 8Bh, 43h, 24h, 8Bh
    db 0Dh, 40h, 1Bh, 2Fh, 01h, 03h, 0C2h, 8Bh, 11h, 8Bh, 4Ch, 24h, 44h, 6Ah, 0FFh, 51h
    db 8Bh, 4Ch, 24h, 30h, 50h, 8Bh, 44h, 24h, 38h, 50h, 51h, 8Bh, 0Dh, 40h, 1Bh, 2Fh
    db 01h, 53h, 0FFh, 92h, 0F4h, 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h
    db 6Ah, 00h, 0FFh, 92h, 90h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 38h, 8Bh, 44h, 24h, 20h
    db 8Bh, 54h, 24h, 18h, 03h, 0C1h, 8Bh, 4Ch, 24h, 3Ch, 03h, 0D1h, 8Bh, 4Ch, 24h, 4Ch
    db 6Ah, 0FFh, 89h, 4Ch, 24h, 48h, 0FFh, 74h, 24h, 48h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h
    db 55h, 52h, 89h, 54h, 24h, 3Ch, 8Bh, 54h, 24h, 20h, 50h, 89h, 44h, 24h, 3Ch, 8Bh
    db 19h, 52h, 0FFh, 93h, 0F4h, 00h, 00h, 00h, 8Bh, 44h, 24h, 50h, 03h, 0C6h, 8Bh, 4Ch
    db 24h, 34h, 6Ah, 0FFh, 8Dh, 14h, 0Fh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 52h, 8Bh, 54h
    db 24h, 1Ch, 50h, 57h, 56h, 89h, 7Ch, 24h, 40h, 89h, 74h, 24h, 3Ch, 8Bh, 19h, 52h
    db 0FFh, 93h, 0F4h, 00h, 00h, 00h, 8Bh, 74h, 24h, 70h, 8Bh, 86h, 9Ch, 01h, 00h, 00h
    db 85h, 0C0h, 74h, 1Ah, 8Bh, 0C8h, 8Bh, 01h, 0FFh, 50h, 0Ch, 85h, 0C0h, 74h, 0Fh, 8Bh
    db 7Ch, 24h, 6Ch, 8Bh, 0C6h, 8Bh, 0CFh, 0E8h, 0A4h, 0FAh, 0FFh, 0FFh, 0EBh, 04h, 8Bh, 7Ch
    db 24h, 6Ch, 8Dh, 4Ch, 24h, 2Ch, 51h, 8Dh, 54h, 24h, 2Ch, 52h, 8Bh, 0CFh, 0E8h, 0F8h
    db 0B4h, 89h, 0FFh, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Bh, 0CFh, 0E8h
    db 58h, 2Ah, 8Ah, 0FFh, 8Bh, 86h, 0A4h, 01h, 00h, 00h, 85h, 0C0h, 74h, 55h, 8Bh, 74h
    db 24h, 34h, 8Bh, 5Ch, 24h, 2Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 03h, 0DEh
    db 8Bh, 74h, 24h, 30h, 89h, 5Ch, 24h, 70h, 8Bh, 5Ch, 24h, 28h, 0DBh, 44h, 24h, 70h
    db 6Ah, 0FFh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 03h, 0DEh, 89h, 9Ch, 24h, 84h, 00h
    db 00h, 00h, 0DBh, 84h, 24h, 84h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0DBh, 44h, 24h
    db 40h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 3Ch, 0D9h, 1Ch, 24h, 50h, 0FFh, 92h, 0E0h
    db 00h, 00h, 00h, 8Bh, 0CFh, 0E8h, 6Eh, 20h, 8Bh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h
    db 69h, 01h, 00h, 00h, 8Bh, 46h, 18h, 85h, 0C0h, 74h, 54h, 8Bh, 4Ch, 24h, 3Ch, 8Bh
    db 54h, 24h, 34h, 03h, 0D1h, 8Bh, 4Ch, 24h, 38h, 89h, 54h, 24h, 70h, 8Bh, 54h, 24h
    db 30h, 0DBh, 44h, 24h, 70h, 6Ah, 02h, 6Ah, 0FFh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch
    db 03h, 0D1h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 0DBh
    db 84h, 24h, 88h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0DBh, 44h, 24h, 54h, 0D9h, 5Ch
    db 24h, 04h, 0DBh, 44h, 24h, 50h, 0D9h, 1Ch, 24h, 50h, 0E8h, 0E5h, 5Bh, 87h, 0FFh, 8Ah
    db 06h, 84h, 0C0h, 0Fh, 84h, 85h, 00h, 00h, 00h, 3Ch, 01h, 75h, 3Ah, 8Bh, 46h, 08h
    db 0DBh, 46h, 04h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 50h, 83h, 0ECh, 14h, 0D9h, 5Ch, 24h
    db 10h, 0DBh, 44h, 24h, 4Ch, 0D9h, 5Ch, 24h, 0Ch, 0DBh, 44h, 24h, 48h, 0D9h, 5Ch, 24h
    db 08h, 0DBh, 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 40h, 0D9h, 1Ch, 24h
    db 0E8h, 12h, 49h, 8Bh, 0FFh, 0EBh, 3Ch, 3Ch, 02h, 75h, 38h, 8Bh, 4Eh, 08h, 0DBh, 46h
    db 04h, 51h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 83h, 0ECh, 14h, 0D9h, 5Ch, 24h, 10h, 0DBh
    db 44h, 24h, 4Ch, 0D9h, 5Ch, 24h, 0Ch, 0DBh, 44h, 24h, 48h, 0D9h, 5Ch, 24h, 08h, 0DBh
    db 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 40h, 0D9h, 1Ch, 24h, 0E8h, 0CBh
    db 00h, 87h, 0FFh, 56h, 8Bh, 0CFh, 0C6h, 06h, 00h, 0E8h, 0ABh, 0E8h, 86h, 0FFh, 8Ah, 46h
    db 0Ch, 84h, 0C0h, 74h, 78h, 8Bh, 76h, 10h, 81h, 0FEh, 0FFh, 0FFh, 0FFh, 00h, 74h, 6Dh
    db 8Bh, 54h, 24h, 34h, 8Bh, 44h, 24h, 30h, 8Bh, 4Ch, 24h, 2Ch, 83h, 0C2h, 02h, 89h
    db 54h, 24h, 70h, 0DBh, 44h, 24h, 70h, 8Bh, 54h, 24h, 28h, 56h, 83h, 0C0h, 02h, 68h
    db 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 84h, 24h, 88h, 00h
    db 00h, 00h, 0DBh, 84h, 24h, 88h, 00h, 00h, 00h, 49h, 89h, 8Ch, 24h, 88h, 00h, 00h
    db 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 4Ah, 0DBh, 84h, 24h, 88h
    db 00h, 00h, 00h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 04h, 0DBh, 84h
    db 24h, 88h, 00h, 00h, 00h, 0D9h, 1Ch, 24h, 0E8h, 21h, 50h, 89h, 0FFh, 5Fh, 5Eh, 5Dh
    db 5Bh, 83h
?d_00794120@@YAXXZ ENDP

; ghidra: FUN_00b94790  retail @ 0x00794790 size 719
public ?d_00794790@@YAXXZ
?d_00794790@@YAXXZ PROC
    db 83h, 0ECh, 4Ch, 53h, 55h, 56h, 8Bh, 74h, 24h, 5Ch, 57h, 8Dh, 44h, 24h, 38h, 50h
    db 8Dh, 4Ch, 24h, 38h, 51h, 8Bh, 0CEh, 0E8h, 9Fh, 0B1h, 89h, 0FFh, 8Dh, 54h, 24h, 30h
    db 52h, 8Dh, 44h, 24h, 30h, 50h, 8Bh, 0CEh, 0E8h, 0FFh, 26h, 8Ah, 0FFh, 8Bh, 6Ch, 24h
    db 64h, 8Bh, 0BDh, 7Ch, 01h, 00h, 00h, 8Bh, 9Dh, 80h, 01h, 00h, 00h, 8Bh, 0CEh, 89h
    db 7Ch, 24h, 18h, 89h, 5Ch, 24h, 20h, 0E8h, 0FEh, 0F5h, 88h, 0FFh, 0A8h, 08h, 75h, 2Eh
    db 0F6h, 45h, 08h, 04h, 74h, 14h, 8Bh, 8Eh, 0C0h, 00h, 00h, 00h, 8Bh, 96h, 0E4h, 00h
    db 00h, 00h, 8Bh, 86h, 0D8h, 00h, 00h, 00h, 0EBh, 65h, 8Bh, 8Eh, 0B4h, 00h, 00h, 00h
    db 8Bh, 96h, 0FCh, 00h, 00h, 00h, 8Bh, 86h, 0F0h, 00h, 00h, 00h, 0EBh, 51h, 8Bh, 45h
    db 08h, 0A8h, 02h, 74h, 2Ch, 0A8h, 04h, 74h, 14h, 8Bh, 8Eh, 2Ch, 01h, 00h, 00h, 8Bh
    db 96h, 50h, 01h, 00h, 00h, 8Bh, 86h, 44h, 01h, 00h, 00h, 0EBh, 32h, 8Bh, 8Eh, 20h
    db 01h, 00h, 00h, 8Bh, 96h, 68h, 01h, 00h, 00h, 8Bh, 86h, 5Ch, 01h, 00h, 00h, 0EBh
    db 1Eh, 0A8h, 04h, 74h, 0Bh, 8Bh, 4Eh, 54h, 8Bh, 56h, 78h, 8Bh, 46h, 6Ch, 0EBh, 0Fh
    db 8Bh, 4Eh, 48h, 8Bh, 96h, 90h, 00h, 00h, 00h, 8Bh, 86h, 84h, 00h, 00h, 00h, 8Bh
    db 0F1h, 85h, 0F6h, 89h, 4Ch, 24h, 10h, 89h, 54h, 24h, 14h, 89h, 44h, 24h, 64h, 0Fh
    db 84h, 0E2h, 01h, 00h, 00h, 8Bh, 0C2h, 85h, 0C0h, 0Fh, 84h, 0D8h, 01h, 00h, 00h, 8Bh
    db 4Ch, 24h, 64h, 85h, 0C9h, 0Fh, 84h, 0CCh, 01h, 00h, 00h, 8Bh, 6Eh, 28h, 8Bh, 40h
    db 28h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 54h, 24h, 34h, 03h, 0CFh, 89h, 44h, 24h, 48h, 03h
    db 0CAh, 8Bh, 0F3h, 2Bh, 0F0h, 03h, 74h, 24h, 30h, 89h, 4Ch, 24h, 3Ch, 8Bh, 4Ch, 24h
    db 38h, 03h, 0EBh, 03h, 0F1h, 03h, 0E9h, 8Bh, 0C6h, 2Bh, 0C5h, 03h, 0FAh, 85h, 0C0h, 7Fh
    db 64h, 8Bh, 44h, 24h, 2Ch, 03h, 0C2h, 89h, 44h, 24h, 24h, 8Bh, 44h, 24h, 30h, 99h
    db 2Bh, 0C2h, 8Bh, 0F0h, 8Bh, 44h, 24h, 24h, 0D1h, 0FEh, 6Ah, 0FFh, 03h, 0F3h, 03h, 0F1h
    db 56h, 50h, 8Bh, 44h, 24h, 1Ch, 8Dh, 2Ch, 0Bh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 11h, 55h, 57h, 50h, 0FFh, 92h, 0F4h, 00h, 00h, 00h, 8Bh, 44h, 24h, 34h, 8Bh, 4Ch
    db 24h, 18h, 8Bh, 7Ch, 24h, 30h, 8Dh, 14h, 01h, 8Bh, 4Ch, 24h, 2Ch, 03h, 0C1h, 8Bh
    db 4Ch, 24h, 38h, 6Ah, 0FFh, 03h, 0F9h, 57h, 50h, 56h, 52h, 8Bh, 54h, 24h, 28h, 52h
    db 0E9h, 24h, 01h, 00h, 00h, 8Bh, 54h, 24h, 64h, 8Bh, 5Ah, 28h, 99h, 0F7h, 0FBh, 8Bh
    db 54h, 24h, 2Ch, 8Bh, 0DDh, 89h, 44h, 24h, 1Ch, 8Bh, 44h, 24h, 18h, 03h, 0C7h, 03h
    db 0C2h, 8Bh, 54h, 24h, 1Ch, 85h, 0D2h, 89h, 44h, 24h, 24h, 7Eh, 49h, 89h, 54h, 24h
    db 1Ch, 8Bh, 4Ch, 24h, 64h, 8Bh, 49h, 28h, 6Ah, 0FFh, 03h, 0CBh, 89h, 4Ch, 24h, 2Ch
    db 0FFh, 74h, 24h, 2Ch, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 50h, 8Bh, 44h, 24h
    db 70h, 53h, 57h, 50h, 0FFh, 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 64h, 8Bh, 51h
    db 28h, 8Bh, 44h, 24h, 1Ch, 03h, 0DAh, 48h, 89h, 44h, 24h, 1Ch, 8Bh, 44h, 24h, 24h
    db 75h, 0BFh, 8Bh, 4Ch, 24h, 38h, 8Bh, 0D6h, 2Bh, 0D3h, 85h, 0D2h, 89h, 7Ch, 24h, 4Ch
    db 89h, 5Ch, 24h, 50h, 89h, 44h, 24h, 54h, 89h, 74h, 24h, 58h, 7Eh, 4Dh, 8Bh, 0Dh
    db 70h, 12h, 2Fh, 01h, 8Bh, 01h, 8Dh, 54h, 24h, 4Ch, 52h, 0FFh, 90h, 88h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 64h, 8Bh, 40h, 28h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h
    db 6Ah, 0FFh, 03h, 0C3h, 50h, 8Bh, 44h, 24h, 2Ch, 50h, 8Bh, 44h, 24h, 70h, 53h, 57h
    db 50h, 0FFh, 92h, 0F4h, 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 6Ah
    db 00h, 0FFh, 92h, 90h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 38h, 8Bh, 54h, 24h, 34h, 8Bh
    db 44h, 24h, 18h, 8Bh, 1Dh, 40h, 1Bh, 2Fh, 01h, 03h, 0C2h, 8Bh, 54h, 24h, 20h, 6Ah
    db 0FFh, 03h, 0CAh, 8Bh, 54h, 24h, 40h, 89h, 6Ch, 24h, 2Ch, 0FFh, 74h, 24h, 2Ch, 8Bh
    db 2Bh, 52h, 51h, 50h, 8Bh, 44h, 24h, 24h, 50h, 8Bh, 0CBh, 0FFh, 95h, 0F4h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 48h, 8Bh, 4Ch, 24h, 2Ch, 6Ah, 0FFh, 03h, 0D6h, 52h, 8Dh, 04h
    db 0Fh, 50h, 8Bh, 44h, 24h, 20h, 56h, 57h, 50h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 19h, 0FFh, 93h, 0F4h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 4Ch, 0C3h
?d_00794790@@YAXXZ ENDP

; ghidra: FUN_00b94b70  retail @ 0x00794B70 size 359
public ?d_00794b70@@YAXXZ
?d_00794b70@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 18h, 17h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 53h, 8Bh, 5Ch, 24h, 3Ch, 85h, 0DBh, 56h
    db 57h, 0Fh, 84h, 2Eh, 01h, 00h, 00h, 83h, 7Bh, 2Ch, 01h, 0Fh, 82h, 24h, 01h, 00h
    db 00h, 8Bh, 7Ch, 24h, 3Ch, 8Dh, 44h, 24h, 28h, 50h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh
    db 0CFh, 0E8h, 06h, 23h, 8Ah, 0FFh, 8Dh, 54h, 24h, 20h, 52h, 8Dh, 44h, 24h, 20h, 50h
    db 8Bh, 0CFh, 0E8h, 84h, 0ADh, 89h, 0FFh, 8Bh, 73h, 30h, 85h, 0F6h, 0Fh, 84h, 0F3h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 44h, 00h, 00h, 00h, 00h, 8Bh, 4Bh, 2Ch, 51h, 51h, 89h
    db 64h, 24h, 20h, 8Bh, 0CCh, 68h, 60h, 9Fh, 0Fh, 01h, 0C7h, 44h, 24h, 40h, 00h, 00h
    db 00h, 00h, 0E8h, 0E9h, 41h, 0Fh, 00h, 8Dh, 54h, 24h, 4Ch, 52h, 0E8h, 8Fh, 45h, 0Fh
    db 00h, 83h, 0C4h, 08h, 8Dh, 44h, 24h, 48h, 89h, 64h, 24h, 1Ch, 8Bh, 0CCh, 50h, 0E8h
    db 0ECh, 37h, 0Fh, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 8Bh, 54h, 24h, 40h, 8Dh
    db 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 52h, 57h, 0E8h, 0ABh, 3Dh, 87h, 0FFh
    db 8Bh, 06h, 83h, 0C4h, 10h, 8Bh, 0CEh, 0FFh, 50h, 1Ch, 8Bh, 0CFh, 8Bh, 0D8h, 0E8h, 3Ah
    db 8Fh, 89h, 0FFh, 3Bh, 0D8h, 74h, 0Fh, 8Bh, 1Eh, 8Bh, 0CFh, 0E8h, 2Dh, 8Fh, 89h, 0FFh
    db 50h, 8Bh, 0CEh, 0FFh, 53h, 18h, 8Bh, 16h, 8Dh, 44h, 24h, 10h, 50h, 8Dh, 4Ch, 24h
    db 10h, 51h, 8Bh, 0CEh, 0FFh, 52h, 3Ch, 0DBh, 44h, 24h, 24h, 0D8h, 0Dh, 3Ch, 53h, 07h
    db 01h, 0DBh, 44h, 24h, 0Ch, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0DEh, 0E9h, 0DAh, 44h, 24h
    db 1Ch, 0E8h, 0B2h, 21h, 26h, 00h, 8Bh, 7Ch, 24h, 20h, 8Bh, 54h, 24h, 28h, 8Bh, 4Ch
    db 24h, 18h, 8Bh, 0D8h, 2Bh, 7Ch, 24h, 10h, 8Bh, 44h, 24h, 14h, 50h, 03h, 0FAh, 8Bh
    db 16h, 51h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 16h, 6Ah, 01h, 6Ah, 01h, 57h, 53h, 8Bh
    db 0CEh, 0FFh, 52h, 38h, 8Dh, 4Ch, 24h, 44h, 0C7h, 44h, 24h, 34h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0Bh, 35h, 0Fh, 00h, 8Bh, 4Ch, 24h, 2Ch, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 2Ch, 0C3h
?d_00794b70@@YAXXZ ENDP

; ghidra: FUN_00b94d30  retail @ 0x00794D30 size 822
public ?d_00794d30@@YAXXZ
?d_00794d30@@YAXXZ PROC
    db 83h, 0ECh, 20h, 53h, 55h, 56h, 8Bh, 74h, 24h, 30h, 57h, 8Dh, 44h, 24h, 24h, 50h
    db 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CEh, 0E8h, 0FFh, 0ABh, 89h, 0FFh, 8Dh, 54h, 24h, 2Ch
    db 52h, 8Dh, 44h, 24h, 2Ch, 50h, 8Bh, 0CEh, 0E8h, 5Fh, 21h, 8Ah, 0FFh, 8Bh, 0CEh, 0E8h
    db 76h, 0F0h, 88h, 0FFh, 0A8h, 08h, 8Bh, 4Ch, 24h, 38h, 75h, 26h, 0F6h, 41h, 08h, 04h
    db 74h, 0Eh, 8Bh, 96h, 0C4h, 00h, 00h, 00h, 8Bh, 86h, 0C8h, 00h, 00h, 00h, 0EBh, 53h
    db 8Bh, 86h, 0B8h, 00h, 00h, 00h, 89h, 44h, 24h, 10h, 8Bh, 86h, 0BCh, 00h, 00h, 00h
    db 0EBh, 45h, 8Bh, 41h, 08h, 0A8h, 02h, 74h, 24h, 0A8h, 04h, 74h, 0Eh, 8Bh, 96h, 30h
    db 01h, 00h, 00h, 8Bh, 86h, 34h, 01h, 00h, 00h, 0EBh, 28h, 8Bh, 86h, 24h, 01h, 00h
    db 00h, 89h, 44h, 24h, 10h, 8Bh, 86h, 28h, 01h, 00h, 00h, 0EBh, 1Ah, 0A8h, 04h, 74h
    db 0Ch, 8Bh, 4Eh, 58h, 8Bh, 46h, 5Ch, 89h, 4Ch, 24h, 10h, 0EBh, 0Ah, 8Bh, 56h, 4Ch
    db 8Bh, 46h, 50h, 89h, 54h, 24h, 10h, 3Dh, 0FFh, 0FFh, 0FFh, 00h, 8Bh, 5Ch, 24h, 20h
    db 8Bh, 6Ch, 24h, 24h, 8Bh, 4Ch, 24h, 28h, 8Bh, 54h, 24h, 2Ch, 8Dh, 34h, 19h, 8Dh
    db 3Ch, 2Ah, 74h, 18h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 57h, 56h, 55h, 53h
    db 68h, 00h, 00h, 80h, 3Fh, 50h, 0FFh, 92h, 0FCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 10h
    db 3Dh, 0FFh, 0FFh, 0FFh, 00h, 74h, 1Ch, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 43h
    db 45h, 4Eh, 4Fh, 57h, 56h, 55h, 53h, 68h, 00h, 00h, 80h, 3Fh, 50h, 0FFh, 92h, 0F8h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 38h, 8Bh, 88h, 9Ch, 01h, 00h, 00h, 85h, 0C9h, 74h
    db 1Ah, 8Bh, 01h, 0FFh, 50h, 0Ch, 85h, 0C0h, 8Bh, 6Ch, 24h, 34h, 74h, 11h, 8Bh, 44h
    db 24h, 38h, 8Bh, 0CDh, 0E8h, 87h, 0F0h, 0FFh, 0FFh, 0EBh, 04h, 8Bh, 6Ch, 24h, 34h, 8Bh
    db 4Ch, 24h, 38h, 8Bh, 81h, 0A4h, 01h, 00h, 00h, 85h, 0C0h, 74h, 4Fh, 8Bh, 7Ch, 24h
    db 24h, 8Bh, 74h, 24h, 2Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 03h, 0F7h, 8Bh
    db 7Ch, 24h, 20h, 89h, 74h, 24h, 10h, 8Bh, 74h, 24h, 28h, 0DBh, 44h, 24h, 10h, 6Ah
    db 0FFh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 03h, 0F7h, 89h, 74h, 24h, 24h, 0DBh, 44h
    db 24h, 24h, 0D9h, 5Ch, 24h, 08h, 0DBh, 44h, 24h, 38h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h
    db 24h, 34h, 0D9h, 1Ch, 24h, 50h, 0FFh, 92h, 0E0h, 00h, 00h, 00h, 8Bh, 0CDh, 0E8h, 75h
    db 16h, 8Bh, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 0Fh, 84h, 91h, 01h, 00h, 00h, 8Bh, 5Fh, 18h
    db 85h, 0DBh, 74h, 79h, 8Bh, 44h, 24h, 24h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 54h, 24h, 20h
    db 03h, 0C8h, 8Bh, 44h, 24h, 28h, 89h, 4Ch, 24h, 10h, 0DBh, 44h, 24h, 10h, 8Bh, 0Dh
    db 70h, 12h, 2Fh, 01h, 03h, 0C2h, 8Bh, 11h, 0D9h, 5Ch, 24h, 14h, 89h, 44h, 24h, 10h
    db 0DBh, 44h, 24h, 10h, 8Bh, 0F1h, 0D9h, 5Ch, 24h, 10h, 0DBh, 44h, 24h, 24h, 0D9h, 5Ch
    db 24h, 18h, 0DBh, 44h, 24h, 20h, 0D9h, 5Ch, 24h, 1Ch, 0FFh, 92h, 0B0h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 14h, 8Bh, 54h, 24h, 10h, 8Bh, 06h, 6Ah, 02h, 6Ah, 0FFh, 51h, 8Bh
    db 4Ch, 24h, 24h, 52h, 8Bh, 54h, 24h, 2Ch, 51h, 52h, 53h, 8Bh, 0CEh, 0FFh, 90h, 0D4h
    db 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 0DCh, 00h, 00h, 00h, 8Ah, 07h, 84h
    db 0C0h, 0Fh, 84h, 85h, 00h, 00h, 00h, 3Ch, 01h, 75h, 3Ah, 8Bh, 4Fh, 08h, 0DBh, 47h
    db 04h, 51h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 83h, 0ECh, 14h, 0D9h, 5Ch, 24h, 10h, 0DBh
    db 44h, 24h, 44h, 0D9h, 5Ch, 24h, 0Ch, 0DBh, 44h, 24h, 40h, 0D9h, 5Ch, 24h, 08h, 0DBh
    db 44h, 24h, 3Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 38h, 0D9h, 1Ch, 24h, 0E8h, 0F4h
    db 3Eh, 8Bh, 0FFh, 0EBh, 3Ch, 3Ch, 02h, 75h, 38h, 8Bh, 57h, 08h, 0DBh, 47h, 04h, 8Bh
    db 0Dh, 70h, 12h, 2Fh, 01h, 52h, 83h, 0ECh, 14h, 0D9h, 5Ch, 24h, 10h, 0DBh, 44h, 24h
    db 44h, 0D9h, 5Ch, 24h, 0Ch, 0DBh, 44h, 24h, 40h, 0D9h, 5Ch, 24h, 08h, 0DBh, 44h, 24h
    db 3Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 38h, 0D9h, 1Ch, 24h, 0E8h, 0ADh, 0F6h, 86h
    db 0FFh, 57h, 8Bh, 0CDh, 0C6h, 07h, 00h, 0E8h, 8Dh, 0DEh, 86h, 0FFh, 80h, 7Fh, 28h, 01h
    db 75h, 0Fh, 8Bh, 44h, 24h, 38h, 57h, 50h, 55h, 0E8h, 0B6h, 0D7h, 89h, 0FFh, 83h, 0C4h
    db 0Ch, 8Ah, 47h, 0Ch, 84h, 0C0h, 74h, 66h, 8Bh, 7Fh, 10h, 81h, 0FFh, 0FFh, 0FFh, 0FFh
    db 00h, 74h, 5Bh, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 54h, 24h, 28h, 8Bh, 44h, 24h, 24h, 83h
    db 0C1h, 02h, 89h, 4Ch, 24h, 38h, 0DBh, 44h, 24h, 38h, 8Bh, 4Ch, 24h, 20h, 57h, 83h
    db 0C2h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 54h
    db 24h, 50h, 0DBh, 44h, 24h, 50h, 48h, 89h, 44h, 24h, 50h, 49h, 0D9h, 5Ch, 24h, 08h
    db 0DBh, 44h, 24h, 50h, 89h, 4Ch, 24h, 50h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch
    db 24h, 04h, 0DBh, 44h, 24h, 50h, 0D9h, 1Ch, 24h, 0E8h, 00h, 46h, 89h, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 20h, 0C3h
?d_00794d30@@YAXXZ ENDP

; ghidra: FUN_00b95140  retail @ 0x00795140 size 2761
_TEXT ENDS
_TEXT$d00b95140 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B95140 size 2761
public ?d_00795140@@YAXXZ
?d_00795140@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va010517CA
    db 050h, 0A0h
    dd ?g_Va01306CE4@@3IA
    db 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 034h, 0A8h, 001h, 053h, 055h, 056h, 057h
    db 075h, 04Eh, 083h, 00Dh
    dd ?g_Va01306CE4@@3IA
    db 001h, 068h
    dd g_Va01127594
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 050h, 000h, 000h, 000h, 000h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 014h, 050h, 0C6h, 044h, 024h, 050h, 001h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CE0
    db 0C6h, 044h, 024h, 04Ch, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 083h, 0CDh, 0FFh, 089h, 06Ch, 024h, 04Ch, 0EBh, 003h, 083h, 0CDh, 0FFh, 0F6h, 005h
    dd ?g_Va01306CE4@@3IA
    db 002h, 075h, 051h, 08Bh, 015h
    dd ?g_Va01306CE4@@3IA
    db 0B8h, 002h, 000h, 000h, 000h, 00Bh, 0D0h, 089h, 015h
    dd ?g_Va01306CE4@@3IA
    db 068h
    dd g_Va01127584
    db 08Dh, 04Ch, 024h, 018h, 089h, 044h, 024h, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 0C6h, 044h, 024h, 050h, 003h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CDC
    db 0C6h, 044h, 024h, 04Ch, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 0F6h, 005h
    dd ?g_Va01306CE4@@3IA
    db 004h, 075h, 051h, 08Bh, 015h
    dd ?g_Va01306CE4@@3IA
    db 0B8h, 004h, 000h, 000h, 000h, 00Bh, 0D0h, 089h, 015h
    dd ?g_Va01306CE4@@3IA
    db 068h
    dd g_Va010FBF68
    db 08Dh, 04Ch, 024h, 018h, 089h, 044h, 024h, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 054h, 024h, 014h, 052h, 0C6h, 044h, 024h, 050h, 005h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CD8
    db 0C6h, 044h, 024h, 04Ch, 004h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 0F6h, 005h
    dd ?g_Va01306CE4@@3IA
    db 008h, 075h, 049h, 083h, 00Dh
    dd ?g_Va01306CE4@@3IA
    db 008h, 0BBh, 006h, 000h, 000h, 000h, 068h
    dd g_Va010FBF58
    db 08Dh, 04Ch, 024h, 018h, 089h, 05Ch, 024h, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 014h, 050h, 0C6h, 044h, 024h, 050h, 007h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CD4
    db 088h, 05Ch, 024h, 04Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 08Ah, 00Dh
    dd ?g_Va01306CE4@@3IA
    db 0B8h, 010h, 000h, 000h, 000h, 084h, 0C8h, 075h, 048h, 009h, 005h
    dd ?g_Va01306CE4@@3IA
    db 068h
    dd g_Va010FBF48
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 050h, 008h, 000h, 000h, 000h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 0C6h, 044h, 024h, 050h, 009h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CD0
    db 0C6h, 044h, 024h, 04Ch, 008h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 08Ah, 00Dh
    dd ?g_Va01306CE4@@3IA
    db 0B8h, 020h, 000h, 000h, 000h, 084h, 0C8h, 075h, 048h, 009h, 005h
    dd ?g_Va01306CE4@@3IA
    db 0BBh, 00Ah, 000h, 000h, 000h, 068h
    dd g_Va010F73E8
    db 08Dh, 04Ch, 024h, 018h, 089h, 05Ch, 024h, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 054h, 024h, 014h, 052h, 0C6h, 044h, 024h, 050h, 00Bh
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CCC
    db 088h, 05Ch, 024h, 04Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 08Ah, 00Dh
    dd ?g_Va01306CE4@@3IA
    db 0B8h, 040h, 000h, 000h, 000h, 084h, 0C8h, 075h, 048h, 009h, 005h
    dd ?g_Va01306CE4@@3IA
    db 0BBh, 00Ch, 000h, 000h, 000h, 068h
    dd g_Va010F73D0
    db 08Dh, 04Ch, 024h, 018h, 089h, 05Ch, 024h, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 014h, 050h, 0C6h, 044h, 024h, 050h, 00Dh
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0A3h
    dd g_Va01306CC8
    db 088h, 05Ch, 024h, 04Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 089h, 06Ch, 024h, 04Ch, 08Bh, 07Ch, 024h, 054h, 08Bh, 04Fh, 048h, 089h, 04Ch, 024h, 010h, 08Bh
    db 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 020h, 000h, 075h, 06Ch, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 000h, 040h, 075h, 05Eh, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A8h, 008h, 08Bh, 054h, 024h, 058h, 075h, 01Eh, 0F6h, 042h, 008h, 004h, 074h, 00Ch, 08Bh, 087h
    db 0C0h, 000h, 000h, 000h, 089h, 044h, 024h, 010h, 0EBh, 03Dh, 08Bh, 08Fh, 0B4h, 000h, 000h, 000h
    db 089h, 04Ch, 024h, 010h, 0EBh, 031h, 08Bh, 042h, 008h, 0A8h, 002h, 074h, 01Ch, 0A8h, 004h, 074h
    db 00Ch, 08Bh, 087h, 02Ch, 001h, 000h, 000h, 089h, 044h, 024h, 010h, 0EBh, 01Ah, 08Bh, 08Fh, 020h
    db 001h, 000h, 000h, 089h, 04Ch, 024h, 010h, 0EBh, 00Eh, 0A8h, 004h, 074h, 00Ah, 08Bh, 097h, 02Ch
    db 001h, 000h, 000h, 089h, 054h, 024h, 010h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 08Bh, 0D8h, 08Bh, 044h, 024h, 010h, 0C1h, 0EBh, 01Ah, 080h, 0E3h, 001h, 085h, 0C0h, 088h, 05Ch
    db 024h, 054h, 00Fh, 084h, 0C1h, 001h, 000h, 000h, 08Dh, 044h, 024h, 030h, 050h, 08Dh, 04Ch, 024h
    db 030h, 051h, 08Bh, 0CFh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 038h, 052h, 08Dh, 044h, 024h, 038h, 050h, 08Bh, 0CFh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 054h, 024h, 058h, 08Bh, 09Ah, 07Ch, 001h, 000h, 000h, 08Bh, 044h, 024h, 02Ch, 08Bh, 0B2h
    db 080h, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 030h, 08Bh, 054h, 024h, 034h, 003h, 0C3h, 003h, 0CEh
    db 08Dh, 034h, 010h, 089h, 044h, 024h, 02Ch, 08Bh, 044h, 024h, 038h, 08Dh, 01Ch, 008h, 089h, 04Ch
    db 024h, 030h, 08Bh, 0CFh, 089h, 074h, 024h, 03Ch, 089h, 05Ch, 024h, 040h, 0BDh, 002h, 000h, 000h
    db 000h, 0C7h, 044h, 024h, 014h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 020h, 000h, 074h, 044h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 000h, 040h, 075h, 036h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A8h, 008h, 075h, 02Bh, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 040h, 000h, 075h, 01Dh, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 000h, 001h, 075h, 007h, 0BDh, 001h, 000h, 000h, 000h, 0EBh, 008h, 0C7h, 044h
    db 024h, 014h, 090h, 090h, 090h, 0FFh, 08Ah, 044h, 024h, 054h, 084h, 0C0h, 00Fh, 084h, 08Bh, 000h
    db 000h, 000h, 033h, 0C9h, 083h, 0FDh, 001h, 00Fh, 095h, 0C1h, 049h, 083h, 0E1h, 004h, 08Bh, 0E9h
    call ?d_00933af0@@YAXXZ
    call ?Rva00933B80StencilBlendA@@YAXXZ
    db 08Bh, 04Ch, 024h, 030h, 08Bh, 044h, 024h, 02Ch, 02Bh, 0D9h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 089h, 05Ch, 024h, 01Ch, 0DBh, 044h, 024h, 01Ch, 02Bh, 0F0h, 089h, 074h, 024h, 01Ch
    db 0D9h, 05Ch, 024h, 018h, 08Bh, 0F1h, 0DBh, 044h, 024h, 01Ch, 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h
    db 024h, 030h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 028h, 0FFh, 092h
    db 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 08Bh, 006h, 06Ah, 0FFh
    db 051h, 08Bh, 04Ch, 024h, 02Ch, 052h, 08Bh, 054h, 024h, 034h, 051h, 052h, 08Bh, 0CEh, 0FFh, 090h
    db 0C4h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h
    call ?Rva00933BF0StencilBlendB@@YAXXZ
    db 0DBh, 044h, 024h, 030h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 08Bh, 0F1h, 0D9h, 05Ch, 024h, 028h, 0DBh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 024h
    db 0FFh, 092h, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 014h, 0DBh, 044h, 024h, 040h, 08Bh, 054h
    db 024h, 028h, 08Bh, 006h, 055h, 051h, 08Bh, 04Ch, 024h, 02Ch, 083h, 0ECh, 008h, 0D9h, 05Ch, 024h
    db 004h, 0DBh, 044h, 024h, 04Ch, 0D9h, 01Ch, 024h, 052h, 08Bh, 054h, 024h, 024h, 051h, 052h, 08Bh
    db 0CEh, 0FFh, 090h, 0D4h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h
    db 000h, 08Ah, 044h, 024h, 054h, 084h, 0C0h, 074h, 005h
    call ?Rva00933810StencilStateA@@YAXXZ
    db 08Ah, 05Ch, 024h, 054h, 083h, 0CDh, 0FFh, 08Bh, 074h, 024h, 058h, 08Bh, 086h, 09Ch, 001h, 000h
    db 000h, 085h, 0C0h, 074h, 014h, 08Bh, 0C8h, 08Bh, 011h, 0FFh, 052h, 00Ch, 085h, 0C0h, 074h, 009h
    db 08Bh, 0C6h, 08Bh, 0CFh
    call ?drawButtonText@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
    db 08Dh, 044h, 024h, 030h, 050h, 08Dh, 04Ch, 024h, 030h, 051h, 08Bh, 0CFh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 038h, 052h, 08Dh, 044h, 024h, 038h, 050h, 08Bh, 0CFh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 086h, 0A4h, 001h, 000h, 000h, 085h, 0C0h, 074h, 04Eh, 08Bh, 074h, 024h, 030h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 055h, 08Bh, 06Ch, 024h, 03Ch, 08Bh, 011h, 003h, 0EEh, 08Bh, 074h, 024h, 038h, 089h, 06Ch, 024h
    db 02Ch, 08Bh, 06Ch, 024h, 030h, 0DBh, 044h, 024h, 02Ch, 083h, 0ECh, 010h, 003h, 0EEh, 0D9h, 05Ch
    db 024h, 00Ch, 089h, 06Ch, 024h, 03Ch, 0DBh, 044h, 024h, 03Ch, 0D9h, 05Ch, 024h, 008h, 0DBh, 044h
    db 024h, 044h, 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 040h, 0D9h, 01Ch, 024h, 050h, 0FFh, 092h
    db 0E0h, 000h, 000h, 000h, 08Bh, 0CFh
    call ?j_00046538@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 00Fh, 084h, 097h, 002h, 000h, 000h, 08Bh, 05Dh, 018h, 085h, 0DBh, 074h
    db 079h, 08Bh, 044h, 024h, 030h, 08Bh, 04Ch, 024h, 038h, 08Bh, 054h, 024h, 02Ch, 003h, 0C8h, 08Bh
    db 044h, 024h, 034h, 089h, 04Ch, 024h, 028h, 0DBh, 044h, 024h, 028h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 003h, 0D0h, 089h, 054h, 024h, 028h, 08Bh, 011h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h, 028h
    db 08Bh, 0F1h, 0D9h, 05Ch, 024h, 028h, 0DBh, 044h, 024h, 030h, 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h
    db 024h, 02Ch, 0D9h, 05Ch, 024h, 018h, 0FFh, 092h, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 024h
    db 08Bh, 054h, 024h, 028h, 08Bh, 006h, 06Ah, 002h, 06Ah, 0FFh, 051h, 08Bh, 04Ch, 024h, 028h, 052h
    db 08Bh, 054h, 024h, 028h, 051h, 052h, 053h, 08Bh, 0CEh, 0FFh, 090h, 0D4h, 000h, 000h, 000h, 08Bh
    db 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h, 08Ah, 045h, 000h, 084h, 0C0h, 00Fh, 084h
    db 07Fh, 001h, 000h, 000h, 03Ch, 001h, 075h, 049h, 08Bh, 04Dh, 004h, 085h, 0C9h, 089h, 04Ch, 024h
    db 010h, 07Eh, 03Eh, 08Bh, 04Dh, 008h, 0DBh, 044h, 024h, 010h, 051h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 083h, 0ECh, 014h, 0D9h, 05Ch, 024h, 010h, 0DBh, 044h, 024h, 050h, 0D9h, 05Ch, 024h, 00Ch, 0DBh
    db 044h, 024h, 04Ch, 0D9h, 05Ch, 024h, 008h, 0DBh, 044h, 024h, 048h, 0D9h, 05Ch, 024h, 004h, 0DBh
    db 044h, 024h, 044h, 0D9h, 01Ch, 024h
    call ?j_00048e87@@YAXXZ
    db 0E9h, 026h, 001h, 000h, 000h, 03Ch, 002h, 00Fh, 085h, 01Eh, 001h, 000h, 000h, 08Bh, 045h, 004h
    db 083h, 0F8h, 064h, 089h, 044h, 024h, 010h, 00Fh, 08Dh, 00Eh, 001h, 000h, 000h, 0A1h
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 085h, 0C0h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 074h, 03Ah, 08Bh, 040h, 00Ch, 085h
    db 0C0h, 074h, 033h, 08Bh, 040h, 004h, 085h, 0C0h, 074h, 01Ch, 08Ah, 088h, 018h, 001h, 000h, 000h
    db 084h, 0C9h, 074h, 012h, 08Bh, 015h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 082h, 018h, 012h, 000h, 000h, 089h, 044h, 024h, 014h, 0EBh, 010h, 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 091h, 014h, 012h, 000h, 000h, 089h, 054h, 024h, 014h, 0DBh, 044h, 024h, 034h, 08Bh, 045h
    db 008h, 050h, 0A1h
    dd g_Va01306CCC
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 051h, 0DBh, 044h, 024h, 040h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0DBh, 044h, 024h, 034h, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h, 038h, 0D8h, 0C1h
    db 0D9h, 05Ch, 024h, 028h, 0D9h, 0C9h, 0D8h, 00Dh
    dd g_Va01127580
    db 0D9h, 05Ch, 024h, 044h, 0D8h, 00Dh
    dd g_Va01127580
    db 0D9h, 044h, 024h, 028h, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 030h, 0D9h, 044h, 024h, 024h, 08Bh, 05Ch
    db 024h, 030h, 0D8h, 044h, 024h, 044h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 028h, 08Bh, 074h
    db 024h, 02Ch, 0D8h, 0E1h, 0D9h, 05Ch, 024h, 020h, 08Bh, 04Ch, 024h, 020h, 0DDh, 0D8h, 0D9h, 044h
    db 024h, 024h, 0D8h, 064h, 024h, 044h, 0D9h, 05Ch, 024h, 024h, 08Bh, 054h, 024h, 024h, 0DBh, 044h
    db 024h, 018h, 0D9h, 01Ch, 024h, 053h, 056h, 051h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 052h, 050h
    call ?j_00034338@@YAXXZ
    db 0DBh, 045h, 004h, 08Bh, 04Ch, 024h, 014h, 08Bh, 054h, 024h, 018h, 08Bh, 044h, 024h, 01Ch, 051h
    db 051h, 08Bh, 00Dh
    dd g_Va01306CC8
    db 0D9h, 01Ch, 024h, 053h, 056h, 052h, 050h, 051h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    call ?j_00034338@@YAXXZ
    db 055h, 08Bh, 0CFh, 0C6h, 045h, 000h, 000h
    call ?j_00002e69@@YAXXZ
    db 08Ah, 044h, 024h, 054h, 084h, 0C0h, 075h, 06Ch, 08Ah, 045h, 00Ch, 084h, 0C0h, 074h, 065h, 08Bh
    db 045h, 010h, 03Dh, 0FFh, 0FFh, 0FFh, 000h, 074h, 05Bh, 08Bh, 054h, 024h, 038h, 08Bh, 04Ch, 024h
    db 030h, 083h, 0C2h, 002h, 050h, 08Bh, 044h, 024h, 038h, 089h, 054h, 024h, 02Ch, 0DBh, 044h, 024h
    db 02Ch, 08Bh, 054h, 024h, 030h, 083h, 0C0h, 002h, 068h, 000h, 000h, 080h, 03Fh, 083h, 0ECh, 010h
    db 0D9h, 05Ch, 024h, 00Ch, 089h, 044h, 024h, 040h, 0DBh, 044h, 024h, 040h, 049h, 089h, 04Ch, 024h
    db 040h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 0D9h, 05Ch, 024h, 008h, 04Ah, 0DBh, 044h, 024h, 040h, 089h, 054h, 024h, 040h, 0D9h, 05Ch, 024h
    db 004h, 0DBh, 044h, 024h, 040h, 0D9h, 01Ch, 024h
    call ?j_0002965e@@YAXXZ
    db 080h, 07Dh, 028h, 001h, 075h, 00Fh, 08Bh, 044h, 024h, 058h, 055h, 050h, 057h
    call ?j_000327a4@@YAXXZ
    db 083h, 0C4h, 00Ch, 08Ah, 05Ch, 024h, 054h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 080h, 000h, 00Fh, 084h, 083h, 000h, 000h, 000h, 084h, 0DBh, 075h, 07Fh, 08Bh
    db 04Ch, 024h, 030h, 08Bh, 054h, 024h, 038h, 08Bh, 044h, 024h, 034h, 08Bh, 02Dh
    dd g_Va01306CDC
    db 003h, 0D1h, 08Bh, 04Ch, 024h, 02Ch, 089h, 054h, 024h, 054h, 0DBh, 044h, 024h, 054h, 003h, 0C8h
    db 089h, 04Ch, 024h, 054h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 0D9h, 05Ch, 024h, 028h, 0DBh, 044h, 024h, 054h, 08Bh, 0F1h, 0D9h, 05Ch, 024h, 054h
    db 0DBh, 044h, 024h, 030h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 01Ch
    db 0FFh, 092h, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 028h, 08Bh, 054h, 024h, 054h, 08Bh, 006h
    db 06Ah, 002h, 06Ah, 0FFh, 051h, 08Bh, 04Ch, 024h, 030h, 052h, 08Bh, 054h, 024h, 02Ch, 051h, 052h
    db 055h, 08Bh, 0CEh, 0FFh, 090h, 0D4h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh
    db 000h, 000h, 000h, 0A1h
    dd ?g_Va01306CE4@@3IA
    db 084h, 0C0h, 078h, 014h, 00Dh, 080h, 000h, 000h, 000h, 0A3h
    dd ?g_Va01306CE4@@3IA
    db 0C7h, 005h
    dd g_Va01306CC4
    db 0FFh, 0FFh, 0FFh, 0FFh, 0F6h, 0C4h, 001h, 075h, 014h, 00Dh, 000h, 001h, 000h, 000h, 0A3h
    dd ?g_Va01306CE4@@3IA
    db 0C7h, 005h
    dd g_Va01306CC0
    db 090h, 090h, 090h, 0FFh, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 085h, 0C0h, 08Bh, 035h
    dd g_Va01306CC0
    db 078h, 006h, 08Bh, 035h
    dd g_Va01306CC4
    db 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 020h, 000h, 00Fh, 084h, 07Dh, 001h, 000h, 000h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A8h, 008h, 00Fh, 084h, 06Eh, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 058h, 08Bh, 041h, 008h, 0A8h
    db 002h, 00Fh, 084h, 0EDh, 000h, 000h, 000h, 0A8h, 004h, 074h, 074h, 084h, 0DBh, 074h, 00Bh, 08Bh
    db 03Dh
    dd g_Va01306CD8
    db 0E9h, 056h, 001h, 000h, 000h, 08Bh, 054h, 024h, 030h, 08Bh, 044h, 024h, 038h, 08Bh, 04Ch, 024h
    db 034h, 003h, 0C2h, 08Bh, 054h, 024h, 02Ch, 06Ah, 002h, 089h, 044h, 024h, 05Ch, 0DBh, 044h, 024h
    db 05Ch, 0A1h
    dd g_Va01306CE0
    db 056h, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 003h, 0D1h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 089h, 054h, 024h, 070h, 0DBh, 044h, 024h, 070h, 0D9h, 05Ch, 024h, 008h, 0DBh, 044h, 024h, 048h
    db 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 044h, 0D9h, 01Ch, 024h, 050h
    call ?j_0000a114@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 034h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 040h, 0C3h, 084h, 0DBh, 074h, 00Bh, 08Bh, 03Dh
    dd g_Va01306CD4
    db 0E9h, 0E2h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 030h, 08Bh, 054h, 024h, 038h, 08Bh, 044h, 024h
    db 034h, 003h, 0D1h, 08Bh, 04Ch, 024h, 02Ch, 06Ah, 002h, 089h, 054h, 024h, 05Ch, 0DBh, 044h, 024h
    db 05Ch, 08Bh, 015h
    dd g_Va01306CDC
    db 056h, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 003h, 0C8h, 089h, 04Ch, 024h, 070h, 0DBh, 044h
    db 024h, 070h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 0D9h, 05Ch, 024h, 008h, 0DBh, 044h, 024h, 048h, 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 044h
    db 0D9h, 01Ch, 024h, 052h
    call ?j_0000a114@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 034h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 040h, 0C3h, 084h, 0DBh, 075h, 072h, 0A8h, 004h, 00Fh, 084h, 081h, 000h, 000h, 000h, 08Bh
    db 044h, 024h, 030h, 08Bh, 04Ch, 024h, 038h, 08Bh, 054h, 024h, 034h, 003h, 0C8h, 08Bh, 044h, 024h
    db 02Ch, 089h, 04Ch, 024h, 058h, 0DBh, 044h, 024h, 058h, 08Bh, 00Dh
    dd g_Va01306CE0
    db 06Ah, 002h, 056h, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 003h, 0C2h, 089h, 044h, 024h, 070h
    db 0DBh, 044h, 024h, 070h, 0D9h, 05Ch, 024h, 008h, 0DBh, 044h, 024h, 048h, 0D9h, 05Ch, 024h, 004h
    db 0DBh, 044h, 024h, 044h, 0D9h, 01Ch, 024h, 051h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    call ?j_0000a114@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 034h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 040h, 0C3h, 084h, 0DBh, 074h, 017h, 08Bh, 03Dh
    dd g_Va01306CD0
    db 08Dh, 04Ch, 024h, 02Ch, 08Dh, 044h, 024h, 034h, 056h
    call ?d_00794040@@YAXXZ
    db 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 044h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 040h, 0C3h
?d_00795140@@YAXXZ ENDP
_TEXT$d00b95140 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b95ec0  retail @ 0x00795EC0 size 14
public ?d_00795ec0@@YAXXZ
?d_00795ec0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 51h, 0E8h, 54h, 0DFh, 89h, 0FFh, 83h, 0C4h, 08h
?d_00795ec0@@YAXXZ ENDP

; ghidra: FUN_00b95ec0  retail @ 0x00795ECE size 8
public ?d_00795ece@@YAXXZ
?d_00795ece@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00795ece@@YAXXZ ENDP

; ghidra: FUN_00b95ee0  retail @ 0x00795EE0 size 181
public ?d_00795ee0@@YAXXZ
?d_00795ee0@@YAXXZ PROC
    db 83h, 0ECh, 10h, 56h, 8Bh, 74h, 24h, 18h, 56h, 0E8h, 08h, 0B8h, 89h, 0FFh, 83h, 0C4h
    db 04h, 84h, 0C0h, 74h, 13h, 8Bh, 44h, 24h, 1Ch, 50h, 56h, 0E8h, 0FDh, 6Bh, 88h, 0FFh
    db 83h, 0C4h, 08h, 5Eh, 83h, 0C4h, 10h, 0C3h, 8Bh, 86h, 84h, 00h, 00h, 00h, 85h, 0C0h
    db 74h, 70h, 57h, 8Bh, 7Ch, 24h, 20h, 0F7h, 47h, 08h, 00h, 00h, 20h, 00h, 74h, 52h
    db 8Dh, 4Ch, 24h, 0Ch, 51h, 8Dh, 54h, 24h, 0Ch, 52h, 8Bh, 0CEh, 0E8h, 1Ah, 9Ah, 89h
    db 0FFh, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0E8h, 7Ah, 0Fh
    db 8Ah, 0FFh, 8Bh, 44h, 24h, 08h, 8Bh, 97h, 7Ch, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch
    db 03h, 0C2h, 89h, 44h, 24h, 08h, 8Bh, 87h, 80h, 01h, 00h, 00h, 03h, 0C8h, 57h, 56h
    db 89h, 4Ch, 24h, 14h, 0E8h, 42h, 0B7h, 89h, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 83h, 0C4h
    db 10h, 0C3h, 57h, 56h, 0E8h, 0F5h, 0Dh, 89h, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 83h, 0C4h
    db 10h, 0C3h, 8Bh, 4Ch, 24h, 1Ch, 51h, 56h, 0E8h, 1Eh, 0B7h, 89h, 0FFh, 83h, 0C4h, 08h
    db 5Eh, 83h, 0C4h, 10h, 0C3h
?d_00795ee0@@YAXXZ ENDP

; ghidra: FUN_00b961d0  retail @ 0x007961D0 size 25
public ?d_007961d0@@YAXXZ
?d_007961d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0A1h, 0Eh, 8Ah, 0FFh, 0C7h, 06h, 0A4h
    db 75h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007961d0@@YAXXZ ENDP

; ghidra: FUN_00b96200  retail @ 0x00796200 size 27
public ?d_00796200@@YAXXZ
?d_00796200@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 50h, 8Bh, 44h, 24h, 08h, 52h, 50h, 51h
    db 0E8h, 58h, 0F0h, 86h, 0FFh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_00796200@@YAXXZ ENDP

; ghidra: FUN_00b96260  retail @ 0x00796260 size 25
public ?d_00796260@@YAXXZ
?d_00796260@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 11h, 0Eh, 8Ah, 0FFh, 0C7h, 06h, 0D8h
    db 75h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00796260@@YAXXZ ENDP

; ghidra: FUN_00b96310  retail @ 0x00796310 size 289
public ?d_00796310@@YAXXZ
?d_00796310@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 53h, 56h, 8Bh, 0D8h, 8Bh, 0B3h, 9Ch, 01h, 00h, 00h, 85h, 0F6h, 57h
    db 8Bh, 0F9h, 0Fh, 84h, 02h, 01h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 0Ch, 85h
    db 0C0h, 0Fh, 84h, 0F3h, 00h, 00h, 00h, 55h, 8Dh, 4Ch, 24h, 28h, 51h, 8Dh, 54h, 24h
    db 28h, 52h, 8Bh, 0CFh, 0E8h, 02h, 96h, 89h, 0FFh, 8Dh, 44h, 24h, 20h, 50h, 8Dh, 4Ch
    db 24h, 20h, 51h, 8Bh, 0CFh, 0E8h, 62h, 0Bh, 8Ah, 0FFh, 8Bh, 0CFh, 0E8h, 79h, 0DAh, 88h
    db 0FFh, 0A8h, 08h, 8Bh, 0CFh, 75h, 10h, 0E8h, 7Ch, 71h, 89h, 0FFh, 8Bh, 0CFh, 8Bh, 0E8h
    db 0E8h, 0E7h, 61h, 89h, 0FFh, 0EBh, 24h, 0F6h, 43h, 08h, 02h, 74h, 10h, 0E8h, 0A6h, 3Dh
    db 87h, 0FFh, 8Bh, 0CFh, 8Bh, 0E8h, 0E8h, 0D6h, 35h, 88h, 0FFh, 0EBh, 0Eh, 0E8h, 3Fh, 42h
    db 89h, 0FFh, 8Bh, 0CFh, 8Bh, 0E8h, 0E8h, 4Fh, 74h, 89h, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 89h
    db 44h, 24h, 10h, 0FFh, 52h, 1Ch, 8Bh, 0CFh, 8Bh, 0D8h, 0E8h, 0CEh, 77h, 89h, 0FFh, 3Bh
    db 0D8h, 74h, 0Fh, 8Bh, 1Eh, 8Bh, 0CFh, 0E8h, 0C1h, 77h, 89h, 0FFh, 50h, 8Bh, 0CEh, 0FFh
    db 53h, 18h, 8Bh, 06h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 54h, 24h, 18h, 52h, 8Bh, 0CEh
    db 0FFh, 50h, 3Ch, 8Bh, 44h, 24h, 14h, 99h, 2Bh, 0C2h, 8Bh, 0C8h, 8Bh, 44h, 24h, 1Ch
    db 99h, 2Bh, 0C2h, 8Bh, 54h, 24h, 24h, 8Bh, 0F8h, 8Bh, 44h, 24h, 18h, 0D1h, 0F9h, 0D1h
    db 0FFh, 2Bh, 0F9h, 03h, 0FAh, 99h, 2Bh, 0C2h, 8Bh, 0C8h, 8Bh, 44h, 24h, 20h, 99h, 2Bh
    db 0C2h, 8Bh, 54h, 24h, 28h, 8Bh, 0D8h, 8Bh, 44h, 24h, 10h, 0D1h, 0F9h, 0D1h, 0FBh, 2Bh
    db 0D9h, 50h, 03h, 0DAh, 8Bh, 16h, 55h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 16h, 6Ah, 01h
    db 6Ah, 01h, 53h, 57h, 8Bh, 0CEh, 0FFh, 52h, 38h, 5Dh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 1Ch
    db 0C3h
?d_00796310@@YAXXZ ENDP

; ghidra: FUN_00b96480  retail @ 0x00796480 size 519
public ?d_00796480@@YAXXZ
?d_00796480@@YAXXZ PROC
    db 83h, 0ECh, 20h, 53h, 55h, 56h, 8Bh, 74h, 24h, 30h, 57h, 8Dh, 44h, 24h, 1Ch, 50h
    db 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CEh, 0E8h, 0AFh, 94h, 89h, 0FFh, 8Dh, 54h, 24h, 24h
    db 52h, 8Dh, 44h, 24h, 24h, 50h, 8Bh, 0CEh, 0E8h, 0Fh, 0Ah, 8Ah, 0FFh, 8Bh, 0CEh, 0E8h
    db 26h, 0D9h, 88h, 0FFh, 0A8h, 08h, 8Bh, 54h, 24h, 38h, 75h, 2Ah, 0F6h, 42h, 08h, 04h
    db 8Bh, 8Eh, 0B8h, 00h, 00h, 00h, 8Bh, 9Eh, 0BCh, 00h, 00h, 00h, 89h, 4Ch, 24h, 14h
    db 74h, 08h, 8Bh, 86h, 0D0h, 00h, 00h, 00h, 0EBh, 55h, 8Bh, 8Eh, 0C4h, 00h, 00h, 00h
    db 89h, 4Ch, 24h, 10h, 0EBh, 4Dh, 8Bh, 42h, 08h, 0A8h, 02h, 74h, 28h, 0A8h, 04h, 8Bh
    db 8Eh, 24h, 01h, 00h, 00h, 8Bh, 9Eh, 28h, 01h, 00h, 00h, 89h, 4Ch, 24h, 14h, 74h
    db 0Ch, 8Bh, 96h, 3Ch, 01h, 00h, 00h, 89h, 54h, 24h, 10h, 0EBh, 26h, 8Bh, 86h, 30h
    db 01h, 00h, 00h, 0EBh, 1Ah, 0A8h, 04h, 8Bh, 4Eh, 4Ch, 8Bh, 5Eh, 50h, 89h, 4Ch, 24h
    db 14h, 74h, 09h, 8Bh, 56h, 64h, 89h, 54h, 24h, 10h, 0EBh, 07h, 8Bh, 46h, 58h, 89h
    db 44h, 24h, 10h, 8Bh, 44h, 24h, 18h, 8Bh, 54h, 24h, 20h, 8Bh, 4Ch, 24h, 1Ch, 8Dh
    db 34h, 02h, 8Bh, 54h, 24h, 24h, 8Dh, 3Ch, 0Ah, 8Bh, 15h, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 12h, 57h, 56h, 51h, 50h, 68h, 00h, 00h, 80h, 3Fh, 89h, 4Ch, 24h, 40h, 8Bh, 0Dh
    db 40h, 1Bh, 2Fh, 01h, 53h, 8Bh, 0E8h, 0FFh, 92h, 0FCh, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 2Ch, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 45h, 40h, 4Eh, 4Fh, 57h, 56h, 50h
    db 8Bh, 44h, 24h, 20h, 55h, 68h, 00h, 00h, 80h, 3Fh, 50h, 0FFh, 92h, 0F8h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 18h, 8Dh, 04h, 11h, 8Bh, 54h, 24h, 1Ch
    db 8Dh, 34h, 11h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 39h, 56h, 50h, 52h, 50h, 68h
    db 00h, 00h, 80h, 3Fh, 53h, 0FFh, 97h, 00h, 01h, 00h, 00h, 8Bh, 44h, 24h, 18h, 8Bh
    db 4Ch, 24h, 1Ch, 8Bh, 7Ch, 24h, 24h, 8Dh, 50h, 01h, 8Dh, 44h, 07h, 0FFh, 8Dh, 7Ch
    db 0Fh, 0FFh, 57h, 50h, 8Dh, 71h, 01h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 56h
    db 52h, 8Bh, 0C5h, 8Bh, 6Ch, 24h, 20h, 68h, 00h, 00h, 80h, 3Fh, 55h, 0FFh, 90h, 0F8h
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 1Ch, 8Bh, 44h, 24h, 20h, 8Bh
    db 7Ch, 24h, 18h, 2Bh, 0C1h, 8Dh, 34h, 11h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 56h, 03h
    db 0C7h, 8Bh, 39h, 50h, 52h, 50h, 68h, 00h, 00h, 80h, 3Fh, 53h, 0FFh, 97h, 00h, 01h
    db 00h, 00h, 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 24h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 74h
    db 24h, 18h, 8Bh, 0C1h, 2Bh, 0C2h, 8Dh, 54h, 3Ah, 0FFh, 52h, 03h, 0C6h, 8Dh, 74h, 31h
    db 0FFh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 56h, 8Dh, 5Fh, 01h, 8Bh, 39h, 53h, 50h, 68h
    db 00h, 00h, 80h, 3Fh, 55h, 0FFh, 97h, 0F8h, 00h, 00h, 00h, 8Bh, 74h, 24h, 38h, 8Bh
    db 86h, 9Ch, 01h, 00h, 00h, 85h, 0C0h, 74h, 16h, 8Bh, 0C8h, 8Bh, 01h, 0FFh, 50h, 0Ch
    db 85h, 0C0h, 74h, 0Bh, 8Bh, 4Ch, 24h, 34h, 8Bh, 0C6h, 0E8h, 91h, 0FCh, 0FFh, 0FFh, 5Fh
    db 5Eh, 5Dh, 5Bh, 83h, 0C4h, 20h, 0C3h
?d_00796480@@YAXXZ ENDP

; ghidra: FUN_00b96710  retail @ 0x00796710 size 539
_TEXT ENDS
_TEXT$d00b96710 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B96710 size 539
public ?d_00796710@@YAXXZ
?d_00796710@@YAXXZ PROC
    db 083h, 0ECh, 03Ch, 053h, 055h, 056h, 057h, 08Bh, 07Ch, 024h, 050h, 08Dh, 044h, 024h, 028h, 050h
    db 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 0CFh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 038h, 052h, 08Dh, 044h, 024h, 038h, 050h, 08Bh, 0CFh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 06Ch, 024h, 054h, 0F6h, 045h, 008h, 004h, 08Bh, 0B5h, 07Ch, 001h, 000h, 000h, 08Bh, 09Dh
    db 080h, 001h, 000h, 000h, 089h, 074h, 024h, 020h, 089h, 05Ch, 024h, 018h, 074h, 014h, 08Bh, 08Fh
    db 044h, 001h, 000h, 000h, 08Bh, 0AFh, 050h, 001h, 000h, 000h, 08Bh, 097h, 05Ch, 001h, 000h, 000h
    db 0EBh, 052h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A8h, 008h, 075h, 01Ch, 08Bh, 087h, 0B4h, 000h, 000h, 000h, 08Bh, 08Fh, 0CCh, 000h, 000h, 000h
    db 08Bh, 0AFh, 0C0h, 000h, 000h, 000h, 089h, 044h, 024h, 010h, 089h, 04Ch, 024h, 014h, 0EBh, 033h
    db 0F6h, 045h, 008h, 002h, 074h, 01Ch, 08Bh, 097h, 020h, 001h, 000h, 000h, 08Bh, 087h, 038h, 001h
    db 000h, 000h, 08Bh, 0AFh, 02Ch, 001h, 000h, 000h, 089h, 054h, 024h, 010h, 089h, 044h, 024h, 014h
    db 0EBh, 011h, 08Bh, 04Fh, 048h, 08Bh, 06Fh, 054h, 08Bh, 057h, 060h, 089h, 04Ch, 024h, 010h, 089h
    db 054h, 024h, 014h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 00Fh, 084h, 04Eh, 001h, 000h, 000h, 085h
    db 0EDh, 00Fh, 084h, 046h, 001h, 000h, 000h, 08Bh, 054h, 024h, 014h, 085h, 0D2h, 00Fh, 084h, 03Ah
    db 001h, 000h, 000h, 08Bh, 078h, 024h, 08Bh, 044h, 024h, 024h, 003h, 0FEh, 02Bh, 072h, 024h, 003h
    db 074h, 024h, 034h, 003h, 0F8h, 003h, 0F0h, 08Bh, 0C6h, 02Bh, 0C7h, 099h, 0F7h, 07Dh, 024h, 08Bh
    db 04Ch, 024h, 038h, 08Bh, 054h, 024h, 018h, 003h, 0D9h, 08Bh, 04Ch, 024h, 028h, 003h, 0D1h, 003h
    db 0D9h, 089h, 04Ch, 024h, 040h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 089h, 054h, 024h, 030h, 08Dh, 054h, 024h, 03Ch, 089h, 07Ch, 024h, 03Ch, 089h, 05Ch, 024h, 048h
    db 089h, 074h, 024h, 044h, 052h, 089h, 07Ch, 024h, 030h, 040h, 089h, 044h, 024h, 020h, 08Bh, 001h
    db 0FFh, 090h, 088h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 01Ch, 085h, 0C9h, 07Eh, 042h, 08Bh, 045h
    db 024h, 089h, 04Ch, 024h, 01Ch, 08Bh, 04Ch, 024h, 02Ch, 06Ah, 0FFh, 003h, 0C1h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 011h, 053h, 050h, 08Bh, 044h, 024h, 03Ch, 050h, 08Bh, 044h, 024h, 03Ch, 050h, 055h, 0FFh
    db 092h, 0F4h, 000h, 000h, 000h, 08Bh, 054h, 024h, 02Ch, 08Bh, 045h, 024h, 08Bh, 04Ch, 024h, 01Ch
    db 003h, 0D0h, 049h, 089h, 054h, 024h, 02Ch, 089h, 04Ch, 024h, 01Ch, 075h, 0C5h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 06Ah, 000h, 0FFh, 092h, 090h, 000h, 000h, 000h, 08Bh, 044h, 024h, 024h, 08Bh, 04Ch
    db 024h, 020h, 08Bh, 054h, 024h, 028h, 06Ah, 0FFh, 003h, 0C1h, 08Bh, 04Ch, 024h, 01Ch, 053h, 003h
    db 0D1h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 029h, 057h, 052h, 08Bh, 054h, 024h, 020h, 050h, 052h, 089h, 05Ch, 024h, 048h, 0FFh, 095h
    db 0F4h, 000h, 000h, 000h, 08Bh, 044h, 024h, 028h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 024h
    db 06Ah, 0FFh, 003h, 0C1h, 08Bh, 04Ch, 024h, 038h, 053h, 003h, 0D1h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 039h, 052h, 08Bh, 054h, 024h, 020h, 050h, 056h, 052h, 0FFh, 097h, 0F4h, 000h, 000h, 000h
    db 08Bh, 074h, 024h, 054h, 08Bh, 086h, 09Ch, 001h, 000h, 000h, 085h, 0C0h, 074h, 016h, 08Bh, 0C8h
    db 08Bh, 001h, 0FFh, 050h, 00Ch, 085h, 0C0h, 074h, 00Bh, 08Bh, 04Ch, 024h, 050h, 08Bh, 0C6h
    call ?drawRadioButtonText@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 03Ch, 0C3h
?d_00796710@@YAXXZ ENDP
_TEXT$d00b96710 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b96a60  retail @ 0x00796A60 size 25
public ?d_00796a60@@YAXXZ
?d_00796a60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 11h, 06h, 8Ah, 0FFh, 0C7h, 06h, 0Ch
    db 76h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00796a60@@YAXXZ ENDP

; ghidra: FUN_00b96a90  retail @ 0x00796A90 size 27
public ?d_00796a90@@YAXXZ
?d_00796a90@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 50h, 8Bh, 44h, 24h, 08h, 52h, 50h, 51h
    db 0E8h, 0AAh, 0A7h, 8Ah, 0FFh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_00796a90@@YAXXZ ENDP

; ghidra: FUN_00b96af0  retail @ 0x00796AF0 size 25
public ?d_00796af0@@YAXXZ
?d_00796af0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 81h, 05h, 8Ah, 0FFh, 0C7h, 06h, 40h
    db 76h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00796af0@@YAXXZ ENDP

; ghidra: FUN_00b96ba0  retail @ 0x00796BA0 size 346
_TEXT ENDS
_TEXT$d00b96ba0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B96BA0 size 346
public ?d_00796ba0@@YAXXZ
?d_00796ba0@@YAXXZ PROC
    db 083h, 0ECh, 02Ch, 056h, 057h, 08Bh, 0F8h, 08Bh, 0CFh
    call ?j_00046538@@YAXXZ
    db 08Bh, 030h, 085h, 0F6h, 089h, 044h, 024h, 00Ch, 00Fh, 084h, 038h, 001h, 000h, 000h, 08Bh, 006h
    db 08Bh, 0CEh, 0FFh, 050h, 00Ch, 085h, 0C0h, 00Fh, 084h, 029h, 001h, 000h, 000h, 08Dh, 04Ch, 024h
    db 020h, 051h, 08Dh, 054h, 024h, 020h, 052h, 08Bh, 0CFh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 044h, 024h, 018h, 050h, 08Dh, 04Ch, 024h, 018h, 051h, 08Bh, 0CFh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 044h, 024h, 014h, 08Bh, 016h, 083h, 0C0h, 0F6h, 050h, 08Bh, 0CEh, 0FFh, 052h, 020h, 08Bh
    db 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 004h, 000h, 08Bh, 0CEh, 074h, 009h, 08Bh, 016h, 06Ah, 001h, 0FFh, 052h, 024h
    db 0EBh, 007h, 08Bh, 006h, 06Ah, 000h, 0FFh, 050h, 024h, 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 010h, 000h, 074h, 014h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 085h, 0C0h, 074h, 00Bh, 08Bh, 080h, 03Ch, 00Ch, 000h, 000h, 050h, 06Ah, 001h, 0EBh, 004h, 06Ah
    db 000h, 06Ah, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 04Ch, 08Bh, 006h, 053h, 055h, 08Dh, 04Ch
    db 024h, 010h, 051h, 08Dh, 054h, 024h, 01Ch, 052h, 08Bh, 0CEh, 0FFh, 050h, 03Ch, 08Bh, 04Ch, 024h
    db 024h, 08Bh, 05Ch, 024h, 01Ch, 08Bh, 06Ch, 024h, 028h, 08Bh, 07Ch, 024h, 020h, 08Dh, 004h, 00Bh
    db 089h, 044h, 024h, 034h, 08Bh, 044h, 024h, 014h, 08Dh, 014h, 02Fh, 089h, 04Ch, 024h, 02Ch, 089h
    db 06Ch, 024h, 030h, 089h, 054h, 024h, 038h, 08Ah, 050h, 004h, 084h, 0D2h, 074h, 020h, 08Bh, 044h
    db 024h, 018h, 099h, 02Bh, 0C2h, 0D1h, 0F8h, 089h, 044h, 024h, 014h, 08Bh, 0C3h, 099h, 02Bh, 0C2h
    db 08Bh, 0D8h, 08Bh, 044h, 024h, 014h, 0D1h, 0FBh, 02Bh, 0D8h, 003h, 0D9h, 0EBh, 003h, 08Dh, 059h
    db 007h, 08Bh, 044h, 024h, 010h, 099h, 02Bh, 0C2h, 08Bh, 0C8h, 08Bh, 0C7h, 099h, 02Bh, 0C2h, 08Bh
    db 016h, 08Bh, 0F8h, 0D1h, 0F9h, 0D1h, 0FFh, 02Bh, 0F9h, 08Dh, 044h, 024h, 02Ch, 050h, 08Bh, 0CEh
    db 003h, 0FDh, 0FFh, 052h, 050h, 08Bh, 044h, 024h, 044h, 08Bh, 04Ch, 024h, 040h, 08Bh, 016h, 050h
    db 051h, 08Bh, 0CEh, 0FFh, 052h, 028h, 08Bh, 016h, 06Ah, 001h, 06Ah, 001h, 057h, 053h, 08Bh, 0CEh
    db 0FFh, 052h, 038h, 05Dh, 05Bh, 05Fh, 05Eh, 083h, 0C4h, 02Ch, 0C3h
?d_00796ba0@@YAXXZ ENDP
_TEXT$d00b96ba0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b96d50  retail @ 0x00796D50 size 303
public ?d_00796d50@@YAXXZ
?d_00796d50@@YAXXZ PROC
    db 83h, 0ECh, 28h, 56h, 8Bh, 74h, 24h, 30h, 57h, 8Bh, 0CEh, 0E8h, 0D8h, 0F7h, 8Ah, 0FFh
    db 89h, 44h, 24h, 14h, 8Dh, 44h, 24h, 1Ch, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CEh
    db 0E8h, 0D6h, 8Bh, 89h, 0FFh, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 44h, 24h, 24h, 50h, 8Bh
    db 0CEh, 0E8h, 36h, 01h, 8Ah, 0FFh, 8Bh, 0CEh, 0E8h, 4Dh, 0D0h, 88h, 0FFh, 0A8h, 08h, 75h
    db 24h, 8Bh, 8Eh, 0B8h, 00h, 00h, 00h, 8Bh, 0BEh, 0BCh, 00h, 00h, 00h, 89h, 4Ch, 24h
    db 08h, 8Bh, 0CEh, 0E8h, 40h, 67h, 89h, 0FFh, 8Bh, 0CEh, 89h, 44h, 24h, 0Ch, 0E8h, 0A9h
    db 57h, 89h, 0FFh, 0EBh, 1Ch, 8Bh, 56h, 4Ch, 8Bh, 7Eh, 50h, 8Bh, 0CEh, 89h, 54h, 24h
    db 08h, 0E8h, 0Bh, 38h, 89h, 0FFh, 8Bh, 0CEh, 89h, 44h, 24h, 0Ch, 0E8h, 19h, 6Ah, 89h
    db 0FFh, 81h, 0FFh, 0FFh, 0FFh, 0FFh, 00h, 53h, 89h, 44h, 24h, 14h, 55h, 74h, 34h, 8Bh
    db 44h, 24h, 20h, 8Bh, 4Ch, 24h, 28h, 8Bh, 5Ch, 24h, 24h, 8Dh, 14h, 08h, 8Bh, 4Ch
    db 24h, 2Ch, 03h, 0CBh, 89h, 4Ch, 24h, 34h, 0FFh, 74h, 24h, 34h, 8Bh, 0Dh, 40h, 1Bh
    db 2Fh, 01h, 8Bh, 29h, 52h, 53h, 50h, 68h, 00h, 00h, 80h, 3Fh, 57h, 0FFh, 95h, 0FCh
    db 00h, 00h, 00h, 81h, 7Ch, 24h, 10h, 0FFh, 0FFh, 0FFh, 00h, 74h, 36h, 8Bh, 44h, 24h
    db 20h, 8Bh, 4Ch, 24h, 28h, 8Bh, 54h, 24h, 24h, 40h, 8Dh, 7Ch, 08h, 0FEh, 8Bh, 4Ch
    db 24h, 2Ch, 42h, 8Dh, 5Ch, 0Ah, 0FEh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 53h
    db 57h, 52h, 8Bh, 54h, 24h, 1Ch, 50h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 95h, 0F8h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 83h, 38h, 00h, 5Dh, 5Bh, 74h, 1Bh, 8Bh, 44h
    db 24h, 0Ch, 3Dh, 0FFh, 0FFh, 0FFh, 00h, 74h, 10h, 8Bh, 4Ch, 24h, 10h, 51h, 50h, 8Bh
    db 0C6h, 0E8h, 2Ah, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 83h, 0C4h, 28h, 0C3h
?d_00796d50@@YAXXZ ENDP

; ghidra: FUN_00b96ed0  retail @ 0x00796ED0 size 238
public ?d_00796ed0@@YAXXZ
?d_00796ed0@@YAXXZ PROC
    db 83h, 0ECh, 24h, 53h, 56h, 8Bh, 74h, 24h, 30h, 57h, 8Bh, 0CEh, 0E8h, 57h, 0F6h, 8Ah
    db 0FFh, 89h, 44h, 24h, 14h, 8Dh, 44h, 24h, 1Ch, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh
    db 0CEh, 0E8h, 55h, 8Ah, 89h, 0FFh, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 44h, 24h, 24h, 50h
    db 8Bh, 0CEh, 0E8h, 0B5h, 0FFh, 89h, 0FFh, 8Bh, 0CEh, 0E8h, 0CCh, 0CEh, 88h, 0FFh, 0A8h, 08h
    db 8Bh, 0CEh, 75h, 1Ah, 8Bh, 0BEh, 0B4h, 00h, 00h, 00h, 0E8h, 0C9h, 65h, 89h, 0FFh, 8Bh
    db 0D8h, 8Bh, 0CEh, 89h, 5Ch, 24h, 0Ch, 0E8h, 30h, 56h, 89h, 0FFh, 0EBh, 15h, 8Bh, 7Eh
    db 48h, 0E8h, 9Bh, 36h, 89h, 0FFh, 8Bh, 0D8h, 8Bh, 0CEh, 89h, 5Ch, 24h, 0Ch, 0E8h, 0A7h
    db 68h, 89h, 0FFh, 85h, 0FFh, 89h, 44h, 24h, 10h, 74h, 4Bh, 8Bh, 4Ch, 24h, 38h, 8Bh
    db 81h, 7Ch, 01h, 00h, 00h, 8Bh, 54h, 24h, 18h, 55h, 8Bh, 6Ch, 24h, 20h, 03h, 0C2h
    db 8Bh, 91h, 80h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 24h, 8Dh, 1Ch, 08h, 8Bh, 4Ch, 24h
    db 28h, 03h, 0D5h, 6Ah, 0FFh, 03h, 0CAh, 89h, 4Ch, 24h, 34h, 0FFh, 74h, 24h, 34h, 8Bh
    db 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 53h, 52h, 50h, 57h, 0FFh, 95h, 0F4h, 00h, 00h
    db 00h, 8Bh, 5Ch, 24h, 10h, 5Dh, 8Bh, 54h, 24h, 14h, 83h, 3Ah, 00h, 74h, 18h, 81h
    db 0FBh, 0FFh, 0FFh, 0FFh, 00h, 74h, 10h, 8Bh, 44h, 24h, 10h, 50h, 53h, 8Bh, 0C6h, 0E8h
    db 0ECh, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 24h, 0C3h
?d_00796ed0@@YAXXZ ENDP

; ghidra: FUN_00b974c0  retail @ 0x007974C0 size 25
public ?d_007974c0@@YAXXZ
?d_007974c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0B1h, 0FBh, 89h, 0FFh, 0C7h, 06h, 74h
    db 76h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007974c0@@YAXXZ ENDP

; ghidra: FUN_00b974f0  retail @ 0x007974F0 size 27
public ?d_007974f0@@YAXXZ
?d_007974f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 50h, 8Bh, 44h, 24h, 08h, 52h, 50h, 51h
    db 0E8h, 03h, 3Ah, 8Ah, 0FFh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_007974f0@@YAXXZ ENDP

; ghidra: FUN_00b97550  retail @ 0x00797550 size 25
public ?d_00797550@@YAXXZ
?d_00797550@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 21h, 0FBh, 89h, 0FFh, 0C7h, 06h, 0A8h
    db 76h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00797550@@YAXXZ ENDP

; ghidra: FUN_00b97600  retail @ 0x00797600 size 1824
public ?d_00797600@@YAXXZ
?d_00797600@@YAXXZ PROC
    db 83h, 0ECh, 24h, 53h, 8Bh, 5Ch, 24h, 2Ch, 55h, 56h, 57h, 8Dh, 44h, 24h, 28h, 50h
    db 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0CBh, 0E8h, 2Fh, 83h, 89h, 0FFh, 8Dh, 54h, 24h, 30h
    db 52h, 8Dh, 44h, 24h, 30h, 50h, 8Bh, 0CBh, 0E8h, 8Fh, 0F8h, 89h, 0FFh, 8Bh, 83h, 0E8h
    db 01h, 00h, 00h, 85h, 0C0h, 74h, 0Dh, 8Bh, 4Ch, 24h, 3Ch, 51h, 53h, 0FFh, 0D0h, 83h
    db 0C4h, 08h, 0EBh, 15h, 8Bh, 44h, 24h, 3Ch, 8Bh, 93h, 18h, 02h, 00h, 00h, 8Dh, 8Bh
    db 18h, 02h, 00h, 00h, 50h, 53h, 0FFh, 52h, 04h, 8Bh, 0CBh, 0E8h, 7Ah, 0C7h, 88h, 0FFh
    db 0F6h, 0C4h, 10h, 74h, 15h, 8Bh, 0CBh, 0E8h, 6Eh, 0C7h, 88h, 0FFh, 0A9h, 00h, 00h, 01h
    db 00h, 75h, 07h, 8Bh, 0CBh, 0E8h, 9Ch, 17h, 89h, 0FFh, 8Bh, 0CBh, 0E8h, 0B7h, 0EEh, 8Ah
    db 0FFh, 8Bh, 4Ch, 24h, 24h, 8Bh, 0E8h, 8Bh, 75h, 44h, 8Bh, 44h, 24h, 28h, 8Bh, 7Dh
    db 4Ch, 8Bh, 55h, 0Ch, 03h, 0F1h, 8Bh, 4Dh, 04h, 03h, 0F8h, 83h, 0F9h, 03h, 8Bh, 45h
    db 08h, 89h, 44h, 24h, 14h, 89h, 54h, 24h, 18h, 74h, 13h, 83h, 0F9h, 06h, 74h, 0Eh
    db 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 89h, 54h, 24h, 20h, 0EBh, 0Ch, 89h, 44h
    db 24h, 1Ch, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 83h, 7Dh, 10h, 01h, 0Fh, 8Ch
    db 0BCh, 00h, 00h, 00h, 8Ah, 4Dh, 34h, 84h, 0C9h, 74h, 12h, 8Bh, 8Bh, 0C4h, 00h, 00h
    db 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 0C8h, 00h, 00h, 00h, 0EBh, 23h, 8Bh, 4Dh, 40h
    db 85h, 0C9h, 75h, 12h, 8Bh, 8Bh, 30h, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh
    db 34h, 01h, 00h, 00h, 0EBh, 0Ah, 8Bh, 4Bh, 58h, 89h, 4Ch, 24h, 38h, 8Bh, 4Bh, 5Ch
    db 81h, 0F9h, 0FFh, 0FFh, 0FFh, 00h, 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh
    db 2Fh, 01h, 8Bh, 09h, 03h, 0D7h, 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h
    db 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h
    db 0FCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h
    db 0FFh, 0FFh, 0FFh, 00h, 74h, 3Ah, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h
    db 3Ah, 0FFh, 52h, 8Dh, 44h, 30h, 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h
    db 8Dh, 46h, 01h, 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h
    db 3Fh, 52h, 0FFh, 90h, 0F8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h
    db 03h, 74h, 24h, 1Ch, 03h, 7Ch, 24h, 20h, 83h, 7Dh, 10h, 02h, 0Fh, 8Ch, 0BBh, 00h
    db 00h, 00h, 8Ah, 4Dh, 35h, 84h, 0C9h, 74h, 12h, 8Bh, 8Bh, 0D0h, 00h, 00h, 00h, 89h
    db 4Ch, 24h, 38h, 8Bh, 8Bh, 0D4h, 00h, 00h, 00h, 0EBh, 22h, 83h, 7Dh, 40h, 01h, 75h
    db 12h, 8Bh, 8Bh, 3Ch, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 40h, 01h, 00h
    db 00h, 0EBh, 0Ah, 8Bh, 4Bh, 64h, 89h, 4Ch, 24h, 38h, 8Bh, 4Bh, 68h, 81h, 0F9h, 0FFh
    db 0FFh, 0FFh, 00h, 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 09h, 03h, 0D7h, 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h, 8Bh, 0C1h, 8Bh
    db 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0FCh, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h, 0FFh, 0FFh, 0FFh
    db 00h, 74h, 3Ah, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h, 3Ah, 0FFh, 52h
    db 8Dh, 44h, 30h, 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h, 8Dh, 46h, 01h
    db 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh
    db 90h, 0F8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 03h, 74h, 24h
    db 1Ch, 03h, 7Ch, 24h, 20h, 83h, 7Dh, 10h, 03h, 0Fh, 8Ch, 0BBh, 00h, 00h, 00h, 8Ah
    db 4Dh, 36h, 84h, 0C9h, 74h, 12h, 8Bh, 8Bh, 0DCh, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h
    db 8Bh, 8Bh, 0E0h, 00h, 00h, 00h, 0EBh, 22h, 83h, 7Dh, 40h, 02h, 75h, 12h, 8Bh, 8Bh
    db 48h, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 4Ch, 01h, 00h, 00h, 0EBh, 0Ah
    db 8Bh, 4Bh, 70h, 89h, 4Ch, 24h, 38h, 8Bh, 4Bh, 74h, 81h, 0F9h, 0FFh, 0FFh, 0FFh, 00h
    db 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 03h, 0D7h
    db 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh
    db 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Bh, 44h
    db 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h, 0FFh, 0FFh, 0FFh, 00h, 74h, 3Ah
    db 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h, 3Ah, 0FFh, 52h, 8Dh, 44h, 30h
    db 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h, 8Dh, 46h, 01h, 50h, 8Bh, 0C1h
    db 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0F8h, 00h
    db 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 03h, 74h, 24h, 1Ch, 03h, 7Ch
    db 24h, 20h, 83h, 7Dh, 10h, 04h, 0Fh, 8Ch, 0BEh, 00h, 00h, 00h, 8Ah, 4Dh, 37h, 84h
    db 0C9h, 74h, 12h, 8Bh, 8Bh, 0E8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 0ECh
    db 00h, 00h, 00h, 0EBh, 25h, 83h, 7Dh, 40h, 03h, 75h, 12h, 8Bh, 8Bh, 54h, 01h, 00h
    db 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 58h, 01h, 00h, 00h, 0EBh, 0Dh, 8Bh, 4Bh, 7Ch
    db 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 80h, 00h, 00h, 00h, 81h, 0F9h, 0FFh, 0FFh, 0FFh, 00h
    db 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 03h, 0D7h
    db 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh
    db 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Bh, 44h
    db 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h, 0FFh, 0FFh, 0FFh, 00h, 74h, 3Ah
    db 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h, 3Ah, 0FFh, 52h, 8Dh, 44h, 30h
    db 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h, 8Dh, 46h, 01h, 50h, 8Bh, 0C1h
    db 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0F8h, 00h
    db 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 03h, 74h, 24h, 1Ch, 03h, 7Ch
    db 24h, 20h, 83h, 7Dh, 10h, 05h, 0Fh, 8Ch, 0C1h, 00h, 00h, 00h, 8Ah, 4Dh, 38h, 84h
    db 0C9h, 74h, 12h, 8Bh, 8Bh, 0F4h, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 0F8h
    db 00h, 00h, 00h, 0EBh, 28h, 83h, 7Dh, 40h, 04h, 75h, 12h, 8Bh, 8Bh, 60h, 01h, 00h
    db 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 64h, 01h, 00h, 00h, 0EBh, 10h, 8Bh, 8Bh, 88h
    db 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 8Ch, 00h, 00h, 00h, 81h, 0F9h, 0FFh
    db 0FFh, 0FFh, 00h, 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 09h, 03h, 0D7h, 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h, 8Bh, 0C1h, 8Bh
    db 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0FCh, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h, 0FFh, 0FFh, 0FFh
    db 00h, 74h, 3Ah, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h, 3Ah, 0FFh, 52h
    db 8Dh, 44h, 30h, 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h, 8Dh, 46h, 01h
    db 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh
    db 90h, 0F8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 03h, 74h, 24h
    db 1Ch, 03h, 7Ch, 24h, 20h, 83h, 7Dh, 10h, 06h, 0Fh, 8Ch, 0C1h, 00h, 00h, 00h, 8Ah
    db 4Dh, 39h, 84h, 0C9h, 74h, 12h, 8Bh, 8Bh, 00h, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h
    db 8Bh, 8Bh, 04h, 01h, 00h, 00h, 0EBh, 28h, 83h, 7Dh, 40h, 05h, 75h, 12h, 8Bh, 8Bh
    db 6Ch, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 70h, 01h, 00h, 00h, 0EBh, 10h
    db 8Bh, 8Bh, 94h, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 98h, 00h, 00h, 00h
    db 81h, 0F9h, 0FFh, 0FFh, 0FFh, 00h, 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh, 0Dh, 40h, 1Bh
    db 2Fh, 01h, 8Bh, 09h, 03h, 0D7h, 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h, 50h, 57h, 56h
    db 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h
    db 0FCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 81h, 7Ch, 24h, 38h
    db 0FFh, 0FFh, 0FFh, 00h, 74h, 3Ah, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 8Dh, 54h
    db 3Ah, 0FFh, 52h, 8Dh, 44h, 30h, 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh, 54h, 24h, 44h
    db 8Dh, 46h, 01h, 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h
    db 3Fh, 52h, 0FFh, 90h, 0F8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h
    db 03h, 74h, 24h, 1Ch, 03h, 7Ch, 24h, 20h, 83h, 7Dh, 10h, 07h, 0Fh, 8Ch, 0C1h, 00h
    db 00h, 00h, 8Ah, 4Dh, 3Ah, 84h, 0C9h, 74h, 12h, 8Bh, 8Bh, 0Ch, 01h, 00h, 00h, 89h
    db 4Ch, 24h, 38h, 8Bh, 8Bh, 10h, 01h, 00h, 00h, 0EBh, 28h, 83h, 7Dh, 40h, 06h, 75h
    db 12h, 8Bh, 8Bh, 78h, 01h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 7Ch, 01h, 00h
    db 00h, 0EBh, 10h, 8Bh, 8Bh, 0A0h, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 8Bh, 8Bh, 0A4h
    db 00h, 00h, 00h, 81h, 0F9h, 0FFh, 0FFh, 0FFh, 00h, 89h, 4Ch, 24h, 10h, 74h, 30h, 8Bh
    db 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 09h, 03h, 0D7h, 52h, 8Bh, 54h, 24h, 14h, 03h, 0C6h
    db 50h, 57h, 56h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h, 00h, 00h, 80h, 3Fh
    db 52h, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 81h
    db 7Ch, 24h, 38h, 0FFh, 0FFh, 0FFh, 00h, 74h, 3Ah, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh
    db 09h, 8Dh, 54h, 3Ah, 0FFh, 52h, 8Dh, 44h, 30h, 0FFh, 50h, 8Dh, 57h, 01h, 52h, 8Bh
    db 54h, 24h, 44h, 8Dh, 46h, 01h, 50h, 8Bh, 0C1h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 68h
    db 00h, 00h, 80h, 3Fh, 52h, 0FFh, 90h, 0F8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh
    db 54h, 24h, 18h, 03h, 74h, 24h, 1Ch, 03h, 7Ch, 24h, 20h, 83h, 7Dh, 10h, 08h, 0Fh
    db 8Ch, 93h, 00h, 00h, 00h, 8Ah, 4Dh, 3Bh, 84h, 0C9h, 74h, 0Eh, 8Bh, 0ABh, 18h, 01h
    db 00h, 00h, 8Bh, 9Bh, 1Ch, 01h, 00h, 00h, 0EBh, 20h, 83h, 7Dh, 40h, 07h, 75h, 0Eh
    db 8Bh, 0ABh, 84h, 01h, 00h, 00h, 8Bh, 9Bh, 88h, 01h, 00h, 00h, 0EBh, 0Ch, 8Bh, 0ABh
    db 0ACh, 00h, 00h, 00h, 8Bh, 9Bh, 0B0h, 00h, 00h, 00h, 81h, 0FBh, 0FFh, 0FFh, 0FFh, 00h
    db 89h, 6Ch, 24h, 38h, 74h, 28h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 03h, 0D7h
    db 52h, 03h, 0C6h, 50h, 57h, 56h, 68h, 00h, 00h, 80h, 3Fh, 53h, 0FFh, 95h, 0FCh, 00h
    db 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 8Bh, 6Ch, 24h, 38h, 81h, 0FDh
    db 0FFh, 0FFh, 0FFh, 00h, 74h, 22h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 19h, 8Dh, 54h
    db 3Ah, 0FFh, 52h, 8Dh, 44h, 30h, 0FFh, 50h, 47h, 57h, 46h, 56h, 68h, 00h, 00h, 80h
    db 3Fh, 55h, 0FFh, 93h, 0F8h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 24h, 0C3h
?d_00797600@@YAXXZ ENDP

; ghidra: FUN_00b97ef0  retail @ 0x00797EF0 size 969
public ?d_00797ef0@@YAXXZ
?d_00797ef0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 53h, 55h, 56h, 8Bh, 74h, 24h, 30h, 57h, 8Dh, 44h, 24h, 24h, 50h
    db 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CEh, 0E8h, 3Fh, 7Ah, 89h, 0FFh, 8Dh, 54h, 24h, 2Ch
    db 52h, 8Dh, 44h, 24h, 2Ch, 50h, 8Bh, 0CEh, 0E8h, 9Fh, 0EFh, 89h, 0FFh, 8Bh, 86h, 0E8h
    db 01h, 00h, 00h, 85h, 0C0h, 74h, 0Dh, 8Bh, 4Ch, 24h, 38h, 51h, 56h, 0FFh, 0D0h, 83h
    db 0C4h, 08h, 0EBh, 15h, 8Bh, 44h, 24h, 38h, 8Bh, 96h, 18h, 02h, 00h, 00h, 8Dh, 8Eh
    db 18h, 02h, 00h, 00h, 50h, 56h, 0FFh, 52h, 04h, 8Bh, 0CEh, 0E8h, 8Ah, 0BEh, 88h, 0FFh
    db 0F6h, 0C4h, 10h, 74h, 15h, 8Bh, 0CEh, 0E8h, 7Eh, 0BEh, 88h, 0FFh, 0A9h, 00h, 00h, 01h
    db 00h, 75h, 07h, 8Bh, 0CEh, 0E8h, 0ACh, 0Eh, 89h, 0FFh, 8Bh, 0CEh, 0E8h, 0C7h, 0E5h, 8Ah
    db 0FFh, 8Bh, 6Ch, 24h, 24h, 8Bh, 0D8h, 8Bh, 44h, 24h, 20h, 8Bh, 73h, 44h, 8Bh, 7Bh
    db 4Ch, 8Bh, 4Bh, 08h, 03h, 0F0h, 8Bh, 43h, 04h, 03h, 0FDh, 83h, 0F8h, 03h, 8Bh, 6Bh
    db 0Ch, 89h, 4Ch, 24h, 18h, 89h, 6Ch, 24h, 1Ch, 74h, 13h, 83h, 0F8h, 06h, 74h, 0Eh
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h, 6Ch, 24h, 14h, 0EBh, 0Ch, 89h, 4Ch
    db 24h, 10h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 83h, 7Bh, 10h, 01h, 7Ch, 55h
    db 8Ah, 43h, 34h, 84h, 0C0h, 8Bh, 4Ch, 24h, 34h, 74h, 08h, 8Bh, 81h, 0C0h, 00h, 00h
    db 00h, 0EBh, 1Ah, 8Bh, 43h, 40h, 85h, 0C0h, 75h, 0Ch, 8Bh, 81h, 2Ch, 01h, 00h, 00h
    db 8Bh, 4Ch, 24h, 34h, 0EBh, 07h, 8Bh, 54h, 24h, 34h, 8Bh, 42h, 54h, 85h, 0C0h, 74h
    db 28h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 6Ah, 0FFh, 8Dh, 0Ch, 2Fh, 51h, 8Bh
    db 4Ch, 24h, 20h, 03h, 0CEh, 51h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 57h, 56h, 50h, 0FFh
    db 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 02h, 7Ch, 4Ch, 8Ah, 43h, 35h
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 0CCh, 00h, 00h, 00h, 0EBh, 11h, 83h, 7Bh, 40h, 01h
    db 75h, 08h, 8Bh, 81h, 38h, 01h, 00h, 00h, 0EBh, 03h, 8Bh, 41h, 60h, 85h, 0C0h, 74h
    db 28h, 8Bh, 15h, 40h, 1Bh, 2Fh, 01h, 8Bh, 12h, 6Ah, 0FFh, 8Dh, 0Ch, 2Fh, 51h, 8Bh
    db 4Ch, 24h, 20h, 03h, 0CEh, 51h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 57h, 56h, 50h, 0FFh
    db 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 03h, 7Ch, 4Ch, 8Ah, 43h, 36h
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 0D8h, 00h, 00h, 00h, 0EBh, 11h, 83h, 7Bh, 40h, 02h
    db 75h, 08h, 8Bh, 81h, 44h, 01h, 00h, 00h, 0EBh, 03h, 8Bh, 41h, 6Ch, 85h, 0C0h, 74h
    db 28h, 8Bh, 15h, 40h, 1Bh, 2Fh, 01h, 8Bh, 12h, 6Ah, 0FFh, 8Dh, 0Ch, 2Fh, 51h, 8Bh
    db 4Ch, 24h, 20h, 03h, 0CEh, 51h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 57h, 56h, 50h, 0FFh
    db 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 04h, 7Ch, 4Ch, 8Ah, 43h, 37h
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 0E4h, 00h, 00h, 00h, 0EBh, 11h, 83h, 7Bh, 40h, 03h
    db 75h, 08h, 8Bh, 81h, 50h, 01h, 00h, 00h, 0EBh, 03h, 8Bh, 41h, 78h, 85h, 0C0h, 74h
    db 28h, 8Bh, 15h, 40h, 1Bh, 2Fh, 01h, 8Bh, 12h, 6Ah, 0FFh, 8Dh, 0Ch, 2Fh, 51h, 8Bh
    db 4Ch, 24h, 20h, 03h, 0CEh, 51h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 57h, 56h, 50h, 0FFh
    db 92h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 05h, 7Ch, 4Ch, 8Ah, 43h, 38h
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 0F0h, 00h, 00h, 00h, 0EBh, 14h, 83h, 7Bh, 40h, 04h
    db 75h, 08h, 8Bh, 81h, 5Ch, 01h, 00h, 00h, 0EBh, 06h, 8Bh, 81h, 84h, 00h, 00h, 00h
    db 85h, 0C0h, 74h, 25h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 6Ah, 0FFh, 03h, 0EFh
    db 55h, 8Bh, 6Ch, 24h, 20h, 03h, 0EEh, 55h, 57h, 56h, 50h, 0FFh, 92h, 0F4h, 00h, 00h
    db 00h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 06h, 7Ch, 4Ch, 8Ah, 43h, 39h
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 0FCh, 00h, 00h, 00h, 0EBh, 14h, 83h, 7Bh, 40h, 05h
    db 75h, 08h, 8Bh, 81h, 68h, 01h, 00h, 00h, 0EBh, 06h, 8Bh, 81h, 90h, 00h, 00h, 00h
    db 85h, 0C0h, 74h, 25h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 6Ah, 0FFh, 03h, 0EFh
    db 55h, 8Bh, 6Ch, 24h, 20h, 03h, 0EEh, 55h, 57h, 56h, 50h, 0FFh, 92h, 0F4h, 00h, 00h
    db 00h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 07h, 7Ch, 4Ch, 8Ah, 43h, 3Ah
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 08h, 01h, 00h, 00h, 0EBh, 14h, 83h, 7Bh, 40h, 06h
    db 75h, 08h, 8Bh, 81h, 74h, 01h, 00h, 00h, 0EBh, 06h, 8Bh, 81h, 9Ch, 00h, 00h, 00h
    db 85h, 0C0h, 74h, 25h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 6Ah, 0FFh, 03h, 0EFh
    db 55h, 8Bh, 6Ch, 24h, 20h, 03h, 0EEh, 55h, 57h, 56h, 50h, 0FFh, 92h, 0F4h, 00h, 00h
    db 00h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h
    db 14h, 03h, 0F0h, 8Bh, 43h, 10h, 03h, 0FAh, 83h, 0F8h, 08h, 7Ch, 44h, 8Ah, 43h, 3Bh
    db 84h, 0C0h, 74h, 08h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0EBh, 14h, 83h, 7Bh, 40h, 07h
    db 75h, 08h, 8Bh, 81h, 80h, 01h, 00h, 00h, 0EBh, 06h, 8Bh, 81h, 0A8h, 00h, 00h, 00h
    db 85h, 0C0h, 74h, 1Dh, 8Bh, 5Ch, 24h, 18h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h
    db 6Ah, 0FFh, 03h, 0EFh, 55h, 03h, 0DEh, 53h, 57h, 56h, 50h, 0FFh, 92h, 0F4h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 20h, 0C3h
?d_00797ef0@@YAXXZ ENDP

; ghidra: FUN_00b98510  retail @ 0x00798510 size 25
public ?d_00798510@@YAXXZ
?d_00798510@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 61h, 0EBh, 89h, 0FFh, 0C7h, 06h, 0DCh
    db 76h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00798510@@YAXXZ ENDP

; ghidra: FUN_00b985a0  retail @ 0x007985A0 size 25
public ?d_007985a0@@YAXXZ
?d_007985a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0D1h, 0EAh, 89h, 0FFh, 0C7h, 06h, 10h
    db 77h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007985a0@@YAXXZ ENDP

; ghidra: FUN_00b985e0  retail @ 0x007985E0 size 85
public ?d_007985e0@@YAXXZ
?d_007985e0@@YAXXZ PROC
    db 51h, 8Dh, 44h, 24h, 01h, 50h, 8Dh, 4Ch, 24h, 07h, 51h, 8Bh, 4Ch, 24h, 10h, 8Dh
    db 54h, 24h, 0Ah, 52h, 8Dh, 44h, 24h, 0Ch, 50h, 51h, 0E8h, 89h, 37h, 88h, 0FFh, 8Ah
    db 44h, 24h, 14h, 80h, 0CAh, 0FFh, 2Ah, 0D0h, 0Fh, 0B6h, 0C2h, 8Ah, 64h, 24h, 15h, 8Ah
    db 54h, 24h, 16h, 80h, 0C9h, 0FFh, 2Ah, 0CAh, 0Fh, 0B6h, 0D1h, 0C1h, 0E0h, 08h, 0Bh, 0C2h
    db 8Ah, 54h, 24h, 17h, 80h, 0C9h, 0FFh, 2Ah, 0CAh, 0Fh, 0B6h, 0D1h, 0C1h, 0E0h, 08h, 0Bh
    db 0C2h, 83h, 0C4h, 18h, 0C3h
?d_007985e0@@YAXXZ ENDP

; ghidra: FUN_00b991a0  retail @ 0x007991A0 size 860
_TEXT ENDS
_TEXT$d00b991a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B991A0 size 860
public ?d_007991a0@@YAXXZ
?d_007991a0@@YAXXZ PROC
    db 083h, 0ECh, 060h, 053h, 055h, 056h, 08Bh, 074h, 024h, 070h, 057h, 08Bh, 0CEh
    call ?j_00046538@@YAXXZ
    db 08Bh, 0E8h, 08Dh, 044h, 024h, 054h, 050h, 08Dh, 04Ch, 024h, 054h, 051h, 08Bh, 0CEh, 089h, 06Ch
    db 024h, 044h, 0C6h, 045h, 015h, 000h
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 04Ch, 052h, 08Dh, 044h, 024h, 04Ch, 050h, 08Bh, 0CEh
    call ?j_00036ebc@@YAXXZ
    db 08Bh, 05Ch, 024h, 078h, 08Bh, 08Bh, 080h, 001h, 000h, 000h, 08Bh, 0BBh, 07Ch, 001h, 000h, 000h
    db 089h, 04Ch, 024h, 024h, 08Bh, 0CEh, 089h, 07Ch, 024h, 038h
    call ?j_00023dda@@YAXXZ
    db 0A8h, 008h, 08Bh, 0CEh, 075h, 057h
    call ?j_0002d4e8@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 034h
    call ?j_0002c55c@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 030h
    call ?j_0002d4e8@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 02Ch
    call ?j_0002c55c@@YAXXZ
    db 08Bh, 096h, 0B4h, 000h, 000h, 000h, 08Bh, 08Eh, 0CCh, 000h, 000h, 000h, 089h, 044h, 024h, 028h
    db 08Bh, 086h, 0C0h, 000h, 000h, 000h, 089h, 054h, 024h, 018h, 08Bh, 096h, 0D8h, 000h, 000h, 000h
    db 089h, 044h, 024h, 01Ch, 089h, 04Ch, 024h, 078h, 089h, 054h, 024h, 010h, 0E9h, 0A0h, 000h, 000h
    db 000h, 0F6h, 043h, 008h, 002h, 074h, 054h
    call ?j_0000a128@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 034h
    call ?j_00019961@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 030h
    call ?j_00006758@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 02Ch
    call ?j_00044026@@YAXXZ
    db 08Bh, 08Eh, 02Ch, 001h, 000h, 000h, 08Bh, 096h, 038h, 001h, 000h, 000h, 089h, 044h, 024h, 028h
    db 08Bh, 086h, 020h, 001h, 000h, 000h, 089h, 044h, 024h, 018h, 08Bh, 086h, 044h, 001h, 000h, 000h
    db 089h, 04Ch, 024h, 01Ch, 089h, 054h, 024h, 078h, 089h, 044h, 024h, 010h, 0EBh, 046h
    call ?j_0002a5d1@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 034h
    call ?j_0002d7ea@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 030h
    call ?j_00006758@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 02Ch
    call ?j_00044026@@YAXXZ
    db 08Bh, 04Eh, 048h, 08Bh, 056h, 054h, 089h, 044h, 024h, 028h, 08Bh, 046h, 060h, 089h, 04Ch, 024h
    db 018h, 08Bh, 04Eh, 06Ch, 089h, 054h, 024h, 01Ch, 089h, 044h, 024h, 078h, 089h, 04Ch, 024h, 010h
    db 08Bh, 04Ch, 024h, 018h, 085h, 0C9h, 00Fh, 084h, 07Fh, 001h, 000h, 000h, 08Bh, 044h, 024h, 01Ch
    db 085h, 0C0h, 00Fh, 084h, 073h, 001h, 000h, 000h, 08Bh, 058h, 024h, 08Bh, 069h, 024h, 08Bh, 04Ch
    db 024h, 024h, 08Bh, 044h, 024h, 04Ch, 08Bh, 054h, 024h, 050h, 003h, 0C1h, 08Bh, 04Ch, 024h, 054h
    db 003h, 0C1h, 003h, 0EFh, 02Bh, 0FBh, 003h, 0EAh, 089h, 05Ch, 024h, 068h, 08Bh, 05Ch, 024h, 048h
    db 089h, 044h, 024h, 064h, 08Bh, 044h, 024h, 078h, 003h, 0FBh, 003h, 0FAh, 08Bh, 054h, 024h, 024h
    db 003h, 0D1h, 08Bh, 048h, 024h, 089h, 054h, 024h, 014h, 08Bh, 0C7h, 02Bh, 0C5h, 099h, 0F7h, 0F9h
    db 08Bh, 054h, 024h, 04Ch, 08Bh, 0DDh, 089h, 044h, 024h, 020h, 08Bh, 044h, 024h, 014h, 003h, 0C2h
    db 089h, 044h, 024h, 05Ch, 08Bh, 044h, 024h, 020h, 085h, 0C0h, 07Eh, 044h, 089h, 044h, 024h, 020h
    db 08Dh, 09Bh, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 0FFh, 074h, 024h, 060h, 08Dh, 004h, 019h, 08Bh
    db 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 011h, 050h, 08Bh, 044h, 024h, 020h, 050h, 08Bh, 084h, 024h, 088h, 000h, 000h, 000h, 053h
    db 050h, 0FFh, 092h, 0F4h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 078h, 08Bh, 049h, 024h, 08Bh, 044h
    db 024h, 020h, 003h, 0D9h, 048h, 089h, 044h, 024h, 020h, 075h, 0C6h, 08Bh, 054h, 024h, 010h, 08Bh
    db 04Ah, 024h, 08Bh, 0C7h, 02Bh, 0C3h, 099h, 0F7h, 0F9h, 08Bh, 054h, 024h, 014h, 040h, 089h, 044h
    db 024h, 020h, 08Bh, 044h, 024h, 04Ch, 003h, 0D0h, 08Bh, 044h, 024h, 020h, 085h, 0C0h, 089h, 054h
    db 024h, 05Ch, 07Eh, 03Bh, 089h, 044h, 024h, 078h, 06Ah, 0FFh, 0FFh, 074h, 024h, 060h, 08Dh, 004h
    db 019h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 011h, 050h, 08Bh, 044h, 024h, 020h, 050h, 08Bh, 044h, 024h, 020h, 053h, 050h, 0FFh, 092h
    db 0F4h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 049h, 024h, 08Bh, 044h, 024h, 078h, 003h
    db 0D9h, 048h, 089h, 044h, 024h, 078h, 075h, 0C9h, 08Bh, 054h, 024h, 038h, 08Bh, 044h, 024h, 050h
    db 08Bh, 04Ch, 024h, 024h, 003h, 0C2h, 08Bh, 054h, 024h, 054h, 003h, 0D1h, 08Bh, 04Ch, 024h, 064h
    db 06Ah, 0FFh, 089h, 04Ch, 024h, 060h, 0FFh, 074h, 024h, 060h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 019h, 055h, 052h, 08Bh, 054h, 024h, 028h, 050h, 052h, 0FFh, 093h, 0F4h, 000h, 000h, 000h
    db 08Bh, 04Ch, 024h, 068h, 08Bh, 044h, 024h, 014h, 08Dh, 014h, 039h, 08Bh, 04Ch, 024h, 04Ch, 06Ah
    db 0FFh, 08Dh, 01Ch, 008h, 08Bh, 00Dh
    dd ?Control0040F780@@3PAUMovieControl0040F780@@A
    db 08Bh, 029h, 053h, 052h, 08Bh, 054h, 024h, 028h, 050h, 057h, 052h, 0FFh, 095h, 0F4h, 000h, 000h
    db 000h, 08Bh, 06Ch, 024h, 03Ch, 08Bh, 04Dh, 000h, 08Bh, 001h, 08Dh, 054h, 024h, 040h, 052h, 08Dh
    db 054h, 024h, 048h, 052h, 0FFh, 050h, 03Ch, 08Bh, 044h, 024h, 048h, 08Bh, 07Ch, 024h, 050h, 083h
    db 0C0h, 0F6h, 08Bh, 0CEh, 089h, 044h, 024h, 078h, 083h, 0C7h, 005h
    call ?j_00023dda@@YAXXZ
    db 0F6h, 0C4h, 040h, 074h, 019h, 08Bh, 044h, 024h, 040h, 040h, 099h, 02Bh, 0C2h, 08Bh, 0C8h, 08Bh
    db 044h, 024h, 04Ch, 099h, 02Bh, 0C2h, 0D1h, 0F9h, 0D1h, 0F8h, 02Bh, 0C1h, 0EBh, 007h, 08Bh, 044h
    db 024h, 054h, 083h, 0C0h, 005h, 08Bh, 054h, 024h, 028h, 08Bh, 04Ch, 024h, 030h, 050h, 08Bh, 044h
    db 024h, 030h, 057h, 052h, 08Bh, 054h, 024h, 040h, 050h, 051h, 052h, 056h
    call ?d_007986c0@@YAXXZ
    db 083h, 0C4h, 01Ch, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 060h, 0C3h
?d_007991a0@@YAXXZ ENDP
_TEXT$d00b991a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b99600  retail @ 0x00799600 size 14
public ?d_00799600@@YAXXZ
?d_00799600@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 51h, 0E8h, 4Bh, 9Ah, 88h, 0FFh, 83h, 0C4h, 08h
?d_00799600@@YAXXZ ENDP

; ghidra: FUN_00b99600  retail @ 0x0079960E size 8
public ?d_0079960e@@YAXXZ
?d_0079960e@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_0079960e@@YAXXZ ENDP

; ghidra: FUN_00b996a0  retail @ 0x007996A0 size 25
public ?d_007996a0@@YAXXZ
?d_007996a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0D1h, 0D9h, 89h, 0FFh, 0C7h, 06h, 44h
    db 77h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007996a0@@YAXXZ ENDP

; ghidra: FUN_00b99730  retail @ 0x00799730 size 25
public ?d_00799730@@YAXXZ
?d_00799730@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 41h, 0D9h, 89h, 0FFh, 0C7h, 06h, 78h
    db 77h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00799730@@YAXXZ ENDP

; ghidra: FUN_00b997e0  retail @ 0x007997E0 size 227
public ?d_007997e0@@YAXXZ
?d_007997e0@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 56h, 8Bh, 74h, 24h, 24h, 57h, 8Dh, 44h, 24h, 18h, 50h
    db 8Dh, 4Ch, 24h, 18h, 51h, 8Bh, 0CEh, 0E8h, 4Fh, 61h, 89h, 0FFh, 8Dh, 54h, 24h, 20h
    db 52h, 8Dh, 44h, 24h, 20h, 50h, 8Bh, 0CEh, 0E8h, 0AFh, 0D6h, 89h, 0FFh, 8Bh, 0CEh, 0E8h
    db 0C6h, 0A5h, 88h, 0FFh, 0A8h, 08h, 75h, 0Eh, 8Bh, 86h, 0BCh, 00h, 00h, 00h, 8Bh, 9Eh
    db 0B8h, 00h, 00h, 00h, 0EBh, 1Eh, 8Bh, 4Ch, 24h, 2Ch, 0F6h, 41h, 08h, 02h, 74h, 0Eh
    db 8Bh, 86h, 28h, 01h, 00h, 00h, 8Bh, 9Eh, 24h, 01h, 00h, 00h, 0EBh, 06h, 8Bh, 46h
    db 50h, 8Bh, 5Eh, 4Ch, 3Dh, 0FFh, 0FFh, 0FFh, 00h, 89h, 5Ch, 24h, 10h, 74h, 32h, 8Bh
    db 54h, 24h, 14h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 7Ch, 24h, 18h, 8Dh, 34h, 11h, 8Bh, 4Ch
    db 24h, 20h, 8Dh, 1Ch, 39h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 53h, 56h, 57h
    db 52h, 68h, 00h, 00h, 80h, 3Fh, 50h, 0FFh, 95h, 0FCh, 00h, 00h, 00h, 8Bh, 5Ch, 24h
    db 10h, 81h, 0FBh, 0FFh, 0FFh, 0FFh, 00h, 74h, 32h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h
    db 1Ch, 8Bh, 54h, 24h, 18h, 40h, 8Dh, 74h, 08h, 0FEh, 8Bh, 4Ch, 24h, 20h, 42h, 8Dh
    db 7Ch, 0Ah, 0FEh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 29h, 57h, 56h, 52h, 50h, 68h
    db 00h, 00h, 80h, 3Fh, 53h, 0FFh, 95h, 0F8h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h
    db 0C4h, 14h, 0C3h
?d_007997e0@@YAXXZ ENDP

; ghidra: FUN_00b9a330  retail @ 0x0079A330 size 1285
_TEXT ENDS
_TEXT$d00b9a330 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B9A330 size 1285
public ?d_0079a330@@YAXXZ
?d_0079a330@@YAXXZ PROC
    db 083h, 0ECh, 030h, 056h, 057h, 08Bh, 07Ch, 024h, 03Ch, 08Bh, 0CFh
    call ?j_00046538@@YAXXZ
    db 08Bh, 0F0h, 08Dh, 044h, 024h, 00Ch, 050h, 08Dh, 04Ch, 024h, 00Ch, 051h, 08Bh, 0CFh
    call ?j_0002f94b@@YAXXZ
    db 08Dh, 054h, 024h, 014h, 052h, 08Dh, 044h, 024h, 014h, 050h, 08Bh, 0CFh
    call ?j_00036ebc@@YAXXZ
    db 085h, 0F6h, 00Fh, 084h, 0C3h, 004h, 000h, 000h, 08Dh, 04Ch, 024h, 030h, 051h, 08Bh, 04Eh, 008h
    db 08Dh, 054h, 024h, 02Ch, 052h, 083h, 0ECh, 018h, 08Bh, 0C4h, 089h, 008h, 08Bh, 056h, 00Ch, 089h
    db 050h, 004h, 08Bh, 04Eh, 010h, 089h, 048h, 008h, 08Bh, 056h, 014h, 089h, 050h, 00Ch, 08Bh, 04Eh
    db 018h, 089h, 048h, 010h, 08Bh, 056h, 01Ch, 089h, 050h, 014h, 08Bh, 044h, 024h, 034h, 08Bh, 04Ch
    db 024h, 030h, 08Bh, 054h, 024h, 02Ch, 089h, 064h, 024h, 044h, 050h, 08Bh, 044h, 024h, 02Ch, 051h
    db 052h, 050h
    call ?j_00016e73@@YAXXZ
    db 0DBh, 044h, 024h, 040h, 0DBh, 044h, 024h, 044h, 083h, 0C4h, 030h, 0D9h, 05Ch, 024h, 018h, 0D9h
    db 046h, 014h, 0D8h, 066h, 008h, 0D8h, 0F1h, 0D9h, 046h, 018h, 0D8h, 066h, 00Ch, 0D8h, 074h, 024h
    db 018h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 08Ah, 080h, 001h, 000h, 000h, 08Bh, 074h
    db 024h, 00Ch, 08Bh, 04Ch, 024h, 02Ch, 02Bh, 0CEh, 049h, 089h, 04Ch, 024h, 018h, 0DBh, 044h, 024h
    db 018h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 08Bh, 0F1h, 0D9h, 05Ch, 024h, 018h, 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h, 024h, 00Ch
    db 0D9h, 05Ch, 024h, 020h, 0DBh, 044h, 024h, 008h, 0D9h, 05Ch, 024h, 024h, 0FFh, 092h, 0B0h, 000h
    db 000h, 000h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 08Bh, 006h, 068h, 000h, 000h, 000h
    db 0FFh, 051h, 08Bh, 04Ch, 024h, 028h, 052h, 08Bh, 054h, 024h, 030h, 051h, 052h, 08Bh, 0CEh, 0FFh
    db 090h, 0C0h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h, 08Bh
    db 044h, 024h, 034h, 08Bh, 04Ch, 024h, 014h, 08Bh, 054h, 024h, 00Ch, 02Bh, 0C8h, 08Dh, 04Ch, 011h
    db 0FFh, 089h, 04Ch, 024h, 024h, 0DBh, 044h, 024h, 024h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 040h, 0D9h, 05Ch, 024h, 020h, 089h, 044h, 024h, 024h, 0DBh, 044h, 024h, 010h, 08Bh
    db 0F1h, 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h, 024h, 024h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h
    db 008h, 0D9h, 05Ch, 024h, 018h, 0FFh, 092h, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 020h, 08Bh
    db 054h, 024h, 01Ch, 08Bh, 006h, 068h, 000h, 000h, 000h, 0FFh, 051h, 08Bh, 04Ch, 024h, 02Ch, 052h
    db 08Bh, 054h, 024h, 024h, 051h, 052h, 08Bh, 0CEh, 0FFh, 090h, 0C0h, 000h, 000h, 000h, 08Bh, 006h
    db 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h, 0DBh, 044h, 024h, 02Ch, 08Bh, 04Ch, 024h, 008h
    db 08Bh, 054h, 024h, 010h, 003h, 0D1h, 0D9h, 054h, 024h, 020h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 089h, 054h, 024h, 024h, 0DBh, 044h, 024h, 024h, 08Bh, 0F1h, 0D9h, 05Ch, 024h, 024h
    db 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h, 024h, 008h, 0D9h, 05Ch, 024h, 018h, 0FFh, 090h, 0B0h, 000h
    db 000h, 000h, 08Bh, 044h, 024h, 020h, 08Bh, 04Ch, 024h, 024h, 08Bh, 016h, 068h, 032h, 032h, 032h
    db 0FFh, 068h, 000h, 000h, 080h, 03Fh, 050h, 08Bh, 044h, 024h, 028h, 051h, 08Bh, 04Ch, 024h, 028h
    db 050h, 051h, 08Bh, 0CEh, 0FFh, 092h, 0B8h, 000h, 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h
    db 0DCh, 000h, 000h, 000h, 08Bh, 044h, 024h, 034h, 08Bh, 04Ch, 024h, 008h, 08Bh, 054h, 024h, 010h
    db 040h, 089h, 044h, 024h, 024h, 0DBh, 044h, 024h, 024h, 003h, 0D1h, 089h, 054h, 024h, 024h, 0D9h
    db 054h, 024h, 020h, 0DBh, 044h, 024h, 024h, 0D9h, 05Ch, 024h, 024h, 0D9h, 05Ch, 024h, 01Ch, 0DBh
    db 044h, 024h, 008h, 0E9h, 081h, 001h, 000h, 000h, 08Bh, 074h, 024h, 008h, 0DDh, 0D8h, 08Bh, 04Ch
    db 024h, 028h, 08Bh, 044h, 024h, 018h, 02Bh, 0CEh, 049h, 089h, 04Ch, 024h, 024h, 0DBh, 044h, 024h
    db 024h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 089h, 044h, 024h, 020h, 0D9h, 05Ch, 024h, 024h, 08Bh, 0F1h, 0DBh, 044h, 024h, 00Ch
    db 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h, 024h, 008h, 0D9h, 05Ch, 024h, 018h, 0FFh, 092h, 0B0h, 000h
    db 000h, 000h, 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 024h, 08Bh, 006h, 068h, 000h, 000h, 000h
    db 0FFh, 051h, 08Bh, 04Ch, 024h, 024h, 052h, 08Bh, 054h, 024h, 024h, 051h, 052h, 08Bh, 0CEh, 0FFh
    db 090h, 0C0h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h, 0DBh
    db 044h, 024h, 014h, 08Bh, 044h, 024h, 030h, 08Bh, 04Ch, 024h, 010h, 08Bh, 054h, 024h, 008h, 0D9h
    db 05Ch, 024h, 020h, 02Bh, 0C8h, 08Dh, 04Ch, 011h, 0FFh, 089h, 04Ch, 024h, 024h, 0DBh, 044h, 024h
    db 024h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 040h, 0D9h, 05Ch, 024h, 01Ch, 089h, 044h, 024h, 024h, 0DBh, 044h, 024h, 00Ch, 08Bh
    db 0F1h, 0D9h, 05Ch, 024h, 018h, 0DBh, 044h, 024h, 024h, 0D9h, 05Ch, 024h, 024h, 0FFh, 092h, 0B0h
    db 000h, 000h, 000h, 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 01Ch, 08Bh, 006h, 068h, 000h, 000h
    db 000h, 0FFh, 051h, 08Bh, 04Ch, 024h, 020h, 052h, 08Bh, 054h, 024h, 030h, 051h, 052h, 08Bh, 0CEh
    db 0FFh, 090h, 0C0h, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0DCh, 000h, 000h, 000h
    db 08Bh, 04Ch, 024h, 00Ch, 08Bh, 054h, 024h, 014h, 003h, 0D1h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 089h, 054h, 024h, 024h, 0DBh, 044h, 024h, 024h, 08Bh, 0F1h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h
    db 024h, 028h, 0D9h, 054h, 024h, 020h, 0DBh, 044h, 024h, 00Ch, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 05Ch
    db 024h, 018h, 08Bh, 001h, 0FFh, 090h, 0B0h, 000h, 000h, 000h, 08Bh, 044h, 024h, 024h, 08Bh, 04Ch
    db 024h, 020h, 08Bh, 016h, 068h, 032h, 032h, 032h, 0FFh, 068h, 000h, 000h, 080h, 03Fh, 050h, 08Bh
    db 044h, 024h, 028h, 051h, 08Bh, 04Ch, 024h, 028h, 050h, 051h, 08Bh, 0CEh, 0FFh, 092h, 0B8h, 000h
    db 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 0DCh, 000h, 000h, 000h, 08Bh, 044h, 024h, 00Ch
    db 08Bh, 04Ch, 024h, 014h, 08Bh, 054h, 024h, 030h, 003h, 0C8h, 089h, 04Ch, 024h, 024h, 0DBh, 044h
    db 024h, 024h, 042h, 089h, 054h, 024h, 024h, 0D9h, 05Ch, 024h, 020h, 0DBh, 044h, 024h, 024h, 0D9h
    db 054h, 024h, 024h, 0DBh, 044h, 024h, 00Ch, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 0D9h, 05Ch, 024h, 018h, 08Bh, 001h, 08Bh, 0F1h, 0FFh, 090h, 0B0h, 000h, 000h, 000h, 08Bh, 044h
    db 024h, 020h, 08Bh, 04Ch, 024h, 024h, 08Bh, 016h, 068h, 032h, 032h, 032h, 0FFh, 068h, 000h, 000h
    db 080h, 03Fh, 050h, 08Bh, 044h, 024h, 028h, 051h, 08Bh, 04Ch, 024h, 028h, 050h, 051h, 08Bh, 0CEh
    db 0FFh, 092h, 0B8h, 000h, 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 0DCh, 000h, 000h, 000h
    db 08Bh, 0CFh
    call ?j_00023dda@@YAXXZ
    db 084h, 0C0h, 079h, 07Bh, 08Bh, 047h, 048h, 085h, 0C0h, 074h, 074h, 08Bh, 047h, 054h, 085h, 0C0h
    db 074h, 032h, 0DBh, 044h, 024h, 034h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 06Ah, 002h, 06Ah, 0FFh, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 0DBh, 044h, 024h, 048h, 0D9h
    db 05Ch, 024h, 008h, 0DBh, 044h, 024h, 044h, 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 040h, 0D9h
    db 01Ch, 024h, 050h
    call ?j_0000a114@@YAXXZ
    db 0DBh, 044h, 024h, 034h, 08Bh, 047h, 048h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 06Ah, 002h, 06Ah, 0FFh, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 0DBh, 044h, 024h, 048h, 0D9h
    db 05Ch, 024h, 008h, 0DBh, 044h, 024h, 044h, 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 040h, 0D9h
    db 01Ch, 024h, 050h
    call ?j_0000a114@@YAXXZ
    db 05Fh, 05Eh, 083h, 0C4h, 030h, 0C3h, 08Bh, 054h, 024h, 02Ch, 08Bh, 04Ch, 024h, 034h, 08Bh, 044h
    db 024h, 028h, 02Bh, 0CAh, 08Bh, 054h, 024h, 030h, 089h, 04Ch, 024h, 024h, 0DBh, 044h, 024h, 024h
    db 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 02Bh, 0D0h, 08Bh, 001h, 0D9h, 05Ch, 024h, 020h, 089h, 054h, 024h, 024h, 0DBh, 044h, 024h, 024h
    db 08Bh, 0F1h, 0D9h, 05Ch, 024h, 024h, 0DBh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 01Ch, 0DBh, 044h
    db 024h, 028h, 0D9h, 05Ch, 024h, 018h, 0FFh, 090h, 0B0h, 000h, 000h, 000h, 08Bh, 044h, 024h, 020h
    db 08Bh, 04Ch, 024h, 024h, 08Bh, 016h, 068h, 032h, 032h, 032h, 0FFh, 050h, 08Bh, 044h, 024h, 024h
    db 051h, 08Bh, 04Ch, 024h, 024h, 050h, 051h, 08Bh, 0CEh, 0FFh, 092h, 0C0h, 000h, 000h, 000h, 08Bh
    db 016h, 08Bh, 0CEh, 0FFh, 092h, 0DCh, 000h, 000h, 000h, 05Fh, 05Eh, 083h, 0C4h, 030h, 0C3h
?d_0079a330@@YAXXZ ENDP
_TEXT$d00b9a330 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b9cff0  retail @ 0x0079CFF0 size 29
public ?d_0079cff0@@YAXXZ
?d_0079cff0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 10h, 0D9h, 44h, 24h, 08h, 0D8h, 20h, 0D9h, 44h, 24h, 0Ch, 0D8h, 60h
    db 04h, 8Bh, 44h, 24h, 04h, 0D9h, 0C9h, 0D9h, 18h, 0D9h, 58h, 04h, 0C3h
?d_0079cff0@@YAXXZ ENDP

; ghidra: FUN_00b9d030  retail @ 0x0079D030 size 18
public ?d_0079d030@@YAXXZ
?d_0079d030@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 08h, 79h, 1Ah, 00h, 0C7h, 06h, 0A0h, 79h, 12h, 01h, 8Bh, 0C6h
    db 5Eh, 0C3h
?d_0079d030@@YAXXZ ENDP

; ghidra: FUN_00b9d090  retail @ 0x0079D090 size 8
public ?d_0079d090@@YAXXZ
?d_0079d090@@YAXXZ PROC
    db 8Bh, 01h, 8Bh, 49h, 04h, 89h, 08h, 0C3h
?d_0079d090@@YAXXZ ENDP

; ghidra: FUN_00b9d180  retail @ 0x0079D180 size 52
public ?d_0079d180@@YAXXZ
?d_0079d180@@YAXXZ PROC
    db 33h, 0D2h, 81h, 0C1h, 0E0h, 04h, 00h, 00h, 0D9h, 41h, 0FCh, 0D9h, 41h, 44h, 0DAh, 0E9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 1Ah, 0D9h, 01h, 0D9h, 41h, 48h, 0DAh, 0E9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 44h, 7Ah, 0Ch, 42h, 83h, 0C1h, 08h, 83h, 0FAh, 04h, 7Ch, 0DAh, 32h, 0C0h
    db 0C3h, 0B0h, 01h, 0C3h
?d_0079d180@@YAXXZ ENDP

; ghidra: FUN_00b9d1d0  retail @ 0x0079D1D0 size 307
public ?d_0079d1d0@@YAXXZ
?d_0079d1d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0AEh, 1Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 0C7h, 06h
    db 48h, 7Ah, 12h, 01h, 0C7h, 46h, 08h, 34h, 7Ah, 12h, 01h, 8Bh, 86h, 10h, 05h, 00h
    db 00h, 33h, 0DBh, 3Bh, 0C3h, 0C7h, 44h, 24h, 14h, 04h, 00h, 00h, 00h, 74h, 28h, 8Bh
    db 8Eh, 18h, 05h, 00h, 00h, 3Bh, 0CBh, 74h, 1Eh, 8Bh, 01h, 0FFh, 90h, 0E8h, 01h, 00h
    db 00h, 84h, 0C0h, 74h, 12h, 8Bh, 8Eh, 10h, 05h, 00h, 00h, 8Bh, 86h, 18h, 05h, 00h
    db 00h, 8Bh, 11h, 50h, 0FFh, 52h, 0Ch, 8Bh, 8Eh, 18h, 05h, 00h, 00h, 3Bh, 0CBh, 74h
    db 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 89h, 9Eh, 18h, 05h, 00h, 00h
    db 8Bh, 8Eh, 14h, 05h, 00h, 00h, 3Bh, 0CBh, 74h, 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh
    db 01h, 0FFh, 10h, 89h, 9Eh, 14h, 05h, 00h, 00h, 8Bh, 8Eh, 10h, 05h, 00h, 00h, 3Bh
    db 0CBh, 74h, 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 89h, 9Eh, 10h, 05h
    db 00h, 00h, 68h, 0B8h, 0EAh, 43h, 00h, 6Ah, 04h, 6Ah, 08h, 8Dh, 86h, 64h, 05h, 00h
    db 00h, 50h, 0C6h, 44h, 24h, 24h, 03h, 0E8h, 0DAh, 9Ah, 25h, 00h, 68h, 0B8h, 0EAh, 43h
    db 00h, 6Ah, 04h, 6Ah, 08h, 8Dh, 8Eh, 44h, 05h, 00h, 00h, 51h, 0C6h, 44h, 24h, 24h
    db 02h, 0E8h, 0C0h, 9Ah, 25h, 00h, 68h, 0B8h, 0EAh, 43h, 00h, 6Ah, 04h, 6Ah, 08h, 8Dh
    db 96h, 24h, 05h, 00h, 00h, 52h, 0C6h, 44h, 24h, 24h, 01h, 0E8h, 0A6h, 9Ah, 25h, 00h
    db 8Bh, 8Eh, 20h, 05h, 00h, 00h, 3Bh, 0CBh, 88h, 5Ch, 24h, 14h, 74h, 05h, 0E8h, 0BDh
    db 0E4h, 24h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0C6h, 8Ch
    db 88h, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_0079d1d0@@YAXXZ ENDP

; ghidra: FUN_00b9d3a0  retail @ 0x0079D3A0 size 162
_TEXT ENDS
_TEXT$d00b9d3a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B9D3A0 size 162
public ?d_0079d3a0@@YAXXZ
?d_0079d3a0@@YAXXZ PROC
    db 083h, 0ECh, 008h, 056h, 057h, 08Bh, 0F1h
    call ?j_00004002@@YAXXZ
    db 08Dh, 086h, 024h, 005h, 000h, 000h, 08Dh, 08Eh, 044h, 005h, 000h, 000h, 03Bh, 0C1h, 0C7h, 044h
    db 024h, 008h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 00Ch, 000h, 000h, 000h, 000h, 074h, 014h
    db 08Bh, 054h, 024h, 008h, 08Bh, 07Ch, 024h, 00Ch, 089h, 010h, 089h, 078h, 004h, 083h, 0C0h, 008h
    db 03Bh, 0C1h, 075h, 0F4h, 08Dh, 086h, 064h, 005h, 000h, 000h, 03Bh, 0C8h, 0C7h, 044h, 024h, 008h
    db 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 00Ch, 000h, 000h, 000h, 000h, 074h, 014h, 08Bh, 054h
    db 024h, 008h, 08Bh, 07Ch, 024h, 00Ch, 089h, 011h, 089h, 079h, 004h, 083h, 0C1h, 008h, 03Bh, 0C8h
    db 075h, 0F4h, 08Dh, 08Eh, 084h, 005h, 000h, 000h, 03Bh, 0C1h, 0C7h, 044h, 024h, 008h, 000h, 000h
    db 000h, 000h, 0C7h, 044h, 024h, 00Ch, 000h, 000h, 000h, 000h, 074h, 014h, 08Bh, 054h, 024h, 008h
    db 08Bh, 074h, 024h, 00Ch, 089h, 010h, 089h, 070h, 004h, 083h, 0C0h, 008h, 03Bh, 0C1h, 075h, 0F4h
    db 05Fh, 05Eh, 083h, 0C4h, 008h, 0C3h
?d_0079d3a0@@YAXXZ ENDP
_TEXT$d00b9d3a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b9d470  retail @ 0x0079D470 size 149
public ?d_0079d470@@YAXXZ
?d_0079d470@@YAXXZ PROC
    db 83h, 0ECh, 30h, 8Bh, 44h, 24h, 4Ch, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 44h, 24h, 48h
    db 89h, 0Ch, 24h, 8Bh, 08h, 89h, 54h, 24h, 04h, 8Bh, 50h, 04h, 8Bh, 44h, 24h, 44h
    db 89h, 4Ch, 24h, 08h, 8Bh, 08h, 89h, 54h, 24h, 0Ch, 8Bh, 50h, 04h, 8Bh, 44h, 24h
    db 40h, 89h, 4Ch, 24h, 10h, 8Bh, 08h, 89h, 54h, 24h, 14h, 8Bh, 50h, 04h, 8Bh, 44h
    db 24h, 3Ch, 89h, 4Ch, 24h, 18h, 8Bh, 08h, 89h, 54h, 24h, 1Ch, 8Bh, 50h, 04h, 8Bh
    db 44h, 24h, 38h, 89h, 4Ch, 24h, 20h, 8Bh, 08h, 6Ah, 0FFh, 89h, 54h, 24h, 28h, 8Bh
    db 50h, 04h, 89h, 4Ch, 24h, 2Ch, 8Dh, 44h, 24h, 04h, 50h, 89h, 54h, 24h, 34h, 8Dh
    db 4Ch, 24h, 10h, 51h, 8Dh, 54h, 24h, 1Ch, 52h, 8Dh, 44h, 24h, 28h, 50h, 8Dh, 4Ch
    db 24h, 34h, 51h, 8Bh, 4Ch, 24h, 4Ch, 8Dh, 54h, 24h, 40h, 52h, 0E8h, 0CBh, 76h, 88h
    db 0FFh, 83h, 0C4h, 30h, 0C3h
?d_0079d470@@YAXXZ ENDP
_TEXT ENDS
END
