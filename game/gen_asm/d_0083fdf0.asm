.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??_7AptValue@@6B@:BYTE
EXTERN ??_7Rva008995E0Value@@6B@:BYTE
EXTERN ?AptGetSwfVersion@@YAIXZ:NEAR
EXTERN ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA:BYTE
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva008D2A30Head@@3PAURva008D2A30Node@@A:BYTE
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?bfmeTheCBC@@3HA:BYTE
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z:NEAR
EXTERN g_Va01059DD0:NEAR
_TEXT SEGMENT

; retail @ 0x0083FDF0 size 32
public ?d_0083fdf0@@YAXXZ
?d_0083fdf0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 10h, 8Bh, 01h, 56h, 8Bh, 74h, 24h, 08h, 52h, 8Bh, 54h, 24h, 14h
    db 52h, 8Bh, 54h, 24h, 14h, 52h, 56h, 0FFh, 50h, 08h, 8Bh, 0C6h, 5Eh, 0C2h, 10h, 00h
?d_0083fdf0@@YAXXZ ENDP

; retail @ 0x0083FE10 size 32
public ?d_0083fe10@@YAXXZ
?d_0083fe10@@YAXXZ PROC
    db 8Bh, 54h, 24h, 10h, 8Bh, 01h, 56h, 8Bh, 74h, 24h, 08h, 52h, 8Bh, 54h, 24h, 14h
    db 52h, 8Bh, 54h, 24h, 14h, 52h, 56h, 0FFh, 50h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 10h, 00h
?d_0083fe10@@YAXXZ ENDP

; retail @ 0x0083FE30 size 5
public ?d_0083fe30@@YAXXZ
?d_0083fe30@@YAXXZ PROC
    db 8Bh, 01h, 0FFh, 60h, 10h
?d_0083fe30@@YAXXZ ENDP

; retail @ 0x0083FE90 size 32
public ?d_0083fe90@@YAXXZ
?d_0083fe90@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 1Ch, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 0A7h, 22h, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_0083fe90@@YAXXZ ENDP

; retail @ 0x0083FEB0 size 8
public ?d_0083feb0@@YAXXZ
?d_0083feb0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 66h, 8Bh, 00h, 0C3h
?d_0083feb0@@YAXXZ ENDP

; retail @ 0x00845150 size 32
public ?d_00845150@@YAXXZ
?d_00845150@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 04h, 8Bh, 11h, 8Bh, 52h, 04h, 8Bh, 4Ch, 0Ah, 58h, 85h
    db 0C9h, 89h, 08h, 0Fh, 94h, 0C1h, 88h, 48h, 05h, 0C6h, 40h, 06h, 00h, 0C2h, 04h, 00h
?d_00845150@@YAXXZ ENDP

; retail @ 0x00845170 size 48
public ?d_00845170@@YAXXZ
?d_00845170@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 83h, 3Fh, 00h, 74h, 07h, 8Bh, 0CFh, 0E8h, 0BEh, 0D7h
    db 0FEh, 0FFh, 8Bh, 74h, 24h, 10h, 83h, 3Eh, 00h, 74h, 07h, 8Bh, 0CEh, 0E8h, 0AEh, 0D7h
    db 0FEh, 0FFh, 8Ah, 47h, 05h, 2Ah, 46h, 05h, 0F6h, 0D8h, 5Fh, 5Eh, 1Bh, 0C0h, 40h, 0C3h
?d_00845170@@YAXXZ ENDP

; retail @ 0x008451A0 size 52
public ?d_008451a0@@YAXXZ
?d_008451a0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 83h, 3Fh, 00h, 74h, 07h, 8Bh, 0CFh, 0E8h, 8Eh, 0D7h
    db 0FEh, 0FFh, 8Bh, 74h, 24h, 10h, 83h, 3Eh, 00h, 74h, 07h, 8Bh, 0CEh, 0E8h, 7Eh, 0D7h
    db 0FEh, 0FFh, 8Ah, 47h, 05h, 8Ah, 56h, 05h, 33h, 0C9h, 3Ah, 0C2h, 0Fh, 95h, 0C1h, 5Fh
    db 8Ah, 0C1h, 5Eh, 0C3h
