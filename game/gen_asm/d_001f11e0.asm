.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?g_bfmeDirectionWeight1285@@3MA:BYTE
EXTERN ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z:NEAR
EXTERN ?j_00003b34@@YAXXZ:NEAR
EXTERN ?j_00006d7f@@YAXXZ:NEAR
EXTERN ?j_0000835f@@YAXXZ:NEAR
EXTERN ?j_000095ed@@YAXXZ:NEAR
EXTERN ?j_0000b81b@@YAXXZ:NEAR
EXTERN ?j_0000de9f@@YAXXZ:NEAR
EXTERN ?j_0000e6e7@@YAXXZ:NEAR
EXTERN ?j_000122ab@@YAXXZ:NEAR
EXTERN ?j_0001336d@@YAXXZ:NEAR
EXTERN ?j_00014506@@YAXXZ:NEAR
EXTERN ?j_00014d7b@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_0002191d@@YAXXZ:NEAR
EXTERN ?j_00024d70@@YAXXZ:NEAR
EXTERN ?j_00026044@@YAXXZ:NEAR
EXTERN ?j_0002f734@@YAXXZ:NEAR
EXTERN ?j_000307e7@@YAXXZ:NEAR
EXTERN ?j_000348ec@@YAXXZ:NEAR
EXTERN ?j_00035e0e@@YAXXZ:NEAR
EXTERN ?j_0003a1a7@@YAXXZ:NEAR
EXTERN ?j_000402d2@@YAXXZ:NEAR
EXTERN ?j_0004b015@@YAXXZ:NEAR
_TEXT SEGMENT

; ghidra: FUN_005f11e0  retail @ 0x001F11E0 size 303
public ?d_001f11e0@@YAXXZ
?d_001f11e0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 53h, 56h, 8Bh, 74h, 24h, 24h, 8Bh, 06h, 57h, 8Dh, 4Ch, 24h, 0Ch
    db 0BBh, 01h, 00h, 00h, 00h, 51h, 8Bh, 0CEh, 88h, 5Ch, 24h, 10h, 88h, 5Ch, 24h, 11h
    db 0FFh, 50h, 28h, 8Bh, 7Ch, 24h, 2Ch, 8Bh, 17h, 8Bh, 4Fh, 04h, 2Bh, 0CAh, 0B8h, 0ABh
    db 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Bh, 16h
    db 89h, 44h, 24h, 28h, 8Dh, 44h, 24h, 2Ch, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 30h, 48h
    db 55h, 07h, 01h, 0FFh, 52h, 2Ch, 8Bh, 10h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0C8h, 0FFh
    db 52h, 74h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h, 74h, 2Bh, 8Bh, 5Fh, 04h
    db 8Bh, 3Fh, 3Bh, 0FBh, 0Fh, 84h, 0ACh, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 57h, 8Bh, 0CEh, 0FFh, 50h, 60h, 83h, 0C7h, 0Ch, 3Bh, 0FBh, 75h, 0F1h, 5Fh
    db 8Bh, 0C6h, 5Eh, 5Bh, 83h, 0C4h, 18h, 0C3h, 8Bh, 0Fh, 3Bh, 4Fh, 04h, 74h, 23h, 68h
    db 24h, 55h, 07h, 01h, 8Dh, 54h, 24h, 14h, 6Ah, 04h, 52h, 0E8h, 90h, 4Fh, 7Eh, 00h
    db 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 5Eh, 5Ah
    db 80h, 00h, 8Bh, 4Ch, 24h, 28h, 51h, 8Bh, 0CFh, 0E8h, 23h, 0C9h, 0E4h, 0FFh, 8Bh, 44h
    db 24h, 28h, 85h, 0C0h, 74h, 50h, 8Bh, 54h, 24h, 28h, 4Ah, 8Dh, 44h, 24h, 18h, 89h
    db 54h, 24h, 28h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh, 4Fh, 08h, 8Bh, 47h
    db 04h, 3Bh, 0C1h, 8Dh, 4Ch, 24h, 18h, 74h, 15h, 51h, 50h, 0E8h, 0C5h, 0EAh, 0E4h, 0FFh
    db 8Bh, 47h, 04h, 83h, 0C4h, 08h, 83h, 0C0h, 0Ch, 89h, 47h, 04h, 0EBh, 10h, 53h, 53h
    db 8Dh, 54h, 24h, 30h, 52h, 51h, 50h, 8Bh, 0CFh, 0E8h, 0CEh, 5Dh, 0E1h, 0FFh, 8Bh, 44h
    db 24h, 28h, 85h, 0C0h, 75h, 0B0h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 83h, 0C4h, 18h, 0C3h
?d_001f11e0@@YAXXZ ENDP

; ghidra: FUN_005f1360  retail @ 0x001F1360 size 8
public ?d_001f1360@@YAXXZ
?d_001f1360@@YAXXZ PROC
    db 83h, 0E9h, 04h, 0E9h, 0E7h, 58h, 0E5h, 0FFh
?d_001f1360@@YAXXZ ENDP

; ghidra: FUN_005f1620  retail @ 0x001F1620 size 449
_TEXT ENDS
_TEXT$d005f1620 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005F1620 size 449
public ?d_001f1620@@YAXXZ
?d_001f1620@@YAXXZ PROC
    db 083h, 0ECh, 06Ch, 055h, 056h, 08Bh, 0F1h, 057h, 08Bh, 07Eh, 008h, 08Bh, 047h, 038h, 089h, 044h
    db 024h, 010h, 08Bh, 04Fh, 03Ch, 089h, 04Ch, 024h, 014h, 0D9h, 047h, 040h, 0D8h, 005h
    dd ?g_bfmeDirectionWeight1285@@3MA
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Dh, 054h, 024h, 010h, 052h, 057h, 0D9h, 05Ch, 024h, 020h
    call ?j_0001c675@@YAXXZ
    db 08Bh, 0E8h, 055h, 08Bh, 0CFh
    call ?j_00035e0e@@YAXXZ
    db 08Bh, 054h, 024h, 014h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 001h, 06Ah, 001h, 06Ah, 000h, 055h, 052h, 08Bh, 054h, 024h, 020h, 052h, 0FFh, 050h, 01Ch
    db 0D9h, 05Ch, 024h, 018h, 08Dh, 044h, 024h, 010h, 050h, 08Bh, 0CFh
    call ?j_0003a1a7@@YAXXZ
    db 08Bh, 04Eh, 044h, 08Bh, 046h, 048h, 06Ah, 000h, 08Dh, 054h, 024h, 013h, 052h, 051h, 050h, 050h
    call ?j_00014d7b@@YAXXZ
    db 089h, 046h, 048h, 0C7h, 046h, 070h, 000h, 000h, 000h, 000h, 0C7h, 046h, 078h, 000h, 000h, 000h
    db 000h, 0C7h, 046h, 028h, 000h, 000h, 000h, 000h, 08Bh, 046h, 07Ch, 08Bh, 028h, 083h, 0C4h, 014h
    db 03Bh, 0E8h, 074h, 017h, 08Bh, 0C5h, 08Bh, 06Dh, 000h, 06Ah, 00Ch, 050h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 08Bh, 046h, 07Ch, 083h, 0C4h, 008h, 03Bh, 0E8h, 075h, 0E9h, 08Bh, 046h, 07Ch, 033h, 0C9h, 089h
    db 04Ch, 024h, 050h, 089h, 04Ch, 024h, 054h, 033h, 0D2h, 089h, 04Ch, 024h, 058h, 089h, 054h, 024h
    db 028h, 089h, 000h, 08Bh, 046h, 07Ch, 089h, 04Ch, 024h, 05Ch, 089h, 054h, 024h, 02Ch, 089h, 054h
    db 024h, 030h, 089h, 040h, 004h, 08Bh, 0C1h, 089h, 04Ch, 024h, 064h, 089h, 054h, 024h, 034h, 089h
    db 04Ch, 024h, 068h, 089h, 054h, 024h, 038h, 089h, 04Ch, 024h, 06Ch, 00Dh, 000h, 000h, 003h, 000h
    db 089h, 054h, 024h, 03Ch, 089h, 04Ch, 024h, 070h, 089h, 044h, 024h, 060h, 089h, 054h, 024h, 040h
    db 089h, 04Ch, 024h, 074h, 08Dh, 044h, 024h, 028h, 089h, 054h, 024h, 044h, 050h, 08Dh, 04Ch, 024h
    db 054h, 089h, 054h, 024h, 04Ch, 051h, 08Bh, 0CFh, 089h, 054h, 024h, 054h
    call ?j_000095ed@@YAXXZ
    db 08Bh, 076h, 004h, 08Ah, 046h, 019h, 084h, 0C0h, 074h, 029h, 08Bh, 08Fh, 01Ch, 001h, 000h, 000h
    db 0B8h, 000h, 000h, 008h, 000h, 085h, 0C8h, 075h, 00Fh, 00Bh, 0C8h, 089h, 08Fh, 01Ch, 001h, 000h
    db 000h, 08Bh, 0CFh
    call ?j_0002191d@@YAXXZ
    db 06Ah, 000h, 06Ah, 008h, 08Bh, 0CFh
    call ?j_00014506@@YAXXZ
    db 033h, 0D2h, 08Bh, 0C2h, 083h, 0C8h, 020h, 089h, 054h, 024h, 020h, 089h, 044h, 024h, 01Ch, 052h
    db 08Dh, 044h, 024h, 020h, 050h, 08Bh, 0CFh, 089h, 054h, 024h, 02Ch
    call ?j_000307e7@@YAXXZ
    db 08Bh, 076h, 038h, 085h, 0F6h, 08Bh, 0BFh, 004h, 002h, 000h, 000h, 076h, 018h, 085h, 0FFh, 074h
    db 022h, 06Ah, 002h, 056h, 08Dh, 04Fh, 020h
    call ?j_0001336d@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 083h, 0C4h, 06Ch, 0C2h, 004h, 000h, 085h, 0FFh, 074h, 00Ah, 06Ah, 002h, 08Dh
    db 04Fh, 020h
    call ?j_00024d70@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 083h, 0C4h, 06Ch, 0C2h, 004h, 000h
?d_001f1620@@YAXXZ ENDP
_TEXT$d005f1620 ENDS
_TEXT SEGMENT

; ghidra: FUN_005f1b90  retail @ 0x001F1B90 size 260
public ?d_001f1b90@@YAXXZ
?d_001f1b90@@YAXXZ PROC
    db 83h, 0ECh, 18h, 53h, 8Bh, 5Ch, 24h, 20h, 55h, 56h, 8Bh, 0F1h, 8Bh, 6Eh, 08h, 57h
    db 8Bh, 7Eh, 04h, 8Ah, 47h, 19h, 84h, 0C0h, 75h, 0Ch, 84h, 0DBh, 75h, 08h, 6Ah, 01h
    db 55h, 0E8h, 24h, 3Ch, 0E2h, 0FFh, 0FFh, 46h, 78h, 8Bh, 56h, 44h, 8Bh, 4Eh, 48h, 2Bh
    db 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 83h, 0F8h, 02h, 7Dh, 12h, 53h, 8Bh, 0CEh, 0E8h, 0ADh, 12h, 0E2h, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 8Bh, 56h, 44h, 8Dh, 0Ch, 40h, 0D9h, 44h
    db 8Ah, 0F4h, 8Dh, 0Ch, 8Ah, 8Dh, 44h, 40h, 0FAh, 0D8h, 24h, 82h, 0D9h, 5Ch, 24h, 10h
    db 0D9h, 41h, 0F8h, 0D8h, 61h, 0ECh, 0D9h, 54h, 24h, 14h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 44h
    db 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 05h, 50h, 53h
    db 07h, 01h, 0D9h, 44h, 24h, 2Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 1Ah, 8Bh
    db 4Ch, 24h, 2Ch, 0DDh, 0D8h, 51h, 0E8h, 08h, 5Eh, 0E3h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h
    db 0C9h, 0D9h, 5Ch, 24h, 10h, 0D8h, 4Ch, 24h, 14h, 0D9h, 44h, 24h, 10h, 8Bh, 0Dh, 0CCh
    db 0F4h, 2Eh, 01h, 0D8h, 4Fh, 20h, 6Ah, 00h, 0D8h, 45h, 38h, 0D9h, 5Ch, 24h, 20h, 0D8h
    db 4Fh, 20h, 0D8h, 45h, 3Ch, 0D9h, 5Ch, 24h, 24h, 8Bh, 44h, 24h, 24h, 8Bh, 11h, 50h
    db 8Bh, 44h, 24h, 24h, 50h, 0FFh, 52h, 18h, 0D9h, 5Ch, 24h, 24h, 8Bh, 16h, 8Dh, 44h
    db 24h, 1Ch, 50h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 52h, 2Ch, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h
    db 18h, 0C2h, 04h, 00h
?d_001f1b90@@YAXXZ ENDP

; ghidra: FUN_005f1e80  retail @ 0x001F1E80 size 34
public ?d_001f1e80@@YAXXZ
?d_001f1e80@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 19h, 8Bh, 44h, 24h, 14h, 8Bh, 54h, 24h, 10h
    db 50h, 8Bh, 44h, 24h, 10h, 52h, 8Bh, 54h, 24h, 10h, 50h, 52h, 0E8h, 0B8h, 0Bh, 0E1h
    db 0FFh, 0C3h
?d_001f1e80@@YAXXZ ENDP

; ghidra: FUN_005f1eb0  retail @ 0x001F1EB0 size 29
public ?d_001f1eb0@@YAXXZ
?d_001f1eb0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 14h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h, 0Ch
    db 50h, 8Bh, 44h, 24h, 0Ch, 52h, 50h, 0E8h, 05h, 42h, 0E2h, 0FFh, 0C3h
?d_001f1eb0@@YAXXZ ENDP

; ghidra: FUN_005f1f30  retail @ 0x001F1F30 size 48
public ?d_001f1f30@@YAXXZ
?d_001f1f30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 01h, 0C3h, 56h, 8Bh, 0B0h, 0F0h, 01h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 16h, 8Dh, 48h, 0Ch, 8Bh, 01h, 0FFh, 50h, 2Ch, 85h, 0C0h
    db 75h, 0Ch, 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0EAh, 33h, 0C0h, 5Eh, 0C3h
?d_001f1f30@@YAXXZ ENDP

; ghidra: FUN_005f2440  retail @ 0x001F2440 size 8
public ?d_001f2440@@YAXXZ
?d_001f2440@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0F8h, 54h, 69h, 00h
?d_001f2440@@YAXXZ ENDP

; ghidra: FUN_005f2450  retail @ 0x001F2450 size 171
public ?d_001f2450@@YAXXZ
?d_001f2450@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 8Bh, 0F1h, 0Fh, 84h, 90h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 55h, 8Bh, 6Ch, 24h, 28h, 75h, 04h
    db 85h, 0EDh, 74h, 7Eh, 53h, 8Bh, 5Ch, 24h, 20h, 8Bh, 83h, 48h, 01h, 00h, 00h, 83h
    db 0C7h, 0Ch, 85h, 0C0h, 7Eh, 6Bh, 89h, 44h, 24h, 24h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 85h, 0EDh, 74h, 2Bh, 8Dh, 44h, 24h, 10h, 50h, 57h, 53h, 8Bh, 0CEh, 0E8h, 59h, 0E2h
    db 0E4h, 0FFh, 8Bh, 0CDh, 0E8h, 0CEh, 0FAh, 0E1h, 0FFh, 84h, 0C0h, 75h, 12h, 6Ah, 00h, 6Ah
    db 00h, 6Ah, 00h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CDh, 0E8h, 62h, 96h, 0E2h, 0FFh, 8Bh
    db 44h, 24h, 28h, 85h, 0C0h, 74h, 24h, 8Dh, 54h, 24h, 10h, 52h, 57h, 53h, 8Bh, 0CEh
    db 0E8h, 26h, 0E2h, 0E4h, 0FFh, 8Bh, 4Eh, 08h, 6Ah, 00h, 6Ah, 00h, 8Dh, 44h, 24h, 18h
    db 50h, 51h, 8Bh, 4Ch, 24h, 38h, 0E8h, 6Eh, 05h, 0E1h, 0FFh, 0FFh, 4Ch, 24h, 24h, 75h
    db 9Fh, 5Bh, 5Dh, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 10h, 00h
?d_001f2450@@YAXXZ ENDP

; ghidra: FUN_005f2530  retail @ 0x001F2530 size 296
public ?d_001f2530@@YAXXZ
?d_001f2530@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 18h, 85h, 0C0h, 0Fh, 84h, 13h, 01h, 00h, 00h, 8Bh
    db 54h, 24h, 20h, 85h, 0D2h, 0Fh, 84h, 07h, 01h, 00h, 00h, 56h, 8Bh, 74h, 24h, 2Ch
    db 85h, 0F6h, 0Fh, 84h, 0F9h, 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h, 34h, 85h, 0DBh, 0Fh
    db 84h, 0EBh, 00h, 00h, 00h, 55h, 8Bh, 69h, 04h, 57h, 50h, 0E8h, 1Dh, 4Ah, 0E5h, 0FFh
    db 0D9h, 46h, 08h, 8Bh, 54h, 24h, 38h, 0D8h, 22h, 8Bh, 4Eh, 04h, 8Bh, 0F8h, 8Bh, 06h
    db 0D8h, 25h, 5Ch, 26h, 0Ah, 01h, 89h, 44h, 24h, 20h, 83h, 0C4h, 04h, 8Dh, 44h, 24h
    db 1Ch, 89h, 4Ch, 24h, 20h, 0D9h, 5Ch, 24h, 24h, 8Bh, 4Ch, 24h, 2Ch, 50h, 0E8h, 04h
    db 7Ch, 0E4h, 0FFh, 8Bh, 17h, 53h, 56h, 8Dh, 44h, 24h, 24h, 50h, 8Bh, 0CFh, 0FFh, 12h
    db 8Bh, 17h, 6Ah, 01h, 8Bh, 0CFh, 0FFh, 52h, 04h, 8Bh, 44h, 24h, 30h, 8Bh, 08h, 51h
    db 8Bh, 4Ch, 24h, 30h, 0E8h, 0DCh, 73h, 0E4h, 0FFh, 0D9h, 03h, 0D8h, 26h, 8Bh, 44h, 24h
    db 40h, 0D9h, 43h, 04h, 8Bh, 17h, 0D8h, 66h, 04h, 0D9h, 43h, 08h, 0D8h, 66h, 08h, 0D9h
    db 00h, 0D8h, 26h, 0D9h, 5Ch, 24h, 10h, 0D9h, 40h, 04h, 0D8h, 66h, 04h, 0D9h, 5Ch, 24h
    db 14h, 0D9h, 40h, 08h, 0D8h, 66h, 08h, 0D9h, 5Ch, 24h, 18h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h
    db 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DBh, 0DDh
    db 0D8h, 0DDh, 0D8h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 0D9h, 44h, 24h, 14h, 0D8h
    db 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h
    db 0FAh, 0D9h, 0C9h, 0D9h, 0C9h, 0DEh, 0F9h, 51h, 8Bh, 0CFh, 0D8h, 4Dh, 08h, 0D9h, 1Ch, 24h
    db 0FFh, 52h, 10h, 8Bh, 4Dh, 0Ch, 8Bh, 07h, 51h, 8Bh, 0CFh, 0FFh, 50h, 14h, 5Fh, 5Dh
    db 5Bh, 5Eh, 83h, 0C4h, 18h, 0C2h, 18h, 00h
?d_001f2530@@YAXXZ ENDP

; ghidra: FUN_005f2730  retail @ 0x001F2730 size 11
public ?d_001f2730@@YAXXZ
?d_001f2730@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_001f2730@@YAXXZ ENDP

