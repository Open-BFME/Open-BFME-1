.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeCameraGlobal12F9DBC@@3MA:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Mouse0040F780@@3PAVMouse@@A:BYTE
EXTERN ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A:BYTE
EXTERN ?Rva009F7256_CIacos@@YAXXZ:NEAR
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheW3DFrameLengthInMsec@@3HA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeAngleTwoPi@@3MA:BYTE
EXTERN ?g_bfmeDefaultEG@@3MA:BYTE
EXTERN ?g_bfmeFlagEC@@3_NA:BYTE
EXTERN ?g_bfmeMgrGK@@3PAVBfmeMgrGK@@A:BYTE
EXTERN ?g_bfmeScaleBK@@3MA:BYTE
EXTERN ?j_000023f6@@YAXXZ:NEAR
EXTERN ?j_00012931@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_00020266@@YAXXZ:NEAR
EXTERN ?j_00022c96@@YAXXZ:NEAR
EXTERN ?j_0002a1b2@@YAXXZ:NEAR
EXTERN ?j_000312a0@@YAXXZ:NEAR
EXTERN ?j_000321fa@@YAXXZ:NEAR
EXTERN ?j_00033fa5@@YAXXZ:NEAR
EXTERN ?j_0003a25b@@YAXXZ:NEAR
EXTERN ?j_000442bf@@YAXXZ:NEAR
EXTERN ?j_00046fa1@@YAXXZ:NEAR
EXTERN ?j_000481fd@@YAXXZ:NEAR
EXTERN ?normAngle@@YIXAAM@Z:NEAR
EXTERN __real@4f800000:BYTE
EXTERN g_Va012BB1D8:BYTE
EXTERN g_Va012BB1DC:BYTE
EXTERN g_Va012BB1E0:BYTE
EXTERN g_Va012BB1E4:BYTE
EXTERN g_Va012BB1E8:BYTE
EXTERN g_Va012BB1F8:BYTE
EXTERN g_Va012BB1FC:BYTE
EXTERN g_Va012BB200:BYTE
EXTERN g_Va012BB204:BYTE
EXTERN g_Va012BB218:BYTE
EXTERN g_Va012F9DDC:BYTE
EXTERN g_Va012F9DE0:BYTE
EXTERN g_Va012F9E28:BYTE
_TEXT SEGMENT

