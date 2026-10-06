.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z:NEAR
EXTERN ?j_000016a4@@YAXXZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000e4a8@@YAXXZ:NEAR
EXTERN ?j_0000e570@@YAXXZ:NEAR
EXTERN ?j_0000faa6@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00033749@@YAXXZ:NEAR
EXTERN ?j_00034964@@YAXXZ:NEAR
EXTERN ?j_00036089@@YAXXZ:NEAR
EXTERN ?j_000441c0@@YAXXZ:NEAR
EXTERN ?j_0004a057@@YAXXZ:NEAR
_TEXT SEGMENT

; ghidra: FUN_005cbdc0  retail @ 0x001CBDC0 size 924
_TEXT ENDS
_TEXT$d005cbdc0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005CBDC0 size 924
public ?d_001cbdc0@@YAXXZ
?d_001cbdc0@@YAXXZ PROC
    db 083h, 0ECh, 058h, 055h, 08Bh, 0E9h, 08Bh, 08Dh, 004h, 002h, 000h, 000h, 085h, 0C9h, 074h, 010h
    db 08Bh, 001h, 0FFh, 090h, 08Ch, 001h, 000h, 000h, 084h, 0C0h, 00Fh, 085h, 075h, 003h, 000h, 000h
    db 0F6h, 085h, 044h, 003h, 000h, 000h, 001h, 00Fh, 085h, 068h, 003h, 000h, 000h, 0F7h, 085h, 090h
    db 000h, 000h, 000h, 000h, 000h, 000h, 010h, 074h, 00Ch, 08Ah, 044h, 024h, 060h, 084h, 0C0h, 00Fh
    db 084h, 050h, 003h, 000h, 000h, 08Bh, 085h, 008h, 002h, 000h, 000h, 085h, 0C0h, 074h, 00Bh, 08Ah
    db 048h, 05Ch, 084h, 0C9h, 00Fh, 085h, 03Bh, 003h, 000h, 000h, 08Bh, 045h, 004h, 085h, 0C0h, 074h
    db 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0D4h, 000h, 000h, 000h, 0F6h, 0C5h, 010h, 056h, 00Fh, 084h, 0F6h, 001h, 000h, 000h
    db 08Bh, 0F5h, 085h, 0F6h, 074h, 017h, 08Bh, 08Eh, 004h, 002h, 000h, 000h, 085h, 0C9h, 074h, 00Dh
    call ?j_0004a057@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0FAh, 002h, 000h, 000h, 08Bh, 055h, 000h, 053h, 057h, 08Bh, 0CDh, 0FFh
    db 052h, 064h, 08Bh, 0F8h, 08Ah, 085h, 094h, 000h, 000h, 000h, 0B3h, 020h, 084h, 0C3h, 089h, 07Ch
    db 024h, 014h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 074h, 013h, 08Bh, 08Dh, 014h, 002h
    db 000h, 000h, 085h, 0C9h, 074h, 009h, 08Bh, 001h, 0FFh, 050h, 064h, 089h, 044h, 024h, 018h, 085h
    db 0FFh, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 074h, 012h, 084h, 09Fh, 094h, 000h, 000h
    db 000h, 074h, 00Ah, 08Bh, 08Fh, 014h, 002h, 000h, 000h, 089h, 04Ch, 024h, 01Ch, 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 04Ah, 00Ch, 08Dh, 044h, 024h, 028h, 050h, 055h
    call ?j_00033749@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 055h, 08Bh, 0D8h
    call ?j_00036089@@YAXXZ
    db 084h, 0C0h, 075h, 02Ah, 085h, 0F6h, 00Fh, 084h, 072h, 002h, 000h, 000h, 06Ah, 06Dh, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 061h, 002h, 000h, 000h, 06Ah, 076h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 050h, 002h, 000h, 000h, 033h, 0C0h, 03Bh, 0D8h, 089h, 044h, 024h, 010h
    db 089h, 044h, 024h, 020h, 00Fh, 084h, 095h, 000h, 000h, 000h, 033h, 0FFh, 085h, 0DBh, 00Fh, 08Eh
    db 087h, 000h, 000h, 000h, 08Bh, 0FFh, 08Bh, 054h, 0BCh, 028h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 052h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 066h, 0F6h, 086h, 044h, 003h, 000h, 000h, 001h, 075h, 05Dh, 08Bh
    db 086h, 008h, 002h, 000h, 000h, 085h, 0C0h, 074h, 007h, 08Ah, 048h, 05Ch, 084h, 0C9h, 075h, 04Ch
    db 056h, 08Bh, 0CDh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 083h, 0F8h, 002h, 074h, 03Fh, 085h, 0C0h, 075h, 03Bh, 06Ah, 007h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 075h, 010h, 068h, 081h, 000h, 000h, 000h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 00Ch, 03Bh, 074h, 024h, 014h, 074h, 006h, 03Bh, 074h, 024h, 018h, 075h, 012h
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 006h, 03Bh, 044h, 024h, 014h, 074h, 004h, 089h, 074h
    db 024h, 010h, 047h, 03Bh, 0FBh, 00Fh, 08Ch, 07Bh, 0FFh, 0FFh, 0FFh, 08Bh, 07Ch, 024h, 014h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 08Dh, 054h, 024h, 028h, 052h, 055h
    call ?j_00034964@@YAXXZ
    db 085h, 0C0h, 089h, 044h, 024h, 024h, 00Fh, 084h, 062h, 001h, 000h, 000h, 033h, 0C9h, 085h, 0C0h
    db 089h, 04Ch, 024h, 014h, 00Fh, 08Eh, 054h, 001h, 000h, 000h, 0EBh, 008h, 08Dh, 0A4h, 024h, 000h
    db 000h, 000h, 000h, 090h, 08Bh, 044h, 08Ch, 028h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 015h, 001h, 000h, 000h, 08Bh, 05Ch, 024h, 018h, 03Bh, 0F3h
    db 00Fh, 084h, 020h, 001h, 000h, 000h, 085h, 0DBh, 074h, 011h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_0000faa6@@YAXXZ
    db 03Bh, 0C3h, 00Fh, 084h, 00Bh, 001h, 000h, 000h, 08Bh, 044h, 024h, 01Ch, 085h, 0C0h, 074h, 032h
    db 039h, 086h, 014h, 002h, 000h, 000h, 075h, 02Ah, 08Bh, 0DEh, 089h, 05Ch, 024h, 010h, 0EBh, 026h
    db 08Bh, 0B5h, 014h, 002h, 000h, 000h, 085h, 0F6h, 074h, 011h, 06Ah, 06Ch, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0F1h, 0FDh, 0FFh, 0FFh, 033h, 0F6h, 0E9h, 005h, 0FEh, 0FFh, 0FFh, 08Bh
    db 05Ch, 024h, 010h, 0F6h, 086h, 044h, 003h, 000h, 000h, 001h, 00Fh, 085h, 0A9h, 000h, 000h, 000h
    db 08Bh, 086h, 008h, 002h, 000h, 000h, 085h, 0C0h, 074h, 00Bh, 08Ah, 048h, 05Ch, 084h, 0C9h, 00Fh
    db 085h, 094h, 000h, 000h, 000h, 056h, 08Bh, 0CDh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 083h, 0F8h, 002h, 075h, 02Dh, 06Ah, 01Ch, 08Bh, 0CEh
    call ?j_000016a4@@YAXXZ
    db 084h, 0C0h, 074h, 07Ah, 08Bh, 044h, 024h, 020h, 085h, 0C0h, 075h, 072h, 08Bh, 0B6h, 004h, 002h
    db 000h, 000h, 085h, 0F6h, 074h, 068h, 08Bh, 04Eh, 030h
    call ?j_0000e570@@YAXXZ
    db 089h, 044h, 024h, 020h, 0EBh, 05Ah, 085h, 0C0h, 075h, 056h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 056h, 08Dh, 055h, 038h, 052h, 055h
    call ?j_000441c0@@YAXXZ
    db 084h, 0C0h, 074h, 03Eh, 085h, 0DBh, 074h, 004h, 03Bh, 0DFh, 074h, 036h, 06Ah, 007h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 075h, 010h, 068h, 081h, 000h, 000h, 000h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 004h, 03Bh, 0F7h, 075h, 015h, 08Ah, 044h, 024h, 06Ch, 084h, 0C0h, 089h, 074h
    db 024h, 010h, 074h, 009h, 06Ah, 000h, 08Bh, 0CEh
    call ?j_0000e4a8@@YAXXZ
    db 08Bh, 04Ch, 024h, 014h, 08Bh, 044h, 024h, 024h, 041h, 03Bh, 0C8h, 089h, 04Ch, 024h, 014h, 00Fh
    db 08Ch, 0BCh, 0FEh, 0FFh, 0FFh, 0EBh, 004h, 089h, 074h, 024h, 010h, 08Bh, 074h, 024h, 010h, 085h
    db 0F6h, 074h, 020h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 056h, 08Dh, 055h, 038h, 052h, 055h
    call ?j_000441c0@@YAXXZ
    db 084h, 0C0h, 074h, 009h, 08Bh, 045h, 000h, 056h, 08Bh, 0CDh, 0FFh, 050h, 068h, 05Fh, 05Bh, 05Eh
    db 05Dh, 083h, 0C4h, 058h, 0C2h, 004h, 000h
?d_001cbdc0@@YAXXZ ENDP
_TEXT$d005cbdc0 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
