.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ?Data00F595C4@@3P6AXXZA:BYTE
EXTERN ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A:BYTE
EXTERN ?g_Rva13596C0@@3P6GXPAX@ZA:BYTE
EXTERN ?j_00007bfd@@YAXXZ:NEAR
EXTERN ?j_0000d99a@@YAXXZ:NEAR
EXTERN ?j_0000f41b@@YAXXZ:NEAR
EXTERN ?j_0000f96b@@YAXXZ:NEAR
EXTERN ?j_0001cce2@@YAXXZ:NEAR
EXTERN ?j_00028173@@YAXXZ:NEAR
EXTERN ?j_0002e1cc@@YAXXZ:NEAR
EXTERN ?j_00031a25@@YAXXZ:NEAR
EXTERN ?j_0003a229@@YAXXZ:NEAR
EXTERN ?j_0003b741@@YAXXZ:NEAR
EXTERN ?j_0003ce89@@YAXXZ:NEAR
EXTERN ?j_000420c3@@YAXXZ:NEAR
EXTERN ?j_00049cdd@@YAXXZ:NEAR
EXTERN __imp_?doFree@BfmeFreeHelper@@QAEXXZ:BYTE
EXTERN __imp__AIL_close_stream@4:BYTE
EXTERN __imp__AIL_register_3D_EOS_callback@8:BYTE
EXTERN __imp__AIL_register_EOS_callback@8:BYTE
EXTERN __imp__AIL_register_stream_callback@8:BYTE
EXTERN __imp__AIL_stop_sample@4:BYTE
EXTERN __imp__ReleaseMutex@4:BYTE
EXTERN __imp__WaitForSingleObject@8:BYTE
EXTERN g_Va01047ED8:NEAR
_TEXT SEGMENT

