.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ?Create_Render_Obj@@YAPAVRenderObjClass@@PBD@Z:NEAR
EXTERN ?Get_Z_Rotation@Matrix3D@@QBEMXZ:NEAR
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012ED5AC@@3PAVOptionPreferences@@A:BYTE
EXTERN ?Rva012F8058@@3PAVRva00712F60@@A:BYTE
EXTERN ?TheParticleSystemManager@@3PAVParticleSystemManager@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?g_bfmeTag1028@@3PADA:BYTE
EXTERN ?j_00001b18@@YAXXZ:NEAR
EXTERN ?j_00002c43@@YAXXZ:NEAR
EXTERN ?j_00005024@@YAXXZ:NEAR
EXTERN ?j_00006e92@@YAXXZ:NEAR
EXTERN ?j_00009ca0@@YAXXZ:NEAR
EXTERN ?j_0000cb80@@YAXXZ:NEAR
EXTERN ?j_0000ce5f@@YAXXZ:NEAR
EXTERN ?j_0000dd50@@YAXXZ:NEAR
EXTERN ?j_0000e525@@YAXXZ:NEAR
EXTERN ?j_0000ebe7@@YAXXZ:NEAR
EXTERN ?j_00012319@@YAXXZ:NEAR
EXTERN ?j_00012d32@@YAXXZ:NEAR
EXTERN ?j_00012e3b@@YAXXZ:NEAR
EXTERN ?j_00013075@@YAXXZ:NEAR
EXTERN ?j_00013746@@YAXXZ:NEAR
EXTERN ?j_00013994@@YAXXZ:NEAR
EXTERN ?j_00021832@@YAXXZ:NEAR
EXTERN ?j_0002319b@@YAXXZ:NEAR
EXTERN ?j_00027aac@@YAXXZ:NEAR
EXTERN ?j_00028524@@YAXXZ:NEAR
EXTERN ?j_0002a216@@YAXXZ:NEAR
EXTERN ?j_0002f766@@YAXXZ:NEAR
EXTERN ?j_0003939c@@YAXXZ:NEAR
EXTERN ?j_0004048a@@YAXXZ:NEAR
EXTERN ?j_00040ae3@@YAXXZ:NEAR
EXTERN ?j_000423b1@@YAXXZ:NEAR
EXTERN ?j_0004429c@@YAXXZ:NEAR
EXTERN ?j_0004484b@@YAXXZ:NEAR
EXTERN ?j_0004697a@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN g_Va0104FF68:NEAR
EXTERN g_Va0104FF88:NEAR
EXTERN g_Va010501D4:NEAR
_TEXT SEGMENT

; ghidra: FUN_00b739f0  retail @ 0x007739F0 size 1310
public ?d_007739f0@@YAXXZ
?d_007739f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 75h, 0FBh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 53h, 55h, 56h, 57h, 0C7h, 44h, 24h, 24h
    db 00h, 00h, 00h, 00h, 8Bh, 7Ch, 24h, 3Ch, 8Bh, 0F1h, 57h, 8Dh, 4Ch, 24h, 18h, 89h
    db 74h, 24h, 1Ch, 0E8h, 38h, 41h, 11h, 00h, 8Bh, 56h, 08h, 8Bh, 6Eh, 04h, 8Dh, 44h
    db 24h, 3Ch, 50h, 52h, 0C7h, 44h, 24h, 38h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 44h
    db 00h, 0E8h, 07h, 15h, 89h, 0FFh, 8Ah, 8Dh, 09h, 01h, 00h, 00h, 8Ah, 5Ch, 24h, 44h
    db 83h, 0C4h, 08h, 84h, 0C9h, 75h, 3Ch, 84h, 0DBh, 75h, 38h, 8Ah, 85h, 08h, 01h, 00h
    db 00h, 84h, 0C0h, 74h, 5Ah, 85h, 0D2h, 74h, 0Eh, 0F6h, 82h, 10h, 01h, 00h, 00h, 20h
    db 0B8h, 02h, 00h, 00h, 00h, 75h, 06h, 8Bh, 86h, 0A0h, 00h, 00h, 00h, 50h, 8Dh, 4Ch
    db 24h, 40h, 57h, 51h, 0E8h, 0C8h, 41h, 8Ah, 0FFh, 83h, 0C4h, 0Ch, 0C6h, 44h, 24h, 30h
    db 03h, 0EBh, 14h, 50h, 8Dh, 54h, 24h, 40h, 57h, 52h, 0E8h, 0B2h, 41h, 8Ah, 0FFh, 83h
    db 0C4h, 0Ch, 0C6h, 44h, 24h, 30h, 02h, 8Dh, 4Ch, 24h, 14h, 50h, 0E8h, 0DFh, 41h, 11h
    db 00h, 8Dh, 4Ch, 24h, 3Ch, 0C6h, 44h, 24h, 30h, 01h, 0E8h, 81h, 3Eh, 11h, 00h, 8Ah
    db 85h, 09h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 0F5h, 00h, 00h, 00h, 84h, 0DBh, 0Fh
    db 84h, 0EDh, 00h, 00h, 00h, 0F6h, 05h, 78h, 5Ah, 30h, 01h, 01h, 75h, 28h, 83h, 0Dh
    db 78h, 5Ah, 30h, 01h, 01h, 0B9h, 68h, 5Ah, 30h, 01h, 0C6h, 44h, 24h, 30h, 04h, 0E8h
    db 0B3h, 0F4h, 8Ah, 0FFh, 68h, 0A0h, 0Ah, 07h, 01h, 0E8h, 28h, 33h, 28h, 00h, 83h, 0C4h
    db 04h, 0C6h, 44h, 24h, 30h, 01h, 8Dh, 44h, 24h, 14h, 50h, 0B9h, 68h, 5Ah, 30h, 01h
    db 0E8h, 5Ch, 0F5h, 88h, 0FFh, 3Bh, 05h, 68h, 5Ah, 30h, 01h, 0Fh, 85h, 0A1h, 00h, 00h
    db 00h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 54h, 24h, 20h, 52h, 0B9h, 68h, 5Ah, 30h, 01h
    db 0E8h, 0CDh, 80h, 8Ah, 0FFh, 0E8h, 96h, 5Bh, 11h, 00h, 84h, 0C0h, 0Fh, 84h, 80h, 00h
    db 00h, 00h, 6Ah, 01h, 0E8h, 57h, 5Bh, 11h, 00h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh
    db 01h, 83h, 0C4h, 04h, 0FFh, 50h, 60h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0Dh, 5Ch, 6Eh
    db 33h, 01h, 8Bh, 11h, 6Ah, 00h, 6Ah, 00h, 0FFh, 52h, 6Ch, 50h, 0E8h, 15h, 34h, 8Ah
    db 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 20h, 8Bh, 40h, 08h, 8Bh, 40h, 04h, 83h, 0C4h, 08h
    db 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 2Bh, 0E7h, 88h, 0FFh
    db 8Bh, 16h, 83h, 0C0h, 20h, 50h, 68h, 9Ch, 3Fh, 12h, 01h, 8Bh, 0CEh, 0FFh, 52h, 38h
    db 50h, 0E8h, 0E0h, 33h, 8Ah, 0FFh, 8Bh, 10h, 83h, 0C4h, 08h, 68h, 20h, 3Fh, 12h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah, 02h, 8Bh, 0C8h, 0FFh, 52h, 4Ch, 8Bh, 74h
    db 24h, 18h, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 50h, 0E8h, 0A6h, 7Fh, 27h, 00h, 83h, 0C4h, 04h, 84h, 0C0h, 0Fh
    db 85h, 2Fh, 01h, 00h, 00h, 84h, 0DBh, 0Fh, 84h, 1Dh, 01h, 00h, 00h, 0F6h, 05h, 78h
    db 5Ah, 30h, 01h, 02h, 75h, 28h, 83h, 0Dh, 78h, 5Ah, 30h, 01h, 02h, 0B9h, 58h, 5Ah
    db 30h, 01h, 0C6h, 44h, 24h, 30h, 05h, 0E8h, 9Bh, 0F3h, 8Ah, 0FFh, 68h, 90h, 0Ah, 07h
    db 01h, 0E8h, 10h, 32h, 28h, 00h, 83h, 0C4h, 04h, 0C6h, 44h, 24h, 30h, 01h, 8Dh, 44h
    db 24h, 14h, 50h, 0B9h, 58h, 5Ah, 30h, 01h, 0E8h, 44h, 0F4h, 88h, 0FFh, 3Bh, 05h, 58h
    db 5Ah, 30h, 01h, 0Fh, 85h, 0D1h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 54h
    db 24h, 20h, 52h, 0B9h, 58h, 5Ah, 30h, 01h, 0E8h, 0B5h, 7Fh, 8Ah, 0FFh, 0E8h, 7Eh, 5Ah
    db 11h, 00h, 84h, 0C0h, 0Fh, 84h, 0B0h, 00h, 00h, 00h, 6Ah, 01h, 0E8h, 3Fh, 5Ah, 11h
    db 00h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 01h, 83h, 0C4h, 04h, 0FFh, 50h, 60h, 8Dh
    db 4Ch, 24h, 14h, 51h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 6Ah, 00h, 6Ah, 00h
    db 0FFh, 52h, 6Ch, 50h, 0E8h, 0FDh, 32h, 8Ah, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 20h, 8Bh
    db 40h, 08h, 8Bh, 40h, 04h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h
    db 0C9h, 74h, 05h, 0E8h, 13h, 0E6h, 88h, 0FFh, 8Bh, 16h, 83h, 0C0h, 20h, 50h, 68h, 08h
    db 3Fh, 12h, 01h, 8Bh, 0CEh, 0FFh, 52h, 38h, 50h, 0E8h, 0C8h, 32h, 8Ah, 0FFh, 8Bh, 10h
    db 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 14h, 51h, 68h, 0E4h, 3Eh, 12h, 01h, 8Bh, 0C8h, 0FFh
    db 52h, 38h, 50h, 0E8h, 0AEh, 32h, 8Ah, 0FFh, 8Bh, 10h, 83h, 0C4h, 08h, 57h, 68h, 0B0h
    db 3Eh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 50h, 0E8h, 98h, 32h, 8Ah, 0FFh, 8Bh, 10h
    db 83h, 0C4h, 08h, 68h, 6Ch, 3Eh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah
    db 02h, 8Bh, 0C8h, 0FFh, 52h, 4Ch, 8Bh, 74h, 24h, 18h, 57h, 8Dh, 4Ch, 24h, 18h, 0E8h
    db 7Ch, 3Fh, 11h, 00h, 8Ah, 85h, 0Bh, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 87h, 01h
    db 00h, 00h, 8Bh, 86h, 48h, 01h, 00h, 00h, 8Bh, 0D8h, 8Bh, 0C8h, 0C1h, 0EBh, 08h, 0C1h
    db 0E9h, 07h, 80h, 0E1h, 01h, 80h, 0E3h, 01h, 0A8h, 20h, 88h, 4Ch, 24h, 13h, 75h, 25h
    db 0A8h, 10h, 75h, 21h, 0A8h, 08h, 75h, 1Dh, 84h, 0C9h, 75h, 19h, 84h, 0DBh, 75h, 15h
    db 8Bh, 74h, 24h, 38h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0E8h, 00h, 3Eh, 11h, 00h
    db 0E9h, 54h, 01h, 00h, 00h, 0B8h, 03h, 00h, 00h, 00h, 89h, 44h, 24h, 1Ch, 8Bh, 0FFh
    db 48h, 74h, 18h, 48h, 74h, 0Bh, 48h, 75h, 28h, 8Ah, 86h, 48h, 01h, 00h, 00h, 0EBh
    db 18h, 8Bh, 86h, 48h, 01h, 00h, 00h, 0A8h, 10h, 0EBh, 0Ch, 8Bh, 86h, 48h, 01h, 00h
    db 00h, 0A8h, 10h, 75h, 0Ch, 0A8h, 08h, 75h, 08h, 0A8h, 20h, 0Fh, 84h, 0F9h, 00h, 00h
    db 00h, 0BFh, 01h, 00h, 00h, 00h, 85h, 0FFh, 74h, 08h, 84h, 0C9h, 0Fh, 84h, 0E1h, 00h
    db 00h, 00h, 0BDh, 01h, 00h, 00h, 00h, 85h, 0EDh, 74h, 08h, 84h, 0DBh, 0Fh, 84h, 0C5h
    db 00h, 00h, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 8Fh, 3Dh, 11h
    db 00h, 6Ah, 01h, 8Dh, 54h, 24h, 40h, 52h, 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 38h
    db 06h, 0C6h, 44h, 24h, 44h, 5Fh, 0E8h, 75h, 3Fh, 11h, 00h, 85h, 0FFh, 74h, 15h, 6Ah
    db 01h, 8Dh, 44h, 24h, 40h, 50h, 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 44h, 6Eh, 0E8h
    db 5Ch, 3Fh, 11h, 00h, 8Bh, 44h, 24h, 1Ch, 48h, 74h, 22h, 48h, 74h, 11h, 48h, 75h
    db 31h, 6Ah, 01h, 8Dh, 4Ch, 24h, 40h, 0C6h, 44h, 24h, 40h, 72h, 51h, 0EBh, 1Ah, 6Ah
    db 01h, 8Dh, 54h, 24h, 40h, 0C6h, 44h, 24h, 40h, 65h, 52h, 0EBh, 0Ch, 6Ah, 01h, 8Dh
    db 44h, 24h, 40h, 0C6h, 44h, 24h, 40h, 64h, 50h, 8Dh, 4Ch, 24h, 20h, 0E8h, 1Eh, 3Fh
    db 11h, 00h, 85h, 0EDh, 74h, 15h, 6Ah, 01h, 8Dh, 4Ch, 24h, 40h, 51h, 8Dh, 4Ch, 24h
    db 20h, 0C6h, 44h, 24h, 44h, 73h, 0E8h, 05h, 3Fh, 11h, 00h, 8Bh, 44h, 24h, 18h, 85h
    db 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h, 0Dh
    db 7Dh, 27h, 00h, 83h, 0C4h, 04h, 84h, 0C0h, 75h, 6Ch, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h
    db 24h, 30h, 01h, 0E8h, 0B8h, 3Ah, 11h, 00h, 4Dh, 0Fh, 89h, 28h, 0FFh, 0FFh, 0FFh, 8Ah
    db 4Ch, 24h, 13h, 4Fh, 0Fh, 89h, 0Ch, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 48h, 89h
    db 44h, 24h, 1Ch, 0Fh, 89h, 0C7h, 0FEh, 0FFh, 0FFh, 8Bh, 74h, 24h, 38h, 8Dh, 44h, 24h
    db 14h, 50h, 8Bh, 0CEh, 0E8h, 0A7h, 3Ch, 11h, 00h, 0C7h, 44h, 24h, 24h, 01h, 00h, 00h
    db 00h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 30h, 00h, 0E8h, 71h, 3Ah, 11h, 00h, 8Bh
    db 4Ch, 24h, 28h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 24h, 0C2h, 08h, 00h, 8Bh, 74h, 24h, 38h, 8Dh, 54h, 24h, 18h, 52h, 8Bh
    db 0CEh, 0E8h, 6Ah, 3Ch, 11h, 00h, 8Dh, 4Ch, 24h, 18h, 0C7h, 44h, 24h, 24h, 01h, 00h
    db 00h, 00h, 0C6h, 44h, 24h, 30h, 01h, 0E8h, 34h, 3Ah, 11h, 00h, 0EBh, 0B3h
?d_007739f0@@YAXXZ ENDP

; ghidra: FUN_00b74090  retail @ 0x00774090 size 62
public ?d_00774090@@YAXXZ
?d_00774090@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 74h
    db 17h, 51h, 50h, 0E8h, 03h, 77h, 8Bh, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h
    db 38h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 10h
    db 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0E3h, 0D7h, 8Ch, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_00774090@@YAXXZ ENDP

; ghidra: FUN_00b74130  retail @ 0x00774130 size 163
public ?d_00774130@@YAXXZ
?d_00774130@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 0FBh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 0Eh
    db 8Bh, 0CEh, 0E8h, 53h, 67h, 8Bh, 0FFh, 83h, 0C6h, 2Ch, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 45h, 8Bh, 4Fh, 08h, 2Bh
    db 0CEh, 0B8h, 0E9h, 0A2h, 8Bh, 2Eh, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh
    db 03h, 0C2h, 6Bh, 0C0h, 2Ch, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Bh, 56h, 0E8h, 0Eh, 0DDh
    db 10h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h, 56h, 0E8h, 32h, 0A4h, 0Bh, 00h, 83h, 0C4h
    db 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_00774130@@YAXXZ ENDP

