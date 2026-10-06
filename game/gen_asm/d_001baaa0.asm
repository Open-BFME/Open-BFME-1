.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??_7DamageInfo@@6B@:BYTE
EXTERN ??_7DamageInfoInput@@6B@:BYTE
EXTERN ??_7DamageInfoOutput@@6B@:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Radar00598950@@3PAVBfmeThingAOA@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheBfmeGenAE@@3PAVBfmeGenAE@@A:BYTE
EXTERN ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A:BYTE
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?g_guardTargetTypeThrowInfo@@3HA:BYTE
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000335f@@YAXXZ:NEAR
EXTERN ?j_00005a7e@@YAXXZ:NEAR
EXTERN ?j_00008ca1@@YAXXZ:NEAR
EXTERN ?j_00008e72@@YAXXZ:NEAR
EXTERN ?j_00009025@@YAXXZ:NEAR
EXTERN ?j_00009b01@@YAXXZ:NEAR
EXTERN ?j_0000b81b@@YAXXZ:NEAR
EXTERN ?j_0000c9b4@@YAXXZ:NEAR
EXTERN ?j_0000db61@@YAXXZ:NEAR
EXTERN ?j_0000e570@@YAXXZ:NEAR
EXTERN ?j_00020176@@YAXXZ:NEAR
EXTERN ?j_000251e4@@YAXXZ:NEAR
EXTERN ?j_00026dd7@@YAXXZ:NEAR
EXTERN ?j_0002aa8b@@YAXXZ:NEAR
EXTERN ?j_0002c566@@YAXXZ:NEAR
EXTERN ?j_0002fc1b@@YAXXZ:NEAR
EXTERN ?j_00031656@@YAXXZ:NEAR
EXTERN ?j_00032ee8@@YAXXZ:NEAR
EXTERN ?j_00033fcd@@YAXXZ:NEAR
EXTERN ?j_00034815@@YAXXZ:NEAR
EXTERN ?j_00035814@@YAXXZ:NEAR
EXTERN ?j_00035a0d@@YAXXZ:NEAR
EXTERN ?j_000361ce@@YAXXZ:NEAR
EXTERN ?j_000394be@@YAXXZ:NEAR
EXTERN ?j_0003EC7A@@YAXXZ:NEAR
EXTERN ?j_0003add7@@YAXXZ:NEAR
EXTERN ?j_0003c8e9@@YAXXZ:NEAR
EXTERN ?j_0003f75b@@YAXXZ:NEAR
EXTERN ?j_0003fbcf@@YAXXZ:NEAR
EXTERN ?j_00044c2e@@YAXXZ:NEAR
EXTERN ?j_00044ce7@@YAXXZ:NEAR
EXTERN ?j_00049945@@YAXXZ:NEAR
EXTERN ?ji_009f6d00@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN _bfmeFormatText:NEAR
EXTERN g_Va0100994C:NEAR
EXTERN g_Va0109CB8C:BYTE
_TEXT SEGMENT

; retail @ 0x001BAAA0 size 576
public ?d_001baaa0@@YAXXZ
?d_001baaa0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 40h, 8Ch, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 55h, 56h, 8Bh, 74h, 24h, 30h, 8Bh, 06h
    db 8Bh, 0E9h, 8Bh, 0CEh, 89h, 6Ch, 24h, 18h, 0FFh, 50h, 10h, 84h, 0C0h, 0Fh, 85h, 0DAh
    db 01h, 00h, 00h, 8Bh, 16h, 53h, 57h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0C6h, 44h
    db 24h, 18h, 01h, 0C6h, 44h, 24h, 19h, 01h, 0FFh, 52h, 28h, 8Bh, 55h, 04h, 8Bh, 4Dh
    db 08h, 8Dh, 7Dh, 04h, 2Bh, 0CAh, 8Bh, 16h, 0C1h, 0F9h, 02h, 8Dh, 44h, 24h, 10h, 89h
    db 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 7Ch, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h
    db 84h, 0C0h, 74h, 56h, 8Bh, 3Fh, 3Bh, 7Dh, 08h, 0Fh, 84h, 73h, 01h, 00h, 00h, 90h
    db 8Bh, 1Fh, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CBh, 0E8h, 58h, 0C8h, 0E6h, 0FFh, 8Bh, 16h
    db 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0FFh
    db 52h, 68h, 8Bh, 16h, 53h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h
    db 24h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0E5h, 0CDh, 6Ch, 00h, 8Bh, 45h, 08h, 83h, 0C7h
    db 04h, 3Bh, 0F8h, 75h, 0BBh, 0E9h, 28h, 01h, 00h, 00h, 8Bh, 07h, 3Bh, 47h, 04h, 74h
    db 20h, 6Ah, 00h, 8Dh, 4Ch, 24h, 24h, 6Ah, 04h, 51h, 0E8h, 0A1h, 0B6h, 81h, 00h, 83h
    db 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h, 24h, 52h, 0E8h, 6Fh, 0C1h, 83h
    db 00h, 66h, 83h, 7Ch, 24h, 10h, 00h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0Fh
    db 86h, 0EDh, 00h, 00h, 00h, 0EBh, 09h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0FFh
    db 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h, 8Bh, 06h, 8Dh, 4Ch, 24h, 38h, 51h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 34h, 01h, 00h, 00h, 00h, 0FFh, 50h, 68h, 8Bh, 44h, 24h, 38h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh
    db 00h, 0D6h, 2Eh, 01h, 50h, 0E8h, 0EDh, 01h, 0E8h, 0FFh, 85h, 0C0h, 89h, 44h, 24h, 18h
    db 0Fh, 84h, 0CAh, 00h, 00h, 00h, 8Bh, 2Dh, 04h, 0F5h, 2Eh, 01h, 8Dh, 54h, 24h, 18h
    db 52h, 8Dh, 44h, 24h, 20h, 8Dh, 5Dh, 08h, 50h, 8Bh, 0CBh, 0E8h, 0F9h, 2Eh, 0E8h, 0FFh
    db 8Bh, 1Bh, 8Bh, 44h, 24h, 1Ch, 3Bh, 0C3h, 0Fh, 84h, 0A2h, 00h, 00h, 00h, 8Bh, 40h
    db 14h, 85h, 0C0h, 0Fh, 84h, 97h, 00h, 00h, 00h, 50h, 8Bh, 0CDh, 0E8h, 0B0h, 6Dh, 0E5h
    db 0FFh, 8Bh, 16h, 8Bh, 0D8h, 53h, 8Bh, 0CEh, 89h, 5Ch, 24h, 1Ch, 0FFh, 52h, 30h, 8Bh
    db 47h, 04h, 3Bh, 47h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 18h, 83h, 47h, 04h
    db 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 40h, 51h, 8Dh, 54h, 24h, 24h
    db 52h, 50h, 8Bh, 0CFh, 0E8h, 25h, 22h, 0E8h, 0FFh, 8Dh, 4Ch, 24h, 38h, 0C7h, 44h, 24h
    db 30h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0C6h, 0CCh, 6Ch, 00h, 8Bh, 44h, 24h, 14h, 40h, 66h
    db 3Bh, 44h, 24h, 10h, 89h, 44h, 24h, 14h, 0Fh, 82h, 22h, 0FFh, 0FFh, 0FFh, 8Bh, 6Ch
    db 24h, 20h, 8Bh, 16h, 8Dh, 45h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 83h
    db 0C5h, 14h, 55h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 5Fh, 5Bh, 8Bh, 4Ch, 24h
    db 20h, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h
    db 6Ah, 00h, 8Dh, 44h, 24h, 24h, 6Ah, 05h, 50h, 0E8h, 52h, 0B5h, 81h, 00h, 83h, 0C4h
    db 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 4Ch, 24h, 24h, 51h, 0E8h, 20h, 0C0h, 83h, 00h
?d_001baaa0@@YAXXZ ENDP

