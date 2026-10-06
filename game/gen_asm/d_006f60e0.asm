.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?ClientAt012F1464@@3PAVClient0009A580@@A:BYTE
EXTERN ?FadeTacticalView@@3PAVFadeView@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Open2OpenPastSeparators@@YAPAVFile@@ABVAsciiString@@@Z:NEAR
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?TheBfmeObject_00C70AB0@@3VGen_00C70AB0Target@@A:BYTE
EXTERN ?TheOpen2Hub@@3PAVOpen2Hub@@A:BYTE
EXTERN ?d_0073ad70@@YAXXZ:NEAR
EXTERN ?g_Rva00F0692CTransform@@3URva007845D0Transform@@A:BYTE
EXTERN ?g_rva00785FD0Dirty@@3DA:BYTE
EXTERN ?j_0000db57@@YAXXZ:NEAR
EXTERN ?j_00012e3b@@YAXXZ:NEAR
EXTERN ?j_0002b81e@@YAXXZ:NEAR
EXTERN ?j_0002d0d8@@YAXXZ:NEAR
EXTERN ?j_00040bc4@@YAXXZ:NEAR
EXTERN ?j_00049062@@YAXXZ:NEAR
EXTERN ?rva00785FD0Flush@@YAXXZ:NEAR
EXTERN g_Va01306930:BYTE
EXTERN g_Va01306934:BYTE
EXTERN g_Va01306938:BYTE
EXTERN g_Va0130693C:BYTE
EXTERN g_Va01306940:BYTE
_TEXT SEGMENT

; retail @ 0x006F60E0 size 29
public ?d_006f60e0@@YAXXZ
?d_006f60e0@@YAXXZ PROC
    db 83h, 0F8h, 02h, 74h, 12h, 83h, 0F8h, 03h, 74h, 0Dh, 83h, 0F8h, 04h, 74h, 08h, 83h
    db 0F8h, 05h, 74h, 03h, 33h, 0C0h, 0C3h, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_006f60e0@@YAXXZ ENDP

; retail @ 0x006FCAB0 size 23
public ?d_006fcab0@@YAXXZ
?d_006fcab0@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D8h, 4Ch, 24h, 04h, 0D9h, 44h, 24h, 04h, 0D9h, 0FAh, 0D8h, 0E1h
    db 0D8h, 4Ch, 24h, 04h, 0DEh, 0C1h, 0C3h
?d_006fcab0@@YAXXZ ENDP

; retail @ 0x0071FED0 size 19
public ?d_0071fed0@@YAXXZ
?d_0071fed0@@YAXXZ PROC
    db 0FFh, 05h, 94h, 05h, 34h, 01h, 5Bh, 5Fh, 5Eh, 5Dh, 81h, 0C4h, 24h, 02h, 00h, 00h
    db 0C2h, 08h, 00h
?d_0071fed0@@YAXXZ ENDP

; retail @ 0x0073AED0 size 135
_TEXT ENDS
_TEXT$d00b3aed0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B3AED0 size 135
public ?d_0073aed0@@YAXXZ
?d_0073aed0@@YAXXZ PROC
    db 051h, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 001h, 056h, 0FFh, 090h, 0ACh, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 004h, 08Bh, 074h, 024h
    db 00Ch, 08Bh, 0CEh
    call ?j_00012e3b@@YAXXZ
    db 084h, 0C0h, 075h, 061h, 0D9h, 044h, 024h, 004h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 050h, 0A1h
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 085h, 0C0h, 08Bh, 08Eh, 0FCh, 000h, 000h, 000h, 074h, 008h, 08Bh, 050h, 00Ch, 08Bh, 042h, 024h
    db 0EBh, 002h, 033h, 0C0h, 085h, 0C9h, 074h, 00Bh, 050h
    call ?j_0002b81e@@YAXXZ
    db 083h, 0F8h, 002h, 07Fh, 028h, 08Bh, 0CEh
    call ?j_0000db57@@YAXXZ
    db 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Ah, 088h, 081h, 00Ah, 000h, 000h, 084h, 0C9h, 074h, 007h, 08Bh, 0CEh
    call ?d_0073ad70@@YAXXZ
    db 0A1h
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 0FFh, 080h, 0C0h, 000h, 000h, 000h, 05Eh, 059h, 0C3h
?d_0073aed0@@YAXXZ ENDP
_TEXT$d00b3aed0 ENDS
_TEXT SEGMENT

