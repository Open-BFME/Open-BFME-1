.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?Rva002EEDA0TheShroudManager@@3PAURva002EEDA0ShroudManager@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?buildTransformMatrix@Matrix3D@@QAEXABVVector3@@0@Z:NEAR
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeDirectionWeight1285@@3MA:BYTE
EXTERN ?g_bfmeScaleBC@@3MA:BYTE
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000666d@@YAXXZ:NEAR
EXTERN ?j_0000ce28@@YAXXZ:NEAR
EXTERN ?j_0000d81e@@YAXXZ:NEAR
EXTERN ?j_000157da@@YAXXZ:NEAR
EXTERN ?j_000184a8@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_0002191d@@YAXXZ:NEAR
EXTERN ?j_0002308d@@YAXXZ:NEAR
EXTERN ?j_00024d70@@YAXXZ:NEAR
EXTERN ?j_00025d56@@YAXXZ:NEAR
EXTERN ?j_00027a43@@YAXXZ:NEAR
EXTERN ?j_000294f6@@YAXXZ:NEAR
EXTERN ?j_0002c9d5@@YAXXZ:NEAR
EXTERN ?j_0002d439@@YAXXZ:NEAR
EXTERN ?j_000322d6@@YAXXZ:NEAR
EXTERN ?j_000359bd@@YAXXZ:NEAR
EXTERN ?j_000361ce@@YAXXZ:NEAR
EXTERN ?j_00039649@@YAXXZ:NEAR
EXTERN ?j_0003a1a7@@YAXXZ:NEAR
EXTERN ?j_0003a391@@YAXXZ:NEAR
EXTERN ?j_00044c60@@YAXXZ:NEAR
EXTERN ?j_000466b4@@YAXXZ:NEAR
EXTERN ?m@Gen_008f7470@@QAEXXZ:NEAR
EXTERN __ftol2:NEAR
EXTERN __real@3e800000:BYTE
EXTERN __real@4f800000:BYTE
EXTERN g_Va010C0904:BYTE
EXTERN g_Va010C0908:BYTE
_TEXT SEGMENT

; ghidra: FUN_0068fdf0  retail @ 0x0028FDF0 size 104
public ?d_0028fdf0@@YAXXZ
?d_0028fdf0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 2Ch, 0FFh, 2Eh, 01h, 6Ah, 0FFh, 68h, 3Eh
    db 18h, 01h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 2Ch, 0FFh, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 1Ch, 00h, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0A5h, 0AFh
    db 0DAh, 0FFh, 0A3h, 28h, 0FFh, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 28h, 0FFh, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_0028fdf0@@YAXXZ ENDP

; ghidra: FUN_006901c0  retail @ 0x002901C0 size 105
public ?d_002901c0@@YAXXZ
?d_002901c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 6Ch, 85h, 0C9h, 57h, 74h, 0Ch, 0E8h, 5Eh, 5Ch, 0D8h, 0FFh
    db 0C7h, 46h, 6Ch, 00h, 00h, 00h, 00h, 8Bh, 7Eh, 60h, 3Bh, 7Eh, 64h, 74h, 22h, 53h
    db 8Bh, 1Fh, 85h, 0DBh, 74h, 10h, 8Bh, 0CBh, 0E8h, 0Dh, 51h, 0DBh, 0FFh, 53h, 0E8h, 0BDh
    db 1Ch, 5Fh, 00h, 83h, 0C4h, 04h, 8Bh, 46h, 64h, 83h, 0C7h, 04h, 3Bh, 0F8h, 75h, 0E0h
    db 5Bh, 8Bh, 46h, 64h, 3Bh, 0C0h, 8Bh, 4Eh, 60h, 75h, 06h, 5Fh, 89h, 4Eh, 64h, 5Eh
    db 0C3h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h
    db 0Ch, 03h, 0C7h, 5Fh, 89h, 46h, 64h, 5Eh, 0C3h
?d_002901c0@@YAXXZ ENDP

; ghidra: FUN_00690250  retail @ 0x00290250 size 470
public ?d_00290250@@YAXXZ
?d_00290250@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 55h, 56h, 8Bh, 74h, 24h, 20h, 57h, 56h, 8Bh, 0F9h, 0E8h, 5Eh
    db 42h, 0D7h, 0FFh, 8Bh, 06h, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 28h
    db 01h, 0C6h, 44h, 24h, 29h, 02h, 0FFh, 50h, 28h, 33h, 0EDh, 8Dh, 5Fh, 58h, 8Bh, 0FFh
    db 8Bh, 16h, 8Dh, 44h, 2Fh, 24h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh
    db 16h, 8Dh, 43h, 0D8h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 53h, 56h, 0E8h, 13h, 0C7h, 0D7h
    db 0FFh, 83h, 0C4h, 08h, 45h, 83h, 0C3h, 04h, 83h, 0FDh, 0Ah, 7Ch, 0D3h, 0C7h, 87h, 0B4h
    db 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0AFh, 84h, 00h, 00h, 00h, 2Bh, 0AFh, 80h
    db 00h, 00h, 00h, 0C1h, 0FDh, 02h, 33h, 0DBh, 85h, 0EDh, 7Eh, 3Dh, 8Dh, 64h, 24h, 00h
    db 8Bh, 8Fh, 80h, 00h, 00h, 00h, 8Bh, 14h, 99h, 8Bh, 06h, 8Bh, 0CEh, 89h, 54h, 24h
    db 10h, 0FFh, 50h, 08h, 84h, 0C0h, 74h, 12h, 8Bh, 4Ch, 24h, 10h, 3Bh, 8Fh, 8Ch, 00h
    db 00h, 00h, 75h, 06h, 89h, 9Fh, 0B4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 56h, 0E8h
    db 0E8h, 8Eh, 0D7h, 0FFh, 43h, 3Bh, 0DDh, 7Ch, 0C7h, 8Bh, 16h, 8Dh, 87h, 0B4h, 00h, 00h
    db 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 06h, 8Dh, 8Fh, 90h, 00h, 00h, 00h, 51h
    db 8Bh, 0CEh, 0FFh, 50h, 78h, 80h, 7Ch, 24h, 25h, 02h, 0Fh, 83h, 97h, 00h, 00h, 00h
    db 8Bh, 97h, 98h, 00h, 00h, 00h, 8Bh, 06h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CEh, 89h
    db 54h, 24h, 14h, 0FFh, 50h, 78h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h
    db 3Eh, 8Bh, 44h, 24h, 10h, 33h, 0DBh, 3Bh, 0C3h, 89h, 5Ch, 24h, 14h, 7Eh, 68h, 8Dh
    db 0AFh, 94h, 00h, 00h, 00h, 8Dh, 44h, 24h, 14h, 50h, 56h, 0E8h, 44h, 0C6h, 0D7h, 0FFh
    db 83h, 0C4h, 08h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 54h, 24h, 1Ch, 52h, 8Bh, 0CDh, 0E8h
    db 75h, 96h, 0DBh, 0FFh, 8Bh, 44h, 24h, 10h, 43h, 3Bh, 0D8h, 7Ch, 0D8h, 0EBh, 38h, 8Bh
    db 87h, 94h, 00h, 00h, 00h, 8Bh, 58h, 08h, 3Bh, 0D8h, 74h, 2Bh, 8Dh, 64h, 24h, 00h
    db 8Bh, 43h, 10h, 8Dh, 4Ch, 24h, 14h, 51h, 56h, 89h, 44h, 24h, 1Ch, 0E8h, 02h, 0C6h
    db 0D7h, 0FFh, 53h, 0E8h, 0B8h, 0B4h, 59h, 00h, 8Bh, 0D8h, 8Bh, 87h, 94h, 00h, 00h, 00h
    db 83h, 0C4h, 0Ch, 3Bh, 0D8h, 75h, 0D9h, 8Bh, 16h, 6Ah, 04h, 8Dh, 87h, 0A0h, 00h, 00h
    db 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 24h, 8Bh, 16h, 8Dh, 87h, 0A4h, 00h, 00h, 00h, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 78h, 8Dh, 8Fh, 0A8h, 00h, 00h, 00h, 51h, 56h, 0E8h, 0C2h, 0C5h
    db 0D7h, 0FFh, 8Ah, 44h, 24h, 2Dh, 83h, 0C4h, 08h, 3Ch, 02h, 72h, 1Fh, 8Bh, 16h, 8Dh
    db 87h, 0ACh, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 81h, 0C7h, 0B0h
    db 00h, 00h, 00h, 57h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh
    db 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00290250@@YAXXZ ENDP

; ghidra: FUN_00690990  retail @ 0x00290990 size 400
public ?d_00290990@@YAXXZ
?d_00290990@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 0Ch, 85h, 0FFh, 75h, 07h, 5Fh, 32h, 0C0h, 5Eh, 0C2h
    db 04h, 00h, 8Bh, 46h, 1Ch, 85h, 0C0h, 55h, 8Bh, 6Ch, 24h, 10h, 74h, 1Ah, 8Bh, 80h
    db 14h, 02h, 00h, 00h, 85h, 0C0h, 74h, 10h, 3Bh, 85h, 14h, 02h, 00h, 00h, 75h, 08h
    db 5Dh, 5Fh, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h, 8Bh, 45h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh
    db 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0E0h, 18h, 0D7h, 0FFh, 8Ah, 88h, 0C8h, 00h, 00h
    db 00h, 84h, 0C9h, 79h, 08h, 5Dh, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h, 6Ah, 6Ch, 8Bh
    db 0CDh, 0E8h, 29h, 1Bh, 0DAh, 0FFh, 84h, 0C0h, 75h, 0EBh, 6Ah, 35h, 8Bh, 0CDh, 0E8h, 1Ch
    db 1Bh, 0DAh, 0FFh, 84h, 0C0h, 75h, 0DEh, 6Ah, 02h, 8Bh, 0CDh, 0E8h, 0Fh, 1Bh, 0DAh, 0FFh
    db 84h, 0C0h, 75h, 0D1h, 6Ah, 2Fh, 8Bh, 0CDh, 0E8h, 02h, 1Bh, 0DAh, 0FFh, 84h, 0C0h, 75h
    db 0C4h, 55h, 8Bh, 0CFh, 0E8h, 0F0h, 9Ch, 0DBh, 0FFh, 85h, 0C0h, 75h, 0B8h, 0F6h, 85h, 44h
    db 03h, 00h, 00h, 01h, 75h, 0AFh, 8Bh, 46h, 10h, 6Ah, 00h, 50h, 8Bh, 0CDh, 0E8h, 95h
    db 74h, 0DBh, 0FFh, 84h, 0C0h, 74h, 9Eh, 8Bh, 4Eh, 08h, 0C6h, 46h, 20h, 01h, 8Bh, 41h
    db 04h, 6Ah, 00h, 55h, 8Dh, 48h, 10h, 0E8h, 0D8h, 0CFh, 0D8h, 0FFh, 84h, 0C0h, 75h, 85h
    db 8Bh, 15h, 14h, 0F2h, 2Eh, 01h, 8Bh, 4Ah, 0Ch, 53h, 6Ah, 00h, 8Dh, 5Dh, 38h, 53h
    db 0E8h, 0B0h, 0C3h, 0DAh, 0FFh, 84h, 0C0h, 74h, 09h, 5Bh, 5Dh, 5Fh, 32h, 0C0h, 5Eh, 0C2h
    db 04h, 00h, 8Bh, 46h, 08h, 8Bh, 0B8h, 80h, 00h, 00h, 00h, 3Bh, 0B8h, 84h, 00h, 00h
    db 00h, 74h, 33h, 8Bh, 0Fh, 8Bh, 41h, 04h, 8Bh, 40h, 04h, 85h, 0C0h, 74h, 05h, 83h
    db 0F8h, 03h, 75h, 12h, 8Bh, 56h, 18h, 8Bh, 46h, 14h, 55h, 52h, 50h, 0E8h, 02h, 5Ch
    db 0DBh, 0FFh, 84h, 0C0h, 75h, 10h, 8Bh, 4Eh, 08h, 8Bh, 81h, 84h, 00h, 00h, 00h, 83h
    db 0C7h, 04h, 3Bh, 0F8h, 75h, 0CDh, 8Bh, 56h, 08h, 3Bh, 0BAh, 84h, 00h, 00h, 00h, 74h
    db 0A8h, 8Bh, 56h, 0Ch, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh, 48h, 0Ch, 6Ah, 00h, 83h, 0C2h
    db 38h, 52h, 0E8h, 3Eh, 0C3h, 0DAh, 0FFh, 84h, 0C0h, 75h, 29h, 8Bh, 0CDh, 0E8h, 9Fh, 98h
    db 0DAh, 0FFh, 83h, 0F8h, 01h, 75h, 1Dh, 8Bh, 56h, 0Ch, 0A1h, 14h, 0F2h, 2Eh, 01h, 8Bh
    db 48h, 0Ch, 53h, 83h, 0C2h, 38h, 52h, 0E8h, 0C0h, 03h, 0DAh, 0FFh, 84h, 0C0h, 0Fh, 84h
    db 65h, 0FFh, 0FFh, 0FFh, 5Bh, 89h, 6Eh, 1Ch, 5Dh, 5Fh, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_00290990@@YAXXZ ENDP

; ghidra: FUN_00690b90  retail @ 0x00290B90 size 536
_TEXT ENDS
_TEXT$d00690b90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00690B90 size 536
public ?d_00290b90@@YAXXZ
?d_00290b90@@YAXXZ PROC
    db 083h, 0ECh, 010h, 053h, 055h, 056h, 057h, 08Bh, 0F1h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 08Bh, 04Eh, 008h, 033h, 0DBh, 03Bh, 0CBh, 089h, 05Ch, 024h, 010h, 074h, 065h
    call ?j_00020824@@YAXXZ
    db 08Bh, 0F8h, 03Bh, 0FBh, 074h, 05Ah, 08Bh, 047h, 024h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 053h, 06Ah, 003h, 050h
    call ?j_00044c60@@YAXXZ
    db 08Bh, 07Fh, 024h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 053h, 06Ah, 004h, 057h, 00Fh, 0B7h, 0E8h
    call ?j_00044c60@@YAXXZ
    db 08Bh, 04Eh, 008h, 00Fh, 0B7h, 0C0h, 050h, 083h, 0C1h, 038h, 06Ah, 001h, 051h, 08Bh, 00Dh
    dd ?Rva002EEDA0TheShroudManager@@3PAURva002EEDA0ShroudManager@@A
    call ?m@Gen_008f7470@@QAEXXZ
    db 08Bh, 00Dh
    dd ?Rva002EEDA0TheShroudManager@@3PAURva002EEDA0ShroudManager@@A
    db 08Bh, 0D8h, 08Bh, 046h, 008h, 055h, 06Ah, 001h, 083h, 0C0h, 038h, 050h
    call ?m@Gen_008f7470@@QAEXXZ
    db 089h, 044h, 024h, 010h, 08Bh, 046h, 008h, 08Bh, 080h, 010h, 002h, 000h, 000h, 085h, 0C0h, 0C7h
    db 044h, 024h, 014h, 000h, 000h, 000h, 000h, 074h, 007h, 08Bh, 048h, 028h, 089h, 04Ch, 024h, 014h
    db 08Bh, 086h, 080h, 000h, 000h, 000h, 03Bh, 086h, 084h, 000h, 000h, 000h, 089h, 044h, 024h, 018h
    db 00Fh, 084h, 037h, 001h, 000h, 000h, 08Bh, 038h, 03Bh, 0BEh, 08Ch, 000h, 000h, 000h, 075h, 033h
    db 08Bh, 047h, 004h, 08Bh, 048h, 00Ch, 085h, 0C9h, 074h, 029h, 08Bh, 040h, 004h, 08Bh, 054h, 086h
    db 058h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 050h, 08Bh, 044h, 024h, 014h, 050h, 053h, 08Bh, 0CFh
    call ?j_000466b4@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 013h, 001h, 000h, 000h, 08Bh, 086h, 0A4h, 000h, 000h, 000h, 085h, 0C0h
    db 07Eh, 014h, 08Bh, 04Fh, 004h, 08Bh, 041h, 004h, 03Bh, 086h, 0A0h, 000h, 000h, 000h, 00Fh, 085h
    db 0C5h, 000h, 000h, 000h, 0EBh, 012h, 08Bh, 057h, 004h, 08Bh, 042h, 004h, 08Ah, 04Ch, 030h, 024h
    db 084h, 0C9h, 00Fh, 084h, 0B1h, 000h, 000h, 000h, 08Bh, 04Eh, 004h, 08Ah, 051h, 02Ch, 084h, 0D2h
    db 075h, 022h, 083h, 07Ch, 024h, 014h, 002h, 07Ch, 01Bh, 083h, 0F8h, 004h, 00Fh, 084h, 097h, 000h
    db 000h, 000h, 083h, 0F8h, 005h, 00Fh, 084h, 08Eh, 000h, 000h, 000h, 083h, 0F8h, 006h, 00Fh, 084h
    db 085h, 000h, 000h, 000h, 083h, 0F8h, 006h, 075h, 058h, 08Bh, 056h, 070h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 074h, 043h, 08Bh, 045h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h
    db 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0C8h, 000h, 000h, 000h, 000h, 000h, 000h, 002h, 075h, 024h, 0F6h, 085h, 090h, 000h
    db 000h, 000h, 040h, 075h, 01Bh, 08Bh, 04Eh, 008h
    call ?j_0003a391@@YAXXZ
    db 08Bh, 0CDh, 089h, 044h, 024h, 01Ch
    call ?j_0003a391@@YAXXZ
    db 08Bh, 04Ch, 024h, 01Ch, 03Bh, 0C8h, 075h, 028h, 08Bh, 047h, 004h, 08Bh, 040h, 004h, 08Bh, 04Ch
    db 086h, 058h, 051h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001f253@@YAXXZ
    db 08Bh, 054h, 024h, 010h, 050h, 052h, 053h, 08Bh, 0CFh
    call ?j_000466b4@@YAXXZ
    db 084h, 0C0h, 075h, 032h, 08Bh, 044h, 024h, 018h, 08Bh, 08Eh, 084h, 000h, 000h, 000h, 083h, 0C0h
    db 004h, 03Bh, 0C1h, 089h, 044h, 024h, 018h, 00Fh, 085h, 0C9h, 0FEh, 0FFh, 0FFh, 08Bh, 086h, 0A4h
    db 000h, 000h, 000h, 085h, 0C0h, 07Eh, 019h, 0C7h, 086h, 0A4h, 000h, 000h, 000h, 000h, 000h, 000h
    db 000h, 0E9h, 00Ch, 0FEh, 0FFh, 0FFh, 08Bh, 0C7h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 010h, 0C3h
    db 05Fh, 05Eh, 05Dh, 033h, 0C0h, 05Bh, 083h, 0C4h, 010h, 0C3h
?d_00290b90@@YAXXZ ENDP
_TEXT$d00690b90 ENDS
_TEXT SEGMENT

; ghidra: FUN_00691890  retail @ 0x00291890 size 25
public ?d_00291890@@YAXXZ
?d_00291890@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0AAh, 63h, 0DBh, 0FFh
?d_00291890@@YAXXZ ENDP

; ghidra: FUN_006918b0  retail @ 0x002918B0 size 35
public ?d_002918b0@@YAXXZ
?d_002918b0@@YAXXZ PROC
    db 8Ah, 44h, 24h, 04h, 84h, 0C0h, 88h, 41h, 2Fh, 74h, 0Eh, 8Ah, 44h, 24h, 08h, 0C6h
    db 41h, 2Dh, 00h, 88h, 41h, 30h, 0C2h, 08h, 00h, 8Ah, 54h, 24h, 08h, 88h, 51h, 30h
    db 0C2h, 08h, 00h
?d_002918b0@@YAXXZ ENDP

; ghidra: FUN_006918e0  retail @ 0x002918E0 size 18
public ?d_002918e0@@YAXXZ
?d_002918e0@@YAXXZ PROC
    db 8Ah, 44h, 24h, 04h, 84h, 0C0h, 88h, 41h, 2Dh, 74h, 04h, 0C6h, 41h, 2Fh, 00h, 0C2h
    db 04h, 00h
?d_002918e0@@YAXXZ ENDP

; ghidra: FUN_006919e0  retail @ 0x002919E0 size 17
public ?d_002919e0@@YAXXZ
?d_002919e0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 0B0h, 0E6h, 0Bh, 01h, 0E8h, 30h, 0EFh, 5Bh, 00h
    db 0C3h
?d_002919e0@@YAXXZ ENDP

