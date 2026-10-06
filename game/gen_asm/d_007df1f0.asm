.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??_U@YAPAXI@Z:NEAR
EXTERN ??_V@YAXPAX@Z:NEAR
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva009A4D00Init@@YAXXZ:NEAR
EXTERN ?Rva009A5800Forward@@YAXHHH@Z:NEAR
EXTERN ?TheBfmeObject_00C70BC0@@3VGen_00C70BC0Target@@A:BYTE
EXTERN ?g_01309838@@3EA:BYTE
EXTERN ?g_rva001077D0RefreshDelay@@3MA:BYTE
EXTERN ?init@VideoPlayer@@UAEXXZ:NEAR
EXTERN ?j_000132af@@YAXXZ:NEAR
EXTERN ?j_0002eae1@@YAXXZ:NEAR
EXTERN ?j_00038163@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?store@Rva009A58C0@@SAXH@Z:NEAR
EXTERN __alldiv:NEAR
EXTERN __allmul:NEAR
EXTERN __ftol2:NEAR
EXTERN __imp__sprintf:BYTE
EXTERN __imp__timeGetTime@0:BYTE
EXTERN __real@3f99999a:BYTE
EXTERN g_Va010F6384:BYTE
EXTERN g_Va01128E24:BYTE
EXTERN g_Va01128E28:BYTE
EXTERN g_Va01128E2C:BYTE
EXTERN g_Va01128E30:BYTE
EXTERN g_Va01128E34:BYTE
EXTERN g_Va01128E36:BYTE
EXTERN g_Va01128E3C:BYTE
EXTERN g_Va01128E40:BYTE
EXTERN g_Va01128E44:BYTE
EXTERN g_Va01128E48:BYTE
EXTERN g_Va01128E4A:BYTE
EXTERN g_Va01128E50:BYTE
EXTERN g_Va01128E6C:BYTE
EXTERN g_Va01128E70:BYTE
EXTERN g_Va01128E74:BYTE
EXTERN g_Va01128E78:BYTE
EXTERN g_Va01128E80:BYTE
EXTERN g_Va01307438:BYTE
EXTERN g_Va01307838:BYTE
EXTERN g_Va01307C38:BYTE
EXTERN g_Va01308038:BYTE
EXTERN g_Va01308438:BYTE
EXTERN g_Va01308838:BYTE
EXTERN g_Va0130983C:BYTE
EXTERN g_Va01309840:BYTE
EXTERN g_Va01309848:BYTE
EXTERN g_Va01309849:BYTE
EXTERN g_Va0130994D:BYTE
EXTERN g_Va01309951:BYTE
EXTERN g_Va01309955:BYTE
EXTERN g_Va0130998D:BYTE
EXTERN g_Va0130998E:BYTE
EXTERN g_Va01309A92:BYTE
EXTERN g_Va01309A96:BYTE
EXTERN g_Va01309A9A:BYTE
EXTERN g_Va01309A9E:BYTE
EXTERN g_Va01309AA0:BYTE
EXTERN g_Va01309AD2:BYTE
EXTERN g_Va01309AD3:BYTE
EXTERN g_Va01309BD7:BYTE
EXTERN g_Va01309BDB:BYTE
EXTERN g_Va01309BDF:BYTE
EXTERN g_Va01309BE3:BYTE
EXTERN g_Va01309BE7:BYTE
EXTERN g_Va01309BE9:BYTE
_TEXT SEGMENT

