.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??_7Rva007F01B0@@6B@:BYTE
EXTERN ?Rva009AA260Scale@@YAHPAURva009AA260Context@@PBEHIIPAEIII@Z:NEAR
EXTERN ?Rva009AAFE0BuildTable@@YAXPAURva009AAFE0Context@@PBE@Z:NEAR
EXTERN ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z:NEAR
EXTERN ?Rva009B64A0BuildTone@@YAXPAE@Z:NEAR
EXTERN ?Rva01142BA0Table@@3QBGB:BYTE
EXTERN ?bfmeGoUSC@@YAHPAXH@Z:NEAR
EXTERN ?g_bfmeSlotB44@@3PAXA:BYTE
EXTERN ?g_rva01356940@@3PAHA:BYTE
EXTERN ?step@Rva009AAF80State@@QAEHXZ:NEAR
EXTERN ___security_cookie:BYTE
EXTERN __imp_?i_009f6ec0@@YAXXZ:BYTE
EXTERN __imp__CreateCompatibleDC@4:BYTE
EXTERN __imp__DeleteDC@4:BYTE
EXTERN __imp__DeleteObject@4:BYTE
EXTERN __imp__SelectObject@8:BYTE
EXTERN __imp__SetBkColor@8:BYTE
EXTERN __imp__SetTextColor@8:BYTE
EXTERN _report_failure:NEAR
EXTERN g_Va01142720:BYTE
EXTERN g_Va01142722:BYTE
EXTERN g_Va01142724:BYTE
EXTERN g_Va011427E0:BYTE
EXTERN g_Va011430B0:BYTE
EXTERN g_Va011430C8:BYTE
EXTERN g_Va01143108:BYTE
EXTERN g_Va01143124:BYTE
EXTERN g_Va01143140:BYTE
EXTERN g_Va011432CC:BYTE
EXTERN g_Va012D7F58:BYTE
EXTERN g_Va012D8058:BYTE
EXTERN g_Va01356EA0:BYTE
EXTERN g_Va01356EC0:BYTE
EXTERN g_Va01356FE0:BYTE
EXTERN g_Va013590B0:BYTE
EXTERN g_Va013590B4:BYTE
EXTERN g_Va013590C0:BYTE
EXTERN g_Va013590CC:BYTE
EXTERN g_Va013590E0:BYTE
EXTERN g_Va01359104:BYTE
_TEXT SEGMENT

; ghidra: FUN_00da4740  retail @ 0x009A4740 size 750
public ?d_009a4740@@YAXXZ
?d_009a4740@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 02h, 06h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 55h, 56h, 57h, 33h, 0DBh, 6Ah, 18h
    db 8Bh, 0F1h, 89h, 5Ch, 24h, 14h, 0E8h, 0D5h, 9Dh, 0E8h, 0FFh, 89h, 44h, 24h, 14h, 89h
    db 5Ch, 24h, 18h, 88h, 18h, 8Bh, 44h, 24h, 14h, 89h, 58h, 04h, 8Bh, 44h, 24h, 14h
    db 89h, 40h, 08h, 8Bh, 44h, 24h, 14h, 83h, 0C4h, 04h, 89h, 40h, 0Ch, 8Bh, 8Eh, 10h
    db 0AEh, 00h, 00h, 89h, 5Ch, 24h, 24h, 89h, 9Eh, 60h, 0C0h, 00h, 00h, 89h, 8Eh, 64h
    db 0C0h, 00h, 00h, 39h, 9Eh, 64h, 0C0h, 00h, 00h, 75h, 30h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 86h, 60h, 0C0h, 00h, 00h, 40h, 3Dh, 93h, 04h, 00h, 00h, 0Fh, 84h, 0BCh, 00h
    db 00h, 00h, 89h, 86h, 60h, 0C0h, 00h, 00h, 8Bh, 94h, 86h, 10h, 0AEh, 00h, 00h, 8Bh
    db 0C2h, 3Bh, 0C3h, 89h, 96h, 64h, 0C0h, 00h, 00h, 74h, 0D5h, 8Bh, 0BEh, 64h, 0C0h, 00h
    db 00h, 3Bh, 0FBh, 8Bh, 47h, 30h, 89h, 86h, 64h, 0C0h, 00h, 00h, 0Fh, 84h, 8Ch, 00h
    db 00h, 00h, 8Bh, 6Ch, 24h, 10h, 8Bh, 45h, 04h, 3Bh, 0C3h, 8Bh, 0CDh, 74h, 1Eh, 8Bh
    db 17h, 39h, 50h, 10h, 72h, 07h, 8Bh, 0C8h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch
    db 3Bh, 0C3h, 75h, 0EDh, 3Bh, 0CDh, 74h, 05h, 3Bh, 51h, 10h, 73h, 12h, 57h, 8Dh, 4Ch
    db 24h, 14h, 0E8h, 99h, 0FEh, 0FFh, 0FFh, 0C7h, 00h, 01h, 00h, 00h, 00h, 0EBh, 03h, 0FFh
    db 41h, 14h, 8Bh, 54h, 24h, 10h, 8Bh, 42h, 04h, 3Bh, 0C3h, 8Dh, 6Fh, 04h, 8Bh, 0CAh
    db 74h, 1Fh, 8Bh, 7Dh, 00h, 39h, 78h, 10h, 72h, 07h, 8Bh, 0C8h, 8Bh, 40h, 08h, 0EBh
    db 03h, 8Bh, 40h, 0Ch, 3Bh, 0C3h, 75h, 0EDh, 3Bh, 0CAh, 74h, 05h, 3Bh, 79h, 10h, 73h
    db 15h, 55h, 8Dh, 4Ch, 24h, 14h, 0E8h, 55h, 0FEh, 0FFh, 0FFh, 0C7h, 00h, 01h, 00h, 00h
    db 00h, 0E9h, 2Dh, 0FFh, 0FFh, 0FFh, 0FFh, 41h, 14h, 0E9h, 25h, 0FFh, 0FFh, 0FFh, 8Bh, 54h
    db 24h, 10h, 8Bh, 42h, 08h, 33h, 0FFh, 3Bh, 0C2h, 74h, 1Fh, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 48h, 14h, 3Bh, 0CFh, 76h, 02h, 8Bh, 0F9h, 50h, 0E8h, 0D1h, 6Fh, 0E8h, 0FFh, 8Bh
    db 54h, 24h, 14h, 83h, 0C4h, 04h, 3Bh, 0C2h, 75h, 0E6h, 39h, 5Ch, 24h, 14h, 74h, 45h
    db 8Bh, 7Ah, 04h, 3Bh, 0FBh, 74h, 25h, 8Bh, 4Fh, 0Ch, 51h, 8Dh, 4Ch, 24h, 14h, 0E8h
    db 0DCh, 0EBh, 0FFh, 0FFh, 8Bh, 6Fh, 08h, 6Ah, 18h, 57h, 0E8h, 21h, 9Dh, 0E8h, 0FFh, 83h
    db 0C4h, 08h, 3Bh, 0EBh, 8Bh, 0FDh, 75h, 0DFh, 8Bh, 54h, 24h, 10h, 89h, 52h, 08h, 8Bh
    db 54h, 24h, 10h, 89h, 5Ah, 04h, 8Bh, 44h, 24h, 10h, 89h, 40h, 0Ch, 8Bh, 54h, 24h
    db 10h, 89h, 5Ch, 24h, 14h, 8Bh, 46h, 18h, 89h, 9Eh, 08h, 0AEh, 00h, 00h, 89h, 86h
    db 0Ch, 0AEh, 00h, 00h, 39h, 9Eh, 0Ch, 0AEh, 00h, 00h, 75h, 2Ch, 8Dh, 64h, 24h, 00h
    db 8Bh, 86h, 08h, 0AEh, 00h, 00h, 40h, 3Dh, 7Bh, 2Bh, 00h, 00h, 0Fh, 84h, 0C2h, 00h
    db 00h, 00h, 89h, 86h, 08h, 0AEh, 00h, 00h, 8Bh, 4Ch, 86h, 18h, 8Bh, 0C1h, 3Bh, 0C3h
    db 89h, 8Eh, 0Ch, 0AEh, 00h, 00h, 74h, 0D8h, 8Bh, 0BEh, 0Ch, 0AEh, 00h, 00h, 3Bh, 0FBh
    db 8Bh, 47h, 30h, 89h, 86h, 0Ch, 0AEh, 00h, 00h, 0Fh, 84h, 95h, 00h, 00h, 00h, 8Bh
    db 42h, 04h, 3Bh, 0C3h, 8Bh, 0CAh, 74h, 24h, 8Bh, 2Fh, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 68h, 10h, 72h, 07h, 8Bh, 0C8h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch, 3Bh
    db 0C3h, 75h, 0EDh, 3Bh, 0CAh, 74h, 05h, 3Bh, 69h, 10h, 73h, 12h, 57h, 8Dh, 4Ch, 24h
    db 14h, 0E8h, 3Ah, 0FDh, 0FFh, 0FFh, 0C7h, 00h, 01h, 00h, 00h, 00h, 0EBh, 03h, 0FFh, 41h
    db 14h, 8Bh, 54h, 24h, 10h, 8Bh, 42h, 04h, 83h, 0C7h, 04h, 3Bh, 0C3h, 8Bh, 0CAh, 74h
    db 1Eh, 8Bh, 2Fh, 39h, 68h, 10h, 72h, 07h, 8Bh, 0C8h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh
    db 40h, 0Ch, 3Bh, 0C3h, 75h, 0EDh, 3Bh, 0CAh, 74h, 05h, 3Bh, 69h, 10h, 73h, 19h, 57h
    db 8Dh, 4Ch, 24h, 14h, 0E8h, 0F7h, 0FCh, 0FFh, 0FFh, 0C7h, 00h, 01h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 10h, 0E9h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 41h, 14h, 8Bh, 54h, 24h, 10h, 0E9h
    db 20h, 0FFh, 0FFh, 0FFh, 8Bh, 42h, 08h, 33h, 0F6h, 3Bh, 0C2h, 74h, 1Dh, 8Dh, 49h, 00h
    db 8Bh, 48h, 14h, 3Bh, 0CEh, 76h, 02h, 8Bh, 0F1h, 50h, 0E8h, 71h, 6Eh, 0E8h, 0FFh, 8Bh
    db 4Ch, 24h, 14h, 83h, 0C4h, 04h, 3Bh, 0C1h, 75h, 0E6h, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h
    db 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F5h, 0F5h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 5Fh
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h
?d_009a4740@@YAXXZ ENDP

; ghidra: FUN_00daa4f0  retail @ 0x009AA4F0 size 606
_TEXT ENDS
_TEXT$d00daa4f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAA4F0 size 606
public ?d_009aa4f0@@YAXXZ
?d_009aa4f0@@YAXXZ PROC
    db 083h, 0ECh, 018h, 053h, 055h, 056h, 08Bh, 074h, 024h, 028h, 08Bh, 046h, 070h, 08Bh, 06Eh, 05Ch
    db 08Bh, 04Eh, 058h, 089h, 044h, 024h, 010h, 00Fh, 0AFh, 0C5h, 08Dh, 044h, 008h, 0FFh, 033h, 0D2h
    db 0F7h, 0F1h, 08Bh, 05Eh, 060h, 057h, 033h, 0D2h, 08Bh, 0F8h, 08Bh, 046h, 074h, 089h, 044h, 024h
    db 01Ch, 00Fh, 0AFh, 046h, 064h, 08Dh, 044h, 018h, 0FFh, 0F7h, 0F3h, 083h, 0FDh, 003h, 089h, 07Ch
    db 024h, 020h, 089h, 044h, 024h, 010h, 075h, 027h, 08Dh, 057h, 002h, 0B8h, 056h, 055h, 055h, 055h
    db 0F7h, 0EAh, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 00Fh, 0AFh, 0C1h, 08Dh, 00Ch, 040h, 0B8h
    db 056h, 055h, 055h, 055h, 0F7h, 0E9h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h, 0C2h, 0EBh, 015h, 08Dh
    db 047h, 007h, 099h, 083h, 0E2h, 007h, 003h, 0C2h, 0C1h, 0F8h, 003h, 00Fh, 0AFh, 0C1h, 0C1h, 0E0h
    db 003h, 099h, 0F7h, 0FDh, 08Bh, 04Eh, 064h, 083h, 0F9h, 003h, 089h, 044h, 024h, 018h, 075h, 02Dh
    db 08Bh, 04Ch, 024h, 010h, 083h, 0C1h, 002h, 0B8h, 056h, 055h, 055h, 055h, 0F7h, 0E9h, 08Bh, 0CAh
    db 0C1h, 0E9h, 01Fh, 003h, 0CAh, 08Bh, 0C1h, 00Fh, 0AFh, 0C3h, 08Dh, 00Ch, 040h, 0B8h, 056h, 055h
    db 055h, 055h, 0F7h, 0E9h, 08Bh, 0EAh, 0C1h, 0EDh, 01Fh, 003h, 0EAh, 0EBh, 01Bh, 08Bh, 044h, 024h
    db 010h, 083h, 0C0h, 007h, 099h, 083h, 0E2h, 007h, 003h, 0C2h, 0C1h, 0F8h, 003h, 00Fh, 0AFh, 0C3h
    db 0C1h, 0E0h, 003h, 099h, 0F7h, 0F9h, 08Bh, 0E8h, 08Bh, 054h, 024h, 01Ch, 08Bh, 05Ch, 024h, 034h
    db 08Bh, 044h, 024h, 014h, 08Bh, 04Bh, 008h, 052h, 08Bh, 053h, 018h, 050h, 08Bh, 044h, 024h, 018h
    db 051h, 003h, 054h, 024h, 044h, 08Bh, 08Eh, 0B4h, 000h, 000h, 000h, 052h, 08Bh, 056h, 040h, 050h
    db 08Dh, 004h, 04Ah, 08Bh, 04Eh, 078h, 08Bh, 054h, 024h, 044h, 057h, 050h, 003h, 0CAh, 051h, 056h
    call ?Rva009AA260Scale@@YAHPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 033h, 0D2h, 083h, 0C4h, 024h, 085h, 0EDh, 089h, 044h, 024h, 034h, 089h, 054h, 024h, 02Ch, 07Eh
    db 04Ch, 08Bh, 04Ch, 024h, 018h, 02Bh, 04Ch, 024h, 014h, 089h, 04Ch, 024h, 024h, 0EBh, 00Ch, 08Bh
    db 04Ch, 024h, 024h, 0EBh, 006h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 07Bh, 008h, 00Fh, 0AFh
    db 0FAh, 003h, 07Bh, 018h, 003h, 07Ch, 024h, 014h, 003h, 07Ch, 024h, 038h, 08Bh, 0D1h, 0C1h, 0E9h
    db 002h, 033h, 0C0h, 0F3h, 0ABh, 08Bh, 0CAh, 08Bh, 054h, 024h, 02Ch, 083h, 0E1h, 003h, 042h, 03Bh
    db 0D5h, 0F3h, 0AAh, 089h, 054h, 024h, 02Ch, 07Ch, 0C6h, 08Bh, 07Ch, 024h, 020h, 08Bh, 054h, 024h
    db 01Ch, 03Bh, 0D5h, 089h, 054h, 024h, 02Ch, 07Dh, 034h, 08Bh, 0FFh, 08Bh, 07Bh, 008h, 08Bh, 04Ch
    db 024h, 018h, 00Fh, 0AFh, 0FAh, 003h, 07Bh, 018h, 003h, 07Ch, 024h, 038h, 08Bh, 0D1h, 0C1h, 0E9h
    db 002h, 033h, 0C0h, 0F3h, 0ABh, 08Bh, 0CAh, 08Bh, 054h, 024h, 02Ch, 083h, 0E1h, 003h, 042h, 03Bh
    db 0D5h, 0F3h, 0AAh, 089h, 054h, 024h, 02Ch, 07Ch, 0D2h, 08Bh, 07Ch, 024h, 020h, 08Bh, 044h, 024h
    db 034h, 085h, 0C0h, 075h, 00Ah, 05Fh, 05Eh, 05Dh, 033h, 0C0h, 05Bh, 083h, 0C4h, 018h, 0C3h, 08Bh
    db 044h, 024h, 014h, 08Bh, 04Ch, 024h, 01Ch, 08Bh, 054h, 024h, 03Ch, 08Dh, 06Fh, 001h, 08Bh, 07Ch
    db 024h, 010h, 0D1h, 0FDh, 047h, 0D1h, 0FFh, 040h, 0D1h, 0F8h, 041h, 0D1h, 0F9h, 051h, 050h, 089h
    db 04Ch, 024h, 040h, 08Bh, 04Bh, 01Ch, 089h, 044h, 024h, 034h, 08Bh, 043h, 014h, 050h, 08Bh, 046h
    db 07Ch, 003h, 0CAh, 08Bh, 056h, 040h, 051h, 08Bh, 08Eh, 0B4h, 000h, 000h, 000h, 057h, 0D1h, 0EAh
    db 003h, 0D1h, 08Bh, 04Ch, 024h, 044h, 055h, 052h, 003h, 0C1h, 050h, 056h
    call ?Rva009AA260Scale@@YAHPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 04Ch, 024h, 05Ch, 08Bh, 054h, 024h, 050h, 08Bh, 043h, 014h, 051h, 08Bh, 04Bh, 020h, 052h
    db 08Bh, 056h, 040h, 050h, 003h, 04Ch, 024h, 06Ch, 08Bh, 086h, 080h, 000h, 000h, 000h, 051h, 057h
    db 08Bh, 07Ch, 024h, 068h, 055h, 08Bh, 0AEh, 0B4h, 000h, 000h, 000h, 0D1h, 0EAh, 003h, 0D5h, 052h
    db 003h, 0C7h, 050h, 056h
    call ?Rva009AA260Scale@@YAHPAURva009AA260Context@@PBEHIIPAEIII@Z
    db 08Bh, 044h, 024h, 07Ch, 083h, 0C4h, 048h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 018h, 0C3h