; ghidra: FUN_00691bd0  retail @ 0x00291BD0 size 194
public ?d_00291bd0@@YAXXZ
?d_00291bd0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 68h, 19h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 30h, 56h, 8Bh, 71h, 08h, 57h, 8Bh, 79h, 04h
    db 8Bh, 0CEh, 0E8h, 2Dh, 0ECh, 0D8h, 0FFh, 33h, 0C9h, 8Dh, 57h, 18h, 89h, 4Ch, 24h, 14h
    db 0C7h, 44h, 24h, 10h, 58h, 51h, 0Ah, 01h, 89h, 54h, 24h, 18h, 89h, 44h, 24h, 1Ch
    db 0C6h, 44h, 24h, 20h, 01h, 89h, 4Ch, 24h, 40h, 89h, 4Ch, 24h, 28h, 0C7h, 44h, 24h
    db 24h, 0C0h, 5Dh, 08h, 01h, 89h, 74h, 24h, 2Ch, 0C7h, 44h, 24h, 30h, 04h, 00h, 00h
    db 00h, 88h, 4Ch, 24h, 34h, 89h, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 08h, 8Ch, 0E5h, 0Bh
    db 01h, 8Dh, 44h, 24h, 08h, 50h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 44h, 02h, 0E8h
    db 8Ch, 0Eh, 76h, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 4Ch, 24h, 14h, 0E8h, 7Eh, 0Eh
    db 76h, 00h, 8Bh, 47h, 14h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h, 8Dh, 54h, 24h, 10h, 52h
    db 6Ah, 01h, 50h, 83h, 0C6h, 38h, 56h, 0E8h, 24h, 0Ah, 76h, 00h, 8Bh, 4Ch, 24h, 38h
    db 85h, 0C0h, 5Fh, 0Fh, 95h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 3Ch, 0C3h
?d_00291bd0@@YAXXZ ENDP

; ghidra: FUN_00691cd0  retail @ 0x00291CD0 size 188
public ?d_00291cd0@@YAXXZ
?d_00291cd0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 19h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 2Ch, 56h, 8Bh, 71h, 08h, 57h, 8Bh, 79h, 04h
    db 6Ah, 00h, 56h, 8Dh, 4Ch, 24h, 18h, 0E8h, 9Bh, 4Dh, 0DBh, 0FFh, 8Bh, 0CEh, 0C7h, 44h
    db 24h, 3Ch, 00h, 00h, 00h, 00h, 0E8h, 19h, 0EBh, 0D8h, 0FFh, 8Dh, 4Fh, 1Ch, 0C7h, 44h
    db 24h, 24h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 58h, 51h, 0Ah, 01h, 89h, 4Ch
    db 24h, 28h, 89h, 44h, 24h, 2Ch, 0C6h, 44h, 24h, 30h, 01h, 0C7h, 44h, 24h, 0Ch, 00h
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 08h, 80h, 3Bh, 08h, 01h, 8Dh, 54h, 24h, 20h, 52h
    db 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 40h, 02h, 0E8h, 92h, 0Dh, 76h, 00h, 8Dh, 44h
    db 24h, 08h, 50h, 8Dh, 4Ch, 24h, 14h, 0E8h, 84h, 0Dh, 76h, 00h, 8Bh, 57h, 14h, 8Dh
    db 4Ch, 24h, 10h, 51h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h, 6Ah, 01h, 52h, 83h, 0C6h, 38h
    db 56h, 0E8h, 2Ah, 09h, 76h, 00h, 8Bh, 4Ch, 24h, 34h, 85h, 0C0h, 5Fh, 0Fh, 95h, 0C0h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 38h, 0C3h
?d_00291cd0@@YAXXZ ENDP

; ghidra: FUN_00691f20  retail @ 0x00291F20 size 541
public ?d_00291f20@@YAXXZ
?d_00291f20@@YAXXZ PROC
    db 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 0F4h, 57h, 8Bh, 7Eh, 0F8h, 0F6h, 87h, 44h, 03h
    db 00h, 00h, 01h, 89h, 5Ch, 24h, 0Ch, 74h, 0Ah, 5Fh, 5Eh, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh
    db 5Bh, 59h, 0C3h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 46h, 14h, 3Bh, 41h, 3Ch, 77h
    db 0Fh, 8Bh, 87h, 90h, 00h, 00h, 00h, 0F6h, 0C4h, 04h, 75h, 04h, 0B0h, 01h, 0EBh, 02h
    db 32h, 0C0h, 8Ah, 4Eh, 1Dh, 84h, 0C9h, 74h, 02h, 0B0h, 01h, 8Ah, 4Eh, 1Ch, 84h, 0C9h
    db 74h, 6Ch, 84h, 0C0h, 74h, 68h, 8Ah, 46h, 20h, 84h, 0C0h, 74h, 04h, 0C6h, 46h, 1Fh
    db 00h, 8Ah, 46h, 1Fh, 84h, 0C0h, 75h, 56h, 6Ah, 35h, 8Bh, 0CFh, 0E8h, 0E9h, 0FFh, 0D9h
    db 0FFh, 6Ah, 16h, 8Bh, 0CFh, 0E8h, 11h, 03h, 0D8h, 0FFh, 8Bh, 8Fh, 04h, 02h, 00h, 00h
    db 85h, 0C9h, 74h, 0Ah, 8Bh, 11h, 6Ah, 00h, 0FFh, 92h, 0FCh, 01h, 00h, 00h, 0C7h, 46h
    db 14h, 0FFh, 0FFh, 0FFh, 3Fh, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 03h, 4Bh, 10h
    db 89h, 4Eh, 18h, 0C6h, 46h, 1Ch, 00h, 0C6h, 46h, 1Eh, 00h, 8Bh, 43h, 2Ch, 85h, 0C0h
    db 74h, 0Ch, 6Ah, 00h, 57h, 50h, 0E8h, 64h, 05h, 0D8h, 0FFh, 83h, 0C4h, 0Ch, 8Ah, 46h
    db 1Ch, 84h, 0C0h, 0Fh, 85h, 4Ah, 01h, 00h, 00h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 56h
    db 18h, 3Bh, 50h, 3Ch, 72h, 0Bh, 8Ah, 46h, 1Fh, 84h, 0C0h, 0Fh, 84h, 32h, 01h, 00h
    db 00h, 55h, 8Dh, 6Eh, 0F0h, 8Bh, 0CDh, 32h, 0DBh, 0E8h, 34h, 16h, 0D8h, 0FFh, 84h, 0C0h
    db 74h, 02h, 0B3h, 01h, 8Bh, 0CDh, 0E8h, 76h, 0E8h, 0D9h, 0FFh, 84h, 0C0h, 74h, 02h, 0B3h
    db 01h, 8Bh, 4Eh, 0F8h, 8Bh, 89h, 00h, 02h, 00h, 00h, 85h, 0C9h, 74h, 14h, 8Bh, 11h
    db 0FFh, 52h, 14h, 0DCh, 1Dh, 0F0h, 0B3h, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 02h
    db 0B3h, 01h, 8Ah, 46h, 1Eh, 84h, 0C0h, 8Bh, 87h, 18h, 01h, 00h, 00h, 74h, 09h, 0F6h
    db 0C4h, 20h, 75h, 0Dh, 0B3h, 01h, 0EBh, 09h, 0F6h, 0C4h, 20h, 74h, 04h, 0C6h, 46h, 1Eh
    db 01h, 8Bh, 87h, 90h, 00h, 00h, 00h, 0F6h, 0C4h, 04h, 74h, 02h, 32h, 0DBh, 8Ah, 46h
    db 1Fh, 84h, 0C0h, 74h, 02h, 0B3h, 01h, 8Ah, 46h, 1Dh, 84h, 0C0h, 0Fh, 85h, 0B0h, 00h
    db 00h, 00h, 84h, 0DBh, 0Fh, 84h, 0A8h, 00h, 00h, 00h, 8Bh, 87h, 2Ch, 01h, 00h, 00h
    db 84h, 0E4h, 78h, 4Ch, 6Ah, 0Ah, 8Bh, 0CFh, 0E8h, 07h, 0F6h, 0D6h, 0FFh, 84h, 0C0h, 75h
    db 3Fh, 8Bh, 5Ch, 24h, 10h, 8Bh, 43h, 20h, 50h, 68h, 1Ah, 01h, 00h, 00h, 8Bh, 0CFh
    db 0E8h, 79h, 64h, 0D9h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 03h, 53h
    db 20h, 52h, 6Ah, 04h, 8Bh, 0CFh, 0E8h, 7Fh, 15h, 0DAh, 0FFh, 8Bh, 43h, 24h, 85h, 0C0h
    db 74h, 12h, 6Ah, 00h, 57h, 50h, 0E8h, 64h, 04h, 0D8h, 0FFh, 83h, 0C4h, 0Ch, 0EBh, 04h
    db 8Bh, 5Ch, 24h, 10h, 6Ah, 01h, 6Ah, 35h, 8Bh, 0CFh, 0E8h, 0FFh, 0Ch, 0DAh, 0FFh, 6Ah
    db 16h, 8Bh, 0CFh, 0E8h, 0F4h, 27h, 0DAh, 0FFh, 8Bh, 8Fh, 04h, 02h, 00h, 00h, 85h, 0C9h
    db 74h, 0Ah, 8Bh, 01h, 6Ah, 08h, 0FFh, 90h, 0FCh, 01h, 00h, 00h, 0C6h, 46h, 1Ch, 01h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 03h, 53h, 0Ch, 89h, 56h, 14h, 8Bh
    db 43h, 28h, 85h, 0C0h, 74h, 0Ch, 6Ah, 00h, 57h, 50h, 0E8h, 10h, 04h, 0D8h, 0FFh, 83h
    db 0C4h, 0Ch, 5Dh, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 59h, 0C3h
?d_00291f20@@YAXXZ ENDP

; ghidra: FUN_006921d0  retail @ 0x002921D0 size 25
public ?d_002921d0@@YAXXZ
?d_002921d0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 6Ah, 5Ah, 0DBh, 0FFh
?d_002921d0@@YAXXZ ENDP

; ghidra: FUN_00692440  retail @ 0x00292440 size 44
public ?d_00292440@@YAXXZ
?d_00292440@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0C3h, 39h, 0D8h, 0FFh, 8Bh, 46h, 20h, 8Bh, 0Dh, 98h, 08h, 2Fh
    db 01h, 50h, 0E8h, 0FCh, 0CDh, 0D8h, 0FFh, 85h, 0C0h, 74h, 08h, 8Bh, 48h, 74h, 89h, 4Eh
    db 20h, 5Eh, 0C3h, 0C7h, 46h, 20h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_00292440@@YAXXZ ENDP

; ghidra: FUN_00692550  retail @ 0x00292550 size 25
public ?d_00292550@@YAXXZ
?d_00292550@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0EAh, 56h, 0DBh, 0FFh
?d_00292550@@YAXXZ ENDP

; ghidra: FUN_006926c0  retail @ 0x002926C0 size 134
public ?d_002926c0@@YAXXZ
?d_002926c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 1Ah, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 18h, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 0Ch, 0E8h, 0F6h, 49h, 0D8h, 0FFh, 0C7h, 46h
    db 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh, 09h, 01h, 83h, 0C8h, 0FFh, 33h
    db 0C9h, 89h, 4Eh, 14h, 89h, 46h, 18h, 89h, 46h, 1Ch, 8Bh, 56h, 08h, 68h, 0FFh, 0FFh
    db 0FFh, 3Fh, 89h, 4Ch, 24h, 14h, 52h, 8Bh, 0CEh, 0C7h, 06h, 0D4h, 0EBh, 0Bh, 01h, 0C7h
    db 46h, 0Ch, 10h, 0EBh, 0Bh, 01h, 0C7h, 46h, 10h, 00h, 0EBh, 0Bh, 01h, 0E8h, 0A8h, 30h
    db 0D8h, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_002926c0@@YAXXZ ENDP

; ghidra: FUN_00692af0  retail @ 0x00292AF0 size 70
public ?d_00292af0@@YAXXZ
?d_00292af0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 8Bh, 88h, 90h, 00h, 00h, 00h, 0F6h, 0C5h, 04h, 74h
    db 33h, 8Bh, 46h, 04h, 8Bh, 48h, 10h, 8Bh, 50h, 0Ch, 68h, 98h, 00h, 00h, 00h, 68h
    db 08h, 0ECh, 0Bh, 01h, 51h, 52h, 0E8h, 93h, 0F0h, 0D6h, 0FFh, 83h, 0C4h, 10h, 83h, 0F8h
    db 01h, 73h, 05h, 0B8h, 01h, 00h, 00h, 00h, 50h, 8Bh, 46h, 08h, 50h, 8Bh, 0CEh, 0E8h
    db 0A6h, 2Ch, 0D8h, 0FFh, 5Eh, 0C3h
?d_00292af0@@YAXXZ ENDP

; ghidra: FUN_00692e00  retail @ 0x00292E00 size 68
public ?d_00292e00@@YAXXZ
?d_00292e00@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 8Bh, 0F1h, 74h, 33h, 8Bh, 4Eh, 20h, 85h
    db 0C9h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 0Dh, 38h, 0F7h, 2Eh, 01h, 6Ah
    db 00h, 57h, 0E8h, 98h, 0F4h, 0D7h, 0FFh, 8Bh, 4Eh, 08h, 89h, 46h, 20h, 8Bh, 51h, 74h
    db 89h, 50h, 08h, 8Bh, 46h, 08h, 8Bh, 4Eh, 20h, 50h, 0E8h, 95h, 0D0h, 0D7h, 0FFh, 5Fh
    db 5Eh, 0C2h, 04h, 00h
?d_00292e00@@YAXXZ ENDP

; ghidra: FUN_00692f00  retail @ 0x00292F00 size 108
public ?d_00292f00@@YAXXZ
?d_00292f00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 0F4h, 8Ah, 48h, 0Ch, 84h, 0C9h, 74h, 0Fh, 8Bh, 4Eh, 0F8h
    db 0F7h, 81h, 28h, 01h, 00h, 00h, 00h, 00h, 02h, 00h, 74h, 49h, 8Ah, 48h, 0Dh, 84h
    db 0C9h, 74h, 0Fh, 8Bh, 56h, 0F8h, 0F7h, 82h, 1Ch, 01h, 00h, 00h, 00h, 00h, 00h, 10h
    db 74h, 33h, 8Ah, 48h, 0Eh, 84h, 0C9h, 74h, 0Ch, 8Bh, 46h, 0F8h, 0F6h, 80h, 44h, 03h
    db 00h, 00h, 01h, 75h, 20h, 8Bh, 4Eh, 10h, 85h, 0C9h, 74h, 19h, 0E8h, 3Bh, 68h, 0D7h
    db 0FFh, 85h, 0C0h, 75h, 10h, 8Bh, 46h, 0F8h, 8Dh, 48h, 38h, 51h, 8Bh, 4Eh, 10h, 50h
    db 0E8h, 0E1h, 0D7h, 0DAh, 0FFh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_00292f00@@YAXXZ ENDP

; ghidra: FUN_00693260  retail @ 0x00293260 size 8
public ?d_00293260@@YAXXZ
?d_00293260@@YAXXZ PROC
    db 83h, 0C1h, 04h, 0E9h, 0D8h, 46h, 5Fh, 00h
?d_00293260@@YAXXZ ENDP

; ghidra: FUN_00693720  retail @ 0x00293720 size 69
public ?d_00293720@@YAXXZ
?d_00293720@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 08h, 2Bh, 0C7h, 0C1h, 0F8h, 03h, 85h, 0C0h
    db 7Eh, 2Dh, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 0D8h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 07h, 8Dh, 4Fh, 04h, 51h, 8Dh, 4Eh, 04h, 89h, 06h, 0E8h, 40h, 45h, 5Fh, 00h
    db 83h, 0C7h, 08h, 83h, 0C6h, 08h, 4Bh, 75h, 0E7h, 8Bh, 0C6h, 5Eh, 5Bh, 5Fh, 0C3h, 8Bh
    db 44h, 24h, 10h, 5Fh, 0C3h
?d_00293720@@YAXXZ ENDP

; ghidra: FUN_006937b0  retail @ 0x002937B0 size 26
public ?d_002937b0@@YAXXZ
?d_002937b0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 68h, 1Ch, 30h, 07h, 01h, 8Dh, 4Eh, 04h, 0C7h, 06h, 00h, 00h, 00h
    db 00h, 0E8h, 0FAh, 53h, 5Fh, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_002937b0@@YAXXZ ENDP

; ghidra: FUN_00693800  retail @ 0x00293800 size 72
public ?d_00293800@@YAXXZ
?d_00293800@@YAXXZ PROC
    db 83h, 0ECh, 5Ch, 53h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 04h, 57h, 8Bh, 7Eh, 08h, 8Dh, 4Ch
    db 24h, 0Ch, 0E8h, 0BEh, 91h, 0D9h, 0FFh, 0DBh, 43h, 14h, 8Bh, 46h, 48h, 89h, 44h, 24h
    db 14h, 8Dh, 44h, 24h, 0Ch, 0D9h, 5Ch, 24h, 28h, 0C7h, 44h, 24h, 1Ch, 06h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 24h, 03h, 00h, 00h, 00h, 8Bh, 17h, 50h, 8Bh, 0CFh, 0FFh, 52h
    db 34h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 5Ch, 0C3h
?d_00293800@@YAXXZ ENDP

; ghidra: FUN_00693e50  retail @ 0x00293E50 size 463
public ?d_00293e50@@YAXXZ
?d_00293e50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FEh, 1Bh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 64h, 53h, 55h, 8Bh, 69h, 04h, 56h, 8Bh, 71h
    db 08h, 0BBh, 01h, 00h, 00h, 00h, 53h, 56h, 89h, 59h, 28h, 0E8h, 5Ah, 19h, 0D8h, 0FFh
    db 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch, 24h, 10h, 51h, 8Dh, 54h, 24h, 10h, 89h, 4Ch, 24h
    db 18h, 83h, 0C8h, 08h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 14h, 0E8h, 47h, 0C9h, 0D9h, 0FFh
    db 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch, 24h, 10h, 51h, 8Dh, 54h, 24h, 10h, 89h, 4Ch, 24h
    db 18h, 83h, 0C8h, 20h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 14h, 0E8h, 27h, 0C9h, 0D9h, 0FFh
    db 33h, 0C9h, 8Bh, 0C1h, 89h, 4Ch, 24h, 1Ch, 53h, 8Dh, 54h, 24h, 1Ch, 89h, 4Ch, 24h
    db 24h, 0Dh, 00h, 08h, 00h, 00h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 20h, 0E8h, 05h, 0C9h
    db 0D9h, 0FFh, 8Bh, 86h, 18h, 01h, 00h, 00h, 84h, 0E4h, 78h, 12h, 0Dh, 00h, 80h, 00h
    db 00h, 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 1Fh, 0DAh, 0D8h, 0FFh, 6Ah, 00h
    db 8Bh, 0CEh, 0E8h, 38h, 0A4h, 0D8h, 0FFh, 84h, 1Dh, 74h, 0FFh, 2Eh, 01h, 75h, 2Bh, 09h
    db 1Dh, 74h, 0FFh, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 0F4h, 0Ch, 09h, 01h
    db 0C7h, 44h, 24h, 7Ch, 00h, 00h, 00h, 00h, 0E8h, 0AAh, 6Eh, 0DAh, 0FFh, 0A3h, 70h, 0FFh
    db 2Eh, 01h, 0C7h, 44h, 24h, 78h, 0FFh, 0FFh, 0FFh, 0FFh, 0A1h, 70h, 0FFh, 2Eh, 01h, 57h
    db 50h, 8Bh, 0CEh, 0E8h, 0DBh, 6Eh, 0D9h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h, 14h, 6Ah, 00h
    db 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0EBh, 0ACh, 0D9h, 0FFh, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 53h, 0DCh
    db 0D9h, 0FFh, 8Ah, 45h, 31h, 84h, 0C0h, 5Fh, 74h, 1Fh, 8Bh, 86h, 24h, 01h, 00h, 00h
    db 0A9h, 00h, 00h, 10h, 00h, 74h, 12h, 25h, 0FFh, 0FFh, 0EFh, 0FFh, 8Bh, 0CEh, 89h, 86h
    db 24h, 01h, 00h, 00h, 0E8h, 94h, 0D9h, 0D8h, 0FFh, 8Ah, 45h, 33h, 84h, 0C0h, 74h, 1Fh
    db 8Bh, 86h, 24h, 01h, 00h, 00h, 0A9h, 00h, 00h, 20h, 00h, 74h, 12h, 25h, 0FFh, 0FFh
    db 0DFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 6Eh, 0D9h, 0D8h, 0FFh, 8Ah
    db 45h, 31h, 84h, 0C0h, 75h, 07h, 8Ah, 45h, 33h, 84h, 0C0h, 74h, 0Fh, 8Bh, 16h, 53h
    db 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 0C8h, 0E8h, 6Dh, 94h, 0D9h, 0FFh, 8Dh, 4Ch, 24h, 24h
    db 0E8h, 24h, 5Dh, 0D8h, 0FFh, 8Bh, 0Dh, 0Ch, 06h, 2Fh, 01h, 8Dh, 44h, 24h, 24h, 50h
    db 56h, 6Ah, 0Bh, 89h, 9Ch, 24h, 84h, 00h, 00h, 00h, 0E8h, 5Ch, 97h, 0D8h, 0FFh, 68h
    db 62h, 13h, 44h, 00h, 6Ah, 03h, 6Ah, 18h, 8Dh, 4Ch, 24h, 34h, 51h, 0C7h, 84h, 24h
    db 88h, 00h, 00h, 00h, 02h, 00h, 00h, 00h, 0E8h, 69h, 2Dh, 76h, 00h, 8Bh, 4Ch, 24h
    db 70h, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 70h, 0C3h
?d_00293e50@@YAXXZ ENDP

