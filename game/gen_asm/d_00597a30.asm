.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?ClientAt012F1464@@3PAVClient0009A580@@A:BYTE
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?R2Ptr012F19E8@@3PAVGen000290D2@@A:BYTE
EXTERN ?TheControlBar@@3PAURva002AD380ControlBar@@A:BYTE
EXTERN ?g_Slot012BC6C8@@3UBigObfSlot@@A:BYTE
EXTERN ?j_0000134d@@YAXXZ:NEAR
EXTERN ?j_00003f80@@YAXXZ:NEAR
EXTERN ?j_00007518@@YAXXZ:NEAR
EXTERN ?j_0000e65b@@YAXXZ:NEAR
EXTERN ?j_0000f7ef@@YAXXZ:NEAR
EXTERN ?j_0001681a@@YAXXZ:NEAR
EXTERN ?j_000179bd@@YAXXZ:NEAR
EXTERN ?j_0001ccab@@YAXXZ:NEAR
EXTERN ?j_0002791c@@YAXXZ:NEAR
EXTERN ?j_000283d5@@YAXXZ:NEAR
EXTERN ?j_0002b616@@YAXXZ:NEAR
EXTERN ?j_00031322@@YAXXZ:NEAR
EXTERN ?j_00035c92@@YAXXZ:NEAR
EXTERN ?j_0003e16c@@YAXXZ:NEAR
EXTERN ?j_000414d4@@YAXXZ:NEAR
EXTERN ?j_00043757@@YAXXZ:NEAR
EXTERN ?j_000448e6@@YAXXZ:NEAR
EXTERN ?j_00047b31@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN g_Va01037E60:NEAR
EXTERN g_Va012BC6CC:BYTE
EXTERN g_Va012BC750:BYTE
EXTERN g_Va012BC754:BYTE
_TEXT SEGMENT