; ghidra: FUN_00b742a0  retail @ 0x007742A0 size 287
public ?d_007742a0@@YAXXZ
?d_007742a0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 00h, 8Bh, 4Dh, 04h, 2Bh, 0C8h, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0E9h, 8Bh, 4Ch, 24h, 20h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h
    db 0E8h, 1Fh, 03h, 0C2h, 56h, 3Bh, 0C1h, 57h, 89h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 28h
    db 72h, 04h, 8Dh, 4Ch, 24h, 10h, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 14h, 74h, 2Ah
    db 8Dh, 04h, 89h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h, 3Dh
    db 0DCh, 10h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 16h, 0E8h, 3Fh, 0A2h, 0Bh
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 8Bh, 75h, 00h, 8Bh, 5Ch, 24h, 1Ch, 3Bh, 0F3h, 8Bh, 7Ch, 24h, 10h, 74h
    db 14h, 56h, 57h, 0E8h, 45h, 6Fh, 8Dh, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h, 83h, 0C7h
    db 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 74h, 24h, 28h, 83h, 0FEh, 01h, 75h, 13h, 8Bh, 44h
    db 24h, 20h, 50h, 57h, 0E8h, 24h, 6Fh, 8Dh, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 0EBh
    db 1Fh, 85h, 0F6h, 76h, 1Bh, 8Bh, 5Ch, 24h, 20h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 53h, 57h, 0E8h, 06h, 6Fh, 8Dh, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 4Eh, 75h, 0F0h
    db 8Ah, 44h, 24h, 2Ch, 84h, 0C0h, 75h, 1Fh, 8Bh, 5Dh, 04h, 8Bh, 74h, 24h, 1Ch, 3Bh
    db 0F3h, 74h, 14h, 56h, 57h, 0E8h, 0E3h, 6Eh, 8Dh, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h
    db 83h, 0C7h, 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0CDh, 0E8h, 0A8h, 79h, 8Bh, 0FFh, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 10h, 89h, 7Dh, 04h, 5Fh, 8Dh, 0Ch, 89h, 8Dh, 14h, 88h
    db 5Eh, 89h, 45h, 00h, 89h, 55h, 08h, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 14h, 00h
?d_007742a0@@YAXXZ ENDP

; ghidra: FUN_00b74410  retail @ 0x00774410 size 287
public ?d_00774410@@YAXXZ
?d_00774410@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 00h, 8Bh, 4Dh, 04h, 2Bh, 0C8h, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0E9h, 8Bh, 4Ch, 24h, 20h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h
    db 0E8h, 1Fh, 03h, 0C2h, 56h, 3Bh, 0C1h, 57h, 89h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 28h
    db 72h, 04h, 8Dh, 4Ch, 24h, 10h, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 14h, 74h, 2Ah
    db 8Dh, 04h, 89h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h, 0CDh
    db 0DAh, 10h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 16h, 0E8h, 0CFh, 0A0h, 0Bh
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 8Bh, 75h, 00h, 8Bh, 5Ch, 24h, 1Ch, 3Bh, 0F3h, 8Bh, 7Ch, 24h, 10h, 74h
    db 14h, 56h, 57h, 0E8h, 8Eh, 21h, 8Ah, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h, 83h, 0C7h
    db 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 74h, 24h, 28h, 83h, 0FEh, 01h, 75h, 13h, 8Bh, 44h
    db 24h, 20h, 50h, 57h, 0E8h, 6Dh, 21h, 8Ah, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 0EBh
    db 1Fh, 85h, 0F6h, 76h, 1Bh, 8Bh, 5Ch, 24h, 20h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 53h, 57h, 0E8h, 4Fh, 21h, 8Ah, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 4Eh, 75h, 0F0h
    db 8Ah, 44h, 24h, 2Ch, 84h, 0C0h, 75h, 1Fh, 8Bh, 5Dh, 04h, 8Bh, 74h, 24h, 1Ch, 3Bh
    db 0F3h, 74h, 14h, 56h, 57h, 0E8h, 2Ch, 21h, 8Ah, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h
    db 83h, 0C7h, 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0CDh, 0E8h, 0DBh, 3Ch, 8Dh, 0FFh, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 10h, 89h, 7Dh, 04h, 5Fh, 8Dh, 0Ch, 89h, 8Dh, 14h, 88h
    db 5Eh, 89h, 45h, 00h, 89h, 55h, 08h, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 14h, 00h
?d_00774410@@YAXXZ ENDP

; ghidra: FUN_00b746e0  retail @ 0x007746E0 size 95
public ?d_007746e0@@YAXXZ
?d_007746e0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0C3h, 61h, 8Bh, 0FFh, 83h, 0C6h, 2Ch, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 37h, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 0E9h, 0A2h, 8Bh, 2Eh, 0F7h, 0E9h
    db 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 6Bh, 0C0h, 2Ch, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Dh, 56h, 0E8h, 86h, 0D7h, 10h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh
    db 0C3h, 50h, 56h, 0E8h, 0B8h, 9Eh, 0Bh, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 0C3h
?d_007746e0@@YAXXZ ENDP

; ghidra: FUN_00b74760  retail @ 0x00774760 size 51
public ?d_00774760@@YAXXZ
?d_00774760@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 3Bh, 0F3h, 57h, 8Bh, 7Ch, 24h
    db 18h, 74h, 1Ah, 56h, 57h, 0E8h, 0FCh, 4Eh, 8Ch, 0FFh, 81h, 0C6h, 28h, 01h, 00h, 00h
    db 83h, 0C4h, 08h, 81h, 0C7h, 28h, 01h, 00h, 00h, 3Bh, 0F3h, 75h, 0E6h, 8Bh, 0C7h, 5Fh
    db 5Eh, 5Bh, 0C3h
?d_00774760@@YAXXZ ENDP

; ghidra: FUN_00b747e0  retail @ 0x007747E0 size 51
public ?d_007747e0@@YAXXZ
?d_007747e0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 3Bh, 0F3h, 57h, 8Bh, 7Ch, 24h
    db 18h, 74h, 1Ah, 56h, 57h, 0E8h, 0D4h, 2Dh, 8Ch, 0FFh, 81h, 0C6h, 0BCh, 00h, 00h, 00h
    db 83h, 0C4h, 08h, 81h, 0C7h, 0BCh, 00h, 00h, 00h, 3Bh, 0F3h, 75h, 0E6h, 8Bh, 0C7h, 5Fh
    db 5Eh, 5Bh, 0C3h
?d_007747e0@@YAXXZ ENDP

; ghidra: FUN_00b74860  retail @ 0x00774860 size 84
public ?d_00774860@@YAXXZ
?d_00774860@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 8Bh, 74h, 24h, 10h, 8Bh, 0CEh, 2Bh, 0CBh, 0B8h, 5Dh
    db 41h, 4Ch, 0AEh, 0F7h, 0E9h, 03h, 0D1h, 0C1h, 0FAh, 07h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 85h, 0C0h, 7Eh, 28h, 57h, 8Bh, 7Ch, 24h, 18h, 8Bh, 0D8h, 8Dh, 64h, 24h, 00h
    db 81h, 0EEh, 0BCh, 00h, 00h, 00h, 81h, 0EFh, 0BCh, 00h, 00h, 00h, 56h, 8Bh, 0CFh, 0E8h
    db 0DDh, 65h, 8Ch, 0FFh, 4Bh, 75h, 0E9h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h, 8Bh, 44h, 24h
    db 14h, 5Eh, 5Bh, 0C3h
?d_00774860@@YAXXZ ENDP

; ghidra: FUN_00b748d0  retail @ 0x007748D0 size 127
public ?d_007748d0@@YAXXZ
?d_007748d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 53h, 8Bh, 5Ch, 24h, 08h, 2Bh, 0C3h, 0C1h, 0F8h, 05h, 85h, 0C0h
    db 7Eh, 67h, 55h, 8Bh, 6Ch, 24h, 14h, 56h, 57h, 8Dh, 7Dh, 04h, 8Dh, 73h, 04h, 89h
    db 44h, 24h, 1Ch, 3Bh, 0F7h, 8Bh, 03h, 89h, 45h, 00h, 74h, 13h, 8Bh, 56h, 04h, 8Bh
    db 06h, 8Dh, 4Ch, 24h, 1Ch, 51h, 52h, 50h, 8Bh, 0CFh, 0E8h, 49h, 0D1h, 8Ah, 0FFh, 8Dh
    db 4Eh, 0Ch, 8Bh, 01h, 8Dh, 57h, 0Ch, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h, 8Bh
    db 49h, 08h, 8Bh, 44h, 24h, 1Ch, 89h, 4Ah, 08h, 8Bh, 56h, 18h, 89h, 57h, 18h, 83h
    db 0C3h, 20h, 83h, 0C6h, 20h, 83h, 0C5h, 20h, 83h, 0C7h, 20h, 48h, 89h, 44h, 24h, 1Ch
    db 75h, 0B1h, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C3h, 8Bh, 44h, 24h, 10h, 5Bh, 0C3h
?d_007748d0@@YAXXZ ENDP

; ghidra: FUN_00b74970  retail @ 0x00774970 size 181
public ?d_00774970@@YAXXZ
?d_00774970@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 53h, 8Bh, 5Ch, 24h, 08h, 2Bh, 0CBh, 0B8h, 0E9h, 0A2h, 8Bh, 2Eh
    db 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 85h, 0C0h, 0Fh, 8Eh
    db 8Bh, 00h, 00h, 00h, 55h, 8Bh, 6Ch, 24h, 14h, 56h, 57h, 8Dh, 7Dh, 18h, 8Dh, 73h
    db 1Ch, 89h, 44h, 24h, 1Ch, 3Bh, 0DDh, 74h, 13h, 8Bh, 4Eh, 0E8h, 8Bh, 13h, 8Dh, 44h
    db 24h, 1Ch, 50h, 51h, 52h, 8Bh, 0CDh, 0E8h, 9Ch, 0D0h, 8Ah, 0FFh, 8Dh, 46h, 0F0h, 8Dh
    db 4Fh, 0F4h, 3Bh, 0C1h, 74h, 15h, 8Bh, 46h, 0F4h, 8Bh, 4Eh, 0F0h, 8Dh, 54h, 24h, 1Ch
    db 52h, 50h, 51h, 8Dh, 4Fh, 0F4h, 0E8h, 7Dh, 0D0h, 8Ah, 0FFh, 8Dh, 56h, 0FCh, 3Bh, 0D7h
    db 74h, 13h, 8Bh, 0Eh, 8Bh, 56h, 0FCh, 8Dh, 44h, 24h, 1Ch, 50h, 51h, 52h, 8Bh, 0CFh
    db 0E8h, 63h, 0D0h, 8Ah, 0FFh, 8Bh, 46h, 08h, 89h, 47h, 0Ch, 8Bh, 4Eh, 0Ch, 8Bh, 44h
    db 24h, 1Ch, 89h, 4Fh, 10h, 83h, 0C3h, 2Ch, 83h, 0C6h, 2Ch, 83h, 0C5h, 2Ch, 83h, 0C7h
    db 2Ch, 48h, 89h, 44h, 24h, 1Ch, 75h, 8Dh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C3h, 8Bh
    db 44h, 24h, 10h, 5Bh, 0C3h
?d_00774970@@YAXXZ ENDP

; ghidra: FUN_00b74aa0  retail @ 0x00774AA0 size 144
public ?d_00774aa0@@YAXXZ
?d_00774aa0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 14h, 85h, 0DBh, 55h, 8Bh, 0E9h, 74h, 7Fh, 0F6h, 83h, 0ACh, 00h
    db 00h, 00h, 10h, 75h, 4Fh, 0A1h, 98h, 08h, 2Fh, 01h, 85h, 0C0h, 74h, 07h, 8Ah, 48h
    db 6Bh, 84h, 0C9h, 75h, 10h, 0A1h, 90h, 0F1h, 2Eh, 01h, 85h, 0C0h, 74h, 36h, 8Ah, 48h
    db 54h, 84h, 0C9h, 74h, 2Fh, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 37h, 3Bh, 77h, 04h
    db 74h, 12h, 56h, 8Bh, 0CDh, 0E8h, 0E3h, 10h, 89h, 0FFh, 8Bh, 47h, 04h, 83h, 0C6h, 04h
    db 3Bh, 0F0h, 75h, 0EEh, 8Ah, 83h, 0ACh, 00h, 00h, 00h, 0Ch, 10h, 5Fh, 88h, 83h, 0ACh
    db 00h, 00h, 00h, 5Eh, 8Bh, 44h, 24h, 1Ch, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 0Ch
    db 50h, 53h, 51h, 52h, 8Bh, 0CDh, 0E8h, 7Fh, 47h, 8Ah, 0FFh, 53h, 8Bh, 0CDh, 0E8h, 0F8h
    db 55h, 8Ch, 0FFh, 55h, 8Bh, 0CBh, 0E8h, 0E4h, 09h, 8Ah, 0FFh, 5Dh, 5Bh, 0C2h, 14h, 00h
?d_00774aa0@@YAXXZ ENDP

; ghidra: FUN_00b74b60  retail @ 0x00774B60 size 373
public ?d_00774b60@@YAXXZ
?d_00774b60@@YAXXZ PROC
    db 33h, 0C0h, 53h, 55h, 56h, 8Bh, 0F1h, 89h, 01h, 89h, 41h, 04h, 89h, 41h, 08h, 89h
    db 41h, 0Ch, 89h, 41h, 10h, 89h, 41h, 14h, 89h, 41h, 18h, 89h, 41h, 1Ch, 89h, 41h
    db 20h, 89h, 41h, 24h, 8Bh, 56h, 2Ch, 8Bh, 46h, 28h, 8Dh, 4Eh, 28h, 57h, 52h, 50h
    db 0E8h, 82h, 00h, 8Bh, 0FFh, 8Dh, 4Eh, 34h, 0E8h, 0A3h, 2Dh, 11h, 00h, 8Bh, 56h, 44h
    db 8Bh, 46h, 40h, 8Dh, 4Eh, 40h, 52h, 50h, 0E8h, 6Ah, 00h, 8Bh, 0FFh, 8Dh, 8Eh, 9Ch
    db 00h, 00h, 00h, 0E8h, 18h, 2Eh, 8Bh, 0FFh, 8Bh, 96h, 0A4h, 00h, 00h, 00h, 8Bh, 86h
    db 0A0h, 00h, 00h, 00h, 8Dh, 8Eh, 0A0h, 00h, 00h, 00h, 52h, 50h, 0E8h, 0E6h, 0D9h, 89h
    db 0FFh, 8Dh, 4Eh, 3Ch, 0E8h, 67h, 2Dh, 11h, 00h, 33h, 0DBh, 88h, 5Eh, 38h, 8Dh, 7Eh
    db 5Ch, 0BDh, 04h, 00h, 00h, 00h, 8Dh, 4Fh, 0F0h, 0E8h, 52h, 2Dh, 11h, 00h, 8Bh, 0CFh
    db 0E8h, 4Bh, 2Dh, 11h, 00h, 8Dh, 4Fh, 10h, 0E8h, 43h, 2Dh, 11h, 00h, 8Dh, 4Fh, 20h
    db 0E8h, 3Bh, 2Dh, 11h, 00h, 8Dh, 4Fh, 30h, 0E8h, 33h, 2Dh, 11h, 00h, 83h, 0C7h, 04h
    db 4Dh, 75h, 0D3h, 89h, 9Eh, 0F0h, 00h, 00h, 00h, 89h, 9Eh, 0F4h, 00h, 00h, 00h, 89h
    db 9Eh, 0F8h, 00h, 00h, 00h, 89h, 9Eh, 0FCh, 00h, 00h, 00h, 89h, 9Eh, 00h, 01h, 00h
    db 00h, 89h, 9Eh, 04h, 01h, 00h, 00h, 89h, 9Eh, 08h, 01h, 00h, 00h, 89h, 9Eh, 0Ch
    db 01h, 00h, 00h, 89h, 9Eh, 10h, 01h, 00h, 00h, 89h, 9Eh, 14h, 01h, 00h, 00h, 89h
    db 9Eh, 18h, 01h, 00h, 00h, 89h, 9Eh, 1Ch, 01h, 00h, 00h, 8Dh, 8Eh, 0BCh, 00h, 00h
    db 00h, 88h, 9Eh, 24h, 01h, 00h, 00h, 0E8h, 0D4h, 2Ch, 11h, 00h, 5Fh, 66h, 89h, 9Eh
    db 0B8h, 00h, 00h, 00h, 89h, 9Eh, 0C0h, 00h, 00h, 00h, 89h, 9Eh, 0C4h, 00h, 00h, 00h
    db 89h, 9Eh, 0C8h, 00h, 00h, 00h, 89h, 9Eh, 0CCh, 00h, 00h, 00h, 89h, 9Eh, 0D0h, 00h
    db 00h, 00h, 89h, 9Eh, 0D4h, 00h, 00h, 00h, 89h, 9Eh, 0DCh, 00h, 00h, 00h, 89h, 9Eh
    db 0E0h, 00h, 00h, 00h, 89h, 9Eh, 0E4h, 00h, 00h, 00h, 88h, 9Eh, 0ECh, 00h, 00h, 00h
    db 88h, 9Eh, 0EDh, 00h, 00h, 00h, 0C7h, 86h, 0D8h, 00h, 00h, 00h, 0FFh, 00h, 00h, 00h
    db 0C7h, 86h, 0E8h, 00h, 00h, 00h, 00h, 00h, 0A0h, 41h, 0C6h, 86h, 0EEh, 00h, 00h, 00h
    db 01h, 5Eh, 5Dh, 5Bh, 0C3h
