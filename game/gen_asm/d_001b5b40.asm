.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeShadowScale@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheAerialPathfinder@@3PAVAerialPathfinder@@A:BYTE
EXTERN ?g_0109B46C@@3MB:BYTE
EXTERN ?g_Rva01095F98@@3MA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeK1266A@@3MB:BYTE
EXTERN ?g_bfmeK1266B@@3MB:BYTE
EXTERN ?g_bfmeK2SMA@@3MA:BYTE
EXTERN ?g_bfmeScaleBK@@3MA:BYTE
EXTERN ?g_millisecondsToSeconds@@3MA:BYTE
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_00004048@@YAXXZ:NEAR
EXTERN ?j_00005ee3@@YAXXZ:NEAR
EXTERN ?j_00008a26@@YAXXZ:NEAR
EXTERN ?j_00008a9e@@YAXXZ:NEAR
EXTERN ?j_0000991c@@YAXXZ:NEAR
EXTERN ?j_0000c1b7@@YAXXZ:NEAR
EXTERN ?j_00012f5d@@YAXXZ:NEAR
EXTERN ?j_0001399e@@YAXXZ:NEAR
EXTERN ?j_0001a334@@YAXXZ:NEAR
EXTERN ?j_0001a9dd@@YAXXZ:NEAR
EXTERN ?j_0001c7ec@@YAXXZ:NEAR
EXTERN ?j_00021017@@YAXXZ:NEAR
EXTERN ?j_0002191d@@YAXXZ:NEAR
EXTERN ?j_000230ab@@YAXXZ:NEAR
EXTERN ?j_000235e2@@YAXXZ:NEAR
EXTERN ?j_00024ea6@@YAXXZ:NEAR
EXTERN ?j_00024f7d@@YAXXZ:NEAR
EXTERN ?j_0002b355@@YAXXZ:NEAR
EXTERN ?j_0002bd82@@YAXXZ:NEAR
EXTERN ?j_0002ed16@@YAXXZ:NEAR
EXTERN ?j_000309f4@@YAXXZ:NEAR
EXTERN ?j_00032a4c@@YAXXZ:NEAR
EXTERN ?j_00033bae@@YAXXZ:NEAR
EXTERN ?j_000361ce@@YAXXZ:NEAR
EXTERN ?j_0003acc4@@YAXXZ:NEAR
EXTERN ?j_0003e13a@@YAXXZ:NEAR
EXTERN ?j_0003faee@@YAXXZ:NEAR
EXTERN ?j_00040246@@YAXXZ:NEAR
EXTERN ?j_00046c09@@YAXXZ:NEAR
EXTERN ?j_00049413@@YAXXZ:NEAR
EXTERN __real@3d800000:BYTE
EXTERN __real@3e4ccccd:BYTE
EXTERN __real@3e800000:BYTE
EXTERN __real@3ecccccd:BYTE
EXTERN __real@3f4ccccd:BYTE
EXTERN __real@40000000:BYTE
EXTERN __real@40490fdb:BYTE
EXTERN __real@4f800000:BYTE
EXTERN g_Va01008BB0:NEAR
EXTERN g_Va01008C98:NEAR
EXTERN g_Va0109DF60:BYTE
EXTERN g_Va0109DF80:BYTE
EXTERN g_Va0109DF84:BYTE
_TEXT SEGMENT

; ghidra: FUN_005b5b40  retail @ 0x001B5B40 size 144
_TEXT ENDS
_TEXT$d005b5b40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005B5B40 size 144
public ?d_001b5b40@@YAXXZ
?d_001b5b40@@YAXXZ PROC
    db 083h, 0ECh, 018h, 056h, 08Bh, 0F1h, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h
    db 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 083h, 078h, 070h, 001h, 075h, 068h, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h
    db 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0D4h, 000h, 000h, 000h, 085h, 0C9h, 074h, 04Bh, 08Bh, 074h, 024h, 020h, 08Dh, 044h
    db 024h, 004h, 050h, 08Bh, 0CEh
    call ?j_00005ee3@@YAXXZ
    db 08Bh, 044h, 024h, 024h, 0D9h, 040h, 004h, 0D9h, 000h, 0D8h, 066h, 038h, 0D9h, 05Ch, 024h, 010h
    db 0D8h, 066h, 03Ch, 0D9h, 044h, 024h, 008h, 0D8h, 0C9h, 0D9h, 044h, 024h, 010h, 0D8h, 04Ch, 024h
    db 004h, 0DEh, 0C1h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 07Ah, 009h, 0B0h, 001h, 05Eh, 083h, 0C4h, 018h, 0C2h
    db 008h, 000h, 032h, 0C0h, 05Eh, 083h, 0C4h, 018h, 0C2h, 008h, 000h
?d_001b5b40@@YAXXZ ENDP
_TEXT$d005b5b40 ENDS
_TEXT SEGMENT

; ghidra: FUN_005b5cc0  retail @ 0x001B5CC0 size 33
public ?d_001b5cc0@@YAXXZ
?d_001b5cc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 16h, 83h, 0C0h, 38h, 8Bh, 10h, 83h, 0C1h, 14h
    db 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h, 8Bh, 40h, 08h, 89h, 41h, 08h, 0C2h, 04h
    db 00h
?d_001b5cc0@@YAXXZ ENDP

; ghidra: FUN_005b6070  retail @ 0x001B6070 size 50
public ?d_001b6070@@YAXXZ
?d_001b6070@@YAXXZ PROC
    db 51h, 8Bh, 41h, 04h, 85h, 0C0h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 74h, 0Ch, 8Bh
    db 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 30h, 0C2h, 0E4h, 0FFh, 56h, 8Bh, 74h, 24h, 0Ch
    db 83h, 0C0h, 0Ch, 50h, 8Bh, 0CEh, 0E8h, 0C5h, 1Ah, 6Dh, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h
    db 04h, 00h
?d_001b6070@@YAXXZ ENDP

; ghidra: FUN_005b6880  retail @ 0x001B6880 size 71
public ?d_001b6880@@YAXXZ
?d_001b6880@@YAXXZ PROC
    db 8Bh, 09h, 8Bh, 41h, 04h, 85h, 0C0h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0D1h, 74h
    db 15h, 8Bh, 37h, 39h, 70h, 10h, 7Ch, 07h, 8Bh, 0D0h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh
    db 40h, 0Ch, 85h, 0C0h, 75h, 0EDh, 3Bh, 0D1h, 74h, 07h, 8Bh, 07h, 3Bh, 42h, 10h, 7Dh
    db 0Bh, 8Bh, 44h, 24h, 0Ch, 5Fh, 89h, 08h, 5Eh, 0C2h, 08h, 00h, 8Bh, 44h, 24h, 0Ch
    db 5Fh, 89h, 10h, 5Eh, 0C2h, 08h, 00h
?d_001b6880@@YAXXZ ENDP

; ghidra: FUN_005b6920  retail @ 0x001B6920 size 98
public ?d_001b6920@@YAXXZ
?d_001b6920@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 8Ah, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 0A8h, 00h, 00h, 00h, 0E8h, 0F0h, 0B5h, 6Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 49h, 0A1h, 0E8h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_001b6920@@YAXXZ ENDP

; ghidra: FUN_005b6cc0  retail @ 0x001B6CC0 size 176
public ?d_001b6cc0@@YAXXZ
?d_001b6cc0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0F1h, 3Bh, 1Eh, 57h
    db 74h, 3Fh, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 75h, 10h, 8Bh, 44h, 24h, 18h, 85h, 0C0h
    db 75h, 2Fh, 8Bh, 45h, 00h, 3Bh, 43h, 10h, 7Ch, 27h, 6Ah, 18h, 0E8h, 4Fh, 78h, 67h
    db 00h, 8Bh, 0F8h, 8Dh, 4Fh, 10h, 55h, 51h, 0E8h, 0DEh, 07h, 0E6h, 0FFh, 89h, 7Bh, 0Ch
    db 8Bh, 06h, 8Bh, 48h, 0Ch, 83h, 0C4h, 0Ch, 3Bh, 0D9h, 75h, 36h, 89h, 78h, 0Ch, 0EBh
    db 31h, 6Ah, 18h, 0E8h, 28h, 78h, 67h, 00h, 8Bh, 0F8h, 8Dh, 57h, 10h, 55h, 52h, 0E8h
    db 0B7h, 07h, 0E6h, 0FFh, 89h, 7Bh, 08h, 8Bh, 06h, 83h, 0C4h, 0Ch, 3Bh, 0D8h, 75h, 0Ah
    db 89h, 78h, 04h, 8Bh, 06h, 89h, 78h, 0Ch, 0EBh, 08h, 3Bh, 58h, 08h, 75h, 03h, 89h
    db 78h, 08h, 33h, 0C0h, 89h, 5Fh, 04h, 89h, 47h, 08h, 89h, 47h, 0Ch, 8Bh, 0Eh, 83h
    db 0C1h, 04h, 51h, 57h, 0E8h, 77h, 5Ch, 67h, 00h, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 40h
    db 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 89h, 38h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 14h, 00h
?d_001b6cc0@@YAXXZ ENDP

; ghidra: FUN_005b6da0  retail @ 0x001B6DA0 size 145
public ?d_001b6da0@@YAXXZ
?d_001b6da0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 9Ch, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 0F0h, 4Ah, 67h, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 7Dh, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 60h, 80h, 0E6h, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_001b6da0@@YAXXZ ENDP

; ghidra: FUN_005b6f20  retail @ 0x001B6F20 size 209
public ?d_001b6f20@@YAXXZ
?d_001b6f20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 43h, 8Bh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 8Bh, 0D9h, 56h, 57h, 89h, 5Ch, 24h, 0Ch, 0C7h
    db 03h, 10h, 0DFh, 09h, 01h, 8Bh, 43h, 08h, 8Bh, 78h, 08h, 3Bh, 0F8h, 8Dh, 73h, 08h
    db 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 74h, 24h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 14h, 85h, 0C9h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 57h, 0E8h, 0FDh
    db 48h, 67h, 00h, 8Bh, 0F8h, 8Bh, 06h, 83h, 0C4h, 04h, 3Bh, 0F8h, 75h, 0E2h, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 3Fh, 8Bh, 0Eh, 8Bh, 79h, 04h, 85h, 0FFh, 74h, 22h, 55h, 90h
    db 8Bh, 57h, 0Ch, 52h, 8Bh, 0CEh, 0E8h, 1Fh, 0B7h, 0E6h, 0FFh, 8Bh, 6Fh, 08h, 6Ah, 18h
    db 57h, 0E8h, 4Ah, 76h, 67h, 00h, 83h, 0C4h, 08h, 85h, 0EDh, 8Bh, 0FDh, 75h, 0E1h, 5Dh
    db 8Bh, 06h, 89h, 40h, 08h, 8Bh, 06h, 33h, 0C9h, 89h, 48h, 04h, 8Bh, 06h, 89h, 40h
    db 0Ch, 89h, 4Eh, 04h, 8Bh, 0CEh, 0C6h, 44h, 24h, 18h, 00h, 0E8h, 45h, 01h, 0E7h, 0FFh
    db 8Bh, 0CBh, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 61h, 0AAh, 7Eh, 00h, 8Bh
    db 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C3h
?d_001b6f20@@YAXXZ ENDP

; ghidra: FUN_005b70e0  retail @ 0x001B70E0 size 92
public ?d_001b70e0@@YAXXZ
?d_001b70e0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 8Bh, 00h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h
    db 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 50h, 0E8h, 0D6h, 3Ch, 0E8h
    db 0FFh, 85h, 0C0h, 89h, 44h, 24h, 08h, 75h, 06h, 33h, 0C0h, 59h, 0C2h, 04h, 00h, 56h
    db 8Bh, 35h, 04h, 0F5h, 2Eh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Dh, 54h, 24h, 08h, 83h
    db 0C6h, 08h, 52h, 8Bh, 0CEh, 0E8h, 0DFh, 69h, 0E8h, 0FFh, 8Bh, 0Eh, 8Bh, 44h, 24h, 04h
    db 3Bh, 0C1h, 5Eh, 74h, 0D4h, 8Bh, 40h, 14h, 59h, 0C2h, 04h, 00h
?d_001b70e0@@YAXXZ ENDP

; ghidra: FUN_005b7160  retail @ 0x001B7160 size 123
public ?d_001b7160@@YAXXZ
?d_001b7160@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 43h, 08h, 56h, 8Bh, 70h, 08h, 3Bh, 0F0h, 74h, 6Ah, 57h, 90h
    db 8Bh, 7Eh, 14h, 8Ah, 47h, 08h, 84h, 0C0h, 74h, 3Eh, 8Bh, 07h, 6Ah, 01h, 8Bh, 0CFh
    db 0FFh, 10h, 56h, 8Bh, 0FEh, 0E8h, 0E6h, 46h, 67h, 00h, 8Bh, 0F0h, 8Bh, 43h, 08h, 8Dh
    db 48h, 0Ch, 51h, 8Dh, 50h, 08h, 52h, 83h, 0C0h, 04h, 50h, 57h, 0E8h, 0BFh, 59h, 67h
    db 00h, 83h, 0C4h, 14h, 85h, 0C0h, 74h, 0Bh, 6Ah, 18h, 50h, 0E8h, 40h, 74h, 67h, 00h
    db 83h, 0C4h, 08h, 0FFh, 4Bh, 0Ch, 0EBh, 1Ah, 8Bh, 4Fh, 04h, 85h, 0C9h, 74h, 08h, 0E8h
    db 58h, 0BBh, 0E7h, 0FFh, 89h, 47h, 04h, 56h, 0E8h, 0A3h, 46h, 67h, 00h, 83h, 0C4h, 04h
    db 8Bh, 0F0h, 3Bh, 73h, 08h, 75h, 99h, 5Fh, 5Eh, 5Bh, 0C3h
?d_001b7160@@YAXXZ ENDP

; ghidra: FUN_005b7200  retail @ 0x001B7200 size 467
public ?d_001b7200@@YAXXZ
?d_001b7200@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 80h, 0A8h, 00h, 00h, 00h, 83h, 0ECh, 48h, 85h, 0C0h, 55h
    db 8Bh, 0E9h, 74h, 10h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 33h, 80h, 0E6h, 0FFh
    db 85h, 0C0h, 75h, 09h, 32h, 0C0h, 5Dh, 83h, 0C4h, 48h, 0C2h, 08h, 00h, 56h, 8Bh, 74h
    db 24h, 54h, 57h, 8Bh, 0BEh, 0FCh, 01h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 87h, 01h, 00h
    db 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 68h, 85h, 0C0h, 0Fh, 84h, 78h, 01h, 00h, 00h
    db 8Bh, 07h, 53h, 8Bh, 0CFh, 0FFh, 50h, 68h, 8Bh, 0D8h, 8Bh, 86h, 04h, 02h, 00h, 00h
    db 85h, 0C0h, 74h, 08h, 8Bh, 0B8h, 40h, 01h, 00h, 00h, 0EBh, 02h, 33h, 0FFh, 85h, 0FFh
    db 0Fh, 84h, 46h, 01h, 00h, 00h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CFh, 0E8h, 21h, 70h
    db 0E7h, 0FFh, 6Ah, 00h, 8Dh, 54h, 24h, 38h, 52h, 55h, 56h, 8Bh, 0CFh, 0E8h, 0Ch, 18h
    db 0E5h, 0FFh, 0D9h, 46h, 38h, 0D9h, 46h, 3Ch, 8Bh, 44h, 24h, 38h, 8Bh, 4Ch, 24h, 3Ch
    db 0D9h, 0C9h, 0D8h, 64h, 24h, 1Ch, 8Bh, 54h, 24h, 40h, 89h, 44h, 24h, 28h, 8Bh, 46h
    db 40h, 0D9h, 5Ch, 24h, 10h, 89h, 44h, 24h, 18h, 89h, 4Ch, 24h, 2Ch, 0D8h, 64h, 24h
    db 20h, 8Dh, 4Ch, 24h, 10h, 89h, 54h, 24h, 30h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h
    db 18h, 0D8h, 64h, 24h, 24h, 0D9h, 5Ch, 24h, 18h, 0E8h, 5Bh, 70h, 0E7h, 0FFh, 0D8h, 1Dh
    db 0C4h, 0FAh, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 5Dh, 8Dh, 4Ch, 24h, 1Ch, 51h
    db 8Bh, 0CEh, 0E8h, 0B0h, 2Eh, 0E8h, 0FFh, 8Dh, 54h, 24h, 1Ch, 52h, 8Bh, 0CDh, 0E8h, 0B4h
    db 4Eh, 0E5h, 0FFh, 8Bh, 44h, 24h, 50h, 50h, 8Bh, 0CEh, 0E8h, 0FFh, 0EAh, 0E7h, 0FFh, 8Bh
    db 44h, 24h, 50h, 8Bh, 4Ch, 24h, 54h, 8Bh, 13h, 50h, 51h, 8Dh, 44h, 24h, 4Ch, 50h
    db 8Dh, 4Ch, 24h, 34h, 51h, 8Bh, 0CBh, 0FFh, 92h, 94h, 01h, 00h, 00h, 8Bh, 15h, 98h
    db 08h, 2Fh, 01h, 8Bh, 42h, 3Ch, 83h, 0C0h, 3Ch, 89h, 45h, 60h, 5Bh, 5Fh, 5Eh, 0B0h
    db 01h, 5Dh, 83h, 0C4h, 48h, 0C2h, 08h, 00h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 92h, 0A4h, 01h
    db 00h, 00h, 84h, 0C0h, 75h, 0Dh, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 3Bh, 4Dh
    db 60h, 76h, 0D9h, 56h, 0E8h, 3Eh, 45h, 0E5h, 0FFh, 8Bh, 0F8h, 83h, 0C4h, 04h, 85h, 0FFh
    db 74h, 4Ah, 8Dh, 54h, 24h, 10h, 52h, 8Bh, 0CFh, 0E8h, 9Eh, 0FDh, 0E4h, 0FFh, 8Dh, 44h
    db 24h, 10h, 50h, 8Bh, 0CFh, 0E8h, 92h, 0FDh, 0E4h, 0FFh, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh
    db 0CFh, 0E8h, 86h, 0FDh, 0E4h, 0FFh, 6Ah, 00h, 8Dh, 54h, 24h, 38h, 52h, 55h, 56h, 8Bh
    db 0CFh, 0E8h, 0F8h, 16h, 0E5h, 0FFh, 81h, 7Ch, 24h, 54h, 0FFh, 0FFh, 0FFh, 7Fh, 74h, 0Ch
    db 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CFh, 0E8h, 60h, 0FDh, 0E4h, 0FFh, 5Bh, 5Fh, 5Eh, 32h
    db 0C0h, 5Dh, 83h, 0C4h, 48h, 0C2h, 08h, 00h, 5Fh, 5Eh, 32h, 0C0h, 5Dh, 83h, 0C4h, 48h
    db 0C2h, 08h, 00h
?d_001b7200@@YAXXZ ENDP

; ghidra: FUN_005b7450  retail @ 0x001B7450 size 35
public ?d_001b7450@@YAXXZ
?d_001b7450@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 3Ch, 0DFh, 09h, 01h, 89h, 48h, 04h, 89h, 48h, 08h
    db 89h, 48h, 0Ch, 89h, 48h, 10h, 88h, 48h, 14h, 89h, 48h, 18h, 89h, 48h, 1Ch, 89h
    db 48h, 20h, 0C3h
?d_001b7450@@YAXXZ ENDP

