.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?g_bfmeSubB3@@3NA:BYTE
EXTERN ?g_rva01356A9C@@3PAHA:BYTE
EXTERN __ftol2:NEAR
EXTERN __imp__rand:BYTE
EXTERN __real@3f8a01a01a01a01a:BYTE
EXTERN __real@3fe0000000000000:BYTE
EXTERN __real@401921fb53c8d4f1:BYTE
EXTERN __real@4040000000000000:BYTE
EXTERN __real@4070000000000000:BYTE
EXTERN __real@c040000000000000:BYTE
EXTERN g_Va012D86C0:BYTE
EXTERN g_Va012D86D0:BYTE
EXTERN g_Va012D86E0:BYTE
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x00968910 size 860
public ?d_00968910@@YAXXZ
?d_00968910@@YAXXZ PROC
    db 81h, 0ECh, 0C0h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h
    db 8Bh, 0CEh, 0FFh, 50h, 20h, 8Bh, 46h, 08h, 83h, 0C0h, 10h, 8Bh, 0C8h, 83h, 0E9h, 02h
    db 0Fh, 84h, 5Dh, 02h, 00h, 00h, 49h, 0Fh, 84h, 6Fh, 01h, 00h, 00h, 81h, 0E9h, 0FDh
    db 00h, 00h, 00h, 0Fh, 84h, 0B5h, 00h, 00h, 00h, 8Bh, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh
    db 54h, 24h, 04h, 41h, 89h, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh, 4Ch, 24h, 14h, 89h, 4Ch
    db 24h, 48h, 8Bh, 4Ch, 24h, 34h, 89h, 54h, 24h, 44h, 8Bh, 54h, 24h, 24h, 89h, 4Ch
    db 24h, 50h, 8Bh, 4Ch, 24h, 18h, 89h, 54h, 24h, 4Ch, 8Bh, 54h, 24h, 08h, 89h, 4Ch
    db 24h, 58h, 8Bh, 4Ch, 24h, 38h, 89h, 54h, 24h, 54h, 8Bh, 54h, 24h, 28h, 89h, 4Ch
    db 24h, 60h, 8Bh, 4Ch, 24h, 1Ch, 89h, 54h, 24h, 5Ch, 8Bh, 54h, 24h, 0Ch, 89h, 4Ch
    db 24h, 68h, 8Bh, 4Ch, 24h, 3Ch, 89h, 54h, 24h, 64h, 8Bh, 54h, 24h, 2Ch, 89h, 4Ch
    db 24h, 70h, 8Bh, 4Ch, 24h, 20h, 57h, 89h, 54h, 24h, 70h, 8Bh, 54h, 24h, 14h, 89h
    db 4Ch, 24h, 7Ch, 8Bh, 4Ch, 24h, 44h, 89h, 54h, 24h, 78h, 8Bh, 54h, 24h, 34h, 8Dh
    db 7Ch, 24h, 48h, 57h, 89h, 8Ch, 24h, 88h, 00h, 00h, 00h, 8Bh, 0Dh, 34h, 05h, 34h
    db 01h, 50h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 8Bh, 11h, 51h, 0FFh, 92h, 0B0h, 00h
    db 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 5Fh, 0E9h, 44h, 02h, 00h, 00h, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h, 0Dh, 90h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 08h, 0A3h, 8Ch, 10h, 34h, 01h, 8Bh, 44h, 24h, 34h, 89h, 0Dh, 9Ch
    db 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 94h, 10h, 34h, 01h, 8Bh, 54h, 24h
    db 18h, 0A3h, 98h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h, 0Dh, 0A8h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0A0h, 10h, 34h, 01h, 8Bh, 54h, 24h, 0Ch, 0A3h, 0A4h
    db 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0B4h, 10h, 34h, 01h, 8Bh, 4Ch, 24h
    db 20h, 89h, 15h, 0ACh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch, 0A3h, 0B0h, 10h, 34h, 01h
    db 8Bh, 44h, 24h, 10h, 89h, 0Dh, 0C0h, 10h, 34h, 01h, 8Bh, 0Dh, 9Ch, 0F4h, 33h, 01h
    db 89h, 15h, 0B8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h, 0BCh, 10h, 34h, 01h, 8Bh
    db 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0FBh, 0FFh, 89h, 15h, 0C4h, 10h, 34h, 01h, 0A3h
    db 0C8h, 10h, 34h, 01h, 83h, 0C9h, 01h, 0E9h, 90h, 01h, 00h, 00h, 8Bh, 54h, 24h, 04h
    db 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 24h, 89h, 94h, 24h, 84h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 34h, 89h, 94h, 24h, 90h, 00h, 00h, 00h, 8Bh, 54h, 24h, 28h, 89h, 84h
    db 24h, 88h, 00h, 00h, 00h, 8Bh, 44h, 24h, 08h, 89h, 94h, 24h, 9Ch, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 1Ch, 89h, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h
    db 84h, 24h, 94h, 00h, 00h, 00h, 8Bh, 44h, 24h, 38h, 89h, 94h, 24h, 0A8h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 10h, 89h, 8Ch, 24h, 98h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch
    db 89h, 84h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 2Ch, 89h, 94h, 24h, 0B4h, 00h
    db 00h, 00h, 8Bh, 54h, 24h, 40h, 89h, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 3Ch, 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 89h, 94h, 24h, 0C0h
    db 00h, 00h, 00h, 8Dh, 94h, 24h, 84h, 00h, 00h, 00h, 89h, 8Ch, 24h, 0B0h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 30h, 52h, 89h, 84h, 24h, 0BCh, 00h, 00h, 00h, 0A1h, 34h, 05h
    db 34h, 01h, 6Ah, 03h, 89h, 8Ch, 24h, 0C4h, 00h, 00h, 00h, 0C7h, 05h, 00h, 05h, 34h
    db 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 98h, 0F4h, 33h, 01h, 00h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0B0h, 00h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0AFh
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h
    db 0Dh, 0D0h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 08h, 0A3h, 0CCh, 10h, 34h, 01h, 8Bh, 44h
    db 24h, 34h, 89h, 0Dh, 0DCh, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 0D4h, 10h
    db 34h, 01h, 8Bh, 54h, 24h, 18h, 0A3h, 0D8h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h
    db 0Dh, 0E8h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0E0h, 10h, 34h, 01h, 8Bh
    db 54h, 24h, 0Ch, 0A3h, 0E4h, 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0F4h, 10h
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 89h, 15h, 0ECh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch
    db 0A3h, 0F0h, 10h, 34h, 01h, 8Bh, 44h, 24h, 10h, 89h, 0Dh, 00h, 11h, 34h, 01h, 8Bh
    db 0Dh, 9Ch, 0F4h, 33h, 01h, 89h, 15h, 0F8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h
    db 0FCh, 10h, 34h, 01h, 8Bh, 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0F7h, 0FFh, 89h, 15h
    db 04h, 11h, 34h, 01h, 0A3h, 08h, 11h, 34h, 01h, 83h, 0C9h, 02h, 89h, 0Dh, 9Ch, 0F4h
    db 33h, 01h, 8Bh, 56h, 08h, 68h, 00h, 00h, 03h, 00h, 6Ah, 0Bh, 52h, 0E8h, 91h, 0D5h
    db 6Bh, 0FFh, 8Bh, 46h, 08h, 6Ah, 02h, 6Ah, 18h, 50h, 0E8h, 84h, 0D5h, 6Bh, 0FFh, 83h
    db 0C4h, 18h, 5Eh, 81h, 0C4h, 0C0h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00968910@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00969C60 size 6
public ?d_00969c60@@YAXXZ
?d_00969c60@@YAXXZ PROC
    db 0B8h, 15h, 00h, 00h, 00h, 0C3h
?d_00969c60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00969CD0 size 39
public ?d_00969cd0@@YAXXZ
?d_00969cd0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 0A2h, 0CEh, 0FFh, 0FFh, 0C7h, 06h
    db 0Ch, 0E6h, 13h, 01h, 8Bh, 47h, 30h, 89h, 46h, 30h, 5Fh, 0C7h, 06h, 30h, 0E6h, 13h
    db 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00969cd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00969D00 size 860
public ?d_00969d00@@YAXXZ
?d_00969d00@@YAXXZ PROC
    db 81h, 0ECh, 0C0h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h
    db 8Bh, 0CEh, 0FFh, 50h, 20h, 8Bh, 46h, 08h, 83h, 0C0h, 10h, 8Bh, 0C8h, 83h, 0E9h, 02h
    db 0Fh, 84h, 5Dh, 02h, 00h, 00h, 49h, 0Fh, 84h, 6Fh, 01h, 00h, 00h, 81h, 0E9h, 0FDh
    db 00h, 00h, 00h, 0Fh, 84h, 0B5h, 00h, 00h, 00h, 8Bh, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh
    db 54h, 24h, 04h, 41h, 89h, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh, 4Ch, 24h, 14h, 89h, 4Ch
    db 24h, 48h, 8Bh, 4Ch, 24h, 34h, 89h, 54h, 24h, 44h, 8Bh, 54h, 24h, 24h, 89h, 4Ch
    db 24h, 50h, 8Bh, 4Ch, 24h, 18h, 89h, 54h, 24h, 4Ch, 8Bh, 54h, 24h, 08h, 89h, 4Ch
    db 24h, 58h, 8Bh, 4Ch, 24h, 38h, 89h, 54h, 24h, 54h, 8Bh, 54h, 24h, 28h, 89h, 4Ch
    db 24h, 60h, 8Bh, 4Ch, 24h, 1Ch, 89h, 54h, 24h, 5Ch, 8Bh, 54h, 24h, 0Ch, 89h, 4Ch
    db 24h, 68h, 8Bh, 4Ch, 24h, 3Ch, 89h, 54h, 24h, 64h, 8Bh, 54h, 24h, 2Ch, 89h, 4Ch
    db 24h, 70h, 8Bh, 4Ch, 24h, 20h, 57h, 89h, 54h, 24h, 70h, 8Bh, 54h, 24h, 14h, 89h
    db 4Ch, 24h, 7Ch, 8Bh, 4Ch, 24h, 44h, 89h, 54h, 24h, 78h, 8Bh, 54h, 24h, 34h, 8Dh
    db 7Ch, 24h, 48h, 57h, 89h, 8Ch, 24h, 88h, 00h, 00h, 00h, 8Bh, 0Dh, 34h, 05h, 34h
    db 01h, 50h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 8Bh, 11h, 51h, 0FFh, 92h, 0B0h, 00h
    db 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 5Fh, 0E9h, 44h, 02h, 00h, 00h, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h, 0Dh, 90h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 08h, 0A3h, 8Ch, 10h, 34h, 01h, 8Bh, 44h, 24h, 34h, 89h, 0Dh, 9Ch
    db 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 94h, 10h, 34h, 01h, 8Bh, 54h, 24h
    db 18h, 0A3h, 98h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h, 0Dh, 0A8h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0A0h, 10h, 34h, 01h, 8Bh, 54h, 24h, 0Ch, 0A3h, 0A4h
    db 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0B4h, 10h, 34h, 01h, 8Bh, 4Ch, 24h
    db 20h, 89h, 15h, 0ACh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch, 0A3h, 0B0h, 10h, 34h, 01h
    db 8Bh, 44h, 24h, 10h, 89h, 0Dh, 0C0h, 10h, 34h, 01h, 8Bh, 0Dh, 9Ch, 0F4h, 33h, 01h
    db 89h, 15h, 0B8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h, 0BCh, 10h, 34h, 01h, 8Bh
    db 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0FBh, 0FFh, 89h, 15h, 0C4h, 10h, 34h, 01h, 0A3h
    db 0C8h, 10h, 34h, 01h, 83h, 0C9h, 01h, 0E9h, 90h, 01h, 00h, 00h, 8Bh, 54h, 24h, 04h
    db 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 24h, 89h, 94h, 24h, 84h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 34h, 89h, 94h, 24h, 90h, 00h, 00h, 00h, 8Bh, 54h, 24h, 28h, 89h, 84h
    db 24h, 88h, 00h, 00h, 00h, 8Bh, 44h, 24h, 08h, 89h, 94h, 24h, 9Ch, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 1Ch, 89h, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h
    db 84h, 24h, 94h, 00h, 00h, 00h, 8Bh, 44h, 24h, 38h, 89h, 94h, 24h, 0A8h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 10h, 89h, 8Ch, 24h, 98h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch
    db 89h, 84h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 2Ch, 89h, 94h, 24h, 0B4h, 00h
    db 00h, 00h, 8Bh, 54h, 24h, 40h, 89h, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 3Ch, 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 89h, 94h, 24h, 0C0h
    db 00h, 00h, 00h, 8Dh, 94h, 24h, 84h, 00h, 00h, 00h, 89h, 8Ch, 24h, 0B0h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 30h, 52h, 89h, 84h, 24h, 0BCh, 00h, 00h, 00h, 0A1h, 34h, 05h
    db 34h, 01h, 6Ah, 03h, 89h, 8Ch, 24h, 0C4h, 00h, 00h, 00h, 0C7h, 05h, 00h, 05h, 34h
    db 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 98h, 0F4h, 33h, 01h, 00h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0B0h, 00h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0AFh
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h
    db 0Dh, 0D0h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 08h, 0A3h, 0CCh, 10h, 34h, 01h, 8Bh, 44h
    db 24h, 34h, 89h, 0Dh, 0DCh, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 0D4h, 10h
    db 34h, 01h, 8Bh, 54h, 24h, 18h, 0A3h, 0D8h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h
    db 0Dh, 0E8h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0E0h, 10h, 34h, 01h, 8Bh
    db 54h, 24h, 0Ch, 0A3h, 0E4h, 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0F4h, 10h
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 89h, 15h, 0ECh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch
    db 0A3h, 0F0h, 10h, 34h, 01h, 8Bh, 44h, 24h, 10h, 89h, 0Dh, 00h, 11h, 34h, 01h, 8Bh
    db 0Dh, 9Ch, 0F4h, 33h, 01h, 89h, 15h, 0F8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h
    db 0FCh, 10h, 34h, 01h, 8Bh, 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0F7h, 0FFh, 89h, 15h
    db 04h, 11h, 34h, 01h, 0A3h, 08h, 11h, 34h, 01h, 83h, 0C9h, 02h, 89h, 0Dh, 9Ch, 0F4h
    db 33h, 01h, 8Bh, 56h, 08h, 68h, 00h, 00h, 01h, 00h, 6Ah, 0Bh, 52h, 0E8h, 0A1h, 0C1h
    db 6Bh, 0FFh, 8Bh, 46h, 08h, 6Ah, 02h, 6Ah, 18h, 50h, 0E8h, 94h, 0C1h, 6Bh, 0FFh, 83h
    db 0C4h, 18h, 5Eh, 81h, 0C4h, 0C0h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_00969d00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096A0C0 size 6
public ?d_0096a0c0@@YAXXZ
?d_0096a0c0@@YAXXZ PROC
    db 0B8h, 16h, 00h, 00h, 00h, 0C3h
?d_0096a0c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096A130 size 39
public ?d_0096a130@@YAXXZ
?d_0096a130@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 42h, 0CAh, 0FFh, 0FFh, 0C7h, 06h
    db 0Ch, 0E6h, 13h, 01h, 8Bh, 47h, 30h, 89h, 46h, 30h, 5Fh, 0C7h, 06h, 54h, 0E6h, 13h
    db 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0096a130@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096A160 size 860