; retail @ 0x001C4CC0 size 460
public ?d_001c4cc0@@YAXXZ
?d_001c4cc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 40h, 8Fh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 56h, 8Bh, 74h, 24h, 2Ch, 8Bh, 06h, 57h
    db 8Bh, 0F9h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h
    db 24h, 11h, 01h, 0FFh, 50h, 28h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 10h, 84h, 0C0h, 74h
    db 1Bh, 56h, 8Bh, 0CFh, 0E8h, 0BAh, 0DDh, 0E7h, 0FFh, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 18h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 8Bh, 06h, 53h, 55h
    db 8Bh, 0CEh, 0FFh, 50h, 08h, 84h, 0C0h, 0Fh, 84h, 0A5h, 00h, 00h, 00h, 8Dh, 4Fh, 04h
    db 33h, 0D2h, 3Bh, 0F9h, 8Bh, 0C7h, 73h, 19h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 18h, 0Fh, 0B6h, 9Bh, 28h, 71h, 2Ch, 01h, 03h, 0D3h, 40h, 3Bh, 0C1h, 72h
    db 0EFh, 8Dh, 44h, 24h, 38h, 89h, 54h, 24h, 38h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 78h, 33h, 0EDh, 83h, 0CBh, 0FFh, 8Bh, 07h, 8Bh, 0CDh, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h
    db 00h, 00h, 0D3h, 0E2h, 85h, 0D0h, 74h, 3Fh, 8Bh, 04h, 0ADh, 00h, 92h, 2Ah, 01h, 85h
    db 0C0h, 74h, 34h, 50h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 33h, 3Eh, 6Ch, 00h, 8Bh, 06h, 8Dh
    db 4Ch, 24h, 18h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0FFh, 50h
    db 68h, 8Bh, 44h, 24h, 38h, 48h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 38h, 89h, 5Ch
    db 24h, 30h, 0E8h, 89h, 2Bh, 6Ch, 00h, 45h, 83h, 0FDh, 0Bh, 7Ch, 0A9h, 5Dh, 5Bh, 5Fh
    db 5Eh, 8Bh, 4Ch, 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h
    db 04h, 00h, 8Dh, 44h, 24h, 1Ch, 0C7h, 07h, 00h, 00h, 00h, 00h, 8Bh, 16h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 78h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch
    db 33h, 0EDh, 85h, 0C0h, 0C7h, 44h, 24h, 30h, 01h, 00h, 00h, 00h, 7Eh, 48h, 8Bh, 0FFh
    db 8Bh, 16h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 44h, 24h, 10h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h
    db 8Ah, 63h, 0E4h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 7Ch, 41h, 8Bh, 1Fh, 8Bh, 0C8h, 8Bh
    db 44h, 24h, 1Ch, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 0Bh, 0DAh, 45h
    db 3Bh, 0E8h, 89h, 1Fh, 7Ch, 0BAh, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0E9h, 2Ah, 6Ch, 00h, 8Bh, 4Ch, 24h, 28h, 5Dh, 5Bh, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 6Ah, 00h, 8Dh, 44h
    db 24h, 24h, 6Ah, 00h, 50h, 0E8h, 0A6h, 13h, 81h, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh
    db 1Dh, 01h, 8Dh, 4Ch, 24h, 24h, 51h, 0E8h, 74h, 1Eh, 83h, 00h
?d_001c4cc0@@YAXXZ ENDP

; retail @ 0x001C50B0 size 460
public ?d_001c50b0@@YAXXZ
?d_001c50b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 60h, 8Fh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 56h, 8Bh, 74h, 24h, 2Ch, 8Bh, 06h, 57h
    db 8Bh, 0F9h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h
    db 24h, 11h, 01h, 0FFh, 50h, 28h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 10h, 84h, 0C0h, 74h
    db 1Bh, 56h, 8Bh, 0CFh, 0E8h, 0C5h, 0E4h, 0E6h, 0FFh, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 18h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 8Bh, 06h, 53h, 55h
    db 8Bh, 0CEh, 0FFh, 50h, 08h, 84h, 0C0h, 0Fh, 84h, 0A5h, 00h, 00h, 00h, 8Dh, 4Fh, 04h
    db 33h, 0D2h, 3Bh, 0F9h, 8Bh, 0C7h, 73h, 19h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 18h, 0Fh, 0B6h, 9Bh, 28h, 71h, 2Ch, 01h, 03h, 0D3h, 40h, 3Bh, 0C1h, 72h
    db 0EFh, 8Dh, 44h, 24h, 38h, 89h, 54h, 24h, 38h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 78h, 33h, 0EDh, 83h, 0CBh, 0FFh, 8Bh, 07h, 8Bh, 0CDh, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h
    db 00h, 00h, 0D3h, 0E2h, 85h, 0D0h, 74h, 3Fh, 8Bh, 04h, 0ADh, 0B0h, 0D6h, 2Ah, 01h, 85h
    db 0C0h, 74h, 34h, 50h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 43h, 3Ah, 6Ch, 00h, 8Bh, 06h, 8Dh
    db 4Ch, 24h, 18h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0FFh, 50h
    db 68h, 8Bh, 44h, 24h, 38h, 48h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 38h, 89h, 5Ch
    db 24h, 30h, 0E8h, 99h, 27h, 6Ch, 00h, 45h, 83h, 0FDh, 1Dh, 7Ch, 0A9h, 5Dh, 5Bh, 5Fh
    db 5Eh, 8Bh, 4Ch, 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h
    db 04h, 00h, 8Dh, 44h, 24h, 1Ch, 0C7h, 07h, 00h, 00h, 00h, 00h, 8Bh, 16h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 78h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch
    db 33h, 0EDh, 85h, 0C0h, 0C7h, 44h, 24h, 30h, 01h, 00h, 00h, 00h, 7Eh, 48h, 8Bh, 0FFh
    db 8Bh, 16h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 44h, 24h, 10h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h
    db 0B8h, 00h, 0E4h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 7Ch, 41h, 8Bh, 1Fh, 8Bh, 0C8h, 8Bh
    db 44h, 24h, 1Ch, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 0Bh, 0DAh, 45h
    db 3Bh, 0E8h, 89h, 1Fh, 7Ch, 0BAh, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0F9h, 26h, 6Ch, 00h, 8Bh, 4Ch, 24h, 28h, 5Dh, 5Bh, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 6Ah, 00h, 8Dh, 44h
    db 24h, 24h, 6Ah, 00h, 50h, 0E8h, 0B6h, 0Fh, 81h, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh
    db 1Dh, 01h, 8Dh, 4Ch, 24h, 24h, 51h, 0E8h, 84h, 1Ah, 83h, 00h
?d_001c50b0@@YAXXZ ENDP

; retail @ 0x001CB270 size 496
public ?d_001cb270@@YAXXZ
?d_001cb270@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 30h, 91h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 55h, 8Bh, 0E9h, 56h, 8Bh, 74h, 24h, 30h
    db 8Bh, 06h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h
    db 24h, 11h, 01h, 0FFh, 50h, 28h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 10h, 84h, 0C0h, 74h
    db 1Bh, 56h, 8Bh, 0CDh, 0E8h, 21h, 0Fh, 0E4h, 0FFh, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 18h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 8Bh, 06h, 57h, 8Bh
    db 0CEh, 0FFh, 50h, 08h, 33h, 0D2h, 84h, 0C0h, 8Bh, 0C5h, 0Fh, 84h, 0ACh, 00h, 00h, 00h
    db 8Dh, 4Dh, 28h, 3Bh, 0E9h, 73h, 1Ah, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 38h, 0Fh, 0B6h, 0BFh, 28h, 71h, 2Ch, 01h, 03h, 0D7h, 40h, 3Bh, 0C1h, 72h
    db 0EFh, 8Dh, 44h, 24h, 34h, 89h, 54h, 24h, 34h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 78h, 33h, 0FFh, 8Bh, 0CFh, 0C1h, 0E9h, 05h, 8Bh, 44h, 8Dh, 00h, 8Bh, 0CFh, 83h, 0E1h
    db 1Fh, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 85h, 0D0h, 74h, 43h, 8Bh, 04h, 0BDh, 18h
    db 69h, 2Ah, 01h, 85h, 0C0h, 74h, 38h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h, 7Fh, 0D8h, 6Bh
    db 00h, 8Bh, 06h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 00h, 00h
    db 00h, 00h, 0FFh, 50h, 68h, 8Bh, 44h, 24h, 34h, 48h, 8Dh, 4Ch, 24h, 14h, 89h, 44h
    db 24h, 34h, 0C7h, 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D1h, 0C5h, 6Bh, 00h, 47h
    db 81h, 0FFh, 30h, 01h, 00h, 00h, 7Ch, 9Bh, 5Fh, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 18h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 89h, 10h, 89h, 50h
    db 04h, 89h, 50h, 08h, 89h, 50h, 0Ch, 89h, 50h, 10h, 89h, 50h, 14h, 89h, 50h, 18h
    db 89h, 50h, 1Ch, 89h, 50h, 20h, 89h, 50h, 24h, 8Bh, 16h, 8Dh, 44h, 24h, 18h, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 78h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 18h, 33h, 0FFh, 85h, 0C0h, 0C7h, 44h, 24h, 2Ch, 01h, 00h, 00h, 00h, 7Eh, 4Ch, 90h
    db 8Bh, 16h, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 44h, 24h, 0Ch
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h
    db 0FDh, 0DCh, 0E4h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 7Ch, 45h, 8Bh, 0C8h, 0C1h, 0E9h, 05h
    db 8Dh, 54h, 8Dh, 00h, 8Bh, 0C8h, 83h, 0E1h, 1Fh, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h
    db 09h, 02h, 8Bh, 44h, 24h, 18h, 47h, 3Bh, 0F8h, 7Ch, 0B5h, 8Dh, 4Ch, 24h, 0Ch, 0C7h
    db 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 14h, 0C5h, 6Bh, 00h, 8Bh, 4Ch, 24h, 24h
    db 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 20h, 6Ah, 00h, 51h, 0E8h, 0D2h, 0ADh, 80h, 00h, 83h, 0C4h
    db 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h, 20h, 52h, 0E8h, 0A0h, 0B8h, 82h, 00h