; ghidra: FUN_005b74d0  retail @ 0x001B74D0 size 387
public ?d_001b74d0@@YAXXZ
?d_001b74d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Bh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h
    db 28h, 8Bh, 07h, 8Dh, 4Ch, 24h, 0Ch, 0B3h, 01h, 51h, 8Bh, 0CFh, 88h, 5Ch, 24h, 10h
    db 88h, 5Ch, 24h, 11h, 0FFh, 50h, 28h, 8Bh, 17h, 56h, 8Bh, 0CFh, 0FFh, 52h, 30h, 8Bh
    db 07h, 8Bh, 0CFh, 0FFh, 50h, 08h, 84h, 0C0h, 74h, 6Bh, 33h, 0C0h, 89h, 44h, 24h, 0Ch
    db 8Bh, 4Ch, 24h, 2Ch, 8Bh, 09h, 3Bh, 0C8h, 89h, 44h, 24h, 20h, 74h, 26h, 8Dh, 54h
    db 24h, 2Ch, 52h, 0E8h, 4Eh, 0FEh, 0E6h, 0FFh, 50h, 8Dh, 4Ch, 24h, 10h, 88h, 5Ch, 24h
    db 24h, 0E8h, 4Ah, 07h, 6Dh, 00h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 20h, 00h, 0E8h
    db 0ECh, 03h, 6Dh, 00h, 8Bh, 07h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CFh, 0FFh, 50h, 68h
    db 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0CFh, 03h, 6Dh
    db 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 18h, 0C2h, 08h, 00h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h, 00h, 8Bh, 17h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CFh, 0C7h, 44h, 24h, 24h, 02h, 00h, 00h, 00h, 0FFh, 52h
    db 68h, 8Bh, 44h, 24h, 28h, 85h, 0C0h, 74h, 07h, 66h, 83h, 78h, 04h, 00h, 75h, 18h
    db 8Bh, 4Ch, 24h, 2Ch, 0C7h, 01h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh
    db 0FFh, 0FFh, 8Dh, 4Ch, 24h, 28h, 0EBh, 0A4h, 8Bh, 56h, 08h, 2Bh, 56h, 04h, 0C1h, 0FAh
    db 02h, 33h, 0FFh, 85h, 0D2h, 76h, 3Fh, 8Bh, 46h, 04h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh
    db 0Ch, 0B8h, 0E8h, 9Fh, 0FDh, 0E6h, 0FFh, 8Dh, 54h, 24h, 28h, 52h, 8Bh, 0C8h, 0E8h, 0D2h
    db 0AAh, 0E6h, 0FFh, 8Bh, 0D8h, 0F7h, 0DBh, 1Ah, 0DBh, 8Dh, 4Ch, 24h, 0Ch, 0FEh, 0C3h, 0E8h
    db 3Ch, 03h, 6Dh, 00h, 84h, 0DBh, 75h, 2Eh, 8Bh, 46h, 08h, 2Bh, 46h, 04h, 47h, 0C1h
    db 0F8h, 02h, 3Bh, 0F8h, 72h, 0C1h, 6Ah, 00h, 8Dh, 44h, 24h, 14h, 6Ah, 05h, 50h, 0E8h
    db 0FCh, 0EBh, 81h, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 4Ch, 24h, 14h
    db 51h, 0E8h, 0CAh, 0F6h, 83h, 00h, 8Bh, 76h, 04h, 8Bh, 0Ch, 0BEh, 8Bh, 54h, 24h, 2Ch
    db 89h, 0Ah, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 28h, 0E9h, 19h
    db 0FFh, 0FFh, 0FFh
?d_001b74d0@@YAXXZ ENDP

; ghidra: FUN_005b7700  retail @ 0x001B7700 size 93
public ?d_001b7700@@YAXXZ
?d_001b7700@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah
    db 0Ch, 89h, 4Ah, 10h, 89h, 4Ah, 14h, 89h, 4Ah, 18h, 89h, 4Ah, 1Ch, 89h, 4Ah, 20h
    db 89h, 4Ah, 24h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 56h, 0C1h, 0EAh, 05h
    db 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 10h
    db 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 0C1h, 0EAh, 05h, 8Bh
    db 0Ch, 90h, 8Dh, 14h, 90h, 0Bh, 0CEh, 89h, 0Ah, 5Eh, 0C2h, 0Ch, 00h
?d_001b7700@@YAXXZ ENDP

; ghidra: FUN_005b7e90  retail @ 0x001B7E90 size 297
public ?d_001b7e90@@YAXXZ
?d_001b7e90@@YAXXZ PROC
    db 51h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0F1h, 8Bh, 8Fh, 00h, 02h, 00h, 00h, 8Bh
    db 01h, 0FFh, 50h, 20h, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 8Bh, 91h, 0D4h, 01h, 00h, 00h
    db 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 89h, 54h, 24h, 10h, 3Bh, 81h, 0D8h, 0Bh, 00h, 00h
    db 8Bh, 46h, 04h, 7Dh, 67h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h
    db 0E8h, 0E6h, 0A3h, 0E4h, 0FFh, 8Ah, 88h, 0FCh, 00h, 00h, 00h, 84h, 0C9h, 74h, 0Ch, 0F7h
    db 87h, 90h, 00h, 00h, 00h, 00h, 00h, 40h, 00h, 75h, 0Ah, 8Ah, 87h, 0F5h, 01h, 00h
    db 00h, 84h, 0C0h, 74h, 2Fh, 8Bh, 46h, 04h, 85h, 0C0h, 75h, 0Eh, 0D9h, 05h, 0E0h, 0CFh
    db 2Ah, 01h, 0D8h, 88h, 0F8h, 00h, 00h, 00h, 0EBh, 3Bh, 8Bh, 48h, 04h, 85h, 0C9h, 74h
    db 05h, 0E8h, 0A5h, 0A3h, 0E4h, 0FFh, 0D9h, 05h, 0E0h, 0CFh, 2Ah, 01h, 0D8h, 88h, 0F8h, 00h
    db 00h, 00h, 0EBh, 21h, 0D9h, 05h, 0E0h, 0CFh, 2Ah, 01h, 0EBh, 19h, 85h, 0C0h, 74h, 0Ch
    db 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 7Fh, 0A3h, 0E4h, 0FFh, 0D9h, 05h, 0E0h, 0CFh
    db 2Ah, 01h, 0D8h, 48h, 20h, 0D8h, 4Ch, 24h, 10h, 0D9h, 54h, 24h, 10h, 0D8h, 5Eh, 28h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 56h, 28h, 89h, 54h, 24h, 10h, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 4Ah, 0A3h, 0E4h
    db 0FFh, 8Ah, 88h, 0E8h, 00h, 00h, 00h, 84h, 0C9h, 74h, 0Fh, 8Bh, 0CFh, 0E8h, 28h, 0F8h
    db 0E6h, 0FFh, 0D8h, 4Ch, 24h, 10h, 0D9h, 5Ch, 24h, 10h, 8Dh, 44h, 24h, 08h, 50h, 6Ah
    db 07h, 8Bh, 0CFh, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 58h, 2Ch, 0E7h, 0FFh
    db 84h, 0C0h, 5Fh, 5Eh, 74h, 0Bh, 0D9h, 04h, 24h, 0D8h, 4Ch, 24h, 08h, 59h, 0C2h, 04h
    db 00h, 0D9h, 44h, 24h, 08h, 59h, 0C2h, 04h, 00h
?d_001b7e90@@YAXXZ ENDP

; ghidra: FUN_005b8010  retail @ 0x001B8010 size 77
public ?d_001b8010@@YAXXZ
?d_001b8010@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 56h, 50h, 8Bh, 0F1h, 0E8h, 8Dh, 0B0h, 0E6h, 0FFh, 0D9h, 5Ch
    db 24h, 0Ch, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h
    db 0E8h, 86h, 0A2h, 0E4h, 0FFh, 8Bh, 48h, 40h, 0DBh, 40h, 40h, 85h, 0C9h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 0D8h, 7Ch, 24h, 0Ch, 0D8h, 56h, 2Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 05h, 0DDh, 0D8h, 0D9h, 46h, 2Ch, 5Eh, 59h, 0C2h, 04h, 00h
?d_001b8010@@YAXXZ ENDP

; ghidra: FUN_005b8070  retail @ 0x001B8070 size 77
public ?d_001b8070@@YAXXZ
?d_001b8070@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 56h, 50h, 8Bh, 0F1h, 0E8h, 2Dh, 0B0h, 0E6h, 0FFh, 0D9h, 5Ch
    db 24h, 0Ch, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h
    db 0E8h, 26h, 0A2h, 0E4h, 0FFh, 8Bh, 48h, 4Ch, 0DBh, 40h, 4Ch, 85h, 0C9h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 0D8h, 7Ch, 24h, 0Ch, 0D8h, 56h, 30h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 05h, 0DDh, 0D8h, 0D9h, 46h, 30h, 5Eh, 59h, 0C2h, 04h, 00h
?d_001b8070@@YAXXZ ENDP

; ghidra: FUN_005b80d0  retail @ 0x001B80D0 size 650
public ?d_001b80d0@@YAXXZ
?d_001b80d0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 74h, 24h, 14h, 85h, 0F6h, 57h, 8Bh, 0F9h, 0Fh, 84h, 6Fh
    db 02h, 00h, 00h, 0D9h, 86h, 0C0h, 00h, 00h, 00h, 8Bh, 47h, 04h, 85h, 0C0h, 0D8h, 0Dh
    db 3Ch, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 18h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h
    db 05h, 0E8h, 0B5h, 0A1h, 0E4h, 0FFh, 0D9h, 40h, 14h, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 1Eh, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h
    db 85h, 0C9h, 74h, 05h, 0E8h, 92h, 0A1h, 0E4h, 0FFh, 0D9h, 44h, 24h, 18h, 0D8h, 48h, 14h
    db 0D9h, 5Ch, 24h, 18h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 0Fh, 84h, 10h, 02h
    db 00h, 00h, 8Bh, 01h, 0FFh, 90h, 50h, 01h, 00h, 00h, 85h, 0C0h, 89h, 44h, 24h, 10h
    db 0Fh, 84h, 0FCh, 01h, 00h, 00h, 55h, 8Bh, 0AEh, 00h, 02h, 00h, 00h, 85h, 0EDh, 0Fh
    db 84h, 0ECh, 01h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 03h, 56h
    db 74h, 89h, 54h, 24h, 10h, 0DBh, 44h, 24h, 10h, 53h, 8Bh, 0CEh, 0D8h, 0Dh, 70h, 5Ch
    db 07h, 01h, 0D9h, 0FEh, 0D8h, 4Ch, 24h, 20h, 0D8h, 0Dh, 0BCh, 0Bh, 08h, 01h, 0D8h, 47h
    db 44h, 0D9h, 5Ch, 24h, 10h, 0E8h, 0AEh, 0D7h, 0E4h, 0FFh, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h
    db 24h, 20h, 0D8h, 0Dh, 0BCh, 0Bh, 08h, 01h, 0D8h, 44h, 24h, 10h, 0D8h, 5Ch, 24h, 14h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 19h, 0D9h, 44h, 24h, 10h, 0D8h, 0Dh, 6Ch, 0B4h, 09h
    db 01h, 0D8h, 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 04h, 32h, 0DBh, 0EBh, 02h
    db 0B3h, 01h, 8Bh, 4Ch, 24h, 18h, 0E8h, 0C4h, 0D1h, 0E8h, 0FFh, 0Ah, 0C3h, 5Bh, 74h, 14h
    db 0D9h, 44h, 24h, 0Ch, 0D8h, 64h, 24h, 10h, 0D8h, 87h, 9Ch, 00h, 00h, 00h, 0D9h, 9Fh
    db 9Ch, 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 50h, 20h, 50h, 56h, 8Bh, 0CFh
    db 0E8h, 63h, 0C6h, 0E4h, 0FFh, 0D9h, 87h, 9Ch, 00h, 00h, 00h, 0D8h, 0Dh, 6Ch, 3Bh, 08h
    db 01h, 0D9h, 54h, 24h, 1Ch, 0D9h, 97h, 9Ch, 00h, 00h, 00h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 08h, 0D9h, 9Fh, 9Ch, 00h, 00h, 00h, 0EBh, 19h, 0D9h, 0E0h, 0D9h, 44h
    db 24h, 1Ch, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0D9h, 9Fh, 9Ch, 00h, 00h
    db 00h, 0EBh, 02h, 0DDh, 0D8h, 0D9h, 87h, 9Ch, 00h, 00h, 00h, 0D8h, 1Dh, 98h, 5Fh, 09h
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 29h, 8Ah, 8Eh, 18h, 01h, 00h, 00h, 84h, 0C9h
    db 0B8h, 40h, 00h, 00h, 00h, 78h, 08h, 84h, 86h, 1Ch, 01h, 00h, 00h, 75h, 29h, 81h
    db 0A6h, 18h, 01h, 00h, 00h, 7Fh, 0FFh, 0FFh, 0FFh, 09h, 86h, 1Ch, 01h, 00h, 00h, 0EBh
    db 10h, 0F6h, 86h, 1Ch, 01h, 00h, 00h, 40h, 74h, 0Eh, 83h, 0A6h, 1Ch, 01h, 00h, 00h
    db 0BFh, 8Bh, 0CEh, 0E8h, 85h, 96h, 0E6h, 0FFh, 0D9h, 46h, 40h, 51h, 0D8h, 87h, 9Ch, 00h
    db 00h, 00h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0E8h, 53h, 0FFh, 0E6h, 0FFh, 8Bh, 86h, 20h, 01h
    db 00h, 00h, 0A9h, 00h, 00h, 02h, 00h, 74h, 12h, 25h, 0FFh, 0FFh, 0FDh, 0FFh, 8Bh, 0CEh
    db 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 52h, 96h, 0E6h, 0FFh, 68h, 82h, 05h, 00h, 00h
    db 68h, 0A4h, 0DEh, 09h, 01h, 68h, 0FDh, 0ADh, 80h, 3Dh, 68h, 0FDh, 0ADh, 80h, 0BDh, 0E8h
    db 0C1h, 49h, 0E7h, 0FFh, 0D8h, 87h, 0A0h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0D9h, 97h, 0A0h
    db 00h, 00h, 00h, 0D8h, 1Dh, 54h, 0DFh, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah
    db 0C7h, 87h, 0A0h, 00h, 00h, 00h, 0FDh, 0ADh, 80h, 3Dh, 0D9h, 87h, 0A0h, 00h, 00h, 00h
    db 0D8h, 1Dh, 50h, 0DFh, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0C7h, 87h, 0A0h
    db 00h, 00h, 00h, 0FDh, 0ADh, 80h, 0BDh, 0D9h, 46h, 44h, 0D8h, 87h, 0A0h, 00h, 00h, 00h
    db 0D9h, 5Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 1Ch, 51h, 0E8h, 0DEh, 15h, 0E5h, 0FFh, 0D9h, 5Ch
    db 24h, 20h, 8Bh, 54h, 24h, 20h, 83h, 0C4h, 04h, 52h, 8Bh, 0CEh, 0E8h, 54h, 16h, 0E8h
    db 0FFh, 5Dh, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_001b80d0@@YAXXZ ENDP

