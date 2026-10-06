.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?TheUpgradeCenter@@3PAVBfmeThingND@@A:BYTE
EXTERN ?bfmeAdd1095@BfmeR1095@@QAEXPAUBfmeZ1095B@@H@Z:NEAR
EXTERN ?j_0000315c@@YAXXZ:NEAR
EXTERN ?j_00003f58@@YAXXZ:NEAR
EXTERN ?j_0000d0a8@@YAXXZ:NEAR
EXTERN ?j_0000e4e4@@YAXXZ:NEAR
EXTERN ?j_0000e570@@YAXXZ:NEAR
EXTERN ?j_0001336d@@YAXXZ:NEAR
EXTERN ?j_00015474@@YAXXZ:NEAR
EXTERN ?j_000170da@@YAXXZ:NEAR
EXTERN ?j_00017c2e@@YAXXZ:NEAR
EXTERN ?j_0001e20e@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_00020455@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_000233ee@@YAXXZ:NEAR
EXTERN ?j_00024d70@@YAXXZ:NEAR
EXTERN ?j_00026ab2@@YAXXZ:NEAR
EXTERN ?j_00028772@@YAXXZ:NEAR
EXTERN ?j_000298c0@@YAXXZ:NEAR
EXTERN ?j_0002F95A@@YAXXZ:NEAR
EXTERN ?j_0002b9d1@@YAXXZ:NEAR
EXTERN ?j_0002e85c@@YAXXZ:NEAR
EXTERN ?j_0002edcf@@YAXXZ:NEAR
EXTERN ?j_0002fc7a@@YAXXZ:NEAR
EXTERN ?j_00030ea4@@YAXXZ:NEAR
EXTERN ?j_00031a7f@@YAXXZ:NEAR
EXTERN ?j_00031f7a@@YAXXZ:NEAR
EXTERN ?j_0003436a@@YAXXZ:NEAR
EXTERN ?j_000346a3@@YAXXZ:NEAR
EXTERN ?j_00037376@@YAXXZ:NEAR
EXTERN ?j_0003a4e5@@YAXXZ:NEAR
EXTERN ?j_0003af7b@@YAXXZ:NEAR
EXTERN ?j_0003bff7@@YAXXZ:NEAR
EXTERN ?j_0003c740@@YAXXZ:NEAR
EXTERN ?j_00040642@@YAXXZ:NEAR
EXTERN ?j_00040732@@YAXXZ:NEAR
EXTERN ?j_00043464@@YAXXZ:NEAR
EXTERN ?j_00043f45@@YAXXZ:NEAR
EXTERN ?j_000443e1@@YAXXZ:NEAR
EXTERN ?j_00044774@@YAXXZ:NEAR
EXTERN ?j_000487f2@@YAXXZ:NEAR
EXTERN ?j_00049413@@YAXXZ:NEAR
EXTERN ?j_0004a0d9@@YAXXZ:NEAR
EXTERN __real@3e19999a:BYTE
EXTERN __real@43960000:BYTE
EXTERN g_Va0100F838:NEAR
EXTERN g_Va010132CB:NEAR
EXTERN g_Va010B61D4:BYTE
EXTERN g_Va010B61EC:BYTE
EXTERN g_Va010B6204:BYTE
EXTERN g_Va010B6220:BYTE
_TEXT SEGMENT

