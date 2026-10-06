.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0Render2DClass@@QAE@XZ:NEAR
EXTERN ??1W3DRadarResetSurface@@QAE@XZ:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ??YRectClass@@QAEAAV0@ABV0@@Z:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeRenderHeight@@3HA:BYTE
EXTERN ?BfmeRenderWidth@@3HA:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Get_Description@SurfaceClass@@QAEXAAUSurfaceDescription@1@@Z:NEAR
EXTERN ?Set_Coordinate_Range@Render2DClass@@QAEXABVRectClass@@@Z:NEAR
EXTERN ?Update_Current_Buffer@FontCharsClass@@AAEXH@Z:NEAR
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A:BYTE
EXTERN ?j_0004183a@@YAXXZ:NEAR
EXTERN __imp__GetGlyphIndicesW@20:BYTE
EXTERN __imp__SelectObject@8:BYTE
EXTERN __imp__floor:BYTE
EXTERN __real@4f800000:BYTE
EXTERN g_Va0105D6D1:NEAR
EXTERN g_Va0105D728:NEAR
EXTERN g_Va013590D0:BYTE
EXTERN g_Va013590E8:BYTE
_TEXT SEGMENT

; ghidra: FUN_00d39520  retail @ 0x00939520 size 808
public ?d_00939520@@YAXXZ
?d_00939520@@YAXXZ PROC
    db 81h, 0ECh, 58h, 01h, 00h, 00h, 53h, 8Bh, 9Ch, 24h, 64h, 01h, 00h, 00h, 56h, 8Bh
    db 0B4h, 24h, 64h, 01h, 00h, 00h, 3Bh, 0F3h, 0Fh, 83h, 01h, 03h, 00h, 00h, 55h, 57h
    db 8Dh, 6Ch, 24h, 68h, 8Bh, 0CBh, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h
    db 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 83h, 0F8h, 10h, 89h, 6Ch, 24h, 10h, 0Fh
    db 8Fh, 97h, 00h, 00h, 00h, 8Dh, 56h, 0Ch, 3Bh, 0D3h, 73h, 6Ch, 8Dh, 64h, 24h, 00h
    db 3Bh, 0D6h, 8Bh, 0C2h, 8Bh, 08h, 89h, 4Ch, 24h, 14h, 8Bh, 48h, 04h, 8Bh, 40h, 08h
    db 89h, 4Ch, 24h, 18h, 89h, 44h, 24h, 1Ch, 8Bh, 0CAh, 74h, 31h, 8Dh, 64h, 24h, 00h
    db 0D9h, 41h, 0FCh, 8Dh, 79h, 0F4h, 0D8h, 5Ch, 24h, 1Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 1Ch, 8Bh, 0C7h, 8Bh, 28h, 89h, 29h, 8Bh, 68h, 04h, 8Bh, 40h, 08h, 89h, 69h, 04h
    db 8Bh, 6Ch, 24h, 10h, 89h, 41h, 08h, 8Bh, 0CFh, 3Bh, 0CEh, 75h, 0D3h, 8Bh, 44h, 24h
    db 14h, 89h, 01h, 8Bh, 44h, 24h, 18h, 89h, 41h, 04h, 8Bh, 44h, 24h, 1Ch, 83h, 0C2h
    db 0Ch, 3Bh, 0D3h, 89h, 41h, 08h, 72h, 98h, 8Dh, 4Ch, 24h, 68h, 3Bh, 0E9h, 0Fh, 84h
    db 59h, 02h, 00h, 00h, 8Bh, 75h, 0FCh, 83h, 0EDh, 04h, 8Bh, 5Dh, 0FCh, 83h, 0EDh, 04h
    db 89h, 9Ch, 24h, 70h, 01h, 00h, 00h, 0E9h, 48h, 0FFh, 0FFh, 0FFh, 99h, 2Bh, 0C2h, 0D1h
    db 0F8h, 8Dh, 14h, 40h, 8Dh, 04h, 96h, 8Bh, 0D0h, 8Bh, 0Ah, 8Bh, 6Ah, 04h, 8Bh, 52h
    db 08h, 89h, 54h, 24h, 4Ch, 8Dh, 7Eh, 0Ch, 89h, 6Ch, 24h, 48h, 8Bh, 0D7h, 8Bh, 2Ah
    db 89h, 28h, 8Bh, 6Ah, 04h, 89h, 68h, 04h, 8Bh, 52h, 08h, 89h, 50h, 08h, 8Bh, 54h
    db 24h, 4Ch, 8Bh, 0C7h, 89h, 08h, 8Bh, 4Ch, 24h, 48h, 89h, 48h, 04h, 89h, 50h, 08h
    db 0D9h, 46h, 14h, 0D8h, 5Bh, 0FCh, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 41h, 8Bh, 0CFh, 8Bh
    db 11h, 89h, 54h, 24h, 38h, 8Bh, 51h, 04h, 8Bh, 49h, 08h, 8Dh, 43h, 0F4h, 89h, 54h
    db 24h, 3Ch, 89h, 4Ch, 24h, 40h, 8Bh, 0D0h, 8Bh, 2Ah, 8Bh, 0CFh, 89h, 29h, 8Bh, 6Ah
    db 04h, 89h, 69h, 04h, 8Bh, 52h, 08h, 89h, 51h, 08h, 8Bh, 4Ch, 24h, 38h, 8Bh, 54h
    db 24h, 3Ch, 89h, 08h, 8Bh, 4Ch, 24h, 40h, 89h, 50h, 04h, 89h, 48h, 08h, 0D9h, 46h
    db 08h, 0D8h, 5Bh, 0FCh, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 41h, 8Bh, 0D6h, 8Bh, 0Ah, 89h
    db 4Ch, 24h, 2Ch, 8Bh, 4Ah, 04h, 8Bh, 52h, 08h, 8Dh, 43h, 0F4h, 89h, 4Ch, 24h, 30h
    db 89h, 54h, 24h, 34h, 8Bh, 0C8h, 8Bh, 29h, 8Bh, 0D6h, 89h, 2Ah, 8Bh, 69h, 04h, 89h
    db 6Ah, 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 8Bh, 54h, 24h, 2Ch, 8Bh, 4Ch, 24h, 30h
    db 89h, 10h, 8Bh, 54h, 24h, 34h, 89h, 48h, 04h, 89h, 50h, 08h, 0D9h, 46h, 14h, 0D8h
    db 5Eh, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 38h, 8Bh, 0CFh, 8Bh, 01h, 8Bh, 51h, 04h
    db 8Bh, 49h, 08h, 89h, 54h, 24h, 60h, 89h, 4Ch, 24h, 64h, 8Bh, 0D6h, 8Bh, 2Ah, 8Bh
    db 0CFh, 89h, 29h, 8Bh, 6Ah, 04h, 89h, 69h, 04h, 8Bh, 52h, 08h, 89h, 51h, 08h, 8Bh
    db 54h, 24h, 60h, 8Bh, 0CEh, 89h, 01h, 8Bh, 44h, 24h, 64h, 89h, 51h, 04h, 89h, 41h
    db 08h, 8Dh, 4Bh, 0F4h, 8Bh, 0D7h, 83h, 0C2h, 0Ch, 8Dh, 43h, 0F4h, 3Bh, 0D0h, 73h, 10h
    db 0D9h, 42h, 08h, 0D8h, 5Eh, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 0E9h, 8Dh, 49h, 00h
    db 83h, 0E9h, 0Ch, 3Bh, 0CFh, 76h, 0Dh, 0D9h, 41h, 08h, 0D8h, 5Eh, 08h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 74h, 0ECh, 3Bh, 0CAh, 72h, 49h, 8Bh, 0C2h, 8Bh, 18h, 89h, 5Ch, 24h, 20h
    db 8Bh, 58h, 04h, 8Bh, 40h, 08h, 89h, 44h, 24h, 28h, 89h, 5Ch, 24h, 24h, 8Bh, 0C1h
    db 8Bh, 28h, 8Bh, 0DAh, 89h, 2Bh, 8Bh, 68h, 04h, 89h, 6Bh, 04h, 8Bh, 40h, 08h, 89h
    db 43h, 08h, 8Bh, 5Ch, 24h, 20h, 8Bh, 0C1h, 89h, 18h, 8Bh, 5Ch, 24h, 24h, 89h, 58h
    db 04h, 8Bh, 5Ch, 24h, 28h, 89h, 58h, 08h, 8Bh, 9Ch, 24h, 70h, 01h, 00h, 00h, 0EBh
    db 85h, 8Bh, 0D6h, 8Bh, 02h, 8Bh, 7Ah, 04h, 8Bh, 52h, 08h, 89h, 54h, 24h, 58h, 89h
    db 7Ch, 24h, 54h, 8Bh, 0D1h, 8Bh, 2Ah, 8Bh, 0FEh, 89h, 2Fh, 8Bh, 6Ah, 04h, 89h, 6Fh
    db 04h, 8Bh, 52h, 08h, 89h, 57h, 08h, 8Bh, 0D1h, 89h, 02h, 8Bh, 44h, 24h, 54h, 89h
    db 42h, 04h, 8Bh, 44h, 24h, 58h, 89h, 42h, 08h, 8Bh, 0D3h, 2Bh, 0D1h, 83h, 0EAh, 0Ch
    db 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0EAh, 0D1h, 0FAh, 8Bh, 0FAh, 8Bh, 6Ch, 24h, 10h, 0C1h
    db 0EFh, 1Fh, 03h, 0FAh, 8Bh, 0D1h, 2Bh, 0D6h, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0EAh, 0D1h
    db 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 3Bh, 0C7h, 7Eh, 14h, 89h, 4Dh, 00h, 83h
    db 0C5h, 04h, 89h, 75h, 00h, 83h, 0C5h, 04h, 8Dh, 71h, 0Ch, 0E9h, 24h, 0FDh, 0FFh, 0FFh
    db 89h, 5Dh, 00h, 83h, 0C5h, 04h, 8Dh, 51h, 0Ch, 8Bh, 0D9h, 89h, 55h, 00h, 83h, 0C5h
    db 04h, 89h, 9Ch, 24h, 70h, 01h, 00h, 00h, 0E9h, 07h, 0FDh, 0FFh, 0FFh, 5Fh, 5Dh, 5Eh
    db 5Bh, 81h, 0C4h, 58h, 01h, 00h, 00h, 0C3h
?d_00939520@@YAXXZ ENDP

; ghidra: FUN_00d39f40  retail @ 0x00939F40 size 114
public ?d_00939f40@@YAXXZ
?d_00939f40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 0D4h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 33h, 0FFh, 89h, 74h, 24h, 08h
    db 89h, 3Eh, 89h, 7Eh, 04h, 89h, 7Eh, 08h, 68h, 52h, 06h, 43h, 00h, 68h, 0D6h, 10h
    db 41h, 00h, 6Ah, 08h, 6Ah, 04h, 8Dh, 46h, 14h, 50h, 89h, 7Ch, 24h, 28h, 0C7h, 46h
    db 0Ch, 1Bh, 44h, 10h, 00h, 89h, 7Eh, 10h, 0E8h, 57h, 0CFh, 0Bh, 00h, 8Bh, 4Ch, 24h
    db 0Ch, 89h, 0BEh, 74h, 02h, 00h, 00h, 89h, 0BEh, 6Ch, 02h, 00h, 00h, 89h, 0BEh, 70h
    db 02h, 00h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_00939f40@@YAXXZ ENDP

; ghidra: FUN_00d3b200  retail @ 0x0093B200 size 186
public ?d_0093b200@@YAXXZ
?d_0093b200@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Eh, 0D5h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 57h, 89h, 4Ch, 24h, 08h, 33h, 0DBh
    db 8Dh, 79h, 0Ch, 89h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 0Ch, 8Bh, 4Fh, 04h, 3Bh, 0CBh
    db 0C6h, 44h, 24h, 18h, 01h, 74h, 0Ch, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 01h, 0FFh, 10h
    db 89h, 5Fh, 04h, 55h, 56h, 8Dh, 0B7h, 60h, 02h, 00h, 00h, 0BDh, 02h, 00h, 00h, 00h
    db 8Bh, 0Eh, 3Bh, 0CBh, 74h, 0Bh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 89h
    db 1Eh, 83h, 0C6h, 04h, 4Dh, 75h, 0E9h, 8Bh, 8Fh, 68h, 02h, 00h, 00h, 3Bh, 0CBh, 5Eh
    db 5Dh, 74h, 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 01h, 0FFh, 10h, 89h, 9Fh, 68h, 02h
    db 00h, 00h, 68h, 52h, 06h, 43h, 00h, 6Ah, 08h, 6Ah, 04h, 83h, 0C7h, 08h, 57h, 88h
    db 5Ch, 24h, 28h, 0E8h, 0DEh, 0BAh, 0Bh, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 18h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 87h, 0E1h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_0093b200@@YAXXZ ENDP

; ghidra: FUN_00d3b2c0  retail @ 0x0093B2C0 size 128
public ?d_0093b2c0@@YAXXZ
?d_0093b2c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Bh, 0D5h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 0Dh, 0C0h, 71h, 2Dh, 01h, 85h, 0C9h, 56h, 8Bh
    db 0F1h, 74h, 17h, 0E8h, 48h, 0E1h, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 68h, 88h, 02h, 00h, 00h, 0E8h
    db 2Ch, 6Ch, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h
    db 10h, 00h, 00h, 00h, 00h, 74h, 17h, 8Bh, 0C8h, 0E8h, 22h, 0ECh, 0FFh, 0FFh, 5Eh, 8Bh
    db 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch
    db 24h, 08h, 33h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0093b2c0@@YAXXZ ENDP

; ghidra: FUN_00d3be00  retail @ 0x0093BE00 size 18
public ?d_0093be00@@YAXXZ
?d_0093be00@@YAXXZ PROC
    db 0C7h, 01h, 0B8h, 0CBh, 13h, 01h, 0C7h, 41h, 08h, 0B0h, 0CBh, 13h, 01h, 0E9h, 0FEh, 3Dh
    db 0FEh, 0FFh
?d_0093be00@@YAXXZ ENDP

; ghidra: FUN_00d3c330  retail @ 0x0093C330 size 14
public ?d_0093c330@@YAXXZ
?d_0093c330@@YAXXZ PROC
    db 8Bh, 41h, 04h, 8Bh, 09h, 50h, 51h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 0C3h
?d_0093c330@@YAXXZ ENDP

; ghidra: FUN_00d3c340  retail @ 0x0093C340 size 188
public ?d_0093c340@@YAXXZ
?d_0093c340@@YAXXZ PROC
    db 83h, 0ECh, 28h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 33h, 0FFh, 8Dh, 5Eh, 0Ch, 57h, 89h
    db 3Eh, 89h, 7Eh, 04h, 89h, 7Eh, 08h, 89h, 3Bh, 89h, 7Eh, 10h, 0FFh, 15h, 0F4h, 8Fh
    db 35h, 01h, 8Bh, 0E8h, 55h, 0FFh, 15h, 0B8h, 90h, 35h, 01h, 55h, 57h, 89h, 46h, 10h
    db 0FFh, 15h, 58h, 90h, 35h, 01h, 8Bh, 46h, 10h, 57h, 50h, 0FFh, 15h, 00h, 91h, 35h
    db 01h, 8Bh, 4Eh, 10h, 68h, 0FFh, 0FFh, 0FFh, 00h, 51h, 0FFh, 15h, 10h, 91h, 35h, 01h
    db 8Bh, 46h, 10h, 57h, 57h, 53h, 57h, 8Dh, 54h, 24h, 20h, 52h, 50h, 0C7h, 44h, 24h
    db 28h, 28h, 00h, 00h, 00h, 0C7h, 44h, 24h, 2Ch, 40h, 00h, 00h, 00h, 0C7h, 44h, 24h
    db 30h, 0C0h, 0FFh, 0FFh, 0FFh, 66h, 0C7h, 44h, 24h, 34h, 01h, 00h, 66h, 0C7h, 44h, 24h
    db 36h, 18h, 00h, 89h, 7Ch, 24h, 38h, 89h, 7Ch, 24h, 3Ch, 89h, 7Ch, 24h, 40h, 89h
    db 7Ch, 24h, 44h, 89h, 7Ch, 24h, 48h, 89h, 7Ch, 24h, 4Ch, 0FFh, 15h, 0BCh, 90h, 35h
    db 01h, 8Bh, 4Eh, 10h, 50h, 51h, 89h, 46h, 08h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 5Fh
    db 89h, 46h, 04h, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 28h, 0C3h
?d_0093c340@@YAXXZ ENDP

; ghidra: FUN_00d3c400  retail @ 0x0093C400 size 64
public ?d_0093c400@@YAXXZ
?d_0093c400@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 1Fh, 8Bh, 46h, 04h, 8Bh, 4Eh, 10h
    db 50h, 51h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 8Bh, 56h, 08h, 52h, 0FFh, 15h, 0C8h, 90h
    db 35h, 01h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 0Eh
    db 50h, 0FFh, 15h, 0C4h, 90h, 35h, 01h, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0093c400@@YAXXZ ENDP

; ghidra: FUN_00d3c440  retail @ 0x0093C440 size 84
public ?d_0093c440@@YAXXZ
?d_0093c440@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 1Fh, 8Bh, 46h, 04h, 8Bh, 4Eh, 10h
    db 50h, 51h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 8Bh, 56h, 08h, 52h, 0FFh, 15h, 0C8h, 90h
    db 35h, 01h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 0Eh
    db 50h, 0FFh, 15h, 0C4h, 90h, 35h, 01h, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 0F6h, 44h
    db 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 25h, 5Ah, 0F4h, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h
    db 5Eh, 0C2h, 04h, 00h
?d_0093c440@@YAXXZ ENDP

; ghidra: FUN_00d3c4a0  retail @ 0x0093C4A0 size 171
public ?d_0093c4a0@@YAXXZ
?d_0093c4a0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 0Fh, 84h, 92h, 00h, 00h, 00h
    db 8Bh, 41h, 48h, 8Bh, 0Dh, 0ACh, 0AEh, 34h, 01h, 53h, 8Bh, 59h, 10h, 55h, 57h, 50h
    db 53h, 0C6h, 44h, 24h, 2Ch, 00h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 8Bh, 6Ch, 24h, 20h
    db 8Bh, 15h, 0ACh, 0AEh, 34h, 01h, 8Bh, 7Ch, 24h, 1Ch, 6Ah, 01h, 55h, 56h, 89h, 44h
    db 24h, 20h, 8Bh, 42h, 10h, 57h, 50h, 0FFh, 15h, 0D8h, 90h, 35h, 01h, 33h, 0D2h, 85h
    db 0F6h, 7Eh, 30h, 8Bh, 0CFh, 2Bh, 0EFh, 66h, 81h, 3Ch, 29h, 0FFh, 0FFh, 75h, 15h, 66h
    db 8Bh, 01h, 66h, 3Dh, 0Ah, 00h, 74h, 0Ch, 66h, 3Dh, 0Dh, 00h, 74h, 06h, 66h, 3Dh
    db 95h, 00h, 75h, 0Ah, 42h, 83h, 0C1h, 02h, 3Bh, 0D6h, 7Ch, 0DBh, 0EBh, 05h, 0C6h, 44h
    db 24h, 24h, 01h, 8Bh, 4Ch, 24h, 14h, 51h, 53h, 0FFh, 15h, 0FCh, 90h, 35h, 01h, 8Ah
    db 44h, 24h, 24h, 5Fh, 5Dh, 84h, 0C0h, 5Bh, 0Fh, 94h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C2h
    db 0Ch, 00h, 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_0093c4a0@@YAXXZ ENDP

; ghidra: FUN_00d3c700  retail @ 0x0093C700 size 26
public ?d_0093c700@@YAXXZ
?d_0093c700@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 48h, 85h, 0C0h, 74h, 0Eh, 50h, 0FFh, 15h, 0C8h, 90h, 35h
    db 01h, 0C7h, 46h, 48h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0093c700@@YAXXZ ENDP

; ghidra: FUN_00d3ca90  retail @ 0x0093CA90 size 39
public ?d_0093ca90@@YAXXZ
?d_0093ca90@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 74h, 11h, 38h, 5Eh, 0Dh
    db 74h, 0Ch, 50h, 0E8h, 48h, 54h, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 5Eh, 04h, 88h, 5Eh
    db 0Dh, 89h, 5Eh, 08h, 5Eh, 5Bh, 0C3h
?d_0093ca90@@YAXXZ ENDP

; ghidra: FUN_00d3cea0  retail @ 0x0093CEA0 size 120
public ?d_0093cea0@@YAXXZ
?d_0093cea0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 3Bh, 0F7h, 74h, 65h, 8Bh, 06h, 0FFh, 50h
    db 0Ch, 0C6h, 46h, 0Ch, 00h, 8Bh, 47h, 08h, 85h, 0C0h, 89h, 46h, 08h, 74h, 43h, 8Dh
    db 0Ch, 85h, 00h, 00h, 00h, 00h, 51h, 0E8h, 0A4h, 50h, 0F4h, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 04h, 74h, 3Bh, 8Bh, 4Eh, 08h, 0B0h, 01h, 88h, 46h, 0Dh, 88h, 46h
    db 0Ch, 33h, 0C0h, 85h, 0C9h, 7Eh, 2Ah, 8Bh, 57h, 04h, 8Bh, 4Eh, 04h, 8Bh, 14h, 82h
    db 89h, 14h, 81h, 8Bh, 4Eh, 08h, 40h, 3Bh, 0C1h, 7Ch, 0ECh, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h
    db 04h, 00h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0C6h, 46h, 0Dh, 00h, 0C6h, 46h, 0Ch
    db 01h, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0093cea0@@YAXXZ ENDP

