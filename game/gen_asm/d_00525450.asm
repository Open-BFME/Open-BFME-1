.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0?$StringBase@G@@AAE@ABV0@@Z:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ?BfmeDefeatScreenTable@@3PAEA:BYTE
EXTERN ?Glo012F1028@@3PAVGlo012F1028Type@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?TheGameText@@3PAVBfmeGameText@@A:BYTE
EXTERN ?TheMapCache@@3PAVMapCache@@A:BYTE
EXTERN ?TheMappedImageCollection@@3PAVImageCollection@@A:BYTE
EXTERN ?TheMultiplayerSettings@@3PAVMultiplayerSettings@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?format@AsciiString@@QAAXV1@ZZ:NEAR
EXTERN ?format@UnicodeString@@QAAXV1@ZZ:NEAR
EXTERN ?j_00001203@@YAXXZ:NEAR
EXTERN ?j_00007004@@YAXXZ:NEAR
EXTERN ?j_00008602@@YAXXZ:NEAR
EXTERN ?j_0000a3df@@YAXXZ:NEAR
EXTERN ?j_0000a6fa@@YAXXZ:NEAR
EXTERN ?j_0000bcd5@@YAXXZ:NEAR
EXTERN ?j_00010857@@YAXXZ:NEAR
EXTERN ?j_00010898@@YAXXZ:NEAR
EXTERN ?j_0001712a@@YAXXZ:NEAR
EXTERN ?j_0001d01b@@YAXXZ:NEAR
EXTERN ?j_0001d606@@YAXXZ:NEAR
EXTERN ?j_00021ec2@@YAXXZ:NEAR
EXTERN ?j_00024c17@@YAXXZ:NEAR
EXTERN ?j_000267a1@@YAXXZ:NEAR
EXTERN ?j_0002a473@@YAXXZ:NEAR
EXTERN ?j_0002a62b@@YAXXZ:NEAR
EXTERN ?j_0002ed9d@@YAXXZ:NEAR
EXTERN ?j_0002f338@@YAXXZ:NEAR
EXTERN ?j_00030391@@YAXXZ:NEAR
EXTERN ?j_00031327@@YAXXZ:NEAR
EXTERN ?j_00032c4a@@YAXXZ:NEAR
EXTERN ?j_00032e93@@YAXXZ:NEAR
EXTERN ?j_000364c6@@YAXXZ:NEAR
EXTERN ?j_000371b9@@YAXXZ:NEAR
EXTERN ?j_0003827b@@YAXXZ:NEAR
EXTERN ?j_00039a77@@YAXXZ:NEAR
EXTERN ?j_0003aa67@@YAXXZ:NEAR
EXTERN ?j_0003b75a@@YAXXZ:NEAR
EXTERN ?j_0003b971@@YAXXZ:NEAR
EXTERN ?j_0003d32a@@YAXXZ:NEAR
EXTERN ?j_0003f6b6@@YAXXZ:NEAR
EXTERN ?j_0003fe86@@YAXXZ:NEAR
EXTERN ?j_00042f87@@YAXXZ:NEAR
EXTERN ?j_00042fa0@@YAXXZ:NEAR
EXTERN ?j_000439c3@@YAXXZ:NEAR
EXTERN ?j_00046b82@@YAXXZ:NEAR
EXTERN ?j_00047767@@YAXXZ:NEAR
EXTERN ?j_00049f30@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@G@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@G@@QAEXABV1@@Z:NEAR
EXTERN __imp___memicmp:BYTE
EXTERN __imp__timeGetTime@0:BYTE
EXTERN g_Va010303C8:NEAR
EXTERN g_Va010304F8:NEAR
EXTERN g_Va01030744:NEAR
EXTERN g_Va010F9CC0:BYTE
EXTERN g_Va01106108:BYTE
EXTERN g_Va01106BD0:BYTE
EXTERN g_Va01106BF0:BYTE
EXTERN g_Va01106C10:BYTE
EXTERN g_Va01106C40:BYTE
EXTERN g_Va01106CA4:BYTE
EXTERN g_Va01106CCC:BYTE
EXTERN g_Va01106CEC:BYTE
EXTERN g_Va01106D0C:BYTE
EXTERN g_Va01106D2C:BYTE
EXTERN g_Va012B77AF:BYTE
_TEXT SEGMENT

; ghidra: FUN_00925450  retail @ 0x00525450 size 219
public ?d_00525450@@YAXXZ
?d_00525450@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 5Dh, 54h
    db 92h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 93h, 0EFh, 0B1h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 71h, 73h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 61h, 73h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 0A0h, 24h
    db 0B1h, 0FFh, 0Fh, 0BFh, 0C0h, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h
    db 0F8h, 6Ah, 0Eh, 6Ah, 03h, 0E8h, 5Ah, 3Dh, 0B2h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h
    db 31h, 0C0h, 74h, 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h
    db 00h, 31h, 0C0h, 74h, 07h, 0Fh, 0BFh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 74h, 08h
    db 8Bh, 45h, 0F8h, 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 13h
    db 02h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 5Dh
    db 54h, 92h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh
    db 0CDh, 0CEh, 58h, 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_00525450@@YAXXZ ENDP

; ghidra: FUN_00925590  retail @ 0x00525590 size 220
public ?d_00525590@@YAXXZ
?d_00525590@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 9Dh, 55h
    db 92h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 53h, 0EEh, 0B1h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 31h, 72h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 21h, 72h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 9Ch, 0Bh
    db 0B0h, 0FFh, 0Fh, 0BFh, 0C0h, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h
    db 0F8h, 6Ah, 0Eh, 6Ah, 03h, 0E8h, 1Ah, 3Ch, 0B2h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h
    db 31h, 0C0h, 74h, 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h
    db 00h, 31h, 0C0h, 40h, 74h, 07h, 0Fh, 0BFh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 74h
    db 08h, 8Bh, 45h, 0F8h, 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h
    db 0D2h, 00h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h
    db 9Dh, 55h, 92h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh
    db 0CCh, 0CDh, 0CEh, 58h, 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_00525590@@YAXXZ ENDP

; ghidra: FUN_009256d0  retail @ 0x005256D0 size 219
public ?d_005256d0@@YAXXZ
?d_005256d0@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0DDh, 56h
    db 92h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 13h, 0EDh, 0B1h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 0F1h, 70h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 0E1h, 70h, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 0C9h, 92h
    db 0B0h, 0FFh, 0Fh, 0BFh, 0C0h, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h
    db 0F8h, 6Ah, 02h, 6Ah, 03h, 0E8h, 0DAh, 3Ah, 0B2h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h
    db 31h, 0C0h, 74h, 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h
    db 00h, 31h, 0C0h, 74h, 07h, 0Fh, 0BFh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 74h, 08h
    db 8Bh, 45h, 0F8h, 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 93h
    db 0FFh, 0AFh, 0FFh, 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0DDh
    db 56h, 92h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh
    db 0CDh, 0CEh, 58h, 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_005256d0@@YAXXZ ENDP

; ghidra: FUN_00925800  retail @ 0x00525800 size 220
public ?d_00525800@@YAXXZ
?d_00525800@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0Dh, 58h
    db 92h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 0E3h, 0EBh, 0B1h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 0C1h, 6Fh, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 0B1h, 6Fh, 0B0h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 3Eh, 83h
    db 0B0h, 0FFh, 0Fh, 0BFh, 0C0h, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h
    db 0F8h, 6Ah, 0Dh, 6Ah, 03h, 0E8h, 0AAh, 39h, 0B2h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h
    db 31h, 0C0h, 74h, 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h
    db 00h, 31h, 0C0h, 74h, 07h, 0Fh, 0BFh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 40h, 74h
    db 08h, 8Bh, 45h, 0F8h, 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h
    db 62h, 0FEh, 0AFh, 0FFh, 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h
    db 0Dh, 58h, 92h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh
    db 0CCh, 0CDh, 0CEh, 58h, 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_00525800@@YAXXZ ENDP

; ghidra: FUN_009259a0  retail @ 0x005259A0 size 109
public ?d_005259a0@@YAXXZ
?d_005259a0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 55h, 8Bh, 6Ch, 24h, 1Ch, 56h, 8Bh, 74h, 24h, 14h, 57h
    db 8Bh, 7Ch, 24h, 28h, 39h, 5Ch, 24h, 1Ch, 75h, 06h, 39h, 74h, 24h, 20h, 74h, 46h
    db 8Bh, 0CEh, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 8Bh, 0CFh, 0BAh, 01h, 00h, 00h, 00h
    db 0D3h, 0E2h, 85h, 55h, 00h, 8Bh, 13h, 0Fh, 95h, 0C1h, 85h, 0D0h, 0Fh, 95h, 0C2h, 3Ah
    db 0D1h, 75h, 1Ch, 8Bh, 0C6h, 46h, 83h, 0F8h, 1Fh, 75h, 05h, 33h, 0F6h, 83h, 0C3h, 04h
    db 8Bh, 0CFh, 47h, 83h, 0F9h, 1Fh, 75h, 0BCh, 33h, 0FFh, 83h, 0C5h, 04h, 0EBh, 0B5h, 5Fh
    db 5Eh, 5Dh, 32h, 0C0h, 5Bh, 0C3h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 0C3h
?d_005259a0@@YAXXZ ENDP

; ghidra: FUN_00925ab0  retail @ 0x00525AB0 size 480
public ?d_00525ab0@@YAXXZ
?d_00525ab0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 18h, 85h, 0DBh, 55h, 8Bh, 0E9h, 0Fh, 84h, 0C5h
    db 01h, 00h, 00h, 8Bh, 44h, 24h, 14h, 56h, 57h, 0BFh, 78h, 6Bh, 10h, 01h, 8Bh, 0F0h
    db 0B9h, 08h, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 3Dh, 0F6h, 85h, 20h, 01h, 00h
    db 00h, 01h, 89h, 9Dh, 08h, 01h, 00h, 00h, 0Fh, 84h, 98h, 01h, 00h, 00h, 8Dh, 44h
    db 24h, 10h, 50h, 6Ah, 02h, 53h, 0C7h, 44h, 24h, 1Ch, 0Ah, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 20h, 5Ah, 00h, 00h, 00h, 0E8h, 0CCh, 4Bh, 0AEh, 0FFh, 83h, 0C4h, 0Ch, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 0BFh, 5Ch, 6Bh, 10h, 01h, 8Bh, 0F0h, 0B9h
    db 16h, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 10h, 5Fh, 5Eh, 89h, 9Dh, 1Ch, 01h
    db 00h, 00h, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 0BFh, 40h, 6Bh, 10h, 01h, 8Bh
    db 0F0h, 0B9h, 15h, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 10h, 5Fh, 5Eh, 89h, 9Dh
    db 18h, 01h, 00h, 00h, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 8Dh, 4Ch, 24h, 24h
    db 51h, 68h, 0B4h, 0C7h, 07h, 01h, 50h, 0FFh, 15h, 94h, 94h, 35h, 01h, 83h, 0C4h, 0Ch
    db 83h, 0F8h, 01h, 0Fh, 85h, 0Dh, 01h, 00h, 00h, 83h, 7Ch, 24h, 24h, 08h, 0Fh, 87h
    db 02h, 01h, 00h, 00h, 8Bh, 54h, 24h, 1Ch, 52h, 0E8h, 0BBh, 13h, 0B0h, 0FFh, 83h, 0C4h
    db 04h, 0BFh, 0F4h, 40h, 08h, 01h, 8Bh, 0F0h, 0B9h, 07h, 00h, 00h, 00h, 33h, 0D2h, 0F3h
    db 0A6h, 75h, 30h, 53h, 0E8h, 5Bh, 14h, 0AEh, 0FFh, 8Bh, 44h, 24h, 28h, 83h, 0C4h, 04h
    db 68h, 27h, 0D7h, 42h, 00h, 53h, 89h, 5Ch, 85h, 68h, 0E8h, 0BCh, 7Eh, 0AEh, 0FFh, 83h
    db 0C4h, 04h, 8Bh, 0C8h, 0E8h, 5Eh, 75h, 0B1h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h
    db 0C2h, 0Ch, 00h, 0BFh, 58h, 0C7h, 07h, 01h, 8Bh, 0F0h, 0B9h, 0Fh, 00h, 00h, 00h, 33h
    db 0D2h, 0F3h, 0A6h, 75h, 1Eh, 53h, 0E8h, 19h, 14h, 0AEh, 0FFh, 8Bh, 44h, 24h, 28h, 83h
    db 0C4h, 04h, 5Fh, 5Eh, 89h, 9Ch, 85h, 0C8h, 00h, 00h, 00h, 5Dh, 5Bh, 83h, 0C4h, 08h
    db 0C2h, 0Ch, 00h, 0BFh, 9Ch, 5Fh, 08h, 01h, 8Bh, 0F0h, 0B9h, 05h, 00h, 00h, 00h, 33h
    db 0D2h, 0F3h, 0A6h, 75h, 1Eh, 53h, 0E8h, 0E9h, 13h, 0AEh, 0FFh, 8Bh, 44h, 24h, 28h, 83h
    db 0C4h, 04h, 5Fh, 5Eh, 89h, 9Ch, 85h, 0A8h, 00h, 00h, 00h, 5Dh, 5Bh, 83h, 0C4h, 08h
    db 0C2h, 0Ch, 00h, 0BFh, 50h, 0C7h, 07h, 01h, 8Bh, 0F0h, 0B9h, 06h, 00h, 00h, 00h, 33h
    db 0D2h, 0F3h, 0A6h, 75h, 24h, 53h, 0E8h, 0B9h, 13h, 0AEh, 0FFh, 8Bh, 44h, 24h, 28h, 83h
    db 0C4h, 04h, 53h, 8Dh, 8Ch, 85h, 88h, 00h, 00h, 00h, 0E8h, 0F0h, 7Bh, 0AFh, 0FFh, 5Fh
    db 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 0BFh, 30h, 6Bh, 10h, 01h, 8Bh, 0F0h
    db 0B9h, 0Ch, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 75h, 0Bh, 8Bh, 44h, 24h, 24h, 89h
    db 9Ch, 85h, 0E8h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_00525ab0@@YAXXZ ENDP

; ghidra: FUN_00925d10  retail @ 0x00525D10 size 368
public ?d_00525d10@@YAXXZ
?d_00525d10@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 03h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 33h, 0FFh, 3Bh
    db 0C7h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h
    db 89h, 7Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C7h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h
    db 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 7Eh, 0Ch, 39h, 7Eh, 08h, 75h, 15h, 5Fh
    db 32h, 0C0h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 04h, 00h, 55h, 8Bh, 6Ch, 24h, 20h, 8Dh, 84h, 0AEh, 88h, 00h, 00h, 00h
    db 50h, 8Dh, 4Ch, 24h, 10h, 0C6h, 46h, 17h, 00h, 0E8h, 81h, 5Bh, 0AFh, 0FFh, 8Dh, 4Ch
    db 24h, 0Ch, 89h, 7Ch, 24h, 18h, 0E8h, 53h, 10h, 0B2h, 0FFh, 50h, 8Dh, 4Ch, 24h, 10h
    db 0E8h, 9Ch, 2Eh, 0AFh, 0FFh, 8Bh, 0F8h, 83h, 0FFh, 0FFh, 7Dh, 27h, 8Dh, 4Ch, 24h, 0Ch
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 96h, 8Dh, 0B1h, 0FFh, 5Dh, 5Fh, 32h
    db 0C0h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C2h, 04h, 00h, 8Bh, 4Eh, 08h, 53h, 55h, 0E8h, 3Bh, 8Eh, 0AFh, 0FFh, 8Bh, 0D8h, 85h
    db 0DBh, 75h, 28h, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 5Fh, 8Dh, 0B1h, 0FFh, 5Bh, 5Dh, 5Fh, 32h, 0C0h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 3Bh, 7Bh, 0Ch, 74h, 0D3h
    db 8Bh, 0Dh, 0FCh, 0D5h, 2Eh, 01h, 8Bh, 51h, 3Ch, 85h, 0D2h, 8Dh, 41h, 3Ch, 75h, 05h
    db 8Bh, 49h, 34h, 89h, 08h, 3Bh, 38h, 7Dh, 0BAh, 83h, 0FFh, 0FFh, 74h, 1Eh, 33h, 0EDh
    db 8Bh, 4Eh, 08h, 55h, 0E8h, 0DFh, 8Dh, 0AFh, 0FFh, 85h, 0C0h, 74h, 09h, 3Bh, 78h, 0Ch
    db 75h, 04h, 3Bh, 0D8h, 75h, 9Dh, 45h, 83h, 0FDh, 08h, 7Ch, 0E4h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 57h, 53h, 0FFh, 52h, 0Ch, 8Dh, 4Ch, 24h, 10h, 8Ah, 0D8h, 0C7h, 44h, 24h, 1Ch
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0EAh, 8Ch, 0B1h, 0FFh, 8Bh, 4Ch, 24h, 14h, 8Ah, 0C3h, 5Bh
    db 5Dh, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00525d10@@YAXXZ ENDP

; ghidra: FUN_00925ee0  retail @ 0x00525EE0 size 117
public ?d_00525ee0@@YAXXZ
?d_00525ee0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 0C6h, 86h, 24h, 01h, 00h, 00h, 00h
    db 74h, 14h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h, 0C7h
    db 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 14h, 8Bh, 4Eh, 04h
    db 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h, 0C7h, 46h, 0Ch, 00h, 00h, 00h
    db 00h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 2Ah, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 08h, 50h
    db 0E8h, 59h, 93h, 0B0h, 0FFh, 8Bh, 0Dh, 94h, 15h, 2Fh, 01h, 0E8h, 40h, 39h, 0AFh, 0FFh
    db 85h, 0C0h, 74h, 0Eh, 8Ah, 48h, 25h, 84h, 0C9h, 74h, 07h, 0C6h, 86h, 24h, 01h, 00h
    db 00h, 01h, 5Eh, 59h, 0C3h
?d_00525ee0@@YAXXZ ENDP

; ghidra: FUN_00925f80  retail @ 0x00525F80 size 146
public ?d_00525f80@@YAXXZ
?d_00525f80@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 57h, 74h, 14h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 14h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h
    db 84h, 0C0h, 75h, 07h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 8Bh, 4Eh, 08h, 85h, 0C9h
    db 74h, 48h, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 0Ch, 50h, 0E8h, 0BFh, 92h, 0B0h, 0FFh, 8Bh
    db 0Dh, 94h, 15h, 2Fh, 01h, 0E8h, 0A6h, 38h, 0AFh, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h, 2Ah
    db 8Bh, 4Ch, 24h, 10h, 51h, 8Bh, 4Eh, 08h, 0E8h, 2Bh, 8Ch, 0AFh, 0FFh, 85h, 0C0h, 74h
    db 19h, 8Bh, 40h, 10h, 85h, 0C0h, 7Ch, 12h, 3Bh, 47h, 20h, 7Dh, 0Dh, 8Dh, 14h, 80h
    db 8Dh, 44h, 97h, 54h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h, 5Fh, 33h, 0C0h, 5Eh, 59h, 0C2h
    db 04h, 00h
?d_00525f80@@YAXXZ ENDP

; ghidra: FUN_00926040  retail @ 0x00526040 size 139
public ?d_00526040@@YAXXZ
?d_00526040@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 80h, 03h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 89h
    db 4Eh, 0Ch, 74h, 21h, 8Dh, 44h, 24h, 04h, 50h, 0E8h, 20h, 92h, 0B0h, 0FFh, 50h, 8Dh
    db 4Eh, 28h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0E8h, 0D8h, 8Bh, 0B1h, 0FFh, 8Dh
    db 4Ch, 24h, 04h, 0EBh, 27h, 68h, 1Ch, 30h, 07h, 01h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 2Dh
    db 2Bh, 36h, 00h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 4Eh, 28h, 0C7h, 44h, 24h, 14h, 01h
    db 00h, 00h, 00h, 0E8h, 0AFh, 8Bh, 0B1h, 0FFh, 8Dh, 4Ch, 24h, 18h, 0C7h, 44h, 24h, 10h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 87h, 18h, 36h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00526040@@YAXXZ ENDP