; ghidra: FUN_005b8400  retail @ 0x001B8400 size 1878
_TEXT ENDS
_TEXT$d005b8400 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005B8400 size 1878
public ?d_001b8400@@YAXXZ
?d_001b8400@@YAXXZ PROC
    db 083h, 0ECh, 07Ch, 053h, 055h, 056h, 08Bh, 0B4h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 046h, 044h
    db 057h, 08Bh, 0F9h, 089h, 044h, 024h, 014h, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h
    db 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0B8h, 000h, 000h, 000h, 08Bh, 047h, 004h, 085h, 0C0h, 089h, 04Ch, 024h, 01Ch, 074h
    db 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 050h, 038h, 08Ah, 087h, 095h, 000h, 000h, 000h, 084h, 0C0h, 089h, 054h, 024h, 018h, 074h
    db 00Eh, 0D9h, 044h, 024h, 018h, 0D8h, 00Dh
    dd __real@3d800000
    db 0D9h, 05Ch, 024h, 018h, 08Bh, 08Eh, 004h, 002h, 000h, 000h, 085h, 0C9h, 0BDh, 001h, 000h, 000h
    db 000h, 074h, 010h, 08Bh, 001h, 0FFh, 090h, 0F0h, 001h, 000h, 000h, 084h, 0C0h, 074h, 004h, 0B3h
    db 001h, 0EBh, 002h, 032h, 0DBh, 0C7h, 087h, 0A4h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 08Bh
    db 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 048h, 070h, 0D9h, 044h, 024h, 01Ch, 0D8h, 08Eh, 0BCh, 000h, 000h, 000h, 08Bh, 056h, 03Ch
    db 083h, 0F9h, 005h, 08Bh, 04Eh, 038h, 089h, 04Ch, 024h, 020h, 0D9h, 05Ch, 024h, 01Ch, 089h, 054h
    db 024h, 024h, 08Bh, 0CEh, 00Fh, 085h, 082h, 003h, 000h, 000h
    call ?j_00040246@@YAXXZ
    db 0D9h, 044h, 024h, 01Ch, 0D8h, 008h, 0D8h, 044h, 024h, 020h, 0D9h, 05Ch, 024h, 020h, 0D9h, 044h
    db 024h, 01Ch, 0D8h, 048h, 004h, 08Bh, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 044h, 024h, 024h
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 000h, 0D8h, 064h, 024h, 020h, 0D9h, 040h, 004h, 0D8h, 064h, 024h
    db 024h, 0D9h, 0C1h, 0D9h, 0E1h, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 015h, 0D9h, 0C0h, 0D9h, 0E1h, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 01Eh, 006h, 000h, 000h, 0D9h, 0C9h, 051h, 0D9h, 0F3h
    db 0D8h, 064h, 024h, 018h, 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 08Bh, 084h, 024h, 0A0h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 018h, 083h, 0C4h, 004h, 085h, 0C0h
    db 074h, 006h, 08Bh, 04Ch, 024h, 014h, 089h, 008h, 0D9h, 044h, 024h, 014h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 08Bh, 047h, 004h, 075h, 043h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h
    db 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 044h, 024h, 014h, 0D8h, 058h, 038h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 089h, 0AFh
    db 0A4h, 000h, 000h, 000h, 0D9h, 044h, 024h, 014h, 0D8h, 09Ch, 024h, 098h, 000h, 000h, 000h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 055h, 08Bh, 094h, 024h, 098h, 000h, 000h, 000h, 089h, 054h, 024h
    db 014h, 0EBh, 048h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 040h, 038h, 0D9h, 0E0h, 0D8h, 05Ch, 024h, 014h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ah
    db 0C7h, 087h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 0D9h, 084h, 024h, 098h, 000h, 000h
    db 000h, 0D9h, 0E0h, 0D9h, 044h, 024h, 014h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h
    db 0D9h, 05Ch, 024h, 014h, 0EBh, 002h, 0DDh, 0D8h, 0D9h, 044h, 024h, 024h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 020h, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 038h, 0D9h, 044h, 024h, 020h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 024h, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 048h, 0DEh, 0C1h, 0D9h, 044h, 024h, 014h
    db 0D9h, 0FFh, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 014h, 0D9h, 0FEh, 0D9h, 044h, 024h, 01Ch
    db 0D9h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 018h, 0D8h, 0E9h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 01Ch, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 014h, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 03Ch, 0D9h, 044h, 024h, 014h, 0D8h, 0E2h
    db 0D9h, 05Ch, 024h, 030h, 0DDh, 0D9h, 0D9h, 044h, 024h, 018h, 0D8h, 0C1h, 0D9h, 0C9h, 0DDh, 0D8h
    db 0D9h, 044h, 024h, 014h, 0D8h, 064h, 024h, 018h, 0D9h, 044h, 024h, 014h, 0D8h, 044h, 024h, 018h
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 044h, 024h, 024h, 0D9h, 0E0h, 0D9h, 044h, 024h, 020h, 0D9h, 0E0h
    db 0D9h, 044h, 024h, 030h, 0D8h, 0CAh, 0D9h, 0C1h, 0D8h, 04Ch, 024h, 02Ch, 0DEh, 0C1h, 0D9h, 0C3h
    db 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DEh, 0C1h, 0D8h, 044h, 024h, 038h, 0D9h, 05Ch, 024h, 038h, 0D9h, 044h, 024h, 03Ch, 0D8h, 0C9h
    db 0D9h, 0C4h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 044h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DEh, 0C1h, 0D8h, 044h, 024h, 048h, 0D9h, 05Ch, 024h, 048h, 0D8h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C4h, 0D9h, 05Ch, 024h, 058h, 0DDh, 0D8h, 0D9h, 046h, 008h, 0D9h, 046h, 018h, 0D9h, 046h
    db 028h, 0D9h, 0C3h, 0D8h, 0C9h, 0D9h, 044h, 024h, 030h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h
    db 04Ch, 024h, 02Ch, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 05Ch, 0D9h, 044h, 024h, 044h, 0D8h, 0C9h, 0D9h
    db 0C5h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 03Ch, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h
    db 06Ch, 0D9h, 0C9h, 0D8h, 0C2h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C1h, 0D9h, 05Ch, 024h, 07Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 046h, 00Ch, 0D9h, 046h, 01Ch
    db 0D9h, 046h, 02Ch, 0D9h, 0C3h, 0D8h, 0C9h, 0D9h, 044h, 024h, 030h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h
    db 0C3h, 0D8h, 04Ch, 024h, 02Ch, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 060h, 0D9h, 044h, 024h, 044h, 0D8h
    db 0C9h, 0D9h, 0C5h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 03Ch, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h
    db 05Ch, 024h, 070h, 0D9h, 0C9h, 0D8h, 0C2h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C1h, 0D9h, 09Ch, 024h, 080h, 000h, 000h, 000h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 046h, 010h
    db 0D9h, 046h, 020h, 0D9h, 046h, 030h, 0D9h, 0C3h, 0D8h, 0C9h, 0D9h, 044h, 024h, 030h, 0D8h, 0CBh
    db 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 04Ch, 024h, 02Ch, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 064h, 0D9h, 044h
    db 024h, 044h, 0D8h, 0C9h, 0D9h, 0C5h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 03Ch, 0D8h, 0CCh
    db 0DEh, 0C1h, 0D9h, 05Ch, 024h, 074h, 0D9h, 0C9h, 0D8h, 0C2h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 08Bh, 056h, 034h, 08Bh, 04Eh, 024h, 08Bh, 046h, 014h, 0D8h, 0C1h, 089h, 054h, 024h, 01Ch, 089h
    db 04Ch, 024h, 018h, 089h, 044h, 024h, 014h, 0D9h, 09Ch, 024h, 084h, 000h, 000h, 000h, 08Dh, 044h
    db 024h, 05Ch, 050h, 0DDh, 0D8h, 08Bh, 0CFh, 0DDh, 0D8h, 0D8h, 04Ch, 024h, 020h, 0D9h, 044h, 024h
    db 034h, 0D8h, 04Ch, 024h, 01Ch, 0DEh, 0C1h, 0D9h, 044h, 024h, 018h, 0D8h, 04Ch, 024h, 030h, 0DEh
    db 0C1h, 0D8h, 044h, 024h, 03Ch, 0D9h, 05Ch, 024h, 06Ch, 0D9h, 044h, 024h, 048h, 0D8h, 04Ch, 024h
    db 020h, 0D9h, 0C9h, 0D8h, 04Ch, 024h, 01Ch, 0DEh, 0C1h, 0D9h, 044h, 024h, 040h, 0D8h, 04Ch, 024h
    db 018h, 0DEh, 0C1h, 0D8h, 044h, 024h, 04Ch, 0D9h, 05Ch, 024h, 07Ch, 0DDh, 0D8h, 0D9h, 044h, 024h
    db 01Ch, 0D8h, 044h, 024h, 018h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 044h, 024h, 05Ch, 0D8h, 044h, 024h, 020h, 0D9h, 09Ch, 024h, 08Ch, 000h, 000h, 000h
    call ?j_00033bae@@YAXXZ
    db 0E9h, 069h, 001h, 000h, 000h
    call ?j_00040246@@YAXXZ
    db 0D9h, 044h, 024h, 01Ch, 0D8h, 008h, 0D8h, 044h, 024h, 020h, 0D9h, 044h, 024h, 01Ch, 0D8h, 048h
    db 004h, 08Bh, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 044h, 024h, 024h, 0D9h, 000h, 0D8h, 0E2h
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 040h, 004h, 0D8h, 0E1h, 0DDh, 0DAh, 0DDh, 0D8h, 0D9h, 044h, 024h
    db 01Ch, 0D9h, 0E1h, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 015h, 0D9h, 0C0h, 0D9h, 0E1h, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 0A0h, 002h, 000h, 000h, 0D9h, 044h, 024h, 01Ch, 051h
    db 0D9h, 0F3h, 0D8h, 064h, 024h, 018h, 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 08Bh, 084h, 024h, 0A0h, 000h, 000h, 000h, 083h, 0C4h, 004h, 085h, 0C0h, 074h, 002h, 0D9h, 010h
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 02Ah, 0D8h, 054h, 024h, 018h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 075h, 006h, 089h, 0AFh, 0A4h, 000h, 000h, 000h, 0D8h, 094h, 024h, 098h, 000h, 000h, 000h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 044h, 0DDh, 0D8h, 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0EBh
    db 039h, 0D9h, 044h, 024h, 018h, 0D9h, 0E0h, 0D9h, 0C1h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h
    db 07Ah, 00Ah, 0C7h, 087h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 0D9h, 084h, 024h, 098h
    db 000h, 000h, 000h, 0D9h, 0E0h, 0D9h, 05Ch, 024h, 01Ch, 0D8h, 054h, 024h, 01Ch, 0DFh, 0E0h, 0F6h
    db 0C4h, 005h, 07Ah, 006h, 0DDh, 0D8h, 0D9h, 044h, 024h, 01Ch, 084h, 0DBh, 074h, 006h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 0C0h, 0D9h, 0FFh, 0D9h, 05Ch, 024h, 014h, 0D9h, 0FEh, 0D9h, 047h, 064h, 0D9h, 047h, 074h
    db 0D9h, 0C1h, 0D8h, 04Ch, 024h, 014h, 0D9h, 0C1h, 0D8h, 0CCh, 0DEh, 0E9h, 0D9h, 05Fh, 064h, 0D8h
    db 04Ch, 024h, 014h, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 05Fh, 074h, 0D9h, 047h, 068h, 0D9h
    db 047h, 078h, 0D9h, 0C1h, 0D8h, 04Ch, 024h, 014h, 0D9h, 0C1h, 0D8h, 0CCh, 0DEh, 0E9h, 0D9h, 05Fh
    db 068h, 0D8h, 04Ch, 024h, 014h, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 05Fh, 078h, 0D9h, 047h
    db 06Ch, 0D9h, 047h, 07Ch, 0D9h, 0C1h, 0D8h, 04Ch, 024h, 014h, 0D9h, 0C1h, 0D8h, 0CCh, 0DEh, 0E9h
    db 0D9h, 05Fh, 06Ch, 0D8h, 04Ch, 024h, 014h, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 05Fh, 07Ch
    db 0DDh, 0D8h, 08Bh, 047h, 03Ch, 056h, 08Bh, 0CFh, 089h, 044h, 024h, 020h
    call ?j_000230ab@@YAXXZ
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0C6h, 044h, 024h, 013h, 001h, 0D9h, 05Ch, 024h, 018h, 0D9h, 044h, 024h, 01Ch, 0D8h, 05Ch, 024h
    db 018h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 022h, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh
    db 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Ah, 088h, 0FDh, 000h, 000h, 000h, 084h, 0C9h, 075h, 005h, 0C6h, 044h, 024h, 013h, 000h, 084h
    db 0DBh, 074h, 005h, 0C6h, 044h, 024h, 013h, 000h, 08Ah, 087h, 095h, 000h, 000h, 000h, 084h, 0C0h
    db 0BBh, 000h, 000h, 000h, 020h, 0BDh, 000h, 000h, 000h, 040h, 075h, 076h, 08Bh, 086h, 01Ch, 001h
    db 000h, 000h, 085h, 0C3h, 074h, 012h, 025h, 0FFh, 0FFh, 0FFh, 0DFh, 08Bh, 0CEh, 089h, 086h, 01Ch
    db 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 086h, 01Ch, 001h, 000h, 000h, 085h, 0C5h, 074h, 012h, 025h, 0FFh, 0FFh, 0FFh, 0BFh, 08Bh
    db 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 020h, 001h, 000h, 000h, 002h, 074h, 016h, 08Bh, 086h, 020h, 001h, 000h, 000h, 083h
    db 0E0h, 0FDh, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 020h, 001h, 000h, 000h, 004h, 074h, 016h, 08Bh, 086h, 020h, 001h, 000h, 000h, 083h
    db 0E0h, 0FBh, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Ah, 044h, 024h, 013h, 084h, 0C0h, 00Fh, 084h, 0A5h, 000h, 000h, 000h, 08Bh, 0BFh, 0A4h, 000h
    db 000h, 000h, 083h, 0FFh, 0FFh, 075h, 056h, 0D9h, 044h, 024h, 01Ch, 0D8h, 05Ch, 024h, 018h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 024h, 06Ah, 07Eh, 068h, 082h, 000h, 000h, 000h, 06Ah, 000h, 08Dh
    db 04Ch, 024h, 038h
    call ?j_00004048@@YAXXZ
    db 050h, 08Bh, 0CEh
    call ?j_0001a9dd@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 07Ch, 0C2h, 010h, 000h, 08Bh, 086h, 01Ch, 001h, 000h, 000h
    db 085h, 0C5h, 075h, 05Dh, 00Bh, 0C5h, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 07Ch, 0C2h, 010h, 000h, 083h, 0FFh, 001h, 075h, 03Fh, 0D9h
    db 044h, 024h, 01Ch, 0D8h, 05Ch, 024h, 018h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 009h, 06Ah, 07Dh
    db 068h, 081h, 000h, 000h, 000h, 0EBh, 0A3h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 085h, 0C3h, 075h
    db 01Dh, 00Bh, 0C3h, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 07Ch, 0C2h, 010h, 000h, 0DDh, 0D8h, 0DDh, 0D8h, 05Fh, 05Eh
    db 05Dh, 05Bh, 083h, 0C4h, 07Ch, 0C2h, 010h, 000h
?d_001b8400@@YAXXZ ENDP
_TEXT$d005b8400 ENDS
_TEXT SEGMENT

; ghidra: FUN_005b8d30  retail @ 0x001B8D30 size 1676
_TEXT ENDS
_TEXT$d005b8d30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005B8D30 size 1676
public ?d_001b8d30@@YAXXZ
?d_001b8d30@@YAXXZ PROC
    db 083h, 0ECh, 04Ch, 053h, 056h, 08Bh, 074h, 024h, 058h, 057h, 056h, 08Bh, 0F9h
    call ?j_000230ab@@YAXXZ
    db 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 068h, 0D8h, 05Ch, 024h, 014h, 0DFh, 0E0h, 0F6h, 0C4h
    db 041h, 075h, 008h, 08Bh, 044h, 024h, 014h, 089h, 044h, 024h, 068h, 08Bh, 04Ch, 024h, 068h, 08Bh
    db 057h, 03Ch, 089h, 04Ch, 024h, 05Ch, 056h, 08Bh, 0CFh, 089h, 054h, 024h, 014h
    call ?j_000230ab@@YAXXZ
    db 0D9h, 05Ch, 024h, 00Ch, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h
    db 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 040h, 04Ch, 085h, 0C0h, 089h, 044h, 024h, 018h, 0DBh, 044h, 024h, 018h, 07Dh, 006h, 0D8h
    db 005h
    dd __real@4f800000
    db 0D8h, 07Ch, 024h, 00Ch, 0D9h, 054h, 024h, 00Ch, 0D8h, 05Fh, 030h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 075h, 007h, 08Bh, 04Fh, 030h, 089h, 04Ch, 024h, 00Ch, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch
    db 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 040h, 024h, 0D9h, 044h, 024h, 010h, 0D8h, 0E1h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 00Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 020h, 0D9h, 044h, 024h, 00Ch, 0D8h, 0F9h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 0C9h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D8h, 0C2h, 0DEh, 0C9h, 0D8h, 00Dh
    dd ?g_bfmeK2SMA@@3MA
    db 0DDh, 0D9h, 0D9h, 005h
    dd ?g_bfmeK1266A@@3MB
    db 0D8h, 0C9h, 0D8h, 05Ch, 024h, 064h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 004h, 083h, 067h, 040h
    db 0FEh, 0D9h, 047h, 03Ch, 0D8h, 064h, 024h, 00Ch, 0D9h, 044h, 024h, 068h, 0D8h, 0D9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 005h, 07Ah, 019h, 0D9h, 054h, 024h, 05Ch, 0D8h, 05Ch, 024h, 00Ch, 0DFh, 0E0h, 0F6h
    db 0C4h, 005h, 07Ah, 00Ch, 08Bh, 054h, 024h, 00Ch, 089h, 054h, 024h, 05Ch, 0EBh, 002h, 0DDh, 0D8h
    db 0D9h, 044h, 024h, 064h, 0D8h, 0D9h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 07Ah, 035h, 08Bh
    db 047h, 040h, 08Bh, 0C8h, 0C1h, 0E9h, 004h, 0F6h, 0C1h, 001h, 075h, 028h, 083h, 0C8h, 001h, 056h
    db 08Bh, 0CFh, 089h, 047h, 040h
    call ?j_000235e2@@YAXXZ
    db 0D8h, 06Fh, 03Ch, 0D9h, 054h, 024h, 05Ch, 0D8h, 05Ch, 024h, 00Ch, 0DFh, 0E0h, 0F6h, 0C4h, 005h
    db 07Ah, 008h, 08Bh, 054h, 024h, 00Ch, 089h, 054h, 024h, 05Ch, 08Bh, 044h, 024h, 060h, 0D9h, 044h
    db 024h, 05Ch, 08Bh, 008h, 0D8h, 05Fh, 03Ch, 08Bh, 050h, 004h, 08Bh, 040h, 008h, 089h, 044h, 024h
    db 024h, 0DFh, 0E0h, 0C7h, 044h, 024h, 054h, 0FFh, 0FFh, 0FFh, 07Fh, 08Dh, 05Eh, 038h, 0F6h, 0C4h
    db 041h, 089h, 04Ch, 024h, 01Ch, 089h, 054h, 024h, 020h, 075h, 014h, 0F6h, 047h, 040h, 001h, 075h
    db 00Eh, 056h, 08Bh, 0CFh
    call ?j_00024f7d@@YAXXZ
    db 0D8h, 047h, 03Ch, 0D9h, 05Fh, 03Ch, 0D9h, 047h, 03Ch, 0D8h, 05Ch, 024h, 05Ch, 0DFh, 0E0h, 0F6h
    db 0C4h, 041h, 075h, 01Ch, 0D9h, 047h, 03Ch, 0D8h, 064h, 024h, 00Ch, 0D9h, 057h, 03Ch, 0D8h, 05Ch
    db 024h, 05Ch, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 007h, 08Bh, 04Ch, 024h, 05Ch, 089h, 04Fh, 03Ch
    db 08Bh, 086h, 004h, 002h, 000h, 000h, 085h, 0C0h, 08Bh, 057h, 03Ch, 055h, 089h, 054h, 024h, 06Ch
    db 074h, 008h, 08Bh, 0A8h, 040h, 001h, 000h, 000h, 0EBh, 002h, 033h, 0EDh, 085h, 0EDh, 00Fh, 084h
    db 002h, 001h, 000h, 000h, 08Bh, 045h, 000h, 040h, 06Ah, 001h, 089h, 045h, 000h, 08Dh, 044h, 024h
    db 03Ch, 050h, 057h, 056h, 08Bh, 0CDh
    call ?j_00008a9e@@YAXXZ
    db 08Bh, 04Ch, 024h, 03Ch, 08Bh, 054h, 024h, 040h, 08Bh, 044h, 024h, 044h, 089h, 04Ch, 024h, 02Ch
    db 06Ah, 000h, 08Dh, 04Ch, 024h, 03Ch, 051h, 057h, 056h, 08Bh, 0CDh, 089h, 054h, 024h, 040h, 089h
    db 044h, 024h, 044h
    call ?j_00008a9e@@YAXXZ
    db 08Bh, 045h, 000h, 085h, 0C0h, 074h, 004h, 048h, 089h, 045h, 000h, 08Bh, 054h, 024h, 03Ch, 08Bh
    db 044h, 024h, 040h, 08Bh, 04Ch, 024h, 044h, 089h, 054h, 024h, 020h, 089h, 044h, 024h, 024h, 08Bh
    db 044h, 024h, 020h, 08Dh, 096h, 078h, 001h, 000h, 000h, 089h, 04Ch, 024h, 028h, 08Bh, 04Ch, 024h
    db 024h, 089h, 002h, 08Bh, 044h, 024h, 028h, 089h, 04Ah, 004h, 0C6h, 086h, 086h, 001h, 000h, 000h
    db 001h, 089h, 042h, 008h, 0D9h, 044h, 024h, 030h, 08Ah, 086h, 086h, 001h, 000h, 000h, 0D9h, 043h
    db 008h, 084h, 0C0h, 05Dh, 08Dh, 086h, 078h, 001h, 000h, 000h, 075h, 002h, 08Bh, 0C3h, 08Bh, 010h
    db 0D9h, 0C9h, 08Bh, 040h, 004h, 08Bh, 04Bh, 008h, 089h, 054h, 024h, 01Ch, 089h, 044h, 024h, 020h
    db 08Bh, 044h, 024h, 01Ch, 089h, 04Ch, 024h, 024h, 08Bh, 04Ch, 024h, 020h, 08Dh, 096h, 078h, 001h
    db 000h, 000h, 089h, 002h, 08Bh, 044h, 024h, 024h, 089h, 04Ah, 004h, 08Bh, 04Ch, 024h, 028h, 0C6h
    db 086h, 086h, 001h, 000h, 000h, 001h, 089h, 042h, 008h, 0D9h, 09Fh, 080h, 000h, 000h, 000h, 089h
    db 04Fh, 070h, 0D9h, 09Fh, 090h, 000h, 000h, 000h, 08Bh, 047h, 004h, 085h, 0C0h, 0D9h, 047h, 03Ch
    db 0D8h, 064h, 024h, 010h, 0D9h, 05Ch, 024h, 060h, 00Fh, 085h, 0B9h, 000h, 000h, 000h, 0E9h, 0C0h
    db 000h, 000h, 000h, 0D9h, 044h, 024h, 020h, 08Bh, 0CBh, 0D8h, 023h, 08Bh, 011h, 08Bh, 041h, 004h
    db 08Bh, 049h, 008h, 0D9h, 05Ch, 024h, 020h, 089h, 044h, 024h, 030h, 0D9h, 044h, 024h, 024h, 089h
    db 054h, 024h, 02Ch, 0D8h, 063h, 004h, 089h, 04Ch, 024h, 034h, 0C7h, 044h, 024h, 028h, 000h, 000h
    db 000h, 000h, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 020h, 0D8h, 04Ch, 024h, 020h, 0D9h, 044h
    db 024h, 024h, 0D8h, 04Ch, 024h, 024h, 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 044h, 024h, 06Ch, 0D8h, 01Dh
    dd __real@40000000
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 06Ch, 000h, 000h, 000h, 040h, 0D9h
    db 044h, 024h, 06Ch, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 004h, 0D9h, 054h, 024h, 06Ch
    db 0D8h, 01Dh
    dd ?g_millisecondsToSeconds@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 085h, 0FFh, 0FEh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 020h
    call ?j_0002bd82@@YAXXZ
    db 0D9h, 044h, 024h, 020h, 0D8h, 04Ch, 024h, 06Ch, 0D9h, 044h, 024h, 024h, 0D8h, 04Ch, 024h, 06Ch
    db 0D9h, 044h, 024h, 02Ch, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 030h, 0D8h, 0C1h
    db 0DDh, 0DAh, 0DDh, 0D8h, 0E9h, 0D1h, 0FEh, 0FFh, 0FFh, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 044h, 024h, 014h, 056h, 0D8h, 048h, 078h, 08Bh, 0CFh, 0D9h, 05Ch, 024h, 06Ch
    call ?j_000230ab@@YAXXZ
    db 08Bh, 047h, 004h, 0D9h, 05Ch, 024h, 05Ch, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h
    db 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 050h, 040h, 0DBh, 040h, 040h, 085h, 0D2h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 07Ch, 024h, 05Ch, 0D8h, 057h, 02Ch, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 005h, 0DDh, 0D8h
    db 0D9h, 047h, 02Ch, 0D9h, 005h
    dd __real@3ecccccd
    db 0D8h, 0C9h, 0D9h, 044h, 024h, 060h, 0DEh, 0D9h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 041h, 00Fh
    db 085h, 0ECh, 000h, 000h, 000h, 0D9h, 044h, 024h, 010h, 0D8h, 05Ch, 024h, 068h, 0DFh, 0E0h, 0F6h
    db 0C4h, 005h, 00Fh, 08Ah, 0D9h, 000h, 000h, 000h, 0F6h, 086h, 020h, 001h, 000h, 000h, 001h, 074h
    db 016h, 08Bh, 086h, 020h, 001h, 000h, 000h, 083h, 0E0h, 0FEh, 08Bh, 0CEh, 089h, 086h, 020h, 001h
    db 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 07Fh, 004h, 085h, 0FFh, 075h, 004h, 033h, 0C0h, 0EBh, 010h, 08Bh, 04Fh, 004h, 085h, 0C9h
    db 074h, 007h
    call ?j_000022bb@@YAXXZ
    db 0EBh, 002h, 08Bh, 0C7h, 0D9h, 044h, 024h, 064h, 0D8h, 058h, 07Ch, 0DFh, 0E0h, 0F6h, 0C4h, 005h
    db 08Bh, 086h, 01Ch, 001h, 000h, 000h, 07Ah, 041h, 085h, 0C0h, 079h, 012h, 025h, 0FFh, 0FFh, 0FFh
    db 07Fh, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 086h, 01Ch, 001h, 000h, 000h, 0BBh, 000h, 000h, 000h, 008h, 085h, 0C3h, 00Fh, 085h, 0D4h
    db 001h, 000h, 000h, 00Bh, 0C3h, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 04Ch, 0C2h, 010h, 000h, 0A9h, 000h, 000h, 000h, 008h, 074h, 018h
    db 08Bh, 086h, 01Ch, 001h, 000h, 000h, 025h, 0FFh, 0FFh, 0FFh, 0F7h, 08Bh, 0CEh, 089h, 086h, 01Ch
    db 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 08Eh, 01Ch, 001h, 000h, 000h, 0B8h, 000h, 000h, 000h, 080h, 085h, 0C8h, 00Fh, 085h, 08Ah
    db 001h, 000h, 000h, 00Bh, 0C8h, 089h, 08Eh, 01Ch, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 04Ch, 0C2h, 010h, 000h, 0F6h, 047h, 040h, 001h, 00Fh, 084h, 0CDh
    db 000h, 000h, 000h, 0D9h, 047h, 03Ch, 0D8h, 05Ch, 024h, 068h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh
    db 08Ah, 0BBh, 000h, 000h, 000h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 085h, 0C0h, 079h, 012h, 025h
    db 0FFh, 0FFh, 0FFh, 07Fh, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Ah, 087h, 094h, 000h, 000h, 000h, 084h, 0C0h, 074h, 04Bh, 08Bh, 086h, 01Ch, 001h, 000h, 000h
    db 0A9h, 000h, 000h, 000h, 008h, 074h, 012h, 025h, 0FFh, 0FFh, 0FFh, 0F7h, 08Bh, 0CEh, 089h, 086h
    db 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 020h, 001h, 000h, 000h, 001h, 00Fh, 085h, 004h, 001h, 000h, 000h, 08Bh, 086h, 020h
    db 001h, 000h, 000h, 083h, 0C8h, 001h, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 04Ch, 0C2h, 010h, 000h, 0F6h, 086h, 020h, 001h, 000h, 000h, 001h
    db 074h, 016h, 08Bh, 086h, 020h, 001h, 000h, 000h, 083h, 0E0h, 0FEh, 08Bh, 0CEh, 089h, 086h, 020h
    db 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 086h, 01Ch, 001h, 000h, 000h, 0BBh, 000h, 000h, 000h, 008h, 085h, 0C3h, 00Fh, 085h, 0B3h
    db 000h, 000h, 000h, 00Bh, 0C3h, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 04Ch, 0C2h, 010h, 000h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 085h
    db 0C0h, 079h, 012h, 025h, 0FFh, 0FFh, 0FFh, 07Fh, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 020h, 001h, 000h, 000h, 001h, 074h, 016h, 08Bh, 086h, 020h, 001h, 000h, 000h, 083h
    db 0E0h, 0FEh, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0D9h, 044h, 024h, 010h, 0D8h, 05Ch, 024h, 068h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 051h, 08Bh
    db 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 044h, 024h, 064h, 0BBh, 000h, 000h, 000h, 008h, 0D8h, 058h, 07Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 041h, 075h, 01Ch, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 085h, 0C3h, 074h, 01Ah, 025h, 0FFh, 0FFh
    db 0FFh, 0F7h, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 085h, 09Eh, 01Ch, 001h, 000h, 000h, 075h, 007h, 0C6h, 087h, 094h, 000h, 000h, 000h, 001h, 05Fh
    db 05Eh, 05Bh, 083h, 0C4h, 04Ch, 0C2h, 010h, 000h