public ?d_0096a160@@YAXXZ
?d_0096a160@@YAXXZ PROC
    db 81h, 0ECh, 0C0h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h
    db 8Bh, 0CEh, 0FFh, 50h, 20h, 8Bh, 46h, 08h, 83h, 0C0h, 10h, 8Bh, 0C8h, 83h, 0E9h, 02h
    db 0Fh, 84h, 5Dh, 02h, 00h, 00h, 49h, 0Fh, 84h, 6Fh, 01h, 00h, 00h, 81h, 0E9h, 0FDh
    db 00h, 00h, 00h, 0Fh, 84h, 0B5h, 00h, 00h, 00h, 8Bh, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh
    db 54h, 24h, 04h, 41h, 89h, 0Dh, 4Ch, 05h, 34h, 01h, 8Bh, 4Ch, 24h, 14h, 89h, 4Ch
    db 24h, 48h, 8Bh, 4Ch, 24h, 34h, 89h, 54h, 24h, 44h, 8Bh, 54h, 24h, 24h, 89h, 4Ch
    db 24h, 50h, 8Bh, 4Ch, 24h, 18h, 89h, 54h, 24h, 4Ch, 8Bh, 54h, 24h, 08h, 89h, 4Ch
    db 24h, 58h, 8Bh, 4Ch, 24h, 38h, 89h, 54h, 24h, 54h, 8Bh, 54h, 24h, 28h, 89h, 4Ch
    db 24h, 60h, 8Bh, 4Ch, 24h, 1Ch, 89h, 54h, 24h, 5Ch, 8Bh, 54h, 24h, 0Ch, 89h, 4Ch
    db 24h, 68h, 8Bh, 4Ch, 24h, 3Ch, 89h, 54h, 24h, 64h, 8Bh, 54h, 24h, 2Ch, 89h, 4Ch
    db 24h, 70h, 8Bh, 4Ch, 24h, 20h, 57h, 89h, 54h, 24h, 70h, 8Bh, 54h, 24h, 14h, 89h
    db 4Ch, 24h, 7Ch, 8Bh, 4Ch, 24h, 44h, 89h, 54h, 24h, 78h, 8Bh, 54h, 24h, 34h, 8Dh
    db 7Ch, 24h, 48h, 57h, 89h, 8Ch, 24h, 88h, 00h, 00h, 00h, 8Bh, 0Dh, 34h, 05h, 34h
    db 01h, 50h, 89h, 94h, 24h, 88h, 00h, 00h, 00h, 8Bh, 11h, 51h, 0FFh, 92h, 0B0h, 00h
    db 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 5Fh, 0E9h, 44h, 02h, 00h, 00h, 8Bh, 4Ch
    db 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h, 0Dh, 90h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 08h, 0A3h, 8Ch, 10h, 34h, 01h, 8Bh, 44h, 24h, 34h, 89h, 0Dh, 9Ch
    db 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 94h, 10h, 34h, 01h, 8Bh, 54h, 24h
    db 18h, 0A3h, 98h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h, 0Dh, 0A8h, 10h, 34h, 01h
    db 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0A0h, 10h, 34h, 01h, 8Bh, 54h, 24h, 0Ch, 0A3h, 0A4h
    db 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0B4h, 10h, 34h, 01h, 8Bh, 4Ch, 24h
    db 20h, 89h, 15h, 0ACh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch, 0A3h, 0B0h, 10h, 34h, 01h
    db 8Bh, 44h, 24h, 10h, 89h, 0Dh, 0C0h, 10h, 34h, 01h, 8Bh, 0Dh, 9Ch, 0F4h, 33h, 01h
    db 89h, 15h, 0B8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h, 0BCh, 10h, 34h, 01h, 8Bh
    db 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0FBh, 0FFh, 89h, 15h, 0C4h, 10h, 34h, 01h, 0A3h
    db 0C8h, 10h, 34h, 01h, 83h, 0C9h, 01h, 0E9h, 90h, 01h, 00h, 00h, 8Bh, 54h, 24h, 04h
    db 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 24h, 89h, 94h, 24h, 84h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 34h, 89h, 94h, 24h, 90h, 00h, 00h, 00h, 8Bh, 54h, 24h, 28h, 89h, 84h
    db 24h, 88h, 00h, 00h, 00h, 8Bh, 44h, 24h, 08h, 89h, 94h, 24h, 9Ch, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 1Ch, 89h, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 89h
    db 84h, 24h, 94h, 00h, 00h, 00h, 8Bh, 44h, 24h, 38h, 89h, 94h, 24h, 0A8h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 10h, 89h, 8Ch, 24h, 98h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch
    db 89h, 84h, 24h, 0A0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 2Ch, 89h, 94h, 24h, 0B4h, 00h
    db 00h, 00h, 8Bh, 54h, 24h, 40h, 89h, 8Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 3Ch, 89h, 84h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 89h, 94h, 24h, 0C0h
    db 00h, 00h, 00h, 8Dh, 94h, 24h, 84h, 00h, 00h, 00h, 89h, 8Ch, 24h, 0B0h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 30h, 52h, 89h, 84h, 24h, 0BCh, 00h, 00h, 00h, 0A1h, 34h, 05h
    db 34h, 01h, 6Ah, 03h, 89h, 8Ch, 24h, 0C4h, 00h, 00h, 00h, 0C7h, 05h, 00h, 05h, 34h
    db 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 98h, 0F4h, 33h, 01h, 00h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0B0h, 00h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0AFh
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 24h, 89h
    db 0Dh, 0D0h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 08h, 0A3h, 0CCh, 10h, 34h, 01h, 8Bh, 44h
    db 24h, 34h, 89h, 0Dh, 0DCh, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 38h, 89h, 15h, 0D4h, 10h
    db 34h, 01h, 8Bh, 54h, 24h, 18h, 0A3h, 0D8h, 10h, 34h, 01h, 8Bh, 44h, 24h, 28h, 89h
    db 0Dh, 0E8h, 10h, 34h, 01h, 8Bh, 4Ch, 24h, 2Ch, 89h, 15h, 0E0h, 10h, 34h, 01h, 8Bh
    db 54h, 24h, 0Ch, 0A3h, 0E4h, 10h, 34h, 01h, 8Bh, 44h, 24h, 1Ch, 89h, 0Dh, 0F4h, 10h
    db 34h, 01h, 8Bh, 4Ch, 24h, 20h, 89h, 15h, 0ECh, 10h, 34h, 01h, 8Bh, 54h, 24h, 3Ch
    db 0A3h, 0F0h, 10h, 34h, 01h, 8Bh, 44h, 24h, 10h, 89h, 0Dh, 00h, 11h, 34h, 01h, 8Bh
    db 0Dh, 9Ch, 0F4h, 33h, 01h, 89h, 15h, 0F8h, 10h, 34h, 01h, 8Bh, 54h, 24h, 30h, 0A3h
    db 0FCh, 10h, 34h, 01h, 8Bh, 44h, 24h, 40h, 81h, 0E1h, 0FFh, 0FFh, 0F7h, 0FFh, 89h, 15h
    db 04h, 11h, 34h, 01h, 0A3h, 08h, 11h, 34h, 01h, 83h, 0C9h, 02h, 89h, 0Dh, 9Ch, 0F4h
    db 33h, 01h, 8Bh, 56h, 08h, 68h, 00h, 00h, 03h, 00h, 6Ah, 0Bh, 52h, 0E8h, 41h, 0BDh
    db 6Bh, 0FFh, 8Bh, 46h, 08h, 6Ah, 02h, 6Ah, 18h, 50h, 0E8h, 34h, 0BDh, 6Bh, 0FFh, 83h
    db 0C4h, 18h, 5Eh, 81h, 0C4h, 0C0h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_0096a160@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096A580 size 44
public ?d_0096a580@@YAXXZ
?d_0096a580@@YAXXZ PROC
    db 56h, 57h, 6Ah, 34h, 8Bh, 0F9h, 0E8h, 0A5h, 79h, 0F1h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 04h
    db 85h, 0F6h, 74h, 13h, 57h, 8Bh, 0CEh, 0E8h, 74h, 0F1h, 0FFh, 0FFh, 5Fh, 0C7h, 06h, 30h
    db 0E6h, 13h, 01h, 8Bh, 0C6h, 5Eh, 0C3h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
?d_0096a580@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096A5B0 size 44
public ?d_0096a5b0@@YAXXZ
?d_0096a5b0@@YAXXZ PROC
    db 56h, 57h, 6Ah, 34h, 8Bh, 0F9h, 0E8h, 75h, 79h, 0F1h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 04h
    db 85h, 0F6h, 74h, 13h, 57h, 8Bh, 0CEh, 0E8h, 44h, 0F1h, 0FFh, 0FFh, 5Fh, 0C7h, 06h, 54h
    db 0E6h, 13h, 01h, 8Bh, 0C6h, 5Eh, 0C3h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
?d_0096a5b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096CE20 size 25
public ?d_0096ce20@@YAXXZ
?d_0096ce20@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_0096ce20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096E0C0 size 25
public ?d_0096e0c0@@YAXXZ
?d_0096e0c0@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_0096e0c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0096E1B0 size 201
public ?d_0096e1b0@@YAXXZ
?d_0096e1b0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 9Bh, 0ECh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 55h, 8Bh, 6Ch, 24h, 18h, 8Bh, 0D9h, 3Bh, 6Bh, 08h
    db 56h, 57h, 0Fh, 84h, 8Ah, 00h, 00h, 00h, 33h, 0FFh, 3Bh, 0EFh, 7Eh, 6Eh, 8Dh, 04h
    db 0EDh, 00h, 00h, 00h, 00h, 50h, 0E8h, 85h, 3Dh, 0F1h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 04h
    db 89h, 74h, 24h, 20h, 3Bh, 0F7h, 89h, 7Ch, 24h, 18h, 74h, 14h, 68h, 0EEh, 27h, 44h
    db 00h, 55h, 6Ah, 08h, 56h, 0E8h, 52h, 0CCh, 69h, 0FFh, 89h, 74h, 24h, 20h, 0EBh, 04h
    db 89h, 7Ch, 24h, 20h, 8Bh, 73h, 04h, 3Bh, 0F7h, 74h, 25h, 8Bh, 43h, 08h, 3Bh, 0E8h
    db 7Dh, 02h, 8Bh, 0C5h, 8Bh, 7Ch, 24h, 20h, 8Dh, 0Ch, 00h, 0F3h, 0A5h, 8Bh, 4Bh, 04h
    db 51h, 0E8h, 0BAh, 3Ch, 0F1h, 0FFh, 83h, 0C4h, 04h, 0C7h, 43h, 04h, 00h, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 20h, 89h, 53h, 04h, 89h, 6Bh, 08h, 0EBh, 16h, 8Bh, 43h, 04h, 3Bh
    db 0C7h, 89h, 7Bh, 08h, 74h, 0Ch, 50h, 0E8h, 94h, 3Ch, 0F1h, 0FFh, 83h, 0C4h, 04h, 89h
    db 7Bh, 04h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_0096e1b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009702F0 size 859
public ?d_009702f0@@YAXXZ
?d_009702f0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 9Bh, 0EEh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 74h, 24h, 24h, 8Bh
    db 0E9h, 8Bh, 0CEh, 0E8h, 68h, 10h, 07h, 00h, 8Bh, 0CEh, 0E8h, 21h, 11h, 07h, 00h, 83h
    db 0F8h, 1Fh, 75h, 3Bh, 68h, 10h, 02h, 00h, 00h, 0E8h, 02h, 1Ch, 0F1h, 0FFh, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 0Ch, 33h, 0DBh, 3Bh, 0C3h, 89h, 5Ch, 24h, 1Ch, 74h, 09h, 8Bh
    db 0C8h, 0E8h, 3Ah, 0FEh, 0FFh, 0FFh, 8Bh, 0D8h, 6Ah, 74h, 53h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 66h, 12h, 07h, 00h, 83h, 0F8h, 74h, 74h, 16h, 5Eh
    db 5Dh, 32h, 0C0h, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 14h, 0C2h, 04h, 00h, 8Bh, 0CEh, 0E8h, 64h, 10h, 07h, 00h, 8Bh, 43h, 04h, 8Bh
    db 53h, 2Ch, 25h, 00h, 00h, 0FFh, 00h, 3Dh, 00h, 00h, 02h, 00h, 8Bh, 43h, 28h, 0Fh
    db 94h, 0C1h, 51h, 6Ah, 01h, 52h, 50h, 8Bh, 0CDh, 0E8h, 32h, 0DCh, 0FDh, 0FFh, 8Dh, 43h
    db 18h, 8Dh, 70h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C6h, 57h, 8Bh, 0F8h
    db 8Dh, 43h, 08h, 8Dh, 70h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 8Bh, 4Bh, 04h
    db 2Bh, 0C6h, 8Dh, 7Ch, 07h, 02h, 89h, 4Dh, 20h, 8Ah, 53h, 38h, 57h, 88h, 55h, 1Ch
    db 0E8h, 9Bh, 1Bh, 0F1h, 0FFh, 8Bh, 0CFh, 8Bh, 0F1h, 8Bh, 0D0h, 0C1h, 0E9h, 02h, 33h, 0C0h
    db 8Bh, 0FAh, 0F3h, 0ABh, 8Bh, 0CEh, 83h, 0C4h, 04h, 83h, 0E1h, 03h, 0F3h, 0AAh, 8Dh, 43h
    db 18h, 89h, 54h, 24h, 10h, 8Dh, 70h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh
    db 0C6h, 89h, 44h, 24h, 14h, 74h, 2Ah, 8Dh, 73h, 18h, 8Bh, 0CAh, 2Bh, 0CEh, 8Bh, 0FFh
    db 8Ah, 06h, 88h, 04h, 31h, 46h, 84h, 0C0h, 75h, 0F6h, 8Bh, 0FAh, 4Fh, 8Dh, 49h, 00h
    db 8Ah, 47h, 01h, 47h, 84h, 0C0h, 75h, 0F8h, 66h, 0A1h, 4Ch, 1Dh, 08h, 01h, 66h, 89h
    db 07h, 8Dh, 43h, 08h, 8Bh, 0F0h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 8Bh, 0FAh, 2Bh
    db 0C6h, 4Fh, 8Ah, 4Fh, 01h, 47h, 84h, 0C9h, 75h, 0F8h, 8Bh, 0C8h, 0C1h, 0E9h, 02h, 0F3h
    db 0A5h, 8Bh, 0C8h, 83h, 0E1h, 03h, 0F3h, 0A4h, 52h, 8Bh, 0CDh, 0E8h, 0E0h, 47h, 0FBh, 0FFh
    db 8Bh, 4Ch, 24h, 10h, 51h, 0E8h, 86h, 1Ah, 0F1h, 0FFh, 8Bh, 55h, 28h, 0D9h, 43h, 54h
    db 0D9h, 43h, 50h, 8Bh, 4Bh, 4Ch, 89h, 93h, 10h, 01h, 00h, 00h, 8Bh, 45h, 24h, 89h
    db 83h, 14h, 01h, 00h, 00h, 0D9h, 5Dh, 6Ch, 89h, 4Dh, 68h, 0D9h, 5Dh, 70h, 8Bh, 53h
    db 58h, 0D9h, 43h, 60h, 83h, 0C4h, 04h, 0D9h, 43h, 5Ch, 89h, 55h, 74h, 0D9h, 5Dh, 78h
    db 5Fh, 0D9h, 5Dh, 7Ch, 8Bh, 43h, 64h, 0D9h, 43h, 6Ch, 0D9h, 43h, 68h, 89h, 85h, 80h
    db 00h, 00h, 00h, 0D9h, 9Dh, 84h, 00h, 00h, 00h, 0D9h, 9Dh, 88h, 00h, 00h, 00h, 8Bh
    db 4Bh, 70h, 89h, 8Dh, 8Ch, 00h, 00h, 00h, 81h, 3Bh, 01h, 00h, 04h, 00h, 72h, 3Ch
    db 8Bh, 43h, 04h, 25h, 00h, 00h, 0FFh, 00h, 3Dh, 00h, 00h, 01h, 00h, 74h, 22h, 3Dh
    db 00h, 00h, 02h, 00h, 74h, 11h, 3Dh, 00h, 00h, 06h, 00h, 75h, 1Fh, 8Bh, 45h, 18h
    db 0Dh, 00h, 08h, 00h, 00h, 0EBh, 12h, 8Bh, 45h, 18h, 0Dh, 00h, 04h, 01h, 00h, 0EBh
    db 08h, 8Bh, 45h, 18h, 0Dh, 00h, 02h, 00h, 00h, 89h, 45h, 18h, 8Bh, 43h, 04h, 0BEh
    db 00h, 20h, 00h, 00h, 85h, 0C6h, 74h, 07h, 81h, 4Dh, 18h, 00h, 01h, 00h, 00h, 8Bh
    db 43h, 04h, 0BAh, 00h, 80h, 00h, 00h, 85h, 0C2h, 74h, 07h, 81h, 4Dh, 18h, 00h, 10h
    db 00h, 00h, 0F7h, 43h, 04h, 00h, 00h, 00h, 20h, 74h, 07h, 81h, 4Dh, 18h, 00h, 00h
    db 01h, 00h, 8Bh, 4Bh, 04h, 0F7h, 0C1h, 00h, 00h, 00h, 0Fh, 74h, 62h, 0A1h, 80h, 6Dh
    db 2Dh, 01h, 83h, 0E8h, 00h, 74h, 33h, 48h, 74h, 1Ch, 48h, 75h, 46h, 0F7h, 0C1h, 00h
    db 00h, 00h, 08h, 74h, 11h, 0C7h, 83h, 88h, 00h, 00h, 00h, 26h, 00h, 00h, 00h, 8Bh
    db 45h, 18h, 0Bh, 0C2h, 0EBh, 46h, 0F7h, 0C1h, 00h, 00h, 00h, 04h, 74h, 0Ch, 0C7h, 83h
    db 88h, 00h, 00h, 00h, 25h, 00h, 00h, 00h, 0EBh, 2Ah, 0F7h, 0C1h, 00h, 00h, 00h, 02h
    db 74h, 11h, 0C7h, 83h, 88h, 00h, 00h, 00h, 24h, 00h, 00h, 00h, 8Bh, 45h, 18h, 0Bh
    db 0C6h, 0EBh, 19h, 0C7h, 83h, 88h, 00h, 00h, 00h, 23h, 00h, 00h, 00h, 0EBh, 10h, 0F6h
    db 0C5h, 40h, 74h, 0Bh, 8Bh, 45h, 18h, 0Dh, 00h, 40h, 00h, 00h, 89h, 45h, 18h, 8Bh
    db 54h, 24h, 24h, 53h, 52h, 8Bh, 0CDh, 0E8h, 0A4h, 0F9h, 0FFh, 0FFh, 81h, 3Bh, 00h, 00h
    db 03h, 00h, 73h, 28h, 8Bh, 45h, 18h, 0F6h, 0C4h, 04h, 74h, 20h, 6Ah, 01h, 8Bh, 0CDh
    db 0E8h, 0CBh, 40h, 0FBh, 0FFh, 8Bh, 55h, 28h, 33h, 0C9h, 85h, 0D2h, 7Eh, 0Eh, 8Bh, 0FFh
    db 66h, 0FFh, 04h, 48h, 8Bh, 55h, 28h, 41h, 3Bh, 0CAh, 7Ch, 0F4h, 0F7h, 45h, 20h, 0F0h
    db 0Fh, 00h, 00h, 74h, 11h, 8Bh, 85h, 90h, 00h, 00h, 00h, 85h, 0C0h, 75h, 07h, 8Bh
    db 0CDh, 0E8h, 4Ah, 4Ah, 0FBh, 0FFh, 53h, 8Bh, 0CDh, 0E8h, 0A2h, 0E1h, 0FFh, 0FFh, 8Bh, 0CBh
    db 0E8h, 0Bh, 0F7h, 0FFh, 0FFh, 53h, 0E8h, 85h, 18h, 0F1h, 0FFh, 83h, 0C4h, 04h, 8Bh, 0CDh
    db 0E8h, 1Bh, 0E1h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_009702f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00970690 size 15
