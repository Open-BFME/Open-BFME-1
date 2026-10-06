.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Glo012F0239@@3_NA:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheActionManager@@3PAVActionManager@@A:BYTE
EXTERN ?TheBfmeGenAE@@3PAVBfmeGenAE@@A:BYTE
EXTERN ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A:BYTE
EXTERN ?canPursue@@YA_NPAVObject@@PAVWeapon@@0@Z:NEAR
EXTERN ?g_Va012EF2F4@@3IA:BYTE
EXTERN ?g_Va012EF304@@3IA:BYTE
EXTERN ?g_bfmeDirectionWeight1285@@3MA:BYTE
EXTERN ?g_bfmeLimit952@@3MA:BYTE
EXTERN ?g_pathfindDoubleCellSize@@3MB:BYTE
EXTERN ?isSamePosition@@YA_NPBUCoord3D@@00@Z:NEAR
EXTERN ?j_000016a4@@YAXXZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_00003b1b@@YAXXZ:NEAR
EXTERN ?j_0000432c@@YAXXZ:NEAR
EXTERN ?j_00004c37@@YAXXZ:NEAR
EXTERN ?j_000065e1@@YAXXZ:NEAR
EXTERN ?j_00006eec@@YAXXZ:NEAR
EXTERN ?j_00007fbd@@YAXXZ:NEAR
EXTERN ?j_0000e1c4@@YAXXZ:NEAR
EXTERN ?j_0000e570@@YAXXZ:NEAR
EXTERN ?j_00011252@@YAXXZ:NEAR
EXTERN ?j_000126b6@@YAXXZ:NEAR
EXTERN ?j_00012b57@@YAXXZ:NEAR
EXTERN ?j_00015d02@@YAXXZ:NEAR
EXTERN ?j_00016199@@YAXXZ:NEAR
EXTERN ?j_0001a0e1@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_0002056d@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_000233ee@@YAXXZ:NEAR
EXTERN ?j_0002ae23@@YAXXZ:NEAR
EXTERN ?j_0002bd82@@YAXXZ:NEAR
EXTERN ?j_0002e85c@@YAXXZ:NEAR
EXTERN ?j_0002f66c@@YAXXZ:NEAR
EXTERN ?j_0002fc7a@@YAXXZ:NEAR
EXTERN ?j_0002fe0f@@YAXXZ:NEAR
EXTERN ?j_00031a7f@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00032b46@@YAXXZ:NEAR
EXTERN ?j_000346a3@@YAXXZ:NEAR
EXTERN ?j_0003a17a@@YAXXZ:NEAR
EXTERN ?j_0003a391@@YAXXZ:NEAR
EXTERN ?j_0003add7@@YAXXZ:NEAR
EXTERN ?j_0003bcff@@YAXXZ:NEAR
EXTERN ?j_0003bff7@@YAXXZ:NEAR
EXTERN ?j_0003ce25@@YAXXZ:NEAR
EXTERN ?j_0003e423@@YAXXZ:NEAR
EXTERN ?j_00040246@@YAXXZ:NEAR
EXTERN ?j_000420aa@@YAXXZ:NEAR
EXTERN ?j_00043ced@@YAXXZ:NEAR
EXTERN ?j_00048112@@YAXXZ:NEAR
EXTERN ?j_0004a327@@YAXXZ:NEAR
EXTERN ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ:NEAR
EXTERN __ftol2:NEAR
EXTERN __real@42700000:BYTE
EXTERN g_Va01005B9E:NEAR
EXTERN g_Va01005BDE:NEAR
EXTERN g_Va0108F924:BYTE
EXTERN g_Va010977E4:BYTE
EXTERN g_Va010977EC:BYTE
EXTERN g_Va010993D8:BYTE
EXTERN g_Va010993FC:BYTE
EXTERN g_Va01099514:BYTE
EXTERN g_Va0109954C:BYTE
EXTERN g_Va01099570:BYTE
EXTERN g_Va010995A8:BYTE
EXTERN g_Va010995CC:BYTE
EXTERN g_Va012EF2F0:BYTE
EXTERN g_Va012EF300:BYTE
_TEXT SEGMENT

; ghidra: FUN_0056f340  retail @ 0x0016F340 size 238
_TEXT ENDS
_TEXT$d0056f340 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0056F340 size 238
public ?d_0016f340@@YAXXZ
?d_0016f340@@YAXXZ PROC
    db 053h, 056h, 08Bh, 0F1h, 08Bh, 04Eh, 01Ch, 08Bh, 059h, 010h, 057h
    call ?j_0000e570@@YAXXZ
    db 08Ah, 08Bh, 044h, 003h, 000h, 000h, 08Bh, 0F8h, 0B0h, 001h, 084h, 0C8h, 00Fh, 085h, 0C3h, 000h
    db 000h, 000h, 085h, 0FFh, 00Fh, 084h, 0BBh, 000h, 000h, 000h, 084h, 087h, 044h, 003h, 000h, 000h
    db 00Fh, 085h, 0AFh, 000h, 000h, 000h, 08Bh, 08Bh, 004h, 002h, 000h, 000h, 08Bh, 001h, 0FFh, 090h
    db 000h, 002h, 000h, 000h, 08Bh, 00Dh
    dd ?TheActionManager@@3PAVActionManager@@A
    db 050h, 057h, 053h
    call ?j_00012b57@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 08Bh, 000h, 000h, 000h, 08Dh, 04Fh, 038h, 08Bh, 011h, 083h, 0C6h, 024h
    db 089h, 016h, 08Bh, 041h, 004h, 089h, 046h, 004h, 08Bh, 049h, 008h, 089h, 04Eh, 008h, 057h, 08Bh
    db 0CBh
    call ?j_00043ced@@YAXXZ
    db 0D8h, 01Dh
    dd ?g_bfmeLimit952@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 05Ah, 0D9h, 047h, 040h, 0D8h, 063h, 040h, 0D9h, 0E1h, 0D8h
    db 01Dh
    dd ?g_bfmeDirectionWeight1285@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 045h, 08Bh, 08Bh, 0FCh, 001h, 000h, 000h, 085h, 0C9h, 074h
    db 00Bh, 08Bh, 011h, 0FFh, 052h, 068h, 08Bh, 0F0h, 085h, 0F6h, 075h, 017h, 08Bh, 08Fh, 0FCh, 001h
    db 000h, 000h, 085h, 0C9h, 074h, 026h, 08Bh, 001h, 0FFh, 050h, 068h, 08Bh, 0F0h, 085h, 0F6h, 08Bh
    db 0FBh, 074h, 019h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 0F4h, 000h, 000h, 000h, 085h, 0C0h, 074h
    db 00Bh, 08Bh, 016h, 06Ah, 000h, 050h, 057h, 08Bh, 0CEh, 0FFh, 052h, 070h, 05Fh, 05Eh, 033h, 0C0h
    db 05Bh, 0C3h, 05Fh, 05Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Bh, 0C3h
?d_0016f340@@YAXXZ ENDP
_TEXT$d0056f340 ENDS
_TEXT SEGMENT

; ghidra: FUN_0056f4a0  retail @ 0x0016F4A0 size 62
public ?d_0016f4a0@@YAXXZ
?d_0016f4a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 0E8h, 0C5h, 0F0h, 0E9h, 0FFh, 85h, 0C0h, 74h, 2Bh, 0D9h
    db 40h, 38h, 0D8h, 66h, 24h, 0D9h, 40h, 3Ch, 0D8h, 66h, 28h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h
    db 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D8h, 1Dh, 0E8h, 77h, 09h, 01h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h
    db 0C4h, 41h, 0DDh, 0D8h, 75h, 04h, 0B0h, 01h, 5Eh, 0C3h, 32h, 0C0h, 5Eh, 0C3h
?d_0016f4a0@@YAXXZ ENDP

; ghidra: FUN_0056f4f0  retail @ 0x0016F4F0 size 243
_TEXT ENDS
_TEXT$d0056f4f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0056F4F0 size 243
public ?d_0016f4f0@@YAXXZ
?d_0016f4f0@@YAXXZ PROC
    db 08Bh, 044h, 024h, 008h, 083h, 0ECh, 00Ch, 085h, 0C0h, 057h, 08Bh, 0F9h, 00Fh, 084h, 0DAh, 000h
    db 000h, 000h, 0D9h, 040h, 038h, 08Bh, 048h, 040h, 0D9h, 040h, 03Ch, 056h, 08Bh, 074h, 024h, 018h
    db 0D9h, 0C9h, 0D8h, 066h, 038h, 089h, 04Ch, 024h, 010h, 08Bh, 04Fh, 01Ch, 06Ah, 000h, 0D9h, 05Ch
    db 024h, 00Ch, 0D8h, 066h, 03Ch, 0D9h, 044h, 024h, 014h, 0D8h, 066h, 040h, 0D9h, 0C0h, 0D8h, 0C9h
    db 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 00Ch, 0D8h, 04Ch, 024h, 00Ch, 0DEh, 0C1h
    db 0D9h, 0FAh, 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 044h, 024h, 00Ch, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 00Ch, 0D9h, 0CAh, 0D8h, 0CAh, 0D9h, 05Ch
    db 024h, 010h, 0DEh, 0C9h, 0D9h, 044h, 024h, 00Ch, 0D8h, 00Dh
    dd g_Va010977EC
    db 0D9h, 044h, 024h, 010h, 0D8h, 00Dh
    dd g_Va010977EC
    db 0D9h, 05Ch, 024h, 010h, 0D9h, 0C9h, 0D8h, 00Dh
    dd g_Va010977EC
    db 0D9h, 05Ch, 024h, 014h, 0D8h, 040h, 038h, 0D9h, 05Ch, 024h, 00Ch, 0D9h, 044h, 024h, 010h, 0D8h
    db 040h, 03Ch, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h, 024h, 014h, 0D8h, 040h, 040h, 0D9h, 05Ch, 024h
    db 014h, 08Bh, 011h, 0FFh, 052h, 038h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 056h
    call ?j_00015d02@@YAXXZ
    db 08Bh, 04Ch, 024h, 008h, 08Bh, 054h, 024h, 00Ch, 08Bh, 044h, 024h, 010h, 0C6h, 047h, 04Ch, 000h
    db 083h, 0C7h, 024h, 089h, 00Fh, 06Ah, 001h, 08Dh, 04Ch, 024h, 00Ch, 089h, 057h, 004h, 051h, 08Bh
    db 04Ch, 024h, 028h, 089h, 047h, 008h
    call ?j_0003bcff@@YAXXZ
    db 05Eh, 05Fh, 083h, 0C4h, 00Ch, 0C2h, 00Ch, 000h
?d_0016f4f0@@YAXXZ ENDP
_TEXT$d0056f4f0 ENDS
_TEXT SEGMENT

; ghidra: FUN_0056f740  retail @ 0x0016F740 size 30
public ?d_0016f740@@YAXXZ
?d_0016f740@@YAXXZ PROC
    db 51h, 8Bh, 49h, 04h, 56h, 8Bh, 74h, 24h, 0Ch, 56h, 0C7h, 44h, 24h, 08h, 00h, 00h
    db 00h, 00h, 0E8h, 0EEh, 48h, 0ECh, 0FFh, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_0016f740@@YAXXZ ENDP

; ghidra: FUN_0056f770  retail @ 0x0016F770 size 56
public ?d_0016f770@@YAXXZ
?d_0016f770@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 7Ch, 29h, 8Bh, 41h, 44h, 8Bh, 51h, 48h, 2Bh
    db 0D0h, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0EAh, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 3Bh, 0F0h, 73h, 0Dh, 8Bh, 41h, 44h, 8Dh, 14h, 76h, 8Dh, 04h, 90h, 5Eh, 0C2h
    db 04h, 00h, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h
?d_0016f770@@YAXXZ ENDP

; ghidra: FUN_0056f7c0  retail @ 0x0016F7C0 size 426
public ?d_0016f7c0@@YAXXZ
?d_0016f7c0@@YAXXZ PROC
    db 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 50h, 14h, 8Ah, 82h, 0B4h, 00h, 00h, 00h, 83h, 0ECh
    db 3Ch, 84h, 0C0h, 75h, 06h, 0B0h, 01h, 83h, 0C4h, 3Ch, 0C3h, 8Bh, 41h, 1Ch, 56h, 8Bh
    db 70h, 10h, 8Bh, 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 89h, 74h, 24h, 10h, 75h, 07h
    db 0B0h, 01h, 5Eh, 83h, 0C4h, 3Ch, 0C3h, 8Bh, 8Eh, 1Ch, 03h, 00h, 00h, 89h, 4Ch, 24h
    db 0Ch, 8Bh, 88h, 94h, 01h, 00h, 00h, 83h, 0F9h, 01h, 89h, 4Ch, 24h, 18h, 7Fh, 0E0h
    db 8Bh, 80h, 0CCh, 01h, 00h, 00h, 85h, 0C0h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 0C2h, 67h, 0EDh
    db 0FFh, 84h, 0C0h, 74h, 0CBh, 6Ah, 04h, 8Dh, 54h, 24h, 18h, 52h, 8Bh, 0CEh, 0E8h, 9Fh
    db 0Ah, 0EDh, 0FFh, 84h, 0C0h, 75h, 0B9h, 53h, 55h, 57h, 8Bh, 0CEh, 0C6h, 44h, 24h, 13h
    db 01h, 0E8h, 0DEh, 0Fh, 0EBh, 0FFh, 89h, 44h, 24h, 28h, 8Bh, 80h, 88h, 02h, 00h, 00h
    db 8Bh, 08h, 3Bh, 0C8h, 89h, 4Ch, 24h, 14h, 0Fh, 84h, 0F6h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 44h, 24h, 14h, 8Bh, 48h, 08h, 8Bh, 81h, 74h, 02h, 00h, 00h, 85h, 0C0h, 89h
    db 44h, 24h, 2Ch, 0Fh, 84h, 0C1h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 74h, 24h, 2Ch, 85h, 0F6h, 0Fh, 84h, 0AEh, 00h, 00h, 00h, 8Bh, 76h, 0Ch, 33h
    db 0D2h, 85h, 0F6h, 0B8h, 40h, 11h, 40h, 00h, 0B9h, 9Ch, 0FFh, 0FFh, 0FFh, 8Bh, 0E8h, 8Bh
    db 0D9h, 89h, 54h, 24h, 44h, 74h, 7Eh, 8Bh, 54h, 24h, 18h, 39h, 96h, 1Ch, 03h, 00h
    db 00h, 75h, 5Ah, 3Bh, 74h, 24h, 1Ch, 8Bh, 0BEh, 04h, 02h, 00h, 00h, 74h, 4Eh, 6Ah
    db 04h, 8Dh, 44h, 24h, 24h, 50h, 8Bh, 0CEh, 0E8h, 05h, 0Ah, 0EDh, 0FFh, 84h, 0C0h, 0Fh
    db 85h, 8Bh, 00h, 00h, 00h, 85h, 0FFh, 74h, 34h, 8Bh, 47h, 30h, 8Bh, 40h, 1Ch, 85h
    db 0C0h, 74h, 2Ah, 83h, 78h, 04h, 36h, 75h, 24h, 8Bh, 8Fh, 0CCh, 01h, 00h, 00h, 85h
    db 0C9h, 74h, 09h, 0E8h, 0EBh, 66h, 0EDh, 0FFh, 84h, 0C0h, 74h, 11h, 8Bh, 4Ch, 24h, 24h
    db 39h, 8Fh, 94h, 01h, 00h, 00h, 74h, 05h, 0C6h, 44h, 24h, 13h, 00h, 8Bh, 56h, 68h
    db 8Bh, 44h, 24h, 44h, 8Bh, 0Ch, 02h, 03h, 0CBh, 8Dh, 4Ch, 31h, 68h, 0FFh, 0D5h, 8Bh
    db 0F0h, 85h, 0F6h, 75h, 82h, 8Bh, 4Ch, 24h, 2Ch, 0E8h, 42h, 31h, 0EBh, 0FFh, 85h, 0C0h
    db 89h, 44h, 24h, 2Ch, 0Fh, 85h, 46h, 0FFh, 0FFh, 0FFh, 8Bh, 54h, 24h, 14h, 8Bh, 02h
    db 8Bh, 4Ch, 24h, 28h, 3Bh, 81h, 88h, 02h, 00h, 00h, 89h, 44h, 24h, 14h, 0Fh, 85h
    db 0Ch, 0FFh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 5Fh, 5Dh, 5Bh, 5Eh, 83h, 0C4h, 3Ch, 0C3h
    db 5Fh, 5Dh, 5Bh, 0B0h, 01h, 5Eh, 83h, 0C4h, 3Ch, 0C3h
?d_0016f7c0@@YAXXZ ENDP

; ghidra: FUN_0056f9e0  retail @ 0x0016F9E0 size 154
public ?d_0016f9e0@@YAXXZ
?d_0016f9e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 5Ah, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 57h, 0E8h, 6Eh, 0EBh
    db 0E9h, 0FFh, 85h, 0C0h, 74h, 09h, 8Bh, 80h, 3Ch, 02h, 00h, 00h, 89h, 46h, 30h, 8Bh
    db 46h, 1Ch, 8Bh, 78h, 10h, 8Bh, 0CFh, 0E8h, 21h, 4Ah, 0EBh, 0FFh, 84h, 0C0h, 74h, 41h
    db 6Ah, 00h, 8Bh, 0CFh, 0E8h, 56h, 20h, 0ECh, 0FFh, 85h, 0C0h, 74h, 34h, 8Dh, 4Ch, 24h
    db 08h, 51h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 44h, 20h, 0ECh, 0FFh, 8Bh, 0C8h, 0E8h, 06h, 80h
    db 0EBh, 0FFh, 8Dh, 4Eh, 40h, 50h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 0E8h, 3Dh
    db 82h, 71h, 00h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 08h, 0EBh
    db 03h, 8Dh, 4Eh, 40h, 0E8h, 0D7h, 7Eh, 71h, 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0016f9e0@@YAXXZ ENDP

; ghidra: FUN_0056fb20  retail @ 0x0016FB20 size 218
public ?d_0016fb20@@YAXXZ
?d_0016fb20@@YAXXZ PROC
    db 8Bh, 49h, 1Ch, 56h, 57h, 8Bh, 79h, 10h, 0E8h, 43h, 0EAh, 0E9h, 0FFh, 85h, 0FFh, 8Bh
    db 0F0h, 0Fh, 84h, 0BBh, 00h, 00h, 00h, 85h, 0F6h, 0Fh, 84h, 0B3h, 00h, 00h, 00h, 8Bh
    db 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 13h, 8Bh, 01h, 57h, 0FFh, 90h, 70h, 01h
    db 00h, 00h, 83h, 0F8h, 02h, 75h, 05h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 8Bh, 8Fh, 0FCh, 01h
    db 00h, 00h, 85h, 0C9h, 0Fh, 84h, 88h, 00h, 00h, 00h, 8Bh, 11h, 55h, 0FFh, 52h, 68h
    db 8Bh, 0E8h, 85h, 0EDh, 75h, 09h, 5Dh, 5Fh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Eh, 0C3h, 8Bh
    db 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 0EDh, 8Bh, 01h, 0FFh, 50h, 60h, 8Bh, 0F0h
    db 85h, 0F6h, 74h, 0E2h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h, 84h, 0C0h, 74h, 06h, 5Dh, 5Fh
    db 33h, 0C0h, 5Eh, 0C3h, 53h, 8Bh, 1Eh, 57h, 8Bh, 0CFh, 0E8h, 09h, 89h, 0E9h, 0FFh, 50h
    db 8Bh, 0CEh, 0FFh, 53h, 04h, 8Bh, 0D8h, 83h, 0FBh, 0FFh, 75h, 0Ah, 5Bh, 5Dh, 5Fh, 0B8h
    db 0FEh, 0FFh, 0FFh, 0FFh, 5Eh, 0C3h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 0E4h, 00h, 00h
    db 00h, 84h, 0C0h, 53h, 8Bh, 0CEh, 57h, 74h, 0Dh, 8Bh, 16h, 0FFh, 52h, 08h, 5Bh, 5Dh
    db 5Fh, 83h, 0C8h, 0FFh, 5Eh, 0C3h, 8Bh, 06h, 0FFh, 50h, 08h, 5Bh, 5Dh, 5Fh, 33h, 0C0h
    db 5Eh, 0C3h, 5Fh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Eh, 0C3h
?d_0016fb20@@YAXXZ ENDP