; ghidra: FUN_00926510  retail @ 0x00526510 size 112
public ?d_00526510@@YAXXZ
?d_00526510@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 42h, 08h, 53h, 8Bh, 5Ah, 04h, 55h, 56h, 8Bh, 74h, 24h
    db 14h, 8Bh, 2Eh, 8Bh, 4Eh, 08h, 2Bh, 0CDh, 8Bh, 6Eh, 04h, 57h, 8Bh, 3Ah, 2Bh, 0C7h
    db 0C1h, 0F9h, 02h, 0C1h, 0F8h, 02h, 0C1h, 0E1h, 05h, 0C1h, 0E0h, 05h, 2Bh, 0CDh, 8Bh, 6Eh
    db 0Ch, 2Bh, 0C3h, 8Bh, 5Ah, 0Ch, 03h, 0CDh, 03h, 0C3h, 3Bh, 0C1h, 75h, 2Bh, 8Bh, 46h
    db 04h, 8Bh, 0Eh, 50h, 51h, 8Bh, 4Ah, 08h, 8Bh, 0C3h, 50h, 8Bh, 42h, 04h, 51h, 50h
    db 8Bh, 0CFh, 51h, 0E8h, 0F5h, 48h, 0B2h, 0FFh, 83h, 0C4h, 18h, 84h, 0C0h, 74h, 0Ah, 5Fh
    db 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 0C3h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 0C3h
?d_00526510@@YAXXZ ENDP

; ghidra: FUN_009265f0  retail @ 0x005265F0 size 8
public ?d_005265f0@@YAXXZ
?d_005265f0@@YAXXZ PROC
    db 6Ah, 00h, 0E8h, 5Ah, 23h, 0B1h, 0FFh, 0C3h
?d_005265f0@@YAXXZ ENDP

; ghidra: FUN_00926600  retail @ 0x00526600 size 74
public ?d_00526600@@YAXXZ
?d_00526600@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 14h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h
    db 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 46h
    db 0Ch, 85h, 0C0h, 74h, 14h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h
    db 75h, 07h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 08h
    db 50h, 8Bh, 0CEh, 0E8h, 09h, 23h, 0B1h, 0FFh, 5Eh, 0C3h
?d_00526600@@YAXXZ ENDP

; ghidra: FUN_009268f0  retail @ 0x005268F0 size 544
_TEXT ENDS
_TEXT$d009268f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x009268F0 size 544
public ?d_005268f0@@YAXXZ
?d_005268f0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va010303C8
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 018h, 053h, 055h, 056h, 033h, 0EDh, 057h, 08Bh, 0F1h, 089h, 06Ch, 024h, 010h, 08Bh, 07Ch, 024h
    db 038h, 083h, 0CBh, 0FFh, 057h, 089h, 06Ch, 024h, 034h, 089h, 05Ch, 024h, 018h
    call ?j_0003aa67@@YAXXZ
    db 03Bh, 0C5h, 074h, 007h, 08Bh, 040h, 004h, 089h, 044h, 024h, 014h, 08Bh, 094h, 0BEh, 0A8h, 000h
    db 000h, 000h, 08Dh, 04Ch, 024h, 038h, 051h, 052h, 089h, 05Ch, 024h, 020h
    call ?j_0003b75a@@YAXXZ
    db 08Bh, 044h, 024h, 040h, 083h, 0C4h, 008h, 03Bh, 0C5h, 07Ch, 015h, 050h, 08Bh, 084h, 0BEh, 0A8h
    db 000h, 000h, 000h, 050h
    call ?j_0003b971@@YAXXZ
    db 083h, 0C4h, 008h, 089h, 044h, 024h, 018h, 08Bh, 08Ch, 0BEh, 0A8h, 000h, 000h, 000h, 051h
    call ?j_00007004@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheMultiplayerSettings@@3PAVMultiplayerSettings@@A
    db 083h, 0C4h, 004h, 053h
    call ?j_00021ec2@@YAXXZ
    db 08Bh, 0D8h, 08Ah, 044h, 024h, 03Ch, 084h, 0C0h, 075h, 006h, 039h, 06Ch, 024h, 014h, 07Dh, 058h
    db 08Bh, 043h, 010h, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 050h, 051h, 08Bh, 0C4h, 089h, 064h, 024h, 028h, 055h, 068h
    dd g_Va01106108
    db 050h, 0FFh, 052h, 028h, 08Bh, 08Ch, 0BEh, 0A8h, 000h, 000h, 000h, 051h
    call ?j_0002f338@@YAXXZ
    db 08Bh, 094h, 0BEh, 0A8h, 000h, 000h, 000h, 06Ah, 0FFh, 050h, 052h, 089h, 044h, 024h, 050h
    call ?j_0001d01b@@YAXXZ
    db 08Ah, 044h, 024h, 054h, 083h, 0C4h, 018h, 084h, 0C0h, 074h, 00Fh, 08Bh, 084h, 0BEh, 0A8h, 000h
    db 000h, 000h, 055h, 055h, 050h, 0E9h, 0F4h, 000h, 000h, 000h, 089h, 06Ch, 024h, 01Ch, 08Bh, 044h
    db 024h, 014h, 085h, 0C0h, 07Ch, 008h, 03Bh, 0C5h, 00Fh, 085h, 0C7h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 03Ch, 000h, 000h, 000h, 000h, 08Dh, 04Dh, 001h, 051h, 051h, 089h, 064h, 024h, 02Ch, 08Bh
    db 0CCh, 068h
    dd g_Va010F9CC0
    db 0C6h, 044h, 024h, 03Ch, 001h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 044h, 052h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 08Bh, 044h, 024h, 048h, 083h, 0C4h, 00Ch, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 06Ah, 000h, 050h, 08Dh, 044h, 024h, 028h, 050h, 0FFh, 052h, 028h, 050h, 08Dh, 04Ch
    db 024h, 014h, 0C6h, 044h, 024h, 034h, 002h
    call ?set@?$StringBase@G@@QAEXABV1@@Z
    db 08Dh, 04Ch, 024h, 020h, 0C6h, 044h, 024h, 030h, 001h
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 043h, 010h, 050h, 051h, 08Dh, 054h, 024h, 018h, 089h, 064h, 024h, 02Ch, 08Bh, 0CCh, 052h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 08Bh, 084h, 0BEh, 0A8h, 000h, 000h, 000h, 050h
    call ?j_0002f338@@YAXXZ
    db 08Bh, 08Ch, 0BEh, 0A8h, 000h, 000h, 000h, 055h, 050h, 051h, 089h, 044h, 024h, 050h
    call ?j_0001d01b@@YAXXZ
    db 08Bh, 044h, 024h, 030h, 083h, 0C4h, 018h, 03Bh, 0E8h, 075h, 008h, 08Bh, 054h, 024h, 038h, 089h
    db 054h, 024h, 01Ch, 08Dh, 04Ch, 024h, 03Ch, 0C6h, 044h, 024h, 030h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 045h, 083h, 0FDh, 004h, 00Fh, 08Ch, 01Fh, 0FFh, 0FFh, 0FFh, 08Bh, 044h, 024h, 01Ch, 08Bh, 08Ch
    db 0BEh, 0A8h, 000h, 000h, 000h, 06Ah, 000h, 050h, 051h
    call ?j_000439c3@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 083h, 0C4h, 00Ch, 0C7h, 044h, 024h, 030h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 04Ch, 024h, 028h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 024h, 0C2h, 008h, 000h
?d_005268f0@@YAXXZ ENDP
_TEXT$d009268f0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00926bc0  retail @ 0x00526BC0 size 120
public ?d_00526bc0@@YAXXZ
?d_00526bc0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 8Dh, 7Bh, 1Fh, 0C1h, 0EFh, 05h, 85h, 0FFh, 8Bh
    db 0F1h, 74h, 23h, 8Dh, 04h, 0BDh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 50h
    db 76h, 0Ah, 0E8h, 49h, 0B3h, 35h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ch, 0E8h, 4Fh, 79h, 30h
    db 00h, 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Dh, 0Ch, 0B8h, 89h, 4Eh, 10h, 33h, 0C9h
    db 89h, 06h, 8Bh, 0F8h, 89h, 4Eh, 04h, 8Bh, 0CBh, 8Bh, 0C1h, 99h, 83h, 0E2h, 1Fh, 03h
    db 0C2h, 0C1h, 0F8h, 05h, 81h, 0E1h, 1Fh, 00h, 00h, 80h, 8Dh, 04h, 87h, 79h, 0Dh, 49h
    db 83h, 0C9h, 0E0h, 41h, 79h, 06h, 83h, 0C1h, 20h, 83h, 0E8h, 04h, 5Fh, 89h, 46h, 08h
    db 89h, 4Eh, 0Ch, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_00526bc0@@YAXXZ ENDP

; ghidra: FUN_00926c80  retail @ 0x00526C80 size 171
public ?d_00526c80@@YAXXZ
?d_00526c80@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 6Ch, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 10h, 77h, 2Bh, 01h, 8Bh, 14h
    db 95h, 24h, 77h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 0C0h, 50h
    db 0ACh, 10h, 0C7h, 40h, 08h, 42h, 48h, 80h, 14h, 0C7h, 40h, 0Ch, 4Fh, 1Ah, 24h, 04h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 0C0h, 50h, 0ACh, 10h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 42h, 48h, 80h, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 4Fh, 1Ah, 24h, 04h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_00526c80@@YAXXZ ENDP

; ghidra: FUN_00926d60  retail @ 0x00526D60 size 171
public ?d_00526d60@@YAXXZ
?d_00526d60@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 64h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 38h, 77h, 2Bh, 01h, 8Bh, 14h
    db 95h, 4Ch, 77h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 0C0h, 50h
    db 0ACh, 10h, 0C7h, 40h, 08h, 42h, 48h, 80h, 14h, 0C7h, 40h, 0Ch, 0C0h, 50h, 0ACh, 10h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 0C0h, 50h, 0ACh, 10h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 42h, 48h, 80h, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 0C0h, 50h, 0ACh, 10h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_00526d60@@YAXXZ ENDP

; ghidra: FUN_00926e40  retail @ 0x00526E40 size 171
public ?d_00526e40@@YAXXZ
?d_00526e40@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 6Ch, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 60h, 77h, 2Bh, 01h, 8Bh, 14h
    db 95h, 74h, 77h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 0C0h, 50h
    db 0ACh, 10h, 0C7h, 40h, 08h, 42h, 48h, 80h, 14h, 0C7h, 40h, 0Ch, 43h, 48h, 80h, 14h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 0C0h, 50h, 0ACh, 10h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 42h, 48h, 80h, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 43h, 48h, 80h, 14h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_00526e40@@YAXXZ ENDP

; ghidra: FUN_00926f20  retail @ 0x00526F20 size 171
public ?d_00526f20@@YAXXZ
?d_00526f20@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 64h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 88h, 77h, 2Bh, 01h, 8Bh, 14h
    db 95h, 9Ch, 77h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 0C0h, 50h
    db 0ACh, 10h, 0C7h, 40h, 08h, 42h, 48h, 80h, 14h, 0C7h, 40h, 0Ch, 0CCh, 1Ah, 00h, 00h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 0C0h, 50h, 0ACh, 10h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 42h, 48h, 80h, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 0CCh, 1Ah, 00h, 00h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_00526f20@@YAXXZ ENDP

; ghidra: FUN_00927050  retail @ 0x00527050 size 176
public ?d_00527050@@YAXXZ
?d_00527050@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 03h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 55h, 56h, 57h, 6Ah, 00h, 8Bh, 0F9h, 0E8h
    db 7Bh, 0D5h, 0B0h, 0FFh, 83h, 0C4h, 04h, 68h, 0C8h, 6Ah, 10h, 01h, 8Dh, 4Ch, 24h, 10h
    db 0E8h, 3Bh, 1Bh, 36h, 00h, 51h, 89h, 64h, 24h, 14h, 8Bh, 0ECh, 6Ah, 10h, 0C7h, 44h
    db 24h, 24h, 00h, 00h, 00h, 00h, 0BEh, 9Bh, 52h, 44h, 00h, 0E8h, 90h, 0AEh, 35h, 00h
    db 83h, 0C4h, 04h, 85h, 0C0h, 74h, 15h, 0C7h, 40h, 04h, 00h, 00h, 00h, 00h, 0C7h, 00h
    db 24h, 6Bh, 10h, 01h, 89h, 78h, 08h, 89h, 70h, 0Ch, 0EBh, 02h, 33h, 0C0h, 85h, 0C0h
    db 89h, 45h, 00h, 74h, 03h, 0FFh, 40h, 04h, 8Dh, 44h, 24h, 10h, 50h, 0E8h, 42h, 6Eh
    db 0B1h, 0FFh, 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 5Ah, 08h, 36h, 00h, 8Dh, 4Fh, 28h, 0E8h, 0Dh, 0ACh, 0AFh, 0FFh, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Dh, 83h, 0C4h, 14h, 0C3h
?d_00527050@@YAXXZ ENDP

; ghidra: FUN_00927130  retail @ 0x00527130 size 162
public ?d_00527130@@YAXXZ
?d_00527130@@YAXXZ PROC
    db 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 10h, 8Bh
    db 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 7Eh, 08h, 8Bh
    db 46h, 0Ch, 3Bh, 0C7h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h
    db 0C0h, 75h, 03h, 89h, 7Eh, 0Ch, 8Bh, 4Eh, 08h, 3Bh, 0CFh, 74h, 46h, 8Dh, 44h, 24h
    db 0Ch, 50h, 0E8h, 17h, 81h, 0B0h, 0FFh, 8Bh, 7Ch, 24h, 14h, 50h, 8Bh, 0CFh, 0E8h, 42h
    db 0AFh, 0AFh, 0FFh, 85h, 0C0h, 8Dh, 4Ch, 24h, 0Ch, 0Fh, 95h, 0C3h, 0E8h, 0AFh, 07h, 36h
    db 00h, 84h, 0DBh, 74h, 1Eh, 51h, 89h, 64h, 24h, 18h, 8Bh, 0CCh, 57h, 0E8h, 0BEh, 09h
    db 36h, 00h, 8Bh, 4Eh, 08h, 0E8h, 31h, 44h, 0AFh, 0FFh, 8Bh, 4Eh, 04h, 8Bh, 11h, 57h
    db 0FFh, 52h, 20h, 8Bh, 0CEh, 0E8h, 0Ch, 07h, 0B1h, 0FFh, 0B0h, 01h, 5Fh, 88h, 46h, 15h
    db 88h, 46h, 14h, 88h, 46h, 10h, 88h, 46h, 12h, 88h, 46h, 13h, 5Eh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_00527130@@YAXXZ ENDP

; ghidra: FUN_00927220  retail @ 0x00527220 size 911
public ?d_00527220@@YAXXZ
?d_00527220@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 18h, 04h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 2Ch
    db 8Bh, 0F1h, 8Bh, 44h, 0BEh, 68h, 33h, 0EDh, 3Bh, 0C5h, 0Fh, 84h, 4Ah, 03h, 00h, 00h
    db 89h, 6Ch, 24h, 14h, 50h, 89h, 6Ch, 24h, 28h, 0E8h, 4Eh, 58h, 0B0h, 0FFh, 8Bh, 0D8h
    db 83h, 0C4h, 04h, 83h, 0FBh, 0FFh, 75h, 31h, 8Bh, 44h, 0BEh, 68h, 50h, 8Dh, 4Ch, 24h
    db 30h, 51h, 0E8h, 5Dh, 98h, 0B1h, 0FFh, 83h, 0C4h, 08h, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h
    db 44h, 24h, 28h, 01h, 0E8h, 0A7h, 12h, 36h, 00h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h
    db 24h, 00h, 0E8h, 39h, 0Fh, 36h, 00h, 0EBh, 10h, 8Bh, 54h, 0BEh, 68h, 53h, 52h, 0E8h
    db 0CDh, 46h, 0B1h, 0FFh, 83h, 0C4h, 08h, 8Bh, 0D8h, 8Bh, 44h, 0BEh, 68h, 50h, 0E8h, 51h
    db 0FDh, 0ADh, 0FFh, 8Bh, 4Ch, 0BEh, 68h, 83h, 0C4h, 04h, 0E8h, 79h, 0F2h, 0B1h, 0FFh, 3Bh
    db 0C5h, 74h, 0Bh, 8Bh, 40h, 28h, 3Bh, 0C5h, 74h, 04h, 8Bh, 0C8h, 0EBh, 02h, 33h, 0C9h
    db 68h, 27h, 0D7h, 42h, 00h, 0E8h, 4Dh, 5Eh, 0B1h, 0FFh, 8Bh, 46h, 08h, 3Bh, 0C5h, 0C6h
    db 44h, 24h, 2Ch, 01h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h
    db 0C0h, 75h, 03h, 89h, 6Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C5h, 74h, 10h, 8Bh, 4Eh, 04h
    db 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 6Eh, 0Ch, 8Bh, 4Eh, 08h
    db 3Bh, 0CDh, 74h, 3Eh, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 14h, 50h, 0E8h, 6Dh, 7Fh, 0B0h
    db 0FFh, 8Bh, 0Dh, 94h, 15h, 2Fh, 01h, 0E8h, 54h, 25h, 0AFh, 0FFh, 3Bh, 0C5h, 74h, 22h
    db 8Bh, 68h, 20h, 85h, 0EDh, 0C6h, 44h, 24h, 2Ch, 00h, 7Eh, 16h, 83h, 0C0h, 55h, 90h
    db 8Ah, 08h, 8Ah, 54h, 24h, 2Ch, 0Ah, 0D1h, 83h, 0C0h, 14h, 4Dh, 88h, 54h, 24h, 2Ch
    db 75h, 0EEh, 8Bh, 4Eh, 08h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 74h
    db 5Ah, 8Bh, 11h, 0FFh, 52h, 14h, 3Bh, 0C7h, 75h, 51h, 0C7h, 44h, 24h, 2Ch, 00h, 00h
    db 00h, 00h, 0A1h, 0F4h, 76h, 2Bh, 01h, 50h, 51h, 8Dh, 54h, 24h, 34h, 89h, 64h, 24h
    db 18h, 8Bh, 0CCh, 52h, 0C6h, 44h, 24h, 30h, 02h, 0E8h, 72h, 10h, 36h, 00h, 8Bh, 44h
    db 0BEh, 68h, 50h, 0E8h, 0A0h, 7Fh, 0B0h, 0FFh, 8Bh, 4Ch, 0BEh, 68h, 6Ah, 00h, 50h, 51h
    db 0E8h, 76h, 5Ch, 0AFh, 0FFh, 83h, 0C4h, 18h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 24h
    db 00h, 0E8h, 1Ah, 0Eh, 36h, 00h, 0E9h, 84h, 01h, 00h, 00h, 0F6h, 86h, 20h, 01h, 00h
    db 00h, 02h, 74h, 0Bh, 85h, 0DBh, 75h, 4Ch, 0BBh, 01h, 00h, 00h, 00h, 0EBh, 45h, 8Bh
    db 15h, 0F4h, 76h, 2Bh, 01h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 52h, 51h, 8Bh
    db 0D4h, 89h, 64h, 24h, 20h, 6Ah, 00h, 68h, 0C4h, 0F2h, 0Fh, 01h, 52h, 0FFh, 50h, 28h
    db 8Bh, 44h, 0BEh, 68h, 50h, 0E8h, 3Eh, 7Fh, 0B0h, 0FFh, 8Bh, 4Ch, 0BEh, 68h, 8Bh, 0E8h
    db 6Ah, 00h, 55h, 51h, 0E8h, 12h, 5Ch, 0AFh, 0FFh, 83h, 0C4h, 18h, 85h, 0DBh, 75h, 04h
    db 89h, 6Ch, 24h, 10h, 8Bh, 15h, 0F4h, 76h, 2Bh, 01h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h
    db 8Bh, 01h, 52h, 51h, 8Bh, 0D4h, 89h, 64h, 24h, 20h, 6Ah, 00h, 68h, 0B4h, 0F2h, 0Fh
    db 01h, 52h, 0FFh, 50h, 28h, 8Bh, 44h, 0BEh, 68h, 50h, 0E8h, 0F9h, 7Eh, 0B0h, 0FFh, 8Bh
    db 4Ch, 0BEh, 68h, 8Bh, 0E8h, 6Ah, 01h, 55h, 51h, 0E8h, 0CDh, 5Bh, 0AFh, 0FFh, 83h, 0C4h
    db 18h, 83h, 0FBh, 01h, 75h, 04h, 89h, 6Ch, 24h, 10h, 8Ah, 44h, 24h, 2Ch, 84h, 0C0h
    db 0Fh, 84h, 0D2h, 00h, 00h, 00h, 8Bh, 15h, 0F4h, 76h, 2Bh, 01h, 8Bh, 0Dh, 7Ch, 14h
    db 2Fh, 01h, 8Bh, 01h, 52h, 51h, 8Bh, 0D4h, 89h, 64h, 24h, 34h, 6Ah, 00h, 68h, 88h
    db 0E7h, 0Fh, 01h, 52h, 0FFh, 50h, 28h, 8Bh, 44h, 0BEh, 68h, 50h, 0E8h, 0A7h, 7Eh, 0B0h
    db 0FFh, 8Bh, 4Ch, 0BEh, 68h, 8Bh, 0E8h, 6Ah, 02h, 55h, 51h, 0E8h, 7Bh, 5Bh, 0AFh, 0FFh
    db 83h, 0C4h, 18h, 83h, 0FBh, 02h, 75h, 04h, 89h, 6Ch, 24h, 10h, 8Bh, 15h, 0F4h, 76h
    db 2Bh, 01h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 52h, 51h, 8Bh, 0D4h, 89h, 64h
    db 24h, 34h, 6Ah, 00h, 68h, 98h, 0E7h, 0Fh, 01h, 52h, 0FFh, 50h, 28h, 8Bh, 44h, 0BEh
    db 68h, 50h, 0E8h, 61h, 7Eh, 0B0h, 0FFh, 8Bh, 4Ch, 0BEh, 68h, 8Bh, 0E8h, 6Ah, 03h, 55h
    db 51h, 0E8h, 35h, 5Bh, 0AFh, 0FFh, 83h, 0C4h, 18h, 83h, 0FBh, 03h, 75h, 04h, 89h, 6Ch
    db 24h, 10h, 8Bh, 15h, 0F4h, 76h, 2Bh, 01h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h
    db 52h, 51h, 8Bh, 0D4h, 89h, 64h, 24h, 34h, 6Ah, 00h, 68h, 0A8h, 0E7h, 0Fh, 01h, 52h
    db 0FFh, 50h, 28h, 8Bh, 44h, 0BEh, 68h, 50h, 0E8h, 1Bh, 7Eh, 0B0h, 0FFh, 8Bh, 4Ch, 0BEh
    db 68h, 8Bh, 0E8h, 6Ah, 04h, 55h, 51h, 0E8h, 0EFh, 5Ah, 0AFh, 0FFh, 83h, 0C4h, 18h, 83h
    db 0FBh, 04h, 75h, 04h, 89h, 6Ch, 24h, 10h, 83h, 7Ch, 24h, 10h, 0FFh, 75h, 2Ch, 68h
    db 0F4h, 8Ah, 08h, 01h, 8Dh, 4Ch, 24h, 18h, 0E8h, 73h, 0F0h, 0B0h, 0FFh, 85h, 0C0h, 74h
    db 07h, 51h, 89h, 64h, 24h, 1Ch, 0EBh, 18h, 8Bh, 4Ch, 0BEh, 68h, 6Ah, 00h, 6Ah, 00h
    db 51h, 0E8h, 5Dh, 0C4h, 0B1h, 0FFh, 83h, 0C4h, 0Ch, 0EBh, 1Eh, 51h, 89h, 64h, 24h, 30h
    db 8Dh, 54h, 24h, 18h, 8Bh, 0CCh, 52h, 0E8h, 84h, 0Eh, 36h, 00h, 8Bh, 44h, 0BEh, 68h
    db 50h, 0E8h, 0B1h, 0ACh, 0AFh, 0FFh, 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h
    db 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 36h, 0Ch, 36h, 00h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh
    db 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_00527220@@YAXXZ ENDP

