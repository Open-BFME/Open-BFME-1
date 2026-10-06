.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?FadeTacticalView@@3PAVFadeView@@A:BYTE
EXTERN ?Glo012F4B98@@3PAVGlo012F4B98Type@@A:BYTE
EXTERN ?R2Ptr012F19E8@@3PAVGen000290D2@@A:BYTE
EXTERN ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A:BYTE
EXTERN ?TheInGameUI@@3PAUInGameUI@@A:BYTE
EXTERN ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeScaleBK@@3MA:BYTE
EXTERN ?getMaxHeightAbovePosition@GeometryInfo@@QBEMXZ:NEAR
EXTERN ?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ:NEAR
EXTERN ?j_000012a8@@YAXXZ:NEAR
EXTERN ?j_000016a4@@YAXXZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_00003f80@@YAXXZ:NEAR
EXTERN ?j_00006938@@YAXXZ:NEAR
EXTERN ?j_00006e83@@YAXXZ:NEAR
EXTERN ?j_0000bc49@@YAXXZ:NEAR
EXTERN ?j_0000d3b9@@YAXXZ:NEAR
EXTERN ?j_0000d495@@YAXXZ:NEAR
EXTERN ?j_0000dfc1@@YAXXZ:NEAR
EXTERN ?j_0000edc7@@YAXXZ:NEAR
EXTERN ?j_0000faa6@@YAXXZ:NEAR
EXTERN ?j_00011cd4@@YAXXZ:NEAR
EXTERN ?j_00013c78@@YAXXZ:NEAR
EXTERN ?j_00015da7@@YAXXZ:NEAR
EXTERN ?j_000166d0@@YAXXZ:NEAR
EXTERN ?j_0001949d@@YAXXZ:NEAR
EXTERN ?j_0001bc34@@YAXXZ:NEAR
EXTERN ?j_0001f0d7@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_0002262e@@YAXXZ:NEAR
EXTERN ?j_00023dda@@YAXXZ:NEAR
EXTERN ?j_000277a5@@YAXXZ:NEAR
EXTERN ?j_00027b24@@YAXXZ:NEAR
EXTERN ?j_00027f2a@@YAXXZ:NEAR
EXTERN ?j_00029dc0@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00033523@@YAXXZ:NEAR
EXTERN ?j_00033f19@@YAXXZ:NEAR
EXTERN ?j_00034e91@@YAXXZ:NEAR
EXTERN ?j_00037740@@YAXXZ:NEAR
EXTERN ?j_0003a5b7@@YAXXZ:NEAR
EXTERN ?j_00046a10@@YAXXZ:NEAR
EXTERN ?j_000482ac@@YAXXZ:NEAR
EXTERN ?j_00048cca@@YAXXZ:NEAR
EXTERN ?j_0004a1fb@@YAXXZ:NEAR
EXTERN __ftol2:NEAR
EXTERN __real@4f800000:BYTE
EXTERN g_Va010FD1A0:BYTE
EXTERN g_Va010FD1D0:BYTE
EXTERN g_Va012B6624:BYTE
_TEXT SEGMENT

; ghidra: FUN_008a32e0  retail @ 0x004A32E0 size 847
public ?d_004a32e0@@YAXXZ
?d_004a32e0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 0Ch, 56h, 57h, 55h, 8Bh, 0D9h, 0E8h, 35h, 54h, 0BAh, 0FFh
    db 8Dh, 45h, 0Ch, 50h, 8Dh, 4Bh, 0Ch, 0E8h, 94h, 49h, 3Eh, 00h, 8Bh, 4Dh, 10h, 89h
    db 4Bh, 10h, 8Bh, 55h, 14h, 89h, 53h, 14h, 8Bh, 45h, 18h, 89h, 43h, 18h, 8Bh, 4Dh
    db 1Ch, 89h, 4Bh, 1Ch, 8Bh, 55h, 20h, 8Dh, 4Dh, 28h, 89h, 53h, 20h, 8Bh, 45h, 24h
    db 51h, 8Dh, 4Bh, 28h, 89h, 43h, 24h, 0E8h, 37h, 47h, 0B6h, 0FFh, 8Bh, 55h, 34h, 8Dh
    db 4Dh, 3Ch, 89h, 53h, 34h, 8Bh, 45h, 38h, 51h, 8Dh, 4Bh, 3Ch, 89h, 43h, 38h, 0E8h
    db 4Ch, 49h, 3Eh, 00h, 8Dh, 55h, 40h, 52h, 8Dh, 4Bh, 40h, 0E8h, 40h, 49h, 3Eh, 00h
    db 8Dh, 45h, 44h, 50h, 8Dh, 4Bh, 44h, 0E8h, 07h, 47h, 0B6h, 0FFh, 8Dh, 4Dh, 50h, 51h
    db 8Dh, 4Bh, 50h, 0E8h, 0FBh, 46h, 0B6h, 0FFh, 8Dh, 55h, 5Ch, 52h, 8Dh, 4Bh, 5Ch, 0E8h
    db 1Ch, 49h, 3Eh, 00h, 8Dh, 45h, 60h, 50h, 8Dh, 4Bh, 60h, 0E8h, 10h, 49h, 3Eh, 00h
    db 8Dh, 4Dh, 64h, 51h, 8Dh, 4Bh, 64h, 0E8h, 04h, 49h, 3Eh, 00h, 8Dh, 55h, 68h, 52h
    db 8Dh, 4Bh, 68h, 0E8h, 0F8h, 48h, 3Eh, 00h, 8Bh, 45h, 6Ch, 89h, 43h, 6Ch, 8Bh, 4Dh
    db 70h, 89h, 4Bh, 70h, 8Bh, 55h, 74h, 89h, 53h, 74h, 8Bh, 45h, 78h, 89h, 43h, 78h
    db 8Bh, 4Dh, 7Ch, 89h, 4Bh, 7Ch, 8Bh, 95h, 80h, 00h, 00h, 00h, 8Dh, 85h, 84h, 00h
    db 00h, 00h, 50h, 8Dh, 8Bh, 84h, 00h, 00h, 00h, 89h, 93h, 80h, 00h, 00h, 00h, 0E8h
    db 9Ch, 56h, 0B7h, 0FFh, 8Bh, 8Dh, 90h, 00h, 00h, 00h, 8Dh, 95h, 94h, 00h, 00h, 00h
    db 89h, 8Bh, 90h, 00h, 00h, 00h, 52h, 8Dh, 8Bh, 94h, 00h, 00h, 00h, 0E8h, 71h, 46h
    db 0B6h, 0FFh, 8Bh, 85h, 0A0h, 00h, 00h, 00h, 89h, 83h, 0A0h, 00h, 00h, 00h, 8Bh, 8Dh
    db 0A4h, 00h, 00h, 00h, 8Dh, 95h, 0A8h, 00h, 00h, 00h, 89h, 8Bh, 0A4h, 00h, 00h, 00h
    db 52h, 8Dh, 8Bh, 0A8h, 00h, 00h, 00h, 0E8h, 2Dh, 0D2h, 0B7h, 0FFh, 8Dh, 85h, 0B4h, 00h
    db 00h, 00h, 50h, 8Dh, 8Bh, 0B4h, 00h, 00h, 00h, 0E8h, 1Bh, 0D2h, 0B7h, 0FFh, 8Dh, 8Dh
    db 0C0h, 00h, 00h, 00h, 51h, 8Dh, 8Bh, 0C0h, 00h, 00h, 00h, 0E8h, 09h, 0D2h, 0B7h, 0FFh
    db 8Dh, 95h, 0CCh, 00h, 00h, 00h, 52h, 8Dh, 8Bh, 0CCh, 00h, 00h, 00h, 0E8h, 0F7h, 0D1h
    db 0B7h, 0FFh, 8Dh, 85h, 0D8h, 00h, 00h, 00h, 50h, 8Dh, 8Bh, 0D8h, 00h, 00h, 00h, 0E8h
    db 0E5h, 0D1h, 0B7h, 0FFh, 8Dh, 8Dh, 0E4h, 00h, 00h, 00h, 51h, 8Dh, 8Bh, 0E4h, 00h, 00h
    db 00h, 0E8h, 0D3h, 0D1h, 0B7h, 0FFh, 8Dh, 95h, 0F0h, 00h, 00h, 00h, 52h, 8Dh, 8Bh, 0F0h
    db 00h, 00h, 00h, 0E8h, 0C1h, 0D1h, 0B7h, 0FFh, 8Dh, 85h, 0FCh, 00h, 00h, 00h, 50h, 8Dh
    db 8Bh, 0FCh, 00h, 00h, 00h, 0E8h, 0AFh, 0D1h, 0B7h, 0FFh, 8Dh, 8Dh, 08h, 01h, 00h, 00h
    db 51h, 8Dh, 8Bh, 08h, 01h, 00h, 00h, 0E8h, 9Dh, 0D1h, 0B7h, 0FFh, 8Dh, 95h, 14h, 01h
    db 00h, 00h, 52h, 8Dh, 8Bh, 14h, 01h, 00h, 00h, 0E8h, 8Bh, 0D1h, 0B7h, 0FFh, 8Dh, 85h
    db 20h, 01h, 00h, 00h, 50h, 8Dh, 8Bh, 20h, 01h, 00h, 00h, 0E8h, 79h, 0D1h, 0B7h, 0FFh
    db 8Dh, 8Dh, 2Ch, 01h, 00h, 00h, 51h, 8Dh, 8Bh, 2Ch, 01h, 00h, 00h, 0E8h, 67h, 0D1h
    db 0B7h, 0FFh, 8Dh, 95h, 38h, 01h, 00h, 00h, 52h, 8Dh, 8Bh, 38h, 01h, 00h, 00h, 0E8h
    db 0EAh, 0BAh, 0B6h, 0FFh, 8Bh, 85h, 44h, 01h, 00h, 00h, 89h, 83h, 44h, 01h, 00h, 00h
    db 8Bh, 8Dh, 48h, 01h, 00h, 00h, 89h, 8Bh, 48h, 01h, 00h, 00h, 8Ah, 95h, 4Ch, 01h
    db 00h, 00h, 88h, 93h, 4Ch, 01h, 00h, 00h, 8Ah, 85h, 4Dh, 01h, 00h, 00h, 88h, 83h
    db 4Dh, 01h, 00h, 00h, 8Ah, 8Dh, 4Eh, 01h, 00h, 00h, 88h, 8Bh, 4Eh, 01h, 00h, 00h
    db 8Ah, 95h, 4Fh, 01h, 00h, 00h, 88h, 93h, 4Fh, 01h, 00h, 00h, 8Ah, 85h, 50h, 01h
    db 00h, 00h, 88h, 83h, 50h, 01h, 00h, 00h, 8Ah, 8Dh, 51h, 01h, 00h, 00h, 88h, 8Bh
    db 51h, 01h, 00h, 00h, 8Ah, 95h, 52h, 01h, 00h, 00h, 88h, 93h, 52h, 01h, 00h, 00h
    db 8Ah, 85h, 53h, 01h, 00h, 00h, 88h, 83h, 53h, 01h, 00h, 00h, 8Bh, 8Dh, 54h, 01h
    db 00h, 00h, 89h, 8Bh, 54h, 01h, 00h, 00h, 8Ah, 95h, 58h, 01h, 00h, 00h, 88h, 93h
    db 58h, 01h, 00h, 00h, 8Dh, 85h, 5Ch, 01h, 00h, 00h, 8Bh, 10h, 8Dh, 8Bh, 5Ch, 01h
    db 00h, 00h, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h, 8Bh, 50h, 08h, 89h, 51h, 08h
    db 8Bh, 50h, 0Ch, 89h, 51h, 0Ch, 8Bh, 50h, 10h, 89h, 51h, 10h, 8Bh, 40h, 14h, 89h
    db 41h, 14h, 8Ah, 8Dh, 74h, 01h, 00h, 00h, 88h, 8Bh, 74h, 01h, 00h, 00h, 8Ah, 95h
    db 75h, 01h, 00h, 00h, 88h, 93h, 75h, 01h, 00h, 00h, 8Bh, 85h, 78h, 01h, 00h, 00h
    db 89h, 83h, 78h, 01h, 00h, 00h, 8Bh, 8Dh, 7Ch, 01h, 00h, 00h, 89h, 8Bh, 7Ch, 01h
    db 00h, 00h, 8Ah, 95h, 80h, 01h, 00h, 00h, 8Dh, 85h, 84h, 01h, 00h, 00h, 50h, 8Dh
    db 8Bh, 84h, 01h, 00h, 00h, 88h, 93h, 80h, 01h, 00h, 00h, 0E8h, 90h, 46h, 3Eh, 00h
    db 8Dh, 0B5h, 88h, 01h, 00h, 00h, 8Dh, 0BBh, 88h, 01h, 00h, 00h, 0B9h, 0Ah, 00h, 00h
    db 00h, 0F3h, 0A5h, 8Dh, 0B5h, 0B0h, 01h, 00h, 00h, 8Dh, 0BBh, 0B0h, 01h, 00h, 00h, 0B9h
    db 0Ah, 00h, 00h, 00h, 0F3h, 0A5h, 5Fh, 5Eh, 5Dh, 8Bh, 0C3h, 5Bh, 0C2h, 04h, 00h
?d_004a32e0@@YAXXZ ENDP

; ghidra: FUN_008a3ab0  retail @ 0x004A3AB0 size 51
public ?d_004a3ab0@@YAXXZ
?d_004a3ab0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 81h, 0C1h, 5Ch, 01h, 00h, 00h, 56h, 8Bh, 31h, 8Bh, 0D0h, 89h
    db 32h, 8Bh, 71h, 04h, 89h, 72h, 04h, 8Bh, 71h, 08h, 89h, 72h, 08h, 8Bh, 71h, 0Ch
    db 89h, 72h, 0Ch, 8Bh, 71h, 10h, 89h, 72h, 10h, 8Bh, 49h, 14h, 89h, 4Ah, 14h, 5Eh
    db 0C2h, 04h, 00h
?d_004a3ab0@@YAXXZ ENDP

; ghidra: FUN_008a3b00  retail @ 0x004A3B00 size 59
public ?d_004a3b00@@YAXXZ
?d_004a3b00@@YAXXZ PROC
    db 56h, 57h, 0BEh, 4Ch, 34h, 2Fh, 01h, 8Dh, 0B9h, 00h, 01h, 00h, 00h, 8Dh, 49h, 00h
    db 0C7h, 46h, 0FCh, 00h, 00h, 00h, 00h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 0Fh, 85h
    db 0C9h, 74h, 07h, 6Ah, 01h, 0E8h, 00h, 44h, 0B8h, 0FFh, 83h, 0C6h, 08h, 83h, 0C7h, 04h
    db 81h, 0FEh, 0ECh, 34h, 2Fh, 01h, 7Ch, 0D8h, 5Fh, 5Eh, 0C3h
?d_004a3b00@@YAXXZ ENDP

; ghidra: FUN_008a3c00  retail @ 0x004A3C00 size 35
public ?d_004a3c00@@YAXXZ
?d_004a3c00@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 81h, 0C1h, 84h, 01h, 00h, 00h, 51h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 44h, 3Fh, 3Eh, 00h, 8Bh, 0C6h, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_004a3c00@@YAXXZ ENDP

; ghidra: FUN_008a3d50  retail @ 0x004A3D50 size 126
public ?d_004a3d50@@YAXXZ
?d_004a3d50@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Dh, 96h, 0B0h, 01h, 00h, 00h, 33h, 0C9h, 8Bh, 0C2h, 90h
    db 83h, 38h, 00h, 75h, 2Ah, 41h, 83h, 0C0h, 04h, 83h, 0F9h, 0Ah, 72h, 0F2h, 8Dh, 96h
    db 88h, 01h, 00h, 00h, 33h, 0C0h, 8Bh, 0CAh, 83h, 39h, 00h, 75h, 2Fh, 40h, 83h, 0C1h
    db 04h, 83h, 0F8h, 0Ah, 72h, 0F2h, 0B8h, 02h, 00h, 00h, 00h, 5Eh, 0C2h, 08h, 00h, 8Bh
    db 4Ch, 24h, 0Ch, 52h, 81h, 0C1h, 10h, 01h, 00h, 00h, 0E8h, 0EFh, 0B3h, 0B9h, 0FFh, 84h
    db 0C0h, 74h, 0CBh, 0B8h, 03h, 00h, 00h, 00h, 5Eh, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h, 0Ch
    db 52h, 81h, 0C1h, 10h, 01h, 00h, 00h, 0E8h, 0D2h, 0B3h, 0B9h, 0FFh, 84h, 0C0h, 0B8h, 03h
    db 00h, 00h, 00h, 74h, 05h, 0B8h, 02h, 00h, 00h, 00h, 5Eh, 0C2h, 08h, 00h
?d_004a3d50@@YAXXZ ENDP

; ghidra: FUN_008a3e90  retail @ 0x004A3E90 size 401
public ?d_004a3e90@@YAXXZ
?d_004a3e90@@YAXXZ PROC
    db 83h, 0ECh, 24h, 8Bh, 44h, 24h, 28h, 53h, 55h, 33h, 0EDh, 3Bh, 0C5h, 8Bh, 0D9h, 89h
    db 5Ch, 24h, 10h, 0Fh, 84h, 70h, 01h, 00h, 00h, 39h, 6Ch, 24h, 34h, 0Fh, 84h, 66h
    db 01h, 00h, 00h, 57h, 8Bh, 0B8h, 0FCh, 01h, 00h, 00h, 3Bh, 0FDh, 0Fh, 84h, 56h, 01h
    db 00h, 00h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 10h, 3Bh, 0C5h, 74h, 0Eh, 8Ah, 88h, 0B6h, 00h
    db 00h, 00h, 84h, 0C9h, 0Fh, 84h, 3Eh, 01h, 00h, 00h, 8Bh, 17h, 56h, 8Bh, 0CFh, 0FFh
    db 52h, 5Ch, 8Bh, 0F0h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 90h, 0B8h, 00h, 00h, 00h, 2Bh, 0F0h
    db 83h, 0C8h, 0FFh, 89h, 74h, 24h, 20h, 89h, 44h, 24h, 14h, 89h, 44h, 24h, 1Ch, 89h
    db 6Ch, 24h, 10h, 8Dh, 0B3h, 00h, 01h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 3Ch, 55h, 0E8h, 66h, 00h, 0B6h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 0Fh, 84h
    db 94h, 00h, 00h, 00h, 83h, 7Bh, 10h, 0Fh, 0Fh, 85h, 8Ah, 00h, 00h, 00h, 83h, 7Ch
    db 24h, 14h, 0FFh, 75h, 04h, 89h, 6Ch, 24h, 14h, 0FFh, 44h, 24h, 10h, 8Bh, 0Eh, 85h
    db 0C9h, 89h, 6Ch, 24h, 1Ch, 74h, 71h, 6Ah, 00h, 0E8h, 0DCh, 3Fh, 0B8h, 0FFh, 8Bh, 0Eh
    db 6Ah, 00h, 0E8h, 0A4h, 62h, 0BAh, 0FFh, 8Bh, 0Eh, 6Ah, 00h, 51h, 0E8h, 0E8h, 7Ch, 0B6h
    db 0FFh, 8Bh, 54h, 24h, 40h, 8Ah, 82h, 0A4h, 01h, 00h, 00h, 83h, 0C4h, 08h, 0A8h, 20h
    db 74h, 09h, 8Bh, 0Eh, 6Ah, 01h, 0E8h, 0AFh, 3Fh, 0B8h, 0FFh, 8Bh, 44h, 24h, 20h, 39h
    db 44h, 24h, 10h, 7Eh, 09h, 8Bh, 0Eh, 6Ah, 01h, 0E8h, 9Ch, 3Fh, 0B8h, 0FFh, 8Bh, 0Eh
    db 53h, 51h, 8Bh, 4Ch, 24h, 20h, 0E8h, 0Ch, 1Eh, 0B7h, 0FFh, 8Ah, 83h, 4Dh, 01h, 00h
    db 00h, 84h, 0C0h, 8Bh, 0Eh, 68h, 00h, 00h, 00h, 04h, 74h, 07h, 0E8h, 72h, 0F5h, 0B8h
    db 0FFh, 0EBh, 05h, 0E8h, 6Ch, 3Bh, 0B8h, 0FFh, 45h, 83h, 0C6h, 04h, 83h, 0FDh, 14h, 0Fh
    db 8Ch, 4Bh, 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 85h, 0C9h, 5Eh, 7Ch, 37h, 8Bh, 44h
    db 24h, 14h, 8Bh, 54h, 24h, 10h, 05h, 00h, 01h, 00h, 00h, 89h, 44h, 24h, 28h, 8Bh
    db 44h, 24h, 34h, 89h, 44h, 24h, 2Ch, 6Ah, 01h, 8Dh, 44h, 24h, 24h, 50h, 89h, 54h
    db 24h, 28h, 8Bh, 17h, 89h, 4Ch, 24h, 2Ch, 68h, 5Fh, 0FDh, 43h, 00h, 8Bh, 0CFh, 0FFh
    db 92h, 0FCh, 00h, 00h, 00h, 8Bh, 17h, 6Ah, 00h, 8Bh, 0CFh, 0FFh, 92h, 00h, 01h, 00h
    db 00h, 8Bh, 4Ch, 24h, 14h, 89h, 41h, 70h, 5Fh, 5Dh, 5Bh, 83h, 0C4h, 24h, 0C2h, 08h
    db 00h