; ghidra: FUN_00d3d0f0  retail @ 0x0093D0F0 size 38
public ?d_0093d0f0@@YAXXZ
?d_0093d0f0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 44h, 33h, 0F6h, 85h, 0C0h, 7Eh, 16h, 8Dh, 49h, 00h
    db 8Bh, 47h, 38h, 8Bh, 0Ch, 0F0h, 0E8h, 15h, 77h, 0FFh, 0FFh, 8Bh, 47h, 44h, 46h, 3Bh
    db 0F0h, 7Ch, 0EDh, 5Fh, 5Eh, 0C3h
?d_0093d0f0@@YAXXZ ENDP

; ghidra: FUN_00d3d120  retail @ 0x0093D120 size 85
public ?d_0093d120@@YAXXZ
?d_0093d120@@YAXXZ PROC
    db 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 14h, 33h, 0EDh, 85h, 0C0h, 7Eh, 43h, 53h, 33h
    db 0DBh, 8Bh, 77h, 08h, 8Bh, 04h, 1Eh, 03h, 0F3h, 85h, 0C0h, 74h, 0Ch, 8Bh, 08h, 50h
    db 0FFh, 51h, 08h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 47h, 14h, 45h, 83h, 0C3h, 24h
    db 3Bh, 0E8h, 7Ch, 0DDh, 85h, 0C0h, 5Bh, 7Eh, 18h, 8Bh, 57h, 04h, 8Dh, 77h, 04h, 8Bh
    db 7Eh, 08h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 8Bh, 06h, 6Ah, 00h, 57h, 8Bh, 0CEh, 0FFh, 50h
    db 08h, 5Fh, 5Eh, 5Dh, 0C3h
?d_0093d120@@YAXXZ ENDP

; ghidra: FUN_00d3d180  retail @ 0x0093D180 size 85
public ?d_0093d180@@YAXXZ
?d_0093d180@@YAXXZ PROC
    db 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 2Ch, 33h, 0EDh, 85h, 0C0h, 7Eh, 43h, 53h, 33h
    db 0DBh, 8Bh, 77h, 20h, 8Bh, 04h, 1Eh, 03h, 0F3h, 85h, 0C0h, 74h, 0Ch, 8Bh, 08h, 50h
    db 0FFh, 51h, 08h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 47h, 2Ch, 45h, 83h, 0C3h, 1Ch
    db 3Bh, 0E8h, 7Ch, 0DDh, 85h, 0C0h, 5Bh, 7Eh, 18h, 8Bh, 57h, 1Ch, 8Dh, 77h, 1Ch, 8Bh
    db 7Eh, 08h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 8Bh, 06h, 6Ah, 00h, 57h, 8Bh, 0CEh, 0FFh, 50h
    db 08h, 5Fh, 5Eh, 5Dh, 0C3h
?d_0093d180@@YAXXZ ENDP

; ghidra: FUN_00d3d200  retail @ 0x0093D200 size 68
public ?d_0093d200@@YAXXZ
?d_0093d200@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D9h, 81h, 0BCh, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Ah, 18h, 0D9h, 44h, 24h, 08h, 0D9h, 81h, 0C0h, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 44h, 7Ah, 05h, 32h, 0C0h, 0C2h, 08h, 00h, 8Bh, 44h, 24h, 04h, 8Bh
    db 54h, 24h, 08h, 89h, 81h, 0BCh, 00h, 00h, 00h, 89h, 91h, 0C0h, 00h, 00h, 00h, 0B0h
    db 01h, 0C2h, 08h, 00h
?d_0093d200@@YAXXZ ENDP

; ghidra: FUN_00d3d250  retail @ 0x0093D250 size 68
public ?d_0093d250@@YAXXZ
?d_0093d250@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D9h, 81h, 0C4h, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Ah, 18h, 0D9h, 44h, 24h, 08h, 0D9h, 81h, 0C8h, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 44h, 7Ah, 05h, 32h, 0C0h, 0C2h, 08h, 00h, 8Bh, 44h, 24h, 04h, 8Bh
    db 54h, 24h, 08h, 89h, 81h, 0C4h, 00h, 00h, 00h, 89h, 91h, 0C8h, 00h, 00h, 00h, 0B0h
    db 01h, 0C2h, 08h, 00h
?d_0093d250@@YAXXZ ENDP

; ghidra: FUN_00d3d2a0  retail @ 0x0093D2A0 size 37
public ?d_0093d2a0@@YAXXZ
?d_0093d2a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 50h, 0E8h, 45h, 4Ch, 0F4h, 0FFh, 8Ah, 44h, 24h, 0Ch, 83h
    db 0C4h, 04h, 0A8h, 01h, 74h, 09h, 56h, 0E8h, 0F4h, 4Bh, 0F4h, 0FFh, 83h, 0C4h, 04h, 8Bh
    db 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0093d2a0@@YAXXZ ENDP

; ghidra: FUN_00d3d2d0  retail @ 0x0093D2D0 size 74
public ?d_0093d2d0@@YAXXZ
?d_0093d2d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 44h, 50h, 51h, 0FFh, 15h, 3Ch, 93h
    db 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 2Bh, 0D9h, 46h, 3Ch, 0D9h, 44h, 24h, 0Ch
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah, 1Bh, 8Bh, 54h, 24h, 14h, 3Bh, 56h, 40h
    db 75h, 12h, 8Ah, 44h, 24h, 10h, 3Ah, 86h, 60h, 04h, 00h, 00h, 75h, 06h, 0B0h, 01h
    db 5Eh, 0C2h, 10h, 00h, 32h, 0C0h, 5Eh, 0C2h, 10h, 00h
?d_0093d2d0@@YAXXZ ENDP

; ghidra: FUN_00d3d560  retail @ 0x0093D560 size 45
public ?d_0093d560@@YAXXZ
?d_0093d560@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 0C7h, 06h, 0C4h, 0CDh, 13h
    db 01h, 74h, 11h, 38h, 5Eh, 0Dh, 74h, 0Ch, 50h, 0E8h, 72h, 49h, 0F4h, 0FFh, 83h, 0C4h
    db 04h, 89h, 5Eh, 04h, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h, 5Eh, 5Bh, 0C3h
?d_0093d560@@YAXXZ ENDP

; ghidra: FUN_00d3d8e0  retail @ 0x0093D8E0 size 61
public ?d_0093d8e0@@YAXXZ
?d_0093d8e0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 74h, 27h, 38h, 5Eh, 0Dh
    db 74h, 22h, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h, 0CFh, 8Fh, 41h, 00h, 51h, 6Ah
    db 24h, 50h, 0E8h, 6Fh, 94h, 0Bh, 00h, 57h, 0E8h, 0E3h, 45h, 0F4h, 0FFh, 83h, 0C4h, 04h
    db 89h, 5Eh, 04h, 5Fh, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h, 5Eh, 5Bh, 0C3h
?d_0093d8e0@@YAXXZ ENDP

; ghidra: FUN_00d3d960  retail @ 0x0093D960 size 72
public ?d_0093d960@@YAXXZ
?d_0093d960@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 0C4h, 0CDh, 13h, 01h, 74h, 17h
    db 8Ah, 4Eh, 0Dh, 84h, 0C9h, 74h, 10h, 50h, 0E8h, 73h, 45h, 0F4h, 0FFh, 83h, 0C4h, 04h
    db 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 0C6h, 46h, 0Dh, 00h
    db 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 74h, 09h, 56h, 0E8h, 11h, 45h, 0F4h, 0FFh, 83h
    db 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0093d960@@YAXXZ ENDP

; ghidra: FUN_00d3d9b0  retail @ 0x0093D9B0 size 91
public ?d_0093d9b0@@YAXXZ
?d_0093d9b0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 85h, 0C0h, 8Bh, 0F1h, 74h, 06h, 8Bh, 08h
    db 50h, 0FFh, 51h, 04h, 8Bh, 06h, 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h
    db 8Bh, 07h, 89h, 06h, 8Bh, 4Fh, 04h, 89h, 4Eh, 04h, 8Bh, 57h, 08h, 89h, 56h, 08h
    db 8Bh, 47h, 0Ch, 89h, 46h, 0Ch, 8Bh, 4Fh, 10h, 89h, 4Eh, 10h, 8Bh, 57h, 14h, 89h
    db 56h, 14h, 8Bh, 47h, 18h, 89h, 46h, 18h, 8Bh, 4Fh, 1Ch, 89h, 4Eh, 1Ch, 8Bh, 57h
    db 20h, 5Fh, 89h, 56h, 20h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0093d9b0@@YAXXZ ENDP

; ghidra: FUN_00d3da80  retail @ 0x0093DA80 size 194
public ?d_0093da80@@YAXXZ
?d_0093da80@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 9Ch, 0D5h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 55h, 56h, 8Bh, 0F1h, 33h, 0DBh, 57h, 8Bh, 7Ch, 24h
    db 20h, 3Bh, 0FBh, 0C7h, 06h, 0Ch, 0CEh, 13h, 01h, 89h, 5Eh, 04h, 89h, 7Eh, 08h, 0C6h
    db 46h, 0Ch, 01h, 88h, 5Eh, 0Dh, 74h, 73h, 8Bh, 44h, 24h, 24h, 3Bh, 0C3h, 74h, 25h
    db 89h, 44h, 24h, 20h, 68h, 0CFh, 8Fh, 41h, 00h, 68h, 0F0h, 0D1h, 0D3h, 00h, 57h, 89h
    db 5Ch, 24h, 24h, 8Dh, 58h, 04h, 6Ah, 24h, 53h, 89h, 38h, 0E8h, 04h, 94h, 0Bh, 00h
    db 89h, 5Eh, 04h, 0EBh, 46h, 8Dh, 04h, 0FFh, 8Dh, 0Ch, 85h, 04h, 00h, 00h, 00h, 51h
    db 0E8h, 7Bh, 44h, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 3Bh, 0C3h, 0C7h, 44h
    db 24h, 18h, 01h, 00h, 00h, 00h, 74h, 1Ah, 68h, 0CFh, 8Fh, 41h, 00h, 68h, 0F0h, 0D1h
    db 0D3h, 00h, 57h, 8Dh, 68h, 04h, 6Ah, 24h, 55h, 89h, 38h, 0E8h, 0C4h, 93h, 0Bh, 00h
    db 0EBh, 02h, 33h, 0EDh, 89h, 6Eh, 04h, 0C6h, 46h, 0Dh, 01h, 8Bh, 4Ch, 24h, 10h, 5Fh
    db 8Bh, 0C6h, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h
?d_0093da80@@YAXXZ ENDP

; ghidra: FUN_00d3df80  retail @ 0x0093DF80 size 45
public ?d_0093df80@@YAXXZ
?d_0093df80@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 0C7h, 06h, 0C4h, 0CDh, 13h
    db 01h, 74h, 11h, 38h, 5Eh, 0Dh, 74h, 0Ch, 50h, 0E8h, 52h, 3Fh, 0F4h, 0FFh, 83h, 0C4h
    db 04h, 89h, 5Eh, 04h, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h, 5Eh, 5Bh, 0C3h
?d_0093df80@@YAXXZ ENDP

; ghidra: FUN_00d3dfb0  retail @ 0x0093DFB0 size 187
public ?d_0093dfb0@@YAXXZ
?d_0093dfb0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 1Bh, 0D6h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 20h, 8Bh, 77h, 2Ch
    db 85h, 0C0h, 0Fh, 94h, 0C1h, 0Fh, 0AFh, 74h, 24h, 1Ch, 84h, 0C9h, 75h, 13h, 8Bh, 4Fh
    db 14h, 8Bh, 44h, 81h, 0FCh, 8Bh, 57h, 28h, 8Bh, 48h, 04h, 03h, 0D6h, 3Bh, 0D1h, 7Eh
    db 66h, 81h, 0FEh, 00h, 80h, 00h, 00h, 7Dh, 05h, 0BEh, 00h, 80h, 00h, 00h, 6Ah, 0Ch
    db 0E8h, 2Bh, 3Fh, 0F4h, 0FFh, 8Bh, 0E8h, 83h, 0C4h, 04h, 89h, 6Ch, 24h, 1Ch, 85h, 0EDh
    db 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h, 1Bh, 8Dh, 04h, 36h, 50h, 89h, 75h
    db 04h, 0C7h, 45h, 08h, 00h, 00h, 00h, 00h, 0E8h, 43h, 3Fh, 0F4h, 0FFh, 83h, 0C4h, 04h
    db 89h, 45h, 00h, 0EBh, 02h, 33h, 0EDh, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Dh, 4Fh, 10h, 0C7h
    db 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 6Ch, 24h, 20h, 0E8h, 0A0h, 0F6h, 0FFh, 0FFh
    db 0C7h, 47h, 28h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Dh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_0093dfb0@@YAXXZ ENDP

; ghidra: FUN_00d3e070  retail @ 0x0093E070 size 82
public ?d_0093e070@@YAXXZ
?d_0093e070@@YAXXZ PROC
    db 0D9h, 44h, 24h, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 83h, 0ECh, 08h, 0DDh, 1Ch, 24h
    db 8Bh, 0F1h, 57h, 8Dh, 46h, 0Ch, 68h, 3Ch, 0CEh, 13h, 01h, 50h, 0E8h, 0FFh, 0DAh, 09h
    db 00h, 83h, 0C4h, 14h, 57h, 8Dh, 4Eh, 44h, 0E8h, 46h, 22h, 6Eh, 0FFh, 8Bh, 4Ch, 24h
    db 10h, 8Ah, 54h, 24h, 14h, 8Bh, 44h, 24h, 18h, 89h, 4Eh, 3Ch, 57h, 8Bh, 0CEh, 88h
    db 96h, 60h, 04h, 00h, 00h, 89h, 46h, 40h, 0E8h, 0B3h, 0E4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h
    db 10h, 00h
?d_0093e070@@YAXXZ ENDP

; ghidra: FUN_00d3e1a0  retail @ 0x0093E1A0 size 67
public ?d_0093e1a0@@YAXXZ
?d_0093e1a0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 0C7h, 06h, 0Ch, 0CEh, 13h
    db 01h, 74h, 27h, 38h, 5Eh, 0Dh, 74h, 22h, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h
    db 0CFh, 8Fh, 41h, 00h, 51h, 6Ah, 24h, 50h, 0E8h, 0A9h, 8Bh, 0Bh, 00h, 57h, 0E8h, 1Dh
    db 3Dh, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 5Eh, 04h, 5Fh, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h
    db 5Eh, 5Bh, 0C3h
?d_0093e1a0@@YAXXZ ENDP

; ghidra: FUN_00d3e1f0  retail @ 0x0093E1F0 size 327
public ?d_0093e1f0@@YAXXZ
?d_0093e1f0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 4Ch, 0D6h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 55h, 8Bh, 6Ch, 24h, 18h, 85h, 0EDh, 56h, 57h, 8Bh
    db 0F1h, 0Fh, 84h, 02h, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 24h, 85h, 0FFh, 0C6h, 46h, 0Ch
    db 00h, 75h, 2Bh, 8Dh, 44h, 0EDh, 00h, 8Dh, 0Ch, 85h, 04h, 00h, 00h, 00h, 51h, 0E8h
    db 3Ch, 3Dh, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 89h, 7Ch, 24h
    db 18h, 74h, 07h, 89h, 28h, 8Dh, 78h, 04h, 0EBh, 15h, 33h, 0FFh, 0EBh, 24h, 89h, 7Ch
    db 24h, 20h, 89h, 2Fh, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 83h, 0C7h, 04h, 68h
    db 0CFh, 8Fh, 41h, 00h, 68h, 0F0h, 0D1h, 0D3h, 00h, 55h, 6Ah, 24h, 57h, 0E8h, 72h, 8Ch
    db 0Bh, 00h, 8Bh, 0DFh, 85h, 0DBh, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0C6h, 46h
    db 0Ch, 01h, 75h, 17h, 32h, 0C0h, 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 46h, 04h, 85h, 0C0h
    db 74h, 61h, 8Bh, 46h, 08h, 3Bh, 0E8h, 7Dh, 02h, 8Bh, 0C5h, 85h, 0C0h, 7Eh, 22h, 33h
    db 0FFh, 89h, 44h, 24h, 20h, 8Bh, 56h, 04h, 03h, 0D7h, 52h, 8Dh, 0Ch, 1Fh, 0E8h, 0EDh
    db 0F6h, 0FFh, 0FFh, 8Bh, 44h, 24h, 20h, 83h, 0C7h, 24h, 48h, 89h, 44h, 24h, 20h, 75h
    db 0E4h, 8Ah, 46h, 0Dh, 84h, 0C0h, 74h, 2Bh, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 1Dh, 8Bh
    db 48h, 0FCh, 8Dh, 78h, 0FCh, 68h, 0CFh, 8Fh, 41h, 00h, 51h, 6Ah, 24h, 50h, 0E8h, 83h
    db 8Ah, 0Bh, 00h, 57h, 0E8h, 0F7h, 3Bh, 0F4h, 0FFh, 83h, 0C4h, 04h, 0C7h, 46h, 04h, 00h
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 24h, 33h, 0C0h, 85h, 0C9h, 0Fh, 94h, 0C0h, 89h, 5Eh
    db 04h, 89h, 6Eh, 08h, 88h, 46h, 0Dh, 0EBh, 07h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 0Ch
    db 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_0093e1f0@@YAXXZ ENDP

; ghidra: FUN_00d3e3b0  retail @ 0x0093E3B0 size 64
public ?d_0093e3b0@@YAXXZ
?d_0093e3b0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 89h, 5Eh, 10h, 74h, 27h
    db 38h, 5Eh, 0Dh, 74h, 22h, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h, 0CFh, 8Fh, 41h
    db 00h, 51h, 6Ah, 24h, 50h, 0E8h, 9Ch, 89h, 0Bh, 00h, 57h, 0E8h, 10h, 3Bh, 0F4h, 0FFh
    db 83h, 0C4h, 04h, 89h, 5Eh, 04h, 5Fh, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h, 5Eh, 5Bh, 0C3h
?d_0093e3b0@@YAXXZ ENDP

; ghidra: FUN_00d3e420  retail @ 0x0093E420 size 85
public ?d_0093e420@@YAXXZ
?d_0093e420@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 39h, 4Eh, 10h, 7Ch, 28h, 8Ah, 46h, 0Dh, 84h, 0C0h
    db 75h, 04h, 85h, 0C9h, 75h, 17h, 8Bh, 46h, 14h, 85h, 0C0h, 7Eh, 10h, 8Bh, 16h, 03h
    db 0C1h, 6Ah, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h, 75h, 06h, 32h, 0C0h, 5Eh
    db 0C2h, 04h, 00h, 8Bh, 46h, 10h, 8Bh, 54h, 24h, 08h, 8Dh, 48h, 01h, 89h, 4Eh, 10h
    db 8Bh, 4Eh, 04h, 8Dh, 04h, 0C0h, 52h, 8Dh, 0Ch, 81h, 0E8h, 41h, 0F5h, 0FFh, 0FFh, 0B0h
    db 01h, 5Eh, 0C2h, 04h, 00h
?d_0093e420@@YAXXZ ENDP

; ghidra: FUN_00d3e4d0  retail @ 0x0093E4D0 size 392
public ?d_0093e4d0@@YAXXZ
?d_0093e4d0@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 7Ch, 0D6h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 1Ch, 55h, 56h, 33h
    db 0F6h, 3Bh, 0DEh, 57h, 8Bh, 0E9h, 0Fh, 84h, 3Dh, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 2Ch
    db 3Bh, 0FEh, 0C6h, 45h, 0Ch, 00h, 75h, 23h, 8Dh, 04h, 0DDh, 04h, 00h, 00h, 00h, 50h
    db 0E8h, 5Bh, 3Ah, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 28h, 3Bh, 0C6h, 89h, 74h
    db 24h, 20h, 74h, 2Bh, 89h, 18h, 8Dh, 70h, 04h, 0EBh, 11h, 89h, 7Ch, 24h, 28h, 0C7h
    db 44h, 24h, 20h, 01h, 00h, 00h, 00h, 89h, 1Fh, 8Dh, 77h, 04h, 68h, 0F5h, 70h, 44h
    db 00h, 68h, 0E0h, 0D1h, 0D3h, 00h, 53h, 6Ah, 08h, 56h, 0E8h, 95h, 89h, 0Bh, 00h, 8Bh
    db 0CEh, 85h, 0C9h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 74h, 24h, 28h, 0C6h
    db 45h, 0Ch, 01h, 75h, 17h, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h, 8Bh, 45h, 04h, 85h
    db 0C0h, 0Fh, 84h, 0A0h, 00h, 00h, 00h, 8Bh, 45h, 08h, 3Bh, 0D8h, 7Dh, 02h, 8Bh, 0C3h
    db 85h, 0C0h, 7Eh, 5Dh, 0BEh, 0FCh, 0FFh, 0FFh, 0FFh, 2Bh, 0F1h, 8Dh, 79h, 04h, 89h, 74h
    db 24h, 14h, 89h, 44h, 24h, 10h, 0EBh, 08h, 8Bh, 74h, 24h, 14h, 8Dh, 64h, 24h, 00h
    db 8Bh, 55h, 04h, 03h, 0F7h, 8Bh, 0Ch, 16h, 03h, 0F2h, 89h, 4Fh, 0FCh, 8Bh, 46h, 04h
    db 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 04h, 8Bh, 07h, 85h, 0C0h, 74h, 06h
    db 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 56h, 04h, 8Bh, 44h, 24h, 10h, 89h, 17h, 83h
    db 0C7h, 08h, 48h, 89h, 44h, 24h, 10h, 75h, 0BFh, 8Bh, 7Ch, 24h, 2Ch, 8Bh, 4Ch, 24h
    db 28h, 8Ah, 45h, 0Dh, 84h, 0C0h, 74h, 2Fh, 8Bh, 45h, 04h, 85h, 0C0h, 74h, 1Dh, 8Bh
    db 48h, 0FCh, 8Dh, 70h, 0FCh, 68h, 0F5h, 70h, 44h, 00h, 51h, 6Ah, 08h, 50h, 0E8h, 63h
    db 87h, 0Bh, 00h, 56h, 0E8h, 0D7h, 38h, 0F4h, 0FFh, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 28h
    db 0C7h, 45h, 04h, 00h, 00h, 00h, 00h, 33h, 0C0h, 85h, 0FFh, 0Fh, 94h, 0C0h, 89h, 4Dh
    db 04h, 89h, 5Dh, 08h, 88h, 45h, 0Dh, 0EBh, 08h, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 52h
    db 0Ch, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h
