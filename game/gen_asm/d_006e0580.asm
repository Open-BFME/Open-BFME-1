.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?CameraShakerSystem@@3VCameraShakeSystemClass@@A:BYTE
EXTERN ?ClientAt012F1464@@3PAVClient0009A580@@A:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Data00EF8048@@3PAVGen006E1AC0@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Look_At@Matrix3D@@QAEXABVVector3@@0M@Z:NEAR
EXTERN ?R2Ptr012F0FE0@@3PAVGen00049FDA@@A:BYTE
EXTERN ?R2Ptr01306EEC@@3PAVGen0003AC38@@A:BYTE
EXTERN ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A:BYTE
EXTERN ?Rva012F8058@@3PAVRva00712F60@@A:BYTE
EXTERN ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A:BYTE
EXTERN ?TheBfmeGlobal_012f7fe0@@3PAVBfmeGlobal_012f7fe0@@A:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeDisplayTwoPi@@3MB:BYTE
EXTERN ?g_bfmeK1266B@@3MB:BYTE
EXTERN ?g_bfmeSubB3@@3NA:BYTE
EXTERN ?j_0000712b@@YAXXZ:NEAR
EXTERN ?j_0000cbcb@@YAXXZ:NEAR
EXTERN ?j_00010cfd@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_00021472@@YAXXZ:NEAR
EXTERN ?j_00022bb0@@YAXXZ:NEAR
EXTERN ?j_00024bcc@@YAXXZ:NEAR
EXTERN ?j_000273db@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00034608@@YAXXZ:NEAR
EXTERN ?j_00040bc9@@YAXXZ:NEAR
EXTERN ?j_00049fda@@YAXXZ:NEAR
EXTERN ?j_0004b03d@@YAXXZ:NEAR
EXTERN __imp_?i_009f7030@@YAXXZ:BYTE
EXTERN __real@3e800000:BYTE
EXTERN __real@3f400000:BYTE
EXTERN __real@3f5f66f3:BYTE
EXTERN __real@497423f0:BYTE
EXTERN __real@4f800000:BYTE
EXTERN g_Va0111D874:BYTE
EXTERN g_Va012BAA30:BYTE
_TEXT SEGMENT

; ghidra: FUN_00ae0580  retail @ 0x006E0580 size 3400
_TEXT ENDS
_TEXT$d00ae0580 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AE0580 size 3400
public ?d_006e0580@@YAXXZ
?d_006e0580@@YAXXZ PROC
    db 081h, 0ECh, 0ACh, 000h, 000h, 000h, 053h, 055h, 056h, 08Bh, 0B4h, 024h, 0BCh, 000h, 000h, 000h
    db 0D9h, 046h, 070h, 08Bh, 086h, 0D4h, 000h, 000h, 000h, 083h, 0F8h, 002h, 0D8h, 046h, 04Ch, 057h
    db 08Dh, 07Eh, 04Ch, 0D9h, 017h, 08Bh, 0E9h, 0D9h, 046h, 074h, 089h, 06Ch, 024h, 048h, 0D8h, 046h
    db 050h, 0D9h, 054h, 024h, 020h, 0D9h, 05Eh, 050h, 00Fh, 085h, 0BDh, 000h, 000h, 000h, 0DDh, 0D8h
    db 08Bh, 007h, 0D9h, 046h, 06Ch, 08Bh, 04Fh, 004h, 0D9h, 046h, 068h, 08Bh, 057h, 008h, 0D9h, 046h
    db 064h, 089h, 044h, 024h, 014h, 0D9h, 0C0h, 089h, 04Ch, 024h, 018h, 0D8h, 0C9h, 089h, 054h, 024h
    db 01Ch, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DAh, 0E9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 044h, 0DDh, 0D8h, 07Ah, 016h, 08Bh
    db 044h, 024h, 014h, 089h, 044h, 024h, 024h, 089h, 04Ch, 024h, 028h, 0C7h, 044h, 024h, 02Ch, 000h
    db 000h, 000h, 000h, 0EBh, 015h, 08Bh, 056h, 064h, 08Bh, 046h, 068h, 08Bh, 04Eh, 06Ch, 089h, 054h
    db 024h, 024h, 089h, 044h, 024h, 028h, 089h, 04Ch, 024h, 02Ch, 08Bh, 006h, 033h, 0DBh, 089h, 058h
    db 004h, 089h, 058h, 008h, 089h, 058h, 00Ch, 0B9h, 000h, 000h, 080h, 03Fh, 089h, 008h, 089h, 048h
    db 014h, 089h, 058h, 010h, 089h, 058h, 018h, 089h, 058h, 01Ch, 089h, 048h, 028h, 089h, 058h, 020h
    db 089h, 058h, 024h, 089h, 058h, 02Ch, 08Bh, 056h, 03Ch, 052h, 08Dh, 044h, 024h, 028h, 050h, 08Dh
    db 04Ch, 024h, 01Ch, 051h, 08Bh, 00Eh
    call ?Look_At@Matrix3D@@QAEXABVVector3@@0M@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0ACh, 000h, 000h, 000h, 0C2h, 004h, 000h, 08Ah, 046h, 078h
    db 033h, 0DBh, 03Ah, 0C3h, 074h, 071h, 0D9h, 046h, 07Ch, 0D9h, 054h, 024h, 010h, 0D8h, 0D9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 0DDh, 0D8h, 0D9h, 044h, 024h, 010h, 0D9h, 017h, 0D9h, 086h
    db 084h, 000h, 000h, 000h, 0D9h, 054h, 024h, 010h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah
    db 006h, 0DDh, 0D8h, 0D9h, 044h, 024h, 010h, 0D9h, 01Fh, 0D9h, 044h, 024h, 020h, 0D9h, 086h, 080h
    db 000h, 000h, 000h, 0D9h, 054h, 024h, 010h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 006h
    db 0DDh, 0D8h, 0D9h, 044h, 024h, 010h, 0D9h, 056h, 050h, 0D9h, 086h, 088h, 000h, 000h, 000h, 0D9h
    db 054h, 024h, 010h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 006h, 0DDh, 0D8h, 0D9h, 044h
    db 024h, 010h, 0D9h, 05Eh, 050h, 0EBh, 002h, 0DDh, 0D8h, 08Ah, 086h, 08Ch, 000h, 000h, 000h, 03Ah
    db 0C3h, 088h, 044h, 024h, 043h, 074h, 061h, 0D9h, 046h, 030h, 08Bh, 086h, 094h, 000h, 000h, 000h
    db 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 096h, 090h, 000h, 000h, 000h, 08Bh, 08Eh, 098h, 000h, 000h, 000h, 089h, 044h, 024h, 018h
    db 089h, 054h, 024h, 014h, 0DFh, 0E0h, 089h, 04Ch, 024h, 01Ch, 0F6h, 0C4h, 041h, 075h, 013h, 0DDh
    db 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 00Dh
    dd __real@3f5f66f3
    db 0D9h, 05Eh, 040h, 0EBh, 077h, 0D8h, 015h
    dd ?g_bfmeADL@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?g_bfmeADL@@3MA
    db 0D8h, 00Dh
    dd __real@3f5f66f3
    db 0D9h, 05Eh, 040h, 0EBh, 057h, 0D9h, 086h, 090h, 000h, 000h, 000h, 08Ah, 086h, 09Ch, 000h, 000h
    db 000h, 03Ah, 0C3h, 0D8h, 04Eh, 030h, 0D9h, 05Ch, 024h, 014h, 0D9h, 086h, 094h, 000h, 000h, 000h
    db 0D8h, 04Eh, 030h, 0D9h, 05Ch, 024h, 018h, 0D9h, 046h, 030h, 0D8h, 08Eh, 098h, 000h, 000h, 000h
    db 0D9h, 05Ch, 024h, 01Ch, 074h, 026h, 08Bh, 096h, 0A4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 03Bh, 0C3h, 074h, 010h, 0D9h, 040h, 040h, 0D8h, 086h, 098h, 000h, 000h, 000h, 0D8h, 04Eh, 030h
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 046h, 02Ch, 0C7h, 044h, 024h, 02Ch, 000h, 000h, 000h, 000h, 0D8h
    db 074h, 024h, 01Ch, 0C7h, 044h, 024h, 05Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 06Ch, 000h
    db 000h, 000h, 000h, 0C7h, 044h, 024h, 07Ch, 000h, 000h, 000h, 000h, 0DCh, 02Dh
    dd ?g_bfmeSubB3@@3NA
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 046h, 034h, 0D9h, 0C0h, 0D9h, 0FFh, 0D9h, 05Ch, 024h, 04Ch, 0D9h
    db 0FEh, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 064h, 024h, 04Ch, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C9h, 0D9h, 054h, 024h, 020h, 0D9h, 05Ch, 024h, 010h, 0D9h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 034h, 0D8h, 044h, 024h, 010h, 0D9h, 044h, 024h, 020h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 05Ch, 024h, 038h, 0D9h, 0CAh, 0D9h, 05Ch, 024h, 03Ch, 0D9h, 044h, 024h, 038h, 0D8h, 064h
    db 024h, 03Ch, 0D9h, 044h, 024h, 04Ch, 0D9h, 054h, 024h, 030h, 0D9h, 05Ch, 024h, 050h, 0D9h, 05Ch
    db 024h, 054h, 0D9h, 0C9h, 0D9h, 05Ch, 024h, 058h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 020h, 0D8h, 064h, 024h, 034h, 0D9h, 044h, 024h, 030h, 0D9h, 044h, 024h, 03Ch
    db 0D8h, 044h, 024h, 038h, 0D9h, 05Ch, 024h, 060h, 0D9h, 05Ch, 024h, 064h, 0D9h, 05Ch, 024h, 068h
    db 0D9h, 044h, 024h, 04Ch, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 044h, 024h, 020h, 0D8h, 044h, 024h, 034h, 0D9h, 044h, 024h, 010h, 0D8h, 064h, 024h, 034h
    db 0D9h, 05Ch, 024h, 070h, 0D9h, 05Ch, 024h, 074h, 0D9h, 05Ch, 024h, 078h, 0D9h, 046h, 038h, 0D9h
    db 0C0h, 0D9h, 0FFh, 0D9h, 0C9h, 0D9h, 0FEh, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0E2h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 010h, 0D9h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 020h, 0D8h, 044h, 024h, 010h, 0D9h, 054h, 024h, 030h, 08Bh, 044h, 024h, 030h
    db 0D9h, 044h, 024h, 010h, 089h, 084h, 024h, 09Ch, 000h, 000h, 000h, 0D8h, 064h, 024h, 020h, 08Dh
    db 044h, 024h, 014h, 050h, 0C7h, 084h, 024h, 09Ch, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0D9h
    db 054h, 024h, 040h, 0C7h, 084h, 024h, 0ACh, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0D9h, 0C4h
    db 08Bh, 054h, 024h, 040h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 089h, 094h, 024h, 0B0h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0BCh, 000h, 000h, 000h, 000h, 000h
    db 000h, 000h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 09Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 094h, 000h, 000h, 000h, 0D9h, 09Ch
    db 024h, 098h, 000h, 000h, 000h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 024h, 0D8h, 064h, 024h, 014h
    db 0D9h, 05Ch, 024h, 03Ch, 08Bh, 04Ch, 024h, 03Ch, 0D9h, 0C0h, 089h, 08Ch, 024h, 0A8h, 000h, 000h
    db 000h, 0D9h, 09Ch, 024h, 0A4h, 000h, 000h, 000h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h, 0D9h
    db 044h, 024h, 014h, 0D8h, 044h, 024h, 024h, 0D9h, 09Ch, 024h, 0B4h, 000h, 000h, 000h, 0D9h, 09Ch
    db 024h, 0B8h, 000h, 000h, 000h
    call ?j_00010cfd@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 051h, 08Dh, 04Ch, 024h, 054h
    call ?j_00010cfd@@YAXXZ
    db 0D9h, 044h, 024h, 044h, 0D8h, 04Ch, 024h, 014h, 08Bh, 046h, 050h, 0D9h, 044h, 024h, 044h, 08Bh
    db 017h, 0D8h, 04Ch, 024h, 018h, 089h, 044h, 024h, 028h, 0D9h, 044h, 024h, 044h, 08Ah, 086h, 09Ch
    db 000h, 000h, 000h, 03Ah, 0C3h, 0D8h, 04Ch, 024h, 01Ch, 089h, 054h, 024h, 024h, 0D9h, 05Ch, 024h
    db 01Ch, 0D9h, 0C9h, 0D8h, 007h, 0D9h, 05Ch, 024h, 014h, 0D8h, 046h, 050h, 0D9h, 05Ch, 024h, 018h
    db 074h, 014h, 08Bh, 08Eh, 0A4h, 000h, 000h, 000h, 051h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0001f253@@YAXXZ
    db 0EBh, 002h, 033h, 0C0h, 038h, 09Eh, 09Ch, 000h, 000h, 000h, 00Fh, 084h, 024h, 002h, 000h, 000h
    db 03Bh, 0C3h, 074h, 011h, 06Ah, 00Ch, 08Bh, 0C8h
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 00Fh, 002h, 000h, 000h, 0D9h, 046h, 034h, 0C7h, 084h, 024h, 098h, 000h
    db 000h, 000h, 000h, 000h, 000h, 000h, 0D9h, 0C0h, 0C7h, 084h, 024h, 0A8h, 000h, 000h, 000h, 000h
    db 000h, 000h, 000h, 0D9h, 0FFh, 0C7h, 084h, 024h, 0B8h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 0FEh, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 064h, 024h, 044h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C9h, 0D9h, 054h, 024h, 030h, 0D9h, 05Ch, 024h, 03Ch, 0D9h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 034h, 0D8h, 044h, 024h, 03Ch, 0D9h, 044h, 024h, 030h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 05Ch, 024h, 020h, 0D9h, 0CAh, 0D9h, 05Ch, 024h, 010h, 0D9h, 044h, 024h, 020h, 0D8h, 064h
    db 024h, 010h, 0D9h, 044h, 024h, 044h, 0D9h, 054h, 024h, 030h, 0D9h, 09Ch, 024h, 08Ch, 000h, 000h
    db 000h, 0D9h, 09Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 0C9h, 0D9h, 09Ch, 024h, 094h, 000h, 000h
    db 000h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 038h, 0D8h, 064h, 024h, 034h, 0D9h, 044h, 024h, 030h, 0D9h, 044h, 024h, 010h
    db 0D8h, 044h, 024h, 020h, 0D9h, 09Ch, 024h, 09Ch, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0A0h, 000h
    db 000h, 000h, 0D9h, 09Ch, 024h, 0A4h, 000h, 000h, 000h, 0D9h, 044h, 024h, 044h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 044h, 024h, 038h, 0D8h, 044h, 024h, 034h, 0D9h, 044h, 024h, 03Ch, 0D8h, 064h, 024h, 034h
    db 0D9h, 09Ch, 024h, 0ACh, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0B0h, 000h, 000h, 000h, 0D9h, 09Ch
    db 024h, 0B4h, 000h, 000h, 000h, 0D9h, 046h, 038h, 0D9h, 0C0h, 0D9h, 0FFh, 0D9h, 0C9h, 0D9h, 0FEh
    db 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0E2h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 0C9h, 0D9h, 05Ch, 024h, 010h, 0D9h, 0C1h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 054h, 024h, 020h, 0D8h, 044h, 024h, 010h, 0D9h, 054h, 024h, 030h, 0D9h, 044h, 024h, 010h
    db 0D8h, 064h, 024h, 020h, 0D9h, 054h, 024h, 03Ch, 0D9h, 0C4h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 054h, 024h, 030h, 08Bh, 04Ch, 024h, 03Ch, 089h, 054h, 024h, 060h, 0D9h, 05Ch, 024h, 050h
    db 08Dh, 054h, 024h, 014h, 0D9h, 05Ch, 024h, 054h, 089h, 04Ch, 024h, 070h, 052h, 0D9h, 05Ch, 024h
    db 05Ch, 08Dh, 04Ch, 024h, 054h, 0C7h, 044h, 024h, 060h, 000h, 000h, 000h, 000h, 0D8h, 00Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0C7h, 044h, 024h, 070h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 000h
    db 000h, 000h, 000h, 0D9h, 05Ch, 024h, 024h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 024h, 0D8h
    db 064h, 024h, 014h, 0D9h, 05Ch, 024h, 03Ch, 08Bh, 044h, 024h, 03Ch, 0D9h, 0C0h, 089h, 044h, 024h
    db 06Ch, 0D9h, 05Ch, 024h, 068h, 0D9h, 044h, 024h, 014h, 0D8h, 044h, 024h, 024h, 0D9h, 05Ch, 024h
    db 078h, 0D9h, 05Ch, 024h, 07Ch
    call ?j_00010cfd@@YAXXZ
    db 08Dh, 044h, 024h, 014h, 050h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h
    call ?j_00010cfd@@YAXXZ
    db 0D9h, 044h, 024h, 014h, 0D8h, 007h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 018h, 0D8h, 046h
    db 050h, 0D9h, 05Ch, 024h, 018h, 0D9h, 044h, 024h, 01Ch, 0D8h, 046h, 054h, 0D9h, 05Ch, 024h, 01Ch
    db 0D9h, 044h, 024h, 024h, 0D8h, 007h, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 028h, 0D8h, 046h
    db 050h, 0D9h, 05Ch, 024h, 028h, 0D9h, 046h, 048h, 0D8h, 046h, 054h, 0EBh, 011h, 0D9h, 044h, 024h
    db 01Ch, 0D8h, 046h, 02Ch, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 046h, 048h, 0D8h, 046h, 02Ch, 08Ah, 044h
    db 024h, 043h, 0D9h, 05Ch, 024h, 02Ch, 03Ah, 0C3h, 074h, 07Fh, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 030h, 000h, 000h, 080h, 03Fh, 0FFh, 092h, 038h, 001h, 000h, 000h
    db 084h, 0C0h, 075h, 047h, 0D9h, 046h, 030h, 0D8h, 015h
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ah, 0DDh, 0D8h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0EBh, 015h, 0D8h, 015h
    dd ?g_bfmeADL@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0DDh, 0D8h, 0D9h, 005h
    dd ?g_bfmeADL@@3MA
    db 0D9h, 005h
    dd __real@3f400000
    db 0D8h, 0C9h, 0D8h, 005h
    dd __real@3e800000
    db 0D8h, 04Ch, 024h, 01Ch, 0D9h, 05Ch, 024h, 01Ch, 0EBh, 004h, 0D9h, 044h, 024h, 030h, 0D8h, 00Dh
    dd __real@3f400000
    db 0D8h, 005h
    dd __real@3e800000
    db 0D9h, 096h, 0A0h, 000h, 000h, 000h, 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0EBh, 029h, 0D9h, 086h, 0A0h, 000h, 000h, 000h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 08Ah, 086h, 09Ch, 000h, 000h, 000h, 0F6h, 0C4h, 041h, 07Bh, 036h, 03Ah, 0C3h, 075h
    db 036h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 0B6h, 0A0h, 000h, 000h, 000h, 0D9h, 044h, 024h, 014h, 0D8h, 064h, 024h, 024h, 0D8h, 0C9h
    db 0D8h, 044h, 024h, 024h, 0D9h, 05Ch, 024h, 014h, 0D9h, 044h, 024h, 018h, 0D8h, 064h, 024h, 028h
    db 0D8h, 0C9h, 0D8h, 044h, 024h, 028h, 0D9h, 05Ch, 024h, 018h, 0EBh, 075h, 03Ah, 0C3h, 074h, 059h
    db 038h, 05Dh, 01Eh, 074h, 003h, 088h, 05Dh, 01Eh, 0D9h, 044h, 024h, 028h, 08Bh, 044h, 024h, 014h
    db 0D8h, 064h, 024h, 018h, 08Bh, 04Ch, 024h, 018h, 0D9h, 044h, 024h, 024h, 08Bh, 054h, 024h, 01Ch
    db 0D8h, 064h, 024h, 014h, 089h, 045h, 010h, 089h, 04Dh, 014h, 089h, 055h, 018h, 0D9h, 0C0h, 0D8h
    db 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 030h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h
    db 044h, 024h, 030h, 0D9h, 0FAh, 0D9h, 05Ch, 024h, 010h, 0D9h, 086h, 0A0h, 000h, 000h, 000h, 0D9h
    db 0F2h, 0DDh, 0D8h, 0D8h, 04Ch, 024h, 010h, 0EBh, 00Eh, 0D9h, 044h, 024h, 01Ch, 0D8h, 064h, 024h
    db 02Ch, 0D8h, 08Eh, 0A0h, 000h, 000h, 000h, 0D9h, 044h, 024h, 01Ch, 0D8h, 0E1h, 0D9h, 05Ch, 024h
    db 02Ch, 08Ah, 086h, 0A8h, 000h, 000h, 000h, 0DDh, 0D8h, 03Ah, 0C3h, 00Fh, 084h, 08Dh, 000h, 000h
    db 000h, 0D9h, 046h, 010h, 08Bh, 046h, 008h, 0D8h, 064h, 024h, 01Ch, 08Bh, 04Eh, 00Ch, 0D9h, 046h
    db 00Ch, 08Bh, 056h, 010h, 0D8h, 064h, 024h, 018h, 089h, 04Ch, 024h, 018h, 0D9h, 046h, 008h, 089h
    db 054h, 024h, 01Ch, 0D8h, 064h, 024h, 014h, 089h, 044h, 024h, 014h, 0D9h, 044h, 024h, 024h, 08Dh
    db 046h, 058h, 08Bh, 0C8h, 08Bh, 029h, 0D8h, 0C1h, 08Bh, 0D7h, 089h, 02Ah, 08Bh, 069h, 004h, 0D9h
    db 05Ch, 024h, 024h, 08Bh, 049h, 008h, 0D9h, 0C1h, 0D8h, 044h, 024h, 028h, 089h, 06Ah, 004h, 08Bh
    db 06Ch, 024h, 048h, 089h, 04Ah, 008h, 0D9h, 05Ch, 024h, 028h, 0D9h, 0CAh, 0D8h, 044h, 024h, 02Ch
    db 0D9h, 05Ch, 024h, 02Ch, 0D9h, 0C9h, 0D8h, 007h, 0D9h, 01Fh, 0D8h, 046h, 050h, 0D9h, 05Eh, 050h
    db 08Bh, 017h, 08Bh, 04Fh, 004h, 089h, 010h, 08Bh, 057h, 008h, 089h, 048h, 004h, 089h, 050h, 008h
    db 038h, 09Eh, 0A9h, 000h, 000h, 000h, 075h, 006h, 088h, 09Eh, 0A8h, 000h, 000h, 000h, 08Bh, 044h
    db 024h, 014h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 089h, 046h, 008h, 08Bh, 044h, 024h
    db 024h, 089h, 04Eh, 00Ch, 08Bh, 04Ch, 024h, 028h, 089h, 056h, 010h, 08Bh, 054h, 024h, 02Ch, 089h
    db 046h, 014h, 089h, 04Eh, 018h, 089h, 056h, 01Ch, 0D9h, 046h, 008h, 0D9h, 046h, 00Ch, 08Bh, 046h
    db 010h, 0D9h, 0C9h, 089h, 084h, 024h, 088h, 000h, 000h, 000h, 0D8h, 066h, 014h, 0D9h, 09Ch, 024h
    db 080h, 000h, 000h, 000h, 0D8h, 066h, 018h, 0D9h, 084h, 024h, 088h, 000h, 000h, 000h, 0D8h, 066h
    db 01Ch, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 084h, 024h, 080h, 000h
    db 000h, 000h, 0D8h, 08Ch, 024h, 080h, 000h, 000h, 000h, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 030h, 0DDh
    db 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 030h, 0D9h, 0FAh, 0D9h, 05Ch, 024h, 048h, 038h, 09Eh, 0D0h
    db 000h, 000h, 000h, 08Bh, 04Ch, 024h, 048h, 089h, 04Eh, 004h, 075h, 012h, 056h, 08Dh, 054h, 024h
    db 028h, 052h, 08Dh, 044h, 024h, 01Ch, 050h, 08Bh, 0CDh
    call ?j_000273db@@YAXXZ
    db 0D9h, 046h, 06Ch, 0D9h, 046h, 068h, 0D9h, 046h, 064h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h
    db 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 041h, 0DDh, 0D8h, 075h, 015h, 0D9h, 046h, 06Ch
    db 08Bh, 04Eh, 064h, 0D9h, 046h, 068h, 089h, 04Ch, 024h, 024h, 0D9h, 05Ch, 024h, 028h, 0D9h, 05Ch
    db 024h, 02Ch, 08Bh, 006h, 089h, 058h, 004h, 089h, 058h, 008h, 089h, 058h, 00Ch, 0B9h, 000h, 000h
    db 080h, 03Fh, 089h, 008h, 089h, 048h, 014h, 089h, 058h, 010h, 089h, 058h, 018h, 089h, 058h, 01Ch
    db 089h, 048h, 028h, 089h, 058h, 020h, 089h, 058h, 024h, 089h, 058h, 02Ch, 08Bh, 056h, 03Ch, 052h
    db 08Dh, 044h, 024h, 028h, 050h, 08Dh, 04Ch, 024h, 01Ch, 051h, 08Bh, 00Eh
    call ?Look_At@Matrix3D@@QAEXABVVector3@@0M@Z
    db 038h, 09Eh, 0D0h, 000h, 000h, 000h, 00Fh, 085h, 078h, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?CameraShakerSystem@@3VCameraShakeSystemClass@@A
    db 068h, 089h, 088h, 008h, 03Dh
    call ?j_0000cbcb@@YAXXZ
    db 08Bh, 054h, 024h, 014h, 08Dh, 07Eh, 020h, 057h, 083h, 0ECh, 00Ch, 08Bh, 0C4h, 089h, 010h, 08Bh
    db 04Ch, 024h, 028h, 089h, 048h, 004h, 08Bh, 054h, 024h, 02Ch, 089h, 050h, 008h, 08Bh, 00Dh
    dd ?CameraShakerSystem@@3VCameraShakeSystemClass@@A
    db 089h, 064h, 024h, 040h
    call ?j_0000712b@@YAXXZ
    db 0D9h, 007h, 0D9h, 0C0h, 08Bh, 006h, 0D9h, 0FEh, 0D9h, 0C9h, 0D9h, 0FFh, 0D9h, 040h, 004h, 0D9h
    db 040h, 008h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C1h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 058h, 004h, 0D8h
    db 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh, 0E9h, 0D9h, 058h, 008h, 0D9h, 040h, 014h, 0D9h, 040h, 018h
    db 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C1h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 058h, 014h, 0D8h, 0CAh, 0D9h
    db 0C9h, 0D8h, 0CBh, 0DEh, 0E9h, 0D9h, 058h, 018h, 0D9h, 040h, 024h, 0D9h, 040h, 028h, 0D9h, 0C1h
    db 0D8h, 0CBh, 0D9h, 0C1h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 058h, 024h, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h
    db 0CBh, 0DEh, 0E9h, 0D9h, 058h, 028h, 08Bh, 006h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 046h, 024h, 0D9h
    db 0C0h, 0D9h, 0FEh, 0D9h, 0C9h, 0D9h, 0FFh, 0D9h, 000h, 0D9h, 040h, 008h, 0D9h, 0C1h, 0D8h, 0CBh
    db 0D9h, 0C1h, 0D8h, 0CDh, 0DEh, 0E9h, 0D9h, 018h, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh, 0C1h
    db 0D9h, 058h, 008h, 0D9h, 040h, 010h, 0D9h, 040h, 018h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C1h, 0D8h
    db 0CDh, 0DEh, 0E9h, 0D9h, 058h, 010h, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 058h
    db 018h, 0D9h, 040h, 020h, 0D9h, 040h, 028h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C1h, 0D8h, 0CDh, 0DEh
    db 0E9h, 0D9h, 058h, 020h, 0D8h, 0CAh, 0D9h, 0C9h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 058h, 028h, 08Bh
    db 006h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 046h, 028h, 0D9h, 0C0h, 0D9h, 0FFh, 0D9h, 0C9h, 0D9h, 0FEh
    db 0D9h, 000h, 0D9h, 040h, 004h, 0D9h, 0C0h, 0D8h, 0CBh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h
    db 018h, 0D8h, 0CBh, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0E9h, 0D9h, 058h, 004h, 0D9h, 040h, 010h, 0D9h
    db 040h, 014h, 0D9h, 0C0h, 0D8h, 0CBh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 058h, 010h, 0D8h
    db 0CBh, 0D9h, 0C9h, 0D8h, 0CAh, 0DEh, 0E9h, 0D9h, 058h, 014h, 0D9h, 040h, 020h, 0D9h, 040h, 024h
    db 0D9h, 0C0h, 0D8h, 0CBh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 058h, 020h, 0D8h, 0CBh, 0D9h
    db 0C9h, 0D8h, 0CAh, 0DEh, 0E9h, 0D9h, 058h, 024h, 0DDh, 0D8h, 0DDh, 0D8h, 038h, 09Eh, 0AAh, 000h
    db 000h, 000h, 00Fh, 084h, 0F2h, 000h, 000h, 000h, 051h, 08Dh, 086h, 0ACh, 000h, 000h, 000h, 089h
    db 064h, 024h, 034h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A
    db 08Bh, 011h, 0FFh, 052h, 06Ch, 03Bh, 0C3h, 00Fh, 084h, 0C6h, 000h, 000h, 000h, 08Bh, 010h, 08Bh
    db 0C8h, 0FFh, 052h, 028h, 03Bh, 0C3h, 00Fh, 084h, 0B7h, 000h, 000h, 000h, 08Bh, 0C8h
    call ?j_00021472@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 00Fh, 03Bh, 0CBh, 00Fh, 084h, 0AAh, 000h, 000h, 000h, 08Bh, 001h, 0FFh, 090h
    db 09Ch, 000h, 000h, 000h, 03Bh, 0C3h, 075h, 00Fh, 08Bh, 04Fh, 004h, 083h, 0C7h, 004h, 03Bh, 0CBh
    db 075h, 0EAh, 0E9h, 08Fh, 000h, 000h, 000h, 08Bh, 010h, 08Dh, 04Ch, 024h, 050h, 051h, 08Dh, 08Eh
    db 0B0h, 000h, 000h, 000h, 051h, 08Bh, 0C8h, 0FFh, 052h, 008h, 08Bh, 006h, 08Bh, 054h, 024h, 050h
    db 089h, 010h, 08Bh, 04Ch, 024h, 054h, 089h, 048h, 004h, 08Bh, 054h, 024h, 058h, 089h, 050h, 008h
    db 08Bh, 04Ch, 024h, 05Ch, 089h, 048h, 00Ch, 08Bh, 054h, 024h, 060h, 089h, 050h, 010h, 08Bh, 04Ch
    db 024h, 064h, 089h, 048h, 014h, 08Bh, 054h, 024h, 068h, 089h, 050h, 018h, 08Bh, 04Ch, 024h, 06Ch
    db 089h, 048h, 01Ch, 08Bh, 054h, 024h, 070h, 089h, 050h, 020h, 08Bh, 04Ch, 024h, 074h, 089h, 048h
    db 024h, 08Bh, 054h, 024h, 078h, 089h, 050h, 028h, 08Bh, 04Ch, 024h, 07Ch, 089h, 048h, 02Ch, 08Bh
    db 006h, 0D9h, 040h, 00Ch, 08Bh, 050h, 02Ch, 0D9h, 040h, 01Ch, 08Bh, 0C2h, 0D9h, 0C9h, 089h, 094h
    db 024h, 088h, 000h, 000h, 000h, 0D9h, 05Eh, 058h, 089h, 046h, 060h, 0D9h, 05Eh, 05Ch, 0EBh, 006h
    db 088h, 09Eh, 0AAh, 000h, 000h, 000h, 0D9h, 046h, 044h, 08Bh, 006h, 0D9h, 0C0h, 0D9h, 0FEh, 0D9h
    db 0C9h, 0D9h, 0FFh, 0D9h, 000h, 0D9h, 040h, 008h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C4h, 0D8h, 0CAh
    db 0DEh, 0E9h, 0D9h, 018h, 0D8h, 0CAh, 0D9h, 0C3h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 058h, 008h, 0DDh
    db 0D8h, 0D9h, 040h, 010h, 0D9h, 040h, 018h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C4h, 0D8h, 0CAh, 0DEh
    db 0E9h, 0D9h, 058h, 010h, 0D8h, 0CAh, 0D9h, 0C3h, 0D8h, 0CAh, 0DEh, 0C1h, 0D9h, 058h, 018h, 0DDh
    db 0D8h, 0D9h, 040h, 020h, 0D9h, 040h, 028h, 0D9h, 0C1h, 0D8h, 0CBh, 0D9h, 0C4h, 0D8h, 0CAh, 0DEh
    db 0E9h, 0D9h, 058h, 020h, 0D8h, 0CAh, 0D9h, 0CBh, 0D8h, 0C9h, 0DEh, 0C3h, 0D9h, 0CAh, 0D9h, 058h
    db 028h, 08Ah, 086h, 0D0h, 000h, 000h, 000h, 03Ah, 0C3h, 0DDh, 0D9h, 0DDh, 0D8h, 074h, 076h, 038h
    db 09Eh, 0D2h, 000h, 000h, 000h, 074h, 06Eh, 0D9h, 086h, 0A0h, 000h, 000h, 000h, 053h, 0D8h, 005h
    dd g_Va0111D874
    db 08Dh, 04Ch, 024h, 028h, 0D9h, 044h, 024h, 018h, 051h, 0D8h, 064h, 024h, 02Ch, 08Bh, 00Eh, 08Dh
    db 054h, 024h, 01Ch, 052h, 0D8h, 0F1h, 0D8h, 044h, 024h, 030h, 0D9h, 05Ch, 024h, 020h, 0D9h, 044h
    db 024h, 024h, 0D8h, 064h, 024h, 034h, 0D8h, 0F1h, 0D8h, 044h, 024h, 034h, 0D9h, 05Ch, 024h, 024h
    db 0DDh, 0D8h
    call ?Look_At@Matrix3D@@QAEXABVVector3@@0M@Z
    db 08Bh, 044h, 024h, 014h, 08Bh, 04Ch, 024h, 018h, 08Bh, 054h, 024h, 01Ch, 089h, 046h, 008h, 08Bh
    db 044h, 024h, 024h, 089h, 04Eh, 00Ch, 08Bh, 04Ch, 024h, 028h, 089h, 056h, 010h, 08Bh, 054h, 024h
    db 02Ch, 089h, 046h, 014h, 089h, 04Eh, 018h, 089h, 056h, 01Ch, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h
    db 0ACh, 000h, 000h, 000h, 0C2h, 004h, 000h