; ghidra: FUN_006940d0  retail @ 0x002940D0 size 346
_TEXT ENDS
_TEXT$d006940d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x006940D0 size 346
public ?d_002940d0@@YAXXZ
?d_002940d0@@YAXXZ PROC
    db 083h, 0ECh, 060h, 053h, 08Bh, 05Ch, 024h, 068h, 0D9h, 043h, 054h, 056h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 057h, 08Bh, 0F9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 08Bh, 043h, 008h, 089h, 047h, 028h
    db 08Bh, 077h, 0E8h, 08Bh, 046h, 03Ch, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 06Ah, 000h, 06Ah, 000h, 050h, 08Bh, 046h, 038h, 050h, 0FFh, 052h, 04Ch, 083h, 07Bh
    db 010h, 006h, 00Fh, 085h, 00Bh, 001h, 000h, 000h, 084h, 0C0h, 00Fh, 085h, 003h, 001h, 000h, 000h
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 041h, 03Ch, 08Bh, 04Fh, 0E4h, 08Bh, 0D0h, 02Bh, 051h, 020h, 03Bh, 057h, 01Ch, 07Eh, 006h
    db 08Bh, 049h, 01Ch, 089h, 04Fh, 018h, 089h, 047h, 01Ch, 08Bh, 086h, 090h, 000h, 000h, 000h, 0F6h
    db 0C4h, 00Ch, 00Fh, 085h, 0D5h, 000h, 000h, 000h, 0D9h, 047h, 018h, 0D8h, 063h, 050h, 0D9h, 057h
    db 018h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 08Ah, 0BBh, 000h, 000h, 000h, 08Dh, 04Fh, 0E0h
    call ?j_000322d6@@YAXXZ
    db 08Bh, 07Fh, 0E4h, 08Ah, 047h, 034h, 084h, 0C0h, 00Fh, 084h, 094h, 000h, 000h, 000h, 08Bh, 086h
    db 0FCh, 001h, 000h, 000h, 085h, 0C0h, 00Fh, 084h, 086h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 010h
    call ?j_0002c9d5@@YAXXZ
    db 08Bh, 047h, 014h, 099h, 02Bh, 0C2h, 0D1h, 0F8h, 089h, 044h, 024h, 00Ch, 083h, 0F8h, 001h, 0C7h
    db 044h, 024h, 070h, 001h, 000h, 000h, 000h, 08Dh, 044h, 024h, 070h, 07Ch, 004h, 08Dh, 044h, 024h
    db 00Ch, 0DBh, 000h, 08Bh, 056h, 074h, 08Bh, 08Eh, 0FCh, 001h, 000h, 000h, 089h, 054h, 024h, 018h
    db 0D9h, 05Ch, 024h, 02Ch, 0C7h, 044h, 024h, 020h, 006h, 000h, 000h, 000h, 0C7h, 044h, 024h, 028h
    db 003h, 000h, 000h, 000h, 08Bh, 001h, 0FFh, 090h, 004h, 001h, 000h, 000h, 08Bh, 0F8h, 085h, 0FFh
    db 074h, 03Ch, 08Bh, 007h, 08Bh, 030h, 03Bh, 0F0h, 074h, 034h, 08Dh, 049h, 000h, 08Bh, 04Eh, 008h
    db 085h, 0C9h, 08Bh, 036h, 074h, 00Ah, 08Bh, 011h, 08Dh, 044h, 024h, 010h, 050h, 0FFh, 052h, 034h
    db 03Bh, 037h, 075h, 0E9h, 05Fh, 05Eh, 05Bh, 083h, 0C4h, 060h, 0C2h, 004h, 000h, 08Bh, 08Eh, 0FCh
    db 001h, 000h, 000h, 085h, 0C9h, 074h, 007h, 08Bh, 011h, 06Ah, 002h, 0FFh, 052h, 074h, 05Fh, 05Eh
    db 05Bh, 083h, 0C4h, 060h, 0C2h, 004h, 000h
?d_002940d0@@YAXXZ ENDP
_TEXT$d006940d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00694280  retail @ 0x00294280 size 150
public ?d_00294280@@YAXXZ
?d_00294280@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 1Ch, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 0Fh
    db 8Dh, 4Eh, 04h, 0E8h, 88h, 36h, 5Fh, 00h, 83h, 0C6h, 08h, 3Bh, 0F3h, 75h, 0F1h, 8Bh
    db 0Fh, 85h, 0C9h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 37h, 8Bh, 47h, 08h
    db 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Bh, 51h
    db 0E8h, 0CBh, 0DBh, 5Eh, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h, 51h, 0E8h, 0EFh, 0A2h, 59h
    db 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00294280@@YAXXZ ENDP

; ghidra: FUN_00694410  retail @ 0x00294410 size 1163
public ?d_00294410@@YAXXZ
?d_00294410@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 4Eh, 1Ch, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 30h, 0A1h, 98h, 08h, 2Fh, 01h, 53h, 55h, 8Bh
    db 68h, 3Ch, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 34h, 85h, 0C0h, 8Bh, 5Fh, 0F4h, 8Bh, 77h
    db 0F8h, 89h, 5Ch, 24h, 20h, 0Fh, 86h, 0E6h, 02h, 00h, 00h, 3Bh, 0E8h, 0Fh, 82h, 0C6h
    db 02h, 00h, 00h, 0C7h, 47h, 34h, 00h, 00h, 00h, 00h, 8Ah, 43h, 35h, 84h, 0C0h, 0Fh
    db 84h, 0B4h, 02h, 00h, 00h, 8Bh, 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 8Dh, 6Eh, 38h
    db 0C7h, 44h, 24h, 28h, 80h, 96h, 18h, 4Bh, 0C7h, 44h, 24h, 2Ch, 80h, 96h, 18h, 4Bh
    db 0C7h, 44h, 24h, 30h, 80h, 96h, 18h, 4Bh, 89h, 44h, 24h, 24h, 0Fh, 84h, 87h, 02h
    db 00h, 00h, 8Bh, 4Bh, 3Ch, 0D9h, 45h, 00h, 8Bh, 53h, 40h, 89h, 4Ch, 24h, 10h, 0D8h
    db 64h, 24h, 10h, 89h, 54h, 24h, 1Ch, 0E8h, 8Ch, 29h, 76h, 00h, 89h, 44h, 24h, 18h
    db 0DBh, 44h, 24h, 18h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 10h, 0D8h, 45h, 00h, 0D8h
    db 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 45h, 01h, 00h, 00h, 8Bh, 0FFh
    db 0D9h, 45h, 04h, 0D8h, 64h, 24h, 10h, 0E8h, 5Ch, 29h, 76h, 00h, 89h, 44h, 24h, 18h
    db 0DBh, 44h, 24h, 18h, 0D9h, 54h, 24h, 18h, 0D9h, 44h, 24h, 10h, 0D8h, 45h, 04h, 0D9h
    db 0C9h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 8Ah, 0E6h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 54h, 24h, 18h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 8Bh, 5Fh, 0F4h, 52h
    db 8Bh, 54h, 24h, 18h, 52h, 0FFh, 50h, 60h, 0D8h, 5Bh, 38h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 0Fh, 85h, 8Bh, 00h, 00h, 00h, 0D9h, 45h, 08h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h
    db 18h, 0D9h, 5Ch, 24h, 3Ch, 0D9h, 45h, 00h, 89h, 44h, 24h, 34h, 0D8h, 64h, 24h, 34h
    db 89h, 4Ch, 24h, 38h, 0D9h, 45h, 04h, 0D8h, 64h, 24h, 38h, 0D9h, 45h, 00h, 0D8h, 64h
    db 24h, 28h, 0D9h, 45h, 04h, 0D8h, 64h, 24h, 2Ch, 0D9h, 0C2h, 0D8h, 0CBh, 0D9h, 0C4h, 0D8h
    db 0CDh, 0DEh, 0C1h, 0D9h, 0C1h, 0D8h, 0CAh, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0DEh, 0D9h, 0DDh
    db 0D8h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 41h, 0DDh, 0D8h, 75h, 33h, 8Bh, 15h
    db 14h, 0F2h, 2Eh, 01h, 8Bh, 4Ah, 0Ch, 6Ah, 00h, 8Dh, 44h, 24h, 38h, 50h, 55h, 56h
    db 0E8h, 92h, 5Dh, 0DBh, 0FFh, 84h, 0C0h, 74h, 18h, 8Bh, 4Ch, 24h, 34h, 8Bh, 54h, 24h
    db 38h, 8Bh, 44h, 24h, 3Ch, 89h, 4Ch, 24h, 28h, 89h, 54h, 24h, 2Ch, 89h, 44h, 24h
    db 30h, 0D9h, 44h, 24h, 18h, 0D8h, 44h, 24h, 1Ch, 0E8h, 7Ah, 28h, 76h, 00h, 89h, 44h
    db 24h, 18h, 0DBh, 44h, 24h, 18h, 0D9h, 54h, 24h, 18h, 0D9h, 44h, 24h, 10h, 0D8h, 45h
    db 04h, 0D9h, 0C9h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 8Bh, 20h, 0FFh, 0FFh, 0FFh
    db 8Bh, 5Ch, 24h, 20h, 0D9h, 44h, 24h, 14h, 0D8h, 44h, 24h, 1Ch, 0E8h, 47h, 28h, 76h
    db 00h, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h, 18h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h
    db 10h, 0D8h, 45h, 00h, 0D8h, 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 84h, 0BDh
    db 0FEh, 0FFh, 0FFh, 0F6h, 05h, 7Ch, 0FFh, 2Eh, 01h, 01h, 75h, 2Ch, 83h, 0Dh, 7Ch, 0FFh
    db 2Eh, 01h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 0F4h, 0Ch, 09h, 01h, 0C7h, 44h
    db 24h, 4Ch, 00h, 00h, 00h, 00h, 0E8h, 9Ch, 67h, 0DAh, 0FFh, 0A3h, 78h, 0FFh, 2Eh, 01h
    db 0C7h, 44h, 24h, 48h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0Dh, 78h, 0FFh, 2Eh, 01h, 51h, 8Bh
    db 0CEh, 0E8h, 0CDh, 67h, 0D9h, 0FFh, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 6Ah, 00h
    db 8Bh, 0E8h, 8Bh, 44h, 24h, 30h, 6Ah, 00h, 50h, 8Bh, 44h, 24h, 34h, 50h, 0FFh, 52h
    db 4Ch, 84h, 0C0h, 0Fh, 84h, 91h, 00h, 00h, 00h, 8Ah, 43h, 44h, 84h, 0C0h, 74h, 25h
    db 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 1Bh, 8Bh, 11h, 6Ah, 04h, 0FFh, 92h
    db 0FCh, 01h, 00h, 00h, 8Bh, 86h, 04h, 02h, 00h, 00h, 0C6h, 80h, 37h, 03h, 00h, 00h
    db 01h, 0C6h, 47h, 3Ch, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 2Ch, 51h, 8Bh, 4Ch, 24h, 2Ch
    db 83h, 0C1h, 20h, 0E8h, 0B2h, 0FCh, 0D9h, 0FFh, 6Ah, 01h, 68h, 0FFh, 0FFh, 00h, 00h, 0C6h
    db 47h, 30h, 01h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 56h, 0E8h, 5Dh, 0A5h, 0D8h, 0FFh, 6Ah
    db 01h, 6Ah, 03h, 8Bh, 0CEh, 0E8h, 14h, 0E7h, 0D9h, 0FFh, 6Ah, 01h, 6Ah, 05h, 8Bh, 0CEh
    db 0E8h, 09h, 0E7h, 0D9h, 0FFh, 85h, 0EDh, 74h, 30h, 6Ah, 01h, 8Bh, 0CDh, 0E8h, 0C3h, 0D4h
    db 0D9h, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch, 24h, 30h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 3Ch, 0C3h, 85h, 0EDh, 74h, 0Bh, 6Ah, 00h
    db 6Ah, 01h, 8Bh, 0CDh, 0E8h, 2Bh, 0A5h, 0D9h, 0FFh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h
    db 00h, 5Bh, 8Bh, 4Ch, 24h, 30h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 3Ch
    db 0C3h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 85h, 0C9h, 74h, 4Ch, 0E8h, 34h, 00h, 0DBh, 0FFh
    db 84h, 0C0h, 75h, 43h, 8Bh, 46h, 3Ch, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 6Ah
    db 00h, 6Ah, 00h, 50h, 8Bh, 46h, 38h, 50h, 0FFh, 52h, 4Ch, 84h, 0C0h, 74h, 28h, 8Bh
    db 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 41h, 3Ch, 8Bh, 57h, 18h, 8Dh, 4Fh, 18h, 83h, 0C0h
    db 0Fh, 89h, 44h, 24h, 24h, 3Bh, 0D0h, 8Bh, 0C1h, 72h, 04h, 8Dh, 44h, 24h, 24h, 8Bh
    db 10h, 89h, 11h, 0C6h, 47h, 30h, 00h, 8Bh, 47h, 20h, 85h, 0C0h, 74h, 14h, 3Bh, 0E8h
    db 72h, 10h, 8Bh, 43h, 10h, 03h, 0C5h, 8Dh, 4Fh, 0F0h, 89h, 47h, 20h, 0E8h, 0EBh, 0B2h
    db 0D7h, 0FFh, 8Bh, 47h, 1Ch, 85h, 0C0h, 74h, 2Dh, 3Bh, 0E8h, 72h, 29h, 6Ah, 01h, 6Ah
    db 0Bh, 8Bh, 0CEh, 0E8h, 36h, 0E6h, 0D9h, 0FFh, 8Bh, 8Eh, 18h, 01h, 00h, 00h, 0B8h, 00h
    db 80h, 00h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 18h, 01h, 00h, 00h, 8Bh
    db 0CEh, 0E8h, 47h, 0D1h, 0D8h, 0FFh, 8Bh, 47h, 18h, 85h, 0C0h, 0Fh, 84h, 9Fh, 00h, 00h
    db 00h, 3Bh, 0E8h, 0Fh, 82h, 97h, 00h, 00h, 00h, 8Bh, 8Eh, 90h, 00h, 00h, 00h, 0C1h
    db 0E9h, 0Ah, 83h, 0E1h, 02h, 89h, 4Fh, 14h, 8Dh, 6Fh, 0F0h, 8Bh, 0CDh, 0E8h, 5Eh, 0ABh
    db 0D9h, 0FFh, 8Bh, 45h, 34h, 85h, 0C0h, 74h, 13h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh
    db 11h, 50h, 0FFh, 52h, 4Ch, 0C7h, 45h, 34h, 00h, 00h, 00h, 00h, 6Ah, 0Ah, 8Bh, 0CEh
    db 0E8h, 55h, 0D7h, 0D9h, 0FFh, 8Bh, 86h, 18h, 01h, 00h, 00h, 0F6h, 0C4h, 20h, 74h, 12h
    db 25h, 0FFh, 0DFh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 0DBh, 0D0h
    db 0D8h, 0FFh, 8Ah, 43h, 44h, 84h, 0C0h, 74h, 2Ch, 8Ah, 47h, 3Ch, 84h, 0C0h, 74h, 25h
    db 8Bh, 86h, 04h, 02h, 00h, 00h, 85h, 0C0h, 74h, 1Bh, 0C6h, 80h, 37h, 03h, 00h, 00h
    db 00h, 8Bh, 8Eh, 04h, 02h, 00h, 00h, 8Bh, 01h, 6Ah, 00h, 0FFh, 90h, 0FCh, 01h, 00h
    db 00h, 0C6h, 47h, 3Ch, 00h, 8Bh, 8Eh, 00h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 28h
    db 8Dh, 4Fh, 0F0h, 0E8h, 93h, 8Fh, 0DAh, 0FFh, 8Bh, 4Ch, 24h, 40h, 5Fh, 5Eh, 5Dh, 5Bh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 3Ch, 0C3h
?d_00294410@@YAXXZ ENDP

; ghidra: FUN_006949d0  retail @ 0x002949D0 size 268
public ?d_002949d0@@YAXXZ
?d_002949d0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 04h, 8Bh, 4Ch, 24h, 20h, 55h, 56h, 2Bh
    db 03h, 0C1h, 0F8h, 03h, 3Bh, 0C1h, 57h, 89h, 5Ch, 24h, 14h, 89h, 44h, 24h, 10h, 8Dh
    db 4Ch, 24h, 2Ch, 72h, 04h, 8Dh, 4Ch, 24h, 10h, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h
    db 18h, 74h, 2Bh, 8Dh, 04h, 0CDh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 50h
    db 76h, 0Eh, 0E8h, 19h, 0D5h, 5Eh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 16h
    db 0E8h, 1Bh, 9Bh, 59h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h, 0C7h, 44h
    db 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 33h, 8Bh, 6Ch, 24h, 20h, 3Bh, 0F5h, 8Bh, 7Ch
    db 24h, 10h, 74h, 14h, 56h, 57h, 0E8h, 0F3h, 75h, 0D9h, 0FFh, 83h, 0C6h, 08h, 83h, 0C4h
    db 08h, 83h, 0C7h, 08h, 3Bh, 0F5h, 75h, 0ECh, 8Bh, 74h, 24h, 2Ch, 83h, 0FEh, 01h, 75h
    db 13h, 8Bh, 44h, 24h, 24h, 50h, 57h, 0E8h, 0D2h, 75h, 0D9h, 0FFh, 83h, 0C4h, 08h, 83h
    db 0C7h, 08h, 0EBh, 18h, 85h, 0F6h, 76h, 14h, 8Bh, 4Ch, 24h, 24h, 51h, 57h, 0E8h, 0BBh
    db 75h, 0D9h, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 08h, 4Eh, 75h, 0ECh, 8Ah, 44h, 24h, 30h
    db 84h, 0C0h, 75h, 24h, 8Bh, 5Bh, 04h, 3Bh, 0EBh, 74h, 19h, 8Bh, 0F5h, 8Dh, 49h, 00h
    db 56h, 57h, 0E8h, 97h, 75h, 0D9h, 0FFh, 83h, 0C6h, 08h, 83h, 0C4h, 08h, 83h, 0C7h, 08h
    db 3Bh, 0F3h, 75h, 0ECh, 8Bh, 5Ch, 24h, 14h, 8Bh, 0CBh, 0E8h, 0F4h, 0D4h, 0D7h, 0FFh, 8Bh
    db 44h, 24h, 10h, 8Bh, 54h, 24h, 18h, 89h, 7Bh, 04h, 5Fh, 89h, 03h, 5Eh, 8Dh, 04h
    db 0D0h, 5Dh, 89h, 43h, 08h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 14h, 00h
?d_002949d0@@YAXXZ ENDP

; ghidra: FUN_00694d00  retail @ 0x00294D00 size 294
public ?d_00294d00@@YAXXZ
?d_00294d00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 1Ch, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 68h, 1Ch, 30h, 07h, 01h, 8Dh
    db 4Ch, 24h, 10h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 90h, 3Eh, 5Fh, 00h
    db 8Bh, 74h, 24h, 28h, 8Bh, 86h, 1Ch, 04h, 00h, 00h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 24h, 00h, 00h, 00h, 00h, 0E8h, 26h, 0BCh, 5Bh, 00h, 8Bh, 1Dh, 3Ch, 93h, 35h, 01h
    db 68h, 24h, 28h, 0Ah, 01h, 50h, 0FFh, 0D3h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 23h, 68h
    db 0CCh, 0EFh, 0Bh, 01h, 8Dh, 44h, 24h, 14h, 6Ah, 03h, 50h, 0E8h, 90h, 0B8h, 5Bh, 00h
    db 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 14h, 51h, 0E8h, 7Eh, 1Fh
    db 76h, 00h, 57h, 8Bh, 7Ch, 24h, 30h, 6Ah, 00h, 8Dh, 54h, 24h, 10h, 52h, 57h, 56h
    db 0E8h, 0B2h, 0FDh, 0D6h, 0FFh, 8Bh, 86h, 1Ch, 04h, 00h, 00h, 83h, 0C4h, 10h, 50h, 8Bh
    db 0CEh, 0E8h, 1Ah, 0BCh, 5Bh, 00h, 85h, 0C0h, 74h, 21h, 68h, 0C4h, 0EFh, 0Bh, 01h, 50h
    db 0FFh, 0D3h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 12h, 50h, 8Bh, 0CEh, 0E8h, 0FFh, 0BBh, 5Bh
    db 00h, 50h, 8Dh, 4Ch, 24h, 14h, 0E8h, 0EEh, 3Dh, 0D9h, 0FFh, 8Bh, 4Fh, 2Ch, 8Bh, 47h
    db 28h, 8Dh, 77h, 24h, 3Bh, 0C1h, 5Fh, 8Dh, 4Ch, 24h, 08h, 74h, 15h, 51h, 50h, 0E8h
    db 5Ah, 72h, 0D9h, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h, 08h, 89h, 46h, 04h
    db 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 30h, 52h, 51h, 50h, 8Bh, 0CEh, 0E8h
    db 0F4h, 4Eh, 0D9h, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 2Bh, 2Bh, 5Fh, 00h, 8Bh, 4Ch, 24h, 18h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_00294d00@@YAXXZ ENDP

; ghidra: FUN_00694ea0  retail @ 0x00294EA0 size 25
public ?d_00294ea0@@YAXXZ
?d_00294ea0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 9Ah, 2Dh, 0DBh, 0FFh
?d_00294ea0@@YAXXZ ENDP