?d_009aa4f0@@YAXXZ ENDP
_TEXT$d00daa4f0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00dab530  retail @ 0x009AB530 size 556
_TEXT ENDS
_TEXT$d00dab530 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAB530 size 556
public ?d_009ab530@@YAXXZ
?d_009ab530@@YAXXZ PROC
    db 083h, 0ECh, 014h, 053h, 08Bh, 05Ch, 024h, 01Ch, 0B8h, 080h, 080h, 080h, 080h, 055h, 089h, 044h
    db 024h, 010h, 089h, 044h, 024h, 014h, 056h, 066h, 089h, 044h, 024h, 01Ch, 057h, 088h, 044h, 024h
    db 022h, 08Dh, 0ABh, 050h, 001h, 000h, 000h, 033h, 0FFh, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 033h, 0F6h, 00Fh, 0B6h, 08Ch, 037h
    dd g_Va011430B0
    db 051h, 055h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 024h, 06Ah, 007h, 055h
    call ?bfmeGoUSC@@YAHPAXH@Z
    db 0D0h, 0E0h, 083h, 0C4h, 008h, 084h, 0C0h, 00Fh, 094h, 0C1h, 002h, 0C8h, 08Dh, 014h, 037h, 088h
    db 04Ch, 034h, 018h, 088h, 08Ch, 01Ah, 0A0h, 003h, 000h, 000h, 0EBh, 016h, 08Ah, 044h, 024h, 02Ch
    db 084h, 0C0h, 075h, 00Eh, 08Ah, 04Ch, 034h, 018h, 08Dh, 004h, 037h, 088h, 08Ch, 018h, 0A0h, 003h
    db 000h, 000h, 046h, 083h, 0FEh, 00Bh, 072h, 0AAh, 083h, 0C7h, 00Bh, 083h, 0FFh, 016h, 072h, 0A0h
    db 08Ah, 044h, 024h, 02Ch, 084h, 0C0h, 075h, 012h, 08Dh, 0BBh, 060h, 005h, 000h, 000h, 0B9h, 007h
    db 000h, 000h, 000h, 0BEh
    dd g_Va01143124
    db 0F3h, 0A5h, 068h, 080h, 000h, 000h, 000h, 055h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 042h, 0BEh, 001h, 000h, 000h, 000h, 00Fh, 0B6h, 096h
    dd g_Va011430C8
    db 052h, 055h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 012h, 06Ah, 004h, 055h
    call ?bfmeGoUSC@@YAHPAXH@Z
    db 083h, 0C4h, 008h, 088h, 084h, 01Eh, 03Ch, 006h, 000h, 000h, 046h, 083h, 0FEh, 040h, 072h, 0D3h
    db 08Dh, 083h, 03Ch, 006h, 000h, 000h, 050h, 053h
    call ?Rva009AAFE0BuildTable@@YAXPAURva009AAFE0Context@@PBE@Z
    db 083h, 0C4h, 008h, 033h, 0FFh, 033h, 0F6h, 00Fh, 0B6h, 08Ch, 037h
    dd g_Va01143108
    db 051h, 055h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 01Eh, 06Ah, 007h, 055h
    call ?bfmeGoUSC@@YAHPAXH@Z
    db 0D0h, 0E0h, 083h, 0C4h, 008h, 084h, 0C0h, 00Fh, 094h, 0C2h, 002h, 0D0h, 08Dh, 004h, 037h, 088h
    db 094h, 018h, 060h, 005h, 000h, 000h, 046h, 083h, 0FEh, 00Eh, 072h, 0C6h, 083h, 0C7h, 00Eh, 083h
    db 0FFh, 01Ch, 072h, 0BCh, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 0B8h
    dd g_Va01143140
    db 08Bh, 06Ch, 024h, 010h, 0C7h, 044h, 024h, 014h, 002h, 000h, 000h, 000h, 08Dh, 049h, 000h, 033h
    db 0FFh, 089h, 044h, 024h, 028h, 033h, 0F6h, 0EBh, 006h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh
    db 04Ch, 024h, 028h, 00Fh, 0B6h, 014h, 031h, 052h, 08Dh, 083h, 050h, 001h, 000h, 000h, 050h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 02Fh, 08Dh, 083h, 050h, 001h, 000h, 000h, 06Ah, 007h, 050h
    call ?bfmeGoUSC@@YAHPAXH@Z
    db 0D0h, 0E0h, 083h, 0C4h, 008h, 084h, 0C0h, 00Fh, 094h, 0C1h, 002h, 0C8h, 08Dh, 004h, 02Fh, 06Bh
    db 0C0h, 00Bh, 003h, 0C6h, 088h, 04Ch, 034h, 018h, 088h, 08Ch, 018h, 0B6h, 003h, 000h, 000h, 0EBh
    db 01Bh, 08Ah, 044h, 024h, 02Ch, 084h, 0C0h, 075h, 013h, 08Ah, 054h, 034h, 018h, 08Dh, 00Ch, 02Fh
    db 06Bh, 0C9h, 00Bh, 003h, 0CEh, 088h, 094h, 019h, 0B6h, 003h, 000h, 000h, 046h, 083h, 0FEh, 00Bh
    db 072h, 094h, 08Bh, 04Ch, 024h, 028h, 047h, 083h, 0C1h, 00Bh, 083h, 0FFh, 006h, 089h, 04Ch, 024h
    db 028h, 00Fh, 082h, 075h, 0FFh, 0FFh, 0FFh, 08Bh, 0C1h, 08Bh, 04Ch, 024h, 014h, 083h, 0C5h, 012h
    db 049h, 089h, 04Ch, 024h, 014h, 00Fh, 085h, 05Bh, 0FFh, 0FFh, 0FFh, 08Bh, 054h, 024h, 010h, 083h
    db 0C2h, 006h, 03Dh
    dd g_Va011432CC
    db 089h, 054h, 024h, 010h, 00Fh, 08Ch, 036h, 0FFh, 0FFh, 0FFh, 053h
    call ?Rva009B64A0BuildTone@@YAXPAE@Z
    db 083h, 0C4h, 004h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 014h, 0C3h
?d_009ab530@@YAXXZ ENDP
_TEXT$d00dab530 ENDS
_TEXT SEGMENT

; ghidra: FUN_00dab9d0  retail @ 0x009AB9D0 size 1509
_TEXT ENDS
_TEXT$d00dab9d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAB9D0 size 1509
public ?d_009ab9d0@@YAXXZ
?d_009ab9d0@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 08Bh, 044h, 024h, 018h, 08Bh, 04Ch, 024h, 010h, 08Bh, 0D0h, 069h, 0D2h, 0C6h
    db 000h, 000h, 000h, 08Dh, 094h, 00Ah, 0B6h, 003h, 000h, 000h, 089h, 054h, 024h, 008h, 08Bh, 091h
    db 03Ch, 001h, 000h, 000h, 08Bh, 092h, 03Ch, 001h, 000h, 000h, 053h, 055h, 089h, 054h, 024h, 008h
    db 08Bh, 091h, 044h, 009h, 000h, 000h, 085h, 0D2h, 056h, 057h, 075h, 010h, 08Ah, 091h, 09Dh, 001h
    db 000h, 000h, 084h, 0D2h, 08Dh, 0B1h, 050h, 001h, 000h, 000h, 075h, 006h, 08Dh, 0B1h, 070h, 001h
    db 000h, 000h, 08Bh, 05Ch, 024h, 02Ch, 08Bh, 0D0h, 06Bh, 0D2h, 00Bh, 08Dh, 0ACh, 00Ah, 0A0h, 003h
    db 000h, 000h, 00Fh, 0B6h, 013h, 08Dh, 004h, 040h, 003h, 0C2h, 08Bh, 054h, 024h, 030h, 00Fh, 0B6h
    db 012h, 003h, 0C2h, 08Dh, 00Ch, 081h, 00Fh, 0B6h, 094h, 008h, 042h, 005h, 000h, 000h, 08Dh, 0BCh
    db 008h, 042h, 005h, 000h, 000h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 013h, 088h, 044h, 024h, 028h, 08Bh, 044h, 024h, 030h, 0C6h
    db 000h, 000h, 0C6h, 003h, 000h, 0E9h, 034h, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 030h, 0C6h, 001h
    db 001h, 0C6h, 003h, 001h, 00Fh, 0B6h, 057h, 002h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 0F8h, 000h, 000h, 000h, 00Fh, 0B6h, 047h, 003h, 050h
    db 056h, 0C6h, 044h, 024h, 030h, 002h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 099h, 000h, 000h, 000h, 00Fh, 0B6h, 04Dh, 006h, 051h
    db 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 038h, 00Fh, 0B6h, 055h, 008h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 013h, 00Fh, 0B6h, 045h, 00Ah, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 009h, 0EBh, 024h, 00Fh, 0B6h, 04Dh, 009h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 007h, 0EBh, 011h, 00Fh, 0B6h, 055h, 007h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 005h, 0C1h, 0E0h, 004h, 08Bh, 0D8h, 00Fh, 0B7h, 0ABh
    dd g_Va01142720
    db 00Fh, 0BFh, 0BBh
    dd g_Va01142722
    db 090h, 00Fh, 0B6h, 084h, 03Bh
    dd g_Va01142724
    db 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 08Bh, 0CFh, 0D3h, 0E0h, 083h, 0C4h, 008h, 003h, 0E8h, 04Fh, 079h, 0E5h, 08Bh, 0CEh
    call ?step@Rva009AAF80State@@QAEHXZ
    db 08Bh, 0C8h, 0F7h, 0D9h, 033h, 0CDh, 0EBh, 057h, 00Fh, 0B6h, 047h, 004h, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 015h, 00Fh, 0B6h, 04Dh, 005h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 08Bh, 0F8h, 083h, 0C4h, 008h, 083h, 0C7h, 003h, 0EBh, 005h, 0BFh, 002h, 000h, 000h, 000h, 08Bh
    db 0CEh
    call ?step@Rva009AAF80State@@QAEHXZ
    db 08Bh, 0D0h, 0F7h, 0DAh, 033h, 0D7h, 003h, 0D0h, 08Bh, 044h, 024h, 024h, 066h, 089h, 010h, 0EBh
    db 01Ch, 08Bh, 0CEh, 0C6h, 044h, 024h, 028h, 001h
    call ?step@Rva009AAF80State@@QAEHXZ
    db 08Bh, 0C8h, 0F7h, 0D9h, 083h, 0F1h, 001h, 08Bh, 054h, 024h, 024h, 003h, 0C8h, 066h, 089h, 00Ah
    db 0B3h, 001h, 088h, 05Ch, 024h, 030h, 08Ah, 054h, 024h, 028h, 00Fh, 0B6h, 0CBh, 00Fh, 0B6h, 0C2h
    db 089h, 04Ch, 024h, 02Ch, 08Bh, 00Ch, 08Dh
    dd g_Va011427E0
    db 08Dh, 004h, 040h, 08Dh, 03Ch, 041h, 08Bh, 04Ch, 024h, 018h, 06Bh, 0FFh, 00Bh, 003h, 0F9h, 080h
    db 0FBh, 001h, 076h, 008h, 084h, 0D2h, 00Fh, 084h, 068h, 001h, 000h, 000h, 00Fh, 0B6h, 017h, 052h
    db 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 053h, 001h, 000h, 000h, 00Fh, 0B6h, 047h, 001h, 050h
    db 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 08Fh, 003h, 000h, 000h, 08Bh, 054h, 024h, 020h, 080h
    db 0FBh, 006h, 01Bh, 0C9h, 041h, 06Bh, 0C9h, 00Eh, 00Fh, 0B6h, 084h, 011h, 060h, 005h, 000h, 000h
    db 08Dh, 0BCh, 011h, 060h, 005h, 000h, 000h, 050h, 056h, 0C6h, 044h, 024h, 030h, 000h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 048h, 00Fh, 0B6h, 04Fh, 001h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 01Ah, 00Fh, 0B6h, 057h, 002h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 040h, 002h, 0D8h, 088h, 05Ch, 024h, 030h, 0E9h, 025h, 003h, 000h, 000h, 00Fh
    db 0B6h, 047h, 003h, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C0h, 003h, 083h, 0C4h, 008h, 002h, 0D8h, 088h, 05Ch, 024h, 030h, 0E9h, 009h, 003h, 000h
    db 000h, 00Fh, 0B6h, 04Fh, 004h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 04Ah, 00Fh, 0B6h, 057h, 005h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 01Ch, 00Fh, 0B6h, 047h, 006h, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C0h, 005h, 083h, 0C4h, 008h, 002h, 0D8h, 088h, 05Ch, 024h, 030h, 0E9h, 0C9h, 002h, 000h
    db 000h, 00Fh, 0B6h, 04Fh, 007h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C0h, 007h, 083h, 0C4h, 008h, 002h, 0D8h, 088h, 05Ch, 024h, 030h, 0E9h, 0ADh, 002h, 000h
    db 000h, 00Fh, 0B6h, 057h, 008h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 08Bh, 0E8h, 00Fh, 0B6h, 047h, 009h, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 00Fh, 0B6h, 04Fh, 00Ah, 051h, 056h, 08Dh, 06Ch, 045h, 000h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 00Fh, 0B6h, 057h, 00Bh, 052h, 056h, 08Dh, 06Ch, 085h, 000h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 08Dh, 06Ch, 0C5h, 000h, 00Fh, 0B6h, 047h, 00Ch, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 00Fh, 0B6h, 04Fh, 00Dh, 051h, 0C1h, 0E0h, 004h, 056h, 003h, 0E8h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 0C1h, 0E0h, 005h, 08Dh, 044h, 028h, 009h, 083h, 0C4h, 030h, 002h, 0D8h, 088h, 05Ch, 024h, 030h
    db 0E9h, 043h, 002h, 000h, 000h, 00Fh, 0B6h, 057h, 002h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 0AEh, 001h, 000h, 000h, 00Fh, 0B6h, 047h, 003h, 050h
    db 056h, 0C6h, 044h, 024h, 030h, 002h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 00Dh, 001h, 000h, 000h, 00Fh, 0B6h, 04Fh, 006h, 051h
    db 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 038h, 00Fh, 0B6h, 057h, 008h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 013h, 00Fh, 0B6h, 047h, 00Ah, 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 009h, 0EBh, 024h, 00Fh, 0B6h, 04Fh, 009h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 007h, 0EBh, 011h, 00Fh, 0B6h, 057h, 007h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 005h, 0C1h, 0E0h, 004h, 08Bh, 0E8h, 00Fh, 0B7h, 09Dh
    dd g_Va01142720
    db 00Fh, 0BFh, 0BDh
    dd g_Va01142722
    db 0EBh, 006h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 00Fh, 0B6h, 084h, 02Fh
    dd g_Va01142724
    db 050h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 08Bh, 0CFh, 0D3h, 0E0h, 083h, 0C4h, 008h, 003h, 0D8h, 04Fh, 079h, 0E5h, 08Bh, 06Eh, 004h, 08Bh
    db 07Eh, 00Ch, 08Dh, 04Dh, 001h, 0D1h, 0E9h, 08Bh, 0D1h, 089h, 05Ch, 024h, 014h, 08Bh, 05Eh, 008h
    db 0C1h, 0E2h, 018h, 03Bh, 0DAh, 01Bh, 0C0h, 040h, 074h, 05Ah, 02Bh, 0E9h, 02Bh, 0DAh, 003h, 0EDh
    db 04Fh, 08Dh, 00Ch, 01Bh, 075h, 015h, 08Bh, 056h, 010h, 08Bh, 05Eh, 014h, 00Fh, 0B6h, 01Ch, 013h
    db 00Bh, 0CBh, 042h, 0BFh, 008h, 000h, 000h, 000h, 089h, 056h, 010h, 08Bh, 054h, 024h, 02Ch, 089h
    db 04Eh, 008h, 08Bh, 0C8h, 089h, 07Eh, 00Ch, 08Bh, 07Ch, 024h, 014h, 0F7h, 0D9h, 033h, 0CFh, 003h
    db 0C8h, 08Bh, 044h, 024h, 020h, 089h, 06Eh, 004h, 00Fh, 0B6h, 094h, 002h, 0BCh, 005h, 000h, 000h
    db 08Bh, 044h, 024h, 010h, 08Bh, 014h, 090h, 08Bh, 044h, 024h, 024h, 066h, 089h, 00Ch, 050h, 0E9h
    db 0FDh, 000h, 000h, 000h, 08Bh, 0E9h, 0EBh, 0A6h, 00Fh, 0B6h, 04Fh, 004h, 051h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 017h, 00Fh, 0B6h, 057h, 005h, 052h, 056h
    call ?Rva009B4800DecodeBool@@YAHPAURva009B4800State@@H@Z
    db 083h, 0C4h, 008h, 083h, 0C0h, 003h, 089h, 044h, 024h, 014h, 0EBh, 008h, 0C7h, 044h, 024h, 014h
    db 002h, 000h, 000h, 000h, 08Bh, 046h, 004h, 08Bh, 05Eh, 008h, 08Bh, 06Eh, 00Ch, 08Dh, 050h, 001h
    db 0D1h, 0EAh, 08Bh, 0FAh, 0C1h, 0E7h, 018h, 03Bh, 0DFh, 01Bh, 0C9h, 041h, 074h, 037h, 02Bh, 0C2h
    db 02Bh, 0DFh, 04Dh, 08Dh, 014h, 01Bh, 08Dh, 03Ch, 000h, 075h, 015h, 08Bh, 046h, 010h, 08Bh, 05Eh
    db 014h, 00Fh, 0B6h, 01Ch, 003h, 00Bh, 0D3h, 040h, 0BDh, 008h, 000h, 000h, 000h, 089h, 046h, 010h
    db 08Bh, 0C1h, 089h, 07Eh, 004h, 08Bh, 07Ch, 024h, 014h, 0F7h, 0D8h, 089h, 06Eh, 00Ch, 089h, 056h
    db 008h, 033h, 0C7h, 0EBh, 056h, 08Bh, 0C2h, 0EBh, 0C9h, 08Bh, 06Eh, 004h, 08Bh, 05Eh, 008h, 08Bh
    db 07Eh, 00Ch, 08Dh, 045h, 001h, 0D1h, 0E8h, 08Bh, 0D0h, 0C1h, 0E2h, 018h, 03Bh, 0DAh, 01Bh, 0C9h
    db 041h, 0C6h, 044h, 024h, 028h, 001h, 074h, 06Bh, 02Bh, 0E8h, 02Bh, 0DAh, 04Fh, 08Dh, 004h, 01Bh
    db 08Dh, 05Ch, 02Dh, 000h, 075h, 015h, 08Bh, 056h, 010h, 08Bh, 06Eh, 014h, 00Fh, 0B6h, 02Ch, 02Ah
    db 00Bh, 0C5h, 042h, 0BFh, 008h, 000h, 000h, 000h, 089h, 056h, 010h, 089h, 046h, 008h, 08Bh, 0C1h
    db 0F7h, 0D8h, 089h, 07Eh, 00Ch, 089h, 05Eh, 004h, 083h, 0F0h, 001h, 08Bh, 054h, 024h, 020h, 003h
    db 0C1h, 08Bh, 04Ch, 024h, 02Ch, 00Fh, 0B6h, 08Ch, 011h, 0BCh, 005h, 000h, 000h, 08Bh, 054h, 024h
    db 010h, 08Bh, 00Ch, 08Ah, 08Bh, 054h, 024h, 024h, 066h, 089h, 004h, 04Ah, 08Ah, 044h, 024h, 030h
    db 0FEh, 0C0h, 088h, 044h, 024h, 030h, 08Ah, 0D8h, 080h, 0FBh, 040h, 00Fh, 082h, 01Bh, 0FCh, 0FFh
    db 0FFh, 0EBh, 006h, 08Bh, 0E8h, 0EBh, 095h, 0FEh, 0C3h, 08Bh, 04Ch, 024h, 020h, 05Fh, 0FEh, 0CBh
    db 00Fh, 0B6h, 0C3h, 08Ah, 084h, 008h, 0FCh, 005h, 000h, 000h, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch
    db 0C3h