?d_006e0580@@YAXXZ ENDP
_TEXT$d00ae0580 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ae1700  retail @ 0x006E1700 size 33
public ?d_006e1700@@YAXXZ
?d_006e1700@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0CCh, 95h, 94h, 0FFh, 33h, 0C0h, 89h, 46h, 0Ch, 89h, 46h, 10h
    db 0C7h, 06h, 04h, 0E2h, 11h, 01h, 0C7h, 46h, 14h, 0FFh, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh
    db 0C3h
?d_006e1700@@YAXXZ ENDP

; ghidra: FUN_00ae1730  retail @ 0x006E1730 size 11
public ?d_006e1730@@YAXXZ
?d_006e1730@@YAXXZ PROC
    db 0C7h, 01h, 04h, 0E2h, 11h, 01h, 0E9h, 0FAh, 86h, 92h, 0FFh
?d_006e1730@@YAXXZ ENDP

; ghidra: FUN_00ae1ac0  retail @ 0x006E1AC0 size 17
public ?d_006e1ac0@@YAXXZ
?d_006e1ac0@@YAXXZ PROC
    db 0A1h, 48h, 80h, 2Fh, 01h, 33h, 0C9h, 89h, 48h, 40h, 89h, 48h, 3Ch, 89h, 48h, 38h
    db 0C3h
?d_006e1ac0@@YAXXZ ENDP

; ghidra: FUN_00ae1be0  retail @ 0x006E1BE0 size 88
_TEXT ENDS
_TEXT$d00ae1be0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AE1BE0 size 88
public ?d_006e1be0@@YAXXZ
?d_006e1be0@@YAXXZ PROC
    db 0A1h
    dd ?Data00EF8048@@3PAVGen006E1AC0@@A
    db 0D9h, 005h
    dd __real@497423f0
    db 083h, 0ECh, 010h, 085h, 0C0h, 074h, 040h, 005h, 084h, 000h, 000h, 000h, 0DDh, 0D8h, 08Bh, 008h
    db 08Bh, 050h, 004h, 089h, 00Ch, 024h, 08Bh, 048h, 008h, 089h, 04Ch, 024h, 008h, 0D9h, 044h, 024h
    db 008h, 0D8h, 04Ch, 024h, 01Ch, 089h, 054h, 024h, 004h, 0D9h, 044h, 024h, 004h, 08Bh, 050h, 00Ch
    db 0D8h, 04Ch, 024h, 018h, 089h, 054h, 024h, 00Ch, 0DEh, 0C1h, 0D9h, 004h, 024h, 0D8h, 04Ch, 024h
    db 014h, 0DEh, 0C1h, 0D8h, 044h, 024h, 00Ch, 083h, 0C4h, 010h, 0C2h, 00Ch, 000h
?d_006e1be0@@YAXXZ ENDP
_TEXT$d00ae1be0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ae1c80  retail @ 0x006E1C80 size 18
public ?d_006e1c80@@YAXXZ
?d_006e1c80@@YAXXZ PROC
    db 8Bh, 51h, 40h, 8Bh, 44h, 24h, 04h, 89h, 10h, 8Bh, 49h, 44h, 89h, 48h, 04h, 0C2h
    db 04h, 00h
?d_006e1c80@@YAXXZ ENDP

; ghidra: FUN_00ae1cd0  retail @ 0x006E1CD0 size 110
public ?d_006e1cd0@@YAXXZ
?d_006e1cd0@@YAXXZ PROC
    db 0A1h, 48h, 80h, 2Fh, 01h, 0D9h, 05h, 38h, 0E2h, 11h, 01h, 83h, 0ECh, 0Ch, 85h, 0C0h
    db 74h, 56h, 0DDh, 0D8h, 8Dh, 88h, 0D4h, 00h, 00h, 00h, 8Bh, 11h, 89h, 14h, 24h, 0D9h
    db 04h, 24h, 0D8h, 64h, 24h, 10h, 8Bh, 51h, 04h, 8Bh, 49h, 08h, 89h, 54h, 24h, 04h
    db 0D9h, 0E1h, 0D9h, 44h, 24h, 04h, 0D8h, 64h, 24h, 14h, 89h, 4Ch, 24h, 08h, 0D9h, 0E1h
    db 0D9h, 44h, 24h, 08h, 0D8h, 64h, 24h, 18h, 0D9h, 0E1h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h
    db 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DBh, 0DDh, 0D8h
    db 0DDh, 0D8h, 0D8h, 0A8h, 0E0h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C2h, 0Ch, 00h
?d_006e1cd0@@YAXXZ ENDP