; retail @ 0x002632F0 size 988
_TEXT ENDS
_TEXT$d006632f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x006632F0 size 988
public ?d_002632f0@@YAXXZ
?d_002632f0@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va0100F838
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 068h, 053h, 055h, 056h, 057h, 08Bh
    db 0F9h, 08Bh, 047h, 0F8h, 08Bh, 088h, 0A4h, 001h, 000h, 000h, 085h, 0C9h, 00Fh, 085h, 075h, 003h
    db 000h, 000h, 08Bh, 0B4h, 024h, 088h, 000h, 000h, 000h, 085h, 0F6h, 00Fh, 084h, 066h, 003h, 000h
    db 000h, 08Bh, 084h, 024h, 08Ch, 000h, 000h, 000h, 050h, 056h, 08Bh, 0CFh
    call ?j_000170da@@YAXXZ
    db 08Dh, 04Fh, 0F0h
    call ?j_0003af7b@@YAXXZ
    db 08Bh, 0D8h, 08Bh, 047h, 0F4h, 089h, 044h, 024h, 010h, 08Bh, 080h, 020h, 002h, 000h, 000h, 083h
    db 0F8h, 007h, 00Fh, 087h, 0A9h, 002h, 000h, 000h, 0FFh, 024h, 085h
    dd ?d_002632f0@@YAXXZ + 03BCh
    db 08Bh, 047h, 0F8h, 083h, 0C0h, 038h, 050h, 08Dh, 044h, 024h, 03Ch, 0EBh, 04Bh, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 056h, 08Dh, 044h, 024h, 048h, 050h, 0FFh, 052h, 034h, 08Bh, 008h, 089h, 04Ch, 024h
    db 014h, 08Bh, 050h, 004h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 089h, 054h, 024h, 018h, 08Bh, 040h, 008h, 08Dh, 054h, 024h, 014h, 089h, 044h, 024h, 01Ch, 08Bh
    db 049h, 00Ch, 052h
    call ?j_0000e4e4@@YAXXZ
    db 06Ah, 000h, 06Ah, 000h, 08Dh, 04Ch, 024h, 01Ch, 051h, 0E9h, 042h, 002h, 000h, 000h, 056h, 08Dh
    db 044h, 024h, 054h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 050h, 0FFh, 052h, 034h, 08Bh, 008h, 089h, 04Ch, 024h, 014h, 08Bh, 050h, 004h, 08Bh
    db 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 089h, 054h, 024h, 018h, 08Bh, 040h, 008h, 08Dh, 054h, 024h, 014h, 089h, 044h, 024h, 01Ch, 08Bh
    db 049h, 00Ch, 052h
    call ?j_0000e4e4@@YAXXZ
    db 06Ah, 000h, 056h, 08Dh, 04Ch, 024h, 01Ch, 051h, 0E9h, 0FDh, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 056h, 08Dh, 044h, 024h, 060h, 050h, 0FFh, 052h, 038h, 08Bh, 008h, 089h, 04Ch, 024h
    db 014h, 08Bh, 050h, 004h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 089h, 054h, 024h, 018h, 08Bh, 040h, 008h, 089h, 044h, 024h, 01Ch, 0D9h, 044h, 024h, 01Ch, 0D8h
    db 005h
    dd __real@43960000
    db 08Dh, 054h, 024h, 014h, 052h, 0D9h, 05Ch, 024h, 020h, 08Bh, 049h, 00Ch
    call ?j_0000e4e4@@YAXXZ
    db 06Ah, 000h, 056h, 08Dh, 04Ch, 024h, 01Ch, 051h, 0E9h, 0AAh, 001h, 000h, 000h, 08Bh, 016h, 08Bh
    db 046h, 004h, 08Bh, 04Eh, 008h, 06Ah, 000h, 089h, 054h, 024h, 018h, 089h, 044h, 024h, 01Ch, 089h
    db 04Ch, 024h, 020h, 06Ah, 000h, 0E9h, 088h, 001h, 000h, 000h, 08Bh, 04Eh, 004h, 08Bh, 006h, 08Bh
    db 056h, 008h, 06Ah, 000h, 06Ah, 000h, 089h, 04Ch, 024h, 020h, 056h, 08Dh, 04Ch, 024h, 020h, 089h
    db 044h, 024h, 020h, 08Bh, 047h, 0F8h, 051h, 050h, 053h, 089h, 054h, 024h, 034h
    call ?j_000443e1@@YAXXZ
    db 083h, 0C4h, 018h, 0E9h, 06Ah, 001h, 000h, 000h, 08Bh, 016h, 08Bh, 046h, 004h, 08Bh, 04Eh, 008h
    db 06Ah, 000h, 089h, 054h, 024h, 018h, 089h, 044h, 024h, 01Ch, 06Ah, 000h, 0E9h, 02Dh, 001h, 000h
    db 000h, 051h, 089h, 0A4h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0CCh, 068h
    dd g_Va010B6220
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 001h, 0FFh, 050h, 07Ch, 051h, 089h, 0A4h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0CCh, 068h
    dd g_Va010B6204
    db 089h, 044h, 024h, 070h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 0FFh, 052h, 07Ch, 051h, 089h, 0A4h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0CCh, 068h
    dd g_Va010B61EC
    db 089h, 044h, 024h, 074h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 001h, 0FFh, 050h, 07Ch, 051h, 089h, 0A4h, 024h, 08Ch, 000h, 000h, 000h, 08Bh, 0CCh, 068h
    dd g_Va010B61D4
    db 089h, 044h, 024h, 078h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 0FFh, 052h, 07Ch, 089h, 044h, 024h, 074h, 0C7h, 084h, 024h, 08Ch, 000h, 000h, 000h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0C7h, 084h, 024h, 088h, 000h, 000h, 000h, 080h, 04Fh, 0C3h, 047h, 033h
    db 0EDh, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 044h, 0ACh, 068h, 085h, 0C0h, 074h, 050h, 0D9h
    db 040h, 00Ch, 08Dh, 04Ch, 024h, 02Ch, 0D9h, 040h, 010h, 08Bh, 040h, 014h, 0D9h, 0C9h, 089h, 044h
    db 024h, 034h, 0D8h, 026h, 0D9h, 05Ch, 024h, 02Ch, 0D8h, 066h, 004h, 0D9h, 05Ch, 024h, 030h, 0D9h
    db 044h, 024h, 034h, 0D8h, 066h, 008h, 0D9h, 05Ch, 024h, 034h
    call ?j_00043464@@YAXXZ
    db 0D8h, 094h, 024h, 088h, 000h, 000h, 000h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 010h, 0D9h, 09Ch
    db 024h, 088h, 000h, 000h, 000h, 089h, 0ACh, 024h, 08Ch, 000h, 000h, 000h, 0EBh, 002h, 0DDh, 0D8h
    db 045h, 083h, 0FDh, 004h, 07Ch, 0A2h, 08Bh, 084h, 024h, 08Ch, 000h, 000h, 000h, 085h, 0C0h, 07Ch
    db 03Eh, 08Bh, 04Ch, 084h, 068h, 083h, 0C1h, 00Ch, 08Bh, 011h, 089h, 054h, 024h, 014h, 08Bh, 041h
    db 004h, 06Ah, 000h, 089h, 044h, 024h, 01Ch, 08Bh, 049h, 008h, 056h, 089h, 04Ch, 024h, 024h, 0D9h
    db 044h, 024h, 024h, 0D8h, 005h
    dd __real@43960000
    db 0D9h, 05Ch, 024h, 024h, 08Dh, 054h, 024h, 01Ch, 052h, 08Bh, 047h, 0F8h, 050h, 053h
    call ?j_00037376@@YAXXZ
    db 083h, 0C4h, 014h, 08Bh, 044h, 024h, 010h, 005h, 024h, 002h, 000h, 000h, 050h, 08Dh, 04Ch, 024h
    db 024h
    call ?j_00015474@@YAXXZ
    db 08Bh, 04Ch, 024h, 024h, 08Bh, 044h, 024h, 020h, 02Bh, 0C8h, 0C1h, 0F9h, 002h, 033h, 0DBh, 085h
    db 0C9h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 076h, 048h, 0EBh, 006h
    db 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?TheUpgradeCenter@@3PAVBfmeThingND@@A
    db 08Dh, 014h, 098h, 052h
    call ?j_0002F95A@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 02Bh, 08Bh, 046h, 004h, 085h, 0C0h, 075h, 012h, 08Bh, 04Fh, 0F8h
    call ?j_00020824@@YAXXZ
    db 06Ah, 002h, 056h, 08Bh, 0C8h
    call ?bfmeAdd1095@BfmeR1095@@QAEXPAUBfmeZ1095B@@H@Z
    db 08Bh, 04Ch, 024h, 024h, 08Bh, 044h, 024h, 020h, 02Bh, 0C8h, 043h, 0C1h, 0F9h, 002h, 03Bh, 0D9h
    db 072h, 0C0h, 08Dh, 04Ch, 024h, 020h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh
    db 0FFh
    call ?j_00026ab2@@YAXXZ
    db 08Bh, 04Ch, 024h, 078h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 074h, 0C2h, 008h, 000h, 08Dh, 049h, 000h
    dd ?d_002632f0@@YAXXZ + 075h
    dd ?d_002632f0@@YAXXZ + 082h
    dd ?d_002632f0@@YAXXZ + 0C8h
    dd ?d_002632f0@@YAXXZ + 0160h
    dd ?d_002632f0@@YAXXZ + 017Dh
    dd ?d_002632f0@@YAXXZ + 01ADh
    dd ?d_002632f0@@YAXXZ + 010Dh
    dd ?d_002632f0@@YAXXZ + 01C6h