; ghidra: FUN_009276a0  retail @ 0x005276A0 size 109
public ?d_005276a0@@YAXXZ
?d_005276a0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 04h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 33h, 0C0h, 56h, 8Bh, 0F1h, 89h, 06h, 89h, 46h, 04h
    db 89h, 46h, 08h, 89h, 46h, 0Ch, 89h, 74h, 24h, 04h, 89h, 46h, 10h, 89h, 44h, 24h
    db 10h, 8Bh, 44h, 24h, 18h, 50h, 0E8h, 0C6h, 3Ah, 0B1h, 0FFh, 8Ah, 54h, 24h, 1Ch, 8Bh
    db 4Eh, 10h, 8Bh, 06h, 0F6h, 0DAh, 1Bh, 0D2h, 3Bh, 0C1h, 74h, 0Dh, 8Dh, 64h, 24h, 00h
    db 89h, 10h, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0F7h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_005276a0@@YAXXZ ENDP

; ghidra: FUN_00927730  retail @ 0x00527730 size 100
public ?d_00527730@@YAXXZ
?d_00527730@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 74h, 0D7h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 78h
    db 0D7h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 00h, 0D8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0FCh, 0D7h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 49h, 0FAh, 0AEh, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 09h, 03h, 0AEh, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_00527730@@YAXXZ ENDP

; ghidra: FUN_009277b0  retail @ 0x005277B0 size 100
public ?d_005277b0@@YAXXZ
?d_005277b0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 74h, 0D7h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 78h
    db 0D7h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 00h, 0D8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0FCh, 0D7h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 6Bh, 67h, 0AEh, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 95h, 0Ah, 0AEh, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_005277b0@@YAXXZ ENDP

; ghidra: FUN_00927830  retail @ 0x00527830 size 100
public ?d_00527830@@YAXXZ
?d_00527830@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 74h, 0D7h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 78h
    db 0D7h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 00h, 0D8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0FCh, 0D7h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 82h, 3Dh, 0AFh, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 7Eh, 0D8h, 0ADh, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_00527830@@YAXXZ ENDP

; ghidra: FUN_009278b0  retail @ 0x005278B0 size 100
public ?d_005278b0@@YAXXZ
?d_005278b0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 74h, 0D7h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 78h
    db 0D7h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 00h, 0D8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0FCh, 0D7h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 0A9h, 0B0h, 0ADh, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 32h, 35h, 0AEh, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_005278b0@@YAXXZ ENDP

; ghidra: FUN_00927930  retail @ 0x00527930 size 1516
public ?d_00527930@@YAXXZ
?d_00527930@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 0B8h, 04h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 38h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h
    db 8Bh, 01h, 57h, 0FFh, 50h, 30h, 84h, 0C0h, 0Fh, 84h, 0A7h, 05h, 00h, 00h, 8Bh, 46h
    db 08h, 33h, 0EDh, 3Bh, 0C5h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h
    db 84h, 0C0h, 75h, 03h, 89h, 6Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C5h, 74h, 10h, 8Bh, 4Eh
    db 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 6Eh, 0Ch, 8Bh, 4Eh
    db 08h, 3Bh, 0CDh, 0Fh, 84h, 6Ch, 05h, 00h, 00h, 55h, 0B3h, 01h, 0E8h, 77h, 72h, 0AFh
    db 0FFh, 88h, 58h, 08h, 89h, 6Ch, 24h, 28h, 89h, 6Ch, 24h, 1Ch, 89h, 6Ch, 24h, 14h
    db 51h, 8Bh, 4Eh, 08h, 8Bh, 0C4h, 89h, 64h, 24h, 34h, 50h, 89h, 6Ch, 24h, 58h, 0E8h
    db 0CAh, 78h, 0B0h, 0FFh, 8Bh, 0Dh, 94h, 15h, 2Fh, 01h, 0E8h, 0B1h, 1Eh, 0AFh, 0FFh, 8Bh
    db 0F8h, 89h, 7Ch, 24h, 30h, 89h, 6Ch, 24h, 18h, 8Bh, 4Eh, 08h, 51h, 88h, 5Ch, 24h
    db 54h, 0E8h, 15h, 1Ah, 0B1h, 0FFh, 83h, 0C4h, 04h, 3Bh, 0FDh, 88h, 44h, 24h, 13h, 0Fh
    db 84h, 0BFh, 04h, 00h, 00h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 0CFh, 0E8h, 0F9h, 2Ch, 0AEh
    db 0FFh, 8Bh, 00h, 3Bh, 0C5h, 0C6h, 44h, 24h, 50h, 02h, 74h, 05h, 83h, 0C0h, 08h, 0EBh
    db 05h, 0B8h, 8Ch, 38h, 07h, 01h, 50h, 51h, 89h, 64h, 24h, 34h, 8Bh, 0CCh, 68h, 0BCh
    db 0F4h, 0Fh, 01h, 0E8h, 0B8h, 13h, 36h, 00h, 8Dh, 44h, 24h, 20h, 50h, 0E8h, 5Eh, 17h
    db 36h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 0C6h, 44h, 24h, 50h, 01h, 0E8h, 8Dh
    db 07h, 36h, 00h, 89h, 6Ch, 24h, 24h, 8Bh, 4Ch, 24h, 24h, 51h, 8Bh, 4Eh, 08h, 0E8h
    db 0C4h, 71h, 0AFh, 0FFh, 8Bh, 0F8h, 3Bh, 0FDh, 0Fh, 84h, 0DBh, 00h, 00h, 00h, 8Bh, 0CFh
    db 0E8h, 66h, 0FFh, 0AFh, 0FFh, 84h, 0C0h, 0Fh, 84h, 0A8h, 00h, 00h, 00h, 8Ah, 47h, 09h
    db 84h, 0C0h, 0Fh, 85h, 9Dh, 00h, 00h, 00h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 0Fh, 85h
    db 91h, 00h, 00h, 00h, 89h, 6Ch, 24h, 20h, 8Bh, 44h, 24h, 18h, 3Bh, 0C5h, 0C6h, 44h
    db 24h, 50h, 03h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Ch, 38h, 07h, 01h, 50h
    db 8Dh, 54h, 24h, 30h, 52h, 8Bh, 0CFh, 0E8h, 5Fh, 27h, 0B1h, 0FFh, 8Bh, 00h, 3Bh, 0C5h
    db 0C6h, 44h, 24h, 54h, 04h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Ch, 38h, 07h
    db 01h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 50h, 8Bh, 01h, 51h, 8Bh, 0D4h, 89h, 64h, 24h
    db 40h, 55h, 68h, 0FCh, 0F4h, 0Fh, 01h, 52h, 0FFh, 50h, 28h, 8Dh, 44h, 24h, 2Ch, 50h
    db 0E8h, 0ABh, 16h, 36h, 00h, 83h, 0C4h, 10h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 50h
    db 03h, 0E8h, 0DAh, 06h, 36h, 00h, 8Bh, 4Eh, 04h, 8Bh, 11h, 6Ah, 02h, 8Dh, 44h, 24h
    db 24h, 50h, 0FFh, 52h, 08h, 8Dh, 4Ch, 24h, 20h, 32h, 0DBh, 0C6h, 44h, 24h, 50h, 01h
    db 0E8h, 0BBh, 06h, 36h, 00h, 8Bh, 0CFh, 0E8h, 77h, 8Ah, 0B1h, 0FFh, 84h, 0C0h, 74h, 19h
    db 83h, 7Fh, 14h, 0FEh, 74h, 13h, 8Bh, 0CFh, 0E8h, 9Eh, 0FEh, 0AFh, 0FFh, 84h, 0C0h, 74h
    db 04h, 0FFh, 44h, 24h, 1Ch, 0FFh, 44h, 24h, 28h, 8Bh, 44h, 24h, 24h, 40h, 83h, 0F8h
    db 08h, 89h, 44h, 24h, 24h, 0Fh, 8Ch, 0FCh, 0FEh, 0FFh, 0FFh, 0F6h, 86h, 20h, 01h, 00h
    db 00h, 10h, 8Bh, 4Ch, 24h, 1Ch, 74h, 4Bh, 83h, 0F9h, 01h, 7Fh, 46h, 8Bh, 0Dh, 7Ch
    db 14h, 2Fh, 01h, 8Bh, 11h, 55h, 68h, 0C0h, 0F5h, 0Fh, 01h, 8Dh, 44h, 24h, 60h, 50h
    db 0FFh, 52h, 28h, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 54h, 05h, 0E8h, 0AEh, 09h
    db 36h, 00h, 8Dh, 4Ch, 24h, 58h, 0C6h, 44h, 24h, 50h, 01h, 0E8h, 40h, 06h, 36h, 00h
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 55h, 8Dh, 44h, 24h, 18h, 50h, 0FFh, 52h, 08h, 0E9h, 43h
    db 03h, 00h, 00h, 8Ah, 44h, 24h, 58h, 84h, 0C0h, 74h, 18h, 8Dh, 86h, 2Ch, 01h, 00h
    db 00h, 89h, 8Eh, 28h, 01h, 00h, 00h, 33h, 0D2h, 8Bh, 0F8h, 89h, 17h, 89h, 57h, 04h
    db 0C6h, 00h, 01h, 84h, 0DBh, 75h, 36h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 55h
    db 68h, 0B4h, 6Bh, 10h, 01h, 8Dh, 54h, 24h, 60h, 52h, 0FFh, 50h, 28h, 50h, 8Bh, 0CEh
    db 0C6h, 44h, 24h, 54h, 06h, 0E8h, 0BCh, 0AFh, 0AFh, 0FFh, 8Dh, 4Ch, 24h, 58h, 0C6h, 44h
    db 24h, 50h, 01h, 0E8h, 0D8h, 05h, 36h, 00h, 0E9h, 0E9h, 02h, 00h, 00h, 8Bh, 44h, 24h
    db 30h, 8Bh, 40h, 20h, 8Bh, 54h, 24h, 28h, 3Bh, 0C2h, 7Dh, 31h, 8Bh, 0Dh, 7Ch, 14h
    db 2Fh, 01h, 8Bh, 11h, 50h, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 60h, 55h, 68h, 0C8h, 0F4h
    db 0Fh, 01h, 50h, 0FFh, 52h, 28h, 8Dh, 4Ch, 24h, 1Ch, 51h, 0E8h, 60h, 15h, 36h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 54h, 24h, 14h, 52h, 0E9h, 0A2h, 02h, 00h, 00h, 0A1h, 0C8h, 0D5h
    db 2Eh, 01h, 8Bh, 80h, 0Ch, 0Bh, 00h, 00h, 3Bh, 0C5h, 74h, 21h, 3Bh, 0CDh, 75h, 1Dh
    db 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 11h, 55h, 68h, 0C0h, 0F5h, 0Fh, 01h, 8Dh, 44h
    db 24h, 60h, 50h, 0FFh, 52h, 28h, 0C6h, 44h, 24h, 50h, 07h, 0EBh, 1Fh, 3Bh, 0D0h, 7Dh
    db 38h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 11h, 55h, 68h, 0C0h, 0F5h, 0Fh, 01h, 8Dh
    db 44h, 24h, 60h, 50h, 0FFh, 52h, 28h, 0C6h, 44h, 24h, 50h, 08h, 50h, 8Dh, 4Ch, 24h
    db 18h, 0E8h, 9Ah, 08h, 36h, 00h, 8Dh, 4Ch, 24h, 58h, 0C6h, 44h, 24h, 50h, 01h, 0E8h
    db 2Ch, 05h, 36h, 00h, 0E9h, 31h, 02h, 00h, 00h, 8Dh, 4Ch, 24h, 3Ch, 33h, 0DBh, 0E8h
    db 9Dh, 0Fh, 0AEh, 0FFh, 0C6h, 44h, 24h, 50h, 09h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Eh, 08h, 55h, 0E8h, 4Fh, 6Fh, 0AFh, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h, 32h, 8Bh
    db 0CFh, 0E8h, 0BDh, 88h, 0B1h, 0FFh, 84h, 0C0h, 74h, 27h, 83h, 7Fh, 14h, 0FEh, 74h, 21h
    db 8Bh, 7Fh, 18h, 85h, 0FFh, 7Ch, 19h, 8Dh, 54h, 24h, 30h, 52h, 8Dh, 44h, 24h, 38h
    db 50h, 8Dh, 4Ch, 24h, 44h, 89h, 7Ch, 24h, 38h, 0E8h, 0B8h, 57h, 0B0h, 0FFh, 0EBh, 01h
    db 43h, 45h, 83h, 0FDh, 08h, 7Ch, 0B9h, 8Bh, 4Ch, 24h, 40h, 8Bh, 15h, 0C8h, 0D5h, 2Eh
    db 01h, 8Dh, 04h, 19h, 3Bh, 82h, 0Ch, 0Bh, 00h, 00h, 73h, 53h, 8Bh, 0Dh, 7Ch, 14h
    db 2Fh, 01h, 8Bh, 01h, 6Ah, 00h, 68h, 80h, 0F5h, 0Fh, 01h, 8Dh, 54h, 24h, 60h, 52h
    db 0FFh, 50h, 28h, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 54h, 0Ah, 0E8h, 0EEh, 07h
    db 36h, 00h, 8Dh, 4Ch, 24h, 58h, 0C6h, 44h, 24h, 50h, 09h, 0E8h, 80h, 04h, 36h, 00h
    db 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0E8h, 4Ah, 0AEh, 0AFh, 0FFh, 8Dh, 4Ch, 24h, 3Ch
    db 0C6h, 44h, 24h, 50h, 01h, 0E8h, 69h, 0B2h, 0B0h, 0FFh, 0E9h, 77h, 01h, 00h, 00h, 83h
    db 0F8h, 02h, 73h, 43h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 11h, 6Ah, 00h, 68h, 10h
    db 0F5h, 0Fh, 01h, 8Dh, 44h, 24h, 38h, 50h, 0FFh, 52h, 28h, 50h, 8Dh, 4Ch, 24h, 18h
    db 0C6h, 44h, 24h, 54h, 0Bh, 0E8h, 96h, 07h, 36h, 00h, 8Dh, 4Ch, 24h, 30h, 0C6h, 44h
    db 24h, 50h, 09h, 0E8h, 28h, 04h, 36h, 00h, 8Bh, 4Eh, 04h, 8Bh, 11h, 6Ah, 00h, 8Dh
    db 44h, 24h, 18h, 50h, 0FFh, 52h, 08h, 33h, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Eh, 08h, 57h, 0E8h, 4Fh, 6Eh, 0AFh, 0FFh, 85h, 0C0h, 74h, 15h, 8Bh, 0C8h, 0E8h
    db 6Fh, 9Eh, 0AEh, 0FFh, 84h, 0C0h, 74h, 0Ah, 6Ah, 01h, 57h, 8Bh, 0CEh, 0E8h, 38h, 38h
    db 0B1h, 0FFh, 47h, 83h, 0FFh, 08h, 7Ch, 0D8h, 8Ah, 44h, 24h, 58h, 84h, 0C0h, 74h, 2Ah
    db 0C7h, 46h, 20h, 06h, 00h, 00h, 00h, 0FFh, 15h, 44h, 95h, 35h, 01h, 8Bh, 4Eh, 20h
    db 69h, 0C9h, 0E8h, 03h, 00h, 00h, 8Dh, 54h, 08h, 0FFh, 8Bh, 0CEh, 89h, 56h, 1Ch, 0C6h
    db 46h, 17h, 01h, 0E8h, 3Fh, 6Bh, 0AFh, 0FFh, 0EBh, 56h, 8Bh, 54h, 24h, 1Ch, 8Bh, 4Eh
    db 04h, 52h, 0C6h, 46h, 17h, 00h, 8Bh, 01h, 6Ah, 01h, 0FFh, 50h, 34h, 8Bh, 0Dh, 7Ch
    db 14h, 2Fh, 01h, 8Bh, 01h, 6Ah, 00h, 68h, 9Ch, 6Bh, 10h, 01h, 8Dh, 54h, 24h, 38h
    db 52h, 0FFh, 50h, 28h, 50h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 54h, 0Ch, 0E8h, 0DDh
    db 06h, 36h, 00h, 8Dh, 4Ch, 24h, 30h, 0C6h, 44h, 24h, 50h, 09h, 0E8h, 6Fh, 03h, 36h
    db 00h, 8Bh, 4Eh, 04h, 8Bh, 01h, 6Ah, 02h, 8Dh, 54h, 24h, 18h, 52h, 0FFh, 50h, 08h
    db 8Dh, 4Ch, 24h, 3Ch, 0C6h, 44h, 24h, 50h, 01h, 0E8h, 55h, 0B1h, 0B0h, 0FFh, 8Dh, 4Ch
    db 24h, 18h, 0C6h, 44h, 24h, 50h, 00h, 0E8h, 44h, 03h, 36h, 00h, 8Dh, 4Ch, 24h, 14h
    db 0C7h, 44h, 24h, 50h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 33h, 03h, 36h, 00h, 0B0h, 01h, 8Bh
    db 4Ch, 24h, 48h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h
    db 44h, 0C2h, 04h, 00h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 51h, 8Bh, 0D4h, 89h
    db 64h, 24h, 5Ch, 55h, 68h, 84h, 6Bh, 10h, 01h, 52h, 0FFh, 50h, 28h, 8Dh, 44h, 24h
    db 18h, 50h, 0E8h, 0B9h, 12h, 36h, 00h, 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh
    db 0CEh, 0E8h, 0C0h, 0ACh, 0AFh, 0FFh, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 50h, 00h, 0E8h
    db 0DCh, 02h, 36h, 00h, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h, 50h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0CBh, 02h, 36h, 00h, 8Bh, 4Ch, 24h, 48h, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 44h, 0C2h, 04h, 00h
