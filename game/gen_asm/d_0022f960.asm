.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??_7?$LatchRestore@_N@@6B@:BYTE
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Factory0040A260@@3PAVThingFactory@@A:BYTE
EXTERN ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z:NEAR
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?TheBfmeGenAE@@3PAVBfmeGenAE@@A:BYTE
EXTERN ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z:NEAR
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?bfmeTwo941F@BfmeThing941F@@QAEXPAX@Z:NEAR
EXTERN ?g_Va012EFAD8@@3IA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeAngleTwoPi@@3MA:BYTE
EXTERN ?j_00001bae@@YAXXZ:NEAR
EXTERN ?j_00005835@@YAXXZ:NEAR
EXTERN ?j_00006c12@@YAXXZ:NEAR
EXTERN ?j_000095ed@@YAXXZ:NEAR
EXTERN ?j_0000A47A@@YAXXZ:NEAR
EXTERN ?j_0000a475@@YAXXZ:NEAR
EXTERN ?j_0000e68d@@YAXXZ:NEAR
EXTERN ?j_00012913@@YAXXZ:NEAR
EXTERN ?j_0001697d@@YAXXZ:NEAR
EXTERN ?j_00017355@@YAXXZ:NEAR
EXTERN ?j_00018223@@YAXXZ:NEAR
EXTERN ?j_0001b10d@@YAXXZ:NEAR
EXTERN ?j_0001d0de@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_000202ed@@YAXXZ:NEAR
EXTERN ?j_000225f7@@YAXXZ:NEAR
EXTERN ?j_0002ae23@@YAXXZ:NEAR
EXTERN ?j_0002de0c@@YAXXZ:NEAR
EXTERN ?j_0002f3dd@@YAXXZ:NEAR
EXTERN ?j_00031b3d@@YAXXZ:NEAR
EXTERN ?j_000348ec@@YAXXZ:NEAR
EXTERN ?j_00035e0e@@YAXXZ:NEAR
EXTERN ?j_00038d61@@YAXXZ:NEAR
EXTERN ?j_000392ca@@YAXXZ:NEAR
EXTERN ?j_0003a1a7@@YAXXZ:NEAR
EXTERN ?j_0003a279@@YAXXZ:NEAR
EXTERN ?j_0003a391@@YAXXZ:NEAR
EXTERN ?j_0003add7@@YAXXZ:NEAR
EXTERN ?j_0003b359@@YAXXZ:NEAR
EXTERN ?j_0003ee55@@YAXXZ:NEAR
EXTERN ?j_0004494a@@YAXXZ:NEAR
EXTERN ?j_00045a39@@YAXXZ:NEAR
EXTERN ?j_0004895a@@YAXXZ:NEAR
EXTERN ?j_0004966b@@YAXXZ:NEAR
EXTERN g_Va0100DA80:NEAR
EXTERN g_Va0100DB7E:NEAR
EXTERN g_Va010906AC:BYTE
EXTERN g_Va010AE860:BYTE
EXTERN g_Va010AEB50:BYTE
EXTERN g_Va012EFAD4:BYTE
EXTERN g_Va012EFADC:BYTE
EXTERN g_Va012EFAE0:BYTE
EXTERN g_Va012EFAE4:BYTE
EXTERN g_Va012EFAE8:BYTE
EXTERN g_Va012EFAEC:BYTE
EXTERN g_Va012EFAF0:BYTE
EXTERN g_Va012EFAF4:BYTE
EXTERN g_Va012EFAF8:BYTE
EXTERN g_Va012EFAFC:BYTE
EXTERN g_Va012EFB00:BYTE
EXTERN g_Va012EFB0C:BYTE
_TEXT SEGMENT

; ghidra: FUN_0062f960  retail @ 0x0022F960 size 625
public ?d_0022f960@@YAXXZ
?d_0022f960@@YAXXZ PROC
    db 83h, 0ECh, 38h, 56h, 8Bh, 0F1h, 8Bh, 86h, 14h, 06h, 00h, 00h, 57h, 33h, 0FFh, 89h
    db 44h, 24h, 24h, 39h, 0BEh, 0F4h, 07h, 00h, 00h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 28h, 00h, 00h, 80h, 0BFh, 89h, 7Ch, 24h, 2Ch, 89h, 7Ch, 24h
    db 20h, 0Fh, 8Eh, 34h, 02h, 00h, 00h, 53h, 55h, 8Dh, 9Eh, 18h, 06h, 00h, 00h, 90h
    db 0D9h, 44h, 24h, 2Ch, 8Bh, 86h, 10h, 06h, 00h, 00h, 0D8h, 63h, 0FCh, 8Dh, 4Fh, 26h
    db 0C1h, 0E1h, 04h, 8Dh, 50h, 0FFh, 0D8h, 64h, 24h, 14h, 03h, 0CEh, 0D9h, 54h, 24h, 24h
    db 0D9h, 44h, 24h, 14h, 3Bh, 0FAh, 7Dh, 42h, 8Bh, 0C1h, 8Bh, 28h, 89h, 6Ch, 24h, 30h
    db 0D9h, 44h, 24h, 30h, 0D8h, 61h, 0F0h, 8Bh, 68h, 04h, 89h, 6Ch, 24h, 34h, 8Bh, 40h
    db 08h, 0D9h, 5Ch, 24h, 30h, 89h, 44h, 24h, 38h, 0D9h, 44h, 24h, 34h, 0D8h, 61h, 0F4h
    db 0D9h, 54h, 24h, 34h, 0D8h, 4Ch, 24h, 34h, 0D9h, 44h, 24h, 30h, 0D8h, 4Ch, 24h, 30h
    db 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 0F3h, 4Fh
    db 0C3h, 47h, 0D9h, 44h, 24h, 10h, 0D8h, 0DAh, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 12h, 0D9h
    db 0C9h, 47h, 0D8h, 64h, 24h, 10h, 83h, 0C1h, 10h, 0D9h, 0C9h, 0D8h, 44h, 24h, 10h, 0EBh
    db 93h, 0D9h, 54h, 24h, 14h, 8Bh, 4Ch, 24h, 34h, 0D9h, 0C9h, 89h, 4Ch, 24h, 40h, 0D9h
    db 54h, 24h, 24h, 0C7h, 44h, 24h, 44h, 00h, 00h, 00h, 00h, 0DDh, 0D9h, 0D9h, 44h, 24h
    db 30h, 0D9h, 44h, 24h, 34h, 0D8h, 4Ch, 24h, 34h, 0D9h, 44h, 24h, 30h, 0D8h, 4Ch, 24h
    db 30h, 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 18h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h
    db 44h, 24h, 18h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 2Eh, 0DDh, 0D8h, 0D9h, 05h
    db 34h, 53h, 07h, 01h, 0D8h, 74h, 24h, 18h, 0D9h, 54h, 24h, 18h, 0D8h, 4Ch, 24h, 30h
    db 0D9h, 44h, 24h, 34h, 0D8h, 4Ch, 24h, 18h, 0D9h, 5Ch, 24h, 40h, 0D9h, 44h, 24h, 18h
    db 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 44h, 0D8h, 0C9h, 8Dh, 47h, 25h, 0D9h
    db 44h, 24h, 40h, 0C1h, 0E0h, 04h, 0D8h, 0CAh, 03h, 0C6h, 0D9h, 5Ch, 24h, 40h, 0D9h, 44h
    db 24h, 44h, 0D8h, 0CAh, 0D9h, 5Ch, 24h, 44h, 0D8h, 00h, 0D9h, 5Ch, 24h, 3Ch, 8Bh, 54h
    db 24h, 3Ch, 0DDh, 0D8h, 0D9h, 44h, 24h, 40h, 0D8h, 40h, 04h, 0D9h, 5Ch, 24h, 40h, 0D9h
    db 44h, 24h, 44h, 0D8h, 40h, 08h, 8Bh, 44h, 24h, 40h, 89h, 53h, 04h, 89h, 43h, 08h
    db 0D9h, 5Ch, 24h, 44h, 8Bh, 4Ch, 24h, 44h, 8Bh, 0D7h, 0C1h, 0E2h, 04h, 8Dh, 04h, 32h
    db 89h, 4Bh, 0Ch, 8Bh, 96h, 10h, 06h, 00h, 00h, 8Bh, 88h, 5Ch, 02h, 00h, 00h, 4Ah
    db 3Bh, 0FAh, 89h, 4Ch, 24h, 1Ch, 0D9h, 44h, 24h, 1Ch, 7Dh, 08h, 0DDh, 0D8h, 0D9h, 80h
    db 6Ch, 02h, 00h, 00h, 0D8h, 64h, 24h, 1Ch, 51h, 0D9h, 1Ch, 24h, 0E8h, 0EBh, 9Dh, 0DDh
    db 0FFh, 0D9h, 44h, 24h, 28h, 0D8h, 74h, 24h, 14h, 0DEh, 0C9h, 0D8h, 44h, 24h, 20h, 0D9h
    db 1Ch, 24h, 0E8h, 0D5h, 9Dh, 0DDh, 0FFh, 8Bh, 03h, 0D9h, 5Ch, 24h, 28h, 0D9h, 44h, 24h
    db 28h, 89h, 44h, 24h, 24h, 0D8h, 64h, 24h, 24h, 0D9h, 1Ch, 24h, 0E8h, 0BBh, 9Dh, 0DDh
    db 0FFh, 0D8h, 15h, 28h, 0E2h, 0Ah, 01h, 83h, 0C4h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 10h, 0DDh, 0D8h, 0D9h, 44h, 24h, 20h, 0D8h, 05h, 28h, 0E2h, 0Ah, 01h, 0D9h, 1Bh, 0EBh
    db 21h, 0D8h, 1Dh, 24h, 0E2h, 0Ah, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Eh, 0D9h, 44h
    db 24h, 20h, 0D8h, 25h, 28h, 0E2h, 0Ah, 01h, 0D9h, 1Bh, 0EBh, 06h, 8Bh, 4Ch, 24h, 24h
    db 89h, 0Bh, 8Bh, 13h, 52h, 0E8h, 72h, 9Dh, 0DDh, 0FFh, 0D9h, 1Bh, 8Bh, 44h, 24h, 2Ch
    db 8Bh, 8Eh, 0F4h, 07h, 00h, 00h, 83h, 0C4h, 04h, 40h, 83h, 0C3h, 18h, 3Bh, 0C1h, 89h
    db 44h, 24h, 28h, 0Fh, 8Ch, 0D7h, 0FDh, 0FFh, 0FFh, 5Dh, 5Bh, 5Fh, 5Eh, 83h, 0C4h, 38h
    db 0C3h
?d_0022f960@@YAXXZ ENDP

; ghidra: FUN_0062ffa0  retail @ 0x0022FFA0 size 124
public ?d_0022ffa0@@YAXXZ
?d_0022ffa0@@YAXXZ PROC
    db 8Bh, 91h, 10h, 06h, 00h, 00h, 83h, 0FAh, 3Ch, 56h, 75h, 07h, 0BAh, 3Bh, 00h, 00h
    db 00h, 0EBh, 0Dh, 85h, 0D2h, 8Dh, 42h, 01h, 89h, 81h, 10h, 06h, 00h, 00h, 7Eh, 32h
    db 8Dh, 42h, 25h, 0C1h, 0E0h, 04h, 53h, 03h, 0C1h, 8Bh, 0F2h, 57h, 8Dh, 64h, 24h, 00h
    db 4Eh, 8Dh, 50h, 0F0h, 8Bh, 0FAh, 8Bh, 1Fh, 89h, 18h, 8Bh, 5Fh, 04h, 89h, 58h, 04h
    db 8Bh, 5Fh, 08h, 8Bh, 7Fh, 0Ch, 89h, 58h, 08h, 89h, 78h, 0Ch, 8Bh, 0C2h, 75h, 0E0h
    db 5Fh, 5Bh, 8Bh, 44h, 24h, 08h, 8Bh, 30h, 8Dh, 91h, 50h, 02h, 00h, 00h, 89h, 32h
    db 8Bh, 70h, 04h, 89h, 72h, 04h, 8Bh, 40h, 08h, 89h, 42h, 08h, 8Bh, 51h, 08h, 8Bh
    db 42h, 44h, 89h, 81h, 5Ch, 02h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_0022ffa0@@YAXXZ ENDP

; ghidra: FUN_00630120  retail @ 0x00230120 size 79
public ?d_00230120@@YAXXZ
?d_00230120@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 56h, 74h, 26h, 8Dh, 04h, 40h, 0C1h, 0E0h, 03h, 3Dh
    db 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 0F4h, 1Dh, 65h, 00h, 83h, 0C4h, 04h, 8Bh
    db 0F0h, 0EBh, 0Eh, 0E8h, 0F8h, 0E3h, 5Fh, 00h, 83h, 0C4h, 04h, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 0Ch, 8Dh, 44h, 24h, 08h, 50h, 56h, 51h
    db 52h, 0E8h, 0E7h, 87h, 0DFh, 0FFh, 83h, 0C4h, 10h, 8Bh, 0C6h, 5Eh, 0C2h, 0Ch, 00h
?d_00230120@@YAXXZ ENDP

; ghidra: FUN_006301a0  retail @ 0x002301A0 size 36
public ?d_002301a0@@YAXXZ
?d_002301a0@@YAXXZ PROC
    db 8Bh, 89h, 2Ch, 01h, 00h, 00h, 8Bh, 44h, 24h, 08h, 0C1h, 0E0h, 04h, 8Bh, 54h, 01h
    db 04h, 8Dh, 4Ch, 01h, 04h, 8Bh, 44h, 24h, 04h, 89h, 10h, 8Bh, 49h, 04h, 89h, 48h
    db 04h, 0C2h, 08h, 00h
?d_002301a0@@YAXXZ ENDP

; ghidra: FUN_006302a0  retail @ 0x002302A0 size 49
public ?d_002302a0@@YAXXZ
?d_002302a0@@YAXXZ PROC
    db 51h, 56h, 8Dh, 0B1h, 20h, 01h, 00h, 00h, 8Dh, 44h, 24h, 0Ch, 50h, 8Dh, 4Ch, 24h
    db 08h, 51h, 8Bh, 0CEh, 0E8h, 47h, 0EDh, 0DEh, 0FFh, 8Bh, 0Eh, 8Bh, 44h, 24h, 04h, 3Bh
    db 0C1h, 5Eh, 74h, 07h, 8Bh, 40h, 14h, 59h, 0C2h, 04h, 00h, 33h, 0C0h, 59h, 0C2h, 04h
    db 00h
?d_002302a0@@YAXXZ ENDP

; ghidra: FUN_006302e0  retail @ 0x002302E0 size 89
public ?d_002302e0@@YAXXZ
?d_002302e0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 30h, 02h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h
    db 0E8h, 5Eh, 0EFh, 0DEh, 0FFh, 85h, 0C0h, 75h, 08h, 89h, 86h, 30h, 02h, 00h, 00h, 5Eh
    db 0C3h, 8Dh, 48h, 38h, 57h, 8Bh, 39h, 8Dh, 96h, 38h, 02h, 00h, 00h, 89h, 3Ah, 8Bh
    db 79h, 04h, 89h, 7Ah, 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 8Dh, 88h, 0ACh, 00h, 00h
    db 00h, 0C7h, 86h, 44h, 02h, 00h, 00h, 00h, 00h, 88h, 41h, 0E8h, 0D0h, 0DCh, 64h, 00h
    db 0D9h, 9Eh, 48h, 02h, 00h, 00h, 5Fh, 5Eh, 0C3h
?d_002302e0@@YAXXZ ENDP

; ghidra: FUN_00630790  retail @ 0x00230790 size 13
public ?d_00230790@@YAXXZ
?d_00230790@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 81h, 0E8h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00230790@@YAXXZ ENDP

; ghidra: FUN_006307d0  retail @ 0x002307D0 size 7
public ?d_002307d0@@YAXXZ
?d_002307d0@@YAXXZ PROC
    db 8Ah, 81h, 1Ah, 01h, 00h, 00h, 0C3h
?d_002307d0@@YAXXZ ENDP

; ghidra: FUN_00630820  retail @ 0x00230820 size 5
public ?d_00230820@@YAXXZ
?d_00230820@@YAXXZ PROC
    db 0C6h, 41h, 04h, 01h, 0C3h
?d_00230820@@YAXXZ ENDP

; ghidra: FUN_00630830  retail @ 0x00230830 size 7
public ?d_00230830@@YAXXZ
?d_00230830@@YAXXZ PROC
    db 8Dh, 81h, 1Ch, 0FFh, 0FFh, 0FFh, 0C3h
?d_00230830@@YAXXZ ENDP

; ghidra: FUN_00630840  retail @ 0x00230840 size 13
public ?d_00230840@@YAXXZ
?d_00230840@@YAXXZ PROC
    db 8Ah, 44h, 24h, 04h, 88h, 81h, 21h, 01h, 00h, 00h, 0C2h, 04h, 00h
?d_00230840@@YAXXZ ENDP

; ghidra: FUN_00630ae0  retail @ 0x00230AE0 size 212
public ?d_00230ae0@@YAXXZ
?d_00230ae0@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 08h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 0Ch, 00h, 00h, 0A0h, 41h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 40h, 0E8h, 15h, 05h
    db 0DFh, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 74h, 16h, 56h, 8Bh, 0CBh, 0E8h, 9Bh, 25h, 0DFh, 0FFh
    db 0D9h, 5Ch, 24h, 0Ch, 56h, 8Bh, 0CBh, 0E8h, 61h, 44h, 0DFh, 0FFh, 0EBh, 04h, 0D9h, 44h
    db 24h, 10h, 8Bh, 46h, 38h, 8Bh, 4Eh, 3Ch, 8Bh, 56h, 40h, 89h, 44h, 24h, 14h, 0D9h
    db 44h, 24h, 14h, 0D8h, 0A7h, 1Ch, 06h, 00h, 00h, 89h, 4Ch, 24h, 18h, 0D9h, 44h, 24h
    db 18h, 89h, 54h, 24h, 1Ch, 0D8h, 0A7h, 20h, 06h, 00h, 00h, 0D9h, 44h, 24h, 1Ch, 0D8h
    db 0A7h, 24h, 06h, 00h, 00h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h
    db 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DBh, 0DDh, 0D8h, 0DDh, 0D8h, 0D8h, 0D9h, 0DFh
    db 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 75h, 0Ch, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CFh, 0E8h
    db 0DDh, 81h, 0E0h, 0FFh, 8Bh, 0CFh, 0E8h, 0B6h, 0D3h, 0E0h, 0FFh, 8Bh, 86h, 28h, 01h, 00h
    db 00h, 0F6h, 0C4h, 10h, 74h, 10h, 0D9h, 44h, 24h, 0Ch, 0D8h, 87h, 4Ch, 02h, 00h, 00h
    db 0D9h, 9Fh, 4Ch, 02h, 00h, 00h, 8Bh, 0CFh, 0E8h, 0BEh, 01h, 0DEh, 0FFh, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 14h, 0C3h
?d_00230ae0@@YAXXZ ENDP