; ghidra: FUN_0056fc30  retail @ 0x0016FC30 size 190
public ?d_0016fc30@@YAXXZ
?d_0016fc30@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 4Bh, 1Ch, 56h, 57h, 8Bh, 79h, 10h, 0E8h, 30h, 0E9h, 0E9h, 0FFh
    db 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 8Bh, 8Eh, 04h, 02h, 00h, 00h
    db 85h, 0C9h, 74h, 14h, 8Bh, 01h, 57h, 0FFh, 90h, 70h, 01h, 00h, 00h, 83h, 0F8h, 02h
    db 75h, 06h, 5Fh, 5Eh, 33h, 0C0h, 5Bh, 0C3h, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h
    db 74h, 73h, 8Bh, 11h, 0FFh, 52h, 60h, 8Bh, 0F0h, 85h, 0F6h, 74h, 68h, 8Bh, 06h, 8Bh
    db 0CEh, 0FFh, 10h, 84h, 0C0h, 75h, 0DBh, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 21h, 26h, 0E9h, 0FFh, 8Bh, 16h, 57h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 04h, 83h, 0F8h, 0FFh, 74h, 3Dh, 8Bh, 16h, 50h, 57h, 8Bh, 0CEh, 0FFh, 52h
    db 08h, 8Bh, 43h, 1Ch, 8Bh, 40h, 1Ch, 85h, 0C0h, 74h, 14h, 8Bh, 40h, 04h, 8Bh, 53h
    db 04h, 33h, 0C9h, 3Bh, 0C2h, 0Fh, 95h, 0C1h, 5Fh, 5Eh, 5Bh, 49h, 8Bh, 0C1h, 0C3h, 8Bh
    db 53h, 04h, 0B8h, 3Fh, 42h, 0Fh, 00h, 33h, 0C9h, 3Bh, 0C2h, 0Fh, 95h, 0C1h, 5Fh, 5Eh
    db 5Bh, 49h, 8Bh, 0C1h, 0C3h, 5Fh, 5Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 0C3h
?d_0016fc30@@YAXXZ ENDP

; ghidra: FUN_0056fd30  retail @ 0x0016FD30 size 223
public ?d_0016fd30@@YAXXZ
?d_0016fd30@@YAXXZ PROC
    db 8Bh, 49h, 1Ch, 83h, 0ECh, 10h, 56h, 8Bh, 71h, 10h, 57h, 0E8h, 30h, 0E8h, 0E9h, 0FFh
    db 85h, 0F6h, 8Bh, 0F8h, 0Fh, 84h, 0BDh, 00h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 0B5h, 00h
    db 00h, 00h, 53h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 23h, 1Dh, 0ECh, 0FFh, 8Bh, 0D8h, 85h, 0DBh
    db 75h, 09h, 5Bh, 5Fh, 32h, 0C0h, 5Eh, 83h, 0C4h, 10h, 0C3h, 0D9h, 46h, 38h, 8Bh, 46h
    db 40h, 0D9h, 46h, 3Ch, 8Bh, 4Bh, 04h, 83h, 0C7h, 38h, 0D9h, 0C9h, 0D8h, 27h, 89h, 44h
    db 24h, 18h, 0D9h, 5Ch, 24h, 10h, 0D8h, 67h, 04h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h
    db 18h, 0D8h, 67h, 08h, 0D9h, 5Ch, 24h, 18h, 0E8h, 66h, 11h, 0ECh, 0FFh, 0D9h, 44h, 24h
    db 18h, 0D8h, 4Ch, 24h, 18h, 0D9h, 44h, 24h, 14h, 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h
    db 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h, 0C1h, 0D8h, 0CAh, 0DEh, 0D9h, 0DFh
    db 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 75h, 9Ah, 8Bh, 4Bh, 04h, 0D9h, 41h, 20h, 0D9h, 54h
    db 24h, 0Ch, 0D8h, 1Dh, 0F0h, 77h, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0C7h
    db 44h, 24h, 0Ch, 29h, 5Ch, 0Fh, 3Dh, 57h, 8Bh, 0CEh, 0E8h, 24h, 96h, 0EDh, 0FFh, 0D8h
    db 5Ch, 24h, 0Ch, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 64h, 0FFh, 0FFh, 0FFh, 5Bh, 5Fh
    db 0B0h, 01h, 5Eh, 83h, 0C4h, 10h, 0C3h, 5Fh, 32h, 0C0h, 5Eh, 83h, 0C4h, 10h, 0C3h
?d_0016fd30@@YAXXZ ENDP

; ghidra: FUN_0056ff30  retail @ 0x0016FF30 size 88
public ?d_0016ff30@@YAXXZ
?d_0016ff30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 1Fh, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h
    db 50h, 76h, 0Ah, 0E8h, 0E8h, 1Fh, 71h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 0EEh, 0E5h
    db 6Bh, 00h, 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Ch, 24h, 08h, 57h, 8Bh, 7Ch
    db 24h, 10h, 3Bh, 0CFh, 74h, 1Eh, 53h, 56h, 8Bh, 0F0h, 2Bh, 0F1h, 8Dh, 64h, 24h, 00h
    db 8Dh, 14h, 0Eh, 85h, 0D2h, 74h, 04h, 8Bh, 19h, 89h, 1Ah, 83h, 0C1h, 04h, 3Bh, 0CFh
    db 75h, 0EEh, 5Eh, 5Bh, 5Fh, 0C2h, 0Ch, 00h
?d_0016ff30@@YAXXZ ENDP

; ghidra: FUN_0056ffa0  retail @ 0x0016FFA0 size 33
public ?d_0016ffa0@@YAXXZ
?d_0016ffa0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 75h, 07h, 8Ah, 80h, 9Dh, 04h, 00h, 00h, 0C3h, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 01h, 23h, 0E9h, 0FFh, 8Ah, 80h, 9Dh, 04h, 00h, 00h
    db 0C3h
?d_0016ffa0@@YAXXZ ENDP

; ghidra: FUN_0056ffd0  retail @ 0x0016FFD0 size 62
public ?d_0016ffd0@@YAXXZ
?d_0016ffd0@@YAXXZ PROC
    db 56h, 8Bh, 71h, 30h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 7Ch, 2Ah, 8Bh, 56h, 44h
    db 8Bh, 4Eh, 48h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h
    db 0C1h, 0E8h, 1Fh, 03h, 0C2h, 3Bh, 0F8h, 73h, 0Eh, 8Bh, 56h, 44h, 8Dh, 0Ch, 7Fh, 5Fh
    db 8Dh, 04h, 8Ah, 5Eh, 0C2h, 04h, 00h, 5Fh, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h
?d_0016ffd0@@YAXXZ ENDP

; ghidra: FUN_00570020  retail @ 0x00170020 size 198
public ?d_00170020@@YAXXZ
?d_00170020@@YAXXZ PROC
    db 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 1Ch, 56h, 8Bh, 70h, 10h, 8Bh, 8Eh, 04h, 02h, 00h
    db 00h, 85h, 0C9h, 74h, 05h, 0E8h, 48h, 2Ch, 0EBh, 0FFh, 0C6h, 45h, 27h, 01h, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 6Ah, 22h, 0E9h
    db 0FFh, 8Ah, 88h, 0CDh, 04h, 00h, 00h, 84h, 0C9h, 74h, 11h, 8Bh, 86h, 0ECh, 01h, 00h
    db 00h, 85h, 0C0h, 74h, 07h, 0C7h, 40h, 20h, 00h, 00h, 00h, 00h, 8Bh, 1Dh, 0FCh, 0D4h
    db 2Eh, 01h, 85h, 0DBh, 74h, 50h, 8Bh, 46h, 04h, 85h, 0C0h, 57h, 8Bh, 7Eh, 74h, 74h
    db 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 2Eh, 22h, 0E9h, 0FFh, 8Bh, 40h, 20h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 0D9h, 46h
    db 40h, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 3Ch, 0DDh, 5Ch, 24h, 08h, 0D9h
    db 46h, 38h, 0DDh, 1Ch, 24h, 57h, 50h, 68h, 0F8h, 77h, 09h, 01h, 53h, 0E8h, 0B8h, 0A0h
    db 0ECh, 0FFh, 83h, 0C4h, 28h, 5Fh, 68h, 0A2h, 07h, 00h, 00h, 68h, 9Ch, 76h, 09h, 01h
    db 6Ah, 0Ah, 6Ah, 00h, 0E8h, 0D5h, 1Ah, 0E9h, 0FFh, 83h, 0C4h, 10h, 5Eh, 66h, 89h, 45h
    db 24h, 5Dh, 33h, 0C0h, 5Bh, 0C3h
?d_00170020@@YAXXZ ENDP

; ghidra: FUN_00570120  retail @ 0x00170120 size 101
public ?d_00170120@@YAXXZ
?d_00170120@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 1Ch, 8Bh, 40h, 10h, 8Bh, 88h, 04h, 02h, 00h, 00h, 8Bh
    db 89h, 0CCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 1Ch, 50h, 0E8h, 0F5h, 0A1h, 0EAh, 0FFh, 0D9h
    db 05h, 50h, 53h, 07h, 01h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 07h, 0B8h, 01h
    db 00h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Eh, 1Ch, 88h, 46h, 2Ch, 0E8h, 0Eh, 0E4h
    db 0E9h, 0FFh, 8Bh, 4Eh, 28h, 85h, 0C9h, 74h, 0Bh, 85h, 0C0h, 75h, 07h, 0B8h, 0FEh, 0FFh
    db 0FFh, 0FFh, 5Eh, 0C3h, 83h, 0F9h, 02h, 75h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 0A2h, 0CAh, 0EBh
    db 0FFh, 33h, 0C0h, 5Eh, 0C3h
?d_00170120@@YAXXZ ENDP

; ghidra: FUN_005701a0  retail @ 0x001701A0 size 36
public ?d_001701a0@@YAXXZ
?d_001701a0@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah
    db 0Ch, 89h, 4Ah, 10h, 89h, 4Ah, 14h, 89h, 4Ah, 18h, 89h, 4Ah, 1Ch, 89h, 4Ah, 20h
    db 89h, 4Ah, 24h, 0C3h
?d_001701a0@@YAXXZ ENDP

; ghidra: FUN_005703c0  retail @ 0x001703C0 size 118
public ?d_001703c0@@YAXXZ
?d_001703c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 58h, 85h, 0C9h, 74h, 62h, 8Bh, 01h, 53h, 0FFh, 50h, 18h
    db 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh, 5Ah, 3Ch, 8Bh, 4Eh, 5Ch, 3Bh, 0CBh, 5Bh, 73h
    db 09h, 85h, 0C0h, 75h, 07h, 83h, 0C8h, 0FFh, 0EBh, 04h, 85h, 0C0h, 7Dh, 46h, 8Bh, 4Eh
    db 58h, 85h, 0C9h, 74h, 3Fh, 8Bh, 01h, 6Ah, 00h, 0FFh, 50h, 14h, 8Bh, 4Eh, 60h, 51h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 48h, 0EEh, 0EAh, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 2Fh
    db 77h, 0EBh, 0FFh, 8Dh, 56h, 64h, 52h, 8Bh, 0CEh, 0E8h, 2Fh, 2Dh, 0E9h, 0FFh, 0C7h, 46h
    db 60h, 00h, 00h, 00h, 00h, 0C7h, 46h, 58h, 00h, 00h, 00h, 00h, 8Bh, 0CEh, 5Eh, 0E9h
    db 50h, 0C8h, 0E9h, 0FFh, 5Eh, 0C3h
?d_001703c0@@YAXXZ ENDP

; ghidra: FUN_00570460  retail @ 0x00170460 size 90
public ?d_00170460@@YAXXZ
?d_00170460@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 58h, 85h, 0C9h, 74h, 4Eh, 8Bh, 01h, 6Ah, 01h, 0FFh, 50h
    db 14h, 8Bh, 4Eh, 60h, 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 0D3h, 0EDh, 0EAh, 0FFh
    db 50h, 8Bh, 0CEh, 0E8h, 0BAh, 76h, 0EBh, 0FFh, 8Dh, 56h, 64h, 52h, 8Bh, 0CEh, 0E8h, 0BAh
    db 2Ch, 0E9h, 0FFh, 0C7h, 46h, 60h, 00h, 00h, 00h, 00h, 0C7h, 46h, 58h, 00h, 00h, 00h
    db 00h, 8Bh, 76h, 10h, 85h, 0F6h, 74h, 10h, 8Bh, 8Eh, 0F8h, 01h, 00h, 00h, 85h, 0C9h
    db 74h, 06h, 5Eh, 0E9h, 5Bh, 0D1h, 0ECh, 0FFh, 5Eh, 0C3h
?d_00170460@@YAXXZ ENDP

; ghidra: FUN_005704d0  retail @ 0x001704D0 size 63
public ?d_001704d0@@YAXXZ
?d_001704d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 58h, 85h, 0C0h, 74h, 11h, 83h, 7Eh, 5Ch, 0FFh, 75h, 04h
    db 33h, 0C0h, 5Eh, 0C3h, 8Bh, 0CEh, 0E8h, 7Bh, 70h, 0EBh, 0FFh, 57h, 8Bh, 0CEh, 0E8h, 6Bh
    db 6Bh, 0E9h, 0FFh, 8Bh, 0F8h, 8Bh, 46h, 10h, 8Bh, 88h, 04h, 02h, 00h, 00h, 85h, 0C9h
    db 74h, 08h, 8Bh, 11h, 0FFh, 92h, 24h, 02h, 00h, 00h, 8Bh, 0C7h, 5Fh, 5Eh, 0C3h
?d_001704d0@@YAXXZ ENDP

; ghidra: FUN_00570520  retail @ 0x00170520 size 97
public ?d_00170520@@YAXXZ
?d_00170520@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 58h, 85h, 0C0h, 74h, 13h, 83h, 7Eh, 5Ch, 0FFh, 75h, 06h
    db 33h, 0C0h, 5Eh, 0C2h, 04h, 00h, 8Bh, 0CEh, 0E8h, 29h, 70h, 0EBh, 0FFh, 8Bh, 46h, 1Ch
    db 85h, 0C0h, 53h, 55h, 57h, 74h, 05h, 8Bh, 68h, 04h, 0EBh, 05h, 0BDh, 3Fh, 42h, 0Fh
    db 00h, 8Bh, 7Ch, 24h, 14h, 57h, 8Bh, 0CEh, 0E8h, 95h, 01h, 0ECh, 0FFh, 8Bh, 0D8h, 8Bh
    db 46h, 10h, 8Bh, 88h, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 0Ch, 3Bh, 0EFh, 74h, 08h
    db 8Bh, 11h, 0FFh, 92h, 24h, 02h, 00h, 00h, 5Fh, 5Dh, 8Bh, 0C3h, 5Bh, 5Eh, 0C2h, 04h
    db 00h
?d_00170520@@YAXXZ ENDP

; ghidra: FUN_005705a0  retail @ 0x001705A0 size 78
public ?d_001705a0@@YAXXZ
?d_001705a0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 54h, 33h, 0F6h, 3Bh, 0C6h, 75h, 2Dh, 6Ah, 1Ch, 0E8h
    db 7Ch, 19h, 71h, 00h, 83h, 0C4h, 04h, 3Bh, 0C6h, 74h, 1Ah, 0C7h, 00h, 78h, 3Eh, 08h
    db 01h, 89h, 70h, 04h, 89h, 70h, 08h, 89h, 70h, 0Ch, 89h, 70h, 10h, 89h, 70h, 14h
    db 89h, 70h, 18h, 0EBh, 02h, 33h, 0C0h, 89h, 47h, 54h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Fh
    db 54h, 6Ah, 01h, 50h, 0E8h, 3Bh, 0E4h, 0EAh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_001705a0@@YAXXZ ENDP

; ghidra: FUN_00570610  retail @ 0x00170610 size 78
public ?d_00170610@@YAXXZ
?d_00170610@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 54h, 33h, 0F6h, 3Bh, 0C6h, 75h, 2Dh, 6Ah, 1Ch, 0E8h
    db 0Ch, 19h, 71h, 00h, 83h, 0C4h, 04h, 3Bh, 0C6h, 74h, 1Ah, 0C7h, 00h, 78h, 3Eh, 08h
    db 01h, 89h, 70h, 04h, 89h, 70h, 08h, 89h, 70h, 0Ch, 89h, 70h, 10h, 89h, 70h, 14h
    db 89h, 70h, 18h, 0EBh, 02h, 33h, 0C0h, 89h, 47h, 54h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Fh
    db 54h, 6Ah, 01h, 50h, 0E8h, 57h, 8Fh, 0EAh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00170610@@YAXXZ ENDP

; ghidra: FUN_00570930  retail @ 0x00170930 size 54
public ?d_00170930@@YAXXZ
?d_00170930@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 85h, 0C0h, 74h, 28h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 50h, 0E8h, 0Dh, 0E9h, 0EAh, 0FFh, 85h, 0C0h, 74h, 18h, 8Bh, 88h, 0FCh, 01h, 00h, 00h
    db 85h, 0C9h, 74h, 0Eh, 8Bh, 56h, 1Ch, 8Bh, 52h, 10h, 8Bh, 01h, 6Ah, 02h, 52h, 0FFh
    db 50h, 34h, 5Eh, 0C2h, 04h, 00h
?d_00170930@@YAXXZ ENDP

; ghidra: FUN_00570980  retail @ 0x00170980 size 67
public ?d_00170980@@YAXXZ
?d_00170980@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 85h, 0C0h, 74h, 28h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 50h, 0E8h, 0BDh, 0E8h, 0EAh, 0FFh, 85h, 0C0h, 74h, 18h, 8Bh, 88h, 0FCh, 01h, 00h, 00h
    db 85h, 0C9h, 74h, 0Eh, 8Bh, 56h, 1Ch, 8Bh, 52h, 10h, 8Bh, 01h, 6Ah, 02h, 52h, 0FFh
    db 50h, 34h, 8Bh, 4Eh, 1Ch, 8Bh, 01h, 5Eh, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h
    db 0FFh, 60h, 38h
?d_00170980@@YAXXZ ENDP

; ghidra: FUN_00570bd0  retail @ 0x00170BD0 size 120
public ?d_00170bd0@@YAXXZ
?d_00170bd0@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 1Ch, 8Bh, 68h, 10h, 8Bh, 0B5h, 04h, 02h
    db 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0C6h, 86h, 3Bh, 03h, 00h, 00h, 00h, 0FFh, 92h, 0A4h
    db 01h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 54h, 0E6h, 0EAh, 0FFh, 8Bh
    db 0D8h, 85h, 0DBh, 74h, 17h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 0B4h, 01h, 00h, 00h, 83h
    db 0F8h, 01h, 75h, 08h, 53h, 8Bh, 0CDh, 0E8h, 25h, 49h, 0EAh, 0FFh, 8Bh, 4Fh, 24h, 85h
    db 0C9h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 0C7h, 47h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0ADh, 04h, 02h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 0B8h, 01h, 00h
    db 00h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h
?d_00170bd0@@YAXXZ ENDP

; ghidra: FUN_00570c70  retail @ 0x00170C70 size 69
public ?d_00170c70@@YAXXZ
?d_00170c70@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah
    db 0Ch, 89h, 4Ah, 10h, 89h, 4Ah, 14h, 89h, 4Ah, 18h, 89h, 4Ah, 1Ch, 89h, 4Ah, 20h
    db 89h, 4Ah, 24h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0D1h, 56h, 83h, 0E1h, 1Fh, 0BEh, 01h, 00h
    db 00h, 00h, 0D3h, 0E6h, 0C1h, 0EAh, 05h, 8Bh, 0Ch, 90h, 8Dh, 14h, 90h, 0Bh, 0CEh, 89h
    db 0Ah, 5Eh, 0C2h, 08h, 00h
?d_00170c70@@YAXXZ ENDP

; ghidra: FUN_005710c0  retail @ 0x001710C0 size 53
public ?d_001710c0@@YAXXZ
?d_001710c0@@YAXXZ PROC
    db 51h, 56h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 08h, 8Bh, 0CCh, 68h, 0BCh, 7Bh, 09h, 01h
    db 0E8h, 0EBh, 7Ah, 71h, 00h, 8Bh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0E8h, 0D1h, 24h, 0E9h
    db 0FFh, 0C7h, 06h, 68h, 7Bh, 09h, 01h, 0C7h, 46h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0C6h
    db 5Eh, 59h, 0C2h, 04h, 00h
?d_001710c0@@YAXXZ ENDP

; ghidra: FUN_00571120  retail @ 0x00171120 size 54
public ?d_00171120@@YAXXZ
?d_00171120@@YAXXZ PROC
    db 51h, 56h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 08h, 8Bh, 0CCh, 68h, 34h, 7Ch, 09h, 01h
    db 0E8h, 8Bh, 7Ah, 71h, 00h, 8Bh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0E8h, 71h, 24h, 0E9h
    db 0FFh, 33h, 0C0h, 89h, 46h, 24h, 89h, 46h, 28h, 0C7h, 06h, 0E0h, 7Bh, 09h, 01h, 8Bh
    db 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_00171120@@YAXXZ ENDP