?d_00527930@@YAXXZ ENDP

; ghidra: FUN_009280a0  retail @ 0x005280A0 size 570
_TEXT ENDS
_TEXT$d009280a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x009280A0 size 570
public ?d_005280a0@@YAXXZ
?d_005280a0@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va010304F8
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 008h, 053h, 055h, 056h, 08Bh, 0F1h
    db 08Ah, 046h, 017h, 033h, 0DBh, 03Ah, 0C3h, 057h, 00Fh, 085h, 0AAh, 000h, 000h, 000h, 039h, 05Eh
    db 01Ch, 074h, 01Ch, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 001h, 053h, 068h
    dd g_Va01106C40
    db 08Dh, 054h, 024h, 01Ch, 052h, 0FFh, 050h, 028h, 089h, 05Ch, 024h, 020h, 0EBh, 026h, 038h, 01Dh
    dd g_Va012B77AF
    db 075h, 03Ah, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 001h, 053h, 068h
    dd g_Va01106C10
    db 08Dh, 054h, 024h, 01Ch, 052h, 0FFh, 050h, 028h, 0C7h, 044h, 024h, 020h, 001h, 000h, 000h, 000h
    db 08Bh, 04Eh, 004h, 08Bh, 011h, 06Ah, 002h, 050h, 0FFh, 052h, 008h, 08Dh, 04Ch, 024h, 014h, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 038h, 05Eh, 018h, 074h, 020h, 08Bh, 04Eh, 004h, 088h, 05Eh, 018h, 08Bh, 001h, 053h, 0FFh, 050h
    db 038h, 08Bh, 04Eh, 004h, 08Bh, 011h, 0FFh, 052h, 030h, 084h, 0C0h, 074h, 008h, 08Bh, 04Eh, 004h
    db 08Bh, 001h, 0FFh, 050h, 03Ch, 0C6h, 005h
    dd g_Va012B77AF
    db 001h, 089h, 05Eh, 020h, 089h, 05Eh, 01Ch, 032h, 0C0h, 08Bh, 04Ch, 024h, 018h, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C3h, 08Bh, 03Dh
    dd __imp__timeGetTime@0
    db 0FFh, 0D7h, 08Bh, 04Eh, 01Ch, 02Bh, 0C8h, 03Bh, 0CBh, 08Ah, 046h, 018h, 00Fh, 08Eh, 0BBh, 000h
    db 000h, 000h, 03Ah, 0C3h, 00Fh, 085h, 015h, 001h, 000h, 000h, 0B8h, 0D3h, 04Dh, 062h, 010h, 0F7h
    db 0E9h, 08Bh, 046h, 020h, 0C1h, 0FAh, 006h, 08Bh, 0FAh, 0C1h, 0EFh, 01Fh, 003h, 0FAh, 03Bh, 0F8h
    db 07Dh, 065h, 03Bh, 0FBh, 07Eh, 05Eh, 089h, 05Ch, 024h, 010h, 083h, 0FFh, 001h, 0C7h, 044h, 024h
    db 020h, 002h, 000h, 000h, 000h, 0B8h
    dd g_Va01106BF0
    db 074h, 005h, 0B8h
    dd g_Va01106BD0
    db 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 057h, 051h, 08Bh, 0ECh, 089h, 064h, 024h, 01Ch, 053h, 050h, 055h, 0FFh, 052h, 028h
    db 08Dh, 044h, 024h, 018h, 050h
    call ?format@UnicodeString@@QAAXV1@ZZ
    db 08Bh, 04Eh, 004h, 08Bh, 011h, 083h, 0C4h, 00Ch, 06Ah, 002h, 08Dh, 044h, 024h, 014h, 050h, 0FFh
    db 052h, 008h, 08Dh, 04Ch, 024h, 010h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 089h, 07Eh, 020h, 038h, 05Eh, 018h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002ed9d@@YAXXZ
    db 00Fh, 0B7h, 0C8h, 03Bh, 08Eh, 028h, 001h, 000h, 000h, 07Dh, 07Dh, 089h, 05Eh, 01Ch, 089h, 05Eh
    db 020h, 0B0h, 001h, 08Bh, 04Ch, 024h, 018h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh
    db 05Dh, 05Bh, 083h, 0C4h, 014h, 0C3h, 03Ah, 0C3h, 075h, 034h, 08Bh, 04Eh, 004h, 08Bh, 011h, 06Ah
    db 001h, 0FFh, 052h, 038h, 0C6h, 046h, 018h, 001h, 0C6h, 005h
    dd g_Va012B77AF
    db 001h, 0FFh, 0D7h, 005h, 088h, 013h, 000h, 000h, 089h, 046h, 01Ch, 0B0h, 001h, 08Bh, 04Ch, 024h
    db 018h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C3h
    db 08Bh, 0CEh, 0C6h, 005h
    dd g_Va012B77AF
    db 001h, 088h, 05Eh, 017h
    call ?j_0002ed9d@@YAXXZ
    db 08Bh, 08Eh, 028h, 001h, 000h, 000h, 00Fh, 0B7h, 0C0h, 03Bh, 0C1h, 07Dh, 021h, 088h, 01Dh
    dd g_Va012B77AF
    db 089h, 05Eh, 01Ch, 089h, 05Eh, 020h, 0B0h, 001h, 08Bh, 04Ch, 024h, 018h, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C3h, 053h, 08Bh, 0CEh
    call ?j_00031327@@YAXXZ
    db 08Bh, 04Ch, 024h, 018h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 014h, 0C3h
?d_005280a0@@YAXXZ ENDP
_TEXT$d009280a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00928370  retail @ 0x00528370 size 296
_TEXT ENDS
_TEXT$d00928370 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00928370 size 296
public ?d_00528370@@YAXXZ
?d_00528370@@YAXXZ PROC
    db 083h, 0ECh, 008h, 053h, 08Bh, 0D9h, 08Bh, 083h, 008h, 001h, 000h, 000h, 055h, 050h
    call ?j_00010857@@YAXXZ
    db 083h, 0C4h, 004h, 033h, 0EDh, 085h, 0C0h, 089h, 044h, 024h, 00Ch, 0C7h, 044h, 024h, 008h, 0FFh
    db 0FFh, 0FFh, 0FFh, 00Fh, 08Eh, 098h, 000h, 000h, 000h, 056h, 057h, 08Bh, 0FFh, 08Bh, 08Bh, 00Ch
    db 001h, 000h, 000h, 08Dh, 004h, 0A9h, 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 078h, 004h
    db 0EBh, 002h, 033h, 0FFh, 085h, 0C0h, 08Dh, 050h, 008h, 075h, 005h, 0BAh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 044h, 024h, 01Ch, 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh, 0B7h, 070h, 004h, 0EBh, 002h
    db 033h, 0F6h, 085h, 0C0h, 08Dh, 048h, 008h, 075h, 005h, 0B9h
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0F7h, 08Bh, 0C6h, 07Ch, 002h, 08Bh, 0C7h, 050h, 052h, 051h, 0FFh, 015h
    dd __imp___memicmp
    db 083h, 0C4h, 00Ch, 085h, 0C0h, 075h, 008h, 02Bh, 0F7h, 08Bh, 0C6h, 085h, 0C0h, 074h, 00Fh, 08Bh
    db 044h, 024h, 014h, 045h, 03Bh, 0E8h, 07Ch, 096h, 08Bh, 044h, 024h, 010h, 0EBh, 006h, 08Bh, 0C5h
    db 089h, 044h, 024h, 010h, 085h, 0C0h, 05Fh, 05Eh, 07Ch, 018h, 08Bh, 08Bh, 008h, 001h, 000h, 000h
    db 050h, 051h
    call ?j_00001203@@YAXXZ
    db 083h, 0C4h, 008h, 05Dh, 05Bh, 083h, 0C4h, 008h, 0C2h, 004h, 000h, 08Bh, 093h, 008h, 001h, 000h
    db 000h, 052h
    call ?j_00010857@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 075h, 02Ah, 08Bh, 08Bh, 008h, 001h, 000h, 000h, 06Ah, 0FFh, 08Dh
    db 044h, 024h, 00Ch, 050h, 051h
    call ?j_00032c4a@@YAXXZ
    db 083h, 0C4h, 00Ch, 068h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 08Bh, 0CBh
    call ?j_0003f6b6@@YAXXZ
    db 05Dh, 05Bh, 083h, 0C4h, 008h, 0C2h, 004h, 000h, 08Bh, 093h, 008h, 001h, 000h, 000h, 06Ah, 000h
    db 052h
    call ?j_00001203@@YAXXZ
    db 08Bh, 083h, 00Ch, 001h, 000h, 000h, 083h, 0C4h, 008h, 050h, 08Bh, 0CBh
    call ?j_0003f6b6@@YAXXZ
    db 05Dh, 05Bh, 083h, 0C4h, 008h, 0C2h, 004h, 000h
?d_00528370@@YAXXZ ENDP
_TEXT$d00928370 ENDS
_TEXT SEGMENT

; ghidra: FUN_009284f0  retail @ 0x005284F0 size 1319
public ?d_005284f0@@YAXXZ
?d_005284f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Ch, 05h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 44h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 08h, 33h
    db 0F6h, 3Bh, 0C6h, 89h, 7Ch, 24h, 18h, 74h, 10h, 8Bh, 4Fh, 04h, 8Bh, 11h, 50h, 0FFh
    db 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 77h, 08h, 8Bh, 47h, 0Ch, 3Bh, 0C6h, 74h, 10h
    db 8Bh, 4Fh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 77h, 0Ch
    db 39h, 77h, 08h, 75h, 15h, 5Fh, 32h, 0C0h, 5Eh, 8Bh, 4Ch, 24h, 44h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 50h, 0C2h, 04h, 00h, 8Bh, 0Dh, 0FCh, 0D5h, 2Eh, 01h
    db 8Bh, 51h, 3Ch, 3Bh, 0D6h, 8Dh, 41h, 3Ch, 75h, 05h, 8Bh, 49h, 34h, 89h, 08h, 53h
    db 55h, 8Bh, 28h, 8Dh, 54h, 24h, 64h, 52h, 6Ah, 01h, 55h, 8Dh, 4Ch, 24h, 4Ch, 89h
    db 6Ch, 24h, 20h, 0E8h, 0A6h, 0F8h, 0B1h, 0FFh, 89h, 74h, 24h, 5Ch, 8Bh, 0DDh, 8Bh, 0FFh
    db 8Bh, 4Fh, 08h, 56h, 0E8h, 7Fh, 66h, 0AFh, 0FFh, 85h, 0C0h, 74h, 2Eh, 3Bh, 74h, 24h
    db 64h, 74h, 28h, 8Bh, 40h, 0Ch, 85h, 0C0h, 7Ch, 21h, 3Bh, 0C5h, 7Dh, 1Dh, 50h, 8Dh
    db 44h, 24h, 28h, 50h, 8Dh, 4Ch, 24h, 48h, 0E8h, 58h, 0ABh, 0AEh, 0FFh, 8Bh, 50h, 04h
    db 8Bh, 08h, 8Bh, 01h, 0F7h, 0D2h, 23h, 0C2h, 89h, 01h, 4Bh, 46h, 83h, 0FEh, 08h, 7Ch
    db 0BFh, 8Bh, 44h, 24h, 64h, 8Dh, 8Ch, 87h, 88h, 00h, 00h, 00h, 51h, 8Dh, 4Ch, 24h
    db 14h, 0E8h, 29h, 33h, 0AFh, 0FFh, 8Bh, 4Ch, 24h, 10h, 0C6h, 44h, 24h, 5Ch, 01h, 0E8h
    db 44h, 0DFh, 0B1h, 0FFh, 8Bh, 40h, 08h, 33h, 0F6h, 3Bh, 0C6h, 89h, 44h, 24h, 24h, 0Fh
    db 84h, 0DBh, 01h, 00h, 00h, 50h, 0E8h, 4Ch, 82h, 0AEh, 0FFh, 83h, 0C4h, 04h, 43h, 3Bh
    db 0C3h, 89h, 44h, 24h, 1Ch, 0Fh, 85h, 0C5h, 01h, 00h, 00h, 89h, 74h, 24h, 2Ch, 89h
    db 74h, 24h, 30h, 89h, 74h, 24h, 34h, 89h, 74h, 24h, 38h, 89h, 74h, 24h, 3Ch, 55h
    db 8Dh, 4Ch, 24h, 30h, 0C6h, 44h, 24h, 60h, 02h, 0E8h, 63h, 2Bh, 0B1h, 0FFh, 8Bh, 74h
    db 24h, 2Ch, 8Bh, 6Ch, 24h, 3Ch, 3Bh, 0F5h, 8Bh, 0C6h, 74h, 11h, 8Dh, 64h, 24h, 00h
    db 0C7h, 00h, 00h, 00h, 00h, 00h, 83h, 0C0h, 04h, 3Bh, 0C5h, 75h, 0F3h, 8Bh, 44h, 24h
    db 1Ch, 33h, 0DBh, 85h, 0C0h, 0C6h, 44h, 24h, 5Ch, 03h, 89h, 5Ch, 24h, 18h, 0Fh, 8Eh
    db 81h, 00h, 00h, 00h, 8Bh, 7Ch, 24h, 30h, 8Bh, 54h, 24h, 24h, 6Ah, 00h, 53h, 52h
    db 0E8h, 0FFh, 09h, 0AEh, 0FFh, 83h, 0C4h, 0Ch, 85h, 0C0h, 7Ch, 52h, 8Bh, 4Ch, 24h, 34h
    db 8Bh, 6Ch, 24h, 38h, 8Bh, 0D6h, 2Bh, 0CAh, 0C1h, 0F9h, 02h, 0C1h, 0E1h, 05h, 2Bh, 0CFh
    db 03h, 0CDh, 3Bh, 0C1h, 73h, 47h, 8Bh, 0CFh, 03h, 0C8h, 8Bh, 0C1h, 99h, 83h, 0E2h, 1Fh
    db 03h, 0C2h, 0C1h, 0F8h, 05h, 81h, 0E1h, 1Fh, 00h, 00h, 80h, 8Dh, 14h, 86h, 79h, 0Dh
    db 49h, 83h, 0C9h, 0E0h, 41h, 79h, 06h, 83h, 0C1h, 20h, 83h, 0EAh, 04h, 8Bh, 5Ch, 24h
    db 18h, 8Bh, 6Ch, 24h, 3Ch, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 09h, 02h, 8Bh, 44h
    db 24h, 1Ch, 43h, 3Bh, 0D8h, 89h, 5Ch, 24h, 18h, 7Ch, 8Dh, 0EBh, 04h, 8Bh, 6Ch, 24h
    db 3Ch, 8Bh, 7Ch, 24h, 20h, 8Dh, 44h, 24h, 40h, 50h, 8Dh, 4Ch, 24h, 30h, 51h, 0E8h
    db 0DBh, 0F0h, 0B1h, 0FFh, 83h, 0C4h, 08h, 84h, 0C0h, 0C6h, 44h, 24h, 5Ch, 01h, 0Fh, 84h
    db 9Eh, 00h, 00h, 00h, 85h, 0F6h, 74h, 28h, 2Bh, 0EEh, 0C1h, 0FDh, 02h, 8Dh, 04h, 0ADh
    db 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 7Fh, 97h, 35h
    db 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 56h, 0E8h, 0B3h, 5Eh, 30h, 00h, 83h, 0C4h, 08h
    db 8Dh, 4Ch, 24h, 10h, 0C6h, 44h, 24h, 5Ch, 00h, 0E8h, 05h, 64h, 0B1h, 0FFh, 8Bh, 4Ch
    db 24h, 40h, 85h, 0C9h, 0C7h, 44h, 24h, 5Ch, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 3Dh, 8Bh, 44h
    db 24h, 50h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 20h, 51h, 0E8h, 39h, 97h, 35h, 00h, 83h, 0C4h, 04h, 5Dh, 5Bh, 5Fh, 32h, 0C0h, 5Eh
    db 8Bh, 4Ch, 24h, 44h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 50h, 0C2h, 04h
    db 00h, 50h, 51h, 0E8h, 58h, 5Eh, 30h, 00h, 83h, 0C4h, 08h, 5Dh, 5Bh, 5Fh, 32h, 0C0h
    db 5Eh, 8Bh, 4Ch, 24h, 44h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 50h, 0C2h
    db 04h, 00h, 85h, 0F6h, 74h, 28h, 2Bh, 0EEh, 0C1h, 0FDh, 02h, 8Dh, 04h, 0ADh, 00h, 00h
    db 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 0E1h, 96h, 35h, 00h, 83h
    db 0C4h, 04h, 0EBh, 0Ah, 50h, 56h, 0E8h, 15h, 5Eh, 30h, 00h, 83h, 0C4h, 08h, 33h, 0F6h
    db 8Dh, 4Ch, 24h, 10h, 0E8h, 0F1h, 0AEh, 0B1h, 0FFh, 8Bh, 0D8h, 4Bh, 0F7h, 0DBh, 1Ah, 0DBh
    db 8Dh, 4Ch, 24h, 10h, 0FEh, 0C3h, 0E8h, 06h, 0E2h, 0B1h, 0FFh, 8Bh, 0Dh, 0FCh, 0D5h, 2Eh
    db 01h, 6Ah, 0FFh, 0E8h, 0BAh, 96h, 0AFh, 0FFh, 0F6h, 05h, 0E0h, 49h, 2Fh, 01h, 01h, 75h
    db 47h, 83h, 0Dh, 0E0h, 49h, 2Fh, 01h, 01h, 68h, 6Ch, 6Ch, 10h, 01h, 8Dh, 4Ch, 24h
    db 24h, 0C6h, 44h, 24h, 60h, 04h, 0E8h, 95h, 03h, 36h, 00h, 8Bh, 0Dh, 24h, 69h, 2Fh
    db 01h, 8Dh, 54h, 24h, 20h, 52h, 0C6h, 44h, 24h, 60h, 05h, 0E8h, 0C6h, 4Dh, 0AFh, 0FFh
    db 8Dh, 4Ch, 24h, 20h, 0A3h, 0DCh, 49h, 2Fh, 01h, 0C6h, 44h, 24h, 5Ch, 04h, 0E8h, 0EDh
    db 0F0h, 35h, 00h, 0C6h, 44h, 24h, 5Ch, 01h, 0A1h, 0F4h, 76h, 2Bh, 01h, 8Bh, 0Dh, 0DCh
    db 49h, 2Fh, 01h, 50h, 6Ah, 14h, 6Ah, 14h, 51h, 8Dh, 4Ch, 24h, 20h, 0E8h, 76h, 0E3h
    db 0AFh, 0FFh, 6Ah, 0FFh, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 84h, 0D2h, 0B0h, 0FFh, 8Bh, 54h
    db 24h, 64h, 8Bh, 4Fh, 08h, 52h, 0E8h, 0D5h, 0Bh, 0B0h, 0FFh, 83h, 78h, 14h, 0FEh, 75h
    db 51h, 56h, 8Dh, 4Ch, 24h, 14h, 0E8h, 21h, 0E5h, 0B1h, 0FFh, 8Dh, 4Ch, 24h, 10h, 0C6h
    db 44h, 24h, 5Ch, 00h, 0E8h, 0AAh, 62h, 0B1h, 0FFh, 8Bh, 4Ch, 24h, 40h, 3Bh, 0CEh, 0C7h
    db 44h, 24h, 5Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0Fh, 84h, 43h, 01h, 00h, 00h, 8Bh, 44h, 24h
    db 50h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 0Fh, 86h
    db 22h, 01h, 00h, 00h, 51h, 0E8h, 0D6h, 95h, 35h, 00h, 83h, 0C4h, 04h, 0E9h, 1Eh, 01h
    db 00h, 00h, 8Bh, 74h, 24h, 14h, 33h, 0FFh, 85h, 0F6h, 0Fh, 8Eh, 0D1h, 00h, 00h, 00h
    db 8Bh, 0Dh, 0FCh, 0D5h, 2Eh, 01h, 57h, 0E8h, 0C6h, 95h, 0AFh, 0FFh, 8Bh, 0E8h, 85h, 0EDh
    db 0Fh, 84h, 0B2h, 00h, 00h, 00h, 8Bh, 44h, 24h, 44h, 8Bh, 74h, 24h, 40h, 8Dh, 0Ch
    db 38h, 8Bh, 0C1h, 99h, 83h, 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 81h, 0E1h, 1Fh, 00h
    db 00h, 80h, 8Dh, 04h, 86h, 79h, 0Dh, 49h, 83h, 0C9h, 0E0h, 41h, 79h, 06h, 83h, 0C1h
    db 20h, 83h, 0E8h, 04h, 8Bh, 0D0h, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 85h, 02h, 74h
    db 73h, 0F6h, 05h, 0E0h, 49h, 2Fh, 01h, 02h, 75h, 47h, 83h, 0Dh, 0E0h, 49h, 2Fh, 01h
    db 02h, 68h, 5Ch, 6Ch, 10h, 01h, 8Dh, 4Ch, 24h, 68h, 0C6h, 44h, 24h, 60h, 06h, 0E8h
    db 5Ch, 02h, 36h, 00h, 8Bh, 0Dh, 24h, 69h, 2Fh, 01h, 8Dh, 44h, 24h, 64h, 50h, 0C6h
    db 44h, 24h, 60h, 07h, 0E8h, 8Dh, 4Ch, 0AFh, 0FFh, 8Dh, 4Ch, 24h, 64h, 0A3h, 0D8h, 49h
    db 2Fh, 01h, 0C6h, 44h, 24h, 5Ch, 06h, 0E8h, 0B4h, 0EFh, 35h, 00h, 0C6h, 44h, 24h, 5Ch
    db 01h, 8Bh, 45h, 10h, 8Bh, 0Dh, 0D8h, 49h, 2Fh, 01h, 50h, 6Ah, 14h, 6Ah, 14h, 51h
    db 8Dh, 4Ch, 24h, 20h, 0E8h, 3Fh, 0E2h, 0AFh, 0FFh, 57h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h
    db 4Eh, 0D1h, 0B0h, 0FFh, 8Bh, 74h, 24h, 14h, 47h, 3Bh, 0FEh, 0Fh, 8Ch, 2Fh, 0FFh, 0FFh
    db 0FFh, 6Bh, 0F6h, 1Eh, 56h, 8Dh, 4Ch, 24h, 14h, 0E8h, 66h, 0E5h, 0B0h, 0FFh, 84h, 0DBh
    db 74h, 0Bh, 6Ah, 00h, 8Dh, 4Ch, 24h, 14h, 0E8h, 0DFh, 0E3h, 0B1h, 0FFh, 8Dh, 4Ch, 24h
    db 10h, 0C6h, 44h, 24h, 5Ch, 00h, 0E8h, 68h, 61h, 0B1h, 0FFh, 8Bh, 4Ch, 24h, 40h, 85h
    db 0C9h, 0E9h, 0B9h, 0FEh, 0FFh, 0FFh, 50h, 51h, 0E8h, 0F3h, 5Bh, 30h, 00h, 83h, 0C4h, 08h
    db 8Bh, 4Ch, 24h, 54h, 5Dh, 5Bh, 5Fh, 0B0h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 50h, 0C2h, 04h, 00h