; ghidra: FUN_005f27c0  retail @ 0x001F27C0 size 11
public ?d_001f27c0@@YAXXZ
?d_001f27c0@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_001f27c0@@YAXXZ ENDP

; ghidra: FUN_005f28b0  retail @ 0x001F28B0 size 32
public ?d_001f28b0@@YAXXZ
?d_001f28b0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 20h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 97h, 52h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_001f28b0@@YAXXZ ENDP

; ghidra: FUN_005f28e0  retail @ 0x001F28E0 size 32
public ?d_001f28e0@@YAXXZ
?d_001f28e0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 24h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 67h, 52h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_001f28e0@@YAXXZ ENDP

; ghidra: FUN_005f2910  retail @ 0x001F2910 size 37
public ?d_001f2910@@YAXXZ
?d_001f2910@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 8Dh, 4Ch, 81h, 64h, 51h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 32h, 52h, 69h, 00h, 8Bh, 0C6h
    db 5Eh, 59h, 0C2h, 08h, 00h
?d_001f2910@@YAXXZ ENDP

; ghidra: FUN_005f2940  retail @ 0x001F2940 size 46
public ?d_001f2940@@YAXXZ
?d_001f2940@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 8Dh, 14h, 42h, 56h, 8Bh, 74h, 24h
    db 0Ch, 03h, 0D0h, 8Dh, 44h, 91h, 74h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h, 00h, 00h
    db 00h, 00h, 0E8h, 0F9h, 51h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 0Ch, 00h
?d_001f2940@@YAXXZ ENDP

; ghidra: FUN_005f2980  retail @ 0x001F2980 size 49
public ?d_001f2980@@YAXXZ
?d_001f2980@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 8Dh, 14h, 42h, 56h, 8Bh, 74h, 24h
    db 0Ch, 03h, 0D0h, 8Dh, 84h, 91h, 0A4h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 08h, 00h, 00h, 00h, 00h, 0E8h, 0B6h, 51h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 0Ch
    db 00h
?d_001f2980@@YAXXZ ENDP

; ghidra: FUN_005f29c0  retail @ 0x001F29C0 size 40
public ?d_001f29c0@@YAXXZ
?d_001f29c0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 8Dh, 8Ch, 81h, 0D4h, 00h, 00h
    db 00h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 7Fh, 51h, 69h
    db 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 08h, 00h
?d_001f29c0@@YAXXZ ENDP

; ghidra: FUN_005f2a00  retail @ 0x001F2A00 size 48
public ?d_001f2a00@@YAXXZ
?d_001f2a00@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 83h, 0C0h, 13h, 8Dh, 14h, 42h, 56h
    db 8Bh, 74h, 24h, 0Ch, 03h, 0D0h, 8Dh, 04h, 91h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 37h, 51h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 0Ch, 00h
?d_001f2a00@@YAXXZ ENDP

; ghidra: FUN_005f2a40  retail @ 0x001F2A40 size 48
public ?d_001f2a40@@YAXXZ
?d_001f2a40@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 83h, 0C0h, 17h, 8Dh, 14h, 42h, 56h
    db 8Bh, 74h, 24h, 0Ch, 03h, 0D0h, 8Dh, 04h, 91h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 0F7h, 50h, 69h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 0Ch, 00h
?d_001f2a40@@YAXXZ ENDP

; ghidra: FUN_005f2a90  retail @ 0x001F2A90 size 8
public ?d_001f2a90@@YAXXZ
?d_001f2a90@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0A8h, 4Eh, 69h, 00h
?d_001f2a90@@YAXXZ ENDP

; ghidra: FUN_005f2aa0  retail @ 0x001F2AA0 size 61
public ?d_001f2aa0@@YAXXZ
?d_001f2aa0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 87h, 80h, 04h, 00h, 00h, 8Bh, 30h, 3Bh, 0F0h, 74h, 19h
    db 8Bh, 0C6h, 8Bh, 36h, 6Ah, 0Ch, 50h, 0E8h, 34h, 0BBh, 63h, 00h, 8Bh, 87h, 80h, 04h
    db 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0F0h, 75h, 0E7h, 8Bh, 87h, 80h, 04h, 00h, 00h, 89h
    db 00h, 8Bh, 0BFh, 80h, 04h, 00h, 00h, 89h, 7Fh, 04h, 5Fh, 5Eh, 0C3h
?d_001f2aa0@@YAXXZ ENDP

; ghidra: FUN_005f32a0  retail @ 0x001F32A0 size 82
public ?d_001f32a0@@YAXXZ
?d_001f32a0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C1h, 0AAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 14h, 89h, 04h, 24h, 85h, 0C0h, 0C7h
    db 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 1Ah, 8Bh, 4Ch, 24h, 18h, 8Bh, 11h, 89h
    db 10h, 8Bh, 51h, 04h, 83h, 0C1h, 08h, 51h, 8Dh, 48h, 08h, 89h, 50h, 04h, 0E8h, 7Dh
    db 48h, 69h, 00h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_001f32a0@@YAXXZ ENDP

; ghidra: FUN_005f3310  retail @ 0x001F3310 size 82
public ?d_001f3310@@YAXXZ
?d_001f3310@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F1h, 0AAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 14h, 89h, 04h, 24h, 85h, 0C0h, 0C7h
    db 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 1Ah, 8Bh, 4Ch, 24h, 18h, 8Bh, 11h, 89h
    db 10h, 8Bh, 51h, 04h, 83h, 0C1h, 08h, 51h, 8Dh, 48h, 08h, 89h, 50h, 04h, 0E8h, 0Dh
    db 48h, 69h, 00h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_001f3310@@YAXXZ ENDP

; ghidra: FUN_005f3c30  retail @ 0x001F3C30 size 212
public ?d_001f3c30@@YAXXZ
?d_001f3c30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 86h, 5Dh, 04h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 0C1h, 00h, 00h
    db 00h, 8Bh, 86h, 60h, 04h, 00h, 00h, 57h, 8Bh, 38h, 3Bh, 0F8h, 74h, 2Fh, 8Bh, 0FFh
    db 8Bh, 47h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 0F4h, 0B5h, 0E2h, 0FFh, 85h
    db 0C0h, 74h, 10h, 50h, 0E8h, 24h, 33h, 0E5h, 0FFh, 8Bh, 10h, 83h, 0C4h, 04h, 8Bh, 0C8h
    db 0FFh, 52h, 0Ch, 8Bh, 3Fh, 3Bh, 0BEh, 60h, 04h, 00h, 00h, 75h, 0D3h, 8Bh, 86h, 60h
    db 04h, 00h, 00h, 8Bh, 38h, 3Bh, 0F8h, 74h, 20h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h, 54h, 0A9h, 63h, 00h, 8Bh, 86h, 60h, 04h
    db 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h, 0E7h, 8Bh, 86h, 60h, 04h, 00h, 00h, 89h
    db 00h, 8Bh, 86h, 60h, 04h, 00h, 00h, 89h, 40h, 04h, 0C6h, 86h, 5Dh, 04h, 00h, 00h
    db 00h, 8Bh, 76h, 0E8h, 8Bh, 8Eh, 00h, 02h, 00h, 00h, 8Bh, 01h, 0FFh, 50h, 20h, 83h
    db 0F8h, 03h, 5Fh, 74h, 2Dh, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 83h, 0C6h, 38h
    db 56h, 0FFh, 92h, 98h, 00h, 00h, 00h, 85h, 0C0h, 74h, 17h, 8Bh, 80h, 88h, 00h, 00h
    db 00h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 6Ah, 01h, 50h, 0E8h, 7Dh, 47h
    db 0E3h, 0FFh, 5Eh, 0C3h
?d_001f3c30@@YAXXZ ENDP

; ghidra: FUN_005f4970  retail @ 0x001F4970 size 424
public ?d_001f4970@@YAXXZ
?d_001f4970@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 56h, 8Bh, 74h, 24h, 1Ch, 57h, 56h, 8Bh, 0F9h, 0E8h, 3Eh
    db 0FBh, 0E0h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 0Fh, 85h, 7Ch, 01h
    db 00h, 00h, 8Bh, 5Fh, 08h, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h, 14h, 88h, 44h, 24h
    db 15h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 89h, 5Ch, 24h, 1Ch, 0FFh, 52h, 28h, 8Bh
    db 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 18h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h
    db 8Bh, 01h, 8Dh, 53h, 38h, 52h, 0FFh, 90h, 98h, 00h, 00h, 00h, 8Bh, 4Bh, 74h, 89h
    db 48h, 60h, 8Dh, 5Fh, 2Ch, 0BDh, 04h, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 53h, 56h, 0E8h, 0CDh, 7Fh, 0E1h, 0FFh, 83h, 0C4h, 08h, 83h, 0C3h, 04h, 4Dh, 75h, 0F0h
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 2Eh, 8Bh, 54h, 24h, 18h, 8Bh
    db 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 83h, 0C2h, 38h, 52h, 0FFh, 90h, 98h, 00h, 00h
    db 00h, 8Bh, 4Fh, 2Ch, 89h, 48h, 64h, 8Bh, 57h, 30h, 89h, 50h, 68h, 8Bh, 4Fh, 34h
    db 89h, 48h, 6Ch, 8Bh, 57h, 38h, 89h, 50h, 70h, 8Bh, 06h, 8Dh, 8Fh, 7Dh, 04h, 00h
    db 00h, 51h, 8Bh, 0CEh, 0FFh, 90h, 8Ch, 00h, 00h, 00h, 8Bh, 8Fh, 80h, 04h, 00h, 00h
    db 33h, 0EDh, 89h, 6Ch, 24h, 20h, 8Bh, 01h, 33h, 0D2h, 3Bh, 0C1h, 74h, 09h, 8Bh, 0FFh
    db 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 8Dh, 44h, 24h, 20h, 89h, 54h, 24h, 20h, 8Bh
    db 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 7Ch, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h
    db 74h, 31h, 8Bh, 87h, 80h, 04h, 00h, 00h, 8Bh, 18h, 3Bh, 0D8h, 74h, 71h, 8Bh, 0FFh
    db 8Bh, 43h, 08h, 8Dh, 4Ch, 24h, 10h, 51h, 56h, 89h, 44h, 24h, 18h, 0E8h, 22h, 7Fh
    db 0E1h, 0FFh, 8Bh, 1Bh, 8Bh, 87h, 80h, 04h, 00h, 00h, 83h, 0C4h, 08h, 3Bh, 0D8h, 75h
    db 0DFh, 0EBh, 4Ch, 66h, 39h, 6Ch, 24h, 20h, 76h, 45h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Dh, 54h, 24h, 10h, 52h, 56h, 0E8h, 0F9h, 7Eh, 0E1h, 0FFh, 8Bh, 9Fh, 80h, 04h, 00h
    db 00h, 6Ah, 0Ch, 0E8h, 78h, 9Ah, 63h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 0Ch, 85h, 0C9h
    db 74h, 06h, 8Bh, 54h, 24h, 10h, 89h, 11h, 8Bh, 4Bh, 04h, 89h, 18h, 89h, 48h, 04h
    db 89h, 01h, 89h, 43h, 04h, 0Fh, 0B7h, 44h, 24h, 20h, 45h, 3Bh, 0E8h, 72h, 0C1h, 8Bh
    db 16h, 8Dh, 87h, 84h, 04h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 81h
    db 0C7h, 7Ch, 04h, 00h, 00h, 57h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_001f4970@@YAXXZ ENDP

; ghidra: FUN_005f4cc0  retail @ 0x001F4CC0 size 278
public ?d_001f4cc0@@YAXXZ
?d_001f4cc0@@YAXXZ PROC
    db 83h, 0ECh, 64h, 55h, 8Bh, 0E9h, 8Bh, 45h, 0E4h, 8Bh, 88h, 00h, 02h, 00h, 00h, 8Bh
    db 11h, 89h, 6Ch, 24h, 08h, 0FFh, 52h, 18h, 8Bh, 44h, 24h, 6Ch, 0D8h, 78h, 1Ch, 8Bh
    db 40h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0D9h, 5Ch, 24h, 08h, 0E8h, 61h, 0A5h
    db 0E2h, 0FFh, 85h, 0C0h, 74h, 23h, 8Bh, 40h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h
    db 85h, 0C9h, 74h, 05h, 0E8h, 0B2h, 0D5h, 0E0h, 0FFh, 0F7h, 80h, 0C8h, 00h, 00h, 00h, 00h
    db 00h, 00h, 01h, 0Fh, 85h, 0B6h, 00h, 00h, 00h, 53h, 56h, 33h, 0DBh, 57h, 83h, 0C5h
    db 0FCh, 8Bh, 55h, 00h, 53h, 8Bh, 0CDh, 0FFh, 52h, 04h, 8Bh, 0C8h, 85h, 0C9h, 0Fh, 84h
    db 8Eh, 00h, 00h, 00h, 8Bh, 35h, 98h, 08h, 2Fh, 01h, 8Bh, 86h, 0B4h, 00h, 00h, 00h
    db 8Bh, 0BEh, 0B8h, 00h, 00h, 00h, 2Bh, 0F8h, 33h, 0D2h, 0C1h, 0FFh, 02h, 8Bh, 0C1h, 0F7h
    db 0F7h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 64h, 8Bh, 0FFh
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 55h, 85h, 0D2h, 74h
    db 51h, 8Bh, 72h, 08h, 85h, 0F6h, 74h, 4Ah, 8Bh, 0BEh, 00h, 02h, 00h, 00h, 8Dh, 4Ch
    db 24h, 18h, 0E8h, 4Eh, 7Ch, 0E3h, 0FFh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 18h, 0D8h, 4Ch
    db 24h, 10h, 8Bh, 44h, 24h, 14h, 8Bh, 48h, 0E4h, 8Bh, 44h, 24h, 78h, 0D9h, 5Ch, 24h
    db 34h, 8Bh, 51h, 74h, 8Bh, 48h, 10h, 89h, 4Ch, 24h, 28h, 8Dh, 4Ch, 24h, 18h, 89h
    db 54h, 24h, 20h, 8Bh, 50h, 18h, 8Bh, 06h, 51h, 8Bh, 0CEh, 89h, 54h, 24h, 34h, 0FFh
    db 50h, 34h, 43h, 83h, 0FBh, 04h, 0Fh, 8Ch, 55h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 5Dh
    db 83h, 0C4h, 64h, 0C2h, 04h, 00h
?d_001f4cc0@@YAXXZ ENDP

; ghidra: FUN_005f5500  retail @ 0x001F5500 size 231
public ?d_001f5500@@YAXXZ
?d_001f5500@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 0ADh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 53h, 56h, 33h, 0DBh, 57h, 89h, 5Ch, 24h
    db 1Ch, 8Bh, 74h, 24h, 30h, 8Bh, 86h, 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CEh, 89h, 5Ch
    db 24h, 2Ch, 89h, 5Ch, 24h, 18h, 0E8h, 35h, 0B4h, 65h, 00h, 8Bh, 0F8h, 68h, 24h, 28h
    db 0Ah, 01h, 57h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 24h
    db 57h, 68h, 0FCh, 27h, 0Ah, 01h, 8Dh, 44h, 24h, 14h, 6Ah, 03h, 50h, 0E8h, 9Eh, 0B0h
    db 65h, 00h, 83h, 0C4h, 10h, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 10h, 51h, 0E8h
    db 8Ch, 17h, 80h, 00h, 8Bh, 7Ch, 24h, 34h, 53h, 8Dh, 54h, 24h, 34h, 52h, 57h, 56h
    db 0E8h, 0C2h, 0F5h, 0E0h, 0FFh, 8Bh, 44h, 24h, 40h, 57h, 8Dh, 5Ch, 24h, 2Ch, 89h, 44h
    db 24h, 28h, 0E8h, 39h, 0CDh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 4Ch, 8Bh, 39h, 6Ah, 14h, 0E8h
    db 9Ch, 8Fh, 63h, 00h, 8Bh, 0F0h, 8Dh, 54h, 24h, 2Ch, 52h, 8Dh, 46h, 08h, 50h, 0E8h
    db 0D0h, 26h, 0E1h, 0FFh, 8Bh, 47h, 04h, 89h, 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h
    db 20h, 8Dh, 4Ch, 24h, 1Ch, 89h, 77h, 04h, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 6Bh, 23h, 69h, 00h, 8Bh, 4Ch, 24h, 20h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 20h, 0C3h
?d_001f5500@@YAXXZ ENDP

; ghidra: FUN_005f5620  retail @ 0x001F5620 size 231
public ?d_001f5620@@YAXXZ
?d_001f5620@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 0ADh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 53h, 56h, 33h, 0DBh, 57h, 89h, 5Ch, 24h
    db 1Ch, 8Bh, 74h, 24h, 30h, 8Bh, 86h, 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CEh, 89h, 5Ch
    db 24h, 2Ch, 89h, 5Ch, 24h, 18h, 0E8h, 15h, 0B3h, 65h, 00h, 8Bh, 0F8h, 68h, 50h, 28h
    db 0Ah, 01h, 57h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 24h
    db 57h, 68h, 28h, 28h, 0Ah, 01h, 8Dh, 44h, 24h, 14h, 6Ah, 03h, 50h, 0E8h, 7Eh, 0AFh
    db 65h, 00h, 83h, 0C4h, 10h, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 10h, 51h, 0E8h
    db 6Ch, 16h, 80h, 00h, 8Bh, 7Ch, 24h, 34h, 53h, 8Dh, 54h, 24h, 34h, 52h, 57h, 56h
    db 0E8h, 0FBh, 74h, 0E4h, 0FFh, 8Bh, 44h, 24h, 40h, 57h, 8Dh, 5Ch, 24h, 2Ch, 89h, 44h
    db 24h, 28h, 0E8h, 19h, 0CCh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 4Ch, 8Bh, 39h, 6Ah, 14h, 0E8h
    db 7Ch, 8Eh, 63h, 00h, 8Bh, 0F0h, 8Dh, 54h, 24h, 2Ch, 52h, 8Dh, 46h, 08h, 50h, 0E8h
    db 0C2h, 2Fh, 0E3h, 0FFh, 8Bh, 47h, 04h, 89h, 3Eh, 89h, 46h, 04h, 89h, 30h, 83h, 0C4h
    db 20h, 8Dh, 4Ch, 24h, 1Ch, 89h, 77h, 04h, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 4Bh, 22h, 69h, 00h, 8Bh, 4Ch, 24h, 20h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 20h, 0C3h
?d_001f5620@@YAXXZ ENDP

; ghidra: FUN_005f5740  retail @ 0x001F5740 size 146
public ?d_001f5740@@YAXXZ
?d_001f5740@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 57h, 89h, 4Ch, 24h, 10h, 33h, 0FFh, 8Dh, 59h, 0F8h, 8Bh, 0FFh
    db 8Bh, 03h, 57h, 8Bh, 0CBh, 0FFh, 50h, 04h, 8Bh, 0C8h, 85h, 0C9h, 74h, 4Bh, 8Bh, 35h
    db 98h, 08h, 2Fh, 01h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 0AEh, 0B8h, 00h, 00h, 00h
    db 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h, 8Bh, 0C1h, 0F7h, 0F5h, 8Bh, 86h, 0B4h, 00h, 00h
    db 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 21h, 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h
    db 0D2h, 75h, 0F5h, 0EBh, 14h, 85h, 0D2h, 74h, 10h, 8Bh, 4Ah, 08h, 85h, 0C9h, 74h, 09h
    db 6Ah, 00h, 6Ah, 08h, 0E8h, 5Dh, 0EDh, 0E1h, 0FFh, 47h, 83h, 0FFh, 04h, 7Ch, 0A1h, 8Bh
    db 74h, 24h, 10h, 8Dh, 4Eh, 0D8h, 0E8h, 61h, 4Bh, 0E1h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh
    db 01h, 8Bh, 51h, 3Ch, 5Fh, 89h, 96h, 5Ch, 04h, 00h, 00h, 5Eh, 5Dh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_001f5740@@YAXXZ ENDP