?d_008451a0@@YAXXZ ENDP

; retail @ 0x0085BBC0 size 16
public ?d_0085bbc0@@YAXXZ
?d_0085bbc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0C0h, 48h, 89h, 44h, 24h, 04h, 0E9h, 50h, 0B9h, 00h, 00h
?d_0085bbc0@@YAXXZ ENDP

; retail @ 0x0085BBD0 size 16
public ?d_0085bbd0@@YAXXZ
?d_0085bbd0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0C0h, 48h, 89h, 44h, 24h, 04h, 0E9h, 40h, 0B7h, 00h, 00h
?d_0085bbd0@@YAXXZ ENDP

; retail @ 0x00891AA0 size 16
public ?d_00891aa0@@YAXXZ
?d_00891aa0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 59h, 0C3h
?d_00891aa0@@YAXXZ ENDP

; retail @ 0x00891AB0 size 7
public ?d_00891ab0@@YAXXZ
?d_00891ab0@@YAXXZ PROC
    db 8Bh, 01h, 0Fh, 0B7h, 40h, 02h, 0C3h
?d_00891ab0@@YAXXZ ENDP

; retail @ 0x008AB7E0 size 32
public ?d_008ab7e0@@YAXXZ
?d_008ab7e0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 33h, 0C0h, 85h, 0D2h, 8Bh, 51h, 60h, 0Fh, 95h, 0C0h, 0C1h, 0E0h
    db 10h, 33h, 0C2h, 25h, 00h, 00h, 01h, 00h, 33h, 0D0h, 89h, 51h, 60h, 0C2h, 04h, 00h
?d_008ab7e0@@YAXXZ ENDP

; retail @ 0x008AB800 size 4
public ?d_008ab800@@YAXXZ
?d_008ab800@@YAXXZ PROC
    db 8Bh, 41h, 50h, 0C3h
?d_008ab800@@YAXXZ ENDP

; retail @ 0x008B84A0 size 16
public ?d_008b84a0@@YAXXZ
?d_008b84a0@@YAXXZ PROC
    db 8Bh, 41h, 20h, 8Bh, 4Ch, 24h, 04h, 8Bh, 04h, 88h, 83h, 0E0h, 01h, 0C2h, 04h, 00h
?d_008b84a0@@YAXXZ ENDP

; retail @ 0x008B84B0 size 16
public ?d_008b84b0@@YAXXZ
?d_008b84b0@@YAXXZ PROC
    db 8Bh, 41h, 20h, 8Bh, 4Ch, 24h, 04h, 8Bh, 04h, 88h, 83h, 0E0h, 0FEh, 0C2h, 04h, 00h
?d_008b84b0@@YAXXZ ENDP

; retail @ 0x008BD000 size 16
public ?d_008bd000@@YAXXZ
?d_008bd000@@YAXXZ PROC
    db 8Bh, 01h, 0C7h, 40h, 50h, 00h, 00h, 00h, 00h, 8Bh, 09h, 8Bh, 11h, 0FFh, 62h, 08h
?d_008bd000@@YAXXZ ENDP

; retail @ 0x008BD010 size 6
public ?d_008bd010@@YAXXZ
?d_008bd010@@YAXXZ PROC
    db 0FFh, 25h, 28h, 78h, 33h, 01h
?d_008bd010@@YAXXZ ENDP

; retail @ 0x008C44F0 size 32
public ?d_008c44f0@@YAXXZ
?d_008c44f0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 33h, 0C0h, 85h, 0D2h, 8Bh, 51h, 1Ch, 0Fh, 95h, 0C0h, 0C1h, 0E0h
    db 09h, 33h, 0C2h, 25h, 00h, 02h, 00h, 00h, 33h, 0D0h, 89h, 51h, 1Ch, 0C2h, 04h, 00h
