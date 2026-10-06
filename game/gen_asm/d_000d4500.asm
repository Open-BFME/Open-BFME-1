.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?TheBfmeGenAE@@3PAVBfmeGenAE@@A:BYTE
EXTERN ?bfmeFindModule@@YAPAVBfmeDestroyable@@XZ:NEAR
EXTERN ?g_Va012ED72C@@3IA:BYTE
EXTERN ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z:NEAR
EXTERN ?j_00001fd7@@YAXXZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000e570@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_0002ae23@@YAXXZ:NEAR
EXTERN ?j_00031a7f@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00034c93@@YAXXZ:NEAR
EXTERN ?j_0003add7@@YAXXZ:NEAR
EXTERN ?j_00043888@@YAXXZ:NEAR
EXTERN g_Va00FF9AAE:NEAR
EXTERN g_Va01083C50:BYTE
EXTERN g_Va012ED728:BYTE
_TEXT SEGMENT

; retail @ 0x000D4500 size 273
_TEXT ENDS
_TEXT$d004d4500 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x004D4500 size 273
public ?d_000d4500@@YAXXZ
?d_000d4500@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va00FF9AAE
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 053h, 08Bh, 05Ch, 024h, 014h, 085h, 0DBh, 056h
    db 057h, 00Fh, 084h, 0D6h, 000h, 000h, 000h, 08Bh, 043h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h
    db 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 080h, 0C8h, 000h, 000h, 000h, 084h, 0C0h, 078h, 011h, 06Ah, 067h, 08Bh, 0CBh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 0A8h, 000h, 000h, 000h, 0F6h, 005h
    dd ?g_Va012ED72C@@3IA
    db 001h, 075h, 02Ch, 083h, 00Dh
    dd ?g_Va012ED72C@@3IA
    db 001h, 08Bh, 00Dh
    dd ?TheBfmeGenAE@@3PAVBfmeGenAE@@A
    db 068h
    dd g_Va01083C50
    db 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h
    call ?j_0003add7@@YAXXZ
    db 0A3h
    dd g_Va012ED728
    db 0C7h, 044h, 024h, 014h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h
    dd g_Va012ED728
    db 050h, 08Bh, 0CBh
    call ?j_0002ae23@@YAXXZ
    db 08Bh, 07Ch, 024h, 020h, 08Bh, 0F0h, 08Bh, 047h, 008h, 085h, 0C0h, 074h, 013h, 08Bh, 04Fh, 00Ch
    db 056h, 053h, 051h, 050h
    call ?j_00043888@@YAXXZ
    db 083h, 0C4h, 010h, 085h, 0C0h, 07Dh, 046h, 08Ah, 047h, 004h, 084h, 0C0h, 074h, 039h, 085h, 0F6h
    db 074h, 02Ch, 08Bh, 096h, 0A0h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 074h, 00Bh, 0F6h, 080h, 044h, 003h, 000h, 000h, 008h, 074h, 016h, 0EBh, 01Ah, 0F6h
    db 083h, 044h, 003h, 000h, 000h, 008h, 074h, 00Bh, 0EBh, 00Fh, 0F6h, 083h, 044h, 003h, 000h, 000h
    db 008h, 075h, 006h, 089h, 05Fh, 008h, 089h, 077h, 00Ch, 08Bh, 04Ch, 024h, 00Ch, 05Fh, 05Eh, 0B8h
    db 001h, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 00Ch, 0C3h
?d_000d4500@@YAXXZ ENDP
_TEXT$d004d4500 ENDS
_TEXT SEGMENT