; retail @ 0x00750590 size 25
public ?d_00750590@@YAXXZ
?d_00750590@@YAXXZ PROC
    db 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 0Ch, 83h, 0F8h, 19h, 75h, 0Ah, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 0A2h, 10h, 02h, 00h, 00h, 0B0h, 01h, 0C3h
?d_00750590@@YAXXZ ENDP

; retail @ 0x00752E10 size 28
public ?d_00752e10@@YAXXZ
?d_00752e10@@YAXXZ PROC
    db 0A1h, 0ACh, 0D5h, 2Eh, 01h, 8Bh, 80h, 0Ch, 17h, 00h, 00h, 48h, 79h, 03h, 33h, 0C0h
    db 0C3h, 83h, 0F8h, 02h, 7Eh, 05h, 0B8h, 02h, 00h, 00h, 00h, 0C3h
?d_00752e10@@YAXXZ ENDP

; retail @ 0x007831B0 size 37
public ?d_007831b0@@YAXXZ
?d_007831b0@@YAXXZ PROC
    db 0D9h, 40h, 08h, 0D8h, 49h, 04h, 0D9h, 01h, 0D8h, 08h, 0DEh, 0C1h, 0D8h, 40h, 10h, 0D9h
    db 1Ah, 0D9h, 40h, 04h, 0D8h, 09h, 0D9h, 40h, 0Ch, 0D8h, 49h, 04h, 0DEh, 0C1h, 0D8h, 40h
    db 14h, 0D9h, 5Ah, 04h, 0C3h
?d_007831b0@@YAXXZ ENDP

; retail @ 0x00783210 size 42
public ?d_00783210@@YAXXZ
?d_00783210@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 81h, 0ECh, 00h, 01h, 00h, 00h, 8Dh, 84h, 24h, 08h, 01h, 00h
    db 00h, 50h, 51h, 8Dh, 54h, 24h, 08h, 68h, 00h, 01h, 00h, 00h, 52h, 0FFh, 15h, 60h
    db 93h, 35h, 01h, 81h, 0C4h, 10h, 01h, 00h, 00h, 0C3h
?d_00783210@@YAXXZ ENDP

; retail @ 0x00783280 size 22
public ?d_00783280@@YAXXZ
?d_00783280@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 50h, 51h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h
    db 0E8h, 12h, 0A1h, 8Bh, 0FFh, 0C3h
?d_00783280@@YAXXZ ENDP

; retail @ 0x007832B0 size 22
public ?d_007832b0@@YAXXZ
?d_007832b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 50h, 51h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h
    db 0E8h, 0DDh, 62h, 88h, 0FFh, 0C3h
?d_007832b0@@YAXXZ ENDP

; retail @ 0x007832D0 size 17
public ?d_007832d0@@YAXXZ
?d_007832d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h, 50h, 0E8h, 63h, 0ACh, 89h, 0FFh
    db 0C3h
?d_007832d0@@YAXXZ ENDP

; retail @ 0x00783310 size 56
public ?d_00783310@@YAXXZ
?d_00783310@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D8h, 1Dh, 68h, 6Ah, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh
    db 17h, 0D9h, 44h, 24h, 08h, 0D8h, 64h, 24h, 04h, 0D9h, 0E1h, 0D8h, 1Dh, 24h, 6Ch, 07h
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 07h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0C3h, 0D9h
    db 44h, 24h, 08h, 0D8h, 74h, 24h, 04h, 0C3h
?d_00783310@@YAXXZ ENDP