?d_009ab9d0@@YAXXZ ENDP
_TEXT$d00dab9d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00dad750  retail @ 0x009AD750 size 848
_TEXT ENDS
_TEXT$d00dad750 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DAD750 size 848
public ?d_009ad750@@YAXXZ
?d_009ad750@@YAXXZ PROC
    db 083h, 0ECh, 04Ch, 08Bh, 044h, 024h, 064h, 08Bh, 04Ch, 024h, 060h, 08Dh, 04Ch, 001h, 0FFh, 03Bh
    db 0C1h, 089h, 004h, 024h, 089h, 04Ch, 024h, 020h, 00Fh, 083h, 02Eh, 003h, 000h, 000h, 08Bh, 044h
    db 024h, 054h, 08Bh, 04Ch, 024h, 058h, 053h, 08Bh, 05Ch, 024h, 054h, 055h, 056h, 08Bh, 0D0h, 057h
    db 02Bh, 0D1h, 08Dh, 070h, 008h, 08Dh, 079h, 005h, 089h, 054h, 024h, 028h, 089h, 074h, 024h, 020h
    db 089h, 07Ch, 024h, 024h, 08Bh, 053h, 024h, 08Bh, 044h, 024h, 010h, 08Bh, 04Ch, 082h, 004h, 08Bh
    db 054h, 024h, 078h, 08Bh, 004h, 08Ah, 089h, 044h, 024h, 070h, 00Fh, 0AFh, 0C0h, 08Dh, 004h, 040h
    db 0C1h, 0F8h, 005h, 089h, 074h, 024h, 074h, 089h, 044h, 024h, 02Ch, 089h, 07Ch, 024h, 018h, 0C7h
    db 044h, 024h, 01Ch, 008h, 000h, 000h, 000h, 0EBh, 007h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 00Fh, 0B6h, 06Eh, 001h, 00Fh, 0B6h, 05Eh, 0FCh, 00Fh, 0B6h, 016h, 00Fh, 0B6h, 04Eh, 0FEh, 08Bh
    db 044h, 024h, 028h, 00Fh, 0B6h, 03Ch, 038h, 00Fh, 0B6h, 046h, 0FFh, 089h, 04Ch, 024h, 040h, 089h
    db 06Ch, 024h, 04Ch, 00Fh, 0B6h, 06Eh, 002h, 00Fh, 0B6h, 076h, 003h, 089h, 074h, 024h, 054h, 08Dh
    db 034h, 008h, 00Fh, 0AFh, 0C9h, 089h, 044h, 024h, 044h, 00Fh, 0AFh, 0C0h, 003h, 0C1h, 08Bh, 0CFh
    db 00Fh, 0AFh, 0CFh, 003h, 0C1h, 08Bh, 0CBh, 00Fh, 0AFh, 0CBh, 003h, 0F7h, 003h, 0F3h, 089h, 05Ch
    db 024h, 038h, 08Bh, 05Ch, 024h, 04Ch, 003h, 0C1h, 08Bh, 04Ch, 024h, 054h, 089h, 07Ch, 024h, 03Ch
    db 08Dh, 03Ch, 029h, 00Fh, 0AFh, 0C9h, 003h, 0FBh, 08Bh, 0DDh, 00Fh, 0AFh, 0DDh, 003h, 0CBh, 089h
    db 06Ch, 024h, 050h, 08Bh, 06Ch, 024h, 04Ch, 08Bh, 0DDh, 00Fh, 0AFh, 0DDh, 003h, 0CBh, 08Bh, 0DAh
    db 00Fh, 0AFh, 0DAh, 003h, 0CBh, 08Dh, 05Eh, 001h, 0D1h, 0FEh, 003h, 0FAh, 0D1h, 0FBh, 00Fh, 0AFh
    db 0DEh, 08Dh, 077h, 001h, 0D1h, 0FEh, 0D1h, 0FFh, 00Fh, 0AFh, 0F7h, 08Bh, 07Ch, 024h, 010h, 02Bh
    db 0CEh, 02Bh, 0C3h, 08Bh, 05Ch, 024h, 060h, 08Bh, 073h, 028h, 001h, 004h, 0BEh, 08Dh, 034h, 0BEh
    db 08Bh, 073h, 028h, 08Dh, 074h, 0BEh, 004h, 001h, 00Eh, 08Bh, 074h, 024h, 02Ch, 03Bh, 0C6h, 00Fh
    db 08Dh, 07Eh, 001h, 000h, 000h, 03Bh, 0CEh, 00Fh, 08Dh, 076h, 001h, 000h, 000h, 08Bh, 07Ch, 024h
    db 044h, 08Bh, 044h, 024h, 070h, 08Bh, 0CAh, 02Bh, 0CFh, 03Bh, 0C8h, 00Fh, 08Dh, 066h, 001h, 000h
    db 000h, 08Bh, 0CFh, 02Bh, 0CAh, 03Bh, 0C8h, 00Fh, 08Dh, 05Ah, 001h, 000h, 000h, 08Bh, 074h, 024h
    db 074h, 00Fh, 0B6h, 04Eh, 0FCh, 00Fh, 0B6h, 05Eh, 0FBh, 08Bh, 0C1h, 02Bh, 0C3h, 085h, 0C0h, 07Fh
    db 004h, 08Bh, 0C3h, 02Bh, 0C1h, 03Bh, 044h, 024h, 070h, 08Bh, 0CBh, 07Ch, 004h, 00Fh, 0B6h, 04Eh
    db 0FCh, 00Fh, 0B6h, 05Eh, 004h, 00Fh, 0B6h, 046h, 003h, 02Bh, 0C3h, 085h, 0C0h, 089h, 04Ch, 024h
    db 014h, 07Fh, 008h, 08Bh, 0C3h, 00Fh, 0B6h, 05Eh, 003h, 02Bh, 0C3h, 03Bh, 044h, 024h, 070h, 07Dh
    db 006h, 00Fh, 0B6h, 046h, 004h, 0EBh, 004h, 00Fh, 0B6h, 046h, 003h, 08Bh, 05Ch, 024h, 040h, 089h
    db 044h, 024h, 074h, 08Dh, 004h, 04Fh, 003h, 0C1h, 003h, 0C3h, 003h, 044h, 024h, 03Ch, 08Bh, 05Ch
    db 024h, 038h, 08Dh, 044h, 018h, 004h, 003h, 0D8h, 0D1h, 0E3h, 02Bh, 0DFh, 08Bh, 07Ch, 024h, 018h
    db 003h, 0DAh, 0C1h, 0FBh, 004h, 088h, 05Fh, 0FFh, 08Bh, 0DAh, 02Bh, 0D9h, 003h, 0C3h, 08Bh, 05Ch
    db 024h, 03Ch, 003h, 0D8h, 0D1h, 0E3h, 02Bh, 0DAh, 003h, 0DDh, 0C1h, 0FBh, 004h, 088h, 01Fh, 08Bh
    db 0DDh, 02Bh, 0D9h, 08Bh, 04Ch, 024h, 040h, 003h, 0C3h, 003h, 0C8h, 0D1h, 0E1h, 08Bh, 0D9h, 08Bh
    db 04Ch, 024h, 050h, 02Bh, 0DDh, 003h, 0D9h, 0C1h, 0FBh, 004h, 088h, 05Fh, 001h, 02Bh, 04Ch, 024h
    db 014h, 003h, 0C1h, 08Bh, 04Ch, 024h, 044h, 003h, 0C8h, 0D1h, 0E1h, 08Bh, 0D9h, 02Bh, 05Ch, 024h
    db 050h, 02Bh, 05Ch, 024h, 038h, 003h, 05Ch, 024h, 014h, 08Bh, 04Ch, 024h, 054h, 003h, 0D9h, 0C1h
    db 0FBh, 004h, 088h, 05Fh, 002h, 02Bh, 04Ch, 024h, 038h, 08Bh, 05Ch, 024h, 054h, 003h, 0C1h, 08Dh
    db 00Ch, 010h, 0D1h, 0E1h, 02Bh, 0CBh, 02Bh, 04Ch, 024h, 03Ch, 003h, 04Ch, 024h, 074h, 003h, 04Ch
    db 024h, 038h, 08Bh, 05Ch, 024h, 074h, 0C1h, 0F9h, 004h, 088h, 04Fh, 003h, 08Bh, 04Ch, 024h, 03Ch
    db 02Bh, 0D9h, 003h, 0C3h, 08Dh, 01Ch, 028h, 08Bh, 06Ch, 024h, 040h, 0D1h, 0E3h, 02Bh, 0DDh, 003h
    db 0D9h, 0C1h, 0FBh, 004h, 088h, 05Fh, 004h, 08Bh, 04Ch, 024h, 074h, 08Bh, 0D9h, 02Bh, 0DDh, 003h
    db 0C3h, 08Bh, 05Ch, 024h, 050h, 003h, 0D8h, 003h, 0C1h, 08Bh, 04Ch, 024h, 054h, 0D1h, 0E3h, 02Bh
    db 05Ch, 024h, 044h, 003h, 0C1h, 0D1h, 0E0h, 02Bh, 0C2h, 08Bh, 054h, 024h, 044h, 003h, 0DDh, 0C1h
    db 0FBh, 004h, 02Bh, 0C2h, 0C1h, 0F8h, 004h, 088h, 05Fh, 005h, 08Bh, 05Ch, 024h, 060h, 088h, 047h
    db 006h, 0EBh, 03Bh, 08Bh, 07Ch, 024h, 044h, 08Bh, 04Ch, 024h, 040h, 08Bh, 0C2h, 02Bh, 0C7h, 08Dh
    db 004h, 040h, 02Bh, 0C5h, 08Dh, 044h, 008h, 004h, 08Bh, 04Bh, 038h, 0C1h, 0F8h, 003h, 08Bh, 034h
    db 081h, 08Ah, 084h, 03Eh
    dd g_Va01356FE0
    db 08Bh, 07Ch, 024h, 018h, 02Bh, 0D6h, 08Bh, 074h, 024h, 074h, 088h, 047h, 002h, 08Ah, 08Ah
    dd g_Va01356FE0
    db 088h, 04Fh, 003h, 08Bh, 044h, 024h, 06Ch, 003h, 0F0h, 003h, 0F8h, 08Bh, 044h, 024h, 01Ch, 048h
    db 089h, 074h, 024h, 074h, 089h, 07Ch, 024h, 018h, 089h, 044h, 024h, 01Ch, 00Fh, 085h, 063h, 0FDh
    db 0FFh, 0FFh, 08Bh, 044h, 024h, 010h, 08Bh, 074h, 024h, 020h, 08Bh, 07Ch, 024h, 024h, 08Bh, 04Ch
    db 024h, 030h, 040h, 083h, 0C6h, 008h, 083h, 0C7h, 008h, 03Bh, 0C1h, 089h, 044h, 024h, 010h, 089h
    db 074h, 024h, 020h, 089h, 07Ch, 024h, 024h, 00Fh, 082h, 0FCh, 0FCh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh
    db 05Bh, 083h, 0C4h, 04Ch, 0C3h
?d_009ad750@@YAXXZ ENDP
_TEXT$d00dad750 ENDS
_TEXT SEGMENT

; ghidra: FUN_00db2190  retail @ 0x009B2190 size 916
public ?d_009b2190@@YAXXZ
?d_009b2190@@YAXXZ PROC
    db 83h, 0ECh, 2Ch, 8Bh, 44h, 24h, 3Ch, 0B9h, 01h, 00h, 00h, 00h, 2Bh, 0C8h, 89h, 4Ch
    db 24h, 1Ch, 0B9h, 02h, 00h, 00h, 00h, 2Bh, 0C8h, 89h, 4Ch, 24h, 18h, 0B9h, 05h, 00h
    db 00h, 00h, 2Bh, 0C8h, 89h, 4Ch, 24h, 20h, 0B9h, 03h, 00h, 00h, 00h, 2Bh, 0C8h, 89h
    db 0Ch, 24h, 0B9h, 06h, 00h, 00h, 00h, 2Bh, 0C8h, 89h, 4Ch, 24h, 24h, 53h, 0B9h, 04h
    db 00h, 00h, 00h, 2Bh, 0C8h, 55h, 8Bh, 6Ch, 24h, 40h, 56h, 89h, 4Ch, 24h, 10h, 8Bh
    db 4Ch, 24h, 40h, 57h, 8Dh, 14h, 00h, 8Bh, 0F1h, 2Bh, 0F2h, 8Bh, 0F9h, 83h, 0C6h, 02h
    db 2Bh, 0F8h, 8Dh, 54h, 0Ah, 0FEh, 83h, 0C7h, 04h, 8Dh, 0Ch, 0C1h, 89h, 6Ch, 24h, 18h
    db 89h, 74h, 24h, 20h, 89h, 7Ch, 24h, 1Ch, 89h, 54h, 24h, 48h, 0C7h, 44h, 24h, 24h
    db 08h, 00h, 00h, 00h, 89h, 4Ch, 24h, 38h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 48h, 45h, 0C7h, 44h, 24h, 44h, 02h, 00h, 00h, 00h, 8Dh, 49h, 00h
    db 0Fh, 0B6h, 5Ch, 30h, 0FDh, 0Fh, 0B6h, 54h, 07h, 0FCh, 8Dh, 54h, 53h, 04h, 8Bh, 5Ch
    db 24h, 2Ch, 0Fh, 0B6h, 1Ch, 19h, 03h, 0D3h, 0Fh, 0B6h, 5Ch, 30h, 0FFh, 03h, 0D3h, 8Bh
    db 5Ch, 24h, 10h, 0Fh, 0B6h, 1Ch, 0Bh, 03h, 0D3h, 0Fh, 0B6h, 5Eh, 0FCh, 8Dh, 14h, 53h
    db 0Fh, 0B6h, 59h, 04h, 03h, 0D3h, 0Fh, 0B6h, 19h, 03h, 0D3h, 0Fh, 0B6h, 1Eh, 03h, 0D3h
    db 0D1h, 0E2h, 8Bh, 5Ch, 24h, 28h, 0C1h, 0FAh, 05h, 88h, 55h, 0FFh, 0Fh, 0B6h, 1Ch, 19h
    db 0Fh, 0B6h, 54h, 38h, 0FDh, 8Dh, 54h, 53h, 04h, 0Fh, 0B6h, 5Ch, 06h, 0FEh, 03h, 0D3h
    db 0Fh, 0B6h, 1Ch, 06h, 03h, 0D3h, 8Bh, 5Ch, 24h, 14h, 0Fh, 0B6h, 1Ch, 0Bh, 03h, 0D3h
    db 0Fh, 0B6h, 5Eh, 0FDh, 8Dh, 14h, 53h, 0Fh, 0B6h, 5Eh, 01h, 03h, 0D3h, 0Fh, 0B6h, 59h
    db 05h, 03h, 0D3h, 0Fh, 0B6h, 59h, 01h, 03h, 0D3h, 8Bh, 5Ch, 24h, 30h, 0D1h, 0E2h, 0C1h
    db 0FAh, 05h, 88h, 55h, 00h, 0Fh, 0B6h, 1Ch, 19h, 0Fh, 0B6h, 54h, 07h, 0FEh, 8Dh, 54h
    db 53h, 04h, 0Fh, 0B6h, 5Fh, 0FFh, 03h, 0D3h, 0Fh, 0B6h, 5Ch, 30h, 0FFh, 03h, 0D3h, 8Bh
    db 5Ch, 24h, 10h, 0Fh, 0B6h, 1Ch, 0Bh, 03h, 0D3h, 0Fh, 0B6h, 5Eh, 0FEh, 8Dh, 14h, 53h
    db 0Fh, 0B6h, 5Eh, 02h, 03h, 0D3h, 0Fh, 0B6h, 59h, 06h, 03h, 0D3h, 0Fh, 0B6h, 59h, 02h
    db 03h, 0D3h, 8Bh, 5Ch, 24h, 34h, 0D1h, 0E2h, 0C1h, 0FAh, 05h, 88h, 55h, 01h, 0Fh, 0B6h
    db 1Ch, 0Bh, 0Fh, 0B6h, 54h, 38h, 0FFh, 8Dh, 54h, 53h, 04h, 0Fh, 0B6h, 1Ch, 06h, 03h
    db 0D3h, 8Bh, 5Ch, 24h, 14h, 0Fh, 0B6h, 1Ch, 0Bh, 03h, 0D3h, 0Fh, 0B6h, 1Fh, 03h, 0D3h
    db 0Fh, 0B6h, 5Eh, 03h, 8Dh, 14h, 53h, 0Fh, 0B6h, 5Eh, 0FFh, 03h, 0D3h, 0Fh, 0B6h, 59h
    db 07h, 03h, 0D3h, 0Fh, 0B6h, 59h, 03h, 03h, 0D3h, 0D1h, 0E2h, 0C1h, 0FAh, 05h, 88h, 55h
    db 02h, 8Bh, 54h, 24h, 44h, 83h, 0C1h, 04h, 83h, 0C5h, 04h, 83h, 0C7h, 04h, 83h, 0C6h
    db 04h, 4Ah, 89h, 54h, 24h, 44h, 0Fh, 85h, 0C4h, 0FEh, 0FFh, 0FFh, 8Bh, 7Ch, 24h, 48h
    db 8Bh, 6Ch, 24h, 18h, 8Bh, 74h, 24h, 20h, 8Bh, 4Ch, 24h, 24h, 03h, 0F8h, 89h, 7Ch
    db 24h, 48h, 8Bh, 7Ch, 24h, 1Ch, 03h, 0E8h, 03h, 0F8h, 03h, 0F0h, 49h, 89h, 6Ch, 24h
    db 18h, 89h, 7Ch, 24h, 1Ch, 89h, 74h, 24h, 20h, 89h, 4Ch, 24h, 24h, 0Fh, 85h, 7Dh
    db 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 38h, 8Bh, 5Ch, 24h, 28h, 8Bh, 0D1h, 2Bh, 0D0h, 8Dh
    db 7Dh, 01h, 83h, 0C2h, 02h, 8Dh, 74h, 01h, 01h, 89h, 7Ch, 24h, 44h, 89h, 54h, 24h
    db 20h, 89h, 74h, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 08h, 00h, 00h, 00h, 8Dh, 49h, 00h
    db 0C7h, 44h, 24h, 48h, 02h, 00h, 00h, 00h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 4Ch, 02h, 0FEh, 0Fh, 0B6h, 6Ch, 10h, 0FDh, 8Dh, 0Ch, 49h, 0D1h, 0E1h, 2Bh
    db 0CDh, 0Fh, 0B6h, 6Ah, 0FEh, 2Bh, 0CDh, 0Fh, 0B6h, 6Eh, 0FFh, 2Bh, 0CDh, 0Fh, 0B6h, 6Ch
    db 10h, 0FFh, 2Bh, 0CDh, 41h, 0D1h, 0F9h, 85h, 0C9h, 7Dh, 04h, 33h, 0C9h, 0EBh, 0Dh, 81h
    db 0F9h, 0FFh, 00h, 00h, 00h, 7Eh, 05h, 0B9h, 0FFh, 00h, 00h, 00h, 88h, 4Fh, 0FFh, 0Fh
    db 0B6h, 4Ch, 10h, 0FFh, 0Fh, 0B6h, 6Ah, 0FFh, 8Dh, 0Ch, 49h, 0D1h, 0E1h, 2Bh, 0CDh, 0Fh
    db 0B6h, 2Eh, 2Bh, 0CDh, 0Fh, 0B6h, 2Ch, 02h, 2Bh, 0CDh, 0Fh, 0B6h, 6Ch, 02h, 0FEh, 2Bh
    db 0CDh, 41h, 0D1h, 0F9h, 85h, 0C9h, 7Dh, 04h, 33h, 0C9h, 0EBh, 0Dh, 81h, 0F9h, 0FFh, 00h
    db 00h, 00h, 7Eh, 05h, 0B9h, 0FFh, 00h, 00h, 00h, 88h, 0Fh, 0Fh, 0B6h, 0Ch, 02h, 0Fh
    db 0B6h, 6Eh, 01h, 8Dh, 0Ch, 49h, 0D1h, 0E1h, 2Bh, 0CDh, 0Fh, 0B6h, 2Ah, 2Bh, 0CDh, 0Fh
    db 0B6h, 6Ch, 10h, 0FFh, 2Bh, 0CDh, 0Fh, 0B6h, 2Ch, 1Eh, 2Bh, 0CDh, 41h, 0D1h, 0F9h, 85h
    db 0C9h, 7Dh, 04h, 33h, 0C9h, 0EBh, 0Dh, 81h, 0F9h, 0FFh, 00h, 00h, 00h, 7Eh, 05h, 0B9h
    db 0FFh, 00h, 00h, 00h, 88h, 4Fh, 01h, 8Bh, 4Ch, 24h, 10h, 0Fh, 0B6h, 2Ch, 31h, 0Fh
    db 0B6h, 0Ch, 1Eh, 8Dh, 0Ch, 49h, 0D1h, 0E1h, 2Bh, 0CDh, 0Fh, 0B6h, 6Ah, 01h, 2Bh, 0CDh
    db 0Fh, 0B6h, 6Eh, 02h, 2Bh, 0CDh, 0Fh, 0B6h, 2Ch, 02h, 2Bh, 0CDh, 41h, 0D1h, 0F9h, 85h
    db 0C9h, 7Dh, 04h, 33h, 0C9h, 0EBh, 0Dh, 81h, 0F9h, 0FFh, 00h, 00h, 00h, 7Eh, 05h, 0B9h
    db 0FFh, 00h, 00h, 00h, 88h, 4Fh, 02h, 8Bh, 4Ch, 24h, 48h, 83h, 0C6h, 04h, 83h, 0C7h
    db 04h, 83h, 0C2h, 04h, 49h, 89h, 4Ch, 24h, 48h, 0Fh, 85h, 0F1h, 0FEh, 0FFh, 0FFh, 8Bh
    db 7Ch, 24h, 44h, 8Bh, 74h, 24h, 24h, 8Bh, 54h, 24h, 20h, 8Bh, 4Ch, 24h, 1Ch, 03h
    db 0F8h, 03h, 0F0h, 03h, 0D0h, 49h, 89h, 7Ch, 24h, 44h, 89h, 74h, 24h, 24h, 89h, 54h
    db 24h, 20h, 89h, 4Ch, 24h, 1Ch, 0Fh, 85h, 0B4h, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh
    db 83h, 0C4h, 2Ch, 0C3h