; ghidra: FUN_005f59a0  retail @ 0x001F59A0 size 48
public ?d_001f59a0@@YAXXZ
?d_001f59a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 01h, 0C3h, 56h, 8Bh, 0B0h, 0F0h, 01h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 16h, 8Dh, 48h, 0Ch, 8Bh, 01h, 0FFh, 50h, 34h, 85h, 0C0h
    db 75h, 0Ch, 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0EAh, 33h, 0C0h, 5Eh, 0C3h
?d_001f59a0@@YAXXZ ENDP

; ghidra: FUN_005f5b90  retail @ 0x001F5B90 size 32
public ?d_001f5b90@@YAXXZ
?d_001f5b90@@YAXXZ PROC
    db 0C7h, 41h, 20h, 2Ch, 29h, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0A3h, 20h, 0E5h, 0FFh
?d_001f5b90@@YAXXZ ENDP

; ghidra: FUN_005f5e80  retail @ 0x001F5E80 size 131
public ?d_001f5e80@@YAXXZ
?d_001f5e80@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 33h, 0E6h, 0E0h, 0FFh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 65h, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h
    db 0Ch, 88h, 44h, 24h, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Dh
    db 4Fh, 24h, 51h, 56h, 0E8h, 77h, 4Dh, 0E2h, 0FFh, 8Bh, 16h, 83h, 0C4h, 08h, 8Dh, 47h
    db 28h, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh, 16h, 8Dh, 47h, 34h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 60h, 8Bh, 16h, 8Dh, 47h, 40h, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh, 16h, 8Dh
    db 47h, 4Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 47h, 50h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 6Ch, 8Bh, 16h, 83h, 0C7h, 54h, 57h, 8Bh, 0CEh, 0FFh, 52h, 60h, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_001f5e80@@YAXXZ ENDP

; ghidra: FUN_005f5f70  retail @ 0x001F5F70 size 39
public ?d_001f5f70@@YAXXZ
?d_001f5f70@@YAXXZ PROC
    db 0C7h, 41h, 10h, 7Ch, 2Ah, 0Ah, 01h, 0C7h, 41h, 14h, 78h, 2Ah, 0Ah, 01h, 0C7h, 41h
    db 18h, 68h, 2Ah, 0Ah, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh
    db 09h, 01h, 0E9h, 0BCh, 1Ch, 0E5h, 0FFh
?d_001f5f70@@YAXXZ ENDP

; ghidra: FUN_005f64e0  retail @ 0x001F64E0 size 388
public ?d_001f64e0@@YAXXZ
?d_001f64e0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 0F8h, 8Dh, 4Eh, 0F8h, 89h, 74h, 24h
    db 08h, 0FFh, 50h, 04h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 53h, 8Dh, 0E2h, 0FFh
    db 8Bh, 0D8h, 85h, 0DBh, 89h, 5Ch, 24h, 0Ch, 0Fh, 84h, 4Eh, 01h, 00h, 00h, 8Bh, 4Eh
    db 0F0h, 8Bh, 89h, 00h, 02h, 00h, 00h, 8Bh, 11h, 57h, 0FFh, 52h, 18h, 8Bh, 7Ch, 24h
    db 18h, 0D8h, 7Fh, 1Ch, 8Bh, 0B3h, 0F0h, 01h, 00h, 00h, 8Bh, 06h, 85h, 0C0h, 0D9h, 5Ch
    db 24h, 18h, 0Fh, 84h, 23h, 01h, 00h, 00h, 8Dh, 48h, 0Ch, 8Bh, 01h, 0FFh, 50h, 2Ch
    db 8Bh, 0D8h, 85h, 0DBh, 75h, 13h, 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0E8h
    db 5Fh, 5Eh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h, 8Bh, 4Fh, 08h, 51h, 8Bh, 0Dh, 98h
    db 08h, 2Fh, 01h, 0E8h, 0EBh, 8Ch, 0E2h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 74h, 46h, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 3Ah, 0BDh, 0E0h
    db 0FFh, 0F7h, 80h, 0C8h, 00h, 00h, 00h, 00h, 00h, 40h, 00h, 0Fh, 85h, 0CAh, 00h, 00h
    db 00h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 17h, 0BDh, 0E0h, 0FFh, 0F7h, 80h, 0C8h, 00h, 00h, 00h, 00h, 00h, 00h, 01h, 0Fh, 85h
    db 0A7h, 00h, 00h, 00h, 33h, 0FFh, 55h, 8Bh, 13h, 57h, 8Bh, 0CBh, 0FFh, 52h, 04h, 8Bh
    db 0C8h, 85h, 0C9h, 74h, 69h, 8Bh, 35h, 98h, 08h, 2Fh, 01h, 8Bh, 86h, 0B4h, 00h, 00h
    db 00h, 8Bh, 0AEh, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h, 8Bh, 0C1h
    db 0F7h, 0F5h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 3Fh, 90h
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 31h, 85h, 0D2h, 74h
    db 2Dh, 8Bh, 72h, 08h, 85h, 0F6h, 74h, 26h, 8Bh, 4Ch, 24h, 10h, 8Bh, 41h, 0F0h, 3Bh
    db 0F0h, 74h, 1Bh, 8Bh, 8Eh, 00h, 02h, 00h, 00h, 8Bh, 11h, 8Bh, 2Eh, 50h, 0FFh, 52h
    db 18h, 0D8h, 4Ch, 24h, 20h, 51h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0FFh, 55h, 40h, 47h, 83h
    db 0FFh, 04h, 7Ch, 83h, 8Bh, 74h, 24h, 14h, 8Bh, 44h, 24h, 10h, 8Bh, 8Eh, 00h, 02h
    db 00h, 00h, 8Bh, 40h, 0F0h, 8Bh, 11h, 8Bh, 3Eh, 50h, 0FFh, 52h, 18h, 0D8h, 4Ch, 24h
    db 20h, 51h, 8Bh, 0CEh, 0D9h, 1Ch, 24h, 0FFh, 57h, 40h, 5Dh, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 08h, 0C2h, 04h, 00h
?d_001f64e0@@YAXXZ ENDP

; ghidra: FUN_005f66d0  retail @ 0x001F66D0 size 78
public ?d_001f66d0@@YAXXZ
?d_001f66d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 41h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch
    db 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0CFh, 0BBh, 0E0h, 0FFh, 0F7h, 80h, 0C8h, 00h
    db 00h, 00h, 00h, 00h, 00h, 01h, 74h, 22h, 8Bh, 0B6h, 0F0h, 01h, 00h, 00h, 8Bh, 06h
    db 85h, 0C0h, 74h, 16h, 8Dh, 48h, 0Ch, 8Bh, 01h, 0FFh, 50h, 30h, 85h, 0C0h, 75h, 0Ch
    db 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0EAh, 33h, 0C0h, 5Eh, 0C3h
?d_001f66d0@@YAXXZ ENDP

; ghidra: FUN_005f6740  retail @ 0x001F6740 size 25
public ?d_001f6740@@YAXXZ
?d_001f6740@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0FAh, 14h, 0E5h, 0FFh
?d_001f6740@@YAXXZ ENDP

; ghidra: FUN_005f6960  retail @ 0x001F6960 size 178
public ?d_001f6960@@YAXXZ
?d_001f6960@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0F0h, 0ADh, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h, 14h, 85h, 0DBh, 55h, 56h, 57h, 74h
    db 7Ch, 8Bh, 79h, 04h, 8Bh, 77h, 18h, 3Bh, 77h, 1Ch, 74h, 71h, 8Bh, 6Ch, 24h, 24h
    db 56h, 8Dh, 4Ch, 24h, 28h, 0E8h, 0C6h, 11h, 69h, 00h, 8Bh, 44h, 24h, 24h, 85h, 0C0h
    db 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h
    db 8Bh, 38h, 07h, 01h, 50h, 8Dh, 4Ch, 24h, 24h, 0E8h, 02h, 22h, 69h, 00h, 6Ah, 00h
    db 6Ah, 00h, 6Ah, 01h, 55h, 8Dh, 44h, 24h, 30h, 50h, 8Bh, 0CBh, 0C6h, 44h, 24h, 2Ch
    db 01h, 0E8h, 0F0h, 27h, 0E4h, 0FFh, 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 18h, 00h, 0E8h
    db 5Ch, 0Fh, 69h, 00h, 8Dh, 4Ch, 24h, 24h, 83h, 0C6h, 04h, 0C7h, 44h, 24h, 18h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 48h, 0Fh, 69h, 00h, 3Bh, 77h, 1Ch, 75h, 93h, 8Bh, 4Ch, 24h
    db 10h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h
?d_001f6960@@YAXXZ ENDP

; ghidra: FUN_005f6c70  retail @ 0x001F6C70 size 126
public ?d_001f6c70@@YAXXZ
?d_001f6c70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 29h, 0AEh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 10h
    db 68h, 28h, 0D8h, 40h, 00h, 68h, 0D9h, 7Bh, 41h, 00h, 6Ah, 04h, 6Ah, 04h, 33h, 0EDh
    db 8Dh, 7Eh, 08h, 57h, 89h, 6Ch, 24h, 30h, 0C7h, 06h, 88h, 2Ch, 0Ah, 01h, 0E8h, 31h
    db 02h, 80h, 00h, 89h, 6Eh, 18h, 89h, 6Eh, 1Ch, 89h, 6Eh, 20h, 0C6h, 44h, 24h, 1Ch
    db 02h, 0BBh, 04h, 00h, 00h, 00h, 55h, 68h, 1Ch, 30h, 07h, 01h, 8Bh, 0CFh, 0E8h, 4Dh
    db 10h, 69h, 00h, 83h, 0C7h, 04h, 4Bh, 75h, 0EDh, 8Bh, 4Ch, 24h, 14h, 5Fh, 8Bh, 0C6h
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_001f6c70@@YAXXZ ENDP

; ghidra: FUN_005f6d40  retail @ 0x001F6D40 size 90
public ?d_001f6d40@@YAXXZ
?d_001f6d40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Eh, 0AEh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 18h
    db 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0E8h, 45h, 0FDh, 0E2h, 0FFh, 68h, 28h, 0D8h
    db 40h, 00h, 6Ah, 04h, 6Ah, 04h, 8Dh, 46h, 08h, 50h, 0C6h, 44h, 24h, 20h, 00h, 0E8h
    db 0F2h, 0FFh, 7Fh, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 44h, 37h, 07h, 01h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_001f6d40@@YAXXZ ENDP

; ghidra: FUN_005f6ee0  retail @ 0x001F6EE0 size 46
public ?d_001f6ee0@@YAXXZ
?d_001f6ee0@@YAXXZ PROC
    db 0C7h, 01h, 0DCh, 30h, 0Ah, 01h, 0C7h, 41h, 0Ch, 18h, 30h, 0Ah, 01h, 0C7h, 41h, 10h
    db 08h, 30h, 0Ah, 01h, 0C7h, 41h, 20h, 04h, 30h, 0Ah, 01h, 0C7h, 41h, 24h, 0F0h, 2Fh
    db 0Ah, 01h, 0C7h, 41h, 50h, 0E0h, 2Fh, 0Ah, 01h, 0E9h, 83h, 0B7h, 0E3h, 0FFh
?d_001f6ee0@@YAXXZ ENDP

; ghidra: FUN_005f6f90  retail @ 0x001F6F90 size 11
public ?d_001f6f90@@YAXXZ
?d_001f6f90@@YAXXZ PROC
    db 85h, 0C9h, 74h, 04h, 8Dh, 41h, 50h, 0C3h, 33h, 0C0h, 0C3h
?d_001f6f90@@YAXXZ ENDP

; ghidra: FUN_005f70a0  retail @ 0x001F70A0 size 104
public ?d_001f70a0@@YAXXZ
?d_001f70a0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 98h, 0F7h, 2Eh, 01h, 6Ah, 0FFh, 68h, 0BEh
    db 0AEh, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 98h, 0F7h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 20h, 09h, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0F5h, 3Ch
    db 0E4h, 0FFh, 0A3h, 94h, 0F7h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 94h, 0F7h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_001f70a0@@YAXXZ ENDP

; ghidra: FUN_005f7790  retail @ 0x001F7790 size 32
public ?d_001f7790@@YAXXZ
?d_001f7790@@YAXXZ PROC
    db 0C7h, 41h, 20h, 90h, 31h, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0A3h, 04h, 0E5h, 0FFh
?d_001f7790@@YAXXZ ENDP

; ghidra: FUN_005f7810  retail @ 0x001F7810 size 33
public ?d_001f7810@@YAXXZ
?d_001f7810@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 0A0h, 31h, 0Ah, 01h, 0C7h, 40h, 08h, 58h, 02h, 00h
    db 00h, 89h, 48h, 0Ch, 89h, 48h, 10h, 89h, 48h, 14h, 89h, 48h, 18h, 89h, 48h, 1Ch
    db 0C3h
?d_001f7810@@YAXXZ ENDP

; ghidra: FUN_005f79f0  retail @ 0x001F79F0 size 96
public ?d_001f79f0@@YAXXZ
?d_001f79f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0F8h, 8Bh, 01h, 0FFh, 50h, 28h, 85h, 0C0h, 8Bh, 4Eh, 0F8h
    db 8Bh, 89h, 04h, 02h, 00h, 00h, 74h, 41h, 85h, 0C9h, 74h, 3Dh, 8Bh, 46h, 14h, 85h
    db 0C0h, 7Eh, 04h, 48h, 89h, 46h, 14h, 8Bh, 46h, 18h, 85h, 0C0h, 7Eh, 24h, 48h, 89h
    db 46h, 18h, 74h, 0Ch, 8Bh, 11h, 0FFh, 92h, 80h, 01h, 00h, 00h, 84h, 0C0h, 75h, 12h
    db 8Bh, 46h, 10h, 8Dh, 4Eh, 10h, 6Ah, 01h, 0FFh, 50h, 08h, 0C7h, 46h, 18h, 00h, 00h
    db 00h, 00h, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 5Eh, 0C3h
?d_001f79f0@@YAXXZ ENDP

; ghidra: FUN_005f7b10  retail @ 0x001F7B10 size 289
public ?d_001f7b10@@YAXXZ
?d_001f7b10@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0D9h, 8Bh, 73h, 0E8h, 85h, 0F6h, 57h, 8Bh, 7Bh, 0E4h
    db 89h, 7Ch, 24h, 10h, 0Fh, 84h, 1Ch, 01h, 00h, 00h, 8Bh, 06h, 55h, 8Bh, 0CEh, 0FFh
    db 50h, 28h, 8Bh, 0E8h, 85h, 0EDh, 0Fh, 84h, 09h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0B7h
    db 8Eh, 0E2h, 0FFh, 8Bh, 08h, 0F6h, 0C5h, 01h, 0Fh, 85h, 0F7h, 00h, 00h, 00h, 0F7h, 86h
    db 20h, 01h, 00h, 00h, 00h, 00h, 00h, 01h, 0Fh, 85h, 0E7h, 00h, 00h, 00h, 0F6h, 86h
    db 24h, 01h, 00h, 00h, 04h, 0Fh, 85h, 0DAh, 00h, 00h, 00h, 8Bh, 8Eh, 04h, 02h, 00h
    db 00h, 85h, 0C9h, 0Fh, 84h, 0CCh, 00h, 00h, 00h, 8Bh, 11h, 0FFh, 92h, 80h, 01h, 00h
    db 00h, 84h, 0C0h, 0Fh, 84h, 0BCh, 00h, 00h, 00h, 8Bh, 7Fh, 08h, 85h, 0FFh, 0Fh, 8Eh
    db 0B1h, 00h, 00h, 00h, 8Bh, 43h, 04h, 8Dh, 4Bh, 04h, 03h, 0C7h, 89h, 01h, 8Bh, 11h
    db 8Dh, 04h, 0BFh, 89h, 44h, 24h, 10h, 3Bh, 0C2h, 8Dh, 44h, 24h, 10h, 7Ch, 02h, 8Bh
    db 0C1h, 8Bh, 00h, 89h, 01h, 8Bh, 4Bh, 08h, 85h, 0C9h, 0Fh, 8Fh, 85h, 00h, 00h, 00h
    db 99h, 0F7h, 0FFh, 83h, 0F8h, 03h, 7Fh, 13h, 6Ah, 74h, 68h, 00h, 34h, 0Ah, 01h, 6Ah
    db 03h, 6Ah, 01h, 0E8h, 0D6h, 9Fh, 0E0h, 0FFh, 83h, 0C4h, 10h, 85h, 0C0h, 7Eh, 66h, 8Dh
    db 78h, 0FFh, 83h, 0FFh, 04h, 77h, 23h, 0FFh, 24h, 0BDh, 50h, 7Ch, 5Fh, 00h, 0B8h, 00h
    db 00h, 00h, 04h, 0EBh, 1Ah, 0B8h, 00h, 00h, 00h, 08h, 0EBh, 13h, 0B8h, 00h, 00h, 00h
    db 10h, 0EBh, 0Ch, 0B8h, 00h, 00h, 00h, 20h, 0EBh, 05h, 0B8h, 00h, 00h, 00h, 40h, 8Bh
    db 8Eh, 20h, 01h, 00h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 20h, 01h, 00h
    db 00h, 8Bh, 0CEh, 0E8h, 0F5h, 9Ch, 0E2h, 0FFh, 6Ah, 00h, 8Bh, 0CDh, 0E8h, 08h, 58h, 0E3h
    db 0FFh
?d_001f7b10@@YAXXZ ENDP

; ghidra: FUN_005f7cc0  retail @ 0x001F7CC0 size 208
public ?d_001f7cc0@@YAXXZ
?d_001f7cc0@@YAXXZ PROC
    db 83h, 0ECh, 50h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0E8h, 8Bh, 01h, 57h, 0FFh, 50h, 28h, 8Bh
    db 0F8h, 85h, 0FFh, 0Fh, 84h, 0AFh, 00h, 00h, 00h, 33h, 0C9h, 89h, 4Ch, 24h, 08h, 33h
    db 0D2h, 89h, 4Ch, 24h, 0Ch, 89h, 54h, 24h, 08h, 89h, 4Ch, 24h, 10h, 89h, 54h, 24h
    db 0Ch, 89h, 4Ch, 24h, 14h, 89h, 54h, 24h, 10h, 89h, 54h, 24h, 14h, 8Bh, 0C2h, 0Dh
    db 00h, 00h, 00h, 0FCh, 89h, 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 33h, 0C0h, 89h, 44h
    db 24h, 30h, 89h, 44h, 24h, 34h, 89h, 4Ch, 24h, 1Ch, 89h, 44h, 24h, 38h, 89h, 4Ch
    db 24h, 20h, 89h, 44h, 24h, 3Ch, 89h, 54h, 24h, 1Ch, 89h, 4Ch, 24h, 24h, 89h, 44h
    db 24h, 40h, 89h, 54h, 24h, 20h, 89h, 4Ch, 24h, 28h, 89h, 44h, 24h, 44h, 89h, 54h
    db 24h, 24h, 89h, 4Ch, 24h, 2Ch, 89h, 54h, 24h, 28h, 89h, 44h, 24h, 48h, 8Dh, 4Ch
    db 24h, 30h, 89h, 54h, 24h, 2Ch, 89h, 44h, 24h, 4Ch, 51h, 8Bh, 4Eh, 0E8h, 8Dh, 54h
    db 24h, 0Ch, 89h, 44h, 24h, 54h, 52h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 89h, 44h
    db 24h, 5Ch, 0E8h, 76h, 18h, 0E1h, 0FFh, 8Ah, 44h, 24h, 5Ch, 84h, 0C0h, 74h, 09h, 6Ah
    db 00h, 8Bh, 0CFh, 0E8h, 0B1h, 56h, 0E3h, 0FFh, 5Fh, 5Eh, 83h, 0C4h, 50h, 0C2h, 04h, 00h