?d_00774b60@@YAXXZ ENDP

; ghidra: FUN_00b74d40  retail @ 0x00774D40 size 240
public ?d_00774d40@@YAXXZ
?d_00774d40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Eh, 0FCh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 8Dh
    db 6Eh, 50h, 8Bh, 0CDh, 0C7h, 44h, 24h, 18h, 08h, 00h, 00h, 00h, 0E8h, 5Fh, 2Ch, 8Bh
    db 0FFh, 8Bh, 46h, 58h, 8Bh, 4Eh, 54h, 8Dh, 7Eh, 54h, 50h, 51h, 8Bh, 0CFh, 0E8h, 34h
    db 0D8h, 89h, 0FFh, 8Dh, 8Eh, 0B0h, 00h, 00h, 00h, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h
    db 0C6h, 44h, 24h, 18h, 07h, 0E8h, 18h, 1Dh, 8Bh, 0FFh, 68h, 0E8h, 55h, 44h, 00h, 6Ah
    db 04h, 6Ah, 0Ch, 8Dh, 46h, 7Ch, 50h, 0C6h, 44h, 24h, 28h, 06h, 0E8h, 0C5h, 1Fh, 28h
    db 00h, 8Dh, 4Eh, 70h, 0C6h, 44h, 24h, 18h, 05h, 0E8h, 0E7h, 0C3h, 8Ch, 0FFh, 8Dh, 4Eh
    db 60h, 0C6h, 44h, 24h, 18h, 04h, 0E8h, 05h, 0B2h, 8Ch, 0FFh, 8Bh, 0CFh, 0C6h, 44h, 24h
    db 18h, 03h, 0E8h, 0D6h, 0E6h, 89h, 0FFh, 8Bh, 0CDh, 0C6h, 44h, 24h, 18h, 02h, 0E8h, 0EDh
    db 2Bh, 8Bh, 0FFh, 8Bh, 6Dh, 00h, 85h, 0EDh, 74h, 0Bh, 6Ah, 2Ch, 55h, 0E8h, 0FEh, 97h
    db 0Bh, 00h, 83h, 0C4h, 08h, 8Dh, 4Eh, 48h, 0C6h, 44h, 24h, 18h, 01h, 0E8h, 3Eh, 2Bh
    db 11h, 00h, 8Dh, 4Eh, 2Ch, 0C6h, 44h, 24h, 18h, 00h, 0E8h, 8Fh, 1Ch, 8Bh, 0FFh, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 22h, 2Bh, 11h, 00h, 8Bh, 4Ch
    db 24h, 10h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00774d40@@YAXXZ ENDP

; ghidra: FUN_00b74e70  retail @ 0x00774E70 size 272
public ?d_00774e70@@YAXXZ
?d_00774e70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 0FCh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 33h, 0C0h, 56h, 89h, 44h, 24h, 0Ch, 8Bh
    db 74h, 24h, 28h, 8Bh, 4Eh, 08h, 89h, 44h, 24h, 18h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Dh
    db 4Ch, 24h, 08h, 74h, 15h, 51h, 50h, 0E8h, 6Ch, 50h, 8Ch, 0FFh, 8Bh, 46h, 04h, 83h
    db 0C4h, 08h, 83h, 0C0h, 08h, 89h, 46h, 04h, 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h
    db 24h, 30h, 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0C7h, 00h, 89h, 0FFh, 57h, 8Dh, 4Ch, 24h
    db 10h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 62h, 2Ah, 11h, 00h, 8Bh, 7Ch
    db 24h, 24h, 8Bh, 76h, 04h, 8Dh, 54h, 24h, 2Ch, 52h, 8Bh, 0CFh, 0E8h, 0EFh, 0C7h, 0Dh
    db 00h, 8Dh, 4Ch, 24h, 2Ch, 0C7h, 44h, 24h, 1Ch, 01h, 00h, 00h, 00h, 0E8h, 9Eh, 2Eh
    db 11h, 00h, 8Dh, 44h, 24h, 08h, 50h, 8Bh, 0CFh, 0E8h, 0D2h, 0C7h, 0Dh, 00h, 8Dh, 4Eh
    db 0FCh, 50h, 0C6h, 44h, 24h, 20h, 02h, 0E8h, 74h, 2Dh, 11h, 00h, 8Dh, 4Ch, 24h, 08h
    db 0C6h, 44h, 24h, 1Ch, 01h, 0E8h, 16h, 2Ah, 11h, 00h, 68h, 0C8h, 3Fh, 12h, 01h, 8Dh
    db 4Ch, 24h, 30h, 0E8h, 0E2h, 60h, 8Dh, 0FFh, 85h, 0C0h, 5Fh, 75h, 09h, 0C7h, 46h, 0F8h
    db 02h, 00h, 00h, 00h, 0EBh, 19h, 68h, 0C0h, 3Fh, 12h, 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h
    db 0C6h, 60h, 8Dh, 0FFh, 85h, 0C0h, 75h, 07h, 0C7h, 46h, 0F8h, 03h, 00h, 00h, 00h, 8Dh
    db 4Ch, 24h, 28h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D0h, 29h, 11h, 00h
    db 8Bh, 4Ch, 24h, 10h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h
?d_00774e70@@YAXXZ ENDP

; ghidra: FUN_00b74fd0  retail @ 0x00774FD0 size 361
public ?d_00774fd0@@YAXXZ
?d_00774fd0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 0FCh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 40h, 53h, 56h, 8Bh, 74h, 24h, 58h, 8Dh, 44h
    db 24h, 08h, 50h, 8Bh, 0CEh, 0E8h, 0E6h, 0C6h, 0Dh, 00h, 8Dh, 4Ch, 24h, 08h, 51h, 33h
    db 0DBh, 8Dh, 4Ch, 24h, 10h, 89h, 5Ch, 24h, 54h, 0E8h, 52h, 2Bh, 11h, 00h, 8Dh, 4Ch
    db 24h, 08h, 0C6h, 44h, 24h, 50h, 01h, 0E8h, 84h, 2Dh, 11h, 00h, 8Dh, 54h, 24h, 08h
    db 52h, 8Dh, 4Ch, 24h, 14h, 0E8h, 36h, 2Bh, 11h, 00h, 89h, 5Ch, 24h, 14h, 89h, 5Ch
    db 24h, 18h, 89h, 5Ch, 24h, 1Ch, 0C7h, 44h, 24h, 20h, 00h, 00h, 80h, 0BFh, 0C7h, 44h
    db 24h, 24h, 01h, 00h, 00h, 00h, 0C7h, 44h, 24h, 28h, 00h, 00h, 0A0h, 40h, 0C7h, 44h
    db 24h, 2Ch, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 30h, 00h, 00h, 80h, 3Fh, 88h, 5Ch
    db 24h, 34h, 88h, 5Ch, 24h, 35h, 0C7h, 44h, 24h, 38h, 01h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 3Ch, 00h, 00h, 80h, 0BFh, 0C7h, 44h, 24h, 40h, 00h, 00h, 80h, 0BFh, 88h, 5Ch
    db 24h, 44h, 8Dh, 44h, 24h, 0Ch, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 54h, 02h
    db 0E8h, 0FBh, 2Bh, 11h, 00h, 83h, 7Ch, 24h, 64h, 01h, 75h, 08h, 0C7h, 44h, 24h, 24h
    db 02h, 00h, 00h, 00h, 68h, 0A0h, 40h, 12h, 01h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh
    db 0E8h, 0EBh, 0CFh, 0Dh, 00h, 8Bh, 44h, 24h, 38h, 3Bh, 0C3h, 7Dh, 06h, 89h, 5Ch, 24h
    db 38h, 0EBh, 0Dh, 83h, 0F8h, 64h, 7Eh, 08h, 0C7h, 44h, 24h, 38h, 64h, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 18h, 3Bh, 0C3h, 74h, 24h, 66h, 39h, 58h, 04h, 74h, 1Eh, 8Dh, 4Ch
    db 24h, 18h, 0E8h, 0B9h, 30h, 11h, 00h, 84h, 0C0h, 75h, 11h, 8Bh, 4Ch, 24h, 5Ch, 8Dh
    db 54h, 24h, 10h, 52h, 83h, 0C1h, 2Ch, 0E8h, 0A5h, 0Eh, 89h, 0FFh, 8Dh, 4Ch, 24h, 10h
    db 0C6h, 44h, 24h, 50h, 01h, 0E8h, 0C8h, 0F7h, 8Ch, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 88h, 5Ch
    db 24h, 50h, 0E8h, 29h, 28h, 11h, 00h, 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 50h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 18h, 28h, 11h, 00h, 8Bh, 4Ch, 24h, 48h, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C3h
?d_00774fd0@@YAXXZ ENDP

; ghidra: FUN_00b75470  retail @ 0x00775470 size 599
_TEXT ENDS
_TEXT$d00b75470 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B75470 size 599
public ?d_00775470@@YAXXZ
?d_00775470@@YAXXZ PROC
    db 083h, 0ECh, 03Ch, 053h, 055h, 08Bh, 06Ch, 024h, 048h, 056h, 057h, 08Bh, 0F9h, 08Bh, 077h, 0F8h
    db 055h, 08Bh, 0CEh
    call ?j_00005024@@YAXXZ
    db 055h, 08Bh, 0CEh, 08Bh, 0D8h
    call ?j_0000ce5f@@YAXXZ
    db 085h, 0DBh, 08Bh, 0E8h, 075h, 00Ch, 05Fh, 05Eh, 05Dh, 032h, 0C0h, 05Bh, 083h, 0C4h, 03Ch, 0C2h
    db 01Ch, 000h, 08Bh, 04Fh, 0FCh, 08Bh, 081h, 0F0h, 002h, 000h, 000h, 050h, 055h, 08Dh, 046h, 030h
    db 050h
    call ?j_0003939c@@YAXXZ
    db 051h, 0D9h, 01Ch, 024h, 06Ah, 000h, 08Bh, 0CBh
    call ?j_00006e92@@YAXXZ
    db 08Bh, 046h, 040h, 033h, 0DBh, 03Bh, 0C3h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 0C7h
    db 044h, 024h, 014h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 00Fh
    db 084h, 0F4h, 000h, 000h, 000h, 066h, 039h, 058h, 004h, 00Fh, 084h, 0EAh, 000h, 000h, 000h, 08Bh
    db 0F0h, 03Bh, 0F3h, 08Dh, 046h, 008h, 075h, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 04Fh, 0FCh, 053h, 06Ah, 001h, 08Dh, 054h, 024h, 024h, 052h, 053h, 053h, 050h
    call ?j_0002319b@@YAXXZ
    db 083h, 0F8h, 001h, 00Fh, 085h, 0C0h, 000h, 000h, 000h, 08Bh, 047h, 0FCh, 0D9h, 040h, 044h, 08Bh
    db 054h, 024h, 048h, 0D9h, 0C0h, 089h, 054h, 024h, 018h, 0D9h, 0FFh, 0D9h, 0C9h, 0D9h, 0FEh, 0D9h
    db 044h, 024h, 01Ch, 0D9h, 044h, 024h, 01Ch, 0D8h, 0CBh, 0D9h, 044h, 024h, 02Ch, 0D8h, 0CBh, 0DEh
    db 0E9h, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 02Ch, 0D8h, 0CBh, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh
    db 0C1h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 020h, 0D9h, 044h, 024h, 020h, 0D8h, 0CBh, 0D9h
    db 044h, 024h, 030h, 0D8h, 0CBh, 0DEh, 0E9h, 0D9h, 05Ch, 024h, 020h, 0D9h, 044h, 024h, 030h, 0D8h
    db 0CBh, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 030h, 0D9h, 044h, 024h, 024h, 0D9h
    db 044h, 024h, 024h, 0D8h, 0CBh, 0D9h, 044h, 024h, 034h, 0D8h, 0CBh, 0DEh, 0E9h, 0D9h, 05Ch, 024h
    db 024h, 0D9h, 044h, 024h, 034h, 0D8h, 0CBh, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 05Ch, 024h
    db 034h, 0D9h, 044h, 024h, 028h, 0D9h, 044h, 024h, 028h, 0D8h, 0CBh, 0D9h, 044h, 024h, 038h, 0D8h
    db 0CBh, 0DEh, 0E9h, 0D9h, 05Ch, 024h, 028h, 0D9h, 044h, 024h, 038h, 08Bh, 04Ch, 024h, 028h, 0D8h
    db 0CBh, 089h, 04Ch, 024h, 010h, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 054h, 024h, 038h, 0D9h
    db 0CAh, 0DDh, 0D9h, 0DDh, 0D8h, 0D9h, 05Ch, 024h, 014h, 08Bh, 044h, 024h, 054h, 08Dh, 004h, 040h
    db 08Bh, 074h, 085h, 07Ch, 08Dh, 04Ch, 085h, 07Ch, 08Bh, 041h, 004h, 03Bh, 0F0h, 075h, 007h, 033h
    db 0C0h, 0E9h, 09Dh, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 058h, 03Bh, 0CBh, 07Ch, 01Bh, 02Bh, 0C6h
    db 08Bh, 0F8h, 0B8h, 089h, 088h, 088h, 088h, 0F7h, 0EFh, 003h, 0D7h, 0C1h, 0FAh, 005h, 08Bh, 0C2h
    db 0C1h, 0E8h, 01Fh, 003h, 0C2h, 03Bh, 0C8h, 072h, 002h, 033h, 0C9h, 08Bh, 044h, 024h, 05Ch, 03Bh
    db 0C3h, 074h, 070h, 06Bh, 0C9h, 03Ch, 0D9h, 044h, 024h, 010h, 08Bh, 054h, 031h, 00Ch, 089h, 010h
    db 08Bh, 054h, 031h, 010h, 089h, 050h, 004h, 08Bh, 054h, 031h, 014h, 089h, 050h, 008h, 08Bh, 054h
    db 031h, 018h, 08Dh, 04Ch, 031h, 00Ch, 089h, 050h, 00Ch, 08Bh, 051h, 010h, 089h, 050h, 010h, 08Bh
    db 051h, 014h, 089h, 050h, 014h, 08Bh, 051h, 018h, 089h, 050h, 018h, 08Bh, 051h, 01Ch, 089h, 050h
    db 01Ch, 08Bh, 051h, 020h, 089h, 050h, 020h, 08Bh, 051h, 024h, 089h, 050h, 024h, 08Bh, 051h, 028h
    db 089h, 050h, 028h, 08Bh, 049h, 02Ch, 089h, 048h, 02Ch, 0D8h, 040h, 00Ch, 0D9h, 058h, 00Ch, 0D9h
    db 044h, 024h, 014h, 0D8h, 040h, 01Ch, 0D9h, 058h, 01Ch, 0D9h, 044h, 024h, 018h, 0D8h, 040h, 02Ch
    db 0D9h, 058h, 02Ch, 08Bh, 04Ch, 024h, 064h, 03Bh, 0CBh, 074h, 008h, 089h, 019h, 089h, 059h, 004h
    db 089h, 059h, 008h, 08Bh, 04Ch, 024h, 068h, 03Bh, 0CBh, 074h, 008h, 089h, 019h, 089h, 059h, 004h
    db 089h, 059h, 008h, 05Fh, 05Eh, 03Bh, 0C3h, 05Dh, 00Fh, 095h, 0C0h, 05Bh, 083h, 0C4h, 03Ch, 0C2h
    db 01Ch, 000h