?d_0093e4d0@@YAXXZ ENDP

; ghidra: FUN_00d3e730  retail @ 0x0093E730 size 114
public ?d_0093e730@@YAXXZ
?d_0093e730@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 39h, 4Eh, 10h, 7Ch, 28h, 8Ah, 46h, 0Dh, 84h, 0C0h
    db 75h, 04h, 85h, 0C9h, 75h, 17h, 8Bh, 46h, 14h, 85h, 0C0h, 7Eh, 10h, 8Bh, 16h, 03h
    db 0C1h, 6Ah, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h, 75h, 06h, 32h, 0C0h, 5Eh
    db 0C2h, 04h, 00h, 8Bh, 46h, 10h, 8Bh, 56h, 04h, 8Dh, 48h, 01h, 89h, 4Eh, 10h, 57h
    db 8Bh, 7Ch, 24h, 0Ch, 8Dh, 34h, 0C2h, 8Bh, 07h, 89h, 06h, 8Bh, 47h, 04h, 85h, 0C0h
    db 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 04h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 06h, 8Bh
    db 10h, 50h, 0FFh, 52h, 08h, 8Bh, 47h, 04h, 89h, 46h, 04h, 5Fh, 0B0h, 01h, 5Eh, 0C2h
    db 04h, 00h
?d_0093e730@@YAXXZ ENDP

; ghidra: FUN_00d3e880  retail @ 0x0093E880 size 94
public ?d_0093e880@@YAXXZ
?d_0093e880@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 0Ch, 0CEh, 13h, 01h, 74h, 2Dh
    db 8Ah, 4Eh, 0Dh, 84h, 0C9h, 74h, 26h, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h, 0CFh
    db 8Fh, 41h, 00h, 51h, 6Ah, 24h, 50h, 0E8h, 0CAh, 84h, 0Bh, 00h, 57h, 0E8h, 3Eh, 36h
    db 0F4h, 0FFh, 83h, 0C4h, 04h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Fh, 0F6h, 44h, 24h
    db 08h, 01h, 0C6h, 46h, 0Dh, 00h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 74h, 09h, 56h
    db 0E8h, 0DBh, 35h, 0F4h, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0093e880@@YAXXZ ENDP

; ghidra: FUN_00d3e8e0  retail @ 0x0093E8E0 size 71
public ?d_0093e8e0@@YAXXZ
?d_0093e8e0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 85h, 0C0h, 8Bh, 0F1h, 74h, 06h, 8Bh
    db 08h, 50h, 0FFh, 51h, 04h, 8Bh, 06h, 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h
    db 08h, 8Bh, 07h, 83h, 0C7h, 04h, 8Dh, 5Eh, 04h, 57h, 8Bh, 0CBh, 89h, 06h, 0E8h, 8Dh
    db 0E5h, 0FFh, 0FFh, 8Bh, 4Fh, 10h, 89h, 4Bh, 10h, 8Bh, 57h, 14h, 5Fh, 8Bh, 0C6h, 5Eh
    db 89h, 53h, 14h, 5Bh, 0C2h, 04h, 00h
?d_0093e8e0@@YAXXZ ENDP

; ghidra: FUN_00d3e9c0  retail @ 0x0093E9C0 size 67
public ?d_0093e9c0@@YAXXZ
?d_0093e9c0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 33h, 0DBh, 3Bh, 0C3h, 0C7h, 06h, 0Ch, 0CEh, 13h
    db 01h, 74h, 27h, 38h, 5Eh, 0Dh, 74h, 22h, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h
    db 0CFh, 8Fh, 41h, 00h, 51h, 6Ah, 24h, 50h, 0E8h, 89h, 83h, 0Bh, 00h, 57h, 0E8h, 0FDh
    db 34h, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 5Eh, 04h, 5Fh, 88h, 5Eh, 0Dh, 89h, 5Eh, 08h
    db 5Eh, 5Bh, 0C3h
?d_0093e9c0@@YAXXZ ENDP

; ghidra: FUN_00d3ea60  retail @ 0x0093EA60 size 189
public ?d_0093ea60@@YAXXZ
?d_0093ea60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0D6h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 0E8h, 11h, 46h, 0FCh, 0FFh, 8Bh
    db 86h, 0B0h, 00h, 00h, 00h, 33h, 0DBh, 3Bh, 0C3h, 89h, 5Ch, 24h, 14h, 74h, 0Eh, 8Dh
    db 4Eh, 7Ch, 0E8h, 39h, 0DDh, 0FBh, 0FFh, 89h, 9Eh, 0B0h, 00h, 00h, 00h, 8Bh, 46h, 7Ch
    db 3Bh, 0C3h, 74h, 09h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 89h, 5Eh, 7Ch, 39h, 5Eh, 44h
    db 7Eh, 2Dh, 55h, 57h, 8Dh, 6Eh, 34h, 8Bh, 56h, 38h, 8Bh, 3Ah, 3Bh, 0FBh, 74h, 10h
    db 8Bh, 0CFh, 0E8h, 0C9h, 83h, 0FFh, 0FFh, 57h, 0E8h, 0E3h, 33h, 0F4h, 0FFh, 83h, 0C4h, 04h
    db 53h, 8Bh, 0CDh, 0E8h, 0D8h, 0FCh, 0FFh, 0FFh, 39h, 5Eh, 44h, 7Fh, 0DAh, 5Fh, 5Dh, 89h
    db 5Eh, 60h, 89h, 5Eh, 64h, 8Bh, 0CEh, 88h, 9Eh, 80h, 00h, 00h, 00h, 88h, 9Eh, 0ADh
    db 00h, 00h, 00h, 0E8h, 88h, 0E6h, 0FFh, 0FFh, 8Bh, 0CEh, 0E8h, 21h, 0E6h, 0FFh, 0FFh, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 04h, 70h, 0FCh, 0FFh, 8Bh, 4Ch, 24h, 0Ch
    db 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0093ea60@@YAXXZ ENDP

; ghidra: FUN_00d3eb50  retail @ 0x0093EB50 size 1983
_TEXT ENDS
_TEXT$d00d3eb50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00D3EB50 size 1983
public ?d_0093eb50@@YAXXZ
?d_0093eb50@@YAXXZ PROC
    db 055h, 08Bh, 0ECh, 083h, 0E4h, 0F8h, 06Ah, 0FFh, 068h
    dd g_Va0105D6D1
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 098h, 000h, 000h, 000h, 053h, 056h, 033h, 0F6h, 057h, 08Bh, 0F9h, 089h, 074h, 024h, 050h, 089h
    db 074h, 024h, 024h, 08Bh, 087h, 0BCh, 000h, 000h, 000h, 08Bh, 08Fh, 0C0h, 000h, 000h, 000h, 089h
    db 0B7h, 09Ch, 000h, 000h, 000h, 089h, 0B7h, 0A0h, 000h, 000h, 000h, 089h, 0B7h, 0A4h, 000h, 000h
    db 000h, 089h, 0B7h, 0A8h, 000h, 000h, 000h, 0D9h, 087h, 0C4h, 000h, 000h, 000h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 089h, 044h, 024h, 044h, 089h, 0B4h, 024h, 0ACh, 000h, 000h, 000h, 089h, 04Ch, 024h, 048h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 00Fh, 085h, 0F6h, 000h, 000h, 000h, 0D9h, 087h, 0C8h, 000h, 000h, 000h
    db 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 085h, 0DFh, 000h, 000h, 000h, 08Bh, 047h, 014h, 033h, 0DBh
    db 03Bh, 0C6h, 07Eh, 068h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 0D9h, 087h, 0A4h, 000h, 000h, 000h
    db 08Bh, 04Fh, 008h, 0D8h, 0A7h, 09Ch, 000h, 000h, 000h, 003h, 0CEh, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 026h, 08Bh, 051h, 004h, 089h, 097h, 09Ch, 000h
    db 000h, 000h, 08Bh, 041h, 008h, 089h, 087h, 0A0h, 000h, 000h, 000h, 08Bh, 051h, 00Ch, 089h, 097h
    db 0A4h, 000h, 000h, 000h, 08Bh, 041h, 010h, 089h, 087h, 0A8h, 000h, 000h, 000h, 0EBh, 00Fh, 083h
    db 0C1h, 004h, 051h, 08Dh, 08Fh, 09Ch, 000h, 000h, 000h
    call ??YRectClass@@QAEAAV0@ABV0@@Z
    db 08Bh, 047h, 014h, 043h, 083h, 0C6h, 024h, 03Bh, 0D8h, 07Ch, 0A0h, 033h, 0F6h, 0D9h, 087h, 0A4h
    db 000h, 000h, 000h, 0D8h, 0A7h, 09Ch, 000h, 000h, 000h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 0C1h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Ch, 0D9h, 087h, 0C4h, 000h, 000h
    db 000h, 0D8h, 0F1h, 0D9h, 05Ch, 024h, 044h, 0DDh, 0D8h, 0D9h, 087h, 0A8h, 000h, 000h, 000h, 0D8h
    db 0A7h, 0A0h, 000h, 000h, 000h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 0C1h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Ch, 0D9h, 087h, 0C8h, 000h, 000h
    db 000h, 0D8h, 0F1h, 0D9h, 05Ch, 024h, 048h, 0DDh, 0D8h, 089h, 0B7h, 09Ch, 000h, 000h, 000h, 089h
    db 0B7h, 0A0h, 000h, 000h, 000h, 089h, 0B7h, 0A4h, 000h, 000h, 000h, 089h, 0B7h, 0A8h, 000h, 000h
    db 000h, 039h, 077h, 014h, 089h, 074h, 024h, 054h, 00Fh, 08Eh, 017h, 006h, 000h, 000h, 089h, 074h
    db 024h, 04Ch, 08Bh, 077h, 008h, 08Bh, 05Ch, 024h, 04Ch, 08Bh, 04Ch, 024h, 024h, 08Bh, 004h, 01Eh
    db 003h, 0F3h, 03Bh, 0C1h, 089h, 074h, 024h, 010h, 00Fh, 084h, 0FBh, 001h, 000h, 000h, 085h, 0C0h
    db 074h, 00Ah, 08Bh, 008h, 050h, 0FFh, 051h, 004h, 08Bh, 04Ch, 024h, 024h, 085h, 0C9h, 074h, 006h
    db 08Bh, 011h, 051h, 0FFh, 052h, 008h, 08Bh, 04Fh, 044h, 08Bh, 036h, 033h, 0C0h, 085h, 0C9h, 089h
    db 074h, 024h, 024h, 07Eh, 018h, 08Bh, 05Fh, 038h, 08Dh, 053h, 004h, 08Dh, 09Bh, 000h, 000h, 000h
    db 000h, 039h, 032h, 074h, 02Fh, 040h, 083h, 0C2h, 008h, 03Bh, 0C1h, 07Ch, 0F4h, 06Ah, 058h
    call ??2@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 028h, 033h, 0DBh, 03Bh, 0C3h, 0C6h, 084h, 024h, 0ACh, 000h
    db 000h, 000h, 001h, 074h, 017h, 08Bh, 0C8h
    call ??0Render2DClass@@QAE@XZ
    db 08Bh, 0F0h, 0EBh, 00Eh, 08Bh, 004h, 0C3h, 089h, 044h, 024h, 050h, 0E9h, 085h, 001h, 000h, 000h
    db 033h, 0F6h, 08Bh, 00Dh
    dd ?BfmeRenderHeight@@3HA
    db 0DBh, 005h
    dd ?BfmeRenderHeight@@3HA
    db 085h, 0C9h, 089h, 074h, 024h, 058h, 0C6h, 084h, 024h, 0ACh, 000h, 000h, 000h, 000h, 089h, 074h
    db 024h, 050h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 08Bh, 015h
    dd ?BfmeRenderWidth@@3HA
    db 0DBh, 005h
    dd ?BfmeRenderWidth@@3HA
    db 085h, 0D2h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D9h, 05Ch, 024h, 074h, 08Dh, 044h, 024h, 06Ch, 050h, 08Bh, 0CEh, 0D9h, 05Ch, 024h, 07Ch, 0C7h
    db 044h, 024h, 070h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 074h, 000h, 000h, 000h, 000h
    call ?Set_Coordinate_Range@Render2DClass@@QAEXABVRectClass@@@Z
    db 089h, 05Ch, 024h, 040h, 08Bh, 044h, 024h, 024h, 03Bh, 0C3h, 0C6h, 084h, 024h, 0ACh, 000h, 000h
    db 000h, 002h, 089h, 074h, 024h, 03Ch, 074h, 014h, 08Bh, 008h, 050h, 0FFh, 051h, 004h, 08Bh, 044h
    db 024h, 040h, 03Bh, 0C3h, 074h, 006h, 08Bh, 010h, 050h, 0FFh, 052h, 008h, 08Bh, 044h, 024h, 024h
    db 08Bh, 04Fh, 044h, 08Dh, 077h, 034h, 089h, 044h, 024h, 040h, 08Bh, 046h, 008h, 03Bh, 0C8h, 07Ch
    db 021h, 08Ah, 04Eh, 00Dh, 084h, 0C9h, 075h, 004h, 03Bh, 0C3h, 075h, 051h, 08Bh, 04Eh, 014h, 03Bh
    db 0CBh, 07Eh, 04Ah, 08Bh, 016h, 003h, 0C8h, 053h, 051h, 08Bh, 0CEh, 0FFh, 052h, 008h, 084h, 0C0h
    db 074h, 03Bh, 08Bh, 046h, 010h, 08Bh, 056h, 004h, 08Dh, 048h, 001h, 089h, 04Eh, 010h, 08Dh, 034h
    db 0C2h, 08Bh, 044h, 024h, 03Ch, 089h, 006h, 08Bh, 04Ch, 024h, 040h, 03Bh, 0CBh, 074h, 00Ah, 08Bh
    db 011h, 051h, 0FFh, 052h, 004h, 08Bh, 04Ch, 024h, 040h, 08Bh, 046h, 004h, 03Bh, 0C3h, 074h, 00Ah
    db 08Bh, 008h, 050h, 0FFh, 051h, 008h, 08Bh, 04Ch, 024h, 040h, 089h, 04Eh, 004h, 039h, 05Fh, 02Ch
    db 089h, 05Ch, 024h, 028h, 07Eh, 06Ch, 033h, 0DBh, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh
    db 047h, 020h, 08Bh, 054h, 024h, 024h, 08Bh, 00Ch, 018h, 003h, 0C3h, 03Bh, 0CAh, 075h, 040h, 08Bh
    db 048h, 00Ch, 08Dh, 070h, 004h, 039h, 04Eh, 010h, 07Ch, 022h, 08Ah, 046h, 00Dh, 084h, 0C0h, 075h
    db 004h, 085h, 0C9h, 075h, 02Ah, 08Bh, 046h, 014h, 085h, 0C0h, 07Eh, 023h, 08Bh, 016h, 003h, 0C1h
    db 06Ah, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 008h, 084h, 0C0h, 074h, 013h, 08Bh, 046h, 010h, 08Bh
    db 056h, 004h, 08Dh, 048h, 001h, 089h, 04Eh, 010h, 08Bh, 04Ch, 024h, 058h, 089h, 00Ch, 082h, 08Bh
    db 044h, 024h, 028h, 08Bh, 04Fh, 02Ch, 040h, 083h, 0C3h, 01Ch, 03Bh, 0C1h, 089h, 044h, 024h, 028h
    db 07Ch, 09Dh, 08Dh, 04Ch, 024h, 040h, 0C6h, 084h, 024h, 0ACh, 000h, 000h, 000h, 000h
    call ??1W3DRadarResetSurface@@QAE@XZ
    db 08Bh, 074h, 024h, 010h, 0D9h, 046h, 004h, 08Bh, 056h, 014h, 0D9h, 046h, 008h, 08Bh, 046h, 018h
    db 0D9h, 046h, 00Ch, 08Bh, 04Eh, 01Ch, 0D9h, 046h, 010h, 089h, 054h, 024h, 02Ch, 0D8h, 0E2h, 08Bh
    db 056h, 020h, 083h, 0ECh, 008h, 089h, 044h, 024h, 038h, 0D9h, 05Ch, 024h, 018h, 089h, 04Ch, 024h
    db 03Ch, 089h, 054h, 024h, 040h, 0D8h, 0E2h, 0D9h, 09Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 0C9h
    db 0D8h, 04Ch, 024h, 04Ch, 0D9h, 05Ch, 024h, 01Ch, 0D8h, 04Ch, 024h, 050h, 0D9h, 084h, 024h, 090h
    db 000h, 000h, 000h, 0D8h, 04Ch, 024h, 04Ch, 0D8h, 044h, 024h, 01Ch, 0D9h, 044h, 024h, 018h, 0D8h
    db 04Ch, 024h, 050h, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 028h, 0D9h, 044h, 024h, 01Ch, 0D8h, 047h, 058h
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 0C9h, 0D8h, 047h, 05Ch, 0D9h, 05Ch, 024h, 020h, 0D8h, 047h, 058h
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 028h, 0D8h, 047h, 05Ch, 0D9h, 05Ch, 024h, 028h, 0D9h
    db 044h, 024h, 01Ch, 0D8h, 005h
    dd ?g_bfmeADL@@3MA
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 020h, 0D8h, 005h
    dd ?g_bfmeADL@@3MA
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 020h, 0D9h, 044h, 024h, 024h, 0D8h, 005h
    dd ?g_bfmeADL@@3MA
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 028h, 0D8h, 005h
    dd ?g_bfmeADL@@3MA
    db 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 08Ah, 087h, 0ACh, 000h, 000h, 000h, 083h, 0C4h, 008h, 084h, 0C0h, 0D9h, 05Ch, 024h, 020h, 00Fh
    db 084h, 078h, 001h, 000h, 000h, 0D9h, 044h, 024h, 01Ch, 0D8h, 09Fh, 08Ch, 000h, 000h, 000h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 00Fh, 08Bh, 0D0h, 002h, 000h, 000h, 0D9h, 044h, 024h, 020h, 0D8h, 09Fh
    db 090h, 000h, 000h, 000h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 08Bh, 0BBh, 002h, 000h, 000h, 0D9h
    db 087h, 08Ch, 000h, 000h, 000h, 0D9h, 044h, 024h, 014h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 075h, 006h, 0DDh, 0D8h, 0D9h, 044h, 024h, 014h, 0D9h, 087h, 094h, 000h, 000h, 000h, 0D9h, 044h
    db 024h, 01Ch, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h, 0DDh, 0D8h, 0D9h, 044h, 024h
    db 01Ch, 0D9h, 087h, 090h, 000h, 000h, 000h, 0D9h, 044h, 024h, 018h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 041h, 075h, 00Ch, 08Bh, 044h, 024h, 018h, 0DDh, 0D8h, 089h, 044h, 024h, 060h, 0EBh, 004h
    db 0D9h, 05Ch, 024h, 060h, 0D9h, 087h, 098h, 000h, 000h, 000h, 0D9h, 044h, 024h, 020h, 0D8h, 0D9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ch, 08Bh, 04Ch, 024h, 020h, 0DDh, 0D8h, 089h, 04Ch, 024h
    db 068h, 0EBh, 004h, 0D9h, 05Ch, 024h, 068h, 0D9h, 044h, 024h, 01Ch, 08Bh, 044h, 024h, 068h, 0D8h
    db 064h, 024h, 014h, 08Bh, 054h, 024h, 060h, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h, 024h, 034h, 0D8h
    db 064h, 024h, 02Ch, 0D9h, 05Ch, 024h, 028h, 0D9h, 0C1h, 0D8h, 064h, 024h, 014h, 0D8h, 074h, 024h
    db 010h, 0D8h, 04Ch, 024h, 028h, 0D8h, 044h, 024h, 02Ch, 0D9h, 0C1h, 0D8h, 064h, 024h, 014h, 0D8h
    db 074h, 024h, 010h, 0D8h, 04Ch, 024h, 028h, 0D8h, 044h, 024h, 02Ch, 0D9h, 044h, 024h, 020h, 089h
    db 044h, 024h, 020h, 0D8h, 064h, 024h, 018h, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h, 024h, 038h, 0D8h
    db 064h, 024h, 030h, 0D9h, 044h, 024h, 060h, 0D8h, 064h, 024h, 018h, 0D8h, 074h, 024h, 010h, 0D8h
    db 0C9h, 0D8h, 044h, 024h, 030h, 0D9h, 044h, 024h, 068h, 0D8h, 064h, 024h, 018h, 089h, 054h, 024h
    db 018h, 0D8h, 074h, 024h, 010h, 0D8h, 0CAh, 0D8h, 044h, 024h, 030h, 0D9h, 09Ch, 024h, 09Ch, 000h
    db 000h, 000h, 08Bh, 08Ch, 024h, 09Ch, 000h, 000h, 000h, 0D9h, 0C5h, 089h, 04Ch, 024h, 038h, 0D9h
    db 05Ch, 024h, 014h, 0D9h, 0C4h, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 0CBh, 0D9h, 05Ch, 024h, 02Ch, 0D9h
    db 0CAh, 0D9h, 05Ch, 024h, 030h, 0DDh, 0D9h, 0D9h, 05Ch, 024h, 034h, 0D8h, 0D9h, 0DFh, 0E0h, 0DDh
    db 0D8h, 0F6h, 0C4h, 041h, 00Fh, 08Bh, 080h, 001h, 000h, 000h, 0D9h, 044h, 024h, 068h, 0D8h, 05Ch
    db 024h, 060h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 08Bh, 06Dh, 001h, 000h, 000h, 08Dh, 054h, 024h
    db 07Ch, 052h, 08Dh, 04Ch, 024h, 028h
    call ?Get_Description@SurfaceClass@@QAEXAAUSurfaceDescription@1@@Z
    db 0DBh, 084h, 024h, 080h, 000h, 000h, 000h, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 085h, 0C0h
    db 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 08Ch, 024h, 084h, 000h, 000h, 000h, 085h, 0C9h, 0D9h, 044h, 024h, 02Ch, 0D8h, 0C9h, 0D9h
    db 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 034h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 034h, 0DDh, 0D8h, 0DBh
    db 084h, 024h, 084h, 000h, 000h, 000h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 055h, 014h, 08Bh, 045h, 010h, 08Bh, 04Dh, 00Ch, 052h, 08Bh, 055h, 008h, 050h, 051h, 052h
    db 08Dh, 044h, 024h, 03Ch, 050h, 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 04Ch, 024h, 068h, 0D9h, 044h
    db 024h, 048h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 048h, 0D9h, 044h, 024h, 050h, 0D8h, 0C9h, 0D9h, 05Ch
    db 024h, 050h, 0DDh, 0D8h
    call ?j_0004183a@@YAXXZ
    db 0D9h, 087h, 0A4h, 000h, 000h, 000h, 0D8h, 0A7h, 09Ch, 000h, 000h, 000h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 02Dh, 08Bh, 054h, 024h, 014h, 08Bh, 044h, 024h
    db 018h, 08Bh, 04Ch, 024h, 01Ch, 089h, 097h, 09Ch, 000h, 000h, 000h, 08Bh, 054h, 024h, 020h, 089h
    db 087h, 0A0h, 000h, 000h, 000h, 089h, 08Fh, 0A4h, 000h, 000h, 000h, 089h, 097h, 0A8h, 000h, 000h
    db 000h, 0E9h, 08Ch, 000h, 000h, 000h, 0D9h, 087h, 09Ch, 000h, 000h, 000h, 0D8h, 05Ch, 024h, 014h
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0D9h, 087h, 09Ch, 000h, 000h, 000h, 0EBh, 004h, 0D9h
    db 044h, 024h, 014h, 0D9h, 09Fh, 09Ch, 000h, 000h, 000h, 0D9h, 087h, 0A0h, 000h, 000h, 000h, 0D8h
    db 05Ch, 024h, 018h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0D9h, 087h, 0A0h, 000h, 000h, 000h
    db 0EBh, 004h, 0D9h, 044h, 024h, 018h, 0D9h, 09Fh, 0A0h, 000h, 000h, 000h, 0D9h, 087h, 0A4h, 000h
    db 000h, 000h, 0D8h, 05Ch, 024h, 01Ch, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0D9h, 087h, 0A4h
    db 000h, 000h, 000h, 0EBh, 004h, 0D9h, 044h, 024h, 01Ch, 0D9h, 09Fh, 0A4h, 000h, 000h, 000h, 0D9h
    db 087h, 0A8h, 000h, 000h, 000h, 0D8h, 05Ch, 024h, 020h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h
    db 0D9h, 087h, 0A8h, 000h, 000h, 000h, 0EBh, 004h, 0D9h, 044h, 024h, 020h, 0D9h, 09Fh, 0A8h, 000h
    db 000h, 000h, 08Bh, 044h, 024h, 054h, 08Bh, 054h, 024h, 04Ch, 08Bh, 04Fh, 014h, 040h, 083h, 0C2h
    db 024h, 03Bh, 0C1h, 089h, 044h, 024h, 054h, 089h, 054h, 024h, 04Ch, 00Fh, 08Ch, 0EDh, 0F9h, 0FFh
    db 0FFh, 08Dh, 04Ch, 024h, 024h, 0C7h, 084h, 024h, 0ACh, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1W3DRadarResetSurface@@QAE@XZ
    db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Bh, 08Bh, 0E5h, 05Dh, 0C2h, 010h, 000h