public ?d_00970690@@YAXXZ
?d_00970690@@YAXXZ PROC
    db 8Bh, 49h, 14h, 85h, 0C9h, 74h, 05h, 0E9h, 54h, 8Eh, 00h, 00h, 33h, 0C0h, 0C3h
?d_00970690@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00970BE0 size 15
public ?d_00970be0@@YAXXZ
?d_00970be0@@YAXXZ PROC
    db 8Bh, 49h, 14h, 85h, 0C9h, 74h, 05h, 0E9h, 0C4h, 0B8h, 0FBh, 0FFh, 33h, 0C0h, 0C3h
?d_00970be0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00970CB0 size 6
public ?d_00970cb0@@YAXXZ
?d_00970cb0@@YAXXZ PROC
    db 0B8h, 48h, 53h, 45h, 4Dh, 0C3h
?d_00970cb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00970CD0 size 321
public ?d_00970cd0@@YAXXZ
?d_00970cd0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0DEh, 0EFh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 20h, 0Dh, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 46h
    db 18h, 8Dh, 54h, 24h, 08h, 57h, 2Bh, 0D0h, 8Ah, 08h, 88h, 0Ch, 02h, 40h, 84h, 0C9h
    db 75h, 0F6h, 8Dh, 44h, 24h, 0Ch, 6Ah, 2Eh, 50h, 0FFh, 15h, 9Ch, 94h, 35h, 01h, 83h
    db 0C4h, 08h, 85h, 0C0h, 74h, 13h, 8Bh, 0Dh, 0E4h, 39h, 11h, 01h, 89h, 08h, 8Ah, 15h
    db 0E8h, 39h, 11h, 01h, 88h, 50h, 04h, 0EBh, 1Fh, 8Dh, 7Ch, 24h, 0Ch, 4Fh, 8Bh, 0FFh
    db 8Ah, 47h, 01h, 47h, 84h, 0C0h, 75h, 0F8h, 0A1h, 0E4h, 39h, 11h, 01h, 8Ah, 0Dh, 0E8h
    db 39h, 11h, 01h, 89h, 07h, 88h, 4Fh, 04h, 8Bh, 56h, 20h, 8Bh, 46h, 1Ch, 52h, 50h
    db 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 57h, 0E1h, 6Ah, 0FFh, 8Bh, 0F8h, 83h, 0C4h, 0Ch, 85h
    db 0FFh, 0Fh, 84h, 93h, 00h, 00h, 00h, 57h, 8Dh, 8Ch, 24h, 14h, 01h, 00h, 00h, 0E8h
    db 0ACh, 05h, 07h, 00h, 8Dh, 8Ch, 24h, 10h, 01h, 00h, 00h, 0E8h, 00h, 06h, 07h, 00h
    db 84h, 0C0h, 74h, 6Fh, 8Dh, 8Ch, 24h, 10h, 01h, 00h, 00h, 0E8h, 0B0h, 06h, 07h, 00h
    db 85h, 0C0h, 75h, 5Fh, 68h, 18h, 03h, 00h, 00h, 0E8h, 92h, 11h, 0F1h, 0FFh, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 08h, 85h, 0C0h, 0C7h, 84h, 24h, 30h, 0Dh, 00h, 00h, 00h, 00h
    db 00h, 00h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0B5h, 0B4h, 0FBh, 0FFh, 0EBh, 02h, 33h, 0C0h, 8Dh
    db 94h, 24h, 10h, 01h, 00h, 00h, 52h, 8Bh, 0C8h, 0C7h, 84h, 24h, 34h, 0Dh, 00h, 00h
    db 0FFh, 0FFh, 0FFh, 0FFh, 89h, 46h, 14h, 0E8h, 0F4h, 0C2h, 0FBh, 0FFh, 84h, 0C0h, 75h, 13h
    db 8Bh, 4Eh, 14h, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 01h, 0FFh, 10h, 0C7h, 46h, 14h, 00h
    db 00h, 00h, 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 08h, 8Bh, 8Ch, 24h, 28h, 0Dh, 00h
    db 00h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 2Ch, 0Dh, 00h, 00h
    db 0C3h
?d_00970cd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009711F0 size 6
public ?d_009711f0@@YAXXZ
?d_009711f0@@YAXXZ PROC
    db 0B8h, 54h, 52h, 41h, 50h, 0C3h
?d_009711f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00971200 size 6
public ?d_00971200@@YAXXZ
?d_00971200@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_00971200@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009715E0 size 23
public ?d_009715e0@@YAXXZ
?d_009715e0@@YAXXZ PROC
    db 8Bh, 41h, 14h, 85h, 0C0h, 74h, 0Dh, 8Bh, 40h, 10h, 69h, 0C0h, 0B4h, 00h, 00h, 00h
    db 83h, 0C0h, 1Ch, 0C3h, 33h, 0C0h, 0C3h
?d_009715e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00971B50 size 15
public ?d_00971b50@@YAXXZ
?d_00971b50@@YAXXZ PROC
    db 8Bh, 49h, 14h, 85h, 0C9h, 74h, 05h, 0E9h, 04h, 0F0h, 00h, 00h, 33h, 0C0h, 0C3h
?d_00971b50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00971C40 size 6
public ?d_00971c40@@YAXXZ
?d_00971c40@@YAXXZ PROC
    db 0B8h, 52h, 47h, 47h, 41h, 0C3h
?d_00971c40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009721A0 size 6
public ?d_009721a0@@YAXXZ
?d_009721a0@@YAXXZ PROC
    db 0B8h, 44h, 00h, 00h, 00h, 0C3h
?d_009721a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00972860 size 8
public ?d_00972860@@YAXXZ
?d_00972860@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 0F8h, 00h, 00h, 00h
?d_00972860@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00972870 size 7
public ?d_00972870@@YAXXZ
?d_00972870@@YAXXZ PROC
    db 8Dh, 81h, 0C8h, 00h, 00h, 00h, 0C3h
?d_00972870@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009728A0 size 6
public ?d_009728a0@@YAXXZ
?d_009728a0@@YAXXZ PROC
    db 0B8h, 74h, 03h, 08h, 01h, 0C3h
?d_009728a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00972910 size 6
public ?d_00972910@@YAXXZ
?d_00972910@@YAXXZ PROC
    db 0B8h, 4Ch, 4Ch, 55h, 4Eh, 0C3h
?d_00972910@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00972920 size 6
public ?d_00972920@@YAXXZ
?d_00972920@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_00972920@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00973B90 size 25
public ?d_00973b90@@YAXXZ
?d_00973b90@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_00973b90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009744E0 size 25
public ?d_009744e0@@YAXXZ
?d_009744e0@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_009744e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009746A0 size 25
public ?d_009746a0@@YAXXZ
?d_009746a0@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_009746a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009747B0 size 8
public ?d_009747b0@@YAXXZ
?d_009747b0@@YAXXZ PROC
    db 83h, 0E9h, 18h, 0E9h, 18h, 00h, 00h, 00h
?d_009747b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00975050 size 28
public ?d_00975050@@YAXXZ
?d_00975050@@YAXXZ PROC
    db 51h, 8Bh, 09h, 85h, 0C9h, 8Bh, 44h, 24h, 08h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h
    db 89h, 08h, 74h, 04h, 66h, 0FFh, 41h, 04h, 59h, 0C2h, 04h, 00h
?d_00975050@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00978DA0 size 7
public ?d_00978da0@@YAXXZ
?d_00978da0@@YAXXZ PROC
    db 8Bh, 81h, 24h, 01h, 00h, 00h, 0C3h
?d_00978da0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00978FB0 size 67
public ?d_00978fb0@@YAXXZ
?d_00978fb0@@YAXXZ PROC
    db 53h, 55h, 57h, 8Bh, 0F9h, 8Bh, 07h, 0FFh, 50h, 6Ch, 8Bh, 0E8h, 33h, 0DBh, 85h, 0EDh
    db 7Eh, 2Bh, 56h, 8Bh, 17h, 53h, 8Bh, 0CFh, 0FFh, 52h, 74h, 8Bh, 4Ch, 24h, 14h, 8Bh
    db 0F0h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 90h, 0F8h, 01h, 00h, 00h, 0FFh, 4Eh, 04h, 75h
    db 06h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h, 43h, 3Bh, 0DDh, 7Ch, 0D7h, 5Eh, 5Fh, 5Dh, 5Bh
    db 0C2h, 04h, 00h
?d_00978fb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00979000 size 86
public ?d_00979000@@YAXXZ
?d_00979000@@YAXXZ PROC
    db 51h, 53h, 57h, 8Bh, 0F9h, 8Bh, 07h, 0FFh, 50h, 6Ch, 33h, 0DBh, 85h, 0C0h, 89h, 44h
    db 24h, 08h, 7Eh, 3Ch, 55h, 8Bh, 6Ch, 24h, 18h, 56h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 17h, 53h, 8Bh, 0CFh, 0FFh, 52h, 74h, 8Bh, 4Ch, 24h, 18h, 8Bh, 0F0h, 8Bh, 06h
    db 55h, 51h, 8Bh, 0CEh, 0FFh, 90h, 0FCh, 01h, 00h, 00h, 0FFh, 4Eh, 04h, 75h, 06h, 8Bh
    db 16h, 8Bh, 0CEh, 0FFh, 12h, 8Bh, 44h, 24h, 10h, 43h, 3Bh, 0D8h, 7Ch, 0D2h, 5Eh, 5Dh
    db 5Fh, 5Bh, 59h, 0C2h, 08h, 00h
?d_00979000@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097B850 size 68
public ?d_0097b850@@YAXXZ
?d_0097b850@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 68h, 00h, 07h, 00h, 00h, 8Bh, 0CEh
    db 32h, 0DBh, 0E8h, 89h, 5Eh, 06h, 00h, 3Ch, 01h, 75h, 21h, 56h, 8Bh, 0CFh, 0E8h, 0CDh
    db 0D0h, 0FFh, 0FFh, 3Ch, 01h, 75h, 0Eh, 56h, 8Bh, 0CFh, 0E8h, 0F1h, 0DBh, 0FFh, 0FFh, 3Ch
    db 01h, 75h, 02h, 8Ah, 0D8h, 8Bh, 0CEh, 0E8h, 64h, 5Fh, 06h, 00h, 5Fh, 5Eh, 8Ah, 0C3h
    db 5Bh, 0C2h, 04h, 00h
?d_0097b850@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097BBE0 size 8
public ?d_0097bbe0@@YAXXZ
?d_0097bbe0@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 08h, 12h, 00h, 00h
?d_0097bbe0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097C8E0 size 47
public ?d_0097c8e0@@YAXXZ
?d_0097c8e0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 50h, 51h, 8Bh, 0CEh, 0E8h
    db 0FCh, 0E4h, 0FFh, 0FFh, 84h, 0C0h, 74h, 11h, 8Bh, 46h, 08h, 3Bh, 46h, 10h, 7Dh, 03h
    db 89h, 46h, 10h, 0B0h, 01h, 5Eh, 0C2h, 08h, 00h, 32h, 0C0h, 5Eh, 0C2h, 08h, 00h
?d_0097c8e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097E980 size 8
public ?d_0097e980@@YAXXZ
?d_0097e980@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 28h, 0Ch, 00h, 00h
?d_0097e980@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097E9A0 size 7
public ?d_0097e9a0@@YAXXZ
?d_0097e9a0@@YAXXZ PROC
    db 8Bh, 81h, 24h, 01h, 00h, 00h, 0C3h
?d_0097e9a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097EA00 size 49
public ?d_0097ea00@@YAXXZ
?d_0097ea00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 8Bh, 41h, 10h, 74h, 13h, 25h, 0FFh, 0DFh, 0FFh, 0FFh
    db 89h, 41h, 10h, 8Bh, 01h, 0FFh, 90h, 14h, 02h, 00h, 00h, 0C2h, 04h, 00h, 0Dh, 00h
    db 20h, 00h, 00h, 89h, 41h, 10h, 8Bh, 01h, 0FFh, 90h, 14h, 02h, 00h, 00h, 0C2h, 04h
    db 00h
?d_0097ea00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097EA40 size 34
public ?d_0097ea40@@YAXXZ
?d_0097ea40@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 50h, 51h, 8Bh, 0CEh, 0E8h
    db 2Ch, 0Eh, 0FAh, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 14h, 02h, 00h, 00h, 5Eh, 0C2h
    db 08h, 00h
?d_0097ea40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097EA70 size 49
public ?d_0097ea70@@YAXXZ
?d_0097ea70@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 8Bh, 41h, 10h, 74h, 13h, 25h, 0FFh, 0BFh, 0FFh, 0FFh
    db 89h, 41h, 10h, 8Bh, 01h, 0FFh, 90h, 14h, 02h, 00h, 00h, 0C2h, 04h, 00h, 0Dh, 00h
    db 40h, 00h, 00h, 89h, 41h, 10h, 8Bh, 01h, 0FFh, 90h, 14h, 02h, 00h, 00h, 0C2h, 04h
    db 00h