?d_009b2190@@YAXXZ ENDP

; ghidra: FUN_00db2530  retail @ 0x009B2530 size 1309
_TEXT ENDS
_TEXT$d00db2530 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB2530 size 1309
public ?d_009b2530@@YAXXZ
?d_009b2530@@YAXXZ PROC
    db 083h, 0ECh, 038h, 053h, 055h, 056h, 08Bh, 074h, 024h, 048h, 08Bh, 006h, 083h, 0F8h, 005h, 08Bh
    db 06Eh, 00Ch, 057h, 07Ch, 022h, 0C7h, 044h, 024h, 038h, 080h, 001h, 000h, 000h, 0C7h, 044h, 024h
    db 034h, 000h, 009h, 000h, 000h, 0C7h, 044h, 024h, 044h, 040h, 00Bh, 000h, 000h, 0C7h, 044h, 024h
    db 024h, 080h, 016h, 000h, 000h, 0EBh, 020h, 0C7h, 044h, 024h, 038h, 000h, 008h, 000h, 000h, 0C7h
    db 044h, 024h, 034h, 000h, 078h, 000h, 000h, 0C7h, 044h, 024h, 044h, 000h, 068h, 001h, 000h, 0C7h
    db 044h, 024h, 024h, 000h, 0E0h, 001h, 000h, 083h, 0F8h, 005h, 07Ch, 00Ah, 0C7h, 044h, 024h, 04Ch
    dd g_Va012D8058
    db 0EBh, 015h, 083h, 0F8h, 002h, 0C7h, 044h, 024h, 04Ch
    dd g_Va012D7F58
    db 07Dh, 008h, 0C7h, 044h, 024h, 04Ch
    dd ?g_rva01356940@@3PAHA
    db 08Bh, 04Eh, 078h, 08Bh, 07Ch, 024h, 050h, 08Bh, 086h, 094h, 000h, 000h, 000h, 08Bh, 096h, 090h
    db 000h, 000h, 000h, 003h, 0F9h, 089h, 07Ch, 024h, 014h, 08Bh, 07Ch, 024h, 054h, 003h, 0CFh, 08Bh
    db 0BEh, 098h, 000h, 000h, 000h, 089h, 04Ch, 024h, 01Ch, 033h, 0C9h, 03Bh, 0C1h, 089h, 054h, 024h
    db 020h, 089h, 044h, 024h, 030h, 089h, 04Ch, 024h, 010h, 089h, 04Ch, 024h, 02Ch, 00Fh, 086h, 0C3h
    db 001h, 000h, 000h, 08Bh, 0FFh, 085h, 0D2h, 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 00Fh
    db 086h, 081h, 001h, 000h, 000h, 08Bh, 05Ch, 024h, 014h, 08Bh, 0C1h, 02Bh, 0C2h, 0C1h, 0E0h, 002h
    db 089h, 044h, 024h, 040h, 08Dh, 004h, 011h, 0C1h, 0E0h, 002h, 089h, 044h, 024h, 03Ch, 08Bh, 044h
    db 024h, 01Ch, 08Bh, 0D3h, 02Bh, 0C2h, 089h, 044h, 024h, 018h, 0EBh, 009h, 08Bh, 044h, 024h, 018h
    db 0EBh, 003h, 08Dh, 049h, 000h, 08Bh, 056h, 028h, 08Bh, 00Ch, 08Ah, 083h, 07Eh, 008h, 005h, 00Fh
    db 08Eh, 0B9h, 000h, 000h, 000h, 03Bh, 04Ch, 024h, 044h, 00Fh, 08Eh, 0AFh, 000h, 000h, 000h, 08Bh
    db 04Ch, 024h, 04Ch, 051h, 055h, 057h, 003h, 0C3h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 044h, 024h, 040h, 083h, 0C4h, 018h, 085h, 0C0h, 08Bh, 044h, 024h, 024h, 076h, 00Dh, 08Bh
    db 056h, 028h, 08Bh, 04Ch, 024h, 010h, 039h, 044h, 08Ah, 0FCh, 07Fh, 04Fh, 08Bh, 054h, 024h, 028h
    db 08Bh, 04Ch, 024h, 020h, 042h, 03Bh, 0D1h, 073h, 00Dh, 08Bh, 04Eh, 028h, 08Bh, 054h, 024h, 010h
    db 039h, 044h, 091h, 004h, 07Fh, 035h, 08Bh, 04Ch, 024h, 02Ch, 08Bh, 054h, 024h, 030h, 041h, 03Bh
    db 0CAh, 073h, 00Ch, 08Bh, 056h, 028h, 08Bh, 04Ch, 024h, 03Ch, 039h, 004h, 011h, 07Fh, 01Ch, 08Bh
    db 04Ch, 024h, 02Ch, 085h, 0C9h, 00Fh, 086h, 088h, 000h, 000h, 000h, 08Bh, 056h, 028h, 08Bh, 04Ch
    db 024h, 040h, 039h, 004h, 011h, 00Fh, 08Eh, 078h, 000h, 000h, 000h, 08Bh, 054h, 024h, 04Ch, 08Bh
    db 044h, 024h, 018h, 052h, 055h, 057h, 003h, 0C3h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 04Ch, 024h, 064h, 08Bh, 054h, 024h, 030h, 051h, 055h, 057h, 08Dh, 004h, 01Ah, 050h, 053h
    db 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 030h, 0EBh, 046h, 08Bh, 054h, 024h, 034h, 003h, 0C3h, 03Bh, 0CAh, 07Eh, 015h, 08Bh
    db 04Ch, 024h, 04Ch, 051h, 055h, 057h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 018h, 0EBh, 027h, 03Bh, 04Ch, 024h, 038h, 07Eh, 015h, 08Bh, 054h, 024h, 04Ch, 052h
    db 055h, 057h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EA0
    db 083h, 0C4h, 018h, 0EBh, 00Ch, 057h, 050h, 053h, 0FFh, 015h
    dd ?g_bfmeSlotB44@@3PAXA
    db 083h, 0C4h, 00Ch, 08Bh, 054h, 024h, 010h, 08Bh, 04Ch, 024h, 03Ch, 042h, 089h, 054h, 024h, 010h
    db 08Bh, 054h, 024h, 040h, 0B8h, 004h, 000h, 000h, 000h, 003h, 0C8h, 003h, 0D0h, 08Bh, 044h, 024h
    db 028h, 089h, 04Ch, 024h, 03Ch, 08Bh, 04Ch, 024h, 020h, 040h, 083h, 0C3h, 008h, 03Bh, 0C1h, 08Bh
    db 04Ch, 024h, 010h, 089h, 054h, 024h, 040h, 089h, 044h, 024h, 028h, 00Fh, 082h, 0AAh, 0FEh, 0FFh
    db 0FFh, 08Bh, 044h, 024h, 030h, 08Bh, 05Ch, 024h, 014h, 08Dh, 014h, 0FDh, 000h, 000h, 000h, 000h
    db 003h, 0DAh, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 01Ch, 003h, 0DAh, 08Bh, 054h, 024h, 02Ch
    db 042h, 089h, 054h, 024h, 02Ch, 03Bh, 0D0h, 08Bh, 054h, 024h, 020h, 089h, 05Ch, 024h, 01Ch, 00Fh
    db 082h, 03Fh, 0FEh, 0FFh, 0FFh, 08Bh, 05Ch, 024h, 050h, 0D1h, 0EAh, 089h, 054h, 024h, 020h, 08Bh
    db 056h, 07Ch, 003h, 0DAh, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 054h, 0D1h, 0E8h, 003h, 0D3h
    db 0D1h, 0EFh, 085h, 0C0h, 089h, 044h, 024h, 030h, 089h, 054h, 024h, 01Ch, 00Fh, 086h, 01Fh, 001h
    db 000h, 000h, 089h, 044h, 024h, 040h, 08Bh, 054h, 024h, 020h, 085h, 0D2h, 00Fh, 086h, 0E5h, 000h
    db 000h, 000h, 08Bh, 05Ch, 024h, 014h, 08Bh, 044h, 024h, 01Ch, 02Bh, 0C3h, 089h, 044h, 024h, 018h
    db 089h, 054h, 024h, 044h, 0EBh, 004h, 08Bh, 044h, 024h, 018h, 083h, 03Eh, 005h, 08Bh, 056h, 028h
    db 08Bh, 014h, 08Ah, 07Dh, 007h, 08Bh, 06Eh, 024h, 08Bh, 06Ch, 08Dh, 000h, 083h, 07Eh, 008h, 005h
    db 07Eh, 04Ah, 03Bh, 054h, 024h, 024h, 07Eh, 044h, 08Bh, 04Ch, 024h, 04Ch, 051h, 055h, 057h, 003h
    db 0C3h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 054h, 024h, 064h, 08Bh, 044h, 024h, 030h, 052h, 055h, 057h, 003h, 0C3h, 050h, 053h, 056h
    db 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 04Ch, 024h, 07Ch, 08Bh, 054h, 024h, 048h, 051h, 055h, 057h, 08Dh, 004h, 013h, 050h, 053h
    db 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 048h, 0EBh, 04Ah, 03Bh, 054h, 024h, 034h, 07Eh, 018h, 08Bh, 04Ch, 024h, 04Ch, 051h
    db 055h, 057h, 08Dh, 014h, 003h, 052h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 018h, 0EBh, 02Ch, 03Bh, 054h, 024h, 038h, 07Eh, 018h, 08Bh, 04Ch, 024h, 04Ch, 051h
    db 055h, 057h, 08Dh, 014h, 003h, 052h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EA0
    db 083h, 0C4h, 018h, 0EBh, 00Eh, 057h, 003h, 0C3h, 050h, 053h, 0FFh, 015h
    dd ?g_bfmeSlotB44@@3PAXA
    db 083h, 0C4h, 00Ch, 08Bh, 054h, 024h, 010h, 08Bh, 044h, 024h, 044h, 042h, 083h, 0C3h, 008h, 048h
    db 089h, 054h, 024h, 010h, 089h, 044h, 024h, 044h, 08Bh, 0CAh, 00Fh, 085h, 033h, 0FFh, 0FFh, 0FFh
    db 08Bh, 044h, 024h, 030h, 08Bh, 05Ch, 024h, 014h, 08Dh, 014h, 0FDh, 000h, 000h, 000h, 000h, 003h
    db 0DAh, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 01Ch, 003h, 0DAh, 08Bh, 054h, 024h, 040h, 04Ah
    db 089h, 05Ch, 024h, 01Ch, 089h, 054h, 024h, 040h, 00Fh, 085h, 0E5h, 0FEh, 0FFh, 0FFh, 08Bh, 096h
    db 080h, 000h, 000h, 000h, 08Bh, 05Ch, 024h, 050h, 003h, 0DAh, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch
    db 024h, 054h, 003h, 0D3h, 085h, 0C0h, 089h, 054h, 024h, 01Ch, 00Fh, 086h, 026h, 001h, 000h, 000h
    db 08Bh, 05Ch, 024h, 014h, 089h, 044h, 024h, 054h, 0EBh, 007h, 08Dh, 0A4h, 024h, 000h, 000h, 000h
    db 000h, 08Bh, 044h, 024h, 020h, 085h, 0C0h, 00Fh, 086h, 0E3h, 000h, 000h, 000h, 08Bh, 0C2h, 08Bh
    db 054h, 024h, 020h, 02Bh, 0C3h, 089h, 044h, 024h, 018h, 089h, 054h, 024h, 050h, 0EBh, 004h, 08Bh
    db 044h, 024h, 018h, 083h, 03Eh, 005h, 08Bh, 056h, 028h, 08Bh, 014h, 08Ah, 07Dh, 007h, 08Bh, 06Eh
    db 024h, 08Bh, 06Ch, 08Dh, 000h, 083h, 07Eh, 008h, 005h, 07Eh, 04Ah, 03Bh, 054h, 024h, 024h, 07Eh
    db 044h, 08Bh, 04Ch, 024h, 04Ch, 051h, 055h, 057h, 003h, 0C3h, 050h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 054h, 024h, 064h, 08Bh, 044h, 024h, 030h, 052h, 055h, 057h, 003h, 0C3h, 050h, 053h, 056h
    db 0FFh, 015h
    dd g_Va01356EC0
    db 08Bh, 04Ch, 024h, 07Ch, 08Bh, 054h, 024h, 048h, 051h, 055h, 057h, 08Dh, 004h, 013h, 050h, 053h
    db 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 048h, 0EBh, 04Ah, 03Bh, 054h, 024h, 034h, 07Eh, 018h, 08Bh, 04Ch, 024h, 04Ch, 051h
    db 055h, 057h, 08Dh, 014h, 003h, 052h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EC0
    db 083h, 0C4h, 018h, 0EBh, 02Ch, 03Bh, 054h, 024h, 038h, 07Eh, 018h, 08Bh, 04Ch, 024h, 04Ch, 051h
    db 055h, 057h, 08Dh, 014h, 003h, 052h, 053h, 056h, 0FFh, 015h
    dd g_Va01356EA0
    db 083h, 0C4h, 018h, 0EBh, 00Eh, 057h, 003h, 0C3h, 050h, 053h, 0FFh, 015h
    dd ?g_bfmeSlotB44@@3PAXA
    db 083h, 0C4h, 00Ch, 08Bh, 054h, 024h, 010h, 08Bh, 044h, 024h, 050h, 042h, 083h, 0C3h, 008h, 048h
    db 089h, 054h, 024h, 010h, 089h, 044h, 024h, 050h, 08Bh, 0CAh, 00Fh, 085h, 033h, 0FFh, 0FFh, 0FFh
    db 08Bh, 05Ch, 024h, 014h, 08Bh, 054h, 024h, 01Ch, 08Dh, 004h, 0FDh, 000h, 000h, 000h, 000h, 003h
    db 0D8h, 003h, 0D0h, 08Bh, 044h, 024h, 054h, 048h, 089h, 05Ch, 024h, 014h, 089h, 054h, 024h, 01Ch
    db 089h, 044h, 024h, 054h, 00Fh, 085h, 0EBh, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h
    db 038h, 0C3h
?d_009b2530@@YAXXZ ENDP
_TEXT$d00db2530 ENDS
_TEXT SEGMENT