?d_00775470@@YAXXZ ENDP
_TEXT$d00b75470 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b75760  retail @ 0x00775760 size 1036
public ?d_00775760@@YAXXZ
?d_00775760@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Eh, 0FDh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 1Ch, 01h, 00h, 00h, 53h, 55h, 8Bh, 0ACh, 24h
    db 34h, 01h, 00h, 00h, 56h, 8Bh, 71h, 0F8h, 57h, 89h, 4Ch, 24h, 20h, 55h, 8Bh, 0CEh
    db 0E8h, 8Fh, 0F8h, 88h, 0FFh, 8Bh, 0F8h, 33h, 0DBh, 3Bh, 0FBh, 75h, 07h, 33h, 0C0h, 0E9h
    db 0ADh, 03h, 00h, 00h, 55h, 8Bh, 0CEh, 0E8h, 0B3h, 76h, 89h, 0FFh, 8Bh, 0D0h, 8Bh, 44h
    db 24h, 20h, 3Bh, 78h, 04h, 89h, 54h, 24h, 24h, 75h, 05h, 8Bh, 68h, 28h, 0EBh, 02h
    db 33h, 0EDh, 8Bh, 48h, 0FCh, 8Bh, 81h, 0F0h, 02h, 00h, 00h, 50h, 52h, 83h, 0C6h, 30h
    db 56h, 0E8h, 0C6h, 3Bh, 8Ch, 0FFh, 51h, 0D9h, 1Ch, 24h, 55h, 8Bh, 0CFh, 0E8h, 0B0h, 16h
    db 89h, 0FFh, 0F6h, 05h, 0E8h, 68h, 30h, 01h, 01h, 0BEh, 40h, 00h, 00h, 00h, 75h, 2Bh
    db 83h, 0Dh, 0E8h, 68h, 30h, 01h, 01h, 68h, 0EFh, 58h, 44h, 00h, 56h, 6Ah, 30h, 68h
    db 80h, 5Ah, 30h, 01h, 89h, 9Ch, 24h, 44h, 01h, 00h, 00h, 0E8h, 4Ch, 56h, 89h, 0FFh
    db 0C7h, 84h, 24h, 34h, 01h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 39h, 0B4h, 24h, 50h, 01h
    db 00h, 00h, 7Eh, 07h, 89h, 0B4h, 24h, 50h, 01h, 00h, 00h, 39h, 9Ch, 24h, 4Ch, 01h
    db 00h, 00h, 75h, 0Bh, 0C7h, 84h, 24h, 4Ch, 01h, 00h, 00h, 80h, 5Ah, 30h, 01h, 8Bh
    db 84h, 24h, 44h, 01h, 00h, 00h, 33h, 0EDh, 8Bh, 0C8h, 0F7h, 0D9h, 1Bh, 0C9h, 83h, 0E1h
    db 63h, 3Bh, 0C1h, 8Bh, 0D0h, 89h, 4Ch, 24h, 28h, 89h, 54h, 24h, 10h, 0Fh, 8Fh, 0F3h
    db 01h, 00h, 00h, 8Bh, 0BCh, 24h, 4Ch, 01h, 00h, 00h, 83h, 0C7h, 18h, 8Dh, 49h, 00h
    db 3Bh, 0D3h, 8Bh, 84h, 24h, 40h, 01h, 00h, 00h, 75h, 12h, 8Dh, 54h, 24h, 2Ch, 2Bh
    db 0D0h, 8Ah, 08h, 88h, 0Ch, 10h, 40h, 3Ah, 0CBh, 75h, 0F6h, 0EBh, 15h, 52h, 50h, 8Dh
    db 4Ch, 24h, 34h, 68h, 88h, 39h, 12h, 01h, 51h, 0FFh, 15h, 8Ch, 94h, 35h, 01h, 83h
    db 0C4h, 10h, 8Dh, 74h, 24h, 2Ch, 8Ah, 06h, 3Ah, 0C3h, 74h, 13h, 0Fh, 0BEh, 0D0h, 52h
    db 0FFh, 15h, 0FCh, 94h, 35h, 01h, 83h, 0C4h, 04h, 46h, 88h, 46h, 0FFh, 75h, 0E7h, 8Bh
    db 0Dh, 00h, 0D6h, 2Eh, 01h, 8Dh, 44h, 24h, 2Ch, 50h, 0E8h, 08h, 55h, 8Ch, 0FFh, 8Bh
    db 4Ch, 24h, 24h, 0F6h, 81h, 0ACh, 00h, 00h, 00h, 01h, 0Fh, 84h, 0D1h, 00h, 00h, 00h
    db 3Bh, 0C3h, 0Fh, 84h, 0C9h, 00h, 00h, 00h, 8Bh, 71h, 70h, 8Bh, 4Eh, 04h, 3Bh, 0CBh
    db 8Bh, 0D6h, 74h, 13h, 39h, 41h, 10h, 7Ch, 07h, 8Bh, 0D1h, 8Bh, 49h, 08h, 0EBh, 03h
    db 8Bh, 49h, 0Ch, 3Bh, 0CBh, 75h, 0EDh, 3Bh, 0D6h, 74h, 05h, 3Bh, 42h, 10h, 7Dh, 02h
    db 8Bh, 0D6h, 8Bh, 4Ch, 24h, 24h, 3Bh, 51h, 70h, 0Fh, 84h, 92h, 00h, 00h, 00h, 8Dh
    db 42h, 14h, 3Bh, 0C3h, 0Fh, 84h, 87h, 00h, 00h, 00h, 8Bh, 10h, 89h, 57h, 0E8h, 8Bh
    db 48h, 04h, 89h, 4Fh, 0ECh, 8Bh, 50h, 08h, 89h, 57h, 0F0h, 8Bh, 48h, 0Ch, 89h, 4Fh
    db 0F4h, 8Bh, 50h, 10h, 89h, 57h, 0F8h, 8Bh, 48h, 14h, 89h, 4Fh, 0FCh, 8Bh, 50h, 18h
    db 89h, 17h, 8Bh, 48h, 1Ch, 89h, 4Fh, 04h, 8Bh, 50h, 20h, 89h, 57h, 08h, 8Bh, 48h
    db 24h, 89h, 4Fh, 0Ch, 8Bh, 50h, 28h, 89h, 57h, 10h, 8Bh, 40h, 2Ch, 89h, 47h, 14h
    db 8Bh, 84h, 24h, 54h, 01h, 00h, 00h, 3Bh, 0C3h, 74h, 07h, 8Bh, 4Ch, 24h, 10h, 89h
    db 0Ch, 0A8h, 8Bh, 84h, 24h, 50h, 01h, 00h, 00h, 45h, 83h, 0C7h, 30h, 3Bh, 0E8h, 0Fh
    db 8Dh, 0C1h, 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 8Bh, 4Ch, 24h, 28h, 40h, 3Bh, 0C1h
    db 89h, 44h, 24h, 10h, 0Fh, 8Fh, 0ACh, 00h, 00h, 00h, 8Bh, 0D0h, 0E9h, 0BFh, 0FEh, 0FFh
    db 0FFh, 8Bh, 84h, 24h, 54h, 01h, 00h, 00h, 3Bh, 0C3h, 74h, 03h, 89h, 1Ch, 0A8h, 8Bh
    db 54h, 24h, 20h, 8Bh, 42h, 0FCh, 8Bh, 88h, 0FCh, 00h, 00h, 00h, 8Dh, 44h, 6Dh, 00h
    db 0C1h, 0E0h, 04h, 3Bh, 0CBh, 74h, 50h, 03h, 84h, 24h, 4Ch, 01h, 00h, 00h, 8Bh, 51h
    db 08h, 89h, 10h, 8Bh, 51h, 0Ch, 89h, 50h, 04h, 8Bh, 51h, 10h, 89h, 50h, 08h, 8Bh
    db 51h, 14h, 89h, 50h, 0Ch, 8Bh, 51h, 18h, 89h, 50h, 10h, 8Bh, 51h, 1Ch, 89h, 50h
    db 14h, 8Bh, 51h, 20h, 89h, 50h, 18h, 8Bh, 51h, 24h, 89h, 50h, 1Ch, 8Bh, 51h, 28h
    db 89h, 50h, 20h, 8Bh, 51h, 2Ch, 89h, 50h, 24h, 8Bh, 51h, 30h, 89h, 50h, 28h, 8Bh
    db 49h, 34h, 89h, 48h, 2Ch, 0EBh, 2Fh, 03h, 84h, 24h, 4Ch, 01h, 00h, 00h, 89h, 58h
    db 04h, 89h, 58h, 08h, 89h, 58h, 0Ch, 0B9h, 00h, 00h, 80h, 3Fh, 89h, 08h, 89h, 58h
    db 10h, 89h, 48h, 14h, 89h, 58h, 18h, 89h, 58h, 1Ch, 89h, 58h, 20h, 89h, 58h, 24h
    db 89h, 48h, 28h, 89h, 58h, 2Ch, 8Bh, 0BCh, 24h, 48h, 01h, 00h, 00h, 3Bh, 0FBh, 0Fh
    db 84h, 0EAh, 00h, 00h, 00h, 8Bh, 84h, 24h, 4Ch, 01h, 00h, 00h, 3Bh, 0C3h, 0Fh, 84h
    db 0DBh, 00h, 00h, 00h, 33h, 0F6h, 83h, 0FDh, 04h, 0Fh, 8Ch, 8Dh, 00h, 00h, 00h, 8Dh
    db 55h, 0FCh, 0C1h, 0EAh, 02h, 83h, 0C0h, 4Ch, 42h, 8Dh, 4Fh, 08h, 8Dh, 34h, 95h, 00h
    db 00h, 00h, 00h, 0D9h, 40h, 0C0h, 8Bh, 58h, 0E0h, 0D9h, 40h, 0D0h, 89h, 19h, 0D9h, 0C9h
    db 89h, 5Ch, 24h, 1Ch, 0D9h, 59h, 0F8h, 05h, 0C0h, 00h, 00h, 00h, 83h, 0C1h, 30h, 4Ah
    db 0D9h, 59h, 0CCh, 0D9h, 80h, 30h, 0FFh, 0FFh, 0FFh, 8Bh, 98h, 50h, 0FFh, 0FFh, 0FFh, 0D9h
    db 80h, 40h, 0FFh, 0FFh, 0FFh, 89h, 59h, 0DCh, 0D9h, 0C9h, 89h, 5Ch, 24h, 1Ch, 0D9h, 59h
    db 0D4h, 0D9h, 59h, 0D8h, 8Bh, 58h, 80h, 0D9h, 80h, 60h, 0FFh, 0FFh, 0FFh, 89h, 5Ch, 24h
    db 1Ch, 0D9h, 80h, 70h, 0FFh, 0FFh, 0FFh, 89h, 59h, 0E8h, 0D9h, 0C9h, 0D9h, 59h, 0E0h, 0D9h
    db 59h, 0E4h, 8Bh, 58h, 0B0h, 0D9h, 40h, 90h, 89h, 5Ch, 24h, 1Ch, 0D9h, 40h, 0A0h, 89h
    db 59h, 0F4h, 0D9h, 0C9h, 0D9h, 59h, 0ECh, 0D9h, 59h, 0F0h, 75h, 87h, 3Bh, 0F5h, 7Dh, 3Fh
    db 8Dh, 14h, 76h, 8Dh, 4Ch, 97h, 08h, 8Bh, 94h, 24h, 4Ch, 01h, 00h, 00h, 8Dh, 04h
    db 76h, 0C1h, 0E0h, 04h, 8Dh, 44h, 10h, 1Ch, 8Bh, 0D5h, 2Bh, 0D6h, 8Dh, 64h, 24h, 00h
    db 0D9h, 40h, 0F0h, 8Bh, 70h, 10h, 0D9h, 00h, 89h, 31h, 0D9h, 0C9h, 83h, 0C0h, 30h, 0D9h
    db 59h, 0F8h, 83h, 0C1h, 0Ch, 4Ah, 0D9h, 59h, 0F0h, 89h, 74h, 24h, 1Ch, 75h, 0E1h, 8Bh
    db 0C5h, 8Bh, 8Ch, 24h, 2Ch, 01h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 81h, 0C4h, 28h, 01h, 00h, 00h, 0C2h, 1Ch, 00h
?d_00775760@@YAXXZ ENDP

; ghidra: FUN_00b75c70  retail @ 0x00775C70 size 640
public ?d_00775c70@@YAXXZ
?d_00775c70@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 30h, 0FDh, 04h, 01h, 50h, 8Bh, 44h
    db 24h, 10h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 8Bh, 00h, 83h, 0ECh, 30h, 85h, 0C0h
    db 57h, 8Bh, 0F9h, 0Fh, 84h, 45h, 02h, 00h, 00h, 66h, 83h, 78h, 04h, 00h, 0Fh, 84h
    db 3Ah, 02h, 00h, 00h, 8Ah, 44h, 24h, 4Ch, 84h, 0C0h, 53h, 55h, 56h, 0Fh, 84h, 17h
    db 01h, 00h, 00h, 8Bh, 77h, 4Ch, 8Bh, 47h, 50h, 8Dh, 6Fh, 4Ch, 32h, 0DBh, 3Bh, 0F0h
    db 74h, 6Dh, 8Bh, 4Ch, 24h, 50h, 8Bh, 01h, 85h, 0C0h, 8Dh, 48h, 08h, 75h, 05h, 0B9h
    db 8Bh, 38h, 07h, 01h, 8Bh, 06h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 51h, 50h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h
    db 0C0h, 75h, 2Ah, 8Ah, 44h, 24h, 54h, 8Bh, 4Ch, 24h, 60h, 84h, 0C0h, 8Bh, 44h, 24h
    db 5Ch, 0C6h, 87h, 65h, 01h, 00h, 00h, 01h, 0Fh, 94h, 0C2h, 88h, 56h, 04h, 89h, 46h
    db 08h, 89h, 4Eh, 10h, 0C7h, 46h, 14h, 00h, 00h, 80h, 3Fh, 0B3h, 01h, 8Bh, 47h, 50h
    db 83h, 0C6h, 18h, 3Bh, 0F0h, 75h, 9Bh, 84h, 0DBh, 0Fh, 85h, 0ACh, 01h, 00h, 00h, 33h
    db 0C0h, 0C6h, 87h, 65h, 01h, 00h, 00h, 01h, 89h, 44h, 24h, 10h, 8Bh, 54h, 24h, 50h
    db 52h, 8Dh, 4Ch, 24h, 14h, 89h, 44h, 24h, 4Ch, 0E8h, 42h, 1Fh, 11h, 00h, 8Ah, 44h
    db 24h, 54h, 8Bh, 54h, 24h, 5Ch, 84h, 0C0h, 0Fh, 94h, 0C1h, 84h, 0C0h, 88h, 4Ch, 24h
    db 14h, 8Bh, 4Ch, 24h, 60h, 89h, 54h, 24h, 18h, 89h, 4Ch, 24h, 20h, 0C7h, 44h, 24h
    db 24h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 1Ch, 72h, 0F9h, 7Fh, 3Fh, 75h, 08h, 0C7h
    db 44h, 24h, 1Ch, 17h, 0B7h, 0D1h, 38h, 8Bh, 45h, 04h, 3Bh, 45h, 08h, 8Dh, 54h, 24h
    db 10h, 74h, 1Ch, 52h, 50h, 0E8h, 52h, 0D7h, 8Bh, 0FFh, 8Bh, 45h, 04h, 83h, 0C4h, 08h
    db 83h, 0C0h, 18h, 89h, 45h, 04h, 8Dh, 4Ch, 24h, 10h, 0E9h, 1Fh, 01h, 00h, 00h, 6Ah
    db 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 5Ch, 51h, 52h, 50h, 8Bh, 0CDh, 0E8h, 40h, 4Ah, 8Bh
    db 0FFh, 8Dh, 4Ch, 24h, 10h, 0E9h, 04h, 01h, 00h, 00h, 8Bh, 77h, 40h, 8Bh, 47h, 44h
    db 3Bh, 0F0h, 8Ah, 5Ch, 24h, 54h, 8Dh, 6Fh, 40h, 0C6h, 44h, 24h, 58h, 00h, 74h, 67h
    db 8Bh, 44h, 24h, 50h, 8Bh, 00h, 85h, 0C0h, 8Dh, 48h, 08h, 75h, 05h, 0B9h, 8Bh, 38h
    db 07h, 01h, 8Bh, 06h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h
    db 07h, 01h, 51h, 50h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 75h
    db 20h, 8Ah, 56h, 04h, 84h, 0D2h, 0Fh, 94h, 0C0h, 3Ah, 0C3h, 74h, 0Fh, 84h, 0DBh, 0Fh
    db 94h, 0C1h, 0C6h, 87h, 64h, 01h, 00h, 00h, 01h, 88h, 4Eh, 04h, 0C6h, 44h, 24h, 58h
    db 01h, 8Bh, 47h, 44h, 83h, 0C6h, 18h, 3Bh, 0F0h, 75h, 0A5h, 8Ah, 44h, 24h, 58h, 84h
    db 0C0h, 0Fh, 85h, 94h, 00h, 00h, 00h, 0C6h, 87h, 64h, 01h, 00h, 00h, 01h, 0C7h, 44h
    db 24h, 28h, 00h, 00h, 00h, 00h, 8Bh, 54h, 24h, 50h, 52h, 8Dh, 4Ch, 24h, 2Ch, 0C7h
    db 44h, 24h, 4Ch, 01h, 00h, 00h, 00h, 0E8h, 24h, 1Eh, 11h, 00h, 8Bh, 4Dh, 08h, 84h
    db 0DBh, 0Fh, 94h, 0C0h, 88h, 44h, 24h, 2Ch, 8Bh, 45h, 04h, 3Bh, 0C1h, 0C7h, 44h, 24h
    db 30h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h
    db 38h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 00h, 00h, 8Dh, 4Ch, 24h
    db 28h, 74h, 15h, 51h, 50h, 0E8h, 42h, 0D6h, 8Bh, 0FFh, 8Bh, 45h, 04h, 83h, 0C4h, 08h
    db 83h, 0C0h, 18h, 89h, 45h, 04h, 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 5Ch
    db 52h, 51h, 50h, 8Bh, 0CDh, 0E8h, 37h, 49h, 8Bh, 0FFh, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h
    db 24h, 48h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 65h, 1Ah, 11h, 00h, 5Eh, 5Dh, 5Bh, 8Bh, 4Ch
    db 24h, 34h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 3Ch, 0C2h, 14h, 00h