?d_001f7cc0@@YAXXZ ENDP

; ghidra: FUN_005f7dd0  retail @ 0x001F7DD0 size 25
public ?d_001f7dd0@@YAXXZ
?d_001f7dd0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 6Ah, 0FEh, 0E4h, 0FFh
?d_001f7dd0@@YAXXZ ENDP

; ghidra: FUN_005f7f20  retail @ 0x001F7F20 size 104
public ?d_001f7f20@@YAXXZ
?d_001f7f20@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 0A8h, 0F7h, 2Eh, 01h, 6Ah, 0FFh, 68h, 0BEh
    db 0AFh, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 0A8h, 0F7h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 74h, 0Ch, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 75h, 2Eh
    db 0E4h, 0FFh, 0A3h, 0A4h, 0F7h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 0A4h, 0F7h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_001f7f20@@YAXXZ ENDP

; ghidra: FUN_005f8080  retail @ 0x001F8080 size 542
public ?d_001f8080@@YAXXZ
?d_001f8080@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 8Bh, 0E9h, 8Bh, 45h, 0F4h, 56h, 8Bh, 75h, 0F8h, 8Bh, 9Eh
    db 04h, 02h, 00h, 00h, 85h, 0DBh, 89h, 44h, 24h, 10h, 74h, 09h, 0F6h, 86h, 44h, 03h
    db 00h, 00h, 01h, 74h, 0Ch, 5Eh, 5Dh, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 5Bh, 83h, 0C4h, 14h
    db 0C3h, 8Bh, 0CEh, 0E8h, 42h, 89h, 0E2h, 0FFh, 8Bh, 08h, 0F6h, 0C5h, 01h, 74h, 0Ch, 5Eh
    db 5Dh, 0B8h, 05h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 14h, 0C3h, 57h, 8Bh, 0BEh, 14h, 02h
    db 00h, 00h, 85h, 0FFh, 74h, 11h, 6Ah, 6Ch, 8Bh, 0CFh, 0E8h, 40h, 0A4h, 0E3h, 0FFh, 84h
    db 0C0h, 0Fh, 84h, 0AAh, 01h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Ah, 48h, 14h, 84h, 0C9h
    db 74h, 2Bh, 85h, 0FFh, 74h, 27h, 6Ah, 6Ch, 8Bh, 0CFh, 0E8h, 20h, 0A4h, 0E3h, 0FFh, 84h
    db 0C0h, 74h, 16h, 8Bh, 0CFh, 0E8h, 0F0h, 88h, 0E2h, 0FFh, 80h, 38h, 00h, 6Ah, 07h, 8Bh
    db 0CEh, 0Fh, 89h, 56h, 01h, 00h, 00h, 0EBh, 2Ch, 8Bh, 44h, 24h, 14h, 0F6h, 86h, 28h
    db 01h, 00h, 00h, 10h, 0Fh, 85h, 67h, 01h, 00h, 00h, 8Ah, 4Dh, 10h, 84h, 0C9h, 74h
    db 48h, 8Bh, 0CEh, 0E8h, 0C2h, 88h, 0E2h, 0FFh, 80h, 38h, 00h, 0Fh, 88h, 50h, 01h, 00h
    db 00h, 6Ah, 07h, 8Bh, 0CEh, 0E8h, 0A2h, 0C7h, 0E3h, 0FFh, 8Bh, 8Eh, 20h, 01h, 00h, 00h
    db 0B8h, 00h, 00h, 40h, 00h, 85h, 0C8h, 0Fh, 85h, 34h, 01h, 00h, 00h, 0Bh, 0C8h, 89h
    db 8Eh, 20h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0B1h, 97h, 0E2h, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h
    db 05h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 14h, 0C3h, 8Bh, 48h, 08h, 89h, 4Ch, 24h, 10h
    db 8Ah, 48h, 15h, 84h, 0C9h, 74h, 52h, 8Bh, 0CBh, 0E8h, 14h, 0E0h, 0E2h, 0FFh, 85h, 0C0h
    db 74h, 47h, 8Bh, 0CBh, 0E8h, 09h, 0E0h, 0E2h, 0FFh, 8Bh, 56h, 38h, 8Bh, 4Eh, 40h, 8Bh
    db 0F8h, 8Bh, 46h, 3Ch, 89h, 54h, 24h, 18h, 8Dh, 57h, 38h, 89h, 4Ch, 24h, 20h, 52h
    db 8Dh, 4Ch, 24h, 1Ch, 89h, 44h, 24h, 20h, 0E8h, 0F9h, 0A4h, 0E1h, 0FFh, 8Dh, 4Ch, 24h
    db 18h, 0E8h, 9Ch, 84h, 0E2h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0D9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Bh, 0EBh, 38h, 8Bh, 44h, 24h, 10h, 8Bh, 0Dh, 14h
    db 0F2h, 2Eh, 01h, 6Ah, 00h, 6Ah, 00h, 6Ah, 62h, 50h, 56h, 0E8h, 0A0h, 77h, 0E4h, 0FFh
    db 8Bh, 0F8h, 85h, 0FFh, 74h, 1Dh, 0D9h, 47h, 40h, 0D8h, 66h, 40h, 0D9h, 0E1h, 0D9h, 44h
    db 24h, 10h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 02h, 33h, 0FFh, 8Bh, 5Ch, 24h, 14h, 8Ah, 43h, 0Ch, 84h, 0C0h, 74h, 14h, 68h, 0CBh
    db 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0F6h, 28h, 0E4h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0FFh, 0FEh
    db 0FFh, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 43h, 10h, 8Bh, 49h, 3Ch, 8Bh, 5Dh
    db 14h, 2Bh, 0C1h, 03h, 0C3h, 85h, 0C0h, 7Fh, 4Dh, 85h, 0FFh, 89h, 4Dh, 14h, 74h, 0Dh
    db 0F6h, 87h, 44h, 03h, 00h, 00h, 01h, 0Fh, 84h, 0D4h, 0FEh, 0FFh, 0FFh, 8Bh, 0CEh, 0E8h
    db 96h, 87h, 0E2h, 0FFh, 80h, 38h, 00h, 79h, 28h, 6Ah, 07h, 8Bh, 0CEh, 0E8h, 39h, 0A0h
    db 0E1h, 0FFh, 8Bh, 86h, 20h, 01h, 00h, 00h, 0A9h, 00h, 00h, 40h, 00h, 74h, 12h, 25h
    db 0FFh, 0FFh, 0BFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 8Ch, 96h, 0E2h
    db 0FFh, 0B8h, 05h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 14h, 0C3h
?d_001f8080@@YAXXZ ENDP

; ghidra: FUN_005f8340  retail @ 0x001F8340 size 32
public ?d_001f8340@@YAXXZ
?d_001f8340@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0E0h, 36h, 0Ah, 01h, 0C7h, 41h, 18h, 0CCh, 36h, 0Ah, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0F3h, 0F8h, 0E4h, 0FFh
?d_001f8340@@YAXXZ ENDP

; ghidra: FUN_005f84c0  retail @ 0x001F84C0 size 115
public ?d_001f84c0@@YAXXZ
?d_001f84c0@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Ah, 43h, 3Ch, 84h, 0C0h, 74h, 67h, 56h, 57h, 8Dh, 73h, 24h, 0BFh
    db 06h, 00h, 00h, 00h, 8Bh, 0Eh, 85h, 0C9h, 74h, 3Eh, 8Ah, 41h, 48h, 84h, 0C0h, 74h
    db 25h, 8Bh, 41h, 60h, 83h, 0F8h, 01h, 74h, 0Fh, 83h, 0F8h, 02h, 74h, 0Ah, 83h, 0F8h
    db 03h, 74h, 05h, 83h, 0F8h, 04h, 75h, 0Eh, 0A1h, 14h, 0F2h, 2Eh, 01h, 51h, 8Bh, 48h
    db 0Ch, 0E8h, 0AAh, 0E8h, 0E1h, 0FFh, 8Bh, 0Eh, 85h, 0C9h, 74h, 06h, 8Bh, 11h, 6Ah, 01h
    db 0FFh, 12h, 0C7h, 06h, 00h, 00h, 00h, 00h, 83h, 0C6h, 04h, 4Fh, 75h, 0B6h, 0A1h, 14h
    db 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 0E8h, 5Ch, 12h, 0E1h, 0FFh, 5Fh, 0C6h, 43h, 3Ch, 00h
    db 5Eh, 5Bh, 0C3h
?d_001f84c0@@YAXXZ ENDP

; ghidra: FUN_005f8660  retail @ 0x001F8660 size 19
public ?d_001f8660@@YAXXZ
?d_001f8660@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Dh, 4Eh, 0E4h, 0E8h, 0D5h, 40h, 0E4h, 0FFh, 0C6h, 46h, 21h, 01h, 5Eh
    db 0C2h, 04h, 00h
?d_001f8660@@YAXXZ ENDP

; ghidra: FUN_005f8c80  retail @ 0x001F8C80 size 104
public ?d_001f8c80@@YAXXZ
?d_001f8c80@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 0B8h, 0F7h, 2Eh, 01h, 6Ah, 0FFh, 68h, 1Eh
    db 0B0h, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 0B8h, 0F7h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 3Ch, 0Bh, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 15h, 21h
    db 0E4h, 0FFh, 0A3h, 0B4h, 0F7h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 0B4h, 0F7h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_001f8c80@@YAXXZ ENDP

; ghidra: FUN_005f8dc0  retail @ 0x001F8DC0 size 10
public ?d_001f8dc0@@YAXXZ
?d_001f8dc0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 0D9h, 80h, 0D8h, 00h, 00h, 00h, 0C3h
?d_001f8dc0@@YAXXZ ENDP

; ghidra: FUN_005f8e20  retail @ 0x001F8E20 size 273
_TEXT ENDS
_TEXT$d005f8e20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005F8E20 size 273
public ?d_001f8e20@@YAXXZ
?d_001f8e20@@YAXXZ PROC
    db 083h, 0ECh, 02Ch, 056h, 057h, 08Bh, 0F1h, 08Bh, 07Eh, 004h, 08Dh, 044h, 024h, 010h, 050h, 08Dh
    db 04Ch, 024h, 020h, 051h, 08Bh, 04Eh, 008h, 0C7h, 044h, 024h, 024h, 000h, 000h, 080h, 03Fh, 0C7h
    db 044h, 024h, 028h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 02Ch, 000h, 000h, 000h, 000h
    call ?j_0002f734@@YAXXZ
    db 0D9h, 044h, 024h, 010h, 08Bh, 04Eh, 008h, 0D8h, 061h, 038h, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h
    db 024h, 014h, 0D8h, 061h, 03Ch, 0D9h, 0C0h, 0D9h, 0E1h, 0D9h, 05Ch, 024h, 008h, 0D9h, 044h, 024h
    db 010h, 0D9h, 0E1h, 0D9h, 054h, 024h, 00Ch, 0D8h, 05Ch, 024h, 008h, 0DFh, 0E0h, 0F6h, 0C4h, 041h
    db 08Dh, 044h, 024h, 00Ch, 074h, 004h, 08Dh, 044h, 024h, 008h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 081h, 0C7h, 0CCh, 000h, 000h, 000h, 0D8h, 030h, 0D9h, 044h, 024h, 010h, 0D8h, 0C9h, 0D9h, 05Ch
    db 024h, 010h, 0D9h, 0C0h, 0D8h, 0CAh, 0D9h, 05Ch, 024h, 014h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 05Ch, 024h, 018h, 08Bh, 017h, 089h, 054h, 024h, 01Ch, 0DDh, 0D8h, 08Bh, 047h, 004h, 0D9h
    db 044h, 024h, 018h, 089h, 044h, 024h, 020h, 0D8h, 04Ch, 024h, 018h, 08Bh, 057h, 008h, 0D9h, 044h
    db 024h, 010h, 08Dh, 044h, 024h, 028h, 0D8h, 04Ch, 024h, 010h, 089h, 054h, 024h, 024h, 050h, 08Dh
    db 054h, 024h, 020h, 0DEh, 0C1h, 052h, 0D9h, 044h, 024h, 01Ch, 0D8h, 04Ch, 024h, 01Ch, 0DEh, 0C1h
    db 0D9h, 0FAh, 0D9h, 044h, 024h, 024h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 028h
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 028h, 0DDh, 0D8h
    call ?j_0002f734@@YAXXZ
    db 08Bh, 044h, 024h, 038h, 0D9h, 044h, 024h, 028h, 08Bh, 04Ch, 024h, 02Ch, 0D9h, 018h, 08Bh, 054h
    db 024h, 030h, 05Fh, 089h, 048h, 004h, 089h, 050h, 008h, 05Eh, 083h, 0C4h, 02Ch, 0C2h, 004h, 000h
?d_001f8e20@@YAXXZ ENDP
_TEXT$d005f8e20 ENDS
_TEXT SEGMENT

; ghidra: FUN_005f9180  retail @ 0x001F9180 size 342
public ?d_001f9180@@YAXXZ
?d_001f9180@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 66h, 0B0h, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0CCh, 00h, 00h, 00h, 56h, 57h, 8Bh, 0F9h, 8Bh
    db 77h, 04h, 8Bh, 86h, 0C8h, 00h, 00h, 00h, 85h, 0C0h, 7Ch, 13h, 8Bh, 96h, 0ACh, 00h
    db 00h, 00h, 2Bh, 96h, 0A8h, 00h, 00h, 00h, 0C1h, 0FAh, 03h, 3Bh, 0C2h, 7Ch, 28h, 8Bh
    db 84h, 24h, 0E4h, 00h, 00h, 00h, 85h, 0C0h, 74h, 16h, 8Bh, 7Fh, 08h, 83h, 0C7h, 38h
    db 8Bh, 0Fh, 89h, 08h, 8Bh, 57h, 04h, 89h, 50h, 04h, 8Bh, 4Fh, 08h, 89h, 48h, 08h
    db 0B0h, 01h, 0E9h, 0D6h, 00h, 00h, 00h, 68h, 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h
    db 00h, 6Ah, 10h, 6Ah, 0Ch, 8Dh, 54h, 24h, 24h, 52h, 0E8h, 0E5h, 0DCh, 7Fh, 00h, 8Bh
    db 86h, 0A4h, 00h, 00h, 00h, 85h, 0C0h, 8Bh, 4Fh, 08h, 0C7h, 84h, 24h, 0DCh, 00h, 00h
    db 00h, 00h, 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h
    db 01h, 6Ah, 00h, 6Ah, 01h, 6Ah, 00h, 8Dh, 54h, 24h, 20h, 52h, 8Bh, 56h, 70h, 52h
    db 50h, 0E8h, 77h, 75h, 0E1h, 0FFh, 8Bh, 8Eh, 0C8h, 00h, 00h, 00h, 8Bh, 86h, 0A8h, 00h
    db 00h, 00h, 8Dh, 04h, 0C8h, 8Bh, 00h, 8Dh, 04h, 40h, 8Bh, 54h, 84h, 14h, 8Bh, 4Ch
    db 84h, 18h, 8Dh, 44h, 84h, 14h, 89h, 54h, 24h, 08h, 8Bh, 50h, 08h, 8Bh, 84h, 24h
    db 0E4h, 00h, 00h, 00h, 85h, 0C0h, 89h, 4Ch, 24h, 0Ch, 89h, 54h, 24h, 10h, 74h, 14h
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 54h, 24h, 0Ch, 89h, 08h, 8Bh, 4Ch, 24h, 10h, 89h, 50h
    db 04h, 89h, 48h, 08h, 8Bh, 15h, 14h, 0F2h, 2Eh, 01h, 8Bh, 4Ah, 0Ch, 53h, 6Ah, 00h
    db 8Dh, 44h, 24h, 10h, 50h, 0E8h, 8Bh, 3Bh, 0E4h, 0FFh, 68h, 4Ch, 36h, 41h, 00h, 6Ah
    db 10h, 6Ah, 0Ch, 8Dh, 4Ch, 24h, 24h, 51h, 8Ah, 0D8h, 0C7h, 84h, 24h, 0F0h, 00h, 00h
    db 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0BCh, 0DAh, 7Fh, 00h, 8Ah, 0C3h, 5Bh, 8Bh, 8Ch, 24h
    db 0D4h, 00h, 00h, 00h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0D8h
    db 00h, 00h, 00h, 0C2h, 04h, 00h
?d_001f9180@@YAXXZ ENDP

; ghidra: FUN_005f9520  retail @ 0x001F9520 size 76
public ?d_001f9520@@YAXXZ
?d_001f9520@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Dh, 44h, 24h, 10h, 8Bh, 0F1h, 50h, 8Bh, 0CFh
    db 0E8h, 1Ch, 3Ah, 0E4h, 0FFh, 8Bh, 4Fh, 04h, 50h, 2Bh, 0Fh, 0C1h, 0F9h, 02h, 51h, 8Bh
    db 0CEh, 0E8h, 8Dh, 7Dh, 0E2h, 0FFh, 8Bh, 5Fh, 04h, 8Bh, 3Fh, 3Bh, 0DFh, 8Bh, 06h, 74h
    db 10h, 2Bh, 0DFh, 53h, 57h, 50h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h
    db 0C3h, 89h, 46h, 04h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_001f9520@@YAXXZ ENDP

; ghidra: FUN_005f9be0  retail @ 0x001F9BE0 size 45
public ?d_001f9be0@@YAXXZ
?d_001f9be0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 98h, 6Fh, 0E2h, 0FFh, 8Ah, 46h, 3Dh, 84h, 0C0h, 75h, 1Ch, 8Bh
    db 46h, 04h, 8Ah, 88h, 0C4h, 00h, 00h, 00h, 84h, 0C9h, 75h, 07h, 8Ah, 46h, 3Ch, 84h
    db 0C0h, 74h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 39h, 0C4h, 0E2h, 0FFh, 5Eh, 0C3h
?d_001f9be0@@YAXXZ ENDP

; ghidra: FUN_005f9c20  retail @ 0x001F9C20 size 50
public ?d_001f9c20@@YAXXZ
?d_001f9c20@@YAXXZ PROC
    db 0A1h, 98h, 08h, 2Fh, 01h, 8Ah, 50h, 6Ah, 84h, 0D2h, 75h, 23h, 8Ah, 41h, 31h, 83h
    db 0C1h, 0F4h, 84h, 0C0h, 75h, 19h, 8Bh, 51h, 04h, 8Ah, 82h, 0C4h, 00h, 00h, 00h, 84h
    db 0C0h, 75h, 07h, 8Ah, 41h, 3Ch, 84h, 0C0h, 74h, 05h, 0E8h, 0F5h, 0C3h, 0E2h, 0FFh, 0C2h
    db 04h, 00h
?d_001f9c20@@YAXXZ ENDP