; ghidra: FUN_00b3e050  retail @ 0x0073E050 size 5126
public ?d_0073e050@@YAXXZ
?d_0073e050@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 81h, 0ECh, 20h, 01h, 00h, 00h, 0A1h, 58h, 80h, 2Fh
    db 01h, 53h, 55h, 56h, 0C6h, 44h, 24h, 5Bh, 00h, 0C6h, 44h, 24h, 37h, 00h, 8Bh, 80h
    db 68h, 08h, 00h, 00h, 8Bh, 0F1h, 57h, 89h, 84h, 24h, 8Ch, 00h, 00h, 00h, 89h, 84h
    db 24h, 90h, 00h, 00h, 00h, 8Bh, 46h, 10h, 33h, 0FFh, 32h, 0DBh, 3Bh, 0C7h, 89h, 0B4h
    db 24h, 9Ch, 00h, 00h, 00h, 74h, 2Ch, 8Bh, 46h, 14h, 3Bh, 0C7h, 7Eh, 25h, 83h, 0F8h
    db 0Ah, 7Dh, 20h, 8Dh, 8Ch, 24h, 90h, 00h, 00h, 00h, 51h, 8Dh, 54h, 24h, 63h, 52h
    db 50h, 0E8h, 9Dh, 91h, 90h, 0FFh, 8Ah, 0D8h, 8Ah, 44h, 24h, 6Bh, 83h, 0C4h, 0Ch, 84h
    db 0C0h, 75h, 30h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Bh, 84h, 24h, 90h, 00h, 00h, 00h
    db 89h, 81h, 68h, 08h, 00h, 00h, 8Bh, 56h, 08h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 52h
    db 0E8h, 3Eh, 0EAh, 8Fh, 0FFh, 0A1h, 58h, 80h, 2Fh, 01h, 89h, 78h, 18h, 8Ah, 4Eh, 19h
    db 88h, 4Eh, 18h, 39h, 7Eh, 10h, 0Fh, 84h, 0A2h, 00h, 00h, 00h, 84h, 0DBh, 0Fh, 84h
    db 9Ah, 00h, 00h, 00h, 8Bh, 46h, 14h, 3Bh, 0C7h, 0Fh, 8Eh, 8Fh, 00h, 00h, 00h, 83h
    db 0F8h, 0Ah, 0Fh, 8Dh, 86h, 00h, 00h, 00h, 8Dh, 54h, 24h, 7Ch, 52h, 8Dh, 8Eh, 04h
    db 0FFh, 0FFh, 0FFh, 0E8h, 8Eh, 0CBh, 8Eh, 0FFh, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 01h
    db 0FFh, 50h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 1Ch, 8Bh
    db 11h, 0FFh, 52h, 30h, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 8Dh, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 20h, 50h, 8Bh
    db 46h, 10h, 8Dh, 4Ch, 24h, 3Fh, 51h, 8Bh, 4Eh, 14h, 8Dh, 94h, 24h, 84h, 00h, 00h
    db 00h, 52h, 50h, 51h, 0E8h, 0B6h, 7Dh, 8Fh, 0FFh, 83h, 0C4h, 14h, 84h, 0C0h, 75h, 0Eh
    db 0C7h, 46h, 14h, 09h, 00h, 00h, 00h, 0C7h, 46h, 10h, 0Fh, 00h, 00h, 00h, 8Ah, 44h
    db 24h, 3Bh, 84h, 0C0h, 0Fh, 84h, 0C4h, 00h, 00h, 00h, 8Bh, 15h, 0E0h, 7Fh, 2Fh, 01h
    db 8Bh, 82h, 1Ch, 30h, 00h, 00h, 57h, 68h, 00h, 00h, 80h, 3Fh, 8Bh, 0C8h, 51h, 8Dh
    db 54h, 24h, 6Ch, 52h, 6Ah, 01h, 6Ah, 01h, 57h, 89h, 44h, 24h, 30h, 0C7h, 44h, 24h
    db 7Ch, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0C7h, 84h, 24h, 84h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 60h, 60h, 1Ch, 00h
    db 0A1h, 58h, 80h, 2Fh, 01h, 89h, 0B8h, 68h, 08h, 00h, 00h, 8Bh, 4Eh, 08h, 83h, 0C4h
    db 1Ch, 51h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 0E8h, 16h, 0E9h, 8Fh, 0FFh, 8Bh, 0Dh, 70h
    db 12h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h
    db 24h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h
    db 0D9h, 5Ch, 24h, 1Ch, 8Bh, 01h, 0FFh, 50h, 30h, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh
    db 44h, 24h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Dh, 4Ch, 24h, 1Ch, 0D9h
    db 5Ch, 24h, 20h, 51h, 8Bh, 4Eh, 10h, 8Dh, 54h, 24h, 3Fh, 52h, 8Bh, 56h, 14h, 8Dh
    db 44h, 24h, 78h, 50h, 51h, 52h, 0E8h, 0D4h, 7Ch, 8Fh, 0FFh, 83h, 0C4h, 14h, 0A1h, 0ACh
    db 0D5h, 2Eh, 01h, 32h, 0DBh, 3Bh, 0C7h, 74h, 0Bh, 83h, 0B8h, 0C4h, 16h, 00h, 00h, 01h
    db 7Fh, 02h, 0B3h, 01h, 8Bh, 46h, 14h, 32h, 0C9h, 83h, 0F8h, 07h, 0BDh, 06h, 00h, 00h
    db 00h, 74h, 09h, 3Bh, 0C5h, 74h, 05h, 83h, 0F8h, 08h, 75h, 02h, 0B1h, 01h, 39h, 0BCh
    db 24h, 8Ch, 00h, 00h, 00h, 0Fh, 85h, 0C0h, 03h, 00h, 00h, 84h, 0C9h, 0Fh, 84h, 48h
    db 01h, 00h, 00h, 83h, 0F8h, 08h, 0C6h, 44h, 24h, 1Bh, 00h, 0B3h, 01h, 89h, 0BCh, 24h
    db 90h, 00h, 00h, 00h, 75h, 02h, 32h, 0DBh, 0E8h, 04h, 01h, 8Dh, 0FFh, 80h, 38h, 00h
    db 75h, 08h, 84h, 0DBh, 0Fh, 84h, 10h, 01h, 00h, 00h, 8Dh, 84h, 24h, 8Ch, 00h, 00h
    db 00h, 50h, 8Dh, 4Ch, 24h, 1Fh, 51h, 6Ah, 04h, 0E8h, 65h, 8Fh, 90h, 0FFh, 8Ah, 44h
    db 24h, 27h, 83h, 0C4h, 0Ch, 84h, 0C0h, 0Fh, 85h, 0EDh, 00h, 00h, 00h, 8Bh, 0Dh, 70h
    db 12h, 2Fh, 01h, 0C7h, 44h, 24h, 30h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 34h, 00h
    db 00h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h
    db 24h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h
    db 0D9h, 5Ch, 24h, 1Ch, 8Bh, 01h, 0FFh, 50h, 30h, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh
    db 44h, 24h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh
    db 01h, 0D9h, 5Ch, 24h, 20h, 8Bh, 91h, 1Ch, 30h, 00h, 00h, 57h, 68h, 00h, 00h, 80h
    db 3Fh, 8Bh, 0C2h, 50h, 8Dh, 4Ch, 24h, 6Ch, 51h, 6Ah, 01h, 6Ah, 01h, 57h, 89h, 54h
    db 24h, 30h, 0C7h, 44h, 24h, 7Ch, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 80h, 00h, 00h
    db 00h, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 84h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0E8h, 0BBh, 5Eh, 1Ch, 00h, 8Bh, 15h, 58h, 80h, 2Fh, 01h, 89h, 0AAh, 68h, 08h, 00h
    db 00h, 8Bh, 46h, 08h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 83h, 0C4h, 1Ch, 50h, 0E8h, 70h
    db 0E7h, 8Fh, 0FFh, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Dh, 54h, 24h, 1Eh, 52h, 8Dh, 44h, 24h
    db 38h, 50h, 55h, 6Ah, 04h, 89h, 3Dh, 00h, 14h, 2Fh, 01h, 0E8h, 6Fh, 7Bh, 8Fh, 0FFh
    db 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 54h, 24h, 32h, 52h, 8Dh, 44h, 24h, 4Ch, 50h, 55h
    db 6Ah, 04h, 0E8h, 58h, 7Bh, 8Fh, 0FFh, 83h, 0C4h, 28h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h
    db 89h, 0B9h, 68h, 08h, 00h, 00h, 0E9h, 70h, 02h, 00h, 00h, 0E8h, 0D1h, 0FFh, 8Ch, 0FFh
    db 80h, 38h, 00h, 0Fh, 84h, 62h, 02h, 00h, 00h, 84h, 0DBh, 0Fh, 85h, 5Ah, 02h, 00h
    db 00h, 8Dh, 94h, 24h, 8Ch, 00h, 00h, 00h, 52h, 8Dh, 44h, 24h, 1Fh, 50h, 6Ah, 04h
    db 0C6h, 44h, 24h, 27h, 01h, 0E8h, 29h, 8Eh, 90h, 0FFh, 8Ah, 44h, 24h, 27h, 83h, 0C4h
    db 0Ch, 84h, 0C0h, 0Fh, 85h, 32h, 02h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0C7h
    db 44h, 24h, 30h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 8Bh
    db 11h, 0FFh, 52h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 1Ch
    db 8Bh, 01h, 0FFh, 50h, 30h, 85h, 0C0h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 7Dh
    db 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 0D9h, 5Ch, 24h
    db 20h, 8Bh, 91h, 1Ch, 30h, 00h, 00h, 57h, 68h, 00h, 00h, 80h, 3Fh, 8Bh, 0C2h, 50h
    db 8Dh, 4Ch, 24h, 6Ch, 51h, 6Ah, 01h, 6Ah, 01h, 57h, 89h, 54h, 24h, 30h, 0C7h, 44h
    db 24h, 7Ch, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 80h, 00h, 00h, 00h, 00h, 00h, 00h
    db 00h, 0C7h, 84h, 24h, 84h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 7Fh, 5Dh, 1Ch
    db 00h, 83h, 0C4h, 1Ch, 0E8h, 0F8h, 0FEh, 8Ch, 0FFh, 8Ah, 48h, 21h, 84h, 0C9h, 8Bh, 15h
    db 58h, 80h, 2Fh, 01h, 75h, 53h, 0C7h, 82h, 68h, 08h, 00h, 00h, 03h, 00h, 00h, 00h
    db 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 0BDh, 0Dh, 00h, 00h, 84h, 0C9h, 75h, 0Fh, 8Bh
    db 4Eh, 08h, 51h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 0E8h, 15h, 0E6h, 8Fh, 0FFh, 8Dh, 54h
    db 24h, 1Ch, 52h, 8Dh, 44h, 24h, 1Eh, 50h, 8Dh, 4Ch, 24h, 38h, 51h, 55h, 6Ah, 04h
    db 0E8h, 1Ah, 7Ah, 8Fh, 0FFh, 8Dh, 54h, 24h, 30h, 52h, 8Dh, 44h, 24h, 32h, 50h, 8Dh
    db 4Ch, 24h, 4Ch, 51h, 0E9h, 1Ch, 01h, 00h, 00h, 89h, 0AAh, 68h, 08h, 00h, 00h, 8Bh
    db 46h, 08h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 50h, 0E8h, 0D5h, 0E5h, 8Fh, 0FFh, 8Dh, 4Ch
    db 24h, 1Ch, 51h, 8Dh, 54h, 24h, 1Eh, 52h, 8Dh, 44h, 24h, 38h, 50h, 55h, 6Ah, 04h
    db 89h, 3Dh, 00h, 14h, 2Fh, 01h, 0E8h, 0D4h, 79h, 8Fh, 0FFh, 8Dh, 4Ch, 24h, 30h, 51h
    db 8Dh, 54h, 24h, 32h, 52h, 8Dh, 44h, 24h, 4Ch, 50h, 55h, 6Ah, 04h, 0E8h, 0BDh, 79h
    db 8Fh, 0FFh, 8Dh, 8Ch, 24h, 0B4h, 00h, 00h, 00h, 51h, 8Dh, 54h, 24h, 47h, 52h, 6Ah
    db 04h, 0E8h, 0BDh, 8Ch, 90h, 0FFh, 0A1h, 58h, 80h, 2Fh, 01h, 0C7h, 80h, 68h, 08h, 00h
    db 00h, 04h, 00h, 00h, 00h, 8Bh, 4Eh, 08h, 83h, 0C4h, 34h, 51h, 8Bh, 0Dh, 58h, 80h
    db 2Fh, 01h, 0E8h, 6Ch, 0E5h, 8Fh, 0FFh, 8Dh, 54h, 24h, 1Ch, 52h, 8Dh, 44h, 24h, 1Eh
    db 50h, 8Dh, 4Ch, 24h, 38h, 51h, 55h, 6Ah, 04h, 0C7h, 05h, 00h, 14h, 2Fh, 01h, 01h
    db 00h, 00h, 00h, 0E8h, 67h, 79h, 8Fh, 0FFh, 8Dh, 54h, 24h, 30h, 52h, 8Dh, 44h, 24h
    db 32h, 50h, 8Dh, 4Ch, 24h, 4Ch, 51h, 55h, 6Ah, 04h, 0E8h, 50h, 79h, 8Fh, 0FFh, 8Dh
    db 94h, 24h, 0B4h, 00h, 00h, 00h, 52h, 8Dh, 44h, 24h, 47h, 50h, 6Ah, 04h, 0E8h, 50h
    db 8Ch, 90h, 0FFh, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 0C7h, 81h, 68h, 08h, 00h, 00h, 05h
    db 00h, 00h, 00h, 8Bh, 56h, 08h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 83h, 0C4h, 34h, 52h
    db 0E8h, 0FEh, 0E4h, 8Fh, 0FFh, 8Dh, 44h, 24h, 1Ch, 50h, 8Dh, 4Ch, 24h, 1Eh, 51h, 8Dh
    db 54h, 24h, 38h, 52h, 55h, 6Ah, 04h, 0C7h, 05h, 00h, 14h, 2Fh, 01h, 02h, 00h, 00h
    db 00h, 0E8h, 0F9h, 78h, 8Fh, 0FFh, 8Dh, 44h, 24h, 30h, 50h, 8Dh, 4Ch, 24h, 32h, 51h
    db 8Dh, 54h, 24h, 4Ch, 52h, 55h, 6Ah, 04h, 0E8h, 0E2h, 78h, 8Fh, 0FFh, 0A1h, 58h, 80h
    db 2Fh, 01h, 83h, 0C4h, 28h, 89h, 0B8h, 68h, 08h, 00h, 00h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh
    db 01h, 39h, 0B9h, 88h, 0Ah, 00h, 00h, 0Fh, 84h, 86h, 0Dh, 00h, 00h, 8Bh, 0ACh, 24h
    db 9Ch, 00h, 00h, 00h, 8Bh, 95h, 04h, 0FFh, 0FFh, 0FFh, 33h, 0C0h, 81h, 0C5h, 04h, 0FFh
    db 0FFh, 0FFh, 8Bh, 0CDh, 89h, 84h, 24h, 0B0h, 00h, 00h, 00h, 89h, 84h, 24h, 0B4h, 00h
    db 00h, 00h, 0FFh, 52h, 3Ch, 89h, 84h, 24h, 0B8h, 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh
    db 0CDh, 0FFh, 50h, 44h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 89h, 84h, 24h, 0BCh, 00h, 00h
    db 00h, 8Bh, 49h, 0Ch, 0E8h, 79h, 46h, 8Ch, 0FFh, 85h, 0C0h, 0Fh, 84h, 4Bh, 06h, 00h
    db 00h, 8Bh, 15h, 14h, 0F2h, 2Eh, 01h, 8Bh, 4Ah, 0Ch, 0E8h, 63h, 46h, 8Ch, 0FFh, 8Bh
    db 58h, 04h, 8Bh, 45h, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 53h, 0Ch, 52h, 8Bh, 0CDh
    db 0FFh, 90h, 5Ch, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 40h, 01h, 00h, 00h, 8Bh, 44h
    db 24h, 28h, 8Bh, 4Ch, 24h, 24h, 83h, 0C0h, 0FDh, 89h, 44h, 24h, 14h, 0DBh, 44h, 24h
    db 14h, 68h, 00h, 0FFh, 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 8Dh, 51h, 03h, 0D9h, 5Ch
    db 24h, 1Ch, 8Bh, 44h, 24h, 1Ch, 50h, 51h, 89h, 54h, 24h, 24h, 0DBh, 44h, 24h, 24h
    db 83h, 0C1h, 0FDh, 89h, 4Ch, 24h, 24h, 0D9h, 1Ch, 24h, 50h, 0DBh, 44h, 24h, 28h, 51h
    db 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 1Ch, 24h, 0E8h, 10h, 0BCh, 90h, 0FFh, 8Bh, 44h
    db 24h, 24h, 83h, 0C0h, 03h, 89h, 44h, 24h, 14h, 8Bh, 44h, 24h, 28h, 0DBh, 44h, 24h
    db 14h, 8Dh, 48h, 03h, 68h, 00h, 0FFh, 0FFh, 0FFh, 89h, 4Ch, 24h, 18h, 0D9h, 5Ch, 24h
    db 30h, 0DBh, 44h, 24h, 18h, 68h, 00h, 00h, 80h, 3Fh, 51h, 8Bh, 4Ch, 24h, 38h, 0D9h
    db 1Ch, 24h, 83h, 0C0h, 0FDh, 51h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 51h, 0D9h
    db 1Ch, 24h, 51h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0E8h, 0C0h, 0BBh, 90h, 0FFh, 8Bh, 54h
    db 24h, 28h, 8Bh, 4Ch, 24h, 24h, 83h, 0C2h, 03h, 89h, 54h, 24h, 14h, 0DBh, 44h, 24h
    db 14h, 68h, 00h, 0FFh, 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 8Dh, 51h, 0FDh, 0D9h, 5Ch
    db 24h, 1Ch, 8Bh, 44h, 24h, 1Ch, 50h, 51h, 89h, 54h, 24h, 24h, 0DBh, 44h, 24h, 24h
    db 83h, 0C1h, 03h, 89h, 4Ch, 24h, 24h, 0D9h, 1Ch, 24h, 50h, 0DBh, 44h, 24h, 28h, 51h
    db 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 1Ch, 24h, 0E8h, 70h, 0BBh, 90h, 0FFh, 8Bh, 44h
    db 24h, 24h, 83h, 0C0h, 0FDh, 89h, 44h, 24h, 14h, 0DBh, 44h, 24h, 14h, 8Bh, 44h, 24h
    db 28h, 68h, 00h, 0FFh, 0FFh, 0FFh, 8Dh, 48h, 0FDh, 68h, 00h, 00h, 80h, 3Fh, 0D9h, 5Ch
    db 24h, 34h, 89h, 4Ch, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 51h, 8Bh, 4Ch, 24h, 38h, 0D9h
    db 1Ch, 24h, 83h, 0C0h, 03h, 51h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 51h, 0D9h
    db 1Ch, 24h, 51h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0E8h, 20h, 0BBh, 90h, 0FFh, 8Bh, 03h
    db 85h, 0C0h, 89h, 44h, 24h, 6Ch, 0Fh, 84h, 0C5h, 02h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 8Bh, 44h, 24h, 6Ch, 8Dh, 78h, 0Ch, 8Bh, 40h, 18h, 8Bh, 0D7h, 8Bh, 0Ah, 89h, 4Ch
    db 24h, 40h, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 83h, 0C3h, 0Ch, 83h, 0F8h, 10h, 89h, 4Ch
    db 24h, 44h, 8Bh, 0Bh, 89h, 4Ch, 24h, 70h, 0D9h, 44h, 24h, 70h, 0D8h, 64h, 24h, 40h
    db 89h, 54h, 24h, 48h, 8Bh, 53h, 04h, 8Bh, 4Bh, 08h, 0D9h, 5Ch, 24h, 4Ch, 89h, 54h
    db 24h, 74h, 0D9h, 44h, 24h, 74h, 89h, 4Ch, 24h, 78h, 0D8h, 64h, 24h, 44h, 0C7h, 44h
    db 24h, 58h, 00h, 0FFh, 0FFh, 0FFh, 0D9h, 5Ch, 24h, 50h, 0D9h, 44h, 24h, 78h, 0D8h, 64h
    db 24h, 48h, 0D9h, 5Ch, 24h, 54h, 75h, 0Ah, 0C7h, 44h, 24h, 58h, 0FFh, 00h, 00h, 0FFh
    db 0EBh, 12h, 83h, 0F8h, 01h, 7Eh, 0Dh, 83h, 0F8h, 10h, 7Dh, 08h, 0C7h, 44h, 24h, 58h
    db 0FFh, 0FFh, 00h, 0FFh, 33h, 0C0h, 89h, 44h, 24h, 2Ch, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0DBh, 44h, 24h, 2Ch, 40h, 89h, 44h, 24h, 2Ch, 8Bh, 0D7h, 0DCh, 0Dh, 68h, 0F0h, 0Eh
    db 01h, 8Bh, 02h, 0DBh, 44h, 24h, 2Ch, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 89h, 44h, 24h
    db 40h, 0DCh, 0Dh, 68h, 0F0h, 0Eh, 01h, 89h, 4Ch, 24h, 44h, 0D9h, 0C1h, 89h, 54h, 24h
    db 48h, 0D8h, 4Ch, 24h, 4Ch, 8Bh, 0C7h, 8Bh, 08h, 8Bh, 50h, 04h, 0D8h, 44h, 24h, 40h
    db 8Bh, 40h, 08h, 89h, 4Ch, 24h, 70h, 89h, 54h, 24h, 74h, 0D9h, 5Ch, 24h, 40h, 8Bh
    db 55h, 00h, 0D9h, 0C1h, 89h, 44h, 24h, 78h, 0D8h, 4Ch, 24h, 50h, 8Dh, 84h, 24h, 94h
    db 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 74h, 0D8h, 44h, 24h, 48h, 51h, 8Bh, 0CDh, 0D9h
    db 5Ch, 24h, 4Ch, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 5Ch, 0D8h, 44h, 24h, 50h, 0D9h, 5Ch, 24h
    db 50h, 0D9h, 44h, 24h, 54h, 0D8h, 0C9h, 0D8h, 44h, 24h, 78h, 0D9h, 5Ch, 24h, 78h, 0D9h
    db 44h, 24h, 58h, 0D8h, 0C9h, 0D8h, 44h, 24h, 7Ch, 0D9h, 5Ch, 24h, 7Ch, 0D8h, 4Ch, 24h
    db 5Ch, 0D8h, 84h, 24h, 80h, 00h, 00h, 00h, 0D9h, 9Ch, 24h, 80h, 00h, 00h, 00h, 0FFh
    db 92h, 5Ch, 01h, 00h, 00h, 8Bh, 55h, 00h, 8Bh, 0D8h, 8Dh, 44h, 24h, 24h, 0F7h, 0DBh
    db 50h, 8Dh, 4Ch, 24h, 44h, 1Ah, 0DBh, 51h, 8Bh, 0CDh, 0FEh, 0C3h, 0FFh, 92h, 5Ch, 01h
    db 00h, 00h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 84h, 0DBh, 75h, 08h, 84h, 0C0h, 0Fh, 84h
    db 9Ch, 00h, 00h, 00h, 8Dh, 94h, 24h, 0B0h, 00h, 00h, 00h, 52h, 8Dh, 84h, 24h, 88h
    db 00h, 00h, 00h, 50h, 8Dh, 8Ch, 24h, 84h, 00h, 00h, 00h, 51h, 8Dh, 94h, 24h, 0A0h
    db 00h, 00h, 00h, 52h, 8Dh, 44h, 24h, 34h, 50h, 0E8h, 75h, 27h, 8Ch, 0FFh, 83h, 0C4h
    db 14h, 84h, 0C0h, 74h, 6Bh, 0DBh, 84h, 24h, 88h, 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h
    db 2Fh, 01h, 8Bh, 11h, 8Bh, 0F1h, 0D9h, 5Ch, 24h, 14h, 0DBh, 84h, 24h, 84h, 00h, 00h
    db 00h, 0D9h, 5Ch, 24h, 3Ch, 0DBh, 84h, 24h, 80h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 30h
    db 0DBh, 44h, 24h, 7Ch, 0D9h, 5Ch, 24h, 1Ch, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 4Ch
    db 24h, 58h, 8Bh, 54h, 24h, 14h, 8Bh, 06h, 51h, 8Bh, 4Ch, 24h, 40h, 68h, 00h, 00h
    db 80h, 3Fh, 52h, 8Bh, 54h, 24h, 3Ch, 51h, 8Bh, 4Ch, 24h, 2Ch, 52h, 51h, 8Bh, 0CEh
    db 0FFh, 90h, 0B8h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 2Ch, 83h, 0F8h, 0Ah, 89h, 44h, 24h, 2Ch, 0Fh, 8Ch, 6Fh, 0FEh, 0FFh
    db 0FFh, 8Bh, 5Ch, 24h, 6Ch, 83h, 3Bh, 00h, 0Fh, 84h, 85h, 00h, 00h, 00h, 8Bh, 45h
    db 00h, 8Dh, 4Ch, 24h, 24h, 51h, 57h, 8Bh, 0CDh, 0FFh, 90h, 5Ch, 01h, 00h, 00h, 85h
    db 0C0h, 75h, 70h, 0DBh, 44h, 24h, 28h, 8Bh, 44h, 24h, 24h, 8Bh, 0Dh, 70h, 12h, 2Fh
    db 01h, 8Dh, 50h, 03h, 0D9h, 54h, 24h, 30h, 89h, 54h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch
    db 83h, 0C0h, 0FCh, 89h, 44h, 24h, 1Ch, 8Bh, 01h, 0D9h, 5Ch, 24h, 3Ch, 8Bh, 0F1h, 0D9h
    db 5Ch, 24h, 14h, 0DBh, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0FFh, 90h, 0B0h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 58h, 8Bh, 4Ch, 24h, 30h, 8Bh, 16h, 50h, 8Bh, 44h, 24h, 40h
    db 68h, 00h, 00h, 80h, 3Fh, 51h, 8Bh, 4Ch, 24h, 20h, 50h, 8Bh, 44h, 24h, 2Ch, 51h
    db 50h, 8Bh, 0CEh, 0FFh, 92h, 0B8h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh
    db 00h, 00h, 00h, 8Bh, 03h, 85h, 0C0h, 89h, 44h, 24h, 6Ch, 0Fh, 85h, 3Fh, 0FDh, 0FFh
    db 0FFh, 85h, 0DBh, 0Fh, 84h, 0FCh, 00h, 00h, 00h, 8Bh, 45h, 00h, 8Dh, 4Ch, 24h, 24h
    db 51h, 83h, 0C3h, 0Ch, 53h, 8Bh, 0CDh, 0FFh, 90h, 5Ch, 01h, 00h, 00h, 85h, 0C0h, 0Fh
    db 85h, 0E0h, 00h, 00h, 00h, 0DBh, 44h, 24h, 28h, 8Bh, 44h, 24h, 24h, 8Bh, 0Dh, 70h
    db 12h, 2Fh, 01h, 8Dh, 50h, 03h, 0D9h, 54h, 24h, 30h, 89h, 54h, 24h, 1Ch, 0DBh, 44h
    db 24h, 1Ch, 83h, 0C0h, 0FCh, 89h, 44h, 24h, 1Ch, 8Bh, 01h, 0D9h, 5Ch, 24h, 3Ch, 8Bh
    db 0F1h, 0D9h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0FFh, 90h, 0B0h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 30h, 8Bh, 4Ch, 24h, 3Ch, 8Bh, 16h, 68h, 00h, 0FFh
    db 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 50h, 8Bh, 44h, 24h, 20h, 51h, 8Bh, 4Ch, 24h
    db 2Ch, 50h, 51h, 8Bh, 0CEh, 0FFh, 92h, 0B8h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh
    db 92h, 0DCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 28h, 8Dh, 48h, 03h, 89h, 4Ch, 24h, 1Ch
    db 0DBh, 44h, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 0D9h, 5Ch, 24h, 30h
    db 83h, 0C0h, 0FCh, 0DBh, 44h, 24h, 24h, 89h, 44h, 24h, 1Ch, 8Bh, 0F1h, 0D9h, 54h, 24h
    db 3Ch, 0DBh, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch, 0D9h, 5Ch, 24h, 14h, 0FFh, 92h, 0B0h
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 30h, 8Bh, 54h, 24h, 3Ch, 8Bh, 06h, 68h, 00h, 0FFh
    db 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 51h, 8Bh, 4Ch, 24h, 28h, 52h, 8Bh, 54h, 24h
    db 24h, 51h, 52h, 8Bh, 0CEh, 0FFh, 90h, 0B8h, 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh
    db 90h, 0DCh, 00h, 00h, 00h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 0E8h, 44h
    db 2Dh, 8Fh, 0FFh, 8Bh, 55h, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 50h, 8Bh, 0CDh, 0FFh, 92h
    db 5Ch, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 0E0h, 00h, 00h, 00h, 0DBh, 44h, 24h, 28h
    db 8Bh, 44h, 24h, 24h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Dh, 50h, 03h, 0D9h, 54h, 24h
    db 30h, 89h, 54h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 83h, 0C0h, 0FDh, 89h, 44h, 24h, 1Ch
    db 8Bh, 01h, 0D9h, 5Ch, 24h, 3Ch, 8Bh, 0F1h, 0D9h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 1Ch
    db 0D9h, 5Ch, 24h, 1Ch, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 30h, 8Bh, 4Ch
    db 24h, 3Ch, 8Bh, 16h, 68h, 00h, 00h, 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 50h, 8Bh
    db 44h, 24h, 20h, 51h, 8Bh, 4Ch, 24h, 2Ch, 50h, 51h, 8Bh, 0CEh, 0FFh, 92h, 0B8h, 00h
    db 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 28h
    db 8Dh, 48h, 03h, 89h, 4Ch, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh
    db 01h, 8Bh, 11h, 0D9h, 5Ch, 24h, 30h, 83h, 0C0h, 0FDh, 0DBh, 44h, 24h, 24h, 89h, 44h
    db 24h, 1Ch, 8Bh, 0F1h, 0D9h, 54h, 24h, 3Ch, 0DBh, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 1Ch
    db 0D9h, 5Ch, 24h, 14h, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 30h, 8Bh, 54h
    db 24h, 3Ch, 8Bh, 06h, 68h, 00h, 00h, 0FFh, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 51h, 8Bh
    db 4Ch, 24h, 28h, 52h, 8Bh, 54h, 24h, 24h, 51h, 52h, 8Bh, 0CEh, 0FFh, 90h, 0B8h, 00h
    db 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 0DCh, 00h, 00h, 00h, 8Bh, 0Dh, 0C8h, 0D5h
    db 2Eh, 01h, 83h, 0B9h, 88h, 0Ah, 00h, 00h, 03h, 0Fh, 85h, 0A7h, 01h, 00h, 00h, 8Bh
    db 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 0FFh, 92h, 0F0h, 00h, 00h, 00h, 83h, 0F8h, 01h
    db 0Fh, 85h, 90h, 01h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 0FFh, 90h
    db 04h, 01h, 00h, 00h, 8Bh, 88h, 0FCh, 00h, 00h, 00h, 8Bh, 81h, 9Ch, 00h, 00h, 00h
    db 83h, 0F8h, 0FFh, 89h, 44h, 24h, 30h, 8Bh, 91h, 0A0h, 00h, 00h, 00h, 89h, 54h, 24h
    db 34h, 8Bh, 0B1h, 0A4h, 00h, 00h, 00h, 89h, 74h, 24h, 24h, 8Bh, 89h, 0A8h, 00h, 00h
    db 00h, 89h, 4Ch, 24h, 28h, 0Fh, 84h, 4Bh, 01h, 00h, 00h, 8Dh, 04h, 80h, 0D1h, 0E0h
    db 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 8Dh, 0Ch, 92h, 0D1h, 0E1h, 0D9h, 5Ch, 24h
    db 60h, 89h, 4Ch, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 6Ah
    db 01h, 6Ah, 00h, 0D9h, 5Ch, 24h, 6Ch, 8Bh, 44h, 24h, 6Ch, 6Ah, 01h, 50h, 8Bh, 44h
    db 24h, 70h, 0C7h, 44h, 24h, 78h, 00h, 00h, 00h, 00h, 8Bh, 11h, 50h, 0FFh, 52h, 1Ch
    db 0D9h, 5Ch, 24h, 68h, 8Bh, 44h, 24h, 24h, 8Dh, 0Ch, 80h, 8Bh, 44h, 24h, 28h, 0D1h
    db 0E1h, 89h, 4Ch, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Dh
    db 14h, 80h, 0D1h, 0E2h, 0D9h, 5Ch, 24h, 4Ch, 89h, 54h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch
    db 6Ah, 01h, 6Ah, 00h, 0D9h, 5Ch, 24h, 58h, 8Bh, 54h, 24h, 58h, 6Ah, 01h, 52h, 8Bh
    db 54h, 24h, 5Ch, 0C7h, 44h, 24h, 64h, 00h, 00h, 00h, 00h, 8Bh, 01h, 52h, 0FFh, 50h
    db 1Ch, 0D9h, 5Ch, 24h, 54h, 8Bh, 45h, 00h, 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 54h, 24h
    db 64h, 52h, 8Bh, 0CDh, 0FFh, 90h, 5Ch, 01h, 00h, 00h, 8Bh, 0D8h, 8Bh, 45h, 00h, 8Dh
    db 4Ch, 24h, 24h, 0F7h, 0DBh, 51h, 8Dh, 54h, 24h, 50h, 1Ah, 0DBh, 52h, 8Bh, 0CDh, 0FEh
    db 0C3h, 0FFh, 90h, 5Ch, 01h, 00h, 00h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 84h, 0DBh, 75h
    db 04h, 84h, 0C0h, 74h, 71h, 8Dh, 84h, 24h, 0B0h, 00h, 00h, 00h, 50h, 8Dh, 8Ch, 24h
    db 80h, 00h, 00h, 00h, 51h, 8Dh, 94h, 24h, 8Ch, 00h, 00h, 00h, 52h, 8Dh, 44h, 24h
    db 30h, 50h, 8Dh, 4Ch, 24h, 40h, 51h, 0E8h, 0D7h, 22h, 8Ch, 0FFh, 83h, 0C4h, 14h, 84h
    db 0C0h, 74h, 43h, 0DBh, 84h, 24h, 80h, 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h
    db 68h, 00h, 0FFh, 00h, 0FFh, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h
    db 0Ch, 0DBh, 84h, 24h, 94h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0DBh, 84h, 24h, 0A0h
    db 00h, 00h, 00h, 0D9h, 5Ch, 24h, 04h, 0DBh, 84h, 24h, 9Ch, 00h, 00h, 00h, 0D9h, 1Ch
    db 24h, 0E8h, 88h, 0B4h, 90h, 0FFh, 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 83h, 0BAh, 88h, 0Ah
    db 00h, 00h, 07h, 0Fh, 85h, 0C9h, 02h, 00h, 00h, 8Bh, 45h, 00h, 33h, 0F6h, 8Bh, 0CDh
    db 89h, 0B4h, 24h, 0A0h, 00h, 00h, 00h, 89h, 0B4h, 24h, 0A4h, 00h, 00h, 00h, 0FFh, 50h
    db 3Ch, 8Bh, 55h, 00h, 8Bh, 0CDh, 89h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh, 52h, 44h
    db 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 01h, 0FFh
    db 50h, 78h, 3Bh, 0C6h, 89h, 44h, 24h, 58h, 0Fh, 84h, 84h, 02h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 4Ch, 24h, 58h, 8Bh, 51h, 4Ch, 83h, 0C8h, 0FFh, 3Bh, 0D0h, 89h, 44h, 24h, 6Ch
    db 0Fh, 8Eh, 59h, 02h, 00h, 00h, 8Bh, 0D1h, 83h, 0C2h, 1Ch, 89h, 54h, 24h, 2Ch, 90h
    db 8Bh, 44h, 24h, 6Ch, 85h, 0C0h, 7Dh, 09h, 8Bh, 44h, 24h, 58h, 8Bh, 40h, 44h, 0EBh
    db 0Fh, 83h, 0F8h, 08h, 7Dh, 08h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 01h, 0EBh, 02h, 33h, 0C0h
    db 85h, 0C0h, 0Fh, 84h, 04h, 02h, 00h, 00h, 8Bh, 7Ch, 24h, 58h, 8Bh, 57h, 0Ch, 8Bh
    db 4Fh, 10h, 83h, 0C7h, 0Ch, 89h, 54h, 24h, 40h, 8Bh, 57h, 08h, 89h, 4Ch, 24h, 44h
    db 89h, 54h, 24h, 48h, 8Bh, 48h, 0Ch, 89h, 4Ch, 24h, 4Ch, 8Bh, 50h, 10h, 89h, 54h
    db 24h, 50h, 0D9h, 40h, 14h, 0D9h, 44h, 24h, 4Ch, 33h, 0C0h, 0D8h, 64h, 24h, 40h, 89h
    db 44h, 24h, 14h, 0D9h, 5Ch, 24h, 60h, 0D9h, 44h, 24h, 50h, 0D8h, 64h, 24h, 44h, 0D9h
    db 5Ch, 24h, 64h, 0D8h, 64h, 24h, 48h, 0D9h, 5Ch, 24h, 68h, 0EBh, 03h, 8Dh, 49h, 00h
    db 0DBh, 44h, 24h, 14h, 40h, 89h, 44h, 24h, 14h, 8Bh, 0C7h, 0DCh, 0Dh, 68h, 0F0h, 0Eh
    db 01h, 8Bh, 08h, 0DBh, 44h, 24h, 14h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 4Ch, 24h
    db 40h, 0DCh, 0Dh, 68h, 0F0h, 0Eh, 01h, 89h, 54h, 24h, 44h, 0D9h, 44h, 24h, 60h, 89h
    db 44h, 24h, 48h, 0D8h, 0CAh, 8Bh, 0CFh, 8Bh, 11h, 8Bh, 41h, 04h, 0D8h, 44h, 24h, 40h
    db 8Bh, 49h, 08h, 89h, 54h, 24h, 4Ch, 8Bh, 55h, 00h, 0D9h, 5Ch, 24h, 40h, 89h, 44h
    db 24h, 50h, 0D9h, 44h, 24h, 64h, 89h, 4Ch, 24h, 54h, 0D8h, 0CAh, 8Dh, 84h, 24h, 94h
    db 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 50h, 0D8h, 44h, 24h, 48h, 51h, 8Bh, 0CDh, 0D9h
    db 5Ch, 24h, 4Ch, 0D9h, 44h, 24h, 70h, 0D8h, 0CAh, 0D8h, 44h, 24h, 50h, 0D9h, 5Ch, 24h
    db 50h, 0D9h, 44h, 24h, 68h, 0D8h, 0C9h, 0D8h, 44h, 24h, 54h, 0D9h, 5Ch, 24h, 54h, 0D9h
    db 44h, 24h, 6Ch, 0D8h, 0C9h, 0D8h, 44h, 24h, 58h, 0D9h, 5Ch, 24h, 58h, 0D9h, 44h, 24h
    db 70h, 0D8h, 0C9h, 0D8h, 44h, 24h, 5Ch, 0D9h, 5Ch, 24h, 5Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0FFh
    db 92h, 5Ch, 01h, 00h, 00h, 8Bh, 55h, 00h, 8Bh, 0D8h, 8Dh, 44h, 24h, 70h, 0F7h, 0DBh
    db 50h, 8Dh, 4Ch, 24h, 44h, 1Ah, 0DBh, 51h, 8Bh, 0CDh, 0FEh, 0C3h, 0FFh, 92h, 5Ch, 01h
    db 00h, 00h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 84h, 0DBh, 75h, 08h, 84h, 0C0h, 0Fh, 84h
    db 0B7h, 00h, 00h, 00h, 8Dh, 94h, 24h, 0A0h, 00h, 00h, 00h, 52h, 8Dh, 84h, 24h, 80h
    db 00h, 00h, 00h, 50h, 8Dh, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 51h, 8Dh, 94h, 24h, 0A0h
    db 00h, 00h, 00h, 52h, 8Dh, 84h, 24h, 80h, 00h, 00h, 00h, 50h, 0E8h, 82h, 20h, 8Ch
    db 0FFh, 83h, 0C4h, 14h, 84h, 0C0h, 0Fh, 84h, 7Fh, 00h, 00h, 00h, 0DBh, 84h, 24h, 80h
    db 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 8Bh, 0F1h, 0D9h, 5Ch, 24h
    db 1Ch, 0DBh, 44h, 24h, 7Ch, 0D9h, 5Ch, 24h, 30h, 0DBh, 84h, 24h, 88h, 00h, 00h, 00h
    db 0D9h, 5Ch, 24h, 3Ch, 0DBh, 84h, 24h, 84h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 24h, 0FFh
    db 92h, 0B0h, 00h, 00h, 00h, 8Bh, 54h, 24h, 6Ch, 33h, 0C9h, 8Bh, 06h, 85h, 0D2h, 8Bh
    db 54h, 24h, 1Ch, 0Fh, 9Dh, 0C1h, 49h, 81h, 0E1h, 00h, 01h, 0FFh, 0FFh, 81h, 0C1h, 00h
    db 0FFh, 0FFh, 0FFh, 51h, 8Bh, 4Ch, 24h, 34h, 68h, 00h, 00h, 80h, 3Fh, 52h, 8Bh, 54h
    db 24h, 48h, 51h, 8Bh, 4Ch, 24h, 34h, 52h, 51h, 8Bh, 0CEh, 0FFh, 90h, 0B8h, 00h, 00h
    db 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 83h
    db 0F8h, 0Ah, 89h, 44h, 24h, 14h, 0Fh, 8Ch, 54h, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h, 6Ch
    db 8Bh, 74h, 24h, 2Ch, 8Bh, 4Ch, 24h, 58h, 8Bh, 51h, 4Ch, 40h, 83h, 0C6h, 04h, 3Bh
    db 0C2h, 89h, 44h, 24h, 6Ch, 89h, 74h, 24h, 2Ch, 0Fh, 8Ch, 0B1h, 0FDh, 0FFh, 0FFh, 8Bh
    db 54h, 24h, 58h, 8Bh, 42h, 1Ch, 85h, 0C0h, 89h, 44h, 24h, 58h, 0Fh, 85h, 7Eh, 0FDh
    db 0FFh, 0FFh, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 83h, 0B8h, 88h, 0Ah, 00h, 00h, 02h, 0Fh, 85h
    db 3Fh, 02h, 00h, 00h, 8Bh, 55h, 00h, 33h, 0FFh, 8Bh, 0CDh, 89h, 0BCh, 24h, 0A0h, 00h
    db 00h, 00h, 89h, 0BCh, 24h, 0A4h, 00h, 00h, 00h, 0FFh, 52h, 3Ch, 89h, 84h, 24h, 0A8h
    db 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 50h, 44h, 8Bh, 0Dh, 14h, 0F2h, 2Eh
    db 01h, 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 51h, 0Ch, 8Bh, 0B2h, 58h, 08h, 00h
    db 00h, 3Bh, 0F7h, 89h, 74h, 24h, 2Ch, 0Fh, 84h, 0F6h, 01h, 00h, 00h, 0EBh, 04h, 8Bh
    db 74h, 24h, 2Ch, 8Dh, 8Ch, 24h, 0C0h, 00h, 00h, 00h, 0E8h, 7Eh, 0ACh, 8Dh, 0FFh, 83h
    db 0C6h, 0Ch, 0B9h, 1Bh, 00h, 00h, 00h, 8Dh, 0BCh, 24h, 0C0h, 00h, 00h, 00h, 0F3h, 0A5h
    db 33h, 0F6h, 89h, 74h, 24h, 14h, 85h, 0F6h, 0BFh, 00h, 00h, 0FFh, 0FFh, 75h, 38h, 8Bh
    db 84h, 24h, 0C0h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 0C4h, 00h, 00h, 00h, 8Bh, 94h, 24h
    db 0C8h, 00h, 00h, 00h, 89h, 44h, 24h, 40h, 8Bh, 84h, 24h, 0CCh, 00h, 00h, 00h, 89h
    db 4Ch, 24h, 44h, 8Bh, 8Ch, 24h, 0D0h, 00h, 00h, 00h, 89h, 54h, 24h, 48h, 8Bh, 94h
    db 24h, 0D4h, 00h, 00h, 00h, 0EBh, 78h, 83h, 0FEh, 01h, 0BFh, 00h, 0FFh, 00h, 0FFh, 75h
    db 38h, 8Bh, 84h, 24h, 0DCh, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 0E0h, 00h, 00h, 00h, 8Bh
    db 94h, 24h, 0E4h, 00h, 00h, 00h, 89h, 44h, 24h, 40h, 8Bh, 84h, 24h, 0E8h, 00h, 00h
    db 00h, 89h, 4Ch, 24h, 44h, 8Bh, 8Ch, 24h, 0ECh, 00h, 00h, 00h, 89h, 54h, 24h, 48h
    db 8Bh, 94h, 24h, 0F0h, 00h, 00h, 00h, 0EBh, 36h, 8Bh, 84h, 24h, 0F4h, 00h, 00h, 00h
    db 8Bh, 8Ch, 24h, 0F8h, 00h, 00h, 00h, 8Bh, 94h, 24h, 0FCh, 00h, 00h, 00h, 89h, 44h
    db 24h, 40h, 8Bh, 84h, 24h, 00h, 01h, 00h, 00h, 89h, 4Ch, 24h, 44h, 8Bh, 8Ch, 24h
    db 04h, 01h, 00h, 00h, 89h, 54h, 24h, 48h, 8Bh, 94h, 24h, 08h, 01h, 00h, 00h, 89h
    db 4Ch, 24h, 50h, 8Dh, 4Ch, 24h, 70h, 89h, 54h, 24h, 54h, 51h, 8Dh, 54h, 24h, 50h
    db 89h, 44h, 24h, 50h, 8Bh, 45h, 00h, 52h, 8Bh, 0CDh, 0FFh, 90h, 5Ch, 01h, 00h, 00h
    db 8Bh, 0D8h, 8Bh, 45h, 00h, 8Dh, 8Ch, 24h, 94h, 00h, 00h, 00h, 0F7h, 0DBh, 51h, 8Dh
    db 54h, 24h, 44h, 1Ah, 0DBh, 52h, 8Bh, 0CDh, 0FEh, 0C3h, 0FFh, 90h, 5Ch, 01h, 00h, 00h
    db 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 84h, 0DBh, 0Fh, 84h, 0A4h, 00h, 00h, 00h, 84h, 0C0h
    db 0Fh, 84h, 9Ch, 00h, 00h, 00h, 8Dh, 84h, 24h, 0A0h, 00h, 00h, 00h, 50h, 8Dh, 8Ch
    db 24h, 80h, 00h, 00h, 00h, 51h, 8Dh, 94h, 24h, 8Ch, 00h, 00h, 00h, 52h, 8Dh, 44h
    db 24h, 7Ch, 50h, 8Dh, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 51h, 0E8h, 0F3h, 1Dh, 8Ch, 0FFh
    db 83h, 0C4h, 14h, 84h, 0C0h, 74h, 6Bh, 0DBh, 84h, 24h, 80h, 00h, 00h, 00h, 8Bh, 0Dh
    db 70h, 12h, 2Fh, 01h, 8Bh, 11h, 8Bh, 0F1h, 0D9h, 5Ch, 24h, 24h, 0DBh, 44h, 24h, 7Ch
    db 0D9h, 5Ch, 24h, 1Ch, 0DBh, 84h, 24h, 88h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 30h, 0DBh
    db 84h, 24h, 84h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 3Ch, 0FFh, 92h, 0B0h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 1Ch, 8Bh, 06h, 57h, 68h, 00h, 00h, 80h, 3Fh
    db 51h, 8Bh, 4Ch, 24h, 3Ch, 52h, 8Bh, 54h, 24h, 4Ch, 51h, 52h, 8Bh, 0CEh, 0FFh, 90h
    db 0B8h, 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 0DCh, 00h, 00h, 00h, 8Bh, 74h
    db 24h, 14h, 46h, 83h, 0FEh, 03h, 89h, 74h, 24h, 14h, 0Fh, 8Ch, 46h, 0FEh, 0FFh, 0FFh
    db 8Bh, 4Ch, 24h, 2Ch, 8Bh, 41h, 04h, 85h, 0C0h, 89h, 44h, 24h, 2Ch, 0Fh, 85h, 0Ch
    db 0FEh, 0FFh, 0FFh, 8Bh, 15h, 64h, 14h, 2Fh, 01h, 8Bh, 0BCh, 24h, 9Ch, 00h, 00h, 00h
    db 33h, 0F6h, 89h, 0B2h, 0C0h, 00h, 00h, 00h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 01h
    db 8Dh, 97h, 04h, 0FFh, 0FFh, 0FFh, 52h, 68h, 0D0h, 0AEh, 0B3h, 00h, 0FFh, 50h, 58h, 90h
    db 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 56h, 0E8h, 84h, 0E7h, 8Ch, 0FFh, 46h, 83h, 0FEh, 0Ah
    db 7Ch, 0EEh, 8Bh, 47h, 0Ch, 8Bh, 0Dh, 5Ch, 80h, 2Fh, 01h, 50h, 0E8h, 0BAh, 92h, 8Ch
    db 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 8Bh