?d_001cb270@@YAXXZ ENDP

; retail @ 0x001D48A0 size 3988
_TEXT ENDS
_TEXT$d005d48a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005D48A0 size 3988
public ?d_001d48a0@@YAXXZ
?d_001d48a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0100994C
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 0A4h, 000h, 000h, 000h, 053h, 055h, 056h, 08Bh, 0B4h, 024h, 0C0h, 000h, 000h, 000h, 08Bh, 006h
    db 057h, 08Bh, 0F9h, 08Dh, 04Ch, 024h, 014h, 051h, 08Bh, 0CEh, 0C6h, 044h, 024h, 018h, 001h, 0C6h
    db 044h, 024h, 019h, 00Bh, 0FFh, 050h, 028h, 08Bh, 016h, 08Dh, 087h, 0E8h, 001h, 000h, 000h, 050h
    db 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Ah, 0D8h, 08Bh, 047h
    db 0A4h, 0F6h, 0DBh, 01Ah, 0DBh, 0FEh, 0C3h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h
    db 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 083h, 0C0h, 020h, 050h, 08Dh, 04Ch, 024h, 034h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 006h, 08Dh, 04Ch, 024h, 030h, 051h, 08Bh, 0CEh, 0C7h, 084h, 024h, 0C0h, 000h, 000h, 000h
    db 000h, 000h, 000h, 000h, 0FFh, 050h, 068h, 08Bh, 057h, 014h, 08Dh, 044h, 024h, 048h, 050h, 056h
    db 089h, 054h, 024h, 050h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 04Ch, 024h, 050h, 08Bh, 047h, 014h, 08Dh, 06Fh, 0A0h, 083h, 0C4h, 008h, 03Bh, 0C1h, 08Bh
    db 0D1h, 089h, 054h, 024h, 010h, 089h, 06Ch, 024h, 024h, 074h, 027h, 085h, 0C0h, 074h, 010h, 08Bh
    db 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 055h
    call ?j_00031656@@YAXXZ
    db 08Bh, 054h, 024h, 010h, 085h, 0D2h, 089h, 055h, 074h, 074h, 00Ch, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 055h
    call ?j_00033fcd@@YAXXZ
    db 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 010h, 084h, 0C0h, 075h, 07Fh, 08Bh, 047h, 0A8h, 08Bh, 04Fh
    db 0ACh, 08Bh, 057h, 0B0h, 089h, 044h, 024h, 058h, 08Bh, 047h, 0B4h, 089h, 044h, 024h, 064h, 08Bh
    db 047h, 0C0h, 089h, 04Ch, 024h, 05Ch, 08Bh, 04Fh, 0B8h, 089h, 054h, 024h, 060h, 08Bh, 057h, 0BCh
    db 089h, 044h, 024h, 070h, 08Bh, 047h, 0CCh, 089h, 04Ch, 024h, 068h, 08Bh, 04Fh, 0C4h, 089h, 054h
    db 024h, 06Ch, 08Bh, 057h, 0C8h, 089h, 044h, 024h, 07Ch, 08Dh, 044h, 024h, 058h, 089h, 04Ch, 024h
    db 074h, 08Bh, 04Fh, 0D0h, 089h, 054h, 024h, 078h, 08Bh, 057h, 0D4h, 050h, 056h, 089h, 08Ch, 024h
    db 088h, 000h, 000h, 000h, 089h, 094h, 024h, 08Ch, 000h, 000h, 000h
    call ?j_00034815@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 00Ch, 08Dh, 044h
    db 024h, 058h, 050h, 08Bh, 0CDh
    call ?j_000361ce@@YAXXZ
    db 08Bh, 016h, 08Dh, 087h, 0E4h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 084h, 000h, 000h
    db 000h, 084h, 0DBh, 074h, 012h, 08Dh, 087h, 0C4h, 001h, 000h, 000h, 050h, 056h
    call ?j_00035814@@YAXXZ
    db 083h, 0C4h, 008h, 0EBh, 00Ch, 056h, 08Dh, 08Fh, 0C4h, 001h, 000h, 000h
    call ?j_0000335f@@YAXXZ
    db 08Bh, 087h, 0B0h, 001h, 000h, 000h, 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 030h, 08Bh, 016h
    db 08Dh, 087h, 040h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh, 016h, 08Bh, 0CEh
    db 0FFh, 052h, 010h, 084h, 0C0h, 00Fh, 084h, 081h, 001h, 000h, 000h, 08Bh, 08Fh, 0A0h, 001h, 000h
    db 000h, 08Bh, 001h, 0FFh, 050h, 010h, 0D9h, 05Ch, 024h, 018h, 08Bh, 016h, 08Dh, 044h, 024h, 018h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 08Fh, 0A0h, 001h, 000h, 000h, 08Bh, 011h, 0FFh, 052h
    db 06Ch, 0D9h, 05Ch, 024h, 038h, 08Bh, 006h, 08Dh, 04Ch, 024h, 038h, 051h, 08Bh, 0CEh, 0FFh, 050h
    db 06Ch, 08Dh, 057h, 018h, 052h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Dh, 047h, 01Ch, 050h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 010h, 08Dh, 087h, 0A4h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 05Ch, 08Bh, 016h, 08Dh, 047h, 03Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 04Ch, 08Bh, 016h, 08Dh, 047h
    db 044h, 050h, 08Bh, 0CEh, 0FFh, 052h, 04Ch, 08Bh, 016h, 08Dh, 087h, 0E0h, 001h, 000h, 000h, 050h
    db 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 09Fh, 0A4h, 001h, 000h, 000h, 085h, 0DBh, 00Fh, 084h, 0C7h
    db 000h, 000h, 000h, 08Dh, 04Ch, 024h, 024h, 051h, 08Bh, 0CBh
    call ?j_00020176@@YAXXZ
    db 08Bh, 016h, 08Dh, 044h, 024h, 024h, 050h, 08Bh, 0CEh, 0C6h, 084h, 024h, 0C0h, 000h, 000h, 000h
    db 001h, 0FFh, 052h, 068h, 08Bh, 043h, 030h, 08Bh, 040h, 01Ch, 085h, 0C0h, 074h, 005h, 08Bh, 040h
    db 004h, 0EBh, 005h, 0B8h, 03Fh, 042h, 00Fh, 000h, 08Bh, 016h, 089h, 044h, 024h, 010h, 08Dh, 044h
    db 024h, 010h, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh, 04Bh, 030h
    call ?j_0000e570@@YAXXZ
    db 085h, 0C0h, 074h, 00Dh, 08Bh, 04Bh, 030h
    call ?j_0000e570@@YAXXZ
    db 08Bh, 040h, 074h, 0EBh, 002h, 033h, 0C0h, 08Dh, 04Ch, 024h, 01Ch, 051h, 056h, 089h, 044h, 024h
    db 024h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 05Bh, 030h, 08Dh, 053h, 024h, 083h, 0C4h, 008h, 085h, 0D2h, 074h, 017h, 08Bh, 043h, 024h
    db 089h, 044h, 024h, 03Ch, 08Bh, 04Bh, 028h, 089h, 04Ch, 024h, 040h, 08Bh, 053h, 02Ch, 089h, 054h
    db 024h, 044h, 0EBh, 018h, 0C7h, 044h, 024h, 03Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 040h
    db 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 044h, 000h, 000h, 000h, 000h, 08Bh, 006h, 08Dh, 04Ch
    db 024h, 03Ch, 051h, 08Bh, 0CEh, 0FFh, 050h, 060h, 08Dh, 04Ch, 024h, 024h, 0C6h, 084h, 024h, 0BCh
    db 000h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0DBh, 081h, 0C7h, 004h, 002h, 000h, 000h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 053h, 08Bh
    db 0CFh
    call ?j_0003c8e9@@YAXXZ
    db 085h, 0C0h, 074h, 008h, 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 030h, 043h, 083h, 0FBh, 004h
    db 07Ch, 0E6h, 0E9h, 0F7h, 00Bh, 000h, 000h, 08Bh, 087h, 0DCh, 001h, 000h, 000h, 085h, 0C0h, 074h
    db 005h, 08Bh, 040h, 008h, 0EBh, 002h, 033h, 0C0h, 08Dh, 04Ch, 024h, 04Ch, 089h, 044h, 024h, 04Ch
    db 08Bh, 006h, 051h, 08Bh, 0CEh, 0FFh, 050h, 074h, 08Dh, 057h, 018h, 052h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Dh, 047h, 01Ch, 050h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 055h, 000h, 083h, 0C4h, 010h, 08Bh, 0CDh, 0FFh, 052h, 028h, 08Bh, 0D8h, 085h, 0DBh, 074h
    db 00Dh, 08Bh, 0CBh
    call ?j_00009b01@@YAXXZ
    db 089h, 044h, 024h, 034h, 0EBh, 008h, 0C7h, 044h, 024h, 034h, 000h, 000h, 000h, 000h, 08Bh, 006h
    db 08Bh, 0CEh, 0FFh, 050h, 00Ch, 084h, 0C0h, 075h, 00Eh, 08Dh, 04Ch, 024h, 034h, 051h, 056h
    call ?j_00008ca1@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 02Eh, 085h, 0DBh
    db 075h, 01Eh, 053h, 08Dh, 044h, 024h, 054h, 053h, 050h
    call _bfmeFormatText
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_guardTargetTypeThrowInfo@@3HA
    db 08Dh, 04Ch, 024h, 054h, 051h
    call ?ji_009f6d00@@YAXXZ
    db 08Bh, 054h, 024h, 034h, 052h, 08Bh, 0CBh
    call ?j_00005a7e@@YAXXZ
    db 08Bh, 006h, 08Dh, 04Fh, 024h, 051h, 08Bh, 0CEh, 0FFh, 050h, 068h, 056h, 08Dh, 04Fh, 030h
    call ?j_00035a0d@@YAXXZ
    db 08Bh, 016h, 08Dh, 047h, 03Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 04Ch, 08Bh, 016h, 08Dh, 047h, 044h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 04Ch, 056h, 08Dh, 08Fh, 0B0h, 000h, 000h, 000h
    call ?j_00026dd7@@YAXXZ
    db 08Bh, 016h, 08Dh, 087h, 0E3h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 084h, 000h, 000h
    db 000h, 08Bh, 016h, 08Dh, 087h, 00Ch, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh
    db 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 03Dh, 08Bh, 044h, 024h, 04Ch, 08Bh, 00Dh
    dd ?TheBfmeTeamFactory@@3PAVRva002BD630TeamFactory@@A
    db 050h
    call ?j_00044c2e@@YAXXZ
    db 085h, 0C0h, 075h, 01Fh, 050h, 08Dh, 04Ch, 024h, 054h, 06Ah, 005h, 051h
    call _bfmeFormatText
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_guardTargetTypeThrowInfo@@3HA
    db 08Dh, 054h, 024h, 054h, 052h
    call ?ji_009f6d00@@YAXXZ
    db 06Ah, 001h, 050h, 08Bh, 0CDh
    call ?j_0002c566@@YAXXZ
    db 08Bh, 006h, 08Dh, 04Fh, 04Ch, 051h, 08Bh, 0CEh, 0FFh, 050h, 030h, 08Bh, 016h, 08Dh, 087h, 034h
    db 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 016h, 08Dh, 087h, 038h, 001h, 000h
    db 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 016h, 08Dh, 087h, 03Ch, 001h, 000h, 000h, 050h
    db 08Bh, 0CEh, 0FFh, 052h, 06Ch, 056h, 08Dh, 08Fh, 044h, 001h, 000h, 000h
    call ?j_00008e72@@YAXXZ
    db 08Bh, 016h, 08Dh, 087h, 0E7h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 08Ch, 000h, 000h
    db 000h, 08Dh, 09Fh, 048h, 001h, 000h, 000h, 0BDh, 00Bh, 000h, 000h, 000h, 08Bh, 016h, 053h, 08Bh
    db 0CEh, 0FFh, 052h, 074h, 083h, 0C3h, 004h, 04Dh, 075h, 0F2h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h
    db 004h, 033h, 0EDh, 084h, 0C0h, 074h, 018h, 039h, 0AFh, 0ACh, 001h, 000h, 000h, 074h, 010h, 08Bh
    db 04Ch, 024h, 024h, 051h, 08Bh, 00Dh
    dd ?Radar00598950@@3PAVBfmeThingAOA@@A
    call ?j_000251e4@@YAXXZ
    db 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 008h, 084h, 0C0h, 074h, 01Bh, 08Bh, 087h, 0B4h, 001h, 000h
    db 000h, 03Bh, 0C5h, 074h, 00Bh, 08Bh, 040h, 074h, 089h, 087h, 0B8h, 001h, 000h, 000h, 0EBh, 006h
    db 089h, 0AFh, 0B8h, 001h, 000h, 000h, 08Dh, 087h, 0B8h, 001h, 000h, 000h, 050h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Dh, 087h, 0BCh, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 074h, 08Bh, 016h, 08Dh, 087h, 0C0h, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh
    db 016h, 08Dh, 087h, 0E0h, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 016h, 08Dh
    db 087h, 0E4h, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 078h, 08Bh, 016h, 08Dh, 087h, 0ECh
    db 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 060h, 08Bh, 016h, 08Dh, 087h, 048h, 002h, 000h
    db 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 060h, 08Dh, 08Fh, 054h, 002h, 000h, 000h, 051h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 083h, 0C4h, 008h, 08Dh, 08Fh, 0B0h, 002h, 000h, 000h
    call ?j_00049945@@YAXXZ
    db 08Bh, 016h, 08Dh, 09Fh, 0E6h, 002h, 000h, 000h, 053h, 08Bh, 0CEh, 0FFh, 092h, 088h, 000h, 000h
    db 000h, 08Bh, 006h, 08Dh, 08Fh, 0A0h, 002h, 000h, 000h, 051h, 08Bh, 0CEh, 0FFh, 050h, 074h, 08Bh
    db 016h, 08Dh, 087h, 0A4h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 05Ch, 08Ah, 003h, 084h
    db 0C0h, 00Fh, 08Ch, 070h, 009h, 000h, 000h, 03Ch, 005h, 00Fh, 08Fh, 068h, 009h, 000h, 000h, 033h
    db 0DBh, 084h, 0C0h, 089h, 05Ch, 024h, 010h, 00Fh, 08Eh, 056h, 001h, 000h, 000h, 0EBh, 003h, 08Dh
    db 049h, 000h, 089h, 06Ch, 024h, 018h, 08Bh, 084h, 0DFh, 078h, 002h, 000h, 000h, 03Bh, 0C5h, 0C6h
    db 084h, 024h, 0BCh, 000h, 000h, 000h, 002h, 074h, 00Dh, 083h, 0C0h, 008h, 050h, 08Dh, 04Ch, 024h
    db 01Ch
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 016h, 08Dh, 044h, 024h, 018h, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 016h, 08Bh, 0CEh
    db 0FFh, 052h, 004h, 084h, 0C0h, 074h, 026h, 051h, 08Dh, 044h, 024h, 01Ch, 089h, 064h, 024h, 020h
    db 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 0FFh, 092h, 090h, 000h, 000h, 000h, 089h, 084h, 0DFh, 078h, 002h, 000h, 000h, 08Bh
    db 006h, 08Dh, 08Ch, 0DFh, 07Ch, 002h, 000h, 000h, 051h, 08Bh, 0CEh, 0FFh, 090h, 088h, 000h, 000h
    db 000h, 08Bh, 016h, 08Dh, 084h, 0DFh, 07Dh, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 088h
    db 000h, 000h, 000h, 08Bh, 016h, 08Dh, 084h, 0DFh, 07Eh, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh
    db 092h, 088h, 000h, 000h, 000h, 039h, 0ACh, 0DFh, 078h, 002h, 000h, 000h, 00Fh, 085h, 088h, 000h
    db 000h, 000h, 08Dh, 04Ch, 024h, 018h, 051h, 08Dh, 054h, 024h, 014h, 052h, 08Dh, 044h, 024h, 044h
    db 050h
    call ?j_00032ee8@@YAXXZ
    db 089h, 044h, 024h, 028h, 08Bh, 08Fh, 0B0h, 002h, 000h, 000h, 06Ah, 010h, 0C6h, 084h, 024h, 0CCh
    db 000h, 000h, 000h, 003h, 089h, 04Ch, 024h, 048h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0E8h, 08Dh, 045h, 008h, 083h, 0C4h, 010h, 089h, 044h, 024h, 010h, 089h, 044h, 024h, 050h
    db 085h, 0C0h, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 004h, 074h, 016h, 08Bh, 04Ch, 024h, 01Ch
    db 08Bh, 011h, 083h, 0C1h, 004h, 089h, 010h, 083h, 0C0h, 004h, 051h, 08Bh, 0C8h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 044h, 024h, 038h, 08Bh, 048h, 004h, 089h, 04Dh, 004h, 089h, 045h, 000h, 089h, 029h, 08Dh
    db 04Ch, 024h, 040h, 089h, 068h, 004h, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0EDh, 08Dh, 04Ch, 024h, 018h, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 00Fh, 0BEh, 087h, 0E6h, 002h, 000h, 000h, 043h, 03Bh, 0D8h, 089h, 05Ch, 024h, 010h, 00Fh, 08Ch
    db 0AFh, 0FEh, 0FFh, 0FFh, 08Dh, 08Fh, 0B4h, 002h, 000h, 000h, 051h, 056h
    call ?j_000394be@@YAXXZ
    db 08Dh, 097h, 0B8h, 002h, 000h, 000h, 052h, 056h
    call ?j_000394be@@YAXXZ
    db 08Bh, 006h, 083h, 0C4h, 010h, 08Dh, 08Fh, 0E0h, 002h, 000h, 000h, 051h, 08Bh, 0CEh, 0FFh, 090h
    db 08Ch, 000h, 000h, 000h, 08Bh, 016h, 08Dh, 087h, 0D0h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh
    db 052h, 074h, 08Dh, 09Fh, 0BCh, 002h, 000h, 000h, 053h, 056h
    call ?j_0000db61@@YAXXZ
    db 08Bh, 003h, 083h, 0C4h, 008h, 03Bh, 0C5h, 074h, 00Eh, 08Bh, 016h, 08Dh, 087h, 0C0h, 002h, 000h
    db 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 050h, 08Bh, 087h, 090h, 001h, 000h, 000h, 089h, 06Ch, 024h
    db 028h, 039h, 028h, 074h, 011h, 090h, 08Bh, 05Ch, 024h, 028h, 043h, 083h, 0C0h, 004h, 089h, 05Ch
    db 024h, 028h, 039h, 028h, 075h, 0F0h, 08Bh, 016h, 08Dh, 044h, 024h, 028h, 050h, 08Bh, 0CEh, 0FFh
    db 052h, 07Ch, 089h, 06Ch, 024h, 02Ch, 08Bh, 016h, 08Bh, 0CEh, 0C6h, 084h, 024h, 0BCh, 000h, 000h
    db 000h, 005h, 0FFh, 052h, 008h, 084h, 0C0h, 00Fh, 084h, 089h, 000h, 000h, 000h, 08Bh, 09Fh, 090h
    db 001h, 000h, 000h, 08Bh, 02Bh, 085h, 0EDh, 00Fh, 084h, 042h, 001h, 000h, 000h, 0EBh, 007h, 08Dh
    db 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 045h, 004h, 08Bh, 040h, 004h, 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 050h, 08Dh, 044h, 024h, 020h, 050h
    call ?j_0003EC7A@@YAXXZ
    db 050h, 08Dh, 04Ch, 024h, 030h, 0C6h, 084h, 024h, 0C0h, 000h, 000h, 000h, 006h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 005h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 016h, 08Dh, 044h, 024h, 02Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 016h, 068h
    dd g_Va0109CB8C
    db 08Bh, 0CEh, 0FFh, 052h, 014h, 08Bh, 006h, 055h, 08Bh, 0CEh, 0FFh, 050h, 030h, 08Bh, 016h, 08Bh
    db 0CEh, 0FFh, 052h, 018h, 08Bh, 06Bh, 004h, 083h, 0C3h, 004h, 085h, 0EDh, 075h, 095h, 0E9h, 0C9h
    db 000h, 000h, 000h, 089h, 06Ch, 024h, 01Ch, 066h, 039h, 06Ch, 024h, 028h, 0C6h, 084h, 024h, 0BCh
    db 000h, 000h, 000h, 007h, 089h, 06Ch, 024h, 010h, 00Fh, 086h, 09Dh, 000h, 000h, 000h, 0EBh, 003h
    db 08Dh, 049h, 000h, 08Bh, 006h, 08Dh, 04Ch, 024h, 02Ch, 051h, 08Bh, 0CEh, 0FFh, 050h, 068h, 08Bh
    db 044h, 024h, 02Ch, 03Bh, 0C5h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 050h
    call ?j_0003add7@@YAXXZ
    db 08Bh, 097h, 090h, 001h, 000h, 000h, 03Bh, 0D5h, 074h, 027h, 08Bh, 00Ah, 03Bh, 0CDh, 074h, 021h
    db 08Bh, 049h, 004h, 03Bh, 041h, 004h, 074h, 013h, 083h, 0C2h, 004h, 075h, 0EDh, 08Bh, 016h, 068h
    dd g_Va0109CB8C
    db 08Bh, 0CEh, 0FFh, 052h, 01Ch, 0EBh, 02Fh, 08Bh, 01Ah, 03Bh, 0DDh, 075h, 00Eh, 08Bh, 016h, 068h
    dd g_Va0109CB8C
    db 08Bh, 0CEh, 0FFh, 052h, 01Ch, 0EBh, 01Bh, 08Bh, 006h, 068h
    dd g_Va0109CB8C
    db 08Bh, 0CEh, 0FFh, 050h, 014h, 08Bh, 016h, 053h, 08Bh, 0CEh, 0FFh, 052h, 030h, 08Bh, 006h, 08Bh
    db 0CEh, 0FFh, 050h, 018h, 08Bh, 044h, 024h, 010h, 040h, 066h, 03Bh, 044h, 024h, 028h, 089h, 044h
    db 024h, 010h, 00Fh, 082h, 068h, 0FFh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 0BCh
    db 000h, 000h, 000h, 005h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 08Fh, 070h, 002h, 000h, 000h, 051h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Dh, 087h, 074h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 074h, 08Bh, 087h, 088h, 001h, 000h, 000h, 08Bh, 016h, 050h, 08Bh, 0CEh, 0FFh, 052h, 030h, 056h
    db 08Dh, 08Fh, 03Ch, 002h, 000h, 000h
    call ?j_00044ce7@@YAXXZ
    db 033h, 0DBh, 08Bh, 016h, 08Dh, 084h, 03Bh, 044h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h
    db 088h, 000h, 000h, 000h, 043h, 083h, 0FBh, 004h, 07Ch, 0E8h, 08Bh, 016h, 08Dh, 087h, 004h, 002h
    db 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 030h, 056h, 08Dh, 08Fh, 060h, 002h, 000h, 000h
    call ?j_0002fc1b@@YAXXZ
    db 08Bh, 016h, 08Dh, 087h, 0C8h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 080h, 07Ch
    db 024h, 015h, 00Bh, 072h, 00Eh, 08Bh, 016h, 08Dh, 087h, 0CCh, 002h, 000h, 000h, 050h, 08Bh, 0CEh
    db 0FFh, 052h, 068h, 08Bh, 016h, 08Dh, 087h, 0E1h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h
    db 08Ch, 000h, 000h, 000h, 08Bh, 016h, 08Dh, 087h, 0E2h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh
    db 092h, 08Ch, 000h, 000h, 000h, 08Bh, 016h, 08Dh, 087h, 0E8h, 002h, 000h, 000h, 050h, 08Bh, 0CEh
    db 0FFh, 092h, 08Ch, 000h, 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 00Ch, 084h, 0C0h, 075h
    db 00Eh, 08Bh, 006h, 08Dh, 08Fh, 0D4h, 002h, 000h, 000h, 051h, 08Bh, 0CEh, 0FFh, 050h, 074h, 08Bh
    db 016h, 08Bh, 0CEh, 0FFh, 052h, 008h, 084h, 0C0h, 074h, 05Bh, 08Bh, 08Fh, 0F0h, 002h, 000h, 000h
    db 02Bh, 08Fh, 0ECh, 002h, 000h, 000h, 0B8h, 0C9h, 042h, 016h, 0B2h, 0F7h, 0E9h, 003h, 0D1h, 0C1h
    db 0FAh, 006h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 08Bh, 016h, 089h, 044h, 024h, 01Ch, 08Dh
    db 044h, 024h, 01Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 08Bh, 0AFh, 0ECh, 002h, 000h, 000h, 03Bh
    db 0AFh, 0F0h, 002h, 000h, 000h, 00Fh, 084h, 04Dh, 002h, 000h, 000h, 08Bh, 055h, 000h, 056h, 08Bh
    db 0CDh, 0FFh, 012h, 08Bh, 087h, 0F0h, 002h, 000h, 000h, 083h, 0C5h, 05Ch, 03Bh, 0E8h, 075h, 0EBh
    db 0E9h, 033h, 002h, 000h, 000h, 08Bh, 08Fh, 0ECh, 002h, 000h, 000h, 08Bh, 087h, 0F0h, 002h, 000h
    db 000h, 06Ah, 000h, 08Dh, 0AFh, 0ECh, 002h, 000h, 000h, 08Dh, 054h, 024h, 027h, 052h, 051h, 050h
    db 050h
    call ?j_00009025@@YAXXZ
    db 083h, 0C4h, 014h, 08Dh, 04Ch, 024h, 018h, 089h, 045h, 004h, 08Bh, 006h, 051h, 08Bh, 0CEh, 0FFh
    db 050h, 074h, 08Bh, 044h, 024h, 018h, 085h, 0C0h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h
    db 00Fh, 086h, 0ECh, 001h, 000h, 000h, 033h, 0DBh, 056h, 08Dh, 04Ch, 024h, 05Ch, 0C7h, 044h, 024h
    db 05Ch
    dd ??_7DamageInfo@@6B@
    db 0C7h, 044h, 024h, 060h
    dd ??_7DamageInfoInput@@6B@
    db 089h, 05Ch, 024h, 064h, 066h, 089h, 05Ch, 024h, 068h, 0C7h, 044h, 024h, 06Ch, 016h, 000h, 000h
    db 000h, 0C7h, 044h, 024h, 070h, 00Fh, 000h, 000h, 000h, 089h, 05Ch, 024h, 074h, 0C7h, 044h, 024h
    db 078h, 000h, 000h, 000h, 000h, 0C6h, 044h, 024h, 07Ch, 000h, 0C6h, 044h, 024h, 07Dh, 001h, 0C7h
    db 084h, 024h, 080h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 089h, 09Ch, 024h, 084h, 000h, 000h
    db 000h, 089h, 09Ch, 024h, 088h, 000h, 000h, 000h, 0C7h, 084h, 024h, 08Ch, 000h, 000h, 000h, 000h
    db 000h, 000h, 000h, 0C7h, 084h, 024h, 090h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h
    db 024h, 094h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 098h, 000h, 000h, 000h
    db 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 09Ch, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h
    db 084h, 024h, 0A0h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0A4h, 000h, 000h
    db 000h, 000h, 000h, 080h, 03Fh, 0C7h, 084h, 024h, 0A8h, 000h, 000h, 000h
    dd ??_7DamageInfoOutput@@6B@
    db 0C7h, 084h, 024h, 0ACh, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0B0h, 000h
    db 000h, 000h, 000h, 000h, 000h, 000h, 0C6h, 084h, 024h, 0B4h, 000h, 000h, 000h, 000h
    call ?j_0003f75b@@YAXXZ
    db 08Bh, 045h, 004h, 03Bh, 045h, 008h, 00Fh, 084h, 0DBh, 000h, 000h, 000h, 03Bh, 0C3h, 00Fh, 084h
    db 0CDh, 000h, 000h, 000h, 0C7h, 000h
    dd ??_7DamageInfo@@6B@
    db 0C7h, 040h, 004h
    dd ??_7DamageInfoInput@@6B@
    db 08Bh, 054h, 024h, 060h, 089h, 050h, 008h, 066h, 08Bh, 04Ch, 024h, 064h, 066h, 089h, 048h, 00Ch
    db 08Bh, 054h, 024h, 068h, 089h, 050h, 010h, 08Bh, 04Ch, 024h, 06Ch, 089h, 048h, 014h, 08Bh, 054h
    db 024h, 070h, 089h, 050h, 018h, 08Bh, 04Ch, 024h, 074h, 089h, 048h, 01Ch, 08Ah, 054h, 024h, 078h
    db 088h, 050h, 020h, 08Ah, 04Ch, 024h, 079h, 088h, 048h, 021h, 08Bh, 054h, 024h, 07Ch, 089h, 050h
    db 024h, 08Bh, 08Ch, 024h, 080h, 000h, 000h, 000h, 089h, 048h, 028h, 08Bh, 094h, 024h, 084h, 000h
    db 000h, 000h, 089h, 050h, 02Ch, 08Bh, 08Ch, 024h, 088h, 000h, 000h, 000h, 089h, 048h, 030h, 08Bh
    db 094h, 024h, 08Ch, 000h, 000h, 000h, 089h, 050h, 034h, 08Bh, 08Ch, 024h, 090h, 000h, 000h, 000h
    db 089h, 048h, 038h, 08Bh, 094h, 024h, 094h, 000h, 000h, 000h, 089h, 050h, 03Ch, 08Bh, 08Ch, 024h
    db 098h, 000h, 000h, 000h, 089h, 048h, 040h, 08Bh, 094h, 024h, 09Ch, 000h, 000h, 000h, 089h, 050h
    db 044h, 08Bh, 08Ch, 024h, 0A0h, 000h, 000h, 000h, 089h, 048h, 048h, 0C7h, 040h, 04Ch
    dd ??_7DamageInfoOutput@@6B@
    db 08Bh, 094h, 024h, 0A8h, 000h, 000h, 000h, 089h, 050h, 050h, 08Bh, 08Ch, 024h, 0ACh, 000h, 000h
    db 000h, 089h, 048h, 054h, 08Ah, 094h, 024h, 0B0h, 000h, 000h, 000h, 088h, 050h, 058h, 083h, 045h
    db 004h, 05Ch, 0EBh, 016h, 06Ah, 001h, 06Ah, 001h, 08Dh, 04Ch, 024h, 02Bh, 051h, 08Dh, 054h, 024h
    db 064h, 052h, 050h, 08Bh, 0CDh
    call ?j_0002aa8b@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 08Bh, 04Ch, 024h, 018h, 040h, 03Bh, 0C1h, 089h, 044h, 024h, 010h, 00Fh
    db 082h, 016h, 0FEh, 0FFh, 0FFh, 08Bh, 006h, 08Dh, 08Fh, 0FCh, 002h, 000h, 000h, 051h, 08Bh, 0CEh
    db 0FFh, 050h, 074h, 08Bh, 016h, 08Dh, 087h, 0F8h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 06Ch, 08Dh, 08Fh, 000h, 003h, 000h, 000h, 051h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 08Bh, 016h, 083h, 0C4h, 008h, 08Dh, 087h, 00Ah, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h
    db 08Ch, 000h, 000h, 000h, 08Bh, 016h, 08Dh, 087h, 0E5h, 002h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh
    db 092h, 084h, 000h, 000h, 000h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 00Ch, 084h, 0C0h, 00Fh, 085h
    db 093h, 000h, 000h, 000h, 08Bh, 006h, 08Dh, 08Fh, 010h, 003h, 000h, 000h, 051h, 08Bh, 0CEh, 0FFh
    db 050h, 078h, 08Ah, 044h, 024h, 015h, 03Ch, 00Ah, 073h, 03Dh, 08Bh, 016h, 08Dh, 044h, 024h, 050h
    db 050h, 08Bh, 0CEh, 0FFh, 052h, 078h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 08Bh, 016h
    db 08Dh, 044h, 024h, 010h, 050h, 08Bh, 0CEh, 0C6h, 084h, 024h, 0C0h, 000h, 000h, 000h, 008h, 0FFh
    db 052h, 068h, 08Dh, 04Ch, 024h, 010h, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 005h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Ah, 044h, 024h, 015h, 03Ch, 007h, 072h, 00Eh, 056h, 08Dh, 08Fh, 014h, 003h, 000h, 000h
    call ?j_0003fbcf@@YAXXZ
    db 0EBh, 02Eh, 03Ch, 006h, 072h, 02Ah, 08Bh, 016h, 08Dh, 087h, 018h, 003h, 000h, 000h, 050h, 08Bh
    db 0CEh, 0FFh, 052h, 078h, 08Bh, 016h, 08Dh, 087h, 01Ch, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh
    db 052h, 078h, 08Bh, 016h, 08Dh, 087h, 020h, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 078h
    db 08Bh, 016h, 08Dh, 087h, 03Ch, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 08Ch, 000h, 000h
    db 000h, 08Bh, 016h, 08Dh, 087h, 030h, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 08Ch, 000h
    db 000h, 000h, 08Bh, 016h, 08Dh, 087h, 008h, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 08Ch
    db 000h, 000h, 000h, 08Bh, 016h, 08Dh, 087h, 038h, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h
    db 078h, 08Bh, 016h, 08Dh, 087h, 040h, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh
    db 016h, 08Dh, 087h, 02Ch, 001h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 06Ch, 08Bh, 016h, 08Bh
    db 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 08Bh, 05Ch, 024h, 024h, 074h, 012h, 08Bh, 003h, 08Bh, 0CBh
    db 0FFh, 050h, 028h, 085h, 0C0h, 074h, 007h, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 052h, 034h, 080h, 07Ch
    db 024h, 015h, 002h, 072h, 00Eh, 08Bh, 006h, 08Dh, 08Fh, 0D8h, 002h, 000h, 000h, 051h, 08Bh, 0CEh
    db 0FFh, 050h, 074h, 080h, 07Ch, 024h, 015h, 003h, 072h, 00Eh, 08Bh, 016h, 08Dh, 087h, 0DCh, 002h
    db 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 080h, 07Ch, 024h, 015h, 004h, 072h, 011h, 08Bh
    db 016h, 08Dh, 087h, 048h, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 092h, 08Ch, 000h, 000h, 000h
    db 08Bh, 016h, 08Dh, 087h, 04Ch, 003h, 000h, 000h, 050h, 08Bh, 0CEh, 0FFh, 052h, 074h, 080h, 07Ch
    db 024h, 015h, 005h, 072h, 010h, 08Dh, 08Fh, 040h, 003h, 000h, 000h, 051h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 083h, 0C4h, 008h, 080h, 07Ch, 024h, 015h, 008h, 072h, 010h, 08Dh, 097h, 044h, 003h, 000h, 000h
    db 052h, 056h
    call ?j_0000c9b4@@YAXXZ
    db 083h, 0C4h, 008h, 080h, 07Ch, 024h, 015h, 009h, 072h, 00Eh, 08Bh, 006h, 08Dh, 08Fh, 0F8h, 001h
    db 000h, 000h, 051h, 08Bh, 0CEh, 0FFh, 050h, 06Ch, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h
    db 0C0h, 074h, 04Ch, 08Bh, 047h, 0A4h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h
    db 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0CCh, 000h, 000h, 000h, 000h, 000h, 000h, 008h, 074h, 02Dh, 0F6h, 087h, 0E4h, 002h
    db 000h, 000h, 001h, 074h, 015h, 08Bh, 0BFh, 0A0h, 001h, 000h, 000h, 085h, 0FFh, 074h, 01Ah, 08Bh
    db 007h, 08Bh, 0CFh, 0FFh, 050h, 020h, 085h, 0C0h, 075h, 00Fh, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 053h
    call ?j_0000b81b@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C6h, 084h, 024h, 0BCh, 000h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 030h, 0C7h, 084h, 024h, 0BCh, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 08Ch, 024h, 0B4h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 0B0h, 000h, 000h, 000h, 0C2h, 004h, 000h, 055h, 08Dh, 054h, 024h, 040h
    db 06Ah, 005h, 052h
    call _bfmeFormatText
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_guardTargetTypeThrowInfo@@3HA
    db 08Dh, 044h, 024h, 040h, 050h
    call ?ji_009f6d00@@YAXXZ
