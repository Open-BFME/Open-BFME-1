.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Rva009A9400@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z:NEAR
EXTERN ?Rva009A97B0@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z:NEAR
EXTERN ?Rva009B3A00Table@@3PAGA:BYTE
EXTERN ?Rva009C5CA0@@YAXPAF0PAH@Z:NEAR
EXTERN ?g_Rva01142608@@3PAEA:BYTE
EXTERN g_Va012D8258:BYTE
EXTERN g_Va012D825C:BYTE
EXTERN g_Va012D8260:BYTE
EXTERN g_Va012D86C0:BYTE
EXTERN g_Va012D86D0:BYTE
EXTERN g_Va01356FE0:BYTE
_TEXT SEGMENT

; retail @ 0x009A7B00 size 993
public ?d_009a7b00@@YAXXZ
?d_009a7b00@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 44h, 24h, 04h, 8Bh, 0D1h, 2Bh, 0D0h, 79h, 06h, 8Bh, 0D0h
    db 8Bh, 0C1h, 2Bh, 0D1h, 83h, 0FAh, 01h, 53h, 55h, 56h, 57h, 0Fh, 85h, 87h, 01h, 00h
    db 00h, 8Bh, 4Ch, 24h, 2Ch, 85h, 0C9h, 8Bh, 4Ch, 24h, 24h, 74h, 27h, 0C1h, 0E1h, 04h
    db 81h, 0C1h, 98h, 77h, 2Dh, 01h, 51h, 8Bh, 4Ch, 24h, 20h, 6Ah, 08h, 6Ah, 08h, 52h
    db 8Bh, 54h, 24h, 30h, 52h, 51h, 50h, 0E8h, 0A4h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 5Fh
    db 5Eh, 5Dh, 5Bh, 0C3h, 8Bh, 5Ch, 24h, 20h, 8Bh, 0D0h, 8Bh, 44h, 24h, 1Ch, 83h, 0C3h
    db 0F8h, 83h, 0C0h, 04h, 0BFh, 08h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 6Ah, 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh, 72h, 01h, 0Fh
    db 0B6h, 12h, 0Fh, 0AFh, 14h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh
    db 07h, 66h, 89h, 50h, 0FCh, 0Fh, 0B6h, 6Eh, 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh
    db 01h, 8Dh, 56h, 01h, 0Fh, 0B6h, 36h, 0Fh, 0AFh, 34h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh
    db 74h, 2Eh, 40h, 0C1h, 0FEh, 07h, 66h, 89h, 70h, 0FEh, 0Fh, 0B6h, 6Ah, 01h, 0Fh, 0AFh
    db 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh, 72h, 01h, 0Fh, 0B6h, 12h, 0Fh, 0AFh, 14h, 0CDh
    db 18h, 78h, 2Dh, 01h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 66h, 89h, 10h, 0Fh, 0B6h
    db 6Eh, 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh, 56h, 01h, 0Fh, 0B6h, 36h
    db 0Fh, 0AFh, 34h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh, 74h, 2Eh, 40h, 0C1h, 0FEh, 07h, 66h
    db 89h, 70h, 02h, 0Fh, 0B6h, 6Ah, 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh
    db 72h, 01h, 0Fh, 0B6h, 12h, 0Fh, 0AFh, 14h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh, 54h, 2Ah
    db 40h, 0C1h, 0FAh, 07h, 66h, 89h, 50h, 04h, 0Fh, 0B6h, 6Eh, 01h, 0Fh, 0AFh, 2Ch, 0CDh
    db 1Ch, 78h, 2Dh, 01h, 8Dh, 56h, 01h, 0Fh, 0B6h, 36h, 0Fh, 0AFh, 34h, 0CDh, 18h, 78h
    db 2Dh, 01h, 8Dh, 74h, 2Eh, 40h, 0C1h, 0FEh, 07h, 66h, 89h, 70h, 06h, 0Fh, 0B6h, 6Ah
    db 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh, 72h, 01h, 0Fh, 0B6h, 12h, 0Fh
    db 0AFh, 14h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 66h, 89h
    db 50h, 08h, 0Fh, 0B6h, 6Eh, 01h, 0Fh, 0AFh, 2Ch, 0CDh, 1Ch, 78h, 2Dh, 01h, 8Dh, 56h
    db 01h, 0Fh, 0B6h, 36h, 0Fh, 0AFh, 34h, 0CDh, 18h, 78h, 2Dh, 01h, 8Dh, 74h, 2Eh, 40h
    db 0C1h, 0FEh, 07h, 66h, 89h, 70h, 0Ah, 03h, 0D3h, 83h, 0C0h, 10h, 4Fh, 0Fh, 85h, 0CDh
    db 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h, 8Bh, 4Ch, 24h, 20h, 3Bh, 0D1h, 0Fh, 85h
    db 85h, 01h, 00h, 00h, 8Bh, 54h, 24h, 2Ch, 85h, 0D2h, 74h, 27h, 8Bh, 54h, 24h, 28h
    db 0C1h, 0E2h, 04h, 81h, 0C2h, 98h, 77h, 2Dh, 01h, 52h, 6Ah, 08h, 6Ah, 08h, 51h, 51h
    db 8Bh, 4Ch, 24h, 30h, 51h, 50h, 0E8h, 15h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 5Fh, 5Eh
    db 5Dh, 5Bh, 0C3h, 8Bh, 54h, 24h, 1Ch, 8Bh, 74h, 24h, 28h, 83h, 0C2h, 04h, 0BFh, 08h
    db 00h, 00h, 00h, 0EBh, 0Bh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 0Fh, 0B6h, 1Ch, 08h, 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h, 0Fh, 0B6h, 28h, 0Fh
    db 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h, 8Dh, 5Ch, 2Bh, 40h, 0C1h, 0FBh, 07h, 66h, 89h
    db 5Ah, 0FCh, 0Fh, 0B6h, 5Ch, 08h, 01h, 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h, 0Fh
    db 0B6h, 68h, 01h, 0Fh, 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h, 8Dh, 5Ch, 2Bh, 40h, 0C1h
    db 0FBh, 07h, 66h, 89h, 5Ah, 0FEh, 40h, 0Fh, 0B6h, 5Ch, 08h, 01h, 0Fh, 0AFh, 1Ch, 0F5h
    db 1Ch, 78h, 2Dh, 01h, 0Fh, 0B6h, 68h, 01h, 0Fh, 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h
    db 8Dh, 5Ch, 2Bh, 40h, 40h, 0C1h, 0FBh, 07h, 66h, 89h, 1Ah, 0Fh, 0B6h, 5Ch, 08h, 01h
    db 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h, 0Fh, 0B6h, 68h, 01h, 0Fh, 0AFh, 2Ch, 0F5h
    db 18h, 78h, 2Dh, 01h, 40h, 8Dh, 5Ch, 2Bh, 40h, 0C1h, 0FBh, 07h, 66h, 89h, 5Ah, 02h
    db 0Fh, 0B6h, 5Ch, 08h, 01h, 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h, 0Fh, 0B6h, 68h
    db 01h, 0Fh, 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h, 40h, 8Dh, 5Ch, 2Bh, 40h, 0C1h, 0FBh
    db 07h, 66h, 89h, 5Ah, 04h, 0Fh, 0B6h, 5Ch, 08h, 01h, 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h
    db 2Dh, 01h, 0Fh, 0B6h, 68h, 01h, 0Fh, 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h, 40h, 8Dh
    db 5Ch, 2Bh, 40h, 0C1h, 0FBh, 07h, 66h, 89h, 5Ah, 06h, 0Fh, 0B6h, 5Ch, 08h, 01h, 0Fh
    db 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h, 0Fh, 0B6h, 68h, 01h, 0Fh, 0AFh, 2Ch, 0F5h, 18h
    db 78h, 2Dh, 01h, 40h, 8Dh, 5Ch, 2Bh, 40h, 0C1h, 0FBh, 07h, 66h, 89h, 5Ah, 08h, 0Fh
    db 0B6h, 5Ch, 08h, 01h, 0Fh, 0B6h, 68h, 01h, 0Fh, 0AFh, 1Ch, 0F5h, 1Ch, 78h, 2Dh, 01h
    db 0Fh, 0AFh, 2Ch, 0F5h, 18h, 78h, 2Dh, 01h, 40h, 8Dh, 5Ch, 2Bh, 40h, 0C1h, 0FBh, 07h
    db 66h, 89h, 5Ah, 0Ah, 40h, 8Dh, 59h, 0F8h, 03h, 0C3h, 83h, 0C2h, 10h, 4Fh, 0Fh, 85h
    db 0CCh, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h, 8Dh, 71h, 0FFh, 3Bh, 0D6h, 75h, 62h
    db 8Bh, 54h, 24h, 2Ch, 85h, 0D2h, 8Bh, 54h, 24h, 28h, 74h, 2Dh, 0C1h, 0E2h, 04h, 81h
    db 0C2h, 98h, 77h, 2Dh, 01h, 52h, 8Bh, 54h, 24h, 28h, 0C1h, 0E2h, 04h, 81h, 0C2h, 98h
    db 77h, 2Dh, 01h, 52h, 51h, 8Bh, 4Ch, 24h, 28h, 51h, 48h, 50h, 0E8h, 0AFh, 0F9h, 0FFh
    db 0FFh, 83h, 0C4h, 14h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h, 48h, 8Dh, 14h, 0D5h, 18h, 78h, 2Dh
    db 01h, 52h, 8Bh, 54h, 24h, 28h, 8Dh, 14h, 0D5h, 18h, 78h, 2Dh, 01h, 52h, 51h, 8Bh
    db 4Ch, 24h, 28h, 51h, 50h, 0E8h, 36h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Fh, 5Eh, 5Dh
    db 5Bh, 0C3h, 8Dh, 71h, 01h, 3Bh, 0D6h, 75h, 0F4h, 8Bh, 54h, 24h, 2Ch, 85h, 0D2h, 8Bh
    db 54h, 24h, 28h, 74h, 0C5h, 0C1h, 0E2h, 04h, 81h, 0C2h, 98h, 77h, 2Dh, 01h, 52h, 8Bh
    db 54h, 24h, 28h, 0C1h, 0E2h, 04h, 81h, 0C2h, 98h, 77h, 2Dh, 01h, 52h, 51h, 8Bh, 4Ch
    db 24h, 28h, 51h, 50h, 0E8h, 47h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Fh, 5Eh, 5Dh, 5Bh
    db 0C3h
?d_009a7b00@@YAXXZ ENDP

; retail @ 0x009A7EF0 size 108
public ?d_009a7ef0@@YAXXZ
?d_009a7ef0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 14h, 85h, 0C0h, 76h, 63h, 53h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 8Bh
    db 74h, 24h, 24h, 57h, 8Bh, 7Ch, 24h, 2Ch, 89h, 44h, 24h, 24h, 8Bh, 44h, 24h, 14h
    db 33h, 0C9h, 85h, 0F6h, 76h, 2Ch, 0EBh, 08h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 90h
    db 8Bh, 54h, 24h, 20h, 0Fh, 0B6h, 14h, 10h, 0Fh, 0B6h, 18h, 0Fh, 0AFh, 57h, 04h, 0Fh
    db 0AFh, 1Fh, 8Dh, 54h, 1Ah, 40h, 0C1h, 0FAh, 07h, 40h, 88h, 14h, 29h, 41h, 3Bh, 0CEh
    db 72h, 0DEh, 8Bh, 4Ch, 24h, 1Ch, 2Bh, 0CEh, 03h, 0C1h, 8Bh, 4Ch, 24h, 24h, 03h, 0EEh
    db 49h, 89h, 4Ch, 24h, 24h, 75h, 0B9h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h
?d_009a7ef0@@YAXXZ ENDP

; retail @ 0x009A85D0 size 28
public ?d_009a85d0@@YAXXZ
?d_009a85d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 6Ah, 40h, 0FFh, 15h, 28h, 8Eh, 35h, 01h, 0C3h, 0CCh, 0CCh
    db 8Bh, 44h, 24h, 04h, 50h, 0FFh, 15h, 2Ch, 8Eh, 35h, 01h, 0C3h
?d_009a85d0@@YAXXZ ENDP

; retail @ 0x009A91D0 size 247
public ?d_009a91d0@@YAXXZ
?d_009a91d0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 08h, 83h, 0C2h, 0FCh, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 44h, 24h, 04h, 53h
    db 56h, 57h, 0Fh, 84h, 87h, 00h, 00h, 00h, 4Ah, 0C1h, 0EAh, 02h, 42h, 89h, 54h, 24h
    db 18h, 55h, 0Fh, 0B6h, 70h, 01h, 0Fh, 0B6h, 10h, 88h, 11h, 6Bh, 0D2h, 33h, 8Bh, 0FEh
    db 6Bh, 0F6h, 66h, 69h, 0FFh, 0CDh, 00h, 00h, 00h, 8Dh, 94h, 17h, 80h, 00h, 00h, 00h
    db 0C1h, 0EAh, 08h, 88h, 51h, 01h, 0Fh, 0B6h, 78h, 02h, 0Fh, 0B6h, 68h, 03h, 69h, 0FFh
    db 9Ah, 00h, 00h, 00h, 8Dh, 94h, 3Eh, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h, 88h, 51h
    db 02h, 8Bh, 0D5h, 69h, 0EDh, 0CDh, 00h, 00h, 00h, 6Bh, 0D2h, 66h, 8Dh, 94h, 3Ah, 80h
    db 00h, 00h, 00h, 0C1h, 0EAh, 08h, 88h, 51h, 03h, 0Fh, 0B6h, 50h, 04h, 6Bh, 0D2h, 33h
    db 8Dh, 94h, 2Ah, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h, 88h, 51h, 04h, 8Bh, 54h, 24h
    db 1Ch, 83h, 0C0h, 04h, 83h, 0C1h, 05h, 4Ah, 89h, 54h, 24h, 1Ch, 75h, 84h, 5Dh, 0Fh
    db 0B6h, 70h, 01h, 0Fh, 0B6h, 10h, 88h, 11h, 6Bh, 0D2h, 33h, 8Bh, 0FEh, 6Bh, 0F6h, 66h
    db 69h, 0FFh, 0CDh, 00h, 00h, 00h, 8Dh, 94h, 17h, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h
    db 88h, 51h, 01h, 0Fh, 0B6h, 50h, 02h, 0Fh, 0B6h, 40h, 03h, 69h, 0D2h, 9Ah, 00h, 00h
    db 00h, 8Dh, 9Ch, 16h, 80h, 00h, 00h, 00h, 8Bh, 0F0h, 6Bh, 0F6h, 66h, 8Dh, 94h, 16h
    db 80h, 00h, 00h, 00h, 5Fh, 0C1h, 0EBh, 08h, 0C1h, 0EAh, 08h, 5Eh, 88h, 59h, 02h, 88h
    db 51h, 03h, 88h, 41h, 04h, 5Bh, 0C3h
?d_009a91d0@@YAXXZ ENDP

; retail @ 0x009A92D0 size 157
public ?d_009a92d0@@YAXXZ
?d_009a92d0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 0Ch, 85h, 0D2h, 8Bh, 44h, 24h, 04h, 0Fh, 86h, 8Ch, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 08h, 53h, 55h, 56h, 8Dh, 34h, 48h, 57h, 03h, 0F1h, 89h, 54h, 24h
    db 14h, 0Fh, 0B6h, 3Ch, 08h, 0Fh, 0B6h, 10h, 6Bh, 0D2h, 33h, 8Bh, 0DFh, 6Bh, 0FFh, 66h
    db 69h, 0DBh, 0CDh, 00h, 00h, 00h, 8Dh, 94h, 1Ah, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h
    db 88h, 14h, 08h, 0Fh, 0B6h, 2Ch, 48h, 0Fh, 0B6h, 16h, 69h, 0EDh, 9Ah, 00h, 00h, 00h
    db 8Dh, 9Ch, 2Fh, 80h, 00h, 00h, 00h, 8Bh, 0FAh, 69h, 0D2h, 0CDh, 00h, 00h, 00h, 6Bh
    db 0FFh, 66h, 0C1h, 0EBh, 08h, 88h, 1Ch, 48h, 8Dh, 9Ch, 2Fh, 80h, 00h, 00h, 00h, 0C1h
    db 0EBh, 08h, 88h, 1Eh, 8Dh, 3Ch, 89h, 0Fh, 0B6h, 3Ch, 07h, 6Bh, 0FFh, 33h, 8Dh, 94h
    db 17h, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h, 88h, 14h, 0Eh, 8Bh, 54h, 24h, 14h, 40h
    db 46h, 4Ah, 89h, 54h, 24h, 14h, 75h, 89h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h
?d_009a92d0@@YAXXZ ENDP

; retail @ 0x009A9370 size 130
public ?d_009a9370@@YAXXZ
?d_009a9370@@YAXXZ PROC
    db 8Bh, 54h, 24h, 0Ch, 85h, 0D2h, 8Bh, 44h, 24h, 04h, 76h, 75h, 8Bh, 4Ch, 24h, 08h
    db 53h, 55h, 56h, 8Dh, 34h, 48h, 57h, 03h, 0F1h, 89h, 54h, 24h, 14h, 8Dh, 49h, 00h
    db 0Fh, 0B6h, 3Ch, 08h, 0Fh, 0B6h, 10h, 6Bh, 0D2h, 33h, 8Bh, 0DFh, 6Bh, 0FFh, 66h, 69h
    db 0DBh, 0CDh, 00h, 00h, 00h, 8Dh, 94h, 1Ah, 80h, 00h, 00h, 00h, 0C1h, 0EAh, 08h, 88h
    db 14h, 08h, 0Fh, 0B6h, 2Ch, 48h, 0Fh, 0B6h, 16h, 69h, 0EDh, 9Ah, 00h, 00h, 00h, 8Dh
    db 9Ch, 2Fh, 80h, 00h, 00h, 00h, 8Bh, 0FAh, 6Bh, 0FFh, 66h, 0C1h, 0EBh, 08h, 88h, 1Ch
    db 48h, 8Dh, 9Ch, 2Fh, 80h, 00h, 00h, 00h, 0C1h, 0EBh, 08h, 88h, 1Eh, 88h, 14h, 0Eh
    db 8Bh, 54h, 24h, 14h, 40h, 46h, 4Ah, 89h, 54h, 24h, 14h, 75h, 0A3h, 5Fh, 5Eh, 5Dh
    db 5Bh, 0C3h
?d_009a9370@@YAXXZ ENDP

; retail @ 0x009A9980 size 155
public ?d_009a9980@@YAXXZ
?d_009a9980@@YAXXZ PROC
    db 51h, 53h, 56h, 8Bh, 74h, 24h, 28h, 8Bh, 0C6h, 0D1h, 0E8h, 89h, 44h, 24h, 08h, 8Bh
    db 44h, 24h, 14h, 57h, 8Bh, 7Ch, 24h, 14h, 8Ah, 1Fh, 03h, 0F8h, 8Ah, 07h, 88h, 44h
    db 24h, 2Ch, 8Bh, 44h, 24h, 28h, 0Fh, 0AFh, 44h, 24h, 30h, 33h, 0C9h, 85h, 0C0h, 8Bh
    db 0D6h, 89h, 4Ch, 24h, 14h, 89h, 44h, 24h, 30h, 76h, 5Bh, 55h, 8Dh, 64h, 24h, 00h
    db 0Fh, 0B6h, 6Ch, 24h, 30h, 0Fh, 0AFh, 0E9h, 0Fh, 0B6h, 0C3h, 0Fh, 0AFh, 0C2h, 03h, 6Ch
    db 24h, 10h, 33h, 0D2h, 03h, 0C5h, 0F7h, 0F6h, 8Bh, 54h, 24h, 28h, 8Bh, 6Ch, 24h, 18h
    db 88h, 04h, 2Ah, 03h, 4Ch, 24h, 20h, 3Bh, 0CEh, 76h, 16h, 8Bh, 44h, 24h, 1Ch, 90h
    db 8Ah, 1Fh, 8Ah, 14h, 07h, 03h, 0F8h, 2Bh, 0CEh, 3Bh, 0CEh, 88h, 54h, 24h, 30h, 77h
    db 0EFh, 03h, 6Ch, 24h, 2Ch, 8Bh, 44h, 24h, 34h, 8Bh, 0D6h, 2Bh, 0D1h, 3Bh, 0E8h, 89h
    db 6Ch, 24h, 18h, 72h, 0ABh, 5Dh, 5Fh, 5Eh, 5Bh, 59h, 0C3h
?d_009a9980@@YAXXZ ENDP

; retail @ 0x009A9A20 size 98
public ?d_009a9a20@@YAXXZ
?d_009a9a20@@YAXXZ PROC
    db 8Bh, 54h, 24h, 08h, 8Bh, 4Ch, 24h, 14h, 55h, 8Bh, 6Ch, 24h, 08h, 8Ah, 45h, 00h
    db 56h, 8Bh, 74h, 24h, 20h, 57h, 8Bh, 0FEh, 0Fh, 0AFh, 7Ch, 24h, 2Ch, 03h, 0D2h, 3Bh
    db 0F7h, 88h, 01h, 73h, 39h, 8Dh, 0Ch, 2Ah, 53h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 1Ch, 11h, 0Fh, 0B6h, 45h, 00h, 03h, 0C3h, 8Dh, 1Ch, 40h, 0Fh, 0B6h, 01h
    db 8Dh, 04h, 80h, 8Dh, 44h, 43h, 08h, 8Bh, 5Ch, 24h, 24h, 0C1h, 0E8h, 04h, 88h, 04h
    db 1Eh, 03h, 74h, 24h, 28h, 03h, 0EAh, 03h, 0CAh, 3Bh, 0F7h, 72h, 0D3h, 5Bh, 5Fh, 5Eh
    db 5Dh, 0C3h
?d_009a9a20@@YAXXZ ENDP

; retail @ 0x009AA100 size 161
_TEXT ENDS
_TEXT$d00daa100 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAA100 size 161
public ?d_009aa100@@YAXXZ
?d_009aa100@@YAXXZ PROC
    db 051h, 08Bh, 044h, 024h, 010h, 08Bh, 048h, 004h, 053h, 055h, 056h, 08Bh, 074h, 024h, 014h, 08Bh
    db 06Eh, 044h, 08Bh, 05Eh, 040h, 08Bh, 056h, 078h, 057h, 08Bh, 038h, 08Bh, 040h, 018h, 051h, 057h
    db 057h, 050h, 08Bh, 044h, 024h, 02Ch, 055h, 089h, 04Ch, 024h, 02Ch, 053h, 08Dh, 04Bh, 020h, 051h
    db 003h, 0D0h, 052h, 056h
    call ?Rva009A9400@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 044h, 024h, 03Ch, 0D1h, 0F8h, 050h, 089h, 044h, 024h, 040h, 08Bh, 044h, 024h, 048h, 08Bh
    db 050h, 01Ch, 08Bh, 046h, 07Ch, 0D1h, 0FFh, 057h, 057h, 052h, 0D1h, 0FDh, 055h, 0D1h, 0FBh, 08Dh
    db 04Bh, 010h, 053h, 051h, 089h, 04Ch, 024h, 050h, 003h, 044h, 024h, 05Ch, 050h, 056h
    call ?Rva009A9400@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 04Ch, 024h, 060h, 08Bh, 054h, 024h, 068h, 08Bh, 042h, 020h, 08Bh, 096h, 080h, 000h, 000h
    db 000h, 083h, 0C4h, 048h, 051h, 08Bh, 04Ch, 024h, 014h, 057h, 057h, 050h, 055h, 053h, 08Bh, 05Ch
    db 024h, 034h, 051h, 003h, 0D3h, 052h, 056h
    call ?Rva009A9400@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 083h, 0C4h, 024h, 05Fh, 05Eh, 05Dh, 05Bh, 059h, 0C3h
?d_009aa100@@YAXXZ ENDP
_TEXT$d00daa100 ENDS
_TEXT SEGMENT

; retail @ 0x009AA1B0 size 161
_TEXT ENDS
_TEXT$d00daa1b0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAA1B0 size 161
public ?d_009aa1b0@@YAXXZ
?d_009aa1b0@@YAXXZ PROC
    db 051h, 08Bh, 044h, 024h, 010h, 08Bh, 048h, 004h, 053h, 055h, 056h, 08Bh, 074h, 024h, 014h, 08Bh
    db 06Eh, 044h, 08Bh, 05Eh, 040h, 08Bh, 056h, 078h, 057h, 08Bh, 038h, 08Bh, 040h, 018h, 051h, 057h
    db 057h, 050h, 08Bh, 044h, 024h, 02Ch, 055h, 089h, 04Ch, 024h, 02Ch, 053h, 08Dh, 04Bh, 020h, 051h
    db 003h, 0D0h, 052h, 056h
    call ?Rva009A97B0@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 044h, 024h, 03Ch, 0D1h, 0F8h, 050h, 089h, 044h, 024h, 040h, 08Bh, 044h, 024h, 048h, 08Bh
    db 050h, 01Ch, 08Bh, 046h, 07Ch, 0D1h, 0FFh, 057h, 057h, 052h, 0D1h, 0FDh, 055h, 0D1h, 0FBh, 08Dh
    db 04Bh, 010h, 053h, 051h, 089h, 04Ch, 024h, 050h, 003h, 044h, 024h, 05Ch, 050h, 056h
    call ?Rva009A97B0@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 04Ch, 024h, 060h, 08Bh, 054h, 024h, 068h, 08Bh, 042h, 020h, 08Bh, 096h, 080h, 000h, 000h
    db 000h, 083h, 0C4h, 048h, 051h, 08Bh, 04Ch, 024h, 014h, 057h, 057h, 050h, 055h, 053h, 08Bh, 05Ch
    db 024h, 034h, 051h, 003h, 0D3h, 052h, 056h
    call ?Rva009A97B0@@YAXPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 083h, 0C4h, 024h, 05Fh, 05Eh, 05Dh, 05Bh, 059h, 0C3h
?d_009aa1b0@@YAXXZ ENDP
_TEXT$d00daa1b0 ENDS
_TEXT SEGMENT

; retail @ 0x009AB950 size 51
public ?d_009ab950@@YAXXZ
?d_009ab950@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 56h, 8Bh, 74h, 81h
    db 0Ch, 89h, 72h, 04h, 8Bh, 71h, 04h, 0C1h, 0E0h, 07h, 66h, 8Bh, 04h, 30h, 66h, 89h
    db 42h, 0Ah, 8Bh, 49h, 08h, 66h, 8Bh, 04h, 8Dh, 0A0h, 2Bh, 14h, 01h, 66h, 89h, 42h
    db 08h, 5Eh, 0C3h
?d_009ab950@@YAXXZ ENDP

; retail @ 0x009AB990 size 51
public ?d_009ab990@@YAXXZ
?d_009ab990@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 56h, 8Bh, 74h, 81h
    db 0Ch, 89h, 72h, 04h, 8Bh, 71h, 04h, 0C1h, 0E0h, 07h, 66h, 8Bh, 04h, 30h, 66h, 89h
    db 42h, 0Ah, 8Bh, 49h, 08h, 66h, 8Bh, 04h, 8Dh, 0A0h, 2Bh, 14h, 01h, 66h, 89h, 42h
    db 08h, 5Eh, 0C3h
?d_009ab990@@YAXXZ ENDP

; retail @ 0x009AC240 size 36
public ?d_009ac240@@YAXXZ
?d_009ac240@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 08h, 33h, 0C9h, 89h, 08h, 0C7h, 40h, 04h, 0FFh
    db 00h, 00h, 00h, 89h, 48h, 08h, 0C7h, 40h, 0Ch, 0E8h, 0FFh, 0FFh, 0FFh, 89h, 50h, 14h
    db 89h, 48h, 10h, 0C3h
?d_009ac240@@YAXXZ ENDP

; retail @ 0x009AC270 size 114
public ?d_009ac270@@YAXXZ
?d_009ac270@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 50h, 0Ch, 83h, 0FAh, 0F0h, 7Dh, 07h, 0B9h, 18h, 00h, 00h
    db 00h, 0EBh, 0Fh, 83h, 0FAh, 0F8h, 0B9h, 10h, 00h, 00h, 00h, 7Ch, 05h, 0B9h, 08h, 00h
    db 00h, 00h, 83h, 0E2h, 07h, 2Bh, 0CAh, 8Bh, 10h, 0D3h, 0E2h, 8Bh, 48h, 14h, 53h, 89h
    db 10h, 8Bh, 50h, 10h, 8Ah, 58h, 03h, 88h, 1Ch, 11h, 8Bh, 48h, 10h, 8Bh, 50h, 14h
    db 8Ah, 58h, 02h, 41h, 89h, 48h, 10h, 88h, 1Ch, 11h, 8Bh, 58h, 10h, 8Bh, 50h, 14h
    db 43h, 89h, 58h, 10h, 8Bh, 0CBh, 8Ah, 58h, 01h, 88h, 1Ch, 11h, 8Bh, 50h, 10h, 8Ah
    db 18h, 42h, 89h, 50h, 10h, 8Bh, 0CAh, 8Bh, 50h, 14h, 88h, 1Ch, 11h, 0FFh, 40h, 10h
    db 5Bh, 0C3h
?d_009ac270@@YAXXZ ENDP

; retail @ 0x009AC390 size 133
public ?d_009ac390@@YAXXZ
?d_009ac390@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 8Bh, 58h, 0Ch, 56h, 8Bh, 30h, 57h, 8Bh, 78h, 04h, 8Dh
    db 4Fh, 0FFh, 0Fh, 0AFh, 4Ch, 24h, 18h, 0C1h, 0E9h, 08h, 41h, 2Bh, 0F9h, 03h, 0F1h, 81h
    db 0FFh, 80h, 00h, 00h, 00h, 73h, 52h, 55h, 0D1h, 0E7h, 85h, 0F6h, 79h, 1Dh, 8Bh, 48h
    db 10h, 49h, 78h, 10h, 8Bh, 50h, 14h, 03h, 0D1h, 80h, 3Ah, 0FFh, 75h, 06h, 49h, 0C6h
    db 02h, 00h, 79h, 0F0h, 8Bh, 50h, 14h, 03h, 0CAh, 0FEh, 01h, 0D1h, 0E6h, 43h, 75h, 20h
    db 8Bh, 50h, 14h, 8Bh, 68h, 10h, 8Bh, 0CEh, 0C1h, 0E9h, 18h, 88h, 0Ch, 2Ah, 8Bh, 50h
    db 10h, 42h, 0BBh, 0F8h, 0FFh, 0FFh, 0FFh, 89h, 50h, 10h, 81h, 0E6h, 0FFh, 0FFh, 0FFh, 00h
    db 81h, 0FFh, 80h, 00h, 00h, 00h, 72h, 0B0h, 5Dh, 89h, 78h, 04h, 5Fh, 89h, 30h, 5Eh
    db 89h, 58h, 0Ch, 5Bh, 0C3h
?d_009ac390@@YAXXZ ENDP

; retail @ 0x009AC420 size 129
public ?d_009ac420@@YAXXZ
?d_009ac420@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 8Bh, 58h, 0Ch, 56h, 8Bh, 70h, 04h, 4Eh, 0Fh, 0AFh, 74h
    db 24h, 14h, 0C1h, 0EEh, 08h, 46h, 81h, 0FEh, 80h, 00h, 00h, 00h, 57h, 8Bh, 38h, 73h
    db 54h, 55h, 0D1h, 0E6h, 85h, 0FFh, 79h, 1Fh, 8Bh, 48h, 10h, 49h, 78h, 12h, 8Bh, 0FFh
    db 8Bh, 50h, 14h, 03h, 0D1h, 80h, 3Ah, 0FFh, 75h, 06h, 49h, 0C6h, 02h, 00h, 79h, 0F0h
    db 8Bh, 50h, 14h, 03h, 0CAh, 0FEh, 01h, 0D1h, 0E7h, 43h, 75h, 20h, 8Bh, 50h, 14h, 8Bh
    db 68h, 10h, 8Bh, 0CFh, 0C1h, 0E9h, 18h, 88h, 0Ch, 2Ah, 8Bh, 50h, 10h, 42h, 0BBh, 0F8h
    db 0FFh, 0FFh, 0FFh, 89h, 50h, 10h, 81h, 0E7h, 0FFh, 0FFh, 0FFh, 00h, 81h, 0FEh, 80h, 00h
    db 00h, 00h, 72h, 0AEh, 5Dh, 89h, 38h, 5Fh, 89h, 70h, 04h, 5Eh, 89h, 58h, 0Ch, 5Bh
    db 0C3h
?d_009ac420@@YAXXZ ENDP

; retail @ 0x009ACB80 size 27
public ?d_009acb80@@YAXXZ
?d_009acb80@@YAXXZ PROC
    db 8Ah, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 88h, 81h, 0ACh, 01h, 00h, 00h, 0C3h, 0CCh
    db 8Bh, 44h, 24h, 04h, 8Ah, 80h, 0ACh, 01h, 00h, 00h, 0C3h
?d_009acb80@@YAXXZ ENDP

; retail @ 0x009ACC80 size 773
public ?d_009acc80@@YAXXZ
?d_009acc80@@YAXXZ PROC
    db 83h, 0ECh, 4Ch, 8Bh, 44h, 24h, 60h, 56h, 8Bh, 74h, 24h, 68h, 8Dh, 44h, 30h, 0FFh
    db 3Bh, 0F0h, 89h, 74h, 24h, 04h, 89h, 44h, 24h, 24h, 0Fh, 83h, 0E0h, 02h, 00h, 00h
    db 8Bh, 44h, 24h, 58h, 8Bh, 4Ch, 24h, 5Ch, 53h, 8Bh, 5Ch, 24h, 58h, 55h, 8Bh, 0D0h
    db 2Bh, 0D1h, 57h, 8Dh, 78h, 08h, 83h, 0C1h, 05h, 89h, 54h, 24h, 24h, 89h, 7Ch, 24h
    db 1Ch, 89h, 4Ch, 24h, 20h, 8Bh, 53h, 24h, 8Bh, 44h, 0B2h, 04h, 8Bh, 54h, 24h, 78h
    db 8Bh, 04h, 82h, 89h, 44h, 24h, 70h, 0Fh, 0AFh, 0C0h, 8Dh, 04h, 40h, 0C1h, 0F8h, 05h
    db 89h, 44h, 24h, 28h, 89h, 4Ch, 24h, 74h, 0C7h, 44h, 24h, 18h, 08h, 00h, 00h, 00h
    db 0Fh, 0B6h, 17h, 8Bh, 44h, 24h, 24h, 0Fh, 0B6h, 1Ch, 08h, 0Fh, 0B6h, 4Fh, 0FEh, 0Fh
    db 0B6h, 47h, 0FFh, 89h, 54h, 24h, 48h, 0Fh, 0B6h, 57h, 01h, 89h, 54h, 24h, 4Ch, 0Fh
    db 0B6h, 57h, 03h, 0Fh, 0B6h, 77h, 0FCh, 89h, 54h, 24h, 54h, 8Dh, 14h, 08h, 89h, 4Ch
    db 24h, 40h, 0Fh, 0AFh, 0C9h, 89h, 44h, 24h, 44h, 0Fh, 0AFh, 0C0h, 03h, 0C1h, 0Fh, 0B6h
    db 6Fh, 02h, 8Bh, 0CBh, 0Fh, 0AFh, 0CBh, 03h, 0C1h, 03h, 0D3h, 8Bh, 0CEh, 0Fh, 0AFh, 0CEh
    db 03h, 0D6h, 89h, 5Ch, 24h, 3Ch, 8Bh, 5Ch, 24h, 4Ch, 03h, 0C1h, 8Bh, 4Ch, 24h, 54h
    db 89h, 74h, 24h, 38h, 8Dh, 34h, 29h, 0Fh, 0AFh, 0C9h, 03h, 0F3h, 03h, 74h, 24h, 48h
    db 8Bh, 0DDh, 0Fh, 0AFh, 0DDh, 03h, 0CBh, 8Bh, 5Ch, 24h, 4Ch, 89h, 6Ch, 24h, 50h, 8Bh
    db 0EBh, 0Fh, 0AFh, 0EBh, 03h, 0CDh, 8Bh, 6Ch, 24h, 48h, 8Bh, 0DDh, 0Fh, 0AFh, 0DDh, 03h
    db 0CBh, 8Dh, 5Ah, 01h, 0D1h, 0FAh, 0D1h, 0FBh, 0Fh, 0AFh, 0DAh, 8Dh, 56h, 01h, 0D1h, 0FAh
    db 0D1h, 0FEh, 0Fh, 0AFh, 0D6h, 8Bh, 74h, 24h, 10h, 2Bh, 0CAh, 2Bh, 0C3h, 8Bh, 5Ch, 24h
    db 60h, 8Bh, 53h, 28h, 01h, 04h, 0B2h, 8Dh, 14h, 0B2h, 8Bh, 53h, 28h, 01h, 4Ch, 0B2h
    db 04h, 8Dh, 54h, 0B2h, 04h, 8Bh, 54h, 24h, 28h, 3Bh, 0C2h, 0Fh, 8Dh, 76h, 01h, 00h
    db 00h, 3Bh, 0CAh, 0Fh, 8Dh, 6Eh, 01h, 00h, 00h, 8Bh, 54h, 24h, 44h, 8Bh, 4Ch, 24h
    db 70h, 8Bh, 0C5h, 2Bh, 0C2h, 3Bh, 0C1h, 0Fh, 8Dh, 5Ah, 01h, 00h, 00h, 8Bh, 0C2h, 2Bh
    db 0C5h, 3Bh, 0C1h, 0Fh, 8Dh, 4Eh, 01h, 00h, 00h, 0Fh, 0B6h, 5Fh, 0FCh, 0Fh, 0B6h, 77h
    db 0FBh, 8Bh, 0C3h, 2Bh, 0C6h, 85h, 0C0h, 7Fh, 04h, 8Bh, 0C6h, 2Bh, 0C3h, 3Bh, 0C1h, 7Ch
    db 02h, 8Bh, 0F3h, 0Fh, 0B6h, 4Fh, 03h, 0Fh, 0B6h, 5Fh, 04h, 8Bh, 0C1h, 2Bh, 0C3h, 85h
    db 0C0h, 7Fh, 04h, 8Bh, 0C3h, 2Bh, 0C1h, 3Bh, 44h, 24h, 70h, 7Dh, 06h, 89h, 5Ch, 24h
    db 14h, 0EBh, 08h, 0Fh, 0B6h, 47h, 03h, 89h, 44h, 24h, 14h, 8Bh, 5Ch, 24h, 40h, 8Bh
    db 4Ch, 24h, 38h, 8Dh, 04h, 72h, 03h, 0C6h, 03h, 0C3h, 8Bh, 5Ch, 24h, 3Ch, 03h, 0C3h
    db 8Dh, 44h, 08h, 04h, 03h, 0C8h, 0D1h, 0E1h, 2Bh, 0CAh, 03h, 0CDh, 0C1h, 0F9h, 04h, 8Bh
    db 0D1h, 8Bh, 4Ch, 24h, 74h, 88h, 51h, 0FFh, 8Bh, 0D5h, 2Bh, 0D6h, 03h, 0C2h, 8Dh, 14h
    db 18h, 0D1h, 0E2h, 8Bh, 0DAh, 8Bh, 54h, 24h, 4Ch, 2Bh, 0DDh, 03h, 0DAh, 0C1h, 0FBh, 04h
    db 88h, 19h, 8Bh, 0DAh, 2Bh, 0DEh, 03h, 0C3h, 8Bh, 5Ch, 24h, 40h, 03h, 0D8h, 0D1h, 0E3h
    db 2Bh, 0DAh, 8Bh, 54h, 24h, 50h, 03h, 0DAh, 0C1h, 0FBh, 04h, 88h, 59h, 01h, 8Bh, 0DAh
    db 2Bh, 0DEh, 03h, 0C3h, 8Bh, 5Ch, 24h, 44h, 03h, 0D8h, 0D1h, 0E3h, 2Bh, 0DAh, 8Bh, 54h
    db 24h, 38h, 2Bh, 0DAh, 03h, 0DEh, 8Bh, 74h, 24h, 54h, 03h, 0DEh, 0C1h, 0FBh, 04h, 88h
    db 59h, 02h, 8Bh, 0DEh, 2Bh, 0DAh, 03h, 0C3h, 8Dh, 1Ch, 28h, 0D1h, 0E3h, 2Bh, 0DEh, 2Bh
    db 5Ch, 24h, 3Ch, 8Bh, 74h, 24h, 14h, 03h, 0DEh, 03h, 0DAh, 0C1h, 0FBh, 04h, 88h, 59h
    db 03h, 8Bh, 5Ch, 24h, 3Ch, 8Bh, 0D6h, 2Bh, 0D3h, 8Bh, 5Ch, 24h, 40h, 03h, 0C2h, 8Bh
    db 54h, 24h, 4Ch, 03h, 0D0h, 0D1h, 0E2h, 2Bh, 0D3h, 03h, 54h, 24h, 3Ch, 8Bh, 5Ch, 24h
    db 40h, 0C1h, 0FAh, 04h, 88h, 51h, 04h, 8Bh, 0D6h, 2Bh, 0D3h, 8Bh, 5Ch, 24h, 44h, 03h
    db 0C2h, 8Bh, 54h, 24h, 50h, 03h, 0D0h, 03h, 0C6h, 03h, 44h, 24h, 54h, 8Bh, 74h, 24h
    db 44h, 0D1h, 0E2h, 2Bh, 0D3h, 8Bh, 5Ch, 24h, 40h, 0D1h, 0E0h, 03h, 0D3h, 8Bh, 5Ch, 24h
    db 60h, 2Bh, 0C5h, 2Bh, 0C6h, 8Bh, 74h, 24h, 10h, 0C1h, 0FAh, 04h, 0C1h, 0F8h, 04h, 88h
    db 51h, 05h, 88h, 41h, 06h, 0EBh, 04h, 8Bh, 4Ch, 24h, 74h, 8Bh, 44h, 24h, 6Ch, 03h
    db 0C8h, 03h, 0F8h, 8Bh, 44h, 24h, 18h, 48h, 89h, 4Ch, 24h, 74h, 89h, 44h, 24h, 18h
    db 0Fh, 85h, 9Ah, 0FDh, 0FFh, 0FFh, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 20h, 8Bh, 44h
    db 24h, 30h, 46h, 83h, 0C7h, 08h, 83h, 0C1h, 08h, 3Bh, 0F0h, 89h, 74h, 24h, 10h, 89h
    db 7Ch, 24h, 1Ch, 89h, 4Ch, 24h, 20h, 0Fh, 82h, 48h, 0FDh, 0FFh, 0FFh, 5Fh, 5Dh, 5Bh
    db 5Eh, 83h, 0C4h, 4Ch, 0C3h
?d_009acc80@@YAXXZ ENDP

; retail @ 0x009ACF90 size 1976
public ?d_009acf90@@YAXXZ
?d_009acf90@@YAXXZ PROC
    db 81h, 0ECh, 84h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 94h, 00h, 00h, 00h, 8Bh, 94h, 24h
    db 98h, 00h, 00h, 00h, 53h, 8Bh, 9Ch, 24h, 8Ch, 00h, 00h, 00h, 55h, 56h, 57h, 8Bh
    db 0BCh, 24h, 0ACh, 00h, 00h, 00h, 03h, 0D7h, 8Dh, 2Ch, 49h, 89h, 54h, 24h, 1Ch, 3Bh
    db 0FAh, 8Bh, 94h, 24h, 0A0h, 00h, 00h, 00h, 89h, 7Ch, 24h, 14h, 8Dh, 34h, 09h, 89h
    db 6Ch, 24h, 50h, 8Dh, 04h, 8Dh, 00h, 00h, 00h, 00h, 0Fh, 83h, 84h, 04h, 00h, 00h
    db 8Bh, 0FDh, 2Bh, 0F8h, 89h, 7Ch, 24h, 7Ch, 8Bh, 0FDh, 2Bh, 0F9h, 89h, 0BCh, 24h, 84h
    db 00h, 00h, 00h, 8Bh, 0F9h, 2Bh, 0FEh, 2Bh, 0EEh, 8Bh, 0B4h, 24h, 9Ch, 00h, 00h, 00h
    db 89h, 7Ch, 24h, 78h, 89h, 6Ch, 24h, 5Ch, 8Bh, 0EEh, 2Bh, 0EAh, 8Dh, 14h, 89h, 8Bh
    db 0F8h, 2Bh, 0FAh, 8Bh, 0D1h, 2Bh, 0D0h, 89h, 94h, 24h, 8Ch, 00h, 00h, 00h, 89h, 7Ch
    db 24h, 70h, 8Bh, 7Ch, 24h, 50h, 8Bh, 0D0h, 2Bh, 0D7h, 89h, 94h, 24h, 90h, 00h, 00h
    db 00h, 8Dh, 3Ch, 09h, 8Bh, 0D0h, 2Bh, 0D7h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 8Bh
    db 0D0h, 2Bh, 0D1h, 8Bh, 4Ch, 24h, 1Ch, 89h, 94h, 24h, 80h, 00h, 00h, 00h, 8Dh, 14h
    db 8Dh, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 50h, 89h, 54h, 24h, 64h, 8Bh, 0D6h, 2Bh
    db 0F0h, 8Bh, 84h, 24h, 0A0h, 00h, 00h, 00h, 89h, 7Ch, 24h, 18h, 8Bh, 0F8h, 2Bh, 0F9h
    db 8Bh, 4Ch, 24h, 18h, 89h, 6Ch, 24h, 6Ch, 89h, 54h, 24h, 54h, 03h, 0C8h, 8Bh, 0FFh
    db 8Bh, 43h, 24h, 8Bh, 5Ch, 24h, 64h, 8Bh, 04h, 03h, 8Bh, 9Ch, 24h, 0B0h, 00h, 00h
    db 00h, 8Bh, 04h, 83h, 89h, 44h, 24h, 20h, 0Fh, 0AFh, 0C0h, 8Dh, 04h, 40h, 0C1h, 0F8h
    db 05h, 89h, 44h, 24h, 68h, 8Bh, 44h, 24h, 50h, 89h, 54h, 24h, 58h, 03h, 0D0h, 89h
    db 54h, 24h, 4Ch, 89h, 74h, 24h, 10h, 89h, 4Ch, 24h, 74h, 0C7h, 44h, 24h, 18h, 08h
    db 00h, 00h, 00h, 0EBh, 0Bh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 0Fh, 0B6h, 1Eh, 8Bh, 84h, 24h, 88h, 00h, 00h, 00h, 0Fh, 0B6h, 04h, 06h, 89h, 44h
    db 24h, 30h, 8Bh, 84h, 24h, 80h, 00h, 00h, 00h, 0Fh, 0B6h, 04h, 06h, 8Bh, 74h, 24h
    db 58h, 0Fh, 0B6h, 36h, 89h, 74h, 24h, 38h, 8Bh, 0B4h, 24h, 90h, 00h, 00h, 00h, 03h
    db 0D6h, 8Bh, 0B4h, 24h, 8Ch, 00h, 00h, 00h, 0Fh, 0B6h, 2Ch, 2Fh, 89h, 54h, 24h, 60h
    db 0Fh, 0B6h, 14h, 16h, 8Bh, 74h, 24h, 30h, 89h, 54h, 24h, 3Ch, 0Fh, 0AFh, 0F6h, 8Bh
    db 54h, 24h, 6Ch, 0Fh, 0B6h, 0Ch, 0Ah, 8Bh, 54h, 24h, 4Ch, 89h, 4Ch, 24h, 40h, 0Fh
    db 0B6h, 0Ah, 8Bh, 54h, 24h, 30h, 03h, 0D0h, 89h, 44h, 24h, 34h, 0Fh, 0AFh, 0C0h, 03h
    db 0C6h, 8Bh, 0F5h, 0Fh, 0AFh, 0F5h, 03h, 0C6h, 8Bh, 0F3h, 0Fh, 0AFh, 0F3h, 03h, 0D5h, 03h
    db 0D3h, 03h, 0C6h, 8Bh, 74h, 24h, 40h, 03h, 0F1h, 89h, 5Ch, 24h, 28h, 03h, 74h, 24h
    db 3Ch, 8Bh, 5Ch, 24h, 40h, 89h, 6Ch, 24h, 2Ch, 03h, 74h, 24h, 38h, 8Bh, 0EBh, 0Fh
    db 0AFh, 0EBh, 8Bh, 5Ch, 24h, 3Ch, 89h, 4Ch, 24h, 44h, 0Fh, 0AFh, 0C9h, 03h, 0CDh, 8Bh
    db 0EBh, 0Fh, 0AFh, 0EBh, 03h, 0CDh, 8Bh, 6Ch, 24h, 38h, 8Bh, 0DDh, 0Fh, 0AFh, 0DDh, 03h
    db 0CBh, 8Dh, 5Ah, 01h, 0D1h, 0FAh, 0D1h, 0FBh, 0Fh, 0AFh, 0DAh, 8Dh, 56h, 01h, 0D1h, 0FEh
    db 0D1h, 0FAh, 0Fh, 0AFh, 0D6h, 8Bh, 74h, 24h, 14h, 2Bh, 0C3h, 8Bh, 9Ch, 24h, 98h, 00h
    db 00h, 00h, 2Bh, 0CAh, 8Bh, 53h, 28h, 8Dh, 14h, 0B2h, 01h, 02h, 8Bh, 53h, 28h, 8Bh
    db 74h, 24h, 64h, 03h, 0D6h, 01h, 0Ah, 8Bh, 54h, 24h, 68h, 3Bh, 0C2h, 0Fh, 8Dh, 0B0h
    db 01h, 00h, 00h, 3Bh, 0CAh, 0Fh, 8Dh, 0A8h, 01h, 00h, 00h, 8Bh, 54h, 24h, 34h, 8Bh
    db 44h, 24h, 20h, 8Bh, 0CDh, 2Bh, 0CAh, 3Bh, 0C8h, 0Fh, 8Dh, 94h, 01h, 00h, 00h, 8Bh
    db 0CAh, 2Bh, 0CDh, 3Bh, 0C8h, 0Fh, 8Dh, 88h, 01h, 00h, 00h, 8Bh, 74h, 24h, 10h, 8Bh
    db 44h, 24h, 70h, 0Fh, 0B6h, 0Eh, 0Fh, 0B6h, 1Ch, 30h, 8Bh, 0C1h, 2Bh, 0C3h, 85h, 0C0h
    db 7Fh, 04h, 8Bh, 0C3h, 2Bh, 0C1h, 3Bh, 44h, 24h, 20h, 8Bh, 0CBh, 7Ch, 03h, 0Fh, 0B6h
    db 0Eh, 8Bh, 44h, 24h, 60h, 0Fh, 0B6h, 18h, 8Bh, 44h, 24h, 4Ch, 0Fh, 0B6h, 00h, 89h
    db 44h, 24h, 10h, 2Bh, 0C3h, 85h, 0C0h, 89h, 5Ch, 24h, 60h, 7Fh, 06h, 8Bh, 0C3h, 2Bh
    db 44h, 24h, 10h, 3Bh, 44h, 24h, 20h, 8Bh, 44h, 24h, 60h, 7Ch, 04h, 8Bh, 44h, 24h
    db 10h, 8Bh, 5Ch, 24h, 30h, 89h, 44h, 24h, 10h, 8Dh, 04h, 4Ah, 03h, 0C1h, 03h, 0C3h
    db 03h, 44h, 24h, 2Ch, 8Bh, 5Ch, 24h, 28h, 8Dh, 44h, 18h, 04h, 03h, 0D8h, 0D1h, 0E3h
    db 2Bh, 0DAh, 03h, 0DDh, 0C1h, 0FBh, 04h, 8Bh, 54h, 24h, 7Ch, 88h, 1Ch, 3Ah, 8Bh, 0D5h
    db 2Bh, 0D1h, 03h, 0C2h, 8Bh, 54h, 24h, 2Ch, 03h, 0D0h, 0D1h, 0E2h, 8Bh, 0DAh, 8Bh, 54h
    db 24h, 3Ch, 2Bh, 0DDh, 03h, 0DAh, 0C1h, 0FBh, 04h, 88h, 1Fh, 8Bh, 0DAh, 2Bh, 0D9h, 03h
    db 0C3h, 8Bh, 5Ch, 24h, 30h, 03h, 0D8h, 0D1h, 0E3h, 2Bh, 0DAh, 03h, 5Ch, 24h, 40h, 8Bh
    db 54h, 24h, 5Ch, 0C1h, 0FBh, 04h, 88h, 1Ch, 3Ah, 8Bh, 54h, 24h, 40h, 8Bh, 0DAh, 2Bh
    db 0D9h, 03h, 0C3h, 8Bh, 5Ch, 24h, 34h, 03h, 0D8h, 0D1h, 0E3h, 2Bh, 0DAh, 8Bh, 54h, 24h
    db 28h, 2Bh, 0DAh, 03h, 0D9h, 03h, 5Ch, 24h, 44h, 8Bh, 8Ch, 24h, 84h, 00h, 00h, 00h
    db 0C1h, 0FBh, 04h, 88h, 1Ch, 39h, 8Bh, 4Ch, 24h, 44h, 8Bh, 0D9h, 2Bh, 0DAh, 03h, 0C3h
    db 8Dh, 1Ch, 28h, 0D1h, 0E3h, 2Bh, 0D9h, 2Bh, 5Ch, 24h, 2Ch, 8Bh, 4Ch, 24h, 10h, 03h
    db 0D9h, 03h, 0DAh, 8Bh, 54h, 24h, 50h, 0C1h, 0FBh, 04h, 88h, 1Ch, 17h, 8Bh, 5Ch, 24h
    db 30h, 8Bh, 0D1h, 8Bh, 4Ch, 24h, 2Ch, 2Bh, 0D1h, 03h, 0C2h, 8Bh, 54h, 24h, 3Ch, 03h
    db 0D0h, 0D1h, 0E2h, 2Bh, 0D3h, 03h, 0D1h, 8Bh, 4Ch, 24h, 74h, 8Bh, 5Ch, 24h, 78h, 0C1h
    db 0FAh, 04h, 88h, 14h, 0Bh, 8Bh, 5Ch, 24h, 30h, 8Bh, 54h, 24h, 10h, 2Bh, 0D3h, 8Bh
    db 5Ch, 24h, 34h, 03h, 0C2h, 8Bh, 54h, 24h, 40h, 03h, 0D0h, 0D1h, 0E2h, 2Bh, 0D3h, 03h
    db 54h, 24h, 30h, 8Bh, 5Ch, 24h, 34h, 0C1h, 0FAh, 04h, 88h, 11h, 8Bh, 54h, 24h, 10h
    db 03h, 0C2h, 03h, 44h, 24h, 44h, 8Bh, 54h, 24h, 5Ch, 0D1h, 0E0h, 2Bh, 0C5h, 8Bh, 6Ch
    db 24h, 6Ch, 2Bh, 0C3h, 8Bh, 9Ch, 24h, 98h, 00h, 00h, 00h, 0C1h, 0F8h, 04h, 88h, 04h
    db 0Ah, 0EBh, 73h, 8Bh, 74h, 24h, 10h, 8Ah, 06h, 8Bh, 4Ch, 24h, 7Ch, 8Bh, 6Ch, 24h
    db 6Ch, 88h, 04h, 39h, 8Ah, 14h, 2Fh, 8Bh, 84h, 24h, 88h, 00h, 00h, 00h, 88h, 17h
    db 8Ah, 0Ch, 06h, 8Bh, 54h, 24h, 5Ch, 8Bh, 84h, 24h, 80h, 00h, 00h, 00h, 88h, 0Ch
    db 3Ah, 8Ah, 0Ch, 06h, 8Bh, 94h, 24h, 84h, 00h, 00h, 00h, 8Bh, 44h, 24h, 58h, 88h
    db 0Ch, 3Ah, 8Ah, 08h, 8Bh, 54h, 24h, 50h, 8Bh, 44h, 24h, 60h, 88h, 0Ch, 17h, 8Bh
    db 8Ch, 24h, 8Ch, 00h, 00h, 00h, 8Ah, 14h, 01h, 8Bh, 4Ch, 24h, 74h, 8Bh, 44h, 24h
    db 78h, 88h, 14h, 08h, 8Ah, 14h, 29h, 8Bh, 44h, 24h, 4Ch, 88h, 11h, 8Ah, 10h, 8Bh
    db 44h, 24h, 5Ch, 88h, 14h, 08h, 8Bh, 44h, 24h, 58h, 8Bh, 54h, 24h, 4Ch, 40h, 46h
    db 42h, 89h, 44h, 24h, 58h, 8Bh, 44h, 24h, 18h, 47h, 41h, 48h, 89h, 74h, 24h, 10h
    db 89h, 54h, 24h, 4Ch, 89h, 4Ch, 24h, 74h, 89h, 44h, 24h, 18h, 0Fh, 85h, 0AEh, 0FCh
    db 0FFh, 0FFh, 8Bh, 54h, 24h, 14h, 8Bh, 44h, 24h, 64h, 42h, 83h, 0C0h, 04h, 89h, 54h
    db 24h, 14h, 8Bh, 54h, 24h, 54h, 89h, 44h, 24h, 64h, 8Bh, 44h, 24h, 1Ch, 83h, 0C2h
    db 08h, 39h, 44h, 24h, 14h, 89h, 54h, 24h, 54h, 0Fh, 82h, 31h, 0FCh, 0FFh, 0FFh, 8Bh
    db 94h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 0BCh, 24h
    db 0ACh, 00h, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 48h, 3Bh, 0F8h, 89h, 7Ch, 24h, 14h, 89h
    db 44h, 24h, 70h, 0Fh, 83h, 0C4h, 02h, 00h, 00h, 0C1h, 0E1h, 03h, 2Bh, 0D1h, 83h, 0C2h
    db 08h, 8Bh, 0C2h, 89h, 44h, 24h, 18h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 53h, 24h, 8Bh, 4Ch, 0BAh, 04h, 8Bh, 94h, 24h, 0B0h, 00h, 00h, 00h, 8Bh, 0Ch
    db 8Ah, 89h, 4Ch, 24h, 20h, 0Fh, 0AFh, 0C9h, 8Dh, 0Ch, 49h, 0C1h, 0F9h, 05h, 89h, 44h
    db 24h, 1Ch, 89h, 4Ch, 24h, 68h, 83h, 0C0h, 0FEh, 0C7h, 44h, 24h, 54h, 08h, 00h, 00h
    db 00h, 0Fh, 0B6h, 70h, 02h, 0Fh, 0B6h, 10h, 0Fh, 0B6h, 48h, 01h, 0Fh, 0B6h, 58h, 0FFh
    db 89h, 74h, 24h, 38h, 0Fh, 0B6h, 70h, 03h, 89h, 74h, 24h, 3Ch, 0Fh, 0B6h, 70h, 05h
    db 0Fh, 0B6h, 78h, 0FEh, 89h, 74h, 24h, 44h, 8Dh, 34h, 11h, 89h, 54h, 24h, 30h, 0Fh
    db 0AFh, 0D2h, 89h, 4Ch, 24h, 34h, 0Fh, 0AFh, 0C9h, 03h, 0CAh, 0Fh, 0B6h, 68h, 04h, 8Bh
    db 0D3h, 0Fh, 0AFh, 0D3h, 03h, 0CAh, 03h, 0F3h, 8Bh, 0D7h, 0Fh, 0AFh, 0D7h, 03h, 0F7h, 89h
    db 5Ch, 24h, 2Ch, 8Bh, 5Ch, 24h, 3Ch, 03h, 0CAh, 8Bh, 54h, 24h, 44h, 89h, 7Ch, 24h
    db 28h, 8Dh, 3Ch, 2Ah, 0Fh, 0AFh, 0D2h, 03h, 0FBh, 03h, 7Ch, 24h, 38h, 8Bh, 0DDh, 0Fh
    db 0AFh, 0DDh, 03h, 0D3h, 8Bh, 5Ch, 24h, 3Ch, 89h, 6Ch, 24h, 40h, 8Bh, 0EBh, 0Fh, 0AFh
    db 0EBh, 03h, 0D5h, 8Bh, 6Ch, 24h, 38h, 8Bh, 0DDh, 0Fh, 0AFh, 0DDh, 03h, 0D3h, 8Dh, 5Eh
    db 01h, 0D1h, 0FEh, 0D1h, 0FBh, 0Fh, 0AFh, 0DEh, 8Dh, 77h, 01h, 0D1h, 0FEh, 0D1h, 0FFh, 0Fh
    db 0AFh, 0F7h, 8Bh, 7Ch, 24h, 14h, 2Bh, 0D6h, 2Bh, 0CBh, 8Bh, 9Ch, 24h, 98h, 00h, 00h
    db 00h, 8Bh, 73h, 28h, 01h, 0Ch, 0BEh, 8Dh, 34h, 0BEh, 8Bh, 73h, 28h, 01h, 54h, 0BEh
    db 04h, 8Dh, 74h, 0BEh, 04h, 8Bh, 74h, 24h, 68h, 3Bh, 0CEh, 0Fh, 8Dh, 6Eh, 01h, 00h
    db 00h, 3Bh, 0D6h, 0Fh, 8Dh, 66h, 01h, 00h, 00h, 8Bh, 54h, 24h, 34h, 8Bh, 74h, 24h
    db 20h, 8Bh, 0CDh, 2Bh, 0CAh, 3Bh, 0CEh, 0Fh, 8Dh, 52h, 01h, 00h, 00h, 8Bh, 0CAh, 2Bh
    db 0CDh, 3Bh, 0CEh, 0Fh, 8Dh, 46h, 01h, 00h, 00h, 0Fh, 0B6h, 58h, 0FEh, 0Fh, 0B6h, 48h
    db 0FDh, 8Bh, 0FBh, 2Bh, 0F9h, 85h, 0FFh, 7Fh, 04h, 8Bh, 0F9h, 2Bh, 0FBh, 3Bh, 0FEh, 8Bh
    db 0F1h, 7Ch, 02h, 8Bh, 0F3h, 0Fh, 0B6h, 48h, 05h, 0Fh, 0B6h, 58h, 06h, 8Bh, 0F9h, 2Bh
    db 0FBh, 85h, 0FFh, 7Fh, 04h, 8Bh, 0FBh, 2Bh, 0F9h, 3Bh, 7Ch, 24h, 20h, 7Dh, 06h, 89h
    db 5Ch, 24h, 10h, 0EBh, 08h, 0Fh, 0B6h, 48h, 05h, 89h, 4Ch, 24h, 10h, 8Bh, 5Ch, 24h
    db 30h, 8Bh, 7Ch, 24h, 2Ch, 8Dh, 0Ch, 72h, 03h, 0CEh, 03h, 0CBh, 03h, 0CFh, 8Bh, 7Ch
    db 24h, 28h, 8Dh, 4Ch, 39h, 04h, 8Dh, 1Ch, 39h, 0D1h, 0E3h, 2Bh, 0DAh, 03h, 0DDh, 0C1h
    db 0FBh, 04h, 88h, 58h, 0FEh, 8Bh, 0D5h, 2Bh, 0D6h, 03h, 0CAh, 8Bh, 54h, 24h, 2Ch, 03h
    db 0D1h, 0D1h, 0E2h, 8Bh, 0DAh, 8Bh, 54h, 24h, 3Ch, 2Bh, 0DDh, 03h, 0DAh, 0C1h, 0FBh, 04h
    db 88h, 58h, 0FFh, 8Bh, 0DAh, 2Bh, 0DEh, 03h, 0CBh, 8Bh, 5Ch, 24h, 30h, 03h, 0D9h, 0D1h
    db 0E3h, 2Bh, 0DAh, 8Bh, 54h, 24h, 40h, 03h, 0DAh, 0C1h, 0FBh, 04h, 88h, 18h, 8Bh, 0DAh
    db 2Bh, 0DEh, 03h, 0CBh, 8Bh, 5Ch, 24h, 34h, 03h, 0D9h, 0D1h, 0E3h, 2Bh, 0DAh, 2Bh, 0DFh
    db 03h, 0DEh, 8Bh, 74h, 24h, 44h, 03h, 0DEh, 0C1h, 0FBh, 04h, 8Bh, 0D6h, 2Bh, 0D7h, 03h
    db 0CAh, 88h, 58h, 01h, 8Dh, 14h, 29h, 0D1h, 0E2h, 8Bh, 0DAh, 8Bh, 54h, 24h, 2Ch, 2Bh
    db 0DEh, 8Bh, 74h, 24h, 10h, 2Bh, 0DAh, 03h, 0DEh, 03h, 0DFh, 8Bh, 7Ch, 24h, 1Ch, 0C1h
    db 0FBh, 04h, 88h, 1Fh, 8Bh, 0FEh, 2Bh, 0FAh, 03h, 0CFh, 8Bh, 7Ch, 24h, 3Ch, 03h, 0F9h
    db 0D1h, 0E7h, 8Bh, 0DFh, 8Bh, 7Ch, 24h, 30h, 2Bh, 0DFh, 03h, 0DAh, 8Bh, 0D6h, 2Bh, 0D7h
    db 0C1h, 0FBh, 04h, 03h, 0CAh, 8Bh, 54h, 24h, 40h, 88h, 58h, 03h, 03h, 0D1h, 03h, 0CEh
    db 8Bh, 74h, 24h, 44h, 0D1h, 0E2h, 03h, 0CEh, 8Bh, 0DAh, 8Bh, 54h, 24h, 34h, 2Bh, 0DAh
    db 0D1h, 0E1h, 03h, 0DFh, 8Bh, 7Ch, 24h, 14h, 2Bh, 0CDh, 0C1h, 0FBh, 04h, 2Bh, 0CAh, 0C1h
    db 0F9h, 04h, 88h, 58h, 04h, 8Bh, 9Ch, 24h, 98h, 00h, 00h, 00h, 88h, 48h, 05h, 8Bh
    db 8Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 54h, 24h, 1Ch, 03h, 0D1h, 03h, 0C1h, 8Bh, 4Ch
    db 24h, 54h, 49h, 89h, 54h, 24h, 1Ch, 89h, 4Ch, 24h, 54h, 0Fh, 85h, 0A0h, 0FDh, 0FFh
    db 0FFh, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 70h, 47h, 83h, 0C0h, 08h, 3Bh, 0F9h, 89h
    db 7Ch, 24h, 14h, 89h, 44h, 24h, 18h, 0Fh, 82h, 53h, 0FDh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh
    db 5Bh, 81h, 0C4h, 84h, 00h, 00h, 00h, 0C3h
?d_009acf90@@YAXXZ ENDP

; retail @ 0x009ADD80 size 2324
_TEXT ENDS
_TEXT$d00dadd80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DADD80 size 2324
public ?d_009add80@@YAXXZ
?d_009add80@@YAXXZ PROC
    db 081h, 0ECh, 0A4h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 08Bh, 084h, 024h
    db 0B4h, 000h, 000h, 000h, 053h, 055h, 08Bh, 0ACh, 024h, 0C0h, 000h, 000h, 000h, 056h, 003h, 0E9h
    db 03Bh, 0CDh, 057h, 089h, 04Ch, 024h, 07Ch, 08Dh, 014h, 000h, 08Dh, 034h, 040h, 08Dh, 03Ch, 085h
    db 000h, 000h, 000h, 000h, 08Dh, 01Ch, 080h, 089h, 0ACh, 024h, 0A0h, 000h, 000h, 000h, 00Fh, 083h
    db 0C5h, 008h, 000h, 000h, 08Bh, 0ACh, 024h, 0C0h, 000h, 000h, 000h, 08Bh, 0CFh, 02Bh, 0C8h, 089h
    db 08Ch, 024h, 0A4h, 000h, 000h, 000h, 08Bh, 0CFh, 02Bh, 0CAh, 089h, 08Ch, 024h, 0A8h, 000h, 000h
    db 000h, 08Bh, 0C8h, 02Bh, 0CAh, 089h, 08Ch, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 0CEh, 02Bh, 0CAh
    db 089h, 08Ch, 024h, 094h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 02Bh, 0CDh
    db 08Bh, 0EBh, 02Bh, 0E8h, 089h, 0ACh, 024h, 0B0h, 000h, 000h, 000h, 08Bh, 0EBh, 02Bh, 0EEh, 089h
    db 0ACh, 024h, 09Ch, 000h, 000h, 000h, 08Bh, 0EBh, 02Bh, 0EAh, 089h, 0ACh, 024h, 098h, 000h, 000h
    db 000h, 08Bh, 0E8h, 02Bh, 0EFh, 089h, 0ACh, 024h, 090h, 000h, 000h, 000h, 08Bh, 0EFh, 02Bh, 0EEh
    db 089h, 0ACh, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0ACh, 024h, 0CCh, 000h, 000h, 000h, 0C1h, 0E5h
    db 002h, 089h, 06Ch, 024h, 01Ch, 08Bh, 0ACh, 024h, 0A0h, 000h, 000h, 000h, 0C1h, 0E5h, 002h, 089h
    db 06Ch, 024h, 020h, 08Bh, 0ACh, 024h, 0BCh, 000h, 000h, 000h, 089h, 06Ch, 024h, 054h, 08Bh, 0ACh
    db 024h, 0C0h, 000h, 000h, 000h, 0C1h, 0E0h, 003h, 02Bh, 0E8h, 08Bh, 084h, 024h, 0BCh, 000h, 000h
    db 000h, 02Bh, 0C3h, 08Bh, 09Ch, 024h, 0BCh, 000h, 000h, 000h, 003h, 0F3h, 08Bh, 09Ch, 024h, 0C0h
    db 000h, 000h, 000h, 089h, 06Ch, 024h, 058h, 083h, 0C5h, 0FEh, 089h, 074h, 024h, 050h, 08Bh, 0F3h
    db 089h, 06Ch, 024h, 060h, 02Bh, 0F7h, 08Dh, 02Ch, 01Ah, 089h, 04Ch, 024h, 064h, 089h, 084h, 024h
    db 080h, 000h, 000h, 000h, 089h, 0B4h, 024h, 084h, 000h, 000h, 000h, 089h, 06Ch, 024h, 06Ch, 0BFh
    db 008h, 000h, 000h, 000h, 08Bh, 054h, 024h, 054h, 08Bh, 05Ch, 024h, 020h, 089h, 054h, 024h, 078h
    db 08Bh, 094h, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 052h, 024h, 08Bh, 014h, 013h, 08Bh, 09Ch, 024h
    db 0D0h, 000h, 000h, 000h, 08Bh, 014h, 093h, 089h, 054h, 024h, 068h, 00Fh, 0AFh, 0D2h, 08Dh, 014h
    db 052h, 0C1h, 0FAh, 005h, 089h, 094h, 024h, 088h, 000h, 000h, 000h, 08Bh, 054h, 024h, 050h, 089h
    db 054h, 024h, 024h, 089h, 044h, 024h, 014h, 089h, 06Ch, 024h, 074h, 089h, 07Ch, 024h, 05Ch, 090h
    db 00Fh, 0B6h, 01Ch, 031h, 08Bh, 08Ch, 024h, 09Ch, 000h, 000h, 000h, 00Fh, 0B6h, 014h, 001h, 08Bh
    db 08Ch, 024h, 098h, 000h, 000h, 000h, 089h, 054h, 024h, 030h, 00Fh, 0B6h, 014h, 008h, 08Bh, 08Ch
    db 024h, 0B0h, 000h, 000h, 000h, 00Fh, 0B6h, 03Ch, 001h, 08Bh, 084h, 024h, 08Ch, 000h, 000h, 000h
    db 089h, 054h, 024h, 034h, 08Bh, 054h, 024h, 078h, 00Fh, 0B6h, 00Ah, 08Bh, 054h, 024h, 024h, 003h
    db 0C2h, 08Bh, 094h, 024h, 090h, 000h, 000h, 000h, 089h, 044h, 024h, 070h, 00Fh, 0B6h, 004h, 010h
    db 08Bh, 054h, 024h, 064h, 089h, 044h, 024h, 040h, 00Fh, 0B6h, 004h, 02Ah, 08Bh, 054h, 024h, 024h
    db 08Bh, 06Ch, 024h, 030h, 089h, 044h, 024h, 044h, 00Fh, 0B6h, 002h, 08Bh, 054h, 024h, 034h, 089h
    db 044h, 024h, 048h, 08Dh, 004h, 017h, 003h, 0C5h, 003h, 0C3h, 08Bh, 0EAh, 00Fh, 0AFh, 0EAh, 08Bh
    db 054h, 024h, 030h, 089h, 044h, 024h, 018h, 08Bh, 0C7h, 00Fh, 0AFh, 0C7h, 003h, 0C5h, 08Bh, 0EAh
    db 00Fh, 0AFh, 0EAh, 08Bh, 0D3h, 00Fh, 0AFh, 0D3h, 003h, 0C5h, 08Bh, 06Ch, 024h, 044h, 089h, 05Ch
    db 024h, 02Ch, 003h, 0C2h, 08Bh, 054h, 024h, 048h, 08Dh, 01Ch, 02Ah, 00Fh, 0AFh, 0D2h, 003h, 05Ch
    db 024h, 040h, 003h, 0D9h, 089h, 05Ch, 024h, 010h, 08Bh, 0DDh, 00Fh, 0AFh, 0DDh, 003h, 0D3h, 08Bh
    db 05Ch, 024h, 040h, 08Bh, 0EBh, 00Fh, 0AFh, 0EBh, 08Bh, 0D9h, 00Fh, 0AFh, 0D9h, 003h, 0D5h, 003h
    db 0D3h, 08Bh, 05Ch, 024h, 018h, 08Dh, 06Bh, 001h, 0D1h, 0FBh, 0D1h, 0FDh, 00Fh, 0AFh, 0EBh, 08Bh
    db 05Ch, 024h, 010h, 02Bh, 0C5h, 08Dh, 06Bh, 001h, 0D1h, 0FBh, 0D1h, 0FDh, 00Fh, 0AFh, 0EBh, 08Bh
    db 09Ch, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 05Bh, 028h, 02Bh, 0D5h, 08Bh, 06Ch, 024h, 01Ch, 003h
    db 0DDh, 001h, 003h, 08Bh, 09Ch, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 05Bh, 028h, 08Bh, 06Ch, 024h
    db 020h, 003h, 0DDh, 001h, 013h, 08Bh, 09Ch, 024h, 088h, 000h, 000h, 000h, 03Bh, 0C3h, 00Fh, 08Dh
    db 0BEh, 001h, 000h, 000h, 03Bh, 0D3h, 00Fh, 08Dh, 0B6h, 001h, 000h, 000h, 08Bh, 06Ch, 024h, 068h
    db 08Bh, 0C1h, 02Bh, 0C7h, 03Bh, 0C5h, 00Fh, 08Dh, 0A6h, 001h, 000h, 000h, 08Bh, 0D7h, 02Bh, 0D1h
    db 03Bh, 0D5h, 00Fh, 08Dh, 09Ah, 001h, 000h, 000h, 08Bh, 044h, 024h, 014h, 00Fh, 0B6h, 010h, 08Bh
    db 044h, 024h, 064h, 00Fh, 0B6h, 01Ch, 030h, 08Bh, 0C3h, 02Bh, 0C2h, 085h, 0C0h, 07Fh, 004h, 08Bh
    db 0C2h, 02Bh, 0C3h, 03Bh, 0C5h, 07Ch, 002h, 08Bh, 0D3h, 08Bh, 044h, 024h, 070h, 00Fh, 0B6h, 018h
    db 08Bh, 044h, 024h, 024h, 00Fh, 0B6h, 028h, 08Bh, 0C5h, 02Bh, 0C3h, 085h, 0C0h, 089h, 054h, 024h
    db 018h, 089h, 06Ch, 024h, 070h, 07Fh, 004h, 08Bh, 0C3h, 02Bh, 0C5h, 03Bh, 044h, 024h, 068h, 07Dh
    db 006h, 089h, 05Ch, 024h, 010h, 0EBh, 008h, 08Bh, 044h, 024h, 070h, 089h, 044h, 024h, 010h, 08Dh
    db 004h, 057h, 003h, 0C2h, 08Bh, 06Ch, 024h, 034h, 08Bh, 05Ch, 024h, 030h, 003h, 0C5h, 08Bh, 06Ch
    db 024h, 02Ch, 003h, 0C3h, 08Dh, 044h, 028h, 004h, 08Dh, 01Ch, 028h, 0D1h, 0E3h, 02Bh, 0DFh, 003h
    db 0D9h, 0C1h, 0FBh, 004h, 088h, 01Eh, 08Bh, 0D9h, 02Bh, 0DAh, 08Bh, 054h, 024h, 030h, 003h, 0C3h
    db 003h, 0D0h, 08Bh, 05Ch, 024h, 040h, 0D1h, 0E2h, 02Bh, 0D1h, 003h, 0D3h, 08Bh, 09Ch, 024h, 08Ch
    db 000h, 000h, 000h, 0C1h, 0FAh, 004h, 088h, 014h, 033h, 08Bh, 05Ch, 024h, 018h, 08Bh, 054h, 024h
    db 040h, 02Bh, 0D3h, 08Bh, 05Ch, 024h, 040h, 003h, 0C2h, 08Bh, 054h, 024h, 034h, 003h, 0D0h, 0D1h
    db 0E2h, 02Bh, 0D3h, 003h, 054h, 024h, 044h, 08Bh, 09Ch, 024h, 0A8h, 000h, 000h, 000h, 0C1h, 0FAh
    db 004h, 088h, 014h, 033h, 08Bh, 05Ch, 024h, 018h, 08Bh, 054h, 024h, 044h, 02Bh, 0D3h, 08Bh, 05Ch
    db 024h, 044h, 003h, 0C2h, 08Dh, 014h, 038h, 0D1h, 0E2h, 02Bh, 0D3h, 08Bh, 05Ch, 024h, 018h, 02Bh
    db 0D5h, 003h, 0D3h, 003h, 054h, 024h, 048h, 08Bh, 09Ch, 024h, 0A4h, 000h, 000h, 000h, 0C1h, 0FAh
    db 004h, 088h, 014h, 033h, 08Bh, 054h, 024h, 048h, 08Bh, 0DAh, 02Bh, 0DDh, 003h, 0C3h, 08Dh, 01Ch
    db 008h, 0D1h, 0E3h, 02Bh, 0DAh, 02Bh, 05Ch, 024h, 030h, 08Bh, 054h, 024h, 010h, 003h, 0DAh, 003h
    db 0DDh, 08Bh, 0ACh, 024h, 0C4h, 000h, 000h, 000h, 0C1h, 0FBh, 004h, 0C1h, 0E5h, 002h, 088h, 01Ch
    db 02Eh, 08Bh, 06Ch, 024h, 030h, 08Bh, 05Ch, 024h, 034h, 02Bh, 0D5h, 003h, 0C2h, 08Bh, 054h, 024h
    db 040h, 003h, 0D0h, 0D1h, 0E2h, 02Bh, 0D3h, 003h, 0D5h, 08Bh, 06Ch, 024h, 074h, 08Bh, 09Ch, 024h
    db 0ACh, 000h, 000h, 000h, 0C1h, 0FAh, 004h, 088h, 014h, 02Bh, 08Bh, 054h, 024h, 034h, 08Bh, 05Ch
    db 024h, 010h, 02Bh, 0DAh, 003h, 0C3h, 08Bh, 05Ch, 024h, 044h, 003h, 0D8h, 0D1h, 0E3h, 02Bh, 0DFh
    db 003h, 0DAh, 08Bh, 054h, 024h, 010h, 0C1h, 0FBh, 004h, 003h, 0C2h, 088h, 05Dh, 000h, 003h, 044h
    db 024h, 048h, 0D1h, 0E0h, 02Bh, 0C1h, 08Bh, 08Ch, 024h, 094h, 000h, 000h, 000h, 02Bh, 0C7h, 0C1h
    db 0F8h, 004h, 088h, 004h, 029h, 08Bh, 044h, 024h, 014h, 08Bh, 04Ch, 024h, 064h, 0E9h, 0B2h, 000h
    db 000h, 000h, 08Bh, 06Ch, 024h, 040h, 08Bh, 0C1h, 02Bh, 0C7h, 08Dh, 014h, 040h, 08Bh, 044h, 024h
    db 034h, 02Bh, 0D5h, 08Dh, 054h, 002h, 004h, 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 040h
    db 038h, 0C1h, 0FAh, 003h, 08Bh, 004h, 090h, 08Ah, 094h, 038h
    dd g_Va01356FE0
    db 08Bh, 0BCh, 024h, 0A4h, 000h, 000h, 000h, 088h, 014h, 037h, 08Bh, 0BCh, 024h, 08Ch, 000h, 000h
    db 000h, 08Bh, 06Ch, 024h, 074h, 02Bh, 0C8h, 08Ah, 089h
    dd g_Va01356FE0
    db 08Bh, 084h, 024h, 0C4h, 000h, 000h, 000h, 0C1h, 0E0h, 002h, 088h, 00Ch, 006h, 08Bh, 04Ch, 024h
    db 064h, 08Ah, 014h, 031h, 08Bh, 044h, 024h, 014h, 088h, 016h, 08Bh, 094h, 024h, 09Ch, 000h, 000h
    db 000h, 08Ah, 014h, 002h, 088h, 014h, 037h, 08Bh, 094h, 024h, 098h, 000h, 000h, 000h, 08Ah, 014h
    db 010h, 08Bh, 0BCh, 024h, 0A8h, 000h, 000h, 000h, 088h, 014h, 037h, 08Bh, 054h, 024h, 070h, 08Bh
    db 0BCh, 024h, 090h, 000h, 000h, 000h, 08Ah, 014h, 03Ah, 08Bh, 0BCh, 024h, 0ACh, 000h, 000h, 000h
    db 088h, 014h, 02Fh, 08Ah, 014h, 029h, 08Bh, 0BCh, 024h, 094h, 000h, 000h, 000h, 088h, 055h, 000h
    db 08Bh, 054h, 024h, 024h, 08Ah, 012h, 088h, 014h, 02Fh, 08Bh, 05Ch, 024h, 078h, 08Bh, 054h, 024h
    db 024h, 043h, 040h, 042h, 089h, 054h, 024h, 024h, 08Bh, 054h, 024h, 05Ch, 046h, 045h, 04Ah, 089h
    db 05Ch, 024h, 078h, 089h, 044h, 024h, 014h, 089h, 06Ch, 024h, 074h, 089h, 054h, 024h, 05Ch, 00Fh
    db 085h, 040h, 0FCh, 0FFh, 0FFh, 08Bh, 054h, 024h, 07Ch, 03Bh, 094h, 024h, 0CCh, 000h, 000h, 000h
    db 075h, 068h, 08Bh, 06Ch, 024h, 054h, 08Bh, 05Ch, 024h, 050h, 08Bh, 084h, 024h, 080h, 000h, 000h
    db 000h, 08Bh, 0B4h, 024h, 084h, 000h, 000h, 000h, 0BFh, 008h, 000h, 000h, 000h, 003h, 0EFh, 089h
    db 06Ch, 024h, 054h, 08Bh, 06Ch, 024h, 06Ch, 003h, 0EFh, 003h, 0DFh, 089h, 06Ch, 024h, 06Ch, 08Bh
    db 06Ch, 024h, 058h, 089h, 05Ch, 024h, 050h, 08Bh, 05Ch, 024h, 060h, 003h, 0EFh, 003h, 0DFh, 089h
    db 06Ch, 024h, 058h, 08Bh, 06Ch, 024h, 01Ch, 089h, 05Ch, 024h, 060h, 0BBh, 004h, 000h, 000h, 000h
    db 003h, 0EBh, 089h, 06Ch, 024h, 01Ch, 08Bh, 06Ch, 024h, 020h, 042h, 003h, 0C7h, 003h, 0F7h, 003h
    db 0EBh, 089h, 06Ch, 024h, 020h, 0E9h, 006h, 003h, 000h, 000h, 08Bh, 044h, 024h, 058h, 08Bh, 08Ch
    db 024h, 0B8h, 000h, 000h, 000h, 08Bh, 051h, 024h, 089h, 044h, 024h, 014h, 08Bh, 044h, 024h, 01Ch
    db 08Bh, 00Ch, 010h, 08Bh, 094h, 024h, 0D0h, 000h, 000h, 000h, 08Bh, 004h, 08Ah, 089h, 044h, 024h
    db 068h, 00Fh, 0AFh, 0C0h, 08Dh, 004h, 040h, 0C1h, 0F8h, 005h, 089h, 084h, 024h, 088h, 000h, 000h
    db 000h, 08Bh, 044h, 024h, 060h, 0C7h, 044h, 024h, 05Ch, 008h, 000h, 000h, 000h, 0EBh, 006h, 08Dh
    db 09Bh, 000h, 000h, 000h, 000h, 00Fh, 0B6h, 048h, 003h, 00Fh, 0B6h, 010h, 00Fh, 0B6h, 078h, 001h
    db 00Fh, 0B6h, 058h, 0FEh, 00Fh, 0B6h, 068h, 0FFh, 089h, 04Ch, 024h, 040h, 00Fh, 0B6h, 048h, 004h
    db 089h, 04Ch, 024h, 044h, 00Fh, 0B6h, 048h, 005h, 089h, 06Ch, 024h, 030h, 089h, 04Ch, 024h, 048h
    db 08Dh, 00Ch, 017h, 003h, 0CDh, 003h, 0CBh, 08Bh, 0EAh, 00Fh, 0AFh, 0EAh, 089h, 04Ch, 024h, 018h
    db 00Fh, 0B6h, 070h, 002h, 08Bh, 0CFh, 00Fh, 0AFh, 0CFh, 003h, 0CDh, 089h, 054h, 024h, 034h, 08Bh
    db 054h, 024h, 030h, 08Bh, 0EAh, 00Fh, 0AFh, 0EAh, 08Bh, 0D3h, 00Fh, 0AFh, 0D3h, 089h, 05Ch, 024h
    db 02Ch, 003h, 0CDh, 08Bh, 06Ch, 024h, 044h, 003h, 0CAh, 08Bh, 054h, 024h, 048h, 08Dh, 01Ch, 02Ah
    db 00Fh, 0AFh, 0D2h, 003h, 05Ch, 024h, 040h, 003h, 0DEh, 089h, 05Ch, 024h, 010h, 08Bh, 0DDh, 00Fh
    db 0AFh, 0DDh, 003h, 0D3h, 08Bh, 05Ch, 024h, 040h, 08Bh, 0EBh, 00Fh, 0AFh, 0EBh, 003h, 0D5h, 08Bh
    db 0DEh, 00Fh, 0AFh, 0DEh, 003h, 0D3h, 08Bh, 05Ch, 024h, 018h, 08Dh, 06Bh, 001h, 0D1h, 0FBh, 0D1h
    db 0FDh, 00Fh, 0AFh, 0EBh, 08Bh, 05Ch, 024h, 010h, 02Bh, 0CDh, 08Dh, 06Bh, 001h, 0D1h, 0FBh, 0D1h
    db 0FDh, 00Fh, 0AFh, 0EBh, 08Bh, 09Ch, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 05Bh, 028h, 02Bh, 0D5h
    db 08Bh, 06Ch, 024h, 01Ch, 001h, 04Ch, 02Bh, 0FCh, 08Dh, 05Ch, 02Bh, 0FCh, 08Bh, 09Ch, 024h, 0B8h
    db 000h, 000h, 000h, 08Bh, 05Bh, 028h, 003h, 0DDh, 001h, 013h, 08Bh, 09Ch, 024h, 088h, 000h, 000h
    db 000h, 03Bh, 0CBh, 00Fh, 08Dh, 058h, 001h, 000h, 000h, 03Bh, 0D3h, 00Fh, 08Dh, 050h, 001h, 000h
    db 000h, 08Bh, 05Ch, 024h, 068h, 08Bh, 0CEh, 02Bh, 0CFh, 03Bh, 0CBh, 00Fh, 08Dh, 040h, 001h, 000h
    db 000h, 08Bh, 0D7h, 02Bh, 0D6h, 03Bh, 0D3h, 00Fh, 08Dh, 034h, 001h, 000h, 000h, 00Fh, 0B6h, 068h
    db 0FEh, 00Fh, 0B6h, 050h, 0FDh, 08Bh, 0CDh, 02Bh, 0CAh, 085h, 0C9h, 07Fh, 004h, 08Bh, 0CAh, 02Bh
    db 0CDh, 03Bh, 0CBh, 07Dh, 002h, 08Bh, 0EAh, 00Fh, 0B6h, 058h, 005h, 00Fh, 0B6h, 050h, 006h, 08Bh
    db 0CBh, 02Bh, 0CAh, 085h, 0C9h, 07Fh, 004h, 08Bh, 0CAh, 02Bh, 0CBh, 03Bh, 04Ch, 024h, 068h, 07Dh
    db 006h, 089h, 054h, 024h, 010h, 0EBh, 008h, 00Fh, 0B6h, 048h, 005h, 089h, 04Ch, 024h, 010h, 08Bh
    db 05Ch, 024h, 034h, 08Bh, 054h, 024h, 02Ch, 08Dh, 00Ch, 06Fh, 003h, 0CDh, 003h, 0CBh, 08Bh, 05Ch
    db 024h, 030h, 003h, 0CBh, 08Dh, 04Ch, 011h, 004h, 003h, 0D1h, 0D1h, 0E2h, 02Bh, 0D7h, 003h, 0D6h
    db 0C1h, 0FAh, 004h, 088h, 050h, 0FEh, 08Bh, 0D6h, 02Bh, 0D5h, 003h, 0CAh, 08Dh, 014h, 019h, 0D1h
    db 0E2h, 08Bh, 0DAh, 08Bh, 054h, 024h, 040h, 02Bh, 0DEh, 003h, 0DAh, 0C1h, 0FBh, 004h, 088h, 058h
    db 0FFh, 08Bh, 0DAh, 02Bh, 0DDh, 003h, 0CBh, 08Bh, 05Ch, 024h, 034h, 003h, 0D9h, 0D1h, 0E3h, 02Bh
    db 0DAh, 08Bh, 054h, 024h, 044h, 003h, 0DAh, 0C1h, 0FBh, 004h, 088h, 018h, 08Bh, 0DAh, 02Bh, 0DDh
    db 003h, 0CBh, 08Dh, 01Ch, 039h, 0D1h, 0E3h, 02Bh, 0DAh, 08Bh, 054h, 024h, 02Ch, 02Bh, 0DAh, 003h
    db 0DDh, 08Bh, 06Ch, 024h, 048h, 003h, 0DDh, 0C1h, 0FBh, 004h, 088h, 058h, 001h, 08Bh, 0DDh, 02Bh
    db 0DAh, 003h, 0CBh, 08Dh, 01Ch, 031h, 0D1h, 0E3h, 02Bh, 0DDh, 02Bh, 05Ch, 024h, 030h, 08Bh, 06Ch
    db 024h, 010h, 003h, 0DDh, 003h, 0DAh, 08Bh, 054h, 024h, 014h, 0C1h, 0FBh, 004h, 088h, 01Ah, 08Bh
    db 05Ch, 024h, 030h, 08Bh, 0D5h, 02Bh, 0D3h, 08Bh, 05Ch, 024h, 034h, 003h, 0CAh, 08Bh, 054h, 024h
    db 040h, 003h, 0D1h, 0D1h, 0E2h, 02Bh, 0D3h, 003h, 054h, 024h, 030h, 0C1h, 0FAh, 004h, 088h, 050h
    db 003h, 08Bh, 054h, 024h, 034h, 08Bh, 0DDh, 02Bh, 0DAh, 003h, 0CBh, 08Bh, 05Ch, 024h, 044h, 003h
    db 0D9h, 0D1h, 0E3h, 02Bh, 0DFh, 003h, 0CDh, 003h, 0DAh, 003h, 04Ch, 024h, 048h, 0D1h, 0E1h, 02Bh
    db 0CEh, 0C1h, 0FBh, 004h, 02Bh, 0CFh, 0C1h, 0F9h, 004h, 088h, 058h, 004h, 088h, 048h, 005h, 0EBh
    db 03Dh, 08Bh, 06Ch, 024h, 040h, 08Bh, 054h, 024h, 034h, 08Bh, 0CEh, 02Bh, 0CFh, 08Dh, 00Ch, 049h
    db 02Bh, 0CDh, 08Dh, 04Ch, 011h, 004h, 08Bh, 094h, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 052h, 038h
    db 0C1h, 0F9h, 003h, 08Bh, 00Ch, 08Ah, 08Ah, 094h, 039h
    dd g_Va01356FE0
    db 088h, 050h, 001h, 08Bh, 054h, 024h, 014h, 02Bh, 0F1h, 08Ah, 08Eh
    dd g_Va01356FE0
    db 088h, 00Ah, 08Bh, 08Ch, 024h, 0C4h, 000h, 000h, 000h, 08Bh, 054h, 024h, 014h, 003h, 0D1h, 003h
    db 0C1h, 08Bh, 04Ch, 024h, 05Ch, 049h, 089h, 054h, 024h, 014h, 089h, 04Ch, 024h, 05Ch, 00Fh, 085h
    db 065h, 0FDh, 0FFh, 0FFh, 08Bh, 084h, 024h, 080h, 000h, 000h, 000h, 08Bh, 0B4h, 024h, 084h, 000h
    db 000h, 000h, 08Bh, 04Ch, 024h, 064h, 08Bh, 054h, 024h, 07Ch, 0BBh, 004h, 000h, 000h, 000h, 0BFh
    db 008h, 000h, 000h, 000h, 08Bh, 06Ch, 024h, 054h, 001h, 05Ch, 024h, 01Ch, 001h, 05Ch, 024h, 020h
    db 08Bh, 09Ch, 024h, 0A0h, 000h, 000h, 000h, 001h, 07Ch, 024h, 058h, 001h, 07Ch, 024h, 060h, 003h
    db 0EFh, 089h, 06Ch, 024h, 054h, 001h, 07Ch, 024h, 050h, 08Bh, 06Ch, 024h, 06Ch, 042h, 003h, 0C7h
    db 003h, 0EFh, 003h, 0F7h, 03Bh, 0D3h, 089h, 054h, 024h, 07Ch, 089h, 084h, 024h, 080h, 000h, 000h
    db 000h, 089h, 06Ch, 024h, 06Ch, 089h, 0B4h, 024h, 084h, 000h, 000h, 000h, 00Fh, 082h, 02Bh, 0F8h
    db 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0A4h, 000h, 000h, 000h, 0C3h
?d_009add80@@YAXXZ ENDP
_TEXT$d00dadd80 ENDS
_TEXT SEGMENT

; retail @ 0x009AE6A0 size 2107
_TEXT ENDS
_TEXT$d00dae6a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAE6A0 size 2107
public ?d_009ae6a0@@YAXXZ
?d_009ae6a0@@YAXXZ PROC
    db 081h, 0ECh, 098h, 000h, 000h, 000h, 08Bh, 084h, 024h, 0A8h, 000h, 000h, 000h, 053h, 08Bh, 09Ch
    db 024h, 0A0h, 000h, 000h, 000h, 08Bh, 05Bh, 00Ch, 055h, 08Bh, 0ACh, 024h, 0BCh, 000h, 000h, 000h
    db 08Bh, 05Ch, 09Dh, 000h, 056h, 089h, 09Ch, 024h, 084h, 000h, 000h, 000h, 08Bh, 09Ch, 024h, 0B8h
    db 000h, 000h, 000h, 057h, 08Bh, 0BCh, 024h, 0C0h, 000h, 000h, 000h, 003h, 0DFh, 03Bh, 0FBh, 089h
    db 07Ch, 024h, 050h, 08Dh, 00Ch, 000h, 08Dh, 014h, 040h, 08Dh, 034h, 085h, 000h, 000h, 000h, 000h
    db 089h, 09Ch, 024h, 094h, 000h, 000h, 000h, 00Fh, 083h, 0D3h, 007h, 000h, 000h, 08Bh, 0ACh, 024h
    db 0B4h, 000h, 000h, 000h, 08Bh, 0FEh, 02Bh, 0FAh, 089h, 0BCh, 024h, 09Ch, 000h, 000h, 000h, 08Bh
    db 0FEh, 02Bh, 0F9h, 089h, 0BCh, 024h, 098h, 000h, 000h, 000h, 08Bh, 0F8h, 02Bh, 0F9h, 089h, 0BCh
    db 024h, 090h, 000h, 000h, 000h, 08Bh, 0BCh, 024h, 0B0h, 000h, 000h, 000h, 08Bh, 0DFh, 02Bh, 0DDh
    db 089h, 05Ch, 024h, 074h, 08Dh, 02Ch, 080h, 08Bh, 0D8h, 02Bh, 0DDh, 089h, 09Ch, 024h, 0A4h, 000h
    db 000h, 000h, 08Bh, 0DEh, 02Bh, 0D8h, 089h, 05Ch, 024h, 078h, 08Bh, 0DAh, 02Bh, 0D9h, 089h, 05Ch
    db 024h, 07Ch, 08Bh, 0DAh, 02Bh, 0D8h, 089h, 09Ch, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 09Ch, 024h
    db 088h, 000h, 000h, 000h, 08Dh, 01Ch, 05Bh, 0C1h, 0FBh, 002h, 089h, 09Ch, 024h, 0A0h, 000h, 000h
    db 000h, 08Bh, 09Ch, 024h, 0C0h, 000h, 000h, 000h, 0C1h, 0E3h, 002h, 089h, 05Ch, 024h, 024h, 08Bh
    db 09Ch, 024h, 094h, 000h, 000h, 000h, 0C1h, 0E3h, 002h, 089h, 05Ch, 024h, 064h, 08Bh, 09Ch, 024h
    db 0B4h, 000h, 000h, 000h, 08Dh, 02Ch, 0C5h, 000h, 000h, 000h, 000h, 02Bh, 0DDh, 08Bh, 0EFh, 02Bh
    db 0EAh, 089h, 07Ch, 024h, 05Ch, 003h, 0F8h, 08Bh, 084h, 024h, 0B4h, 000h, 000h, 000h, 08Bh, 0D0h
    db 02Bh, 0D6h, 089h, 05Ch, 024h, 058h, 083h, 0C3h, 0FCh, 003h, 0C8h, 089h, 054h, 024h, 054h, 089h
    db 06Ch, 024h, 068h, 089h, 07Ch, 024h, 060h, 089h, 05Ch, 024h, 06Ch, 089h, 04Ch, 024h, 070h, 0BAh
    db 008h, 000h, 000h, 000h, 0EBh, 00Ah, 08Bh, 06Ch, 024h, 068h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 08Bh, 044h, 024h, 05Ch, 08Bh, 05Ch, 024h, 060h, 08Bh, 074h, 024h, 070h, 08Bh, 04Ch, 024h, 054h
    db 089h, 044h, 024h, 020h, 08Bh, 0C5h, 089h, 09Ch, 024h, 084h, 000h, 000h, 000h, 089h, 084h, 024h
    db 080h, 000h, 000h, 000h, 089h, 054h, 024h, 01Ch, 0EBh, 006h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 08Bh, 094h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0BCh, 024h, 0A4h, 000h, 000h, 000h, 003h, 0D0h
    db 00Fh, 0B6h, 02Ch, 03Ah, 00Fh, 0B6h, 038h, 089h, 07Ch, 024h, 030h, 08Bh, 07Ch, 024h, 07Ch, 00Fh
    db 0B6h, 004h, 038h, 089h, 044h, 024h, 034h, 089h, 054h, 024h, 018h, 08Bh, 0C2h, 00Fh, 0B6h, 000h
    db 089h, 044h, 024h, 038h, 08Bh, 044h, 024h, 020h, 00Fh, 0B6h, 038h, 00Fh, 0B6h, 003h, 08Bh, 054h
    db 024h, 074h, 00Fh, 0B6h, 014h, 00Ah, 089h, 044h, 024h, 040h, 08Bh, 044h, 024h, 074h, 00Fh, 0B6h
    db 004h, 030h, 089h, 044h, 024h, 044h, 08Bh, 084h, 024h, 08Ch, 000h, 000h, 000h, 00Fh, 0B6h, 004h
    db 003h, 089h, 044h, 024h, 048h, 08Bh, 044h, 024h, 078h, 00Fh, 0B6h, 004h, 003h, 089h, 044h, 024h
    db 04Ch, 08Bh, 0C2h, 02Bh, 0C5h, 085h, 0C0h, 089h, 054h, 024h, 02Ch, 07Fh, 004h, 08Bh, 0C5h, 02Bh
    db 0C2h, 08Bh, 05Ch, 024h, 030h, 089h, 044h, 024h, 014h, 08Bh, 0C3h, 02Bh, 0C2h, 085h, 0C0h, 07Fh
    db 004h, 08Bh, 0C2h, 02Bh, 0C3h, 08Bh, 05Ch, 024h, 014h, 003h, 0D8h, 08Bh, 044h, 024h, 034h, 089h
    db 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 030h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 006h, 08Bh, 0C3h, 02Bh
    db 044h, 024h, 034h, 08Bh, 05Ch, 024h, 014h, 003h, 0D8h, 08Bh, 044h, 024h, 038h, 089h, 05Ch, 024h
    db 014h, 08Bh, 05Ch, 024h, 034h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 006h, 08Bh, 0C3h, 02Bh, 044h, 024h
    db 038h, 08Bh, 05Ch, 024h, 014h, 003h, 0D8h, 08Bh, 044h, 024h, 040h, 089h, 05Ch, 024h, 014h, 08Bh
    db 0DFh, 02Bh, 0D8h, 085h, 0DBh, 07Fh, 004h, 08Bh, 0D8h, 02Bh, 0DFh, 089h, 05Ch, 024h, 010h, 08Bh
    db 05Ch, 024h, 044h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 006h, 08Bh, 0C3h, 02Bh, 044h, 024h, 040h, 08Bh
    db 05Ch, 024h, 010h, 003h, 0D8h, 08Bh, 044h, 024h, 044h, 089h, 05Ch, 024h, 010h, 08Bh, 05Ch, 024h
    db 048h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 006h, 08Bh, 0C3h, 02Bh, 044h, 024h, 044h, 08Bh, 05Ch, 024h
    db 010h, 003h, 0D8h, 08Bh, 044h, 024h, 048h, 089h, 05Ch, 024h, 010h, 08Bh, 05Ch, 024h, 04Ch, 02Bh
    db 0C3h, 085h, 0C0h, 07Fh, 006h, 08Bh, 0C3h, 02Bh, 044h, 024h, 048h, 08Bh, 05Ch, 024h, 010h, 003h
    db 0D8h, 08Bh, 044h, 024h, 014h, 03Dh, 0FFh, 000h, 000h, 000h, 089h, 05Ch, 024h, 010h, 0C7h, 044h
    db 024h, 018h, 0FFh, 000h, 000h, 000h, 07Fh, 004h, 089h, 044h, 024h, 018h, 08Bh, 084h, 024h, 0ACh
    db 000h, 000h, 000h, 08Bh, 040h, 028h, 08Bh, 05Ch, 024h, 024h, 003h, 0C3h, 08Bh, 05Ch, 024h, 018h
    db 001h, 018h, 08Bh, 044h, 024h, 010h, 03Dh, 0FFh, 000h, 000h, 000h, 0C7h, 044h, 024h, 018h, 0FFh
    db 000h, 000h, 000h, 07Fh, 004h, 089h, 044h, 024h, 018h, 08Bh, 084h, 024h, 0ACh, 000h, 000h, 000h
    db 08Bh, 040h, 028h, 08Bh, 05Ch, 024h, 064h, 003h, 0C3h, 08Bh, 05Ch, 024h, 018h, 001h, 018h, 08Bh
    db 084h, 024h, 0A0h, 000h, 000h, 000h, 039h, 044h, 024h, 014h, 00Fh, 08Dh, 018h, 001h, 000h, 000h
    db 039h, 044h, 024h, 010h, 00Fh, 08Dh, 00Eh, 001h, 000h, 000h, 08Bh, 044h, 024h, 038h, 08Bh, 0DFh
    db 02Bh, 0D8h, 08Bh, 084h, 024h, 088h, 000h, 000h, 000h, 03Bh, 0D8h, 00Fh, 08Dh, 0F7h, 000h, 000h
    db 000h, 08Bh, 05Ch, 024h, 038h, 02Bh, 0DFh, 03Bh, 0D8h, 00Fh, 08Dh, 0E9h, 000h, 000h, 000h, 08Bh
    db 044h, 024h, 038h, 08Bh, 05Ch, 024h, 034h, 08Dh, 004h, 068h, 003h, 0C5h, 003h, 0C3h, 08Bh, 05Ch
    db 024h, 030h, 003h, 0C3h, 08Dh, 044h, 010h, 004h, 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 011h, 08Bh
    db 0D7h, 02Bh, 0D5h, 003h, 0C2h, 08Bh, 0D3h, 003h, 0D0h, 08Bh, 09Ch, 024h, 09Ch, 000h, 000h, 000h
    db 0C1h, 0FAh, 003h, 088h, 014h, 00Bh, 08Bh, 054h, 024h, 040h, 02Bh, 0D5h, 003h, 0C2h, 08Bh, 054h
    db 024h, 034h, 08Bh, 09Ch, 024h, 098h, 000h, 000h, 000h, 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 014h
    db 00Bh, 08Bh, 054h, 024h, 044h, 08Bh, 05Ch, 024h, 078h, 02Bh, 0D5h, 08Bh, 06Ch, 024h, 038h, 003h
    db 0C2h, 08Dh, 014h, 028h, 0C1h, 0FAh, 003h, 088h, 014h, 00Bh, 08Bh, 05Ch, 024h, 02Ch, 08Bh, 054h
    db 024h, 048h, 02Bh, 0D3h, 08Bh, 05Ch, 024h, 030h, 003h, 0C2h, 08Dh, 014h, 038h, 08Bh, 0BCh, 024h
    db 0B8h, 000h, 000h, 000h, 0C1h, 0FAh, 003h, 0C1h, 0E7h, 002h, 088h, 014h, 039h, 08Bh, 07Ch, 024h
    db 04Ch, 08Bh, 0D7h, 02Bh, 0D3h, 08Bh, 09Ch, 024h, 090h, 000h, 000h, 000h, 003h, 0C2h, 08Bh, 054h
    db 024h, 040h, 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 014h, 033h, 08Bh, 05Ch, 024h, 034h, 08Bh, 0D7h
    db 02Bh, 0D3h, 08Bh, 09Ch, 024h, 084h, 000h, 000h, 000h, 003h, 0C2h, 08Bh, 054h, 024h, 044h, 003h
    db 0D0h, 0C1h, 0FAh, 003h, 088h, 016h, 08Bh, 0D7h, 08Bh, 07Ch, 024h, 048h, 02Bh, 0D5h, 003h, 0D0h
    db 08Bh, 044h, 024h, 07Ch, 003h, 0D7h, 0C1h, 0FAh, 003h, 088h, 014h, 030h, 08Bh, 084h, 024h, 080h
    db 000h, 000h, 000h, 0E9h, 0A2h, 000h, 000h, 000h, 08Bh, 054h, 024h, 038h, 08Bh, 06Ch, 024h, 040h
    db 08Bh, 05Ch, 024h, 034h, 08Bh, 0C7h, 02Bh, 0C2h, 08Dh, 004h, 040h, 02Bh, 0C5h, 08Dh, 044h, 018h
    db 004h, 08Bh, 09Ch, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 05Bh, 038h, 08Bh, 0ACh, 024h, 090h, 000h
    db 000h, 000h, 0C1h, 0F8h, 003h, 08Bh, 004h, 083h, 08Ah, 094h, 010h
    dd g_Va01356FE0
    db 08Bh, 05Ch, 024h, 078h, 088h, 014h, 00Bh, 08Bh, 09Ch, 024h, 098h, 000h, 000h, 000h, 02Bh, 0F8h
    db 08Ah, 097h
    dd g_Va01356FE0
    db 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 0BCh, 024h, 09Ch, 000h, 000h, 000h, 0C1h, 0E0h
    db 002h, 088h, 014h, 001h, 08Bh, 044h, 024h, 074h, 08Ah, 014h, 008h, 08Bh, 084h, 024h, 080h, 000h
    db 000h, 000h, 088h, 011h, 08Ah, 010h, 088h, 014h, 00Fh, 08Bh, 07Ch, 024h, 07Ch, 08Ah, 014h, 038h
    db 088h, 014h, 00Bh, 08Bh, 09Ch, 024h, 084h, 000h, 000h, 000h, 08Ah, 013h, 088h, 014h, 02Eh, 08Bh
    db 054h, 024h, 074h, 08Ah, 014h, 032h, 088h, 016h, 08Bh, 094h, 024h, 08Ch, 000h, 000h, 000h, 08Ah
    db 014h, 013h, 088h, 014h, 037h, 08Bh, 06Ch, 024h, 020h, 08Bh, 07Ch, 024h, 01Ch, 045h, 040h, 043h
    db 041h, 046h, 04Fh, 0BAh, 008h, 000h, 000h, 000h, 089h, 06Ch, 024h, 020h, 089h, 084h, 024h, 080h
    db 000h, 000h, 000h, 089h, 09Ch, 024h, 084h, 000h, 000h, 000h, 089h, 07Ch, 024h, 01Ch, 00Fh, 085h
    db 067h, 0FCh, 0FFh, 0FFh, 08Bh, 044h, 024h, 050h, 03Bh, 084h, 024h, 0C0h, 000h, 000h, 000h, 00Fh
    db 084h, 09Bh, 002h, 000h, 000h, 08Bh, 04Ch, 024h, 058h, 089h, 04Ch, 024h, 020h, 08Bh, 04Ch, 024h
    db 06Ch, 089h, 054h, 024h, 018h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 00Fh, 0B6h, 041h, 002h, 00Fh
    db 0B6h, 019h, 00Fh, 0B6h, 079h, 0FFh, 00Fh, 0B6h, 051h, 001h, 00Fh, 0B6h, 069h, 003h, 00Fh, 0B6h
    db 071h, 004h, 089h, 044h, 024h, 034h, 00Fh, 0B6h, 041h, 005h, 089h, 044h, 024h, 040h, 00Fh, 0B6h
    db 041h, 006h, 089h, 044h, 024h, 044h, 00Fh, 0B6h, 041h, 007h, 089h, 044h, 024h, 048h, 00Fh, 0B6h
    db 041h, 008h, 089h, 044h, 024h, 04Ch, 08Bh, 0C3h, 02Bh, 0C7h, 085h, 0C0h, 089h, 05Ch, 024h, 02Ch
    db 089h, 054h, 024h, 030h, 07Fh, 004h, 08Bh, 0C7h, 02Bh, 0C3h, 089h, 044h, 024h, 014h, 08Bh, 0C2h
    db 02Bh, 0C3h, 085h, 0C0h, 07Fh, 004h, 08Bh, 0C3h, 02Bh, 0C2h, 001h, 044h, 024h, 014h, 08Bh, 05Ch
    db 024h, 034h, 08Bh, 0C3h, 02Bh, 0C2h, 085h, 0C0h, 07Eh, 004h, 08Bh, 0D0h, 0EBh, 002h, 02Bh, 0D3h
    db 001h, 054h, 024h, 014h, 08Bh, 0C5h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 004h, 08Bh, 0C3h, 02Bh, 0C5h
    db 001h, 044h, 024h, 014h, 08Bh, 054h, 024h, 040h, 08Bh, 0C6h, 02Bh, 0C2h, 085h, 0C0h, 07Fh, 004h
    db 08Bh, 0C2h, 02Bh, 0C6h, 08Bh, 05Ch, 024h, 044h, 089h, 044h, 024h, 010h, 08Bh, 0C2h, 02Bh, 0C3h
    db 085h, 0C0h, 07Fh, 004h, 08Bh, 0C3h, 02Bh, 0C2h, 001h, 044h, 024h, 010h, 08Bh, 054h, 024h, 048h
    db 08Bh, 0C3h, 02Bh, 0C2h, 085h, 0C0h, 07Fh, 004h, 08Bh, 0C2h, 02Bh, 0C3h, 001h, 044h, 024h, 010h
    db 08Bh, 05Ch, 024h, 04Ch, 08Bh, 0C2h, 02Bh, 0C3h, 085h, 0C0h, 07Fh, 004h, 08Bh, 0C3h, 02Bh, 0C2h
    db 08Bh, 054h, 024h, 010h, 003h, 0D0h, 08Bh, 044h, 024h, 014h, 03Dh, 0FFh, 000h, 000h, 000h, 089h
    db 054h, 024h, 010h, 0C7h, 044h, 024h, 01Ch, 0FFh, 000h, 000h, 000h, 07Fh, 004h, 089h, 044h, 024h
    db 01Ch, 08Bh, 094h, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 042h, 028h, 08Bh, 054h, 024h, 024h, 08Dh
    db 044h, 002h, 0FCh, 08Bh, 054h, 024h, 01Ch, 001h, 010h, 08Bh, 044h, 024h, 010h, 03Dh, 0FFh, 000h
    db 000h, 000h, 0C7h, 044h, 024h, 01Ch, 0FFh, 000h, 000h, 000h, 07Fh, 004h, 089h, 044h, 024h, 01Ch
    db 08Bh, 084h, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 050h, 028h, 08Bh, 044h, 024h, 024h, 003h, 0C2h
    db 08Bh, 054h, 024h, 01Ch, 001h, 010h, 08Bh, 084h, 024h, 0A0h, 000h, 000h, 000h, 039h, 044h, 024h
    db 014h, 00Fh, 08Dh, 0D5h, 000h, 000h, 000h, 039h, 044h, 024h, 010h, 00Fh, 08Dh, 0CBh, 000h, 000h
    db 000h, 08Bh, 084h, 024h, 088h, 000h, 000h, 000h, 08Bh, 0D6h, 02Bh, 0D5h, 03Bh, 0D0h, 00Fh, 08Dh
    db 0B8h, 000h, 000h, 000h, 08Bh, 0D5h, 02Bh, 0D6h, 03Bh, 0D0h, 00Fh, 08Dh, 0ACh, 000h, 000h, 000h
    db 08Bh, 054h, 024h, 034h, 08Dh, 044h, 07Dh, 000h, 003h, 0C7h, 003h, 0C2h, 003h, 044h, 024h, 030h
    db 08Bh, 054h, 024h, 02Ch, 08Dh, 044h, 010h, 004h, 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 011h, 08Bh
    db 0D6h, 02Bh, 0D7h, 003h, 0C2h, 08Bh, 054h, 024h, 030h, 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 051h
    db 001h, 08Bh, 054h, 024h, 040h, 02Bh, 0D7h, 003h, 0C2h, 08Bh, 054h, 024h, 034h, 003h, 0D0h, 0C1h
    db 0FAh, 003h, 088h, 051h, 002h, 08Bh, 054h, 024h, 044h, 02Bh, 0D7h, 08Bh, 07Ch, 024h, 02Ch, 003h
    db 0C2h, 08Dh, 014h, 028h, 0C1h, 0FAh, 003h, 088h, 051h, 003h, 08Bh, 054h, 024h, 048h, 02Bh, 0D7h
    db 08Bh, 07Ch, 024h, 030h, 003h, 0C2h, 08Dh, 014h, 030h, 08Bh, 074h, 024h, 020h, 0C1h, 0FAh, 003h
    db 088h, 016h, 08Bh, 074h, 024h, 034h, 08Bh, 0D3h, 02Bh, 0D7h, 003h, 0C2h, 08Bh, 054h, 024h, 040h
    db 003h, 0D0h, 0C1h, 0FAh, 003h, 088h, 051h, 005h, 08Bh, 0D3h, 02Bh, 0D6h, 003h, 0C2h, 08Bh, 054h
    db 024h, 044h, 003h, 0D0h, 0C1h, 0FAh, 003h, 02Bh, 0DDh, 088h, 051h, 006h, 08Bh, 054h, 024h, 048h
    db 003h, 0D8h, 003h, 0DAh, 0C1h, 0FBh, 003h, 088h, 059h, 007h, 0EBh, 03Dh, 08Bh, 05Ch, 024h, 040h
    db 08Bh, 054h, 024h, 034h, 08Bh, 0C6h, 02Bh, 0C5h, 08Dh, 004h, 040h, 02Bh, 0C3h, 08Dh, 044h, 010h
    db 004h, 08Bh, 094h, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 052h, 038h, 0C1h, 0F8h, 003h, 08Bh, 004h
    db 082h, 08Ah, 094h, 028h
    dd g_Va01356FE0
    db 088h, 051h, 003h, 08Bh, 054h, 024h, 020h, 02Bh, 0F0h, 08Ah, 086h
    dd g_Va01356FE0
    db 088h, 002h, 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h, 08Bh, 054h, 024h, 020h, 003h, 0D0h, 003h
    db 0C8h, 08Bh, 044h, 024h, 018h, 048h, 089h, 054h, 024h, 020h, 089h, 044h, 024h, 018h, 00Fh, 085h
    db 080h, 0FDh, 0FFh, 0FFh, 0BAh, 008h, 000h, 000h, 000h, 08Bh, 044h, 024h, 070h, 08Bh, 04Ch, 024h
    db 068h, 08Bh, 074h, 024h, 060h, 08Bh, 05Ch, 024h, 050h, 08Bh, 07Ch, 024h, 05Ch, 08Bh, 06Ch, 024h
    db 054h, 003h, 0CAh, 003h, 0C2h, 003h, 0F2h, 089h, 04Ch, 024h, 068h, 08Bh, 04Ch, 024h, 064h, 043h
    db 003h, 0FAh, 089h, 044h, 024h, 070h, 0B8h, 004h, 000h, 000h, 000h, 003h, 0C8h, 089h, 074h, 024h
    db 060h, 08Bh, 074h, 024h, 024h, 089h, 05Ch, 024h, 050h, 08Bh, 05Ch, 024h, 058h, 089h, 07Ch, 024h
    db 05Ch, 08Bh, 07Ch, 024h, 06Ch, 003h, 0F0h, 08Bh, 044h, 024h, 050h, 089h, 04Ch, 024h, 064h, 08Bh
    db 08Ch, 024h, 094h, 000h, 000h, 000h, 003h, 0FAh, 003h, 0DAh, 003h, 0EAh, 03Bh, 0C1h, 089h, 06Ch
    db 024h, 054h, 089h, 05Ch, 024h, 058h, 089h, 07Ch, 024h, 06Ch, 089h, 074h, 024h, 024h, 00Fh, 082h
    db 006h, 0F9h, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 098h, 000h, 000h, 000h, 0C3h
?d_009ae6a0@@YAXXZ ENDP
_TEXT$d00dae6a0 ENDS
_TEXT SEGMENT

; retail @ 0x009AF530 size 51
public ?d_009af530@@YAXXZ
?d_009af530@@YAXXZ PROC
    db 8Bh, 0Dh, 7Ch, 6Ah, 35h, 01h, 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 0Ch, 8Bh, 04h
    db 81h, 83h, 3Eh, 02h, 50h, 56h, 7Ch, 0Dh, 0E8h, 43h, 0FFh, 0FFh, 0FFh, 83h, 0C4h, 08h
    db 89h, 46h, 30h, 5Eh, 0C3h, 0FFh, 15h, 68h, 6Eh, 35h, 01h, 83h, 0C4h, 08h, 89h, 46h
    db 30h, 5Eh, 0C3h
?d_009af530@@YAXXZ ENDP

; retail @ 0x009B10E0 size 3558
public ?d_009b10e0@@YAXXZ
?d_009b10e0@@YAXXZ PROC
    db 81h, 0ECh, 78h, 01h, 00h, 00h, 8Bh, 84h, 24h, 8Ch, 01h, 00h, 00h, 8Bh, 8Ch, 24h
    db 90h, 01h, 00h, 00h, 8Bh, 14h, 81h, 8Bh, 04h, 85h, 58h, 81h, 2Dh, 01h, 8Bh, 8Ch
    db 24h, 80h, 01h, 00h, 00h, 53h, 89h, 44h, 24h, 08h, 55h, 8Bh, 0ACh, 24h, 90h, 01h
    db 00h, 00h, 8Bh, 0C1h, 2Bh, 0C5h, 89h, 44h, 24h, 14h, 8Dh, 04h, 29h, 89h, 44h, 24h
    db 28h, 8Dh, 04h, 52h, 83h, 0F8h, 20h, 56h, 57h, 89h, 54h, 24h, 18h, 89h, 44h, 24h
    db 10h, 7Eh, 08h, 0C7h, 44h, 24h, 10h, 20h, 00h, 00h, 00h, 83h, 0C1h, 03h, 89h, 4Ch
    db 24h, 20h, 83h, 0C9h, 0FFh, 2Bh, 0CDh, 8Dh, 84h, 24h, 0FAh, 00h, 00h, 00h, 89h, 4Ch
    db 24h, 28h, 0C7h, 44h, 24h, 2Ch, 09h, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 28h, 8Bh, 5Ch, 24h, 20h, 8Dh, 34h, 19h, 8Bh, 0C8h, 0C7h, 44h, 24h
    db 24h, 02h, 00h, 00h, 00h, 0Fh, 0B6h, 7Ch, 2Eh, 0FEh, 0Fh, 0B6h, 46h, 0FEh, 8Bh, 0D7h
    db 2Bh, 0D0h, 85h, 0D2h, 7Fh, 04h, 2Bh, 0C7h, 8Bh, 0D0h, 8Bh, 44h, 24h, 18h, 2Bh, 0C2h
    db 83h, 0C0h, 20h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h, 0C0h
    db 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h
    db 0Fh, 0B6h, 7Ch, 2Eh, 0FFh, 0Fh, 0B6h, 56h, 0FFh, 66h, 89h, 41h, 0FEh, 8Bh, 0C7h, 2Bh
    db 0C2h, 85h, 0C0h, 7Eh, 04h, 8Bh, 0D0h, 0EBh, 02h, 2Bh, 0D7h, 8Bh, 44h, 24h, 18h, 2Bh
    db 0C2h, 83h, 0C0h, 20h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h
    db 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h, 7Eh, 02h, 8Bh
    db 0C2h, 0Fh, 0B6h, 3Ch, 2Eh, 0Fh, 0B6h, 16h, 66h, 89h, 01h, 8Bh, 0C7h, 2Bh, 0C2h, 85h
    db 0C0h, 7Eh, 04h, 8Bh, 0D0h, 0EBh, 02h, 2Bh, 0D7h, 8Bh, 44h, 24h, 18h, 2Bh, 0C2h, 83h
    db 0C0h, 20h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h, 0C0h, 7Dh
    db 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h, 0Fh
    db 0B6h, 3Bh, 0Fh, 0B6h, 56h, 01h, 66h, 89h, 41h, 02h, 8Bh, 0C7h, 2Bh, 0C2h, 85h, 0C0h
    db 7Eh, 04h, 8Bh, 0D0h, 0EBh, 02h, 2Bh, 0D7h, 8Bh, 44h, 24h, 18h, 2Bh, 0C2h, 83h, 0C0h
    db 20h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h
    db 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h, 66h, 89h
    db 41h, 04h, 8Bh, 44h, 24h, 24h, 83h, 0C1h, 08h, 83h, 0C6h, 04h, 83h, 0C3h, 04h, 48h
    db 89h, 44h, 24h, 24h, 0Fh, 85h, 0EBh, 0FEh, 0FFh, 0FFh, 8Bh, 54h, 24h, 20h, 8Bh, 0C1h
    db 8Bh, 4Ch, 24h, 2Ch, 03h, 0D5h, 49h, 89h, 54h, 24h, 20h, 89h, 4Ch, 24h, 2Ch, 0Fh
    db 85h, 0BBh, 0FEh, 0FFh, 0FFh, 8Bh, 9Ch, 24h, 90h, 01h, 00h, 00h, 43h, 8Dh, 44h, 24h
    db 6Ah, 0BDh, 08h, 00h, 00h, 00h, 33h, 0FFh, 8Bh, 0C8h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 74h, 3Bh, 0FFh, 0Fh, 0B6h, 44h, 3Bh, 0FEh, 8Bh, 0D6h, 2Bh, 0D0h, 85h, 0D2h
    db 7Fh, 04h, 2Bh, 0C6h, 8Bh, 0D0h, 8Bh, 44h, 24h, 18h, 2Bh, 0C2h, 83h, 0C0h, 20h, 83h
    db 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h
    db 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h, 0Fh, 0B6h, 14h, 3Bh
    db 66h, 89h, 41h, 0FEh, 8Bh, 0C2h, 2Bh, 0C6h, 85h, 0C0h, 7Eh, 04h, 8Bh, 0F0h, 0EBh, 02h
    db 2Bh, 0F2h, 8Bh, 44h, 24h, 18h, 2Bh, 0C6h, 83h, 0C0h, 20h, 83h, 0F8h, 0C0h, 7Dh, 06h
    db 8Bh, 44h, 24h, 14h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 74h
    db 24h, 10h, 3Bh, 0C6h, 7Eh, 02h, 8Bh, 0C6h, 0Fh, 0B6h, 74h, 3Bh, 01h, 66h, 89h, 01h
    db 8Bh, 0C6h, 2Bh, 0C2h, 85h, 0C0h, 7Eh, 04h, 8Bh, 0D0h, 0EBh, 02h, 2Bh, 0D6h, 8Bh, 44h
    db 24h, 18h, 2Bh, 0C2h, 83h, 0C0h, 20h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 14h
    db 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 10h, 3Bh, 0C2h
    db 7Eh, 02h, 8Bh, 0C2h, 66h, 89h, 41h, 02h, 83h, 0C7h, 03h, 83h, 0C1h, 06h, 83h, 0FFh
    db 09h, 0Fh, 82h, 39h, 0FFh, 0FFh, 0FFh, 03h, 9Ch, 24h, 98h, 01h, 00h, 00h, 4Dh, 8Bh
    db 0C1h, 0Fh, 85h, 1Fh, 0FFh, 0FFh, 0FFh, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 5Ch, 24h, 30h, 8Bh
    db 94h, 24h, 94h, 01h, 00h, 00h, 8Dh, 4Dh, 04h, 8Dh, 7Bh, 02h, 2Bh, 0DDh, 89h, 4Ch
    db 24h, 14h, 8Bh, 8Ch, 24h, 90h, 01h, 00h, 00h, 89h, 5Ch, 24h, 64h, 8Bh, 0D9h, 2Bh
    db 0EBh, 89h, 6Ch, 24h, 20h, 8Bh, 0EAh, 2Bh, 0EBh, 8Bh, 5Ch, 24h, 30h, 89h, 6Ch, 24h
    db 54h, 8Bh, 6Ch, 24h, 1Ch, 2Bh, 0EBh, 89h, 6Ch, 24h, 5Ch, 8Bh, 0EAh, 2Bh, 0EBh, 8Bh
    db 5Ch, 24h, 1Ch, 8Dh, 42h, 03h, 2Bh, 0D3h, 89h, 44h, 24h, 24h, 8Dh, 74h, 24h, 6Ah
    db 8Dh, 84h, 24h, 08h, 01h, 00h, 00h, 89h, 6Ch, 24h, 60h, 89h, 54h, 24h, 58h, 0C7h
    db 44h, 24h, 2Ch, 08h, 00h, 00h, 00h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 29h, 0Fh, 0BFh, 1Eh, 0Fh, 0BFh, 56h, 0FEh, 89h, 6Ch, 24h, 30h, 0Fh, 0B6h
    db 69h, 01h, 89h, 6Ch, 24h, 1Ch, 8Bh, 6Ch, 24h, 20h, 03h, 0E9h, 89h, 6Ch, 24h, 28h
    db 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 18h, 2Bh, 0EBh, 0Fh, 0BFh, 58h, 0F0h
    db 2Bh, 0EBh, 8Bh, 5Ch, 24h, 64h, 2Bh, 0EAh, 8Bh, 54h, 24h, 28h, 0Fh, 0AFh, 6Ch, 24h
    db 30h, 0Fh, 0B6h, 1Ch, 1Ah, 0Fh, 0BFh, 10h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h, 0FEh, 03h
    db 0EBh, 0Fh, 0B6h, 59h, 0FFh, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 20h, 03h, 0D1h, 03h, 0EBh
    db 0Fh, 0B6h, 1Ah, 0Fh, 0BFh, 50h, 0F0h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 1Ch, 03h, 0EBh
    db 0Fh, 0BFh, 1Eh, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 85h, 0D2h, 7Dh
    db 0Ah, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0EBh, 14h, 81h, 0FAh, 0FFh, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 34h, 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h, 54h, 24h, 34h, 0Fh
    db 0B6h, 69h, 02h, 0Fh, 0BFh, 56h, 02h, 89h, 6Ch, 24h, 18h, 0BDh, 80h, 00h, 00h, 00h
    db 2Bh, 0EAh, 0Fh, 0BFh, 50h, 02h, 2Bh, 0EAh, 0Fh, 0BFh, 50h, 0F2h, 2Bh, 0EAh, 2Bh, 0EBh
    db 8Bh, 5Ch, 24h, 20h, 0Fh, 0AFh, 6Ch, 24h, 1Ch, 03h, 0D9h, 0Fh, 0B6h, 5Bh, 01h, 0Fh
    db 0AFh, 0DAh, 0Fh, 0BFh, 50h, 02h, 03h, 0EBh, 0Fh, 0B6h, 5Fh, 0FFh, 0Fh, 0AFh, 0DAh, 0Fh
    db 0BFh, 56h, 02h, 03h, 0EBh, 8Bh, 5Ch, 24h, 18h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 30h
    db 03h, 0EBh, 0Fh, 0BFh, 1Eh, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 85h
    db 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h, 0EBh, 14h, 81h, 0FAh, 0FFh
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 38h, 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h, 54h, 24h
    db 38h, 0Fh, 0B6h, 69h, 03h, 0Fh, 0BFh, 5Eh, 04h, 0Fh, 0BFh, 50h, 0F4h, 89h, 6Ch, 24h
    db 10h, 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 58h, 04h, 2Bh, 0EBh, 0Fh, 0BFh
    db 5Eh, 02h, 2Bh, 0EAh, 2Bh, 0EBh, 8Bh, 5Ch, 24h, 5Ch, 0Fh, 0AFh, 6Ch, 24h, 18h, 0Fh
    db 0B6h, 1Ch, 3Bh, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 50h, 04h, 03h, 0EBh, 0Fh, 0B6h, 1Fh, 0Fh
    db 0AFh, 0DAh, 0Fh, 0BFh, 56h, 04h, 03h, 0EBh, 8Bh, 5Ch, 24h, 10h, 0Fh, 0AFh, 0DAh, 8Bh
    db 54h, 24h, 1Ch, 03h, 0EBh, 0Fh, 0BFh, 5Eh, 02h, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h
    db 0C1h, 0FAh, 07h, 85h, 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 00h, 00h, 0EBh
    db 14h, 81h, 0FAh, 0FFh, 00h, 00h, 00h, 0C7h, 44h, 24h, 3Ch, 0FFh, 00h, 00h, 00h, 7Fh
    db 04h, 89h, 54h, 24h, 3Ch, 0Fh, 0B6h, 69h, 04h, 0Fh, 0BFh, 5Eh, 06h, 0Fh, 0BFh, 50h
    db 06h, 89h, 6Ch, 24h, 1Ch, 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 58h, 0F6h
    db 2Bh, 0EAh, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 04h, 2Bh, 0EBh, 0Fh, 0B6h, 5Fh, 01h, 0Fh, 0AFh
    db 6Ch, 24h, 10h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 14h, 03h, 0EBh, 0Fh, 0B6h, 5Ah, 0FFh
    db 0Fh, 0BFh, 50h, 0F6h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h, 06h, 03h, 0EBh, 8Bh, 5Ch, 24h
    db 1Ch, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 18h, 03h, 0EBh, 0Fh, 0BFh, 5Eh, 04h, 0Fh, 0AFh
    db 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 85h, 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 40h
    db 00h, 00h, 00h, 00h, 0EBh, 14h, 81h, 0FAh, 0FFh, 00h, 00h, 00h, 0C7h, 44h, 24h, 40h
    db 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h, 54h, 24h, 40h, 0Fh, 0B6h, 69h, 05h, 0Fh, 0BFh
    db 5Eh, 08h, 0Fh, 0BFh, 50h, 08h, 89h, 6Ch, 24h, 18h, 0BDh, 80h, 00h, 00h, 00h, 2Bh
    db 0EBh, 0Fh, 0BFh, 58h, 0F8h, 2Bh, 0EAh, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 06h, 2Bh, 0EBh, 0Fh
    db 0B6h, 5Fh, 02h, 0Fh, 0AFh, 6Ch, 24h, 1Ch, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 14h, 03h
    db 0EBh, 0Fh, 0B6h, 1Ah, 0Fh, 0BFh, 50h, 0F8h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h, 08h, 03h
    db 0EBh, 8Bh, 5Ch, 24h, 18h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 10h, 03h, 0EBh, 0Fh, 0BFh
    db 5Eh, 06h, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h, 85h, 0D2h, 7Dh, 0Ah
    db 0C7h, 44h, 24h, 44h, 00h, 00h, 00h, 00h, 0EBh, 14h, 81h, 0FAh, 0FFh, 00h, 00h, 00h
    db 0C7h, 44h, 24h, 44h, 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h, 54h, 24h, 44h, 0Fh, 0B6h
    db 69h, 06h, 0Fh, 0BFh, 5Eh, 0Ah, 0Fh, 0BFh, 50h, 0Ah, 89h, 6Ch, 24h, 10h, 0BDh, 80h
    db 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 58h, 0FAh, 2Bh, 0EAh, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh
    db 08h, 2Bh, 0EBh, 0Fh, 0B6h, 5Fh, 03h, 0Fh, 0AFh, 6Ch, 24h, 18h, 0Fh, 0AFh, 0DAh, 8Bh
    db 54h, 24h, 14h, 03h, 0EBh, 0Fh, 0B6h, 5Ah, 01h, 0Fh, 0BFh, 50h, 0FAh, 0Fh, 0AFh, 0DAh
    db 0Fh, 0BFh, 56h, 0Ah, 03h, 0EBh, 8Bh, 5Ch, 24h, 10h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h
    db 1Ch, 03h, 0EBh, 0Fh, 0BFh, 5Eh, 08h, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh
    db 07h, 85h, 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 48h, 00h, 00h, 00h, 00h, 0EBh, 14h, 81h
    db 0FAh, 0FFh, 00h, 00h, 00h, 0C7h, 44h, 24h, 48h, 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h
    db 54h, 24h, 48h, 0Fh, 0BFh, 5Eh, 0Ch, 0Fh, 0BFh, 50h, 0Ch, 0BDh, 80h, 00h, 00h, 00h
    db 2Bh, 0EBh, 0Fh, 0BFh, 58h, 0FCh, 2Bh, 0EAh, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 0Ah, 2Bh, 0EBh
    db 0Fh, 0B6h, 5Fh, 04h, 0Fh, 0AFh, 6Ch, 24h, 10h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 14h
    db 03h, 0EBh, 0Fh, 0B6h, 5Ah, 02h, 0Fh, 0BFh, 50h, 0FCh, 0Fh, 0AFh, 0DAh, 0Fh, 0B6h, 51h
    db 07h, 03h, 0EBh, 8Bh, 0DAh, 0Fh, 0BFh, 56h, 0Ch, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 18h
    db 03h, 0EBh, 0Fh, 0BFh, 5Eh, 0Ah, 0Fh, 0AFh, 0D3h, 8Dh, 54h, 2Ah, 40h, 0C1h, 0FAh, 07h
    db 85h, 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 4Ch, 00h, 00h, 00h, 00h, 0EBh, 14h, 81h, 0FAh
    db 0FFh, 00h, 00h, 00h, 0C7h, 44h, 24h, 4Ch, 0FFh, 00h, 00h, 00h, 7Fh, 04h, 89h, 54h
    db 24h, 4Ch, 0Fh, 0BFh, 50h, 0Eh, 0Fh, 0BFh, 58h, 0FEh, 89h, 54h, 24h, 28h, 0Fh, 0BFh
    db 56h, 0Eh, 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EAh, 2Bh, 6Ch, 24h, 28h, 2Bh, 0EBh, 0Fh
    db 0BFh, 5Eh, 0Ch, 2Bh, 0EBh, 0Fh, 0B6h, 59h, 07h, 0Fh, 0AFh, 0EBh, 0Fh, 0B6h, 59h, 08h
    db 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 50h, 0Eh, 03h, 0EBh, 0Fh, 0B6h, 5Fh, 05h, 0Fh, 0AFh, 0DAh
    db 8Bh, 54h, 24h, 14h, 03h, 0EBh, 0Fh, 0B6h, 5Ah, 03h, 0Fh, 0BFh, 50h, 0FEh, 0Fh, 0AFh
    db 0DAh, 8Bh, 54h, 24h, 10h, 03h, 0EBh, 0Fh, 0BFh, 5Eh, 0Ch, 0Fh, 0AFh, 0D3h, 8Dh, 54h
    db 2Ah, 40h, 0C1h, 0FAh, 07h, 85h, 0D2h, 7Dh, 0Ah, 0C7h, 44h, 24h, 50h, 00h, 00h, 00h
    db 00h, 0EBh, 14h, 81h, 0FAh, 0FFh, 00h, 00h, 00h, 0C7h, 44h, 24h, 50h, 0FFh, 00h, 00h
    db 00h, 7Fh, 04h, 89h, 54h, 24h, 50h, 8Ah, 54h, 24h, 34h, 8Bh, 5Ch, 24h, 54h, 8Bh
    db 6Ch, 24h, 24h, 88h, 14h, 0Bh, 8Ah, 54h, 24h, 38h, 8Bh, 5Ch, 24h, 60h, 88h, 55h
    db 0FEh, 8Ah, 54h, 24h, 3Ch, 88h, 14h, 3Bh, 8Ah, 54h, 24h, 40h, 8Bh, 5Ch, 24h, 14h
    db 88h, 55h, 00h, 8Ah, 54h, 24h, 44h, 8Bh, 6Ch, 24h, 58h, 88h, 14h, 2Bh, 8Bh, 6Ch
    db 24h, 24h, 8Ah, 54h, 24h, 48h, 88h, 55h, 02h, 8Ah, 54h, 24h, 4Ch, 88h, 55h, 03h
    db 8Ah, 54h, 24h, 50h, 88h, 55h, 04h, 8Bh, 94h, 24h, 98h, 01h, 00h, 00h, 03h, 0DAh
    db 03h, 0EAh, 03h, 0CAh, 03h, 0FAh, 8Bh, 54h, 24h, 2Ch, 83h, 0C0h, 10h, 83h, 0C6h, 12h
    db 4Ah, 89h, 5Ch, 24h, 14h, 89h, 6Ch, 24h, 24h, 89h, 54h, 24h, 2Ch, 0Fh, 85h, 4Dh
    db 0FBh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 81h, 0C4h, 78h, 01h, 00h, 00h, 0C3h, 0CCh, 0CCh
    db 81h, 0ECh, 60h, 01h, 00h, 00h, 8Bh, 84h, 24h, 74h, 01h, 00h, 00h, 8Bh, 8Ch, 24h
    db 78h, 01h, 00h, 00h, 8Bh, 14h, 81h, 8Bh, 04h, 85h, 58h, 81h, 2Dh, 01h, 8Bh, 8Ch
    db 24h, 68h, 01h, 00h, 00h, 53h, 89h, 44h, 24h, 04h, 55h, 8Bh, 0ACh, 24h, 78h, 01h
    db 00h, 00h, 8Bh, 0C1h, 2Bh, 0C5h, 89h, 44h, 24h, 20h, 8Dh, 04h, 29h, 89h, 44h, 24h
    db 28h, 8Dh, 04h, 52h, 83h, 0F8h, 18h, 56h, 57h, 89h, 54h, 24h, 18h, 89h, 44h, 24h
    db 14h, 7Eh, 08h, 0C7h, 44h, 24h, 14h, 18h, 00h, 00h, 00h, 83h, 0C1h, 03h, 83h, 0CAh
    db 0FFh, 2Bh, 0D5h, 89h, 4Ch, 24h, 20h, 8Dh, 44h, 24h, 52h, 89h, 54h, 24h, 2Ch, 0C7h
    db 44h, 24h, 24h, 09h, 00h, 00h, 00h, 0EBh, 08h, 8Bh, 54h, 24h, 2Ch, 8Bh, 4Ch, 24h
    db 20h, 8Bh, 0D9h, 03h, 0D1h, 8Bh, 0F8h, 0C7h, 44h, 24h, 1Ch, 02h, 00h, 00h, 00h, 90h
    db 0Fh, 0B6h, 74h, 2Ah, 0FEh, 0Fh, 0B6h, 42h, 0FEh, 8Bh, 0CEh, 2Bh, 0C8h, 85h, 0C9h, 7Eh
    db 04h, 8Bh, 0C1h, 0EBh, 02h, 2Bh, 0C6h, 0B9h, 10h, 00h, 00h, 00h, 2Bh, 0C8h, 8Bh, 44h
    db 24h, 18h, 8Dh, 04h, 48h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h, 10h, 0EBh, 12h
    db 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 4Ch, 24h, 14h, 3Bh, 0C1h, 7Eh, 02h
    db 8Bh, 0C1h, 0Fh, 0B6h, 74h, 2Ah, 0FFh, 0Fh, 0B6h, 4Ah, 0FFh, 66h, 89h, 47h, 0FEh, 8Bh
    db 0C6h, 2Bh, 0C1h, 85h, 0C0h, 7Fh, 04h, 2Bh, 0CEh, 8Bh, 0C1h, 0B9h, 10h, 00h, 00h, 00h
    db 2Bh, 0C8h, 8Bh, 44h, 24h, 18h, 8Dh, 04h, 48h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h
    db 24h, 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 4Ch, 24h, 14h
    db 3Bh, 0C1h, 7Eh, 02h, 8Bh, 0C1h, 0Fh, 0B6h, 34h, 2Ah, 0Fh, 0B6h, 0Ah, 66h, 89h, 07h
    db 8Bh, 0C6h, 2Bh, 0C1h, 85h, 0C0h, 7Fh, 04h, 2Bh, 0CEh, 8Bh, 0C1h, 0B9h, 10h, 00h, 00h
    db 00h, 2Bh, 0C8h, 8Bh, 44h, 24h, 18h, 8Dh, 04h, 48h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh
    db 44h, 24h, 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 4Ch, 24h
    db 14h, 3Bh, 0C1h, 7Eh, 02h, 8Bh, 0C1h, 0Fh, 0B6h, 33h, 0Fh, 0B6h, 4Ah, 01h, 66h, 89h
    db 47h, 02h, 8Bh, 0C6h, 2Bh, 0C1h, 85h, 0C0h, 7Fh, 04h, 2Bh, 0CEh, 8Bh, 0C1h, 0B9h, 10h
    db 00h, 00h, 00h, 2Bh, 0C8h, 8Bh, 44h, 24h, 18h, 8Dh, 04h, 48h, 83h, 0F8h, 0C0h, 7Dh
    db 06h, 8Bh, 44h, 24h, 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh
    db 4Ch, 24h, 14h, 3Bh, 0C1h, 7Eh, 02h, 8Bh, 0C1h, 66h, 89h, 47h, 04h, 8Bh, 44h, 24h
    db 1Ch, 83h, 0C7h, 08h, 83h, 0C2h, 04h, 83h, 0C3h, 04h, 48h, 89h, 44h, 24h, 1Ch, 0Fh
    db 85h, 0DBh, 0FEh, 0FFh, 0FFh, 8Bh, 54h, 24h, 20h, 8Bh, 4Ch, 24h, 24h, 03h, 0D5h, 49h
    db 89h, 54h, 24h, 20h, 8Bh, 0C7h, 89h, 4Ch, 24h, 24h, 0Fh, 85h, 0A9h, 0FEh, 0FFh, 0FFh
    db 8Bh, 0ACh, 24h, 78h, 01h, 00h, 00h, 45h, 8Bh, 0DDh, 8Dh, 84h, 24h, 0E2h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 1Ch, 08h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 33h, 0F6h, 8Bh, 0F8h, 0Fh, 0B6h, 54h, 33h, 0FFh, 0Fh, 0B6h, 44h, 33h, 0FEh, 8Bh, 0CAh
    db 2Bh, 0C8h, 85h, 0C9h, 7Eh, 04h, 8Bh, 0C1h, 0EBh, 02h, 2Bh, 0C2h, 0B9h, 10h, 00h, 00h
    db 00h, 2Bh, 0C8h, 8Bh, 44h, 24h, 18h, 8Dh, 04h, 48h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh
    db 44h, 24h, 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 4Ch, 24h
    db 14h, 3Bh, 0C1h, 7Eh, 02h, 8Bh, 0C1h, 0Fh, 0B6h, 0Ch, 33h, 66h, 89h, 47h, 0FEh, 8Bh
    db 0C1h, 2Bh, 0C2h, 85h, 0C0h, 7Fh, 04h, 2Bh, 0D1h, 8Bh, 0C2h, 0BAh, 10h, 00h, 00h, 00h
    db 2Bh, 0D0h, 8Bh, 44h, 24h, 18h, 8Dh, 04h, 50h, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h
    db 24h, 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 54h, 24h, 14h
    db 3Bh, 0C2h, 7Eh, 02h, 8Bh, 0C2h, 0Fh, 0B6h, 54h, 33h, 01h, 66h, 89h, 07h, 8Bh, 0C2h
    db 2Bh, 0C1h, 85h, 0C0h, 7Fh, 04h, 2Bh, 0CAh, 8Bh, 0C1h, 8Bh, 54h, 24h, 18h, 0B9h, 10h
    db 00h, 00h, 00h, 2Bh, 0C8h, 8Dh, 04h, 4Ah, 83h, 0F8h, 0C0h, 7Dh, 06h, 8Bh, 44h, 24h
    db 10h, 0EBh, 12h, 85h, 0C0h, 7Dh, 04h, 33h, 0C0h, 0EBh, 0Ah, 8Bh, 4Ch, 24h, 14h, 3Bh
    db 0C1h, 7Eh, 02h, 8Bh, 0C1h, 66h, 89h, 47h, 02h, 83h, 0C6h, 03h, 83h, 0C7h, 06h, 83h
    db 0FEh, 09h, 0Fh, 82h, 2Ch, 0FFh, 0FFh, 0FFh, 8Bh, 94h, 24h, 80h, 01h, 00h, 00h, 8Bh
    db 4Ch, 24h, 1Ch, 03h, 0DAh, 49h, 8Bh, 0C7h, 89h, 4Ch, 24h, 1Ch, 0Fh, 85h, 0Eh, 0FFh
    db 0FFh, 0FFh, 8Bh, 74h, 24h, 30h, 8Bh, 54h, 24h, 28h, 8Bh, 0BCh, 24h, 78h, 01h, 00h
    db 00h, 8Bh, 0C6h, 2Bh, 0C2h, 89h, 44h, 24h, 44h, 8Bh, 84h, 24h, 7Ch, 01h, 00h, 00h
    db 8Bh, 0C8h, 2Bh, 0CAh, 89h, 4Ch, 24h, 4Ch, 8Bh, 0CFh, 2Bh, 0CAh, 89h, 4Ch, 24h, 20h
    db 8Bh, 0C8h, 2Bh, 0CFh, 89h, 4Ch, 24h, 3Ch, 8Bh, 0CEh, 2Bh, 0C8h, 83h, 0C6h, 03h, 89h
    db 4Ch, 24h, 34h, 8Bh, 0CAh, 8Dh, 0BCh, 24h, 0E2h, 00h, 00h, 00h, 83h, 0C0h, 02h, 89h
    db 74h, 24h, 1Ch, 89h, 4Ch, 24h, 28h, 8Dh, 74h, 24h, 60h, 89h, 7Ch, 24h, 30h, 89h
    db 6Ch, 24h, 40h, 89h, 44h, 24h, 24h, 0C7h, 44h, 24h, 2Ch, 08h, 00h, 00h, 00h, 90h
    db 8Bh, 44h, 24h, 24h, 89h, 44h, 24h, 18h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h
    db 8Bh, 0C5h, 89h, 7Ch, 24h, 10h, 0Fh, 0BFh, 1Fh, 0Fh, 0BFh, 16h, 89h, 5Ch, 24h, 38h
    db 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 0F0h, 2Bh, 0EAh, 2Bh, 0EBh, 0Fh
    db 0BFh, 5Fh, 0FEh, 2Bh, 0EBh, 8Bh, 5Ch, 24h, 20h, 0Fh, 0B6h, 1Ch, 19h, 0Fh, 0AFh, 0EBh
    db 8Bh, 5Ch, 24h, 44h, 0Fh, 0B6h, 1Ch, 19h, 0Fh, 0AFh, 0DAh, 8Bh, 54h, 24h, 20h, 03h
    db 0EBh, 0Fh, 0B6h, 5Ch, 11h, 0FFh, 0Fh, 0BFh, 57h, 0FEh, 0Fh, 0AFh, 0DAh, 0Fh, 0B6h, 10h
    db 0Fh, 0AFh, 54h, 24h, 38h, 03h, 0EBh, 0Fh, 0B6h, 19h, 03h, 0EAh, 0Fh, 0BFh, 56h, 0F0h
    db 0Fh, 0AFh, 0DAh, 8Dh, 6Ch, 2Bh, 40h, 0C1h, 0FDh, 07h, 85h, 0EDh, 7Dh, 04h, 33h, 0D2h
    db 0EBh, 0Fh, 81h, 0FDh, 0FFh, 00h, 00h, 00h, 0BAh, 0FFh, 00h, 00h, 00h, 7Fh, 02h, 8Bh
    db 0D5h, 8Bh, 5Ch, 24h, 4Ch, 0Fh, 0BFh, 7Fh, 02h, 88h, 14h, 19h, 0Fh, 0BFh, 5Eh, 02h
    db 0Fh, 0BFh, 56h, 0F2h, 89h, 5Ch, 24h, 48h, 8Bh, 5Ch, 24h, 3Ch, 0BDh, 80h, 00h, 00h
    db 00h, 2Bh, 0EFh, 2Bh, 6Ch, 24h, 48h, 03h, 0D8h, 2Bh, 0EAh, 2Bh, 6Ch, 24h, 38h, 0Fh
    db 0B6h, 10h, 0Fh, 0AFh, 0EAh, 8Bh, 54h, 24h, 34h, 0Fh, 0B6h, 1Ch, 13h, 0Fh, 0BFh, 56h
    db 02h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h, 0F2h, 03h, 0EBh, 0Fh, 0B6h, 59h, 01h, 0Fh, 0AFh
    db 0DAh, 0Fh, 0B6h, 50h, 01h, 0Fh, 0AFh, 0D7h, 03h, 0EBh, 03h, 0EAh, 8Bh, 54h, 24h, 20h
    db 0Fh, 0B6h, 1Ch, 11h, 8Bh, 54h, 24h, 10h, 0Fh, 0BFh, 12h, 0Fh, 0AFh, 0DAh, 8Dh, 6Ch
    db 2Bh, 40h, 0C1h, 0FDh, 07h, 85h, 0EDh, 7Dh, 04h, 33h, 0D2h, 0EBh, 0Fh, 81h, 0FDh, 0FFh
    db 00h, 00h, 00h, 0BAh, 0FFh, 00h, 00h, 00h, 7Fh, 02h, 8Bh, 0D5h, 8Bh, 5Ch, 24h, 3Ch
    db 88h, 14h, 18h, 0Fh, 0BFh, 56h, 0F4h, 8Dh, 2Ch, 18h, 8Bh, 5Ch, 24h, 10h, 0Fh, 0BFh
    db 5Bh, 04h, 0BDh, 80h, 00h, 00h, 00h, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 04h, 2Bh, 0EBh, 8Bh
    db 5Ch, 24h, 34h, 2Bh, 0EAh, 0Fh, 0B6h, 50h, 01h, 2Bh, 0EFh, 0Fh, 0AFh, 0EAh, 8Bh, 54h
    db 24h, 18h, 0Fh, 0B6h, 1Ch, 1Ah, 0Fh, 0BFh, 56h, 04h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h
    db 0F4h, 03h, 0EBh, 0Fh, 0B6h, 59h, 02h, 0Fh, 0AFh, 0DAh, 0Fh, 0B6h, 10h, 0Fh, 0AFh, 0D7h
    db 8Bh, 7Ch, 24h, 10h, 03h, 0EBh, 0Fh, 0B6h, 58h, 02h, 03h, 0EAh, 0Fh, 0BFh, 57h, 04h
    db 0Fh, 0AFh, 0DAh, 8Dh, 6Ch, 2Bh, 40h, 0C1h, 0FDh, 07h, 85h, 0EDh, 7Dh, 04h, 33h, 0DBh
    db 0EBh, 0Fh, 81h, 0FDh, 0FFh, 00h, 00h, 00h, 0BBh, 0FFh, 00h, 00h, 00h, 7Fh, 02h, 8Bh
    db 0DDh, 8Bh, 6Ch, 24h, 18h, 88h, 5Dh, 00h, 0Fh, 0BFh, 5Fh, 06h, 0BDh, 80h, 00h, 00h
    db 00h, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 06h, 2Bh, 0EBh, 0Fh, 0BFh, 5Eh, 0F6h, 2Bh, 0EBh, 8Bh
    db 5Ch, 24h, 1Ch, 2Bh, 0EAh, 0Fh, 0B6h, 50h, 02h, 0Fh, 0AFh, 0EAh, 8Bh, 54h, 24h, 14h
    db 0Fh, 0B6h, 1Ch, 13h, 0Fh, 0BFh, 56h, 06h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 57h, 06h, 03h
    db 0EBh, 0Fh, 0B6h, 58h, 03h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 56h, 0F6h, 03h, 0EBh, 0Fh, 0B6h
    db 59h, 03h, 0Fh, 0AFh, 0DAh, 0Fh, 0BFh, 57h, 04h, 03h, 0EBh, 0Fh, 0B6h, 58h, 01h, 0Fh
    db 0AFh, 0DAh, 8Dh, 6Ch, 2Bh, 40h, 0C1h, 0FDh, 07h, 85h, 0EDh, 7Dh, 04h, 33h, 0D2h, 0EBh
    db 0Fh, 81h, 0FDh, 0FFh, 00h, 00h, 00h, 0BAh, 0FFh, 00h, 00h, 00h, 7Fh, 02h, 8Bh, 0D5h
    db 8Bh, 6Ch, 24h, 18h, 88h, 55h, 01h, 8Bh, 54h, 24h, 14h, 83h, 0C2h, 04h, 83h, 0C7h
    db 08h, 83h, 0C5h, 04h, 83h, 0C6h, 08h, 83h, 0C1h, 04h, 83h, 0C0h, 04h, 83h, 0FAh, 08h
    db 89h, 54h, 24h, 14h, 89h, 7Ch, 24h, 10h, 89h, 6Ch, 24h, 18h, 0Fh, 82h, 0C4h, 0FDh
    db 0FFh, 0FFh, 8Bh, 84h, 24h, 80h, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 54h, 24h
    db 24h, 8Bh, 6Ch, 24h, 40h, 8Bh, 4Ch, 24h, 28h, 03h, 0F8h, 03h, 0D0h, 03h, 0E8h, 03h
    db 0C8h, 8Bh, 44h, 24h, 2Ch, 89h, 7Ch, 24h, 1Ch, 8Bh, 7Ch, 24h, 30h, 83h, 0C7h, 12h
    db 48h, 89h, 54h, 24h, 24h, 89h, 6Ch, 24h, 40h, 89h, 4Ch, 24h, 28h, 89h, 7Ch, 24h
    db 30h, 89h, 44h, 24h, 2Ch, 0Fh, 85h, 65h, 0FDh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 81h
    db 0C4h, 60h, 01h, 00h, 00h, 0C3h
?d_009b10e0@@YAXXZ ENDP

; retail @ 0x009B3F40 size 555
_TEXT ENDS
_TEXT$d00db3f40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB3F40 size 555
public ?d_009b3f40@@YAXXZ
?d_009b3f40@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 0A8h, 000h, 000h, 000h, 00Fh, 0B6h, 043h, 014h
    db 00Fh, 0B6h, 080h
    dd ?g_Rva01142608@@3PAEA
    db 08Bh, 04Bh, 008h, 0C1h, 0E0h, 008h, 08Dh, 014h, 008h, 08Bh, 082h, 090h, 001h, 000h, 000h, 089h
    db 045h, 0F8h, 08Dh, 041h, 008h, 056h, 083h, 0C1h, 018h, 057h, 089h, 055h, 0F0h, 089h, 045h, 0ECh
    db 089h, 04Dh, 0F4h, 0C7h, 045h, 0FCh, 000h, 000h, 000h, 000h, 08Bh, 073h, 00Ch, 033h, 0C9h, 08Bh
    db 07Dh, 0ECh, 0F3h, 00Fh, 06Fh, 017h, 08Bh, 07Dh, 0F4h, 0F3h, 00Fh, 06Fh, 01Fh, 08Dh, 0BDh, 060h
    db 0FFh, 0FFh, 0FFh, 08Bh, 043h, 010h, 066h, 00Fh, 0EFh, 0FFh, 066h, 00Fh, 06Fh, 004h, 00Eh, 066h
    db 00Fh, 06Fh, 0C8h, 066h, 00Fh, 071h, 0E1h, 00Fh, 066h, 00Fh, 0EFh, 0C1h, 066h, 00Fh, 0F9h, 0C1h
    db 066h, 00Fh, 0FDh, 0C2h, 066h, 00Fh, 0E4h, 0C3h, 066h, 00Fh, 0EFh, 0C1h, 066h, 00Fh, 0F9h, 0C1h
    db 066h, 00Fh, 07Fh, 004h, 00Fh, 066h, 00Fh, 07Fh, 03Ch, 008h, 083h, 0C1h, 010h, 081h, 0F9h, 080h
    db 000h, 000h, 000h, 07Ch, 0C5h, 08Bh, 04Bh, 00Ch, 00Fh, 0BFh, 001h, 08Bh, 08Ah, 090h, 005h, 000h
    db 000h, 03Bh, 0C1h, 08Bh, 073h, 010h, 07Ch, 014h, 08Bh, 092h, 090h, 003h, 000h, 000h, 003h, 0D0h
    db 00Fh, 0AFh, 055h, 0F8h, 0C1h, 0FAh, 010h, 066h, 089h, 016h, 0EBh, 024h, 0F7h, 0D9h, 03Bh, 0C1h
    db 07Fh, 017h, 02Bh, 082h, 090h, 003h, 000h, 000h, 00Fh, 0AFh, 045h, 0F8h, 005h, 0FFh, 0FFh, 000h
    db 000h, 0C1h, 0F8h, 010h, 066h, 089h, 006h, 0EBh, 007h, 0C7h, 045h, 0FCh, 001h, 000h, 000h, 000h
    db 083h, 0C6h, 006h, 0B8h, 004h, 000h, 000h, 000h, 089h, 075h, 0F4h, 089h, 045h, 0F8h, 0EBh, 009h
    db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 0FFh, 08Bh, 088h
    dd g_Va012D8258
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 039h, 08Bh, 043h, 00Ch, 00Fh, 0BFh, 004h, 048h, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Eh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 070h, 0FCh, 08Bh, 04Dh, 0F8h, 08Bh, 089h
    dd g_Va012D825C
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 039h, 08Bh, 053h, 00Ch, 00Fh, 0BFh, 004h, 04Ah, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Eh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 070h, 0FEh, 08Bh, 04Dh, 0F8h, 08Bh, 089h
    dd g_Va012D8260
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 038h, 08Bh, 053h, 00Ch, 00Fh, 0BFh, 004h, 04Ah, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Dh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 030h, 08Bh, 045h, 0F8h, 08Bh, 055h, 0F4h, 083h
    db 0C0h, 00Ch, 083h, 0C2h, 006h, 03Dh, 000h, 001h, 000h, 000h, 089h, 045h, 0F8h, 089h, 055h, 0F4h
    db 00Fh, 082h, 0EEh, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 08Bh, 0E5h, 05Dh, 08Bh, 0E3h, 05Bh, 0C3h
?d_009b3f40@@YAXXZ ENDP
_TEXT$d00db3f40 ENDS
_TEXT SEGMENT

; retail @ 0x009B4170 size 539
_TEXT ENDS
_TEXT$d00db4170 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB4170 size 539
public ?d_009b4170@@YAXXZ
?d_009b4170@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 0A8h, 000h, 000h, 000h, 00Fh, 0B6h, 043h, 014h
    db 00Fh, 0B6h, 080h
    dd ?g_Rva01142608@@3PAEA
    db 08Bh, 04Bh, 008h, 0C1h, 0E0h, 008h, 08Dh, 014h, 008h, 08Bh, 082h, 090h, 001h, 000h, 000h, 089h
    db 045h, 0F8h, 08Dh, 041h, 008h, 056h, 083h, 0C1h, 018h, 057h, 089h, 055h, 0F0h, 089h, 045h, 0ECh
    db 089h, 04Dh, 0F4h, 0C7h, 045h, 0FCh, 000h, 000h, 000h, 000h, 08Bh, 073h, 00Ch, 033h, 0C9h, 08Bh
    db 07Dh, 0ECh, 00Fh, 06Fh, 017h, 08Bh, 07Dh, 0F4h, 00Fh, 06Fh, 01Fh, 08Dh, 0BDh, 060h, 0FFh, 0FFh
    db 0FFh, 08Bh, 043h, 010h, 00Fh, 0EFh, 0FFh, 00Fh, 06Fh, 004h, 00Eh, 00Fh, 07Fh, 0C1h, 00Fh, 071h
    db 0E1h, 00Fh, 00Fh, 0EFh, 0C1h, 00Fh, 0F9h, 0C1h, 00Fh, 0FDh, 0C2h, 00Fh, 0E4h, 0C3h, 00Fh, 0EFh
    db 0C1h, 00Fh, 0F9h, 0C1h, 00Fh, 07Fh, 004h, 00Fh, 00Fh, 07Fh, 03Ch, 008h, 083h, 0C1h, 008h, 081h
    db 0F9h, 080h, 000h, 000h, 000h, 07Ch, 0D0h, 08Bh, 04Bh, 00Ch, 00Fh, 0BFh, 001h, 08Bh, 08Ah, 090h
    db 005h, 000h, 000h, 03Bh, 0C1h, 08Bh, 073h, 010h, 07Ch, 014h, 08Bh, 092h, 090h, 003h, 000h, 000h
    db 003h, 0D0h, 00Fh, 0AFh, 055h, 0F8h, 0C1h, 0FAh, 010h, 066h, 089h, 016h, 0EBh, 024h, 0F7h, 0D9h
    db 03Bh, 0C1h, 07Fh, 017h, 02Bh, 082h, 090h, 003h, 000h, 000h, 00Fh, 0AFh, 045h, 0F8h, 005h, 0FFh
    db 0FFh, 000h, 000h, 0C1h, 0F8h, 010h, 066h, 089h, 006h, 0EBh, 007h, 0C7h, 045h, 0FCh, 001h, 000h
    db 000h, 000h, 083h, 0C6h, 006h, 0B8h, 004h, 000h, 000h, 000h, 089h, 075h, 0F4h, 089h, 045h, 0F8h
    db 0EBh, 007h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 088h
    dd g_Va012D8258
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 039h, 08Bh, 043h, 00Ch, 00Fh, 0BFh, 004h, 048h, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Eh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 070h, 0FCh, 08Bh, 04Dh, 0F8h, 08Bh, 089h
    dd g_Va012D825C
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 039h, 08Bh, 053h, 00Ch, 00Fh, 0BFh, 004h, 04Ah, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Eh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 070h, 0FEh, 08Bh, 04Dh, 0F8h, 08Bh, 089h
    dd g_Va012D8260
    db 00Fh, 0B7h, 0B4h, 04Dh, 060h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 075h, 005h, 0FFh, 045h, 0FCh, 0EBh
    db 038h, 08Bh, 053h, 00Ch, 00Fh, 0BFh, 004h, 04Ah, 099h, 08Bh, 0F8h, 08Bh, 045h, 0F0h, 033h, 0FAh
    db 02Bh, 0FAh, 08Bh, 055h, 0FCh, 08Bh, 094h, 090h, 090h, 007h, 000h, 000h, 003h, 094h, 088h, 090h
    db 005h, 000h, 000h, 03Bh, 0FAh, 07Dh, 005h, 0FFh, 045h, 0FCh, 0EBh, 00Dh, 08Bh, 045h, 0F4h, 0C7h
    db 045h, 0FCh, 000h, 000h, 000h, 000h, 066h, 089h, 030h, 08Bh, 045h, 0F8h, 08Bh, 055h, 0F4h, 083h
    db 0C0h, 00Ch, 083h, 0C2h, 006h, 03Dh, 000h, 001h, 000h, 000h, 089h, 045h, 0F8h, 089h, 055h, 0F4h
    db 00Fh, 082h, 0EEh, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 08Bh, 0E5h, 05Dh, 08Bh, 0E3h, 05Bh, 0C3h
?d_009b4170@@YAXXZ ENDP
_TEXT$d00db4170 ENDS
_TEXT SEGMENT

; retail @ 0x009B6080 size 88
public ?d_009b6080@@YAXXZ
?d_009b6080@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 8Bh, 18h, 8Bh, 0C3h, 83h, 0F8h, 0FFh, 57h, 8Bh, 0FBh, 74h
    db 25h, 8Dh, 0Ch, 52h, 55h, 8Bh, 6Ch, 8Eh, 04h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Dh, 0Ch, 40h, 3Bh, 6Ch, 8Eh, 04h, 8Dh, 0Ch, 8Eh, 7Eh, 09h, 8Bh, 0F8h, 8Bh, 01h
    db 83h, 0F8h, 0FFh, 75h, 0EBh, 5Dh, 3Bh, 0C3h, 75h, 0Fh, 8Bh, 4Ch, 24h, 0Ch, 89h, 11h
    db 8Dh, 14h, 52h, 5Fh, 89h, 04h, 96h, 5Bh, 0C3h, 8Dh, 0Ch, 7Fh, 89h, 14h, 8Eh, 8Dh
    db 14h, 52h, 5Fh, 89h, 04h, 96h, 5Bh, 0C3h
?d_009b6080@@YAXXZ ENDP

; retail @ 0x009B6420 size 125
public ?d_009b6420@@YAXXZ
?d_009b6420@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 10h, 33h, 0C0h, 49h, 89h, 4Ch, 24h, 10h, 78h, 6Fh, 53h, 8Bh, 5Ch
    db 24h, 08h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 57h, 0EBh, 05h, 8Bh, 4Ch, 24h, 20h, 90h
    db 8Bh, 74h, 24h, 1Ch, 0D3h, 0FEh, 8Bh, 4Bh, 18h, 83h, 0E6h, 01h, 85h, 0C9h, 74h, 16h
    db 8Dh, 04h, 40h, 0Fh, 0B6h, 4Ch, 85h, 08h, 8Dh, 7Ch, 85h, 00h, 51h, 56h, 53h, 0E8h
    db 4Ch, 60h, 0FFh, 0FFh, 0EBh, 14h, 8Dh, 14h, 40h, 0Fh, 0B6h, 44h, 95h, 08h, 8Dh, 7Ch
    db 95h, 00h, 50h, 56h, 53h, 0E8h, 76h, 5Eh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 85h, 0F6h, 74h
    db 05h, 8Bh, 47h, 04h, 0EBh, 02h, 8Bh, 07h, 8Bh, 4Ch, 24h, 20h, 0D1h, 0E8h, 83h, 0E0h
    db 7Fh, 49h, 89h, 4Ch, 24h, 20h, 79h, 0A3h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h
?d_009b6420@@YAXXZ ENDP

; retail @ 0x009B6D80 size 5028
_TEXT ENDS
_TEXT$d00db6d80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB6D80 size 5028
public ?d_009b6d80@@YAXXZ
?d_009b6d80@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 0B8h, 001h, 000h, 000h, 08Bh, 043h, 00Ch, 08Bh
    db 053h, 018h, 08Bh, 04Bh, 010h, 056h, 08Bh, 073h, 01Ch, 089h, 045h, 0F8h, 08Dh, 004h, 032h, 03Bh
    db 0F0h, 057h, 089h, 075h, 0F4h, 089h, 04Dh, 0FCh, 089h, 045h, 08Ch, 00Fh, 083h, 0FBh, 008h, 000h
    db 000h, 08Dh, 00Ch, 085h, 000h, 000h, 000h, 000h, 089h, 04Dh, 0CCh, 0EBh, 003h, 08Dh, 049h, 000h
    db 08Bh, 053h, 008h, 08Bh, 04Ah, 024h, 08Bh, 055h, 0CCh, 08Bh, 00Ch, 00Ah, 08Bh, 053h, 020h, 08Bh
    db 00Ch, 08Ah, 083h, 0F9h, 003h, 00Fh, 086h, 03Dh, 008h, 000h, 000h, 066h, 089h, 04Dh, 090h, 066h
    db 089h, 04Dh, 092h, 066h, 089h, 04Dh, 094h, 066h, 089h, 04Dh, 096h, 050h, 055h, 051h, 052h, 056h
    db 057h, 00Fh, 06Fh, 045h, 090h, 00Fh, 06Fh, 00Dh
    dd g_Va012D86C0
    db 00Fh, 0D5h, 0C8h, 00Fh, 0D5h, 0C8h, 00Fh, 071h, 0D1h, 005h, 00Fh, 07Fh, 08Dh, 070h, 0FFh, 0FFh
    db 0FFh, 08Bh, 045h, 0F8h, 033h, 0D2h, 08Dh, 0B5h, 050h, 0FEh, 0FFh, 0FFh, 08Dh, 0BDh, 0D0h, 0FEh
    db 0FFh, 0FFh, 08Bh, 04Bh, 014h, 00Fh, 0EFh, 0FFh, 02Bh, 0D1h, 08Dh, 004h, 090h, 00Fh, 06Fh, 004h
    db 010h, 00Fh, 07Fh, 0C1h, 00Fh, 060h, 0C7h, 00Fh, 06Fh, 010h, 00Fh, 07Fh, 0D3h, 00Fh, 068h, 0CFh
    db 00Fh, 07Fh, 007h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 04Fh, 008h, 00Fh, 06Fh, 024h
    db 008h, 00Fh, 07Fh, 057h, 010h, 00Fh, 07Fh, 05Fh, 018h, 00Fh, 07Fh, 0E5h, 00Fh, 060h, 0E7h, 00Fh
    db 06Fh, 004h, 048h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C1h, 00Fh, 07Fh, 067h, 020h, 00Fh, 060h, 0C7h
    db 08Dh, 004h, 088h, 00Fh, 07Fh, 06Fh, 028h, 00Fh, 068h, 0CFh, 00Fh, 06Fh, 014h, 010h, 00Fh, 07Fh
    db 047h, 030h, 00Fh, 07Fh, 0D3h, 00Fh, 060h, 0D7h, 00Fh, 07Fh, 04Fh, 038h, 00Fh, 068h, 0DFh, 00Fh
    db 06Fh, 020h, 00Fh, 07Fh, 057h, 040h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 05Fh, 048h, 00Fh, 060h, 0E7h
    db 00Fh, 068h, 0EFh, 00Fh, 06Fh, 004h, 008h, 00Fh, 07Fh, 067h, 050h, 00Fh, 07Fh, 0C1h, 00Fh, 07Fh
    db 06Fh, 058h, 00Fh, 060h, 0C7h, 00Fh, 068h, 0CFh, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h, 00Fh
    db 07Fh, 0D3h, 00Fh, 07Fh, 047h, 060h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 06Fh, 024h, 010h
    db 00Fh, 07Fh, 04Fh, 068h, 00Fh, 07Fh, 0E5h, 00Fh, 060h, 0E7h, 00Fh, 07Fh, 057h, 070h, 00Fh, 07Fh
    db 05Fh, 078h, 00Fh, 06Fh, 000h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C1h, 00Fh, 07Fh, 0A7h, 080h, 000h
    db 000h, 000h, 00Fh, 060h, 0C7h, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 0AFh, 088h, 000h, 000h, 000h, 00Fh
    db 07Fh, 087h, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 08Fh, 098h, 000h, 000h, 000h, 00Fh, 075h, 0DBh
    db 00Fh, 071h, 0F3h, 00Fh, 00Fh, 071h, 0D3h, 008h, 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh, 077h, 050h
    db 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h, 00Fh
    db 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh, 07Fh, 0F5h, 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh, 077h, 060h
    db 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh
    db 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh, 077h, 070h
    db 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh
    db 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h, 080h
    db 000h, 000h, 000h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh
    db 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 07Fh, 0DFh, 00Fh, 071h
    db 0D7h, 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0E6h, 00Fh, 0FDh, 0C7h, 00Fh, 0FDh, 0E7h, 00Fh, 071h
    db 0E2h, 001h, 00Fh, 071h, 0E6h, 001h, 00Fh, 071h, 0E0h, 001h, 00Fh, 071h, 0E4h, 001h, 00Fh, 0D5h
    db 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h, 0EEh, 00Fh, 06Fh, 0BDh, 070h, 0FFh, 0FFh
    db 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 07Fh, 04Dh, 0B0h, 00Fh, 07Fh, 06Dh, 0A0h, 00Fh
    db 0F9h, 0CFh, 00Fh, 0F9h, 0EFh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 071h, 0E1h
    db 00Fh, 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh, 07Fh, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh
    db 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0FAh, 00Fh, 0D9h, 0FCh, 00Fh, 0D9h, 0E2h, 00Fh
    db 0EBh, 0FCh, 00Fh, 0F9h, 07Dh, 090h, 00Fh, 071h, 0E7h, 00Fh, 00Fh, 0DBh, 0FEh, 083h, 0C7h, 008h
    db 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh, 077h, 050h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 07Fh
    db 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh, 07Fh, 0F5h
    db 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh
    db 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh
    db 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh, 077h, 070h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh
    db 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh
    db 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h
    db 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh
    db 00Fh, 0FDh, 0EEh, 00Fh, 071h, 0D3h, 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0E6h, 00Fh, 0FDh, 0C3h
    db 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E2h, 001h, 00Fh, 071h, 0E6h, 001h, 00Fh, 071h, 0E0h, 001h, 00Fh
    db 071h, 0E4h, 001h, 00Fh, 0D5h, 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h, 0EEh, 00Fh
    db 07Fh, 04Dh, 0E0h, 00Fh, 07Fh, 06Dh, 0D0h, 00Fh, 06Fh, 09Dh, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 07Fh
    db 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h, 0CBh, 00Fh, 0F9h, 0EBh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h
    db 0E6h, 00Fh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh, 047h, 040h, 00Fh, 0DFh
    db 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0C2h, 00Fh, 0D9h
    db 0C4h, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh, 0C4h, 00Fh, 0F9h, 045h, 090h, 00Fh, 071h, 0E0h, 00Fh, 00Fh
    db 0DBh, 0C6h, 083h, 0EFh, 008h, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh
    db 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h, 00Fh
    db 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh, 0CCh, 00Fh
    db 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 0E3h
    db 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h
    db 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0D3h, 00Fh, 0EBh, 0D4h
    db 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 05Fh
    db 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0F4h
    db 001h, 00Fh, 0F9h, 067h, 040h, 00Fh, 0FDh, 067h, 050h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh, 020h, 00Fh, 0F9h, 0D9h
    db 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h
    db 050h, 00Fh, 0FDh, 067h, 060h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh
    db 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh, 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh
    db 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h, 060h, 00Fh, 0FDh
    db 067h, 070h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0E1h, 00Fh, 0F9h, 067h, 010h, 00Fh, 0F9h
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h, 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h
    db 000h, 00Fh, 0FDh, 0E2h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh
    db 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h
    db 030h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh
    db 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh
    db 06Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h
    db 0C7h, 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh
    db 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h, 00Fh
    db 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh, 0CCh, 00Fh
    db 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 0E3h
    db 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h
    db 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0D3h, 00Fh, 0EBh, 0D4h
    db 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 05Fh
    db 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0F4h
    db 001h, 00Fh, 0F9h, 067h, 040h, 00Fh, 0FDh, 067h, 050h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh, 020h, 00Fh, 0F9h, 0D9h
    db 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h
    db 050h, 00Fh, 0FDh, 067h, 060h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh
    db 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh, 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh
    db 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h, 060h, 00Fh, 0FDh
    db 067h, 070h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0E1h, 00Fh, 0F9h, 067h, 010h, 00Fh, 0F9h
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h, 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h
    db 000h, 00Fh, 0FDh, 0E2h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh
    db 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h
    db 030h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh
    db 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh
    db 06Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h
    db 0C7h, 008h, 083h, 0EEh, 008h, 08Bh, 06Dh, 0FCh, 08Dh, 06Ch, 095h, 000h, 00Fh, 06Fh, 006h, 00Fh
    db 067h, 046h, 008h, 00Fh, 07Fh, 045h, 000h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 067h, 04Eh, 018h, 00Fh
    db 07Fh, 04Ch, 00Dh, 000h, 00Fh, 06Fh, 056h, 020h, 00Fh, 067h, 056h, 028h, 00Fh, 07Fh, 054h, 04Dh
    db 000h, 00Fh, 06Fh, 05Eh, 030h, 00Fh, 067h, 05Eh, 038h, 08Dh, 06Ch, 08Dh, 000h, 00Fh, 07Fh, 05Ch
    db 015h, 000h, 00Fh, 06Fh, 046h, 040h, 00Fh, 067h, 046h, 048h, 00Fh, 07Fh, 045h, 000h, 00Fh, 06Fh
    db 04Eh, 050h, 00Fh, 067h, 04Eh, 058h, 00Fh, 07Fh, 04Ch, 00Dh, 000h, 00Fh, 06Fh, 056h, 060h, 00Fh
    db 067h, 056h, 068h, 00Fh, 07Fh, 054h, 04Dh, 000h, 00Fh, 06Fh, 05Eh, 070h, 00Fh, 067h, 05Eh, 078h
    db 08Dh, 06Ch, 04Dh, 000h, 00Fh, 07Fh, 05Ch, 00Dh, 000h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h, 08Bh
    db 043h, 008h, 08Bh, 048h, 028h, 08Bh, 055h, 0F4h, 00Fh, 0B7h, 075h, 0E4h, 08Dh, 00Ch, 091h, 00Fh
    db 0B7h, 055h, 0E6h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0E2h, 08Bh, 039h, 003h, 0D6h, 00Fh, 0B7h, 075h
    db 0E0h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0B6h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0B4h, 003h, 0D6h, 00Fh
    db 0B7h, 075h, 0B2h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0B0h, 003h, 0D6h, 003h, 0FAh, 00Fh, 0B7h, 055h
    db 0D6h, 089h, 039h, 08Bh, 040h, 028h, 08Bh, 04Dh, 0CCh, 003h, 0C1h, 00Fh, 0B7h, 04Dh, 0D4h, 003h
    db 0D1h, 00Fh, 0B7h, 04Dh, 0D2h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0D0h, 003h, 0D1h, 00Fh, 0B7h, 04Dh
    db 0A6h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A4h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A2h, 003h, 0D1h, 00Fh
    db 0B7h, 04Dh, 0A0h, 003h, 0D1h, 001h, 010h, 08Bh, 045h, 08Ch, 0EBh, 064h, 056h, 057h, 051h, 08Bh
    db 075h, 0F8h, 08Bh, 07Dh, 0FCh, 052h, 08Bh, 04Bh, 014h, 033h, 0D2h, 02Bh, 0D1h, 08Dh, 034h, 096h
    db 00Fh, 06Fh, 006h, 00Fh, 07Fh, 004h, 097h, 08Dh, 03Ch, 097h, 00Fh, 06Fh, 00Ch, 00Eh, 00Fh, 07Fh
    db 00Ch, 00Fh, 00Fh, 06Fh, 014h, 04Eh, 08Dh, 034h, 08Eh, 00Fh, 07Fh, 014h, 04Fh, 08Dh, 03Ch, 08Fh
    db 00Fh, 06Fh, 01Ch, 016h, 00Fh, 07Fh, 01Ch, 017h, 00Fh, 06Fh, 026h, 00Fh, 06Fh, 02Ch, 00Eh, 00Fh
    db 07Fh, 027h, 00Fh, 06Fh, 034h, 04Eh, 08Dh, 034h, 08Eh, 00Fh, 07Fh, 02Ch, 00Fh, 00Fh, 07Fh, 034h
    db 04Fh, 00Fh, 06Fh, 03Ch, 016h, 08Dh, 03Ch, 08Fh, 00Fh, 07Fh, 03Ch, 017h, 05Ah, 059h, 05Fh, 05Eh
    db 08Bh, 075h, 0F8h, 08Bh, 055h, 0FCh, 0B9h, 008h, 000h, 000h, 000h, 003h, 0F1h, 003h, 0D1h, 08Bh
    db 04Dh, 0F4h, 089h, 075h, 0F8h, 08Bh, 075h, 0CCh, 041h, 083h, 0C6h, 004h, 03Bh, 0C8h, 089h, 055h
    db 0FCh, 089h, 04Dh, 0F4h, 089h, 075h, 0CCh, 00Fh, 082h, 017h, 0F7h, 0FFh, 0FFh, 08Bh, 073h, 01Ch
    db 08Bh, 053h, 014h, 08Dh, 00Ch, 0D5h, 000h, 000h, 000h, 000h, 0BFh, 008h, 000h, 000h, 000h, 02Bh
    db 0F9h, 08Bh, 04Bh, 018h, 0C1h, 0E1h, 003h, 02Bh, 0F9h, 08Bh, 04Dh, 0FCh, 003h, 0CFh, 048h, 03Bh
    db 0F0h, 089h, 04Dh, 0FCh, 089h, 04Dh, 0F8h, 089h, 075h, 0F4h, 089h, 045h, 08Ch, 00Fh, 083h, 02Ch
    db 00Ah, 000h, 000h, 090h, 08Bh, 043h, 008h, 08Bh, 040h, 024h, 08Bh, 044h, 0B0h, 004h, 08Bh, 07Bh
    db 020h, 08Bh, 004h, 087h, 083h, 0F8h, 003h, 00Fh, 086h, 0F4h, 009h, 000h, 000h, 066h, 089h, 045h
    db 090h, 066h, 089h, 045h, 092h, 066h, 089h, 045h, 094h, 066h, 089h, 045h, 096h, 066h, 00Fh, 0B6h
    db 041h, 0FBh, 066h, 089h, 085h, 0D0h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 041h, 004h, 066h, 089h
    db 085h, 060h, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 044h, 011h, 0FBh, 066h, 089h, 085h, 0D2h, 0FEh
    db 0FFh, 0FFh, 066h, 00Fh, 0B6h, 044h, 011h, 004h, 066h, 089h, 085h, 062h, 0FFh, 0FFh, 0FFh, 066h
    db 00Fh, 0B6h, 044h, 051h, 0FBh, 066h, 089h, 085h, 0D4h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 044h
    db 051h, 004h, 066h, 089h, 085h, 064h, 0FFh, 0FFh, 0FFh, 08Dh, 004h, 052h, 066h, 00Fh, 0B6h, 074h
    db 008h, 0FBh, 066h, 00Fh, 0B6h, 044h, 008h, 004h, 066h, 089h, 085h, 066h, 0FFh, 0FFh, 0FFh, 066h
    db 00Fh, 0B6h, 044h, 091h, 0FBh, 066h, 089h, 085h, 0D8h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 044h
    db 091h, 004h, 066h, 089h, 085h, 068h, 0FFh, 0FFh, 0FFh, 08Dh, 004h, 092h, 066h, 089h, 0B5h, 0D6h
    db 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 074h, 008h, 0FBh, 066h, 00Fh, 0B6h, 044h, 008h, 004h, 066h
    db 089h, 085h, 06Ah, 0FFh, 0FFh, 0FFh, 08Dh, 004h, 052h, 06Bh, 0D2h, 007h, 0D1h, 0E0h, 066h, 089h
    db 0B5h, 0DAh, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 074h, 008h, 0FBh, 066h, 00Fh, 0B6h, 044h, 008h
    db 004h, 066h, 089h, 085h, 06Ch, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 044h, 00Ah, 0FBh, 066h, 00Fh
    db 0B6h, 04Ch, 00Ah, 004h, 066h, 089h, 0B5h, 0DCh, 0FEh, 0FFh, 0FFh, 066h, 089h, 085h, 0DEh, 0FEh
    db 0FFh, 0FFh, 066h, 089h, 08Dh, 06Eh, 0FFh, 0FFh, 0FFh, 050h, 055h, 051h, 052h, 056h, 057h, 00Fh
    db 06Fh, 045h, 090h, 00Fh, 06Fh, 00Dh
    dd g_Va012D86C0
    db 00Fh, 0D5h, 0C8h, 00Fh, 0D5h, 0C8h, 00Fh, 071h, 0D1h, 005h, 00Fh, 07Fh, 08Dh, 070h, 0FFh, 0FFh
    db 0FFh, 08Bh, 045h, 0F8h, 033h, 0D2h, 083h, 0E8h, 004h, 08Dh, 0B5h, 050h, 0FEh, 0FFh, 0FFh, 08Dh
    db 0BDh, 0D0h, 0FEh, 0FFh, 0FFh, 08Bh, 04Bh, 014h, 02Bh, 0D1h, 00Fh, 06Fh, 000h, 00Fh, 06Fh, 00Ch
    db 008h, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h, 00Fh, 06Fh, 01Ch, 010h, 00Fh, 07Fh, 0C4h, 00Fh
    db 060h, 0C1h, 00Fh, 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h, 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh
    db 0C1h, 00Fh, 061h, 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h
    db 00Fh, 0EFh, 0FFh, 00Fh, 07Fh, 0C5h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 047h, 010h, 00Fh, 068h, 0EFh
    db 00Fh, 07Fh, 0C8h, 00Fh, 07Fh, 06Fh, 020h, 00Fh, 060h, 0CFh, 00Fh, 068h, 0C7h, 00Fh, 07Fh, 04Fh
    db 030h, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 047h, 040h, 00Fh, 060h, 0D7h, 00Fh, 068h
    db 0DFh, 00Fh, 07Fh, 057h, 050h, 00Fh, 060h, 0E7h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 05Fh, 060h, 00Fh
    db 06Fh, 000h, 00Fh, 06Fh, 00Ch, 008h, 00Fh, 07Fh, 067h, 070h, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h
    db 088h, 00Fh, 07Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0C4h, 00Fh, 06Fh, 01Ch, 010h, 00Fh
    db 060h, 0C1h, 00Fh, 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h, 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh
    db 0C1h, 00Fh, 061h, 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h
    db 00Fh, 07Fh, 0C5h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 047h, 018h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C8h
    db 00Fh, 07Fh, 06Fh, 028h, 00Fh, 060h, 0CFh, 00Fh, 068h, 0C7h, 00Fh, 07Fh, 04Fh, 038h, 00Fh, 07Fh
    db 0D3h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 047h, 048h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh
    db 057h, 058h, 00Fh, 060h, 0E7h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 05Fh, 068h, 00Fh, 07Fh, 067h, 078h
    db 00Fh, 07Fh, 0AFh, 088h, 000h, 000h, 000h, 00Fh, 075h, 0DBh, 00Fh, 071h, 0F3h, 00Fh, 00Fh, 071h
    db 0D3h, 008h, 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh, 077h, 050h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h
    db 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh
    db 07Fh, 0F5h, 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h
    db 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh
    db 0FDh, 0EEh, 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh, 077h, 070h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h
    db 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh
    db 0FDh, 0EEh, 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 0D3h
    db 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh
    db 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 07Fh, 0DFh, 00Fh, 071h, 0D7h, 007h, 00Fh, 07Fh, 0C2h, 00Fh
    db 07Fh, 0E6h, 00Fh, 0FDh, 0C7h, 00Fh, 0FDh, 0E7h, 00Fh, 071h, 0E2h, 001h, 00Fh, 071h, 0E6h, 001h
    db 00Fh, 071h, 0E0h, 001h, 00Fh, 071h, 0E4h, 001h, 00Fh, 0D5h, 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h
    db 0CAh, 00Fh, 0F9h, 0EEh, 00Fh, 07Fh, 04Dh, 0B0h, 00Fh, 07Fh, 06Dh, 0A0h, 00Fh, 06Fh, 0BDh, 070h
    db 0FFh, 0FFh, 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h, 0CFh, 00Fh, 0F9h, 0EFh, 00Fh
    db 071h, 0E1h, 00Fh, 00Fh, 071h, 0E5h, 00Fh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E6h, 00Fh, 00Fh
    db 06Fh, 07Fh, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h
    db 00Fh, 07Fh, 0FAh, 00Fh, 0D9h, 0FCh, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh, 0FCh, 00Fh, 0F9h, 07Dh, 090h
    db 00Fh, 071h, 0E7h, 00Fh, 00Fh, 0DBh, 0FEh, 083h, 0C7h, 008h, 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh
    db 077h, 050h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h
    db 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh, 07Fh, 0F5h, 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh
    db 077h, 060h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h
    db 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh
    db 077h, 070h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h
    db 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh
    db 0B7h, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh
    db 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 071h, 0D3h
    db 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0E6h, 00Fh, 0FDh, 0C3h, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E2h
    db 001h, 00Fh, 071h, 0E6h, 001h, 00Fh, 071h, 0E0h, 001h, 00Fh, 071h, 0E4h, 001h, 00Fh, 0D5h, 0D0h
    db 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h, 0EEh, 00Fh, 07Fh, 04Dh, 0E0h, 00Fh, 07Fh, 06Dh
    db 0D0h, 00Fh, 06Fh, 09Dh, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h
    db 0CBh, 00Fh, 0F9h, 0EBh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E1h, 00Fh
    db 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh, 047h, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh
    db 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0C2h, 00Fh, 0D9h, 0C4h, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh
    db 0C4h, 00Fh, 0F9h, 045h, 090h, 00Fh, 071h, 0E0h, 00Fh, 00Fh, 0DBh, 0C6h, 083h, 0EFh, 008h, 00Fh
    db 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh
    db 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h
    db 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh, 0CCh, 00Fh, 06Fh, 0A7h, 080h, 000h, 000h, 000h
    db 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h
    db 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh
    db 0E2h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0D3h, 00Fh, 0EBh, 0D4h, 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh
    db 00Fh, 0FDh, 0D9h, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 05Fh, 020h, 00Fh, 0FDh, 067h, 030h, 00Fh
    db 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0F4h
    db 001h, 00Fh, 0F9h, 067h, 040h, 00Fh, 0FDh, 067h, 050h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh, 020h, 00Fh, 0F9h, 0D9h
    db 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h
    db 050h, 00Fh, 0FDh, 067h, 060h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh
    db 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh, 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh
    db 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h, 060h, 00Fh, 0FDh
    db 067h, 070h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0E1h, 00Fh, 0F9h, 067h, 010h, 00Fh, 0F9h
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h, 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h
    db 000h, 00Fh, 0FDh, 0E2h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh
    db 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h
    db 030h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh
    db 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh
    db 06Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h
    db 0C7h, 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh
    db 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h, 00Fh
    db 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh, 0CCh, 00Fh
    db 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 0E3h
    db 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 065h, 090h
    db 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0D3h, 00Fh, 0EBh, 0D4h
    db 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh, 067h, 010h, 00Fh, 0FDh, 05Fh
    db 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh, 025h
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0DCh, 00Fh, 07Fh, 0DCh, 00Fh, 06Fh, 06Fh, 010h, 00Fh, 0FDh, 0E5h, 00Fh, 071h, 0F4h
    db 001h, 00Fh, 0F9h, 067h, 040h, 00Fh, 0FDh, 067h, 050h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 026h, 00Fh, 06Fh, 06Fh, 020h, 00Fh, 0F9h, 0D9h
    db 00Fh, 0FDh, 05Fh, 050h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h
    db 050h, 00Fh, 0FDh, 067h, 060h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh
    db 0FDh, 0E5h, 00Fh, 07Fh, 066h, 010h, 00Fh, 06Fh, 06Fh, 030h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh
    db 060h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0F9h, 067h, 060h, 00Fh, 0FDh
    db 067h, 070h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 020h, 00Fh, 06Fh, 06Fh, 040h, 00Fh, 0F9h, 0D9h, 00Fh, 0FDh, 05Fh, 070h, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0E1h, 00Fh, 0F9h, 067h, 010h, 00Fh, 0F9h
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h
    db 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h
    db 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh
    db 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h, 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h
    db 000h, 00Fh, 0FDh, 0E2h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh
    db 0E5h, 00Fh, 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h
    db 030h, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh
    db 066h, 050h, 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh
    db 06Fh, 0AFh, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 08Bh
    db 045h, 0FCh, 083h, 0C7h, 008h, 083h, 0EEh, 008h, 083h, 0E8h, 004h, 00Fh, 06Fh, 006h, 00Fh, 06Fh
    db 04Eh, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 061h, 0C1h, 00Fh, 069h, 0E1h, 00Fh, 06Fh, 056h, 020h, 00Fh
    db 06Fh, 05Eh, 030h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh
    db 062h, 0C2h, 00Fh, 07Fh, 007h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h, 00Fh
    db 062h, 0C5h, 00Fh, 06Ah, 0E5h, 00Fh, 06Fh, 04Eh, 040h, 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh, 06Eh
    db 060h, 00Fh, 06Fh, 076h, 070h, 00Fh, 07Fh, 0CBh, 00Fh, 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh, 069h
    db 0DAh, 00Fh, 061h, 0EEh, 00Fh, 069h, 0FEh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h, 0CDh
    db 00Fh, 06Ah, 0D5h, 00Fh, 062h, 0DFh, 00Fh, 06Ah, 0F7h, 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h, 00Fh
    db 07Fh, 028h, 00Fh, 06Fh, 07Fh, 010h, 00Fh, 067h, 0FAh, 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h, 0C3h
    db 00Fh, 067h, 0E6h, 00Fh, 07Fh, 004h, 048h, 08Dh, 004h, 088h, 00Fh, 07Fh, 024h, 010h, 083h, 0C7h
    db 008h, 083h, 0C6h, 008h, 00Fh, 06Fh, 006h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 061h
    db 0C1h, 00Fh, 069h, 0E1h, 00Fh, 06Fh, 056h, 020h, 00Fh, 06Fh, 05Eh, 030h, 00Fh, 07Fh, 0D5h, 00Fh
    db 061h, 0D3h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 07Fh, 007h, 00Fh, 06Ah
    db 0CAh, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h, 00Fh, 062h, 0C5h, 00Fh, 06Ah, 0E5h, 00Fh, 06Fh
    db 04Eh, 040h, 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh, 06Eh, 060h, 00Fh, 06Fh, 076h, 070h, 00Fh, 07Fh
    db 0CBh, 00Fh, 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh, 069h, 0DAh, 00Fh, 061h, 0EEh, 00Fh, 069h, 0FEh
    db 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h, 0CDh, 00Fh, 06Ah, 0D5h, 00Fh, 062h, 0DFh, 00Fh
    db 06Ah, 0F7h, 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h, 00Fh, 07Fh, 028h, 00Fh, 06Fh, 07Fh, 010h, 00Fh
    db 067h, 0FAh, 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h, 0C3h, 00Fh, 067h, 0E6h, 00Fh, 07Fh, 004h, 048h
    db 08Dh, 004h, 088h, 00Fh, 07Fh, 024h, 010h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h, 00Fh, 0B7h, 07Dh
    db 0E4h, 00Fh, 0B7h, 075h, 0E6h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0E2h, 08Bh, 04Bh, 008h, 08Bh, 051h
    db 028h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0E0h, 08Bh, 045h, 0F4h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B6h
    db 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B4h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B2h, 08Dh, 014h, 082h, 003h
    db 0F7h, 00Fh, 0B7h, 07Dh, 0B0h, 003h, 0F7h, 001h, 032h, 08Bh, 049h, 028h, 00Fh, 0B7h, 055h, 0D6h
    db 08Dh, 044h, 081h, 004h, 00Fh, 0B7h, 04Dh, 0D4h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0D2h, 003h, 0D1h
    db 00Fh, 0B7h, 04Dh, 0D0h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A6h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A4h
    db 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A2h, 003h, 0D1h, 00Fh, 0B7h, 04Dh, 0A0h, 003h, 0D1h, 08Bh, 008h
    db 08Bh, 075h, 0F4h, 003h, 0CAh, 08Bh, 053h, 014h, 089h, 008h, 08Bh, 04Dh, 0F8h, 08Bh, 07Dh, 0FCh
    db 08Bh, 045h, 08Ch, 046h, 083h, 0C1h, 008h, 083h, 0C7h, 008h, 03Bh, 0F0h, 089h, 075h, 0F4h, 089h
    db 04Dh, 0F8h, 089h, 07Dh, 0FCh, 00Fh, 082h, 0D5h, 0F5h, 0FFh, 0FFh, 05Fh, 05Eh, 08Bh, 0E5h, 05Dh
    db 08Bh, 0E3h, 05Bh, 0C3h
?d_009b6d80@@YAXXZ ENDP
_TEXT$d00db6d80 ENDS
_TEXT SEGMENT

; retail @ 0x009BA790 size 11476
public ?d_009ba790@@YAXXZ
?d_009ba790@@YAXXZ PROC
    db 53h, 8Bh, 0DCh, 83h, 0ECh, 08h, 83h, 0E4h, 0F0h, 83h, 0C4h, 04h, 55h, 8Bh, 6Bh, 04h
    db 89h, 6Ch, 24h, 04h, 8Bh, 0ECh, 81h, 0ECh, 88h, 09h, 00h, 00h, 0B0h, 0FEh, 0B2h, 02h
    db 0B1h, 01h, 56h, 57h, 88h, 85h, 0F0h, 0F7h, 0FFh, 0FFh, 0C6h, 85h, 0F1h, 0F7h, 0FFh, 0FFh
    db 00h, 88h, 85h, 0F2h, 0F7h, 0FFh, 0FFh, 88h, 95h, 0F3h, 0F7h, 0FFh, 0FFh, 0C6h, 85h, 0F4h
    db 0F7h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0F5h, 0F7h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0F6h, 0F7h, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 0F7h, 0F7h, 0FFh, 0FFh, 88h, 95h, 0F8h, 0F7h, 0FFh, 0FFh, 88h, 8Dh
    db 0F9h, 0F7h, 0FFh, 0FFh, 88h, 85h, 0FAh, 0F7h, 0FFh, 0FFh, 88h, 95h, 0FBh, 0F7h, 0FFh, 0FFh
    db 88h, 8Dh, 0FCh, 0F7h, 0FFh, 0FFh, 0C6h, 85h, 0FDh, 0F7h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0FEh
    db 0F7h, 0FFh, 0FFh, 0FFh, 88h, 85h, 0FFh, 0F7h, 0FFh, 0FFh, 88h, 85h, 00h, 0F8h, 0FFh, 0FFh
    db 0C6h, 85h, 01h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 02h, 0F8h, 0FFh, 0FFh, 88h, 85h, 03h
    db 0F8h, 0FFh, 0FFh, 88h, 95h, 04h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 05h, 0F8h, 0FFh, 0FFh, 00h
    db 88h, 85h, 06h, 0F8h, 0FFh, 0FFh, 88h, 85h, 07h, 0F8h, 0FFh, 0FFh, 88h, 85h, 08h, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 09h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Ah, 0F8h, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 0Bh, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 0Ch, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0Dh
    db 0F8h, 0FFh, 0FFh, 88h, 85h, 0Eh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0Fh, 0F8h, 0FFh, 0FFh, 0C6h
    db 85h, 10h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 11h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 12h
    db 0F8h, 0FFh, 0FFh, 88h, 8Dh, 13h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 14h, 0F8h, 0FFh, 0FFh, 88h
    db 95h, 15h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 16h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 17h, 0F8h
    db 0FFh, 0FFh, 0FFh, 88h, 95h, 18h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 19h, 0F8h, 0FFh, 0FFh, 88h
    db 95h, 1Ah, 0F8h, 0FFh, 0FFh, 88h, 95h, 1Bh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 1Ch, 0F8h, 0FFh
    db 0FFh, 00h, 88h, 85h, 1Dh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 1Eh, 0F8h, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 1Fh, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 95h, 20h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 21h, 0F8h
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 22h, 0F8h, 0FFh, 0FFh, 88h, 95h, 23h, 0F8h, 0FFh, 0FFh, 88h
    db 95h, 24h, 0F8h, 0FFh, 0FFh, 88h, 95h, 25h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 26h, 0F8h, 0FFh
    db 0FFh, 0C6h, 85h, 27h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 28h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 29h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 95h, 2Ah, 0F8h, 0FFh, 0FFh, 88h, 85h, 2Bh, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 2Ch, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 2Dh, 0F8h, 0FFh, 0FFh, 88h
    db 8Dh, 2Eh, 0F8h, 0FFh, 0FFh, 88h, 85h, 2Fh, 0F8h, 0FFh, 0FFh, 88h, 85h, 30h, 0F8h, 0FFh
    db 0FFh, 88h, 95h, 31h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 32h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 33h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 34h, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 35h, 0F8h
    db 0FFh, 0FFh, 88h, 95h, 36h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 37h, 0F8h, 0FFh, 0FFh, 0C6h, 85h
    db 38h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 39h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 3Ah, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 3Bh, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 3Ch, 0F8h, 0FFh, 0FFh, 00h
    db 88h, 95h, 3Dh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 3Eh, 0F8h, 0FFh, 0FFh, 88h, 85h, 3Fh, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 40h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 41h, 0F8h, 0FFh, 0FFh, 0FFh
    db 88h, 8Dh, 42h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 43h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 44h, 0F8h
    db 0FFh, 0FFh, 00h, 0C6h, 85h, 45h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 46h, 0F8h, 0FFh, 0FFh
    db 0C6h, 85h, 47h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 48h, 0F8h, 0FFh, 0FFh, 00h, 88h, 95h
    db 49h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 4Ah, 0F8h, 0FFh, 0FFh, 00h, 88h, 95h, 4Bh, 0F8h, 0FFh
    db 0FFh, 88h, 8Dh, 4Ch, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 4Dh, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 4Eh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 4Fh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 50h, 0F8h, 0FFh, 0FFh
    db 00h, 88h, 85h, 51h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 52h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 53h
    db 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 54h, 0F8h, 0FFh, 0FFh, 88h, 95h, 55h, 0F8h, 0FFh, 0FFh
    db 88h, 85h, 56h, 0F8h, 0FFh, 0FFh, 88h, 95h, 57h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 58h, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 59h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 5Ah, 0F8h, 0FFh, 0FFh, 00h
    db 88h, 85h, 5Bh, 0F8h, 0FFh, 0FFh, 88h, 95h, 5Ch, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 5Dh, 0F8h
    db 0FFh, 0FFh, 88h, 85h, 5Eh, 0F8h, 0FFh, 0FFh, 88h, 95h, 5Fh, 0F8h, 0FFh, 0FFh, 88h, 95h
    db 60h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 61h, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 62h, 0F8h, 0FFh
    db 0FFh, 88h, 85h, 63h, 0F8h, 0FFh, 0FFh, 88h, 95h, 64h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 65h
    db 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 66h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 67h, 0F8h, 0FFh, 0FFh
    db 00h, 88h, 8Dh, 68h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 69h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 6Ah, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 6Bh, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 6Ch, 0F8h
    db 0FFh, 0FFh, 88h, 8Dh, 6Dh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 6Eh, 0F8h, 0FFh, 0FFh, 0C6h, 85h
    db 6Fh, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 70h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 71h, 0F8h, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 72h, 0F8h, 0FFh, 0FFh, 88h, 85h, 73h, 0F8h, 0FFh, 0FFh, 0C6h, 85h
    db 74h, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 75h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 76h, 0F8h, 0FFh
    db 0FFh, 00h, 88h, 85h, 77h, 0F8h, 0FFh, 0FFh, 88h, 95h, 78h, 0F8h, 0FFh, 0FFh, 88h, 95h
    db 79h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 7Ah, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 7Bh, 0F8h, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 7Ch, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 7Dh, 0F8h, 0FFh, 0FFh, 0FFh
    db 88h, 95h, 7Eh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 7Fh, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 80h
    db 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 81h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 95h, 82h, 0F8h, 0FFh
    db 0FFh, 0C6h, 85h, 83h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 84h, 0F8h, 0FFh, 0FFh, 0C6h, 85h
    db 85h, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 86h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 87h, 0F8h, 0FFh
    db 0FFh, 88h, 95h, 88h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 89h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 8Ah, 0F8h, 0FFh, 0FFh, 00h, 88h, 95h, 8Bh, 0F8h, 0FFh, 0FFh, 88h, 85h, 8Ch, 0F8h, 0FFh
    db 0FFh, 88h, 95h, 8Dh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 8Eh, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h
    db 8Fh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 90h, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 91h, 0F8h, 0FFh
    db 0FFh, 88h, 95h, 92h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 93h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 94h
    db 0F8h, 0FFh, 0FFh, 88h, 85h, 95h, 0F8h, 0FFh, 0FFh, 88h, 95h, 96h, 0F8h, 0FFh, 0FFh, 88h
    db 85h, 97h, 0F8h, 0FFh, 0FFh, 88h, 85h, 98h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 99h, 0F8h, 0FFh
    db 0FFh, 0C6h, 85h, 9Ah, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 95h, 9Bh, 0F8h, 0FFh, 0FFh, 0C6h, 85h
    db 9Ch, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 9Dh, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 9Eh, 0F8h
    db 0FFh, 0FFh, 88h, 8Dh, 9Fh, 0F8h, 0FFh, 0FFh, 88h, 95h, 0A0h, 0F8h, 0FFh, 0FFh, 88h, 8Dh
    db 0A1h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0A2h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0A3h, 0F8h, 0FFh, 0FFh
    db 0C6h, 85h, 0A4h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 0A5h, 0F8h, 0FFh, 0FFh, 88h, 85h, 0A6h
    db 0F8h, 0FFh, 0FFh, 88h, 85h, 0A7h, 0F8h, 0FFh, 0FFh, 88h, 95h, 0A8h, 0F8h, 0FFh, 0FFh, 88h
    db 95h, 0A9h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0AAh, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 0ABh, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 0ACh, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 0ADh, 0F8h, 0FFh, 0FFh, 88h
    db 85h, 0AEh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0AFh, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 0B0h, 0F8h
    db 0FFh, 0FFh, 88h, 8Dh, 0B1h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0B2h, 0F8h, 0FFh, 0FFh, 00h, 88h
    db 85h, 0B3h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0B4h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0B5h, 0F8h
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0B6h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0B7h, 0F8h, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 0B8h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0B9h, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 0BAh, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0BBh, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 0BCh, 0F8h
    db 0FFh, 0FFh, 88h, 85h, 0BDh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0BEh, 0F8h, 0FFh, 0FFh, 00h, 88h
    db 95h, 0BFh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0C0h, 0F8h, 0FFh, 0FFh, 88h, 95h, 0C1h, 0F8h, 0FFh
    db 0FFh, 88h, 85h, 0C2h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0C3h, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 0C4h, 0F8h, 0FFh, 0FFh, 88h, 95h, 0C5h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0C6h, 0F8h, 0FFh, 0FFh
    db 00h, 88h, 95h, 0C7h, 0F8h, 0FFh, 0FFh, 88h, 85h, 0C8h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0C9h
    db 0F8h, 0FFh, 0FFh, 88h, 85h, 0CAh, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0CBh, 0F8h, 0FFh, 0FFh, 00h
    db 88h, 95h, 0CCh, 0F8h, 0FFh, 0FFh, 88h, 85h, 0CDh, 0F8h, 0FFh, 0FFh, 88h, 95h, 0CEh, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 0CFh, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0D0h, 0F8h, 0FFh, 0FFh, 0FFh
    db 88h, 8Dh, 0D1h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0D2h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0D3h
    db 0F8h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0D4h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0D5h, 0F8h, 0FFh, 0FFh
    db 0C6h, 85h, 0D6h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0D7h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 0D8h, 0F8h, 0FFh, 0FFh, 00h, 88h, 8Dh, 0D9h, 0F8h, 0FFh, 0FFh, 88h, 95h, 0DAh, 0F8h, 0FFh
    db 0FFh, 88h, 95h, 0DBh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0DCh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0DDh
    db 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0DEh, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0DFh, 0F8h, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 0E0h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0E1h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0E2h
    db 0F8h, 0FFh, 0FFh, 00h, 88h, 95h, 0E3h, 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0E4h, 0F8h, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 0E5h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0E6h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0E7h
    db 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0E8h, 0F8h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0E9h, 0F8h, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 0EAh, 0F8h, 0FFh, 0FFh, 00h, 88h, 85h, 0EBh, 0F8h, 0FFh, 0FFh, 88h, 8Dh
    db 0ECh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0EDh, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0EEh, 0F8h, 0FFh, 0FFh
    db 88h, 8Dh, 0EFh, 0F8h, 0FFh, 0FFh, 88h, 95h, 0F0h, 0F8h, 0FFh, 0FFh, 88h, 85h, 0F1h, 0F8h
    db 0FFh, 0FFh, 0C6h, 85h, 0F2h, 0F8h, 0FFh, 0FFh, 00h, 88h, 95h, 0F3h, 0F8h, 0FFh, 0FFh, 88h
    db 95h, 0F4h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0F5h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0F6h, 0F8h, 0FFh
    db 0FFh, 88h, 85h, 0F7h, 0F8h, 0FFh, 0FFh, 88h, 8Dh, 0F8h, 0F8h, 0FFh, 0FFh, 88h, 95h, 0F9h
    db 0F8h, 0FFh, 0FFh, 0C6h, 85h, 0FAh, 0F8h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0FBh, 0F8h, 0FFh, 0FFh
    db 00h, 0C6h, 85h, 0FCh, 0F8h, 0FFh, 0FFh, 0FFh, 88h, 85h, 0FDh, 0F8h, 0FFh, 0FFh, 88h, 85h
    db 0FEh, 0F8h, 0FFh, 0FFh, 88h, 95h, 0FFh, 0F8h, 0FFh, 0FFh, 88h, 95h, 00h, 0F9h, 0FFh, 0FFh
    db 88h, 8Dh, 01h, 0F9h, 0FFh, 0FFh, 88h, 85h, 02h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 03h, 0F9h
    db 0FFh, 0FFh, 0FFh, 88h, 85h, 04h, 0F9h, 0FFh, 0FFh, 88h, 85h, 05h, 0F9h, 0FFh, 0FFh, 88h
    db 8Dh, 06h, 0F9h, 0FFh, 0FFh, 88h, 95h, 07h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 08h, 0F9h, 0FFh
    db 0FFh, 00h, 0C6h, 85h, 09h, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0Ah, 0F9h, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 0Bh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Ch, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 0Dh, 0F9h, 0FFh, 0FFh, 00h, 88h, 85h, 0Eh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0Fh, 0F9h, 0FFh
    db 0FFh, 0FFh, 88h, 8Dh, 10h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 11h, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 12h, 0F9h, 0FFh, 0FFh, 88h, 95h, 13h, 0F9h, 0FFh, 0FFh, 88h, 95h, 14h, 0F9h, 0FFh
    db 0FFh, 88h, 8Dh, 15h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 16h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h
    db 17h, 0F9h, 0FFh, 0FFh, 88h, 85h, 18h, 0F9h, 0FFh, 0FFh, 88h, 85h, 19h, 0F9h, 0FFh, 0FFh
    db 88h, 8Dh, 1Ah, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 1Bh, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 1Ch
    db 0F9h, 0FFh, 0FFh, 88h, 95h, 1Dh, 0F9h, 0FFh, 0FFh, 88h, 85h, 1Eh, 0F9h, 0FFh, 0FFh, 88h
    db 95h, 1Fh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 20h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 21h, 0F9h, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 22h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 23h, 0F9h, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 24h, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 25h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 26h
    db 0F9h, 0FFh, 0FFh, 0C6h, 85h, 27h, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 28h, 0F9h, 0FFh, 0FFh
    db 88h, 85h, 29h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 2Ah, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Bh
    db 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 2Ch, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 2Dh, 0F9h, 0FFh
    db 0FFh, 0C6h, 85h, 2Eh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Fh, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 8Dh, 30h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 31h, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 32h, 0F9h
    db 0FFh, 0FFh, 0C6h, 85h, 33h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 34h, 0F9h, 0FFh, 0FFh, 88h
    db 8Dh, 35h, 0F9h, 0FFh, 0FFh, 88h, 85h, 36h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 37h, 0F9h, 0FFh
    db 0FFh, 88h, 95h, 38h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 39h, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh
    db 3Ah, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 3Bh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 3Ch, 0F9h, 0FFh
    db 0FFh, 0FFh, 88h, 8Dh, 3Dh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 3Eh, 0F9h, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 3Fh, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 40h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 41h, 0F9h
    db 0FFh, 0FFh, 88h, 85h, 42h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 43h, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 85h, 44h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 45h, 0F9h, 0FFh, 0FFh, 88h, 95h, 46h, 0F9h, 0FFh
    db 0FFh, 88h, 8Dh, 47h, 0F9h, 0FFh, 0FFh, 88h, 85h, 48h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 49h
    db 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 4Ah, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 4Bh, 0F9h, 0FFh, 0FFh
    db 88h, 85h, 4Ch, 0F9h, 0FFh, 0FFh, 88h, 95h, 4Dh, 0F9h, 0FFh, 0FFh, 88h, 95h, 4Eh, 0F9h
    db 0FFh, 0FFh, 0C6h, 85h, 4Fh, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 50h, 0F9h, 0FFh, 0FFh, 88h
    db 95h, 51h, 0F9h, 0FFh, 0FFh, 88h, 85h, 52h, 0F9h, 0FFh, 0FFh, 88h, 85h, 53h, 0F9h, 0FFh
    db 0FFh, 88h, 8Dh, 54h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 55h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 56h
    db 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 57h, 0F9h, 0FFh, 0FFh, 88h, 85h, 58h, 0F9h, 0FFh, 0FFh
    db 88h, 8Dh, 59h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 5Ah, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 5Bh
    db 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 5Ch, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 5Dh, 0F9h, 0FFh
    db 0FFh, 88h, 95h, 5Eh, 0F9h, 0FFh, 0FFh, 88h, 95h, 5Fh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 60h
    db 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 61h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 62h, 0F9h, 0FFh, 0FFh
    db 88h, 95h, 63h, 0F9h, 0FFh, 0FFh, 88h, 85h, 64h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 65h, 0F9h
    db 0FFh, 0FFh, 0C6h, 85h, 66h, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 67h, 0F9h, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 68h, 0F9h, 0FFh, 0FFh, 88h, 95h, 69h, 0F9h, 0FFh, 0FFh, 88h, 85h, 6Ah, 0F9h
    db 0FFh, 0FFh, 0C6h, 85h, 6Bh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 6Ch, 0F9h, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 6Dh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 6Eh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 6Fh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 70h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 71h, 0F9h
    db 0FFh, 0FFh, 88h, 95h, 72h, 0F9h, 0FFh, 0FFh, 88h, 85h, 73h, 0F9h, 0FFh, 0FFh, 0C6h, 85h
    db 74h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 75h, 0F9h, 0FFh, 0FFh, 88h, 95h, 76h, 0F9h, 0FFh
    db 0FFh, 88h, 8Dh, 77h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 78h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 79h
    db 0F9h, 0FFh, 0FFh, 0C6h, 85h, 7Ah, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 7Bh, 0F9h, 0FFh, 0FFh
    db 0C6h, 85h, 7Ch, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 7Dh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 7Eh
    db 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 7Fh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 80h, 0F9h, 0FFh
    db 0FFh, 00h, 88h, 95h, 81h, 0F9h, 0FFh, 0FFh, 88h, 85h, 82h, 0F9h, 0FFh, 0FFh, 88h, 85h
    db 83h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 84h, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 85h, 0F9h, 0FFh
    db 0FFh, 00h, 88h, 85h, 86h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 87h, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 88h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 89h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 8Ah, 0F9h
    db 0FFh, 0FFh, 88h, 85h, 8Bh, 0F9h, 0FFh, 0FFh, 88h, 95h, 8Ch, 0F9h, 0FFh, 0FFh, 88h, 85h
    db 8Dh, 0F9h, 0FFh, 0FFh, 88h, 85h, 8Eh, 0F9h, 0FFh, 0FFh, 88h, 85h, 8Fh, 0F9h, 0FFh, 0FFh
    db 0C6h, 85h, 90h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 91h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 92h
    db 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 93h, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 94h, 0F9h, 0FFh
    db 0FFh, 88h, 95h, 95h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 96h, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h
    db 97h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 98h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 99h, 0F9h, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 9Ah, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 9Bh, 0F9h, 0FFh, 0FFh, 0C6h, 85h
    db 9Ch, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 9Dh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 9Eh, 0F9h, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 9Fh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0A0h, 0F9h, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 0A1h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0A2h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0A3h
    db 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0A4h, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 0A5h, 0F9h, 0FFh, 0FFh
    db 88h, 85h, 0A6h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0A7h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0A8h, 0F9h
    db 0FFh, 0FFh, 88h, 8Dh, 0A9h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0AAh, 0F9h, 0FFh, 0FFh, 00h, 88h
    db 85h, 0ABh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0ACh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0ADh, 0F9h
    db 0FFh, 0FFh, 0FFh, 88h, 85h, 0AEh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0AFh, 0F9h, 0FFh, 0FFh, 00h
    db 88h, 85h, 0B0h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0B1h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0B2h, 0F9h
    db 0FFh, 0FFh, 88h, 85h, 0B3h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0B4h, 0F9h, 0FFh, 0FFh, 88h, 8Dh
    db 0B5h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0B6h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0B7h, 0F9h, 0FFh, 0FFh
    db 0C6h, 85h, 0B8h, 0F9h, 0FFh, 0FFh, 00h, 88h, 8Dh, 0B9h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0BAh
    db 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0BBh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0BCh, 0F9h, 0FFh, 0FFh, 88h
    db 8Dh, 0BDh, 0F9h, 0FFh, 0FFh, 88h, 85h, 0BEh, 0F9h, 0FFh, 0FFh, 88h, 95h, 0BFh, 0F9h, 0FFh
    db 0FFh, 88h, 8Dh, 0C0h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0C1h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0C2h
    db 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0C3h, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 0C4h, 0F9h, 0FFh, 0FFh
    db 88h, 85h, 0C5h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0C6h, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 85h, 0C7h
    db 0F9h, 0FFh, 0FFh, 88h, 95h, 0C8h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0C9h, 0F9h, 0FFh, 0FFh, 0C6h
    db 85h, 0CAh, 0F9h, 0FFh, 0FFh, 0FFh, 88h, 95h, 0CBh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0CCh, 0F9h
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0CDh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0CEh, 0F9h, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 0CFh, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0D0h, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0D1h
    db 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 0D2h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0D3h, 0F9h, 0FFh, 0FFh
    db 88h, 95h, 0D4h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0D5h, 0F9h, 0FFh, 0FFh, 00h, 88h, 85h, 0D6h
    db 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0D7h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0D8h, 0F9h, 0FFh, 0FFh, 88h
    db 95h, 0D9h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0DAh, 0F9h, 0FFh, 0FFh, 88h, 95h, 0DBh, 0F9h, 0FFh
    db 0FFh, 0C6h, 85h, 0DCh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0DDh, 0F9h, 0FFh, 0FFh, 00h, 88h
    db 85h, 0DEh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0DFh, 0F9h, 0FFh, 0FFh, 88h, 85h, 0E0h, 0F9h, 0FFh
    db 0FFh, 0C6h, 85h, 0E1h, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0E2h, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 0E3h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0E4h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0E5h, 0F9h, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 0E6h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0E7h, 0F9h, 0FFh, 0FFh, 0FFh, 88h
    db 85h, 0E8h, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0E9h, 0F9h, 0FFh, 0FFh, 88h, 95h, 0EAh, 0F9h, 0FFh
    db 0FFh, 88h, 95h, 0EBh, 0F9h, 0FFh, 0FFh, 88h, 85h, 0ECh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0EDh
    db 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0EEh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 0EFh, 0F9h, 0FFh, 0FFh, 88h
    db 95h, 0F0h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0F1h, 0F9h, 0FFh, 0FFh, 00h, 88h, 95h, 0F2h, 0F9h
    db 0FFh, 0FFh, 88h, 8Dh, 0F3h, 0F9h, 0FFh, 0FFh, 88h, 85h, 0F4h, 0F9h, 0FFh, 0FFh, 88h, 8Dh
    db 0F5h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0F6h, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0F7h, 0F9h, 0FFh
    db 0FFh, 00h, 88h, 95h, 0F8h, 0F9h, 0FFh, 0FFh, 0C6h, 85h, 0F9h, 0F9h, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 0FAh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0FBh, 0F9h, 0FFh, 0FFh, 00h, 0C6h, 85h, 0FCh
    db 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0FDh, 0F9h, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0FEh, 0F9h, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 0FFh, 0F9h, 0FFh, 0FFh, 88h, 8Dh, 00h, 0FAh, 0FFh, 0FFh, 88h, 85h
    db 01h, 0FAh, 0FFh, 0FFh, 88h, 85h, 02h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 03h, 0FAh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 04h, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 05h, 0FAh, 0FFh, 0FFh, 88h, 85h
    db 06h, 0FAh, 0FFh, 0FFh, 88h, 85h, 07h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 08h, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 09h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0Ah, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0Bh
    db 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0Ch, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0Dh, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 0Eh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0Fh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 10h
    db 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 11h, 0FAh, 0FFh, 0FFh, 88h, 95h, 12h, 0FAh, 0FFh, 0FFh
    db 88h, 95h, 13h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 14h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 15h
    db 0FAh, 0FFh, 0FFh, 88h, 85h, 16h, 0FAh, 0FFh, 0FFh, 88h, 95h, 17h, 0FAh, 0FFh, 0FFh, 0C6h
    db 85h, 18h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 19h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 1Ah
    db 0FAh, 0FFh, 0FFh, 88h, 8Dh, 1Bh, 0FAh, 0FFh, 0FFh, 88h, 85h, 1Ch, 0FAh, 0FFh, 0FFh, 0C6h
    db 85h, 1Dh, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 1Eh, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 1Fh
    db 0FAh, 0FFh, 0FFh, 00h, 88h, 95h, 20h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 21h, 0FAh, 0FFh, 0FFh
    db 88h, 8Dh, 22h, 0FAh, 0FFh, 0FFh, 88h, 95h, 23h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 24h, 0FAh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 25h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 26h, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 27h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 28h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 29h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Ah, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 2Bh, 0FAh
    db 0FFh, 0FFh, 88h, 8Dh, 2Ch, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 2Dh, 0FAh, 0FFh, 0FFh, 88h, 8Dh
    db 2Eh, 0FAh, 0FFh, 0FFh, 88h, 85h, 2Fh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 30h, 0FAh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 31h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 32h, 0FAh, 0FFh, 0FFh, 88h, 95h
    db 33h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 34h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 35h, 0FAh, 0FFh
    db 0FFh, 00h, 88h, 85h, 36h, 0FAh, 0FFh, 0FFh, 88h, 95h, 37h, 0FAh, 0FFh, 0FFh, 0C6h, 85h
    db 38h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 39h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 3Ah, 0FAh
    db 0FFh, 0FFh, 0C6h, 85h, 3Bh, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 3Ch, 0FAh, 0FFh, 0FFh, 88h
    db 85h, 3Dh, 0FAh, 0FFh, 0FFh, 88h, 85h, 3Eh, 0FAh, 0FFh, 0FFh, 88h, 85h, 3Fh, 0FAh, 0FFh
    db 0FFh, 88h, 85h, 40h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 41h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 42h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 43h, 0FAh, 0FFh, 0FFh, 88h, 85h, 44h, 0FAh, 0FFh
    db 0FFh, 0C6h, 85h, 45h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 85h, 46h, 0FAh, 0FFh, 0FFh, 88h, 8Dh
    db 47h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 48h, 0FAh, 0FFh, 0FFh, 88h, 85h, 49h, 0FAh, 0FFh, 0FFh
    db 88h, 8Dh, 4Ah, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 4Bh, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 4Ch, 0FAh
    db 0FFh, 0FFh, 0C6h, 85h, 4Dh, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 4Eh, 0FAh, 0FFh, 0FFh, 0C6h
    db 85h, 4Fh, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 50h, 0FAh, 0FFh, 0FFh, 88h, 95h, 51h, 0FAh
    db 0FFh, 0FFh, 0C6h, 85h, 52h, 0FAh, 0FFh, 0FFh, 00h, 88h, 95h, 53h, 0FAh, 0FFh, 0FFh, 88h
    db 8Dh, 54h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 55h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 56h, 0FAh
    db 0FFh, 0FFh, 88h, 8Dh, 57h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 58h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 59h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 85h, 5Ah, 0FAh, 0FFh, 0FFh, 88h, 95h, 5Bh, 0FAh
    db 0FFh, 0FFh, 88h, 85h, 5Ch, 0FAh, 0FFh, 0FFh, 88h, 85h, 5Dh, 0FAh, 0FFh, 0FFh, 0C6h, 85h
    db 5Eh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 5Fh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 60h, 0FAh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 61h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 62h, 0FAh, 0FFh, 0FFh, 00h
    db 88h, 85h, 63h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 64h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 65h
    db 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 66h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 67h, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 68h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 69h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h
    db 6Ah, 0FAh, 0FFh, 0FFh, 88h, 95h, 6Bh, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 6Ch, 0FAh, 0FFh, 0FFh
    db 88h, 95h, 6Dh, 0FAh, 0FFh, 0FFh, 88h, 85h, 6Eh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 6Fh, 0FAh
    db 0FFh, 0FFh, 00h, 88h, 95h, 70h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 71h, 0FAh, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 72h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 73h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 74h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 75h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 76h, 0FAh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 77h, 0FAh, 0FFh, 0FFh, 88h, 85h, 78h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 79h
    db 0FAh, 0FFh, 0FFh, 00h, 88h, 95h, 7Ah, 0FAh, 0FFh, 0FFh, 88h, 95h, 7Bh, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 7Ch, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 7Dh, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 7Eh
    db 0FAh, 0FFh, 0FFh, 88h, 95h, 7Fh, 0FAh, 0FFh, 0FFh, 88h, 95h, 80h, 0FAh, 0FFh, 0FFh, 0C6h
    db 85h, 81h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 82h, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 83h
    db 0FAh, 0FFh, 0FFh, 88h, 8Dh, 84h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 85h, 0FAh, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 86h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 87h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 88h, 0FAh, 0FFh, 0FFh, 00h, 88h, 95h, 89h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 8Ah, 0FAh, 0FFh
    db 0FFh, 0C6h, 85h, 8Bh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 85h, 8Ch, 0FAh, 0FFh, 0FFh, 0C6h, 85h
    db 8Dh, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 8Eh, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 8Fh, 0FAh
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 90h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 91h, 0FAh, 0FFh, 0FFh, 0FFh
    db 88h, 95h, 92h, 0FAh, 0FFh, 0FFh, 88h, 85h, 93h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 94h, 0FAh
    db 0FFh, 0FFh, 88h, 8Dh, 95h, 0FAh, 0FFh, 0FFh, 88h, 95h, 96h, 0FAh, 0FFh, 0FFh, 88h, 85h
    db 97h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 98h, 0FAh, 0FFh, 0FFh, 00h, 88h, 95h, 99h, 0FAh, 0FFh
    db 0FFh, 88h, 8Dh, 9Ah, 0FAh, 0FFh, 0FFh, 88h, 95h, 9Bh, 0FAh, 0FFh, 0FFh, 88h, 85h, 9Ch
    db 0FAh, 0FFh, 0FFh, 88h, 95h, 9Dh, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 9Eh, 0FAh, 0FFh, 0FFh, 88h
    db 95h, 9Fh, 0FAh, 0FFh, 0FFh, 88h, 95h, 0A0h, 0FAh, 0FFh, 0FFh, 88h, 95h, 0A1h, 0FAh, 0FFh
    db 0FFh, 88h, 8Dh, 0A2h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0A3h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0A4h
    db 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0A5h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0A6h, 0FAh, 0FFh, 0FFh
    db 0FFh, 88h, 8Dh, 0A7h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0A8h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0A9h
    db 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0AAh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0ABh, 0FAh, 0FFh, 0FFh, 00h
    db 88h, 85h, 0ACh, 0FAh, 0FFh, 0FFh, 88h, 95h, 0ADh, 0FAh, 0FFh, 0FFh, 88h, 95h, 0AEh, 0FAh
    db 0FFh, 0FFh, 88h, 85h, 0AFh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0B0h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 0B1h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0B2h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0B3h
    db 0FAh, 0FFh, 0FFh, 88h, 85h, 0B4h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0B5h, 0FAh, 0FFh, 0FFh, 88h
    db 95h, 0B6h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0B7h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0B8h, 0FAh, 0FFh
    db 0FFh, 88h, 8Dh, 0B9h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0BAh, 0FAh, 0FFh, 0FFh, 88h, 85h, 0BBh
    db 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0BCh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0BDh, 0FAh, 0FFh, 0FFh
    db 88h, 95h, 0BEh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0BFh, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0C0h
    db 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0C1h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0C2h, 0FAh, 0FFh, 0FFh
    db 0FFh, 88h, 8Dh, 0C3h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0C4h, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 0C5h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0C6h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0C7h, 0FAh, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 0C8h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0C9h, 0FAh, 0FFh, 0FFh, 88h, 85h
    db 0CAh, 0FAh, 0FFh, 0FFh, 88h, 85h, 0CBh, 0FAh, 0FFh, 0FFh, 88h, 85h, 0CCh, 0FAh, 0FFh, 0FFh
    db 0C6h, 85h, 0CDh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0CEh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0CFh
    db 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0D0h, 0FAh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0D1h, 0FAh, 0FFh
    db 0FFh, 00h, 88h, 85h, 0D2h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0D3h, 0FAh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 0D4h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0D5h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0D6h, 0FAh
    db 0FFh, 0FFh, 88h, 95h, 0D7h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0D8h, 0FAh, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 0D9h, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 0DAh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0DBh, 0FAh
    db 0FFh, 0FFh, 00h, 0C6h, 85h, 0DCh, 0FAh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0DDh, 0FAh, 0FFh, 0FFh
    db 00h, 88h, 95h, 0DEh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0DFh, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h
    db 0E0h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0E1h, 0FAh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0E2h, 0FAh, 0FFh
    db 0FFh, 88h, 8Dh, 0E3h, 0FAh, 0FFh, 0FFh, 88h, 95h, 0E4h, 0FAh, 0FFh, 0FFh, 88h, 95h, 0E5h
    db 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0E6h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0E7h, 0FAh, 0FFh, 0FFh
    db 88h, 8Dh, 0E8h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0E9h, 0FAh, 0FFh, 0FFh, 88h, 95h, 0EAh, 0FAh
    db 0FFh, 0FFh, 88h, 8Dh, 0EBh, 0FAh, 0FFh, 0FFh, 88h, 95h, 0ECh, 0FAh, 0FFh, 0FFh, 88h, 95h
    db 0EDh, 0FAh, 0FFh, 0FFh, 88h, 95h, 0EEh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0EFh, 0FAh, 0FFh, 0FFh
    db 00h, 0C6h, 85h, 0F0h, 0FAh, 0FFh, 0FFh, 00h, 88h, 85h, 0F1h, 0FAh, 0FFh, 0FFh, 0C6h, 85h
    db 0F2h, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0F3h, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0F4h, 0FAh, 0FFh
    db 0FFh, 00h, 88h, 85h, 0F5h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0F6h, 0FAh, 0FFh, 0FFh, 88h, 8Dh
    db 0F7h, 0FAh, 0FFh, 0FFh, 88h, 8Dh, 0F8h, 0FAh, 0FFh, 0FFh, 88h, 85h, 0F9h, 0FAh, 0FFh, 0FFh
    db 88h, 85h, 0FAh, 0FAh, 0FFh, 0FFh, 0C6h, 85h, 0FBh, 0FAh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0FCh
    db 0FAh, 0FFh, 0FFh, 88h, 95h, 0FDh, 0FAh, 0FFh, 0FFh, 88h, 85h, 0FEh, 0FAh, 0FFh, 0FFh, 88h
    db 85h, 0FFh, 0FAh, 0FFh, 0FFh, 88h, 85h, 00h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 01h, 0FBh, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 02h, 0FBh, 0FFh, 0FFh, 88h, 95h, 03h, 0FBh, 0FFh, 0FFh, 88h, 8Dh
    db 04h, 0FBh, 0FFh, 0FFh, 88h, 85h, 05h, 0FBh, 0FFh, 0FFh, 88h, 95h, 06h, 0FBh, 0FFh, 0FFh
    db 88h, 8Dh, 07h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 08h, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 09h
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0Ah, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Bh, 0FBh, 0FFh, 0FFh
    db 0FFh, 88h, 8Dh, 0Ch, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0Dh, 0FBh, 0FFh, 0FFh, 88h, 85h, 0Eh
    db 0FBh, 0FFh, 0FFh, 88h, 95h, 0Fh, 0FBh, 0FFh, 0FFh, 88h, 85h, 10h, 0FBh, 0FFh, 0FFh, 88h
    db 8Dh, 11h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 12h, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 13h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 14h, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 15h, 0FBh, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 16h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 17h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 18h
    db 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 19h, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 1Ah, 0FBh, 0FFh
    db 0FFh, 88h, 85h, 1Bh, 0FBh, 0FFh, 0FFh, 88h, 95h, 1Ch, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 1Dh
    db 0FBh, 0FFh, 0FFh, 88h, 85h, 1Eh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 1Fh, 0FBh, 0FFh, 0FFh, 00h
    db 88h, 8Dh, 20h, 0FBh, 0FFh, 0FFh, 88h, 95h, 21h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 22h, 0FBh
    db 0FFh, 0FFh, 88h, 8Dh, 23h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 24h, 0FBh, 0FFh, 0FFh, 88h, 95h
    db 25h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 26h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 27h, 0FBh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 28h, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 29h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 2Ah, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 2Bh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 2Ch, 0FBh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 2Dh, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Eh, 0FBh, 0FFh, 0FFh
    db 00h, 88h, 95h, 2Fh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 30h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 31h
    db 0FBh, 0FFh, 0FFh, 88h, 8Dh, 32h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 33h, 0FBh, 0FFh, 0FFh, 00h
    db 88h, 8Dh, 34h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 35h, 0FBh, 0FFh, 0FFh, 88h, 95h, 36h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 37h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 38h, 0FBh, 0FFh, 0FFh, 88h
    db 95h, 39h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 3Ah, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 3Bh, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 3Ch, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 3Dh, 0FBh, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 3Eh, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 3Fh, 0FBh, 0FFh, 0FFh, 88h, 95h, 40h
    db 0FBh, 0FFh, 0FFh, 88h, 85h, 41h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 42h, 0FBh, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 43h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 44h, 0FBh, 0FFh, 0FFh, 88h, 95h, 45h
    db 0FBh, 0FFh, 0FFh, 88h, 8Dh, 46h, 0FBh, 0FFh, 0FFh, 88h, 85h, 47h, 0FBh, 0FFh, 0FFh, 88h
    db 8Dh, 48h, 0FBh, 0FFh, 0FFh, 88h, 85h, 49h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 4Ah, 0FBh, 0FFh
    db 0FFh, 00h, 0C6h, 85h, 4Bh, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 4Ch, 0FBh, 0FFh, 0FFh, 00h
    db 88h, 85h, 4Dh, 0FBh, 0FFh, 0FFh, 88h, 95h, 4Eh, 0FBh, 0FFh, 0FFh, 88h, 85h, 4Fh, 0FBh
    db 0FFh, 0FFh, 88h, 8Dh, 50h, 0FBh, 0FFh, 0FFh, 88h, 85h, 51h, 0FBh, 0FFh, 0FFh, 88h, 85h
    db 52h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 53h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 54h, 0FBh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 55h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 56h, 0FBh, 0FFh, 0FFh, 0C6h, 85h
    db 57h, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 58h, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 59h, 0FBh
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 5Ah, 0FBh, 0FFh, 0FFh, 88h, 85h, 5Bh, 0FBh, 0FFh, 0FFh, 0C6h
    db 85h, 5Ch, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 5Dh, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 5Eh
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 5Fh, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 60h, 0FBh, 0FFh, 0FFh
    db 0C6h, 85h, 61h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 62h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 63h, 0FBh, 0FFh, 0FFh, 88h, 95h, 64h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 65h, 0FBh, 0FFh, 0FFh
    db 88h, 95h, 66h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 67h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 68h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 69h, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 6Ah, 0FBh, 0FFh, 0FFh, 88h
    db 8Dh, 6Bh, 0FBh, 0FFh, 0FFh, 88h, 95h, 6Ch, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 6Dh, 0FBh, 0FFh
    db 0FFh, 00h, 0C6h, 85h, 6Eh, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 85h, 6Fh, 0FBh, 0FFh, 0FFh, 88h
    db 95h, 70h, 0FBh, 0FFh, 0FFh, 88h, 95h, 71h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 72h, 0FBh, 0FFh
    db 0FFh, 00h, 88h, 85h, 73h, 0FBh, 0FFh, 0FFh, 88h, 95h, 74h, 0FBh, 0FFh, 0FFh, 88h, 8Dh
    db 75h, 0FBh, 0FFh, 0FFh, 88h, 85h, 76h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 77h, 0FBh, 0FFh, 0FFh
    db 00h, 88h, 95h, 78h, 0FBh, 0FFh, 0FFh, 88h, 85h, 79h, 0FBh, 0FFh, 0FFh, 88h, 85h, 7Ah
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 7Bh, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 85h, 7Ch, 0FBh, 0FFh, 0FFh
    db 0C6h, 85h, 7Dh, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 7Eh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 7Fh
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 80h, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 81h, 0FBh, 0FFh, 0FFh
    db 88h, 8Dh, 82h, 0FBh, 0FFh, 0FFh, 88h, 95h, 83h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 84h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 85h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 95h, 86h, 0FBh, 0FFh, 0FFh, 0C6h
    db 85h, 87h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 95h, 88h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 89h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 8Ah, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 85h, 8Bh, 0FBh, 0FFh, 0FFh, 0C6h
    db 85h, 8Ch, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 85h, 8Dh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 8Eh, 0FBh
    db 0FFh, 0FFh, 00h, 88h, 85h, 8Fh, 0FBh, 0FFh, 0FFh, 88h, 95h, 90h, 0FBh, 0FFh, 0FFh, 88h
    db 85h, 91h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 92h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 93h, 0FBh
    db 0FFh, 0FFh, 0FFh, 88h, 85h, 94h, 0FBh, 0FFh, 0FFh, 88h, 85h, 95h, 0FBh, 0FFh, 0FFh, 88h
    db 85h, 96h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 97h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 98h, 0FBh, 0FFh
    db 0FFh, 88h, 95h, 99h, 0FBh, 0FFh, 0FFh, 88h, 85h, 9Ah, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 9Bh
    db 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 9Ch, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 9Dh, 0FBh, 0FFh
    db 0FFh, 0C6h, 85h, 9Eh, 0FBh, 0FFh, 0FFh, 00h, 0C6h, 85h, 9Fh, 0FBh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 0A0h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0A1h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0A2h, 0FBh
    db 0FFh, 0FFh, 00h, 88h, 85h, 0A3h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0A4h, 0FBh, 0FFh, 0FFh, 88h
    db 95h, 0A5h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0A6h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0A7h, 0FBh, 0FFh
    db 0FFh, 0C6h, 85h, 0A8h, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0A9h, 0FBh, 0FFh, 0FFh, 88h, 8Dh
    db 0AAh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0ABh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0ACh, 0FBh, 0FFh, 0FFh
    db 0FFh, 88h, 95h, 0ADh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0AEh, 0FBh, 0FFh, 0FFh, 88h, 85h, 0AFh
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0B0h, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 0B1h, 0FBh, 0FFh, 0FFh
    db 0C6h, 85h, 0B2h, 0FBh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0B3h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0B4h
    db 0FBh, 0FFh, 0FFh, 88h, 85h, 0B5h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0B6h, 0FBh, 0FFh, 0FFh, 0C6h
    db 85h, 0B7h, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 0B8h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0B9h, 0FBh
    db 0FFh, 0FFh, 88h, 8Dh, 0BAh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0BBh, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 0BCh, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0BDh, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 0BEh
    db 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0BFh, 0FBh, 0FFh, 0FFh, 88h, 85h, 0C0h, 0FBh, 0FFh, 0FFh, 88h
    db 8Dh, 0C1h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0C2h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0C3h, 0FBh, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 0C4h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0C5h, 0FBh, 0FFh, 0FFh, 88h, 8Dh
    db 0C6h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0C7h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0C8h, 0FBh, 0FFh, 0FFh
    db 0FFh, 88h, 8Dh, 0C9h, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0CAh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0CBh
    db 0FBh, 0FFh, 0FFh, 00h, 88h, 95h, 0CCh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0CDh, 0FBh, 0FFh, 0FFh
    db 0C6h, 85h, 0CEh, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0CFh, 0FBh, 0FFh, 0FFh, 00h, 88h, 95h
    db 0D0h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0D1h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0D2h, 0FBh, 0FFh, 0FFh
    db 88h, 85h, 0D3h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0D4h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0D5h, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 0D6h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0D7h, 0FBh, 0FFh, 0FFh, 0FFh
    db 88h, 95h, 0D8h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0D9h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0DAh, 0FBh
    db 0FFh, 0FFh, 0C6h, 85h, 0DBh, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0DCh, 0FBh, 0FFh, 0FFh, 0C6h
    db 85h, 0DDh, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0DEh, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0DFh
    db 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0E0h, 0FBh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0E1h, 0FBh, 0FFh
    db 0FFh, 88h, 95h, 0E2h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0E3h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0E4h
    db 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0E5h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0E6h, 0FBh, 0FFh, 0FFh, 88h
    db 85h, 0E7h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0E8h, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0E9h, 0FBh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 0EAh, 0FBh, 0FFh, 0FFh, 00h, 88h, 85h, 0EBh, 0FBh, 0FFh, 0FFh, 88h
    db 95h, 0ECh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0EDh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0EEh, 0FBh, 0FFh
    db 0FFh, 00h, 88h, 95h, 0EFh, 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0F0h, 0FBh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 0F1h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0F2h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0F3h, 0FBh, 0FFh
    db 0FFh, 88h, 95h, 0F4h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0F5h, 0FBh, 0FFh, 0FFh, 88h, 85h, 0F6h
    db 0FBh, 0FFh, 0FFh, 0C6h, 85h, 0F7h, 0FBh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0F8h, 0FBh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 0F9h, 0FBh, 0FFh, 0FFh, 88h, 95h, 0FAh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0FBh
    db 0FBh, 0FFh, 0FFh, 88h, 8Dh, 0FCh, 0FBh, 0FFh, 0FFh, 88h, 85h, 0FDh, 0FBh, 0FFh, 0FFh, 88h
    db 8Dh, 0FEh, 0FBh, 0FFh, 0FFh, 88h, 95h, 0FFh, 0FBh, 0FFh, 0FFh, 88h, 8Dh, 00h, 0FCh, 0FFh
    db 0FFh, 88h, 95h, 01h, 0FCh, 0FFh, 0FFh, 88h, 85h, 02h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 03h
    db 0FCh, 0FFh, 0FFh, 0C6h, 85h, 04h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 05h, 0FCh, 0FFh, 0FFh
    db 88h, 95h, 06h, 0FCh, 0FFh, 0FFh, 88h, 95h, 07h, 0FCh, 0FFh, 0FFh, 88h, 85h, 08h, 0FCh
    db 0FFh, 0FFh, 88h, 8Dh, 09h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0Ah, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 85h, 0Bh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0Ch, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Dh, 0FCh
    db 0FFh, 0FFh, 00h, 88h, 85h, 0Eh, 0FCh, 0FFh, 0FFh, 88h, 95h, 0Fh, 0FCh, 0FFh, 0FFh, 0C6h
    db 85h, 10h, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 11h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 12h
    db 0FCh, 0FFh, 0FFh, 88h, 95h, 13h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 14h, 0FCh, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 15h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 16h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 17h, 0FCh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 18h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 19h, 0FCh, 0FFh, 0FFh
    db 88h, 95h, 1Ah, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 1Bh, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 1Ch
    db 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 1Dh, 0FCh, 0FFh, 0FFh, 88h, 95h, 1Eh, 0FCh, 0FFh, 0FFh
    db 88h, 8Dh, 1Fh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 20h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 21h
    db 0FCh, 0FFh, 0FFh, 0C6h, 85h, 22h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 23h, 0FCh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 24h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 25h, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 26h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 85h, 27h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 28h, 0FCh, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 29h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 2Ah, 0FCh, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 2Bh, 0FCh, 0FFh, 0FFh, 88h, 85h, 2Ch, 0FCh, 0FFh, 0FFh, 88h, 95h, 2Dh, 0FCh, 0FFh
    db 0FFh, 88h, 95h, 2Eh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 2Fh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h
    db 30h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 31h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 32h, 0FCh, 0FFh
    db 0FFh, 00h, 88h, 8Dh, 33h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 34h, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 85h, 35h, 0FCh, 0FFh, 0FFh, 88h, 95h, 36h, 0FCh, 0FFh, 0FFh, 88h, 85h, 37h, 0FCh, 0FFh
    db 0FFh, 0C6h, 85h, 38h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 39h, 0FCh, 0FFh, 0FFh, 0FFh, 88h
    db 8Dh, 3Ah, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 3Bh, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 3Ch, 0FCh
    db 0FFh, 0FFh, 88h, 8Dh, 3Dh, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 3Eh, 0FCh, 0FFh, 0FFh, 0C6h, 85h
    db 3Fh, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 40h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 41h, 0FCh, 0FFh
    db 0FFh, 88h, 85h, 42h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 43h, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h
    db 44h, 0FCh, 0FFh, 0FFh, 88h, 85h, 45h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 46h, 0FCh, 0FFh, 0FFh
    db 0C6h, 85h, 47h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 48h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 49h
    db 0FCh, 0FFh, 0FFh, 00h, 88h, 8Dh, 4Ah, 0FCh, 0FFh, 0FFh, 88h, 85h, 4Bh, 0FCh, 0FFh, 0FFh
    db 88h, 8Dh, 4Ch, 0FCh, 0FFh, 0FFh, 88h, 85h, 4Dh, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 4Eh, 0FCh
    db 0FFh, 0FFh, 88h, 95h, 4Fh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 50h, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 51h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 52h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 53h, 0FCh
    db 0FFh, 0FFh, 88h, 8Dh, 54h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 55h, 0FCh, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 56h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 57h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 58h, 0FCh
    db 0FFh, 0FFh, 00h, 88h, 8Dh, 59h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 5Ah, 0FCh, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 5Bh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 5Ch, 0FCh, 0FFh, 0FFh, 00h, 88h, 8Dh, 5Dh
    db 0FCh, 0FFh, 0FFh, 0C6h, 85h, 5Eh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 5Fh, 0FCh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 60h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 61h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 62h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 63h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 64h, 0FCh, 0FFh
    db 0FFh, 00h, 88h, 95h, 65h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 66h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 67h, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h, 68h, 0FCh, 0FFh, 0FFh, 88h, 95h, 69h, 0FCh
    db 0FFh, 0FFh, 88h, 95h, 6Ah, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 6Bh, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 6Ch, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 6Dh, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 6Eh, 0FCh
    db 0FFh, 0FFh, 0C6h, 85h, 6Fh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 70h, 0FCh, 0FFh, 0FFh, 00h
    db 88h, 85h, 71h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 72h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 73h
    db 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 74h, 0FCh, 0FFh, 0FFh, 88h, 95h, 75h, 0FCh, 0FFh, 0FFh
    db 88h, 95h, 76h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 77h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 78h, 0FCh
    db 0FFh, 0FFh, 00h, 88h, 85h, 79h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 7Ah, 0FCh, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 7Bh, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 7Ch, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h
    db 7Dh, 0FCh, 0FFh, 0FFh, 88h, 95h, 7Eh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 7Fh, 0FCh, 0FFh, 0FFh
    db 0FFh, 88h, 8Dh, 80h, 0FCh, 0FFh, 0FFh, 88h, 95h, 81h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 82h
    db 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 83h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 84h, 0FCh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 85h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 86h, 0FCh, 0FFh, 0FFh, 0C6h
    db 85h, 87h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 88h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 89h
    db 0FCh, 0FFh, 0FFh, 88h, 95h, 8Ah, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 8Bh, 0FCh, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 8Ch, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 8Dh, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 8Eh
    db 0FCh, 0FFh, 0FFh, 0C6h, 85h, 8Fh, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h, 90h, 0FCh, 0FFh, 0FFh
    db 88h, 95h, 91h, 0FCh, 0FFh, 0FFh, 88h, 85h, 92h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 93h, 0FCh
    db 0FFh, 0FFh, 0C6h, 85h, 94h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 85h, 95h, 0FCh, 0FFh, 0FFh, 88h
    db 85h, 96h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 97h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 98h, 0FCh
    db 0FFh, 0FFh, 00h, 88h, 95h, 99h, 0FCh, 0FFh, 0FFh, 88h, 85h, 9Ah, 0FCh, 0FFh, 0FFh, 88h
    db 85h, 9Bh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 9Ch, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 9Dh, 0FCh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 9Eh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 9Fh, 0FCh, 0FFh, 0FFh
    db 00h, 0C6h, 85h, 0A0h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 0A1h, 0FCh, 0FFh, 0FFh, 88h, 8Dh
    db 0A2h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0A3h, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0A4h, 0FCh, 0FFh
    db 0FFh, 00h, 0C6h, 85h, 0A5h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 0A6h, 0FCh, 0FFh, 0FFh, 0C6h
    db 85h, 0A7h, 0FCh, 0FFh, 0FFh, 00h, 88h, 95h, 0A8h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 0A9h, 0FCh
    db 0FFh, 0FFh, 88h, 95h, 0AAh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0ABh, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 95h, 0ACh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0ADh, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0AEh, 0FCh
    db 0FFh, 0FFh, 0C6h, 85h, 0AFh, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0B0h, 0FCh, 0FFh, 0FFh, 88h
    db 8Dh, 0B1h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0B2h, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 0B3h, 0FCh, 0FFh
    db 0FFh, 0C6h, 85h, 0B4h, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h, 0B5h, 0FCh, 0FFh, 0FFh, 88h, 85h
    db 0B6h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0B7h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0B8h, 0FCh, 0FFh, 0FFh
    db 00h, 88h, 95h, 0B9h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0BAh, 0FCh, 0FFh, 0FFh, 88h, 85h, 0BBh
    db 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0BCh, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0BDh, 0FCh, 0FFh, 0FFh
    db 88h, 8Dh, 0BEh, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 0BFh, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 0C0h, 0FCh
    db 0FFh, 0FFh, 0C6h, 85h, 0C1h, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0C2h, 0FCh, 0FFh, 0FFh, 88h
    db 95h, 0C3h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0C4h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0C5h, 0FCh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 0C6h, 0FCh, 0FFh, 0FFh, 00h, 88h, 85h, 0C7h, 0FCh, 0FFh, 0FFh, 88h
    db 85h, 0C8h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0C9h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0CAh, 0FCh, 0FFh
    db 0FFh, 0FFh, 88h, 8Dh, 0CBh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0CCh, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 85h, 0CDh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0CEh, 0FCh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0CFh, 0FCh
    db 0FFh, 0FFh, 88h, 8Dh, 0D0h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0D1h, 0FCh, 0FFh, 0FFh, 88h, 85h
    db 0D2h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0D3h, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0D4h, 0FCh, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 0D5h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0D6h, 0FCh, 0FFh, 0FFh, 88h, 95h
    db 0D7h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0D8h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0D9h, 0FCh, 0FFh, 0FFh
    db 88h, 85h, 0DAh, 0FCh, 0FFh, 0FFh, 88h, 95h, 0DBh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0DCh, 0FCh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0DDh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0DEh, 0FCh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 0DFh, 0FCh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0E0h, 0FCh, 0FFh, 0FFh, 88h, 95h
    db 0E1h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0E2h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0E3h, 0FCh, 0FFh, 0FFh
    db 88h, 85h, 0E4h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0E5h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0E6h, 0FCh
    db 0FFh, 0FFh, 00h, 88h, 95h, 0E7h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0E8h, 0FCh, 0FFh, 0FFh, 88h
    db 85h, 0E9h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0EAh, 0FCh, 0FFh, 0FFh, 88h, 95h, 0EBh, 0FCh, 0FFh
    db 0FFh, 0C6h, 85h, 0ECh, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0EDh, 0FCh, 0FFh, 0FFh, 00h, 88h
    db 8Dh, 0EEh, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0EFh, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0F0h, 0FCh
    db 0FFh, 0FFh, 0FFh, 88h, 95h, 0F1h, 0FCh, 0FFh, 0FFh, 88h, 95h, 0F2h, 0FCh, 0FFh, 0FFh, 88h
    db 8Dh, 0F3h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0F4h, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0F5h, 0FCh
    db 0FFh, 0FFh, 0FFh, 88h, 85h, 0F6h, 0FCh, 0FFh, 0FFh, 88h, 85h, 0F7h, 0FCh, 0FFh, 0FFh, 88h
    db 8Dh, 0F8h, 0FCh, 0FFh, 0FFh, 0C6h, 85h, 0F9h, 0FCh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0FAh, 0FCh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0FBh, 0FCh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0FCh, 0FCh, 0FFh, 0FFh
    db 00h, 88h, 8Dh, 0FDh, 0FCh, 0FFh, 0FFh, 88h, 95h, 0FEh, 0FCh, 0FFh, 0FFh, 88h, 8Dh, 0FFh
    db 0FCh, 0FFh, 0FFh, 88h, 95h, 00h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 01h, 0FDh, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 02h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 03h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h
    db 04h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 05h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 06h, 0FDh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 07h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 08h, 0FDh, 0FFh, 0FFh, 00h
    db 0C6h, 85h, 09h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Ah, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 0Bh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0Ch, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0Dh, 0FDh, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 0Eh, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0Fh, 0FDh, 0FFh, 0FFh, 88h, 95h
    db 10h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 11h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 12h, 0FDh, 0FFh, 0FFh
    db 0C6h, 85h, 13h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 14h, 0FDh, 0FFh, 0FFh, 88h, 85h, 15h
    db 0FDh, 0FFh, 0FFh, 88h, 8Dh, 16h, 0FDh, 0FFh, 0FFh, 88h, 95h, 17h, 0FDh, 0FFh, 0FFh, 0C6h
    db 85h, 18h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 19h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 1Ah, 0FDh
    db 0FFh, 0FFh, 00h, 88h, 85h, 1Bh, 0FDh, 0FFh, 0FFh, 88h, 95h, 1Ch, 0FDh, 0FFh, 0FFh, 88h
    db 8Dh, 1Dh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 1Eh, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 1Fh, 0FDh
    db 0FFh, 0FFh, 0C6h, 85h, 20h, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 21h, 0FDh, 0FFh, 0FFh, 88h
    db 8Dh, 22h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 23h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 24h, 0FDh, 0FFh
    db 0FFh, 88h, 95h, 25h, 0FDh, 0FFh, 0FFh, 88h, 85h, 26h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 27h
    db 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 28h, 0FDh, 0FFh, 0FFh, 88h, 85h, 29h, 0FDh, 0FFh, 0FFh
    db 0C6h, 85h, 2Ah, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 2Bh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 2Ch
    db 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Dh, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 2Eh, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 2Fh, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 30h, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 31h, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 32h, 0FDh, 0FFh, 0FFh, 88h, 85h, 33h, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 34h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 35h, 0FDh, 0FFh, 0FFh, 88h, 95h
    db 36h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 37h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 38h, 0FDh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 39h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 3Ah, 0FDh, 0FFh, 0FFh, 88h
    db 95h, 3Bh, 0FDh, 0FFh, 0FFh, 88h, 85h, 3Ch, 0FDh, 0FFh, 0FFh, 88h, 85h, 3Dh, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 3Eh, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 3Fh, 0FDh, 0FFh, 0FFh, 0FFh, 88h
    db 8Dh, 40h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 41h, 0FDh, 0FFh, 0FFh, 88h, 85h, 42h, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 43h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 44h, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 45h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 46h, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 47h, 0FDh
    db 0FFh, 0FFh, 88h, 8Dh, 48h, 0FDh, 0FFh, 0FFh, 88h, 85h, 49h, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 4Ah, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 4Bh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 4Ch, 0FDh, 0FFh
    db 0FFh, 0FFh, 88h, 85h, 4Dh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 4Eh, 0FDh, 0FFh, 0FFh, 0FFh, 88h
    db 8Dh, 4Fh, 0FDh, 0FFh, 0FFh, 88h, 95h, 50h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 51h, 0FDh, 0FFh
    db 0FFh, 00h, 88h, 95h, 52h, 0FDh, 0FFh, 0FFh, 88h, 85h, 53h, 0FDh, 0FFh, 0FFh, 88h, 8Dh
    db 54h, 0FDh, 0FFh, 0FFh, 88h, 95h, 55h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 56h, 0FDh, 0FFh, 0FFh
    db 88h, 8Dh, 57h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 58h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 59h
    db 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 5Ah, 0FDh, 0FFh, 0FFh, 88h, 95h, 5Bh, 0FDh, 0FFh, 0FFh
    db 0C6h, 85h, 5Ch, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 5Dh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 5Eh
    db 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 5Fh, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 60h, 0FDh, 0FFh
    db 0FFh, 00h, 88h, 8Dh, 61h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 62h, 0FDh, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 63h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 64h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 65h, 0FDh
    db 0FFh, 0FFh, 0C6h, 85h, 66h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 67h, 0FDh, 0FFh, 0FFh, 88h
    db 8Dh, 68h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 69h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 6Ah, 0FDh
    db 0FFh, 0FFh, 0FFh, 88h, 8Dh, 6Bh, 0FDh, 0FFh, 0FFh, 88h, 95h, 6Ch, 0FDh, 0FFh, 0FFh, 0C6h
    db 85h, 6Dh, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 6Eh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 6Fh, 0FDh
    db 0FFh, 0FFh, 0FFh, 88h, 95h, 70h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 71h, 0FDh, 0FFh, 0FFh, 0C6h
    db 85h, 72h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 73h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 74h
    db 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 75h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 76h, 0FDh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 77h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 78h, 0FDh, 0FFh, 0FFh, 88h
    db 85h, 79h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 7Ah, 0FDh, 0FFh, 0FFh, 88h, 95h, 7Bh, 0FDh, 0FFh
    db 0FFh, 88h, 8Dh, 7Ch, 0FDh, 0FFh, 0FFh, 88h, 95h, 7Dh, 0FDh, 0FFh, 0FFh, 88h, 85h, 7Eh
    db 0FDh, 0FFh, 0FFh, 0C6h, 85h, 7Fh, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 80h, 0FDh, 0FFh, 0FFh
    db 88h, 95h, 81h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 82h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 83h
    db 0FDh, 0FFh, 0FFh, 88h, 8Dh, 84h, 0FDh, 0FFh, 0FFh, 88h, 95h, 85h, 0FDh, 0FFh, 0FFh, 88h
    db 95h, 86h, 0FDh, 0FFh, 0FFh, 88h, 95h, 87h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 88h, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 89h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 8Ah, 0FDh, 0FFh, 0FFh, 88h, 85h
    db 8Bh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 8Ch, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 8Dh, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 8Eh, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 8Fh, 0FDh, 0FFh, 0FFh, 88h, 85h
    db 90h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 91h, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 92h, 0FDh, 0FFh
    db 0FFh, 88h, 8Dh, 93h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 94h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 95h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 96h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 97h, 0FDh, 0FFh
    db 0FFh, 88h, 95h, 98h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 99h, 0FDh, 0FFh, 0FFh, 88h, 85h, 9Ah
    db 0FDh, 0FFh, 0FFh, 0C6h, 85h, 9Bh, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 9Ch, 0FDh, 0FFh, 0FFh
    db 88h, 95h, 9Dh, 0FDh, 0FFh, 0FFh, 88h, 85h, 9Eh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 9Fh, 0FDh
    db 0FFh, 0FFh, 00h, 88h, 95h, 0A0h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0A1h, 0FDh, 0FFh, 0FFh, 00h
    db 88h, 95h, 0A2h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0A3h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0A4h
    db 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0A5h, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0A6h, 0FDh, 0FFh
    db 0FFh, 88h, 95h, 0A7h, 0FDh, 0FFh, 0FFh, 88h, 95h, 0A8h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0A9h
    db 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0AAh, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0ABh, 0FDh, 0FFh, 0FFh
    db 88h, 85h, 0ACh, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0ADh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0AEh, 0FDh
    db 0FFh, 0FFh, 00h, 88h, 95h, 0AFh, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0B0h, 0FDh, 0FFh, 0FFh, 0C6h
    db 85h, 0B1h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0B2h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0B3h
    db 0FDh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 0B4h, 0FDh, 0FFh, 0FFh, 88h, 95h, 0B5h, 0FDh, 0FFh, 0FFh
    db 88h, 85h, 0B6h, 0FDh, 0FFh, 0FFh, 88h, 85h, 0B7h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0B8h, 0FDh
    db 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0B9h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0BAh, 0FDh, 0FFh, 0FFh
    db 0FFh, 88h, 95h, 0BBh, 0FDh, 0FFh, 0FFh, 88h, 95h, 0BCh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0BDh
    db 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0BEh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0BFh, 0FDh, 0FFh, 0FFh
    db 00h, 0C6h, 85h, 0C0h, 0FDh, 0FFh, 0FFh, 00h, 88h, 95h, 0C1h, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 0C2h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0C3h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0C4h, 0FDh
    db 0FFh, 0FFh, 00h, 0C6h, 85h, 0C5h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0C6h, 0FDh, 0FFh, 0FFh
    db 00h, 88h, 95h, 0C7h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0C8h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h
    db 0C9h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0CAh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0CBh, 0FDh, 0FFh
    db 0FFh, 00h, 0C6h, 85h, 0CCh, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0CDh, 0FDh, 0FFh, 0FFh, 88h
    db 8Dh, 0CEh, 0FDh, 0FFh, 0FFh, 88h, 85h, 0CFh, 0FDh, 0FFh, 0FFh, 88h, 85h, 0D0h, 0FDh, 0FFh
    db 0FFh, 0C6h, 85h, 0D1h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0D2h, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 0D3h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0D4h, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0D5h, 0FDh
    db 0FFh, 0FFh, 0C6h, 85h, 0D6h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0D7h, 0FDh, 0FFh, 0FFh, 88h
    db 8Dh, 0D8h, 0FDh, 0FFh, 0FFh, 88h, 85h, 0D9h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0DAh, 0FDh, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 0DBh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0DCh, 0FDh, 0FFh, 0FFh, 00h, 88h
    db 95h, 0DDh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0DEh, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0DFh, 0FDh
    db 0FFh, 0FFh, 0C6h, 85h, 0E0h, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0E1h, 0FDh, 0FFh, 0FFh, 0FFh
    db 88h, 85h, 0E2h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0E3h, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0E4h
    db 0FDh, 0FFh, 0FFh, 88h, 85h, 0E5h, 0FDh, 0FFh, 0FFh, 88h, 95h, 0E6h, 0FDh, 0FFh, 0FFh, 0C6h
    db 85h, 0E7h, 0FDh, 0FFh, 0FFh, 0FFh, 88h, 95h, 0E8h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0E9h, 0FDh
    db 0FFh, 0FFh, 00h, 0C6h, 85h, 0EAh, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0EBh, 0FDh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 0ECh, 0FDh, 0FFh, 0FFh, 00h, 0C6h, 85h, 0EDh, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 0EEh, 0FDh, 0FFh, 0FFh, 00h, 88h, 8Dh, 0EFh, 0FDh, 0FFh, 0FFh, 88h, 95h, 0F0h, 0FDh
    db 0FFh, 0FFh, 0C6h, 85h, 0F1h, 0FDh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 0F2h, 0FDh, 0FFh, 0FFh, 00h
    db 88h, 8Dh, 0F3h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0F4h, 0FDh, 0FFh, 0FFh, 88h, 85h, 0F5h, 0FDh
    db 0FFh, 0FFh, 88h, 85h, 0F6h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0F7h, 0FDh, 0FFh, 0FFh, 88h, 95h
    db 0F8h, 0FDh, 0FFh, 0FFh, 88h, 8Dh, 0F9h, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0FAh, 0FDh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 0FBh, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 0FCh, 0FDh, 0FFh, 0FFh, 0C6h, 85h
    db 0FDh, 0FDh, 0FFh, 0FFh, 00h, 88h, 85h, 0FEh, 0FDh, 0FFh, 0FFh, 0C6h, 85h, 0FFh, 0FDh, 0FFh
    db 0FFh, 0FFh, 88h, 95h, 00h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 01h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 02h, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 85h, 03h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 04h, 0FEh
    db 0FFh, 0FFh, 0FFh, 88h, 85h, 05h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 06h, 0FEh, 0FFh, 0FFh, 0FFh
    db 0C6h, 85h, 07h, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 85h, 08h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 09h
    db 0FEh, 0FFh, 0FFh, 0FFh, 88h, 85h, 0Ah, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 0Bh, 0FEh, 0FFh, 0FFh
    db 00h, 88h, 95h, 0Ch, 0FEh, 0FFh, 0FFh, 88h, 95h, 0Dh, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 0Eh
    db 0FEh, 0FFh, 0FFh, 00h, 88h, 95h, 0Fh, 0FEh, 0FFh, 0FFh, 88h, 85h, 10h, 0FEh, 0FFh, 0FFh
    db 0C6h, 85h, 11h, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 12h, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh
    db 13h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 14h, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 95h, 15h, 0FEh, 0FFh
    db 0FFh, 0C6h, 85h, 16h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 17h, 0FEh, 0FFh, 0FFh, 0FFh, 88h
    db 95h, 18h, 0FEh, 0FFh, 0FFh, 88h, 95h, 19h, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 1Ah, 0FEh, 0FFh
    db 0FFh, 88h, 8Dh, 1Bh, 0FEh, 0FFh, 0FFh, 88h, 85h, 1Ch, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 1Dh
    db 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 1Eh, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 95h, 1Fh, 0FEh, 0FFh
    db 0FFh, 88h, 95h, 20h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 21h, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh
    db 22h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 23h, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 95h, 24h, 0FEh, 0FFh
    db 0FFh, 0C6h, 85h, 25h, 0FEh, 0FFh, 0FFh, 00h, 88h, 85h, 26h, 0FEh, 0FFh, 0FFh, 88h, 95h
    db 27h, 0FEh, 0FFh, 0FFh, 88h, 85h, 28h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 29h, 0FEh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 2Ah, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 2Bh, 0FEh, 0FFh, 0FFh, 0C6h, 85h
    db 2Ch, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 2Dh, 0FEh, 0FFh, 0FFh, 00h, 88h, 85h, 2Eh, 0FEh
    db 0FFh, 0FFh, 88h, 95h, 2Fh, 0FEh, 0FFh, 0FFh, 88h, 85h, 30h, 0FEh, 0FFh, 0FFh, 88h, 85h
    db 31h, 0FEh, 0FFh, 0FFh, 88h, 95h, 32h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 33h, 0FEh, 0FFh, 0FFh
    db 00h, 88h, 8Dh, 34h, 0FEh, 0FFh, 0FFh, 88h, 85h, 35h, 0FEh, 0FFh, 0FFh, 88h, 85h, 36h
    db 0FEh, 0FFh, 0FFh, 0C6h, 85h, 37h, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh, 38h, 0FEh, 0FFh, 0FFh
    db 0C6h, 85h, 39h, 0FEh, 0FFh, 0FFh, 00h, 88h, 95h, 3Ah, 0FEh, 0FFh, 0FFh, 88h, 95h, 3Bh
    db 0FEh, 0FFh, 0FFh, 0C6h, 85h, 3Ch, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 3Dh, 0FEh, 0FFh, 0FFh
    db 00h, 88h, 95h, 3Eh, 0FEh, 0FFh, 0FFh, 88h, 85h, 3Fh, 0FEh, 0FFh, 0FFh, 88h, 95h, 40h
    db 0FEh, 0FFh, 0FFh, 0C6h, 85h, 41h, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 42h, 0FEh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 43h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 44h, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 85h
    db 45h, 0FEh, 0FFh, 0FFh, 88h, 85h, 46h, 0FEh, 0FFh, 0FFh, 88h, 85h, 47h, 0FEh, 0FFh, 0FFh
    db 88h, 95h, 48h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 49h, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh, 4Ah
    db 0FEh, 0FFh, 0FFh, 0C6h, 85h, 4Bh, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 4Ch, 0FEh, 0FFh, 0FFh
    db 88h, 8Dh, 4Dh, 0FEh, 0FFh, 0FFh, 88h, 95h, 4Eh, 0FEh, 0FFh, 0FFh, 88h, 95h, 4Fh, 0FEh
    db 0FFh, 0FFh, 88h, 95h, 50h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 51h, 0FEh, 0FFh, 0FFh, 0FFh, 88h
    db 85h, 52h, 0FEh, 0FFh, 0FFh, 88h, 85h, 53h, 0FEh, 0FFh, 0FFh, 88h, 95h, 54h, 0FEh, 0FFh
    db 0FFh, 88h, 85h, 55h, 0FEh, 0FFh, 0FFh, 88h, 95h, 56h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 57h
    db 0FEh, 0FFh, 0FFh, 0FFh, 88h, 95h, 58h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 59h, 0FEh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 5Ah, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 8Dh, 5Bh, 0FEh, 0FFh, 0FFh, 88h, 95h
    db 5Ch, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 5Dh, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 5Eh, 0FEh, 0FFh
    db 0FFh, 00h, 88h, 8Dh, 5Fh, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 60h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 61h, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 62h, 0FEh, 0FFh, 0FFh, 00h, 88h, 95h, 63h
    db 0FEh, 0FFh, 0FFh, 88h, 8Dh, 64h, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 65h, 0FEh, 0FFh, 0FFh, 0C6h
    db 85h, 66h, 0FEh, 0FFh, 0FFh, 00h, 88h, 95h, 67h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 68h, 0FEh
    db 0FFh, 0FFh, 00h, 0C6h, 85h, 69h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 6Ah, 0FEh, 0FFh, 0FFh
    db 0FFh, 88h, 85h, 6Bh, 0FEh, 0FFh, 0FFh, 88h, 95h, 6Ch, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 6Dh
    db 0FEh, 0FFh, 0FFh, 0C6h, 85h, 6Eh, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 6Fh, 0FEh, 0FFh, 0FFh
    db 0FFh, 0C6h, 85h, 70h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h, 85h, 71h, 0FEh, 0FFh, 0FFh, 0FFh, 88h
    db 85h, 72h, 0FEh, 0FFh, 0FFh, 88h, 95h, 73h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 74h, 0FEh, 0FFh
    db 0FFh, 0FFh, 0C6h, 85h, 75h, 0FEh, 0FFh, 0FFh, 00h, 88h, 85h, 76h, 0FEh, 0FFh, 0FFh, 88h
    db 95h, 77h, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 78h, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 79h, 0FEh, 0FFh
    db 0FFh, 88h, 85h, 7Ah, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 7Bh, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh
    db 7Ch, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 7Dh, 0FEh, 0FFh, 0FFh, 00h, 88h, 8Dh, 7Eh, 0FEh, 0FFh
    db 0FFh, 88h, 95h, 7Fh, 0FEh, 0FFh, 0FFh, 88h, 85h, 80h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 81h
    db 0FEh, 0FFh, 0FFh, 0FFh, 88h, 95h, 82h, 0FEh, 0FFh, 0FFh, 88h, 8Dh, 83h, 0FEh, 0FFh, 0FFh
    db 88h, 85h, 84h, 0FEh, 0FFh, 0FFh, 88h, 95h, 85h, 0FEh, 0FFh, 0FFh, 88h, 85h, 86h, 0FEh
    db 0FFh, 0FFh, 88h, 8Dh, 87h, 0FEh, 0FFh, 0FFh, 88h, 85h, 88h, 0FEh, 0FFh, 0FFh, 88h, 85h
    db 89h, 0FEh, 0FFh, 0FFh, 88h, 85h, 8Ah, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 8Bh, 0FEh, 0FFh, 0FFh
    db 00h, 0C6h, 85h, 8Ch, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 8Dh, 0FEh, 0FFh, 0FFh, 00h, 0C6h
    db 85h, 8Eh, 0FEh, 0FFh, 0FFh, 0FFh, 88h, 85h, 8Fh, 0FEh, 0FFh, 0FFh, 88h, 85h, 91h, 0FEh
    db 0FFh, 0FFh, 88h, 85h, 93h, 0FEh, 0FFh, 0FFh, 0C6h, 85h, 90h, 0FEh, 0FFh, 0FFh, 0FFh, 0C6h
    db 85h, 92h, 0FEh, 0FFh, 0FFh, 00h, 0C6h, 85h, 94h, 0FEh, 0FFh, 0FFh, 0FFh, 33h, 0C0h, 0B9h
    db 56h, 00h, 00h, 00h, 8Dh, 0BDh, 95h, 0FEh, 0FFh, 0FFh, 0F3h, 0ABh, 66h, 0ABh, 0AAh, 0Fh
    db 77h, 8Bh, 4Bh, 18h, 0B8h, 3Fh, 00h, 00h, 00h, 2Bh, 0C1h, 89h, 45h, 0F8h, 33h, 0FFh
    db 0DBh, 45h, 0F8h, 89h, 7Dh, 0FCh, 0DCh, 0Dh, 00h, 17h, 14h, 01h, 0DCh, 05h, 40h, 0C6h
    db 07h, 01h, 0DDh, 9Dh, 0D8h, 0F7h, 0FFh, 0FFh, 0DDh, 05h, 0F8h, 16h, 14h, 01h, 0DDh, 95h
    db 0E8h, 0F7h, 0FFh, 0FFh, 0EBh, 0Ah, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Dh, 49h, 00h
    db 83h, 0ECh, 18h, 0DDh, 5Ch, 24h, 10h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 0DDh, 5Ch, 24h
    db 08h, 0DDh, 85h, 0D8h, 0F7h, 0FFh, 0FFh, 0DDh, 1Ch, 24h, 0E8h, 71h, 8Ch, 0FEh, 0FFh, 0DCh
    db 0Dh, 10h, 0DCh, 11h, 01h, 83h, 0C4h, 18h, 0DCh, 05h, 0F0h, 0B3h, 09h, 01h, 0E8h, 95h
    db 9Bh, 03h, 00h, 8Bh, 0F0h, 85h, 0F6h, 89h, 75h, 0F4h, 74h, 43h, 33h, 0C0h, 85h, 0F6h
    db 7Eh, 38h, 0DDh, 85h, 0E8h, 0F7h, 0FFh, 0FFh, 8Dh, 0BCh, 3Dh, 80h, 0F6h, 0FFh, 0FFh, 0E8h
    db 74h, 9Bh, 03h, 00h, 8Bh, 0CEh, 8Bh, 0D1h, 89h, 55h, 0F8h, 8Ah, 0D0h, 8Ah, 0F2h, 0C1h
    db 0E9h, 02h, 8Bh, 0C2h, 0C1h, 0E0h, 10h, 66h, 8Bh, 0C2h, 8Bh, 0D6h, 0F3h, 0ABh, 8Bh, 0CAh
    db 83h, 0E1h, 03h, 0F3h, 0AAh, 8Bh, 7Dh, 0FCh, 8Bh, 0C6h, 03h, 0F8h, 89h, 7Dh, 0FCh, 0DDh
    db 85h, 0E8h, 0F7h, 0FFh, 0FFh, 0DCh, 05h, 40h, 0C6h, 07h, 01h, 0DCh, 15h, 80h, 0FDh, 07h
    db 01h, 0DDh, 95h, 0E8h, 0F7h, 0FFh, 0FFh, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Bh, 5Eh, 0FFh
    db 0FFh, 0FFh, 81h, 0FFh, 00h, 01h, 00h, 00h, 0DDh, 0D8h, 7Dh, 20h, 8Dh, 94h, 3Dh, 80h
    db 0F6h, 0FFh, 0FFh, 0B9h, 00h, 01h, 00h, 00h, 2Bh, 0CFh, 8Bh, 0FAh, 8Bh, 0D1h, 0C1h, 0E9h
    db 02h, 33h, 0C0h, 0F3h, 0ABh, 8Bh, 0CAh, 83h, 0E1h, 03h, 0F3h, 0AAh, 33h, 0F6h, 8Bh, 0FFh
    db 0FFh, 15h, 70h, 94h, 35h, 01h, 25h, 0FFh, 00h, 00h, 00h, 8Ah, 84h, 05h, 80h, 0F6h
    db 0FFh, 0FFh, 88h, 84h, 35h, 0F0h, 0F7h, 0FFh, 0FFh, 46h, 81h, 0FEh, 00h, 08h, 00h, 00h
    db 72h, 0DEh, 8Ah, 85h, 80h, 0F6h, 0FFh, 0FFh, 8Ah, 0C8h, 0B2h, 0FEh, 0F6h, 0EAh, 8Ah, 0D0h
    db 8Ah, 0F2h, 0F6h, 0D9h, 8Bh, 0C2h, 0C1h, 0E0h, 10h, 66h, 8Bh, 0C2h, 89h, 85h, 0C0h, 0F7h
    db 0FFh, 0FFh, 89h, 85h, 0C4h, 0F7h, 0FFh, 0FFh, 89h, 85h, 0C8h, 0F7h, 0FFh, 0FFh, 89h, 85h
    db 0CCh, 0F7h, 0FFh, 0FFh, 8Ah, 0C1h, 8Ah, 0D0h, 8Ah, 0F2h, 8Bh, 0C2h, 0C1h, 0E0h, 10h, 66h
    db 8Bh, 0C2h, 89h, 85h, 0D0h, 0F7h, 0FFh, 0FFh, 89h, 85h, 0D4h, 0F7h, 0FFh, 0FFh, 89h, 85h
    db 0D8h, 0F7h, 0FFh, 0FFh, 89h, 85h, 0DCh, 0F7h, 0FFh, 0FFh, 8Ah, 0C1h, 8Ah, 0E0h, 8Bh, 0C8h
    db 0C1h, 0E1h, 10h, 66h, 8Bh, 0C8h, 8Bh, 43h, 10h, 85h, 0C0h, 89h, 8Dh, 0B0h, 0F7h, 0FFh
    db 0FFh, 89h, 8Dh, 0B4h, 0F7h, 0FFh, 0FFh, 89h, 8Dh, 0B8h, 0F7h, 0FFh, 0FFh, 89h, 8Dh, 0BCh
    db 0F7h, 0FFh, 0FFh, 76h, 76h, 8Bh, 4Bh, 08h, 89h, 4Dh, 0FCh, 89h, 45h, 0F8h, 8Bh, 0FFh
    db 8Bh, 55h, 0FCh, 89h, 95h, 0ECh, 0F7h, 0FFh, 0FFh, 0FFh, 15h, 70h, 94h, 35h, 01h, 25h
    db 0FFh, 00h, 00h, 00h, 8Dh, 84h, 05h, 0F0h, 0F7h, 0FFh, 0FFh, 89h, 45h, 0F4h, 8Bh, 4Bh
    db 0Ch, 8Bh, 0B5h, 0ECh, 0F7h, 0FFh, 0FFh, 8Bh, 7Dh, 0F4h, 33h, 0C0h, 0Fh, 6Fh, 0Ch, 06h
    db 0Fh, 0D8h, 8Dh, 0B0h, 0F7h, 0FFh, 0FFh, 0Fh, 0DCh, 8Dh, 0C0h, 0F7h, 0FFh, 0FFh, 0Fh, 0D8h
    db 8Dh, 0D0h, 0F7h, 0FFh, 0FFh, 0Fh, 6Fh, 14h, 07h, 0Fh, 0FCh, 0CAh, 0Fh, 7Fh, 0Ch, 06h
    db 83h, 0C0h, 08h, 3Bh, 0C1h, 7Ch, 0D5h, 8Bh, 55h, 0FCh, 8Bh, 4Bh, 14h, 8Bh, 45h, 0F8h
    db 03h, 0D1h, 48h, 89h, 55h, 0FCh, 89h, 45h, 0F8h, 75h, 95h, 5Fh, 5Eh, 8Bh, 0E5h, 5Dh
    db 8Bh, 0E3h, 5Bh, 0C3h
?d_009ba790@@YAXXZ ENDP

; retail @ 0x009BD570 size 232
public ?d_009bd570@@YAXXZ
?d_009bd570@@YAXXZ PROC
    db 53h, 8Bh, 0DCh, 83h, 0ECh, 08h, 83h, 0E4h, 0F8h, 83h, 0C4h, 04h, 55h, 8Bh, 6Bh, 04h
    db 89h, 6Ch, 24h, 04h, 8Bh, 0ECh, 83h, 0ECh, 48h, 56h, 57h, 8Bh, 43h, 08h, 8Bh, 88h
    db 90h, 00h, 00h, 00h, 8Bh, 53h, 14h, 0C1h, 0E1h, 03h, 89h, 4Dh, 0ECh, 8Bh, 48h, 78h
    db 03h, 0D1h, 89h, 55h, 0FCh, 8Bh, 53h, 18h, 03h, 0CAh, 8Ah, 53h, 0Ch, 8Bh, 0B0h, 94h
    db 00h, 00h, 00h, 8Bh, 80h, 98h, 00h, 00h, 00h, 89h, 45h, 0F0h, 8Bh, 43h, 10h, 89h
    db 4Dh, 0F8h, 8Ah, 0C8h, 02h, 0CAh, 8Ah, 0D1h, 8Ah, 0F2h, 0C1h, 0E6h, 03h, 8Bh, 0CAh, 0C1h
    db 0E1h, 10h, 66h, 8Bh, 0CAh, 89h, 4Dh, 0C8h, 89h, 4Dh, 0CCh, 8Ah, 0C8h, 8Ah, 0E9h, 8Bh
    db 0C1h, 0C1h, 0E0h, 10h, 66h, 8Bh, 0C1h, 89h, 45h, 0D8h, 89h, 45h, 0DCh, 8Bh, 43h, 0Ch
    db 8Ah, 0D0h, 8Ah, 0F2h, 8Bh, 0C2h, 0C1h, 0E0h, 10h, 85h, 0F6h, 66h, 8Bh, 0C2h, 89h, 45h
    db 0B8h, 89h, 45h, 0BCh, 7Eh, 49h, 8Bh, 55h, 0F0h, 89h, 75h, 0F4h, 8Dh, 64h, 24h, 00h
    db 8Bh, 4Dh, 0ECh, 8Bh, 75h, 0FCh, 8Bh, 7Dh, 0F8h, 33h, 0C0h, 0Fh, 6Fh, 0Ch, 06h, 0Fh
    db 0D8h, 4Dh, 0B8h, 0Fh, 0DCh, 4Dh, 0C8h, 0Fh, 0D8h, 4Dh, 0D8h, 0Fh, 7Fh, 0Ch, 07h, 83h
    db 0C0h, 08h, 3Bh, 0C1h, 7Ch, 0E5h, 8Bh, 75h, 0FCh, 8Bh, 4Dh, 0F8h, 8Bh, 45h, 0F4h, 03h
    db 0F2h, 03h, 0CAh, 48h, 89h, 75h, 0FCh, 89h, 4Dh, 0F8h, 89h, 45h, 0F4h, 75h, 0C1h, 5Fh
    db 5Eh, 8Bh, 0E5h, 5Dh, 8Bh, 0E3h, 5Bh, 0C3h
?d_009bd570@@YAXXZ ENDP

; retail @ 0x009C2CE0 size 2374
_TEXT ENDS
_TEXT$d00dc2ce0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC2CE0 size 2374
public ?d_009c2ce0@@YAXXZ
?d_009c2ce0@@YAXXZ PROC
    db 052h, 051h, 053h, 08Bh, 044h, 024h, 010h, 08Bh, 054h, 024h, 018h, 08Bh, 00Ah, 08Bh, 05Ah, 01Ch
    db 08Bh, 04Ah, 038h, 08Bh, 05Ah, 054h, 08Bh, 04Ah, 070h, 08Bh, 05Ah, 07Ch, 08Bh, 05Ch, 024h, 014h
    db 08Dh, 00Dh
    dd ?Rva009B3A00Table@@3PAGA
    db 00Fh, 06Fh, 000h, 00Fh, 0D5h, 003h, 00Fh, 06Fh, 048h, 010h, 00Fh, 0D5h, 04Bh, 010h, 00Fh, 06Fh
    db 011h, 00Fh, 07Fh, 0C3h, 00Fh, 06Fh, 060h, 008h, 00Fh, 073h, 0D0h, 010h, 00Fh, 0D5h, 063h, 008h
    db 00Fh, 0DBh, 0DAh, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 0CEh, 00Fh, 0DBh, 0EAh, 00Fh, 073h, 0F6h, 020h
    db 00Fh, 06Fh, 079h, 018h, 00Fh, 0EFh, 0C5h, 00Fh, 0DBh, 0FEh, 00Fh, 0EBh, 0C3h, 00Fh, 0EFh, 0F7h
    db 00Fh, 0EBh, 0C7h, 00Fh, 06Fh, 079h, 018h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh, 002h, 00Fh, 0DBh, 0DAh
    db 00Fh, 06Fh, 040h, 020h, 00Fh, 073h, 0F3h, 010h, 00Fh, 0D5h, 043h, 020h, 00Fh, 0DBh, 0F9h, 00Fh
    db 0EBh, 0EBh, 00Fh, 0EBh, 0FEh, 00Fh, 06Fh, 058h, 018h, 00Fh, 0EBh, 0FDh, 00Fh, 0D5h, 05Bh, 018h
    db 00Fh, 073h, 0D4h, 010h, 00Fh, 07Fh, 07Ah, 010h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 0C7h, 00Fh, 073h
    db 0D4h, 010h, 00Fh, 073h, 0D7h, 030h, 00Fh, 07Fh, 0D6h, 00Fh, 0DBh, 0EAh, 00Fh, 0DBh, 0F4h, 00Fh
    db 07Fh, 07Ah, 050h, 00Fh, 0EFh, 0E6h, 00Fh, 073h, 0D1h, 020h, 00Fh, 0EBh, 0E5h, 00Fh, 06Fh, 079h
    db 018h, 00Fh, 0DBh, 0CAh, 00Fh, 06Fh, 068h, 030h, 00Fh, 073h, 0F0h, 010h, 00Fh, 0D5h, 06Bh, 030h
    db 00Fh, 0DBh, 0F8h, 00Fh, 07Fh, 04Ah, 040h, 00Fh, 0EBh, 0FCh, 00Fh, 07Fh, 0DCh, 00Fh, 0DBh, 0DAh
    db 00Fh, 06Fh, 049h, 010h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 0FBh, 00Fh, 07Fh, 0EBh, 00Fh, 073h
    db 0F3h, 030h, 00Fh, 0DBh, 0C8h, 00Fh, 07Fh, 07Ah, 020h, 00Fh, 0EBh, 0F3h, 00Fh, 06Fh, 079h, 008h
    db 00Fh, 0EBh, 0F1h, 00Fh, 06Fh, 048h, 038h, 00Fh, 0DBh, 0FCh, 00Fh, 0D5h, 04Bh, 038h, 00Fh, 0EBh
    db 0FEh, 00Fh, 0DBh, 041h, 008h, 00Fh, 073h, 0D4h, 020h, 00Fh, 07Fh, 07Ah, 030h, 00Fh, 07Fh, 0E6h
    db 00Fh, 06Fh, 079h, 018h, 00Fh, 0DBh, 0E2h, 00Fh, 06Fh, 059h, 008h, 00Fh, 0DBh, 0F9h, 00Fh, 0DBh
    db 0DDh, 00Fh, 0EBh, 0C4h, 00Fh, 073h, 0F3h, 010h, 00Fh, 0EBh, 0F8h, 00Fh, 06Fh, 061h, 010h, 00Fh
    db 0EBh, 0FBh, 00Fh, 06Fh, 040h, 050h, 00Fh, 07Fh, 0E3h, 00Fh, 0D5h, 043h, 050h, 00Fh, 0DBh, 0E5h
    db 00Fh, 07Fh, 07Ah, 008h, 00Fh, 0EBh, 0F4h, 00Fh, 07Fh, 0DCh, 00Fh, 073h, 0D6h, 010h, 00Fh, 07Fh
    db 0C7h, 00Fh, 0DBh, 0E1h, 00Fh, 073h, 0F7h, 030h, 00Fh, 0EBh, 0F4h, 00Fh, 06Fh, 060h, 058h, 00Fh
    db 0EBh, 0FEh, 00Fh, 0D5h, 063h, 058h, 00Fh, 073h, 0D3h, 010h, 00Fh, 07Fh, 07Ah, 018h, 00Fh, 0DBh
    db 0D9h, 00Fh, 073h, 0D5h, 030h, 00Fh, 0DBh, 0CAh, 00Fh, 06Fh, 070h, 068h, 00Fh, 0EBh, 0EBh, 00Fh
    db 0D5h, 073h, 068h, 00Fh, 073h, 0D0h, 010h, 00Fh, 07Fh, 0E7h, 00Fh, 07Fh, 0D3h, 00Fh, 073h, 0F7h
    db 030h, 00Fh, 0DBh, 0D8h, 00Fh, 0EFh, 0C3h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 0FDh, 00Fh, 07Fh
    db 0F5h, 00Fh, 0DBh, 071h, 008h, 00Fh, 0EBh, 0FBh, 00Fh, 073h, 0F6h, 020h, 00Fh, 0EBh, 0C1h, 00Fh
    db 07Fh, 07Ah, 028h, 00Fh, 0EBh, 0C6h, 00Fh, 06Fh, 078h, 078h, 00Fh, 07Fh, 0EEh, 00Fh, 0D5h, 07Bh
    db 078h, 00Fh, 073h, 0D5h, 020h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0E9h, 00Fh, 07Fh, 042h, 038h, 00Fh
    db 0DBh, 0CAh, 00Fh, 06Fh, 040h, 070h, 00Fh, 07Fh, 0FBh, 00Fh, 0D5h, 043h, 070h, 00Fh, 073h, 0F3h
    db 010h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0EFh, 0E9h, 00Fh, 0EBh, 0F5h, 00Fh, 07Fh, 0DDh, 00Fh, 0DBh
    db 069h, 018h, 00Fh, 0EBh, 0F9h, 00Fh, 06Fh, 048h, 060h, 00Fh, 0EFh, 0DDh, 00Fh, 0D5h, 04Bh, 060h
    db 00Fh, 0EBh, 0FBh, 00Fh, 0EBh, 0F5h, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 073h, 0D5h
    db 010h, 00Fh, 0DBh, 069h, 010h, 00Fh, 07Fh, 0C7h, 00Fh, 0EBh, 0F5h, 00Fh, 0DBh, 0C2h, 00Fh, 0EFh
    db 0F8h, 00Fh, 073h, 0F0h, 020h, 00Fh, 07Fh, 072h, 068h, 00Fh, 073h, 0D4h, 010h, 00Fh, 06Fh, 068h
    db 048h, 00Fh, 073h, 0F7h, 010h, 00Fh, 0D5h, 06Bh, 048h, 00Fh, 07Fh, 0FEh, 00Fh, 06Fh, 059h, 010h
    db 00Fh, 073h, 0F6h, 010h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0DBh, 0D9h, 00Fh, 0EBh, 0F8h, 00Fh, 07Fh
    db 0C8h, 00Fh, 0DBh, 049h, 018h, 00Fh, 0EBh, 0F3h, 00Fh, 07Fh, 0E3h, 00Fh, 073h, 0D1h, 020h, 00Fh
    db 0DBh, 0DAh, 00Fh, 0EBh, 0F9h, 00Fh, 0EBh, 0FBh, 00Fh, 07Fh, 0E3h, 00Fh, 0DBh, 059h, 008h, 00Fh
    db 07Fh, 0E9h, 00Fh, 07Fh, 07Ah, 058h, 00Fh, 073h, 0D5h, 030h, 00Fh, 06Fh, 078h, 040h, 00Fh, 0EBh
    db 0F3h, 00Fh, 0D5h, 07Bh, 040h, 00Fh, 0EBh, 0F5h, 00Fh, 0DBh, 061h, 010h, 00Fh, 073h, 0F0h, 020h
    db 00Fh, 07Fh, 072h, 048h, 00Fh, 07Fh, 0C6h, 00Fh, 0DBh, 041h, 018h, 00Fh, 073h, 0F6h, 010h, 00Fh
    db 06Fh, 068h, 028h, 00Fh, 07Fh, 0CBh, 00Fh, 0D5h, 06Bh, 028h, 00Fh, 073h, 0D1h, 010h, 00Fh, 0DBh
    db 049h, 008h, 00Fh, 0EBh, 0C4h, 00Fh, 0DBh, 0D7h, 00Fh, 0EBh, 0C1h, 00Fh, 0EBh, 0C2h, 00Fh, 073h
    db 0F3h, 010h, 00Fh, 07Fh, 0DCh, 00Fh, 07Fh, 0EAh, 00Fh, 07Fh, 042h, 070h, 00Fh, 073h, 0D2h, 030h
    db 00Fh, 0DBh, 061h, 010h, 00Fh, 0EBh, 0F2h, 00Fh, 06Fh, 051h, 008h, 00Fh, 0EBh, 0F4h, 00Fh, 0DBh
    db 0D7h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 05Ah, 050h, 00Fh, 0EBh, 0F2h, 00Fh, 06Fh, 051h, 018h
    db 00Fh, 073h, 0F5h, 010h, 00Fh, 07Fh, 072h, 060h, 00Fh, 0DBh, 0D5h, 00Fh, 06Fh, 071h, 010h, 00Fh
    db 0EFh, 0EAh, 00Fh, 0DBh, 0F7h, 00Fh, 073h, 0D2h, 020h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0EBh, 0DAh
    db 00Fh, 0EBh, 07Ah, 040h, 00Fh, 0EBh, 0F3h, 00Fh, 0EBh, 0FDh, 00Fh, 07Fh, 072h, 050h, 00Fh, 07Fh
    db 07Ah, 040h, 00Fh, 06Fh, 052h, 030h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah
    db 018h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h
    db 0CAh, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh
    db 0FDh, 0F7h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 04Ah, 038h, 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh
    db 0E5h, 0C3h, 00Fh, 0EDh, 0E7h, 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh
    db 0FDh, 0C3h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 052h, 020h, 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh
    db 07Fh, 0D1h, 00Fh, 0E5h, 051h, 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah, 028h, 00Fh, 0EDh, 0C7h
    db 00Fh, 07Fh, 0EFh, 00Fh, 0E9h, 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h
    db 048h, 00Fh, 0EDh, 0E4h, 00Fh, 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h
    db 00Fh, 0E5h, 079h, 048h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 062h, 010h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh
    db 061h, 038h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh, 07Fh, 072h, 020h, 00Fh
    db 07Fh, 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 008h, 00Fh
    db 0E9h, 0E9h, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh
    db 0DBh, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h
    db 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h
    db 00Fh, 0E9h, 0D1h, 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0E9h, 0E7h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0FFh
    db 00Fh, 0EDh, 0CAh, 00Fh, 0EDh, 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 0DBh, 00Fh, 0E9h, 0F5h, 00Fh
    db 0EDh, 0EDh, 00Fh, 0EDh, 0DCh, 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 0C0h, 00Fh, 07Fh
    db 04Ah, 010h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 002h, 00Fh, 069h
    db 0CDh, 00Fh, 07Fh, 0F0h, 00Fh, 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh
    db 00Fh, 07Fh, 0CEh, 00Fh, 07Fh, 062h, 008h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 018h, 00Fh, 06Ah
    db 0F0h, 00Fh, 06Fh, 022h, 00Fh, 062h, 0C8h, 00Fh, 06Fh, 06Ah, 010h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh
    db 072h, 038h, 00Fh, 061h, 0C5h, 00Fh, 07Fh, 04Ah, 028h, 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh
    db 061h, 0D3h, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh
    db 002h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh
    db 062h, 030h, 00Fh, 07Fh, 052h, 020h, 00Fh, 06Fh, 052h, 070h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh
    db 0D4h, 00Fh, 06Fh, 07Ah, 058h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh
    db 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah, 050h, 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h
    db 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 04Ah, 078h, 00Fh, 0FDh, 0FDh
    db 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh, 0E7h, 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h
    db 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 052h, 060h, 00Fh, 0E5h, 0F9h
    db 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h, 051h, 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah
    db 068h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh, 0E9h, 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh
    db 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h, 00Fh, 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh
    db 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 062h, 050h, 00Fh
    db 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh
    db 07Fh, 072h, 060h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 072h, 040h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh
    db 00Fh, 06Fh, 05Ah, 048h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h
    db 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh
    db 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 050h, 00Fh
    db 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh, 06Fh, 05Ah, 060h, 00Fh, 0E9h, 0E7h, 00Fh
    db 0EDh, 0C9h, 00Fh, 0EDh, 0FFh, 00Fh, 0EDh, 0CAh, 00Fh, 0EDh, 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh
    db 0DBh, 00Fh, 0E9h, 0F5h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0DCh, 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h
    db 00Fh, 0EDh, 0C0h, 00Fh, 07Fh, 04Ah, 050h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h
    db 00Fh, 07Fh, 042h, 040h, 00Fh, 069h, 0CDh, 00Fh, 07Fh, 0F0h, 00Fh, 061h, 0F7h, 00Fh, 07Fh, 0E5h
    db 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh, 00Fh, 07Fh, 0CEh, 00Fh, 07Fh, 062h, 048h, 00Fh, 069h, 0C7h
    db 00Fh, 07Fh, 06Ah, 058h, 00Fh, 06Ah, 0F0h, 00Fh, 06Fh, 062h, 040h, 00Fh, 062h, 0C8h, 00Fh, 06Fh
    db 06Ah, 050h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 072h, 078h, 00Fh, 061h, 0C5h, 00Fh, 07Fh, 04Ah, 068h
    db 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh
    db 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh, 042h, 040h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 04Ah, 050h
    db 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh, 062h, 070h, 00Fh, 07Fh, 052h, 060h, 00Fh, 06Fh
    db 052h, 030h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 050h, 00Fh, 0E5h, 0E6h
    db 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah
    db 010h, 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh
    db 0D1h, 00Fh, 06Fh, 04Ah, 070h, 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh
    db 0E7h, 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h
    db 0DFh, 00Fh, 06Fh, 052h, 020h, 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h
    db 051h, 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah, 060h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh
    db 0E9h, 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h
    db 00Fh, 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h
    db 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 062h, 010h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh
    db 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh, 07Fh, 072h, 020h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh
    db 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 040h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh
    db 0D0h, 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h
    db 00Fh, 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh
    db 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh
    db 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h, 004h, 00Fh, 0E9h, 0E7h
    db 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0EDh, 0FFh, 00Fh, 07Fh, 052h, 020h, 00Fh
    db 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h, 058h, 00Fh, 0EDh, 0DBh
    db 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h, 0E3h, 004h, 00Fh, 0EDh
    db 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h, 00Fh, 07Fh, 062h, 040h
    db 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 030h, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 079h, 058h, 00Fh
    db 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh, 072h, 060h, 00Fh, 071h, 0E0h
    db 004h, 00Fh, 07Fh, 06Ah, 050h, 00Fh, 07Fh, 07Ah, 070h, 00Fh, 07Fh, 002h, 00Fh, 06Fh, 052h, 038h
    db 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 058h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh
    db 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah, 018h, 00Fh
    db 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh, 0D1h, 00Fh
    db 06Fh, 04Ah, 078h, 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh, 0E7h, 00Fh
    db 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 0DFh, 00Fh
    db 06Fh, 052h, 028h, 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h, 051h, 028h
    db 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah, 068h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh, 0E9h, 0C4h
    db 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h, 00Fh, 0EDh
    db 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h, 00Fh, 0EDh
    db 0F3h, 00Fh, 07Fh, 062h, 018h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh, 0DDh, 00Fh
    db 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh, 07Fh, 072h, 028h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 072h, 008h
    db 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 048h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh, 0D0h
    db 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h, 00Fh
    db 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh
    db 0D2h, 00Fh, 06Fh, 042h, 018h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh, 0EDh
    db 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h, 004h, 00Fh, 0E9h, 0E7h, 00Fh
    db 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 028h, 00Fh, 0EDh, 0FFh, 00Fh, 07Fh, 052h, 028h, 00Fh, 0EDh
    db 0FCh, 00Fh, 07Fh, 04Ah, 018h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h, 058h, 00Fh, 0EDh, 0DBh, 00Fh
    db 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h, 0E3h, 004h, 00Fh, 0EDh, 071h
    db 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h, 00Fh, 07Fh, 062h, 048h, 00Fh
    db 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 038h, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 079h, 058h, 00Fh, 0EDh
    db 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh, 072h, 068h, 00Fh, 071h, 0E0h, 004h
    db 00Fh, 07Fh, 06Ah, 058h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 07Fh, 042h, 008h, 05Bh, 059h, 05Ah, 0C3h
?d_009c2ce0@@YAXXZ ENDP
_TEXT$d00dc2ce0 ENDS
_TEXT SEGMENT

; retail @ 0x009C3630 size 1724
_TEXT ENDS
_TEXT$d00dc3630 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC3630 size 1724
public ?d_009c3630@@YAXXZ
?d_009c3630@@YAXXZ PROC
    db 052h, 051h, 053h, 08Bh, 044h, 024h, 010h, 08Bh, 054h, 024h, 018h, 08Bh, 00Ah, 08Bh, 05Ah, 01Ch
    db 08Bh, 04Ah, 038h, 08Bh, 05Ah, 054h, 08Bh, 04Ah, 070h, 08Bh, 05Ah, 07Ch, 08Bh, 05Ch, 024h, 014h
    db 08Dh, 00Dh
    dd ?Rva009B3A00Table@@3PAGA
    db 00Fh, 06Fh, 000h, 00Fh, 0D5h, 003h, 00Fh, 06Fh, 048h, 010h, 00Fh, 0D5h, 04Bh, 010h, 00Fh, 06Fh
    db 011h, 00Fh, 07Fh, 0C3h, 00Fh, 06Fh, 060h, 008h, 00Fh, 073h, 0D0h, 010h, 00Fh, 0D5h, 063h, 008h
    db 00Fh, 0DBh, 0DAh, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 0CEh, 00Fh, 0DBh, 0EAh, 00Fh, 073h, 0F6h, 020h
    db 00Fh, 06Fh, 079h, 018h, 00Fh, 0EFh, 0C5h, 00Fh, 0DBh, 0FEh, 00Fh, 0EBh, 0C3h, 00Fh, 0EFh, 0F7h
    db 00Fh, 0EBh, 0C7h, 00Fh, 06Fh, 079h, 018h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh, 002h, 00Fh, 0DBh, 0DAh
    db 00Fh, 06Fh, 040h, 020h, 00Fh, 073h, 0F3h, 010h, 00Fh, 0D5h, 043h, 020h, 00Fh, 0DBh, 0F9h, 00Fh
    db 0EBh, 0EBh, 00Fh, 0EBh, 0FEh, 00Fh, 06Fh, 058h, 018h, 00Fh, 0EBh, 0FDh, 00Fh, 0D5h, 05Bh, 018h
    db 00Fh, 073h, 0D4h, 010h, 00Fh, 07Fh, 07Ah, 010h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 0C7h, 00Fh, 073h
    db 0D4h, 010h, 00Fh, 073h, 0D7h, 030h, 00Fh, 07Fh, 0D6h, 00Fh, 0DBh, 0EAh, 00Fh, 0DBh, 0F4h, 00Fh
    db 07Fh, 07Ah, 050h, 00Fh, 0EFh, 0E6h, 00Fh, 073h, 0D1h, 020h, 00Fh, 0EBh, 0E5h, 00Fh, 06Fh, 079h
    db 018h, 00Fh, 0DBh, 0CAh, 00Fh, 06Fh, 068h, 030h, 00Fh, 073h, 0F0h, 010h, 00Fh, 0D5h, 06Bh, 030h
    db 00Fh, 0DBh, 0F8h, 00Fh, 07Fh, 04Ah, 040h, 00Fh, 0EBh, 0FCh, 00Fh, 07Fh, 0DCh, 00Fh, 0DBh, 0DAh
    db 00Fh, 06Fh, 049h, 010h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 0FBh, 00Fh, 07Fh, 0EBh, 00Fh, 073h
    db 0F3h, 030h, 00Fh, 0DBh, 0C8h, 00Fh, 07Fh, 07Ah, 020h, 00Fh, 0EBh, 0F3h, 00Fh, 06Fh, 079h, 008h
    db 00Fh, 0EBh, 0F1h, 00Fh, 06Fh, 048h, 038h, 00Fh, 0DBh, 0FCh, 00Fh, 0D5h, 04Bh, 038h, 00Fh, 0EBh
    db 0FEh, 00Fh, 0DBh, 041h, 008h, 00Fh, 073h, 0D4h, 020h, 00Fh, 07Fh, 07Ah, 030h, 00Fh, 07Fh, 0E6h
    db 00Fh, 06Fh, 079h, 018h, 00Fh, 0DBh, 0E2h, 00Fh, 06Fh, 059h, 008h, 00Fh, 0DBh, 0F9h, 00Fh, 0DBh
    db 0DDh, 00Fh, 0EBh, 0C4h, 00Fh, 073h, 0F3h, 010h, 00Fh, 0EBh, 0F8h, 00Fh, 06Fh, 061h, 010h, 00Fh
    db 0EBh, 0FBh, 00Fh, 06Fh, 040h, 050h, 00Fh, 07Fh, 0E3h, 00Fh, 0D5h, 043h, 050h, 00Fh, 0DBh, 0E5h
    db 00Fh, 07Fh, 07Ah, 008h, 00Fh, 0EBh, 0F4h, 00Fh, 07Fh, 0DCh, 00Fh, 073h, 0D6h, 010h, 00Fh, 07Fh
    db 0C7h, 00Fh, 0DBh, 0E1h, 00Fh, 073h, 0F7h, 030h, 00Fh, 0EBh, 0F4h, 00Fh, 06Fh, 060h, 058h, 00Fh
    db 0EBh, 0FEh, 00Fh, 0D5h, 063h, 058h, 00Fh, 073h, 0D3h, 010h, 00Fh, 07Fh, 07Ah, 018h, 00Fh, 0DBh
    db 0D9h, 00Fh, 073h, 0D5h, 030h, 00Fh, 0DBh, 0CAh, 00Fh, 06Fh, 070h, 068h, 00Fh, 0EBh, 0EBh, 00Fh
    db 0D5h, 073h, 068h, 00Fh, 073h, 0D0h, 010h, 00Fh, 07Fh, 0E7h, 00Fh, 07Fh, 0D3h, 00Fh, 073h, 0F7h
    db 030h, 00Fh, 0DBh, 0D8h, 00Fh, 0EFh, 0C3h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 0FDh, 00Fh, 07Fh
    db 0F5h, 00Fh, 0DBh, 071h, 008h, 00Fh, 0EBh, 0FBh, 00Fh, 073h, 0F6h, 020h, 00Fh, 0EBh, 0C1h, 00Fh
    db 07Fh, 07Ah, 028h, 00Fh, 0EBh, 0C6h, 00Fh, 06Fh, 078h, 078h, 00Fh, 07Fh, 0EEh, 00Fh, 0D5h, 07Bh
    db 078h, 00Fh, 073h, 0D5h, 020h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0E9h, 00Fh, 07Fh, 042h, 038h, 00Fh
    db 0DBh, 0CAh, 00Fh, 06Fh, 040h, 070h, 00Fh, 07Fh, 0FBh, 00Fh, 0D5h, 043h, 070h, 00Fh, 073h, 0F3h
    db 010h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0EFh, 0E9h, 00Fh, 0EBh, 0F5h, 00Fh, 07Fh, 0DDh, 00Fh, 0DBh
    db 069h, 018h, 00Fh, 0EBh, 0F9h, 00Fh, 06Fh, 048h, 060h, 00Fh, 0EFh, 0DDh, 00Fh, 0D5h, 04Bh, 060h
    db 00Fh, 0EBh, 0FBh, 00Fh, 0EBh, 0F5h, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 073h, 0D5h
    db 010h, 00Fh, 0DBh, 069h, 010h, 00Fh, 07Fh, 0C7h, 00Fh, 0EBh, 0F5h, 00Fh, 0DBh, 0C2h, 00Fh, 0EFh
    db 0F8h, 00Fh, 073h, 0F0h, 020h, 00Fh, 07Fh, 072h, 068h, 00Fh, 073h, 0D4h, 010h, 00Fh, 06Fh, 068h
    db 048h, 00Fh, 073h, 0F7h, 010h, 00Fh, 0D5h, 06Bh, 048h, 00Fh, 07Fh, 0FEh, 00Fh, 06Fh, 059h, 010h
    db 00Fh, 073h, 0F6h, 010h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0DBh, 0D9h, 00Fh, 0EBh, 0F8h, 00Fh, 07Fh
    db 0C8h, 00Fh, 0DBh, 049h, 018h, 00Fh, 0EBh, 0F3h, 00Fh, 07Fh, 0E3h, 00Fh, 073h, 0D1h, 020h, 00Fh
    db 0DBh, 0DAh, 00Fh, 0EBh, 0F9h, 00Fh, 0EBh, 0FBh, 00Fh, 07Fh, 0E3h, 00Fh, 0DBh, 059h, 008h, 00Fh
    db 07Fh, 0E9h, 00Fh, 07Fh, 07Ah, 058h, 00Fh, 073h, 0D5h, 030h, 00Fh, 06Fh, 078h, 040h, 00Fh, 0EBh
    db 0F3h, 00Fh, 0D5h, 07Bh, 040h, 00Fh, 0EBh, 0F5h, 00Fh, 0DBh, 061h, 010h, 00Fh, 073h, 0F0h, 020h
    db 00Fh, 07Fh, 072h, 048h, 00Fh, 07Fh, 0C6h, 00Fh, 0DBh, 041h, 018h, 00Fh, 073h, 0F6h, 010h, 00Fh
    db 06Fh, 068h, 028h, 00Fh, 07Fh, 0CBh, 00Fh, 0D5h, 06Bh, 028h, 00Fh, 073h, 0D1h, 010h, 00Fh, 0DBh
    db 049h, 008h, 00Fh, 0EBh, 0C4h, 00Fh, 0DBh, 0D7h, 00Fh, 0EBh, 0C1h, 00Fh, 0EBh, 0C2h, 00Fh, 073h
    db 0F3h, 010h, 00Fh, 07Fh, 0DCh, 00Fh, 07Fh, 0EAh, 00Fh, 07Fh, 042h, 070h, 00Fh, 073h, 0D2h, 030h
    db 00Fh, 0DBh, 061h, 010h, 00Fh, 0EBh, 0F2h, 00Fh, 06Fh, 051h, 008h, 00Fh, 0EBh, 0F4h, 00Fh, 0DBh
    db 0D7h, 00Fh, 073h, 0F3h, 020h, 00Fh, 0EBh, 05Ah, 050h, 00Fh, 0EBh, 0F2h, 00Fh, 06Fh, 051h, 018h
    db 00Fh, 073h, 0F5h, 010h, 00Fh, 07Fh, 072h, 060h, 00Fh, 0DBh, 0D5h, 00Fh, 06Fh, 071h, 010h, 00Fh
    db 0EFh, 0EAh, 00Fh, 0DBh, 0F7h, 00Fh, 073h, 0D2h, 020h, 00Fh, 0DBh, 079h, 018h, 00Fh, 0EBh, 0DAh
    db 00Fh, 0EBh, 07Ah, 040h, 00Fh, 0EBh, 0F3h, 00Fh, 0EBh, 0FDh, 00Fh, 07Fh, 072h, 050h, 00Fh, 07Fh
    db 07Ah, 040h, 00Fh, 06Fh, 052h, 030h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh
    db 049h, 040h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 041h, 020h
    db 00Fh, 0FDh, 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 020h, 00Fh, 0E5h, 0C3h
    db 00Fh, 07Fh, 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0E5h, 069h
    db 028h, 00Fh, 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 020h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh, 0FDh, 00Fh, 0EDh
    db 0E0h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 010h, 00Fh, 0EDh, 0F6h, 00Fh
    db 06Fh, 061h, 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 07Fh, 072h, 020h
    db 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 0FDh, 0D0h, 00Fh
    db 0E9h, 0E9h, 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 032h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh, 0F4h, 00Fh, 0EDh
    db 0CDh, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0E9h
    db 0D1h, 090h, 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0E9h, 0E7h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0FFh, 00Fh
    db 0EDh, 0CAh, 00Fh, 0EDh, 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 0DBh, 00Fh, 0E9h, 0F5h, 00Fh, 0EDh
    db 0EDh, 00Fh, 0EDh, 0DCh, 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 0C0h, 00Fh, 07Fh, 04Ah
    db 010h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0CDh
    db 00Fh, 07Fh, 0F0h, 00Fh, 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh, 00Fh
    db 07Fh, 0CEh, 00Fh, 07Fh, 062h, 008h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 018h, 00Fh, 06Ah, 0F0h
    db 00Fh, 06Fh, 022h, 00Fh, 062h, 0C8h, 00Fh, 06Fh, 06Ah, 010h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 072h
    db 038h, 00Fh, 061h, 0C5h, 00Fh, 07Fh, 04Ah, 028h, 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 061h
    db 0D3h, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh, 002h
    db 00Fh, 069h, 0EBh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh, 062h
    db 030h, 00Fh, 07Fh, 052h, 020h, 00Fh, 06Fh, 052h, 030h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh
    db 0D4h, 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0CAh, 00Fh
    db 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 020h
    db 00Fh, 0E5h, 0C3h, 00Fh, 07Fh, 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h
    db 00Fh, 0E5h, 069h, 028h, 00Fh, 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 020h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh
    db 0FDh, 00Fh, 0EDh, 0E0h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 010h, 00Fh
    db 0EDh, 0F6h, 00Fh, 06Fh, 061h, 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh
    db 07Fh, 072h, 020h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh
    db 0FDh, 0D0h, 00Fh, 0E9h, 0E9h, 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 032h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh
    db 0F4h, 00Fh, 0EDh, 0CDh, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh
    db 0D6h, 00Fh, 0E9h, 0D1h, 090h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh
    db 071h, 0E2h, 004h, 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0EDh
    db 0FFh, 00Fh, 07Fh, 052h, 020h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0E9h, 0E3h, 00Fh
    db 0EDh, 061h, 058h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h
    db 00Fh, 071h, 0E3h, 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h
    db 0E6h, 004h, 00Fh, 07Fh, 062h, 040h, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 030h, 00Fh, 0E9h
    db 0F8h, 00Fh, 0EDh, 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh
    db 07Fh, 072h, 060h, 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 050h, 00Fh, 07Fh, 07Ah, 070h, 00Fh
    db 07Fh, 002h, 00Fh, 06Fh, 052h, 038h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh
    db 049h, 040h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 018h, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 041h, 020h
    db 00Fh, 0FDh, 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 028h, 00Fh, 0E5h, 0C3h
    db 00Fh, 07Fh, 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0E5h, 069h
    db 028h, 00Fh, 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 028h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh, 0FDh, 00Fh, 0EDh
    db 0E0h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 018h, 00Fh, 0EDh, 0F6h, 00Fh
    db 06Fh, 061h, 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 07Fh, 072h, 028h
    db 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 072h, 008h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 0FDh, 0D0h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 072h, 008h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh, 0F4h
    db 00Fh, 0EDh, 0CDh, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 018h, 00Fh, 0EDh, 0D6h
    db 00Fh, 0E9h, 0D1h, 090h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h
    db 0E2h, 004h, 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 028h, 00Fh, 0EDh, 0FFh
    db 00Fh, 07Fh, 052h, 028h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 018h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh
    db 061h, 058h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh
    db 071h, 0E3h, 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h
    db 004h, 00Fh, 07Fh, 062h, 048h, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 038h, 00Fh, 0E9h, 0F8h
    db 00Fh, 0EDh, 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh
    db 072h, 068h, 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 058h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 07Fh
    db 042h, 008h, 05Bh, 059h, 05Ah, 0C3h
?d_009c3630@@YAXXZ ENDP
_TEXT$d00dc3630 ENDS
_TEXT SEGMENT

; retail @ 0x009C3D50 size 1777
_TEXT ENDS
_TEXT$d00dc3d50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC3D50 size 1777
public ?d_009c3d50@@YAXXZ
?d_009c3d50@@YAXXZ PROC
    db 052h, 051h, 053h, 08Bh, 044h, 024h, 010h, 08Bh, 054h, 024h, 018h, 08Bh, 00Ah, 08Bh, 05Ah, 01Ch
    db 08Bh, 04Ah, 038h, 08Bh, 05Ah, 054h, 08Bh, 04Ah, 070h, 08Bh, 05Ah, 07Ch, 08Bh, 05Ch, 024h, 014h
    db 08Dh, 00Dh
    dd ?Rva009B3A00Table@@3PAGA
    db 00Fh, 06Fh, 000h, 00Fh, 0D5h, 003h, 00Fh, 06Fh, 048h, 008h, 00Fh, 0D5h, 04Bh, 008h, 00Fh, 06Fh
    db 050h, 010h, 00Fh, 0D5h, 053h, 010h, 00Fh, 06Fh, 058h, 018h, 00Fh, 0D5h, 05Bh, 018h, 00Fh, 06Fh
    db 060h, 020h, 00Fh, 0D5h, 063h, 020h, 00Fh, 06Fh, 068h, 028h, 00Fh, 0D5h, 06Bh, 028h, 00Fh, 06Fh
    db 070h, 030h, 00Fh, 0D5h, 073h, 030h, 00Fh, 06Fh, 078h, 038h, 00Fh, 0D5h, 07Bh, 038h, 00Fh, 07Fh
    db 002h, 00Fh, 07Fh, 04Ah, 008h, 00Fh, 07Fh, 052h, 010h, 00Fh, 07Fh, 05Ah, 018h, 00Fh, 07Fh, 062h
    db 020h, 00Fh, 07Fh, 06Ah, 028h, 00Fh, 07Fh, 072h, 030h, 00Fh, 07Fh, 07Ah, 038h, 00Fh, 06Fh, 040h
    db 040h, 00Fh, 0D5h, 043h, 040h, 00Fh, 06Fh, 048h, 048h, 00Fh, 0D5h, 04Bh, 048h, 00Fh, 06Fh, 050h
    db 050h, 00Fh, 0D5h, 053h, 050h, 00Fh, 06Fh, 058h, 058h, 00Fh, 0D5h, 05Bh, 058h, 00Fh, 06Fh, 060h
    db 060h, 00Fh, 0D5h, 063h, 060h, 00Fh, 06Fh, 068h, 068h, 00Fh, 0D5h, 06Bh, 068h, 00Fh, 06Fh, 070h
    db 070h, 00Fh, 0D5h, 073h, 070h, 00Fh, 06Fh, 078h, 078h, 00Fh, 0D5h, 07Bh, 078h, 00Fh, 07Fh, 042h
    db 040h, 00Fh, 07Fh, 04Ah, 048h, 00Fh, 07Fh, 052h, 050h, 00Fh, 07Fh, 05Ah, 058h, 00Fh, 07Fh, 062h
    db 060h, 00Fh, 07Fh, 06Ah, 068h, 00Fh, 07Fh, 072h, 070h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 06Fh, 052h
    db 030h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 018h, 00Fh, 0E5h, 0E6h, 00Fh
    db 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah, 010h
    db 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh, 0D1h
    db 00Fh, 06Fh, 04Ah, 038h, 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh, 0E7h
    db 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 0DFh
    db 00Fh, 06Fh, 052h, 020h, 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h, 051h
    db 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah, 028h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh, 0E9h
    db 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h, 00Fh
    db 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h, 00Fh
    db 0EDh, 0F3h, 00Fh, 07Fh, 062h, 010h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh, 0DDh
    db 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh, 07Fh, 072h, 020h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 032h
    db 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 008h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh, 0D0h
    db 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h, 00Fh
    db 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh
    db 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh, 06Fh
    db 05Ah, 020h, 00Fh, 0E9h, 0E7h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0FFh, 00Fh, 0EDh, 0CAh, 00Fh, 0EDh
    db 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 0DBh, 00Fh, 0E9h, 0F5h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0DCh
    db 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 0C0h, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0EDh, 0C7h
    db 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0CDh, 00Fh, 07Fh, 0F0h, 00Fh
    db 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh, 00Fh, 07Fh, 0CEh, 00Fh, 07Fh
    db 062h, 008h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 018h, 00Fh, 06Ah, 0F0h, 00Fh, 06Fh, 022h, 00Fh
    db 062h, 0C8h, 00Fh, 06Fh, 06Ah, 010h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 072h, 038h, 00Fh, 061h, 0C5h
    db 00Fh, 07Fh, 04Ah, 028h, 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 07Fh, 0C1h
    db 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0EBh, 00Fh
    db 07Fh, 04Ah, 010h, 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh, 062h, 030h, 00Fh, 07Fh, 052h
    db 020h, 00Fh, 06Fh, 052h, 070h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 058h
    db 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh
    db 00Fh, 06Fh, 05Ah, 050h, 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh
    db 0F7h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 04Ah, 078h, 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h
    db 0C3h, 00Fh, 0EDh, 0E7h, 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh
    db 0C3h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 052h, 060h, 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh
    db 0D1h, 00Fh, 0E5h, 051h, 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh, 06Ah, 068h, 00Fh, 0EDh, 0C7h, 00Fh
    db 07Fh, 0EFh, 00Fh, 0E9h, 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h
    db 00Fh, 0EDh, 0E4h, 00Fh, 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh
    db 0E5h, 079h, 048h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 062h, 050h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h
    db 038h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh, 00Fh, 07Fh, 072h, 060h, 00Fh, 07Fh
    db 0C2h, 00Fh, 06Fh, 072h, 040h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 048h, 00Fh
    db 0E9h, 0E9h, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0F3h, 00Fh, 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh
    db 0DBh, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0D8h, 00Fh, 0EDh, 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h
    db 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 050h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h
    db 00Fh, 0E9h, 0D1h, 00Fh, 06Fh, 05Ah, 060h, 00Fh, 0E9h, 0E7h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0FFh
    db 00Fh, 0EDh, 0CAh, 00Fh, 0EDh, 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 0DBh, 00Fh, 0E9h, 0F5h, 00Fh
    db 0EDh, 0EDh, 00Fh, 0EDh, 0DCh, 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 0C0h, 00Fh, 07Fh
    db 04Ah, 050h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 042h, 040h, 00Fh
    db 069h, 0CDh, 00Fh, 07Fh, 0F0h, 00Fh, 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah
    db 0EEh, 00Fh, 07Fh, 0CEh, 00Fh, 07Fh, 062h, 048h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 058h, 00Fh
    db 06Ah, 0F0h, 00Fh, 06Fh, 062h, 040h, 00Fh, 062h, 0C8h, 00Fh, 06Fh, 06Ah, 050h, 00Fh, 07Fh, 0E0h
    db 00Fh, 07Fh, 072h, 078h, 00Fh, 061h, 0C5h, 00Fh, 07Fh, 04Ah, 068h, 00Fh, 069h, 0E5h, 00Fh, 07Fh
    db 0D5h, 00Fh, 061h, 0D3h, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h
    db 00Fh, 07Fh, 042h, 040h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 04Ah, 050h, 00Fh, 06Ah, 0E5h, 00Fh, 062h
    db 0D5h, 00Fh, 07Fh, 062h, 070h, 00Fh, 07Fh, 052h, 060h, 00Fh, 06Fh, 052h, 030h, 00Fh, 06Fh, 071h
    db 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 050h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 049h, 040h, 00Fh
    db 0E5h, 0F7h, 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0EFh, 00Fh
    db 06Fh, 041h, 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 04Ah, 070h
    db 00Fh, 0FDh, 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh, 0E7h, 00Fh, 0E5h, 0E9h, 00Fh
    db 06Fh, 079h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 052h, 020h
    db 00Fh, 0E5h, 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h, 051h, 028h, 00Fh, 0E9h, 0DDh
    db 00Fh, 06Fh, 06Ah, 060h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh, 0E9h, 0C4h, 00Fh, 0E5h, 069h
    db 028h, 00Fh, 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h, 00Fh, 0EDh, 0E0h, 00Fh, 0E9h
    db 0DEh, 00Fh, 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh
    db 062h, 010h, 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh
    db 0EDh, 0FAh, 00Fh, 07Fh, 072h, 020h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh
    db 0FDh, 0EBh, 00Fh, 06Fh, 05Ah, 040h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0F3h, 00Fh
    db 07Fh, 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0D8h, 00Fh, 0EDh
    db 0CDh, 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h
    db 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh
    db 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h, 004h, 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh
    db 06Fh, 05Ah, 020h, 00Fh, 0EDh, 0FFh, 00Fh, 07Fh, 052h, 020h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah
    db 010h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h, 058h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h
    db 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h, 0E3h, 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh
    db 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h, 00Fh, 07Fh, 062h, 040h, 00Fh, 071h, 0E5h, 004h, 00Fh
    db 07Fh, 05Ah, 030h, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h
    db 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh, 072h, 060h, 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 050h
    db 00Fh, 07Fh, 07Ah, 070h, 00Fh, 07Fh, 002h, 00Fh, 06Fh, 052h, 038h, 00Fh, 06Fh, 071h, 030h, 00Fh
    db 07Fh, 0D4h, 00Fh, 06Fh, 07Ah, 058h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 049h, 040h, 00Fh, 0E5h, 0F7h
    db 00Fh, 07Fh, 0CDh, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 05Ah, 018h, 00Fh, 0E5h, 0EFh, 00Fh, 06Fh, 041h
    db 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0FDh, 0F7h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 04Ah, 078h, 00Fh, 0FDh
    db 0FDh, 00Fh, 07Fh, 0C5h, 00Fh, 0E5h, 0C3h, 00Fh, 0EDh, 0E7h, 00Fh, 0E5h, 0E9h, 00Fh, 06Fh, 079h
    db 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 052h, 028h, 00Fh, 0E5h
    db 0F9h, 00Fh, 0FDh, 0E9h, 00Fh, 07Fh, 0D1h, 00Fh, 0E5h, 051h, 028h, 00Fh, 0E9h, 0DDh, 00Fh, 06Fh
    db 06Ah, 068h, 00Fh, 0EDh, 0C7h, 00Fh, 07Fh, 0EFh, 00Fh, 0E9h, 0C4h, 00Fh, 0E5h, 069h, 028h, 00Fh
    db 0FDh, 0D1h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0EDh, 0E4h, 00Fh, 0EDh, 0E0h, 00Fh, 0E9h, 0DEh, 00Fh
    db 0FDh, 0EFh, 00Fh, 0EDh, 0F6h, 00Fh, 0E5h, 079h, 048h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 062h, 018h
    db 00Fh, 0E9h, 0CDh, 00Fh, 06Fh, 061h, 038h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 0EDh, 0FAh
    db 00Fh, 07Fh, 072h, 028h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 072h, 008h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh
    db 0EBh, 00Fh, 06Fh, 05Ah, 048h, 00Fh, 0E9h, 0E9h, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0F3h, 00Fh, 07Fh
    db 0F0h, 00Fh, 0E5h, 0F4h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0D8h, 00Fh, 0EDh, 0CDh
    db 00Fh, 0E5h, 0E3h, 00Fh, 0EDh, 0F0h, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 018h
    db 00Fh, 0EDh, 0D6h, 00Fh, 0FDh, 0E3h, 00Fh, 0E9h, 0D1h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h
    db 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h, 004h, 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh
    db 05Ah, 028h, 00Fh, 0EDh, 0FFh, 00Fh, 07Fh, 052h, 028h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 018h
    db 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h, 058h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h
    db 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h, 0E3h, 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh
    db 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h, 00Fh, 07Fh, 062h, 048h, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh
    db 05Ah, 038h, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh
    db 071h, 0E7h, 004h, 00Fh, 07Fh, 072h, 068h, 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 058h, 00Fh
    db 07Fh, 07Ah, 078h, 00Fh, 07Fh, 042h, 008h, 05Bh, 059h, 05Ah, 0C3h
?d_009c3d50@@YAXXZ ENDP
_TEXT$d00dc3d50 ENDS
_TEXT SEGMENT

; retail @ 0x009C4450 size 1034
_TEXT ENDS
_TEXT$d00dc4450 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC4450 size 1034
public ?d_009c4450@@YAXXZ
?d_009c4450@@YAXXZ PROC
    db 052h, 051h, 053h, 08Bh, 044h, 024h, 010h, 08Bh, 054h, 024h, 018h, 08Bh, 00Ah, 08Bh, 05Ah, 01Ch
    db 08Bh, 04Ah, 038h, 08Bh, 05Ah, 054h, 08Bh, 04Ah, 070h, 08Bh, 05Ah, 07Ch, 08Bh, 05Ch, 024h, 014h
    db 08Dh, 00Dh
    dd ?Rva009B3A00Table@@3PAGA
    db 00Fh, 06Fh, 000h, 00Fh, 0D5h, 003h, 00Fh, 06Fh, 048h, 010h, 00Fh, 0D5h, 04Bh, 010h, 00Fh, 06Fh
    db 050h, 020h, 00Fh, 0D5h, 053h, 020h, 00Fh, 06Fh, 058h, 030h, 00Fh, 0D5h, 05Bh, 030h, 00Fh, 07Fh
    db 002h, 00Fh, 0EFh, 0EDh, 00Fh, 07Fh, 06Ah, 008h, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 07Fh, 06Ah, 018h
    db 00Fh, 07Fh, 052h, 020h, 00Fh, 07Fh, 06Ah, 028h, 00Fh, 07Fh, 05Ah, 030h, 00Fh, 07Fh, 06Ah, 038h
    db 00Fh, 07Fh, 06Ah, 040h, 00Fh, 07Fh, 06Ah, 048h, 00Fh, 07Fh, 06Ah, 050h, 00Fh, 07Fh, 06Ah, 058h
    db 00Fh, 07Fh, 06Ah, 060h, 00Fh, 07Fh, 06Ah, 068h, 00Fh, 07Fh, 06Ah, 070h, 00Fh, 07Fh, 06Ah, 078h
    db 00Fh, 06Fh, 052h, 030h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 049h, 040h
    db 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh
    db 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 020h, 00Fh, 0E5h, 0C3h, 00Fh, 07Fh
    db 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0E5h, 069h, 028h, 00Fh
    db 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 020h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh, 0FDh, 00Fh, 0EDh, 0E0h, 00Fh
    db 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 010h, 00Fh, 0EDh, 0F6h, 00Fh, 06Fh, 061h
    db 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 07Fh, 072h, 020h, 00Fh, 07Fh
    db 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h, 0E9h
    db 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 032h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh, 0F4h, 00Fh, 0EDh, 0CDh, 00Fh
    db 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh, 0E9h, 0D1h, 090h
    db 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0E9h, 0E7h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0FFh, 00Fh, 0EDh, 0CAh
    db 00Fh, 0EDh, 0FCh, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 0DBh, 00Fh, 0E9h, 0F5h, 00Fh, 0EDh, 0EDh, 00Fh
    db 0EDh, 0DCh, 00Fh, 0EDh, 0EEh, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh, 0C0h, 00Fh, 07Fh, 04Ah, 010h, 00Fh
    db 0EDh, 0C7h, 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0CDh, 00Fh, 07Fh
    db 0F0h, 00Fh, 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh, 00Fh, 07Fh, 0CEh
    db 00Fh, 07Fh, 062h, 008h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 018h, 00Fh, 06Ah, 0F0h, 00Fh, 06Fh
    db 022h, 00Fh, 062h, 0C8h, 00Fh, 06Fh, 06Ah, 010h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 072h, 038h, 00Fh
    db 061h, 0C5h, 00Fh, 07Fh, 04Ah, 028h, 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh
    db 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh, 002h, 00Fh, 069h
    db 0EBh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh, 062h, 030h, 00Fh
    db 07Fh, 052h, 020h, 00Fh, 06Fh, 052h, 030h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh
    db 06Fh, 049h, 040h, 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 010h, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 041h
    db 020h, 00Fh, 0FDh, 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 020h, 00Fh, 0E5h
    db 0C3h, 00Fh, 07Fh, 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0E5h
    db 069h, 028h, 00Fh, 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 020h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh, 0FDh, 00Fh
    db 0EDh, 0E0h, 00Fh, 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 010h, 00Fh, 0EDh, 0F6h
    db 00Fh, 06Fh, 061h, 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 07Fh, 072h
    db 020h, 00Fh, 07Fh, 0C2h, 00Fh, 06Fh, 032h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 0FDh, 0D0h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 032h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh, 0F4h, 00Fh
    db 0EDh, 0CDh, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 010h, 00Fh, 0EDh, 0D6h, 00Fh
    db 0E9h, 0D1h, 090h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h
    db 004h, 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 020h, 00Fh, 0EDh, 0FFh, 00Fh
    db 07Fh, 052h, 020h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h
    db 058h, 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h
    db 0E3h, 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h
    db 00Fh, 07Fh, 062h, 040h, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 030h, 00Fh, 0E9h, 0F8h, 00Fh
    db 0EDh, 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh, 072h
    db 060h, 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 050h, 00Fh, 07Fh, 07Ah, 070h, 00Fh, 07Fh, 002h
    db 00Fh, 06Fh, 052h, 038h, 090h, 00Fh, 06Fh, 071h, 030h, 00Fh, 07Fh, 0D4h, 00Fh, 06Fh, 049h, 040h
    db 00Fh, 0E5h, 0E6h, 00Fh, 06Fh, 05Ah, 018h, 00Fh, 0E5h, 0CAh, 00Fh, 06Fh, 041h, 020h, 00Fh, 0FDh
    db 0E2h, 00Fh, 0EFh, 0F6h, 00Fh, 0FDh, 0D1h, 00Fh, 06Fh, 06Ah, 028h, 00Fh, 0E5h, 0C3h, 00Fh, 07Fh
    db 0E9h, 00Fh, 0FDh, 0C3h, 00Fh, 0E5h, 059h, 050h, 00Fh, 0E9h, 0F2h, 00Fh, 0E5h, 069h, 028h, 00Fh
    db 0E9h, 0C4h, 00Fh, 06Fh, 07Ah, 028h, 00Fh, 0EDh, 0E4h, 00Fh, 0FDh, 0FDh, 00Fh, 0EDh, 0E0h, 00Fh
    db 0E5h, 049h, 048h, 00Fh, 0E9h, 0DEh, 00Fh, 07Fh, 062h, 018h, 00Fh, 0EDh, 0F6h, 00Fh, 06Fh, 061h
    db 038h, 00Fh, 0EDh, 0F3h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0DCh, 00Fh, 07Fh, 072h, 028h, 00Fh, 07Fh
    db 0C2h, 00Fh, 06Fh, 072h, 008h, 00Fh, 0E5h, 0C4h, 00Fh, 0FDh, 0EBh, 00Fh, 0FDh, 0D0h, 00Fh, 0E9h
    db 0E9h, 00Fh, 0E5h, 0F4h, 00Fh, 0FDh, 072h, 008h, 00Fh, 0EDh, 0C9h, 00Fh, 07Fh, 0F4h, 00Fh, 0EDh
    db 0CDh, 00Fh, 0E9h, 0F2h, 00Fh, 0EDh, 0D2h, 00Fh, 06Fh, 042h, 018h, 00Fh, 0EDh, 0D6h, 00Fh, 0E9h
    db 0D1h, 090h, 00Fh, 0EDh, 051h, 058h, 00Fh, 0EDh, 0C9h, 00Fh, 0EDh, 0CAh, 00Fh, 071h, 0E2h, 004h
    db 00Fh, 0E9h, 0E7h, 00Fh, 071h, 0E1h, 004h, 00Fh, 06Fh, 05Ah, 028h, 00Fh, 0EDh, 0FFh, 00Fh, 07Fh
    db 052h, 028h, 00Fh, 0EDh, 0FCh, 00Fh, 07Fh, 04Ah, 018h, 00Fh, 0E9h, 0E3h, 00Fh, 0EDh, 061h, 058h
    db 00Fh, 0EDh, 0DBh, 00Fh, 0EDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0E9h, 0F5h, 00Fh, 071h, 0E3h
    db 004h, 00Fh, 0EDh, 071h, 058h, 00Fh, 0EDh, 0EDh, 00Fh, 0EDh, 0EEh, 00Fh, 071h, 0E6h, 004h, 00Fh
    db 07Fh, 062h, 048h, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 05Ah, 038h, 00Fh, 0E9h, 0F8h, 00Fh, 0EDh
    db 079h, 058h, 00Fh, 0EDh, 0C0h, 00Fh, 0EDh, 0C7h, 00Fh, 071h, 0E7h, 004h, 00Fh, 07Fh, 072h, 068h
    db 00Fh, 071h, 0E0h, 004h, 00Fh, 07Fh, 06Ah, 058h, 00Fh, 07Fh, 07Ah, 078h, 00Fh, 07Fh, 042h, 008h
    db 05Bh, 059h, 05Ah, 0C3h
?d_009c4450@@YAXXZ ENDP
_TEXT$d00dc4450 ENDS
_TEXT SEGMENT

; retail @ 0x009C4860 size 777
_TEXT ENDS
_TEXT$d00dc4860 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC4860 size 777
public ?d_009c4860@@YAXXZ
?d_009c4860@@YAXXZ PROC
    db 052h, 051h, 053h, 08Bh, 044h, 024h, 010h, 08Bh, 054h, 024h, 014h, 08Bh, 00Ah, 08Bh, 05Ah, 01Ch
    db 08Bh, 04Ah, 038h, 08Bh, 05Ah, 054h, 08Bh, 04Ah, 070h, 08Bh, 05Ah, 07Ch, 08Dh, 00Dh
    dd ?Rva009B3A00Table@@3PAGA
    db 00Fh, 06Fh, 000h, 00Fh, 0EFh, 0C9h, 00Fh, 06Fh, 011h, 00Fh, 07Fh, 0C3h, 00Fh, 0EFh, 0E4h, 00Fh
    db 073h, 0D0h, 010h, 00Fh, 0DBh, 0DAh, 00Fh, 07Fh, 0C5h, 00Fh, 07Fh, 0CEh, 00Fh, 0DBh, 0EAh, 00Fh
    db 06Fh, 079h, 018h, 00Fh, 0EFh, 0C5h, 00Fh, 0DBh, 0FEh, 00Fh, 0EBh, 0C3h, 00Fh, 0EFh, 0F7h, 00Fh
    db 0EBh, 0C7h, 00Fh, 06Fh, 079h, 018h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh, 002h, 00Fh, 0DBh, 0DAh, 00Fh
    db 073h, 0F3h, 010h, 00Fh, 0DBh, 0F9h, 00Fh, 0EBh, 0EBh, 00Fh, 0EBh, 0FEh, 00Fh, 0EBh, 0FDh, 00Fh
    db 073h, 0D4h, 010h, 00Fh, 07Fh, 07Ah, 010h, 00Fh, 07Fh, 062h, 020h, 00Fh, 07Fh, 062h, 030h, 00Fh
    db 07Fh, 062h, 008h, 00Fh, 07Fh, 062h, 018h, 00Fh, 07Fh, 062h, 028h, 00Fh, 07Fh, 062h, 038h, 00Fh
    db 07Fh, 062h, 078h, 00Fh, 07Fh, 062h, 068h, 00Fh, 07Fh, 062h, 058h, 00Fh, 07Fh, 062h, 048h, 00Fh
    db 07Fh, 062h, 070h, 00Fh, 07Fh, 062h, 060h, 00Fh, 07Fh, 062h, 050h, 00Fh, 07Fh, 062h, 040h, 00Fh
    db 06Fh, 07Ah, 010h, 00Fh, 06Fh, 041h, 020h, 00Fh, 06Fh, 059h, 050h, 00Fh, 0E5h, 0C7h, 00Fh, 0E5h
    db 0DFh, 00Fh, 06Fh, 032h, 00Fh, 06Fh, 061h, 038h, 00Fh, 0FDh, 0C7h, 00Fh, 07Fh, 0F1h, 00Fh, 0E5h
    db 0F4h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0D4h, 00Fh, 0E5h, 0ECh, 00Fh, 0FDh, 0F1h
    db 00Fh, 07Fh, 0F4h, 00Fh, 0FDh, 0D0h, 00Fh, 0FDh, 0EBh, 00Fh, 07Fh, 0F7h, 00Fh, 07Fh, 0E9h, 00Fh
    db 0F9h, 0F2h, 00Fh, 0F9h, 0E3h, 00Fh, 0F9h, 0F8h, 00Fh, 0FDh, 0D2h, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh
    db 0C0h, 00Fh, 0FDh, 0D6h, 00Fh, 0FDh, 0DCh, 00Fh, 0F9h, 0D1h, 00Fh, 0F9h, 0F5h, 00Fh, 0FDh, 0C9h
    db 00Fh, 0FDh, 0EDh, 00Fh, 0FDh, 0C7h, 00Fh, 0FDh, 0CAh, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0FDh, 0EEh
    db 00Fh, 07Fh, 0E1h, 00Fh, 061h, 0E5h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0CDh, 00Fh, 07Fh, 0F0h, 00Fh
    db 061h, 0F7h, 00Fh, 07Fh, 0E5h, 00Fh, 062h, 0E6h, 00Fh, 06Ah, 0EEh, 00Fh, 07Fh, 0CEh, 00Fh, 07Fh
    db 062h, 008h, 00Fh, 069h, 0C7h, 00Fh, 07Fh, 06Ah, 018h, 00Fh, 06Ah, 0F0h, 00Fh, 06Fh, 022h, 00Fh
    db 062h, 0C8h, 00Fh, 06Fh, 06Ah, 010h, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 072h, 038h, 00Fh, 061h, 0C5h
    db 00Fh, 07Fh, 04Ah, 028h, 00Fh, 069h, 0E5h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 07Fh, 0C1h
    db 00Fh, 062h, 0C2h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 07Fh, 002h, 00Fh, 069h, 0EBh, 00Fh
    db 07Fh, 04Ah, 010h, 00Fh, 06Ah, 0E5h, 00Fh, 062h, 0D5h, 00Fh, 07Fh, 062h, 030h, 00Fh, 07Fh, 052h
    db 020h, 00Fh, 06Fh, 07Ah, 010h, 00Fh, 06Fh, 041h, 020h, 00Fh, 06Fh, 059h, 050h, 00Fh, 0E5h, 0C7h
    db 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 032h, 00Fh, 06Fh, 061h, 038h, 00Fh, 0FDh, 0C7h, 00Fh, 07Fh, 0F1h
    db 00Fh, 0E5h, 0F4h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0DDh, 00Fh, 0E5h, 0D4h, 00Fh, 0E5h, 0ECh, 00Fh
    db 0FDh, 0F1h, 00Fh, 07Fh, 0F4h, 00Fh, 0FDh, 071h, 058h, 00Fh, 0FDh, 061h, 058h, 00Fh, 0FDh, 0D0h
    db 00Fh, 0FDh, 0EBh, 00Fh, 07Fh, 0F7h, 00Fh, 07Fh, 0E9h, 00Fh, 0F9h, 0F2h, 00Fh, 0F9h, 0E3h, 00Fh
    db 0F9h, 0F8h, 00Fh, 0FDh, 0D2h, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0C0h, 00Fh, 0FDh, 0D6h, 00Fh, 0FDh
    db 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 07Fh, 062h, 040h, 00Fh, 071h, 0E3h, 004h, 00Fh, 07Fh, 05Ah
    db 030h, 00Fh, 0F9h, 0D1h, 00Fh, 0F9h, 0F5h, 00Fh, 0FDh, 0C9h, 00Fh, 0FDh, 0EDh, 00Fh, 0FDh, 0C7h
    db 00Fh, 0FDh, 0CAh, 00Fh, 071h, 0E7h, 004h, 00Fh, 071h, 0E2h, 004h, 00Fh, 071h, 0E0h, 004h, 00Fh
    db 071h, 0E1h, 004h, 00Fh, 07Fh, 07Ah, 070h, 00Fh, 07Fh, 002h, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 07Fh
    db 052h, 020h, 00Fh, 07Fh, 04Ah, 010h, 00Fh, 0FDh, 0EEh, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 06Ah
    db 050h, 00Fh, 071h, 0E6h, 004h, 00Fh, 07Fh, 072h, 060h, 00Fh, 06Fh, 07Ah, 018h, 00Fh, 06Fh, 041h
    db 020h, 00Fh, 06Fh, 059h, 050h, 00Fh, 0E5h, 0C7h, 00Fh, 0E5h, 0DFh, 00Fh, 06Fh, 072h, 008h, 00Fh
    db 06Fh, 061h, 038h, 00Fh, 0FDh, 0C7h, 00Fh, 07Fh, 0F1h, 00Fh, 0E5h, 0F4h, 00Fh, 07Fh, 0C2h, 00Fh
    db 07Fh, 0DDh, 00Fh, 0E5h, 0D4h, 00Fh, 0E5h, 0ECh, 00Fh, 0FDh, 0F1h, 00Fh, 07Fh, 0F4h, 00Fh, 0FDh
    db 071h, 058h, 00Fh, 0FDh, 061h, 058h, 00Fh, 0FDh, 0D0h, 00Fh, 0FDh, 0EBh, 00Fh, 07Fh, 0F7h, 00Fh
    db 07Fh, 0E9h, 00Fh, 0F9h, 0F2h, 00Fh, 0F9h, 0E3h, 00Fh, 0F9h, 0F8h, 00Fh, 0FDh, 0D2h, 00Fh, 0FDh
    db 0DBh, 00Fh, 0FDh, 0C0h, 00Fh, 0FDh, 0D6h, 00Fh, 0FDh, 0DCh, 00Fh, 071h, 0E4h, 004h, 00Fh, 07Fh
    db 062h, 048h, 00Fh, 071h, 0E3h, 004h, 00Fh, 07Fh, 05Ah, 038h, 00Fh, 0F9h, 0D1h, 00Fh, 0F9h, 0F5h
    db 00Fh, 0FDh, 0C9h, 00Fh, 0FDh, 0EDh, 00Fh, 0FDh, 0C7h, 00Fh, 0FDh, 0CAh, 00Fh, 071h, 0E7h, 004h
    db 00Fh, 071h, 0E2h, 004h, 00Fh, 071h, 0E0h, 004h, 00Fh, 071h, 0E1h, 004h, 00Fh, 07Fh, 07Ah, 078h
    db 00Fh, 07Fh, 042h, 008h, 00Fh, 07Fh, 04Ah, 018h, 00Fh, 07Fh, 052h, 028h, 00Fh, 07Fh, 04Ah, 018h
    db 00Fh, 0FDh, 0EEh, 00Fh, 071h, 0E5h, 004h, 00Fh, 07Fh, 06Ah, 058h, 00Fh, 071h, 0E6h, 004h, 00Fh
    db 07Fh, 072h, 068h, 05Bh, 059h, 05Ah, 0C3h
?d_009c4860@@YAXXZ ENDP
_TEXT$d00dc4860 ENDS
_TEXT SEGMENT

; retail @ 0x009C4DF0 size 153
public ?d_009c4df0@@YAXXZ
?d_009c4df0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 08h, 57h, 8Dh, 46h, 04h, 0BAh, 08h, 00h
    db 00h, 00h, 66h, 8Bh, 39h, 66h, 81h, 0C7h, 80h, 00h, 66h, 89h, 78h, 0FCh, 66h, 8Bh
    db 79h, 02h, 66h, 81h, 0C7h, 80h, 00h, 66h, 89h, 78h, 0FEh, 66h, 8Bh, 79h, 04h, 66h
    db 81h, 0C7h, 80h, 00h, 66h, 89h, 38h, 66h, 8Bh, 79h, 06h, 66h, 81h, 0C7h, 80h, 00h
    db 66h, 89h, 78h, 02h, 66h, 8Bh, 79h, 08h, 66h, 81h, 0C7h, 80h, 00h, 66h, 89h, 78h
    db 04h, 66h, 8Bh, 79h, 0Ah, 66h, 81h, 0C7h, 80h, 00h, 66h, 89h, 78h, 06h, 66h, 8Bh
    db 79h, 0Ch, 66h, 81h, 0C7h, 80h, 00h, 66h, 89h, 78h, 08h, 66h, 8Bh, 79h, 0Eh, 66h
    db 81h, 0C7h, 80h, 00h, 66h, 89h, 78h, 0Ah, 83h, 0C0h, 10h, 83h, 0C1h, 10h, 4Ah, 75h
    db 91h, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 10h, 6Ah, 08h, 50h, 56h, 51h, 0E8h, 3Dh
    db 0FEh, 0FFh, 0FFh, 83h, 0C4h, 10h, 5Fh, 5Eh, 0C3h
?d_009c4df0@@YAXXZ ENDP

; retail @ 0x009C4E90 size 485
public ?d_009c4e90@@YAXXZ
?d_009c4e90@@YAXXZ PROC
    db 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h, 0Ch, 53h, 8Bh, 5Ch, 24h, 08h, 55h, 56h, 8Bh
    db 74h, 24h, 20h, 57h, 8Dh, 4Bh, 04h, 0BFh, 02h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 66h, 0Fh, 0B6h, 28h, 66h, 03h, 2Ah, 66h, 89h, 69h, 0FCh, 66h, 0Fh, 0B6h, 68h, 01h
    db 66h, 03h, 6Ah, 02h, 66h, 89h, 69h, 0FEh, 66h, 0Fh, 0B6h, 68h, 02h, 66h, 03h, 6Ah
    db 04h, 66h, 89h, 29h, 66h, 0Fh, 0B6h, 68h, 03h, 66h, 03h, 6Ah, 06h, 66h, 89h, 69h
    db 02h, 66h, 0Fh, 0B6h, 68h, 04h, 66h, 03h, 6Ah, 08h, 66h, 89h, 69h, 04h, 66h, 0Fh
    db 0B6h, 68h, 05h, 66h, 03h, 6Ah, 0Ah, 66h, 89h, 69h, 06h, 66h, 0Fh, 0B6h, 68h, 06h
    db 66h, 03h, 6Ah, 0Ch, 66h, 89h, 69h, 08h, 66h, 0Fh, 0B6h, 68h, 07h, 66h, 03h, 6Ah
    db 0Eh, 03h, 0C6h, 66h, 89h, 69h, 0Ah, 66h, 0Fh, 0B6h, 28h, 66h, 03h, 6Ah, 10h, 66h
    db 89h, 69h, 0Ch, 66h, 0Fh, 0B6h, 68h, 01h, 66h, 03h, 6Ah, 12h, 66h, 89h, 69h, 0Eh
    db 66h, 0Fh, 0B6h, 68h, 02h, 66h, 03h, 6Ah, 14h, 66h, 89h, 69h, 10h, 66h, 0Fh, 0B6h
    db 68h, 03h, 66h, 03h, 6Ah, 16h, 66h, 89h, 69h, 12h, 66h, 0Fh, 0B6h, 68h, 04h, 66h
    db 03h, 6Ah, 18h, 66h, 89h, 69h, 14h, 66h, 0Fh, 0B6h, 68h, 05h, 66h, 03h, 6Ah, 1Ah
    db 66h, 89h, 69h, 16h, 66h, 0Fh, 0B6h, 68h, 06h, 66h, 03h, 6Ah, 1Ch, 66h, 89h, 69h
    db 18h, 66h, 0Fh, 0B6h, 68h, 07h, 66h, 03h, 6Ah, 1Eh, 03h, 0C6h, 66h, 89h, 69h, 1Ah
    db 66h, 0Fh, 0B6h, 28h, 66h, 03h, 6Ah, 20h, 66h, 89h, 69h, 1Ch, 66h, 0Fh, 0B6h, 68h
    db 01h, 66h, 03h, 6Ah, 22h, 66h, 89h, 69h, 1Eh, 66h, 0Fh, 0B6h, 68h, 02h, 66h, 03h
    db 6Ah, 24h, 66h, 89h, 69h, 20h, 66h, 0Fh, 0B6h, 68h, 03h, 66h, 03h, 6Ah, 26h, 66h
    db 89h, 69h, 22h, 66h, 0Fh, 0B6h, 68h, 04h, 66h, 03h, 6Ah, 28h, 66h, 89h, 69h, 24h
    db 66h, 0Fh, 0B6h, 68h, 05h, 66h, 03h, 6Ah, 2Ah, 66h, 89h, 69h, 26h, 66h, 0Fh, 0B6h
    db 68h, 06h, 66h, 03h, 6Ah, 2Ch, 66h, 89h, 69h, 28h, 66h, 0Fh, 0B6h, 68h, 07h, 66h
    db 03h, 6Ah, 2Eh, 03h, 0C6h, 66h, 89h, 69h, 2Ah, 66h, 0Fh, 0B6h, 28h, 66h, 03h, 6Ah
    db 30h, 66h, 89h, 69h, 2Ch, 66h, 0Fh, 0B6h, 68h, 01h, 66h, 03h, 6Ah, 32h, 66h, 89h
    db 69h, 2Eh, 66h, 0Fh, 0B6h, 68h, 02h, 66h, 03h, 6Ah, 34h, 83h, 0C2h, 40h, 66h, 89h
    db 69h, 30h, 66h, 0Fh, 0B6h, 68h, 03h, 66h, 03h, 6Ah, 0F6h, 83h, 0C1h, 40h, 66h, 89h
    db 69h, 0F2h, 66h, 0Fh, 0B6h, 68h, 04h, 66h, 03h, 6Ah, 0F8h, 66h, 89h, 69h, 0F4h, 66h
    db 0Fh, 0B6h, 68h, 05h, 66h, 03h, 6Ah, 0FAh, 66h, 89h, 69h, 0F6h, 66h, 0Fh, 0B6h, 68h
    db 06h, 66h, 03h, 6Ah, 0FCh, 66h, 89h, 69h, 0F8h, 66h, 0Fh, 0B6h, 68h, 07h, 66h, 03h
    db 6Ah, 0FEh, 03h, 0C6h, 4Fh, 66h, 89h, 69h, 0FAh, 0Fh, 85h, 51h, 0FEh, 0FFh, 0FFh, 8Bh
    db 44h, 24h, 18h, 6Ah, 08h, 56h, 53h, 50h, 0E8h, 53h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 10h
    db 5Fh, 5Eh, 5Dh, 5Bh, 0C3h
?d_009c4e90@@YAXXZ ENDP

; retail @ 0x009C5360 size 308
public ?d_009c5360@@YAXXZ
?d_009c5360@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 4Ch, 24h, 08h, 56h, 57h, 8Bh, 0F0h, 0BAh, 02h, 00h, 00h
    db 00h, 66h, 8Bh, 39h, 66h, 01h, 38h, 66h, 8Bh, 79h, 02h, 66h, 01h, 78h, 02h, 66h
    db 8Bh, 79h, 04h, 66h, 01h, 78h, 04h, 66h, 8Bh, 79h, 06h, 66h, 01h, 78h, 06h, 66h
    db 8Bh, 79h, 08h, 66h, 01h, 78h, 08h, 66h, 8Bh, 79h, 0Ah, 66h, 01h, 78h, 0Ah, 66h
    db 8Bh, 79h, 0Ch, 66h, 01h, 78h, 0Ch, 66h, 8Bh, 79h, 0Eh, 66h, 01h, 78h, 0Eh, 66h
    db 8Bh, 79h, 10h, 66h, 01h, 78h, 10h, 66h, 8Bh, 79h, 12h, 66h, 01h, 78h, 12h, 66h
    db 8Bh, 79h, 14h, 66h, 01h, 78h, 14h, 66h, 8Bh, 79h, 16h, 66h, 01h, 78h, 16h, 66h
    db 8Bh, 79h, 18h, 66h, 01h, 78h, 18h, 66h, 8Bh, 79h, 1Ah, 66h, 01h, 78h, 1Ah, 66h
    db 8Bh, 79h, 1Ch, 66h, 01h, 78h, 1Ch, 66h, 8Bh, 79h, 1Eh, 66h, 01h, 78h, 1Eh, 66h
    db 8Bh, 79h, 20h, 66h, 01h, 78h, 20h, 66h, 8Bh, 79h, 22h, 66h, 01h, 78h, 22h, 66h
    db 8Bh, 79h, 24h, 66h, 01h, 78h, 24h, 66h, 8Bh, 79h, 26h, 66h, 01h, 78h, 26h, 66h
    db 8Bh, 79h, 28h, 66h, 01h, 78h, 28h, 66h, 8Bh, 79h, 2Ah, 66h, 01h, 78h, 2Ah, 66h
    db 8Bh, 79h, 2Ch, 66h, 01h, 78h, 2Ch, 66h, 8Bh, 79h, 2Eh, 66h, 01h, 78h, 2Eh, 66h
    db 8Bh, 79h, 30h, 66h, 01h, 78h, 30h, 66h, 8Bh, 79h, 32h, 66h, 01h, 78h, 32h, 66h
    db 8Bh, 79h, 34h, 66h, 01h, 78h, 34h, 66h, 8Bh, 79h, 36h, 66h, 01h, 78h, 36h, 66h
    db 8Bh, 79h, 38h, 66h, 01h, 78h, 38h, 66h, 8Bh, 79h, 3Ah, 66h, 01h, 78h, 3Ah, 66h
    db 8Bh, 79h, 3Ch, 66h, 01h, 78h, 3Ch, 66h, 8Bh, 79h, 3Eh, 66h, 01h, 78h, 3Eh, 83h
    db 0C0h, 40h, 83h, 0C1h, 40h, 4Ah, 0Fh, 85h, 0F5h, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h, 18h
    db 8Bh, 4Ch, 24h, 14h, 6Ah, 08h, 50h, 56h, 51h, 0E8h, 32h, 0F8h, 0FFh, 0FFh, 83h, 0C4h
    db 10h, 5Fh, 5Eh, 0C3h
?d_009c5360@@YAXXZ ENDP

; retail @ 0x009C5D60 size 1529
_TEXT ENDS
_TEXT$d00dc5d60 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DC5D60 size 1529
public ?d_009c5d60@@YAXXZ
?d_009c5d60@@YAXXZ PROC
    db 08Bh, 04Ch, 024h, 004h, 08Bh, 054h, 024h, 008h, 081h, 0ECh, 018h, 001h, 000h, 000h, 053h, 055h
    db 056h, 057h, 08Dh, 044h, 024h, 028h, 050h, 051h, 052h
    call ?Rva009C5CA0@@YAXPAF0PAH@Z
    db 08Bh, 05Ch, 024h, 034h, 08Bh, 04Ch, 024h, 038h, 08Bh, 07Ch, 024h, 03Ch, 08Bh, 044h, 024h, 040h
    db 08Bh, 0D3h, 00Bh, 0D1h, 00Bh, 0D7h, 083h, 0C4h, 00Ch, 00Bh, 0D0h, 00Fh, 084h, 0E9h, 000h, 000h
    db 000h, 08Bh, 0F0h, 069h, 0C0h, 03Ah, 08Eh, 000h, 000h, 069h, 0DBh, 005h, 0B5h, 000h, 000h, 08Bh
    db 0D1h, 069h, 0F6h, 0DBh, 0D4h, 000h, 000h, 069h, 0C9h, 0F1h, 031h, 000h, 000h, 0C1h, 0F8h, 010h
    db 069h, 0D2h, 015h, 0FBh, 000h, 000h, 0F7h, 0D8h, 089h, 044h, 024h, 010h, 0C1h, 0FAh, 010h, 0C1h
    db 0FEh, 010h, 08Bh, 0C2h, 02Bh, 0C6h, 003h, 0F2h, 069h, 0C0h, 005h, 0B5h, 000h, 000h, 08Bh, 054h
    db 024h, 010h, 0C1h, 0F9h, 010h, 089h, 074h, 024h, 014h, 08Bh, 0E9h, 02Bh, 04Ch, 024h, 010h, 08Bh
    db 0F7h, 069h, 0FFh, 0F8h, 061h, 000h, 000h, 069h, 0C9h, 005h, 0B5h, 000h, 000h, 069h, 0F6h, 083h
    db 0ECh, 000h, 000h, 0C1h, 0F8h, 010h, 003h, 0D5h, 0C1h, 0FBh, 010h, 0C1h, 0FFh, 010h, 089h, 054h
    db 024h, 018h, 08Bh, 0D3h, 08Dh, 01Ch, 010h, 089h, 07Ch, 024h, 010h, 0C1h, 0F9h, 010h, 0C1h, 0FEh
    db 010h, 08Bh, 0FAh, 02Bh, 0FEh, 003h, 0F2h, 02Bh, 0D0h, 08Bh, 044h, 024h, 010h, 08Bh, 0E9h, 003h
    db 0C8h, 08Bh, 044h, 024h, 014h, 003h, 0C6h, 00Fh, 0BFh, 0C0h, 02Bh, 06Ch, 024h, 010h, 089h, 044h
    db 024h, 028h, 02Bh, 074h, 024h, 014h, 00Fh, 0BFh, 0C6h, 089h, 044h, 024h, 044h, 08Dh, 004h, 00Bh
    db 02Bh, 0D9h, 00Fh, 0BFh, 0C0h, 00Fh, 0BFh, 0CBh, 089h, 044h, 024h, 02Ch, 08Bh, 044h, 024h, 018h
    db 089h, 04Ch, 024h, 030h, 08Dh, 00Ch, 038h, 00Fh, 0BFh, 0C9h, 02Bh, 0F8h, 00Fh, 0BFh, 0C7h, 089h
    db 04Ch, 024h, 034h, 08Dh, 00Ch, 02Ah, 089h, 044h, 024h, 038h, 00Fh, 0BFh, 0C1h, 02Bh, 0D5h, 00Fh
    db 0BFh, 0CAh, 089h, 044h, 024h, 03Ch, 089h, 04Ch, 024h, 040h, 08Bh, 05Ch, 024h, 048h, 08Bh, 04Ch
    db 024h, 04Ch, 08Bh, 07Ch, 024h, 050h, 08Bh, 044h, 024h, 054h, 08Bh, 0D3h, 00Bh, 0D1h, 00Bh, 0D7h
    db 00Bh, 0D0h, 00Fh, 084h, 0E9h, 000h, 000h, 000h, 08Bh, 0F0h, 069h, 0C0h, 03Ah, 08Eh, 000h, 000h
    db 069h, 0DBh, 005h, 0B5h, 000h, 000h, 08Bh, 0D1h, 069h, 0F6h, 0DBh, 0D4h, 000h, 000h, 069h, 0C9h
    db 0F1h, 031h, 000h, 000h, 0C1h, 0F8h, 010h, 069h, 0D2h, 015h, 0FBh, 000h, 000h, 0F7h, 0D8h, 089h
    db 044h, 024h, 010h, 0C1h, 0FAh, 010h, 0C1h, 0FEh, 010h, 08Bh, 0C2h, 02Bh, 0C6h, 003h, 0F2h, 069h
    db 0C0h, 005h, 0B5h, 000h, 000h, 08Bh, 054h, 024h, 010h, 0C1h, 0F9h, 010h, 089h, 074h, 024h, 014h
    db 08Bh, 0E9h, 02Bh, 04Ch, 024h, 010h, 08Bh, 0F7h, 069h, 0FFh, 0F8h, 061h, 000h, 000h, 069h, 0C9h
    db 005h, 0B5h, 000h, 000h, 069h, 0F6h, 083h, 0ECh, 000h, 000h, 0C1h, 0F8h, 010h, 003h, 0D5h, 0C1h
    db 0FBh, 010h, 0C1h, 0FFh, 010h, 089h, 054h, 024h, 018h, 08Bh, 0D3h, 08Dh, 01Ch, 010h, 089h, 07Ch
    db 024h, 010h, 0C1h, 0F9h, 010h, 0C1h, 0FEh, 010h, 08Bh, 0FAh, 02Bh, 0FEh, 003h, 0F2h, 02Bh, 0D0h
    db 08Bh, 044h, 024h, 010h, 08Bh, 0E9h, 003h, 0C8h, 08Bh, 044h, 024h, 014h, 003h, 0C6h, 00Fh, 0BFh
    db 0C0h, 02Bh, 06Ch, 024h, 010h, 089h, 044h, 024h, 048h, 02Bh, 074h, 024h, 014h, 00Fh, 0BFh, 0C6h
    db 089h, 044h, 024h, 064h, 08Dh, 004h, 00Bh, 02Bh, 0D9h, 00Fh, 0BFh, 0C0h, 00Fh, 0BFh, 0CBh, 089h
    db 044h, 024h, 04Ch, 08Bh, 044h, 024h, 018h, 089h, 04Ch, 024h, 050h, 08Dh, 00Ch, 038h, 00Fh, 0BFh
    db 0C9h, 02Bh, 0F8h, 00Fh, 0BFh, 0C7h, 089h, 04Ch, 024h, 054h, 08Dh, 00Ch, 02Ah, 089h, 044h, 024h
    db 058h, 00Fh, 0BFh, 0C1h, 02Bh, 0D5h, 00Fh, 0BFh, 0CAh, 089h, 044h, 024h, 05Ch, 089h, 04Ch, 024h
    db 060h, 08Bh, 05Ch, 024h, 068h, 08Bh, 04Ch, 024h, 06Ch, 08Bh, 07Ch, 024h, 070h, 08Bh, 044h, 024h
    db 074h, 08Bh, 0D3h, 00Bh, 0D1h, 00Bh, 0D7h, 00Bh, 0D0h, 00Fh, 084h, 0EFh, 000h, 000h, 000h, 08Bh
    db 0F0h, 069h, 0C0h, 03Ah, 08Eh, 000h, 000h, 069h, 0DBh, 005h, 0B5h, 000h, 000h, 08Bh, 0D1h, 069h
    db 0F6h, 0DBh, 0D4h, 000h, 000h, 069h, 0C9h, 0F1h, 031h, 000h, 000h, 0C1h, 0F8h, 010h, 069h, 0D2h
    db 015h, 0FBh, 000h, 000h, 0F7h, 0D8h, 089h, 044h, 024h, 010h, 0C1h, 0FAh, 010h, 0C1h, 0FEh, 010h
    db 08Bh, 0C2h, 02Bh, 0C6h, 003h, 0F2h, 069h, 0C0h, 005h, 0B5h, 000h, 000h, 08Bh, 054h, 024h, 010h
    db 0C1h, 0F9h, 010h, 089h, 074h, 024h, 014h, 08Bh, 0E9h, 02Bh, 04Ch, 024h, 010h, 08Bh, 0F7h, 069h
    db 0FFh, 0F8h, 061h, 000h, 000h, 069h, 0C9h, 005h, 0B5h, 000h, 000h, 069h, 0F6h, 083h, 0ECh, 000h
    db 000h, 0C1h, 0F8h, 010h, 003h, 0D5h, 0C1h, 0FBh, 010h, 0C1h, 0FFh, 010h, 089h, 054h, 024h, 018h
    db 08Bh, 0D3h, 08Dh, 01Ch, 010h, 089h, 07Ch, 024h, 010h, 0C1h, 0F9h, 010h, 0C1h, 0FEh, 010h, 08Bh
    db 0FAh, 02Bh, 0FEh, 003h, 0F2h, 02Bh, 0D0h, 08Bh, 044h, 024h, 010h, 08Bh, 0E9h, 003h, 0C8h, 08Bh
    db 044h, 024h, 014h, 003h, 0C6h, 00Fh, 0BFh, 0C0h, 02Bh, 06Ch, 024h, 010h, 089h, 044h, 024h, 068h
    db 02Bh, 074h, 024h, 014h, 00Fh, 0BFh, 0C6h, 089h, 084h, 024h, 084h, 000h, 000h, 000h, 08Dh, 004h
    db 00Bh, 02Bh, 0D9h, 00Fh, 0BFh, 0C0h, 00Fh, 0BFh, 0CBh, 089h, 044h, 024h, 06Ch, 08Bh, 044h, 024h
    db 018h, 089h, 04Ch, 024h, 070h, 08Dh, 00Ch, 038h, 00Fh, 0BFh, 0C9h, 02Bh, 0F8h, 00Fh, 0BFh, 0C7h
    db 089h, 04Ch, 024h, 074h, 08Dh, 00Ch, 02Ah, 089h, 044h, 024h, 078h, 00Fh, 0BFh, 0C1h, 02Bh, 0D5h
    db 00Fh, 0BFh, 0CAh, 089h, 044h, 024h, 07Ch, 089h, 08Ch, 024h, 080h, 000h, 000h, 000h, 08Bh, 09Ch
    db 024h, 088h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0BCh, 024h, 090h
    db 000h, 000h, 000h, 08Bh, 084h, 024h, 094h, 000h, 000h, 000h, 08Bh, 0D3h, 00Bh, 0D1h, 00Bh, 0D7h
    db 00Bh, 0D0h, 00Fh, 084h, 001h, 001h, 000h, 000h, 08Bh, 0F0h, 069h, 0C0h, 03Ah, 08Eh, 000h, 000h
    db 069h, 0DBh, 005h, 0B5h, 000h, 000h, 08Bh, 0D1h, 069h, 0F6h, 0DBh, 0D4h, 000h, 000h, 069h, 0C9h
    db 0F1h, 031h, 000h, 000h, 0C1h, 0F8h, 010h, 069h, 0D2h, 015h, 0FBh, 000h, 000h, 0F7h, 0D8h, 089h
    db 044h, 024h, 010h, 0C1h, 0FAh, 010h, 0C1h, 0FEh, 010h, 08Bh, 0C2h, 02Bh, 0C6h, 003h, 0F2h, 069h
    db 0C0h, 005h, 0B5h, 000h, 000h, 08Bh, 054h, 024h, 010h, 0C1h, 0F9h, 010h, 089h, 074h, 024h, 014h
    db 08Bh, 0E9h, 02Bh, 04Ch, 024h, 010h, 08Bh, 0F7h, 069h, 0FFh, 0F8h, 061h, 000h, 000h, 069h, 0C9h
    db 005h, 0B5h, 000h, 000h, 069h, 0F6h, 083h, 0ECh, 000h, 000h, 0C1h, 0F8h, 010h, 003h, 0D5h, 0C1h
    db 0FBh, 010h, 0C1h, 0FFh, 010h, 089h, 054h, 024h, 018h, 08Bh, 0D3h, 08Dh, 01Ch, 010h, 089h, 07Ch
    db 024h, 010h, 0C1h, 0F9h, 010h, 0C1h, 0FEh, 010h, 08Bh, 0FAh, 02Bh, 0FEh, 003h, 0F2h, 02Bh, 0D0h
    db 08Bh, 044h, 024h, 010h, 08Bh, 0E9h, 003h, 0C8h, 08Bh, 044h, 024h, 014h, 003h, 0C6h, 00Fh, 0BFh
    db 0C0h, 02Bh, 06Ch, 024h, 010h, 089h, 084h, 024h, 088h, 000h, 000h, 000h, 02Bh, 074h, 024h, 014h
    db 00Fh, 0BFh, 0C6h, 089h, 084h, 024h, 0A4h, 000h, 000h, 000h, 08Dh, 004h, 00Bh, 02Bh, 0D9h, 00Fh
    db 0BFh, 0C0h, 00Fh, 0BFh, 0CBh, 089h, 084h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 044h, 024h, 018h
    db 089h, 08Ch, 024h, 090h, 000h, 000h, 000h, 08Dh, 00Ch, 038h, 00Fh, 0BFh, 0C9h, 02Bh, 0F8h, 00Fh
    db 0BFh, 0C7h, 089h, 08Ch, 024h, 094h, 000h, 000h, 000h, 08Dh, 00Ch, 02Ah, 089h, 084h, 024h, 098h
    db 000h, 000h, 000h, 00Fh, 0BFh, 0C1h, 02Bh, 0D5h, 00Fh, 0BFh, 0CAh, 089h, 084h, 024h, 09Ch, 000h
    db 000h, 000h, 089h, 08Ch, 024h, 0A0h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 034h, 001h, 000h, 000h
    db 08Dh, 0ACh, 024h, 088h, 000h, 000h, 000h, 083h, 0C1h, 010h, 089h, 06Ch, 024h, 01Ch, 0C7h, 044h
    db 024h, 020h, 008h, 000h, 000h, 000h, 033h, 0C0h, 08Bh, 075h, 0A0h, 08Bh, 055h, 000h, 08Bh, 05Dh
    db 0C0h, 08Bh, 07Dh, 0E0h, 00Bh, 0D6h, 00Bh, 0D3h, 00Bh, 0D7h, 00Fh, 084h, 018h, 001h, 000h, 000h
    db 08Bh, 0C3h, 069h, 0F6h, 005h, 0B5h, 000h, 000h, 08Bh, 0F8h, 069h, 0C0h, 0F1h, 031h, 000h, 000h
    db 0C1h, 0F8h, 010h, 069h, 0FFh, 015h, 0FBh, 000h, 000h, 089h, 044h, 024h, 018h, 08Bh, 045h, 000h
    db 08Bh, 0D8h, 069h, 0C0h, 03Ah, 08Eh, 000h, 000h, 069h, 0DBh, 0DBh, 0D4h, 000h, 000h, 0C1h, 0FFh
    db 010h, 0C1h, 0FBh, 010h, 0C1h, 0F8h, 010h, 08Bh, 0D7h, 02Bh, 0D3h, 003h, 0DFh, 069h, 0D2h, 005h
    db 0B5h, 000h, 000h, 0F7h, 0D8h, 089h, 044h, 024h, 010h, 08Bh, 07Ch, 024h, 010h, 08Bh, 044h, 024h
    db 018h, 02Bh, 044h, 024h, 010h, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 018h, 069h, 0C0h, 005h
    db 0B5h, 000h, 000h, 003h, 0FBh, 08Bh, 05Dh, 0E0h, 089h, 07Ch, 024h, 018h, 08Bh, 0FBh, 069h, 0DBh
    db 0F8h, 061h, 000h, 000h, 0C1h, 0FBh, 010h, 069h, 0FFh, 083h, 0ECh, 000h, 000h, 0C1h, 0F8h, 010h
    db 089h, 05Ch, 024h, 010h, 08Bh, 06Ch, 024h, 010h, 08Bh, 0D8h, 02Bh, 0DDh, 089h, 05Ch, 024h, 024h
    db 0C1h, 0FFh, 010h, 0C1h, 0FAh, 010h, 0C1h, 0FEh, 010h, 08Bh, 0DDh, 003h, 0D8h, 08Dh, 06Ch, 032h
    db 008h, 089h, 05Ch, 024h, 010h, 08Dh, 05Ch, 037h, 008h, 08Bh, 0C6h, 02Bh, 0C7h, 02Bh, 0F2h, 08Bh
    db 054h, 024h, 014h, 08Dh, 03Ch, 013h, 0C1h, 0FFh, 004h, 02Bh, 0DAh, 08Bh, 054h, 024h, 010h, 066h
    db 089h, 079h, 0F0h, 08Dh, 03Ch, 02Ah, 02Bh, 0EAh, 08Bh, 054h, 024h, 018h, 083h, 0C0h, 008h, 0C1h
    db 0FFh, 004h, 066h, 089h, 039h, 08Dh, 03Ch, 010h, 02Bh, 0C2h, 0C1h, 0F8h, 004h, 083h, 0C6h, 008h
    db 066h, 089h, 041h, 030h, 08Bh, 044h, 024h, 024h, 08Dh, 014h, 006h, 02Bh, 0F0h, 0C1h, 0FBh, 004h
    db 0C1h, 0FDh, 004h, 0C1h, 0FFh, 004h, 0C1h, 0FAh, 004h, 0C1h, 0FEh, 004h, 066h, 089h, 059h, 060h
    db 066h, 089h, 069h, 010h, 066h, 089h, 079h, 020h, 066h, 089h, 051h, 040h, 066h, 089h, 071h, 050h
    db 033h, 0C0h, 08Bh, 06Ch, 024h, 01Ch, 0EBh, 01Fh, 066h, 089h, 041h, 0F0h, 066h, 089h, 041h, 060h
    db 066h, 089h, 001h, 066h, 089h, 041h, 010h, 066h, 089h, 041h, 020h, 066h, 089h, 041h, 030h, 066h
    db 089h, 041h, 040h, 066h, 089h, 041h, 050h, 08Bh, 054h, 024h, 020h, 083h, 0C5h, 004h, 083h, 0C1h
    db 002h, 04Ah, 089h, 06Ch, 024h, 01Ch, 089h, 054h, 024h, 020h, 00Fh, 085h, 098h, 0FEh, 0FFh, 0FFh
    db 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 018h, 001h, 000h, 000h, 0C3h
?d_009c5d60@@YAXXZ ENDP
_TEXT$d00dc5d60 ENDS
_TEXT SEGMENT

; retail @ 0x009C6360 size 48
public ?d_009c6360@@YAXXZ
?d_009c6360@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 0Fh, 0BFh, 11h, 8Bh, 44h, 24h, 04h, 0Fh, 0BFh, 00h, 0Fh, 0AFh
    db 0C2h, 83h, 0C0h, 0Fh, 0C1h, 0F8h, 05h, 66h, 8Bh, 0D0h, 57h, 8Bh, 7Ch, 24h, 10h, 0B9h
    db 20h, 00h, 00h, 00h, 0C1h, 0E2h, 10h, 66h, 8Bh, 0D0h, 8Bh, 0C2h, 0F3h, 0ABh, 5Fh, 0C3h
?d_009c6360@@YAXXZ ENDP

; retail @ 0x009C6A30 size 486
public ?d_009c6a30@@YAXXZ
?d_009c6a30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 8Bh, 0D0h, 81h, 0ECh, 00h, 01h, 00h, 00h
    db 2Bh, 0D1h, 79h, 06h, 8Bh, 0D1h, 8Bh, 0C8h, 2Bh, 0D0h, 85h, 0D2h, 0Fh, 84h, 0BDh, 01h
    db 00h, 00h, 83h, 0FAh, 01h, 75h, 6Dh, 8Bh, 84h, 24h, 1Ch, 01h, 00h, 00h, 85h, 0C0h
    db 74h, 30h, 8Bh, 84h, 24h, 14h, 01h, 00h, 00h, 0C1h, 0E0h, 06h, 05h, 0E0h, 89h, 2Dh
    db 01h, 50h, 6Ah, 08h, 6Ah, 08h, 52h, 8Bh, 94h, 24h, 20h, 01h, 00h, 00h, 52h, 8Dh
    db 44h, 24h, 14h, 50h, 51h, 0E8h, 06h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 0E9h, 66h, 01h
    db 00h, 00h, 8Bh, 94h, 24h, 14h, 01h, 00h, 00h, 8Bh, 84h, 24h, 10h, 01h, 00h, 00h
    db 0C1h, 0E2h, 05h, 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 52h, 6Ah, 08h, 6Ah, 08h, 6Ah, 01h
    db 50h, 8Dh, 54h, 24h, 14h, 52h, 51h, 0E8h, 34h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 0E9h
    db 34h, 01h, 00h, 00h, 8Bh, 84h, 24h, 10h, 01h, 00h, 00h, 3Bh, 0D0h, 75h, 58h, 8Bh
    db 94h, 24h, 1Ch, 01h, 00h, 00h, 85h, 0D2h, 8Bh, 94h, 24h, 18h, 01h, 00h, 00h, 74h
    db 23h, 0C1h, 0E2h, 06h, 81h, 0C2h, 0E0h, 89h, 2Dh, 01h, 52h, 6Ah, 08h, 6Ah, 08h, 50h
    db 50h, 8Dh, 44h, 24h, 14h, 50h, 51h, 0E8h, 74h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 0E9h
    db 0F4h, 00h, 00h, 00h, 0C1h, 0E2h, 05h, 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 52h, 6Ah, 08h
    db 6Ah, 08h, 50h, 50h, 8Dh, 44h, 24h, 14h, 50h, 51h, 0E8h, 61h, 0FCh, 0FFh, 0FFh, 83h
    db 0C4h, 1Ch, 0E9h, 0D1h, 00h, 00h, 00h, 56h, 8Dh, 70h, 0FFh, 3Bh, 0D6h, 75h, 5Ch, 8Bh
    db 94h, 24h, 20h, 01h, 00h, 00h, 85h, 0D2h, 8Bh, 94h, 24h, 1Ch, 01h, 00h, 00h, 74h
    db 2Dh, 0C1h, 0E2h, 06h, 81h, 0C2h, 0E0h, 89h, 2Dh, 01h, 52h, 8Bh, 94h, 24h, 1Ch, 01h
    db 00h, 00h, 0C1h, 0E2h, 06h, 81h, 0C2h, 0E0h, 89h, 2Dh, 01h, 52h, 50h, 8Dh, 44h, 24h
    db 10h, 50h, 49h, 51h, 0E8h, 67h, 0FEh, 0FFh, 0FFh, 0E9h, 86h, 00h, 00h, 00h, 0C1h, 0E2h
    db 05h, 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 52h, 8Bh, 94h, 24h, 1Ch, 01h, 00h, 00h, 0C1h
    db 0E2h, 05h, 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 49h, 0EBh, 5Ch, 8Dh, 70h, 01h, 3Bh, 0D6h
    db 75h, 65h, 8Bh, 94h, 24h, 20h, 01h, 00h, 00h, 85h, 0D2h, 8Bh, 94h, 24h, 1Ch, 01h
    db 00h, 00h, 74h, 29h, 0C1h, 0E2h, 06h, 81h, 0C2h, 0E0h, 89h, 2Dh, 01h, 52h, 8Bh, 94h
    db 24h, 1Ch, 01h, 00h, 00h, 0C1h, 0E2h, 06h, 81h, 0C2h, 0E0h, 89h, 2Dh, 01h, 52h, 50h
    db 8Dh, 44h, 24h, 10h, 50h, 51h, 0E8h, 05h, 0FEh, 0FFh, 0FFh, 0EBh, 27h, 0C1h, 0E2h, 05h
    db 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 52h, 8Bh, 94h, 24h, 1Ch, 01h, 00h, 00h, 0C1h, 0E2h
    db 05h, 81h, 0C2h, 0E0h, 88h, 2Dh, 01h, 52h, 50h, 8Dh, 44h, 24h, 10h, 50h, 51h, 0E8h
    db 0Ch, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Eh, 8Bh, 8Ch, 24h, 0Ch, 01h, 00h, 00h, 6Ah
    db 08h, 51h, 8Dh, 54h, 24h, 08h, 52h, 0E8h, 34h, 02h, 00h, 00h, 83h, 0C4h, 0Ch, 81h
    db 0C4h, 00h, 01h, 00h, 00h, 0C3h
?d_009c6a30@@YAXXZ ENDP

; retail @ 0x009C7380 size 204
public ?d_009c7380@@YAXXZ
?d_009c7380@@YAXXZ PROC
    db 8Bh, 54h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 8Bh, 0C2h, 2Bh, 0C1h, 79h, 06h, 8Bh, 0C1h
    db 8Bh, 0CAh, 2Bh, 0C2h, 83h, 0F8h, 01h, 8Bh, 54h, 24h, 10h, 75h, 23h, 8Bh, 44h, 24h
    db 14h, 0C1h, 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h, 50h, 8Bh, 44h, 24h, 10h, 6Ah, 08h
    db 6Ah, 08h, 6Ah, 01h, 52h, 50h, 51h, 0E8h, 0A4h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 1Ch, 0C3h
    db 3Bh, 0C2h, 75h, 22h, 8Bh, 44h, 24h, 18h, 0C1h, 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h
    db 50h, 6Ah, 08h, 6Ah, 08h, 52h, 52h, 8Bh, 54h, 24h, 20h, 52h, 51h, 0E8h, 0EEh, 0FCh
    db 0FFh, 0FFh, 83h, 0C4h, 1Ch, 0C3h, 56h, 8Dh, 72h, 0FFh, 3Bh, 0C6h, 75h, 2Ch, 8Bh, 44h
    db 24h, 1Ch, 0C1h, 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h, 50h, 8Bh, 44h, 24h, 1Ch, 0C1h
    db 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h, 50h, 52h, 8Bh, 54h, 24h, 1Ch, 49h, 52h, 51h
    db 0E8h, 2Bh, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Eh, 0C3h, 8Dh, 72h, 01h, 3Bh, 0C6h, 75h
    db 29h, 8Bh, 44h, 24h, 1Ch, 0C1h, 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h, 50h, 8Bh, 44h
    db 24h, 1Ch, 0C1h, 0E0h, 05h, 05h, 10h, 8Ch, 2Dh, 01h, 50h, 52h, 8Bh, 54h, 24h, 1Ch
    db 52h, 51h, 0E8h, 0F9h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Eh, 0C3h
?d_009c7380@@YAXXZ ENDP

; retail @ 0x009C80C0 size 98
public ?d_009c80c0@@YAXXZ
?d_009c80c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 0BAh, 0Fh, 00h, 00h, 00h, 66h, 0Fh, 6Eh, 0D2h, 8Bh, 4Ch, 24h
    db 08h, 8Bh, 54h, 24h, 0Ch, 0F3h, 0Fh, 7Eh, 00h, 0F3h, 0Fh, 7Eh, 09h, 66h, 0Fh, 0D5h
    db 0C1h, 66h, 0Fh, 0FDh, 0C2h, 66h, 0Fh, 71h, 0E0h, 05h, 66h, 0Fh, 61h, 0C0h, 66h, 0Fh
    db 62h, 0C0h, 66h, 0Fh, 6Ch, 0C0h, 66h, 0Fh, 6Fh, 0C8h, 66h, 0Fh, 7Fh, 02h, 66h, 0Fh
    db 7Fh, 4Ah, 10h, 66h, 0Fh, 7Fh, 42h, 20h, 66h, 0Fh, 7Fh, 4Ah, 30h, 66h, 0Fh, 7Fh
    db 42h, 40h, 66h, 0Fh, 7Fh, 4Ah, 50h, 66h, 0Fh, 7Fh, 42h, 60h, 66h, 0Fh, 7Fh, 4Ah
    db 70h, 0C3h
?d_009c80c0@@YAXXZ ENDP

; retail @ 0x009C85C0 size 59
public ?d_009c85c0@@YAXXZ
?d_009c85c0@@YAXXZ PROC
    db 0C7h, 01h, 0F8h, 39h, 14h, 01h, 8Bh, 0Dh, 60h, 0D0h, 34h, 01h, 85h, 0C9h, 74h, 06h
    db 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 0Dh, 50h, 0CCh, 34h, 01h, 85h, 0C9h, 0C7h, 05h
    db 60h, 0D0h, 34h, 01h, 00h, 00h, 00h, 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h
    db 0C7h, 05h, 50h, 0CCh, 34h, 01h, 00h, 00h, 00h, 00h, 0C3h
?d_009c85c0@@YAXXZ ENDP

; retail @ 0x009C8680 size 27
public ?d_009c8680@@YAXXZ
?d_009c8680@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 0BAh, 48h, 0C9h, 34h, 01h, 2Bh, 0D0h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Ah, 08h, 88h, 0Ch, 02h, 40h, 84h, 0C9h, 75h, 0F6h, 0C3h
?d_009c8680@@YAXXZ ENDP

; retail @ 0x009C8F40 size 50
public ?d_009c8f40@@YAXXZ
?d_009c8f40@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 27h, 8Bh, 44h, 24h, 08h, 8Dh, 04h, 40h, 0C1h
    db 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Ch, 51h, 0E8h, 51h, 8Fh, 0EBh, 0FFh, 83h
    db 0C4h, 04h, 0C2h, 08h, 00h, 50h, 51h, 0E8h, 84h, 56h, 0E6h, 0FFh, 83h, 0C4h, 08h, 0C2h
    db 08h, 00h
?d_009c8f40@@YAXXZ ENDP

; retail @ 0x009C91C0 size 50
public ?d_009c91c0@@YAXXZ
?d_009c91c0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 27h, 8Bh, 44h, 24h, 08h, 8Dh, 04h, 40h, 0C1h
    db 0E0h, 04h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Ch, 51h, 0E8h, 0D1h, 8Ch, 0EBh, 0FFh, 83h
    db 0C4h, 04h, 0C2h, 08h, 00h, 50h, 51h, 0E8h, 04h, 54h, 0E6h, 0FFh, 83h, 0C4h, 08h, 0C2h
    db 08h, 00h
?d_009c91c0@@YAXXZ ENDP

; retail @ 0x009C9310 size 49
public ?d_009c9310@@YAXXZ
?d_009c9310@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 24h, 8Dh, 04h, 40h, 0C1h, 0E0h, 04h, 3Dh, 80h
    db 00h, 00h, 00h, 50h, 76h, 0Bh, 0E8h, 05h, 8Ch, 0EBh, 0FFh, 83h, 0C4h, 04h, 0C2h, 08h
    db 00h, 0E8h, 0Ah, 52h, 0E6h, 0FFh, 83h, 0C4h, 04h, 0C2h, 08h, 00h, 33h, 0C0h, 0C2h, 08h
    db 00h
?d_009c9310@@YAXXZ ENDP

; retail @ 0x009C9490 size 35
public ?d_009c9490@@YAXXZ
?d_009c9490@@YAXXZ PROC
    db 51h, 56h, 6Ah, 00h, 8Dh, 44h, 24h, 0Bh, 50h, 8Bh, 0F1h, 0E8h, 0B0h, 0FEh, 0FFh, 0FFh
    db 6Ah, 18h, 0E8h, 99h, 50h, 0E6h, 0FFh, 89h, 06h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_009c9490@@YAXXZ ENDP

; retail @ 0x009CA000 size 21
public ?d_009ca000@@YAXXZ
?d_009ca000@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 96h, 0FAh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca000@@YAXXZ ENDP

; retail @ 0x009CA020 size 21
public ?d_009ca020@@YAXXZ
?d_009ca020@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 76h, 0FAh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca020@@YAXXZ ENDP

; retail @ 0x009CA040 size 21
public ?d_009ca040@@YAXXZ
?d_009ca040@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 26h, 0FBh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca040@@YAXXZ ENDP

; retail @ 0x009CA070 size 21
public ?d_009ca070@@YAXXZ
?d_009ca070@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 26h, 0FAh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca070@@YAXXZ ENDP

; retail @ 0x009CA090 size 21
public ?d_009ca090@@YAXXZ
?d_009ca090@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 06h, 0FAh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca090@@YAXXZ ENDP

; retail @ 0x009CA0F0 size 21
public ?d_009ca0f0@@YAXXZ
?d_009ca0f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 76h, 0FAh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca0f0@@YAXXZ ENDP

; retail @ 0x009CA440 size 21
public ?d_009ca440@@YAXXZ
?d_009ca440@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 50h, 0E8h, 96h, 0F8h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 04h, 89h, 01h
    db 8Bh, 0C1h, 0C2h, 08h, 00h
?d_009ca440@@YAXXZ ENDP

; retail @ 0x009CBA60 size 53
public ?d_009cba60@@YAXXZ
?d_009cba60@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 24h, 8Bh, 44h, 24h, 08h, 0C1h, 0E0h, 03h, 3Dh
    db 80h, 00h, 00h, 00h, 76h, 0Ch, 51h, 0E8h, 34h, 64h, 0EBh, 0FFh, 83h, 0C4h, 04h, 0C2h
    db 08h, 00h, 50h, 51h, 0E8h, 67h, 2Bh, 0E6h, 0FFh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 0CCh
    db 8Bh, 0C1h, 0C2h, 04h, 00h
?d_009cba60@@YAXXZ ENDP

; retail @ 0x009CBCC0 size 37
public ?d_009cbcc0@@YAXXZ
?d_009cbcc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 6Ah, 00h, 50h, 8Dh, 4Eh, 08h, 0C7h, 06h, 00h
    db 00h, 00h, 00h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0E8h, 21h, 0FFh, 0FFh, 0FFh, 8Bh
    db 0C6h, 5Eh, 0C2h, 04h, 00h
?d_009cbcc0@@YAXXZ ENDP

; retail @ 0x009CBD90 size 45
public ?d_009cbd90@@YAXXZ
?d_009cbd90@@YAXXZ PROC
    db 8Bh, 11h, 85h, 0D2h, 74h, 26h, 8Bh, 41h, 08h, 2Bh, 0C2h, 0C1h, 0F8h, 03h, 0C1h, 0E0h
    db 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Ah, 52h, 0E8h, 02h, 61h, 0EBh, 0FFh, 83h, 0C4h
    db 04h, 0C3h, 50h, 52h, 0E8h, 37h, 28h, 0E6h, 0FFh, 83h, 0C4h, 08h, 0C3h
?d_009cbd90@@YAXXZ ENDP

; retail @ 0x009CBFA0 size 58
public ?d_009cbfa0@@YAXXZ
?d_009cbfa0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 3Bh, 41h, 08h, 74h, 1Bh, 85h, 0C0h, 74h, 10h, 8Bh, 54h, 24h, 04h
    db 56h, 8Bh, 32h, 89h, 30h, 8Bh, 52h, 04h, 89h, 50h, 04h, 5Eh, 83h, 41h, 04h, 08h
    db 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 0Ch, 52h, 8Bh, 54h, 24h, 10h
    db 52h, 50h, 0E8h, 39h, 0FEh, 0FFh, 0FFh, 0C2h, 04h, 00h
?d_009cbfa0@@YAXXZ ENDP
_TEXT ENDS
END