; retail @ 0x00597A30 size 1020
_TEXT ENDS
_TEXT$d00997a30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00997A30 size 1020
public ?d_00597a30@@YAXXZ
?d_00597a30@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01037E60
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 05Ch, 053h, 055h, 056h, 08Bh, 0D9h, 057h, 089h, 05Ch, 024h, 01Ch
    call ?j_000448e6@@YAXXZ
    db 08Bh, 04Bh, 004h, 033h, 0C0h, 085h, 0C9h, 089h, 044h, 024h, 014h, 00Fh, 084h, 050h, 002h, 000h
    db 000h, 033h, 0F6h, 089h, 074h, 024h, 018h, 08Dh, 06Bh, 024h, 0EBh, 004h, 08Bh, 044h, 024h, 014h
    db 083h, 0F8h, 00Ch, 00Fh, 08Dh, 07Bh, 003h, 000h, 000h, 08Ah, 044h, 01Eh, 008h, 0C6h, 044h, 01Eh
    db 008h, 000h, 08Bh, 04Bh, 004h, 056h, 088h, 044h, 024h, 017h
    call ?j_00003f80@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 0FDh, 001h, 000h, 000h, 06Ah, 000h, 08Dh, 04Ch, 024h, 028h
    db 051h, 08Bh, 00Dh
    dd ?TheControlBar@@3PAURva002AD380ControlBar@@A
    db 06Ah, 000h, 06Ah, 000h, 057h
    call ?j_000414d4@@YAXXZ
    db 08Bh, 0F0h, 083h, 0FEh, 003h, 00Fh, 084h, 0D7h, 001h, 000h, 000h, 083h, 0FEh, 004h, 074h, 008h
    db 0C7h, 044h, 024h, 024h, 000h, 000h, 080h, 03Fh, 08Bh, 015h
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 04Ah, 00Ch, 08Bh, 044h, 024h, 01Ch, 08Bh, 010h, 032h, 0DBh, 03Bh, 0D1h, 074h, 00Fh
    call ?j_000179bd@@YAXXZ
    db 084h, 0C0h, 074h, 004h, 033h, 0F6h, 0EBh, 007h, 0B3h, 001h, 083h, 0FEh, 006h, 077h, 024h, 0FFh
    db 024h, 0B5h
    dd ?d_00597a30@@YAXXZ + 03E0h
    db 0BEh, 004h, 000h, 000h, 000h, 0EBh, 01Bh, 08Bh, 047h, 018h, 025h, 000h, 000h, 000h, 010h, 0F7h
    db 0D8h, 01Bh, 0C0h, 083h, 0E0h, 0FEh, 083h, 0C0h, 005h, 08Bh, 0F0h, 0EBh, 005h, 0BEh, 001h, 000h
    db 000h, 000h, 084h, 0DBh, 074h, 00Eh, 083h, 0FEh, 005h, 075h, 00Eh, 0BEh, 006h, 000h, 000h, 000h
    db 033h, 0C0h, 0EBh, 013h, 083h, 0FEh, 005h, 074h, 009h, 083h, 0FEh, 003h, 074h, 004h, 033h, 0C0h
    db 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 08Bh
    db 05Ch, 024h, 014h, 088h, 044h, 011h, 008h, 039h, 07Dh, 0F8h, 074h, 05Dh, 08Dh, 044h, 024h, 020h
    db 053h, 050h
    call ?j_0000134d@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 045h, 0F8h, 085h, 0C0h, 0C7h, 044h, 024h, 074h, 000h, 000h, 000h, 000h
    db 074h, 010h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    call ?j_00047b31@@YAXXZ
    db 08Bh, 0CFh, 089h, 07Dh, 0F8h
    call ?j_00035c92@@YAXXZ
    db 085h, 0C0h, 074h, 011h, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 050h, 08Dh, 054h, 024h, 024h, 052h
    call ?j_0001681a@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h, 0C7h, 044h, 024h, 074h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 056h, 056h
    call ?j_000283d5@@YAXXZ
    db 08Bh, 04Dh, 000h, 050h, 051h
    call ?j_00007518@@YAXXZ
    db 083h, 0C4h, 010h, 03Dh, 098h, 0DAh, 04Ah, 094h, 075h, 01Bh, 056h, 056h
    call ?j_000283d5@@YAXXZ
    db 050h, 050h, 089h, 045h, 000h
    call ?j_0000e65b@@YAXXZ
    db 050h, 053h
    call ?j_0000f7ef@@YAXXZ
    db 083h, 0C4h, 018h, 08Bh, 044h, 024h, 024h, 089h, 045h, 004h, 0A1h
    dd ?TheControlBar@@3PAURva002AD380ControlBar@@A
    db 085h, 0C0h, 074h, 008h, 08Bh, 080h, 06Ch, 002h, 000h, 000h, 0EBh, 005h, 0B8h, 000h, 000h, 000h
    db 0C0h, 089h, 045h, 008h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 075h, 019h, 08Bh, 04Ch, 024h, 01Ch
    db 08Bh, 054h, 024h, 018h, 08Ah, 044h, 00Ah, 008h, 084h, 0C0h, 074h, 009h, 053h
    call ?j_0002791c@@YAXXZ
    db 083h, 0C4h, 004h, 08Bh, 087h, 044h, 001h, 000h, 000h, 085h, 0C0h, 07Eh, 025h, 08Bh, 00Dh
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 08Bh, 001h, 0FFh, 050h, 068h, 033h, 0D2h, 0B9h, 00Ah, 000h, 000h, 000h, 0F7h, 0F1h, 085h, 0D2h
    db 075h, 00Dh, 08Bh, 087h, 044h, 001h, 000h, 000h, 048h, 089h, 087h, 044h, 001h, 000h, 000h, 08Bh
    db 08Fh, 044h, 001h, 000h, 000h, 08Ah, 045h, 00Ch, 085h, 0C9h, 00Fh, 09Fh, 0C3h, 03Ah, 0D8h, 088h
    db 05Ch, 024h, 028h, 074h, 015h, 08Bh, 054h, 024h, 028h, 08Bh, 044h, 024h, 014h, 052h, 050h
    call ?j_0002b616@@YAXXZ
    db 083h, 0C4h, 008h, 088h, 05Dh, 00Ch, 08Bh, 04Ch, 024h, 014h, 08Bh, 05Ch, 024h, 01Ch, 041h, 089h
    db 04Ch, 024h, 014h, 083h, 0C5h, 018h, 08Bh, 074h, 024h, 018h, 046h, 083h, 0FEh, 014h, 089h, 074h
    db 024h, 018h, 00Fh, 08Ch, 0C8h, 0FDh, 0FFh, 0FFh, 08Bh, 044h, 024h, 014h, 083h, 0F8h, 00Ch, 00Fh
    db 08Dh, 043h, 001h, 000h, 000h, 08Dh, 00Ch, 040h, 0C7h, 044h, 024h, 024h, 098h, 0DAh, 04Ah, 094h
    db 08Dh, 074h, 0CBh, 024h, 0EBh, 007h, 08Bh, 044h, 024h, 014h, 08Dh, 049h, 000h, 08Bh, 04Eh, 0F8h
    db 085h, 0C9h, 074h, 03Ah, 050h, 08Dh, 054h, 024h, 02Ch, 052h
    call ?j_0000134d@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 050h, 0C7h, 044h, 024h, 078h, 001h, 000h, 000h, 000h
    call ?j_00047b31@@YAXXZ
    db 08Dh, 04Ch, 024h, 028h, 0C7h, 044h, 024h, 074h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 0C7h, 046h, 0F8h, 000h, 000h, 000h, 000h, 08Bh, 03Dh
    dd ?g_Slot012BC6C8@@3UBigObfSlot@@A
    db 085h, 0FFh, 08Bh, 006h, 089h, 044h, 024h, 020h, 075h, 00Ah, 08Bh, 00Dh
    dd g_Va012BC6CC
    db 085h, 0C9h, 074h, 02Fh, 08Bh, 01Dh
    dd g_Va012BC750
    db 08Bh, 02Dh
    dd g_Va012BC754
    db 08Dh, 044h, 024h, 024h, 050h, 08Dh, 04Ch, 024h, 024h, 051h, 08Dh, 04Ch, 024h, 034h
    call ?j_00043757@@YAXXZ
    db 08Dh, 044h, 024h, 02Ch, 099h, 052h, 050h, 055h, 053h, 0FFh, 0D7h, 083h, 0C4h, 010h, 0EBh, 00Eh
    db 068h, 098h, 0DAh, 04Ah, 094h, 050h
    call ?j_0003e16c@@YAXXZ
    db 083h, 0C4h, 008h, 03Dh, 098h, 0DAh, 04Ah, 094h, 075h, 065h, 08Bh, 054h, 024h, 014h, 033h, 0DBh
    db 053h, 052h
    call ?j_0000f7ef@@YAXXZ
    db 08Bh, 03Dh
    dd ?g_Slot012BC6C8@@3UBigObfSlot@@A
    db 083h, 0C4h, 008h, 03Bh, 0FBh, 089h, 05Ch, 024h, 020h, 089h, 05Ch, 024h, 01Ch, 075h, 008h, 039h
    db 01Dh
    dd g_Va012BC6CC
    db 074h, 02Fh, 08Bh, 01Dh
    dd g_Va012BC750
    db 08Bh, 02Dh
    dd g_Va012BC754
    db 08Dh, 044h, 024h, 020h, 050h, 08Dh, 04Ch, 024h, 020h, 051h, 08Dh, 04Ch, 024h, 054h
    call ?j_00031322@@YAXXZ
    db 08Dh, 044h, 024h, 04Ch, 099h, 052h, 050h, 055h, 053h, 0FFh, 0D7h, 083h, 0C4h, 010h, 0EBh, 00Ah
    db 053h, 053h
    call ?j_0001ccab@@YAXXZ
    db 083h, 0C4h, 008h, 089h, 006h, 08Bh, 044h, 024h, 014h, 040h, 0C7h, 046h, 004h, 000h, 000h, 080h
    db 03Fh, 0C7h, 046h, 008h, 000h, 000h, 000h, 000h, 0C6h, 046h, 00Ch, 000h, 083h, 0C6h, 018h, 083h
    db 0F8h, 00Ch, 089h, 044h, 024h, 014h, 00Fh, 08Ch, 0CEh, 0FEh, 0FFh, 0FFh, 08Bh, 04Ch, 024h, 06Ch
    db 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 068h, 0C3h, 08Bh
    db 0FFh
    dd ?d_00597a30@@YAXXZ + 0ECh
    dd ?d_00597a30@@YAXXZ + 0D6h
    dd ?d_00597a30@@YAXXZ + 0D6h
    dd ?d_00597a30@@YAXXZ + 0ECh
    dd ?d_00597a30@@YAXXZ + 0CFh
    dd ?d_00597a30@@YAXXZ + 0ECh
    dd ?d_00597a30@@YAXXZ + 0ECh