?d_0093eb50@@YAXXZ ENDP
_TEXT$d00d3eb50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00d3f310  retail @ 0x0093F310 size 224
public ?d_0093f310@@YAXXZ
?d_0093f310@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 0D6h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 2Ch, 56h, 8Bh, 0F1h, 8Bh, 46h, 68h, 2Bh, 46h
    db 70h, 85h, 0C0h, 89h, 44h, 24h, 08h, 0Fh, 8Eh, 0A3h, 00h, 00h, 00h, 8Bh, 46h, 4Ch
    db 8Bh, 48h, 2Ch, 89h, 4Ch, 24h, 04h, 0DBh, 44h, 24h, 04h, 0C7h, 44h, 24h, 0Ch, 00h
    db 00h, 00h, 00h, 0D9h, 5Ch, 24h, 04h, 8Bh, 46h, 7Ch, 85h, 0C0h, 0C7h, 44h, 24h, 38h
    db 00h, 00h, 00h, 00h, 74h, 14h, 8Bh, 10h, 50h, 0FFh, 52h, 04h, 8Bh, 44h, 24h, 0Ch
    db 85h, 0C0h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 0DBh, 44h, 24h, 08h, 8Bh, 56h
    db 7Ch, 8Bh, 4Eh, 64h, 8Bh, 46h, 60h, 0D8h, 46h, 60h, 89h, 54h, 24h, 0Ch, 8Dh, 54h
    db 24h, 0Ch, 89h, 4Ch, 24h, 14h, 0D9h, 5Ch, 24h, 18h, 52h, 0D9h, 44h, 24h, 08h, 8Dh
    db 4Eh, 04h, 0D8h, 46h, 64h, 89h, 44h, 24h, 14h, 0D9h, 5Ch, 24h, 20h, 0DBh, 46h, 70h
    db 0D9h, 5Ch, 24h, 24h, 0DBh, 46h, 6Ch, 0D9h, 54h, 24h, 28h, 0DBh, 46h, 68h, 0D9h, 5Ch
    db 24h, 2Ch, 0D8h, 44h, 24h, 08h, 0D9h, 5Ch, 24h, 30h, 0E8h, 51h, 0F0h, 0FFh, 0FFh, 8Dh
    db 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 38h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D0h, 0D1h, 0FBh, 0FFh
    db 8Bh, 4Ch, 24h, 30h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 38h, 0C3h
?d_0093f310@@YAXXZ ENDP

; ghidra: FUN_00d3f3f0  retail @ 0x0093F3F0 size 73
public ?d_0093f3f0@@YAXXZ
?d_0093f3f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 08h, 0D7h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 89h, 48h, 08h, 89h
    db 48h, 0Ch, 88h, 48h, 11h, 89h, 48h, 14h, 8Bh, 4Ch, 24h, 04h, 0C6h, 40h, 10h, 01h
    db 0C7h, 40h, 04h, 0F4h, 0CDh, 13h, 01h, 0C7h, 40h, 18h, 0Ah, 00h, 00h, 00h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0093f3f0@@YAXXZ ENDP

; ghidra: FUN_00d3f440  retail @ 0x0093F440 size 1329
_TEXT ENDS
_TEXT$d00d3f440 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00D3F440 size 1329
public ?d_0093f440@@YAXXZ
?d_0093f440@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105D728
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 0ACh, 000h, 000h, 000h, 053h, 08Bh, 01Dh
    dd __imp__SelectObject@8
    db 055h, 056h, 08Bh, 0E9h, 08Bh, 045h, 048h, 08Bh, 00Dh
    dd ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A
    db 08Bh, 071h, 010h, 057h, 050h, 056h, 089h, 0ACh, 024h, 08Ch, 000h, 000h, 000h, 089h, 0B4h, 024h
    db 080h, 000h, 000h, 000h, 089h, 0B4h, 024h, 084h, 000h, 000h, 000h, 0FFh, 0D3h, 089h, 084h, 024h
    db 080h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A
    db 06Ah, 001h, 08Dh, 054h, 024h, 050h, 052h, 06Ah, 001h, 0BFh, 0FFh, 0FFh, 000h, 000h, 08Dh, 084h
    db 024h, 0D8h, 000h, 000h, 000h, 089h, 07Ch, 024h, 058h, 08Bh, 051h, 010h, 050h, 052h, 0C7h, 084h
    db 024h, 0D8h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0FFh, 015h
    dd __imp__GetGlyphIndicesW@20
    db 066h, 039h, 07Ch, 024h, 04Ch, 075h, 058h, 066h, 08Bh, 084h, 024h, 0CCh, 000h, 000h, 000h, 066h
    db 03Dh, 000h, 001h, 073h, 01Eh, 08Bh, 08Ch, 024h, 080h, 000h, 000h, 000h, 00Fh, 0B7h, 0C0h, 051h
    db 056h, 0C7h, 044h, 085h, 04Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0D3h, 083h, 0C8h, 0FFh, 0E9h, 05Bh
    db 004h, 000h, 000h, 00Fh, 0B7h, 08Dh, 05Ch, 004h, 000h, 000h, 00Fh, 0B7h, 0D0h, 08Bh, 085h, 04Ch
    db 004h, 000h, 000h, 02Bh, 0D1h, 08Bh, 08Ch, 024h, 080h, 000h, 000h, 000h, 051h, 056h, 0C7h, 004h
    db 090h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0D3h, 083h, 0C8h, 0FFh, 0E9h, 02Fh, 004h, 000h, 000h, 08Bh
    db 04Dh, 040h, 08Bh, 0C1h, 00Fh, 0AFh, 0C1h, 089h, 044h, 024h, 068h, 0D1h, 0F8h, 089h, 044h, 024h
    db 060h, 0B8h, 040h, 000h, 000h, 000h, 099h, 0F7h, 0F9h, 08Dh, 054h, 024h, 03Ch, 052h, 0BEh, 001h
    db 000h, 000h, 000h, 056h, 08Bh, 0D8h, 08Bh, 0C1h, 00Fh, 0AFh, 0CBh, 00Fh, 0AFh, 0C3h, 089h, 044h
    db 024h, 03Ch, 089h, 04Ch, 024h, 040h, 08Bh, 00Dh
    dd ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A
    db 08Bh, 051h, 010h, 08Dh, 084h, 024h, 0D4h, 000h, 000h, 000h, 050h, 052h, 089h, 09Ch, 024h, 0A0h
    db 000h, 000h, 000h, 0FFh, 015h
    dd g_Va013590E8
    db 085h, 0C0h, 075h, 008h, 089h, 074h, 024h, 040h, 089h, 074h, 024h, 03Ch, 08Bh, 04Dh, 040h, 08Bh
    db 044h, 024h, 03Ch, 08Dh, 044h, 001h, 0FFh, 099h, 0F7h, 0F9h, 08Bh, 054h, 024h, 040h, 08Bh, 0F0h
    db 003h, 075h, 038h, 08Dh, 044h, 011h, 0FFh, 099h, 0F7h, 0F9h, 056h, 08Bh, 0CDh, 089h, 074h, 024h
    db 058h, 089h, 044h, 024h, 05Ch
    call ?Update_Current_Buffer@FontCharsClass@@AAEXH@Z
    db 08Bh, 045h, 020h, 08Bh, 04Dh, 014h, 08Bh, 054h, 081h, 0FCh, 08Bh, 00Ah, 08Bh, 045h, 028h, 08Dh
    db 03Ch, 041h, 08Bh, 04Dh, 030h, 08Bh, 0C1h, 099h, 02Bh, 0C2h, 0D1h, 0F8h, 02Bh, 0C8h, 00Fh, 0AFh
    db 0C6h, 089h, 04Ch, 024h, 014h, 0D1h, 0E0h, 08Bh, 0D7h, 003h, 0F8h, 08Bh, 0C8h, 089h, 07Ch, 024h
    db 044h, 08Bh, 0FAh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 033h, 0C0h, 0F3h, 0ABh, 08Bh, 0CAh, 08Bh, 054h
    db 024h, 058h, 083h, 0E1h, 003h, 00Fh, 0AFh, 0D6h, 0F3h, 0AAh, 08Bh, 04Ch, 024h, 014h, 08Bh, 07Ch
    db 024h, 044h, 00Fh, 0AFh, 0CEh, 0D1h, 0E1h, 08Dh, 03Ch, 057h, 033h, 0C0h, 08Bh, 0D1h, 0C1h, 0E9h
    db 002h, 0F3h, 0ABh, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0AAh, 08Dh, 044h, 01Eh, 0FFh, 099h, 0F7h
    db 0FBh, 033h, 0FFh, 089h, 0BCh, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 0C8h, 08Bh, 044h, 024h, 058h
    db 08Dh, 044h, 018h, 0FFh, 099h, 0F7h, 0FBh, 089h, 04Ch, 024h, 070h, 085h, 0C0h, 089h, 044h, 024h
    db 074h, 00Fh, 08Eh, 080h, 002h, 000h, 000h, 08Bh, 0FFh, 085h, 0C9h, 00Fh, 08Eh, 066h, 002h, 000h
    db 000h, 08Bh, 0C7h, 00Fh, 0AFh, 0FBh, 00Fh, 0AFh, 044h, 024h, 038h, 033h, 0D2h, 089h, 054h, 024h
    db 010h, 089h, 054h, 024h, 018h, 089h, 054h, 024h, 028h, 08Bh, 054h, 024h, 034h, 089h, 084h, 024h
    db 0B8h, 000h, 000h, 000h, 0F7h, 0D8h, 0F7h, 0DAh, 089h, 044h, 024h, 064h, 089h, 0BCh, 024h, 098h
    db 000h, 000h, 000h, 089h, 094h, 024h, 08Ch, 000h, 000h, 000h, 089h, 04Ch, 024h, 014h, 0EBh, 00Bh
    db 08Bh, 044h, 024h, 064h, 08Bh, 0BCh, 024h, 098h, 000h, 000h, 000h, 08Bh, 054h, 024h, 034h, 033h
    db 0C9h, 051h, 06Ah, 001h, 089h, 094h, 024h, 0B4h, 000h, 000h, 000h, 08Bh, 054h, 024h, 040h, 089h
    db 08Ch, 024h, 0ACh, 000h, 000h, 000h, 089h, 08Ch, 024h, 0B0h, 000h, 000h, 000h, 089h, 094h, 024h
    db 0B8h, 000h, 000h, 000h, 08Dh, 08Ch, 024h, 0D4h, 000h, 000h, 000h, 051h, 08Bh, 00Dh
    dd ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A
    db 08Dh, 094h, 024h, 0B0h, 000h, 000h, 000h, 052h, 08Bh, 051h, 010h, 06Ah, 002h, 050h, 08Bh, 044h
    db 024h, 040h, 050h, 052h, 0FFh, 015h
    dd g_Va013590D0
    db 08Bh, 044h, 024h, 010h, 003h, 0C3h, 03Bh, 0C6h, 089h, 044h, 024h, 06Ch, 089h, 044h, 024h, 02Ch
    db 07Eh, 004h, 089h, 074h, 024h, 02Ch, 08Bh, 054h, 024h, 058h, 08Dh, 00Ch, 01Fh, 03Bh, 0CAh, 089h
    db 04Ch, 024h, 030h, 07Eh, 006h, 089h, 054h, 024h, 030h, 08Bh, 0CAh, 08Bh, 094h, 024h, 098h, 000h
    db 000h, 000h, 03Bh, 0D1h, 089h, 07Ch, 024h, 05Ch, 00Fh, 08Dh, 04Ch, 001h, 000h, 000h, 08Bh, 044h
    db 024h, 010h, 00Fh, 0AFh, 0D6h, 08Bh, 04Ch, 024h, 044h, 003h, 0D0h, 08Dh, 014h, 051h, 089h, 054h
    db 024h, 020h, 08Bh, 044h, 024h, 020h, 089h, 044h, 024h, 050h, 08Bh, 045h, 040h, 08Bh, 0C8h, 00Fh
    db 0AFh, 0CFh, 08Dh, 014h, 008h, 08Bh, 044h, 024h, 040h, 03Bh, 0D0h, 089h, 08Ch, 024h, 088h, 000h
    db 000h, 000h, 089h, 054h, 024h, 01Ch, 07Eh, 006h, 089h, 044h, 024h, 01Ch, 08Bh, 0D0h, 08Bh, 044h
    db 024h, 010h, 03Bh, 044h, 024h, 02Ch, 089h, 044h, 024h, 024h, 00Fh, 08Dh, 0D8h, 000h, 000h, 000h
    db 0EBh, 00Bh, 08Bh, 054h, 024h, 01Ch, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 045h, 040h
    db 08Bh, 0F0h, 00Fh, 0AFh, 074h, 024h, 024h, 08Dh, 01Ch, 030h, 08Bh, 044h, 024h, 03Ch, 033h, 0FFh
    db 03Bh, 0D8h, 07Eh, 002h, 08Bh, 0D8h, 03Bh, 0CAh, 07Dh, 065h, 08Bh, 0ACh, 024h, 0B8h, 000h, 000h
    db 000h, 08Bh, 0C1h, 02Bh, 0C5h, 08Bh, 06Ch, 024h, 018h, 0C1h, 0E0h, 006h, 02Bh, 0C5h, 003h, 0C6h
    db 02Bh, 0D1h, 08Dh, 02Ch, 040h, 089h, 054h, 024h, 048h, 08Dh, 064h, 024h, 000h, 03Bh, 0F3h, 07Dh
    db 026h, 08Bh, 00Dh
    dd ?g_fontCharsGdiState0134AEAC@@3PAVFontCharsClassGdiState@@A
    db 08Bh, 041h, 00Ch, 08Bh, 0CBh, 003h, 0C5h, 02Bh, 0CEh, 08Ah, 010h, 00Fh, 0B6h, 0D2h, 0C1h, 0EAh
    db 004h, 083h, 0C0h, 003h, 003h, 0FAh, 049h, 075h, 0F0h, 08Bh, 08Ch, 024h, 088h, 000h, 000h, 000h
    db 08Bh, 044h, 024h, 048h, 081h, 0C5h, 0C0h, 000h, 000h, 000h, 048h, 089h, 044h, 024h, 048h, 075h
    db 0C5h, 08Bh, 0ACh, 024h, 084h, 000h, 000h, 000h, 08Bh, 044h, 024h, 060h, 033h, 0D2h, 003h, 0C7h
    db 0F7h, 074h, 024h, 068h, 08Bh, 0D0h, 08Bh, 044h, 024h, 050h, 0C1h, 0E2h, 00Ch, 081h, 0CAh, 0FFh
    db 00Fh, 000h, 000h, 066h, 089h, 010h, 08Bh, 054h, 024h, 02Ch, 083h, 0C0h, 002h, 089h, 044h, 024h
    db 050h, 08Bh, 044h, 024h, 024h, 040h, 03Bh, 0C2h, 089h, 044h, 024h, 024h, 00Fh, 08Ch, 039h, 0FFh
    db 0FFh, 0FFh, 08Bh, 074h, 024h, 054h, 08Bh, 09Ch, 024h, 090h, 000h, 000h, 000h, 08Bh, 07Ch, 024h
    db 05Ch, 08Bh, 04Ch, 024h, 020h, 08Dh, 004h, 036h, 003h, 0C8h, 08Bh, 044h, 024h, 030h, 047h, 03Bh
    db 0F8h, 089h, 07Ch, 024h, 05Ch, 089h, 04Ch, 024h, 020h, 00Fh, 08Ch, 0CCh, 0FEh, 0FFh, 0FFh, 08Bh
    db 044h, 024h, 06Ch, 08Bh, 04Ch, 024h, 034h, 08Bh, 054h, 024h, 018h, 003h, 0D1h, 08Bh, 04Ch, 024h
    db 028h, 089h, 054h, 024h, 018h, 08Bh, 094h, 024h, 08Ch, 000h, 000h, 000h, 089h, 044h, 024h, 010h
    db 08Bh, 044h, 024h, 014h, 003h, 0CAh, 048h, 089h, 04Ch, 024h, 028h, 089h, 044h, 024h, 014h, 00Fh
    db 085h, 0E8h, 0FDh, 0FFh, 0FFh, 08Bh, 0BCh, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 044h, 024h, 074h
    db 08Bh, 04Ch, 024h, 070h, 047h, 03Bh, 0F8h, 089h, 0BCh, 024h, 0A0h, 000h, 000h, 000h, 00Fh, 08Ch
    db 082h, 0FDh, 0FFh, 0FFh, 06Ah, 00Ch
    call ??2@YAPAXI@Z
    db 08Bh, 0F8h, 066h, 08Bh, 084h, 024h, 0D0h, 000h, 000h, 000h, 066h, 089h, 007h, 066h, 089h, 077h
    db 002h, 066h, 0C7h, 047h, 004h, 000h, 000h, 08Bh, 04Dh, 020h, 08Bh, 055h, 014h, 08Bh, 044h, 08Ah
    db 0FCh, 08Bh, 010h, 08Bh, 04Dh, 028h, 08Dh, 004h, 04Ah, 089h, 047h, 008h, 066h, 08Bh, 084h, 024h
    db 0D0h, 000h, 000h, 000h, 083h, 0C4h, 004h, 066h, 03Dh, 000h, 001h, 073h, 009h, 00Fh, 0B7h, 0C8h
    db 089h, 07Ch, 08Dh, 04Ch, 0EBh, 015h, 00Fh, 0B7h, 095h, 05Ch, 004h, 000h, 000h, 08Bh, 08Dh, 04Ch
    db 004h, 000h, 000h, 00Fh, 0B7h, 0C0h, 02Bh, 0C2h, 089h, 03Ch, 081h, 08Bh, 055h, 038h, 08Bh, 084h
    db 024h, 080h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 078h, 003h, 0D6h, 00Fh, 0AFh, 055h, 02Ch, 08Bh
    db 075h, 028h, 050h, 003h, 0F2h, 051h, 089h, 075h, 028h, 0FFh, 015h
    dd __imp__SelectObject@8
    db 08Bh, 0C7h, 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 081h, 0C4h, 0B8h, 000h, 000h, 000h, 0C2h, 004h, 000h
?d_0093f440@@YAXXZ ENDP
_TEXT$d00d3f440 ENDS
_TEXT SEGMENT