; ghidra: FUN_00ae1d60  retail @ 0x006E1D60 size 78
public ?d_006e1d60@@YAXXZ
?d_006e1d60@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 38h, 16h, 25h, 00h, 33h, 0C0h, 89h, 46h, 38h, 89h, 46h, 3Ch
    db 89h, 46h, 40h, 89h, 46h, 44h, 89h, 46h, 48h, 89h, 46h, 4Ch, 89h, 46h, 50h, 0C7h
    db 06h, 3Ch, 0E2h, 11h, 01h, 0C6h, 46h, 54h, 01h, 89h, 46h, 58h, 89h, 46h, 5Ch, 89h
    db 46h, 60h, 89h, 46h, 64h, 88h, 46h, 68h, 88h, 46h, 69h, 88h, 46h, 6Ah, 89h, 86h
    db 0E0h, 00h, 00h, 00h, 89h, 86h, 0E4h, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_006e1d60@@YAXXZ ENDP

; ghidra: FUN_00ae1e00  retail @ 0x006E1E00 size 137
public ?d_006e1e00@@YAXXZ
?d_006e1e00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A9h, 0AFh, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 3Ch
    db 0E2h, 11h, 01h, 8Bh, 4Eh, 64h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 03h, 00h, 00h, 00h
    db 74h, 05h, 0E8h, 69h, 99h, 30h, 00h, 8Bh, 4Eh, 60h, 85h, 0C9h, 0C6h, 44h, 24h, 10h
    db 02h, 74h, 05h, 0E8h, 58h, 99h, 30h, 00h, 8Bh, 4Eh, 5Ch, 85h, 0C9h, 0C6h, 44h, 24h
    db 10h, 01h, 74h, 05h, 0E8h, 47h, 99h, 30h, 00h, 8Bh, 4Eh, 58h, 85h, 0C9h, 0C6h, 44h
    db 24h, 10h, 00h, 74h, 05h, 0E8h, 36h, 99h, 30h, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A7h, 15h, 25h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006e1e00@@YAXXZ ENDP

; ghidra: FUN_00ae2220  retail @ 0x006E2220 size 32
public ?d_006e2220@@YAXXZ
?d_006e2220@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 08h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 27h, 59h, 1Ah, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_006e2220@@YAXXZ ENDP

; ghidra: FUN_00ae2250  retail @ 0x006E2250 size 32
public ?d_006e2250@@YAXXZ
?d_006e2250@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 0Ch, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 0F7h, 58h, 1Ah, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_006e2250@@YAXXZ ENDP

; ghidra: FUN_00ae22b0  retail @ 0x006E22B0 size 32
public ?d_006e22b0@@YAXXZ
?d_006e22b0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 20h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 97h, 58h, 1Ah, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_006e22b0@@YAXXZ ENDP

; ghidra: FUN_00ae22e0  retail @ 0x006E22E0 size 35
public ?d_006e22e0@@YAXXZ
?d_006e22e0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 81h, 0C1h, 9Ch, 00h, 00h, 00h, 51h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 64h, 58h, 1Ah, 00h, 8Bh, 0C6h, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_006e22e0@@YAXXZ ENDP

; ghidra: FUN_00ae2310  retail @ 0x006E2310 size 232
public ?d_006e2310@@YAXXZ
?d_006e2310@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 23h, 0B0h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h
    db 0E8h, 0C4h, 4Dh, 92h, 0FFh, 33h, 0DBh, 68h, 0E8h, 00h, 00h, 00h, 89h, 5Ch, 24h, 1Ch
    db 0C7h, 06h, 50h, 0E2h, 11h, 01h, 0E8h, 0E5h, 0FBh, 19h, 00h, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 0Ch, 3Bh, 0C3h, 0C6h, 44h, 24h, 18h, 01h, 74h, 09h, 8Bh, 0C8h, 0E8h, 31h, 11h
    db 94h, 0FFh, 0EBh, 02h, 33h, 0C0h, 8Bh, 4Ch, 24h, 10h, 0A3h, 48h, 80h, 2Fh, 01h, 89h
    db 9Eh, 0ACh, 00h, 00h, 00h, 89h, 9Eh, 0B0h, 00h, 00h, 00h, 88h, 9Eh, 0B8h, 00h, 00h
    db 00h, 89h, 9Eh, 0BCh, 00h, 00h, 00h, 89h, 9Eh, 0C0h, 00h, 00h, 00h, 0C7h, 86h, 0B4h
    db 00h, 00h, 00h, 0FFh, 00h, 00h, 00h, 89h, 9Eh, 0C4h, 00h, 00h, 00h, 89h, 9Eh, 0C8h
    db 00h, 00h, 00h, 89h, 9Eh, 0CCh, 00h, 00h, 00h, 89h, 9Eh, 0D0h, 00h, 00h, 00h, 89h
    db 9Eh, 0D4h, 00h, 00h, 00h, 89h, 9Eh, 0D8h, 00h, 00h, 00h, 89h, 9Eh, 0DCh, 00h, 00h
    db 00h, 89h, 9Eh, 0E0h, 00h, 00h, 00h, 89h, 9Eh, 0E4h, 00h, 00h, 00h, 89h, 9Eh, 0ECh
    db 00h, 00h, 00h, 89h, 9Eh, 0F0h, 00h, 00h, 00h, 89h, 9Eh, 0F4h, 00h, 00h, 00h, 0C7h
    db 86h, 0E8h, 00h, 00h, 00h, 55h, 55h, 55h, 00h, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_006e2310@@YAXXZ ENDP

; ghidra: FUN_00ae2480  retail @ 0x006E2480 size 112
public ?d_006e2480@@YAXXZ
?d_006e2480@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 0B0h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 50h
    db 0E2h, 11h, 01h, 0A1h, 48h, 80h, 2Fh, 01h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h
    db 00h, 00h, 74h, 1Dh, 8Bh, 50h, 04h, 8Bh, 0C8h, 83h, 0C0h, 04h, 4Ah, 85h, 0D2h, 89h
    db 10h, 75h, 04h, 8Bh, 01h, 0FFh, 10h, 0C7h, 05h, 48h, 80h, 2Fh, 01h, 00h, 00h, 00h
    db 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 91h, 8Ah, 95h, 0FFh
    db 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_006e2480@@YAXXZ ENDP

; ghidra: FUN_00ae2540  retail @ 0x006E2540 size 1126
public ?d_006e2540@@YAXXZ
?d_006e2540@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 68h, 0B0h, 04h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 40h, 53h, 56h, 8Bh, 0F1h, 8Bh, 86h, 0B0h, 00h
    db 00h, 00h, 33h, 0DBh, 3Bh, 0C3h, 0Fh, 84h, 0FFh, 00h, 00h, 00h, 83h, 0F8h, 02h, 0Fh
    db 85h, 0A6h, 03h, 00h, 00h, 8Dh, 46h, 2Ch, 8Bh, 08h, 8Bh, 50h, 04h, 8Bh, 40h, 08h
    db 89h, 4Ch, 24h, 0Ch, 8Bh, 0Dh, 0E0h, 0Fh, 2Fh, 01h, 3Bh, 0CBh, 57h, 89h, 54h, 24h
    db 14h, 89h, 44h, 24h, 18h, 0Fh, 84h, 50h, 03h, 00h, 00h, 0E8h, 3Ah, 7Ah, 96h, 0FFh
    db 3Ah, 0C3h, 0Fh, 84h, 43h, 03h, 00h, 00h, 38h, 9Eh, 0B8h, 00h, 00h, 00h, 0Fh, 84h
    db 8Eh, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 14h, 8Bh, 44h, 24h, 18h
    db 89h, 8Eh, 0C4h, 00h, 00h, 00h, 89h, 96h, 0C8h, 00h, 00h, 00h, 89h, 86h, 0CCh, 00h
    db 00h, 00h, 8Bh, 8Eh, 0BCh, 00h, 00h, 00h, 49h, 8Bh, 0C1h, 3Bh, 0C3h, 89h, 8Eh, 0BCh
    db 00h, 00h, 00h, 0Fh, 8Fh, 93h, 00h, 00h, 00h, 88h, 9Eh, 0B8h, 00h, 00h, 00h, 89h
    db 9Eh, 0BCh, 00h, 00h, 00h, 89h, 9Eh, 0C0h, 00h, 00h, 00h, 89h, 9Eh, 0F4h, 00h, 00h
    db 00h, 89h, 9Eh, 0C4h, 00h, 00h, 00h, 89h, 9Eh, 0C8h, 00h, 00h, 00h, 89h, 9Eh, 0CCh
    db 00h, 00h, 00h, 38h, 5Eh, 4Ch, 74h, 24h, 8Dh, 8Eh, 0D0h, 00h, 00h, 00h, 51h, 8Bh
    db 0Dh, 58h, 80h, 2Fh, 01h, 0E8h, 86h, 05h, 94h, 0FFh, 0A1h, 0ECh, 6Eh, 30h, 01h, 3Bh
    db 0C3h, 74h, 09h, 8Bh, 96h, 0E8h, 00h, 00h, 00h, 89h, 50h, 04h, 8Bh, 0Dh, 58h, 80h
    db 2Fh, 01h, 6Ah, 01h, 8Dh, 0BEh, 0DCh, 00h, 00h, 00h, 57h, 0E8h, 0B8h, 1Fh, 95h, 0FFh
    db 89h, 9Eh, 0D0h, 00h, 00h, 00h, 89h, 9Eh, 0D4h, 00h, 00h, 00h, 89h, 9Eh, 0D8h, 00h
    db 00h, 00h, 89h, 1Fh, 89h, 5Fh, 04h, 89h, 5Fh, 08h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h
    db 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C3h, 38h, 9Eh, 81h, 00h
    db 00h, 00h, 74h, 60h, 8Dh, 4Eh, 74h, 0E8h, 29h, 0B1h, 92h, 0FFh, 0D9h, 96h, 0C0h, 00h
    db 00h, 00h, 0DCh, 1Dh, 78h, 0F3h, 0Ah, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah, 0C7h
    db 86h, 0C0h, 00h, 00h, 00h, 66h, 66h, 66h, 3Fh, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 6Ah
    db 01h, 8Dh, 0BEh, 0DCh, 00h, 00h, 00h, 57h, 0E8h, 4Bh, 1Fh, 95h, 0FFh, 0D9h, 86h, 0C0h
    db 00h, 00h, 00h, 0D9h, 86h, 0C0h, 00h, 00h, 00h, 8Bh, 86h, 0C0h, 00h, 00h, 00h, 0D9h
    db 5Fh, 04h, 53h, 89h, 07h, 0D9h, 5Fh, 08h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 57h, 0E8h
    db 24h, 1Fh, 95h, 0FFh, 38h, 9Eh, 80h, 00h, 00h, 00h, 0Fh, 84h, 7Ah, 0FFh, 0FFh, 0FFh
    db 8Bh, 4Eh, 70h, 89h, 4Ch, 24h, 0Ch, 0E8h, 04h, 67h, 1Fh, 00h, 0D8h, 5Ch, 24h, 0Ch
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 5Fh, 0FFh, 0FFh, 0FFh, 38h, 5Eh, 4Ch, 0Fh, 84h
    db 56h, 0FFh, 0FFh, 0FFh, 8Dh, 54h, 24h, 10h, 52h, 8Bh, 0CEh, 0E8h, 32h, 5Eh, 93h, 0FFh
    db 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Dh, 44h, 24h, 10h, 50h, 0E8h, 80h, 04h, 94h, 0FFh
    db 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 40h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 4Ch, 0C3h, 0E8h, 0B9h, 66h, 1Fh, 00h, 0D9h, 46h, 50h, 0D9h, 0C9h, 0D8h, 0D9h, 0DFh, 0E0h
    db 0DDh, 0D8h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 90h, 01h, 00h, 00h, 8Bh, 8Eh, 0F4h, 00h, 00h
    db 00h, 41h, 8Bh, 0C1h, 83h, 0F8h, 03h, 89h, 8Eh, 0F4h, 00h, 00h, 00h, 0Fh, 8Eh, 78h
    db 01h, 00h, 00h, 8Dh, 4Eh, 64h, 0C6h, 86h, 0B8h, 00h, 00h, 00h, 01h, 0E8h, 33h, 0B0h
    db 92h, 0FFh, 0E8h, 0B1h, 46h, 31h, 00h, 8Dh, 4Eh, 74h, 89h, 86h, 0BCh, 00h, 00h, 00h
    db 0E8h, 20h, 0B0h, 92h, 0FFh, 0D9h, 96h, 0C0h, 00h, 00h, 00h, 0DCh, 1Dh, 78h, 0F3h, 0Ah
    db 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ah, 0C7h, 86h, 0C0h, 00h, 00h, 00h, 66h, 66h
    db 66h, 3Fh, 0D9h, 86h, 0C0h, 00h, 00h, 00h, 8Dh, 0BEh, 0DCh, 00h, 00h, 00h, 0D9h, 86h
    db 0C0h, 00h, 00h, 00h, 0D9h, 86h, 0C0h, 00h, 00h, 00h, 0D9h, 1Fh, 0D9h, 5Fh, 04h, 0D9h
    db 5Fh, 08h, 8Ah, 46h, 4Ch, 3Ah, 0C3h, 74h, 50h, 8Dh, 8Eh, 0D0h, 00h, 00h, 00h, 51h
    db 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 0E8h, 84h, 0C5h, 95h, 0FFh, 8Dh, 54h, 24h, 28h, 52h
    db 8Bh, 0CEh, 0E8h, 5Bh, 5Dh, 93h, 0FFh, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Dh, 44h, 24h
    db 28h, 50h, 0E8h, 0A9h, 03h, 94h, 0FFh, 0A1h, 0ECh, 6Eh, 30h, 01h, 3Bh, 0C3h, 74h, 19h
    db 8Bh, 40h, 04h, 8Bh, 0CEh, 89h, 86h, 0E8h, 00h, 00h, 00h, 0E8h, 0DEh, 79h, 93h, 0FFh
    db 8Bh, 0Dh, 0ECh, 6Eh, 30h, 01h, 89h, 41h, 04h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 53h
    db 57h, 0E8h, 0D2h, 1Dh, 95h, 0FFh, 39h, 9Eh, 0ECh, 00h, 00h, 00h, 75h, 5Ah, 8Dh, 54h
    db 24h, 0Ch, 52h, 8Bh, 0CEh, 0E8h, 8Ch, 33h, 93h, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 89h, 5Ch
    db 24h, 54h, 0E8h, 6Dh, 0ADh, 94h, 0FFh, 84h, 0C0h, 74h, 24h, 8Bh, 44h, 24h, 0Ch, 3Bh
    db 0C3h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 0Dh, 4Ch
    db 14h, 2Fh, 01h, 50h, 0E8h, 25h, 3Eh, 93h, 0FFh, 89h, 86h, 0ECh, 00h, 00h, 00h, 8Dh
    db 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 54h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B0h, 50h, 1Ah, 00h
    db 39h, 9Eh, 0ECh, 00h, 00h, 00h, 74h, 53h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 01h
    db 8Dh, 54h, 24h, 34h, 52h, 0FFh, 50h, 20h, 0D9h, 44h, 24h, 40h, 0D8h, 44h, 24h, 34h
    db 8Bh, 8Eh, 0ECh, 00h, 00h, 00h, 53h, 53h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 53h, 8Dh
    db 44h, 24h, 28h, 0D9h, 5Ch, 24h, 28h, 50h, 0D9h, 44h, 24h, 54h, 51h, 0D8h, 44h, 24h
    db 4Ch, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h
    db 5Ch, 24h, 34h, 0E8h, 55h, 30h, 93h, 0FFh, 83h, 0C4h, 14h, 8Bh, 54h, 24h, 10h, 8Bh
    db 44h, 24h, 14h, 8Bh, 4Ch, 24h, 18h, 89h, 96h, 0C4h, 00h, 00h, 00h, 89h, 86h, 0C8h
    db 00h, 00h, 00h, 5Fh, 89h, 8Eh, 0CCh, 00h, 00h, 00h, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 40h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 4Ch, 0C3h, 0DBh, 86h, 0B4h, 00h, 00h
    db 00h, 8Dh, 56h, 2Ch, 8Bh, 02h, 8Bh, 4Ah, 04h, 0DCh, 0Dh, 0B0h, 0E2h, 11h, 01h, 8Bh
    db 52h, 08h, 89h, 44h, 24h, 0Ch, 89h, 4Ch, 24h, 10h, 0DCh, 2Dh, 40h, 0C6h, 07h, 01h
    db 89h, 54h, 24h, 14h, 0D9h, 44h, 24h, 0Ch, 0D8h, 0C9h, 0D9h, 9Eh, 0C4h, 00h, 00h, 00h
    db 0D9h, 44h, 24h, 10h, 0D8h, 0C9h, 0D9h, 9Eh, 0C8h, 00h, 00h, 00h, 0D9h, 44h, 24h, 14h
    db 0D8h, 0C9h, 0D9h, 9Eh, 0CCh, 00h, 00h, 00h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 01h
    db 0DDh, 0D8h, 0FFh, 50h, 68h, 33h, 0D2h, 0B9h, 0Ah, 00h, 00h, 00h, 0F7h, 0F1h, 85h, 0D2h
    db 0Fh, 85h, 0E5h, 0FCh, 0FFh, 0FFh, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 11h, 53h, 0FFh
    db 92h, 28h, 02h, 00h, 00h, 8Bh, 4Ch, 24h, 48h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 4Ch, 0C3h
?d_006e2540@@YAXXZ ENDP

; ghidra: FUN_00ae6a80  retail @ 0x006E6A80 size 309
_TEXT ENDS
_TEXT$d00ae6a80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AE6A80 size 309
public ?d_006e6a80@@YAXXZ
?d_006e6a80@@YAXXZ PROC
    db 053h, 056h, 08Bh, 0F1h, 08Bh, 00Dh
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 08Bh, 001h, 0FFh, 050h, 068h, 08Bh, 096h, 0F0h, 000h, 000h, 000h, 033h, 0DBh, 032h, 0C9h, 03Bh
    db 0D0h, 075h, 002h, 0B1h, 001h, 03Ah, 0CBh, 089h, 086h, 0F0h, 000h, 000h, 000h, 00Fh, 085h, 005h
    db 001h, 000h, 000h, 08Bh, 00Dh
    dd ?R2Ptr012F0FE0@@3PAVGen00049FDA@@A
    db 057h, 08Bh, 079h, 00Ch, 083h, 0FFh, 001h, 074h, 021h, 083h, 0FFh, 002h, 074h, 01Ch, 08Bh, 086h
    db 0ACh, 000h, 000h, 000h, 083h, 0F8h, 001h, 074h, 005h, 083h, 0F8h, 002h, 075h, 033h, 0C7h, 086h
    db 0B0h, 000h, 000h, 000h, 003h, 000h, 000h, 000h, 0EBh, 021h, 08Bh, 086h, 0ACh, 000h, 000h, 000h
    db 083h, 0F8h, 001h, 074h, 01Ch, 083h, 0F8h, 002h, 074h, 017h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h
    db 024h, 0C7h, 086h, 0B0h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 089h, 0BEh, 0ACh, 000h, 000h
    db 000h, 08Bh, 00Dh
    dd ?R2Ptr012F0FE0@@3PAVGen00049FDA@@A
    db 03Bh, 0CBh, 074h, 00Dh
    call ?j_00049fda@@YAXXZ
    db 03Ah, 0C3h, 00Fh, 085h, 08Dh, 000h, 000h, 000h, 038h, 09Eh, 0B8h, 000h, 000h, 000h, 00Fh, 084h
    db 081h, 000h, 000h, 000h, 088h, 09Eh, 0B8h, 000h, 000h, 000h, 089h, 09Eh, 0BCh, 000h, 000h, 000h
    db 089h, 09Eh, 0C0h, 000h, 000h, 000h, 089h, 09Eh, 0F4h, 000h, 000h, 000h, 089h, 09Eh, 0C4h, 000h
    db 000h, 000h, 089h, 09Eh, 0C8h, 000h, 000h, 000h, 089h, 09Eh, 0CCh, 000h, 000h, 000h, 038h, 05Eh
    db 04Ch, 074h, 024h, 08Bh, 00Dh
    dd ?Rva012F8058@@3PAVRva00712F60@@A
    db 08Dh, 086h, 0D0h, 000h, 000h, 000h, 050h
    call ?j_00022bb0@@YAXXZ
    db 0A1h
    dd ?R2Ptr01306EEC@@3PAVGen0003AC38@@A
    db 03Bh, 0C3h, 074h, 009h, 08Bh, 08Eh, 0E8h, 000h, 000h, 000h, 089h, 048h, 004h, 08Bh, 00Dh
    dd ?Rva012F8058@@3PAVRva00712F60@@A
    db 06Ah, 001h, 08Dh, 0BEh, 0DCh, 000h, 000h, 000h, 057h
    call ?j_00034608@@YAXXZ
    db 089h, 09Eh, 0D0h, 000h, 000h, 000h, 089h, 09Eh, 0D4h, 000h, 000h, 000h, 089h, 09Eh, 0D8h, 000h
    db 000h, 000h, 089h, 01Fh, 089h, 05Fh, 004h, 089h, 05Fh, 008h, 05Fh, 08Bh, 0CEh, 05Eh, 05Bh
    jmp ?j_0004b03d@@YAXXZ
    db 05Eh, 05Bh, 0C3h