?d_00775c70@@YAXXZ ENDP

; ghidra: FUN_00b75fe0  retail @ 0x00775FE0 size 62
public ?d_00775fe0@@YAXXZ
?d_00775fe0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 74h
    db 17h, 51h, 50h, 0E8h, 75h, 52h, 8Dh, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h
    db 14h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 10h
    db 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0AEh, 9Bh, 89h, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_00775fe0@@YAXXZ ENDP

; ghidra: FUN_00b76030  retail @ 0x00776030 size 62
public ?d_00776030@@YAXXZ
?d_00776030@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 74h
    db 17h, 51h, 50h, 0E8h, 0DEh, 05h, 8Ah, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h
    db 14h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 10h
    db 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 33h, 14h, 8Ch, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_00776030@@YAXXZ ENDP

; ghidra: FUN_00b764e0  retail @ 0x007764E0 size 1104
public ?d_007764e0@@YAXXZ
?d_007764e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 9Fh, 0FEh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 98h, 00h, 00h, 00h, 53h, 55h, 56h, 57h, 8Dh
    db 4Ch, 24h, 30h, 0E8h, 26h, 0EAh, 89h, 0FFh, 8Bh, 0ACh, 24h, 0B8h, 00h, 00h, 00h, 8Bh
    db 85h, 1Ch, 04h, 00h, 00h, 33h, 0DBh, 50h, 8Bh, 0CDh, 89h, 9Ch, 24h, 0B4h, 00h, 00h
    db 00h, 88h, 5Ch, 24h, 6Ch, 0E8h, 96h, 0A4h, 0Dh, 00h, 3Bh, 0C3h, 0Fh, 84h, 4Dh, 01h
    db 00h, 00h, 0BFh, 20h, 5Ch, 11h, 01h, 8Bh, 0F0h, 0B9h, 06h, 00h, 00h, 00h, 33h, 0D2h
    db 0F3h, 0A6h, 75h, 28h, 8Bh, 85h, 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CDh, 0E8h, 6Eh, 0A4h
    db 0Dh, 00h, 3Bh, 0C3h, 0Fh, 84h, 0Fh, 01h, 00h, 00h, 50h, 0E8h, 0C0h, 0C0h, 0Dh, 00h
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 34h, 0E9h, 0FDh, 00h, 00h, 00h, 0BFh, 0E8h, 41h, 12h
    db 01h, 8Bh, 0F0h, 0B9h, 0Ah, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 28h, 8Bh, 85h
    db 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CDh, 0E8h, 34h, 0A4h, 0Dh, 00h, 3Bh, 0C3h, 0Fh, 84h
    db 0D5h, 00h, 00h, 00h, 50h, 0E8h, 86h, 0C0h, 0Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 30h, 0E9h, 0C3h, 00h, 00h, 00h, 0BFh, 0DCh, 41h, 12h, 01h, 8Bh, 0F0h, 0B9h, 0Ah, 00h
    db 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 28h, 8Bh, 85h, 1Ch, 04h, 00h, 00h, 50h, 8Bh
    db 0CDh, 0E8h, 0FAh, 0A3h, 0Dh, 00h, 3Bh, 0C3h, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 50h, 0E8h
    db 4Ch, 0C0h, 0Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 38h, 0E9h, 89h, 00h, 00h, 00h
    db 0BFh, 94h, 0C0h, 09h, 01h, 8Bh, 0F0h, 0B9h, 05h, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h
    db 75h, 36h, 8Bh, 85h, 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CDh, 0E8h, 0C0h, 0A3h, 0Dh, 00h
    db 8Dh, 74h, 24h, 68h, 8Bh, 0C8h, 2Bh, 0F0h, 8Ah, 11h, 88h, 14h, 0Eh, 41h, 3Ah, 0D3h
    db 75h, 0F6h, 3Bh, 0C3h, 74h, 53h, 8Bh, 0Dh, 4Ch, 14h, 2Fh, 01h, 50h, 0E8h, 7Ch, 00h
    db 8Ah, 0FFh, 89h, 44h, 24h, 40h, 0EBh, 41h, 8Bh, 0F0h, 0BFh, 28h, 26h, 0Ah, 01h, 0B9h
    db 05h, 00h, 00h, 00h, 33h, 0C0h, 0F3h, 0A6h, 75h, 2Fh, 8Bh, 85h, 1Ch, 04h, 00h, 00h
    db 50h, 8Bh, 0CDh, 0E8h, 78h, 0A3h, 0Dh, 00h, 3Bh, 0C3h, 74h, 10h, 8Bh, 0C8h, 8Dh, 71h
    db 01h, 8Ah, 11h, 41h, 3Ah, 0D3h, 75h, 0F9h, 2Bh, 0CEh, 0EBh, 02h, 33h, 0C9h, 51h, 50h
    db 8Dh, 4Ch, 24h, 44h, 0E8h, 0B7h, 16h, 11h, 00h, 8Bh, 85h, 1Ch, 04h, 00h, 00h, 50h
    db 8Bh, 0CDh, 0E8h, 49h, 0A3h, 0Dh, 00h, 3Bh, 0C3h, 0Fh, 85h, 0B3h, 0FEh, 0FFh, 0FFh, 8Bh
    db 4Ch, 24h, 40h, 38h, 59h, 08h, 0Fh, 84h, 3Bh, 02h, 00h, 00h, 8Dh, 4Ch, 24h, 1Ch
    db 0E8h, 99h, 0E8h, 89h, 0FFh, 89h, 5Ch, 24h, 2Ch, 8Bh, 54h, 24h, 34h, 8Dh, 44h, 24h
    db 3Ch, 50h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 84h, 24h, 0B4h, 00h, 00h, 00h, 01h, 89h, 54h
    db 24h, 24h, 0E8h, 0D9h, 15h, 11h, 00h, 8Bh, 4Ch, 24h, 30h, 8Bh, 54h, 24h, 38h, 89h
    db 4Ch, 24h, 1Ch, 8Dh, 44h, 24h, 68h, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0Dh, 4Ch
    db 14h, 2Fh, 01h, 89h, 54h, 24h, 2Ch, 0E8h, 0DAh, 0CDh, 8Ah, 0FFh, 8Bh, 0F0h, 8Dh, 54h
    db 24h, 2Ch, 3Bh, 0D6h, 0C6h, 84h, 24h, 0B0h, 00h, 00h, 00h, 02h, 74h, 2Dh, 8Bh, 06h
    db 3Bh, 0C3h, 74h, 03h, 0FFh, 40h, 28h, 8Bh, 44h, 24h, 2Ch, 3Bh, 0C3h, 74h, 16h, 8Bh
    db 50h, 28h, 8Dh, 48h, 24h, 4Ah, 8Bh, 0C2h, 3Bh, 0C3h, 89h, 51h, 04h, 7Fh, 06h, 8Bh
    db 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 0Eh, 89h, 4Ch, 24h, 2Ch, 8Bh, 4Ch, 24h, 18h, 3Bh
    db 0CBh, 0C6h, 84h, 24h, 0B0h, 00h, 00h, 00h, 01h, 74h, 16h, 8Bh, 51h, 28h, 83h, 0C1h
    db 24h, 4Ah, 8Bh, 0C2h, 3Bh, 0C3h, 89h, 51h, 04h, 7Fh, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh
    db 12h, 8Bh, 44h, 24h, 2Ch, 83h, 0C0h, 04h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 72h, 0D7h
    db 8Bh, 0FFh, 8Bh, 54h, 24h, 14h, 8Bh, 0Ah, 3Bh, 0CAh, 0C6h, 84h, 24h, 0B0h, 00h, 00h
    db 00h, 03h, 89h, 4Ch, 24h, 18h, 0Fh, 84h, 0A5h, 00h, 00h, 00h, 8Bh, 0ACh, 24h, 0C4h
    db 00h, 00h, 00h, 0EBh, 0Bh, 8Bh, 4Ch, 24h, 18h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 41h, 08h, 83h, 78h, 04h, 09h, 75h, 7Ah, 89h, 5Ch, 24h, 44h, 88h, 5Ch, 24h
    db 48h, 89h, 5Ch, 24h, 4Ch, 89h, 5Ch, 24h, 50h, 89h, 5Ch, 24h, 54h, 89h, 5Ch, 24h
    db 58h, 89h, 5Ch, 24h, 5Ch, 89h, 5Ch, 24h, 60h, 88h, 5Ch, 24h, 64h, 8Dh, 4Ch, 24h
    db 44h, 51h, 50h, 0C6h, 84h, 24h, 0B8h, 00h, 00h, 00h, 04h, 0E8h, 0C7h, 11h, 89h, 0FFh
    db 8Bh, 7Dh, 00h, 6Ah, 2Ch, 0E8h, 76h, 7Dh, 0Bh, 00h, 8Bh, 0F0h, 8Dh, 54h, 24h, 50h
    db 52h, 8Dh, 46h, 08h, 50h, 0E8h, 4Ah, 1Dh, 8Bh, 0FFh, 8Bh, 47h, 04h, 89h, 3Eh, 89h
    db 46h, 04h, 89h, 30h, 83h, 0C4h, 14h, 8Dh, 4Ch, 24h, 44h, 89h, 77h, 04h, 0C6h, 84h
    db 24h, 0B0h, 00h, 00h, 00h, 03h, 0E8h, 45h, 11h, 11h, 00h, 8Bh, 54h, 24h, 14h, 8Bh
    db 4Ch, 24h, 18h, 8Bh, 09h, 3Bh, 0CAh, 89h, 4Ch, 24h, 18h, 0Fh, 85h, 64h, 0FFh, 0FFh
    db 0FFh, 8Bh, 0B4h, 24h, 0C0h, 00h, 00h, 00h, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 3Bh, 0C1h
    db 8Dh, 4Ch, 24h, 1Ch, 74h, 15h, 51h, 50h, 0E8h, 0F9h, 0FDh, 89h, 0FFh, 8Bh, 46h, 04h
    db 83h, 0C4h, 08h, 83h, 0C0h, 14h, 89h, 46h, 04h, 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh
    db 54h, 24h, 1Bh, 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 50h, 0Ch, 8Ch, 0FFh, 8Bh, 44h, 24h
    db 14h, 8Bh, 30h, 3Bh, 0F0h, 0C6h, 84h, 24h, 0B0h, 00h, 00h, 00h, 01h, 74h, 18h, 90h
    db 8Bh, 0C6h, 8Bh, 36h, 6Ah, 0Ch, 50h, 0E8h, 84h, 7Dh, 0Bh, 00h, 8Bh, 44h, 24h, 1Ch
    db 83h, 0C4h, 08h, 3Bh, 0F0h, 75h, 0E9h, 89h, 00h, 8Bh, 44h, 24h, 14h, 89h, 40h, 04h
    db 8Bh, 54h, 24h, 14h, 6Ah, 0Ch, 52h, 0E8h, 64h, 7Dh, 0Bh, 00h, 83h, 0C4h, 08h, 8Bh
    db 4Ch, 24h, 2Ch, 3Bh, 0CBh, 0C6h, 84h, 24h, 0B0h, 00h, 00h, 00h, 05h, 74h, 16h, 8Bh
    db 51h, 28h, 83h, 0C1h, 24h, 4Ah, 8Bh, 0C2h, 3Bh, 0C3h, 89h, 51h, 04h, 7Fh, 06h, 8Bh
    db 01h, 6Ah, 01h, 0FFh, 10h, 8Dh, 4Ch, 24h, 28h, 88h, 9Ch, 24h, 0B0h, 00h, 00h, 00h
    db 0E8h, 7Bh, 10h, 11h, 00h, 0EBh, 3Ch, 8Bh, 0B4h, 24h, 0BCh, 00h, 00h, 00h, 8Bh, 4Eh
    db 08h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Dh, 4Ch, 24h, 30h, 74h, 15h, 51h, 50h, 0E8h, 8Ah
    db 49h, 8Dh, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h, 14h, 89h, 46h, 04h, 0EBh
    db 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 1Bh, 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0C5h
    db 92h, 89h, 0FFh, 8Dh, 4Ch, 24h, 3Ch, 0C7h, 84h, 24h, 0B0h, 00h, 00h, 00h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 29h, 10h, 11h, 00h, 8Bh, 8Ch, 24h, 0A8h, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 81h, 0C4h, 0A4h, 00h, 00h, 00h, 0C3h
?d_007764e0@@YAXXZ ENDP

; ghidra: FUN_00b77b50  retail @ 0x00777B50 size 350
_TEXT ENDS
_TEXT$d00b77b50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B77B50 size 350
public ?d_00777b50@@YAXXZ
?d_00777b50@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va0104FF68
    db 050h, 0A1h
    dd ?Rva012ED5AC@@3PAVOptionPreferences@@A
    db 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 020h, 085h, 0C0h, 053h, 08Bh, 0D9h, 074h
    db 00Dh, 083h, 0B8h, 0C4h, 016h, 000h, 000h, 002h, 00Fh, 08Eh, 01Bh, 001h, 000h, 000h, 056h, 08Bh
    db 074h, 024h, 038h, 085h, 0F6h, 00Fh, 084h, 00Dh, 001h, 000h, 000h, 057h, 08Bh, 07Ch, 024h, 040h
    db 085h, 0FFh, 00Fh, 084h, 0FFh, 000h, 000h, 000h, 08Bh, 043h, 034h, 085h, 0C0h, 00Fh, 084h, 0F4h
    db 000h, 000h, 000h, 08Bh, 0C8h, 08Bh, 001h, 057h, 0FFh, 090h, 0C4h, 000h, 000h, 000h, 085h, 0C0h
    db 00Fh, 084h, 0E1h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 010h
    call ?j_0004048a@@YAXXZ
    db 089h, 074h, 024h, 00Ch, 08Bh, 056h, 004h, 042h, 057h, 08Dh, 04Ch, 024h, 014h, 0C7h, 044h, 024h
    db 038h, 000h, 000h, 000h, 000h, 089h, 056h, 004h
    call ?j_00013746@@YAXXZ
    db 08Ah, 044h, 024h, 044h, 084h, 0C0h, 074h, 062h, 068h, 021h, 022h, 000h, 000h, 068h
    dd ?g_bfmeTag1028@@3PADA
    db 06Ah, 003h, 06Ah, 0FDh
    call ?j_00027aac@@YAXXZ
    db 068h, 022h, 022h, 000h, 000h, 089h, 044h, 024h, 058h, 0DBh, 044h, 024h, 058h, 068h
    dd ?g_bfmeTag1028@@3PADA
    db 06Ah, 003h, 06Ah, 0FDh, 0D9h, 05Ch, 024h, 03Ch
    call ?j_00027aac@@YAXXZ
    db 068h, 023h, 022h, 000h, 000h, 089h, 044h, 024h, 068h, 0DBh, 044h, 024h, 068h, 068h
    dd ?g_bfmeTag1028@@3PADA
    db 06Ah, 003h, 06Ah, 0FDh, 0D9h, 05Ch, 024h, 050h
    call ?j_00027aac@@YAXXZ
    db 089h, 044h, 024h, 074h, 0DBh, 044h, 024h, 074h, 083h, 0C4h, 030h, 0D9h, 05Ch, 024h, 024h, 0EBh
    db 018h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h
    db 000h, 0C7h, 044h, 024h, 024h, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 048h, 08Bh, 044h, 024h
    db 00Ch, 089h, 04Ch, 024h, 028h, 08Bh, 00Dh
    dd ?Rva012F8058@@3PAVRva00712F60@@A
    db 08Bh, 011h, 050h, 0FFh, 052h, 008h, 08Dh, 04Ch, 024h, 00Ch, 051h, 08Dh, 08Bh, 030h, 001h, 000h
    db 000h
    call ?j_0000dd50@@YAXXZ
    db 08Dh, 04Ch, 024h, 00Ch, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_0004429c@@YAXXZ
    db 05Fh, 05Eh, 08Bh, 04Ch, 024h, 024h, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 02Ch, 0C2h, 010h, 000h