; ghidra: FUN_00d3f980  retail @ 0x0093F980 size 227
public ?d_0093f980@@YAXXZ
?d_0093f980@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 0D7h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 28h, 56h, 8Bh, 0F1h, 8Bh, 46h, 68h, 2Bh, 46h
    db 70h, 85h, 0C0h, 89h, 44h, 24h, 04h, 0Fh, 8Eh, 0A4h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 3Ch, 8Bh, 48h, 2Ch, 89h, 4Ch, 24h, 3Ch, 0DBh, 44h, 24h, 3Ch, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 3Ch, 8Bh, 46h, 7Ch, 85h, 0C0h, 0C7h, 44h, 24h
    db 34h, 00h, 00h, 00h, 00h, 74h, 14h, 8Bh, 10h, 50h, 0FFh, 52h, 04h, 8Bh, 44h, 24h
    db 08h, 85h, 0C0h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 0DBh, 44h, 24h, 04h, 8Bh
    db 56h, 7Ch, 8Bh, 4Eh, 64h, 8Bh, 46h, 60h, 0D8h, 46h, 60h, 89h, 54h, 24h, 08h, 8Dh
    db 54h, 24h, 08h, 89h, 4Ch, 24h, 10h, 0D9h, 5Ch, 24h, 14h, 52h, 0D9h, 44h, 24h, 40h
    db 8Dh, 4Eh, 04h, 0D8h, 46h, 64h, 89h, 44h, 24h, 10h, 0D9h, 5Ch, 24h, 1Ch, 0DBh, 46h
    db 70h, 0D9h, 5Ch, 24h, 20h, 0DBh, 46h, 6Ch, 0D9h, 54h, 24h, 24h, 0DBh, 46h, 68h, 0D9h
    db 5Ch, 24h, 28h, 0D8h, 44h, 24h, 40h, 0D9h, 5Ch, 24h, 2Ch, 0E8h, 0E0h, 0E9h, 0FFh, 0FFh
    db 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 34h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 5Fh, 0CBh, 0FBh
    db 0FFh, 8Bh, 4Ch, 24h, 2Ch, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 34h
    db 0C2h, 04h, 00h
?d_0093f980@@YAXXZ ENDP

; ghidra: FUN_00d3fb80  retail @ 0x0093FB80 size 136
public ?d_0093fb80@@YAXXZ
?d_0093fb80@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 39h, 4Eh, 10h, 7Ch, 28h, 8Ah, 46h, 0Dh, 84h, 0C0h
    db 75h, 04h, 85h, 0C9h, 75h, 17h, 8Bh, 46h, 14h, 85h, 0C0h, 7Eh, 10h, 8Bh, 16h, 03h
    db 0C1h, 6Ah, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h, 75h, 06h, 32h, 0C0h, 5Eh
    db 0C2h, 04h, 00h, 8Bh, 46h, 10h, 8Bh, 56h, 04h, 8Dh, 48h, 01h, 6Bh, 0C0h, 1Ch, 03h
    db 0C2h, 89h, 4Eh, 10h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 0F8h, 8Bh, 06h, 85h, 0C0h, 74h
    db 06h, 8Bh, 10h, 50h, 0FFh, 52h, 04h, 8Bh, 07h, 85h, 0C0h, 74h, 06h, 8Bh, 08h, 50h
    db 0FFh, 51h, 08h, 8Bh, 16h, 89h, 17h, 83h, 0C6h, 04h, 83h, 0C7h, 04h, 56h, 8Bh, 0CFh
    db 0E8h, 0ABh, 0D2h, 0FFh, 0FFh, 8Bh, 46h, 10h, 89h, 47h, 10h, 8Bh, 4Eh, 14h, 89h, 4Fh
    db 14h, 5Fh, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_0093fb80@@YAXXZ ENDP

; ghidra: FUN_00d3fc10  retail @ 0x0093FC10 size 294
public ?d_0093fc10@@YAXXZ
?d_0093fc10@@YAXXZ PROC
    db 8Bh, 54h, 24h, 08h, 85h, 0D2h, 53h, 8Bh, 0D9h, 0Fh, 84h, 8Ch, 00h, 00h, 00h, 8Bh
    db 4Bh, 04h, 8Bh, 43h, 08h, 2Bh, 0C1h, 0D1h, 0F8h, 3Bh, 0C2h, 0Fh, 82h, 0E8h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 10h, 0Fh, 0B7h, 00h, 55h, 8Bh, 6Ch, 24h, 0Ch, 2Bh, 0CDh, 56h
    db 8Bh, 73h, 04h, 0D1h, 0F9h, 57h, 8Bh, 0F9h, 3Bh, 0FAh, 89h, 44h, 24h, 18h, 89h, 7Ch
    db 24h, 1Ch, 76h, 5Bh, 8Dh, 04h, 12h, 8Bh, 0FEh, 2Bh, 0F8h, 3Bh, 0F7h, 89h, 44h, 24h
    db 1Ch, 74h, 14h, 8Bh, 0CEh, 2Bh, 0CFh, 51h, 57h, 56h, 0FFh, 15h, 5Ch, 94h, 35h, 01h
    db 8Bh, 44h, 24h, 28h, 83h, 0C4h, 0Ch, 8Bh, 4Bh, 04h, 03h, 0C8h, 2Bh, 0FDh, 85h, 0FFh
    db 89h, 4Bh, 04h, 7Eh, 12h, 57h, 55h, 2Bh, 0F7h, 56h, 0FFh, 15h, 5Ch, 94h, 35h, 01h
    db 8Bh, 44h, 24h, 28h, 83h, 0C4h, 0Ch, 8Dh, 54h, 24h, 18h, 52h, 03h, 0C5h, 50h, 55h
    db 0E8h, 7Bh, 0D2h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 0Ch, 00h, 8Bh
    db 0CAh, 2Bh, 0CFh, 89h, 4Ch, 24h, 14h, 74h, 1Eh, 66h, 8Bh, 0D0h, 8Bh, 0FEh, 0C1h, 0E2h
    db 10h, 66h, 8Bh, 0D0h, 0D1h, 0E9h, 8Bh, 0C2h, 0F3h, 0ABh, 13h, 0C9h, 66h, 0F3h, 0ABh, 8Bh
    db 7Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 14h, 8Bh, 53h, 04h, 8Dh, 04h, 09h, 03h, 0D0h, 3Bh
    db 0F5h, 89h, 53h, 04h, 8Bh, 0C2h, 74h, 10h, 8Bh, 0CEh, 2Bh, 0CDh, 51h, 55h, 50h, 0FFh
    db 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 8Bh, 43h, 04h, 8Dh, 14h, 3Fh, 03h, 0C2h
    db 89h, 43h, 04h, 8Dh, 44h, 24h, 18h, 50h, 56h, 55h, 0E8h, 11h, 0D2h, 0FFh, 0FFh, 83h
    db 0C4h, 0Ch, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 0Ch, 00h, 8Bh, 44h, 24h, 08h, 6Ah, 00h, 52h
    db 8Bh, 54h, 24h, 18h, 8Dh, 4Ch, 24h, 18h, 51h, 52h, 50h, 8Bh, 0CBh, 0E8h, 0FAh, 82h
    db 70h, 0FFh, 5Bh, 0C2h, 0Ch, 00h
?d_0093fc10@@YAXXZ ENDP

; ghidra: FUN_00d3fd80  retail @ 0x0093FD80 size 178
public ?d_0093fd80@@YAXXZ
?d_0093fd80@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 0F1h, 3Bh, 1Eh, 57h
    db 74h, 41h, 8Bh, 44h, 24h, 24h, 85h, 0C0h, 75h, 12h, 8Bh, 44h, 24h, 18h, 85h, 0C0h
    db 75h, 31h, 66h, 8Bh, 45h, 00h, 66h, 3Bh, 43h, 10h, 72h, 27h, 6Ah, 18h, 0E8h, 8Dh
    db 0E7h, 0EEh, 0FFh, 8Bh, 0F8h, 8Dh, 4Fh, 10h, 55h, 51h, 0E8h, 61h, 0DFh, 0FFh, 0FFh, 89h
    db 7Bh, 0Ch, 8Bh, 06h, 8Bh, 48h, 0Ch, 83h, 0C4h, 0Ch, 3Bh, 0D9h, 75h, 36h, 89h, 78h
    db 0Ch, 0EBh, 31h, 6Ah, 18h, 0E8h, 66h, 0E7h, 0EEh, 0FFh, 8Bh, 0F8h, 8Dh, 57h, 10h, 55h
    db 52h, 0E8h, 3Ah, 0DFh, 0FFh, 0FFh, 89h, 7Bh, 08h, 8Bh, 06h, 83h, 0C4h, 0Ch, 3Bh, 0D8h
    db 75h, 0Ah, 89h, 78h, 04h, 8Bh, 06h, 89h, 78h, 0Ch, 0EBh, 08h, 3Bh, 58h, 08h, 75h
    db 03h, 89h, 78h, 08h, 33h, 0C0h, 89h, 5Fh, 04h, 89h, 47h, 08h, 89h, 47h, 0Ch, 8Bh
    db 0Eh, 83h, 0C1h, 04h, 51h, 57h, 0E8h, 0B5h, 0CBh, 0EEh, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h
    db 08h, 40h, 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 89h, 38h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h
    db 14h, 00h
?d_0093fd80@@YAXXZ ENDP

; ghidra: FUN_00d40010  retail @ 0x00940010 size 348
public ?d_00940010@@YAXXZ
?d_00940010@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D9h, 0D7h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 06h, 8Ch, 0CEh, 13h, 01h, 8Bh, 46h, 20h, 33h, 0EDh, 3Bh, 0C5h, 0C7h, 44h, 24h, 18h
    db 03h, 00h, 00h, 00h, 74h, 46h, 8Bh, 46h, 14h, 8Bh, 38h, 3Bh, 0FDh, 74h, 11h, 8Bh
    db 07h, 50h, 0E8h, 99h, 1Eh, 0F4h, 0FFh, 57h, 0E8h, 53h, 1Eh, 0F4h, 0FFh, 83h, 0C4h, 08h
    db 8Bh, 46h, 20h, 3Bh, 0C5h, 7Eh, 20h, 8Dh, 48h, 0FFh, 33h, 0C0h, 3Bh, 0CDh, 89h, 4Eh
    db 20h, 7Eh, 14h, 8Bh, 4Eh, 14h, 8Bh, 54h, 81h, 04h, 8Dh, 0Ch, 81h, 89h, 11h, 8Bh
    db 4Eh, 20h, 40h, 3Bh, 0C1h, 7Ch, 0ECh, 39h, 6Eh, 20h, 75h, 0BAh, 8Bh, 46h, 48h, 3Bh
    db 0C5h, 53h, 8Bh, 1Dh, 0C8h, 90h, 35h, 01h, 74h, 06h, 50h, 0FFh, 0D3h, 89h, 6Eh, 48h
    db 8Bh, 0CEh, 0E8h, 0A9h, 0C6h, 0FFh, 0FFh, 0A1h, 0ACh, 0AEh, 34h, 01h, 0FFh, 08h, 0A1h, 0ACh
    db 0AEh, 34h, 01h, 39h, 28h, 75h, 4Fh, 8Bh, 48h, 08h, 85h, 0C9h, 8Dh, 78h, 08h, 8Bh
    db 0E8h, 74h, 19h, 8Bh, 48h, 04h, 8Bh, 50h, 10h, 51h, 52h, 0FFh, 15h, 0FCh, 90h, 35h
    db 01h, 8Bh, 07h, 50h, 0FFh, 0D3h, 0C7h, 07h, 00h, 00h, 00h, 00h, 8Bh, 45h, 10h, 85h
    db 0C0h, 74h, 0Eh, 50h, 0FFh, 15h, 0C4h, 90h, 35h, 01h, 0C7h, 45h, 10h, 00h, 00h, 00h
    db 00h, 55h, 0E8h, 0B9h, 1Dh, 0F4h, 0FFh, 83h, 0C4h, 04h, 0C7h, 05h, 0ACh, 0AEh, 34h, 01h
    db 00h, 00h, 00h, 00h, 33h, 0EDh, 8Dh, 8Eh, 50h, 04h, 00h, 00h, 0E8h, 7Fh, 0F9h, 0FFh
    db 0FFh, 8Dh, 4Eh, 44h, 0C6h, 44h, 24h, 1Ch, 02h, 0E8h, 82h, 0B6h, 09h, 00h, 8Bh, 46h
    db 14h, 3Bh, 0C5h, 0C7h, 46h, 10h, 0C4h, 0CDh, 13h, 01h, 5Bh, 74h, 13h, 8Ah, 4Eh, 1Dh
    db 84h, 0C9h, 74h, 0Ch, 50h, 0E8h, 0B6h, 1Dh, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 6Eh, 14h
    db 8Dh, 4Eh, 0Ch, 0C6h, 46h, 1Dh, 00h, 89h, 6Eh, 18h, 0C6h, 44h, 24h, 18h, 00h, 0E8h
    db 4Ch, 0B6h, 09h, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh, 0C7h, 06h, 0ACh, 35h, 11h, 01h, 5Eh
    db 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00940010@@YAXXZ ENDP

; ghidra: FUN_00d40450  retail @ 0x00940450 size 382
public ?d_00940450@@YAXXZ
?d_00940450@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Ch, 0D8h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 8Bh, 74h, 24h, 20h, 33h, 0EDh, 3Bh
    db 0F5h, 57h, 8Bh, 0D9h, 0Fh, 84h, 36h, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 28h, 3Bh, 0FDh
    db 0C6h, 43h, 0Ch, 00h, 75h, 24h, 8Bh, 0C6h, 6Bh, 0C0h, 1Ch, 83h, 0C0h, 04h, 50h, 0E8h
    db 0DCh, 1Ah, 0F4h, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 3Bh, 0C5h, 89h, 6Ch, 24h
    db 1Ch, 74h, 2Bh, 89h, 30h, 8Dh, 68h, 04h, 0EBh, 11h, 89h, 7Ch, 24h, 10h, 0C7h, 44h
    db 24h, 1Ch, 01h, 00h, 00h, 00h, 89h, 37h, 8Dh, 6Fh, 04h, 68h, 18h, 60h, 41h, 00h
    db 68h, 0F0h, 0F3h, 0D3h, 00h, 56h, 6Ah, 1Ch, 55h, 0E8h, 16h, 6Ah, 0Bh, 00h, 85h, 0EDh
    db 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0C6h, 43h, 0Ch, 01h, 75h, 17h, 5Fh, 5Eh
    db 5Dh, 32h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C2h, 08h, 00h, 8Bh, 43h, 04h, 85h, 0C0h, 0Fh, 84h, 9Eh, 00h, 00h, 00h
    db 8Bh, 43h, 08h, 3Bh, 0F0h, 7Dh, 02h, 8Bh, 0C6h, 85h, 0C0h, 7Eh, 5Bh, 33h, 0F6h, 89h
    db 44h, 24h, 10h, 8Bh, 7Bh, 04h, 8Bh, 04h, 37h, 03h, 0FEh, 85h, 0C0h, 74h, 06h, 8Bh
    db 08h, 50h, 0FFh, 51h, 04h, 8Bh, 04h, 2Eh, 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh
    db 52h, 08h, 8Bh, 07h, 83h, 0C7h, 04h, 57h, 8Dh, 4Ch, 2Eh, 04h, 89h, 04h, 2Eh, 0E8h
    db 5Ch, 0C9h, 0FFh, 0FFh, 8Bh, 4Fh, 10h, 8Bh, 44h, 24h, 10h, 89h, 4Ch, 2Eh, 14h, 8Bh
    db 57h, 14h, 89h, 54h, 2Eh, 18h, 83h, 0C6h, 1Ch, 48h, 89h, 44h, 24h, 10h, 75h, 0B3h
    db 8Bh, 74h, 24h, 24h, 8Bh, 7Ch, 24h, 28h, 8Ah, 43h, 0Dh, 84h, 0C0h, 74h, 2Fh, 8Bh
    db 43h, 04h, 85h, 0C0h, 74h, 21h, 8Bh, 48h, 0FCh, 8Dh, 78h, 0FCh, 68h, 18h, 60h, 41h
    db 00h, 51h, 6Ah, 1Ch, 50h, 0E8h, 0ECh, 67h, 0Bh, 00h, 57h, 0E8h, 60h, 19h, 0F4h, 0FFh
    db 8Bh, 7Ch, 24h, 2Ch, 83h, 0C4h, 04h, 0C7h, 43h, 04h, 00h, 00h, 00h, 00h, 33h, 0C0h
    db 85h, 0FFh, 0Fh, 94h, 0C0h, 89h, 6Bh, 04h, 89h, 73h, 08h, 88h, 43h, 0Dh, 0EBh, 07h
    db 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h, 0Ch, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh, 0B0h, 01h
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_00940450@@YAXXZ ENDP

; ghidra: FUN_00d40610  retail @ 0x00940610 size 342
public ?d_00940610@@YAXXZ
?d_00940610@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 57h, 0D8h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 46h, 04h, 01h, 00h, 00h, 00h, 33h, 0DBh, 0C7h, 06h, 8Ch, 0CEh, 13h, 01h, 0A1h, 24h
    db 91h, 2Dh, 01h, 8Dh, 7Eh, 0Ch, 53h, 53h, 8Bh, 0CFh, 89h, 5Ch, 24h, 20h, 89h, 07h
    db 0E8h, 3Bh, 0B2h, 09h, 00h, 8Bh, 0Fh, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 89h
    db 5Eh, 14h, 89h, 5Eh, 18h, 0C6h, 46h, 1Ch, 01h, 88h, 5Eh, 1Dh, 0C7h, 46h, 10h, 0DCh
    db 0CDh, 13h, 01h, 0C7h, 46h, 24h, 0Ah, 00h, 00h, 00h, 89h, 5Eh, 20h, 89h, 5Eh, 28h
    db 89h, 5Eh, 2Ch, 89h, 5Eh, 30h, 89h, 5Eh, 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 0C7h
    db 46h, 40h, 01h, 00h, 00h, 00h, 0A1h, 24h, 91h, 2Dh, 01h, 8Dh, 7Eh, 44h, 53h, 53h
    db 8Bh, 0CFh, 0C6h, 44h, 24h, 20h, 02h, 89h, 07h, 0E8h, 0E2h, 0B1h, 09h, 00h, 8Bh, 0Fh
    db 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 89h, 5Eh, 48h, 89h, 9Eh, 4Ch, 04h, 00h
    db 00h, 6Ah, 18h, 0C6h, 44h, 24h, 1Ch, 03h, 89h, 9Eh, 50h, 04h, 00h, 00h, 0E8h, 6Dh
    db 0DEh, 0EEh, 0FFh, 89h, 86h, 50h, 04h, 00h, 00h, 89h, 9Eh, 54h, 04h, 00h, 00h, 88h
    db 18h, 8Bh, 86h, 50h, 04h, 00h, 00h, 89h, 58h, 04h, 8Bh, 86h, 50h, 04h, 00h, 00h
    db 89h, 40h, 08h, 8Bh, 86h, 50h, 04h, 00h, 00h, 83h, 0C4h, 04h, 89h, 40h, 0Ch, 66h
    db 0C7h, 86h, 5Ch, 04h, 00h, 00h, 0FFh, 0FFh, 66h, 89h, 9Eh, 5Eh, 04h, 00h, 00h, 88h
    db 9Eh, 60h, 04h, 00h, 00h, 0A1h, 0ACh, 0AEh, 34h, 01h, 3Bh, 0C3h, 0C6h, 44h, 24h, 18h
    db 04h, 75h, 1Eh, 6Ah, 14h, 0E8h, 06h, 18h, 0F4h, 0FFh, 83h, 0C4h, 04h, 3Bh, 0C3h, 74h
    db 09h, 8Bh, 0C8h, 0E8h, 08h, 0BCh, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0ACh, 0AEh, 34h
    db 01h, 0FFh, 00h, 89h, 5Eh, 08h, 33h, 0C0h, 8Dh, 7Eh, 4Ch, 0B9h, 00h, 01h, 00h, 00h
    db 0F3h, 0ABh, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00940610@@YAXXZ ENDP

; ghidra: FUN_00d407b0  retail @ 0x009407B0 size 87
public ?d_009407b0@@YAXXZ
?d_009407b0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 04h, 8Bh, 37h, 8Bh, 0C8h, 2Bh
    db 0CEh, 0D1h, 0F9h, 3Bh, 0D1h, 73h, 2Bh, 3Bh, 0C0h, 8Dh, 0Ch, 56h, 75h, 0Ah, 8Bh, 0C1h
    db 89h, 47h, 04h, 5Fh, 5Eh, 0C2h, 08h, 00h, 8Bh, 0F0h, 2Bh, 0F0h, 56h, 50h, 51h, 0FFh
    db 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C6h, 89h, 47h, 04h, 5Fh, 5Eh, 0C2h
    db 08h, 00h, 8Dh, 74h, 24h, 10h, 56h, 2Bh, 0D1h, 52h, 50h, 8Bh, 0CFh, 0E8h, 0Eh, 0F4h
    db 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_009407b0@@YAXXZ ENDP