; retail @ 0x007833E0 size 642
public ?d_007833e0@@YAXXZ
?d_007833e0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 08h, 89h, 0Dh, 2Ch, 69h, 30h, 01h, 8Bh, 50h, 04h, 89h
    db 15h, 30h, 69h, 30h, 01h, 8Bh, 48h, 08h, 89h, 0Dh, 34h, 69h, 30h, 01h, 8Bh, 50h
    db 0Ch, 83h, 0ECh, 14h, 89h, 15h, 38h, 69h, 30h, 01h, 8Bh, 48h, 10h, 56h, 89h, 0Dh
    db 3Ch, 69h, 30h, 01h, 8Bh, 50h, 14h, 57h, 8Dh, 44h, 24h, 18h, 50h, 8Dh, 4Ch, 24h
    db 18h, 51h, 89h, 15h, 40h, 69h, 30h, 01h, 0E8h, 0D3h, 0F5h, 10h, 00h, 8Dh, 54h, 24h
    db 28h, 52h, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 4Ch, 24h, 20h, 51h, 8Dh, 54h, 24h, 20h
    db 52h, 0E8h, 0BAh, 9Dh, 17h, 00h, 8Bh, 4Ch, 24h, 2Ch, 0A1h, 9Ch, 69h, 30h, 01h, 8Bh
    db 74h, 24h, 28h, 8Bh, 54h, 24h, 30h, 8Bh, 7Ch, 24h, 24h, 83h, 0C4h, 18h, 3Bh, 0C8h
    db 75h, 1Ch, 3Bh, 15h, 0A0h, 69h, 30h, 01h, 75h, 14h, 3Bh, 3Dh, 0A4h, 69h, 30h, 01h
    db 75h, 0Ch, 3Bh, 35h, 0A8h, 69h, 30h, 01h, 0Fh, 84h, 0BAh, 00h, 00h, 00h, 85h, 0C9h
    db 74h, 10h, 0DBh, 44h, 24h, 0Ch, 0DAh, 74h, 24h, 14h, 0D9h, 1Dh, 6Ch, 0B8h, 2Bh, 01h
    db 0EBh, 0Ah, 0C7h, 05h, 6Ch, 0B8h, 2Bh, 01h, 00h, 00h, 80h, 3Fh, 85h, 0D2h, 74h, 10h
    db 0DBh, 44h, 24h, 10h, 0DAh, 74h, 24h, 18h, 0D9h, 1Dh, 70h, 0B8h, 2Bh, 01h, 0EBh, 0Ah
    db 0C7h, 05h, 70h, 0B8h, 2Bh, 01h, 00h, 00h, 80h, 3Fh, 0D9h, 05h, 50h, 53h, 07h, 01h
    db 0D9h, 05h, 6Ch, 0B8h, 2Bh, 01h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 14h, 0D9h
    db 05h, 34h, 53h, 07h, 01h, 0D8h, 35h, 6Ch, 0B8h, 2Bh, 01h, 0D9h, 1Dh, 74h, 0B8h, 2Bh
    db 01h, 0EBh, 0Ah, 0C7h, 05h, 74h, 0B8h, 2Bh, 01h, 00h, 00h, 80h, 3Fh, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 0D9h, 05h, 70h, 0B8h, 2Bh, 01h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 7Bh, 14h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 35h, 70h, 0B8h, 2Bh, 01h, 0D9h, 1Dh
    db 78h, 0B8h, 2Bh, 01h, 0EBh, 0Ah, 0C7h, 05h, 78h, 0B8h, 2Bh, 01h, 00h, 00h, 80h, 3Fh
    db 89h, 0Dh, 9Ch, 69h, 30h, 01h, 89h, 15h, 0A0h, 69h, 30h, 01h, 89h, 3Dh, 0A4h, 69h
    db 30h, 01h, 89h, 35h, 0A8h, 69h, 30h, 01h, 0D9h, 05h, 3Ch, 69h, 30h, 01h, 0A1h, 2Ch
    db 69h, 30h, 01h, 0D8h, 0Dh, 6Ch, 0B8h, 2Bh, 01h, 8Bh, 15h, 34h, 69h, 30h, 01h, 8Bh
    db 0Dh, 30h, 69h, 30h, 01h, 0A3h, 14h, 69h, 30h, 01h, 0D9h, 1Dh, 3Ch, 69h, 30h, 01h
    db 0A1h, 38h, 69h, 30h, 01h, 0D9h, 05h, 40h, 69h, 30h, 01h, 0A3h, 20h, 69h, 30h, 01h
    db 0D8h, 0Dh, 70h, 0B8h, 2Bh, 01h, 89h, 0Dh, 18h, 69h, 30h, 01h, 8Bh, 0Dh, 3Ch, 69h
    db 30h, 01h, 89h, 15h, 1Ch, 69h, 30h, 01h, 0D9h, 1Dh, 40h, 69h, 30h, 01h, 8Bh, 15h
    db 40h, 69h, 30h, 01h, 0D9h, 05h, 2Ch, 69h, 30h, 01h, 5Fh, 0D8h, 0Dh, 6Ch, 0B8h, 2Bh
    db 01h, 89h, 0Dh, 24h, 69h, 30h, 01h, 89h, 15h, 28h, 69h, 30h, 01h, 5Eh, 0D9h, 1Dh
    db 2Ch, 69h, 30h, 01h, 0D9h, 05h, 34h, 69h, 30h, 01h, 0D8h, 0Dh, 6Ch, 0B8h, 2Bh, 01h
    db 0D9h, 1Dh, 34h, 69h, 30h, 01h, 0D9h, 05h, 30h, 69h, 30h, 01h, 0D8h, 0Dh, 70h, 0B8h
    db 2Bh, 01h, 0D9h, 1Dh, 30h, 69h, 30h, 01h, 0D9h, 05h, 38h, 69h, 30h, 01h, 0D8h, 0Dh
    db 70h, 0B8h, 2Bh, 01h, 0D9h, 1Dh, 38h, 69h, 30h, 01h, 0D9h, 05h, 2Ch, 69h, 30h, 01h
    db 0D8h, 25h, 34h, 53h, 07h, 01h, 0D9h, 0E1h, 0D8h, 1Dh, 68h, 6Ah, 12h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 74h, 4Fh, 0D9h, 05h, 30h, 69h, 30h, 01h, 0D9h, 0E1h, 0D8h, 1Dh, 68h
    db 6Ah, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 3Ah, 0D9h, 05h, 34h, 69h, 30h, 01h
    db 0D9h, 0E1h, 0D8h, 1Dh, 68h, 6Ah, 12h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 25h, 0D9h
    db 05h, 38h, 69h, 30h, 01h, 0C7h, 05h, 60h, 0B8h, 2Bh, 01h, 03h, 00h, 00h, 00h, 0D8h
    db 25h, 34h, 53h, 07h, 01h, 0D9h, 0E1h, 0D8h, 1Dh, 68h, 6Ah, 12h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 75h, 0Ah, 0C7h, 05h, 60h, 0B8h, 2Bh, 01h, 01h, 00h, 00h, 00h, 83h, 0C4h
    db 14h, 0C3h