?d_004a3e90@@YAXXZ ENDP

; ghidra: FUN_008a4160  retail @ 0x004A4160 size 87
public ?d_004a4160@@YAXXZ
?d_004a4160@@YAXXZ PROC
    db 8Bh, 88h, 0FCh, 01h, 00h, 00h, 53h, 33h, 0DBh, 85h, 0C9h, 74h, 46h, 8Bh, 11h, 0FFh
    db 92h, 04h, 01h, 00h, 00h, 85h, 0C0h, 74h, 3Ah, 56h, 57h, 8Bh, 38h, 8Bh, 37h, 3Bh
    db 0F7h, 74h, 2Ah, 8Bh, 46h, 08h, 83h, 0C0h, 04h, 8Bh, 00h, 85h, 0C0h, 74h, 0Ch, 8Bh
    db 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 20h, 0E1h, 0B5h, 0FFh, 8Bh, 88h, 0CCh, 00h, 00h
    db 00h, 0F6h, 0C5h, 08h, 74h, 01h, 43h, 8Bh, 36h, 3Bh, 0F7h, 75h, 0D6h, 5Fh, 5Eh, 8Bh
    db 0C3h, 5Bh, 0C3h, 8Bh, 0C3h, 5Bh, 0C3h
?d_004a4160@@YAXXZ ENDP

; ghidra: FUN_008a41d0  retail @ 0x004A41D0 size 78
public ?d_004a41d0@@YAXXZ
?d_004a41d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h
    db 0C9h, 74h, 05h, 0E8h, 0D3h, 0E0h, 0B5h, 0FFh, 8Bh, 88h, 0D4h, 00h, 00h, 00h, 0F6h, 0C5h
    db 10h, 74h, 29h, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 1Fh, 8Bh, 01h, 0FFh
    db 50h, 68h, 85h, 0C0h, 74h, 16h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 92h, 0E0h, 00h, 00h, 00h
    db 84h, 0C0h, 75h, 08h, 8Bh, 44h, 24h, 0Ch, 0C6h, 40h, 04h, 01h, 5Eh, 0C3h
?d_004a41d0@@YAXXZ ENDP

