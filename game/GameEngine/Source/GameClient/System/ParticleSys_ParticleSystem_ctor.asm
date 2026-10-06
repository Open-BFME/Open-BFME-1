.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?j_00001b18@@YAXXZ:NEAR
EXTERN ?j_0000d7b5@@YAXXZ:NEAR
EXTERN ?j_0000fa3d@@YAXXZ:NEAR
EXTERN ?j_00013994@@YAXXZ:NEAR
EXTERN ?j_00015dde@@YAXXZ:NEAR
EXTERN ?j_0003128c@@YAXXZ:NEAR
EXTERN ?j_0003a373@@YAXXZ:NEAR
EXTERN ?j_00042a87@@YAXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN __ftol2:NEAR
EXTERN g_0103A6C0:NEAR
EXTERN g_0110FE48:BYTE
EXTERN g_012F1464:BYTE
EXTERN g_012F64BC:BYTE

; ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z
; Exact 1426B retail @ 0x005CF850; factory new(0x1E0)+call from create @0x5C33E0; queue 0x6E2296 was helper epilogue
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d009cf850 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x009CF850 size 1426
public ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z
??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z PROC
    db 06Ah, 0FFh, 068h
    dd g_0103A6C0
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 01Ch, 053h, 055h, 056h, 08Bh, 0F1h, 057h, 089h, 074h, 024h, 010h
    call ?j_0003128c@@YAXXZ
    db 033h, 0DBh, 0C7h, 006h
    dd g_0110FE48
    db 089h, 09Eh, 098h, 000h, 000h, 000h, 089h, 09Eh, 09Ch, 000h, 000h, 000h, 089h, 05Ch, 024h, 034h
    db 089h, 09Eh, 0BCh, 000h, 000h, 000h, 089h, 09Eh, 060h, 001h, 000h, 000h, 089h, 09Eh, 064h, 001h
    db 000h, 000h, 089h, 09Eh, 068h, 001h, 000h, 000h, 089h, 09Eh, 070h, 001h, 000h, 000h, 089h, 09Eh
    db 074h, 001h, 000h, 000h, 089h, 09Eh, 078h, 001h, 000h, 000h, 089h, 09Eh, 0B0h, 001h, 000h, 000h
    db 089h, 09Eh, 0B4h, 001h, 000h, 000h, 089h, 09Eh, 0B8h, 001h, 000h, 000h, 089h, 09Eh, 0BCh, 001h
    db 000h, 000h, 089h, 09Eh, 0C0h, 001h, 000h, 000h, 089h, 09Eh, 0C4h, 001h, 000h, 000h, 089h, 09Eh
    db 0C8h, 001h, 000h, 000h, 089h, 09Eh, 0CCh, 001h, 000h, 000h, 089h, 09Eh, 0D0h, 001h, 000h, 000h
    db 089h, 09Eh, 0D4h, 001h, 000h, 000h, 089h, 09Eh, 0D8h, 001h, 000h, 000h, 08Bh, 044h, 024h, 040h
    db 08Bh, 07Ch, 024h, 03Ch, 089h, 086h, 0ACh, 000h, 000h, 000h, 089h, 09Eh, 0A4h, 000h, 000h, 000h
    db 089h, 09Eh, 0A0h, 000h, 000h, 000h, 0C6h, 086h, 0A9h, 001h, 000h, 000h, 001h, 089h, 0BEh, 09Ch
    db 001h, 000h, 000h, 089h, 09Eh, 054h, 001h, 000h, 000h, 089h, 09Eh, 058h, 001h, 000h, 000h, 089h
    db 09Eh, 05Ch, 001h, 000h, 000h, 089h, 09Eh, 048h, 001h, 000h, 000h, 089h, 09Eh, 04Ch, 001h, 000h
    db 000h, 089h, 09Eh, 050h, 001h, 000h, 000h, 089h, 09Eh, 034h, 001h, 000h, 000h, 089h, 09Eh, 038h
    db 001h, 000h, 000h, 089h, 09Eh, 03Ch, 001h, 000h, 000h, 089h, 09Eh, 0B4h, 000h, 000h, 000h, 089h
    db 09Eh, 0B8h, 000h, 000h, 000h, 0C6h, 086h, 0A4h, 001h, 000h, 000h, 001h, 089h, 09Eh, 0C4h, 000h
    db 000h, 000h, 089h, 09Eh, 0C8h, 000h, 000h, 000h, 089h, 09Eh, 0CCh, 000h, 000h, 000h, 0B8h, 000h
    db 000h, 080h, 03Fh, 089h, 086h, 0C0h, 000h, 000h, 000h, 089h, 09Eh, 0D0h, 000h, 000h, 000h, 089h
    db 086h, 0D4h, 000h, 000h, 000h, 089h, 09Eh, 0D8h, 000h, 000h, 000h, 089h, 09Eh, 0DCh, 000h, 000h
    db 000h, 089h, 09Eh, 0E0h, 000h, 000h, 000h, 089h, 09Eh, 0E4h, 000h, 000h, 000h, 089h, 086h, 0E8h
    db 000h, 000h, 000h, 089h, 09Eh, 0ECh, 000h, 000h, 000h, 0C6h, 086h, 0A5h, 001h, 000h, 000h, 001h
    db 089h, 086h, 0F0h, 000h, 000h, 000h, 089h, 09Eh, 0F4h, 000h, 000h, 000h, 089h, 09Eh, 0F8h, 000h
    db 000h, 000h, 089h, 09Eh, 0FCh, 000h, 000h, 000h, 089h, 09Eh, 000h, 001h, 000h, 000h, 089h, 086h
    db 004h, 001h, 000h, 000h, 089h, 09Eh, 008h, 001h, 000h, 000h, 089h, 09Eh, 00Ch, 001h, 000h, 000h
    db 0C6h, 044h, 024h, 034h, 004h, 089h, 09Eh, 010h, 001h, 000h, 000h, 089h, 09Eh, 014h, 001h, 000h
    db 000h, 089h, 086h, 018h, 001h, 000h, 000h, 089h, 09Eh, 01Ch, 001h, 000h, 000h, 088h, 09Eh, 0A7h
    db 001h, 000h, 000h, 088h, 09Eh, 0A8h, 001h, 000h, 000h, 0C6h, 086h, 0AAh, 001h, 000h, 000h, 001h
    db 088h, 09Eh, 0ABh, 001h, 000h, 000h, 08Dh, 04Fh, 06Ch, 08Bh, 029h, 08Dh, 056h, 06Ch, 089h, 02Ah
    db 08Bh, 069h, 004h, 089h, 06Ah, 004h, 08Bh, 049h, 008h, 089h, 04Ah, 008h, 089h, 086h, 034h, 001h
    db 000h, 000h, 089h, 086h, 038h, 001h, 000h, 000h, 089h, 086h, 03Ch, 001h, 000h, 000h, 089h, 086h
    db 040h, 001h, 000h, 000h, 089h, 086h, 044h, 001h, 000h, 000h, 089h, 086h, 080h, 001h, 000h, 000h
    db 089h, 086h, 088h, 001h, 000h, 000h, 089h, 05Eh, 040h, 089h, 09Eh, 08Ch, 001h, 000h, 000h, 089h
    db 09Eh, 090h, 001h, 000h, 000h, 089h, 09Eh, 094h, 001h, 000h, 000h, 088h, 09Eh, 098h, 001h, 000h
    db 000h, 08Dh, 057h, 014h, 08Bh, 00Ah, 08Dh, 046h, 014h, 089h, 008h, 08Bh, 04Ah, 004h, 089h, 048h
    db 004h, 08Bh, 052h, 008h, 089h, 050h, 008h, 08Dh, 047h, 028h, 08Bh, 010h, 08Dh, 04Eh, 028h, 089h
    db 011h, 08Bh, 050h, 004h, 089h, 051h, 004h, 08Bh, 040h, 008h, 089h, 041h, 008h, 08Dh, 04Fh, 034h
    db 08Bh, 001h, 08Dh, 056h, 034h, 089h, 002h, 08Bh, 041h, 004h, 089h, 042h, 004h, 08Bh, 049h, 008h
    db 089h, 04Ah, 008h, 08Dh, 057h, 044h, 08Bh, 00Ah, 08Dh, 046h, 044h, 089h, 008h, 08Bh, 04Ah, 004h
    db 089h, 048h, 004h, 08Bh, 052h, 008h, 089h, 050h, 008h, 089h, 09Eh, 020h, 001h, 000h, 000h, 08Dh
    db 047h, 050h, 08Bh, 010h, 08Dh, 04Eh, 050h, 089h, 011h, 08Bh, 050h, 004h, 089h, 051h, 004h, 08Bh
    db 040h, 008h, 089h, 041h, 008h, 08Ah, 04Fh, 004h, 088h, 04Eh, 004h, 08Dh, 04Fh, 05Ch
    call ?j_0000d7b5@@YAXXZ
    call __ftol2
    db 089h, 086h, 024h, 001h, 000h, 000h, 08Bh, 00Dh
    dd g_012F1464
    db 08Bh, 011h, 0FFh, 052h, 068h, 089h, 086h, 028h, 001h, 000h, 000h, 08Bh, 047h, 020h, 089h, 086h
    db 02Ch, 001h, 000h, 000h, 039h, 05Fh, 020h, 00Fh, 094h, 0C1h, 088h, 08Eh, 0A6h, 001h, 000h, 000h
    db 08Bh, 057h, 024h, 089h, 056h, 024h, 089h, 09Eh, 084h, 001h, 000h, 000h, 08Bh, 047h, 07Ch, 089h
    db 046h, 07Ch, 08Ah, 08Fh, 080h, 000h, 000h, 000h, 088h, 08Eh, 080h, 000h, 000h, 000h, 08Ah, 097h
    db 081h, 000h, 000h, 000h, 088h, 096h, 081h, 000h, 000h, 000h, 08Ah, 087h, 082h, 000h, 000h, 000h
    db 088h, 086h, 082h, 000h, 000h, 000h, 08Ah, 08Fh, 083h, 000h, 000h, 000h, 088h, 08Eh, 083h, 000h
    db 000h, 000h, 08Bh, 057h, 008h, 089h, 056h, 008h, 08Bh, 047h, 00Ch, 08Dh, 057h, 010h, 08Dh, 04Eh
    db 010h, 052h, 089h, 046h, 00Ch
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 038h, 05Ch, 024h, 044h, 088h, 09Eh, 0A7h, 001h, 000h, 000h, 089h, 09Eh, 07Ch, 001h, 000h, 000h
    db 089h, 09Eh, 06Ch, 001h, 000h, 000h, 00Fh, 084h, 0A0h, 000h, 000h, 000h, 06Ah, 001h, 08Dh, 044h
    db 024h, 018h, 050h, 08Bh, 0CFh
    call ?j_0003a373@@YAXXZ
    db 039h, 05Ch, 024h, 014h, 074h, 07Eh, 08Dh, 04Ch, 024h, 014h, 051h, 08Dh, 08Eh, 060h, 001h, 000h
    db 000h
    call ?j_0000fa3d@@YAXXZ
    db 08Bh, 044h, 024h, 014h, 03Bh, 0C3h, 074h, 008h, 08Bh, 080h, 0ACh, 000h, 000h, 000h, 0EBh, 002h
    db 033h, 0C0h, 056h, 08Dh, 04Ch, 024h, 024h, 089h, 086h, 06Ch, 001h, 000h, 000h
    call ?j_00042a87@@YAXXZ
    db 08Bh, 0E8h, 08Bh, 086h, 060h, 001h, 000h, 000h, 03Bh, 0C3h, 0C6h, 044h, 024h, 034h, 006h, 075h
    db 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 0C8h, 055h, 081h, 0C1h, 070h, 001h, 000h, 000h, 089h, 044h, 024h, 048h
    call ?j_0000fa3d@@YAXXZ
    db 08Bh, 06Dh, 000h, 03Bh, 0EBh, 074h, 008h, 08Bh, 0ADh, 0ACh, 000h, 000h, 000h, 0EBh, 002h, 033h
    db 0EDh, 08Bh, 054h, 024h, 044h, 08Dh, 04Ch, 024h, 020h, 089h, 0AAh, 07Ch, 001h, 000h, 000h
    call ?j_00013994@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 034h, 004h
    call ?j_00013994@@YAXXZ
    db 08Dh, 047h, 078h, 08Dh, 04Eh, 078h, 050h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 089h, 09Eh, 0A8h, 000h, 000h, 000h, 089h, 09Eh, 0B0h, 000h, 000h, 000h, 089h, 09Eh, 030h, 001h
    db 000h, 000h, 089h, 09Eh, 0A0h, 001h, 000h, 000h, 088h, 09Eh, 0ACh, 001h, 000h, 000h, 08Dh, 08Fh
    db 084h, 000h, 000h, 000h, 08Bh, 001h, 08Dh, 096h, 084h, 000h, 000h, 000h, 089h, 002h, 08Bh, 041h
    db 004h, 089h, 042h, 004h, 08Bh, 041h, 008h, 089h, 042h, 008h, 08Bh, 049h, 00Ch, 089h, 04Ah, 00Ch
    db 089h, 074h, 024h, 014h, 08Bh, 096h, 09Ch, 000h, 000h, 000h, 08Dh, 044h, 024h, 014h, 089h, 054h
    db 024h, 018h, 089h, 05Ch, 024h, 01Ch, 089h, 086h, 09Ch, 000h, 000h, 000h, 08Bh, 044h, 024h, 018h
    db 03Bh, 0C3h, 074h, 009h, 08Dh, 04Ch, 024h, 014h, 089h, 048h, 008h, 0EBh, 00Eh, 08Bh, 044h, 024h
    db 014h, 08Dh, 054h, 024h, 014h, 089h, 090h, 098h, 000h, 000h, 000h, 08Bh, 08Fh, 0A0h, 000h, 000h
    db 000h, 03Bh, 0CBh, 0C6h, 044h, 024h, 034h, 007h, 074h, 00Ch, 08Bh, 011h, 08Dh, 044h, 024h, 014h
    db 050h, 0FFh, 052h, 008h, 0EBh, 002h, 033h, 0C0h, 057h, 08Dh, 04Ch, 024h, 018h, 051h, 08Dh, 08Eh
    db 0B4h, 001h, 000h, 000h, 089h, 086h, 0B0h, 001h, 000h, 000h
    call ?j_00015dde@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h
    call ?j_00013994@@YAXXZ
    db 089h, 074h, 024h, 014h, 08Bh, 096h, 09Ch, 000h, 000h, 000h, 08Dh, 044h, 024h, 014h, 089h, 054h
    db 024h, 018h, 089h, 05Ch, 024h, 01Ch, 089h, 086h, 09Ch, 000h, 000h, 000h, 08Bh, 044h, 024h, 018h
    db 03Bh, 0C3h, 074h, 009h, 08Dh, 04Ch, 024h, 014h, 089h, 048h, 008h, 0EBh, 00Eh, 08Bh, 044h, 024h
    db 014h, 08Dh, 054h, 024h, 014h, 089h, 090h, 098h, 000h, 000h, 000h, 0A1h
    dd g_012F64BC
    db 08Bh, 0B8h, 080h, 000h, 000h, 000h, 06Ah, 014h, 0C6h, 044h, 024h, 038h, 008h, 089h, 044h, 024h
    db 048h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Dh, 048h, 008h, 083h, 0C4h, 004h, 03Bh, 0CBh, 074h, 03Eh, 08Bh, 054h, 024h, 014h, 089h, 011h
    db 08Bh, 054h, 024h, 014h, 03Bh, 0D3h, 074h, 02Ah, 08Bh, 0AAh, 09Ch, 000h, 000h, 000h, 081h, 0C2h
    db 09Ch, 000h, 000h, 000h, 089h, 069h, 004h, 089h, 059h, 008h, 089h, 00Ah, 08Bh, 051h, 004h, 03Bh
    db 0D3h, 074h, 005h, 089h, 04Ah, 008h, 0EBh, 010h, 08Bh, 011h, 089h, 08Ah, 098h, 000h, 000h, 000h
    db 0EBh, 006h, 089h, 059h, 008h, 089h, 059h, 004h, 08Bh, 04Fh, 004h, 089h, 048h, 004h, 089h, 038h
    db 089h, 001h, 089h, 047h, 004h, 08Bh, 044h, 024h, 044h, 0FFh, 080h, 08Ch, 000h, 000h, 000h, 08Dh
    db 04Ch, 024h, 014h
    call ?j_00013994@@YAXXZ
    db 08Bh, 04Ch, 024h, 02Ch, 05Fh, 08Bh, 0C6h, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Bh, 083h, 0C4h, 028h, 0C2h, 00Ch, 000h
??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z ENDP
_TEXT$d009cf850 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