?d_006e6a80@@YAXXZ ENDP
_TEXT$d00ae6a80 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ae6c10  retail @ 0x006E6C10 size 40
public ?d_006e6c10@@YAXXZ
?d_006e6c10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 07h, 0C3h, 94h, 0FFh, 33h, 0C0h, 89h, 46h, 20h, 89h, 46h, 2Ch
    db 0C7h, 06h, 0D0h, 0E2h, 11h, 01h, 0C7h, 46h, 24h, 09h, 00h, 00h, 00h, 0C7h, 46h, 28h
    db 0Dh, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_006e6c10@@YAXXZ ENDP

; ghidra: FUN_00ae6c50  retail @ 0x006E6C50 size 84
public ?d_006e6c50@@YAXXZ
?d_006e6c50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0B4h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0D0h
    db 0E2h, 11h, 01h, 8Bh, 46h, 2Ch, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 0Ch, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 11h, 50h, 0FFh, 52h, 28h, 8Bh, 4Ch
    db 24h, 08h, 0C7h, 06h, 98h, 0F8h, 10h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_006e6c50@@YAXXZ ENDP

; ghidra: FUN_00ae6cc0  retail @ 0x006E6CC0 size 19
public ?d_006e6cc0@@YAXXZ
?d_006e6cc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Dh, 0CCh, 12h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h, 24h, 89h, 46h
    db 2Ch, 5Eh, 0C3h
?d_006e6cc0@@YAXXZ ENDP

; ghidra: FUN_00ae6ce0  retail @ 0x006E6CE0 size 26
public ?d_006e6ce0@@YAXXZ
?d_006e6ce0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 20h, 8Bh, 49h, 2Ch, 85h, 0C9h, 74h, 09h, 8Bh, 11h
    db 89h, 44h, 24h, 04h, 0FFh, 62h, 18h, 0C2h, 04h, 00h
?d_006e6ce0@@YAXXZ ENDP

; ghidra: FUN_00ae7210  retail @ 0x006E7210 size 335
public ?d_006e7210@@YAXXZ
?d_006e7210@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 0F9h, 8Dh, 44h, 24h, 08h, 50h, 8Dh, 4Ch, 24h, 10h
    db 51h, 6Ah, 06h, 6Ah, 04h, 8Bh, 0CFh, 0E8h, 74h, 0F7h, 24h, 00h, 8Bh, 0F0h, 8Bh, 44h
    db 24h, 14h, 0D9h, 40h, 04h, 0D9h, 00h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 1Eh, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 04h, 8Bh, 15h, 0D8h, 6Dh, 34h, 01h, 89h, 56h
    db 08h, 0D9h, 40h, 0Ch, 0D9h, 00h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 5Eh, 2Ch, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 30h, 8Bh, 0Dh, 0D8h, 6Dh, 34h, 01h, 89h, 4Eh
    db 34h, 0D9h, 40h, 04h, 0D9h, 40h, 08h, 8Bh, 4Ch, 24h, 1Ch, 0D8h, 4Fh, 04h, 51h, 0D8h
    db 47h, 0Ch, 0D9h, 5Eh, 58h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 5Ch, 8Bh, 15h
    db 0D8h, 6Dh, 34h, 01h, 89h, 56h, 60h, 0D9h, 40h, 0Ch, 0D9h, 40h, 08h, 0D8h, 4Fh, 04h
    db 0D8h, 47h, 0Ch, 0D9h, 9Eh, 84h, 00h, 00h, 00h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h
    db 9Eh, 88h, 00h, 00h, 00h, 0A1h, 0D8h, 6Dh, 34h, 01h, 89h, 86h, 8Ch, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 1Ch, 0D9h, 00h, 0D9h, 56h, 48h, 0D9h, 5Eh, 1Ch, 0D9h, 40h, 08h, 0D9h
    db 96h, 0A0h, 00h, 00h, 00h, 0D9h, 5Eh, 74h, 0D9h, 40h, 04h, 0D9h, 56h, 78h, 0D9h, 5Eh
    db 20h, 0D9h, 40h, 0Ch, 0D9h, 96h, 0A4h, 00h, 00h, 00h, 0D9h, 5Eh, 4Ch, 0FFh, 15h, 98h
    db 71h, 2Dh, 01h, 8Bh, 54h, 24h, 28h, 52h, 89h, 46h, 18h, 0FFh, 15h, 98h, 71h, 2Dh
    db 01h, 89h, 46h, 44h, 8Bh, 44h, 24h, 28h, 50h, 0FFh, 15h, 98h, 71h, 2Dh, 01h, 8Bh
    db 4Ch, 24h, 34h, 89h, 46h, 70h, 51h, 0FFh, 15h, 98h, 71h, 2Dh, 01h, 89h, 86h, 9Ch
    db 00h, 00h, 00h, 8Bh, 54h, 24h, 18h, 8Bh, 44h, 24h, 1Ch, 81h, 0C2h, 00h, 00h, 01h
    db 00h, 89h, 10h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 1Ch, 81h, 0C1h, 02h, 00h, 02h
    db 00h, 89h, 4Ah, 04h, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 1Ch, 83h, 0C4h, 10h, 05h
    db 01h, 00h, 03h, 00h, 5Fh, 89h, 41h, 08h, 5Eh, 83h, 0C4h, 08h, 0C2h, 18h, 00h
?d_006e7210@@YAXXZ ENDP

; ghidra: FUN_00ae73c0  retail @ 0x006E73C0 size 294
public ?d_006e73c0@@YAXXZ
?d_006e73c0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 0F9h, 8Dh, 44h, 24h, 08h, 50h, 8Dh, 4Ch, 24h, 10h
    db 51h, 6Ah, 06h, 6Ah, 04h, 8Bh, 0CFh, 0E8h, 0C4h, 0F5h, 24h, 00h, 8Bh, 0F0h, 8Bh, 44h
    db 24h, 14h, 0D9h, 40h, 04h, 0D9h, 47h, 04h, 0D8h, 08h, 0D8h, 47h, 0Ch, 0D9h, 1Eh, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 04h, 8Bh, 15h, 0D8h, 6Dh, 34h, 01h, 89h, 56h
    db 08h, 0D9h, 40h, 0Ch, 0D9h, 47h, 04h, 0D8h, 08h, 0D8h, 47h, 0Ch, 0D9h, 5Eh, 2Ch, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 30h, 8Bh, 0Dh, 0D8h, 6Dh, 34h, 01h, 89h, 4Eh
    db 34h, 0D9h, 40h, 04h, 0D9h, 40h, 08h, 8Bh, 4Ch, 24h, 18h, 0D8h, 4Fh, 04h, 51h, 0D8h
    db 47h, 0Ch, 0D9h, 5Eh, 58h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 5Ch, 8Bh, 15h
    db 0D8h, 6Dh, 34h, 01h, 89h, 56h, 60h, 0D9h, 40h, 0Ch, 0D9h, 40h, 08h, 0D8h, 4Fh, 04h
    db 0D8h, 47h, 0Ch, 0D9h, 9Eh, 84h, 00h, 00h, 00h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h
    db 9Eh, 88h, 00h, 00h, 00h, 0A1h, 0D8h, 6Dh, 34h, 01h, 89h, 86h, 8Ch, 00h, 00h, 00h
    db 33h, 0C0h, 89h, 46h, 78h, 89h, 46h, 20h, 89h, 46h, 48h, 89h, 46h, 1Ch, 0B8h, 00h
    db 00h, 80h, 3Fh, 89h, 86h, 0A4h, 00h, 00h, 00h, 89h, 46h, 4Ch, 89h, 86h, 0A0h, 00h
    db 00h, 00h, 89h, 46h, 74h, 0FFh, 15h, 98h, 71h, 2Dh, 01h, 89h, 86h, 9Ch, 00h, 00h
    db 00h, 89h, 46h, 70h, 89h, 46h, 44h, 89h, 46h, 18h, 8Bh, 54h, 24h, 0Ch, 8Bh, 44h
    db 24h, 10h, 81h, 0C2h, 00h, 00h, 01h, 00h, 89h, 10h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h
    db 24h, 10h, 83h, 0C4h, 04h, 81h, 0C1h, 02h, 00h, 02h, 00h, 89h, 4Ah, 04h, 8Bh, 44h
    db 24h, 08h, 8Bh, 4Ch, 24h, 0Ch, 05h, 01h, 00h, 03h, 00h, 5Fh, 89h, 41h, 08h, 5Eh
    db 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_006e73c0@@YAXXZ ENDP

; ghidra: FUN_00ae7530  retail @ 0x006E7530 size 435
public ?d_006e7530@@YAXXZ
?d_006e7530@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0D9h, 43h, 04h, 55h, 8Bh, 6Ch, 24h, 18h
    db 0D8h, 65h, 04h, 57h, 8Bh, 0F9h, 0D9h, 5Ch, 24h, 0Ch, 0D9h, 45h, 00h, 0D8h, 23h, 0D9h
    db 54h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0D9h, 44h, 24h, 0Ch, 0D8h, 4Ch, 24h, 0Ch, 0DEh
    db 0C1h, 0D9h, 5Ch, 24h, 18h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 18h, 0DAh
    db 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 0Fh, 8Bh, 5Eh, 01h, 00h, 00h, 8Bh, 44h, 24h, 18h
    db 56h, 50h, 0E8h, 0BCh, 04h, 94h, 0FFh, 0D8h, 4Ch, 24h, 24h, 8Dh, 4Ch, 24h, 1Ch, 51h
    db 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 8Dh, 54h, 24h, 24h, 0D9h, 44h, 24h, 14h, 52h, 6Ah
    db 06h, 0D8h, 0C9h, 6Ah, 04h, 8Bh, 0CFh, 0D9h, 5Ch, 24h, 20h, 0D9h, 44h, 24h, 24h, 0D8h
    db 0C9h, 0D9h, 5Ch, 24h, 24h, 0DDh, 0D8h, 0E8h, 0E4h, 0F3h, 24h, 00h, 0D9h, 43h, 04h, 8Bh
    db 0F0h, 0D8h, 64h, 24h, 14h, 0D9h, 03h, 0D8h, 64h, 24h, 10h, 0D8h, 4Fh, 04h, 0D8h, 47h
    db 0Ch, 0D9h, 1Eh, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 04h, 0A1h, 0D8h, 6Dh, 34h
    db 01h, 0D9h, 44h, 24h, 14h, 89h, 46h, 08h, 0D8h, 43h, 04h, 0D9h, 44h, 24h, 10h, 0D8h
    db 03h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 5Eh, 2Ch, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h
    db 0D9h, 5Eh, 30h, 8Bh, 0Dh, 0D8h, 6Dh, 34h, 01h, 89h, 4Eh, 34h, 0D9h, 45h, 04h, 0D8h
    db 64h, 24h, 14h, 0D9h, 45h, 00h, 0D8h, 64h, 24h, 10h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch
    db 0D9h, 5Eh, 58h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 5Ch, 8Bh, 15h, 0D8h, 6Dh
    db 34h, 01h, 0D9h, 44h, 24h, 14h, 89h, 56h, 60h, 0D8h, 45h, 04h, 0D9h, 44h, 24h, 10h
    db 0D8h, 45h, 00h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 9Eh, 84h, 00h, 00h, 00h, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 9Eh, 88h, 00h, 00h, 00h, 0A1h, 0D8h, 6Dh, 34h, 01h
    db 89h, 86h, 8Ch, 00h, 00h, 00h, 33h, 0C0h, 89h, 46h, 78h, 89h, 46h, 20h, 89h, 46h
    db 48h, 89h, 46h, 1Ch, 0B8h, 00h, 00h, 80h, 3Fh, 89h, 86h, 0A4h, 00h, 00h, 00h, 8Bh
    db 4Ch, 24h, 28h, 51h, 89h, 46h, 4Ch, 89h, 86h, 0A0h, 00h, 00h, 00h, 89h, 46h, 74h
    db 0FFh, 15h, 98h, 71h, 2Dh, 01h, 89h, 86h, 9Ch, 00h, 00h, 00h, 89h, 46h, 70h, 89h
    db 46h, 44h, 89h, 46h, 18h, 8Bh, 54h, 24h, 20h, 8Bh, 44h, 24h, 24h, 81h, 0C2h, 00h
    db 00h, 01h, 00h, 89h, 10h, 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 24h, 81h, 0C1h, 02h
    db 00h, 02h, 00h, 89h, 4Ah, 04h, 8Bh, 44h, 24h, 20h, 8Bh, 4Ch, 24h, 24h, 83h, 0C4h
    db 04h, 05h, 01h, 00h, 03h, 00h, 89h, 41h, 08h, 5Eh, 5Fh, 5Dh, 5Bh, 83h, 0C4h, 08h
    db 0C2h, 10h, 00h
?d_006e7530@@YAXXZ ENDP

; ghidra: FUN_00ae7750  retail @ 0x006E7750 size 446
public ?d_006e7750@@YAXXZ
?d_006e7750@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 0D9h, 43h, 04h, 55h, 8Bh, 6Ch, 24h, 18h
    db 0D8h, 65h, 04h, 57h, 8Bh, 0F9h, 0D9h, 5Ch, 24h, 0Ch, 0D9h, 45h, 00h, 0D8h, 23h, 0D9h
    db 54h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0D9h, 44h, 24h, 0Ch, 0D8h, 4Ch, 24h, 0Ch, 0DEh
    db 0C1h, 0D9h, 5Ch, 24h, 18h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 18h, 0DAh
    db 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 0Fh, 8Bh, 69h, 01h, 00h, 00h, 8Bh, 44h, 24h, 18h
    db 56h, 50h, 0E8h, 9Ch, 02h, 94h, 0FFh, 0D8h, 4Ch, 24h, 24h, 8Dh, 4Ch, 24h, 1Ch, 51h
    db 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 8Dh, 54h, 24h, 24h, 0D9h, 44h, 24h, 14h, 52h, 6Ah
    db 06h, 0D8h, 0C9h, 6Ah, 04h, 8Bh, 0CFh, 0D9h, 5Ch, 24h, 20h, 0D9h, 44h, 24h, 24h, 0D8h
    db 0C9h, 0D9h, 5Ch, 24h, 24h, 0DDh, 0D8h, 0E8h, 0C4h, 0F1h, 24h, 00h, 0D9h, 43h, 04h, 8Bh
    db 0F0h, 0D8h, 64h, 24h, 14h, 0D9h, 03h, 0D8h, 64h, 24h, 10h, 0D8h, 4Fh, 04h, 0D8h, 47h
    db 0Ch, 0D9h, 1Eh, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 04h, 0A1h, 0D8h, 6Dh, 34h
    db 01h, 0D9h, 44h, 24h, 14h, 89h, 46h, 08h, 0D8h, 43h, 04h, 0D9h, 44h, 24h, 10h, 0D8h
    db 03h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 5Eh, 2Ch, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h
    db 0D9h, 5Eh, 30h, 8Bh, 0Dh, 0D8h, 6Dh, 34h, 01h, 89h, 4Eh, 34h, 0D9h, 45h, 04h, 0D8h
    db 64h, 24h, 14h, 0D9h, 45h, 00h, 0D8h, 64h, 24h, 10h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch
    db 0D9h, 5Eh, 58h, 0D8h, 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 5Eh, 5Ch, 8Bh, 15h, 0D8h, 6Dh
    db 34h, 01h, 0D9h, 44h, 24h, 14h, 89h, 56h, 60h, 0D8h, 45h, 04h, 0D9h, 44h, 24h, 10h
    db 0D8h, 45h, 00h, 0D8h, 4Fh, 04h, 0D8h, 47h, 0Ch, 0D9h, 9Eh, 84h, 00h, 00h, 00h, 0D8h
    db 4Fh, 08h, 0D8h, 47h, 10h, 0D9h, 9Eh, 88h, 00h, 00h, 00h, 0A1h, 0D8h, 6Dh, 34h, 01h
    db 89h, 86h, 8Ch, 00h, 00h, 00h, 33h, 0C0h, 89h, 46h, 78h, 89h, 46h, 20h, 89h, 46h
    db 48h, 89h, 46h, 1Ch, 0B8h, 00h, 00h, 80h, 3Fh, 89h, 86h, 0A4h, 00h, 00h, 00h, 8Bh
    db 4Ch, 24h, 28h, 51h, 89h, 46h, 4Ch, 89h, 86h, 0A0h, 00h, 00h, 00h, 89h, 46h, 74h
    db 0FFh, 15h, 98h, 71h, 2Dh, 01h, 8Bh, 54h, 24h, 30h, 52h, 89h, 46h, 44h, 89h, 46h
    db 18h, 0FFh, 15h, 98h, 71h, 2Dh, 01h, 89h, 86h, 9Ch, 00h, 00h, 00h, 89h, 46h, 70h
    db 8Bh, 44h, 24h, 24h, 8Bh, 4Ch, 24h, 28h, 05h, 00h, 00h, 01h, 00h, 89h, 01h, 8Bh
    db 54h, 24h, 24h, 8Bh, 44h, 24h, 28h, 81h, 0C2h, 02h, 00h, 02h, 00h, 89h, 50h, 04h
    db 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 28h, 83h, 0C4h, 08h, 81h, 0C1h, 01h, 00h, 03h
    db 00h, 89h, 4Ah, 08h, 5Eh, 5Fh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 14h, 00h
?d_006e7750@@YAXXZ ENDP

; ghidra: FUN_00ae7c60  retail @ 0x006E7C60 size 102
public ?d_006e7c60@@YAXXZ
?d_006e7c60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0B4h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Ah, 41h, 14h, 84h, 0C0h, 75h, 38h, 0E8h, 0Eh, 0B4h
    db 21h, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 54h, 24h, 18h, 6Ah, 00h
    db 50h, 8Bh, 44h, 24h, 1Ch, 51h, 52h, 50h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h
    db 0E8h, 0ABh, 0DAh, 21h, 00h, 83h, 0C4h, 14h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 5Bh, 0DEh, 21h, 00h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C2h, 10h, 00h
?d_006e7c60@@YAXXZ ENDP

; ghidra: FUN_00ae7ce0  retail @ 0x006E7CE0 size 113
public ?d_006e7ce0@@YAXXZ
?d_006e7ce0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 8Bh, 0Dh, 38h, 0D2h, 2Eh, 01h, 56h, 57h, 8Dh, 44h, 24h, 10h, 50h
    db 51h, 0FFh, 15h, 0ECh, 8Fh, 35h, 01h, 8Bh, 44h, 24h, 10h, 8Bh, 74h, 24h, 18h, 8Bh
    db 4Ch, 24h, 14h, 8Bh, 7Ch, 24h, 1Ch, 8Dh, 54h, 24h, 08h, 2Bh, 0F0h, 89h, 44h, 24h
    db 08h, 0A1h, 38h, 0D2h, 2Eh, 01h, 52h, 50h, 2Bh, 0F9h, 89h, 4Ch, 24h, 14h, 0FFh, 15h
    db 0ACh, 8Fh, 35h, 01h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 44h, 24h, 08h, 89h, 4Ch, 24h, 14h
    db 03h, 0CFh, 89h, 4Ch, 24h, 1Ch, 89h, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 10h, 03h, 0C6h
    db 51h, 89h, 44h, 24h, 1Ch, 0FFh, 15h, 0B0h, 8Fh, 35h, 01h, 5Fh, 5Eh, 83h, 0C4h, 18h
    db 0C3h