; ghidra: FUN_00630bf0  retail @ 0x00230BF0 size 1020
public ?d_00230bf0@@YAXXZ
?d_00230bf0@@YAXXZ PROC
    db 83h, 0ECh, 4Ch, 53h, 56h, 8Bh, 74h, 24h, 58h, 8Bh, 86h, 28h, 01h, 00h, 00h, 0BBh
    db 00h, 80h, 00h, 00h, 85h, 0C3h, 57h, 8Bh, 0F9h, 74h, 40h, 8Bh, 44h, 24h, 68h, 8Bh
    db 4Ch, 24h, 64h, 8Bh, 54h, 24h, 60h, 50h, 51h, 52h, 56h, 8Bh, 0CFh, 0E8h, 9Eh, 17h
    db 0E1h, 0FFh, 8Bh, 86h, 28h, 01h, 00h, 00h, 85h, 0C3h, 0Fh, 84h, 0B3h, 03h, 00h, 00h
    db 25h, 0FFh, 7Fh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 28h, 01h, 00h, 00h, 0E8h, 0DBh, 0Ch
    db 0DFh, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 4Ch, 0C2h, 10h, 00h, 8Bh, 8Eh, 04h, 02h, 00h
    db 00h, 85h, 0C9h, 74h, 38h, 8Bh, 01h, 0FFh, 90h, 84h, 01h, 00h, 00h, 84h, 0C0h, 74h
    db 2Ch, 8Bh, 86h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 0Fh, 84h, 71h, 03h
    db 00h, 00h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh, 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h
    db 99h, 0Ch, 0DFh, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 4Ch, 0C2h, 10h, 00h, 8Ah, 87h, 0FCh
    db 01h, 00h, 00h, 84h, 0C0h, 74h, 1Bh, 8Bh, 4Ch, 24h, 64h, 8Bh, 54h, 24h, 60h, 51h
    db 52h, 56h, 8Bh, 0CFh, 0E8h, 0F1h, 0EEh, 0DEh, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 4Ch, 0C2h
    db 10h, 00h, 8Bh, 46h, 74h, 55h, 8Dh, 4Ch, 24h, 68h, 51h, 8Dh, 54h, 24h, 64h, 8Dh
    db 9Fh, 20h, 01h, 00h, 00h, 52h, 8Bh, 0CBh, 89h, 44h, 24h, 70h, 0E8h, 2Fh, 0E3h, 0DEh
    db 0FFh, 8Bh, 44h, 24h, 60h, 3Bh, 03h, 74h, 05h, 8Bh, 68h, 14h, 0EBh, 02h, 33h, 0EDh
    db 55h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CFh, 0E8h, 25h, 5Fh, 0DDh, 0FFh, 8Bh, 8Fh, 0F4h
    db 07h, 00h, 00h, 49h, 85h, 0C9h, 7Eh, 23h, 8Dh, 14h, 49h, 8Dh, 94h, 0D7h, 14h, 06h
    db 00h, 00h, 0D9h, 44h, 24h, 10h, 0D9h, 02h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh
    db 08h, 49h, 83h, 0EAh, 18h, 85h, 0C9h, 7Fh, 0E9h, 85h, 0C9h, 7Dh, 02h, 33h, 0C9h, 8Dh
    db 84h, 49h, 0C3h, 00h, 00h, 00h, 0D9h, 04h, 0C7h, 8Bh, 0CEh, 0D9h, 5Ch, 24h, 68h, 0C7h
    db 44h, 24h, 60h, 00h, 3Ch, 1Ch, 46h, 0C7h, 44h, 24h, 6Ch, 0DBh, 0Fh, 49h, 40h, 0E8h
    db 0D3h, 02h, 0DFh, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 74h, 1Eh, 56h, 8Bh, 0CBh, 0E8h, 59h, 23h
    db 0DFh, 0FFh, 0D8h, 0Dh, 58h, 0E8h, 0Ah, 01h, 56h, 8Bh, 0CBh, 0D9h, 5Ch, 24h, 64h, 0E8h
    db 42h, 41h, 0DFh, 0FFh, 0D9h, 5Ch, 24h, 6Ch, 8Bh, 4Fh, 08h, 8Bh, 91h, 14h, 01h, 00h
    db 00h, 8Bh, 8Eh, 14h, 01h, 00h, 00h, 0B8h, 00h, 00h, 00h, 10h, 85h, 0D0h, 74h, 0Eh
    db 85h, 0C8h, 75h, 1Fh, 0Bh, 0C8h, 89h, 8Eh, 14h, 01h, 00h, 00h, 0EBh, 0Eh, 85h, 0C8h
    db 74h, 11h, 81h, 0A6h, 14h, 01h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh, 0CEh, 0E8h, 7Ah
    db 0Bh, 0DFh, 0FFh, 8Bh, 57h, 08h, 8Bh, 8Ah, 28h, 01h, 00h, 00h, 8Bh, 5Ch, 24h, 64h
    db 0B8h, 00h, 10h, 00h, 00h, 85h, 0C8h, 8Bh, 8Eh, 28h, 01h, 00h, 00h, 74h, 66h, 85h
    db 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 28h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 4Bh, 0Bh
    db 0DFh, 0FFh, 55h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CFh, 0E8h, 57h, 89h, 0DEh, 0FFh, 53h
    db 8Bh, 0CEh, 0E8h, 2Ch, 86h, 0E1h, 0FFh, 0D8h, 54h, 24h, 6Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 0Fh, 0DDh, 0D8h, 0D9h, 44h, 24h, 6Ch, 0D8h, 46h, 44h, 0D9h, 5Ch, 24h, 68h, 0EBh
    db 40h, 0D9h, 44h, 24h, 6Ch, 0D9h, 0E0h, 0D9h, 5Ch, 24h, 68h, 0D8h, 54h, 24h, 68h, 0DFh
    db 0E0h, 0F6h, 0C4h, 05h, 7Ah, 06h, 0DDh, 0D8h, 0D9h, 44h, 24h, 68h, 0D8h, 46h, 44h, 0D9h
    db 5Ch, 24h, 68h, 0EBh, 1Ch, 85h, 0C8h, 74h, 18h, 8Bh, 86h, 28h, 01h, 00h, 00h, 25h
    db 0FFh, 0EFh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 28h, 01h, 00h, 00h, 0E8h, 0DCh, 0Ah, 0DFh
    db 0FFh, 0D9h, 03h, 8Bh, 4Eh, 38h, 0D9h, 43h, 04h, 8Bh, 56h, 3Ch, 8Bh, 46h, 40h, 0D9h
    db 0C9h, 89h, 4Ch, 24h, 20h, 0D8h, 64h, 24h, 20h, 8Bh, 4Bh, 08h, 89h, 54h, 24h, 24h
    db 0D9h, 5Ch, 24h, 10h, 89h, 4Ch, 24h, 18h, 89h, 44h, 24h, 28h, 0D8h, 64h, 24h, 24h
    db 5Dh, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h, 14h, 0D8h, 64h, 24h, 24h, 0D9h, 5Ch, 24h
    db 14h, 0D9h, 44h, 24h, 0Ch, 0D8h, 4Ch, 24h, 0Ch, 0D9h, 44h, 24h, 14h, 0D8h, 4Ch, 24h
    db 14h, 0DEh, 0C1h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h, 0FAh, 0D8h
    db 5Ch, 24h, 5Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 45h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0CFh
    db 0AEh, 0DFh, 0FFh, 0D9h, 44h, 24h, 0Ch, 0D8h, 4Ch, 24h, 5Ch, 0D9h, 44h, 24h, 10h, 0D8h
    db 4Ch, 24h, 5Ch, 0D9h, 44h, 24h, 14h, 0D8h, 4Ch, 24h, 5Ch, 0D9h, 5Ch, 24h, 14h, 0D9h
    db 0C9h, 0D8h, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0D8h, 44h, 24h, 20h, 0D9h, 5Ch, 24h
    db 20h, 0D9h, 44h, 24h, 14h, 0D8h, 44h, 24h, 24h, 0D9h, 5Ch, 24h, 24h, 0EBh, 14h, 8Bh
    db 13h, 8Bh, 43h, 04h, 8Bh, 4Bh, 08h, 89h, 54h, 24h, 1Ch, 89h, 44h, 24h, 20h, 89h
    db 4Ch, 24h, 24h, 0D9h, 44h, 24h, 64h, 8Bh, 54h, 24h, 1Ch, 0D9h, 0FFh, 8Bh, 4Ch, 24h
    db 24h, 8Bh, 44h, 24h, 20h, 89h, 54h, 24h, 34h, 8Dh, 54h, 24h, 28h, 89h, 4Ch, 24h
    db 54h, 52h, 8Bh, 0CEh, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 44h
    db 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 54h, 00h, 00h, 80h, 3Fh, 89h, 44h, 24h, 48h
    db 0D9h, 5Ch, 24h, 60h, 0D9h, 44h, 24h, 68h, 0D9h, 0FEh, 0D9h, 44h, 24h, 60h, 0D9h, 0C1h
    db 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 54h, 24h, 64h, 0D8h, 0C1h, 0D9h, 5Ch, 24h, 2Ch
    db 0D9h, 44h, 24h, 60h, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 54h, 24h, 68h, 0D8h, 0E2h
    db 0D9h, 5Ch, 24h, 30h, 0D9h, 0C9h, 0D8h, 44h, 24h, 68h, 0D9h, 5Ch, 24h, 3Ch, 0D8h, 64h
    db 24h, 64h, 0D9h, 5Ch, 24h, 40h, 0D9h, 44h, 24h, 68h, 0D8h, 44h, 24h, 64h, 0D9h, 5Ch
    db 24h, 4Ch, 0D9h, 44h, 24h, 68h, 0D8h, 64h, 24h, 64h, 0D9h, 5Ch, 24h, 50h, 0E8h, 2Bh
    db 52h, 0E0h, 0FFh, 8Dh, 44h, 24h, 1Ch, 50h, 8Bh, 0CEh, 0E8h, 0F8h, 91h, 0E0h, 0FFh, 8Bh
    db 54h, 24h, 1Ch, 8Bh, 44h, 24h, 20h, 8Dh, 8Eh, 78h, 01h, 00h, 00h, 89h, 11h, 8Bh
    db 54h, 24h, 24h, 0C6h, 86h, 86h, 01h, 00h, 00h, 01h, 8Bh, 0B6h, 08h, 02h, 00h, 00h
    db 85h, 0F6h, 89h, 41h, 04h, 89h, 51h, 08h, 74h, 09h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 3Bh
    db 0C8h, 0DDh, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 4Ch, 0C2h, 10h, 00h
?d_00230bf0@@YAXXZ ENDP

; ghidra: FUN_00631a00  retail @ 0x00231A00 size 334
public ?d_00231a00@@YAXXZ
?d_00231a00@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 06h, 8Bh, 4Eh, 04h, 2Bh, 0C8h, 0B8h, 0ABh, 0AAh
    db 0AAh, 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 02h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 57h, 8Bh, 7Ch, 24h
    db 24h, 03h, 0C2h, 3Bh, 0C7h, 89h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 24h, 72h, 04h, 8Dh
    db 4Ch, 24h, 10h, 8Bh, 29h, 03h, 0E8h, 74h, 2Bh, 8Dh, 44h, 6Dh, 00h, 0C1h, 0E0h, 03h
    db 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h, 0E3h, 04h, 65h, 00h, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 24h, 0EBh, 16h, 0E8h, 0E5h, 0CAh, 5Fh, 00h, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 24h, 0EBh, 08h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 24h
    db 8Bh, 54h, 24h, 18h, 8Dh, 44h, 24h, 28h, 50h, 8Bh, 06h, 51h, 52h, 50h, 0E8h, 0CAh
    db 6Eh, 0DFh, 0FFh, 83h, 0C4h, 10h, 83h, 0FFh, 01h, 8Bh, 0D8h, 75h, 31h, 85h, 0DBh, 74h
    db 28h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 01h, 8Bh, 0D3h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h
    db 04h, 8Bh, 41h, 08h, 89h, 42h, 08h, 8Bh, 41h, 0Ch, 89h, 42h, 0Ch, 8Bh, 41h, 10h
    db 89h, 42h, 10h, 8Bh, 49h, 14h, 89h, 4Ah, 14h, 83h, 0C3h, 18h, 0EBh, 16h, 8Bh, 44h
    db 24h, 1Ch, 8Dh, 54h, 24h, 28h, 52h, 50h, 57h, 53h, 0E8h, 3Fh, 63h, 0DEh, 0FFh, 83h
    db 0C4h, 10h, 8Bh, 0D8h, 8Ah, 44h, 24h, 28h, 84h, 0C0h, 75h, 19h, 8Bh, 56h, 04h, 8Bh
    db 44h, 24h, 18h, 8Dh, 4Ch, 24h, 28h, 51h, 53h, 52h, 50h, 0E8h, 5Dh, 6Eh, 0DFh, 0FFh
    db 83h, 0C4h, 10h, 8Bh, 0D8h, 8Bh, 3Eh, 85h, 0FFh, 74h, 38h, 8Bh, 4Eh, 08h, 2Bh, 0CFh
    db 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 02h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 57h, 0E8h
    db 8Ch, 03h, 65h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 57h, 0E8h, 0C0h, 0CAh, 5Fh, 00h
    db 83h, 0C4h, 08h, 8Bh, 44h, 24h, 24h, 8Dh, 4Ch, 6Dh, 00h, 5Fh, 8Dh, 14h, 0C8h, 89h
    db 5Eh, 04h, 89h, 06h, 89h, 56h, 08h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 14h, 00h
?d_00231a00@@YAXXZ ENDP

; ghidra: FUN_00631c50  retail @ 0x00231C50 size 812
_TEXT ENDS
_TEXT$d00631c50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00631C50 size 812
public ?d_00231c50@@YAXXZ
?d_00231c50@@YAXXZ PROC
    db 083h, 0ECh, 02Ch, 08Bh, 044h, 024h, 030h, 053h, 055h, 056h, 057h, 08Bh, 0F1h, 08Bh, 07Eh, 004h
    db 08Bh, 05Eh, 008h, 050h
    call ?j_0002de0c@@YAXXZ
    db 08Bh, 08Eh, 02Ch, 001h, 000h, 000h, 08Bh, 086h, 030h, 001h, 000h, 000h, 02Bh, 0C1h, 0C1h, 0F8h
    db 004h, 08Dh, 0AEh, 024h, 002h, 000h, 000h, 050h, 08Bh, 0CDh, 089h, 044h, 024h, 014h
    call ?j_00005835@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 00Fh, 08Eh, 09Dh, 001h, 000h, 000h, 089h, 044h, 024h, 014h
    db 08Dh, 064h, 024h, 000h, 0D9h, 087h, 0F8h, 002h, 000h, 000h, 068h, 009h, 002h, 000h, 000h, 0D8h
    db 00Dh
    dd ?g_bfmeAngleTwoPi@@3MA
    db 068h
    dd g_Va010AE860
    db 083h, 0ECh, 008h, 0D9h, 05Ch, 024h, 050h, 0D9h, 087h, 000h, 003h, 000h, 000h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Ch, 024h, 004h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0A7h, 000h, 003h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 08Bh, 04Ch, 024h, 050h, 0D9h, 05Ch, 024h, 038h, 068h, 00Ah, 002h, 000h, 000h, 068h
    dd g_Va010AE860
    db 051h, 06Ah, 000h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 087h, 0F8h, 002h, 000h, 000h, 083h, 0C4h, 020h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 068h, 00Bh, 002h, 000h, 000h, 068h
    dd g_Va010AE860
    db 083h, 0ECh, 008h, 0D9h, 05Ch, 024h, 004h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0A7h, 0F8h, 002h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 0D9h, 05Ch, 024h, 03Ch, 083h, 0C4h, 010h, 0D9h, 087h, 00Ch, 003h, 000h, 000h, 068h, 00Eh, 002h
    db 000h, 000h, 0D8h, 00Dh
    dd ?g_bfmeAngleTwoPi@@3MA
    db 068h
    dd g_Va010AE860
    db 083h, 0ECh, 008h, 0D9h, 05Ch, 024h, 050h, 0D9h, 087h, 014h, 003h, 000h, 000h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Ch, 024h, 004h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0A7h, 014h, 003h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 08Bh, 054h, 024h, 050h, 0D9h, 05Ch, 024h, 044h, 068h, 00Fh, 002h, 000h, 000h, 068h
    dd g_Va010AE860
    db 052h, 06Ah, 000h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 0D9h, 05Ch, 024h, 050h, 0D9h, 087h, 00Ch, 003h, 000h, 000h, 083h, 0C4h, 020h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 068h, 010h, 002h, 000h, 000h, 068h
    dd g_Va010AE860
    db 083h, 0ECh, 008h, 0D9h, 05Ch, 024h, 004h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0A7h, 00Ch, 003h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?Rva0002CCA5GetGameLogicRandomValueRealThunk@@YAMMMPADH@Z
    db 08Bh, 045h, 004h, 0D9h, 05Ch, 024h, 048h, 08Bh, 04Dh, 008h, 083h, 0C4h, 010h, 03Bh, 0C1h, 074h
    db 033h, 085h, 0C0h, 074h, 029h, 08Bh, 04Ch, 024h, 024h, 08Bh, 054h, 024h, 028h, 089h, 008h, 08Bh
    db 04Ch, 024h, 02Ch, 089h, 050h, 004h, 08Bh, 054h, 024h, 030h, 089h, 048h, 008h, 08Bh, 04Ch, 024h
    db 034h, 089h, 050h, 00Ch, 08Bh, 054h, 024h, 038h, 089h, 048h, 010h, 089h, 050h, 014h, 083h, 045h
    db 004h, 018h, 0EBh, 016h, 06Ah, 001h, 06Ah, 001h, 08Dh, 04Ch, 024h, 048h, 051h, 08Dh, 054h, 024h
    db 030h, 052h, 050h, 08Bh, 0CDh
    call ?j_0000A47A@@YAXXZ
    db 0FFh, 04Ch, 024h, 014h, 00Fh, 085h, 06Fh, 0FEh, 0FFh, 0FFh, 08Bh, 044h, 024h, 010h, 033h, 0EDh
    db 085h, 0C0h, 0C7h, 044h, 024h, 040h, 000h, 000h, 000h, 000h, 00Fh, 08Eh, 007h, 001h, 000h, 000h
    db 055h, 08Dh, 044h, 024h, 018h, 050h, 08Bh, 0CEh
    call ?j_00006c12@@YAXXZ
    db 08Bh, 0BEh, 0F4h, 007h, 000h, 000h, 033h, 0C9h, 085h, 0FFh, 07Eh, 027h, 08Dh, 096h, 014h, 006h
    db 000h, 000h, 0D9h, 002h, 0D9h, 044h, 024h, 014h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 00Fh
    db 08Bh, 0C8h, 000h, 000h, 000h, 08Bh, 086h, 0F4h, 007h, 000h, 000h, 041h, 083h, 0C2h, 018h, 03Bh
    db 0C8h, 07Ch, 0DFh, 083h, 0FFh, 014h, 00Fh, 08Dh, 0BEh, 000h, 000h, 000h, 0D9h, 044h, 024h, 014h
    db 08Dh, 00Ch, 07Fh, 0D9h, 09Ch, 0CEh, 014h, 006h, 000h, 000h, 08Bh, 086h, 0F4h, 007h, 000h, 000h
    db 085h, 0C0h, 075h, 008h, 08Bh, 054h, 024h, 014h, 089h, 054h, 024h, 040h, 0D9h, 044h, 024h, 014h
    db 08Dh, 044h, 024h, 014h, 0D8h, 064h, 024h, 040h, 050h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CEh
    db 0D9h, 05Ch, 024h, 01Ch, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h
    call ?j_00031b3d@@YAXXZ
    db 08Bh, 086h, 0F4h, 007h, 000h, 000h, 08Dh, 014h, 040h, 0C6h, 084h, 0D6h, 028h, 006h, 000h, 000h
    db 001h, 0D9h, 043h, 038h, 0D9h, 043h, 03Ch, 08Bh, 043h, 040h, 0D9h, 0C9h, 089h, 044h, 024h, 02Ch
    db 0D8h, 044h, 024h, 01Ch, 08Bh, 086h, 0F4h, 007h, 000h, 000h, 08Dh, 00Ch, 040h, 08Dh, 094h, 0CEh
    db 01Ch, 006h, 000h, 000h, 0D9h, 05Ch, 024h, 024h, 08Bh, 044h, 024h, 024h, 0D8h, 044h, 024h, 020h
    db 089h, 002h, 08Bh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 028h, 08Bh, 04Ch, 024h, 028h, 089h, 04Ah
    db 004h, 089h, 042h, 008h, 08Bh, 086h, 0F4h, 007h, 000h, 000h, 08Bh, 053h, 044h, 083h, 0C0h, 041h
    db 08Dh, 00Ch, 040h, 089h, 014h, 0CEh, 0FFh, 086h, 0F4h, 007h, 000h, 000h, 08Bh, 044h, 024h, 010h
    db 045h, 03Bh, 0E8h, 00Fh, 08Ch, 0F9h, 0FEh, 0FFh, 0FFh, 08Bh, 086h, 0F4h, 007h, 000h, 000h, 048h
    db 078h, 01Bh, 08Dh, 00Ch, 040h, 08Dh, 0BCh, 0CEh, 01Ch, 006h, 000h, 000h, 08Dh, 058h, 001h, 057h
    db 08Bh, 0CEh
    call ?j_00038d61@@YAXXZ
    db 083h, 0EFh, 018h, 04Bh, 075h, 0F2h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 02Ch, 0C2h, 004h, 000h
?d_00231c50@@YAXXZ ENDP
_TEXT$d00631c50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00632050  retail @ 0x00232050 size 17
public ?d_00232050@@YAXXZ
?d_00232050@@YAXXZ PROC
    db 8Bh, 41h, 08h, 8Bh, 88h, 04h, 02h, 00h, 00h, 83h, 0C1h, 20h, 0E9h, 09h, 23h, 0E0h
    db 0FFh
?d_00232050@@YAXXZ ENDP

; ghidra: FUN_00632210  retail @ 0x00232210 size 98
public ?d_00232210@@YAXXZ
?d_00232210@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 57h, 74h, 51h, 8Bh, 7Ch, 24h, 10h, 85h, 0FFh
    db 74h, 49h, 53h, 55h, 6Ah, 00h, 8Bh, 0CFh, 32h, 0DBh, 0E8h, 77h, 0D8h, 0DDh, 0FFh, 8Bh
    db 0E8h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 84h, 01h, 00h, 00h, 84h, 0C0h, 74h, 23h, 8Bh
    db 4Eh, 30h, 0E8h, 29h, 0C3h, 0DDh, 0FFh, 85h, 0C0h, 74h, 17h, 3Bh, 0F8h, 74h, 11h, 6Ah
    db 00h, 8Bh, 0C8h, 0E8h, 4Eh, 0D8h, 0DDh, 0FFh, 85h, 0C0h, 74h, 06h, 3Bh, 0E8h, 75h, 02h
    db 0B3h, 01h, 5Dh, 8Ah, 0C3h, 5Bh, 5Fh, 5Eh, 0C2h, 08h, 00h, 5Fh, 32h, 0C0h, 5Eh, 0C2h
    db 08h, 00h
?d_00232210@@YAXXZ ENDP

; ghidra: FUN_006322d0  retail @ 0x002322D0 size 27
public ?d_002322d0@@YAXXZ
?d_002322d0@@YAXXZ PROC
    db 8Bh, 81h, 24h, 0FFh, 0FFh, 0FFh, 8Bh, 88h, 04h, 02h, 00h, 00h, 85h, 0C9h, 75h, 03h
    db 32h, 0C0h, 0C3h, 8Bh, 11h, 0FFh, 0A2h, 94h, 01h, 00h, 00h
