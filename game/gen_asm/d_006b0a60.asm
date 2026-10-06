.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeDefeatScreenTable@@3PAEA:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?_bfme_debugRecordCallsite@@YAXH@Z:NEAR
EXTERN ?_bfme_debugReportingEnabled@@YA_NXZ:NEAR
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?g_Rva13596C0@@3P6GXPAX@ZA:BYTE
EXTERN ?j_00001eb5@@YAXXZ:NEAR
EXTERN ?j_0000268a@@YAXXZ:NEAR
EXTERN ?j_0000b43d@@YAXXZ:NEAR
EXTERN ?j_0000b7d5@@YAXXZ:NEAR
EXTERN ?j_0000cd3d@@YAXXZ:NEAR
EXTERN ?j_0000f380@@YAXXZ:NEAR
EXTERN ?j_0000fa1f@@YAXXZ:NEAR
EXTERN ?j_0001079e@@YAXXZ:NEAR
EXTERN ?j_0001147d@@YAXXZ:NEAR
EXTERN ?j_00015a69@@YAXXZ:NEAR
EXTERN ?j_00016928@@YAXXZ:NEAR
EXTERN ?j_00017f85@@YAXXZ:NEAR
EXTERN ?j_00018d22@@YAXXZ:NEAR
EXTERN ?j_0001978b@@YAXXZ:NEAR
EXTERN ?j_0001dff2@@YAXXZ:NEAR
EXTERN ?j_00021ff3@@YAXXZ:NEAR
EXTERN ?j_000220c5@@YAXXZ:NEAR
EXTERN ?j_00023911@@YAXXZ:NEAR
EXTERN ?j_00024f00@@YAXXZ:NEAR
EXTERN ?j_00025cca@@YAXXZ:NEAR
EXTERN ?j_00026f35@@YAXXZ:NEAR
EXTERN ?j_0002918b@@YAXXZ:NEAR
EXTERN ?j_000298e8@@YAXXZ:NEAR
EXTERN ?j_00029910@@YAXXZ:NEAR
EXTERN ?j_0002e668@@YAXXZ:NEAR
EXTERN ?j_000311bf@@YAXXZ:NEAR
EXTERN ?j_0003214b@@YAXXZ:NEAR
EXTERN ?j_00032317@@YAXXZ:NEAR
EXTERN ?j_000334b0@@YAXXZ:NEAR
EXTERN ?j_000351b6@@YAXXZ:NEAR
EXTERN ?j_0003828a@@YAXXZ:NEAR
EXTERN ?j_0003aa6c@@YAXXZ:NEAR
EXTERN ?j_0004066f@@YAXXZ:NEAR
EXTERN ?j_00046a33@@YAXXZ:NEAR
EXTERN ?j_00047b27@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN __imp__AIL_init_sample@4:BYTE
EXTERN __imp__AIL_register_EOS_callback@8:BYTE
EXTERN __imp__AIL_set_3D_sample_volume@8:BYTE
EXTERN __imp__AIL_stop_sample@4:BYTE
EXTERN __imp__InterlockedDecrement@4:BYTE
EXTERN __imp__InterlockedIncrement@4:BYTE
EXTERN __imp__ReleaseMutex@4:BYTE
EXTERN __imp__Rva0135961COff@4:BYTE
EXTERN __imp__WaitForSingleObject@8:BYTE
EXTERN __imp___AIL_set_sample_volume_pan@12:BYTE
EXTERN __imp__free:BYTE
EXTERN g_Va00AB7BF0:NEAR
EXTERN g_Va00AB7D24:NEAR
EXTERN g_Va01048D18:NEAR
EXTERN g_Va01048DB8:NEAR
EXTERN g_Va01048ECE:NEAR
EXTERN g_Va01049040:NEAR
EXTERN g_Va010490BA:NEAR
EXTERN g_Va01049100:NEAR
EXTERN g_Va01076C28:BYTE
EXTERN g_Va0111C410:BYTE
EXTERN g_Va0111C4DC:BYTE
EXTERN g_Va0111C4F0:BYTE
EXTERN g_Va0111C668:BYTE
EXTERN g_Va0111C6A8:BYTE
EXTERN g_Va012F7764:BYTE
EXTERN g_Va01359584:BYTE
EXTERN g_Va013595E4:BYTE
EXTERN g_Va013595E8:BYTE
EXTERN g_Va01359624:BYTE
EXTERN g_Va01359650:BYTE
EXTERN g_Va0135967C:BYTE
EXTERN g_Va013596A0:BYTE
EXTERN g_Va013596AC:BYTE
EXTERN g_Va013596B0:BYTE
EXTERN g_Va013596D4:BYTE
_TEXT SEGMENT

; ghidra: FUN_00ab0a60  retail @ 0x006B0A60 size 387
public ?d_006b0a60@@YAXXZ
?d_006b0a60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 49h, 8Ah, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 7Ch, 24h, 2Ch, 8Bh
    db 07h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CFh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h, 24h
    db 11h, 01h, 0FFh, 50h, 28h, 8Bh, 74h, 24h, 30h, 8Bh, 06h, 8Bh, 56h, 04h, 2Bh, 0D0h
    db 8Bh, 07h, 8Dh, 4Ch, 24h, 10h, 0C1h, 0FAh, 02h, 51h, 8Bh, 0CFh, 89h, 54h, 24h, 30h
    db 0C7h, 44h, 24h, 14h, 48h, 55h, 07h, 01h, 0FFh, 50h, 2Ch, 8Bh, 10h, 8Dh, 4Ch, 24h
    db 2Ch, 51h, 8Bh, 0C8h, 0FFh, 52h, 74h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 08h, 84h, 0C0h
    db 74h, 31h, 8Bh, 5Eh, 04h, 8Bh, 36h, 3Bh, 0F3h, 0Fh, 84h, 0F0h, 00h, 00h, 00h, 90h
    db 8Bh, 07h, 56h, 8Bh, 0CFh, 0FFh, 50h, 64h, 83h, 0C6h, 04h, 3Bh, 0F3h, 75h, 0F1h, 8Bh
    db 0C7h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 1Ch, 0C3h, 8Bh, 0Eh, 3Bh, 4Eh, 04h, 74h, 23h, 68h, 24h, 55h, 07h, 01h, 8Dh
    db 54h, 24h, 18h, 6Ah, 04h, 52h, 0E8h, 05h, 57h, 32h, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch
    db 0FEh, 1Dh, 01h, 8Dh, 44h, 24h, 18h, 50h, 0E8h, 0D3h, 61h, 34h, 00h, 8Bh, 4Ch, 24h
    db 2Ch, 51h, 8Bh, 0CEh, 0E8h, 0Dh, 0C8h, 95h, 0FFh, 33h, 0DBh, 89h, 5Ch, 24h, 30h, 39h
    db 5Ch, 24h, 2Ch, 89h, 5Ch, 24h, 24h, 74h, 6Ch, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 2Ch, 4Ah, 8Dh, 44h, 24h, 30h, 89h, 54h, 24h, 2Ch, 8Bh, 17h, 50h
    db 8Bh, 0CFh, 0FFh, 52h, 64h, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 74h, 2Ch, 89h, 44h, 24h
    db 10h, 89h, 44h, 24h, 14h, 3Bh, 0C3h, 0C6h, 44h, 24h, 24h, 01h, 74h, 0Ch, 8Dh, 4Ch
    db 24h, 30h, 51h, 8Bh, 0C8h, 0E8h, 76h, 78h, 1Dh, 00h, 8Bh, 46h, 04h, 83h, 0C0h, 04h
    db 88h, 5Ch, 24h, 24h, 89h, 46h, 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h
    db 34h, 52h, 8Dh, 4Ch, 24h, 3Ch, 51h, 50h, 8Bh, 0CEh, 0E8h, 0B4h, 5Eh, 96h, 0FFh, 39h
    db 5Ch, 24h, 2Ch, 75h, 9Bh, 8Bh, 44h, 24h, 2Ch, 48h, 8Dh, 4Ch, 24h, 30h, 89h, 44h
    db 24h, 2Ch, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 01h, 76h, 1Dh, 00h, 8Bh
    db 4Ch, 24h, 1Ch, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 1Ch, 0C3h
?d_006b0a60@@YAXXZ ENDP

; ghidra: FUN_00ab0cb0  retail @ 0x006B0CB0 size 258
public ?d_006b0cb0@@YAXXZ
?d_006b0cb0@@YAXXZ PROC
    db 51h, 53h, 56h, 8Bh, 74h, 24h, 10h, 8Bh, 0D9h, 0B0h, 01h, 57h, 8Dh, 4Ch, 24h, 0Ch
    db 88h, 44h, 24h, 0Ch, 88h, 44h, 24h, 0Dh, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h
    db 8Dh, 7Bh, 04h, 0C7h, 44h, 24h, 14h, 06h, 00h, 00h, 00h, 55h, 8Dh, 64h, 24h, 00h
    db 0BDh, 02h, 00h, 00h, 00h, 8Bh, 16h, 57h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 83h, 0C7h, 04h
    db 4Dh, 75h, 0F2h, 0FFh, 4Ch, 24h, 18h, 75h, 0E7h, 8Dh, 83h, 0A0h, 00h, 00h, 00h, 50h
    db 56h, 0E8h, 3Eh, 28h, 95h, 0FFh, 8Bh, 16h, 83h, 0C4h, 08h, 8Dh, 83h, 9Ch, 00h, 00h
    db 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 0BBh, 0C4h, 00h, 00h, 00h, 57h
    db 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 80h, 3Fh, 00h, 5Dh, 74h, 54h, 8Bh, 06h
    db 8Dh, 8Bh, 0ACh, 00h, 00h, 00h, 51h, 8Bh, 0CEh, 0FFh, 50h, 6Ch, 8Bh, 16h, 8Dh, 83h
    db 0B0h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 83h, 0B4h, 00h
    db 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 83h, 0B8h, 00h, 00h, 00h
    db 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 83h, 0BCh, 00h, 00h, 00h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 83h, 0C0h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 6Ch, 8Dh, 8Bh, 0B8h, 01h, 00h, 00h, 51h, 56h, 0E8h, 45h, 3Ch, 96h, 0FFh, 83h
    db 0C4h, 08h, 33h, 0FFh, 33h, 0F6h, 56h, 57h, 8Bh, 0CBh, 0E8h, 0CCh, 90h, 96h, 0FFh, 46h
    db 83h, 0FEh, 02h, 7Ch, 0F1h, 47h, 83h, 0FFh, 06h, 7Ch, 0E9h, 5Fh, 5Eh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_006b0cb0@@YAXXZ ENDP

; ghidra: FUN_00ab0e00  retail @ 0x006B0E00 size 1550
public ?d_006b0e00@@YAXXZ
?d_006b0e00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Ch, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h
    db 24h, 10h, 0E8h, 09h, 0Ch, 2Fh, 00h, 0C7h, 46h, 08h, 44h, 37h, 07h, 01h, 33h, 0DBh
    db 0C7h, 06h, 0C0h, 0C0h, 11h, 01h, 0C7h, 46h, 08h, 0ACh, 0C0h, 11h, 01h, 89h, 5Eh, 0Ch
    db 89h, 5Eh, 10h, 89h, 5Eh, 14h, 89h, 5Eh, 18h, 89h, 5Eh, 1Ch, 89h, 5Eh, 20h, 0C7h
    db 46h, 24h, 00h, 00h, 80h, 3Fh, 89h, 5Eh, 28h, 89h, 5Eh, 2Ch, 89h, 5Eh, 30h, 89h
    db 5Eh, 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h, 0C7h, 46h, 44h, 55h, 55h
    db 05h, 42h, 89h, 5Eh, 48h, 6Ah, 0Ch, 89h, 5Ch, 24h, 24h, 89h, 5Eh, 4Ch, 0E8h, 0BDh
    db 0D6h, 17h, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 04h, 89h, 46h, 4Ch, 8Dh, 4Eh
    db 50h, 89h, 59h, 04h, 89h, 59h, 08h, 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h
    db 0C6h, 44h, 24h, 24h, 02h, 89h, 59h, 10h, 0E8h, 3Ch, 0B0h, 98h, 0FFh, 8Dh, 7Eh, 64h
    db 6Ah, 14h, 0C6h, 44h, 24h, 24h, 03h, 89h, 1Fh, 0E8h, 82h, 0D6h, 17h, 00h, 89h, 07h
    db 89h, 5Fh, 04h, 88h, 18h, 8Bh, 07h, 89h, 58h, 04h, 8Bh, 07h, 89h, 40h, 08h, 8Bh
    db 07h, 83h, 0C4h, 04h, 89h, 40h, 0Ch, 8Dh, 4Eh, 70h, 89h, 59h, 04h, 89h, 59h, 08h
    db 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h, 0C6h, 44h, 24h, 24h, 05h, 89h, 59h
    db 10h, 0E8h, 0DDh, 89h, 98h, 0FFh, 0C7h, 86h, 84h, 00h, 00h, 00h, 05h, 00h, 00h, 00h
    db 89h, 9Eh, 88h, 00h, 00h, 00h, 89h, 9Eh, 8Ch, 00h, 00h, 00h, 89h, 9Eh, 90h, 00h
    db 00h, 00h, 0C6h, 44h, 24h, 20h, 07h, 68h, 5Fh, 97h, 40h, 00h, 68h, 92h, 0A3h, 42h
    db 00h, 6Ah, 03h, 6Ah, 0Ch, 8Dh, 8Eh, 94h, 00h, 00h, 00h, 51h, 0E8h, 0B3h, 5Fh, 34h
    db 00h, 68h, 04h, 0EFh, 43h, 00h, 68h, 1Fh, 3Ah, 42h, 00h, 6Ah, 03h, 68h, 0C4h, 01h
    db 00h, 00h, 8Dh, 0AEh, 0B8h, 00h, 00h, 00h, 55h, 0C6h, 44h, 24h, 34h, 08h, 0E8h, 91h
    db 5Fh, 34h, 00h, 68h, 0F0h, 0E6h, 41h, 00h, 68h, 65h, 0EBh, 40h, 00h, 6Ah, 40h, 0B8h
    db 02h, 00h, 00h, 00h, 6Ah, 0Ch, 8Dh, 96h, 54h, 06h, 00h, 00h, 52h, 0C6h, 44h, 24h
    db 34h, 09h, 89h, 86h, 04h, 06h, 00h, 00h, 89h, 9Eh, 08h, 06h, 00h, 00h, 89h, 9Eh
    db 0Ch, 06h, 00h, 00h, 89h, 9Eh, 10h, 06h, 00h, 00h, 89h, 9Eh, 14h, 06h, 00h, 00h
    db 89h, 9Eh, 18h, 06h, 00h, 00h, 89h, 9Eh, 1Ch, 06h, 00h, 00h, 89h, 9Eh, 20h, 06h
    db 00h, 00h, 89h, 9Eh, 24h, 06h, 00h, 00h, 66h, 89h, 86h, 28h, 06h, 00h, 00h, 0C6h
    db 86h, 2Ah, 06h, 00h, 00h, 01h, 0C6h, 86h, 2Bh, 06h, 00h, 00h, 01h, 0C6h, 86h, 2Ch
    db 06h, 00h, 00h, 01h, 0C6h, 86h, 2Dh, 06h, 00h, 00h, 01h, 0C6h, 86h, 2Eh, 06h, 00h
    db 00h, 01h, 88h, 9Eh, 2Fh, 06h, 00h, 00h, 88h, 9Eh, 30h, 06h, 00h, 00h, 88h, 9Eh
    db 31h, 06h, 00h, 00h, 88h, 9Eh, 32h, 06h, 00h, 00h, 88h, 9Eh, 33h, 06h, 00h, 00h
    db 88h, 9Eh, 34h, 06h, 00h, 00h, 88h, 9Eh, 35h, 06h, 00h, 00h, 88h, 9Eh, 36h, 06h
    db 00h, 00h, 88h, 9Eh, 37h, 06h, 00h, 00h, 89h, 9Eh, 38h, 06h, 00h, 00h, 0E8h, 0D1h
    db 5Eh, 34h, 00h, 8Dh, 8Eh, 6Ch, 09h, 00h, 00h, 89h, 9Eh, 54h, 09h, 00h, 00h, 0C7h
    db 86h, 58h, 09h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 9Eh, 5Ch, 09h, 00h, 00h, 89h
    db 9Eh, 60h, 09h, 00h, 00h, 89h, 9Eh, 64h, 09h, 00h, 00h, 89h, 9Eh, 68h, 09h, 00h
    db 00h, 89h, 59h, 04h, 89h, 59h, 08h, 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h
    db 0C6h, 44h, 24h, 24h, 0Bh, 89h, 59h, 10h, 0E8h, 9Ch, 0D8h, 95h, 0FFh, 89h, 9Eh, 80h
    db 09h, 00h, 00h, 89h, 9Eh, 84h, 09h, 00h, 00h, 89h, 9Eh, 88h, 09h, 00h, 00h, 89h
    db 9Eh, 8Ch, 09h, 00h, 00h, 89h, 9Eh, 90h, 09h, 00h, 00h, 89h, 9Eh, 94h, 09h, 00h
    db 00h, 68h, 0B9h, 0B2h, 43h, 00h, 68h, 0A7h, 2Fh, 42h, 00h, 0C6h, 44h, 24h, 28h, 0Eh
    db 6Ah, 03h, 6Ah, 0Ch, 8Dh, 86h, 98h, 09h, 00h, 00h, 50h, 0E8h, 44h, 5Eh, 34h, 00h
    db 6Ah, 0Ch, 0C6h, 44h, 24h, 24h, 0Fh, 89h, 9Eh, 0BCh, 09h, 00h, 00h, 0E8h, 8Eh, 0D4h
    db 17h, 00h, 89h, 00h, 89h, 40h, 04h, 89h, 86h, 0BCh, 09h, 00h, 00h, 6Ah, 0Ch, 0C6h
    db 44h, 24h, 28h, 10h, 89h, 9Eh, 0C0h, 09h, 00h, 00h, 0E8h, 71h, 0D4h, 17h, 00h, 89h
    db 00h, 89h, 40h, 04h, 89h, 86h, 0C0h, 09h, 00h, 00h, 6Ah, 0Ch, 0C6h, 44h, 24h, 2Ch
    db 11h, 89h, 9Eh, 0C4h, 09h, 00h, 00h, 0E8h, 54h, 0D4h, 17h, 00h, 89h, 00h, 89h, 40h
    db 04h, 89h, 86h, 0C4h, 09h, 00h, 00h, 6Ah, 0Ch, 0C6h, 44h, 24h, 30h, 12h, 89h, 9Eh
    db 0C8h, 09h, 00h, 00h, 0E8h, 37h, 0D4h, 17h, 00h, 89h, 00h, 89h, 40h, 04h, 89h, 86h
    db 0C8h, 09h, 00h, 00h, 6Ah, 0Ch, 0C6h, 44h, 24h, 34h, 13h, 89h, 9Eh, 0CCh, 09h, 00h
    db 00h, 0E8h, 1Ah, 0D4h, 17h, 00h, 89h, 00h, 89h, 40h, 04h, 89h, 86h, 0CCh, 09h, 00h
    db 00h, 6Ah, 0Ch, 0C6h, 44h, 24h, 38h, 14h, 89h, 9Eh, 0D0h, 09h, 00h, 00h, 0E8h, 0FDh
    db 0D3h, 17h, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 18h, 89h, 86h, 0D0h, 09h, 00h
    db 00h, 68h, 44h, 6Dh, 44h, 00h, 68h, 0A0h, 40h, 42h, 00h, 6Ah, 06h, 6Ah, 28h, 8Dh
    db 8Eh, 0D4h, 09h, 00h, 00h, 51h, 0C6h, 44h, 24h, 34h, 15h, 0E8h, 74h, 5Dh, 34h, 00h
    db 68h, 0F6h, 46h, 40h, 00h, 68h, 0DFh, 1Eh, 43h, 00h, 6Ah, 03h, 6Ah, 04h, 8Dh, 96h
    db 0D0h, 0Ah, 00h, 00h, 52h, 0C6h, 44h, 24h, 34h, 16h, 0E8h, 55h, 5Dh, 34h, 00h, 89h
    db 9Eh, 0DCh, 0Ah, 00h, 00h, 89h, 9Eh, 0E0h, 0Ah, 00h, 00h, 89h, 9Eh, 0E4h, 0Ah, 00h
    db 00h, 89h, 9Eh, 0E8h, 0Ah, 00h, 00h, 89h, 9Eh, 0ECh, 0Ah, 00h, 00h, 89h, 9Eh, 0F0h
    db 0Ah, 00h, 00h, 0C6h, 44h, 24h, 20h, 19h, 6Ah, 18h, 89h, 9Eh, 0F4h, 0Ah, 00h, 00h
    db 0E8h, 7Bh, 0D3h, 17h, 00h, 89h, 86h, 0F4h, 0Ah, 00h, 00h, 89h, 9Eh, 0F8h, 0Ah, 00h
    db 00h, 88h, 18h, 8Bh, 86h, 0F4h, 0Ah, 00h, 00h, 89h, 58h, 04h, 8Bh, 86h, 0F4h, 0Ah
    db 00h, 00h, 89h, 40h, 08h, 8Bh, 86h, 0F4h, 0Ah, 00h, 00h, 89h, 40h, 0Ch, 89h, 9Eh
    db 00h, 0Bh, 00h, 00h, 6Ah, 0Ch, 0C6h, 44h, 24h, 28h, 1Ah, 89h, 9Eh, 04h, 0Bh, 00h
    db 00h, 0E8h, 3Ah, 0D3h, 17h, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h, 08h, 89h, 86h
    db 04h, 0Bh, 00h, 00h, 8Dh, 8Eh, 08h, 0Bh, 00h, 00h, 89h, 59h, 04h, 89h, 59h, 08h
    db 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h, 0C6h, 44h, 24h, 24h, 1Ch, 89h, 59h
    db 10h, 0E8h, 81h, 59h, 96h, 0FFh, 8Dh, 8Eh, 1Ch, 0Bh, 00h, 00h, 89h, 59h, 04h, 89h
    db 59h, 08h, 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h, 0C6h, 44h, 24h, 24h, 1Eh
    db 89h, 59h, 10h, 0E8h, 0BEh, 5Eh, 96h, 0FFh, 8Dh, 8Eh, 30h, 0Bh, 00h, 00h, 89h, 59h
    db 04h, 89h, 59h, 08h, 89h, 4Ch, 24h, 14h, 89h, 59h, 0Ch, 6Ah, 64h, 0C6h, 44h, 24h
    db 24h, 20h, 89h, 59h, 10h, 0E8h, 01h, 9Bh, 95h, 0FFh, 53h, 0C6h, 44h, 24h, 24h, 21h
    db 89h, 9Eh, 44h, 0Bh, 00h, 00h, 89h, 9Eh, 48h, 0Bh, 00h, 00h, 0C7h, 86h, 4Ch, 0Bh
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 9Eh, 50h, 0Bh, 00h, 00h, 89h, 9Eh, 54h, 0Bh
    db 00h, 00h, 89h, 9Eh, 58h, 0Bh, 00h, 00h, 0C7h, 86h, 5Ch, 0Bh, 00h, 00h, 07h, 00h
    db 00h, 00h, 89h, 9Eh, 60h, 0Bh, 00h, 00h, 0FFh, 15h, 54h, 93h, 35h, 01h, 89h, 86h
    db 68h, 0Bh, 00h, 00h, 89h, 96h, 6Ch, 0Bh, 00h, 00h, 88h, 9Eh, 70h, 0Bh, 00h, 00h
    db 8Bh, 47h, 04h, 83h, 0C4h, 04h, 3Bh, 0C3h, 74h, 1Fh, 8Bh, 0Fh, 8Bh, 51h, 04h, 52h
    db 8Bh, 0CFh, 0E8h, 28h, 7Dh, 97h, 0FFh, 8Bh, 07h, 89h, 40h, 08h, 8Bh, 07h, 89h, 58h
    db 04h, 8Bh, 07h, 89h, 40h, 0Ch, 89h, 5Fh, 04h, 89h, 9Eh, 0C4h, 0Ah, 00h, 00h, 89h
    db 5Dh, 00h, 89h, 9Eh, 3Ch, 06h, 00h, 00h, 89h, 9Eh, 48h, 06h, 00h, 00h, 89h, 9Eh
    db 0C8h, 0Ah, 00h, 00h, 0C7h, 86h, 7Ch, 02h, 00h, 00h, 01h, 00h, 00h, 00h, 89h, 9Eh
    db 40h, 06h, 00h, 00h, 89h, 9Eh, 4Ch, 06h, 00h, 00h, 89h, 9Eh, 0CCh, 0Ah, 00h, 00h
    db 0C7h, 86h, 40h, 04h, 00h, 00h, 02h, 00h, 00h, 00h, 68h, 38h, 01h, 00h, 00h, 89h
    db 9Eh, 44h, 06h, 00h, 00h, 89h, 9Eh, 50h, 06h, 00h, 00h, 0E8h, 0E0h, 0Bh, 1Dh, 00h
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 14h, 3Bh, 0C3h, 0C6h, 44h, 24h, 20h, 22h, 74h, 09h
    db 8Bh, 0C8h, 0E8h, 9Fh, 60h, 99h, 0FFh, 0EBh, 02h, 33h, 0C0h, 68h, 00h, 0Eh, 00h, 00h
    db 0C6h, 44h, 24h, 24h, 21h, 89h, 46h, 0Ch, 0E8h, 0B3h, 0Bh, 1Dh, 00h, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 14h, 3Bh, 0C3h, 0C6h, 44h, 24h, 20h, 23h, 74h, 09h, 8Bh, 0C8h, 0E8h
    db 49h, 9Ch, 95h, 0FFh, 0EBh, 02h, 33h, 0C0h, 68h, 5Ch, 0BAh, 11h, 01h, 53h, 53h, 0C6h
    db 44h, 24h, 2Ch, 21h, 89h, 46h, 10h, 0FFh, 15h, 0F4h, 8Ch, 35h, 01h, 6Ah, 4Ch, 89h
    db 86h, 5Ch, 09h, 00h, 00h, 0E8h, 76h, 0Bh, 1Dh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 14h, 3Bh, 0C3h, 0C6h, 44h, 24h, 20h, 24h, 74h, 29h, 8Bh, 8Eh, 5Ch, 09h, 00h, 00h
    db 51h, 8Bh, 0C8h, 0E8h, 0C2h, 92h, 96h, 0FFh, 5Fh, 89h, 86h, 00h, 0Bh, 00h, 00h, 8Bh
    db 0C6h, 5Eh, 5Dh, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 14h, 0C3h, 8Bh, 4Ch, 24h, 18h, 5Fh, 89h, 9Eh, 00h, 0Bh, 00h, 00h, 8Bh, 0C6h
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_006b0e00@@YAXXZ ENDP