?d_00597a30@@YAXXZ ENDP
_TEXT$d00997a30 ENDS
_TEXT SEGMENT

; retail @ 0x0059CBF0 size 1160
public ?d_0059cbf0@@YAXXZ
?d_0059cbf0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 20h, 48h, 83h, 0F8h, 06h, 0Fh, 87h, 56h, 04h, 00h
    db 00h, 0FFh, 24h, 85h, 5Ch, 0D0h, 99h, 00h, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh
    db 14h, 8Bh, 56h, 10h, 68h, 2Dh, 0CBh, 0FFh, 64h, 83h, 0E8h, 02h, 68h, 00h, 00h, 80h
    db 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch
    db 41h, 89h, 4Ch, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h
    db 0DBh, 44h, 24h, 1Ch, 89h, 54h, 24h, 1Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 1Ch
    db 0D9h, 1Ch, 24h, 0E8h, 06h, 0CAh, 0A8h, 0FFh, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh
    db 14h, 8Bh, 56h, 10h, 83h, 0E8h, 02h, 68h, 2Dh, 0CBh, 0FFh, 21h, 83h, 0ECh, 10h, 0D9h
    db 5Ch, 24h, 0Ch, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h, 18h, 41h, 89h, 4Ch, 24h, 18h
    db 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 18h, 89h
    db 54h, 24h, 18h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 18h, 0D9h, 1Ch, 24h, 0E8h, 0FFh
    db 72h, 0A7h, 0FFh, 5Eh, 59h, 0C3h, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh
    db 56h, 10h, 68h, 2Dh, 0CBh, 0FFh, 96h, 83h, 0E8h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h
    db 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 41h, 89h
    db 4Ch, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h
    db 24h, 1Ch, 89h, 54h, 24h, 1Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch
    db 24h, 0E8h, 68h, 0C9h, 0A8h, 0FFh, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh
    db 56h, 10h, 83h, 0E8h, 02h, 68h, 2Dh, 0CBh, 0FFh, 42h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h
    db 0Ch, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h, 18h, 41h, 89h, 4Ch, 24h, 18h, 8Bh, 0Dh
    db 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 18h, 89h, 54h, 24h
    db 18h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 18h, 0D9h, 1Ch, 24h, 0E8h, 61h, 72h, 0A7h
    db 0FFh, 5Eh, 59h, 0C3h, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h
    db 68h, 2Dh, 0CBh, 0FFh, 0C8h, 83h, 0E8h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h
    db 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 41h, 89h, 4Ch, 24h
    db 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 1Ch
    db 89h, 54h, 24h, 1Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch, 24h, 0E8h
    db 0CAh, 0C8h, 0A8h, 0FFh, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h
    db 83h, 0E8h, 02h, 68h, 2Dh, 0CBh, 0FFh, 63h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h
    db 44h, 24h, 18h, 0DBh, 44h, 24h, 18h, 41h, 89h, 4Ch, 24h, 18h, 8Bh, 0Dh, 70h, 12h
    db 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 18h, 89h, 54h, 24h, 18h, 0D9h
    db 5Ch, 24h, 04h, 0DBh, 44h, 24h, 18h, 0D9h, 1Ch, 24h, 0E8h, 0C3h, 71h, 0A7h, 0FFh, 5Eh
    db 59h, 0C3h, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 68h, 2Dh
    db 0CBh, 0FFh, 0FAh, 83h, 0E8h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch
    db 24h, 0Ch, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 41h, 89h, 4Ch, 24h, 1Ch, 8Bh
    db 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 1Ch, 89h, 54h
    db 24h, 1Ch, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch, 24h, 0E8h, 2Ch, 0C8h
    db 0A8h, 0FFh, 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 83h, 0E8h
    db 02h, 68h, 2Dh, 0CBh, 0FFh, 4Bh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h
    db 18h, 0DBh, 44h, 24h, 18h, 41h, 89h, 4Ch, 24h, 18h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h
    db 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 18h, 89h, 54h, 24h, 18h, 0D9h, 5Ch, 24h
    db 04h, 0DBh, 44h, 24h, 18h, 0D9h, 1Ch, 24h, 0E8h, 25h, 71h, 0A7h, 0FFh, 5Eh, 59h, 0C3h
    db 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 68h, 2Dh, 0CBh, 0FFh
    db 0FAh, 83h, 0E8h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch
    db 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 41h, 89h, 4Ch, 24h, 1Ch, 8Bh, 0Dh, 70h
    db 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 1Ch, 89h, 54h, 24h, 1Ch
    db 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch, 24h, 0E8h, 8Eh, 0C7h, 0A8h, 0FFh
    db 8Bh, 46h, 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 83h, 0E8h, 02h, 68h
    db 2Dh, 0CBh, 0FFh, 32h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 18h, 0DBh
    db 44h, 24h, 18h, 41h, 89h, 4Ch, 24h, 18h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch
    db 24h, 08h, 42h, 0DBh, 44h, 24h, 18h, 89h, 54h, 24h, 18h, 0D9h, 5Ch, 24h, 04h, 0DBh
    db 44h, 24h, 18h, 0D9h, 1Ch, 24h, 0E8h, 87h, 70h, 0A7h, 0FFh, 5Eh, 59h, 0C3h, 8Bh, 46h
    db 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 68h, 2Dh, 0CBh, 0FFh, 0FAh, 83h
    db 0E8h, 02h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h
    db 24h, 1Ch, 0DBh, 44h, 24h, 1Ch, 41h, 89h, 4Ch, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh
    db 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 1Ch, 89h, 54h, 24h, 1Ch, 0D9h, 5Ch
    db 24h, 04h, 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch, 24h, 0E8h, 0F0h, 0C6h, 0A8h, 0FFh, 8Bh, 46h
    db 18h, 0DBh, 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 83h, 0E8h, 02h, 68h, 2Dh, 0CBh
    db 0FFh, 19h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h
    db 18h, 41h, 89h, 4Ch, 24h, 18h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h
    db 42h, 0DBh, 44h, 24h, 18h, 89h, 54h, 24h, 18h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h
    db 18h, 0D9h, 1Ch, 24h, 0E8h, 0E9h, 6Fh, 0A7h, 0FFh, 5Eh, 59h, 0C3h, 8Bh, 46h, 18h, 0DBh
    db 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 68h, 2Dh, 0CBh, 0FFh, 0FAh, 83h, 0E8h, 02h
    db 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 1Ch
    db 0DBh, 44h, 24h, 1Ch, 41h, 89h, 4Ch, 24h, 1Ch, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h
    db 5Ch, 24h, 08h, 42h, 0DBh, 44h, 24h, 1Ch, 89h, 54h, 24h, 1Ch, 0D9h, 5Ch, 24h, 04h
    db 0DBh, 44h, 24h, 1Ch, 0D9h, 1Ch, 24h, 0E8h, 52h, 0C6h, 0A8h, 0FFh, 8Bh, 46h, 18h, 0DBh
    db 46h, 1Ch, 8Bh, 4Eh, 14h, 8Bh, 56h, 10h, 83h, 0E8h, 02h, 68h, 2Dh, 0CBh, 0FFh, 0Ah
    db 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h, 18h, 41h
    db 89h, 4Ch, 24h, 18h, 8Bh, 0Dh, 70h, 12h, 2Fh, 01h, 0D9h, 5Ch, 24h, 08h, 42h, 0DBh
    db 44h, 24h, 18h, 89h, 54h, 24h, 18h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 18h, 0D9h
    db 1Ch, 24h, 0E8h, 4Bh, 6Fh, 0A7h, 0FFh, 5Eh, 59h, 0C3h, 8Bh, 0FFh, 08h, 0CCh, 99h, 00h
    db 0A6h, 0CCh, 99h, 00h, 44h, 0CDh, 99h, 00h, 0E2h, 0CDh, 99h, 00h, 80h, 0CEh, 99h, 00h
    db 1Eh, 0CFh, 99h, 00h, 0BCh, 0CFh, 99h, 00h
?d_0059cbf0@@YAXXZ ENDP
_TEXT ENDS
END