; retail @ 0x000D5980 size 78
public ?d_000d5980@@YAXXZ
?d_000d5980@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 53h, 8Ah, 18h, 56h, 8Bh, 74h, 24h, 0Ch, 85h, 0F6h, 74h, 36h
    db 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 18h
    db 0C9h, 0F2h, 0FFh, 0F6h, 80h, 0D0h, 00h, 00h, 00h, 40h, 74h, 1Ah, 84h, 0DBh, 8Bh, 0CEh
    db 6Ah, 06h, 74h, 0Dh, 0E8h, 49h, 8Ah, 0F4h, 0FFh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh
    db 0C3h, 0E8h, 0A4h, 66h, 0F6h, 0FFh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 0C3h
?d_000d5980@@YAXXZ ENDP

; retail @ 0x000FBE90 size 210
public ?d_000fbe90@@YAXXZ
?d_000fbe90@@YAXXZ PROC
    db 8Bh, 0Dh, 14h, 70h, 2Fh, 01h, 8Bh, 01h, 56h, 8Bh, 74h, 24h, 08h, 8Bh, 56h, 04h
    db 57h, 52h, 8Bh, 16h, 52h, 0FFh, 50h, 20h, 85h, 0C0h, 8Bh, 7Ch, 24h, 10h, 74h, 0Bh
    db 8Ah, 48h, 1Ch, 84h, 0C9h, 74h, 04h, 0C6h, 47h, 18h, 01h, 0A1h, 14h, 0F2h, 2Eh, 01h
    db 8Bh, 48h, 0Ch, 6Ah, 01h, 56h, 0E8h, 0FDh, 0Eh, 0F2h, 0FFh, 84h, 0C0h, 74h, 04h, 0C6h
    db 47h, 18h, 01h, 0D9h, 46h, 08h, 0D8h, 5Fh, 20h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 06h
    db 8Bh, 4Eh, 08h, 89h, 4Fh, 20h, 0D9h, 46h, 08h, 0D8h, 5Fh, 1Ch, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 06h, 8Bh, 56h, 08h, 89h, 57h, 1Ch, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0D9h
    db 81h, 30h, 0Bh, 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 75h, 4Dh, 0D9h, 07h, 0D8h, 81h, 30h, 0Bh, 00h, 00h, 0D8h, 1Eh, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 74h, 38h, 0D9h, 47h, 0Ch, 0D8h, 0A1h, 30h, 0Bh, 00h, 00h, 0D8h, 1Eh, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Bh, 26h, 0D9h, 47h, 04h, 0D8h, 81h, 30h, 0Bh, 00h, 00h, 0D8h, 5Eh
    db 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 13h, 0D9h, 47h, 10h, 0D8h, 0A1h, 30h, 0Bh, 00h
    db 00h, 0D8h, 5Eh, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 04h, 0C6h, 47h, 18h, 01h, 5Fh
    db 5Eh, 0C3h
?d_000fbe90@@YAXXZ ENDP

; retail @ 0x000FC2A0 size 42
public ?d_000fc2a0@@YAXXZ
?d_000fc2a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 0E8h, 13h, 0F4h, 0F0h, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 74h
    db 13h, 8Bh, 10h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 4Eh, 04h, 51h, 8Bh, 0C8h, 0FFh, 52h
    db 18h, 01h, 06h, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_000fc2a0@@YAXXZ ENDP

; retail @ 0x0010F100 size 20
public ?d_0010f100@@YAXXZ
?d_0010f100@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 04h, 50h, 51h, 8Bh, 4Ch, 24h, 10h, 0E8h, 04h
    db 78h, 0F2h, 0FFh, 0C3h
?d_0010f100@@YAXXZ ENDP

; retail @ 0x00110790 size 20
public ?d_00110790@@YAXXZ
?d_00110790@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 04h, 50h, 51h, 8Bh, 4Ch, 24h, 10h, 0E8h, 0A3h
    db 0EDh, 0F0h, 0FFh, 0C3h
?d_00110790@@YAXXZ ENDP

; retail @ 0x0014B880 size 45
public ?d_0014b880@@YAXXZ
?d_0014b880@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 24h, 6Ah, 0EBh, 0FFh, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 4Eh, 04h, 50h
    db 0E8h, 79h, 0ABh, 0ECh, 0FFh, 3Bh, 06h, 7Eh, 02h, 89h, 06h, 5Eh, 0C3h