; ghidra: FUN_00ab15a0  retail @ 0x006B15A0 size 184
_TEXT ENDS
_TEXT$d00ab15a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB15A0 size 184
public ?d_006b15a0@@YAXXZ
?d_006b15a0@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01048D18
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 008h, 055h, 08Bh, 06Ch, 024h, 01Ch
    db 08Bh, 045h, 000h, 085h, 0C0h, 056h, 08Bh, 0F1h, 074h, 07Eh, 066h, 083h, 078h, 004h, 000h, 074h
    db 077h, 053h, 057h, 08Bh, 0BEh, 05Ch, 009h, 000h, 000h, 06Ah, 0FFh, 032h, 0DBh, 057h, 088h, 05Ch
    db 024h, 01Ch, 089h, 07Ch, 024h, 018h, 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 074h, 006h, 0B3h, 001h, 088h, 05Ch, 024h, 014h, 055h, 08Dh, 08Eh
    db 06Ch, 009h, 000h, 000h, 0C7h, 044h, 024h, 024h, 000h, 000h, 000h, 000h
    call ?j_00018d22@@YAXXZ
    db 085h, 0C0h, 075h, 00Eh, 055h, 08Dh, 08Eh, 08Ch, 009h, 000h, 000h
    call ?j_00032317@@YAXXZ
    db 0EBh, 01Ch, 08Dh, 048h, 008h, 08Bh, 001h, 085h, 0C0h, 074h, 013h, 066h, 083h, 078h, 004h, 000h
    db 074h, 00Ch, 051h, 08Dh, 08Eh, 080h, 009h, 000h, 000h
    call ?j_00024f00@@YAXXZ
    db 084h, 0DBh, 074h, 007h, 057h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 05Fh, 05Bh, 08Bh, 04Ch, 024h, 010h, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 014h, 0C2h, 004h, 000h
?d_006b15a0@@YAXXZ ENDP
_TEXT$d00ab15a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab1690  retail @ 0x006B1690 size 695
public ?d_006b1690@@YAXXZ
?d_006b1690@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 4Eh, 8Dh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 30h, 8Bh, 41h, 04h, 8Bh, 68h, 28h, 8Bh, 58h, 64h, 3Bh, 9Ch, 0AEh, 0C4h, 0Ah, 00h
    db 00h, 57h, 8Dh, 79h, 04h, 89h, 6Ch, 24h, 18h, 89h, 5Ch, 24h, 20h, 7Eh, 1Ah, 8Ah
    db 51h, 10h, 33h, 0C0h, 84h, 0D2h, 0Fh, 94h, 0C0h, 8Bh, 0CEh, 50h, 55h, 0E8h, 3Dh, 05h
    db 97h, 0FFh, 89h, 9Ch, 0AEh, 0C4h, 0Ah, 00h, 00h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CEh
    db 0E8h, 0B4h, 5Ch, 97h, 0FFh, 8Bh, 5Ch, 24h, 10h, 83h, 0C3h, 14h, 3Bh, 0DFh, 0C7h, 44h
    db 24h, 2Ch, 00h, 00h, 00h, 00h, 74h, 3Ch, 8Bh, 07h, 85h, 0C0h, 74h, 0Ah, 83h, 0C0h
    db 74h, 50h, 0FFh, 15h, 5Ch, 8Eh, 35h, 01h, 8Bh, 03h, 85h, 0C0h, 74h, 22h, 8Dh, 68h
    db 70h, 8Dh, 4Dh, 04h, 51h, 0FFh, 15h, 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 0Dh, 85h
    db 0EDh, 74h, 09h, 8Bh, 55h, 00h, 6Ah, 01h, 8Bh, 0CDh, 0FFh, 12h, 8Bh, 6Ch, 24h, 18h
    db 8Bh, 07h, 89h, 03h, 8Bh, 4Ch, 24h, 10h, 8Bh, 49h, 14h, 8Dh, 54h, 24h, 14h, 52h
    db 0E8h, 80h, 0A0h, 95h, 0FFh, 8Bh, 44h, 24h, 14h, 33h, 0DBh, 3Bh, 0C3h, 0C6h, 44h, 24h
    db 2Ch, 01h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 7Ch
    db 24h, 10h, 53h, 50h, 8Bh, 86h, 60h, 09h, 00h, 00h, 50h, 0FFh, 15h, 0D8h, 95h, 35h
    db 01h, 89h, 47h, 08h, 8Bh, 4Ch, 24h, 10h, 39h, 59h, 08h, 0Fh, 85h, 0E2h, 00h, 00h
    db 00h, 0F6h, 05h, 60h, 77h, 2Fh, 01h, 01h, 75h, 52h, 83h, 0Dh, 60h, 77h, 2Fh, 01h
    db 01h, 6Ah, 14h, 0C6h, 44h, 24h, 30h, 02h, 89h, 1Dh, 50h, 77h, 2Fh, 01h, 0E8h, 8Dh
    db 0CDh, 17h, 00h, 0A3h, 50h, 77h, 2Fh, 01h, 89h, 1Dh, 54h, 77h, 2Fh, 01h, 0C6h, 00h
    db 00h, 8Bh, 15h, 50h, 77h, 2Fh, 01h, 89h, 5Ah, 04h, 0A1h, 50h, 77h, 2Fh, 01h, 89h
    db 40h, 08h, 0A1h, 50h, 77h, 2Fh, 01h, 68h, 10h, 09h, 07h, 01h, 89h, 40h, 0Ch, 0E8h
    db 42h, 56h, 34h, 00h, 83h, 0C4h, 08h, 0C6h, 44h, 24h, 2Ch, 01h, 8Dh, 44h, 24h, 14h
    db 50h, 0B9h, 50h, 77h, 2Fh, 01h, 0E8h, 76h, 18h, 95h, 0FFh, 3Bh, 05h, 50h, 77h, 2Fh
    db 01h, 75h, 7Ch, 0E8h, 0C8h, 7Eh, 1Dh, 00h, 84h, 0C0h, 74h, 51h, 6Ah, 01h, 0E8h, 8Dh
    db 7Eh, 1Dh, 00h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 83h, 0C4h, 04h, 0FFh, 52h
    db 60h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 01h, 53h, 53h, 0FFh, 50h, 6Ch, 8Bh, 10h
    db 8Dh, 4Ch, 24h, 14h, 51h, 68h, 78h, 0C3h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 50h
    db 0E8h, 41h, 57h, 96h, 0FFh, 8Bh, 10h, 83h, 0C4h, 08h, 68h, 6Ch, 0C3h, 11h, 01h, 8Bh
    db 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah, 02h, 8Bh, 0C8h, 0FFh, 52h, 4Ch, 8Dh, 44h, 24h
    db 14h, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 0B9h, 50h, 77h, 2Fh, 01h, 0E8h, 91h, 0A3h, 96h
    db 0FFh, 0EBh, 0Ch, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0E8h, 74h, 07h, 97h, 0FFh, 8Bh
    db 44h, 24h, 10h, 8Bh, 4Ch, 24h, 20h, 0C7h, 40h, 0Ch, 03h, 00h, 00h, 00h, 3Bh, 8Ch
    db 0AEh, 0C4h, 0Ah, 00h, 00h, 75h, 49h, 8Bh, 44h, 24h, 34h, 8Ah, 48h, 10h, 33h, 0D2h
    db 84h, 0C9h, 0Fh, 94h, 0C2h, 8Bh, 0CEh, 52h, 55h, 0E8h, 71h, 03h, 97h, 0FFh, 8Bh, 4Ch
    db 24h, 10h, 8Bh, 49h, 14h, 0E8h, 0F1h, 2Dh, 95h, 0FFh, 84h, 0C0h, 74h, 22h, 8Bh, 54h
    db 24h, 10h, 0C6h, 42h, 35h, 01h, 8Bh, 46h, 0Ch, 0DBh, 40h, 3Ch, 8Bh, 4Ch, 24h, 10h
    db 53h, 0D9h, 59h, 28h, 8Bh, 54h, 24h, 14h, 8Bh, 4Ah, 14h, 0E8h, 0EFh, 0ACh, 97h, 0FFh
    db 8Bh, 44h, 24h, 10h, 39h, 58h, 08h, 74h, 11h, 68h, 00h, 00h, 80h, 0BFh, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0E8h, 0B0h, 93h, 99h, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h
    db 24h, 2Ch, 00h, 0E8h, 38h, 60h, 1Dh, 00h, 8Bh, 74h, 24h, 10h, 3Bh, 0F3h, 0C7h, 44h
    db 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 1Ah, 8Dh, 56h, 04h, 52h, 0FFh, 15h, 54h, 8Eh
    db 35h, 01h, 85h, 0C0h, 7Fh, 0Ch, 3Bh, 0F3h, 74h, 08h, 8Bh, 06h, 6Ah, 01h, 8Bh, 0CEh
    db 0FFh, 10h, 8Bh, 4Ch, 24h, 24h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 20h, 0C2h, 04h, 00h
?d_006b1690@@YAXXZ ENDP

; ghidra: FUN_00ab1ce0  retail @ 0x006B1CE0 size 301
public ?d_006b1ce0@@YAXXZ
?d_006b1ce0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 8Bh, 75h, 00h, 8Bh, 46h, 0Ch, 48h, 57h
    db 8Bh, 0D9h, 74h, 19h, 48h, 74h, 04h, 33h, 0FFh, 0EBh, 15h, 8Bh, 46h, 08h, 8Bh, 8Bh
    db 44h, 0Bh, 00h, 00h, 0C1h, 0E0h, 06h, 8Bh, 7Ch, 08h, 04h, 0EBh, 03h, 8Bh, 7Eh, 08h
    db 8Bh, 46h, 14h, 6Ah, 01h, 50h, 8Bh, 0CBh, 0E8h, 6Eh, 74h, 97h, 0FFh, 8Bh, 43h, 0Ch
    db 0DBh, 40h, 3Ch, 8Bh, 55h, 00h, 0D8h, 7Ah, 28h, 0D8h, 2Dh, 34h, 53h, 07h, 01h, 0D8h
    db 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah, 0DDh, 0D8h, 0D9h, 05h
    db 50h, 53h, 07h, 01h, 0EBh, 15h, 0D8h, 15h, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 0C9h, 51h, 0D9h, 1Ch
    db 24h, 57h, 0DDh, 0D8h, 0FFh, 15h, 5Ch, 96h, 35h, 01h, 8Bh, 4Eh, 14h, 0E8h, 0B2h, 53h
    db 97h, 0FFh, 0D9h, 5Ch, 24h, 18h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 18h
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 20h, 57h, 0FFh, 15h, 88h, 95h, 35h, 01h
    db 89h, 44h, 24h, 10h, 0DBh, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 18h, 0E8h, 97h, 50h, 34h
    db 00h, 50h, 57h, 0FFh, 15h, 58h, 96h, 35h, 01h, 8Bh, 4Eh, 14h, 8Bh, 51h, 08h, 0D9h
    db 42h, 70h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 28h, 8Bh
    db 4Ch, 24h, 1Ch, 8Bh, 03h, 51h, 8Bh, 0CBh, 0FFh, 90h, 84h, 01h, 00h, 00h, 84h, 0C0h
    db 75h, 15h, 8Bh, 56h, 14h, 0D9h, 05h, 34h, 53h, 07h, 01h, 8Bh, 42h, 08h, 0D8h, 60h
    db 70h, 51h, 0D9h, 1Ch, 24h, 0EBh, 02h, 6Ah, 00h, 57h, 0FFh, 15h, 54h, 96h, 35h, 01h
    db 8Dh, 4Ch, 24h, 18h, 51h, 55h, 8Bh, 0CBh, 0E8h, 0D3h, 27h, 99h, 0FFh, 55h, 8Bh, 0CBh
    db 0E8h, 09h, 0C8h, 97h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_006b1ce0@@YAXXZ ENDP