; ghidra: FUN_00bdf1f0  retail @ 0x007DF1F0 size 9305
public ?d_007df1f0@@YAXXZ
?d_007df1f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 40h, 43h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 14h, 53h, 33h, 0DBh, 3Bh, 0C3h, 56h
    db 57h, 0Fh, 85h, 0EEh, 21h, 00h, 00h, 55h, 0E8h, 73h, 56h, 12h, 00h, 0A1h, 34h, 05h
    db 34h, 01h, 8Bh, 08h, 6Ah, 03h, 6Ah, 01h, 53h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h
    db 8Bh, 35h, 94h, 05h, 34h, 01h, 8Bh, 15h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h
    db 01h, 6Ah, 03h, 6Ah, 02h, 46h, 42h, 53h, 89h, 35h, 94h, 05h, 34h, 01h, 89h, 15h
    db 68h, 05h, 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 94h
    db 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 6Ah, 03h, 40h, 6Ah, 01h, 0A3h, 68h
    db 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h, 89h, 0Dh, 94h, 05h, 34h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 2Dh, 94h, 05h, 34h, 01h, 8Bh
    db 3Dh, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 02h, 45h, 47h
    db 6Ah, 01h, 89h, 2Dh, 94h, 05h, 34h, 01h, 89h, 3Dh, 68h, 05h, 34h, 01h, 8Bh, 10h
    db 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 35h, 94h, 05h, 34h, 01h, 8Bh, 15h, 68h
    db 05h, 34h, 01h, 46h, 42h, 53h, 89h, 35h, 94h, 05h, 34h, 01h, 89h, 15h, 68h, 05h
    db 34h, 01h, 0E8h, 0B2h, 90h, 85h, 0FFh, 6Ah, 01h, 0E8h, 0ABh, 90h, 85h, 0FFh, 8Dh, 44h
    db 24h, 2Ch, 53h, 50h, 0E8h, 04h, 0BBh, 83h, 0FFh, 83h, 0C4h, 10h, 8Bh, 35h, 34h, 05h
    db 34h, 01h, 8Bh, 3Eh, 8Bh, 0C8h, 89h, 5Ch, 24h, 1Ch, 0E8h, 61h, 0E9h, 12h, 00h, 50h
    db 53h, 56h, 0FFh, 97h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 24h, 83h, 0CFh, 0FFh, 3Bh
    db 0CBh, 89h, 7Ch, 24h, 1Ch, 74h, 05h, 0E8h, 84h, 0C4h, 20h, 00h, 8Dh, 4Ch, 24h, 24h
    db 6Ah, 01h, 51h, 0E8h, 0C5h, 0BAh, 83h, 0FFh, 83h, 0C4h, 08h, 8Bh, 35h, 34h, 05h, 34h
    db 01h, 8Bh, 2Eh, 8Bh, 0C8h, 0C7h, 44h, 24h, 1Ch, 01h, 00h, 00h, 00h, 0E8h, 1Eh, 0E9h
    db 12h, 00h, 50h, 6Ah, 01h, 56h, 0FFh, 95h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 24h
    db 3Bh, 0CBh, 89h, 7Ch, 24h, 1Ch, 74h, 05h, 0E8h, 43h, 0C4h, 20h, 00h, 0A1h, 0E4h, 0F9h
    db 33h, 01h, 0BEh, 04h, 00h, 00h, 00h, 3Bh, 0C6h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h
    db 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch
    db 89h, 54h, 24h, 2Ch, 0E8h, 07h, 0C5h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h
    db 0ECh, 34h, 01h, 88h, 08h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 01h, 52h, 0C7h, 44h, 24h
    db 28h, 02h, 00h, 00h, 00h, 0E8h, 36h, 7Ch, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h
    db 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0E6h, 0C3h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h
    db 6Ah, 01h, 53h, 89h, 35h, 0E4h, 0F9h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 0Ch, 0FAh, 33h, 01h
    db 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 80h, 0C4h, 1Fh, 00h
    db 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 53h, 8Dh, 54h, 24h
    db 28h, 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 28h, 03h, 00h, 00h, 00h, 0E8h, 0AFh, 7Bh, 12h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 5Fh, 0C3h, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 0Bh, 53h, 89h, 1Dh, 0Ch, 0FAh, 33h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h
    db 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 0A1h, 0E8h, 0F9h, 33h, 01h, 0BDh, 02h, 00h, 00h, 00h, 3Bh, 0C5h, 74h, 79h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 42h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0F3h, 0C3h, 1Fh, 00h, 8Bh, 44h, 24h
    db 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 55h, 8Dh, 54h, 24h, 28h, 55h, 52h
    db 89h, 74h, 24h, 28h, 0E8h, 27h, 7Bh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h
    db 89h, 7Ch, 24h, 1Ch, 0E8h, 0D7h, 0C2h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 55h, 55h
    db 53h, 89h, 2Dh, 0E8h, 0F9h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 0ECh, 0F9h, 33h, 01h, 74h, 7Fh
    db 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 72h, 0C3h, 1Fh, 00h, 8Bh, 44h
    db 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 53h, 8Dh, 54h, 24h, 28h, 6Ah
    db 03h, 52h, 0C7h, 44h, 24h, 28h, 05h, 00h, 00h, 00h, 0E8h, 0A1h, 7Ah, 12h, 00h, 83h
    db 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 51h, 0C2h, 1Fh, 00h, 0A1h
    db 34h, 05h, 34h, 01h, 53h, 6Ah, 03h, 53h, 89h, 1Dh, 0ECh, 0F9h, 33h, 01h, 8Bh, 08h
    db 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h
    db 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h
    db 35h, 0F0h, 0F9h, 33h, 01h, 74h, 7Dh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch
    db 0E8h, 0EBh, 0C2h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h
    db 08h, 56h, 8Dh, 54h, 24h, 28h, 56h, 52h, 0C7h, 44h, 24h, 28h, 06h, 00h, 00h, 00h
    db 0E8h, 1Bh, 7Ah, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch
    db 0E8h, 0CBh, 0C1h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 56h, 53h, 89h, 35h, 0F0h
    db 0F9h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 0A1h, 0F4h, 0F9h, 33h, 01h, 0BEh, 02h, 00h, 00h, 00h, 3Bh, 0C6h
    db 0BDh, 07h, 00h, 00h, 00h, 74h, 7Bh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 43h, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch
    db 0E8h, 5Bh, 0C2h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h
    db 08h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 05h, 52h, 89h, 6Ch, 24h, 28h, 0E8h, 8Eh, 79h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 3Eh, 0C1h
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 05h, 53h, 89h, 35h, 0F4h, 0F9h, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 39h, 1Dh, 0F8h, 0F9h, 33h, 01h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h
    db 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h
    db 54h, 24h, 2Ch, 0E8h, 0D8h, 0C1h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh
    db 34h, 01h, 88h, 08h, 53h, 8Dh, 54h, 24h, 28h, 6Ah, 06h, 52h, 0C7h, 44h, 24h, 28h
    db 08h, 00h, 00h, 00h, 0E8h, 07h, 79h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h
    db 89h, 7Ch, 24h, 1Ch, 0E8h, 0B7h, 0C0h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah
    db 06h, 53h, 89h, 1Dh, 0F8h, 0F9h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h
    db 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh
    db 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 2Dh, 64h, 0FAh, 33h, 01h, 0Fh
    db 84h, 80h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 4Dh
    db 0C1h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 55h
    db 8Dh, 54h, 24h, 28h, 6Ah, 01h, 52h, 0C7h, 44h, 24h, 28h, 09h, 00h, 00h, 00h, 0E8h
    db 7Ch, 78h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h
    db 2Ch, 0C0h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 55h, 6Ah, 01h, 6Ah, 01h, 89h, 2Dh
    db 64h, 0FAh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h
    db 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h
    db 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 8Ch, 0FAh, 33h, 01h, 01h, 0Fh, 84h, 86h, 00h
    db 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 48h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0C0h, 0C0h, 1Fh, 00h
    db 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 6Ah, 01h, 8Dh, 54h
    db 24h, 28h, 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 28h, 0Ah, 00h, 00h, 00h, 0E8h, 0EEh, 77h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 9Eh, 0BFh
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h, 6Ah, 0Bh, 6Ah, 01h, 0C7h, 05h, 8Ch
    db 0FAh, 33h, 01h, 01h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 68h, 0FAh, 33h, 01h, 0BEh, 30h, 00h
    db 00h, 00h, 3Bh, 0C6h, 0Fh, 84h, 80h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h
    db 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h
    db 54h, 24h, 2Ch, 0E8h, 28h, 0C0h, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh
    db 34h, 01h, 88h, 08h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 02h, 52h, 0C7h, 44h, 24h, 28h
    db 0Bh, 00h, 00h, 00h, 0E8h, 57h, 77h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h
    db 89h, 7Ch, 24h, 1Ch, 0E8h, 07h, 0BFh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah
    db 02h, 6Ah, 01h, 89h, 35h, 68h, 0FAh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 6Ch, 0FAh, 33h, 01h
    db 0Fh, 84h, 80h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h
    db 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h
    db 9Ch, 0BFh, 1Fh, 00h, 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h
    db 53h, 8Dh, 54h, 24h, 28h, 6Ah, 03h, 52h, 0C7h, 44h, 24h, 28h, 0Ch, 00h, 00h, 00h
    db 0E8h, 0CBh, 76h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch
    db 0E8h, 7Bh, 0BEh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 03h, 6Ah, 01h, 89h
    db 1Dh, 6Ch, 0FAh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 2Dh, 70h, 0FAh, 33h, 01h, 0Fh, 84h, 80h, 00h
    db 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 10h, 0BFh, 1Fh, 00h
    db 8Bh, 44h, 24h, 24h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h, 08h, 55h, 8Dh, 54h, 24h
    db 28h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 28h, 0Dh, 00h, 00h, 00h, 0E8h, 3Fh, 76h, 12h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0EFh, 0BDh, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 55h, 6Ah, 04h, 6Ah, 01h, 89h, 2Dh, 70h, 0FAh, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 0A1h, 74h, 0FAh, 33h, 01h, 0BDh, 13h, 00h, 00h, 00h, 3Bh, 0C5h, 74h, 7Fh
    db 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 82h, 0BEh, 1Fh, 00h, 0A0h, 0C8h
    db 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 55h, 8Dh, 54h, 24h, 28h, 6Ah, 05h
    db 52h, 0C7h, 44h, 24h, 28h, 0Eh, 00h, 00h, 00h, 0E8h, 0B2h, 75h, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 62h, 0BDh, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 55h, 6Ah, 05h, 6Ah, 01h, 89h, 2Dh, 74h, 0FAh, 33h, 01h, 8Bh, 08h
    db 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h
    db 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h
    db 78h, 0FAh, 33h, 01h, 0BEh, 03h, 00h, 00h, 00h, 3Bh, 0C6h, 74h, 7Fh, 38h, 1Dh, 51h
    db 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch
    db 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0F5h, 0BDh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h
    db 8Bh, 4Ch, 24h, 24h, 88h, 01h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 06h, 52h, 0C7h, 44h
    db 24h, 28h, 0Fh, 00h, 00h, 00h, 0E8h, 25h, 75h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch
    db 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0D5h, 0BCh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 56h, 6Ah, 06h, 6Ah, 01h, 89h, 35h, 78h, 0FAh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 80h, 0F4h, 33h
    db 01h, 3Bh, 0C3h, 74h, 3Bh, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0A1h, 34h, 05h, 34h, 01h
    db 53h, 0BEh, 02h, 00h, 00h, 00h, 56h, 89h, 1Dh, 80h, 0F4h, 33h, 01h, 8Bh, 08h, 50h
    db 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 60h, 05h, 34h
    db 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 60h, 05h, 34h, 01h, 0EBh, 05h
    db 0BEh, 02h, 00h, 00h, 00h, 83h, 3Dh, 0E4h, 0FAh, 33h, 01h, 04h, 0Fh, 84h, 84h, 00h
    db 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 20h, 0BDh, 1Fh, 00h
    db 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 04h, 8Dh, 54h, 24h
    db 28h, 6Ah, 01h, 52h, 0C7h, 44h, 24h, 28h, 10h, 00h, 00h, 00h, 0E8h, 4Fh, 74h, 12h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0FFh, 0BBh, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h, 6Ah, 01h, 56h, 0C7h, 05h, 0E4h, 0FAh, 33h
    db 01h, 04h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 35h, 0Ch, 0FBh, 33h, 01h, 74h, 7Eh, 38h, 1Dh
    db 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh
    db 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 94h, 0BCh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h
    db 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 0Bh, 52h, 0C7h
    db 44h, 24h, 28h, 11h, 00h, 00h, 00h, 0E8h, 0C4h, 73h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 74h, 0BBh, 1Fh, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 56h, 6Ah, 0Bh, 56h, 89h, 35h, 0Ch, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 35h, 0E8h, 0FAh
    db 33h, 01h, 74h, 7Ch, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 45h, 8Bh, 15h, 24h, 91h
    db 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0Eh, 0BCh
    db 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 56h, 8Dh, 54h
    db 24h, 28h, 56h, 52h, 0C7h, 44h, 24h, 28h, 12h, 00h, 00h, 00h, 0E8h, 3Fh, 73h, 12h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0EFh, 0BAh, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 56h, 56h, 89h, 35h, 0E8h, 0FAh, 33h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 39h, 35h, 0ECh, 0FAh, 33h, 01h, 74h, 7Ah, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 42h
    db 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h
    db 2Ch, 0E8h, 8Ah, 0BBh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h
    db 01h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 03h, 52h, 89h, 6Ch, 24h, 28h, 0E8h, 0BEh, 72h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 6Eh, 0BAh
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 03h, 56h, 89h, 35h, 0ECh, 0FAh, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 83h, 3Dh, 0F0h, 0FAh, 33h, 01h, 04h, 0Fh, 84h, 84h, 00h, 00h, 00h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 03h, 0BBh, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 04h, 8Dh, 54h, 24h, 28h, 6Ah, 04h
    db 52h, 0C7h, 44h, 24h, 28h, 14h, 00h, 00h, 00h, 0E8h, 32h, 72h, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0E2h, 0B9h, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 04h, 6Ah, 04h, 56h, 0C7h, 05h, 0F0h, 0FAh, 33h, 01h, 04h, 00h
    db 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h
    db 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h
    db 05h, 34h, 01h, 83h, 3Dh, 0F4h, 0FAh, 33h, 01h, 03h, 0Fh, 84h, 84h, 00h, 00h, 00h
    db 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 72h, 0BAh, 1Fh, 00h, 0A0h, 0C8h
    db 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 28h, 6Ah
    db 05h, 52h, 0C7h, 44h, 24h, 28h, 15h, 00h, 00h, 00h, 0E8h, 0A1h, 71h, 12h, 00h, 83h
    db 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 51h, 0B9h, 1Fh, 00h, 0A1h
    db 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 05h, 56h, 0C7h, 05h, 0F4h, 0FAh, 33h, 01h, 03h
    db 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 83h, 3Dh, 0F8h, 0FAh, 33h, 01h, 03h, 0Fh, 84h, 84h, 00h, 00h
    db 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0E1h, 0B9h, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 28h
    db 6Ah, 06h, 52h, 0C7h, 44h, 24h, 28h, 16h, 00h, 00h, 00h, 0E8h, 10h, 71h, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0C0h, 0B8h, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 06h, 56h, 0C7h, 05h, 0F8h, 0FAh, 33h, 01h
    db 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h
    db 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h
    db 0A3h, 68h, 05h, 34h, 01h, 0A1h, 84h, 0F4h, 33h, 01h, 3Bh, 0C3h, 74h, 35h, 8Bh, 10h
    db 50h, 0FFh, 52h, 08h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 03h, 89h, 1Dh, 84h, 0F4h
    db 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h
    db 01h, 0A1h, 60h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 60h
    db 05h, 34h, 01h, 39h, 35h, 64h, 0FBh, 33h, 01h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h
    db 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch
    db 89h, 54h, 24h, 2Ch, 0E8h, 17h, 0B9h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch
    db 24h, 24h, 88h, 01h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 01h, 52h, 0C7h, 44h, 24h, 28h
    db 17h, 00h, 00h, 00h, 0E8h, 47h, 70h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h
    db 89h, 7Ch, 24h, 1Ch, 0E8h, 0F7h, 0B7h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah
    db 01h, 6Ah, 03h, 89h, 35h, 64h, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 8Ch, 0FBh, 33h, 01h
    db 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch
    db 0E8h, 8Bh, 0B8h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h
    db 6Ah, 03h, 8Dh, 54h, 24h, 28h, 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 28h, 18h, 00h, 00h
    db 00h, 0E8h, 0BAh, 6Fh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h
    db 1Ch, 0E8h, 6Ah, 0B7h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 0Bh, 6Ah
    db 03h, 0C7h, 05h, 8Ch, 0FBh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 68h, 0FBh, 33h
    db 01h, 0BEh, 20h, 00h, 00h, 00h, 3Bh, 0C6h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h
    db 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h
    db 54h, 24h, 2Ch, 0E8h, 0F8h, 0B7h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h
    db 24h, 88h, 01h, 56h, 8Dh, 54h, 24h, 28h, 6Ah, 02h, 52h, 0C7h, 44h, 24h, 28h, 19h
    db 00h, 00h, 00h, 0E8h, 28h, 6Fh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h
    db 7Ch, 24h, 1Ch, 0E8h, 0D8h, 0B6h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 02h
    db 6Ah, 03h, 89h, 35h, 68h, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h
    db 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh
    db 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 6Ch, 0FBh, 33h, 01h, 74h
    db 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 71h, 0B7h, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 53h, 8Dh, 54h, 24h, 28h, 6Ah
    db 03h, 52h, 0C7h, 44h, 24h, 28h, 1Ah, 00h, 00h, 00h, 0E8h, 0A1h, 6Eh, 12h, 00h, 83h
    db 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 51h, 0B6h, 1Fh, 00h, 0A1h
    db 34h, 05h, 34h, 01h, 53h, 6Ah, 03h, 6Ah, 03h, 89h, 1Dh, 6Ch, 0FBh, 33h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 83h, 3Dh, 70h, 0FBh, 33h, 01h, 02h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h
    db 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch
    db 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0E5h, 0B6h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h
    db 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 02h, 8Dh, 54h, 24h, 28h, 6Ah, 04h, 52h, 0C7h
    db 44h, 24h, 28h, 1Bh, 00h, 00h, 00h, 0E8h, 14h, 6Eh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0C4h, 0B5h, 1Fh, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 6Ah, 02h, 6Ah, 04h, 6Ah, 03h, 0C7h, 05h, 70h, 0FBh, 33h, 01h, 02h, 00h, 00h
    db 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 83h, 3Dh, 74h, 0FBh, 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 53h, 0B6h, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 28h, 6Ah, 05h
    db 52h, 0C7h, 44h, 24h, 28h, 1Ch, 00h, 00h, 00h, 0E8h, 82h, 6Dh, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 32h, 0B5h, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 03h, 6Ah, 05h, 6Ah, 03h, 0C7h, 05h, 74h, 0FBh, 33h, 01h, 03h
    db 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 83h, 3Dh, 78h, 0FBh, 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h
    db 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0C1h, 0B5h, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 28h
    db 6Ah, 06h, 52h, 0C7h, 44h, 24h, 28h, 1Dh, 00h, 00h, 00h, 0E8h, 0F0h, 6Ch, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0A0h, 0B4h, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 06h, 6Ah, 03h, 0C7h, 05h, 78h, 0FBh, 33h
    db 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 88h, 0F4h, 33h, 01h, 3Bh, 0C3h, 74h, 35h, 8Bh
    db 10h, 50h, 0FFh, 52h, 08h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 04h, 89h, 1Dh, 88h
    db 0F4h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 60h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 60h, 05h, 34h, 01h, 83h, 3Dh, 0E4h, 0FBh, 33h, 01h, 04h, 0Fh, 84h, 85h, 00h, 00h
    db 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0F1h, 0B4h, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 04h, 8Dh, 54h, 24h, 28h
    db 6Ah, 01h, 52h, 0C7h, 44h, 24h, 28h, 1Eh, 00h, 00h, 00h, 0E8h, 20h, 6Ch, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0D0h, 0B3h, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h, 6Ah, 01h, 6Ah, 04h, 0C7h, 05h, 0E4h, 0FBh, 33h
    db 01h, 04h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0Ch, 0FCh, 33h, 01h, 04h, 0Fh, 84h, 85h
    db 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh
    db 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 5Fh, 0B4h, 1Fh
    db 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 04h, 8Dh, 54h
    db 24h, 28h, 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 28h, 1Fh, 00h, 00h, 00h, 0E8h, 8Eh, 6Bh
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 3Eh, 0B3h
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h, 6Ah, 0Bh, 6Ah, 04h, 0C7h, 05h, 0Ch
    db 0FCh, 33h, 01h, 04h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0E8h, 0FBh, 33h, 01h, 01h, 0Fh
    db 84h, 81h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 43h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0CDh
    db 0B3h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 01h
    db 8Dh, 54h, 24h, 28h, 6Ah, 02h, 52h, 89h, 74h, 24h, 28h, 0E8h, 00h, 6Bh, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0B0h, 0B2h, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h, 6Ah, 02h, 6Ah, 04h, 0C7h, 05h, 0E8h, 0FBh, 33h
    db 01h, 01h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 0ECh, 0FBh, 33h, 01h, 74h, 7Fh, 38h, 1Dh
    db 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh
    db 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 44h, 0B3h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h
    db 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 53h, 8Dh, 54h, 24h, 28h, 6Ah, 03h, 52h, 0C7h
    db 44h, 24h, 28h, 21h, 00h, 00h, 00h, 0E8h, 74h, 6Ah, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 24h, 0B2h, 1Fh, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 53h, 6Ah, 03h, 6Ah, 04h, 89h, 1Dh, 0ECh, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh
    db 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h
    db 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0F0h
    db 0FBh, 33h, 01h, 04h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h
    db 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h
    db 54h, 24h, 2Ch, 0E8h, 0B8h, 0B2h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h
    db 24h, 88h, 01h, 6Ah, 04h, 8Dh, 54h, 24h, 28h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 28h
    db 22h, 00h, 00h, 00h, 0E8h, 0E7h, 69h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h
    db 89h, 7Ch, 24h, 1Ch, 0E8h, 97h, 0B1h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h
    db 6Ah, 04h, 6Ah, 04h, 0C7h, 05h, 0F0h, 0FBh, 33h, 01h, 04h, 00h, 00h, 00h, 8Bh, 08h
    db 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h
    db 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h
    db 3Dh, 0F4h, 0FBh, 33h, 01h, 01h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h
    db 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h
    db 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 26h, 0B2h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh
    db 4Ch, 24h, 24h, 88h, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 28h, 6Ah, 05h, 52h, 0C7h, 44h
    db 24h, 28h, 23h, 00h, 00h, 00h, 0E8h, 55h, 69h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch
    db 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 05h, 0B1h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 6Ah, 01h, 6Ah, 05h, 6Ah, 04h, 0C7h, 05h, 0F4h, 0FBh, 33h, 01h, 01h, 00h, 00h, 00h
    db 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h
    db 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 39h, 1Dh, 0F8h, 0FBh, 33h, 01h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h
    db 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h
    db 24h, 2Ch, 0E8h, 99h, 0B1h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h
    db 88h, 01h, 53h, 8Dh, 54h, 24h, 28h, 6Ah, 06h, 52h, 0C7h, 44h, 24h, 28h, 24h, 00h
    db 00h, 00h, 0E8h, 0C9h, 68h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch
    db 24h, 1Ch, 0E8h, 79h, 0B0h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 06h, 6Ah
    db 04h, 89h, 1Dh, 0F8h, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 8Ch, 0F4h, 33h, 01h, 3Bh, 0C3h, 74h
    db 35h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 05h, 89h
    db 1Dh, 8Ch, 0F4h, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 60h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 60h, 05h, 34h, 01h, 83h, 3Dh, 64h, 0FCh, 33h, 01h, 07h, 0Fh, 84h, 85h
    db 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh
    db 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0CFh, 0B0h, 1Fh
    db 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 07h, 8Dh, 54h
    db 24h, 28h, 6Ah, 01h, 52h, 0C7h, 44h, 24h, 28h, 25h, 00h, 00h, 00h, 0E8h, 0FEh, 67h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0AEh, 0AFh
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 07h, 6Ah, 01h, 6Ah, 05h, 0C7h, 05h, 64h
    db 0FCh, 33h, 01h, 07h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 8Ch, 0FCh, 33h, 01h, 05h, 0Fh
    db 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 3Dh
    db 0B0h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 05h
    db 8Dh, 54h, 24h, 28h, 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 28h, 26h, 00h, 00h, 00h, 0E8h
    db 6Ch, 67h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h
    db 1Ch, 0AFh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 05h, 6Ah, 0Bh, 6Ah, 05h, 0C7h
    db 05h, 8Ch, 0FCh, 33h, 01h, 05h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 68h, 0FCh, 33h, 01h
    db 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 0B0h, 0AFh, 1Fh, 00h
    db 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 53h, 8Dh, 54h, 24h, 28h
    db 6Ah, 02h, 52h, 0C7h, 44h, 24h, 28h, 27h, 00h, 00h, 00h, 0E8h, 0E0h, 66h, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 90h, 0AEh, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 02h, 6Ah, 05h, 89h, 1Dh, 68h, 0FCh, 33h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h
    db 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 39h, 1Dh, 6Ch, 0FCh, 33h, 01h, 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h
    db 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h
    db 24h, 2Ch, 0E8h, 29h, 0AFh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h
    db 88h, 01h, 53h, 8Dh, 54h, 24h, 28h, 6Ah, 03h, 52h, 0C7h, 44h, 24h, 28h, 28h, 00h
    db 00h, 00h, 0E8h, 59h, 66h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch
    db 24h, 1Ch, 0E8h, 09h, 0AEh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 03h, 6Ah
    db 05h, 89h, 1Dh, 6Ch, 0FCh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 70h, 0FCh, 33h, 01h, 07h, 0Fh
    db 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 9Dh
    db 0AEh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 6Ah, 07h
    db 8Dh, 54h, 24h, 28h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 28h, 29h, 00h, 00h, 00h, 0E8h
    db 0CCh, 65h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h
    db 7Ch, 0ADh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 07h, 6Ah, 04h, 6Ah, 05h, 0C7h
    db 05h, 70h, 0FCh, 33h, 01h, 07h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 2Dh, 74h, 0FCh, 33h, 01h
    db 74h, 7Fh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 46h, 8Bh, 15h, 24h, 91h, 2Dh, 01h
    db 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 2Ch, 0E8h, 10h, 0AEh, 1Fh, 00h
    db 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 24h, 88h, 01h, 55h, 8Dh, 54h, 24h, 28h
    db 6Ah, 05h, 52h, 0C7h, 44h, 24h, 28h, 2Ah, 00h, 00h, 00h, 0E8h, 40h, 65h, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 24h, 89h, 7Ch, 24h, 1Ch, 0E8h, 0F0h, 0ACh, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 55h, 6Ah, 05h, 6Ah, 05h, 89h, 2Dh, 74h, 0FCh, 33h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h
    db 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 83h, 3Dh, 78h, 0FCh, 33h, 01h, 03h, 5Dh, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 83h, 0ADh, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 24h, 6Ah, 06h
    db 52h, 0C7h, 44h, 24h, 24h, 2Bh, 00h, 00h, 00h, 0E8h, 0B2h, 64h, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 62h, 0ACh, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 03h, 6Ah, 06h, 6Ah, 05h, 0C7h, 05h, 78h, 0FCh, 33h, 01h, 03h
    db 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 0A1h, 90h, 0F4h, 33h, 01h, 3Bh, 0C3h, 74h, 35h, 8Bh, 10h, 50h
    db 0FFh, 52h, 08h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 06h, 89h, 1Dh, 90h, 0F4h, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 60h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 60h, 05h
    db 34h, 01h, 83h, 3Dh, 0E4h, 0FCh, 33h, 01h, 04h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 0B3h, 0ACh, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 04h, 8Dh, 54h, 24h, 24h, 6Ah, 01h
    db 52h, 0C7h, 44h, 24h, 24h, 2Ch, 00h, 00h, 00h, 0E8h, 0E2h, 63h, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 92h, 0ABh, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 04h, 6Ah, 01h, 6Ah, 06h, 0C7h, 05h, 0E4h, 0FCh, 33h, 01h, 04h
    db 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 83h, 3Dh, 0Ch, 0FDh, 33h, 01h, 06h, 0Fh, 84h, 85h, 00h, 00h
    db 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 21h, 0ACh, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 06h, 8Dh, 54h, 24h, 24h
    db 6Ah, 0Bh, 52h, 0C7h, 44h, 24h, 24h, 2Dh, 00h, 00h, 00h, 0E8h, 50h, 63h, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 00h, 0ABh, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 06h, 6Ah, 0Bh, 6Ah, 06h, 0C7h, 05h, 0Ch, 0FDh, 33h
    db 01h, 06h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0E8h, 0FCh, 33h, 01h, 03h, 0Fh, 84h, 85h
    db 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh
    db 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 8Fh, 0ABh, 1Fh
    db 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h, 8Dh, 54h
    db 24h, 24h, 6Ah, 02h, 52h, 0C7h, 44h, 24h, 24h, 2Eh, 00h, 00h, 00h, 0E8h, 0BEh, 62h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 6Eh, 0AAh
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 02h, 6Ah, 06h, 0C7h, 05h, 0E8h
    db 0FCh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0ECh, 0FCh, 33h, 01h, 03h, 0Fh
    db 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 0FDh
    db 0AAh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h
    db 8Dh, 54h, 24h, 24h, 6Ah, 03h, 52h, 0C7h, 44h, 24h, 24h, 2Fh, 00h, 00h, 00h, 0E8h
    db 2Ch, 62h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h
    db 0DCh, 0A9h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 03h, 6Ah, 06h, 0C7h
    db 05h, 0ECh, 0FCh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0F0h, 0FCh, 33h, 01h
    db 04h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h
    db 0E8h, 6Bh, 0AAh, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h
    db 6Ah, 04h, 8Dh, 54h, 24h, 24h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 24h, 30h, 00h, 00h
    db 00h, 0E8h, 9Ah, 61h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h
    db 18h, 0E8h, 4Ah, 0A9h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h, 6Ah, 04h, 6Ah
    db 06h, 0C7h, 05h, 0F0h, 0FCh, 33h, 01h, 04h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 0F4h, 0FCh
    db 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h
    db 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h
    db 24h, 28h, 0E8h, 0D9h, 0A9h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h
    db 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 24h, 6Ah, 05h, 52h, 0C7h, 44h, 24h, 24h, 31h
    db 00h, 00h, 00h, 0E8h, 08h, 61h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h
    db 7Ch, 24h, 18h, 0E8h, 0B8h, 0A8h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah
    db 05h, 6Ah, 06h, 0C7h, 05h, 0F4h, 0FCh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h
    db 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h
    db 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh
    db 0F8h, 0FCh, 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h
    db 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h
    db 89h, 54h, 24h, 28h, 0E8h, 47h, 0A9h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch
    db 24h, 20h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 24h, 6Ah, 06h, 52h, 0C7h, 44h, 24h
    db 24h, 32h, 00h, 00h, 00h, 0E8h, 76h, 60h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h
    db 20h, 89h, 7Ch, 24h, 18h, 0E8h, 26h, 0A8h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah
    db 03h, 6Ah, 06h, 6Ah, 06h, 0C7h, 05h, 0F8h, 0FCh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 0A1h, 94h, 0F4h, 33h, 01h, 3Bh, 0C3h, 74h, 35h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0A1h
    db 34h, 05h, 34h, 01h, 53h, 6Ah, 07h, 89h, 1Dh, 94h, 0F4h, 33h, 01h, 8Bh, 08h, 50h
    db 0FFh, 91h, 04h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 60h, 05h, 34h
    db 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 60h, 05h, 34h, 01h, 83h, 3Dh
    db 64h, 0FDh, 33h, 01h, 02h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h
    db 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h
    db 89h, 54h, 24h, 28h, 0E8h, 77h, 0A8h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch
    db 24h, 20h, 88h, 01h, 6Ah, 02h, 8Dh, 54h, 24h, 24h, 6Ah, 01h, 52h, 0C7h, 44h, 24h
    db 24h, 33h, 00h, 00h, 00h, 0E8h, 0A6h, 5Fh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h
    db 20h, 89h, 7Ch, 24h, 18h, 0E8h, 56h, 0A7h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah
    db 02h, 6Ah, 01h, 6Ah, 07h, 0C7h, 05h, 64h, 0FDh, 33h, 01h, 02h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 83h, 3Dh, 8Ch, 0FDh, 33h, 01h, 07h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h
    db 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch
    db 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 0E5h, 0A7h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h
    db 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 07h, 8Dh, 54h, 24h, 24h, 6Ah, 0Bh, 52h, 0C7h
    db 44h, 24h, 24h, 34h, 00h, 00h, 00h, 0E8h, 14h, 5Fh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 0C4h, 0A6h, 1Fh, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 6Ah, 07h, 6Ah, 0Bh, 6Ah, 07h, 0C7h, 05h, 8Ch, 0FDh, 33h, 01h, 07h, 00h, 00h
    db 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 83h, 3Dh, 68h, 0FDh, 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h
    db 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h
    db 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 53h, 0A7h, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 24h, 6Ah, 02h
    db 52h, 0C7h, 44h, 24h, 24h, 35h, 00h, 00h, 00h, 0E8h, 82h, 5Eh, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 32h, 0A6h, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 03h, 6Ah, 02h, 6Ah, 07h, 0C7h, 05h, 68h, 0FDh, 33h, 01h, 03h
    db 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h
    db 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h
    db 68h, 05h, 34h, 01h, 83h, 3Dh, 6Ch, 0FDh, 33h, 01h, 03h, 0Fh, 84h, 85h, 00h, 00h
    db 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah
    db 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 0C1h, 0A6h, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h, 8Dh, 54h, 24h, 24h
    db 6Ah, 03h, 52h, 0C7h, 44h, 24h, 24h, 36h, 00h, 00h, 00h, 0E8h, 0F0h, 5Dh, 12h, 00h
    db 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 0A0h, 0A5h, 1Fh, 00h
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 03h, 6Ah, 07h, 0C7h, 05h, 6Ch, 0FDh, 33h
    db 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 70h, 0FDh, 33h, 01h, 02h, 0Fh, 84h, 85h
    db 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h, 91h, 2Dh
    db 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 2Fh, 0A6h, 1Fh
    db 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 02h, 8Dh, 54h
    db 24h, 24h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 24h, 37h, 00h, 00h, 00h, 0E8h, 5Eh, 5Dh
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 0Eh, 0A5h
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 02h, 6Ah, 04h, 6Ah, 07h, 0C7h, 05h, 70h
    db 0FDh, 33h, 01h, 02h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 74h, 0FDh, 33h, 01h, 03h, 0Fh
    db 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh, 15h, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 9Dh
    db 0A5h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 6Ah, 03h
    db 8Dh, 54h, 24h, 24h, 6Ah, 05h, 52h, 0C7h, 44h, 24h, 24h, 38h, 00h, 00h, 00h, 0E8h
    db 0CCh, 5Ch, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h
    db 7Ch, 0A4h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 05h, 6Ah, 07h, 0C7h
    db 05h, 74h, 0FDh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 3Dh, 78h, 0FDh, 33h, 01h
    db 03h, 0Fh, 84h, 85h, 00h, 00h, 00h, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 47h, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h
    db 0E8h, 0Bh, 0A5h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h
    db 6Ah, 03h, 8Dh, 54h, 24h, 24h, 6Ah, 06h, 52h, 0C7h, 44h, 24h, 24h, 39h, 00h, 00h
    db 00h, 0E8h, 3Ah, 5Ch, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h
    db 18h, 0E8h, 0EAh, 0A3h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 06h, 6Ah
    db 07h, 0C7h, 05h, 78h, 0FDh, 33h, 01h, 03h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 5Fh, 5Eh, 0B8h, 01h
    db 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C2h, 04h, 00h, 0A1h, 0E4h, 0FAh, 33h, 01h, 0BEh, 01h, 00h, 00h, 00h, 83h
    db 0CFh, 0FFh, 3Bh, 0C6h, 74h, 7Ch, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 44h, 8Bh, 15h
    db 24h, 91h, 2Dh, 01h, 56h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 5Dh
    db 0A4h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 56h, 8Dh
    db 54h, 24h, 24h, 56h, 52h, 0C7h, 44h, 24h, 24h, 3Ah, 00h, 00h, 00h, 0E8h, 8Eh, 5Bh
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 3Eh, 0A3h
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 56h, 6Ah, 02h, 89h, 35h, 0E4h, 0FAh, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 39h, 35h, 0F0h, 0FAh, 33h, 01h, 74h, 7Eh, 38h, 1Dh, 51h, 0F4h, 33h, 01h
    db 74h, 45h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 56h, 53h, 8Dh, 4Ch, 24h, 28h, 89h, 54h
    db 24h, 28h, 0E8h, 0D9h, 0A3h, 1Fh, 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 20h
    db 88h, 01h, 56h, 8Dh, 54h, 24h, 24h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 24h, 3Bh, 00h
    db 00h, 00h, 0E8h, 09h, 5Bh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 20h, 89h, 7Ch
    db 24h, 18h, 0E8h, 0B9h, 0A2h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 04h, 6Ah
    db 02h, 89h, 35h, 0F0h, 0FAh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 35h, 64h, 0FBh, 33h, 01h, 74h, 7Ch
    db 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 44h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 56h, 53h
    db 8Dh, 4Ch, 24h, 28h, 89h, 54h, 24h, 28h, 0E8h, 53h, 0A3h, 1Fh, 00h, 0A0h, 0C8h, 0ECh
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 88h, 01h, 56h, 8Dh, 54h, 24h, 24h, 56h, 52h, 0C7h
    db 44h, 24h, 24h, 3Ch, 00h, 00h, 00h, 0E8h, 84h, 5Ah, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 20h, 89h, 7Ch, 24h, 18h, 0E8h, 34h, 0A2h, 1Fh, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 56h, 56h, 6Ah, 03h, 89h, 35h, 64h, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 35h, 70h, 0FBh
    db 33h, 01h, 74h, 7Eh, 38h, 1Dh, 51h, 0F4h, 33h, 01h, 74h, 45h, 8Bh, 15h, 24h, 91h
    db 2Dh, 01h, 56h, 53h, 8Dh, 4Ch, 24h, 14h, 89h, 54h, 24h, 14h, 0E8h, 0CFh, 0A2h, 1Fh
    db 00h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 0Ch, 88h, 01h, 56h, 8Dh, 54h, 24h
    db 10h, 6Ah, 04h, 52h, 0C7h, 44h, 24h, 24h, 3Dh, 00h, 00h, 00h, 0E8h, 0FFh, 59h, 12h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 0Ch, 89h, 7Ch, 24h, 18h, 0E8h, 0AFh, 0A1h, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 04h, 6Ah, 03h, 89h, 35h, 70h, 0FBh, 33h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h
    db 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h
    db 34h, 01h, 0E8h, 29h, 26h, 12h, 00h, 6Ah, 02h, 0B9h, 0E8h, 0C2h, 2Bh, 01h, 0E8h, 0EFh
    db 0A6h, 85h, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_007df1f0@@YAXXZ ENDP