; ghidra: FUN_00571b40  retail @ 0x00171B40 size 413
public ?d_00171b40@@YAXXZ
?d_00171b40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C6h, 5Ah, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h
    db 24h, 10h, 33h, 0DBh, 53h, 51h, 8Dh, 44h, 24h, 38h, 89h, 64h, 24h, 1Ch, 8Bh, 0CCh
    db 50h, 89h, 5Ch, 24h, 2Ch, 0E8h, 0E6h, 5Fh, 71h, 00h, 8Bh, 4Ch, 24h, 30h, 51h, 8Bh
    db 0CEh, 0E8h, 9Dh, 0D5h, 0E9h, 0FFh, 0F6h, 05h, 0ECh, 0F2h, 2Eh, 01h, 01h, 0C6h, 44h, 24h
    db 20h, 01h, 0C7h, 06h, 10h, 73h, 09h, 01h, 75h, 4Ch, 83h, 0Dh, 0ECh, 0F2h, 2Eh, 01h
    db 01h, 0B8h, 0Fh, 27h, 00h, 00h, 0C7h, 05h, 0C0h, 0F2h, 2Eh, 01h, 20h, 1Bh, 57h, 00h
    db 0A3h, 0C4h, 0F2h, 2Eh, 01h, 89h, 1Dh, 0C8h, 0F2h, 2Eh, 01h, 0C7h, 05h, 0CCh, 0F2h, 2Eh
    db 01h, 70h, 0AFh, 56h, 00h, 0A3h, 0D0h, 0F2h, 2Eh, 01h, 0C7h, 05h, 0D4h, 0F2h, 2Eh, 01h
    db 02h, 00h, 00h, 00h, 89h, 1Dh, 0D8h, 0F2h, 2Eh, 01h, 89h, 1Dh, 0DCh, 0F2h, 2Eh, 01h
    db 89h, 1Dh, 0E0h, 0F2h, 2Eh, 01h, 6Ah, 2Ch, 0E8h, 43h, 03h, 71h, 00h, 8Bh, 0F8h, 83h
    db 0C4h, 04h, 89h, 7Ch, 24h, 28h, 3Bh, 0FBh, 0C6h, 44h, 24h, 20h, 02h, 74h, 36h, 8Bh
    db 44h, 24h, 2Ch, 3Bh, 0C3h, 74h, 05h, 8Dh, 68h, 24h, 0EBh, 02h, 33h, 0EDh, 51h, 89h
    db 64h, 24h, 30h, 8Bh, 0CCh, 68h, 14h, 7Eh, 09h, 01h, 0E8h, 0A1h, 6Fh, 71h, 00h, 56h
    db 8Bh, 0CFh, 0E8h, 8Bh, 19h, 0E9h, 0FFh, 0C7h, 07h, 0C0h, 7Dh, 09h, 01h, 89h, 6Fh, 24h
    db 88h, 5Fh, 28h, 0EBh, 02h, 33h, 0FFh, 68h, 0C0h, 0F2h, 2Eh, 01h, 68h, 0Fh, 27h, 00h
    db 00h, 68h, 0F5h, 01h, 00h, 00h, 57h, 68h, 0F4h, 01h, 00h, 00h, 8Bh, 0CEh, 0C6h, 44h
    db 24h, 34h, 01h, 0E8h, 5Bh, 0B5h, 0ECh, 0FFh, 6Ah, 24h, 0E8h, 0D1h, 02h, 71h, 00h, 8Bh
    db 0F8h, 83h, 0C4h, 04h, 89h, 7Ch, 24h, 28h, 3Bh, 0FBh, 0C6h, 44h, 24h, 20h, 03h, 74h
    db 21h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 94h, 7Dh, 09h, 01h, 0E8h, 3Eh, 6Fh
    db 71h, 00h, 56h, 8Bh, 0CFh, 0E8h, 28h, 19h, 0E9h, 0FFh, 0C7h, 07h, 40h, 7Dh, 09h, 01h
    db 0EBh, 02h, 33h, 0FFh, 68h, 0C0h, 0F2h, 2Eh, 01h, 68h, 0Fh, 27h, 00h, 00h, 68h, 0F4h
    db 01h, 00h, 00h, 57h, 68h, 0F5h, 01h, 00h, 00h, 8Bh, 0CEh, 0C6h, 44h, 24h, 34h, 01h
    db 0E8h, 0FEh, 0B4h, 0ECh, 0FFh, 8Dh, 4Ch, 24h, 30h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 7Ah, 5Ch, 71h, 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_00171b40@@YAXXZ ENDP

; ghidra: FUN_00571db0  retail @ 0x00171DB0 size 106
public ?d_00171db0@@YAXXZ
?d_00171db0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 5Ah, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 40h
    db 85h, 09h, 01h, 8Bh, 4Eh, 24h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 19h, 8Bh, 01h, 0FFh, 50h, 3Ch, 8Bh, 4Eh, 24h, 85h, 0C9h, 74h, 06h, 8Bh, 11h
    db 6Ah, 01h, 0FFh, 12h, 0C7h, 46h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 1Bh, 49h, 0EAh, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00171db0@@YAXXZ ENDP

; ghidra: FUN_00571e70  retail @ 0x00171E70 size 275
public ?d_00171e70@@YAXXZ
?d_00171e70@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 8Bh, 48h, 1Ch, 55h, 56h, 8Bh, 71h, 10h, 0E8h, 0EEh, 0C6h
    db 0E9h, 0FFh, 6Ah, 00h, 8Bh, 0CEh, 8Bh, 0E8h, 0E8h, 0F2h, 0FBh, 0EBh, 0FFh, 85h, 0EDh, 89h
    db 44h, 24h, 08h, 75h, 06h, 5Eh, 0B0h, 01h, 5Dh, 59h, 0C3h, 85h, 0C0h, 53h, 57h, 0Fh
    db 84h, 0D6h, 00h, 00h, 00h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 0C6h, 44h, 24h
    db 18h, 00h, 0B3h, 01h, 74h, 0Ah, 8Bh, 11h, 0FFh, 92h, 0ECh, 01h, 00h, 00h, 8Ah, 0D8h
    db 6Ah, 02h, 8Bh, 0CEh, 0E8h, 56h, 06h, 0ECh, 0FFh, 84h, 0C0h, 74h, 02h, 0B3h, 01h, 6Ah
    db 53h, 8Bh, 0CEh, 0E8h, 47h, 06h, 0ECh, 0FFh, 84h, 0C0h, 74h, 02h, 0B3h, 01h, 8Bh, 0BEh
    db 14h, 02h, 00h, 00h, 85h, 0FFh, 74h, 18h, 6Ah, 07h, 8Bh, 0CFh, 0E8h, 2Eh, 06h, 0ECh
    db 0FFh, 84h, 0C0h, 75h, 09h, 0F6h, 87h, 90h, 00h, 00h, 00h, 40h, 75h, 02h, 0B3h, 01h
    db 8Bh, 7Ch, 24h, 10h, 8Bh, 4Fh, 04h, 0E8h, 0A0h, 99h, 0E9h, 0FFh, 84h, 0C0h, 75h, 36h
    db 8Bh, 4Fh, 04h, 0E8h, 5Ch, 70h, 0EBh, 0FFh, 84h, 0C0h, 75h, 2Ah, 84h, 0DBh, 74h, 26h
    db 8Bh, 0CDh, 0E8h, 0CAh, 80h, 0EAh, 0FFh, 84h, 0C0h, 75h, 1Bh, 0A1h, 14h, 0F2h, 2Eh, 01h
    db 8Bh, 48h, 0Ch, 8Dh, 55h, 38h, 52h, 55h, 8Dh, 46h, 38h, 50h, 56h, 0E8h, 00h, 11h
    db 0EBh, 0FFh, 8Ah, 0D8h, 0EBh, 04h, 8Ah, 5Ch, 24h, 18h, 8Bh, 0CFh, 0E8h, 53h, 92h, 0E9h
    db 0FFh, 84h, 0C0h, 75h, 04h, 84h, 0DBh, 75h, 1Ah, 8Bh, 0CFh, 0E8h, 44h, 92h, 0E9h, 0FFh
    db 84h, 0C0h, 75h, 17h, 6Ah, 00h, 55h, 56h, 8Bh, 0CFh, 0E8h, 0EDh, 0C8h, 0EBh, 0FFh, 84h
    db 0C0h, 75h, 08h, 5Fh, 5Bh, 5Eh, 0B0h, 01h, 5Dh, 59h, 0C3h, 5Fh, 5Bh, 5Eh, 32h, 0C0h
    db 5Dh, 59h, 0C3h
?d_00171e70@@YAXXZ ENDP

; ghidra: FUN_005720d0  retail @ 0x001720D0 size 68
public ?d_001720d0@@YAXXZ
?d_001720d0@@YAXXZ PROC
    db 51h, 56h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 08h, 8Bh, 0CCh, 68h, 04h, 86h, 09h, 01h
    db 0E8h, 0DBh, 6Ah, 71h, 00h, 8Bh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0E8h, 0C1h, 14h, 0E9h
    db 0FFh, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 0Fh, 94h, 0C1h, 0C7h, 06h, 0B0h, 85h, 09h, 01h
    db 88h, 4Eh, 26h, 0C6h, 46h, 27h, 00h, 66h, 0C7h, 46h, 24h, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh
    db 59h, 0C2h, 08h, 00h
?d_001720d0@@YAXXZ ENDP

; ghidra: FUN_00572180  retail @ 0x00172180 size 295
public ?d_00172180@@YAXXZ
?d_00172180@@YAXXZ PROC
    db 8Ah, 41h, 27h, 83h, 0ECh, 0Ch, 84h, 0C0h, 0Fh, 84h, 15h, 01h, 00h, 00h, 8Bh, 41h
    db 1Ch, 53h, 0C6h, 41h, 27h, 00h, 56h, 8Bh, 70h, 10h, 0F6h, 86h, 94h, 00h, 00h, 00h
    db 20h, 57h, 8Bh, 0BEh, 04h, 02h, 00h, 00h, 0B3h, 01h, 74h, 22h, 8Bh, 86h, 14h, 02h
    db 00h, 00h, 32h, 0DBh, 85h, 0C0h, 74h, 16h, 8Bh, 80h, 04h, 02h, 00h, 00h, 85h, 0C0h
    db 74h, 0Ch, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 92h, 80h, 01h, 00h, 00h, 8Ah, 0D8h, 8Bh, 0CEh
    db 0E8h, 0A2h, 9Ch, 0EBh, 0FFh, 85h, 0C0h, 74h, 1Ah, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 92h, 0D8h
    db 01h, 00h, 00h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 56h, 32h, 0DBh, 0E8h, 0Fh
    db 3Bh, 0EAh, 0FFh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 92h, 80h, 01h, 00h, 00h, 84h, 0C0h, 0Fh
    db 84h, 88h, 00h, 00h, 00h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 90h, 0ECh, 01h, 00h, 00h, 84h
    db 0C0h, 74h, 7Ah, 84h, 0DBh, 74h, 76h, 8Bh, 4Eh, 38h, 0D9h, 05h, 50h, 53h, 07h, 01h
    db 8Bh, 46h, 40h, 8Bh, 56h, 3Ch, 89h, 4Ch, 24h, 0Ch, 0D9h, 44h, 24h, 0Ch, 0DAh, 0E9h
    db 89h, 44h, 24h, 14h, 89h, 54h, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 26h, 0D9h
    db 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 10h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 7Ah, 13h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 14h, 0DAh, 0E9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 44h, 7Bh, 28h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 59h, 0Ch, 68h, 0CCh
    db 07h, 00h, 00h, 68h, 9Ch, 76h, 09h, 01h, 8Bh, 0CEh, 0E8h, 12h, 81h, 0ECh, 0FFh, 50h
    db 8Dh, 54h, 24h, 18h, 52h, 56h, 8Bh, 0CBh, 0E8h, 55h, 72h, 0EBh, 0FFh, 8Bh, 07h, 8Bh
    db 0CFh, 0FFh, 90h, 0E8h, 01h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0ACh, 88h, 0EDh, 0FFh
    db 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_00172180@@YAXXZ ENDP

; ghidra: FUN_00572430  retail @ 0x00172430 size 98
public ?d_00172430@@YAXXZ
?d_00172430@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 08h, 5Bh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 08h
    db 5Bh, 09h, 01h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 74h, 0Eh, 8Bh, 46h, 40h, 83h, 0F8h, 05h, 72h, 06h, 8Bh, 11h, 50h
    db 0FFh, 52h, 4Ch, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A3h, 42h
    db 0EAh, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_00172430@@YAXXZ ENDP

; ghidra: FUN_005724b0  retail @ 0x001724B0 size 203
public ?d_001724b0@@YAXXZ
?d_001724b0@@YAXXZ PROC
    db 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 8Bh, 15h, 0FCh, 0D4h, 2Eh, 01h, 56h, 8Bh, 0F1h
    db 74h, 18h, 85h, 0D2h, 74h, 14h, 68h, 2Ch, 87h, 09h, 01h, 52h, 0E8h, 0A9h, 7Ch, 0ECh
    db 0FFh, 8Bh, 15h, 0FCh, 0D4h, 2Eh, 01h, 83h, 0C4h, 08h, 8Bh, 46h, 1Ch, 8Bh, 40h, 10h
    db 8Ah, 88h, 90h, 00h, 00h, 00h, 84h, 0C9h, 79h, 1Fh, 0A0h, 39h, 02h, 2Fh, 01h, 84h
    db 0C0h, 74h, 4Ch, 85h, 0D2h, 74h, 48h, 68h, 0D8h, 86h, 09h, 01h, 52h, 0E8h, 78h, 7Ch
    db 0ECh, 0FFh, 83h, 0C4h, 08h, 32h, 0C0h, 5Eh, 0C3h, 8Bh, 88h, 04h, 02h, 00h, 00h, 85h
    db 0C9h, 74h, 36h, 8Bh, 11h, 0FFh, 92h, 74h, 01h, 00h, 00h, 84h, 0C0h, 75h, 24h, 0A0h
    db 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h
    db 0Eh, 68h, 68h, 86h, 09h, 01h, 50h, 0E8h, 3Eh, 7Ch, 0ECh, 0FFh, 83h, 0C4h, 08h, 32h
    db 0C0h, 5Eh, 0C3h, 8Bh, 15h, 0FCh, 0D4h, 2Eh, 01h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h
    db 74h, 24h, 85h, 0D2h, 74h, 20h, 8Ah, 46h, 4Ch, 84h, 0C0h, 0B8h, 58h, 0FAh, 07h, 01h
    db 75h, 05h, 0B8h, 80h, 01h, 08h, 01h, 50h, 68h, 18h, 86h, 09h, 01h, 52h, 0E8h, 07h
    db 7Ch, 0ECh, 0FFh, 83h, 0C4h, 0Ch, 8Ah, 46h, 4Ch, 5Eh, 0C3h
?d_001724b0@@YAXXZ ENDP

; ghidra: FUN_005725b0  retail @ 0x001725B0 size 56
public ?d_001725b0@@YAXXZ
?d_001725b0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h, 57h, 8Bh, 0B9h, 04h, 02h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 42h, 0DBh, 0E9h, 0FFh, 8Dh, 56h, 24h, 8Bh, 0CFh, 50h, 52h, 0E8h, 2Ch
    db 97h, 0ECh, 0FFh, 8Ah, 87h, 1Eh, 03h, 00h, 00h, 8Bh, 0CFh, 88h, 46h, 4Dh, 0E8h, 8Ah
    db 0FEh, 0E9h, 0FFh, 5Fh, 0B0h, 01h, 5Eh, 0C3h
?d_001725b0@@YAXXZ ENDP