; ghidra: FUN_00db4390  retail @ 0x009B4390 size 610
_TEXT ENDS
_TEXT$d00db4390 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB4390 size 610
public ?d_009b4390@@YAXXZ
?d_009b4390@@YAXXZ PROC
    db 081h, 0ECh, 02Ch, 001h, 000h, 000h, 08Bh, 094h, 024h, 030h, 001h, 000h, 000h, 08Bh, 082h, 0B8h
    db 001h, 000h, 000h, 08Bh, 092h, 05Ch, 002h, 000h, 000h, 053h, 08Bh, 09Ch, 024h, 038h, 001h, 000h
    db 000h, 055h, 056h, 057h, 089h, 044h, 024h, 034h, 033h, 0C0h, 0C6h, 044h, 024h, 03Ch, 000h, 0B9h
    db 03Fh, 000h, 000h, 000h, 08Dh, 07Ch, 024h, 03Dh, 0F3h, 0ABh, 003h, 0D3h, 066h, 0ABh, 08Dh, 08Ch
    db 024h, 04Ch, 001h, 000h, 000h, 051h, 089h, 054h, 024h, 02Ch, 08Bh, 094h, 024h, 04Ch, 001h, 000h
    db 000h, 052h, 0AAh, 08Dh, 044h, 024h, 044h, 068h, 000h, 001h, 000h, 000h, 033h, 0EDh, 050h, 089h
    db 06Ch, 024h, 034h, 0FFh, 015h
    dd __imp_?i_009f6ec0@@YAXXZ
    db 08Dh, 044h, 024h, 04Ch, 083h, 0C4h, 010h, 089h, 06Ch, 024h, 010h, 089h, 06Ch, 024h, 014h, 08Dh
    db 050h, 001h, 0EBh, 003h, 08Dh, 049h, 000h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 02Bh, 0C2h
    db 08Dh, 00Ch, 0C5h, 000h, 000h, 000h, 000h, 055h, 089h, 04Ch, 024h, 01Ch, 0C7h, 044h, 024h, 020h
    db 008h, 000h, 000h, 000h, 0FFh, 015h
    dd __imp__CreateCompatibleDC@4
    db 08Bh, 0F0h, 03Bh, 0F5h, 00Fh, 084h, 07Ah, 001h, 000h, 000h, 08Bh, 054h, 024h, 01Ch, 08Bh, 044h
    db 024h, 018h, 055h, 06Ah, 001h, 06Ah, 001h, 052h, 050h, 0FFh, 015h
    dd g_Va013590B4
    db 08Bh, 0D8h, 03Bh, 0DDh, 089h, 05Ch, 024h, 02Ch, 00Fh, 084h, 057h, 001h, 000h, 000h, 08Bh, 03Dh
    dd __imp__SelectObject@8
    db 053h, 056h, 0FFh, 0D7h, 03Bh, 0C5h, 089h, 044h, 024h, 038h, 00Fh, 084h, 034h, 001h, 000h, 000h
    db 068h
    dd ??_7Rva007F01B0@@6B@
    db 06Ah, 022h, 055h, 055h, 055h, 055h, 055h, 055h, 055h, 055h, 055h, 055h, 055h, 06Ah, 008h, 0FFh
    db 015h
    dd g_Va013590C0
    db 08Bh, 0E8h, 085h, 0EDh, 089h, 06Ch, 024h, 020h, 00Fh, 084h, 0FBh, 000h, 000h, 000h, 053h, 056h
    db 0FFh, 0D7h, 085h, 0C0h, 089h, 044h, 024h, 030h, 00Fh, 084h, 0EBh, 000h, 000h, 000h, 055h, 056h
    db 0FFh, 0D7h, 06Ah, 001h, 056h, 0FFh, 015h
    dd __imp__SetTextColor@8
    db 06Ah, 000h, 056h, 0FFh, 015h
    dd __imp__SetBkColor@8
    db 06Ah, 001h, 056h, 0FFh, 015h
    dd g_Va01359104
    db 08Bh, 044h, 024h, 014h, 08Bh, 04Ch, 024h, 010h, 08Bh, 054h, 024h, 01Ch, 06Ah, 042h, 050h, 051h
    db 056h, 052h, 08Bh, 054h, 024h, 02Ch, 052h, 050h, 051h, 056h, 0FFh, 015h
    dd g_Va013590B0
    db 085h, 0C0h, 00Fh, 084h, 0A4h, 000h, 000h, 000h, 08Dh, 044h, 024h, 03Ch, 08Dh, 050h, 001h, 08Dh
    db 064h, 024h, 000h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 06Ah, 000h, 02Bh, 0C2h, 050h, 08Dh
    db 044h, 024h, 044h, 050h, 08Dh, 04Ch, 024h, 01Ch, 051h, 06Ah, 004h, 06Ah, 000h, 06Ah, 000h, 056h
    db 0FFh, 015h
    dd g_Va013590CC
    db 085h, 0C0h, 074h, 072h, 08Bh, 06Ch, 024h, 014h, 08Bh, 044h, 024h, 01Ch, 03Bh, 0E8h, 07Dh, 04Eh
    db 08Bh, 01Dh
    dd g_Va013590E0
    db 08Bh, 04Ch, 024h, 018h, 08Bh, 07Ch, 024h, 010h, 03Bh, 0F9h, 07Dh, 025h, 02Bh, 0C5h, 048h, 050h
    db 057h, 056h, 0FFh, 0D3h, 085h, 0C0h, 074h, 008h, 08Bh, 054h, 024h, 028h, 0C6h, 004h, 017h, 0FFh
    db 08Bh, 04Ch, 024h, 018h, 08Bh, 044h, 024h, 01Ch, 047h, 03Bh, 0F9h, 07Ch, 0DFh, 08Bh, 07Ch, 024h
    db 010h, 08Bh, 054h, 024h, 034h, 001h, 054h, 024h, 028h, 045h, 03Bh, 0E8h, 07Ch, 0CAh, 08Bh, 05Ch
    db 024h, 02Ch, 08Bh, 03Dh
    dd __imp__SelectObject@8
    db 08Dh, 044h, 024h, 03Ch, 08Dh, 050h, 001h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 08Bh, 06Ch
    db 024h, 020h, 02Bh, 0C2h, 089h, 044h, 024h, 024h, 08Bh, 044h, 024h, 038h, 050h, 056h, 0FFh, 0D7h
    db 053h, 0FFh, 015h
    dd __imp__DeleteObject@4
    db 0EBh, 017h, 08Bh, 06Ch, 024h, 020h, 053h, 0FFh, 015h
    dd __imp__DeleteObject@4
    db 0EBh, 00Ah, 08Bh, 03Dh
    dd __imp__SelectObject@8
    db 08Bh, 06Ch, 024h, 020h, 085h, 0EDh, 074h, 013h, 08Bh, 044h, 024h, 030h, 085h, 0C0h, 074h, 004h
    db 050h, 056h, 0FFh, 0D7h, 055h, 0FFh, 015h
    dd __imp__DeleteObject@4
    db 085h, 0F6h, 074h, 007h, 056h, 0FFh, 015h
    dd __imp__DeleteDC@4
    db 08Bh, 044h, 024h, 024h, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 02Ch, 001h, 000h, 000h, 0C3h
?d_009b4390@@YAXXZ ENDP
_TEXT$d00db4390 ENDS
_TEXT SEGMENT

; ghidra: FUN_00db4a10  retail @ 0x009B4A10 size 1661
public ?d_009b4a10@@YAXXZ
?d_009b4a10@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 8Bh, 4Ch, 24h, 18h, 53h, 8Bh, 5Ch, 24h, 14h, 8Bh, 84h, 8Bh, 24h
    db 45h, 00h, 00h, 85h, 0C0h, 55h, 56h, 57h, 8Dh, 0B3h, 90h, 01h, 00h, 00h, 0C7h, 44h
    db 24h, 10h, 01h, 00h, 00h, 00h, 7Eh, 0Fh, 48h, 89h, 84h, 8Bh, 24h, 45h, 00h, 00h
    db 33h, 0C0h, 0E9h, 0F6h, 01h, 00h, 00h, 8Bh, 56h, 04h, 8Dh, 0ACh, 0C9h, 0A2h, 00h, 00h
    db 00h, 0C1h, 0E1h, 07h, 8Dh, 0BCh, 19h, 0FCh, 30h, 00h, 00h, 8Bh, 0Eh, 0B8h, 01h, 00h
    db 00h, 00h, 0D3h, 0E0h, 0C1h, 0E5h, 04h, 03h, 0EBh, 48h, 23h, 0C2h, 83h, 0F9h, 06h, 72h
    db 09h, 83h, 0C1h, 0FAh, 0D3h, 0E8h, 8Bh, 0D0h, 0EBh, 10h, 8Bh, 56h, 08h, 0Fh, 0B6h, 12h
    db 0C1h, 0E0h, 08h, 0Bh, 0D0h, 83h, 0C1h, 02h, 0D3h, 0EAh, 0Fh, 0B7h, 04h, 57h, 8Bh, 0Eh
    db 0C1h, 0E8h, 0Ch, 2Bh, 0C8h, 89h, 0Eh, 79h, 35h, 8Bh, 46h, 08h, 0Fh, 0B6h, 08h, 0Fh
    db 0B6h, 58h, 01h, 0C1h, 0E1h, 08h, 03h, 0CBh, 0Fh, 0B6h, 58h, 02h, 0C1h, 0E1h, 08h, 03h
    db 0CBh, 0Fh, 0B6h, 58h, 03h, 83h, 0C0h, 04h, 0C1h, 0E1h, 08h, 89h, 46h, 08h, 8Bh, 06h
    db 03h, 0CBh, 8Bh, 5Ch, 24h, 20h, 83h, 0C0h, 20h, 89h, 4Eh, 04h, 89h, 06h, 33h, 0C0h
    db 66h, 8Bh, 04h, 57h, 0A8h, 01h, 74h, 0Ah, 0D1h, 0E8h, 83h, 0E0h, 1Fh, 0E9h, 89h, 00h
    db 00h, 00h, 8Bh, 54h, 24h, 28h, 8Bh, 7Eh, 04h, 81h, 0E2h, 01h, 0FFh, 0FFh, 0FFh, 83h
    db 0E0h, 3Eh, 0Bh, 0C2h, 8Bh, 0D0h, 8Bh, 0Eh, 85h, 0C9h, 74h, 0Ch, 49h, 8Bh, 0C7h, 0D3h
    db 0E8h, 89h, 0Eh, 83h, 0E0h, 01h, 0EBh, 37h, 8Bh, 46h, 08h, 0Fh, 0B6h, 08h, 0Fh, 0B6h
    db 78h, 01h, 0C1h, 0E1h, 08h, 03h, 0CFh, 0Fh, 0B6h, 78h, 02h, 0C1h, 0E1h, 08h, 03h, 0CFh
    db 0Fh, 0B6h, 78h, 03h, 0C1h, 0E1h, 08h, 03h, 0CFh, 83h, 0C0h, 04h, 89h, 46h, 08h, 8Bh
    db 0F9h, 8Bh, 0C1h, 89h, 4Eh, 04h, 0C7h, 06h, 1Fh, 00h, 00h, 00h, 0C1h, 0E8h, 1Fh, 85h
    db 0C0h, 8Bh, 0C2h, 74h, 0Eh, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 14h, 40h, 8Bh, 54h, 95h
    db 04h, 0EBh, 0Ch, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 04h, 40h, 8Bh, 54h, 85h, 00h, 0F6h
    db 0C2h, 01h, 74h, 92h, 0D1h, 0EAh, 83h, 0E2h, 7Fh, 8Bh, 0C2h, 83h, 0F8h, 0Bh, 8Bh, 3Ch
    db 85h, 0E8h, 29h, 14h, 01h, 0Fh, 84h, 0FFh, 04h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 80h
    db 00h, 00h, 00h, 0B9h, 02h, 00h, 00h, 00h, 8Bh, 0C6h, 0E8h, 51h, 0FBh, 0FFh, 0FFh, 40h
    db 83h, 0F8h, 03h, 75h, 22h, 0B9h, 02h, 00h, 00h, 00h, 8Bh, 0C6h, 0E8h, 3Fh, 0FBh, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 28h, 83h, 0C0h, 03h, 48h, 89h, 84h, 8Bh, 24h, 45h, 00h, 00h
    db 33h, 0C0h, 0E9h, 86h, 00h, 00h, 00h, 83h, 0F8h, 04h, 75h, 37h, 8Bh, 0C6h, 0E8h, 0EDh
    db 0FBh, 0FFh, 0FFh, 85h, 0C0h, 8Bh, 0C6h, 74h, 1Dh, 0B9h, 06h, 00h, 00h, 00h, 0E8h, 0Dh
    db 0FBh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 28h, 83h, 0C0h, 0Bh, 48h, 89h, 84h, 8Bh, 24h, 45h
    db 00h, 00h, 33h, 0C0h, 0EBh, 57h, 0B9h, 02h, 00h, 00h, 00h, 0E8h, 0F0h, 0FAh, 0FFh, 0FFh
    db 83h, 0C0h, 07h, 8Bh, 4Ch, 24h, 28h, 48h, 89h, 84h, 8Bh, 24h, 45h, 00h, 00h, 33h
    db 0C0h, 0EBh, 3Ah, 83h, 0F8h, 04h, 7Eh, 16h, 83h, 0F8h, 09h, 8Dh, 48h, 0FCh, 7Eh, 05h
    db 0B9h, 0Bh, 00h, 00h, 00h, 8Bh, 0C6h, 0E8h, 0C4h, 0FAh, 0FFh, 0FFh, 03h, 0F8h, 8Bh, 0C6h
    db 0E8h, 8Bh, 0FBh, 0FFh, 0FFh, 8Bh, 0D0h, 0F7h, 0DAh, 33h, 0D7h, 03h, 0D0h, 8Bh, 44h, 24h
    db 24h, 66h, 89h, 10h, 33h, 0C0h, 83h, 0FFh, 01h, 0Fh, 9Fh, 0C0h, 40h, 8Bh, 54h, 24h
    db 28h, 8Bh, 8Ch, 93h, 2Ch, 45h, 00h, 00h, 85h, 0C9h, 7Eh, 24h, 5Fh, 49h, 89h, 8Ch
    db 93h, 2Ch, 45h, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch, 8Ah, 84h, 19h, 0FBh, 05h, 00h, 00h
    db 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 54h, 24h, 10h, 8Bh, 0Ch, 95h, 18h, 2Ah, 14h, 01h, 8Bh, 54h, 24h, 28h, 8Bh
    db 7Eh, 04h, 8Dh, 04h, 42h, 8Dh, 04h, 40h, 8Dh, 04h, 41h, 8Bh, 0Eh, 8Dh, 94h, 0C0h
    db 0A7h, 01h, 00h, 00h, 0C1h, 0E0h, 07h, 8Dh, 0ACh, 18h, 0FCh, 31h, 00h, 00h, 0B8h, 01h
    db 00h, 00h, 00h, 0D3h, 0E0h, 0C1h, 0E2h, 04h, 03h, 0D3h, 48h, 23h, 0C7h, 83h, 0F9h, 06h
    db 72h, 09h, 83h, 0C1h, 0FAh, 0D3h, 0E8h, 8Bh, 0F8h, 0EBh, 10h, 8Bh, 7Eh, 08h, 0Fh, 0B6h
    db 3Fh, 0C1h, 0E0h, 08h, 0Bh, 0F8h, 83h, 0C1h, 02h, 0D3h, 0EFh, 0Fh, 0B7h, 4Ch, 7Dh, 00h
    db 8Bh, 06h, 0C1h, 0E9h, 0Ch, 2Bh, 0C1h, 89h, 06h, 79h, 35h, 8Bh, 46h, 08h, 0Fh, 0B6h
    db 08h, 0Fh, 0B6h, 58h, 01h, 0C1h, 0E1h, 08h, 03h, 0CBh, 0Fh, 0B6h, 58h, 02h, 0C1h, 0E1h
    db 08h, 03h, 0CBh, 0Fh, 0B6h, 58h, 03h, 83h, 0C0h, 04h, 0C1h, 0E1h, 08h, 89h, 46h, 08h
    db 8Bh, 06h, 03h, 0CBh, 8Bh, 5Ch, 24h, 20h, 83h, 0C0h, 20h, 89h, 4Eh, 04h, 89h, 06h
    db 33h, 0C0h, 66h, 8Bh, 44h, 7Dh, 00h, 0A8h, 01h, 74h, 0Ah, 0D1h, 0E8h, 83h, 0E0h, 1Fh
    db 0E9h, 98h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 7Eh, 04h, 83h, 0E0h, 3Eh, 81h
    db 0E1h, 01h, 0FFh, 0FFh, 0FFh, 0Bh, 0C1h, 89h, 44h, 24h, 14h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 0Eh, 8Dh, 48h, 0FFh, 8Bh, 0C7h, 0D3h, 0E8h, 89h, 0Eh, 83h
    db 0E0h, 01h, 0EBh, 37h, 8Bh, 46h, 08h, 0Fh, 0B6h, 08h, 0Fh, 0B6h, 78h, 01h, 0C1h, 0E1h
    db 08h, 03h, 0CFh, 0Fh, 0B6h, 78h, 02h, 0C1h, 0E1h, 08h, 03h, 0CFh, 0Fh, 0B6h, 78h, 03h
    db 0C1h, 0E1h, 08h, 03h, 0CFh, 83h, 0C0h, 04h, 89h, 46h, 08h, 8Bh, 0F9h, 8Bh, 0C1h, 89h
    db 4Eh, 04h, 0C7h, 06h, 1Fh, 00h, 00h, 00h, 0C1h, 0E8h, 1Fh, 85h, 0C0h, 8Bh, 44h, 24h
    db 14h, 74h, 0Eh, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 04h, 40h, 8Bh, 4Ch, 82h, 04h, 0EBh
    db 0Bh, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 04h, 40h, 8Bh, 0Ch, 82h, 8Ah, 0C1h, 0A8h, 01h
    db 89h, 4Ch, 24h, 14h, 74h, 8Ah, 8Bh, 0C1h, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 85h, 0C0h, 8Bh
    db 3Ch, 85h, 0E8h, 29h, 14h, 01h, 0Fh, 85h, 7Bh, 01h, 00h, 00h, 8Bh, 6Ch, 24h, 10h
    db 8Bh, 0Eh, 83h, 0FDh, 06h, 0Fh, 9Dh, 0C0h, 8Bh, 0D0h, 69h, 0D2h, 0A8h, 00h, 00h, 00h
    db 0C1h, 0E0h, 07h, 8Dh, 0BCh, 18h, 0FCh, 43h, 00h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0D3h
    db 0E0h, 8Dh, 0ACh, 1Ah, 0ACh, 2Fh, 00h, 00h, 8Bh, 56h, 04h, 48h, 23h, 0C2h, 83h, 0F9h
    db 06h, 72h, 09h, 83h, 0C1h, 0FAh, 0D3h, 0E8h, 8Bh, 0D0h, 0EBh, 10h, 8Bh, 56h, 08h, 0Fh
    db 0B6h, 12h, 0C1h, 0E0h, 08h, 0Bh, 0D0h, 83h, 0C1h, 02h, 0D3h, 0EAh, 0Fh, 0B7h, 04h, 57h
    db 8Bh, 0Eh, 0C1h, 0E8h, 0Ch, 2Bh, 0C8h, 89h, 0Eh, 79h, 35h, 8Bh, 46h, 08h, 0Fh, 0B6h
    db 08h, 0Fh, 0B6h, 58h, 01h, 0C1h, 0E1h, 08h, 03h, 0CBh, 0Fh, 0B6h, 58h, 02h, 0C1h, 0E1h
    db 08h, 03h, 0CBh, 0Fh, 0B6h, 58h, 03h, 83h, 0C0h, 04h, 0C1h, 0E1h, 08h, 89h, 46h, 08h
    db 8Bh, 06h, 03h, 0CBh, 8Bh, 5Ch, 24h, 20h, 83h, 0C0h, 20h, 89h, 4Eh, 04h, 89h, 06h
    db 33h, 0C0h, 66h, 8Bh, 04h, 57h, 0A8h, 01h, 74h, 0Ah, 0D1h, 0E8h, 83h, 0E0h, 1Fh, 0E9h
    db 9Ah, 00h, 00h, 00h, 8Bh, 54h, 24h, 18h, 81h, 0E2h, 01h, 0FFh, 0FFh, 0FFh, 83h, 0E0h
    db 3Eh, 0Bh, 0C2h, 8Bh, 56h, 04h, 89h, 44h, 24h, 18h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 0Eh, 8Dh, 48h, 0FFh, 8Bh, 0C2h, 0D3h, 0E8h, 89h, 0Eh, 83h
    db 0E0h, 01h, 0EBh, 37h, 8Bh, 46h, 08h, 0Fh, 0B6h, 08h, 0Fh, 0B6h, 50h, 01h, 0C1h, 0E1h
    db 08h, 03h, 0CAh, 0Fh, 0B6h, 50h, 02h, 0C1h, 0E1h, 08h, 03h, 0CAh, 0Fh, 0B6h, 50h, 03h
    db 0C1h, 0E1h, 08h, 03h, 0CAh, 83h, 0C0h, 04h, 89h, 46h, 08h, 8Bh, 0D1h, 8Bh, 0C1h, 89h
    db 4Eh, 04h, 0C7h, 06h, 1Fh, 00h, 00h, 00h, 0C1h, 0E8h, 1Fh, 85h, 0C0h, 8Bh, 44h, 24h
    db 18h, 74h, 0Eh, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 04h, 40h, 8Bh, 4Ch, 85h, 04h, 0EBh
    db 0Ch, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 8Dh, 04h, 40h, 8Bh, 4Ch, 85h, 00h, 8Ah, 0C1h, 0A8h
    db 01h, 89h, 4Ch, 24h, 18h, 74h, 89h, 8Bh, 0C1h, 0D1h, 0E8h, 83h, 0E0h, 7Fh, 83h, 0F8h
    db 08h, 73h, 11h, 8Bh, 4Ch, 24h, 10h, 03h, 0C8h, 89h, 4Ch, 24h, 10h, 33h, 0C0h, 0E9h
    db 0C0h, 00h, 00h, 00h, 0B9h, 06h, 00h, 00h, 00h, 8Bh, 0C6h, 0E8h, 0B0h, 0F7h, 0FFh, 0FFh
    db 8Bh, 54h, 24h, 10h, 8Dh, 44h, 02h, 08h, 89h, 44h, 24h, 10h, 8Bh, 4Ch, 24h, 10h
    db 33h, 0C0h, 0E9h, 9Dh, 00h, 00h, 00h, 83h, 0F8h, 0Bh, 0Fh, 84h, 0B1h, 00h, 00h, 00h
    db 83h, 0F8h, 04h, 7Fh, 4Ch, 8Bh, 06h, 85h, 0C0h, 74h, 0Fh, 8Dh, 48h, 0FFh, 8Bh, 46h
    db 04h, 0D3h, 0E8h, 89h, 0Eh, 83h, 0E0h, 01h, 0EBh, 54h, 8Bh, 46h, 08h, 0Fh, 0B6h, 08h
    db 0Fh, 0B6h, 50h, 01h, 0C1h, 0E1h, 08h, 03h, 0CAh, 0Fh, 0B6h, 50h, 02h, 0C1h, 0E1h, 08h
    db 03h, 0CAh, 0Fh, 0B6h, 50h, 03h, 0C1h, 0E1h, 08h, 83h, 0C0h, 04h, 03h, 0CAh, 89h, 46h
    db 08h, 8Bh, 0C1h, 89h, 4Eh, 04h, 0C7h, 06h, 1Fh, 00h, 00h, 00h, 0C1h, 0E8h, 1Fh, 0EBh
    db 1Dh, 83h, 0F8h, 09h, 8Dh, 48h, 0FCh, 7Eh, 05h, 0B9h, 0Bh, 00h, 00h, 00h, 8Bh, 0C6h
    db 0E8h, 2Bh, 0F7h, 0FFh, 0FFh, 03h, 0F8h, 8Bh, 0C6h, 0E8h, 0F2h, 0F7h, 0FFh, 0FFh, 8Bh, 4Ch
    db 24h, 10h, 8Bh, 6Ch, 24h, 24h, 8Bh, 0D0h, 0F7h, 0DAh, 33h, 0D7h, 03h, 0D0h, 0Fh, 0B6h
    db 84h, 19h, 7Ch, 05h, 00h, 00h, 66h, 89h, 54h, 45h, 00h, 33h, 0C0h, 83h, 0FFh, 01h
    db 0Fh, 9Fh, 0C0h, 40h, 41h, 83h, 0F9h, 40h, 89h, 4Ch, 24h, 10h, 0Fh, 8Ch, 7Eh, 0FCh
    db 0FFh, 0FFh, 8Ah, 84h, 19h, 0FBh, 05h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch
    db 0C3h, 8Bh, 44h, 24h, 10h, 83h, 0F8h, 01h, 75h, 74h, 0B9h, 02h, 00h, 00h, 00h, 8Bh
    db 0C6h, 0E8h, 0CAh, 0F6h, 0FFh, 0FFh, 40h, 83h, 0F8h, 03h, 75h, 11h, 0B9h, 02h, 00h, 00h
    db 00h, 8Bh, 0C6h, 0E8h, 0B8h, 0F6h, 0FFh, 0FFh, 83h, 0C0h, 03h, 0EBh, 2Eh, 83h, 0F8h, 04h
    db 75h, 29h, 8Bh, 0C6h, 0E8h, 77h, 0F7h, 0FFh, 0FFh, 85h, 0C0h, 8Bh, 0C6h, 74h, 0Fh, 0B9h
    db 06h, 00h, 00h, 00h, 0E8h, 97h, 0F6h, 0FFh, 0FFh, 83h, 0C0h, 0Bh, 0EBh, 0Dh, 0B9h, 02h
    db 00h, 00h, 00h, 0E8h, 88h, 0F6h, 0FFh, 0FFh, 83h, 0C0h, 07h, 8Bh, 4Ch, 24h, 28h, 8Bh
    db 54h, 24h, 10h, 5Fh, 48h, 5Eh, 89h, 84h, 8Bh, 2Ch, 45h, 00h, 00h, 8Ah, 84h, 1Ah
    db 0FBh, 05h, 00h, 00h, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 44h, 24h, 10h, 8Ah, 84h
    db 18h, 0FBh, 05h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_009b4a10@@YAXXZ ENDP