; ghidra: FUN_006950d0  retail @ 0x002950D0 size 683
public ?d_002950d0@@YAXXZ
?d_002950d0@@YAXXZ PROC
    db 83h, 0ECh, 48h, 56h, 57h, 8Bh, 0F9h, 80h, 7Fh, 10h, 01h, 75h, 41h, 8Bh, 77h, 0F8h
    db 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 6Ah, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 8Bh
    db 56h, 3Ch, 83h, 0C6h, 38h, 52h, 8Bh, 16h, 52h, 0FFh, 50h, 4Ch, 8Bh, 06h, 8Bh, 54h
    db 24h, 08h, 89h, 44h, 24h, 14h, 8Bh, 4Eh, 04h, 8Dh, 44h, 24h, 14h, 89h, 4Ch, 24h
    db 18h, 8Bh, 4Fh, 0F8h, 50h, 89h, 54h, 24h, 20h, 0E8h, 89h, 50h, 0DAh, 0FFh, 8Bh, 4Fh
    db 0F8h, 8Bh, 11h, 0FFh, 52h, 28h, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 40h, 02h, 00h, 00h
    db 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 0DBh, 40h, 3Ch, 85h, 0C9h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 0D9h, 05h, 8Ch, 0F4h, 0Bh, 01h, 0D8h, 0C9h, 8Bh, 8Eh, 0A0h
    db 01h, 00h, 00h, 8Bh, 96h, 98h, 01h, 00h, 00h, 8Bh, 86h, 9Ch, 01h, 00h, 00h, 0D9h
    db 0FEh, 89h, 4Ch, 24h, 28h, 8Bh, 8Eh, 0ACh, 01h, 00h, 00h, 89h, 54h, 24h, 20h, 8Bh
    db 96h, 0A4h, 01h, 00h, 00h, 89h, 44h, 24h, 24h, 8Bh, 86h, 0A8h, 01h, 00h, 00h, 89h
    db 4Ch, 24h, 34h, 8Bh, 8Eh, 0B8h, 01h, 00h, 00h, 89h, 54h, 24h, 2Ch, 8Bh, 96h, 0B0h
    db 01h, 00h, 00h, 89h, 44h, 24h, 30h, 8Bh, 86h, 0B4h, 01h, 00h, 00h, 89h, 4Ch, 24h
    db 40h, 8Bh, 8Eh, 0C4h, 01h, 00h, 00h, 89h, 54h, 24h, 38h, 8Bh, 96h, 0BCh, 01h, 00h
    db 00h, 89h, 44h, 24h, 3Ch, 8Bh, 86h, 0C0h, 01h, 00h, 00h, 89h, 4Ch, 24h, 4Ch, 8Dh
    db 4Ch, 24h, 20h, 89h, 54h, 24h, 44h, 89h, 44h, 24h, 48h, 0D8h, 0Dh, 70h, 0A6h, 0Bh
    db 01h, 0D9h, 5Ch, 24h, 0Ch, 0D8h, 0Dh, 88h, 0F4h, 0Bh, 01h, 0D9h, 0FEh, 0D8h, 0Dh, 70h
    db 0A6h, 0Bh, 01h, 0D9h, 5Ch, 24h, 10h, 0E8h, 0B4h, 16h, 64h, 00h, 0D9h, 0C0h, 0C7h, 44h
    db 24h, 2Ch, 00h, 00h, 00h, 00h, 0D9h, 0FFh, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 00h, 00h
    db 0C7h, 44h, 24h, 4Ch, 00h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 08h, 0D9h, 0FEh, 0D9h, 05h
    db 50h, 53h, 07h, 01h, 0D8h, 0C9h, 0D9h, 44h, 24h, 08h, 0D9h, 0C0h, 0D8h, 0C2h, 0D9h, 5Ch
    db 24h, 20h, 0D9h, 44h, 24h, 08h, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 54h, 24h, 08h
    db 0D8h, 0E3h, 0D9h, 5Ch, 24h, 24h, 0D9h, 0CAh, 0D8h, 44h, 24h, 08h, 0D9h, 5Ch, 24h, 30h
    db 0D9h, 0C9h, 0D8h, 0E1h, 0D9h, 5Ch, 24h, 34h, 0D9h, 44h, 24h, 08h, 0D8h, 0C1h, 0D9h, 5Ch
    db 24h, 40h, 0D9h, 44h, 24h, 08h, 0D8h, 0E1h, 0D9h, 0C9h, 0DDh, 0D8h, 0D9h, 44h, 24h, 0Ch
    db 0D9h, 0C0h, 0D9h, 0FEh, 8Bh, 54h, 24h, 30h, 89h, 54h, 24h, 0Ch, 0D9h, 0C9h, 0D9h, 0FFh
    db 0D9h, 44h, 24h, 20h, 0D9h, 0C2h, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 0C2h, 0D8h, 4Ch
    db 24h, 20h, 0D8h, 0E1h, 0D9h, 5Ch, 24h, 20h, 0D9h, 0C2h, 0D8h, 0Dh, 50h, 53h, 07h, 01h
    db 0D9h, 5Ch, 24h, 08h, 0D9h, 0C9h, 0D8h, 0CBh, 0D8h, 44h, 24h, 08h, 0D9h, 5Ch, 24h, 28h
    db 0D9h, 44h, 24h, 30h, 0D8h, 0CAh, 0D8h, 0E1h, 0D9h, 5Ch, 24h, 30h, 0DDh, 0D8h, 0D9h, 44h
    db 24h, 0Ch, 0D8h, 0CAh, 0D8h, 44h, 24h, 08h, 0D9h, 5Ch, 24h, 38h, 0D9h, 44h, 24h, 40h
    db 0D9h, 44h, 24h, 40h, 0D8h, 0CAh, 0D8h, 0E3h, 0D9h, 5Ch, 24h, 40h, 0D8h, 0CAh, 0D8h, 0C1h
    db 0D9h, 0CAh, 0D9h, 0C9h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 44h, 24h, 10h, 0D9h, 0C0h, 0D9h, 0FEh
    db 0D9h, 5Ch, 24h, 08h, 0D9h, 0FFh, 0D9h, 44h, 24h, 24h, 0D9h, 44h, 24h, 28h, 0D8h, 4Ch
    db 24h, 08h, 0D9h, 0C2h, 0D8h, 4Ch, 24h, 24h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 24h, 0D9h, 44h
    db 24h, 28h, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 08h, 0DEh, 0E9h, 0D9h, 5Ch, 24h, 28h
    db 0D9h, 44h, 24h, 34h, 0D9h, 44h, 24h, 38h, 0D8h, 4Ch, 24h, 08h, 0D9h, 44h, 24h, 34h
    db 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 34h, 0D9h, 44h, 24h, 38h, 0D8h, 0CAh, 0D9h, 0C9h
    db 0D8h, 4Ch, 24h, 08h, 0DEh, 0E9h, 6Ah, 00h, 8Dh, 44h, 24h, 24h, 50h, 0D9h, 5Ch, 24h
    db 40h, 0D9h, 0C2h, 8Bh, 0CEh, 0D9h, 0C2h, 0D8h, 4Ch, 24h, 10h, 0D9h, 0CCh, 0D8h, 0CAh, 0DEh
    db 0C4h, 0D9h, 0CBh, 0D9h, 5Ch, 24h, 4Ch, 0D9h, 0C9h, 0D8h, 0C9h, 0D9h, 0CAh, 0D8h, 4Ch, 24h
    db 10h, 0DEh, 0EAh, 0D9h, 0C9h, 0D9h, 5Ch, 24h, 50h, 0DDh, 0D8h, 0E8h, 60h, 57h, 0DAh, 0FFh
    db 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 48h, 0C3h
?d_002950d0@@YAXXZ ENDP

; ghidra: FUN_006954c0  retail @ 0x002954C0 size 25
public ?d_002954c0@@YAXXZ
?d_002954c0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 7Ah, 27h, 0DBh, 0FFh
?d_002954c0@@YAXXZ ENDP

; ghidra: FUN_006956a0  retail @ 0x002956A0 size 102
public ?d_002956a0@@YAXXZ
?d_002956a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 13h, 0EEh, 0D6h, 0FFh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 48h, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h
    db 0Ch, 88h, 44h, 24h, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh
    db 16h, 8Dh, 47h, 20h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh
    db 47h, 21h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 47h, 24h
    db 50h, 8Bh, 0CEh, 0FFh, 52h, 60h, 8Bh, 16h, 83h, 0C7h, 30h, 57h, 8Bh, 0CEh, 0FFh, 52h
    db 74h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_002956a0@@YAXXZ ENDP

; ghidra: FUN_00695ac0  retail @ 0x00295AC0 size 25
public ?d_00295ac0@@YAXXZ
?d_00295ac0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 7Ah, 21h, 0DBh, 0FFh
?d_00295ac0@@YAXXZ ENDP

; ghidra: FUN_00695b20  retail @ 0x00295B20 size 95
public ?d_00295b20@@YAXXZ
?d_00295b20@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 50h, 51h, 8Bh, 0CEh, 0E8h
    db 0B0h, 15h, 0D8h, 0FFh, 0C7h, 46h, 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh
    db 09h, 01h, 33h, 0C0h, 89h, 46h, 14h, 89h, 46h, 20h, 88h, 46h, 30h, 88h, 46h, 31h
    db 88h, 46h, 32h, 83h, 0C9h, 0FFh, 89h, 4Eh, 18h, 89h, 4Eh, 1Ch, 0C7h, 06h, 0E4h, 0F7h
    db 0Bh, 01h, 0C7h, 46h, 0Ch, 20h, 0F7h, 0Bh, 01h, 0C7h, 46h, 10h, 14h, 0F7h, 0Bh, 01h
    db 89h, 46h, 24h, 89h, 46h, 28h, 89h, 46h, 2Ch, 8Bh, 0C6h, 5Eh, 0C2h, 08h, 00h
?d_00295b20@@YAXXZ ENDP

; ghidra: FUN_00695d30  retail @ 0x00295D30 size 44
public ?d_00295d30@@YAXXZ
?d_00295d30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0D3h, 00h, 0D8h, 0FFh, 8Bh, 46h, 20h, 8Bh, 0Dh, 98h, 08h, 2Fh
    db 01h, 50h, 0E8h, 0Ch, 95h, 0D8h, 0FFh, 85h, 0C0h, 74h, 08h, 8Bh, 48h, 74h, 89h, 4Eh
    db 20h, 5Eh, 0C3h, 0C7h, 46h, 20h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_00295d30@@YAXXZ ENDP

; ghidra: FUN_00695d70  retail @ 0x00295D70 size 334
public ?d_00295d70@@YAXXZ
?d_00295d70@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 57h, 8Bh, 0F9h, 8Ah, 47h, 20h, 33h, 0DBh, 3Ah, 0C3h, 0Fh, 84h
    db 2Fh, 01h, 00h, 00h, 38h, 5Fh, 21h, 55h, 56h, 0Fh, 84h, 1Fh, 01h, 00h, 00h, 8Bh
    db 47h, 10h, 3Bh, 0C3h, 8Bh, 77h, 0F8h, 74h, 47h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h
    db 0E8h, 0AEh, 94h, 0D8h, 0FFh, 8Bh, 0E8h, 3Bh, 0EBh, 74h, 35h, 8Dh, 5Dh, 38h, 53h, 8Bh
    db 0CEh, 0E8h, 0F1h, 43h, 0DAh, 0FFh, 8Bh, 0CDh, 0E8h, 34h, 42h, 0D8h, 0FFh, 88h, 47h, 22h
    db 8Bh, 03h, 83h, 0C7h, 14h, 89h, 07h, 8Bh, 4Bh, 04h, 89h, 4Fh, 04h, 8Bh, 53h, 08h
    db 5Eh, 5Dh, 89h, 57h, 08h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C3h
    db 8Bh, 0CEh, 0E8h, 78h, 50h, 0D9h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 28h, 85h, 0C0h
    db 74h, 0Fh, 8Bh, 16h, 53h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 0C8h, 0E8h, 36h, 25h, 0D7h
    db 0FFh, 6Ah, 04h, 8Bh, 0CEh, 0E8h, 70h, 0C1h, 0D9h, 0FFh, 53h, 8Bh, 0CEh, 0E8h, 58h, 0C6h
    db 0DAh, 0FFh, 6Ah, 03h, 8Bh, 0CEh, 0E8h, 5Fh, 0C1h, 0D9h, 0FFh, 8Bh, 86h, 04h, 02h, 00h
    db 00h, 3Bh, 0C3h, 74h, 0Ah, 6Ah, 02h, 8Dh, 48h, 20h, 0E8h, 41h, 0EFh, 0D8h, 0FFh, 38h
    db 5Fh, 22h, 74h, 71h, 8Bh, 47h, 0F4h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 83h, 0C0h, 0Ch
    db 50h, 0E8h, 1Ah, 27h, 0D9h, 0FFh, 3Bh, 0C3h, 74h, 5Bh, 33h, 0C9h, 89h, 4Ch, 24h, 10h
    db 89h, 4Ch, 24h, 14h, 53h, 89h, 4Ch, 24h, 1Ch, 8Bh, 8Eh, 3Ch, 02h, 00h, 00h, 8Dh
    db 54h, 24h, 14h, 52h, 51h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 50h, 0E8h, 0D9h, 0EAh, 0DAh
    db 0FFh, 8Bh, 0E8h, 8Dh, 47h, 14h, 50h, 8Bh, 0CDh, 0E8h, 29h, 43h, 0DAh, 0FFh, 8Bh, 8Dh
    db 0FCh, 01h, 00h, 00h, 8Bh, 11h, 6Ah, 01h, 56h, 0FFh, 92h, 84h, 00h, 00h, 00h, 84h
    db 0C0h, 74h, 12h, 8Bh, 0ADh, 0FCh, 01h, 00h, 00h, 8Bh, 45h, 00h, 56h, 8Bh, 0CDh, 0FFh
    db 90h, 88h, 00h, 00h, 00h, 89h, 5Fh, 10h, 88h, 5Fh, 21h, 88h, 5Fh, 20h, 5Eh, 88h
    db 5Fh, 22h, 5Dh, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_00295d70@@YAXXZ ENDP

; ghidra: FUN_00696250  retail @ 0x00296250 size 32
public ?d_00296250@@YAXXZ
?d_00296250@@YAXXZ PROC
    db 0C7h, 41h, 20h, 40h, 0F9h, 0Bh, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0E3h, 19h, 0DBh, 0FFh
?d_00296250@@YAXXZ ENDP

; ghidra: FUN_00696280  retail @ 0x00296280 size 44
public ?d_00296280@@YAXXZ
?d_00296280@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 65h, 84h, 0C0h, 74h, 20h, 8Bh, 0Dh, 44h, 10h, 2Fh, 01h
    db 56h, 0E8h, 0B0h, 0ACh, 0D7h, 0FFh, 8Bh, 46h, 08h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 50h, 8Bh
    db 0CEh, 0E8h, 34h, 0F5h, 0D7h, 0FFh, 0C6h, 46h, 65h, 00h, 5Eh, 0C3h
?d_00296280@@YAXXZ ENDP

; ghidra: FUN_00696420  retail @ 0x00296420 size 11
public ?d_00296420@@YAXXZ
?d_00296420@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 89h, 08h, 0C2h, 08h, 00h
?d_00296420@@YAXXZ ENDP

; ghidra: FUN_00696550  retail @ 0x00296550 size 44
public ?d_00296550@@YAXXZ
?d_00296550@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 65h, 84h, 0C0h, 74h, 20h, 8Bh, 0Dh, 44h, 10h, 2Fh, 01h
    db 56h, 0E8h, 0E0h, 0A9h, 0D7h, 0FFh, 8Bh, 46h, 08h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 50h, 8Bh
    db 0CEh, 0E8h, 64h, 0F2h, 0D7h, 0FFh, 0C6h, 46h, 65h, 00h, 5Eh, 0C3h
?d_00296550@@YAXXZ ENDP

; ghidra: FUN_00696800  retail @ 0x00296800 size 152
public ?d_00296800@@YAXXZ
?d_00296800@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 91h, 1Dh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 56h, 57h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h
    db 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 23h, 80h, 0D8h, 0FFh, 8Bh, 3Dh, 0A0h, 0FFh, 2Eh
    db 01h, 8Bh, 77h, 08h, 3Bh, 0F7h, 0C7h, 44h, 24h, 20h, 01h, 00h, 00h, 00h, 74h, 1Fh
    db 8Bh, 46h, 10h, 83h, 0C0h, 08h, 50h, 8Dh, 4Ch, 24h, 10h, 0E8h, 0C4h, 0B1h, 0D6h, 0FFh
    db 56h, 0E8h, 1Ah, 50h, 59h, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h, 3Bh, 0F7h, 75h, 0E1h, 8Bh
    db 74h, 24h, 28h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 0CEh, 0E8h, 0FEh, 87h, 0D9h, 0FFh, 8Dh
    db 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 08h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 20h, 00h
    db 0E8h, 44h, 19h, 0D8h, 0FFh, 8Bh, 4Ch, 24h, 18h, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_00296800@@YAXXZ ENDP

; ghidra: FUN_006968c0  retail @ 0x002968C0 size 274
public ?d_002968c0@@YAXXZ
?d_002968c0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 55h, 8Bh, 0E9h, 8Ah, 45h, 55h, 84h, 0C0h, 56h, 8Bh, 75h, 0F4h, 89h
    db 74h, 24h, 10h, 75h, 0Dh, 8Bh, 46h, 18h, 6Ah, 54h, 68h, 20h, 0F8h, 0Bh, 01h, 50h
    db 0EBh, 12h, 8Bh, 4Dh, 0F8h, 85h, 0C9h, 75h, 22h, 8Bh, 56h, 18h, 6Ah, 54h, 68h, 20h
    db 0F8h, 0Bh, 01h, 52h, 6Ah, 00h, 0E8h, 0B3h, 0B2h, 0D6h, 0FFh, 8Bh, 4Eh, 14h, 83h, 0C4h
    db 10h, 5Eh, 8Dh, 44h, 08h, 01h, 5Dh, 83h, 0C4h, 0Ch, 0C3h, 53h, 57h, 8Dh, 91h, 10h
    db 01h, 00h, 00h, 6Ah, 00h, 8Dh, 79h, 38h, 89h, 54h, 24h, 18h, 8Dh, 99h, 90h, 00h
    db 00h, 00h, 0E8h, 0F4h, 0D1h, 0D6h, 0FFh, 8Dh, 75h, 14h, 56h, 8Bh, 0CFh, 88h, 44h, 24h
    db 17h, 0E8h, 3Ch, 74h, 0D8h, 0FFh, 84h, 0C0h, 74h, 29h, 8Bh, 4Ch, 24h, 14h, 8Dh, 45h
    db 20h, 50h, 0E8h, 5Ah, 0F3h, 0D9h, 0FFh, 84h, 0C0h, 75h, 18h, 8Dh, 4Dh, 48h, 51h, 8Bh
    db 0CBh, 0E8h, 04h, 0C3h, 0D8h, 0FFh, 84h, 0C0h, 75h, 09h, 8Ah, 54h, 24h, 13h, 3Ah, 55h
    db 54h, 74h, 47h, 8Bh, 0Dh, 44h, 10h, 2Fh, 01h, 8Dh, 45h, 0F0h, 50h, 0E8h, 0AAh, 0Ah
    db 0D9h, 0FFh, 8Bh, 0Fh, 89h, 0Eh, 8Bh, 57h, 04h, 89h, 56h, 04h, 8Bh, 47h, 08h, 89h
    db 46h, 08h, 8Bh, 74h, 24h, 14h, 8Dh, 7Dh, 20h, 0B9h, 0Ah, 00h, 00h, 00h, 0F3h, 0A5h
    db 8Bh, 13h, 8Dh, 4Dh, 48h, 89h, 11h, 8Bh, 43h, 04h, 89h, 41h, 04h, 8Bh, 53h, 08h
    db 8Ah, 44h, 24h, 13h, 89h, 51h, 08h, 88h, 45h, 54h, 8Bh, 74h, 24h, 18h, 8Bh, 4Eh
    db 18h, 6Ah, 54h, 68h, 20h, 0F8h, 0Bh, 01h, 51h, 6Ah, 00h, 0E8h, 0EEh, 0B1h, 0D6h, 0FFh
    db 8Bh, 56h, 14h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 8Dh, 44h, 10h, 01h, 5Dh, 83h, 0C4h
    db 0Ch, 0C3h
?d_002968c0@@YAXXZ ENDP