?d_002322d0@@YAXXZ ENDP

; ghidra: FUN_00632310  retail @ 0x00232310 size 46
public ?d_00232310@@YAXXZ
?d_00232310@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 85h, 0D2h, 74h, 21h, 8Bh, 44h, 24h, 0Ch, 85h, 0C0h, 74h, 19h
    db 8Bh, 4Ch, 24h, 08h, 85h, 0C9h, 74h, 11h, 6Ah, 00h, 50h, 52h, 0E8h, 2Bh, 0C5h, 0DFh
    db 0FFh, 84h, 0C0h, 0Fh, 95h, 0C0h, 0C2h, 0Ch, 00h, 32h, 0C0h, 0C2h, 0Ch, 00h
?d_00232310@@YAXXZ ENDP

; ghidra: FUN_006323b0  retail @ 0x002323B0 size 110
public ?d_002323b0@@YAXXZ
?d_002323b0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 0C0h, 0FAh, 2Eh, 01h, 6Ah, 0FFh, 68h, 3Eh
    db 0D9h, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 2Bh, 09h, 05h, 0C0h, 0FAh, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 0A4h, 04h, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0E5h, 89h
    db 0E0h, 0FFh, 0A3h, 0BCh, 0FAh, 2Eh, 01h, 0C7h, 44h, 24h, 08h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h
    db 0BCh, 0FAh, 2Eh, 01h, 8Bh, 4Ch, 24h, 10h, 50h, 0E8h, 15h, 8Ah, 0DFh, 0FFh, 8Bh, 0Ch
    db 24h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_002323b0@@YAXXZ ENDP

; ghidra: FUN_00632540  retail @ 0x00232540 size 33
public ?d_00232540@@YAXXZ
?d_00232540@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 06h, 6Ah, 00h, 0FFh, 90h, 50h, 01h, 00h, 00h, 8Bh, 16h
    db 8Bh, 0CEh, 8Bh, 0F8h, 0FFh, 92h, 54h, 01h, 00h, 00h, 2Bh, 0F8h, 8Bh, 0C7h, 5Fh, 5Eh
    db 0C3h
?d_00232540@@YAXXZ ENDP

; ghidra: FUN_006325f0  retail @ 0x002325F0 size 94
public ?d_002325f0@@YAXXZ
?d_002325f0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 8Bh, 44h, 24h, 20h, 0D9h, 00h, 8Bh, 49h, 08h, 85h, 0C9h, 0D9h, 40h
    db 04h, 8Bh, 44h, 24h, 1Ch, 0D9h, 0C9h, 0D8h, 60h, 38h, 0D9h, 1Ch, 24h, 0D8h, 60h, 3Ch
    db 0D9h, 5Ch, 24h, 04h, 74h, 30h, 8Dh, 44h, 24h, 0Ch, 50h, 0E8h, 0C3h, 38h, 0DDh, 0FFh
    db 0D9h, 44h, 24h, 04h, 0D8h, 4Ch, 24h, 10h, 0D9h, 04h, 24h, 0D8h, 4Ch, 24h, 0Ch, 0DEh
    db 0C1h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0B0h, 01h
    db 83h, 0C4h, 18h, 0C2h, 08h, 00h, 32h, 0C0h, 83h, 0C4h, 18h, 0C2h, 08h, 00h
?d_002325f0@@YAXXZ ENDP

; ghidra: FUN_00632670  retail @ 0x00232670 size 49
public ?d_00232670@@YAXXZ
?d_00232670@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 0BEh, 24h, 0FFh, 0FFh, 0FFh, 85h, 0FFh, 74h, 1Eh, 8Bh, 44h
    db 24h, 0Ch, 50h, 8Bh, 0CFh, 0E8h, 1Bh, 73h, 0E0h, 0FFh, 6Ah, 01h, 57h, 8Dh, 8Eh, 1Ch
    db 0FFh, 0FFh, 0FFh, 0C6h, 46h, 04h, 01h, 0E8h, 3Eh, 31h, 0DEh, 0FFh, 5Fh, 5Eh, 0C2h, 04h
    db 00h
?d_00232670@@YAXXZ ENDP

; ghidra: FUN_006337f0  retail @ 0x002337F0 size 49
public ?d_002337f0@@YAXXZ
?d_002337f0@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 04h, 8Bh, 11h, 89h, 10h, 8Bh, 51h, 04h, 89h, 50h, 04h
    db 8Bh, 51h, 08h, 89h, 50h, 08h, 8Bh, 51h, 0Ch, 89h, 50h, 0Ch, 8Ah, 51h, 10h, 88h
    db 50h, 10h, 8Bh, 51h, 14h, 89h, 50h, 14h, 8Bh, 49h, 18h, 89h, 48h, 18h, 0C2h, 04h
    db 00h
?d_002337f0@@YAXXZ ENDP

; ghidra: FUN_00633960  retail @ 0x00233960 size 94
public ?d_00233960@@YAXXZ
?d_00233960@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 23h, 0C1h, 0E0h, 04h, 3Dh, 80h
    db 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 0B5h, 0E5h, 64h, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h
    db 0EBh, 0Eh, 0E8h, 0B9h, 0ABh, 5Fh, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh, 02h, 33h, 0EDh
    db 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h, 8Bh, 0FDh, 2Bh
    db 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 0C2h, 0Dh, 0DEh, 0FFh, 83h, 0C6h, 10h, 83h, 0C4h
    db 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch, 00h
?d_00233960@@YAXXZ ENDP

; ghidra: FUN_006339e0  retail @ 0x002339E0 size 41
public ?d_002339e0@@YAXXZ
?d_002339e0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 08h, 3Bh, 0C2h, 74h, 1Ch, 53h, 8Bh, 5Ch, 24h
    db 10h, 56h, 57h, 8Bh, 0F8h, 83h, 0C0h, 1Ch, 3Bh, 0C2h, 0B9h, 07h, 00h, 00h, 00h, 8Bh
    db 0F3h, 0F3h, 0A5h, 75h, 0EEh, 5Fh, 5Eh, 5Bh, 0C3h
?d_002339e0@@YAXXZ ENDP

; ghidra: FUN_00633a20  retail @ 0x00233A20 size 78
public ?d_00233a20@@YAXXZ
?d_00233a20@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 53h, 8Bh, 5Ch, 24h, 08h, 2Bh, 0CBh, 0B8h, 93h, 24h, 49h, 92h
    db 0F7h, 0E9h, 03h, 0D1h, 0C1h, 0FAh, 04h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 85h, 0C0h
    db 7Eh, 26h, 56h, 8Bh, 0D0h, 8Bh, 44h, 24h, 14h, 57h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 0F3h, 8Bh, 0F8h, 0B9h, 07h, 00h, 00h, 00h, 83h, 0C3h, 1Ch, 83h, 0C0h, 1Ch, 4Ah
    db 0F3h, 0A5h, 75h, 0ECh, 5Fh, 5Eh, 5Bh, 0C3h, 8Bh, 44h, 24h, 10h, 5Bh, 0C3h
?d_00233a20@@YAXXZ ENDP

; ghidra: FUN_00633b60  retail @ 0x00233B60 size 79
public ?d_00233b60@@YAXXZ
?d_00233b60@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0CBh, 2Bh, 0CFh, 0B8h, 93h
    db 24h, 49h, 92h, 0F7h, 0E9h, 03h, 0D1h, 0C1h, 0FAh, 04h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 85h, 0C0h, 7Eh, 23h, 8Bh, 0D0h, 8Bh, 44h, 24h, 14h, 56h, 8Dh, 64h, 24h, 00h
    db 83h, 0EBh, 1Ch, 83h, 0E8h, 1Ch, 4Ah, 0B9h, 07h, 00h, 00h, 00h, 8Bh, 0F3h, 8Bh, 0F8h
    db 0F3h, 0A5h, 75h, 0ECh, 5Eh, 5Fh, 5Bh, 0C3h, 8Bh, 44h, 24h, 14h, 5Fh, 5Bh, 0C3h
?d_00233b60@@YAXXZ ENDP

; ghidra: FUN_00633c60  retail @ 0x00233C60 size 26
public ?d_00233c60@@YAXXZ
?d_00233c60@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 0C6h, 40h, 10h, 01h, 89h, 48h, 14h, 89h, 48h, 18h
    db 89h, 48h, 04h, 89h, 48h, 08h, 89h, 48h, 0Ch, 0C3h
?d_00233c60@@YAXXZ ENDP

; ghidra: FUN_00633c80  retail @ 0x00233C80 size 16
public ?d_00233c80@@YAXXZ
?d_00233c80@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 00h, 00h, 00h, 00h, 0C7h, 40h, 0Ch, 00h, 00h, 00h, 00h, 0C3h
?d_00233c80@@YAXXZ ENDP

; ghidra: FUN_00633ca0  retail @ 0x00233CA0 size 16
public ?d_00233ca0@@YAXXZ
?d_00233ca0@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 89h, 48h, 04h, 89h, 48h, 08h, 89h, 48h, 0Ch, 0C3h
?d_00233ca0@@YAXXZ ENDP

; ghidra: FUN_00633cc0  retail @ 0x00233CC0 size 39
public ?d_00233cc0@@YAXXZ
?d_00233cc0@@YAXXZ PROC
    db 56h, 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 57h, 8Bh, 0D1h, 8Bh, 3Ah, 8Bh, 0F0h, 89h, 3Eh
    db 8Bh, 7Ah, 04h, 89h, 7Eh, 04h, 8Bh, 52h, 08h, 89h, 56h, 08h, 8Bh, 49h, 0Ch, 5Fh
    db 89h, 48h, 0Ch, 5Eh, 0C2h, 04h, 00h
?d_00233cc0@@YAXXZ ENDP

; ghidra: FUN_00633d20  retail @ 0x00233D20 size 27
public ?d_00233d20@@YAXXZ
?d_00233d20@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 75h, 04h, 8Bh, 40h, 6Ch, 0C3h, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 84h, 0E5h, 0DCh, 0FFh, 8Bh, 40h, 6Ch, 0C3h
?d_00233d20@@YAXXZ ENDP

; ghidra: FUN_00633dc0  retail @ 0x00233DC0 size 78
public ?d_00233dc0@@YAXXZ
?d_00233dc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 74h, 39h, 86h, 0B4h, 01h, 00h, 00h
    db 75h, 0Eh, 0C7h, 86h, 0B4h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
    db 39h, 86h, 0BCh, 01h, 00h, 00h, 75h, 22h, 51h, 8Bh, 0CEh, 0C7h, 86h, 0BCh, 01h, 00h
    db 00h, 00h, 00h, 00h, 00h, 0E8h, 0E0h, 0B7h, 0E0h, 0FFh, 85h, 0C0h, 74h, 0Ch, 8Bh, 40h
    db 04h, 8Bh, 48h, 10h, 89h, 8Eh, 0CCh, 01h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_00233dc0@@YAXXZ ENDP

; ghidra: FUN_00633e90  retail @ 0x00233E90 size 30
public ?d_00233e90@@YAXXZ
?d_00233e90@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0E2h, 0E9h, 0E0h, 0FFh, 8Bh, 46h, 0D0h, 8Ah, 88h, 70h, 02h, 00h
    db 00h, 84h, 0C9h, 0Fh, 94h, 0C1h, 88h, 8Eh, 0EDh, 01h, 00h, 00h, 5Eh, 0C3h
?d_00233e90@@YAXXZ ENDP

; ghidra: FUN_00633ee0  retail @ 0x00233EE0 size 40
public ?d_00233ee0@@YAXXZ
?d_00233ee0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 20h, 0FFh, 0FFh, 0FFh, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 05h
    db 48h, 02h, 00h, 00h, 50h, 0E8h, 66h, 46h, 0DFh, 0FFh, 85h, 0C0h, 74h, 08h, 8Bh, 16h
    db 50h, 8Bh, 0CEh, 0FFh, 52h, 64h, 5Eh, 0C3h
?d_00233ee0@@YAXXZ ENDP

; ghidra: FUN_00633f30  retail @ 0x00233F30 size 154
public ?d_00233f30@@YAXXZ
?d_00233f30@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 18h, 0D9h, 47h, 04h, 8Bh, 0F1h, 0D9h, 07h
    db 8Bh, 46h, 08h, 0D9h, 0C0h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 0D8h, 0C9h, 8Bh, 11h, 0D9h
    db 0C2h, 83h, 0C0h, 38h, 0D8h, 0CBh, 50h, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D9h
    db 5Ch, 24h, 1Ch, 0FFh, 92h, 0BCh, 00h, 00h, 00h, 84h, 0C0h, 74h, 11h, 0D9h, 44h, 24h
    db 18h, 8Bh, 46h, 04h, 0D8h, 88h, 0DCh, 02h, 00h, 00h, 0D9h, 5Ch, 24h, 18h, 8Bh, 0CFh
    db 0E8h, 0CDh, 2Eh, 0E1h, 0FFh, 8Bh, 4Eh, 08h, 0D8h, 41h, 44h, 0D9h, 5Ch, 24h, 08h, 8Bh
    db 74h, 24h, 08h, 56h, 0E8h, 87h, 0F9h, 63h, 00h, 0D9h, 5Ch, 24h, 0Ch, 56h, 0E8h, 6Dh
    db 0F9h, 63h, 00h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 20h, 8Bh, 44h, 24h, 1Ch, 83h
    db 0C4h, 08h, 5Fh, 0D9h, 5Ch, 24h, 04h, 5Eh, 0D8h, 4Ch, 24h, 10h, 0D9h, 04h, 24h, 0D9h
    db 18h, 0D9h, 58h, 04h, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_00233f30@@YAXXZ ENDP

; ghidra: FUN_00634040  retail @ 0x00234040 size 62
public ?d_00234040@@YAXXZ
?d_00234040@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 6Ah, 00h, 0FFh, 50h, 78h, 8Bh, 0CEh, 0E8h, 2Dh, 32h, 0DEh
    db 0FFh, 8Bh, 4Eh, 04h, 8Ah, 81h, 70h, 02h, 00h, 00h, 33h, 0D2h, 84h, 0C0h, 0Fh, 0B6h
    db 86h, 21h, 02h, 00h, 00h, 0Fh, 94h, 0C2h, 3Bh, 0C2h, 74h, 10h, 8Bh, 96h, 0E4h, 00h
    db 00h, 00h, 8Dh, 8Eh, 0E4h, 00h, 00h, 00h, 5Eh, 0FFh, 62h, 5Ch, 5Eh, 0C3h
?d_00234040@@YAXXZ ENDP

; ghidra: FUN_006341b0  retail @ 0x002341B0 size 12
public ?d_002341b0@@YAXXZ
?d_002341b0@@YAXXZ PROC
    db 8Bh, 81h, 20h, 0FFh, 0FFh, 0FFh, 05h, 3Ch, 02h, 00h, 00h, 0C3h
?d_002341b0@@YAXXZ ENDP

; ghidra: FUN_006341c0  retail @ 0x002341C0 size 47
public ?d_002341c0@@YAXXZ
?d_002341c0@@YAXXZ PROC
    db 8Bh, 41h, 08h, 56h, 8Bh, 0B0h, 14h, 02h, 00h, 00h, 85h, 0F6h, 74h, 1Dh, 8Bh, 8Eh
    db 0FCh, 01h, 00h, 00h, 8Bh, 44h, 24h, 08h, 8Bh, 11h, 6Ah, 00h, 50h, 0FFh, 52h, 44h
    db 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 04h, 5Eh, 0C2h, 04h, 00h
?d_002341c0@@YAXXZ ENDP

; ghidra: FUN_006346f0  retail @ 0x002346F0 size 11
public ?d_002346f0@@YAXXZ
?d_002346f0@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_002346f0@@YAXXZ ENDP

; ghidra: FUN_00634710  retail @ 0x00234710 size 11
public ?d_00234710@@YAXXZ
?d_00234710@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_00234710@@YAXXZ ENDP

; ghidra: FUN_00634780  retail @ 0x00234780 size 53
public ?d_00234780@@YAXXZ
?d_00234780@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 2Ch, 8Bh, 4Ch, 24h, 08h, 8Bh, 11h, 89h, 10h
    db 8Bh, 51h, 04h, 89h, 50h, 04h, 8Bh, 51h, 08h, 89h, 50h, 08h, 8Bh, 51h, 0Ch, 89h
    db 50h, 0Ch, 8Ah, 51h, 10h, 88h, 50h, 10h, 8Bh, 51h, 14h, 89h, 50h, 14h, 8Bh, 49h
    db 18h, 89h, 48h, 18h, 0C3h
?d_00234780@@YAXXZ ENDP

; ghidra: FUN_006347d0  retail @ 0x002347D0 size 45
public ?d_002347d0@@YAXXZ
?d_002347d0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 3Bh, 0F3h, 57h, 8Bh, 7Ch, 24h
    db 18h, 74h, 14h, 56h, 57h, 0E8h, 0F2h, 0E0h, 0DDh, 0FFh, 83h, 0C6h, 1Ch, 83h, 0C4h, 08h
    db 83h, 0C7h, 1Ch, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_002347d0@@YAXXZ ENDP

; ghidra: FUN_006348e0  retail @ 0x002348E0 size 179
public ?d_002348e0@@YAXXZ
?d_002348e0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 56h, 8Bh, 74h, 24h, 18h, 57h, 8Bh, 0F9h, 3Bh, 1Fh, 74h
    db 3Dh, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 75h, 0Fh, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 75h
    db 2Dh, 8Bh, 06h, 3Bh, 43h, 10h, 7Ch, 26h, 6Ah, 14h, 0E8h, 31h, 9Ch, 5Fh, 00h, 8Dh
    db 48h, 10h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 04h, 8Bh, 16h, 89h, 11h, 89h, 43h, 0Ch
    db 8Bh, 0Fh, 3Bh, 59h, 0Ch, 8Bh, 0F0h, 75h, 37h, 89h, 41h, 0Ch, 0EBh, 32h, 6Ah, 14h
    db 0E8h, 0Bh, 9Ch, 5Fh, 00h, 8Dh, 48h, 10h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 04h, 8Bh
    db 16h, 89h, 11h, 89h, 43h, 08h, 8Bh, 0Fh, 3Bh, 0D9h, 8Bh, 0F0h, 75h, 0Ah, 89h, 41h
    db 04h, 8Bh, 0Fh, 89h, 41h, 0Ch, 0EBh, 08h, 3Bh, 59h, 08h, 75h, 03h, 89h, 41h, 08h
    db 89h, 5Eh, 04h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 0C7h, 46h, 0Ch, 00h, 00h, 00h
    db 00h, 8Bh, 17h, 83h, 0C2h, 04h, 52h, 56h, 0E8h, 53h, 80h, 5Fh, 00h, 8Bh, 47h, 04h
    db 83h, 0C4h, 08h, 40h, 89h, 47h, 04h, 8Bh, 44h, 24h, 10h, 5Fh, 89h, 30h, 5Eh, 5Bh
    db 0C2h, 14h, 00h
?d_002348e0@@YAXXZ ENDP

; ghidra: FUN_006349d0  retail @ 0x002349D0 size 94
public ?d_002349d0@@YAXXZ
?d_002349d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 23h, 6Bh, 0C0h, 1Ch, 3Dh, 80h
    db 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 45h, 0D5h, 64h, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h
    db 0EBh, 0Eh, 0E8h, 49h, 9Bh, 5Fh, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh, 02h, 33h, 0EDh
    db 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h, 8Bh, 0FDh, 2Bh
    db 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 0C1h, 0DEh, 0DDh, 0FFh, 83h, 0C6h, 1Ch, 83h, 0C4h
    db 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch, 00h
?d_002349d0@@YAXXZ ENDP

; ghidra: FUN_00634a80  retail @ 0x00234A80 size 41
public ?d_00234a80@@YAXXZ
?d_00234a80@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 85h, 0FFh, 76h, 16h, 53h, 8Bh
    db 5Ch, 24h, 18h, 53h, 56h, 0E8h, 42h, 0DEh, 0DDh, 0FFh, 83h, 0C4h, 08h, 83h, 0C6h, 1Ch
    db 4Fh, 75h, 0F0h, 5Bh, 5Fh, 8Bh, 0C6h, 5Eh, 0C3h
?d_00234a80@@YAXXZ ENDP

; ghidra: FUN_00634cd0  retail @ 0x00234CD0 size 108
public ?d_00234cd0@@YAXXZ
?d_00234cd0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 6Eh, 0D9h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 00h
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0C7h, 46h, 04h, 00h, 00h
    db 00h, 00h, 6Ah, 00h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 4Eh, 08h, 0C6h, 44h, 24h, 18h
    db 01h, 0E8h, 0F0h, 05h, 0DFh, 0FFh, 6Ah, 00h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 4Eh, 78h
    db 0C6h, 44h, 24h, 18h, 02h, 0E8h, 0DCh, 05h, 0DFh, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00234cd0@@YAXXZ ENDP