; ghidra: FUN_00d40bf0  retail @ 0x00940BF0 size 333
public ?d_00940bf0@@YAXXZ
?d_00940bf0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E1h, 0D8h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 33h, 0DBh, 53h, 8Dh, 7Eh
    db 04h, 53h, 8Bh, 0CFh, 89h, 74h, 24h, 14h, 0C7h, 06h, 0ACh, 0CEh, 13h, 01h, 0E8h, 5Dh
    db 0CEh, 0FFh, 0FFh, 0C7h, 07h, 44h, 0CEh, 13h, 01h, 0C7h, 47h, 14h, 0Ah, 00h, 00h, 00h
    db 89h, 5Fh, 10h, 53h, 8Dh, 7Eh, 1Ch, 53h, 8Bh, 0CFh, 89h, 5Ch, 24h, 20h, 0E8h, 9Dh
    db 0F2h, 0FFh, 0FFh, 0C7h, 07h, 94h, 0CEh, 13h, 01h, 0C7h, 47h, 14h, 0Ah, 00h, 00h, 00h
    db 89h, 5Fh, 10h, 53h, 8Dh, 7Eh, 34h, 53h, 8Bh, 0CFh, 0C6h, 44h, 24h, 20h, 01h, 0E8h
    db 4Ch, 0CFh, 0FFh, 0FFh, 0C7h, 07h, 5Ch, 0CEh, 13h, 01h, 0C7h, 47h, 14h, 0Ah, 00h, 00h
    db 00h, 89h, 5Fh, 10h, 89h, 5Eh, 4Ch, 89h, 5Eh, 50h, 89h, 5Eh, 54h, 89h, 5Eh, 58h
    db 89h, 5Eh, 5Ch, 89h, 5Eh, 60h, 89h, 5Eh, 64h, 89h, 5Eh, 68h, 89h, 5Eh, 6Ch, 53h
    db 8Dh, 4Eh, 7Ch, 0C6h, 44h, 24h, 1Ch, 02h, 89h, 5Eh, 70h, 89h, 5Eh, 74h, 89h, 5Eh
    db 78h, 0E8h, 0EAh, 0B8h, 0FBh, 0FFh, 8Bh, 4Ch, 24h, 10h, 88h, 9Eh, 80h, 00h, 00h, 00h
    db 89h, 9Eh, 84h, 00h, 00h, 00h, 88h, 9Eh, 88h, 00h, 00h, 00h, 89h, 9Eh, 8Ch, 00h
    db 00h, 00h, 89h, 9Eh, 90h, 00h, 00h, 00h, 89h, 9Eh, 94h, 00h, 00h, 00h, 89h, 9Eh
    db 98h, 00h, 00h, 00h, 89h, 9Eh, 9Ch, 00h, 00h, 00h, 89h, 9Eh, 0A0h, 00h, 00h, 00h
    db 89h, 9Eh, 0A4h, 00h, 00h, 00h, 89h, 9Eh, 0A8h, 00h, 00h, 00h, 88h, 9Eh, 0ACh, 00h
    db 00h, 00h, 88h, 9Eh, 0ADh, 00h, 00h, 00h, 88h, 9Eh, 0AEh, 00h, 00h, 00h, 89h, 9Eh
    db 0B0h, 00h, 00h, 00h, 89h, 9Eh, 0B4h, 00h, 00h, 00h, 89h, 9Eh, 0B8h, 00h, 00h, 00h
    db 0B8h, 00h, 00h, 80h, 3Fh, 89h, 86h, 0BCh, 00h, 00h, 00h, 89h, 86h, 0C0h, 00h, 00h
    db 00h, 89h, 9Eh, 0C4h, 00h, 00h, 00h, 89h, 9Eh, 0C8h, 00h, 00h, 00h, 5Fh, 8Bh, 0C6h
    db 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00940bf0@@YAXXZ ENDP

; ghidra: FUN_00d41290  retail @ 0x00941290 size 81
public ?d_00941290@@YAXXZ
?d_00941290@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 8Bh, 0F1h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Dh, 44h, 24h, 10h, 8Dh, 0BEh, 50h, 04h, 00h, 00h, 50h, 8Bh, 0CFh, 0E8h, 2Eh, 0CAh
    db 0FFh, 0FFh, 3Bh, 07h, 74h, 07h, 8Bh, 40h, 14h, 85h, 0C0h, 75h, 08h, 53h, 8Bh, 0CEh
    db 0E8h, 7Bh, 0FAh, 0FFh, 0FFh, 83h, 0F8h, 0FFh, 75h, 11h, 8Bh, 46h, 08h, 85h, 0C0h, 74h
    db 08h, 3Bh, 0F0h, 74h, 04h, 8Bh, 0F0h, 0EBh, 0C7h, 33h, 0C0h, 5Fh, 5Eh, 5Bh, 0C2h, 04h
    db 00h
?d_00941290@@YAXXZ ENDP

; ghidra: FUN_00d412f0  retail @ 0x009412F0 size 260
public ?d_009412f0@@YAXXZ
?d_009412f0@@YAXXZ PROC
    db 51h, 8Bh, 54h, 24h, 08h, 66h, 81h, 0FAh, 01h, 0Eh, 56h, 8Bh, 0F1h, 72h, 07h, 66h
    db 81h, 0FAh, 3Ah, 0Eh, 76h, 12h, 66h, 81h, 0FAh, 3Fh, 0Eh, 0Fh, 82h, 80h, 00h, 00h
    db 00h, 66h, 81h, 0FAh, 5Bh, 0Eh, 77h, 79h, 8Bh, 46h, 48h, 8Bh, 0Dh, 0ACh, 0AEh, 34h
    db 01h, 53h, 8Bh, 1Dh, 0FCh, 90h, 35h, 01h, 55h, 57h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 00h, 00h, 8Bh, 79h, 10h, 50h, 57h, 0FFh, 0D3h, 8Bh, 0Dh, 0ACh, 0AEh, 34h, 01h, 6Ah
    db 01h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 51h, 10h, 8Bh, 0E8h, 6Ah, 01h, 8Dh, 44h, 24h
    db 24h, 50h, 52h, 0FFh, 15h, 0D8h, 90h, 35h, 01h, 55h, 57h, 0FFh, 0D3h, 8Bh, 44h, 24h
    db 10h, 66h, 3Dh, 0FFh, 0FFh, 5Fh, 5Dh, 5Bh, 74h, 0Dh, 50h, 8Bh, 0CEh, 0E8h, 1Eh, 0FFh
    db 0FFh, 0FFh, 5Eh, 59h, 0C2h, 04h, 00h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 0Fh, 8Bh, 44h
    db 24h, 0Ch, 50h, 0E8h, 68h, 0FFh, 0FFh, 0FFh, 5Eh, 59h, 0C2h, 04h, 00h, 8Bh, 54h, 24h
    db 0Ch, 66h, 81h, 0FAh, 00h, 01h, 73h, 09h, 0Fh, 0B7h, 0CAh, 8Bh, 44h, 8Eh, 4Ch, 0EBh
    db 21h, 52h, 8Bh, 0CEh, 0E8h, 77h, 0BFh, 0FFh, 0FFh, 8Bh, 54h, 24h, 0Ch, 0Fh, 0B7h, 86h
    db 5Ch, 04h, 00h, 00h, 0Fh, 0B7h, 0CAh, 2Bh, 0C8h, 8Bh, 86h, 4Ch, 04h, 00h, 00h, 8Bh
    db 04h, 88h, 85h, 0C0h, 75h, 0Ch, 52h, 8Bh, 0CEh, 0E8h, 72h, 0E0h, 0FFh, 0FFh, 8Bh, 54h
    db 24h, 0Ch, 83h, 0F8h, 0FFh, 75h, 18h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 0Fh, 3Bh, 0F1h
    db 74h, 0Bh, 52h, 0E8h, 08h, 0FFh, 0FFh, 0FFh, 5Eh, 59h, 0C2h, 04h, 00h, 33h, 0C0h, 5Eh
    db 59h, 0C2h, 04h, 00h
?d_009412f0@@YAXXZ ENDP

; ghidra: FUN_00d41930  retail @ 0x00941930 size 198
public ?d_00941930@@YAXXZ
?d_00941930@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 14h, 55h, 8Bh, 0E9h, 8Bh, 45h, 4Ch, 0DBh, 40h
    db 2Ch, 56h, 33h, 0F6h, 66h, 8Bh, 33h, 66h, 85h, 0F6h, 0D9h, 5Ch, 24h, 10h, 0C7h, 44h
    db 24h, 0Ch, 00h, 00h, 00h, 00h, 0Fh, 84h, 80h, 00h, 00h, 00h, 57h, 8Dh, 49h, 00h
    db 83h, 0C3h, 02h, 66h, 83h, 0FEh, 0Ah, 74h, 6Ah, 8Bh, 7Dh, 4Ch, 56h, 8Bh, 0CFh, 0E8h
    db 7Ch, 0F9h, 0FFh, 0FFh, 85h, 0C0h, 74h, 47h, 66h, 8Bh, 48h, 02h, 66h, 85h, 0C9h, 74h
    db 3Eh, 66h, 81h, 0FEh, 01h, 0Eh, 72h, 07h, 66h, 81h, 0FEh, 3Ah, 0Eh, 76h, 0Eh, 66h
    db 81h, 0FEh, 3Fh, 0Eh, 72h, 16h, 66h, 81h, 0FEh, 5Bh, 0Eh, 77h, 0Fh, 0Fh, 0BFh, 50h
    db 04h, 0Fh, 0BFh, 0C1h, 03h, 0D0h, 89h, 54h, 24h, 20h, 0EBh, 1Bh, 8Bh, 57h, 38h, 8Bh
    db 47h, 34h, 0Fh, 0BFh, 0C9h, 2Bh, 0CAh, 2Bh, 0C8h, 89h, 4Ch, 24h, 20h, 0EBh, 08h, 0C7h
    db 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0DBh, 44h, 24h, 20h, 0D8h, 44h, 24h, 10h, 0D9h
    db 5Ch, 24h, 10h, 66h, 8Bh, 33h, 66h, 85h, 0F6h, 75h, 85h, 5Fh, 8Bh, 44h, 24h, 18h
    db 0D9h, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 0D9h, 18h, 5Eh, 5Dh, 89h, 50h, 04h, 5Bh
    db 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_00941930@@YAXXZ ENDP

; ghidra: FUN_00d41a00  retail @ 0x00941A00 size 597
public ?d_00941a00@@YAXXZ
?d_00941a00@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 58h, 0D9h, 05h, 01h, 50h, 8Ah, 44h
    db 24h, 14h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 24h, 84h, 0C0h, 53h, 56h
    db 57h, 8Bh, 0D9h, 75h, 1Ch, 8Bh, 83h, 0B0h, 00h, 00h, 00h, 85h, 0C0h, 74h, 12h, 8Dh
    db 4Bh, 7Ch, 0E8h, 99h, 0ADh, 0FBh, 0FFh, 0C7h, 83h, 0B0h, 00h, 00h, 00h, 00h, 00h, 00h
    db 00h, 8Bh, 44h, 24h, 40h, 66h, 83h, 38h, 00h, 55h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 6Dh, 8Bh, 0E8h, 8Bh, 7Bh, 4Ch, 33h, 0F6h, 66h, 8Bh, 30h, 8Bh, 0CFh
    db 56h, 0E8h, 8Ah, 0F8h, 0FFh, 0FFh, 85h, 0C0h, 74h, 3Fh, 66h, 8Bh, 48h, 02h, 66h, 85h
    db 0C9h, 74h, 36h, 66h, 81h, 0FEh, 01h, 0Eh, 72h, 07h, 66h, 81h, 0FEh, 3Ah, 0Eh, 76h
    db 0Eh, 66h, 81h, 0FEh, 3Fh, 0Eh, 72h, 12h, 66h, 81h, 0FEh, 5Bh, 0Eh, 77h, 0Bh, 0Fh
    db 0BFh, 40h, 04h, 0Fh, 0BFh, 0C9h, 03h, 0C1h, 0EBh, 11h, 8Bh, 57h, 38h, 0Fh, 0BFh, 0C1h
    db 8Bh, 4Fh, 34h, 2Bh, 0C2h, 2Bh, 0C1h, 0EBh, 02h, 33h, 0C0h, 8Bh, 74h, 24h, 10h, 03h
    db 0F0h, 83h, 0C5h, 02h, 66h, 83h, 7Dh, 00h, 00h, 89h, 74h, 24h, 10h, 8Bh, 0C5h, 75h
    db 95h, 8Bh, 53h, 4Ch, 8Bh, 42h, 2Ch, 40h, 0C7h, 43h, 74h, 00h, 01h, 00h, 00h, 0C7h
    db 44h, 24h, 44h, 0FFh, 0C9h, 9Ah, 3Bh, 0B9h, 06h, 00h, 00h, 00h, 89h, 44h, 24h, 14h
    db 8Bh, 44h, 24h, 10h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 99h, 0F7h, 0FEh, 8Bh, 0F8h
    db 8Bh, 0C6h, 99h, 0F7h, 7Ch, 24h, 14h, 47h, 8Bh, 0E8h, 85h, 0EDh, 7Eh, 24h, 8Bh, 0C7h
    db 99h, 0F7h, 0FDh, 83h, 0F8h, 01h, 7Fh, 05h, 0B8h, 01h, 00h, 00h, 00h, 8Bh, 54h, 24h
    db 44h, 0Fh, 0AFh, 0C6h, 0Fh, 0AFh, 0C6h, 3Bh, 0C2h, 7Dh, 07h, 89h, 73h, 74h, 89h, 44h
    db 24h, 44h, 41h, 83h, 0F9h, 08h, 7Eh, 0B8h, 8Bh, 43h, 74h, 8Bh, 4Bh, 78h, 3Bh, 0C8h
    db 5Dh, 7Eh, 02h, 8Bh, 0C1h, 89h, 43h, 74h, 8Ah, 44h, 24h, 44h, 33h, 0F6h, 84h, 0C0h
    db 0Fh, 85h, 0F2h, 00h, 00h, 00h, 8Bh, 43h, 7Ch, 3Bh, 0C6h, 74h, 09h, 8Bh, 08h, 50h
    db 0FFh, 51h, 08h, 89h, 73h, 7Ch, 8Bh, 43h, 74h, 6Ah, 02h, 6Ah, 15h, 50h, 50h, 8Dh
    db 4Ch, 24h, 54h, 0E8h, 0F8h, 0A9h, 0FBh, 0FFh, 8Bh, 0F8h, 8Bh, 07h, 3Bh, 0C6h, 89h, 74h
    db 24h, 38h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 04h, 8Bh, 43h, 7Ch, 3Bh, 0C6h, 74h
    db 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 17h, 83h, 0CFh, 0FFh, 8Dh, 4Ch, 24h, 44h
    db 89h, 53h, 7Ch, 89h, 7Ch, 24h, 38h, 0E8h, 14h, 0AAh, 0FBh, 0FFh, 89h, 74h, 24h, 14h
    db 89h, 74h, 24h, 1Ch, 89h, 74h, 24h, 20h, 0C6h, 44h, 24h, 24h, 01h, 0C6h, 44h, 24h
    db 25h, 00h, 0C7h, 44h, 24h, 18h, 0F4h, 0CDh, 13h, 01h, 0C7h, 44h, 24h, 2Ch, 0Ah, 00h
    db 00h, 00h, 89h, 74h, 24h, 28h, 8Bh, 43h, 7Ch, 3Bh, 0C6h, 0C7h, 44h, 24h, 38h, 02h
    db 00h, 00h, 00h, 74h, 14h, 8Bh, 08h, 50h, 0FFh, 51h, 04h, 8Bh, 44h, 24h, 14h, 3Bh
    db 0C6h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 8Bh, 43h, 7Ch, 8Dh, 4Ch, 24h, 14h
    db 51h, 8Dh, 4Bh, 1Ch, 89h, 44h, 24h, 18h, 0E8h, 83h, 0DFh, 0FFh, 0FFh, 8Bh, 44h, 24h
    db 1Ch, 3Bh, 0C6h, 89h, 7Ch, 24h, 38h, 0C7h, 44h, 24h, 18h, 5Ch, 38h, 07h, 01h, 74h
    db 15h, 8Ah, 4Ch, 24h, 25h, 84h, 0C9h, 74h, 0Dh, 50h, 0E8h, 0D1h, 02h, 0F4h, 0FFh, 83h
    db 0C4h, 04h, 89h, 74h, 24h, 1Ch, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 25h, 00h, 89h
    db 74h, 24h, 20h, 0E8h, 78h, 0A9h, 0FBh, 0FFh, 8Bh, 4Ch, 24h, 30h, 89h, 73h, 68h, 89h
    db 73h, 6Ch, 89h, 73h, 70h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 30h, 0C2h, 08h, 00h
?d_00941a00@@YAXXZ ENDP

; ghidra: FUN_00d42bc0  retail @ 0x00942BC0 size 40
public ?d_00942bc0@@YAXXZ
?d_00942bc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 08h, 85h, 0C0h, 74h, 17h, 8Bh, 54h, 24h, 14h, 6Ah
    db 00h, 52h, 8Bh, 54h, 24h, 18h, 52h, 50h, 8Dh, 44h, 24h, 10h, 50h, 0E8h, 4Eh, 0F8h
    db 0FFh, 0FFh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_00942bc0@@YAXXZ ENDP

; ghidra: FUN_00d42f20  retail @ 0x00942F20 size 16
public ?d_00942f20@@YAXXZ
?d_00942f20@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0C8h, 0EEh, 0FEh, 0FFh, 8Dh, 86h, 94h, 01h, 00h, 00h, 5Eh, 0C3h
?d_00942f20@@YAXXZ ENDP

; ghidra: FUN_00d431f0  retail @ 0x009431F0 size 88
public ?d_009431f0@@YAXXZ
?d_009431f0@@YAXXZ PROC
    db 51h, 0D9h, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 0D8h, 26h, 8Bh, 46h, 24h, 85h, 0C0h, 0D8h
    db 4Eh, 20h, 0DBh, 46h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0DEh, 0C9h, 83h
    db 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 0D9h, 5Ch, 24h, 14h, 83h
    db 0C4h, 08h, 0D9h, 44h, 24h, 0Ch, 0DBh, 5Ch, 24h, 04h, 8Bh, 44h, 24h, 04h, 85h, 0C0h
    db 7Dh, 07h, 33h, 0C0h, 5Eh, 59h, 0C2h, 04h, 00h, 8Bh, 76h, 24h, 3Bh, 0C6h, 72h, 03h
    db 8Dh, 46h, 0FFh, 5Eh, 59h, 0C2h, 04h, 00h
?d_009431f0@@YAXXZ ENDP

; ghidra: FUN_00d43250  retail @ 0x00943250 size 89
public ?d_00943250@@YAXXZ
?d_00943250@@YAXXZ PROC
    db 51h, 0D9h, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 0D8h, 66h, 04h, 8Bh, 46h, 24h, 85h, 0C0h
    db 0D8h, 4Eh, 20h, 0DBh, 46h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0DEh, 0C9h
    db 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h, 01h, 0D9h, 5Ch, 24h, 14h
    db 83h, 0C4h, 08h, 0D9h, 44h, 24h, 0Ch, 0DBh, 5Ch, 24h, 04h, 8Bh, 44h, 24h, 04h, 85h
    db 0C0h, 7Dh, 07h, 33h, 0C0h, 5Eh, 59h, 0C2h, 04h, 00h, 8Bh, 76h, 24h, 3Bh, 0C6h, 72h
    db 03h, 8Dh, 46h, 0FFh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00943250@@YAXXZ ENDP

; ghidra: FUN_00d432b0  retail @ 0x009432B0 size 240
public ?d_009432b0@@YAXXZ
?d_009432b0@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 53h, 55h, 56h, 8Bh, 74h, 24h, 2Ch, 8Bh, 46h, 24h, 8Bh, 16h, 57h
    db 8Bh, 0F9h, 8Bh, 4Eh, 34h, 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 1Ch, 89h, 4Ch, 24h
    db 14h, 50h, 8Bh, 0CEh, 0FFh, 92h, 08h, 01h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h
    db 18h, 01h, 00h, 00h, 0D8h, 44h, 24h, 28h, 51h, 8Bh, 0CFh, 0D9h, 5Ch, 24h, 34h, 0D9h
    db 44h, 24h, 14h, 0D8h, 64h, 24h, 34h, 0D9h, 1Ch, 24h, 0E8h, 0F1h, 0FEh, 0FFh, 0FFh, 0D9h
    db 44h, 24h, 14h, 8Bh, 5Ch, 24h, 34h, 0D8h, 64h, 24h, 30h, 51h, 8Bh, 0CFh, 89h, 03h
    db 0D9h, 1Ch, 24h, 0E8h, 38h, 0FFh, 0FFh, 0FFh, 0D9h, 44h, 24h, 14h, 8Bh, 6Ch, 24h, 38h
    db 0D8h, 44h, 24h, 30h, 51h, 8Bh, 0CFh, 89h, 45h, 00h, 0D9h, 1Ch, 24h, 0E8h, 1Eh, 0FFh
    db 0FFh, 0FFh, 8Bh, 4Dh, 00h, 0D9h, 44h, 24h, 10h, 0D8h, 44h, 24h, 30h, 8Bh, 0F0h, 51h
    db 33h, 0F1h, 8Bh, 0CFh, 0D9h, 1Ch, 24h, 0E8h, 0A4h, 0FEh, 0FFh, 0FFh, 33h, 03h, 0Bh, 0F0h
    db 8Bh, 44h, 24h, 3Ch, 89h, 30h, 74h, 3Eh, 8Bh, 0C6h, 33h, 0C9h, 0F6h, 0C4h, 0FFh, 74h
    db 08h, 0C1h, 0E8h, 08h, 0B9h, 08h, 00h, 00h, 00h, 0A8h, 0F0h, 74h, 06h, 0C1h, 0E8h, 04h
    db 83h, 0C9h, 04h, 0A8h, 0Ch, 74h, 06h, 0C1h, 0E8h, 02h, 83h, 0C9h, 02h, 0A8h, 02h, 74h
    db 03h, 83h, 0C9h, 01h, 8Bh, 13h, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 0F7h, 0D0h, 23h
    db 0D0h, 89h, 13h, 21h, 45h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 1Ch, 0C2h, 10h, 00h
?d_009432b0@@YAXXZ ENDP