; ghidra: FUN_00696b90  retail @ 0x00296B90 size 179
public ?d_00296b90@@YAXXZ
?d_00296b90@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 10h, 56h, 8Bh, 74h, 24h, 18h, 57h, 8Bh, 0F9h, 3Bh, 1Fh, 74h
    db 3Dh, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 75h, 0Fh, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 75h
    db 2Dh, 8Bh, 06h, 3Bh, 43h, 10h, 72h, 26h, 6Ah, 14h, 0E8h, 81h, 79h, 59h, 00h, 8Dh
    db 48h, 10h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 04h, 8Bh, 16h, 89h, 11h, 89h, 43h, 0Ch
    db 8Bh, 0Fh, 3Bh, 59h, 0Ch, 8Bh, 0F0h, 75h, 37h, 89h, 41h, 0Ch, 0EBh, 32h, 6Ah, 14h
    db 0E8h, 5Bh, 79h, 59h, 00h, 8Dh, 48h, 10h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 04h, 8Bh
    db 16h, 89h, 11h, 89h, 43h, 08h, 8Bh, 0Fh, 3Bh, 0D9h, 8Bh, 0F0h, 75h, 0Ah, 89h, 41h
    db 04h, 8Bh, 0Fh, 89h, 41h, 0Ch, 0EBh, 08h, 3Bh, 59h, 08h, 75h, 03h, 89h, 41h, 08h
    db 89h, 5Eh, 04h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 0C7h, 46h, 0Ch, 00h, 00h, 00h
    db 00h, 8Bh, 17h, 83h, 0C2h, 04h, 52h, 56h, 0E8h, 0A3h, 5Dh, 59h, 00h, 8Bh, 47h, 04h
    db 83h, 0C4h, 08h, 40h, 89h, 47h, 04h, 8Bh, 44h, 24h, 10h, 5Fh, 89h, 30h, 5Eh, 5Bh
    db 0C2h, 14h, 00h
?d_00296b90@@YAXXZ ENDP

; ghidra: FUN_00696ed0  retail @ 0x00296ED0 size 145
public ?d_00296ed0@@YAXXZ
?d_00296ed0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 03h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 46h, 10h, 0Fh, 92h, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 15h, 57h, 0E8h, 0C0h, 49h, 59h, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 10h, 3Bh, 13h, 73h, 24h, 6Ah, 00h, 53h, 57h, 56h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 0A7h, 5Eh, 0D7h, 0FFh, 8Bh, 08h, 8Bh, 44h, 24h
    db 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h, 08h
    db 00h
?d_00296ed0@@YAXXZ ENDP

; ghidra: FUN_00696f90  retail @ 0x00296F90 size 131
public ?d_00296f90@@YAXXZ
?d_00296f90@@YAXXZ PROC
    db 57h, 8Bh, 0F9h, 8Ah, 47h, 65h, 84h, 0C0h, 75h, 77h, 8Bh, 47h, 08h, 0F7h, 80h, 94h
    db 00h, 00h, 00h, 00h, 00h, 08h, 00h, 75h, 68h, 53h, 56h, 0C6h, 47h, 65h, 01h, 8Bh
    db 0Dh, 44h, 10h, 2Fh, 01h, 57h, 0E8h, 0AFh, 36h, 0DBh, 0FFh, 8Bh, 77h, 04h, 8Bh, 4Eh
    db 18h, 8Bh, 5Fh, 08h, 6Ah, 54h, 68h, 20h, 0F8h, 0Bh, 01h, 51h, 6Ah, 00h, 0E8h, 0DBh
    db 0ABh, 0D6h, 0FFh, 8Bh, 56h, 14h, 83h, 0C4h, 10h, 8Dh, 44h, 10h, 01h, 50h, 53h, 8Bh
    db 0CFh, 0E8h, 0F4h, 0E7h, 0D7h, 0FFh, 8Bh, 47h, 08h, 8Dh, 48h, 38h, 8Bh, 31h, 8Dh, 57h
    db 24h, 89h, 32h, 8Bh, 71h, 04h, 89h, 72h, 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 8Dh
    db 0B0h, 10h, 01h, 00h, 00h, 83h, 0C7h, 30h, 0B9h, 0Ah, 00h, 00h, 00h, 0F3h, 0A5h, 5Eh
    db 5Bh, 5Fh, 0C3h
?d_00296f90@@YAXXZ ENDP

; ghidra: FUN_006972b0  retail @ 0x002972B0 size 144
public ?d_002972b0@@YAXXZ
?d_002972b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 33h, 1Eh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 24h
    db 0C7h, 06h, 0B8h, 96h, 08h, 01h, 8Bh, 47h, 04h, 89h, 74h, 24h, 08h, 89h, 46h, 04h
    db 8Dh, 4Fh, 08h, 51h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0C7h
    db 06h, 60h, 0FAh, 0Bh, 01h, 0E8h, 73h, 7Dh, 0D9h, 0FFh, 8Bh, 57h, 14h, 89h, 56h, 14h
    db 8Bh, 47h, 18h, 89h, 46h, 18h, 66h, 8Bh, 4Fh, 1Ch, 8Dh, 54h, 24h, 24h, 52h, 8Dh
    db 44h, 24h, 10h, 66h, 89h, 4Eh, 1Ch, 50h, 0B9h, 0A0h, 0FFh, 2Eh, 01h, 0C6h, 44h, 24h
    db 24h, 01h, 89h, 74h, 24h, 2Ch, 0E8h, 57h, 44h, 0DAh, 0FFh, 8Bh, 4Ch, 24h, 14h, 5Fh
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_002972b0@@YAXXZ ENDP

; ghidra: FUN_006974d0  retail @ 0x002974D0 size 32
public ?d_002974d0@@YAXXZ
?d_002974d0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0D8h, 0FAh, 0Bh, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 63h, 07h, 0DBh, 0FFh
?d_002974d0@@YAXXZ ENDP

; ghidra: FUN_00697620  retail @ 0x00297620 size 17
public ?d_00297620@@YAXXZ
?d_00297620@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 48h, 0FBh, 0Bh, 01h, 0E8h, 0F0h, 92h, 5Bh, 00h
    db 0C3h
?d_00297620@@YAXXZ ENDP

; ghidra: FUN_00697820  retail @ 0x00297820 size 89
public ?d_00297820@@YAXXZ
?d_00297820@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 04h, 8Bh, 43h, 20h, 3Bh, 43h, 24h, 74h, 45h, 8Bh
    db 4Eh, 08h, 8Bh, 11h, 57h, 0FFh, 52h, 28h, 8Bh, 0F8h, 85h, 0FFh, 74h, 35h, 8Bh, 46h
    db 08h, 85h, 0C0h, 74h, 2Eh, 8Bh, 73h, 20h, 3Bh, 73h, 24h, 74h, 1Fh, 55h, 8Bh, 6Ch
    db 24h, 14h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 55h, 56h, 8Bh, 0CFh, 0E8h, 65h, 19h, 0DAh
    db 0FFh, 8Bh, 43h, 24h, 83h, 0C6h, 04h, 3Bh, 0F0h, 75h, 0E7h, 5Dh, 8Bh, 0CFh, 0E8h, 0DCh
    db 2Dh, 0D8h, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_00297820@@YAXXZ ENDP

; ghidra: FUN_00697890  retail @ 0x00297890 size 8
public ?d_00297890@@YAXXZ
?d_00297890@@YAXXZ PROC
    db 6Ah, 00h, 0E8h, 0C6h, 0C8h, 0D9h, 0FFh, 0C3h
?d_00297890@@YAXXZ ENDP

; ghidra: FUN_00697de0  retail @ 0x00297DE0 size 25
public ?d_00297de0@@YAXXZ
?d_00297de0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 5Ah, 0FEh, 0DAh, 0FFh
?d_00297de0@@YAXXZ ENDP

; ghidra: FUN_00697e90  retail @ 0x00297E90 size 26
public ?d_00297e90@@YAXXZ
?d_00297e90@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 0A8h, 0FEh, 0Bh, 01h, 89h, 48h, 08h, 89h, 48h, 0Ch
    db 88h, 48h, 10h, 88h, 48h, 11h, 89h, 48h, 14h, 0C3h
?d_00297e90@@YAXXZ ENDP

; ghidra: FUN_00697f10  retail @ 0x00297F10 size 70
public ?d_00297f10@@YAXXZ
?d_00297f10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 48h, 0Ch, 8Bh, 40h, 08h, 6Ah, 74h, 68h, 0B8h
    db 0FDh, 0Bh, 01h, 51h, 50h, 0E8h, 84h, 9Ch, 0D6h, 0FFh, 83h, 0C4h, 10h, 83h, 0F8h, 01h
    db 73h, 05h, 0B8h, 01h, 00h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 49h, 3Ch
    db 8Bh, 56h, 08h, 89h, 4Eh, 24h, 03h, 0C8h, 50h, 89h, 4Eh, 20h, 52h, 8Bh, 0CEh, 0E8h
    db 86h, 0D8h, 0D7h, 0FFh, 5Eh, 0C3h
?d_00297f10@@YAXXZ ENDP

; ghidra: FUN_00698380  retail @ 0x00298380 size 32
public ?d_00298380@@YAXXZ
?d_00298380@@YAXXZ PROC
    db 0C7h, 01h, 58h, 01h, 0Ch, 01h, 0C7h, 41h, 0Ch, 90h, 00h, 0Ch, 01h, 0C7h, 41h, 10h
    db 80h, 00h, 0Ch, 01h, 0C7h, 41h, 20h, 54h, 00h, 0Ch, 01h, 0E9h, 07h, 0C0h, 0D8h, 0FFh
?d_00298380@@YAXXZ ENDP

; ghidra: FUN_00698530  retail @ 0x00298530 size 125
public ?d_00298530@@YAXXZ
?d_00298530@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 27h, 0F8h, 0D7h, 0FFh, 8Bh, 46h, 24h, 85h, 0C0h, 75h, 6Ch, 8Bh
    db 46h, 04h, 8Bh, 80h, 54h, 02h, 00h, 00h, 48h, 8Bh, 4Eh, 08h, 74h, 40h, 48h, 74h
    db 20h, 48h, 75h, 57h, 8Bh, 91h, 28h, 01h, 00h, 00h, 0B8h, 00h, 04h, 00h, 00h, 85h
    db 0D0h, 75h, 48h, 0Bh, 0D0h, 89h, 91h, 28h, 01h, 00h, 00h, 5Eh, 0E9h, 0ACh, 93h, 0D8h
    db 0FFh, 8Bh, 91h, 28h, 01h, 00h, 00h, 0B8h, 00h, 02h, 00h, 00h, 85h, 0D0h, 75h, 2Bh
    db 0Bh, 0D0h, 89h, 91h, 28h, 01h, 00h, 00h, 5Eh, 0E9h, 8Fh, 93h, 0D8h, 0FFh, 8Bh, 91h
    db 28h, 01h, 00h, 00h, 0B8h, 00h, 01h, 00h, 00h, 85h, 0D0h, 75h, 0Eh, 0Bh, 0D0h, 89h
    db 91h, 28h, 01h, 00h, 00h, 5Eh, 0E9h, 72h, 93h, 0D8h, 0FFh, 5Eh, 0C3h
?d_00298530@@YAXXZ ENDP

; ghidra: FUN_00698870  retail @ 0x00298870 size 25
public ?d_00298870@@YAXXZ
?d_00298870@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0CAh, 0F3h, 0DAh, 0FFh
?d_00298870@@YAXXZ ENDP

; ghidra: FUN_006988f0  retail @ 0x002988F0 size 13
public ?d_002988f0@@YAXXZ
?d_002988f0@@YAXXZ PROC
    db 8Bh, 41h, 20h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 2Bh, 41h, 3Ch, 0C3h
?d_002988f0@@YAXXZ ENDP

; ghidra: FUN_00698aa0  retail @ 0x00298AA0 size 48
public ?d_00298aa0@@YAXXZ
?d_00298aa0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 48h, 10h, 8Bh, 50h, 0Ch, 6Ah, 6Ah, 68h, 0A8h
    db 03h, 0Ch, 01h, 51h, 52h, 0E8h, 0F4h, 90h, 0D6h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 8Bh, 49h, 3Ch, 89h, 4Eh, 24h, 03h, 0C8h, 83h, 0C4h, 10h, 89h, 4Eh, 20h, 5Eh, 0C3h
?d_00298aa0@@YAXXZ ENDP

; ghidra: FUN_00698ce0  retail @ 0x00298CE0 size 32
public ?d_00298ce0@@YAXXZ
?d_00298ce0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 00h, 04h, 0Ch, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 53h, 0EFh, 0DAh, 0FFh
?d_00298ce0@@YAXXZ ENDP

; ghidra: FUN_00698df0  retail @ 0x00298DF0 size 17
public ?d_00298df0@@YAXXZ
?d_00298df0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 18h, 05h, 0Ch, 01h, 0E8h, 20h, 7Bh, 5Bh, 00h
    db 0C3h
?d_00298df0@@YAXXZ ENDP

; ghidra: FUN_00698fd0  retail @ 0x00298FD0 size 98
public ?d_00298fd0@@YAXXZ
?d_00298fd0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 0E3h, 0B4h, 0D6h, 0FFh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 44h, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h
    db 0Ch, 88h, 44h, 24h, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Dh
    db 4Fh, 24h, 51h, 56h, 0E8h, 0ABh, 39h, 0D7h, 0FFh, 8Bh, 16h, 83h, 0C4h, 08h, 8Dh, 47h
    db 28h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 8Dh, 47h, 2Ch, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 6Ch, 8Bh, 16h, 83h, 0C7h, 30h, 57h, 8Bh, 0CEh, 0FFh, 52h, 74h, 5Fh, 5Eh, 0C2h
    db 04h, 00h
?d_00298fd0@@YAXXZ ENDP

; ghidra: FUN_006991d0  retail @ 0x002991D0 size 42
public ?d_002991d0@@YAXXZ
?d_002991d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 71h, 60h
    db 0D8h, 0FFh, 85h, 0C0h, 74h, 12h, 6Ah, 00h, 6Ah, 08h, 8Bh, 0C8h, 0E8h, 15h, 0B3h, 0D7h
    db 0FFh, 0C7h, 46h, 24h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_002991d0@@YAXXZ ENDP

; ghidra: FUN_00699210  retail @ 0x00299210 size 44
public ?d_00299210@@YAXXZ
?d_00299210@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 31h, 60h
    db 0D8h, 0FFh, 85h, 0C0h, 74h, 12h, 6Ah, 00h, 6Ah, 08h, 8Bh, 0C8h, 0E8h, 0D5h, 0B2h, 0D7h
    db 0FFh, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_00299210@@YAXXZ ENDP

; ghidra: FUN_00699250  retail @ 0x00299250 size 292
public ?d_00299250@@YAXXZ
?d_00299250@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 96h, 20h, 01h, 01h, 50h, 0A1h, 98h
    db 08h, 2Fh, 01h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 8Bh, 40h, 3Ch, 83h, 0ECh, 70h
    db 55h, 56h, 8Bh, 0F1h, 8Bh, 6Eh, 04h, 89h, 46h, 30h, 0F6h, 05h, 0DCh, 0FFh, 2Eh, 01h
    db 01h, 57h, 8Bh, 7Eh, 08h, 0C7h, 46h, 28h, 00h, 00h, 00h, 00h, 75h, 32h, 83h, 0Dh
    db 0DCh, 0FFh, 2Eh, 01h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 3Ch, 40h, 08h, 01h
    db 0C7h, 84h, 24h, 88h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 27h, 1Bh, 0DAh, 0FFh
    db 0A3h, 0D8h, 0FFh, 2Eh, 01h, 0C7h, 84h, 24h, 84h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh
    db 8Bh, 0Dh, 0D8h, 0FFh, 2Eh, 01h, 51h, 8Bh, 0CFh, 0E8h, 55h, 1Bh, 0D9h, 0FFh, 85h, 0C0h
    db 74h, 6Bh, 8Ah, 48h, 2Dh, 84h, 0C9h, 74h, 64h, 8Bh, 0C8h, 0E8h, 0CFh, 0DFh, 0D8h, 0FFh
    db 6Ah, 12h, 8Bh, 0CFh, 0E8h, 91h, 8Ch, 0D9h, 0FFh, 6Ah, 01h, 6Ah, 00h, 6Ah, 05h, 8Bh
    db 0CFh, 0E8h, 28h, 86h, 0D7h, 0FFh, 8Bh, 4Dh, 20h, 85h, 0C9h, 8Dh, 45h, 20h, 74h, 3Dh
    db 8Bh, 7Fh, 74h, 57h, 50h, 8Dh, 4Ch, 24h, 14h, 0E8h, 78h, 0FBh, 0D6h, 0FFh, 8Bh, 0Dh
    db 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 0Ch, 50h, 0C7h, 84h, 24h, 88h, 00h
    db 00h, 00h, 01h, 00h, 00h, 00h, 0FFh, 52h, 44h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 84h, 24h
    db 84h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F8h, 0DBh, 0D8h, 0FFh, 8Bh, 4Eh, 24h
    db 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 07h, 5Fh, 0D8h, 0FFh, 85h, 0C0h, 74h, 12h
    db 6Ah, 00h, 6Ah, 08h, 8Bh, 0C8h, 0E8h, 0ABh, 0B1h, 0D7h, 0FFh, 0C7h, 46h, 24h, 00h, 00h
    db 00h, 00h, 8Bh, 4Ch, 24h, 7Ch, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 7Ch, 0C3h
?d_00299250@@YAXXZ ENDP

; ghidra: FUN_006993c0  retail @ 0x002993C0 size 49
public ?d_002993c0@@YAXXZ
?d_002993c0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 33h, 0D2h, 8Bh, 0C2h, 0Dh, 00h, 00h, 04h, 00h, 89h, 04h, 24h, 6Ah
    db 01h, 8Dh, 44h, 24h, 04h, 0C7h, 41h, 30h, 00h, 00h, 00h, 00h, 8Bh, 49h, 08h, 89h
    db 54h, 24h, 08h, 50h, 89h, 54h, 24h, 10h, 0E8h, 0FAh, 73h, 0D9h, 0FFh, 83h, 0C4h, 0Ch
    db 0C3h
?d_002993c0@@YAXXZ ENDP

; ghidra: FUN_00699400  retail @ 0x00299400 size 377
public ?d_00299400@@YAXXZ
?d_00299400@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 24h, 8Bh, 46h, 08h, 8Bh, 6Eh
    db 04h, 57h, 8Bh, 3Dh, 98h, 08h, 2Fh, 01h, 51h, 8Bh, 0CFh, 89h, 44h, 24h, 14h, 0E8h
    db 2Fh, 5Eh, 0D8h, 0FFh, 8Bh, 4Fh, 3Ch, 8Bh, 7Dh, 0Ch, 8Bh, 5Eh, 28h, 03h, 0DFh, 8Bh
    db 7Dh, 10h, 03h, 0FBh, 3Bh, 0CFh, 89h, 44h, 24h, 1Ch, 89h, 4Ch, 24h, 14h, 72h, 1Eh
    db 8Bh, 54h, 24h, 10h, 83h, 0C2h, 38h, 52h, 8Bh, 0C8h, 0E8h, 58h, 0Dh, 0DAh, 0FFh, 8Bh
    db 0CEh, 0E8h, 71h, 0Dh, 0D8h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 1Ch, 0C3h, 85h, 0C0h
    db 0Fh, 84h, 0Bh, 01h, 00h, 00h, 8Bh, 80h, 04h, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 84h
    db 0FDh, 00h, 00h, 00h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 92h, 80h, 01h, 00h, 00h, 84h, 0C0h
    db 0Fh, 84h, 0EBh, 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 8Bh, 48h, 38h, 8Bh, 50h, 3Ch
    db 68h, 0B9h, 00h, 00h, 00h, 68h, 0B8h, 06h, 0Ch, 01h, 68h, 0DBh, 0Fh, 0C9h, 3Fh, 68h
    db 0DBh, 0Fh, 0C9h, 0BFh, 89h, 4Ch, 24h, 30h, 89h, 54h, 24h, 34h, 0E8h, 0F4h, 37h, 0D9h
    db 0FFh, 0D8h, 46h, 2Ch, 8Bh, 44h, 24h, 24h, 83h, 0C4h, 10h, 2Bh, 0C3h, 0D9h, 54h, 24h
    db 18h, 0D9h, 5Eh, 2Ch, 75h, 09h, 8Bh, 45h, 18h, 89h, 44h, 24h, 10h, 0EBh, 40h, 85h
    db 0C0h, 0D9h, 45h, 18h, 89h, 44h, 24h, 14h, 0DBh, 44h, 24h, 14h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 2Bh, 0FBh, 85h, 0FFh, 89h, 7Ch, 24h, 14h, 0DBh, 44h, 24h, 14h
    db 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0DEh, 0F9h, 0D9h, 45h, 18h, 0D8h, 0Dh, 3Ch
    db 53h, 07h, 01h, 0D8h, 0E2h, 0DEh, 0C9h, 0D8h, 0C1h, 0D9h, 5Ch, 24h, 10h, 0DDh, 0D8h, 8Bh
    db 4Ch, 24h, 18h, 51h, 0E8h, 07h, 0A4h, 5Dh, 00h, 0D8h, 4Ch, 24h, 14h, 8Bh, 56h, 2Ch
    db 52h, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h, 28h, 0E8h, 0E2h, 0A3h, 5Dh, 00h, 0D8h, 4Ch
    db 24h, 18h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h, 83h, 0C4h, 08h, 0D8h, 44h, 24h
    db 24h, 6Ah, 00h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 52h, 8Bh, 54h, 24h, 28h
    db 52h, 0FFh, 50h, 18h, 0D9h, 5Ch, 24h, 28h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 89h, 04h, 02h
    db 00h, 00h, 6Ah, 02h, 8Dh, 44h, 24h, 24h, 50h, 83h, 0C1h, 20h, 0E8h, 0F9h, 0ADh, 0D9h
    db 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 1Ch, 0C3h
?d_00299400@@YAXXZ ENDP