?d_007833e0@@YAXXZ ENDP

; retail @ 0x00783720 size 72
public ?d_00783720@@YAXXZ
?d_00783720@@YAXXZ PROC
    db 0D9h, 02h, 0D8h, 19h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 8Bh, 01h, 89h, 02h, 0EBh
    db 0Fh, 0D9h, 06h, 0D8h, 19h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 04h, 8Bh, 01h, 89h, 06h
    db 0D9h, 42h, 04h, 0D8h, 59h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 49h, 04h
    db 89h, 4Ah, 04h, 0C3h, 0D9h, 46h, 04h, 0D8h, 59h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 06h, 8Bh, 51h, 04h, 89h, 56h, 04h, 0C3h
?d_00783720@@YAXXZ ENDP

; retail @ 0x00783F90 size 122
public ?d_00783f90@@YAXXZ
?d_00783f90@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 0C8h, 0C1h, 0E9h, 10h, 81h, 0E1h, 0FFh, 00h, 00h, 00h, 85h
    db 0C9h, 89h, 4Ch, 24h, 04h, 0DBh, 44h, 24h, 04h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h
    db 01h, 0D8h, 0Dh, 4Ch, 0C6h, 07h, 01h, 8Bh, 0D0h, 0C1h, 0EAh, 08h, 81h, 0E2h, 0FFh, 00h
    db 00h, 00h, 85h, 0D2h, 0D9h, 1Dh, 6Ch, 69h, 30h, 01h, 89h, 54h, 24h, 04h, 0DBh, 44h
    db 24h, 04h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0D8h, 0Dh, 4Ch, 0C6h, 07h, 01h
    db 25h, 0FFh, 00h, 00h, 00h, 85h, 0C0h, 89h, 44h, 24h, 04h, 0D9h, 1Dh, 70h, 69h, 30h
    db 01h, 0DBh, 44h, 24h, 04h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0D8h, 0Dh, 4Ch
    db 0C6h, 07h, 01h, 0D9h, 1Dh, 74h, 69h, 30h, 01h, 0C3h
?d_00783f90@@YAXXZ ENDP