; ghidra: FUN_00572600  retail @ 0x00172600 size 1524
public ?d_00172600@@YAXXZ
?d_00172600@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 83h, 0ECh, 20h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 0Dh
    db 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 57h, 74h, 15h, 8Bh, 46h, 40h, 83h, 0F8h, 05h, 72h
    db 0Dh, 8Bh, 11h, 50h, 0FFh, 52h, 4Ch, 0C7h, 46h, 40h, 01h, 00h, 00h, 00h, 8Bh, 46h
    db 1Ch, 8Bh, 68h, 10h, 8Bh, 0BDh, 04h, 02h, 00h, 00h, 8Ah, 8Fh, 1Eh, 03h, 00h, 00h
    db 88h, 4Eh, 4Dh, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 89h, 7Ch, 24h, 1Ch, 74h, 5Dh
    db 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 54h, 8Bh, 45h, 04h, 85h, 0C0h, 8Bh, 5Dh
    db 74h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 4Ch, 0FCh, 0E8h, 0FFh, 8Bh
    db 40h, 20h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 0D9h, 46h, 2Ch, 8Bh, 15h, 0FCh, 0D4h, 2Eh, 01h, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h
    db 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 53h, 50h, 68h
    db 70h, 8Eh, 09h, 01h, 52h, 0E8h, 0D0h, 7Ah, 0ECh, 0FFh, 83h, 0C4h, 28h, 0F7h, 85h, 94h
    db 00h, 00h, 00h, 00h, 00h, 01h, 00h, 74h, 2Dh, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h
    db 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 08h, 8Eh, 09h, 01h
    db 50h, 0E8h, 0A4h, 7Ah, 0ECh, 0FFh, 83h, 0C4h, 08h, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 8Bh, 0E5h, 5Dh, 0C3h, 8Bh, 0CFh, 0E8h, 0BFh, 0Ch, 0ECh, 0FFh, 0D9h, 5Ch, 24h
    db 20h, 8Bh, 9Fh, 0CCh, 01h, 00h, 00h, 85h, 0DBh, 89h, 5Ch, 24h, 18h, 74h, 07h, 8Bh
    db 0CBh, 0E8h, 95h, 70h, 0E9h, 0FFh, 8Bh, 0CFh, 0C6h, 46h, 4Eh, 01h, 0E8h, 5Ch, 0FDh, 0E9h
    db 0FFh, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 2Eh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h
    db 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h
    db 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 90h, 8Dh, 09h, 01h, 50h
    db 0E8h, 35h, 7Ah, 0ECh, 0FFh, 83h, 0C4h, 20h, 8Bh, 0CEh, 0E8h, 0BAh, 0D9h, 0E9h, 0FFh, 84h
    db 0C0h, 0A0h, 39h, 02h, 2Fh, 01h, 0Fh, 84h, 54h, 01h, 00h, 00h, 84h, 0C0h, 74h, 17h
    db 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 38h, 8Dh, 09h, 01h, 50h, 0E8h
    db 06h, 7Ah, 0ECh, 0FFh, 83h, 0C4h, 08h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 58h, 0Ch, 8Bh
    db 0CFh, 0E8h, 0E5h, 7Bh, 0EAh, 0FFh, 50h, 8Bh, 0CBh, 0E8h, 54h, 0A0h, 0EAh, 0FFh, 8Bh, 4Ch
    db 24h, 1Ch, 6Ah, 00h, 8Dh, 7Eh, 24h, 57h, 81h, 0C1h, 0A8h, 01h, 00h, 00h, 51h, 55h
    db 8Bh, 0CBh, 0E8h, 55h, 58h, 0EBh, 0FFh, 84h, 0C0h, 0A0h, 39h, 02h, 2Fh, 01h, 75h, 69h
    db 84h, 0C0h, 74h, 2Dh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 24h, 0D9h, 46h, 2Ch
    db 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 07h
    db 0DDh, 1Ch, 24h, 68h, 0B0h, 8Ch, 09h, 01h, 50h, 0E8h, 9Ch, 79h, 0ECh, 0FFh, 83h, 0C4h
    db 20h, 57h, 55h, 8Bh, 0CBh, 0E8h, 2Ch, 24h, 0ECh, 0FFh, 0A0h, 39h, 02h, 2Fh, 01h, 84h
    db 0C0h, 74h, 57h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 4Eh, 0D9h, 46h, 2Ch, 83h
    db 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 07h, 0DDh
    db 1Ch, 24h, 68h, 30h, 8Ch, 09h, 01h, 0EBh, 28h, 84h, 0C0h, 74h, 2Dh, 0A1h, 0FCh, 0D4h
    db 2Eh, 01h, 85h, 0C0h, 74h, 24h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h
    db 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 07h, 0DDh, 1Ch, 24h, 68h, 0B0h, 8Bh, 09h
    db 01h, 50h, 0E8h, 33h, 79h, 0ECh, 0FFh, 83h, 0C4h, 20h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h
    db 68h, 09h, 09h, 00h, 00h, 68h, 9Ch, 76h, 09h, 01h, 57h, 55h, 0E8h, 14h, 9Eh, 0EAh
    db 0FFh, 50h, 57h, 55h, 8Bh, 0CBh, 0E8h, 77h, 6Ch, 0EBh, 0FFh, 0A0h, 39h, 02h, 2Fh, 01h
    db 84h, 0C0h, 74h, 2Dh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 24h, 0D9h, 46h, 2Ch
    db 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 07h
    db 0DDh, 1Ch, 24h, 68h, 38h, 8Bh, 09h, 01h, 50h, 0E8h, 0DCh, 78h, 0ECh, 0FFh, 83h, 0C4h
    db 20h, 6Ah, 00h, 8Bh, 0CBh, 0E8h, 38h, 9Fh, 0EAh, 0FFh, 8Bh, 5Ch, 24h, 18h, 0EBh, 1Bh
    db 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 0D8h, 8Ah
    db 09h, 01h, 50h, 0E8h, 0B2h, 78h, 0ECh, 0FFh, 83h, 0C4h, 08h, 0D9h, 45h, 3Ch, 8Dh, 7Dh
    db 38h, 0D9h, 07h, 0D8h, 66h, 24h, 0D9h, 5Ch, 24h, 24h, 0D8h, 66h, 28h, 0D9h, 44h, 24h
    db 24h, 0D9h, 0E1h, 0D9h, 5Ch, 24h, 18h, 0D9h, 0E1h, 0D9h, 44h, 24h, 18h, 0D8h, 0D9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ch, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0D8h, 44h, 24h, 18h
    db 0EBh, 0Ch, 0D9h, 44h, 24h, 18h, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0DEh, 0C1h, 0D8h, 1Dh
    db 0D4h, 8Ah, 09h, 01h, 0DFh, 0E0h, 0A0h, 39h, 02h, 2Fh, 01h, 0F6h, 0C4h, 41h, 0Fh, 85h
    db 9Ch, 01h, 00h, 00h, 84h, 0C0h, 0C6h, 44h, 24h, 17h, 01h, 74h, 2Eh, 0A1h, 0FCh, 0D4h
    db 2Eh, 01h, 85h, 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h
    db 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 58h, 8Ah
    db 09h, 01h, 50h, 0E8h, 22h, 78h, 0ECh, 0FFh, 83h, 0C4h, 20h, 85h, 0DBh, 0Fh, 84h, 0B8h
    db 00h, 00h, 00h, 55h, 8Bh, 0CBh, 0E8h, 68h, 41h, 0EDh, 0FFh, 84h, 0C0h, 0Fh, 84h, 0A8h
    db 00h, 00h, 00h, 8Ah, 46h, 4Dh, 84h, 0C0h, 75h, 12h, 0D9h, 44h, 24h, 20h, 0D8h, 5Bh
    db 38h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 8Fh, 00h, 00h, 00h, 0A0h, 39h, 02h, 2Fh
    db 01h, 84h, 0C0h, 74h, 2Eh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 25h, 0D9h, 46h
    db 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h
    db 46h, 24h, 0DDh, 1Ch, 24h, 68h, 0F8h, 89h, 09h, 01h, 50h, 0E8h, 0BAh, 77h, 0ECh, 0FFh
    db 83h, 0C4h, 20h, 8Bh, 15h, 14h, 0F2h, 2Eh, 01h, 8Bh, 5Ah, 0Ch, 8Bh, 0CDh, 0E8h, 0BEh
    db 79h, 0ECh, 0FFh, 50h, 57h, 8Bh, 0CBh, 0E8h, 93h, 98h, 0EAh, 0FFh, 0F6h, 0D8h, 0BAh, 01h
    db 00h, 00h, 00h, 1Bh, 0C0h, 83h, 0E0h, 2Ah, 83h, 0C0h, 3Ch, 8Bh, 0C8h, 83h, 0E1h, 1Fh
    db 0C1h, 0E8h, 05h, 0D3h, 0E2h, 8Bh, 8Ch, 85h, 10h, 01h, 00h, 00h, 8Dh, 84h, 85h, 10h
    db 01h, 00h, 00h, 85h, 0D1h, 0Fh, 85h, 0ECh, 00h, 00h, 00h, 0Bh, 0CAh, 89h, 08h, 8Bh
    db 0CDh, 0E8h, 07h, 0EFh, 0EAh, 0FFh, 0E9h, 0DCh, 00h, 00h, 00h, 6Ah, 0Eh, 8Bh, 0CDh, 0E8h
    db 0FBh, 0FAh, 0EBh, 0FFh, 84h, 0C0h, 74h, 64h, 6Ah, 10h, 8Bh, 0CDh, 0E8h, 0EEh, 0FAh, 0EBh
    db 0FFh, 84h, 0C0h, 74h, 57h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 2Eh, 0A1h, 0FCh
    db 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h
    db 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 98h
    db 89h, 09h, 01h, 50h, 0E8h, 11h, 77h, 0ECh, 0FFh, 83h, 0C4h, 20h, 8Bh, 8Dh, 14h, 01h
    db 00h, 00h, 0B8h, 00h, 00h, 00h, 10h, 85h, 0C8h, 75h, 7Ch, 0Bh, 0C8h, 89h, 8Dh, 14h
    db 01h, 00h, 00h, 8Bh, 0CDh, 0E8h, 93h, 0EEh, 0EAh, 0FFh, 0EBh, 6Bh, 0A0h, 39h, 02h, 2Fh
    db 01h, 84h, 0C0h, 0Fh, 84h, 95h, 00h, 00h, 00h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h
    db 74h, 55h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh
    db 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 38h, 89h, 09h, 01h, 0EBh, 2Eh
    db 84h, 0C0h, 0C6h, 44h, 24h, 17h, 00h, 74h, 65h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h
    db 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh
    db 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 0C0h, 88h, 09h, 01h, 50h, 0E8h
    db 86h, 76h, 0ECh, 0FFh, 83h, 0C4h, 20h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 2Eh
    db 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh
    db 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h
    db 68h, 50h, 88h, 09h, 01h, 50h, 0E8h, 4Fh, 76h, 0ECh, 0FFh, 83h, 0C4h, 20h, 8Bh, 16h
    db 8Bh, 0CEh, 0FFh, 52h, 44h, 84h, 0C0h, 0A0h, 39h, 02h, 2Fh, 01h, 75h, 48h, 84h, 0C0h
    db 74h, 2Eh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh
    db 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h, 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh
    db 1Ch, 24h, 68h, 0E0h, 87h, 09h, 01h, 50h, 0E8h, 0Dh, 76h, 0ECh, 0FFh, 83h, 0C4h, 20h
    db 8Bh, 4Ch, 24h, 1Ch, 0E8h, 0Dh, 0F9h, 0E9h, 0FFh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 8Bh, 0E5h, 5Dh, 0C3h, 84h, 0C0h, 74h, 2Eh, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h
    db 0C0h, 74h, 25h, 0D9h, 46h, 2Ch, 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0D9h, 46h, 28h
    db 0DDh, 5Ch, 24h, 08h, 0D9h, 46h, 24h, 0DDh, 1Ch, 24h, 68h, 68h, 87h, 09h, 01h, 50h
    db 0E8h, 0C5h, 75h, 0ECh, 0FFh, 83h, 0C4h, 20h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 07h, 8Bh, 0CFh
    db 0FFh, 90h, 0D4h, 01h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0DCh, 0BFh, 0E9h, 0FFh, 68h
    db 0F0h, 23h, 74h, 49h, 8Bh, 0CFh, 0E8h, 0CCh, 60h, 0EDh, 0FFh, 8Ah, 44h, 24h, 17h, 84h
    db 0C0h, 74h, 07h, 8Bh, 0CEh, 0E8h, 06h, 88h, 0EBh, 0FFh, 5Fh, 33h, 0C0h, 5Eh, 5Dh, 5Bh
    db 8Bh, 0E5h, 5Dh, 0C3h
?d_00172600@@YAXXZ ENDP

; ghidra: FUN_00572d80  retail @ 0x00172D80 size 189
public ?d_00172d80@@YAXXZ
?d_00172d80@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 1Ch, 8Bh, 70h, 10h, 8Bh, 86h, 98h, 00h, 00h
    db 00h, 0F6h, 0C4h, 04h, 8Bh, 9Eh, 04h, 02h, 00h, 00h, 75h, 1Fh, 8Bh, 86h, 14h, 01h
    db 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh, 0CEh
    db 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 62h, 0EBh, 0EAh, 0FFh, 8Bh, 86h, 20h, 01h, 00h
    db 00h, 0A9h, 00h, 00h, 04h, 00h, 74h, 12h, 25h, 0FFh, 0FFh, 0FBh, 0FFh, 8Bh, 0CEh, 89h
    db 86h, 20h, 01h, 00h, 00h, 0E8h, 43h, 0EBh, 0EAh, 0FFh, 0F6h, 86h, 1Ch, 01h, 00h, 00h
    db 40h, 74h, 16h, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 83h, 0E0h, 0BFh, 8Bh, 0CEh, 89h, 86h
    db 1Ch, 01h, 00h, 00h, 0E8h, 24h, 0EBh, 0EAh, 0FFh, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 0F6h
    db 0C4h, 01h, 74h, 12h, 25h, 0FFh, 0FEh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h
    db 00h, 0E8h, 07h, 0EBh, 0EAh, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 47h, 40h, 8Bh
    db 11h, 50h, 0FFh, 52h, 4Ch, 85h, 0DBh, 0C7h, 47h, 40h, 01h, 00h, 00h, 00h, 74h, 07h
    db 8Bh, 0CBh, 0E8h, 4Fh, 0F6h, 0E9h, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_00172d80@@YAXXZ ENDP

; ghidra: FUN_00572e70  retail @ 0x00172E70 size 1166
public ?d_00172e70@@YAXXZ
?d_00172e70@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 1Ch, 55h, 56h, 8Bh, 70h, 10h, 8Bh, 0AEh
    db 04h, 02h, 00h, 00h, 8Ah, 43h, 4Dh, 84h, 0C0h, 57h, 8Bh, 0BDh, 40h, 01h, 00h, 00h
    db 89h, 5Ch, 24h, 18h, 89h, 6Ch, 24h, 14h, 0Fh, 84h, 89h, 00h, 00h, 00h, 8Bh, 0Dh
    db 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 89h, 53h, 44h, 8Ah, 85h, 1Eh, 03h, 00h, 00h
    db 84h, 0C0h, 0Fh, 85h, 3Ch, 04h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 0Eh, 03h, 00h, 00h
    db 8Dh, 43h, 24h, 8Bh, 10h, 8Dh, 4Bh, 34h, 89h, 11h, 8Bh, 50h, 04h, 8Bh, 40h, 08h
    db 89h, 51h, 04h, 89h, 41h, 08h, 8Bh, 0CBh, 0C6h, 43h, 4Dh, 00h, 0E8h, 28h, 0D2h, 0E9h
    db 0FFh, 84h, 0C0h, 74h, 26h, 8Bh, 47h, 08h, 8Bh, 48h, 18h, 8Bh, 15h, 14h, 0F2h, 2Eh
    db 01h, 68h, 0DCh, 09h, 00h, 00h, 68h, 9Ch, 76h, 09h, 01h, 51h, 8Bh, 4Ah, 0Ch, 83h
    db 0C0h, 0Ch, 50h, 56h, 0E8h, 0D9h, 65h, 0EBh, 0FFh, 0EBh, 0Eh, 0A1h, 14h, 0F2h, 2Eh, 01h
    db 8Bh, 48h, 0Ch, 56h, 0E8h, 0E9h, 2Dh, 0EAh, 0FFh, 8Ah, 85h, 2Eh, 03h, 00h, 00h, 84h
    db 0C0h, 75h, 04h, 0C6h, 43h, 4Eh, 00h, 85h, 0FFh, 0C6h, 44h, 24h, 13h, 00h, 75h, 05h
    db 0C6h, 44h, 24h, 13h, 01h, 8Ah, 85h, 26h, 03h, 00h, 00h, 84h, 0C0h, 75h, 09h, 83h
    db 0BDh, 6Ch, 01h, 00h, 00h, 0Ah, 7Eh, 11h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h
    db 3Ch, 0C6h, 44h, 24h, 13h, 01h, 89h, 53h, 48h, 8Bh, 0CDh, 0E8h, 0A7h, 53h, 0ECh, 0FFh
    db 84h, 0C0h, 74h, 2Bh, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 44h, 0F3h, 0E8h, 0FFh, 0F7h, 80h, 0C8h, 00h, 00h, 00h, 00h, 00h, 00h
    db 02h, 74h, 0Ch, 0C7h, 43h, 44h, 00h, 00h, 00h, 00h, 0C6h, 44h, 24h, 13h, 01h, 85h
    db 0FFh, 74h, 0Bh, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 0D4h, 01h, 00h, 00h, 8Bh, 0CDh
    db 0E8h, 07h, 04h, 0ECh, 0FFh, 8Bh, 9Dh, 0CCh, 01h, 00h, 00h, 85h, 0DBh, 74h, 32h, 0D8h
    db 5Bh, 38h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 74h, 2Ah, 8Bh, 86h, 14h, 01h, 00h, 00h, 0A9h
    db 00h, 00h, 00h, 10h, 0Fh, 84h, 0ABh, 01h, 00h, 00h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh
    db 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 41h, 0E9h, 0EAh, 0FFh, 0E9h, 94h, 01h, 00h
    db 00h, 0DDh, 0D8h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 69h, 0Ch, 8Bh, 0CEh, 0BFh, 3Ch
    db 00h, 00h, 00h, 0E8h, 99h, 73h, 0ECh, 0FFh, 50h, 8Dh, 56h, 38h, 52h, 8Bh, 0CDh, 0E8h
    db 6Bh, 92h, 0EAh, 0FFh, 84h, 0C0h, 0BDh, 00h, 01h, 00h, 00h, 74h, 53h, 8Bh, 44h, 24h
    db 14h, 8Bh, 80h, 0CCh, 01h, 00h, 00h, 85h, 0C0h, 74h, 24h, 8Bh, 48h, 40h, 0C1h, 0E9h
    db 07h, 0F6h, 0C1h, 01h, 74h, 19h, 0F6h, 86h, 1Ch, 01h, 00h, 00h, 40h, 0BFh, 68h, 00h
    db 00h, 00h, 74h, 2Ch, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 83h, 0E0h, 0BFh, 0EBh, 14h, 8Bh
    db 86h, 1Ch, 01h, 00h, 00h, 85h, 0C5h, 0BFh, 66h, 00h, 00h, 00h, 74h, 12h, 25h, 0FFh
    db 0FEh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 0BDh, 0E8h, 0EAh, 0FFh
    db 8Bh, 54h, 24h, 14h, 83h, 0BAh, 6Ch, 01h, 00h, 00h, 05h, 7Eh, 40h, 8Bh, 86h, 14h
    db 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh
    db 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 91h, 0E8h, 0EAh, 0FFh, 8Bh, 86h, 20h, 01h
    db 00h, 00h, 0A9h, 00h, 00h, 04h, 00h, 0Fh, 84h, 0D4h, 00h, 00h, 00h, 25h, 0FFh, 0FFh
    db 0FBh, 0FFh, 89h, 86h, 20h, 01h, 00h, 00h, 0E9h, 0BDh, 00h, 00h, 00h, 83h, 0FFh, 3Ch
    db 75h, 3Bh, 0F6h, 86h, 1Ch, 01h, 00h, 00h, 40h, 74h, 16h, 8Bh, 86h, 1Ch, 01h, 00h
    db 00h, 83h, 0E0h, 0BFh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 4Ch, 0E8h, 0EAh
    db 0FFh, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 85h, 0C5h, 74h, 12h, 25h, 0FFh, 0FEh, 0FFh, 0FFh
    db 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 30h, 0E8h, 0EAh, 0FFh, 85h, 0DBh, 74h
    db 31h, 56h, 8Bh, 0CBh, 0E8h, 0B2h, 0FFh, 0EAh, 0FFh, 0D9h, 05h, 50h, 53h, 07h, 01h, 0DAh
    db 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 1Ah, 8Bh, 86h, 14h, 01h, 00h, 00h, 0A9h, 00h
    db 00h, 00h, 10h, 74h, 2Bh, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 86h, 14h, 01h, 00h, 00h
    db 0EBh, 17h, 8Bh, 8Eh, 14h, 01h, 00h, 00h, 0B8h, 00h, 00h, 00h, 10h, 85h, 0C8h, 75h
    db 0Fh, 0Bh, 0C8h, 89h, 8Eh, 14h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0DDh, 0E7h, 0EAh, 0FFh
    db 83h, 0FFh, 3Ch, 74h, 2Ch, 8Bh, 0CFh, 83h, 0E1h, 1Fh, 0B8h, 01h, 00h, 00h, 00h, 0C1h
    db 0EFh, 05h, 8Bh, 94h, 0BEh, 10h, 01h, 00h, 00h, 0D3h, 0E0h, 8Dh, 8Ch, 0BEh, 10h, 01h
    db 00h, 00h, 85h, 0C2h, 75h, 0Bh, 0Bh, 0D0h, 89h, 11h, 8Bh, 0CEh, 0E8h, 0ACh, 0E7h, 0EAh
    db 0FFh, 8Bh, 6Ch, 24h, 14h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 8Bh, 7Ch, 24h, 18h, 75h
    db 22h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 2Bh, 4Fh, 44h, 83h, 0F9h, 05h, 76h
    db 63h, 8Dh, 47h, 24h, 8Dh, 4Fh, 34h, 8Dh, 56h, 38h, 0E8h, 0D1h, 78h, 0FFh, 0FFh, 84h
    db 0C0h, 75h, 51h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh
    db 01h, 85h, 0C0h, 74h, 0Eh, 68h, 0E4h, 8Eh, 09h, 01h, 50h, 0E8h, 0BAh, 6Fh, 0ECh, 0FFh
    db 83h, 0C4h, 08h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 44h, 84h, 0C0h, 75h, 0Dh, 5Fh, 5Eh
    db 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h, 1Ch, 0C3h, 8Bh, 85h, 40h, 01h, 00h
    db 00h, 85h, 0C0h, 0Fh, 84h, 0Bh, 01h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h
    db 0D4h, 01h, 00h, 00h, 8Bh, 0CDh, 0E8h, 0B1h, 01h, 0ECh, 0FFh, 0D9h, 5Ch, 24h, 1Ch, 8Bh
    db 0BDh, 0CCh, 01h, 00h, 00h, 32h, 0DBh, 85h, 0FFh, 0Fh, 84h, 0E5h, 00h, 00h, 00h, 0D9h
    db 44h, 24h, 1Ch, 0D8h, 5Fh, 38h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 02h, 0B3h, 01h, 8Bh
    db 6Ch, 24h, 14h, 8Bh, 8Dh, 68h, 01h, 00h, 00h, 89h, 4Ch, 24h, 14h, 8Bh, 0CFh, 0E8h
    db 79h, 0BAh, 0EBh, 0FFh, 0D8h, 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 14h, 8Bh
    db 0CFh, 0E8h, 67h, 0BAh, 0EBh, 0FFh, 0DCh, 0C0h, 0D8h, 5Ch, 24h, 1Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 74h, 08h, 84h, 0DBh, 0Fh, 84h, 99h, 00h, 00h, 00h, 8Bh, 55h, 00h, 8Bh, 0CDh
    db 0FFh, 92h, 0ECh, 01h, 00h, 00h, 84h, 0C0h, 8Bh, 4Ch, 24h, 18h, 74h, 5Dh, 8Bh, 41h
    db 24h, 8Bh, 51h, 28h, 89h, 44h, 24h, 20h, 8Bh, 85h, 40h, 01h, 00h, 00h, 8Bh, 40h
    db 08h, 85h, 0C0h, 89h, 54h, 24h, 24h, 74h, 17h, 83h, 0C0h, 0Ch, 8Bh, 10h, 89h, 54h
    db 24h, 20h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 54h, 24h, 24h, 89h, 44h, 24h, 28h
    db 0D9h, 46h, 38h, 0D8h, 64h, 24h, 20h, 0D9h, 46h, 3Ch, 0D8h, 64h, 24h, 24h, 0D9h, 0C0h
    db 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 1Dh
    db 50h, 6Ch, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 29h, 0E8h, 39h, 0CEh, 0E9h, 0FFh
    db 84h, 0C0h, 74h, 0Bh, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 92h, 0E8h, 01h, 00h, 00h, 5Fh
    db 5Eh, 0C7h, 85h, 60h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 5Dh, 83h, 0C8h, 0FFh, 5Bh
    db 83h, 0C4h, 1Ch, 0C3h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 83h, 0C4h, 1Ch, 0C3h
?d_00172e70@@YAXXZ ENDP

; ghidra: FUN_005737c0  retail @ 0x001737C0 size 237
public ?d_001737c0@@YAXXZ
?d_001737c0@@YAXXZ PROC
    db 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 53h, 56h, 57h, 8Bh, 0F1h, 74h, 17h, 0A1h, 0FCh
    db 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 94h, 64h, 09h, 01h, 50h, 0E8h, 98h, 69h
    db 0ECh, 0FFh, 83h, 0C4h, 08h, 8Bh, 4Eh, 1Ch, 0C6h, 46h, 4Ch, 01h, 8Bh, 41h, 10h, 8Bh
    db 0B8h, 04h, 02h, 00h, 00h, 0E8h, 76h, 0ADh, 0E9h, 0FFh, 85h, 0C0h, 74h, 3Eh, 85h, 0FFh
    db 74h, 3Ah, 8Bh, 4Eh, 1Ch, 0E8h, 66h, 0ADh, 0E9h, 0FFh, 8Bh, 58h, 74h, 8Bh, 0CFh, 0E8h
    db 57h, 6Bh, 0EAh, 0FFh, 3Bh, 0D8h, 75h, 24h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h
    db 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 70h, 8Fh, 09h, 01h, 50h
    db 0E8h, 45h, 69h, 0ECh, 0FFh, 83h, 0C4h, 08h, 0C6h, 46h, 4Ch, 00h, 8Bh, 4Eh, 1Ch, 0E8h
    db 2Ch, 0ADh, 0E9h, 0FFh, 85h, 0C0h, 8Bh, 4Eh, 1Ch, 74h, 1Dh, 0E8h, 20h, 0ADh, 0E9h, 0FFh
    db 83h, 0C0h, 38h, 8Bh, 10h, 8Dh, 4Eh, 24h, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h
    db 8Bh, 40h, 08h, 89h, 41h, 08h, 0EBh, 16h, 83h, 0C1h, 24h, 8Bh, 01h, 8Dh, 56h, 24h
    db 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 8Bh, 0CEh
    db 0E8h, 0A2h, 0E5h, 0EAh, 0FFh, 8Bh, 0D8h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 19h, 85h, 0FFh
    db 74h, 15h, 8Bh, 0CFh, 0E8h, 0DBh, 0Eh, 0EDh, 0FFh, 84h, 0C0h, 74h, 0Ah, 8Bh, 17h, 8Bh
    db 0CFh, 0FFh, 92h, 0E8h, 01h, 00h, 00h, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 0C3h