; retail @ 0x00685910 size 1116
public ?d_00685910@@YAXXZ
?d_00685910@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 41h, 63h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h
    db 56h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 83h, 0F8h, 12h
    db 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 0Fh, 87h, 7Bh, 03h, 00h, 00h, 0FFh, 24h
    db 85h, 20h, 5Dh, 0A8h, 00h, 68h, 80h, 0B6h, 11h, 01h, 6Ah, 00h, 68h, 58h, 0B6h, 11h
    db 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 4Eh, 32h
    db 20h, 00h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 74h, 36h, 20h, 00h, 83h, 0C4h, 14h, 0E9h
    db 64h, 03h, 00h, 00h, 68h, 20h, 0B6h, 11h, 01h, 6Ah, 01h, 68h, 0FCh, 0B5h, 11h, 01h
    db 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 1Fh, 32h, 20h
    db 00h, 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 45h, 36h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 35h
    db 03h, 00h, 00h, 68h, 0E0h, 0B5h, 11h, 01h, 6Ah, 02h, 68h, 0B8h, 0B5h, 11h, 01h, 51h
    db 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 0F0h, 31h, 20h, 00h
    db 8Dh, 54h, 24h, 14h, 52h, 0E8h, 16h, 36h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 06h, 03h
    db 00h, 00h, 68h, 9Ch, 0B5h, 11h, 01h, 6Ah, 03h, 68h, 78h, 0B5h, 11h, 01h, 51h, 89h
    db 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 0C1h, 31h, 20h, 00h, 8Dh
    db 44h, 24h, 14h, 50h, 0E8h, 0E7h, 35h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 0D7h, 02h, 00h
    db 00h, 68h, 60h, 0B5h, 11h, 01h, 6Ah, 04h, 68h, 3Ch, 0B5h, 11h, 01h, 51h, 89h, 64h
    db 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 92h, 31h, 20h, 00h, 8Dh, 4Ch
    db 24h, 14h, 51h, 0E8h, 0B8h, 35h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 0A8h, 02h, 00h, 00h
    db 68h, 18h, 0B5h, 11h, 01h, 6Ah, 05h, 68h, 0F8h, 0B4h, 11h, 01h, 51h, 89h, 64h, 24h
    db 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 63h, 31h, 20h, 00h, 8Dh, 54h, 24h
    db 14h, 52h, 0E8h, 89h, 35h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 79h, 02h, 00h, 00h, 68h
    db 0CCh, 0B4h, 11h, 01h, 6Ah, 06h, 68h, 0A0h, 0B4h, 11h, 01h, 51h, 89h, 64h, 24h, 30h
    db 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 34h, 31h, 20h, 00h, 8Dh, 44h, 24h, 14h
    db 50h, 0E8h, 5Ah, 35h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 4Ah, 02h, 00h, 00h, 68h, 84h
    db 0B4h, 11h, 01h, 6Ah, 07h, 68h, 58h, 0B4h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh
    db 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 05h, 31h, 20h, 00h, 8Dh, 4Ch, 24h, 14h, 51h
    db 0E8h, 2Bh, 35h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 1Bh, 02h, 00h, 00h, 68h, 30h, 0B4h
    db 11h, 01h, 6Ah, 08h, 68h, 04h, 0B4h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh
    db 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 0D6h, 30h, 20h, 00h, 8Dh, 54h, 24h, 14h, 52h, 0E8h
    db 0FCh, 34h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 0ECh, 01h, 00h, 00h, 68h, 0DCh, 0B3h, 11h
    db 01h, 6Ah, 09h, 68h, 0BCh, 0B3h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h
    db 4Ch, 0B6h, 11h, 01h, 0E8h, 0A7h, 30h, 20h, 00h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 0CDh
    db 34h, 20h, 00h, 83h, 0C4h, 14h, 0E9h, 0BDh, 01h, 00h, 00h, 68h, 98h, 0B3h, 11h, 01h
    db 6Ah, 0Ah, 68h, 70h, 0B3h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch
    db 0B6h, 11h, 01h, 0E8h, 78h, 30h, 20h, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 9Eh, 34h
    db 20h, 00h, 83h, 0C4h, 14h, 0E9h, 8Eh, 01h, 00h, 00h, 68h, 50h, 0B3h, 11h, 01h, 6Ah
    db 0Bh, 68h, 34h, 0B3h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h
    db 11h, 01h, 0E8h, 49h, 30h, 20h, 00h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 6Fh, 34h, 20h
    db 00h, 83h, 0C4h, 14h, 0E9h, 5Fh, 01h, 00h, 00h, 68h, 0D8h, 0B2h, 11h, 01h, 6Ah, 0Ch
    db 68h, 0ACh, 0B2h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h
    db 01h, 0E8h, 1Ah, 30h, 20h, 00h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 40h, 34h, 20h, 00h
    db 83h, 0C4h, 14h, 0E9h, 30h, 01h, 00h, 00h, 68h, 8Ch, 0B2h, 11h, 01h, 6Ah, 0Dh, 68h
    db 6Ch, 0B2h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h
    db 0E8h, 0EBh, 2Fh, 20h, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 11h, 34h, 20h, 00h, 83h
    db 0C4h, 14h, 0E9h, 01h, 01h, 00h, 00h, 68h, 44h, 0B2h, 11h, 01h, 6Ah, 0Eh, 68h, 1Ch
    db 0B2h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h
    db 0BCh, 2Fh, 20h, 00h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0E2h, 33h, 20h, 00h, 83h, 0C4h
    db 14h, 0E9h, 0D2h, 00h, 00h, 00h, 68h, 0F4h, 0B1h, 11h, 01h, 6Ah, 0Fh, 68h, 0D0h, 0B1h
    db 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 8Dh
    db 2Fh, 20h, 00h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 0B3h, 33h, 20h, 00h, 83h, 0C4h, 14h
    db 0E9h, 0A3h, 00h, 00h, 00h, 68h, 80h, 0B1h, 11h, 01h, 6Ah, 10h, 68h, 60h, 0B1h, 11h
    db 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 5Eh, 2Fh
    db 20h, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 84h, 33h, 20h, 00h, 83h, 0C4h, 14h, 0EBh
    db 77h, 68h, 10h, 0B1h, 11h, 01h, 6Ah, 11h, 68h, 0E4h, 0B0h, 11h, 01h, 51h, 89h, 64h
    db 24h, 30h, 8Bh, 0CCh, 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 32h, 2Fh, 20h, 00h, 8Dh, 54h
    db 24h, 14h, 52h, 0E8h, 58h, 33h, 20h, 00h, 83h, 0C4h, 14h, 0EBh, 4Bh, 68h, 0A4h, 0B0h
    db 11h, 01h, 6Ah, 12h, 68h, 78h, 0B0h, 11h, 01h, 51h, 89h, 64h, 24h, 30h, 8Bh, 0CCh
    db 68h, 4Ch, 0B6h, 11h, 01h, 0E8h, 06h, 2Fh, 20h, 00h, 8Dh, 44h, 24h, 14h, 50h, 0E8h
    db 2Ch, 33h, 20h, 00h, 83h, 0C4h, 14h, 0EBh, 1Fh, 50h, 51h, 89h, 64h, 24h, 28h, 8Bh
    db 0CCh, 68h, 5Ch, 0B0h, 11h, 01h, 0E8h, 0E5h, 2Eh, 20h, 00h, 8Dh, 4Ch, 24h, 0Ch, 51h
    db 0E8h, 0Bh, 33h, 20h, 00h, 83h, 0C4h, 0Ch, 8Bh, 74h, 24h, 1Ch, 8Dh, 54h, 24h, 04h
    db 52h, 8Bh, 0CEh, 0E8h, 68h, 1Eh, 20h, 00h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 08h
    db 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 14h, 00h, 0E8h, 32h, 1Ch, 20h, 00h, 8Bh, 4Ch
    db 24h, 0Ch, 8Bh, 0C6h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h
    db 55h, 59h, 0A8h, 00h, 84h, 59h, 0A8h, 00h, 0B3h, 59h, 0A8h, 00h, 0E2h, 59h, 0A8h, 00h
    db 11h, 5Ah, 0A8h, 00h, 40h, 5Ah, 0A8h, 00h, 6Fh, 5Ah, 0A8h, 00h, 9Eh, 5Ah, 0A8h, 00h
    db 0CDh, 5Ah, 0A8h, 00h, 0FCh, 5Ah, 0A8h, 00h, 2Bh, 5Bh, 0A8h, 00h, 5Ah, 5Bh, 0A8h, 00h
    db 89h, 5Bh, 0A8h, 00h, 0B8h, 5Bh, 0A8h, 00h, 0E7h, 5Bh, 0A8h, 00h, 16h, 5Ch, 0A8h, 00h
    db 45h, 5Ch, 0A8h, 00h, 71h, 5Ch, 0A8h, 00h, 9Dh, 5Ch, 0A8h, 00h