; ghidra: FUN_00ab1e60  retail @ 0x006B1E60 size 281
public ?d_006b1e60@@YAXXZ
?d_006b1e60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Dh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 57h, 0C6h, 44h, 24h, 18h, 00h, 89h, 7Ch, 24h, 14h, 0FFh
    db 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 05h, 0C6h, 44h, 24h, 10h
    db 01h, 8Bh, 86h, 58h, 09h, 00h, 00h, 83h, 0F8h, 0FFh, 8Bh, 5Ch, 24h, 24h, 0C7h, 44h
    db 24h, 1Ch, 00h, 00h, 00h, 00h, 74h, 45h, 8Dh, 84h, 40h, 95h, 01h, 00h, 00h, 68h
    db 78h, 0BAh, 11h, 01h, 8Dh, 0Ch, 86h, 0E8h, 4Eh, 91h, 99h, 0FFh, 85h, 0C0h, 75h, 29h
    db 84h, 0DBh, 74h, 29h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 07h, 57h, 0FFh, 15h, 0CCh
    db 8Eh, 35h, 01h, 5Fh, 5Eh, 0B0h, 01h, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 84h, 0DBh, 74h, 0D7h, 53h, 8Bh, 0CEh
    db 0E8h, 21h, 27h, 98h, 0FFh, 8Bh, 86h, 58h, 09h, 00h, 00h, 83h, 0F8h, 0FFh, 74h, 44h
    db 8Dh, 8Ch, 40h, 95h, 01h, 00h, 00h, 68h, 78h, 0BAh, 11h, 01h, 8Dh, 0Ch, 8Eh, 0E8h
    db 0F6h, 90h, 99h, 0FFh, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 3Ah, 0D8h, 8Ah, 44h, 24h, 10h
    db 0Fh, 94h, 0C3h, 84h, 0C0h, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 5Fh, 5Eh
    db 8Ah, 0C3h, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 14h, 0C2h, 04h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 07h, 57h, 0FFh, 15h, 0CCh
    db 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006b1e60@@YAXXZ ENDP

; ghidra: FUN_00ab1fc0  retail @ 0x006B1FC0 size 258
_TEXT ENDS
_TEXT$d00ab1fc0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB1FC0 size 258
public ?d_006b1fc0@@YAXXZ
?d_006b1fc0@@YAXXZ PROC
    db 083h, 0ECh, 014h, 053h, 055h, 056h, 08Bh, 074h, 024h, 024h, 08Bh, 046h, 008h, 08Bh, 068h, 034h
    db 057h, 06Ah, 001h, 033h, 0FFh, 056h, 08Bh, 0D9h, 089h, 07Ch, 024h, 018h
    call ?j_0002918b@@YAXXZ
    db 0D9h, 05Ch, 024h, 020h, 08Bh, 0CEh
    call ?j_0000f380@@YAXXZ
    db 084h, 0C0h, 074h, 00Ch, 08Dh, 08Bh, 0CCh, 009h, 000h, 000h, 089h, 04Ch, 024h, 028h, 0EBh, 00Ah
    db 08Dh, 093h, 0C8h, 009h, 000h, 000h, 089h, 054h, 024h, 028h, 08Bh, 044h, 024h, 028h, 08Bh, 000h
    db 08Bh, 030h, 03Bh, 0F0h, 00Fh, 084h, 0A0h, 000h, 000h, 000h, 08Bh, 04Eh, 008h, 08Bh, 079h, 014h
    db 08Bh, 0D1h, 08Bh, 042h, 014h, 06Ah, 001h, 050h, 08Bh, 0CBh
    call ?j_0002918b@@YAXXZ
    db 08Bh, 04Bh, 00Ch, 0DBh, 041h, 03Ch, 08Bh, 046h, 008h, 0D8h, 078h, 028h, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 057h, 008h, 0D8h, 0C9h, 08Bh, 04Ah, 034h, 03Bh, 0CDh, 0D9h, 05Ch, 024h, 018h, 0DDh, 0D8h
    db 07Ch, 011h, 07Fh, 01Dh, 0D9h, 044h, 024h, 018h, 0D8h, 05Ch, 024h, 020h, 0DFh, 0E0h, 0F6h, 0C4h
    db 005h, 07Ah, 00Eh, 08Bh, 044h, 024h, 018h, 089h, 07Ch, 024h, 010h, 08Bh, 0E9h, 089h, 044h, 024h
    db 020h, 08Bh, 04Ch, 024h, 028h, 08Bh, 036h, 03Bh, 031h, 00Fh, 085h, 06Eh, 0FFh, 0FFh, 0FFh, 08Bh
    db 044h, 024h, 010h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C2h, 004h, 000h, 08Bh, 0C7h, 05Fh
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C2h, 004h, 000h
?d_006b1fc0@@YAXXZ ENDP
_TEXT$d00ab1fc0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab2110  retail @ 0x006B2110 size 228
_TEXT ENDS
_TEXT$d00ab2110 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB2110 size 228
public ?d_006b2110@@YAXXZ
?d_006b2110@@YAXXZ PROC
    db 083h, 0ECh, 008h, 053h, 055h, 056h, 08Bh, 074h, 024h, 018h, 08Bh, 046h, 008h, 08Bh, 068h, 034h
    db 057h, 06Ah, 001h, 056h, 08Bh, 0F9h
    call ?j_0002918b@@YAXXZ
    db 0D9h, 05Ch, 024h, 014h, 08Bh, 0CEh
    call ?j_0000f380@@YAXXZ
    db 084h, 0C0h, 074h, 00Ch, 08Dh, 08Fh, 0CCh, 009h, 000h, 000h, 089h, 04Ch, 024h, 01Ch, 0EBh, 00Ah
    db 08Dh, 097h, 0C8h, 009h, 000h, 000h, 089h, 054h, 024h, 01Ch, 08Bh, 044h, 024h, 01Ch, 08Bh, 000h
    db 08Bh, 030h, 03Bh, 0F0h, 074h, 07Eh, 08Dh, 064h, 024h, 000h, 08Bh, 04Eh, 008h, 08Bh, 059h, 014h
    db 08Bh, 0D1h, 08Bh, 042h, 014h, 06Ah, 001h, 050h, 08Bh, 0CFh
    call ?j_0002918b@@YAXXZ
    db 08Bh, 04Fh, 00Ch, 0DBh, 041h, 03Ch, 08Bh, 046h, 008h, 0D8h, 078h, 028h, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 053h, 008h, 0DEh, 0C9h, 08Bh, 042h, 034h, 03Bh, 0C5h, 07Ch, 027h, 07Fh, 00Dh, 0D8h, 05Ch
    db 024h, 014h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 01Ch, 0EBh, 002h, 0DDh, 0D8h, 08Bh, 044h, 024h
    db 01Ch, 08Bh, 036h, 03Bh, 030h, 075h, 086h, 05Fh, 05Eh, 05Dh, 032h, 0C0h, 05Bh, 083h, 0C4h, 008h
    db 0C2h, 004h, 000h, 0DDh, 0D8h, 05Fh, 05Eh, 05Dh, 0B0h, 001h, 05Bh, 083h, 0C4h, 008h, 0C2h, 004h
    db 000h
?d_006b2110@@YAXXZ ENDP
_TEXT$d00ab2110 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab2230  retail @ 0x006B2230 size 535
public ?d_006b2230@@YAXXZ
?d_006b2230@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A0h, 8Dh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 74h, 24h, 24h, 8Bh
    db 0E9h, 57h, 8Bh, 0CEh, 89h, 6Ch, 24h, 10h, 0E8h, 23h, 0D1h, 95h, 0FFh, 84h, 0C0h, 74h
    db 15h, 8Bh, 0CDh, 0E8h, 0ABh, 0Ch, 95h, 0FFh, 8Bh, 85h, 0C4h, 09h, 00h, 00h, 39h, 00h
    db 0Fh, 85h, 0BAh, 01h, 00h, 00h, 56h, 8Bh, 0CDh, 0E8h, 78h, 5Eh, 97h, 0FFh, 85h, 0C0h
    db 89h, 44h, 24h, 28h, 74h, 7Eh, 8Bh, 0CEh, 0E8h, 0F3h, 0D0h, 95h, 0FFh, 84h, 0C0h, 0Fh
    db 84h, 0D2h, 00h, 00h, 00h, 8Bh, 85h, 0CCh, 09h, 00h, 00h, 8Bh, 38h, 3Bh, 0F8h, 8Dh
    db 9Dh, 0CCh, 09h, 00h, 00h, 74h, 5Dh, 8Bh, 2Dh, 54h, 8Eh, 35h, 01h, 8Dh, 49h, 00h
    db 8Bh, 77h, 08h, 85h, 0F6h, 89h, 74h, 24h, 14h, 74h, 0Ah, 8Dh, 46h, 04h, 50h, 0FFh
    db 15h, 5Ch, 8Eh, 35h, 01h, 85h, 0F6h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 75h
    db 0Ah, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 23h, 8Bh, 4Ch, 24h, 28h, 39h
    db 4Eh, 14h, 74h, 37h, 8Dh, 56h, 04h, 52h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0FFh, 0D5h, 85h, 0C0h, 7Fh, 08h, 8Bh, 06h, 6Ah, 01h, 8Bh, 0CEh, 0FFh, 10h, 8Bh, 3Fh
    db 3Bh, 3Bh, 75h, 0ACh, 32h, 0C0h, 8Bh, 4Ch, 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 8Bh, 4Eh, 14h, 0E8h, 0A9h
    db 0FCh, 95h, 0FFh, 84h, 0C0h, 74h, 0Eh, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 4Ch, 24h, 14h
    db 0E8h, 0E2h, 0C9h, 96h, 0FFh, 8Bh, 4Ch, 24h, 10h, 56h, 0E8h, 5Eh, 43h, 97h, 0FFh, 51h
    db 8Bh, 0C4h, 8Dh, 54h, 24h, 2Ch, 89h, 64h, 24h, 2Ch, 52h, 8Bh, 0CBh, 89h, 38h, 0E8h
    db 0D0h, 0E9h, 96h, 0FFh, 8Dh, 46h, 04h, 50h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0FFh, 0D5h, 0E9h, 0BDh, 00h, 00h, 00h, 8Bh, 85h, 0C8h, 09h, 00h, 00h, 8Bh, 38h, 3Bh
    db 0F8h, 8Dh, 9Dh, 0C8h, 09h, 00h, 00h, 74h, 8Bh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 77h, 08h, 85h, 0F6h, 89h, 74h, 24h, 14h, 74h, 0Ah, 8Dh, 46h, 04h, 50h, 0FFh
    db 15h, 5Ch, 8Eh, 35h, 01h, 85h, 0F6h, 0C7h, 44h, 24h, 20h, 01h, 00h, 00h, 00h, 75h
    db 0Ah, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 27h, 8Bh, 4Ch, 24h, 28h, 39h
    db 4Eh, 14h, 74h, 29h, 8Dh, 56h, 04h, 52h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0FFh, 15h, 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 08h, 8Bh, 06h, 6Ah, 01h, 8Bh, 0CEh
    db 0FFh, 10h, 8Bh, 3Fh, 3Bh, 3Bh, 75h, 0A8h, 0E9h, 27h, 0FFh, 0FFh, 0FFh, 8Bh, 4Eh, 14h
    db 0E8h, 0E7h, 0FBh, 95h, 0FFh, 84h, 0C0h, 74h, 0Ch, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CDh
    db 0E8h, 22h, 0C9h, 96h, 0FFh, 56h, 8Bh, 0CDh, 0E8h, 0A0h, 42h, 97h, 0FFh, 51h, 8Bh, 0C4h
    db 8Dh, 54h, 24h, 2Ch, 89h, 64h, 24h, 2Ch, 52h, 8Bh, 0CBh, 89h, 38h, 0E8h, 12h, 0E9h
    db 96h, 0FFh, 8Dh, 46h, 04h, 50h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 15h
    db 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 08h, 8Bh, 16h, 6Ah, 01h, 8Bh, 0CEh, 0FFh, 12h
    db 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Bh, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006b2230@@YAXXZ ENDP