?d_001b8d30@@YAXXZ ENDP
_TEXT$d005b8d30 ENDS
_TEXT SEGMENT

; ghidra: FUN_005b9590  retail @ 0x001B9590 size 25
public ?d_001b9590@@YAXXZ
?d_001b9590@@YAXXZ PROC
    db 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh, 41h, 5Ch, 3Bh, 42h, 3Ch, 73h, 05h, 0E9h, 08h
    db 9Bh, 0E6h, 0FFh, 0D9h, 41h, 58h, 0C2h, 04h, 00h
?d_001b9590@@YAXXZ ENDP

; ghidra: FUN_005b95b0  retail @ 0x001B95B0 size 603
public ?d_001b95b0@@YAXXZ
?d_001b95b0@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 55h, 56h, 57h, 8Bh, 0F9h, 0D9h, 47h, 48h, 0D8h, 1Dh, 50h, 53h, 07h
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 33h, 02h, 00h, 00h, 8Bh, 74h, 24h, 2Ch
    db 8Bh, 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 89h, 44h, 24h, 0Ch, 0Fh, 84h, 1Dh, 02h
    db 00h, 00h, 8Bh, 44h, 24h, 30h, 0D9h, 00h, 8Bh, 4Eh, 40h, 0D9h, 40h, 04h, 8Bh, 46h
    db 3Ch, 0D9h, 46h, 38h, 89h, 44h, 24h, 14h, 0D9h, 0CAh, 89h, 4Ch, 24h, 18h, 0D8h, 0E2h
    db 6Ah, 00h, 8Bh, 0CEh, 0D9h, 5Ch, 24h, 20h, 0DDh, 0D9h, 0D8h, 64h, 24h, 18h, 0D9h, 0C0h
    db 0DEh, 0C9h, 0D9h, 44h, 24h, 20h, 0D8h, 4Ch, 24h, 20h, 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 5Ch
    db 24h, 30h, 0D9h, 44h, 24h, 1Ch, 0D8h, 64h, 24h, 38h, 0D9h, 5Ch, 24h, 34h, 0E8h, 4Ch
    db 84h, 0E7h, 0FFh, 8Bh, 0E8h, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 74h, 3Eh, 0D9h, 44h
    db 24h, 30h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 7Ah, 1Eh, 8Bh
    db 8Eh, 1Ch, 01h, 00h, 00h, 0B8h, 00h, 00h, 08h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h
    db 89h, 8Eh, 1Ch, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0B0h, 82h, 0E6h, 0FFh, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 5Fh, 5Eh, 5Dh, 83h, 0C4h, 1Ch, 0C2h, 0Ch, 00h, 85h, 0EDh, 0Fh, 84h
    db 71h, 01h, 00h, 00h, 8Bh, 47h, 04h, 85h, 0C0h, 8Dh, 77h, 04h, 74h, 0Ch, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 21h, 8Ch, 0E4h, 0FFh, 0D9h, 40h, 60h, 0D8h, 1Dh, 50h
    db 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 47h, 01h, 00h, 00h, 8Bh, 87h
    db 98h, 00h, 00h, 00h, 83h, 0E8h, 00h, 0Fh, 84h, 0F3h, 00h, 00h, 00h, 48h, 74h, 74h
    db 48h, 0Fh, 85h, 38h, 01h, 00h, 00h, 0D9h, 47h, 44h, 8Bh, 0CEh, 0D8h, 67h, 48h, 0D9h
    db 5Ch, 24h, 0Ch, 0E8h, 0BDh, 0D7h, 0E6h, 0FFh, 0D9h, 44h, 24h, 2Ch, 0C7h, 44h, 24h, 34h
    db 00h, 00h, 80h, 3Fh, 0D8h, 70h, 60h, 0DCh, 0C0h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 05h, 34h
    db 53h, 07h, 01h, 0D8h, 5Ch, 24h, 2Ch, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 8Dh, 44h, 24h, 34h
    db 7Bh, 04h, 8Dh, 44h, 24h, 2Ch, 0D9h, 44h, 24h, 0Ch, 0D8h, 08h, 0D8h, 47h, 48h, 0D9h
    db 44h, 24h, 30h, 0D8h, 5Fh, 44h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 0E1h, 00h, 00h
    db 00h, 0C7h, 87h, 98h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 83h, 0C4h
    db 1Ch, 0C2h, 0Ch, 00h, 0D9h, 47h, 44h, 8Bh, 0CEh, 0D8h, 67h, 48h, 0D9h, 5Ch, 24h, 34h
    db 0E8h, 50h, 0D7h, 0E6h, 0FFh, 0D9h, 44h, 24h, 2Ch, 0C7h, 44h, 24h, 30h, 00h, 00h, 80h
    db 3Fh, 0D8h, 70h, 60h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 5Ch
    db 24h, 2Ch, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 8Dh, 44h, 24h, 30h, 7Bh, 04h, 8Dh, 44h, 24h
    db 2Ch, 0D9h, 44h, 24h, 34h, 8Bh, 0CDh, 0D8h, 08h, 0D8h, 47h, 48h, 0D9h, 5Ch, 24h, 2Ch
    db 0E8h, 07h, 00h, 0E5h, 0FFh, 85h, 0C0h, 75h, 10h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 11h, 0FFh
    db 92h, 84h, 01h, 00h, 00h, 84h, 0C0h, 75h, 0Ah, 0C7h, 87h, 98h, 00h, 00h, 00h, 02h
    db 00h, 00h, 00h, 0D9h, 44h, 24h, 2Ch, 5Fh, 5Eh, 5Dh, 83h, 0C4h, 1Ch, 0C2h, 0Ch, 00h
    db 8Bh, 47h, 40h, 0C1h, 0E8h, 02h, 0A8h, 01h, 75h, 45h, 8Bh, 0CEh, 0E8h, 0D4h, 0D6h, 0E6h
    db 0FFh, 0D9h, 44h, 24h, 2Ch, 0D8h, 58h, 60h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 30h, 8Bh
    db 4Ch, 24h, 0Ch, 8Bh, 11h, 0FFh, 92h, 84h, 01h, 00h, 00h, 84h, 0C0h, 74h, 20h, 0D9h
    db 47h, 44h, 0C7h, 87h, 98h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 83h
    db 0C4h, 1Ch, 0C2h, 0Ch, 00h, 0C7h, 87h, 98h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0D9h
    db 47h, 44h, 5Fh, 5Eh, 5Dh, 83h, 0C4h, 1Ch, 0C2h, 0Ch, 00h
?d_001b95b0@@YAXXZ ENDP

; ghidra: FUN_005b98b0  retail @ 0x001B98B0 size 113
public ?d_001b98b0@@YAXXZ
?d_001b98b0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 2Bh, 46h, 04h, 57h, 0C1h, 0F8h, 02h, 33h, 0FFh, 85h
    db 0C0h, 76h, 1Eh, 8Bh, 4Eh, 04h, 8Bh, 0Ch, 0B9h, 85h, 0C9h, 74h, 06h, 8Bh, 11h, 6Ah
    db 01h, 0FFh, 12h, 8Bh, 46h, 08h, 2Bh, 46h, 04h, 47h, 0C1h, 0F8h, 02h, 3Bh, 0F8h, 72h
    db 0E2h, 8Bh, 46h, 08h, 3Bh, 0C0h, 8Bh, 4Eh, 04h, 75h, 13h, 8Bh, 0C1h, 89h, 46h, 08h
    db 5Fh, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 0C6h, 46h, 14h, 00h, 5Eh, 0C3h, 8Bh, 0F8h
    db 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h
    db 89h, 46h, 08h, 5Fh, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 0C6h, 46h, 14h, 00h, 5Eh
    db 0C3h
?d_001b98b0@@YAXXZ ENDP

; ghidra: FUN_005b9980  retail @ 0x001B9980 size 168
public ?d_001b9980@@YAXXZ
?d_001b9980@@YAXXZ PROC
    db 51h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 89h, 4Ch, 24h, 04h, 0Fh, 84h, 91h, 00h
    db 00h, 00h, 53h, 55h, 56h, 8Bh, 0CFh, 0E8h, 0A4h, 0DFh, 6Ch, 00h, 33h, 0DBh, 0B0h, 01h
    db 33h, 0EDh, 8Bh, 74h, 24h, 10h, 8Bh, 0CDh, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h, 00h, 00h
    db 0D3h, 0E2h, 8Bh, 0CDh, 0C1h, 0E9h, 05h, 85h, 14h, 8Eh, 74h, 5Bh, 8Bh, 34h, 0ADh, 18h
    db 69h, 2Ah, 01h, 85h, 0F6h, 74h, 50h, 84h, 0C0h, 75h, 0Eh, 6Ah, 02h, 68h, 5Ch, 0DFh
    db 09h, 01h, 8Bh, 0CFh, 0E8h, 87h, 0E3h, 6Ch, 00h, 3Bh, 5Ch, 24h, 1Ch, 7Ch, 10h, 6Ah
    db 01h, 68h, 94h, 02h, 08h, 01h, 8Bh, 0CFh, 33h, 0DBh, 0E8h, 71h, 0E3h, 6Ch, 00h, 8Bh
    db 0C6h, 0C6h, 44h, 24h, 18h, 00h, 8Dh, 50h, 01h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 50h, 56h, 8Bh, 0CFh, 0E8h, 4Eh, 0E3h
    db 6Ch, 00h, 8Ah, 44h, 24h, 18h, 43h, 45h, 81h, 0FDh, 30h, 01h, 00h, 00h, 7Ch, 82h
    db 5Eh, 5Dh, 5Bh, 5Fh, 59h, 0C2h, 08h, 00h
?d_001b9980@@YAXXZ ENDP

; ghidra: FUN_005b9a90  retail @ 0x001B9A90 size 36
public ?d_001b9a90@@YAXXZ
?d_001b9a90@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h
    db 10h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 81h, 14h, 01h, 00h, 00h, 0E8h, 6Ch, 7Eh, 0E6h
    db 0FFh, 0C2h, 04h, 00h
?d_001b9a90@@YAXXZ ENDP

; ghidra: FUN_005b9ac0  retail @ 0x001B9AC0 size 36
public ?d_001b9ac0@@YAXXZ
?d_001b9ac0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h
    db 10h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 81h, 14h, 01h, 00h, 00h, 0E8h, 3Ch, 7Eh, 0E6h
    db 0FFh, 0C2h, 04h, 00h
?d_001b9ac0@@YAXXZ ENDP

; ghidra: FUN_005b9af0  retail @ 0x001B9AF0 size 36
public ?d_001b9af0@@YAXXZ
?d_001b9af0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h
    db 10h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 81h, 14h, 01h, 00h, 00h, 0E8h, 0Ch, 7Eh, 0E6h
    db 0FFh, 0C2h, 04h, 00h
?d_001b9af0@@YAXXZ ENDP

; ghidra: FUN_005b9b20  retail @ 0x001B9B20 size 36
public ?d_001b9b20@@YAXXZ
?d_001b9b20@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 81h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h
    db 10h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 89h, 81h, 14h, 01h, 00h, 00h, 0E8h, 0DCh, 7Dh, 0E6h
    db 0FFh, 0C2h, 04h, 00h
?d_001b9b20@@YAXXZ ENDP

; ghidra: FUN_005b9b50  retail @ 0x001B9B50 size 142
public ?d_001b9b50@@YAXXZ
?d_001b9b50@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 0D8h, 5Eh, 3Ch, 57h, 8Bh, 7Ch, 24h, 10h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 20h, 57h, 0E8h, 11h, 0B4h, 0E6h, 0FFh, 0D8h, 46h, 3Ch, 0D9h
    db 56h, 3Ch, 0D8h, 5Ch, 24h, 0Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 10h, 8Bh, 44h, 24h
    db 0Ch, 89h, 46h, 3Ch, 0EBh, 07h, 8Bh, 4Ch, 24h, 0Ch, 89h, 4Eh, 3Ch, 57h, 8Bh, 0CEh
    db 0E8h, 16h, 95h, 0E6h, 0FFh, 8Bh, 56h, 3Ch, 89h, 54h, 24h, 0Ch, 0D9h, 44h, 24h, 0Ch
    db 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Eh, 5Fh, 0DDh, 0D8h
    db 0C7h, 46h, 3Ch, 00h, 00h, 00h, 00h, 5Eh, 0C2h, 08h, 00h, 0D9h, 44h, 24h, 0Ch, 0D8h
    db 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 5Fh, 0D9h, 5Eh, 3Ch, 5Eh, 0C2h, 08h, 00h
    db 8Bh, 44h, 24h, 0Ch, 0DDh, 0D8h, 5Fh, 89h, 46h, 3Ch, 5Eh, 0C2h, 08h, 00h
?d_001b9b50@@YAXXZ ENDP

; ghidra: FUN_005b9c10  retail @ 0x001B9C10 size 49
public ?d_001b9c10@@YAXXZ
?d_001b9c10@@YAXXZ PROC
    db 51h, 8Bh, 54h, 24h, 08h, 8Bh, 41h, 3Ch, 52h, 89h, 44h, 24h, 04h, 0E8h, 89h, 94h
    db 0E6h, 0FFh, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0D8h, 1Ch, 24h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 7Ah, 09h, 0B8h, 01h, 00h, 00h, 00h, 59h, 0C2h, 04h, 00h, 33h, 0C0h, 59h, 0C2h, 04h
    db 00h
?d_001b9c10@@YAXXZ ENDP

; ghidra: FUN_005b9c50  retail @ 0x001B9C50 size 135
public ?d_001b9c50@@YAXXZ
?d_001b9c50@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 47h, 08h, 89h, 46h, 64h, 8Bh, 4Fh
    db 0Ch, 89h, 4Eh, 68h, 8Bh, 57h, 10h, 89h, 56h, 6Ch, 8Bh, 47h, 14h, 89h, 46h, 70h
    db 8Bh, 4Fh, 18h, 89h, 4Eh, 74h, 8Bh, 57h, 1Ch, 89h, 56h, 78h, 8Bh, 47h, 20h, 89h
    db 46h, 7Ch, 8Bh, 4Fh, 24h, 89h, 8Eh, 80h, 00h, 00h, 00h, 8Bh, 57h, 28h, 89h, 96h
    db 84h, 00h, 00h, 00h, 8Bh, 47h, 2Ch, 89h, 86h, 88h, 00h, 00h, 00h, 8Bh, 4Fh, 30h
    db 89h, 8Eh, 8Ch, 00h, 00h, 00h, 8Bh, 57h, 34h, 57h, 8Bh, 0CEh, 89h, 96h, 90h, 00h
    db 00h, 00h, 0E8h, 0EFh, 0B1h, 0E6h, 0FFh, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 44h, 24h, 14h, 8Bh
    db 4Ch, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 50h, 51h, 52h, 57h, 8Bh, 0CEh, 0E8h, 8Fh, 9Bh
    db 0E7h, 0FFh, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_001b9c50@@YAXXZ ENDP