; ghidra: FUN_008a4240  retail @ 0x004A4240 size 4572
public ?d_004a4240@@YAXXZ
?d_004a4240@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DAh, 83h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 40h, 8Bh, 44h, 24h, 5Ch, 53h, 8Bh, 0D9h, 0C7h
    db 00h, 00h, 00h, 80h, 3Fh, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 89h, 5Ch, 24h, 0Ch, 0E8h
    db 0B7h, 33h, 0B6h, 0FFh, 8Bh, 0C8h, 85h, 0C9h, 89h, 4Ch, 24h, 04h, 75h, 17h, 0B8h, 03h
    db 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 4Ch, 0C2h, 14h, 00h, 56h, 57h, 8Bh, 7Ch, 24h, 5Ch, 8Bh, 47h, 10h, 83h, 0F8h
    db 1Fh, 74h, 0Eh, 83h, 0F8h, 24h, 75h, 12h, 0E8h, 0BDh, 17h, 0B6h, 0FFh, 8Bh, 0F0h, 0EBh
    db 0Dh, 0E8h, 66h, 0F0h, 0B7h, 0FFh, 8Bh, 0F0h, 0EBh, 04h, 8Bh, 74h, 24h, 64h, 85h, 0F6h
    db 0Fh, 84h, 3Dh, 11h, 00h, 00h, 8Ah, 86h, 43h, 03h, 00h, 00h, 0A8h, 03h, 0Fh, 85h
    db 2Fh, 11h, 00h, 00h, 8Bh, 86h, 0A4h, 01h, 00h, 00h, 0A8h, 20h, 0Fh, 85h, 21h, 11h
    db 00h, 00h, 68h, 0CBh, 00h, 00h, 00h, 8Dh, 8Eh, 10h, 01h, 00h, 00h, 0E8h, 7Bh, 23h
    db 0B6h, 0FFh, 8Bh, 4Fh, 18h, 0F7h, 0C1h, 00h, 00h, 00h, 04h, 74h, 04h, 84h, 0C0h, 74h
    db 2Ah, 0F7h, 0C1h, 00h, 00h, 00h, 08h, 74h, 04h, 84h, 0C0h, 75h, 1Eh, 0F7h, 0C1h, 00h
    db 00h, 00h, 40h, 74h, 2Ch, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 22h, 8Bh
    db 11h, 0FFh, 92h, 0F0h, 01h, 00h, 00h, 84h, 0C0h, 74h, 16h, 5Fh, 5Eh, 33h, 0C0h, 5Bh
    db 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h
    db 00h, 55h, 8Bh, 6Fh, 10h, 83h, 0FDh, 17h, 74h, 12h, 56h, 57h, 8Bh, 0CBh, 0E8h, 88h
    db 0D9h, 0B9h, 0FFh, 83h, 0F8h, 03h, 0Fh, 84h, 37h, 0Dh, 00h, 00h, 8Ah, 86h, 47h, 03h
    db 00h, 00h, 84h, 0C0h, 0Fh, 85h, 29h, 0Dh, 00h, 00h, 8Bh, 8Eh, 10h, 02h, 00h, 00h
    db 85h, 0C9h, 0Fh, 84h, 0C2h, 0Ah, 00h, 00h, 8Bh, 87h, 54h, 01h, 00h, 00h, 85h, 0C0h
    db 7Eh, 09h, 39h, 41h, 28h, 0Fh, 8Ch, 0AFh, 0Ah, 00h, 00h, 8Bh, 9Eh, 0A4h, 01h, 00h
    db 00h, 85h, 0DBh, 0Fh, 95h, 0C0h, 84h, 0C0h, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 0F6h, 0C7h
    db 01h, 74h, 16h, 8Dh, 4Ch, 24h, 60h, 89h, 5Ch, 24h, 60h, 0E8h, 0E4h, 9Dh, 0B9h, 0FFh
    db 83h, 0F8h, 01h, 0Fh, 84h, 80h, 00h, 00h, 00h, 0F7h, 47h, 18h, 00h, 00h, 10h, 00h
    db 74h, 17h, 0F6h, 0C3h, 40h, 74h, 12h, 8Dh, 4Ch, 24h, 60h, 89h, 5Ch, 24h, 60h, 0E8h
    db 0C0h, 9Dh, 0B9h, 0FFh, 83h, 0F8h, 01h, 74h, 60h, 8Ah, 44h, 24h, 70h, 84h, 0C0h, 75h
    db 58h, 83h, 0FDh, 10h, 74h, 53h, 83h, 0FDh, 26h, 74h, 4Eh, 83h, 0FDh, 0Fh, 74h, 49h
    db 83h, 0FDh, 13h, 74h, 44h, 83h, 0FDh, 14h, 74h, 3Fh, 83h, 0FDh, 1Ah, 74h, 3Ah, 8Bh
    db 44h, 24h, 6Ch, 8Bh, 4Ch, 24h, 64h, 6Ah, 01h, 50h, 56h, 51h, 8Bh, 4Ch, 24h, 28h
    db 57h, 0E8h, 0BEh, 0D0h, 0B9h, 0FFh, 33h, 0D2h, 83h, 0F8h, 03h, 0Fh, 95h, 0C2h, 5Dh, 5Fh
    db 5Eh, 5Bh, 4Ah, 83h, 0E2h, 03h, 8Bh, 0C2h, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 0F6h, 47h, 18h, 40h, 74h, 24h, 8Bh
    db 47h, 24h, 85h, 0C0h, 74h, 1Dh, 8Bh, 48h, 04h, 85h, 0C9h, 0Fh, 85h, 3Bh, 01h, 00h
    db 00h, 8Bh, 4Ch, 24h, 10h, 50h, 0E8h, 64h, 0F1h, 0B7h, 0FFh, 84h, 0C0h, 0Fh, 84h, 30h
    db 0Ch, 00h, 00h, 8Bh, 47h, 18h, 83h, 0CDh, 0FFh, 0F6h, 0C4h, 08h, 0Fh, 84h, 0DEh, 00h
    db 00h, 00h, 56h, 0E8h, 6Fh, 0A2h, 0B6h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 0CDh
    db 00h, 00h, 00h, 8Bh, 40h, 18h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 0C1h, 0ADh
    db 0B7h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 0Fh, 84h, 9Eh, 09h, 00h, 00h, 0F6h, 05h, 30h, 35h
    db 2Fh, 01h, 01h, 75h, 28h, 83h, 0Dh, 30h, 35h, 2Fh, 01h, 01h, 8Bh, 0Dh, 00h, 0D6h
    db 2Eh, 01h, 68h, 50h, 3Ch, 08h, 01h, 0C7h, 44h, 24h, 5Ch, 00h, 00h, 00h, 00h, 0E8h
    db 13h, 69h, 0B9h, 0FFh, 0A3h, 2Ch, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 0A1h, 2Ch, 35h
    db 2Fh, 01h, 50h, 8Bh, 0CBh, 0E8h, 49h, 69h, 0B8h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 74h, 70h
    db 33h, 0C9h, 89h, 4Ch, 24h, 34h, 89h, 4Ch, 24h, 38h, 89h, 4Ch, 24h, 3Ch, 89h, 4Ch
    db 24h, 40h, 89h, 4Ch, 24h, 44h, 8Dh, 54h, 24h, 1Ch, 89h, 4Ch, 24h, 48h, 88h, 4Ch
    db 24h, 4Ch, 52h, 8Bh, 0CFh, 0E8h, 0BFh, 0D7h, 0B7h, 0FFh, 8Bh, 08h, 89h, 4Ch, 24h, 34h
    db 8Bh, 50h, 04h, 89h, 54h, 24h, 38h, 8Bh, 48h, 08h, 89h, 4Ch, 24h, 3Ch, 8Bh, 50h
    db 0Ch, 89h, 54h, 24h, 40h, 8Bh, 48h, 10h, 89h, 4Ch, 24h, 44h, 8Bh, 50h, 14h, 8Dh
    db 44h, 24h, 34h, 50h, 68h, 1Fh, 0C1h, 42h, 00h, 8Bh, 0CBh, 89h, 54h, 24h, 50h, 0E8h
    db 0F8h, 61h, 0BAh, 0FFh, 8Ah, 44h, 24h, 4Ch, 84h, 0C0h, 0Fh, 84h, 0EAh, 08h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 0FBh, 0F5h, 0B5h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 0Fh, 84h, 9Eh, 00h, 00h
    db 00h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h, 48h, 85h, 0C0h, 74h, 0Dh, 0F7h, 47h, 18h, 00h
    db 00h, 01h, 00h, 0Fh, 85h, 1Ah, 0Bh, 00h, 00h, 8Bh, 03h, 8Bh, 0CBh, 0FFh, 50h, 38h
    db 83h, 0F8h, 14h, 0Fh, 94h, 0C1h, 88h, 4Ch, 24h, 70h, 0EBh, 7Ch, 83h, 0F9h, 01h, 0Fh
    db 85h, 0CEh, 0FEh, 0FFh, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 9Ah, 74h, 0B6h, 0FFh, 84h, 0C0h, 0Fh
    db 85h, 0BEh, 0FEh, 0FFh, 0FFh, 8Bh, 0CFh, 0E8h, 20h, 0C0h, 0B7h, 0FFh, 85h, 0C0h, 0Fh, 84h
    db 0DFh, 0Ah, 00h, 00h, 8Bh, 0CFh, 0E8h, 11h, 0C0h, 0B7h, 0FFh, 8Bh, 0C8h, 0E8h, 5Eh, 0A1h
    db 0B9h, 0FFh, 83h, 0F8h, 02h, 0Fh, 84h, 6Fh, 08h, 00h, 00h, 83h, 0F8h, 03h, 0Fh, 85h
    db 0BFh, 0Ah, 00h, 00h, 8Bh, 0CEh, 0E8h, 49h, 0C2h, 0B7h, 0FFh, 83h, 78h, 2Ch, 01h, 0Fh
    db 84h, 0AEh, 0Ah, 00h, 00h, 5Dh, 5Fh, 5Eh, 0B8h, 03h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch
    db 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 0C6h
    db 44h, 24h, 70h, 00h, 8Ah, 4Ch, 24h, 70h, 8Bh, 47h, 10h, 48h, 83h, 0F8h, 31h, 0Fh
    db 87h, 0D4h, 0Dh, 00h, 00h, 0Fh, 0B6h, 90h, 7Ch, 54h, 8Ah, 00h, 0FFh, 24h, 95h, 1Ch
    db 54h, 8Ah, 00h, 8Bh, 0CFh, 0E8h, 0A2h, 0BFh, 0B7h, 0FFh, 85h, 0C0h, 74h, 2Dh, 8Bh, 0CFh
    db 0E8h, 97h, 0BFh, 0B7h, 0FFh, 8Bh, 0C8h, 0E8h, 0E4h, 0A0h, 0B9h, 0FFh, 83h, 0F8h, 02h, 0Fh
    db 84h, 0F5h, 07h, 00h, 00h, 83h, 0F8h, 03h, 75h, 11h, 8Bh, 0CEh, 0E8h, 0D3h, 0C1h, 0B7h
    db 0FFh, 83h, 78h, 2Ch, 01h, 0Fh, 85h, 0DFh, 07h, 00h, 00h, 6Ah, 0Eh, 8Bh, 0CEh, 0E8h
    db 0BBh, 0DEh, 0B8h, 0FFh, 84h, 0C0h, 75h, 11h, 6Ah, 67h, 8Bh, 0CEh, 0E8h, 0AEh, 0DEh, 0B8h
    db 0FFh, 84h, 0C0h, 0Fh, 84h, 1Ah, 0Ah, 00h, 00h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h
    db 0C9h, 74h, 0Ch, 8Bh, 01h, 0FFh, 90h, 3Ch, 01h, 00h, 00h, 8Bh, 0D8h, 0EBh, 02h, 33h
    db 0DBh, 8Bh, 0CEh, 0E8h, 07h, 98h, 0B6h, 0FFh, 85h, 0DBh, 8Bh, 0E8h, 75h, 09h, 85h, 0EDh
    db 75h, 1Ah, 0E9h, 0ECh, 09h, 00h, 00h, 8Bh, 13h, 6Ah, 00h, 8Bh, 0CBh, 0FFh, 52h, 18h
    db 3Ch, 01h, 0Fh, 84h, 0DBh, 09h, 00h, 00h, 85h, 0EDh, 74h, 1Ah, 8Bh, 0CEh, 0E8h, 0DCh
    db 97h, 0B6h, 0FFh, 85h, 0C0h, 74h, 0Fh, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 84h, 0C0h
    db 0Fh, 85h, 0BDh, 09h, 00h, 00h, 8Bh, 0CFh, 0E8h, 0EFh, 0BEh, 0B7h, 0FFh, 8Bh, 74h, 24h
    db 10h, 50h, 8Bh, 0CEh, 0E8h, 65h, 34h, 0B6h, 0FFh, 84h, 0C0h, 75h, 22h, 8Ah, 87h, 4Dh
    db 01h, 00h, 00h, 0F6h, 0D8h, 5Dh, 5Fh, 5Eh, 5Bh, 1Bh, 0C0h, 83h, 0E0h, 03h, 8Bh, 4Ch
    db 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh
    db 0CFh, 0E8h, 0B6h, 0BEh, 0B7h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 56h, 49h, 0B7h, 0FFh, 84h, 0C0h
    db 0Fh, 85h, 0C3h, 0Ch, 00h, 00h, 5Dh, 5Fh, 5Eh, 0B8h, 05h, 00h, 00h, 00h, 5Bh, 8Bh
    db 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h
    db 0F6h, 05h, 30h, 35h, 2Fh, 01h, 02h, 75h, 28h, 83h, 0Dh, 30h, 35h, 2Fh, 01h, 02h
    db 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 50h, 3Ch, 08h, 01h, 0C7h, 44h, 24h, 5Ch, 01h
    db 00h, 00h, 00h, 0E8h, 6Fh, 66h, 0B9h, 0FFh, 0A3h, 28h, 35h, 2Fh, 01h, 89h, 6Ch, 24h
    db 58h, 0A1h, 28h, 35h, 2Fh, 01h, 50h, 8Bh, 0CEh, 0E8h, 0A5h, 66h, 0B8h, 0FFh, 8Bh, 0F8h
    db 85h, 0FFh, 0Fh, 84h, 0B2h, 06h, 00h, 00h, 8Bh, 0CFh, 0E8h, 01h, 6Ah, 0B6h, 0FFh, 84h
    db 0C0h, 0Fh, 84h, 0A3h, 06h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 84h, 0C0h, 0B7h, 0FFh
    db 50h, 8Bh, 0CFh, 0E8h, 4Bh, 02h, 0B6h, 0FFh, 84h, 0C0h, 0Fh, 84h, 8Ah, 06h, 00h, 00h
    db 5Dh, 5Fh, 5Eh, 0B8h, 02h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 0A0h, 30h, 35h, 2Fh, 01h, 0BBh
    db 04h, 00h, 00h, 00h, 84h, 0C3h, 75h, 27h, 09h, 1Dh, 30h, 35h, 2Fh, 01h, 8Bh, 0Dh
    db 00h, 0D6h, 2Eh, 01h, 68h, 50h, 3Ch, 08h, 01h, 0C7h, 44h, 24h, 5Ch, 02h, 00h, 00h
    db 00h, 0E8h, 0E1h, 65h, 0B9h, 0FFh, 0A3h, 24h, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 8Bh
    db 0Dh, 24h, 35h, 2Fh, 01h, 51h, 8Bh, 0CEh, 0E8h, 16h, 66h, 0B8h, 0FFh, 8Bh, 0F8h, 85h
    db 0FFh, 0Fh, 84h, 23h, 06h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 14h, 56h, 0B7h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 12h, 06h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0F3h, 0BFh, 0B7h
    db 0FFh, 50h, 8Bh, 0CFh, 0E8h, 0BAh, 01h, 0B6h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0F9h, 05h, 00h
    db 00h, 8Bh, 0CEh, 0E8h, 0DCh, 0BFh, 0B7h, 0FFh, 50h, 8Bh, 0CFh, 0E8h, 1Ch, 5Eh, 0B8h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 0CEh, 0FEh, 0FFh, 0FFh, 8Bh, 0CFh, 0E8h, 72h, 0D7h, 0B6h, 0FFh, 0D9h
    db 0C0h, 8Bh, 54h, 24h, 6Ch, 0D9h, 1Ah, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 01h, 0Fh, 84h, 38h, 0FFh, 0FFh, 0FFh, 5Dh, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 8Bh, 4Ch
    db 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh
    db 0CFh, 0E8h, 36h, 0BDh, 0B7h, 0FFh, 8Ah, 0Dh, 30h, 35h, 2Fh, 01h, 8Bh, 0D8h, 0B8h, 08h
    db 00h, 00h, 00h, 84h, 0C8h, 75h, 27h, 09h, 05h, 30h, 35h, 2Fh, 01h, 8Bh, 0Dh, 00h
    db 0D6h, 2Eh, 01h, 68h, 50h, 3Ch, 08h, 01h, 0C7h, 44h, 24h, 5Ch, 03h, 00h, 00h, 00h
    db 0E8h, 12h, 65h, 0B9h, 0FFh, 0A3h, 20h, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 0A1h, 20h
    db 35h, 2Fh, 01h, 50h, 8Bh, 0CEh, 0E8h, 48h, 65h, 0B8h, 0FFh, 85h, 0DBh, 8Bh, 0F8h, 0Fh
    db 84h, 55h, 05h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 4Dh, 05h, 00h, 00h, 6Ah, 00h, 8Bh
    db 0CFh, 0E8h, 3Eh, 55h, 0B7h, 0FFh, 84h, 0C0h, 0Fh, 84h, 3Ch, 05h, 00h, 00h, 6Ah, 00h
    db 8Bh, 0CEh, 0E8h, 1Dh, 0BFh, 0B7h, 0FFh, 50h, 8Bh, 0CFh, 0E8h, 0E4h, 00h, 0B6h, 0FFh, 84h
    db 0C0h, 0Fh, 84h, 23h, 05h, 00h, 00h, 53h, 8Bh, 0CEh, 0E8h, 05h, 0BFh, 0B7h, 0FFh, 50h
    db 8Bh, 0CFh, 0E8h, 71h, 0A1h, 0B6h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0F7h, 0FDh, 0FFh, 0FFh, 8Bh
    db 0CFh, 0E8h, 9Bh, 0D6h, 0B6h, 0FFh, 0D9h, 0C0h, 8Bh, 4Ch, 24h, 6Ch, 0D9h, 19h, 0D8h, 1Dh
    db 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 71h, 04h, 00h, 00h, 0E9h
    db 5Ch, 0FEh, 0FFh, 0FFh, 8Bh, 0CEh, 0E8h, 7Eh, 08h, 0B9h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 0Fh
    db 84h, 0D5h, 04h, 00h, 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 1Ch, 84h, 0C0h, 74h, 2Eh
    db 8Bh, 1Fh, 8Bh, 0CEh, 0E8h, 0ABh, 0BEh, 0B7h, 0FFh, 50h, 8Bh, 0CFh, 0FFh, 53h, 18h, 0F6h
    db 0D8h, 5Dh, 5Fh, 5Eh, 5Bh, 1Bh, 0C0h, 83h, 0E0h, 0FDh, 83h, 0C0h, 05h, 8Bh, 4Ch, 24h
    db 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 07h
    db 8Bh, 0CFh, 0FFh, 50h, 14h, 0F6h, 0D8h, 5Dh, 5Fh, 5Eh, 5Bh, 1Bh, 0C0h, 83h, 0E0h, 07h
    db 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h
    db 00h, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 0C5h, 06h, 00h, 00h, 8Bh, 0CFh
    db 0E8h, 0F7h, 0BBh, 0B7h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 0Fh, 84h, 5Bh, 04h, 00h, 00h, 8Bh
    db 0CFh, 0E8h, 3Ah, 9Dh, 0B9h, 0FFh, 83h, 0F8h, 02h, 0Fh, 84h, 4Bh, 04h, 00h, 00h, 83h
    db 0F8h, 03h, 75h, 11h, 8Bh, 0CEh, 0E8h, 29h, 0BEh, 0B7h, 0FFh, 83h, 78h, 2Ch, 01h, 0Fh
    db 85h, 35h, 04h, 00h, 00h, 8Ah, 44h, 24h, 70h, 84h, 0C0h, 0Fh, 85h, 15h, 0FDh, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 10h, 57h, 0E8h, 33h, 31h, 0B6h, 0FFh, 84h, 0C0h, 0Fh, 84h, 70h
    db 06h, 00h, 00h, 8Bh, 0Dh, 3Ch, 0D8h, 2Eh, 01h, 8Bh, 11h, 55h, 57h, 56h, 0FFh, 52h
    db 40h, 83h, 0F8h, 07h, 75h, 1Ah, 5Dh, 5Fh, 5Eh, 0B8h, 06h, 00h, 00h, 00h, 5Bh, 8Bh
    db 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h
    db 83h, 0F8h, 06h, 0Fh, 84h, 3Ah, 06h, 00h, 00h, 83h, 0F8h, 05h, 0Fh, 84h, 31h, 06h
    db 00h, 00h, 83h, 0F8h, 02h, 0Fh, 85h, 7Eh, 09h, 00h, 00h, 5Dh, 5Fh, 5Eh, 0B8h, 05h
    db 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 56h, 0E8h, 0F4h, 0EFh, 0B5h
    db 0FFh, 84h, 0C0h, 0Fh, 84h, 0A1h, 03h, 00h, 00h, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h
    db 0Fh, 85h, 0EDh, 05h, 00h, 00h, 8Bh, 0CEh, 0E8h, 77h, 0BDh, 0B7h, 0FFh, 8Bh, 0BFh, 0A0h
    db 00h, 00h, 00h, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 0D6h, 05h, 00h, 00h, 3Bh, 0FDh, 0Fh
    db 84h, 0CEh, 05h, 00h, 00h, 8Dh, 44h, 24h, 70h, 50h, 57h, 8Dh, 8Eh, 84h, 06h, 00h
    db 00h, 0C7h, 44h, 24h, 78h, 00h, 00h, 00h, 00h, 0E8h, 0A6h, 35h, 0B7h, 0FFh, 0D9h, 0C0h
    db 8Bh, 4Ch, 24h, 6Ch, 0D9h, 19h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 0C1h, 0DAh, 0E9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 07h, 0DDh, 0D8h, 0E9h, 95h, 05h, 00h, 00h, 0D9h, 05h
    db 34h, 53h, 07h, 01h, 0D9h, 0C9h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 0Fh, 8Ah, 0ADh
    db 02h, 00h, 00h, 8Bh, 56h, 4Ch, 3Bh, 54h, 24h, 70h, 5Dh, 1Bh, 0C0h, 5Fh, 83h, 0E0h
    db 04h, 5Eh, 40h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 0B6h, 0FCh, 01h, 00h, 00h, 85h, 0F6h, 0Fh, 84h, 0A6h
    db 08h, 00h, 00h, 8Bh, 06h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 90h, 00h, 01h, 00h, 00h, 85h
    db 0C0h, 0Fh, 86h, 92h, 08h, 00h, 00h, 0E9h, 37h, 05h, 00h, 00h, 8Bh, 47h, 20h, 85h
    db 0C0h, 0Fh, 84h, 0D3h, 02h, 00h, 00h, 84h, 0C9h, 0Fh, 85h, 0B7h, 0FBh, 0FFh, 0FFh, 8Bh
    db 5Ch, 24h, 10h, 50h, 8Bh, 0CBh, 0E8h, 44h, 0EAh, 0B7h, 0FFh, 3Ch, 01h, 74h, 4Bh, 8Bh
    db 47h, 20h, 50h, 8Bh, 0CBh, 0E8h, 04h, 0C1h, 0B7h, 0FFh, 3Ch, 01h, 74h, 3Ch, 8Bh, 77h
    db 20h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 32h, 0BAh, 0B7h, 0FFh, 50h, 56h, 53h, 8Bh, 0Dh, 88h
    db 0F1h, 2Eh, 01h, 0E8h, 01h, 83h, 0B7h, 0FFh, 84h, 0C0h, 0Fh, 85h, 39h, 08h, 00h, 00h
    db 5Dh, 5Fh, 5Eh, 0B8h, 05h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 5Dh, 5Fh, 5Eh, 0B8h, 07h, 00h
    db 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 4Ch, 0C2h, 14h, 00h, 8Bh, 47h, 20h, 85h, 0C0h, 0Fh, 84h, 4Bh, 02h, 00h, 00h, 68h
    db 95h, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 24h, 0D9h, 0B8h, 0FFh, 84h, 0C0h, 74h, 14h, 8Bh
    db 8Eh, 00h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 20h, 83h, 0F8h, 03h, 0Fh, 84h, 80h
    db 04h, 00h, 00h, 8Ah, 44h, 24h, 70h, 84h, 0C0h, 0Fh, 85h, 07h, 0FBh, 0FFh, 0FFh, 85h
    db 0DBh, 0Fh, 84h, 6Ch, 04h, 00h, 00h, 8Bh, 47h, 20h, 50h, 8Bh, 0CEh, 0E8h, 05h, 6Eh
    db 0B6h, 0FFh, 3Ch, 01h, 74h, 94h, 8Bh, 47h, 20h, 8Bh, 13h, 50h, 8Bh, 0CBh, 0FFh, 52h
    db 14h, 3Ch, 01h, 74h, 85h, 8Bh, 47h, 20h, 50h, 8Bh, 0CEh, 0E8h, 66h, 2Bh, 0B6h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 3Bh, 04h, 00h, 00h, 8Bh, 77h, 20h, 6Ah, 00h, 8Bh, 0CFh, 0E8h
    db 68h, 0B9h, 0B7h, 0FFh, 50h, 8Bh, 44h, 24h, 18h, 56h, 50h, 0E9h, 2Dh, 0FFh, 0FFh, 0FFh
    db 84h, 0C9h, 0Fh, 85h, 0AEh, 0FAh, 0FFh, 0FFh, 85h, 0DBh, 0Fh, 84h, 13h, 04h, 00h, 00h
    db 8Bh, 47h, 20h, 8Bh, 13h, 50h, 8Bh, 0CBh, 0FFh, 52h, 14h, 84h, 0C0h, 75h, 68h, 0F6h
    db 05h, 30h, 35h, 2Fh, 01h, 10h, 75h, 28h, 83h, 0Dh, 30h, 35h, 2Fh, 01h, 10h, 8Bh
    db 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 8Ch, 0Dh, 09h, 01h, 0C7h, 44h, 24h, 5Ch, 04h, 00h
    db 00h, 00h, 0E8h, 20h, 61h, 0B9h, 0FFh, 0A3h, 1Ch, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h
    db 0A1h, 1Ch, 35h, 2Fh, 01h, 50h, 8Bh, 0CEh, 0E8h, 56h, 61h, 0B8h, 0FFh, 85h, 0C0h, 74h
    db 26h, 8Bh, 48h, 18h, 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 73h, 0A5h, 0B7h, 0FFh
    db 85h, 0C0h, 74h, 13h, 8Bh, 4Fh, 20h, 51h, 8Bh, 0C8h, 0E8h, 48h, 6Dh, 0B6h, 0FFh, 84h
    db 0C0h, 0Fh, 85h, 0D3h, 0FEh, 0FFh, 0FFh, 8Bh, 77h, 20h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0C9h
    db 0B8h, 0B7h, 0FFh, 8Bh, 54h, 24h, 14h, 50h, 56h, 52h, 0E9h, 8Eh, 0FEh, 0FFh, 0FFh, 8Bh
    db 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 76h, 03h, 00h, 00h, 8Bh, 7Fh, 6Ch
    db 57h, 8Dh, 8Eh, 64h, 02h, 00h, 00h, 0E8h, 0BDh, 7Bh, 0B9h, 0FFh, 8Bh, 0F8h, 85h, 0FFh
    db 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 58h, 3Ch, 0Fh, 84h, 0ABh, 06h, 00h, 00h, 56h, 8Bh
    db 0CFh, 0E8h, 4Fh, 0FCh, 0B9h, 0FFh, 85h, 0C0h, 75h, 0Fh, 8Bh, 0CFh, 0E8h, 2Ch, 43h, 0B8h
    db 0FFh, 84h, 0C0h, 0Fh, 84h, 90h, 06h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 3Eh, 99h
    db 0B7h, 0FFh, 85h, 0C0h, 75h, 10h, 8Bh, 47h, 18h, 3Bh, 0C3h, 74h, 09h, 4Bh, 3Bh, 0C3h
    db 0Fh, 85h, 73h, 06h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 21h, 99h, 0B7h, 0FFh, 83h
    db 0F8h, 03h, 74h, 2Fh, 8Bh, 0CFh, 0E8h, 0F2h, 42h, 0B8h, 0FFh, 84h, 0C0h, 75h, 24h, 8Bh
    db 4Ch, 24h, 6Ch, 5Dh, 5Fh, 5Eh, 0C7h, 01h, 00h, 00h, 00h, 00h, 0B8h, 04h, 00h, 00h
    db 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch
    db 0C2h, 14h, 00h, 8Bh, 0CFh, 0E8h, 9Fh, 0FDh, 0B7h, 0FFh, 8Bh, 54h, 24h, 6Ch, 0D9h, 1Ah
    db 5Dh, 5Fh, 5Eh, 0B8h, 04h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 0C6h, 0E8h, 7Fh, 0F3h, 0FFh
    db 0FFh, 85h, 0C0h, 0Fh, 8Fh, 00h, 06h, 00h, 00h, 0E9h, 0A5h, 02h, 00h, 00h, 8Bh, 4Ch
    db 24h, 64h, 85h, 0C9h, 74h, 0Dh, 0E8h, 0DFh, 0EFh, 0B7h, 0FFh, 0A8h, 08h, 0Fh, 84h, 90h
    db 02h, 00h, 00h, 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 0Fh, 84h, 0D8h, 05h, 00h
    db 00h, 8Bh, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 14h, 52h, 68h, 0D0h, 41h, 8Ah, 00h, 0C6h
    db 44h, 24h, 20h, 00h, 89h, 74h, 24h, 1Ch, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Ah, 44h
    db 24h, 14h, 84h, 0C0h, 0Fh, 84h, 0AFh, 05h, 00h, 00h, 5Dh, 5Fh, 5Eh, 0B8h, 03h, 00h
    db 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 4Ch, 0C2h, 14h, 00h, 8Bh, 0B6h, 0FCh, 01h, 00h, 00h, 85h, 0F6h, 0Fh, 84h, 31h, 02h
    db 00h, 00h, 8Bh, 06h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 90h, 00h, 01h, 00h, 00h, 85h, 0C0h
    db 0Fh, 87h, 73h, 05h, 00h, 00h, 0E9h, 18h, 02h, 00h, 00h, 8Bh, 8Eh, 0FCh, 01h, 00h
    db 00h, 85h, 0C9h, 0Fh, 84h, 0Ah, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 92h, 08h, 01h, 00h
    db 00h, 85h, 0C0h, 0Fh, 84h, 0FAh, 01h, 00h, 00h, 8Bh, 0B6h, 0FCh, 01h, 00h, 00h, 8Bh
    db 06h, 8Bh, 0CEh, 0FFh, 90h, 08h, 01h, 00h, 00h, 8Bh, 0C8h, 0E8h, 0C6h, 72h, 0B6h, 0FFh
    db 85h, 0C0h, 0Fh, 87h, 31h, 05h, 00h, 00h, 0E9h, 0D6h, 01h, 00h, 00h, 8Ah, 8Fh, 52h
    db 01h, 00h, 00h, 84h, 0C9h, 8Bh, 47h, 34h, 89h, 44h, 24h, 70h, 0Fh, 84h, 68h, 0FFh
    db 0FFh, 0FFh, 85h, 0C0h, 0Fh, 84h, 60h, 0FFh, 0FFh, 0FFh, 8Bh, 0C8h, 0E8h, 54h, 0D6h, 0B6h
    db 0FFh, 8Bh, 0E8h, 83h, 0FDh, 0FFh, 74h, 50h, 8Bh, 0CEh, 0E8h, 35h, 0B9h, 0B7h, 0FFh, 8Bh
    db 0D8h, 85h, 0DBh, 0Fh, 84h, 41h, 0FFh, 0FFh, 0FFh, 8Bh, 0CBh, 0E8h, 0BDh, 2Ah, 0B7h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 32h, 0FFh, 0FFh, 0FFh, 55h, 8Bh, 0CBh, 0E8h, 2Fh, 45h, 0B6h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 22h, 0FFh, 0FFh, 0FFh, 55h, 8Bh, 0CBh, 0E8h, 9Dh, 0C3h, 0B9h, 0FFh
    db 84h, 0C0h, 0Fh, 85h, 6Bh, 01h, 00h, 00h, 55h, 8Bh, 0CBh, 0E8h, 0D6h, 6Dh, 0B7h, 0FFh
    db 84h, 0C0h, 0Fh, 85h, 5Bh, 01h, 00h, 00h, 8Bh, 6Ch, 24h, 70h, 55h, 8Bh, 0CEh, 0E8h
    db 7Bh, 0B2h, 0B9h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 0Fh, 85h, 9Eh, 00h, 00h, 00h, 8Dh, 4Ch
    db 24h, 64h, 51h, 8Bh, 0CFh, 0E8h, 0F7h, 0Eh, 0B7h, 0FFh, 8Bh, 0C8h, 0E8h, 0F1h, 77h, 0B6h
    db 0FFh, 8Ah, 0D8h, 0F6h, 0DBh, 1Ah, 0DBh, 8Dh, 4Ch, 24h, 64h, 0FEh, 0C3h, 0E8h, 0CEh, 29h
    db 3Eh, 00h, 84h, 0DBh, 0Fh, 84h, 6Fh, 04h, 00h, 00h, 8Dh, 54h, 24h, 60h, 52h, 8Bh
    db 0CFh, 0E8h, 0CBh, 0Eh, 0B7h, 0FFh, 8Bh, 0Dh, 0F8h, 33h, 2Fh, 01h, 50h, 0C7h, 44h, 24h
    db 5Ch, 05h, 00h, 00h, 00h, 0E8h, 03h, 66h, 0B9h, 0FFh, 8Dh, 4Ch, 24h, 60h, 8Bh, 0F8h
    db 0C7h, 44h, 24h, 58h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 93h, 29h, 3Eh, 00h, 85h, 0FFh, 0Fh
    db 84h, 34h, 04h, 00h, 00h, 83h, 7Fh, 10h, 17h, 0Fh, 85h, 2Ah, 04h, 00h, 00h, 8Bh
    db 7Fh, 34h, 85h, 0FFh, 0Fh, 84h, 1Fh, 04h, 00h, 00h, 57h, 8Bh, 0CEh, 0E8h, 0EDh, 0B1h
    db 0B9h, 0FFh, 5Dh, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 03h, 8Bh, 0CBh
    db 0FFh, 50h, 04h, 84h, 0C0h, 75h, 5Bh, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h, 08h, 0D9h, 0C0h
    db 8Bh, 6Ch, 24h, 6Ch, 0D9h, 5Dh, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 7Ah, 14h, 8Bh, 03h, 8Bh, 0CBh, 0FFh, 50h, 0Ch, 84h, 0C0h, 74h, 09h, 0C7h
    db 45h, 00h, 00h, 00h, 80h, 3Fh, 0EBh, 6Bh, 8Bh, 4Ch, 24h, 18h, 56h, 57h, 0E8h, 0A8h
    db 0CCh, 0B9h, 0FFh, 83h, 0E8h, 03h, 5Dh, 0F7h, 0D8h, 5Fh, 1Bh, 0C0h, 5Eh, 83h, 0E0h, 04h
    db 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h
    db 14h, 00h, 8Bh, 4Ch, 24h, 18h, 56h, 57h, 0E8h, 7Eh, 0CCh, 0B9h, 0FFh, 83h, 0F8h, 03h
    db 74h, 31h, 8Bh, 13h, 6Ah, 00h, 8Bh, 0CBh, 0FFh, 52h, 58h, 84h, 0C0h, 74h, 24h, 8Bh
    db 0CDh, 0E8h, 0C8h, 0B9h, 0B9h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 7Eh, 64h, 0BAh, 0FFh, 85h, 0C0h
    db 74h, 28h, 8Dh, 48h, 20h, 8Bh, 01h, 57h, 0FFh, 50h, 18h, 84h, 0C0h, 0Fh, 84h, 56h
    db 03h, 00h, 00h, 5Dh, 5Fh, 5Eh, 33h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h
    db 18h, 8Bh, 0C8h, 0E8h, 86h, 0B9h, 0B9h, 0FFh, 83h, 0F8h, 24h, 0Fh, 85h, 28h, 03h, 00h
    db 00h, 0F6h, 05h, 30h, 35h, 2Fh, 01h, 20h, 75h, 2Ch, 83h, 0Dh, 30h, 35h, 2Fh, 01h
    db 20h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 90h, 04h, 09h, 01h, 0C7h, 44h, 24h, 5Ch
    db 06h, 00h, 00h, 00h, 0E8h, 0EEh, 5Ch, 0B9h, 0FFh, 0A3h, 18h, 35h, 2Fh, 01h, 0C7h, 44h
    db 24h, 58h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h, 18h, 35h, 2Fh, 01h, 50h, 8Bh, 0CEh, 0E8h, 20h
    db 5Dh, 0B8h, 0FFh, 85h, 0C0h, 0Fh, 84h, 0DEh, 02h, 00h, 00h, 8Bh, 50h, 20h, 8Bh, 7Fh
    db 18h, 8Dh, 48h, 20h, 0FFh, 52h, 0Ch, 85h, 0C7h, 0Fh, 84h, 0CAh, 02h, 00h, 00h, 5Dh
    db 5Fh, 5Eh, 0B8h, 02h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h, 0F6h, 05h, 30h, 35h, 2Fh, 01h, 40h
    db 75h, 28h, 83h, 0Dh, 30h, 35h, 2Fh, 01h, 40h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h
    db 0C0h, 5Eh, 08h, 01h, 0C7h, 44h, 24h, 5Ch, 07h, 00h, 00h, 00h, 0E8h, 76h, 5Ch, 0B9h
    db 0FFh, 0A3h, 14h, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 0A1h, 14h, 35h, 2Fh, 01h, 50h
    db 8Bh, 0CEh, 0E8h, 0ACh, 5Ch, 0B8h, 0FFh, 85h, 0C0h, 74h, 07h, 8Dh, 58h, 0FCh, 85h, 0DBh
    db 75h, 23h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 88h, 0A2h, 08h, 01h, 0E8h, 45h, 5Ch
    db 0B9h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 89h, 5Ch, 0B8h, 0FFh, 85h, 0C0h, 74h, 05h, 8Dh, 58h
    db 0FCh, 0EBh, 02h, 33h, 0DBh, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 0F6h, 0C4h, 0B5h, 0FFh, 84h, 0C0h
    db 0Fh, 85h, 0DDh, 0FEh, 0FFh, 0FFh, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 0D0h
    db 0FEh, 0FFh, 0FFh, 85h, 0DBh, 0Fh, 84h, 0C8h, 0FEh, 0FFh, 0FFh, 8Bh, 13h, 8Bh, 0CBh, 0FFh
    db 52h, 28h, 84h, 0C0h, 0Fh, 84h, 0B9h, 0FEh, 0FFh, 0FFh, 8Bh, 47h, 10h, 83h, 0F8h, 2Ah
    db 74h, 29h, 83h, 0F8h, 29h, 75h, 0Bh, 8Bh, 03h, 8Bh, 0CBh, 0FFh, 50h, 18h, 84h, 0C0h
    db 74h, 19h, 83h, 7Fh, 10h, 28h, 0Fh, 85h, 97h, 0FEh, 0FFh, 0FFh, 8Bh, 13h, 8Bh, 0CBh
    db 0FFh, 52h, 18h, 3Ch, 01h, 0Fh, 85h, 88h, 0FEh, 0FFh, 0FFh, 5Dh, 5Fh, 5Eh, 0B8h, 02h
    db 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 4Ch, 0C2h, 14h, 00h, 8Bh, 47h, 6Ch, 50h, 8Dh, 8Eh, 64h, 02h, 00h, 00h, 0E8h
    db 0B5h, 76h, 0B9h, 0FFh, 85h, 0C0h, 0Fh, 84h, 57h, 0FEh, 0FFh, 0FFh, 8Bh, 0Dh, 8Ch, 14h
    db 2Fh, 01h, 8Bh, 01h, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Bh, 0E8h, 8Bh, 45h, 00h, 8Bh
    db 18h, 3Bh, 0D8h, 0Fh, 84h, 57h, 0F5h, 0FFh, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 73h, 08h, 85h, 0F6h, 74h, 3Fh, 8Bh, 8Eh, 0FCh, 00h, 00h, 00h, 85h, 0C9h, 74h
    db 35h, 0E8h, 1Bh, 0ADh, 0B7h, 0FFh, 84h, 0C0h, 74h, 2Ch, 8Bh, 8Eh, 0FCh, 00h, 00h, 00h
    db 6Ah, 00h, 0E8h, 0F8h, 0C7h, 0B8h, 0FFh, 85h, 0C0h, 74h, 1Bh, 8Bh, 0B6h, 0FCh, 00h, 00h
    db 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0E5h, 0C7h, 0B8h, 0FFh, 8Bh, 48h, 0Ch, 3Bh, 4Fh, 6Ch
    db 0Fh, 85h, 43h, 01h, 00h, 00h, 8Bh, 1Bh, 3Bh, 5Dh, 00h, 75h, 0B3h, 0E9h, 0FEh, 0F4h
    db 0FFh, 0FFh, 8Bh, 0CEh, 0E8h, 3Eh, 0F6h, 0B7h, 0FFh, 8Bh, 0D8h, 53h, 8Bh, 0CFh, 0E8h, 7Bh
    db 0BFh, 0B6h, 0FFh, 83h, 0F8h, 03h, 0Fh, 84h, 6Eh, 0FBh, 0FFh, 0FFh, 3Bh, 0C3h, 0Fh, 84h
    db 66h, 0FBh, 0FFh, 0FFh, 50h, 8Dh, 8Eh, 64h, 02h, 00h, 00h, 0E8h, 09h, 76h, 0B9h, 0FFh
    db 85h, 0C0h, 0Fh, 84h, 52h, 0FBh, 0FFh, 0FFh, 8Bh, 47h, 18h, 0F6h, 0C4h, 20h, 0Fh, 84h
    db 0F5h, 00h, 00h, 00h, 8Ah, 0Dh, 30h, 35h, 2Fh, 01h, 0B8h, 80h, 00h, 00h, 00h, 84h
    db 0C8h, 75h, 27h, 09h, 05h, 30h, 35h, 2Fh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h
    db 90h, 04h, 09h, 01h, 0C7h, 44h, 24h, 5Ch, 08h, 00h, 00h, 00h, 0E8h, 0B6h, 5Ah, 0B9h
    db 0FFh, 0A3h, 10h, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 8Bh, 15h, 10h, 35h, 2Fh, 01h
    db 52h, 8Bh, 0CEh, 0E8h, 0EBh, 5Ah, 0B8h, 0FFh, 85h, 0C0h, 0Fh, 84h, 0A9h, 00h, 00h, 00h
    db 8Bh, 0C8h, 0E8h, 0DAh, 7Ah, 0B8h, 0FFh, 83h, 0F8h, 01h, 0E9h, 3Eh, 0FDh, 0FFh, 0FFh, 6Ah
    db 12h, 8Bh, 0CEh, 0E8h, 4Ch, 0C3h, 0B5h, 0FFh, 84h, 0C0h, 0Fh, 84h, 33h, 0FDh, 0FFh, 0FFh
    db 8Bh, 0Dh, 30h, 35h, 2Fh, 01h, 0B8h, 00h, 01h, 00h, 00h, 85h, 0C8h, 75h, 29h, 0Bh
    db 0C8h, 89h, 0Dh, 30h, 35h, 2Fh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 3Ch, 40h
    db 08h, 01h, 0C7h, 44h, 24h, 5Ch, 09h, 00h, 00h, 00h, 0E8h, 48h, 5Ah, 0B9h, 0FFh, 0A3h
    db 0Ch, 35h, 2Fh, 01h, 89h, 6Ch, 24h, 58h, 0A1h, 0Ch, 35h, 2Fh, 01h, 50h, 8Bh, 0CEh
    db 0E8h, 7Eh, 5Ah, 0B8h, 0FFh, 85h, 0C0h, 74h, 40h, 8Bh, 0C8h, 0E8h, 8Ch, 8Ch, 0B8h, 0FFh
    db 84h, 0C0h, 75h, 35h, 0E9h, 0DAh, 0FCh, 0FFh, 0FFh, 8Bh, 0CFh, 0E8h, 0Ch, 0B2h, 0B7h, 0FFh
    db 8Bh, 0CEh, 8Bh, 0F8h, 0E8h, 0F0h, 7Fh, 0B6h, 0FFh, 85h, 0FFh, 0Fh, 84h, 0C2h, 0FCh, 0FFh
    db 0FFh, 85h, 0C0h, 0Fh, 84h, 0BAh, 0FCh, 0FFh, 0FFh, 8Bh, 10h, 57h, 8Bh, 0C8h, 0FFh, 52h
    db 60h, 84h, 0C0h, 0Fh, 84h, 0AAh, 0FCh, 0FFh, 0FFh, 5Dh, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h
    db 00h, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch
    db 0C2h, 14h, 00h, 8Bh, 4Ch, 24h, 4Ch, 5Fh, 5Eh, 0B8h, 03h, 00h, 00h, 00h, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C2h, 14h, 00h