; ghidra: FUN_00be2110  retail @ 0x007E2110 size 70
public ?d_007e2110@@YAXXZ
?d_007e2110@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h
    db 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 8Bh, 46h, 10h
    db 85h, 0C0h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 0C7h, 46h, 08h, 00h, 00h, 00h
    db 00h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 0B8h
    db 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_007e2110@@YAXXZ ENDP

; ghidra: FUN_00be2180  retail @ 0x007E2180 size 2531
public ?d_007e2180@@YAXXZ
?d_007e2180@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 54h, 44h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0A0h, 00h, 00h, 00h, 53h, 55h, 56h, 57h, 89h
    db 4Ch, 24h, 14h, 0E8h, 0E8h, 26h, 12h, 00h, 8Dh, 44h, 24h, 10h, 6Ah, 00h, 50h, 0E8h
    db 39h, 8Ch, 83h, 0FFh, 83h, 0C4h, 08h, 8Bh, 35h, 34h, 05h, 34h, 01h, 8Bh, 3Eh, 8Bh
    db 0C8h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 8Fh, 0BAh, 12h
    db 00h, 50h, 6Ah, 00h, 56h, 0FFh, 97h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 83h
    db 0CFh, 0FFh, 85h, 0C9h, 89h, 0BCh, 24h, 0B8h, 00h, 00h, 00h, 74h, 05h, 0E8h, 0AEh, 95h
    db 20h, 00h, 0BDh, 01h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 10h, 55h, 51h, 0E8h, 0EBh, 8Bh
    db 83h, 0FFh, 83h, 0C4h, 08h, 8Bh, 35h, 34h, 05h, 34h, 01h, 8Bh, 1Eh, 8Bh, 0C8h, 89h
    db 0ACh, 24h, 0B8h, 00h, 00h, 00h, 0E8h, 45h, 0BAh, 12h, 00h, 50h, 55h, 56h, 0FFh, 93h
    db 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h, 89h, 0BCh, 24h, 0B8h, 00h, 00h
    db 00h, 74h, 05h, 0E8h, 68h, 95h, 20h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah
    db 03h, 55h, 6Ah, 00h, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 0A1h, 94h, 05h, 34h, 01h
    db 8Bh, 1Dh, 68h, 05h, 34h, 01h, 40h, 43h, 89h, 1Dh, 68h, 05h, 34h, 01h, 6Ah, 03h
    db 0BBh, 02h, 00h, 00h, 00h, 53h, 0A3h, 94h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h
    db 8Bh, 08h, 6Ah, 00h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h
    db 01h, 0A1h, 68h, 05h, 34h, 01h, 6Ah, 03h, 41h, 40h, 55h, 0A3h, 68h, 05h, 34h, 01h
    db 0A1h, 34h, 05h, 34h, 01h, 55h, 89h, 0Dh, 94h, 05h, 34h, 01h, 8Bh, 10h, 50h, 0FFh
    db 92h, 14h, 01h, 00h, 00h, 0A1h, 94h, 05h, 34h, 01h, 8Bh, 35h, 68h, 05h, 34h, 01h
    db 6Ah, 03h, 40h, 53h, 0A3h, 94h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 46h, 55h
    db 89h, 35h, 68h, 05h, 34h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh
    db 15h, 94h, 05h, 34h, 01h, 8Bh, 0Dh, 68h, 05h, 34h, 01h, 0A1h, 0Ch, 0FAh, 33h, 01h
    db 42h, 41h, 85h, 0C0h, 89h, 15h, 94h, 05h, 34h, 01h, 89h, 0Dh, 68h, 05h, 34h, 01h
    db 0Fh, 84h, 89h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Ah, 8Bh
    db 15h, 24h, 91h, 2Dh, 01h, 55h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 54h, 24h, 18h
    db 0E8h, 7Bh, 95h, 1Fh, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 0Dh, 0C8h, 0ECh, 34h, 01h, 88h
    db 08h, 6Ah, 00h, 8Dh, 54h, 24h, 14h, 6Ah, 0Bh, 52h, 89h, 9Ch, 24h, 0C4h, 00h, 00h
    db 00h, 0E8h, 0AAh, 4Ch, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 0BCh, 24h
    db 0B8h, 00h, 00h, 00h, 0E8h, 57h, 94h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 00h
    db 6Ah, 0Bh, 6Ah, 00h, 0C7h, 05h, 0Ch, 0FAh, 33h, 01h, 00h, 00h, 00h, 00h, 8Bh, 08h
    db 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h
    db 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h
    db 2Dh, 8Ch, 0FAh, 33h, 01h, 0Fh, 84h, 86h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h
    db 84h, 0C0h, 74h, 4Dh, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 55h, 6Ah, 00h, 8Dh, 4Ch, 24h
    db 18h, 89h, 54h, 24h, 18h, 0E8h, 0E6h, 94h, 1Fh, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 0Dh
    db 0C8h, 0ECh, 34h, 01h, 88h, 08h, 55h, 8Dh, 54h, 24h, 14h, 6Ah, 0Bh, 52h, 0C7h, 84h
    db 24h, 0C4h, 00h, 00h, 00h, 03h, 00h, 00h, 00h, 0E8h, 12h, 4Ch, 12h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 0BCh, 24h, 0B8h, 00h, 00h, 00h, 0E8h, 0BFh, 93h, 1Fh
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 55h, 6Ah, 0Bh, 55h, 89h, 2Dh, 8Ch, 0FAh, 33h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h
    db 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 6Ah, 00h, 0E8h, 71h, 5Fh, 85h, 0FFh, 55h, 0E8h, 6Bh, 5Fh, 85h, 0FFh, 0A1h, 0F4h
    db 9Ch, 2Fh, 01h, 83h, 0C4h, 08h, 3Bh, 0C3h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 0Fh
    db 8Ch, 18h, 07h, 00h, 00h, 8Dh, 4Ch, 24h, 30h, 51h, 53h, 50h, 0FFh, 92h, 0B4h, 00h
    db 00h, 00h, 0A1h, 94h, 05h, 34h, 01h, 40h, 8Dh, 54h, 24h, 30h, 0A3h, 94h, 05h, 34h
    db 01h, 52h, 8Dh, 44h, 24h, 30h, 50h, 8Dh, 4Ch, 24h, 78h, 51h, 0E8h, 0C0h, 8Eh, 21h
    db 00h, 0A1h, 0Ch, 0FBh, 33h, 01h, 0BDh, 00h, 00h, 02h, 00h, 3Bh, 0C5h, 0BEh, 04h, 00h
    db 00h, 00h, 0Fh, 84h, 83h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h
    db 4Ah, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h
    db 54h, 24h, 18h, 0E8h, 0F8h, 93h, 1Fh, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 0Dh, 0C8h, 0ECh
    db 34h, 01h, 88h, 08h, 55h, 8Dh, 54h, 24h, 14h, 6Ah, 0Bh, 52h, 89h, 0B4h, 24h, 0C4h
    db 00h, 00h, 00h, 0E8h, 28h, 4Bh, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h
    db 0BCh, 24h, 0B8h, 00h, 00h, 00h, 0E8h, 0D5h, 92h, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 55h, 6Ah, 0Bh, 53h, 89h, 2Dh, 0Ch, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch
    db 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h
    db 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 39h, 1Dh, 40h, 0FBh, 33h
    db 01h, 0Fh, 84h, 87h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Eh
    db 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 54h
    db 24h, 18h, 0E8h, 69h, 93h, 1Fh, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 0Dh, 0C8h, 0ECh, 34h
    db 01h, 88h, 08h, 53h, 8Dh, 54h, 24h, 14h, 6Ah, 18h, 52h, 0C7h, 84h, 24h, 0C4h, 00h
    db 00h, 00h, 05h, 00h, 00h, 00h, 0E8h, 95h, 4Ah, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch
    db 24h, 10h, 89h, 0BCh, 24h, 0B8h, 00h, 00h, 00h, 0E8h, 42h, 92h, 1Fh, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 53h, 6Ah, 18h, 53h, 89h, 1Dh, 40h, 0FBh, 33h, 01h, 8Bh, 08h, 50h
    db 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h
    db 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 34h
    db 05h, 34h, 01h, 8Bh, 10h, 6Ah, 01h, 6Ah, 01h, 53h, 50h, 0FFh, 92h, 14h, 01h, 00h
    db 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 6Ah, 01h, 40h
    db 53h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 53h, 89h, 0Dh, 94h, 05h
    db 34h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 15h, 94h, 05h, 34h
    db 01h, 8Bh, 0Dh, 68h, 05h, 34h, 01h, 0A1h, 0F4h, 9Ch, 2Fh, 01h, 42h, 41h, 3Bh, 0C6h
    db 0A1h, 34h, 05h, 34h, 01h, 89h, 15h, 94h, 05h, 34h, 01h, 89h, 0Dh, 68h, 05h, 34h
    db 01h, 8Bh, 10h, 0Fh, 85h, 01h, 04h, 00h, 00h, 6Ah, 01h, 6Ah, 01h, 6Ah, 03h, 50h
    db 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 3Dh, 94h, 05h, 34h, 01h, 8Bh, 35h, 68h, 05h
    db 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h, 53h, 47h, 46h, 6Ah, 03h, 89h, 3Dh
    db 94h, 05h, 34h, 01h, 89h, 35h, 68h, 05h, 34h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h
    db 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 8Dh
    db 54h, 24h, 10h, 40h, 53h, 52h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h
    db 01h, 0E8h, 97h, 87h, 83h, 0FFh, 83h, 0C4h, 08h, 8Bh, 35h, 34h, 05h, 34h, 01h, 8Bh
    db 3Eh, 8Bh, 0C8h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h, 06h, 00h, 00h, 00h, 0E8h, 0EDh
    db 0B5h, 12h, 00h, 50h, 53h, 56h, 0FFh, 97h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 10h
    db 85h, 0C9h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 05h, 0E8h
    db 0Ch, 91h, 20h, 00h, 8Dh, 44h, 24h, 10h, 6Ah, 03h, 50h, 0E8h, 4Dh, 87h, 83h, 0FFh
    db 83h, 0C4h, 08h, 8Bh, 35h, 34h, 05h, 34h, 01h, 8Bh, 3Eh, 8Bh, 0C8h, 0C7h, 84h, 24h
    db 0B8h, 00h, 00h, 00h, 07h, 00h, 00h, 00h, 0E8h, 0A3h, 0B5h, 12h, 00h, 50h, 6Ah, 03h
    db 56h, 0FFh, 97h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h, 0C7h, 84h, 24h
    db 0B8h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 05h, 0E8h, 0C1h, 90h, 20h, 00h, 8Bh
    db 54h, 24h, 14h, 8Bh, 52h, 10h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 52h, 50h, 0FFh
    db 91h, 0ACh, 01h, 00h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0A1h, 0C8h, 0D5h, 2Eh, 01h
    db 85h, 0C0h, 74h, 05h, 0DDh, 0D8h, 0D9h, 40h, 48h, 0D9h, 54h, 24h, 18h, 0B9h, 04h, 00h
    db 00h, 00h, 0D9h, 54h, 24h, 1Ch, 0BFh, 50h, 11h, 34h, 01h, 0D9h, 54h, 24h, 20h, 8Dh
    db 74h, 24h, 18h, 33h, 0C0h, 0D9h, 5Ch, 24h, 24h, 0F3h, 0A7h, 74h, 44h, 8Bh, 4Ch, 24h
    db 18h, 8Bh, 44h, 24h, 20h, 8Bh, 54h, 24h, 1Ch, 89h, 0Dh, 50h, 11h, 34h, 01h, 8Bh
    db 4Ch, 24h, 24h, 89h, 0Dh, 5Ch, 11h, 34h, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 1Ch, 51h
    db 0A3h, 58h, 11h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 00h, 89h, 15h, 54h, 11h
    db 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 0B4h, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h
    db 01h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 53h, 6Ah, 06h, 53h, 50h, 0FFh, 92h, 14h
    db 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 53h
    db 40h, 6Ah, 05h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 53h, 89h, 0Dh
    db 94h, 05h, 34h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 35h, 94h
    db 05h, 34h, 01h, 8Bh, 15h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h
    db 6Ah, 06h, 46h, 42h, 6Ah, 03h, 89h, 35h, 94h, 05h, 34h, 01h, 89h, 15h, 68h, 05h
    db 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 3Dh, 94h, 05h, 34h
    db 01h, 8Bh, 35h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah, 05h, 47h
    db 46h, 6Ah, 03h, 89h, 3Dh, 94h, 05h, 34h, 01h, 89h, 35h, 68h, 05h, 34h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 6Ah, 01h, 8Dh, 54h, 24h, 74h, 0A3h, 68h, 05h, 34h, 01h
    db 52h, 8Dh, 44h, 24h, 38h, 89h, 0Dh, 94h, 05h, 34h, 01h, 50h, 0B9h, 0E8h, 0C2h, 2Bh
    db 01h, 0E8h, 0C9h, 73h, 83h, 0FFh, 8Bh, 3Dh, 4Ch, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h
    db 01h, 8Dh, 54h, 24h, 30h, 52h, 47h, 6Ah, 12h, 89h, 3Dh, 4Ch, 05h, 34h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0B0h, 00h, 00h, 00h, 8Bh, 35h, 94h, 05h, 34h, 01h, 6Ah, 01h
    db 8Dh, 44h, 24h, 74h, 50h, 8Dh, 4Ch, 24h, 38h, 51h, 46h, 0B9h, 0E8h, 0C2h, 2Bh, 01h
    db 89h, 35h, 94h, 05h, 34h, 01h, 0E8h, 84h, 29h, 82h, 0FFh, 8Bh, 3Dh, 4Ch, 05h, 34h
    db 01h, 47h, 0A1h, 34h, 05h, 34h, 01h, 8Dh, 4Ch, 24h, 30h, 51h, 6Ah, 13h, 89h, 3Dh
    db 4Ch, 05h, 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 0Dh, 94h
    db 05h, 34h, 01h, 0A1h, 8Ch, 0FBh, 33h, 01h, 41h, 3Bh, 0C5h, 89h, 0Dh, 94h, 05h, 34h
    db 01h, 0Fh, 84h, 8Ch, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 52h
    db 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 54h
    db 24h, 18h, 0E8h, 0B9h, 8Fh, 1Fh, 00h, 8Bh, 44h, 24h, 10h, 8Ah, 0Dh, 0C8h, 0ECh, 34h
    db 01h, 88h, 08h, 55h, 8Dh, 54h, 24h, 14h, 6Ah, 0Bh, 52h, 0C7h, 84h, 24h, 0C4h, 00h
    db 00h, 00h, 08h, 00h, 00h, 00h, 0E8h, 0E5h, 46h, 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch
    db 24h, 10h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 8Eh, 8Eh
    db 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 55h, 6Ah, 0Bh, 6Ah, 03h, 89h, 2Dh, 8Ch, 0FBh
    db 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h
    db 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h
    db 05h, 34h, 01h, 39h, 1Dh, 0C0h, 0FBh, 33h, 01h, 0Fh, 84h, 8Bh, 00h, 00h, 00h, 0A0h
    db 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 51h, 8Bh, 15h, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 54h, 24h, 18h, 0E8h, 21h, 8Fh, 1Fh, 00h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 8Bh, 4Ch, 24h, 10h, 88h, 01h, 53h, 8Dh, 54h, 24h, 14h, 6Ah
    db 18h, 52h, 0C7h, 84h, 24h, 0C4h, 00h, 00h, 00h, 09h, 00h, 00h, 00h, 0E8h, 4Eh, 46h
    db 12h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F7h, 8Dh, 1Fh, 00h, 0A1h, 34h, 05h, 34h, 01h, 53h, 6Ah
    db 18h, 6Ah, 03h, 89h, 1Dh, 0C0h, 0FBh, 33h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h
    db 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h
    db 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0B8h, 01h, 00h, 00h, 00h, 8Bh
    db 8Ch, 24h, 0B0h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 81h, 0C4h, 0ACh, 00h, 00h, 00h, 0C2h, 04h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 49h
    db 0Ch, 51h, 50h, 0FFh, 92h, 0ACh, 01h, 00h, 00h, 39h, 1Dh, 0F4h, 9Ch, 2Fh, 01h, 75h
    db 5Eh, 8Dh, 54h, 24h, 14h, 53h, 52h, 0E8h, 0D1h, 83h, 83h, 0FFh, 83h, 0C4h, 08h, 8Bh
    db 35h, 34h, 05h, 34h, 01h, 8Bh, 2Eh, 8Bh, 0C8h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h
    db 0Ah, 00h, 00h, 00h, 0E8h, 27h, 0B2h, 12h, 00h, 50h, 53h, 56h, 0FFh, 95h, 04h, 01h
    db 00h, 00h, 8Bh, 4Ch, 24h, 14h, 85h, 0C9h, 89h, 0BCh, 24h, 0B8h, 00h, 00h, 00h, 74h
    db 05h, 0E8h, 4Ah, 8Dh, 20h, 00h, 6Ah, 01h, 8Dh, 44h, 24h, 74h, 50h, 8Dh, 4Ch, 24h
    db 38h, 51h, 0B9h, 0E8h, 0C2h, 2Bh, 01h, 0E8h, 93h, 71h, 83h, 0FFh, 53h, 0EBh, 5Eh, 8Dh
    db 54h, 24h, 28h, 6Ah, 03h, 52h, 0E8h, 72h, 83h, 83h, 0FFh, 83h, 0C4h, 08h, 8Bh, 35h
    db 34h, 05h, 34h, 01h, 8Bh, 2Eh, 8Bh, 0C8h, 0C7h, 84h, 24h, 0B8h, 00h, 00h, 00h, 0Bh
    db 00h, 00h, 00h, 0E8h, 0C8h, 0B1h, 12h, 00h, 50h, 53h, 56h, 0FFh, 95h, 04h, 01h, 00h
    db 00h, 8Bh, 4Ch, 24h, 28h, 85h, 0C9h, 89h, 0BCh, 24h, 0B8h, 00h, 00h, 00h, 74h, 05h
    db 0E8h, 0EBh, 8Ch, 20h, 00h, 6Ah, 01h, 8Dh, 44h, 24h, 74h, 50h, 8Dh, 4Ch, 24h, 38h
    db 51h, 0B9h, 0E8h, 0C2h, 2Bh, 01h, 0E8h, 34h, 27h, 82h, 0FFh, 6Ah, 01h, 0A1h, 34h, 05h
    db 34h, 01h, 8Bh, 10h, 6Ah, 06h, 53h, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 0Dh
    db 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 53h, 40h, 6Ah, 05h, 0A3h, 68h
    db 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 53h, 89h, 0Dh, 94h, 05h, 34h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 8Bh, 1Dh, 4Ch, 05h, 34h, 01h, 41h, 89h, 0Dh, 94h, 05h, 34h, 01h
    db 40h, 8Dh, 4Ch, 24h, 30h, 51h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h
    db 43h, 6Ah, 12h, 89h, 1Dh, 4Ch, 05h, 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 0B0h, 00h
    db 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 8Dh, 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h
    db 14h, 8Bh, 49h, 08h, 51h, 50h, 0FFh, 92h, 0ACh, 01h, 00h, 00h, 8Bh, 0C5h, 0E9h, 7Ch
    db 0FEh, 0FFh, 0FFh