?d_0014b880@@YAXXZ ENDP

; retail @ 0x0015C280 size 129
public ?d_0015c280@@YAXXZ
?d_0015c280@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 1Ch, 57h, 8Bh, 79h, 10h, 85h, 0FFh, 74h, 08h, 8Bh
    db 8Fh, 00h, 02h, 00h, 00h, 0EBh, 02h, 33h, 0C9h, 85h, 0FFh, 74h, 60h, 85h, 0C9h, 74h
    db 5Ch, 8Bh, 11h, 0FFh, 52h, 48h, 85h, 0C0h, 74h, 53h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 56h, 50h, 0E8h, 9Ch, 2Fh, 0ECh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 75h, 05h, 5Eh, 32h, 0C0h
    db 5Fh, 0C3h, 56h, 8Bh, 0CFh, 0E8h, 4Fh, 0E4h, 0EEh, 0FFh, 85h, 0C0h, 75h, 0EFh, 0F6h, 86h
    db 44h, 03h, 00h, 00h, 01h, 75h, 0E6h, 8Bh, 0CFh, 0E8h, 0F9h, 5Ch, 0EAh, 0FFh, 84h, 0C0h
    db 74h, 0DBh, 6Ah, 02h, 56h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0A5h, 89h, 0EDh, 0FFh, 83h, 0F8h
    db 03h, 74h, 05h, 83h, 0F8h, 02h, 75h, 0C5h, 5Eh, 0B0h, 01h, 5Fh, 0C3h, 32h, 0C0h, 5Fh
    db 0C3h
?d_0015c280@@YAXXZ ENDP

; retail @ 0x0016AF70 size 125
_TEXT ENDS
_TEXT$d0056af70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0056AF70 size 125
public ?d_0016af70@@YAXXZ
?d_0016af70@@YAXXZ PROC
    db 08Bh, 044h, 024h, 004h, 08Bh, 048h, 01Ch, 056h, 08Bh, 071h, 010h, 057h
    call ?j_0000e570@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 009h, 0F6h, 087h, 044h, 003h, 000h, 000h, 001h, 074h, 01Ah, 06Ah
    db 000h, 08Bh, 0CEh
    call ?j_00031a7f@@YAXXZ
    db 085h, 0C0h, 074h, 00Dh, 08Bh, 048h, 004h, 08Ah, 081h, 033h, 005h, 000h, 000h, 084h, 0C0h, 075h
    db 03Eh, 085h, 0F6h, 074h, 03Ah, 085h, 0FFh, 074h, 036h, 08Bh, 0CEh
    call ?j_00001fd7@@YAXXZ
    db 084h, 0C0h, 074h, 026h, 08Bh, 08Eh, 004h, 002h, 000h, 000h, 08Bh, 011h, 0FFh, 092h, 000h, 002h
    db 000h, 000h, 050h, 08Bh, 044h, 024h, 014h, 057h, 050h, 08Bh, 0CEh
    call ?j_00034c93@@YAXXZ
    db 083h, 0F8h, 003h, 074h, 00Ah, 083h, 0F8h, 002h, 074h, 005h, 05Fh, 0B0h, 001h, 05Eh, 0C3h, 05Fh
    db 032h, 0C0h, 05Eh, 0C3h
?d_0016af70@@YAXXZ ENDP
_TEXT$d0056af70 ENDS
_TEXT SEGMENT

; retail @ 0x00171B20 size 25
public ?d_00171b20@@YAXXZ
?d_00171b20@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 1Ch, 8Bh, 51h, 10h, 8Bh, 82h, 94h, 00h, 00h, 00h
    db 0C1h, 0E8h, 04h, 0F7h, 0D0h, 83h, 0E0h, 01h, 0C3h