?d_00685910@@YAXXZ ENDP

; retail @ 0x00691330 size 460
public ?d_00691330@@YAXXZ
?d_00691330@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F1h, 6Fh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 8Bh
    db 44h, 24h, 1Ch, 83h, 0F8h, 07h, 56h, 0Fh, 87h, 17h, 01h, 00h, 00h, 0FFh, 24h, 85h
    db 0DCh, 14h, 0A9h, 00h, 8Bh, 74h, 24h, 1Ch, 68h, 0FCh, 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h
    db 4Ch, 78h, 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 8Bh, 74h, 24h, 1Ch, 68h, 0ECh, 0B9h, 11h, 01h, 8Bh
    db 0CEh, 0E8h, 2Ah, 78h, 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 8Bh, 74h, 24h, 1Ch, 68h, 0DCh, 0B9h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 08h, 78h, 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 8Bh, 74h, 24h, 1Ch, 68h, 0CCh
    db 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h, 0E6h, 77h, 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 8Bh, 74h, 24h, 1Ch
    db 68h, 0BCh, 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h, 0C4h, 77h, 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 8Bh, 74h
    db 24h, 1Ch, 68h, 0A0h, 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h, 0A2h, 77h, 1Fh, 00h, 8Bh, 0C6h
    db 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h
    db 8Bh, 74h, 24h, 1Ch, 68h, 80h, 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h, 80h, 77h, 1Fh, 00h
    db 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h
    db 14h, 0C3h, 8Bh, 74h, 24h, 1Ch, 68h, 64h, 0B9h, 11h, 01h, 8Bh, 0CEh, 0E8h, 5Eh, 77h
    db 1Fh, 00h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh
    db 83h, 0C4h, 14h, 0C3h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 50h, 51h, 89h, 64h
    db 24h, 10h, 8Bh, 0CCh, 68h, 54h, 0B9h, 11h, 01h, 0C7h, 44h, 24h, 20h, 01h, 00h, 00h
    db 00h, 0E8h, 2Ah, 77h, 1Fh, 00h, 8Dh, 44h, 24h, 28h, 50h, 0E8h, 50h, 7Bh, 1Fh, 00h
    db 8Bh, 74h, 24h, 28h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 51h, 8Bh, 0CEh, 0E8h, 0ADh
    db 66h, 1Fh, 00h, 8Dh, 4Ch, 24h, 20h, 0C7h, 44h, 24h, 04h, 01h, 00h, 00h, 00h, 0C6h
    db 44h, 24h, 14h, 00h, 0E8h, 77h, 64h, 1Fh, 00h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 0C6h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 14h, 0C3h, 90h, 64h, 13h, 0A9h, 00h
    db 86h, 13h, 0A9h, 00h, 0A8h, 13h, 0A9h, 00h, 0CAh, 13h, 0A9h, 00h, 0ECh, 13h, 0A9h, 00h
    db 0Eh, 14h, 0A9h, 00h, 30h, 14h, 0A9h, 00h, 52h, 14h, 0A9h, 00h