; ghidra: FUN_00ab24d0  retail @ 0x006B24D0 size 1772
_TEXT ENDS
_TEXT$d00ab24d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB24D0 size 1772
public ?d_006b24d0@@YAXXZ
?d_006b24d0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01048DB8
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 034h, 053h, 055h, 056h, 08Bh, 0E9h, 033h, 0DBh, 057h, 089h, 06Ch, 024h, 014h, 089h, 05Ch, 024h
    db 010h, 08Bh, 085h, 0C8h, 009h, 000h, 000h, 08Bh, 038h, 03Bh, 0F8h, 089h, 05Ch, 024h, 04Ch, 00Fh
    db 084h, 012h, 001h, 000h, 000h, 08Dh, 064h, 024h, 000h, 08Dh, 077h, 008h, 08Dh, 044h, 024h, 010h
    db 03Bh, 0C6h, 074h, 030h, 08Bh, 006h, 085h, 0C0h, 074h, 00Ah, 083h, 0C0h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedIncrement@4
    db 085h, 0DBh, 074h, 016h, 08Dh, 04Bh, 004h, 051h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 013h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 012h, 08Bh, 01Eh, 089h, 05Ch
    db 024h, 010h, 085h, 0DBh, 00Fh, 084h, 0BDh, 000h, 000h, 000h, 08Bh, 044h, 024h, 054h, 08Bh, 000h
    db 085h, 0C0h, 074h, 026h, 066h, 083h, 078h, 004h, 000h, 074h, 01Fh, 08Bh, 043h, 014h, 08Bh, 048h
    db 008h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 04Ch, 024h, 054h, 051h, 08Bh, 0C8h
    call ?j_000220c5@@YAXXZ
    db 085h, 0C0h, 00Fh, 085h, 08Dh, 000h, 000h, 000h, 08Bh, 043h, 014h, 08Bh, 050h, 028h, 03Bh, 054h
    db 024h, 05Ch, 00Fh, 085h, 07Dh, 000h, 000h, 000h, 050h, 08Bh, 0CDh
    call ?j_00001eb5@@YAXXZ
    db 08Bh, 043h, 014h, 06Ah, 001h, 050h, 08Bh, 0CDh
    call ?j_0002918b@@YAXXZ
    db 08Bh, 045h, 00Ch, 0DBh, 040h, 03Ch, 0D8h, 07Bh, 028h, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 053h, 008h, 0D8h, 0C9h, 08Dh, 04Ch, 024h, 01Ch, 051h, 06Ah, 000h, 0D9h, 05Ch, 024h, 028h
    db 052h, 0DDh, 0D8h, 0FFh, 015h
    dd g_Va01359624
    db 08Bh, 044h, 024h, 01Ch, 08Bh, 04Ch, 024h, 020h, 08Bh, 053h, 008h, 050h, 051h, 052h, 0FFh, 015h
    dd __imp___AIL_set_sample_volume_pan@12
    db 08Bh, 03Fh, 03Bh, 0BDh, 0C8h, 009h, 000h, 000h, 00Fh, 085h, 0F2h, 0FEh, 0FFh, 0FFh, 08Bh, 085h
    db 0CCh, 009h, 000h, 000h, 08Bh, 038h, 03Bh, 0F8h, 089h, 07Ch, 024h, 018h, 00Fh, 084h, 07Ch, 001h
    db 000h, 000h, 08Dh, 077h, 008h, 08Dh, 044h, 024h, 010h, 03Bh, 0C6h, 074h, 030h, 08Bh, 006h, 085h
    db 0C0h, 074h, 00Ah, 083h, 0C0h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedIncrement@4
    db 085h, 0DBh, 074h, 016h, 08Dh, 04Bh, 004h, 051h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 013h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 012h, 08Bh, 01Eh, 089h, 05Ch
    db 024h, 010h, 085h, 0DBh, 00Fh, 084h, 027h, 001h, 000h, 000h, 08Bh, 044h, 024h, 054h, 08Bh, 000h
    db 085h, 0C0h, 074h, 079h, 066h, 083h, 078h, 004h, 000h, 074h, 072h, 08Bh, 043h, 014h, 08Bh, 048h
    db 008h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 04Ch, 024h, 054h, 08Bh, 009h, 085h, 0C9h, 074h, 006h
    db 00Fh, 0B7h, 069h, 004h, 0EBh, 002h, 033h, 0EDh, 085h, 0C9h, 08Dh, 079h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 050h, 004h, 0EBh, 002h, 033h, 0D2h, 085h, 0C0h
    db 08Dh, 070h, 008h, 075h, 005h, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0D5h, 08Bh, 0CAh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h
    db 083h, 0D8h, 0FFh, 085h, 0C0h, 00Fh, 085h, 0B0h, 000h, 000h, 000h, 02Bh, 0D5h, 08Bh, 0C2h, 085h
    db 0C0h, 00Fh, 085h, 0A4h, 000h, 000h, 000h, 08Bh, 07Ch, 024h, 018h, 08Bh, 06Ch, 024h, 014h, 08Bh
    db 04Bh, 014h, 08Bh, 054h, 024h, 05Ch, 039h, 051h, 028h, 00Fh, 085h, 094h, 000h, 000h, 000h, 08Bh
    db 043h, 00Ch, 048h, 074h, 019h, 048h, 00Fh, 085h, 087h, 000h, 000h, 000h, 08Bh, 043h, 008h, 08Bh
    db 095h, 044h, 00Bh, 000h, 000h, 0C1h, 0E0h, 006h, 08Bh, 074h, 010h, 004h, 0EBh, 003h, 08Bh, 073h
    db 008h, 085h, 0F6h, 074h, 06Eh, 051h, 08Bh, 0CDh
    call ?j_00001eb5@@YAXXZ
    db 08Bh, 043h, 014h, 06Ah, 001h, 050h, 08Bh, 0CDh
    call ?j_0002918b@@YAXXZ
    db 08Bh, 045h, 00Ch, 0DBh, 040h, 03Ch, 0D8h, 07Bh, 028h, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 020h, 08Bh, 04Ch, 024h, 020h, 051h, 0DDh, 0D8h, 056h, 0FFh, 015h
    dd __imp__AIL_set_3D_sample_volume@8
    db 0EBh, 008h, 08Bh, 07Ch, 024h, 018h, 08Bh, 06Ch, 024h, 014h, 08Bh, 03Fh, 03Bh, 0BDh, 0CCh, 009h
    db 000h, 000h, 089h, 07Ch, 024h, 018h, 00Fh, 085h, 084h, 0FEh, 0FFh, 0FFh, 08Bh, 085h, 0D0h, 009h
    db 000h, 000h, 08Bh, 038h, 03Bh, 0F8h, 089h, 07Ch, 024h, 018h, 00Fh, 084h, 07Fh, 001h, 000h, 000h
    db 08Dh, 077h, 008h, 08Dh, 054h, 024h, 010h, 03Bh, 0D6h, 074h, 030h, 08Bh, 006h, 085h, 0C0h, 074h
    db 00Ah, 083h, 0C0h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedIncrement@4
    db 085h, 0DBh, 074h, 016h, 08Dh, 043h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 013h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 012h, 08Bh, 01Eh, 089h, 05Ch
    db 024h, 010h, 085h, 0DBh, 00Fh, 084h, 026h, 001h, 000h, 000h, 08Bh, 044h, 024h, 054h, 08Bh, 000h
    db 085h, 0C0h, 074h, 075h, 066h, 083h, 078h, 004h, 000h, 074h, 06Eh, 08Bh, 043h, 014h, 08Bh, 048h
    db 008h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 04Ch, 024h, 054h, 08Bh, 009h, 085h, 0C9h, 074h, 006h
    db 00Fh, 0B7h, 069h, 004h, 0EBh, 002h, 033h, 0EDh, 085h, 0C9h, 08Dh, 079h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 050h, 004h, 0EBh, 002h, 033h, 0D2h, 085h, 0C0h
    db 08Dh, 070h, 008h, 075h, 005h, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0D5h, 08Bh, 0CAh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h
    db 083h, 0D8h, 0FFh, 085h, 0C0h, 00Fh, 085h, 0B3h, 000h, 000h, 000h, 02Bh, 0D5h, 08Bh, 0C2h, 085h
    db 0C0h, 00Fh, 085h, 0A7h, 000h, 000h, 000h, 08Bh, 07Ch, 024h, 018h, 08Bh, 043h, 014h, 08Bh, 054h
    db 024h, 05Ch, 039h, 050h, 028h, 00Fh, 085h, 097h, 000h, 000h, 000h, 08Bh, 048h, 008h, 083h, 0B9h
    db 084h, 000h, 000h, 000h, 003h, 00Fh, 084h, 087h, 000h, 000h, 000h, 08Bh, 074h, 024h, 014h, 050h
    db 08Bh, 0CEh
    call ?j_00001eb5@@YAXXZ
    db 08Bh, 043h, 014h, 06Ah, 001h, 050h, 08Bh, 0CEh
    call ?j_0002918b@@YAXXZ
    db 08Bh, 046h, 00Ch, 0DBh, 040h, 03Ch, 0D8h, 07Bh, 028h, 0D8h, 02Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 053h, 008h, 0D8h, 0C9h, 08Dh, 04Ch, 024h, 01Ch, 051h, 06Ah, 000h, 0D9h, 05Ch, 024h, 028h
    db 052h, 0DDh, 0D8h, 0FFh, 015h
    dd g_Va013596D4
    db 08Bh, 044h, 024h, 01Ch, 08Bh, 04Ch, 024h, 020h, 08Bh, 053h, 008h, 050h, 051h, 052h, 0FFh, 015h
    dd g_Va013596A0
    db 0EBh, 004h, 08Bh, 07Ch, 024h, 018h, 08Bh, 044h, 024h, 014h, 08Bh, 03Fh, 03Bh, 0B8h, 0D0h, 009h
    db 000h, 000h, 089h, 07Ch, 024h, 018h, 00Fh, 085h, 081h, 0FEh, 0FFh, 0FFh, 08Bh, 054h, 024h, 05Ch
    db 08Bh, 044h, 024h, 014h, 08Dh, 00Ch, 092h, 0C1h, 0E1h, 004h, 08Dh, 084h, 001h, 0D4h, 009h, 000h
    db 000h, 089h, 044h, 024h, 018h, 0C7h, 044h, 024h, 020h, 002h, 000h, 000h, 000h, 08Bh, 0C8h, 08Bh
    db 031h, 08Bh, 079h, 004h, 089h, 07Ch, 024h, 028h, 08Bh, 079h, 008h, 08Bh, 049h, 00Ch, 089h, 07Ch
    db 024h, 02Ch, 089h, 04Ch, 024h, 030h, 08Dh, 048h, 010h, 08Bh, 0F9h, 08Bh, 00Fh, 03Bh, 0F1h, 08Bh
    db 06Fh, 004h, 089h, 06Ch, 024h, 038h, 08Bh, 06Fh, 008h, 08Bh, 07Fh, 00Ch, 089h, 074h, 024h, 024h
    db 089h, 04Ch, 024h, 034h, 089h, 06Ch, 024h, 03Ch, 089h, 07Ch, 024h, 040h, 00Fh, 084h, 00Dh, 001h
    db 000h, 000h, 08Dh, 054h, 024h, 010h, 03Bh, 0D6h, 074h, 030h, 08Bh, 006h, 085h, 0C0h, 074h, 00Ah
    db 083h, 0C0h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedIncrement@4
    db 085h, 0DBh, 074h, 016h, 08Dh, 043h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 013h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 012h, 08Bh, 01Eh, 089h, 05Ch
    db 024h, 010h, 085h, 0DBh, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 08Bh, 07Ch, 024h, 054h, 08Bh, 007h
    db 085h, 0C0h, 074h, 069h, 066h, 083h, 078h, 004h, 000h, 074h, 062h, 08Bh, 043h, 014h, 08Bh, 048h
    db 008h, 08Bh, 001h, 0FFh, 050h, 004h, 08Bh, 00Fh, 085h, 0C9h, 074h, 006h, 00Fh, 0B7h, 069h, 004h
    db 0EBh, 002h, 033h, 0EDh, 085h, 0C9h, 08Dh, 079h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 050h, 004h, 0EBh, 002h, 033h, 0D2h, 085h, 0C0h
    db 08Dh, 070h, 008h, 075h, 005h, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0D5h, 08Bh, 0CAh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h
    db 083h, 0D8h, 0FFh, 085h, 0C0h, 075h, 024h, 02Bh, 0D5h, 08Bh, 0C2h, 085h, 0C0h, 075h, 01Ch, 08Bh
    db 074h, 024h, 024h, 08Bh, 043h, 014h, 08Bh, 04Ch, 024h, 05Ch, 039h, 048h, 028h, 075h, 010h, 08Bh
    db 04Ch, 024h, 014h, 050h
    call ?j_00001eb5@@YAXXZ
    db 0EBh, 004h, 08Bh, 074h, 024h, 024h, 08Bh, 044h, 024h, 02Ch, 083h, 0C6h, 004h, 03Bh, 0F0h, 089h
    db 074h, 024h, 024h, 075h, 01Dh, 08Bh, 054h, 024h, 030h, 08Dh, 042h, 004h, 089h, 044h, 024h, 030h
    db 08Bh, 000h, 08Dh, 088h, 080h, 000h, 000h, 000h, 08Bh, 0F0h, 089h, 04Ch, 024h, 02Ch, 089h, 074h
    db 024h, 024h, 03Bh, 074h, 024h, 034h, 00Fh, 085h, 0FBh, 0FEh, 0FFh, 0FFh, 08Bh, 054h, 024h, 05Ch
    db 08Bh, 044h, 024h, 018h, 08Bh, 04Ch, 024h, 020h, 083h, 0C0h, 028h, 049h, 089h, 044h, 024h, 018h
    db 089h, 04Ch, 024h, 020h, 00Fh, 085h, 098h, 0FEh, 0FFh, 0FFh, 08Bh, 044h, 024h, 014h, 08Dh, 014h
    db 052h, 08Bh, 08Ch, 090h, 098h, 000h, 000h, 000h, 08Dh, 004h, 090h, 08Bh, 080h, 094h, 000h, 000h
    db 000h, 03Bh, 0C1h, 089h, 04Ch, 024h, 020h, 089h, 044h, 024h, 05Ch, 00Fh, 084h, 094h, 000h, 000h
    db 000h, 08Bh, 074h, 024h, 054h, 08Bh, 006h, 085h, 0C0h, 074h, 066h, 066h, 083h, 078h, 004h, 000h
    db 074h, 05Fh, 08Bh, 04Ch, 024h, 05Ch, 08Bh, 049h, 008h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 00Eh
    db 085h, 0C9h, 074h, 006h, 00Fh, 0B7h, 069h, 004h, 0EBh, 002h, 033h, 0EDh, 085h, 0C9h, 08Dh, 079h
    db 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 050h, 004h, 0EBh, 002h, 033h, 0D2h, 085h, 0C0h
    db 08Dh, 070h, 008h, 075h, 005h, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0D5h, 08Bh, 0CAh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h
    db 083h, 0D8h, 0FFh, 085h, 0C0h, 075h, 015h, 02Bh, 0D5h, 08Bh, 0C2h, 085h, 0C0h, 075h, 00Dh, 08Bh
    db 043h, 014h, 08Bh, 04Ch, 024h, 014h, 050h
    call ?j_00001eb5@@YAXXZ
    db 08Bh, 044h, 024h, 05Ch, 08Bh, 04Ch, 024h, 020h, 083h, 0C0h, 078h, 03Bh, 0C1h, 089h, 044h, 024h
    db 05Ch, 00Fh, 085h, 06Ch, 0FFh, 0FFh, 0FFh, 085h, 0DBh, 0C7h, 044h, 024h, 04Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 074h, 016h, 08Dh, 043h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 013h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 012h, 08Bh, 04Ch, 024h, 044h
    db 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 040h, 0C2h, 00Ch
    db 000h
?d_006b24d0@@YAXXZ ENDP
_TEXT$d00ab24d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab2d80  retail @ 0x006B2D80 size 448
public ?d_006b2d80@@YAXXZ
?d_006b2d80@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0E9h, 57h, 8Dh, 9Dh, 0D0h, 0Ah, 00h, 00h, 0C7h
    db 44h, 24h, 10h, 03h, 00h, 00h, 00h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 13h, 85h, 0D2h, 0Fh, 84h, 83h, 01h, 00h, 00h, 8Bh, 0B5h, 0D0h, 09h, 00h, 00h
    db 8Bh, 06h, 32h, 0C9h, 3Bh, 0C6h, 74h, 1Dh, 84h, 0C9h, 0Fh, 85h, 47h, 01h, 00h, 00h
    db 39h, 50h, 08h, 75h, 02h, 0B1h, 01h, 8Bh, 00h, 3Bh, 0C6h, 75h, 0EBh, 84h, 0C9h, 0Fh
    db 85h, 32h, 01h, 00h, 00h, 8Bh, 4Ah, 14h, 8Bh, 41h, 08h, 8Bh, 0B0h, 8Ch, 00h, 00h
    db 00h, 8Bh, 0B8h, 90h, 00h, 00h, 00h, 8Dh, 51h, 08h, 05h, 8Ch, 00h, 00h, 00h, 3Bh
    db 0F7h, 74h, 0Ch, 8Bh, 41h, 28h, 50h, 52h, 8Bh, 0CDh, 0E8h, 3Eh, 86h, 95h, 0FFh, 8Ah
    db 85h, 33h, 06h, 00h, 00h, 84h, 0C0h, 8Bh, 03h, 74h, 17h, 8Bh, 48h, 14h, 8Bh, 49h
    db 08h, 8Bh, 51h, 7Ch, 8Bh, 89h, 80h, 00h, 00h, 00h, 52h, 8Bh, 50h, 08h, 51h, 52h
    db 0EBh, 0Bh, 8Bh, 48h, 08h, 6Ah, 00h, 68h, 00h, 00h, 80h, 3Fh, 51h, 0FFh, 15h, 9Ch
    db 96h, 35h, 01h, 8Bh, 03h, 8Bh, 48h, 08h, 8Dh, 54h, 24h, 14h, 52h, 6Ah, 00h, 51h
    db 0FFh, 15h, 0D4h, 96h, 35h, 01h, 8Bh, 13h, 8Bh, 42h, 14h, 6Ah, 01h, 50h, 8Bh, 0CDh
    db 0E8h, 36h, 63h, 97h, 0FFh, 8Bh, 45h, 0Ch, 0DBh, 40h, 3Ch, 8Bh, 0Bh, 0D8h, 79h, 28h
    db 0D8h, 2Dh, 34h, 53h, 07h, 01h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 0Ah, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0EBh, 15h, 0D8h, 15h, 34h
    db 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h, 53h
    db 07h, 01h, 8Bh, 54h, 24h, 14h, 0D8h, 0C9h, 8Bh, 41h, 08h, 52h, 51h, 0D9h, 1Ch, 24h
    db 50h, 0DDh, 0D8h, 0FFh, 15h, 0A0h, 96h, 35h, 01h, 8Bh, 0BDh, 0D0h, 09h, 00h, 00h, 6Ah
    db 0Ch, 0E8h, 8Ah, 0B6h, 17h, 00h, 8Bh, 0F0h, 8Dh, 4Eh, 08h, 53h, 51h, 0E8h, 4Dh, 58h
    db 96h, 0FFh, 8Bh, 47h, 04h, 89h, 3Eh, 89h, 46h, 04h, 89h, 30h, 89h, 77h, 04h, 8Bh
    db 03h, 8Ah, 48h, 39h, 83h, 0C4h, 0Ch, 84h, 0C9h, 75h, 19h, 8Ah, 48h, 3Ah, 84h, 0C9h
    db 75h, 12h, 8Ah, 48h, 3Bh, 84h, 0C9h, 75h, 0Bh, 8Ah, 48h, 3Ch, 84h, 0C9h, 75h, 04h
    db 33h, 0C9h, 0EBh, 05h, 0B9h, 01h, 00h, 00h, 00h, 8Bh, 40h, 08h, 0Fh, 0B6h, 0D1h, 52h
    db 50h, 0FFh, 15h, 0DCh, 95h, 35h, 01h, 8Bh, 33h, 85h, 0F6h, 74h, 20h, 8Dh, 4Eh, 04h
    db 51h, 0FFh, 15h, 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 0Ch, 85h, 0F6h, 74h, 08h, 8Bh
    db 16h, 6Ah, 01h, 8Bh, 0CEh, 0FFh, 12h, 0C7h, 03h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 10h, 83h, 0C3h, 04h, 48h, 89h, 44h, 24h, 10h, 0Fh, 85h, 61h, 0FEh, 0FFh, 0FFh, 5Fh
?d_006b2d80@@YAXXZ ENDP

; ghidra: FUN_00ab3c50  retail @ 0x006B3C50 size 23
public ?d_006b3c50@@YAXXZ
?d_006b3c50@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Dh, 04h, 24h, 50h, 0C7h, 41h, 44h, 00h, 00h, 00h, 00h, 0E8h, 1Fh
    db 70h, 99h, 0FFh, 83h, 0C4h, 08h, 0C3h
?d_006b3c50@@YAXXZ ENDP

; ghidra: FUN_00ab3c70  retail @ 0x006B3C70 size 176
public ?d_006b3c70@@YAXXZ
?d_006b3c70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 8Dh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 55h, 8Bh, 0E9h, 8Bh, 9Dh, 5Ch, 09h
    db 00h, 00h, 6Ah, 0FFh, 53h, 0C6h, 44h, 24h, 14h, 00h, 89h, 5Ch, 24h, 10h, 0FFh, 15h
    db 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 05h, 0C6h, 44h, 24h, 0Ch, 01h
    db 56h, 57h, 33h, 0F6h, 89h, 74h, 24h, 28h, 8Dh, 0BDh, 0B8h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 8Bh, 4Ch, 24h, 34h, 85h, 0C1h, 74h
    db 0Ch, 8Bh, 54h, 24h, 30h, 52h, 8Bh, 0CFh, 0E8h, 6Bh, 0DAh, 95h, 0FFh, 46h, 81h, 0C7h
    db 0C4h, 01h, 00h, 00h, 83h, 0FEh, 03h, 7Ch, 0D7h, 8Dh, 44h, 24h, 18h, 50h, 8Bh, 0CDh
    db 0C7h, 45h, 44h, 00h, 00h, 00h, 00h, 0E8h, 86h, 6Fh, 99h, 0FFh, 8Ah, 44h, 24h, 14h
    db 84h, 0C0h, 5Fh, 5Eh, 74h, 07h, 53h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h
    db 18h, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 08h, 00h
?d_006b3c70@@YAXXZ ENDP

; ghidra: FUN_00ab3d50  retail @ 0x006B3D50 size 175
public ?d_006b3d50@@YAXXZ
?d_006b3d50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 18h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 0AEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 55h, 88h, 5Ch, 24h, 18h, 89h, 6Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 28h, 8Bh, 4Ch, 24h, 24h, 69h, 0C0h, 0C4h, 01h, 00h
    db 00h, 8Dh, 0B4h, 30h, 0B8h, 00h, 00h, 00h, 51h, 8Dh, 8Eh, 0A0h, 00h, 00h, 00h, 0C7h
    db 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0E8h, 30h, 0DDh, 98h, 0FFh, 85h, 0C0h, 76h, 20h
    db 81h, 0BEh, 9Ch, 00h, 00h, 00h, 00h, 00h, 80h, 3Fh, 74h, 14h, 57h, 8Dh, 0BEh, 88h
    db 01h, 00h, 00h, 0B9h, 0Ch, 00h, 00h, 00h, 0B8h, 02h, 02h, 02h, 02h, 0F3h, 0ABh, 5Fh
    db 84h, 0DBh, 74h, 07h, 55h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 14h, 5Eh
    db 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h
?d_006b3d50@@YAXXZ ENDP