?d_005284f0@@YAXXZ ENDP

; ghidra: FUN_00928b60  retail @ 0x00528B60 size 683
public ?d_00528b60@@YAXXZ
?d_00528b60@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 90h, 05h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h
    db 33h, 0EDh, 3Bh, 0C5h, 57h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h
    db 84h, 0C0h, 75h, 03h, 89h, 6Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C5h, 74h, 10h, 8Bh, 4Eh
    db 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 6Eh, 0Ch, 8Bh, 4Eh
    db 08h, 3Bh, 0CDh, 0Fh, 84h, 3Dh, 02h, 00h, 00h, 8Bh, 7Ch, 24h, 30h, 57h, 0E8h, 55h
    db 60h, 0AFh, 0FFh, 8Bh, 4Eh, 08h, 8Bh, 0D8h, 8Bh, 01h, 89h, 5Ch, 24h, 10h, 0FFh, 50h
    db 10h, 84h, 0C0h, 74h, 14h, 3Bh, 0DDh, 74h, 5Dh, 8Bh, 0CBh, 0E8h, 0FFh, 96h, 0B1h, 0FFh
    db 84h, 0C0h, 74h, 05h, 57h, 6Ah, 01h, 0EBh, 5Bh, 3Bh, 0DDh, 74h, 49h, 8Bh, 4Eh, 08h
    db 8Bh, 11h, 0FFh, 52h, 14h, 3Bh, 0C7h, 75h, 3Dh, 8Ah, 43h, 08h, 84h, 0C0h, 74h, 10h
    db 8Bh, 4Eh, 08h, 8Bh, 01h, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 04h, 6Ah, 0FFh, 0EBh, 33h
    db 8Ah, 43h, 09h, 84h, 0C0h, 74h, 06h, 6Ah, 0FFh, 6Ah, 01h, 0EBh, 27h, 8Bh, 4Eh, 08h
    db 51h, 0E8h, 0D5h, 07h, 0B1h, 0FFh, 83h, 0C4h, 04h, 88h, 44h, 24h, 30h, 8Bh, 54h, 24h
    db 30h, 6Ah, 0FFh, 52h, 0EBh, 0Eh, 8Bh, 4Eh, 08h, 8Bh, 01h, 0FFh, 50h, 10h, 84h, 0C0h
    db 74h, 09h, 57h, 55h, 8Bh, 0CEh, 0E8h, 87h, 3Ch, 0AFh, 0FFh, 3Bh, 0DDh, 0Fh, 84h, 95h
    db 00h, 00h, 00h, 8Bh, 0CBh, 0E8h, 71h, 0EDh, 0AFh, 0FFh, 84h, 0C0h, 74h, 7Eh, 8Dh, 4Ch
    db 24h, 14h, 51h, 8Bh, 0CBh, 0E8h, 0A1h, 15h, 0B1h, 0FFh, 8Bh, 54h, 0BEh, 68h, 52h, 8Dh
    db 44h, 24h, 1Ch, 50h, 89h, 6Ch, 24h, 30h, 0E8h, 57h, 7Eh, 0B1h, 0FFh, 83h, 0C4h, 08h
    db 39h, 6Ch, 0BEh, 68h, 0C6h, 44h, 24h, 28h, 01h, 74h, 30h, 8Dh, 4Ch, 24h, 18h, 51h
    db 8Dh, 4Ch, 24h, 18h, 0E8h, 53h, 9Ah, 0AFh, 0FFh, 85h, 0C0h, 74h, 1Eh, 51h, 8Dh, 54h
    db 24h, 18h, 89h, 64h, 24h, 34h, 8Bh, 0CCh, 52h, 0E8h, 52h, 0F7h, 35h, 00h, 8Bh, 44h
    db 0BEh, 68h, 50h, 0E8h, 7Fh, 95h, 0AFh, 0FFh, 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 18h, 0C6h
    db 44h, 24h, 28h, 00h, 0E8h, 07h, 0F5h, 35h, 00h, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h
    db 28h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F6h, 0F4h, 35h, 00h, 0EBh, 0Ch, 8Bh, 4Bh, 04h, 51h
    db 57h, 8Bh, 0CEh, 0E8h, 32h, 29h, 0B1h, 0FFh, 8Bh, 4Eh, 08h, 8Bh, 11h, 0FFh, 52h, 10h
    db 84h, 0C0h, 75h, 0Eh, 8Bh, 4Ch, 0BEh, 68h, 3Bh, 0CDh, 74h, 06h, 55h, 0E8h, 0F9h, 14h
    db 0B2h, 0FFh, 8Bh, 8Ch, 0BEh, 88h, 00h, 00h, 00h, 85h, 0C9h, 8Dh, 0ACh, 0BEh, 88h, 00h
    db 00h, 00h, 0C6h, 44h, 24h, 30h, 00h, 74h, 15h, 0E8h, 0BCh, 0B0h, 0AFh, 0FFh, 0A8h, 08h
    db 74h, 0Ch, 57h, 8Bh, 0CEh, 0E8h, 0C7h, 24h, 0B1h, 0FFh, 88h, 44h, 24h, 30h, 83h, 7Dh
    db 00h, 00h, 74h, 5Dh, 8Bh, 0CDh, 0E8h, 9Fh, 0A9h, 0B1h, 0FFh, 33h, 0DBh, 85h, 0C0h, 89h
    db 44h, 24h, 1Ch, 7Eh, 1Eh, 53h, 8Bh, 0CDh, 0E8h, 0F4h, 0FEh, 0AEh, 0FFh, 8Bh, 4Ch, 24h
    db 10h, 3Bh, 41h, 0Ch, 74h, 09h, 8Bh, 44h, 24h, 1Ch, 43h, 3Bh, 0D8h, 7Ch, 0E6h, 8Bh
    db 44h, 24h, 1Ch, 3Bh, 0D8h, 75h, 02h, 33h, 0DBh, 8Bh, 0CDh, 0E8h, 7Eh, 0E0h, 0B1h, 0FFh
    db 8Ah, 4Ch, 24h, 30h, 84h, 0C9h, 75h, 04h, 3Bh, 0C3h, 74h, 11h, 6Ah, 01h, 8Bh, 0CDh
    db 0E8h, 50h, 8Ah, 0ADh, 0FFh, 53h, 8Bh, 0CDh, 0E8h, 2Fh, 0E0h, 0B1h, 0FFh, 8Bh, 5Ch, 24h
    db 10h, 8Bh, 84h, 0BEh, 0A8h, 00h, 00h, 00h, 85h, 0C0h, 74h, 4Eh, 50h, 0E8h, 74h, 63h
    db 0B1h, 0FFh, 8Bh, 0D8h, 83h, 0C4h, 04h, 33h, 0EDh, 85h, 0DBh, 7Eh, 39h, 8Dh, 49h, 00h
    db 8Bh, 94h, 0BEh, 0A8h, 00h, 00h, 00h, 55h, 52h, 0E8h, 0B3h, 2Bh, 0B1h, 0FFh, 8Bh, 4Ch
    db 24h, 18h, 8Bh, 51h, 18h, 83h, 0C4h, 08h, 3Bh, 0C2h, 74h, 07h, 45h, 3Bh, 0EBh, 7Ch
    db 0DFh, 0EBh, 13h, 8Bh, 94h, 0BEh, 0A8h, 00h, 00h, 00h, 6Ah, 01h, 55h, 52h, 0E8h, 0E0h
    db 0ABh, 0B1h, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 5Ch, 24h, 10h, 8Bh, 43h, 14h, 50h, 57h, 8Bh
    db 0CEh, 0E8h, 0E5h, 30h, 0B0h, 0FFh, 8Bh, 4Ch, 24h, 20h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_00528b60@@YAXXZ ENDP

; ghidra: FUN_00928f60  retail @ 0x00528F60 size 333
public ?d_00528f60@@YAXXZ
?d_00528f60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0ABh, 05h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 14h, 53h, 33h, 0DBh, 56h, 8Bh, 0F1h
    db 89h, 46h, 04h, 0B0h, 01h, 8Dh, 4Eh, 28h, 89h, 74h, 24h, 08h, 0C7h, 06h, 80h, 6Ch
    db 10h, 01h, 89h, 5Eh, 08h, 89h, 5Eh, 0Ch, 88h, 5Eh, 10h, 88h, 5Eh, 11h, 88h, 5Eh
    db 12h, 88h, 5Eh, 13h, 88h, 5Eh, 14h, 88h, 5Eh, 15h, 88h, 46h, 16h, 88h, 46h, 17h
    db 88h, 5Eh, 18h, 89h, 5Eh, 1Ch, 89h, 5Eh, 20h, 89h, 5Eh, 24h, 0E8h, 5Ch, 78h, 0B1h
    db 0FFh, 68h, 53h, 0EBh, 43h, 00h, 68h, 0DDh, 8Eh, 43h, 00h, 6Ah, 08h, 6Ah, 04h, 8Dh
    db 8Eh, 88h, 00h, 00h, 00h, 51h, 89h, 5Ch, 24h, 28h, 0E8h, 05h, 0DFh, 4Ch, 00h, 8Bh
    db 54h, 24h, 20h, 89h, 9Eh, 08h, 01h, 00h, 00h, 89h, 9Eh, 0Ch, 01h, 00h, 00h, 89h
    db 9Eh, 10h, 01h, 00h, 00h, 89h, 9Eh, 14h, 01h, 00h, 00h, 89h, 96h, 20h, 01h, 00h
    db 00h, 89h, 9Eh, 18h, 01h, 00h, 00h, 89h, 9Eh, 1Ch, 01h, 00h, 00h, 88h, 9Eh, 24h
    db 01h, 00h, 00h, 89h, 9Eh, 28h, 01h, 00h, 00h, 89h, 35h, 0D4h, 49h, 2Fh, 01h, 33h
    db 0C0h, 8Dh, 4Eh, 68h, 89h, 01h, 89h, 41h, 04h, 89h, 41h, 08h, 89h, 41h, 0Ch, 89h
    db 41h, 10h, 89h, 41h, 14h, 89h, 41h, 18h, 89h, 41h, 1Ch, 33h, 0D2h, 8Dh, 86h, 0A8h
    db 00h, 00h, 00h, 89h, 10h, 89h, 50h, 04h, 89h, 50h, 08h, 89h, 50h, 0Ch, 89h, 50h
    db 10h, 89h, 50h, 14h, 89h, 50h, 18h, 89h, 50h, 1Ch, 33h, 0C9h, 8Dh, 96h, 0C8h, 00h
    db 00h, 00h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah, 0Ch, 89h, 4Ah, 10h
    db 89h, 4Ah, 14h, 89h, 4Ah, 18h, 89h, 4Ah, 1Ch, 33h, 0C0h, 8Dh, 8Eh, 0E8h, 00h, 00h
    db 00h, 89h, 01h, 89h, 41h, 04h, 89h, 41h, 08h, 89h, 41h, 0Ch, 89h, 41h, 10h, 89h
    db 41h, 14h, 89h, 41h, 18h, 89h, 41h, 1Ch, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 0C6h, 5Eh, 5Bh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_00528f60@@YAXXZ ENDP

; ghidra: FUN_00929110  retail @ 0x00529110 size 176
public ?d_00529110@@YAXXZ
?d_00529110@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F1h, 05h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 80h
    db 6Ch, 10h, 01h, 8Ah, 46h, 18h, 84h, 0C0h, 0C7h, 44h, 24h, 10h, 02h, 00h, 00h, 00h
    db 74h, 22h, 8Bh, 4Eh, 04h, 0C6h, 46h, 18h, 00h, 8Bh, 01h, 6Ah, 00h, 0FFh, 50h, 38h
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 0FFh, 52h, 30h, 84h, 0C0h, 74h, 08h, 8Bh, 4Eh, 04h, 8Bh
    db 01h, 0FFh, 50h, 3Ch, 39h, 35h, 0D4h, 49h, 2Fh, 01h, 75h, 0Ah, 0C7h, 05h, 0D4h, 49h
    db 2Fh, 01h, 00h, 00h, 00h, 00h, 8Dh, 8Eh, 0Ch, 01h, 00h, 00h, 0C6h, 44h, 24h, 10h
    db 01h, 0E8h, 2Ch, 0D9h, 0AFh, 0FFh, 68h, 53h, 0EBh, 43h, 00h, 6Ah, 08h, 6Ah, 04h, 8Dh
    db 8Eh, 88h, 00h, 00h, 00h, 51h, 0C6h, 44h, 24h, 20h, 00h, 0E8h, 0D6h, 0DBh, 4Ch, 00h
    db 8Dh, 4Eh, 28h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0EEh, 8Eh, 0AEh, 0FFh
    db 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00529110@@YAXXZ ENDP

; ghidra: FUN_009291f0  retail @ 0x005291F0 size 97
public ?d_005291f0@@YAXXZ
?d_005291f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 10h, 8Bh, 4Eh, 04h
    db 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 7Eh, 08h, 8Bh, 46h, 0Ch
    db 3Bh, 0C7h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h
    db 03h, 89h, 7Eh, 0Ch, 39h, 7Eh, 08h, 74h, 25h, 8Ah, 46h, 16h, 84h, 0C0h, 75h, 1Eh
    db 0C6h, 46h, 16h, 01h, 57h, 8Bh, 0CEh, 0E8h, 0E2h, 0F9h, 0AEh, 0FFh, 47h, 83h, 0FFh, 08h
    db 7Ch, 0F2h, 0C6h, 46h, 12h, 01h, 0C6h, 46h, 13h, 01h, 0C6h, 46h, 16h, 00h, 5Fh, 5Eh
    db 0C3h
?d_005291f0@@YAXXZ ENDP

; ghidra: FUN_00929390  retail @ 0x00529390 size 36
public ?d_00529390@@YAXXZ
?d_00529390@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 68h, 42h, 9Ch, 0CDh, 0E4h, 50h, 0E8h, 0FFh, 9Bh, 0B1h
    db 0FFh, 8Bh, 4Ch, 24h, 10h, 89h, 46h, 04h, 83h, 0C4h, 08h, 89h, 41h, 04h, 8Bh, 0C1h
    db 5Eh, 0C2h, 04h, 00h