?d_008c44f0@@YAXXZ ENDP

; retail @ 0x008C4510 size 20
public ?d_008c4510@@YAXXZ
?d_008c4510@@YAXXZ PROC
    db 0Fh, 0BFh, 41h, 0Ah, 8Bh, 4Ch, 24h, 04h, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 23h
    db 0C2h, 0C2h, 04h, 00h
?d_008c4510@@YAXXZ ENDP

; retail @ 0x008C7500 size 752
_TEXT ENDS
_TEXT$d00cc7500 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CC7500 size 752
public ?d_008c7500@@YAXXZ
?d_008c7500@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01059DD0
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 00Ch, 053h, 055h, 08Bh, 06Ch, 024h, 024h, 08Bh, 045h, 000h, 08Bh, 04Dh, 008h, 08Bh, 05Ch, 081h
    db 0FCh, 056h, 08Bh, 074h, 081h, 0F8h, 057h, 089h, 074h, 024h, 018h, 0C7h, 044h, 024h, 02Ch, 000h
    db 000h, 000h, 000h
    call ?AptGetSwfVersion@@YAIXZ
    db 083h, 0F8h, 007h, 00Fh, 085h, 0F7h, 000h, 000h, 000h, 08Bh, 043h, 004h, 0C1h, 0E8h, 00Fh, 0F6h
    db 0D0h, 0A8h, 001h, 074h, 008h, 0C7h, 044h, 024h, 02Ch, 001h, 000h, 000h, 000h, 08Bh, 04Eh, 004h
    db 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 074h, 004h, 0FFh, 044h, 024h, 02Ch, 08Bh, 044h
    db 024h, 02Ch, 048h, 00Fh, 084h, 0B5h, 000h, 000h, 000h, 048h, 00Fh, 085h, 0C0h, 000h, 000h, 000h
    db 0A1h
    dd ?Rva008D2A30Head@@3PAURva008D2A30Node@@A
    db 085h, 0C0h, 074h, 03Bh, 08Bh, 050h, 008h, 089h, 015h
    dd ?Rva008D2A30Head@@3PAURva008D2A30Node@@A
    db 08Bh, 015h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 072h, 004h, 03Bh, 032h, 08Dh, 04Ah, 004h, 07Ch, 012h, 081h, 060h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0C6h, 040h, 008h, 001h, 08Bh, 0F8h, 0E9h, 080h, 000h, 000h, 000h, 08Bh, 052h, 008h, 089h
    db 004h, 0B2h, 0FFh, 001h, 0C6h, 040h, 008h, 001h, 08Bh, 0F8h, 0EBh, 070h, 06Ah, 00Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 055h, 08Bh, 048h, 004h, 081h, 0E1h, 005h, 080h, 000h, 0F0h
    db 081h, 0C9h, 005h, 080h, 000h, 040h, 0C7h, 000h
    dd ??_7AptValue@@6B@
    db 089h, 048h, 004h, 08Bh, 035h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 07Eh, 004h, 03Bh, 03Eh, 08Dh, 056h, 004h, 07Ch, 017h, 081h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh
    db 089h, 048h, 004h, 0C7h, 000h
    dd ??_7Rva008995E0Value@@6B@
    db 0C6h, 040h, 008h, 001h, 08Bh, 0F8h, 0EBh, 022h, 08Bh, 04Eh, 008h, 089h, 004h, 0B9h, 0FFh, 002h
    db 0C7h, 000h
    dd ??_7Rva008995E0Value@@6B@
    db 0C6h, 040h, 008h, 001h, 08Bh, 0F8h, 0EBh, 00Ch, 033h, 0C0h, 08Bh, 0F8h, 0EBh, 006h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 085h, 0FFh, 00Fh, 085h, 058h, 001h, 000h, 000h, 08Bh, 074h, 024h, 018h, 066h, 0A1h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0B9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 089h, 04Ch, 024h, 014h, 066h, 040h, 066h, 040h, 0C7h, 044h, 024h, 024h, 000h, 000h, 000h, 000h
    db 089h, 04Ch, 024h, 010h, 066h, 0A3h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 054h, 024h, 014h, 052h, 08Bh, 0CBh, 0C6h, 044h, 024h, 028h, 001h
    call ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
    db 08Dh, 044h, 024h, 010h, 050h, 08Bh, 0CEh
    call ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
    db 08Bh, 044h, 024h, 014h, 08Bh, 054h, 024h, 010h, 00Fh, 0B7h, 048h, 002h, 00Fh, 0B7h, 072h, 002h
    db 03Bh, 0CEh, 075h, 018h, 03Bh, 0C2h, 074h, 00Ch, 08Dh, 07Ah, 008h, 08Dh, 070h, 008h, 033h, 0D2h
    db 0F3h, 0A6h, 075h, 008h, 0C7h, 044h, 024h, 02Ch, 001h, 000h, 000h, 000h, 08Bh, 054h, 024h, 02Ch
    db 0A1h
    dd ?Rva008D2A30Head@@3PAURva008D2A30Node@@A
    db 085h, 0D2h, 00Fh, 095h, 0C3h, 085h, 0C0h, 074h, 032h, 08Bh, 048h, 008h, 08Bh, 015h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 089h, 00Dh
    dd ?Rva008D2A30Head@@3PAURva008D2A30Node@@A
    db 08Bh, 072h, 004h, 03Bh, 032h, 08Dh, 04Ah, 004h, 07Ch, 00Ch, 081h, 060h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 088h, 058h, 008h, 0EBh, 06Dh, 08Bh, 052h, 008h, 089h, 004h, 0B2h, 0FFh, 001h, 088h, 058h
    db 008h, 0EBh, 060h, 06Ah, 00Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 04Fh, 08Bh, 048h, 004h, 081h, 0E1h, 005h, 080h, 000h, 0F0h
    db 081h, 0C9h, 005h, 080h, 000h, 040h, 0C7h, 000h
    dd ??_7AptValue@@6B@
    db 089h, 048h, 004h, 08Bh, 035h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 07Eh, 004h, 03Bh, 03Eh, 08Dh, 056h, 004h, 07Ch, 014h, 081h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh
    db 089h, 048h, 004h, 0C7h, 000h
    dd ??_7Rva008995E0Value@@6B@
    db 088h, 058h, 008h, 0EBh, 015h, 08Bh, 04Eh, 008h, 089h, 004h, 0B9h, 0FFh, 002h, 0C7h, 000h
    dd ??_7Rva008995E0Value@@6B@
    db 088h, 058h, 008h, 0EBh, 002h, 033h, 0C0h, 08Bh, 0F8h, 08Bh, 044h, 024h, 010h, 066h, 0FFh, 008h
    db 066h, 083h, 038h, 000h, 0C6h, 044h, 024h, 024h, 000h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 014h, 066h, 0FFh, 008h, 066h, 083h
    db 038h, 000h, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 0BEh, 001h, 000h, 000h, 000h, 08Bh, 04Dh, 000h, 08Bh, 055h
    db 008h, 02Bh, 0CEh, 08Bh, 00Ch, 08Ah, 08Bh, 041h, 004h, 0C1h, 0E8h, 01Eh, 0A8h, 001h, 075h, 005h
    db 08Bh, 011h, 0FFh, 052h, 004h, 046h, 083h, 0FEh, 002h, 07Eh, 0E0h, 08Bh, 075h, 000h, 08Bh, 04Dh
    db 008h, 083h, 0C6h, 0FEh, 089h, 075h, 000h, 08Bh, 0C6h, 089h, 03Ch, 081h, 0FFh, 045h, 000h, 08Bh
    db 057h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h
    db 08Bh, 04Ch, 024h, 01Ch, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 018h, 0C3h