; ghidra: FUN_00ab3e30  retail @ 0x006B3E30 size 270
_TEXT ENDS
_TEXT$d00ab3e30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB3E30 size 270
public ?d_006b3e30@@YAXXZ
?d_006b3e30@@YAXXZ PROC
    db 051h, 053h, 055h, 056h, 08Bh, 074h, 024h, 014h, 08Bh, 01Eh, 057h, 08Bh, 07Bh, 008h, 08Bh, 0E9h
    db 057h, 089h, 06Ch, 024h, 014h, 0FFh, 015h
    dd __imp__AIL_init_sample@4
    db 068h
    dd ?j_0001978b@@YAXXZ
    db 057h, 0FFh, 015h
    dd __imp__AIL_register_EOS_callback@8
    db 056h, 08Bh, 0CDh
    call ?j_00016928@@YAXXZ
    db 08Bh, 006h, 08Bh, 048h, 018h, 085h, 0C9h, 00Fh, 084h, 0C8h, 000h, 000h, 000h, 08Bh, 04Bh, 014h
    db 08Bh, 041h, 008h, 08Bh, 0A8h, 08Ch, 000h, 000h, 000h, 08Dh, 051h, 008h, 005h, 08Ch, 000h, 000h
    db 000h, 03Bh, 068h, 004h, 08Bh, 06Ch, 024h, 010h, 074h, 00Ch, 08Bh, 049h, 028h, 051h, 052h, 08Bh
    db 0CDh
    call ?j_0000b43d@@YAXXZ
    db 08Bh, 006h, 083h, 0C0h, 018h, 08Bh, 000h, 085h, 0C0h, 074h, 005h, 08Bh, 040h, 02Ch, 0EBh, 002h
    db 033h, 0C0h, 06Ah, 000h, 050h, 057h, 0FFh, 015h
    dd g_Va0135967C
    db 057h, 0FFh, 015h
    dd g_Va013596B0
    db 08Bh, 053h, 014h, 0B3h, 001h, 088h, 05Ah, 048h, 08Bh, 006h, 08Bh, 048h, 014h, 08Bh, 049h, 028h
    db 083h, 0F9h, 002h, 074h, 00Dh, 03Bh, 08Dh, 004h, 006h, 000h, 000h, 074h, 005h, 088h, 058h, 03Bh
    db 0EBh, 004h, 0C6h, 040h, 03Bh, 000h, 08Bh, 006h, 08Ah, 048h, 039h, 084h, 0C9h, 075h, 015h, 08Ah
    db 048h, 03Ah, 084h, 0C9h, 075h, 00Eh, 08Ah, 048h, 03Bh, 084h, 0C9h, 075h, 007h, 08Ah, 048h, 03Ch
    db 084h, 0C9h, 074h, 00Ch, 08Bh, 050h, 008h, 052h, 0FFh, 015h
    dd __imp__AIL_stop_sample@4
    db 0EBh, 00Ah, 08Bh, 040h, 008h, 050h, 0FFh, 015h
    dd __imp__Rva0135961COff@4
    db 08Bh, 036h, 083h, 0C6h, 018h, 08Bh, 036h, 085h, 0F6h, 075h, 005h, 0BEh
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 056h, 08Bh, 0CDh
    call ?j_00021ff3@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 08Ah, 0C3h, 05Bh, 059h, 0C2h, 004h, 000h, 05Fh, 05Eh, 05Dh, 032h, 0C0h, 05Bh
    db 059h, 0C2h, 004h, 000h
?d_006b3e30@@YAXXZ ENDP
_TEXT$d00ab3e30 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab3f90  retail @ 0x006B3F90 size 196
public ?d_006b3f90@@YAXXZ
?d_006b3f90@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 56h, 8Bh, 30h, 8Bh, 46h, 0Ch, 48h, 57h, 8Bh, 0F9h, 74h
    db 19h, 48h, 74h, 04h, 33h, 0DBh, 0EBh, 15h, 8Bh, 4Eh, 08h, 8Bh, 97h, 44h, 0Bh, 00h
    db 00h, 0C1h, 0E1h, 06h, 8Bh, 5Ch, 11h, 04h, 0EBh, 03h, 8Bh, 5Eh, 08h, 8Bh, 4Eh, 14h
    db 8Bh, 41h, 08h, 8Dh, 51h, 08h, 05h, 8Ch, 00h, 00h, 00h, 55h, 8Bh, 28h, 3Bh, 68h
    db 04h, 5Dh, 74h, 0Ch, 8Bh, 41h, 28h, 50h, 52h, 8Bh, 0CFh, 0E8h, 5Dh, 74h, 95h, 0FFh
    db 8Bh, 4Eh, 14h, 8Bh, 51h, 08h, 0F6h, 42h, 38h, 08h, 75h, 1Dh, 0E8h, 0BEh, 33h, 96h
    db 0FFh, 8Bh, 47h, 0Ch, 0D8h, 58h, 7Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 0Bh, 8Bh, 4Eh
    db 14h, 8Bh, 51h, 08h, 0D9h, 42h, 78h, 0EBh, 06h, 8Bh, 47h, 0Ch, 0DBh, 40h, 38h, 51h
    db 0DCh, 0C0h, 8Bh, 4Eh, 14h, 8Bh, 51h, 08h, 8Bh, 42h, 74h, 0D9h, 1Ch, 24h, 50h, 53h
    db 0FFh, 15h, 40h, 96h, 35h, 01h, 8Bh, 74h, 24h, 14h, 0D9h, 46h, 08h, 8Bh, 16h, 51h
    db 0D9h, 0E0h, 8Bh, 4Eh, 04h, 0D9h, 1Ch, 24h, 51h, 52h, 53h, 0FFh, 15h, 34h, 96h, 35h
    db 01h, 8Bh, 44h, 24h, 10h, 56h, 50h, 8Bh, 0CFh, 0E8h, 6Ch, 51h, 95h, 0FFh, 5Fh, 5Eh
    db 5Bh, 0C2h, 08h, 00h
?d_006b3f90@@YAXXZ ENDP

; ghidra: FUN_00ab4090  retail @ 0x006B4090 size 369
public ?d_006b4090@@YAXXZ
?d_006b4090@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 57h, 8Bh, 7Dh, 00h, 8Bh, 47h
    db 0Ch, 48h, 8Bh, 0D9h, 74h, 19h, 48h, 74h, 04h, 33h, 0F6h, 0EBh, 15h, 8Bh, 47h, 08h
    db 8Bh, 8Bh, 44h, 0Bh, 00h, 00h, 0C1h, 0E0h, 06h, 8Bh, 74h, 08h, 04h, 0EBh, 03h, 8Bh
    db 77h, 08h, 8Bh, 47h, 14h, 8Dh, 54h, 24h, 20h, 52h, 50h, 8Dh, 4Ch, 24h, 18h, 51h
    db 8Bh, 0CBh, 0E8h, 0F7h, 0DDh, 94h, 0FFh, 8Ah, 44h, 24h, 20h, 84h, 0C0h, 0Fh, 84h, 86h
    db 00h, 00h, 00h, 8Bh, 45h, 00h, 8Bh, 48h, 18h, 85h, 0C9h, 74h, 7Ch, 8Bh, 0C1h, 85h
    db 0C0h, 75h, 05h, 0B8h, 50h, 6Eh, 33h, 01h, 50h, 8Bh, 0CBh, 0E8h, 0F3h, 0DEh, 96h, 0FFh
    db 8Bh, 4Dh, 00h, 8Bh, 41h, 18h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 02h, 33h
    db 0C0h, 83h, 78h, 14h, 01h, 74h, 5Eh, 0E8h, 0B4h, 55h, 1Dh, 00h, 84h, 0C0h, 74h, 49h
    db 6Ah, 01h, 0E8h, 79h, 55h, 1Dh, 00h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 83h
    db 0C4h, 04h, 0FFh, 52h, 60h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 01h, 6Ah, 00h, 6Ah
    db 00h, 0FFh, 50h, 6Ch, 8Bh, 7Fh, 14h, 8Bh, 10h, 83h, 0C7h, 14h, 57h, 68h, 0E0h, 0C3h
    db 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 50h, 0E8h, 29h, 2Eh, 96h, 0FFh, 8Bh, 10h, 83h
    db 0C4h, 08h, 6Ah, 02h, 8Bh, 0C8h, 0FFh, 52h, 4Ch, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 5Bh, 83h
    db 0C4h, 0Ch, 0C2h, 04h, 00h, 8Bh, 49h, 18h, 85h, 0C9h, 74h, 05h, 8Bh, 41h, 2Ch, 0EBh
    db 02h, 33h, 0C0h, 50h, 56h, 0FFh, 15h, 48h, 96h, 35h, 01h, 68h, 6Dh, 0BDh, 43h, 00h
    db 56h, 0FFh, 15h, 0FCh, 95h, 35h, 01h, 8Dh, 44h, 24h, 10h, 50h, 55h, 8Bh, 0CBh, 0E8h
    db 75h, 33h, 99h, 0FFh, 6Ah, 01h, 56h, 0FFh, 15h, 50h, 96h, 35h, 01h, 56h, 0FFh, 15h
    db 0ACh, 96h, 35h, 01h, 8Bh, 4Fh, 14h, 0C6h, 41h, 48h, 01h, 8Bh, 45h, 00h, 8Bh, 50h
    db 14h, 8Bh, 4Ah, 28h, 83h, 0F9h, 02h, 74h, 20h, 3Bh, 8Bh, 04h, 06h, 00h, 00h, 74h
    db 18h, 55h, 8Bh, 0CBh, 0C6h, 40h, 3Bh, 01h, 0E8h, 8Bh, 0A4h, 97h, 0FFh, 5Fh, 5Eh, 5Dh
    db 0B0h, 01h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h, 55h, 8Bh, 0CBh, 0C6h, 40h, 3Bh, 00h
    db 0E8h, 73h, 0A4h, 97h, 0FFh, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h
    db 00h
?d_006b4090@@YAXXZ ENDP

; ghidra: FUN_00ab4260  retail @ 0x006B4260 size 130
public ?d_006b4260@@YAXXZ
?d_006b4260@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 24h, 50h, 8Bh, 44h, 24h, 2Ch, 8Dh, 0Ch, 40h, 8Dh
    db 8Ch, 8Eh, 98h, 09h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0E8h, 29h
    db 0D8h, 98h, 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h
    db 08h, 00h
?d_006b4260@@YAXXZ ENDP

; ghidra: FUN_00ab4310  retail @ 0x006B4310 size 156
public ?d_006b4310@@YAXXZ
?d_006b4310@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh
    db 5Ch, 09h, 00h, 00h, 6Ah, 0FFh, 57h, 0C6h, 44h, 24h, 1Ch, 00h, 89h, 7Ch, 24h, 18h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 05h, 0C6h, 44h, 24h
    db 14h, 01h, 8Bh, 44h, 24h, 30h, 8Bh, 6Ch, 24h, 2Ch, 69h, 0C0h, 0C4h, 01h, 00h, 00h
    db 8Bh, 5Ch, 24h, 28h, 55h, 53h, 8Dh, 8Ch, 30h, 0B8h, 00h, 00h, 00h, 0C7h, 44h, 24h
    db 28h, 00h, 00h, 00h, 00h, 0E8h, 35h, 84h, 97h, 0FFh, 8Bh, 4Ch, 24h, 30h, 51h, 55h
    db 53h, 8Bh, 0CEh, 0E8h, 99h, 0F9h, 96h, 0FFh, 8Ah, 44h, 24h, 14h, 84h, 0C0h, 74h, 07h
    db 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 0Ch, 00h
?d_006b4310@@YAXXZ ENDP

; ghidra: FUN_00ab43e0  retail @ 0x006B43E0 size 153
public ?d_006b43e0@@YAXXZ
?d_006b43e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh
    db 5Ch, 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 1Ch, 89h, 7Ch, 24h
    db 18h, 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h
    db 88h, 5Ch, 24h, 14h, 8Bh, 44h, 24h, 2Ch, 8Bh, 6Ch, 24h, 28h, 69h, 0C0h, 0C4h, 01h
    db 00h, 00h, 55h, 8Dh, 8Ch, 30h, 70h, 02h, 00h, 00h, 0C7h, 44h, 24h, 24h, 00h, 00h
    db 00h, 00h, 0E8h, 82h, 6Bh, 95h, 0FFh, 8Bh, 4Ch, 24h, 2Ch, 51h, 68h, 00h, 00h, 80h
    db 0BFh, 55h, 8Bh, 0CEh, 0E8h, 0C8h, 0F8h, 96h, 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h
    db 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h
?d_006b43e0@@YAXXZ ENDP

; ghidra: FUN_00ab44a0  retail @ 0x006B44A0 size 187
public ?d_006b44a0@@YAXXZ
?d_006b44a0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 55h, 57h, 8Bh, 0F9h, 8Bh, 0AFh, 5Ch, 09h
    db 00h, 00h, 6Ah, 0FFh, 55h, 0C6h, 44h, 24h, 14h, 00h, 89h, 6Ch, 24h, 10h, 0FFh, 15h
    db 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 05h, 0C6h, 44h, 24h, 0Ch, 01h
    db 53h, 56h, 8Bh, 5Ch, 24h, 28h, 8Bh, 0C3h, 69h, 0C0h, 0C4h, 01h, 00h, 00h, 8Dh, 0B4h
    db 38h, 70h, 02h, 00h, 00h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 20h, 00h, 00h
    db 00h, 00h, 74h, 21h, 8Bh, 0Eh, 8Bh, 51h, 04h, 52h, 8Bh, 0CEh, 0E8h, 19h, 0FCh, 98h
    db 0FFh, 8Bh, 06h, 89h, 40h, 08h, 8Bh, 06h, 33h, 0C9h, 89h, 48h, 04h, 8Bh, 06h, 89h
    db 40h, 0Ch, 89h, 4Eh, 04h, 53h, 68h, 00h, 00h, 80h, 0BFh, 68h, 50h, 6Eh, 33h, 01h
    db 8Bh, 0CFh, 0E8h, 0EAh, 0F7h, 96h, 0FFh, 8Ah, 44h, 24h, 14h, 84h, 0C0h, 5Eh, 5Bh, 74h
    db 07h, 55h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Dh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006b44a0@@YAXXZ ENDP

; ghidra: FUN_00ab4590  retail @ 0x006B4590 size 481
_TEXT ENDS
_TEXT$d00ab4590 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB4590 size 481
public ?d_006b4590@@YAXXZ
?d_006b4590@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01048ECE
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 080h, 000h, 000h, 000h, 053h, 055h, 056h, 057h, 08Bh, 0F1h, 08Bh, 0AEh, 05Ch, 009h, 000h, 000h
    db 06Ah, 0FFh, 032h, 0DBh, 055h, 088h, 05Ch, 024h, 024h, 089h, 06Ch, 024h, 020h, 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 074h, 006h, 0B3h, 001h, 088h, 05Ch, 024h, 01Ch, 08Bh, 0BCh, 024h
    db 0A0h, 000h, 000h, 000h, 08Bh, 047h, 008h, 085h, 0C0h, 0C7h, 084h, 024h, 098h, 000h, 000h, 000h
    db 000h, 000h, 000h, 000h, 075h, 019h, 08Bh, 006h, 057h, 08Bh, 0CEh, 0FFh, 090h, 0ACh, 000h, 000h
    db 000h, 08Bh, 047h, 008h, 085h, 0C0h, 075h, 007h, 084h, 0DBh, 0E9h, 044h, 001h, 000h, 000h, 08Bh
    db 01Eh, 08Bh, 0CFh
    call ?j_00015a69@@YAXXZ
    db 050h, 08Bh, 0CEh, 0FFh, 093h, 0B8h, 000h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 024h, 001h, 000h
    db 000h, 057h, 08Dh, 04Ch, 024h, 024h
    call ?j_00047b27@@YAXXZ
    db 0BBh, 001h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 020h, 088h, 09Ch, 024h, 098h, 000h, 000h, 000h
    call ?j_00046a33@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h
    call ?j_0003828a@@YAXXZ
    db 08Bh, 04Ch, 024h, 048h, 069h, 0C9h, 0C4h, 001h, 000h, 000h, 08Dh, 084h, 031h, 0B8h, 000h, 000h
    db 000h, 08Dh, 0B8h, 0B8h, 001h, 000h, 000h, 08Dh, 054h, 024h, 034h, 052h, 08Bh, 0CFh
    call ?j_00025cca@@YAXXZ
    db 03Bh, 007h, 074h, 011h, 083h, 0C0h, 014h, 074h, 00Ch, 08Bh, 000h, 050h, 08Dh, 04Ch, 024h, 024h
    call ?j_0001147d@@YAXXZ
    db 08Dh, 04Ch, 024h, 010h, 051h, 08Dh, 04Ch, 024h, 024h
    call ?j_0000b7d5@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 0C6h, 084h, 024h, 098h, 000h, 000h, 000h, 002h, 074h, 005h
    db 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 06Ah, 000h, 053h, 050h, 0FFh, 015h
    dd g_Va013595E4
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 06Bh, 08Dh, 054h, 024h, 010h, 052h, 08Bh, 0CEh
    call ?j_00021ff3@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00017f85@@YAXXZ
    db 08Bh, 044h, 024h, 048h, 069h, 0C0h, 0C4h, 001h, 000h, 000h, 068h, 000h, 000h, 000h, 03Fh, 08Dh
    db 04Ch, 024h, 024h, 0D9h, 084h, 030h, 0ACh, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 018h
    call ?j_0000cd3d@@YAXXZ
    db 0D8h, 04Ch, 024h, 018h, 051h, 0D9h, 01Ch, 024h, 057h, 0FFh, 015h
    dd g_Va013595E8
    db 08Bh, 0B6h, 0BCh, 009h, 000h, 000h, 06Ah, 00Ch
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Dh, 048h, 008h, 083h, 0C4h, 004h, 085h, 0C9h, 074h, 002h, 089h, 039h, 08Bh, 04Eh, 004h, 089h
    db 030h, 089h, 048h, 004h, 089h, 001h, 089h, 046h, 004h, 08Dh, 04Ch, 024h, 010h, 088h, 09Ch, 024h
    db 098h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 020h, 0C6h, 084h, 024h, 098h, 000h, 000h, 000h, 000h
    call ?j_00026f35@@YAXXZ
    db 08Ah, 044h, 024h, 01Ch, 084h, 0C0h, 074h, 007h, 055h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 08Bh, 08Ch, 024h, 090h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 08Ch, 000h, 000h, 000h, 0C2h, 004h, 000h
?d_006b4590@@YAXXZ ENDP
_TEXT$d00ab4590 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab47f0  retail @ 0x006B47F0 size 150
public ?d_006b47f0@@YAXXZ
?d_006b47f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 8Eh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 94h, 0Ah, 00h, 00h, 84h, 0C9h
    db 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 74h, 1Fh, 0C6h, 05h, 44h, 0A1h, 2Bh, 01h
    db 00h, 0E8h, 66h, 0B3h, 97h, 0FFh, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h
    db 00h, 00h, 00h, 00h, 0E8h, 19h, 64h, 99h, 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h
    db 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_006b47f0@@YAXXZ ENDP