; retail @ 0x00784030 size 76
public ?d_00784030@@YAXXZ
?d_00784030@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 0D9h, 40h, 0Ch, 8Bh, 08h, 0D9h, 40h, 08h, 0D9h, 40h, 04h, 89h
    db 0Dh, 7Ch, 69h, 30h, 01h, 0D9h, 1Dh, 80h, 69h, 30h, 01h, 0D9h, 1Dh, 84h, 69h, 30h
    db 01h, 0D9h, 1Dh, 88h, 69h, 30h, 01h, 8Bh, 50h, 10h, 0D9h, 40h, 1Ch, 0D9h, 40h, 18h
    db 0D9h, 40h, 14h, 89h, 15h, 8Ch, 69h, 30h, 01h, 0D9h, 1Dh, 90h, 69h, 30h, 01h, 0D9h
    db 1Dh, 94h, 69h, 30h, 01h, 0D9h, 1Dh, 98h, 69h, 30h, 01h, 0C3h
?d_00784030@@YAXXZ ENDP

; retail @ 0x007852E0 size 19
_TEXT ENDS
_TEXT$d00b852e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B852E0 size 19
public ?d_007852e0@@YAXXZ
?d_007852e0@@YAXXZ PROC
    call ?Open2OpenPastSeparators@@YAPAVFile@@ABVAsciiString@@@Z
    db 085h, 0C0h, 074h, 007h, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 062h, 034h, 033h, 0C0h, 0C3h
?d_007852e0@@YAXXZ ENDP
_TEXT$d00b852e0 ENDS
_TEXT SEGMENT

; retail @ 0x00786060 size 301
public ?d_00786060@@YAXXZ
?d_00786060@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 0Ch, 83h, 0ECh, 10h, 85h, 0C9h, 0Fh, 84h, 1Ah, 01h, 00h, 00h, 8Bh
    db 01h, 56h, 0FFh, 50h, 08h, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 09h, 01h, 00h, 00h, 57h
    db 0E8h, 4Bh, 0FFh, 0FFh, 0FFh, 8Bh, 3Dh, 98h, 71h, 2Dh, 01h, 8Bh, 0Dh, 54h, 69h, 30h
    db 01h, 0C7h, 05h, 98h, 71h, 2Dh, 01h, 0BDh, 0B2h, 44h, 00h, 0E8h, 4Fh, 0B9h, 89h, 0FFh
    db 8Bh, 15h, 2Ch, 69h, 30h, 01h, 8Dh, 4Eh, 10h, 89h, 11h, 0A1h, 30h, 69h, 30h, 01h
    db 89h, 41h, 04h, 8Bh, 15h, 34h, 69h, 30h, 01h, 89h, 51h, 08h, 0A1h, 38h, 69h, 30h
    db 01h, 89h, 41h, 0Ch, 8Bh, 15h, 3Ch, 69h, 30h, 01h, 89h, 51h, 10h, 0A1h, 40h, 69h
    db 30h, 01h, 89h, 41h, 14h, 8Dh, 4Ch, 24h, 08h, 51h, 8Dh, 54h, 24h, 14h, 52h, 8Bh
    db 0CEh, 0E8h, 0B8h, 55h, 89h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h, 05h, 3Ch, 53h, 07h, 01h
    db 0E8h, 43h, 0Dh, 27h, 00h, 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 0D9h, 5Ch, 24h
    db 10h, 0D9h, 44h, 24h, 14h, 0D8h, 05h, 3Ch, 53h, 07h, 01h, 0E8h, 28h, 0Dh, 27h, 00h
    db 89h, 44h, 24h, 24h, 0DBh, 44h, 24h, 24h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 08h
    db 0D8h, 05h, 3Ch, 53h, 07h, 01h, 0E8h, 0Dh, 0Dh, 27h, 00h, 89h, 44h, 24h, 24h, 0DBh
    db 44h, 24h, 24h, 0D9h, 5Ch, 24h, 08h, 0D9h, 44h, 24h, 0Ch, 0D8h, 05h, 3Ch, 53h, 07h
    db 01h, 0E8h, 0F2h, 0Ch, 27h, 00h, 8Bh, 4Ch, 24h, 20h, 89h, 44h, 24h, 24h, 8Bh, 44h
    db 24h, 28h, 0DBh, 44h, 24h, 24h, 50h, 51h, 8Bh, 4Ch, 24h, 24h, 0D9h, 5Ch, 24h, 14h
    db 8Dh, 54h, 24h, 10h, 52h, 8Dh, 44h, 24h, 1Ch, 50h, 51h, 8Bh, 0Dh, 0E8h, 19h, 2Fh
    db 01h, 0E8h, 6Dh, 0D3h, 89h, 0FFh, 8Bh, 0Dh, 54h, 69h, 30h, 01h, 89h, 3Dh, 98h, 71h
    db 2Dh, 01h, 0E8h, 0C4h, 2Bh, 88h, 0FFh, 5Fh, 5Eh, 83h, 0C4h, 10h, 0C3h