?d_007e2180@@YAXXZ ENDP

; ghidra: FUN_00be2e50  retail @ 0x007E2E50 size 53
public ?d_007e2e50@@YAXXZ
?d_007e2e50@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 10h, 57h, 56h, 0E8h, 13h, 0F1h, 09h, 00h, 8Bh, 0D0h, 8Bh
    db 0CEh, 8Bh, 0D9h, 0C1h, 0E9h, 02h, 33h, 0C0h, 8Bh, 0FAh, 0F3h, 0ABh, 8Bh, 0CBh, 83h, 0C4h
    db 04h, 83h, 0E1h, 03h, 0F3h, 0AAh, 8Bh, 44h, 24h, 10h, 5Fh, 89h, 72h, 04h, 5Eh, 89h
    db 02h, 8Bh, 0C2h, 5Bh, 0C3h
?d_007e2e50@@YAXXZ ENDP

; ghidra: FUN_00be2eb0  retail @ 0x007E2EB0 size 120
public ?d_007e2eb0@@YAXXZ
?d_007e2eb0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 55h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 8Bh, 01h, 6Ah, 04h, 52h
    db 0FFh, 50h, 0Ch, 83h, 0F8h, 04h, 8Bh, 6Ch, 24h, 14h, 0C6h, 45h, 00h, 00h, 74h, 0Fh
    db 85h, 0C0h, 74h, 04h, 0C6h, 45h, 00h, 01h, 5Eh, 32h, 0C0h, 5Dh, 0C2h, 0Ch, 00h, 8Bh
    db 4Eh, 04h, 8Bh, 01h, 53h, 8Bh, 5Ch, 24h, 14h, 57h, 6Ah, 04h, 53h, 0FFh, 50h, 0Ch
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 8Bh, 0F8h, 0FFh, 52h, 30h, 8Bh, 76h, 0Ch, 2Bh, 0F0h, 83h
    db 0FFh, 04h, 75h, 17h, 8Bh, 1Bh, 83h, 0FBh, 08h, 72h, 10h, 83h, 0C3h, 0F8h, 3Bh, 0DEh
    db 77h, 09h, 5Fh, 5Bh, 5Eh, 0B0h, 01h, 5Dh, 0C2h, 0Ch, 00h, 5Fh, 5Bh, 5Eh, 0C6h, 45h
    db 00h, 01h, 32h, 0C0h, 5Dh, 0C2h, 0Ch, 00h