?d_00777b50@@YAXXZ ENDP
_TEXT$d00b77b50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b77d10  retail @ 0x00777D10 size 238
_TEXT ENDS
_TEXT$d00b77d10 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B77D10 size 238
public ?d_00777d10@@YAXXZ
?d_00777d10@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va0104FF88
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 053h, 055h, 056h, 057h, 08Bh, 0E9h, 08Bh, 085h
    db 030h, 001h, 000h, 000h, 08Bh, 08Dh, 034h, 001h, 000h, 000h, 03Bh, 0C1h, 08Dh, 0B5h, 030h, 001h
    db 000h, 000h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 00Fh, 084h, 081h, 000h, 000h, 000h
    db 08Bh, 044h, 024h, 020h, 085h, 0C0h, 00Fh, 084h, 09Bh, 000h, 000h, 000h, 083h, 0C0h, 008h, 085h
    db 0C0h, 074h, 06Eh, 050h
    call ?Create_Render_Obj@@YAPAVRenderObjClass@@PBD@Z
    db 08Bh, 0F8h, 083h, 0C4h, 004h, 085h, 0FFh, 074h, 05Fh, 08Bh, 016h, 08Bh, 04Eh, 004h, 02Bh, 0CAh
    db 0B8h, 0ABh, 0AAh, 0AAh, 02Ah, 0F7h, 0E9h, 0D1h, 0FAh, 08Bh, 0CAh, 068h, 076h, 022h, 000h, 000h
    db 0C1h, 0E9h, 01Fh, 068h
    dd ?g_bfmeTag1028@@3PADA
    db 08Dh, 054h, 00Ah, 0FFh, 052h, 06Ah, 000h
    call ?j_00027aac@@YAXXZ
    db 08Bh, 00Eh, 08Bh, 054h, 024h, 034h, 08Dh, 004h, 040h, 08Dh, 01Ch, 081h, 08Bh, 04Ch, 024h, 038h
    db 08Bh, 003h, 083h, 0C4h, 010h, 051h, 052h, 050h, 057h, 08Dh, 04Dh, 0F4h
    call ?j_00012d32@@YAXXZ
    db 053h, 08Bh, 0CEh
    call ?j_00002c43@@YAXXZ
    db 0FFh, 04Fh, 004h, 075h, 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h, 08Dh, 04Ch, 024h, 020h, 0C7h
    db 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 010h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 00Ch, 0C2h, 00Ch, 000h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 0E9h, 062h, 0FFh, 0FFh, 0FFh
?d_00777d10@@YAXXZ ENDP
_TEXT$d00b77d10 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b77e40  retail @ 0x00777E40 size 62
public ?d_00777e40@@YAXXZ
?d_00777e40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 3Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 74h
    db 17h, 51h, 50h, 0E8h, 5Bh, 0AEh, 8Bh, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h
    db 2Ch, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 10h
    db 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0E4h, 71h, 8Bh, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_00777e40@@YAXXZ ENDP

; ghidra: FUN_00b77ee0  retail @ 0x00777EE0 size 76
public ?d_00777ee0@@YAXXZ
?d_00777ee0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 04h, 6Ah, 00h, 8Dh
    db 4Ch, 24h, 18h, 51h, 52h, 50h, 8Bh, 44h, 24h, 28h, 50h, 0E8h, 0E5h, 0CFh, 8Ch, 0FFh
    db 8Bh, 6Fh, 04h, 8Bh, 0D8h, 83h, 0C4h, 14h, 3Bh, 0DDh, 8Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0A3h, 29h, 8Bh, 0FFh, 83h, 0C6h, 2Ch, 3Bh, 0F5h, 75h, 0F2h, 8Bh, 44h
    db 24h, 14h, 89h, 5Fh, 04h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 08h, 00h
?d_00777ee0@@YAXXZ ENDP

; ghidra: FUN_00b781c0  retail @ 0x007781C0 size 779
public ?d_007781c0@@YAXXZ
?d_007781c0@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 8Bh, 54h, 24h, 10h, 68h, 02h, 00h, 05h
    db 01h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 8Bh, 42h, 04h, 83h, 0ECh, 2Ch, 53h
    db 55h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0Ah, 50h, 51h, 8Bh, 0CAh, 0E8h, 40h, 0E5h, 88h, 0FFh
    db 8Bh, 54h, 24h, 50h, 8Bh, 42h, 04h, 8Bh, 0Ah, 50h, 51h, 8Bh, 0CAh, 0E8h, 2Eh, 0E5h
    db 88h, 0FFh, 8Bh, 5Ch, 24h, 58h, 8Bh, 43h, 04h, 3Bh, 0C0h, 8Bh, 0Bh, 75h, 04h, 8Bh
    db 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h
    db 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 43h, 04h, 8Bh, 46h, 04h, 8Ah, 88h, 0B0h, 00h, 00h
    db 00h, 84h, 0C9h, 8Bh, 76h, 08h, 89h, 44h, 24h, 20h, 74h, 0Bh, 8Bh, 0B6h, 0FCh, 00h
    db 00h, 00h, 8Bh, 6Eh, 78h, 0EBh, 06h, 8Bh, 0AEh, 0F0h, 02h, 00h, 00h, 8Bh, 58h, 78h
    db 3Bh, 58h, 7Ch, 89h, 6Ch, 24h, 14h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h
    db 5Ch, 24h, 18h, 0Fh, 84h, 4Dh, 02h, 00h, 00h, 8Bh, 74h, 24h, 4Ch, 4Eh, 89h, 74h
    db 24h, 4Ch, 0EBh, 04h, 8Bh, 74h, 24h, 4Ch, 8Bh, 43h, 08h, 8Bh, 7Bh, 04h, 8Bh, 0C8h
    db 2Bh, 0CFh, 0C1h, 0F9h, 02h, 85h, 0F6h, 8Dh, 51h, 0FFh, 7Dh, 04h, 33h, 0F6h, 0EBh, 06h
    db 3Bh, 0F2h, 7Eh, 02h, 8Bh, 0F2h, 3Bh, 0F8h, 0Fh, 84h, 0F9h, 01h, 00h, 00h, 8Bh, 44h
    db 24h, 10h, 8Bh, 0DDh, 83h, 0E3h, 0Fh, 40h, 0Fh, 0AFh, 0D8h, 0B8h, 67h, 66h, 66h, 66h
    db 0F7h, 0EDh, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 03h, 44h, 24h, 10h, 89h
    db 44h, 24h, 1Ch, 0B8h, 56h, 55h, 55h, 55h, 0F7h, 0EDh, 8Bh, 6Ch, 24h, 14h, 8Bh, 0C2h
    db 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Bh, 54h, 24h, 1Ch, 03h, 0D3h, 03h, 0C2h, 03h, 0C5h, 33h
    db 0D2h, 0F7h, 0F1h, 85h, 0D2h, 7Dh, 04h, 33h, 0D2h, 0EBh, 06h, 3Bh, 0D6h, 7Eh, 02h, 8Bh
    db 0D6h, 8Bh, 5Ch, 24h, 18h, 8Bh, 03h, 85h, 0C0h, 8Dh, 48h, 08h, 75h, 05h, 0B9h, 8Bh
    db 38h, 07h, 01h, 8Dh, 34h, 95h, 00h, 00h, 00h, 00h, 8Bh, 04h, 3Eh, 85h, 0C0h, 74h
    db 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 51h, 50h, 0FFh, 15h, 3Ch
    db 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 0Fh, 84h, 69h, 01h, 00h, 00h, 8Bh, 43h
    db 04h, 8Bh, 04h, 06h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h
    db 07h, 01h, 8Dh, 4Ch, 24h, 54h, 51h, 50h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0C7h, 2Fh, 8Ch
    db 0FFh, 8Bh, 74h, 24h, 54h, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 0C7h, 44h, 24h, 44h, 00h
    db 00h, 00h, 00h, 74h, 23h, 89h, 44h, 24h, 1Ch, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C6h
    db 44h, 24h, 44h, 01h, 74h, 0Ch, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 0C8h, 0E8h, 8Fh, 47h
    db 8Ah, 0FFh, 83h, 46h, 04h, 0Ch, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 5Ch
    db 51h, 8Dh, 54h, 24h, 30h, 52h, 50h, 8Bh, 0CEh, 0E8h, 91h, 57h, 89h, 0FFh, 8Bh, 4Ch
    db 24h, 24h, 8Bh, 44h, 24h, 2Ch, 83h, 0CFh, 0FFh, 2Bh, 0C1h, 85h, 0C9h, 89h, 7Ch, 24h
    db 44h, 74h, 1Ch, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0F0h, 9Ah, 10h, 00h
    db 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 24h, 62h, 0Bh, 00h, 83h, 0C4h, 08h, 8Bh
    db 03h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Dh
    db 4Ch, 24h, 54h, 51h, 50h, 8Dh, 4Ch, 24h, 38h, 0E8h, 2Ah, 2Fh, 8Ch, 0FFh, 8Bh, 74h
    db 24h, 50h, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 0C7h, 44h, 24h, 44h, 02h, 00h, 00h, 00h
    db 74h, 23h, 89h, 44h, 24h, 1Ch, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C6h, 44h, 24h, 44h
    db 03h, 74h, 0Ch, 8Dh, 54h, 24h, 30h, 52h, 8Bh, 0C8h, 0E8h, 0F2h, 46h, 8Ah, 0FFh, 83h
    db 46h, 04h, 0Ch, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 5Ch, 51h, 8Dh, 54h
    db 24h, 3Ch, 52h, 50h, 8Bh, 0CEh, 0E8h, 0F4h, 56h, 89h, 0FFh, 8Bh, 4Ch, 24h, 30h, 8Bh
    db 44h, 24h, 38h, 2Bh, 0C1h, 85h, 0C9h, 89h, 7Ch, 24h, 44h, 74h, 1Ch, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Bh, 51h, 0E8h, 56h, 9Ah, 10h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h
    db 51h, 0E8h, 8Ah, 61h, 0Bh, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 58h, 8Bh, 41h, 04h
    db 3Bh, 41h, 08h, 74h, 0Fh, 85h, 0C0h, 74h, 05h, 8Bh, 53h, 10h, 89h, 10h, 83h, 41h
    db 04h, 04h, 0EBh, 13h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 5Ch, 52h, 8Dh, 53h, 10h
    db 52h, 50h, 0E8h, 0DEh, 2Bh, 8Ch, 0FFh, 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h, 20h, 8Bh
    db 48h, 7Ch, 83h, 0C3h, 14h, 42h, 3Bh, 0D9h, 89h, 5Ch, 24h, 18h, 89h, 54h, 24h, 10h
    db 0Fh, 85h, 0BEh, 0FDh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 3Ch, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 38h, 0C2h, 10h, 00h
?d_007781c0@@YAXXZ ENDP

; ghidra: FUN_00b79e60  retail @ 0x00779E60 size 98
public ?d_00779e60@@YAXXZ
?d_00779e60@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 2Ch, 0B6h, 8Ch, 0FFh, 83h, 0C6h, 14h, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 3Ah, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 67h, 66h, 66h, 66h, 0F7h, 0E9h
    db 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 80h, 0C1h, 0E0h, 02h
    db 3Dh, 80h, 00h, 00h, 00h, 76h, 0Dh, 56h, 0E8h, 03h, 80h, 10h, 00h, 83h, 0C4h, 04h
    db 5Fh, 5Eh, 5Bh, 0C3h, 50h, 56h, 0E8h, 35h, 47h, 0Bh, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh
    db 5Bh, 0C3h
?d_00779e60@@YAXXZ ENDP