?d_00529390@@YAXXZ ENDP

; ghidra: FUN_009293e0  retail @ 0x005293E0 size 209
public ?d_005293e0@@YAXXZ
?d_005293e0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 18h, 06h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 47h, 0Ch, 83h
    db 0C7h, 08h, 85h, 0C0h, 75h, 14h, 0B0h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 74h, 24h, 20h, 56h, 8Dh
    db 4Ch, 24h, 20h, 0E8h, 38h, 0E7h, 35h, 00h, 6Ah, 07h, 68h, 0BCh, 0C1h, 09h, 01h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 62h, 0E1h, 35h, 00h, 84h, 0C0h
    db 75h, 37h, 6Ah, 07h, 68h, 0BCh, 0C1h, 09h, 01h, 8Dh, 4Ch, 24h, 24h, 0E8h, 0CEh, 0E8h
    db 35h, 00h, 8Bh, 06h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 48h, 04h, 0EBh, 02h, 33h, 0C9h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 51h, 50h
    db 8Dh, 4Ch, 24h, 24h, 0E8h, 0E7h, 0E8h, 35h, 00h, 8Bh, 37h, 8Dh, 44h, 24h, 1Ch, 50h
    db 8Bh, 0CFh, 0E8h, 0EAh, 9Bh, 0ADh, 0FFh, 3Bh, 0C6h, 8Dh, 4Ch, 24h, 1Ch, 0Fh, 95h, 0C3h
    db 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A3h, 0E4h, 35h, 00h, 8Bh, 4Ch, 24h
    db 0Ch, 5Fh, 5Eh, 8Ah, 0C3h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch
    db 0C3h
?d_005293e0@@YAXXZ ENDP

; ghidra: FUN_009294f0  retail @ 0x005294F0 size 1214
public ?d_005294f0@@YAXXZ
?d_005294f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 69h, 06h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 48h, 53h, 55h, 56h, 33h, 0EDh, 8Bh, 0F1h, 89h
    db 6Ch, 24h, 18h, 8Bh, 46h, 08h, 3Bh, 0C5h, 57h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h
    db 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 6Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C5h
    db 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h
    db 6Eh, 0Ch, 8Bh, 4Eh, 08h, 3Bh, 0CDh, 0Fh, 84h, 4Ch, 04h, 00h, 00h, 8Bh, 7Ch, 24h
    db 68h, 57h, 0E8h, 0C1h, 56h, 0AFh, 0FFh, 3Bh, 0C5h, 0Fh, 84h, 3Ah, 04h, 00h, 00h, 8Bh
    db 0C8h, 0E8h, 79h, 8Dh, 0B1h, 0FFh, 84h, 0C0h, 75h, 0Eh, 0F6h, 86h, 20h, 01h, 00h, 00h
    db 04h, 0C6h, 44h, 24h, 68h, 01h, 74h, 05h, 0C6h, 44h, 24h, 68h, 00h, 57h, 8Bh, 0CEh
    db 0E8h, 0E2h, 14h, 0B1h, 0FFh, 8Bh, 8Ch, 0BEh, 0C8h, 00h, 00h, 00h, 89h, 44h, 24h, 20h
    db 8Dh, 44h, 24h, 18h, 50h, 51h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B7h
    db 21h, 0B1h, 0FFh, 8Bh, 44h, 24h, 20h, 83h, 0C4h, 08h, 3Bh, 0C5h, 7Ch, 15h, 8Bh, 94h
    db 0BEh, 0C8h, 00h, 00h, 00h, 50h, 52h, 0E8h, 0B5h, 23h, 0B1h, 0FFh, 83h, 0C4h, 08h, 89h
    db 44h, 24h, 28h, 0A1h, 50h, 0D7h, 2Eh, 01h, 8Bh, 48h, 0Ch, 2Bh, 48h, 08h, 0B8h, 1Dh
    db 38h, 70h, 0E0h, 0F7h, 0E9h, 03h, 0D1h, 0C1h, 0FAh, 08h, 8Bh, 0DAh, 0C1h, 0EBh, 1Fh, 03h
    db 0DAh, 89h, 5Ch, 24h, 38h, 89h, 6Ch, 24h, 40h, 8Bh, 84h, 0BEh, 0C8h, 00h, 00h, 00h
    db 50h, 89h, 6Ch, 24h, 64h, 0E8h, 0Ah, 0DAh, 0ADh, 0FFh, 8Bh, 0Dh, 0FCh, 0D5h, 2Eh, 01h
    db 83h, 0C4h, 04h, 6Ah, 0FFh, 0E8h, 0B8h, 88h, 0AFh, 0FFh, 8Bh, 54h, 24h, 20h, 8Bh, 0C8h
    db 8Ah, 86h, 24h, 01h, 00h, 00h, 84h, 0C0h, 89h, 4Ch, 24h, 3Ch, 75h, 0Eh, 3Bh, 0D5h
    db 74h, 14h, 83h, 7Ah, 0Ch, 01h, 75h, 0Eh, 84h, 0C0h, 74h, 4Bh, 3Bh, 0D5h, 74h, 47h
    db 83h, 7Ah, 0Ch, 01h, 74h, 41h, 8Bh, 41h, 10h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh
    db 11h, 50h, 51h, 8Bh, 0C4h, 89h, 64h, 24h, 3Ch, 55h, 68h, 94h, 0B8h, 0Eh, 01h, 50h
    db 0FFh, 52h, 28h, 8Bh, 8Ch, 0BEh, 0C8h, 00h, 00h, 00h, 51h, 0E8h, 0D8h, 5Ch, 0B0h, 0FFh
    db 8Bh, 94h, 0BEh, 0C8h, 00h, 00h, 00h, 6Ah, 0FFh, 50h, 52h, 89h, 44h, 24h, 30h, 0E8h
    db 0A7h, 39h, 0AFh, 0FFh, 83h, 0C4h, 18h, 6Ah, 14h, 89h, 6Ch, 24h, 30h, 89h, 6Ch, 24h
    db 50h, 0E8h, 0BAh, 4Eh, 30h, 00h, 89h, 44h, 24h, 50h, 89h, 6Ch, 24h, 54h, 0C6h, 00h
    db 00h, 8Bh, 44h, 24h, 50h, 89h, 68h, 04h, 8Bh, 44h, 24h, 50h, 89h, 40h, 08h, 8Bh
    db 44h, 24h, 50h, 83h, 0C4h, 04h, 89h, 40h, 0Ch, 8Ah, 86h, 24h, 01h, 00h, 00h, 84h
    db 0C0h, 0C6h, 44h, 24h, 60h, 01h, 74h, 0Ah, 39h, 6Ch, 24h, 20h, 0Fh, 84h, 0F6h, 01h
    db 00h, 00h, 3Bh, 0DDh, 89h, 6Ch, 24h, 24h, 0Fh, 8Eh, 0EAh, 01h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 4Ch, 24h, 24h, 51h, 8Bh, 0Dh, 50h, 0D7h, 2Eh, 01h, 0E8h, 0F2h, 0E4h, 0B0h, 0FFh
    db 8Bh, 0E8h, 85h, 0EDh, 0Fh, 84h, 0BBh, 01h, 00h, 00h, 8Ah, 85h, 0BDh, 00h, 00h, 00h
    db 84h, 0C0h, 0Fh, 84h, 0ADh, 01h, 00h, 00h, 8Ah, 85h, 0BCh, 00h, 00h, 00h, 84h, 0C0h
    db 0Fh, 85h, 9Fh, 01h, 00h, 00h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 8Bh, 45h
    db 08h, 85h, 0C0h, 0C6h, 44h, 24h, 60h, 02h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 50h, 51h, 89h, 64h, 24h, 4Ch, 8Bh, 0CCh, 68h, 28h, 0Eh, 10h
    db 01h, 0E8h, 8Ah, 0F4h, 35h, 00h, 8Dh, 54h, 24h, 1Ch, 52h, 0E8h, 0B0h, 0F8h, 35h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 50h, 0E8h, 20h, 99h, 0ADh
    db 0FFh, 3Bh, 44h, 24h, 4Ch, 8Dh, 4Ch, 24h, 14h, 74h, 0Fh, 0C6h, 44h, 24h, 60h, 01h
    db 0E8h, 0DBh, 0E1h, 35h, 00h, 0E9h, 3Bh, 01h, 00h, 00h, 51h, 8Dh, 54h, 24h, 48h, 52h
    db 8Dh, 4Ch, 24h, 54h, 0E8h, 30h, 77h, 0B0h, 0FFh, 8Bh, 5Ch, 24h, 20h, 85h, 0DBh, 74h
    db 3Fh, 8Bh, 6Dh, 08h, 85h, 0EDh, 8Dh, 45h, 08h, 75h, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 50h, 8Dh, 4Ch, 24h, 34h, 0E8h, 26h, 0F4h, 35h, 00h, 8Bh, 54h, 24h, 1Ch, 8Dh, 44h
    db 24h, 30h, 50h, 83h, 0CAh, 01h, 53h, 0C6h, 44h, 24h, 68h, 03h, 89h, 54h, 24h, 24h
    db 0E8h, 0BAh, 0F7h, 0AFh, 0FFh, 83h, 0C4h, 08h, 84h, 0C0h, 75h, 04h, 32h, 0DBh, 0EBh, 02h
    db 0B3h, 01h, 0F6h, 44h, 24h, 1Ch, 01h, 0C7h, 44h, 24h, 60h, 02h, 00h, 00h, 00h, 74h
    db 14h, 8Bh, 44h, 24h, 1Ch, 83h, 0E0h, 0FEh, 8Dh, 4Ch, 24h, 30h, 89h, 44h, 24h, 1Ch
    db 0E8h, 5Bh, 0E1h, 35h, 00h, 84h, 0DBh, 0Fh, 84h, 0A6h, 00h, 00h, 00h, 8Dh, 4Ch, 24h
    db 13h, 51h, 51h, 8Dh, 54h, 24h, 1Ch, 89h, 64h, 24h, 4Ch, 8Bh, 0CCh, 52h, 0E8h, 5Dh
    db 0E3h, 35h, 00h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 8Dh, 54h, 24h, 3Ch, 52h
    db 0FFh, 50h, 24h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 0C6h, 44h, 24h, 60h, 04h, 74h, 65h
    db 8Bh, 44h, 24h, 3Ch, 8Bh, 40h, 10h, 50h, 51h, 89h, 64h, 24h, 4Ch, 8Bh, 0DCh, 6Ah
    db 00h, 51h, 8Dh, 54h, 24h, 24h, 89h, 64h, 24h, 54h, 8Bh, 0CCh, 52h, 0E8h, 1Eh, 0E3h
    db 35h, 00h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 01h, 53h, 0FFh, 50h, 24h, 8Bh, 8Ch
    db 0BEh, 0C8h, 00h, 00h, 00h, 51h, 0E8h, 0DDh, 5Ah, 0B0h, 0FFh, 8Bh, 5Ch, 24h, 30h, 8Bh
    db 94h, 0BEh, 0C8h, 00h, 00h, 00h, 53h, 50h, 52h, 89h, 44h, 24h, 30h, 0E8h, 0A9h, 37h
    db 0AFh, 0FFh, 8Bh, 44h, 24h, 40h, 83h, 0C4h, 18h, 3Bh, 0C3h, 75h, 08h, 8Bh, 44h, 24h
    db 18h, 89h, 44h, 24h, 2Ch, 8Dh, 4Ch, 24h, 34h, 0C6h, 44h, 24h, 60h, 02h, 0E8h, 3Dh
    db 0E9h, 35h, 00h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 60h, 01h, 0E8h, 9Fh, 0E0h, 35h
    db 00h, 8Bh, 5Ch, 24h, 38h, 8Bh, 44h, 24h, 24h, 40h, 3Bh, 0C3h, 89h, 44h, 24h, 24h
    db 0Fh, 8Ch, 1Ah, 0FEh, 0FFh, 0FFh, 33h, 0EDh, 39h, 6Ch, 24h, 50h, 74h, 2Ah, 8Bh, 4Ch
    db 24h, 4Ch, 8Bh, 51h, 04h, 52h, 8Dh, 4Ch, 24h, 50h, 0E8h, 40h, 0F7h, 0AFh, 0FFh, 8Bh
    db 44h, 24h, 4Ch, 89h, 40h, 08h, 8Bh, 44h, 24h, 4Ch, 89h, 68h, 04h, 8Bh, 44h, 24h
    db 4Ch, 89h, 40h, 0Ch, 89h, 6Ch, 24h, 50h, 39h, 6Ch, 24h, 20h, 75h, 67h, 8Ah, 44h
    db 24h, 68h, 84h, 0C0h, 74h, 5Fh, 8Bh, 0Dh, 0FCh, 0D5h, 2Eh, 01h, 6Ah, 0FEh, 0E8h, 0BFh
    db 85h, 0AFh, 0FFh, 8Bh, 40h, 10h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh, 11h, 50h, 51h
    db 8Bh, 0C4h, 89h, 64h, 24h, 70h, 55h, 68h, 84h, 0B8h, 0Eh, 01h, 50h, 0FFh, 52h, 28h
    db 8Bh, 8Ch, 0BEh, 0C8h, 00h, 00h, 00h, 51h, 0E8h, 0Bh, 5Ah, 0B0h, 0FFh, 8Bh, 94h, 0BEh
    db 0C8h, 00h, 00h, 00h, 6Ah, 0FEh, 50h, 52h, 89h, 44h, 24h, 30h, 0E8h, 0DAh, 36h, 0AFh
    db 0FFh, 8Bh, 44h, 24h, 40h, 83h, 0C4h, 18h, 83h, 0F8h, 0FEh, 75h, 08h, 8Bh, 44h, 24h
    db 18h, 89h, 44h, 24h, 2Ch, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 94h, 0BEh, 0C8h, 00h, 00h, 00h
    db 55h, 51h, 52h, 0E8h, 5Bh, 0A0h, 0B1h, 0FFh, 8Bh, 84h, 0BEh, 0C8h, 00h, 00h, 00h, 6Ah
    db 0Ah, 50h, 0E8h, 09h, 0A7h, 0B1h, 0FFh, 83h, 0C4h, 14h, 8Dh, 4Ch, 24h, 4Ch, 0C6h, 44h
    db 24h, 60h, 00h, 0E8h, 5Fh, 9Ch, 0AFh, 0FFh, 8Dh, 4Ch, 24h, 40h, 0C7h, 44h, 24h, 60h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 37h, 0E8h, 35h, 00h, 8Bh, 4Ch, 24h, 58h, 5Fh, 5Eh, 5Dh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 54h, 0C2h, 04h, 00h
?d_005294f0@@YAXXZ ENDP

; ghidra: FUN_00929b10  retail @ 0x00529B10 size 56
public ?d_00529b10@@YAXXZ
?d_00529b10@@YAXXZ PROC
    db 57h, 8Bh, 0F9h, 8Ah, 47h, 16h, 84h, 0C0h, 75h, 2Ch, 56h, 0C6h, 47h, 16h, 01h, 33h
    db 0F6h, 56h, 8Bh, 0CFh, 0E8h, 0Ch, 01h, 0B0h, 0FFh, 6Ah, 00h, 56h, 8Bh, 0CFh, 0E8h, 5Eh
    db 4Fh, 0B0h, 0FFh, 56h, 8Bh, 0CFh, 0E8h, 4Fh, 38h, 0B0h, 0FFh, 46h, 83h, 0FEh, 08h, 7Ch
    db 0E0h, 0C6h, 47h, 16h, 00h, 5Eh, 5Fh, 0C3h
?d_00529b10@@YAXXZ ENDP

; ghidra: FUN_00929bb0  retail @ 0x00529BB0 size 36
public ?d_00529bb0@@YAXXZ
?d_00529bb0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 7Eh, 04h, 68h, 42h, 9Ch, 0CDh, 0E4h, 57h, 0E8h, 0DEh, 93h
    db 0B1h, 0FFh, 89h, 46h, 04h, 8Bh, 44h, 24h, 14h, 83h, 0C4h, 08h, 89h, 78h, 04h, 5Fh
    db 5Eh, 0C2h, 08h, 00h
?d_00529bb0@@YAXXZ ENDP

; ghidra: FUN_00929be0  retail @ 0x00529BE0 size 186
_TEXT ENDS
_TEXT$d00929be0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00929BE0 size 186
public ?d_00529be0@@YAXXZ
?d_00529be0@@YAXXZ PROC
    db 057h, 08Bh, 0F9h, 08Dh, 04Fh, 028h
    call ?j_00042f87@@YAXXZ
    db 084h, 0C0h, 074h, 00Ah, 08Bh, 087h, 008h, 001h, 000h, 000h, 085h, 0C0h, 075h, 004h, 032h, 0C0h
    db 05Fh, 0C3h, 056h, 06Ah, 000h, 06Ah, 000h
    call ?j_000364c6@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0F0h, 068h, 031h, 080h, 0DCh, 0B9h, 056h
    call ?j_0002a473@@YAXXZ
    db 083h, 0C4h, 008h, 03Dh, 079h, 09Ch, 0DEh, 066h, 074h, 074h, 056h, 056h
    call ?j_0003d32a@@YAXXZ
    db 00Fh, 0BFh, 0C0h, 08Bh, 04Ch, 087h, 068h, 083h, 0C4h, 008h, 085h, 0C9h, 074h, 05Ah, 056h, 056h
    call ?j_0003d32a@@YAXXZ
    db 00Fh, 0BFh, 0C8h, 08Dh, 084h, 08Fh, 088h, 000h, 000h, 000h, 08Bh, 008h, 083h, 0C4h, 008h, 085h
    db 0C9h, 074h, 040h, 056h, 056h
    call ?j_0003d32a@@YAXXZ
    db 00Fh, 0BFh, 0D0h, 08Bh, 084h, 097h, 0A8h, 000h, 000h, 000h, 083h, 0C4h, 008h, 085h, 0C0h, 074h
    db 028h, 056h, 056h
    call ?j_0003d32a@@YAXXZ
    db 00Fh, 0BFh, 0C0h, 08Bh, 08Ch, 087h, 0C8h, 000h, 000h, 000h, 083h, 0C4h, 008h, 085h, 0C9h, 074h
    db 010h, 068h, 042h, 09Ch, 0CDh, 0E4h, 056h
    call ?j_00042fa0@@YAXXZ
    db 0E9h, 077h, 0FFh, 0FFh, 0FFh, 05Eh, 032h, 0C0h, 05Fh, 0C3h, 05Eh, 0B0h, 001h, 05Fh, 0C3h