; ghidra: FUN_00634d60  retail @ 0x00234D60 size 102
public ?d_00234d60@@YAXXZ
?d_00234d60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0AEh, 0D9h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 78h
    db 0C7h, 44h, 24h, 10h, 02h, 00h, 00h, 00h, 0E8h, 0A8h, 21h, 0DFh, 0FFh, 8Dh, 4Eh, 08h
    db 0C6h, 44h, 24h, 10h, 01h, 0E8h, 9Bh, 21h, 0DFh, 0FFh, 8Dh, 4Eh, 04h, 0C6h, 44h, 24h
    db 10h, 00h, 0E8h, 99h, 2Bh, 65h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 8Ah, 2Bh, 65h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00234d60@@YAXXZ ENDP

; ghidra: FUN_006350c0  retail @ 0x002350C0 size 99
public ?d_002350c0@@YAXXZ
?d_002350c0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 56h, 57h, 8Bh, 0F9h, 8Dh, 4Ch, 24h, 10h, 0E8h, 69h, 0ECh, 0DFh, 0FFh
    db 8Bh, 74h, 24h, 28h, 8Bh, 87h, 2Ch, 01h, 00h, 00h, 0C1h, 0E6h, 04h, 8Dh, 44h, 06h
    db 04h, 50h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CFh, 0E8h, 4Fh, 0CAh, 0DFh, 0FFh, 8Bh, 10h
    db 8Bh, 8Fh, 2Ch, 01h, 00h, 00h, 0D9h, 44h, 0Eh, 0Ch, 8Bh, 40h, 04h, 8Bh, 74h, 24h
    db 24h, 0D9h, 5Ch, 24h, 1Ch, 89h, 54h, 24h, 14h, 8Dh, 54h, 24h, 10h, 52h, 8Bh, 0CEh
    db 89h, 44h, 24h, 1Ch, 0E8h, 46h, 02h, 0E0h, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 83h, 0C4h, 18h
    db 0C2h, 08h, 00h
?d_002350c0@@YAXXZ ENDP

; ghidra: FUN_00635140  retail @ 0x00235140 size 11
public ?d_00235140@@YAXXZ
?d_00235140@@YAXXZ PROC
    db 8Bh, 51h, 34h, 33h, 0C0h, 85h, 0D2h, 0Fh, 94h, 0C0h, 0C3h
?d_00235140@@YAXXZ ENDP

; ghidra: FUN_00635150  retail @ 0x00235150 size 299
_TEXT ENDS
_TEXT$d00635150 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00635150 size 299
public ?d_00235150@@YAXXZ
?d_00235150@@YAXXZ PROC
    db 083h, 0ECh, 02Ch, 057h, 08Bh, 0F9h, 08Bh, 087h, 024h, 0FFh, 0FFh, 0FFh, 08Bh, 08Fh, 054h, 0FFh
    db 0FFh, 0FFh, 089h, 044h, 024h, 008h, 08Bh, 001h, 03Bh, 0C1h, 089h, 044h, 024h, 004h, 00Fh, 084h
    db 000h, 001h, 000h, 000h, 053h, 055h, 08Bh, 06Ch, 024h, 048h, 056h, 0EBh, 004h, 08Bh, 044h, 024h
    db 010h, 08Bh, 070h, 008h, 085h, 0F6h, 00Fh, 084h, 0D3h, 000h, 000h, 000h, 08Bh, 09Eh, 004h, 002h
    db 000h, 000h, 08Bh, 017h, 08Dh, 044h, 024h, 04Ch, 050h, 056h, 08Dh, 04Ch, 024h, 038h, 051h, 08Bh
    db 0CFh, 0C7h, 044h, 024h, 058h, 000h, 000h, 000h, 000h, 0FFh, 052h, 01Ch, 08Bh, 010h, 089h, 054h
    db 024h, 024h, 08Bh, 048h, 004h, 089h, 04Ch, 024h, 028h, 08Bh, 050h, 008h, 08Bh, 044h, 024h, 014h
    db 083h, 0C0h, 038h, 083h, 0FDh, 001h, 08Bh, 008h, 089h, 054h, 024h, 02Ch, 08Bh, 050h, 004h, 08Bh
    db 040h, 008h, 089h, 04Ch, 024h, 018h, 089h, 054h, 024h, 01Ch, 089h, 044h, 024h, 020h, 074h, 040h
    db 08Bh, 044h, 024h, 044h, 0D9h, 044h, 024h, 018h, 0D8h, 000h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h
    db 004h, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 008h, 0D9h, 05Ch, 024h, 020h, 0D9h, 0C9h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 05Ch, 024h, 018h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 020h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 05Ch, 024h, 020h, 08Bh, 04Ch, 024h, 014h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 06Ah, 000h, 051h, 08Bh, 048h, 00Ch, 08Dh, 054h, 024h, 02Ch, 052h, 056h
    call ?j_000392ca@@YAXXZ
    db 08Bh, 044h, 024h, 048h, 08Dh, 04Ch, 024h, 024h, 051h, 08Bh, 04Ch, 024h, 048h, 08Dh, 054h, 024h
    db 01Ch, 052h, 08Bh, 054h, 024h, 048h, 055h, 050h, 051h, 052h, 08Bh, 0CBh
    call ?j_0004895a@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 08Bh, 000h, 03Bh, 087h, 054h, 0FFh, 0FFh, 0FFh, 089h, 044h, 024h, 010h
    db 00Fh, 085h, 00Ch, 0FFh, 0FFh, 0FFh, 05Eh, 05Dh, 05Bh, 05Fh, 083h, 0C4h, 02Ch, 0C2h, 010h, 000h
?d_00235150@@YAXXZ ENDP
_TEXT$d00635150 ENDS
_TEXT SEGMENT

; ghidra: FUN_00635320  retail @ 0x00235320 size 68
public ?d_00235320@@YAXXZ
?d_00235320@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 87h, 54h, 0FFh, 0FFh, 0FFh, 8Bh, 30h, 3Bh, 0F0h, 74h, 2Ah
    db 8Bh, 46h, 08h, 85h, 0C0h, 74h, 19h, 8Bh, 80h, 04h, 02h, 00h, 00h, 8Bh, 88h, 40h
    db 01h, 00h, 00h, 85h, 0C9h, 74h, 09h, 0E8h, 0BFh, 22h, 0DFh, 0FFh, 84h, 0C0h, 75h, 0Fh
    db 8Bh, 36h, 3Bh, 0B7h, 54h, 0FFh, 0FFh, 0FFh, 75h, 0D6h, 5Fh, 32h, 0C0h, 5Eh, 0C3h, 5Fh
    db 0B0h, 01h, 5Eh, 0C3h
?d_00235320@@YAXXZ ENDP

; ghidra: FUN_00635380  retail @ 0x00235380 size 118
public ?d_00235380@@YAXXZ
?d_00235380@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 07h, 0FFh, 50h, 40h, 8Bh, 87h, 54h, 0FFh
    db 0FFh, 0FFh, 8Bh, 30h, 3Bh, 0F0h, 74h, 56h, 53h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 5Eh, 08h, 8Bh, 17h, 8Dh, 44h, 24h, 0Ch, 50h, 53h, 8Dh, 4Ch, 24h, 24h, 51h
    db 8Bh, 0CFh, 0FFh, 52h, 1Ch, 8Bh, 10h, 89h, 54h, 24h, 10h, 8Bh, 48h, 04h, 89h, 4Ch
    db 24h, 14h, 8Bh, 50h, 08h, 6Ah, 00h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CBh, 89h, 54h
    db 24h, 20h, 0E8h, 44h, 0Eh, 0DEh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CBh, 0E8h, 0C2h
    db 45h, 0E0h, 0FFh, 8Bh, 36h, 3Bh, 0B7h, 54h, 0FFh, 0FFh, 0FFh, 75h, 0B3h, 5Bh, 5Fh, 5Eh
    db 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_00235380@@YAXXZ ENDP

; ghidra: FUN_00635420  retail @ 0x00235420 size 196
public ?d_00235420@@YAXXZ
?d_00235420@@YAXXZ PROC
    db 83h, 0ECh, 4Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 07h, 0FFh, 50h, 40h, 8Bh, 44h, 24h, 58h
    db 8Bh, 08h, 8Bh, 50h, 04h, 89h, 4Ch, 24h, 24h, 8Bh, 48h, 08h, 89h, 54h, 24h, 28h
    db 8Bh, 50h, 0Ch, 89h, 4Ch, 24h, 2Ch, 8Bh, 48h, 10h, 89h, 54h, 24h, 30h, 8Bh, 50h
    db 14h, 89h, 4Ch, 24h, 34h, 8Bh, 48h, 18h, 89h, 54h, 24h, 38h, 8Bh, 50h, 1Ch, 89h
    db 4Ch, 24h, 3Ch, 8Bh, 48h, 20h, 89h, 54h, 24h, 40h, 8Bh, 50h, 24h, 89h, 4Ch, 24h
    db 44h, 8Bh, 48h, 28h, 89h, 54h, 24h, 48h, 8Bh, 50h, 2Ch, 8Bh, 87h, 54h, 0FFh, 0FFh
    db 0FFh, 89h, 4Ch, 24h, 4Ch, 89h, 54h, 24h, 50h, 8Bh, 30h, 3Bh, 0F0h, 74h, 4Dh, 53h
    db 8Bh, 5Eh, 08h, 8Bh, 07h, 8Dh, 4Ch, 24h, 0Ch, 51h, 53h, 8Dh, 54h, 24h, 24h, 52h
    db 8Bh, 0CFh, 0FFh, 50h, 1Ch, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 4Ch, 24h
    db 10h, 89h, 4Ch, 24h, 34h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0CBh, 89h, 54h, 24h, 18h
    db 89h, 44h, 24h, 1Ch, 89h, 54h, 24h, 48h, 89h, 44h, 24h, 58h, 0E8h, 78h, 0E8h, 0DEh
    db 0FFh, 8Bh, 36h, 3Bh, 0B7h, 54h, 0FFh, 0FFh, 0FFh, 75h, 0B5h, 5Bh, 5Fh, 5Eh, 83h, 0C4h
    db 4Ch, 0C2h, 04h, 00h
?d_00235420@@YAXXZ ENDP

; ghidra: FUN_00635520  retail @ 0x00235520 size 145
public ?d_00235520@@YAXXZ
?d_00235520@@YAXXZ PROC
    db 83h, 0ECh, 10h, 8Bh, 41h, 20h, 53h, 83h, 0C1h, 20h, 56h, 0C7h, 44h, 24h, 08h, 00h
    db 24h, 74h, 49h, 33h, 0DBh, 0FFh, 90h, 04h, 01h, 00h, 00h, 8Bh, 30h, 8Bh, 0Eh, 3Bh
    db 0CEh, 74h, 64h, 55h, 57h, 8Bh, 7Ch, 24h, 24h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 51h, 08h, 3Bh, 0D7h, 74h, 48h, 8Dh, 42h, 38h, 8Bh, 28h, 89h, 6Ch, 24h, 14h
    db 0D9h, 44h, 24h, 14h, 0D8h, 67h, 38h, 8Bh, 68h, 04h, 8Bh, 40h, 08h, 89h, 6Ch, 24h
    db 18h, 0D9h, 44h, 24h, 18h, 0D8h, 67h, 3Ch, 89h, 44h, 24h, 1Ch, 0D9h, 0C0h, 0D8h, 0C9h
    db 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 54h, 24h, 10h, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Ah, 08h, 0D9h, 5Ch, 24h, 10h, 8Bh, 0DAh, 0EBh, 02h, 0DDh, 0D8h, 8Bh
    db 09h, 3Bh, 0CEh, 75h, 0ABh, 5Fh, 5Dh, 5Eh, 8Bh, 0C3h, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h
    db 00h
?d_00235520@@YAXXZ ENDP

; ghidra: FUN_00635a30  retail @ 0x00235A30 size 145
public ?d_00235a30@@YAXXZ
?d_00235a30@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 9Ch, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 60h, 5Eh, 5Fh, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 7Dh, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 0FDh, 51h, 0DFh, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_00235a30@@YAXXZ ENDP

; ghidra: FUN_00635cd0  retail @ 0x00235CD0 size 53
public ?d_00235cd0@@YAXXZ
?d_00235cd0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 2Ch, 8Bh, 44h, 24h, 08h, 8Bh, 10h, 89h, 11h
    db 56h, 83h, 0C0h, 04h, 57h, 83h, 0C1h, 04h, 8Bh, 0D0h, 8Bh, 3Ah, 8Bh, 0F1h, 89h, 3Eh
    db 8Bh, 7Ah, 04h, 89h, 7Eh, 04h, 8Bh, 52h, 08h, 89h, 56h, 08h, 8Bh, 40h, 0Ch, 5Fh
    db 89h, 41h, 0Ch, 5Eh, 0C3h
?d_00235cd0@@YAXXZ ENDP

; ghidra: FUN_00635d20  retail @ 0x00235D20 size 35
public ?d_00235d20@@YAXXZ
?d_00235d20@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 81h, 0C1h, 40h, 02h, 00h, 00h, 51h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 24h, 1Eh, 65h, 00h, 8Bh, 0C6h, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_00235d20@@YAXXZ ENDP

; ghidra: FUN_006368c0  retail @ 0x002368C0 size 90
public ?d_002368c0@@YAXXZ
?d_002368c0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 74h, 24h, 10h, 8Bh, 86h, 14h, 04h, 00h, 00h, 50h, 8Bh
    db 0CEh, 0E8h, 0EAh, 0A0h, 61h, 00h, 85h, 0C0h, 74h, 3Bh, 53h, 8Bh, 1Dh, 84h, 93h, 35h
    db 01h, 57h, 8Bh, 7Ch, 24h, 20h, 50h, 0FFh, 0D3h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h
    db 8Dh, 44h, 24h, 18h, 50h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CFh, 0E8h, 0Fh, 32h, 0DDh
    db 0FFh, 8Bh, 86h, 14h, 04h, 00h, 00h, 50h, 8Bh, 0CEh, 0E8h, 0B1h, 0A0h, 61h, 00h, 85h
    db 0C0h, 75h, 0D3h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 08h, 0C3h
?d_002368c0@@YAXXZ ENDP

; ghidra: FUN_00636930  retail @ 0x00236930 size 99
public ?d_00236930@@YAXXZ
?d_00236930@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 8Bh, 87h, 14h, 04h, 00h, 00h, 50h, 8Bh
    db 0CFh, 0E8h, 7Ah, 0A0h, 61h, 00h, 85h, 0C0h, 74h, 44h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 0FFh
    db 50h, 0FFh, 15h, 84h, 93h, 35h, 01h, 8Bh, 75h, 00h, 6Ah, 0Ch, 8Bh, 0D8h, 0E8h, 0DDh
    db 7Bh, 5Fh, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 08h, 85h, 0C9h, 74h, 02h, 89h, 19h, 8Bh
    db 4Eh, 04h, 89h, 48h, 04h, 89h, 30h, 89h, 01h, 89h, 46h, 04h, 8Bh, 87h, 14h, 04h
    db 00h, 00h, 50h, 8Bh, 0CFh, 0E8h, 36h, 0A0h, 61h, 00h, 85h, 0C0h, 75h, 0C2h, 5Fh, 5Eh
    db 5Dh, 5Bh, 0C3h
?d_00236930@@YAXXZ ENDP

; ghidra: FUN_006369c0  retail @ 0x002369C0 size 154
public ?d_002369c0@@YAXXZ
?d_002369c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 38h, 01h, 00h, 00h, 39h, 00h, 75h, 04h, 33h, 0C0h, 5Eh
    db 0C3h, 8Bh, 8Eh, 38h, 01h, 00h, 00h, 8Bh, 01h, 33h, 0D2h, 3Bh, 0C1h, 74h, 08h, 90h
    db 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 68h, 0CFh, 03h, 00h, 00h, 68h, 50h, 0EBh, 0Ah
    db 01h, 4Ah, 52h, 6Ah, 00h, 0E8h, 0B4h, 0B1h, 0DCh, 0FFh, 8Bh, 8Eh, 38h, 01h, 00h, 00h
    db 8Bh, 09h, 83h, 0C4h, 10h, 85h, 0C0h, 7Eh, 0Ch, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 48h, 8Bh, 09h, 75h, 0FBh, 8Bh, 49h, 08h, 8Bh, 86h, 2Ch, 01h, 00h, 00h, 8Bh, 76h
    db 04h, 0C1h, 0E1h, 04h, 03h, 0C8h, 8Bh, 86h, 24h, 02h, 00h, 00h, 8Bh, 0B6h, 28h, 02h
    db 00h, 00h, 3Bh, 0C6h, 74h, 0Fh, 8Bh, 09h, 8Bh, 10h, 3Bh, 0Ah, 74h, 0Bh, 83h, 0C0h
    db 04h, 3Bh, 0C6h, 75h, 0F3h, 33h, 0C0h, 5Eh, 0C3h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 83h
    db 0C2h, 04h, 52h, 0E8h, 08h, 1Bh, 0DFh, 0FFh, 5Eh, 0C3h
?d_002369c0@@YAXXZ ENDP

; ghidra: FUN_00636b10  retail @ 0x00236B10 size 65
public ?d_00236b10@@YAXXZ
?d_00236b10@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 8Bh, 47h, 74h, 8Bh, 0F1h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 4Eh, 30h, 89h, 44h, 24h, 1Ch, 0E8h
    db 0C5h, 2Eh, 0E1h, 0FFh, 8Bh, 86h, 3Ch, 0FFh, 0FFh, 0FFh, 8Dh, 8Eh, 3Ch, 0FFh, 0FFh, 0FFh
    db 6Ah, 00h, 57h, 0FFh, 90h, 90h, 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h
    db 00h
?d_00236b10@@YAXXZ ENDP

; ghidra: FUN_00636c10  retail @ 0x00236C10 size 115
public ?d_00236c10@@YAXXZ
?d_00236c10@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 8Bh, 0F9h, 8Bh, 87h, 54h, 0FFh, 0FFh, 0FFh, 8Bh
    db 30h, 3Bh, 0F0h, 74h, 17h, 8Bh, 4Eh, 08h, 53h, 0E8h, 88h, 0Bh, 0DDh, 0FFh, 84h, 0C0h
    db 75h, 49h, 8Bh, 36h, 3Bh, 0B7h, 54h, 0FFh, 0FFh, 0FFh, 75h, 0E9h, 8Bh, 47h, 30h, 8Bh
    db 70h, 08h, 3Bh, 0F0h, 74h, 2Dh, 8Bh, 46h, 10h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h
    db 0E8h, 0FEh, 85h, 0DEh, 0FFh, 53h, 8Bh, 0C8h, 0E8h, 59h, 0Bh, 0DDh, 0FFh, 84h, 0C0h, 75h
    db 1Ah, 56h, 0E8h, 09h, 4Ch, 5Fh, 00h, 8Bh, 0F0h, 8Bh, 47h, 30h, 83h, 0C4h, 04h, 3Bh
    db 0F0h, 75h, 0D3h, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 0C2h, 04h, 00h, 5Fh, 5Eh, 0B0h, 01h, 5Bh
    db 0C2h, 04h, 00h
?d_00236c10@@YAXXZ ENDP

; ghidra: FUN_00636ca0  retail @ 0x00236CA0 size 292
public ?d_00236ca0@@YAXXZ
?d_00236ca0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0D9h, 8Bh, 83h, 54h, 0FFh
    db 0FFh, 0FFh, 8Bh, 8Bh, 24h, 0FFh, 0FFh, 0FFh, 57h, 8Bh, 38h, 55h, 0C7h, 44h, 24h, 14h
    db 0A4h, 70h, 7Dh, 3Fh, 0C7h, 44h, 24h, 18h, 0A4h, 70h, 7Dh, 3Fh, 0C7h, 44h, 24h, 1Ch
    db 0A4h, 70h, 7Dh, 3Fh, 0E8h, 0A5h, 3Ch, 0DEh, 0FFh, 3Bh, 0BBh, 54h, 0FFh, 0FFh, 0FFh, 74h
    db 3Eh, 8Bh, 77h, 08h, 55h, 8Bh, 0CEh, 0E8h, 0CAh, 0Ah, 0DDh, 0FFh, 84h, 0C0h, 74h, 25h
    db 55h, 8Bh, 0CEh, 0E8h, 86h, 3Ch, 0DEh, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 85h
    db 0C0h, 74h, 12h, 6Ah, 0Fh, 6Ah, 04h, 6Ah, 04h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0C8h
    db 0E8h, 8Ch, 35h, 0E0h, 0FFh, 8Bh, 3Fh, 3Bh, 0BBh, 54h, 0FFh, 0FFh, 0FFh, 75h, 0C2h, 8Bh
    db 43h, 30h, 8Bh, 78h, 08h, 3Bh, 0F8h, 0Fh, 84h, 8Dh, 00h, 00h, 00h, 8Dh, 49h, 00h
    db 8Bh, 77h, 10h, 85h, 0F6h, 74h, 48h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h
    db 8Bh, 0C6h, 0F7h, 0F5h, 8Bh, 81h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h
    db 13h, 39h, 72h, 04h, 74h, 0Ah, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 33h, 0F6h, 0EBh, 0Bh
    db 85h, 0D2h, 75h, 04h, 33h, 0F6h, 0EBh, 03h, 8Bh, 72h, 08h, 8Bh, 6Ch, 24h, 20h, 55h
    db 8Bh, 0CEh, 0E8h, 0F7h, 3Bh, 0DEh, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 85h, 0C0h
    db 74h, 12h, 6Ah, 0Fh, 6Ah, 04h, 6Ah, 04h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0C8h, 0E8h
    db 0FDh, 34h, 0E0h, 0FFh, 57h, 0E8h, 0C6h, 4Ah, 5Fh, 00h, 8Bh, 0F8h, 8Bh, 43h, 30h, 83h
    db 0C4h, 04h, 3Bh, 0F8h, 0Fh, 85h, 76h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 04h, 00h
