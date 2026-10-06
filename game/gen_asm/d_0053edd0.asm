.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?BFMEEmptyUnicodeString@@3GB:BYTE
EXTERN ?Data00EF49FC@@3PAVGen0000C955@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?j_000019f6@@YAXXZ:NEAR
EXTERN ?j_0001b720@@YAXXZ:NEAR
EXTERN ?j_0001c666@@YAXXZ:NEAR
EXTERN ?j_0002c7b4@@YAXXZ:NEAR
EXTERN ?j_0004b09c@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@G@@AAEXXZ:NEAR
EXTERN g_Va01031B28:NEAR
EXTERN g_Va01359364:BYTE
_TEXT SEGMENT

; retail @ 0x0053EDD0 size 864
_TEXT ENDS
_TEXT$d0093edd0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0093EDD0 size 864
public ?d_0053edd0@@YAXXZ
?d_0053edd0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01031B28
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 080h, 0D0h, 00Bh, 000h, 000h, 053h, 055h, 056h, 08Bh, 074h, 024h, 020h, 057h, 08Bh, 0BEh
    db 030h, 004h, 000h, 000h, 050h, 050h
    call ?j_000019f6@@YAXXZ
    db 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 083h, 0C4h, 008h, 03Bh, 0F8h, 075h, 012h, 08Bh, 086h, 034h, 004h, 000h, 000h, 03Bh, 081h, 0C8h
    db 00Bh, 000h, 000h, 075h, 004h, 032h, 0DBh, 0EBh, 002h, 0B3h, 001h, 08Bh, 081h, 0D0h, 00Bh, 000h
    db 000h, 08Bh, 07Ch, 024h, 028h, 08Bh, 0AFh, 030h, 004h, 000h, 000h, 050h, 050h
    call ?j_000019f6@@YAXXZ
    db 083h, 0C4h, 008h, 03Bh, 0E8h, 075h, 018h, 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 087h, 034h, 004h, 000h, 000h, 03Bh, 081h, 0C8h, 00Bh, 000h, 000h, 075h, 004h, 032h, 0C0h
    db 0EBh, 002h, 0B0h, 001h, 032h, 0C3h, 074h, 017h, 05Fh, 05Eh, 05Dh, 08Ah, 0C3h, 05Bh, 08Bh, 04Ch
    db 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 08Bh
    db 0CEh
    call ?j_0001c666@@YAXXZ
    db 08Bh, 0CEh, 08Bh, 0D8h
    call ?j_0001b720@@YAXXZ
    db 03Bh, 0D8h, 074h, 010h, 08Bh, 0CEh
    call ?j_0004b09c@@YAXXZ
    db 083h, 0F8h, 008h, 074h, 004h, 032h, 0DBh, 0EBh, 002h, 0B3h, 001h, 08Bh, 0CFh
    call ?j_0001c666@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0E8h
    call ?j_0001b720@@YAXXZ
    db 03Bh, 0E8h, 074h, 010h, 08Bh, 0CFh
    call ?j_0004b09c@@YAXXZ
    db 083h, 0F8h, 008h, 074h, 004h, 032h, 0C0h, 0EBh, 002h, 0B0h, 001h, 08Ah, 0D0h, 032h, 0D3h, 00Fh
    db 085h, 0A1h, 001h, 000h, 000h, 08Dh, 044h, 024h, 010h, 050h, 08Bh, 0CFh
    call ?j_0002c7b4@@YAXXZ
    db 08Bh, 0D8h, 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 0CEh, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h
    db 000h
    call ?j_0002c7b4@@YAXXZ
    db 08Bh, 00Bh, 085h, 0C9h, 074h, 005h, 083h, 0C1h, 008h, 0EBh, 005h, 0B9h
    dd ?BFMEEmptyUnicodeString@@3GB
    db 08Bh, 000h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?BFMEEmptyUnicodeString@@3GB
    db 051h, 050h, 0FFh, 015h
    dd g_Va01359364
    db 083h, 0C4h, 008h, 08Dh, 04Ch, 024h, 028h, 089h, 044h, 024h, 024h
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Dh, 04Ch, 024h, 010h, 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 09Eh, 04Ch, 004h, 000h, 000h, 08Bh, 0AFh, 04Ch, 004h, 000h, 000h, 08Bh, 0CEh, 02Bh, 0DDh
    call ?j_0001c666@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0E8h
    call ?j_0001c666@@YAXXZ
    db 08Bh, 0CEh, 02Bh, 0E8h
    call ?j_0001b720@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0F0h
    call ?j_0001b720@@YAXXZ
    db 08Bh, 03Dh
    dd ?Data00EF49FC@@3PAVGen0000C955@@A
    db 02Bh, 0F0h, 085h, 0FFh, 075h, 020h, 08Bh, 04Ch, 024h, 024h, 05Fh, 05Eh, 033h, 0C0h, 085h, 0C9h
    db 05Dh, 00Fh, 09Fh, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 010h, 0C2h, 008h, 000h, 08Bh, 087h, 0E8h, 001h, 000h, 000h, 0C7h, 044h, 024h, 028h
    db 000h, 000h, 000h, 000h, 0EBh, 009h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 0FFh, 08Bh
    db 0D0h, 081h, 0E2h, 000h, 000h, 001h, 000h, 081h, 0FAh, 000h, 000h, 001h, 000h, 00Fh, 094h, 0C1h
    db 025h, 0FFh, 0FFh, 0FEh, 0FFh, 048h, 083h, 0F8h, 007h, 00Fh, 087h, 087h, 000h, 000h, 000h, 0FFh
    db 024h, 085h
    dd ?d_0053edd0@@YAXXZ + 0340h
    db 08Bh, 054h, 024h, 024h, 085h, 0D2h, 074h, 078h, 033h, 0C0h, 084h, 0C9h, 00Fh, 084h, 09Dh, 000h
    db 000h, 000h, 05Fh, 05Eh, 085h, 0D2h, 05Dh, 00Fh, 09Fh, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 085h, 0EDh, 074h, 050h
    db 033h, 0C0h, 084h, 0C9h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 05Fh, 05Eh, 085h, 0EDh, 05Dh, 00Fh
    db 09Fh, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 010h, 0C2h, 008h, 000h, 085h, 0DBh, 074h, 028h, 033h, 0C0h, 084h, 0C9h, 00Fh, 084h, 081h, 000h
    db 000h, 000h, 05Fh, 05Eh, 085h, 0DBh, 05Dh, 00Fh, 09Fh, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 085h, 0F6h, 075h, 07Dh
    db 08Bh, 04Ch, 024h, 028h, 08Bh, 087h, 0ECh, 001h, 000h, 000h, 041h, 083h, 0F9h, 002h, 089h, 04Ch
    db 024h, 028h, 00Fh, 08Ch, 041h, 0FFh, 0FFh, 0FFh, 0B0h, 001h, 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch
    db 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 05Fh
    db 05Eh, 085h, 0D2h, 05Dh, 00Fh, 09Ch, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 05Fh, 05Eh, 085h, 0EDh, 05Dh, 00Fh, 09Ch
    db 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h
    db 0C2h, 008h, 000h, 05Fh, 05Eh, 085h, 0DBh, 05Dh, 00Fh, 09Ch, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 033h, 0C0h, 084h
    db 0C9h, 074h, 01Ah, 05Fh, 085h, 0F6h, 05Eh, 05Dh, 00Fh, 09Fh, 0C0h, 05Bh, 08Bh, 04Ch, 024h, 004h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 08Bh, 04Ch, 024h
    db 014h, 05Fh, 085h, 0F6h, 05Eh, 05Dh, 00Fh, 09Ch, 0C0h, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h, 08Bh, 0FFh
    dd ?d_0053edd0@@YAXXZ + 0207h
    dd ?d_0053edd0@@YAXXZ + 0233h
    dd ?d_0053edd0@@YAXXZ + 0287h
    dd ?d_0053edd0@@YAXXZ + 025Bh
    dd ?d_0053edd0@@YAXXZ + 0287h
    dd ?d_0053edd0@@YAXXZ + 0287h
    dd ?d_0053edd0@@YAXXZ + 0287h
    dd ?d_0053edd0@@YAXXZ + 0283h
?d_0053edd0@@YAXXZ ENDP
_TEXT$d0093edd0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