?d_004a4240@@YAXXZ ENDP

; ghidra: FUN_008a5950  retail @ 0x004A5950 size 959
public ?d_004a5950@@YAXXZ
?d_004a5950@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Eh, 84h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 24h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h
    db 5Ch, 33h, 0EDh, 85h, 0C0h, 89h, 7Ch, 24h, 14h, 89h, 6Ch, 24h, 18h, 74h, 18h, 8Bh
    db 80h, 0FCh, 00h, 00h, 00h, 85h, 0C0h, 89h, 44h, 24h, 18h, 8Bh, 0E8h, 74h, 08h, 8Bh
    db 0B0h, 0FCh, 01h, 00h, 00h, 0EBh, 02h, 33h, 0F6h, 85h, 0F6h, 74h, 32h, 8Bh, 16h, 8Bh
    db 0CEh, 0FFh, 52h, 5Ch, 85h, 0C0h, 7Eh, 27h, 8Bh, 06h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 90h
    db 00h, 01h, 00h, 00h, 39h, 47h, 70h, 74h, 16h, 8Bh, 16h, 6Ah, 00h, 8Bh, 0CEh, 0FFh
    db 92h, 00h, 01h, 00h, 00h, 8Bh, 0CFh, 89h, 47h, 70h, 0E8h, 0BEh, 0C9h, 0B5h, 0FFh, 85h
    db 0EDh, 74h, 0Bh, 8Bh, 0CDh, 0E8h, 78h, 0E1h, 0B5h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h
    db 8Bh, 4Fh, 40h, 0E8h, 0CFh, 4Bh, 0B9h, 0FFh, 84h, 0C0h, 0Fh, 85h, 82h, 00h, 00h, 00h
    db 6Ah, 00h, 8Bh, 0CFh, 0E8h, 35h, 0CCh, 0B7h, 0FFh, 85h, 0F6h, 74h, 75h, 8Bh, 06h, 8Bh
    db 0CEh, 0FFh, 50h, 48h, 8Bh, 0D8h, 85h, 0DBh, 74h, 68h, 0F6h, 05h, 38h, 35h, 2Fh, 01h
    db 01h, 75h, 2Ch, 83h, 0Dh, 38h, 35h, 2Fh, 01h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 0F8h, 0BFh, 0Fh, 01h, 0C7h, 44h, 24h, 40h, 00h, 00h, 00h, 00h, 0E8h, 0A5h, 53h
    db 0B9h, 0FFh, 0A3h, 34h, 35h, 2Fh, 01h, 0C7h, 44h, 24h, 3Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h
    db 34h, 35h, 2Fh, 01h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 11h, 50h, 8Bh, 47h, 40h
    db 50h, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 0D9h, 43h, 14h, 8Bh, 8Fh, 6Ch, 02h, 00h, 00h
    db 8Bh, 0F0h, 51h, 0E8h, 0D0h, 13h, 55h, 00h, 50h, 56h, 0E8h, 0D6h, 8Ah, 0B9h, 0FFh, 83h
    db 0C4h, 0Ch, 85h, 0EDh, 74h, 0Dh, 8Bh, 0CDh, 0E8h, 14h, 0A5h, 0B7h, 0FFh, 88h, 44h, 24h
    db 11h, 0EBh, 05h, 0C6h, 44h, 24h, 11h, 00h, 8Dh, 97h, 00h, 01h, 00h, 00h, 89h, 54h
    db 24h, 1Ch, 0C7h, 44h, 24h, 2Ch, 14h, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 1Ch, 8Bh, 30h, 85h, 0F6h, 0Fh, 84h, 34h, 02h, 00h, 00h, 56h, 0E8h
    db 0D4h, 0B3h, 0B6h, 0FFh, 8Bh, 0E8h, 83h, 0C4h, 04h, 85h, 0EDh, 89h, 6Ch, 24h, 30h, 0Fh
    db 84h, 1Dh, 02h, 00h, 00h, 8Bh, 54h, 24h, 18h, 6Ah, 00h, 8Dh, 4Ch, 24h, 28h, 51h
    db 52h, 56h, 55h, 8Bh, 0CFh, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h, 0E8h, 0F2h, 0B9h
    db 0B9h, 0FFh, 8Bh, 0F8h, 8Ah, 44h, 24h, 11h, 32h, 0DBh, 84h, 0C0h, 0C6h, 44h, 24h, 13h
    db 00h, 88h, 5Ch, 24h, 12h, 75h, 2Ah, 0A1h, 48h, 0D7h, 2Eh, 01h, 8Bh, 48h, 0Ch, 0E8h
    db 0B9h, 1Eh, 0B7h, 0FFh, 84h, 0C0h, 74h, 14h, 85h, 0FFh, 0C6h, 44h, 24h, 12h, 01h, 74h
    db 2Dh, 83h, 0FFh, 03h, 74h, 10h, 0B3h, 01h, 33h, 0FFh, 0EBh, 22h, 0C6h, 44h, 24h, 13h
    db 01h, 83h, 0FFh, 03h, 75h, 0Fh, 8Bh, 0CEh, 0E8h, 8Ah, 4Ah, 0B9h, 0FFh, 84h, 0C0h, 0Fh
    db 85h, 0A9h, 01h, 00h, 00h, 85h, 0FFh, 74h, 05h, 83h, 0FFh, 06h, 75h, 12h, 0F7h, 45h
    db 18h, 00h, 00h, 40h, 00h, 74h, 09h, 84h, 0DBh, 75h, 05h, 0BFh, 03h, 00h, 00h, 00h
    db 83h, 7Dh, 10h, 0Fh, 8Bh, 0CEh, 75h, 21h, 68h, 00h, 00h, 00h, 01h, 0E8h, 0C1h, 0D9h
    db 0B8h, 0FFh, 83h, 0FFh, 03h, 0Fh, 85h, 73h, 01h, 00h, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h
    db 0B6h, 23h, 0B8h, 0FFh, 0E9h, 65h, 01h, 00h, 00h, 68h, 00h, 00h, 40h, 00h, 0E8h, 0A1h
    db 1Fh, 0B8h, 0FFh, 68h, 00h, 00h, 00h, 01h, 8Bh, 0CEh, 0E8h, 95h, 1Fh, 0B8h, 0FFh, 68h
    db 00h, 00h, 00h, 40h, 8Bh, 0CEh, 0E8h, 89h, 1Fh, 0B8h, 0FFh, 68h, 00h, 00h, 00h, 80h
    db 8Bh, 0CEh, 0E8h, 7Dh, 1Fh, 0B8h, 0FFh, 33h, 0EDh, 83h, 0FFh, 07h, 0C6h, 44h, 24h, 28h
    db 00h, 89h, 6Ch, 24h, 20h, 77h, 72h, 0FFh, 24h, 0BDh, 10h, 5Dh, 8Ah, 00h, 0C6h, 44h
    db 24h, 28h, 01h, 0EBh, 6Dh, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 2Dh, 46h, 0BAh, 0FFh, 68h, 00h
    db 00h, 00h, 80h, 8Bh, 0CEh, 0E8h, 49h, 0D9h, 0B8h, 0FFh, 83h, 0FFh, 07h, 75h, 53h, 68h
    db 00h, 00h, 00h, 01h, 8Bh, 0CEh, 0E8h, 38h, 0D9h, 0B8h, 0FFh, 0EBh, 45h, 8Bh, 4Ch, 24h
    db 14h, 8Bh, 0A9h, 6Ch, 02h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 89h, 6Ch, 24h, 24h, 0E8h
    db 0F7h, 45h, 0BAh, 0FFh, 68h, 00h, 00h, 40h, 00h, 8Bh, 0CEh, 0E8h, 13h, 0D9h, 0B8h, 0FFh
    db 0EBh, 20h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0E0h, 45h, 0BAh, 0FFh, 68h, 00h, 00h, 00h, 01h
    db 8Bh, 0CEh, 0E8h, 0FCh, 0D8h, 0B8h, 0FFh, 0EBh, 09h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0C9h, 45h
    db 0BAh, 0FFh, 0DBh, 44h, 24h, 20h, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 22h, 8Ah, 44h, 24h, 12h, 84h, 0C0h, 75h, 1Ah, 0D9h, 44h, 24h, 24h, 55h
    db 0D8h, 0Dh, 0C4h, 0FAh, 07h, 01h, 0E8h, 0DDh, 11h, 55h, 00h, 50h, 56h, 0E8h, 0E3h, 88h
    db 0B9h, 0FFh, 83h, 0C4h, 0Ch, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 20h, 8Bh, 0CEh, 0E8h
    db 66h, 0E1h, 0B7h, 0FFh, 0A8h, 08h, 74h, 15h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 7Ah, 45h, 0BAh
    db 0FFh, 68h, 00h, 00h, 00h, 40h, 8Bh, 0CEh, 0E8h, 96h, 0D8h, 0B8h, 0FFh, 8Bh, 54h, 24h
    db 28h, 52h, 8Bh, 0CEh, 0E8h, 91h, 22h, 0B8h, 0FFh, 8Bh, 5Ch, 24h, 30h, 8Ah, 83h, 51h
    db 01h, 00h, 00h, 84h, 0C0h, 75h, 09h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 4Bh, 45h, 0BAh, 0FFh
    db 8Bh, 0CBh, 0E8h, 15h, 0A9h, 0B7h, 0FFh, 6Ah, 00h, 56h, 0E8h, 8Ah, 5Fh, 0B6h, 0FFh, 8Bh
    db 43h, 18h, 83h, 0C4h, 08h, 0F6h, 0C4h, 04h, 74h, 14h, 83h, 0FFh, 02h, 75h, 04h, 6Ah
    db 01h, 0EBh, 02h, 6Ah, 00h, 56h, 0E8h, 8Eh, 0F9h, 0B5h, 0FFh, 83h, 0C4h, 08h, 8Bh, 7Ch
    db 24h, 14h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 44h, 24h, 2Ch, 83h, 0C1h, 04h, 48h, 89h, 4Ch
    db 24h, 1Ch, 89h, 44h, 24h, 2Ch, 0Fh, 85h, 0A4h, 0FDh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 34h
    db 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 30h, 0C3h
?d_004a5950@@YAXXZ ENDP

; ghidra: FUN_008a6570  retail @ 0x004A6570 size 71
public ?d_004a6570@@YAXXZ
?d_004a6570@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 38h, 8Bh, 0CEh, 0E8h, 11h, 9Ah, 0B7h, 0FFh
    db 84h, 0C0h, 74h, 2Dh, 8Bh, 0CEh, 0E8h, 78h, 0B6h, 0B5h, 0FFh, 84h, 0C0h, 74h, 22h, 8Bh
    db 0CEh, 0E8h, 04h, 9Eh, 0B9h, 0FFh, 84h, 0C0h, 75h, 17h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h
    db 8Bh, 01h, 0FFh, 90h, 60h, 01h, 00h, 00h, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C2h, 04h
    db 00h, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h
?d_004a6570@@YAXXZ ENDP

; ghidra: FUN_008a6c00  retail @ 0x004A6C00 size 176
public ?d_004a6c00@@YAXXZ
?d_004a6c00@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0F1h, 3Bh, 1Eh, 57h
    db 74h, 3Fh, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 75h, 10h, 8Bh, 44h, 24h, 18h, 85h, 0C0h
    db 75h, 2Fh, 8Bh, 45h, 00h, 3Bh, 43h, 10h, 7Ch, 27h, 6Ah, 18h, 0E8h, 0Fh, 79h, 38h
    db 00h, 8Bh, 0F8h, 8Dh, 4Fh, 10h, 55h, 51h, 0E8h, 6Bh, 9Eh, 0B8h, 0FFh, 89h, 7Bh, 0Ch
    db 8Bh, 06h, 8Bh, 48h, 0Ch, 83h, 0C4h, 0Ch, 3Bh, 0D9h, 75h, 36h, 89h, 78h, 0Ch, 0EBh
    db 31h, 6Ah, 18h, 0E8h, 0E8h, 78h, 38h, 00h, 8Bh, 0F8h, 8Dh, 57h, 10h, 55h, 52h, 0E8h
    db 44h, 9Eh, 0B8h, 0FFh, 89h, 7Bh, 08h, 8Bh, 06h, 83h, 0C4h, 0Ch, 3Bh, 0D8h, 75h, 0Ah
    db 89h, 78h, 04h, 8Bh, 06h, 89h, 78h, 0Ch, 0EBh, 08h, 3Bh, 58h, 08h, 75h, 03h, 89h
    db 78h, 08h, 33h, 0C0h, 89h, 5Fh, 04h, 89h, 47h, 08h, 89h, 47h, 0Ch, 8Bh, 0Eh, 83h
    db 0C1h, 04h, 51h, 57h, 0E8h, 37h, 5Dh, 38h, 00h, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 40h
    db 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 89h, 38h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 14h, 00h
?d_004a6c00@@YAXXZ ENDP

; ghidra: FUN_008a6d40  retail @ 0x004A6D40 size 145
public ?d_004a6d40@@YAXXZ
?d_004a6d40@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 9Ch, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 50h, 4Bh, 38h, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 7Dh, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 77h, 9Fh, 0B9h, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_004a6d40@@YAXXZ ENDP