; ghidra: FUN_00db5420  retail @ 0x009B5420 size 272
_TEXT ENDS
_TEXT$d00db5420 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DB5420 size 272
public ?d_009b5420@@YAXXZ
?d_009b5420@@YAXXZ PROC
    db 051h, 08Bh, 04Ch, 024h, 008h, 08Bh, 081h, 030h, 002h, 000h, 000h, 00Fh, 0AFh, 044h, 024h, 00Ch
    db 08Bh, 054h, 024h, 010h, 053h, 055h, 00Fh, 0B6h, 06Ch, 024h, 01Ch, 056h, 003h, 0C2h, 033h, 0F6h
    db 057h, 089h, 074h, 024h, 018h, 089h, 074h, 024h, 020h, 0C7h, 044h, 024h, 01Ch, 001h, 000h, 000h
    db 000h, 08Dh, 0B9h, 0A8h, 006h, 000h, 000h, 0EBh, 007h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 08Bh, 017h, 08Bh, 099h, 0F0h, 006h, 000h, 000h, 003h, 0D0h, 00Fh, 0BEh, 01Ch, 013h, 039h, 02Ch
    db 09Dh
    dd ?Rva01142BA0Table@@3QBGB
    db 075h, 00Dh, 08Bh, 099h, 0F4h, 006h, 000h, 000h, 08Bh, 014h, 093h, 085h, 0D2h, 075h, 00Bh, 046h
    db 083h, 0C7h, 004h, 083h, 0FEh, 00Ch, 07Ch, 0D3h, 0EBh, 00Ch, 089h, 054h, 024h, 018h, 0C7h, 044h
    db 024h, 01Ch, 002h, 000h, 000h, 000h, 089h, 074h, 024h, 010h, 046h, 083h, 0FEh, 00Ch, 07Dh, 03Eh
    db 08Dh, 09Ch, 0B1h, 0A8h, 006h, 000h, 000h, 08Dh, 064h, 024h, 000h, 08Bh, 013h, 08Bh, 0B9h, 0F0h
    db 006h, 000h, 000h, 003h, 0D0h, 00Fh, 0BEh, 03Ch, 017h, 039h, 02Ch, 0BDh
    dd ?Rva01142BA0Table@@3QBGB
    db 075h, 013h, 08Bh, 0B9h, 0F4h, 006h, 000h, 000h, 08Bh, 014h, 097h, 03Bh, 054h, 024h, 018h, 074h
    db 004h, 085h, 0D2h, 075h, 035h, 046h, 083h, 0C3h, 004h, 083h, 0FEh, 00Ch, 07Ch, 0CDh, 08Bh, 054h
    db 024h, 020h, 080h, 07Ch, 024h, 024h, 001h, 075h, 02Bh, 08Bh, 044h, 024h, 028h, 08Bh, 074h, 024h
    db 01Ch, 089h, 030h, 08Bh, 044h, 024h, 010h, 05Fh, 05Eh, 089h, 041h, 044h, 08Bh, 044h, 024h, 010h
    db 05Dh, 089h, 041h, 03Ch, 089h, 051h, 040h, 05Bh, 059h, 0C3h, 0C7h, 044h, 024h, 01Ch, 000h, 000h
    db 000h, 000h, 0EBh, 0CEh, 08Bh, 044h, 024h, 010h, 05Fh, 05Eh, 089h, 041h, 050h, 08Bh, 044h, 024h
    db 010h, 05Dh, 089h, 041h, 048h, 089h, 051h, 04Ch, 05Bh, 059h, 0C3h
?d_009b5420@@YAXXZ ENDP
_TEXT$d00db5420 ENDS
_TEXT SEGMENT

; ghidra: FUN_00dcc710  retail @ 0x009CC710 size 832
public ?d_009cc710@@YAXXZ
?d_009cc710@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 53h, 08h, 06h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 3Ch, 8Bh, 0Dh, 60h, 0D0h, 34h, 01h, 8Bh, 01h
    db 53h, 55h, 56h, 8Bh, 74h, 24h, 58h, 57h, 6Ah, 41h, 56h, 0FFh, 50h, 08h, 8Bh, 0E8h
    db 33h, 0DBh, 89h, 6Ch, 24h, 24h, 89h, 5Ch, 24h, 5Ch, 3Bh, 0F3h, 89h, 5Ch, 24h, 54h
    db 74h, 10h, 8Bh, 0C6h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h
    db 0EBh, 02h, 33h, 0C0h, 50h, 56h, 8Dh, 4Ch, 24h, 64h, 0E8h, 0B1h, 0B5h, 0EBh, 0FFh, 8Dh
    db 4Ch, 24h, 5Ch, 0E8h, 28h, 0B6h, 0EBh, 0FFh, 6Ah, 2Ch, 0E8h, 0B1h, 57h, 0EBh, 0FFh, 83h
    db 0C4h, 04h, 89h, 44h, 24h, 28h, 3Bh, 0C3h, 0C6h, 44h, 24h, 54h, 01h, 74h, 0Fh, 8Bh
    db 0C8h, 0E8h, 4Ah, 4Dh, 00h, 00h, 8Bh, 0F8h, 89h, 7Ch, 24h, 10h, 0EBh, 06h, 89h, 5Ch
    db 24h, 10h, 8Bh, 0FBh, 56h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 58h, 00h, 0E8h, 0Dh
    db 0C4h, 0EBh, 0FFh, 8Bh, 17h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CFh, 0C6h, 44h, 24h, 58h
    db 02h, 0FFh, 52h, 24h, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 54h, 00h, 0E8h, 6Eh, 0B1h
    db 0EBh, 0FFh, 3Bh, 0EBh, 75h, 28h, 8Dh, 4Ch, 24h, 5Ch, 0C7h, 44h, 24h, 54h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 59h, 0B1h, 0EBh, 0FFh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 8Bh, 4Ch, 24h
    db 3Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 48h, 0C2h, 04h, 00h, 8Bh, 55h
    db 00h, 6Ah, 10h, 8Dh, 44h, 24h, 40h, 50h, 8Bh, 0CDh, 0FFh, 52h, 0Ch, 83h, 0F8h, 10h
    db 0Fh, 85h, 0Ah, 02h, 00h, 00h, 8Bh, 15h, 30h, 90h, 2Dh, 01h, 8Bh, 35h, 0BCh, 94h
    db 35h, 01h, 6Ah, 04h, 8Dh, 4Ch, 24h, 40h, 51h, 52h, 0FFh, 0D6h, 83h, 0C4h, 0Ch, 85h
    db 0C0h, 74h, 1Bh, 8Bh, 0Dh, 34h, 90h, 2Dh, 01h, 6Ah, 04h, 8Dh, 44h, 24h, 40h, 50h
    db 51h, 0FFh, 0D6h, 83h, 0C4h, 0Ch, 85h, 0C0h, 0Fh, 85h, 0D2h, 01h, 00h, 00h, 8Dh, 4Ch
    db 24h, 2Ch, 0E8h, 0F9h, 0FDh, 0FFh, 0FFh, 8Bh, 44h, 24h, 48h, 8Bh, 0F0h, 8Bh, 0D0h, 81h
    db 0E6h, 00h, 0FFh, 00h, 00h, 0C1h, 0E2h, 10h, 03h, 0F2h, 0C1h, 0E8h, 18h, 0C1h, 0E6h, 08h
    db 03h, 0F0h, 33h, 0C0h, 8Ah, 64h, 24h, 4Ah, 33h, 0D2h, 8Ah, 74h, 24h, 46h, 0C6h, 44h
    db 24h, 54h, 03h, 03h, 0F0h, 8Bh, 44h, 24h, 44h, 8Bh, 0F8h, 8Bh, 0C8h, 0C1h, 0E7h, 10h
    db 81h, 0E1h, 00h, 0FFh, 00h, 00h, 03h, 0F9h, 0C1h, 0E7h, 08h, 0C1h, 0E8h, 18h, 03h, 0F8h
    db 56h, 03h, 0FAh, 0E8h, 0C8h, 56h, 0EBh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0D8h, 8Bh, 45h, 00h
    db 8Dh, 4Eh, 0F0h, 51h, 53h, 8Bh, 0CDh, 89h, 5Ch, 24h, 30h, 0FFh, 50h, 0Ch, 83h, 0C6h
    db 0F0h, 3Bh, 0C6h, 0Fh, 85h, 3Ch, 01h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 34h, 01h, 00h
    db 00h, 89h, 7Ch, 24h, 1Ch, 8Dh, 54h, 24h, 5Ch, 52h, 8Dh, 4Ch, 24h, 34h, 0E8h, 0ADh
    db 0B3h, 0EBh, 0FFh, 8Bh, 03h, 8Bh, 0C8h, 0C1h, 0E1h, 10h, 8Bh, 0D0h, 81h, 0E2h, 00h, 0FFh
    db 00h, 00h, 03h, 0CAh, 33h, 0D2h, 89h, 44h, 24h, 20h, 8Ah, 74h, 24h, 22h, 0C1h, 0E1h
    db 08h, 0C1h, 0E8h, 18h, 8Dh, 73h, 08h, 03h, 0CAh, 03h, 0C8h, 89h, 4Ch, 24h, 34h, 8Bh
    db 43h, 04h, 8Bh, 0C8h, 8Bh, 0D0h, 81h, 0E2h, 00h, 0FFh, 00h, 00h, 0C1h, 0E1h, 10h, 03h
    db 0CAh, 33h, 0D2h, 89h, 44h, 24h, 20h, 8Ah, 74h, 24h, 22h, 0C1h, 0E1h, 08h, 0C1h, 0E8h
    db 18h, 03h, 0CAh, 03h, 0C8h, 8Bh, 0C6h, 89h, 4Ch, 24h, 38h, 8Dh, 50h, 01h, 8Bh, 0FFh
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 8Bh, 0E8h, 78h, 11h, 8Dh, 49h, 00h
    db 8Ah, 04h, 2Eh, 3Ch, 5Ch, 74h, 07h, 3Ch, 2Fh, 74h, 03h, 4Dh, 79h, 0F2h, 8Dh, 4Ch
    db 2Eh, 01h, 85h, 0C9h, 74h, 15h, 8Bh, 0C1h, 8Dh, 78h, 01h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Ah, 10h, 40h, 84h, 0D2h, 75h, 0F9h, 2Bh, 0C7h, 0EBh, 02h, 33h, 0C0h, 50h, 51h, 8Dh
    db 4Ch, 24h, 34h, 0E8h, 98h, 0B3h, 0EBh, 0FFh, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0Fh, 0B4h, 0EBh
    db 0FFh, 56h, 8Dh, 4Ch, 24h, 18h, 0E8h, 25h, 0C2h, 0EBh, 0FFh, 45h, 55h, 6Ah, 00h, 8Dh
    db 44h, 24h, 1Ch, 50h, 8Dh, 4Ch, 24h, 24h, 0C6h, 44h, 24h, 60h, 04h, 0E8h, 0DEh, 0C5h
    db 0EBh, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 54h, 06h, 0E8h, 80h, 0AFh, 0EBh, 0FFh
    db 8Dh, 4Ch, 24h, 2Ch, 51h, 8Bh, 4Ch, 24h, 14h, 8Dh, 54h, 24h, 1Ch, 52h, 0E8h, 3Dh
    db 47h, 00h, 00h, 8Bh, 0C6h, 8Dh, 48h, 01h, 8Ah, 10h, 40h, 84h, 0D2h, 75h, 0F9h, 2Bh
    db 0C1h, 8Dh, 4Ch, 24h, 18h, 8Dh, 5Ch, 03h, 09h, 0C6h, 44h, 24h, 54h, 03h, 0E8h, 4Dh
    db 0AFh, 0EBh, 0FFh, 0FFh, 4Ch, 24h, 1Ch, 0Fh, 85h, 0D8h, 0FEh, 0FFh, 0FFh, 8Bh, 6Ch, 24h
    db 24h, 8Bh, 5Ch, 24h, 28h, 53h, 0E8h, 0E5h, 54h, 0EBh, 0FFh, 83h, 0C4h, 04h, 8Dh, 4Ch
    db 24h, 2Ch, 0C6h, 44h, 24h, 54h, 00h, 0E8h, 0E4h, 0FBh, 0FFh, 0FFh, 8Bh, 7Ch, 24h, 10h
    db 55h, 8Bh, 0CFh, 0E8h, 38h, 1Bh, 00h, 00h, 8Dh, 4Ch, 24h, 5Ch, 0C7h, 44h, 24h, 54h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 07h, 0AFh, 0EBh, 0FFh, 8Bh, 4Ch, 24h, 4Ch, 8Bh, 0C7h, 5Fh
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 48h, 0C2h, 04h, 00h
?d_009cc710@@YAXXZ ENDP

; ghidra: FUN_00dcdb90  retail @ 0x009CDB90 size 459
public ?d_009cdb90@@YAXXZ
?d_009cdb90@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 09h, 06h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 33h, 0EDh
    db 6Ah, 14h, 0C7h, 44h, 24h, 3Ch, 01h, 00h, 00h, 00h, 89h, 6Ch, 24h, 28h, 0E8h, 7Dh
    db 09h, 0E6h, 0FFh, 89h, 44h, 24h, 28h, 89h, 6Ch, 24h, 2Ch, 0C6h, 00h, 00h, 8Bh, 44h
    db 24h, 28h, 89h, 68h, 04h, 8Bh, 44h, 24h, 28h, 89h, 40h, 08h, 8Bh, 44h, 24h, 28h
    db 83h, 0C4h, 04h, 89h, 40h, 0Ch, 68h, 1Ch, 30h, 07h, 01h, 8Dh, 4Ch, 24h, 18h, 0C6h
    db 44h, 24h, 3Ch, 02h, 0E8h, 0C7h, 0AFh, 0EBh, 0FFh, 8Bh, 0Dh, 60h, 0D0h, 34h, 01h, 8Bh
    db 11h, 6Ah, 01h, 8Dh, 44h, 24h, 28h, 50h, 8Dh, 44h, 24h, 4Ch, 50h, 8Dh, 44h, 24h
    db 20h, 50h, 8Dh, 44h, 24h, 50h, 50h, 0C6h, 44h, 24h, 4Ch, 03h, 0FFh, 52h, 14h, 8Dh
    db 4Ch, 24h, 14h, 0C6h, 44h, 24h, 38h, 02h, 0E8h, 13h, 9Dh, 0EBh, 0FFh, 89h, 6Ch, 24h
    db 18h, 89h, 6Ch, 24h, 1Ch, 89h, 6Ch, 24h, 20h, 8Bh, 44h, 24h, 28h, 51h, 8Bh, 0CCh
    db 89h, 64h, 24h, 18h, 89h, 29h, 50h, 8Dh, 4Ch, 24h, 20h, 0C6h, 44h, 24h, 40h, 04h
    db 0E8h, 3Bh, 0FCh, 0FFh, 0FFh, 8Bh, 44h, 24h, 24h, 8Bh, 48h, 08h, 55h, 8Dh, 54h, 24h
    db 44h, 52h, 8Bh, 54h, 24h, 20h, 52h, 50h, 51h, 0E8h, 52h, 0E8h, 0FFh, 0FFh, 8Bh, 4Ch
    db 24h, 30h, 8Bh, 54h, 24h, 2Ch, 0C6h, 44h, 24h, 28h, 00h, 8Bh, 44h, 24h, 28h, 50h
    db 51h, 52h, 0E8h, 0B9h, 0FEh, 0FFh, 0FFh, 8Bh, 74h, 24h, 38h, 8Bh, 44h, 24h, 3Ch, 83h
    db 0C4h, 20h, 3Bh, 0F0h, 0C6h, 44h, 24h, 13h, 00h, 74h, 6Ch, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 06h, 3Bh, 0C5h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h
    db 8Bh, 17h, 50h, 8Bh, 0CFh, 0FFh, 52h, 08h, 8Bh, 0D8h, 3Bh, 0DDh, 74h, 3Eh, 8Bh, 4Ch
    db 24h, 48h, 8Bh, 07h, 51h, 56h, 53h, 8Bh, 0CFh, 0FFh, 50h, 28h, 8Dh, 6Fh, 04h, 56h
    db 8Bh, 0CDh, 0E8h, 99h, 0BEh, 0FFh, 0FFh, 3Bh, 45h, 00h, 74h, 0Fh, 8Bh, 40h, 14h, 85h
    db 0C0h, 74h, 08h, 8Bh, 10h, 6Ah, 01h, 8Bh, 0C8h, 0FFh, 12h, 56h, 8Bh, 0CDh, 0E8h, 2Fh
    db 0AEh, 66h, 0FFh, 89h, 18h, 0C6h, 44h, 24h, 13h, 01h, 33h, 0EDh, 8Bh, 44h, 24h, 1Ch
    db 83h, 0C6h, 04h, 3Bh, 0F0h, 75h, 99h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h, 38h, 02h
    db 0E8h, 9Dh, 8Dh, 65h, 0FFh, 8Dh, 4Ch, 24h, 24h, 0C6h, 44h, 24h, 38h, 01h, 0E8h, 0B8h
    db 47h, 64h, 0FFh, 8Dh, 4Ch, 24h, 40h, 0C6h, 44h, 24h, 38h, 00h, 0E8h, 0Fh, 9Ch, 0EBh
    db 0FFh, 8Dh, 4Ch, 24h, 44h, 0C7h, 44h, 24h, 38h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0FEh, 9Bh
    db 0EBh, 0FFh, 8Bh, 4Ch, 24h, 30h, 8Ah, 44h, 24h, 13h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 2Ch, 0C2h, 0Ch, 00h