; ghidra: FUN_005f9c60  retail @ 0x001F9C60 size 145
_TEXT ENDS
_TEXT$d005f9c60 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005F9C60 size 145
public ?d_001f9c60@@YAXXZ
?d_001f9c60@@YAXXZ PROC
    db 053h, 056h, 057h, 08Bh, 0F9h, 08Dh, 05Fh, 0F0h, 08Bh, 0CBh
    call ?j_0000835f@@YAXXZ
    db 08Bh, 077h, 0F8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 028h, 085h, 0C0h, 074h, 049h, 08Bh, 07Fh
    db 0F4h, 08Bh, 097h, 0C0h, 000h, 000h, 000h, 085h, 0D2h, 074h, 03Ch, 00Fh, 0B7h, 04Ah, 004h, 085h
    db 0C9h, 07Eh, 034h, 08Bh, 0FAh, 085h, 0FFh, 08Dh, 04Fh, 008h, 075h, 005h, 0B9h
    dd ?Rva006A16B0Empty@@3PADA
    db 051h, 08Bh, 0C8h
    call ?j_00003b34@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 056h
    call ?j_00006d7f@@YAXXZ
    db 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 04Ah, 00Ch, 056h
    call ?j_0000b81b@@YAXXZ
    db 08Bh, 0CBh
    call ?j_00026044@@YAXXZ
    db 08Bh, 086h, 004h, 002h, 000h, 000h, 085h, 0C0h, 074h, 016h, 08Bh, 0CEh
    call ?j_0000de9f@@YAXXZ
    db 085h, 0C0h, 074h, 00Bh, 08Bh, 04Eh, 074h, 08Bh, 010h, 051h, 08Bh, 0C8h, 0FFh, 052h, 008h, 05Fh
    db 05Eh, 05Bh, 0C3h
?d_001f9c60@@YAXXZ ENDP
_TEXT$d005f9c60 ENDS
_TEXT SEGMENT

; ghidra: FUN_005fa220  retail @ 0x001FA220 size 203
public ?d_001fa220@@YAXXZ
?d_001fa220@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0B1h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 34h
    db 8Bh, 0Eh, 85h, 0C9h, 74h, 27h, 8Bh, 46h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 42h, 7Ch, 68h, 00h, 83h, 0C4h
    db 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 76h, 43h, 63h, 00h, 83h, 0C4h, 08h, 83h, 0C6h, 0Ch
    db 3Bh, 0F3h, 75h, 0CCh, 8Bh, 37h, 85h, 0F6h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh
    db 74h, 47h, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh
    db 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 1Bh, 56h, 0E8h, 0F6h, 7Bh, 68h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h
    db 56h, 0E8h, 1Ah, 43h, 63h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_001fa220@@YAXXZ ENDP

; ghidra: FUN_005fabc0  retail @ 0x001FABC0 size 16
public ?d_001fabc0@@YAXXZ
?d_001fabc0@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 38h, 3Ch, 0Ah, 01h, 0C7h, 40h, 08h, 80h, 4Fh, 0C3h, 47h, 0C3h
?d_001fabc0@@YAXXZ ENDP

; ghidra: FUN_005fabe0  retail @ 0x001FABE0 size 17
public ?d_001fabe0@@YAXXZ
?d_001fabe0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 0A0h, 3Ch, 0Ah, 01h, 0E8h, 30h, 5Dh, 65h, 00h
    db 0C3h
?d_001fabe0@@YAXXZ ENDP

; ghidra: FUN_005fad80  retail @ 0x001FAD80 size 25
public ?d_001fad80@@YAXXZ
?d_001fad80@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0BAh, 0CEh, 0E4h, 0FFh
?d_001fad80@@YAXXZ ENDP

; ghidra: FUN_005fae30  retail @ 0x001FAE30 size 139
_TEXT ENDS
_TEXT$d005fae30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005FAE30 size 139
public ?d_001fae30@@YAXXZ
?d_001fae30@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 08Ah, 044h, 024h, 010h, 056h, 08Bh, 071h, 008h, 033h, 0C9h, 089h, 04Ch, 024h
    db 004h, 084h, 0C0h, 08Bh, 0C1h, 089h, 04Ch, 024h, 00Ch, 08Dh, 054h, 024h, 004h, 08Bh, 0CEh, 074h
    db 035h, 06Ah, 001h, 00Dh, 000h, 000h, 020h, 000h, 052h, 089h, 044h, 024h, 010h
    call ?j_000307e7@@YAXXZ
    db 06Ah, 016h, 08Bh, 0CEh
    call ?j_000348ec@@YAXXZ
    db 08Bh, 08Eh, 004h, 002h, 000h, 000h, 085h, 0C9h, 074h, 03Fh, 08Bh, 001h, 06Ah, 008h, 0FFh, 090h
    db 0FCh, 001h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h, 06Ah, 000h, 00Dh, 000h, 000h
    db 020h, 000h, 052h, 089h, 044h, 024h, 010h
    call ?j_000307e7@@YAXXZ
    db 06Ah, 016h, 08Bh, 0CEh
    call ?j_000122ab@@YAXXZ
    db 08Bh, 08Eh, 004h, 002h, 000h, 000h, 085h, 0C9h, 074h, 00Ah, 08Bh, 001h, 06Ah, 000h, 0FFh, 090h
    db 0FCh, 001h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h
?d_001fae30@@YAXXZ ENDP
_TEXT$d005fae30 ENDS
_TEXT SEGMENT

; ghidra: FUN_005faf60  retail @ 0x001FAF60 size 102
public ?d_001faf60@@YAXXZ
?d_001faf60@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 08h, 33h, 0C9h, 89h, 4Ch, 24h, 08h
    db 8Bh, 0C1h, 51h, 8Dh, 54h, 24h, 0Ch, 89h, 4Ch, 24h, 14h, 0Dh, 00h, 00h, 20h, 00h
    db 52h, 8Bh, 0CEh, 0C7h, 47h, 20h, 00h, 00h, 00h, 00h, 89h, 44h, 24h, 14h, 0E8h, 54h
    db 58h, 0E3h, 0FFh, 6Ah, 16h, 8Bh, 0CEh, 0E8h, 0Fh, 73h, 0E1h, 0FFh, 8Bh, 8Eh, 04h, 02h
    db 00h, 00h, 85h, 0C9h, 74h, 0Ah, 8Bh, 01h, 6Ah, 00h, 0FFh, 90h, 0FCh, 01h, 00h, 00h
    db 8Bh, 4Fh, 08h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 51h, 8Bh, 0CFh, 0E8h, 1Ah, 0A8h, 0E1h, 0FFh
    db 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C3h
?d_001faf60@@YAXXZ ENDP

; ghidra: FUN_005fafe0  retail @ 0x001FAFE0 size 137
public ?d_001fafe0@@YAXXZ
?d_001fafe0@@YAXXZ PROC
    db 0D9h, 41h, 10h, 83h, 0ECh, 0Ch, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 6Dh, 0D9h, 41h, 10h, 0D8h, 25h, 34h, 53h, 07h, 01h, 0D9h, 51h, 10h, 0DCh
    db 1Dh, 58h, 5Fh, 08h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 7Ah, 54h, 56h, 8Bh, 71h, 0F8h
    db 0C7h, 41h, 10h, 00h, 00h, 00h, 00h, 33h, 0C9h, 89h, 4Ch, 24h, 04h, 8Bh, 0C1h, 51h
    db 8Dh, 54h, 24h, 08h, 89h, 4Ch, 24h, 10h, 0Dh, 00h, 00h, 20h, 00h, 52h, 8Bh, 0CEh
    db 89h, 44h, 24h, 10h, 0E8h, 0AEh, 57h, 0E3h, 0FFh, 6Ah, 16h, 8Bh, 0CEh, 0E8h, 69h, 72h
    db 0E1h, 0FFh, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 5Eh, 74h, 0Ah, 8Bh, 01h, 6Ah
    db 00h, 0FFh, 90h, 0FCh, 01h, 00h, 00h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 83h, 0C4h, 0Ch, 0C3h
    db 0B8h, 05h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_001fafe0@@YAXXZ ENDP

; ghidra: FUN_005fb270  retail @ 0x001FB270 size 435
public ?d_001fb270@@YAXXZ
?d_001fb270@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 56h, 8Bh, 0F9h, 0E8h, 42h, 92h, 0E0h, 0FFh, 56h
    db 8Dh, 4Fh, 20h, 0E8h, 24h, 0EBh, 0E2h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 10h, 84h
    db 0C0h, 0Fh, 85h, 86h, 01h, 00h, 00h, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h, 08h, 88h
    db 44h, 24h, 09h, 8Dh, 44h, 24h, 08h, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 57h, 2Ch
    db 85h, 0D2h, 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh, 44h, 24h, 10h, 88h, 4Ch, 24h, 10h, 50h
    db 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 0Bh
    db 8Bh, 47h, 2Ch, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh, 57h, 30h, 85h, 0D2h
    db 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh, 44h, 24h, 10h, 88h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh
    db 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 0Bh, 8Bh, 47h
    db 30h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh, 57h, 34h, 85h, 0D2h, 8Bh, 16h
    db 0Fh, 95h, 0C1h, 8Dh, 44h, 24h, 10h, 88h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 92h
    db 8Ch, 00h, 00h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 0Bh, 8Bh, 47h, 34h, 8Bh
    db 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh, 57h, 38h, 85h, 0D2h, 8Bh, 16h, 0Fh, 95h
    db 0C1h, 8Dh, 44h, 24h, 10h, 88h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h
    db 00h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 0Bh, 8Bh, 47h, 38h, 8Bh, 16h, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh, 57h, 3Ch, 85h, 0D2h, 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh
    db 44h, 24h, 10h, 88h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h
    db 8Ah, 44h, 24h, 10h, 84h, 0C0h, 74h, 0Bh, 8Bh, 47h, 3Ch, 8Bh, 16h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 30h, 8Bh, 57h, 40h, 85h, 0D2h, 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh, 44h, 24h
    db 10h, 88h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Ah, 44h
    db 24h, 10h, 84h, 0C0h, 74h, 0Bh, 8Bh, 47h, 40h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 30h, 8Bh, 57h, 44h, 85h, 0D2h, 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh, 44h, 24h, 10h, 88h
    db 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Ah, 44h, 24h, 10h
    db 84h, 0C0h, 74h, 0Bh, 8Bh, 47h, 44h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 30h, 8Bh
    db 57h, 48h, 85h, 0D2h, 8Bh, 16h, 0Fh, 95h, 0C1h, 8Dh, 44h, 24h, 10h, 88h, 4Ch, 24h
    db 10h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h
    db 74h, 0Bh, 8Bh, 47h, 48h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 30h, 5Fh, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_001fb270@@YAXXZ ENDP

; ghidra: FUN_005fb490  retail @ 0x001FB490 size 17
public ?d_001fb490@@YAXXZ
?d_001fb490@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 73h, 0A9h, 0E1h, 0FFh, 8Dh, 4Eh, 20h, 5Eh, 0E9h, 0BAh, 2Ah, 0E3h
    db 0FFh
?d_001fb490@@YAXXZ ENDP

; ghidra: FUN_005fb550  retail @ 0x001FB550 size 15
public ?d_001fb550@@YAXXZ
?d_001fb550@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 6Ah, 01h, 50h, 83h, 0C1h, 0E0h, 0E8h, 7Ch, 0A2h, 0E1h, 0FFh, 0C3h
?d_001fb550@@YAXXZ ENDP

; ghidra: FUN_005fb580  retail @ 0x001FB580 size 16
public ?d_001fb580@@YAXXZ
?d_001fb580@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 0C0h, 35h, 0E3h, 0FFh, 0C3h
?d_001fb580@@YAXXZ ENDP

; ghidra: FUN_005fb5b0  retail @ 0x001FB5B0 size 16
public ?d_001fb5b0@@YAXXZ
?d_001fb5b0@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 61h, 2Dh, 0E3h, 0FFh, 0C3h
?d_001fb5b0@@YAXXZ ENDP

; ghidra: FUN_005fb930  retail @ 0x001FB930 size 233
public ?d_001fb930@@YAXXZ
?d_001fb930@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 0F8h, 8Dh, 4Eh, 0F8h, 0FFh, 10h, 84h, 0C0h, 0Fh, 84h, 0D2h
    db 00h, 00h, 00h, 8Bh, 54h, 24h, 08h, 8Bh, 4Ah, 10h, 8Bh, 46h, 0DCh, 57h, 49h, 0BFh
    db 01h, 00h, 00h, 00h, 0D3h, 0E7h, 85h, 78h, 74h, 0Fh, 84h, 0B5h, 00h, 00h, 00h, 0D9h
    db 42h, 50h, 0D8h, 58h, 78h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Bh, 0A4h, 00h, 00h, 00h
    db 8Bh, 7Eh, 0E0h, 8Bh, 8Fh, 00h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 20h, 83h, 0F8h
    db 03h, 75h, 26h, 8Bh, 4Eh, 10h, 85h, 0C9h, 0Fh, 84h, 86h, 00h, 00h, 00h, 0E8h, 0F9h
    db 0DDh, 0E0h, 0FFh, 85h, 0C0h, 75h, 7Dh, 8Bh, 4Eh, 10h, 8Dh, 47h, 38h, 50h, 57h, 0E8h
    db 0A2h, 4Dh, 0E4h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h, 83h, 0F8h, 02h, 75h, 22h, 8Bh, 4Eh
    db 0Ch, 85h, 0C9h, 74h, 5Fh, 0E8h, 0D2h, 0DDh, 0E0h, 0FFh, 85h, 0C0h, 75h, 56h, 8Dh, 4Fh
    db 38h, 51h, 8Bh, 4Eh, 0Ch, 57h, 0E8h, 7Bh, 4Dh, 0E4h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
    db 83h, 0F8h, 01h, 75h, 22h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 38h, 0E8h, 0ABh, 0DDh, 0E0h
    db 0FFh, 85h, 0C0h, 75h, 2Fh, 8Bh, 4Eh, 08h, 8Dh, 57h, 38h, 52h, 57h, 0E8h, 54h, 4Dh
    db 0E4h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h, 8Bh, 4Eh, 04h, 85h, 0C9h, 74h, 16h, 0E8h, 89h
    db 0DDh, 0E0h, 0FFh, 85h, 0C0h, 75h, 0Dh, 8Bh, 4Eh, 04h, 8Dh, 47h, 38h, 50h, 57h, 0E8h
    db 32h, 4Dh, 0E4h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_001fb930@@YAXXZ ENDP

; ghidra: FUN_005fba60  retail @ 0x001FBA60 size 208
public ?d_001fba60@@YAXXZ
?d_001fba60@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 8Dh, 4Eh, 10h, 0FFh, 10h, 84h, 0C0h, 75h, 07h, 0B8h
    db 0FFh, 0FFh, 0FFh, 3Fh, 5Eh, 0C3h, 57h, 8Bh, 7Eh, 0F8h, 8Bh, 8Fh, 00h, 02h, 00h, 00h
    db 8Bh, 11h, 0FFh, 52h, 20h, 83h, 0F8h, 03h, 75h, 2Dh, 8Bh, 4Eh, 38h, 85h, 0C9h, 0Fh
    db 84h, 93h, 00h, 00h, 00h, 0E8h, 0F2h, 0DCh, 0E0h, 0FFh, 85h, 0C0h, 0Fh, 85h, 86h, 00h
    db 00h, 00h, 8Bh, 4Eh, 38h, 8Dh, 47h, 38h, 50h, 57h, 0E8h, 97h, 4Ch, 0E4h, 0FFh, 5Fh
    db 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h, 83h, 0F8h, 02h, 75h, 25h, 8Bh, 4Eh, 34h, 85h
    db 0C9h, 74h, 65h, 0E8h, 0C4h, 0DCh, 0E0h, 0FFh, 85h, 0C0h, 75h, 5Ch, 8Dh, 4Fh, 38h, 51h
    db 8Bh, 4Eh, 34h, 57h, 0E8h, 6Dh, 4Ch, 0E4h, 0FFh, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh
    db 0C3h, 83h, 0F8h, 01h, 75h, 25h, 8Bh, 4Eh, 30h, 85h, 0C9h, 74h, 3Bh, 0E8h, 9Ah, 0DCh
    db 0E0h, 0FFh, 85h, 0C0h, 75h, 32h, 8Bh, 4Eh, 30h, 8Dh, 57h, 38h, 52h, 57h, 0E8h, 43h
    db 4Ch, 0E4h, 0FFh, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h, 8Bh, 4Eh, 2Ch, 85h, 0C9h
    db 74h, 16h, 0E8h, 75h, 0DCh, 0E0h, 0FFh, 85h, 0C0h, 75h, 0Dh, 8Bh, 4Eh, 2Ch, 8Dh, 47h
    db 38h, 50h, 57h, 0E8h, 1Eh, 4Ch, 0E4h, 0FFh, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_001fba60@@YAXXZ ENDP

; ghidra: FUN_005fbc40  retail @ 0x001FBC40 size 17
public ?d_001fbc40@@YAXXZ
?d_001fbc40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 56h, 48h, 0E4h, 0FFh, 8Dh, 4Eh, 20h, 5Eh, 0E9h, 0Ah, 23h, 0E3h
    db 0FFh
?d_001fbc40@@YAXXZ ENDP

; ghidra: FUN_005fbf70  retail @ 0x001FBF70 size 16
public ?d_001fbf70@@YAXXZ
?d_001fbf70@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 0D0h, 2Bh, 0E3h, 0FFh, 0C3h
?d_001fbf70@@YAXXZ ENDP

; ghidra: FUN_005fbfa0  retail @ 0x001FBFA0 size 16
public ?d_001fbfa0@@YAXXZ
?d_001fbfa0@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 71h, 23h, 0E3h, 0FFh, 0C3h
?d_001fbfa0@@YAXXZ ENDP

; ghidra: FUN_005fbfc0  retail @ 0x001FBFC0 size 39
public ?d_001fbfc0@@YAXXZ
?d_001fbfc0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 40h, 3Fh, 0Ah, 01h, 0C7h, 41h, 28h, 3Ch, 3Fh, 0Ah, 01h, 0C7h, 41h
    db 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh
    db 09h, 01h, 0E9h, 6Ch, 0BCh, 0E4h, 0FFh
?d_001fbfc0@@YAXXZ ENDP

; ghidra: FUN_005fbff0  retail @ 0x001FBFF0 size 109
public ?d_001fbff0@@YAXXZ
?d_001fbff0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 8Bh, 44h, 24h, 1Ch, 8Bh, 11h, 23h, 10h, 53h, 8Bh, 59h, 0Ch, 55h
    db 8Bh, 69h, 10h, 56h, 8Bh, 71h, 04h, 57h, 8Bh, 79h, 08h, 8Bh, 49h, 14h, 89h, 54h
    db 24h, 10h, 23h, 70h, 04h, 23h, 78h, 08h, 8Bh, 50h, 14h, 89h, 7Ch, 24h, 18h, 23h
    db 58h, 0Ch, 89h, 74h, 24h, 14h, 23h, 68h, 10h, 5Fh, 5Eh, 89h, 6Ch, 24h, 18h, 23h
    db 0CAh, 5Dh, 89h, 5Ch, 24h, 10h, 89h, 4Ch, 24h, 18h, 33h, 0C0h, 5Bh, 8Dh, 49h, 00h
    db 8Bh, 0Ch, 84h, 85h, 0C9h, 75h, 0Eh, 40h, 83h, 0F8h, 06h, 72h, 0F3h, 32h, 0C0h, 83h
    db 0C4h, 18h, 0C2h, 04h, 00h, 0B0h, 01h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_001fbff0@@YAXXZ ENDP