; ghidra: FUN_008a9010  retail @ 0x004A9010 size 600
_TEXT ENDS
_TEXT$d008a9010 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x008A9010 size 600
public ?d_004a9010@@YAXXZ
?d_004a9010@@YAXXZ PROC
    db 083h, 0ECh, 010h, 08Bh, 044h, 024h, 014h, 053h, 055h, 033h, 0EDh, 03Bh, 0C5h, 08Bh, 0D9h, 089h
    db 05Ch, 024h, 010h, 00Fh, 084h, 037h, 002h, 000h, 000h, 056h, 08Bh, 0B0h, 0FCh, 000h, 000h, 000h
    db 03Bh, 0F5h, 089h, 074h, 024h, 018h, 00Fh, 084h, 023h, 002h, 000h, 000h, 06Ah, 02Fh, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 012h, 002h, 000h, 000h, 057h, 08Bh, 0CEh
    call ?j_00029dc0@@YAXXZ
    db 050h, 08Bh, 0CBh
    call ?j_00048cca@@YAXXZ
    db 08Bh, 0F8h, 03Bh, 0FDh, 089h, 07Ch, 024h, 014h, 08Dh, 0B3h, 000h, 001h, 000h, 000h, 075h, 028h
    db 0BFh, 014h, 000h, 000h, 000h, 08Bh, 00Eh, 03Bh, 0CDh, 089h, 0AEh, 0F0h, 000h, 000h, 000h, 074h
    db 007h, 06Ah, 001h
    call ?j_00027f2a@@YAXXZ
    db 083h, 0C6h, 004h, 04Fh, 075h, 0E7h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 010h, 0C2h, 008h, 000h
    db 080h, 07Ch, 024h, 028h, 001h, 00Fh, 085h, 038h, 001h, 000h, 000h, 089h, 06Ch, 024h, 024h, 089h
    db 074h, 024h, 010h, 08Bh, 044h, 024h, 024h, 050h, 08Bh, 0CFh
    call ?j_00003f80@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 00Fh, 084h, 0F3h, 000h, 000h, 000h, 08Bh, 045h, 018h, 0F6h, 0C4h, 001h
    db 00Fh, 084h, 0E7h, 000h, 000h, 000h, 08Bh, 00Eh, 085h, 0C9h, 089h, 0AEh, 0F0h, 000h, 000h, 000h
    db 00Fh, 084h, 0D7h, 000h, 000h, 000h, 06Ah, 000h
    call ?j_00027f2a@@YAXXZ
    db 08Bh, 00Eh, 06Ah, 001h
    call ?j_0004a1fb@@YAXXZ
    db 083h, 07Dh, 010h, 023h, 00Fh, 085h, 0A4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?TheInGameUI@@3PAUInGameUI@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 0FFh, 092h, 0FCh, 000h, 000h, 000h
    db 08Bh, 0D8h, 08Bh, 003h, 08Bh, 038h, 03Bh, 0F8h, 074h, 067h, 08Bh, 047h, 008h, 085h, 0C0h, 074h
    db 056h, 08Bh, 0B0h, 0FCh, 000h, 000h, 000h, 085h, 0F6h, 074h, 04Ch, 06Ah, 02Fh, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 075h, 03Fh, 06Ah, 013h, 08Bh, 0CEh
    call ?j_000016a4@@YAXXZ
    db 084h, 0C0h, 075h, 032h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_0000faa6@@YAXXZ
    db 085h, 0C0h, 074h, 025h, 08Bh, 0C8h
    call ?j_0000d3b9@@YAXXZ
    db 085h, 0C0h, 074h, 01Ah, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 092h, 0D8h, 000h, 000h, 000h, 084h, 0C0h
    db 08Bh, 044h, 024h, 028h, 074h, 003h, 048h, 0EBh, 001h, 040h, 089h, 044h, 024h, 028h, 08Bh, 03Fh
    db 03Bh, 03Bh, 075h, 09Dh, 08Bh, 074h, 024h, 010h, 08Bh, 054h, 024h, 028h, 033h, 0C0h, 085h, 0D2h
    db 00Fh, 09Dh, 0C0h, 08Bh, 0CDh, 050h
    call ?j_00011cd4@@YAXXZ
    db 08Bh, 05Ch, 024h, 018h, 08Bh, 07Ch, 024h, 014h, 0EBh, 00Eh, 08Bh, 04Ch, 024h, 01Ch, 06Ah, 000h
    db 051h, 08Bh, 0CDh
    call ?j_00006938@@YAXXZ
    db 08Bh, 016h, 055h, 052h, 08Bh, 0CBh
    call ?j_00015da7@@YAXXZ
    db 08Bh, 044h, 024h, 024h, 040h, 083h, 0C6h, 004h, 083h, 0F8h, 014h, 089h, 044h, 024h, 024h, 089h
    db 074h, 024h, 010h, 00Fh, 08Ch, 0DEh, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 010h
    db 0C2h, 008h, 000h, 08Bh, 07Ch, 024h, 014h, 055h, 08Bh, 0CFh
    call ?j_00003f80@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 006h, 083h, 07Fh, 010h, 009h, 074h, 010h, 08Bh, 086h, 0F0h, 000h
    db 000h, 000h, 085h, 0C0h, 074h, 03Ah, 083h, 078h, 010h, 009h, 075h, 034h, 08Bh, 086h, 0F0h, 000h
    db 000h, 000h, 085h, 0C0h, 0B1h, 001h, 075h, 02Ah, 08Bh, 00Eh, 085h, 0C9h, 089h, 0BEh, 0F0h, 000h
    db 000h, 000h, 074h, 03Dh, 050h
    call ?j_00027f2a@@YAXXZ
    db 08Bh, 00Eh, 06Ah, 001h
    call ?j_0004a1fb@@YAXXZ
    db 08Bh, 006h, 057h, 050h, 08Bh, 0CBh
    call ?j_00015da7@@YAXXZ
    db 0EBh, 021h, 032h, 0C9h, 03Bh, 0F8h, 074h, 01Bh, 084h, 0C9h, 075h, 017h, 08Bh, 00Eh, 085h, 0C9h
    db 0C7h, 086h, 0F0h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 074h, 007h, 06Ah, 001h
    call ?j_00027f2a@@YAXXZ
    db 045h, 083h, 0C6h, 004h, 083h, 0FDh, 014h, 00Fh, 08Ch, 076h, 0FFh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh
    db 05Bh, 083h, 0C4h, 010h, 0C2h, 008h, 000h
?d_004a9010@@YAXXZ ENDP
_TEXT$d008a9010 ENDS
_TEXT SEGMENT

; ghidra: FUN_008a9300  retail @ 0x004A9300 size 634
_TEXT ENDS
_TEXT$d008a9300 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x008A9300 size 634
public ?d_004a9300@@YAXXZ
?d_004a9300@@YAXXZ PROC
    db 083h, 0ECh, 018h, 053h, 055h, 089h, 04Ch, 024h, 00Ch, 08Bh, 00Dh
    dd ?TheInGameUI@@3PAUInGameUI@@A
    db 08Bh, 001h, 056h, 057h, 0FFh, 090h, 0FCh, 000h, 000h, 000h, 089h, 044h, 024h, 018h, 08Bh, 000h
    db 08Bh, 038h, 033h, 0DBh, 033h, 0EDh, 03Bh, 0F8h, 089h, 05Ch, 024h, 01Ch, 00Fh, 084h, 0DCh, 000h
    db 000h, 000h, 08Bh, 05Fh, 008h, 08Bh, 0B3h, 0FCh, 000h, 000h, 000h, 085h, 0F6h, 00Fh, 084h, 09Bh
    db 000h, 000h, 000h, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h
    db 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0D0h, 000h, 000h, 000h, 000h, 000h, 000h, 002h, 074h, 07Ch, 08Bh, 046h, 004h, 085h
    db 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0CCh, 000h, 000h, 000h, 084h, 0EDh, 078h, 05Fh, 056h, 08Dh, 04Ch, 024h, 024h, 051h
    db 08Bh, 00Dh
    dd ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A
    call ?j_0000edc7@@YAXXZ
    db 08Bh, 054h, 024h, 020h, 083h, 0ECh, 008h, 08Bh, 0C4h, 089h, 010h, 08Bh, 04Ch, 024h, 02Ch, 089h
    db 048h, 004h, 08Bh, 00Dh
    dd ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A
    call ?j_0000dfc1@@YAXXZ
    db 084h, 0C0h, 074h, 02Dh, 08Bh, 054h, 024h, 020h, 083h, 0ECh, 008h, 08Bh, 0C4h, 089h, 010h, 08Bh
    db 04Ch, 024h, 02Ch, 089h, 048h, 004h, 08Bh, 00Dh
    dd ?TheExperienceLevelSystem@@3PAVBfmeExperienceLevelSystem@@A
    call ?j_000012a8@@YAXXZ
    db 085h, 0EDh, 074h, 006h, 03Bh, 044h, 024h, 01Ch, 07Eh, 006h, 08Bh, 0EBh, 089h, 044h, 024h, 01Ch
    db 08Bh, 054h, 024h, 018h, 08Bh, 03Fh, 03Bh, 03Ah, 00Fh, 085h, 046h, 0FFh, 0FFh, 0FFh, 033h, 0DBh
    db 03Bh, 0EBh, 074h, 01Ch, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 05Ch, 08Bh, 085h, 0FCh, 000h, 000h
    db 000h, 053h, 050h
    call ?j_0000d495@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 018h, 0C3h, 08Bh, 07Ch, 024h, 014h, 081h, 0C7h, 000h, 001h
    db 000h, 000h, 0C6h, 044h, 024h, 01Ch, 001h, 0C6h, 044h, 024h, 013h, 000h, 089h, 05Ch, 024h, 020h
    db 08Bh, 0F7h, 0BDh, 014h, 000h, 000h, 000h, 08Dh, 064h, 024h, 000h, 08Bh, 006h, 085h, 0C0h, 0C7h
    db 086h, 0F0h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 074h, 00Bh, 06Ah, 000h, 050h
    call ?j_0000bc49@@YAXXZ
    db 083h, 0C4h, 008h, 083h, 0C6h, 004h, 04Dh, 075h, 0DFh, 0BEh, 014h, 000h, 000h, 000h, 08Bh, 00Fh
    db 085h, 0C9h, 074h, 007h, 06Ah, 001h
    call ?j_00027f2a@@YAXXZ
    db 083h, 0C7h, 004h, 04Eh, 075h, 0EDh, 08Bh, 04Ch, 024h, 018h, 08Bh, 001h, 08Bh, 028h, 03Bh, 0E8h
    db 00Fh, 084h, 0CDh, 000h, 000h, 000h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 075h, 008h
    db 08Bh, 0BEh, 0FCh, 000h, 000h, 000h, 08Bh, 047h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h
    db 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0CCh, 000h, 000h, 000h, 084h, 0EDh, 00Fh, 088h, 08Dh, 000h, 000h, 000h, 085h, 0FFh
    db 00Fh, 084h, 085h, 000h, 000h, 000h, 0F7h, 087h, 090h, 000h, 000h, 000h, 000h, 000h, 008h, 000h
    db 00Fh, 085h, 075h, 000h, 000h, 000h, 08Bh, 054h, 024h, 01Ch, 08Bh, 04Ch, 024h, 014h, 052h, 056h
    call ?j_00037740@@YAXXZ
    db 08Ah, 044h, 024h, 013h, 084h, 0C0h, 0C6h, 044h, 024h, 01Ch, 000h, 075h, 031h, 08Bh, 046h, 004h
    db 085h, 0C0h, 075h, 004h, 033h, 0C9h, 0EBh, 00Eh, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 0C8h
    call ?j_000166d0@@YAXXZ
    db 08Bh, 0D8h, 08Bh, 086h, 0FCh, 000h, 000h, 000h, 089h, 044h, 024h, 020h, 0C6h, 044h, 024h, 013h
    db 001h, 0EBh, 028h, 08Bh, 076h, 004h, 085h, 0F6h, 075h, 004h, 033h, 0C9h, 0EBh, 012h, 08Bh, 04Eh
    db 004h, 085h, 0C9h, 074h, 007h
    call ?j_000022bb@@YAXXZ
    db 0EBh, 002h, 08Bh, 0C6h, 08Bh, 0C8h
    call ?j_000166d0@@YAXXZ
    db 03Bh, 0C3h, 074h, 002h, 033h, 0DBh, 08Bh, 04Ch, 024h, 018h, 08Bh, 06Dh, 000h, 03Bh, 029h, 00Fh
    db 085h, 03Ah, 0FFh, 0FFh, 0FFh, 08Bh, 054h, 024h, 020h, 08Bh, 074h, 024h, 014h, 052h, 08Bh, 0CEh
    call ?j_0002262e@@YAXXZ
    db 08Bh, 00Dh
    dd ?Glo012F4B98@@3PAVGlo012F4B98Type@@A
    db 085h, 0C9h, 074h, 007h, 06Ah, 000h
    call ?j_0001f0d7@@YAXXZ
    db 08Bh, 08Eh, 0F0h, 002h, 000h, 000h
    call ?j_00033f19@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 018h, 0C3h
?d_004a9300@@YAXXZ ENDP
_TEXT$d008a9300 ENDS
_TEXT SEGMENT

; ghidra: FUN_008a9620  retail @ 0x004A9620 size 655
public ?d_004a9620@@YAXXZ
?d_004a9620@@YAXXZ PROC
    db 83h, 0ECh, 6Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 5Ch, 85h, 0C0h, 89h, 5Ch, 24h, 04h, 74h
    db 0Ah, 0E8h, 0F7h, 0D0h, 0B8h, 0FFh, 5Bh, 83h, 0C4h, 6Ch, 0C3h, 55h, 56h, 57h, 33h, 0C0h
    db 0B9h, 14h, 00h, 00h, 00h, 8Dh, 7Ch, 24h, 2Ch, 0F3h, 0ABh, 8Bh, 0Dh, 8Ch, 14h, 2Fh
    db 01h, 8Bh, 01h, 0FFh, 90h, 0FCh, 00h, 00h, 00h, 8Bh, 0F0h, 8Bh, 06h, 8Bh, 08h, 3Bh
    db 0C8h, 89h, 74h, 24h, 28h, 89h, 4Ch, 24h, 1Ch, 0Fh, 84h, 0DBh, 01h, 00h, 00h, 90h
    db 8Bh, 4Ch, 24h, 1Ch, 8Bh, 41h, 08h, 8Bh, 0B8h, 0FCh, 00h, 00h, 00h, 8Bh, 47h, 04h
    db 85h, 0C0h, 89h, 7Ch, 24h, 24h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 27h, 8Ch, 0B5h, 0FFh, 8Bh, 88h, 0CCh, 00h, 00h, 00h, 84h, 0EDh, 0Fh, 88h, 96h, 01h
    db 00h, 00h, 85h, 0FFh, 0Fh, 84h, 8Eh, 01h, 00h, 00h, 8Dh, 93h, 00h, 01h, 00h, 00h
    db 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 89h, 54h, 24h, 18h, 0EBh, 04h, 8Bh, 7Ch
    db 24h, 24h, 8Bh, 44h, 24h, 18h, 8Bh, 30h, 85h, 0F6h, 0Fh, 84h, 47h, 01h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 0E0h, 0Eh, 0B9h, 0FFh, 3Ch, 01h, 0Fh, 84h, 38h, 01h, 00h, 00h, 56h
    db 0E8h, 0A3h, 77h, 0B6h, 0FFh, 8Bh, 0E8h, 83h, 0C4h, 04h, 85h, 0EDh, 0Fh, 84h, 25h, 01h
    db 00h, 00h, 6Ah, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 57h, 56h, 55h, 8Bh, 0CBh, 0E8h, 0D1h
    db 7Dh, 0B9h, 0FFh, 68h, 00h, 00h, 40h, 00h, 8Bh, 0CEh, 8Bh, 0F8h, 0E8h, 13h, 0E4h, 0B7h
    db 0FFh, 68h, 00h, 00h, 00h, 01h, 8Bh, 0CEh, 0E8h, 07h, 0E4h, 0B7h, 0FFh, 68h, 00h, 00h
    db 00h, 40h, 8Bh, 0CEh, 0E8h, 0FBh, 0E3h, 0B7h, 0FFh, 68h, 00h, 00h, 00h, 80h, 8Bh, 0CEh
    db 0E8h, 0EFh, 0E3h, 0B7h, 0FFh, 33h, 0DBh, 83h, 0FFh, 07h, 77h, 72h, 0FFh, 24h, 0BDh, 0B0h
    db 98h, 8Ah, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0DEh, 0E7h, 0B7h, 0FFh, 0EBh, 69h, 6Ah, 00h
    db 8Bh, 0CEh, 0E8h, 0A4h, 0Ah, 0BAh, 0FFh, 68h, 00h, 00h, 00h, 80h, 8Bh, 0CEh, 0E8h, 0C0h
    db 9Dh, 0B8h, 0FFh, 83h, 0FFh, 07h, 75h, 4Fh, 68h, 00h, 00h, 00h, 01h, 8Bh, 0CEh, 0E8h
    db 0AFh, 9Dh, 0B8h, 0FFh, 0EBh, 41h, 8Bh, 54h, 24h, 10h, 8Bh, 9Ah, 6Ch, 02h, 00h, 00h
    db 6Ah, 00h, 8Bh, 0CEh, 0E8h, 72h, 0Ah, 0BAh, 0FFh, 68h, 00h, 00h, 40h, 00h, 8Bh, 0CEh
    db 0E8h, 8Eh, 9Dh, 0B8h, 0FFh, 0EBh, 20h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 5Bh, 0Ah, 0BAh, 0FFh
    db 68h, 00h, 00h, 00h, 01h, 8Bh, 0CEh, 0E8h, 77h, 9Dh, 0B8h, 0FFh, 0EBh, 09h, 6Ah, 01h
    db 8Bh, 0CEh, 0E8h, 44h, 0Ah, 0BAh, 0FFh, 0D9h, 44h, 24h, 20h, 0D8h, 1Dh, 34h, 53h, 07h
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Ah, 0D9h, 44h, 24h, 20h, 53h, 0D8h, 0Dh, 0C4h
    db 0FAh, 07h, 01h, 0E8h, 60h, 0D6h, 54h, 00h, 50h, 56h, 0E8h, 66h, 4Dh, 0B9h, 0FFh, 83h
    db 0C4h, 0Ch, 8Bh, 45h, 18h, 0F6h, 0C4h, 04h, 74h, 10h, 83h, 0FFh, 02h, 0Fh, 94h, 0C0h
    db 50h, 56h, 0E8h, 72h, 0BEh, 0B5h, 0FFh, 83h, 0C4h, 08h, 83h, 0FFh, 01h, 74h, 05h, 83h
    db 0FFh, 02h, 75h, 0Fh, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 84h, 2Ch, 8Dh, 44h, 84h, 2Ch
    db 41h, 89h, 08h, 8Bh, 5Ch, 24h, 10h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 18h, 40h
    db 83h, 0C2h, 04h, 83h, 0F8h, 14h, 89h, 44h, 24h, 14h, 89h, 54h, 24h, 18h, 0Fh, 8Ch
    db 8Ah, 0FEh, 0FFh, 0FFh, 8Bh, 74h, 24h, 28h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 01h, 3Bh, 06h
    db 89h, 44h, 24h, 1Ch, 0Fh, 85h, 26h, 0FEh, 0FFh, 0FFh, 33h, 0EDh, 8Dh, 0BBh, 0F0h, 01h
    db 00h, 00h, 8Bh, 0B7h, 10h, 0FFh, 0FFh, 0FFh, 85h, 0F6h, 74h, 42h, 8Bh, 0CEh, 0E8h, 54h
    db 0Dh, 0B9h, 0FFh, 3Ch, 01h, 74h, 37h, 83h, 3Fh, 00h, 74h, 32h, 8Bh, 44h, 0ACh, 2Ch
    db 85h, 0C0h, 8Bh, 0CEh, 7Eh, 21h, 6Ah, 01h, 0E8h, 7Eh, 09h, 0BAh, 0FFh, 68h, 00h, 00h
    db 00h, 80h, 8Bh, 0CEh, 0E8h, 9Bh, 0E2h, 0B7h, 0FFh, 68h, 00h, 00h, 00h, 01h, 8Bh, 0CEh
    db 0E8h, 8Fh, 0E2h, 0B7h, 0FFh, 0EBh, 07h, 6Ah, 00h, 0E8h, 5Dh, 09h, 0BAh, 0FFh, 45h, 83h
    db 0C7h, 04h, 83h, 0FDh, 14h, 7Ch, 0ABh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 6Ch, 0C3h
?d_004a9620@@YAXXZ ENDP

; ghidra: FUN_008ab3a0  retail @ 0x004AB3A0 size 30
public ?d_004ab3a0@@YAXXZ
?d_004ab3a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 6Ah, 0Ch, 0C7h, 06h, 00h, 00h, 00h, 00h, 0E8h, 90h, 31h, 38h, 00h
    db 89h, 00h, 89h, 40h, 04h, 89h, 06h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C3h
?d_004ab3a0@@YAXXZ ENDP

; ghidra: FUN_008ab630  retail @ 0x004AB630 size 312
public ?d_004ab630@@YAXXZ
?d_004ab630@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 86h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 57h, 89h, 4Ch, 24h, 10h, 33h, 0FFh
    db 6Ah, 24h, 89h, 7Ch, 24h, 20h, 0E8h, 0D5h, 68h, 3Dh, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h
    db 3Bh, 0F7h, 74h, 76h, 8Dh, 44h, 24h, 24h, 8Dh, 5Eh, 10h, 8Dh, 6Eh, 0Ch, 50h, 8Bh
    db 0CEh, 89h, 3Eh, 89h, 3Bh, 89h, 7Dh, 00h, 89h, 7Eh, 08h, 89h, 7Eh, 04h, 89h, 7Eh
    db 18h, 89h, 7Eh, 14h, 89h, 7Eh, 20h, 89h, 7Eh, 1Ch, 0E8h, 01h, 0C6h, 3Dh, 00h, 8Bh
    db 44h, 24h, 24h, 3Bh, 0C7h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h
    db 01h, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 39h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 50h
    db 0E8h, 22h, 0F7h, 0B8h, 0FFh, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 50h, 6Ah, 00h, 0FFh, 97h
    db 0DCh, 00h, 00h, 00h, 8Bh, 0F8h, 85h, 0FFh, 75h, 38h, 8Bh, 0CEh, 0E8h, 6Fh, 0C2h, 3Dh
    db 00h, 56h, 0E8h, 0D9h, 67h, 3Dh, 00h, 83h, 0C4h, 04h, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h
    db 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 55h, 0C2h, 3Dh, 00h, 33h, 0C0h, 8Bh, 4Ch, 24h
    db 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h, 53h, 55h, 8Bh, 0CFh, 0E8h, 83h, 0AEh, 0B8h, 0FFh, 8Dh, 46h, 08h, 50h, 8Dh
    db 46h, 04h, 50h, 8Bh, 0CFh, 0E8h, 0A2h, 0B7h, 0B8h, 0FFh, 8Bh, 54h, 24h, 10h, 8Bh, 3Ah
    db 6Ah, 0Ch, 0E8h, 19h, 2Eh, 38h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h
    db 02h, 89h, 31h, 8Bh, 4Fh, 04h, 89h, 48h, 04h, 89h, 38h, 89h, 01h, 8Dh, 4Ch, 24h
    db 24h, 89h, 47h, 04h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0EFh, 0C1h, 3Dh
    db 00h, 8Bh, 4Ch, 24h, 14h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_004ab630@@YAXXZ ENDP

; ghidra: FUN_008acd70  retail @ 0x004ACD70 size 12
public ?d_004acd70@@YAXXZ
?d_004acd70@@YAXXZ PROC
    db 0C7h, 41h, 14h, 00h, 00h, 00h, 00h, 0E9h, 0C4h, 0ABh, 3Dh, 00h
?d_004acd70@@YAXXZ ENDP