?d_007e2eb0@@YAXXZ ENDP

; ghidra: FUN_00be2f50  retail @ 0x007E2F50 size 236
_TEXT ENDS
_TEXT$d00be2f50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE2F50 size 236
public ?d_007e2f50@@YAXXZ
?d_007e2f50@@YAXXZ PROC
    db 051h, 08Bh, 044h, 024h, 008h, 053h, 08Bh, 05Ch, 024h, 018h, 055h, 08Bh, 06Ch, 024h, 014h, 056h
    db 08Bh, 074h, 024h, 01Ch, 057h, 053h, 056h, 08Bh, 0F9h, 0C6h, 003h, 000h, 055h, 089h, 07Ch, 024h
    db 01Ch, 0C7h, 000h, 000h, 000h, 000h, 000h
    call ?j_00038163@@YAXXZ
    db 084h, 0C0h, 074h, 07Ah, 08Ah, 044h, 024h, 028h, 084h, 0C0h, 074h, 07Ch, 08Bh, 01Eh, 08Bh, 04Dh
    db 000h, 053h, 089h, 04Ch, 024h, 02Ch
    call ??_U@YAPAXI@Z
    db 08Bh, 0D0h, 08Bh, 0CBh, 08Bh, 0E9h, 0C1h, 0E9h, 002h, 033h, 0C0h, 08Bh, 0FAh, 0F3h, 0ABh, 08Bh
    db 0CDh, 083h, 0E1h, 003h, 0F3h, 0AAh, 08Bh, 044h, 024h, 02Ch, 08Bh, 07Ch, 024h, 01Ch, 08Bh, 04Ch
    db 024h, 014h, 089h, 05Ah, 004h, 089h, 002h, 089h, 017h, 08Bh, 01Eh, 08Bh, 049h, 004h, 08Bh, 001h
    db 083h, 0C4h, 004h, 083h, 0EBh, 008h, 083h, 0C2h, 008h, 053h, 052h, 0FFh, 050h, 00Ch, 08Bh, 00Eh
    db 083h, 0E9h, 008h, 03Bh, 0C1h, 074h, 054h, 08Bh, 007h, 085h, 0C0h, 074h, 00Fh, 050h
    call ??_V@YAXPAX@Z
    db 083h, 0C4h, 004h, 0C7h, 007h, 000h, 000h, 000h, 000h, 08Bh, 054h, 024h, 024h, 0C6h, 002h, 001h
    db 05Fh, 05Eh, 05Dh, 032h, 0C0h, 05Bh, 059h, 0C2h, 014h, 000h, 08Bh, 04Fh, 004h, 08Bh, 036h, 08Bh
    db 001h, 083h, 0C6h, 0F8h, 0FFh, 050h, 030h, 08Bh, 04Fh, 00Ch, 003h, 0C6h, 03Bh, 0C1h, 07Eh, 00Dh
    db 05Fh, 05Eh, 05Dh, 0C6h, 003h, 001h, 032h, 0C0h, 05Bh, 059h, 0C2h, 014h, 000h, 08Bh, 04Fh, 004h
    db 08Bh, 011h, 06Ah, 001h, 056h, 0FFh, 052h, 014h, 05Fh, 05Eh, 05Dh, 0B0h, 001h, 05Bh, 059h, 0C2h
    db 014h, 000h