?d_001d48a0@@YAXXZ ENDP
_TEXT$d005d48a0 ENDS
_TEXT SEGMENT

; retail @ 0x001F1860 size 649
public ?d_001f1860@@YAXXZ
?d_001f1860@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0C8h, 0A9h, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 74h, 24h, 24h, 57h, 56h
    db 8Bh, 0F9h, 0E8h, 3Ah, 2Ch, 0E1h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h
    db 0Fh, 85h, 0B3h, 01h, 00h, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0C6h
    db 44h, 24h, 10h, 01h, 0C6h, 44h, 24h, 11h, 02h, 0FFh, 52h, 28h, 8Dh, 4Fh, 28h, 51h
    db 56h, 0E8h, 0FEh, 0B0h, 0E1h, 0FFh, 8Dh, 57h, 38h, 52h, 56h, 0E8h, 0F4h, 0B0h, 0E1h, 0FFh
    db 8Bh, 06h, 83h, 0C4h, 10h, 8Dh, 4Fh, 6Ch, 51h, 8Bh, 0CEh, 0FFh, 50h, 78h, 8Bh, 16h
    db 8Dh, 47h, 68h, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 47h, 50h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 60h, 8Bh, 16h, 8Dh, 47h, 5Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh
    db 16h, 8Dh, 87h, 80h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h
    db 8Dh, 4Fh, 7Ch, 51h, 56h, 0E8h, 0D8h, 0E6h, 0E1h, 0FFh, 8Bh, 16h, 83h, 0C4h, 08h, 8Dh
    db 47h, 2Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Dh, 4Fh, 44h, 51h, 56h, 0E8h, 0A7h, 0B9h
    db 0E1h, 0FFh, 8Ah, 44h, 24h, 15h, 83h, 0C4h, 08h, 3Ch, 02h, 72h, 0Eh, 8Bh, 16h, 8Dh
    db 87h, 84h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 68h, 50h, 6Eh, 33h, 01h
    db 8Dh, 4Ch, 24h, 2Ch, 0E8h, 17h, 62h, 69h, 00h, 8Bh, 4Fh, 40h, 33h, 0DBh, 3Bh, 0CBh
    db 89h, 5Ch, 24h, 20h, 74h, 26h, 8Dh, 54h, 24h, 10h, 52h, 0E8h, 0E5h, 26h, 0E4h, 0FFh
    db 50h, 8Dh, 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 24h, 01h, 0E8h, 21h, 63h, 69h, 00h, 8Dh
    db 4Ch, 24h, 10h, 88h, 5Ch, 24h, 20h, 0E8h, 0C4h, 5Fh, 69h, 00h, 8Bh, 06h, 8Dh, 4Ch
    db 24h, 28h, 51h, 8Bh, 0CEh, 0FFh, 50h, 68h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h
    db 0C0h, 74h, 19h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 24h, 07h, 0E3h
    db 0FFh, 85h, 0C0h, 0Fh, 85h, 0B4h, 00h, 00h, 00h, 89h, 5Fh, 40h, 68h, 50h, 6Eh, 33h
    db 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0D6h, 62h, 69h, 00h, 8Bh, 4Fh, 3Ch, 3Bh, 0CBh, 74h
    db 26h, 8Dh, 44h, 24h, 10h, 50h, 0E8h, 7Ah, 26h, 0E4h, 0FFh, 50h, 8Dh, 4Ch, 24h, 2Ch
    db 0C6h, 44h, 24h, 24h, 02h, 0E8h, 0B6h, 62h, 69h, 00h, 8Dh, 4Ch, 24h, 10h, 88h, 5Ch
    db 24h, 20h, 0E8h, 59h, 5Fh, 69h, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 28h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 68h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 19h, 68h, 50h
    db 6Eh, 33h, 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0B9h, 06h, 0E3h, 0FFh, 85h, 0C0h, 0Fh, 85h
    db 8Fh, 00h, 00h, 00h, 89h, 5Fh, 3Ch, 8Bh, 06h, 8Dh, 4Fh, 78h, 51h, 8Bh, 0CEh, 0FFh
    db 50h, 78h, 8Bh, 16h, 8Dh, 47h, 70h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 83h
    db 0C7h, 74h, 57h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F7h, 5Eh, 69h, 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 51h, 8Dh, 44h
    db 24h, 2Ch, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 50h, 0E8h, 0F2h, 60h, 69h, 00h, 8Bh, 0Dh
    db 38h, 0F7h, 2Eh, 01h, 0E8h, 81h, 0B9h, 0E1h, 0FFh, 3Bh, 0C3h, 89h, 47h, 40h, 0Fh, 85h
    db 28h, 0FFh, 0FFh, 0FFh, 53h, 8Dh, 4Ch, 24h, 14h, 6Ah, 05h, 51h, 0E8h, 8Fh, 47h, 7Eh
    db 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 5Dh
    db 52h, 80h, 00h, 51h, 8Dh, 44h, 24h, 2Ch, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 50h, 0E8h
    db 0ACh, 60h, 69h, 00h, 8Bh, 0Dh, 38h, 0F7h, 2Eh, 01h, 0E8h, 3Bh, 0B9h, 0E1h, 0FFh, 3Bh
    db 0C3h, 89h, 47h, 3Ch, 0Fh, 85h, 4Dh, 0FFh, 0FFh, 0FFh, 53h, 8Dh, 4Ch, 24h, 14h, 6Ah
    db 05h, 51h, 0E8h, 49h, 47h, 7Eh, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh
    db 54h, 24h, 14h, 52h, 0E8h, 17h, 52h, 80h, 00h