; ghidra: FUN_008ad250  retail @ 0x004AD250 size 357
public ?d_004ad250@@YAXXZ
?d_004ad250@@YAXXZ PROC
    db 51h, 53h, 56h, 57h, 8Bh, 0F1h, 8Dh, 9Eh, 58h, 01h, 00h, 00h, 0C7h, 44h, 24h, 0Ch
    db 06h, 00h, 00h, 00h, 55h, 8Bh, 03h, 8Bh, 38h, 3Bh, 0F8h, 74h, 20h, 8Dh, 49h, 00h
    db 8Bh, 6Fh, 08h, 85h, 0EDh, 74h, 10h, 8Bh, 0CDh, 0E8h, 0A6h, 0FEh, 0B6h, 0FFh, 55h, 0E8h
    db 2Ch, 4Ch, 3Dh, 00h, 83h, 0C4h, 04h, 8Bh, 3Fh, 3Bh, 3Bh, 75h, 0E3h, 8Bh, 03h, 8Bh
    db 38h, 3Bh, 0F8h, 74h, 15h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h, 4Fh, 13h, 38h
    db 00h, 8Bh, 03h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h, 0EBh, 8Bh, 03h, 89h, 00h, 8Bh, 03h
    db 89h, 40h, 04h, 8Bh, 44h, 24h, 10h, 83h, 0C3h, 04h, 48h, 89h, 44h, 24h, 10h, 75h
    db 0A4h, 8Bh, 86h, 70h, 01h, 00h, 00h, 8Bh, 28h, 3Bh, 0E8h, 74h, 2Ch, 8Dh, 49h, 00h
    db 8Bh, 7Dh, 08h, 33h, 0DBh, 3Bh, 0FBh, 74h, 13h, 8Bh, 0CFh, 89h, 5Fh, 08h, 0E8h, 51h
    db 90h, 0B5h, 0FFh, 57h, 0E8h, 0C7h, 4Bh, 3Dh, 00h, 83h, 0C4h, 04h, 8Bh, 6Dh, 00h, 3Bh
    db 0AEh, 70h, 01h, 00h, 00h, 75h, 0D9h, 0EBh, 02h, 33h, 0DBh, 8Bh, 86h, 70h, 01h, 00h
    db 00h, 8Bh, 38h, 3Bh, 0F8h, 5Dh, 74h, 19h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h
    db 0DCh, 12h, 38h, 00h, 8Bh, 86h, 70h, 01h, 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h
    db 0E7h, 8Bh, 86h, 70h, 01h, 00h, 00h, 89h, 00h, 8Bh, 86h, 70h, 01h, 00h, 00h, 8Bh
    db 0CEh, 89h, 40h, 04h, 0E8h, 07h, 0A6h, 3Dh, 00h, 8Dh, 4Eh, 0Ch, 89h, 5Eh, 08h, 89h
    db 5Eh, 04h, 0E8h, 0F9h, 0A5h, 3Dh, 00h, 5Fh, 89h, 5Eh, 10h, 89h, 5Eh, 14h, 89h, 5Eh
    db 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h, 89h, 5Eh, 44h, 89h, 5Eh, 48h
    db 89h, 5Eh, 4Ch, 89h, 5Eh, 50h, 89h, 5Eh, 54h, 89h, 5Eh, 58h, 89h, 5Eh, 5Ch, 89h
    db 5Eh, 60h, 89h, 5Eh, 64h, 89h, 5Eh, 68h, 89h, 5Eh, 6Ch, 89h, 5Eh, 70h, 89h, 5Eh
    db 74h, 89h, 5Eh, 78h, 89h, 5Eh, 7Ch, 89h, 9Eh, 80h, 00h, 00h, 00h, 89h, 9Eh, 84h
    db 00h, 00h, 00h, 89h, 9Eh, 88h, 00h, 00h, 00h, 89h, 9Eh, 8Ch, 00h, 00h, 00h, 89h
    db 9Eh, 90h, 00h, 00h, 00h, 89h, 9Eh, 54h, 01h, 00h, 00h, 89h, 9Eh, 50h, 01h, 00h
    db 00h, 5Eh, 5Bh, 59h, 0C3h
?d_004ad250@@YAXXZ ENDP

; ghidra: FUN_008ad4c0  retail @ 0x004AD4C0 size 256
public ?d_004ad4c0@@YAXXZ
?d_004ad4c0@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 56h, 57h, 8Dh, 0A9h, 60h, 01h, 00h, 00h, 0C7h, 44h, 24h
    db 10h, 03h, 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 38h, 3Bh, 0F8h, 0Fh, 84h, 0C2h, 00h
    db 00h, 00h, 8Bh, 47h, 08h, 85h, 0C0h, 0Fh, 84h, 0ACh, 00h, 00h, 00h, 8Bh, 58h, 14h
    db 85h, 0DBh, 0Fh, 84h, 0A1h, 00h, 00h, 00h, 8Bh, 48h, 08h, 0DBh, 44h, 24h, 34h, 8Bh
    db 50h, 10h, 03h, 0D1h, 89h, 54h, 24h, 14h, 0DBh, 44h, 24h, 14h, 89h, 4Ch, 24h, 18h
    db 8Bh, 48h, 04h, 8Bh, 40h, 0Ch, 0D8h, 4Ch, 24h, 2Ch, 03h, 0C1h, 89h, 44h, 24h, 14h
    db 89h, 4Ch, 24h, 1Ch, 0D8h, 0C1h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 8Bh, 0F1h
    db 0D9h, 5Ch, 24h, 20h, 0DBh, 44h, 24h, 30h, 0DBh, 44h, 24h, 14h, 0D8h, 4Ch, 24h, 28h
    db 0D8h, 0C1h, 0D9h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 2Ch, 0D8h, 0C2h
    db 0D9h, 5Ch, 24h, 18h, 0DBh, 44h, 24h, 1Ch, 0D8h, 4Ch, 24h, 28h, 0D8h, 0C1h, 0D9h, 5Ch
    db 24h, 1Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 20h
    db 8Bh, 54h, 24h, 14h, 8Bh, 06h, 6Ah, 02h, 6Ah, 0FFh, 51h, 8Bh, 4Ch, 24h, 24h, 52h
    db 8Bh, 54h, 24h, 2Ch, 51h, 52h, 53h, 8Bh, 0CEh, 0FFh, 90h, 0D4h, 00h, 00h, 00h, 8Bh
    db 06h, 8Bh, 0CEh, 0FFh, 90h, 0DCh, 00h, 00h, 00h, 8Bh, 3Fh, 3Bh, 7Dh, 00h, 0Fh, 85h
    db 3Eh, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 83h, 0EDh, 04h, 48h, 89h, 44h, 24h, 10h
    db 0Fh, 85h, 1Fh, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 14h, 0C2h, 10h, 00h
?d_004ad4c0@@YAXXZ ENDP

; ghidra: FUN_008ad600  retail @ 0x004AD600 size 256
public ?d_004ad600@@YAXXZ
?d_004ad600@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 56h, 57h, 8Dh, 0A9h, 6Ch, 01h, 00h, 00h, 0C7h, 44h, 24h
    db 10h, 03h, 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 38h, 3Bh, 0F8h, 0Fh, 84h, 0C2h, 00h
    db 00h, 00h, 8Bh, 47h, 08h, 85h, 0C0h, 0Fh, 84h, 0ACh, 00h, 00h, 00h, 8Bh, 58h, 14h
    db 85h, 0DBh, 0Fh, 84h, 0A1h, 00h, 00h, 00h, 8Bh, 48h, 08h, 0DBh, 44h, 24h, 34h, 8Bh
    db 50h, 10h, 03h, 0D1h, 89h, 54h, 24h, 14h, 0DBh, 44h, 24h, 14h, 89h, 4Ch, 24h, 18h
    db 8Bh, 48h, 04h, 8Bh, 40h, 0Ch, 0D8h, 4Ch, 24h, 2Ch, 03h, 0C1h, 89h, 44h, 24h, 14h
    db 89h, 4Ch, 24h, 1Ch, 0D8h, 0C1h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 8Bh, 0F1h
    db 0D9h, 5Ch, 24h, 20h, 0DBh, 44h, 24h, 30h, 0DBh, 44h, 24h, 14h, 0D8h, 4Ch, 24h, 28h
    db 0D8h, 0C1h, 0D9h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 2Ch, 0D8h, 0C2h
    db 0D9h, 5Ch, 24h, 18h, 0DBh, 44h, 24h, 1Ch, 0D8h, 4Ch, 24h, 28h, 0D8h, 0C1h, 0D9h, 5Ch
    db 24h, 1Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 20h
    db 8Bh, 54h, 24h, 14h, 8Bh, 06h, 6Ah, 02h, 6Ah, 0FFh, 51h, 8Bh, 4Ch, 24h, 24h, 52h
    db 8Bh, 54h, 24h, 2Ch, 51h, 52h, 53h, 8Bh, 0CEh, 0FFh, 90h, 0D4h, 00h, 00h, 00h, 8Bh
    db 06h, 8Bh, 0CEh, 0FFh, 90h, 0DCh, 00h, 00h, 00h, 8Bh, 3Fh, 3Bh, 7Dh, 00h, 0Fh, 85h
    db 3Eh, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 83h, 0EDh, 04h, 48h, 89h, 44h, 24h, 10h
    db 0Fh, 85h, 1Fh, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 14h, 0C2h, 10h, 00h
?d_004ad600@@YAXXZ ENDP

; ghidra: FUN_008ad740  retail @ 0x004AD740 size 245
public ?d_004ad740@@YAXXZ
?d_004ad740@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C8h, 86h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 10h
    db 8Dh, 4Ch, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 2Fh, 0A6h, 3Dh
    db 00h, 8Bh, 46h, 0Ch, 8Bh, 18h, 3Bh, 0D8h, 74h, 6Bh, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 6Bh, 08h, 85h, 0EDh, 74h, 5Eh, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 74h, 09h, 0Fh
    db 0B7h, 78h, 04h, 8Dh, 50h, 08h, 0EBh, 07h, 33h, 0FFh, 0BAh, 8Bh, 38h, 07h, 01h, 8Bh
    db 45h, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 70h, 04h, 0EBh, 02h, 33h, 0F6h, 85h, 0C0h
    db 8Dh, 48h, 08h, 75h, 05h, 0B9h, 8Bh, 38h, 07h, 01h, 3Bh, 0F7h, 8Bh, 0C6h, 7Ch, 02h
    db 8Bh, 0C7h, 50h, 52h, 51h, 0FFh, 15h, 10h, 93h, 35h, 01h, 83h, 0C4h, 0Ch, 85h, 0C0h
    db 75h, 08h, 2Bh, 0F7h, 8Bh, 0C6h, 85h, 0C0h, 74h, 33h, 8Bh, 44h, 24h, 10h, 8Bh, 1Bh
    db 3Bh, 58h, 0Ch, 75h, 9Bh, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 4Ah, 0A1h, 3Dh, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Dh, 4Ch, 24h
    db 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 22h, 0A1h, 3Dh, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C2h, 04h, 00h
?d_004ad740@@YAXXZ ENDP

; ghidra: FUN_008ad880  retail @ 0x004AD880 size 191
public ?d_004ad880@@YAXXZ
?d_004ad880@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 86h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 8Bh, 0F1h, 51h, 8Dh, 44h, 24h, 20h, 89h
    db 64h, 24h, 0Ch, 8Bh, 0CCh, 50h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 0ADh
    db 0A2h, 3Dh, 00h, 8Bh, 0CEh, 0E8h, 71h, 6Bh, 0B5h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h, 77h
    db 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 2Ch, 33h, 0D2h, 0F7h, 77h, 04h
    db 85h, 0C0h, 89h, 44h, 24h, 08h, 0DBh, 44h, 24h, 08h, 7Dh, 06h, 0D8h, 05h, 58h, 53h
    db 07h, 01h, 0D9h, 5Eh, 04h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h, 30h
    db 33h, 0D2h, 0F7h, 77h, 08h, 85h, 0C0h, 89h, 44h, 24h, 08h, 0DBh, 44h, 24h, 08h, 7Dh
    db 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 0CFh, 0D9h, 5Eh, 08h, 89h, 3Eh, 0E8h, 0B6h
    db 0Fh, 0B9h, 0FFh, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 1Ch, 0A0h, 3Dh, 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Eh, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0EBh, 0D4h
?d_004ad880@@YAXXZ ENDP

; ghidra: FUN_008ad970  retail @ 0x004AD970 size 12
public ?d_004ad970@@YAXXZ
?d_004ad970@@YAXXZ PROC
    db 8Bh, 09h, 85h, 0C9h, 74h, 05h, 0E9h, 41h, 51h, 0B6h, 0FFh, 0C3h
?d_004ad970@@YAXXZ ENDP

; ghidra: FUN_008adc80  retail @ 0x004ADC80 size 131
public ?d_004adc80@@YAXXZ
?d_004adc80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 6Bh, 87h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 8Bh, 0F1h, 33h, 0FFh, 6Ah, 0Ch, 89h, 74h
    db 24h, 0Ch, 89h, 7Eh, 0Ch, 0E8h, 96h, 08h, 38h, 00h, 89h, 00h, 89h, 40h, 04h, 83h
    db 0C4h, 04h, 89h, 46h, 0Ch, 89h, 3Eh, 8Bh, 46h, 0Ch, 89h, 7Ch, 24h, 14h, 8Bh, 38h
    db 3Bh, 0F8h, 74h, 16h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h, 20h, 09h, 38h, 00h
    db 8Bh, 46h, 0Ch, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h, 0EAh, 8Bh, 46h, 0Ch, 8Bh, 4Ch, 24h
    db 0Ch, 89h, 00h, 8Bh, 46h, 0Ch, 89h, 40h, 04h, 0B8h, 00h, 00h, 80h, 3Fh, 89h, 46h
    db 08h, 89h, 46h, 04h, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_004adc80@@YAXXZ ENDP

; ghidra: FUN_008ae3f0  retail @ 0x004AE3F0 size 45
public ?d_004ae3f0@@YAXXZ
?d_004ae3f0@@YAXXZ PROC
    db 56h, 8Bh, 31h, 6Ah, 0Ch, 0E8h, 46h, 01h, 38h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h
    db 85h, 0C9h, 74h, 08h, 8Bh, 54h, 24h, 08h, 8Bh, 12h, 89h, 11h, 8Bh, 4Eh, 04h, 89h
    db 30h, 89h, 48h, 04h, 89h, 01h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h
?d_004ae3f0@@YAXXZ ENDP

; ghidra: FUN_008ae430  retail @ 0x004AE430 size 698
public ?d_004ae430@@YAXXZ
?d_004ae430@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 29h, 88h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 33h, 0FFh
    db 89h, 74h, 24h, 14h, 89h, 3Eh, 89h, 7Ch, 24h, 20h, 89h, 7Eh, 0Ch, 68h, 76h, 0B9h
    db 43h, 00h, 68h, 0D5h, 91h, 43h, 00h, 6Ah, 06h, 6Ah, 04h, 8Dh, 0AEh, 58h, 01h, 00h
    db 00h, 55h, 0C6h, 44h, 24h, 34h, 01h, 0E8h, 68h, 8Ah, 54h, 00h, 6Ah, 0Ch, 0C6h, 44h
    db 24h, 24h, 02h, 89h, 0BEh, 70h, 01h, 00h, 00h, 0E8h, 0B2h, 00h, 38h, 00h, 89h, 00h
    db 89h, 40h, 04h, 83h, 0C4h, 04h, 89h, 86h, 70h, 01h, 00h, 00h, 8Bh, 18h, 3Bh, 0D8h
    db 0C6h, 44h, 24h, 20h, 03h, 74h, 19h, 8Bh, 0C3h, 8Bh, 1Bh, 6Ah, 0Ch, 50h, 0E8h, 3Dh
    db 01h, 38h, 00h, 8Bh, 86h, 70h, 01h, 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0D8h, 75h, 0E7h
    db 8Bh, 86h, 70h, 01h, 00h, 00h, 89h, 00h, 8Bh, 86h, 70h, 01h, 00h, 00h, 89h, 40h
    db 04h, 0C7h, 44h, 24h, 10h, 06h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 45h, 00h, 8Bh, 18h, 3Bh, 0D8h, 74h, 1Dh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0C3h, 8Bh, 1Bh, 6Ah, 0Ch, 50h, 0E8h, 0F4h, 00h, 38h, 00h, 8Bh, 45h, 00h, 83h
    db 0C4h, 08h, 3Bh, 0D8h, 75h, 0EAh, 8Bh, 45h, 00h, 89h, 00h, 8Bh, 45h, 00h, 89h, 40h
    db 04h, 8Bh, 44h, 24h, 10h, 83h, 0C5h, 04h, 48h, 89h, 44h, 24h, 10h, 75h, 0C1h, 8Bh
    db 0CEh, 0E8h, 1Ah, 94h, 3Dh, 00h, 8Dh, 4Eh, 0Ch, 89h, 7Eh, 08h, 89h, 7Eh, 04h, 0E8h
    db 0Ch, 94h, 3Dh, 00h, 0B8h, 0FFh, 0FFh, 0FFh, 00h, 89h, 7Eh, 10h, 89h, 7Eh, 14h, 0C7h
    db 46h, 18h, 00h, 00h, 00h, 80h, 89h, 46h, 1Ch, 89h, 46h, 20h, 89h, 46h, 24h, 89h
    db 46h, 28h, 89h, 46h, 2Ch, 89h, 7Eh, 34h, 89h, 7Eh, 38h, 89h, 7Eh, 3Ch, 89h, 7Eh
    db 40h, 89h, 7Eh, 30h, 89h, 7Eh, 44h, 89h, 7Eh, 48h, 89h, 7Eh, 4Ch, 89h, 7Eh, 50h
    db 89h, 7Eh, 54h, 89h, 7Eh, 58h, 89h, 7Eh, 5Ch, 89h, 7Eh, 60h, 89h, 7Eh, 64h, 89h
    db 7Eh, 68h, 89h, 7Eh, 6Ch, 89h, 7Eh, 70h, 89h, 7Eh, 74h, 89h, 7Eh, 78h, 89h, 7Eh
    db 7Ch, 89h, 0BEh, 80h, 00h, 00h, 00h, 89h, 0BEh, 84h, 00h, 00h, 00h, 89h, 0BEh, 88h
    db 00h, 00h, 00h, 89h, 0BEh, 8Ch, 00h, 00h, 00h, 89h, 0BEh, 90h, 00h, 00h, 00h, 89h
    db 0BEh, 54h, 01h, 00h, 00h, 89h, 0BEh, 50h, 01h, 00h, 00h, 89h, 0BEh, 94h, 00h, 00h
    db 00h, 89h, 0BEh, 98h, 00h, 00h, 00h, 89h, 0BEh, 9Ch, 00h, 00h, 00h, 89h, 0BEh, 0A0h
    db 00h, 00h, 00h, 89h, 0BEh, 0A4h, 00h, 00h, 00h, 89h, 0BEh, 0A8h, 00h, 00h, 00h, 89h
    db 0BEh, 0ACh, 00h, 00h, 00h, 89h, 0BEh, 0BCh, 00h, 00h, 00h, 89h, 0BEh, 0B0h, 00h, 00h
    db 00h, 89h, 0BEh, 0B4h, 00h, 00h, 00h, 89h, 0BEh, 0B8h, 00h, 00h, 00h, 89h, 0BEh, 0D0h
    db 00h, 00h, 00h, 89h, 0BEh, 0D8h, 00h, 00h, 00h, 89h, 0BEh, 0E0h, 00h, 00h, 00h, 89h
    db 0BEh, 0E8h, 00h, 00h, 00h, 89h, 0BEh, 0F0h, 00h, 00h, 00h, 89h, 0BEh, 0F8h, 00h, 00h
    db 00h, 89h, 0BEh, 00h, 01h, 00h, 00h, 89h, 0BEh, 08h, 01h, 00h, 00h, 89h, 0BEh, 10h
    db 01h, 00h, 00h, 89h, 0BEh, 18h, 01h, 00h, 00h, 89h, 0BEh, 20h, 01h, 00h, 00h, 89h
    db 0BEh, 28h, 01h, 00h, 00h, 89h, 0BEh, 30h, 01h, 00h, 00h, 89h, 0BEh, 38h, 01h, 00h
    db 00h, 89h, 0BEh, 40h, 01h, 00h, 00h, 89h, 0BEh, 48h, 01h, 00h, 00h, 89h, 0BEh, 0D4h
    db 00h, 00h, 00h, 89h, 0BEh, 0DCh, 00h, 00h, 00h, 89h, 0BEh, 0E4h, 00h, 00h, 00h, 89h
    db 0BEh, 0ECh, 00h, 00h, 00h, 89h, 0BEh, 0F4h, 00h, 00h, 00h, 89h, 0BEh, 0FCh, 00h, 00h
    db 00h, 89h, 0BEh, 04h, 01h, 00h, 00h, 89h, 0BEh, 0Ch, 01h, 00h, 00h, 89h, 0BEh, 14h
    db 01h, 00h, 00h, 89h, 0BEh, 1Ch, 01h, 00h, 00h, 89h, 0BEh, 24h, 01h, 00h, 00h, 89h
    db 0BEh, 2Ch, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h, 0BEh, 34h, 01h, 00h, 00h, 89h
    db 0BEh, 3Ch, 01h, 00h, 00h, 89h, 0BEh, 44h, 01h, 00h, 00h, 89h, 0BEh, 4Ch, 01h, 00h
    db 00h, 89h, 0BEh, 0C0h, 00h, 00h, 00h, 89h, 0BEh, 0C4h, 00h, 00h, 00h, 89h, 0BEh, 0C8h
    db 00h, 00h, 00h, 89h, 0BEh, 0CCh, 00h, 00h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_004ae430@@YAXXZ ENDP