?d_00236ca0@@YAXXZ ENDP

; ghidra: FUN_00636f50  retail @ 0x00236F50 size 152
public ?d_00236f50@@YAXXZ
?d_00236f50@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 43h, 18h, 56h, 8Bh, 30h, 3Bh, 0F0h, 57h, 74h, 11h, 8Bh, 0FFh
    db 8Bh, 4Eh, 08h, 8Bh, 01h, 0FFh, 50h, 48h, 8Bh, 36h, 3Bh, 73h, 18h, 75h, 0F1h, 8Bh
    db 83h, 0F4h, 00h, 00h, 00h, 8Bh, 78h, 08h, 3Bh, 0F8h, 74h, 68h, 55h, 8Dh, 49h, 00h
    db 8Bh, 77h, 10h, 85h, 0F6h, 74h, 47h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h
    db 8Bh, 0C6h, 0F7h, 0F5h, 8Bh, 89h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 91h, 85h, 0D2h, 74h
    db 1Dh, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 10h, 85h, 0D2h
    db 74h, 0Ch, 8Bh, 4Ah, 08h, 85h, 0C9h, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 48h, 57h, 0E8h
    db 9Ch, 48h, 5Fh, 00h, 8Bh, 0F8h, 8Bh, 83h, 0F4h, 00h, 00h, 00h, 83h, 0C4h, 04h, 3Bh
    db 0F8h, 75h, 9Dh, 5Dh, 5Fh, 5Eh, 5Bh, 0C3h
?d_00236f50@@YAXXZ ENDP

; ghidra: FUN_006371c0  retail @ 0x002371C0 size 195
public ?d_002371c0@@YAXXZ
?d_002371c0@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 83h, 3Ch, 0FFh, 0FFh, 0FFh, 56h, 8Dh, 8Bh, 3Ch, 0FFh, 0FFh, 0FFh
    db 57h, 0FFh, 90h, 04h, 01h, 00h, 00h, 8Bh, 0F8h, 8Bh, 07h, 8Bh, 30h, 3Bh, 0F0h, 74h
    db 20h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 13h, 8Bh, 15h, 14h, 0F2h, 2Eh, 01h, 8Dh, 48h
    db 38h, 51h, 8Bh, 4Ah, 0Ch, 50h, 0E8h, 4Ch, 0C4h, 0DDh, 0FFh, 8Bh, 36h, 3Bh, 37h, 75h
    db 0E0h, 8Bh, 43h, 30h, 8Bh, 78h, 08h, 3Bh, 0F8h, 74h, 74h, 55h, 8Dh, 64h, 24h, 00h
    db 8Bh, 77h, 10h, 85h, 0F6h, 74h, 55h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h
    db 8Bh, 0C6h, 0F7h, 0F5h, 8Bh, 81h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h
    db 2Bh, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 1Eh, 85h, 0D2h
    db 74h, 1Ah, 8Bh, 52h, 08h, 85h, 0D2h, 74h, 13h, 8Dh, 4Ah, 38h, 51h, 52h, 8Bh, 15h
    db 14h, 0F2h, 2Eh, 01h, 8Bh, 4Ah, 0Ch, 0E8h, 0DBh, 0C3h, 0DDh, 0FFh, 57h, 0E8h, 0FEh, 45h
    db 5Fh, 00h, 8Bh, 0F8h, 8Bh, 43h, 30h, 83h, 0C4h, 04h, 3Bh, 0F8h, 75h, 92h, 5Dh, 5Fh
    db 5Eh, 5Bh, 0C3h
?d_002371c0@@YAXXZ ENDP

; ghidra: FUN_006372c0  retail @ 0x002372C0 size 994
_TEXT ENDS
_TEXT$d006372c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x006372C0 size 994
public ?d_002372c0@@YAXXZ
?d_002372c0@@YAXXZ PROC
    db 083h, 0ECh, 038h, 08Bh, 041h, 030h, 053h, 055h, 056h, 057h, 08Bh, 078h, 008h, 033h, 0DBh, 03Bh
    db 0F8h, 089h, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 024h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h
    db 028h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 02Ch, 000h, 000h, 000h, 000h, 089h, 05Ch, 024h
    db 014h, 0C7h, 044h, 024h, 01Ch, 001h, 000h, 000h, 000h, 00Fh, 084h, 095h, 000h, 000h, 000h, 090h
    db 08Bh, 077h, 010h, 085h, 0F6h, 074h, 06Fh, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 081h, 0B4h, 000h, 000h, 000h, 08Bh, 0A9h, 0B8h, 000h, 000h, 000h, 02Bh, 0E8h, 033h, 0D2h
    db 0C1h, 0FDh, 002h, 08Bh, 0C6h, 0F7h, 0F5h, 08Bh, 081h, 0B4h, 000h, 000h, 000h, 08Bh, 014h, 090h
    db 085h, 0D2h, 074h, 045h, 039h, 072h, 004h, 074h, 008h, 08Bh, 012h, 085h, 0D2h, 075h, 0F5h, 0EBh
    db 038h, 085h, 0D2h, 074h, 034h, 08Bh, 072h, 008h, 085h, 0F6h, 074h, 02Dh, 08Bh, 0CEh
    call ?j_00018223@@YAXXZ
    db 084h, 0C0h, 074h, 022h, 0D9h, 044h, 024h, 024h, 043h, 0D8h, 046h, 038h, 0D9h, 05Ch, 024h, 024h
    db 0D9h, 044h, 024h, 028h, 0D8h, 046h, 03Ch, 0D9h, 05Ch, 024h, 028h, 0D9h, 044h, 024h, 02Ch, 0D8h
    db 046h, 040h, 0D9h, 05Ch, 024h, 02Ch, 057h
    call ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
    db 08Bh, 04Ch, 024h, 01Ch, 08Bh, 0F8h, 08Bh, 041h, 030h, 083h, 0C4h, 004h, 03Bh, 0F8h, 00Fh, 085h
    db 070h, 0FFh, 0FFh, 0FFh, 089h, 05Ch, 024h, 014h, 08Bh, 091h, 03Ch, 0FFh, 0FFh, 0FFh, 081h, 0C1h
    db 03Ch, 0FFh, 0FFh, 0FFh, 0FFh, 092h, 004h, 001h, 000h, 000h, 0D9h, 044h, 024h, 024h, 0D9h, 044h
    db 024h, 02Ch, 08Bh, 0F0h, 08Bh, 016h, 08Bh, 002h, 03Bh, 0C2h, 089h, 074h, 024h, 020h, 074h, 02Bh
    db 0D9h, 044h, 024h, 028h, 08Bh, 048h, 008h, 085h, 0C9h, 074h, 012h, 0D9h, 0CAh, 043h, 0D8h, 041h
    db 038h, 0D9h, 0CAh, 0D8h, 041h, 03Ch, 0D9h, 0C9h, 0D8h, 041h, 040h, 0D9h, 0C9h, 08Bh, 000h, 03Bh
    db 0C2h, 075h, 0E1h, 0D9h, 05Ch, 024h, 028h, 089h, 05Ch, 024h, 014h, 085h, 0DBh, 00Fh, 08Eh, 0A5h
    db 002h, 000h, 000h, 0DBh, 044h, 024h, 014h, 08Bh, 06Ch, 024h, 04Ch, 08Bh, 045h, 038h, 08Bh, 04Dh
    db 03Ch, 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 055h, 040h, 089h, 044h, 024h, 03Ch, 08Bh, 044h, 024h, 018h, 08Bh, 040h, 030h, 089h, 04Ch
    db 024h, 040h, 089h, 054h, 024h, 044h, 08Bh, 078h, 008h, 03Bh, 0F8h, 0C7h, 044h, 024h, 010h, 000h
    db 000h, 080h, 0BFh, 0D9h, 0C0h, 0D8h, 0CBh, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 028h, 0D8h
    db 0C9h, 0D9h, 05Ch, 024h, 028h, 0D9h, 0C9h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 02Ch, 0DDh, 0D8h, 0DDh
    db 0D8h, 00Fh, 084h, 034h, 001h, 000h, 000h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 077h, 010h
    db 085h, 0F6h, 00Fh, 084h, 005h, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 081h, 0B4h, 000h, 000h, 000h, 08Bh, 099h, 0B8h, 000h, 000h, 000h, 02Bh, 0D8h, 033h, 0D2h
    db 0C1h, 0FBh, 002h, 08Bh, 0C6h, 0F7h, 0F3h, 08Bh, 089h, 0B4h, 000h, 000h, 000h, 08Bh, 014h, 091h
    db 085h, 0D2h, 00Fh, 084h, 0D7h, 000h, 000h, 000h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 039h
    db 072h, 004h, 074h, 00Bh, 08Bh, 012h, 085h, 0D2h, 075h, 0F5h, 0E9h, 0C0h, 000h, 000h, 000h, 085h
    db 0D2h, 00Fh, 084h, 0B8h, 000h, 000h, 000h, 08Bh, 072h, 008h, 085h, 0F6h, 00Fh, 084h, 0ADh, 000h
    db 000h, 000h, 08Bh, 0CEh
    call ?j_00018223@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 09Eh, 000h, 000h, 000h, 08Bh, 056h, 038h, 08Bh, 046h, 03Ch, 08Bh, 04Eh
    db 040h, 089h, 054h, 024h, 030h, 0D9h, 044h, 024h, 030h, 0D8h, 064h, 024h, 024h, 089h, 044h, 024h
    db 034h, 0D9h, 044h, 024h, 034h, 089h, 04Ch, 024h, 038h, 0D8h, 064h, 024h, 028h, 0D9h, 044h, 024h
    db 038h, 0D8h, 064h, 024h, 02Ch, 0D9h, 044h, 024h, 010h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 01Bh, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh
    db 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D8h, 05Ch, 024h, 010h, 0DFh, 0E0h, 0F6h, 0C4h, 005h
    db 07Ah, 03Fh, 0D9h, 0C0h, 08Bh, 04Ch, 024h, 038h, 0D8h, 0C9h, 08Bh, 054h, 024h, 030h, 08Bh, 044h
    db 024h, 034h, 0D9h, 0C2h, 0D8h, 0CBh, 089h, 04Ch, 024h, 044h, 08Bh, 0CEh, 089h, 054h, 024h, 03Ch
    db 0DEh, 0C1h, 089h, 044h, 024h, 040h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 010h
    db 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h
    call ?j_0003a391@@YAXXZ
    db 089h, 044h, 024h, 01Ch, 0EBh, 006h, 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h, 057h
    call ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 0F8h, 08Bh, 042h, 030h, 083h, 0C4h, 004h, 03Bh, 0F8h, 00Fh, 085h
    db 0D6h, 0FEh, 0FFh, 0FFh, 08Bh, 074h, 024h, 020h, 08Bh, 006h, 08Bh, 038h, 03Bh, 0F8h, 00Fh, 084h
    db 0E8h, 000h, 000h, 000h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 077h, 008h, 08Bh, 046h, 038h
    db 089h, 044h, 024h, 030h, 08Bh, 04Eh, 03Ch, 08Bh, 085h, 004h, 002h, 000h, 000h, 089h, 04Ch, 024h
    db 034h, 08Bh, 056h, 040h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 089h, 054h, 024h, 038h, 08Bh, 080h, 0B8h, 001h, 000h, 000h, 08Bh, 059h, 00Ch, 055h, 050h, 08Bh
    db 0CDh
    call ?j_0003a391@@YAXXZ
    db 050h, 08Dh, 054h, 024h, 03Ch, 052h, 08Bh, 0CBh
    call ?j_0003b359@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 089h, 000h, 000h, 000h, 0D9h, 044h, 024h, 030h, 0D8h, 064h, 024h, 024h
    db 0D9h, 044h, 024h, 034h, 0D8h, 064h, 024h, 028h, 0D9h, 044h, 024h, 038h, 0D8h, 064h, 024h, 02Ch
    db 0D9h, 044h, 024h, 010h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 01Bh, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh
    db 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D8h, 05Ch, 024h, 010h, 0DFh, 0E0h, 0F6h, 0C4h, 005h
    db 07Ah, 03Fh, 0D9h, 0C0h, 08Bh, 04Ch, 024h, 034h, 0D8h, 0C9h, 08Bh, 044h, 024h, 030h, 08Bh, 054h
    db 024h, 038h, 0D9h, 0C2h, 0D8h, 0CBh, 089h, 04Ch, 024h, 040h, 08Bh, 0CEh, 089h, 044h, 024h, 03Ch
    db 0DEh, 0C1h, 089h, 054h, 024h, 044h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 010h
    db 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h
    call ?j_0003a391@@YAXXZ
    db 089h, 044h, 024h, 01Ch, 0EBh, 006h, 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h, 08Bh, 044h, 024h, 020h
    db 08Bh, 03Fh, 03Bh, 038h, 00Fh, 085h, 01Eh, 0FFh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 03Ch, 051h, 08Bh
    db 0CDh
    call ?j_0003a1a7@@YAXXZ
    db 08Bh, 054h, 024h, 01Ch, 052h, 08Bh, 0CDh
    call ?j_00035e0e@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 038h, 0C2h, 004h, 000h, 05Fh, 0DDh, 0D8h, 05Eh, 0DDh, 0D8h
    db 05Dh, 05Bh, 083h, 0C4h, 038h, 0C2h, 004h, 000h
?d_002372c0@@YAXXZ ENDP
_TEXT$d006372c0 ENDS
_TEXT SEGMENT

; ghidra: FUN_006377a0  retail @ 0x002377A0 size 336
public ?d_002377a0@@YAXXZ
?d_002377a0@@YAXXZ PROC
    db 51h, 0A1h, 48h, 0D7h, 2Eh, 01h, 53h, 8Bh, 58h, 0Ch, 55h, 56h, 8Bh, 0F1h, 57h, 8Bh
    db 0BEh, 24h, 0FFh, 0FFh, 0FFh, 85h, 0FFh, 0C6h, 44h, 24h, 13h, 00h, 74h, 4Eh, 8Bh, 0CFh
    db 0E8h, 5Fh, 90h, 0DEh, 0FFh, 3Bh, 0C3h, 75h, 43h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 28h
    db 8Bh, 0D8h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 76h, 0Ah, 00h, 00h, 84h, 0C9h, 74h
    db 26h, 85h, 0DBh, 74h, 27h, 8Bh, 16h, 57h, 8Bh, 0CEh, 0FFh, 92h, 64h, 01h, 00h, 00h
    db 50h, 8Bh, 06h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 90h, 50h, 01h, 00h, 00h, 50h, 8Bh, 0CBh
    db 0E8h, 0F2h, 6Fh, 0E0h, 0FFh, 0EBh, 05h, 0C6h, 44h, 24h, 13h, 01h, 8Bh, 86h, 54h, 0FFh
    db 0FFh, 0FFh, 8Bh, 18h, 3Bh, 0D8h, 74h, 3Bh, 8Bh, 7Bh, 08h, 85h, 0FFh, 74h, 2Ah, 8Bh
    db 17h, 8Bh, 0CFh, 0FFh, 52h, 28h, 8Bh, 0E8h, 85h, 0EDh, 74h, 1Dh, 8Ah, 44h, 24h, 13h
    db 84h, 0C0h, 74h, 15h, 8Bh, 06h, 57h, 8Bh, 0CEh, 0FFh, 90h, 64h, 01h, 00h, 00h, 50h
    db 6Ah, 01h, 8Bh, 0CDh, 0E8h, 0AEh, 6Fh, 0E0h, 0FFh, 8Bh, 1Bh, 3Bh, 9Eh, 54h, 0FFh, 0FFh
    db 0FFh, 75h, 0C5h, 8Bh, 46h, 30h, 8Bh, 58h, 08h, 3Bh, 0D8h, 0Fh, 84h, 89h, 00h, 00h
    db 00h, 8Bh, 7Bh, 10h, 85h, 0FFh, 74h, 6Ch, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h
    db 0B4h, 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh
    db 02h, 8Bh, 0C7h, 0F7h, 0F5h, 8Bh, 89h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 91h, 85h, 0D2h
    db 74h, 42h, 39h, 7Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 35h, 85h
    db 0D2h, 74h, 31h, 8Bh, 7Ah, 08h, 85h, 0FFh, 74h, 2Ah, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h
    db 28h, 8Bh, 0E8h, 85h, 0EDh, 74h, 1Dh, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 15h, 8Bh
    db 06h, 57h, 8Bh, 0CEh, 0FFh, 90h, 64h, 01h, 00h, 00h, 50h, 6Ah, 01h, 8Bh, 0CDh, 0E8h
    db 23h, 6Fh, 0E0h, 0FFh, 53h, 0E8h, 96h, 3Fh, 5Fh, 00h, 8Bh, 0D8h, 8Bh, 46h, 30h, 83h
    db 0C4h, 04h, 3Bh, 0D8h, 0Fh, 85h, 77h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h
?d_002377a0@@YAXXZ ENDP

; ghidra: FUN_00637d70  retail @ 0x00237D70 size 170
_TEXT ENDS
_TEXT$d00637d70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00637D70 size 170
public ?d_00237d70@@YAXXZ
?d_00237d70@@YAXXZ PROC
    db 056h, 08Bh, 0F1h, 08Bh, 086h, 03Ch, 0FFh, 0FFh, 0FFh, 08Dh, 08Eh, 03Ch, 0FFh, 0FFh, 0FFh, 0FFh
    db 090h, 004h, 001h, 000h, 000h, 08Bh, 008h, 08Bh, 001h, 03Bh, 0C1h, 075h, 053h, 08Bh, 046h, 034h
    db 085h, 0C0h, 075h, 002h, 05Eh, 0C3h, 08Bh, 04Eh, 030h, 08Bh, 071h, 008h, 068h, 064h, 010h, 000h
    db 000h, 068h
    dd g_Va010AEB50
    db 048h, 050h, 06Ah, 000h
    call ?j_00001bae@@YAXXZ
    db 083h, 0C4h, 010h, 085h, 0C0h, 074h, 019h, 057h, 08Bh, 0F8h, 08Dh, 0A4h, 024h, 000h, 000h, 000h
    db 000h, 056h
    call ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
    db 083h, 0C4h, 004h, 04Fh, 08Bh, 0F0h, 075h, 0F2h, 05Fh, 08Bh, 056h, 010h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 05Eh, 0C3h, 033h, 0D2h, 03Bh, 0C1h, 08Bh, 0F0h, 074h, 007h, 08Bh, 000h, 042h, 03Bh, 0C1h, 075h
    db 0F9h, 068h, 06Ah, 010h, 000h, 000h, 068h
    dd g_Va010AEB50
    db 04Ah, 052h, 06Ah, 000h
    call ?j_00001bae@@YAXXZ
    db 083h, 0C4h, 010h, 085h, 0C0h, 074h, 00Ch, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 048h, 08Bh
    db 036h, 075h, 0FBh, 08Bh, 046h, 008h, 05Eh, 0C3h
?d_00237d70@@YAXXZ ENDP
_TEXT$d00637d70 ENDS
_TEXT SEGMENT

; ghidra: FUN_00637e50  retail @ 0x00237E50 size 281
public ?d_00237e50@@YAXXZ
?d_00237e50@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 8Bh, 0E9h, 8Bh, 85h, 3Ch, 0FFh, 0FFh, 0FFh, 56h, 8Dh, 8Dh
    db 3Ch, 0FFh, 0FFh, 0FFh, 57h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h
    db 10h, 00h, 00h, 00h, 00h, 0FFh, 90h, 04h, 01h, 00h, 00h, 8Bh, 0D8h, 8Bh, 03h, 8Bh
    db 38h, 3Bh, 0F8h, 74h, 3Bh, 8Bh, 77h, 08h, 85h, 0F6h, 74h, 2Eh, 6Ah, 00h, 8Bh, 0CEh
    db 0E8h, 0EAh, 9Bh, 0DFh, 0FFh, 85h, 0C0h, 74h, 21h, 6Ah, 00h, 56h, 8Bh, 0C8h, 0E8h, 0C8h
    db 0D4h, 0DDh, 0FFh, 0D8h, 54h, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah, 0D9h, 5Ch
    db 24h, 10h, 89h, 74h, 24h, 14h, 0EBh, 02h, 0DDh, 0D8h, 8Bh, 3Fh, 3Bh, 3Bh, 75h, 0C5h
    db 8Bh, 45h, 30h, 8Bh, 78h, 08h, 3Bh, 0F8h, 0Fh, 84h, 8Fh, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 77h, 10h, 85h, 0F6h, 74h, 70h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 8Bh, 99h, 0B8h, 00h, 00h, 00h, 2Bh, 0D8h, 33h, 0D2h, 0C1h, 0FBh, 02h
    db 8Bh, 0C6h, 0F7h, 0F3h, 8Bh, 89h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 91h, 85h, 0D2h, 74h
    db 46h, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 39h, 85h, 0D2h
    db 74h, 35h, 8Bh, 72h, 08h, 85h, 0F6h, 74h, 2Eh, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 5Dh, 9Bh
    db 0DFh, 0FFh, 85h, 0C0h, 74h, 21h, 6Ah, 00h, 56h, 8Bh, 0C8h, 0E8h, 3Bh, 0D4h, 0DDh, 0FFh
    db 0D8h, 54h, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah, 0D9h, 5Ch, 24h, 10h, 89h
    db 74h, 24h, 14h, 0EBh, 02h, 0DDh, 0D8h, 57h, 0E8h, 23h, 39h, 5Fh, 00h, 8Bh, 0F8h, 8Bh
    db 45h, 30h, 83h, 0C4h, 04h, 3Bh, 0F8h, 0Fh, 85h, 73h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C3h