?d_00691330@@YAXXZ ENDP

; retail @ 0x006A59F0 size 904
_TEXT ENDS
_TEXT$d00aa59f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AA59F0 size 904
public ?d_006a59f0@@YAXXZ
?d_006a59f0@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va01047ED8
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 010h, 053h, 055h, 08Bh, 06Ch, 024h
    db 028h, 08Bh, 045h, 014h, 085h, 0C0h, 056h, 057h, 08Bh, 0F1h, 00Fh, 084h, 083h, 000h, 000h, 000h
    db 08Bh, 048h, 008h, 085h, 0C9h, 074h, 07Ch, 08Bh, 089h, 084h, 000h, 000h, 000h, 049h, 074h, 02Fh
    db 049h, 075h, 048h, 08Bh, 045h, 00Ch, 085h, 0C0h, 075h, 010h, 08Bh, 045h, 008h, 085h, 0C0h, 074h
    db 03Ah, 08Bh, 0CEh
    call ?j_0000d99a@@YAXXZ
    db 0EBh, 031h, 083h, 0F8h, 001h, 075h, 02Ch, 08Bh, 045h, 008h, 085h, 0C0h, 074h, 025h, 08Bh, 0CEh
    call ?j_000420c3@@YAXXZ
    db 0EBh, 01Ch, 08Bh, 040h, 028h, 08Bh, 0C8h, 08Bh, 086h, 024h, 006h, 000h, 000h, 0BAh, 001h, 000h
    db 000h, 000h, 0D3h, 0E2h, 0F7h, 0D2h, 023h, 0C2h, 089h, 086h, 024h, 006h, 000h, 000h, 08Ah, 045h
    db 03Dh, 084h, 0C0h, 074h, 021h, 08Bh, 045h, 014h, 051h, 083h, 0C0h, 06Ch, 089h, 064h, 024h, 014h
    db 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A
    call ?j_0002e1cc@@YAXXZ
    db 0C6h, 000h, 001h, 08Bh, 045h, 00Ch, 032h, 0DBh, 083h, 0F8h, 003h, 00Fh, 087h, 06Ah, 001h, 000h
    db 000h, 0FFh, 024h, 085h
    dd ?d_006a59f0@@YAXXZ + 0378h
    db 08Bh, 045h, 008h, 085h, 0C0h, 08Dh, 07Dh, 008h, 00Fh, 084h, 055h, 001h, 000h, 000h, 06Ah, 000h
    db 050h, 0FFh, 015h
    dd __imp__AIL_register_EOS_callback@8
    db 08Bh, 007h, 050h, 0FFh, 015h
    dd __imp__AIL_stop_sample@4
    db 0FFh, 015h
    dd ?Data00F595C4@@3P6AXXZA
    db 0C6h, 044h, 024h, 010h, 001h, 057h, 08Dh, 04Ch, 024h, 01Ch, 08Dh, 0AEh, 008h, 00Bh, 000h, 000h
    db 051h, 08Bh, 0CDh, 0C7h, 044h, 024h, 030h, 000h, 000h, 000h, 000h
    call ?j_00028173@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 085h, 0C0h, 075h, 01Ch, 0FFh, 015h
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 057h, 08Dh, 08Eh, 0C0h, 009h, 000h, 000h, 0C6h, 044h, 024h, 014h, 000h
    call ?j_0000f96b@@YAXXZ
    db 0E9h, 0E5h, 000h, 000h, 000h, 08Bh, 054h, 024h, 030h, 039h, 050h, 008h, 074h, 01Ch, 0FFh, 015h
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 057h, 08Dh, 08Eh, 0C0h, 009h, 000h, 000h, 0C6h, 044h, 024h, 014h, 000h
    call ?j_0000f96b@@YAXXZ
    db 0E9h, 0C0h, 000h, 000h, 000h, 083h, 0ECh, 008h, 08Bh, 0CCh, 089h, 001h, 08Bh, 044h, 024h, 024h
    db 089h, 041h, 004h, 08Bh, 0CDh, 089h, 064h, 024h, 01Ch
    call ?j_00031a25@@YAXXZ
    db 057h, 08Dh, 08Eh, 0C0h, 009h, 000h, 000h
    call ?j_0000f96b@@YAXXZ
    db 0E9h, 096h, 000h, 000h, 000h, 08Bh, 045h, 008h, 085h, 0C0h, 08Dh, 07Dh, 008h, 00Fh, 084h, 09Ch
    db 000h, 000h, 000h, 06Ah, 000h, 050h, 0FFh, 015h
    dd __imp__AIL_register_3D_EOS_callback@8
    db 08Bh, 00Fh, 051h, 0FFh, 015h
    dd ?g_Rva13596C0@@3P6GXPAX@ZA
    db 0FFh, 015h
    dd ?Data00F595C4@@3P6AXXZA
    db 0C6h, 044h, 024h, 010h, 001h, 057h, 08Dh, 054h, 024h, 01Ch, 08Dh, 0AEh, 01Ch, 00Bh, 000h, 000h
    db 052h, 08Bh, 0CDh, 0C7h, 044h, 024h, 030h, 001h, 000h, 000h, 000h
    call ?j_0001cce2@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 085h, 0C0h, 075h, 00Dh, 0FFh, 015h
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 0C6h, 044h, 024h, 010h, 000h, 0EBh, 02Fh, 08Bh, 04Ch, 024h, 030h, 039h, 048h, 008h, 074h, 00Dh
    db 0FFh, 015h
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 0C6h, 044h, 024h, 010h, 000h, 0EBh, 019h, 08Bh, 054h, 024h, 01Ch, 083h, 0ECh, 008h, 08Bh, 0CCh
    db 089h, 001h, 089h, 051h, 004h, 08Bh, 0CDh, 089h, 064h, 024h, 01Ch
    call ?j_0003ce89@@YAXXZ
    db 057h, 08Dh, 08Eh, 0C4h, 009h, 000h, 000h
    call ?j_0003a229@@YAXXZ
    db 08Ah, 044h, 024h, 010h, 084h, 0C0h, 0B3h, 001h, 074h, 006h, 0FFh, 015h
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 08Bh, 06Ch, 024h, 030h, 084h, 0DBh, 0C7h, 045h, 00Ch, 004h, 000h, 000h, 000h, 074h, 02Bh, 08Bh
    db 06Dh, 014h, 085h, 0EDh, 074h, 024h, 08Bh, 04Dh, 008h, 085h, 0C9h, 08Dh, 045h, 008h, 074h, 01Ah
    db 08Bh, 091h, 08Ch, 000h, 000h, 000h, 03Bh, 091h, 090h, 000h, 000h, 000h, 074h, 00Ch, 08Bh, 04Dh
    db 028h, 051h, 050h, 08Bh, 0CEh
    call ?j_00049cdd@@YAXXZ
    db 08Bh, 04Ch, 024h, 020h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 01Ch, 0C2h, 004h, 000h, 08Bh, 045h, 008h, 085h, 0C0h, 08Dh, 07Dh, 008h, 074h, 0ABh, 06Ah
    db 000h, 050h, 0FFh, 015h
    dd __imp__AIL_register_stream_callback@8
    db 08Bh, 007h, 050h, 0FFh, 015h
    dd __imp__AIL_close_stream@4
    db 0FFh, 015h
    dd ?Data00F595C4@@3P6AXXZA
    db 0C6h, 044h, 024h, 010h, 001h, 057h, 08Dh, 04Ch, 024h, 01Ch, 08Dh, 0AEh, 030h, 00Bh, 000h, 000h
    db 051h, 08Bh, 0CDh, 0C7h, 044h, 024h, 030h, 002h, 000h, 000h, 000h
    call ?j_0000f41b@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 085h, 0C0h, 08Bh, 03Dh
    dd __imp_?doFree@BfmeFreeHelper@@QAEXXZ
    db 075h, 009h, 0FFh, 0D7h, 0C6h, 044h, 024h, 010h, 000h, 0EBh, 02Bh, 08Bh, 054h, 024h, 030h, 039h
    db 050h, 008h, 074h, 009h, 0FFh, 0D7h, 0C6h, 044h, 024h, 010h, 000h, 0EBh, 019h, 083h, 0ECh, 008h
    db 08Bh, 0CCh, 089h, 001h, 08Bh, 044h, 024h, 024h, 089h, 041h, 004h, 08Bh, 0CDh, 089h, 064h, 024h
    db 01Ch
    call ?j_00007bfd@@YAXXZ
    db 08Ah, 044h, 024h, 010h, 084h, 0C0h, 0B3h, 001h, 00Fh, 084h, 01Fh, 0FFh, 0FFh, 0FFh, 0FFh, 0D7h
    db 0E9h, 018h, 0FFh, 0FFh, 0FFh, 08Bh, 0BEh, 05Ch, 009h, 000h, 000h, 06Ah, 0FFh, 057h, 032h, 0DBh
    db 0FFh, 015h
    dd __imp__WaitForSingleObject@8
    db 03Dh, 002h, 001h, 000h, 000h, 074h, 002h, 0B3h, 001h, 08Bh, 04Dh, 008h, 08Bh, 096h, 044h, 00Bh
    db 000h, 000h, 0C1h, 0E1h, 006h, 084h, 0DBh, 0C6h, 004h, 011h, 000h, 074h, 007h, 057h, 0FFh, 015h
    dd __imp__ReleaseMutex@4
    db 08Bh, 045h, 008h, 08Bh, 08Eh, 044h, 00Bh, 000h, 000h, 0C1h, 0E0h, 006h, 08Bh, 054h, 008h, 004h
    db 052h, 0FFh, 015h
    dd ?g_Rva13596C0@@3P6GXPAX@ZA
    db 08Bh, 045h, 008h, 08Bh, 096h, 044h, 00Bh, 000h, 000h, 0C1h, 0E0h, 006h, 003h, 0C2h, 050h, 08Bh
    db 0CEh
    call ?j_0003b741@@YAXXZ
    db 0B3h, 001h, 0E9h, 0B3h, 0FEh, 0FFh, 0FFh, 08Dh, 049h, 000h
    dd ?d_006a59f0@@YAXXZ + 0C5h
    dd ?d_006a59f0@@YAXXZ + 017Eh
    dd ?d_006a59f0@@YAXXZ + 030Ch
    dd ?d_006a59f0@@YAXXZ + 0273h
?d_006a59f0@@YAXXZ ENDP
_TEXT$d00aa59f0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