?d_001737c0@@YAXXZ ENDP

; ghidra: FUN_00573900  retail @ 0x00173900 size 111
public ?d_00173900@@YAXXZ
?d_00173900@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 3Bh, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh
    db 48h, 3Ch, 3Bh, 4Eh, 50h, 76h, 07h, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Eh, 0C3h, 8Bh, 56h
    db 1Ch, 8Bh, 4Ah, 10h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h
    db 10h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 81h, 14h, 01h, 00h, 00h, 0E8h, 0DCh, 0DFh, 0EAh
    db 0FFh, 33h, 0C0h, 5Eh, 0C3h, 8Bh, 4Eh, 1Ch, 0E8h, 23h, 0ACh, 0E9h, 0FFh, 85h, 0C0h, 74h
    db 16h, 83h, 0C0h, 38h, 8Bh, 10h, 8Dh, 4Eh, 24h, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h
    db 04h, 8Bh, 40h, 08h, 89h, 41h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 87h, 4Fh, 0EDh, 0FFh
?d_00173900@@YAXXZ ENDP

; ghidra: FUN_00573990  retail @ 0x00173990 size 101
public ?d_00173990@@YAXXZ
?d_00173990@@YAXXZ PROC
    db 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 56h, 8Bh, 0F1h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh
    db 01h, 85h, 0C0h, 74h, 0Eh, 68h, 14h, 90h, 09h, 01h, 50h, 0E8h, 0CAh, 67h, 0ECh, 0FFh
    db 83h, 0C4h, 08h, 8Bh, 46h, 1Ch, 0C6h, 46h, 4Ch, 01h, 8Bh, 48h, 10h, 8Bh, 81h, 04h
    db 02h, 00h, 00h, 8Bh, 80h, 40h, 01h, 00h, 00h, 85h, 0C0h, 75h, 07h, 0B8h, 0FEh, 0FFh
    db 0FFh, 0FFh, 5Eh, 0C3h, 8Bh, 50h, 08h, 83h, 0C2h, 0Ch, 8Bh, 0Ah, 8Dh, 46h, 24h, 89h
    db 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 8Bh, 0CEh, 89h, 50h, 08h, 5Eh
    db 0E9h, 32h, 0E4h, 0EAh, 0FFh
?d_00173990@@YAXXZ ENDP

; ghidra: FUN_00573b20  retail @ 0x00173B20 size 90
public ?d_00173b20@@YAXXZ
?d_00173b20@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 48h, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h
    db 8Bh, 81h, 04h, 02h, 00h, 00h, 8Bh, 88h, 40h, 01h, 00h, 00h, 85h, 0C9h, 74h, 32h
    db 8Ah, 88h, 1Eh, 03h, 00h, 00h, 84h, 0C9h, 75h, 28h, 0A0h, 39h, 02h, 2Fh, 01h, 84h
    db 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 80h, 90h, 09h
    db 01h, 50h, 0E8h, 13h, 66h, 0ECh, 0FFh, 83h, 0C4h, 08h, 0C6h, 46h, 4Ch, 01h, 0C6h, 46h
    db 54h, 00h, 8Bh, 0CEh, 5Eh, 0E9h, 7Ch, 4Dh, 0EDh, 0FFh
?d_00173b20@@YAXXZ ENDP

; ghidra: FUN_00573b90  retail @ 0x00173B90 size 178
public ?d_00173b90@@YAXXZ
?d_00173b90@@YAXXZ PROC
    db 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 74h, 17h, 0A1h
    db 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 0B4h, 90h, 09h, 01h, 50h, 0E8h, 0C7h
    db 65h, 0ECh, 0FFh, 83h, 0C4h, 08h, 8Bh, 4Eh, 1Ch, 0C6h, 46h, 4Ch, 00h, 8Bh, 79h, 10h
    db 0E8h, 0ABh, 0A9h, 0E9h, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h, 8Bh
    db 99h, 04h, 02h, 00h, 00h, 74h, 61h, 85h, 0DBh, 74h, 5Dh, 8Bh, 13h, 6Ah, 04h, 8Bh
    db 0CBh, 0FFh, 92h, 0FCh, 01h, 00h, 00h, 85h, 0FFh, 74h, 1Eh, 8Bh, 8Fh, 18h, 01h, 00h
    db 00h, 0B8h, 00h, 10h, 00h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Fh, 18h, 01h
    db 00h, 00h, 8Bh, 0CFh, 0E8h, 14h, 0DDh, 0EAh, 0FFh, 0B8h, 01h, 00h, 00h, 00h, 89h, 46h
    db 50h, 88h, 46h, 54h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 57h, 0E8h, 0E0h, 20h
    db 0EAh, 0FFh, 8Bh, 4Dh, 74h, 51h, 8Bh, 0CBh, 0E8h, 0E3h, 0D7h, 0E8h, 0FFh, 5Fh, 8Bh, 0CEh
    db 5Eh, 5Dh, 5Bh, 0E9h, 0EFh, 0E1h, 0EAh, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh
    db 5Bh, 0C3h
?d_00173b90@@YAXXZ ENDP

; ghidra: FUN_00573c70  retail @ 0x00173C70 size 115
public ?d_00173c70@@YAXXZ
?d_00173c70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 61h, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h
    db 8Bh, 81h, 04h, 02h, 00h, 00h, 8Bh, 88h, 40h, 01h, 00h, 00h, 85h, 0C9h, 74h, 4Bh
    db 8Ah, 90h, 1Eh, 03h, 00h, 00h, 84h, 0D2h, 75h, 41h, 8Bh, 51h, 08h, 83h, 0C2h, 0Ch
    db 8Bh, 0Ah, 8Dh, 46h, 24h, 89h, 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h
    db 89h, 50h, 08h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh
    db 01h, 85h, 0C0h, 74h, 0Eh, 68h, 0ECh, 90h, 09h, 01h, 50h, 0E8h, 0AAh, 64h, 0ECh, 0FFh
    db 83h, 0C4h, 08h, 0C6h, 46h, 4Ch, 00h, 0C6h, 46h, 54h, 00h, 8Bh, 0CEh, 5Eh, 0E9h, 13h
    db 4Ch, 0EDh, 0FFh
?d_00173c70@@YAXXZ ENDP

; ghidra: FUN_00573e50  retail @ 0x00173E50 size 115
public ?d_00173e50@@YAXXZ
?d_00173e50@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 61h, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h
    db 8Bh, 81h, 04h, 02h, 00h, 00h, 8Bh, 88h, 40h, 01h, 00h, 00h, 85h, 0C9h, 74h, 4Bh
    db 8Ah, 90h, 1Eh, 03h, 00h, 00h, 84h, 0D2h, 75h, 41h, 8Bh, 51h, 08h, 83h, 0C2h, 0Ch
    db 8Bh, 0Ah, 8Dh, 46h, 24h, 89h, 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h
    db 89h, 50h, 08h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh
    db 01h, 85h, 0C0h, 74h, 0Eh, 68h, 5Ch, 91h, 09h, 01h, 50h, 0E8h, 0CAh, 62h, 0ECh, 0FFh
    db 83h, 0C4h, 08h, 0C6h, 46h, 4Ch, 00h, 0C6h, 46h, 54h, 00h, 8Bh, 0CEh, 5Eh, 0E9h, 33h
    db 4Ah, 0EDh, 0FFh
?d_00173e50@@YAXXZ ENDP

; ghidra: FUN_00573f30  retail @ 0x00173F30 size 94
public ?d_00173f30@@YAXXZ
?d_00173f30@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 5Bh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0F8h
    db 7Ah, 09h, 01h, 8Bh, 4Eh, 24h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 0Dh, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C7h, 46h, 24h, 00h, 00h, 00h, 00h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A7h, 27h, 0EAh, 0FFh, 8Bh, 4Ch
    db 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00173f30@@YAXXZ ENDP

; ghidra: FUN_00573fb0  retail @ 0x00173FB0 size 402
public ?d_00173fb0@@YAXXZ
?d_00173fb0@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 1Ch, 8Ah, 47h, 58h, 84h, 0C0h, 8Bh, 69h
    db 10h, 8Bh, 0B5h, 04h, 02h, 00h, 00h, 74h, 7Ch, 0E8h, 0A2h, 0A5h, 0E9h, 0FFh, 8Bh, 0D8h
    db 85h, 0DBh, 74h, 20h, 0F6h, 83h, 44h, 03h, 00h, 00h, 01h, 74h, 0Ah, 5Fh, 5Eh, 5Dh
    db 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 5Bh, 0C3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 3Bh
    db 4Fh, 5Ch, 76h, 08h, 5Fh, 5Eh, 5Dh, 83h, 0C8h, 0FFh, 5Bh, 0C3h, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 92h, 0E8h, 01h, 00h, 00h, 8Bh, 85h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h
    db 10h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh, 0CDh, 89h, 85h, 14h, 01h, 00h, 00h
    db 0E8h, 0F8h, 0D8h, 0EAh, 0FFh, 83h, 0C3h, 38h, 53h, 8Bh, 0CDh, 0E8h, 0E3h, 53h, 0EDh, 0FFh
    db 0D8h, 45h, 44h, 51h, 8Bh, 0CDh, 0D9h, 1Ch, 24h, 0E8h, 67h, 59h, 0ECh, 0FFh, 5Fh, 5Eh
    db 5Dh, 33h, 0C0h, 5Bh, 0C3h, 8Ah, 47h, 54h, 84h, 0C0h, 74h, 55h, 8Bh, 86h, 40h, 01h
    db 00h, 00h, 85h, 0C0h, 74h, 4Bh, 8Ah, 8Eh, 1Eh, 03h, 00h, 00h, 84h, 0C9h, 75h, 41h
    db 8Bh, 40h, 08h, 83h, 0C0h, 0Ch, 8Bh, 10h, 8Dh, 4Fh, 24h, 89h, 11h, 8Bh, 50h, 04h
    db 89h, 51h, 04h, 8Bh, 40h, 08h, 89h, 41h, 08h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h
    db 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 94h, 91h, 09h, 01h
    db 50h, 0E8h, 0E4h, 60h, 0ECh, 0FFh, 83h, 0C4h, 08h, 0C6h, 47h, 4Ch, 00h, 0C6h, 47h, 54h
    db 00h, 8Bh, 0CFh, 0E8h, 4Eh, 48h, 0EDh, 0FFh, 85h, 0C0h, 0Fh, 84h, 8Bh, 00h, 00h, 00h
    db 85h, 0F6h, 0C6h, 47h, 58h, 01h, 74h, 31h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0E8h, 01h
    db 00h, 00h, 8Bh, 0CEh, 0E8h, 0BDh, 0E3h, 0E9h, 0FFh, 8Dh, 47h, 24h, 8Bh, 10h, 8Dh, 8Eh
    db 80h, 01h, 00h, 00h, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h, 8Bh, 40h, 08h, 89h
    db 41h, 08h, 0C6h, 86h, 1Dh, 03h, 00h, 00h, 00h, 8Ah, 86h, 32h, 03h, 00h, 00h, 84h
    db 0C0h, 74h, 1Dh, 8Bh, 4Eh, 04h, 8Bh, 51h, 38h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h
    db 3Ch, 0C1h, 0EAh, 02h, 03h, 0D1h, 89h, 57h, 5Ch, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 0C3h
    db 8Bh, 76h, 04h, 8Bh, 46h, 34h, 8Bh, 76h, 38h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh
    db 59h, 3Ch, 68h, 0B5h, 0Dh, 00h, 00h, 68h, 9Ch, 76h, 09h, 01h, 50h, 56h, 0E8h, 7Bh
    db 0DAh, 0E8h, 0FFh, 83h, 0C4h, 10h, 03h, 0C3h, 89h, 47h, 5Ch, 5Fh, 5Eh, 5Dh, 33h, 0C0h
    db 5Bh, 0C3h
?d_00173fb0@@YAXXZ ENDP

; ghidra: FUN_005741b0  retail @ 0x001741B0 size 72
public ?d_001741b0@@YAXXZ
?d_001741b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 54h, 51h, 0EBh, 0FFh, 8Bh, 4Eh, 1Ch
    db 8Bh, 71h, 10h, 85h, 0F6h, 74h, 1Ch, 8Bh, 86h, 14h, 01h, 00h, 00h, 85h, 0C0h, 79h
    db 12h, 25h, 0FFh, 0FFh, 0FFh, 7Fh, 8Bh, 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 3Ah
    db 0D7h, 0EAh, 0FFh, 8Bh, 0B6h, 04h, 02h, 00h, 00h, 85h, 0F6h, 74h, 07h, 0C6h, 86h, 32h
    db 03h, 00h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_001741b0@@YAXXZ ENDP

; ghidra: FUN_00574520  retail @ 0x00174520 size 113
public ?d_00174520@@YAXXZ
?d_00174520@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 1Ch, 8Bh, 70h, 10h, 8Bh, 0CEh, 0E8h
    db 0CFh, 0D6h, 0E8h, 0FFh, 6Ah, 00h, 8Bh, 0CEh, 88h, 47h, 24h, 0E8h, 0E6h, 9Bh, 0ECh, 0FFh
    db 33h, 0C0h, 6Ah, 01h, 8Dh, 4Ch, 24h, 0Ch, 89h, 44h, 24h, 0Ch, 89h, 44h, 24h, 10h
    db 83h, 0C8h, 10h, 51h, 8Bh, 0CEh, 89h, 44h, 24h, 18h, 0E8h, 88h, 0C2h, 0EBh, 0FFh, 8Bh
    db 8Eh, 30h, 01h, 00h, 00h, 0B8h, 00h, 00h, 00h, 02h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h
    db 89h, 8Eh, 30h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0A0h, 0D3h, 0EAh, 0FFh, 8Bh, 57h, 1Ch
    db 8Bh, 0CFh, 0C6h, 42h, 40h, 01h, 0E8h, 79h, 28h, 0EBh, 0FFh, 5Fh, 5Eh, 83h, 0C4h, 0Ch
    db 0C3h
?d_00174520@@YAXXZ ENDP

; ghidra: FUN_005745b0  retail @ 0x001745B0 size 153
public ?d_001745b0@@YAXXZ
?d_001745b0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 1Ch, 8Bh, 70h, 10h, 33h, 0C9h, 8Ah
    db 4Fh, 24h, 51h, 8Bh, 0CEh, 0E8h, 5Ch, 9Bh, 0ECh, 0FFh, 33h, 0C0h, 89h, 44h, 24h, 08h
    db 89h, 44h, 24h, 0Ch, 6Ah, 00h, 8Dh, 54h, 24h, 0Ch, 83h, 0C8h, 10h, 52h, 8Bh, 0CEh
    db 89h, 44h, 24h, 18h, 0E8h, 0FEh, 0C1h, 0EBh, 0FFh, 8Bh, 86h, 30h, 01h, 00h, 00h, 0A9h
    db 00h, 00h, 00h, 02h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FDh, 8Bh, 0CEh, 89h, 86h, 30h
    db 01h, 00h, 00h, 0E8h, 15h, 0D3h, 0EAh, 0FFh, 8Bh, 47h, 1Ch, 0C6h, 40h, 40h, 00h, 8Bh
    db 4Fh, 1Ch, 8Bh, 71h, 10h, 85h, 0F6h, 74h, 28h, 6Ah, 04h, 8Bh, 0CEh, 0E8h, 24h, 0Fh
    db 0EAh, 0FFh, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 15h, 8Bh, 11h, 0FFh, 52h
    db 68h, 85h, 0C0h, 74h, 0Ch, 8Bh, 10h, 6Ah, 00h, 8Bh, 0C8h, 0FFh, 92h, 70h, 01h, 00h
    db 00h, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_001745b0@@YAXXZ ENDP

; ghidra: FUN_00574670  retail @ 0x00174670 size 88
public ?d_00174670@@YAXXZ
?d_00174670@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 57h, 0E8h, 0F3h, 9Eh, 0E9h, 0FFh, 8Bh, 0D8h, 85h
    db 0DBh, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h, 8Bh, 0B9h, 04h, 02h, 00h, 00h, 74h, 30h, 85h
    db 0FFh, 74h, 2Ch, 8Bh, 17h, 6Ah, 04h, 8Bh, 0CFh, 0FFh, 92h, 0FCh, 01h, 00h, 00h, 0B8h
    db 01h, 00h, 00h, 00h, 89h, 46h, 50h, 88h, 46h, 54h, 8Bh, 43h, 74h, 50h, 8Bh, 0CFh
    db 0E8h, 5Bh, 0CDh, 0E8h, 0FFh, 5Fh, 8Bh, 0CEh, 5Eh, 5Bh, 0E9h, 68h, 0D7h, 0EAh, 0FFh, 5Fh
    db 5Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 0C3h
?d_00174670@@YAXXZ ENDP

; ghidra: FUN_00574730  retail @ 0x00174730 size 159
public ?d_00174730@@YAXXZ
?d_00174730@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 57h, 8Bh, 79h, 10h, 0E8h, 31h, 9Eh, 0E9h, 0FFh, 85h
    db 0C0h, 0Fh, 84h, 80h, 00h, 00h, 00h, 8Bh, 46h, 1Ch, 8Bh, 48h, 10h, 8Bh, 81h, 04h
    db 02h, 00h, 00h, 85h, 0C0h, 74h, 70h, 8Ah, 46h, 54h, 84h, 0C0h, 74h, 60h, 8Bh, 87h
    db 04h, 02h, 00h, 00h, 8Bh, 88h, 40h, 01h, 00h, 00h, 85h, 0C9h, 74h, 4Bh, 8Ah, 90h
    db 1Eh, 03h, 00h, 00h, 84h, 0D2h, 75h, 41h, 8Bh, 51h, 08h, 83h, 0C2h, 0Ch, 8Bh, 0Ah
    db 8Dh, 46h, 24h, 89h, 08h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 89h, 50h
    db 08h, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h
    db 0C0h, 74h, 0Eh, 68h, 44h, 92h, 09h, 01h, 50h, 0E8h, 0CCh, 59h, 0ECh, 0FFh, 83h, 0C4h
    db 08h, 0C6h, 46h, 4Ch, 00h, 0C6h, 46h, 54h, 00h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 5Fh, 8Bh
    db 0CEh, 5Eh, 0E9h, 2Fh, 41h, 0EDh, 0FFh, 5Fh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Eh, 0C3h
?d_00174730@@YAXXZ ENDP