?d_00237e50@@YAXXZ ENDP

; ghidra: FUN_006381c0  retail @ 0x002381C0 size 206
public ?d_002381c0@@YAXXZ
?d_002381c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0DAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 33h, 0DBh, 6Ah, 0Ch, 8Bh, 0F1h, 89h, 5Ch
    db 24h, 0Ch, 0E8h, 59h, 63h, 5Fh, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 08h, 8Bh, 06h, 8Dh, 4Ch, 24h, 08h, 51h, 8Bh, 0CEh, 89h, 5Ch, 24h, 18h
    db 0FFh, 90h, 0F0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 01h, 33h, 0D2h, 3Bh, 0C1h
    db 74h, 0Ch, 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 83h, 0FAh, 01h, 73h, 26h, 8Dh, 4Ch
    db 24h, 08h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 5Eh, 64h, 0DDh, 0FFh, 5Eh
    db 32h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 04h, 00h, 8Bh, 0B6h, 20h, 0FFh, 0FFh, 0FFh, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h
    db 81h, 0C6h, 48h, 02h, 00h, 00h, 56h, 0E8h, 04h, 03h, 0DFh, 0FFh, 3Bh, 0C3h, 74h, 08h
    db 39h, 44h, 24h, 1Ch, 75h, 02h, 0B3h, 01h, 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 14h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 14h, 64h, 0DDh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Eh, 8Ah, 0C3h
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_002381c0@@YAXXZ ENDP

; ghidra: FUN_006382d0  retail @ 0x002382D0 size 543
_TEXT ENDS
_TEXT$d006382d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x006382D0 size 543
public ?d_002382d0@@YAXXZ
?d_002382d0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0100DA80
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 014h, 08Bh, 054h, 024h, 024h, 053h, 055h, 033h, 0C0h, 056h, 089h, 044h, 024h, 014h, 057h, 089h
    db 044h, 024h, 01Ch, 08Bh, 0F1h, 089h, 044h, 024h, 020h, 08Bh, 086h, 024h, 0FFh, 0FFh, 0FFh, 08Bh
    db 080h, 03Ch, 002h, 000h, 000h, 033h, 0EDh, 055h, 08Dh, 04Ch, 024h, 01Ch, 051h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 050h, 052h
    call ?j_0004494a@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 08Fh, 0FCh, 001h, 000h, 000h, 03Bh, 0CDh, 089h, 07Ch, 024h, 014h, 074h, 009h
    db 08Bh, 001h, 0FFh, 050h, 068h, 03Bh, 0C5h, 075h, 021h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 057h
    call ?j_0001d0de@@YAXXZ
    db 08Bh, 04Ch, 024h, 024h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h
    db 0C4h, 020h, 0C2h, 004h, 000h, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 092h, 0E8h, 001h, 000h, 000h, 08Bh
    db 0D8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0C0h, 001h, 000h, 000h, 06Ah, 00Ch, 089h, 06Ch, 024h
    db 014h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 089h, 000h, 089h, 040h, 004h, 083h, 0C4h, 004h, 089h, 044h, 024h, 010h, 08Bh, 016h, 08Dh, 044h
    db 024h, 010h, 050h, 08Bh, 0CEh, 089h, 06Ch, 024h, 030h, 0FFh, 052h, 044h, 08Bh, 08Eh, 0D8h, 000h
    db 000h, 000h, 051h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 074h, 036h, 08Bh, 04Ch, 024h, 010h, 08Bh, 001h, 03Bh, 0C1h, 074h, 02Ch
    db 08Dh, 09Bh, 000h, 000h, 000h, 000h, 039h, 068h, 008h, 074h, 008h, 08Bh, 000h, 03Bh, 0C1h, 075h
    db 0F5h, 0EBh, 019h, 03Bh, 0C1h, 074h, 015h, 08Bh, 008h, 08Bh, 050h, 004h, 06Ah, 00Ch, 089h, 00Ah
    db 050h, 089h, 051h, 004h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Bh, 08Eh, 024h, 0FFh, 0FFh, 0FFh, 08Bh, 011h, 0FFh, 052h, 028h, 08Ah, 088h
    db 0ACh, 003h, 000h, 000h, 084h, 0C9h, 08Bh, 08Eh, 024h, 0FFh, 0FFh, 0FFh, 057h, 00Fh, 095h, 044h
    db 024h, 038h
    call ?j_00012913@@YAXXZ
    db 08Bh, 08Eh, 0E8h, 000h, 000h, 000h, 08Bh, 083h, 0E4h, 000h, 000h, 000h, 08Dh, 0BBh, 0E4h, 000h
    db 000h, 000h, 051h, 08Bh, 0CFh, 0FFh, 090h, 044h, 001h, 000h, 000h, 08Bh, 017h, 08Dh, 044h, 024h
    db 010h, 050h, 08Bh, 0CFh, 0FFh, 052h, 074h, 085h, 0EDh, 074h, 068h, 08Bh, 04Ch, 024h, 010h, 08Bh
    db 001h, 033h, 0D2h, 03Bh, 0C1h, 074h, 04Ch, 08Bh, 000h, 042h, 03Bh, 0C1h, 075h, 0F9h, 085h, 0D2h
    db 076h, 041h, 08Dh, 0B3h, 010h, 002h, 000h, 000h, 08Ah, 01Eh, 0C7h, 044h, 024h, 018h
    dd ??_7?$LatchRestore@_N@@6B@
    db 089h, 074h, 024h, 020h, 088h, 05Ch, 024h, 01Ch, 0C6h, 006h, 001h, 08Bh, 04Ch, 024h, 010h, 08Bh
    db 001h, 08Bh, 040h, 008h, 085h, 0C0h, 0C6h, 044h, 024h, 02Ch, 001h, 074h, 00Dh, 08Bh, 017h, 06Ah
    db 001h, 050h, 055h, 08Bh, 0CFh, 0FFh, 052h, 070h, 033h, 0EDh, 0C6h, 044h, 024h, 02Ch, 000h, 088h
    db 01Eh, 085h, 0EDh, 074h, 00Ch, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 055h
    call ?j_0001d0de@@YAXXZ
    db 08Bh, 007h, 08Bh, 0CFh, 0FFh, 090h, 0BCh, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 014h, 051h, 08Bh
    db 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001d0de@@YAXXZ
    db 08Ah, 044h, 024h, 034h, 084h, 0C0h, 074h, 00Ah, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 092h, 0D0h, 000h
    db 000h, 000h, 08Dh, 04Ch, 024h, 010h, 0C7h, 044h, 024h, 02Ch, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_0000e68d@@YAXXZ
    db 08Bh, 04Ch, 024h, 024h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 020h, 0C2h, 004h, 000h
?d_002382d0@@YAXXZ ENDP
_TEXT$d006382d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00638580  retail @ 0x00238580 size 197
public ?d_00238580@@YAXXZ
?d_00238580@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0DAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 0Ch, 8Bh, 0F1h, 0C7h, 44h, 24h, 08h, 00h
    db 00h, 00h, 00h, 0E8h, 98h, 5Fh, 5Fh, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 04h, 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 14h, 00h, 00h, 00h, 00h, 0FFh, 90h, 0F0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 04h, 8Bh
    db 01h, 33h, 0D2h, 3Bh, 0C1h, 74h, 4Bh, 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 83h, 0FAh
    db 01h, 72h, 3Fh, 8Bh, 0B6h, 20h, 0FFh, 0FFh, 0FFh, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 81h
    db 0C6h, 48h, 02h, 00h, 00h, 56h, 0E8h, 65h, 0FFh, 0DEh, 0FFh, 85h, 0C0h, 74h, 23h, 8Dh
    db 4Ch, 24h, 04h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 7Dh, 60h, 0DDh, 0FFh
    db 0B0h, 01h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 5Ah
    db 60h, 0DDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 32h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
?d_00238580@@YAXXZ ENDP

; ghidra: FUN_00638680  retail @ 0x00238680 size 146
public ?d_00238680@@YAXXZ
?d_00238680@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 08h, 85h, 0EDh, 56h, 8Bh, 0F1h, 75h, 07h, 5Eh, 32h, 0C0h, 5Dh
    db 0C2h, 04h, 00h, 8Bh, 86h, 00h, 01h, 00h, 00h, 85h, 0C0h, 74h, 0EFh, 8Bh, 0Dh, 98h
    db 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 57h, 3Bh, 96h, 04h, 01h, 00h, 00h, 72h, 08h, 5Fh
    db 5Eh, 32h, 0C0h, 5Dh, 0C2h, 04h, 00h, 50h, 0E8h, 96h, 6Bh, 0DEh, 0FFh, 8Bh, 0F8h, 85h
    db 0FFh, 74h, 0ECh, 8Bh, 86h, 24h, 0FFh, 0FFh, 0FFh, 53h, 50h, 8Bh, 0CDh, 0E8h, 1Bh, 0B6h
    db 0E0h, 0FFh, 0D8h, 1Dh, 0B8h, 0EBh, 0Ah, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 04h, 0B3h
    db 01h, 0EBh, 02h, 32h, 0DBh, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0B8h, 73h, 0DDh, 0FFh, 6Ah, 00h
    db 8Bh, 0CDh, 8Bh, 0F0h, 0E8h, 0ADh, 73h, 0DDh, 0FFh, 3Bh, 0C6h, 75h, 09h, 5Bh, 5Fh, 5Eh
    db 0B0h, 01h, 5Dh, 0C2h, 04h, 00h, 84h, 0DBh, 5Bh, 5Fh, 5Eh, 0Fh, 95h, 0C0h, 5Dh, 0C2h
    db 04h, 00h
?d_00238680@@YAXXZ ENDP

; ghidra: FUN_00638740  retail @ 0x00238740 size 232
public ?d_00238740@@YAXXZ
?d_00238740@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 0DAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 41h, 04h, 8Bh
    db 0A8h, 30h, 02h, 00h, 00h, 8Bh, 80h, 34h, 02h, 00h, 00h, 3Bh, 0E8h, 89h, 44h, 24h
    db 10h, 74h, 63h, 8Bh, 7Ch, 24h, 28h, 85h, 0FFh, 8Bh, 45h, 00h, 89h, 44h, 24h, 14h
    db 74h, 09h, 0Fh, 0B7h, 5Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0DBh, 0BFh, 8Bh, 38h
    db 07h, 01h, 8Bh, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh, 02h, 33h, 0D2h
    db 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh
    db 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h
    db 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 74h, 33h, 8Bh, 44h, 24h, 10h, 83h
    db 0C5h, 04h, 3Bh, 0E8h, 75h, 9Dh, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 59h, 0F1h, 64h, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 8Bh, 4Ch, 24h
    db 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 8Dh, 4Ch
    db 24h, 28h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 31h, 0F1h, 64h, 00h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 44h, 24h, 14h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_00238740@@YAXXZ ENDP

; ghidra: FUN_00638a60  retail @ 0x00238A60 size 65
public ?d_00238a60@@YAXXZ
?d_00238a60@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 3Ch, 0FFh, 0FFh, 0FFh, 8Dh, 8Eh, 3Ch, 0FFh, 0FFh, 0FFh, 0FFh
    db 90h, 04h, 01h, 00h, 00h, 8Bh, 00h, 8Bh, 08h, 3Bh, 0C8h, 74h, 05h, 8Bh, 41h, 08h
    db 5Eh, 0C3h, 8Bh, 76h, 30h, 8Bh, 46h, 08h, 3Bh, 0C6h, 74h, 11h, 8Bh, 48h, 10h, 51h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 0B8h, 67h, 0DEh, 0FFh, 5Eh, 0C3h, 33h, 0C0h, 5Eh
    db 0C3h
?d_00238a60@@YAXXZ ENDP

; ghidra: FUN_00638ac0  retail @ 0x00238AC0 size 19
public ?d_00238ac0@@YAXXZ
?d_00238ac0@@YAXXZ PROC
    db 8Bh, 81h, 0D8h, 00h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 81h, 67h
    db 0DEh, 0FFh, 0C3h
?d_00238ac0@@YAXXZ ENDP

; ghidra: FUN_00638bc0  retail @ 0x00238BC0 size 261
public ?d_00238bc0@@YAXXZ
?d_00238bc0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 8Bh, 6Ch, 24h, 14h, 33h, 0D2h, 3Bh, 0EAh, 8Bh, 0D9h, 75h
    db 23h, 8Bh, 8Bh, 54h, 0FFh, 0FFh, 0FFh, 8Bh, 01h, 3Bh, 0C1h, 74h, 0Ah, 8Dh, 49h, 00h
    db 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 8Bh, 43h, 34h, 5Dh, 03h, 0C2h, 5Bh, 83h, 0C4h
    db 08h, 0C2h, 04h, 00h, 8Bh, 83h, 54h, 0FFh, 0FFh, 0FFh, 56h, 8Bh, 30h, 3Bh, 0F0h, 57h
    db 8Bh, 0BBh, 24h, 0FFh, 0FFh, 0FFh, 89h, 54h, 24h, 10h, 89h, 7Ch, 24h, 14h, 74h, 25h
    db 8Bh, 0CFh, 0E8h, 0Dh, 7Ch, 0DEh, 0FFh, 50h, 8Bh, 46h, 08h, 50h, 8Bh, 0CDh, 0E8h, 11h
    db 4Eh, 0DEh, 0FFh, 84h, 0C0h, 74h, 04h, 0FFh, 44h, 24h, 10h, 8Bh, 36h, 3Bh, 0B3h, 54h
    db 0FFh, 0FFh, 0FFh, 75h, 0DBh, 8Bh, 43h, 30h, 8Bh, 78h, 08h, 3Bh, 0F8h, 74h, 78h, 90h
    db 8Bh, 77h, 10h, 85h, 0F6h, 74h, 5Eh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h
    db 8Bh, 0C6h, 0F7h, 0F5h, 8Bh, 89h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 91h, 85h, 0D2h, 74h
    db 34h, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 27h, 85h, 0D2h
    db 74h, 23h, 8Bh, 72h, 08h, 85h, 0F6h, 74h, 1Ch, 8Bh, 4Ch, 24h, 14h, 0E8h, 92h, 7Bh
    db 0DEh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 50h, 56h, 0E8h, 97h, 4Dh, 0DEh, 0FFh, 84h, 0C0h, 74h
    db 04h, 0FFh, 44h, 24h, 10h, 57h, 0E8h, 0C5h, 2Bh, 5Fh, 00h, 8Bh, 0F8h, 8Bh, 43h, 30h
    db 83h, 0C4h, 04h, 3Bh, 0F8h, 75h, 89h, 8Bh, 44h, 24h, 10h, 5Fh, 5Eh, 5Dh, 5Bh, 83h
    db 0C4h, 08h, 0C2h, 04h, 00h
?d_00238bc0@@YAXXZ ENDP

; ghidra: FUN_00639600  retail @ 0x00239600 size 185
public ?d_00239600@@YAXXZ
?d_00239600@@YAXXZ PROC
    db 83h, 0ECh, 14h, 8Bh, 81h, 24h, 0FFh, 0FFh, 0FFh, 8Bh, 50h, 38h, 83h, 0C0h, 38h, 8Bh
    db 40h, 04h, 53h, 55h, 56h, 89h, 44h, 24h, 18h, 8Bh, 81h, 54h, 0FFh, 0FFh, 0FFh, 57h
    db 8Bh, 38h, 3Bh, 0F8h, 89h, 54h, 24h, 18h, 89h, 44h, 24h, 14h, 74h, 77h, 8Bh, 51h
    db 30h, 8Bh, 0DAh, 8Bh, 6Bh, 04h, 89h, 54h, 24h, 10h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 77h, 08h, 8Bh, 56h, 74h, 8Bh, 0C5h, 85h, 0C0h, 8Bh, 0CBh, 74h, 1Eh, 8Bh, 0FFh
    db 39h, 50h, 10h, 7Ch, 07h, 8Bh, 0C8h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch, 85h
    db 0C0h, 75h, 0EDh, 3Bh, 0CBh, 74h, 05h, 3Bh, 51h, 10h, 7Dh, 02h, 8Bh, 0CBh, 3Bh, 4Ch
    db 24h, 10h, 75h, 29h, 0D9h, 44h, 24h, 18h, 0D8h, 66h, 38h, 0D9h, 44h, 24h, 1Ch, 0D8h
    db 66h, 3Ch, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D8h, 1Dh, 0C4h, 0FAh
    db 07h, 01h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 0DDh, 0D8h, 74h, 12h, 8Bh, 3Fh, 3Bh
    db 7Ch, 24h, 14h, 75h, 9Bh, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 83h, 0C4h, 14h, 0C3h, 5Fh
    db 5Eh, 5Dh, 32h, 0C0h, 5Bh, 83h, 0C4h, 14h, 0C3h
?d_00239600@@YAXXZ ENDP

; ghidra: FUN_006396f0  retail @ 0x002396F0 size 480
public ?d_002396f0@@YAXXZ
?d_002396f0@@YAXXZ PROC
    db 83h, 0ECh, 2Ch, 53h, 55h, 8Bh, 0E9h, 8Bh, 85h, 54h, 0FFh, 0FFh, 0FFh, 56h, 8Bh, 30h
    db 3Bh, 0F0h, 57h, 74h, 4Dh, 8Dh, 0BDh, 9Ch, 00h, 00h, 00h, 0EBh, 03h, 8Dh, 49h, 00h
    db 33h, 0C0h, 89h, 44h, 24h, 14h, 89h, 44h, 24h, 18h, 89h, 44h, 24h, 1Ch, 89h, 44h
    db 24h, 20h, 89h, 44h, 24h, 24h, 89h, 44h, 24h, 28h, 89h, 44h, 24h, 2Ch, 8Dh, 4Ch
    db 24h, 14h, 89h, 44h, 24h, 30h, 51h, 8Bh, 4Eh, 08h, 89h, 44h, 24h, 38h, 57h, 89h
    db 44h, 24h, 40h, 0E8h, 0A5h, 0FEh, 0DCh, 0FFh, 8Bh, 36h, 3Bh, 0B5h, 54h, 0FFh, 0FFh, 0FFh
    db 75h, 0BEh, 8Bh, 85h, 0C8h, 00h, 00h, 00h, 8Dh, 0BDh, 0C4h, 00h, 00h, 00h, 33h, 0DBh
    db 3Bh, 0C3h, 74h, 3Dh, 8Bh, 17h, 8Bh, 72h, 04h, 3Bh, 0F3h, 74h, 22h, 8Dh, 49h, 00h
    db 8Bh, 46h, 0Ch, 50h, 8Bh, 0CFh, 0E8h, 0D9h, 0B2h, 0DFh, 0FFh, 8Bh, 5Eh, 08h, 6Ah, 18h
    db 56h, 0E8h, 6Ah, 4Eh, 5Fh, 00h, 83h, 0C4h, 08h, 85h, 0DBh, 8Bh, 0F3h, 75h, 0E1h, 8Bh
    db 07h, 89h, 40h, 08h, 8Bh, 0Fh, 89h, 59h, 04h, 8Bh, 07h, 89h, 40h, 0Ch, 89h, 5Fh
    db 04h, 8Bh, 4Dh, 6Ch, 3Bh, 0CBh, 8Bh, 35h, 98h, 08h, 2Fh, 01h, 75h, 06h, 89h, 5Ch
    db 24h, 10h, 0EBh, 46h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 0BEh, 0B8h, 00h, 00h, 00h
    db 2Bh, 0F8h, 33h, 0D2h, 0C1h, 0FFh, 02h, 8Bh, 0C1h, 0F7h, 0F7h, 8Bh, 86h, 0B4h, 00h, 00h
    db 00h, 8Bh, 14h, 90h, 3Bh, 0D3h, 74h, 15h, 39h, 4Ah, 04h, 74h, 0Ch, 8Bh, 12h, 3Bh
    db 0D3h, 75h, 0F5h, 89h, 5Ch, 24h, 10h, 0EBh, 11h, 3Bh, 0D3h, 75h, 06h, 89h, 5Ch, 24h
    db 10h, 0EBh, 07h, 8Bh, 4Ah, 08h, 89h, 4Ch, 24h, 10h, 8Bh, 7Dh, 70h, 3Bh, 0FBh, 75h
    db 04h, 33h, 0F6h, 0EBh, 45h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 8Eh, 0B8h, 00h, 00h
    db 00h, 2Bh, 0C8h, 33h, 0D2h, 0C1h, 0F9h, 02h, 8Bh, 0C7h, 0F7h, 0F1h, 8Bh, 86h, 0B4h, 00h
    db 00h, 00h, 8Bh, 14h, 90h, 3Bh, 0D3h, 74h, 1Ah, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 39h, 7Ah, 04h, 74h, 0Ah, 8Bh, 12h, 3Bh, 0D3h, 75h, 0F5h, 33h, 0F6h, 0EBh, 0Bh, 3Bh
    db 0D3h, 75h, 04h, 33h, 0F6h, 0EBh, 03h, 8Bh, 72h, 08h, 8Bh, 4Ch, 24h, 10h, 3Bh, 0CBh
    db 74h, 38h, 33h, 0D2h, 89h, 54h, 24h, 14h, 89h, 54h, 24h, 18h, 89h, 54h, 24h, 1Ch
    db 89h, 54h, 24h, 20h, 89h, 54h, 24h, 24h, 89h, 54h, 24h, 28h, 89h, 54h, 24h, 2Ch
    db 89h, 54h, 24h, 30h, 89h, 54h, 24h, 34h, 8Dh, 44h, 24h, 14h, 89h, 54h, 24h, 38h
    db 50h, 8Dh, 55h, 74h, 52h, 0E8h, 63h, 0FDh, 0DCh, 0FFh, 3Bh, 0F3h, 74h, 3Ah, 33h, 0C0h
    db 89h, 44h, 24h, 14h, 89h, 44h, 24h, 18h, 89h, 44h, 24h, 1Ch, 89h, 44h, 24h, 20h
    db 89h, 44h, 24h, 24h, 89h, 44h, 24h, 28h, 89h, 44h, 24h, 2Ch, 8Dh, 4Ch, 24h, 14h
    db 89h, 44h, 24h, 30h, 51h, 8Dh, 55h, 74h, 89h, 44h, 24h, 38h, 52h, 8Bh, 0CEh, 89h
    db 44h, 24h, 40h, 0E8h, 25h, 0FDh, 0DCh, 0FFh, 5Fh, 5Eh, 89h, 5Dh, 6Ch, 5Dh, 5Bh, 83h