?d_007e2f50@@YAXXZ ENDP
_TEXT$d00be2f50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00be3080  retail @ 0x007E3080 size 108
public ?d_007e3080@@YAXXZ
?d_007e3080@@YAXXZ PROC
    db 51h, 53h, 8Bh, 5Ch, 24h, 10h, 56h, 8Bh, 74h, 24h, 18h, 57h, 8Dh, 44h, 24h, 0Fh
    db 50h, 56h, 53h, 8Bh, 0F9h, 0C6h, 44h, 24h, 1Bh, 00h, 0E8h, 0C4h, 50h, 85h, 0FFh, 84h
    db 0C0h, 74h, 40h, 8Ah, 44h, 24h, 0Fh, 84h, 0C0h, 75h, 38h, 8Bh, 0Eh, 3Bh, 4Ch, 24h
    db 20h, 77h, 30h, 8Bh, 13h, 8Bh, 44h, 24h, 14h, 89h, 10h, 8Bh, 0Eh, 89h, 48h, 04h
    db 8Bh, 4Fh, 04h, 8Bh, 3Eh, 8Bh, 11h, 83h, 0EFh, 08h, 57h, 83h, 0C0h, 08h, 50h, 0FFh
    db 52h, 0Ch, 8Bh, 0Eh, 5Fh, 83h, 0E9h, 08h, 3Bh, 0C1h, 5Eh, 0Fh, 94h, 0C0h, 5Bh, 59h
    db 0C2h, 10h, 00h, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 59h, 0C2h, 10h, 00h
?d_007e3080@@YAXXZ ENDP

; ghidra: FUN_00be3110  retail @ 0x007E3110 size 30
public ?d_007e3110@@YAXXZ
?d_007e3110@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 85h, 0C9h, 74h, 10h, 8Bh, 01h, 0FFh, 50h, 08h, 0C7h
    db 46h, 04h, 00h, 00h, 00h, 00h, 0B0h, 01h, 5Eh, 0C3h, 32h, 0C0h, 5Eh, 0C3h
?d_007e3110@@YAXXZ ENDP

; ghidra: FUN_00be31d0  retail @ 0x007E31D0 size 67
public ?d_007e31d0@@YAXXZ
?d_007e31d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 83h, 7Eh, 08h, 06h, 57h, 75h, 32h, 8Bh, 7Ch, 24h, 14h, 8Bh, 44h
    db 24h, 10h, 8Bh, 4Ch, 24h, 0Ch, 57h, 50h, 51h, 8Bh, 0CEh, 0E8h, 73h, 4Fh, 85h, 0FFh
    db 84h, 0C0h, 74h, 18h, 80h, 3Fh, 00h, 75h, 13h, 8Bh, 4Eh, 04h, 8Bh, 11h, 6Ah, 01h
    db 6Ah, 0F8h, 0FFh, 52h, 14h, 5Fh, 0B0h, 01h, 5Eh, 0C2h, 0Ch, 00h, 5Fh, 32h, 0C0h, 5Eh
    db 0C2h, 0Ch, 00h
?d_007e31d0@@YAXXZ ENDP

; ghidra: FUN_00be3230  retail @ 0x007E3230 size 83
public ?d_007e3230@@YAXXZ
?d_007e3230@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 83h, 7Eh, 08h, 06h, 75h, 42h, 8Dh, 44h, 24h, 07h
    db 50h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0C6h, 44h, 24h
    db 13h, 00h, 0E8h, 0Ch, 4Fh, 85h, 0FFh, 84h, 0C0h, 74h, 23h, 8Ah, 44h, 24h, 07h, 84h
    db 0C0h, 75h, 1Bh, 8Bh, 4Eh, 04h, 8Bh, 01h, 6Ah, 01h, 6Ah, 0F8h, 0FFh, 50h, 14h, 8Bh
    db 4Eh, 04h, 8Bh, 44h, 24h, 08h, 8Bh, 11h, 6Ah, 01h, 50h, 0FFh, 52h, 14h, 5Eh, 83h
    db 0C4h, 0Ch, 0C3h
?d_007e3230@@YAXXZ ENDP

; ghidra: FUN_00be32a0  retail @ 0x007E32A0 size 41
public ?d_007e32a0@@YAXXZ
?d_007e32a0@@YAXXZ PROC
    db 83h, 79h, 08h, 06h, 75h, 1Eh, 8Bh, 54h, 24h, 0Ch, 6Ah, 01h, 8Dh, 44h, 24h, 10h
    db 50h, 8Bh, 44h, 24h, 10h, 52h, 8Bh, 54h, 24h, 10h, 50h, 52h, 0E8h, 4Eh, 0C5h, 85h
    db 0FFh, 0C2h, 0Ch, 00h, 32h, 0C0h, 0C2h, 0Ch, 00h
?d_007e32a0@@YAXXZ ENDP

; ghidra: FUN_00be32e0  retail @ 0x007E32E0 size 230
public ?d_007e32e0@@YAXXZ
?d_007e32e0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 83h, 7Eh, 08h, 06h, 0Fh, 85h, 0D6h, 00h, 00h, 00h
    db 53h, 57h, 8Dh, 44h, 24h, 0Fh, 50h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 54h, 24h, 18h
    db 52h, 8Bh, 0CEh, 0C6h, 44h, 24h, 1Bh, 00h, 0E8h, 56h, 4Eh, 85h, 0FFh, 84h, 0C0h, 8Bh
    db 5Ch, 24h, 20h, 74h, 5Ah, 0EBh, 09h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Ah, 44h, 24h, 0Fh, 84h, 0C0h, 0Fh, 85h, 8Fh, 00h, 00h, 00h, 39h, 5Ch, 24h, 10h
    db 74h, 4Bh, 8Bh, 4Eh, 04h, 8Bh, 7Ch, 24h, 14h, 8Bh, 01h, 83h, 0C7h, 0F8h, 0FFh, 50h
    db 30h, 8Bh, 4Eh, 0Ch, 03h, 0C7h, 3Bh, 0C1h, 7Fh, 71h, 8Bh, 4Eh, 04h, 8Bh, 11h, 6Ah
    db 01h, 57h, 0FFh, 52h, 14h, 8Dh, 44h, 24h, 0Fh, 50h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh
    db 54h, 24h, 18h, 52h, 8Bh, 0CEh, 0E8h, 0F8h, 4Dh, 85h, 0FFh, 84h, 0C0h, 75h, 0B1h, 8Ah
    db 44h, 24h, 0Fh, 84h, 0C0h, 75h, 44h, 39h, 5Ch, 24h, 10h, 75h, 3Eh, 8Bh, 4Eh, 04h
    db 8Bh, 01h, 6Ah, 01h, 6Ah, 0F8h, 0FFh, 50h, 14h, 83h, 7Eh, 08h, 06h, 75h, 2Ch, 6Ah
    db 01h, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 4Ch, 24h, 24h, 8Dh, 54h, 24h, 1Ch, 52h, 8Dh
    db 44h, 24h, 1Ch, 50h, 51h, 8Bh, 0CEh, 0E8h, 63h, 0C4h, 85h, 0FFh, 84h, 0C0h, 74h, 0Bh
    db 5Fh, 5Bh, 0B0h, 01h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 5Fh, 5Bh, 32h, 0C0h, 5Eh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_007e32e0@@YAXXZ ENDP

; ghidra: FUN_00be3410  retail @ 0x007E3410 size 19
public ?d_007e3410@@YAXXZ
?d_007e3410@@YAXXZ PROC
    db 83h, 79h, 08h, 06h, 75h, 0Ch, 8Bh, 49h, 04h, 8Bh, 01h, 6Ah, 00h, 6Ah, 00h, 0FFh
    db 50h, 14h, 0C3h
?d_007e3410@@YAXXZ ENDP

; ghidra: FUN_00be3430  retail @ 0x007E3430 size 20
public ?d_007e3430@@YAXXZ
?d_007e3430@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 89h, 48h, 04h, 0C7h, 40h, 08h, 04h, 00h, 00h, 00h
    db 89h, 48h, 0Ch, 0C3h
?d_007e3430@@YAXXZ ENDP

; ghidra: FUN_00be3450  retail @ 0x007E3450 size 87
public ?d_007e3450@@YAXXZ
?d_007e3450@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 44h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 4Eh, 04h
    db 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 0Ch, 8Bh, 01h, 0FFh, 50h
    db 08h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0A9h, 44h, 0Ah, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_007e3450@@YAXXZ ENDP

; ghidra: FUN_00be35e0  retail @ 0x007E35E0 size 314
public ?d_007e35e0@@YAXXZ
?d_007e35e0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 53h, 56h, 32h, 0DBh, 85h, 0D2h, 57h, 8Bh, 0F1h, 74h, 10h, 8Bh
    db 0C2h, 8Dh, 78h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C7h, 0EBh, 02h, 33h
    db 0C0h, 50h, 52h, 8Bh, 0CEh, 0E8h, 16h, 47h, 0Ah, 00h, 8Bh, 44h, 24h, 14h, 83h, 0F8h
    db 01h, 0Fh, 85h, 0BBh, 00h, 00h, 00h, 8Bh, 06h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h
    db 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 48h, 0CBh, 34h, 01h, 50h, 0E8h, 6Dh
    db 50h, 1Eh, 00h, 84h, 0C0h, 75h, 0Fh, 0C7h, 46h, 08h, 05h, 00h, 00h, 00h, 5Fh, 5Eh
    db 8Ah, 0C3h, 5Bh, 0C2h, 0Ch, 00h, 8Bh, 06h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh
    db 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 48h, 0CBh, 34h, 01h, 68h, 41h, 01h, 00h
    db 00h, 50h, 0E8h, 0F9h, 51h, 1Eh, 00h, 89h, 46h, 04h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h
    db 2Ch, 83h, 0F8h, 08h, 0BFh, 06h, 00h, 00h, 00h, 89h, 46h, 0Ch, 89h, 7Eh, 08h, 7Ch
    db 42h, 8Ah, 44h, 24h, 18h, 84h, 0C0h, 74h, 21h, 8Bh, 0CEh, 0E8h, 0D1h, 0CAh, 84h, 0FFh
    db 84h, 0C0h, 75h, 16h, 8Bh, 0CEh, 0C7h, 46h, 08h, 03h, 00h, 00h, 00h, 0E8h, 4Fh, 0AAh
    db 83h, 0FFh, 5Fh, 5Eh, 8Ah, 0C3h, 5Bh, 0C2h, 0Ch, 00h, 39h, 7Eh, 08h, 75h, 0Ch, 8Bh
    db 4Eh, 04h, 8Bh, 01h, 6Ah, 00h, 6Ah, 00h, 0FFh, 50h, 14h, 5Fh, 5Eh, 0B0h, 01h, 5Bh
    db 0C2h, 0Ch, 00h, 5Fh, 0C7h, 46h, 08h, 03h, 00h, 00h, 00h, 5Eh, 8Ah, 0C3h, 5Bh, 0C2h
    db 0Ch, 00h, 83h, 0F8h, 02h, 0Fh, 85h, 63h, 0FFh, 0FFh, 0FFh, 8Bh, 06h, 85h, 0C0h, 74h
    db 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 48h, 0CBh, 34h
    db 01h, 6Ah, 5Ah, 50h, 0E8h, 67h, 51h, 1Eh, 00h, 85h, 0C0h, 89h, 46h, 04h, 0C7h, 46h
    db 08h, 03h, 00h, 00h, 00h, 0Fh, 84h, 33h, 0FFh, 0FFh, 0FFh, 5Fh, 0C7h, 46h, 08h, 07h
    db 00h, 00h, 00h, 5Eh, 0B0h, 01h, 5Bh, 0C2h, 0Ch, 00h
?d_007e35e0@@YAXXZ ENDP

; ghidra: FUN_00be3770  retail @ 0x007E3770 size 301
public ?d_007e3770@@YAXXZ
?d_007e3770@@YAXXZ PROC
    db 83h, 0ECh, 18h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 0BFh, 06h, 00h, 00h
    db 00h, 3Bh, 0C7h, 0Fh, 85h, 08h, 01h, 00h, 00h, 8Bh, 4Eh, 04h, 8Bh, 01h, 33h, 0DBh
    db 89h, 5Ch, 24h, 14h, 0FFh, 50h, 30h, 89h, 44h, 24h, 20h, 39h, 7Eh, 08h, 89h, 5Ch
    db 24h, 1Ch, 89h, 5Ch, 24h, 18h, 88h, 5Ch, 24h, 13h, 75h, 0Ah, 8Bh, 4Eh, 04h, 8Bh
    db 11h, 53h, 53h, 0FFh, 52h, 14h, 8Bh, 7Ch, 24h, 30h, 8Bh, 6Ch, 24h, 2Ch, 8Bh, 0FFh
    db 83h, 7Eh, 08h, 06h, 0Fh, 85h, 0AAh, 00h, 00h, 00h, 8Dh, 44h, 24h, 13h, 50h, 8Dh
    db 4Ch, 24h, 1Ch, 51h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 0CEh, 0E8h, 83h, 49h, 85h, 0FFh
    db 84h, 0C0h, 8Ah, 44h, 24h, 13h, 0Fh, 84h, 84h, 00h, 00h, 00h, 3Ah, 0C3h, 0Fh, 85h
    db 9Dh, 00h, 00h, 00h, 8Bh, 4Eh, 04h, 8Bh, 01h, 6Ah, 01h, 6Ah, 0F8h, 0FFh, 50h, 14h
    db 3Bh, 0EBh, 8Bh, 44h, 24h, 18h, 74h, 0Ch, 39h, 6Ch, 24h, 1Ch, 75h, 0Ah, 39h, 07h
    db 73h, 02h, 89h, 07h, 0FFh, 44h, 24h, 14h, 39h, 07h, 73h, 02h, 89h, 07h, 83h, 7Eh
    db 08h, 06h, 75h, 50h, 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 54h, 24h, 30h, 52h, 8Dh, 44h
    db 24h, 2Ch, 50h, 8Bh, 0CEh, 88h, 5Ch, 24h, 3Ch, 0E8h, 25h, 49h, 85h, 0FFh, 84h, 0C0h
    db 0Fh, 84h, 7Ah, 0FFh, 0FFh, 0FFh, 38h, 5Ch, 24h, 30h, 0Fh, 85h, 70h, 0FFh, 0FFh, 0FFh
    db 8Bh, 4Eh, 04h, 8Bh, 11h, 6Ah, 01h, 6Ah, 0F8h, 0FFh, 52h, 14h, 8Bh, 4Eh, 04h, 8Bh
    db 54h, 24h, 2Ch, 8Bh, 01h, 6Ah, 01h, 52h, 0FFh, 50h, 14h, 0E9h, 50h, 0FFh, 0FFh, 0FFh
    db 3Ah, 0C3h, 75h, 1Dh, 8Bh, 4Eh, 04h, 8Bh, 54h, 24h, 20h, 8Bh, 01h, 6Ah, 01h, 52h
    db 0FFh, 50h, 14h, 8Bh, 44h, 24h, 14h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 18h, 0C2h, 08h
    db 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 83h, 0C4h, 18h, 0C2h, 08h, 00h