; ghidra: FUN_008aed60  retail @ 0x004AED60 size 117
public ?d_004aed60@@YAXXZ
?d_004aed60@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 56h, 39h, 0Ch, 0C5h, 48h, 34h, 2Fh, 01h, 74h, 0Ch
    db 40h, 83h, 0F8h, 14h, 7Ch, 0F1h, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h, 8Bh, 34h, 0C5h, 4Ch
    db 34h, 2Fh, 01h, 85h, 0F6h, 74h, 41h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h
    db 00h, 00h, 00h, 57h, 8Bh, 0B9h, 0B8h, 00h, 00h, 00h, 2Bh, 0F8h, 0C1h, 0FFh, 02h, 33h
    db 0D2h, 8Bh, 0C6h, 0F7h, 0F7h, 8Bh, 81h, 0B4h, 00h, 00h, 00h, 5Fh, 8Bh, 14h, 90h, 85h
    db 0D2h, 74h, 15h, 39h, 72h, 04h, 74h, 0Ch, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 33h, 0C0h
    db 5Eh, 0C2h, 04h, 00h, 85h, 0D2h, 75h, 06h, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h, 8Bh, 42h
    db 08h, 5Eh, 0C2h, 04h, 00h
?d_004aed60@@YAXXZ ENDP

; ghidra: FUN_008af3d0  retail @ 0x004AF3D0 size 151
public ?d_004af3d0@@YAXXZ
?d_004af3d0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 5Ch, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 8Bh, 0B0h
    db 0FCh, 00h, 00h, 00h, 8Bh, 59h, 0Ch, 8Bh, 0CEh, 0E8h, 0A3h, 0Bh, 0B7h, 0FFh, 84h, 0C0h
    db 75h, 4Eh, 8Bh, 86h, 3Ch, 02h, 00h, 00h, 50h, 8Bh, 0CBh, 0E8h, 7Ah, 0F3h, 0B8h, 0FFh
    db 83h, 0F8h, 01h, 74h, 3Bh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 0F8h, 85h, 0FFh
    db 74h, 51h, 8Bh, 0Dh, 0ECh, 0D5h, 2Eh, 01h, 8Bh, 01h, 68h, 0ECh, 03h, 00h, 00h, 0FFh
    db 50h, 34h, 8Bh, 4Eh, 74h, 51h, 8Bh, 0C8h, 0E8h, 0BFh, 0C8h, 0B7h, 0FFh, 8Bh, 0Dh, 8Ch
    db 14h, 2Fh, 01h, 8Bh, 11h, 57h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 0C3h
    db 8Bh, 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 19h, 8Bh, 01h, 6Ah, 00h, 0FFh, 90h
    db 00h, 01h, 00h, 00h, 39h, 47h, 70h, 74h, 0Ah, 6Ah, 00h, 56h, 8Bh, 0CFh, 0E8h, 0EAh
    db 0EAh, 0B6h, 0FFh, 5Fh, 5Eh, 5Bh, 0C3h
?d_004af3d0@@YAXXZ ENDP

; ghidra: FUN_008af660  retail @ 0x004AF660 size 48
public ?d_004af660@@YAXXZ
?d_004af660@@YAXXZ PROC
    db 8Bh, 41h, 5Ch, 8Bh, 90h, 0FCh, 00h, 00h, 00h, 0F6h, 82h, 90h, 00h, 00h, 00h, 04h
    db 75h, 05h, 0E9h, 16h, 2Dh, 0B5h, 0FFh, 0D9h, 82h, 20h, 02h, 00h, 00h, 0D9h, 41h, 68h
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 06h, 52h, 0E8h, 46h, 98h, 0B6h, 0FFh, 0C3h
?d_004af660@@YAXXZ ENDP

; ghidra: FUN_008af6a0  retail @ 0x004AF6A0 size 627
public ?d_004af6a0@@YAXXZ
?d_004af6a0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 60h, 89h, 02h, 01h, 50h, 8Bh, 44h
    db 24h, 10h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 55h, 33h, 0EDh, 3Bh
    db 0C5h, 57h, 8Bh, 0F9h, 75h, 26h, 8Bh, 0Dh, 98h, 4Bh, 2Fh, 01h, 3Bh, 0CDh, 0Fh, 84h
    db 2Ch, 02h, 00h, 00h, 0E8h, 0A3h, 3Fh, 0B8h, 0FFh, 5Fh, 5Dh, 8Bh, 4Ch, 24h, 14h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 20h, 0C2h, 04h, 00h, 53h, 56h, 8Dh, 0B7h
    db 00h, 01h, 00h, 00h, 0BBh, 14h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Eh, 3Bh, 0CDh, 74h, 12h, 6Ah, 01h, 0E8h, 1Dh, 88h, 0B7h, 0FFh, 8Bh, 06h, 55h
    db 50h, 8Bh, 0CFh, 0E8h, 8Fh, 66h, 0B6h, 0FFh, 83h, 0C6h, 04h, 4Bh, 75h, 0E2h, 8Bh, 0Dh
    db 0F8h, 33h, 2Fh, 01h, 83h, 0B9h, 0ECh, 02h, 00h, 00h, 01h, 0Fh, 94h, 0C3h, 89h, 6Ch
    db 24h, 18h, 89h, 6Ch, 24h, 1Ch, 89h, 6Ch, 24h, 20h, 8Bh, 4Ch, 24h, 34h, 89h, 6Ch
    db 24h, 2Ch, 0E8h, 4Ah, 08h, 0B7h, 0FFh, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 88h, 44h, 24h
    db 13h, 0E8h, 86h, 39h, 0B8h, 0FFh, 84h, 0C0h, 75h, 0Dh, 8Ah, 44h, 24h, 13h, 84h, 0C0h
    db 0C6h, 44h, 24h, 12h, 00h, 74h, 05h, 0C6h, 44h, 24h, 12h, 01h, 68h, 7Ch, 0D1h, 0Fh
    db 01h, 8Dh, 4Ch, 24h, 18h, 0E8h, 46h, 94h, 3Dh, 00h, 8Dh, 54h, 24h, 14h, 52h, 8Bh
    db 0CFh, 0C6h, 44h, 24h, 30h, 01h, 0E8h, 12h, 0BEh, 0B8h, 0FFh, 8Dh, 4Ch, 24h, 14h, 8Bh
    db 0E8h, 0C6h, 44h, 24h, 2Ch, 00h, 0E8h, 0A5h, 81h, 3Dh, 00h, 85h, 0EDh, 8Bh, 0B7h, 00h
    db 01h, 00h, 00h, 89h, 74h, 24h, 14h, 0Fh, 84h, 0BAh, 00h, 00h, 00h, 85h, 0F6h, 0Fh
    db 84h, 0B2h, 00h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 6Ch, 87h, 0B7h, 0FFh, 84h, 0DBh
    db 74h, 4Bh, 8Ah, 44h, 24h, 12h, 84h, 0C0h, 74h, 43h, 68h, 00h, 00h, 00h, 04h, 8Bh
    db 0CEh, 0E8h, 4Dh, 3Dh, 0B8h, 0FFh, 8Bh, 44h, 24h, 1Ch, 3Bh, 44h, 24h, 20h, 74h, 13h
    db 85h, 0C0h, 74h, 06h, 89h, 30h, 8Bh, 44h, 24h, 1Ch, 83h, 0C0h, 04h, 89h, 44h, 24h
    db 1Ch, 0EBh, 26h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 3Ch, 51h, 8Dh, 54h, 24h, 20h
    db 52h, 50h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0C2h, 5Eh, 0B5h, 0FFh, 0EBh, 0Ch, 68h, 00h, 00h
    db 00h, 04h, 8Bh, 0CEh, 0E8h, 0Bh, 83h, 0B7h, 0FFh, 55h, 56h, 8Bh, 0CFh, 0E8h, 85h, 65h
    db 0B6h, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 17h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0C8h
    db 0A9h, 0B9h, 0FFh, 68h, 00h, 00h, 00h, 40h, 8Bh, 0CEh, 0E8h, 0E5h, 82h, 0B7h, 0FFh, 0EBh
    db 26h, 0A1h, 48h, 0D7h, 2Eh, 01h, 8Bh, 48h, 0Ch, 0E8h, 6Fh, 81h, 0B6h, 0FFh, 84h, 0C0h
    db 8Bh, 0CEh, 6Ah, 00h, 75h, 0D8h, 0E8h, 0A0h, 0A9h, 0B9h, 0FFh, 68h, 00h, 00h, 00h, 40h
    db 8Bh, 0CEh, 0E8h, 0BCh, 3Ch, 0B8h, 0FFh, 8Bh, 74h, 24h, 34h, 56h, 8Bh, 0CFh, 0E8h, 62h
    db 96h, 0B6h, 0FFh, 56h, 8Bh, 0CFh, 0E8h, 0B3h, 2Dh, 0B7h, 0FFh, 8Bh, 0CEh, 0E8h, 0CCh, 44h
    db 0B7h, 0FFh, 85h, 0C0h, 74h, 0Fh, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 20h, 50h, 8Bh, 0CFh
    db 0E8h, 0A1h, 0DBh, 0B5h, 0FFh, 8Bh, 0Dh, 98h, 4Bh, 2Fh, 01h, 85h, 0C9h, 74h, 06h, 56h
    db 0E8h, 32h, 0F8h, 0B6h, 0FFh, 8Bh, 8Fh, 0F0h, 02h, 00h, 00h, 8Dh, 44h, 24h, 18h, 50h
    db 0E8h, 0A3h, 52h, 0B8h, 0FFh, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 5Eh, 0C7h, 44h, 24h, 28h
    db 0FFh, 0FFh, 0FFh, 0FFh, 5Bh, 74h, 39h, 8Bh, 44h, 24h, 18h, 2Bh, 0C1h, 0C1h, 0F8h, 02h
    db 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Ch, 51h, 0E8h, 0D0h, 25h, 3Dh, 00h
    db 83h, 0C4h, 04h, 5Fh, 5Dh, 8Bh, 4Ch, 24h, 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 20h, 0C2h, 04h, 00h, 50h, 51h, 0E8h, 0F3h, 0ECh, 37h, 00h, 83h, 0C4h, 08h
    db 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 20h
    db 0C2h, 04h, 00h
?d_004af6a0@@YAXXZ ENDP

; ghidra: FUN_008afa10  retail @ 0x004AFA10 size 75
public ?d_004afa10@@YAXXZ
?d_004afa10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0D9h, 46h, 0Ch, 0D9h, 44h, 24h, 08h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Ah, 10h, 0D9h, 46h, 10h, 0D9h, 44h, 24h, 0Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Bh, 24h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 08h, 50h, 51h, 8Dh, 56h, 08h
    db 52h, 0E8h, 0EEh, 0C1h, 0B6h, 0FFh, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 18h, 83h, 0C4h
    db 0Ch, 89h, 46h, 0Ch, 89h, 4Eh, 10h, 5Eh, 0C2h, 08h, 00h
?d_004afa10@@YAXXZ ENDP

; ghidra: FUN_008afa80  retail @ 0x004AFA80 size 25
public ?d_004afa80@@YAXXZ
?d_004afa80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 09h, 8Bh, 40h, 74h, 89h, 41h, 1Ch, 0C2h, 04h
    db 00h, 33h, 0C0h, 89h, 41h, 1Ch, 0C2h, 04h, 00h
?d_004afa80@@YAXXZ ENDP

; ghidra: FUN_008aff40  retail @ 0x004AFF40 size 26
public ?d_004aff40@@YAXXZ
?d_004aff40@@YAXXZ PROC
    db 8Bh, 09h, 85h, 0C9h, 74h, 13h, 8Bh, 51h, 04h, 4Ah, 8Bh, 0C2h, 85h, 0C0h, 89h, 51h
    db 04h, 7Fh, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C3h
?d_004aff40@@YAXXZ ENDP

; ghidra: FUN_008aff60  retail @ 0x004AFF60 size 27
public ?d_004aff60@@YAXXZ
?d_004aff60@@YAXXZ PROC
    db 8Bh, 49h, 04h, 85h, 0C9h, 74h, 13h, 8Bh, 51h, 04h, 4Ah, 8Bh, 0C2h, 85h, 0C0h, 89h
    db 51h, 04h, 7Fh, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C3h
?d_004aff60@@YAXXZ ENDP

; ghidra: FUN_008b00e0  retail @ 0x004B00E0 size 53
public ?d_004b00e0@@YAXXZ
?d_004b00e0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 56h, 8Bh, 74h, 24h, 10h, 3Bh, 0F3h, 74h, 1Ah, 57h, 8Bh
    db 7Ch, 24h, 1Ch, 8Bh, 0Eh, 0FFh, 0D7h, 83h, 0C6h, 04h, 3Bh, 0F3h, 75h, 0F5h, 8Bh, 44h
    db 24h, 10h, 89h, 38h, 5Fh, 5Eh, 5Bh, 0C3h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 18h
    db 5Eh, 89h, 08h, 5Bh, 0C3h
?d_004b00e0@@YAXXZ ENDP

; ghidra: FUN_008b01d0  retail @ 0x004B01D0 size 75
public ?d_004b01d0@@YAXXZ
?d_004b01d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 8Bh, 00h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 16h
    db 8Bh, 76h, 04h, 57h, 8Bh, 0F9h, 2Bh, 0F2h, 2Bh, 0F8h, 33h, 0F7h, 0F7h, 0C6h, 0FCh, 0FFh
    db 0FFh, 0FFh, 75h, 22h, 3Bh, 0C1h, 74h, 16h, 2Bh, 0D0h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 30h, 3Bh, 34h, 02h, 75h, 0Fh, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0F2h, 5Fh, 0B8h
    db 01h, 00h, 00h, 00h, 5Eh, 0C3h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
?d_004b01d0@@YAXXZ ENDP

; ghidra: FUN_008b02a0  retail @ 0x004B02A0 size 134
public ?d_004b02a0@@YAXXZ
?d_004b02a0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 83h, 89h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 33h, 0C0h, 57h, 89h, 74h
    db 24h, 08h, 89h, 46h, 04h, 8Dh, 7Eh, 08h, 0C7h, 06h, 0CCh, 0D1h, 0Fh, 01h, 89h, 44h
    db 24h, 18h, 89h, 07h, 89h, 46h, 0Ch, 89h, 46h, 10h, 0A1h, 38h, 36h, 2Fh, 01h, 8Bh
    db 0C8h, 51h, 51h, 40h, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 68h, 0C0h, 0D1h, 0Fh, 01h, 0C6h
    db 44h, 24h, 24h, 01h, 0A3h, 38h, 36h, 2Fh, 01h, 0E8h, 0C2h, 88h, 3Dh, 00h, 57h, 0E8h
    db 0ECh, 8Ch, 3Dh, 00h, 57h, 0E8h, 50h, 1Fh, 0B7h, 0FFh, 57h, 0E8h, 07h, 5Dh, 0B7h, 0FFh
    db 8Bh, 4Ch, 24h, 24h, 83h, 0C4h, 14h, 5Fh, 8Bh, 0C6h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Eh, 83h, 0C4h, 14h, 0C3h
?d_004b02a0@@YAXXZ ENDP

; ghidra: FUN_008b0350  retail @ 0x004B0350 size 91
public ?d_004b0350@@YAXXZ
?d_004b0350@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B3h, 89h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 0C7h, 06h
    db 0CCh, 0D1h, 0Fh, 01h, 8Dh, 7Eh, 08h, 57h, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h
    db 0E8h, 0A4h, 0D3h, 0B5h, 0FFh, 83h, 0C4h, 04h, 8Bh, 0CFh, 0C6h, 44h, 24h, 14h, 00h, 0E8h
    db 0ACh, 75h, 3Dh, 00h, 8Bh, 4Ch, 24h, 0Ch, 0C7h, 06h, 58h, 0ADh, 0Eh, 01h, 5Fh, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_004b0350@@YAXXZ ENDP

; ghidra: FUN_008b05a0  retail @ 0x004B05A0 size 30
public ?d_004b05a0@@YAXXZ
?d_004b05a0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 15h, 8Bh, 44h, 24h, 08h, 8Bh, 10h, 89h, 11h
    db 8Bh, 40h, 04h, 85h, 0C0h, 89h, 41h, 04h, 74h, 03h, 0FFh, 40h, 04h, 0C3h
?d_004b05a0@@YAXXZ ENDP

; ghidra: FUN_008b0850  retail @ 0x004B0850 size 355
_TEXT ENDS
_TEXT$d008b0850 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x008B0850 size 355
public ?d_004b0850@@YAXXZ
?d_004b0850@@YAXXZ PROC
    db 083h, 0ECh, 020h, 056h, 057h, 08Bh, 0F9h, 08Bh, 047h, 018h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 029h, 001h, 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h
    db 028h, 085h, 0C0h, 074h, 01Dh, 08Bh, 0C8h
    call ?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ
    db 08Bh, 008h, 089h, 04Ch, 024h, 010h, 08Bh, 050h, 004h, 089h, 054h, 024h, 014h, 08Bh, 040h, 008h
    db 089h, 044h, 024h, 018h, 0EBh, 017h, 08Dh, 04Eh, 038h, 08Bh, 011h, 08Bh, 041h, 004h, 08Bh, 049h
    db 008h, 089h, 054h, 024h, 010h, 089h, 044h, 024h, 014h, 089h, 04Ch, 024h, 018h, 06Ah, 000h, 06Ah
    db 000h, 06Ah, 000h, 068h
    dd g_Va010FD1D0
    db 08Dh, 054h, 024h, 02Ch, 052h, 08Bh, 0C2h, 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 034h, 000h, 000h
    db 000h, 000h, 0C7h, 044h, 024h, 038h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 03Ch, 000h, 000h
    db 000h, 000h
    call ?j_00034e91@@YAXXZ
    db 084h, 0C0h, 074h, 03Fh, 0D9h, 044h, 024h, 01Ch, 0D8h, 066h, 038h, 0D9h, 05Ch, 024h, 01Ch, 0D9h
    db 044h, 024h, 020h, 0D8h, 066h, 03Ch, 0D9h, 05Ch, 024h, 020h, 0D9h, 044h, 024h, 024h, 0D8h, 066h
    db 040h, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 01Ch, 0D8h, 044h, 024h, 010h, 0D9h, 05Ch, 024h
    db 010h, 0D9h, 044h, 024h, 014h, 0D8h, 044h, 024h, 020h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h
    db 024h, 0EBh, 011h, 08Dh, 08Eh, 0ACh, 000h, 000h, 000h
    call ?getMaxHeightAbovePosition@GeometryInfo@@QBEMXZ
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D8h, 044h, 024h, 018h, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Dh, 044h, 024h, 008h, 050h, 08Dh, 044h, 024h, 014h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 011h, 050h
    db 0FFh, 092h, 05Ch, 001h, 000h, 000h, 085h, 0C0h, 074h, 009h, 0BEh, 019h, 0FCh, 0FFh, 0FFh, 08Bh
    db 0CEh, 0EBh, 008h, 08Bh, 04Ch, 024h, 00Ch, 08Bh, 074h, 024h, 008h, 08Bh, 047h, 024h, 02Bh, 0C1h
    db 099h, 053h, 08Bh, 0D8h, 08Bh, 047h, 020h, 033h, 0DAh, 02Bh, 0DAh, 02Bh, 0C6h, 099h, 033h, 0C2h
    db 02Bh, 0C2h, 003h, 0D8h, 083h, 0FBh, 002h, 05Bh, 07Eh, 024h, 089h, 077h, 020h, 089h, 04Fh, 024h
    db 0C6h, 047h, 008h, 001h, 05Fh, 05Eh, 083h, 0C4h, 020h, 0C3h, 08Bh, 017h, 0BEh, 019h, 0FCh, 0FFh
    db 0FFh, 08Bh, 0CFh, 089h, 074h, 024h, 008h, 089h, 074h, 024h, 00Ch, 0FFh, 052h, 010h, 05Fh, 05Eh
    db 083h, 0C4h, 020h, 0C3h
?d_004b0850@@YAXXZ ENDP
_TEXT$d008b0850 ENDS
_TEXT SEGMENT