?d_002396f0@@YAXXZ ENDP

; ghidra: FUN_00639af0  retail @ 0x00239AF0 size 330
public ?d_00239af0@@YAXXZ
?d_00239af0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 87h, 3Ch, 0FFh, 0FFh, 0FFh, 8Dh, 8Fh
    db 3Ch, 0FFh, 0FFh, 0FFh, 89h, 7Ch, 24h, 0Ch, 0FFh, 90h, 04h, 01h, 00h, 00h, 8Bh, 97h
    db 24h, 0FFh, 0FFh, 0FFh, 8Bh, 0E8h, 8Bh, 44h, 24h, 18h, 8Bh, 00h, 85h, 0C0h, 8Bh, 4Dh
    db 00h, 8Bh, 31h, 89h, 54h, 24h, 10h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 50h, 0E8h, 98h, 12h, 0E0h, 0FFh, 8Bh
    db 0Dh, 0E4h, 07h, 2Fh, 01h, 50h, 0E8h, 9Bh, 0CDh, 0DEh, 0FFh, 8Bh, 0Dh, 0E4h, 07h, 2Fh
    db 01h, 50h, 0E8h, 63h, 40h, 0DEh, 0FFh, 85h, 0C0h, 0Fh, 84h, 0B2h, 00h, 00h, 00h, 0F6h
    db 40h, 0Ch, 40h, 0Fh, 85h, 0A8h, 00h, 00h, 00h, 3Bh, 75h, 00h, 53h, 8Bh, 5Ch, 24h
    db 20h, 74h, 39h, 85h, 0DBh, 8Bh, 7Eh, 08h, 74h, 16h, 8Bh, 4Ch, 24h, 14h, 0E8h, 0A1h
    db 6Ch, 0DEh, 0FFh, 50h, 57h, 8Bh, 0CBh, 0E8h, 0A8h, 3Eh, 0DEh, 0FFh, 84h, 0C0h, 74h, 11h
    db 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 1Ch, 51h, 52h, 8Bh, 0CFh, 0E8h, 0B5h, 0DEh, 0DFh
    db 0FFh, 8Bh, 36h, 3Bh, 75h, 00h, 75h, 0CBh, 8Bh, 7Ch, 24h, 10h, 8Bh, 47h, 30h, 8Bh
    db 78h, 08h, 3Bh, 0F8h, 74h, 56h, 8Bh, 47h, 10h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h
    db 0E8h, 8Eh, 56h, 0DEh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 74h, 2Bh, 85h, 0DBh, 74h, 16h, 8Bh
    db 4Ch, 24h, 14h, 0E8h, 4Ch, 6Ch, 0DEh, 0FFh, 50h, 56h, 8Bh, 0CBh, 0E8h, 53h, 3Eh, 0DEh
    db 0FFh, 84h, 0C0h, 74h, 11h, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 1Ch, 51h, 52h, 8Bh
    db 0CEh, 0E8h, 60h, 0DEh, 0DFh, 0FFh, 57h, 0E8h, 74h, 1Ch, 5Fh, 00h, 8Bh, 0F8h, 8Bh, 44h
    db 24h, 14h, 8Bh, 48h, 30h, 83h, 0C4h, 04h, 3Bh, 0F9h, 75h, 0AAh, 8Bh, 7Ch, 24h, 10h
    db 5Bh, 8Bh, 8Fh, 24h, 0FFh, 0FFh, 0FFh, 0E8h, 0D1h, 66h, 0DEh, 0FFh, 85h, 0C0h, 5Fh, 5Eh
    db 5Dh, 74h, 11h, 8Bh, 4Ch, 24h, 14h, 8Bh, 54h, 24h, 0Ch, 51h, 52h, 8Bh, 0C8h, 0E8h
    db 51h, 0F9h, 0E0h, 0FFh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_00239af0@@YAXXZ ENDP

; ghidra: FUN_00639c90  retail @ 0x00239C90 size 287
public ?d_00239c90@@YAXXZ
?d_00239c90@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0E9h, 8Bh, 85h, 3Ch, 0FFh, 0FFh, 0FFh, 56h, 8Dh, 8Dh, 3Ch, 0FFh
    db 0FFh, 0FFh, 57h, 0FFh, 90h, 04h, 01h, 00h, 00h, 8Bh, 8Dh, 24h, 0FFh, 0FFh, 0FFh, 8Bh
    db 0D8h, 8Bh, 03h, 8Bh, 30h, 3Bh, 0F0h, 89h, 4Ch, 24h, 10h, 74h, 38h, 8Dh, 49h, 00h
    db 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 8Bh, 7Eh, 08h, 74h, 18h, 8Bh, 4Ch, 24h, 10h, 0E8h
    db 50h, 6Bh, 0DEh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 50h, 57h, 0E8h, 55h, 3Dh, 0DEh, 0FFh, 84h
    db 0C0h, 74h, 0Ch, 8Bh, 54h, 24h, 18h, 52h, 8Bh, 0CFh, 0E8h, 0ADh, 52h, 0DEh, 0FFh, 8Bh
    db 36h, 3Bh, 33h, 75h, 0CBh, 8Bh, 45h, 30h, 8Bh, 78h, 08h, 3Bh, 0F8h, 0Fh, 84h, 89h
    db 00h, 00h, 00h, 8Bh, 77h, 10h, 85h, 0F6h, 74h, 6Ch, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 8Bh, 81h, 0B4h, 00h, 00h, 00h, 8Bh, 99h, 0B8h, 00h, 00h, 00h, 2Bh, 0D8h, 33h, 0D2h
    db 0C1h, 0FBh, 02h, 8Bh, 0C6h, 0F7h, 0F3h, 8Bh, 81h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h
    db 85h, 0D2h, 74h, 42h, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh
    db 35h, 85h, 0D2h, 74h, 31h, 8Bh, 72h, 08h, 85h, 0F6h, 74h, 2Ah, 8Bh, 5Ch, 24h, 1Ch
    db 85h, 0DBh, 74h, 16h, 8Bh, 4Ch, 24h, 10h, 0E8h, 0C7h, 6Ah, 0DEh, 0FFh, 50h, 56h, 8Bh
    db 0CBh, 0E8h, 0CEh, 3Ch, 0DEh, 0FFh, 84h, 0C0h, 74h, 0Ch, 8Bh, 4Ch, 24h, 18h, 51h, 8Bh
    db 0CEh, 0E8h, 26h, 52h, 0DEh, 0FFh, 57h, 0E8h, 0F4h, 1Ah, 5Fh, 00h, 8Bh, 0F8h, 8Bh, 45h
    db 30h, 83h, 0C4h, 04h, 3Bh, 0F8h, 0Fh, 85h, 77h, 0FFh, 0FFh, 0FFh, 8Bh, 8Dh, 24h, 0FFh
    db 0FFh, 0FFh, 0E8h, 56h, 65h, 0DEh, 0FFh, 85h, 0C0h, 5Fh, 5Eh, 5Dh, 5Bh, 74h, 0Ch, 8Bh
    db 54h, 24h, 08h, 52h, 8Bh, 0C8h, 0E8h, 0A9h, 39h, 0DFh, 0FFh, 59h, 0C2h, 08h, 00h
?d_00239c90@@YAXXZ ENDP

; ghidra: FUN_00639e00  retail @ 0x00239E00 size 603
public ?d_00239e00@@YAXXZ
?d_00239e00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E6h, 0DAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 6Ch, 0A1h, 14h, 0F2h, 2Eh, 01h, 53h, 57h, 8Bh
    db 0B9h, 24h, 0FFh, 0FFh, 0FFh, 89h, 7Ch, 24h, 08h, 6Ah, 00h, 89h, 4Ch, 24h, 18h, 8Bh
    db 48h, 0Ch, 83h, 0C7h, 38h, 57h, 32h, 0DBh, 0E8h, 0E8h, 2Fh, 0E0h, 0FFh, 84h, 0C0h, 75h
    db 19h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 57h, 0E8h, 49h, 8Ch, 0DDh, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 0F2h, 01h, 00h, 00h, 0B3h, 01h, 33h, 0D2h, 89h, 54h, 24h, 24h
    db 8Bh, 0C2h, 55h, 89h, 54h, 24h, 30h, 0Dh, 00h, 00h, 00h, 08h, 56h, 89h, 54h, 24h
    db 38h, 89h, 44h, 24h, 30h, 68h, 0B8h, 0D8h, 2Eh, 01h, 8Dh, 44h, 24h, 30h, 89h, 54h
    db 24h, 40h, 50h, 8Dh, 4Ch, 24h, 4Ch, 89h, 54h, 24h, 48h, 0E8h, 6Dh, 0E4h, 0DFh, 0FFh
    db 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h, 50h, 6Ah, 01h, 68h, 00h, 00h, 16h, 43h, 57h, 0C7h
    db 84h, 24h, 94h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 0F1h, 87h, 7Bh, 00h, 8Bh
    db 0E8h, 83h, 0CEh, 0FFh, 85h, 0EDh, 89h, 0B4h, 24h, 84h, 00h, 00h, 00h, 0C7h, 44h, 24h
    db 44h, 5Ch, 3Bh, 08h, 01h, 0Fh, 84h, 67h, 01h, 00h, 00h, 0F6h, 05h, 0D0h, 0FAh, 2Eh
    db 01h, 01h, 75h, 36h, 8Bh, 0Dh, 0D0h, 0FAh, 2Eh, 01h, 0B8h, 01h, 00h, 00h, 00h, 0Bh
    db 0C8h, 89h, 0Dh, 0D0h, 0FAh, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 0A4h, 0Ch
    db 09h, 01h, 89h, 84h, 24h, 88h, 00h, 00h, 00h, 0E8h, 0D9h, 0Eh, 0E0h, 0FFh, 0A3h, 0CCh
    db 0FAh, 2Eh, 01h, 89h, 0B4h, 24h, 84h, 00h, 00h, 00h, 8Bh, 0Dh, 0CCh, 0FAh, 2Eh, 01h
    db 51h, 8Bh, 0CDh, 0E8h, 0Bh, 0Fh, 0DFh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 0CBh, 00h
    db 00h, 00h, 8Bh, 0CEh, 0E8h, 86h, 0E3h, 0DDh, 0FFh, 85h, 0C0h, 0Fh, 84h, 0BCh, 00h, 00h
    db 00h, 8Bh, 0CEh, 33h, 0DBh, 0C7h, 44h, 24h, 14h, 00h, 24h, 74h, 49h, 33h, 0EDh, 0E8h
    db 6Bh, 0E3h, 0DDh, 0FFh, 85h, 0C0h, 7Eh, 6Fh, 55h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 0CEh
    db 0E8h, 60h, 0F9h, 0DFh, 0FFh, 0D9h, 44h, 24h, 20h, 0D8h, 27h, 0D9h, 5Ch, 24h, 20h, 0D9h
    db 44h, 24h, 24h, 0D8h, 67h, 04h, 0D9h, 5Ch, 24h, 24h, 0D9h, 44h, 24h, 28h, 0D8h, 67h
    db 08h, 0D9h, 5Ch, 24h, 28h, 0D9h, 44h, 24h, 20h, 0D9h, 0E1h, 0D9h, 44h, 24h, 24h, 0D9h
    db 0E1h, 0D9h, 0C1h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 02h, 0D9h, 0C9h, 0D8h, 0Dh
    db 6Ch, 3Bh, 08h, 01h, 0DEh, 0C1h, 0D8h, 54h, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 08h, 0D9h, 5Ch, 24h, 14h, 8Bh, 0DDh, 0EBh, 02h, 0DDh, 0D8h, 8Bh, 0CEh, 45h, 0E8h, 0FCh
    db 0E2h, 0DDh, 0FFh, 3Bh, 0E8h, 7Ch, 91h, 53h, 8Dh, 44h, 24h, 24h, 50h, 8Bh, 0CEh, 0E8h
    db 62h, 0A7h, 0DEh, 0FFh, 0D9h, 00h, 53h, 0D9h, 0E0h, 8Dh, 4Ch, 24h, 30h, 0D9h, 5Ch, 24h
    db 18h, 51h, 8Bh, 0CEh, 0E8h, 4Dh, 0A7h, 0DEh, 0FFh, 0D9h, 40h, 04h, 0D9h, 0E0h, 8Dh, 4Ch
    db 24h, 14h, 0D9h, 5Ch, 24h, 18h, 0E8h, 67h, 0CEh, 0E0h, 0FFh, 0EBh, 30h, 84h, 0DBh, 75h
    db 39h, 8Bh, 55h, 44h, 8Bh, 6Dh, 04h, 85h, 0EDh, 89h, 54h, 24h, 14h, 75h, 04h, 33h
    db 0C0h, 0EBh, 10h, 8Bh, 4Dh, 04h, 85h, 0C9h, 74h, 07h, 0E8h, 0ACh, 82h, 0DCh, 0FFh, 0EBh
    db 02h, 8Bh, 0C5h, 0D9h, 44h, 24h, 14h, 0D8h, 80h, 04h, 04h, 00h, 00h, 51h, 8Bh, 4Ch
    db 24h, 14h, 0D9h, 1Ch, 24h, 0E8h, 7Bh, 0F9h, 0DFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 0C6h, 40h
    db 04h, 01h, 8Bh, 4Ch, 24h, 10h, 6Ah, 01h, 51h, 8Bh, 4Ch, 24h, 24h, 81h, 0C1h, 1Ch
    db 0FFh, 0FFh, 0FFh, 0E8h, 92h, 0B7h, 0DDh, 0FFh, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 74h, 5Fh, 5Bh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 78h, 0C3h
?d_00239e00@@YAXXZ ENDP

; ghidra: FUN_0063a1d0  retail @ 0x0023A1D0 size 116
public ?d_0023a1d0@@YAXXZ
?d_0023a1d0@@YAXXZ PROC
    db 55h, 8Bh, 0E9h, 8Bh, 85h, 54h, 0FFh, 0FFh, 0FFh, 56h, 8Bh, 30h, 3Bh, 0F0h, 74h, 5Fh
    db 53h, 57h, 8Bh, 4Dh, 30h, 8Bh, 7Eh, 08h, 8Bh, 41h, 04h, 85h, 0C0h, 8Bh, 36h, 8Bh
    db 5Fh, 74h, 8Bh, 0D1h, 74h, 13h, 39h, 58h, 10h, 7Ch, 07h, 8Bh, 0D0h, 8Bh, 40h, 08h
    db 0EBh, 03h, 8Bh, 40h, 0Ch, 85h, 0C0h, 75h, 0EDh, 3Bh, 0D1h, 74h, 05h, 3Bh, 5Ah, 10h
    db 7Dh, 02h, 8Bh, 0D1h, 3Bh, 55h, 30h, 75h, 1Ch, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 85h
    db 0C9h, 74h, 12h, 8Bh, 54h, 24h, 18h, 8Bh, 01h, 52h, 8Bh, 54h, 24h, 18h, 52h, 0FFh
    db 90h, 0E0h, 01h, 00h, 00h, 3Bh, 0B5h, 54h, 0FFh, 0FFh, 0FFh, 75h, 0A5h, 5Fh, 5Bh, 5Eh
    db 5Dh, 0C2h, 08h, 00h
?d_0023a1d0@@YAXXZ ENDP

; ghidra: FUN_0063a550  retail @ 0x0023A550 size 383
_TEXT ENDS
_TEXT$d0063a550 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0063A550 size 383
public ?d_0023a550@@YAXXZ
?d_0023a550@@YAXXZ PROC
    db 083h, 0ECh, 008h, 053h, 055h, 033h, 0C0h, 056h, 08Bh, 074h, 024h, 018h, 08Bh, 0E9h, 089h, 006h
    db 089h, 046h, 004h, 089h, 046h, 008h, 08Bh, 085h, 054h, 0FFh, 0FFh, 0FFh, 08Bh, 018h, 03Bh, 0D8h
    db 057h, 089h, 06Ch, 024h, 014h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 074h, 051h, 090h
    db 08Bh, 07Bh, 008h, 085h, 0FFh, 074h, 03Fh, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 028h, 085h, 0C0h
    db 074h, 034h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 028h, 08Bh, 0C8h
    call ?j_0003ee55@@YAXXZ
    db 0D9h, 000h, 0D8h, 006h, 0D9h, 01Eh, 0D9h, 040h, 004h, 0D8h, 046h, 004h, 0D9h, 05Eh, 004h, 0D9h
    db 040h, 008h, 0D8h, 046h, 008h, 0D9h, 05Eh, 008h, 0D9h, 044h, 024h, 010h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Ch, 024h, 010h, 08Bh, 01Bh, 03Bh, 09Dh, 054h, 0FFh, 0FFh, 0FFh, 075h, 0B0h, 08Bh, 045h
    db 030h, 08Bh, 058h, 008h, 03Bh, 0D8h, 00Fh, 084h, 0A8h, 000h, 000h, 000h, 08Bh, 0FFh, 08Bh, 07Bh
    db 010h, 085h, 0FFh, 00Fh, 084h, 081h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 081h, 0B4h, 000h, 000h, 000h, 08Bh, 0A9h, 0B8h, 000h, 000h, 000h, 02Bh, 0E8h, 033h, 0D2h
    db 0C1h, 0FDh, 002h, 08Bh, 0C7h, 0F7h, 0F5h, 08Bh, 081h, 0B4h, 000h, 000h, 000h, 08Bh, 014h, 090h
    db 085h, 0D2h, 074h, 057h, 039h, 07Ah, 004h, 074h, 008h, 08Bh, 012h, 085h, 0D2h, 075h, 0F5h, 0EBh
    db 04Ah, 085h, 0D2h, 074h, 046h, 08Bh, 07Ah, 008h, 085h, 0FFh, 074h, 03Fh, 08Bh, 017h, 08Bh, 0CFh
    db 0FFh, 052h, 028h, 085h, 0C0h, 074h, 034h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 028h, 08Bh, 0C8h
    call ?j_0003ee55@@YAXXZ
    db 0D9h, 006h, 0D8h, 000h, 0D9h, 01Eh, 0D9h, 040h, 004h, 0D8h, 046h, 004h, 0D9h, 05Eh, 004h, 0D9h
    db 040h, 008h, 0D8h, 046h, 008h, 0D9h, 05Eh, 008h, 0D9h, 044h, 024h, 010h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Ch, 024h, 010h, 053h
    call ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
    db 08Bh, 04Ch, 024h, 018h, 08Bh, 0D8h, 08Bh, 041h, 030h, 083h, 0C4h, 004h, 03Bh, 0D8h, 00Fh, 085h
    db 05Ah, 0FFh, 0FFh, 0FFh, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 010h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 00Ch, 05Fh, 05Eh, 05Dh
    db 032h, 0C0h, 05Bh, 083h, 0C4h, 008h, 0C2h, 004h, 000h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 05Fh, 0D8h, 074h, 024h, 00Ch, 0B0h, 001h, 0D9h, 0C0h, 0D8h, 00Eh, 0D9h, 01Eh, 0D9h, 0C0h, 0D8h
    db 04Eh, 004h, 0D9h, 05Eh, 004h, 0D8h, 04Eh, 008h, 0D9h, 05Eh, 008h, 05Eh, 05Dh, 05Bh, 083h, 0C4h
    db 008h, 0C2h, 004h, 000h
?d_0023a550@@YAXXZ ENDP
_TEXT$d0063a550 ENDS
_TEXT SEGMENT

