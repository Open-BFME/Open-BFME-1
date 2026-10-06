.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??1UserPreferences@@UAE@XZ:NEAR
EXTERN ?format@AsciiString@@QAAXV1@ZZ:NEAR
EXTERN ?j_00014308@@YAXXZ:NEAR
EXTERN ?j_00030495@@YAXXZ:NEAR
EXTERN ?j_00049e13@@YAXXZ:NEAR
EXTERN ?j_0004b19b@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN g_Va01042D20:NEAR
EXTERN g_Va01100C74:BYTE
_TEXT SEGMENT

; retail @ 0x00654D20 size 239
_TEXT ENDS
_TEXT$d00a54d20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00A54D20 size 239
public ?d_00654d20@@YAXXZ
?d_00654d20@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01042D20
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 018h, 053h, 056h, 08Bh, 074h, 024h
    db 048h, 033h, 0DBh, 03Bh, 0F3h, 00Fh, 084h, 0B6h, 000h, 000h, 000h, 039h, 05Ch, 024h, 040h, 00Fh
    db 084h, 0A9h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 00Ch
    call ?j_0004b19b@@YAXXZ
    db 089h, 05Ch, 024h, 028h, 089h, 05Ch, 024h, 048h, 08Bh, 044h, 024h, 034h, 050h, 051h, 089h, 064h
    db 024h, 010h, 08Bh, 0CCh, 068h
    dd g_Va01100C74
    db 0C6h, 044h, 024h, 034h, 001h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 050h, 051h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 008h, 08Dh, 054h, 024h, 04Ch, 089h, 064h, 024h, 00Ch, 08Bh, 0CCh, 052h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Dh, 04Ch, 024h, 010h
    call ?j_00014308@@YAXXZ
    db 039h, 05Ch, 024h, 014h, 074h, 02Ah, 08Bh, 044h, 024h, 010h, 08Bh, 048h, 004h, 051h, 08Dh, 04Ch
    db 024h, 014h
    call ?j_00049e13@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 089h, 040h, 008h, 08Bh, 054h, 024h, 010h, 089h, 05Ah, 004h, 08Bh, 044h
    db 024h, 010h, 089h, 040h, 00Ch, 089h, 05Ch, 024h, 014h, 08Dh, 04Ch, 024h, 00Ch
    call ?j_00030495@@YAXXZ
    db 08Dh, 04Ch, 024h, 048h, 088h, 05Ch, 024h, 028h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 00Ch, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1UserPreferences@@UAE@XZ
    db 0FFh, 04Eh, 054h, 08Bh, 04Ch, 024h, 020h, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh
    db 083h, 0C4h, 024h, 0C3h
?d_00654d20@@YAXXZ ENDP
_TEXT$d00a54d20 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