; ghidra: FUN_005b9d00  retail @ 0x001B9D00 size 972
_TEXT ENDS
_TEXT$d005b9d00 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005B9D00 size 972
public ?d_001b9d00@@YAXXZ
?d_001b9d00@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01008BB0
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 020h, 053h, 056h, 057h, 08Bh, 0F9h
    db 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Ah, 088h, 0CFh, 000h, 000h, 000h, 084h, 0C9h, 08Bh, 074h, 024h, 03Ch, 08Bh, 05Ch, 024h, 040h
    db 074h, 011h, 0D9h, 046h, 040h, 0D8h, 05Bh, 008h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 065h
    db 003h, 000h, 000h, 056h, 08Bh, 0CFh
    call ?j_000230ab@@YAXXZ
    db 0D9h, 05Ch, 024h, 00Ch, 0D9h, 044h, 024h, 048h, 0D8h, 05Ch, 024h, 00Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 041h, 075h, 008h, 08Bh, 044h, 024h, 00Ch, 089h, 044h, 024h, 048h, 0D9h, 043h, 004h, 08Bh, 04Fh
    db 03Ch, 0D8h, 066h, 03Ch, 08Bh, 056h, 044h, 0D9h, 003h, 089h, 04Ch, 024h, 01Ch, 0D8h, 066h, 038h
    db 089h, 054h, 024h, 018h, 0D9h, 0F3h, 0D9h, 05Ch, 024h, 014h, 0D9h, 046h, 03Ch, 0D9h, 046h, 038h
    db 0D8h, 023h, 0D9h, 05Ch, 024h, 020h, 0D8h, 063h, 004h, 0D9h, 0C0h, 0DEh, 0C9h, 0D9h, 044h, 024h
    db 020h, 0D8h, 04Ch, 024h, 020h, 0DEh, 0C1h, 0D9h, 0FAh, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h, 08Bh, 0C2h, 089h, 044h, 024h, 014h, 0D9h, 044h, 024h
    db 014h, 051h, 0D8h, 064h, 024h, 01Ch, 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 08Bh, 043h, 008h, 0D9h, 05Ch, 024h, 014h, 08Bh, 00Bh, 08Bh, 053h, 004h, 089h, 044h, 024h, 02Ch
    db 08Bh, 047h, 004h, 083h, 0C4h, 004h, 085h, 0C0h, 089h, 04Ch, 024h, 020h, 089h, 054h, 024h, 024h
    db 0C6h, 044h, 024h, 03Ch, 000h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0D4h, 000h, 000h, 000h, 085h, 0C9h, 074h, 00Eh, 0F6h, 086h, 018h, 001h, 000h, 000h
    db 001h, 074h, 005h, 0C6h, 044h, 024h, 03Ch, 001h, 0F6h, 086h, 094h, 000h, 000h, 000h, 020h, 074h
    db 02Eh, 08Bh, 08Eh, 014h, 002h, 000h, 000h, 085h, 0C9h, 074h, 024h
    call ?j_00021017@@YAXXZ
    db 085h, 0C0h, 074h, 01Bh, 08Bh, 08Eh, 014h, 002h, 000h, 000h
    call ?j_00021017@@YAXXZ
    db 08Bh, 0C8h
    call ?j_00046c09@@YAXXZ
    db 084h, 0C0h, 074h, 005h, 0C6h, 044h, 024h, 03Ch, 001h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 055h, 0D9h, 044h, 024h, 020h, 0BDh, 000h, 000h, 004h, 000h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 044h, 07Ah, 054h, 08Ah, 044h, 024h, 040h, 084h, 0C0h, 074h, 022h, 08Bh, 04Fh, 040h, 0D9h, 044h
    db 024h, 010h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 081h, 0E1h, 0FFh, 0FEh, 0FFh, 0FFh, 081h, 0C9h, 080h, 000h, 000h, 000h, 089h, 04Fh, 040h, 0D9h
    db 05Ch, 024h, 010h, 0EBh, 023h, 08Bh, 086h, 020h, 001h, 000h, 000h, 085h, 0C5h, 074h, 012h, 025h
    db 0FFh, 0FFh, 0FBh, 0FFh, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 081h, 067h, 040h, 07Fh, 0FFh, 0FFh, 0FFh, 0C6h, 087h, 094h, 000h, 000h, 000h, 000h, 08Ah, 044h
    db 024h, 040h, 084h, 0C0h, 075h, 037h, 08Bh, 057h, 040h, 0C1h, 0EAh, 007h, 0F6h, 0C2h, 001h, 00Fh
    db 084h, 0B3h, 000h, 000h, 000h, 08Bh, 086h, 020h, 001h, 000h, 000h, 085h, 0C5h, 074h, 012h, 025h
    db 0FFh, 0FFh, 0FBh, 0FFh, 08Bh, 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 081h, 067h, 040h, 07Fh, 0FFh, 0FFh, 0FFh, 0E9h, 08Bh, 000h, 000h, 000h, 081h, 04Fh, 040h, 080h
    db 000h, 000h, 000h, 08Bh, 086h, 020h, 001h, 000h, 000h, 085h, 0C5h, 075h, 00Fh, 00Bh, 0C5h, 08Bh
    db 0CEh, 089h, 086h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0D9h, 044h, 024h, 018h, 051h, 0D8h, 025h
    dd __real@40490fdb
    db 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 0D8h, 064h, 024h, 020h, 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 08Bh, 046h, 038h, 0D9h, 05Ch, 024h, 018h, 08Bh, 04Eh, 03Ch, 08Bh, 056h, 040h, 089h, 044h, 024h
    db 028h, 0D9h, 044h, 024h, 028h, 0DCh, 0C0h, 089h, 04Ch, 024h, 02Ch, 0D9h, 044h, 024h, 02Ch, 089h
    db 054h, 024h, 030h, 0DCh, 0C0h, 083h, 0C4h, 004h, 0D9h, 044h, 024h, 02Ch, 0DCh, 0C0h, 0D9h, 05Ch
    db 024h, 02Ch, 0D9h, 0C9h, 0D8h, 023h, 0D9h, 05Ch, 024h, 024h, 0D8h, 063h, 004h, 0D9h, 05Ch, 024h
    db 028h, 0D9h, 044h, 024h, 02Ch, 0D8h, 063h, 008h, 0D9h, 05Ch, 024h, 02Ch, 06Ah, 000h, 08Dh, 044h
    db 024h, 028h, 050h, 056h, 08Bh, 0CFh
    call ?j_00012f5d@@YAXXZ
    db 08Bh, 047h, 004h, 085h, 0C0h, 05Dh, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 040h, 060h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 03Ch, 056h, 08Bh, 0CFh
    call ?j_00024f7d@@YAXXZ
    db 0D8h, 05Ch, 024h, 01Ch, 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 00Ch, 0D9h, 044h, 024h, 010h, 0DCh
    db 0C0h, 0D9h, 05Ch, 024h, 010h, 0EBh, 01Dh, 0D9h, 044h, 024h, 00Ch, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D8h, 05Ch, 024h, 01Ch, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 010h, 000h
    db 000h, 000h, 000h, 08Bh, 047h, 004h, 085h, 0C0h, 0B3h, 001h, 074h, 00Ch, 08Bh, 048h, 004h, 085h
    db 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 083h, 078h, 070h, 007h, 074h, 019h, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h
    db 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 083h, 078h, 070h, 004h, 075h, 002h, 032h, 0DBh, 0D9h, 044h, 024h, 010h, 0D9h, 0E1h, 0D8h, 00Dh
    dd g_Va0109DF60
    db 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 084h, 0DBh, 08Bh, 04Ch, 024h, 048h, 089h, 04Ch, 024h, 03Ch, 075h, 010h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0E1h, 0D8h, 04Ch, 024h, 048h, 0D9h, 05Ch, 024h, 03Ch, 0DDh, 0D8h, 0D9h, 044h, 024h, 048h
    db 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 02Bh, 08Bh, 054h, 024h, 03Ch, 08Bh, 044h, 024h, 044h, 08Bh
    db 04Ch, 024h, 040h, 052h, 050h, 051h, 056h, 08Bh, 0CFh
    call ?j_0001c7ec@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 020h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 02Ch, 0C2h, 010h, 000h, 0C7h, 047h, 03Ch, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 02Ch, 05Fh
    db 05Eh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 02Ch, 0C2h, 010h, 000h
?d_001b9d00@@YAXXZ ENDP
_TEXT$d005b9d00 ENDS
_TEXT SEGMENT

; ghidra: FUN_005ba1c0  retail @ 0x001BA1C0 size 1615
public ?d_001ba1c0@@YAXXZ
?d_001ba1c0@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 0D6h, 8Bh, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0D8h, 00h, 00h, 00h, 53h, 55h, 56h, 57h, 8Dh
    db 44h, 24h, 14h, 50h, 8Bh, 0E9h, 0B3h, 01h, 0E8h, 1Dh, 87h, 0E4h, 0FFh, 8Bh, 45h, 04h
    db 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0BBh, 80h, 0E4h, 0FFh
    db 8Bh, 40h, 6Ch, 8Bh, 0B4h, 24h, 0F8h, 00h, 00h, 00h, 0B9h, 08h, 00h, 00h, 00h, 3Bh
    db 0C1h, 0Fh, 87h, 80h, 05h, 00h, 00h, 0FFh, 24h, 85h, 10h, 0A8h, 5Bh, 00h, 8Bh, 8Ch
    db 24h, 0FCh, 00h, 00h, 00h, 8Bh, 51h, 08h, 8Bh, 84h, 24h, 0F8h, 00h, 00h, 00h, 8Bh
    db 4Ch, 24h, 14h, 0C6h, 80h, 86h, 01h, 00h, 00h, 01h, 05h, 78h, 01h, 00h, 00h, 89h
    db 08h, 89h, 54h, 24h, 1Ch, 8Bh, 54h, 24h, 18h, 8Bh, 4Ch, 24h, 1Ch, 89h, 50h, 04h
    db 89h, 48h, 08h, 32h, 0C0h, 0E9h, 9Ah, 05h, 00h, 00h, 84h, 8Eh, 0A4h, 01h, 00h, 00h
    db 0Fh, 85h, 31h, 05h, 00h, 00h, 68h, 90h, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0AEh, 08h
    db 0E8h, 0FFh, 84h, 0C0h, 0Fh, 85h, 1Dh, 05h, 00h, 00h, 8Bh, 0CEh, 32h, 0DBh, 0E8h, 0Eh
    db 01h, 0E8h, 0FFh, 8Bh, 0F8h, 83h, 0FFh, 01h, 75h, 4Dh, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h
    db 8Bh, 11h, 8Dh, 44h, 24h, 10h, 50h, 8Dh, 44h, 24h, 24h, 50h, 8Bh, 44h, 24h, 20h
    db 50h, 8Bh, 44h, 24h, 20h, 50h, 0FFh, 52h, 4Ch, 84h, 0C0h, 74h, 2Ah, 8Bh, 0Dh, 14h
    db 0F2h, 2Eh, 01h, 0D9h, 44h, 24h, 20h, 0D8h, 64h, 24h, 10h, 8Bh, 51h, 14h, 0D9h, 82h
    db 9Ch, 00h, 00h, 00h, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 5Ch, 0B3h, 01h, 0EBh, 58h, 8Bh, 54h, 24h, 18h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh
    db 01h, 8Bh, 01h, 6Ah, 01h, 6Ah, 00h, 57h, 52h, 8Bh, 54h, 24h, 24h, 52h, 0FFh, 50h
    db 1Ch, 0D9h, 5Ch, 24h, 10h, 0A1h, 98h, 08h, 2Fh, 01h, 83h, 78h, 3Ch, 05h, 76h, 2Fh
    db 83h, 0FFh, 10h, 74h, 0Dh, 57h, 0E8h, 0EAh, 0DFh, 0E5h, 0FFh, 83h, 0C4h, 04h, 84h, 0C0h
    db 74h, 1Dh, 0D9h, 44h, 24h, 1Ch, 0D8h, 64h, 24h, 10h, 0D8h, 1Dh, 0E0h, 77h, 09h, 01h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 8Bh, 4Ch, 24h, 1Ch, 89h, 4Ch, 24h, 10h, 8Bh
    db 54h, 24h, 10h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CDh, 89h, 54h, 24h, 20h, 0E8h, 74h
    db 1Eh, 0E5h, 0FFh, 84h, 0DBh, 74h, 7Bh, 0D9h, 44h, 24h, 20h, 8Bh, 0Dh, 14h, 0F2h, 2Eh
    db 01h, 0D8h, 64h, 24h, 10h, 8Bh, 51h, 14h, 0D8h, 9Ah, 9Ch, 00h, 00h, 00h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 27h, 68h, 0E4h, 00h, 00h, 00h, 68h, 0E5h, 00h, 00h, 00h, 6Ah
    db 00h, 8Dh, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 0E8h, 0CBh, 9Ch, 0E4h, 0FFh, 50h, 8Bh, 0CEh
    db 0E8h, 58h, 06h, 0E6h, 0FFh, 32h, 0DBh, 0E9h, 0Bh, 04h, 00h, 00h, 8Bh, 86h, 2Ch, 01h
    db 00h, 00h, 0A8h, 20h, 75h, 04h, 0A8h, 10h, 75h, 48h, 8Bh, 8Eh, 2Ch, 01h, 00h, 00h
    db 83h, 0E1h, 0DFh, 8Bh, 0C1h, 89h, 8Eh, 2Ch, 01h, 00h, 00h, 83h, 0C8h, 10h, 8Bh, 0CEh
    db 89h, 86h, 2Ch, 01h, 00h, 00h, 0E8h, 62h, 75h, 0E6h, 0FFh, 32h, 0DBh, 0E9h, 0D5h, 03h
    db 00h, 00h, 68h, 0E4h, 00h, 00h, 00h, 68h, 0E5h, 00h, 00h, 00h, 6Ah, 00h, 8Dh, 8Ch
    db 24h, 0CCh, 00h, 00h, 00h, 0E8h, 6Eh, 9Ch, 0E4h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 79h, 15h
    db 0E5h, 0FFh, 32h, 0DBh, 0E9h, 0AEh, 03h, 00h, 00h, 8Ah, 86h, 0A4h, 01h, 00h, 00h, 32h
    db 0DBh, 84h, 0C1h, 0Fh, 85h, 9Eh, 03h, 00h, 00h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh
    db 01h, 6Ah, 00h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 54h, 24h, 20h, 52h, 8Bh, 54h, 24h
    db 20h, 52h, 0FFh, 50h, 4Ch, 84h, 0C0h, 74h, 19h, 8Bh, 44h, 24h, 20h, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0CDh, 89h, 44h, 24h, 20h, 0E8h, 8Ah, 1Dh, 0E5h, 0FFh, 0E9h, 65h, 03h
    db 00h, 00h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 39h, 6Ah, 01h, 6Ah, 00h, 8Bh, 0CEh
    db 0E8h, 4Ch, 0FFh, 0E7h, 0FFh, 8Bh, 54h, 24h, 20h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 50h
    db 8Bh, 44h, 24h, 20h, 52h, 50h, 0FFh, 57h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0CDh, 0E8h, 4Eh, 1Dh, 0E5h, 0FFh, 0E9h, 29h, 03h, 00h, 00h, 8Bh, 45h
    db 04h, 85h, 0C0h, 0B3h, 01h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 38h
    db 7Eh, 0E4h, 0FFh, 83h, 78h, 6Ch, 04h, 0Fh, 94h, 0C0h, 84h, 0C0h, 74h, 13h, 8Bh, 54h
    db 24h, 18h, 8Bh, 44h, 24h, 14h, 52h, 50h, 8Bh, 0CDh, 0E8h, 0A1h, 33h, 0E6h, 0FFh, 0EBh
    db 06h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D8h, 45h, 44h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh
    db 0CDh, 0D9h, 5Ch, 24h, 20h, 0E8h, 0FDh, 1Ch, 0E5h, 0FFh, 0E9h, 0D8h, 02h, 00h, 00h, 8Bh
    db 44h, 24h, 18h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 6Ah, 00h, 50h, 8Bh, 44h
    db 24h, 1Ch, 50h, 0B3h, 01h, 0FFh, 52h, 18h, 0D9h, 5Ch, 24h, 1Ch, 68h, 0B8h, 0D8h, 2Eh
    db 01h, 6Ah, 07h, 6Ah, 00h, 8Dh, 4Ch, 24h, 54h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h
    db 00h, 0E8h, 19h, 0E8h, 0E4h, 0FFh, 50h, 8Dh, 4Ch, 24h, 68h, 0E8h, 0FDh, 0DDh, 0E7h, 0FFh
    db 6Ah, 00h, 50h, 6Ah, 01h, 68h, 00h, 00h, 80h, 3Fh, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh
    db 0Dh, 0B8h, 0D5h, 2Eh, 01h, 8Dh, 54h, 24h, 34h, 52h, 0C7h, 84h, 24h, 08h, 01h, 00h
    db 00h, 00h, 00h, 00h, 00h, 0E8h, 36h, 84h, 83h, 00h, 0C6h, 84h, 24h, 0F0h, 00h, 00h
    db 00h, 02h, 0C7h, 44h, 24h, 60h, 5Ch, 3Bh, 08h, 01h, 0EBh, 04h, 0DDh, 0D8h, 8Bh, 0FFh
    db 8Bh, 4Ch, 24h, 20h, 8Bh, 41h, 04h, 8Bh, 51h, 0Ch, 3Bh, 0D0h, 74h, 2Ah, 8Bh, 0C2h
    db 8Bh, 10h, 83h, 0C0h, 08h, 85h, 0D2h, 89h, 41h, 0Ch, 74h, 1Ch, 8Dh, 8Ah, 0ACh, 00h
    db 00h, 00h, 0E8h, 99h, 3Ah, 6Ch, 00h, 0D8h, 54h, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 0CAh, 0D9h, 5Ch, 24h, 10h, 0EBh, 0C8h, 0D9h, 44h, 24h, 10h, 8Dh, 44h, 24h, 14h
    db 0D8h, 45h, 44h, 50h, 8Bh, 0CDh, 0D9h, 5Ch, 24h, 20h, 0E8h, 28h, 1Ch, 0E5h, 0FFh, 8Dh
    db 4Ch, 24h, 20h, 0C7h, 84h, 24h, 0F0h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0CEh
    db 1Eh, 0E7h, 0FFh, 0E9h, 0EFh, 01h, 00h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0B3h, 01h
    db 0D9h, 45h, 44h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 0Eh, 8Bh, 4Dh, 40h, 0C1h
    db 0E9h, 03h, 84h, 0CBh, 0Fh, 84h, 0CDh, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0C0h, 0FDh, 0E7h
    db 0FFh, 83h, 0F8h, 01h, 75h, 12h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 6Ah, 00h, 8Dh, 54h
    db 24h, 18h, 52h, 0E8h, 0A9h, 0BAh, 0E4h, 0FFh, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h
    db 6Ah, 00h, 8Dh, 7Ch, 24h, 40h, 57h, 50h, 8Bh, 44h, 24h, 24h, 50h, 8Bh, 44h, 24h
    db 24h, 50h, 0FFh, 52h, 1Ch, 0D8h, 45h, 44h, 8Bh, 4Dh, 40h, 0C1h, 0E9h, 03h, 0F6h, 0C1h
    db 01h, 74h, 0Ch, 8Bh, 94h, 24h, 0FCh, 00h, 00h, 00h, 0DDh, 0D8h, 0D9h, 42h, 08h, 0D8h
    db 64h, 24h, 1Ch, 0D8h, 4Dh, 4Ch, 0D8h, 44h, 24h, 1Ch, 0D8h, 64h, 24h, 1Ch, 0D8h, 0Dh
    db 70h, 5Ch, 07h, 01h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 0C1h, 0DAh, 0E9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 44h, 0Fh, 8Bh, 4Ch, 01h, 00h, 00h, 0D8h, 44h, 24h, 1Ch, 8Dh, 44h, 24h
    db 14h, 50h, 8Bh, 0CDh, 0D9h, 5Ch, 24h, 20h, 0E8h, 5Ah, 1Bh, 0E5h, 0FFh, 0E9h, 35h, 01h
    db 00h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0B3h, 01h, 0D9h, 45h, 44h, 0DAh, 0E9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 44h, 7Ah, 0Eh, 8Bh, 4Dh, 40h, 0C1h, 0E9h, 03h, 84h, 0CBh, 0Fh, 84h
    db 13h, 01h, 00h, 00h, 8Bh, 45h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 24h, 7Ch, 0E4h, 0FFh, 83h, 78h, 6Ch, 02h, 75h, 17h, 8Bh, 54h, 24h
    db 18h, 8Bh, 44h, 24h, 14h, 52h, 50h, 8Bh, 0CDh, 0E8h, 92h, 31h, 0E6h, 0FFh, 0D9h, 5Ch
    db 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 10h
    db 8Bh, 0BCh, 24h, 0FCh, 00h, 00h, 00h, 51h, 57h, 56h, 8Bh, 0CDh, 0E8h, 5Eh, 0CAh, 0E5h
    db 0FFh, 0D8h, 44h, 24h, 10h, 8Bh, 55h, 40h, 0C1h, 0EAh, 03h, 0F6h, 0C2h, 01h, 74h, 05h
    db 0DDh, 0D8h, 0D9h, 47h, 08h, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 74h, 13h, 0A1h, 0C8h
    db 0D5h, 2Eh, 01h, 0DDh, 0D8h, 8Bh, 88h, 0ACh, 01h, 00h, 00h, 89h, 4Ch, 24h, 10h, 0EBh
    db 19h, 0D8h, 64h, 24h, 1Ch, 0D8h, 4Dh, 4Ch, 0D8h, 44h, 24h, 1Ch, 0D8h, 64h, 24h, 1Ch
    db 0D8h, 0Dh, 70h, 5Ch, 07h, 01h, 0D9h, 5Ch, 24h, 10h, 0D9h, 05h, 50h, 53h, 07h, 01h
    db 0D9h, 44h, 24h, 10h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 18h, 0D9h, 44h, 24h
    db 10h, 8Dh, 54h, 24h, 14h, 0D8h, 44h, 24h, 1Ch, 52h, 8Bh, 0CDh, 0D9h, 5Ch, 24h, 20h
    db 0E8h, 72h, 1Ah, 0E5h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h, 1Dh, 3Ch, 53h, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 1Eh, 8Ah, 8Eh, 1Ch, 01h, 00h, 00h, 0B8h, 40h, 00h, 00h
    db 00h, 84h, 0C8h, 75h, 32h, 09h, 86h, 1Ch, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0ABh, 71h
    db 0E6h, 0FFh, 0EBh, 23h, 0F6h, 86h, 1Ch, 01h, 00h, 00h, 40h, 74h, 1Ah, 8Bh, 86h, 1Ch
    db 01h, 00h, 00h, 83h, 0E0h, 0BFh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 8Ah
    db 71h, 0E6h, 0FFh, 0EBh, 02h, 0DDh, 0D8h, 8Ah, 86h, 86h, 01h, 00h, 00h, 84h, 0C0h, 8Dh
    db 86h, 78h, 01h, 00h, 00h, 75h, 03h, 8Dh, 46h, 38h, 8Bh, 08h, 8Bh, 50h, 04h, 8Dh
    db 44h, 24h, 30h, 89h, 4Ch, 24h, 24h, 50h, 8Bh, 0CEh, 89h, 54h, 24h, 2Ch, 0E8h, 3Ah
    db 12h, 0E8h, 0FFh, 0D9h, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 24h, 0DCh, 0C0h, 8Bh, 54h, 24h
    db 28h, 0C6h, 86h, 86h, 01h, 00h, 00h, 01h, 0D8h, 64h, 24h, 38h, 81h, 0C6h, 78h, 01h
    db 00h, 00h, 89h, 0Eh, 89h, 56h, 04h, 0D9h, 5Ch, 24h, 2Ch, 8Bh, 44h, 24h, 2Ch, 89h
    db 46h, 08h, 8Ah, 0C3h, 8Bh, 8Ch, 24h, 0E8h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0E4h, 00h, 00h, 00h, 0C2h, 08h, 00h