?d_0097ea70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097EAB0 size 27
public ?d_0097eab0@@YAXXZ
?d_0097eab0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0D3h, 0Dh, 0FAh, 0FFh, 8Bh, 16h, 8Bh
    db 0CEh, 0FFh, 92h, 14h, 02h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_0097eab0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0097EAF0 size 7
public ?d_0097eaf0@@YAXXZ
?d_0097eaf0@@YAXXZ PROC
    db 8Ah, 81h, 20h, 01h, 00h, 00h, 0C3h
?d_0097eaf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00980320 size 26
public ?d_00980320@@YAXXZ
?d_00980320@@YAXXZ PROC
    db 53h, 32h, 0DBh, 0E8h, 48h, 0FAh, 0FFh, 0FFh, 85h, 0C0h, 74h, 08h, 8Bh, 10h, 5Bh, 8Bh
    db 0C8h, 0FFh, 62h, 08h, 8Ah, 0C3h, 5Bh, 0C2h, 04h, 00h
?d_00980320@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00980550 size 49
public ?d_00980550@@YAXXZ
?d_00980550@@YAXXZ PROC
    db 8Dh, 41h, 44h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 53h
    db 89h, 4Ah, 0Ch, 6Ah, 14h, 89h, 4Ah, 10h, 8Bh, 4Ch, 24h, 0Ch, 50h, 32h, 0DBh, 0E8h
    db 4Ch, 10h, 06h, 00h, 83h, 0F8h, 14h, 0B0h, 01h, 74h, 02h, 8Ah, 0C3h, 5Bh, 0C2h, 04h
    db 00h
?d_00980550@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00980660 size 32
public ?d_00980660@@YAXXZ
?d_00980660@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 53h, 6Ah, 40h, 50h, 32h, 0DBh, 0E8h, 2Dh
    db 12h, 06h, 00h, 83h, 0F8h, 40h, 0B0h, 01h, 74h, 02h, 8Ah, 0C3h, 5Bh, 0C2h, 08h, 00h
?d_00980660@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00980C70 size 25
public ?d_00980c70@@YAXXZ
?d_00980c70@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_00980c70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00980E60 size 25
public ?d_00980e60@@YAXXZ
?d_00980e60@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_00980e60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00981440 size 25
public ?d_00981440@@YAXXZ
?d_00981440@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_00981440@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00981550 size 25
public ?d_00981550@@YAXXZ
?d_00981550@@YAXXZ PROC
    db 8Ah, 41h, 0Ch, 84h, 0C0h, 75h, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 44h, 24h, 04h
    db 2Bh, 41h, 04h, 0C1h, 0E8h, 02h, 0C2h, 04h, 00h
?d_00981550@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00982080 size 8
public ?d_00982080@@YAXXZ
?d_00982080@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 68h, 0Ch, 00h, 00h
?d_00982080@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00982EB0 size 8
public ?d_00982eb0@@YAXXZ
?d_00982eb0@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 28h, 03h, 00h, 00h
?d_00982eb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00982FD0 size 68
public ?d_00982fd0@@YAXXZ
?d_00982fd0@@YAXXZ PROC
    db 53h, 55h, 57h, 8Bh, 0F9h, 8Bh, 07h, 33h, 0EDh, 33h, 0DBh, 0FFh, 50h, 6Ch, 85h, 0C0h
    db 7Eh, 2Ch, 56h, 8Bh, 17h, 53h, 8Bh, 0CFh, 0FFh, 52h, 74h, 8Bh, 0F0h, 8Bh, 06h, 8Bh
    db 0CEh, 0FFh, 50h, 2Ch, 03h, 0E8h, 0FFh, 4Eh, 04h, 75h, 06h, 8Bh, 16h, 8Bh, 0CEh, 0FFh
    db 12h, 8Bh, 07h, 8Bh, 0CFh, 43h, 0FFh, 50h, 6Ch, 3Bh, 0D8h, 7Ch, 0D6h, 5Eh, 5Fh, 8Bh
    db 0C5h, 5Dh, 5Bh, 0C3h
?d_00982fd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00983750 size 29
public ?d_00983750@@YAXXZ
?d_00983750@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 92h, 0C4h, 0F9h, 0FFh, 8Bh, 07h
    db 6Ah, 00h, 56h, 8Bh, 0CFh, 0FFh, 50h, 38h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00983750@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00984B50 size 8
public ?d_00984b50@@YAXXZ
?d_00984b50@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 0A8h, 4Eh, 00h, 00h
?d_00984b50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098C4B0 size 87
public ?d_0098c4b0@@YAXXZ
?d_0098c4b0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh, 0CEh, 32h, 0DBh, 0E8h, 0BEh, 4Eh
    db 05h, 00h, 84h, 0C0h, 74h, 39h, 8Bh, 0CEh, 0E8h, 73h, 4Fh, 05h, 00h, 3Dh, 03h, 05h
    db 00h, 00h, 75h, 2Bh, 8Dh, 57h, 18h, 33h, 0C0h, 8Bh, 0FAh, 0B9h, 53h, 00h, 00h, 00h
    db 68h, 4Ch, 01h, 00h, 00h, 0F3h, 0ABh, 52h, 8Bh, 0CEh, 0E8h, 0D1h, 50h, 05h, 00h, 3Dh
    db 4Ch, 01h, 00h, 00h, 75h, 02h, 0B3h, 01h, 8Bh, 0CEh, 0E8h, 0E1h, 4Eh, 05h, 00h, 5Fh
    db 5Eh, 8Ah, 0C3h, 5Bh, 0C2h, 04h, 00h
?d_0098c4b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098C510 size 187
public ?d_0098c510@@YAXXZ
?d_0098c510@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 0Ch, 56h, 8Bh, 0F1h, 8Bh, 0CDh, 32h, 0DBh, 0E8h, 5Eh, 4Eh
    db 05h, 00h, 84h, 0C0h, 0Fh, 84h, 99h, 00h, 00h, 00h, 8Bh, 0CDh, 0E8h, 0Fh, 4Fh, 05h
    db 00h, 3Dh, 04h, 05h, 00h, 00h, 0Fh, 85h, 87h, 00h, 00h, 00h, 57h, 8Dh, 96h, 64h
    db 01h, 00h, 00h, 33h, 0C0h, 8Bh, 0FAh, 0B9h, 1Fh, 00h, 00h, 00h, 6Ah, 7Ch, 0F3h, 0ABh
    db 52h, 8Bh, 0CDh, 0E8h, 68h, 50h, 05h, 00h, 83h, 0F8h, 7Ch, 75h, 5Eh, 8Bh, 8Eh, 0D4h
    db 02h, 00h, 00h, 33h, 0FFh, 3Bh, 0CFh, 74h, 0Ch, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 89h
    db 0BEh, 0D4h, 02h, 00h, 00h, 8Bh, 8Eh, 0D8h, 02h, 00h, 00h, 3Bh, 0CFh, 74h, 0Ch, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 12h, 89h, 0BEh, 0D8h, 02h, 00h, 00h, 8Bh, 06h, 8Dh, 8Eh, 68h
    db 01h, 00h, 00h, 51h, 8Bh, 0CEh, 0FFh, 90h, 24h, 01h, 00h, 00h, 8Bh, 16h, 89h, 86h
    db 0D4h, 02h, 00h, 00h, 8Dh, 86h, 88h, 01h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 92h, 24h
    db 01h, 00h, 00h, 89h, 86h, 0D8h, 02h, 00h, 00h, 0B3h, 01h, 8Bh, 0CDh, 0E8h, 1Eh, 4Eh
    db 05h, 00h, 5Fh, 5Eh, 5Dh, 8Ah, 0C3h, 5Bh, 0C2h, 04h, 00h
?d_0098c510@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098CBD0 size 67
public ?d_0098cbd0@@YAXXZ
?d_0098cbd0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 68h, 03h, 05h, 00h, 00h, 8Bh, 0CEh
    db 32h, 0DBh, 0E8h, 09h, 4Bh, 05h, 00h, 3Ch, 01h, 75h, 20h, 68h, 4Ch, 01h, 00h, 00h
    db 83h, 0C7h, 18h, 57h, 8Bh, 0CEh, 0E8h, 0A5h, 4Ch, 05h, 00h, 3Dh, 4Ch, 01h, 00h, 00h
    db 75h, 02h, 0B3h, 01h, 8Bh, 0CEh, 0E8h, 0E5h, 4Bh, 05h, 00h, 5Fh, 5Eh, 8Ah, 0C3h, 5Bh
    db 0C2h, 04h, 00h
?d_0098cbd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098CC20 size 65
public ?d_0098cc20@@YAXXZ
?d_0098cc20@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 68h, 04h, 05h, 00h, 00h, 8Bh, 0CEh
    db 32h, 0DBh, 0E8h, 0B9h, 4Ah, 05h, 00h, 3Ch, 01h, 75h, 1Eh, 6Ah, 7Ch, 81h, 0C7h, 64h
    db 01h, 00h, 00h, 57h, 8Bh, 0CEh, 0E8h, 55h, 4Ch, 05h, 00h, 83h, 0F8h, 7Ch, 75h, 02h
    db 0B3h, 01h, 8Bh, 0CEh, 0E8h, 97h, 4Bh, 05h, 00h, 5Fh, 5Eh, 8Ah, 0C3h, 5Bh, 0C2h, 04h
    db 00h
?d_0098cc20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098CDB0 size 65
public ?d_0098cdb0@@YAXXZ
?d_0098cdb0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 68h, 09h, 05h, 00h, 00h, 8Bh, 0CEh
    db 32h, 0DBh, 0E8h, 29h, 49h, 05h, 00h, 3Ch, 01h, 75h, 1Eh, 6Ah, 40h, 81h, 0C7h, 08h
    db 02h, 00h, 00h, 57h, 8Bh, 0CEh, 0E8h, 0C5h, 4Ah, 05h, 00h, 83h, 0F8h, 40h, 75h, 02h
    db 0B3h, 01h, 8Bh, 0CEh, 0E8h, 07h, 4Ah, 05h, 00h, 5Fh, 5Eh, 8Ah, 0C3h, 5Bh, 0C2h, 04h
    db 00h
?d_0098cdb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098D380 size 13
public ?d_0098d380@@YAXXZ
?d_0098d380@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 81h, 64h, 01h, 00h, 00h, 0C2h, 04h, 00h
?d_0098d380@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098D3E0 size 7
public ?d_0098d3e0@@YAXXZ
?d_0098d3e0@@YAXXZ PROC
    db 0D9h, 81h, 0A8h, 02h, 00h, 00h, 0C3h
?d_0098d3e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098D3F0 size 10
public ?d_0098d3f0@@YAXXZ
?d_0098d3f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 0Ch, 0C2h, 04h, 00h
?d_0098d3f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098D4C0 size 13
public ?d_0098d4c0@@YAXXZ
?d_0098d4c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 81h, 0Ch, 02h, 00h, 00h, 0C2h, 04h, 00h
?d_0098d4c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0098DBA0 size 943
public ?d_0098dba0@@YAXXZ
?d_0098dba0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0DBh, 0FFh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 28h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 06h, 32h
    db 0DBh, 0FFh, 90h, 38h, 01h, 00h, 00h, 8Bh, 6Ch, 24h, 44h, 8Bh, 0CDh, 0E8h, 0AEh, 37h
    db 05h, 00h, 84h, 0C0h, 0Fh, 84h, 5Fh, 03h, 00h, 00h, 8Bh, 0CDh, 0E8h, 5Fh, 38h, 05h
    db 00h, 3Dh, 05h, 05h, 00h, 00h, 0Fh, 85h, 4Dh, 03h, 00h, 00h, 33h, 0C9h, 89h, 4Ch
    db 24h, 10h, 89h, 4Ch, 24h, 14h, 89h, 4Ch, 24h, 18h, 89h, 4Ch, 24h, 1Ch, 89h, 4Ch
    db 24h, 20h, 89h, 4Ch, 24h, 24h, 89h, 4Ch, 24h, 28h, 89h, 4Ch, 24h, 2Ch, 6Ah, 28h
    db 8Dh, 54h, 24h, 10h, 89h, 4Ch, 24h, 34h, 52h, 8Bh, 0CDh, 0C7h, 44h, 24h, 14h, 00h
    db 00h, 00h, 00h, 0E8h, 98h, 39h, 05h, 00h, 83h, 0F8h, 28h, 0Fh, 85h, 01h, 03h, 00h
    db 00h, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 14h, 48h, 89h, 86h
    db 60h, 02h, 00h, 00h, 0Fh, 0B6h, 44h, 24h, 1Ah, 49h, 89h, 44h, 24h, 44h, 8Bh, 44h
    db 24h, 18h, 0DBh, 44h, 24h, 44h, 89h, 8Eh, 74h, 02h, 00h, 00h, 0Fh, 0B6h, 0CCh, 4Ah
    db 89h, 96h, 88h, 02h, 00h, 00h, 89h, 4Ch, 24h, 44h, 8Bh, 4Ch, 24h, 20h, 0Fh, 0B6h
    db 0D0h, 0D8h, 0Dh, 4Ch, 0C6h, 07h, 01h, 0DBh, 44h, 24h, 44h, 8Bh, 44h, 24h, 1Ch, 89h
    db 54h, 24h, 44h, 0D8h, 0Dh, 4Ch, 0C6h, 07h, 01h, 0DBh, 44h, 24h, 44h, 57h, 0D8h, 0Dh
    db 4Ch, 0C6h, 07h, 01h, 0D9h, 9Eh, 54h, 02h, 00h, 00h, 0D9h, 9Eh, 58h, 02h, 00h, 00h
    db 0D9h, 9Eh, 5Ch, 02h, 00h, 00h, 89h, 86h, 70h, 02h, 00h, 00h, 8Bh, 86h, 60h, 02h
    db 00h, 00h, 85h, 0C0h, 89h, 8Eh, 84h, 02h, 00h, 00h, 76h, 5Ah, 8Dh, 14h, 85h, 00h
    db 00h, 00h, 00h, 52h, 0E8h, 0A7h, 42h, 0EFh, 0FFh, 8Bh, 0BEh, 60h, 02h, 00h, 00h, 89h
    db 86h, 64h, 02h, 00h, 00h, 8Dh, 04h, 7Fh, 0C1h, 0E0h, 02h, 50h, 0E8h, 8Fh, 42h, 0EFh
    db 0FFh, 8Bh, 0D8h, 83h, 0C4h, 08h, 89h, 5Ch, 24h, 48h, 85h, 0DBh, 0C7h, 44h, 24h, 40h
    db 00h, 00h, 00h, 00h, 74h, 10h, 68h, 7Ch, 67h, 44h, 00h, 57h, 6Ah, 0Ch, 53h, 0E8h
    db 58h, 0D1h, 67h, 0FFh, 0EBh, 02h, 33h, 0DBh, 0C7h, 44h, 24h, 40h, 0FFh, 0FFh, 0FFh, 0FFh
    db 89h, 9Eh, 68h, 02h, 00h, 00h, 8Bh, 86h, 74h, 02h, 00h, 00h, 85h, 0C0h, 76h, 2Bh
    db 8Dh, 0Ch, 85h, 00h, 00h, 00h, 00h, 51h, 0E8h, 43h, 42h, 0EFh, 0FFh, 8Bh, 96h, 74h
    db 02h, 00h, 00h, 0C1h, 0E2h, 02h, 52h, 89h, 86h, 78h, 02h, 00h, 00h, 0E8h, 2Eh, 42h
    db 0EFh, 0FFh, 83h, 0C4h, 08h, 89h, 86h, 7Ch, 02h, 00h, 00h, 8Bh, 86h, 88h, 02h, 00h
    db 00h, 85h, 0C0h, 76h, 27h, 0C1h, 0E0h, 02h, 50h, 0E8h, 12h, 42h, 0EFh, 0FFh, 8Bh, 8Eh
    db 88h, 02h, 00h, 00h, 0C1h, 0E1h, 02h, 51h, 89h, 86h, 8Ch, 02h, 00h, 00h, 0E8h, 0FDh
    db 41h, 0EFh, 0FFh, 83h, 0C4h, 08h, 89h, 86h, 90h, 02h, 00h, 00h, 8Bh, 16h, 8Dh, 86h
    db 48h, 02h, 00h, 00h, 50h, 6Ah, 00h, 55h, 8Bh, 0CEh, 0FFh, 92h, 0E4h, 00h, 00h, 00h
    db 8Bh, 86h, 60h, 02h, 00h, 00h, 33h, 0FFh, 85h, 0C0h, 76h, 30h, 33h, 0DBh, 8Bh, 0FFh
    db 8Bh, 86h, 68h, 02h, 00h, 00h, 8Bh, 8Eh, 64h, 02h, 00h, 00h, 8Bh, 16h, 03h, 0C3h
    db 50h, 8Dh, 04h, 0B9h, 50h, 55h, 8Bh, 0CEh, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 86h
    db 60h, 02h, 00h, 00h, 47h, 83h, 0C3h, 0Ch, 3Bh, 0F8h, 72h, 0D4h, 8Bh, 86h, 60h, 02h
    db 00h, 00h, 48h, 85h, 0C0h, 0Fh, 8Eh, 0AFh, 00h, 00h, 00h, 8Bh, 96h, 68h, 02h, 00h
    db 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Dh, 0Ch, 40h, 0C1h, 0E1h, 02h, 0D9h, 04h, 0Ah
    db 03h, 0D1h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 0Fh, 8Ah, 8Bh, 00h, 00h, 00h, 0D9h
    db 05h, 50h, 53h, 07h, 01h, 0D9h, 42h, 04h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Ah
    db 79h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 42h, 08h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 44h, 7Ah, 67h, 0D9h, 86h, 54h, 02h, 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 74h, 26h, 0D9h, 86h, 58h, 02h, 00h, 00h, 0D8h, 1Dh, 50h, 53h
    db 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 13h, 0D9h, 86h, 5Ch, 02h, 00h, 00h, 0D8h
    db 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 2Eh, 0D9h, 86h, 54h, 02h
    db 00h, 00h, 0D9h, 0E0h, 0D9h, 1Ah, 8Bh, 86h, 68h, 02h, 00h, 00h, 0D9h, 86h, 58h, 02h
    db 00h, 00h, 0D9h, 0E0h, 0D9h, 5Ch, 01h, 04h, 8Bh, 96h, 68h, 02h, 00h, 00h, 0D9h, 86h
    db 5Ch, 02h, 00h, 00h, 0D9h, 0E0h, 0D9h, 5Ch, 11h, 08h, 8Bh, 06h, 8Dh, 8Eh, 6Ch, 02h
    db 00h, 00h, 51h, 6Ah, 00h, 55h, 8Bh, 0CEh, 0FFh, 90h, 0E8h, 00h, 00h, 00h, 8Bh, 86h
    db 74h, 02h, 00h, 00h, 33h, 0FFh, 85h, 0C0h, 76h, 35h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 8Eh, 7Ch, 02h, 00h, 00h, 8Bh, 16h, 8Dh, 04h, 0BDh, 00h, 00h, 00h, 00h, 03h
    db 0C8h, 51h, 8Bh, 8Eh, 78h, 02h, 00h, 00h, 03h, 0C8h, 51h, 55h, 8Bh, 0CEh, 0FFh, 92h
    db 0E8h, 00h, 00h, 00h, 8Bh, 86h, 74h, 02h, 00h, 00h, 47h, 3Bh, 0F8h, 72h, 0D1h, 8Bh
    db 16h, 8Dh, 86h, 80h, 02h, 00h, 00h, 50h, 6Ah, 00h, 55h, 8Bh, 0CEh, 0FFh, 92h, 0ECh
    db 00h, 00h, 00h, 8Bh, 86h, 88h, 02h, 00h, 00h, 33h, 0FFh, 85h, 0C0h, 76h, 30h, 90h
    db 8Bh, 8Eh, 90h, 02h, 00h, 00h, 8Bh, 16h, 8Dh, 04h, 0BDh, 00h, 00h, 00h, 00h, 03h
    db 0C8h, 51h, 8Bh, 8Eh, 8Ch, 02h, 00h, 00h, 03h, 0C8h, 51h, 55h, 8Bh, 0CEh, 0FFh, 92h
    db 0ECh, 00h, 00h, 00h, 8Bh, 86h, 88h, 02h, 00h, 00h, 47h, 3Bh, 0F8h, 72h, 0D1h, 0B3h
    db 01h, 5Fh, 8Bh, 0CDh, 0E8h, 0A7h, 34h, 05h, 00h, 8Bh, 4Ch, 24h, 34h, 5Eh, 5Dh, 8Ah
    db 0C3h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 34h, 0C2h, 04h, 00h