?d_008c7500@@YAXXZ ENDP
_TEXT$d00cc7500 ENDS
_TEXT SEGMENT

; retail @ 0x008C77F0 size 346
public ?d_008c77f0@@YAXXZ
?d_008c77f0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0E8h, 9Dh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 55h, 56h, 8Bh, 74h, 24h, 1Ch, 8Bh, 06h, 8Bh, 4Eh
    db 08h, 8Bh, 4Ch, 81h, 0FCh, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 57h, 0C7h, 44h, 24h
    db 20h, 98h, 52h, 2Dh, 01h, 8Dh, 54h, 24h, 20h, 52h, 0C7h, 44h, 24h, 1Ch, 00h, 00h
    db 00h, 00h, 0E8h, 89h, 0Dh, 0FDh, 0FFh, 8Bh, 44h, 24h, 20h, 0Fh, 0B7h, 68h, 02h, 0A1h
    db 0D0h, 87h, 33h, 01h, 85h, 0C0h, 74h, 32h, 8Bh, 48h, 08h, 8Bh, 15h, 10h, 78h, 33h
    db 01h, 89h, 0Dh, 0D0h, 87h, 33h, 01h, 8Bh, 7Ah, 04h, 3Bh, 3Ah, 8Dh, 4Ah, 04h, 7Ch
    db 0Ch, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 68h, 08h, 0EBh, 6Dh, 8Bh, 52h, 08h
    db 89h, 04h, 0BAh, 0FFh, 01h, 89h, 68h, 08h, 0EBh, 60h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h
    db 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 4Fh, 8Bh, 48h, 04h, 81h, 0E1h, 07h, 80h
    db 00h, 0F0h, 81h, 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h, 48h
    db 04h, 8Bh, 3Dh, 10h, 78h, 33h, 01h, 8Bh, 5Fh, 04h, 3Bh, 1Fh, 8Dh, 57h, 04h, 7Ch
    db 14h, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 48h, 04h, 0C7h, 00h, 00h, 64h, 13h, 01h
    db 89h, 68h, 08h, 0EBh, 15h, 8Bh, 4Fh, 08h, 89h, 04h, 99h, 0FFh, 02h, 0C7h, 00h, 00h
    db 64h, 13h, 01h, 89h, 68h, 08h, 0EBh, 02h, 33h, 0C0h, 8Bh, 16h, 8Bh, 0F8h, 8Bh, 46h
    db 08h, 8Bh, 4Ch, 90h, 0FCh, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h
    db 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 1Eh, 8Bh, 4Eh, 08h, 4Bh, 89h, 1Eh, 8Bh, 0C3h, 89h
    db 3Ch, 81h, 0FFh, 06h, 8Bh, 57h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 06h, 8Bh
    db 07h, 8Bh, 0CFh, 0FFh, 10h, 8Bh, 44h, 24h, 20h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h
    db 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Dh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_008c77f0@@YAXXZ ENDP