; ghidra: FUN_00699a80  retail @ 0x00299A80 size 176
public ?d_00299a80@@YAXXZ
?d_00299a80@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 85h, 0C0h, 0Fh, 84h, 9Ch, 00h, 00h, 00h, 8Bh
    db 44h, 24h, 0Ch, 0DBh, 44h, 24h, 0Ch, 85h, 0C0h, 53h, 57h, 8Bh, 7Eh, 04h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 14h, 8Dh, 4Fh, 10h, 8Bh, 5Ch, 24h
    db 14h, 53h, 0E8h, 08h, 0F4h, 0D9h, 0FFh, 0DCh, 0C0h, 53h, 8Dh, 4Fh, 68h, 0D9h, 5Ch, 24h
    db 18h, 0E8h, 0F9h, 0F3h, 0D9h, 0FFh, 8Bh, 4Eh, 24h, 8Bh, 41h, 58h, 8Bh, 54h, 24h, 14h
    db 8Bh, 0CAh, 89h, 50h, 58h, 89h, 48h, 5Ch, 8Bh, 56h, 24h, 8Bh, 42h, 5Ch, 0D8h, 0Dh
    db 54h, 59h, 07h, 01h, 8Bh, 0D1h, 89h, 48h, 58h, 53h, 0D9h, 5Ch, 24h, 10h, 8Dh, 4Fh
    db 3Ch, 89h, 50h, 5Ch, 0E8h, 0C6h, 0F3h, 0D9h, 0FFh, 0D8h, 0Dh, 68h, 40h, 08h, 01h, 0E8h
    db 34h, 0D3h, 75h, 00h, 8Bh, 4Eh, 24h, 50h, 0E8h, 71h, 41h, 0D7h, 0FFh, 0D9h, 44h, 24h
    db 0Ch, 8Bh, 46h, 24h, 0D9h, 0E0h, 8Bh, 48h, 58h, 8Bh, 54h, 24h, 0Ch, 89h, 51h, 20h
    db 8Bh, 46h, 24h, 8Bh, 48h, 5Ch, 5Fh, 0D9h, 59h, 20h, 5Bh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00299a80@@YAXXZ ENDP

; ghidra: FUN_00699bb0  retail @ 0x00299BB0 size 259
public ?d_00299bb0@@YAXXZ
?d_00299bb0@@YAXXZ PROC
    db 81h, 0ECh, 0A8h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 85h, 0C0h, 0Fh, 85h
    db 0E7h, 00h, 00h, 00h, 57h, 8Bh, 7Eh, 04h, 8Bh, 47h, 08h, 85h, 0C0h, 0Fh, 84h, 0D7h
    db 00h, 00h, 00h, 66h, 83h, 78h, 04h, 00h, 0Fh, 84h, 0CCh, 00h, 00h, 00h, 6Ah, 00h
    db 8Dh, 4Fh, 10h, 0C7h, 84h, 24h, 0ACh, 00h, 00h, 00h, 00h, 00h, 0A0h, 41h, 0C6h, 84h
    db 24h, 0B0h, 00h, 00h, 00h, 00h, 0E8h, 0C4h, 0F2h, 0D9h, 0FFh, 0D9h, 5Ch, 24h, 08h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 6Ah, 40h, 50h, 8Dh, 44h, 24h, 14h, 50h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 0D9h, 44h
    db 24h, 14h, 8Bh, 0Dh, 0ECh, 6Dh, 30h, 01h, 0DCh, 0C0h, 83h, 0C4h, 0Ch, 8Dh, 44h, 24h
    db 0Ch, 50h, 0D9h, 94h, 24h, 98h, 00h, 00h, 00h, 50h, 0D9h, 9Ch, 24h, 0A0h, 00h, 00h
    db 00h, 0C6h, 44h, 24h, 53h, 00h, 0C7h, 84h, 24h, 94h, 00h, 00h, 00h, 40h, 00h, 00h
    db 00h, 0C6h, 84h, 24h, 98h, 00h, 00h, 00h, 00h, 0C6h, 84h, 24h, 99h, 00h, 00h, 00h
    db 01h, 0C7h, 84h, 24h, 0A4h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 0A8h
    db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 8Bh, 11h, 6Ah, 40h, 0FFh, 52h, 10h, 85h, 0C0h
    db 89h, 46h, 24h, 74h, 25h, 8Bh, 4Eh, 08h, 83h, 0C1h, 38h, 8Bh, 11h, 83h, 0C0h, 08h
    db 89h, 10h, 8Bh, 51h, 04h, 89h, 50h, 04h, 8Bh, 49h, 08h, 89h, 48h, 08h, 8Bh, 57h
    db 0Ch, 8Bh, 4Eh, 24h, 52h, 0E8h, 7Ch, 18h, 0D9h, 0FFh, 5Fh, 5Eh, 81h, 0C4h, 0A8h, 00h
    db 00h, 00h, 0C3h
?d_00299bb0@@YAXXZ ENDP

; ghidra: FUN_00699d80  retail @ 0x00299D80 size 16
public ?d_00299d80@@YAXXZ
?d_00299d80@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 83h, 0C0h, 0D7h, 0FFh, 8Bh, 0CEh, 5Eh, 0E9h, 59h, 0D9h, 0D6h, 0FFh
?d_00299d80@@YAXXZ ENDP

; ghidra: FUN_0069a150  retail @ 0x0029A150 size 930
public ?d_0029a150@@YAXXZ
?d_0029a150@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 0D9h, 44h, 24h, 08h, 0D8h, 1Dh, 3Ch, 53h, 07h, 01h
    db 6Ah, 0FFh, 68h, 0BBh, 21h, 01h, 01h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h
    db 0ECh, 7Ch, 0DFh, 0E0h, 56h, 0F6h, 0C4h, 05h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 04h, 7Ah, 0Bh
    db 0C7h, 84h, 24h, 98h, 00h, 00h, 00h, 00h, 00h, 00h, 3Fh, 8Bh, 46h, 54h, 85h, 0C0h
    db 75h, 09h, 8Bh, 4Fh, 10h, 89h, 4Ch, 24h, 0Ch, 0EBh, 07h, 8Bh, 57h, 34h, 89h, 54h
    db 24h, 0Ch, 85h, 0C0h, 75h, 09h, 8Bh, 47h, 14h, 89h, 44h, 24h, 10h, 0EBh, 07h, 8Bh
    db 4Fh, 38h, 89h, 4Ch, 24h, 10h, 68h, 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h, 00h
    db 6Ah, 04h, 6Ah, 0Ch, 8Dh, 54h, 24h, 34h, 52h, 0E8h, 16h, 0CDh, 75h, 00h, 0D9h, 46h
    db 34h, 0D8h, 66h, 40h, 8Dh, 46h, 2Ch, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 40h, 08h, 0D8h
    db 15h, 50h, 53h, 07h, 01h, 89h, 4Ch, 24h, 24h, 8Dh, 4Eh, 38h, 89h, 54h, 24h, 28h
    db 8Bh, 11h, 89h, 44h, 24h, 2Ch, 8Bh, 41h, 04h, 8Bh, 49h, 08h, 89h, 44h, 24h, 4Ch
    db 0DFh, 0E0h, 0C7h, 84h, 24h, 8Ch, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0F6h, 0C4h, 05h
    db 89h, 54h, 24h, 48h, 89h, 4Ch, 24h, 50h, 7Ah, 08h, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h
    db 07h, 01h, 0D9h, 84h, 24h, 98h, 00h, 00h, 00h, 0D8h, 0E1h, 0D8h, 0B4h, 24h, 98h, 00h
    db 00h, 00h, 0D9h, 54h, 24h, 14h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 05h, 7Ah, 08h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0D8h, 84h, 24h, 98h, 00h
    db 00h, 00h, 0D9h, 5Eh, 48h, 0D9h, 44h, 24h, 48h, 0D8h, 64h, 24h, 24h, 0D9h, 44h, 24h
    db 0Ch, 0D8h, 0C9h, 0D8h, 44h, 24h, 24h, 0D9h, 5Ch, 24h, 30h, 0D9h, 44h, 24h, 4Ch, 0D8h
    db 64h, 24h, 28h, 0D9h, 44h, 24h, 0Ch, 0D8h, 0C9h, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h
    db 34h, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 10h, 0D8h, 44h, 24h, 24h, 0D9h, 5Ch, 24h, 3Ch, 0D8h
    db 4Ch, 24h, 10h, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h, 40h, 8Ah, 47h, 42h, 84h, 0C0h
    db 74h, 25h, 0D9h, 44h, 24h, 50h, 0D8h, 64h, 24h, 2Ch, 0D9h, 0C0h, 0D8h, 4Fh, 44h, 0D8h
    db 44h, 24h, 2Ch, 0D9h, 5Ch, 24h, 38h, 0D8h, 4Fh, 48h, 0D8h, 44h, 24h, 2Ch, 0D9h, 5Ch
    db 24h, 44h, 0E9h, 60h, 01h, 00h, 00h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 11h, 8Dh
    db 44h, 24h, 48h, 50h, 8Dh, 44h, 24h, 28h, 50h, 0FFh, 52h, 40h, 0D9h, 5Ch, 24h, 08h
    db 8Bh, 46h, 54h, 85h, 0C0h, 75h, 05h, 0D9h, 47h, 08h, 0EBh, 03h, 0D9h, 47h, 2Ch, 85h
    db 0C0h, 75h, 05h, 0D9h, 47h, 0Ch, 0EBh, 03h, 0D9h, 47h, 30h, 0D9h, 0C9h, 0D8h, 8Ch, 24h
    db 98h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 18h, 0D8h, 4Ch, 24h, 14h, 0D8h, 8Ch, 24h, 98h
    db 00h, 00h, 00h, 0D9h, 5Ch, 24h, 14h, 0D9h, 47h, 3Ch, 0D8h, 1Dh, 50h, 53h, 07h, 01h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 0B4h, 00h, 00h, 00h, 0D9h, 44h, 24h, 48h, 0D8h
    db 64h, 24h, 24h, 0D9h, 44h, 24h, 4Ch, 0D8h, 64h, 24h, 28h, 0D9h, 44h, 24h, 50h, 0D8h
    db 64h, 24h, 2Ch, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h
    db 0CCh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 1Ch, 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 44h, 24h
    db 1Ch, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 20h, 0D9h, 44h, 24h, 20h, 0D8h, 77h, 3Ch, 0D8h, 15h
    db 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h
    db 53h, 07h, 01h, 0D9h, 44h, 24h, 50h, 0D8h, 64h, 24h, 2Ch, 0D9h, 44h, 24h, 0Ch, 0D8h
    db 0C9h, 0D8h, 44h, 24h, 2Ch, 0D9h, 5Ch, 24h, 38h, 0D8h, 4Ch, 24h, 10h, 0D8h, 44h, 24h
    db 2Ch, 0D9h, 44h, 24h, 38h, 0D8h, 5Ch, 24h, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h
    db 8Bh, 4Ch, 24h, 08h, 89h, 4Ch, 24h, 38h, 0D9h, 0C1h, 0D8h, 4Ch, 24h, 18h, 0D8h, 44h
    db 24h, 38h, 0D9h, 5Ch, 24h, 38h, 0D8h, 54h, 24h, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah
    db 06h, 0DDh, 0D8h, 0D9h, 44h, 24h, 08h, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 14h, 0EBh, 40h, 0D9h
    db 44h, 24h, 08h, 0D8h, 5Ch, 24h, 2Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 8Dh, 44h, 24h, 08h
    db 74h, 04h, 8Dh, 44h, 24h, 2Ch, 0D9h, 00h, 0D9h, 54h, 24h, 08h, 0D8h, 5Ch, 24h, 50h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 8Dh, 44h, 24h, 08h, 74h, 04h, 8Dh, 44h, 24h, 50h, 0D9h
    db 00h, 0D9h, 44h, 24h, 18h, 0D8h, 0C1h, 0D9h, 5Ch, 24h, 38h, 0D9h, 44h, 24h, 14h, 0D8h
    db 0C1h, 0D9h, 5Ch, 24h, 44h, 0DDh, 0D8h, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 4Ch, 24h, 58h
    db 0E8h, 58h, 0Ah, 0D8h, 0FFh, 8Ah, 84h, 24h, 94h, 00h, 00h, 00h, 84h, 0C0h, 0C6h, 84h
    db 24h, 8Ch, 00h, 00h, 00h, 01h, 74h, 36h, 8Bh, 46h, 44h, 68h, 00h, 00h, 80h, 3Fh
    db 8Dh, 4Ch, 24h, 58h, 89h, 44h, 24h, 24h, 0E8h, 0Ch, 9Fh, 0DAh, 0FFh, 0D8h, 74h, 24h
    db 20h, 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 94h, 93h, 35h, 01h, 0D8h, 05h, 34h
    db 53h, 07h, 01h, 83h, 0C4h, 08h, 0E8h, 0BDh, 0C9h, 75h, 00h, 89h, 46h, 4Ch, 8Bh, 4Eh
    db 4Ch, 0B8h, 03h, 00h, 00h, 00h, 3Bh, 0C8h, 7Dh, 03h, 89h, 46h, 4Ch, 8Bh, 56h, 4Ch
    db 8Dh, 4Eh, 20h, 51h, 52h, 8Dh, 4Ch, 24h, 5Ch, 0E8h, 0C8h, 9Fh, 0D7h, 0FFh, 68h, 4Ch
    db 36h, 41h, 00h, 6Ah, 04h, 6Ah, 0Ch, 8Dh, 44h, 24h, 60h, 50h, 0C6h, 84h, 24h, 9Ch
    db 00h, 00h, 00h, 00h, 0E8h, 0BDh, 0C8h, 75h, 00h, 68h, 4Ch, 36h, 41h, 00h, 6Ah, 04h
    db 6Ah, 0Ch, 8Dh, 4Ch, 24h, 30h, 51h, 0C7h, 84h, 24h, 9Ch, 00h, 00h, 00h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 9Fh, 0C8h, 75h, 00h, 8Bh, 8Ch, 24h, 84h, 00h, 00h, 00h, 5Fh, 0B0h
    db 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C2h
    db 08h, 00h
?d_0029a150@@YAXXZ ENDP

; ghidra: FUN_0069a6a0  retail @ 0x0029A6A0 size 196
public ?d_0029a6a0@@YAXXZ
?d_0029a6a0@@YAXXZ PROC
    db 55h, 56h, 8Bh, 0E9h, 8Bh, 75h, 08h, 8Bh, 46h, 04h, 85h, 0C0h, 57h, 8Bh, 0BEh, 14h
    db 02h, 00h, 00h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0FAh, 7Bh, 0D6h
    db 0FFh, 8Ah, 88h, 0B0h, 04h, 00h, 00h, 84h, 0C9h, 75h, 21h, 85h, 0FFh, 74h, 21h, 8Bh
    db 47h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0D9h, 7Bh
    db 0D6h, 0FFh, 8Ah, 88h, 0B0h, 04h, 00h, 00h, 84h, 0C9h, 74h, 04h, 32h, 0C0h, 0EBh, 04h
    db 8Ah, 44h, 24h, 10h, 84h, 0C0h, 88h, 45h, 5Ch, 75h, 63h, 8Bh, 86h, 20h, 01h, 00h
    db 00h, 0BFh, 00h, 00h, 00h, 02h, 85h, 0C7h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FDh, 8Bh
    db 0CEh, 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 01h, 72h, 0D8h, 0FFh, 8Bh, 86h, 1Ch, 01h
    db 00h, 00h, 0A9h, 00h, 00h, 00h, 01h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FEh, 8Bh, 0CEh
    db 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 0E2h, 71h, 0D8h, 0FFh, 8Bh, 86h, 1Ch, 01h, 00h
    db 00h, 85h, 0C7h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FDh, 8Bh, 0CEh, 89h, 86h, 1Ch, 01h
    db 00h, 00h, 0E8h, 0C6h, 71h, 0D8h, 0FFh, 0C7h, 45h, 58h, 00h, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Dh, 0C2h, 04h, 00h
?d_0029a6a0@@YAXXZ ENDP

; ghidra: FUN_0069a7a0  retail @ 0x0029A7A0 size 31
public ?d_0029a7a0@@YAXXZ
?d_0029a7a0@@YAXXZ PROC
    db 8Bh, 41h, 08h, 0F7h, 80h, 1Ch, 01h, 00h, 00h, 00h, 00h, 00h, 01h, 75h, 0Dh, 8Ah
    db 88h, 18h, 01h, 00h, 00h, 84h, 0C9h, 78h, 03h, 32h, 0C0h, 0C3h, 0B0h, 01h, 0C3h
?d_0029a7a0@@YAXXZ ENDP

; ghidra: FUN_0069a7d0  retail @ 0x0029A7D0 size 133
public ?d_0029a7d0@@YAXXZ
?d_0029a7d0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 08h, 8Bh, 46h, 04h, 85h, 0C0h, 8Bh, 9Eh, 14h
    db 02h, 00h, 00h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0CAh, 7Ah, 0D6h
    db 0FFh, 8Ah, 88h, 0B0h, 04h, 00h, 00h, 84h, 0C9h, 75h, 56h, 85h, 0DBh, 74h, 1Dh, 8Bh
    db 43h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0A9h, 7Ah
    db 0D6h, 0FFh, 8Ah, 88h, 0B0h, 04h, 00h, 00h, 84h, 0C9h, 75h, 35h, 8Bh, 8Eh, 1Ch, 01h
    db 00h, 00h, 0B8h, 00h, 00h, 00h, 02h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 1Ch
    db 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0E3h, 70h, 0D8h, 0FFh, 8Bh, 47h, 04h, 0C6h, 47h, 5Ch
    db 01h, 8Bh, 48h, 20h, 6Ah, 01h, 89h, 4Fh, 58h, 56h, 8Bh, 0CFh, 0E8h, 89h, 0AFh, 0D7h
    db 0FFh, 5Fh, 5Eh, 5Bh, 0C3h
?d_0029a7d0@@YAXXZ ENDP

; ghidra: FUN_0069a880  retail @ 0x0029A880 size 202
public ?d_0029a880@@YAXXZ
?d_0029a880@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E3h, 21h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 18h, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 0Ch, 0E8h, 36h, 0C8h, 0D7h, 0FFh, 0C7h, 46h
    db 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh, 09h, 01h, 83h, 0C9h, 0FFh, 33h
    db 0C0h, 89h, 46h, 14h, 89h, 4Eh, 18h, 89h, 4Eh, 1Ch, 0C7h, 06h, 8Ch, 0Ch, 0Ch, 01h
    db 0C7h, 46h, 0Ch, 0C8h, 0Bh, 0Ch, 01h, 0C7h, 46h, 10h, 0BCh, 0Bh, 0Ch, 01h, 89h, 46h
    db 20h, 89h, 46h, 24h, 89h, 44h, 24h, 10h, 89h, 46h, 28h, 89h, 46h, 44h, 89h, 46h
    db 48h, 89h, 46h, 4Ch, 89h, 46h, 50h, 89h, 46h, 54h, 89h, 46h, 58h, 88h, 46h, 5Ch
    db 88h, 46h, 5Eh, 88h, 46h, 5Fh, 89h, 46h, 2Ch, 89h, 46h, 30h, 89h, 46h, 34h, 89h
    db 46h, 38h, 89h, 46h, 3Ch, 89h, 46h, 40h, 8Bh, 4Eh, 08h, 8Bh, 56h, 04h, 8Ah, 42h
    db 58h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 18h, 01h, 88h, 46h
    db 5Dh, 0E8h, 0A4h, 0AEh, 0D7h, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_0029a880@@YAXXZ ENDP

; ghidra: FUN_0069aa30  retail @ 0x0029AA30 size 172
public ?d_0029aa30@@YAXXZ
?d_0029aa30@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 22h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 0C7h, 06h
    db 8Ch, 0Ch, 0Ch, 01h, 0C7h, 46h, 0Ch, 0C8h, 0Bh, 0Ch, 01h, 0C7h, 46h, 10h, 0BCh, 0Bh
    db 0Ch, 01h, 8Bh, 7Eh, 20h, 85h, 0FFh, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h
    db 37h, 8Bh, 4Eh, 28h, 2Bh, 0CFh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh
    db 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h
    db 00h, 76h, 0Bh, 57h, 0E8h, 17h, 74h, 5Eh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 57h
    db 0E8h, 4Bh, 3Bh, 59h, 00h, 83h, 0C4h, 08h, 8Bh, 0CEh, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0C7h, 46h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 06h, 5Ch, 0CBh, 09h, 01h, 0C7h
    db 46h, 0Ch, 98h, 0CAh, 09h, 01h, 0E8h, 88h, 0D1h, 0DAh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Fh
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0029aa30@@YAXXZ ENDP