?d_0073e050@@YAXXZ ENDP

; ghidra: FUN_00b3fa90  retail @ 0x0073FA90 size 336
_TEXT ENDS
_TEXT$d00b3fa90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B3FA90 size 336
public ?d_0073fa90@@YAXXZ
?d_0073fa90@@YAXXZ PROC
    db 08Bh, 044h, 024h, 008h, 083h, 0ECh, 00Ch, 083h, 0F8h, 001h, 056h, 08Bh, 0F1h, 0C7h, 086h, 0BCh
    db 001h, 000h, 000h, 000h, 000h, 000h, 000h, 0C6h, 086h, 0C8h, 001h, 000h, 000h, 000h, 07Dh, 009h
    db 0B8h, 001h, 000h, 000h, 000h, 089h, 044h, 024h, 018h, 099h, 0F7h, 03Dh
    dd ?TheW3DFrameLengthInMsec@@3HA
    db 083h, 0F8h, 001h, 089h, 086h, 0ACh, 001h, 000h, 000h, 07Dh, 00Ah, 0C7h, 086h, 0ACh, 001h, 000h
    db 000h, 001h, 000h, 000h, 000h, 0D9h, 046h, 00Ch, 08Bh, 044h, 024h, 014h, 0D9h, 046h, 010h, 0D9h
    db 000h, 0D8h, 0E2h, 0D9h, 05Ch, 024h, 008h, 0D9h, 040h, 004h, 0D8h, 0E1h, 0D9h, 05Ch, 024h, 00Ch
    db 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 00Ch, 0D8h, 04Ch, 024h, 00Ch, 0D9h, 044h, 024h, 008h
    db 0D8h, 04Ch, 024h, 008h, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 004h, 0D9h, 044h, 024h, 004h, 0D9h, 0FAh
    db 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 014h, 0D8h, 01Dh
    dd ?g_bfmeScaleBK@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 0B0h, 000h, 000h, 000h, 0D9h, 044h, 024h, 008h, 0D8h
    db 074h, 024h, 014h
    call ?Rva009F7256_CIacos@@YAXXZ
    db 0D9h, 044h, 024h, 00Ch, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 002h, 0D9h, 0E0h, 0D8h, 025h
    dd ?g_bfmeDefaultEG@@3MA
    db 08Dh, 04Ch, 024h, 014h, 0D9h, 05Ch, 024h, 014h
    call ?normAngle@@YIXAAM@Z
    db 08Ah, 044h, 024h, 024h, 084h, 0C0h, 074h, 022h, 0D9h, 046h, 028h, 0D8h, 05Ch, 024h, 014h, 0D9h
    db 044h, 024h, 014h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0D8h, 025h
    dd ?g_bfmeAngleTwoPi@@3MA
    db 0EBh, 00Ch, 0D8h, 005h
    dd ?g_bfmeAngleTwoPi@@3MA
    db 0EBh, 004h, 0D9h, 044h, 024h, 014h, 08Bh, 046h, 028h, 0D9h, 09Eh, 0D0h, 001h, 000h, 000h, 0DBh
    db 044h, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 051h, 08Bh, 04Ch, 024h, 024h, 0D9h, 01Ch, 024h, 051h
    db 089h, 086h, 0CCh, 001h, 000h, 000h, 08Bh, 086h, 0C4h, 023h, 000h, 000h, 052h, 08Dh, 08Eh, 0C0h
    db 001h, 000h, 000h, 0C7h, 086h, 0B0h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 0C6h, 086h, 0DCh
    db 001h, 000h, 000h, 001h, 089h, 086h, 0B4h, 001h, 000h, 000h, 089h, 086h, 0B8h, 001h, 000h, 000h
    call ?j_0002a1b2@@YAXXZ
    db 05Eh, 083h, 0C4h, 00Ch, 0C2h, 014h, 000h
?d_0073fa90@@YAXXZ ENDP
_TEXT$d00b3fa90 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b401a0  retail @ 0x007401A0 size 528
public ?d_007401a0@@YAXXZ
?d_007401a0@@YAXXZ PROC
    db 83h, 0ECh, 40h, 57h, 8Bh, 0F9h, 8Ah, 87h, 0DCh, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h
    db 0F5h, 01h, 00h, 00h, 83h, 0BFh, 54h, 23h, 00h, 00h, 01h, 0Fh, 85h, 0E8h, 01h, 00h
    db 00h, 8Bh, 8Fh, 0F0h, 22h, 00h, 00h, 8Dh, 41h, 0FFh, 83h, 0F8h, 02h, 7Fh, 05h, 0B8h
    db 02h, 00h, 00h, 00h, 3Bh, 0C1h, 53h, 8Bh, 0D8h, 0Fh, 8Fh, 0C9h, 01h, 00h, 00h, 55h
    db 8Dh, 0ACh, 87h, 0E8h, 16h, 00h, 00h, 8Dh, 04h, 80h, 56h, 8Dh, 0B4h, 87h, 0ACh, 02h
    db 00h, 00h, 8Dh, 4Eh, 0ECh, 8Bh, 11h, 8Bh, 41h, 04h, 8Bh, 49h, 08h, 89h, 54h, 24h
    db 20h, 0D9h, 44h, 24h, 20h, 0D8h, 06h, 89h, 44h, 24h, 24h, 0D9h, 44h, 24h, 24h, 8Bh
    db 0D6h, 0D8h, 46h, 04h, 8Bh, 02h, 0D9h, 0C9h, 89h, 44h, 24h, 38h, 0D8h, 0Dh, 3Ch, 53h
    db 07h, 01h, 89h, 4Ch, 24h, 28h, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 0D9h, 5Ch, 24h, 20h
    db 89h, 4Ch, 24h, 3Ch, 8Bh, 0C6h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 8Bh, 08h, 89h, 4Ch
    db 24h, 2Ch, 0D9h, 44h, 24h, 2Ch, 0D8h, 46h, 14h, 89h, 54h, 24h, 40h, 8Bh, 50h, 04h
    db 89h, 54h, 24h, 30h, 0D9h, 44h, 24h, 30h, 0D8h, 46h, 18h, 8Bh, 40h, 08h, 0D9h, 0C9h
    db 89h, 44h, 24h, 34h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 8Bh, 44h, 24h, 54h, 0D9h, 5Ch
    db 24h, 2Ch, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 44h, 24h, 2Ch, 0D8h, 64h, 24h, 20h
    db 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D8h, 44h, 24h, 20h, 0D9h, 0C1h, 0D8h, 0E3h, 0D8h, 0Dh
    db 3Ch, 53h, 07h, 01h, 0D8h, 0C3h, 0D9h, 5Ch, 24h, 48h, 0D9h, 44h, 24h, 38h, 0D8h, 64h
    db 24h, 2Ch, 0D8h, 44h, 24h, 38h, 0D8h, 64h, 24h, 20h, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h
    db 0D8h, 0C1h, 0D9h, 5Ch, 24h, 44h, 0DDh, 0D8h, 0D9h, 44h, 24h, 3Ch, 0D8h, 0E1h, 0D8h, 44h
    db 24h, 3Ch, 0DEh, 0E2h, 0D9h, 0C9h, 0D8h, 0Dh, 6Ch, 3Bh, 08h, 01h, 0D8h, 44h, 24h, 48h
    db 0DDh, 0D9h, 0D9h, 00h, 0D8h, 64h, 24h, 44h, 0D9h, 5Ch, 24h, 18h, 0D9h, 40h, 04h, 0D8h
    db 0E1h, 0D9h, 5Ch, 24h, 1Ch, 0DDh, 0D8h, 0D9h, 44h, 24h, 1Ch, 0D8h, 4Ch, 24h, 1Ch, 0D9h
    db 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h
    db 10h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 14h, 0D8h, 1Dh, 70h, 5Ch, 07h
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 79h, 0D9h, 44h, 24h, 18h, 0D8h, 74h, 24h, 14h
    db 0E8h, 31h, 6Fh, 2Bh, 00h, 0D9h, 44h, 24h, 1Ch, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 05h, 7Ah, 02h, 0D9h, 0E0h, 0D8h, 25h, 14h, 71h, 09h, 01h, 8Dh, 4Ch
    db 24h, 10h, 0D9h, 5Ch, 24h, 10h, 0E8h, 0B5h, 0A5h, 0FFh, 0FFh, 3Bh, 9Fh, 0F0h, 22h, 00h
    db 00h, 75h, 09h, 8Bh, 4Ch, 24h, 10h, 89h, 4Dh, 00h, 0EBh, 35h, 0D9h, 44h, 24h, 10h
    db 8Dh, 4Ch, 24h, 10h, 0D8h, 65h, 00h, 0D9h, 5Ch, 24h, 10h, 0E8h, 90h, 0A5h, 0FFh, 0FFh
    db 0D9h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 10h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D8h, 45h
    db 00h, 0D9h, 5Ch, 24h, 10h, 0E8h, 76h, 0A5h, 0FFh, 0FFh, 8Bh, 54h, 24h, 10h, 89h, 55h
    db 00h, 8Bh, 87h, 0F0h, 22h, 00h, 00h, 43h, 83h, 0C5h, 04h, 83h, 0C6h, 14h, 3Bh, 0D8h
    db 0Fh, 8Eh, 4Ch, 0FEh, 0FFh, 0FFh, 5Eh, 5Dh, 5Bh, 5Fh, 83h, 0C4h, 40h, 0C2h, 04h, 00h
?d_007401a0@@YAXXZ ENDP