?d_001f1860@@YAXXZ ENDP

; retail @ 0x0020F000 size 460
public ?d_0020f000@@YAXXZ
?d_0020f000@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 30h, 0C4h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 56h, 8Bh, 74h, 24h, 2Ch, 8Bh, 06h, 57h
    db 8Bh, 0F9h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h
    db 24h, 11h, 01h, 0FFh, 50h, 28h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 10h, 84h, 0C0h, 74h
    db 1Bh, 56h, 8Bh, 0CFh, 0E8h, 5Bh, 6Dh, 0E3h, 0FFh, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 18h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 8Bh, 06h, 53h, 55h
    db 8Bh, 0CEh, 0FFh, 50h, 08h, 84h, 0C0h, 0Fh, 84h, 0A5h, 00h, 00h, 00h, 8Dh, 4Fh, 04h
    db 33h, 0D2h, 3Bh, 0F9h, 8Bh, 0C7h, 73h, 19h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 18h, 0Fh, 0B6h, 9Bh, 28h, 71h, 2Ch, 01h, 03h, 0D3h, 40h, 3Bh, 0C1h, 72h
    db 0EFh, 8Dh, 44h, 24h, 38h, 89h, 54h, 24h, 38h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 78h, 33h, 0EDh, 83h, 0CBh, 0FFh, 8Bh, 07h, 8Bh, 0CDh, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h
    db 00h, 00h, 0D3h, 0E2h, 85h, 0D0h, 74h, 3Fh, 8Bh, 04h, 0ADh, 0D8h, 68h, 2Ah, 01h, 85h
    db 0C0h, 74h, 34h, 50h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 0F3h, 9Ah, 67h, 00h, 8Bh, 06h, 8Dh
    db 4Ch, 24h, 18h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0FFh, 50h
    db 68h, 8Bh, 44h, 24h, 38h, 48h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 38h, 89h, 5Ch
    db 24h, 30h, 0E8h, 49h, 88h, 67h, 00h, 45h, 83h, 0FDh, 0Bh, 7Ch, 0A9h, 5Dh, 5Bh, 5Fh
    db 5Eh, 8Bh, 4Ch, 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h
    db 04h, 00h, 8Dh, 44h, 24h, 1Ch, 0C7h, 07h, 00h, 00h, 00h, 00h, 8Bh, 16h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 78h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch
    db 33h, 0EDh, 85h, 0C0h, 0C7h, 44h, 24h, 30h, 01h, 00h, 00h, 00h, 7Eh, 48h, 8Bh, 0FFh
    db 8Bh, 16h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 44h, 24h, 10h
    db 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h
    db 0E2h, 20h, 0E2h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 7Ch, 41h, 8Bh, 1Fh, 8Bh, 0C8h, 8Bh
    db 44h, 24h, 1Ch, 83h, 0E1h, 1Fh, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 0Bh, 0DAh, 45h
    db 3Bh, 0E8h, 89h, 1Fh, 7Ch, 0BAh, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0A9h, 87h, 67h, 00h, 8Bh, 4Ch, 24h, 28h, 5Dh, 5Bh, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C2h, 04h, 00h, 6Ah, 00h, 8Dh, 44h
    db 24h, 24h, 6Ah, 00h, 50h, 0E8h, 66h, 70h, 7Ch, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh
    db 1Dh, 01h, 8Dh, 4Ch, 24h, 24h, 51h, 0E8h, 34h, 7Bh, 7Eh, 00h
