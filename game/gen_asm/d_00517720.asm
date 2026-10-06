.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ?EngineGlobal007629F0@@3PAUEngine007629F0@@A:BYTE
EXTERN ?R2Ptr012F19E8@@3PAVGen000290D2@@A:BYTE
EXTERN ?TheChallengeGenerals@@3PAVChallengeGenerals@@A:BYTE
EXTERN ?TheGameState@@3PAURva0075B660State@@A:BYTE
EXTERN ?TheGameText@@3PAVBfmeGameText@@A:BYTE
EXTERN ?TheShell@@3PAVBfmeShell@@A:BYTE
EXTERN ?j_0000b460@@YAXXZ:NEAR
EXTERN ?j_0000bd7f@@YAXXZ:NEAR
EXTERN ?j_00015235@@YAXXZ:NEAR
EXTERN ?j_0002bbe8@@YAXXZ:NEAR
EXTERN ?j_000316c4@@YAXXZ:NEAR
EXTERN ?j_00042366@@YAXXZ:NEAR
EXTERN ?j_000428ed@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN g_Va0102FBC0:NEAR
EXTERN g_Va010EDB20:BYTE
EXTERN g_Va01106208:BYTE
EXTERN g_Va01106218:BYTE
EXTERN g_Va01106238:BYTE
EXTERN g_Va01106258:BYTE
EXTERN g_Va01106274:BYTE
_TEXT SEGMENT

; retail @ 0x00517720 size 268
public ?d_00517720@@YAXXZ
?d_00517720@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 81h, 0F3h, 02h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 68h, 68h, 58h, 10h, 01h, 8Dh, 4Ch, 24h
    db 04h, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 72h, 14h, 37h, 00h, 8Bh, 44h
    db 24h, 1Ch, 83h, 0F8h, 0Bh, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 77h, 62h, 0FFh
    db 24h, 85h, 0FCh, 77h, 91h, 00h, 68h, 5Ch, 58h, 10h, 01h, 0EBh, 4Bh, 68h, 48h, 58h
    db 10h, 01h, 0EBh, 44h, 68h, 2Ch, 58h, 10h, 01h, 0EBh, 3Dh, 68h, 14h, 58h, 10h, 01h
    db 0EBh, 36h, 68h, 0F8h, 57h, 10h, 01h, 0EBh, 2Fh, 68h, 0DCh, 57h, 10h, 01h, 0EBh, 28h
    db 68h, 0C4h, 57h, 10h, 01h, 0EBh, 21h, 68h, 0A8h, 57h, 10h, 01h, 0EBh, 1Ah, 68h, 90h
    db 57h, 10h, 01h, 0EBh, 13h, 68h, 7Ch, 57h, 10h, 01h, 0EBh, 0Ch, 68h, 64h, 57h, 10h
    db 01h, 0EBh, 05h, 68h, 50h, 57h, 10h, 01h, 8Dh, 4Ch, 24h, 04h, 0E8h, 0F8h, 13h, 0B1h
    db 0FFh, 56h, 8Bh, 74h, 24h, 1Ch, 8Dh, 44h, 24h, 04h, 50h, 8Bh, 0CEh, 0E8h, 8Eh, 03h
    db 37h, 00h, 8Dh, 4Ch, 24h, 04h, 0C7h, 44h, 24h, 08h, 01h, 00h, 00h, 00h, 0C6h, 44h
    db 24h, 14h, 00h, 0E8h, 58h, 01h, 37h, 00h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 0C6h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h, 8Bh, 0FFh, 66h, 77h, 91h, 00h
    db 6Dh, 77h, 91h, 00h, 74h, 77h, 91h, 00h, 7Bh, 77h, 91h, 00h, 82h, 77h, 91h, 00h
    db 89h, 77h, 91h, 00h, 90h, 77h, 91h, 00h, 97h, 77h, 91h, 00h, 9Eh, 77h, 91h, 00h
    db 0A5h, 77h, 91h, 00h, 0ACh, 77h, 91h, 00h, 0B3h, 77h, 91h, 00h
?d_00517720@@YAXXZ ENDP