; ghidra: FUN_00b40440  retail @ 0x00740440 size 347
public ?d_00740440@@YAXXZ
?d_00740440@@YAXXZ PROC
    db 83h, 0ECh, 10h, 56h, 57h, 8Bh, 0F9h, 8Ah, 4Ch, 24h, 1Ch, 84h, 0C9h, 8Dh, 87h, 68h
    db 14h, 00h, 00h, 89h, 44h, 24h, 0Ch, 8Bh, 0F0h, 0Fh, 84h, 18h, 01h, 00h, 00h, 8Bh
    db 8Fh, 70h, 20h, 00h, 00h, 53h, 0BBh, 02h, 00h, 00h, 00h, 03h, 0CBh, 83h, 0C6h, 04h
    db 3Bh, 0CBh, 0Fh, 8Eh, 0E8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 28h, 8Dh, 14h, 80h, 8Dh
    db 44h, 97h, 54h, 55h, 8Dh, 6Fh, 54h, 89h, 44h, 24h, 2Ch, 0EBh, 04h, 8Bh, 44h, 24h
    db 2Ch, 0D9h, 45h, 00h, 0D8h, 20h, 0D9h, 5Ch, 24h, 18h, 0D9h, 45h, 04h, 0D8h, 60h, 04h
    db 0D9h, 54h, 24h, 1Ch, 0D8h, 4Ch, 24h, 1Ch, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h
    db 0DEh, 0C1h, 0D9h, 5Ch, 24h, 24h, 0D9h, 44h, 24h, 24h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 10h
    db 0D9h, 44h, 24h, 18h, 0D8h, 74h, 24h, 10h, 0D9h, 54h, 24h, 24h, 0D8h, 1Dh, 3Ch, 0BFh
    db 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0C7h, 44h, 24h, 24h, 00h, 00h, 80h
    db 0BFh, 0EBh, 19h, 0D9h, 44h, 24h, 24h, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 08h, 0C7h, 44h, 24h, 24h, 00h, 00h, 80h, 3Fh, 0D9h, 44h, 24h, 1Ch
    db 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 24h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 09h, 0E8h, 40h, 6Dh, 2Bh, 00h, 0D9h, 0E0h, 0EBh, 05h, 0E8h, 37h, 6Dh, 2Bh, 00h, 0D8h
    db 25h, 14h, 71h, 09h, 01h, 8Dh, 4Ch, 24h, 24h, 0D9h, 5Ch, 24h, 24h, 0E8h, 0CEh, 0A3h
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 24h, 89h, 06h, 8Bh, 44h, 24h, 2Ch, 8Bh, 8Fh, 70h, 20h
    db 00h, 00h, 83h, 0C6h, 04h, 43h, 83h, 0C0h, 14h, 83h, 0C1h, 02h, 83h, 0C5h, 14h, 3Bh
    db 0D9h, 89h, 44h, 24h, 2Ch, 0Fh, 8Ch, 32h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 14h, 5Dh
    db 8Bh, 54h, 24h, 24h, 5Bh, 89h, 97h, 6Ch, 14h, 00h, 00h, 8Bh, 0CAh, 5Fh, 89h, 08h
    db 5Eh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 8Bh, 97h, 70h, 20h, 00h, 00h, 8Dh, 0Ch, 96h
    db 3Bh, 0F1h, 8Bh, 0C6h, 74h, 0Dh, 8Bh, 54h, 24h, 20h, 89h, 10h, 83h, 0C0h, 04h, 3Bh
    db 0C1h, 75h, 0F3h, 5Fh, 5Eh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_00740440@@YAXXZ ENDP

; ghidra: FUN_00b40600  retail @ 0x00740600 size 140
public ?d_00740600@@YAXXZ
?d_00740600@@YAXXZ PROC
    db 83h, 0ECh, 38h, 56h, 8Bh, 0F1h, 8Bh, 86h, 0A0h, 01h, 00h, 00h, 8Bh, 8Eh, 9Ch, 01h
    db 00h, 00h, 3Bh, 0C1h, 89h, 44h, 24h, 04h, 89h, 4Ch, 24h, 08h, 7Fh, 51h, 0DBh, 44h
    db 24h, 04h, 51h, 8Dh, 8Eh, 0A4h, 01h, 00h, 00h, 0DAh, 74h, 24h, 0Ch, 0D9h, 1Ch, 24h
    db 0E8h, 8Ah, 3Ch, 90h, 0FFh, 0D9h, 5Ch, 24h, 08h, 8Dh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h
    db 08h, 50h, 51h, 8Dh, 96h, 6Ch, 01h, 00h, 00h, 52h, 8Dh, 86h, 3Ch, 01h, 00h, 00h
    db 50h, 0E8h, 2Ah, 7Eh, 19h, 00h, 8Bh, 8Eh, 04h, 01h, 00h, 00h, 8Bh, 11h, 83h, 0C4h
    db 10h, 8Dh, 44h, 24h, 0Ch, 50h, 0FFh, 52h, 54h, 0FFh, 86h, 0A0h, 01h, 00h, 00h, 8Bh
    db 8Eh, 0A0h, 01h, 00h, 00h, 3Bh, 8Eh, 9Ch, 01h, 00h, 00h, 7Ch, 0Ah, 0C7h, 86h, 54h
    db 23h, 00h, 00h, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 38h, 0C3h
?d_00740600@@YAXXZ ENDP

; ghidra: FUN_00b40970  retail @ 0x00740970 size 32
public ?d_00740970@@YAXXZ
?d_00740970@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 0Ch, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 0D7h, 71h, 14h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_00740970@@YAXXZ ENDP

; ghidra: FUN_00b409a0  retail @ 0x007409A0 size 126
public ?d_007409a0@@YAXXZ
?d_007409a0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 18h, 0DAh, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 57h, 8Bh, 7Ch, 24h, 18h, 8Bh, 0F1h, 3Bh, 0F7h, 74h
    db 48h, 8Dh, 44h, 24h, 18h, 50h, 8Bh, 0CFh, 0E8h, 0B9h, 19h, 8Eh, 0FFh, 8Dh, 4Eh, 0Ch
    db 50h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0E8h, 0B2h, 72h, 14h, 00h, 8Dh, 4Ch
    db 24h, 18h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 51h, 6Fh, 14h, 00h, 8Bh
    db 0CFh, 8Bh, 01h, 8Bh, 0D6h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h, 8Bh, 49h, 08h
    db 89h, 4Ah, 08h, 8Bh, 57h, 10h, 89h, 56h, 10h, 8Bh, 4Ch, 24h, 08h, 5Fh, 8Bh, 0C6h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_007409a0@@YAXXZ ENDP

; ghidra: FUN_00b40ae0  retail @ 0x00740AE0 size 160
public ?d_00740ae0@@YAXXZ
?d_00740ae0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 71h, 0DAh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 68h, 00h, 00h, 80h, 3Fh, 8Bh, 0F1h, 33h
    db 0DBh, 53h, 8Dh, 4Eh, 10h, 53h, 89h, 74h, 24h, 14h, 0C7h, 06h, 50h, 74h, 0Ch, 01h
    db 0E8h, 9Dh, 96h, 8Eh, 0FFh, 89h, 5Eh, 04h, 89h, 5Eh, 08h, 89h, 5Eh, 18h, 89h, 5Eh
    db 1Ch, 89h, 5Eh, 20h, 88h, 5Eh, 24h, 89h, 5Eh, 28h, 68h, 2Ah, 0DFh, 41h, 00h, 68h
    db 0CFh, 0ABh, 43h, 00h, 68h, 0FFh, 00h, 00h, 00h, 6Ah, 14h, 8Dh, 46h, 2Ch, 50h, 89h
    db 5Ch, 24h, 28h, 0C7h, 06h, 1Ch, 17h, 12h, 01h, 0E8h, 96h, 63h, 2Bh, 00h, 68h, 2Ah
    db 0DFh, 41h, 00h, 68h, 0CFh, 0ABh, 43h, 00h, 6Ah, 04h, 6Ah, 14h, 8Dh, 8Eh, 18h, 14h
    db 00h, 00h, 51h, 0C6h, 44h, 24h, 28h, 01h, 0E8h, 77h, 63h, 2Bh, 00h, 8Bh, 4Ch, 24h
    db 0Ch, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00740ae0@@YAXXZ ENDP

; ghidra: FUN_00b40bc0  retail @ 0x00740BC0 size 106
public ?d_00740bc0@@YAXXZ
?d_00740bc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B1h, 0DAh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 68h, 2Ah, 0DFh
    db 41h, 00h, 6Ah, 04h, 6Ah, 14h, 8Dh, 86h, 18h, 14h, 00h, 00h, 50h, 0C7h, 44h, 24h
    db 20h, 01h, 00h, 00h, 00h, 0E8h, 7Ch, 61h, 2Bh, 00h, 68h, 2Ah, 0DFh, 41h, 00h, 68h
    db 0FFh, 00h, 00h, 00h, 6Ah, 14h, 8Dh, 4Eh, 2Ch, 51h, 0C6h, 44h, 24h, 20h, 00h, 0E8h
    db 62h, 61h, 2Bh, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 50h, 74h, 0Ch, 01h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00740bc0@@YAXXZ ENDP

; ghidra: FUN_00b40c80  retail @ 0x00740C80 size 83
public ?d_00740c80@@YAXXZ
?d_00740c80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DEh, 0DAh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 8Eh, 0B0h
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 90h, 6Ch, 14h, 00h
    db 8Dh, 8Eh, 0ACh, 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 7Dh
    db 6Ch, 14h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_00740c80@@YAXXZ ENDP

; ghidra: FUN_00b40f60  retail @ 0x00740F60 size 599
_TEXT ENDS
_TEXT$d00b40f60 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B40F60 size 599
public ?d_00740f60@@YAXXZ
?d_00740f60@@YAXXZ PROC
    db 08Bh, 054h, 024h, 00Ch, 083h, 0ECh, 00Ch, 053h, 055h, 056h, 057h, 06Ah, 001h, 08Bh, 0F1h, 08Bh
    db 04Ch, 024h, 030h, 08Bh, 086h, 080h, 002h, 000h, 000h, 033h, 0DBh, 053h, 051h, 08Bh, 04Ch, 024h
    db 02Ch, 052h, 08Bh, 096h, 0C4h, 023h, 000h, 000h, 051h, 08Dh, 0BEh, 080h, 002h, 000h, 000h, 052h
    db 08Bh, 0CFh, 0FFh, 050h, 008h, 08Bh, 086h, 0F0h, 022h, 000h, 000h, 0B9h, 001h, 000h, 000h, 000h
    db 03Bh, 0C1h, 089h, 09Eh, 0E8h, 01Eh, 000h, 000h, 07Eh, 05Ah, 08Dh, 096h, 0E8h, 01Ah, 000h, 000h
    db 08Dh, 086h, 0C4h, 002h, 000h, 000h, 0D9h, 040h, 010h, 0D8h, 060h, 0FCh, 0D9h, 040h, 014h, 0D8h
    db 020h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 028h, 0DDh
    db 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 028h, 0D9h, 0FAh, 0D9h, 05Ch, 024h, 02Ch, 08Bh, 06Ch, 024h
    db 02Ch, 0D9h, 044h, 024h, 02Ch, 089h, 02Ah, 0D8h, 086h, 0E8h, 01Eh, 000h, 000h, 041h, 083h, 0C2h
    db 004h, 0D9h, 09Eh, 0E8h, 01Eh, 000h, 000h, 08Bh, 0AEh, 0F0h, 022h, 000h, 000h, 083h, 0C0h, 014h
    db 03Bh, 0CDh, 07Ch, 0B2h, 08Bh, 086h, 0F0h, 022h, 000h, 000h, 089h, 09Eh, 0E4h, 01Ah, 000h, 000h
    db 089h, 09Ch, 086h, 0E4h, 01Ah, 000h, 000h, 08Bh, 08Eh, 0F0h, 022h, 000h, 000h, 089h, 09Ch, 08Eh
    db 0E8h, 01Ah, 000h, 000h, 08Bh, 016h, 06Ah, 0FFh, 08Bh, 0CEh, 0FFh, 092h, 0FCh, 000h, 000h, 000h
    db 08Bh, 044h, 024h, 028h, 051h, 0D9h, 01Ch, 024h, 050h, 08Bh, 0CFh
    call ?j_00020266@@YAXXZ
    db 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 0FCh, 000h, 000h, 000h, 08Bh, 087h, 070h, 020h, 000h, 000h
    db 0D9h, 09Fh, 06Ch, 014h, 000h, 000h, 08Bh, 08Ch, 087h, 068h, 014h, 000h, 000h, 089h, 08Ch, 087h
    db 06Ch, 014h, 000h, 000h, 08Bh, 097h, 06Ch, 014h, 000h, 000h, 08Dh, 084h, 087h, 070h, 014h, 000h
    db 000h, 089h, 097h, 068h, 014h, 000h, 000h, 08Bh, 086h, 0F0h, 022h, 000h, 000h, 08Bh, 08Ch, 086h
    db 0E4h, 016h, 000h, 000h, 089h, 08Ch, 086h, 0E8h, 016h, 000h, 000h, 08Bh, 086h, 0F0h, 022h, 000h
    db 000h, 08Bh, 094h, 086h, 0E8h, 016h, 000h, 000h, 089h, 094h, 086h, 0ECh, 016h, 000h, 000h, 08Bh
    db 086h, 0F0h, 022h, 000h, 000h, 08Dh, 048h, 0FFh, 08Dh, 041h, 0FFh, 083h, 0F8h, 004h, 07Ch, 056h
    db 08Dh, 051h, 0FBh, 0C1h, 0EAh, 002h, 042h, 08Bh, 0FAh, 0F7h, 0DFh, 08Dh, 084h, 08Eh, 0E4h, 016h
    db 000h, 000h, 08Dh, 00Ch, 0B9h, 0D9h, 000h, 083h, 0E8h, 010h, 04Ah, 0D8h, 040h, 014h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 058h, 014h, 0D9h, 040h, 010h, 0D8h, 040h, 00Ch, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 058h, 010h, 0D9h, 040h, 00Ch, 0D8h, 040h, 008h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 058h, 00Ch, 0D9h, 040h, 004h, 0D8h, 040h, 008h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 058h, 008h, 075h, 0BFh, 083h, 0F9h, 001h, 07Eh, 01Dh, 08Dh, 084h, 08Eh, 0E8h, 016h, 000h
    db 000h, 049h, 0D9h, 040h, 0FCh, 083h, 0C0h, 0FCh, 049h, 0D8h, 040h, 004h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 058h, 004h, 075h, 0EBh, 08Bh, 086h, 0F0h, 022h, 000h, 000h, 08Dh, 00Ch, 080h, 08Bh, 094h
    db 08Eh, 0ACh, 002h, 000h, 000h, 08Dh, 084h, 08Eh, 0ACh, 002h, 000h, 000h, 08Bh, 040h, 004h, 08Bh
    db 08Eh, 0F8h, 023h, 000h, 000h, 053h, 089h, 054h, 024h, 014h, 08Bh, 06Ch, 024h, 014h, 089h, 08Eh
    db 0ECh, 01Eh, 000h, 000h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 08Bh, 0F8h, 057h, 055h, 089h, 044h, 024h, 020h, 0FFh, 052h, 018h, 0D9h, 09Eh, 0F0h
    db 01Eh, 000h, 000h, 038h, 09Eh, 064h, 024h, 000h, 000h, 074h, 013h, 057h, 055h, 08Dh, 08Eh, 048h
    db 024h, 000h, 000h
    call ?j_00046fa1@@YAXXZ
    db 0D9h, 09Eh, 0F0h, 01Eh, 000h, 000h, 08Bh, 08Eh, 0F0h, 022h, 000h, 000h, 08Bh, 016h, 033h, 0C0h
    db 083h, 0F9h, 001h, 00Fh, 09Fh, 0C0h, 053h, 08Bh, 0CEh, 089h, 086h, 054h, 023h, 000h, 000h, 0FFh
    db 052h, 06Ch, 05Fh, 088h, 09Eh, 0DCh, 001h, 000h, 000h, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h
    db 010h, 000h
?d_00740f60@@YAXXZ ENDP
_TEXT$d00b40f60 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b41360  retail @ 0x00741360 size 545
_TEXT ENDS
_TEXT$d00b41360 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B41360 size 545
public ?d_00741360@@YAXXZ
?d_00741360@@YAXXZ PROC
    db 083h, 0ECh, 010h, 053h, 08Ah, 05Ch, 024h, 01Ch, 084h, 0DBh, 056h, 057h, 08Bh, 0F9h, 08Dh, 0B7h
    db 058h, 023h, 000h, 000h, 075h, 006h, 08Dh, 0B7h, 0F4h, 022h, 000h, 000h, 08Ah, 046h, 024h, 084h
    db 0C0h, 00Fh, 084h, 0F1h, 001h, 000h, 000h, 08Bh, 046h, 008h, 08Bh, 04Ch, 024h, 020h, 089h, 044h
    db 024h, 00Ch, 0DBh, 044h, 024h, 00Ch, 003h, 0C1h, 089h, 046h, 008h, 08Bh, 015h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Ah, 08Ah, 074h, 00Ah, 000h, 000h, 0D9h, 05Ch, 024h, 00Ch, 084h, 0C9h, 08Bh, 04Eh, 004h, 074h
    db 018h, 03Bh, 0C1h, 00Fh, 08Eh, 0BEh, 001h, 000h, 000h, 0C6h, 087h, 0C0h, 023h, 000h, 000h, 000h
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 03Bh, 0C1h, 055h, 00Fh, 08Eh, 001h, 001h
    db 000h, 000h, 084h, 0DBh, 075h, 02Dh, 08Ah, 046h, 045h, 084h, 0C0h, 075h, 026h, 08Bh, 01Fh, 08Dh
    db 06Eh, 02Ch, 08Bh, 0CDh
    call ?j_000023f6@@YAXXZ
    db 069h, 0C0h, 0B8h, 000h, 000h, 000h, 08Bh, 04Dh, 000h, 08Bh, 094h, 008h, 044h, 0FFh, 0FFh, 0FFh
    db 052h, 08Bh, 0CFh, 0FFh, 053h, 06Ch, 08Ah, 05Ch, 024h, 028h, 0C6h, 087h, 0C0h, 023h, 000h, 000h
    db 000h, 08Bh, 046h, 02Ch, 08Bh, 04Eh, 030h, 02Bh, 0C8h, 0B8h, 0C9h, 042h, 016h, 0B2h, 0F7h, 0E9h
    db 003h, 0D1h, 08Bh, 04Eh, 02Ch, 0C1h, 0FAh, 007h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 069h
    db 0C0h, 0B8h, 000h, 000h, 000h, 084h, 0DBh, 08Bh, 094h, 008h, 034h, 0FFh, 0FFh, 0FFh, 08Dh, 084h
    db 008h, 034h, 0FFh, 0FFh, 0FFh, 08Bh, 048h, 004h, 089h, 054h, 024h, 014h, 08Bh, 050h, 008h, 089h
    db 04Ch, 024h, 018h, 089h, 054h, 024h, 01Ch, 074h, 01Ch, 08Bh, 04Ch, 024h, 014h, 08Bh, 054h, 024h
    db 018h, 08Dh, 087h, 03Ch, 024h, 000h, 000h, 089h, 008h, 08Bh, 04Ch, 024h, 01Ch, 089h, 050h, 004h
    db 089h, 048h, 008h, 0EBh, 042h, 08Bh, 044h, 024h, 014h, 08Bh, 06Ch, 024h, 018h, 08Bh, 04Ch, 024h
    db 01Ch, 08Dh, 057h, 00Ch, 089h, 002h, 089h, 06Ah, 004h, 089h, 04Ah, 008h, 08Dh, 097h, 004h, 024h
    db 000h, 000h, 052h, 050h, 08Dh, 087h, 0FCh, 023h, 000h, 000h, 050h
    call ?j_00012931@@YAXXZ
    db 08Dh, 08Fh, 008h, 024h, 000h, 000h, 051h, 08Dh, 097h, 000h, 024h, 000h, 000h, 055h, 052h
    call ?j_00012931@@YAXXZ
    db 083h, 0C4h, 018h, 08Ah, 046h, 045h, 084h, 0C0h, 075h, 004h, 0C6h, 046h, 045h, 001h, 08Bh, 04Eh
    db 008h, 08Bh, 044h, 024h, 024h, 02Bh, 0C8h, 089h, 04Ch, 024h, 028h, 0DBh, 044h, 024h, 028h, 089h
    db 04Eh, 008h, 0D9h, 05Ch, 024h, 010h, 0DBh, 046h, 004h, 051h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Dh, 06Eh, 010h, 08Bh, 0CDh, 0D8h, 0F1h, 0D9h, 05Ch, 024h, 02Ch, 0DDh, 0D8h, 0DBh, 046h, 008h
    db 0D8h, 04Ch, 024h, 02Ch, 0D9h, 01Ch, 024h
    call ?j_000442bf@@YAXXZ
    db 0D9h, 05Ch, 024h, 024h, 051h, 0D9h, 044h, 024h, 02Ch, 08Bh, 0CDh, 0D8h, 04Ch, 024h, 014h, 0D9h
    db 01Ch, 024h
    call ?j_000442bf@@YAXXZ
    db 0D8h, 06Ch, 024h, 024h, 08Ah, 046h, 046h, 084h, 0C0h, 05Dh, 0D8h, 04Eh, 038h, 0D8h, 046h, 018h
    db 0D9h, 05Eh, 018h, 074h, 015h, 08Bh, 056h, 008h, 08Bh, 04Eh, 00Ch, 033h, 0C0h, 03Bh, 0D1h, 089h
    db 046h, 018h, 07Eh, 006h, 088h, 046h, 046h, 089h, 046h, 008h, 08Ah, 046h, 045h, 084h, 0C0h, 075h
    db 014h, 08Bh, 00Dh
    dd ?g_bfmeMgrGK@@3PAVBfmeMgrGK@@A
    db 084h, 0DBh, 00Fh, 094h, 0C0h, 06Ah, 000h, 050h, 056h
    call ?j_000481fd@@YAXXZ
    db 083h, 0C6h, 048h, 084h, 0DBh, 08Bh, 00Eh, 074h, 008h, 081h, 0C7h, 03Ch, 024h, 000h, 000h, 0EBh
    db 003h, 083h, 0C7h, 00Ch, 089h, 00Fh, 08Bh, 056h, 004h, 089h, 057h, 004h, 08Bh, 046h, 008h, 089h
    db 047h, 008h, 05Fh, 05Eh, 05Bh, 083h, 0C4h, 010h, 0C2h, 008h, 000h