; ghidra: FUN_00ab48b0  retail @ 0x006B48B0 size 150
public ?d_006b48b0@@YAXXZ
?d_006b48b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 18h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 94h, 0Ah, 00h, 00h, 84h, 0C9h
    db 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 74h, 1Fh, 0C6h, 05h, 44h, 0A1h, 2Bh, 01h
    db 01h, 0E8h, 0A6h, 0B2h, 97h, 0FFh, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h
    db 00h, 00h, 00h, 00h, 0E8h, 59h, 63h, 99h, 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h
    db 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_006b48b0@@YAXXZ ENDP

; ghidra: FUN_00ab4970  retail @ 0x006B4970 size 144
public ?d_006b4970@@YAXXZ
?d_006b4970@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 6Ah, 00h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 0A3h, 2Ch, 0A1h, 2Bh, 01h, 0E8h, 71h, 35h, 99h, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 0A1h, 62h, 99h
    db 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch
    db 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b4970@@YAXXZ ENDP

; ghidra: FUN_00ab4a30  retail @ 0x006B4A30 size 144
public ?d_006b4a30@@YAXXZ
?d_006b4a30@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 6Ah, 01h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 0A3h, 30h, 0A1h, 2Bh, 01h, 0E8h, 0B1h, 34h, 99h, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 0E1h, 61h, 99h
    db 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch
    db 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b4a30@@YAXXZ ENDP

; ghidra: FUN_00ab4af0  retail @ 0x006B4AF0 size 144
public ?d_006b4af0@@YAXXZ
?d_006b4af0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 78h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 6Ah, 02h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 0A3h, 34h, 0A1h, 2Bh, 01h, 0E8h, 0F1h, 33h, 99h, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 21h, 61h, 99h
    db 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch
    db 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b4af0@@YAXXZ ENDP

; ghidra: FUN_00ab4bb0  retail @ 0x006B4BB0 size 144
public ?d_006b4bb0@@YAXXZ
?d_006b4bb0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 6Ah, 04h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 0A3h, 3Ch, 0A1h, 2Bh, 01h, 0E8h, 31h, 33h, 99h, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 61h, 60h, 99h
    db 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch
    db 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b4bb0@@YAXXZ ENDP

; ghidra: FUN_00ab4c70  retail @ 0x006B4C70 size 144
public ?d_006b4c70@@YAXXZ
?d_006b4c70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 8Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 6Ah, 03h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h
    db 00h, 0A3h, 38h, 0A1h, 2Bh, 01h, 0E8h, 71h, 32h, 99h, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 0A1h, 5Fh, 99h
    db 0FFh, 84h, 0DBh, 74h, 07h, 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch
    db 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b4c70@@YAXXZ ENDP

; ghidra: FUN_00ab5890  retail @ 0x006B5890 size 89
public ?d_006b5890@@YAXXZ
?d_006b5890@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 90h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 78h, 0Bh, 00h, 00h, 0E8h, 80h, 0C6h, 1Ch, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 16h, 8Bh, 0C8h, 0E8h, 3Ah, 98h, 97h, 0FFh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Bh, 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006b5890@@YAXXZ ENDP

; ghidra: FUN_00ab5900  retail @ 0x006B5900 size 304
_TEXT ENDS
_TEXT$d00ab5900 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB5900 size 304
public ?d_006b5900@@YAXXZ
?d_006b5900@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01049040
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 053h, 055h, 056h, 057h, 08Bh, 07Ch, 024h, 020h
    db 08Bh, 047h, 008h, 08Dh, 077h, 008h, 0BBh, 001h, 000h, 000h, 000h, 088h, 058h, 048h, 08Bh, 0E9h
    db 08Bh, 00Eh, 08Bh, 041h, 060h, 083h, 0F8h, 002h, 075h, 006h, 039h, 05Ch, 024h, 028h, 075h, 005h
    call ?j_0001079e@@YAXXZ
    db 08Bh, 00Eh
    call ?j_00046a33@@YAXXZ
    db 08Bh, 006h, 08Bh, 048h, 060h, 083h, 0F9h, 002h, 075h, 033h, 08Bh, 047h, 024h, 085h, 0C0h, 08Dh
    db 05Fh, 024h, 075h, 060h, 08Bh, 08Dh, 000h, 00Bh, 000h, 000h, 06Ah, 000h, 056h, 08Dh, 044h, 024h
    db 028h, 050h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Bh, 0CBh, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h, 0EBh, 02Ah, 083h, 078h, 060h, 003h, 074h, 031h, 06Ah, 000h, 056h, 08Dh
    db 04Ch, 024h, 030h, 051h, 08Bh, 08Dh, 000h, 00Bh, 000h, 000h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Dh, 04Fh, 020h, 089h, 05Ch, 024h, 01Ch
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 028h, 0C7h, 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000298e8@@YAXXZ
    db 08Bh, 074h, 024h, 024h, 08Dh, 05Fh, 01Ch, 056h, 08Bh, 0CBh
    call ?j_0000268a@@YAXXZ
    db 08Bh, 00Eh, 033h, 0D2h, 03Bh, 0CAh, 075h, 01Bh, 089h, 057h, 02Ch, 089h, 057h, 028h, 08Bh, 04Ch
    db 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch
    db 0C2h, 00Ch, 000h, 08Bh, 01Bh, 03Bh, 0DAh, 074h, 003h, 08Bh, 053h, 02Ch, 08Bh, 041h, 00Ch, 02Bh
    db 0C2h, 089h, 047h, 02Ch, 08Bh, 051h, 010h, 003h, 0D0h, 089h, 057h, 028h, 08Bh, 006h, 085h, 0C0h
    db 075h, 005h, 0B8h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 050h, 08Bh, 0CDh
    call ?j_00021ff3@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 00Ch, 0C2h, 00Ch, 000h
?d_006b5900@@YAXXZ ENDP
_TEXT$d00ab5900 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab5a80  retail @ 0x006B5A80 size 1480
_TEXT ENDS
_TEXT$d00ab5a80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB5A80 size 1480
public ?d_006b5a80@@YAXXZ
?d_006b5a80@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va010490BA
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 038h, 053h, 055h, 033h, 0C0h, 056h, 089h, 044h, 024h, 00Ch, 08Bh, 06Ch, 024h, 054h, 057h, 089h
    db 04Ch, 024h, 014h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 054h, 024h, 05Ch, 08Bh, 075h, 030h
    db 040h, 08Bh, 0FAh, 02Bh, 0FEh, 089h, 044h, 024h, 044h, 089h, 07Ch, 024h, 018h, 00Fh, 084h, 069h
    db 005h, 000h, 000h, 083h, 0F8h, 00Fh, 00Fh, 084h, 058h, 005h, 000h, 000h, 08Bh, 045h, 01Ch, 085h
    db 0C0h, 00Fh, 085h, 08Ah, 004h, 000h, 000h, 08Bh, 045h, 008h, 083h, 078h, 060h, 003h, 08Dh, 05Dh
    db 008h, 075h, 033h, 08Bh, 0CFh, 08Bh, 07Dh, 014h, 003h, 0FEh, 08Bh, 0F1h, 0C1h, 0E9h, 002h, 033h
    db 0C0h, 0F3h, 0ABh, 08Bh, 0CEh, 083h, 0E1h, 003h, 0F3h, 0AAh, 03Bh, 055h, 018h, 089h, 055h, 030h
    db 00Fh, 082h, 05Bh, 004h, 000h, 000h, 0C6h, 045h, 03Ch, 001h, 0C7h, 045h, 030h, 000h, 000h, 000h
    db 000h, 0E9h, 04Bh, 004h, 000h, 000h, 08Bh, 050h, 060h, 0BFh, 002h, 000h, 000h, 000h, 03Bh, 0D7h
    db 00Fh, 085h, 034h, 001h, 000h, 000h, 08Bh, 055h, 024h, 085h, 0D2h, 08Dh, 075h, 024h, 074h, 041h
    db 080h, 07Ah, 041h, 000h, 074h, 03Bh, 0C6h, 040h, 048h, 001h, 08Dh, 044h, 024h, 01Ch, 050h, 08Bh
    db 0CEh
    call ?j_000334b0@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 06Ah, 001h, 050h, 055h, 0C7h, 044h, 024h, 05Ch, 000h, 000h, 000h, 000h
    call ?j_0001dff2@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000351b6@@YAXXZ
    db 0E9h, 082h, 001h, 000h, 000h, 083h, 03Eh, 000h, 00Fh, 085h, 081h, 000h, 000h, 000h, 08Bh, 089h
    db 000h, 00Bh, 000h, 000h, 057h, 053h, 08Dh, 054h, 024h, 028h, 052h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 054h, 001h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000298e8@@YAXXZ
    db 08Bh, 006h, 085h, 0C0h, 00Fh, 084h, 03Ch, 001h, 000h, 000h, 08Ah, 048h, 041h, 084h, 0C9h, 00Fh
    db 084h, 031h, 001h, 000h, 000h, 08Bh, 003h, 0C6h, 040h, 048h, 001h, 08Dh, 044h, 024h, 024h, 050h
    db 08Bh, 0CEh
    call ?j_000334b0@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 06Ah, 001h, 050h, 055h, 089h, 07Ch, 024h, 05Ch
    call ?j_0001dff2@@YAXXZ
    db 08Dh, 04Ch, 024h, 024h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000351b6@@YAXXZ
    db 0E9h, 0F8h, 000h, 000h, 000h, 08Bh, 016h, 085h, 0D2h, 074h, 006h, 080h, 07Ah, 042h, 000h, 074h
    db 00Eh, 06Ah, 003h, 08Bh, 0C8h
    call ?j_00023911@@YAXXZ
    db 0E9h, 0DEh, 000h, 000h, 000h, 08Bh, 006h, 085h, 0C0h, 074h, 009h, 039h, 078h, 03Ch, 00Fh, 08Dh
    db 0CFh, 000h, 000h, 000h, 08Bh, 006h, 085h, 0C0h, 075h, 005h, 0B8h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 08Bh, 089h, 000h, 00Bh, 000h, 000h, 057h, 050h, 08Dh, 054h, 024h, 030h, 052h
    call ?j_0003214b@@YAXXZ
    db 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 054h, 003h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 028h, 0E9h, 08Ch, 000h, 000h, 000h, 083h, 078h, 060h, 003h, 00Fh, 084h, 08Fh
    db 000h, 000h, 000h, 08Bh, 045h, 020h, 085h, 0C0h, 08Dh, 075h, 020h, 074h, 007h, 08Ah, 050h, 042h
    db 084h, 0D2h, 074h, 028h, 08Bh, 089h, 000h, 00Bh, 000h, 000h, 057h, 053h, 08Dh, 044h, 024h, 034h
    db 050h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 054h, 004h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0EBh, 049h, 08Bh, 006h, 085h, 0C0h, 074h, 007h, 08Ah, 050h, 041h, 084h
    db 0D2h, 075h, 049h, 08Bh, 006h, 085h, 0C0h, 074h, 005h, 039h, 078h, 03Ch, 07Dh, 03Eh, 08Bh, 006h
    db 085h, 0C0h, 075h, 005h, 0B8h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 08Bh, 089h, 000h, 00Bh, 000h, 000h, 057h, 050h, 08Dh, 054h, 024h, 038h, 052h
    call ?j_0003214b@@YAXXZ
    db 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 054h, 005h, 000h, 000h, 000h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 030h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000298e8@@YAXXZ
    db 08Bh, 045h, 020h, 085h, 0C0h, 08Dh, 04Dh, 020h, 074h, 053h, 08Ah, 050h, 041h, 084h, 0D2h, 074h
    db 04Ch, 08Bh, 013h, 08Bh, 042h, 060h, 02Bh, 0C7h, 074h, 003h, 048h, 0EBh, 00Eh, 08Bh, 045h, 01Ch
    db 085h, 0C0h, 075h, 044h, 08Bh, 052h, 008h, 0F6h, 042h, 03Ch, 001h, 074h, 030h, 08Dh, 044h, 024h
    db 034h, 050h
    call ?j_000334b0@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 06Ah, 000h, 050h, 055h, 0C7h, 044h, 024h, 05Ch, 006h, 000h, 000h, 000h
    call ?j_0001dff2@@YAXXZ
    db 08Dh, 04Ch, 024h, 034h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_000351b6@@YAXXZ
    db 08Bh, 045h, 01Ch, 085h, 0C0h, 00Fh, 084h, 006h, 002h, 000h, 000h, 08Bh, 045h, 01Ch, 085h, 0C0h
    db 074h, 009h, 083h, 0C0h, 008h, 089h, 044h, 024h, 058h, 0EBh, 008h, 0C7h, 044h, 024h, 058h, 000h
    db 000h, 000h, 000h, 08Bh, 04Ch, 024h, 058h, 08Bh, 051h, 010h, 03Bh, 055h, 038h, 00Fh, 084h, 0EAh
    db 000h, 000h, 000h
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 00Fh, 084h, 0B4h, 000h, 000h, 000h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 083h, 0C4h, 004h, 0FFh, 050h, 060h, 08Bh, 00Bh, 08Dh, 054h, 024h, 03Ch, 052h
    call ?j_0000fa1f@@YAXXZ
    db 089h, 044h, 024h, 038h, 08Bh, 074h, 024h, 010h, 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 06Ah, 000h, 083h, 0CEh, 001h, 06Ah, 000h, 0C7h, 044h, 024h, 058h, 007h, 000h, 000h
    db 000h, 089h, 074h, 024h, 018h, 0FFh, 050h, 06Ch, 08Bh, 010h, 08Bh, 03Bh, 068h
    dd g_Va0111C4F0
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 0F0h, 08Bh, 047h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h
    db 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 038h, 08Bh, 006h, 068h
    dd g_Va0111C4DC
    db 08Bh, 0CEh, 0FFh, 050h, 038h, 08Bh, 04Ch, 024h, 038h, 08Bh, 0F0h, 08Bh, 001h, 085h, 0C0h, 074h
    db 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 038h, 08Bh, 006h, 068h
    dd g_Va01076C28
    db 08Bh, 0CEh, 0FFh, 050h, 038h, 08Bh, 010h, 06Ah, 002h, 08Bh, 0C8h, 0FFh, 052h, 04Ch, 0BFh, 002h
    db 000h, 000h, 000h, 0F6h, 044h, 024h, 010h, 001h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh
    db 074h, 014h, 08Bh, 044h, 024h, 010h, 083h, 0E0h, 0FEh, 08Dh, 04Ch, 024h, 03Ch, 089h, 044h, 024h
    db 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 045h, 028h, 089h, 045h, 02Ch, 08Bh, 04Ch, 024h, 058h, 08Bh, 051h, 00Ch, 03Bh, 055h, 034h
    db 00Fh, 084h, 0E4h, 000h, 000h, 000h
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 00Fh, 084h, 0AEh, 000h, 000h, 000h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 083h, 0C4h, 004h, 0FFh, 050h, 060h, 08Bh, 00Bh, 08Dh, 054h, 024h, 040h, 052h
    call ?j_0000fa1f@@YAXXZ
    db 089h, 044h, 024h, 058h, 08Bh, 074h, 024h, 010h, 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 06Ah, 000h, 00Bh, 0F7h, 06Ah, 000h, 0C7h, 044h, 024h, 058h, 008h, 000h, 000h, 000h
    db 089h, 074h, 024h, 018h, 0FFh, 050h, 06Ch, 08Bh, 010h, 08Bh, 03Bh, 068h
    dd g_Va0111C410
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 0F0h, 08Bh, 047h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h
    db 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 038h, 08Bh, 006h, 068h
    dd g_Va0111C4DC
    db 08Bh, 0CEh, 0FFh, 050h, 038h, 08Bh, 04Ch, 024h, 058h, 08Bh, 0F0h, 08Bh, 001h, 085h, 0C0h, 074h
    db 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 038h, 08Bh, 006h, 068h
    dd g_Va01076C28
    db 08Bh, 0CEh, 0FFh, 050h, 038h, 08Bh, 010h, 06Ah, 002h, 08Bh, 0C8h, 0FFh, 052h, 04Ch, 0F6h, 044h
    db 024h, 010h, 002h, 0C7h, 044h, 024h, 050h, 0FFh, 0FFh, 0FFh, 0FFh, 074h, 014h, 08Bh, 044h, 024h
    db 010h, 083h, 0E0h, 0FDh, 08Dh, 04Ch, 024h, 040h, 089h, 044h, 024h, 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 045h, 028h, 089h, 045h, 02Ch, 08Bh, 045h, 01Ch, 085h, 0C0h, 08Dh, 05Dh, 01Ch, 00Fh, 084h
    db 0BDh, 000h, 000h, 000h, 08Bh, 075h, 02Ch, 08Bh, 045h, 028h, 08Bh, 04Ch, 024h, 018h, 02Bh, 0C6h
    db 03Bh, 0C1h, 089h, 044h, 024h, 058h, 08Dh, 07Ch, 024h, 058h, 07Ch, 004h, 08Dh, 07Ch, 024h, 018h
    db 08Bh, 00Bh, 085h, 0C9h, 074h, 005h, 08Bh, 051h, 02Ch, 0EBh, 002h, 033h, 0D2h, 08Bh, 00Fh, 08Bh
    db 07Dh, 014h, 003h, 0F2h, 003h, 07Dh, 030h, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 0F3h, 0A5h, 08Bh, 0CAh
    db 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 04Ch, 024h, 018h, 03Bh, 0C8h, 07Ch, 038h, 08Bh, 055h, 030h
    db 08Bh, 075h, 02Ch, 08Bh, 04Dh, 018h, 003h, 0D0h, 003h, 0F0h, 08Bh, 0C2h, 03Bh, 0C1h, 089h, 075h
    db 02Ch, 089h, 055h, 030h, 072h, 00Bh, 0C7h, 045h, 030h, 000h, 000h, 000h, 000h, 0C6h, 045h, 03Ch
    db 001h, 08Bh, 0CBh
    call ?j_000311bf@@YAXXZ
    db 08Bh, 044h, 024h, 044h, 08Bh, 04Ch, 024h, 014h, 0E9h, 0B9h, 0FAh, 0FFh, 0FFh, 08Bh, 055h, 02Ch
    db 08Bh, 044h, 024h, 05Ch, 003h, 0D1h, 03Bh, 045h, 018h, 089h, 055h, 02Ch, 089h, 045h, 030h, 072h
    db 028h, 05Fh, 05Eh, 0C6h, 045h, 03Ch, 001h, 0C7h, 045h, 030h, 000h, 000h, 000h, 000h, 05Dh, 05Bh
    db 08Bh, 04Ch, 024h, 038h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 044h, 0C2h, 008h
    db 000h, 08Dh, 04Dh, 01Ch
    call ?j_000311bf@@YAXXZ
    db 08Bh, 04Ch, 024h, 048h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 044h, 0C2h, 008h, 000h