?d_00171b20@@YAXXZ ENDP

; retail @ 0x0018A0F0 size 118
_TEXT ENDS
_TEXT$d0058a0f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0058A0F0 size 118
public ?d_0018a0f0@@YAXXZ
?d_0018a0f0@@YAXXZ PROC
    db 08Bh, 044h, 024h, 004h, 08Bh, 048h, 01Ch, 057h, 08Bh, 079h, 010h, 085h, 0FFh, 074h, 008h, 08Bh
    db 08Fh, 000h, 002h, 000h, 000h, 0EBh, 002h, 033h, 0C9h, 085h, 0FFh, 074h, 055h, 085h, 0C9h, 074h
    db 051h, 08Bh, 011h, 0FFh, 052h, 048h, 085h, 0C0h, 074h, 048h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 056h, 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 075h, 005h, 05Eh, 032h, 0C0h, 05Fh, 0C3h, 056h, 08Bh, 0CFh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 085h, 0C0h, 075h, 0EFh, 0F6h, 086h, 044h, 003h, 000h, 000h, 001h, 075h, 0E6h, 06Ah, 002h, 056h
    db 06Ah, 000h, 08Bh, 0CFh
    call ?j_00034c93@@YAXXZ
    db 083h, 0F8h, 003h, 074h, 005h, 083h, 0F8h, 002h, 075h, 0D0h, 05Eh, 0B0h, 001h, 05Fh, 0C3h, 032h
    db 0C0h, 05Fh, 0C3h
?d_0018a0f0@@YAXXZ ENDP
_TEXT$d0058a0f0 ENDS
_TEXT SEGMENT

; retail @ 0x001B40F0 size 63
public ?d_001b40f0@@YAXXZ
?d_001b40f0@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D8h, 64h, 24h, 08h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 7Ah, 09h, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0C3h, 0D9h, 44h
    db 24h, 0Ch, 0D8h, 0F9h, 0D8h, 05h, 34h, 53h, 07h, 01h, 0D9h, 0C9h, 0D8h, 0Dh, 3Ch, 53h
    db 07h, 01h, 0D8h, 44h, 24h, 08h, 0DEh, 0C9h, 0D8h, 0Dh, 1Ch, 0D1h, 09h, 01h, 0C3h
?d_001b40f0@@YAXXZ ENDP

; retail @ 0x001DCF20 size 27
public ?d_001dcf20@@YAXXZ
?d_001dcf20@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 0Eh, 50h, 0E8h, 0E8h, 0D7h, 0E6h
    db 0FFh, 85h, 0C0h, 75h, 04h, 0C6h, 46h, 04h, 01h, 5Eh, 0C3h
?d_001dcf20@@YAXXZ ENDP

; retail @ 0x001E4AA0 size 267
public ?d_001e4aa0@@YAXXZ
?d_001e4aa0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 6Eh, 0A1h, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h, 18h, 8Bh, 03h, 56h, 57h, 8Bh, 7Ch
    db 24h, 1Ch, 3Bh, 0F8h, 0Fh, 84h, 0CAh, 00h, 00h, 00h, 8Bh, 40h, 04h, 85h, 0C0h, 75h
    db 04h, 33h, 0F6h, 0EBh, 0Eh, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0DAh, 0D7h, 0E1h
    db 0FFh, 8Bh, 0F0h, 8Bh, 47h, 04h, 85h, 0C0h, 75h, 04h, 33h, 0C9h, 0EBh, 0Eh, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0C1h, 0D7h, 0E1h, 0FFh, 8Bh, 0C8h, 56h, 0E8h, 09h, 9Dh
    db 0E5h, 0FFh, 84h, 0C0h, 0Fh, 84h, 8Ah, 00h, 00h, 00h, 8Bh, 03h, 0D9h, 47h, 38h, 0D8h
    db 60h, 38h, 83h, 0C0h, 38h, 0D9h, 47h, 3Ch, 0D8h, 60h, 04h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h
    db 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 5Bh, 08h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 74h, 61h, 0F6h, 05h, 40h, 0F7h, 2Eh, 01h, 01h, 75h, 2Ch, 83h, 0Dh, 40h, 0F7h
    db 2Eh, 01h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 0Ch, 08h, 09h, 01h, 0C7h, 44h
    db 24h, 18h, 00h, 00h, 00h, 00h, 0E8h, 7Ch, 62h, 0E5h, 0FFh, 0A3h, 3Ch, 0F7h, 2Eh, 01h
    db 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h, 3Ch, 0F7h, 2Eh, 01h, 50h, 8Bh, 0CFh
    db 0E8h, 0AEh, 62h, 0E4h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 74h, 19h, 8Bh, 0CEh, 0E8h, 0CFh, 59h
    db 0E2h, 0FFh, 84h, 0C0h, 74h, 0Eh, 8Bh, 4Bh, 04h, 8Bh, 13h, 51h, 52h, 8Bh, 0CEh, 0E8h
    db 72h, 7Bh, 0E3h, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_001e4aa0@@YAXXZ ENDP