?d_006e7ce0@@YAXXZ ENDP

; ghidra: FUN_00ae7f00  retail @ 0x006E7F00 size 327
public ?d_006e7f00@@YAXXZ
?d_006e7f00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 0B4h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 0E8h, 6Dh
    db 0B1h, 21h, 00h, 8Bh, 5Ch, 24h, 40h, 8Bh, 4Ch, 24h, 3Ch, 8Bh, 7Ch, 24h, 38h, 8Bh
    db 6Ch, 24h, 34h, 6Ah, 01h, 0Fh, 0B6h, 0C3h, 50h, 51h, 57h, 55h, 0C7h, 44h, 24h, 40h
    db 00h, 00h, 00h, 00h, 0E8h, 77h, 52h, 21h, 00h, 83h, 0C4h, 14h, 3Ch, 01h, 75h, 7Fh
    db 85h, 0EDh, 89h, 6Ch, 24h, 40h, 0DBh, 44h, 24h, 40h, 0C7h, 44h, 24h, 14h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 7Dh, 06h, 0D8h, 05h, 58h, 53h
    db 07h, 01h, 85h, 0FFh, 0D9h, 5Ch, 24h, 1Ch, 89h, 7Ch, 24h, 40h, 0DBh, 44h, 24h, 40h
    db 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 8Eh, 64h, 01h, 00h, 00h, 0D9h, 5Ch
    db 24h, 20h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 0B4h, 0BAh, 24h, 00h, 8Bh, 44h, 24h, 3Ch
    db 53h, 50h, 57h, 55h, 8Bh, 0CEh, 0E8h, 0F6h, 0F3h, 91h, 0FFh, 0C7h, 44h, 24h, 2Ch, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 58h, 0DBh, 21h, 00h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 8Bh, 4Ch
    db 24h, 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 20h, 0C2h, 10h, 00h, 8Bh
    db 16h, 6Ah, 01h, 8Bh, 0CEh, 0FFh, 52h, 40h, 8Bh, 16h, 0Fh, 0B6h, 0C0h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 38h, 50h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 30h, 8Bh, 16h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 2Ch, 50h, 0E8h, 0C7h, 51h, 21h, 00h, 8Bh, 06h, 83h, 0C4h, 14h, 8Bh, 0CEh
    db 0FFh, 50h, 40h, 8Bh, 16h, 8Bh, 0CEh, 50h, 0FFh, 52h, 38h, 50h, 8Bh, 06h, 8Bh, 0CEh
    db 0FFh, 50h, 30h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 2Ch, 50h, 8Bh, 0CEh, 0E8h, 7Eh
    db 0F3h, 91h, 0FFh, 0C7h, 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0E0h, 0DAh, 21h, 00h
    db 8Bh, 4Ch, 24h, 24h, 5Fh, 5Eh, 5Dh, 32h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 20h, 0C2h, 10h, 00h
?d_006e7f00@@YAXXZ ENDP

; ghidra: FUN_00ae80a0  retail @ 0x006E80A0 size 121
public ?d_006e80a0@@YAXXZ
?d_006e80a0@@YAXXZ PROC
    db 83h, 0ECh, 14h, 8Bh, 44h, 24h, 18h, 56h, 50h, 8Bh, 0F1h, 0E8h, 11h, 93h, 95h, 0FFh
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 30h, 85h, 0C0h, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h
    db 1Ch, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 06h, 0D9h, 5Ch, 24h, 1Ch, 8Bh
    db 0CEh, 0FFh, 50h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 04h, 0DBh, 44h, 24h, 04h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 4Ch, 24h, 1Ch, 0D9h, 5Ch, 24h, 10h, 8Dh, 54h
    db 24h, 08h, 89h, 4Ch, 24h, 14h, 8Bh, 8Eh, 64h, 01h, 00h, 00h, 52h, 0C7h, 44h, 24h
    db 0Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 3Eh, 0B9h
    db 24h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006e80a0@@YAXXZ ENDP

; ghidra: FUN_00ae8140  retail @ 0x006E8140 size 121
public ?d_006e8140@@YAXXZ
?d_006e8140@@YAXXZ PROC
    db 83h, 0ECh, 14h, 8Bh, 44h, 24h, 18h, 56h, 50h, 8Bh, 0F1h, 0E8h, 0C1h, 0CAh, 94h, 0FFh
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 30h, 85h, 0C0h, 89h, 44h, 24h, 1Ch, 0DBh, 44h, 24h
    db 1Ch, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 06h, 0D9h, 5Ch, 24h, 1Ch, 8Bh
    db 0CEh, 0FFh, 50h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 04h, 0DBh, 44h, 24h, 04h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 4Ch, 24h, 1Ch, 0D9h, 5Ch, 24h, 10h, 8Dh, 54h
    db 24h, 08h, 89h, 4Ch, 24h, 14h, 8Bh, 8Eh, 64h, 01h, 00h, 00h, 52h, 0C7h, 44h, 24h
    db 0Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 9Eh, 0B8h
    db 24h, 00h, 5Eh, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006e8140@@YAXXZ ENDP

; ghidra: FUN_00ae8310  retail @ 0x006E8310 size 555
_TEXT ENDS
_TEXT$d00ae8310 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AE8310 size 555
public ?d_006e8310@@YAXXZ
?d_006e8310@@YAXXZ PROC
    db 083h, 0ECh, 048h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 056h, 08Bh, 0F1h, 0D9h, 046h, 008h, 089h, 074h, 024h, 018h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 044h, 00Fh, 08Bh, 006h, 002h, 000h, 000h, 08Bh, 00Dh
    dd ?ClientAt012F1464@@3PAVClient0009A580@@A
    db 08Bh, 001h, 0FFh, 050h, 068h, 02Bh, 046h, 004h, 085h, 0C0h, 089h, 044h, 024h, 024h, 0DBh, 044h
    db 024h, 024h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 00Dh
    dd g_Va012BAA30
    db 0D8h, 076h, 008h, 0D9h, 054h, 024h, 004h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ch, 0C7h, 046h, 008h, 000h, 000h, 000h, 000h, 05Eh, 083h
    db 0C4h, 048h, 0C3h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 006h, 083h, 0F8h, 001h, 0D8h, 064h, 024h, 004h, 0D9h, 05Ch, 024h, 008h, 075h, 010h, 0D9h
    db 044h, 024h, 008h, 08Bh, 04Ch, 024h, 004h, 0D9h, 05Ch, 024h, 004h, 089h, 04Ch, 024h, 008h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 088h, 018h, 002h, 000h, 000h, 089h, 04Ch, 024h, 024h, 06Bh, 0C9h, 06Ch, 003h, 0C1h, 08Dh
    db 088h, 024h, 002h, 000h, 000h, 08Dh, 090h, 0ACh, 004h, 000h, 000h, 005h, 034h, 007h, 000h, 000h
    db 089h, 044h, 024h, 00Ch, 083h, 0C0h, 014h, 089h, 044h, 024h, 010h, 08Bh, 0C2h, 02Bh, 0C1h, 089h
    db 044h, 024h, 01Ch, 08Bh, 044h, 024h, 00Ch, 053h, 02Bh, 0C1h, 08Dh, 071h, 00Ch, 08Bh, 04Ch, 024h
    db 010h, 055h, 033h, 0DBh, 033h, 0EDh, 02Bh, 0CAh, 057h, 08Dh, 07Ah, 010h, 089h, 044h, 024h, 02Ch
    db 089h, 04Ch, 024h, 020h, 0EBh, 00Ah, 08Bh, 04Ch, 024h, 020h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 08Bh, 044h, 024h, 024h, 0D9h, 044h, 024h, 014h, 0D8h, 048h, 014h, 08Bh, 054h, 024h, 028h, 0D9h
    db 044h, 024h, 010h, 0D8h, 04Eh, 008h, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 054h, 0D9h, 044h, 024h, 014h
    db 0D8h, 048h, 00Ch, 0D9h, 044h, 024h, 010h, 0D8h, 00Eh, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 04Ch, 0D9h
    db 044h, 024h, 014h, 0D8h, 048h, 010h, 08Bh, 044h, 024h, 01Ch, 0D9h, 05Ch, 024h, 018h, 0D9h, 044h
    db 024h, 010h, 0D8h, 04Eh, 004h, 0D8h, 044h, 024h, 018h, 0D9h, 05Ch, 024h, 050h, 0D9h, 044h, 024h
    db 010h, 0D8h, 04Fh, 004h, 0D8h, 0C2h, 0D9h, 05Ch, 024h, 03Ch, 0D9h, 044h, 024h, 010h, 0D8h, 00Ch
    db 032h, 08Bh, 054h, 024h, 02Ch, 0D8h, 0C1h, 0D9h, 05Ch, 024h, 034h, 0D9h, 044h, 024h, 010h, 0D8h
    db 00Fh, 0D8h, 044h, 024h, 018h, 0D9h, 05Ch, 024h, 038h, 0D9h, 044h, 024h, 010h, 0D8h, 008h, 0D8h
    db 0C2h, 0D9h, 05Ch, 024h, 048h, 0D9h, 044h, 024h, 010h, 0D8h, 00Ch, 032h, 08Bh, 054h, 024h, 03Ch
    db 052h, 08Bh, 054h, 024h, 03Ch, 0D8h, 0C1h, 052h, 08Bh, 054h, 024h, 03Ch, 052h, 0D9h, 05Ch, 024h
    db 04Ch, 053h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 020h, 0D8h, 00Ch, 039h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 0D8h, 044h, 024h, 028h, 0D9h, 05Ch, 024h, 054h, 0FFh, 090h, 0A0h, 000h, 000h, 000h
    db 08Bh, 054h, 024h, 048h, 08Bh, 00Dh
    dd ?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A
    db 08Bh, 001h, 052h, 08Bh, 054h, 024h, 048h, 052h, 08Bh, 054h, 024h, 048h, 052h, 053h, 0FFh, 090h
    db 0A4h, 000h, 000h, 000h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 054h, 024h, 04Ch, 08Dh, 08Ch, 028h, 0E0h, 009h, 000h, 000h, 08Bh, 044h, 024h, 050h, 089h
    db 011h, 08Bh, 054h, 024h, 054h, 089h, 041h, 004h, 089h, 051h, 008h, 08Bh, 054h, 024h, 01Ch, 043h
    db 083h, 0C6h, 024h, 083h, 0C7h, 024h, 083h, 0C2h, 024h, 083h, 0C5h, 00Ch, 083h, 0FDh, 024h, 089h
    db 054h, 024h, 01Ch, 00Fh, 08Ch, 0D7h, 0FEh, 0FFh, 0FFh, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012f7fe0@@3PAVBfmeGlobal_012f7fe0@@A
    db 085h, 0C9h, 05Fh, 05Dh, 05Bh, 074h, 00Ah, 08Bh, 044h, 024h, 024h, 050h
    call ?j_00040bc9@@YAXXZ
    db 05Eh, 083h, 0C4h, 048h, 0C3h
?d_006e8310@@YAXXZ ENDP
_TEXT$d00ae8310 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ae85d0  retail @ 0x006E85D0 size 20
public ?d_006e85d0@@YAXXZ
?d_006e85d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0DBh, 27h, 96h, 0FFh, 8Dh, 8Eh, 78h, 02h, 00h, 00h, 5Eh, 0E9h
    db 18h, 72h, 94h, 0FFh
?d_006e85d0@@YAXXZ ENDP

; ghidra: FUN_00ae8790  retail @ 0x006E8790 size 84
public ?d_006e8790@@YAXXZ
?d_006e8790@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 56h, 57h, 0BFh, 03h, 00h, 00h, 00h, 8Dh, 0B1h, 8Ch, 01h, 00h
    db 00h, 0BBh, 0Fh, 00h, 00h, 00h, 8Bh, 0Eh, 8Bh, 01h, 68h, 00h, 00h, 00h, 0FFh, 6Ah
    db 0FFh, 0FFh, 50h, 28h, 8Bh, 0Eh, 8Bh, 11h, 6Ah, 01h, 6Ah, 01h, 57h, 6Ah, 03h, 0FFh
    db 52h, 38h, 8Bh, 0Eh, 8Bh, 01h, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 54h, 24h, 14h, 52h
    db 0FFh, 50h, 3Ch, 03h, 7Ch, 24h, 0Ch, 83h, 0C6h, 04h, 4Bh, 75h, 0C9h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 08h, 0C3h
?d_006e8790@@YAXXZ ENDP

; ghidra: FUN_00ae8800  retail @ 0x006E8800 size 762
public ?d_006e8800@@YAXXZ
?d_006e8800@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 56h, 89h, 4Ch, 24h, 14h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h
    db 57h, 0C7h, 44h, 24h, 14h, 03h, 00h, 00h, 00h, 0C6h, 44h, 24h, 13h, 00h, 33h, 0DBh
    db 83h, 0FBh, 0Ah, 0Fh, 8Ch, 3Fh, 01h, 00h, 00h, 83h, 0FBh, 10h, 0Fh, 8Fh, 36h, 01h
    db 00h, 00h, 85h, 0C9h, 0Fh, 84h, 96h, 02h, 00h, 00h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 8Dh, 73h, 0F7h, 56h, 0E8h, 0B0h, 0BDh, 94h, 0FFh, 8Bh, 0E8h, 8Ah, 45h, 10h, 84h, 0C0h
    db 0Fh, 85h, 74h, 02h, 00h, 00h, 83h, 7Dh, 14h, 01h, 75h, 0Ah, 0B8h, 0E1h, 0A0h, 0C8h
    db 0FFh, 0E9h, 96h, 00h, 00h, 00h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 8Bh, 01h, 0FFh, 90h
    db 8Ch, 00h, 00h, 00h, 84h, 0C0h, 74h, 7Fh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 79h
    db 3Ch, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 8Bh, 11h, 56h, 0FFh, 92h, 0D8h, 00h, 00h, 00h
    db 0B9h, 0Ah, 00h, 00h, 00h, 2Bh, 0CFh, 03h, 0C1h, 83h, 0F8h, 08h, 77h, 3Fh, 0FFh, 24h
    db 85h, 0FCh, 8Ah, 0AEh, 00h, 0B8h, 0A0h, 0FFh, 0FFh, 0FFh, 0EBh, 50h, 0B8h, 0A0h, 0FFh, 0A0h
    db 0FFh, 0EBh, 49h, 0B8h, 0FFh, 0A0h, 0A0h, 0FFh, 0EBh, 42h, 0B8h, 0FFh, 96h, 96h, 0FFh, 0EBh
    db 3Bh, 0B8h, 0FFh, 8Ch, 8Ch, 0FFh, 0EBh, 34h, 0B8h, 0FFh, 82h, 82h, 0FFh, 0EBh, 2Dh, 0B8h
    db 0FFh, 78h, 78h, 0FFh, 0EBh, 26h, 0B8h, 0FFh, 6Eh, 6Eh, 0FFh, 0EBh, 1Fh, 0A0h, 0A9h, 81h
    db 2Fh, 01h, 0F6h, 0D8h, 0C6h, 44h, 24h, 13h, 01h, 1Bh, 0C0h, 25h, 0FFh, 0FFh, 00h, 00h
    db 05h, 00h, 00h, 0FFh, 0FFh, 0EBh, 05h, 0B8h, 0A0h, 0C8h, 0C8h, 0FFh, 83h, 7Dh, 00h, 00h
    db 74h, 0Ah, 0B8h, 64h, 64h, 0A0h, 0C8h, 0E9h, 73h, 01h, 00h, 00h, 8Bh, 4Dh, 14h, 85h
    db 0C9h, 75h, 26h, 8Bh, 4Dh, 0Ch, 85h, 0C9h, 74h, 0Ah, 0B8h, 0C8h, 0C8h, 64h, 0FFh, 0E9h
    db 5Bh, 01h, 00h, 00h, 8Bh, 4Dh, 08h, 85h, 0C9h, 0Fh, 84h, 50h, 01h, 00h, 00h, 0B8h
    db 64h, 96h, 0C8h, 0FFh, 0E9h, 46h, 01h, 00h, 00h, 83h, 0F9h, 01h, 0Fh, 85h, 3Dh, 01h
    db 00h, 00h, 8Bh, 4Dh, 0Ch, 85h, 0C9h, 74h, 0Ah, 0B8h, 0FFh, 0A0h, 0DCh, 0FFh, 0E9h, 2Ch
    db 01h, 00h, 00h, 8Bh, 4Dh, 08h, 85h, 0C9h, 0Fh, 84h, 21h, 01h, 00h, 00h, 0B8h, 0AFh
    db 64h, 96h, 0FFh, 0E9h, 17h, 01h, 00h, 00h, 83h, 0FBh, 08h, 0Fh, 85h, 0B9h, 00h, 00h
    db 00h, 85h, 0C9h, 0Fh, 84h, 03h, 01h, 00h, 00h, 8Bh, 11h, 0FFh, 92h, 8Ch, 00h, 00h
    db 00h, 84h, 0C0h, 0Fh, 85h, 0F3h, 00h, 00h, 00h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 8Bh
    db 01h, 0FFh, 90h, 0CCh, 00h, 00h, 00h, 83h, 0F8h, 09h, 77h, 74h, 0FFh, 24h, 85h, 20h
    db 8Bh, 0AEh, 00h, 0B8h, 0A0h, 0FFh, 0FFh, 0FFh, 0E9h, 0D2h, 00h, 00h, 00h, 0B8h, 0A0h, 0FFh
    db 0A0h, 0FFh, 0E9h, 0C8h, 00h, 00h, 00h, 0B8h, 0FFh, 0A0h, 0A0h, 0FFh, 0E9h, 0BEh, 00h, 00h
    db 00h, 0B8h, 0FFh, 96h, 96h, 0FFh, 0E9h, 0B4h, 00h, 00h, 00h, 0B8h, 0FFh, 8Ch, 8Ch, 0FFh
    db 0E9h, 0AAh, 00h, 00h, 00h, 0B8h, 0FFh, 82h, 82h, 0FFh, 0E9h, 0A0h, 00h, 00h, 00h, 0B8h
    db 0FFh, 78h, 78h, 0FFh, 0E9h, 96h, 00h, 00h, 00h, 0B8h, 0FFh, 6Eh, 6Eh, 0FFh, 0E9h, 8Ch
    db 00h, 00h, 00h, 8Bh, 0Dh, 54h, 80h, 2Fh, 01h, 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh
    db 42h, 3Ch, 83h, 0C1h, 05h, 3Bh, 0C8h, 73h, 07h, 0B8h, 00h, 00h, 0FFh, 0FFh, 0EBh, 6Fh
    db 0A0h, 0A9h, 81h, 2Fh, 01h, 0F6h, 0D8h, 0C6h, 44h, 24h, 13h, 01h, 1Bh, 0C0h, 25h, 0FFh
    db 0FFh, 00h, 00h, 05h, 00h, 00h, 0FFh, 0FFh, 0EBh, 55h, 83h, 0FBh, 09h, 75h, 2Ah, 0A1h
    db 54h, 80h, 2Fh, 01h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 83h, 0C0h, 05h
    db 3Bh, 0C2h, 72h, 38h, 0A0h, 0A9h, 81h, 2Fh, 01h, 0F6h, 0D8h, 1Bh, 0C0h, 25h, 0FFh, 0FFh
    db 00h, 00h, 05h, 00h, 00h, 0FFh, 0FFh, 0EBh, 26h, 83h, 0FBh, 07h, 75h, 1Eh, 85h, 0C9h
    db 74h, 13h, 8Bh, 11h, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 84h, 0C0h, 74h, 07h, 0B8h, 0FFh
    db 0C8h, 0C8h, 0FFh, 0EBh, 0Ah, 0B8h, 0C8h, 0C8h, 0FFh, 0FFh, 0EBh, 03h, 83h, 0C8h, 0FFh, 8Bh
    db 7Ch, 24h, 18h, 8Bh, 8Ch, 9Fh, 2Ch, 02h, 00h, 00h, 8Bh, 11h, 68h, 00h, 00h, 00h
    db 0FFh, 50h, 0FFh, 52h, 28h, 8Bh, 74h, 24h, 14h, 8Bh, 8Ch, 9Fh, 2Ch, 02h, 00h, 00h
    db 8Bh, 01h, 6Ah, 01h, 6Ah, 01h, 56h, 6Ah, 03h, 0FFh, 50h, 38h, 8Bh, 8Ch, 9Fh, 2Ch
    db 02h, 00h, 00h, 8Bh, 11h, 8Dh, 44h, 24h, 1Ch, 50h, 8Dh, 44h, 24h, 24h, 50h, 0FFh
    db 52h, 3Ch, 03h, 74h, 24h, 1Ch, 89h, 74h, 24h, 14h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h
    db 43h, 83h, 0FBh, 11h, 0Fh, 8Ch, 46h, 0FDh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h
    db 5Fh, 5Eh, 5Dh, 5Bh, 74h, 10h, 0A0h, 0A9h, 81h, 2Fh, 01h, 84h, 0C0h, 0Fh, 94h, 0C1h
    db 88h, 0Dh, 0A9h, 81h, 2Fh, 01h, 83h, 0C4h, 14h, 0C3h