?d_006b5a80@@YAXXZ ENDP
_TEXT$d00ab5a80 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab61c0  retail @ 0x006B61C0 size 558
_TEXT ENDS
_TEXT$d00ab61c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB61C0 size 558
public ?d_006b61c0@@YAXXZ
?d_006b61c0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01049100
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 020h, 0A1h
    dd g_Va012F7764
    db 053h, 055h, 056h, 08Bh, 0D9h, 057h, 089h, 05Ch, 024h, 010h, 08Bh, 0E8h, 089h, 044h, 024h, 024h
    db 08Dh, 049h, 000h, 08Bh, 083h, 048h, 00Bh, 000h, 000h, 045h, 03Bh, 0E8h, 089h, 06Ch, 024h, 014h
    db 07Ch, 00Ch, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 08Bh, 06Ch, 024h, 014h, 08Bh, 08Bh
    db 044h, 00Bh, 000h, 000h, 08Bh, 0F5h, 0C1h, 0E6h, 006h, 08Ah, 004h, 00Eh, 003h, 0F1h, 084h, 0C0h
    db 00Fh, 084h, 074h, 001h, 000h, 000h, 0C6h, 044h, 024h, 02Ch, 000h, 08Bh, 0BBh, 05Ch, 009h, 000h
    db 000h, 06Ah, 000h, 057h, 0C7h, 044h, 024h, 040h, 000h, 000h, 000h, 000h, 089h, 07Ch, 024h, 028h
    db 089h, 07Ch, 024h, 030h, 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 00Fh, 084h, 04Fh, 001h, 000h, 000h, 080h, 03Eh, 000h, 0C6h, 044h
    db 024h, 02Ch, 001h, 089h, 02Dh
    dd g_Va012F7764
    db 075h, 014h, 057h, 0C7h, 044h, 024h, 03Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 0E9h, 01Ch, 001h, 000h, 000h, 08Ah, 046h, 001h, 084h, 0C0h, 074h, 021h, 08Bh, 046h, 004h, 050h
    db 0FFh, 015h
    dd ?g_Rva13596C0@@3P6GXPAX@ZA
    db 057h, 0C6h, 006h, 000h, 0C7h, 044h, 024h, 03Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 0E9h, 0F4h, 000h, 000h, 000h, 08Bh, 04Eh, 008h, 08Ah, 041h, 045h, 084h, 0C0h, 08Dh, 06Eh, 008h
    db 074h, 04Ch, 08Bh, 046h, 024h, 085h, 0C0h, 08Dh, 07Eh, 024h, 075h, 042h, 083h, 079h, 060h, 001h
    db 075h, 03Ch
    call ?j_0001079e@@YAXXZ
    db 08Bh, 045h, 000h, 083h, 078h, 060h, 002h, 075h, 02Eh, 06Ah, 001h, 055h, 08Dh, 04Ch, 024h, 020h
    db 051h, 08Bh, 08Bh, 000h, 00Bh, 000h, 000h
    call ?j_0003aa6c@@YAXXZ
    db 050h, 08Bh, 0CFh, 0C6h, 044h, 024h, 03Ch, 001h
    call ?j_0004066f@@YAXXZ
    db 08Dh, 04Ch, 024h, 018h, 0C6h, 044h, 024h, 038h, 000h
    call ?j_000298e8@@YAXXZ
    db 08Bh, 056h, 004h, 052h, 0FFh, 015h
    dd g_Va01359584
    db 08Bh, 04Eh, 018h, 08Bh, 0F8h, 03Bh, 0F9h, 072h, 002h, 033h, 0FFh, 08Bh, 046h, 030h, 03Bh, 0F8h
    db 08Ah, 05Eh, 03Ch, 00Fh, 086h, 09Ah, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 057h, 056h
    call ?j_00029910@@YAXXZ
    db 08Ah, 046h, 03Ch, 084h, 0C0h, 074h, 04Bh, 084h, 0DBh, 075h, 047h, 08Bh, 04Eh, 004h, 051h, 0FFh
    db 015h
    dd g_Va013596AC
    db 08Bh, 076h, 010h, 085h, 0F6h, 089h, 074h, 024h, 01Ch, 074h, 00Ah, 08Dh, 056h, 004h, 052h, 0FFh
    db 015h
    dd __imp__InterlockedIncrement@4
    db 08Bh, 04Ch, 024h, 010h, 08Dh, 044h, 024h, 01Ch, 050h
    call ?j_0002e668@@YAXXZ
    db 085h, 0F6h, 074h, 016h, 08Dh, 04Eh, 004h, 051h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 008h, 08Bh, 016h, 06Ah, 001h, 08Bh, 0CEh, 0FFh, 012h, 08Bh, 044h, 024h, 020h
    db 050h, 0C7h, 044h, 024h, 03Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 08Bh, 06Ch, 024h, 014h, 08Bh, 05Ch, 024h, 010h, 0C6h, 044h, 024h, 02Ch, 000h, 03Bh, 06Ch, 024h
    db 024h, 00Fh, 085h, 04Fh, 0FEh, 0FFh, 0FFh, 08Bh, 04Ch, 024h, 030h, 05Fh, 05Eh, 05Dh, 05Bh, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 02Ch, 0C3h, 00Fh, 083h, 06Bh, 0FFh, 0FFh, 0FFh
    db 051h, 08Bh, 04Ch, 024h, 014h, 056h
    call ?j_00029910@@YAXXZ
    db 08Bh, 046h, 01Ch, 085h, 0C0h, 00Fh, 085h, 04Ah, 0FFh, 0FFh, 0FFh, 08Bh, 06Dh, 000h, 083h, 07Dh
    db 060h, 003h, 00Fh, 085h, 03Dh, 0FFh, 0FFh, 0FFh, 08Bh, 046h, 004h, 06Ah, 001h, 050h, 0FFh, 015h
    dd g_Va01359650
    db 0C6h, 006h, 000h, 0EBh, 089h
?d_006b61c0@@YAXXZ ENDP
_TEXT$d00ab61c0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab64a0  retail @ 0x006B64A0 size 404
public ?d_006b64a0@@YAXXZ
?d_006b64a0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 53h, 56h, 8Bh, 74h, 24h, 24h, 57h, 8Bh, 0F9h, 8Bh, 0CEh, 0E8h, 0CDh
    db 8Eh, 95h, 0FFh, 84h, 0C0h, 0B3h, 08h, 0Fh, 84h, 0D6h, 00h, 00h, 00h, 8Bh, 46h, 08h
    db 84h, 58h, 38h, 0Fh, 85h, 0CAh, 00h, 00h, 00h, 83h, 78h, 34h, 04h, 0Fh, 84h, 0C0h
    db 00h, 00h, 00h, 0D9h, 40h, 18h, 8Bh, 4Fh, 0Ch, 0D8h, 59h, 7Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 01h, 0Fh, 84h, 0ACh, 00h, 00h, 00h, 8Dh, 54h, 24h, 28h, 52h, 8Dh, 44h, 24h, 1Ch
    db 50h, 8Bh, 0CEh, 0E8h, 0E9h, 35h, 97h, 0FFh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 92h, 0Ch, 01h
    db 00h, 00h, 0D9h, 00h, 8Bh, 48h, 04h, 8Bh, 50h, 08h, 8Ah, 44h, 24h, 28h, 84h, 0C0h
    db 89h, 4Ch, 24h, 10h, 89h, 54h, 24h, 14h, 75h, 0Dh, 0DDh, 0D8h, 5Fh, 5Eh, 32h, 0C0h
    db 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 0D8h, 64h, 24h, 18h, 8Bh, 46h, 08h, 0D9h, 44h
    db 24h, 10h, 8Ah, 48h, 38h, 84h, 0CBh, 0D8h, 64h, 24h, 1Ch, 0D9h, 44h, 24h, 14h, 0D8h
    db 64h, 24h, 20h, 74h, 08h, 8Bh, 47h, 0Ch, 0DBh, 40h, 38h, 0EBh, 03h, 0D9h, 40h, 78h
    db 0D9h, 0C1h, 0D8h, 0CAh, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0C4h, 0D8h, 0CDh, 0DEh, 0C1h
    db 0D9h, 0C1h, 0D8h, 0CAh, 0DEh, 0D9h, 0DDh, 0D8h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h
    db 41h, 0DDh, 0D8h, 7Bh, 0A7h, 8Bh, 17h, 56h, 8Bh, 0CFh, 0FFh, 92h, 88h, 01h, 00h, 00h
    db 84h, 0C0h, 74h, 0Fh, 5Fh, 0C6h, 46h, 47h, 01h, 5Eh, 32h, 0C0h, 5Bh, 83h, 0C4h, 18h
    db 0C2h, 04h, 00h, 56h, 8Bh, 0CFh, 0E8h, 26h, 6Fh, 96h, 0FFh, 84h, 0C0h, 74h, 14h, 8Bh
    db 46h, 08h, 8Bh, 40h, 3Ch, 5Fh, 0C1h, 0E8h, 03h, 5Eh, 24h, 01h, 5Bh, 83h, 0C4h, 18h
    db 0C2h, 04h, 00h, 56h, 8Bh, 0CFh, 0E8h, 71h, 0CDh, 95h, 0FFh, 84h, 0C0h, 0Fh, 85h, 59h
    db 0FFh, 0FFh, 0FFh, 8Bh, 46h, 08h, 84h, 58h, 3Ch, 75h, 22h, 83h, 0B8h, 84h, 00h, 00h
    db 00h, 02h, 75h, 19h, 8Bh, 0CEh, 0E8h, 0A5h, 8Dh, 95h, 0FFh, 84h, 0C0h, 74h, 19h, 8Bh
    db 8Fh, 14h, 06h, 00h, 00h, 3Bh, 8Fh, 0Ch, 06h, 00h, 00h, 73h, 19h, 5Fh, 5Eh, 0B0h
    db 01h, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 8Bh, 97h, 10h, 06h, 00h, 00h, 3Bh, 97h
    db 08h, 06h, 00h, 00h, 72h, 0E7h, 56h, 8Bh, 0CFh, 0E8h, 0A2h, 6Bh, 96h, 0FFh, 84h, 0C0h
    db 75h, 0DBh, 8Bh, 46h, 08h, 84h, 58h, 3Ch, 0Fh, 84h, 0FEh, 0FEh, 0FFh, 0FFh, 56h, 8Bh
    db 0CFh, 0E8h, 0E3h, 10h, 98h, 0FFh, 5Fh, 84h, 0C0h, 5Eh, 0Fh, 95h, 0C0h, 5Bh, 83h, 0C4h
    db 18h, 0C2h, 04h, 00h
?d_006b64a0@@YAXXZ ENDP

; ghidra: FUN_00ab6910  retail @ 0x006B6910 size 171
public ?d_006b6910@@YAXXZ
?d_006b6910@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 91h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 57h, 8Bh, 0F1h, 8Bh, 0BEh, 5Ch
    db 09h, 00h, 00h, 6Ah, 0FFh, 32h, 0DBh, 57h, 88h, 5Ch, 24h, 18h, 89h, 7Ch, 24h, 14h
    db 0FFh, 15h, 64h, 8Fh, 35h, 01h, 3Dh, 02h, 01h, 00h, 00h, 74h, 06h, 0B3h, 01h, 88h
    db 5Ch, 24h, 10h, 8Bh, 44h, 24h, 2Ch, 3Bh, 86h, 04h, 06h, 00h, 00h, 0C7h, 44h, 24h
    db 24h, 00h, 00h, 00h, 00h, 74h, 35h, 89h, 86h, 04h, 06h, 00h, 00h, 8Bh, 86h, 54h
    db 0Bh, 00h, 00h, 50h, 8Bh, 0CEh, 0C6h, 86h, 31h, 06h, 00h, 00h, 01h, 0E8h, 8Ah, 0F5h
    db 98h, 0FFh, 8Bh, 0CEh, 0E8h, 82h, 59h, 95h, 0FFh, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh
    db 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0E8h, 0E6h, 42h, 99h, 0FFh, 84h, 0DBh, 74h, 07h
    db 57h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_006b6910@@YAXXZ ENDP

; ghidra: FUN_00ab78d0  retail @ 0x006B78D0 size 423
public ?d_006b78d0@@YAXXZ
?d_006b78d0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0B8h, 91h, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 56h, 6Ah, 00h, 8Bh, 0F1h, 0FFh, 15h, 54h
    db 93h, 35h, 01h, 89h, 86h, 68h, 0Bh, 00h, 00h, 89h, 96h, 6Ch, 0Bh, 00h, 00h, 0A1h
    db 0C8h, 0D5h, 2Eh, 01h, 8Ah, 88h, 6Ch, 0Ah, 00h, 00h, 83h, 0C4h, 04h, 84h, 0C9h, 0Fh
    db 84h, 52h, 01h, 00h, 00h, 57h, 68h, 60h, 0C6h, 11h, 01h, 0FFh, 15h, 78h, 96h, 35h
    db 01h, 0E8h, 8Ah, 11h, 34h, 00h, 0FFh, 15h, 0BCh, 96h, 35h, 01h, 8Bh, 46h, 0Ch, 8Bh
    db 48h, 24h, 8Bh, 50h, 20h, 51h, 8Bh, 48h, 1Ch, 52h, 0Fh, 0B6h, 50h, 19h, 0Fh, 0B6h
    db 40h, 18h, 51h, 52h, 50h, 0FFh, 15h, 0F0h, 95h, 35h, 01h, 6Ah, 00h, 6Ah, 00h, 8Dh
    db 8Eh, 60h, 09h, 00h, 00h, 51h, 8Bh, 0F8h, 0FFh, 15h, 0E0h, 95h, 35h, 01h, 85h, 0FFh
    db 8Bh, 0CEh, 74h, 07h, 0E8h, 0C6h, 1Dh, 98h, 0FFh, 0EBh, 0Ch, 8Bh, 16h, 6Ah, 1Fh, 6Ah
    db 00h, 0FFh, 92h, 0BCh, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 08h, 0E8h, 0BCh, 0F7h, 97h, 0FFh
    db 8Dh, 4Ch, 24h, 08h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0E8h, 03h, 0C8h, 97h
    db 0FFh, 8Bh, 0CEh, 50h, 0E8h, 0ADh, 76h, 96h, 0FFh, 8Bh, 0CEh, 0E8h, 0EEh, 50h, 97h, 0FFh
    db 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 00h, 01h, 00h, 00h, 68h, 21h, 02h, 41h, 00h, 0FFh
    db 15h, 08h, 96h, 35h, 01h, 8Bh, 0C8h, 83h, 0F9h, 0FFh, 89h, 8Eh, 4Ch, 0Bh, 00h, 00h
    db 75h, 44h, 0E8h, 09h, 1Dh, 1Dh, 00h, 84h, 0C0h, 74h, 75h, 6Ah, 01h, 0E8h, 0CEh, 1Ch
    db 1Dh, 00h, 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 83h, 0C4h, 04h, 0FFh, 52h, 60h
    db 8Bh, 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 01h, 6Ah, 00h, 6Ah, 00h, 0FFh, 50h, 6Ch, 8Bh
    db 10h, 68h, 00h, 0C6h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah, 02h, 8Bh
    db 0C8h, 0FFh, 52h, 4Ch, 0EBh, 3Ah, 8Bh, 7Eh, 0Ch, 8Bh, 47h, 50h, 33h, 0D2h, 0F7h, 77h
    db 54h, 83h, 0F8h, 01h, 7Dh, 05h, 0B8h, 01h, 00h, 00h, 00h, 69h, 0C0h, 0E8h, 03h, 00h
    db 00h, 50h, 51h, 0FFh, 15h, 0A4h, 96h, 35h, 01h, 8Bh, 86h, 50h, 0Bh, 00h, 00h, 85h
    db 0C0h, 7Eh, 0Dh, 8Bh, 86h, 4Ch, 0Bh, 00h, 00h, 50h, 0FFh, 15h, 0B8h, 96h, 35h, 01h
    db 8Bh, 8Eh, 58h, 09h, 00h, 00h, 3Bh, 8Eh, 54h, 09h, 00h, 00h, 5Fh, 73h, 07h, 8Bh
    db 0CEh, 0E8h, 53h, 06h, 99h, 0FFh, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0A0h, 98h, 94h, 0FFh, 8Bh, 4Ch, 24h, 18h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 20h, 0C3h
?d_006b78d0@@YAXXZ ENDP

; ghidra: Catch@00ab7b9b  retail @ 0x006B7B9B size 85
_TEXT ENDS
_TEXT$d00ab7b9b SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB7B9B size 85
public ?d_006b7b9b@@YAXXZ
?d_006b7b9b@@YAXXZ PROC
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 074h, 046h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 083h, 0C4h, 004h, 0FFh, 050h, 060h, 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 011h, 06Ah, 000h, 06Ah, 000h, 0FFh, 052h, 06Ch, 08Bh, 010h, 068h
    dd g_Va0111C6A8
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 04Dh, 0E0h, 08Bh, 009h, 08Bh, 010h, 051h, 08Bh, 0C8h, 0FFh
    db 052h, 038h, 08Bh, 010h, 06Ah, 002h, 08Bh, 0C8h, 0FFh, 052h, 04Ch, 0B8h
    dd g_Va00AB7BF0
    db 0C3h
?d_006b7b9b@@YAXXZ ENDP
_TEXT$d00ab7b9b ENDS
_TEXT SEGMENT

; ghidra: Catch@00ab7ccf  retail @ 0x006B7CCF size 85
_TEXT ENDS
_TEXT$d00ab7ccf SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB7CCF size 85
public ?d_006b7ccf@@YAXXZ
?d_006b7ccf@@YAXXZ PROC
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 074h, 046h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 011h, 083h, 0C4h, 004h, 0FFh, 052h, 060h, 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 06Ah, 000h, 06Ah, 000h, 0FFh, 050h, 06Ch, 08Bh, 010h, 068h
    dd g_Va0111C668
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 04Dh, 0D4h, 08Bh, 009h, 08Bh, 010h, 051h, 08Bh, 0C8h, 0FFh
    db 052h, 038h, 08Bh, 010h, 06Ah, 002h, 08Bh, 0C8h, 0FFh, 052h, 04Ch, 0B8h
    dd g_Va00AB7D24
    db 0C3h