?d_00529be0@@YAXXZ ENDP
_TEXT$d00929be0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00929cd0  retail @ 0x00529CD0 size 391
public ?d_00529cd0@@YAXXZ
?d_00529cd0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 98h, 06h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 33h
    db 0DBh, 3Bh, 0C3h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h
    db 75h, 03h, 89h, 5Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C3h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 5Eh, 0Ch, 8Bh, 4Eh, 08h, 3Bh
    db 0CBh, 75h, 15h, 5Eh, 32h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 0C6h, 46h, 17h, 00h, 8Bh, 01h, 57h, 0FFh
    db 50h, 14h, 8Bh, 7Ch, 24h, 28h, 3Bh, 0F8h, 75h, 16h, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
    db 55h, 8Bh, 6Ch, 0BEh, 68h, 8Dh, 4Ch, 24h, 18h, 51h, 55h, 0E8h, 0EAh, 19h, 0B1h, 0FFh
    db 8Bh, 44h, 24h, 20h, 83h, 0C4h, 08h, 3Bh, 0C3h, 0Fh, 8Ch, 0C1h, 00h, 00h, 00h, 8Bh
    db 4Eh, 08h, 57h, 0E8h, 90h, 4Eh, 0AFh, 0FFh, 8Bh, 0F8h, 3Bh, 0FBh, 0Fh, 84h, 0AEh, 00h
    db 00h, 00h, 8Bh, 54h, 24h, 18h, 52h, 55h, 0E8h, 0D4h, 1Bh, 0B1h, 0FFh, 8Bh, 0D8h, 8Bh
    db 47h, 04h, 83h, 0C4h, 08h, 3Bh, 0D8h, 0Fh, 84h, 93h, 00h, 00h, 00h, 83h, 0FBh, 05h
    db 0Fh, 84h, 8Ah, 00h, 00h, 00h, 8Bh, 0CFh, 0E8h, 22h, 85h, 0B1h, 0FFh, 88h, 44h, 24h
    db 13h, 8Dh, 44h, 24h, 14h, 55h, 50h, 0E8h, 08h, 6Dh, 0B1h, 0FFh, 83h, 0C4h, 08h, 8Bh
    db 4Eh, 04h, 8Bh, 11h, 8Dh, 44h, 24h, 14h, 50h, 53h, 57h, 0C7h, 44h, 24h, 30h, 00h
    db 00h, 00h, 00h, 0FFh, 52h, 18h, 84h, 0C0h, 74h, 45h, 8Bh, 0CFh, 0E8h, 0EEh, 84h, 0B1h
    db 0FFh, 32h, 44h, 24h, 13h, 74h, 0Ch, 8Bh, 4Ch, 24h, 2Ch, 51h, 8Bh, 0CEh, 0E8h, 87h
    db 35h, 0B0h, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C6h, 46h, 10h, 01h, 0C7h, 44h, 24h, 24h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0B8h, 0E3h, 35h, 00h, 5Dh, 5Fh, 5Eh, 0B0h, 01h, 5Bh, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 8Dh
    db 4Ch, 24h, 14h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 90h, 0E3h, 35h, 00h
    db 8Bh, 4Ch, 24h, 1Ch, 5Dh, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_00529cd0@@YAXXZ ENDP

; ghidra: FUN_00929ec0  retail @ 0x00529EC0 size 843
public ?d_00529ec0@@YAXXZ
?d_00529ec0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D0h, 06h, 03h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 33h, 0EDh
    db 3Bh, 0C5h, 57h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h
    db 75h, 03h, 89h, 6Eh, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C5h, 74h, 10h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 03h, 89h, 6Eh, 0Ch, 39h, 6Eh, 08h, 0Fh
    db 84h, 34h, 01h, 00h, 00h, 8Ah, 46h, 16h, 84h, 0C0h, 0Fh, 85h, 0D1h, 02h, 00h, 00h
    db 89h, 6Ch, 24h, 10h, 8Bh, 44h, 24h, 24h, 3Dh, 08h, 40h, 00h, 00h, 89h, 6Ch, 24h
    db 1Ch, 0Fh, 87h, 0F1h, 00h, 00h, 00h, 74h, 2Eh, 48h, 0Fh, 84h, 0A0h, 02h, 00h, 00h
    db 48h, 0Fh, 84h, 99h, 02h, 00h, 00h, 83h, 0E8h, 15h, 0Fh, 85h, 0E8h, 00h, 00h, 00h
    db 83h, 7Ch, 24h, 28h, 01h, 0Fh, 85h, 85h, 02h, 00h, 00h, 8Bh, 44h, 24h, 2Ch, 0C6h
    db 00h, 01h, 0E9h, 79h, 02h, 00h, 00h, 8Bh, 4Ch, 24h, 28h, 51h, 8Dh, 4Eh, 28h, 0E8h
    db 0E8h, 0E0h, 0AEh, 0FFh, 8Bh, 0D8h, 3Bh, 0DDh, 0Fh, 8Ch, 62h, 02h, 00h, 00h, 33h, 0FFh
    db 8Bh, 4Eh, 08h, 57h, 0E8h, 8Fh, 4Ch, 0AFh, 0FFh, 3Bh, 0C5h, 74h, 05h, 39h, 58h, 10h
    db 74h, 27h, 47h, 83h, 0FFh, 08h, 7Ch, 0E8h, 55h, 8Bh, 0CEh, 0E8h, 2Eh, 37h, 0AFh, 0FFh
    db 3Bh, 0C5h, 7Dh, 07h, 8Bh, 0CEh, 0E8h, 63h, 0A0h, 0B0h, 0FFh, 53h, 50h, 8Bh, 0CEh, 0E8h
    db 3Dh, 72h, 0B0h, 0FFh, 0E9h, 27h, 02h, 00h, 00h, 3Bh, 0FDh, 7Ch, 0DBh, 8Bh, 4Eh, 08h
    db 57h, 0E8h, 52h, 4Ch, 0AFh, 0FFh, 8Bh, 4Eh, 08h, 8Bh, 11h, 8Bh, 0E8h, 0FFh, 52h, 14h
    db 3Bh, 0F8h, 74h, 27h, 8Bh, 4Eh, 08h, 8Bh, 01h, 0FFh, 50h, 10h, 84h, 0C0h, 0Fh, 84h
    db 0FCh, 01h, 00h, 00h, 85h, 0EDh, 0Fh, 84h, 0F4h, 01h, 00h, 00h, 8Bh, 0CDh, 0E8h, 0ECh
    db 82h, 0B1h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0E5h, 01h, 00h, 00h, 8Dh, 4Fh, 01h, 51h, 8Bh
    db 0CEh, 0E8h, 0C8h, 36h, 0AFh, 0FFh, 6Ah, 0FFh, 57h, 8Bh, 0CEh, 8Bh, 0E8h, 0E8h, 0DFh, 71h
    db 0B0h, 0FFh, 85h, 0EDh, 0Fh, 8Ch, 0C6h, 01h, 00h, 00h, 53h, 55h, 8Bh, 0CEh, 0E8h, 0CEh
    db 71h, 0B0h, 0FFh, 0E9h, 0B8h, 01h, 00h, 00h, 2Dh, 14h, 40h, 00h, 00h, 0Fh, 84h, 59h
    db 01h, 00h, 00h, 83h, 0E8h, 11h, 74h, 28h, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 1Ch
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 87h, 0E1h, 35h, 00h, 33h, 0C0h, 8Bh, 4Ch, 24h, 14h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
    db 8Bh, 6Ch, 24h, 28h, 33h, 0DBh, 8Dh, 0BEh, 0C8h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 3Bh, 6Fh, 0C0h, 74h, 3Ch, 3Bh, 2Fh, 74h, 49h, 3Bh, 6Fh, 0E0h, 74h, 55h, 3Bh, 6Fh
    db 0A0h, 75h, 0Ch, 8Bh, 4Eh, 08h, 8Bh, 11h, 0FFh, 52h, 10h, 84h, 0C0h, 75h, 55h, 3Bh
    db 0AEh, 18h, 01h, 00h, 00h, 74h, 5Eh, 3Bh, 0AEh, 1Ch, 01h, 00h, 00h, 0Fh, 84h, 0A9h
    db 00h, 00h, 00h, 43h, 83h, 0C7h, 04h, 83h, 0FBh, 08h, 7Ch, 0C4h, 0E9h, 2Fh, 01h, 00h
    db 00h, 53h, 8Bh, 0CEh, 0E8h, 4Eh, 7Ch, 0ADh, 0FFh, 0C6h, 46h, 10h, 01h, 0E9h, 1Eh, 01h
    db 00h, 00h, 53h, 8Bh, 0CEh, 0E8h, 0F8h, 0A0h, 0AFh, 0FFh, 0C6h, 46h, 10h, 01h, 0E9h, 0Dh
    db 01h, 00h, 00h, 53h, 8Bh, 0CEh, 0E8h, 0B6h, 0DDh, 0ADh, 0FFh, 0C6h, 46h, 10h, 01h, 0E9h
    db 0FCh, 00h, 00h, 00h, 53h, 8Bh, 0CEh, 0E8h, 11h, 48h, 0AFh, 0FFh, 0C6h, 46h, 10h, 01h
    db 0E9h, 0EBh, 00h, 00h, 00h, 8Bh, 86h, 18h, 01h, 00h, 00h, 50h, 0E8h, 0ABh, 29h, 0B0h
    db 0FFh, 83h, 0C4h, 04h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 50h, 51h, 89h, 64h, 24h, 30h
    db 8Bh, 0CCh, 68h, 70h, 0C7h, 07h, 01h, 0E8h, 0A4h, 0EAh, 35h, 00h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 0C6h, 44h, 24h, 24h, 00h, 0FFh, 52h, 04h, 8Bh, 0C8h, 0E8h, 99h, 0DBh, 0AEh, 0FFh
    db 8Bh, 4Eh, 04h, 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 0C6h
    db 46h, 11h, 01h, 0C6h, 46h, 10h, 01h, 0E9h, 94h, 00h, 00h, 00h, 6Ah, 00h, 51h, 89h
    db 64h, 24h, 30h, 8Bh, 0CCh, 68h, 90h, 6Ch, 10h, 01h, 0E8h, 61h, 0EAh, 35h, 00h, 8Bh
    db 4Eh, 04h, 8Bh, 01h, 0C6h, 44h, 24h, 24h, 00h, 0FFh, 50h, 04h, 8Bh, 0C8h, 0E8h, 56h
    db 0DBh, 0AEh, 0FFh, 8Bh, 4Eh, 04h, 8Bh, 11h, 0FFh, 52h, 04h, 8Bh, 10h, 8Bh, 0C8h, 0FFh
    db 52h, 0Ch, 0C6h, 46h, 11h, 01h, 0C6h, 46h, 10h, 01h, 0EBh, 54h, 8Bh, 44h, 24h, 28h
    db 3Bh, 86h, 08h, 01h, 00h, 00h, 75h, 48h, 8Bh, 4Ch, 24h, 2Ch, 3Bh, 0CDh, 7Dh, 0Eh
    db 68h, 50h, 6Eh, 33h, 01h, 8Bh, 0CEh, 0E8h, 0Ah, 55h, 0B1h, 0FFh, 0EBh, 32h, 8Bh, 86h
    db 0Ch, 01h, 00h, 00h, 8Dh, 0Ch, 88h, 51h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 9Fh, 0D9h, 35h
    db 00h, 8Dh, 54h, 24h, 28h, 52h, 8Bh, 0CEh, 0C6h, 44h, 24h, 20h, 03h, 0E8h, 0E4h, 54h
    db 0B1h, 0FFh, 8Dh, 4Ch, 24h, 28h, 0C6h, 44h, 24h, 1Ch, 00h, 0E8h, 60h, 0D7h, 35h, 00h
    db 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0DFh, 0DFh, 35h
    db 00h, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_00529ec0@@YAXXZ ENDP

; ghidra: FUN_0092a2e0  retail @ 0x0052A2E0 size 1306
_TEXT ENDS
_TEXT$d0092a2e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0092A2E0 size 1306
public ?d_0052a2e0@@YAXXZ
?d_0052a2e0@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va01030744
    db 050h, 0A1h
    dd ?TheMapCache@@3PAVMapCache@@A
    db 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 054h, 053h, 055h, 056h, 033h, 0EDh, 03Bh
    db 0C5h, 057h, 08Bh, 0F9h, 00Fh, 084h, 0D8h, 004h, 000h, 000h, 08Bh, 087h, 008h, 001h, 000h, 000h
    db 03Bh, 0C5h, 00Fh, 084h, 0CAh, 004h, 000h, 000h, 033h, 0F6h, 0BBh, 00Ah, 000h, 000h, 000h, 050h
    db 089h, 06Ch, 024h, 030h, 089h, 06Ch, 024h, 02Ch, 089h, 06Ch, 024h, 028h, 089h, 06Ch, 024h, 024h
    db 089h, 06Ch, 024h, 020h, 089h, 074h, 024h, 018h, 089h, 05Ch, 024h, 014h, 0C6h, 047h, 016h, 001h
    call ?j_000267a1@@YAXXZ
    db 083h, 0C4h, 004h, 083h, 0F8h, 001h, 089h, 044h, 024h, 018h, 00Fh, 08Eh, 0B0h, 001h, 000h, 000h
    db 068h
    dd g_Va01106D2C
    db 08Dh, 04Ch, 024h, 018h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 014h, 050h, 089h, 06Ch, 024h, 070h
    call ?j_0001d606@@YAXXZ
    db 083h, 0CEh, 0FFh, 08Dh, 04Ch, 024h, 014h, 089h, 044h, 024h, 02Ch, 089h, 074h, 024h, 06Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 068h
    dd g_Va01106D0C
    db 08Dh, 04Ch, 024h, 018h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 0C7h, 044h, 024h, 070h, 001h, 000h, 000h, 000h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 089h, 044h, 024h, 028h, 089h, 074h, 024h, 06Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 068h
    dd g_Va01106CEC
    db 08Dh, 04Ch, 024h, 018h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 054h, 024h, 014h, 052h, 0C7h, 044h, 024h, 070h, 002h, 000h, 000h, 000h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 089h, 044h, 024h, 024h, 089h, 074h, 024h, 06Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 068h
    dd g_Va01106CCC
    db 08Dh, 04Ch, 024h, 014h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 010h, 050h, 0C7h, 044h, 024h, 070h, 003h, 000h, 000h, 000h
    call ?j_0001d606@@YAXXZ
    db 08Bh, 0D8h, 08Dh, 04Ch, 024h, 010h, 089h, 05Ch, 024h, 020h, 089h, 074h, 024h, 06Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 068h
    dd g_Va01106CA4
    db 08Dh, 04Ch, 024h, 018h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 0C7h, 044h, 024h, 070h, 004h, 000h, 000h, 000h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 089h, 044h, 024h, 01Ch, 089h, 074h, 024h, 06Ch
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 04Ch
    call ?j_00047767@@YAXXZ
    db 06Ah, 03Ch, 0C7h, 044h, 024h, 070h, 005h, 000h, 000h, 000h
    call ??2@YAPAXI@Z
    db 08Bh, 0F0h, 083h, 0C4h, 004h, 089h, 074h, 024h, 038h, 03Bh, 0F5h, 0C6h, 044h, 024h, 06Ch, 006h
    db 074h, 01Ah, 051h, 08Bh, 0D4h, 089h, 064h, 024h, 038h, 052h, 08Dh, 04Ch, 024h, 054h
    call ?j_00010898@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00008602@@YAXXZ
    db 0EBh, 002h, 033h, 0C0h, 03Bh, 0DDh, 0C6h, 044h, 024h, 06Ch, 005h, 089h, 044h, 024h, 014h, 074h
    db 005h, 08Bh, 05Bh, 024h, 0EBh, 005h, 0BBh, 00Ah, 000h, 000h, 000h, 08Bh, 087h, 008h, 001h, 000h
    db 000h, 055h, 050h
    call ?j_00030391@@YAXXZ
    db 083h, 0C4h, 008h, 03Bh, 0C3h, 07Dh, 012h, 08Bh, 08Fh, 008h, 001h, 000h, 000h, 055h, 051h
    call ?j_00030391@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0D8h, 08Dh, 04Ch, 024h, 04Ch, 089h, 05Ch, 024h, 010h, 0C7h, 044h, 024h
    db 06Ch, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_00046b82@@YAXXZ
    db 08Bh, 074h, 024h, 014h, 0F6h, 044h, 024h, 074h, 040h, 075h, 028h, 08Bh, 097h, 008h, 001h, 000h
    db 000h, 052h
    call ?j_0000a3df@@YAXXZ
    db 08Bh, 087h, 010h, 001h, 000h, 000h, 08Bh, 097h, 00Ch, 001h, 000h, 000h, 08Dh, 08Fh, 00Ch, 001h
    db 000h, 000h, 083h, 0C4h, 004h, 050h, 052h
    call ?j_00024c17@@YAXXZ
    db 089h, 06Ch, 024h, 040h, 089h, 06Ch, 024h, 044h, 089h, 06Ch, 024h, 048h, 08Bh, 04Ch, 024h, 074h
    db 08Dh, 044h, 024h, 040h, 050h, 051h, 0C7h, 044h, 024h, 074h, 007h, 000h, 000h, 000h
    call ?j_0000bcd5@@YAXXZ
    db 08Bh, 044h, 024h, 04Ch, 08Bh, 04Ch, 024h, 048h, 0C6h, 044h, 024h, 07Ch, 000h, 08Bh, 054h, 024h
    db 07Ch, 052h, 050h, 051h
    call ?j_00032e93@@YAXXZ
    db 08Bh, 044h, 024h, 054h, 08Bh, 04Ch, 024h, 058h, 083h, 0C4h, 014h, 03Bh, 0C1h, 089h, 044h, 024h
    db 074h, 00Fh, 084h, 0FFh, 001h, 000h, 000h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h
    db 018h, 08Bh, 054h, 024h, 074h, 08Bh, 02Ah, 083h, 0C8h, 0FFh, 083h, 0CEh, 0FFh, 083h, 0F9h, 001h
    db 00Fh, 08Eh, 023h, 001h, 000h, 000h, 08Ah, 04Dh, 024h, 084h, 0C9h, 00Fh, 084h, 018h, 001h, 000h
    db 000h, 08Bh, 045h, 050h, 085h, 0C0h, 06Ah, 002h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 051h, 089h, 064h, 024h, 040h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 074h, 024h, 01Ch, 08Bh, 0CEh
    call ?j_000371b9@@YAXXZ
    db 089h, 044h, 024h, 038h, 08Bh, 045h, 050h, 085h, 0C0h, 06Ah, 003h, 074h, 005h, 083h, 0C0h, 008h
    db 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 051h, 089h, 064h, 024h, 03Ch, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 0CEh
    call ?j_000371b9@@YAXXZ
    db 089h, 044h, 024h, 034h, 08Bh, 045h, 050h, 085h, 0C0h, 06Ah, 004h, 074h, 005h, 083h, 0C0h, 008h
    db 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 051h, 089h, 064h, 024h, 038h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 0CEh
    call ?j_000371b9@@YAXXZ
    db 089h, 044h, 024h, 030h, 08Bh, 045h, 050h, 085h, 0C0h, 06Ah, 005h, 074h, 005h, 083h, 0C0h, 008h
    db 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 051h, 089h, 064h, 024h, 044h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 0CEh
    call ?j_000371b9@@YAXXZ
    db 085h, 0C0h, 074h, 00Bh, 08Bh, 04Ch, 024h, 01Ch, 0BEh, 004h, 000h, 000h, 000h, 0EBh, 03Fh, 08Bh
    db 044h, 024h, 030h, 085h, 0C0h, 074h, 00Bh, 08Bh, 04Ch, 024h, 020h, 0BEh, 003h, 000h, 000h, 000h
    db 0EBh, 02Ch, 08Bh, 044h, 024h, 034h, 085h, 0C0h, 074h, 00Bh, 08Bh, 04Ch, 024h, 024h, 0BEh, 002h
    db 000h, 000h, 000h, 0EBh, 019h, 08Bh, 044h, 024h, 038h, 085h, 0C0h, 074h, 00Bh, 08Bh, 04Ch, 024h
    db 028h, 0BEh, 001h, 000h, 000h, 000h, 0EBh, 006h, 08Bh, 04Ch, 024h, 02Ch, 033h, 0F6h, 08Bh, 044h
    db 024h, 010h, 08Bh, 097h, 008h, 001h, 000h, 000h, 06Ah, 0FFh, 06Ah, 001h, 050h, 053h, 06Ah, 000h
    db 06Ah, 0FFh, 051h, 052h
    call ?j_0001712a@@YAXXZ
    db 083h, 0C4h, 020h, 08Bh, 04Ch, 024h, 018h, 06Ah, 001h, 049h, 051h, 050h, 06Ah, 0FFh, 051h, 08Bh
    db 0C4h, 089h, 064h, 024h, 050h, 050h, 08Bh, 0CDh
    call ?j_0000a6fa@@YAXXZ
    db 08Bh, 08Fh, 008h, 001h, 000h, 000h, 051h
    call ?j_0003fe86@@YAXXZ
    db 08Bh, 097h, 014h, 001h, 000h, 000h, 08Dh, 04Dh, 050h, 08Dh, 0AFh, 00Ch, 001h, 000h, 000h, 089h
    db 044h, 024h, 050h, 08Bh, 045h, 004h, 083h, 0C4h, 018h, 03Bh, 0C2h, 074h, 029h, 089h, 044h, 024h
    db 03Ch, 089h, 044h, 024h, 034h, 085h, 0C0h, 0C6h, 044h, 024h, 06Ch, 008h, 074h, 008h, 051h, 08Bh
    db 0C8h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 045h, 004h, 083h, 0C0h, 004h, 0C6h, 044h, 024h, 06Ch, 007h, 089h, 045h, 004h, 0EBh, 012h
    db 06Ah, 001h, 06Ah, 001h, 08Dh, 054h, 024h, 07Ch, 052h, 051h, 050h, 08Bh, 0CDh
    call ?j_0003827b@@YAXXZ
    db 083h, 07Ch, 024h, 018h, 001h, 07Eh, 017h, 08Bh, 044h, 024h, 038h, 08Bh, 08Fh, 008h, 001h, 000h
    db 000h, 06Ah, 001h, 050h, 056h, 051h
    call ?j_00049f30@@YAXXZ
    db 083h, 0C4h, 010h, 08Bh, 044h, 024h, 074h, 08Bh, 04Ch, 024h, 044h, 083h, 0C0h, 004h, 03Bh, 0C1h
    db 089h, 044h, 024h, 074h, 00Fh, 085h, 011h, 0FEh, 0FFh, 0FFh, 08Bh, 044h, 024h, 040h, 08Bh, 074h
    db 024h, 014h, 033h, 0EDh, 03Bh, 0F5h, 074h, 00Ch, 08Bh, 016h, 06Ah, 001h, 08Bh, 0CEh, 0FFh, 012h
    db 08Bh, 044h, 024h, 040h, 03Bh, 0C5h, 0C6h, 047h, 016h, 000h, 0C7h, 044h, 024h, 06Ch, 0FFh, 0FFh
    db 0FFh, 0FFh, 074h, 03Ch, 08Bh, 04Ch, 024h, 048h, 02Bh, 0C8h, 0C1h, 0F9h, 002h, 0C1h, 0E1h, 002h
    db 081h, 0F9h, 080h, 000h, 000h, 000h, 076h, 01Eh, 050h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 064h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh
    db 05Dh, 05Bh, 083h, 0C4h, 060h, 0C2h, 004h, 000h, 051h, 050h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Bh, 04Ch, 024h, 064h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 083h, 0C4h, 060h, 0C2h, 004h, 000h