?d_0020f000@@YAXXZ ENDP

; retail @ 0x0022BFF0 size 282
public ?d_0022bff0@@YAXXZ
?d_0022bff0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 89h, 44h, 24h, 10h
    db 0E8h, 79h, 0B2h, 0DEh, 0FFh, 8Bh, 86h, 0E4h, 00h, 00h, 00h, 39h, 00h, 74h, 20h, 6Ah
    db 00h, 8Dh, 4Ch, 24h, 14h, 6Ah, 05h, 51h, 0E8h, 03h, 0A2h, 7Ah, 00h, 83h, 0C4h, 0Ch
    db 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0D1h, 0ACh, 7Ch, 00h, 8Bh
    db 86h, 0FCh, 00h, 00h, 00h, 8Bh, 28h, 3Bh, 0E8h, 74h, 71h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 45h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 04h, 32h, 0DFh, 0FFh, 8Bh
    db 0D8h, 85h, 0DBh, 0Fh, 84h, 91h, 00h, 00h, 00h, 8Bh, 0BEh, 0E4h, 00h, 00h, 00h, 6Ah
    db 0Ch, 0E8h, 0DAh, 24h, 60h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 02h
    db 89h, 19h, 8Bh, 4Fh, 04h, 89h, 38h, 89h, 48h, 04h, 89h, 01h, 89h, 47h, 04h, 0F7h
    db 83h, 94h, 00h, 00h, 00h, 00h, 00h, 00h, 10h, 74h, 0Ch, 8Bh, 16h, 6Ah, 00h, 6Ah
    db 00h, 53h, 8Bh, 0CEh, 0FFh, 52h, 5Ch, 8Bh, 44h, 24h, 10h, 89h, 83h, 14h, 02h, 00h
    db 00h, 8Bh, 6Dh, 00h, 3Bh, 0AEh, 0FCh, 00h, 00h, 00h, 75h, 94h, 8Bh, 86h, 0FCh, 00h
    db 00h, 00h, 8Bh, 38h, 3Bh, 0F8h, 74h, 19h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h
    db 2Ch, 25h, 60h, 00h, 8Bh, 86h, 0FCh, 00h, 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h
    db 0E7h, 8Bh, 86h, 0FCh, 00h, 00h, 00h, 89h, 00h, 8Bh, 0B6h, 0FCh, 00h, 00h, 00h, 5Fh
    db 89h, 76h, 04h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C3h, 6Ah, 00h, 8Dh, 4Ch, 24h, 14h
    db 6Ah, 05h, 51h, 0E8h, 28h, 0A1h, 7Ah, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h
    db 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0F6h, 0ABh, 7Ch, 00h