; ghidra: FUN_00d433a0  retail @ 0x009433A0 size 135
public ?d_009433a0@@YAXXZ
?d_009433a0@@YAXXZ PROC
    db 8Bh, 41h, 1Ch, 8Bh, 51h, 24h, 53h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Bh, 71h, 18h
    db 0C1h, 0E8h, 02h, 0D1h, 0EAh, 85h, 0C0h, 57h, 8Bh, 7Ch, 24h, 18h, 74h, 34h, 8Bh, 0FFh
    db 85h, 0D5h, 75h, 2Eh, 0FFh, 06h, 8Bh, 0CAh, 23h, 0CFh, 0F7h, 0D9h, 1Bh, 0C9h, 8Bh, 0DAh
    db 23h, 5Ch, 24h, 1Ch, 0F7h, 0D9h, 0F7h, 0DBh, 1Bh, 0DBh, 83h, 0E3h, 02h, 03h, 0CBh, 0Fh
    db 0AFh, 0C8h, 6Bh, 0C9h, 1Ch, 0C1h, 0E8h, 02h, 0D1h, 0EAh, 85h, 0C0h, 8Dh, 74h, 0Eh, 1Ch
    db 75h, 0CEh, 8Bh, 5Ch, 24h, 14h, 85h, 0DBh, 74h, 05h, 8Dh, 43h, 08h, 0EBh, 02h, 33h
    db 0C0h, 6Ah, 00h, 50h, 8Dh, 4Eh, 04h, 0E8h, 54h, 8Bh, 09h, 00h, 8Bh, 54h, 24h, 1Ch
    db 0C1h, 0E7h, 0Ah, 0Bh, 0FAh, 0C1h, 0E7h, 0Ah, 0Bh, 0FDh, 89h, 0BBh, 94h, 00h, 00h, 00h
    db 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 10h, 00h
?d_009433a0@@YAXXZ ENDP

; ghidra: FUN_00d43430  retail @ 0x00943430 size 166
public ?d_00943430@@YAXXZ
?d_00943430@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 8Bh, 80h, 94h, 00h, 00h, 00h, 53h, 56h, 8Bh, 0D0h, 57h
    db 0C1h, 0FAh, 0Ah, 8Bh, 0F8h, 8Bh, 0DAh, 0C1h, 0FFh, 14h, 81h, 0E3h, 0FFh, 03h, 00h, 80h
    db 79h, 08h, 4Bh, 81h, 0CBh, 00h, 0FCh, 0FFh, 0FFh, 43h, 25h, 0FFh, 03h, 00h, 80h, 79h
    db 07h, 48h, 0Dh, 00h, 0FCh, 0FFh, 0FFh, 40h, 8Bh, 51h, 24h, 8Bh, 71h, 18h, 89h, 44h
    db 24h, 0Ch, 8Bh, 41h, 1Ch, 0C1h, 0E8h, 02h, 0D1h, 0EAh, 85h, 0C0h, 74h, 37h, 55h, 90h
    db 8Bh, 4Ch, 24h, 10h, 85h, 0D1h, 75h, 2Ch, 0FFh, 0Eh, 8Bh, 0CAh, 23h, 0CBh, 0F7h, 0D9h
    db 1Bh, 0C9h, 83h, 0E1h, 02h, 8Bh, 0EAh, 23h, 0EFh, 0F7h, 0DDh, 1Bh, 0EDh, 0F7h, 0DDh, 03h
    db 0CDh, 0Fh, 0AFh, 0C8h, 6Bh, 0C9h, 1Ch, 0C1h, 0E8h, 02h, 0D1h, 0EAh, 85h, 0C0h, 8Dh, 74h
    db 0Eh, 1Ch, 75h, 0CCh, 5Dh, 8Bh, 7Ch, 24h, 14h, 8Dh, 57h, 08h, 52h, 8Dh, 4Eh, 04h
    db 0E8h, 3Bh, 8Ch, 09h, 00h, 0C7h, 87h, 94h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 5Fh
    db 5Eh, 5Bh, 59h, 0C2h, 04h, 00h
?d_00943430@@YAXXZ ENDP

; ghidra: FUN_00d434e0  retail @ 0x009434E0 size 105
public ?d_009434e0@@YAXXZ
?d_009434e0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 0F1h, 8Dh, 44h, 24h
    db 10h, 50h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 54h, 24h, 24h, 52h, 57h, 8Bh, 0CEh, 0E8h
    db 0ACh, 0FDh, 0FFh, 0FFh, 8Bh, 87h, 94h, 00h, 00h, 00h, 85h, 0C0h, 8Bh, 5Ch, 24h, 10h
    db 8Bh, 6Ch, 24h, 14h, 7Ch, 1Ah, 8Bh, 4Ch, 24h, 1Ch, 0C1h, 0E1h, 0Ah, 0Bh, 0CDh, 0C1h
    db 0E1h, 0Ah, 0Bh, 0CBh, 3Bh, 0C8h, 74h, 17h, 57h, 8Bh, 0CEh, 0E8h, 00h, 0FFh, 0FFh, 0FFh
    db 8Bh, 54h, 24h, 1Ch, 53h, 55h, 52h, 57h, 8Bh, 0CEh, 0E8h, 61h, 0FEh, 0FFh, 0FFh, 5Fh
    db 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_009434e0@@YAXXZ ENDP

; ghidra: FUN_00d436c0  retail @ 0x009436C0 size 458
public ?d_009436c0@@YAXXZ
?d_009436c0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 53h, 56h, 8Bh, 0F1h, 8Bh, 4Dh, 08h, 8Bh, 06h, 57h
    db 51h, 8Bh, 0CEh, 89h, 75h, 0E4h, 0FFh, 50h, 60h, 8Bh, 56h, 30h, 8Bh, 46h, 2Ch, 89h
    db 55h, 0E8h, 8Ah, 56h, 1Ch, 8Dh, 4Eh, 20h, 89h, 45h, 0ECh, 89h, 4Dh, 0F4h, 88h, 15h
    db 28h, 05h, 34h, 01h, 0C7h, 45h, 0FCh, 00h, 00h, 00h, 00h, 0C7h, 45h, 0F8h, 00h, 00h
    db 7Fh, 43h, 83h, 0ECh, 14h, 9Bh, 9Bh, 0D9h, 7Ch, 24h, 10h, 8Bh, 44h, 24h, 10h, 8Bh
    db 0F8h, 25h, 0FFh, 0F3h, 0FFh, 0FFh, 0Dh, 00h, 0Ch, 00h, 00h, 2Bh, 0F8h, 74h, 06h, 89h
    db 04h, 24h, 0D9h, 2Ch, 24h, 8Bh, 75h, 0F4h, 0D9h, 45h, 0F8h, 0D9h, 06h, 0D9h, 46h, 04h
    db 0D9h, 46h, 08h, 0D9h, 45h, 0FCh, 0D9h, 0C4h, 0DCh, 0CCh, 0DCh, 0CBh, 0DCh, 0CAh, 0DEh, 0C9h
    db 0DBh, 1Ch, 24h, 0DBh, 5Ch, 24h, 04h, 0DBh, 5Ch, 24h, 08h, 0DBh, 5Ch, 24h, 0Ch, 8Bh
    db 0Ch, 24h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 08h, 8Bh, 5Ch, 24h, 0Ch, 0C1h, 0E1h
    db 18h, 0C1h, 0E3h, 10h, 0C1h, 0E2h, 08h, 0Bh, 0C1h, 0Bh, 0C3h, 0Bh, 0C2h, 0DDh, 0D8h, 83h
    db 0FFh, 00h, 74h, 05h, 9Bh, 0D9h, 6Ch, 24h, 10h, 83h, 0C4h, 14h, 89h, 45h, 0F0h, 8Bh
    db 4Dh, 0ECh, 8Bh, 45h, 0F0h, 51h, 6Ah, 24h, 0A3h, 2Ch, 05h, 34h, 01h, 0C6h, 05h, 0FCh
    db 6Dh, 2Dh, 01h, 01h, 0E8h, 85h, 0FAh, 6Ch, 0FFh, 8Bh, 55h, 0E8h, 52h, 6Ah, 25h, 0E8h
    db 7Ah, 0FAh, 6Ch, 0FFh, 8Bh, 75h, 0E4h, 8Bh, 46h, 18h, 83h, 0C4h, 10h, 85h, 0C0h, 75h
    db 1Fh, 8Bh, 4Dh, 08h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 5Ch, 8Bh, 45h, 08h, 8Bh
    db 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 64h, 5Fh, 5Eh, 5Bh, 8Bh, 0E5h, 5Dh, 0C2h, 04h, 00h
    db 8Ah, 15h, 90h, 6Dh, 2Dh, 01h, 6Ah, 00h, 88h, 55h, 0E4h, 0E8h, 0D0h, 22h, 0FCh, 0FFh
    db 8Bh, 7Dh, 08h, 8Bh, 06h, 83h, 0C4h, 04h, 57h, 8Bh, 0CEh, 0FFh, 50h, 5Ch, 8Bh, 46h
    db 18h, 48h, 74h, 54h, 48h, 75h, 73h, 6Ah, 00h, 68h, 00h, 00h, 80h, 3Fh, 6Ah, 00h
    db 8Dh, 4Dh, 0D8h, 51h, 6Ah, 00h, 6Ah, 00h, 6Ah, 01h, 0C7h, 45h, 0D8h, 00h, 00h, 00h
    db 00h, 0C7h, 45h, 0DCh, 00h, 00h, 00h, 00h, 0C7h, 45h, 0E0h, 00h, 00h, 00h, 00h, 0E8h
    db 2Ch, 0Ah, 0FCh, 0FFh, 6Ah, 00h, 0E8h, 0E5h, 9Bh, 0FBh, 0FFh, 6Ah, 02h, 6Ah, 08h, 0E8h
    db 0EAh, 0F9h, 6Ch, 0FFh, 6Ah, 07h, 0E8h, 75h, 22h, 0FCh, 0FFh, 8Bh, 16h, 83h, 0C4h, 2Ch
    db 57h, 8Bh, 0CEh, 0FFh, 52h, 5Ch, 0EBh, 22h, 6Ah, 00h, 0E8h, 0C1h, 9Bh, 0FBh, 0FFh, 6Ah
    db 02h, 6Ah, 08h, 0E8h, 0C6h, 0F9h, 6Ch, 0FFh, 6Ah, 07h, 0E8h, 51h, 22h, 0FCh, 0FFh, 8Bh
    db 06h, 83h, 0C4h, 10h, 57h, 8Bh, 0CEh, 0FFh, 50h, 5Ch, 8Bh, 4Dh, 0E4h, 51h, 0E8h, 9Dh
    db 9Bh, 0FBh, 0FFh, 8Bh, 45h, 08h, 8Bh, 16h, 83h, 0C4h, 04h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 64h, 5Fh, 5Eh, 5Bh, 8Bh, 0E5h, 5Dh, 0C2h, 04h, 00h
?d_009436c0@@YAXXZ ENDP

; ghidra: FUN_00d43890  retail @ 0x00943890 size 39
public ?d_00943890@@YAXXZ
?d_00943890@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Dh, 7Eh, 60h, 8Bh, 46h, 64h, 3Bh, 0C7h, 74h, 16h, 8Bh, 40h
    db 0Ch, 85h, 0C0h, 74h, 0Fh, 83h, 0C0h, 0F8h, 74h, 0Ah, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 0Ch, 0EBh, 0E3h, 5Fh, 5Eh, 0C3h
?d_00943890@@YAXXZ ENDP

; ghidra: FUN_00d43970  retail @ 0x00943970 size 8
public ?d_00943970@@YAXXZ
?d_00943970@@YAXXZ PROC
    db 83h, 0C1h, 04h, 0E9h, 28h, 0FCh, 0FFh, 0FFh
?d_00943970@@YAXXZ ENDP

; ghidra: FUN_00d43ad0  retail @ 0x00943AD0 size 388
public ?d_00943ad0@@YAXXZ
?d_00943ad0@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 0BEh, 0D9h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 6Ch, 24h, 24h, 56h, 8Bh
    db 0D9h, 8Bh, 4Dh, 00h, 8Bh, 03h, 57h, 51h, 8Bh, 0CBh, 0FFh, 50h, 6Ch, 8Bh, 73h, 7Ch
    db 8Dh, 7Bh, 78h, 3Bh, 0F7h, 74h, 1Ah, 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 05h, 8Dh, 48h
    db 0F8h, 0EBh, 02h, 33h, 0C9h, 8Bh, 11h, 0FFh, 52h, 34h, 8Bh, 76h, 04h, 3Bh, 0F7h, 75h
    db 0E6h, 6Ah, 00h, 6Ah, 00h, 0E8h, 0D6h, 0E9h, 0FBh, 0FFh, 6Ah, 00h, 6Ah, 01h, 0E8h, 0CDh
    db 0E9h, 0FBh, 0FFh, 6Ah, 00h, 6Ah, 02h, 0E8h, 0C4h, 0E9h, 0FBh, 0FFh, 6Ah, 00h, 6Ah, 03h
    db 0E8h, 0BBh, 0E9h, 0FBh, 0FFh, 8Bh, 45h, 1Ch, 83h, 0C4h, 20h, 85h, 0C0h, 0Fh, 85h, 0B1h
    db 00h, 00h, 00h, 0F6h, 05h, 0E0h, 0B0h, 34h, 01h, 01h, 75h, 2Eh, 83h, 0Dh, 0E0h, 0B0h
    db 34h, 01h, 01h, 0B9h, 0B8h, 0AEh, 34h, 01h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h
    db 0E8h, 7Bh, 6Fh, 00h, 00h, 68h, 40h, 13h, 07h, 01h, 0E8h, 0A7h, 32h, 0Bh, 00h, 83h
    db 0C4h, 04h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 8Dh, 43h, 08h, 50h, 8Dh, 4Ch
    db 24h, 14h, 51h, 0B9h, 0B8h, 0AEh, 34h, 01h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h
    db 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h
    db 0E8h, 0BBh, 70h, 00h, 00h, 8Bh, 0B3h, 94h, 00h, 00h, 00h, 8Dh, 0BBh, 90h, 00h, 00h
    db 00h, 3Bh, 0F7h, 74h, 20h, 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 0F8h, 0EBh
    db 02h, 33h, 0C0h, 50h, 0B9h, 0B8h, 0AEh, 34h, 01h, 0E8h, 0C2h, 7Ch, 00h, 00h, 8Bh, 76h
    db 04h, 3Bh, 0F7h, 75h, 0E0h, 8Bh, 75h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 50h, 83h
    db 0C6h, 18h, 56h, 0B9h, 0B8h, 0AEh, 34h, 01h, 0E8h, 43h, 7Fh, 00h, 00h, 0C7h, 45h, 1Ch
    db 0B8h, 0AEh, 34h, 01h, 8Bh, 0BBh, 0F4h, 00h, 00h, 00h, 81h, 0C3h, 0F0h, 00h, 00h, 00h
    db 3Bh, 0FBh, 74h, 2Bh, 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 05h, 8Dh, 70h, 0F8h, 0EBh, 02h
    db 33h, 0F6h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 7Ch, 01h, 00h, 00h, 85h, 0C0h, 74h, 08h
    db 8Bh, 16h, 55h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh, 7Fh, 04h, 3Bh, 0FBh, 75h, 0D5h, 8Bh
    db 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 18h, 0C2h, 04h, 00h
?d_00943ad0@@YAXXZ ENDP

; ghidra: FUN_00d43cf0  retail @ 0x00943CF0 size 82
public ?d_00943cf0@@YAXXZ
?d_00943cf0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 30h, 85h, 0F6h, 8Bh, 0D9h, 74h
    db 39h, 57h, 8Bh, 7Eh, 04h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 54h, 24h, 10h, 52h, 8Dh
    db 44h, 24h, 18h, 50h, 57h, 8Bh, 0CBh, 0E8h, 94h, 0F5h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 18h
    db 8Bh, 54h, 24h, 0Ch, 8Bh, 44h, 24h, 10h, 51h, 52h, 50h, 57h, 8Bh, 0CBh, 0E8h, 6Dh
    db 0F6h, 0FFh, 0FFh, 8Bh, 36h, 85h, 0F6h, 75h, 0C9h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 08h, 0C2h
    db 04h, 00h
?d_00943cf0@@YAXXZ ENDP

; ghidra: FUN_00d43f70  retail @ 0x00943F70 size 124
public ?d_00943f70@@YAXXZ
?d_00943f70@@YAXXZ PROC
    db 51h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 1Ch, 85h, 0C9h, 8Bh, 47h, 18h, 0C7h, 44h, 24h, 04h
    db 00h, 00h, 00h, 00h, 7Eh, 61h, 53h, 8Bh, 5Ch, 24h, 10h, 55h, 56h, 8Dh, 68h, 0Ch
    db 8Bh, 45h, 00h, 8Dh, 4Dh, 0FCh, 3Bh, 0C1h, 74h, 37h, 8Bh, 40h, 0Ch, 85h, 0C0h, 74h
    db 30h, 8Dh, 70h, 0F8h, 85h, 0F6h, 74h, 29h, 6Ah, 08h, 0E8h, 91h, 0A5h, 0EEh, 0FFh, 8Dh
    db 48h, 04h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 02h, 89h, 31h, 0C7h, 00h, 00h, 00h, 00h
    db 00h, 8Bh, 13h, 89h, 10h, 56h, 8Bh, 0CFh, 89h, 03h, 0E8h, 61h, 0F4h, 0FFh, 0FFh, 0EBh
    db 0BFh, 8Bh, 44h, 24h, 10h, 8Bh, 4Fh, 1Ch, 40h, 83h, 0C5h, 1Ch, 3Bh, 0C1h, 89h, 44h
    db 24h, 10h, 7Ch, 0ACh, 5Eh, 5Dh, 5Bh, 5Fh, 59h, 0C2h, 04h, 00h
?d_00943f70@@YAXXZ ENDP

; ghidra: FUN_00d43ff0  retail @ 0x00943FF0 size 201
public ?d_00943ff0@@YAXXZ
?d_00943ff0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0DAh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h
    db 00h, 8Dh, 44h, 24h, 04h, 50h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0E8h, 4Dh
    db 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 18h, 8Bh, 01h, 8Bh, 0D6h, 89h, 02h, 8Bh, 41h, 04h
    db 89h, 42h, 04h, 8Bh, 41h, 08h, 89h, 42h, 08h, 8Bh, 41h, 0Ch, 89h, 42h, 0Ch, 8Bh
    db 41h, 10h, 89h, 42h, 10h, 8Bh, 49h, 14h, 89h, 4Ah, 14h, 0D9h, 46h, 0Ch, 0D8h, 26h
    db 0D9h, 46h, 10h, 0D8h, 66h, 04h, 0D9h, 5Ch, 24h, 18h, 0D8h, 54h, 24h, 18h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 74h, 06h, 0DDh, 0D8h, 0D9h, 44h, 24h, 18h, 0D9h, 05h, 34h, 53h, 07h
    db 01h, 8Dh, 54h, 24h, 04h, 0D8h, 0F1h, 52h, 8Bh, 0CEh, 0D9h, 5Eh, 20h, 0DDh, 0D8h, 0E8h
    db 6Ch, 0FCh, 0FFh, 0FFh, 8Bh, 74h, 24h, 04h, 85h, 0F6h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 74h, 13h, 8Bh, 0C6h, 8Bh, 36h, 6Ah, 08h, 50h, 0E8h, 50h, 0A5h, 0EEh, 0FFh
    db 83h, 0C4h, 08h, 85h, 0F6h, 75h, 0EDh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00943ff0@@YAXXZ ENDP

; ghidra: FUN_00d440c0  retail @ 0x009440C0 size 262
public ?d_009440c0@@YAXXZ
?d_009440c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 83h, 0DAh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 57h, 8Bh, 0F9h, 8Bh, 4Ch, 24h, 18h, 83h, 0F9h, 0Ah
    db 0Fh, 87h, 0CEh, 00h, 00h, 00h, 8Bh, 57h, 24h, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h
    db 3Bh, 0C2h, 0Fh, 84h, 0BCh, 00h, 00h, 00h, 85h, 0C9h, 55h, 56h, 89h, 47h, 24h, 0BEh
    db 01h, 00h, 00h, 00h, 74h, 0Ah, 49h, 8Dh, 34h, 0B5h, 01h, 00h, 00h, 00h, 75h, 0F6h
    db 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 8Dh, 44h, 24h, 20h, 50h, 8Bh, 0CFh, 0C7h
    db 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 44h, 0FEh, 0FFh, 0FFh, 8Bh, 47h, 18h, 85h
    db 0C0h, 74h, 1Dh, 8Bh, 48h, 0FCh, 8Dh, 68h, 0FCh, 68h, 70h, 39h, 0D4h, 00h, 51h, 6Ah
    db 1Ch, 50h, 0E8h, 2Fh, 2Ch, 0Bh, 00h, 55h, 0E8h, 0A3h, 0DDh, 0F3h, 0FFh, 83h, 0C4h, 04h
    db 8Bh, 0D6h, 6Bh, 0D2h, 1Ch, 83h, 0C2h, 04h, 52h, 89h, 77h, 1Ch, 0E8h, 0Fh, 0DEh, 0F3h
    db 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 85h, 0C0h, 0C6h, 44h, 24h, 18h, 01h, 74h
    db 1Ah, 68h, 70h, 39h, 0D4h, 00h, 68h, 50h, 36h, 0D4h, 00h, 56h, 8Dh, 68h, 04h, 6Ah
    db 1Ch, 55h, 89h, 30h, 0E8h, 5Bh, 2Dh, 0Bh, 00h, 0EBh, 02h, 33h, 0EDh, 8Dh, 44h, 24h
    db 20h, 50h, 8Bh, 0CFh, 0C6h, 44h, 24h, 1Ch, 00h, 89h, 6Fh, 18h, 0E8h, 4Fh, 0FBh, 0FFh
    db 0FFh, 8Dh, 4Ch, 24h, 20h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B4h, 0A6h
    db 6Eh, 0FFh, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 08h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_009440c0@@YAXXZ ENDP