; ghidra: FUN_005fc0b0  retail @ 0x001FC0B0 size 353
public ?d_001fc0b0@@YAXXZ
?d_001fc0b0@@YAXXZ PROC
    db 83h, 0ECh, 3Ch, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 60h, 85h, 0C0h, 8Bh, 5Eh, 0DCh, 57h
    db 7Eh, 39h, 8Bh, 7Ch, 24h, 4Ch, 8Dh, 47h, 04h, 50h, 8Dh, 4Eh, 08h, 0E8h, 0AAh, 0A0h
    db 0E0h, 0FFh, 8Bh, 4Fh, 50h, 89h, 4Eh, 54h, 8Bh, 57h, 54h, 89h, 56h, 58h, 8Ah, 47h
    db 58h, 88h, 46h, 5Ch, 8Bh, 4Eh, 0E0h, 6Ah, 01h, 51h, 8Dh, 4Eh, 0D8h, 0E8h, 0E8h, 96h
    db 0E1h, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 3Ch, 0C2h, 04h, 00h, 8Bh, 56h, 0F8h, 8Dh, 4Eh
    db 0F8h, 0FFh, 12h, 84h, 0C0h, 75h, 0Eh, 8Bh, 46h, 0DCh, 8Ah, 48h, 70h, 84h, 0C9h, 0Fh
    db 84h, 0F3h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 4Ch, 8Bh, 46h, 0E0h, 51h, 50h, 8Dh, 8Bh
    db 84h, 00h, 00h, 00h, 0E8h, 0AFh, 96h, 0E3h, 0FFh, 84h, 0C0h, 0Fh, 84h, 0D7h, 00h, 00h
    db 00h, 8Bh, 4Eh, 0E0h, 0F7h, 81h, 98h, 00h, 00h, 00h, 00h, 00h, 20h, 00h, 0Fh, 85h
    db 0C4h, 00h, 00h, 00h, 8Ah, 43h, 71h, 84h, 0C0h, 75h, 0Fh, 6Ah, 02h, 0E8h, 52h, 55h
    db 0E0h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0AEh, 00h, 00h, 00h, 33h, 0C0h, 89h, 44h, 24h, 18h
    db 33h, 0D2h, 89h, 44h, 24h, 1Ch, 89h, 54h, 24h, 30h, 89h, 44h, 24h, 20h, 89h, 54h
    db 24h, 34h, 89h, 44h, 24h, 24h, 89h, 44h, 24h, 28h, 89h, 54h, 24h, 38h, 89h, 44h
    db 24h, 2Ch, 89h, 54h, 24h, 3Ch, 8Dh, 44h, 24h, 18h, 89h, 54h, 24h, 40h, 50h, 8Dh
    db 4Eh, 0F8h, 8Dh, 44h, 24h, 34h, 89h, 54h, 24h, 48h, 8Bh, 11h, 50h, 0FFh, 52h, 28h
    db 8Bh, 7Eh, 0E0h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 8Fh, 24h, 02h, 00h, 00h, 0E8h, 76h
    db 6Bh, 0E0h, 0FFh, 84h, 0C0h, 75h, 51h, 8Bh, 0CFh, 0E8h, 66h, 46h, 0E2h, 0FFh, 8Dh, 54h
    db 24h, 18h, 52h, 8Dh, 88h, 8Ch, 00h, 00h, 00h, 0E8h, 5Bh, 6Bh, 0E0h, 0FFh, 84h, 0C0h
    db 75h, 36h, 8Bh, 83h, 0B0h, 00h, 00h, 00h, 85h, 0C0h, 74h, 2Ch, 8Dh, 44h, 24h, 0Ch
    db 50h, 8Dh, 4Bh, 78h, 51h, 8Bh, 4Eh, 0E0h, 0E8h, 47h, 35h, 0E3h, 0FFh, 8Bh, 46h, 0E0h
    db 8Bh, 8Bh, 0B0h, 00h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 50h, 51h, 8Bh, 0Dh, 38h
    db 0F7h, 2Eh, 01h, 0E8h, 56h, 9Ch, 0E3h, 0FFh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 3Ch, 0C2h, 04h
    db 00h
?d_001fc0b0@@YAXXZ ENDP

; ghidra: FUN_005fc280  retail @ 0x001FC280 size 66
public ?d_001fc280@@YAXXZ
?d_001fc280@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 0C1h, 0C7h, 40h, 04h, 00h, 00h, 00h, 00h, 0C7h, 00h, 0B4h
    db 40h, 0Ah, 01h, 56h, 8Bh, 32h, 8Dh, 48h, 08h, 89h, 31h, 8Bh, 72h, 04h, 89h, 71h
    db 04h, 8Bh, 52h, 08h, 89h, 51h, 08h, 8Bh, 54h, 24h, 0Ch, 8Bh, 32h, 8Dh, 48h, 14h
    db 89h, 31h, 8Bh, 72h, 04h, 89h, 71h, 04h, 8Bh, 52h, 08h, 89h, 51h, 08h, 5Eh, 0C2h
    db 08h, 00h
?d_001fc280@@YAXXZ ENDP

; ghidra: FUN_005fc330  retail @ 0x001FC330 size 56
public ?d_001fc330@@YAXXZ
?d_001fc330@@YAXXZ PROC
    db 8Dh, 41h, 04h, 0C7h, 01h, 0CCh, 41h, 0Ah, 01h, 0C7h, 41h, 10h, 08h, 41h, 0Ah, 01h
    db 0C7h, 41h, 14h, 0F8h, 40h, 0Ah, 01h, 0C7h, 00h, 0C4h, 40h, 0Ah, 01h, 0C7h, 40h, 10h
    db 0ACh, 0CBh, 09h, 01h, 0C7h, 00h, 5Ch, 0CBh, 09h, 01h, 0C7h, 40h, 0Ch, 98h, 0CAh, 09h
    db 01h, 8Bh, 0C8h, 0E9h, 0EBh, 0B8h, 0E4h, 0FFh
?d_001fc330@@YAXXZ ENDP

; ghidra: FUN_005fc400  retail @ 0x001FC400 size 26
public ?d_001fc400@@YAXXZ
?d_001fc400@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 18h, 84h, 0C0h, 8Bh, 0CEh, 74h, 06h, 8Bh, 16h
    db 5Eh, 0FFh, 62h, 20h, 8Bh, 06h, 5Eh, 0FFh, 60h, 1Ch
?d_001fc400@@YAXXZ ENDP

; ghidra: FUN_005fc440  retail @ 0x001FC440 size 34
public ?d_001fc440@@YAXXZ
?d_001fc440@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0F8h, 0FFh, 74h, 05h, 83h, 0F8h, 01h, 75h, 11h, 8Bh, 51h
    db 40h, 85h, 0D2h, 7Dh, 07h, 0C7h, 41h, 40h, 00h, 00h, 00h, 00h, 01h, 41h, 40h, 0C2h
    db 04h, 00h
?d_001fc440@@YAXXZ ENDP

; ghidra: FUN_005fc6b0  retail @ 0x001FC6B0 size 220
public ?d_001fc6b0@@YAXXZ
?d_001fc6b0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 83h, 0B3h, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0E0h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 0Dh
    db 68h, 0D6h, 2Eh, 01h, 8Bh, 56h, 44h, 8Bh, 01h, 52h, 0FFh, 50h, 4Ch, 8Bh, 4Eh, 28h
    db 83h, 0F9h, 03h, 8Bh, 56h, 08h, 8Bh, 46h, 0Ch, 0Fh, 87h, 83h, 00h, 00h, 00h, 0FFh
    db 24h, 8Dh, 8Ch, 0C7h, 5Fh, 00h, 8Dh, 4Ah, 1Ch, 83h, 39h, 00h, 74h, 74h, 8Bh, 40h
    db 74h, 50h, 51h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 7Ah, 0C7h, 0E0h, 0FFh, 8Bh, 0Dh, 68h, 0D6h
    db 2Eh, 01h, 8Bh, 01h, 8Dh, 54h, 24h, 04h, 52h, 0C7h, 84h, 24h, 0F0h, 00h, 00h, 00h
    db 00h, 00h, 00h, 00h, 0FFh, 50h, 44h, 8Dh, 4Ch, 24h, 04h, 0EBh, 35h, 8Dh, 4Ah, 24h
    db 83h, 39h, 00h, 74h, 3Dh, 8Bh, 40h, 74h, 50h, 51h, 8Dh, 4Ch, 24h, 7Ch, 0E8h, 43h
    db 0C7h, 0E0h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 8Dh, 54h, 24h, 74h, 52h
    db 0C7h, 84h, 24h, 0F0h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 0FFh, 50h, 44h, 8Dh, 4Ch
    db 24h, 74h, 0C7h, 84h, 24h, 0ECh, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0C3h, 0A7h
    db 0E2h, 0FFh, 8Bh, 8Ch, 24h, 0E4h, 00h, 00h, 00h, 0C6h, 46h, 48h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0ECh, 00h, 00h, 00h, 0C3h
?d_001fc6b0@@YAXXZ ENDP

; ghidra: FUN_005fc950  retail @ 0x001FC950 size 239
public ?d_001fc950@@YAXXZ
?d_001fc950@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 56h, 8Bh, 74h, 24h, 14h, 57h, 56h, 8Bh, 0F9h, 0E8h, 51h, 97h
    db 0E1h, 0FFh, 8Bh, 06h, 8Dh, 4Ch, 24h, 18h, 51h, 0B3h, 03h, 8Bh, 0CEh, 0C6h, 44h, 24h
    db 1Ch, 01h, 88h, 5Ch, 24h, 1Dh, 0FFh, 50h, 28h, 38h, 5Ch, 24h, 19h, 72h, 08h, 56h
    db 8Bh, 0CFh, 0E8h, 3Ah, 7Bh, 0E0h, 0FFh, 8Bh, 57h, 24h, 8Bh, 06h, 8Dh, 4Ch, 24h, 0Ch
    db 51h, 8Bh, 0CEh, 89h, 54h, 24h, 10h, 0FFh, 50h, 78h, 8Bh, 47h, 28h, 8Bh, 54h, 24h
    db 0Ch, 8Dh, 5Fh, 28h, 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 10h, 89h, 57h, 24h, 8Bh
    db 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 4Ch, 24h, 10h, 89h, 0Bh, 8Bh, 16h, 8Dh
    db 47h, 2Ch, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 47h, 38h
    db 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Dh, 4Fh, 20h, 51h, 56h, 0E8h, 0D4h, 0FFh, 0E0h, 0FFh
    db 8Bh, 16h, 83h, 0C4h, 08h, 8Dh, 47h, 3Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 0Dh
    db 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 47h, 40h, 50h, 56h, 0FFh, 92h, 48h, 01h, 00h
    db 00h, 8Bh, 16h, 8Dh, 47h, 44h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 80h
    db 7Ch, 24h, 19h, 02h, 72h, 20h, 8Bh, 16h, 6Ah, 04h, 53h, 8Bh, 0CEh, 0FFh, 52h, 24h
    db 8Bh, 06h, 8Dh, 4Fh, 30h, 51h, 8Bh, 0CEh, 0FFh, 50h, 6Ch, 8Bh, 16h, 83h, 0C7h, 34h
    db 57h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_001fc950@@YAXXZ ENDP

; ghidra: FUN_005fca90  retail @ 0x001FCA90 size 151
public ?d_001fca90@@YAXXZ
?d_001fca90@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 43h, 24h, 85h, 0C0h, 75h, 04h, 32h, 0C0h, 5Bh, 0C3h, 8Bh, 0Dh
    db 98h, 08h, 2Fh, 01h, 57h, 50h, 0E8h, 0A8h, 27h, 0E2h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h
    db 71h, 8Bh, 0CFh, 0E8h, 6Ch, 3Dh, 0E2h, 0FFh, 85h, 0C0h, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h
    db 8Bh, 49h, 0Ch, 74h, 5Dh, 85h, 0C9h, 74h, 59h, 3Bh, 0C1h, 75h, 55h, 8Bh, 0Dh, 8Ch
    db 14h, 2Fh, 01h, 8Bh, 11h, 56h, 0FFh, 92h, 0E8h, 00h, 00h, 00h, 8Bh, 0Dh, 0ECh, 0D5h
    db 2Eh, 01h, 8Bh, 01h, 68h, 0EAh, 03h, 00h, 00h, 0FFh, 50h, 34h, 8Bh, 0F0h, 6Ah, 01h
    db 8Bh, 0CEh, 0E8h, 0B4h, 67h, 0E0h, 0FFh, 8Bh, 4Bh, 24h, 51h, 8Bh, 0CEh, 0E8h, 0EAh, 0F1h
    db 0E2h, 0FFh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 28h, 85h, 0C0h, 5Eh, 74h, 0Fh, 8Bh, 0Dh
    db 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 50h, 0FFh, 92h, 0E0h, 00h, 00h, 00h, 5Fh, 0B0h, 01h
    db 5Bh, 0C3h, 5Fh, 32h, 0C0h, 5Bh, 0C3h
?d_001fca90@@YAXXZ ENDP

; ghidra: FUN_005fcce0  retail @ 0x001FCCE0 size 72
public ?d_001fcce0@@YAXXZ
?d_001fcce0@@YAXXZ PROC
    db 83h, 79h, 2Ch, 01h, 74h, 05h, 32h, 0C0h, 0C2h, 04h, 00h, 56h, 8Bh, 74h, 24h, 08h
    db 85h, 0F6h, 74h, 28h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 0B4h, 55h, 0E0h, 0FFh, 0F6h, 80h, 0C8h, 00h, 00h, 00h, 04h, 75h, 0Ch
    db 8Bh, 0CEh, 0E8h, 7Ah, 0D6h, 0E3h, 0FFh, 83h, 0F8h, 01h, 74h, 06h, 32h, 0C0h, 5Eh, 0C2h
    db 04h, 00h, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_001fcce0@@YAXXZ ENDP

; ghidra: FUN_005fcd40  retail @ 0x001FCD40 size 203
public ?d_001fcd40@@YAXXZ
?d_001fcd40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 4Bh, 0B4h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 9Ch, 00h, 00h, 00h, 8Bh, 84h, 24h, 0B0h, 00h
    db 00h, 00h, 56h, 50h, 8Bh, 0F1h, 6Ah, 34h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 33h, 41h, 0E3h
    db 0FFh, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 04h, 89h, 4Ch
    db 24h, 18h, 50h, 8Bh, 0CEh, 0C7h, 84h, 24h, 0ACh, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0FFh, 12h, 8Bh, 74h, 24h, 24h, 85h, 0F6h, 0C7h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 74h, 4Eh, 8Bh, 4Ch, 24h, 2Ch, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 21h, 56h, 0E8h, 0E2h, 50h, 68h, 00h, 83h, 0C4h
    db 04h, 5Eh, 8Bh, 8Ch, 24h, 9Ch, 00h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h, 50h, 56h, 0E8h, 00h, 18h, 63h, 00h
    db 83h, 0C4h, 08h, 8Bh, 8Ch, 24h, 0A0h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h
?d_001fcd40@@YAXXZ ENDP

; ghidra: FUN_005fd550  retail @ 0x001FD550 size 63
public ?d_001fd550@@YAXXZ
?d_001fd550@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 28h, 84h, 0C0h, 74h, 31h, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 52h, 18h, 84h, 0C0h, 75h, 26h, 8Bh, 0CEh, 0E8h, 0FCh, 0B7h, 0E4h, 0FFh, 6Ah, 00h
    db 8Bh, 0CEh, 0E8h, 55h, 0E9h, 0E2h, 0FFh, 0C6h, 46h, 30h, 00h, 0C7h, 46h, 34h, 00h, 00h
    db 00h, 00h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 89h, 4Eh, 3Ch, 5Eh, 0C3h
?d_001fd550@@YAXXZ ENDP

; ghidra: FUN_005fd5a0  retail @ 0x001FD5A0 size 60
public ?d_001fd5a0@@YAXXZ
?d_001fd5a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 28h, 84h, 0C0h, 74h, 2Eh, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 52h, 18h, 84h, 0C0h, 74h, 23h, 8Bh, 0CEh, 0E8h, 0ACh, 0B7h, 0E4h, 0FFh, 6Ah, 02h
    db 8Bh, 0CEh, 0E8h, 05h, 0E9h, 0E2h, 0FFh, 33h, 0C0h, 88h, 46h, 30h, 89h, 46h, 34h, 0A1h
    db 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 89h, 4Eh, 3Ch, 5Eh, 0C3h
?d_001fd5a0@@YAXXZ ENDP

; ghidra: FUN_005fd5f0  retail @ 0x001FD5F0 size 146
public ?d_001fd5f0@@YAXXZ
?d_001fd5f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 2Ch, 57h, 0BFh, 01h, 00h, 00h, 00h, 3Bh, 0C7h, 74h, 7Fh
    db 53h, 55h, 0E8h, 63h, 0B7h, 0E4h, 0FFh, 8Bh, 6Eh, 0Ch, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh
    db 48h, 0Ch, 55h, 0E8h, 7Dh, 67h, 0E1h, 0FFh, 6Ah, 09h, 8Bh, 0CDh, 89h, 7Eh, 2Ch, 0E8h
    db 0CAh, 0EBh, 0E0h, 0FFh, 8Bh, 76h, 08h, 8Bh, 7Eh, 28h, 3Bh, 7Eh, 2Ch, 8Dh, 9Dh, 0ACh
    db 00h, 00h, 00h, 74h, 14h, 6Ah, 00h, 57h, 8Bh, 0CBh, 0E8h, 81h, 23h, 68h, 00h, 8Bh
    db 46h, 2Ch, 83h, 0C7h, 04h, 3Bh, 0F8h, 75h, 0ECh, 8Bh, 7Eh, 34h, 3Bh, 7Eh, 38h, 74h
    db 14h, 6Ah, 01h, 57h, 8Bh, 0CBh, 0E8h, 65h, 23h, 68h, 00h, 8Bh, 46h, 38h, 83h, 0C7h
    db 04h, 3Bh, 0F8h, 75h, 0ECh, 6Ah, 01h, 8Bh, 0CDh, 0E8h, 0B2h, 35h, 0E2h, 0FFh, 8Bh, 0Dh
    db 14h, 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 55h, 0E8h, 9Eh, 0E1h, 0E0h, 0FFh, 5Dh, 5Bh, 5Fh
    db 5Eh, 0C3h
?d_001fd5f0@@YAXXZ ENDP

; ghidra: FUN_005fd6b0  retail @ 0x001FD6B0 size 163
public ?d_001fd6b0@@YAXXZ
?d_001fd6b0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 2Ch, 57h, 0BFh, 02h, 00h, 00h, 00h, 3Bh, 0C7h, 75h, 0Ch
    db 8Ah, 44h, 24h, 0Ch, 84h, 0C0h, 0Fh, 84h, 82h, 00h, 00h, 00h, 53h, 55h, 8Bh, 0CEh
    db 0E8h, 95h, 0B6h, 0E4h, 0FFh, 8Bh, 6Eh, 0Ch, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch
    db 55h, 0E8h, 0AFh, 66h, 0E1h, 0FFh, 6Ah, 09h, 8Bh, 0CDh, 89h, 7Eh, 2Ch, 0E8h, 1Ah, 0E4h
    db 0E2h, 0FFh, 8Bh, 76h, 08h, 8Bh, 7Eh, 28h, 3Bh, 7Eh, 2Ch, 8Dh, 9Dh, 0ACh, 00h, 00h
    db 00h, 74h, 14h, 6Ah, 01h, 57h, 8Bh, 0CBh, 0E8h, 0B3h, 22h, 68h, 00h, 8Bh, 46h, 2Ch
    db 83h, 0C7h, 04h, 3Bh, 0F8h, 75h, 0ECh, 8Bh, 7Eh, 34h, 3Bh, 7Eh, 38h, 74h, 15h, 90h
    db 6Ah, 00h, 57h, 8Bh, 0CBh, 0E8h, 96h, 22h, 68h, 00h, 8Bh, 46h, 38h, 83h, 0C7h, 04h
    db 3Bh, 0F8h, 75h, 0ECh, 6Ah, 01h, 8Bh, 0CDh, 0E8h, 0E3h, 34h, 0E2h, 0FFh, 8Bh, 0Dh, 14h
    db 0F2h, 2Eh, 01h, 8Bh, 49h, 0Ch, 55h, 0E8h, 0CFh, 0E0h, 0E0h, 0FFh, 5Dh, 5Bh, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_001fd6b0@@YAXXZ ENDP