?d_006e8800@@YAXXZ ENDP

; ghidra: FUN_00ae8c20  retail @ 0x006E8C20 size 198
public ?d_006e8c20@@YAXXZ
?d_006e8c20@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 56h, 57h, 0BBh, 03h, 00h, 00h, 00h, 83h, 0CEh, 0FFh, 0BDh
    db 0FCh, 0FFh, 0FFh, 0FFh, 8Dh, 0B9h, 0C8h, 01h, 00h, 00h, 0C7h, 44h, 24h, 10h, 19h, 00h
    db 00h, 00h, 83h, 3Fh, 00h, 0Fh, 84h, 80h, 00h, 00h, 00h, 83h, 0FDh, 13h, 77h, 4Bh
    db 0FFh, 24h, 0ADh, 0E8h, 8Ch, 0AEh, 00h, 0BEh, 96h, 96h, 0FFh, 0FFh, 0EBh, 3Dh, 0BEh, 0FFh
    db 0A0h, 0A0h, 0FFh, 0EBh, 36h, 0BEh, 64h, 0FFh, 64h, 0FFh, 0EBh, 2Fh, 0BEh, 00h, 0FFh, 0FFh
    db 0FFh, 0EBh, 28h, 0BEh, 00h, 0FFh, 0FFh, 0E1h, 0EBh, 21h, 0BEh, 00h, 0FFh, 0FFh, 0D7h, 0EBh
    db 1Ah, 0BEh, 00h, 0FFh, 0FFh, 0CDh, 0EBh, 13h, 0BEh, 00h, 0FFh, 0FFh, 0C3h, 0EBh, 0Ch, 0BEh
    db 64h, 0FFh, 64h, 0E1h, 0EBh, 05h, 0BEh, 00h, 0FFh, 0FFh, 0B9h, 8Bh, 0Fh, 8Bh, 01h, 68h
    db 00h, 00h, 00h, 0FFh, 56h, 0FFh, 50h, 28h, 8Bh, 0Fh, 8Bh, 11h, 6Ah, 01h, 6Ah, 01h
    db 53h, 6Ah, 03h, 0FFh, 52h, 38h, 8Bh, 0Fh, 8Bh, 01h, 8Dh, 54h, 24h, 14h, 52h, 8Dh
    db 54h, 24h, 1Ch, 52h, 0FFh, 50h, 3Ch, 03h, 5Ch, 24h, 14h, 8Bh, 44h, 24h, 10h, 83h
    db 0C7h, 04h, 45h, 48h, 89h, 44h, 24h, 10h, 0Fh, 85h, 64h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_006e8c20@@YAXXZ ENDP

; ghidra: FUN_00ae8d80  retail @ 0x006E8D80 size 42
public ?d_006e8d80@@YAXXZ
?d_006e8d80@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 8Eh, 70h, 02h, 00h, 00h, 8Bh, 01h, 68h, 00h, 00h, 00h, 0FFh
    db 6Ah, 0FFh, 0FFh, 50h, 28h, 8Bh, 8Eh, 70h, 02h, 00h, 00h, 8Bh, 11h, 6Ah, 01h, 6Ah
    db 01h, 6Ah, 14h, 6Ah, 03h, 0FFh, 52h, 38h, 5Eh, 0C3h
?d_006e8d80@@YAXXZ ENDP

; ghidra: FUN_00ae8df0  retail @ 0x006E8DF0 size 83
public ?d_006e8df0@@YAXXZ
?d_006e8df0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 2Ch, 3Dh, 0F0h, 0F9h, 42h, 00h, 75h, 06h, 5Eh, 0E9h, 9Dh
    db 96h, 91h, 0FFh, 3Dh, 3Fh, 41h, 43h, 00h, 75h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 25h, 0E7h
    db 95h, 0FFh, 3Dh, 79h, 0D7h, 40h, 00h, 75h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 0B7h, 6Ah, 94h
    db 0FFh, 8Bh, 4Eh, 28h, 85h, 0C9h, 74h, 19h, 85h, 0C0h, 74h, 15h, 8Bh, 01h, 0FFh, 50h
    db 2Ch, 8Bh, 4Eh, 30h, 8Bh, 56h, 28h, 6Ah, 00h, 51h, 52h, 0FFh, 56h, 2Ch, 83h, 0C4h
    db 0Ch, 5Eh, 0C3h
?d_006e8df0@@YAXXZ ENDP

; ghidra: FUN_00ae8e60  retail @ 0x006E8E60 size 556
public ?d_006e8e60@@YAXXZ
?d_006e8e60@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 6Ah, 0FFh, 68h, 0F8h, 0B4h, 04h, 01h, 64h, 0A1h, 00h
    db 00h, 00h, 00h, 50h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 5Ch, 53h, 55h
    db 56h, 57h, 8Dh, 44h, 24h, 48h, 50h, 8Bh, 0F9h, 0FFh, 15h, 0B8h, 8Eh, 35h, 01h, 8Bh
    db 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0DBh, 41h, 5Ch, 8Bh, 1Dh, 0B4h, 8Eh, 35h, 01h, 0C7h, 44h
    db 24h, 24h, 01h, 00h, 00h, 00h, 0BDh, 08h, 00h, 00h, 00h, 0D8h, 0Dh, 0ECh, 66h, 07h
    db 01h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 1Ch, 8Dh, 49h, 00h
    db 8Dh, 45h, 0FDh, 83h, 0F8h, 05h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 0Fh, 87h
    db 7Ch, 01h, 00h, 00h, 0FFh, 24h, 85h, 8Ch, 90h, 0AEh, 00h, 0BDh, 07h, 00h, 00h, 00h
    db 0EBh, 0Ch, 0BDh, 06h, 00h, 00h, 00h, 0EBh, 05h, 0BDh, 03h, 00h, 00h, 00h, 8Bh, 15h
    db 0C8h, 0D5h, 2Eh, 01h, 89h, 6Ah, 54h, 0A1h, 58h, 80h, 2Fh, 01h, 0C6h, 80h, 28h, 01h
    db 00h, 00h, 01h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 11h, 6Ah, 00h, 0FFh, 92h, 20h
    db 02h, 00h, 00h, 0DFh, 6Ch, 24h, 48h, 33h, 0F6h, 0DDh, 5Ch, 24h, 50h, 8Dh, 49h, 00h
    db 8Dh, 44h, 24h, 38h, 50h, 0FFh, 0D3h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 92h, 80h, 00h, 00h
    db 00h, 0E8h, 5Ah, 0A1h, 21h, 00h, 6Ah, 00h, 6Ah, 00h, 8Dh, 44h, 24h, 64h, 50h, 6Ah
    db 01h, 6Ah, 01h, 0C7h, 84h, 24h, 88h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 70h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 74h, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 78h, 00h, 00h, 00h, 00h, 0E8h, 15h, 53h, 21h, 00h, 83h, 0C4h, 14h, 3Ch, 01h
    db 75h, 11h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 7Ch, 6Ah, 01h, 0E8h, 00h, 49h, 21h, 00h
    db 83h, 0C4h, 04h, 8Dh, 44h, 24h, 30h, 50h, 0FFh, 0D3h, 8Bh, 54h, 24h, 38h, 8Bh, 4Ch
    db 24h, 30h, 8Bh, 44h, 24h, 3Ch, 2Bh, 0CAh, 8Bh, 54h, 24h, 34h, 1Bh, 0D0h, 83h, 0FEh
    db 05h, 89h, 4Ch, 24h, 40h, 89h, 54h, 24h, 44h, 0DFh, 6Ch, 24h, 40h, 0DCh, 74h, 24h
    db 50h, 0D9h, 5Ch, 24h, 28h, 7Ch, 2Fh, 83h, 0FEh, 06h, 0D9h, 44h, 24h, 28h, 0D8h, 44h
    db 24h, 18h, 0D9h, 5Ch, 24h, 18h, 7Eh, 1Eh, 8Dh, 46h, 0FCh, 89h, 44h, 24h, 2Ch, 0DBh
    db 44h, 24h, 2Ch, 0D8h, 7Ch, 24h, 28h, 0D9h, 44h, 24h, 1Ch, 0DCh, 0C0h, 0DEh, 0D9h, 0DFh
    db 0E0h, 0F6h, 0C4h, 05h, 7Bh, 19h, 0C7h, 44h, 24h, 74h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 1Dh
    db 0CBh, 21h, 00h, 46h, 83h, 0FEh, 14h, 0Fh, 8Ch, 23h, 0FFh, 0FFh, 0FFh, 0EBh, 0Eh, 46h
    db 0C7h, 44h, 24h, 74h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 03h, 0CBh, 21h, 00h, 83h, 0C6h, 0FBh
    db 89h, 74h, 24h, 2Ch, 0DBh, 44h, 24h, 2Ch, 8Bh, 44h, 24h, 20h, 40h, 89h, 44h, 24h
    db 20h, 0D8h, 7Ch, 24h, 18h, 0D8h, 54h, 24h, 1Ch, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Ah
    db 39h, 6Ch, 24h, 24h, 7Dh, 04h, 89h, 6Ch, 24h, 24h, 0D8h, 5Ch, 24h, 1Ch, 0DFh, 0E0h
    db 0F6h, 0C4h, 05h, 7Bh, 0Bh, 83h, 7Ch, 24h, 20h, 0Ah, 0Fh, 8Ch, 70h, 0FEh, 0FFh, 0FFh
    db 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 8Bh, 4Ch, 24h, 24h, 89h, 4Ah, 54h, 0A1h, 58h, 80h
    db 2Fh, 01h, 0C6h, 80h, 28h, 01h, 00h, 00h, 00h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 8Bh
    db 11h, 6Ah, 00h, 0FFh, 92h, 20h, 02h, 00h, 00h, 8Bh, 4Ch, 24h, 6Ch, 5Fh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Eh, 5Dh, 5Bh, 8Bh, 0E5h, 5Dh, 0C3h
?d_006e8e60@@YAXXZ ENDP

; ghidra: FUN_00ae9190  retail @ 0x006E9190 size 95
public ?d_006e9190@@YAXXZ
?d_006e9190@@YAXXZ PROC
    db 0A1h, 0C8h, 0D5h, 2Eh, 01h, 56h, 8Bh, 0F1h, 8Ah, 48h, 58h, 84h, 0C9h, 74h, 25h, 8Bh
    db 0Dh, 98h, 08h, 2Fh, 01h, 8Ah, 81h, 93h, 00h, 00h, 00h, 84h, 0C0h, 74h, 15h, 8Bh
    db 96h, 7Ch, 01h, 00h, 00h, 8Bh, 0Dh, 0ACh, 0D5h, 2Eh, 01h, 52h, 0E8h, 0F4h, 0F1h, 95h
    db 0FFh, 50h, 0EBh, 02h, 6Ah, 04h, 8Bh, 0Dh, 0ACh, 0D5h, 2Eh, 01h, 0E8h, 36h, 6Eh, 95h
    db 0FFh, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 83h, 78h, 54h, 08h, 75h, 11h, 0A1h, 0E0h, 7Fh, 2Fh
    db 01h, 85h, 0C0h, 74h, 08h, 8Bh, 0CEh, 5Eh, 0E9h, 60h, 8Dh, 94h, 0FFh, 5Eh, 0C3h
?d_006e9190@@YAXXZ ENDP

; ghidra: FUN_00ae9210  retail @ 0x006E9210 size 576
public ?d_006e9210@@YAXXZ
?d_006e9210@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Ah, 86h, 0D4h, 00h, 00h, 00h, 84h, 0C0h, 57h, 0Fh
    db 84h, 3Bh, 01h, 00h, 00h, 8Bh, 86h, 0D0h, 00h, 00h, 00h, 0B9h, 00h, 00h, 80h, 3Fh
    db 3Bh, 0C1h, 74h, 3Bh, 8Bh, 44h, 24h, 14h, 2Bh, 86h, 0D8h, 00h, 00h, 00h, 85h, 0C0h
    db 89h, 44h, 24h, 14h, 0DBh, 44h, 24h, 14h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h
    db 0D8h, 0Dh, 0ECh, 66h, 07h, 01h, 0D9h, 96h, 0D0h, 00h, 00h, 00h, 0D8h, 1Dh, 34h, 53h
    db 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 89h, 8Eh, 0D0h, 00h, 00h, 00h, 0D9h
    db 86h, 0D0h, 00h, 00h, 00h, 0D8h, 0Dh, 68h, 40h, 08h, 01h, 0E8h, 0B8h, 0DBh, 30h, 00h
    db 0DBh, 46h, 08h, 8Bh, 4Eh, 08h, 8Bh, 0F8h, 0C1h, 0E7h, 18h, 85h, 0C9h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 8Bh, 56h, 0Ch, 0DBh, 46h, 0Ch, 85h, 0D2h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 8Bh, 06h, 0D9h, 0C1h, 0D8h, 0Dh, 64h, 0E3h, 11h, 01h, 8Bh
    db 0CEh, 0DEh, 0E9h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 14h, 0D9h, 5Ch, 24h
    db 08h, 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 08h, 8Bh
    db 16h, 57h, 50h, 51h, 6Ah, 00h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 92h, 0C0h, 00h, 00h, 00h
    db 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 0DBh, 46h, 0Ch, 8Bh, 46h, 0Ch
    db 85h, 0C0h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 4Eh, 08h, 0D9h, 54h, 24h
    db 14h, 85h, 0C9h, 0DBh, 46h, 08h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 16h
    db 0D9h, 54h, 24h, 08h, 0D8h, 0Dh, 64h, 0E3h, 11h, 01h, 8Bh, 0CEh, 0D8h, 0E9h, 0D8h, 0Dh
    db 3Ch, 53h, 07h, 01h, 0D8h, 0E9h, 0D9h, 5Ch, 24h, 0Ch, 0DDh, 0D8h, 0FFh, 92h, 0B0h, 00h
    db 00h, 00h, 8Bh, 4Ch, 24h, 14h, 8Bh, 54h, 24h, 08h, 8Bh, 06h, 57h, 51h, 8Bh, 4Ch
    db 24h, 14h, 52h, 51h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 90h, 0C0h, 00h, 00h, 00h, 8Bh, 16h
    db 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
    db 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 86h, 0D0h, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 44h, 0Fh, 8Bh, 0C8h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 2Bh, 86h, 0D8h
    db 00h, 00h, 00h, 85h, 0C0h, 89h, 44h, 24h, 14h, 0DBh, 44h, 24h, 14h, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 0D8h, 0Dh, 0ECh, 66h, 07h, 01h, 0D8h, 2Dh, 34h, 53h, 07h
    db 01h, 0D9h, 96h, 0D0h, 00h, 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 05h, 7Ah, 0Ah, 0C7h, 86h, 0D0h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0D9h, 86h
    db 0D0h, 00h, 00h, 00h, 0D8h, 0Dh, 68h, 40h, 08h, 01h, 0E8h, 69h, 0DAh, 30h, 00h, 0DBh
    db 46h, 08h, 8Bh, 4Eh, 08h, 8Bh, 0F8h, 0C1h, 0E7h, 18h, 85h, 0C9h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 8Bh, 56h, 0Ch, 0DBh, 46h, 0Ch, 85h, 0D2h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 8Bh, 06h, 0D9h, 0C1h, 0D8h, 0Dh, 64h, 0E3h, 11h, 01h, 8Bh, 0CEh
    db 0DEh, 0E9h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 14h, 0D9h, 5Ch, 24h, 0Ch
    db 0FFh, 90h, 0B0h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 16h
    db 57h, 50h, 51h, 6Ah, 00h, 6Ah, 00h, 8Bh, 0CEh, 0FFh, 92h, 0C0h, 00h, 00h, 00h, 8Bh
    db 16h, 8Bh, 0CEh, 0FFh, 92h, 0DCh, 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h
    db 00h, 5Fh, 0C6h, 86h, 0D4h, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_006e9210@@YAXXZ ENDP

; ghidra: FUN_00ae9540  retail @ 0x006E9540 size 245
public ?d_006e9540@@YAXXZ
?d_006e9540@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 0D9h, 44h, 24h, 18h, 0D8h, 44h, 24h, 1Ch, 0D9h, 54h, 24h, 1Ch, 0D8h
    db 1Dh, 8Ch, 5Fh, 09h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Bh, 0CFh, 00h, 00h, 00h
    db 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 56h, 0E8h, 0C1h, 0AEh, 94h, 0FFh, 8Bh, 0F0h, 0C6h, 86h
    db 48h, 01h, 00h, 00h, 01h, 33h, 0C0h, 88h, 86h, 49h, 01h, 00h, 00h, 89h, 86h, 54h
    db 01h, 00h, 00h, 88h, 86h, 4Ah, 01h, 00h, 00h, 89h, 86h, 58h, 01h, 00h, 00h, 8Bh
    db 44h, 24h, 18h, 0D9h, 00h, 8Bh, 48h, 08h, 0D9h, 40h, 04h, 8Bh, 0D1h, 89h, 96h, 0E0h
    db 00h, 00h, 00h, 0D9h, 0C9h, 0D9h, 9Eh, 0D8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 0Ch, 0D9h
    db 9Eh, 0DCh, 00h, 00h, 00h, 0D9h, 00h, 0D9h, 40h, 04h, 8Bh, 40h, 08h, 8Bh, 0C8h, 0D9h
    db 0C9h, 0D9h, 9Eh, 0E4h, 00h, 00h, 00h, 89h, 8Eh, 0ECh, 00h, 00h, 00h, 89h, 44h, 24h
    db 0Ch, 8Bh, 44h, 24h, 14h, 0D9h, 9Eh, 0E8h, 00h, 00h, 00h, 8Bh, 48h, 04h, 8Bh, 10h
    db 89h, 4Ch, 24h, 08h, 8Dh, 4Ch, 24h, 04h, 89h, 54h, 24h, 04h, 8Bh, 50h, 08h, 8Bh
    db 06h, 51h, 8Bh, 0CEh, 89h, 54h, 24h, 10h, 0FFh, 50h, 58h, 8Bh, 54h, 24h, 1Ch, 8Bh
    db 4Ch, 24h, 28h, 8Bh, 44h, 24h, 20h, 89h, 96h, 04h, 01h, 00h, 00h, 8Bh, 54h, 24h
    db 24h, 51h, 52h, 8Bh, 0CEh, 89h, 86h, 08h, 01h, 00h, 00h, 0E8h, 0C9h, 0B3h, 91h, 0FFh
    db 0C6h, 86h, 49h, 01h, 00h, 00h, 01h, 0C6h, 86h, 4Ah, 01h, 00h, 00h, 01h, 5Eh, 83h
    db 0C4h, 0Ch, 0C2h, 18h, 00h