; ghidra: FUN_00d441d0  retail @ 0x009441D0 size 392
public ?d_009441d0@@YAXXZ
?d_009441d0@@YAXXZ PROC
    db 51h, 53h, 8Bh, 5Ch, 24h, 30h, 55h, 8Bh, 6Ch, 24h, 14h, 56h, 8Bh, 74h, 24h, 1Ch
    db 57h, 89h, 4Ch, 24h, 10h, 8Bh, 4Dh, 0Ch, 8Dh, 45h, 08h, 3Bh, 0C8h, 74h, 52h, 8Bh
    db 0F9h, 8Dh, 45h, 08h, 3Bh, 0F8h, 74h, 49h, 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 09h, 83h
    db 0C0h, 0F8h, 89h, 44h, 24h, 3Ch, 0EBh, 08h, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 00h, 00h
    db 6Ah, 08h, 0E8h, 29h, 0A3h, 0EEh, 0FFh, 8Dh, 48h, 04h, 83h, 0C4h, 04h, 85h, 0C9h, 74h
    db 06h, 8Bh, 54h, 24h, 3Ch, 89h, 11h, 8Bh, 4Ch, 24h, 18h, 0C7h, 00h, 00h, 00h, 00h
    db 00h, 8Bh, 11h, 89h, 10h, 89h, 01h, 8Bh, 7Fh, 04h, 8Dh, 45h, 08h, 3Bh, 0F8h, 75h
    db 0B7h, 83h, 7Dh, 00h, 00h, 0Fh, 84h, 05h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 38h, 8Bh
    db 7Ch, 24h, 24h, 8Bh, 0C3h, 99h, 2Bh, 0C2h, 0D1h, 0F8h, 8Bh, 0D8h, 8Bh, 44h, 24h, 28h
    db 8Dh, 14h, 19h, 83h, 0C5h, 1Ch, 3Bh, 0C2h, 8Bh, 44h, 24h, 34h, 89h, 54h, 24h, 3Ch
    db 7Dh, 77h, 8Dh, 14h, 18h, 3Bh, 0FAh, 7Dh, 30h, 8Bh, 54h, 24h, 28h, 53h, 51h, 8Bh
    db 4Ch, 24h, 34h, 50h, 8Bh, 44h, 24h, 3Ch, 50h, 51h, 8Bh, 4Ch, 24h, 2Ch, 52h, 57h
    db 8Bh, 0C6h, 0C1h, 0E8h, 02h, 50h, 55h, 51h, 8Bh, 4Ch, 24h, 38h, 0E8h, 2Fh, 0FFh, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 38h, 8Bh, 44h, 24h, 34h, 8Dh, 14h, 18h, 39h, 54h, 24h, 2Ch
    db 7Ch, 33h, 8Bh, 44h, 24h, 2Ch, 53h, 51h, 8Bh, 4Ch, 24h, 30h, 52h, 8Bh, 54h, 24h
    db 3Ch, 52h, 50h, 8Bh, 0C6h, 6Bh, 0C0h, 1Ch, 51h, 8Bh, 4Ch, 24h, 30h, 57h, 8Bh, 0D6h
    db 0C1h, 0EAh, 02h, 52h, 03h, 0C5h, 50h, 51h, 8Bh, 4Ch, 24h, 38h, 0E8h, 0EFh, 0FEh, 0FFh
    db 0FFh, 8Bh, 44h, 24h, 34h, 8Bh, 54h, 24h, 3Ch, 39h, 54h, 24h, 30h, 7Ch, 61h, 8Dh
    db 0Ch, 18h, 3Bh, 0F9h, 89h, 4Ch, 24h, 34h, 7Dh, 37h, 8Bh, 4Ch, 24h, 28h, 53h, 52h
    db 8Bh, 54h, 24h, 38h, 50h, 8Bh, 44h, 24h, 38h, 52h, 50h, 8Bh, 0C6h, 6Bh, 0C0h, 38h
    db 51h, 8Bh, 4Ch, 24h, 30h, 57h, 8Bh, 0D6h, 0C1h, 0EAh, 02h, 52h, 03h, 0C5h, 50h, 51h
    db 8Bh, 4Ch, 24h, 38h, 0E8h, 0A7h, 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 34h, 8Bh, 54h, 24h
    db 3Ch, 39h, 4Ch, 24h, 2Ch, 7Ch, 19h, 8Bh, 0C6h, 6Bh, 0F6h, 54h, 0C1h, 0E8h, 02h, 03h
    db 0EEh, 89h, 54h, 24h, 38h, 89h, 4Ch, 24h, 34h, 8Bh, 0F0h, 0E9h, 95h, 0FEh, 0FFh, 0FFh
    db 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 28h, 00h
?d_009441d0@@YAXXZ ENDP

; ghidra: FUN_00d44360  retail @ 0x00944360 size 195
public ?d_00944360@@YAXXZ
?d_00944360@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 8Bh, 0F1h, 74h, 04h, 0D9h, 07h
    db 0EBh, 06h, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Bh, 5Ch, 24h, 18h, 0D9h, 03h, 51h, 0D8h
    db 0E1h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0DDh, 0D8h, 0E8h, 63h, 0EEh, 0FFh, 0FFh, 85h, 0FFh, 89h
    db 44h, 24h, 18h, 74h, 04h, 0D9h, 07h, 0EBh, 06h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D8h
    db 43h, 0Ch, 51h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0E8h, 43h, 0EEh, 0FFh, 0FFh, 85h, 0FFh, 89h
    db 44h, 24h, 1Ch, 74h, 05h, 0D9h, 47h, 04h, 0EBh, 06h, 0D9h, 05h, 50h, 53h, 07h, 01h
    db 0D9h, 43h, 04h, 51h, 0D8h, 0E1h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0DDh, 0D8h, 0E8h, 7Eh, 0EEh
    db 0FFh, 0FFh, 85h, 0FFh, 8Bh, 0E8h, 74h, 05h, 0D9h, 47h, 04h, 0EBh, 06h, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 0D8h, 43h, 10h, 51h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0E8h, 5Fh, 0EEh, 0FFh
    db 0FFh, 8Bh, 4Eh, 24h, 8Bh, 54h, 24h, 1Ch, 51h, 8Bh, 4Eh, 1Ch, 6Ah, 00h, 6Ah, 00h
    db 50h, 8Bh, 44h, 24h, 28h, 52h, 8Bh, 56h, 18h, 55h, 50h, 8Bh, 44h, 24h, 30h, 0C1h
    db 0E9h, 02h, 51h, 52h, 50h, 8Bh, 0CEh, 0E8h, 0B4h, 0FDh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh
    db 0C2h, 0Ch, 00h
?d_00944360@@YAXXZ ENDP

; ghidra: FUN_00d44430  retail @ 0x00944430 size 568
public ?d_00944430@@YAXXZ
?d_00944430@@YAXXZ PROC
    db 83h, 0ECh, 34h, 53h, 55h, 56h, 8Bh, 74h, 24h, 48h, 8Bh, 0E9h, 57h, 8Bh, 0CEh, 0E8h
    db 0ACh, 0D9h, 0FEh, 0FFh, 0D9h, 86h, 0A0h, 01h, 00h, 00h, 8Dh, 8Eh, 94h, 01h, 00h, 00h
    db 8Bh, 0C1h, 8Bh, 10h, 89h, 54h, 24h, 38h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 89h, 54h
    db 24h, 3Ch, 89h, 44h, 24h, 40h, 8Bh, 0D1h, 8Bh, 02h, 89h, 44h, 24h, 2Ch, 0D8h, 5Ch
    db 24h, 2Ch, 8Bh, 42h, 04h, 8Bh, 52h, 08h, 89h, 44h, 24h, 30h, 0DFh, 0E0h, 89h, 54h
    db 24h, 34h, 0F6h, 0C4h, 05h, 7Ah, 09h, 8Bh, 41h, 0Ch, 89h, 44h, 24h, 2Ch, 0EBh, 15h
    db 0D9h, 41h, 0Ch, 0D8h, 5Ch, 24h, 38h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 51h
    db 0Ch, 89h, 54h, 24h, 38h, 0D9h, 41h, 10h, 0D8h, 5Ch, 24h, 30h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 09h, 8Bh, 41h, 10h, 89h, 44h, 24h, 30h, 0EBh, 15h, 0D9h, 41h, 10h, 0D8h
    db 5Ch, 24h, 3Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 51h, 10h, 89h, 54h, 24h
    db 3Ch, 0D9h, 41h, 18h, 0D8h, 5Ch, 24h, 2Ch, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 09h, 8Bh
    db 41h, 18h, 89h, 44h, 24h, 2Ch, 0EBh, 15h, 0D9h, 41h, 18h, 0D8h, 5Ch, 24h, 38h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 51h, 18h, 89h, 54h, 24h, 38h, 0D9h, 41h, 1Ch
    db 0D8h, 5Ch, 24h, 30h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 09h, 8Bh, 41h, 1Ch, 89h, 44h
    db 24h, 30h, 0EBh, 15h, 0D9h, 41h, 1Ch, 0D8h, 5Ch, 24h, 3Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 07h, 8Bh, 51h, 1Ch, 89h, 54h, 24h, 3Ch, 0D9h, 41h, 24h, 0D8h, 5Ch, 24h, 2Ch
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 09h, 8Bh, 41h, 24h, 89h, 44h, 24h, 2Ch, 0EBh, 15h
    db 0D9h, 41h, 24h, 0D8h, 5Ch, 24h, 38h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 51h
    db 24h, 89h, 54h, 24h, 38h, 0D9h, 41h, 28h, 0D8h, 5Ch, 24h, 30h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 09h, 8Bh, 41h, 28h, 89h, 44h, 24h, 30h, 0EBh, 15h, 0D9h, 41h, 28h, 0D8h
    db 5Ch, 24h, 3Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 51h, 28h, 89h, 54h, 24h
    db 3Ch, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 24h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 8Dh, 71h, 30h, 0BBh, 04h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Dh, 44h, 24h, 4Ch, 50h, 56h, 8Dh, 7Eh, 0D0h, 57h, 8Dh, 4Ch, 24h, 28h, 0E8h, 85h
    db 0BCh, 6Dh, 0FFh, 84h, 0C0h, 75h, 08h, 0C7h, 44h, 24h, 4Ch, 00h, 00h, 80h, 3Fh, 0D9h
    db 06h, 0D8h, 27h, 0D8h, 4Ch, 24h, 4Ch, 0D8h, 07h, 0D9h, 46h, 04h, 0D8h, 66h, 0D4h, 0D8h
    db 4Ch, 24h, 4Ch, 0D8h, 46h, 0D4h, 0D9h, 5Ch, 24h, 14h, 0D8h, 54h, 24h, 2Ch, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Ah, 06h, 0D9h, 5Ch, 24h, 2Ch, 0EBh, 13h, 0D8h, 54h, 24h, 38h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 5Ch, 24h, 38h, 0EBh, 02h, 0DDh, 0D8h, 0D9h, 44h
    db 24h, 14h, 0D8h, 5Ch, 24h, 30h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 8Bh, 4Ch, 24h
    db 14h, 89h, 4Ch, 24h, 30h, 0EBh, 17h, 0D9h, 44h, 24h, 14h, 0D8h, 5Ch, 24h, 3Ch, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 8Bh, 54h, 24h, 14h, 89h, 54h, 24h, 3Ch, 83h, 0C6h
    db 0Ch, 4Bh, 0Fh, 85h, 68h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 50h, 8Bh, 54h, 24h, 48h
    db 50h, 8Dh, 4Ch, 24h, 30h, 51h, 52h, 8Bh, 0CDh, 0E8h, 02h, 0FDh, 0FFh, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 34h, 0C2h, 0Ch, 00h
?d_00944430@@YAXXZ ENDP

; ghidra: FUN_00d44fc0  retail @ 0x00944FC0 size 70
public ?d_00944fc0@@YAXXZ
?d_00944fc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 10h, 0D0h, 13h, 01h, 74h, 10h
    db 50h, 0E8h, 1Ah, 0CFh, 0F3h, 0FFh, 83h, 0C4h, 04h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 04h, 0D0h, 13h, 01h, 74h, 17h, 50h, 0E8h, 0FDh
    db 0CEh, 0F3h, 0FFh, 83h, 0C4h, 04h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0C7h, 46h, 08h
    db 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_00944fc0@@YAXXZ ENDP

; ghidra: FUN_00d451c0  retail @ 0x009451C0 size 210
public ?d_009451c0@@YAXXZ
?d_009451c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 0DAh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 8Dh, 5Eh, 10h, 8Bh, 0CBh, 89h
    db 5Ch, 24h, 08h, 0E8h, 0C0h, 1Dh, 6Eh, 0FFh, 83h, 3Eh, 00h, 0C7h, 44h, 24h, 14h, 00h
    db 00h, 00h, 00h, 75h, 7Dh, 57h, 8Bh, 7Eh, 04h, 68h, 04h, 0Ch, 00h, 00h, 0E8h, 2Dh
    db 0CDh, 0F3h, 0FFh, 89h, 46h, 04h, 89h, 38h, 8Bh, 46h, 04h, 83h, 0C4h, 04h, 83h, 0C0h
    db 04h, 89h, 06h, 0B8h, 18h, 00h, 00h, 00h, 5Fh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Eh, 8Dh, 4Ch, 08h, 0E8h, 8Dh, 51h, 0Ch, 89h, 11h, 8Bh, 0Eh, 8Dh, 14h, 08h
    db 89h, 54h, 08h, 0F4h, 8Bh, 0Eh, 8Dh, 54h, 08h, 0Ch, 89h, 14h, 08h, 8Bh, 0Eh, 8Dh
    db 54h, 08h, 18h, 89h, 54h, 08h, 0Ch, 83h, 0C0h, 30h, 3Dh, 18h, 0Ch, 00h, 00h, 7Ch
    db 0CFh, 8Bh, 06h, 0C7h, 80h, 0F4h, 0Bh, 00h, 00h, 00h, 00h, 00h, 00h, 8Bh, 56h, 08h
    db 8Bh, 4Eh, 0Ch, 0B8h, 00h, 01h, 00h, 00h, 03h, 0D0h, 03h, 0C8h, 89h, 56h, 08h, 89h
    db 4Eh, 0Ch, 8Bh, 06h, 8Bh, 08h, 89h, 0Eh, 0FFh, 4Eh, 08h, 8Bh, 4Ch, 24h, 0Ch, 0C7h
    db 03h, 00h, 00h, 00h, 00h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_009451c0@@YAXXZ ENDP

; ghidra: FUN_00d452d0  retail @ 0x009452D0 size 210
public ?d_009452d0@@YAXXZ
?d_009452d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 0DAh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 8Dh, 5Eh, 10h, 8Bh, 0CBh, 89h
    db 5Ch, 24h, 08h, 0E8h, 0B0h, 1Ch, 6Eh, 0FFh, 83h, 3Eh, 00h, 0C7h, 44h, 24h, 14h, 00h
    db 00h, 00h, 00h, 75h, 7Dh, 57h, 8Bh, 7Eh, 04h, 68h, 04h, 0Ch, 00h, 00h, 0E8h, 1Dh
    db 0CCh, 0F3h, 0FFh, 89h, 46h, 04h, 89h, 38h, 8Bh, 46h, 04h, 83h, 0C4h, 04h, 83h, 0C0h
    db 04h, 89h, 06h, 0B8h, 18h, 00h, 00h, 00h, 5Fh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Eh, 8Dh, 4Ch, 08h, 0E8h, 8Dh, 51h, 0Ch, 89h, 11h, 8Bh, 0Eh, 8Dh, 14h, 08h
    db 89h, 54h, 08h, 0F4h, 8Bh, 0Eh, 8Dh, 54h, 08h, 0Ch, 89h, 14h, 08h, 8Bh, 0Eh, 8Dh
    db 54h, 08h, 18h, 89h, 54h, 08h, 0Ch, 83h, 0C0h, 30h, 3Dh, 18h, 0Ch, 00h, 00h, 7Ch
    db 0CFh, 8Bh, 06h, 0C7h, 80h, 0F4h, 0Bh, 00h, 00h, 00h, 00h, 00h, 00h, 8Bh, 56h, 08h
    db 8Bh, 4Eh, 0Ch, 0B8h, 00h, 01h, 00h, 00h, 03h, 0D0h, 03h, 0C8h, 89h, 56h, 08h, 89h
    db 4Eh, 0Ch, 8Bh, 06h, 8Bh, 08h, 89h, 0Eh, 0FFh, 4Eh, 08h, 8Bh, 4Ch, 24h, 0Ch, 0C7h
    db 03h, 00h, 00h, 00h, 00h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_009452d0@@YAXXZ ENDP

; ghidra: FUN_00d45490  retail @ 0x00945490 size 34
public ?d_00945490@@YAXXZ
?d_00945490@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 81h, 0Ch, 85h, 0C9h, 8Bh, 44h, 24h, 08h, 0C7h
    db 04h, 24h, 00h, 00h, 00h, 00h, 89h, 08h, 74h, 04h, 66h, 0FFh, 41h, 04h, 59h, 0C2h
    db 08h, 00h
?d_00945490@@YAXXZ ENDP

; ghidra: FUN_00d45670  retail @ 0x00945670 size 37
public ?d_00945670@@YAXXZ
?d_00945670@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 60h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 08h, 8Bh, 16h, 8Bh, 0CEh, 5Eh, 0FFh, 62h, 60h, 0D9h, 86h, 0F8h
    db 02h, 00h, 00h, 5Eh, 0C3h
?d_00945670@@YAXXZ ENDP

; ghidra: FUN_00d45b20  retail @ 0x00945B20 size 83
public ?d_00945b20@@YAXXZ
?d_00945b20@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 10h, 8Bh, 09h, 53h, 56h, 57h, 8Bh, 0B9h
    db 9Ch, 00h, 00h, 00h, 8Dh, 34h, 50h, 8Bh, 9Ch, 0B7h, 0B4h, 00h, 00h, 00h, 85h, 0DBh
    db 8Bh, 74h, 24h, 14h, 50h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 52h, 74h, 14h
    db 8Bh, 44h, 24h, 20h, 50h, 56h, 0E8h, 15h, 95h, 0FEh, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh
    db 59h, 0C2h, 10h, 00h, 56h, 0E8h, 26h, 6Fh, 0FEh, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 59h
    db 0C2h, 10h, 00h
?d_00945b20@@YAXXZ ENDP

; ghidra: FUN_00d45bd0  retail @ 0x00945BD0 size 301
public ?d_00945bd0@@YAXXZ
?d_00945bd0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0D9h, 8Bh, 83h, 00h, 04h, 00h, 00h, 85h, 0C0h, 56h, 57h, 0C7h
    db 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0Fh, 86h, 93h, 00h, 00h, 00h, 8Dh, 0B3h, 00h
    db 02h, 00h, 00h, 8Bh, 44h, 24h, 18h, 8Bh, 08h, 3Bh, 8Eh, 00h, 0FEh, 0FFh, 0FFh, 75h
    db 65h, 8Bh, 50h, 04h, 3Bh, 96h, 00h, 0FFh, 0FFh, 0FFh, 75h, 5Ah, 8Bh, 6Ch, 24h, 1Ch
    db 85h, 0EDh, 8Bh, 3Eh, 74h, 1Ah, 8Ah, 45h, 68h, 84h, 0C0h, 74h, 0Eh, 8Bh, 0CDh, 0E8h
    db 0CCh, 0B2h, 0FDh, 0FFh, 89h, 45h, 64h, 0C6h, 45h, 68h, 00h, 8Bh, 6Dh, 64h, 0EBh, 02h
    db 33h, 0EDh, 85h, 0FFh, 74h, 1Ah, 8Ah, 47h, 68h, 84h, 0C0h, 74h, 0Eh, 8Bh, 0CFh, 0E8h
    db 0ACh, 0B2h, 0FDh, 0FFh, 89h, 47h, 64h, 0C6h, 47h, 68h, 00h, 8Bh, 7Fh, 64h, 0EBh, 02h
    db 33h, 0FFh, 3Bh, 0EFh, 75h, 10h, 8Bh, 44h, 24h, 20h, 3Bh, 86h, 00h, 01h, 00h, 00h
    db 0Fh, 84h, 8Dh, 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 8Bh, 8Bh, 00h, 04h, 00h, 00h
    db 40h, 83h, 0C6h, 04h, 3Bh, 0C1h, 89h, 44h, 24h, 10h, 0Fh, 82h, 73h, 0FFh, 0FFh, 0FFh
    db 8Bh, 74h, 24h, 18h, 33h, 0FFh, 8Bh, 8Bh, 00h, 04h, 00h, 00h, 8Bh, 06h, 03h, 0CFh
    db 85h, 0C0h, 8Dh, 2Ch, 8Bh, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 4Dh, 00h, 85h, 0C9h
    db 74h, 05h, 0E8h, 0F9h, 5Ah, 0Ah, 00h, 8Bh, 16h, 83h, 0C7h, 40h, 83h, 0C6h, 04h, 81h
    db 0FFh, 80h, 00h, 00h, 00h, 89h, 55h, 00h, 72h, 0CCh, 8Bh, 83h, 00h, 04h, 00h, 00h
    db 8Bh, 4Ch, 24h, 1Ch, 89h, 8Ch, 83h, 00h, 02h, 00h, 00h, 8Bh, 93h, 00h, 04h, 00h
    db 00h, 8Bh, 44h, 24h, 20h, 89h, 84h, 93h, 00h, 03h, 00h, 00h, 8Bh, 83h, 00h, 04h
    db 00h, 00h, 5Fh, 5Eh, 40h, 89h, 83h, 00h, 04h, 00h, 00h, 5Dh, 0B0h, 01h, 5Bh, 59h
    db 0C2h, 0Ch, 00h, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 5Bh, 59h, 0C2h, 0Ch, 00h
?d_00945bd0@@YAXXZ ENDP

; ghidra: FUN_00d45d00  retail @ 0x00945D00 size 19
public ?d_00945d00@@YAXXZ
?d_00945d00@@YAXXZ PROC
    db 68h, 52h, 06h, 43h, 00h, 68h, 80h, 00h, 00h, 00h, 6Ah, 04h, 51h, 0E8h, 64h, 10h
    db 0Bh, 00h, 0C3h
?d_00945d00@@YAXXZ ENDP
_TEXT ENDS
END