?d_001ba1c0@@YAXXZ ENDP

; ghidra: FUN_005ba9e0  retail @ 0x001BA9E0 size 147
public ?d_001ba9e0@@YAXXZ
?d_001ba9e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 19h, 8Ch, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 3Ch
    db 0DFh, 09h, 01h, 0C7h, 44h, 24h, 10h, 03h, 00h, 00h, 00h, 0E8h, 0BAh, 94h, 0E6h, 0FFh
    db 8Dh, 4Eh, 1Ch, 0C6h, 44h, 24h, 10h, 02h, 0E8h, 23h, 0CFh, 6Ch, 00h, 8Dh, 4Eh, 18h
    db 0C6h, 44h, 24h, 10h, 01h, 0E8h, 16h, 0CFh, 6Ch, 00h, 8Bh, 4Eh, 04h, 85h, 0C9h, 0C6h
    db 44h, 24h, 10h, 00h, 74h, 27h, 8Bh, 46h, 0Ch, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 62h, 74h, 6Ch, 00h, 83h, 0C4h
    db 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 96h, 3Bh, 67h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h
    db 08h, 0C7h, 06h, 44h, 37h, 07h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_001ba9e0@@YAXXZ ENDP

; ghidra: FUN_005bb090  retail @ 0x001BB090 size 42
public ?d_001bb090@@YAXXZ
?d_001bb090@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 10h
    db 50h, 51h, 57h, 8Bh, 0CEh, 0E8h, 0B3h, 7Eh, 0E5h, 0FFh, 83h, 0C6h, 64h, 56h, 8Bh, 0CFh
    db 0E8h, 19h, 0B1h, 0E7h, 0FFh, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_001bb090@@YAXXZ ENDP

; ghidra: FUN_005bb0d0  retail @ 0x001BB0D0 size 890
public ?d_001bb0d0@@YAXXZ
?d_001bb0d0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 28h, 57h, 8Bh, 0F1h, 0E8h, 0C9h, 7Fh
    db 0E6h, 0FFh, 0D9h, 5Ch, 24h, 0Ch, 0D9h, 44h, 24h, 34h, 0D8h, 5Ch, 24h, 0Ch, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 08h, 8Bh, 44h, 24h, 0Ch, 89h, 44h, 24h, 34h, 0D9h, 47h, 44h
    db 8Bh, 6Ch, 24h, 2Ch, 0D9h, 45h, 04h, 51h, 0D8h, 67h, 3Ch, 0D9h, 45h, 00h, 0D8h, 67h
    db 38h, 0D9h, 0F3h, 0D9h, 54h, 24h, 2Ch, 0D8h, 0E1h, 0D9h, 1Ch, 24h, 0DDh, 0D8h, 0E8h, 0F9h
    db 0E7h, 0E4h, 0FFh, 8Bh, 46h, 04h, 0D9h, 5Ch, 24h, 14h, 83h, 0C4h, 04h, 85h, 0C0h, 74h
    db 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 7Eh, 71h, 0E4h, 0FFh, 8Bh, 88h, 0D4h
    db 00h, 00h, 00h, 85h, 0C9h, 53h, 0Fh, 95h, 0C3h, 84h, 0DBh, 0Fh, 84h, 95h, 00h, 00h
    db 00h, 0D9h, 46h, 18h, 0D9h, 46h, 14h, 0D8h, 67h, 38h, 0D9h, 5Ch, 24h, 1Ch, 0D8h, 67h
    db 3Ch, 0D9h, 44h, 24h, 1Ch, 0D9h, 0E1h, 0D9h, 5Ch, 24h, 30h, 0D9h, 0E1h, 0D9h, 44h, 24h
    db 30h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 10h, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h
    db 0D8h, 44h, 24h, 30h, 0D9h, 5Ch, 24h, 30h, 0EBh, 12h, 0D9h, 44h, 24h, 30h, 0D8h, 0Dh
    db 6Ch, 3Bh, 08h, 01h, 0D8h, 0C1h, 0D9h, 5Ch, 24h, 30h, 0DDh, 0D8h, 8Bh, 46h, 04h, 85h
    db 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0Ch, 71h, 0E4h, 0FFh, 0D9h
    db 44h, 24h, 30h, 0D8h, 98h, 34h, 01h, 00h, 00h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 26h
    db 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0E8h
    db 70h, 0E4h, 0FFh, 0D9h, 44h, 24h, 34h, 0D8h, 98h, 38h, 01h, 00h, 00h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 02h, 32h, 0DBh, 84h, 0DBh, 8Bh, 4Eh, 3Ch, 89h, 4Ch, 24h, 30h, 74h
    db 56h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 0B7h, 70h, 0E4h, 0FFh, 0D9h, 44h, 24h, 14h, 0D9h, 0E1h, 0D9h, 80h, 3Ch, 01h, 00h, 00h
    db 0D8h, 0Dh, 14h, 7Bh, 08h, 01h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 28h, 8Bh
    db 8Fh, 20h, 01h, 00h, 00h, 0B8h, 00h, 00h, 04h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h
    db 89h, 8Fh, 20h, 01h, 00h, 00h, 8Bh, 0CFh, 0E8h, 0E0h, 66h, 0E6h, 0FFh, 8Bh, 46h, 40h
    db 0Dh, 80h, 00h, 00h, 00h, 0EBh, 27h, 8Bh, 87h, 20h, 01h, 00h, 00h, 0A9h, 00h, 00h
    db 04h, 00h, 74h, 12h, 25h, 0FFh, 0FFh, 0FBh, 0FFh, 8Bh, 0CFh, 89h, 87h, 20h, 01h, 00h
    db 00h, 0E8h, 0B7h, 66h, 0E6h, 0FFh, 8Bh, 46h, 40h, 25h, 7Fh, 0FFh, 0FFh, 0FFh, 8Bh, 0D0h
    db 0C1h, 0EAh, 07h, 0F6h, 0C2h, 01h, 89h, 46h, 40h, 74h, 1Ah, 0D9h, 44h, 24h, 2Ch, 51h
    db 0D8h, 25h, 14h, 7Bh, 08h, 01h, 0D9h, 1Ch, 24h, 0E8h, 8Eh, 0E6h, 0E4h, 0FFh, 0D9h, 5Ch
    db 24h, 30h, 83h, 0C4h, 04h, 8Bh, 47h, 38h, 8Bh, 4Fh, 3Ch, 8Bh, 57h, 40h, 8Bh, 5Ch
    db 24h, 2Ch, 53h, 89h, 44h, 24h, 20h, 89h, 4Ch, 24h, 24h, 89h, 54h, 24h, 28h, 0E8h
    db 6Ch, 86h, 6Bh, 00h, 0D8h, 0Dh, 68h, 5Ch, 07h, 01h, 53h, 0D8h, 44h, 24h, 24h, 0D9h
    db 5Ch, 24h, 24h, 0E8h, 48h, 86h, 6Bh, 00h, 0D8h, 0Dh, 68h, 5Ch, 07h, 01h, 83h, 0C4h
    db 08h, 6Ah, 00h, 8Dh, 44h, 24h, 20h, 0D8h, 44h, 24h, 24h, 50h, 57h, 8Bh, 0CEh, 0D9h
    db 5Ch, 24h, 2Ch, 0E8h, 75h, 7Ch, 0E5h, 0FFh, 57h, 8Bh, 0CEh, 0E8h, 0BBh, 7Dh, 0E6h, 0FFh
    db 0D9h, 5Ch, 24h, 2Ch, 8Bh, 46h, 04h, 85h, 0C0h, 5Bh, 74h, 0Ch, 8Bh, 48h, 04h, 85h
    db 0C9h, 74h, 05h, 0E8h, 0B3h, 6Fh, 0E4h, 0FFh, 8Bh, 48h, 40h, 0DBh, 40h, 40h, 85h, 0C9h
    db 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0D8h, 7Ch, 24h, 28h, 0D8h, 56h, 2Ch, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 05h, 0DDh, 0D8h, 0D9h, 46h, 2Ch, 0D9h, 44h, 24h, 2Ch, 0D8h
    db 0D9h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 7Ah, 08h, 0D9h, 44h, 24h, 10h, 0DCh, 0C0h
    db 0EBh, 21h, 0D9h, 44h, 24h, 0Ch, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0D8h, 5Ch, 24h, 2Ch
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0EBh, 04h, 0D9h
    db 44h, 24h, 10h, 0D9h, 44h, 24h, 0Ch, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0D9h
    db 0E1h, 0F6h, 0C4h, 41h, 0Fh, 85h, 0AAh, 00h, 00h, 00h, 0D8h, 0Dh, 60h, 0DFh, 09h, 01h
    db 0D9h, 54h, 24h, 28h, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 08h, 0C7h, 44h, 24h, 28h, 00h, 00h, 80h, 3Fh, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch
    db 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0Fh, 6Fh, 0E4h, 0FFh, 8Ah, 88h, 30h, 01h
    db 00h, 00h, 84h, 0C9h, 74h, 2Bh, 8Bh, 56h, 40h, 0C1h, 0EAh, 07h, 0F6h, 0C2h, 01h, 74h
    db 20h, 0F7h, 87h, 1Ch, 01h, 00h, 00h, 00h, 00h, 00h, 60h, 75h, 0Ah, 8Bh, 44h, 24h
    db 34h, 89h, 44h, 24h, 34h, 0EBh, 31h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0EBh
    db 27h, 8Bh, 4Eh, 40h, 0C1h, 0E9h, 07h, 0F6h, 0C1h, 01h, 74h, 0Ah, 8Bh, 54h, 24h, 34h
    db 89h, 54h, 24h, 34h, 0EBh, 12h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 64h, 24h, 28h
    db 0D8h, 4Ch, 24h, 34h, 0D9h, 5Ch, 24h, 34h, 8Bh, 44h, 24h, 34h, 8Bh, 4Ch, 24h, 30h
    db 50h, 51h, 55h, 57h, 8Bh, 0CEh, 0E8h, 0D1h, 13h, 0E6h, 0FFh, 5Fh, 5Eh, 5Dh, 83h, 0C4h
    db 18h, 0C2h, 10h, 00h, 0D8h, 1Dh, 24h, 6Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 10h, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 6Ah, 02h, 83h, 0C1h, 20h, 0E8h, 2Fh, 99h, 0E6h
    db 0FFh, 5Fh, 5Eh, 5Dh, 83h, 0C4h, 18h, 0C2h, 10h, 00h
?d_001bb0d0@@YAXXZ ENDP

; ghidra: FUN_005bbbc0  retail @ 0x001BBBC0 size 58
public ?d_001bbbc0@@YAXXZ
?d_001bbbc0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 6Ah, 00h, 53h, 57h, 8Bh
    db 0F1h, 0E8h, 87h, 73h, 0E5h, 0FFh, 8Dh, 46h, 64h, 50h, 8Bh, 0CFh, 0E8h, 0EDh, 0A5h, 0E7h
    db 0FFh, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 54h, 24h, 18h, 51h, 52h, 53h, 57h, 8Bh, 0CEh, 0E8h
    db 0F8h, 0Bh, 0E6h, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 10h, 00h
?d_001bbbc0@@YAXXZ ENDP