?d_006e9540@@YAXXZ ENDP

; ghidra: FUN_00ae9680  retail @ 0x006E9680 size 61
public ?d_006e9680@@YAXXZ
?d_006e9680@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 8Eh, 0D4h, 00h, 00h, 00h, 84h, 0C9h, 0Fh, 94h, 0C0h, 88h, 86h
    db 0D4h, 00h, 00h, 00h, 0FFh, 15h, 44h, 95h, 35h, 01h, 89h, 86h, 0D8h, 00h, 00h, 00h
    db 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 85h, 0C9h, 74h, 11h, 8Ah, 86h, 0D4h, 00h, 00h, 00h
    db 8Bh, 11h, 84h, 0C0h, 0Fh, 94h, 0C0h, 50h, 0FFh, 52h, 1Ch, 5Eh, 0C3h
?d_006e9680@@YAXXZ ENDP

; ghidra: FUN_00ae96d0  retail @ 0x006E96D0 size 115
public ?d_006e96d0@@YAXXZ
?d_006e96d0@@YAXXZ PROC
    db 8Ah, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 84h, 0C0h, 8Ah, 86h, 0D4h, 00h, 00h, 00h, 74h
    db 2Fh, 84h, 0C0h, 75h, 5Ah, 0C6h, 86h, 0D4h, 00h, 00h, 00h, 01h, 0FFh, 15h, 44h, 95h
    db 35h, 01h, 89h, 86h, 0D8h, 00h, 00h, 00h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 85h, 0C9h
    db 74h, 3Dh, 8Bh, 01h, 5Eh, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0FFh, 60h, 1Ch
    db 84h, 0C0h, 74h, 2Bh, 0C6h, 86h, 0D4h, 00h, 00h, 00h, 00h, 0FFh, 15h, 44h, 95h, 35h
    db 01h, 89h, 86h, 0D8h, 00h, 00h, 00h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 85h, 0C9h, 74h
    db 0Eh, 8Bh, 11h, 5Eh, 0C7h, 44h, 24h, 04h, 01h, 00h, 00h, 00h, 0FFh, 62h, 1Ch, 5Eh
    db 0C2h, 04h, 00h
?d_006e96d0@@YAXXZ ENDP

; ghidra: FUN_00ae9760  retail @ 0x006E9760 size 372
public ?d_006e9760@@YAXXZ
?d_006e9760@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 32h, 33h, 0C9h, 3Bh, 0F1h, 57h, 74h, 51h, 0D9h, 44h, 24h
    db 18h, 89h, 8Eh, 0D8h, 00h, 00h, 00h, 89h, 8Eh, 0DCh, 00h, 00h, 00h, 89h, 8Eh, 0E0h
    db 00h, 00h, 00h, 0D8h, 48h, 0Ch, 0D9h, 44h, 24h, 18h, 8Bh, 32h, 0D8h, 48h, 10h, 81h
    db 0C6h, 0E4h, 00h, 00h, 00h, 0D9h, 44h, 24h, 18h, 0D8h, 48h, 14h, 0D9h, 5Ch, 24h, 10h
    db 8Bh, 7Ch, 24h, 10h, 0D9h, 0C9h, 89h, 7Eh, 08h, 0D9h, 1Eh, 0D9h, 5Eh, 04h, 8Bh, 32h
    db 81h, 0C6h, 0F0h, 00h, 00h, 00h, 89h, 0Eh, 89h, 4Eh, 04h, 89h, 4Eh, 08h, 8Bh, 72h
    db 04h, 3Bh, 0F1h, 74h, 53h, 0D9h, 44h, 24h, 18h, 89h, 8Eh, 0D8h, 00h, 00h, 00h, 89h
    db 8Eh, 0DCh, 00h, 00h, 00h, 89h, 8Eh, 0E0h, 00h, 00h, 00h, 0D8h, 48h, 30h, 0D9h, 44h
    db 24h, 18h, 8Bh, 72h, 04h, 0D8h, 48h, 34h, 81h, 0C6h, 0E4h, 00h, 00h, 00h, 0D9h, 44h
    db 24h, 18h, 0D8h, 48h, 38h, 0D9h, 5Ch, 24h, 10h, 8Bh, 7Ch, 24h, 10h, 0D9h, 0C9h, 89h
    db 7Eh, 08h, 0D9h, 1Eh, 0D9h, 5Eh, 04h, 8Bh, 72h, 04h, 81h, 0C6h, 0F0h, 00h, 00h, 00h
    db 89h, 0Eh, 89h, 4Eh, 04h, 89h, 4Eh, 08h, 8Bh, 72h, 08h, 3Bh, 0F1h, 74h, 53h, 0D9h
    db 44h, 24h, 18h, 89h, 8Eh, 0D8h, 00h, 00h, 00h, 89h, 8Eh, 0DCh, 00h, 00h, 00h, 89h
    db 8Eh, 0E0h, 00h, 00h, 00h, 0D8h, 48h, 54h, 0D9h, 44h, 24h, 18h, 8Bh, 72h, 08h, 0D8h
    db 48h, 58h, 81h, 0C6h, 0E4h, 00h, 00h, 00h, 0D9h, 44h, 24h, 18h, 0D8h, 48h, 5Ch, 0D9h
    db 5Ch, 24h, 10h, 8Bh, 7Ch, 24h, 10h, 0D9h, 0C9h, 89h, 7Eh, 08h, 0D9h, 1Eh, 0D9h, 5Eh
    db 04h, 8Bh, 72h, 08h, 81h, 0C6h, 0F0h, 00h, 00h, 00h, 89h, 0Eh, 89h, 4Eh, 04h, 89h
    db 4Eh, 08h, 8Bh, 72h, 0Ch, 3Bh, 0F1h, 74h, 55h, 0D9h, 44h, 24h, 18h, 89h, 8Eh, 0D8h
    db 00h, 00h, 00h, 89h, 8Eh, 0DCh, 00h, 00h, 00h, 89h, 8Eh, 0E0h, 00h, 00h, 00h, 0D8h
    db 48h, 78h, 0D9h, 44h, 24h, 18h, 0D8h, 48h, 7Ch, 0D9h, 44h, 24h, 18h, 0D8h, 88h, 80h
    db 00h, 00h, 00h, 8Bh, 42h, 0Ch, 05h, 0E4h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 10h, 8Bh
    db 74h, 24h, 10h, 0D9h, 0C9h, 89h, 70h, 08h, 0D9h, 18h, 0D9h, 58h, 04h, 8Bh, 52h, 0Ch
    db 81h, 0C2h, 0F0h, 00h, 00h, 00h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 5Fh, 5Eh
    db 83h, 0C4h, 0Ch, 0C3h
?d_006e9760@@YAXXZ ENDP

; ghidra: FUN_00ae9940  retail @ 0x006E9940 size 183
public ?d_006e9940@@YAXXZ
?d_006e9940@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Bh, 81h, 18h, 02h
    db 00h, 00h, 6Bh, 0C0h, 6Ch, 03h, 0C1h, 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 85h, 0C9h, 55h
    db 56h, 57h, 8Dh, 0B0h, 0ACh, 04h, 00h, 00h, 8Dh, 0B8h, 34h, 07h, 00h, 00h, 74h, 5Ah
    db 0D9h, 44h, 24h, 20h, 8Dh, 54h, 24h, 10h, 0D8h, 0Eh, 52h, 0D9h, 5Ch, 24h, 14h, 0D9h
    db 44h, 24h, 24h, 0D8h, 4Eh, 04h, 0D9h, 5Ch, 24h, 18h, 0D9h, 44h, 24h, 24h, 0D8h, 4Eh
    db 08h, 0D9h, 5Ch, 24h, 1Ch, 8Bh, 01h, 0FFh, 50h, 18h, 0D9h, 44h, 24h, 20h, 0D8h, 0Fh
    db 0A1h, 58h, 80h, 2Fh, 01h, 0D9h, 44h, 24h, 20h, 05h, 40h, 01h, 00h, 00h, 0D8h, 4Fh
    db 04h, 0D9h, 44h, 24h, 20h, 0D8h, 4Fh, 08h, 0D9h, 5Ch, 24h, 18h, 8Bh, 4Ch, 24h, 18h
    db 0D9h, 0C9h, 89h, 48h, 08h, 0D9h, 18h, 0D9h, 58h, 04h, 8Bh, 6Ch, 24h, 20h, 8Dh, 93h
    db 44h, 01h, 00h, 00h, 55h, 8Bh, 0C6h, 0E8h, 84h, 0FDh, 0FFh, 0FFh, 8Dh, 93h, 54h, 01h
    db 00h, 00h, 55h, 8Bh, 0C7h, 0E8h, 76h, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Dh
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_006e9940@@YAXXZ ENDP

; ghidra: FUN_00ae9a70  retail @ 0x006E9A70 size 48
public ?d_006e9a70@@YAXXZ
?d_006e9a70@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 84h, 81h, 54h, 01h, 00h, 00h, 85h, 0C0h, 74h, 1Eh, 8Bh
    db 4Ch, 24h, 08h, 8Bh, 54h, 24h, 0Ch, 89h, 88h, 0E4h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 10h, 89h, 90h, 0E8h, 00h, 00h, 00h, 89h, 88h, 0ECh, 00h, 00h, 00h, 0C2h, 10h, 00h
?d_006e9a70@@YAXXZ ENDP

; ghidra: FUN_00ae9b30  retail @ 0x006E9B30 size 44
public ?d_006e9b30@@YAXXZ
?d_006e9b30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Dh, 64h, 14h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h, 68h, 8Bh, 4Ch
    db 24h, 08h, 89h, 86h, 7Ch, 02h, 00h, 00h, 0C7h, 86h, 78h, 02h, 00h, 00h, 00h, 00h
    db 00h, 00h, 89h, 8Eh, 80h, 02h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_006e9b30@@YAXXZ ENDP

; ghidra: FUN_00ae9b90  retail @ 0x006E9B90 size 81
public ?d_006e9b90@@YAXXZ
?d_006e9b90@@YAXXZ PROC
    db 83h, 0ECh, 10h, 8Bh, 81h, 64h, 01h, 00h, 00h, 8Bh, 54h, 24h, 1Ch, 0C6h, 40h, 54h
    db 00h, 8Bh, 44h, 24h, 20h, 8Bh, 89h, 64h, 01h, 00h, 00h, 89h, 14h, 24h, 8Bh, 54h
    db 24h, 14h, 89h, 44h, 24h, 04h, 8Bh, 44h, 24h, 18h, 89h, 54h, 24h, 08h, 8Bh, 54h
    db 24h, 28h, 52h, 89h, 44h, 24h, 10h, 8Bh, 44h, 24h, 28h, 50h, 8Dh, 54h, 24h, 08h
    db 52h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 52h, 0Dh, 94h, 0FFh, 83h, 0C4h, 10h, 0C2h, 18h
    db 00h
?d_006e9b90@@YAXXZ ENDP

; ghidra: FUN_00ae9d40  retail @ 0x006E9D40 size 617
public ?d_006e9d40@@YAXXZ
?d_006e9d40@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0E4h, 0F8h, 83h, 0ECh, 2Ch, 0D9h, 45h, 08h, 53h, 56h, 8Bh, 0F1h
    db 8Ah, 86h, 78h, 01h, 00h, 00h, 84h, 0C0h, 57h, 0Fh, 84h, 00h, 02h, 00h, 00h, 0E8h
    db 0D4h, 0D0h, 30h, 00h, 0D9h, 45h, 0Ch, 8Bh, 0F8h, 89h, 44h, 24h, 0Ch, 89h, 7Ch, 24h
    db 10h, 0E8h, 0C2h, 0D0h, 30h, 00h, 8Bh, 0D8h, 89h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 14h
    db 89h, 7Ch, 24h, 18h, 0D8h, 45h, 14h, 0E8h, 0ACh, 0D0h, 30h, 00h, 89h, 44h, 24h, 1Ch
    db 8Dh, 0BEh, 68h, 01h, 00h, 00h, 57h, 8Dh, 44h, 24h, 24h, 50h, 8Dh, 4Ch, 24h, 30h
    db 51h, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 44h, 24h, 20h, 50h, 0E8h, 0B3h, 73h, 91h, 0FFh
    db 83h, 0C4h, 14h, 84h, 0C0h, 74h, 34h, 8Bh, 45h, 1Ch, 0DBh, 44h, 24h, 24h, 8Bh, 4Dh
    db 18h, 8Bh, 16h, 50h, 51h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 0CEh, 0DBh, 44h
    db 24h, 38h, 0D9h, 5Ch, 24h, 08h, 0DBh, 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h
    db 24h, 40h, 0D9h, 1Ch, 24h, 0FFh, 92h, 0B8h, 00h, 00h, 00h, 0DBh, 44h, 24h, 10h, 0D8h
    db 45h, 10h, 0E8h, 41h, 0D0h, 30h, 00h, 8Bh, 54h, 24h, 14h, 89h, 44h, 24h, 18h, 57h
    db 8Dh, 44h, 24h, 24h, 50h, 8Dh, 4Ch, 24h, 30h, 89h, 54h, 24h, 24h, 51h, 8Dh, 54h
    db 24h, 24h, 52h, 8Dh, 44h, 24h, 20h, 50h, 0E8h, 46h, 73h, 91h, 0FFh, 83h, 0C4h, 14h
    db 84h, 0C0h, 74h, 34h, 8Bh, 45h, 1Ch, 0DBh, 44h, 24h, 24h, 8Bh, 4Dh, 18h, 8Bh, 16h
    db 50h, 51h, 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 0CEh, 0DBh, 44h, 24h, 38h, 0D9h
    db 5Ch, 24h, 08h, 0DBh, 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 40h, 0D9h
    db 1Ch, 24h, 0FFh, 92h, 0B8h, 00h, 00h, 00h, 0D9h, 45h, 08h, 0D8h, 45h, 10h, 0E8h, 0D5h
    db 0CFh, 30h, 00h, 89h, 5Ch, 24h, 14h, 0DBh, 44h, 24h, 14h, 89h, 44h, 24h, 10h, 89h
    db 44h, 24h, 18h, 0D8h, 45h, 14h, 0E8h, 0BDh, 0CFh, 30h, 00h, 57h, 8Dh, 54h, 24h, 24h
    db 52h, 89h, 44h, 24h, 24h, 8Dh, 44h, 24h, 30h, 50h, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh
    db 54h, 24h, 20h, 52h, 0E8h, 0CAh, 72h, 91h, 0FFh, 83h, 0C4h, 14h, 84h, 0C0h, 74h, 34h
    db 8Bh, 4Dh, 1Ch, 0DBh, 44h, 24h, 24h, 8Bh, 55h, 18h, 8Bh, 06h, 51h, 52h, 83h, 0ECh
    db 10h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 0CEh, 0DBh, 44h, 24h, 38h, 0D9h, 5Ch, 24h, 08h, 0DBh
    db 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 40h, 0D9h, 1Ch, 24h, 0FFh, 90h
    db 0B8h, 00h, 00h, 00h, 0D9h, 45h, 0Ch, 8Bh, 44h, 24h, 0Ch, 0D8h, 45h, 14h, 89h, 44h
    db 24h, 10h, 0E8h, 51h, 0CFh, 30h, 00h, 0DBh, 44h, 24h, 10h, 8Bh, 0D8h, 89h, 5Ch, 24h
    db 14h, 0D8h, 45h, 10h, 0E8h, 3Fh, 0CFh, 30h, 00h, 57h, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh
    db 54h, 24h, 30h, 89h, 44h, 24h, 20h, 52h, 8Dh, 44h, 24h, 24h, 50h, 8Dh, 4Ch, 24h
    db 20h, 51h, 89h, 5Ch, 24h, 30h, 0E8h, 48h, 72h, 91h, 0FFh, 83h, 0C4h, 14h, 84h, 0C0h
    db 74h, 7Eh, 8Bh, 45h, 1Ch, 0DBh, 44h, 24h, 24h, 8Bh, 4Dh, 18h, 8Bh, 16h, 50h, 51h
    db 83h, 0ECh, 10h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 0CEh, 0DBh, 44h, 24h, 38h, 0D9h, 5Ch, 24h
    db 08h, 0DBh, 44h, 24h, 44h, 0D9h, 5Ch, 24h, 04h, 0DBh, 44h, 24h, 40h, 0D9h, 1Ch, 24h
    db 0FFh, 92h, 0B8h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 8Bh, 0E5h, 5Dh, 0C2h, 18h, 00h, 0D8h
    db 45h, 10h, 8Bh, 96h, 64h, 01h, 00h, 00h, 8Bh, 45h, 08h, 8Bh, 4Dh, 0Ch, 0C6h, 42h
    db 54h, 00h, 0D9h, 5Ch, 24h, 30h, 8Bh, 55h, 1Ch, 0D9h, 45h, 0Ch, 0D8h, 45h, 14h, 89h
    db 44h, 24h, 28h, 8Bh, 45h, 18h, 52h, 89h, 4Ch, 24h, 30h, 0D9h, 5Ch, 24h, 38h, 50h
    db 8Dh, 4Ch, 24h, 30h, 51h, 8Bh, 8Eh, 64h, 01h, 00h, 00h, 0E8h, 0A0h, 0CFh, 24h, 00h
    db 5Fh, 5Eh, 5Bh, 8Bh, 0E5h, 5Dh, 0C2h, 18h, 00h
?d_006e9d40@@YAXXZ ENDP

; ghidra: FUN_00aea1c0  retail @ 0x006EA1C0 size 323
public ?d_006ea1c0@@YAXXZ
?d_006ea1c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 23h, 0B5h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 0E8h, 0B3h, 8Eh, 21h, 00h, 8Bh, 5Ch, 24h
    db 1Ch, 84h, 0DBh, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h, 40h, 8Bh, 0Dh, 78h
    db 05h, 34h, 01h, 6Ah, 15h, 0E8h, 0F6h, 12h, 23h, 00h, 84h, 0C0h, 74h, 2Fh, 0BEh, 05h
    db 00h, 00h, 00h, 6Ah, 4Ch, 0E8h, 26h, 7Dh, 19h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 1Ch, 85h, 0C0h, 0C6h, 44h, 24h, 14h, 01h, 0Fh, 84h, 0C1h, 00h, 00h, 00h, 56h, 8Bh
    db 0C8h, 0E8h, 0Dh, 15h, 94h, 0FFh, 8Bh, 0F0h, 0E9h, 0B4h, 00h, 00h, 00h, 0E8h, 2Eh, 8Eh
    db 21h, 00h, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 8Bh, 0F0h, 56h, 0E8h, 0B0h, 12h, 23h, 00h
    db 84h, 0C0h, 74h, 10h, 53h, 56h, 0E8h, 4Ch, 12h, 92h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 08h
    db 85h, 0F6h, 75h, 0AFh, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 6Ah, 16h, 0E8h, 8Fh, 12h, 23h
    db 00h, 84h, 0C0h, 74h, 07h, 0BEh, 02h, 00h, 00h, 00h, 0EBh, 97h, 8Bh, 0Dh, 78h, 05h
    db 34h, 01h, 6Ah, 14h, 0E8h, 77h, 12h, 23h, 00h, 84h, 0C0h, 74h, 0Ah, 0BEh, 01h, 00h
    db 00h, 00h, 0E9h, 7Ch, 0FFh, 0FFh, 0FFh, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 6Ah, 17h, 0E8h
    db 5Ch, 12h, 23h, 00h, 84h, 0C0h, 74h, 0Ah, 0BEh, 03h, 00h, 00h, 00h, 0E9h, 61h, 0FFh
    db 0FFh, 0FFh, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 6Ah, 18h, 0E8h, 41h, 12h, 23h, 00h, 84h
    db 0C0h, 74h, 0Ah, 0BEh, 04h, 00h, 00h, 00h, 0E9h, 46h, 0FFh, 0FFh, 0FFh, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 46h, 0B8h, 21h, 00h, 5Eh, 33h, 0C0h, 5Bh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 33h
    db 0F6h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 22h, 0B8h, 21h, 00h, 8Bh, 4Ch
    db 24h, 0Ch, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C2h, 04h, 00h