; ghidra: FUN_008b0ba0  retail @ 0x004B0BA0 size 176
public ?d_004b0ba0@@YAXXZ
?d_004b0ba0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0F1h, 3Bh, 1Eh, 57h
    db 74h, 3Fh, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 75h, 10h, 8Bh, 44h, 24h, 18h, 85h, 0C0h
    db 75h, 2Fh, 8Bh, 45h, 00h, 3Bh, 43h, 10h, 72h, 27h, 6Ah, 18h, 0E8h, 6Fh, 0D9h, 37h
    db 00h, 8Bh, 0F8h, 8Dh, 4Fh, 10h, 55h, 51h, 0E8h, 52h, 36h, 0B8h, 0FFh, 89h, 7Bh, 0Ch
    db 8Bh, 06h, 8Bh, 48h, 0Ch, 83h, 0C4h, 0Ch, 3Bh, 0D9h, 75h, 36h, 89h, 78h, 0Ch, 0EBh
    db 31h, 6Ah, 18h, 0E8h, 48h, 0D9h, 37h, 00h, 8Bh, 0F8h, 8Dh, 57h, 10h, 55h, 52h, 0E8h
    db 2Bh, 36h, 0B8h, 0FFh, 89h, 7Bh, 08h, 8Bh, 06h, 83h, 0C4h, 0Ch, 3Bh, 0D8h, 75h, 0Ah
    db 89h, 78h, 04h, 8Bh, 06h, 89h, 78h, 0Ch, 0EBh, 08h, 3Bh, 58h, 08h, 75h, 03h, 89h
    db 78h, 08h, 33h, 0C0h, 89h, 5Fh, 04h, 89h, 47h, 08h, 89h, 47h, 0Ch, 8Bh, 0Eh, 83h
    db 0C1h, 04h, 51h, 57h, 0E8h, 97h, 0BDh, 37h, 00h, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 40h
    db 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 89h, 38h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 14h, 00h
?d_004b0ba0@@YAXXZ ENDP

; ghidra: FUN_008b0c80  retail @ 0x004B0C80 size 145
public ?d_004b0c80@@YAXXZ
?d_004b0c80@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 92h, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 10h, 0ACh, 37h, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 73h, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 95h, 2Bh, 0B7h, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_004b0c80@@YAXXZ ENDP

; ghidra: FUN_008b0d40  retail @ 0x004B0D40 size 979
_TEXT ENDS
_TEXT$d008b0d40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x008B0D40 size 979
public ?d_004b0d40@@YAXXZ
?d_004b0d40@@YAXXZ PROC
    db 083h, 0ECh, 048h, 056h, 057h, 08Bh, 0F1h, 08Bh, 07Eh, 010h, 02Bh, 07Eh, 00Ch, 0C1h, 0FFh, 002h
    db 085h, 0FFh, 00Fh, 084h, 0B5h, 003h, 000h, 000h
    call ?j_00006e83@@YAXXZ
    db 08Ah, 046h, 008h, 084h, 0C0h, 00Fh, 084h, 0A5h, 003h, 000h, 000h, 0B8h, 001h, 000h, 000h, 000h
    db 03Bh, 0C7h, 01Bh, 0C9h, 03Bh, 0F8h, 089h, 04Ch, 024h, 020h, 0DBh, 044h, 024h, 020h, 0C7h, 044h
    db 024h, 028h, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 02Ch, 00Fh, 086h, 085h, 000h, 000h, 000h
    db 08Bh, 056h, 038h, 0DBh, 046h, 038h, 085h, 0D2h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D9h, 005h
    dd g_Va012B6624
    db 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd g_Va012B6624
    db 0D8h, 035h
    dd g_Va012B6624
    db 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 054h, 024h, 010h, 0D9h, 0FEh, 0D9h, 05Ch, 024h, 008h, 0D9h, 044h, 024h, 010h, 0D9h, 0FFh
    db 0D9h, 05Ch, 024h, 00Ch, 0D9h, 044h, 024h, 010h, 0D9h, 0FBh, 0D9h, 05Ch, 024h, 00Ch, 0D9h, 05Ch
    db 024h, 008h, 0D9h, 044h, 024h, 00Ch, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 02Ch, 0D8h, 04Ch, 024h, 008h, 0DEh, 0E9h, 0D9h, 044h, 024h, 02Ch, 0D8h, 04Ch
    db 024h, 00Ch, 0D9h, 044h, 024h, 008h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DEh, 0C1h, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 05Ch, 024h, 028h, 08Bh, 046h, 00Ch, 03Bh, 046h, 010h
    db 0C7h, 044h, 024h, 034h, 0F0h, 023h, 074h, 049h, 0C7h, 044h, 024h, 030h, 0F0h, 023h, 074h, 049h
    db 0C7h, 044h, 024h, 03Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 038h, 000h, 000h, 000h, 000h
    db 089h, 044h, 024h, 01Ch, 00Fh, 084h, 0AAh, 002h, 000h, 000h, 053h, 055h, 0EBh, 00Ah, 08Bh, 044h
    db 024h, 024h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 028h, 0D8h, 05Eh, 03Ch, 089h, 06Ch, 024h, 018h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h
    db 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0EBh, 003h, 0D9h, 046h, 03Ch, 0DBh, 046h, 028h, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0C9h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    call __ftol2
    db 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 0D8h, 0D8h, 05Eh, 03Ch, 089h, 05Ch, 024h, 048h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h
    db 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0EBh, 003h, 0D9h, 046h, 03Ch, 0DBh, 046h, 02Ch, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0C9h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    call __ftol2
    db 0DDh, 0D8h, 08Bh, 0F8h, 057h, 053h, 08Bh, 0CDh
    call ?j_000482ac@@YAXXZ
    db 0DBh, 046h, 030h, 08Bh, 046h, 030h, 085h, 0C0h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 025h
    dd ?g_bfmeScaleBK@@3MA
    db 0D8h, 04Eh, 03Ch, 0D8h, 005h
    dd ?g_bfmeScaleBK@@3MA
    db 0D9h, 044h, 024h, 030h, 0D8h, 0C9h, 0D9h, 044h, 024h, 034h, 0D8h, 0CAh, 0D9h, 05Ch, 024h, 054h
    db 0DBh, 046h, 020h, 0D8h, 0C1h
    call __ftol2
    db 0DDh, 0D8h, 0DDh, 0D8h, 08Bh, 0D8h, 0DBh, 046h, 024h, 089h, 05Ch, 024h, 010h, 0D8h, 044h, 024h
    db 054h
    call __ftol2
    db 08Dh, 04Ch, 024h, 018h, 051h, 08Dh, 054h, 024h, 02Ch, 08Bh, 0E8h, 052h, 08Dh, 04Eh, 044h, 089h
    db 06Ch, 024h, 01Ch
    call ?j_00046a10@@YAXXZ
    db 08Bh, 044h, 024h, 028h, 03Bh, 046h, 044h, 074h, 07Bh, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 08Bh, 011h, 0FFh, 052h, 02Ch, 0D9h, 000h, 0D9h, 040h, 004h, 08Bh, 044h, 024h, 028h, 0DBh, 044h
    db 024h, 014h, 08Bh, 048h, 014h, 089h, 04Ch, 024h, 02Ch, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 01Ch, 0DDh
    db 0D8h, 0DBh, 044h, 024h, 010h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 014h, 0DDh, 0D8h, 0D9h, 041h, 00Ch
    db 0D9h, 044h, 024h, 014h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 010h, 0D9h, 041h, 010h
    db 0D9h, 044h, 024h, 01Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 028h, 08Bh, 054h, 024h
    db 01Ch, 08Bh, 044h, 024h, 014h, 052h, 050h, 083h, 0C1h, 008h, 051h
    call ?j_0001bc34@@YAXXZ
    db 08Bh, 044h, 024h, 038h, 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 028h, 083h, 0C4h, 00Ch, 089h
    db 048h, 00Ch, 089h, 050h, 010h, 08Bh, 044h, 024h, 048h, 099h, 08Bh, 04Ch, 024h, 018h, 02Bh, 0C2h
    db 0D1h, 0F8h, 0F7h, 0D8h, 003h, 0D8h, 08Bh, 0C7h, 099h, 02Bh, 0C2h, 0D1h, 0F8h, 0F7h, 0D8h, 003h
    db 0E8h, 055h, 053h, 089h, 05Ch, 024h, 018h, 089h, 06Ch, 024h, 01Ch
    call ?j_0001949d@@YAXXZ
    db 0DBh, 044h, 024h, 010h, 0D8h, 054h, 024h, 038h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h, 0D9h
    db 05Ch, 024h, 038h, 0EBh, 002h, 0DDh, 0D8h, 0DBh, 044h, 024h, 014h, 0D8h, 054h, 024h, 03Ch, 0DFh
    db 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h, 0D9h, 05Ch, 024h, 03Ch, 0EBh, 002h, 0DDh, 0D8h, 003h, 05Ch
    db 024h, 048h, 089h, 05Ch, 024h, 010h, 0DBh, 044h, 024h, 010h, 003h, 0EFh, 089h, 06Ch, 024h, 014h
    db 0D8h, 054h, 024h, 040h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 0D9h, 05Ch, 024h, 040h, 0EBh
    db 002h, 0DDh, 0D8h, 0DBh, 044h, 024h, 014h, 0D8h, 054h, 024h, 044h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 075h, 006h, 0D9h, 05Ch, 024h, 044h, 0EBh, 002h, 0DDh, 0D8h, 08Bh, 046h, 040h, 089h, 044h, 024h
    db 020h, 0D9h, 044h, 024h, 020h, 0D9h, 0FEh, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 020h, 0D9h
    db 0FFh, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 020h, 0D9h, 0FBh, 0D9h, 05Ch, 024h, 01Ch, 0D9h
    db 05Ch, 024h, 014h, 0D9h, 044h, 024h, 01Ch, 0D8h, 04Ch, 024h, 030h, 08Bh, 04Eh, 038h, 085h, 0C9h
    db 0D9h, 044h, 024h, 034h, 0D8h, 04Ch, 024h, 014h, 0DEh, 0E9h, 0D9h, 044h, 024h, 034h, 0D8h, 04Ch
    db 024h, 01Ch, 0D9h, 044h, 024h, 014h, 0D8h, 04Ch, 024h, 030h, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 034h
    db 0D9h, 05Ch, 024h, 030h, 0DBh, 046h, 038h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 01Dh
    dd g_Va010FD1A0
    db 08Bh, 04Ch, 024h, 018h, 068h, 000h, 002h, 000h, 000h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 007h
    call ?j_00033523@@YAXXZ
    db 0EBh, 005h
    call ?j_00027b24@@YAXXZ
    db 08Bh, 044h, 024h, 024h, 08Bh, 04Eh, 010h, 083h, 0C0h, 004h, 03Bh, 0C1h, 089h, 044h, 024h, 024h
    db 00Fh, 085h, 05Ch, 0FDh, 0FFh, 0FFh, 05Dh, 05Bh, 08Bh, 056h, 038h, 0DBh, 046h, 038h, 085h, 0D2h
    db 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 01Dh
    dd g_Va012B6624
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 004h, 0C6h, 046h, 008h, 000h, 05Fh, 05Eh, 083h, 0C4h, 048h
    db 0C3h
?d_004b0d40@@YAXXZ ENDP
_TEXT$d008b0d40 ENDS
_TEXT SEGMENT

; ghidra: FUN_008b1670  retail @ 0x004B1670 size 133
public ?d_004b1670@@YAXXZ
?d_004b1670@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 03h, 8Ah, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0D8h
    db 0D1h, 0Fh, 01h, 8Dh, 4Eh, 44h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0E8h, 66h
    db 40h, 0B5h, 0FFh, 8Bh, 4Eh, 0Ch, 85h, 0C9h, 0C6h, 44h, 24h, 10h, 00h, 74h, 27h, 8Bh
    db 46h, 14h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 0Bh, 51h, 0E8h, 0E9h, 07h, 3Dh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 1Dh
    db 0CFh, 37h, 00h, 83h, 0C4h, 08h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 5Bh, 03h, 4Fh, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
?d_004b1670@@YAXXZ ENDP

; ghidra: FUN_008b1720  retail @ 0x004B1720 size 142
public ?d_004b1720@@YAXXZ
?d_004b1720@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0D9h, 8Bh, 43h, 10h, 57h, 8Bh, 7Bh, 0Ch, 3Bh, 0F8h, 74h, 27h, 90h
    db 8Bh, 37h, 85h, 0F6h, 74h, 16h, 6Ah, 01h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 6Bh, 6Bh, 0B9h
    db 0FFh, 6Ah, 0FFh, 6Ah, 0FFh, 8Bh, 0CEh, 0E8h, 51h, 7Dh, 0B6h, 0FFh, 8Bh, 43h, 10h, 83h
    db 0C7h, 04h, 3Bh, 0F8h, 75h, 0DAh, 8Bh, 43h, 10h, 3Bh, 0C0h, 8Bh, 4Bh, 0Ch, 75h, 04h
    db 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F0h, 2Bh, 0F0h, 56h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h
    db 01h, 83h, 0C4h, 0Ch, 03h, 0C6h, 8Dh, 73h, 44h, 89h, 43h, 10h, 8Bh, 46h, 04h, 85h
    db 0C0h, 74h, 27h, 8Bh, 06h, 8Bh, 48h, 04h, 51h, 8Bh, 0CEh, 0E8h, 25h, 63h, 0B8h, 0FFh
    db 8Bh, 06h, 89h, 40h, 08h, 8Bh, 16h, 0C7h, 42h, 04h, 00h, 00h, 00h, 00h, 8Bh, 06h
    db 89h, 40h, 0Ch, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 0C3h
?d_004b1720@@YAXXZ ENDP

; ghidra: FUN_008b18b0  retail @ 0x004B18B0 size 143
public ?d_004b18b0@@YAXXZ
?d_004b18b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 33h, 8Ah, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 0E8h, 5Dh
    db 01h, 4Fh, 00h, 33h, 0DBh, 0C7h, 06h, 0D8h, 0D1h, 0Fh, 01h, 88h, 5Eh, 08h, 89h, 5Eh
    db 0Ch, 89h, 5Eh, 10h, 89h, 5Ch, 24h, 14h, 89h, 5Eh, 14h, 89h, 5Eh, 18h, 89h, 5Eh
    db 1Ch, 89h, 5Eh, 30h, 89h, 5Eh, 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h
    db 6Ah, 18h, 0C6h, 44h, 24h, 18h, 01h, 89h, 5Eh, 44h, 0E8h, 31h, 0CCh, 37h, 00h, 8Bh
    db 4Ch, 24h, 10h, 89h, 46h, 44h, 89h, 5Eh, 48h, 88h, 18h, 8Bh, 46h, 44h, 89h, 58h
    db 04h, 8Bh, 46h, 44h, 89h, 40h, 08h, 8Bh, 46h, 44h, 83h, 0C4h, 04h, 89h, 40h, 0Ch
    db 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_004b18b0@@YAXXZ ENDP

; ghidra: FUN_008b19a0  retail @ 0x004B19A0 size 50
public ?d_004b19a0@@YAXXZ
?d_004b19a0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 33h, 0DBh, 88h, 5Eh, 08h, 0E8h, 6Bh, 25h, 0B8h, 0FFh, 89h, 5Eh
    db 18h, 89h, 5Eh, 1Ch, 89h, 5Eh, 24h, 89h, 5Eh, 20h, 89h, 5Eh, 2Ch, 89h, 5Eh, 28h
    db 89h, 5Eh, 30h, 89h, 5Eh, 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h, 5Eh
    db 5Bh, 0C3h
?d_004b19a0@@YAXXZ ENDP

; ghidra: FUN_008b19e0  retail @ 0x004B19E0 size 342
_TEXT ENDS
_TEXT$d008b19e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x008B19E0 size 342
public ?d_004b19e0@@YAXXZ
?d_004b19e0@@YAXXZ PROC
    db 053h, 055h, 056h, 057h, 08Bh, 07Ch, 024h, 014h, 08Bh, 047h, 004h, 08Bh, 0F1h, 08Bh, 00Fh, 03Bh
    db 0C8h, 089h, 04Ch, 024h, 014h, 00Fh, 084h, 092h, 000h, 000h, 000h, 08Dh, 059h, 004h, 08Bh, 0FFh
    db 08Bh, 029h, 085h, 0EDh, 075h, 01Fh, 08Bh, 047h, 004h, 03Bh, 0D8h, 074h, 012h, 02Bh, 0C3h, 050h
    db 053h, 051h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 08Bh, 04Ch, 024h, 020h, 083h, 0C4h, 00Ch, 083h, 047h, 004h, 0FCh, 0EBh, 05Fh, 08Bh, 0CDh
    call ?j_0003a5b7@@YAXXZ
    db 084h, 0C0h, 075h, 018h, 08Bh, 0CDh
    call ?j_00023dda@@YAXXZ
    db 0A9h, 000h, 000h, 000h, 004h, 074h, 00Ah, 083h, 044h, 024h, 014h, 004h, 083h, 0C3h, 004h, 0EBh
    db 038h, 08Bh, 047h, 004h, 03Bh, 0D8h, 074h, 012h, 02Bh, 0C3h, 050h, 08Bh, 044h, 024h, 018h, 053h
    db 050h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 083h, 0C4h, 00Ch, 08Bh, 04Fh, 004h, 083h, 0C1h, 0FCh, 06Ah, 001h, 089h, 04Fh, 004h, 06Ah, 001h
    db 08Bh, 0CDh
    call ?j_000482ac@@YAXXZ
    db 06Ah, 0FFh, 06Ah, 0FFh, 08Bh, 0CDh
    call ?j_0001949d@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 03Bh, 04Fh, 004h, 00Fh, 085h, 073h, 0FFh, 0FFh, 0FFh, 08Dh, 05Eh, 00Ch
    db 057h, 053h
    call ?j_00013c78@@YAXXZ
    db 083h, 0C4h, 008h, 084h, 0C0h, 00Fh, 085h, 08Dh, 000h, 000h, 000h, 08Bh, 0CEh
    call ?j_00033f19@@YAXXZ
    db 08Bh, 00Fh, 08Bh, 003h, 089h, 00Bh, 089h, 007h, 08Bh, 057h, 004h, 08Bh, 043h, 004h, 089h, 053h
    db 004h, 089h, 047h, 004h, 083h, 0C7h, 008h, 08Dh, 043h, 008h, 057h, 050h
    call ?j_000277a5@@YAXXZ
    db 08Bh, 00Bh, 08Bh, 043h, 004h, 083h, 0C4h, 008h, 03Bh, 0C8h, 074h, 059h, 08Bh, 06Eh, 010h, 08Bh
    db 01Bh, 033h, 0C0h, 03Bh, 0DDh, 0C6h, 046h, 008h, 001h, 089h, 046h, 024h, 089h, 046h, 020h, 089h
    db 046h, 02Ch, 089h, 046h, 028h, 089h, 046h, 030h, 089h, 046h, 034h, 089h, 046h, 038h, 089h, 046h
    db 03Ch, 089h, 046h, 040h, 074h, 02Fh, 08Bh, 03Bh, 06Ah, 004h, 06Ah, 004h, 08Bh, 0CFh
    call ?j_000482ac@@YAXXZ
    db 08Bh, 056h, 024h, 08Bh, 046h, 020h, 052h, 050h, 08Bh, 0CFh
    call ?j_0001949d@@YAXXZ
    db 068h, 000h, 002h, 000h, 000h, 08Bh, 0CFh
    call ?j_00033523@@YAXXZ
    db 083h, 0C3h, 004h, 03Bh, 0DDh, 075h, 0D1h, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 004h, 000h
?d_004b19e0@@YAXXZ ENDP
_TEXT$d008b19e0 ENDS
_TEXT SEGMENT

; ghidra: FUN_008b1b90  retail @ 0x004B1B90 size 183
public ?d_004b1b90@@YAXXZ
?d_004b1b90@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 60h, 8Ah, 02h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 31h, 8Bh, 46h, 04h, 85h
    db 0C0h, 57h, 8Bh, 7Ch, 24h, 28h, 8Bh, 0D6h, 74h, 19h, 8Bh, 1Fh, 8Dh, 64h, 24h, 00h
    db 39h, 58h, 10h, 72h, 07h, 8Bh, 0D0h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch, 85h
    db 0C0h, 75h, 0EDh, 3Bh, 0D6h, 74h, 07h, 8Bh, 07h, 3Bh, 42h, 10h, 73h, 52h, 0C7h, 44h
    db 24h, 0Ch, 00h, 00h, 00h, 00h, 8Bh, 07h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h
    db 89h, 44h, 24h, 10h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 8Dh, 44h, 24h, 10h
    db 50h, 51h, 8Bh, 0C4h, 89h, 10h, 8Dh, 54h, 24h, 30h, 52h, 0C6h, 44h, 24h, 2Ch, 01h
    db 0E8h, 0C8h, 0E1h, 0B7h, 0FFh, 8Bh, 44h, 24h, 28h, 83h, 0C0h, 14h, 8Bh, 4Ch, 24h, 18h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h
    db 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 8Dh, 42h, 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_004b1b90@@YAXXZ ENDP

; ghidra: FUN_008b2260  retail @ 0x004B2260 size 86
public ?d_004b2260@@YAXXZ
?d_004b2260@@YAXXZ PROC
    db 51h, 8Dh, 04h, 24h, 50h, 6Ah, 02h, 0E8h, 62h, 9Ch, 0B5h, 0FFh, 84h, 0C0h, 75h, 07h
    db 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 0D9h, 04h, 24h, 83h, 0ECh, 08h, 0D8h, 05h, 3Ch
    db 53h, 07h, 01h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 83h, 0C4h, 08h, 0E8h
    db 0A4h, 4Bh, 54h, 00h, 8Bh, 8Fh, 70h, 04h, 00h, 00h, 85h, 0C9h, 89h, 0Eh, 7Ch, 04h
    db 03h, 0C8h, 89h, 0Eh, 8Bh, 8Fh, 74h, 04h, 00h, 00h, 85h, 0C9h, 89h, 0Bh, 7Ch, 04h
    db 03h, 0C8h, 89h, 0Bh, 59h, 0C3h
?d_004b2260@@YAXXZ ENDP
_TEXT ENDS
END