?d_00741360@@YAXXZ ENDP
_TEXT$d00b41360 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b41610  retail @ 0x00741610 size 124
public ?d_00741610@@YAXXZ
?d_00741610@@YAXXZ PROC
    db 83h, 0ECh, 18h, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 44h, 24h, 20h, 8Dh, 54h, 24h, 04h
    db 52h, 50h, 0E8h, 0F2h, 94h, 8Ch, 0FFh, 0D9h, 44h, 24h, 24h, 0D9h, 44h, 24h, 08h, 0D8h
    db 0E1h, 0D8h, 1Dh, 2Ch, 17h, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ch, 0DDh, 0D8h
    db 0D9h, 44h, 24h, 08h, 0D8h, 25h, 2Ch, 17h, 12h, 01h, 0D9h, 44h, 24h, 14h, 8Bh, 44h
    db 24h, 20h, 0D8h, 64h, 24h, 08h, 0D9h, 0C1h, 0D8h, 64h, 24h, 08h, 0D9h, 44h, 24h, 0Ch
    db 0D8h, 24h, 24h, 0D8h, 0F2h, 0D8h, 0C9h, 0D8h, 04h, 24h, 0D9h, 18h, 0D9h, 44h, 24h, 10h
    db 0D8h, 64h, 24h, 04h, 0D8h, 0F2h, 0D8h, 0C9h, 0D8h, 44h, 24h, 04h, 0D9h, 58h, 04h, 0DDh
    db 0D8h, 0DDh, 0D8h, 0D9h, 58h, 08h, 83h, 0C4h, 18h, 0C2h, 0Ch, 00h
?d_00741610@@YAXXZ ENDP

; ghidra: FUN_00b416e0  retail @ 0x007416E0 size 47
public ?d_007416e0@@YAXXZ
?d_007416e0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 26h, 8Bh, 4Ch, 24h, 08h, 8Bh, 11h, 89h, 10h
    db 8Bh, 51h, 04h, 89h, 50h, 04h, 8Bh, 51h, 08h, 89h, 50h, 08h, 8Bh, 51h, 0Ch, 89h
    db 50h, 0Ch, 8Bh, 51h, 10h, 89h, 50h, 10h, 8Ah, 49h, 14h, 88h, 48h, 14h, 0C3h
?d_007416e0@@YAXXZ ENDP

; ghidra: FUN_00b417a0  retail @ 0x007417A0 size 97
public ?d_007417a0@@YAXXZ
?d_007417a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 26h, 8Dh, 04h, 40h, 0C1h, 0E0h
    db 03h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 72h, 07h, 14h, 00h, 83h, 0C4h
    db 04h, 8Bh, 0E8h, 0EBh, 0Eh, 0E8h, 76h, 0CDh, 0Eh, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh
    db 02h, 33h, 0EDh, 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h
    db 8Bh, 0FDh, 2Bh, 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 11h, 32h, 8Fh, 0FFh, 83h, 0C6h
    db 18h, 83h, 0C4h, 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch
    db 00h
?d_007417a0@@YAXXZ ENDP

; ghidra: FUN_00b41830  retail @ 0x00741830 size 95
public ?d_00741830@@YAXXZ
?d_00741830@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 50h, 8Dh, 4Eh, 04h, 0C7h, 06h, 00h, 00h, 00h
    db 00h, 0E8h, 1Ah, 63h, 14h, 00h, 8Bh, 44h, 24h, 0Ch, 8Bh, 08h, 89h, 4Eh, 08h, 8Bh
    db 50h, 04h, 8Bh, 4Ch, 24h, 10h, 89h, 56h, 0Ch, 8Bh, 40h, 08h, 8Bh, 54h, 24h, 14h
    db 89h, 46h, 10h, 8Bh, 44h, 24h, 18h, 89h, 46h, 1Ch, 8Bh, 44h, 24h, 20h, 89h, 4Eh
    db 14h, 8Bh, 4Ch, 24h, 24h, 89h, 56h, 18h, 8Bh, 54h, 24h, 1Ch, 89h, 46h, 28h, 89h
    db 4Eh, 20h, 89h, 56h, 24h, 0C6h, 46h, 2Ch, 00h, 8Bh, 0C6h, 5Eh, 0C2h, 20h, 00h
?d_00741830@@YAXXZ ENDP

; ghidra: FUN_00b418b0  retail @ 0x007418B0 size 676
_TEXT ENDS
_TEXT$d00b418b0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B418B0 size 676
public ?d_007418b0@@YAXXZ
?d_007418b0@@YAXXZ PROC
    db 083h, 0ECh, 018h, 053h, 055h, 056h, 08Bh, 0F1h, 08Dh, 09Eh, 0ACh, 016h, 000h, 000h, 08Dh, 046h
    db 00Ch, 08Bh, 010h, 08Bh, 0CBh, 089h, 011h, 08Bh, 050h, 004h, 089h, 051h, 004h, 08Bh, 040h, 008h
    db 057h, 089h, 041h, 008h, 053h, 08Dh, 08Eh, 0C0h, 002h, 000h, 000h
    call ?j_0003a25b@@YAXXZ
    db 08Bh, 06Ch, 024h, 030h, 085h, 0EDh, 0C7h, 086h, 0E8h, 01Ah, 000h, 000h, 000h, 000h, 000h, 000h
    db 00Fh, 084h, 0C0h, 000h, 000h, 000h, 08Dh, 0BEh, 0C0h, 016h, 000h, 000h, 08Dh, 04Dh, 008h, 08Bh
    db 001h, 08Bh, 0D7h, 089h, 002h, 08Bh, 041h, 004h, 089h, 042h, 004h, 08Bh, 049h, 008h, 089h, 04Ah
    db 008h, 057h, 08Dh, 08Eh, 0D4h, 002h, 000h, 000h
    call ?j_0003a25b@@YAXXZ
    db 08Bh, 044h, 024h, 040h, 08Bh, 04Ch, 024h, 03Ch, 08Bh, 016h, 050h, 08Bh, 044h, 024h, 038h, 051h
    db 0C7h, 086h, 0ECh, 01Ah, 000h, 000h, 000h, 000h, 000h, 000h, 08Bh, 04Dh, 024h, 050h, 051h, 08Bh
    db 0CEh, 0FFh, 092h, 0E8h, 000h, 000h, 000h, 08Bh, 055h, 028h, 08Bh, 006h, 08Bh, 0CAh, 051h, 08Bh
    db 0CEh, 089h, 054h, 024h, 034h, 0FFh, 090h, 014h, 002h, 000h, 000h, 0D9h, 05Ch, 024h, 030h, 08Bh
    db 044h, 024h, 040h, 08Bh, 04Ch, 024h, 03Ch, 08Bh, 016h, 050h, 08Bh, 044h, 024h, 038h, 051h, 08Bh
    db 04Ch, 024h, 038h, 050h, 051h, 08Bh, 0CEh, 0FFh, 092h, 0ECh, 000h, 000h, 000h, 08Bh, 044h, 024h
    db 040h, 08Bh, 04Ch, 024h, 03Ch, 08Bh, 016h, 050h, 08Bh, 044h, 024h, 038h, 051h, 08Bh, 04Dh, 01Ch
    db 050h, 051h, 08Bh, 0CEh, 0FFh, 092h, 0F0h, 000h, 000h, 000h, 08Bh, 044h, 024h, 040h, 08Bh, 04Ch
    db 024h, 03Ch, 08Bh, 016h, 050h, 08Bh, 044h, 024h, 038h, 051h, 08Bh, 04Dh, 020h, 050h, 051h, 08Bh
    db 0CEh, 0FFh, 092h, 0F4h, 000h, 000h, 000h, 0EBh, 03Ah, 08Bh, 044h, 024h, 02Ch, 085h, 0C0h, 00Fh
    db 084h, 088h, 001h, 000h, 000h, 08Bh, 008h, 08Dh, 0BEh, 0C0h, 016h, 000h, 000h, 08Bh, 0D7h, 089h
    db 00Ah, 08Bh, 048h, 004h, 089h, 04Ah, 004h, 08Bh, 040h, 008h, 057h, 08Dh, 08Eh, 0D4h, 002h, 000h
    db 000h, 089h, 042h, 008h
    call ?j_0003a25b@@YAXXZ
    db 0C7h, 086h, 0ECh, 01Ah, 000h, 000h, 000h, 000h, 000h, 000h, 0D9h, 007h, 08Bh, 04Fh, 008h, 0D9h
    db 047h, 004h, 08Bh, 013h, 08Bh, 043h, 004h, 0D9h, 0C9h, 0D8h, 023h, 089h, 04Ch, 024h, 024h, 08Bh
    db 04Bh, 008h, 089h, 054h, 024h, 010h, 0D9h, 05Ch, 024h, 01Ch, 089h, 044h, 024h, 014h, 089h, 04Ch
    db 024h, 018h, 0D8h, 063h, 004h, 08Dh, 086h, 098h, 016h, 000h, 000h, 08Bh, 0D0h, 050h, 0D9h, 05Ch
    db 024h, 024h, 0D9h, 044h, 024h, 028h, 0D8h, 063h, 008h, 0D9h, 05Ch, 024h, 028h, 0D9h, 044h, 024h
    db 014h, 0D8h, 064h, 024h, 020h, 0D9h, 05Ch, 024h, 014h, 08Bh, 04Ch, 024h, 014h, 0D9h, 044h, 024h
    db 018h, 089h, 00Ah, 0D8h, 064h, 024h, 024h, 0D9h, 05Ch, 024h, 018h, 08Bh, 04Ch, 024h, 018h, 0D9h
    db 044h, 024h, 01Ch, 089h, 04Ah, 004h, 0D8h, 064h, 024h, 028h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 04Ch
    db 024h, 01Ch, 089h, 04Ah, 008h, 08Dh, 08Eh, 0ACh, 002h, 000h, 000h
    call ?j_0003a25b@@YAXXZ
    db 08Bh, 017h, 08Bh, 047h, 004h, 08Bh, 04Fh, 008h, 089h, 054h, 024h, 010h, 0D9h, 044h, 024h, 010h
    db 0D8h, 044h, 024h, 01Ch, 089h, 044h, 024h, 014h, 089h, 04Ch, 024h, 018h, 08Dh, 086h, 0D4h, 016h
    db 000h, 000h, 0D9h, 05Ch, 024h, 010h, 08Bh, 04Ch, 024h, 010h, 0D9h, 044h, 024h, 014h, 08Bh, 0D0h
    db 0D8h, 044h, 024h, 020h, 089h, 00Ah, 050h, 0D9h, 05Ch, 024h, 018h, 08Bh, 04Ch, 024h, 018h, 0D9h
    db 044h, 024h, 01Ch, 089h, 04Ah, 004h, 0D8h, 044h, 024h, 028h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 04Ch
    db 024h, 01Ch, 089h, 04Ah, 008h, 08Dh, 08Eh, 0E8h, 002h, 000h, 000h
    call ?j_0003a25b@@YAXXZ
    db 08Bh, 054h, 024h, 040h, 08Bh, 044h, 024h, 03Ch, 08Bh, 04Ch, 024h, 038h, 052h, 08Bh, 054h, 024h
    db 038h, 050h, 051h, 052h, 08Bh, 0CEh, 0C7h, 086h, 0F0h, 022h, 000h, 000h, 002h, 000h, 000h, 000h
    call ?j_00033fa5@@YAXXZ
    db 085h, 0EDh, 074h, 01Bh, 08Bh, 045h, 014h, 089h, 086h, 0F0h, 01Eh, 000h, 000h, 08Bh, 04Dh, 018h
    db 089h, 08Eh, 0F0h, 016h, 000h, 000h, 08Bh, 055h, 018h, 089h, 096h, 0F4h, 016h, 000h, 000h, 08Bh
    db 086h, 084h, 002h, 000h, 000h, 0BFh, 001h, 000h, 000h, 000h, 03Bh, 0C7h, 075h, 021h, 057h, 08Bh
    db 0CEh
    call ?j_000321fa@@YAXXZ
    db 08Bh, 006h, 06Ah, 000h, 08Bh, 0CEh, 089h, 0BEh, 054h, 023h, 000h, 000h, 0C7h, 086h, 038h, 001h
    db 000h, 000h, 000h, 000h, 000h, 000h, 0FFh, 050h, 06Ch, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 018h
    db 0C2h, 018h, 000h
?d_007418b0@@YAXXZ ENDP
_TEXT$d00b418b0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b41c00  retail @ 0x00741C00 size 195
public ?d_00741c00@@YAXXZ
?d_00741c00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 0DAh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 56h, 8Bh, 0F1h, 8Bh, 46h, 0Ch, 8Bh, 4Eh
    db 10h, 8Bh, 56h, 14h, 57h, 6Ah, 30h, 89h, 44h, 24h, 10h, 89h, 4Ch, 24h, 14h, 89h
    db 54h, 24h, 18h, 0C6h, 46h, 44h, 00h, 0E8h, 0F4h, 02h, 14h, 00h, 8Bh, 0F8h, 83h, 0C4h
    db 04h, 89h, 7Ch, 24h, 08h, 85h, 0FFh, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 74h
    db 5Dh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 0Ch, 01h, 00h, 00h, 8Bh, 16h, 51h, 8Bh, 4Eh
    db 6Ch, 0D9h, 1Ch, 24h, 51h, 8Bh, 0CEh, 0FFh, 92h, 20h, 01h, 00h, 00h, 8Bh, 46h, 70h
    db 8Bh, 16h, 51h, 0D9h, 1Ch, 24h, 50h, 8Bh, 0CEh, 0FFh, 92h, 0FCh, 00h, 00h, 00h, 8Bh
    db 86h, 0F8h, 23h, 00h, 00h, 8Bh, 54h, 24h, 38h, 51h, 0D9h, 1Ch, 24h, 50h, 8Dh, 4Ch
    db 24h, 24h, 51h, 52h, 8Bh, 0CFh, 0E8h, 0C5h, 18h, 8Eh, 0FFh, 5Fh, 5Eh, 8Bh, 4Ch, 24h
    db 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h, 8Bh, 4Ch
    db 24h, 18h, 5Fh, 33h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch
    db 0C2h, 04h, 00h
?d_00741c00@@YAXXZ ENDP