?d_009cdb90@@YAXXZ ENDP

; ghidra: FUN_00deff50  retail @ 0x009EFF50 size 3186
public ?d_009eff50@@YAXXZ
?d_009eff50@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 6Ah, 0FFh, 68h, 26h, 1Bh, 06h, 01h, 64h, 0A1h, 00h
    db 00h, 00h, 00h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0BCh, 00h, 00h
    db 00h, 53h, 55h, 56h, 57h, 8Bh, 0E9h, 8Dh, 45h, 60h, 50h, 89h, 6Ch, 24h, 1Ch, 89h
    db 84h, 24h, 0B0h, 00h, 00h, 00h, 0FFh, 15h, 18h, 8Dh, 35h, 01h, 8Dh, 0B5h, 90h, 01h
    db 00h, 00h, 33h, 0FFh, 56h, 8Bh, 0CDh, 89h, 0BCh, 24h, 0D8h, 00h, 00h, 00h, 0E8h, 9Dh
    db 0FDh, 0FFh, 0FFh, 8Dh, 85h, 0A4h, 01h, 00h, 00h, 50h, 8Bh, 0CDh, 0E8h, 8Fh, 0FDh, 0FFh
    db 0FFh, 6Ah, 18h, 89h, 7Ch, 24h, 30h, 0E8h, 84h, 0E5h, 0E3h, 0FFh, 89h, 44h, 24h, 30h
    db 89h, 7Ch, 24h, 34h, 0C6h, 00h, 00h, 8Bh, 44h, 24h, 30h, 89h, 78h, 04h, 8Bh, 44h
    db 24h, 30h, 89h, 40h, 08h, 8Bh, 44h, 24h, 30h, 83h, 0C4h, 04h, 89h, 40h, 0Ch, 56h
    db 8Dh, 8Ch, 24h, 9Ch, 00h, 00h, 00h, 0C6h, 84h, 24h, 0D8h, 00h, 00h, 00h, 01h, 0E8h
    db 0ECh, 0E8h, 0FFh, 0FFh, 89h, 0BCh, 24h, 0A4h, 00h, 00h, 00h, 0C6h, 84h, 24h, 0A8h, 00h
    db 00h, 00h, 01h, 8Bh, 85h, 0B8h, 01h, 00h, 00h, 8Bh, 48h, 08h, 50h, 51h, 8Dh, 8Ch
    db 24h, 0A0h, 00h, 00h, 00h, 0C6h, 84h, 24h, 0DCh, 00h, 00h, 00h, 02h, 0E8h, 0AEh, 0AFh
    db 64h, 0FFh, 8Bh, 9Ch, 24h, 98h, 00h, 00h, 00h, 0C6h, 84h, 24h, 0A8h, 00h, 00h, 00h
    db 01h, 89h, 7Ch, 24h, 14h, 0EBh, 09h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 44h, 24h, 14h, 8Dh, 4Ch, 80h, 0Fh, 8Bh, 7Ch, 0CDh, 0Ch, 8Bh, 54h, 0CDh, 1Ch
    db 8Bh, 74h, 0CDh, 14h, 8Dh, 44h, 0CDh, 00h, 8Bh, 48h, 10h, 2Bh, 0D7h, 8Bh, 38h, 0C1h
    db 0FAh, 02h, 2Bh, 0CEh, 4Ah, 0C1h, 0F9h, 02h, 0C1h, 0E2h, 05h, 03h, 0D1h, 8Bh, 48h, 08h
    db 2Bh, 0CFh, 0C1h, 0F9h, 02h, 03h, 0D1h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h
    db 44h, 24h, 4Ch, 0Fh, 84h, 0D9h, 05h, 00h, 00h, 8Bh, 44h, 24h, 14h, 33h, 0D2h, 83h
    db 0F8h, 04h, 0Fh, 9Ch, 0C2h, 89h, 94h, 24h, 0B0h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 8Bh, 4Ch, 24h, 4Ch, 8Bh, 01h, 8Bh, 51h, 04h, 8Bh, 79h, 08h, 8Bh, 71h, 0Ch, 8Bh
    db 0C8h, 2Bh, 0CAh, 0C1h, 0F9h, 02h, 03h, 4Ch, 24h, 10h, 78h, 0Eh, 83h, 0F9h, 20h, 7Dh
    db 09h, 8Bh, 4Ch, 24h, 10h, 8Dh, 0Ch, 88h, 0EBh, 32h, 85h, 0C9h, 7Eh, 0Dh, 8Bh, 0C1h
    db 99h, 83h, 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 0EBh, 0Dh, 8Dh, 41h, 01h, 99h, 83h
    db 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 48h, 8Bh, 14h, 86h, 8Dh, 34h, 86h, 0C1h, 0E0h
    db 05h, 2Bh, 0C8h, 8Dh, 0BAh, 80h, 00h, 00h, 00h, 8Dh, 0Ch, 8Ah, 8Bh, 0C1h, 89h, 74h
    db 24h, 28h, 8Bh, 30h, 8Bh, 43h, 04h, 85h, 0C0h, 89h, 54h, 24h, 20h, 8Bh, 56h, 08h
    db 89h, 7Ch, 24h, 24h, 8Bh, 0CBh, 74h, 1Ch, 39h, 50h, 10h, 72h, 07h, 8Bh, 0C8h, 8Bh
    db 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch, 85h, 0C0h, 75h, 0EDh, 3Bh, 0CBh, 74h, 05h, 3Bh
    db 51h, 10h, 73h, 02h, 8Bh, 0CBh, 3Bh, 0CBh, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h, 00h, 0Fh
    db 95h, 0C2h, 0Fh, 0B6h, 0C2h, 3Bh, 0C1h, 0Fh, 84h, 0D8h, 04h, 00h, 00h, 8Bh, 4Ch, 24h
    db 14h, 8Bh, 46h, 04h, 33h, 0D2h, 83h, 0F9h, 03h, 0Fh, 9Fh, 0C2h, 8Bh, 0F8h, 0C1h, 0E2h
    db 19h, 33h, 0D0h, 81h, 0E2h, 00h, 00h, 00h, 02h, 33h, 0FAh, 83h, 0F9h, 03h, 89h, 7Eh
    db 04h, 8Bh, 0C7h, 0Fh, 85h, 26h, 01h, 00h, 00h, 0A9h, 00h, 00h, 00h, 04h, 0Fh, 85h
    db 9Ah, 04h, 00h, 00h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 41h, 04h, 85h, 0C0h, 8Bh, 56h, 10h
    db 89h, 54h, 24h, 50h, 89h, 74h, 24h, 54h, 74h, 19h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 3Bh, 50h, 10h, 8Bh, 0C8h, 73h, 05h, 8Bh, 40h, 08h, 0EBh, 03h, 8Bh, 40h, 0Ch, 85h
    db 0C0h, 75h, 0EDh, 6Ah, 00h, 8Dh, 54h, 24h, 54h, 52h, 51h, 50h, 8Dh, 84h, 24h, 0D4h
    db 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 40h, 0E8h, 13h, 0DAh, 0FFh, 0FFh, 8Bh, 0BDh, 0FCh
    db 00h, 00h, 00h, 8Bh, 8Dh, 0Ch, 01h, 00h, 00h, 8Bh, 95h, 00h, 01h, 00h, 00h, 8Bh
    db 85h, 0F8h, 00h, 00h, 00h, 2Bh, 0CFh, 8Bh, 0BDh, 04h, 01h, 00h, 00h, 8Dh, 0B5h, 0F0h
    db 00h, 00h, 00h, 0C1h, 0F9h, 02h, 49h, 2Bh, 0D7h, 8Bh, 3Eh, 0C1h, 0E1h, 05h, 0C1h, 0FAh
    db 02h, 03h, 0CAh, 2Bh, 0C7h, 0C1h, 0F8h, 02h, 8Dh, 44h, 01h, 0FFh, 8Bh, 0CEh, 8Bh, 11h
    db 89h, 54h, 24h, 78h, 8Bh, 51h, 04h, 89h, 54h, 24h, 7Ch, 8Bh, 51h, 08h, 8Bh, 49h
    db 0Ch, 89h, 8Ch, 24h, 84h, 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 7Ch, 89h, 94h, 24h
    db 84h, 00h, 00h, 00h, 0E8h, 67h, 0D2h, 0FFh, 0FFh, 8Bh, 54h, 24h, 7Ch, 8Bh, 84h, 24h
    db 80h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 84h, 00h, 00h, 00h, 8Bh, 7Ch, 24h, 78h, 89h
    db 54h, 24h, 20h, 89h, 44h, 24h, 24h, 89h, 4Ch, 24h, 28h, 8Bh, 0D6h, 8Bh, 02h, 8Bh
    db 4Ah, 04h, 89h, 44h, 24h, 58h, 8Bh, 42h, 08h, 89h, 4Ch, 24h, 5Ch, 8Bh, 4Ah, 0Ch
    db 8Bh, 54h, 24h, 10h, 89h, 4Ch, 24h, 64h, 52h, 8Dh, 4Ch, 24h, 5Ch, 89h, 44h, 24h
    db 64h, 0E8h, 1Ah, 0D2h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 5Ch, 8Bh, 44h, 24h, 58h, 8Bh, 54h
    db 24h, 60h, 89h, 4Ch, 24h, 20h, 8Bh, 4Ch, 24h, 64h, 0E9h, 2Fh, 03h, 00h, 00h, 83h
    db 0F9h, 04h, 0Fh, 85h, 35h, 02h, 00h, 00h, 8Bh, 4Eh, 04h, 8Bh, 16h, 81h, 0E1h, 0FFh
    db 0FFh, 03h, 0FFh, 81h, 0C9h, 00h, 00h, 03h, 00h, 89h, 4Eh, 04h, 8Bh, 0CEh, 0FFh, 52h
    db 38h, 8Bh, 7Ch, 24h, 18h, 01h, 47h, 20h, 81h, 0C7h, 18h, 01h, 00h, 00h, 8Bh, 0C7h
    db 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 58h, 08h, 8Bh, 68h, 0Ch, 8Bh, 44h, 24h, 10h, 89h
    db 4Ch, 24h, 38h, 2Bh, 0CAh, 0C1h, 0F9h, 02h, 03h, 0C8h, 78h, 0Eh, 83h, 0F9h, 20h, 7Dh
    db 09h, 8Bh, 4Ch, 24h, 38h, 8Dh, 0Ch, 81h, 0EBh, 34h, 85h, 0C9h, 7Eh, 0Dh, 8Bh, 0C1h
    db 99h, 83h, 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 0EBh, 0Dh, 8Dh, 41h, 01h, 99h, 83h
    db 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 48h, 8Bh, 54h, 85h, 00h, 8Dh, 6Ch, 85h, 00h
    db 0C1h, 0E0h, 05h, 2Bh, 0C8h, 8Dh, 9Ah, 80h, 00h, 00h, 00h, 8Dh, 0Ch, 8Ah, 8Bh, 76h
    db 04h, 0C1h, 0EEh, 10h, 81h, 0E6h, 0FFh, 00h, 00h, 00h, 89h, 94h, 24h, 0B8h, 00h, 00h
    db 00h, 8Bh, 54h, 24h, 18h, 83h, 0C6h, 03h, 89h, 8Ch, 24h, 0B4h, 00h, 00h, 00h, 8Dh
    db 0Ch, 0B6h, 8Bh, 44h, 0CAh, 10h, 8Dh, 0Ch, 0CAh, 8Bh, 51h, 18h, 83h, 0EAh, 04h, 3Bh
    db 0C2h, 89h, 9Ch, 24h, 0BCh, 00h, 00h, 00h, 89h, 0ACh, 24h, 0C0h, 00h, 00h, 00h, 74h
    db 15h, 85h, 0C0h, 74h, 0Bh, 8Bh, 94h, 24h, 0B4h, 00h, 00h, 00h, 8Bh, 12h, 89h, 10h
    db 83h, 41h, 10h, 04h, 0EBh, 0Dh, 8Bh, 84h, 24h, 0B4h, 00h, 00h, 00h, 50h, 0E8h, 3Dh
    db 0EDh, 0FFh, 0FFh, 8Bh, 6Fh, 0Ch, 8Bh, 4Fh, 1Ch, 8Bh, 47h, 14h, 8Bh, 57h, 10h, 8Bh
    db 37h, 2Bh, 0CDh, 0C1h, 0F9h, 02h, 49h, 2Bh, 0D0h, 8Bh, 47h, 08h, 0C1h, 0E1h, 05h, 2Bh
    db 0C6h, 0C1h, 0FAh, 02h, 03h, 0CAh, 0C1h, 0F8h, 02h, 8Dh, 44h, 01h, 0FFh, 8Bh, 0CFh, 8Bh
    db 29h, 8Bh, 51h, 04h, 8Bh, 59h, 08h, 8Bh, 71h, 0Ch, 8Bh, 0CDh, 2Bh, 0CAh, 0C1h, 0F9h
    db 02h, 03h, 0C8h, 78h, 0Bh, 83h, 0F9h, 20h, 7Dh, 06h, 8Dh, 4Ch, 85h, 00h, 0EBh, 32h
    db 85h, 0C9h, 7Eh, 0Dh, 8Bh, 0C1h, 99h, 83h, 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 0EBh
    db 0Dh, 8Dh, 41h, 01h, 99h, 83h, 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 48h, 8Bh, 14h
    db 86h, 8Dh, 34h, 86h, 0C1h, 0E0h, 05h, 2Bh, 0C8h, 8Dh, 9Ah, 80h, 00h, 00h, 00h, 8Dh
    db 0Ch, 8Ah, 8Bh, 0E9h, 8Bh, 0CFh, 8Bh, 01h, 89h, 54h, 24h, 20h, 8Bh, 51h, 04h, 89h
    db 5Ch, 24h, 24h, 8Bh, 59h, 08h, 89h, 74h, 24h, 28h, 8Bh, 71h, 0Ch, 8Bh, 0C8h, 2Bh
    db 0CAh, 0C1h, 0F9h, 02h, 03h, 4Ch, 24h, 10h, 78h, 0Eh, 83h, 0F9h, 20h, 7Dh, 09h, 8Bh
    db 4Ch, 24h, 10h, 8Dh, 0Ch, 88h, 0EBh, 32h, 85h, 0C9h, 7Eh, 0Dh, 8Bh, 0C1h, 99h, 83h
    db 0E2h, 1Fh, 03h, 0C2h, 0C1h, 0F8h, 05h, 0EBh, 0Dh, 8Dh, 41h, 01h, 99h, 83h, 0E2h, 1Fh
    db 03h, 0C2h, 0C1h, 0F8h, 05h, 48h, 8Bh, 14h, 86h, 8Dh, 34h, 86h, 0C1h, 0E0h, 05h, 2Bh
    db 0C8h, 8Dh, 9Ah, 80h, 00h, 00h, 00h, 8Dh, 0Ch, 8Ah, 8Bh, 0C1h, 89h, 54h, 24h, 20h
    db 8Bh, 55h, 00h, 89h, 10h, 8Bh, 4Fh, 10h, 8Bh, 47h, 14h, 3Bh, 0C8h, 89h, 5Ch, 24h
    db 24h, 89h, 74h, 24h, 28h, 74h, 0Fh, 8Bh, 6Ch, 24h, 18h, 83h, 0C1h, 0FCh, 89h, 4Fh
    db 10h, 0E9h, 74h, 01h, 00h, 00h, 85h, 0C0h, 74h, 0Eh, 68h, 80h, 00h, 00h, 00h, 50h
    db 0E8h, 3Bh, 0E1h, 0E3h, 0FFh, 83h, 0C4h, 08h, 8Bh, 47h, 1Ch, 8Bh, 6Ch, 24h, 18h, 83h
    db 0E8h, 04h, 89h, 47h, 1Ch, 8Bh, 00h, 89h, 47h, 14h, 05h, 80h, 00h, 00h, 00h, 89h
    db 47h, 18h, 83h, 0E8h, 04h, 89h, 47h, 10h, 0E9h, 3Dh, 01h, 00h, 00h, 85h, 0C9h, 0Fh
    db 85h, 39h, 01h, 00h, 00h, 8Bh, 4Eh, 04h, 81h, 0E1h, 0FFh, 0FFh, 07h, 0FFh, 81h, 0C9h
    db 00h, 00h, 07h, 00h, 89h, 4Eh, 04h, 8Bh, 9Dh, 84h, 00h, 00h, 00h, 8Bh, 95h, 94h
    db 00h, 00h, 00h, 8Bh, 85h, 88h, 00h, 00h, 00h, 8Bh, 8Dh, 80h, 00h, 00h, 00h, 2Bh
    db 0D3h, 8Bh, 9Dh, 8Ch, 00h, 00h, 00h, 8Dh, 75h, 78h, 0C1h, 0FAh, 02h, 4Ah, 0C1h, 0E2h
    db 05h, 2Bh, 0C3h, 2Bh, 0Eh, 0C1h, 0F9h, 02h, 0C1h, 0F8h, 02h, 03h, 0D0h, 8Dh, 44h, 0Ah
    db 0FFh, 8Bh, 0D6h, 8Bh, 0Ah, 89h, 8Ch, 24h, 88h, 00h, 00h, 00h, 8Bh, 4Ah, 04h, 89h
    db 8Ch, 24h, 8Ch, 00h, 00h, 00h, 8Bh, 4Ah, 08h, 8Bh, 52h, 0Ch, 89h, 8Ch, 24h, 90h
    db 00h, 00h, 00h, 50h, 8Dh, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 89h, 94h, 24h, 98h, 00h
    db 00h, 00h, 0E8h, 39h, 0CFh, 0FFh, 0FFh, 8Bh, 84h, 24h, 8Ch, 00h, 00h, 00h, 8Bh, 8Ch
    db 24h, 90h, 00h, 00h, 00h, 8Bh, 94h, 24h, 94h, 00h, 00h, 00h, 8Bh, 0BCh, 24h, 88h
    db 00h, 00h, 00h, 89h, 44h, 24h, 20h, 89h, 4Ch, 24h, 24h, 8Bh, 0C6h, 8Bh, 08h, 89h
    db 54h, 24h, 28h, 8Bh, 50h, 04h, 89h, 4Ch, 24h, 68h, 8Bh, 48h, 08h, 89h, 54h, 24h
    db 6Ch, 8Bh, 50h, 0Ch, 8Bh, 44h, 24h, 10h, 89h, 4Ch, 24h, 70h, 50h, 8Dh, 4Ch, 24h
    db 6Ch, 89h, 54h, 24h, 78h, 0E8h, 0E6h, 0CEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 6Ch, 8Bh, 44h
    db 24h, 68h, 8Bh, 54h, 24h, 70h, 89h, 4Ch, 24h, 20h, 8Bh, 4Ch, 24h, 74h, 89h, 54h
    db 24h, 24h, 8Bh, 17h, 89h, 10h, 8Bh, 46h, 14h, 89h, 4Ch, 24h, 28h, 8Bh, 4Eh, 10h
    db 3Bh, 0C8h, 74h, 08h, 83h, 0C1h, 0FCh, 89h, 4Eh, 10h, 0EBh, 2Eh, 85h, 0C0h, 74h, 0Eh
    db 68h, 80h, 00h, 00h, 00h, 50h, 0E8h, 0F5h, 0DFh, 0E3h, 0FFh, 83h, 0C4h, 08h, 8Bh, 46h
    db 1Ch, 83h, 0E8h, 04h, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 05h, 80h, 00h, 00h
    db 00h, 89h, 46h, 18h, 83h, 0E8h, 04h, 89h, 46h, 10h, 0FFh, 4Ch, 24h, 10h, 8Bh, 9Ch
    db 24h, 98h, 00h, 00h, 00h, 8Bh, 44h, 24h, 4Ch, 8Bh, 78h, 0Ch, 8Bh, 50h, 1Ch, 8Bh
    db 4Ch, 24h, 10h, 8Bh, 70h, 10h, 2Bh, 0D7h, 8Bh, 78h, 14h, 0C1h, 0FAh, 02h, 2Bh, 0F7h
    db 8Bh, 38h, 41h, 4Ah, 0C1h, 0FEh, 02h, 0C1h, 0E2h, 05h, 03h, 0D6h, 8Bh, 70h, 08h, 2Bh
    db 0F7h, 0C1h, 0FEh, 02h, 03h, 0D6h, 3Bh, 0CAh, 89h, 4Ch, 24h, 10h, 0Fh, 82h, 3Eh, 0FAh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 14h, 40h, 83h, 0F8h, 07h, 89h, 44h, 24h, 14h, 0Fh, 8Ch
    db 0CCh, 0F9h, 0FFh, 0FFh, 8Bh, 45h, 20h, 3Bh, 45h, 24h, 0Fh, 8Ch, 0FBh, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 30h, 85h, 0C0h, 0Fh, 84h, 0EFh, 00h, 00h, 00h, 8Bh, 44h, 24h, 2Ch
    db 8Bh, 50h, 08h, 8Bh, 7Ah, 14h, 8Dh, 70h, 0Ch, 8Dh, 48h, 08h, 56h, 51h, 83h, 0C0h
    db 04h, 50h, 52h, 0E8h, 0B8h, 0C4h, 0E3h, 0FFh, 83h, 0C4h, 10h, 85h, 0C0h, 74h, 0Bh, 6Ah
    db 18h, 50h, 0E8h, 39h, 0DFh, 0E3h, 0FFh, 83h, 0C4h, 08h, 0FFh, 4Ch, 24h, 30h, 8Bh, 4Fh
    db 04h, 8Bh, 17h, 81h, 0E1h, 0FFh, 0FFh, 04h, 0FFh, 81h, 0C9h, 00h, 00h, 04h, 00h, 89h
    db 4Fh, 04h, 8Bh, 0CFh, 0FFh, 52h, 38h, 29h, 45h, 20h, 8Bh, 47h, 04h, 0C1h, 0E8h, 10h
    db 25h, 0FFh, 00h, 00h, 00h, 83h, 0C0h, 03h, 8Dh, 04h, 80h, 8Bh, 4Ch, 0C5h, 18h, 8Dh
    db 74h, 0C5h, 00h, 8Bh, 46h, 10h, 83h, 0E9h, 04h, 3Bh, 0C1h, 74h, 0Ch, 85h, 0C0h, 74h
    db 02h, 89h, 38h, 83h, 46h, 10h, 04h, 0EBh, 58h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 20h, 8Bh
    db 46h, 24h, 2Bh, 0D1h, 0C1h, 0FAh, 02h, 2Bh, 0C2h, 83h, 0F8h, 02h, 73h, 0Bh, 6Ah, 00h
    db 6Ah, 01h, 8Bh, 0CEh, 0E8h, 37h, 0DCh, 0FFh, 0FFh, 68h, 80h, 00h, 00h, 00h, 0E8h, 0Dh
    db 0DEh, 0E3h, 0FFh, 8Bh, 4Eh, 1Ch, 89h, 41h, 04h, 8Bh, 46h, 10h, 83h, 0C4h, 04h, 85h
    db 0C0h, 74h, 02h, 89h, 38h, 8Bh, 46h, 1Ch, 83h, 0C0h, 04h, 89h, 46h, 1Ch, 8Bh, 00h
    db 89h, 46h, 14h, 05h, 80h, 00h, 00h, 00h, 89h, 46h, 18h, 8Bh, 56h, 14h, 89h, 56h
    db 10h, 8Bh, 45h, 20h, 85h, 0C0h, 7Dh, 07h, 0C7h, 45h, 20h, 00h, 00h, 00h, 00h, 8Bh
    db 45h, 20h, 3Bh, 45h, 24h, 0Fh, 8Dh, 05h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 2Ch, 8Bh
    db 58h, 08h, 3Bh, 0D8h, 0Fh, 84h, 96h, 00h, 00h, 00h, 8Dh, 0B5h, 0F0h, 00h, 00h, 00h
    db 8Bh, 4Eh, 18h, 8Bh, 46h, 10h, 83h, 0E9h, 04h, 3Bh, 0C1h, 74h, 11h, 85h, 0C0h, 74h
    db 05h, 8Bh, 53h, 14h, 89h, 10h, 8Bh, 46h, 10h, 83h, 0C0h, 04h, 0EBh, 58h, 8Bh, 46h
    db 1Ch, 8Bh, 56h, 20h, 8Bh, 4Eh, 24h, 8Bh, 7Bh, 14h, 2Bh, 0C2h, 0C1h, 0F8h, 02h, 2Bh
    db 0C8h, 83h, 0F9h, 02h, 73h, 0Bh, 6Ah, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 8Fh, 0DBh, 0FFh
    db 0FFh, 68h, 80h, 00h, 00h, 00h, 0E8h, 65h, 0DDh, 0E3h, 0FFh, 8Bh, 56h, 1Ch, 89h, 42h
    db 04h, 8Bh, 46h, 10h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 02h, 89h, 38h, 8Bh, 46h, 1Ch
    db 83h, 0C0h, 04h, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 18h, 8Bh, 46h, 14h, 53h, 89h, 46h, 10h, 0E8h, 61h, 0B0h, 0E3h, 0FFh, 8Bh
    db 0D8h, 8Bh, 44h, 24h, 30h, 83h, 0C4h, 04h, 3Bh, 0D8h, 0Fh, 85h, 70h, 0FFh, 0FFh, 0FFh
    db 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 33h, 0F6h, 6Ah, 14h, 89h, 74h, 24h, 3Ch
    db 0E8h, 0Bh, 0DDh, 0E3h, 0FFh, 89h, 44h, 24h, 3Ch, 89h, 74h, 24h, 40h, 0C6h, 00h, 00h
    db 8Bh, 4Ch, 24h, 3Ch, 89h, 71h, 04h, 8Bh, 44h, 24h, 3Ch, 89h, 40h, 08h, 8Bh, 44h
    db 24h, 3Ch, 89h, 40h, 0Ch, 83h, 0C4h, 04h, 89h, 74h, 24h, 44h, 0C6h, 44h, 24h, 48h
    db 01h, 39h, 74h, 24h, 18h, 0C6h, 84h, 24h, 0D4h, 00h, 00h, 00h, 03h, 75h, 69h, 8Dh
    db 54h, 24h, 38h, 8Dh, 0B5h, 0A4h, 01h, 00h, 00h, 3Bh, 0D6h, 74h, 14h, 56h, 8Bh, 0CAh
    db 0E8h, 0FBh, 49h, 62h, 0FFh, 8Bh, 46h, 0Ch, 0C6h, 44h, 24h, 48h, 01h, 89h, 44h, 24h
    db 44h, 8Dh, 85h, 90h, 01h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 3Ch, 0E8h, 0CFh, 0BEh, 0FFh
    db 0FFh, 8Bh, 0BDh, 0B8h, 01h, 00h, 00h, 8Bh, 77h, 08h, 3Bh, 0F7h, 74h, 23h, 8Bh, 0FFh
    db 8Dh, 4Eh, 10h, 51h, 8Dh, 54h, 24h, 54h, 52h, 8Dh, 4Ch, 24h, 40h, 0E8h, 51h, 0FBh
    db 63h, 0FFh, 56h, 0E8h, 0A8h, 0AFh, 0E3h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 04h, 3Bh, 0F7h, 75h
    db 0DFh, 0C6h, 44h, 24h, 48h, 01h, 0EBh, 32h, 8Dh, 44h, 24h, 38h, 8Dh, 0B5h, 90h, 01h
    db 00h, 00h, 3Bh, 0C6h, 74h, 14h, 56h, 8Bh, 0C8h, 0E8h, 92h, 49h, 62h, 0FFh, 8Bh, 4Eh
    db 0Ch, 0C6h, 44h, 24h, 48h, 01h, 89h, 4Ch, 24h, 44h, 8Dh, 85h, 0A4h, 01h, 00h, 00h
    db 50h, 8Dh, 4Ch, 24h, 3Ch, 0E8h, 0A6h, 0BCh, 0FFh, 0FFh, 8Bh, 44h, 24h, 38h, 8Bh, 48h
    db 08h, 3Bh, 0C8h, 89h, 4Ch, 24h, 14h, 0Fh, 84h, 0Bh, 01h, 00h, 00h, 8Dh, 5Dh, 44h
    db 8Bh, 0F1h, 8Bh, 53h, 04h, 8Bh, 7Bh, 08h, 8Bh, 4Eh, 10h, 2Bh, 0FAh, 0C1h, 0FFh, 02h
    db 33h, 0D2h, 8Bh, 0C1h, 0F7h, 0F7h, 8Bh, 43h, 04h, 8Bh, 04h, 90h, 85h, 0C0h, 74h, 0Bh
    db 39h, 48h, 04h, 74h, 06h, 8Bh, 00h, 85h, 0C0h, 75h, 0F5h, 85h, 0C0h, 89h, 5Ch, 24h
    db 54h, 0Fh, 84h, 0B6h, 00h, 00h, 00h, 8Bh, 78h, 08h, 8Bh, 57h, 04h, 81h, 0E2h, 00h
    db 00h, 0FFh, 00h, 81h, 0FAh, 00h, 00h, 07h, 00h, 0Fh, 85h, 9Eh, 00h, 00h, 00h, 8Bh
    db 47h, 04h, 25h, 0FFh, 0FFh, 00h, 0FFh, 89h, 47h, 04h, 0Dh, 00h, 00h, 00h, 02h, 89h
    db 47h, 04h, 8Bh, 47h, 04h, 0C1h, 0E8h, 10h, 25h, 0FFh, 00h, 00h, 00h, 83h, 0C0h, 03h
    db 8Dh, 04h, 80h, 8Bh, 4Ch, 0C5h, 18h, 8Dh, 74h, 0C5h, 00h, 8Bh, 46h, 10h, 83h, 0E9h
    db 04h, 3Bh, 0C1h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 38h, 83h, 46h, 10h, 04h, 0EBh
    db 58h, 8Bh, 56h, 1Ch, 8Bh, 4Eh, 20h, 8Bh, 46h, 24h, 2Bh, 0D1h, 0C1h, 0FAh, 02h, 2Bh
    db 0C2h, 83h, 0F8h, 02h, 73h, 0Bh, 6Ah, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 8Fh, 0D9h, 0FFh
    db 0FFh, 68h, 80h, 00h, 00h, 00h, 0E8h, 65h, 0DBh, 0E3h, 0FFh, 8Bh, 4Eh, 1Ch, 89h, 41h
    db 04h, 8Bh, 46h, 10h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 02h, 89h, 38h, 8Bh, 46h, 1Ch
    db 83h, 0C0h, 04h, 89h, 46h, 1Ch, 8Bh, 00h, 89h, 46h, 14h, 05h, 80h, 00h, 00h, 00h
    db 89h, 46h, 18h, 8Bh, 56h, 14h, 89h, 56h, 10h, 8Bh, 74h, 24h, 14h, 56h, 0E8h, 5Dh
    db 0AEh, 0E3h, 0FFh, 8Bh, 0F0h, 8Bh, 44h, 24h, 3Ch, 83h, 0C4h, 04h, 3Bh, 0F0h, 89h, 74h
    db 24h, 14h, 0Fh, 85h, 0FAh, 0FEh, 0FFh, 0FFh, 8Bh, 9Dh, 0ACh, 00h, 00h, 00h, 8Bh, 95h
    db 0D4h, 00h, 00h, 00h, 8Bh, 8Dh, 0BCh, 00h, 00h, 00h, 8Bh, 85h, 0E4h, 00h, 00h, 00h
    db 8Bh, 74h, 24h, 18h, 2Bh, 0C2h, 8Bh, 95h, 94h, 00h, 00h, 00h, 2Bh, 0CBh, 8Bh, 9Dh
    db 84h, 00h, 00h, 00h, 0C1h, 0F8h, 02h, 0C1h, 0F9h, 02h, 2Bh, 0D3h, 03h, 0C1h, 0C1h, 0FAh
    db 02h, 8Dh, 44h, 10h, 0FDh, 0C1h, 0E0h, 05h, 85h, 0F6h, 75h, 73h, 8Bh, 9Dh, 0DCh, 00h
    db 00h, 00h, 8Bh, 8Dh, 0D8h, 00h, 00h, 00h, 8Bh, 95h, 0B0h, 00h, 00h, 00h, 2Bh, 0CBh
    db 2Bh, 95h, 0B4h, 00h, 00h, 00h, 8Bh, 9Dh, 8Ch, 00h, 00h, 00h, 0C1h, 0F9h, 02h, 03h
    db 0C1h, 8Bh, 8Dh, 88h, 00h, 00h, 00h, 0C1h, 0FAh, 02h, 03h, 0C2h, 8Bh, 95h, 0D0h, 00h
    db 00h, 00h, 2Bh, 0CBh, 2Bh, 95h, 0C8h, 00h, 00h, 00h, 8Bh, 5Dh, 78h, 0C1h, 0F9h, 02h
    db 03h, 0C1h, 8Bh, 8Dh, 80h, 00h, 00h, 00h, 0C1h, 0FAh, 02h, 03h, 0C2h, 8Bh, 95h, 0A8h
    db 00h, 00h, 00h, 2Bh, 0CBh, 8Bh, 9Dh, 0A0h, 00h, 00h, 00h, 0C1h, 0F9h, 02h, 2Bh, 0D3h
    db 03h, 0C1h, 0C1h, 0FAh, 02h, 03h, 0C2h, 89h, 85h, 0E0h, 01h, 00h, 00h, 0EBh, 7Bh, 8Bh
    db 9Dh, 0B4h, 00h, 00h, 00h, 8Bh, 8Dh, 0B0h, 00h, 00h, 00h, 8Bh, 95h, 88h, 00h, 00h
    db 00h, 2Bh, 0CBh, 8Bh, 9Dh, 8Ch, 00h, 00h, 00h, 0C1h, 0F9h, 02h, 03h, 0C1h, 8Bh, 8Dh
    db 0D8h, 00h, 00h, 00h, 2Bh, 0D3h, 8Bh, 9Dh, 0DCh, 00h, 00h, 00h, 0C1h, 0FAh, 02h, 03h
    db 0C2h, 8Bh, 95h, 0A8h, 00h, 00h, 00h, 2Bh, 0CBh, 8Bh, 9Dh, 0A0h, 00h, 00h, 00h, 0C1h
    db 0F9h, 02h, 03h, 0C1h, 8Bh, 8Dh, 0D0h, 00h, 00h, 00h, 2Bh, 0D3h, 8Bh, 9Dh, 0C8h, 00h
    db 00h, 00h, 0C1h, 0FAh, 02h, 03h, 0C2h, 8Bh, 95h, 80h, 00h, 00h, 00h, 2Bh, 0CBh, 0C1h
    db 0F9h, 02h, 03h, 0C1h, 2Bh, 55h, 78h, 8Bh, 8Dh, 0E0h, 01h, 00h, 00h, 0C1h, 0FAh, 02h
    db 03h, 0C2h, 2Bh, 0C1h, 89h, 85h, 0E4h, 01h, 00h, 00h, 8Dh, 4Ch, 24h, 38h, 0C6h, 84h
    db 24h, 0D4h, 00h, 00h, 00h, 02h, 0E8h, 0Fh, 52h, 62h, 0FFh, 46h, 83h, 0FEh, 02h, 89h
    db 74h, 24h, 18h, 0Fh, 8Ch, 0AFh, 0FCh, 0FFh, 0FFh, 8Dh, 8Ch, 24h, 98h, 00h, 00h, 00h
    db 0C6h, 84h, 24h, 0D4h, 00h, 00h, 00h, 01h, 0E8h, 0EDh, 51h, 62h, 0FFh, 8Dh, 4Ch, 24h
    db 2Ch, 0C6h, 84h, 24h, 0D4h, 00h, 00h, 00h, 00h, 0E8h, 0D2h, 0D4h, 0FFh, 0FFh, 8Bh, 84h
    db 24h, 0ACh, 00h, 00h, 00h, 50h, 0FFh, 15h, 74h, 8Eh, 35h, 01h, 8Bh, 8Ch, 24h, 0CCh
    db 00h, 00h, 00h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 5Dh, 5Bh, 8Bh, 0E5h
    db 5Dh, 0C3h
?d_009eff50@@YAXXZ ENDP

; retail @ 0x009F74F4 size 14
_TEXT ENDS
_TEXT$d00df74f4 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00DF74F4 size 14
public ?d_009f74f4@@YAXXZ
?d_009f74f4@@YAXXZ PROC
    db 03Bh, 00Dh
    dd ___security_cookie
    db 075h, 001h, 0C3h
    jmp _report_failure
?d_009f74f4@@YAXXZ ENDP
_TEXT$d00df74f4 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
