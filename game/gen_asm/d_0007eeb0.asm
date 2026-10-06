.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0INI@@QAE@XZ:NEAR
EXTERN ??1INI@@QAE@XZ:NEAR
EXTERN ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?StaticGameLODNames@@3PAPBDA:BYTE
EXTERN ?j_00001307@@YAXXZ:NEAR
EXTERN ?j_00003729@@YAXXZ:NEAR
EXTERN ?j_0000d53a@@YAXXZ:NEAR
EXTERN ?j_0001391c@@YAXXZ:NEAR
EXTERN ?j_0001bbf3@@YAXXZ:NEAR
EXTERN ?j_00023dad@@YAXXZ:NEAR
EXTERN ?j_00027a52@@YAXXZ:NEAR
EXTERN ?j_00028bb9@@YAXXZ:NEAR
EXTERN ?j_00030495@@YAXXZ:NEAR
EXTERN ?j_0003713C@@YAXXZ:NEAR
EXTERN ?j_0003da0f@@YAXXZ:NEAR
EXTERN ?j_0003e6da@@YAXXZ:NEAR
EXTERN ?j_000487fc@@YAXXZ:NEAR
EXTERN ?j_00049c65@@YAXXZ:NEAR
EXTERN ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN __imp_?bfmeFopenVIF@@YAPAXPBD0@Z:BYTE
EXTERN __imp__fclose:BYTE
EXTERN __imp__fprintf:BYTE
EXTERN g_Va00FF45F1:NEAR
EXTERN g_Va01076CA8:BYTE
EXTERN g_Va01076CE8:BYTE
EXTERN g_Va01076DC4:BYTE
EXTERN g_Va01076DE8:BYTE
EXTERN g_Va01076DF8:BYTE
EXTERN g_Va01076DFC:BYTE
EXTERN g_Va01076E00:BYTE
EXTERN g_Va01076E24:BYTE
EXTERN g_Va012A7418:BYTE
_TEXT SEGMENT