; ghidra: FUN_00b41d30  retail @ 0x00741D30 size 1322
public ?d_00741d30@@YAXXZ
?d_00741d30@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 1Bh, 0DBh, 04h, 01h, 50h, 0A1h, 98h
    db 08h, 2Fh, 01h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0D8h, 00h, 00h, 00h
    db 85h, 0C0h, 56h, 8Bh, 0F1h, 0Fh, 84h, 0E7h, 04h, 00h, 00h, 83h, 0BEh, 54h, 23h, 00h
    db 00h, 03h, 75h, 73h, 8Bh, 0B6h, 04h, 01h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h
    db 50h, 8Bh, 4Eh, 18h, 8Bh, 84h, 24h, 0ECh, 00h, 00h, 00h, 89h, 08h, 8Bh, 56h, 1Ch
    db 89h, 50h, 04h, 8Bh, 4Eh, 20h, 89h, 48h, 08h, 8Bh, 56h, 24h, 89h, 50h, 0Ch, 8Bh
    db 4Eh, 28h, 89h, 48h, 10h, 8Bh, 56h, 2Ch, 89h, 50h, 14h, 8Bh, 4Eh, 30h, 89h, 48h
    db 18h, 8Bh, 56h, 34h, 89h, 50h, 1Ch, 8Bh, 4Eh, 38h, 89h, 48h, 20h, 8Bh, 56h, 3Ch
    db 89h, 50h, 24h, 8Bh, 4Eh, 40h, 89h, 48h, 28h, 8Bh, 56h, 44h, 89h, 50h, 2Ch, 5Eh
    db 8Bh, 8Ch, 24h, 0D8h, 00h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h
    db 0E4h, 00h, 00h, 00h, 0C2h, 04h, 00h, 57h, 8Dh, 4Ch, 24h, 08h, 0E8h, 15h, 7Ch, 8Eh
    db 0FFh, 8Bh, 0Dh, 14h, 0B2h, 2Bh, 01h, 8Bh, 84h, 24h, 0F0h, 00h, 00h, 00h, 8Bh, 96h
    db 10h, 24h, 00h, 00h, 89h, 44h, 24h, 08h, 8Bh, 86h, 14h, 24h, 00h, 00h, 89h, 4Ch
    db 24h, 0Ch, 8Bh, 8Eh, 18h, 24h, 00h, 00h, 89h, 54h, 24h, 10h, 8Bh, 96h, 1Ch, 24h
    db 00h, 00h, 89h, 44h, 24h, 14h, 8Bh, 86h, 20h, 24h, 00h, 00h, 89h, 4Ch, 24h, 18h
    db 8Bh, 8Eh, 24h, 24h, 00h, 00h, 89h, 54h, 24h, 1Ch, 8Bh, 96h, 2Ch, 01h, 00h, 00h
    db 89h, 44h, 24h, 20h, 8Bh, 86h, 30h, 01h, 00h, 00h, 89h, 4Ch, 24h, 24h, 8Bh, 8Eh
    db 34h, 01h, 00h, 00h, 89h, 54h, 24h, 28h, 8Bh, 96h, 0F8h, 23h, 00h, 00h, 89h, 44h
    db 24h, 2Ch, 8Bh, 06h, 89h, 4Ch, 24h, 30h, 8Bh, 0CEh, 0C7h, 84h, 24h, 0E8h, 00h, 00h
    db 00h, 00h, 00h, 00h, 00h, 89h, 54h, 24h, 34h, 0FFh, 90h, 20h, 01h, 00h, 00h, 0D9h
    db 5Ch, 24h, 38h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0FCh, 00h, 00h, 00h, 0D9h, 5Ch, 24h
    db 3Ch, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 04h, 01h, 00h, 00h, 0D9h, 5Ch, 24h, 40h, 8Bh
    db 16h, 8Bh, 0CEh, 0FFh, 92h, 0Ch, 01h, 00h, 00h, 0D9h, 5Ch, 24h, 44h, 8Bh, 46h, 6Ch
    db 8Bh, 0Dh, 0BCh, 9Dh, 2Fh, 01h, 89h, 44h, 24h, 48h, 8Dh, 7Eh, 0Ch, 8Bh, 0D7h, 8Bh
    db 02h, 89h, 44h, 24h, 54h, 89h, 4Ch, 24h, 4Ch, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 89h
    db 4Ch, 24h, 58h, 8Bh, 0C7h, 8Bh, 08h, 89h, 54h, 24h, 5Ch, 8Bh, 50h, 04h, 8Bh, 40h
    db 08h, 89h, 44h, 24h, 68h, 8Ah, 86h, 0Ch, 24h, 00h, 00h, 84h, 0C0h, 89h, 4Ch, 24h
    db 60h, 8Bh, 8Eh, 18h, 01h, 00h, 00h, 89h, 54h, 24h, 64h, 8Bh, 96h, 1Ch, 01h, 00h
    db 00h, 89h, 4Ch, 24h, 78h, 89h, 54h, 24h, 7Ch, 88h, 84h, 24h, 80h, 00h, 00h, 00h
    db 74h, 2Dh, 8Dh, 86h, 0FCh, 23h, 00h, 00h, 8Bh, 08h, 8Bh, 50h, 04h, 89h, 8Ch, 24h
    db 84h, 00h, 00h, 00h, 8Bh, 48h, 08h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 8Bh, 50h
    db 0Ch, 89h, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 89h, 94h, 24h, 90h, 00h, 00h, 00h, 8Ah
    db 86h, 2Ah, 24h, 00h, 00h, 8Dh, 8Eh, 0D8h, 23h, 00h, 00h, 8Bh, 11h, 88h, 84h, 24h
    db 94h, 00h, 00h, 00h, 8Bh, 41h, 04h, 8Bh, 49h, 08h, 89h, 94h, 24h, 98h, 00h, 00h
    db 00h, 8Bh, 16h, 89h, 8Ch, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 0CEh, 89h, 84h, 24h, 9Ch
    db 00h, 00h, 00h, 0FFh, 92h, 0C8h, 01h, 00h, 00h, 8Bh, 16h, 88h, 84h, 24h, 0A4h, 00h
    db 00h, 00h, 8Bh, 46h, 70h, 8Bh, 0CEh, 89h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh, 92h
    db 0D0h, 01h, 00h, 00h, 8Ah, 8Eh, 0DCh, 01h, 00h, 00h, 8Ah, 96h, 29h, 24h, 00h, 00h
    db 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Ah, 86h, 28h, 24h, 00h, 00h, 88h, 84h, 24h
    db 0B0h, 00h, 00h, 00h, 8Dh, 86h, 2Ch, 24h, 00h, 00h, 88h, 8Ch, 24h, 0B1h, 00h, 00h
    db 00h, 50h, 8Dh, 8Ch, 24h, 0B8h, 00h, 00h, 00h, 88h, 94h, 24h, 0B6h, 00h, 00h, 00h
    db 0E8h, 0CBh, 5Ch, 14h, 00h, 8Dh, 8Eh, 30h, 24h, 00h, 00h, 51h, 8Dh, 8Ch, 24h, 0BCh
    db 00h, 00h, 00h, 0E8h, 0B8h, 5Ch, 14h, 00h, 8Bh, 96h, 0Ch, 01h, 00h, 00h, 8Bh, 86h
    db 10h, 01h, 00h, 00h, 89h, 94h, 24h, 0BCh, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 89h
    db 84h, 24h, 0C0h, 00h, 00h, 00h, 0FFh, 52h, 3Ch, 89h, 84h, 24h, 0C4h, 00h, 00h, 00h
    db 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 44h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 86h, 38h
    db 01h, 00h, 00h, 8Bh, 4Eh, 20h, 8Bh, 56h, 24h, 0DAh, 0E9h, 89h, 84h, 24h, 0C8h, 00h
    db 00h, 00h, 8Bh, 86h, 04h, 01h, 00h, 00h, 89h, 84h, 24h, 0D4h, 00h, 00h, 00h, 0DFh
    db 0E0h, 89h, 8Ch, 24h, 0CCh, 00h, 00h, 00h, 8Bh, 8Eh, 54h, 23h, 00h, 00h, 0F6h, 0C4h
    db 44h, 89h, 94h, 24h, 0D0h, 00h, 00h, 00h, 0C6h, 84h, 24h, 0D8h, 00h, 00h, 00h, 00h
    db 89h, 8Ch, 24h, 0DCh, 00h, 00h, 00h, 7Bh, 5Eh, 8Ah, 86h, 0DCh, 01h, 00h, 00h, 84h
    db 0C0h, 74h, 0Ch, 8Bh, 96h, 38h, 01h, 00h, 00h, 89h, 54h, 24h, 50h, 0EBh, 48h, 0D9h
    db 86h, 38h, 01h, 00h, 00h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h, 0D9h, 86h, 38h, 01h, 00h
    db 00h, 0D8h, 1Dh, 38h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 56h, 0D9h, 86h
    db 38h, 01h, 00h, 00h, 0D8h, 1Dh, 30h, 17h, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 43h, 0C7h, 86h, 38h, 01h, 00h, 00h, 00h, 00h, 00h, 00h, 0DDh, 0D8h, 8Bh, 86h, 38h
    db 01h, 00h, 00h, 89h, 44h, 24h, 50h, 8Ah, 86h, 0B8h, 23h, 00h, 00h, 84h, 0C0h, 0Fh
    db 84h, 88h, 00h, 00h, 00h, 8Dh, 8Eh, 3Ch, 24h, 00h, 00h, 8Bh, 11h, 8Bh, 41h, 04h
    db 8Bh, 49h, 08h, 89h, 54h, 24h, 6Ch, 89h, 44h, 24h, 70h, 89h, 4Ch, 24h, 74h, 0E9h
    db 0C6h, 00h, 00h, 00h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 27h, 0D9h, 05h, 38h, 53h, 07h, 01h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h
    db 0DDh, 0D8h, 0D9h, 05h, 38h, 53h, 07h, 01h, 0D9h, 86h, 38h, 01h, 00h, 00h, 0D8h, 0E1h
    db 0D9h, 9Eh, 38h, 01h, 00h, 00h, 0EBh, 93h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Ah, 86h, 0D9h, 05h, 30h, 17h, 12h, 01h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 05h, 7Ah, 08h, 0DDh, 0D8h, 0D9h, 05h, 30h, 17h, 12h, 01h, 0D8h, 86h, 38h, 01h
    db 00h, 00h, 0D9h, 9Eh, 38h, 01h, 00h, 00h, 0E9h, 60h, 0FFh, 0FFh, 0FFh, 8Ah, 86h, 0DCh
    db 01h, 00h, 00h, 84h, 0C0h, 74h, 3Bh, 8Bh, 96h, 0CCh, 01h, 00h, 00h, 8Bh, 0Dh, 98h
    db 08h, 2Fh, 01h, 52h, 0E8h, 0EAh, 0D0h, 8Dh, 0FFh, 85h, 0C0h, 74h, 25h, 83h, 0C0h, 38h
    db 8Bh, 08h, 89h, 4Ch, 24h, 6Ch, 8Bh, 50h, 04h, 89h, 54h, 24h, 70h, 8Bh, 40h, 08h
    db 89h, 44h, 24h, 74h, 0D9h, 44h, 24h, 74h, 0D8h, 44h, 24h, 50h, 0D9h, 5Ch, 24h, 74h
    db 0EBh, 18h, 0C7h, 44h, 24h, 6Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 70h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 74h, 00h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 08h, 51h, 8Dh
    db 8Eh, 0B4h, 00h, 00h, 00h, 0E8h, 0FDh, 13h, 8Ch, 0FFh, 8Bh, 84h, 24h, 0BCh, 00h, 00h
    db 00h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 84h, 24h, 0C0h
    db 00h, 00h, 00h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 92h, 0B8h, 00h, 00h, 00h, 8Bh, 4Ch
    db 24h, 60h, 8Bh, 54h, 24h, 64h, 8Bh, 44h, 24h, 68h, 89h, 0Fh, 89h, 57h, 04h, 89h
    db 47h, 08h, 0A1h, 64h, 14h, 2Fh, 01h, 8Ah, 88h, 0BDh, 00h, 00h, 00h, 84h, 0C9h, 5Fh
    db 75h, 0Ah, 8Ah, 88h, 0BCh, 00h, 00h, 00h, 84h, 0C9h, 74h, 22h, 0B9h, 0D0h, 79h, 2Ah
    db 01h, 0E8h, 0EEh, 70h, 8Ch, 0FFh, 0D9h, 46h, 28h, 0D8h, 0Dh, 0C0h, 0ECh, 09h, 01h, 51h
    db 0B9h, 0E0h, 0D5h, 2Eh, 01h, 0D9h, 1Ch, 24h, 50h, 0E8h, 76h, 6Dh, 90h, 0FFh, 8Dh, 4Ch
    db 24h, 04h, 0C7h, 84h, 24h, 0E4h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A8h, 62h
    db 8Ch, 0FFh, 8Bh, 8Ch, 24h, 0DCh, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 81h, 0C4h, 0E4h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00741d30@@YAXXZ ENDP

; ghidra: FUN_00b423b0  retail @ 0x007423B0 size 679
public ?d_007423b0@@YAXXZ
?d_007423b0@@YAXXZ PROC
    db 83h, 0ECh, 40h, 56h, 8Bh, 0F1h, 0C6h, 86h, 0C8h, 23h, 00h, 00h, 01h, 0A1h, 0C8h, 0D5h
    db 2Eh, 01h, 0C7h, 44h, 24h, 14h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 18h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 28h, 00h, 00h
    db 80h, 3Fh, 0C7h, 44h, 24h, 2Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 30h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 38h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 40h, 00h, 00h
    db 00h, 00h, 0D9h, 80h, 28h, 0Ah, 00h, 00h, 0D8h, 0Dh, 34h, 17h, 12h, 01h, 51h, 8Bh
    db 8Eh, 04h, 01h, 00h, 00h, 0D9h, 1Ch, 24h, 68h, 00h, 00h, 20h, 41h, 0E8h, 2Eh, 0EFh
    db 1Eh, 00h, 8Ah, 86h, 0Ch, 24h, 00h, 00h, 84h, 0C0h, 75h, 31h, 8Dh, 4Ch, 24h, 14h
    db 51h, 8Bh, 0CEh, 0E8h, 87h, 84h, 8Ch, 0FFh, 8Bh, 8Eh, 04h, 01h, 00h, 00h, 8Bh, 11h
    db 8Dh, 44h, 24h, 14h, 50h, 0FFh, 52h, 54h, 8Bh, 0CEh, 0E8h, 0C5h, 24h, 8Dh, 0FFh, 8Ah
    db 86h, 0Ch, 24h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 0ADh, 00h, 00h, 00h, 8Ah, 46h, 44h
    db 84h, 0C0h, 0Fh, 84h, 0A2h, 00h, 00h, 00h, 8Bh, 4Eh, 0Ch, 0D9h, 86h, 0FCh, 23h, 00h
    db 00h, 8Bh, 46h, 14h, 8Bh, 56h, 10h, 89h, 4Ch, 24h, 08h, 0D9h, 44h, 24h, 08h, 8Bh
    db 8Eh, 04h, 24h, 00h, 00h, 0D8h, 0D9h, 89h, 44h, 24h, 10h, 89h, 54h, 24h, 0Ch, 89h
    db 4Ch, 24h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 1Bh, 0DDh, 0D8h, 0D9h, 44h, 24h, 08h
    db 0D8h, 5Ch, 24h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 44h, 24h, 04h, 0EBh
    db 04h, 0D9h, 44h, 24h, 08h, 8Bh, 96h, 08h, 24h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0D9h
    db 86h, 00h, 24h, 00h, 00h, 89h, 54h, 24h, 04h, 0D9h, 44h, 24h, 0Ch, 0D8h, 0D9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 05h, 7Bh, 1Bh, 0DDh, 0D8h, 0D9h, 44h, 24h, 0Ch, 0D8h, 5Ch, 24h, 04h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 44h, 24h, 04h, 0EBh, 04h, 0D9h, 44h, 24h
    db 0Ch, 8Bh, 44h, 24h, 08h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h, 24h
    db 10h, 89h, 46h, 0Ch, 89h, 4Eh, 10h, 89h, 56h, 14h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah
    db 88h, 0D0h, 0Eh, 00h, 00h, 84h, 0C9h, 68h, 00h, 00h, 80h, 0BFh, 74h, 09h, 8Bh, 80h
    db 0D4h, 0Eh, 00h, 00h, 50h, 0EBh, 04h, 8Bh, 4Eh, 6Ch, 51h, 8Bh, 8Eh, 04h, 01h, 00h
    db 00h, 0E8h, 2Ah, 0F2h, 1Eh, 00h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0E8h, 7Dh, 83h
    db 8Ch, 0FFh, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 0D0h, 0Eh, 00h, 00h, 84h, 0C9h, 0Fh
    db 84h, 84h, 00h, 00h, 00h, 0D9h, 80h, 0D8h, 0Eh, 00h, 00h, 0D9h, 0C0h, 0D9h, 0FEh, 0D9h
    db 0C9h, 0D9h, 0FFh, 0D9h, 44h, 24h, 14h, 0D9h, 0C1h, 0D8h, 4Ch, 24h, 14h, 0D9h, 44h, 24h
    db 1Ch, 0D8h, 0CCh, 0DEh, 0E9h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 1Ch, 0D8h, 0CAh, 0D9h
    db 0C9h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 1Ch, 0D9h, 44h, 24h, 24h, 0D9h, 44h, 24h
    db 24h, 0D8h, 0CAh, 0D9h, 44h, 24h, 2Ch, 0D8h, 0CCh, 0DEh, 0E9h, 0D9h, 5Ch, 24h, 24h, 0D9h
    db 44h, 24h, 2Ch, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h
    db 44h, 24h, 34h, 0D9h, 44h, 24h, 34h, 0D8h, 0CAh, 0D9h, 44h, 24h, 3Ch, 0D8h, 0CCh, 0DEh
    db 0E9h, 0D9h, 5Ch, 24h, 34h, 0D9h, 44h, 24h, 3Ch, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh
    db 0C1h, 0D9h, 5Ch, 24h, 3Ch, 0DDh, 0D8h, 0DDh, 0D8h, 8Bh, 8Eh, 04h, 01h, 00h, 00h, 8Bh
    db 01h, 8Dh, 54h, 24h, 14h, 52h, 0FFh, 50h, 54h, 0A1h, 0E0h, 7Fh, 2Fh, 01h, 85h, 0C0h
    db 74h, 35h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 57h, 0E8h, 0ECh, 03h, 90h, 0FFh, 8Bh, 0Dh
    db 0E0h, 7Fh, 2Fh, 01h, 8Bh, 96h, 04h, 01h, 00h, 00h, 8Bh, 0F8h, 8Bh, 01h, 57h, 52h
    db 0FFh, 90h, 1Ch, 02h, 00h, 00h, 85h, 0FFh, 74h, 0Ch, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h
    db 57h, 0E8h, 0ADh, 26h, 8Eh, 0FFh, 5Fh, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 0E8h, 63h, 81h
    db 8Fh, 0FFh, 5Eh, 83h, 0C4h, 40h, 0C3h
?d_007423b0@@YAXXZ ENDP

; ghidra: FUN_00b42df0  retail @ 0x00742DF0 size 87
public ?d_00742df0@@YAXXZ
?d_00742df0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 2Bh, 01h, 90h, 0FFh, 8Bh, 86h, 0B8h, 24h, 00h, 00h, 8Dh, 56h
    db 28h, 8Dh, 8Eh, 0B8h, 24h, 00h, 00h, 52h, 6Ah, 00h, 0FFh, 50h, 48h, 0D9h, 86h, 0D8h
    db 23h, 00h, 00h, 0D8h, 8Eh, 0A0h, 00h, 00h, 00h, 0C7h, 46h, 70h, 00h, 00h, 80h, 3Fh
    db 0C7h, 46h, 6Ch, 0F3h, 66h, 5Fh, 3Fh, 8Bh, 0CEh, 0D9h, 9Eh, 0D8h, 23h, 00h, 00h, 0D9h
    db 86h, 0DCh, 23h, 00h, 00h, 0D8h, 8Eh, 0A0h, 00h, 00h, 00h, 0D9h, 9Eh, 0DCh, 23h, 00h
    db 00h, 5Eh, 0E9h, 59h, 0E4h, 8Eh, 0FFh
?d_00742df0@@YAXXZ ENDP

; ghidra: FUN_00b43860  retail @ 0x00743860 size 676
public ?d_00743860@@YAXXZ
?d_00743860@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 56h, 8Bh, 0F1h, 8Bh, 9Eh, 0B0h, 01h, 00h, 00h, 43h, 89h, 9Eh
    db 0B0h, 01h, 00h, 00h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 91h, 74h, 0Ah, 00h, 00h
    db 8Bh, 0C3h, 33h, 0DBh, 3Ah, 0D3h, 89h, 44h, 24h, 0Ch, 74h, 28h, 8Bh, 96h, 0BCh, 01h
    db 00h, 00h, 03h, 96h, 0ACh, 01h, 00h, 00h, 3Bh, 0C2h, 7Ch, 0Ch, 88h, 9Eh, 0DCh, 01h
    db 00h, 00h, 88h, 9Eh, 0C0h, 23h, 00h, 00h, 88h, 9Eh, 28h, 24h, 00h, 00h, 5Eh, 5Bh
    db 83h, 0C4h, 10h, 0C3h, 38h, 9Eh, 0C8h, 01h, 00h, 00h, 8Bh, 8Eh, 0ACh, 01h, 00h, 00h
    db 89h, 4Ch, 24h, 08h, 0Fh, 84h, 73h, 01h, 00h, 00h, 8Bh, 96h, 0BCh, 01h, 00h, 00h
    db 03h, 0D1h, 3Bh, 0C2h, 0Fh, 8Fh, 0EFh, 01h, 00h, 00h, 8Bh, 86h, 0CCh, 01h, 00h, 00h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 67h, 0B9h, 8Dh, 0FFh, 3Bh, 0C3h, 74h, 12h
    db 8Bh, 48h, 38h, 89h, 8Eh, 0D0h, 01h, 00h, 00h, 8Bh, 50h, 3Ch, 89h, 96h, 0D4h, 01h
    db 00h, 00h, 0DBh, 44h, 24h, 0Ch, 0DAh, 74h, 24h, 08h, 0D8h, 8Eh, 0D8h, 01h, 00h, 00h
    db 0D9h, 9Eh, 38h, 01h, 00h, 00h, 0D9h, 86h, 0D0h, 01h, 00h, 00h, 0D8h, 66h, 0Ch, 0D9h
    db 5Ch, 24h, 10h, 0D9h, 86h, 0D4h, 01h, 00h, 00h, 0D8h, 66h, 10h, 0D9h, 54h, 24h, 14h
    db 0D8h, 4Ch, 24h, 14h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h, 5Ch
    db 24h, 08h, 0D9h, 44h, 24h, 08h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 0Ch, 0D9h, 44h, 24h, 0Ch
    db 0D8h, 1Dh, 70h, 5Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 68h, 01h, 00h
    db 00h, 0D9h, 44h, 24h, 10h, 0D8h, 74h, 24h, 0Ch, 0E8h, 0E8h, 38h, 2Bh, 00h, 0D9h, 44h
    db 24h, 14h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 02h, 0D9h
    db 0E0h, 0D8h, 25h, 14h, 71h, 09h, 01h, 8Dh, 4Ch, 24h, 0Ch, 0D9h, 5Ch, 24h, 0Ch, 0E8h
    db 6Ch, 6Fh, 0FFh, 0FFh, 8Bh, 86h, 0B0h, 01h, 00h, 00h, 8Bh, 8Eh, 0ACh, 01h, 00h, 00h
    db 3Bh, 0C1h, 89h, 44h, 24h, 10h, 89h, 4Ch, 24h, 08h, 0Fh, 8Fh, 81h, 00h, 00h, 00h
    db 0DBh, 44h, 24h, 10h, 51h, 0DAh, 74h, 24h, 0Ch, 8Dh, 8Eh, 0C0h, 01h, 00h, 00h, 0D9h
    db 1Ch, 24h, 0E8h, 0F8h, 08h, 90h, 0FFh, 0D9h, 5Ch, 24h, 08h, 0D9h, 44h, 24h, 0Ch, 8Dh
    db 56h, 28h, 0D8h, 22h, 8Dh, 4Ch, 24h, 0Ch, 0D9h, 5Ch, 24h, 0Ch, 0E8h, 1Fh, 6Fh, 0FFh
    db 0FFh, 0D9h, 44h, 24h, 0Ch, 8Bh, 0CAh, 0D8h, 4Ch, 24h, 08h, 0D8h, 02h, 0D9h, 1Ah, 0E8h
    db 0Ch, 6Fh, 0FFh, 0FFh, 8Bh, 8Eh, 0B4h, 01h, 00h, 00h, 8Bh, 86h, 0B8h, 01h, 00h, 00h
    db 2Bh, 0C1h, 89h, 44h, 24h, 10h, 0DBh, 44h, 24h, 10h, 51h, 0D8h, 4Ch, 24h, 0Ch, 0DCh
    db 05h, 0F0h, 0B3h, 09h, 01h, 0D9h, 1Ch, 24h, 0E8h, 5Dh, 1Fh, 8Ch, 0FFh, 0D9h, 5Ch, 24h
    db 14h, 83h, 0C4h, 04h, 0D9h, 44h, 24h, 10h, 0DBh, 5Ch, 24h, 0Ch, 0E9h, 88h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 0Ch, 89h, 56h, 28h, 0E9h, 8Ch, 00h, 00h, 00h, 3Bh, 0C1h, 0Fh
    db 8Fh, 84h, 00h, 00h, 00h, 0DBh, 44h, 24h, 0Ch, 51h, 0DAh, 74h, 24h, 0Ch, 8Dh, 8Eh
    db 0C0h, 01h, 00h, 00h, 0D9h, 1Ch, 24h, 0E8h, 63h, 08h, 90h, 0FFh, 0D9h, 5Ch, 24h, 0Ch
    db 0D9h, 86h, 0CCh, 01h, 00h, 00h, 8Dh, 4Eh, 28h, 0D9h, 86h, 0D0h, 01h, 00h, 00h, 0D8h
    db 0E1h, 0D8h, 4Ch, 24h, 0Ch, 0D8h, 0C1h, 0D9h, 19h, 0DDh, 0D8h, 0E8h, 80h, 6Eh, 0FFh, 0FFh
    db 8Bh, 86h, 0B8h, 01h, 00h, 00h, 2Bh, 86h, 0B4h, 01h, 00h, 00h, 89h, 44h, 24h, 10h
    db 0DBh, 44h, 24h, 10h, 83h, 0ECh, 08h, 0D8h, 4Ch, 24h, 14h, 0DCh, 05h, 0F0h, 0B3h, 09h
    db 01h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 0D9h, 5Ch, 24h, 18h, 83h, 0C4h
    db 08h, 0D9h, 44h, 24h, 10h, 0DBh, 5Ch, 24h, 0Ch, 8Bh, 8Eh, 0B4h, 01h, 00h, 00h, 03h
    db 4Ch, 24h, 0Ch, 89h, 8Eh, 0C4h, 23h, 00h, 00h, 8Bh, 96h, 0BCh, 01h, 00h, 00h, 8Bh
    db 8Eh, 0ACh, 01h, 00h, 00h, 8Bh, 86h, 0B0h, 01h, 00h, 00h, 03h, 0D1h, 3Bh, 0C2h, 7Ch
    db 1Dh, 38h, 9Eh, 0C8h, 01h, 00h, 00h, 88h, 9Eh, 0DCh, 01h, 00h, 00h, 88h, 9Eh, 0C0h
    db 23h, 00h, 00h, 75h, 09h, 8Bh, 86h, 0D0h, 01h, 00h, 00h, 89h, 46h, 28h, 5Eh, 5Bh
    db 83h, 0C4h, 10h, 0C3h