?d_006b7ccf@@YAXXZ ENDP
_TEXT$d00ab7ccf ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab7d2d  retail @ 0x006B7D2D size 61
_TEXT ENDS
_TEXT$d00ab7d2d SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AB7D2D size 61
public ?d_006b7d2d@@YAXXZ
?d_006b7d2d@@YAXXZ PROC
    db 057h, 0C7h, 045h, 0FCh, 000h, 000h, 000h, 000h, 0FFh, 015h
    dd __imp__free
    db 083h, 0C4h, 004h, 085h, 0DBh, 074h, 008h, 08Bh, 003h, 06Ah, 001h, 08Bh, 0CBh, 0FFh, 010h, 08Bh
    db 016h, 08Bh, 0CEh, 0FFh, 052h, 014h, 08Bh, 04Dh, 0DCh, 08Ah, 045h, 0CCh, 05Fh, 088h, 001h, 08Bh
    db 04Dh, 0F4h, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 08Bh, 0E5h, 05Dh, 0C3h
?d_006b7d2d@@YAXXZ ENDP
_TEXT$d00ab7d2d ENDS
_TEXT SEGMENT

; ghidra: FUN_00ab7e10  retail @ 0x006B7E10 size 68
public ?d_006b7e10@@YAXXZ
?d_006b7e10@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 47h, 04h, 85h, 0C0h, 8Bh, 0F1h, 74h, 21h, 8Bh
    db 48h, 08h, 85h, 0C9h, 75h, 0Bh, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 92h, 0ACh, 00h, 00h
    db 00h, 8Bh, 47h, 04h, 8Bh, 48h, 08h, 83h, 0B9h, 84h, 00h, 00h, 00h, 02h, 74h, 07h
    db 5Fh, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h, 50h, 8Bh, 0CEh, 0E8h, 7Bh, 0E6h, 98h, 0FFh, 5Fh
    db 5Eh, 0C2h, 04h, 00h
?d_006b7e10@@YAXXZ ENDP

; ghidra: FUN_00ab7e70  retail @ 0x006B7E70 size 748
public ?d_006b7e70@@YAXXZ
?d_006b7e70@@YAXXZ PROC
    db 83h, 0ECh, 38h, 53h, 55h, 8Bh, 0D9h, 8Bh, 83h, 48h, 0Bh, 00h, 00h, 56h, 33h, 0EDh
    db 85h, 0C0h, 57h, 7Eh, 3Ch, 8Bh, 3Dh, 8Ch, 95h, 35h, 01h, 33h, 0F6h, 8Dh, 49h, 00h
    db 8Bh, 83h, 44h, 0Bh, 00h, 00h, 8Ah, 0Ch, 30h, 03h, 0C6h, 84h, 0C9h, 75h, 14h, 8Bh
    db 40h, 04h, 85h, 0C0h, 74h, 1Bh, 50h, 0FFh, 0D7h, 83h, 0F8h, 04h, 0Fh, 95h, 0C0h, 84h
    db 0C0h, 75h, 0Eh, 8Bh, 83h, 48h, 0Bh, 00h, 00h, 45h, 83h, 0C6h, 40h, 3Bh, 0E8h, 7Ch
    db 0CFh, 3Bh, 0ABh, 48h, 0Bh, 00h, 00h, 75h, 1Dh, 8Bh, 83h, 14h, 06h, 00h, 00h, 85h
    db 0C0h, 76h, 07h, 48h, 89h, 83h, 14h, 06h, 00h, 00h, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 5Bh
    db 83h, 0C4h, 38h, 0C2h, 08h, 00h, 8Bh, 7Ch, 24h, 4Ch, 8Bh, 0Fh, 89h, 69h, 08h, 8Bh
    db 17h, 0C7h, 42h, 0Ch, 02h, 00h, 00h, 00h, 8Bh, 8Bh, 44h, 0Bh, 00h, 00h, 0C1h, 0E5h
    db 06h, 8Ah, 44h, 0Dh, 0Ch, 03h, 0E9h, 84h, 0C0h, 74h, 08h, 55h, 8Bh, 0CBh, 0E8h, 2Eh
    db 38h, 98h, 0FFh, 8Bh, 0Fh, 8Bh, 51h, 14h, 8Dh, 44h, 24h, 13h, 50h, 52h, 8Dh, 44h
    db 24h, 20h, 50h, 8Bh, 0CBh, 0E8h, 0A4h, 9Fh, 94h, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h
    db 0Fh, 84h, 06h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 50h, 0C6h, 45h, 01h, 00h, 0C6h, 45h
    db 3Ch, 00h, 89h, 4Dh, 04h, 8Bh, 37h, 83h, 0C6h, 14h, 8Dh, 45h, 08h, 3Bh, 0C6h, 74h
    db 3Fh, 8Bh, 06h, 85h, 0C0h, 74h, 0Ah, 83h, 0C0h, 74h, 50h, 0FFh, 15h, 5Ch, 8Eh, 35h
    db 01h, 8Bh, 45h, 08h, 85h, 0C0h, 74h, 23h, 83h, 0C0h, 70h, 89h, 44h, 24h, 14h, 83h
    db 0C0h, 04h, 50h, 0FFh, 15h, 54h, 8Eh, 35h, 01h, 85h, 0C0h, 7Fh, 0Eh, 8Bh, 4Ch, 24h
    db 14h, 85h, 0C9h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 06h, 89h, 45h, 08h
    db 0C7h, 45h, 30h, 00h, 00h, 00h, 00h, 8Bh, 0Fh, 89h, 4Dh, 10h, 0C6h, 45h, 0Ch, 01h
    db 8Bh, 83h, 50h, 0Bh, 00h, 00h, 85h, 0C0h, 7Fh, 12h, 8Bh, 83h, 4Ch, 0Bh, 00h, 00h
    db 83h, 0F8h, 0FFh, 74h, 07h, 50h, 0FFh, 15h, 0B8h, 96h, 35h, 01h, 0FFh, 83h, 50h, 0Bh
    db 00h, 00h, 8Bh, 07h, 8Bh, 48h, 18h, 85h, 0C9h, 74h, 71h, 8Bh, 0C1h, 85h, 0C0h, 74h
    db 05h, 8Dh, 70h, 08h, 0EBh, 02h, 33h, 0F6h, 83h, 7Eh, 14h, 01h, 74h, 6Ah, 0E8h, 0EDh
    db 16h, 1Dh, 00h, 84h, 0C0h, 74h, 4Bh, 6Ah, 01h, 0E8h, 0B2h, 16h, 1Dh, 00h, 8Bh, 0Dh
    db 5Ch, 6Eh, 33h, 01h, 8Bh, 11h, 83h, 0C4h, 04h, 0FFh, 52h, 60h, 8Bh, 0Dh, 5Ch, 6Eh
    db 33h, 01h, 8Bh, 01h, 6Ah, 00h, 6Ah, 00h, 0FFh, 50h, 6Ch, 8Bh, 0Fh, 8Bh, 49h, 14h
    db 8Bh, 10h, 83h, 0C1h, 14h, 51h, 68h, 0E0h, 0C3h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h
    db 50h, 0E8h, 60h, 0EFh, 95h, 0FFh, 8Bh, 10h, 83h, 0C4h, 08h, 6Ah, 02h, 8Bh, 0C8h, 0FFh
    db 52h, 4Ch, 8Bh, 0Fh, 83h, 0C1h, 18h, 0E8h, 83h, 91h, 97h, 0FFh, 5Fh, 5Eh, 5Dh, 32h
    db 0C0h, 5Bh, 83h, 0C4h, 38h, 0C2h, 08h, 00h, 8Bh, 46h, 10h, 89h, 45h, 38h, 8Bh, 4Eh
    db 0Ch, 89h, 4Dh, 34h, 8Bh, 17h, 6Ah, 02h, 83h, 0C2h, 18h, 52h, 55h, 8Bh, 0CBh, 0E8h
    db 8Eh, 5Fh, 96h, 0FFh, 8Bh, 0Fh, 83h, 0C1h, 18h, 0E8h, 51h, 91h, 97h, 0FFh, 8Bh, 43h
    db 0Ch, 8Bh, 48h, 50h, 0Fh, 0AFh, 4Dh, 38h, 0Fh, 0AFh, 4Dh, 34h, 0B8h, 0D3h, 4Dh, 62h
    db 10h, 0F7h, 0E1h, 0C1h, 0EAh, 09h, 81h, 0FAh, 00h, 0C4h, 00h, 00h, 89h, 55h, 18h, 7Dh
    db 07h, 0C7h, 45h, 18h, 00h, 0C4h, 00h, 00h, 8Bh, 45h, 18h, 8Bh, 0C8h, 83h, 0E1h, 03h
    db 74h, 08h, 2Bh, 0C1h, 83h, 0C0h, 04h, 89h, 45h, 18h, 8Bh, 55h, 18h, 0C1h, 0EAh, 02h
    db 0C1h, 0E2h, 02h, 52h, 0E8h, 0B7h, 9Eh, 1Ch, 00h, 83h, 0C4h, 04h, 89h, 45h, 14h, 8Bh
    db 45h, 18h, 50h, 55h, 8Bh, 0CBh, 0E8h, 45h, 18h, 97h, 0FFh, 0B9h, 09h, 00h, 00h, 00h
    db 8Dh, 7Ch, 24h, 24h, 0F3h, 0A5h, 8Bh, 4Dh, 14h, 8Bh, 74h, 24h, 50h, 8Dh, 44h, 24h
    db 24h, 89h, 4Ch, 24h, 28h, 8Bh, 55h, 18h, 50h, 56h, 89h, 54h, 24h, 34h, 0FFh, 15h
    db 4Ch, 96h, 35h, 01h, 6Ah, 00h, 56h, 0FFh, 15h, 0FCh, 95h, 35h, 01h, 8Bh, 7Ch, 24h
    db 4Ch, 8Dh, 4Ch, 24h, 18h, 51h, 57h, 8Bh, 0CBh, 0E8h, 0Bh, 0F4h, 98h, 0FFh, 6Ah, 00h
    db 56h, 0FFh, 15h, 50h, 96h, 35h, 01h, 8Bh, 07h, 8Bh, 50h, 14h, 8Bh, 4Ah, 28h, 83h
    db 0F9h, 02h, 74h, 0Eh, 3Bh, 8Bh, 04h, 06h, 00h, 00h, 74h, 06h, 0C6h, 40h, 3Bh, 01h
    db 0EBh, 04h, 0C6h, 40h, 3Bh, 00h, 57h, 8Bh, 0CBh, 0E8h, 2Ah, 65h, 97h, 0FFh, 8Ah, 45h
    db 3Ch, 84h, 0C0h, 74h, 07h, 56h, 0FFh, 15h, 0ACh, 96h, 35h, 01h, 5Fh, 5Eh, 0C6h, 45h
    db 00h, 01h, 5Dh, 0B0h, 01h, 5Bh, 83h, 0C4h, 38h, 0C2h, 08h, 00h
?d_006b7e70@@YAXXZ ENDP

; ghidra: FUN_00ab8a60  retail @ 0x006B8A60 size 379
public ?d_006b8a60@@YAXXZ
?d_006b8a60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DFh, 92h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 48h, 53h, 55h, 56h, 8Bh, 0F1h, 33h, 0C9h, 89h
    db 4Ch, 24h, 14h, 8Bh, 5Ch, 24h, 64h, 8Bh, 43h, 04h, 8Bh, 68h, 08h, 3Bh, 0E9h, 57h
    db 8Dh, 7Bh, 04h, 89h, 6Ch, 24h, 10h, 74h, 0Ch, 8Dh, 45h, 04h, 50h, 0FFh, 15h, 5Ch
    db 8Eh, 35h, 01h, 33h, 0C9h, 3Bh, 0E9h, 89h, 4Ch, 24h, 60h, 0Fh, 84h, 79h, 06h, 00h
    db 00h, 89h, 4Ch, 24h, 3Ch, 8Bh, 0Fh, 0C6h, 44h, 24h, 60h, 01h, 0E8h, 8Bh, 0A6h, 95h
    db 0FFh, 8Dh, 4Ch, 24h, 68h, 51h, 8Bh, 0CEh, 8Bh, 0E8h, 0E8h, 0DAh, 0E8h, 96h, 0FFh, 8Bh
    db 4Ch, 24h, 68h, 57h, 83h, 0C1h, 14h, 0C6h, 44h, 24h, 64h, 02h, 0E8h, 0A8h, 24h, 99h
    db 0FFh, 8Bh, 0Fh, 8Ah, 41h, 47h, 84h, 0C0h, 74h, 22h, 8Bh, 41h, 08h, 8Bh, 50h, 2Ch
    db 89h, 54h, 24h, 14h, 0DBh, 44h, 24h, 14h, 0D8h, 1Dh, 98h, 0BBh, 11h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Ah, 07h, 6Ah, 01h, 0E8h, 0C3h, 3Ah, 97h, 0FFh, 8Bh, 07h, 0C6h, 40h
    db 47h, 00h, 8Bh, 0Fh, 0E8h, 92h, 0BBh, 94h, 0FFh, 84h, 0C0h, 74h, 1Eh, 8Bh, 44h, 24h
    db 68h, 0C6h, 40h, 35h, 01h, 8Bh, 4Eh, 0Ch, 0DBh, 41h, 3Ch, 8Bh, 54h, 24h, 68h, 6Ah
    db 00h, 0D9h, 5Ah, 28h, 8Bh, 0Fh, 0E8h, 94h, 3Ah, 97h, 0FFh, 8Bh, 07h, 8Bh, 4Ch, 24h
    db 10h, 0C6h, 40h, 44h, 00h, 8Bh, 81h, 84h, 00h, 00h, 00h, 83h, 0F8h, 04h, 0Fh, 87h
    db 6Bh, 05h, 00h, 00h, 0FFh, 24h, 85h, 40h, 91h, 0ABh, 00h, 83h, 0F8h, 01h, 75h, 12h
    db 8Bh, 0Fh, 8Ah, 51h, 43h, 84h, 0D2h, 74h, 09h, 8Bh, 0CEh, 0E8h, 3Fh, 0FBh, 96h, 0FFh
    db 0EBh, 20h, 85h, 0C0h, 75h, 1Ch, 8Bh, 07h, 8Bh, 48h, 64h, 8Bh, 40h, 28h, 3Bh, 8Ch
    db 86h, 0C4h, 0Ah, 00h, 00h, 7Eh, 0Bh, 6Ah, 00h, 50h, 51h, 8Bh, 0CEh, 0E8h, 59h, 9Eh
    db 94h, 0FFh, 85h, 0EDh, 74h, 13h, 8Bh, 06h, 55h, 8Bh, 0CEh, 0FFh, 50h, 50h, 84h, 0C0h
    db 75h, 07h, 33h, 0EDh, 0E9h, 82h, 01h, 00h, 00h, 8Bh, 0Fh, 8Dh, 54h, 24h, 20h, 52h
    db 0E8h, 20h, 2Ch, 95h, 0FFh, 8Bh, 00h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h
    db 0B8h, 8Bh, 38h, 07h, 01h, 6Ah, 00h, 50h, 8Bh, 86h, 60h, 09h, 00h, 00h, 50h, 0FFh
    db 15h, 0D8h, 95h, 35h, 01h, 8Bh, 0E8h, 8Dh, 4Ch, 24h, 20h
?d_006b8a60@@YAXXZ ENDP

; ghidra: FUN_00ab9320  retail @ 0x006B9320 size 348
public ?d_006b9320@@YAXXZ
?d_006b9320@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 9Bh, 0E7h, 97h, 0FFh, 84h, 0C0h
    db 75h, 14h, 56h, 8Bh, 0CFh, 0E8h, 0C7h, 39h, 95h, 0FFh, 8Bh, 44h, 24h, 10h, 5Fh, 0C6h
    db 00h, 00h, 5Eh, 0C2h, 0Ch, 00h, 8Ah, 46h, 11h, 84h, 0C0h, 74h, 58h, 56h, 8Bh, 0CFh
    db 0E8h, 52h, 0D7h, 97h, 0FFh, 84h, 0C0h, 75h, 4Ch, 83h, 3Eh, 00h, 0Fh, 85h, 15h, 01h
    db 00h, 00h, 8Bh, 4Eh, 04h, 85h, 0C9h, 0Fh, 84h, 0Ah, 01h, 00h, 00h, 0E8h, 5Ah, 8Ch
    db 95h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0FDh, 00h, 00h, 00h, 8Bh, 4Eh, 04h, 0E8h, 0B1h, 0D6h
    db 98h, 0FFh, 8Bh, 4Eh, 04h, 0E8h, 42h, 8Ch, 95h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0E5h, 00h
    db 00h, 00h, 8Bh, 4Ch, 24h, 10h, 0C6h, 01h, 00h, 8Bh, 56h, 04h, 5Fh, 0C6h, 42h, 44h
    db 01h, 5Eh, 0C2h, 0Ch, 00h, 8Bh, 06h, 83h, 0F8h, 07h, 0Fh, 87h, 0C7h, 00h, 00h, 00h
    db 53h, 0FFh, 24h, 85h, 7Ch, 94h, 0ABh, 00h, 8Bh, 44h, 24h, 18h, 50h, 56h, 8Bh, 0CFh
    db 0E8h, 34h, 0B4h, 95h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 8Bh, 4Eh, 08h, 51h, 8Bh
    db 0CFh, 0E8h, 0A7h, 3Dh, 97h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 56h, 8Bh, 0CFh, 0E8h
    db 68h, 98h, 95h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 56h, 8Bh, 0CFh, 0E8h, 0D1h, 0CBh
    db 95h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 56h, 8Bh, 0CFh, 0E8h, 8Bh, 0C3h, 94h, 0FFh
    db 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 8Ah, 5Eh, 10h, 8Bh, 46h, 04h, 8Bh, 48h, 64h, 33h
    db 0D2h, 84h, 0DBh, 0Fh, 94h, 0C2h, 52h, 8Bh, 50h, 28h, 51h, 52h, 8Bh, 0CFh, 0E8h, 0C2h
    db 0E8h, 97h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 8Bh, 4Eh, 04h, 8Bh, 59h, 64h, 55h
    db 8Bh, 69h, 28h, 0E8h, 73h, 0B2h, 94h, 0FFh, 8Ah, 4Eh, 10h, 0F6h, 0D8h, 1Bh, 0C0h, 40h
    db 50h, 33h, 0C0h, 84h, 0C9h, 0Fh, 94h, 0C0h, 8Bh, 0CFh, 50h, 53h, 55h, 0E8h, 0DEh, 24h
    db 98h, 0FFh, 5Dh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h, 8Ah, 56h, 10h, 8Bh, 46h, 04h, 33h
    db 0C9h, 84h, 0D2h, 8Bh, 50h, 64h, 8Bh, 40h, 28h, 0Fh, 94h, 0C1h, 51h, 52h, 50h, 8Bh
    db 0CFh, 0E8h, 0E8h, 0E9h, 95h, 0FFh, 5Bh, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_006b9320@@YAXXZ ENDP
_TEXT ENDS
END