?d_007e3770@@YAXXZ ENDP

; ghidra: FUN_00be38f0  retail @ 0x007E38F0 size 48
public ?d_007e38f0@@YAXXZ
?d_007e38f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 83h, 7Eh, 08h, 06h, 75h, 21h, 8Bh, 4Eh, 04h, 8Bh, 01h, 6Ah, 00h
    db 6Ah, 00h, 0FFh, 50h, 14h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 51h, 52h, 8Bh
    db 0CEh, 0E8h, 0FBh, 83h, 82h, 0FFh, 5Eh, 0C2h, 08h, 00h, 32h, 0C0h, 5Eh, 0C2h, 08h, 00h
?d_007e38f0@@YAXXZ ENDP

; ghidra: FUN_00be3930  retail @ 0x007E3930 size 100
public ?d_007e3930@@YAXXZ
?d_007e3930@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 44h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 6Ah, 01h, 8Bh, 0F1h
    db 57h, 89h, 74h, 24h, 10h, 0E8h, 26h, 52h, 0Ah, 00h, 8Bh, 4Ch, 24h, 20h, 33h, 0C0h
    db 89h, 44h, 24h, 14h, 89h, 46h, 04h, 89h, 46h, 0Ch, 8Bh, 44h, 24h, 24h, 50h, 51h
    db 57h, 8Bh, 0CEh, 0C7h, 46h, 08h, 04h, 00h, 00h, 00h, 0E8h, 8Fh, 22h, 82h, 0FFh, 8Bh
    db 4Ch, 24h, 0Ch, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 0Ch, 00h
?d_007e3930@@YAXXZ ENDP

; ghidra: FUN_00be3a80  retail @ 0x007E3A80 size 37
public ?d_007e3a80@@YAXXZ
?d_007e3a80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 0Ch, 50h
    db 51h, 52h, 8Bh, 0CEh, 0E8h, 0B7h, 8Ah, 03h, 00h, 0C7h, 06h, 30h, 8Dh, 12h, 01h, 8Bh
    db 0C6h, 5Eh, 0C2h, 0Ch, 00h
?d_007e3a80@@YAXXZ ENDP

; ghidra: FUN_00be3ad0  retail @ 0x007E3AD0 size 16
public ?d_007e3ad0@@YAXXZ
?d_007e3ad0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 88h, 12h, 1Ch, 00h, 8Bh, 0CEh, 5Eh, 0E9h, 50h, 88h, 03h, 00h
?d_007e3ad0@@YAXXZ ENDP

; ghidra: FUN_00be3b40  retail @ 0x007E3B40 size 144
public ?d_007e3b40@@YAXXZ
?d_007e3b40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 44h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 53h, 56h, 8Bh, 0F1h, 8Bh, 4Ch
    db 24h, 1Ch, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 10h, 0E8h, 11h, 0A9h, 03h, 00h, 33h
    db 0DBh, 8Dh, 4Eh, 1Ch, 89h, 5Ch, 24h, 14h, 0C7h, 06h, 0A8h, 8Dh, 12h, 01h, 89h, 5Eh
    db 14h, 89h, 5Eh, 18h, 0E8h, 8Ch, 75h, 85h, 0FFh, 0B8h, 01h, 00h, 00h, 00h, 83h, 0C9h
    db 0FFh, 89h, 46h, 44h, 89h, 46h, 5Ch, 89h, 46h, 60h, 89h, 5Eh, 2Ch, 89h, 5Eh, 30h
    db 89h, 5Eh, 34h, 88h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h, 89h, 4Eh, 48h, 89h
    db 4Eh, 4Ch, 8Bh, 4Ch, 24h, 0Ch, 89h, 5Eh, 50h, 89h, 5Eh, 54h, 89h, 5Eh, 58h, 8Bh
    db 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_007e3b40@@YAXXZ ENDP

; ghidra: FUN_00be3c20  retail @ 0x007E3C20 size 217
public ?d_007e3c20@@YAXXZ
?d_007e3c20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 03h, 45h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 06h, 0A8h, 8Dh, 12h, 01h, 8Bh, 46h, 14h, 8Dh, 7Eh, 14h, 33h, 0DBh, 3Bh, 0C3h, 0C7h
    db 44h, 24h, 18h, 01h, 00h, 00h, 00h, 74h, 0Bh, 57h, 0E8h, 0C1h, 1Bh, 1Ch, 00h, 83h
    db 0C4h, 04h, 89h, 1Fh, 8Bh, 46h, 18h, 3Bh, 0C3h, 8Dh, 7Eh, 18h, 74h, 0Bh, 57h, 0E8h
    db 0ACh, 1Bh, 1Ch, 00h, 83h, 0C4h, 04h, 89h, 1Fh, 8Bh, 4Eh, 2Ch, 3Bh, 0CBh, 74h, 0Ah
    db 8Bh, 01h, 6Ah, 01h, 0FFh, 50h, 04h, 89h, 5Eh, 2Ch, 8Bh, 46h, 54h, 3Bh, 0C3h, 74h
    db 13h, 3Bh, 0C3h, 74h, 0Ch, 50h, 0E8h, 55h, 0E2h, 09h, 00h, 83h, 0C4h, 04h, 89h, 5Eh
    db 54h, 89h, 5Eh, 54h, 8Bh, 46h, 5Ch, 83h, 0F8h, 01h, 74h, 0Ch, 8Bh, 0Dh, 68h, 0D6h
    db 2Eh, 01h, 8Bh, 11h, 50h, 0FFh, 52h, 4Ch, 8Bh, 46h, 60h, 83h, 0F8h, 01h, 74h, 0Ch
    db 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 50h, 0FFh, 52h, 4Ch, 8Dh, 4Eh, 1Ch, 88h
    db 5Ch, 24h, 18h, 0E8h, 77h, 0Eh, 84h, 0FFh, 8Bh, 0CEh, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0C9h, 0A7h, 03h, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_007e3c20@@YAXXZ ENDP

; ghidra: FUN_00be3d30  retail @ 0x007E3D30 size 243
_TEXT ENDS
_TEXT$d00be3d30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE3D30 size 243
public ?d_007e3d30@@YAXXZ
?d_007e3d30@@YAXXZ PROC
    db 083h, 0ECh, 008h, 056h, 08Bh, 0F1h, 08Ah, 046h, 038h, 084h, 0C0h, 057h, 089h, 035h
    dd g_Va01309840
    db 074h, 056h, 08Dh, 07Eh, 01Ch, 08Bh, 046h, 058h, 050h, 08Bh, 046h, 054h, 08Dh, 04Ch, 024h, 010h
    db 051h, 08Dh, 054h, 024h, 010h, 052h, 050h, 08Bh, 0CFh
    call ?j_0002eae1@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 0A1h, 000h, 000h, 000h, 08Bh, 044h, 024h, 008h, 03Dh, 041h, 056h, 030h
    db 04Bh, 074h, 007h, 03Dh, 041h, 056h, 030h, 046h, 075h, 0CDh, 08Bh, 056h, 034h, 08Bh, 046h, 030h
    db 08Bh, 04Ch, 024h, 00Ch, 052h, 08Bh, 056h, 054h, 050h, 08Bh, 046h, 018h, 051h, 083h, 0C2h, 008h
    db 052h, 050h
    call ?Rva009A5800Forward@@YAXHHH@Z
    db 083h, 0C4h, 014h, 08Dh, 07Eh, 01Ch, 08Dh, 049h, 000h, 08Bh, 04Eh, 058h, 051h, 08Bh, 04Eh, 054h
    db 08Dh, 054h, 024h, 010h, 052h, 08Dh, 044h, 024h, 010h, 050h, 051h, 08Bh, 0CFh
    call ?j_0002eae1@@YAXXZ
    db 08Bh, 015h
    dd g_Va0130983C
    db 042h, 084h, 0C0h, 089h, 015h
    dd g_Va0130983C
    db 074h, 04Ch, 08Bh, 044h, 024h, 008h, 03Dh, 04Dh, 056h, 030h, 04Bh, 074h, 007h, 03Dh, 04Dh, 056h
    db 030h, 046h, 075h, 0C4h, 08Bh, 046h, 034h, 08Bh, 04Eh, 030h, 08Bh, 054h, 024h, 00Ch, 050h, 08Bh
    db 046h, 054h, 051h, 08Bh, 04Eh, 014h, 052h, 083h, 0C0h, 008h, 050h, 051h
    call ?Rva009A5800Forward@@YAXHHH@Z
    db 08Bh, 046h, 048h, 083h, 0C4h, 014h, 040h, 05Fh, 089h, 046h, 048h, 05Eh, 083h, 0C4h, 008h, 0C3h
    db 08Bh, 04Eh, 03Ch, 049h, 05Fh, 089h, 04Eh, 048h, 05Eh, 083h, 0C4h, 008h, 0C3h, 08Bh, 056h, 03Ch
    db 04Ah, 05Fh, 089h, 056h, 048h, 05Eh, 083h, 0C4h, 008h, 0C3h
?d_007e3d30@@YAXXZ ENDP
_TEXT$d00be3d30 ENDS
_TEXT SEGMENT

; ghidra: FUN_00be4730  retail @ 0x007E4730 size 11
; ghidra: FUN_00be4790  retail @ 0x007E4790 size 13
public ?d_007e4790@@YAXXZ
?d_007e4790@@YAXXZ PROC
    db 8Bh, 41h, 3Ch, 8Bh, 51h, 48h, 48h, 3Bh, 0D0h, 0Fh, 9Dh, 0C0h, 0C3h
?d_007e4790@@YAXXZ ENDP

; ghidra: FUN_00be47a0  retail @ 0x007E47A0 size 87
public ?d_007e47a0@@YAXXZ
?d_007e47a0@@YAXXZ PROC
    db 51h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 83h, 7Fh, 24h, 05h, 8Bh, 0F1h, 0C6h, 44h, 24h
    db 08h, 00h, 75h, 05h, 0C6h, 44h, 24h, 08h, 01h, 8Bh, 44h, 24h, 08h, 8Bh, 16h, 53h
    db 8Bh, 1Fh, 50h, 8Bh, 0CEh, 0FFh, 52h, 2Ch, 50h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 30h
    db 50h, 8Bh, 0CFh, 0FFh, 53h, 08h, 84h, 0C0h, 5Bh, 74h, 0Bh, 89h, 7Eh, 2Ch, 5Fh, 0B0h
    db 01h, 5Eh, 59h, 0C2h, 04h, 00h, 8Bh, 17h, 6Ah, 01h, 8Bh, 0CFh, 0FFh, 52h, 04h, 5Fh
    db 32h, 0C0h, 5Eh, 59h, 0C2h, 04h, 00h
?d_007e47a0@@YAXXZ ENDP

; ghidra: FUN_00be4820  retail @ 0x007E4820 size 230
_TEXT ENDS
_TEXT$d00be4820 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE4820 size 230
public ?d_007e4820@@YAXXZ
?d_007e4820@@YAXXZ PROC
    db 0A0h
    dd ?g_01309838@@3EA
    db 056h, 084h, 0C0h, 08Bh, 044h, 024h, 008h, 057h, 08Bh, 0F1h, 075h, 034h, 0A8h, 044h, 075h, 030h
    db 0FFh, 015h
    dd __imp__timeGetTime@0
    db 02Bh, 046h, 050h, 0F7h, 06Eh, 040h, 08Bh, 0C8h, 08Bh, 046h, 044h, 08Bh, 0FAh, 099h, 052h, 050h
    db 057h, 051h
    call __alldiv
    db 06Ah, 000h, 068h, 0E8h, 003h, 000h, 000h, 052h, 050h
    call __alldiv
    db 05Fh, 05Eh, 0C2h, 004h, 000h, 0A9h, 000h, 000h, 080h, 000h, 08Bh, 07Eh, 040h, 074h, 002h, 0D1h
    db 0FFh, 053h, 055h, 0FFh, 015h
    dd __imp__timeGetTime@0
    db 08Bh, 0C8h, 08Bh, 0C7h, 099h, 08Bh, 0F8h, 08Bh, 046h, 048h, 040h, 08Bh, 0DAh, 08Bh, 056h, 050h
    db 089h, 044h, 024h, 014h, 08Bh, 0C1h, 053h, 02Bh, 0C2h, 099h, 057h, 052h, 050h
    call __allmul
    db 08Bh, 0C8h, 08Bh, 046h, 044h, 08Bh, 0EAh, 099h, 052h, 050h, 055h, 051h
    call __alldiv
    db 06Ah, 000h, 068h, 0E8h, 003h, 000h, 000h, 052h, 050h
    call __alldiv
    db 08Bh, 04Ch, 024h, 014h, 03Bh, 0C8h, 07Dh, 009h, 05Dh, 05Bh, 05Fh, 08Bh, 0C1h, 05Eh, 0C2h, 004h
    db 000h, 0FFh, 015h
    dd __imp__timeGetTime@0
    db 08Bh, 056h, 050h, 053h, 02Bh, 0C2h, 099h, 057h, 052h, 050h
    call __allmul
    db 08Bh, 0C8h, 08Bh, 046h, 044h, 08Bh, 0FAh, 099h, 052h, 050h, 057h, 051h
    call __alldiv
    db 06Ah, 000h, 068h, 0E8h, 003h, 000h, 000h, 052h, 050h
    call __alldiv
    db 05Dh, 05Bh, 05Fh, 05Eh, 0C2h, 004h, 000h