?d_00743860@@YAXXZ ENDP

; ghidra: FUN_00b43bb0  retail @ 0x00743BB0 size 40
public ?d_00743bb0@@YAXXZ
?d_00743bb0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C6h, 86h, 2Ah, 24h, 00h, 00h, 00h, 0C7h, 46h, 70h, 00h, 00h, 80h
    db 3Fh, 0C7h, 46h, 6Ch, 0F3h, 66h, 5Fh, 3Fh, 0E8h, 0D3h, 0D6h, 8Eh, 0FFh, 8Bh, 06h, 8Bh
    db 0CEh, 5Eh, 0FFh, 0A0h, 78h, 01h, 00h, 00h
?d_00743bb0@@YAXXZ ENDP

; ghidra: FUN_00b43f80  retail @ 0x00743F80 size 789
_TEXT ENDS
_TEXT$d00b43f80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B43F80 size 789
public ?d_00743f80@@YAXXZ
?d_00743f80@@YAXXZ PROC
    db 083h, 0ECh, 014h, 056h, 08Bh, 0F1h, 08Bh, 006h, 0FFh, 090h, 0C8h, 001h, 000h, 000h, 084h, 0C0h
    db 00Fh, 084h, 0E6h, 002h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_00022c96@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0D3h, 002h, 000h, 000h, 0A0h
    dd g_Va012BB218
    db 053h, 033h, 0DBh, 03Ah, 0C3h, 00Fh, 085h, 027h, 002h, 000h, 000h, 038h, 01Dh
    dd ?g_bfmeFlagEC@@3_NA
    db 00Fh, 085h, 0E6h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 0FFh, 052h, 02Ch, 085h, 0C0h, 089h, 044h, 024h, 00Ch, 0DBh, 044h, 024h, 00Ch, 07Dh
    db 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 00Dh
    dd g_Va012BB1D8
    db 0A1h
    dd ?Mouse0040F780@@3PAVMouse@@A
    db 0D9h, 05Ch, 024h, 008h, 0DBh, 080h, 010h, 04Dh, 000h, 000h, 0D9h, 054h, 024h, 010h, 0D8h, 064h
    db 024h, 008h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 03Ch, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 0DDh, 0D8h, 08Bh, 011h, 0FFh, 052h, 02Ch, 085h, 0C0h, 089h, 044h, 024h, 00Ch, 0DBh, 044h, 024h
    db 00Ch, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 064h, 024h, 008h, 0D8h, 06Ch, 024h, 010h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 00Dh
    dd g_Va012BB1DC
    db 0D8h, 02Dh
    dd g_Va012F9DE0
    db 0D9h, 005h
    dd g_Va012BB1E0
    db 0D8h, 0C9h, 0D8h, 0E9h, 0D9h, 01Dh
    dd g_Va012F9DE0
    db 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 005h
    dd g_Va012F9DE0
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 030h, 038h, 01Dh
    dd ?g_bfmeFlagEC@@3_NA
    db 075h, 016h, 0D9h, 005h
    dd ?BfmeCameraGlobal12F9DBC@@3MA
    db 0C7h, 005h
    dd ?BfmeCameraGlobal12F9DBC@@3MA
    db 000h, 000h, 000h, 000h, 0D8h, 046h, 028h, 0D9h, 05Eh, 028h, 0D9h, 005h
    dd g_Va012F9DE0
    db 08Dh, 04Eh, 028h, 0D8h, 001h, 0D9h, 019h
    call ?normAngle@@YIXAAM@Z
    db 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 0FFh, 050h, 030h, 085h, 0C0h, 089h, 044h, 024h, 00Ch, 0DBh, 044h, 024h, 00Ch, 07Dh
    db 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 00Dh
    dd g_Va012BB1E4
    db 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 0D9h, 05Ch, 024h, 008h, 0FFh, 052h, 030h, 085h, 0C0h, 089h, 044h, 024h, 00Ch, 0DBh
    db 044h, 024h, 00Ch, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 00Dh
    dd g_Va012BB1E8
    db 0A1h
    dd ?Mouse0040F780@@3PAVMouse@@A
    db 0D9h, 05Ch, 024h, 00Ch, 0DBh, 080h, 014h, 04Dh, 000h, 000h, 0D9h, 054h, 024h, 014h, 0D8h, 064h
    db 024h, 008h, 0D9h, 054h, 024h, 008h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 057h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 0FFh, 052h, 030h, 085h, 0C0h, 089h, 044h, 024h, 008h, 0DBh, 044h, 024h, 008h, 07Dh
    db 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 064h, 024h, 00Ch, 0D8h, 06Ch, 024h, 014h, 0D9h, 054h, 024h, 008h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 054h, 0D9h, 044h, 024h, 008h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 010h, 0D9h, 046h, 070h, 0D8h, 01Dh
    dd g_Va012BB1F8
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 021h, 0D9h, 044h, 024h, 008h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 022h, 0D9h, 046h, 070h, 0D8h, 01Dh
    dd g_Va012BB1FC
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 012h, 0D9h, 005h
    dd g_Va012BB200
    db 0D8h, 04Ch, 024h, 008h, 0D8h, 005h
    dd g_Va012F9DDC
    db 0EBh, 006h, 0D9h, 005h
    dd g_Va012F9DDC
    db 0D9h, 005h
    dd g_Va012BB204
    db 0D8h, 0C9h, 0D8h, 0E9h, 0D9h, 01Dh
    dd g_Va012F9DDC
    db 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 005h
    dd g_Va012F9DDC
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Ch, 0D9h, 005h
    dd g_Va012F9DDC
    db 0D8h, 046h, 070h, 0D9h, 05Eh, 070h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 0D0h, 001h, 000h, 000h
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 03Bh, 0C3h, 074h, 04Eh, 038h, 01Dh
    dd ?g_bfmeFlagEC@@3_NA
    db 075h, 046h, 08Bh, 048h, 038h, 08Bh, 050h, 03Ch, 08Dh, 046h, 00Ch, 089h, 008h, 089h, 04Ch, 024h
    db 010h, 089h, 050h, 004h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 018h
    db 089h, 054h, 024h, 014h, 08Bh, 016h, 089h, 048h, 008h, 053h, 08Bh, 0CEh, 088h, 09Eh, 0DCh, 001h
    db 000h, 000h, 089h, 09Eh, 054h, 023h, 000h, 000h, 0FFh, 052h, 06Ch, 08Bh, 0CEh, 088h, 09Eh, 07Dh
    db 002h, 000h, 000h
    call ?j_000312a0@@YAXXZ
    db 0A1h
    dd g_Va012F9E28
    db 03Bh, 0C3h, 074h, 010h, 0C7h, 080h, 0B0h, 000h, 000h, 000h, 000h, 000h, 080h, 03Fh, 089h, 01Dh
    dd g_Va012F9E28
    db 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 0FFh, 050h, 02Ch, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 05Bh, 05Eh, 083h, 0C4h, 014h, 0FFh, 062h, 030h, 083h, 0BEh, 090h, 024h, 000h, 000h
    db 004h, 075h, 00Bh, 08Bh, 0CEh, 05Eh, 083h, 0C4h, 014h
    jmp ?j_000312a0@@YAXXZ
    db 05Eh, 083h, 0C4h, 014h, 0C3h
?d_00743f80@@YAXXZ ENDP
_TEXT$d00b43f80 ENDS
_TEXT SEGMENT

; ghidra: FUN_00b44530  retail @ 0x00744530 size 293
public ?d_00744530@@YAXXZ
?d_00744530@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 91h, 90h, 0Ah, 00h, 00h, 32h
    db 0C0h, 84h, 0D2h, 74h, 17h, 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh, 4Ah, 3Ch, 39h, 8Eh
    db 0B4h, 24h, 00h, 00h, 7Dh, 06h, 89h, 8Eh, 0B4h, 24h, 00h, 00h, 8Ah, 8Eh, 28h, 02h
    db 00h, 00h, 84h, 0C9h, 74h, 09h, 8Bh, 0CEh, 0E8h, 35h, 67h, 8Eh, 0FFh, 0B0h, 01h, 8Ah
    db 8Eh, 54h, 02h, 00h, 00h, 84h, 0C9h, 74h, 09h, 8Bh, 0CEh, 0E8h, 8Eh, 19h, 8Eh, 0FFh
    db 0B0h, 01h, 8Ah, 8Eh, 04h, 02h, 00h, 00h, 84h, 0C9h, 74h, 09h, 8Bh, 0CEh, 0E8h, 51h
    db 0F0h, 8Bh, 0FFh, 0B0h, 01h, 8Ah, 8Eh, 7Ch, 02h, 00h, 00h, 84h, 0C9h, 74h, 09h, 8Bh
    db 0CEh, 0E8h, 0E4h, 18h, 90h, 0FFh, 0B0h, 01h, 8Ah, 8Eh, 0DCh, 01h, 00h, 00h, 84h, 0C9h
    db 74h, 1Bh, 8Bh, 46h, 0Ch, 89h, 86h, 0E4h, 23h, 00h, 00h, 8Bh, 4Eh, 10h, 89h, 8Eh
    db 0E8h, 23h, 00h, 00h, 8Bh, 0CEh, 0E8h, 92h, 8Fh, 8Ch, 0FFh, 0B0h, 01h, 8Ah, 8Eh, 0B8h
    db 23h, 00h, 00h, 84h, 0C9h, 74h, 12h, 8Bh, 15h, 0CCh, 0B1h, 2Bh, 01h, 6Ah, 01h, 52h
    db 8Bh, 0CEh, 0E8h, 0ACh, 69h, 90h, 0FFh, 0B0h, 01h, 8Bh, 8Eh, 54h, 23h, 00h, 00h, 49h
    db 74h, 33h, 49h, 74h, 0Ch, 49h, 75h, 4Fh, 8Bh, 0CEh, 0E8h, 5Ah, 0F0h, 8Eh, 0FFh, 0EBh
    db 44h, 8Bh, 46h, 0Ch, 89h, 86h, 0E4h, 23h, 00h, 00h, 8Bh, 4Eh, 10h, 89h, 8Eh, 0E8h
    db 23h, 00h, 00h, 8Bh, 15h, 0CCh, 0B1h, 2Bh, 01h, 6Ah, 00h, 52h, 8Bh, 0CEh, 0E8h, 70h
    db 69h, 90h, 0FFh, 0EBh, 20h, 8Bh, 46h, 0Ch, 89h, 86h, 0E4h, 23h, 00h, 00h, 8Bh, 4Eh
    db 10h, 89h, 8Eh, 0E8h, 23h, 00h, 00h, 8Bh, 15h, 0CCh, 0B1h, 2Bh, 01h, 52h, 8Bh, 0CEh
    db 0E8h, 0B5h, 0DBh, 8Eh, 0FFh, 0B0h, 01h, 8Ah, 8Eh, 7Dh, 02h, 00h, 00h, 84h, 0C9h, 5Eh
    db 74h, 02h, 0B0h, 01h, 0C3h
?d_00744530@@YAXXZ ENDP