?d_006ea1c0@@YAXXZ ENDP

; ghidra: FUN_00aeab90  retail @ 0x006EAB90 size 35
public ?d_006eab90@@YAXXZ
?d_006eab90@@YAXXZ PROC
    db 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Bh, 54h, 24h, 04h, 8Bh, 01h, 52h, 0FFh, 50h, 48h
    db 8Bh, 0Dh, 58h, 80h, 2Fh, 01h, 8Bh, 01h, 0C7h, 44h, 24h, 04h, 08h, 00h, 00h, 00h
    db 0FFh, 60h, 4Ch
?d_006eab90@@YAXXZ ENDP

; ghidra: FUN_00aeaf00  retail @ 0x006EAF00 size 120
public ?d_006eaf00@@YAXXZ
?d_006eaf00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 56h, 8Bh, 74h, 24h, 14h, 57h, 8Bh, 7Ch, 24h, 14h, 8Bh
    db 0CFh, 2Bh, 0C8h, 0C1h, 0F9h, 04h, 85h, 0C9h, 7Eh, 30h, 8Bh, 16h, 8Dh, 64h, 24h, 00h
    db 39h, 10h, 74h, 50h, 8Bh, 58h, 04h, 83h, 0C0h, 04h, 3Bh, 0DAh, 74h, 46h, 8Bh, 58h
    db 04h, 83h, 0C0h, 04h, 3Bh, 0DAh, 74h, 3Ch, 8Bh, 58h, 04h, 83h, 0C0h, 04h, 3Bh, 0DAh
    db 74h, 32h, 83h, 0C0h, 04h, 49h, 85h, 0C9h, 7Fh, 0D6h, 8Bh, 0CFh, 2Bh, 0C8h, 0C1h, 0F9h
    db 02h, 49h, 74h, 18h, 49h, 74h, 0Ch, 49h, 75h, 18h, 8Bh, 08h, 3Bh, 0Eh, 74h, 14h
    db 83h, 0C0h, 04h, 8Bh, 10h, 3Bh, 16h, 74h, 0Bh, 83h, 0C0h, 04h, 8Bh, 08h, 3Bh, 0Eh
    db 74h, 02h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_006eaf00@@YAXXZ ENDP

; ghidra: FUN_00aeb000  retail @ 0x006EB000 size 54
public ?d_006eb000@@YAXXZ
?d_006eb000@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 8Bh, 0F1h, 3Bh, 46h, 4Ch, 74h, 22h, 85h
    db 0C0h, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 4Eh, 4Ch, 85h, 0C9h, 74h, 05h, 0E8h, 7Dh
    db 07h, 30h, 00h, 8Bh, 07h, 8Bh, 0C8h, 0F7h, 0D9h, 1Bh, 0C9h, 89h, 46h, 4Ch, 89h, 4Eh
    db 50h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_006eb000@@YAXXZ ENDP

; ghidra: FUN_00aeb500  retail @ 0x006EB500 size 1215
public ?d_006eb500@@YAXXZ
?d_006eb500@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0B5h, 04h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 0F1h, 0E8h, 6Dh
    db 7Bh, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 85h, 0C0h, 0C7h, 44h, 24h, 20h, 00h, 00h
    db 00h, 00h, 74h, 34h, 8Bh, 08h, 50h, 0FFh, 51h, 0Ch, 85h, 0C0h, 75h, 2Ah, 8Bh, 15h
    db 98h, 08h, 2Fh, 01h, 8Ah, 82h, 1Dh, 01h, 00h, 00h, 84h, 0C0h, 75h, 0Fh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 90h, 80h, 00h, 00h, 00h, 0E8h, 43h, 63h, 93h, 0FFh, 8Bh, 0Dh, 0BCh
    db 64h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 14h, 0E8h, 83h, 0C9h, 24h, 00h, 0E8h, 0EEh, 0BCh
    db 24h, 00h, 8Bh, 0D8h, 0E8h, 0F7h, 0BCh, 24h, 00h, 8Bh, 0E8h, 0A1h, 0E0h, 7Fh, 2Fh, 01h
    db 85h, 0C0h, 74h, 4Eh, 8Bh, 88h, 0F4h, 2Fh, 00h, 00h, 85h, 0C9h, 74h, 44h, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 74h, 8Bh, 0F8h, 0A1h, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 88h, 0B8h, 30h
    db 00h, 00h, 85h, 0C9h, 74h, 11h, 8Bh, 87h, 04h, 01h, 00h, 00h, 50h, 0E8h, 25h, 0A2h
    db 95h, 0FFh, 0A1h, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 88h, 0BCh, 30h, 00h, 00h, 85h, 0C9h, 74h
    db 11h, 8Bh, 0BFh, 04h, 01h, 00h, 00h, 57h, 0E8h, 37h, 20h, 95h, 0FFh, 0A1h, 0E0h, 7Fh
    db 2Fh, 01h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 91h, 0BFh, 0Dh, 00h, 00h, 84h, 0D2h
    db 0Fh, 85h, 47h, 03h, 00h, 00h, 8Ah, 91h, 0Bh, 0Ch, 00h, 00h, 84h, 0D2h, 0Fh, 85h
    db 39h, 03h, 00h, 00h, 8Bh, 88h, 1Ch, 30h, 00h, 00h, 33h, 0FFh, 57h, 8Bh, 0D1h, 52h
    db 8Dh, 46h, 1Ch, 50h, 6Ah, 01h, 6Ah, 01h, 89h, 4Ch, 24h, 28h, 0E8h, 6Fh, 2Ch, 21h
    db 00h, 83h, 0C4h, 14h, 3Ch, 01h, 0Fh, 85h, 11h, 03h, 00h, 00h, 8Bh, 0Dh, 0C8h, 0D5h
    db 2Eh, 01h, 80h, 0B9h, 0B9h, 0Bh, 00h, 00h, 01h, 75h, 67h, 8Bh, 15h, 40h, 1Bh, 2Fh
    db 01h, 0C7h, 42h, 38h, 01h, 00h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h
    db 0FFh, 50h, 1Ch, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h, 8Bh, 11h, 0FFh, 52h, 1Ch, 0A1h, 40h
    db 1Bh, 2Fh, 01h, 83h, 0CEh, 0FFh, 89h, 70h, 38h, 8Bh, 0Dh, 5Ch, 4Ch, 2Fh, 01h, 3Bh
    db 0CFh, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 1Ch, 6Ah, 01h, 0E8h, 11h, 22h, 21h, 00h, 83h
    db 0C4h, 04h, 89h, 74h, 24h, 20h, 0E8h, 95h, 0A4h, 21h, 00h, 5Fh, 5Eh, 5Dh, 0B0h, 01h
    db 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h
    db 04h, 00h, 3Bh, 0DFh, 0C6h, 05h, 54h, 0AAh, 2Bh, 01h, 01h, 75h, 04h, 3Bh, 0EFh, 74h
    db 0Fh, 68h, 08h, 6Eh, 2Dh, 01h, 55h, 53h, 0E8h, 0F3h, 0BCh, 24h, 00h, 83h, 0C4h, 0Ch
    db 0A1h, 58h, 80h, 2Fh, 01h, 89h, 0B8h, 68h, 08h, 00h, 00h, 0D9h, 86h, 0D0h, 00h, 00h
    db 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 04h, 0B3h, 01h
    db 0EBh, 02h, 32h, 0DBh, 8Bh, 8Eh, 80h, 01h, 00h, 00h, 3Bh, 0CFh, 74h, 5Eh, 8Ah, 41h
    db 08h, 84h, 0C0h, 74h, 57h, 0E8h, 0B6h, 0BAh, 94h, 0FFh, 8Bh, 8Eh, 80h, 01h, 00h, 00h
    db 8Bh, 41h, 04h, 83h, 0F8h, 02h, 0Fh, 84h, 0C6h, 00h, 00h, 00h, 8Bh, 15h, 40h, 1Bh
    db 2Fh, 01h, 0C7h, 42h, 38h, 01h, 00h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh
    db 01h, 0FFh, 50h, 1Ch, 84h, 0DBh, 75h, 0Eh, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h
    db 0FFh, 92h, 30h, 01h, 00h, 00h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h
    db 1Ch, 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 89h, 79h, 38h, 0EBh, 6Fh, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 52h, 7Ch, 6Ah, 02h, 57h, 8Bh, 0CEh, 0E8h, 0AAh, 24h, 92h, 0FFh, 6Ah, 02h, 6Ah
    db 01h, 8Bh, 0CEh, 0E8h, 9Fh, 24h, 92h, 0FFh, 6Ah, 02h, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 94h
    db 24h, 92h, 0FFh, 39h, 7Eh, 34h, 75h, 07h, 8Bh, 0CEh, 0E8h, 11h, 43h, 95h, 0FFh, 0A1h
    db 40h, 1Bh, 2Fh, 01h, 0C7h, 40h, 38h, 01h, 00h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh
    db 01h, 8Bh, 11h, 0FFh, 52h, 1Ch, 84h, 0DBh, 75h, 0Eh, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h
    db 8Bh, 01h, 0FFh, 90h, 30h, 01h, 00h, 00h, 8Bh, 0Dh, 0E8h, 19h, 2Fh, 01h, 8Bh, 11h
    db 0FFh, 52h, 1Ch, 0A1h, 40h, 1Bh, 2Fh, 01h, 89h, 78h, 38h, 8Bh, 0Dh, 8Ch, 14h, 2Fh
    db 01h, 8Bh, 11h, 0FFh, 52h, 1Ch, 0A1h, 40h, 1Bh, 2Fh, 01h, 0C7h, 40h, 38h, 0FFh, 0FFh
    db 0FFh, 0FFh, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 0E8h, 25h, 41h, 93h, 0FFh, 8Bh, 0Dh, 5Ch
    db 4Ch, 2Fh, 01h, 3Bh, 0CFh, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 1Ch, 39h, 7Eh, 34h, 0Fh
    db 84h, 0BCh, 00h, 00h, 00h, 6Ah, 01h, 57h, 8Bh, 0CEh, 0E8h, 08h, 24h, 92h, 0FFh, 6Ah
    db 01h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0FDh, 23h, 92h, 0FFh, 8Bh, 86h, 04h, 01h, 00h, 00h
    db 8Bh, 96h, 00h, 01h, 00h, 00h, 8Bh, 4Eh, 34h, 8Bh, 3Eh, 6Ah, 0FFh, 50h, 8Bh, 86h
    db 0FCh, 00h, 00h, 00h, 52h, 8Bh, 96h, 0F8h, 00h, 00h, 00h, 50h, 8Bh, 01h, 52h, 0FFh
    db 50h, 3Ch, 50h, 8Bh, 0CEh, 0FFh, 97h, 0E0h, 00h, 00h, 00h, 6Ah, 01h, 6Ah, 02h, 8Bh
    db 0CEh, 0E8h, 0C1h, 23h, 92h, 0FFh, 8Bh, 0CEh, 0E8h, 43h, 42h, 95h, 0FFh, 8Bh, 0CEh, 0E8h
    db 4Eh, 0FDh, 95h, 0FFh, 8Bh, 4Eh, 34h, 8Bh, 51h, 08h, 8Bh, 7Ah, 18h, 85h, 0FFh, 74h
    db 50h, 8Bh, 06h, 8Bh, 0E9h, 8Bh, 0CEh, 0FFh, 50h, 30h, 85h, 0C0h, 89h, 44h, 24h, 14h
    db 0DBh, 44h, 24h, 14h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 16h, 51h, 8Bh
    db 0CEh, 0D9h, 1Ch, 24h, 0FFh, 52h, 2Ch, 85h, 0C0h, 89h, 44h, 24h, 18h, 0DBh, 44h, 24h
    db 18h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 8Bh, 45h, 00h, 51h, 0D9h, 1Ch, 24h
    db 6Ah, 00h, 6Ah, 00h, 8Bh, 0CDh, 0FFh, 50h, 20h, 50h, 8Bh, 0CFh, 0E8h, 7Fh, 1Ch, 13h
    db 00h, 8Bh, 4Ch, 24h, 28h, 51h, 8Bh, 0CEh, 0E8h, 69h, 33h, 95h, 0FFh, 84h, 0DBh, 74h
    db 0Eh, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 0FFh, 92h, 30h, 01h, 00h, 00h, 8Bh
    db 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 0FFh, 90h, 54h, 01h, 00h, 00h, 84h, 0C0h, 75h
    db 37h, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 0E8h, 0A5h, 02h, 92h, 0FFh, 84h, 0C0h, 75h, 0Fh
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 0F3h, 0E7h, 95h, 0FFh, 84h, 0C0h, 74h, 19h, 8Ah
    db 86h, 3Ch, 01h, 00h, 00h, 84h, 0C0h, 74h, 0Fh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 92h, 68h
    db 01h, 00h, 00h, 0E8h, 0C1h, 0EBh, 92h, 0FFh, 8Bh, 0Dh, 30h, 33h, 2Fh, 01h, 8Bh, 01h
    db 0FFh, 50h, 1Ch, 8Bh, 46h, 2Ch, 85h, 0C0h, 74h, 07h, 8Bh, 0CEh, 0E8h, 49h, 59h, 93h
    db 0FFh, 6Ah, 01h, 0E8h, 58h, 1Fh, 21h, 00h, 83h, 0C4h, 04h, 0EBh, 10h, 0A0h, 54h, 0AAh
    db 2Bh, 01h, 84h, 0C0h, 74h, 07h, 0C6h, 05h, 54h, 0AAh, 2Bh, 01h, 00h, 8Bh, 0Dh, 6Ch
    db 07h, 2Fh, 01h, 8Bh, 0F1h, 0E8h, 0F3h, 38h, 95h, 0FFh, 84h, 0C0h, 75h, 4Dh, 8Bh, 0CEh
    db 0E8h, 2Eh, 7Eh, 91h, 0FFh, 84h, 0C0h, 75h, 42h, 8Bh, 0Dh, 6Ch, 07h, 2Fh, 01h, 0E8h
    db 0B4h, 0B9h, 93h, 0FFh, 84h, 0C0h, 75h, 33h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 23h
    db 73h, 93h, 0FFh, 84h, 0C0h, 75h, 24h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 8Ch, 0A1h, 21h, 00h, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 0C7h, 44h, 24h, 20h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 68h, 0A1h, 21h, 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 32h
    db 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_006eb500@@YAXXZ ENDP

; ghidra: FUN_00aebd20  retail @ 0x006EBD20 size 405
_TEXT ENDS
_TEXT$d00aebd20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00AEBD20 size 405
public ?d_006ebd20@@YAXXZ
?d_006ebd20@@YAXXZ PROC
    db 055h, 08Bh, 0ECh, 083h, 0E4h, 0F8h, 083h, 0ECh, 05Ch, 0D9h, 045h, 010h, 053h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 08Bh, 0D9h, 08Bh, 083h, 064h, 001h, 000h, 000h, 0C6h, 040h, 054h, 000h, 0D9h, 05Ch, 024h, 008h
    db 056h, 0D9h, 045h, 014h, 08Bh, 04Ch, 024h, 00Ch, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 057h, 089h, 04Ch, 024h, 030h, 0C7h, 044h, 024h, 034h, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h
    db 018h, 0D9h, 044h, 024h, 010h, 0D8h, 045h, 008h, 0D9h, 05Ch, 024h, 01Ch, 0D9h, 044h, 024h, 018h
    db 0D8h, 045h, 00Ch, 0D9h, 05Ch, 024h, 020h, 0D9h, 044h, 024h, 010h, 0D8h, 05Ch, 024h, 018h, 0DFh
    db 0E0h, 0F6h, 0C4h, 041h, 075h, 006h, 0D9h, 044h, 024h, 010h, 0EBh, 004h, 0D9h, 044h, 024h, 018h
    db 0D8h, 00Dh
    dd ?g_bfmeK1266B@@3MB
    db 083h, 0ECh, 008h, 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp_?i_009f7030@@YAXXZ
    db 0D9h, 05Ch, 024h, 01Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 014h, 0DBh, 05Ch, 024h, 024h, 0DBh
    db 044h, 024h, 024h, 08Bh, 07Ch, 024h, 024h, 033h, 0F6h, 085h, 0FFh, 0D8h, 03Dh
    dd ?g_bfmeDisplayTwoPi@@3MB
    db 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 02Ch, 00Fh, 08Eh, 0D6h, 000h
    db 000h, 000h, 08Bh, 054h, 024h, 01Ch, 0D9h, 044h, 024h, 030h, 08Bh, 044h, 024h, 020h, 089h, 074h
    db 024h, 038h, 089h, 074h, 024h, 03Ch, 089h, 074h, 024h, 040h, 089h, 074h, 024h, 044h, 089h, 074h
    db 024h, 048h, 089h, 074h, 024h, 04Ch, 089h, 054h, 024h, 060h, 089h, 044h, 024h, 064h, 046h, 03Bh
    db 0F7h, 07Dh, 026h, 0D9h, 044h, 024h, 014h, 0D8h, 044h, 024h, 02Ch, 0D9h, 054h, 024h, 014h, 0D9h
    db 0FFh, 0D8h, 04Ch, 024h, 010h, 0D9h, 05Ch, 024h, 024h, 0D9h, 044h, 024h, 014h, 0D9h, 0FEh, 0D8h
    db 04Ch, 024h, 018h, 0D9h, 05Ch, 024h, 028h, 0EBh, 010h, 08Bh, 04Ch, 024h, 010h, 089h, 04Ch, 024h
    db 024h, 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 0D9h, 044h, 024h, 024h, 08Bh, 055h, 018h
    db 0D8h, 044h, 024h, 01Ch, 052h, 08Dh, 044h, 024h, 03Ch, 050h, 0D9h, 05Ch, 024h, 058h, 08Dh, 04Ch
    db 024h, 048h, 0D9h, 044h, 024h, 030h, 051h, 0D8h, 044h, 024h, 02Ch, 08Dh, 054h, 024h, 054h, 052h
    db 08Dh, 044h, 024h, 060h, 0D9h, 05Ch, 024h, 064h, 050h, 08Dh, 04Ch, 024h, 06Ch, 0D8h, 044h, 024h
    db 030h, 051h, 08Bh, 08Bh, 064h, 001h, 000h, 000h, 08Dh, 054h, 024h, 078h, 0D9h, 05Ch, 024h, 070h
    db 052h, 0D9h, 044h, 024h, 050h, 0D8h, 044h, 024h, 03Ch, 0D9h, 05Ch, 024h, 078h
    call ?j_00024bcc@@YAXXZ
    db 03Bh, 0F7h, 0D9h, 044h, 024h, 024h, 08Bh, 044h, 024h, 028h, 089h, 044h, 024h, 034h, 00Fh, 08Ch
    db 058h, 0FFh, 0FFh, 0FFh, 0DDh, 0D8h, 05Fh, 05Eh, 05Bh, 08Bh, 0E5h, 05Dh, 0C2h, 014h, 000h
?d_006ebd20@@YAXXZ ENDP
_TEXT$d00aebd20 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