; ghidra: FUN_00574a20  retail @ 0x00174A20 size 536
public ?d_00174a20@@YAXXZ
?d_00174a20@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 73h, 5Bh, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 78h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 1Ch
    db 8Bh, 70h, 10h, 8Bh, 86h, 18h, 01h, 00h, 00h, 0A8h, 01h, 75h, 10h, 83h, 0C8h, 01h
    db 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 0C0h, 0CEh, 0EAh, 0FFh, 8Bh, 4Fh, 1Ch
    db 8Bh, 0AEh, 04h, 02h, 00h, 00h, 0E8h, 05h, 9Bh, 0E9h, 0FFh, 85h, 0C0h, 0Fh, 84h, 0AAh
    db 01h, 00h, 00h, 0F6h, 80h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 9Dh, 01h, 00h, 00h
    db 8Ah, 47h, 58h, 84h, 0C0h, 74h, 1Ah, 5Fh, 5Eh, 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 5Dh, 8Bh
    db 4Ch, 24h, 78h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 84h, 00h, 00h, 00h
    db 0C3h, 8Ah, 47h, 54h, 84h, 0C0h, 74h, 5Bh, 8Bh, 86h, 04h, 02h, 00h, 00h, 8Bh, 88h
    db 40h, 01h, 00h, 00h, 85h, 0C9h, 74h, 4Bh, 8Ah, 90h, 1Eh, 03h, 00h, 00h, 84h, 0D2h
    db 75h, 41h, 8Bh, 49h, 08h, 83h, 0C1h, 0Ch, 8Bh, 01h, 8Dh, 57h, 24h, 89h, 02h, 8Bh
    db 41h, 04h, 89h, 42h, 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 0A0h, 39h, 02h, 2Fh, 01h
    db 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 0D0h, 92h
    db 09h, 01h, 50h, 0E8h, 82h, 56h, 0ECh, 0FFh, 83h, 0C4h, 08h, 0C6h, 47h, 4Ch, 00h, 0C6h
    db 47h, 54h, 00h, 8Bh, 0CFh, 0E8h, 0ECh, 3Dh, 0EDh, 0FFh, 85h, 0C0h, 74h, 0Fh, 85h, 0EDh
    db 0C6h, 47h, 58h, 01h, 74h, 07h, 8Bh, 0CDh, 0E8h, 69h, 0D9h, 0E9h, 0FFh, 6Ah, 04h, 8Dh
    db 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0E8h, 0A7h, 0B7h, 0ECh, 0FFh, 3Ch, 01h, 0Fh, 85h, 0D3h
    db 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 28h, 8Bh, 0F8h, 83h, 0CDh, 0FFh, 85h
    db 0FFh, 0Fh, 84h, 0A8h, 00h, 00h, 00h, 68h, 0B4h, 92h, 09h, 01h, 8Dh, 4Ch, 24h, 10h
    db 0E8h, 6Bh, 40h, 71h, 00h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CFh, 0C7h, 84h, 24h, 90h
    db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 0D8h, 0B1h, 0E9h, 0FFh, 8Dh, 4Ch, 24h, 0Ch
    db 8Bh, 0F8h, 89h, 0ACh, 24h, 8Ch, 00h, 00h, 00h, 0E8h, 0C2h, 2Dh, 71h, 00h, 85h, 0FFh
    db 74h, 6Dh, 57h, 8Dh, 4Ch, 24h, 18h, 0E8h, 9Bh, 2Fh, 0EDh, 0FFh, 8Bh, 46h, 74h, 50h
    db 8Dh, 4Ch, 24h, 18h, 0C7h, 84h, 24h, 90h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 0E8h
    db 0C6h, 4Eh, 0EAh, 0FFh, 8Bh, 8Eh, 3Ch, 02h, 00h, 00h, 85h, 0C9h, 74h, 21h, 0E8h, 0E8h
    db 0EAh, 0EAh, 0FFh, 85h, 0C0h, 74h, 18h, 8Bh, 8Eh, 3Ch, 02h, 00h, 00h, 0E8h, 0D9h, 0EAh
    db 0EAh, 0FFh, 8Bh, 40h, 24h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 0B9h, 60h, 0ECh, 0FFh, 8Bh
    db 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 14h, 50h, 0FFh, 52h, 44h, 8Dh
    db 4Ch, 24h, 14h, 89h, 0ACh, 24h, 8Ch, 00h, 00h, 00h, 0E8h, 46h, 23h, 0EBh, 0FFh, 5Fh
    db 5Eh, 8Bh, 0C5h, 5Dh, 8Bh, 4Ch, 24h, 78h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h
    db 0C4h, 84h, 00h, 00h, 00h, 0C3h, 5Fh, 5Eh, 33h, 0C0h, 5Dh, 8Bh, 4Ch, 24h, 78h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 84h, 00h, 00h, 00h, 0C3h, 8Bh, 8Ch, 24h
    db 84h, 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C8h, 0FFh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 81h, 0C4h, 84h, 00h, 00h, 00h, 0C3h
?d_00174a20@@YAXXZ ENDP

; ghidra: FUN_00574cc0  retail @ 0x00174CC0 size 261
public ?d_00174cc0@@YAXXZ
?d_00174cc0@@YAXXZ PROC
    db 8Bh, 87h, 08h, 02h, 00h, 00h, 83h, 0ECh, 08h, 85h, 0C0h, 0Fh, 84h, 97h, 00h, 00h
    db 00h, 0F6h, 86h, 94h, 00h, 00h, 00h, 20h, 74h, 0Eh, 8Bh, 86h, 14h, 02h, 00h, 00h
    db 85h, 0C0h, 0Fh, 85h, 80h, 00h, 00h, 00h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h
    db 74h, 76h, 0E8h, 0ACh, 0F9h, 0EBh, 0FFh, 83h, 0F8h, 0FFh, 74h, 6Ch, 0A1h, 14h, 0F2h, 2Eh
    db 01h, 8Bh, 48h, 14h, 8Ah, 81h, 8Ch, 00h, 00h, 00h, 84h, 0C0h, 74h, 2Ah, 8Bh, 0CEh
    db 0E8h, 0Fh, 0BBh, 0EAh, 0FFh, 85h, 0C0h, 74h, 1Fh, 8Bh, 0CEh, 0E8h, 04h, 0BBh, 0EAh, 0FFh
    db 83h, 78h, 2Ch, 01h, 75h, 12h, 6Ah, 02h, 57h, 8Bh, 0CEh, 0E8h, 7Ah, 0D3h, 0ECh, 0FFh
    db 84h, 0C0h, 0Fh, 85h, 87h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch, 57h, 56h, 0E8h, 99h
    db 9Ah, 0E9h, 0FFh, 84h, 0C0h, 75h, 21h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 0E8h, 53h, 8Dh
    db 0ECh, 0FFh, 0D9h, 1Ch, 24h, 8Bh, 0CFh, 0E8h, 6Ch, 0FAh, 0E8h, 0FFh, 0D8h, 14h, 24h, 0DFh
    db 0E0h, 0F6h, 0C4h, 01h, 75h, 08h, 0DDh, 0D8h, 32h, 0C0h, 83h, 0C4h, 08h, 0C3h, 0D9h, 04h
    db 24h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h, 0D9h, 0C9h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 7Bh, 0E6h, 0D9h, 47h, 38h, 8Bh, 0CFh, 0D8h, 66h, 38h, 0D9h, 5Ch, 24h, 04h, 0D9h, 47h
    db 3Ch, 0D8h, 66h, 3Ch, 0D9h, 1Ch, 24h, 0E8h, 0AAh, 0B4h, 0ECh, 0FFh, 0D9h, 00h, 0D9h, 40h
    db 04h, 0D9h, 04h, 24h, 0D8h, 0C9h, 0D9h, 0CAh, 0D8h, 4Ch, 24h, 04h, 0DEh, 0C2h, 0D9h, 0C9h
    db 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 05h, 7Bh, 0A9h, 0B0h
    db 01h, 83h, 0C4h, 08h, 0C3h
?d_00174cc0@@YAXXZ ENDP

; ghidra: FUN_00574e10  retail @ 0x00174E10 size 734
public ?d_00174e10@@YAXXZ
?d_00174e10@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 1Ch, 56h, 8Bh, 70h, 10h, 8Bh, 46h
    db 04h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 57h, 33h, 0FFh, 3Bh, 0C7h, 89h, 4Ch, 24h, 14h
    db 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CFh, 74h, 05h, 0E8h, 79h, 0D4h
    db 0E8h, 0FFh, 0F7h, 80h, 0C8h, 00h, 00h, 00h, 00h, 00h, 00h, 02h, 0BBh, 08h, 00h, 00h
    db 00h, 74h, 11h, 8Bh, 54h, 24h, 14h, 8Bh, 82h, 0CCh, 01h, 00h, 00h, 3Bh, 0C7h, 74h
    db 03h, 09h, 58h, 40h, 8Dh, 46h, 38h, 8Bh, 10h, 8Dh, 4Dh, 5Ch, 89h, 11h, 8Bh, 50h
    db 04h, 89h, 51h, 04h, 8Bh, 40h, 08h, 89h, 41h, 08h, 8Bh, 4Dh, 1Ch, 0E8h, 0AAh, 0F4h
    db 0E8h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0C0h, 00h, 00h, 00h, 88h, 45h, 75h, 84h, 9Eh, 98h
    db 00h, 00h, 00h, 0Fh, 85h, 22h, 02h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Ah, 81h, 3Ah
    db 03h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 10h, 02h, 00h, 00h, 57h, 8Bh, 0CEh, 89h, 7Dh
    db 50h, 89h, 7Dh, 54h, 89h, 7Dh, 58h, 0C7h, 45h, 68h, 0FBh, 0FFh, 0FFh, 0FFh, 0E8h, 0BCh
    db 0CBh, 0EBh, 0FFh, 8Bh, 4Dh, 1Ch, 8Bh, 0F8h, 89h, 7Ch, 24h, 18h, 0E8h, 9Fh, 96h, 0E9h
    db 0FFh, 8Bh, 0D8h, 85h, 0DBh, 0Fh, 84h, 0C2h, 00h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 0FEh
    db 01h, 00h, 00h, 6Ah, 00h, 53h, 56h, 8Bh, 0CFh, 0E8h, 6Eh, 99h, 0EBh, 0FFh, 84h, 0C0h
    db 74h, 36h, 8Bh, 4Ch, 24h, 14h, 8Bh, 11h, 0FFh, 92h, 0ECh, 01h, 00h, 00h, 84h, 0C0h
    db 74h, 48h, 8Bh, 0CBh, 0E8h, 0E8h, 50h, 0EAh, 0FFh, 84h, 0C0h, 75h, 3Dh, 0A1h, 14h, 0F2h
    db 2Eh, 01h, 8Bh, 48h, 0Ch, 8Dh, 53h, 38h, 52h, 53h, 8Dh, 46h, 38h, 50h, 56h, 0E8h
    db 1Eh, 0E1h, 0EAh, 0FFh, 84h, 0C0h, 74h, 22h, 8Bh, 0FEh, 0E8h, 0E1h, 60h, 0FFh, 0FFh, 84h
    db 0C0h, 0Fh, 84h, 0AAh, 01h, 00h, 00h, 8Bh, 44h, 24h, 18h, 50h, 8Bh, 0FBh, 0E8h, 7Dh
    db 0FDh, 0FFh, 0FFh, 83h, 0C4h, 04h, 84h, 0C0h, 74h, 0Bh, 5Fh, 5Eh, 5Dh, 83h, 0C8h, 0FFh
    db 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 4Ch, 24h, 14h, 8Bh, 51h, 04h, 8Ah, 42h, 28h, 84h
    db 0C0h, 74h, 53h, 8Bh, 0CEh, 0E8h, 27h, 54h, 0ECh, 0FFh, 83h, 0F8h, 11h, 7Ch, 47h, 8Bh
    db 4Ch, 24h, 14h, 8Dh, 43h, 38h, 50h, 0E8h, 36h, 3Fh, 0EAh, 0FFh, 84h, 0C0h, 75h, 36h
    db 0C6h, 45h, 75h, 01h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 83h, 0C2h, 0Ah
    db 89h, 55h, 6Ch, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 85h, 0FFh, 0Fh
    db 84h, 3Ch, 01h, 00h, 00h, 8Bh, 47h, 04h, 8Ah, 88h, 33h, 05h, 00h, 00h, 84h, 0C9h
    db 0Fh, 84h, 2Bh, 01h, 00h, 00h, 6Ah, 25h, 8Bh, 0CEh, 0E8h, 0E5h, 0C6h, 0E8h, 0FFh, 84h
    db 0C0h, 74h, 0Eh, 8Bh, 86h, 14h, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 10h, 01h, 00h
    db 00h, 8Bh, 0CEh, 0C6h, 44h, 24h, 13h, 01h, 0E8h, 2Ah, 26h, 0EAh, 0FFh, 84h, 0C0h, 75h
    db 04h, 88h, 44h, 24h, 13h, 8Bh, 7Ch, 24h, 14h, 8Bh, 8Fh, 0CCh, 01h, 00h, 00h, 56h
    db 0E8h, 0B6h, 0E0h, 0EAh, 0FFh, 0D8h, 1Dh, 70h, 5Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 0Fh, 8Bh, 7Ah, 0FFh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 0Fh, 84h, 6Eh, 0FFh
    db 0FFh, 0FFh, 8Bh, 0CFh, 0E8h, 8Ah, 0F6h, 0EBh, 0FFh, 83h, 0F8h, 0FFh, 74h, 27h, 8Ah, 4Dh
    db 71h, 84h, 0C9h, 74h, 11h, 33h, 0C9h, 8Ah, 4Dh, 74h, 51h, 53h, 50h, 8Bh, 0CFh, 0E8h
    db 0ADh, 50h, 0EAh, 0FFh, 0EBh, 0Fh, 8Bh, 55h, 1Ch, 83h, 0C2h, 24h, 52h, 50h, 8Bh, 0CFh
    db 0E8h, 78h, 0E1h, 0EBh, 0FFh, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 50h, 44h, 84h, 0C0h, 0Fh
    db 84h, 8Ch, 00h, 00h, 00h, 8Ah, 45h, 75h, 84h, 0C0h, 0Fh, 85h, 33h, 0FFh, 0FFh, 0FFh
    db 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h
    db 74h, 0Eh, 68h, 40h, 93h, 09h, 01h, 50h, 0E8h, 0FDh, 50h, 0ECh, 0FFh, 83h, 0C4h, 08h
    db 8Bh, 0CDh, 0C6h, 45h, 4Ch, 00h, 0E8h, 9Ch, 0CDh, 0EAh, 0FFh, 8Bh, 0F0h, 0A0h, 39h, 02h
    db 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h
    db 08h, 93h, 09h, 01h, 50h, 0E8h, 0D0h, 50h, 0ECh, 0FFh, 83h, 0C4h, 08h, 5Fh, 8Bh, 0C6h
    db 5Eh, 0C6h, 45h, 4Ch, 01h, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 4Dh, 1Ch, 0E8h, 0ADh
    db 94h, 0E9h, 0FFh, 50h, 56h, 0E8h, 6Dh, 0FBh, 0E8h, 0FFh, 83h, 0C4h, 08h, 84h, 0C0h, 0Fh
    db 85h, 75h, 0FEh, 0FFh, 0FFh, 8Bh, 6Dh, 1Ch, 8Bh, 55h, 00h, 57h, 8Bh, 0CDh, 0FFh, 52h
    db 38h, 5Fh, 5Eh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_00174e10@@YAXXZ ENDP

; ghidra: FUN_005752a0  retail @ 0x001752A0 size 943
_TEXT ENDS
_TEXT$d005752a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005752A0 size 943
public ?d_001752a0@@YAXXZ
?d_001752a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01005B9E
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 034h, 055h, 08Bh, 06Ch, 024h, 04Ch, 08Bh, 085h, 004h, 002h, 000h, 000h, 085h, 0C0h, 089h, 044h
    db 024h, 010h, 075h, 012h, 032h, 0C0h, 05Dh, 08Bh, 04Ch, 024h, 034h, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 040h, 0C3h, 053h, 056h, 08Bh, 074h, 024h, 050h, 0D9h, 006h, 057h, 0D9h
    db 046h, 004h, 08Dh, 07Dh, 038h, 0D9h, 0C9h, 08Bh, 05Ch, 024h, 05Ch, 085h, 0DBh, 0D8h, 027h, 08Bh
    db 006h, 08Bh, 04Eh, 004h, 0D9h, 05Ch, 024h, 020h, 08Bh, 056h, 008h, 089h, 044h, 024h, 038h, 0D8h
    db 067h, 004h, 089h, 04Ch, 024h, 03Ch, 089h, 054h, 024h, 040h, 0D9h, 0C0h, 0DEh, 0C9h, 0D9h, 044h
    db 024h, 020h, 0D8h, 04Ch, 024h, 020h, 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 05Ch, 024h, 018h, 074h, 07Ah
    db 08Dh, 043h, 038h, 08Bh, 008h, 08Bh, 050h, 004h, 08Bh, 040h, 008h, 089h, 04Ch, 024h, 038h, 06Ah
    db 05Ch, 08Bh, 0CBh, 089h, 054h, 024h, 040h, 089h, 044h, 024h, 044h
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 056h, 0F6h, 005h
    dd ?g_Va012EF2F4@@3IA
    db 001h, 075h, 02Ch, 083h, 00Dh
    dd ?g_Va012EF2F4@@3IA
    db 001h, 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 068h
    dd g_Va0108F924
    db 0C7h, 044h, 024h, 050h, 000h, 000h, 000h, 000h
    call ?j_0003add7@@YAXXZ
    db 0A3h
    dd g_Va012EF2F0
    db 0C7h, 044h, 024h, 04Ch, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 00Dh
    dd g_Va012EF2F0
    db 051h, 08Bh, 0CBh
    call ?j_0002ae23@@YAXXZ
    db 085h, 0C0h, 074h, 00Fh, 08Bh, 0C8h
    call ?j_00048112@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 099h, 002h, 000h, 000h, 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 05Ah, 00Ch, 06Ah, 000h, 06Ah, 000h, 08Bh, 0CDh
    call ?j_00031a7f@@YAXXZ
    db 050h, 08Dh, 044h, 024h, 040h, 050h, 055h, 08Bh, 0CBh
    call ?j_00032b46@@YAXXZ
    db 084h, 0C0h, 088h, 044h, 024h, 013h, 074h, 01Bh, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 06Ah, 000h, 056h, 057h, 055h
    call ?j_0004a327@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 054h, 002h, 000h, 000h, 08Bh, 0D6h, 08Bh, 002h, 08Bh, 04Ah, 004h, 089h
    db 044h, 024h, 020h, 0D9h, 044h, 024h, 020h, 0D8h, 027h, 089h, 04Ch, 024h, 024h, 0D9h, 044h, 024h
    db 024h, 08Bh, 052h, 008h, 0D8h, 067h, 004h, 08Bh, 006h, 08Bh, 04Eh, 004h, 089h, 054h, 024h, 028h
    db 0D9h, 0C0h, 08Bh, 056h, 008h, 0D8h, 0C9h, 089h, 044h, 024h, 02Ch, 0D9h, 0C2h, 089h, 04Ch, 024h
    db 030h, 0D8h, 0CBh, 089h, 054h, 024h, 034h, 0D9h, 0C1h, 0D8h, 0C1h, 0D9h, 0FAh, 0D8h, 00Dh
    dd g_Va010977E4
    call __ftol2
    db 0D9h, 0C9h, 0D8h, 0C1h, 083h, 0CBh, 0FFh, 02Bh, 0D8h, 085h, 0DBh, 0D9h, 0FAh, 0C7h, 044h, 024h
    db 014h, 000h, 000h, 000h, 000h, 0DDh, 0D9h, 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 054h, 024h, 058h, 0D8h, 0CAh, 0D9h, 05Ch, 024h, 020h, 0D8h, 04Ch, 024h, 058h, 0DDh, 0D9h
    db 0D9h, 044h, 024h, 058h, 0C6h, 044h, 024h, 058h, 000h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 020h, 0D8h, 00Dh
    dd ?g_pathfindDoubleCellSize@@3MB
    db 0D9h, 05Ch, 024h, 020h, 0D9h, 0C9h, 0D8h, 00Dh
    dd ?g_pathfindDoubleCellSize@@3MB
    db 0D9h, 05Ch, 024h, 024h, 0D8h, 00Dh
    dd ?g_pathfindDoubleCellSize@@3MB
    db 0D9h, 05Ch, 024h, 028h, 00Fh, 08Eh, 083h, 000h, 000h, 000h, 08Dh, 064h, 024h, 000h, 0D9h, 044h
    db 024h, 02Ch, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 0D8h, 064h, 024h, 020h, 06Ah, 000h, 08Dh, 054h, 024h, 030h, 052h, 0D9h, 05Ch, 024h, 034h, 057h
    db 0D9h, 044h, 024h, 03Ch, 055h, 0D8h, 064h, 024h, 034h, 0D9h, 05Ch, 024h, 040h, 0D9h, 044h, 024h
    db 044h, 0D8h, 064h, 024h, 038h, 0D9h, 05Ch, 024h, 044h, 08Bh, 048h, 00Ch
    call ?j_0004a327@@YAXXZ
    db 084h, 0C0h, 075h, 056h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Dh, 044h, 024h, 02Ch, 050h, 055h
    call ?j_0001c675@@YAXXZ
    db 083h, 0F8h, 001h, 07Fh, 019h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 06Ah, 001h, 08Dh, 054h, 024h, 030h, 052h
    call ?j_00007fbd@@YAXXZ
    db 084h, 0C0h, 074h, 005h, 0C6h, 044h, 024h, 058h, 001h, 08Bh, 044h, 024h, 014h, 040h, 03Bh, 0C3h
    db 089h, 044h, 024h, 014h, 07Ch, 081h, 05Fh, 05Eh, 05Bh, 032h, 0C0h, 05Dh, 08Bh, 04Ch, 024h, 034h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 040h, 0C3h, 08Ah, 04Ch, 024h, 058h, 08Bh
    db 03Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 032h, 0C0h, 084h, 0C9h, 074h, 066h, 08Ah, 04Ch, 024h, 013h, 084h, 0C9h, 075h, 05Eh, 08Bh, 047h
    db 014h, 0D9h, 080h, 0D0h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 020h, 0D8h, 085h, 0BCh, 000h, 000h
    db 000h, 0D9h, 05Ch, 024h, 058h
    call ?j_0002bd82@@YAXXZ
    db 0D9h, 044h, 024h, 020h, 0B0h, 001h, 0D8h, 04Ch, 024h, 058h, 0D9h, 044h, 024h, 024h, 0D8h, 04Ch
    db 024h, 058h, 0D9h, 044h, 024h, 058h, 0D8h, 04Ch, 024h, 028h, 0D9h, 05Ch, 024h, 028h, 0D9h, 044h
    db 024h, 02Ch, 0D8h, 0E2h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 030h, 0D8h, 0E1h, 0D9h, 05Ch
    db 024h, 030h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 034h, 0D8h, 064h, 024h, 028h, 0D9h, 05Ch
    db 024h, 034h, 084h, 0C0h, 08Bh, 0CEh, 08Bh, 011h, 089h, 054h, 024h, 020h, 0D9h, 044h, 024h, 020h
    db 08Bh, 051h, 004h, 0D8h, 064h, 024h, 02Ch, 08Bh, 049h, 008h, 089h, 054h, 024h, 024h, 0D9h, 044h
    db 024h, 024h, 0D8h, 064h, 024h, 030h, 089h, 04Ch, 024h, 028h, 075h, 036h, 0D9h, 0C0h, 0D8h, 0C9h
    db 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 005h
    dd ?g_pathfindDoubleCellSize@@3MB
    db 0D8h, 05Ch, 024h, 018h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 019h, 05Fh, 05Eh, 05Bh, 032h, 0C0h
    db 05Dh, 08Bh, 04Ch, 024h, 034h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 040h, 0C3h
    db 0DDh, 0D8h, 0DDh, 0D8h, 08Bh, 044h, 024h, 01Ch, 08Bh, 04Fh, 00Ch, 08Dh, 054h, 024h, 02Ch, 052h
    db 005h, 0A8h, 001h, 000h, 000h, 050h, 055h
    call ?j_00011252@@YAXXZ
    db 08Bh, 04Ch, 024h, 02Ch, 08Bh, 054h, 024h, 030h, 08Bh, 044h, 024h, 034h, 089h, 00Eh, 089h, 056h
    db 004h, 089h, 046h, 008h, 08Bh, 04Ch, 024h, 044h, 05Fh, 05Eh, 05Bh, 0B0h, 001h, 05Dh, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 040h, 0C3h