?d_0098dba0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00991AE0 size 154
public ?d_00991ae0@@YAXXZ
?d_00991ae0@@YAXXZ PROC
    db 81h, 0ECh, 10h, 02h, 00h, 00h, 56h, 8Bh, 0B4h, 24h, 18h, 02h, 00h, 00h, 57h, 8Dh
    db 44h, 24h, 08h, 50h, 6Ah, 01h, 56h, 0E8h, 44h, 8Dh, 00h, 00h, 8Dh, 4Ch, 24h, 18h
    db 51h, 56h, 8Bh, 0F8h, 0E8h, 97h, 8Bh, 00h, 00h, 8Bh, 44h, 24h, 1Ch, 83h, 0C4h, 14h
    db 33h, 0F6h, 85h, 0C0h, 76h, 49h, 53h, 8Bh, 1Dh, 00h, 95h, 35h, 01h, 8Dh, 49h, 00h
    db 8Bh, 44h, 24h, 10h, 8Dh, 94h, 24h, 1Ch, 02h, 00h, 00h, 3Bh, 0C2h, 72h, 0Dh, 8Dh
    db 44h, 24h, 10h, 50h, 0E8h, 87h, 89h, 00h, 00h, 83h, 0C4h, 04h, 0Fh, 0B6h, 0Ch, 3Eh
    db 51h, 0FFh, 0D3h, 8Bh, 54h, 24h, 14h, 88h, 02h, 8Bh, 54h, 24h, 14h, 8Bh, 44h, 24h
    db 10h, 83h, 0C4h, 04h, 42h, 46h, 3Bh, 0F0h, 89h, 54h, 24h, 10h, 72h, 0C2h, 5Bh, 8Dh
    db 44h, 24h, 0Ch, 50h, 0E8h, 27h, 8Ah, 00h, 00h, 83h, 0C4h, 04h, 5Fh, 0B8h, 01h, 00h
    db 00h, 00h, 5Eh, 81h, 0C4h, 10h, 02h, 00h, 00h, 0C3h
?d_00991ae0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009931C0 size 227
public ?d_009931c0@@YAXXZ
?d_009931c0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 6Ah, 0FFh, 56h, 0E8h, 61h, 0D1h, 0FFh, 0FFh, 6Ah
    db 0FEh, 56h, 8Bh, 0D8h, 0E8h, 07h, 0CCh, 0FFh, 0FFh, 6Ah, 01h, 56h, 0E8h, 4Fh, 0D1h, 0FFh
    db 0FFh, 8Bh, 0F8h, 83h, 0C4h, 18h, 85h, 0FFh, 74h, 25h, 6Ah, 01h, 56h, 0E8h, 0BEh, 0CEh
    db 0FFh, 0FFh, 8Bh, 4Bh, 08h, 83h, 0C4h, 08h, 3Bh, 0C1h, 74h, 25h, 3Bh, 43h, 0Ch, 75h
    db 0Eh, 68h, 90h, 01h, 14h, 01h, 56h, 0E8h, 0D4h, 26h, 00h, 00h, 83h, 0C4h, 08h, 68h
    db 0ACh, 01h, 14h, 01h, 6Ah, 01h, 56h, 33h, 0FFh, 0E8h, 0A2h, 74h, 00h, 00h, 83h, 0C4h
    db 0Ch, 0A1h, 0F0h, 92h, 35h, 01h, 3Bh, 0F8h, 74h, 34h, 8Dh, 48h, 20h, 3Bh, 0F9h, 74h
    db 2Dh, 83h, 0C0h, 40h, 3Bh, 0F8h, 74h, 26h, 8Bh, 53h, 08h, 52h, 57h, 56h, 0E8h, 0ADh
    db 0D2h, 0FFh, 0FFh, 8Bh, 43h, 0Ch, 50h, 56h, 0E8h, 0E3h, 0D7h, 0FFh, 0FFh, 57h, 0FFh, 15h
    db 0A0h, 93h, 35h, 01h, 83h, 0C4h, 18h, 0F7h, 0D8h, 1Bh, 0C0h, 40h, 74h, 16h, 6Ah, 00h
    db 6Ah, 00h, 56h, 0E8h, 88h, 0D2h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 5Fh, 5Eh, 0B8h, 01h, 00h
    db 00h, 00h, 5Bh, 0C3h, 56h, 0E8h, 36h, 0D1h, 0FFh, 0FFh, 68h, 7Ch, 01h, 14h, 01h, 56h
    db 0E8h, 0FBh, 0D1h, 0FFh, 0FFh, 0DDh, 05h, 18h, 5Fh, 09h, 01h, 83h, 0C4h, 04h, 0DDh, 1Ch
    db 24h, 56h, 0E8h, 79h, 0D1h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 5Fh, 5Eh, 0B8h, 03h, 00h, 00h
    db 00h, 5Bh, 0C3h
?d_009931c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009934D0 size 20
public ?d_009934d0@@YAXXZ
?d_009934d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 68h, 38h, 0Bh, 13h, 01h, 6Ah, 00h, 0E8h, 0E0h, 0FEh, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 0C3h
?d_009934d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009934F0 size 20
public ?d_009934f0@@YAXXZ
?d_009934f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 68h, 0F8h, 6Dh, 07h, 01h, 6Ah, 01h, 0E8h, 0C0h, 0FEh, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 0C3h
?d_009934f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00993510 size 70
public ?d_00993510@@YAXXZ
?d_00993510@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 6Ah, 0FFh, 56h, 0E8h, 11h, 0CEh, 0FFh, 0FFh, 6Ah
    db 0FEh, 56h, 8Bh, 0D8h, 0E8h, 0B7h, 0C8h, 0FFh, 0FFh, 83h, 0C4h, 10h, 68h, 84h, 54h, 07h
    db 01h, 6Ah, 00h, 6Ah, 01h, 56h, 0E8h, 05h, 73h, 00h, 00h, 83h, 0C4h, 0Ch, 50h, 0FFh
    db 15h, 0BCh, 93h, 35h, 01h, 6Ah, 01h, 53h, 8Bh, 0F8h, 0E8h, 0B1h, 0FBh, 0FFh, 0FFh, 83h
    db 0C4h, 10h, 5Fh, 5Eh, 5Bh, 0C3h
?d_00993510@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009945A0 size 155
public ?d_009945a0@@YAXXZ
?d_009945a0@@YAXXZ PROC
    db 55h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 56h, 0E8h, 23h, 0B8h, 0FFh, 0FFh, 68h, 40h, 04h
    db 14h, 01h, 56h, 8Bh, 0E8h, 0E8h, 0A6h, 0BFh, 0FFh, 0FFh, 0BFh, 01h, 00h, 00h, 00h, 83h
    db 0C4h, 0Ch, 3Bh, 0EFh, 7Ch, 62h, 53h, 6Ah, 0FFh, 56h, 0E8h, 21h, 0B9h, 0FFh, 0FFh, 57h
    db 56h, 0E8h, 1Ah, 0B9h, 0FFh, 0FFh, 6Ah, 01h, 6Ah, 01h, 56h, 0E8h, 0E0h, 0C3h, 0FFh, 0FFh
    db 6Ah, 0FFh, 56h, 0E8h, 68h, 0BCh, 0FFh, 0FFh, 8Bh, 0D8h, 83h, 0C4h, 24h, 85h, 0DBh, 75h
    db 0Eh, 68h, 0D0h, 05h, 14h, 01h, 56h, 0E8h, 0E4h, 12h, 00h, 00h, 83h, 0C4h, 08h, 83h
    db 0FFh, 01h, 7Eh, 0Dh, 68h, 0E8h, 2Dh, 13h, 01h, 0E8h, 9Fh, 0A5h, 6Ah, 0FFh, 83h, 0C4h
    db 04h, 53h, 0E8h, 96h, 0A5h, 6Ah, 0FFh, 6Ah, 0FEh, 56h, 0E8h, 0C1h, 0B7h, 0FFh, 0FFh, 83h
    db 0C4h, 0Ch, 47h, 3Bh, 0FDh, 7Eh, 0A0h, 5Bh, 68h, 94h, 02h, 08h, 01h, 0E8h, 7Bh, 0A5h
    db 6Ah, 0FFh, 83h, 0C4h, 04h, 5Fh, 5Eh, 33h, 0C0h, 5Dh, 0C3h
?d_009945a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0099F6F0 size 35
public ?d_0099f6f0@@YAXXZ
?d_0099f6f0@@YAXXZ PROC
    db 56h, 33h, 0C0h, 8Bh, 0F1h, 85h, 0F6h, 8Bh, 74h, 24h, 08h, 0Fh, 95h, 0C0h, 8Dh, 44h
    db 00h, 27h, 50h, 8Bh, 44h, 24h, 10h, 6Ah, 00h, 0E8h, 0B2h, 0FEh, 0FFh, 0FFh, 83h, 0C4h
    db 08h, 5Eh, 0C3h
?d_0099f6f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A1990 size 11
public ?d_009a1990@@YAXXZ
?d_009a1990@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009a1990@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A2560 size 8
public ?d_009a2560@@YAXXZ
?d_009a2560@@YAXXZ PROC
    db 8Bh, 49h, 0Ch, 0E9h, 0C8h, 24h, 00h, 00h
?d_009a2560@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A2650 size 8
public ?d_009a2650@@YAXXZ
?d_009a2650@@YAXXZ PROC
    db 83h, 0E9h, 08h, 0E9h, 0D8h, 00h, 00h, 00h
?d_009a2650@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A2670 size 6
public ?d_009a2670@@YAXXZ
?d_009a2670@@YAXXZ PROC
    db 0B8h, 0A4h, 16h, 14h, 01h, 0C3h
?d_009a2670@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A2700 size 46
public ?d_009a2700@@YAXXZ
?d_009a2700@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 8Bh
    db 4Fh, 04h, 56h, 0E8h, 98h, 08h, 00h, 00h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_009a2700@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A3440 size 11
public ?d_009a3440@@YAXXZ
?d_009a3440@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_009a3440@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A38E0 size 71
public ?d_009a38e0@@YAXXZ
?d_009a38e0@@YAXXZ PROC
    db 8Bh, 09h, 8Bh, 41h, 04h, 85h, 0C0h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0D1h, 74h
    db 15h, 8Bh, 37h, 39h, 70h, 10h, 72h, 07h, 8Bh, 0D0h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh
    db 40h, 0Ch, 85h, 0C0h, 75h, 0EDh, 3Bh, 0D1h, 74h, 07h, 8Bh, 07h, 3Bh, 42h, 10h, 73h
    db 0Bh, 8Bh, 44h, 24h, 0Ch, 5Fh, 89h, 08h, 5Eh, 0C2h, 08h, 00h, 8Bh, 44h, 24h, 0Ch
    db 5Fh, 89h, 10h, 5Eh, 0C2h, 08h, 00h
?d_009a38e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A3930 size 33
public ?d_009a3930@@YAXXZ
?d_009a3930@@YAXXZ PROC
    db 56h, 6Ah, 18h, 0E8h, 08h, 0ACh, 0E8h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Eh, 10h, 51h, 0E8h, 0D8h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_009a3930@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A59D0 size 49