; ghidra: FUN_005bbc50  retail @ 0x001BBC50 size 1791
_TEXT ENDS
_TEXT$d005bbc50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005BBC50 size 1791
public ?d_001bbc50@@YAXXZ
?d_001bbc50@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01008C98
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 0B4h, 000h, 000h, 000h, 055h, 056h
    db 08Bh, 0B4h, 024h, 0CCh, 000h, 000h, 000h, 085h, 0F6h, 08Bh, 0E9h, 074h, 05Bh, 0D9h, 086h, 0C0h
    db 000h, 000h, 000h, 08Bh, 045h, 004h, 085h, 0C0h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 05Ch, 024h, 008h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 040h, 014h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 01Eh, 08Bh, 045h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h
    db 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0D9h, 044h, 024h, 008h, 0D8h, 048h, 014h, 0D9h, 05Ch, 024h, 008h, 08Bh, 08Eh, 004h, 002h, 000h
    db 000h, 085h, 0C9h, 075h, 007h, 032h, 0C0h, 0E9h, 05Ah, 006h, 000h, 000h, 08Bh, 001h, 053h, 0FFh
    db 090h, 050h, 001h, 000h, 000h, 08Bh, 0D8h, 085h, 0DBh, 089h, 05Ch, 024h, 01Ch, 075h, 007h, 032h
    db 0C0h, 0E9h, 03Fh, 006h, 000h, 000h, 08Bh, 04Eh, 008h, 089h, 04Dh, 064h, 08Bh, 056h, 00Ch, 089h
    db 055h, 068h, 08Bh, 046h, 010h, 089h, 045h, 06Ch, 08Bh, 04Eh, 014h, 089h, 04Dh, 070h, 08Bh, 056h
    db 018h, 057h, 08Dh, 07Dh, 064h, 089h, 057h, 010h, 08Bh, 046h, 01Ch, 089h, 047h, 014h, 08Bh, 04Eh
    db 020h, 089h, 04Fh, 018h, 08Bh, 056h, 024h, 089h, 057h, 01Ch, 08Bh, 046h, 028h, 089h, 047h, 020h
    db 08Bh, 04Eh, 02Ch, 089h, 04Fh, 024h, 08Bh, 056h, 030h, 089h, 057h, 028h, 08Bh, 046h, 034h, 089h
    db 047h, 02Ch, 08Bh, 08Bh, 070h, 004h, 000h, 000h, 08Bh, 084h, 024h, 0DCh, 000h, 000h, 000h, 089h
    db 04Ch, 024h, 024h, 0D9h, 044h, 024h, 024h, 08Bh, 08Ch, 024h, 0E0h, 000h, 000h, 000h, 0D8h, 000h
    db 08Dh, 054h, 024h, 044h, 052h, 0D9h, 054h, 024h, 01Ch, 0D9h, 018h, 08Bh, 044h, 024h, 01Ch, 050h
    db 051h, 08Bh, 00Dh
    dd ?TheAerialPathfinder@@3PAVAerialPathfinder@@A
    call ?j_0003e13a@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 04Eh, 005h, 000h, 000h, 08Dh, 054h, 024h, 044h, 052h, 08Bh, 0CDh
    call ?j_0000c1b7@@YAXXZ
    db 08Bh, 083h, 0F0h, 003h, 000h, 000h, 0C1h, 0E8h, 007h, 024h, 001h, 088h, 044h, 024h, 037h, 075h
    db 037h, 08Bh, 08Bh, 07Ch, 004h, 000h, 000h, 08Bh, 093h, 080h, 004h, 000h, 000h, 08Bh, 083h, 084h
    db 004h, 000h, 000h, 089h, 04Ch, 024h, 028h, 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 0CEh, 089h, 054h
    db 024h, 030h, 089h, 044h, 024h, 034h
    call ?j_00008a26@@YAXXZ
    db 0D8h, 01Dh
    dd g_Va0109DF84
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 014h, 08Bh, 086h, 014h, 001h, 000h, 000h, 0A9h, 000h, 000h
    db 000h, 010h, 075h, 026h, 00Dh, 000h, 000h, 000h, 010h, 0EBh, 012h, 08Bh, 086h, 014h, 001h, 000h
    db 000h, 0A9h, 000h, 000h, 000h, 010h, 074h, 012h, 025h, 0FFh, 0FFh, 0FFh, 0EFh, 08Bh, 0CEh, 089h
    db 086h, 014h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 045h, 004h, 085h, 0C0h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h
    db 018h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 074h, 00Ch, 08Bh
    db 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Ah, 048h, 018h, 084h, 0C9h, 074h, 008h, 057h, 08Bh, 0CEh
    call ?j_0001399e@@YAXXZ
    db 08Bh, 084h, 024h, 0DCh, 000h, 000h, 000h, 0D9h, 000h, 08Dh, 054h, 024h, 050h, 0D8h, 064h, 024h
    db 010h, 052h, 051h, 08Bh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 0D9h, 01Ch, 024h, 051h, 08Bh, 00Dh
    dd ?TheAerialPathfinder@@3PAVAerialPathfinder@@A
    call ?j_0003e13a@@YAXXZ
    db 084h, 0C0h, 074h, 040h, 08Dh, 054h, 024h, 044h, 052h, 08Dh, 044h, 024h, 054h, 050h
    call ?j_00032a4c@@YAXXZ
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 08Dh, 04Ch, 024h, 050h, 051h, 08Bh, 0CEh
    call ?j_00049413@@YAXXZ
    db 0D8h, 005h
    dd __real@40490fdb
    db 051h, 0D9h, 01Ch, 024h
    call ?j_0000991c@@YAXXZ
    db 0D9h, 05Ch, 024h, 020h, 083h, 0C4h, 004h, 0C7h, 044h, 024h, 018h, 000h, 000h, 080h, 03Fh, 08Bh
    db 084h, 024h, 0DCh, 000h, 000h, 000h, 0D9h, 044h, 024h, 010h, 0D8h, 000h, 08Dh, 054h, 024h, 05Ch
    db 052h, 051h, 08Bh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 0D9h, 01Ch, 024h, 051h, 08Bh, 00Dh
    dd ?TheAerialPathfinder@@3PAVAerialPathfinder@@A
    call ?j_0003e13a@@YAXXZ
    db 084h, 0C0h, 074h, 03Ch, 08Dh, 054h, 024h, 05Ch, 052h, 08Dh, 044h, 024h, 048h, 050h
    call ?j_00032a4c@@YAXXZ
    db 0D8h, 044h, 024h, 01Ch, 083h, 0C4h, 008h, 08Dh, 04Ch, 024h, 05Ch, 051h, 0D9h, 05Ch, 024h, 018h
    db 08Bh, 0CEh
    call ?j_00049413@@YAXXZ
    db 0D8h, 044h, 024h, 01Ch, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 018h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Ch, 024h, 018h, 0D9h, 044h, 024h, 018h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 01Ch, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 074h, 024h, 018h, 0D9h, 044h, 024h, 01Ch, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 01Ch, 0D8h, 04Ch
    db 024h, 014h, 0D9h, 05Ch, 024h, 014h, 08Bh, 093h, 074h, 004h, 000h, 000h, 056h, 08Bh, 0CDh, 089h
    db 054h, 024h, 01Ch
    call ?j_00024ea6@@YAXXZ
    db 0D9h, 044h, 024h, 01Ch, 0D9h, 0E1h, 0D9h, 0C1h, 0D8h, 00Dh
    dd ?g_bfmeK1266A@@3MB
    db 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 004h, 0B3h, 001h, 0EBh, 002h, 032h, 0DBh, 0D9h
    db 0C0h, 0D9h, 0E0h, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h, 024h, 01Ch, 0D8h, 05Ch, 024h, 010h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 0D9h, 044h, 024h, 01Ch, 0EBh, 004h, 0D9h, 044h, 024h, 010h
    db 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 01Bh, 0DDh, 0D8h, 0D9h, 044h, 024h, 01Ch, 0D8h
    db 05Ch, 024h, 010h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 0D9h, 044h, 024h, 01Ch, 0EBh, 004h
    db 0D9h, 044h, 024h, 010h, 0D9h, 005h
    dd __real@3e4ccccd
    db 08Bh, 044h, 024h, 020h, 0D8h, 0C9h, 051h, 0D9h, 044h, 024h, 01Ch, 0D8h, 00Dh
    dd __real@3f4ccccd
    db 0DEh, 0C1h, 0D9h, 098h, 074h, 004h, 000h, 000h, 0D9h, 046h, 044h, 0D8h, 0C1h, 0D9h, 01Ch, 024h
    db 0DDh, 0D8h
    call ?j_0000991c@@YAXXZ
    db 0D9h, 05Ch, 024h, 014h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 010h, 051h, 08Bh, 0CDh
    call ?j_0003acc4@@YAXXZ
    db 08Bh, 094h, 024h, 0E0h, 000h, 000h, 000h, 083h, 0C2h, 054h, 052h, 08Dh, 044h, 024h, 02Ch, 050h
    db 08Bh, 0CEh
    call ?j_0003faee@@YAXXZ
    db 0D9h, 044h, 024h, 028h, 0D8h, 04Ch, 024h, 028h, 08Bh, 04Ch, 024h, 020h, 0D9h, 044h, 024h, 030h
    db 0D8h, 04Ch, 024h, 030h, 0DEh, 0C1h, 0D9h, 044h, 024h, 02Ch, 0D8h, 04Ch, 024h, 02Ch, 0DEh, 0C1h
    db 0D9h, 0FAh, 0D9h, 081h, 070h, 004h, 000h, 000h, 0D9h, 005h
    dd ?g_bfmeK1266B@@3MB
    db 0D8h, 0C9h, 0D9h, 0C9h, 0D9h, 0CAh, 0DEh, 0D9h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 07Ah
    db 01Dh, 0D9h, 044h, 024h, 014h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ch, 0D9h, 044h, 024h, 014h, 0D8h, 00Dh
    dd ?BfmeShadowScale@@3MB
    db 0EBh, 00Eh, 084h, 0DBh, 074h, 00Eh, 0D9h, 044h, 024h, 014h, 0D8h, 005h
    dd ?g_0109B46C@@3MB
    db 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 024h, 0D8h, 094h, 024h, 0D8h, 000h, 000h, 000h, 0DFh
    db 0E0h, 0F6h, 0C4h, 005h, 07Ah, 010h, 056h, 0DDh, 0D8h, 08Bh, 0CDh
    call ?j_00024f7d@@YAXXZ
    db 0D8h, 044h, 024h, 024h, 0EBh, 01Ch, 0D8h, 094h, 024h, 0D8h, 000h, 000h, 000h, 0DFh, 0E0h, 0F6h
    db 0C4h, 041h, 075h, 00Eh, 056h, 0DDh, 0D8h, 08Bh, 0CDh
    call ?j_000235e2@@YAXXZ
    db 0D8h, 06Ch, 024h, 024h, 0D9h, 044h, 024h, 014h, 056h, 0D8h, 00Dh
    dd __real@3ecccccd
    db 08Bh, 0CDh, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 028h, 0DDh, 0D8h
    call ?j_000230ab@@YAXXZ
    db 0D8h, 05Ch, 024h, 024h, 08Bh, 0CDh, 056h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 007h
    call ?j_000230ab@@YAXXZ
    db 0EBh, 01Eh
    call ?j_0001a334@@YAXXZ
    db 0D8h, 05Ch, 024h, 024h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ah, 056h, 08Bh, 0CDh
    call ?j_0001a334@@YAXXZ
    db 0EBh, 004h, 0D9h, 044h, 024h, 024h, 08Bh, 05Ch, 024h, 020h, 0D9h, 09Bh, 070h, 004h, 000h, 000h
    db 08Bh, 057h, 00Ch, 0D9h, 047h, 02Ch, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 001h, 0D9h, 054h, 024h, 018h, 0D9h, 047h, 01Ch, 089h, 054h, 024h, 028h, 0D9h, 054h, 024h
    db 010h, 06Ah, 000h, 08Bh, 054h, 024h, 014h, 0D9h, 05Ch, 024h, 030h, 052h, 08Bh, 054h, 024h, 030h
    db 0D9h, 05Ch, 024h, 038h, 052h, 0FFh, 050h, 018h, 0D9h, 05Ch, 024h, 020h, 08Dh, 086h, 0ACh, 000h
    db 000h, 000h, 050h, 08Dh, 04Ch, 024h, 06Ch
    call ?j_0002b355@@YAXXZ
    db 0D9h, 044h, 024h, 07Ch, 0D8h, 00Dh
    dd __real@3e800000
    db 0C7h, 084h, 024h, 0CCh, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0D8h, 044h, 024h, 020h, 0D9h
    db 05Ch, 024h, 020h, 0D9h, 044h, 024h, 018h, 0D8h, 05Ch, 024h, 020h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 08Dh, 044h, 024h, 030h, 074h, 004h, 08Dh, 044h, 024h, 020h, 0D9h, 000h, 08Bh, 04Ch, 024h, 028h
    db 08Bh, 054h, 024h, 010h, 0D9h, 05Fh, 02Ch, 0D9h, 044h, 024h, 014h, 089h, 04Fh, 00Ch, 0D8h, 01Dh
    dd ?g_Rva01095F98@@3MA
    db 089h, 057h, 01Ch, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 02Ch, 08Bh, 086h, 018h, 001h, 000h, 000h
    db 084h, 0C0h, 078h, 00Dh, 0F6h, 086h, 01Ch, 001h, 000h, 000h, 040h, 00Fh, 085h, 08Eh, 000h, 000h
    db 000h, 081h, 0A6h, 018h, 001h, 000h, 000h, 07Fh, 0FFh, 0FFh, 0FFh, 08Bh, 086h, 01Ch, 001h, 000h
    db 000h, 083h, 0C8h, 040h, 0EBh, 06Ch, 0D9h, 044h, 024h, 014h, 0D8h, 01Dh
    dd g_Va0109DF80
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 027h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 0A8h, 040h, 075h
    db 00Ah, 08Ah, 086h, 018h, 001h, 000h, 000h, 084h, 0C0h, 078h, 054h, 083h, 0A6h, 01Ch, 001h, 000h
    db 000h, 0BFh, 081h, 08Eh, 018h, 001h, 000h, 000h, 080h, 000h, 000h, 000h, 0EBh, 03Ah, 08Ah, 086h
    db 018h, 001h, 000h, 000h, 084h, 0C0h, 079h, 018h, 08Bh, 086h, 018h, 001h, 000h, 000h, 025h, 07Fh
    db 0FFh, 0FFh, 0FFh, 08Bh, 0CEh, 089h, 086h, 018h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 01Ch, 001h, 000h, 000h, 040h, 074h, 016h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 083h
    db 0E0h, 0BFh, 089h, 086h, 01Ch, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002191d@@YAXXZ
    db 057h, 08Bh, 0CEh
    call ?j_000361ce@@YAXXZ
    db 08Bh, 046h, 038h, 08Bh, 04Eh, 03Ch, 08Bh, 056h, 040h, 089h, 04Ch, 024h, 03Ch, 08Bh, 08Ch, 024h
    db 0DCh, 000h, 000h, 000h, 089h, 044h, 024h, 038h, 089h, 054h, 024h, 040h, 0D9h, 083h, 070h, 004h
    db 000h, 000h, 0D8h, 001h, 08Bh, 094h, 024h, 0E0h, 000h, 000h, 000h, 08Dh, 044h, 024h, 038h, 050h
    db 051h, 08Bh, 00Dh
    dd ?TheAerialPathfinder@@3PAVAerialPathfinder@@A
    db 0D9h, 01Ch, 024h, 052h
    call ?j_0003e13a@@YAXXZ
    db 084h, 0C0h, 074h, 00Ch, 08Dh, 044h, 024h, 038h, 050h, 08Bh, 0CEh
    call ?j_0002ed16@@YAXXZ
    db 08Dh, 04Ch, 024h, 068h, 0C7h, 084h, 024h, 0CCh, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000309f4@@YAXXZ
    db 032h, 0C0h, 0EBh, 062h, 08Bh, 086h, 014h, 001h, 000h, 000h, 0A9h, 000h, 000h, 000h, 010h, 074h
    db 012h, 025h, 0FFh, 0FFh, 0FFh, 0EFh, 08Bh, 0CEh, 089h, 086h, 014h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0F6h, 086h, 01Ch, 001h, 000h, 000h, 040h, 074h, 016h, 08Bh, 086h, 01Ch, 001h, 000h, 000h, 083h
    db 0E0h, 0BFh, 08Bh, 0CEh, 089h, 086h, 01Ch, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Ah, 086h, 018h, 001h, 000h, 000h, 084h, 0C0h, 079h, 018h, 08Bh, 086h, 018h, 001h, 000h, 000h
    db 025h, 07Fh, 0FFh, 0FFh, 0FFh, 08Bh, 0CEh, 089h, 086h, 018h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0B0h, 001h, 05Fh, 05Bh, 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 05Eh, 05Dh, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 081h, 0C4h, 0C0h, 000h, 000h, 000h, 0C2h, 010h, 000h
?d_001bbc50@@YAXXZ ENDP
_TEXT$d005bbc50 ENDS
_TEXT SEGMENT

; ghidra: FUN_005bc510  retail @ 0x001BC510 size 58
public ?d_001bc510@@YAXXZ
?d_001bc510@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 6Ah, 00h, 53h, 57h, 8Bh
    db 0F1h, 0E8h, 37h, 6Ah, 0E5h, 0FFh, 8Dh, 46h, 64h, 50h, 8Bh, 0CFh, 0E8h, 9Dh, 9Ch, 0E7h
    db 0FFh, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 54h, 24h, 18h, 51h, 52h, 53h, 57h, 8Bh, 0CEh, 0E8h
    db 0A8h, 02h, 0E6h, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 10h, 00h
?d_001bc510@@YAXXZ ENDP

; ghidra: FUN_005bc560  retail @ 0x001BC560 size 210
public ?d_001bc560@@YAXXZ
?d_001bc560@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 5Ch, 24h, 18h, 56h, 8Bh, 74h, 24h, 18h, 57h, 6Ah, 00h
    db 53h, 56h, 8Bh, 0F9h, 0E8h, 0E4h, 69h, 0E5h, 0FFh, 8Dh, 47h, 64h, 50h, 8Bh, 0CEh, 0E8h
    db 4Ah, 9Ch, 0E7h, 0FFh, 8Bh, 4Ch, 24h, 28h, 8Bh, 54h, 24h, 24h, 51h, 52h, 53h, 56h
    db 8Bh, 0CFh, 0E8h, 55h, 02h, 0E6h, 0FFh, 8Bh, 46h, 38h, 8Bh, 4Eh, 3Ch, 6Ah, 00h, 89h
    db 44h, 24h, 10h, 89h, 4Ch, 24h, 14h, 8Bh, 44h, 24h, 14h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh
    db 01h, 8Bh, 11h, 6Ah, 00h, 50h, 8Bh, 44h, 24h, 18h, 50h, 0FFh, 52h, 4Ch, 84h, 0C0h
    db 8Bh, 47h, 40h, 74h, 35h, 8Bh, 0C8h, 0C1h, 0E9h, 05h, 0F6h, 0C1h, 01h, 75h, 5Ah, 83h
    db 0C8h, 20h, 89h, 47h, 40h, 8Ah, 8Eh, 1Ch, 01h, 00h, 00h, 0B8h, 10h, 00h, 00h, 00h
    db 84h, 0C8h, 75h, 45h, 09h, 86h, 1Ch, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 2Ch, 53h, 0E6h
    db 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 10h, 00h, 8Bh, 0D0h, 0C1h, 0EAh, 05h, 0F6h
    db 0C2h, 01h, 74h, 25h, 83h, 0E0h, 0DFh, 89h, 47h, 40h, 0F6h, 86h, 1Ch, 01h, 00h, 00h
    db 10h, 74h, 16h, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 83h, 0E0h, 0EFh, 8Bh, 0CEh, 89h, 86h
    db 1Ch, 01h, 00h, 00h, 0E8h, 0F4h, 52h, 0E6h, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 10h, 00h
?d_001bc560@@YAXXZ ENDP

; ghidra: FUN_005bc670  retail @ 0x001BC670 size 338
public ?d_001bc670@@YAXXZ
?d_001bc670@@YAXXZ PROC
    db 83h, 0ECh, 10h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 0F1h, 8Bh, 0CFh, 0E8h, 0AEh, 55h
    db 0E4h, 0FFh, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 27h
    db 01h, 00h, 00h, 83h, 4Eh, 40h, 10h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 11h, 5Ch, 0E4h, 0FFh, 8Bh, 40h, 60h, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 89h, 44h, 24h, 1Ch, 0D9h, 44h, 24h, 1Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 44h, 7Ah, 0Eh, 6Ah, 00h, 57h, 8Bh, 0CEh, 0E8h, 42h, 0B1h, 0E4h, 0FFh, 0D9h, 5Ch
    db 24h, 1Ch, 0D9h, 46h, 08h, 0D8h, 67h, 38h, 0D9h, 46h, 0Ch, 0D8h, 67h, 3Ch, 0D9h, 0C1h
    db 0D9h, 0E1h, 0D8h, 1Dh, 0ECh, 66h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Ah, 0D9h
    db 0C0h, 0D9h, 0E1h, 0D8h, 1Dh, 0ECh, 66h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 09h
    db 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 47h, 44h, 0EBh, 04h, 0D9h, 0C9h, 0D9h, 0F3h, 0D9h, 05h, 8Ch
    db 0DFh, 09h, 01h, 0D9h, 44h, 24h, 1Ch, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 05h, 7Ah, 12h, 0DDh, 0D8h, 0D9h, 44h, 24h, 1Ch, 0D9h, 0E0h, 0D9h, 5Ch, 24h, 1Ch
    db 0D9h, 05h, 88h, 0DFh, 09h, 01h, 8Bh, 4Eh, 08h, 0D8h, 0C1h, 8Bh, 56h, 0Ch, 8Bh, 46h
    db 10h, 0D9h, 5Ch, 24h, 08h, 53h, 8Bh, 5Ch, 24h, 0Ch, 53h, 0DDh, 0D8h, 89h, 4Ch, 24h
    db 14h, 89h, 54h, 24h, 18h, 89h, 44h, 24h, 1Ch, 0E8h, 0C2h, 71h, 6Bh, 00h, 0D8h, 4Ch
    db 24h, 24h, 53h, 0D8h, 44h, 24h, 18h, 0D9h, 5Ch, 24h, 18h, 0E8h, 0A0h, 71h, 6Bh, 00h
    db 0D8h, 4Ch, 24h, 28h, 83h, 0C4h, 08h, 57h, 8Bh, 0CEh, 0D8h, 44h, 24h, 18h, 0D9h, 5Ch
    db 24h, 18h, 0E8h, 0ADh, 0DBh, 0E5h, 0FFh, 6Ah, 00h, 0D9h, 5Ch, 24h, 24h, 8Dh, 4Ch, 24h
    db 14h, 51h, 57h, 8Bh, 0CEh, 0E8h, 0C3h, 67h, 0E5h, 0FFh, 8Dh, 56h, 64h, 52h, 8Bh, 0CFh
    db 0E8h, 29h, 9Ah, 0E7h, 0FFh, 8Bh, 44h, 24h, 20h, 50h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h
    db 51h, 57h, 8Bh, 0CEh, 0E8h, 33h, 00h, 0E6h, 0FFh, 5Bh, 5Fh, 5Eh, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_001bc670@@YAXXZ ENDP