?d_002632f0@@YAXXZ ENDP
_TEXT$d006632f0 ENDS
_TEXT SEGMENT

; retail @ 0x00266F40 size 704
_TEXT ENDS
_TEXT$d00666f40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00666F40 size 704
public ?d_00266f40@@YAXXZ
?d_00266f40@@YAXXZ PROC
    db 083h, 0ECh, 020h, 055h, 056h, 08Bh, 0F1h, 08Bh, 06Eh, 0F8h, 0F6h, 085h, 044h, 003h, 000h, 000h
    db 001h, 074h, 01Fh, 055h
    call ?j_0002fc7a@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h
    call ?j_0003c740@@YAXXZ
    db 05Eh, 0B8h, 0FFh, 0FFh, 0FFh, 03Fh, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Bh, 046h, 028h, 085h, 0C0h
    db 074h, 0EEh, 08Ah, 046h, 060h, 084h, 0C0h, 074h, 019h, 06Ah, 004h, 08Dh, 04Eh, 0F0h
    call ?j_000298c0@@YAXXZ
    db 0C6h, 046h, 060h, 000h, 05Eh, 0B8h, 001h, 000h, 000h, 000h, 05Dh, 083h, 0C4h, 020h, 0C3h, 057h
    db 08Bh, 0BDh, 004h, 002h, 000h, 000h, 085h, 0FFh, 075h, 014h, 08Dh, 04Eh, 0F0h
    call ?j_00040642@@YAXXZ
    db 05Fh, 05Eh, 0B8h, 0FFh, 0FFh, 0FFh, 03Fh, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Bh, 045h, 000h, 08Bh
    db 0CDh, 0FFh, 050h, 028h, 085h, 0C0h, 074h, 0E8h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 092h, 080h, 001h
    db 000h, 000h, 084h, 0C0h, 075h, 00Fh, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 090h, 000h, 002h, 000h, 000h
    db 083h, 0F8h, 002h, 075h, 0C3h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 092h, 080h, 001h, 000h, 000h, 084h
    db 0C0h, 074h, 00Eh, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 090h, 000h, 002h, 000h, 000h, 085h, 0C0h, 074h
    db 0A7h, 08Bh, 046h, 030h, 053h, 033h, 0DBh, 085h, 0C0h, 074h, 032h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0D8h, 085h, 0DBh, 074h, 009h, 0F6h, 083h, 044h, 003h, 000h, 000h, 001h, 074h, 021h, 08Bh
    db 046h, 028h, 033h, 0DBh, 083h, 0F8h, 003h, 089h, 05Eh, 030h, 075h, 00Ah, 06Ah, 004h, 08Dh, 04Eh
    db 0F0h
    call ?j_000298c0@@YAXXZ
    db 06Ah, 004h, 08Dh, 04Eh, 0F0h
    call ?j_000298c0@@YAXXZ
    db 08Bh, 046h, 028h, 083h, 0F8h, 004h, 00Fh, 087h, 08Dh, 001h, 000h, 000h, 0FFh, 024h, 085h
    dd ?d_00266f40@@YAXXZ + 02ACh
    db 06Ah, 03Fh, 08Bh, 0CBh
    call ?j_00031f7a@@YAXXZ
    db 05Bh, 05Fh, 05Eh, 0B8h, 0FFh, 0FFh, 0FFh, 03Fh, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Bh, 045h, 040h
    db 08Bh, 04Dh, 038h, 08Bh, 055h, 03Ch, 089h, 044h, 024h, 020h, 08Dh, 046h, 054h, 089h, 04Ch, 024h
    db 018h, 050h, 08Dh, 04Ch, 024h, 01Ch, 089h, 054h, 024h, 020h, 089h, 044h, 024h, 018h
    call ?j_000233ee@@YAXXZ
    db 08Dh, 04Ch, 024h, 018h, 051h, 08Bh, 0CDh
    call ?j_00049413@@YAXXZ
    db 0D9h, 0E1h, 0D8h, 01Dh
    dd __real@3e19999a
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 051h, 053h, 08Bh, 0CDh
    call ?j_0001e20e@@YAXXZ
    db 084h, 0C0h, 075h, 00Eh, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 092h, 080h, 001h, 000h, 000h, 084h, 0C0h
    db 074h, 037h, 055h
    call ?j_0002fc7a@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 074h, 02Ah, 08Bh, 0C8h, 06Ah, 000h
    call ?j_0003bff7@@YAXXZ
    db 084h, 0C0h, 074h, 01Dh, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 090h, 0E8h, 001h, 000h, 000h, 06Ah, 002h
    db 06Ah, 000h, 08Dh, 04Fh, 020h
    call ?j_0001336d@@YAXXZ
    db 06Ah, 002h, 0E9h, 0D6h, 000h, 000h, 000h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 092h, 080h, 001h, 000h
    db 000h, 084h, 0C0h, 00Fh, 084h, 0CCh, 000h, 000h, 000h, 053h, 08Bh, 0CFh
    call ?j_0000315c@@YAXXZ
    db 08Ah, 056h, 050h, 084h, 0D2h, 00Fh, 094h, 0C0h, 084h, 0C0h, 088h, 046h, 050h, 074h, 052h, 08Bh
    db 04Ch, 024h, 014h, 08Dh, 044h, 024h, 013h, 050h, 051h, 053h, 08Dh, 054h, 024h, 030h, 052h, 08Dh
    db 04Eh, 0F0h, 0C6h, 044h, 024h, 023h, 000h
    call ?j_00020455@@YAXXZ
    db 08Dh, 04Eh, 044h, 08Bh, 030h, 08Bh, 0D1h, 089h, 032h, 08Bh, 070h, 004h, 089h, 072h, 004h, 08Bh
    db 040h, 008h, 089h, 042h, 008h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 074h, 07Bh, 06Ah, 002h, 051h
    db 08Dh, 04Fh, 020h
    call ?j_0003436a@@YAXXZ
    db 05Bh, 05Fh, 05Eh, 0B8h, 001h, 000h, 000h, 000h, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Bh, 04Dh, 038h
    db 08Bh, 055h, 03Ch, 08Bh, 045h, 040h, 089h, 04Ch, 024h, 018h, 08Bh, 04Ch, 024h, 014h, 051h, 08Dh
    db 04Ch, 024h, 01Ch, 089h, 054h, 024h, 020h, 089h, 044h, 024h, 024h
    call ?j_000233ee@@YAXXZ
    db 06Ah, 002h, 08Dh, 054h, 024h, 01Ch, 052h, 08Dh, 04Fh, 020h
    call ?j_00040732@@YAXXZ
    db 05Bh, 05Fh, 05Eh, 0B8h, 001h, 000h, 000h, 000h, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Bh, 07Eh, 02Ch
    db 08Bh, 04Eh, 0F4h, 047h, 089h, 07Eh, 02Ch, 08Bh, 091h, 0D0h, 001h, 000h, 000h, 08Bh, 0C7h, 03Bh
    db 0C2h, 072h, 00Eh, 06Ah, 003h, 0EBh, 002h, 06Ah, 000h, 08Dh, 04Eh, 0F0h
    call ?j_000298c0@@YAXXZ
    db 05Bh, 05Fh, 05Eh, 0B8h, 001h, 000h, 000h, 000h, 05Dh, 083h, 0C4h, 020h, 0C3h, 08Dh, 049h, 000h
    dd ?d_00266f40@@YAXXZ + 0116h
    dd ?d_00266f40@@YAXXZ + 012Ch
    dd ?d_00266f40@@YAXXZ + 0278h
    dd ?d_00266f40@@YAXXZ + 029Ch
    dd ?d_00266f40@@YAXXZ + 0292h