public ?d_009a59d0@@YAXXZ
?d_009a59d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 0Fh, 0AFh, 74h, 24h, 0Ch, 56h, 0E8h, 40h, 0FFh, 0FFh, 0FFh
    db 8Bh, 0D0h, 83h, 0C4h, 04h, 85h, 0D2h, 74h, 14h, 57h, 8Bh, 0CEh, 0C1h, 0E9h, 02h, 33h
    db 0C0h, 8Bh, 0FAh, 0F3h, 0ABh, 8Bh, 0CEh, 83h, 0E1h, 03h, 0F3h, 0AAh, 5Fh, 8Bh, 0C2h, 5Eh
    db 0C3h
?d_009a59d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009A5F50 size 475
_TEXT ENDS
_TEXT$d00da5f50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DA5F50 size 475
public ?d_009a5f50@@YAXXZ
?d_009a5f50@@YAXXZ PROC
    db 081h, 0ECh, 03Ch, 009h, 000h, 000h, 08Bh, 08Ch, 024h, 050h, 009h, 000h, 000h, 0B8h, 03Fh, 000h
    db 000h, 000h, 02Bh, 0C1h, 089h, 004h, 024h, 0DBh, 004h, 024h, 053h, 055h, 056h, 0DCh, 00Dh
    dd __real@3f8a01a01a01a01a
    db 057h, 033h, 0EDh, 0DCh, 005h
    dd ?g_bfmeSubB3@@3NA
    db 0DDh, 05Ch, 024h, 010h, 0DDh, 005h
    dd __real@c040000000000000
    db 0DDh, 044h, 024h, 010h, 0DCh, 04Ch, 024h, 010h, 0DCh, 0C0h, 0DDh, 005h
    dd __real@401921fb53c8d4f1
    db 0D9h, 0FAh, 0DCh, 04Ch, 024h, 010h, 08Dh, 064h, 024h, 000h, 0D9h, 0C2h, 0D9h, 0C0h, 0D8h, 0C9h
    db 0D8h, 0F3h, 0D9h, 0E0h, 0D9h, 0EAh, 0DEh, 0C9h, 0D9h, 0C0h, 0D9h, 0FCh, 0D9h, 0C9h, 0D8h, 0E1h
    db 0D9h, 0F0h, 0D9h, 0E8h, 0DEh, 0C1h, 0D9h, 0FDh, 0DDh, 0D9h, 0D8h, 0F2h, 0DCh, 00Dh
    dd __real@4070000000000000
    db 0DCh, 005h
    dd __real@3fe0000000000000
    call __ftol2
    db 0DDh, 0D8h, 08Bh, 0F0h, 085h, 0F6h, 074h, 031h, 033h, 0C0h, 085h, 0F6h, 07Eh, 029h, 0D9h, 0C2h
    db 08Dh, 07Ch, 02Ch, 020h
    call __ftol2
    db 08Ah, 0D8h, 08Ah, 0FBh, 08Bh, 0CEh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 08Bh, 0C3h, 0C1h, 0E0h, 010h
    db 066h, 08Bh, 0C3h, 0F3h, 0ABh, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0AAh, 08Bh, 0C6h, 003h, 0E8h
    db 0D9h, 0CAh, 0DCh, 005h
    dd ?g_bfmeSubB3@@3NA
    db 0D9h, 0CAh, 0D9h, 0C2h, 0DCh, 01Dh
    dd __real@4040000000000000
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Bh, 077h, 0FFh, 0FFh, 0FFh, 081h, 0FDh, 000h, 001h, 000h
    db 000h, 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h, 07Dh, 01Bh, 0B9h, 000h, 001h, 000h, 000h, 02Bh, 0CDh
    db 08Bh, 0D1h, 0C1h, 0E9h, 002h, 033h, 0C0h, 08Dh, 07Ch, 02Ch, 020h, 0F3h, 0ABh, 08Bh, 0CAh, 083h
    db 0E1h, 003h, 0F3h, 0AAh, 08Bh, 035h
    dd __imp__rand
    db 033h, 0FFh, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 0FFh, 0D6h, 025h, 0FFh, 000h, 000h, 000h, 08Ah
    db 044h, 004h, 020h, 088h, 084h, 03Ch, 04Ch, 001h, 000h, 000h, 047h, 081h, 0FFh, 000h, 008h, 000h
    db 000h, 072h, 0E5h, 08Bh, 084h, 024h, 058h, 009h, 000h, 000h, 085h, 0C0h, 00Fh, 086h, 096h, 000h
    db 000h, 000h, 08Bh, 0ACh, 024h, 050h, 009h, 000h, 000h, 08Ah, 05Ch, 024h, 020h, 089h, 06Ch, 024h
    db 01Ch, 089h, 044h, 024h, 010h, 08Dh, 049h, 000h, 0FFh, 0D6h, 08Bh, 094h, 024h, 054h, 009h, 000h
    db 000h, 025h, 0FFh, 000h, 000h, 000h, 085h, 0D2h, 08Dh, 0BCh, 004h, 04Ch, 001h, 000h, 000h, 076h
    db 04Fh, 00Fh, 0BEh, 0F3h, 08Ah, 0CBh, 0F7h, 0DEh, 0F6h, 0D9h, 08Bh, 0C5h, 02Bh, 0FDh, 089h, 054h
    db 024h, 018h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 00Fh, 0B6h, 010h, 03Bh, 0D6h, 07Dh, 002h, 088h
    db 008h, 00Fh, 0B6h, 028h, 08Dh, 096h, 0FFh, 000h, 000h, 000h, 03Bh, 0EAh, 07Eh, 007h, 080h, 0CAh
    db 0FFh, 02Ah, 0D3h, 088h, 010h, 08Ah, 014h, 007h, 000h, 010h, 08Bh, 054h, 024h, 018h, 040h, 04Ah
    db 089h, 054h, 024h, 018h, 075h, 0D2h, 08Bh, 06Ch, 024h, 01Ch, 08Bh, 035h
    dd __imp__rand
    db 08Bh, 08Ch, 024h, 05Ch, 009h, 000h, 000h, 08Bh, 044h, 024h, 010h, 003h, 0E9h, 048h, 089h, 06Ch
    db 024h, 01Ch, 089h, 044h, 024h, 010h, 075h, 080h, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 03Ch, 009h
    db 000h, 000h, 0C3h
?d_009a5f50@@YAXXZ ENDP
_TEXT$d00da5f50 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x009AAC30 size 67
public ?d_009aac30@@YAXXZ
?d_009aac30@@YAXXZ PROC
    db 56h, 68h, 74h, 2Fh, 13h, 01h, 68h, 0ECh, 26h, 14h, 01h, 0FFh, 15h, 0BCh, 93h, 35h
    db 01h, 8Bh, 0F0h, 8Bh, 44h, 24h, 10h, 8Bh, 90h, 08h, 02h, 00h, 00h, 8Bh, 88h, 0Ch
    db 02h, 00h, 00h, 56h, 8Dh, 0Ch, 4Ah, 8Bh, 90h, 54h, 02h, 00h, 00h, 6Ah, 01h, 51h
    db 52h, 0FFh, 15h, 0F4h, 93h, 35h, 01h, 56h, 0FFh, 15h, 0A0h, 93h, 35h, 01h, 83h, 0C4h
    db 1Ch, 5Eh, 0C3h
?d_009aac30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009AAD20 size 208
public ?d_009aad20@@YAXXZ
?d_009aad20@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 0BEh, 70h, 02h, 00h, 00h, 33h, 0C0h, 0B9h, 20h
    db 00h, 00h, 00h, 0F3h, 0ABh, 8Bh, 46h, 08h, 85h, 0C0h, 75h, 33h, 8Bh, 4Eh, 74h, 8Bh
    db 96h, 70h, 02h, 00h, 00h, 51h, 8Bh, 8Eh, 54h, 02h, 00h, 00h, 52h, 8Bh, 46h, 70h
    db 8Bh, 96h, 5Ch, 02h, 00h, 00h, 03h, 0C8h, 51h, 03h, 0D0h, 8Bh, 86h, 84h, 02h, 00h
    db 00h, 52h, 50h, 0FFh, 15h, 84h, 6Dh, 35h, 01h, 83h, 0C4h, 14h, 5Fh, 5Eh, 0C3h, 8Bh
    db 0Ch, 85h, 70h, 77h, 2Dh, 01h, 85h, 0C9h, 74h, 3Ch, 8Bh, 4Ch, 24h, 10h, 8Bh, 96h
    db 84h, 02h, 00h, 00h, 51h, 52h, 56h, 0E8h, 0A4h, 0A7h, 00h, 00h, 8Bh, 46h, 74h, 8Bh
    db 56h, 70h, 8Bh, 8Eh, 5Ch, 02h, 00h, 00h, 50h, 8Bh, 86h, 84h, 02h, 00h, 00h, 03h
    db 0CAh, 8Bh, 96h, 70h, 02h, 00h, 00h, 51h, 52h, 50h, 0FFh, 15h, 88h, 6Dh, 35h, 01h
    db 83h, 0C4h, 1Ch, 5Fh, 5Eh, 0C3h, 83h, 0F8h, 05h, 8Bh, 4Eh, 74h, 8Bh, 96h, 70h, 02h
    db 00h, 00h, 51h, 52h, 75h, 0Bh, 8Bh, 8Eh, 4Ch, 02h, 00h, 00h, 0E9h, 7Ch, 0FFh, 0FFh
    db 0FFh, 8Bh, 4Eh, 70h, 8Bh, 86h, 5Ch, 02h, 00h, 00h, 03h, 0C1h, 8Bh, 8Eh, 84h, 02h
    db 00h, 00h, 50h, 51h, 0FFh, 15h, 8Ch, 6Dh, 35h, 01h, 83h, 0C4h, 10h, 5Fh, 5Eh, 0C3h
?d_009aad20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009AC2F0 size 145
public ?d_009ac2f0@@YAXXZ
?d_009ac2f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 8Bh, 54h, 24h, 08h, 53h, 8Bh, 58h, 0Ch, 56h
    db 8Dh, 71h, 0FFh, 0Fh, 0AFh, 74h, 24h, 14h, 0C1h, 0EEh, 08h, 46h, 85h, 0D2h, 57h, 8Bh
    db 38h, 74h, 06h, 03h, 0FEh, 2Bh, 0CEh, 8Bh, 0F1h, 81h, 0FEh, 80h, 00h, 00h, 00h, 73h
    db 54h, 55h, 0D1h, 0E6h, 85h, 0FFh, 79h, 1Fh, 8Bh, 48h, 10h, 49h, 78h, 12h, 8Bh, 0FFh
    db 8Bh, 50h, 14h, 03h, 0D1h, 80h, 3Ah, 0FFh, 75h, 06h, 49h, 0C6h, 02h, 00h, 79h, 0F0h
    db 8Bh, 50h, 14h, 03h, 0CAh, 0FEh, 01h, 0D1h, 0E7h, 43h, 75h, 20h, 8Bh, 50h, 14h, 8Bh
    db 68h, 10h, 8Bh, 0CFh, 0C1h, 0E9h, 18h, 88h, 0Ch, 2Ah, 8Bh, 50h, 10h, 42h, 0BBh, 0F8h
    db 0FFh, 0FFh, 0FFh, 89h, 50h, 10h, 81h, 0E7h, 0FFh, 0FFh, 0FFh, 00h, 81h, 0FEh, 80h, 00h
    db 00h, 00h, 72h, 0AEh, 5Dh, 89h, 38h, 5Fh, 89h, 70h, 04h, 5Eh, 89h, 58h, 0Ch, 5Bh
    db 0C3h
?d_009ac2f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009AC4B0 size 47
public ?d_009ac4b0@@YAXXZ
?d_009ac4b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 0Ch, 85h, 0C0h, 8Bh, 44h, 24h, 04h, 74h, 14h
    db 8Dh, 14h, 8Dh, 00h, 00h, 00h, 00h, 0B9h, 64h, 30h, 14h, 01h, 2Bh, 0CAh, 8Bh, 11h
    db 01h, 50h, 1Ch, 0C3h, 8Bh, 14h, 8Dh, 68h, 2Ch, 14h, 01h, 01h, 50h, 1Ch, 0C3h
?d_009ac4b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009ACC40 size 64
public ?d_009acc40@@YAXXZ
?d_009acc40@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 83h, 3Eh, 02h, 7Ch, 1Bh, 8Bh, 46h, 0Ch, 8Bh, 0Dh, 9Ch
    db 6Ah, 35h, 01h, 8Bh, 04h, 81h, 50h, 56h, 0E8h, 43h, 0FFh, 0FFh, 0FFh, 83h, 0C4h, 08h
    db 89h, 46h, 38h, 5Eh, 0C3h, 8Bh, 56h, 0Ch, 0A1h, 9Ch, 6Ah, 35h, 01h, 8Bh, 04h, 90h
    db 50h, 56h, 0FFh, 15h, 64h, 6Eh, 35h, 01h, 83h, 0C4h, 08h, 89h, 46h, 38h, 5Eh, 0C3h