?d_0052a2e0@@YAXXZ ENDP
_TEXT$d0092a2e0 ENDS
_TEXT SEGMENT

; ghidra: FUN_0092a940  retail @ 0x0052A940 size 312
public ?d_0052a940@@YAXXZ
?d_0052a940@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 88h, 07h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h
    db 0C0h, 74h, 14h, 8Bh, 4Eh, 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h
    db 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 14h, 8Bh, 4Eh
    db 04h, 8Bh, 11h, 50h, 0FFh, 52h, 24h, 84h, 0C0h, 75h, 07h, 0C7h, 46h, 0Ch, 00h, 00h
    db 00h, 00h, 8Bh, 46h, 08h, 85h, 0C0h, 0Fh, 84h, 0BAh, 00h, 00h, 00h, 6Ah, 00h, 51h
    db 89h, 64h, 24h, 14h, 8Bh, 0CCh, 68h, 54h, 06h, 08h, 01h, 0E8h, 10h, 0E2h, 35h, 00h
    db 8Bh, 4Eh, 04h, 8Bh, 01h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 50h, 04h
    db 8Bh, 0C8h, 0E8h, 06h, 1Eh, 0B0h, 0FFh, 6Ah, 01h, 51h, 89h, 64h, 24h, 14h, 8Bh, 0CCh
    db 68h, 70h, 0C7h, 07h, 01h, 8Ah, 0D8h, 0E8h, 0E4h, 0E1h, 35h, 00h, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 52h, 04h, 8Bh, 0C8h, 0E8h, 0DAh
    db 1Dh, 0B0h, 0FFh, 84h, 0C0h, 75h, 71h, 0F6h, 46h, 24h, 01h, 74h, 6Bh, 33h, 0C9h, 83h
    db 0C9h, 02h, 83h, 0C9h, 10h, 51h, 8Bh, 0CEh, 0E8h, 0FAh, 0D0h, 0AEh, 0FFh, 8Bh, 4Eh, 08h
    db 8Dh, 44h, 24h, 08h, 50h, 0E8h, 74h, 48h, 0B0h, 0FFh, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 1Ch, 02h, 00h, 00h, 00h, 0E8h, 7Fh, 86h, 0B1h, 0FFh, 8Dh, 4Ch, 24h, 08h, 0C7h, 44h
    db 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 05h, 0CFh, 35h, 00h, 8Bh, 8Eh, 08h, 01h, 00h
    db 00h, 85h, 0C9h, 0C6h, 46h, 12h, 01h, 74h, 0Eh, 84h, 0DBh, 74h, 0Ah, 68h, 30h, 47h
    db 92h, 00h, 0E8h, 0D0h, 26h, 0B1h, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Bh, 83h, 0C4h, 14h, 0C3h, 84h, 0C0h, 0B9h, 08h, 00h, 00h, 00h, 74h
    db 8Eh, 0B9h, 09h, 00h, 00h, 00h, 0EBh, 8Ah
?d_0052a940@@YAXXZ ENDP

; ghidra: FUN_0092aad0  retail @ 0x0052AAD0 size 443
public ?d_0052aad0@@YAXXZ
?d_0052aad0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0A8h, 07h, 03h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 0E8h, 0ACh, 57h, 0B0h, 0FFh
    db 84h, 0C0h, 74h, 0Ah, 8Bh, 44h, 24h, 20h, 33h, 0DBh, 3Bh, 0C3h, 75h, 17h, 32h, 0C0h
    db 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h
    db 0C4h, 0Ch, 0C2h, 08h, 00h, 89h, 46h, 08h, 8Bh, 44h, 24h, 24h, 8Bh, 0CEh, 0C6h, 46h
    db 16h, 01h, 89h, 5Eh, 0Ch, 89h, 46h, 24h, 0E8h, 9Fh, 0A5h, 0AFh, 0FFh, 8Bh, 0CEh, 0E8h
    db 45h, 0Ch, 0B0h, 0FFh, 8Bh, 4Eh, 04h, 8Bh, 11h, 0FFh, 52h, 30h, 88h, 44h, 24h, 20h
    db 8Bh, 6Ch, 24h, 20h, 0BFh, 07h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 57h, 8Bh, 0CEh, 0E8h, 0DDh, 0F0h, 0AFh, 0FFh, 57h, 8Bh, 0CEh, 0E8h, 91h, 06h, 0B1h, 0FFh
    db 57h, 8Bh, 0CEh, 0E8h, 22h, 28h, 0B0h, 0FFh, 53h, 57h, 8Bh, 0CEh, 0E8h, 20h, 3Fh, 0B0h
    db 0FFh, 8Bh, 4Ch, 0BEh, 68h, 55h, 0E8h, 80h, 0F6h, 0B1h, 0FFh, 8Bh, 8Ch, 0BEh, 88h, 00h
    db 00h, 00h, 53h, 0E8h, 73h, 0F6h, 0B1h, 0FFh, 8Bh, 8Ch, 0BEh, 0C8h, 00h, 00h, 00h, 53h
    db 0E8h, 66h, 0F6h, 0B1h, 0FFh, 8Bh, 8Ch, 0BEh, 0A8h, 00h, 00h, 00h, 53h, 0E8h, 59h, 0F6h
    db 0B1h, 0FFh, 8Bh, 8Ch, 0BEh, 0E8h, 00h, 00h, 00h, 3Bh, 0CBh, 74h, 1Fh, 3Bh, 0FBh, 74h
    db 09h, 6Ah, 01h, 0E8h, 72h, 0D3h, 0AFh, 0FFh, 0EBh, 12h, 0A1h, 0D8h, 0A0h, 2Bh, 01h, 8Bh
    db 8Eh, 0E8h, 00h, 00h, 00h, 50h, 53h, 0E8h, 0E4h, 0B6h, 0AFh, 0FFh, 8Bh, 4Ch, 0BEh, 68h
    db 0E8h, 91h, 52h, 0AEh, 0FFh, 8Bh, 8Ch, 0BEh, 88h, 00h, 00h, 00h, 0E8h, 85h, 52h, 0AEh
    db 0FFh, 8Bh, 8Ch, 0BEh, 0C8h, 00h, 00h, 00h, 0E8h, 79h, 52h, 0AEh, 0FFh, 8Bh, 8Ch, 0BEh
    db 0A8h, 00h, 00h, 00h, 0E8h, 6Dh, 52h, 0AEh, 0FFh, 4Fh, 0Fh, 89h, 50h, 0FFh, 0FFh, 0FFh
    db 8Bh, 0Dh, 94h, 15h, 2Fh, 01h, 3Bh, 0CBh, 74h, 05h, 0E8h, 0FDh, 0E2h, 0AEh, 0FFh, 38h
    db 5Ch, 24h, 20h, 74h, 07h, 8Bh, 0CEh, 0E8h, 0A8h, 0E5h, 0ADh, 0FFh, 8Dh, 4Ch, 24h, 20h
    db 51h, 8Bh, 4Eh, 08h, 0C6h, 46h, 61h, 01h, 0E8h, 61h, 46h, 0B0h, 0FFh, 50h, 8Bh, 0CEh
    db 89h, 5Ch, 24h, 1Ch, 0E8h, 7Dh, 4Ah, 0B1h, 0FFh, 8Dh, 4Ch, 24h, 20h, 0C7h, 44h, 24h
    db 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F6h, 0CCh, 35h, 00h, 6Ah, 01h, 0E8h, 9Eh, 99h, 0B0h
    db 0FFh, 8Bh, 4Ch, 24h, 14h, 83h, 0C4h, 04h, 5Fh, 88h, 5Eh, 16h, 88h, 5Eh, 11h, 89h
    db 9Eh, 28h, 01h, 00h, 00h, 0C6h, 46h, 15h, 01h, 0C6h, 46h, 10h, 01h, 0C6h, 46h, 12h
    db 01h, 0C6h, 46h, 13h, 01h, 0C6h, 46h, 14h, 01h, 5Eh, 5Dh, 0B0h, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_0052aad0@@YAXXZ ENDP

; ghidra: FUN_0092ad00  retail @ 0x0052AD00 size 123
public ?d_0052ad00@@YAXXZ
?d_0052ad00@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Ah, 4Eh, 16h, 32h, 0DBh, 32h, 0C0h, 3Ah, 0CBh, 74h, 03h, 5Eh
    db 5Bh, 0C3h, 38h, 5Eh, 11h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh, 11h, 0E8h, 0A3h, 0E4h, 0ADh
    db 0FFh, 0B0h, 01h, 38h, 5Eh, 14h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh, 14h, 0E8h, 1Bh, 4Ch
    db 0AEh, 0FFh, 0B0h, 01h, 38h, 5Eh, 15h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh, 15h, 0E8h, 0E2h
    db 82h, 0AEh, 0FFh, 0B0h, 01h, 38h, 5Eh, 10h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh, 10h, 0E8h
    db 13h, 95h, 0AFh, 0FFh, 0B0h, 01h, 38h, 5Eh, 12h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh, 12h
    db 0E8h, 51h, 0C9h, 0AEh, 0FFh, 0B0h, 01h, 38h, 5Eh, 13h, 74h, 0Ch, 8Bh, 0CEh, 88h, 5Eh
    db 13h, 0E8h, 06h, 0D1h, 0AEh, 0FFh, 0B0h, 01h, 5Eh, 5Bh, 0C3h
?d_0052ad00@@YAXXZ ENDP

; ghidra: FUN_0092ae20  retail @ 0x0052AE20 size 77
_TEXT ENDS
_TEXT$d0092ae20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0092AE20 size 77
public ?d_0052ae20@@YAXXZ
?d_0052ae20@@YAXXZ PROC
    db 08Bh, 00Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 085h, 0C9h, 055h, 08Bh, 06Ch, 024h, 008h, 075h, 005h, 083h, 0C8h, 0FFh, 05Dh, 0C3h, 053h, 056h
    call ?j_0002a62b@@YAXXZ
    db 08Bh, 0D8h, 033h, 0F6h, 057h, 03Bh, 0F3h, 07Dh, 01Ah, 08Bh, 00Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 08Bh, 0FEh, 057h, 046h
    call ?j_00039a77@@YAXXZ
    db 084h, 0C0h, 074h, 0E9h, 085h, 0EDh, 07Eh, 00Bh, 04Dh, 0EBh, 0E2h, 05Fh, 05Eh, 05Bh, 083h, 0C8h
    db 0FFh, 05Dh, 0C3h, 08Bh, 0C7h, 05Fh, 05Eh, 05Bh, 05Dh, 0C3h
?d_0052ae20@@YAXXZ ENDP
_TEXT$d0092ae20 ENDS
_TEXT SEGMENT

; ghidra: FUN_0092afe0  retail @ 0x0052AFE0 size 49
public ?d_0052afe0@@YAXXZ
?d_0052afe0@@YAXXZ PROC
    db 0A1h, 0E4h, 49h, 2Fh, 01h, 85h, 0C0h, 74h, 25h, 8Ah, 88h, 54h, 02h, 00h, 00h, 84h
    db 0C9h, 75h, 1Bh, 0B1h, 01h, 88h, 88h, 54h, 02h, 00h, 00h, 0A1h, 58h, 4Bh, 2Fh, 01h
    db 88h, 48h, 50h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h, 0E8h, 0C4h, 0E0h, 0AFh, 0FFh, 0C2h, 04h
    db 00h
?d_0052afe0@@YAXXZ ENDP

; ghidra: FUN_0092b2a0  retail @ 0x0052B2A0 size 323
public ?d_0052b2a0@@YAXXZ
?d_0052b2a0@@YAXXZ PROC
    db 51h, 0A1h, 0E4h, 49h, 2Fh, 01h, 85h, 0C0h, 56h, 0Fh, 85h, 31h, 01h, 00h, 00h, 8Bh
    db 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 0FFh, 90h, 54h, 01h, 00h, 00h, 84h, 0C0h, 0Fh
    db 85h, 1Bh, 01h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 2Ah, 97h, 0B0h, 0FFh
    db 84h, 0C0h, 0Fh, 85h, 08h, 01h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Ah, 41h
    db 69h, 84h, 0C0h, 0Fh, 85h, 0F7h, 00h, 00h, 00h, 8Bh, 15h, 6Ch, 07h, 2Fh, 01h, 8Bh
    db 82h, 80h, 70h, 01h, 00h, 85h, 0C0h, 0Fh, 8Dh, 0E3h, 00h, 00h, 00h, 8Bh, 0Dh, 30h
    db 33h, 2Fh, 01h, 0E8h, 67h, 7Bh, 0B1h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0D0h, 00h, 00h, 00h
    db 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 85h, 0C9h, 74h, 26h, 8Bh, 01h, 0FFh, 90h, 38h, 01h
    db 00h, 00h, 84h, 0C0h, 0Fh, 85h, 0B6h, 00h, 00h, 00h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h
    db 8Bh, 11h, 0FFh, 92h, 34h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 0A0h, 00h, 00h, 00h
    db 8Bh, 35h, 98h, 08h, 2Fh, 01h, 8Bh, 0CEh, 0E8h, 88h, 0AFh, 0ADh, 0FFh, 84h, 0C0h, 75h
    db 0Dh, 6Ah, 01h, 6Ah, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0F2h, 0BBh, 0ADh, 0FFh, 0A1h, 64h
    db 49h, 2Fh, 01h, 85h, 0C0h, 75h, 79h, 0E8h, 17h, 0E2h, 0AEh, 0FFh, 8Bh, 0Dh, 5Ch, 4Ch
    db 2Fh, 01h, 8Bh, 01h, 6Ah, 02h, 0FFh, 50h, 38h, 8Bh, 0Dh, 58h, 4Bh, 2Fh, 01h, 6Ah
    db 00h, 0E8h, 0E0h, 6Fh, 0B1h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 1Ah, 2Dh, 0AFh
    db 0FFh, 84h, 0C0h, 6Ah, 00h, 51h, 8Bh, 0CCh, 89h, 64h, 24h, 0Ch, 74h, 0Ch, 0BEh, 01h
    db 00h, 00h, 00h, 68h, 0D8h, 79h, 08h, 01h, 0EBh, 07h, 33h, 0F6h, 68h, 0ECh, 79h, 08h
    db 01h, 0E8h, 0Ah, 0D8h, 35h, 00h, 8Bh, 0Dh, 58h, 4Bh, 2Fh, 01h, 0E8h, 0E5h, 85h, 0B0h
    db 0FFh, 0A1h, 0E4h, 49h, 2Fh, 01h, 85h, 0C0h, 74h, 06h, 89h, 0B0h, 64h, 02h, 00h, 00h
    db 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 6Ah, 01h, 0FFh, 92h, 50h, 01h, 00h, 00h
    db 5Eh, 59h, 0C3h
?d_0052b2a0@@YAXXZ ENDP

; ghidra: FUN_0092b440  retail @ 0x0052B440 size 130
public ?d_0052b440@@YAXXZ
?d_0052b440@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0E8h, 00h, 56h, 8Bh, 74h, 24h, 0Ch, 0C6h, 06h, 30h, 0C6h
    db 46h, 01h, 00h, 74h, 39h, 48h, 75h, 66h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 75h, 5Eh
    db 0A1h, 98h, 08h, 2Fh, 01h, 85h, 0C0h, 74h, 0Eh, 83h, 0B8h, 0Ch, 01h, 00h, 00h, 02h
    db 0BAh, 0C0h, 0Fh, 08h, 01h, 74h, 05h, 0BAh, 38h, 12h, 08h, 01h, 8Bh, 0CEh, 8Bh, 0FFh
    db 8Ah, 02h, 42h, 88h, 01h, 41h, 84h, 0C0h, 75h, 0F6h, 5Eh, 0C2h, 0Ch, 00h, 8Ah, 44h
    db 24h, 10h, 84h, 0C0h, 75h, 28h, 83h, 0B9h, 64h, 02h, 00h, 00h, 01h, 75h, 1Fh, 8Bh
    db 81h, 5Ch, 02h, 00h, 00h, 2Bh, 81h, 58h, 02h, 00h, 00h, 0C1h, 0F8h, 02h, 50h, 68h
    db 0B4h, 0C7h, 07h, 01h, 56h, 0FFh, 15h, 8Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 5Eh, 0C2h
    db 0Ch, 00h
?d_0052b440@@YAXXZ ENDP

; ghidra: FUN_0092b4f0  retail @ 0x0052B4F0 size 52
public ?d_0052b4f0@@YAXXZ
?d_0052b4f0@@YAXXZ PROC
    db 83h, 7Ch, 24h, 04h, 15h, 75h, 12h, 0Fh, 0B6h, 44h, 24h, 08h, 48h, 74h, 0Fh, 83h
    db 0E8h, 0Eh, 74h, 0Ah, 83h, 0E8h, 0Dh, 74h, 05h, 33h, 0C0h, 0C2h, 0Ch, 00h, 0F6h, 44h
    db 24h, 0Ch, 01h, 74h, 07h, 6Ah, 00h, 0E8h, 31h, 6Fh, 0B0h, 0FFh, 0B8h, 01h, 00h, 00h
    db 00h, 0C2h, 0Ch, 00h
?d_0052b4f0@@YAXXZ ENDP
_TEXT ENDS
END