; ghidra: FUN_00b446a0  retail @ 0x007446A0 size 2618
public ?d_007446a0@@YAXXZ
?d_007446a0@@YAXXZ PROC
    db 83h, 0ECh, 34h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 53h, 55h, 56h, 8Bh, 0F1h, 8Ah, 88h, 0D0h
    db 0Eh, 00h, 00h, 0A1h, 0E0h, 7Fh, 2Fh, 01h, 33h, 0DBh, 3Bh, 0C3h, 57h, 88h, 4Ch, 24h
    db 12h, 0C6h, 44h, 24h, 13h, 00h, 74h, 3Ah, 8Ah, 88h, 09h, 30h, 00h, 00h, 84h, 0C9h
    db 74h, 30h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 0E8h, 2Dh, 0E3h, 8Fh, 0FFh, 8Bh, 0Dh, 0E0h
    db 7Fh, 2Fh, 01h, 8Bh, 11h, 8Bh, 0F8h, 8Bh, 46h, 08h, 57h, 50h, 0FFh, 92h, 1Ch, 02h
    db 00h, 00h, 3Bh, 0FBh, 74h, 0Ch, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 57h, 0E8h, 0F1h, 05h
    db 8Eh, 0FFh, 8Bh, 96h, 04h, 0FFh, 0FFh, 0FFh, 8Dh, 0AEh, 04h, 0FFh, 0FFh, 0FFh, 8Bh, 0CDh
    db 89h, 6Ch, 24h, 28h, 0FFh, 92h, 7Ch, 01h, 00h, 00h, 8Bh, 0F8h, 3Bh, 0FBh, 75h, 0Fh
    db 0C7h, 05h, 3Ch, 0B2h, 2Bh, 01h, 00h, 00h, 80h, 0BFh, 0E9h, 94h, 02h, 00h, 00h, 8Bh
    db 45h, 00h, 53h, 8Bh, 0CDh, 89h, 9Eh, 58h, 22h, 00h, 00h, 0FFh, 50h, 6Ch, 8Bh, 0Dh
    db 98h, 08h, 2Fh, 01h, 57h, 0E8h, 09h, 0ABh, 8Dh, 0FFh, 8Bh, 0F8h, 32h, 0DBh, 85h, 0FFh
    db 75h, 02h, 0B3h, 01h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 01h, 8Bh, 55h, 00h, 8Bh
    db 0CDh, 89h, 44h, 24h, 24h, 0FFh, 92h, 94h, 01h, 00h, 00h, 8Bh, 0Dh, 64h, 14h, 2Fh
    db 01h, 50h, 8Bh, 44h, 24h, 28h, 0FFh, 50h, 2Ch, 84h, 0DBh, 8Bh, 0C8h, 74h, 1Eh, 8Bh
    db 6Ch, 24h, 28h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 9Ch, 01h, 00h, 00h, 0C7h, 05h
    db 3Ch, 0B2h, 2Bh, 01h, 00h, 00h, 80h, 0BFh, 0E9h, 24h, 02h, 00h, 00h, 0D9h, 05h, 3Ch
    db 0B2h, 2Bh, 01h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ch
    db 0C7h, 05h, 3Ch, 0B2h, 2Bh, 01h, 0CDh, 0CCh, 4Ch, 3Dh, 0EBh, 29h, 0D9h, 05h, 3Ch, 0B2h
    db 2Bh, 01h, 0D8h, 05h, 70h, 0A6h, 0Bh, 01h, 0D9h, 15h, 3Ch, 0B2h, 2Bh, 01h, 0D8h, 1Dh
    db 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah, 0C7h, 05h, 3Ch, 0B2h, 2Bh
    db 01h, 00h, 00h, 80h, 3Fh, 85h, 0C9h, 8Bh, 57h, 38h, 8Bh, 47h, 3Ch, 89h, 54h, 24h
    db 38h, 8Bh, 57h, 40h, 89h, 44h, 24h, 3Ch, 89h, 54h, 24h, 40h, 74h, 19h, 0E8h, 2Ah
    db 69h, 90h, 0FFh, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 4Ch, 24h, 38h, 89h
    db 54h, 24h, 3Ch, 89h, 44h, 24h, 40h, 8Bh, 8Eh, 10h, 0FFh, 0FFh, 0FFh, 0D9h, 86h, 14h
    db 0FFh, 0FFh, 0FFh, 89h, 4Ch, 24h, 2Ch, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0D9h, 81h, 0BCh
    db 01h, 00h, 00h, 8Ah, 86h, 7Ah, 0FFh, 0FFh, 0FFh, 84h, 0C0h, 0D9h, 0C0h, 0D8h, 0C9h, 8Bh
    db 96h, 18h, 0FFh, 0FFh, 0FFh, 89h, 54h, 24h, 34h, 0D9h, 5Ch, 24h, 1Ch, 0DDh, 0D8h, 0D9h
    db 44h, 24h, 2Ch, 0D8h, 64h, 24h, 38h, 0D9h, 0C1h, 0D8h, 64h, 24h, 3Ch, 0D9h, 0C1h, 0D8h
    db 0CAh, 0D9h, 0C1h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 18h, 0DDh, 0D8h, 0DDh, 0D8h, 74h
    db 15h, 8Bh, 44h, 24h, 38h, 8Bh, 4Ch, 24h, 3Ch, 89h, 44h, 24h, 2Ch, 89h, 4Ch, 24h
    db 30h, 0E9h, 0A0h, 00h, 00h, 00h, 0D9h, 44h, 24h, 38h, 8Bh, 86h, 64h, 0FFh, 0FFh, 0FFh
    db 83h, 0F8h, 01h, 0D8h, 64h, 24h, 2Ch, 0D9h, 5Ch, 24h, 14h, 8Bh, 54h, 24h, 14h, 0D9h
    db 44h, 24h, 3Ch, 89h, 54h, 24h, 24h, 0D8h, 0E1h, 0D9h, 54h, 24h, 20h, 75h, 55h, 0D9h
    db 44h, 24h, 18h, 0D8h, 5Ch, 24h, 1Ch, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 75h, 24h, 0D9h, 44h
    db 24h, 1Ch, 0D8h, 74h, 24h, 18h, 0D8h, 2Dh, 34h, 53h, 07h, 01h, 0D8h, 89h, 64h, 0Eh
    db 00h, 00h, 0D9h, 44h, 24h, 24h, 0D8h, 0C9h, 0D8h, 44h, 24h, 2Ch, 0D9h, 5Ch, 24h, 2Ch
    db 0EBh, 3Ah, 0DDh, 0D8h, 0D9h, 86h, 68h, 0FFh, 0FFh, 0FFh, 0D8h, 0Dh, 24h, 6Ch, 07h, 01h
    db 0D9h, 44h, 24h, 14h, 0D8h, 0C9h, 0D8h, 44h, 24h, 2Ch, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 44h
    db 24h, 20h, 0EBh, 18h, 0D9h, 05h, 3Ch, 0B2h, 2Bh, 01h, 0D8h, 4Ch, 24h, 24h, 0D8h, 44h
    db 24h, 2Ch, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 05h, 3Ch, 0B2h, 2Bh, 01h, 0D8h, 0C9h, 0D8h, 0C2h
    db 0D9h, 5Ch, 24h, 30h, 0DDh, 0D8h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 0DDh, 0D8h, 8Bh, 0F9h
    db 0E8h, 08h, 0A9h, 8Fh, 0FFh, 84h, 0C0h, 75h, 41h, 8Bh, 0CFh, 0E8h, 43h, 0EEh, 8Bh, 0FFh
    db 84h, 0C0h, 75h, 36h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 0E8h, 0C9h, 29h, 8Eh, 0FFh, 84h
    db 0C0h, 75h, 27h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 38h, 0E3h, 8Dh, 0FFh, 84h, 0C0h
    db 75h, 18h, 8Bh, 86h, 10h, 0FFh, 0FFh, 0FFh, 89h, 86h, 0E8h, 22h, 00h, 00h, 8Bh, 8Eh
    db 14h, 0FFh, 0FFh, 0FFh, 89h, 8Eh, 0ECh, 22h, 00h, 00h, 8Bh, 54h, 24h, 2Ch, 8Bh, 44h
    db 24h, 30h, 8Bh, 4Ch, 24h, 34h, 89h, 96h, 10h, 0FFh, 0FFh, 0FFh, 89h, 86h, 14h, 0FFh
    db 0FFh, 0FFh, 8Ah, 86h, 7Ah, 0FFh, 0FFh, 0FFh, 84h, 0C0h, 89h, 8Eh, 18h, 0FFh, 0FFh, 0FFh
    db 74h, 07h, 0C6h, 86h, 7Ah, 0FFh, 0FFh, 0FFh, 00h, 8Bh, 54h, 24h, 40h, 8Bh, 6Ch, 24h
    db 28h, 89h, 96h, 0FCh, 22h, 00h, 00h, 0C6h, 44h, 24h, 13h, 01h, 0C6h, 44h, 24h, 12h
    db 01h, 33h, 0DBh, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 8Bh, 0F9h, 0E8h, 6Dh, 0A8h, 8Fh, 0FFh
    db 84h, 0C0h, 75h, 3Bh, 8Bh, 0CFh, 0E8h, 0A8h, 0EDh, 8Bh, 0FFh, 84h, 0C0h, 75h, 30h, 8Bh
    db 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 0ACh, 0E2h, 8Dh, 0FFh, 84h, 0C0h, 75h, 21h, 0A1h, 98h
    db 08h, 2Fh, 01h, 8Ah, 88h, 1Dh, 01h, 00h, 00h, 84h, 0C9h, 75h, 12h, 8Bh, 0CDh, 0E8h
    db 0FDh, 96h, 8Ch, 0FFh, 84h, 0C0h, 74h, 46h, 0C6h, 44h, 24h, 12h, 01h, 0EBh, 3Ah, 39h
    db 9Eh, 58h, 22h, 00h, 00h, 75h, 32h, 8Ah, 86h, 0E0h, 00h, 00h, 00h, 84h, 0C0h, 75h
    db 28h, 8Ah, 86h, 08h, 01h, 00h, 00h, 84h, 0C0h, 75h, 1Eh, 8Ah, 86h, 2Ch, 01h, 00h
    db 00h, 84h, 0C0h, 75h, 14h, 8Ah, 86h, 81h, 01h, 00h, 00h, 84h, 0C0h, 75h, 0Ah, 8Ah
    db 86h, 80h, 01h, 00h, 00h, 84h, 0C0h, 74h, 05h, 0C6h, 44h, 24h, 13h, 01h, 0D9h, 46h
    db 2Ch, 0D8h, 1Dh, 24h, 6Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 5Dh, 0D9h, 46h
    db 2Ch, 0D8h, 4Eh, 24h, 0D9h, 5Eh, 1Ch, 0D9h, 46h, 28h, 0D8h, 4Eh, 2Ch, 0D9h, 5Eh, 20h
    db 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 0D0h, 0Eh, 00h, 00h, 84h, 0C9h, 74h, 0Ah, 8Ah
    db 88h, 0D1h, 0Eh, 00h, 00h, 84h, 0C9h, 74h, 1Ch, 0D9h, 46h, 2Ch, 0D8h, 0Dh, 48h, 0F7h
    db 09h, 01h, 0D9h, 5Eh, 2Ch, 0D9h, 46h, 24h, 0D9h, 0E0h, 0D9h, 5Eh, 24h, 0D9h, 46h, 28h
    db 0D9h, 0E0h, 0D9h, 5Eh, 28h, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 92h, 94h, 01h, 00h, 00h
    db 85h, 0C0h, 75h, 10h, 0C6h, 44h, 24h, 12h, 01h, 0EBh, 09h, 89h, 5Eh, 2Ch, 89h, 5Eh
    db 1Ch, 89h, 5Eh, 20h, 8Bh, 0Dh, 0ECh, 7Fh, 2Fh, 01h, 0E8h, 4Dh, 0D5h, 8Ch, 0FFh, 84h
    db 0C0h, 74h, 05h, 0C6h, 44h, 24h, 12h, 01h, 8Bh, 86h, 58h, 22h, 00h, 00h, 83h, 0F8h
    db 02h, 0Fh, 84h, 59h, 03h, 00h, 00h, 83h, 0F8h, 03h, 0Fh, 84h, 50h, 03h, 00h, 00h
    db 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 94h, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 0A7h
    db 02h, 00h, 00h, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 92h, 7Ch, 01h, 00h, 00h, 85h, 0C0h
    db 0Fh, 85h, 94h, 02h, 00h, 00h, 8Ah, 86h, 68h, 23h, 00h, 00h, 84h, 0C0h, 0Fh, 84h
    db 80h, 00h, 00h, 00h, 8Bh, 86h, 14h, 0FFh, 0FFh, 0FFh, 8Bh, 8Eh, 10h, 0FFh, 0FFh, 0FFh
    db 50h, 51h, 8Dh, 8Eh, 4Ch, 23h, 00h, 00h, 0E8h, 64h, 24h, 90h, 0FFh, 0D9h, 5Ch, 24h
    db 18h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 0FFh, 92h, 0A4h, 00h, 00h, 00h, 84h
    db 0C0h, 74h, 45h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 75h, 3Dh, 0D9h, 44h, 24h, 18h, 0D8h
    db 1Dh, 0A4h, 16h, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0C7h, 44h, 24h, 18h
    db 00h, 00h, 2Fh, 44h, 0D9h, 86h, 0FCh, 22h, 00h, 00h, 0D9h, 44h, 24h, 18h, 0DAh, 0E9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 11h, 8Bh, 44h, 24h, 18h, 89h, 86h, 0FCh, 22h, 00h
    db 00h, 0C6h, 86h, 10h, 23h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h, 8Eh, 58h, 0FFh
    db 0FFh, 0FFh, 0EBh, 1Ch, 8Bh, 96h, 14h, 0FFh, 0FFh, 0FFh, 8Bh, 86h, 10h, 0FFh, 0FFh, 0FFh
    db 52h, 50h, 0E8h, 0F9h, 5Dh, 0FFh, 0FFh, 0D9h, 9Eh, 58h, 0FFh, 0FFh, 0FFh, 83h, 0C4h, 08h
    db 0D9h, 86h, 40h, 0FFh, 0FFh, 0FFh, 0D8h, 8Eh, 0E4h, 22h, 00h, 00h, 0D8h, 0A6h, 58h, 0FFh
    db 0FFh, 0FFh, 0D9h, 9Eh, 54h, 0FFh, 0FFh, 0FFh, 0A1h, 0CCh, 0F4h, 2Eh, 01h, 3Bh, 0C3h, 0Fh
    db 84h, 5Bh, 02h, 00h, 00h, 39h, 1Dh, 0C8h, 0D5h, 2Eh, 01h, 0Fh, 84h, 4Fh, 02h, 00h
    db 00h, 39h, 1Dh, 8Ch, 14h, 2Fh, 01h, 0Fh, 84h, 43h, 02h, 00h, 00h, 8Ah, 86h, 79h
    db 0FFh, 0FFh, 0FFh, 84h, 0C0h, 0Fh, 84h, 35h, 02h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh
    db 01h, 0E8h, 80h, 0E0h, 8Dh, 0FFh, 84h, 0C0h, 0Fh, 85h, 22h, 02h, 00h, 00h, 0D9h, 86h
    db 44h, 0FFh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 0D8h, 86h, 58h, 0FFh, 0FFh, 0FFh
    db 0D8h, 0B6h, 0E4h, 22h, 00h, 00h, 0D9h, 5Ch, 24h, 18h, 75h, 1Fh, 8Bh, 0Dh, 98h, 08h
    db 2Fh, 01h, 83h, 0B9h, 0Ch, 01h, 00h, 00h, 03h, 75h, 26h, 8Bh, 15h, 0C8h, 0D5h, 2Eh
    db 01h, 8Ah, 82h, 0Dh, 0Ch, 00h, 00h, 84h, 0C0h, 74h, 16h, 8Bh, 86h, 54h, 0FFh, 0FFh
    db 0FFh, 8Bh, 8Eh, 40h, 0FFh, 0FFh, 0FFh, 89h, 86h, 44h, 0FFh, 0FFh, 0FFh, 89h, 4Ch, 24h
    db 18h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 0FFh, 92h, 0A4h, 00h, 00h, 00h, 84h
    db 0C0h, 0Fh, 84h, 0B2h, 00h, 00h, 00h, 0D9h, 86h, 0F4h, 22h, 00h, 00h, 0D9h, 86h, 0F0h
    db 22h, 00h, 00h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh
    db 0DAh, 0DDh, 0D8h, 0D8h, 9Eh, 0F8h, 22h, 00h, 00h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 49h
    db 8Bh, 86h, 0BCh, 23h, 00h, 00h, 8Dh, 0BEh, 0BCh, 23h, 00h, 00h, 8Bh, 0CFh, 0FFh, 10h
    db 0D8h, 9Eh, 54h, 0FFh, 0FFh, 0FFh, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 2Ch, 8Bh, 0Dh, 0C8h
    db 0D5h, 2Eh, 01h, 8Ah, 81h, 7Ch, 0Bh, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 5Fh, 01h, 00h
    db 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 04h, 0D8h, 9Eh, 54h, 0FFh, 0FFh, 0FFh, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 0Fh, 8Ah, 47h, 01h, 00h, 00h, 0D9h, 44h, 24h, 18h, 0A1h, 0C8h, 0D5h
    db 2Eh, 01h, 0D8h, 0A6h, 40h, 0FFh, 0FFh, 0FFh, 0D8h, 88h, 78h, 0Bh, 00h, 00h, 0D9h, 0C0h
    db 0D9h, 0E1h, 0DCh, 1Dh, 58h, 17h, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 1Bh
    db 01h, 00h, 00h, 0D8h, 86h, 40h, 0FFh, 0FFh, 0FFh, 0C6h, 44h, 24h, 12h, 01h, 0D9h, 9Eh
    db 40h, 0FFh, 0FFh, 0FFh, 0E9h, 07h, 01h, 00h, 00h, 0D9h, 86h, 40h, 0FFh, 0FFh, 0FFh, 8Bh
    db 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0D8h, 64h, 24h, 18h, 0D8h, 89h, 78h, 0Bh, 00h, 00h, 0D9h
    db 54h, 24h, 28h, 0D9h, 0E1h, 0DCh, 1Dh, 58h, 17h, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h
    db 0Fh, 85h, 0DAh, 00h, 00h, 00h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 0Fh, 8Bh, 54h
    db 24h, 18h, 89h, 96h, 40h, 0FFh, 0FFh, 0FFh, 0E9h, 0C3h, 00h, 00h, 00h, 0D9h, 86h, 40h
    db 0FFh, 0FFh, 0FFh, 8Bh, 45h, 00h, 0D8h, 64h, 24h, 28h, 8Bh, 0CDh, 0D9h, 9Eh, 40h, 0FFh
    db 0FFh, 0FFh, 0FFh, 90h, 94h, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 0A0h, 00h, 00h, 00h
    db 0C6h, 44h, 24h, 12h, 01h, 0E9h, 96h, 00h, 00h, 00h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h
    db 8Bh, 39h, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 92h, 94h, 01h, 00h, 00h, 8Bh, 0Dh, 64h
    db 14h, 2Fh, 01h, 50h, 0FFh, 57h, 2Ch, 3Bh, 0C3h, 74h, 0Bh, 8Bh, 0C8h, 0E8h, 5Bh, 63h
    db 90h, 0FFh, 8Bh, 0C8h, 0EBh, 1Eh, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 90h, 7Ch, 01h, 00h
    db 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 66h, 0A4h, 8Dh, 0FFh, 3Bh, 0C3h, 74h
    db 4Fh, 8Dh, 48h, 38h, 3Bh, 0CBh, 74h, 48h, 0D9h, 86h, 6Ch, 0FFh, 0FFh, 0FFh, 0D8h, 1Dh
    db 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0D9h, 86h, 6Ch, 0FFh, 0FFh
    db 0FFh, 0EBh, 0Ch, 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 0D9h, 82h, 58h, 0Eh, 00h, 00h, 0D8h
    db 41h, 08h, 8Bh, 45h, 00h, 51h, 8Bh, 0CDh, 0D9h, 1Ch, 24h, 0FFh, 90h, 4Ch, 02h, 00h
    db 00h, 0D9h, 9Eh, 40h, 0FFh, 0FFh, 0FFh, 0C6h, 44h, 24h, 12h, 01h, 0EBh, 02h, 0DDh, 0D8h
    db 8Bh, 8Eh, 0B0h, 23h, 00h, 00h, 3Bh, 0CBh, 74h, 45h, 8Dh, 96h, 10h, 0FFh, 0FFh, 0FFh
    db 52h, 0E8h, 85h, 59h, 8Ch, 0FFh, 84h, 0C0h, 74h, 35h, 8Ah, 86h, 0B4h, 23h, 00h, 00h
    db 84h, 0C0h, 75h, 22h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 14h, 8Bh, 91h, 0C0h, 00h
    db 00h, 00h, 89h, 56h, 0A0h, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 14h, 8Bh, 91h, 0BCh
    db 00h, 00h, 00h, 89h, 56h, 0A8h, 0C6h, 86h, 0B4h, 23h, 00h, 00h, 01h, 0EBh, 1Ch, 8Ah
    db 86h, 0B4h, 23h, 00h, 00h, 84h, 0C0h, 74h, 0Bh, 0B8h, 00h, 00h, 80h, 3Fh, 89h, 46h
    db 0A0h, 89h, 46h, 0A8h, 0C6h, 86h, 0B4h, 23h, 00h, 00h, 00h, 0D9h, 46h, 0A0h, 0D8h, 1Dh
    db 40h, 0BFh, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 07h, 0C7h, 46h, 0A0h, 6Fh, 12h
    db 83h, 3Ah, 0D9h, 46h, 0A0h, 0D8h, 66h, 0A4h, 0D9h, 0C0h, 0D9h, 0E1h, 0D8h, 1Dh, 24h, 6Ch
    db 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0C7h, 44h, 24h, 18h, 00h, 00h, 80h
    db 3Fh, 0EBh, 3Fh, 0D9h, 05h, 50h, 2Ah, 0Ah, 01h, 0D8h, 0C9h, 0D9h, 0C0h, 0D9h, 0E1h, 0D8h
    db 1Dh, 24h, 6Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Bh, 0D8h, 1Dh, 50h, 53h
    db 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0D9h, 05h, 24h, 6Ch, 07h, 01h, 0EBh
    db 06h, 0D9h, 05h, 0DCh, 0Ah, 0Fh, 01h, 0D8h, 0F1h, 0C6h, 44h, 24h, 12h, 01h, 0D9h, 5Ch
    db 24h, 18h, 0D9h, 46h, 0A8h, 0D8h, 66h, 0ACh, 0D9h, 54h, 24h, 1Ch, 0D9h, 0E1h, 0D8h, 1Dh
    db 24h, 6Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0C7h, 44h, 24h, 14h, 00h
    db 00h, 80h, 3Fh, 0EBh, 43h, 0D9h, 44h, 24h, 1Ch, 0D8h, 0Dh, 50h, 2Ah, 0Ah, 01h, 0D9h
    db 0C0h, 0D9h, 0E1h, 0D8h, 1Dh, 24h, 6Ch, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Bh
    db 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0D9h, 05h, 24h
    db 6Ch, 07h, 01h, 0EBh, 06h, 0D9h, 05h, 0DCh, 0Ah, 0Fh, 01h, 0D8h, 74h, 24h, 1Ch, 0C6h
    db 44h, 24h, 12h, 01h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 14h, 0C7h, 44h, 24h, 28h
    db 00h, 00h, 80h, 3Fh, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 12h, 0D9h, 44h, 24h, 14h, 0C7h, 44h, 24h, 28h, 00h, 00h, 80h, 0BFh, 0D9h, 0E0h, 0D9h
    db 5Ch, 24h, 14h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D9h, 44h, 24h, 18h, 0D8h, 1Dh, 50h
    db 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 12h, 0DDh, 0D8h, 0D9h, 44h, 24h, 18h
    db 0D9h, 0E0h, 0D9h, 5Ch, 24h, 18h, 0D9h, 05h, 3Ch, 0BFh, 09h, 01h, 0D9h, 44h, 24h, 14h
    db 0D8h, 5Ch, 24h, 18h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 8Dh, 44h, 24h, 14h, 7Bh, 04h, 8Dh
    db 44h, 24h, 18h, 0D9h, 00h, 8Bh, 86h, 0BCh, 23h, 00h, 00h, 0D9h, 44h, 24h, 28h, 8Dh
    db 8Eh, 0BCh, 23h, 00h, 00h, 0D8h, 0C9h, 53h, 8Dh, 0BEh, 0DCh, 22h, 00h, 00h, 57h, 0D8h
    db 4Ch, 24h, 24h, 0D8h, 46h, 0ACh, 0D9h, 5Eh, 0ACh, 0D8h, 0C9h, 0D8h, 0CAh, 0D8h, 46h, 0A4h
    db 0D9h, 5Eh, 0A4h, 0DDh, 0D8h, 0DDh, 0D8h, 0FFh, 50h, 48h, 0D9h, 07h, 8Ah, 44h, 24h, 12h
    db 84h, 0C0h, 0D8h, 4Eh, 0A4h, 0D9h, 1Fh, 0D9h, 46h, 0A4h, 0D8h, 8Eh, 0E0h, 22h, 00h, 00h
    db 0D9h, 9Eh, 0E0h, 22h, 00h, 00h, 75h, 0Ah, 8Ah, 86h, 2Dh, 23h, 00h, 00h, 84h, 0C0h
    db 74h, 22h, 8Bh, 0CDh, 0E8h, 47h, 0C2h, 8Eh, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h
    db 13h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 3Bh, 0CBh, 74h, 09h, 8Bh, 11h, 53h, 0FFh, 92h
    db 34h, 02h, 00h, 00h, 0A1h, 20h, 0F4h, 33h, 01h, 2Bh, 05h, 24h, 0F4h, 33h, 01h, 74h
    db 51h, 8Bh, 8Eh, 7Ch, 0FFh, 0FFh, 0FFh, 8Bh, 56h, 80h, 8Bh, 76h, 08h, 89h, 4Ch, 24h
    db 28h, 8Bh, 0CEh, 89h, 54h, 24h, 24h, 0E8h, 54h, 0CDh, 1Eh, 00h, 0D9h, 44h, 24h, 28h
    db 0D8h, 4Ch, 24h, 28h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 0D9h, 44h, 24h, 24h, 8Bh, 01h
    db 0D8h, 4Ch, 24h, 24h, 55h, 68h, 50h, 0ADh, 0B3h, 00h, 51h, 0DEh, 0C1h, 81h, 0C6h, 04h
    db 01h, 00h, 00h, 0D9h, 0FAh, 0D8h, 25h, 24h, 6Ch, 07h, 01h, 0D9h, 1Ch, 24h, 56h, 0FFh
    db 50h, 54h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 34h, 0C3h
?d_007446a0@@YAXXZ ENDP
_TEXT ENDS
END