; retail @ 0x008CB1C0 size 64
public ?d_008cb1c0@@YAXXZ
?d_008cb1c0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 01h, 8Ah, 10h, 40h, 88h, 54h, 24h, 08h, 8Ah, 10h, 40h
    db 89h, 01h, 8Bh, 44h, 24h, 04h, 88h, 54h, 24h, 09h, 8Bh, 50h, 60h, 0Fh, 0B7h, 4Ch
    db 24h, 08h, 8Bh, 0Ch, 8Ah, 8Bh, 10h, 56h, 8Bh, 70h, 08h, 89h, 0Ch, 96h, 0FFh, 00h
    db 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh, 0A8h, 01h, 5Eh, 75h, 04h, 8Bh, 11h, 0FFh, 22h, 0C3h
?d_008cb1c0@@YAXXZ ENDP

; retail @ 0x008CB200 size 86
public ?d_008cb200@@YAXXZ
?d_008cb200@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 01h, 8Ah, 10h, 40h, 88h, 54h, 24h, 08h, 8Ah, 10h, 40h
    db 88h, 54h, 24h, 09h, 8Ah, 10h, 40h, 88h, 54h, 24h, 0Ah, 8Ah, 10h, 40h, 88h, 54h
    db 24h, 0Bh, 89h, 01h, 8Bh, 44h, 24h, 08h, 56h, 50h, 0E8h, 0A1h, 9Ah, 0FDh, 0FFh, 8Bh
    db 54h, 24h, 0Ch, 8Bh, 0Ah, 8Bh, 72h, 08h, 89h, 04h, 8Eh, 8Bh, 0Ah, 83h, 0C4h, 04h
    db 41h, 89h, 0Ah, 8Bh, 50h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 5Eh, 75h, 06h, 8Bh
    db 10h, 8Bh, 0C8h, 0FFh, 22h, 0C3h