; retail @ 0x00220820 size 18
public ?d_00220820@@YAXXZ
?d_00220820@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 04h, 51h, 8Bh, 4Ch, 24h, 08h, 0E8h, 0E2h, 6Ch, 0DEh
    db 0FFh, 0C3h
?d_00220820@@YAXXZ ENDP

; retail @ 0x0022FC80 size 33
public ?d_0022fc80@@YAXXZ
?d_0022fc80@@YAXXZ PROC
    db 0D9h, 44h, 24h, 04h, 0D9h, 0FAh, 0D8h, 4Ch, 24h, 04h, 0D9h, 44h, 24h, 04h, 0D8h, 4Ch
    db 24h, 04h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 64h, 24h, 04h, 0DEh, 0C9h, 0DEh, 0C1h
    db 0C3h
?d_0022fc80@@YAXXZ ENDP

; retail @ 0x0024F280 size 64
public ?d_0024f280@@YAXXZ
?d_0024f280@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 37h, 8Bh, 88h, 04h, 02h, 00h, 00h, 85h, 0C9h
    db 74h, 2Dh, 8Bh, 41h, 30h, 8Bh, 40h, 1Ch, 85h, 0C0h, 74h, 05h, 8Bh, 40h, 04h, 0EBh
    db 05h, 0B8h, 3Fh, 42h, 0Fh, 00h, 83h, 0F8h, 38h, 74h, 14h, 83h, 0F8h, 0Fh, 74h, 0Fh
    db 8Bh, 44h, 24h, 08h, 6Ah, 02h, 50h, 83h, 0C1h, 20h, 0E8h, 0ABh, 0CFh, 0DCh, 0FFh, 0C3h
?d_0024f280@@YAXXZ ENDP

; retail @ 0x002555A0 size 49
public ?d_002555a0@@YAXXZ
?d_002555a0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 23h, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 74h, 1Bh
    db 50h, 0E8h, 09h, 0ACh, 0DEh, 0FFh, 85h, 0C0h, 74h, 11h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 8Bh, 49h, 3Ch, 8Bh, 10h, 51h, 8Bh, 0C8h, 0FFh, 52h, 24h, 0B8h, 01h, 00h, 00h, 00h
    db 0C3h
?d_002555a0@@YAXXZ ENDP

; retail @ 0x0028CF30 size 24
_TEXT ENDS
_TEXT$d0068cf30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0068CF30 size 24
public ?d_0028cf30@@YAXXZ
?d_0028cf30@@YAXXZ PROC
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 074h, 005h
    jmp ?bfmeFindModule@@YAPAVBfmeDestroyable@@XZ
    db 033h, 0C0h, 0C3h
?d_0028cf30@@YAXXZ ENDP
_TEXT$d0068cf30 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