; ghidra: FUN_005fe160  retail @ 0x001FE160 size 18
public ?d_001fe160@@YAXXZ
?d_001fe160@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0A3h, 7Ch, 0E1h, 0FFh, 8Bh, 46h, 20h, 8Dh, 4Eh, 20h, 5Eh, 0FFh
    db 60h, 08h
?d_001fe160@@YAXXZ ENDP

; ghidra: FUN_005fe380  retail @ 0x001FE380 size 182
public ?d_001fe380@@YAXXZ
?d_001fe380@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0B6h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 18h, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 0Ch, 0E8h, 36h, 8Dh, 0E1h, 0FFh, 0C7h, 46h
    db 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh, 09h, 01h, 83h, 0C9h, 0FFh, 33h
    db 0C0h, 89h, 46h, 14h, 89h, 4Eh, 18h, 89h, 4Eh, 1Ch, 0C7h, 46h, 20h, 98h, 42h, 0Ah
    db 01h, 8Bh, 56h, 08h, 6Ah, 01h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 18h, 0C7h, 06h, 0F4h
    db 46h, 0Ah, 01h, 0C7h, 46h, 0Ch, 30h, 46h, 0Ah, 01h, 0C7h, 46h, 10h, 24h, 46h, 0Ah
    db 01h, 0C7h, 46h, 20h, 0E0h, 45h, 0Ah, 01h, 0C7h, 46h, 24h, 01h, 00h, 00h, 00h, 89h
    db 46h, 2Ch, 88h, 46h, 34h, 88h, 46h, 35h, 88h, 46h, 36h, 89h, 46h, 38h, 88h, 46h
    db 30h, 89h, 46h, 28h, 88h, 46h, 31h, 88h, 46h, 32h, 88h, 46h, 33h, 0E8h, 0B8h, 73h
    db 0E1h, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_001fe380@@YAXXZ ENDP

; ghidra: FUN_005fe5a0  retail @ 0x001FE5A0 size 70
public ?d_001fe5a0@@YAXXZ
?d_001fe5a0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Bh, 46h, 0E4h, 0D9h, 40h, 24h, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 80h, 3Fh, 0D8h, 0Dh, 44h, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 04h, 0D9h, 05h
    db 34h, 53h, 07h, 01h, 0D8h, 5Ch, 24h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 8Dh, 44h, 24h
    db 08h, 74h, 04h, 8Dh, 44h, 24h, 04h, 0D9h, 00h, 0E8h, 5Ah, 88h, 7Fh, 00h, 89h, 46h
    db 0Ch, 5Eh, 83h, 0C4h, 08h, 0C3h
?d_001fe5a0@@YAXXZ ENDP

; ghidra: FUN_005fe600  retail @ 0x001FE600 size 28
public ?d_001fe600@@YAXXZ
?d_001fe600@@YAXXZ PROC
    db 8Bh, 41h, 0E4h, 83h, 0C0h, 14h, 8Bh, 00h, 85h, 0C0h, 74h, 0Ah, 66h, 83h, 78h, 04h
    db 00h, 74h, 03h, 33h, 0C0h, 0C3h, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_001fe600@@YAXXZ ENDP

; ghidra: FUN_005fe670  retail @ 0x001FE670 size 71
public ?d_001fe670@@YAXXZ
?d_001fe670@@YAXXZ PROC
    db 51h, 8Bh, 41h, 0E8h, 85h, 0C0h, 74h, 08h, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 75h, 06h
    db 32h, 0C0h, 59h, 0C2h, 04h, 00h, 8Bh, 11h, 56h, 8Bh, 70h, 4Ch, 50h, 0FFh, 52h, 2Ch
    db 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 94h, 93h, 35h, 01h, 0D9h, 5Ch, 24h, 14h
    db 83h, 0C4h, 08h, 0D9h, 44h, 24h, 0Ch, 0DBh, 5Ch, 24h, 04h, 3Bh, 74h, 24h, 04h, 1Bh
    db 0C0h, 40h, 5Eh, 59h, 0C2h, 04h, 00h
?d_001fe670@@YAXXZ ENDP

; ghidra: FUN_005fe6d0  retail @ 0x001FE6D0 size 86
public ?d_001fe6d0@@YAXXZ
?d_001fe6d0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 08h, 85h, 0C9h, 74h, 44h, 56h, 0E8h, 41h
    db 21h, 0E2h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 74h, 37h, 8Bh, 47h, 20h, 8Dh, 4Fh, 20h, 56h
    db 0FFh, 50h, 2Ch, 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 94h, 93h, 35h, 01h, 0D9h
    db 5Ch, 24h, 10h, 83h, 0C4h, 08h, 0D9h, 44h, 24h, 08h, 0DBh, 5Ch, 24h, 0Ch, 8Bh, 44h
    db 24h, 0Ch, 6Ah, 01h, 50h, 8Dh, 4Eh, 48h, 89h, 47h, 38h, 0E8h, 74h, 31h, 0E4h, 0FFh
    db 5Eh, 5Fh, 83h, 0C4h, 08h, 0C3h
?d_001fe6d0@@YAXXZ ENDP

; ghidra: FUN_005fe8a0  retail @ 0x001FE8A0 size 86
public ?d_001fe8a0@@YAXXZ
?d_001fe8a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 0E8h, 83h, 0C0h, 04h, 8Bh, 00h, 85h, 0C0h, 75h, 04h, 33h
    db 0C9h, 0EBh, 0Eh, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0FCh, 39h, 0E0h, 0FFh, 8Bh
    db 0C8h, 8Bh, 44h, 24h, 08h, 6Ah, 0FFh, 50h, 0E8h, 0BDh, 0F1h, 0E0h, 0FFh, 8Bh, 4Eh, 0E8h
    db 8Bh, 89h, 00h, 02h, 00h, 00h, 8Bh, 11h, 8Bh, 76h, 0E4h, 89h, 44h, 24h, 08h, 0DBh
    db 44h, 24h, 08h, 0D9h, 5Ch, 24h, 08h, 0FFh, 52h, 20h, 0D9h, 44h, 24h, 08h, 0D8h, 4Ch
    db 86h, 30h, 5Eh, 0C2h, 04h, 00h
?d_001fe8a0@@YAXXZ ENDP

; ghidra: FUN_005fe910  retail @ 0x001FE910 size 76
public ?d_001fe910@@YAXXZ
?d_001fe910@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 8Bh, 48h, 78h, 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 0E8h, 2Eh, 09h, 0E2h, 0FFh, 85h, 0C0h, 74h, 12h, 8Bh, 0C8h, 0E8h, 6Fh, 0F5h, 0E0h, 0FFh
    db 85h, 0C0h, 74h, 07h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 14h, 8Bh, 0Dh, 68h, 0D6h, 2Eh
    db 01h, 85h, 0C9h, 74h, 15h, 8Bh, 46h, 24h, 83h, 0F8h, 05h, 72h, 0Dh, 8Bh, 11h, 50h
    db 0FFh, 52h, 4Ch, 0C7h, 46h, 24h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_001fe910@@YAXXZ ENDP

; ghidra: FUN_005fe970  retail @ 0x001FE970 size 339
_TEXT ENDS
_TEXT$d005fe970 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005FE970 size 339
public ?d_001fe970@@YAXXZ
?d_001fe970@@YAXXZ PROC
    db 083h, 0ECh, 008h, 055h, 056h, 08Bh, 0F1h, 08Bh, 06Eh, 008h, 08Bh, 046h, 004h, 057h, 08Bh, 0BDh
    db 000h, 002h, 000h, 000h, 085h, 0FFh, 089h, 044h, 024h, 010h, 00Fh, 084h, 02Ch, 001h, 000h, 000h
    db 0F6h, 085h, 044h, 003h, 000h, 000h, 001h, 074h, 00Bh, 08Ah, 048h, 02Ch, 084h, 0C9h, 00Fh, 084h
    db 018h, 001h, 000h, 000h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 010h, 0D9h, 05Ch, 024h, 00Ch, 08Bh
    db 017h, 08Bh, 0CFh, 0FFh, 052h, 018h, 0D8h, 05Ch, 024h, 00Ch, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh
    db 085h, 0F7h, 000h, 000h, 000h, 08Bh, 046h, 008h, 050h
    call ?j_0000e6e7@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 01Dh, 08Bh, 048h, 014h, 085h, 0C9h, 074h, 016h, 08Ah, 048h
    db 024h, 084h, 0C9h, 075h, 00Fh, 08Bh, 0C8h
    call ?j_0004b015@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0CAh, 000h, 000h, 000h, 08Ah, 046h, 035h, 084h, 0C0h, 053h, 0C7h, 044h
    db 024h, 010h, 000h, 000h, 000h, 000h, 075h, 016h, 06Ah, 004h, 08Dh, 044h, 024h, 014h, 050h, 08Bh
    db 0CDh
    call ?j_000402d2@@YAXXZ
    db 084h, 0C0h, 074h, 004h, 0B3h, 001h, 0EBh, 002h, 032h, 0DBh, 08Bh, 04Ch, 024h, 014h, 08Bh, 041h
    db 014h, 085h, 0C0h, 074h, 007h, 066h, 083h, 078h, 004h, 000h, 075h, 038h, 084h, 0DBh, 00Fh, 085h
    db 087h, 000h, 000h, 000h, 08Bh, 056h, 020h, 08Dh, 07Eh, 020h, 08Bh, 0CFh, 0FFh, 052h, 014h, 084h
    db 0C0h, 075h, 078h, 0D9h, 046h, 028h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Bh, 068h, 08Bh, 007h, 06Ah, 001h, 08Bh, 0CFh, 0FFh, 050h, 004h
    db 05Bh, 05Fh, 05Eh, 05Dh, 083h, 0C4h, 008h, 0C3h, 08Bh, 04Dh, 07Ch, 051h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 074h, 009h, 0F6h, 080h, 044h, 003h, 000h, 000h, 001h, 074h, 03Bh, 0D9h, 046h, 028h
    db 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 010h, 084h, 0DBh, 075h, 00Ch, 0D9h, 046h, 028h, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Eh, 028h, 0D9h, 046h, 028h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 00Bh, 08Bh, 056h, 020h, 08Dh, 04Eh, 020h, 06Ah, 001h, 0FFh
    db 052h, 004h, 05Bh, 05Fh, 05Eh, 05Dh, 083h, 0C4h, 008h, 0C3h
?d_001fe970@@YAXXZ ENDP
_TEXT$d005fe970 ENDS
_TEXT SEGMENT

; ghidra: FUN_005feb50  retail @ 0x001FEB50 size 178
public ?d_001feb50@@YAXXZ
?d_001feb50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 0B6h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0F4h
    db 46h, 0Ah, 01h, 0C7h, 46h, 0Ch, 30h, 46h, 0Ah, 01h, 0C7h, 46h, 10h, 24h, 46h, 0Ah
    db 01h, 0C7h, 46h, 20h, 0E0h, 45h, 0Ah, 01h, 8Bh, 46h, 08h, 85h, 0C0h, 0C7h, 44h, 24h
    db 10h, 00h, 00h, 00h, 00h, 74h, 1Eh, 8Bh, 40h, 7Ch, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 50h, 0E8h, 0ADh, 06h, 0E2h, 0FFh, 85h, 0C0h, 74h, 0Bh, 6Ah, 16h, 6Ah, 08h, 8Bh, 0C8h
    db 0E8h, 51h, 59h, 0E1h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 74h, 10h, 8Bh
    db 56h, 24h, 8Bh, 01h, 52h, 0FFh, 50h, 4Ch, 0C7h, 46h, 24h, 01h, 00h, 00h, 00h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0C7h, 46h, 10h, 0ACh, 0CBh, 09h, 01h
    db 0C7h, 06h, 5Ch, 0CBh, 09h, 01h, 0C7h, 46h, 0Ch, 98h, 0CAh, 09h, 01h, 0E8h, 61h, 90h
    db 0E4h, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C3h
?d_001feb50@@YAXXZ ENDP

; ghidra: FUN_005fec30  retail @ 0x001FEC30 size 122
public ?d_001fec30@@YAXXZ
?d_001fec30@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 57h, 8Bh, 0F9h, 8Bh, 47h, 20h, 8Dh, 4Fh, 20h, 0FFh, 50h, 14h, 84h
    db 0C0h, 74h, 62h, 56h, 8Bh, 77h, 08h, 0C6h, 47h, 32h, 00h, 0F6h, 86h, 18h, 01h, 00h
    db 00h, 10h, 74h, 16h, 8Bh, 86h, 18h, 01h, 00h, 00h, 83h, 0E0h, 0EFh, 8Bh, 0CEh, 89h
    db 86h, 18h, 01h, 00h, 00h, 0E8h, 0B3h, 2Ch, 0E2h, 0FFh, 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch
    db 24h, 0Ch, 51h, 8Dh, 54h, 24h, 0Ch, 89h, 4Ch, 24h, 14h, 83h, 0C8h, 04h, 52h, 8Bh
    db 0CEh, 89h, 44h, 24h, 10h, 0E8h, 5Dh, 1Bh, 0E3h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h
    db 85h, 0C9h, 5Eh, 74h, 10h, 8Bh, 57h, 24h, 8Bh, 01h, 52h, 0FFh, 50h, 4Ch, 0C7h, 47h
    db 24h, 01h, 00h, 00h, 00h, 5Fh, 83h, 0C4h, 0Ch, 0C3h
?d_001fec30@@YAXXZ ENDP

; ghidra: FUN_005ff060  retail @ 0x001FF060 size 242
_TEXT ENDS
_TEXT$d005ff060 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005FF060 size 242
public ?d_001ff060@@YAXXZ
?d_001ff060@@YAXXZ PROC
    db 055h, 08Bh, 0E9h, 08Ah, 045h, 030h, 084h, 0C0h, 056h, 057h, 08Bh, 07Dh, 008h, 075h, 07Dh, 057h
    call ?j_0000e6e7@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 019h, 08Bh, 048h, 014h, 085h, 0C9h, 074h, 012h, 08Ah, 048h
    db 024h, 084h, 0C9h, 075h, 00Bh, 08Bh, 0C8h
    call ?j_0004b015@@YAXXZ
    db 084h, 0C0h, 075h, 057h, 08Bh, 047h, 07Ch, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 03Ch, 057h, 08Bh, 0CEh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 083h, 0F8h, 002h, 074h, 02Fh, 08Bh, 08Eh, 02Ch, 001h, 000h, 000h, 0B8h, 000h, 000h, 002h, 000h
    db 085h, 0C8h, 075h, 00Fh, 00Bh, 0C8h, 089h, 08Eh, 02Ch, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002191d@@YAXXZ
    db 06Ah, 016h, 06Ah, 008h, 08Bh, 0CEh
    call ?j_00014506@@YAXXZ
    db 05Fh, 05Eh, 0B0h, 001h, 05Dh, 0C3h, 05Fh, 05Eh, 032h, 0C0h, 05Dh, 0C3h, 08Bh, 04Fh, 07Ch, 051h
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 047h, 08Bh, 08Eh, 004h, 002h, 000h, 000h, 085h, 0C9h, 074h, 041h
    db 08Bh, 011h, 0FFh, 092h, 080h, 001h, 000h, 000h, 084h, 0C0h, 074h, 035h, 08Bh, 047h, 07Ch, 03Bh
    db 047h, 074h, 074h, 02Dh, 08Bh, 08Eh, 02Ch, 001h, 000h, 000h, 0B8h, 000h, 000h, 002h, 000h, 085h
    db 0C8h, 075h, 00Fh, 00Bh, 0C8h, 089h, 08Eh, 02Ch, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002191d@@YAXXZ
    db 06Ah, 016h, 06Ah, 008h, 08Bh, 0CEh
    call ?j_00014506@@YAXXZ
    db 0C6h, 045h, 030h, 000h, 05Fh, 05Eh, 0B0h, 001h, 05Dh, 0C3h
?d_001ff060@@YAXXZ ENDP
_TEXT$d005ff060 ENDS
_TEXT SEGMENT

; ghidra: FUN_005ff1c0  retail @ 0x001FF1C0 size 321
public ?d_001ff1c0@@YAXXZ
?d_001ff1c0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 07h, 8Bh, 5Fh, 0E4h, 8Bh, 77h, 0E8h
    db 0FFh, 50h, 14h, 84h, 0C0h, 75h, 54h, 8Bh, 43h, 14h, 85h, 0C0h, 74h, 0Bh, 66h, 83h
    db 78h, 04h, 00h, 0Fh, 85h, 0Fh, 01h, 00h, 00h, 85h, 0F6h, 0Fh, 84h, 0E4h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 1Ch, 85h, 0C9h, 0Fh, 84h, 0D8h, 00h, 00h, 00h, 8Bh, 41h, 74h
    db 39h, 46h, 7Ch, 0Fh, 85h, 0CCh, 00h, 00h, 00h, 8Bh, 76h, 74h, 39h, 71h, 78h, 0Fh
    db 85h, 0C0h, 00h, 00h, 00h, 3Bh, 0C6h, 0Fh, 84h, 0B8h, 00h, 00h, 00h, 6Ah, 16h, 6Ah
    db 08h, 0E8h, 0E0h, 52h, 0E1h, 0FFh, 0E9h, 0AAh, 00h, 00h, 00h, 0C6h, 47h, 12h, 00h, 0C7h
    db 86h, 20h, 02h, 00h, 00h, 00h, 00h, 80h, 0BFh, 8Ah, 47h, 13h, 84h, 0C0h, 74h, 29h
    db 68h, 88h, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0D3h, 32h, 0E3h, 0FFh, 84h, 0C0h, 75h, 19h
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 85h, 0C0h, 74h, 0Eh, 8Bh, 06h, 8Bh, 0CEh, 0FFh
    db 50h, 28h, 8Bh, 0C8h, 0E8h, 88h, 9Ah, 0E0h, 0FFh, 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch, 24h
    db 10h, 51h, 8Dh, 54h, 24h, 10h, 89h, 4Ch, 24h, 18h, 83h, 0C8h, 04h, 52h, 8Bh, 0CEh
    db 89h, 44h, 24h, 14h, 0E8h, 5Eh, 15h, 0E3h, 0FFh, 0F6h, 86h, 18h, 01h, 00h, 00h, 04h
    db 74h, 16h, 8Bh, 86h, 18h, 01h, 00h, 00h, 83h, 0E0h, 0FBh, 8Bh, 0CEh, 89h, 86h, 18h
    db 01h, 00h, 00h, 0E8h, 75h, 26h, 0E2h, 0FFh, 0F6h, 86h, 18h, 01h, 00h, 00h, 10h, 74h
    db 16h, 8Bh, 86h, 18h, 01h, 00h, 00h, 83h, 0E0h, 0EFh, 8Bh, 0CEh, 89h, 86h, 18h, 01h
    db 00h, 00h, 0E8h, 56h, 26h, 0E2h, 0FFh, 8Bh, 0CEh, 0E8h, 0CDh, 0ABh, 0E3h, 0FFh, 8Bh, 07h
    db 8Bh, 0CFh, 0FFh, 50h, 08h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 85h, 0C9h, 74h, 15h, 8Bh
    db 47h, 04h, 83h, 0F8h, 05h, 72h, 0Dh, 8Bh, 11h, 50h, 0FFh, 52h, 4Ch, 0C7h, 47h, 04h
    db 01h, 00h, 00h, 00h, 0C6h, 47h, 15h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h
    db 00h
?d_001ff1c0@@YAXXZ ENDP