?d_008cb200@@YAXXZ ENDP

; retail @ 0x008CE890 size 64
public ?d_008ce890@@YAXXZ
?d_008ce890@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 08h, 8Bh, 50h, 04h, 56h, 8Bh, 74h, 24h, 08h, 6Ah
    db 00h, 6Ah, 01h, 6Ah, 01h, 68h, 10h, 87h, 33h, 01h, 51h, 52h, 8Bh, 0CEh, 0E8h, 8Dh
    db 0E0h, 0FFh, 0FFh, 8Bh, 0Eh, 8Bh, 56h, 08h, 89h, 04h, 8Ah, 0FFh, 06h, 8Bh, 48h, 04h
    db 0C1h, 0E9h, 1Eh, 0F6h, 0C1h, 01h, 5Eh, 75h, 06h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 22h, 0C3h
?d_008ce890@@YAXXZ ENDP

; retail @ 0x008CE8D0 size 61
public ?d_008ce8d0@@YAXXZ
?d_008ce8d0@@YAXXZ PROC
    db 56h, 6Ah, 00h, 0E8h, 08h, 29h, 0FDh, 0FFh, 8Bh, 74h, 24h, 0Ch, 8Bh, 0Eh, 8Bh, 56h
    db 08h, 89h, 04h, 8Ah, 8Bh, 0Eh, 83h, 0C4h, 04h, 41h, 89h, 0Eh, 8Bh, 48h, 04h, 0C1h
    db 0E9h, 1Eh, 0F6h, 0C1h, 01h, 75h, 06h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 12h, 8Bh, 44h, 24h
    db 0Ch, 50h, 56h, 0E8h, 28h, 0E8h, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Eh, 0C3h
?d_008ce8d0@@YAXXZ ENDP

; retail @ 0x008F8E40 size 32
public ?d_008f8e40@@YAXXZ
?d_008f8e40@@YAXXZ PROC
    db 8Bh, 54h, 24h, 10h, 8Bh, 0C1h, 8Bh, 4Ch, 24h, 04h, 89h, 08h, 8Bh, 4Ch, 24h, 08h
    db 89h, 50h, 04h, 8Bh, 54h, 24h, 0Ch, 89h, 48h, 08h, 89h, 50h, 0Ch, 0C2h, 10h, 00h
?d_008f8e40@@YAXXZ ENDP

; retail @ 0x008F8E60 size 3
public ?d_008f8e60@@YAXXZ
?d_008f8e60@@YAXXZ PROC
    db 8Bh, 0C1h, 0C3h
?d_008f8e60@@YAXXZ ENDP

; retail @ 0x008FD4A0 size 16
public ?d_008fd4a0@@YAXXZ
?d_008fd4a0@@YAXXZ PROC
    db 8Bh, 0Dh, 0E8h, 0B0h, 34h, 01h, 6Ah, 00h, 0E8h, 23h, 0A7h, 04h, 00h, 0B0h, 01h, 0C3h
?d_008fd4a0@@YAXXZ ENDP

; retail @ 0x008FD4B0 size 3
public ?d_008fd4b0@@YAXXZ
?d_008fd4b0@@YAXXZ PROC
    db 0B0h, 01h, 0C3h
?d_008fd4b0@@YAXXZ ENDP
_TEXT ENDS
END