; ghidra: FUN_00b79f10  retail @ 0x00779F10 size 2480
_TEXT ENDS
_TEXT$d00b79f10 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B79F10 size 2480
public ?d_00779f10@@YAXXZ
?d_00779f10@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va010501D4
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 070h, 001h, 000h, 000h, 053h, 055h
    db 08Bh, 0D9h, 08Ah, 043h, 02Ch, 084h, 0C0h, 056h, 057h, 00Fh, 084h, 059h, 009h, 000h, 000h, 08Bh
    db 043h, 008h, 085h, 0C0h, 089h, 044h, 024h, 034h, 00Fh, 084h, 05Ch, 009h, 000h, 000h, 08Bh, 04Bh
    db 014h, 085h, 0C9h, 00Fh, 084h, 039h, 009h, 000h, 000h, 0F6h, 080h, 010h, 001h, 000h, 000h, 008h
    db 00Fh, 085h, 02Ch, 009h, 000h, 000h, 06Ah, 02Ch
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 01Ch, 089h, 000h, 089h, 040h, 004h, 089h, 084h, 024h, 04Ch
    db 001h, 000h, 000h, 08Bh, 043h, 014h, 08Bh, 048h, 050h, 08Bh, 039h, 03Bh, 0F9h, 0C7h, 084h, 024h
    db 088h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 074h, 039h, 06Ah, 02Ch, 08Dh, 06Fh, 008h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 056h, 008h, 055h, 052h
    call ?j_00028524@@YAXXZ
    db 08Bh, 04Ch, 024h, 028h, 08Bh, 041h, 004h, 089h, 046h, 004h, 089h, 00Eh, 089h, 030h, 089h, 071h
    db 004h, 08Bh, 043h, 014h, 08Bh, 03Fh, 08Bh, 048h, 050h, 083h, 0C0h, 050h, 083h, 0C4h, 00Ch, 03Bh
    db 0F9h, 075h, 0C7h, 08Bh, 043h, 010h, 08Bh, 088h, 09Ch, 000h, 000h, 000h, 08Bh, 039h, 03Bh, 0F9h
    db 074h, 042h, 08Dh, 064h, 024h, 000h, 06Ah, 02Ch, 08Dh, 06Fh, 008h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 056h, 008h, 055h, 052h
    call ?j_00028524@@YAXXZ
    db 08Bh, 04Ch, 024h, 028h, 08Bh, 041h, 004h, 089h, 046h, 004h, 089h, 00Eh, 089h, 030h, 089h, 071h
    db 004h, 08Bh, 043h, 010h, 08Bh, 03Fh, 08Bh, 088h, 09Ch, 000h, 000h, 000h, 005h, 09Ch, 000h, 000h
    db 000h, 083h, 0C4h, 00Ch, 03Bh, 0F9h, 075h, 0C2h, 08Bh, 04Ch, 024h, 01Ch, 08Bh, 001h, 03Bh, 0C1h
    db 089h, 044h, 024h, 030h, 00Fh, 084h, 0EFh, 007h, 000h, 000h, 08Bh, 074h, 024h, 030h, 083h, 0C6h
    db 008h, 056h, 08Dh, 04Ch, 024h, 040h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 04Eh, 008h, 08Ah, 046h, 004h, 08Bh, 056h, 00Ch, 08Bh, 06Eh, 01Ch, 089h, 04Ch, 024h, 044h
    db 08Bh, 04Eh, 014h, 089h, 04Ch, 024h, 050h, 08Bh, 04Eh, 018h, 088h, 044h, 024h, 040h, 08Bh, 046h
    db 010h, 089h, 04Ch, 024h, 054h, 08Ah, 04Eh, 020h, 089h, 054h, 024h, 048h, 089h, 044h, 024h, 04Ch
    db 089h, 06Ch, 024h, 058h, 088h, 04Ch, 024h, 05Ch, 085h, 0D2h, 0C6h, 084h, 024h, 088h, 001h, 000h
    db 000h, 001h, 074h, 037h, 08Bh, 04Bh, 048h, 08Bh, 031h, 03Bh, 0F1h, 074h, 02Eh, 08Bh, 0FFh, 039h
    db 056h, 014h, 075h, 020h, 083h, 0F8h, 003h, 08Bh, 0F8h, 00Fh, 084h, 05Ah, 007h, 000h, 000h, 08Ah
    db 04Eh, 018h, 084h, 0C9h, 00Fh, 085h, 04Fh, 007h, 000h, 000h, 083h, 0F8h, 002h, 074h, 065h, 083h
    db 0F8h, 001h, 074h, 060h, 08Bh, 036h, 03Bh, 073h, 048h, 075h, 0D4h, 085h, 0EDh, 00Fh, 084h, 036h
    db 007h, 000h, 000h, 06Ah, 001h, 055h, 08Dh, 04Ch, 024h, 018h, 051h, 08Bh, 00Dh
    dd ?TheParticleSystemManager@@3PAVParticleSystemManager@@A
    call ?j_0000ebe7@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 0C6h, 084h, 024h, 088h, 001h, 000h, 000h, 003h, 00Fh, 084h
    db 00Fh, 007h, 000h, 000h, 08Bh, 04Ch, 024h, 044h, 085h, 0C9h, 08Bh, 06Ch, 024h, 034h, 00Fh, 084h
    db 0D4h, 000h, 000h, 000h, 039h, 08Dh, 0ECh, 002h, 000h, 000h, 00Fh, 084h, 0C8h, 000h, 000h, 000h
    db 08Dh, 04Ch, 024h, 010h
    call ?j_00013994@@YAXXZ
    db 0E9h, 0E5h, 006h, 000h, 000h, 08Bh, 056h, 008h, 08Bh, 00Dh
    dd ?TheParticleSystemManager@@3PAVParticleSystemManager@@A
    db 052h, 08Dh, 044h, 024h, 028h, 050h
    call ?j_0002a216@@YAXXZ
    db 08Bh, 04Ch, 024h, 024h, 033h, 0EDh, 03Bh, 0CDh, 0C6h, 084h, 024h, 088h, 001h, 000h, 000h, 002h
    db 074h, 009h
    call ?j_0000e525@@YAXXZ
    db 08Bh, 04Ch, 024h, 024h, 083h, 0FFh, 001h, 075h, 023h, 08Bh, 04Eh, 004h, 08Bh, 006h, 089h, 001h
    db 089h, 048h, 004h, 08Dh, 04Eh, 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 06Ah, 01Ch, 056h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 08Bh, 04Ch, 024h, 02Ch, 083h, 0C4h, 008h, 0EBh, 009h, 083h, 0FFh, 002h, 075h, 004h, 0C6h, 046h
    db 018h, 001h, 03Bh, 0CDh, 00Fh, 084h, 07Dh, 006h, 000h, 000h, 08Bh, 044h, 024h, 028h, 03Bh, 0C5h
    db 074h, 009h, 08Bh, 04Ch, 024h, 02Ch, 089h, 048h, 008h, 0EBh, 00Ah, 08Bh, 054h, 024h, 02Ch, 089h
    db 091h, 098h, 000h, 000h, 000h, 08Bh, 044h, 024h, 02Ch, 03Bh, 0C5h, 074h, 014h, 08Bh, 04Ch, 024h
    db 028h, 089h, 048h, 004h, 089h, 06Ch, 024h, 028h, 089h, 06Ch, 024h, 02Ch, 0E9h, 046h, 006h, 000h
    db 000h, 08Bh, 054h, 024h, 028h, 08Bh, 044h, 024h, 024h, 089h, 090h, 09Ch, 000h, 000h, 000h, 089h
    db 06Ch, 024h, 028h, 089h, 06Ch, 024h, 02Ch, 0E9h, 02Bh, 006h, 000h, 000h, 08Bh, 04Bh, 034h, 085h
    db 0C9h, 0C7h, 044h, 024h, 060h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 064h, 000h, 000h, 000h
    db 000h, 0C7h, 044h, 024h, 068h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 038h, 000h, 000h, 000h
    db 000h, 074h, 027h, 08Bh, 044h, 024h, 03Ch, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 011h, 050h, 0FFh, 092h, 0C4h, 000h, 000h, 000h, 08Bh, 0F8h, 08Bh, 044h, 024h, 010h, 089h
    db 07Ch, 024h, 020h, 0EBh, 00Ch, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h, 08Bh, 07Ch, 024h
    db 020h, 08Bh, 04Bh, 004h, 08Ah, 091h, 0FEh, 000h, 000h, 000h, 084h, 0D2h, 074h, 052h, 08Bh, 044h
    db 024h, 03Ch, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 04Bh, 008h, 06Ah, 001h, 08Dh, 094h, 024h, 054h, 001h, 000h, 000h, 052h, 06Ah, 000h, 06Ah
    db 000h, 050h
    call ?j_0002f766@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 0B1h, 003h, 000h, 000h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Dh, 08Ch, 024h, 050h, 001h, 000h, 000h, 051h, 08Bh, 0C8h
    call ?j_0004484b@@YAXXZ
    db 0E9h, 090h, 003h, 000h, 000h, 08Ah, 04Ch, 024h, 040h, 084h, 0C9h, 00Fh, 084h, 0DDh, 000h, 000h
    db 000h, 085h, 0FFh, 00Fh, 084h, 0ACh, 000h, 000h, 000h, 08Bh, 04Bh, 034h, 085h, 0C9h, 00Fh, 084h
    db 0A1h, 000h, 000h, 000h, 08Bh, 011h, 057h, 0FFh, 092h, 0C8h, 000h, 000h, 000h, 08Bh, 008h, 089h
    db 08Ch, 024h, 0ECh, 000h, 000h, 000h, 08Bh, 050h, 004h, 089h, 094h, 024h, 0F0h, 000h, 000h, 000h
    db 08Bh, 048h, 008h, 089h, 08Ch, 024h, 0F4h, 000h, 000h, 000h, 08Bh, 050h, 00Ch, 089h, 094h, 024h
    db 0F8h, 000h, 000h, 000h, 08Bh, 048h, 010h, 089h, 08Ch, 024h, 0FCh, 000h, 000h, 000h, 08Bh, 050h
    db 014h, 089h, 094h, 024h, 000h, 001h, 000h, 000h, 08Bh, 048h, 018h, 089h, 08Ch, 024h, 004h, 001h
    db 000h, 000h, 08Bh, 050h, 01Ch, 089h, 094h, 024h, 008h, 001h, 000h, 000h, 08Bh, 048h, 020h, 089h
    db 08Ch, 024h, 00Ch, 001h, 000h, 000h, 08Bh, 050h, 024h, 089h, 094h, 024h, 010h, 001h, 000h, 000h
    db 08Bh, 048h, 028h, 089h, 08Ch, 024h, 014h, 001h, 000h, 000h, 08Bh, 050h, 02Ch, 08Bh, 044h, 024h
    db 010h, 085h, 0C0h, 089h, 094h, 024h, 018h, 001h, 000h, 000h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Dh, 08Ch, 024h, 0ECh, 000h, 000h, 000h, 051h, 08Bh, 0C8h
    call ?j_0004484b@@YAXXZ
    db 0E9h, 0D0h, 002h, 000h, 000h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Dh, 054h, 024h, 060h, 052h, 08Bh, 0C8h
    call ?j_00021832@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 06Ah, 000h, 0E9h, 0A0h, 002h, 000h, 000h, 085h, 0FFh, 00Fh, 084h, 071h, 002h, 000h, 000h, 08Bh
    db 073h, 034h, 085h, 0F6h, 00Fh, 084h, 066h, 002h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h
    db 050h, 08Bh, 04Eh, 018h, 089h, 08Ch, 024h, 01Ch, 001h, 000h, 000h, 08Bh, 056h, 01Ch, 089h, 094h
    db 024h, 020h, 001h, 000h, 000h, 08Bh, 046h, 020h, 089h, 084h, 024h, 024h, 001h, 000h, 000h, 08Bh
    db 04Eh, 024h, 089h, 08Ch, 024h, 028h, 001h, 000h, 000h, 08Bh, 056h, 028h, 089h, 094h, 024h, 02Ch
    db 001h, 000h, 000h, 08Bh, 046h, 02Ch, 089h, 084h, 024h, 030h, 001h, 000h, 000h, 08Bh, 04Eh, 030h
    db 089h, 08Ch, 024h, 034h, 001h, 000h, 000h, 08Bh, 056h, 034h, 089h, 094h, 024h, 038h, 001h, 000h
    db 000h, 08Bh, 046h, 038h, 089h, 084h, 024h, 03Ch, 001h, 000h, 000h, 08Bh, 04Eh, 03Ch, 089h, 08Ch
    db 024h, 040h, 001h, 000h, 000h, 08Bh, 056h, 040h, 08Bh, 04Bh, 008h, 089h, 094h, 024h, 044h, 001h
    db 000h, 000h, 08Bh, 046h, 044h, 089h, 084h, 024h, 048h, 001h, 000h, 000h, 0C7h, 044h, 024h, 06Ch
    db 000h, 000h, 080h, 03Fh, 0C7h, 044h, 024h, 070h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 074h
    db 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 078h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 07Ch
    db 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 000h, 000h, 080h, 03Fh, 0C7h
    db 084h, 024h, 084h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 088h, 000h, 000h
    db 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 08Ch, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    db 0C7h, 084h, 024h, 090h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 094h, 000h
    db 000h, 000h, 000h, 000h, 080h, 03Fh, 0C7h, 084h, 024h, 098h, 000h, 000h, 000h, 000h, 000h, 000h
    db 000h
    call ?j_0003939c@@YAXXZ
    db 0D9h, 044h, 024h, 06Ch, 0D8h, 0C9h, 08Bh, 04Bh, 034h, 08Dh, 044h, 024h, 06Ch, 050h, 0D9h, 05Ch
    db 024h, 070h, 0D9h, 084h, 024h, 080h, 000h, 000h, 000h, 0D8h, 0C9h, 0D9h, 09Ch, 024h, 080h, 000h
    db 000h, 000h, 0D9h, 084h, 024h, 090h, 000h, 000h, 000h, 0D8h, 0C9h, 0D9h, 09Ch, 024h, 090h, 000h
    db 000h, 000h, 0D9h, 044h, 024h, 074h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 074h, 0D9h, 084h, 024h, 084h
    db 000h, 000h, 000h, 0D8h, 0C9h, 0D9h, 09Ch, 024h, 084h, 000h, 000h, 000h, 0D9h, 084h, 024h, 094h
    db 000h, 000h, 000h, 0D8h, 0C9h, 0D9h, 09Ch, 024h, 094h, 000h, 000h, 000h, 0D9h, 044h, 024h, 078h
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 078h, 0D9h, 084h, 024h, 088h, 000h, 000h, 000h, 0D8h, 0C9h, 0D9h
    db 09Ch, 024h, 088h, 000h, 000h, 000h, 0D8h, 08Ch, 024h, 098h, 000h, 000h, 000h, 0D9h, 09Ch, 024h
    db 098h, 000h, 000h, 000h, 08Bh, 011h, 0FFh, 052h, 054h, 08Bh, 04Bh, 034h, 08Bh, 011h, 057h, 0FFh
    db 092h, 0C8h, 000h, 000h, 000h, 08Bh, 008h, 089h, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 08Bh, 050h
    db 004h, 089h, 094h, 024h, 0C0h, 000h, 000h, 000h, 08Bh, 048h, 008h, 089h, 08Ch, 024h, 0C4h, 000h
    db 000h, 000h, 0D9h, 040h, 00Ch, 0D9h, 094h, 024h, 0C8h, 000h, 000h, 000h, 08Bh, 050h, 010h, 089h
    db 094h, 024h, 0CCh, 000h, 000h, 000h, 08Bh, 048h, 014h, 089h, 08Ch, 024h, 0D0h, 000h, 000h, 000h
    db 08Bh, 050h, 018h, 089h, 094h, 024h, 0D4h, 000h, 000h, 000h, 0D9h, 040h, 01Ch, 0D9h, 094h, 024h
    db 0D8h, 000h, 000h, 000h, 08Bh, 048h, 020h, 089h, 08Ch, 024h, 0DCh, 000h, 000h, 000h, 0D9h, 0C9h
    db 08Bh, 050h, 024h, 0D9h, 09Ch, 024h, 09Ch, 000h, 000h, 000h, 089h, 094h, 024h, 0E0h, 000h, 000h
    db 000h, 08Bh, 048h, 028h, 0D9h, 09Ch, 024h, 0A0h, 000h, 000h, 000h, 089h, 08Ch, 024h, 0E4h, 000h
    db 000h, 000h, 08Bh, 050h, 02Ch, 08Bh, 0C2h, 08Dh, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 089h, 094h
    db 024h, 0E8h, 000h, 000h, 000h, 089h, 084h, 024h, 0A4h, 000h, 000h, 000h
    call ?Get_Z_Rotation@Matrix3D@@QBEMXZ
    db 0D9h, 05Ch, 024h, 038h, 08Bh, 04Bh, 034h, 08Bh, 011h, 08Dh, 084h, 024h, 01Ch, 001h, 000h, 000h
    db 050h, 0FFh, 052h, 054h, 08Bh, 084h, 024h, 0A4h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 09Ch, 000h
    db 000h, 000h, 08Bh, 094h, 024h, 0A0h, 000h, 000h, 000h, 089h, 044h, 024h, 068h, 08Bh, 044h, 024h
    db 010h, 089h, 04Ch, 024h, 060h, 089h, 054h, 024h, 064h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Dh, 04Ch, 024h, 060h, 051h, 08Bh, 0C8h
    call ?j_00021832@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 054h, 024h, 038h, 052h, 08Bh, 0C8h
    call ?j_0004697a@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 055h, 08Bh, 0C8h
    call ?j_00012319@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 06Ah, 000h, 08Bh, 0C8h
    call ?j_000423b1@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Ah, 04Ch, 024h, 040h, 088h, 088h, 0ABh, 001h, 000h, 000h, 08Bh, 0B5h, 0FCh, 000h, 000h, 000h
    db 085h, 0F6h, 074h, 032h, 08Ah, 044h, 024h, 05Ch, 084h, 0C0h, 074h, 02Ah, 08Bh, 07Ch, 024h, 010h
    db 085h, 0FFh, 075h, 007h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 0CEh
    call ?j_00009ca0@@YAXXZ
    db 08Bh, 08Fh, 0B0h, 001h, 000h, 000h, 085h, 0C9h, 074h, 006h, 08Bh, 011h, 050h, 0FFh, 052h, 010h
    db 08Bh, 07Ch, 024h, 020h, 08Bh, 04Ch, 024h, 034h
    call ?j_00012e3b@@YAXXZ
    db 084h, 0C0h, 075h, 007h, 08Ah, 043h, 02Dh, 084h, 0C0h, 074h, 018h, 08Bh, 044h, 024h, 010h, 033h
    db 0EDh, 03Bh, 0C5h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 0C8h
    call ?j_00013075@@YAXXZ
    db 0EBh, 002h, 033h, 0EDh, 089h, 0ACh, 024h, 0B0h, 000h, 000h, 000h, 08Bh, 044h, 024h, 010h, 03Bh
    db 0C5h, 0C6h, 084h, 024h, 088h, 001h, 000h, 000h, 004h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 080h, 0ACh, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 03Ch, 051h, 08Dh, 08Ch, 024h, 0B4h, 000h
    db 000h, 000h, 089h, 084h, 024h, 0ACh, 000h, 000h, 000h, 089h, 0BCh, 024h, 0B0h, 000h, 000h, 000h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 039h, 06Ch, 024h, 054h, 08Bh, 054h, 024h, 048h, 089h, 094h, 024h, 0B4h, 000h, 000h, 000h, 0C6h
    db 084h, 024h, 0B8h, 000h, 000h, 000h, 000h, 074h, 020h, 08Bh, 044h, 024h, 010h, 03Bh, 0C5h, 075h
    db 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 080h, 0ACh, 000h, 000h, 000h, 050h, 08Bh, 044h, 024h, 054h, 050h, 0FFh, 054h, 024h, 05Ch
    db 083h, 0C4h, 008h, 08Bh, 044h, 024h, 010h, 03Bh, 0C5h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Ah, 088h, 0ABh, 001h, 000h, 000h, 084h, 0C9h, 06Ah, 01Ch, 074h, 01Ah, 08Bh, 04Bh, 048h, 08Bh
    db 039h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 094h, 024h, 0ACh, 000h, 000h, 000h, 052h, 08Dh, 046h, 008h, 050h, 0EBh, 016h
    db 08Bh, 07Bh, 048h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 08Ch, 024h, 0ACh, 000h, 000h, 000h, 051h, 08Dh, 056h, 008h, 052h
    call ?j_00040ae3@@YAXXZ
    db 08Bh, 047h, 004h, 089h, 046h, 004h, 089h, 03Eh, 089h, 030h, 083h, 0C4h, 00Ch, 08Dh, 08Ch, 024h
    db 0B0h, 000h, 000h, 000h, 089h, 077h, 004h, 0C6h, 084h, 024h, 088h, 001h, 000h, 000h, 003h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 010h, 03Bh, 0CDh, 074h, 042h, 08Bh, 044h, 024h, 014h, 03Bh, 0C5h, 074h, 009h
    db 08Bh, 04Ch, 024h, 018h, 089h, 048h, 008h, 0EBh, 00Ah, 08Bh, 054h, 024h, 018h, 089h, 091h, 098h
    db 000h, 000h, 000h, 08Bh, 044h, 024h, 018h, 03Bh, 0C5h, 074h, 009h, 08Bh, 04Ch, 024h, 014h, 089h
    db 048h, 004h, 0EBh, 00Eh, 08Bh, 054h, 024h, 014h, 08Bh, 044h, 024h, 010h, 089h, 090h, 09Ch, 000h
    db 000h, 000h, 089h, 06Ch, 024h, 014h, 089h, 06Ch, 024h, 018h, 08Dh, 04Ch, 024h, 03Ch, 0C6h, 084h
    db 024h, 088h, 001h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 030h, 08Bh, 001h, 03Bh, 044h, 024h, 01Ch, 089h, 044h, 024h, 030h, 00Fh, 085h
    db 011h, 0F8h, 0FFh, 0FFh, 08Bh, 06Ch, 024h, 01Ch, 08Bh, 075h, 000h, 03Bh, 0F5h, 074h, 021h, 08Dh
    db 09Bh, 000h, 000h, 000h, 000h, 08Bh, 0FEh, 08Bh, 036h, 08Dh, 04Fh, 008h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 06Ah, 02Ch, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 03Bh, 0F5h, 075h, 0E5h, 089h, 06Dh, 000h, 089h, 06Dh, 004h, 08Bh, 075h, 000h
    db 03Bh, 0F5h, 0C7h, 084h, 024h, 088h, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 074h, 01Bh, 08Bh
    db 0FEh, 08Bh, 036h, 08Dh, 04Fh, 008h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 06Ah, 02Ch, 057h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 03Bh, 0F5h, 075h, 0E5h, 06Ah, 02Ch, 089h, 06Dh, 000h, 055h, 089h, 06Dh, 004h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 0C6h, 043h, 02Ch, 000h, 0EBh, 012h, 08Bh, 053h, 00Ch, 08Dh, 04Bh, 00Ch, 06Ah
    db 001h, 0FFh, 052h, 068h, 08Bh, 0CBh
    call ?j_0000cb80@@YAXXZ
    db 08Bh, 08Ch, 024h, 080h, 001h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 07Ch, 001h, 000h, 000h, 0C3h