; ghidra: FUN_005ff360  retail @ 0x001FF360 size 479
public ?d_001ff360@@YAXXZ
?d_001ff360@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 71h, 0E8h, 57h, 8Bh, 79h, 0E4h, 8Bh, 47h, 14h, 85h
    db 0C0h, 8Dh, 5Fh, 14h, 74h, 07h, 66h, 83h, 78h, 04h, 00h, 75h, 13h, 8Bh, 54h, 24h
    db 1Ch, 8Bh, 01h, 52h, 0FFh, 50h, 10h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
    db 55h, 8Bh, 0CEh, 0E8h, 8Ch, 14h, 0E2h, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 0Fh, 84h, 93h, 01h
    db 00h, 00h, 8Bh, 0CEh, 0E8h, 7Bh, 14h, 0E2h, 0FFh, 8Bh, 0C8h, 0E8h, 53h, 0D1h, 0E1h, 0FFh
    db 84h, 0C0h, 0Fh, 84h, 7Dh, 01h, 00h, 00h, 8Ah, 47h, 1Ch, 84h, 0C0h, 74h, 1Ah, 8Bh
    db 0CEh, 0E8h, 5Eh, 14h, 0E2h, 0FFh, 8Bh, 40h, 04h, 8Ah, 88h, 18h, 01h, 00h, 00h, 84h
    db 0C9h, 74h, 06h, 83h, 0C7h, 18h, 57h, 0EBh, 01h, 53h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h
    db 0E8h, 7Bh, 91h, 0E2h, 0FFh, 85h, 0C0h, 0Fh, 84h, 48h, 01h, 00h, 00h, 33h, 0C9h, 89h
    db 4Ch, 24h, 10h, 89h, 4Ch, 24h, 14h, 6Ah, 00h, 89h, 4Ch, 24h, 1Ch, 8Bh, 8Dh, 30h
    db 02h, 00h, 00h, 8Dh, 54h, 24h, 14h, 52h, 51h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 50h
    db 0E8h, 35h, 55h, 0E4h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 0Fh, 84h, 16h, 01h, 00h, 00h, 8Dh
    db 46h, 38h, 50h, 8Bh, 0CFh, 0E8h, 7Dh, 0ADh, 0E3h, 0FFh, 56h, 8Bh, 0CFh, 0E8h, 5Eh, 0E5h
    db 0E0h, 0FFh, 57h, 8Bh, 0CEh, 0E8h, 07h, 2Bh, 0E0h, 0FFh, 0F6h, 86h, 44h, 03h, 00h, 00h
    db 01h, 0Fh, 84h, 0B3h, 00h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 37h, 14h, 0E3h, 0FFh
    db 6Ah, 01h, 6Ah, 02h, 8Bh, 0CEh, 0C7h, 86h, 20h, 02h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0E8h, 89h, 39h, 0E3h, 0FFh, 0F6h, 86h, 10h, 01h, 00h, 00h, 20h, 74h, 16h, 8Bh, 86h
    db 10h, 01h, 00h, 00h, 83h, 0E0h, 0DFh, 8Bh, 0CEh, 89h, 86h, 10h, 01h, 00h, 00h, 0E8h
    db 99h, 24h, 0E2h, 0FFh, 8Bh, 86h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 20h, 74h
    db 12h, 25h, 0FFh, 0FFh, 0FFh, 0DFh, 8Bh, 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 7Ah
    db 24h, 0E2h, 0FFh, 8Bh, 86h, 14h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 08h, 74h, 12h
    db 25h, 0FFh, 0FFh, 0FFh, 0F7h, 8Bh, 0CEh, 89h, 86h, 14h, 01h, 00h, 00h, 0E8h, 5Bh, 24h
    db 0E2h, 0FFh, 8Ah, 8Eh, 18h, 01h, 00h, 00h, 0B8h, 04h, 00h, 00h, 00h, 84h, 0C8h, 75h
    db 0Dh, 09h, 86h, 18h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 3Fh, 24h, 0E2h, 0FFh, 8Ah, 8Eh
    db 18h, 01h, 00h, 00h, 0B8h, 10h, 00h, 00h, 00h, 84h, 0C8h, 75h, 0Dh, 09h, 86h, 18h
    db 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 23h, 24h, 0E2h, 0FFh, 8Bh, 9Fh, 04h, 02h, 00h, 00h
    db 85h, 0DBh, 74h, 1Fh, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 97h, 21h, 0E0h, 0FFh, 84h, 0C0h, 6Ah
    db 02h, 8Dh, 4Bh, 20h, 56h, 74h, 07h, 0E8h, 0F8h, 25h, 0E4h, 0FFh, 0EBh, 05h, 0E8h, 0E5h
    db 0A6h, 0E2h, 0FFh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 28h, 85h, 0C0h, 74h, 07h, 8Bh, 0C8h
    db 0E8h, 3Dh, 0D2h, 0E3h, 0FFh, 5Dh, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_001ff360@@YAXXZ ENDP

; ghidra: FUN_005ff5c0  retail @ 0x001FF5C0 size 555
public ?d_001ff5c0@@YAXXZ
?d_001ff5c0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0E9h, 56h, 8Bh, 75h, 08h, 8Bh, 9Eh, 00h, 02h, 00h, 00h, 85h
    db 0DBh, 0Fh, 84h, 0Fh, 02h, 00h, 00h, 8Bh, 46h, 7Ch, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 57h, 50h, 0E8h, 6Ch, 0FCh, 0E1h, 0FFh, 8Bh, 55h, 20h, 8Dh, 4Dh, 20h, 8Bh, 0F8h, 0FFh
    db 52h, 28h, 84h, 0C0h, 75h, 1Dh, 8Bh, 03h, 8Bh, 0CBh, 0FFh, 50h, 10h, 0D9h, 5Ch, 24h
    db 10h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 52h, 18h, 0D8h, 5Ch, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 7Ah, 27h, 0D9h, 86h, 20h, 02h, 00h, 00h, 0D8h, 1Dh, 0C4h, 0FAh, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 01h, 0Fh, 84h, 0BAh, 00h, 00h, 00h, 81h, 0BEh, 20h, 02h, 00h, 00h
    db 00h, 00h, 80h, 0BFh, 0Fh, 84h, 0AAh, 00h, 00h, 00h, 8Ah, 45h, 33h, 84h, 0C0h, 0Fh
    db 85h, 0A0h, 01h, 00h, 00h, 8Ah, 45h, 30h, 84h, 0C0h, 0Fh, 85h, 95h, 01h, 00h, 00h
    db 85h, 0FFh, 0Fh, 84h, 8Dh, 01h, 00h, 00h, 3Bh, 0FEh, 0Fh, 84h, 85h, 01h, 00h, 00h
    db 8Bh, 8Fh, 04h, 02h, 00h, 00h, 85h, 0C9h, 0Fh, 84h, 77h, 01h, 00h, 00h, 8Bh, 01h
    db 0FFh, 90h, 80h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 67h, 01h, 00h, 00h, 0D9h, 87h
    db 0BCh, 00h, 00h, 00h, 57h, 0D8h, 0Dh, 6Ch, 0B4h, 09h, 01h, 8Bh, 0CEh, 0D9h, 5Ch, 24h
    db 14h, 0E8h, 57h, 46h, 0E4h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0DEh, 0D9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Fh, 0F6h, 87h, 1Ch, 01h, 00h, 00h, 08h, 75h, 16h
    db 8Bh, 87h, 1Ch, 01h, 00h, 00h, 83h, 0C8h, 08h, 8Bh, 0CFh, 89h, 87h, 1Ch, 01h, 00h
    db 00h, 0E8h, 57h, 22h, 0E2h, 0FFh, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 8Bh, 89h, 0CCh, 01h
    db 00h, 00h, 6Ah, 00h, 83h, 0C6h, 38h, 56h, 57h, 0E8h, 6Bh, 34h, 0E0h, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 59h, 0C3h, 57h, 8Bh, 0CEh, 0E8h, 55h, 28h, 0E0h, 0FFh, 85h, 0FFh, 74h, 2Ch
    db 8Bh, 8Fh, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 22h, 3Bh, 0FEh, 74h, 1Eh, 56h, 0E8h
    db 58h, 3Ah, 0E0h, 0FFh, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 6Ah, 02h, 8Dh, 56h, 38h, 52h
    db 83h, 0C1h, 20h, 0E8h, 52h, 4Ch, 0E3h, 0FFh, 0C6h, 45h, 30h, 01h, 0F6h, 86h, 10h, 01h
    db 00h, 00h, 08h, 74h, 16h, 8Bh, 86h, 10h, 01h, 00h, 00h, 83h, 0E0h, 0F7h, 8Bh, 0CEh
    db 89h, 86h, 10h, 01h, 00h, 00h, 0E8h, 0E2h, 21h, 0E2h, 0FFh, 8Ah, 86h, 10h, 01h, 00h
    db 00h, 0B3h, 10h, 84h, 0C3h, 0BFh, 0EFh, 0FFh, 0FFh, 0FFh, 74h, 15h, 8Bh, 86h, 10h, 01h
    db 00h, 00h, 23h, 0C7h, 8Bh, 0CEh, 89h, 86h, 10h, 01h, 00h, 00h, 0E8h, 0BCh, 21h, 0E2h
    db 0FFh, 0F6h, 86h, 18h, 01h, 00h, 00h, 04h, 74h, 16h, 8Bh, 86h, 18h, 01h, 00h, 00h
    db 83h, 0E0h, 0FBh, 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 9Dh, 21h, 0E2h, 0FFh
    db 84h, 9Eh, 18h, 01h, 00h, 00h, 74h, 15h, 8Bh, 86h, 18h, 01h, 00h, 00h, 23h, 0C7h
    db 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 80h, 21h, 0E2h, 0FFh, 0F6h, 86h, 18h
    db 01h, 00h, 00h, 08h, 74h, 16h, 8Bh, 86h, 18h, 01h, 00h, 00h, 83h, 0E0h, 0F7h, 8Bh
    db 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 61h, 21h, 0E2h, 0FFh, 8Bh, 45h, 20h, 8Dh
    db 75h, 20h, 8Bh, 0CEh, 0FFh, 50h, 14h, 84h, 0C0h, 74h, 09h, 8Bh, 16h, 6Ah, 00h, 8Bh
    db 0CEh, 0FFh, 52h, 0Ch, 8Bh, 45h, 04h, 8Bh, 48h, 20h, 89h, 4Dh, 28h, 0C6h, 45h, 33h
    db 01h, 0C6h, 45h, 36h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h
?d_001ff5c0@@YAXXZ ENDP

; ghidra: FUN_005ff880  retail @ 0x001FF880 size 470
public ?d_001ff880@@YAXXZ
?d_001ff880@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 6Eh, 0F8h, 8Ah, 9Dh, 44h, 03h, 00h
    db 00h, 8Ah, 4Eh, 21h, 8Bh, 46h, 0F4h, 80h, 0E3h, 01h, 3Ah, 0CBh, 57h, 89h, 44h, 24h
    db 18h, 74h, 18h, 8Ah, 48h, 2Ch, 84h, 0C9h, 74h, 11h, 84h, 0DBh, 88h, 5Eh, 21h, 8Bh
    db 40h, 20h, 89h, 46h, 18h, 74h, 04h, 0C6h, 46h, 20h, 01h, 8Ah, 46h, 25h, 84h, 0C0h
    db 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 75h, 17h, 6Ah, 04h, 8Dh, 4Ch, 24h, 18h
    db 51h, 8Bh, 0CDh, 0E8h, 0FAh, 09h, 0E4h, 0FFh, 84h, 0C0h, 0C6h, 44h, 24h, 12h, 01h, 75h
    db 05h, 0C6h, 44h, 24h, 12h, 00h, 8Dh, 7Eh, 0F0h, 8Bh, 0CFh, 89h, 7Ch, 24h, 1Ch, 0E8h
    db 55h, 6Bh, 0E3h, 0FFh, 84h, 0DBh, 88h, 44h, 24h, 13h, 0Fh, 85h, 34h, 01h, 00h, 00h
    db 8Bh, 5Ch, 24h, 18h, 0D9h, 43h, 20h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 01h, 75h, 13h, 8Ah, 44h, 24h, 12h, 84h, 0C0h, 74h, 0Bh, 8Ah, 46h, 26h, 84h
    db 0C0h, 0Fh, 84h, 0Dh, 01h, 00h, 00h, 8Bh, 56h, 10h, 8Dh, 4Eh, 10h, 0FFh, 52h, 14h
    db 84h, 0C0h, 0Fh, 84h, 0E7h, 00h, 00h, 00h, 8Bh, 46h, 0F8h, 50h, 0E8h, 0A6h, 0EDh, 0E0h
    db 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 1Dh, 8Bh, 48h, 14h, 85h, 0C9h, 74h, 16h, 8Ah
    db 48h, 24h, 84h, 0C9h, 75h, 0Fh, 8Bh, 0C8h, 0E8h, 0B8h, 0B6h, 0E4h, 0FFh, 84h, 0C0h, 0Fh
    db 85h, 0BAh, 00h, 00h, 00h, 8Ah, 46h, 26h, 84h, 0C0h, 75h, 0Ch, 8Ah, 44h, 24h, 13h
    db 84h, 0C0h, 0Fh, 85h, 0AFh, 00h, 00h, 00h, 8Ah, 46h, 24h, 84h, 0C0h, 75h, 2Fh, 0D9h
    db 85h, 20h, 02h, 00h, 00h, 0D8h, 1Dh, 90h, 0DCh, 2Ah, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h
    db 75h, 1Ch, 0C6h, 46h, 24h, 01h, 8Bh, 43h, 28h, 85h, 0C0h, 74h, 11h, 8Dh, 4Dh, 38h
    db 51h, 8Bh, 0Dh, 38h, 0F7h, 2Eh, 01h, 55h, 50h, 0E8h, 0B0h, 64h, 0E3h, 0FFh, 8Bh, 0BDh
    db 00h, 02h, 00h, 00h, 85h, 0FFh, 74h, 51h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 18h, 0DBh
    db 46h, 1Ch, 8Bh, 46h, 1Ch, 85h, 0C0h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0DEh
    db 0F9h, 8Bh, 55h, 00h, 6Ah, 02h, 55h, 8Bh, 0CDh, 0D9h, 5Ch, 24h, 20h, 8Bh, 44h, 24h
    db 20h, 50h, 0FFh, 52h, 44h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 14h, 0D8h, 0Dh, 0C4h, 0FAh
    db 07h, 01h, 0D9h, 9Dh, 20h, 02h, 00h, 00h, 8Ah, 46h, 25h, 84h, 0C0h, 75h, 0Ah, 8Bh
    db 07h, 8Bh, 0CFh, 0FFh, 90h, 90h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 1Ch, 0E8h, 0CEh, 64h
    db 0E3h, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 10h, 0C3h, 8Ah
    db 44h, 24h, 13h, 84h, 0C0h, 74h, 14h, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh
    db 83h, 0C4h, 10h, 0C3h, 8Bh, 0CFh, 0E8h, 94h, 2Fh, 0E3h, 0FFh, 8Bh, 0CFh, 0E8h, 9Eh, 64h
    db 0E3h, 0FFh, 8Bh, 0CFh, 0E8h, 0CBh, 0EFh, 0E2h, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 05h, 00h, 00h
    db 00h, 5Bh, 83h, 0C4h, 10h, 0C3h
?d_001ff880@@YAXXZ ENDP

; ghidra: FUN_005ffca0  retail @ 0x001FFCA0 size 110
public ?d_001ffca0@@YAXXZ
?d_001ffca0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 56h
    db 8Bh, 0CFh, 0E8h, 0D3h, 6Bh, 0E3h, 0FFh, 8Bh, 16h, 8Dh, 47h, 50h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 74h, 56h, 8Dh, 4Fh, 54h, 0E8h, 41h, 0C7h, 0E2h, 0FFh, 8Bh, 16h, 8Dh, 87h, 0D4h
    db 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 87h
    db 0C4h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh, 16h, 81h, 0C7h, 0D0h, 00h
    db 00h, 00h, 57h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_001ffca0@@YAXXZ ENDP

; ghidra: FUN_005fffc0  retail @ 0x001FFFC0 size 313
public ?d_001fffc0@@YAXXZ
?d_001fffc0@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 4Ch, 24h, 24h, 8Bh, 47h, 0E0h
    db 51h, 8Bh, 0CFh, 89h, 44h, 24h, 14h, 0E8h, 0E5h, 0F7h, 0E1h, 0FFh, 8Bh, 77h, 0E4h, 8Bh
    db 56h, 38h, 89h, 54h, 24h, 14h, 8Bh, 46h, 3Ch, 89h, 44h, 24h, 18h, 8Bh, 4Eh, 40h
    db 89h, 4Ch, 24h, 1Ch, 8Bh, 9Eh, 04h, 02h, 00h, 00h, 85h, 0DBh, 8Bh, 0AEh, 08h, 02h
    db 00h, 00h, 0Fh, 84h, 0A1h, 00h, 00h, 00h, 0F7h, 86h, 14h, 01h, 00h, 00h, 00h, 00h
    db 00h, 10h, 74h, 4Eh, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 92h, 50h, 01h, 00h, 00h, 85h, 0C0h
    db 0Fh, 84h, 0C9h, 00h, 00h, 00h, 0D9h, 80h, 70h, 04h, 00h, 00h, 0D8h, 0Dh, 44h, 53h
    db 07h, 01h, 0D8h, 15h, 0A8h, 0FAh, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 21h, 0D9h
    db 46h, 44h, 0D9h, 0C0h, 0D9h, 0FFh, 0D8h, 0CAh, 0D8h, 44h, 24h, 14h, 0D9h, 5Ch, 24h, 14h
    db 0D9h, 0FEh, 0D8h, 0C9h, 0D8h, 44h, 24h, 18h, 0D9h, 5Ch, 24h, 18h, 0C6h, 45h, 5Dh, 01h
    db 0DDh, 0D8h, 8Bh, 44h, 24h, 10h, 83h, 0ECh, 18h, 8Dh, 88h, 24h, 02h, 00h, 00h, 8Bh
    db 31h, 8Bh, 0D4h, 89h, 32h, 8Bh, 71h, 04h, 89h, 72h, 04h, 8Bh, 71h, 08h, 89h, 72h
    db 08h, 8Bh, 71h, 0Ch, 89h, 72h, 0Ch, 8Bh, 71h, 10h, 8Bh, 49h, 14h, 89h, 72h, 10h
    db 89h, 4Ah, 14h, 8Dh, 54h, 24h, 2Ch, 52h, 8Bh, 0CAh, 8Bh, 90h, 3Ch, 02h, 00h, 00h
    db 51h, 52h, 8Bh, 0CBh, 0E8h, 0F1h, 2Ah, 0E4h, 0FFh, 8Bh, 54h, 24h, 18h, 8Bh, 0Dh, 0CCh
    db 0F4h, 2Eh, 01h, 8Bh, 01h, 6Ah, 00h, 52h, 8Bh, 54h, 24h, 1Ch, 52h, 0FFh, 50h, 18h
    db 0D9h, 5Ch, 24h, 1Ch, 8Bh, 54h, 24h, 14h, 8Dh, 87h, 0A0h, 00h, 00h, 00h, 8Bh, 0C8h
    db 89h, 11h, 8Bh, 54h, 24h, 18h, 89h, 51h, 04h, 8Bh, 54h, 24h, 1Ch, 68h, 00h, 00h
    db 0F0h, 41h, 6Ah, 00h, 89h, 51h, 08h, 50h, 8Bh, 0CDh, 0E8h, 39h, 0CDh, 0E0h, 0FFh, 5Fh
    db 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_001fffc0@@YAXXZ ENDP

; ghidra: FUN_00600160  retail @ 0x00200160 size 25
public ?d_00200160@@YAXXZ
?d_00200160@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0DAh, 7Ah, 0E4h, 0FFh
?d_00200160@@YAXXZ ENDP
_TEXT ENDS
END