; ghidra: FUN_0069ab10  retail @ 0x0029AB10 size 194
public ?d_0029ab10@@YAXXZ
?d_0029ab10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 08h, 8Bh, 87h, 14h, 02h, 00h, 00h, 85h, 0C0h, 74h
    db 30h, 8Bh, 40h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 87h, 77h, 0D6h, 0FFh, 8Bh, 88h, 0D4h, 00h, 00h, 00h, 0F6h, 0C5h, 10h, 75h, 12h, 68h
    db 0FFh, 0FFh, 0FFh, 3Fh, 57h, 8Bh, 0CEh, 0E8h, 8Eh, 0ACh, 0D7h, 0FFh, 5Fh, 5Eh, 0C2h, 0Ch
    db 00h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 11h, 8Dh, 46h, 38h, 89h, 10h, 8Bh, 51h, 04h, 89h
    db 50h, 04h, 8Bh, 49h, 08h, 89h, 48h, 08h, 83h, 0C7h, 38h, 8Bh, 07h, 8Dh, 56h, 2Ch
    db 89h, 02h, 8Bh, 4Fh, 04h, 89h, 4Ah, 04h, 8Bh, 47h, 08h, 8Bh, 4Ch, 24h, 14h, 89h
    db 42h, 08h, 8Bh, 54h, 24h, 10h, 52h, 89h, 4Eh, 44h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0Dh
    db 0BDh, 0D8h, 0FFh, 84h, 0C0h, 74h, 36h, 8Bh, 46h, 10h, 8Dh, 7Eh, 10h, 8Bh, 0CFh, 0C7h
    db 46h, 50h, 00h, 00h, 00h, 00h, 0FFh, 10h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h
    db 3Ch, 8Bh, 4Eh, 08h, 52h, 0E8h, 89h, 0Fh, 0D9h, 0FFh, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 10h
    db 8Bh, 4Eh, 08h, 6Ah, 01h, 51h, 8Bh, 0CEh, 0E8h, 0Dh, 0ACh, 0D7h, 0FFh, 5Fh, 5Eh, 0C2h
    db 0Ch, 00h
?d_0029ab10@@YAXXZ ENDP

; ghidra: FUN_0069ac40  retail @ 0x0029AC40 size 990
_TEXT ENDS
_TEXT$d0069ac40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0069AC40 size 990
public ?d_0029ac40@@YAXXZ
?d_0029ac40@@YAXXZ PROC
    db 083h, 0ECh, 02Ch, 053h, 055h, 08Bh, 0E9h, 08Bh, 05Dh, 008h, 08Bh, 083h, 014h, 002h, 000h, 000h
    db 085h, 0C0h, 056h, 08Bh, 075h, 004h, 089h, 06Ch, 024h, 01Ch, 089h, 05Ch, 024h, 018h, 074h, 034h
    db 08Bh, 040h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0D4h, 000h, 000h, 000h, 0F6h, 0C5h, 010h, 075h, 016h, 068h, 0FFh, 0FFh, 0FFh, 03Fh
    db 053h, 08Bh, 0CDh
    call ?j_000157da@@YAXXZ
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 02Ch, 0C2h, 004h, 000h, 0F6h, 083h, 098h, 000h, 000h, 000h, 020h
    db 074h, 007h, 08Bh, 0CBh
    call ?j_0002308d@@YAXXZ
    db 057h, 08Bh, 0BBh, 004h, 002h, 000h, 000h, 085h, 0FFh, 074h, 01Fh, 08Bh, 007h, 08Bh, 0CFh, 0FFh
    db 090h, 034h, 001h, 000h, 000h, 084h, 0C0h, 075h, 011h, 08Bh, 0CFh
    call ?j_000359bd@@YAXXZ
    db 06Ah, 002h, 08Dh, 04Fh, 020h
    call ?j_00024d70@@YAXXZ
    db 06Ah, 001h, 053h, 08Bh, 0CDh
    call ?j_000157da@@YAXXZ
    db 08Bh, 04Bh, 038h, 08Bh, 053h, 03Ch, 08Bh, 043h, 040h, 08Dh, 06Bh, 038h, 089h, 04Ch, 024h, 030h
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 039h, 06Ah, 001h, 06Ah, 000h, 08Bh, 0CBh, 089h, 054h, 024h, 03Ch, 089h, 044h, 024h, 040h
    call ?j_0003a391@@YAXXZ
    db 08Bh, 054h, 024h, 03Ch, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 050h, 08Bh, 044h, 024h, 03Ch, 052h, 050h, 0FFh, 057h, 01Ch, 0D8h, 06Ch, 024h, 038h, 0D9h, 054h
    db 024h, 010h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 0D9h
    db 044h, 024h, 010h, 08Bh, 015h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 033h, 0DBh, 0B9h, 002h, 000h, 000h, 000h, 089h, 05Ch, 024h, 018h, 089h, 04Ch, 024h, 014h, 08Dh
    db 049h, 000h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 085h, 0C1h, 000h, 000h, 000h, 0DBh, 044h, 024h, 018h, 0D8h
    db 04Eh, 04Ch, 0D8h, 08Ah, 0ACh, 001h, 000h, 000h, 0DEh, 0C1h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 00Fh, 085h, 091h, 000h, 000h, 000h, 08Dh, 041h, 0FFh, 089h, 044h
    db 024h, 018h, 0DBh, 044h, 024h, 018h, 0D8h, 04Eh, 04Ch, 0D8h, 08Ah, 0ACh, 001h, 000h, 000h, 0DEh
    db 0C1h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 071h, 0DBh, 044h, 024h, 014h, 0D8h, 04Eh, 04Ch, 0D8h, 08Ah
    db 0ACh, 001h, 000h, 000h, 0DEh, 0C1h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 05Ah, 08Dh, 041h, 001h, 089h, 044h, 024h, 018h, 0DBh, 044h
    db 024h, 018h, 0D8h, 04Eh, 04Ch, 0D8h, 08Ah, 0ACh, 001h, 000h, 000h, 0DEh, 0C1h, 0D8h, 015h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 03Ch, 08Dh, 041h, 002h, 089h, 044h, 024h, 018h, 0DBh, 044h
    db 024h, 018h, 083h, 0C1h, 005h, 083h, 0C3h, 005h, 083h, 0F9h, 011h, 0D8h, 04Eh, 04Ch, 089h, 05Ch
    db 024h, 018h, 089h, 04Ch, 024h, 014h, 0D8h, 08Ah, 0ACh, 001h, 000h, 000h, 0DEh, 0C1h, 00Fh, 08Ch
    db 040h, 0FFh, 0FFh, 0FFh, 0EBh, 010h, 043h, 0EBh, 00Dh, 083h, 0C3h, 002h, 0EBh, 008h, 083h, 0C3h
    db 003h, 0EBh, 003h, 083h, 0C3h, 004h, 08Bh, 07Ch, 024h, 040h, 0DDh, 0D8h, 0D9h, 047h, 008h, 0D9h
    db 047h, 008h, 0D9h, 047h, 004h, 0D9h, 007h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 040h, 0DDh
    db 0D8h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D8h, 044h, 024h, 040h, 0D9h
    db 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 00Dh
    dd __real@3e800000
    db 0D9h, 0C1h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 027h, 083h, 0FBh, 002h, 07Dh, 022h
    db 0DDh, 0D8h, 0D9h, 047h, 008h, 0D9h, 047h, 004h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh
    db 0DEh, 0C1h, 0D8h, 044h, 024h, 040h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 00Dh
    dd __real@3e800000
    db 0D9h, 0C0h, 0D8h, 0C1h, 0D9h, 082h, 0ACh, 001h, 000h, 000h, 0D8h, 04Eh, 04Ch, 0DEh, 0F9h, 0D9h
    db 0E1h
    call __ftol2
    db 083h, 0F8h, 001h, 073h, 005h, 0B8h, 001h, 000h, 000h, 000h, 003h, 0C3h, 085h, 0C0h, 089h, 044h
    db 024h, 040h, 0DBh, 044h, 024h, 040h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D9h, 054h, 024h, 014h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 0C9h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0DEh, 0C9h, 0D9h, 054h, 024h, 018h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 0D9h
    db 007h, 08Bh, 04Ch, 024h, 014h, 0D9h, 047h, 004h, 089h, 04Ch, 024h, 040h, 0D9h, 0C9h, 08Bh, 0D5h
    db 0D8h, 04Ch, 024h, 040h, 08Bh, 002h, 089h, 044h, 024h, 024h, 08Bh, 04Ah, 004h, 0D9h, 05Ch, 024h
    db 030h, 089h, 04Ch, 024h, 028h, 08Bh, 052h, 008h, 0D8h, 04Ch, 024h, 040h, 08Bh, 04Ch, 024h, 01Ch
    db 089h, 054h, 024h, 02Ch, 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 0D9h, 05Ch, 024h, 034h, 08Dh, 044h, 024h, 024h, 0D9h, 044h, 024h, 040h, 050h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 055h, 051h, 0D9h, 05Ch, 024h, 044h, 0D9h, 044h, 024h, 03Ch, 0D8h, 044h, 024h, 030h, 0D9h, 05Ch
    db 024h, 030h, 0D9h, 044h, 024h, 040h, 0D8h, 044h, 024h, 034h, 0D9h, 05Ch, 024h, 034h, 0D9h, 044h
    db 024h, 038h, 0D8h, 044h, 024h, 044h, 0D9h, 05Ch, 024h, 038h, 08Bh, 04Ah, 00Ch
    call ?j_00039649@@YAXXZ
    db 0D9h, 044h, 024h, 02Ch, 0D8h, 005h
    dd ?g_bfmeDirectionWeight1285@@3MA
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 044h, 024h, 02Ch, 0D9h, 05Ch, 024h, 034h, 08Bh, 031h, 050h, 06Ah
    db 000h
    call ?j_0001c675@@YAXXZ
    db 08Bh, 04Ch, 024h, 030h, 08Bh, 054h, 024h, 02Ch, 050h, 051h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 052h, 0FFh, 056h, 01Ch, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 044h, 024h, 034h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 0D8h, 04Ch, 024h, 034h, 05Fh, 0D9h, 044h, 024h, 02Ch, 0D8h, 04Ch, 024h, 02Ch, 0DEh, 0C1h, 0D9h
    db 044h, 024h, 034h, 0D8h, 04Ch, 024h, 034h, 0DEh, 0C1h, 0D9h, 0FAh, 0D9h, 044h, 024h, 014h, 0DCh
    db 0C0h, 0DEh, 0C1h, 0D8h, 044h, 024h, 00Ch, 0D8h, 074h, 024h, 010h, 0D9h, 05Ch, 024h, 03Ch, 0D9h
    db 080h, 0ACh, 001h, 000h, 000h, 0D9h, 0E0h, 0D9h, 044h, 024h, 03Ch, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 005h, 07Ah, 006h, 0D9h, 05Ch, 024h, 03Ch, 0EBh, 002h, 0DDh, 0D8h, 08Bh, 04Ch, 024h, 03Ch
    db 08Bh, 054h, 024h, 014h, 051h, 08Bh, 04Ch, 024h, 020h, 052h, 08Dh, 044h, 024h, 028h, 050h
    call ?j_0000ce28@@YAXXZ
    db 05Eh, 05Dh, 05Bh, 083h, 0C4h, 02Ch, 0C2h, 004h, 000h
?d_0029ac40@@YAXXZ ENDP
_TEXT$d0069ac40 ENDS
_TEXT SEGMENT

; ghidra: FUN_0069b120  retail @ 0x0029B120 size 137
public ?d_0029b120@@YAXXZ
?d_0029b120@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 4Eh, 20h, 8Bh, 46h, 24h, 8Bh, 7Eh, 08h, 6Ah, 00h, 8Dh
    db 54h, 24h, 10h, 52h, 51h, 50h, 50h, 0E8h, 3Fh, 9Ch, 0D7h, 0FFh, 89h, 46h, 24h, 8Ah
    db 46h, 5Fh, 83h, 0C4h, 14h, 84h, 0C0h, 0C7h, 46h, 50h, 00h, 00h, 00h, 00h, 0C7h, 46h
    db 54h, 00h, 00h, 00h, 00h, 75h, 24h, 8Bh, 46h, 04h, 8Ah, 48h, 59h, 84h, 0C9h, 75h
    db 1Ah, 8Ah, 44h, 24h, 0Ch, 84h, 0C0h, 75h, 3Bh, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 57h, 8Bh
    db 0CEh, 0E8h, 64h, 0A6h, 0D7h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h, 8Bh, 8Fh, 1Ch, 01h, 00h
    db 00h, 0B8h, 00h, 00h, 08h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Fh, 1Ch, 01h
    db 00h, 00h, 8Bh, 0CFh, 0E8h, 84h, 67h, 0D8h, 0FFh, 6Ah, 00h, 6Ah, 08h, 8Bh, 0CFh, 0E8h
    db 62h, 93h, 0D7h, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_0029b120@@YAXXZ ENDP

; ghidra: FUN_0069b310  retail @ 0x0029B310 size 40
public ?d_0029b310@@YAXXZ
?d_0029b310@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 8Dh, 04h, 24h, 50h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0C7h
    db 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h
    db 50h, 0EFh, 0D8h, 0FFh, 83h, 0C4h, 0Ch, 0C3h
?d_0029b310@@YAXXZ ENDP

; ghidra: FUN_0069b350  retail @ 0x0029B350 size 315
_TEXT ENDS
_TEXT$d0069b350 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0069B350 size 315
public ?d_0029b350@@YAXXZ
?d_0029b350@@YAXXZ PROC
    db 083h, 0ECh, 018h, 053h, 08Bh, 05Ch, 024h, 020h, 084h, 0DBh, 056h, 08Bh, 0F1h, 057h, 08Bh, 07Eh
    db 008h, 075h, 008h, 06Ah, 001h, 057h
    call ?j_000157da@@YAXXZ
    db 0FFh, 046h, 054h, 08Bh, 056h, 020h, 08Bh, 04Eh, 024h, 02Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 02Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 083h, 0F8h, 002h, 07Dh, 011h
    db 053h, 08Bh, 0CEh
    call ?j_000184a8@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 018h, 0C2h, 004h, 000h, 08Bh, 056h, 020h, 08Dh, 00Ch, 040h, 0D9h
    db 044h, 08Ah, 0F4h, 08Dh, 00Ch, 08Ah, 08Dh, 044h, 040h, 0FAh, 0D8h, 024h, 082h, 0D9h, 05Ch, 024h
    db 00Ch, 0D9h, 041h, 0F8h, 0D8h, 061h, 0ECh, 0D9h, 054h, 024h, 010h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h
    db 044h, 024h, 00Ch, 0D8h, 04Ch, 024h, 00Ch, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 028h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 028h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 01Ah, 08Bh, 04Ch, 024h
    db 028h, 0DDh, 0D8h, 051h
    call ?j_00027a43@@YAXXZ
    db 0D9h, 044h, 024h, 00Ch, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 00Ch, 0D8h, 04Ch, 024h, 010h, 0D9h, 046h
    db 03Ch, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 0D9h, 046h, 038h, 08Bh, 011h, 0D8h, 066h, 02Ch, 06Ah, 000h, 0D9h, 05Ch, 024h, 01Ch, 0D8h, 066h
    db 030h, 0D9h, 0C0h, 0DEh, 0C9h, 0D9h, 044h, 024h, 01Ch, 0D8h, 04Ch, 024h, 01Ch, 0DEh, 0C1h, 0D9h
    db 0FAh, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 044h, 024h, 010h, 0D8h, 0C9h, 0D8h, 047h, 038h, 0D9h, 05Ch, 024h, 010h, 0D8h, 0C9h, 0D8h
    db 047h, 03Ch, 0D9h, 05Ch, 024h, 014h, 08Bh, 044h, 024h, 014h, 050h, 08Bh, 044h, 024h, 014h, 0DDh
    db 0D8h, 050h, 0FFh, 052h, 018h, 0D9h, 05Ch, 024h, 014h, 0D9h, 046h, 044h, 083h, 0ECh, 008h, 0D8h
    db 00Dh
    dd g_Va010C0908
    db 08Dh, 04Ch, 024h, 014h, 0D9h, 05Ch, 024h, 004h, 0D9h, 046h, 048h, 0D8h, 00Dh
    dd g_Va010C0904
    db 0D9h, 01Ch, 024h, 051h, 08Bh, 0CEh
    call ?j_0000ce28@@YAXXZ
    db 05Fh, 0C6h, 046h, 05Eh, 001h, 05Eh, 05Bh, 083h, 0C4h, 018h, 0C2h, 004h, 000h
?d_0029b350@@YAXXZ ENDP
_TEXT$d0069b350 ENDS
_TEXT SEGMENT

; ghidra: FUN_0069b4e0  retail @ 0x0029B4E0 size 512
public ?d_0029b4e0@@YAXXZ
?d_0029b4e0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0E9h, 8Bh, 4Dh, 24h, 2Bh, 4Dh, 20h, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 0Fh, 84h, 0DBh, 01h, 00h
    db 00h, 8Bh, 45h, 04h, 56h, 8Bh, 75h, 08h, 57h, 8Bh, 78h, 50h, 85h, 0FFh, 89h, 44h
    db 24h, 10h, 74h, 1Ch, 8Bh, 0CFh, 0E8h, 5Ch, 6Ah, 0D7h, 0FFh, 84h, 0C0h, 75h, 11h, 6Ah
    db 00h, 6Ah, 00h, 6Ah, 00h, 8Dh, 4Eh, 38h, 51h, 8Bh, 0CFh, 0E8h, 0F1h, 05h, 0D8h, 0FFh
    db 8Ah, 86h, 18h, 01h, 00h, 00h, 32h, 0DBh, 84h, 0C0h, 0BFh, 00h, 00h, 00h, 01h, 79h
    db 5Eh, 8Bh, 8Eh, 1Ch, 01h, 00h, 00h, 0B8h, 00h, 00h, 08h, 00h, 85h, 0C8h, 75h, 0Fh
    db 0Bh, 0C8h, 89h, 8Eh, 1Ch, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0BEh, 63h, 0D8h, 0FFh, 8Ah
    db 86h, 18h, 01h, 00h, 00h, 84h, 0C0h, 79h, 18h, 8Bh, 86h, 18h, 01h, 00h, 00h, 25h
    db 7Fh, 0FFh, 0FFh, 0FFh, 8Bh, 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 9Ch, 63h, 0D8h
    db 0FFh, 8Bh, 86h, 1Ch, 01h, 00h, 00h, 85h, 0C7h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FEh
    db 8Bh, 0CEh, 89h, 86h, 1Ch, 01h, 00h, 00h, 0E8h, 80h, 63h, 0D8h, 0FFh, 0B3h, 01h, 8Ah
    db 45h, 5Ch, 84h, 0C0h, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 8Bh, 45h, 58h, 85h, 0C0h, 7Eh
    db 0Dh, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 84h, 87h, 00h, 00h, 00h, 8Bh, 86h
    db 1Ch, 01h, 00h, 00h, 85h, 0C7h, 74h, 12h, 25h, 0FFh, 0FFh, 0FFh, 0FEh, 8Bh, 0CEh, 89h
    db 86h, 1Ch, 01h, 00h, 00h, 0E8h, 43h, 63h, 0D8h, 0FFh, 8Ah, 86h, 18h, 01h, 00h, 00h
    db 84h, 0C0h, 79h, 18h, 8Bh, 86h, 18h, 01h, 00h, 00h, 25h, 7Fh, 0FFh, 0FFh, 0FFh, 8Bh
    db 0CEh, 89h, 86h, 18h, 01h, 00h, 00h, 0E8h, 21h, 63h, 0D8h, 0FFh, 0F6h, 86h, 44h, 03h
    db 00h, 00h, 01h, 0Fh, 84h, 84h, 00h, 00h, 00h, 8Bh, 8Eh, 14h, 01h, 00h, 00h, 0B8h
    db 00h, 00h, 00h, 20h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 14h, 01h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 0F6h, 62h, 0D8h, 0FFh, 8Bh, 8Eh, 1Ch, 01h, 00h, 00h, 0B8h, 00h, 00h
    db 08h, 00h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 1Ch, 01h, 00h, 00h, 8Bh, 0CEh
    db 0E8h, 0D8h, 62h, 0D8h, 0FFh, 84h, 0DBh, 8Bh, 7Ch, 24h, 10h, 74h, 1Bh, 8Bh, 16h, 8Bh
    db 0CEh, 0FFh, 52h, 28h, 85h, 0C0h, 74h, 10h, 8Bh, 06h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 50h
    db 28h, 8Bh, 0C8h, 0E8h, 0D1h, 1Dh, 0D9h, 0FFh, 8Ah, 45h, 5Dh, 84h, 0C0h, 75h, 07h, 8Ah
    db 47h, 58h, 84h, 0C0h, 74h, 5Bh, 8Bh, 4Dh, 54h, 3Bh, 4Fh, 24h, 7Dh, 53h, 6Ah, 00h
    db 8Bh, 0CDh, 0E8h, 87h, 85h, 0D8h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h, 8Bh, 8Eh, 1Ch
    db 01h, 00h, 00h, 0B8h, 00h, 00h, 00h, 02h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh
    db 1Ch, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 72h, 62h, 0D8h, 0FFh, 8Bh, 7Ch, 24h, 10h, 8Bh
    db 57h, 1Ch, 8Bh, 47h, 18h, 68h, 0C7h, 02h, 00h, 00h, 68h, 0C0h, 0Ch, 0Ch, 01h, 52h
    db 50h, 0E8h, 0E8h, 64h, 0D6h, 0FFh, 83h, 0C4h, 10h, 89h, 45h, 58h, 0E9h, 7Ch, 0FFh, 0FFh
    db 0FFh, 6Ah, 01h, 8Bh, 0CDh, 0E8h, 0CEh, 0CDh, 0D7h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h
?d_0029b4e0@@YAXXZ ENDP