?d_0022bff0@@YAXXZ ENDP

; retail @ 0x0024A900 size 282
public ?d_0024a900@@YAXXZ
?d_0024a900@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 89h, 44h, 24h, 10h
    db 0E8h, 7Ah, 60h, 0DFh, 0FFh, 8Bh, 86h, 0ECh, 00h, 00h, 00h, 39h, 00h, 74h, 20h, 6Ah
    db 00h, 8Dh, 4Ch, 24h, 14h, 6Ah, 05h, 51h, 0E8h, 0F3h, 0B8h, 78h, 00h, 83h, 0C4h, 0Ch
    db 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0C1h, 0C3h, 7Ah, 00h, 8Bh
    db 86h, 04h, 01h, 00h, 00h, 8Bh, 28h, 3Bh, 0E8h, 74h, 71h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 45h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 0F4h, 48h, 0DDh, 0FFh, 8Bh
    db 0D8h, 85h, 0DBh, 0Fh, 84h, 91h, 00h, 00h, 00h, 8Bh, 0BEh, 0ECh, 00h, 00h, 00h, 6Ah
    db 0Ch, 0E8h, 0CAh, 3Bh, 5Eh, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 02h
    db 89h, 19h, 8Bh, 4Fh, 04h, 89h, 38h, 89h, 48h, 04h, 89h, 01h, 89h, 47h, 04h, 0F7h
    db 83h, 94h, 00h, 00h, 00h, 00h, 00h, 00h, 10h, 74h, 0Ch, 8Bh, 16h, 6Ah, 00h, 6Ah
    db 00h, 53h, 8Bh, 0CEh, 0FFh, 52h, 5Ch, 8Bh, 44h, 24h, 10h, 89h, 83h, 14h, 02h, 00h
    db 00h, 8Bh, 6Dh, 00h, 3Bh, 0AEh, 04h, 01h, 00h, 00h, 75h, 94h, 8Bh, 86h, 04h, 01h
    db 00h, 00h, 8Bh, 38h, 3Bh, 0F8h, 74h, 19h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h
    db 1Ch, 3Ch, 5Eh, 00h, 8Bh, 86h, 04h, 01h, 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h
    db 0E7h, 8Bh, 86h, 04h, 01h, 00h, 00h, 89h, 00h, 8Bh, 0B6h, 04h, 01h, 00h, 00h, 5Fh
    db 89h, 76h, 04h, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C3h, 6Ah, 00h, 8Dh, 4Ch, 24h, 14h
    db 6Ah, 05h, 51h, 0E8h, 18h, 0B8h, 78h, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h
    db 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0E6h, 0C2h, 7Ah, 00h
?d_0024a900@@YAXXZ ENDP
_TEXT ENDS
END