?d_00786060@@YAXXZ ENDP

; retail @ 0x00786C70 size 22
public ?d_00786c70@@YAXXZ
?d_00786c70@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 75h, 03h, 33h, 0C0h, 0C3h, 8Bh, 44h, 24h, 08h, 50h
    db 0E8h, 96h, 0BCh, 8Ah, 0FFh, 0C3h
?d_00786c70@@YAXXZ ENDP

; retail @ 0x007874F0 size 191
_TEXT ENDS
_TEXT$d00b874f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00B874F0 size 191
public ?d_007874f0@@YAXXZ
?d_007874f0@@YAXXZ PROC
    db 051h, 0A1h
    dd ?TheOpen2Hub@@3PAVOpen2Hub@@A
    db 085h, 0C0h, 00Fh, 084h, 0AFh, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 008h, 085h, 0C9h, 00Fh, 084h
    db 0A3h, 000h, 000h, 000h, 08Bh, 001h, 056h, 0FFh, 050h, 008h, 08Bh, 0F0h, 085h, 0F6h, 089h, 074h
    db 024h, 004h, 00Fh, 084h, 08Eh, 000h, 000h, 000h, 08Bh, 015h
    dd ?g_Rva00F0692CTransform@@3URva007845D0Transform@@A
    db 08Dh, 04Eh, 010h, 089h, 011h, 0A1h
    dd g_Va01306930
    db 089h, 041h, 004h, 08Bh, 015h
    dd g_Va01306934
    db 089h, 051h, 008h, 0A1h
    dd g_Va01306938
    db 089h, 041h, 00Ch, 08Bh, 015h
    dd g_Va0130693C
    db 089h, 051h, 010h, 0A1h
    dd g_Va01306940
    db 089h, 041h, 014h, 08Bh, 044h, 024h, 010h, 083h, 0F8h, 0FFh, 074h, 022h, 085h, 0C0h, 074h, 040h
    db 083h, 0F8h, 001h, 075h, 047h, 08Dh, 04Ch, 024h, 004h, 051h, 0B9h
    dd ?TheBfmeObject_00C70AB0@@3VGen_00C70AB0Target@@A
    call ?j_0002d0d8@@YAXXZ
    db 0C6h, 005h
    dd ?g_rva00785FD0Dirty@@3DA
    db 001h, 05Eh, 059h, 0C3h, 0A1h
    dd ?TheBfmeObject_00C70AB0@@3VGen_00C70AB0Target@@A
    db 039h, 000h, 074h, 019h, 08Dh, 054h, 024h, 004h, 052h, 0B9h
    dd ?TheBfmeObject_00C70AB0@@3VGen_00C70AB0Target@@A
    call ?j_00040bc4@@YAXXZ
    db 0C6h, 005h
    dd ?g_rva00785FD0Dirty@@3DA
    db 001h, 05Eh, 059h, 0C3h
    call ?rva00785FD0Flush@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00049062@@YAXXZ
    db 05Eh, 059h, 0C3h
?d_007874f0@@YAXXZ ENDP
_TEXT$d00b874f0 ENDS
_TEXT SEGMENT

; retail @ 0x00788A00 size 29
public ?d_00788a00@@YAXXZ
?d_00788a00@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 14h, 8Bh, 44h, 24h, 08h, 50h, 0E8h, 6Bh, 76h
    db 88h, 0FFh, 85h, 0C0h, 74h, 06h, 8Bh, 4Ch, 24h, 0Ch, 89h, 08h, 0C3h
?d_00788a00@@YAXXZ ENDP
_TEXT ENDS
END