; ghidra: FUN_0069b760  retail @ 0x0029B760 size 862
_TEXT ENDS
_TEXT$d0069b760 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0069B760 size 862
public ?d_0029b760@@YAXXZ
?d_0029b760@@YAXXZ PROC
    db 083h, 0ECh, 04Ch, 053h, 055h, 056h, 08Bh, 0F1h, 08Bh, 046h, 0F4h, 089h, 044h, 024h, 00Ch, 08Ah
    db 046h, 04Ch, 032h, 0DBh, 084h, 0C0h, 057h, 08Bh, 07Eh, 0F8h, 0C6h, 046h, 04Eh, 000h, 00Fh, 084h
    db 0A9h, 000h, 000h, 000h, 08Bh, 046h, 048h, 085h, 0C0h, 00Fh, 08Eh, 09Eh, 000h, 000h, 000h, 0F6h
    db 087h, 044h, 003h, 000h, 000h, 001h, 00Fh, 085h, 091h, 000h, 000h, 000h, 048h, 085h, 0C0h, 089h
    db 046h, 048h, 00Fh, 08Fh, 085h, 000h, 000h, 000h, 08Bh, 087h, 01Ch, 001h, 000h, 000h, 0BDh, 000h
    db 000h, 000h, 002h, 085h, 0C5h, 074h, 03Ch, 08Bh, 0C8h, 081h, 0E1h, 0FFh, 0FFh, 0FFh, 0FDh, 089h
    db 08Fh, 01Ch, 001h, 000h, 000h, 08Bh, 0CFh
    call ?j_0002191d@@YAXXZ
    db 08Bh, 087h, 020h, 001h, 000h, 000h, 085h, 0C5h, 075h, 00Fh, 00Bh, 0C5h, 08Bh, 0CFh, 089h, 087h
    db 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 051h, 020h, 089h, 056h, 048h, 0B3h, 001h, 0EBh, 03Ah, 068h, 099h
    db 000h, 000h, 000h, 08Dh, 08Fh, 010h, 001h, 000h, 000h
    call ?j_0000666d@@YAXXZ
    db 084h, 0C0h, 074h, 01Ch, 08Bh, 087h, 020h, 001h, 000h, 000h, 085h, 0C5h, 074h, 012h, 025h, 0FFh
    db 0FFh, 0FFh, 0FDh, 08Bh, 0CFh, 089h, 087h, 020h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Dh, 04Eh, 0F0h, 06Ah, 000h
    call ?j_0000d81e@@YAXXZ
    db 08Bh, 046h, 010h, 08Bh, 04Eh, 014h, 02Bh, 0C8h, 0B8h, 0ABh, 0AAh, 0AAh, 02Ah, 0F7h, 0E9h, 08Bh
    db 04Eh, 040h, 0D1h, 0FAh, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 03Bh, 0C8h, 072h, 039h, 083h
    db 0C6h, 0F0h, 08Bh, 0CEh
    call ?j_000294f6@@YAXXZ
    db 08Bh, 04Eh, 024h, 02Bh, 04Eh, 020h, 0B8h, 0ABh, 0AAh, 0AAh, 02Ah, 0F7h, 0E9h, 0D1h, 0FAh, 08Bh
    db 0CAh, 0C1h, 0E9h, 01Fh, 003h, 0CAh, 00Fh, 085h, 01Fh, 002h, 000h, 000h, 08Ah, 046h, 05Ch, 084h
    db 0C0h, 00Fh, 084h, 034h, 002h, 000h, 000h, 08Bh, 046h, 058h, 0E9h, 023h, 002h, 000h, 000h, 084h
    db 0DBh, 074h, 01Bh, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 028h, 085h, 0C0h, 074h, 010h, 08Bh, 007h
    db 06Ah, 000h, 08Bh, 0CFh, 0FFh, 050h, 028h, 08Bh, 0C8h
    call ?j_0002d439@@YAXXZ
    db 08Bh, 046h, 040h, 08Bh, 056h, 010h, 08Dh, 00Ch, 040h, 08Dh, 02Ch, 08Ah, 08Bh, 04Ch, 024h, 010h
    db 08Ah, 051h, 041h, 084h, 0D2h, 00Fh, 084h, 0E4h, 000h, 000h, 000h, 08Ah, 051h, 040h, 084h, 0D2h
    db 00Fh, 085h, 0D9h, 000h, 000h, 000h, 085h, 0C0h, 00Fh, 08Eh, 0D1h, 000h, 000h, 000h, 0D9h, 045h
    db 008h, 08Bh, 046h, 044h, 085h, 0C0h, 0D8h, 065h, 0FCh, 0D9h, 045h, 004h, 0D8h, 065h, 0F8h, 0D9h
    db 054h, 024h, 010h, 0D9h, 045h, 000h, 0D8h, 065h, 0F4h, 0D9h, 05Ch, 024h, 014h, 0D9h, 05Ch, 024h
    db 018h, 0D9h, 05Ch, 024h, 01Ch, 07Eh, 018h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 0D9h, 080h, 0ACh, 001h, 000h, 000h, 0D8h, 049h, 04Ch, 0D8h, 00Dh
    dd ?g_bfmeScaleBC@@3MA
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 014h, 0D8h, 04Ch, 024h, 014h, 0D9h, 044h, 024h, 010h
    db 0D8h, 04Ch, 024h, 010h, 0DEh, 0C1h, 0D9h, 044h, 024h, 01Ch, 0D8h, 04Ch, 024h, 01Ch, 0DEh, 0C1h
    db 0D9h, 05Ch, 024h, 010h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 010h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 026h, 08Bh, 04Ch, 024h
    db 010h, 051h
    call ?j_00027a43@@YAXXZ
    db 0D9h, 044h, 024h, 014h, 0D8h, 0C9h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 018h, 0D8h, 0C9h
    db 0D9h, 05Ch, 024h, 018h, 0D8h, 04Ch, 024h, 01Ch, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 055h, 000h, 08Bh
    db 045h, 004h, 08Bh, 04Dh, 008h, 089h, 054h, 024h, 020h, 08Dh, 054h, 024h, 014h, 089h, 044h, 024h
    db 024h, 052h, 08Dh, 044h, 024h, 024h, 089h, 04Ch, 024h, 02Ch, 050h, 08Dh, 04Ch, 024h, 034h
    call ?buildTransformMatrix@Matrix3D@@QAEXABVVector3@@0@Z
    db 08Dh, 04Ch, 024h, 02Ch, 051h, 08Bh, 04Eh, 0F8h
    call ?j_000361ce@@YAXXZ
    db 0EBh, 009h, 08Bh, 04Eh, 0F8h, 055h
    call ?j_0003a1a7@@YAXXZ
    db 08Bh, 056h, 014h, 08Bh, 05Eh, 010h, 08Bh, 04Eh, 040h, 02Bh, 0D3h, 0B8h, 0ABh, 0AAh, 0AAh, 02Ah
    db 0F7h, 0EAh, 0D1h, 0FAh, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 08Dh, 054h, 002h, 0FFh, 03Bh, 0CAh, 073h
    db 029h, 08Dh, 044h, 049h, 003h, 0C6h, 087h, 086h, 001h, 000h, 000h, 001h, 08Bh, 0CBh, 08Bh, 014h
    db 081h, 08Dh, 004h, 081h, 081h, 0C7h, 078h, 001h, 000h, 000h, 089h, 017h, 08Bh, 048h, 004h, 089h
    db 04Fh, 004h, 08Bh, 050h, 008h, 089h, 057h, 008h, 0EBh, 06Fh, 0D9h, 047h, 038h, 08Bh, 04Dh, 008h
    db 0D9h, 047h, 03Ch, 08Bh, 047h, 040h, 0D9h, 045h, 000h, 089h, 04Ch, 024h, 01Ch, 0D9h, 045h, 004h
    db 089h, 044h, 024h, 028h, 0D9h, 0C9h, 0C6h, 087h, 086h, 001h, 000h, 000h, 001h, 0DCh, 0C0h, 081h
    db 0C7h, 078h, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 014h, 0DCh, 0C0h, 0D9h, 044h, 024h, 01Ch, 0DCh
    db 0C0h, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 014h, 0D8h, 0E3h, 0D9h, 05Ch, 024h, 014h, 08Bh
    db 054h, 024h, 014h, 089h, 017h, 0D8h, 0E1h, 0D9h, 05Ch, 024h, 018h, 08Bh, 044h, 024h, 018h, 089h
    db 047h, 004h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 01Ch, 0D8h, 064h, 024h, 028h, 0D9h, 05Ch
    db 024h, 01Ch, 08Bh, 04Ch, 024h, 01Ch, 089h, 04Fh, 008h, 08Bh, 056h, 0F8h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 052h
    call ?j_00025d56@@YAXXZ
    db 0FFh, 046h, 040h, 08Bh, 04Eh, 014h, 02Bh, 04Eh, 010h, 0B8h, 0ABh, 0AAh, 0AAh, 02Ah, 0F7h, 0E9h
    db 0D1h, 0FAh, 08Bh, 0CAh, 0C1h, 0E9h, 01Fh, 003h, 0CAh, 074h, 00Dh, 05Fh, 05Eh, 05Dh, 0B8h, 001h
    db 000h, 000h, 000h, 05Bh, 083h, 0C4h, 04Ch, 0C3h, 08Ah, 046h, 04Ch, 084h, 0C0h, 074h, 00Ch, 08Bh
    db 046h, 048h, 085h, 0C0h, 0B8h, 001h, 000h, 000h, 000h, 07Fh, 005h, 0B8h, 0FFh, 0FFh, 0FFh, 03Fh
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 04Ch, 0C3h
?d_0029b760@@YAXXZ ENDP
_TEXT$d0069b760 ENDS
_TEXT SEGMENT

; ghidra: FUN_0069bbc0  retail @ 0x0029BBC0 size 22
public ?d_0029bbc0@@YAXXZ
?d_0029bbc0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0F8h, 01h, 74h, 08h, 83h, 0F8h, 03h, 74h, 03h, 33h, 0C0h, 0C3h
    db 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_0029bbc0@@YAXXZ ENDP

; ghidra: FUN_0069bcc0  retail @ 0x0029BCC0 size 66
public ?d_0029bcc0@@YAXXZ
?d_0029bcc0@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 90h, 0Dh, 0Ch, 01h, 89h, 48h, 04h, 89h, 48h, 08h
    db 89h, 48h, 0Ch, 0C7h, 40h, 10h, 01h, 00h, 00h, 00h, 89h, 48h, 14h, 89h, 48h, 18h
    db 89h, 48h, 1Ch, 89h, 48h, 20h, 89h, 48h, 24h, 89h, 48h, 28h, 89h, 48h, 2Ch, 89h
    db 48h, 30h, 88h, 48h, 34h, 89h, 48h, 38h, 89h, 48h, 3Ch, 89h, 48h, 40h, 89h, 48h
    db 44h, 0C3h
?d_0029bcc0@@YAXXZ ENDP

; ghidra: FUN_0069bd20  retail @ 0x0029BD20 size 36
public ?d_0029bd20@@YAXXZ
?d_0029bd20@@YAXXZ PROC
    db 0A1h, 24h, 0D5h, 2Eh, 01h, 83h, 78h, 30h, 01h, 75h, 06h, 8Bh, 51h, 14h, 89h, 51h
    db 44h, 0A1h, 24h, 0D5h, 2Eh, 01h, 0D9h, 40h, 38h, 0D8h, 49h, 18h, 0D8h, 41h, 44h, 0E9h
    db 0F4h, 0B0h, 75h, 00h
?d_0029bd20@@YAXXZ ENDP

; ghidra: FUN_0069bd80  retail @ 0x0029BD80 size 74
public ?d_0029bd80@@YAXXZ
?d_0029bd80@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 56h, 8Bh, 73h, 08h, 85h, 0F6h, 74h, 3Ah, 57h, 8Bh, 7Ch, 24h, 10h
    db 8Bh, 46h, 04h, 83h, 0F8h, 01h, 74h, 05h, 83h, 0F8h, 03h, 75h, 0Fh, 8Bh, 46h, 08h
    db 50h, 8Bh, 0CFh, 0E8h, 63h, 2Ah, 0DAh, 0FFh, 84h, 0C0h, 75h, 0Dh, 8Bh, 76h, 3Ch, 85h
    db 0F6h, 75h, 0DDh, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h, 8Bh, 4Eh, 10h, 8Bh, 03h, 51h, 8Bh
    db 0CBh, 0FFh, 50h, 20h, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_0029bd80@@YAXXZ ENDP

; ghidra: FUN_0069bde0  retail @ 0x0029BDE0 size 98
public ?d_0029bde0@@YAXXZ
?d_0029bde0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Ah, 4Ch, 24h, 14h, 8Bh, 77h, 0Ch, 33h, 0DBh, 84h, 0C9h
    db 0Fh, 95h, 0C3h, 8Dh, 1Ch, 9Dh, 01h, 00h, 00h, 00h, 85h, 0DBh, 74h, 3Eh, 55h, 8Bh
    db 6Ch, 24h, 14h, 85h, 0F6h, 74h, 34h, 8Bh, 46h, 04h, 83h, 0F8h, 01h, 74h, 05h, 83h
    db 0F8h, 03h, 75h, 20h, 8Bh, 46h, 08h, 50h, 8Bh, 0CDh, 0E8h, 0ECh, 29h, 0DAh, 0FFh, 84h
    db 0C0h, 74h, 11h, 8Bh, 4Eh, 10h, 8Bh, 07h, 51h, 8Bh, 0CFh, 0FFh, 50h, 20h, 8Bh, 77h
    db 0Ch, 4Bh, 0EBh, 03h, 8Bh, 76h, 40h, 85h, 0DBh, 75h, 0C8h, 5Dh, 5Fh, 5Eh, 5Bh, 0C2h
    db 08h, 00h
?d_0029bde0@@YAXXZ ENDP

; ghidra: FUN_0069be60  retail @ 0x0029BE60 size 70
public ?d_0029be60@@YAXXZ
?d_0029be60@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 56h, 8Bh, 73h, 08h, 85h, 0F6h, 74h, 36h, 55h, 8Bh, 6Ch, 24h, 10h
    db 57h, 83h, 7Eh, 04h, 01h, 75h, 21h, 8Bh, 46h, 08h, 50h, 8Bh, 0CDh, 0E8h, 89h, 29h
    db 0DAh, 0FFh, 84h, 0C0h, 74h, 12h, 8Bh, 4Eh, 10h, 8Bh, 03h, 8Bh, 7Eh, 3Ch, 51h, 8Bh
    db 0CBh, 0FFh, 50h, 20h, 8Bh, 0F7h, 0EBh, 03h, 8Bh, 76h, 3Ch, 85h, 0F6h, 75h, 0D2h, 5Fh
    db 5Dh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_0029be60@@YAXXZ ENDP

; ghidra: FUN_0069bf00  retail @ 0x0029BF00 size 54
public ?d_0029bf00@@YAXXZ
?d_0029bf00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 0FFh, 50h, 48h, 85h, 0C0h, 74h, 1Bh, 8Bh, 7Ch, 24h
    db 0Ch, 83h, 78h, 04h, 02h, 75h, 05h, 39h, 78h, 0Ch, 74h, 13h, 8Bh, 16h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 4Ch, 85h, 0C0h, 75h, 0E9h, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h, 5Fh
    db 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_0029bf00@@YAXXZ ENDP

; ghidra: FUN_0069bfb0  retail @ 0x0029BFB0 size 72
public ?d_0029bfb0@@YAXXZ
?d_0029bfb0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 0C6h, 86h, 0B5h, 00h, 00h, 00h, 01h, 74h
    db 21h, 8Bh, 4Eh, 08h, 8Bh, 41h, 04h, 48h, 74h, 06h, 48h, 74h, 1Eh, 48h, 75h, 12h
    db 8Bh, 41h, 10h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 20h, 8Bh, 46h, 08h, 85h, 0C0h
    db 75h, 0DFh, 0C6h, 86h, 0B5h, 00h, 00h, 00h, 00h, 5Eh, 0C3h, 8Bh, 49h, 0Ch, 8Bh, 06h
    db 51h, 8Bh, 0CEh, 0FFh, 50h, 10h, 0EBh, 0E3h
?d_0029bfb0@@YAXXZ ENDP

; ghidra: FUN_0069c090  retail @ 0x0029C090 size 48
public ?d_0029c090@@YAXXZ
?d_0029c090@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 01h, 0C3h, 56h, 8Bh, 0B0h, 0F0h, 01h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 16h, 8Dh, 48h, 0Ch, 8Bh, 01h, 0FFh, 50h, 6Ch, 85h, 0C0h
    db 75h, 0Ch, 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0EAh, 33h, 0C0h, 5Eh, 0C3h
?d_0029c090@@YAXXZ ENDP

; ghidra: FUN_0069c290  retail @ 0x0029C290 size 42
public ?d_0029c290@@YAXXZ
?d_0029c290@@YAXXZ PROC
    db 33h, 0C0h, 56h, 8Bh, 0F1h, 89h, 46h, 3Ch, 89h, 46h, 40h, 89h, 46h, 38h, 0F6h, 44h
    db 24h, 08h, 01h, 0C7h, 06h, 90h, 0Dh, 0Ch, 01h, 74h, 09h, 56h, 0E8h, 0FFh, 5Bh, 5Eh
    db 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0029c290@@YAXXZ ENDP

; ghidra: FUN_0069c2f0  retail @ 0x0029C2F0 size 53
public ?d_0029c2f0@@YAXXZ
?d_0029c2f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0E8h, 0E8h, 29h, 45h, 0D8h, 0FFh, 85h, 0C0h, 74h, 22h, 8Bh
    db 4Eh, 0E8h, 57h, 0E8h, 1Ch, 45h, 0D8h, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 3Eh, 51h, 8Dh
    db 88h, 84h, 06h, 00h, 00h, 0E8h, 72h, 71h, 0DAh, 0FFh, 50h, 8Bh, 0CEh, 0FFh, 57h, 24h
    db 5Fh, 5Eh, 0C2h, 04h, 00h
?d_0029c2f0@@YAXXZ ENDP

; ghidra: FUN_0069c340  retail @ 0x0029C340 size 42
public ?d_0029c340@@YAXXZ
?d_0029c340@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 85h, 0D2h, 74h, 1Fh, 8Bh, 41h, 08h, 85h, 0C0h, 74h, 18h, 8Bh
    db 80h, 70h, 03h, 00h, 00h, 83h, 0F8h, 0FFh, 74h, 0Dh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 50h, 52h, 0E8h, 12h, 0DFh, 0D9h, 0FFh, 0C2h, 04h, 00h
?d_0029c340@@YAXXZ ENDP

; ghidra: FUN_0069c380  retail @ 0x0029C380 size 111
public ?d_0029c380@@YAXXZ
?d_0029c380@@YAXXZ PROC
    db 53h, 55h, 8Bh, 0D9h, 8Bh, 43h, 20h, 56h, 8Dh, 6Bh, 20h, 57h, 8Bh, 0CDh, 0FFh, 50h
    db 48h, 8Bh, 0F8h, 85h, 0FFh, 74h, 49h, 83h, 7Fh, 04h, 03h, 75h, 34h, 8Bh, 4Bh, 08h
    db 0E8h, 7Fh, 44h, 0D8h, 0FFh, 8Bh, 4Fh, 08h, 8Bh, 0F0h, 8Bh, 47h, 10h, 50h, 81h, 0C6h
    db 84h, 06h, 00h, 00h, 51h, 8Bh, 0CEh, 0E8h, 0EDh, 0E3h, 0D6h, 0FFh, 50h, 8Bh, 0CEh, 0E8h
    db 40h, 1Eh, 0D8h, 0FFh, 0D8h, 1Dh, 34h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 74h
    db 17h, 8Bh, 55h, 00h, 57h, 8Bh, 0CDh, 0FFh, 52h, 4Ch, 8Bh, 0F8h, 85h, 0FFh, 75h, 0B7h
    db 8Bh, 43h, 28h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h
?d_0029c380@@YAXXZ ENDP

; ghidra: FUN_0069c410  retail @ 0x0029C410 size 32
public ?d_0029c410@@YAXXZ
?d_0029c410@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 24h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 37h, 0B7h, 5Eh, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_0029c410@@YAXXZ ENDP

; ghidra: FUN_0069c440  retail @ 0x0029C440 size 37
public ?d_0029c440@@YAXXZ
?d_0029c440@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 8Dh, 4Ch, 81h, 38h, 51h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 02h, 0B7h, 5Eh, 00h, 8Bh, 0C6h
    db 5Eh, 59h, 0C2h, 08h, 00h
?d_0029c440@@YAXXZ ENDP

; ghidra: FUN_0069c560  retail @ 0x0029C560 size 67
public ?d_0029c560@@YAXXZ
?d_0029c560@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 08h, 2Bh, 0C7h, 0C1h, 0F8h, 03h, 85h, 0C0h
    db 7Eh, 2Bh, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 0D8h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 57h, 8Bh, 0CEh, 0E8h, 08h, 0B7h, 5Eh, 00h, 8Bh, 47h, 04h, 89h, 46h, 04h, 83h, 0C7h
    db 08h, 83h, 0C6h, 08h, 4Bh, 75h, 0E9h, 8Bh, 0C6h, 5Eh, 5Bh, 5Fh, 0C3h, 8Bh, 44h, 24h
    db 10h, 5Fh, 0C3h
?d_0029c560@@YAXXZ ENDP
_TEXT ENDS
END