; ghidra: FUN_005bc820  retail @ 0x001BC820 size 557
public ?d_001bc820@@YAXXZ
?d_001bc820@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 40h, 8Dh, 5Fh, 64h, 83h
    db 0E1h, 0FBh, 89h, 4Fh, 40h, 8Bh, 46h, 08h, 89h, 03h, 8Bh, 4Eh, 0Ch, 89h, 4Bh, 04h
    db 8Bh, 56h, 10h, 89h, 53h, 08h, 8Bh, 46h, 14h, 89h, 43h, 0Ch, 8Bh, 4Eh, 18h, 89h
    db 4Bh, 10h, 8Bh, 56h, 1Ch, 89h, 53h, 14h, 8Bh, 46h, 20h, 89h, 43h, 18h, 8Bh, 4Eh
    db 24h, 89h, 4Bh, 1Ch, 8Bh, 56h, 28h, 89h, 53h, 20h, 8Bh, 46h, 2Ch, 89h, 43h, 24h
    db 8Bh, 4Eh, 30h, 89h, 4Bh, 28h, 8Bh, 56h, 34h, 89h, 53h, 2Ch, 0A1h, 98h, 08h, 2Fh
    db 01h, 8Bh, 48h, 3Ch, 3Bh, 4Fh, 5Ch, 77h, 15h, 0D9h, 44h, 24h, 1Ch, 0D8h, 5Fh, 58h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 57h, 58h, 89h, 54h, 24h, 1Ch, 56h, 8Bh
    db 0CFh, 0E8h, 05h, 68h, 0E6h, 0FFh, 0D9h, 44h, 24h, 1Ch, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 06h, 0D9h, 5Ch, 24h, 1Ch, 0EBh, 02h, 0DDh, 0D8h, 8Bh, 86h, 08h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 0Bh, 8Ah, 48h, 5Ch, 84h, 0C9h, 0Fh, 85h, 77h, 01h, 00h, 00h
    db 0F6h, 86h, 94h, 00h, 00h, 00h, 10h, 0Fh, 85h, 6Ah, 01h, 00h, 00h, 0C6h, 87h, 95h
    db 00h, 00h, 00h, 00h, 8Bh, 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 74h, 08h, 8Bh, 80h
    db 40h, 01h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 85h, 0C0h, 74h, 0Dh, 8Bh, 0C8h, 0E8h, 38h
    db 0BBh, 0E4h, 0FFh, 88h, 87h, 95h, 00h, 00h, 00h, 55h, 68h, 85h, 00h, 00h, 00h, 8Bh
    db 0CEh, 0E8h, 09h, 5Ch, 0E7h, 0FFh, 84h, 0C0h, 8Bh, 6Ch, 24h, 18h, 75h, 36h, 8Bh, 8Eh
    db 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 2Ch, 55h, 0E8h, 71h, 4Bh, 0E6h, 0FFh, 84h, 0C0h
    db 75h, 22h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 0E8h, 0F1h, 4Ah, 0E4h, 0FFh, 84h, 0C0h, 75h
    db 13h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 0E8h, 49h, 6Eh, 0E6h, 0FFh, 84h, 0C0h, 0Fh, 85h
    db 0F2h, 00h, 00h, 00h, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 54h, 59h, 0E4h, 0FFh, 8Bh, 40h, 70h, 83h, 0F8h, 08h, 0Fh, 87h, 85h
    db 00h, 00h, 00h, 0FFh, 24h, 85h, 50h, 0CAh, 5Bh, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 4Ch
    db 24h, 1Ch, 50h, 51h, 55h, 56h, 8Bh, 0CFh, 0E8h, 0AFh, 02h, 0E7h, 0FFh, 0EBh, 7Ch, 8Bh
    db 54h, 24h, 20h, 8Bh, 44h, 24h, 1Ch, 52h, 50h, 55h, 56h, 8Bh, 0CFh, 0E8h, 64h, 0D5h
    db 0E5h, 0FFh, 0EBh, 67h, 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 1Ch, 51h, 52h, 55h, 56h
    db 8Bh, 0CFh, 0E8h, 5Dh, 3Fh, 0E6h, 0FFh, 0EBh, 52h, 8Bh, 44h, 24h, 20h, 8Bh, 4Ch, 24h
    db 1Ch, 50h, 51h, 55h, 56h, 8Bh, 0CFh, 0E8h, 5Dh, 60h, 0E7h, 0FFh, 0EBh, 3Dh, 8Bh, 54h
    db 24h, 20h, 8Bh, 44h, 24h, 1Ch, 52h, 50h, 55h, 56h, 8Bh, 0CFh, 0E8h, 21h, 92h, 0E6h
    db 0FFh, 0EBh, 28h, 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 1Ch, 51h, 52h, 55h, 56h, 8Bh
    db 0CFh, 0E8h, 33h, 60h, 0E7h, 0FFh, 0EBh, 13h, 8Bh, 44h, 24h, 20h, 8Bh, 4Ch, 24h, 1Ch
    db 50h, 51h, 55h, 56h, 8Bh, 0CFh, 0E8h, 16h, 1Eh, 0E6h, 0FFh, 8Bh, 86h, 04h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 08h, 8Bh, 80h, 40h, 01h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 85h
    db 0C0h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 0A5h, 0A3h, 0E4h, 0FFh, 84h, 0C0h, 75h, 09h, 55h, 56h
    db 8Bh, 0CFh, 0E8h, 84h, 34h, 0E5h, 0FFh, 53h, 8Bh, 0CEh, 0E8h, 8Fh, 97h, 0E7h, 0FFh, 0C6h
    db 87h, 95h, 00h, 00h, 00h, 00h, 5Dh, 5Fh, 5Eh, 5Bh, 0C2h, 14h, 00h
?d_001bc820@@YAXXZ ENDP

; ghidra: FUN_005bcb10  retail @ 0x001BCB10 size 577
public ?d_001bcb10@@YAXXZ
?d_001bcb10@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 33h, 0DBh, 3Bh, 0F3h, 57h, 8Bh, 0F9h, 75h, 08h, 5Fh
    db 5Eh, 32h, 0C0h, 5Bh, 0C2h, 04h, 00h, 8Bh, 46h, 08h, 89h, 47h, 64h, 8Bh, 4Eh, 0Ch
    db 89h, 4Fh, 68h, 8Bh, 56h, 10h, 89h, 57h, 6Ch, 8Bh, 46h, 14h, 89h, 47h, 70h, 8Bh
    db 4Eh, 18h, 55h, 8Dh, 6Fh, 64h, 89h, 4Dh, 10h, 8Bh, 56h, 1Ch, 89h, 55h, 14h, 8Bh
    db 46h, 20h, 89h, 45h, 18h, 8Bh, 4Eh, 24h, 89h, 4Dh, 1Ch, 8Bh, 56h, 28h, 89h, 55h
    db 20h, 8Bh, 46h, 2Ch, 89h, 45h, 24h, 8Bh, 4Eh, 30h, 89h, 4Dh, 28h, 8Bh, 56h, 34h
    db 89h, 55h, 2Ch, 8Bh, 47h, 40h, 8Bh, 0C8h, 0C1h, 0E9h, 02h, 0F6h, 0C1h, 01h, 75h, 1Eh
    db 8Dh, 56h, 38h, 8Bh, 1Ah, 8Dh, 4Fh, 08h, 89h, 19h, 8Bh, 5Ah, 04h, 89h, 59h, 04h
    db 8Bh, 52h, 08h, 83h, 0C8h, 04h, 89h, 51h, 08h, 89h, 47h, 40h, 33h, 0DBh, 0F7h, 86h
    db 14h, 01h, 00h, 00h, 00h, 00h, 00h, 10h, 0Fh, 85h, 0D6h, 00h, 00h, 00h, 8Bh, 86h
    db 1Ch, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 20h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0DFh
    db 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 50h, 4Dh, 0E6h, 0FFh, 8Bh, 86h, 1Ch
    db 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 40h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0BFh, 8Bh
    db 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 31h, 4Dh, 0E6h, 0FFh, 0F6h, 86h, 20h, 01h
    db 00h, 00h, 02h, 74h, 16h, 8Bh, 86h, 20h, 01h, 00h, 00h, 83h, 0E0h, 0FDh, 8Bh, 0CEh
    db 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 12h, 4Dh, 0E6h, 0FFh, 0F6h, 86h, 20h, 01h, 00h
    db 00h, 04h, 74h, 16h, 8Bh, 86h, 20h, 01h, 00h, 00h, 83h, 0E0h, 0FBh, 8Bh, 0CEh, 89h
    db 86h, 20h, 01h, 00h, 00h, 0E8h, 0F3h, 4Ch, 0E6h, 0FFh, 8Bh, 86h, 1Ch, 01h, 00h, 00h
    db 85h, 0C0h, 79h, 12h, 25h, 0FFh, 0FFh, 0FFh, 7Fh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h
    db 00h, 0E8h, 0D7h, 4Ch, 0E6h, 0FFh, 0F6h, 86h, 20h, 01h, 00h, 00h, 01h, 74h, 16h, 8Bh
    db 86h, 20h, 01h, 00h, 00h, 83h, 0E0h, 0FEh, 8Bh, 0CEh, 89h, 86h, 20h, 01h, 00h, 00h
    db 0E8h, 0B8h, 4Ch, 0E6h, 0FFh, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 08h
    db 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0F7h, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h
    db 99h, 4Ch, 0E6h, 0FFh, 8Bh, 4Fh, 40h, 83h, 0E1h, 0FEh, 88h, 9Fh, 94h, 00h, 00h, 00h
    db 89h, 4Fh, 40h, 39h, 9Eh, 08h, 02h, 00h, 00h, 75h, 09h, 5Dh, 5Fh, 5Eh, 0B0h, 01h
    db 5Bh, 0C2h, 04h, 00h, 8Bh, 47h, 04h, 3Bh, 0C3h, 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh
    db 48h, 04h, 3Bh, 0CBh, 74h, 05h, 0E8h, 00h, 56h, 0E4h, 0FFh, 8Bh, 40h, 70h, 83h, 0F8h
    db 08h, 77h, 47h, 0FFh, 24h, 85h, 54h, 0CDh, 5Bh, 00h, 56h, 8Bh, 0CFh, 89h, 5Fh, 3Ch
    db 0E8h, 3Ch, 55h, 0E4h, 0FFh, 0EBh, 57h, 56h, 8Bh, 0CFh, 89h, 5Fh, 3Ch, 0E8h, 0CEh, 0B8h
    db 0E6h, 0FFh, 0EBh, 4Ah, 56h, 8Bh, 0CFh, 89h, 5Fh, 3Ch, 0E8h, 7Fh, 32h, 0E6h, 0FFh, 0EBh
    db 3Dh, 56h, 8Bh, 0CFh, 0E8h, 98h, 0FBh, 0E5h, 0FFh, 0EBh, 33h, 89h, 5Fh, 3Ch, 0EBh, 2Ch
    db 56h, 8Bh, 0CFh, 0E8h, 0CAh, 0D5h, 0E8h, 0FFh, 0EBh, 22h, 89h, 5Fh, 3Ch, 8Bh, 86h, 14h
    db 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 10h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0EFh, 8Bh
    db 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 0F1h, 4Bh, 0E6h, 0FFh, 0B3h, 01h, 8Dh, 47h
    db 08h, 50h, 56h, 8Bh, 0CFh, 0E8h, 81h, 31h, 0E5h, 0FFh, 84h, 0C0h, 74h, 02h, 0B3h, 01h
    db 55h, 8Bh, 0CEh, 0E8h, 86h, 94h, 0E7h, 0FFh, 5Dh, 5Fh, 5Eh, 8Ah, 0C3h, 5Bh, 0C2h, 04h
    db 00h
?d_001bcb10@@YAXXZ ENDP

; ghidra: FUN_005bce20  retail @ 0x001BCE20 size 542
public ?d_001bce20@@YAXXZ
?d_001bce20@@YAXXZ PROC
    db 83h, 0ECh, 10h, 55h, 8Bh, 0E9h, 8Bh, 4Dh, 40h, 56h, 8Bh, 74h, 24h, 1Ch, 83h, 0E1h
    db 0FBh, 85h, 0F6h, 89h, 4Dh, 40h, 0Fh, 84h, 0FAh, 01h, 00h, 00h, 8Bh, 45h, 04h, 85h
    db 0C0h, 0Fh, 84h, 0EFh, 01h, 00h, 00h, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 68h
    db 54h, 0E4h, 0FFh, 85h, 0C0h, 0Fh, 84h, 0DBh, 01h, 00h, 00h, 8Bh, 86h, 08h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 0Bh, 8Ah, 48h, 5Ch, 84h, 0C9h, 0Fh, 85h, 0C6h, 01h, 00h, 00h
    db 8Bh, 46h, 08h, 89h, 45h, 64h, 8Bh, 4Eh, 0Ch, 89h, 4Dh, 68h, 8Bh, 56h, 10h, 89h
    db 55h, 6Ch, 8Bh, 46h, 14h, 89h, 45h, 70h, 8Bh, 4Eh, 18h, 57h, 8Dh, 7Dh, 64h, 89h
    db 4Fh, 10h, 8Bh, 56h, 1Ch, 89h, 57h, 14h, 8Bh, 46h, 20h, 89h, 47h, 18h, 8Bh, 4Eh
    db 24h, 89h, 4Fh, 1Ch, 8Bh, 56h, 28h, 89h, 57h, 20h, 8Bh, 46h, 2Ch, 89h, 47h, 24h
    db 8Bh, 4Eh, 30h, 89h, 4Fh, 28h, 8Bh, 56h, 34h, 89h, 57h, 2Ch, 0D9h, 46h, 44h, 0D9h
    db 44h, 24h, 24h, 51h, 0D8h, 0E1h, 0D9h, 1Ch, 24h, 0DDh, 0D8h, 0E8h, 4Ch, 0CAh, 0E4h, 0FFh
    db 8Bh, 45h, 04h, 0D9h, 5Ch, 24h, 24h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0D1h, 53h, 0E4h, 0FFh, 8Bh, 4Ch, 24h, 20h, 8Bh, 80h
    db 80h, 00h, 00h, 00h, 53h, 51h, 89h, 44h, 24h, 14h, 0E8h, 21h, 6Ah, 6Bh, 00h, 0D9h
    db 5Ch, 24h, 28h, 8Bh, 54h, 24h, 14h, 52h, 0E8h, 13h, 6Ah, 6Bh, 00h, 0D8h, 5Ch, 24h
    db 2Ch, 83h, 0C4h, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 37h, 8Bh, 8Eh, 0FCh, 01h, 00h
    db 00h, 85h, 0C9h, 74h, 2Dh, 8Bh, 01h, 0FFh, 50h, 68h, 8Bh, 0D8h, 85h, 0DBh, 74h, 22h
    db 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h, 3Ch, 8Bh, 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 81h
    db 0DDh, 0E7h, 0FFh, 57h, 8Bh, 0CEh, 0E8h, 53h, 6Ah, 0E5h, 0FFh, 8Bh, 13h, 8Bh, 0CBh, 0FFh
    db 52h, 40h, 56h, 8Bh, 0CDh, 0E8h, 0DAh, 0D3h, 0E5h, 0FFh, 0D9h, 54h, 24h, 24h, 0D8h, 1Dh
    db 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 6Ah, 8Bh, 46h, 38h, 8Bh, 4Eh
    db 3Ch, 8Bh, 56h, 40h, 8Bh, 7Ch, 24h, 28h, 57h, 89h, 44h, 24h, 18h, 89h, 4Ch, 24h
    db 1Ch, 89h, 54h, 24h, 20h, 0E8h, 96h, 69h, 6Bh, 00h, 0D8h, 4Ch, 24h, 28h, 57h, 0DCh
    db 0C0h, 0D8h, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0E8h, 72h, 69h, 6Bh, 00h, 0D8h, 4Ch
    db 24h, 2Ch, 8Bh, 4Ch, 24h, 2Ch, 83h, 0C4h, 08h, 8Dh, 44h, 24h, 28h, 50h, 0DCh, 0C0h
    db 51h, 68h, 80h, 4Fh, 0C3h, 47h, 0D8h, 44h, 24h, 24h, 8Dh, 54h, 24h, 20h, 52h, 56h
    db 8Bh, 0CDh, 0D9h, 5Ch, 24h, 2Ch, 0E8h, 57h, 69h, 0E4h, 0FFh, 5Bh, 5Fh, 5Eh, 5Dh, 83h
    db 0C4h, 10h, 0C2h, 08h, 00h, 8Bh, 46h, 38h, 8Bh, 4Eh, 3Ch, 8Bh, 56h, 40h, 8Bh, 5Ch
    db 24h, 28h, 8Dh, 7Eh, 38h, 53h, 89h, 44h, 24h, 18h, 89h, 4Ch, 24h, 1Ch, 89h, 54h
    db 24h, 20h, 0E8h, 29h, 69h, 6Bh, 00h, 0D8h, 0Dh, 68h, 5Ch, 07h, 01h, 53h, 0D8h, 44h
    db 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0E8h, 05h, 69h, 6Bh, 00h, 0D8h, 0Dh, 68h, 5Ch, 07h
    db 01h, 83h, 0C4h, 08h, 6Ah, 00h, 8Dh, 44h, 24h, 18h, 0D8h, 44h, 24h, 1Ch, 50h, 56h
    db 8Bh, 0CDh, 0D9h, 5Ch, 24h, 24h, 0E8h, 1Eh, 5Bh, 0E4h, 0FFh, 57h, 56h, 8Bh, 0CDh, 0E8h
    db 87h, 2Eh, 0E5h, 0FFh, 5Bh, 5Fh, 5Eh, 5Dh, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_001bce20@@YAXXZ ENDP

; ghidra: FUN_005bd200  retail @ 0x001BD200 size 76
public ?d_001bd200@@YAXXZ
?d_001bd200@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 6Ah, 00h, 68h, 1Ch, 30h, 07h, 01h, 8Dh, 4Eh, 18h, 0E8h, 0Dh
    db 0ABh, 6Ch, 00h, 6Ah, 00h, 68h, 1Ch, 30h, 07h, 01h, 8Dh, 4Eh, 1Ch, 0E8h, 0FEh, 0AAh
    db 6Ch, 00h, 8Bh, 7Ch, 24h, 0Ch, 68h, 38h, 0E0h, 09h, 01h, 56h, 8Bh, 0CFh, 0C7h, 46h
    db 20h, 00h, 00h, 00h, 00h, 0E8h, 66h, 4Eh, 69h, 00h, 8Bh, 44h, 24h, 10h, 50h, 57h
    db 8Bh, 0CEh, 0E8h, 0F2h, 71h, 0E5h, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_001bd200@@YAXXZ ENDP

; ghidra: FUN_005bd490  retail @ 0x001BD490 size 91
public ?d_001bd490@@YAXXZ
?d_001bd490@@YAXXZ PROC
    db 8Bh, 81h, 60h, 02h, 00h, 00h, 33h, 0D2h, 3Bh, 0C2h, 56h, 74h, 0Ch, 8Bh, 0B1h, 5Ch
    db 02h, 00h, 00h, 89h, 0B0h, 5Ch, 02h, 00h, 00h, 8Bh, 81h, 5Ch, 02h, 00h, 00h, 3Bh
    db 0C2h, 74h, 1Ch, 8Bh, 0B1h, 60h, 02h, 00h, 00h, 89h, 0B0h, 60h, 02h, 00h, 00h, 89h
    db 91h, 5Ch, 02h, 00h, 00h, 89h, 91h, 60h, 02h, 00h, 00h, 5Eh, 0C2h, 04h, 00h, 8Bh
    db 81h, 60h, 02h, 00h, 00h, 8Bh, 74h, 24h, 08h, 89h, 06h, 89h, 91h, 5Ch, 02h, 00h
    db 00h, 89h, 91h, 60h, 02h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_001bd490@@YAXXZ ENDP
_TEXT ENDS
END