?d_007e4820@@YAXXZ ENDP
_TEXT$d00be4820 ENDS
_TEXT SEGMENT

; ghidra: FUN_00be4960  retail @ 0x007E4960 size 9
public ?d_007e4960@@YAXXZ
?d_007e4960@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 0Ch, 8Eh, 12h, 01h, 0C3h
?d_007e4960@@YAXXZ ENDP

; ghidra: FUN_00be4a00  retail @ 0x007E4A00 size 86
public ?d_007e4a00@@YAXXZ
?d_007e4a00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 45h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 30h
    db 8Dh, 12h, 01h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 30h, 03h, 1Ch, 00h
    db 8Bh, 0CEh, 0E8h, 0F9h, 78h, 03h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 4Ah, 7Bh, 03h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_007e4a00@@YAXXZ ENDP

; ghidra: FUN_00be4aa0  retail @ 0x007E4AA0 size 29
public ?d_007e4aa0@@YAXXZ
?d_007e4aa0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0FEh, 45h, 83h, 0FFh, 8Bh, 56h, 4Ch
    db 33h, 0C9h, 3Bh, 0D0h, 0Fh, 9Ch, 0C1h, 8Ah, 0C1h, 5Eh, 0C2h, 04h, 00h
?d_007e4aa0@@YAXXZ ENDP

; ghidra: FUN_00be4ad0  retail @ 0x007E4AD0 size 136
public ?d_007e4ad0@@YAXXZ
?d_007e4ad0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 0F9h, 83h, 0C8h, 0FFh, 8Dh, 77h, 1Ch, 8Bh, 0CEh, 89h
    db 47h, 48h, 89h, 47h, 4Ch, 0E8h, 8Dh, 0CFh, 82h, 0FFh, 8Dh, 44h, 24h, 0Bh, 50h, 8Dh
    db 4Ch, 24h, 14h, 51h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0E8h, 0Ah, 81h, 84h, 0FFh
    db 84h, 0C0h, 74h, 3Eh, 8Bh, 44h, 24h, 0Ch, 3Dh, 41h, 56h, 50h, 36h, 75h, 09h, 8Bh
    db 0CEh, 0E8h, 30h, 36h, 84h, 0FFh, 0EBh, 07h, 3Dh, 4Dh, 56h, 68h, 64h, 74h, 1Ch, 8Dh
    db 44h, 24h, 0Bh, 50h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh
    db 0E8h, 0D5h, 80h, 84h, 0FFh, 84h, 0C0h, 75h, 0CBh, 0EBh, 07h, 8Bh, 0CEh, 0E8h, 04h, 36h
    db 84h, 0FFh, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 08h, 0FFh, 15h, 44h, 95h, 35h, 01h, 89h
    db 47h, 50h, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C3h
?d_007e4ad0@@YAXXZ ENDP

; ghidra: FUN_00be4b80  retail @ 0x007E4B80 size 320
public ?d_007e4b80@@YAXXZ
?d_007e4b80@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 0FFh, 50h, 34h, 8Ah, 0D8h, 8Bh
    db 46h, 48h, 0F6h, 0DBh, 1Bh, 0DBh, 83h, 0E3h, 02h, 85h, 0C0h, 7Dh, 07h, 8Bh, 16h, 8Bh
    db 0CEh, 0FFh, 52h, 08h, 8Bh, 44h, 24h, 20h, 8Bh, 0F8h, 83h, 0E7h, 04h, 89h, 7Ch, 24h
    db 14h, 75h, 09h, 0F6h, 0C3h, 02h, 0Fh, 85h, 0F9h, 00h, 00h, 00h, 8Bh, 16h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 14h, 84h, 0C0h, 0Fh, 84h, 0E9h, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h
    db 55h, 50h, 8Bh, 0CEh, 0E8h, 0D2h, 44h, 83h, 0FFh, 8Bh, 0E8h, 0A0h, 38h, 98h, 30h, 01h
    db 84h, 0C0h, 89h, 6Ch, 24h, 1Ch, 75h, 0Bh, 85h, 0FFh, 75h, 07h, 0F6h, 44h, 24h, 24h
    db 40h, 74h, 5Fh, 8Bh, 4Eh, 44h, 8Bh, 56h, 40h, 89h, 4Ch, 24h, 14h, 89h, 54h, 24h
    db 10h, 0FFh, 15h, 44h, 95h, 35h, 01h, 8Bh, 0F8h, 8Bh, 44h, 24h, 14h, 69h, 0C0h, 0E8h
    db 03h, 00h, 00h, 0F7h, 0EDh, 8Bh, 0C8h, 8Bh, 44h, 24h, 10h, 8Bh, 0EAh, 99h, 52h, 50h
    db 55h, 51h, 0E8h, 0B9h, 24h, 21h, 00h, 2Bh, 0F8h, 8Bh, 44h, 24h, 10h, 99h, 0F7h, 7Ch
    db 24h, 14h, 8Bh, 6Eh, 50h, 8Bh, 0C8h, 0B8h, 0E8h, 03h, 00h, 00h, 99h, 0F7h, 0F9h, 8Bh
    db 0D7h, 2Bh, 0D5h, 8Bh, 6Ch, 24h, 1Ch, 3Bh, 0D0h, 7Eh, 03h, 89h, 7Eh, 50h, 8Bh, 7Ch
    db 24h, 18h, 39h, 6Eh, 48h, 7Dh, 20h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 34h, 84h, 0C0h
    db 75h, 15h, 85h, 0FFh, 75h, 11h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 8Bh, 46h, 48h
    db 83h, 0CBh, 04h, 3Bh, 0C5h, 7Ch, 0E0h, 0F6h, 44h, 24h, 24h, 01h, 5Dh, 75h, 36h, 8Bh
    db 46h, 4Ch, 3Bh, 46h, 48h, 74h, 2Eh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 8Bh, 4Eh
    db 2Ch, 8Bh, 01h, 0FFh, 10h, 8Bh, 16h, 8Bh, 0CEh, 83h, 0CBh, 01h, 0FFh, 52h, 08h, 85h
    db 0FFh, 74h, 12h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 34h, 84h, 0C0h, 74h, 07h, 8Bh, 0CEh
    db 0E8h, 0E6h, 0B1h, 84h, 0FFh, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_007e4b80@@YAXXZ ENDP

; ghidra: FUN_00be4d40  retail @ 0x007E4D40 size 666
_TEXT ENDS
_TEXT$d00be4d40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE4D40 size 666
public ?d_007e4d40@@YAXXZ
?d_007e4d40@@YAXXZ PROC
    db 051h, 053h, 055h, 056h, 057h
    call ?init@VideoPlayer@@UAEXXZ
    db 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 081h, 0C0h, 00Dh, 000h, 000h, 085h, 0C0h, 08Bh, 035h
    dd __imp__sprintf
    db 0B3h, 001h, 074h, 056h, 066h, 083h, 078h, 004h, 000h, 074h, 04Fh, 088h, 01Dh
    dd g_Va01309848
    db 08Bh, 089h, 0C0h, 00Dh, 000h, 000h, 085h, 0C9h, 08Dh, 041h, 008h, 075h, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 068h
    dd g_Va01128E80
    db 050h, 068h
    dd g_Va01128E78
    db 068h
    dd g_Va01309849
    db 0FFh, 0D6h, 0A1h
    dd g_Va01128E6C
    db 08Bh, 00Dh
    dd g_Va01128E70
    db 08Ah, 015h
    dd g_Va01128E74
    db 083h, 0C4h, 010h, 0A3h
    dd g_Va0130994D
    db 089h, 00Dh
    dd g_Va01309951
    db 088h, 015h
    dd g_Va01309955
    db 08Dh, 044h, 024h, 010h, 050h, 088h, 01Dh
    dd g_Va0130998D
    call ?j_000132af@@YAXXZ
    db 08Bh, 000h, 083h, 0C4h, 004h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 068h
    dd g_Va01128E50
    db 068h
    dd g_Va0130998E
    db 0FFh, 0D6h, 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 00Dh
    dd g_Va01128E3C
    db 08Bh, 015h
    dd g_Va01128E40
    db 0A1h
    dd g_Va01128E44
    db 068h
    dd g_Va01128E80
    db 089h, 00Dh
    dd g_Va01309A92
    db 066h, 08Bh, 00Dh
    dd g_Va01128E48
    db 089h, 015h
    dd g_Va01309A96
    db 08Ah, 015h
    dd g_Va01128E4A
    db 068h
    dd g_Va010F6384
    db 068h
    dd g_Va01309AD3
    db 0A3h
    dd g_Va01309A9A
    db 066h, 089h, 00Dh
    dd g_Va01309A9E
    db 088h, 015h
    dd g_Va01309AA0
    db 088h, 01Dh
    dd g_Va01309AD2
    db 0FFh, 0D6h, 0A1h
    dd g_Va01128E24
    db 08Bh, 00Dh
    dd g_Va01128E28
    db 08Bh, 015h
    dd g_Va01128E2C
    db 0A3h
    dd g_Va01309BD7
    db 0A1h
    dd g_Va01128E30
    db 089h, 00Dh
    dd g_Va01309BDB
    db 066h, 08Bh, 00Dh
    dd g_Va01128E34
    db 089h, 015h
    dd g_Va01309BDF
    db 08Ah, 015h
    dd g_Va01128E36
    db 068h
    dd ?TheBfmeObject_00C70BC0@@3VGen_00C70BC0Target@@A
    db 0A3h
    dd g_Va01309BE3
    db 066h, 089h, 00Dh
    dd g_Va01309BE7
    db 088h, 015h
    dd g_Va01309BE9
    call ?store@Rva009A58C0@@SAXH@Z
    db 083h, 0C4h, 010h
    call ?Rva009A4D00Init@@YAXXZ
    db 033h, 0F6h, 08Dh, 086h, 000h, 0FFh, 0FFh, 0FFh, 089h, 044h, 024h, 010h, 0DBh, 044h, 024h, 010h
    db 0D8h, 00Dh
    dd __real@3f99999a
    db 0D8h, 025h
    dd ?g_rva001077D0RefreshDelay@@3MA
    call __ftol2
    db 03Dh, 0FFh, 000h, 000h, 000h, 07Eh, 007h, 0B9h, 0FFh, 000h, 000h, 000h, 0EBh, 00Ah, 033h, 0C9h
    db 085h, 0C0h, 00Fh, 09Ch, 0C1h, 049h, 023h, 0C8h, 00Fh, 0B6h, 0C9h, 089h, 00Ch, 0B5h
    dd g_Va01308838
    db 046h, 081h, 0FEh, 000h, 004h, 000h, 000h, 072h, 0B6h, 0BBh, 017h, 0E9h, 0FFh, 0FFh, 0BDh, 080h
    db 050h, 0FFh, 0FFh, 0BFh, 080h, 022h, 0FFh, 0FFh, 0C7h, 044h, 024h, 010h, 080h, 059h, 000h, 000h
    db 0BEh, 000h, 02Bh, 000h, 000h, 033h, 0C9h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 0C7h
    db 099h, 081h, 0E2h, 0FFh, 000h, 000h, 000h, 003h, 0C2h, 0C1h, 0F8h, 008h, 005h, 000h, 001h, 000h
    db 000h, 089h, 081h
    dd g_Va01308438
    db 08Bh, 0C6h, 099h, 081h, 0E2h, 0FFh, 000h, 000h, 000h, 003h, 0C2h, 0C1h, 0F8h, 008h, 089h, 081h
    dd g_Va01308038
    db 08Bh, 044h, 024h, 010h, 099h, 081h, 0E2h, 0FFh, 000h, 000h, 000h, 003h, 0C2h, 0C1h, 0F8h, 008h
    db 005h, 000h, 001h, 000h, 000h, 089h, 081h
    dd g_Va01307C38
    db 08Bh, 0C5h, 099h, 081h, 0E2h, 0FFh, 000h, 000h, 000h, 003h, 0C2h, 0C1h, 0F8h, 008h, 005h, 000h
    db 001h, 000h, 000h, 089h, 081h
    dd g_Va01307838
    db 0B8h, 07Dh, 063h, 0DAh, 004h, 0F7h, 0EBh, 0C1h, 0FAh, 002h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h
    db 0C2h, 03Dh, 0FFh, 000h, 000h, 000h, 07Eh, 007h, 0B8h, 0FFh, 000h, 000h, 000h, 0EBh, 00Ah, 033h
    db 0D2h, 085h, 0C0h, 00Fh, 09Ch, 0C2h, 04Ah, 023h, 0C2h, 0C1h, 0E0h, 018h, 089h, 081h
    dd g_Va01307438
    db 08Bh, 044h, 024h, 010h, 083h, 0EEh, 056h, 02Dh, 0B3h, 000h, 000h, 000h, 081h, 0C7h, 0BBh, 001h
    db 000h, 000h, 081h, 0C5h, 05Fh, 001h, 000h, 000h, 081h, 0C3h, 0FFh, 000h, 000h, 000h, 083h, 0C1h
    db 004h, 081h, 0FEh, 000h, 0D5h, 0FFh, 0FFh, 089h, 044h, 024h, 010h, 00Fh, 08Fh, 03Ch, 0FFh, 0FFh
    db 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 059h, 0C3h
?d_007e4d40@@YAXXZ ENDP
_TEXT$d00be4d40 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