?d_009acc40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x009B8130 size 5572
_TEXT ENDS
_TEXT$d00db8130 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB8130 size 5572
public ?d_009b8130@@YAXXZ
?d_009b8130@@YAXXZ PROC
    db 053h, 08Bh, 0DCh, 083h, 0ECh, 008h, 083h, 0E4h, 0F0h, 083h, 0C4h, 004h, 055h, 08Bh, 06Bh, 004h
    db 089h, 06Ch, 024h, 004h, 08Bh, 0ECh, 081h, 0ECh, 0F8h, 001h, 000h, 000h, 08Bh, 043h, 008h, 08Bh
    db 050h, 00Ch, 0A1h
    dd ?g_rva01356A9C@@3PAHA
    db 08Bh, 004h, 090h, 08Bh, 04Bh, 01Ch, 08Bh, 053h, 018h, 066h, 089h, 045h, 080h, 066h, 089h, 045h
    db 082h, 066h, 089h, 045h, 084h, 066h, 089h, 045h, 086h, 08Dh, 004h, 00Ah, 03Bh, 0C8h, 056h, 057h
    db 089h, 04Dh, 0ECh, 089h, 085h, 06Ch, 0FFh, 0FFh, 0FFh, 00Fh, 083h, 065h, 015h, 000h, 000h, 08Bh
    db 04Bh, 00Ch, 08Bh, 053h, 014h, 0C1h, 0E0h, 002h, 089h, 045h, 0FCh, 08Bh, 043h, 010h, 089h, 04Dh
    db 0F0h, 08Dh, 00Ch, 0D5h, 000h, 000h, 000h, 000h, 089h, 045h, 0F8h, 02Bh, 0C1h, 089h, 045h, 0F4h
    db 08Bh, 055h, 0F0h, 08Bh, 045h, 0F8h, 08Bh, 04Bh, 008h, 089h, 055h, 094h, 08Bh, 051h, 024h, 089h
    db 045h, 098h, 08Bh, 045h, 0FCh, 08Bh, 00Ch, 010h, 08Bh, 053h, 020h, 08Bh, 004h, 08Ah, 089h, 045h
    db 09Ch, 050h, 055h, 051h, 052h, 056h, 057h, 08Bh, 045h, 09Ch, 033h, 0D2h, 08Bh, 04Bh, 014h, 00Fh
    db 075h, 0F6h, 00Fh, 06Eh, 0E8h, 08Bh, 045h, 094h, 00Fh, 071h, 0D6h, 00Eh, 00Fh, 061h, 0EDh, 08Dh
    db 0B5h, 010h, 0FEh, 0FFh, 0FFh, 00Fh, 062h, 0EDh, 02Bh, 0D1h, 00Fh, 0D5h, 0F5h, 00Fh, 07Fh, 0ADh
    db 050h, 0FFh, 0FFh, 0FFh, 08Dh, 0BDh, 090h, 0FEh, 0FFh, 0FFh, 00Fh, 0EFh, 0FFh, 00Fh, 0D5h, 0F5h
    db 08Dh, 004h, 090h, 00Fh, 06Fh, 004h, 010h, 00Fh, 07Fh, 0C1h, 00Fh, 060h, 0C7h, 00Fh, 071h, 0D6h
    db 005h, 00Fh, 07Fh, 0B5h, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 010h, 00Fh, 068h, 0CFh, 00Fh, 07Fh
    db 0D3h, 00Fh, 060h, 0D7h, 00Fh, 07Fh, 007h, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 04Fh, 008h, 00Fh, 06Fh
    db 024h, 008h, 00Fh, 07Fh, 057h, 010h, 00Fh, 07Fh, 05Fh, 018h, 00Fh, 07Fh, 0E5h, 00Fh, 060h, 0E7h
    db 00Fh, 06Fh, 004h, 048h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C1h, 00Fh, 07Fh, 067h, 020h, 00Fh, 060h
    db 0C7h, 08Dh, 004h, 088h, 00Fh, 07Fh, 06Fh, 028h, 00Fh, 068h, 0CFh, 00Fh, 06Fh, 014h, 010h, 00Fh
    db 07Fh, 047h, 030h, 00Fh, 07Fh, 0D3h, 00Fh, 060h, 0D7h, 00Fh, 07Fh, 04Fh, 038h, 00Fh, 068h, 0DFh
    db 00Fh, 06Fh, 020h, 00Fh, 07Fh, 057h, 040h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 05Fh, 048h, 00Fh, 060h
    db 0E7h, 00Fh, 068h, 0EFh, 00Fh, 06Fh, 004h, 008h, 00Fh, 07Fh, 067h, 050h, 00Fh, 07Fh, 0C1h, 00Fh
    db 07Fh, 06Fh, 058h, 00Fh, 060h, 0C7h, 00Fh, 068h, 0CFh, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h
    db 00Fh, 07Fh, 0D3h, 00Fh, 07Fh, 047h, 060h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 06Fh, 024h
    db 010h, 00Fh, 07Fh, 04Fh, 068h, 00Fh, 07Fh, 0E5h, 00Fh, 060h, 0E7h, 00Fh, 07Fh, 057h, 070h, 00Fh
    db 07Fh, 05Fh, 078h, 00Fh, 06Fh, 000h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C1h, 00Fh, 07Fh, 0A7h, 080h
    db 000h, 000h, 000h, 00Fh, 060h, 0C7h, 00Fh, 068h, 0CFh, 00Fh, 07Fh, 0AFh, 088h, 000h, 000h, 000h
    db 00Fh, 07Fh, 087h, 090h, 000h, 000h, 000h, 00Fh, 07Fh, 08Fh, 098h, 000h, 000h, 000h, 00Fh, 075h
    db 0DBh, 00Fh, 071h, 0F3h, 00Fh, 00Fh, 071h, 0D3h, 008h, 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh, 077h
    db 050h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h
    db 00Fh, 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh, 07Fh, 0F5h, 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh, 077h
    db 060h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h
    db 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh, 077h
    db 070h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h
    db 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h
    db 080h, 000h, 000h, 000h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h
    db 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 07Fh, 0DFh, 00Fh
    db 071h, 0D7h, 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0E6h, 00Fh, 0FDh, 0C7h, 00Fh, 0FDh, 0E7h, 00Fh
    db 071h, 0E2h, 001h, 00Fh, 071h, 0E6h, 001h, 00Fh, 071h, 0E0h, 001h, 00Fh, 071h, 0E4h, 001h, 00Fh
    db 0D5h, 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h, 0EEh, 00Fh, 06Fh, 0BDh, 070h, 0FFh
    db 0FFh, 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 07Fh, 04Dh, 0B0h, 00Fh, 07Fh, 06Dh, 0C0h
    db 00Fh, 0F9h, 0CFh, 00Fh, 0F9h, 0EFh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 071h
    db 0E1h, 00Fh, 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh, 07Fh, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h
    db 00Fh, 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0FAh, 00Fh, 0D9h, 0FCh, 00Fh, 0D9h, 0E2h
    db 00Fh, 0EBh, 0FCh, 00Fh, 0F9h, 0BDh, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E7h, 00Fh, 00Fh, 0DBh
    db 0FEh, 083h, 0C7h, 008h, 00Fh, 06Fh, 057h, 010h, 00Fh, 06Fh, 077h, 050h, 00Fh, 0F9h, 0D3h, 00Fh
    db 0F9h, 0F3h, 00Fh, 07Fh, 0D0h, 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 07Fh
    db 0D1h, 00Fh, 07Fh, 0F5h, 00Fh, 06Fh, 057h, 020h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0D3h, 00Fh
    db 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh
    db 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 030h, 00Fh, 06Fh, 077h, 070h, 00Fh, 0F9h, 0D3h, 00Fh
    db 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh
    db 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h, 080h, 000h, 000h, 000h, 00Fh
    db 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h
    db 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh, 071h, 0D3h, 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh
    db 0E6h, 00Fh, 0FDh, 0C3h, 00Fh, 0FDh, 0E3h, 00Fh, 071h, 0E2h, 001h, 00Fh, 071h, 0E6h, 001h, 00Fh
    db 071h, 0E0h, 001h, 00Fh, 071h, 0E4h, 001h, 00Fh, 0D5h, 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh
    db 00Fh, 0F9h, 0EEh, 00Fh, 07Fh, 04Dh, 0D0h, 00Fh, 07Fh, 06Dh, 0A0h, 00Fh, 06Fh, 09Dh, 070h, 0FFh
    db 0FFh, 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h, 0CBh, 00Fh, 0F9h, 0EBh, 00Fh, 071h
    db 0E2h, 00Fh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh
    db 047h, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh
    db 07Fh, 0C2h, 00Fh, 0D9h, 0C4h, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh, 0C4h, 00Fh, 0F9h, 085h, 050h, 0FFh
    db 0FFh, 0FFh, 00Fh, 071h, 0E0h, 00Fh, 00Fh, 0DBh, 0C6h, 083h, 0EFh, 008h, 00Fh, 06Fh, 04Dh, 080h
    db 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h
    db 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 040h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 030h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh
    db 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 0A5h, 050h, 0FFh, 0FFh
    db 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh
    db 0CCh, 00Fh, 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh
    db 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h
    db 0A5h, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh
    db 0DFh, 0D3h, 00Fh, 0EBh, 0D4h, 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh
    db 067h, 010h, 00Fh, 0FDh, 05Fh, 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh
    db 025h
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
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0ADh, 040h, 0FFh, 0FFh, 0FFh
    db 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h, 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h
    db 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 0FDh, 0E2h, 00Fh, 06Fh, 0ADh, 030h, 0FFh
    db 0FFh, 0FFh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h, 030h, 00Fh
    db 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h
    db 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh
    db 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h, 0C7h, 008h
    db 083h, 0C6h, 008h, 00Fh, 06Fh, 04Dh, 080h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh
    db 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 0DCh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh
    db 00Fh, 071h, 0E3h, 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 040h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 030h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh
    db 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 0A5h, 050h, 0FFh, 0FFh
    db 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh
    db 0CCh, 00Fh, 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh
    db 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h
    db 0A5h, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh
    db 0DFh, 0D3h, 00Fh, 0EBh, 0D4h, 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh
    db 067h, 010h, 00Fh, 0FDh, 05Fh, 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh
    db 025h
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
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0ADh, 040h, 0FFh, 0FFh, 0FFh
    db 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h, 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h
    db 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 0FDh, 0E2h, 00Fh, 06Fh, 0ADh, 030h, 0FFh
    db 0FFh, 0FFh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h, 030h, 00Fh
    db 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h
    db 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh
    db 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h, 0C7h, 008h
    db 083h, 0EEh, 008h, 08Bh, 06Dh, 098h, 08Dh, 06Ch, 095h, 000h, 00Fh, 06Fh, 006h, 00Fh, 067h, 046h
    db 008h, 00Fh, 07Fh, 045h, 000h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 067h, 04Eh, 018h, 00Fh, 07Fh, 04Ch
    db 00Dh, 000h, 00Fh, 06Fh, 056h, 020h, 00Fh, 067h, 056h, 028h, 00Fh, 07Fh, 054h, 04Dh, 000h, 00Fh
    db 06Fh, 05Eh, 030h, 00Fh, 067h, 05Eh, 038h, 08Dh, 06Ch, 08Dh, 000h, 00Fh, 07Fh, 05Ch, 015h, 000h
    db 00Fh, 06Fh, 046h, 040h, 00Fh, 067h, 046h, 048h, 00Fh, 07Fh, 045h, 000h, 00Fh, 06Fh, 04Eh, 050h
    db 00Fh, 067h, 04Eh, 058h, 00Fh, 07Fh, 04Ch, 00Dh, 000h, 00Fh, 06Fh, 056h, 060h, 00Fh, 067h, 056h
    db 068h, 00Fh, 07Fh, 054h, 04Dh, 000h, 00Fh, 06Fh, 05Eh, 070h, 00Fh, 067h, 05Eh, 078h, 08Dh, 06Ch
    db 04Dh, 000h, 00Fh, 07Fh, 05Ch, 00Dh, 000h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h, 00Fh, 0B7h, 07Dh
    db 0D4h, 00Fh, 0B7h, 075h, 0D6h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0D2h, 003h, 0F7h, 00Fh, 0B7h, 07Dh
    db 0D0h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B6h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B4h, 08Bh, 053h, 008h
    db 08Bh, 042h, 028h, 08Bh, 04Dh, 0ECh, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B2h, 003h, 0F7h, 00Fh, 0B7h
    db 07Dh, 0B0h, 003h, 0F7h, 08Bh, 03Ch, 088h, 003h, 0FEh, 08Bh, 075h, 0FCh, 089h, 03Ch, 088h, 00Fh
    db 0B7h, 07Dh, 0A4h, 08Dh, 004h, 088h, 08Bh, 042h, 028h, 003h, 0C6h, 00Fh, 0B7h, 075h, 0A6h, 003h
    db 0F7h, 00Fh, 0B7h, 07Dh, 0A2h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0A0h, 003h, 0F7h, 00Fh, 0B7h, 07Dh
    db 0C6h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0C4h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0C2h, 003h, 0F7h, 00Fh
    db 0B7h, 07Dh, 0C0h, 003h, 0F7h, 001h, 030h, 03Bh, 04Bh, 01Ch, 075h, 026h, 08Bh, 07Dh, 0F0h, 08Bh
    db 075h, 0F8h, 08Bh, 055h, 0F4h, 0B8h, 008h, 000h, 000h, 000h, 041h, 003h, 0F8h, 003h, 0F0h, 003h
    db 0D0h, 089h, 04Dh, 0ECh, 089h, 07Dh, 0F0h, 089h, 075h, 0F8h, 089h, 055h, 0F4h, 0E9h, 06Fh, 00Bh
    db 000h, 000h, 08Bh, 052h, 024h, 08Bh, 00Ch, 08Ah, 08Bh, 045h, 0F4h, 08Bh, 053h, 020h, 08Bh, 00Ch
    db 08Ah, 066h, 00Fh, 0B6h, 050h, 0FBh, 066h, 089h, 095h, 090h, 0FEh, 0FFh, 0FFh, 089h, 04Dh, 09Ch
    db 066h, 00Fh, 0B6h, 048h, 004h, 066h, 089h, 08Dh, 020h, 0FFh, 0FFh, 0FFh, 08Bh, 04Bh, 014h, 066h
    db 00Fh, 0B6h, 054h, 008h, 0FBh, 066h, 089h, 095h, 092h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h
    db 008h, 004h, 066h, 089h, 095h, 022h, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 048h, 0FBh, 066h
    db 089h, 095h, 094h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 048h, 004h, 066h, 089h, 095h, 024h
    db 0FFh, 0FFh, 0FFh, 08Dh, 014h, 049h, 066h, 00Fh, 0B6h, 074h, 010h, 0FBh, 066h, 00Fh, 0B6h, 054h
    db 010h, 004h, 066h, 089h, 095h, 026h, 0FFh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 088h, 0FBh, 066h
    db 089h, 095h, 098h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 088h, 004h, 066h, 089h, 095h, 028h
    db 0FFh, 0FFh, 0FFh, 08Dh, 014h, 089h, 066h, 089h, 0B5h, 096h, 0FEh, 0FFh, 0FFh, 066h, 00Fh, 0B6h
    db 074h, 010h, 0FBh, 066h, 00Fh, 0B6h, 054h, 010h, 004h, 066h, 089h, 095h, 02Ah, 0FFh, 0FFh, 0FFh
    db 08Dh, 014h, 049h, 06Bh, 0C9h, 007h, 0D1h, 0E2h, 066h, 089h, 0B5h, 09Ah, 0FEh, 0FFh, 0FFh, 066h
    db 00Fh, 0B6h, 074h, 010h, 0FBh, 066h, 00Fh, 0B6h, 054h, 010h, 004h, 066h, 089h, 095h, 02Ch, 0FFh
    db 0FFh, 0FFh, 066h, 00Fh, 0B6h, 054h, 008h, 0FBh, 089h, 045h, 098h, 089h, 045h, 094h, 066h, 00Fh
    db 0B6h, 044h, 008h, 004h, 066h, 089h, 0B5h, 09Ch, 0FEh, 0FFh, 0FFh, 066h, 089h, 095h, 09Eh, 0FEh
    db 0FFh, 0FFh, 066h, 089h, 085h, 02Eh, 0FFh, 0FFh, 0FFh, 050h, 055h, 08Bh, 045h, 09Ch, 00Fh, 06Eh
    db 0C0h, 051h, 00Fh, 061h, 0C0h, 00Fh, 06Fh, 00Dh
    dd g_Va012D86C0
    db 052h, 00Fh, 062h, 0C0h, 00Fh, 07Fh, 085h, 050h, 0FFh, 0FFh, 0FFh, 056h, 00Fh, 0D5h, 0C8h, 00Fh
    db 0D5h, 0C8h, 057h, 00Fh, 071h, 0D1h, 005h, 00Fh, 07Fh, 08Dh, 070h, 0FFh, 0FFh, 0FFh, 08Bh, 045h
    db 094h, 033h, 0D2h, 083h, 0E8h, 004h, 08Dh, 0B5h, 010h, 0FEh, 0FFh, 0FFh, 08Dh, 0BDh, 090h, 0FEh
    db 0FFh, 0FFh, 08Bh, 04Bh, 014h, 02Bh, 0D1h, 00Fh, 06Fh, 000h, 00Fh, 06Fh, 00Ch, 008h, 00Fh, 06Fh
    db 014h, 048h, 08Dh, 004h, 088h, 00Fh, 06Fh, 01Ch, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 060h, 0C1h, 00Fh
    db 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h, 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 061h
    db 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h, 00Fh, 0EFh, 0FFh
    db 00Fh, 07Fh, 0C5h, 00Fh, 060h, 0C7h, 00Fh, 07Fh, 047h, 010h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C8h
    db 00Fh, 07Fh, 06Fh, 020h, 00Fh, 060h, 0CFh, 00Fh, 068h, 0C7h, 00Fh, 07Fh, 04Fh, 030h, 00Fh, 07Fh
    db 0D3h, 00Fh, 07Fh, 0E5h, 00Fh, 07Fh, 047h, 040h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh
    db 057h, 050h, 00Fh, 060h, 0E7h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 05Fh, 060h, 00Fh, 06Fh, 000h, 00Fh
    db 06Fh, 00Ch, 008h, 00Fh, 07Fh, 067h, 070h, 00Fh, 06Fh, 014h, 048h, 08Dh, 004h, 088h, 00Fh, 07Fh
    db 0AFh, 080h, 000h, 000h, 000h, 00Fh, 07Fh, 0C4h, 00Fh, 06Fh, 01Ch, 010h, 00Fh, 060h, 0C1h, 00Fh
    db 068h, 0E1h, 00Fh, 07Fh, 0D5h, 00Fh, 060h, 0D3h, 00Fh, 068h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 061h
    db 0C2h, 00Fh, 069h, 0CAh, 00Fh, 07Fh, 0E2h, 00Fh, 069h, 0E5h, 00Fh, 061h, 0D5h, 00Fh, 07Fh, 0C5h
    db 00Fh, 060h, 0C7h, 00Fh, 07Fh, 047h, 018h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 0C8h, 00Fh, 07Fh, 06Fh
    db 028h, 00Fh, 060h, 0CFh, 00Fh, 068h, 0C7h, 00Fh, 07Fh, 04Fh, 038h, 00Fh, 07Fh, 0D3h, 00Fh, 07Fh
    db 0E5h, 00Fh, 07Fh, 047h, 048h, 00Fh, 060h, 0D7h, 00Fh, 068h, 0DFh, 00Fh, 07Fh, 057h, 058h, 00Fh
    db 060h, 0E7h, 00Fh, 068h, 0EFh, 00Fh, 07Fh, 05Fh, 068h, 00Fh, 07Fh, 067h, 078h, 00Fh, 07Fh, 0AFh
    db 088h, 000h, 000h, 000h, 00Fh, 075h, 0DBh, 00Fh, 071h, 0F3h, 00Fh, 00Fh, 071h, 0D3h, 008h, 00Fh
    db 06Fh, 057h, 010h, 00Fh, 06Fh, 077h, 050h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 07Fh, 0D0h
    db 00Fh, 07Fh, 0F4h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 07Fh, 0D1h, 00Fh, 07Fh, 0F5h, 00Fh
    db 06Fh, 057h, 020h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h
    db 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh
    db 06Fh, 057h, 030h, 00Fh, 06Fh, 077h, 070h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h, 00Fh, 0FDh, 0C2h
    db 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh, 0FDh, 0EEh, 00Fh
    db 06Fh, 057h, 040h, 00Fh, 06Fh, 0B7h, 080h, 000h, 000h, 000h, 00Fh, 0F9h, 0D3h, 00Fh, 0F9h, 0F3h
    db 00Fh, 0FDh, 0C2h, 00Fh, 0FDh, 0E6h, 00Fh, 0D5h, 0D2h, 00Fh, 0D5h, 0F6h, 00Fh, 0FDh, 0CAh, 00Fh
    db 0FDh, 0EEh, 00Fh, 07Fh, 0DFh, 00Fh, 071h, 0D7h, 007h, 00Fh, 07Fh, 0C2h, 00Fh, 07Fh, 0E6h, 00Fh
    db 0FDh, 0C7h, 00Fh, 0FDh, 0E7h, 00Fh, 071h, 0E2h, 001h, 00Fh, 071h, 0E6h, 001h, 00Fh, 071h, 0E0h
    db 001h, 00Fh, 071h, 0E4h, 001h, 00Fh, 0D5h, 0D0h, 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h
    db 0EEh, 00Fh, 07Fh, 04Dh, 0B0h, 00Fh, 07Fh, 06Dh, 0C0h, 00Fh, 06Fh, 0BDh, 070h, 0FFh, 0FFh, 0FFh
    db 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h, 0CFh, 00Fh, 0F9h, 0EFh, 00Fh, 071h, 0E1h, 00Fh
    db 00Fh, 071h, 0E5h, 00Fh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 06Fh, 07Fh, 040h
    db 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh, 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0FAh
    db 00Fh, 0D9h, 0FCh, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh, 0FCh, 00Fh, 0F9h, 0BDh, 050h, 0FFh, 0FFh, 0FFh
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
    db 00Fh, 0D5h, 0F4h, 00Fh, 0F9h, 0CAh, 00Fh, 0F9h, 0EEh, 00Fh, 07Fh, 04Dh, 0D0h, 00Fh, 07Fh, 06Dh
    db 0A0h, 00Fh, 06Fh, 09Dh, 070h, 0FFh, 0FFh, 0FFh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0EEh, 00Fh, 0F9h
    db 0CBh, 00Fh, 0F9h, 0EBh, 00Fh, 071h, 0E6h, 00Fh, 00Fh, 071h, 0E2h, 00Fh, 00Fh, 071h, 0E1h, 00Fh
    db 00Fh, 071h, 0E5h, 00Fh, 00Fh, 06Fh, 047h, 040h, 00Fh, 0DFh, 0D1h, 00Fh, 0DFh, 0F5h, 00Fh, 06Fh
    db 067h, 050h, 00Fh, 0DBh, 0F2h, 00Fh, 07Fh, 0C2h, 00Fh, 0D9h, 0C4h, 00Fh, 0D9h, 0E2h, 00Fh, 0EBh
    db 0C4h, 00Fh, 0F9h, 085h, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E0h, 00Fh, 00Fh, 0DBh, 0C6h, 083h
    db 0EFh, 008h, 00Fh, 06Fh, 04Dh, 080h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh, 06Fh
    db 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh, 00Fh
    db 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 040h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 030h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh
    db 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 0A5h, 050h, 0FFh, 0FFh
    db 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh
    db 0CCh, 00Fh, 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh
    db 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h
    db 0A5h, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh
    db 0DFh, 0D3h, 00Fh, 0EBh, 0D4h, 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh
    db 067h, 010h, 00Fh, 0FDh, 05Fh, 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh
    db 025h
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
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0ADh, 040h, 0FFh, 0FFh, 0FFh
    db 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h, 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h
    db 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 0FDh, 0E2h, 00Fh, 06Fh, 0ADh, 030h, 0FFh
    db 0FFh, 0FFh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h, 030h, 00Fh
    db 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h
    db 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh
    db 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E7h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 083h, 0C7h, 008h
    db 083h, 0C6h, 008h, 00Fh, 06Fh, 04Dh, 080h, 00Fh, 06Fh, 05Fh, 030h, 00Fh, 06Fh, 067h, 040h, 00Fh
    db 06Fh, 06Fh, 050h, 00Fh, 06Fh, 077h, 060h, 00Fh, 0F9h, 0ECh, 00Fh, 0F9h, 0DEh, 00Fh, 07Fh, 0ECh
    db 00Fh, 0FDh, 0E5h, 00Fh, 0FDh, 01Dh
    dd g_Va012D86D0
    db 00Fh, 0FDh, 0ECh, 00Fh, 0FDh, 0DDh, 00Fh, 071h, 0E3h, 003h, 00Fh, 07Fh, 0DAh, 00Fh, 071h, 0E3h
    db 00Fh, 00Fh, 0EFh, 0D3h, 00Fh, 0E9h, 0D3h, 00Fh, 0EBh, 01Dh
    dd g_Va012D86E0
    db 00Fh, 07Fh, 0CCh, 00Fh, 0F9h, 0CAh, 00Fh, 07Fh, 0CDh, 00Fh, 071h, 0E1h, 00Fh, 00Fh, 0EFh, 0E9h
    db 00Fh, 0E9h, 0E9h, 00Fh, 0D9h, 0E5h, 00Fh, 0D5h, 0E3h, 00Fh, 06Fh, 04Fh, 040h, 00Fh, 06Fh, 057h
    db 050h, 00Fh, 0FDh, 0CCh, 00Fh, 0F9h, 0D4h, 00Fh, 0EFh, 0F6h, 00Fh, 067h, 0C9h, 00Fh, 067h, 0D2h
    db 00Fh, 060h, 0CEh, 00Fh, 07Fh, 08Dh, 040h, 0FFh, 0FFh, 0FFh, 00Fh, 060h, 0D6h, 00Fh, 07Fh, 095h
    db 030h, 0FFh, 0FFh, 0FFh, 00Fh, 06Fh, 02Fh, 00Fh, 06Fh, 067h, 010h, 00Fh, 07Fh, 0E3h, 00Fh, 07Fh
    db 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h, 0A5h, 050h, 0FFh, 0FFh
    db 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E1h, 00Fh, 0DBh, 0E6h, 00Fh, 0DFh, 0CBh, 00Fh, 0EBh
    db 0CCh, 00Fh, 06Fh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0AFh, 090h, 000h, 000h, 000h, 00Fh
    db 07Fh, 0E3h, 00Fh, 07Fh, 0EEh, 00Fh, 0D9h, 0E6h, 00Fh, 0D9h, 0EBh, 00Fh, 0EBh, 0E5h, 00Fh, 0F9h
    db 0A5h, 050h, 0FFh, 0FFh, 0FFh, 00Fh, 071h, 0E4h, 00Fh, 00Fh, 07Fh, 0E2h, 00Fh, 0DBh, 0E6h, 00Fh
    db 0DFh, 0D3h, 00Fh, 0EBh, 0D4h, 00Fh, 07Fh, 0CBh, 00Fh, 0FDh, 0DBh, 00Fh, 0FDh, 0D9h, 00Fh, 06Fh
    db 067h, 010h, 00Fh, 0FDh, 05Fh, 020h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0FDh, 05Fh, 040h, 00Fh, 0FDh
    db 025h
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
    db 067h, 070h, 00Fh, 0FDh, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 06Fh, 0ADh, 040h, 0FFh, 0FFh, 0FFh
    db 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h
    db 030h, 00Fh, 06Fh, 06Fh, 050h, 00Fh, 0F9h, 05Fh, 010h, 00Fh, 0FDh, 09Fh, 080h, 000h, 000h, 000h
    db 00Fh, 07Fh, 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 010h, 00Fh, 0F9h, 067h
    db 020h, 00Fh, 0F9h, 0A7h, 080h, 000h, 000h, 000h, 00Fh, 0FDh, 0E2h, 00Fh, 06Fh, 0ADh, 030h, 0FFh
    db 0FFh, 0FFh, 00Fh, 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh
    db 07Fh, 066h, 040h, 00Fh, 06Fh, 06Fh, 060h, 00Fh, 0F9h, 05Fh, 020h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh
    db 0ECh, 00Fh, 0FDh, 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 020h, 00Fh, 0F9h, 067h, 030h, 00Fh
    db 071h, 0E4h, 004h, 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 050h
    db 00Fh, 06Fh, 06Fh, 070h, 00Fh, 0F9h, 05Fh, 030h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 030h, 00Fh, 0F9h, 067h, 040h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 060h, 00Fh, 06Fh, 0AFh
    db 080h, 000h, 000h, 000h, 00Fh, 0F9h, 05Fh, 040h, 00Fh, 0FDh, 0DAh, 00Fh, 07Fh, 0ECh, 00Fh, 0FDh
    db 0E3h, 00Fh, 0FDh, 0E4h, 00Fh, 0FDh, 067h, 040h, 00Fh, 0F9h, 067h, 050h, 00Fh, 071h, 0E4h, 004h
    db 00Fh, 0F9h, 0E5h, 00Fh, 0DBh, 0E0h, 00Fh, 0FDh, 0E5h, 00Fh, 07Fh, 066h, 070h, 08Bh, 045h, 098h
    db 083h, 0C7h, 008h, 083h, 0EEh, 008h, 083h, 0E8h, 004h, 00Fh, 06Fh, 006h, 00Fh, 06Fh, 04Eh, 010h
    db 00Fh, 07Fh, 0C4h, 00Fh, 061h, 0C1h, 00Fh, 069h, 0E1h, 00Fh, 06Fh, 056h, 020h, 00Fh, 06Fh, 05Eh
    db 030h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h, 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h
    db 00Fh, 07Fh, 007h, 00Fh, 06Ah, 0CAh, 00Fh, 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h, 00Fh, 062h, 0C5h
    db 00Fh, 06Ah, 0E5h, 00Fh, 06Fh, 04Eh, 040h, 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh, 06Eh, 060h, 00Fh
    db 06Fh, 076h, 070h, 00Fh, 07Fh, 0CBh, 00Fh, 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh, 069h, 0DAh, 00Fh
    db 061h, 0EEh, 00Fh, 069h, 0FEh, 00Fh, 07Fh, 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h, 0CDh, 00Fh, 06Ah
    db 0D5h, 00Fh, 062h, 0DFh, 00Fh, 06Ah, 0F7h, 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h, 00Fh, 07Fh, 028h
    db 00Fh, 06Fh, 07Fh, 010h, 00Fh, 067h, 0FAh, 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h, 0C3h, 00Fh, 067h
    db 0E6h, 00Fh, 07Fh, 004h, 048h, 08Dh, 004h, 088h, 00Fh, 07Fh, 024h, 010h, 083h, 0C7h, 008h, 083h
    db 0C6h, 008h, 00Fh, 06Fh, 006h, 00Fh, 06Fh, 04Eh, 010h, 00Fh, 07Fh, 0C4h, 00Fh, 061h, 0C1h, 00Fh
    db 069h, 0E1h, 00Fh, 06Fh, 056h, 020h, 00Fh, 06Fh, 05Eh, 030h, 00Fh, 07Fh, 0D5h, 00Fh, 061h, 0D3h
    db 00Fh, 069h, 0EBh, 00Fh, 07Fh, 0C1h, 00Fh, 062h, 0C2h, 00Fh, 07Fh, 007h, 00Fh, 06Ah, 0CAh, 00Fh
    db 07Fh, 0E0h, 00Fh, 07Fh, 04Fh, 010h, 00Fh, 062h, 0C5h, 00Fh, 06Ah, 0E5h, 00Fh, 06Fh, 04Eh, 040h
    db 00Fh, 06Fh, 056h, 050h, 00Fh, 06Fh, 06Eh, 060h, 00Fh, 06Fh, 076h, 070h, 00Fh, 07Fh, 0CBh, 00Fh
    db 07Fh, 0EFh, 00Fh, 061h, 0CAh, 00Fh, 069h, 0DAh, 00Fh, 061h, 0EEh, 00Fh, 069h, 0FEh, 00Fh, 07Fh
    db 0CAh, 00Fh, 07Fh, 0DEh, 00Fh, 062h, 0CDh, 00Fh, 06Ah, 0D5h, 00Fh, 062h, 0DFh, 00Fh, 06Ah, 0F7h
    db 00Fh, 06Fh, 02Fh, 00Fh, 067h, 0E9h, 00Fh, 07Fh, 028h, 00Fh, 06Fh, 07Fh, 010h, 00Fh, 067h, 0FAh
    db 00Fh, 07Fh, 03Ch, 008h, 00Fh, 067h, 0C3h, 00Fh, 067h, 0E6h, 00Fh, 07Fh, 004h, 048h, 08Dh, 004h
    db 088h, 00Fh, 07Fh, 024h, 010h, 05Fh, 05Eh, 05Ah, 059h, 05Dh, 058h, 00Fh, 0B7h, 07Dh, 0D4h, 00Fh
    db 0B7h, 075h, 0D6h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0D2h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0D0h, 08Bh
    db 053h, 008h, 08Bh, 04Ah, 028h, 08Bh, 045h, 0ECh, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B6h, 003h, 0F7h
    db 00Fh, 0B7h, 07Dh, 0B4h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B2h, 003h, 0F7h, 00Fh, 0B7h, 07Dh, 0B0h
    db 003h, 0F7h, 08Bh, 07Ch, 081h, 0FCh, 08Dh, 04Ch, 081h, 0FCh, 003h, 0FEh, 00Fh, 0B7h, 075h, 0A4h
    db 089h, 039h, 08Bh, 052h, 028h, 08Dh, 00Ch, 082h, 00Fh, 0B7h, 055h, 0A6h, 003h, 0D6h, 00Fh, 0B7h
    db 075h, 0A2h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0A0h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0C6h, 003h, 0D6h
    db 00Fh, 0B7h, 075h, 0C4h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0C2h, 003h, 0D6h, 00Fh, 0B7h, 075h, 0C0h
    db 003h, 0D6h, 08Bh, 031h, 003h, 0F2h, 08Bh, 055h, 0F8h, 089h, 031h, 08Bh, 075h, 0F0h, 08Bh, 04Dh
    db 0F4h, 040h, 089h, 045h, 0ECh, 0B8h, 008h, 000h, 000h, 000h, 003h, 0F0h, 003h, 0D0h, 003h, 0C8h
    db 089h, 04Dh, 0F4h, 08Bh, 04Dh, 0ECh, 089h, 075h, 0F0h, 089h, 055h, 0F8h, 083h, 045h, 0FCh, 004h
    db 03Bh, 08Dh, 06Ch, 0FFh, 0FFh, 0FFh, 00Fh, 082h, 0BCh, 0EAh, 0FFh, 0FFh, 05Fh, 05Eh, 08Bh, 0E5h
    db 05Dh, 08Bh, 0E3h, 05Bh, 0C3h
?d_009b8130@@YAXXZ ENDP
_TEXT$d00db8130 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