; retail @ 0x0007EEB0 size 1074
_TEXT ENDS
_TEXT$d0047eeb0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0047EEB0 size 1074
public ?d_0007eeb0@@YAXXZ
?d_0007eeb0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va00FF45F1
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 07Ch, 008h, 000h, 000h, 053h, 055h, 056h, 08Bh, 0F1h, 057h, 08Dh, 04Ch, 024h, 044h
    call ??0INI@@QAE@XZ
    db 06Ah, 000h, 06Ah, 001h, 051h, 089h, 064h, 024h, 028h, 08Bh, 0CCh, 068h
    dd g_Va01076E24
    db 0C7h, 084h, 024h, 0A4h, 008h, 000h, 000h, 000h, 000h, 000h, 000h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 050h
    call ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z
    db 06Ah, 000h, 06Ah, 001h, 051h, 089h, 064h, 024h, 028h, 08Bh, 0CCh, 068h
    dd g_Va01076E00
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 050h
    call ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z
    db 08Bh, 0CEh
    call ?j_00023dad@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch
    call ?j_0003713C@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C6h, 084h, 024h, 094h, 008h, 000h, 000h, 001h
    call ?j_00003729@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 089h, 044h, 024h, 01Ch
    call ?j_0000d53a@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 089h, 086h, 008h, 017h, 000h, 000h
    call ?j_0001bbf3@@YAXXZ
    db 083h, 0F8h, 0FFh, 089h, 086h, 0C4h, 016h, 000h, 000h, 075h, 05Fh, 083h, 0BEh, 008h, 017h, 000h
    db 000h, 0FFh, 074h, 056h, 068h
    dd g_Va01076CA8
    db 08Dh, 04Ch, 024h, 028h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 086h, 008h, 017h, 000h, 000h, 08Bh, 004h, 085h
    dd ?StaticGameLODNames@@3PAPBDA
    db 050h, 08Dh, 04Ch, 024h, 028h, 051h, 08Dh, 04Ch, 024h, 038h, 0C6h, 084h, 024h, 09Ch, 008h, 000h
    db 000h, 002h
    call ?j_0003e6da@@YAXXZ
    db 08Bh, 0C8h
    call ?j_00028bb9@@YAXXZ
    db 08Dh, 04Ch, 024h, 024h, 0C6h, 084h, 024h, 094h, 008h, 000h, 000h, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 096h, 008h, 017h, 000h, 000h, 089h, 096h, 0C4h, 016h, 000h, 000h, 08Dh, 04Ch, 024h, 02Ch
    call ?j_00027a52@@YAXXZ
    db 06Ah, 000h, 06Ah, 000h, 06Ah, 000h, 08Bh, 0D8h, 08Dh, 0BEh, 018h, 017h, 000h, 000h, 057h, 08Dh
    db 086h, 01Ch, 017h, 000h, 000h, 050h, 08Dh, 0AEh, 014h, 017h, 000h, 000h, 055h, 06Ah, 000h, 089h
    db 05Ch, 024h, 030h
    call ?j_0001391c@@YAXXZ
    db 0DBh, 007h, 083h, 0C4h, 01Ch, 0D8h, 00Dh
    dd g_Va01076DFC
    db 0D8h, 01Dh
    dd g_Va01076CE8
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 007h, 0C6h, 086h, 0EEh, 016h, 000h, 000h, 001h, 083h, 0BEh
    db 008h, 017h, 000h, 000h, 0FFh, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 074h, 013h, 08Ah, 088h, 0ACh, 00Ah, 000h, 000h, 084h, 0C9h, 075h, 009h, 083h, 0FBh, 0FFh, 00Fh
    db 085h, 0F1h, 001h, 000h, 000h, 083h, 07Dh, 000h, 000h, 074h, 00Eh, 08Ah, 088h, 0ACh, 00Ah, 000h
    db 000h, 084h, 0C9h, 00Fh, 084h, 0DDh, 001h, 000h, 000h, 08Dh, 086h, 028h, 017h, 000h, 000h, 050h
    db 08Dh, 0BEh, 024h, 017h, 000h, 000h, 057h, 08Dh, 09Eh, 020h, 017h, 000h, 000h, 053h, 06Ah, 000h
    db 06Ah, 000h, 06Ah, 000h, 06Ah, 000h
    call ?j_0001391c@@YAXXZ
    db 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Ah, 088h, 0ACh, 00Ah, 000h, 000h, 083h, 0C4h, 01Ch, 084h, 0C9h, 074h, 05Fh, 068h
    dd g_Va01076DF8
    db 068h
    dd g_Va01076DE8
    db 0FFh, 015h
    dd __imp_?bfmeFopenVIF@@YAPAXPBD0@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 089h, 044h, 024h, 018h, 074h, 044h, 0D9h, 086h, 028h, 017h, 000h
    db 000h, 08Bh, 08Eh, 01Ch, 017h, 000h, 000h, 08Bh, 055h, 000h, 083h, 0ECh, 018h, 0DDh, 05Ch, 024h
    db 010h, 0D9h, 007h, 0DDh, 05Ch, 024h, 008h, 0D9h, 003h, 0DDh, 01Ch, 024h, 051h, 08Bh, 00Ch, 095h
    dd g_Va012A7418
    db 051h, 068h
    dd g_Va01076DC4
    db 050h, 0FFh, 015h
    dd __imp__fprintf
    db 08Bh, 054h, 024h, 040h, 052h, 0FFh, 015h
    dd __imp__fclose
    db 083h, 0C4h, 02Ch, 0D9h, 003h, 08Bh, 086h, 004h, 017h, 000h, 000h, 085h, 0C0h, 0D8h, 007h, 08Dh
    db 08Eh, 080h, 015h, 000h, 000h, 0C7h, 044h, 024h, 020h, 001h, 000h, 000h, 000h, 0D9h, 09Eh, 02Ch
    db 017h, 000h, 000h, 089h, 04Ch, 024h, 010h, 0C7h, 045h, 000h, 001h, 000h, 000h, 000h, 0C7h, 086h
    db 01Ch, 017h, 000h, 000h, 0E8h, 003h, 000h, 000h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h
    db 00Fh, 08Eh, 003h, 001h, 000h, 000h, 0EBh, 00Bh, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Dh
    db 064h, 024h, 000h, 0D9h, 086h, 020h, 017h, 000h, 000h, 0D8h, 071h, 008h, 0D8h, 01Dh
    dd g_Va01076CE8
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 00Fh, 085h, 0BEh, 000h, 000h, 000h, 0D9h, 086h, 024h, 017h, 000h
    db 000h, 0D8h, 071h, 00Ch, 0D8h, 01Dh
    dd g_Va01076CE8
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 00Fh, 085h, 0A4h, 000h, 000h, 000h, 0D9h, 086h, 028h, 017h, 000h
    db 000h, 0D8h, 071h, 010h, 0D8h, 01Dh
    dd g_Va01076CE8
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 00Fh, 085h, 08Ah, 000h, 000h, 000h, 08Dh, 08Eh, 080h, 00Dh, 000h
    db 000h, 0BDh, 003h, 000h, 000h, 000h, 08Dh, 09Eh, 0FCh, 016h, 000h, 000h, 089h, 04Ch, 024h, 028h
    db 08Bh, 03Bh, 033h, 0D2h, 085h, 0FFh, 07Eh, 031h, 08Bh, 044h, 024h, 010h, 08Bh, 000h, 089h, 044h
    db 024h, 040h, 08Bh, 044h, 024h, 040h, 03Bh, 001h, 075h, 017h, 08Bh, 044h, 024h, 010h, 0DBh, 040h
    db 004h, 0DAh, 071h, 004h, 0D8h, 01Dh
    dd g_Va01076CE8
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 074h, 027h, 083h, 0C1h, 020h, 042h, 03Bh, 0D7h, 07Ch, 0D9h, 039h
    db 06Ch, 024h, 020h, 07Dh, 032h, 08Bh, 04Ch, 024h, 028h, 04Dh, 081h, 0E9h, 000h, 004h, 000h, 000h
    db 083h, 0EBh, 004h, 083h, 0FDh, 001h, 089h, 04Ch, 024h, 028h, 07Dh, 0AAh, 0EBh, 019h, 08Bh, 044h
    db 024h, 010h, 08Bh, 008h, 089h, 08Eh, 014h, 017h, 000h, 000h, 08Bh, 050h, 004h, 089h, 06Ch, 024h
    db 020h, 089h, 096h, 01Ch, 017h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 08Bh, 044h, 024h, 018h, 08Bh
    db 096h, 004h, 017h, 000h, 000h, 083h, 0C1h, 014h, 040h, 03Bh, 0C2h, 089h, 04Ch, 024h, 010h, 089h
    db 044h, 024h, 018h, 00Fh, 08Ch, 00Ah, 0FFh, 0FFh, 0FFh, 08Bh, 05Ch, 024h, 014h, 08Bh, 07Ch, 024h
    db 01Ch, 083h, 0FFh, 005h, 075h, 00Dh, 08Dh, 044h, 024h, 02Ch, 050h
    call ?j_000487fc@@YAXXZ
    db 083h, 0C4h, 004h, 057h, 08Bh, 0CEh
    call ?j_00049c65@@YAXXZ
    db 083h, 0FBh, 0FFh, 075h, 02Eh, 08Bh, 08Eh, 01Ch, 017h, 000h, 000h, 08Bh, 096h, 038h, 017h, 000h
    db 000h, 033h, 0C0h, 03Bh, 0CAh, 00Fh, 09Dh, 0C0h, 08Dh, 04Ch, 024h, 02Ch, 050h, 089h, 044h, 024h
    db 018h
    call ?j_0003da0f@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch
    call ?j_00030495@@YAXXZ
    db 08Bh, 05Ch, 024h, 014h, 085h, 0DBh, 07Ch, 025h, 083h, 0FBh, 002h, 07Dh, 020h, 039h, 09Eh, 0CCh
    db 016h, 000h, 000h, 074h, 018h, 089h, 09Eh, 0CCh, 016h, 000h, 000h, 08Bh, 00Dh
    dd ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A
    db 085h, 0C9h, 074h, 008h, 08Bh, 011h, 0FFh, 092h, 070h, 001h, 000h, 000h, 08Dh, 04Ch, 024h, 02Ch
    db 0C6h, 084h, 024h, 094h, 008h, 000h, 000h, 000h
    call ?j_00001307@@YAXXZ
    db 08Dh, 04Ch, 024h, 044h, 0C7h, 084h, 024h, 094h, 008h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1INI@@QAE@XZ
    db 08Bh, 08Ch, 024h, 08Ch, 008h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 088h, 008h, 000h, 000h, 0C3h
?d_0007eeb0@@YAXXZ ENDP
_TEXT$d0047eeb0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