?d_001752a0@@YAXXZ ENDP
_TEXT$d005752a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00575820  retail @ 0x00175820 size 158
public ?d_00175820@@YAXXZ
?d_00175820@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 0Fh, 84h, 87h, 00h, 00h, 00h
    db 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 75h, 7Eh, 0F6h, 86h, 94h, 00h, 00h, 00h, 20h
    db 74h, 18h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 4Ah, 01h, 0ECh, 0FFh, 85h, 0C0h, 74h, 0Bh, 6Ah
    db 00h, 8Bh, 0CEh, 0E8h, 3Dh, 01h, 0ECh, 0FFh, 8Bh, 0F0h, 0D9h, 46h, 38h, 8Bh, 44h, 24h
    db 14h, 0D9h, 46h, 3Ch, 8Bh, 0CEh, 0D9h, 0C9h, 0D8h, 60h, 38h, 0D9h, 5Ch, 24h, 04h, 0D8h
    db 60h, 3Ch, 0D9h, 5Ch, 24h, 08h, 0E8h, 0CBh, 0A9h, 0ECh, 0FFh, 0D9h, 00h, 0D9h, 40h, 04h
    db 0D9h, 44h, 24h, 08h, 0D8h, 0C9h, 0D9h, 0CAh, 0D8h, 4Ch, 24h, 04h, 0DEh, 0C2h, 0D9h, 0C9h
    db 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 05h, 7Bh, 18h, 8Bh
    db 0CEh, 0E8h, 86h, 0FFh, 0ECh, 0FFh, 85h, 0C0h, 74h, 0Dh, 56h, 8Bh, 0C8h, 0E8h, 21h, 12h
    db 0EDh, 0FFh, 5Eh, 83h, 0C4h, 0Ch, 0C3h, 32h, 0C0h, 5Eh, 83h, 0C4h, 0Ch, 0C3h
?d_00175820@@YAXXZ ENDP

; ghidra: FUN_005758f0  retail @ 0x001758F0 size 308
public ?d_001758f0@@YAXXZ
?d_001758f0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 4Bh, 1Ch, 55h, 8Bh, 69h, 10h, 89h, 5Ch, 24h
    db 10h, 0E8h, 26h, 0EAh, 0E8h, 0FFh, 84h, 0C0h, 74h, 09h, 5Dh, 83h, 0C8h, 0FFh, 5Bh, 83h
    db 0C4h, 0Ch, 0C3h, 8Bh, 4Bh, 1Ch, 56h, 0E8h, 54h, 8Ch, 0E9h, 0FFh, 8Bh, 0F0h, 85h, 0F6h
    db 75h, 0Ah, 5Eh, 5Dh, 83h, 0C8h, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 8Dh, 0FCh, 01h
    db 00h, 00h, 85h, 0C9h, 57h, 0Fh, 84h, 0DFh, 00h, 00h, 00h, 8Bh, 01h, 0FFh, 50h, 68h
    db 8Bh, 0F8h, 85h, 0FFh, 75h, 0Bh, 5Fh, 5Eh, 5Dh, 83h, 0C8h, 0FFh, 5Bh, 83h, 0C4h, 0Ch
    db 0C3h, 0F6h, 86h, 94h, 00h, 00h, 00h, 20h, 8Bh, 4Eh, 74h, 89h, 4Ch, 24h, 10h, 74h
    db 16h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 3Ch, 0A1h, 0E9h, 0FFh, 85h, 0C0h, 74h, 09h, 8Bh, 50h
    db 74h, 89h, 54h, 24h, 10h, 8Bh, 0F0h, 56h, 55h, 0E8h, 0EFh, 0ABh, 0EAh, 0FFh, 83h, 0C4h
    db 08h, 84h, 0C0h, 74h, 0Dh, 5Fh, 5Eh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h
    db 0Ch, 0C3h, 8Bh, 07h, 56h, 8Bh, 0CFh, 0FFh, 90h, 24h, 01h, 00h, 00h, 84h, 0C0h, 75h
    db 50h, 6Ah, 5Ch, 8Bh, 0CEh, 0BBh, 28h, 00h, 00h, 00h, 0E8h, 70h, 0CBh, 0EBh, 0FFh, 84h
    db 0C0h, 74h, 11h, 8Bh, 0CDh, 0E8h, 0D7h, 49h, 0ECh, 0FFh, 83h, 0F8h, 01h, 74h, 05h, 0BBh
    db 3Ch, 00h, 00h, 00h, 56h, 8Bh, 0CDh, 0E8h, 21h, 0E3h, 0ECh, 0FFh, 8Bh, 0CBh, 0Fh, 0AFh
    db 0CBh, 89h, 4Ch, 24h, 14h, 0DBh, 44h, 24h, 14h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 0A3h, 8Bh, 17h, 56h, 8Bh, 0CFh, 0FFh, 92h, 34h, 01h, 00h, 00h, 8Bh, 5Ch, 24h
    db 18h, 8Bh, 4Ch, 24h, 10h, 8Bh, 07h, 51h, 8Bh, 0CFh, 0FFh, 90h, 38h, 01h, 00h, 00h
    db 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh, 42h, 3Ch, 83h, 0C0h, 0Fh, 89h, 43h, 24h, 8Bh
    db 17h, 56h, 8Bh, 0CFh, 0FFh, 92h, 10h, 01h, 00h, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh
    db 83h, 0C4h, 0Ch, 0C3h
?d_001758f0@@YAXXZ ENDP

; ghidra: FUN_00575c00  retail @ 0x00175C00 size 91
public ?d_00175c00@@YAXXZ
?d_00175c00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 1Ch, 0C7h, 46h, 28h, 00h, 00h, 00h, 00h, 0E8h, 1Ah, 0E7h
    db 0E8h, 0FFh, 84h, 0C0h, 75h, 0Ch, 8Bh, 4Eh, 1Ch, 0E8h, 52h, 89h, 0E9h, 0FFh, 85h, 0C0h
    db 75h, 05h, 83h, 0C8h, 0FFh, 5Eh, 0C3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 8Bh
    db 56h, 1Ch, 89h, 4Eh, 24h, 8Bh, 42h, 10h, 0F6h, 80h, 98h, 00h, 00h, 00h, 08h, 75h
    db 10h, 8Bh, 80h, 04h, 02h, 00h, 00h, 8Ah, 90h, 3Ah, 03h, 00h, 00h, 84h, 0D2h, 74h
    db 06h, 83h, 0C1h, 07h, 89h, 4Eh, 24h, 33h, 0C0h, 5Eh, 0C3h
?d_00175c00@@YAXXZ ENDP

; ghidra: FUN_00576070  retail @ 0x00176070 size 379
_TEXT ENDS
_TEXT$d00576070 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00576070 size 379
public ?d_00176070@@YAXXZ
?d_00176070@@YAXXZ PROC
    db 053h, 055h, 056h, 08Bh, 0E9h, 057h, 08Bh, 07Dh, 01Ch, 08Bh, 077h, 010h, 08Bh, 046h, 004h, 085h
    db 0C0h, 08Bh, 09Eh, 004h, 002h, 000h, 000h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0C8h, 000h, 000h, 000h, 000h, 000h, 000h, 002h, 00Fh, 085h, 009h, 001h, 000h, 000h
    db 08Bh, 0CFh
    call ?j_0000432c@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0FAh, 000h, 000h, 000h, 08Ah, 045h, 061h, 084h, 0C0h, 074h, 066h, 0F6h
    db 086h, 098h, 000h, 000h, 000h, 008h, 00Fh, 085h, 0F9h, 000h, 000h, 000h, 08Ah, 083h, 03Ah, 003h
    db 000h, 000h, 084h, 0C0h, 00Fh, 085h, 0EBh, 000h, 000h, 000h, 0A0h
    dd ?Glo012F0239@@3_NA
    db 033h, 0FFh, 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 03Bh, 0C7h, 074h, 00Eh, 068h
    dd g_Va010993FC
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0CEh, 0C6h, 045h, 04Ch, 000h
    call ?j_00020824@@YAXXZ
    db 039h, 078h, 02Ch, 075h, 023h, 08Bh, 003h, 08Bh, 0CBh, 0FFh, 090h, 000h, 002h, 000h, 000h, 083h
    db 0F8h, 002h, 075h, 014h, 08Ah, 086h, 0F5h, 001h, 000h, 000h, 084h, 0C0h, 075h, 00Ah, 05Fh, 05Eh
    db 05Dh, 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 05Bh, 0C3h, 08Bh, 04Dh, 01Ch, 089h, 07Dh, 050h, 089h, 07Dh
    db 054h, 089h, 07Dh, 058h, 0C7h, 045h, 05Ch, 0FBh, 0FFh, 0FFh, 0FFh
    call ?j_0000e570@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 065h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00031a7f@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 087h, 000h, 000h, 000h, 050h
    call ?canPursue@@YA_NPAVObject@@PAVWeapon@@0@Z
    db 083h, 0C4h, 004h, 084h, 0C0h, 074h, 047h, 08Bh, 0CBh
    call ?j_000346a3@@YAXXZ
    db 083h, 0F8h, 0FFh, 074h, 03Bh, 033h, 0C9h, 08Ah, 04Dh, 064h, 051h, 057h, 050h, 08Bh, 0CBh
    call ?j_0001a0e1@@YAXXZ
    db 0A0h
    dd ?Glo012F0239@@3_NA
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va010993D8
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 044h, 084h, 0C0h, 075h, 008h, 05Fh
    db 05Eh, 05Dh, 083h, 0C8h, 0FFh, 05Bh, 0C3h, 05Fh, 05Eh, 08Bh, 0CDh, 05Dh, 05Bh
    jmp ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
    db 08Bh, 04Dh, 01Ch
    call ?j_0000e570@@YAXXZ
    db 050h, 056h
    call ?j_00004c37@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 075h, 0D7h, 08Bh, 04Dh, 01Ch, 08Bh, 001h, 06Ah, 000h, 0FFh, 050h
    db 038h, 05Fh, 05Eh, 05Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Bh, 0C3h
?d_00176070@@YAXXZ ENDP
_TEXT$d00576070 ENDS
_TEXT SEGMENT

; ghidra: FUN_00576250  retail @ 0x00176250 size 522
public ?d_00176250@@YAXXZ
?d_00176250@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 0E9h, 8Bh, 4Dh, 1Ch, 8Bh, 41h, 10h, 8Bh, 98h, 04h
    db 02h, 00h, 00h, 89h, 5Ch, 24h, 08h, 0E8h, 0C0h, 0E0h, 0E8h, 0FFh, 84h, 0C0h, 74h, 1Eh
    db 8Bh, 13h, 8Bh, 0CBh, 0FFh, 92h, 04h, 02h, 00h, 00h, 6Ah, 00h, 8Bh, 0CBh, 0E8h, 0C9h
    db 48h, 0EDh, 0FFh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 4Dh
    db 1Ch, 56h, 57h, 0C6h, 45h, 62h, 00h, 8Bh, 79h, 10h, 0C7h, 44h, 24h, 18h, 0FEh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0C9h, 82h, 0E9h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 9Dh, 01h, 00h
    db 00h, 0F7h, 86h, 94h, 00h, 00h, 00h, 00h, 00h, 04h, 00h, 75h, 64h, 8Bh, 0CFh, 0E8h
    db 60h, 0A5h, 0EAh, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 4Fh, 0D8h, 0E8h, 0FFh, 84h, 0C0h, 75h, 51h
    db 56h, 8Bh, 0CBh, 0E8h, 74h, 48h, 0EDh, 0FFh, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h
    db 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h, 85h, 0C0h, 74h, 0Eh, 68h, 38h, 94h, 09h, 01h, 50h
    db 0E8h, 85h, 3Eh, 0ECh, 0FFh, 83h, 0C4h, 08h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 50h, 44h
    db 84h, 0C0h, 74h, 1Dh, 8Bh, 0CDh, 0E8h, 0EBh, 25h, 0EDh, 0FFh, 85h, 0C0h, 89h, 44h, 24h
    db 18h, 75h, 2Dh, 50h, 8Bh, 0CFh, 0E8h, 64h, 0B7h, 0EBh, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 75h
    db 0Dh, 5Fh, 5Eh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 4Ch
    db 24h, 10h, 0E8h, 6Ch, 0E3h, 0EBh, 0FFh, 83h, 0F8h, 0FFh, 89h, 44h, 24h, 14h, 75h, 0Bh
    db 5Fh, 5Eh, 5Dh, 83h, 0C8h, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 4Ch, 24h, 10h, 8Bh
    db 11h, 0FFh, 92h, 0ECh, 01h, 00h, 00h, 84h, 0C0h, 74h, 2Ah, 8Bh, 0CEh, 0E8h, 8Fh, 3Ch
    db 0EAh, 0FFh, 84h, 0C0h, 75h, 1Fh, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 8Dh, 56h
    db 38h, 52h, 56h, 8Dh, 47h, 38h, 50h, 57h, 0E8h, 0C5h, 0CCh, 0EAh, 0FFh, 84h, 0C0h, 0Fh
    db 85h, 0BBh, 00h, 00h, 00h, 8Bh, 86h, 08h, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0ADh
    db 00h, 00h, 00h, 6Ah, 00h, 56h, 57h, 8Bh, 0CBh, 0E8h, 0BEh, 84h, 0EBh, 0FFh, 84h, 0C0h
    db 0Fh, 84h, 9Ah, 00h, 00h, 00h, 8Bh, 54h, 24h, 14h, 33h, 0C9h, 8Ah, 4Dh, 64h, 51h
    db 8Bh, 4Ch, 24h, 14h, 56h, 52h, 0E8h, 26h, 3Dh, 0EAh, 0FFh, 8Bh, 0CEh, 0C6h, 45h, 63h
    db 00h, 0E8h, 02h, 0E4h, 0E8h, 0FFh, 0D9h, 5Ch, 24h, 14h, 6Ah, 00h, 8Dh, 46h, 38h, 50h
    db 56h, 8Dh, 4Fh, 38h, 51h, 57h, 8Bh, 0CBh, 0E8h, 08h, 41h, 0ECh, 0FFh, 84h, 0C0h, 74h
    db 0Eh, 0D9h, 44h, 24h, 14h, 0D8h, 0Dh, 34h, 94h, 09h, 01h, 0D9h, 5Ch, 24h, 14h, 6Ah
    db 02h, 56h, 8Bh, 0CFh, 0E8h, 0B1h, 0BCh, 0ECh, 0FFh, 84h, 0C0h, 74h, 08h, 0C7h, 44h, 24h
    db 14h, 0F0h, 23h, 74h, 49h, 8Bh, 54h, 24h, 14h, 8Bh, 74h, 24h, 10h, 52h, 8Bh, 0CEh
    db 0E8h, 92h, 28h, 0EDh, 0FFh, 8Bh, 8Eh, 0CCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 2Fh, 0E8h
    db 89h, 88h, 0EBh, 0FFh, 0D9h, 05h, 50h, 53h, 07h, 01h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Ah, 1Bh, 5Fh, 5Eh, 5Dh, 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
    db 8Bh, 4Ch, 24h, 10h, 68h, 0F0h, 23h, 74h, 49h, 0E8h, 59h, 28h, 0EDh, 0FFh, 8Bh, 44h
    db 24h, 18h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_00176250@@YAXXZ ENDP

; ghidra: FUN_005764e0  retail @ 0x001764E0 size 96
public ?d_001764e0@@YAXXZ
?d_001764e0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 0E8h, 08h, 0EAh, 0E9h, 0FFh, 8Bh, 0D8h, 8Bh, 47h, 1Ch, 8Bh
    db 48h, 10h, 8Ah, 47h, 63h, 84h, 0C0h, 8Bh, 0B1h, 04h, 02h, 00h, 00h, 74h, 3Bh, 55h
    db 8Bh, 0CEh, 0E8h, 9Ch, 0E1h, 0EBh, 0FFh, 8Bh, 0E8h, 83h, 0FDh, 0FFh, 74h, 25h, 6Ah, 00h
    db 6Ah, 01h, 8Bh, 0CEh, 0E8h, 3Fh, 0DAh, 0E8h, 0FFh, 85h, 0C0h, 74h, 16h, 33h, 0D2h, 8Ah
    db 57h, 64h, 8Bh, 0CEh, 52h, 50h, 55h, 0E8h, 0B5h, 3Bh, 0EAh, 0FFh, 0C6h, 86h, 35h, 03h
    db 00h, 00h, 01h, 5Dh, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 0C3h, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 0C3h
?d_001764e0@@YAXXZ ENDP