?d_00266f40@@YAXXZ ENDP
_TEXT$d00666f40 ENDS
_TEXT SEGMENT

; retail @ 0x0028EF30 size 54
public ?d_0028ef30@@YAXXZ
?d_0028ef30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0F8h, 09h, 77h, 13h, 0Fh, 0B6h, 80h, 5Ch, 0EFh, 68h, 00h
    db 0FFh, 24h, 85h, 54h, 0EFh, 68h, 00h, 0B0h, 01h, 0C2h, 04h, 00h, 32h, 0C0h, 0C2h, 04h
    db 00h, 8Dh, 49h, 00h, 47h, 0EFh, 68h, 00h, 4Ch, 0EFh, 68h, 00h, 00h, 01h, 01h, 00h
    db 00h, 00h, 00h, 00h, 01h, 00h
?d_0028ef30@@YAXXZ ENDP

; retail @ 0x0028EF80 size 54
public ?d_0028ef80@@YAXXZ
?d_0028ef80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0F8h, 09h, 77h, 13h, 0Fh, 0B6h, 80h, 0ACh, 0EFh, 68h, 00h
    db 0FFh, 24h, 85h, 0A4h, 0EFh, 68h, 00h, 0B0h, 01h, 0C2h, 04h, 00h, 32h, 0C0h, 0C2h, 04h
    db 00h, 8Dh, 49h, 00h, 9Ch, 0EFh, 68h, 00h, 97h, 0EFh, 68h, 00h, 00h, 01h, 01h, 00h
    db 00h, 00h, 00h, 00h, 01h, 00h