; ghidra: FUN_0063a730  retail @ 0x0023A730 size 191
public ?d_0023a730@@YAXXZ
?d_0023a730@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 08h, 0DBh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 8Eh, 24h, 0FFh, 0FFh, 0FFh, 0E8h
    db 07h, 8Bh, 0DCh, 0FFh, 6Ah, 0Ch, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 0DDh
    db 3Dh, 5Fh, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 8Bh
    db 06h, 8Dh, 4Ch, 24h, 04h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h
    db 0FFh, 90h, 0F0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 04h, 8Bh, 30h, 3Bh, 0F0h, 74h, 12h
    db 8Bh, 4Eh, 08h, 0E8h, 0C3h, 8Ah, 0DCh, 0FFh, 8Bh, 36h, 8Bh, 44h, 24h, 04h, 3Bh, 0F0h
    db 75h, 0EEh, 8Bh, 30h, 3Bh, 0F0h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 17h
    db 8Bh, 0C6h, 8Bh, 36h, 6Ah, 0Ch, 50h, 0E8h, 34h, 3Eh, 5Fh, 00h, 8Bh, 44h, 24h, 0Ch
    db 83h, 0C4h, 08h, 3Bh, 0F0h, 75h, 0E9h, 89h, 00h, 8Bh, 44h, 24h, 04h, 89h, 40h, 04h
    db 8Bh, 54h, 24h, 04h, 6Ah, 0Ch, 52h, 0E8h, 14h, 3Eh, 5Fh, 00h, 8Bh, 4Ch, 24h, 10h
    db 83h, 0C4h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0023a730@@YAXXZ ENDP

; ghidra: FUN_0063a820  retail @ 0x0023A820 size 400
public ?d_0023a820@@YAXXZ
?d_0023a820@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah
    db 0Ch, 89h, 4Ah, 10h, 89h, 4Ah, 14h, 89h, 4Ah, 18h, 89h, 4Ah, 1Ch, 89h, 4Ah, 20h
    db 89h, 4Ah, 24h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh
    db 14h, 90h, 56h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 10h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 14h, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 20h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 24h, 8Bh, 0D1h, 0C1h, 0EAh, 05h, 83h, 0E1h, 1Fh
    db 0BEh, 01h, 00h, 00h, 00h, 8Dh, 14h, 90h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 28h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 30h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 34h, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 38h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 3Ch, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 40h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h
    db 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 44h, 8Bh, 0D1h, 0C1h, 0EAh, 05h, 83h, 0E1h, 1Fh
    db 0BEh, 01h, 00h, 00h, 00h, 8Dh, 14h, 90h, 0D3h, 0E6h, 09h, 32h, 5Eh, 0C2h, 40h, 00h
?d_0023a820@@YAXXZ ENDP

; ghidra: FUN_0063b4d0  retail @ 0x0023B4D0 size 176
public ?d_0023b4d0@@YAXXZ
?d_0023b4d0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0F1h, 3Bh, 1Eh, 57h
    db 74h, 3Fh, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 75h, 10h, 8Bh, 44h, 24h, 18h, 85h, 0C0h
    db 75h, 2Fh, 8Bh, 45h, 00h, 3Bh, 43h, 10h, 7Ch, 27h, 6Ah, 24h, 0E8h, 3Fh, 30h, 5Fh
    db 00h, 8Bh, 0F8h, 8Dh, 4Fh, 10h, 55h, 51h, 0E8h, 0CAh, 0C9h, 0DCh, 0FFh, 89h, 7Bh, 0Ch
    db 8Bh, 06h, 8Bh, 48h, 0Ch, 83h, 0C4h, 0Ch, 3Bh, 0D9h, 75h, 36h, 89h, 78h, 0Ch, 0EBh
    db 31h, 6Ah, 24h, 0E8h, 18h, 30h, 5Fh, 00h, 8Bh, 0F8h, 8Dh, 57h, 10h, 55h, 52h, 0E8h
    db 0A3h, 0C9h, 0DCh, 0FFh, 89h, 7Bh, 08h, 8Bh, 06h, 83h, 0C4h, 0Ch, 3Bh, 0D8h, 75h, 0Ah
    db 89h, 78h, 04h, 8Bh, 06h, 89h, 78h, 0Ch, 0EBh, 08h, 3Bh, 58h, 08h, 75h, 03h, 89h
    db 78h, 08h, 33h, 0C0h, 89h, 5Fh, 04h, 89h, 47h, 08h, 89h, 47h, 0Ch, 8Bh, 0Eh, 83h
    db 0C1h, 04h, 51h, 57h, 0E8h, 67h, 14h, 5Fh, 00h, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 40h
    db 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 89h, 38h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 14h, 00h
?d_0023b4d0@@YAXXZ ENDP

; ghidra: FUN_0063b5b0  retail @ 0x0023B5B0 size 145
public ?d_0023b5b0@@YAXXZ
?d_0023b5b0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 9Ch, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 0E0h, 02h, 5Fh, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 7Dh, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 4Dh, 0C5h, 0E0h, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_0023b5b0@@YAXXZ ENDP

; ghidra: FUN_0063b7a0  retail @ 0x0023B7A0 size 465
_TEXT ENDS
_TEXT$d0063b7a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0063B7A0 size 465
public ?d_0023b7a0@@YAXXZ
?d_0023b7a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0100DB7E
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 053h
    db 08Bh, 0D9h, 056h, 08Bh, 0B3h, 024h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 015h, 05Eh, 033h, 0C0h
    db 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h
    db 004h, 000h, 08Bh, 086h, 0FCh, 001h, 000h, 000h, 057h, 033h, 0FFh, 085h, 0C0h, 089h, 044h, 024h
    db 00Ch, 00Fh, 084h, 06Dh, 001h, 000h, 000h, 055h, 08Dh, 0ABh, 01Ch, 0FFh, 0FFh, 0FFh, 08Bh, 0CDh
    call ?j_00045a39@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 034h, 001h, 000h, 000h, 08Bh, 048h, 020h, 085h, 0C9h, 08Dh, 051h, 008h
    db 075h, 005h, 0BAh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 07Bh, 0F0h, 06Ah, 000h, 052h, 08Bh, 054h, 024h, 018h, 056h, 08Dh, 04Bh, 0F0h, 052h, 050h
    db 0FFh, 017h, 08Bh, 0F8h, 0F7h, 086h, 094h, 000h, 000h, 000h, 000h, 000h, 000h, 020h, 074h, 008h
    db 057h, 08Bh, 0CEh
    call ?j_0004966b@@YAXXZ
    db 08Bh, 086h, 070h, 003h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h, 057h
    call ?j_0003a279@@YAXXZ
    db 08Bh, 044h, 024h, 024h, 050h, 08Bh, 0CFh
    call ?bfmeTwo941F@BfmeThing941F@@QAEXPAX@Z
    db 057h, 08Bh, 0CDh
    call ?j_00017355@@YAXXZ
    db 06Ah, 018h, 08Bh, 0CEh
    call ?j_000225f7@@YAXXZ
    db 084h, 0C0h, 074h, 009h, 06Ah, 018h, 08Bh, 0CFh
    call ?j_000348ec@@YAXXZ
    db 08Bh, 08Fh, 010h, 002h, 000h, 000h, 08Bh, 086h, 010h, 002h, 000h, 000h, 08Bh, 051h, 028h, 08Bh
    db 040h, 028h, 08Bh, 00Dh
    dd ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A
    db 06Ah, 000h, 02Bh, 0C2h, 050h, 057h
    call ?j_0001697d@@YAXXZ
    db 08Bh, 013h, 06Ah, 000h, 08Dh, 086h, 024h, 002h, 000h, 000h, 050h, 08Bh, 0CBh, 0FFh, 092h, 0B0h
    db 000h, 000h, 000h, 08Bh, 0CEh
    call ?j_000202ed@@YAXXZ
    db 085h, 0C0h, 074h, 008h, 057h, 08Bh, 0C8h
    call ?j_0000a475@@YAXXZ
    db 08Ah, 00Dh
    dd ?g_Va012EFAD8@@3IA
    db 0B8h, 001h, 000h, 000h, 000h, 084h, 0C8h, 075h, 02Bh, 009h, 005h
    dd ?g_Va012EFAD8@@3IA
    db 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 068h
    dd g_Va010906AC
    db 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h
    call ?j_0003add7@@YAXXZ
    db 0A3h
    dd g_Va012EFAD4
    db 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 00Dh
    dd g_Va012EFAD4
    db 051h, 08Bh, 0CEh
    call ?j_0002ae23@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 029h, 08Bh, 015h
    dd g_Va012EFAD4
    db 052h, 08Bh, 0CFh
    call ?j_0002ae23@@YAXXZ
    db 085h, 0C0h, 074h, 017h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 059h, 03Ch, 08Bh, 056h, 020h, 02Bh, 0D3h, 052h, 052h, 08Bh, 0C8h
    call ?j_0002f3dd@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 011h, 0FFh, 052h, 068h, 08Bh, 0F0h, 085h, 0F6h, 05Dh, 074h, 013h
    db 08Bh, 006h, 06Ah, 000h, 08Bh, 0CEh, 0FFh, 050h, 010h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 0BCh
    db 001h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 0C7h, 05Fh, 05Eh, 05Bh, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 004h, 000h
?d_0023b7a0@@YAXXZ ENDP
_TEXT$d0063b7a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_0063bb90  retail @ 0x0023BB90 size 567
_TEXT ENDS
_TEXT$d0063bb90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0063BB90 size 567
public ?d_0023bb90@@YAXXZ
?d_0023bb90@@YAXXZ PROC
    db 08Bh, 044h, 024h, 004h, 083h, 0ECh, 078h, 085h, 0C0h, 053h, 08Bh, 0D9h, 00Fh, 084h, 01Eh, 002h
    db 000h, 000h, 08Ah, 00Dh
    dd g_Va012EFB0C
    db 055h, 0B8h, 001h, 000h, 000h, 000h, 084h, 0C8h, 056h, 057h, 075h, 059h, 068h, 0E5h, 000h, 000h
    db 000h, 068h, 0E4h, 000h, 000h, 000h, 06Ah, 025h, 08Bh, 03Dh
    dd g_Va012EFB0C
    db 068h, 019h, 001h, 000h, 000h, 068h, 0BEh, 000h, 000h, 000h, 06Ah, 040h, 068h, 0A0h, 000h, 000h
    db 000h, 068h, 0EEh, 000h, 000h, 000h, 068h, 0BFh, 000h, 000h, 000h, 068h, 0C3h, 000h, 000h, 000h
    db 068h, 02Fh, 001h, 000h, 000h, 06Ah, 03Fh, 068h, 0C2h, 000h, 000h, 000h, 068h, 0C1h, 000h, 000h
    db 000h, 06Ah, 03Eh, 00Bh, 0F8h, 06Ah, 000h, 0B9h
    dd g_Va012EFADC
    db 089h, 03Dh
    dd g_Va012EFB0C
    call ?j_0001b10d@@YAXXZ
    db 08Bh, 043h, 008h, 0B9h, 00Ah, 000h, 000h, 000h, 0BEh
    dd g_Va012EFADC
    db 08Dh, 07Ch, 024h, 038h, 0F3h, 0A5h, 08Bh, 054h, 024h, 03Ch, 08Bh, 05Ch, 024h, 048h, 08Bh, 06Ch
    db 024h, 044h, 08Dh, 0B0h, 010h, 001h, 000h, 000h, 0B9h, 00Ah, 000h, 000h, 000h, 08Dh, 07Ch, 024h
    db 060h, 0F3h, 0A5h, 08Bh, 04Ch, 024h, 064h, 08Bh, 044h, 024h, 060h, 08Bh, 074h, 024h, 038h, 08Bh
    db 07Ch, 024h, 04Ch, 023h, 0F0h, 08Bh, 044h, 024h, 040h, 023h, 0D1h, 08Bh, 04Ch, 024h, 070h, 089h
    db 054h, 024h, 03Ch, 08Bh, 054h, 024h, 068h, 023h, 0C2h, 08Bh, 054h, 024h, 074h, 023h, 0FAh, 08Bh
    db 054h, 024h, 054h, 089h, 044h, 024h, 040h, 08Bh, 044h, 024h, 06Ch, 023h, 0E8h, 08Bh, 044h, 024h
    db 078h, 023h, 0D9h, 08Bh, 04Ch, 024h, 07Ch, 023h, 0D1h, 089h, 074h, 024h, 038h, 08Bh, 074h, 024h
    db 050h, 023h, 0F0h, 08Bh, 044h, 024h, 058h, 089h, 06Ch, 024h, 044h, 08Bh, 06Ch, 024h, 05Ch, 089h
    db 054h, 024h, 054h, 08Bh, 094h, 024h, 080h, 000h, 000h, 000h, 023h, 0C2h, 089h, 044h, 024h, 058h
    db 08Bh, 084h, 024h, 084h, 000h, 000h, 000h, 023h, 0E8h, 089h, 06Ch, 024h, 05Ch, 089h, 07Ch, 024h
    db 04Ch, 089h, 074h, 024h, 050h, 0B9h, 00Ah, 000h, 000h, 000h, 08Dh, 074h, 024h, 060h, 08Dh, 07Ch
    db 024h, 010h, 0F3h, 0A5h, 08Bh, 06Ch, 024h, 028h, 08Bh, 044h, 024h, 010h, 08Bh, 04Ch, 024h, 014h
    db 08Bh, 054h, 024h, 018h, 08Bh, 074h, 024h, 01Ch, 08Bh, 07Ch, 024h, 020h, 0F7h, 0D5h, 089h, 06Ch
    db 024h, 028h, 08Bh, 06Ch, 024h, 02Ch, 0F7h, 0D5h, 089h, 06Ch, 024h, 02Ch, 08Bh, 06Ch, 024h, 030h
    db 0F7h, 0D5h, 089h, 06Ch, 024h, 030h, 08Bh, 06Ch, 024h, 034h, 0F7h, 0D5h, 089h, 06Ch, 024h, 034h
    db 08Bh, 02Dh
    dd g_Va012EFADC
    db 089h, 05Ch, 024h, 048h, 08Bh, 05Ch, 024h, 024h, 0F7h, 0D0h, 023h, 0C5h, 0F7h, 0D1h, 0F7h, 0D2h
    db 0F7h, 0D6h, 0F7h, 0D7h, 0F7h, 0D3h, 066h, 0C7h, 044h, 024h, 036h, 000h, 000h, 089h, 044h, 024h
    db 010h, 08Bh, 02Dh
    dd g_Va012EFAE0
    db 0A1h
    dd g_Va012EFAE4
    db 023h, 0CDh, 08Bh, 02Dh
    dd g_Va012EFAE8
    db 023h, 0D0h, 08Bh, 044h, 024h, 028h, 089h, 04Ch, 024h, 014h, 023h, 01Dh
    dd g_Va012EFAF0
    db 08Bh, 00Dh
    dd g_Va012EFAF4
    db 089h, 054h, 024h, 018h, 023h, 03Dh
    dd g_Va012EFAEC
    db 08Bh, 015h
    dd g_Va012EFAF8
    db 023h, 0C1h, 08Bh, 00Dh
    dd g_Va012EFB00
    db 023h, 0F5h, 08Bh, 06Ch, 024h, 02Ch, 089h, 05Ch, 024h, 024h, 08Bh, 05Ch, 024h, 030h, 089h, 044h
    db 024h, 028h, 0A1h
    dd g_Va012EFAFC
    db 023h, 0EAh, 089h, 07Ch, 024h, 020h, 08Bh, 07Ch, 024h, 034h, 023h, 0D8h, 08Dh, 054h, 024h, 038h
    db 023h, 0F9h, 08Bh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 052h, 08Dh, 044h, 024h, 014h, 050h, 089h
    db 074h, 024h, 024h, 089h, 06Ch, 024h, 034h, 089h, 05Ch, 024h, 038h, 089h, 07Ch, 024h, 03Ch
    call ?j_000095ed@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 078h, 0C2h, 004h, 000h
?d_0023bb90@@YAXXZ ENDP
_TEXT$d0063bb90 ENDS
_TEXT SEGMENT

; ghidra: FUN_0063be60  retail @ 0x0023BE60 size 189
public ?d_0023be60@@YAXXZ
?d_0023be60@@YAXXZ PROC
    db 83h, 0ECh, 40h, 56h, 8Bh, 74h, 24h, 48h, 8Bh, 46h, 04h, 85h, 0C0h, 57h, 8Bh, 0F9h
    db 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 3Dh, 64h, 0DCh, 0FFh, 8Bh, 88h
    db 0C8h, 00h, 00h, 00h, 0F6h, 0C5h, 08h, 74h, 0Ah, 5Fh, 0B0h, 01h, 5Eh, 83h, 0C4h, 40h
    db 0C2h, 04h, 00h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 8Bh, 7Fh, 08h, 53h, 55h
    db 8Dh, 54h, 24h, 10h, 52h, 8Dh, 46h, 38h, 50h, 56h, 0E8h, 07h, 0BCh, 0DEh, 0FFh, 8Bh
    db 0D8h, 33h, 0F6h, 85h, 0DBh, 7Eh, 4Eh, 8Bh, 4Fh, 74h, 8Bh, 2Dh, 98h, 08h, 2Fh, 01h
    db 89h, 4Ch, 24h, 54h, 8Bh, 44h, 0B4h, 10h, 3Bh, 44h, 24h, 54h, 74h, 32h, 50h, 8Bh
    db 0CDh, 0E8h, 7Dh, 33h, 0DEh, 0FFh, 85h, 0C0h, 74h, 37h, 39h, 0B8h, 14h, 02h, 00h, 00h
    db 74h, 1Eh, 8Bh, 40h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h
    db 0E8h, 0C6h, 63h, 0DCh, 0FFh, 8Bh, 88h, 0D4h, 00h, 00h, 00h, 0F6h, 0C5h, 10h, 74h, 11h
    db 46h, 3Bh, 0F3h, 7Ch, 0BFh, 5Dh, 5Bh, 5Fh, 0B0h, 01h, 5Eh, 83h, 0C4h, 40h, 0C2h, 04h
    db 00h, 5Dh, 5Bh, 5Fh, 32h, 0C0h, 5Eh, 83h, 0C4h, 40h, 0C2h, 04h, 00h
?d_0023be60@@YAXXZ ENDP

; ghidra: FUN_0063c000  retail @ 0x0023C000 size 345
public ?d_0023c000@@YAXXZ
?d_0023c000@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 98h, 0DBh, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 08h, 8Bh, 40h
    db 78h, 85h, 0C0h, 0Fh, 85h, 20h, 01h, 00h, 00h, 56h, 57h, 0E8h, 25h, 0E3h, 0DFh, 0FFh
    db 8Bh, 83h, 0E4h, 00h, 00h, 00h, 8Dh, 0BBh, 0E4h, 00h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh
    db 89h, 7Ch, 24h, 14h, 0FFh, 50h, 10h, 8Bh, 53h, 0Ch, 8Dh, 73h, 0Ch, 8Bh, 0CEh, 0FFh
    db 52h, 08h, 85h, 0C0h, 0Fh, 84h, 0E3h, 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h
    db 08h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 68h, 85h, 0C0h, 0Fh, 84h, 0CDh, 00h, 00h, 00h
    db 8Dh, 43h, 38h, 50h, 8Dh, 4Ch, 24h, 10h, 0E8h, 78h, 0C5h, 0DFh, 0FFh, 8Bh, 74h, 24h
    db 0Ch, 8Bh, 3Eh, 33h, 0C9h, 3Bh, 0FEh, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 8Bh
    db 0C7h, 74h, 07h, 8Bh, 00h, 41h, 3Bh, 0C6h, 75h, 0F9h, 55h, 8Bh, 0ABh, 00h, 02h, 00h
    db 00h, 0BAh, 64h, 00h, 00h, 00h, 2Bh, 0D5h, 85h, 0C9h, 89h, 54h, 24h, 18h, 0DBh, 44h
    db 24h, 18h, 89h, 4Ch, 24h, 18h, 0DCh, 0Dh, 0D0h, 0EBh, 0Ah, 01h, 0DBh, 44h, 24h, 18h
    db 7Dh, 06h, 0DCh, 05h, 0C0h, 0EBh, 0Ah, 01h, 0DEh, 0C9h, 0E8h, 69h, 0ADh, 7Bh, 00h, 33h
    db 0C9h, 3Bh, 0FEh, 8Bh, 0E8h, 8Bh, 0C7h, 74h, 4Eh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 00h, 41h, 3Bh, 0C6h, 75h, 0F9h, 3Bh, 0E9h, 73h, 3Ch, 85h, 0EDh, 7Eh, 38h, 8Bh
    db 0DFh, 3Bh, 0DEh, 74h, 32h, 8Bh, 7Bh, 08h, 8Bh, 87h, 00h, 02h, 00h, 00h, 85h, 0C0h
    db 74h, 1Fh, 85h, 0EDh, 74h, 1Bh, 8Bh, 4Ch, 24h, 14h, 8Bh, 01h, 57h, 0FFh, 50h, 34h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 57h, 0E8h, 0C2h, 0Fh, 0DEh, 0FFh, 8Bh, 74h, 24h, 10h
    db 4Dh, 8Bh, 1Bh, 3Bh, 0DEh, 75h, 0CEh, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 24h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 55h, 25h, 0DDh, 0FFh, 8Bh, 7Ch, 24h, 14h, 5Dh, 8Bh, 17h, 8Bh
    db 0CFh, 0FFh, 92h, 0BCh, 01h, 00h, 00h, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 10h, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h
?d_0023c000@@YAXXZ ENDP
_TEXT ENDS
END