?d_00779f10@@YAXXZ ENDP
_TEXT$d00b79f10 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b7aea0  retail @ 0x0077AEA0 size 287
public ?d_0077aea0@@YAXXZ
?d_0077aea0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 00h, 8Bh, 4Dh, 04h, 2Bh, 0C8h, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0E9h, 8Bh, 4Ch, 24h, 20h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h
    db 0E8h, 1Fh, 03h, 0C2h, 56h, 3Bh, 0C1h, 57h, 89h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 28h
    db 72h, 04h, 8Dh, 4Ch, 24h, 10h, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 14h, 74h, 2Ah
    db 8Dh, 04h, 89h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h, 3Dh
    db 70h, 10h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 16h, 0E8h, 3Fh, 36h, 0Bh
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 8Bh, 75h, 00h, 8Bh, 5Ch, 24h, 1Ch, 3Bh, 0F3h, 8Bh, 7Ch, 24h, 10h, 74h
    db 14h, 56h, 57h, 0E8h, 0AAh, 0C0h, 88h, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h, 83h, 0C7h
    db 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 74h, 24h, 28h, 83h, 0FEh, 01h, 75h, 13h, 8Bh, 44h
    db 24h, 20h, 50h, 57h, 0E8h, 89h, 0C0h, 88h, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 0EBh
    db 1Fh, 85h, 0F6h, 76h, 1Bh, 8Bh, 5Ch, 24h, 20h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 53h, 57h, 0E8h, 6Bh, 0C0h, 88h, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 14h, 4Eh, 75h, 0F0h
    db 8Ah, 44h, 24h, 2Ch, 84h, 0C0h, 75h, 1Fh, 8Bh, 5Dh, 04h, 8Bh, 74h, 24h, 1Ch, 3Bh
    db 0F3h, 74h, 14h, 56h, 57h, 0E8h, 48h, 0C0h, 88h, 0FFh, 83h, 0C6h, 14h, 83h, 0C4h, 08h
    db 83h, 0C7h, 14h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0CDh, 0E8h, 0D6h, 9Bh, 88h, 0FFh, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 10h, 89h, 7Dh, 04h, 5Fh, 8Dh, 0Ch, 89h, 8Dh, 14h, 88h
    db 5Eh, 89h, 45h, 00h, 89h, 55h, 08h, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 14h, 00h
?d_0077aea0@@YAXXZ ENDP

; ghidra: FUN_00b7b010  retail @ 0x0077B010 size 95
public ?d_0077b010@@YAXXZ
?d_0077b010@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0D9h, 45h, 89h, 0FFh, 83h, 0C6h, 6Ch, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 37h, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 0F7h, 12h, 0DAh, 4Bh, 0F7h, 0E9h
    db 0C1h, 0FAh, 05h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 6Bh, 0C0h, 6Ch, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 0Dh, 56h, 0E8h, 56h, 6Eh, 10h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh
    db 0C3h, 50h, 56h, 0E8h, 88h, 35h, 0Bh, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 0C3h
?d_0077b010@@YAXXZ ENDP

; ghidra: FUN_00b7b3f0  retail @ 0x0077B3F0 size 1209
public ?d_0077b3f0@@YAXXZ
?d_0077b3f0@@YAXXZ PROC
    db 83h, 0ECh, 4Ch, 56h, 8Bh, 0F1h, 8Ah, 86h, 84h, 00h, 00h, 00h, 84h, 0C0h, 75h, 0Eh
    db 8Bh, 86h, 88h, 00h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 94h, 04h, 00h, 00h, 55h, 8Bh
    db 6Eh, 04h, 8Ah, 85h, 31h, 01h, 00h, 00h, 84h, 0C0h, 89h, 6Ch, 24h, 08h, 74h, 19h
    db 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 80h, 0Ch, 01h, 00h, 00h, 83h, 0F8h, 01h, 74h, 09h
    db 83h, 0F8h, 05h, 0Fh, 85h, 68h, 04h, 00h, 00h, 8Ah, 85h, 33h, 01h, 00h, 00h, 84h
    db 0C0h, 74h, 0Eh, 8Bh, 86h, 0A0h, 00h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 50h, 04h, 00h
    db 00h, 0C6h, 86h, 84h, 00h, 00h, 00h, 00h, 0F6h, 86h, 64h, 01h, 00h, 00h, 10h, 53h
    db 8Bh, 5Ch, 24h, 5Ch, 57h, 0Fh, 84h, 0FDh, 00h, 00h, 00h, 8Bh, 45h, 14h, 83h, 0C5h
    db 14h, 85h, 0C0h, 0Fh, 84h, 0EFh, 00h, 00h, 00h, 66h, 83h, 78h, 04h, 00h, 0Fh, 84h
    db 0E4h, 00h, 00h, 00h, 8Bh, 4Bh, 1Ch, 0D9h, 43h, 0Ch, 8Bh, 0D1h, 0D9h, 54h, 24h, 20h
    db 0D9h, 43h, 2Ch, 89h, 54h, 24h, 18h, 6Ah, 00h, 0D9h, 0C9h, 8Dh, 54h, 24h, 20h, 0D9h
    db 5Ch, 24h, 18h, 52h, 89h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 24h, 8Bh, 54h, 24h, 2Ch
    db 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 52h, 8Bh, 54h, 24h, 2Ch, 52h, 0FFh, 50h
    db 4Ch, 8Bh, 46h, 18h, 85h, 0C0h, 8Dh, 7Eh, 18h, 74h, 2Fh, 8Bh, 0F8h, 85h, 0FFh, 75h
    db 16h, 0E8h, 42h, 66h, 88h, 0FFh, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 50h, 63h
    db 8Ah, 0FFh, 0E9h, 0A2h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 14h, 8Bh, 0C7h, 51h, 8Bh, 0C8h
    db 0E8h, 3Dh, 63h, 8Ah, 0FFh, 0E9h, 8Fh, 00h, 00h, 00h, 8Bh, 0Dh, 0BCh, 64h, 2Fh, 01h
    db 55h, 0E8h, 61h, 9Dh, 89h, 0FFh, 85h, 0C0h, 74h, 7Fh, 8Bh, 0Dh, 0BCh, 64h, 2Fh, 01h
    db 6Ah, 01h, 50h, 8Dh, 54h, 24h, 28h, 52h, 0E8h, 0CAh, 36h, 89h, 0FFh, 50h, 8Bh, 0CFh
    db 0E8h, 18h, 45h, 89h, 0FFh, 8Dh, 4Ch, 24h, 20h, 0E8h, 66h, 84h, 89h, 0FFh, 8Bh, 07h
    db 85h, 0C0h, 74h, 55h, 85h, 0C0h, 75h, 05h, 0E8h, 0DBh, 65h, 88h, 0FFh, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0C8h, 0E8h, 0E9h, 62h, 8Ah, 0FFh, 8Bh, 3Fh, 85h, 0FFh, 75h, 0Eh, 0E8h
    db 0C4h, 65h, 88h, 0FFh, 8Bh, 0C8h, 0E8h, 78h, 4Ah, 89h, 0FFh, 0EBh, 2Ch, 8Bh, 0C7h, 8Bh
    db 0C8h, 0E8h, 6Dh, 4Ah, 89h, 0FFh, 0EBh, 21h, 8Bh, 46h, 18h, 85h, 0C0h, 8Dh, 7Eh, 18h
    db 74h, 17h, 85h, 0C0h, 75h, 05h, 0E8h, 9Dh, 65h, 88h, 0FFh, 8Bh, 0C8h, 0E8h, 0A3h, 2Fh
    db 89h, 0FFh, 8Bh, 0CFh, 0E8h, 0B7h, 0A0h, 89h, 0FFh, 8Bh, 15h, 64h, 80h, 2Fh, 01h, 3Bh
    db 96h, 9Ch, 00h, 00h, 00h, 74h, 07h, 8Bh, 0CEh, 0E8h, 0C1h, 99h, 8Ah, 0FFh, 8Bh, 46h
    db 34h, 85h, 0C0h, 0Fh, 84h, 92h, 01h, 00h, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 48h, 69h
    db 84h, 0C9h, 0C7h, 44h, 24h, 2Ch, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 30h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 3Ch, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 40h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 44h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 4Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 50h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 54h, 00h, 00h, 80h, 3Fh, 74h, 1Bh, 0D9h, 43h, 0Ch, 8Bh
    db 4Bh, 2Ch, 0D9h, 43h, 1Ch, 89h, 4Ch, 24h, 28h, 0D9h, 0C9h, 8Bh, 0D1h, 0D9h, 5Ch, 24h
    db 38h, 0D9h, 5Ch, 24h, 48h, 0EBh, 4Fh, 8Bh, 03h, 8Bh, 4Bh, 04h, 8Bh, 53h, 08h, 89h
    db 44h, 24h, 2Ch, 8Bh, 43h, 0Ch, 89h, 4Ch, 24h, 30h, 8Bh, 4Bh, 10h, 89h, 54h, 24h
    db 34h, 8Bh, 53h, 14h, 89h, 44h, 24h, 38h, 8Bh, 43h, 18h, 89h, 4Ch, 24h, 3Ch, 8Bh
    db 4Bh, 1Ch, 89h, 54h, 24h, 40h, 8Bh, 53h, 20h, 89h, 44h, 24h, 44h, 8Bh, 43h, 24h
    db 89h, 4Ch, 24h, 48h, 8Bh, 4Bh, 28h, 89h, 54h, 24h, 4Ch, 8Bh, 53h, 2Ch, 89h, 44h
    db 24h, 50h, 89h, 4Ch, 24h, 54h, 8Dh, 44h, 24h, 2Ch, 50h, 8Bh, 0CEh, 89h, 54h, 24h
    db 5Ch, 0E8h, 0DAh, 0ACh, 8Ah, 0FFh, 8Bh, 4Eh, 34h, 8Bh, 11h, 8Dh, 44h, 24h, 2Ch, 50h
    db 0FFh, 52h, 54h, 8Ah, 86h, 10h, 02h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 0AAh, 00h, 00h
    db 00h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 68h, 8Bh, 0BEh, 1Ch, 02h
    db 00h, 00h, 8Bh, 0C8h, 89h, 86h, 1Ch, 02h, 00h, 00h, 8Bh, 86h, 18h, 02h, 00h, 00h
    db 2Bh, 0CFh, 03h, 0C1h, 8Bh, 8Eh, 14h, 02h, 00h, 00h, 8Dh, 0BEh, 14h, 02h, 00h, 00h
    db 89h, 44h, 24h, 60h, 3Bh, 0C1h, 8Dh, 44h, 24h, 60h, 72h, 02h, 8Bh, 0C7h, 8Bh, 00h
    db 85h, 0C0h, 89h, 44h, 24h, 60h, 0DBh, 44h, 24h, 60h, 89h, 86h, 18h, 02h, 00h, 00h
    db 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 07h, 0DBh, 07h, 85h, 0C0h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 0DEh, 0F9h, 8Bh, 4Eh, 34h, 83h, 0ECh, 0Ch, 0D9h, 0C0h
    db 0D8h, 8Eh, 28h, 02h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0D9h, 0C0h, 0D8h, 8Eh, 24h, 02h
    db 00h, 00h, 0D9h, 5Ch, 24h, 04h, 0D8h, 8Eh, 20h, 02h, 00h, 00h, 0D9h, 1Ch, 24h, 51h
    db 0E8h, 0B5h, 12h, 8Bh, 0FFh, 8Bh, 96h, 18h, 02h, 00h, 00h, 8Bh, 07h, 83h, 0C4h, 10h
    db 3Bh, 0D0h, 72h, 07h, 0C6h, 86h, 10h, 02h, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0E7h, 7Bh
    db 8Ch, 0FFh, 8Bh, 0CEh, 0E8h, 37h, 66h, 8Ch, 0FFh, 8Bh, 5Ch, 24h, 10h, 8Ah, 83h, 0DCh
    db 00h, 00h, 00h, 84h, 0C0h, 74h, 0Bh, 8Bh, 46h, 0Ch, 8Dh, 4Eh, 0Ch, 6Ah, 00h, 0FFh
    db 50h, 68h, 8Bh, 86h, 90h, 00h, 00h, 00h, 85h, 0C0h, 74h, 65h, 8Bh, 86h, 8Ch, 00h
    db 00h, 00h, 8Bh, 68h, 08h, 3Bh, 0E8h, 74h, 58h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 45h, 10h, 8Bh, 11h, 50h, 0FFh, 52h, 2Ch, 8Bh
    db 0F8h, 85h, 0FFh, 74h, 27h, 8Bh, 4Eh, 08h, 8Bh, 41h, 68h, 85h, 0C0h, 74h, 0Dh, 8Bh
    db 4Fh, 68h, 85h, 0C9h, 74h, 06h, 50h, 0E8h, 0DBh, 0D9h, 89h, 0FFh, 8Bh, 0CFh, 0E8h, 6Ch
    db 0Ah, 8Ah, 0FFh, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0B7h, 80h, 88h, 0FFh, 55h, 0E8h, 0AEh, 00h
    db 0Bh, 00h, 8Bh, 0E8h, 8Bh, 86h, 8Ch, 00h, 00h, 00h, 83h, 0C4h, 04h, 3Bh, 0E8h, 75h
    db 0AFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0ECh, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 47h, 71h
    db 8Ch, 0FFh, 8Bh, 46h, 08h, 8Bh, 0B8h, 0FCh, 00h, 00h, 00h, 85h, 0FFh, 74h, 32h, 8Bh
    db 87h, 14h, 02h, 00h, 00h, 85h, 0C0h, 74h, 28h, 8Ah, 8Bh, 0Ah, 01h, 00h, 00h, 84h
    db 0C9h, 75h, 1Eh, 8Bh, 80h, 0FCh, 01h, 00h, 00h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 24h
    db 84h, 0C0h, 75h, 0Dh, 8Ah, 46h, 2Fh, 84h, 0C0h, 75h, 18h, 0C6h, 46h, 2Fh, 01h, 0EBh
    db 12h, 8Ah, 46h, 2Eh, 84h, 0C0h, 74h, 0Bh, 8Ah, 46h, 2Fh, 84h, 0C0h, 74h, 04h, 0C6h
    db 46h, 2Fh, 00h, 85h, 0FFh, 74h, 1Eh, 8Bh, 46h, 3Ch, 85h, 0C0h, 74h, 17h, 83h, 78h
    db 34h, 01h, 75h, 11h, 0F6h, 87h, 44h, 03h, 00h, 00h, 01h, 74h, 08h, 0C6h, 46h, 2Fh
    db 01h, 0C6h, 40h, 04h, 00h, 8Bh, 46h, 58h, 3Bh, 46h, 5Ch, 5Fh, 5Bh, 74h, 0Ah, 8Ah
    db 86h, 71h, 01h, 00h, 00h, 84h, 0C0h, 75h, 12h, 8Bh, 4Eh, 4Ch, 3Bh, 4Eh, 50h, 74h
    db 13h, 8Ah, 86h, 70h, 01h, 00h, 00h, 84h, 0C0h, 74h, 09h, 8Bh, 56h, 0Ch, 8Dh, 4Eh
    db 0Ch, 0FFh, 52h, 70h, 8Bh, 46h, 34h, 50h, 8Bh, 0CEh, 0E8h, 0E2h, 0ADh, 89h, 0FFh, 8Dh
    db 8Eh, 78h, 01h, 00h, 00h, 0E8h, 7Bh, 43h, 8Ch, 0FFh, 8Bh, 0CEh, 0E8h, 02h, 0DDh, 8Ch
    db 0FFh, 5Dh, 5Eh, 83h, 0C4h, 4Ch, 0C2h, 04h, 00h
?d_0077b3f0@@YAXXZ ENDP
_TEXT ENDS
END