?d_0028ef80@@YAXXZ ENDP

; retail @ 0x002A11F0 size 112
public ?d_002a11f0@@YAXXZ
?d_002a11f0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 74h, 05h, 8Bh, 51h, 3Ch, 89h, 10h, 8Bh, 41h
    db 2Ch, 83h, 0F8h, 04h, 77h, 3Ch, 0FFh, 24h, 85h, 4Ch, 12h, 6Ah, 00h, 0D9h, 05h, 34h
    db 53h, 07h, 01h, 59h, 0C2h, 04h, 00h, 8Bh, 41h, 38h, 85h, 0C0h, 89h, 44h, 24h, 08h
    db 7Eh, 20h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 50h, 3Ch, 0DBh, 40h, 3Ch, 85h, 0D2h, 7Dh
    db 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0DAh, 61h, 34h, 0DAh, 74h, 24h, 08h, 59h, 0C2h
    db 04h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 59h, 0C2h, 04h, 00h, 42h, 12h, 6Ah, 00h
    db 0Dh, 12h, 6Ah, 00h, 42h, 12h, 6Ah, 00h, 17h, 12h, 6Ah, 00h, 42h, 12h, 6Ah, 00h
?d_002a11f0@@YAXXZ ENDP

; retail @ 0x002B5CC0 size 1124
_TEXT ENDS
_TEXT$d006b5cc0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x006B5CC0 size 1124
public ?d_002b5cc0@@YAXXZ
?d_002b5cc0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va010132CB
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 0A0h, 000h, 000h, 000h, 053h, 055h, 056h, 08Bh, 0F1h, 08Bh, 06Eh, 0F8h, 057h, 06Ah, 000h, 08Bh
    db 0CDh
    call ?j_00031a7f@@YAXXZ
    db 08Bh, 0D8h, 033h, 0FFh, 085h, 0DBh, 0C6h, 044h, 024h, 012h, 000h, 0C6h, 044h, 024h, 011h, 000h
    db 00Fh, 084h, 0A3h, 001h, 000h, 000h, 08Ah, 086h, 0F2h, 003h, 000h, 000h, 084h, 0C0h, 074h, 023h
    db 057h, 08Dh, 086h, 0E4h, 003h, 000h, 000h, 050h, 057h, 08Dh, 04Dh, 038h, 051h, 055h, 08Bh, 0CBh
    call ?j_0003a4e5@@YAXXZ
    db 088h, 044h, 024h, 012h, 0C6h, 044h, 024h, 011h, 001h, 0E9h, 076h, 001h, 000h, 000h, 08Ah, 086h
    db 0F1h, 003h, 000h, 000h, 084h, 0C0h, 074h, 045h, 08Bh, 096h, 0E0h, 003h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 050h, 001h, 000h, 000h, 0F6h, 087h, 044h, 003h, 000h, 000h
    db 001h, 074h, 007h, 033h, 0FFh, 0E9h, 040h, 001h, 000h, 000h, 06Ah, 000h, 057h, 055h, 08Bh, 0CBh
    call ?j_0002e85c@@YAXXZ
    db 088h, 044h, 024h, 012h, 0C6h, 044h, 024h, 011h, 001h, 0E9h, 027h, 001h, 000h, 000h, 08Ah, 086h
    db 0F0h, 003h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 019h, 001h, 000h, 000h, 08Dh, 07Eh, 0F0h, 08Bh
    db 0CFh, 0C6h, 044h, 024h, 013h, 000h
    call ?j_000346a3@@YAXXZ
    db 083h, 0F8h, 0FFh, 074h, 00Ah, 050h, 08Bh, 0CFh
    call ?j_000487f2@@YAXXZ
    db 0EBh, 008h, 08Bh, 04Eh, 020h
    call ?j_0000e570@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 075h, 018h, 08Bh, 086h, 0DCh, 003h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 020h, 0F6h, 087h, 044h, 003h, 000h, 000h, 001h, 074h, 013h, 06Ah
    db 000h, 06Ah, 001h, 08Dh, 04Eh, 0F0h
    call ?j_00003f58@@YAXXZ
    db 08Bh, 0F8h, 0C6h, 044h, 024h, 013h, 001h, 085h, 0FFh, 075h, 062h, 08Ah, 086h, 0F3h, 003h, 000h
    db 000h, 084h, 0C0h, 074h, 054h, 06Ah, 000h, 06Ah, 000h, 08Dh, 04Eh, 0F0h
    call ?j_00003f58@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 00Fh, 084h, 04Eh, 0FFh, 0FFh, 0FFh, 06Ah, 000h, 057h, 055h, 08Bh, 0CBh
    call ?j_0002e85c@@YAXXZ
    db 084h, 0C0h, 088h, 044h, 024h, 012h, 0C6h, 044h, 024h, 011h, 001h, 00Fh, 084h, 032h, 0FFh, 0FFh
    db 0FFh, 06Ah, 002h, 068h, 0FFh, 0FFh, 0FFh, 07Fh, 057h, 08Dh, 04Eh, 010h
    call ?j_0002edcf@@YAXXZ
    db 0C6h, 086h, 0F4h, 003h, 000h, 000h, 001h, 08Bh, 047h, 074h, 089h, 086h, 0DCh, 003h, 000h, 000h
    db 0EBh, 057h, 085h, 0FFh, 074h, 049h, 06Ah, 000h, 057h, 055h, 08Bh, 0CBh
    call ?j_0002e85c@@YAXXZ
    db 088h, 044h, 024h, 012h, 08Bh, 047h, 074h, 089h, 086h, 0DCh, 003h, 000h, 000h, 08Ah, 086h, 0F4h
    db 003h, 000h, 000h, 084h, 0C0h, 0C6h, 044h, 024h, 011h, 001h, 074h, 02Ch, 08Ah, 044h, 024h, 013h
    db 084h, 0C0h, 074h, 024h, 08Ah, 044h, 024h, 012h, 084h, 0C0h, 074h, 01Ch, 06Ah, 002h, 068h, 0FFh
    db 0FFh, 0FFh, 07Fh, 057h, 08Dh, 04Eh, 010h
    call ?j_0002edcf@@YAXXZ
    db 0EBh, 00Ah, 0C7h, 086h, 0DCh, 003h, 000h, 000h, 000h, 000h, 000h, 000h, 08Ah, 086h, 0F3h, 003h
    db 000h, 000h, 084h, 0C0h, 074h, 01Eh, 085h, 0FFh, 075h, 01Ah, 08Dh, 04Eh, 0F0h
    call ?j_00044774@@YAXXZ
    db 084h, 0C0h, 075h, 00Eh, 08Ah, 086h, 00Eh, 003h, 000h, 000h, 084h, 0C0h, 075h, 004h, 0B1h, 001h
    db 0EBh, 002h, 032h, 0C9h, 08Bh, 086h, 0D4h, 003h, 000h, 000h, 083h, 0F8h, 004h, 08Bh, 015h
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 05Ah, 03Ch, 00Fh, 087h, 0B3h, 001h, 000h, 000h, 0FFh, 024h, 085h
    dd ?d_002b5cc0@@YAXXZ + 043Ch
    db 084h, 0C9h, 075h, 018h, 08Ah, 044h, 024h, 012h, 084h, 0C0h, 00Fh, 084h, 09Ch, 001h, 000h, 000h
    db 08Ah, 044h, 024h, 011h, 084h, 0C0h, 00Fh, 084h, 090h, 001h, 000h, 000h, 06Ah, 001h, 08Dh, 04Eh
    db 0F0h, 0E9h, 081h, 001h, 000h, 000h, 084h, 0C9h, 00Fh, 085h, 084h, 000h, 000h, 000h, 08Ah, 044h
    db 024h, 012h, 084h, 0C0h, 08Ah, 044h, 024h, 011h, 075h, 006h, 084h, 0C0h, 075h, 01Ah, 0EBh, 004h
    db 084h, 0C0h, 075h, 06Eh, 08Ah, 086h, 00Eh, 003h, 000h, 000h, 084h, 0C0h, 075h, 00Ah, 08Bh, 086h
    db 030h, 001h, 000h, 000h, 085h, 0C0h, 074h, 05Ah, 08Dh, 07Eh, 0F0h, 08Bh, 0CFh
    call ?j_000346a3@@YAXXZ
    db 083h, 0F8h, 0FFh, 00Fh, 084h, 038h, 001h, 000h, 000h, 08Bh, 046h, 0F4h, 08Ah, 048h, 06Eh, 084h
    db 0C9h, 00Fh, 084h, 02Ah, 001h, 000h, 000h, 08Bh, 04Fh, 008h, 0C7h, 087h, 0E4h, 003h, 000h, 000h
    db 004h, 000h, 000h, 000h, 08Bh, 001h, 0FFh, 050h, 028h, 08Bh, 0CFh, 0C7h, 087h, 0E8h, 003h, 000h
    db 000h, 000h, 000h, 000h, 000h
    call ?j_000346a3@@YAXXZ
    db 083h, 0F8h, 0FFh, 00Fh, 084h, 007h, 001h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?j_0000d0a8@@YAXXZ
    db 0E9h, 0FAh, 000h, 000h, 000h, 085h, 0FFh, 00Fh, 085h, 0F2h, 000h, 000h, 000h, 08Ah, 086h, 0F4h
    db 003h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 0E4h, 000h, 000h, 000h, 08Ah, 086h, 0D0h, 003h, 000h
    db 000h, 084h, 0C0h, 00Fh, 084h, 0D6h, 000h, 000h, 000h, 06Ah, 002h, 06Ah, 0FFh, 08Dh, 04Ch, 024h
    db 01Ch
    call ?j_00030ea4@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Dh, 08Eh, 030h, 003h, 000h, 000h, 0C7h, 084h, 024h, 0BCh, 000h
    db 000h, 000h, 006h, 000h, 000h, 000h
    call ?j_0002b9d1@@YAXXZ
    db 08Bh, 056h, 010h, 08Dh, 04Eh, 010h, 08Dh, 044h, 024h, 014h, 050h, 0FFh, 012h, 08Dh, 04Ch, 024h
    db 014h, 0C7h, 084h, 024h, 0B8h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_00017c2e@@YAXXZ
    db 0E9h, 088h, 000h, 000h, 000h, 08Bh, 086h, 0D8h, 003h, 000h, 000h, 085h, 0C0h, 074h, 07Eh, 03Bh
    db 0D8h, 072h, 07Ah, 06Ah, 002h, 08Dh, 04Eh, 0F0h
    call ?j_0004a0d9@@YAXXZ
    db 08Ah, 086h, 0F0h, 003h, 000h, 000h, 084h, 0C0h, 074h, 066h, 08Ah, 044h, 024h, 012h, 084h, 0C0h
    db 074h, 05Eh, 08Ah, 044h, 024h, 011h, 084h, 0C0h, 074h, 056h, 085h, 0FFh, 074h, 052h, 06Ah, 002h
    db 068h, 0FFh, 0FFh, 0FFh, 07Fh, 057h, 08Dh, 04Eh, 010h
    call ?j_0002edcf@@YAXXZ
    db 0C6h, 086h, 0F4h, 003h, 000h, 000h, 001h, 0EBh, 039h, 08Bh, 086h, 0D8h, 003h, 000h, 000h, 085h
    db 0C0h, 074h, 02Fh, 03Bh, 0D8h, 072h, 02Bh, 06Ah, 000h, 08Dh, 04Eh, 0F0h, 0EBh, 01Fh, 08Dh, 07Eh
    db 0F0h, 08Bh, 0CFh
    call ?j_000346a3@@YAXXZ
    db 083h, 0F8h, 0FFh, 074h, 015h, 050h, 08Bh, 0CFh
    call ?j_00043f45@@YAXXZ
    db 084h, 0C0h, 074h, 009h, 06Ah, 003h, 08Bh, 0CFh
    call ?j_0004a0d9@@YAXXZ
    db 08Bh, 086h, 0D4h, 003h, 000h, 000h, 083h, 0F8h, 004h, 0BFh, 0FFh, 0FFh, 0FFh, 03Fh, 077h, 02Bh
    db 0FFh, 024h, 085h
    dd ?d_002b5cc0@@YAXXZ + 0450h
    db 0BFh, 0FFh, 0FFh, 0FFh, 03Fh, 0EBh, 01Dh, 08Bh, 0BEh, 0D8h, 003h, 000h, 000h, 03Bh, 0FBh, 076h
    db 004h, 02Bh, 0FBh, 0EBh, 005h, 0BFh, 001h, 000h, 000h, 000h, 08Dh, 04Eh, 010h, 06Ah, 002h
    call ?j_00024d70@@YAXXZ
    db 08Bh, 0CEh
    call ?j_00028772@@YAXXZ
    db 03Bh, 0F8h, 07Dh, 002h, 08Bh, 0C7h, 08Bh, 08Ch, 024h, 0B0h, 000h, 000h, 000h, 05Fh, 05Eh, 05Dh
    db 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 081h, 0C4h, 0ACh, 000h, 000h, 000h, 0C3h
    dd ?d_002b5cc0@@YAXXZ + 022Fh
    dd ?d_002b5cc0@@YAXXZ + 0353h
    dd ?d_002b5cc0@@YAXXZ + 0255h
    dd ?d_002b5cc0@@YAXXZ + 03A2h
    dd ?d_002b5cc0@@YAXXZ + 03B7h
    dd ?d_002b5cc0@@YAXXZ + 03F2h
    dd ?d_002b5cc0@@YAXXZ + 03F9h
    dd ?d_002b5cc0@@YAXXZ + 03F2h
    dd ?d_002b5cc0@@YAXXZ + 03F9h
    dd ?d_002b5cc0@@YAXXZ + 0407h
?d_002b5cc0@@YAXXZ ENDP
_TEXT$d006b5cc0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