; ghidra: FUN_005766f0  retail @ 0x001766F0 size 657
public ?d_001766f0@@YAXXZ
?d_001766f0@@YAXXZ PROC
    db 83h, 0ECh, 24h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 1Ch, 8Bh, 4Fh, 68h, 8Bh
    db 73h, 10h, 8Bh, 86h, 04h, 02h, 00h, 00h, 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 89h
    db 44h, 24h, 18h, 0E8h, 3Bh, 8Bh, 0EAh, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 89h, 6Ch, 24h, 18h
    db 75h, 36h, 8Bh, 0CBh, 0E8h, 47h, 7Eh, 0E9h, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 75h, 23h, 8Bh
    db 74h, 24h, 14h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 04h, 02h, 00h, 00h, 55h, 8Bh, 0CEh
    db 0E8h, 07h, 44h, 0EDh, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 5Bh, 83h, 0C4h
    db 24h, 0C3h, 8Bh, 45h, 74h, 89h, 47h, 68h, 8Bh, 4Fh, 1Ch, 0E8h, 10h, 7Eh, 0E9h, 0FFh
    db 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CEh, 8Bh, 0D8h, 0E8h, 11h, 0B3h, 0EBh, 0FFh, 85h, 0C0h
    db 89h, 44h, 24h, 20h, 74h, 0CFh, 85h, 0DBh, 0C6h, 44h, 24h, 13h, 00h, 74h, 42h, 3Bh
    db 5Ch, 24h, 18h, 74h, 3Ch, 8Bh, 0CEh, 0E8h, 0BAh, 9Ah, 0ECh, 0FFh, 0D9h, 00h, 0D9h, 40h
    db 04h, 0D9h, 43h, 3Ch, 0D9h, 43h, 38h, 0D8h, 66h, 38h, 0D9h, 5Ch, 24h, 28h, 0D8h, 66h
    db 3Ch, 0D8h, 0C9h, 0D9h, 44h, 24h, 28h, 0D8h, 0CBh, 0DEh, 0C1h, 0D8h, 1Dh, 50h, 53h, 07h
    db 01h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 0DDh, 0D8h, 75h, 05h, 0C6h, 44h, 24h, 13h
    db 01h, 0F7h, 86h, 90h, 00h, 00h, 00h, 00h, 00h, 00h, 10h, 74h, 2Ah, 8Bh, 44h, 24h
    db 18h, 85h, 0C0h, 74h, 22h, 50h, 8Bh, 0CEh, 0E8h, 10h, 0D5h, 0ECh, 0FFh, 0D9h, 86h, 0BCh
    db 00h, 00h, 00h, 0DCh, 0C0h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 09h, 8Bh, 4Ch
    db 24h, 14h, 0E8h, 0EAh, 0FDh, 0E8h, 0FFh, 8Bh, 4Ch, 24h, 20h, 0E8h, 8Ch, 2Fh, 0E9h, 0FFh
    db 8Ah, 4Fh, 6Ch, 84h, 0C9h, 74h, 72h, 83h, 0F8h, 04h, 0Fh, 84h, 92h, 00h, 00h, 00h
    db 85h, 0C0h, 75h, 5Ah, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 0Fh, 84h, 82h, 00h, 00h, 00h
    db 3Bh, 5Ch, 24h, 18h, 75h, 06h, 0C6h, 47h, 6Ch, 00h, 0EBh, 76h, 8Bh, 96h, 0BCh, 00h
    db 00h, 00h, 53h, 8Bh, 0CEh, 89h, 54h, 24h, 20h, 0E8h, 0AFh, 0D4h, 0ECh, 0FFh, 0D9h, 44h
    db 24h, 1Ch, 0D8h, 4Ch, 24h, 1Ch, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0D7h, 8Bh
    db 4Ch, 24h, 14h, 55h, 0E8h, 90h, 0BDh, 0E9h, 0FFh, 8Bh, 0CEh, 0E8h, 0ACh, 0D5h, 0EAh, 0FFh
    db 8Bh, 4Fh, 68h, 8Bh, 06h, 51h, 53h, 8Bh, 0CEh, 0FFh, 50h, 2Ch, 0EBh, 34h, 83h, 0F8h
    db 05h, 75h, 2Fh, 0C6h, 47h, 6Ch, 00h, 0EBh, 29h, 85h, 0C0h, 75h, 25h, 3Bh, 0DDh, 74h
    db 21h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 19h, 6Ah, 01h, 6Ah, 0Dh, 8Bh, 0CEh, 0C6h
    db 47h, 6Ch, 01h, 0E8h, 56h, 0C5h, 0EBh, 0FFh, 6Ah, 00h, 53h, 8Bh, 0CEh, 0E8h, 6Bh, 2Dh
    db 0ECh, 0FFh, 33h, 0D2h, 8Bh, 0C2h, 0Dh, 00h, 00h, 00h, 10h, 89h, 54h, 24h, 2Ch, 89h
    db 44h, 24h, 28h, 52h, 8Dh, 44h, 24h, 2Ch, 50h, 8Bh, 0CEh, 89h, 54h, 24h, 38h, 0E8h
    db 23h, 9Fh, 0EBh, 0FFh, 0F7h, 85h, 94h, 00h, 00h, 00h, 00h, 00h, 04h, 00h, 0Fh, 85h
    db 71h, 0FEh, 0FFh, 0FFh, 8Bh, 0CEh, 0E8h, 49h, 9Fh, 0EAh, 0FFh, 50h, 8Bh, 0CDh, 0E8h, 38h
    db 0D2h, 0E8h, 0FFh, 84h, 0C0h, 0Fh, 85h, 5Ah, 0FEh, 0FFh, 0FFh, 8Bh, 5Ch, 24h, 14h, 55h
    db 8Bh, 0CBh, 0E8h, 55h, 42h, 0EDh, 0FFh, 8Bh, 83h, 40h, 01h, 00h, 00h, 85h, 0C0h, 75h
    db 11h, 8Bh, 4Ch, 24h, 20h, 6Ah, 00h, 55h, 56h, 0E8h, 4Eh, 7Fh, 0EBh, 0FFh, 84h, 0C0h
    db 75h, 5Ah, 0A0h, 39h, 02h, 2Fh, 01h, 84h, 0C0h, 74h, 17h, 0A1h, 0FCh, 0D4h, 2Eh, 01h
    db 85h, 0C0h, 74h, 0Eh, 68h, 0F0h, 94h, 09h, 01h, 50h, 0E8h, 4Bh, 38h, 0ECh, 0FFh, 83h
    db 0C4h, 08h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 44h, 84h, 0C0h, 0Fh, 84h, 04h, 0FEh, 0FFh
    db 0FFh, 8Bh, 0CFh, 0E8h, 0AEh, 1Fh, 0EDh, 0FFh, 85h, 0C0h, 74h, 2Bh, 83h, 0F8h, 0FFh, 75h
    db 1Bh, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 74h, 13h, 8Bh, 7Fh, 1Ch, 8Bh, 07h, 56h, 8Bh
    db 0CFh, 0FFh, 50h, 38h, 56h, 8Bh, 0CBh, 0E8h, 7Dh, 0BCh, 0E9h, 0FFh, 5Fh, 5Eh, 5Dh, 83h
    db 0C8h, 0FFh, 5Bh, 83h, 0C4h, 24h, 0C3h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 83h, 0C4h, 24h
    db 0C3h
?d_001766f0@@YAXXZ ENDP

; ghidra: FUN_00576a50  retail @ 0x00176A50 size 1041
_TEXT ENDS
_TEXT$d00576a50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00576A50 size 1041
public ?d_00176a50@@YAXXZ
?d_00176a50@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01005BDE
    db 050h, 0A0h
    dd ?Glo012F0239@@3_NA
    db 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 01Ch, 084h, 0C0h, 055h, 08Bh, 0E9h, 074h
    db 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va0109954C
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 04Dh, 01Ch, 08Bh, 041h, 010h, 08Bh, 080h, 004h, 002h, 000h, 000h, 08Ah
    db 090h, 026h, 003h, 000h, 000h, 084h, 0D2h, 0C6h, 044h, 024h, 007h, 000h, 089h, 044h, 024h, 008h
    db 074h, 012h, 032h, 0C0h, 05Dh, 08Bh, 04Ch, 024h, 01Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 028h, 0C3h, 08Ah, 055h, 04Dh, 084h, 0D2h, 074h, 012h, 0B0h, 001h, 05Dh, 08Bh, 04Ch
    db 024h, 01Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 028h, 0C3h, 08Bh, 090h, 040h
    db 001h, 000h, 000h, 053h, 085h, 0D2h, 08Bh, 015h
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 057h, 00Fh, 085h, 0C3h, 000h, 000h, 000h, 08Ah, 098h, 01Eh, 003h, 000h, 000h, 084h, 0DBh, 00Fh
    db 085h, 0B5h, 000h, 000h, 000h, 0C6h, 044h, 024h, 00Fh, 001h, 08Bh, 042h, 03Ch, 056h, 089h, 045h
    db 050h
    call ?j_0000e570@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 0C6h, 001h, 000h, 000h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 08Bh, 04Dh
    db 01Ch, 08Bh, 059h, 010h, 075h, 017h
    call ?j_0000e570@@YAXXZ
    db 083h, 0C0h, 038h, 08Dh, 04Dh, 054h, 08Dh, 053h, 038h
    call ?isSamePosition@@YA_NPBUCoord3D@@00@Z
    db 084h, 0C0h, 075h, 062h, 06Ah, 000h, 08Bh, 0CBh
    call ?j_00031a7f@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 090h, 001h, 000h, 000h, 08Bh, 04Dh, 01Ch
    call ?j_0000e570@@YAXXZ
    db 08Bh, 0F8h, 08Dh, 047h, 038h, 08Bh, 010h, 08Dh, 075h, 054h, 08Bh, 0CEh, 089h, 011h, 08Bh, 050h
    db 004h, 089h, 051h, 004h, 08Bh, 040h, 008h, 06Ah, 002h, 089h, 041h, 008h, 057h, 08Bh, 0CBh
    call ?j_000420aa@@YAXXZ
    db 084h, 0C0h, 074h, 059h, 08Bh, 016h, 08Dh, 045h, 024h, 08Bh, 0C8h, 089h, 011h, 08Bh, 056h, 004h
    db 089h, 051h, 004h, 08Bh, 056h, 008h, 06Ah, 000h, 089h, 051h, 008h, 08Bh, 04Ch, 024h, 018h, 050h
    call ?j_0003bcff@@YAXXZ
    db 05Eh, 05Fh, 05Bh, 0B0h, 001h, 05Dh, 08Bh, 04Ch, 024h, 01Ch, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 083h, 0C4h, 028h, 0C3h, 08Bh, 042h, 03Ch, 02Bh, 045h, 050h, 083h, 0F8h, 005h, 00Fh, 083h
    db 041h, 0FFh, 0FFh, 0FFh, 05Fh, 05Bh, 0B0h, 001h, 05Dh, 08Bh, 04Ch, 024h, 01Ch, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 083h, 0C4h, 028h, 0C3h, 0D9h, 043h, 03Ch, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 0D9h, 043h, 038h, 08Bh, 048h, 014h, 0D8h, 026h, 089h, 04Ch, 024h, 01Ch, 08Dh, 04Ch, 024h, 020h
    db 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 020h, 0D8h, 066h, 004h, 0D9h
    db 05Ch, 024h, 024h
    call ?j_0002fe0f@@YAXXZ
    db 08Bh, 044h, 024h, 01Ch, 0D9h, 080h, 090h, 000h, 000h, 000h, 0D8h, 080h, 094h, 000h, 000h, 000h
    db 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 084h, 0BAh, 000h, 000h, 000h, 068h, 095h, 000h
    db 000h, 000h, 08Bh, 0CFh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0A6h, 000h, 000h, 000h, 057h, 053h
    call ?j_0002056d@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 08Bh, 0CFh, 00Fh, 084h, 0A7h, 000h, 000h, 000h
    call ?j_00040246@@YAXXZ
    db 0D9h, 087h, 0BCh, 000h, 000h, 000h, 08Bh, 010h, 0DCh, 0C0h, 08Bh, 048h, 004h, 089h, 054h, 024h
    db 020h, 0D8h, 005h
    dd __real@42700000
    db 08Bh, 050h, 008h, 051h, 089h, 04Ch, 024h, 028h, 08Dh, 04Ch, 024h, 024h, 0D9h, 01Ch, 024h, 089h
    db 054h, 024h, 02Ch
    call ?j_0000e1c4@@YAXXZ
    db 08Bh, 00Eh, 08Bh, 056h, 004h, 08Dh, 07Dh, 024h, 08Bh, 0C7h, 089h, 008h, 08Bh, 04Eh, 008h, 089h
    db 050h, 004h, 08Dh, 054h, 024h, 020h, 089h, 048h, 008h, 052h, 08Bh, 0CFh
    call ?j_0002f66c@@YAXXZ
    db 0A0h
    dd ?Glo012F0239@@3_NA
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va01099514
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 04Ch, 024h, 014h, 06Ah, 000h, 057h, 0C6h, 045h, 04Ch, 000h
    call ?j_0003bcff@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 08Ah, 091h, 01Eh, 003h, 000h, 000h, 088h, 055h, 04Dh, 05Eh, 05Fh, 05Bh
    db 032h, 0C0h, 05Dh, 08Bh, 04Ch, 024h, 01Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 028h, 0C3h, 033h, 0C0h, 06Ah, 05Ch, 089h, 044h, 024h, 01Ch, 089h, 044h, 024h, 020h
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 074h, 08Bh, 0CBh
    call ?j_0003a391@@YAXXZ
    db 083h, 0F8h, 001h, 074h, 068h, 0F6h, 005h
    dd ?g_Va012EF304@@3IA
    db 001h, 075h, 02Ch, 083h, 00Dh
    dd ?g_Va012EF304@@3IA
    db 001h, 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 068h
    dd g_Va0108F924
    db 0C7h, 044h, 024h, 038h, 000h, 000h, 000h, 000h
    call ?j_0003add7@@YAXXZ
    db 0A3h
    dd g_Va012EF300
    db 0C7h, 044h, 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h
    dd g_Va012EF300
    db 050h, 08Bh, 0CFh
    call ?j_0002ae23@@YAXXZ
    db 057h, 08Bh, 0D8h
    call ?j_0002fc7a@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0DBh, 089h, 044h, 024h, 01Ch, 074h, 017h, 08Bh, 0CBh
    call ?j_00048112@@YAXXZ
    db 084h, 0C0h, 075h, 00Ch, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 08Bh, 05Ch, 024h, 018h
    db 085h, 0DBh, 0C6h, 044h, 024h, 018h, 000h, 074h, 03Ah, 08Bh, 044h, 024h, 01Ch, 085h, 0C0h, 074h
    db 032h, 08Dh, 05Dh, 024h, 053h, 08Bh, 0C8h
    call ?j_0003bff7@@YAXXZ
    db 084h, 0C0h, 074h, 023h, 08Bh, 00Bh, 08Bh, 053h, 004h, 08Bh, 043h, 008h, 089h, 04Ch, 024h, 020h
    db 056h, 08Dh, 04Ch, 024h, 024h, 089h, 054h, 024h, 028h, 089h, 044h, 024h, 02Ch
    call ?j_000126b6@@YAXXZ
    db 0C6h, 044h, 024h, 018h, 001h, 08Dh, 04Ch, 024h, 020h
    call ?j_0002bd82@@YAXXZ
    db 08Bh, 08Fh, 0BCh, 000h, 000h, 000h, 051h, 08Dh, 04Ch, 024h, 024h
    call ?j_0000e1c4@@YAXXZ
    db 08Bh, 006h, 08Bh, 04Eh, 004h, 08Dh, 07Dh, 024h, 08Bh, 0D7h, 089h, 002h, 08Bh, 046h, 008h, 089h
    db 04Ah, 004h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CFh, 089h, 042h, 008h
    call ?j_0002f66c@@YAXXZ
    db 08Ah, 044h, 024h, 018h, 084h, 0C0h, 074h, 029h, 033h, 0F6h, 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 04Ah, 00Ch, 06Ah, 000h, 057h
    call ?j_0003ce25@@YAXXZ
    db 084h, 0C0h, 075h, 012h, 08Dh, 044h, 024h, 020h, 050h, 08Bh, 0CFh
    call ?j_000233ee@@YAXXZ
    db 046h, 083h, 0FEh, 00Ah, 07Ch, 0D9h, 08Bh, 04Ch, 024h, 018h, 051h, 08Bh, 04Ch, 024h, 018h, 057h
    call ?j_0003e423@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 08Ch, 0FEh, 0FFh, 0FFh, 08Bh, 054h, 024h, 014h, 08Ah, 082h, 01Eh, 003h
    db 000h, 000h, 08Bh, 04Ch, 024h, 02Ch, 05Eh, 05Fh, 088h, 045h, 04Dh, 05Bh, 0B0h, 001h, 05Dh, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 028h, 0C3h
?d_00176a50@@YAXXZ ENDP
_TEXT$d00576a50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00576f70  retail @ 0x00176F70 size 747
_TEXT ENDS
_TEXT$d00576f70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00576F70 size 747
public ?d_00176f70@@YAXXZ
?d_00176f70@@YAXXZ PROC
    db 083h, 0ECh, 010h, 055h, 08Bh, 0E9h, 08Bh, 04Dh, 01Ch, 056h, 08Bh, 071h, 010h, 089h, 06Ch, 024h
    db 008h
    call ?j_0000432c@@YAXXZ
    db 084h, 0C0h, 074h, 00Bh, 05Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h, 08Bh
    db 04Dh, 01Ch, 057h
    call ?j_0000e570@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 029h, 08Bh, 0CEh
    call ?j_00020824@@YAXXZ
    db 050h, 08Bh, 0CFh
    call ?j_00003b1b@@YAXXZ
    db 084h, 0C0h, 074h, 016h, 08Bh, 04Dh, 01Ch, 08Bh, 001h, 06Ah, 000h, 0FFh, 050h, 038h, 05Fh, 05Eh
    db 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h, 0F6h, 086h, 098h, 000h, 000h, 000h
    db 008h, 00Fh, 085h, 025h, 002h, 000h, 000h, 08Bh, 08Eh, 004h, 002h, 000h, 000h, 08Ah, 081h, 03Ah
    db 003h, 000h, 000h, 084h, 0C0h, 00Fh, 085h, 011h, 002h, 000h, 000h, 0A0h
    dd ?Glo012F0239@@3_NA
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va010995CC
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0FFh, 0C6h, 045h, 04Ch, 000h, 0C7h, 045h, 050h, 000h, 000h, 000h, 000h
    db 074h, 0A4h, 06Ah, 002h, 057h, 08Bh, 0CEh
    call ?j_000420aa@@YAXXZ
    db 084h, 0C0h, 074h, 021h, 08Bh, 0CEh
    call ?j_00016199@@YAXXZ
    db 084h, 0C0h, 074h, 016h, 08Bh, 04Dh, 01Ch, 08Bh, 011h, 068h, 0E9h, 000h, 000h, 000h, 0FFh, 052h
    db 020h, 05Fh, 05Eh, 033h, 0C0h, 05Dh, 083h, 0C4h, 010h, 0C3h, 08Bh, 08Fh, 008h, 002h, 000h, 000h
    db 085h, 0C9h, 074h, 00Dh
    call ?j_00006eec@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 05Eh, 0FFh, 0FFh, 0FFh, 06Ah, 000h, 08Bh, 0CEh
    call ?j_00031a7f@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 04Dh, 0FFh, 0FFh, 0FFh, 06Ah, 000h, 057h, 056h, 08Bh, 0C8h
    call ?j_0002e85c@@YAXXZ
    db 084h, 0C0h, 074h, 00Ah, 05Fh, 05Eh, 083h, 0C8h, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h, 053h, 08Dh
    db 05Fh, 038h, 083h, 0C5h, 054h, 08Bh, 0C3h, 08Bh, 010h, 08Bh, 0CDh, 089h, 011h, 08Bh, 050h, 004h
    db 089h, 051h, 004h, 08Bh, 040h, 008h, 06Ah, 002h, 089h, 041h, 008h, 057h, 08Bh, 0CEh
    call ?j_000420aa@@YAXXZ
    db 084h, 0C0h, 075h, 050h, 0D9h, 046h, 03Ch, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 0D9h, 046h, 038h, 08Bh, 079h, 014h, 0D8h, 065h, 000h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h
    db 01Ch, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 014h, 0D8h, 065h, 004h, 0D9h, 05Ch, 024h, 018h
    call ?j_0002fe0f@@YAXXZ
    db 0D9h, 087h, 094h, 000h, 000h, 000h, 0D8h, 087h, 090h, 000h, 000h, 000h, 0DEh, 0D9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 041h, 075h, 00Dh, 05Bh, 05Fh, 05Eh, 0B8h, 0FFh, 0FFh, 0FFh, 0FFh, 05Dh, 083h, 0C4h
    db 010h, 0C3h, 06Ah, 025h, 08Bh, 0CEh
    call ?j_000016a4@@YAXXZ
    db 084h, 0C0h, 074h, 017h, 08Bh, 086h, 014h, 002h, 000h, 000h, 085h, 0C0h, 074h, 00Dh, 05Bh, 05Fh
    db 05Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h, 08Bh, 08Eh, 004h, 002h, 000h
    db 000h
    call ?j_000065e1@@YAXXZ
    db 08Bh, 003h, 08Bh, 0D5h, 089h, 002h, 08Bh, 04Bh, 004h, 089h, 04Ah, 004h, 08Bh, 043h, 008h, 089h
    db 042h, 008h, 0D9h, 046h, 03Ch, 0D9h, 046h, 038h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 0D8h, 065h, 000h, 08Bh, 071h, 014h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h, 01Ch, 000h, 000h
    db 000h, 000h, 0D9h, 05Ch, 024h, 014h, 0D8h, 065h, 004h, 0D9h, 05Ch, 024h, 018h
    call ?j_0002fe0f@@YAXXZ
    db 0D9h, 086h, 094h, 000h, 000h, 000h, 0D8h, 086h, 090h, 000h, 000h, 000h, 0DEh, 0D9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 041h, 00Fh, 084h, 06Bh, 0FFh, 0FFh, 0FFh, 0A0h
    dd ?Glo012F0239@@3_NA
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va010995A8
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 074h, 024h, 010h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 044h, 084h, 0C0h
    db 075h, 00Bh, 05Bh, 05Fh, 05Eh, 083h, 0C8h, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h, 08Bh, 0CEh
    call ?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ
    db 08Bh, 0F8h, 0A0h
    dd ?Glo012F0239@@3_NA
    db 084h, 0C0h, 074h, 017h, 0A1h
    dd ?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A
    db 085h, 0C0h, 074h, 00Eh, 068h
    dd g_Va01099570
    db 050h
    call ?j_0003a17a@@YAXXZ
    db 083h, 0C4h, 008h, 05Bh, 08Bh, 0C7h, 05Fh, 0C6h, 046h, 04Ch, 001h, 05Eh, 05Dh, 083h, 0C4h, 010h
    db 0C3h, 057h, 056h
    call ?j_00004c37@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 00Fh, 084h, 0A6h, 0FDh, 0FFh, 0FFh, 08Bh, 086h, 004h, 002h, 000h
    db 000h, 08Ah, 088h, 03Ah, 003h, 000h, 000h, 084h, 0C9h, 00Fh, 084h, 05Eh, 0FEh, 0FFh, 0FFh, 06Ah
    db 000h, 08Bh, 0CEh
    call ?j_00031a7f@@YAXXZ
    db 085h, 0C0h, 074h, 013h, 06Ah, 000h, 057h, 056h, 08Bh, 0C8h
    call ?j_0002e85c@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 03Eh, 0FEh, 0FFh, 0FFh, 08Bh, 04Dh, 01Ch, 08Bh, 011h, 06Ah, 000h, 0FFh
    db 052h, 038h, 05Fh, 05Eh, 0B8h, 0FEh, 0FFh, 0FFh, 0FFh, 05Dh, 083h, 0C4h, 010h, 0C3h
?d_00176f70@@YAXXZ ENDP
_TEXT$d00576f70 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