; retail @ 0x0051D700 size 484
_TEXT ENDS
_TEXT$d0091d700 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0091D700 size 484
public ?d_0051d700@@YAXXZ
?d_0051d700@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va0102FBC0
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 00Ch, 053h, 056h, 08Bh, 0F1h, 08Bh
    db 086h, 064h, 002h, 000h, 000h, 048h, 083h, 0F8h, 005h, 00Fh, 087h, 088h, 001h, 000h, 000h, 0FFh
    db 024h, 085h
    dd ?d_0051d700@@YAXXZ + 01CCh
    db 08Bh, 00Dh
    dd ?TheShell@@3PAVBfmeShell@@A
    db 06Ah, 001h
    call ?j_000428ed@@YAXXZ
    db 068h
    dd g_Va010EDB20
    db 08Dh, 04Ch, 024h, 00Ch
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheGameState@@3PAURva0075B660State@@A
    db 08Dh, 044h, 024h, 008h, 050h, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h
    call ?j_000316c4@@YAXXZ
    db 085h, 0C0h, 08Dh, 04Ch, 024h, 008h, 00Fh, 095h, 0C3h, 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh
    db 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 084h, 0DBh, 074h, 03Bh, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 08Bh, 011h, 0FFh, 052h, 010h, 08Bh, 00Dh
    dd ?TheShell@@3PAVBfmeShell@@A
    db 06Ah, 001h
    call ?j_00042366@@YAXXZ
    db 0C6h, 086h, 059h, 002h, 000h, 000h, 000h, 0C7h, 086h, 064h, 002h, 000h, 000h, 000h, 000h, 000h
    db 000h, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 06Ah, 000h
    call ?j_0000bd7f@@YAXXZ
    db 0E9h, 0F9h, 000h, 000h, 000h, 0C7h, 086h, 064h, 002h, 000h, 000h, 002h, 000h, 000h, 000h, 0E9h
    db 0EAh, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?TheChallengeGenerals@@3PAVChallengeGenerals@@A
    db 085h, 0C9h, 00Fh, 084h, 0DCh, 000h, 000h, 000h, 08Bh, 001h, 0FFh, 050h, 014h, 08Bh, 00Dh
    dd ?TheChallengeGenerals@@3PAVChallengeGenerals@@A
    db 08Ah, 041h, 030h, 084h, 0C0h, 00Fh, 084h, 0C6h, 000h, 000h, 000h, 08Bh, 096h, 050h, 002h, 000h
    db 000h, 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 068h
    dd g_Va01106274
    db 052h
    call ?j_00015235@@YAXXZ
    db 0E9h, 09Eh, 000h, 000h, 000h, 08Dh, 08Eh, 068h, 002h, 000h, 000h
    call ?j_0000b460@@YAXXZ
    db 08Bh, 00Dh
    dd ?R2Ptr012F19E8@@3PAVGen000290D2@@A
    db 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 084h, 0C0h, 08Bh, 086h, 050h, 002h, 000h, 000h, 06Ah, 000h
    db 075h, 05Fh, 06Ah, 000h, 06Ah, 000h, 068h
    dd g_Va01106258
    db 050h
    call ?j_00015235@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 001h, 06Ah, 000h, 051h, 08Bh, 0D4h, 089h, 064h, 024h, 014h, 06Ah, 000h, 068h
    dd g_Va01106238
    db 052h, 0FFh, 050h, 028h, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 001h, 051h, 08Bh, 0D4h, 089h, 064h, 024h, 01Ch, 06Ah, 000h, 068h
    dd g_Va01106218
    db 052h, 0C7h, 044h, 024h, 034h, 001h, 000h, 000h, 000h, 0FFh, 050h, 028h, 0C7h, 044h, 024h, 028h
    db 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_0002bbe8@@YAXXZ
    db 083h, 0C4h, 00Ch, 0EBh, 012h, 068h
    dd g_Va01106208
    db 06Ah, 001h, 068h
    dd g_Va01106258
    db 050h
    call ?j_00015235@@YAXXZ
    db 0C7h, 086h, 064h, 002h, 000h, 000h, 000h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 014h, 05Eh, 0B8h
    db 001h, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 018h, 0C3h
    db 08Bh, 0FFh
    dd ?d_0051d700@@YAXXZ + 033h
    dd ?d_0051d700@@YAXXZ + 01B4h
    dd ?d_0051d700@@YAXXZ + 01B4h
    dd ?d_0051d700@@YAXXZ + 0CAh
    dd ?d_0051d700@@YAXXZ + 0116h
    dd ?d_0051d700@@YAXXZ + 01AAh
?d_0051d700@@YAXXZ ENDP
_TEXT$d0091d700 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
