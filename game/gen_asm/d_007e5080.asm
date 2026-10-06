.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0Format@Debug@@QAA@PBDZZ:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva0134CB48FileSystem@@3PAVFileSystem@@A:BYTE
EXTERN ?TheBfmeObject_00C70BC0@@3VGen_00C70BC0Target@@A:BYTE
EXTERN ?_bfme_debugRecordCallsite@@YAXH@Z:NEAR
EXTERN ?_bfme_debugReportingEnabled@@YA_NXZ:NEAR
EXTERN ?bfmeLinkEQB@@YGPAUBfmeNodeEQB@@PAU1@@Z:NEAR
EXTERN ?doesFileExist@FileSystem@@QBE_NPBD@Z:NEAR
EXTERN ?format@AsciiString@@QAAXV1@ZZ:NEAR
EXTERN ?j_0001a2fd@@YAXXZ:NEAR
EXTERN ?ji_009f6ec6@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN g_Va01054581:NEAR
EXTERN g_Va01128E90:BYTE
EXTERN g_Va01128EBC:BYTE
EXTERN g_Va01128ED0:BYTE
EXTERN g_Va01128F04:BYTE
EXTERN g_Va01128F10:BYTE
EXTERN g_Va011295B0:BYTE
EXTERN g_Va012C37EE:BYTE
EXTERN g_Va01309849:BYTE
_TEXT SEGMENT

; ghidra: FUN_00be5080  retail @ 0x007E5080 size 737
_TEXT ENDS
_TEXT$d00be5080 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE5080 size 737
public ?d_007e5080@@YAXXZ
?d_007e5080@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01054581
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 00Ch, 002h, 000h, 000h, 053h, 055h, 056h, 08Bh, 0E9h, 057h, 089h, 06Ch, 024h, 018h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Ah, 088h, 07Dh, 00Ah, 000h, 000h, 033h, 0F6h, 084h, 0C9h, 089h, 0B4h, 024h, 024h, 002h, 000h
    db 000h, 00Fh, 085h, 052h, 001h, 000h, 000h, 051h, 08Dh, 094h, 024h, 030h, 002h, 000h, 000h, 089h
    db 064h, 024h, 014h, 08Bh, 0CCh, 052h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 045h, 000h, 08Bh, 0CDh, 0FFh, 050h, 04Ch, 08Bh, 0D8h, 03Bh, 0DEh, 00Fh, 084h, 0DDh, 001h
    db 000h, 000h, 089h, 074h, 024h, 014h, 033h, 0FFh, 0C6h, 084h, 024h, 024h, 002h, 000h, 000h, 001h
    db 089h, 07Ch, 024h, 010h, 0BEh
    dd g_Va01309849
    db 08Bh, 0FFh, 08Ah, 046h, 0FFh, 084h, 0C0h, 074h, 057h, 08Bh, 003h, 085h, 0C0h, 068h
    dd g_Va01128F10
    db 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 056h, 051h, 089h, 064h, 024h, 020h, 08Bh, 0CCh, 068h
    dd g_Va01128F04
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 024h, 051h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 08Bh, 044h, 024h, 028h, 083h, 0C4h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?Rva0134CB48FileSystem@@3PAVFileSystem@@A
    db 050h
    call ?doesFileExist@FileSystem@@QBE_NPBD@Z
    db 084h, 0C0h, 075h, 015h, 081h, 0C6h, 045h, 001h, 000h, 000h, 047h, 081h, 0FEh
    dd ?TheBfmeObject_00C70BC0@@3VGen_00C70BC0Target@@A
    db 07Ch, 093h, 089h, 07Ch, 024h, 010h, 0EBh, 00Dh, 083h, 0FFh, 003h, 089h, 07Ch, 024h, 010h, 00Fh
    db 08Ch, 0B1h, 000h, 000h, 000h
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 074h, 074h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 011h, 083h, 0C4h, 004h, 0FFh, 052h, 060h, 08Bh, 003h, 085h, 0C0h, 08Dh, 068h, 008h, 075h
    db 005h, 0BDh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 084h, 024h, 02Ch, 002h, 000h, 000h, 085h, 0C0h, 08Dh, 078h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 06Ah, 000h, 06Ah, 000h, 0FFh, 050h, 06Ch, 055h, 057h, 08Dh, 04Ch, 024h, 024h, 068h
    dd g_Va01128ED0
    db 051h, 08Bh, 0F0h
    call ??0Format@Debug@@QAA@PBDZZ
    db 08Bh, 016h, 083h, 0C4h, 010h, 050h, 08Bh, 0CEh, 0FFh, 052h, 038h, 08Bh, 006h, 06Ah, 002h, 08Bh
    db 0CEh, 0FFh, 050h, 04Ch, 08Bh, 07Ch, 024h, 010h, 08Bh, 06Ch, 024h, 018h, 083h, 0FFh, 003h, 07Ch
    db 02Fh, 08Dh, 04Ch, 024h, 014h, 0C6h, 084h, 024h, 024h, 002h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 08Ch, 024h, 02Ch, 002h, 000h, 000h, 0C7h, 084h, 024h, 024h, 002h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0C0h, 0E9h, 015h, 001h, 000h, 000h, 06Ah, 064h
    call ??2@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 018h, 085h, 0C0h, 0C6h, 084h, 024h, 024h, 002h, 000h, 000h
    db 002h, 074h, 00Dh, 055h, 053h, 08Bh, 0C8h
    call ?j_0001a2fd@@YAXXZ
    db 08Bh, 0F0h, 0EBh, 002h, 033h, 0F6h, 08Bh, 08Ch, 024h, 030h, 002h, 000h, 000h, 08Bh, 006h, 083h
    db 0C9h, 040h, 00Fh, 095h, 0C2h, 088h, 054h, 024h, 018h, 08Bh, 04Ch, 024h, 018h, 051h, 053h, 08Dh
    db 054h, 024h, 01Ch, 052h, 08Bh, 0CEh, 0C6h, 084h, 024h, 030h, 002h, 000h, 000h, 001h, 0FFh, 050h
    db 04Ch, 084h, 0C0h, 074h, 01Eh, 056h, 08Bh, 0CDh
    call ?bfmeLinkEQB@@YGPAUBfmeNodeEQB@@PAU1@@Z
    db 08Dh, 04Ch, 024h, 014h, 0C6h, 084h, 024h, 024h, 002h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 0E9h, 086h, 000h, 000h, 000h, 08Bh, 006h, 06Ah, 001h, 08Bh, 0CEh, 0FFh, 010h, 08Dh, 04Ch, 024h
    db 014h, 033h, 0F6h, 0C6h, 084h, 024h, 024h, 002h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 0EBh, 069h
    call ?_bfme_debugReportingEnabled@@YA_NXZ
    db 084h, 0C0h, 074h, 060h, 06Ah, 001h
    call ?_bfme_debugRecordCallsite@@YAXH@Z
    db 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 011h, 083h, 0C4h, 004h, 0FFh, 052h, 060h, 08Bh, 00Dh
    dd ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
    db 08Bh, 001h, 056h, 056h, 0FFh, 050h, 06Ch, 08Bh, 010h, 068h
    dd g_Va01128EBC
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 08Ch, 024h, 02Ch, 002h, 000h, 000h, 03Bh, 0CEh, 074h, 005h
    db 083h, 0C1h, 008h, 0EBh, 005h, 0B9h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 010h, 051h, 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 010h, 068h
    dd g_Va01128E90
    db 08Bh, 0C8h, 0FFh, 052h, 038h, 08Bh, 010h, 06Ah, 002h, 08Bh, 0C8h, 0FFh, 052h, 04Ch, 08Dh, 08Ch
    db 024h, 02Ch, 002h, 000h, 000h, 0C7h, 084h, 024h, 024h, 002h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 0C6h, 08Bh, 08Ch, 024h, 01Ch, 002h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 05Bh, 081h, 0C4h, 018h, 002h, 000h, 000h, 0C2h, 008h, 000h
?d_007e5080@@YAXXZ ENDP
_TEXT$d00be5080 ENDS
_TEXT SEGMENT

; ghidra: FUN_00be5420  retail @ 0x007E5420 size 367
public ?d_007e5420@@YAXXZ
?d_007e5420@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BEh, 45h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0E4h, 00h, 00h, 00h, 53h, 55h, 8Bh, 0ACh, 24h
    db 0FCh, 00h, 00h, 00h, 56h, 57h, 8Bh, 0F9h, 0BBh, 01h, 00h, 00h, 00h, 55h, 8Dh, 4Ch
    db 24h, 14h, 33h, 0F6h, 89h, 5Fh, 5Ch, 89h, 5Fh, 60h, 0E8h, 01h, 27h, 0Ah, 00h, 6Ah
    db 06h, 68h, 14h, 8Fh, 12h, 01h, 8Dh, 4Ch, 24h, 18h, 89h, 0B4h, 24h, 04h, 01h, 00h
    db 00h, 0E8h, 0EAh, 28h, 0Ah, 00h, 0A1h, 68h, 0D6h, 2Eh, 01h, 85h, 0C0h, 0Fh, 84h, 0DBh
    db 00h, 00h, 00h, 6Ah, 02h, 55h, 8Dh, 8Ch, 24h, 8Ch, 00h, 00h, 00h, 0E8h, 74h, 0FEh
    db 83h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 8Dh, 94h, 24h, 84h, 00h, 00h
    db 00h, 52h, 88h, 9Ch, 24h, 00h, 01h, 00h, 00h, 0FFh, 90h, 0ACh, 00h, 00h, 00h, 8Bh
    db 84h, 24h, 8Ch, 00h, 00h, 00h, 85h, 0C0h, 74h, 28h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h
    db 8Bh, 01h, 8Dh, 94h, 24h, 84h, 00h, 00h, 00h, 52h, 0FFh, 50h, 58h, 89h, 47h, 5Ch
    db 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 0FFh, 90h, 34h, 01h, 00h, 00h, 8Bh, 0F0h
    db 0F7h, 0DEh, 6Ah, 02h, 8Dh, 4Ch, 24h, 14h, 51h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 14h, 0FEh
    db 83h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h, 14h, 50h, 0C6h
    db 84h, 24h, 00h, 01h, 00h, 00h, 02h, 0FFh, 92h, 0ACh, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 1Ch, 85h, 0C0h, 74h, 25h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh, 44h, 24h
    db 14h, 50h, 0FFh, 52h, 58h, 89h, 47h, 60h, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h
    db 0FFh, 92h, 34h, 01h, 00h, 00h, 8Bh, 0F0h, 0F7h, 0DEh, 8Dh, 4Ch, 24h, 14h, 88h, 9Ch
    db 24h, 0FCh, 00h, 00h, 00h, 0E8h, 0EBh, 19h, 84h, 0FFh, 8Dh, 8Ch, 24h, 84h, 00h, 00h
    db 00h, 0C6h, 84h, 24h, 0FCh, 00h, 00h, 00h, 00h, 0E8h, 0D7h, 19h, 84h, 0FFh, 8Dh, 4Ch
    db 24h, 10h, 0C7h, 84h, 24h, 0FCh, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0CEh, 23h
    db 0Ah, 00h, 8Bh, 8Ch, 24h, 0F4h, 00h, 00h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0F0h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_007e5420@@YAXXZ ENDP

; ghidra: FUN_00be5840  retail @ 0x007E5840 size 24
public ?d_007e5840@@YAXXZ
?d_007e5840@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 89h, 4Ah
    db 0Ch, 89h, 4Ah, 10h, 89h, 4Ah, 14h, 0C3h
?d_007e5840@@YAXXZ ENDP

; ghidra: FUN_00be7850  retail @ 0x007E7850 size 33
public ?d_007e7850@@YAXXZ
?d_007e7850@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 0Ch, 50h, 0FFh, 15h, 0D4h
    db 93h, 35h, 01h, 83h, 0C4h, 04h, 89h, 3Eh, 89h, 7Eh, 04h, 89h, 7Eh, 08h, 5Fh, 5Eh
    db 0C3h
?d_007e7850@@YAXXZ ENDP

; ghidra: FUN_00be78d0  retail @ 0x007E78D0 size 145
public ?d_007e78d0@@YAXXZ
?d_007e78d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 33h, 0FFh, 3Bh, 0F7h, 74h, 0Bh, 8Bh, 06h, 3Bh, 0C7h
    db 74h, 66h, 83h, 0F8h, 2Ch, 74h, 0Ah, 5Fh, 0B8h, 57h, 00h, 07h, 80h, 5Eh, 0C2h, 08h
    db 00h, 39h, 7Eh, 24h, 53h, 55h, 7Eh, 28h, 8Bh, 5Ch, 24h, 18h, 8Bh, 2Dh, 9Ch, 90h
    db 35h, 01h, 85h, 0FFh, 7Ch, 49h, 3Bh, 7Eh, 24h, 7Dh, 44h, 8Bh, 46h, 20h, 0Fh, 0B7h
    db 0Ch, 78h, 53h, 51h, 0FFh, 0D5h, 8Bh, 46h, 24h, 47h, 3Bh, 0F8h, 7Ch, 0E4h, 33h, 0FFh
    db 8Bh, 46h, 20h, 3Bh, 0C7h, 74h, 0Dh, 50h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h
    db 04h, 89h, 7Eh, 20h, 8Dh, 56h, 04h, 52h, 89h, 7Eh, 24h, 89h, 7Eh, 28h, 0FFh, 15h
    db 0Ch, 8Dh, 35h, 01h, 5Dh, 89h, 3Eh, 5Bh, 5Fh, 33h, 0C0h, 5Eh, 0C2h, 08h, 00h, 6Ah
    db 00h, 6Ah, 00h, 6Ah, 01h, 68h, 8Ch, 00h, 00h, 0C0h, 0FFh, 15h, 0BCh, 8Eh, 35h, 01h
    db 0CCh
?d_007e78d0@@YAXXZ ENDP

; ghidra: FUN_00be8500  retail @ 0x007E8500 size 33
public ?d_007e8500@@YAXXZ
?d_007e8500@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 0Ch, 50h, 0FFh, 15h, 0D4h
    db 93h, 35h, 01h, 83h, 0C4h, 04h, 89h, 3Eh, 89h, 7Eh, 04h, 89h, 7Eh, 08h, 5Fh, 5Eh
    db 0C3h
?d_007e8500@@YAXXZ ENDP

; ghidra: ~_ATL_WIN_MODULE70  retail @ 0x007E8570 size 35
public ?d_007e8570@@YAXXZ
?d_007e8570@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 20h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 0Dh, 50h, 0FFh, 15h
    db 0D4h, 93h, 35h, 01h, 83h, 0C4h, 04h, 89h, 7Eh, 20h, 89h, 7Eh, 24h, 89h, 7Eh, 28h
    db 5Fh, 5Eh, 0C3h
?d_007e8570@@YAXXZ ENDP

; ghidra: FUN_00be85a0  retail @ 0x007E85A0 size 69
public ?d_007e85a0@@YAXXZ
?d_007e85a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 33h, 0C0h, 8Dh, 4Eh, 04h, 8Bh, 0D1h, 89h, 02h, 89h, 42h, 04h, 89h
    db 42h, 08h, 89h, 42h, 0Ch, 89h, 42h, 10h, 89h, 42h, 14h, 57h, 33h, 0FFh, 89h, 7Eh
    db 20h, 89h, 7Eh, 24h, 89h, 7Eh, 28h, 0C7h, 06h, 2Ch, 00h, 00h, 00h, 89h, 7Eh, 1Ch
    db 0E8h, 0F2h, 28h, 85h, 0FFh, 3Bh, 0C7h, 8Bh, 0C6h, 7Dh, 07h, 0C6h, 05h, 40h, 0A4h, 30h
    db 01h, 01h, 5Fh, 5Eh, 0C3h
?d_007e85a0@@YAXXZ ENDP

; ghidra: FUN_00be8600  retail @ 0x007E8600 size 47
public ?d_007e8600@@YAXXZ
?d_007e8600@@YAXXZ PROC
    db 0A1h, 4Ch, 0FBh, 34h, 01h, 56h, 57h, 8Bh, 0F1h, 50h, 56h, 0E8h, 0D0h, 0F0h, 85h, 0FFh
    db 8Bh, 46h, 20h, 33h, 0FFh, 3Bh, 0C7h, 74h, 0Dh, 50h, 0FFh, 15h, 0D4h, 93h, 35h, 01h
    db 83h, 0C4h, 04h, 89h, 7Eh, 20h, 89h, 7Eh, 24h, 89h, 7Eh, 28h, 5Fh, 5Eh, 0C3h
?d_007e8600@@YAXXZ ENDP

; ghidra: FUN_00be8640  retail @ 0x007E8640 size 98
public ?d_007e8640@@YAXXZ
?d_007e8640@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 14h, 85h, 0FFh, 75h, 18h, 0E8h, 0C1h, 31h, 00h, 00h, 8Bh
    db 10h, 6Ah, 21h, 68h, 2Ch, 93h, 12h, 01h, 68h, 28h, 93h, 12h, 01h, 8Bh, 0C8h, 0FFh
    db 52h, 0Ch, 8Bh, 0C7h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 8Bh, 74h
    db 24h, 10h, 2Bh, 0C2h, 3Bh, 0C6h, 72h, 18h, 0E8h, 93h, 31h, 00h, 00h, 8Bh, 10h, 6Ah
    db 22h, 68h, 2Ch, 93h, 12h, 01h, 68h, 10h, 93h, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch
    db 8Bh, 44h, 24h, 0Ch, 56h, 57h, 50h, 0E8h, 1Eh, 0EAh, 20h, 00h, 83h, 0C4h, 0Ch, 5Fh
    db 5Eh, 0C3h
?d_007e8640@@YAXXZ ENDP

; ghidra: FUN_00be86b0  retail @ 0x007E86B0 size 16
public ?d_007e86b0@@YAXXZ
?d_007e86b0@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 58h, 93h, 12h, 01h, 0C7h, 40h, 04h, 00h, 00h, 00h, 00h, 0C3h
?d_007e86b0@@YAXXZ ENDP

; ghidra: FUN_00be86d0  retail @ 0x007E86D0 size 92
public ?d_007e86d0@@YAXXZ
?d_007e86d0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 8Dh, 44h, 24h, 0Ch, 50h, 8Dh, 4Ch, 24h, 0Ch, 51h
    db 8Bh, 4Ch, 24h, 1Ch, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 44h, 24h, 20h, 50h, 68h, 0E4h
    db 0FBh, 07h, 01h, 51h, 0E8h, 0ADh, 0E8h, 20h, 00h, 8Bh, 54h, 24h, 2Ch, 8Bh, 44h, 24h
    db 1Ch, 0C1h, 0E2h, 08h, 03h, 0D0h, 8Bh, 44h, 24h, 20h, 0C1h, 0E2h, 08h, 03h, 0D0h, 8Bh
    db 44h, 24h, 24h, 83h, 0C4h, 18h, 0C1h, 0E2h, 08h, 03h, 0D0h, 8Bh, 44h, 24h, 18h, 89h
    db 56h, 08h, 89h, 46h, 0Ch, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_007e86d0@@YAXXZ ENDP

; ghidra: FUN_00be8730  retail @ 0x007E8730 size 33
public ?d_007e8730@@YAXXZ
?d_007e8730@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 50h, 8Bh, 0F1h, 8Dh, 4Eh, 08h, 6Ah, 1Ch, 51h, 0E8h, 0FDh
    db 0FEh, 0FFh, 0FFh, 8Bh, 54h, 24h, 18h, 83h, 0C4h, 0Ch, 89h, 56h, 24h, 5Eh, 0C2h, 08h
    db 00h
?d_007e8730@@YAXXZ ENDP

; ghidra: FUN_00be8760  retail @ 0x007E8760 size 85
public ?d_007e8760@@YAXXZ
?d_007e8760@@YAXXZ PROC
    db 83h, 7Ch, 24h, 08h, 11h, 56h, 8Bh, 0F1h, 73h, 18h, 0E8h, 0A1h, 30h, 00h, 00h, 8Bh
    db 10h, 6Ah, 31h, 68h, 6Ch, 93h, 12h, 01h, 68h, 0A0h, 0C2h, 11h, 01h, 8Bh, 0C8h, 0FFh
    db 52h, 0Ch, 8Bh, 46h, 08h, 0Fh, 0B6h, 0C8h, 51h, 8Bh, 0D0h, 0C1h, 0EAh, 08h, 0Fh, 0B6h
    db 0CAh, 51h, 8Bh, 0D0h, 0C1h, 0EAh, 10h, 0Fh, 0B6h, 0CAh, 8Bh, 54h, 24h, 10h, 51h, 0C1h
    db 0E8h, 18h, 50h, 68h, 5Ch, 93h, 12h, 01h, 52h, 0E8h, 34h, 0E6h, 20h, 00h, 83h, 0C4h
    db 18h, 5Eh, 0C2h, 08h, 00h
?d_007e8760@@YAXXZ ENDP

; ghidra: FUN_00be87f0  retail @ 0x007E87F0 size 29
public ?d_007e87f0@@YAXXZ
?d_007e87f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0B8h, 0FEh, 0FFh, 0FFh, 33h, 0C0h, 89h, 46h, 08h, 89h, 46h, 0Ch
    db 89h, 46h, 04h, 0C7h, 06h, 0B0h, 96h, 12h, 01h, 8Bh, 0C6h, 5Eh, 0C3h
?d_007e87f0@@YAXXZ ENDP

; ghidra: FUN_00be8810  retail @ 0x007E8810 size 60
public ?d_007e8810@@YAXXZ
?d_007e8810@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 98h, 0FEh, 0FFh, 0FFh, 33h, 0C0h, 89h, 46h, 08h, 89h, 46h, 0Ch
    db 89h, 46h, 04h, 89h, 46h, 10h, 89h, 46h, 18h, 89h, 46h, 14h, 89h, 46h, 28h, 89h
    db 46h, 24h, 89h, 46h, 20h, 89h, 46h, 1Ch, 88h, 46h, 30h, 0C7h, 06h, 0B0h, 96h, 12h
    db 01h, 0C7h, 46h, 2Ch, 04h, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_007e8810@@YAXXZ ENDP

; ghidra: FUN_00be8850  retail @ 0x007E8850 size 76
public ?d_007e8850@@YAXXZ
?d_007e8850@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 58h, 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 54h, 24h, 0Ch
    db 33h, 0C0h, 3Bh, 0C8h, 0C7h, 06h, 0B0h, 96h, 12h, 01h, 89h, 46h, 08h, 89h, 46h, 0Ch
    db 89h, 46h, 04h, 89h, 4Eh, 10h, 89h, 56h, 14h, 89h, 46h, 18h, 89h, 46h, 28h, 89h
    db 46h, 24h, 89h, 46h, 20h, 89h, 46h, 1Ch, 74h, 02h, 88h, 01h, 88h, 46h, 30h, 0C7h
    db 46h, 2Ch, 04h, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C2h, 08h, 00h
?d_007e8850@@YAXXZ ENDP

; ghidra: FUN_00be88d0  retail @ 0x007E88D0 size 44
public ?d_007e88d0@@YAXXZ
?d_007e88d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 8Bh, 56h, 14h, 50h, 8Bh
    db 46h, 10h, 51h, 52h, 50h, 0E8h, 0D6h, 3Ch, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 7Dh
    db 07h, 0C7h, 46h, 24h, 9Ch, 0FFh, 0FFh, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_007e88d0@@YAXXZ ENDP

; ghidra: FUN_00be8900  retail @ 0x007E8900 size 45
public ?d_007e8900@@YAXXZ
?d_007e8900@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 49h, 10h, 50h, 51h, 0E8h, 92h, 33h, 00h, 00h, 83h, 0C4h
    db 08h, 85h, 0C0h, 75h, 07h, 8Bh, 44h, 24h, 08h, 0C2h, 08h, 00h, 8Bh, 54h, 24h, 08h
    db 52h, 50h, 0E8h, 0F9h, 5Dh, 00h, 00h, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_007e8900@@YAXXZ ENDP

; ghidra: FUN_00be8930  retail @ 0x007E8930 size 70
public ?d_007e8930@@YAXXZ
?d_007e8930@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 49h, 10h, 83h, 0ECh, 08h, 50h, 51h, 0E8h, 5Fh, 33h, 00h
    db 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 0Eh, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h, 14h
    db 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 8Dh, 14h, 24h, 52h, 68h, 0B4h, 96h, 12h, 01h, 50h
    db 0E8h, 41h, 0E6h, 20h, 00h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 83h, 0C4h, 0Ch
    db 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_007e8930@@YAXXZ ENDP

; ghidra: FUN_00be8980  retail @ 0x007E8980 size 51
public ?d_007e8980@@YAXXZ
?d_007e8980@@YAXXZ PROC
    db 8Ah, 54h, 24h, 08h, 33h, 0C0h, 84h, 0D2h, 0Fh, 95h, 0C0h, 56h, 8Bh, 0F1h, 8Bh, 4Ch
    db 24h, 08h, 8Bh, 56h, 14h, 50h, 8Bh, 46h, 10h, 51h, 52h, 50h, 0E8h, 1Fh, 3Ch, 00h
    db 00h, 83h, 0C4h, 10h, 85h, 0C0h, 7Dh, 07h, 0C7h, 46h, 24h, 9Ch, 0FFh, 0FFh, 0FFh, 5Eh
    db 0C2h, 08h, 00h
?d_007e8980@@YAXXZ ENDP

; ghidra: FUN_00be89c0  retail @ 0x007E89C0 size 73
public ?d_007e89c0@@YAXXZ
?d_007e89c0@@YAXXZ PROC
    db 8Ah, 54h, 24h, 08h, 33h, 0C0h, 84h, 0D2h, 8Bh, 54h, 24h, 04h, 0Fh, 95h, 0C0h, 56h
    db 52h, 8Bh, 0F0h, 8Bh, 41h, 10h, 50h, 0E8h, 0C4h, 32h, 00h, 00h, 83h, 0C4h, 08h, 85h
    db 0C0h, 75h, 0Fh, 8Bh, 0C6h, 33h, 0C9h, 85h, 0C0h, 0Fh, 95h, 0C1h, 8Ah, 0C1h, 5Eh, 0C2h
    db 08h, 00h, 56h, 50h, 0E8h, 27h, 5Dh, 00h, 00h, 83h, 0C4h, 08h, 33h, 0C9h, 85h, 0C0h
    db 0Fh, 95h, 0C1h, 8Ah, 0C1h, 5Eh, 0C2h, 08h, 00h
?d_007e89c0@@YAXXZ ENDP

; ghidra: FUN_00be8a10  retail @ 0x007E8A10 size 44
public ?d_007e8a10@@YAXXZ
?d_007e8a10@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 8Bh, 56h, 14h, 50h, 8Bh
    db 46h, 10h, 51h, 52h, 50h, 0E8h, 36h, 44h, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 7Dh
    db 07h, 0C7h, 46h, 24h, 9Ch, 0FFh, 0FFh, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_007e8a10@@YAXXZ ENDP

; ghidra: FUN_00be8a80  retail @ 0x007E8A80 size 57
public ?d_007e8a80@@YAXXZ
?d_007e8a80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 49h, 10h, 50h, 51h, 0E8h, 12h, 32h, 00h, 00h, 8Bh, 54h
    db 24h, 10h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 07h, 88h, 02h, 32h, 0C0h, 0C2h, 0Ch, 00h
    db 8Bh, 4Ch, 24h, 0Ch, 68h, 1Ch, 30h, 07h, 01h, 51h, 52h, 50h, 0E8h, 7Fh, 61h, 00h
    db 00h, 83h, 0C4h, 10h, 0B0h, 01h, 0C2h, 0Ch, 00h
?d_007e8a80@@YAXXZ ENDP

; ghidra: FUN_00be8ac0  retail @ 0x007E8AC0 size 21
public ?d_007e8ac0@@YAXXZ
?d_007e8ac0@@YAXXZ PROC
    db 8Bh, 51h, 10h, 33h, 0C0h, 88h, 02h, 89h, 41h, 18h, 89h, 41h, 24h, 0C7h, 41h, 2Ch
    db 04h, 00h, 00h, 00h, 0C3h
?d_007e8ac0@@YAXXZ ENDP

; ghidra: FUN_00be8b00  retail @ 0x007E8B00 size 549
_TEXT ENDS
_TEXT$d00be8b00 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BE8B00 size 549
public ?d_007e8b00@@YAXXZ
?d_007e8b00@@YAXXZ PROC
    db 08Bh, 054h, 024h, 004h, 085h, 0D2h, 075h, 004h, 083h, 0C8h, 0FFh, 0C3h, 08Bh, 044h, 024h, 00Ch
    db 085h, 0C0h, 053h, 00Fh, 084h, 007h, 002h, 000h, 000h, 08Ah, 018h, 080h, 0FBh, 020h, 00Fh, 086h
    db 0FCh, 001h, 000h, 000h, 080h, 0FBh, 07Eh, 08Ah, 00Ah, 056h, 057h, 08Bh, 0C2h, 075h, 043h, 084h
    db 0C9h, 074h, 036h, 08Ah, 048h, 001h, 040h, 084h, 0C9h, 075h, 0F8h, 03Bh, 0C2h, 074h, 02Ah, 08Ah
    db 048h, 0FFh, 080h, 0F9h, 020h, 072h, 022h, 00Fh, 0B6h, 0F1h, 08Ah, 00Dh
    dd g_Va012C37EE
    db 00Fh, 0BEh, 0F9h, 03Bh, 0F7h, 074h, 012h, 08Bh, 074h, 024h, 014h, 08Dh, 074h, 032h, 0FFh, 03Bh
    db 0C6h, 073h, 006h, 088h, 008h, 040h, 0C6h, 000h, 000h, 08Bh, 0C8h, 08Bh, 0D8h, 0E9h, 0E1h, 000h
    db 000h, 000h, 084h, 0C9h, 074h, 0F3h, 08Ah, 008h, 080h, 0F9h, 020h, 077h, 003h, 040h, 0EBh, 06Dh
    db 00Fh, 0B6h, 0C9h, 080h, 0B9h
    dd g_Va011295B0
    db 001h, 074h, 0DDh, 00Fh, 0B6h, 010h, 08Ah, 08Ah
    dd g_Va011295B0
    db 00Fh, 0B6h, 0D3h, 08Ah, 092h
    dd g_Va011295B0
    db 03Ah, 0CAh, 075h, 02Dh, 08Bh, 074h, 024h, 018h, 08Bh, 0F8h, 02Bh, 0FEh, 08Dh, 09Bh, 000h, 000h
    db 000h, 000h, 080h, 0F9h, 002h, 072h, 01Ah, 00Fh, 0B6h, 04Ch, 037h, 001h, 00Fh, 0B6h, 056h, 001h
    db 08Ah, 089h
    dd g_Va011295B0
    db 08Ah, 092h
    dd g_Va011295B0
    db 046h, 03Ah, 0CAh, 074h, 0E1h, 00Fh, 0B6h, 0D2h, 00Fh, 0B6h, 0C9h, 003h, 0D1h, 083h, 0FAh, 002h
    db 074h, 05Ah, 08Dh, 064h, 024h, 000h, 08Ah, 048h, 001h, 040h, 080h, 0F9h, 020h, 073h, 0F7h, 08Bh
    db 054h, 024h, 010h, 080h, 038h, 000h, 075h, 084h, 03Bh, 0C2h, 00Fh, 084h, 06Fh, 0FFh, 0FFh, 0FFh
    db 08Ah, 048h, 0FFh, 080h, 0F9h, 020h, 00Fh, 082h, 063h, 0FFh, 0FFh, 0FFh, 00Fh, 0B6h, 0F1h, 08Ah
    db 00Dh
    dd g_Va012C37EE
    db 00Fh, 0BEh, 0F9h, 03Bh, 0F7h, 00Fh, 084h, 04Fh, 0FFh, 0FFh, 0FFh, 08Bh, 074h, 024h, 014h, 08Dh
    db 074h, 032h, 0FFh, 03Bh, 0C6h, 00Fh, 083h, 03Fh, 0FFh, 0FFh, 0FFh, 088h, 008h, 040h, 0C6h, 000h
    db 000h, 08Bh, 0C8h, 08Bh, 0D8h, 0EBh, 01Dh, 080h, 038h, 020h, 08Bh, 0C8h, 08Bh, 0D8h, 072h, 00Ah
    db 090h, 08Ah, 051h, 001h, 041h, 080h, 0FAh, 020h, 073h, 0F7h, 080h, 039h, 000h, 08Bh, 054h, 024h
    db 010h, 076h, 001h, 041h, 08Bh, 074h, 024h, 018h, 055h, 033h, 0EDh, 080h, 03Eh, 020h, 072h, 008h
    db 090h, 045h, 080h, 03Ch, 02Eh, 020h, 073h, 0F9h, 045h, 08Bh, 0F5h, 02Bh, 0F1h, 003h, 0F0h, 080h
    db 039h, 000h, 08Bh, 0F9h, 074h, 008h, 08Ah, 047h, 001h, 047h, 084h, 0C0h, 075h, 0F8h, 047h, 085h
    db 0F6h, 07Eh, 016h, 08Bh, 044h, 024h, 018h, 02Bh, 0D7h, 003h, 0D0h, 03Bh, 0D6h, 07Dh, 008h, 05Dh
    db 05Fh, 05Eh, 083h, 0C8h, 0FFh, 05Bh, 0C3h, 085h, 0F6h, 075h, 015h, 08Bh, 07Ch, 024h, 01Ch, 08Bh
    db 0CDh, 08Bh, 0F3h, 033h, 0D2h, 0F3h, 0A6h, 075h, 035h, 05Dh, 05Fh, 05Eh, 033h, 0C0h, 05Bh, 0C3h
    db 085h, 0F6h, 07Eh, 013h, 08Bh, 0C7h, 02Bh, 0C1h, 050h, 051h, 003h, 0CEh, 051h
    call ?ji_009f6ec6@@YAXXZ
    db 083h, 0C4h, 00Ch, 085h, 0F6h, 07Dh, 015h, 08Bh, 0D6h, 02Bh, 0D3h, 003h, 0D7h, 052h, 08Bh, 0C3h
    db 02Bh, 0C6h, 050h, 053h
    call ?ji_009f6ec6@@YAXXZ
    db 083h, 0C4h, 00Ch, 08Bh, 074h, 024h, 01Ch, 08Bh, 0CDh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 08Bh, 0FBh
    db 0F3h, 0A5h, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0A4h, 080h, 03Ch, 02Bh, 000h, 075h, 016h, 080h
    db 03Dh
    dd g_Va012C37EE
    db 00Ah, 074h, 00Dh, 0C6h, 044h, 02Bh, 0FFh, 000h, 08Dh, 045h, 0FFh, 05Dh, 05Fh, 05Eh, 05Bh, 0C3h
    db 0A0h
    dd g_Va012C37EE
    db 088h, 044h, 02Bh, 0FFh, 08Dh, 045h, 0FFh, 05Dh, 05Fh, 05Eh, 05Bh, 0C3h, 083h, 0C8h, 0FFh, 05Bh
    db 0C3h
?d_007e8b00@@YAXXZ ENDP
_TEXT$d00be8b00 ENDS
_TEXT SEGMENT

; ghidra: FUN_00be8e90  retail @ 0x007E8E90 size 93
public ?d_007e8e90@@YAXXZ
?d_007e8e90@@YAXXZ PROC
    db 83h, 0ECh, 24h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 89h, 44h, 24h, 24h, 8Bh, 44h, 24h
    db 34h, 50h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 34h, 51h, 8Dh, 54h, 24h, 0Ch, 68h, 0B4h, 96h
    db 12h, 01h, 52h, 0E8h, 2Ah, 0DFh, 20h, 00h, 8Bh, 4Ch, 24h, 3Ch, 8Bh, 56h, 14h, 8Dh
    db 44h, 24h, 14h, 50h, 8Bh, 46h, 10h, 51h, 52h, 50h, 0E8h, 91h, 3Fh, 00h, 00h, 83h
    db 0C4h, 20h, 85h, 0C0h, 7Dh, 07h, 0C7h, 46h, 24h, 9Ch, 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h
    db 24h, 5Eh, 0E8h, 0Dh, 0E6h, 20h, 00h, 83h, 0C4h, 24h, 0C2h, 0Ch, 00h
?d_007e8e90@@YAXXZ ENDP

; ghidra: FUN_00be8ef0  retail @ 0x007E8EF0 size 42
public ?d_007e8ef0@@YAXXZ
?d_007e8ef0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 14h, 8Bh, 4Eh, 10h, 50h, 8Bh, 44h, 24h, 10h, 51h, 8Bh
    db 4Ch, 24h, 10h, 0E8h, 28h, 0FEh, 0FFh, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 7Dh, 07h, 0C7h
    db 46h, 24h, 9Ch, 0FFh, 0FFh, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_007e8ef0@@YAXXZ ENDP

; ghidra: FUN_00be8f20  retail @ 0x007E8F20 size 243
public ?d_007e8f20@@YAXXZ
?d_007e8f20@@YAXXZ PROC
    db 83h, 0ECh, 44h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 53h, 56h, 57h, 89h, 44h, 24h, 4Ch, 8Bh
    db 0F1h, 33h, 0C0h, 0C6h, 44h, 24h, 0Ch, 00h, 0B9h, 0Fh, 00h, 00h, 00h, 8Dh, 7Ch, 24h
    db 0Dh, 0F3h, 0ABh, 66h, 0ABh, 0AAh, 8Bh, 7Ch, 24h, 58h, 57h, 8Dh, 44h, 24h, 10h, 68h
    db 28h, 97h, 12h, 01h, 50h, 0E8h, 88h, 0DEh, 20h, 00h, 8Bh, 5Ch, 24h, 60h, 83h, 0C4h
    db 0Ch, 68h, 80h, 00h, 00h, 00h, 56h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CBh, 0E8h, 0Dh
    db 0FBh, 0FFh, 0FFh, 84h, 0C0h, 75h, 12h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 40h, 0E8h, 71h
    db 0E5h, 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h, 57h, 8Dh, 54h, 24h, 10h, 68h, 10h
    db 97h, 12h, 01h, 52h, 0E8h, 49h, 0DEh, 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 04h, 8Dh, 86h
    db 80h, 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CBh, 0E8h, 0CFh, 0FAh, 0FFh
    db 0FFh, 57h, 8Dh, 54h, 24h, 10h, 68h, 0E8h, 96h, 12h, 01h, 52h, 0E8h, 21h, 0DEh, 20h
    db 00h, 83h, 0C4h, 0Ch, 6Ah, 12h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CBh, 0E8h, 2Eh, 0F9h
    db 0FFh, 0FFh, 57h, 8Dh, 4Ch, 24h, 10h, 68h, 0C4h, 96h, 12h, 01h, 51h, 89h, 86h, 84h
    db 00h, 00h, 00h, 0E8h, 0FAh, 0DDh, 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 0Dh, 8Dh, 54h, 24h
    db 10h, 52h, 8Bh, 0CBh, 0E8h, 07h, 0F9h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 4Ch, 5Fh, 89h, 86h
    db 88h, 00h, 00h, 00h, 5Eh, 0B0h, 01h, 5Bh, 0E8h, 0E7h, 0E4h, 20h, 00h, 83h, 0C4h, 44h
    db 0C2h, 08h, 00h
?d_007e8f20@@YAXXZ ENDP

; ghidra: FUN_00be9090  retail @ 0x007E9090 size 36
public ?d_007e9090@@YAXXZ
?d_007e9090@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 0Eh, 50h, 51h, 8Bh, 4Ch, 24h, 10h, 0E8h, 7Dh
    db 0FEh, 0FFh, 0FFh, 84h, 0C0h, 75h, 04h, 5Eh, 0C2h, 04h, 00h, 0FFh, 46h, 04h, 0B0h, 01h
    db 5Eh, 0C2h, 04h, 00h
?d_007e9090@@YAXXZ ENDP

; ghidra: FUN_00be90c0  retail @ 0x007E90C0 size 104
public ?d_007e90c0@@YAXXZ
?d_007e90c0@@YAXXZ PROC
    db 83h, 0ECh, 44h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 8Bh, 0F1h, 89h, 44h, 24h, 44h, 8Bh
    db 46h, 04h, 50h, 8Dh, 4Ch, 24h, 08h, 68h, 0B0h, 97h, 12h, 01h, 51h, 0E8h, 00h, 0DDh
    db 20h, 00h, 8Bh, 54h, 24h, 5Ch, 8Bh, 44h, 24h, 58h, 83h, 0C4h, 0Ch, 52h, 50h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 8Bh, 0Eh, 0E8h, 85h, 0F9h, 0FFh, 0FFh, 84h, 0C0h, 75h, 10h, 5Eh
    db 8Bh, 4Ch, 24h, 40h, 0E8h, 0EBh, 0E3h, 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h, 8Bh
    db 46h, 04h, 8Bh, 4Ch, 24h, 44h, 40h, 89h, 46h, 04h, 0B0h, 01h, 5Eh, 0E8h, 0D2h, 0E3h
    db 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h
?d_007e90c0@@YAXXZ ENDP

; ghidra: FUN_00be9130  retail @ 0x007E9130 size 151
public ?d_007e9130@@YAXXZ
?d_007e9130@@YAXXZ PROC
    db 83h, 0ECh, 44h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 8Bh, 0F1h, 89h, 44h, 24h, 44h, 8Bh
    db 46h, 04h, 50h, 8Dh, 4Ch, 24h, 08h, 68h, 0DCh, 97h, 12h, 01h, 51h, 0E8h, 90h, 0DCh
    db 20h, 00h, 8Bh, 54h, 24h, 60h, 8Bh, 44h, 24h, 58h, 83h, 0C4h, 0Ch, 52h, 50h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 8Bh, 0Eh, 0E8h, 15h, 0F9h, 0FFh, 0FFh, 84h, 0C0h, 74h, 3Fh, 8Bh
    db 56h, 04h, 52h, 8Dh, 44h, 24h, 08h, 68h, 0BCh, 97h, 12h, 01h, 50h, 0E8h, 60h, 0DCh
    db 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 8Dh, 4Ch, 24h, 08h, 51h, 8Bh, 0Eh, 0E8h, 6Dh
    db 0F7h, 0FFh, 0FFh, 8Bh, 54h, 24h, 50h, 89h, 02h, 0FFh, 46h, 04h, 0B0h, 01h, 5Eh, 8Bh
    db 4Ch, 24h, 40h, 0E8h, 4Ch, 0E3h, 20h, 00h, 83h, 0C4h, 44h, 0C2h, 0Ch, 00h, 8Bh, 4Ch
    db 24h, 44h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 32h, 0C0h, 5Eh, 0E8h, 33h, 0E3h, 20h
    db 00h, 83h, 0C4h, 44h, 0C2h, 0Ch, 00h
?d_007e9130@@YAXXZ ENDP

; ghidra: FUN_00be91d0  retail @ 0x007E91D0 size 104
public ?d_007e91d0@@YAXXZ
?d_007e91d0@@YAXXZ PROC
    db 83h, 0ECh, 44h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 8Bh, 0F1h, 89h, 44h, 24h, 44h, 8Bh
    db 46h, 04h, 50h, 8Dh, 4Ch, 24h, 08h, 68h, 0B0h, 97h, 12h, 01h, 51h, 0E8h, 0F0h, 0DBh
    db 20h, 00h, 8Bh, 54h, 24h, 5Ch, 8Bh, 44h, 24h, 58h, 83h, 0C4h, 0Ch, 52h, 50h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 8Bh, 0Eh, 0E8h, 75h, 0F8h, 0FFh, 0FFh, 84h, 0C0h, 75h, 10h, 5Eh
    db 8Bh, 4Ch, 24h, 40h, 0E8h, 0DBh, 0E2h, 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h, 8Bh
    db 46h, 04h, 8Bh, 4Ch, 24h, 44h, 40h, 89h, 46h, 04h, 0B0h, 01h, 5Eh, 0E8h, 0C2h, 0E2h
    db 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h
?d_007e91d0@@YAXXZ ENDP

; ghidra: FUN_00be9240  retail @ 0x007E9240 size 104
public ?d_007e9240@@YAXXZ
?d_007e9240@@YAXXZ PROC
    db 83h, 0ECh, 44h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 8Bh, 0F1h, 89h, 44h, 24h, 44h, 8Bh
    db 46h, 04h, 50h, 8Dh, 4Ch, 24h, 08h, 68h, 0F8h, 97h, 12h, 01h, 51h, 0E8h, 80h, 0DBh
    db 20h, 00h, 8Bh, 54h, 24h, 5Ch, 8Bh, 44h, 24h, 58h, 83h, 0C4h, 0Ch, 52h, 50h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 8Bh, 0Eh, 0E8h, 05h, 0F8h, 0FFh, 0FFh, 84h, 0C0h, 75h, 10h, 5Eh
    db 8Bh, 4Ch, 24h, 40h, 0E8h, 6Bh, 0E2h, 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h, 8Bh
    db 46h, 04h, 8Bh, 4Ch, 24h, 44h, 40h, 89h, 46h, 04h, 0B0h, 01h, 5Eh, 0E8h, 52h, 0E2h
    db 20h, 00h, 83h, 0C4h, 44h, 0C2h, 08h, 00h
?d_007e9240@@YAXXZ ENDP

; ghidra: FUN_00be92c0  retail @ 0x007E92C0 size 36
public ?d_007e92c0@@YAXXZ
?d_007e92c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C7h, 06h, 58h, 97h, 12h, 01h, 0E8h, 0F2h, 23h, 00h, 00h, 0F6h, 44h
    db 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 0D5h, 8Bh, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h
    db 5Eh, 0C2h, 04h, 00h
?d_007e92c0@@YAXXZ ENDP

; ghidra: FUN_00be93c0  retail @ 0x007E93C0 size 223
public ?d_007e93c0@@YAXXZ
?d_007e93c0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0F4h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0EDh
    db 0F6h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 29h, 0F6h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0A0h, 95h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 18h, 0F6h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 51h, 68h, 7Ch, 98h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 07h, 0F6h, 0FFh, 0FFh, 8Bh, 54h, 24h, 18h, 52h, 68h, 08h
    db 99h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0F6h, 0F5h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 50h, 68h
    db 00h, 99h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0A5h, 0F4h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 20h, 51h
    db 68h, 0F4h, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 94h, 0F4h, 0FFh, 0FFh, 8Bh, 54h, 24h, 24h
    db 52h, 68h, 0ECh, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 83h, 0F4h, 0FFh, 0FFh, 8Bh, 44h, 24h
    db 28h, 50h, 68h, 0E0h, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0B2h, 0F5h, 0FFh, 0FFh, 8Bh, 44h
    db 24h, 2Ch, 85h, 0C0h, 74h, 12h, 80h, 38h, 00h, 74h, 0Dh, 50h, 68h, 0D0h, 98h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 98h, 0F5h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 30h, 51h, 68h, 0C4h, 98h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 0F7h, 0F4h, 0FFh, 0FFh, 8Bh, 54h, 24h, 34h, 52h, 68h, 0B0h
    db 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0E6h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 2Ch, 00h
?d_007e93c0@@YAXXZ ENDP

; ghidra: FUN_00be94a0  retail @ 0x007E94A0 size 61
public ?d_007e94a0@@YAXXZ
?d_007e94a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0DCh, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0Dh
    db 0F6h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 49h, 0F5h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0A0h, 95h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 38h, 0F5h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_007e94a0@@YAXXZ ENDP

; ghidra: FUN_00be94e0  retail @ 0x007E94E0 size 61
public ?d_007e94e0@@YAXXZ
?d_007e94e0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 18h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0CDh
    db 0F5h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 09h, 0F5h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0A0h, 95h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 0F8h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_007e94e0@@YAXXZ ENDP

; ghidra: FUN_00be9520  retail @ 0x007E9520 size 61
public ?d_007e9520@@YAXXZ
?d_007e9520@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 24h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 8Dh
    db 0F5h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 0C9h, 0F4h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 08h, 99h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 0B8h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_007e9520@@YAXXZ ENDP

; ghidra: FUN_00be9560  retail @ 0x007E9560 size 61
public ?d_007e9560@@YAXXZ
?d_007e9560@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 00h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 4Dh
    db 0F5h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 89h, 0F4h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0A0h, 95h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 78h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_007e9560@@YAXXZ ENDP

; ghidra: FUN_00be95a0  retail @ 0x007E95A0 size 44
public ?d_007e95a0@@YAXXZ
?d_007e95a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 78h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0Dh
    db 0F5h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 49h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e95a0@@YAXXZ ENDP

; ghidra: FUN_00be95d0  retail @ 0x007E95D0 size 44
public ?d_007e95d0@@YAXXZ
?d_007e95d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 94h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0DDh
    db 0F4h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 19h, 0F4h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e95d0@@YAXXZ ENDP

; ghidra: FUN_00be9600  retail @ 0x007E9600 size 174
public ?d_007e9600@@YAXXZ
?d_007e9600@@YAXXZ PROC
    db 83h, 0ECh, 24h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 53h, 56h, 8Bh, 35h, 0B8h, 0A4h, 30h, 01h
    db 57h, 8Bh, 7Ch, 24h, 34h, 8Bh, 0CFh, 89h, 44h, 24h, 2Ch, 0E8h, 0A0h, 0F4h, 0FFh, 0FFh
    db 56h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CFh, 0C7h, 47h, 1Ch, 74h, 63h, 63h, 61h, 0E8h
    db 0DCh, 0F3h, 0FFh, 0FFh, 8Bh, 44h, 24h, 38h, 50h, 68h, 0A0h, 95h, 11h, 01h, 8Bh, 0CFh
    db 0E8h, 0CBh, 0F3h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 44h, 51h, 68h, 28h, 99h, 12h, 01h, 8Bh
    db 0CFh, 0E8h, 7Ah, 0F2h, 0FFh, 0FFh, 8Bh, 5Ch, 24h, 40h, 33h, 0F6h, 85h, 0DBh, 7Eh, 2Fh
    db 55h, 8Bh, 6Ch, 24h, 40h, 56h, 8Dh, 54h, 24h, 14h, 68h, 1Ch, 99h, 12h, 01h, 52h
    db 0E8h, 6Dh, 0D7h, 20h, 00h, 8Bh, 44h, 0B5h, 00h, 83h, 0C4h, 0Ch, 50h, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0CFh, 0E8h, 87h, 0F3h, 0FFh, 0FFh, 46h, 3Bh, 0F3h, 7Ch, 0D7h, 5Dh, 53h
    db 68h, 10h, 99h, 12h, 01h, 8Bh, 0CFh, 0E8h, 34h, 0F2h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 2Ch
    db 5Fh, 5Eh, 5Bh, 0E8h, 4Ch, 0DEh, 20h, 00h, 83h, 0C4h, 24h, 0C2h, 14h, 00h
?d_007e9600@@YAXXZ ENDP

; ghidra: FUN_00be96b0  retail @ 0x007E96B0 size 174
public ?d_007e96b0@@YAXXZ
?d_007e96b0@@YAXXZ PROC
    db 83h, 0ECh, 24h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 53h, 56h, 8Bh, 35h, 48h, 0A5h, 30h, 01h
    db 57h, 8Bh, 7Ch, 24h, 34h, 8Bh, 0CFh, 89h, 44h, 24h, 2Ch, 0E8h, 0F0h, 0F3h, 0FFh, 0FFh
    db 56h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CFh, 0C7h, 47h, 1Ch, 74h, 63h, 63h, 61h, 0E8h
    db 2Ch, 0F3h, 0FFh, 0FFh, 8Bh, 44h, 24h, 38h, 50h, 68h, 0A0h, 95h, 11h, 01h, 8Bh, 0CFh
    db 0E8h, 1Bh, 0F3h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 44h, 51h, 68h, 28h, 99h, 12h, 01h, 8Bh
    db 0CFh, 0E8h, 0CAh, 0F1h, 0FFh, 0FFh, 8Bh, 5Ch, 24h, 40h, 33h, 0F6h, 85h, 0DBh, 7Eh, 2Fh
    db 55h, 8Bh, 6Ch, 24h, 40h, 56h, 8Dh, 54h, 24h, 14h, 68h, 1Ch, 99h, 12h, 01h, 52h
    db 0E8h, 0BDh, 0D6h, 20h, 00h, 8Bh, 44h, 0B5h, 00h, 83h, 0C4h, 0Ch, 50h, 8Dh, 4Ch, 24h
    db 14h, 51h, 8Bh, 0CFh, 0E8h, 0D7h, 0F2h, 0FFh, 0FFh, 46h, 3Bh, 0F3h, 7Ch, 0D7h, 5Dh, 53h
    db 68h, 10h, 99h, 12h, 01h, 8Bh, 0CFh, 0E8h, 84h, 0F1h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 2Ch
    db 5Fh, 5Eh, 5Bh, 0E8h, 9Ch, 0DDh, 20h, 00h, 83h, 0C4h, 24h, 0C2h, 14h, 00h
?d_007e96b0@@YAXXZ ENDP

; ghidra: FUN_00be9760  retail @ 0x007E9760 size 173
public ?d_007e9760@@YAXXZ
?d_007e9760@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 30h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 4Dh
    db 0F3h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 89h, 0F2h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 4Ch, 99h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 78h, 0F2h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 51h, 68h, 44h, 99h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 67h, 0F2h, 0FFh, 0FFh, 8Bh, 54h, 24h, 18h, 52h, 68h, 38h
    db 99h, 12h, 01h, 8Bh, 0CEh, 0E8h, 56h, 0F2h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h
    db 74h, 12h, 80h, 38h, 00h, 74h, 0Dh, 50h, 68h, 0A0h, 95h, 11h, 01h, 8Bh, 0CEh, 0E8h
    db 3Ch, 0F2h, 0FFh, 0FFh, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 74h, 12h, 80h, 38h, 00h, 74h
    db 0Dh, 50h, 68h, 7Ch, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 22h, 0F2h, 0FFh, 0FFh, 8Bh, 44h
    db 24h, 24h, 85h, 0C0h, 74h, 12h, 80h, 38h, 00h, 74h, 0Dh, 50h, 68h, 88h, 98h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 08h, 0F2h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 1Ch, 00h
?d_007e9760@@YAXXZ ENDP

; ghidra: FUN_00be9810  retail @ 0x007E9810 size 78
public ?d_007e9810@@YAXXZ
?d_007e9810@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 60h, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 9Dh
    db 0F2h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 0D9h, 0F1h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 7Ch, 98h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 0C8h, 0F1h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 51h, 68h, 54h, 99h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 0B7h, 0F1h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_007e9810@@YAXXZ ENDP

; ghidra: FUN_00be9860  retail @ 0x007E9860 size 61
public ?d_007e9860@@YAXXZ
?d_007e9860@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0A0h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 4Dh
    db 0F2h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 89h, 0F1h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0A0h, 95h, 11h
    db 01h, 8Bh, 0CEh, 0E8h, 78h, 0F1h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_007e9860@@YAXXZ ENDP

; ghidra: FUN_00be98a0  retail @ 0x007E98A0 size 44
public ?d_007e98a0@@YAXXZ
?d_007e98a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0C4h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0Dh
    db 0F2h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 49h, 0F1h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e98a0@@YAXXZ ENDP

; ghidra: FUN_00be98d0  retail @ 0x007E98D0 size 44
public ?d_007e98d0@@YAXXZ
?d_007e98d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 3Ch, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0DDh
    db 0F1h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 19h, 0F1h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e98d0@@YAXXZ ENDP

; ghidra: FUN_00be9900  retail @ 0x007E9900 size 129
public ?d_007e9900@@YAXXZ
?d_007e9900@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0ACh, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0ADh
    db 0F1h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 0E9h, 0F0h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 08h, 99h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 0D8h, 0F0h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 51h, 68h, 0D0h, 98h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 0C7h, 0F0h, 0FFh, 0FFh, 8Bh, 54h, 24h, 18h, 52h, 68h, 0E0h
    db 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0B6h, 0F0h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 50h, 68h
    db 0C4h, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 15h, 0F0h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 20h, 51h
    db 68h, 0B0h, 98h, 12h, 01h, 8Bh, 0CEh, 0E8h, 04h, 0F0h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 18h
    db 00h
?d_007e9900@@YAXXZ ENDP

; ghidra: FUN_00be9990  retail @ 0x007E9990 size 44
public ?d_007e9990@@YAXXZ
?d_007e9990@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0D0h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 1Dh
    db 0F1h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 59h, 0F0h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e9990@@YAXXZ ENDP

; ghidra: FUN_00be99c0  retail @ 0x007E99C0 size 44
public ?d_007e99c0@@YAXXZ
?d_007e99c0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 6Ch, 0A5h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0EDh
    db 0F0h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 29h, 0F0h, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007e99c0@@YAXXZ ENDP

; ghidra: FUN_00be99f0  retail @ 0x007E99F0 size 78
public ?d_007e99f0@@YAXXZ
?d_007e99f0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 3Dh, 0E8h, 0A4h, 30h, 01h, 8Bh, 0CEh, 0E8h, 0BDh
    db 0F0h, 0FFh, 0FFh, 57h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h, 1Ch, 74h, 63h
    db 63h, 61h, 0E8h, 0F9h, 0EFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 68h, 0C4h, 98h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 58h, 0EFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 14h, 51h, 68h, 0B0h, 98h
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 47h, 0EFh, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_007e99f0@@YAXXZ ENDP

; ghidra: FUN_00be9b10  retail @ 0x007E9B10 size 38
public ?d_007e9b10@@YAXXZ
?d_007e9b10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C7h, 06h, 58h, 97h, 12h, 01h, 0E8h, 0A2h, 1Bh, 00h, 00h, 0F6h, 44h
    db 24h, 08h, 01h, 74h, 0Bh, 6Ah, 0Ch, 56h, 0E8h, 43h, 66h, 00h, 00h, 83h, 0C4h, 08h
    db 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007e9b10@@YAXXZ ENDP

; ghidra: FUN_00be9b40  retail @ 0x007E9B40 size 45
public ?d_007e9b40@@YAXXZ
?d_007e9b40@@YAXXZ PROC
    db 6Ah, 0Ch, 0E8h, 0E9h, 65h, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 1Ch, 8Bh, 4Ch
    db 24h, 04h, 0C7h, 40h, 04h, 44h, 97h, 12h, 01h, 89h, 48h, 08h, 0C7h, 00h, 10h, 98h
    db 12h, 01h, 0C7h, 40h, 04h, 08h, 98h, 12h, 01h, 0C3h, 33h, 0C0h, 0C3h
?d_007e9b40@@YAXXZ ENDP

; ghidra: FUN_00be9b80  retail @ 0x007E9B80 size 33
public ?d_007e9b80@@YAXXZ
?d_007e9b80@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 68h, 67h, 00h, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 0C7h, 06h
    db 9Ch, 9Ah, 12h, 01h, 0FFh, 15h, 0F4h, 8Ch, 35h, 01h, 89h, 46h, 04h, 8Bh, 0C6h, 5Eh
    db 0C3h
?d_007e9b80@@YAXXZ ENDP

; ghidra: FUN_00be9c20  retail @ 0x007E9C20 size 31
public ?d_007e9c20@@YAXXZ
?d_007e9c20@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 9Ch, 9Ah, 12h, 01h, 74h, 07h
    db 50h, 0FFh, 15h, 0CCh, 8Ch, 35h, 01h, 8Bh, 0CEh, 5Eh, 0E9h, 0C1h, 66h, 00h, 00h
?d_007e9c20@@YAXXZ ENDP

; ghidra: FUN_00be9c40  retail @ 0x007E9C40 size 52
public ?d_007e9c40@@YAXXZ
?d_007e9c40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 0C7h, 06h, 9Ch, 9Ah, 12h, 01h, 74h, 07h
    db 50h, 0FFh, 15h, 0CCh, 8Ch, 35h, 01h, 8Bh, 0CEh, 0E8h, 0A2h, 66h, 00h, 00h, 0F6h, 44h
    db 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 45h, 82h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h
    db 5Eh, 0C2h, 04h, 00h
?d_007e9c40@@YAXXZ ENDP

; ghidra: FUN_00be9ce0  retail @ 0x007E9CE0 size 56
public ?d_007e9ce0@@YAXXZ
?d_007e9ce0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 4Ch, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 2Ah, 7Fh, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 4Ch, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 4Ch, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 4Ch, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9ce0@@YAXXZ ENDP

; ghidra: FUN_00be9d70  retail @ 0x007E9D70 size 56
public ?d_007e9d70@@YAXXZ
?d_007e9d70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 34h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 0BAh, 0FDh, 0FFh, 0FFh, 8Bh, 4Eh, 04h, 89h, 81h, 34h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 34h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 34h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9d70@@YAXXZ ENDP

; ghidra: FUN_00be9db0  retail @ 0x007E9DB0 size 56
public ?d_007e9db0@@YAXXZ
?d_007e9db0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 48h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 8Ah, 83h, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 48h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 48h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 48h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9db0@@YAXXZ ENDP

; ghidra: FUN_00be9df0  retail @ 0x007E9DF0 size 56
public ?d_007e9df0@@YAXXZ
?d_007e9df0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 38h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 5Ah, 90h, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 38h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 38h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 38h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9df0@@YAXXZ ENDP

; ghidra: FUN_00be9e30  retail @ 0x007E9E30 size 56
public ?d_007e9e30@@YAXXZ
?d_007e9e30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 3Ch, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 0CAh, 95h, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 3Ch, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 3Ch, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 3Ch, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9e30@@YAXXZ ENDP

; ghidra: FUN_00be9e70  retail @ 0x007E9E70 size 56
public ?d_007e9e70@@YAXXZ
?d_007e9e70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 40h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 6Ah, 0A2h, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 40h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 40h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 40h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9e70@@YAXXZ ENDP

; ghidra: FUN_00be9eb0  retail @ 0x007E9EB0 size 36
public ?d_007e9eb0@@YAXXZ
?d_007e9eb0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 44h, 02h, 00h, 00h, 85h, 0C0h, 75h, 0Fh, 56h, 0E8h, 4Dh
    db 0A9h, 00h, 00h, 83h, 0C4h, 04h, 89h, 86h, 44h, 02h, 00h, 00h, 8Bh, 86h, 44h, 02h
    db 00h, 00h, 5Eh, 0C3h
?d_007e9eb0@@YAXXZ ENDP

; ghidra: FUN_00be9ee0  retail @ 0x007E9EE0 size 16
public ?d_007e9ee0@@YAXXZ
?d_007e9ee0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 68h, 0AEh, 00h, 00h, 89h, 86h, 0A0h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9ee0@@YAXXZ ENDP

; ghidra: FUN_00be9ef0  retail @ 0x007E9EF0 size 56
public ?d_007e9ef0@@YAXXZ
?d_007e9ef0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 0A4h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 9Ah, 0E7h, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 0A4h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 0A4h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 0A4h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9ef0@@YAXXZ ENDP

; ghidra: FUN_00be9f30  retail @ 0x007E9F30 size 56
public ?d_007e9f30@@YAXXZ
?d_007e9f30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 88h, 0A8h, 02h, 00h, 00h, 85h, 0C9h, 75h, 1Dh
    db 50h, 0E8h, 8Ah, 0EAh, 00h, 00h, 8Bh, 4Eh, 04h, 89h, 81h, 0A8h, 02h, 00h, 00h, 8Bh
    db 56h, 04h, 8Bh, 82h, 0A8h, 02h, 00h, 00h, 83h, 0C4h, 04h, 5Eh, 0C3h, 8Bh, 46h, 04h
    db 8Bh, 80h, 0A8h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007e9f30@@YAXXZ ENDP

; ghidra: FUN_00be9fc0  retail @ 0x007E9FC0 size 221
public ?d_007e9fc0@@YAXXZ
?d_007e9fc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 56h, 8Bh, 0F1h, 74h, 68h, 8Bh, 8Eh, 54h, 02h, 00h
    db 00h, 89h, 86h, 60h, 02h, 00h, 00h, 8Bh, 44h, 24h, 08h, 89h, 86h, 64h, 02h, 00h
    db 00h, 8Bh, 89h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 6Ah, 00h, 6Ah, 02h, 0FFh, 52h, 08h
    db 8Bh, 8Eh, 50h, 02h, 00h, 00h, 8Bh, 01h, 33h, 0D2h, 8Ah, 96h, 30h, 02h, 00h, 00h
    db 52h, 8Dh, 96h, 58h, 02h, 00h, 00h, 52h, 0FFh, 50h, 10h, 85h, 0C0h, 0Fh, 84h, 86h
    db 00h, 00h, 00h, 89h, 44h, 24h, 08h, 8Bh, 86h, 54h, 02h, 00h, 00h, 8Bh, 88h, 0A8h
    db 06h, 00h, 00h, 8Bh, 11h, 8Dh, 44h, 24h, 08h, 50h, 6Ah, 00h, 0FFh, 52h, 08h, 5Eh
    db 0C2h, 08h, 00h, 8Ah, 86h, 0A0h, 00h, 00h, 00h, 84h, 0C0h, 75h, 35h, 8Ah, 86h, 0ACh
    db 02h, 00h, 00h, 84h, 0C0h, 75h, 2Bh, 8Bh, 44h, 24h, 08h, 8Bh, 4Eh, 0Ch, 56h, 68h
    db 10h, 0ACh, 0BEh, 00h, 50h, 8Dh, 86h, 90h, 00h, 00h, 00h, 50h, 0C6h, 86h, 0ACh, 02h
    db 00h, 00h, 01h, 8Bh, 11h, 6Ah, 00h, 83h, 0C6h, 30h, 56h, 0FFh, 52h, 08h, 5Eh, 0C2h
    db 08h, 00h, 8Bh, 8Eh, 54h, 02h, 00h, 00h, 0C6h, 86h, 0ACh, 02h, 00h, 00h, 00h, 0C7h
    db 44h, 24h, 08h, 35h, 0FFh, 0FFh, 0FFh, 8Bh, 89h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 8Dh
    db 44h, 24h, 08h, 50h, 6Ah, 00h, 0FFh, 52h, 08h, 5Eh, 0C2h, 08h, 00h
?d_007e9fc0@@YAXXZ ENDP

; ghidra: FUN_00bea0a0  retail @ 0x007EA0A0 size 118
public ?d_007ea0a0@@YAXXZ
?d_007ea0a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 54h, 02h, 00h, 00h, 85h, 0C0h, 57h, 8Bh, 7Ch, 24h, 0Ch
    db 74h, 19h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 01h, 57h, 6Ah, 00h, 0FFh, 50h, 08h
    db 8Bh, 8Eh, 50h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 14h, 8Bh, 86h, 88h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 19h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 01h, 57h, 6Ah, 00h
    db 0FFh, 50h, 08h, 8Bh, 8Eh, 84h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 14h, 8Bh, 86h
    db 6Ch, 02h, 00h, 00h, 85h, 0C0h, 74h, 19h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 01h
    db 57h, 6Ah, 00h, 0FFh, 50h, 08h, 8Bh, 8Eh, 68h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h
    db 14h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007ea0a0@@YAXXZ ENDP

; ghidra: FUN_00bea120  retail @ 0x007EA120 size 458
public ?d_007ea120@@YAXXZ
?d_007ea120@@YAXXZ PROC
    db 51h, 53h, 56h, 8Dh, 44h, 24h, 08h, 50h, 8Bh, 0F1h, 0C7h, 44h, 24h, 0Ch, 33h, 0FFh
    db 0FFh, 0FFh, 0E8h, 69h, 0FFh, 0FFh, 0FFh, 8Bh, 8Eh, 0A4h, 02h, 00h, 00h, 33h, 0DBh, 3Bh
    db 0CBh, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 0A8h, 02h, 00h, 00h, 3Bh
    db 0CBh, 89h, 9Eh, 0A4h, 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh
    db 8Eh, 9Ch, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 0A8h, 02h, 00h, 00h, 74h, 06h, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 80h, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 9Ch
    db 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 8Eh, 40h, 02h, 00h
    db 00h, 3Bh, 0CBh, 89h, 9Eh, 80h, 02h, 00h, 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh
    db 12h, 8Bh, 8Eh, 3Ch, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 40h, 02h, 00h, 00h, 74h
    db 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 8Eh, 38h, 02h, 00h, 00h, 3Bh, 0CBh, 89h
    db 9Eh, 3Ch, 02h, 00h, 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 34h
    db 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 38h, 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah
    db 01h, 0FFh, 10h, 8Bh, 8Eh, 44h, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 34h, 02h, 00h
    db 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 54h, 02h, 00h, 00h, 3Bh
    db 0CBh, 89h, 9Eh, 44h, 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh
    db 8Eh, 6Ch, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 54h, 02h, 00h, 00h, 74h, 06h, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 88h, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 6Ch
    db 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 8Eh, 0A0h, 02h, 00h
    db 00h, 3Bh, 0CBh, 89h, 9Eh, 88h, 02h, 00h, 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh
    db 12h, 8Bh, 8Eh, 84h, 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 0A0h, 02h, 00h, 00h, 74h
    db 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 8Eh, 68h, 02h, 00h, 00h, 3Bh, 0CBh, 89h
    db 9Eh, 84h, 02h, 00h, 00h, 74h, 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 8Eh, 50h
    db 02h, 00h, 00h, 3Bh, 0CBh, 89h, 9Eh, 68h, 02h, 00h, 00h, 74h, 06h, 8Bh, 01h, 6Ah
    db 01h, 0FFh, 10h, 8Bh, 4Eh, 0Ch, 3Bh, 0CBh, 89h, 9Eh, 50h, 02h, 00h, 00h, 74h, 06h
    db 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 89h, 5Eh, 0Ch, 89h, 9Eh, 24h, 02h, 00h, 00h, 89h
    db 9Eh, 28h, 02h, 00h, 00h, 89h, 9Eh, 2Ch, 02h, 00h, 00h, 88h, 9Eh, 90h, 00h, 00h
    db 00h, 88h, 9Eh, 0A0h, 00h, 00h, 00h, 88h, 9Eh, 0E1h, 00h, 00h, 00h, 88h, 9Eh, 01h
    db 01h, 00h, 00h, 88h, 9Eh, 42h, 01h, 00h, 00h, 88h, 9Eh, 0ACh, 02h, 00h, 00h, 0C6h
    db 86h, 30h, 02h, 00h, 00h, 01h, 5Eh, 5Bh, 59h, 0C3h
?d_007ea120@@YAXXZ ENDP

; ghidra: FUN_00bea300  retail @ 0x007EA300 size 20
public ?d_007ea300@@YAXXZ
?d_007ea300@@YAXXZ PROC
    db 51h, 8Dh, 04h, 24h, 50h, 0C7h, 44h, 24h, 04h, 34h, 0FFh, 0FFh, 0FFh, 0E8h, 8Eh, 0FDh
    db 0FFh, 0FFh, 59h, 0C3h
?d_007ea300@@YAXXZ ENDP

; ghidra: FUN_00bea320  retail @ 0x007EA320 size 89
public ?d_007ea320@@YAXXZ
?d_007ea320@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 85h, 0C9h, 74h, 2Ch, 89h, 88h, 78h, 02h, 00h, 00h
    db 8Bh, 4Ch, 24h, 04h, 89h, 88h, 7Ch, 02h, 00h, 00h, 8Bh, 88h, 68h, 02h, 00h, 00h
    db 8Bh, 11h, 05h, 70h, 02h, 00h, 00h, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 89h
    db 44h, 24h, 04h, 0FFh, 62h, 10h, 8Bh, 80h, 6Ch, 02h, 00h, 00h, 0C7h, 44h, 24h, 08h
    db 35h, 0FFh, 0FFh, 0FFh, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 8Dh, 44h, 24h, 08h
    db 50h, 6Ah, 00h, 0FFh, 52h, 08h, 0C2h, 08h, 00h
?d_007ea320@@YAXXZ ENDP

; ghidra: FUN_00bea380  retail @ 0x007EA380 size 89
public ?d_007ea380@@YAXXZ
?d_007ea380@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 08h, 85h, 0C9h, 74h, 2Ch, 89h, 88h, 94h, 02h, 00h, 00h
    db 8Bh, 4Ch, 24h, 04h, 89h, 88h, 98h, 02h, 00h, 00h, 8Bh, 88h, 84h, 02h, 00h, 00h
    db 8Bh, 11h, 05h, 8Ch, 02h, 00h, 00h, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 89h
    db 44h, 24h, 04h, 0FFh, 62h, 10h, 8Bh, 80h, 88h, 02h, 00h, 00h, 0C7h, 44h, 24h, 08h
    db 35h, 0FFh, 0FFh, 0FFh, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 8Dh, 44h, 24h, 08h
    db 50h, 6Ah, 00h, 0FFh, 52h, 08h, 0C2h, 08h, 00h
?d_007ea380@@YAXXZ ENDP

; ghidra: FUN_00bea400  retail @ 0x007EA400 size 99
public ?d_007ea400@@YAXXZ
?d_007ea400@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 50h, 81h, 0C1h, 0A0h, 00h, 00h
    db 00h, 6Ah, 41h, 51h, 0E8h, 27h, 0E2h, 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 83h, 0C4h, 0Ch
    db 85h, 0C0h, 75h, 05h, 0B8h, 1Ch, 30h, 07h, 01h, 8Bh, 56h, 04h, 50h, 81h, 0C2h, 01h
    db 01h, 00h, 00h, 6Ah, 41h, 52h, 0E8h, 05h, 0E2h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 83h
    db 0C4h, 0Ch, 85h, 0C0h, 75h, 05h, 0B8h, 1Ch, 30h, 07h, 01h, 50h, 8Bh, 46h, 04h, 05h
    db 42h, 01h, 00h, 00h, 6Ah, 41h, 50h, 0E8h, 0E4h, 0E1h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 5Eh
    db 0C2h, 0Ch, 00h
?d_007ea400@@YAXXZ ENDP

; ghidra: FUN_00bea4f0  retail @ 0x007EA4F0 size 44
public ?d_007ea4f0@@YAXXZ
?d_007ea4f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 04h, 8Bh, 87h, 0A0h, 02h, 00h, 00h, 85h, 0C0h, 75h
    db 0Bh, 0E8h, 4Ah, 0A8h, 00h, 00h, 89h, 87h, 0A0h, 02h, 00h, 00h, 8Bh, 46h, 04h, 8Bh
    db 88h, 0A0h, 02h, 00h, 00h, 8Bh, 11h, 5Fh, 5Eh, 0FFh, 62h, 14h
?d_007ea4f0@@YAXXZ ENDP

; ghidra: FUN_00bea520  retail @ 0x007EA520 size 44
public ?d_007ea520@@YAXXZ
?d_007ea520@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 04h, 8Bh, 87h, 0A0h, 02h, 00h, 00h, 85h, 0C0h, 75h
    db 0Bh, 0E8h, 1Ah, 0A8h, 00h, 00h, 89h, 87h, 0A0h, 02h, 00h, 00h, 8Bh, 46h, 04h, 8Bh
    db 88h, 0A0h, 02h, 00h, 00h, 8Bh, 11h, 5Fh, 5Eh, 0FFh, 62h, 18h
?d_007ea520@@YAXXZ ENDP

; ghidra: FUN_00bea550  retail @ 0x007EA550 size 60
public ?d_007ea550@@YAXXZ
?d_007ea550@@YAXXZ PROC
    db 33h, 0C0h, 8Dh, 51h, 10h, 83h, 3Ah, 00h, 74h, 27h, 40h, 83h, 0C2h, 04h, 83h, 0F8h
    db 08h, 7Ch, 0F2h, 0E8h, 0A8h, 12h, 00h, 00h, 8Bh, 10h, 68h, 0A7h, 02h, 00h, 00h, 68h
    db 0F8h, 9Ah, 12h, 01h, 68h, 0A0h, 0C2h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 0C2h, 04h
    db 00h, 8Bh, 54h, 24h, 04h, 89h, 54h, 81h, 10h, 0C2h, 04h, 00h
?d_007ea550@@YAXXZ ENDP

; ghidra: FUN_00bea590  retail @ 0x007EA590 size 72
public ?d_007ea590@@YAXXZ
?d_007ea590@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 33h, 0C0h, 8Dh, 51h, 10h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 32h, 74h, 28h, 40h, 83h, 0C2h, 04h, 83h, 0F8h, 08h, 7Ch, 0F3h, 0E8h, 5Eh, 12h
    db 00h, 00h, 8Bh, 10h, 68h, 0B6h, 02h, 00h, 00h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 0A0h
    db 0C2h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 5Eh, 0C2h, 04h, 00h, 0C7h, 44h, 81h, 10h
    db 00h, 00h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_007ea590@@YAXXZ ENDP

; ghidra: FUN_00bea5e0  retail @ 0x007EA5E0 size 87
public ?d_007ea5e0@@YAXXZ
?d_007ea5e0@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 0E9h, 0E8h, 85h, 0F5h, 0FFh, 0FFh, 8Bh, 10h, 8Bh, 0C8h, 0FFh
    db 52h, 0Ch, 0E8h, 79h, 0F5h, 0FFh, 0FFh, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 08h, 8Bh, 0D8h
    db 8Dh, 75h, 10h, 0BFh, 08h, 00h, 00h, 00h, 8Bh, 06h, 85h, 0C0h, 74h, 07h, 8Bh, 0C8h
    db 8Bh, 01h, 53h, 0FFh, 10h, 83h, 0C6h, 04h, 4Fh, 75h, 0EDh, 0E8h, 50h, 0F5h, 0FFh, 0FFh
    db 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 10h, 0F6h, 45h, 08h, 02h, 5Fh, 5Eh, 5Dh, 5Bh, 75h
    db 05h, 0E9h, 5Ah, 0E6h, 00h, 00h, 0C3h
?d_007ea5e0@@YAXXZ ENDP

; ghidra: FUN_00bea660  retail @ 0x007EA660 size 7
public ?d_007ea660@@YAXXZ
?d_007ea660@@YAXXZ PROC
    db 8Dh, 81h, 03h, 02h, 00h, 00h, 0C3h
?d_007ea660@@YAXXZ ENDP

; ghidra: FUN_00bea670  retail @ 0x007EA670 size 17
public ?d_007ea670@@YAXXZ
?d_007ea670@@YAXXZ PROC
    db 8Dh, 81h, 0E1h, 00h, 00h, 00h, 80h, 38h, 00h, 75h, 05h, 0B8h, 30h, 9Bh, 12h, 01h
    db 0C3h
?d_007ea670@@YAXXZ ENDP

; ghidra: FUN_00bea6f0  retail @ 0x007EA6F0 size 625
public ?d_007ea6f0@@YAXXZ
?d_007ea6f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 0A4h, 02h, 00h, 00h, 85h, 0C0h, 0C7h, 06h, 0B0h, 9Ch, 12h
    db 01h, 74h, 18h, 0E8h, 08h, 11h, 00h, 00h, 8Bh, 10h, 6Ah, 6Dh, 68h, 0F8h, 9Ah, 12h
    db 01h, 68h, 9Ch, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 0A8h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 18h, 0E8h, 0E6h, 10h, 00h, 00h, 8Bh, 10h, 6Ah, 6Eh, 68h, 0F8h
    db 9Ah, 12h, 01h, 68h, 8Ch, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 9Ch
    db 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 0C4h, 10h, 00h, 00h, 8Bh, 10h, 6Ah, 6Fh
    db 68h, 0F8h, 9Ah, 12h, 01h, 68h, 74h, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh
    db 86h, 80h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 0A2h, 10h, 00h, 00h, 8Bh, 10h
    db 6Ah, 70h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 5Ch, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h
    db 0Ch, 8Bh, 86h, 40h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 80h, 10h, 00h, 00h
    db 8Bh, 10h, 6Ah, 71h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 48h, 9Ch, 12h, 01h, 8Bh, 0C8h
    db 0FFh, 52h, 0Ch, 8Bh, 86h, 3Ch, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 5Eh, 10h
    db 00h, 00h, 8Bh, 10h, 6Ah, 72h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 34h, 9Ch, 12h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 38h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h
    db 3Ch, 10h, 00h, 00h, 8Bh, 10h, 6Ah, 73h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 1Ch, 9Ch
    db 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 34h, 02h, 00h, 00h, 85h, 0C0h, 74h
    db 18h, 0E8h, 1Ah, 10h, 00h, 00h, 8Bh, 10h, 6Ah, 74h, 68h, 0F8h, 9Ah, 12h, 01h, 68h
    db 04h, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 44h, 02h, 00h, 00h, 85h
    db 0C0h, 74h, 18h, 0E8h, 0F8h, 0Fh, 00h, 00h, 8Bh, 10h, 6Ah, 75h, 68h, 0F8h, 9Ah, 12h
    db 01h, 68h, 0ECh, 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 54h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 18h, 0E8h, 0D6h, 0Fh, 00h, 00h, 8Bh, 10h, 6Ah, 76h, 68h, 0F8h
    db 9Ah, 12h, 01h, 68h, 0D0h, 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 6Ch
    db 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 0B4h, 0Fh, 00h, 00h, 8Bh, 10h, 6Ah, 77h
    db 68h, 0F8h, 9Ah, 12h, 01h, 68h, 0B0h, 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh
    db 86h, 88h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 92h, 0Fh, 00h, 00h, 8Bh, 10h
    db 6Ah, 78h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 94h, 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h
    db 0Ch, 8Bh, 86h, 0A0h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 70h, 0Fh, 00h, 00h
    db 8Bh, 10h, 6Ah, 79h, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 80h, 9Bh, 12h, 01h, 8Bh, 0C8h
    db 0FFh, 52h, 0Ch, 8Bh, 86h, 84h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h, 4Eh, 0Fh
    db 00h, 00h, 8Bh, 10h, 6Ah, 7Ah, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 6Ch, 9Bh, 12h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 68h, 02h, 00h, 00h, 85h, 0C0h, 74h, 18h, 0E8h
    db 2Ch, 0Fh, 00h, 00h, 8Bh, 10h, 6Ah, 7Bh, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 58h, 9Bh
    db 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 86h, 50h, 02h, 00h, 00h, 85h, 0C0h, 74h
    db 18h, 0E8h, 0Ah, 0Fh, 00h, 00h, 8Bh, 10h, 6Ah, 7Ch, 68h, 0F8h, 9Ah, 12h, 01h, 68h
    db 48h, 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 18h
    db 0E8h, 0EBh, 0Eh, 00h, 00h, 8Bh, 10h, 6Ah, 7Dh, 68h, 0F8h, 9Ah, 12h, 01h, 68h, 34h
    db 9Bh, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Dh, 8Eh, 8Ch, 02h, 00h, 00h, 0E8h, 7Dh
    db 0DDh, 0FFh, 0FFh, 8Dh, 8Eh, 70h, 02h, 00h, 00h, 0E8h, 72h, 0DDh, 0FFh, 0FFh, 8Dh, 8Eh
    db 58h, 02h, 00h, 00h, 0E8h, 67h, 0DDh, 0FFh, 0FFh, 0C7h, 06h, 0F4h, 9Ah, 12h, 01h, 5Eh
    db 0C3h
?d_007ea6f0@@YAXXZ ENDP

; ghidra: FUN_00bea9c0  retail @ 0x007EA9C0 size 164
public ?d_007ea9c0@@YAXXZ
?d_007ea9c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0F6h, 46h, 08h, 01h, 75h, 0Ah, 6Ah, 00h, 0E8h, 0B0h, 09h, 00h, 00h
    db 83h, 0C4h, 04h, 56h, 0E8h, 97h, 03h, 01h, 00h, 89h, 46h, 0Ch, 0E8h, 1Fh, 0FFh, 00h
    db 00h, 68h, 0B8h, 06h, 00h, 00h, 89h, 86h, 50h, 02h, 00h, 00h, 0E8h, 3Fh, 57h, 00h
    db 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0Ah, 56h, 8Bh, 0C8h, 0E8h, 80h, 0F1h, 00h, 00h
    db 0EBh, 02h, 33h, 0C0h, 85h, 0C0h, 89h, 86h, 54h, 02h, 00h, 00h, 74h, 05h, 83h, 0C0h
    db 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 8Eh, 50h, 02h, 00h, 00h, 8Bh, 11h, 50h, 0FFh, 52h
    db 04h, 8Bh, 86h, 50h, 02h, 00h, 00h, 8Bh, 8Eh, 54h, 02h, 00h, 00h, 50h, 0E8h, 5Dh
    db 0EBh, 00h, 00h, 0E8h, 78h, 0E5h, 00h, 00h, 8Bh, 8Eh, 54h, 02h, 00h, 00h, 89h, 41h
    db 24h, 8Bh, 86h, 54h, 02h, 00h, 00h, 85h, 0C0h, 74h, 0Dh, 83h, 0C0h, 08h, 50h, 8Bh
    db 0CEh, 0E8h, 0FAh, 0FAh, 0FFh, 0FFh, 5Eh, 0C3h, 33h, 0C0h, 50h, 8Bh, 0CEh, 0E8h, 0EEh, 0FAh
    db 0FFh, 0FFh, 5Eh, 0C3h
?d_007ea9c0@@YAXXZ ENDP

; ghidra: FUN_00beaa70  retail @ 0x007EAA70 size 163
public ?d_007eaa70@@YAXXZ
?d_007eaa70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 80h, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 90h, 00h, 00h
    db 00h, 0E8h, 7Ah, 0FEh, 00h, 00h, 68h, 0B8h, 06h, 00h, 00h, 89h, 86h, 68h, 02h, 00h
    db 00h, 0E8h, 9Ah, 56h, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 0Ah, 56h, 8Bh, 0C8h
    db 0E8h, 0DBh, 0F0h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 85h, 0C0h, 89h, 86h, 6Ch, 02h, 00h
    db 00h, 74h, 05h, 83h, 0C0h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 8Eh, 68h, 02h, 00h, 00h
    db 8Bh, 11h, 50h, 0FFh, 52h, 04h, 8Bh, 86h, 68h, 02h, 00h, 00h, 8Bh, 8Eh, 6Ch, 02h
    db 00h, 00h, 50h, 0E8h, 0B8h, 0EAh, 00h, 00h, 0E8h, 23h, 11h, 01h, 00h, 8Bh, 8Eh, 6Ch
    db 02h, 00h, 00h, 89h, 41h, 24h, 8Bh, 86h, 6Ch, 02h, 00h, 00h, 85h, 0C0h, 74h, 05h
    db 83h, 0C0h, 08h, 0EBh, 02h, 33h, 0C0h, 50h, 8Bh, 0CEh, 0E8h, 51h, 0FAh, 0FFh, 0FFh, 8Bh
    db 56h, 04h, 52h, 0E8h, 18h, 10h, 01h, 00h, 83h, 0C4h, 04h, 89h, 86h, 80h, 02h, 00h
    db 00h, 5Eh, 0C3h
?d_007eaa70@@YAXXZ ENDP

; ghidra: FUN_00beab20  retail @ 0x007EAB20 size 22
public ?d_007eab20@@YAXXZ
?d_007eab20@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 0E8h, 45h, 0FFh, 0FFh, 0FFh, 8Bh, 46h, 04h, 8Bh, 80h
    db 80h, 02h, 00h, 00h, 5Eh, 0C3h
?d_007eab20@@YAXXZ ENDP

; ghidra: FUN_00beab40  retail @ 0x007EAB40 size 163
public ?d_007eab40@@YAXXZ
?d_007eab40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 9Ch, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 85h, 90h, 00h, 00h
    db 00h, 0E8h, 0AAh, 0FDh, 00h, 00h, 68h, 0B8h, 06h, 00h, 00h, 89h, 86h, 84h, 02h, 00h
    db 00h, 0E8h, 0CAh, 55h, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 0Ah, 56h, 8Bh, 0C8h
    db 0E8h, 0Bh, 0F0h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 85h, 0C0h, 89h, 86h, 88h, 02h, 00h
    db 00h, 74h, 05h, 83h, 0C0h, 04h, 0EBh, 02h, 33h, 0C0h, 8Bh, 8Eh, 84h, 02h, 00h, 00h
    db 8Bh, 11h, 50h, 0FFh, 52h, 04h, 8Bh, 86h, 84h, 02h, 00h, 00h, 8Bh, 8Eh, 88h, 02h
    db 00h, 00h, 50h, 0E8h, 0E8h, 0E9h, 00h, 00h, 0E8h, 0B3h, 24h, 01h, 00h, 8Bh, 8Eh, 88h
    db 02h, 00h, 00h, 89h, 41h, 24h, 8Bh, 86h, 88h, 02h, 00h, 00h, 85h, 0C0h, 74h, 05h
    db 83h, 0C0h, 08h, 0EBh, 02h, 33h, 0C0h, 50h, 8Bh, 0CEh, 0E8h, 81h, 0F9h, 0FFh, 0FFh, 8Bh
    db 56h, 04h, 52h, 0E8h, 0A8h, 23h, 01h, 00h, 83h, 0C4h, 04h, 89h, 86h, 9Ch, 02h, 00h
    db 00h, 5Eh, 0C3h
?d_007eab40@@YAXXZ ENDP

; ghidra: FUN_00beabf0  retail @ 0x007EABF0 size 22
public ?d_007eabf0@@YAXXZ
?d_007eabf0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 0E8h, 45h, 0FFh, 0FFh, 0FFh, 8Bh, 46h, 04h, 8Bh, 80h
    db 9Ch, 02h, 00h, 00h, 5Eh, 0C3h
?d_007eabf0@@YAXXZ ENDP

; ghidra: FUN_00beac30  retail @ 0x007EAC30 size 193
public ?d_007eac30@@YAXXZ
?d_007eac30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0B8h, 0DDh, 00h, 00h, 6Ah, 1Fh, 50h, 8Dh, 86h, 0E3h, 01h, 00h
    db 00h, 50h, 0E8h, 73h, 0C4h, 20h, 00h, 8Bh, 86h, 44h, 02h, 00h, 00h, 83h, 0C4h, 0Ch
    db 85h, 0C0h, 75h, 0Fh, 56h, 0E8h, 0B6h, 9Bh, 00h, 00h, 83h, 0C4h, 04h, 89h, 86h, 44h
    db 02h, 00h, 00h, 8Bh, 8Eh, 44h, 02h, 00h, 00h, 8Bh, 11h, 0FFh, 52h, 0Ch, 8Bh, 86h
    db 54h, 02h, 00h, 00h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 6Ah, 00h, 6Ah, 01h
    db 0FFh, 52h, 08h, 8Bh, 46h, 04h, 0C6h, 86h, 0ACh, 02h, 00h, 00h, 00h, 8Ah, 88h, 0A0h
    db 00h, 00h, 00h, 84h, 0C9h, 74h, 2Ah, 8Bh, 8Eh, 24h, 02h, 00h, 00h, 85h, 0C9h, 8Bh
    db 0D1h, 7Fh, 04h, 8Bh, 54h, 24h, 08h, 8Bh, 48h, 0Ch, 8Bh, 01h, 56h, 68h, 10h, 0ACh
    db 0BEh, 00h, 52h, 81h, 0C6h, 0A0h, 00h, 00h, 00h, 56h, 0FFh, 50h, 04h, 5Eh, 0C2h, 04h
    db 00h, 8Bh, 86h, 24h, 02h, 00h, 00h, 85h, 0C0h, 7Fh, 04h, 8Bh, 44h, 24h, 08h, 8Bh
    db 4Eh, 0Ch, 8Bh, 11h, 56h, 68h, 10h, 0ACh, 0BEh, 00h, 50h, 8Dh, 86h, 90h, 00h, 00h
    db 00h, 50h, 8Dh, 46h, 70h, 50h, 83h, 0C6h, 30h, 56h, 0FFh, 52h, 08h, 5Eh, 0C2h, 04h
    db 00h
?d_007eac30@@YAXXZ ENDP

; ghidra: FUN_00bead30  retail @ 0x007EAD30 size 83
public ?d_007ead30@@YAXXZ
?d_007ead30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 38h, 0FDh, 0FFh, 0FFh, 8Ah, 86h, 01h, 01h, 00h, 00h, 84h, 0C0h
    db 8Dh, 96h, 01h, 01h, 00h, 00h, 74h, 23h, 8Bh, 86h, 28h, 02h, 00h, 00h, 85h, 0C0h
    db 7Fh, 05h, 0B8h, 0C1h, 34h, 00h, 00h, 8Bh, 4Eh, 0Ch, 57h, 8Bh, 39h, 56h, 68h, 10h
    db 0ADh, 0BEh, 00h, 50h, 52h, 0FFh, 57h, 04h, 5Fh, 5Eh, 0C3h, 8Bh, 4Eh, 0Ch, 8Bh, 01h
    db 56h, 68h, 10h, 0ADh, 0BEh, 00h, 8Dh, 56h, 70h, 52h, 83h, 0C6h, 30h, 56h, 0FFh, 50h
    db 0Ch, 5Eh, 0C3h
?d_007ead30@@YAXXZ ENDP

; ghidra: FUN_00beadc0  retail @ 0x007EADC0 size 83
public ?d_007eadc0@@YAXXZ
?d_007eadc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 78h, 0FDh, 0FFh, 0FFh, 8Ah, 86h, 42h, 01h, 00h, 00h, 84h, 0C0h
    db 8Dh, 96h, 42h, 01h, 00h, 00h, 74h, 23h, 8Bh, 86h, 2Ch, 02h, 00h, 00h, 85h, 0C0h
    db 7Fh, 05h, 0B8h, 0DCh, 37h, 00h, 00h, 8Bh, 4Eh, 0Ch, 57h, 8Bh, 39h, 56h, 68h, 0A0h
    db 0ADh, 0BEh, 00h, 50h, 52h, 0FFh, 57h, 04h, 5Fh, 5Eh, 0C3h, 8Bh, 4Eh, 0Ch, 8Bh, 01h
    db 56h, 68h, 0A0h, 0ADh, 0BEh, 00h, 8Dh, 56h, 70h, 52h, 83h, 0C6h, 30h, 56h, 0FFh, 50h
    db 10h, 5Eh, 0C3h
?d_007eadc0@@YAXXZ ENDP

; ghidra: FUN_00beae30  retail @ 0x007EAE30 size 780
public ?d_007eae30@@YAXXZ
?d_007eae30@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 57h, 8Dh, 0BEh, 58h, 02h, 00h, 00h, 8Bh, 0CFh, 0C7h, 06h, 0B0h
    db 9Ch, 12h, 01h, 0E8h, 68h, 0D8h, 0FFh, 0FFh, 33h, 0DBh, 0C7h, 07h, 0B0h, 96h, 12h, 01h
    db 89h, 5Fh, 08h, 89h, 5Fh, 0Ch, 89h, 5Fh, 04h, 8Dh, 0BEh, 70h, 02h, 00h, 00h, 8Bh
    db 0CFh, 0E8h, 4Ah, 0D8h, 0FFh, 0FFh, 0C7h, 07h, 0B0h, 96h, 12h, 01h, 89h, 5Fh, 08h, 89h
    db 5Fh, 0Ch, 89h, 5Fh, 04h, 8Dh, 0BEh, 8Ch, 02h, 00h, 00h, 8Bh, 0CFh, 0E8h, 2Eh, 0D8h
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 20h, 0C7h, 07h, 0B0h, 96h, 12h, 01h, 89h, 5Fh, 08h, 89h
    db 5Fh, 0Ch, 89h, 5Fh, 04h, 8Bh, 7Ch, 24h, 10h, 3Bh, 0FBh, 89h, 76h, 04h, 89h, 5Eh
    db 10h, 89h, 5Eh, 14h, 89h, 5Eh, 18h, 89h, 5Eh, 1Ch, 89h, 5Eh, 20h, 89h, 5Eh, 24h
    db 89h, 5Eh, 28h, 89h, 5Eh, 2Ch, 89h, 46h, 08h, 75h, 18h, 0E8h, 50h, 09h, 00h, 00h
    db 8Bh, 10h, 6Ah, 21h, 68h, 2Ch, 93h, 12h, 01h, 68h, 28h, 93h, 12h, 01h, 8Bh, 0C8h
    db 0FFh, 52h, 0Ch, 8Bh, 0C7h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh
    db 0C2h, 83h, 0F8h, 20h, 72h, 18h, 0E8h, 25h, 09h, 00h, 00h, 8Bh, 10h, 6Ah, 22h, 68h
    db 2Ch, 93h, 12h, 01h, 68h, 10h, 93h, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 6Ah, 20h
    db 8Dh, 46h, 30h, 57h, 50h, 0E8h, 0B0h, 0C1h, 20h, 00h, 8Bh, 7Ch, 24h, 20h, 83h, 0C4h
    db 0Ch, 3Bh, 0FBh, 75h, 18h, 0E8h, 0F6h, 08h, 00h, 00h, 8Bh, 10h, 6Ah, 21h, 68h, 2Ch
    db 93h, 12h, 01h, 68h, 28h, 93h, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 0C7h, 8Dh
    db 50h, 01h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh, 0C2h, 83h, 0F8h, 20h, 72h, 18h
    db 0E8h, 0CBh, 08h, 00h, 00h, 8Bh, 10h, 6Ah, 22h, 68h, 2Ch, 93h, 12h, 01h, 68h, 10h
    db 93h, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 6Ah, 20h, 8Dh, 46h, 50h, 57h, 50h, 0E8h
    db 56h, 0C1h, 20h, 00h, 8Bh, 7Ch, 24h, 24h, 83h, 0C4h, 0Ch, 3Bh, 0FBh, 75h, 18h, 0E8h
    db 9Ch, 08h, 00h, 00h, 8Bh, 10h, 6Ah, 21h, 68h, 2Ch, 93h, 12h, 01h, 68h, 28h, 93h
    db 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 0C7h, 8Dh, 50h, 01h, 8Dh, 64h, 24h, 00h
    db 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh, 0C2h, 83h, 0F8h, 10h, 72h, 18h, 0E8h, 6Dh
    db 08h, 00h, 00h, 8Bh, 10h, 6Ah, 22h, 68h, 2Ch, 93h, 12h, 01h, 68h, 10h, 93h, 12h
    db 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 6Ah, 10h, 8Dh, 46h, 70h, 57h, 50h, 0E8h, 0F8h, 0C0h
    db 20h, 00h, 8Bh, 7Ch, 24h, 28h, 83h, 0C4h, 0Ch, 3Bh, 0FBh, 75h, 18h, 0E8h, 3Eh, 08h
    db 00h, 00h, 8Bh, 10h, 6Ah, 21h, 68h, 2Ch, 93h, 12h, 01h, 68h, 28h, 93h, 12h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 0C7h, 8Dh, 50h, 01h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh, 0C2h, 83h, 0F8h, 10h, 72h, 18h, 0E8h, 0Dh
    db 08h, 00h, 00h, 8Bh, 10h, 6Ah, 22h, 68h, 2Ch, 93h, 12h, 01h, 68h, 10h, 93h, 12h
    db 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 6Ah, 10h, 8Dh, 86h, 80h, 00h, 00h, 00h, 57h, 50h
    db 0E8h, 95h, 0C0h, 20h, 00h, 8Bh, 7Ch, 24h, 30h, 83h, 0C4h, 0Ch, 3Bh, 0FBh, 74h, 3Fh
    db 8Bh, 0C7h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh, 0C2h, 83h, 0F8h
    db 20h, 72h, 18h, 0E8h, 0C8h, 07h, 00h, 00h, 8Bh, 10h, 6Ah, 22h, 68h, 2Ch, 93h, 12h
    db 01h, 68h, 10h, 93h, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 6Ah, 20h, 8Dh, 86h, 03h
    db 02h, 00h, 00h, 57h, 50h, 0E8h, 50h, 0C0h, 20h, 00h, 83h, 0C4h, 0Ch, 0EBh, 06h, 88h
    db 9Eh, 03h, 02h, 00h, 00h, 8Bh, 0CEh, 88h, 9Eh, 90h, 00h, 00h, 00h, 88h, 9Eh, 0A0h
    db 00h, 00h, 00h, 88h, 9Eh, 0E1h, 00h, 00h, 00h, 88h, 9Eh, 01h, 01h, 00h, 00h, 88h
    db 9Eh, 42h, 01h, 00h, 00h, 88h, 9Eh, 83h, 01h, 00h, 00h, 88h, 9Eh, 0E3h, 01h, 00h
    db 00h, 89h, 9Eh, 34h, 02h, 00h, 00h, 89h, 9Eh, 48h, 02h, 00h, 00h, 89h, 9Eh, 38h
    db 02h, 00h, 00h, 89h, 9Eh, 3Ch, 02h, 00h, 00h, 89h, 9Eh, 40h, 02h, 00h, 00h, 89h
    db 9Eh, 44h, 02h, 00h, 00h, 89h, 9Eh, 80h, 02h, 00h, 00h, 89h, 9Eh, 9Ch, 02h, 00h
    db 00h, 89h, 9Eh, 0A4h, 02h, 00h, 00h, 89h, 9Eh, 0A8h, 02h, 00h, 00h, 89h, 9Eh, 54h
    db 02h, 00h, 00h, 89h, 9Eh, 6Ch, 02h, 00h, 00h, 89h, 9Eh, 88h, 02h, 00h, 00h, 89h
    db 9Eh, 50h, 02h, 00h, 00h, 89h, 9Eh, 68h, 02h, 00h, 00h, 89h, 9Eh, 84h, 02h, 00h
    db 00h, 89h, 9Eh, 0A0h, 02h, 00h, 00h, 89h, 5Eh, 0Ch, 89h, 9Eh, 24h, 02h, 00h, 00h
    db 89h, 9Eh, 28h, 02h, 00h, 00h, 89h, 9Eh, 2Ch, 02h, 00h, 00h, 89h, 9Eh, 4Ch, 02h
    db 00h, 00h, 0C6h, 86h, 30h, 02h, 00h, 00h, 01h, 88h, 9Eh, 0ACh, 02h, 00h, 00h, 0E8h
    db 8Ch, 0F8h, 0FFh, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 0C2h, 18h, 00h
?d_007eae30@@YAXXZ ENDP

; ghidra: FUN_00beb140  retail @ 0x007EB140 size 35
public ?d_007eb140@@YAXXZ
?d_007eb140@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0A8h, 0F5h, 0FFh, 0FFh, 0F6h, 44h, 24h, 08h, 01h, 74h, 0Eh, 68h
    db 0B0h, 02h, 00h, 00h, 56h, 0E8h, 16h, 50h, 00h, 00h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh
    db 0C2h, 04h, 00h
?d_007eb140@@YAXXZ ENDP

; ghidra: FUN_00beb1c0  retail @ 0x007EB1C0 size 151
public ?d_007eb1c0@@YAXXZ
?d_007eb1c0@@YAXXZ PROC
    db 0E8h, 0FBh, 4Dh, 00h, 00h, 85h, 0C0h, 75h, 11h, 50h, 50h, 0E8h, 50h, 4Fh, 00h, 00h
    db 83h, 0C4h, 08h, 0C6h, 05h, 8Ch, 0A5h, 30h, 01h, 01h, 0E8h, 31h, 06h, 00h, 00h, 85h
    db 0C0h, 75h, 0Ch, 0E8h, 0B8h, 08h, 00h, 00h, 0C6h, 05h, 8Dh, 0A5h, 30h, 01h, 01h, 0A1h
    db 88h, 0A5h, 30h, 01h, 85h, 0C0h, 74h, 18h, 0E8h, 13h, 06h, 00h, 00h, 8Bh, 10h, 6Ah
    db 35h, 68h, 0D4h, 9Ch, 12h, 01h, 68h, 0B8h, 9Ch, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch
    db 68h, 0B0h, 02h, 00h, 00h, 0E8h, 16h, 4Fh, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 74h
    db 2Bh, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h, 14h, 51h, 8Bh, 4Ch, 24h, 14h, 52h, 8Bh
    db 54h, 24h, 14h, 51h, 8Bh, 4Ch, 24h, 14h, 52h, 8Bh, 54h, 24h, 14h, 51h, 52h, 8Bh
    db 0C8h, 0E8h, 0EAh, 0FBh, 0FFh, 0FFh, 0A3h, 88h, 0A5h, 30h, 01h, 0C3h, 0C7h, 05h, 88h, 0A5h
    db 30h, 01h, 00h, 00h, 00h, 00h, 0C3h
?d_007eb1c0@@YAXXZ ENDP

; ghidra: FUN_00beb260  retail @ 0x007EB260 size 6
public ?d_007eb260@@YAXXZ
?d_007eb260@@YAXXZ PROC
    db 0A1h, 88h, 0A5h, 30h, 01h, 0C3h
?d_007eb260@@YAXXZ ENDP

; ghidra: FUN_00beb270  retail @ 0x007EB270 size 70
public ?d_007eb270@@YAXXZ
?d_007eb270@@YAXXZ PROC
    db 8Bh, 0Dh, 88h, 0A5h, 30h, 01h, 85h, 0C9h, 74h, 1Fh, 0E8h, 0A1h, 0EEh, 0FFh, 0FFh, 8Bh
    db 0Dh, 88h, 0A5h, 30h, 01h, 85h, 0C9h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C7h
    db 05h, 88h, 0A5h, 30h, 01h, 00h, 00h, 00h, 00h, 0A0h, 8Dh, 0A5h, 30h, 01h, 84h, 0C0h
    db 74h, 05h, 0E8h, 89h, 05h, 00h, 00h, 0A0h, 8Ch, 0A5h, 30h, 01h, 84h, 0C0h, 74h, 05h
    db 0E9h, 0ABh, 4Dh, 00h, 00h, 0C3h
?d_007eb270@@YAXXZ ENDP

; ghidra: FUN_00beb310  retail @ 0x007EB310 size 100
public ?d_007eb310@@YAXXZ
?d_007eb310@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C7h, 06h, 0B4h, 9Ch, 12h, 01h, 8Bh, 0Dh, 88h, 0A5h, 30h, 01h, 85h
    db 0C9h, 74h, 1Fh, 0E8h, 0F8h, 0EDh, 0FFh, 0FFh, 8Bh, 0Dh, 88h, 0A5h, 30h, 01h, 85h, 0C9h
    db 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 0C7h, 05h, 88h, 0A5h, 30h, 01h, 00h, 00h
    db 00h, 00h, 0A0h, 8Dh, 0A5h, 30h, 01h, 84h, 0C0h, 74h, 05h, 0E8h, 0E0h, 04h, 00h, 00h
    db 0A0h, 8Ch, 0A5h, 30h, 01h, 84h, 0C0h, 74h, 05h, 0E8h, 02h, 4Dh, 00h, 00h, 0F6h, 44h
    db 24h, 08h, 01h, 74h, 09h, 56h, 0E8h, 45h, 6Bh, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h
    db 5Eh, 0C2h, 04h, 00h
?d_007eb310@@YAXXZ ENDP

; ghidra: FUN_00beb380  retail @ 0x007EB380 size 81
public ?d_007eb380@@YAXXZ
?d_007eb380@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 3Dh, 90h, 0A5h, 30h, 01h, 00h, 74h, 05h, 83h, 0C8h, 0FFh, 0EBh
    db 37h, 83h, 7Dh, 08h, 00h, 75h, 07h, 0C7h, 45h, 08h, 9Ch, 0A5h, 30h, 01h, 6Ah, 02h
    db 0E8h, 0DBh, 1Ch, 01h, 00h, 83h, 0C4h, 04h, 0C7h, 05h, 90h, 0A5h, 30h, 01h, 01h, 00h
    db 00h, 00h, 0C7h, 05h, 94h, 0A5h, 30h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 98h, 0A5h
    db 30h, 01h, 00h, 00h, 00h, 00h, 33h, 0C0h, 3Bh, 0ECh, 0E8h, 33h, 0C1h, 20h, 00h, 5Dh
    db 0C3h
?d_007eb380@@YAXXZ ENDP

; ghidra: FUN_00beb3e0  retail @ 0x007EB3E0 size 7
public ?d_007eb3e0@@YAXXZ
?d_007eb3e0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 33h, 0C0h, 5Dh, 0C3h
?d_007eb3e0@@YAXXZ ENDP

; ghidra: FUN_00beb3f0  retail @ 0x007EB3F0 size 7
public ?d_007eb3f0@@YAXXZ
?d_007eb3f0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 33h, 0C0h, 5Dh, 0C3h
?d_007eb3f0@@YAXXZ ENDP

; ghidra: FUN_00beb400  retail @ 0x007EB400 size 7
public ?d_007eb400@@YAXXZ
?d_007eb400@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 33h, 0C0h, 5Dh, 0C3h
?d_007eb400@@YAXXZ ENDP

; ghidra: FUN_00beb410  retail @ 0x007EB410 size 236
public ?d_007eb410@@YAXXZ
?d_007eb410@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 0FCh, 00h, 00h, 00h, 57h, 8Dh, 0BDh, 04h, 0FFh, 0FFh, 0FFh
    db 0B9h, 3Fh, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 81h, 7Dh, 08h, 6Eh, 65h, 70h, 6Fh, 75h, 0Ah, 0A1h, 90h, 0A5h
    db 30h, 01h, 0E9h, 8Ah, 00h, 00h, 00h, 83h, 3Dh, 90h, 0A5h, 30h, 01h, 01h, 74h, 12h
    db 68h, 0D0h, 38h, 2Ch, 01h, 0E8h, 26h, 33h, 01h, 00h, 83h, 0C4h, 04h, 83h, 0C8h, 0FFh
    db 0EBh, 6Fh, 81h, 7Dh, 08h, 6Eh, 6Ch, 6Eh, 6Fh, 75h, 07h, 0A1h, 98h, 0A5h, 30h, 01h
    db 0EBh, 5Fh, 81h, 7Dh, 08h, 6Eh, 6Eh, 6Fh, 63h, 75h, 07h, 0A1h, 94h, 0A5h, 30h, 01h
    db 0EBh, 4Fh, 81h, 7Dh, 08h, 72h, 64h, 64h, 61h, 75h, 07h, 0E8h, 50h, 2Ah, 01h, 00h
    db 0EBh, 3Fh, 81h, 7Dh, 08h, 78h, 63h, 61h, 6Dh, 75h, 33h, 8Dh, 85h, 08h, 0FFh, 0FFh
    db 0FFh, 50h, 0E8h, 79h, 00h, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 72h, 1Ch, 6Ah, 06h
    db 8Dh, 8Dh, 08h, 0FFh, 0FFh, 0FFh, 51h, 8Bh, 55h, 0Ch, 52h, 0E8h, 0F8h, 0C0h, 20h, 00h
    db 83h, 0C4h, 0Ch, 0B8h, 01h, 00h, 00h, 00h, 0EBh, 07h, 33h, 0C0h, 0EBh, 03h, 83h, 0C8h
    db 0FFh, 52h, 8Bh, 0CDh, 50h, 8Dh, 15h, 0FCh, 0B4h, 0BEh, 00h, 0E8h, 45h, 0C0h, 20h, 00h
    db 58h, 5Ah, 8Bh, 4Dh, 0FCh, 0E8h, 0Ah, 0C0h, 20h, 00h, 5Fh, 81h, 0C4h, 0FCh, 00h, 00h
    db 00h, 3Bh, 0ECh, 0E8h, 0Ah, 0C0h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007eb410@@YAXXZ ENDP

; ghidra: FUN_00beb520  retail @ 0x007EB520 size 274
public ?d_007eb520@@YAXXZ
?d_007eb520@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 54h, 57h, 8Dh, 7Dh, 0ACh, 0B9h, 15h, 00h, 00h, 00h, 0B8h
    db 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 89h, 45h, 0FCh, 6Ah, 40h
    db 6Ah, 00h, 8Dh, 45h, 0B8h, 50h, 0E8h, 79h, 0C0h, 20h, 00h, 83h, 0C4h, 0Ch, 0C6h, 45h
    db 0B8h, 32h, 0C6h, 45h, 0E8h, 00h, 0EBh, 09h, 8Ah, 4Dh, 0E8h, 80h, 0C1h, 01h, 88h, 4Dh
    db 0E8h, 0Fh, 0B6h, 55h, 0E8h, 83h, 0FAh, 0Ah, 7Dh, 33h, 8Dh, 45h, 0B8h, 50h, 0E8h, 65h
    db 08h, 03h, 00h, 0Fh, 0B6h, 0C8h, 89h, 4Dh, 0B0h, 83h, 7Dh, 0B0h, 00h, 74h, 1Ah, 83h
    db 7Dh, 0B0h, 23h, 74h, 12h, 0Fh, 0B6h, 55h, 0B9h, 52h, 68h, 50h, 38h, 2Ch, 01h, 0E8h
    db 0ECh, 31h, 01h, 00h, 83h, 0C4h, 08h, 0EBh, 02h, 0EBh, 02h, 0EBh, 0BBh, 0Fh, 0B6h, 45h
    db 0E8h, 83h, 0F8h, 0Ah, 7Dh, 54h, 0Fh, 0B6h, 4Dh, 0E8h, 89h, 4Dh, 0ACh, 6Ah, 40h, 6Ah
    db 00h, 8Dh, 55h, 0B8h, 52h, 0E8h, 0Ah, 0C0h, 20h, 00h, 83h, 0C4h, 0Ch, 0C6h, 45h, 0B8h
    db 33h, 8Ah, 45h, 0ACh, 88h, 45h, 0E8h, 68h, 80h, 38h, 2Ch, 01h, 8Dh, 4Dh, 0C2h, 51h
    db 0E8h, 0E9h, 0BFh, 20h, 00h, 83h, 0C4h, 08h, 8Bh, 55h, 08h, 89h, 55h, 0BCh, 66h, 0C7h
    db 45h, 0C0h, 0F0h, 00h, 8Dh, 45h, 0B8h, 50h, 0E8h, 0EBh, 07h, 03h, 00h, 0Fh, 0B6h, 0C8h
    db 85h, 0C9h, 75h, 04h, 33h, 0C0h, 0EBh, 12h, 0EBh, 0Dh, 68h, 94h, 38h, 2Ch, 01h, 0E8h
    db 7Ch, 31h, 01h, 00h, 83h, 0C4h, 04h, 83h, 0C8h, 0FFh, 52h, 8Bh, 0CDh, 50h, 8Dh, 15h
    db 32h, 0B6h, 0BEh, 00h, 0E8h, 0Ch, 0BFh, 20h, 00h, 58h, 5Ah, 8Bh, 4Dh, 0FCh, 0E8h, 0D1h
    db 0BEh, 20h, 00h, 5Fh, 83h, 0C4h, 54h, 3Bh, 0ECh, 0E8h, 0D4h, 0BEh, 20h, 00h, 8Bh, 0E5h
    db 5Dh, 0C3h
?d_007eb520@@YAXXZ ENDP

; ghidra: FUN_00beb650  retail @ 0x007EB650 size 34
public ?d_007eb650@@YAXXZ
?d_007eb650@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 0E8h, 0D8h, 0D6h, 00h, 00h, 0E8h, 13h, 1Ch, 01h, 00h, 0C7h, 05h, 90h
    db 0A5h, 30h, 01h, 00h, 00h, 00h, 00h, 33h, 0C0h, 3Bh, 0ECh, 0E8h, 92h, 0BEh, 20h, 00h
    db 5Dh, 0C3h
?d_007eb650@@YAXXZ ENDP

; ghidra: FUN_00beb680  retail @ 0x007EB680 size 33
public ?d_007eb680@@YAXXZ
?d_007eb680@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 56h, 8Bh, 0F4h, 8Bh, 45h, 08h, 50h, 0FFh, 15h, 30h, 8Fh, 35h, 01h
    db 3Bh, 0F4h, 0E8h, 6Bh, 0BEh, 20h, 00h, 5Eh, 3Bh, 0ECh, 0E8h, 63h, 0BEh, 20h, 00h, 5Dh
    db 0C3h
?d_007eb680@@YAXXZ ENDP

; ghidra: FUN_00beb6f0  retail @ 0x007EB6F0 size 16
public ?d_007eb6f0@@YAXXZ
?d_007eb6f0@@YAXXZ PROC
    db 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 0FFh, 62h, 0Ch
?d_007eb6f0@@YAXXZ ENDP

; ghidra: FUN_00beb700  retail @ 0x007EB700 size 16
public ?d_007eb700@@YAXXZ
?d_007eb700@@YAXXZ PROC
    db 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 88h, 0A8h, 06h, 00h, 00h, 8Bh, 11h, 0FFh, 62h, 10h
?d_007eb700@@YAXXZ ENDP

; ghidra: FUN_00beb740  retail @ 0x007EB740 size 29
public ?d_007eb740@@YAXXZ
?d_007eb740@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C7h, 06h, 30h, 9Dh, 12h, 01h, 0E8h, 72h, 48h, 00h, 00h, 8Bh, 4Eh
    db 0Ch, 8Bh, 10h, 6Ah, 00h, 51h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 5Eh, 0C3h
?d_007eb740@@YAXXZ ENDP

; ghidra: FUN_00beb7a0  retail @ 0x007EB7A0 size 98
public ?d_007eb7a0@@YAXXZ
?d_007eb7a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 0Ch, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 17h, 0E8h, 0Eh, 48h
    db 00h, 00h, 8Bh, 4Eh, 0Ch, 8Bh, 10h, 57h, 51h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 89h, 7Eh
    db 0Ch, 89h, 7Eh, 10h, 8Bh, 54h, 24h, 0Ch, 83h, 0E2h, 0F8h, 81h, 0C2h, 80h, 00h, 00h
    db 00h, 89h, 56h, 10h, 0E8h, 0E7h, 47h, 00h, 00h, 8Bh, 4Eh, 10h, 8Bh, 10h, 57h, 51h
    db 8Bh, 0C8h, 0FFh, 52h, 08h, 8Bh, 4Eh, 10h, 8Bh, 0D1h, 8Bh, 0F8h, 0C1h, 0E9h, 02h, 89h
    db 7Eh, 0Ch, 33h, 0C0h, 0F3h, 0ABh, 8Bh, 0CAh, 83h, 0E1h, 03h, 0F3h, 0AAh, 5Fh, 5Eh, 0C2h
    db 04h, 00h
?d_007eb7a0@@YAXXZ ENDP

; ghidra: FUN_00beb810  retail @ 0x007EB810 size 6
public ?d_007eb810@@YAXXZ
?d_007eb810@@YAXXZ PROC
    db 0A1h, 0A0h, 0A5h, 30h, 01h, 0C3h
?d_007eb810@@YAXXZ ENDP

; ghidra: FUN_00beb830  retail @ 0x007EB830 size 28
public ?d_007eb830@@YAXXZ
?d_007eb830@@YAXXZ PROC
    db 8Bh, 0Dh, 0A0h, 0A5h, 30h, 01h, 85h, 0C9h, 74h, 07h, 8Bh, 01h, 6Ah, 01h, 0FFh, 50h
    db 14h, 0C7h, 05h, 0A0h, 0A5h, 30h, 01h, 00h, 00h, 00h, 00h, 0C3h
?d_007eb830@@YAXXZ ENDP

; ghidra: FUN_00beb870  retail @ 0x007EB870 size 51
public ?d_007eb870@@YAXXZ
?d_007eb870@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0C7h, 06h, 30h, 9Dh, 12h, 01h, 0E8h, 42h, 47h, 00h, 00h, 8Bh, 4Eh
    db 0Ch, 8Bh, 10h, 6Ah, 00h, 51h, 8Bh, 0C8h, 0FFh, 52h, 0Ch, 0F6h, 44h, 24h, 08h, 01h
    db 74h, 0Bh, 6Ah, 14h, 56h, 0E8h, 0D6h, 48h, 00h, 00h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh
    db 0C2h, 04h, 00h
?d_007eb870@@YAXXZ ENDP

; ghidra: FUN_00bebaa0  retail @ 0x007EBAA0 size 63
public ?d_007ebaa0@@YAXXZ
?d_007ebaa0@@YAXXZ PROC
    db 0A1h, 0A0h, 0A5h, 30h, 01h, 56h, 33h, 0F6h, 3Bh, 0C6h, 75h, 31h, 6Ah, 14h, 0E8h, 7Dh
    db 46h, 00h, 00h, 83h, 0C4h, 04h, 3Bh, 0C6h, 74h, 1Dh, 89h, 70h, 08h, 89h, 70h, 0Ch
    db 89h, 70h, 10h, 0C7h, 00h, 30h, 9Dh, 12h, 01h, 0C7h, 40h, 04h, 20h, 0B8h, 0BEh, 00h
    db 0A3h, 0A0h, 0A5h, 30h, 01h, 5Eh, 0C3h, 89h, 35h, 0A0h, 0A5h, 30h, 01h, 5Eh, 0C3h
?d_007ebaa0@@YAXXZ ENDP

; ghidra: FUN_00bebae0  retail @ 0x007EBAE0 size 35
public ?d_007ebae0@@YAXXZ
?d_007ebae0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 51h, 0C7h, 45h, 0FCh, 0CCh, 0CCh, 0CCh, 0CCh, 0A0h, 1Ch, 39h, 2Ch, 01h
    db 88h, 45h, 0FFh, 8Ah, 4Dh, 08h, 88h, 0Dh, 1Ch, 39h, 2Ch, 01h, 8Ah, 45h, 0FFh, 8Bh
    db 0E5h, 5Dh, 0C3h
?d_007ebae0@@YAXXZ ENDP

; ghidra: FUN_00bebb10  retail @ 0x007EBB10 size 397
public ?d_007ebb10@@YAXXZ
?d_007ebb10@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 10h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0F0h, 89h, 45h
    db 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh, 8Bh, 45h, 08h, 89h, 45h, 0F4h, 8Bh, 4Dh, 0F4h
    db 89h, 4Dh, 0F8h, 8Bh, 55h, 0F8h, 89h, 55h, 0FCh, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 08h, 85h
    db 0C9h, 0Fh, 84h, 83h, 00h, 00h, 00h, 8Bh, 55h, 0FCh, 0Fh, 0B6h, 02h, 83h, 0F8h, 20h
    db 7Dh, 57h, 8Bh, 4Dh, 0F8h, 8Ah, 55h, 0Ch, 88h, 11h, 8Bh, 45h, 0F8h, 83h, 0C0h, 01h
    db 89h, 45h, 0F8h, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 11h, 85h, 0D2h, 7Eh, 16h, 8Bh, 45h, 0FCh
    db 0Fh, 0B6h, 08h, 83h, 0F9h, 20h, 7Dh, 0Bh, 8Bh, 55h, 0FCh, 83h, 0C2h, 01h, 89h, 55h
    db 0FCh, 0EBh, 0E0h, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 08h, 83h, 0F9h, 3Dh, 74h, 0Bh, 8Bh, 55h
    db 0FCh, 0Fh, 0B6h, 02h, 83h, 0F8h, 3Ah, 75h, 0Eh, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 51h, 01h
    db 83h, 0FAh, 20h, 7Dh, 02h, 0EBh, 23h, 0EBh, 1Ch, 8Bh, 45h, 0F8h, 8Bh, 4Dh, 0FCh, 8Ah
    db 11h, 88h, 10h, 8Bh, 45h, 0F8h, 83h, 0C0h, 01h, 89h, 45h, 0F8h, 8Bh, 4Dh, 0FCh, 83h
    db 0C1h, 01h, 89h, 4Dh, 0FCh, 0E9h, 6Fh, 0FFh, 0FFh, 0FFh, 8Bh, 55h, 0F8h, 3Bh, 55h, 0F4h
    db 74h, 3Bh, 8Bh, 45h, 0F8h, 0Fh, 0B6h, 48h, 0FFh, 0Fh, 0B6h, 55h, 0Ch, 3Bh, 0CAh, 75h
    db 2Ch, 0Fh, 0B6h, 45h, 0Ch, 83h, 0F8h, 0Ah, 74h, 13h, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 11h
    db 85h, 0D2h, 75h, 09h, 0C7h, 45h, 0F0h, 00h, 00h, 00h, 00h, 0EBh, 07h, 0C7h, 45h, 0F0h
    db 0Ah, 00h, 00h, 00h, 8Bh, 45h, 0F8h, 8Ah, 4Dh, 0F0h, 88h, 48h, 0FFh, 8Bh, 55h, 0FCh
    db 0Fh, 0B6h, 02h, 85h, 0C0h, 74h, 7Ch, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 11h, 83h, 0FAh, 20h
    db 7Dh, 50h, 8Bh, 45h, 0F8h, 0C6h, 00h, 0Ah, 8Bh, 4Dh, 0F8h, 83h, 0C1h, 01h, 89h, 4Dh
    db 0F8h, 8Bh, 55h, 0FCh, 8Ah, 02h, 88h, 45h, 0Ch, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h
    db 4Dh, 0FCh, 8Bh, 55h, 0FCh, 0Fh, 0B6h, 02h, 85h, 0C0h, 7Eh, 24h, 8Bh, 4Dh, 0FCh, 0Fh
    db 0B6h, 11h, 83h, 0FAh, 20h, 7Dh, 19h, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 08h, 0Fh, 0B6h, 55h
    db 0Ch, 3Bh, 0CAh, 74h, 0Bh, 8Bh, 45h, 0FCh, 83h, 0C0h, 01h, 89h, 45h, 0FCh, 0EBh, 0D2h
    db 0EBh, 1Ch, 8Bh, 4Dh, 0F8h, 8Bh, 55h, 0FCh, 8Ah, 02h, 88h, 01h, 8Bh, 4Dh, 0F8h, 83h
    db 0C1h, 01h, 89h, 4Dh, 0F8h, 8Bh, 55h, 0FCh, 83h, 0C2h, 01h, 89h, 55h, 0FCh, 0E9h, 7Ah
    db 0FFh, 0FFh, 0FFh, 8Bh, 45h, 0F8h, 0C6h, 00h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ebb10@@YAXXZ ENDP

; ghidra: FUN_00bebca0  retail @ 0x007EBCA0 size 374
public ?d_007ebca0@@YAXXZ
?d_007ebca0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 1Ch, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0E4h, 89h, 45h
    db 0E8h, 89h, 45h, 0ECh, 89h, 45h, 0F0h, 89h, 45h, 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh
    db 8Bh, 45h, 0Ch, 89h, 45h, 0ECh, 8Bh, 4Dh, 08h, 89h, 4Dh, 0E8h, 83h, 7Dh, 0E8h, 00h
    db 74h, 0Ah, 8Bh, 55h, 0E8h, 0Fh, 0B6h, 02h, 85h, 0C0h, 75h, 07h, 33h, 0C0h, 0E9h, 2Fh
    db 01h, 00h, 00h, 83h, 7Dh, 0ECh, 00h, 74h, 0Ah, 8Bh, 4Dh, 0ECh, 0Fh, 0B6h, 11h, 85h
    db 0D2h, 75h, 07h, 33h, 0C0h, 0E9h, 18h, 01h, 00h, 00h, 8Bh, 45h, 0ECh, 89h, 45h, 0F0h
    db 0EBh, 09h, 8Bh, 4Dh, 0F0h, 83h, 0C1h, 01h, 89h, 4Dh, 0F0h, 8Bh, 55h, 0F0h, 0Fh, 0B6h
    db 02h, 85h, 0C0h, 74h, 02h, 0EBh, 0EBh, 8Bh, 4Dh, 0F0h, 83h, 0E9h, 01h, 89h, 4Dh, 0F0h
    db 8Bh, 55h, 0E8h, 89h, 55h, 0FCh, 0EBh, 09h, 8Bh, 45h, 0FCh, 83h, 0C0h, 01h, 89h, 45h
    db 0FCh, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 11h, 85h, 0D2h, 0Fh, 84h, 0D1h, 00h, 00h, 00h, 8Bh
    db 45h, 0FCh, 0Fh, 0B6h, 08h, 83h, 0F9h, 3Dh, 74h, 0Dh, 8Bh, 55h, 0FCh, 0Fh, 0B6h, 02h
    db 83h, 0F8h, 3Ah, 74h, 02h, 0EBh, 0D1h, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 51h, 01h, 83h, 0FAh
    db 20h, 7Dh, 11h, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 48h, 0FFh, 83h, 0F9h, 20h, 7Fh, 05h, 0E9h
    db 9Ch, 00h, 00h, 00h, 8Bh, 55h, 0FCh, 83h, 0EAh, 01h, 89h, 55h, 0F8h, 8Bh, 45h, 0F0h
    db 89h, 45h, 0F4h, 0EBh, 12h, 8Bh, 4Dh, 0F8h, 83h, 0E9h, 01h, 89h, 4Dh, 0F8h, 8Bh, 55h
    db 0F4h, 83h, 0EAh, 01h, 89h, 55h, 0F4h, 8Bh, 45h, 0F8h, 3Bh, 45h, 0E8h, 72h, 6Ch, 8Bh
    db 4Dh, 0F4h, 3Bh, 4Dh, 0ECh, 72h, 64h, 8Bh, 55h, 0F8h, 0Fh, 0B6h, 02h, 0Fh, 0B6h, 88h
    db 10h, 0A2h, 12h, 01h, 8Bh, 55h, 0F4h, 0Fh, 0B6h, 02h, 0Fh, 0B6h, 90h, 10h, 0A2h, 12h
    db 01h, 3Bh, 0CAh, 75h, 46h, 8Bh, 45h, 0F4h, 3Bh, 45h, 0ECh, 75h, 39h, 8Bh, 4Dh, 0F8h
    db 3Bh, 4Dh, 0E8h, 74h, 0Ch, 8Bh, 55h, 0F8h, 0Fh, 0B6h, 42h, 0FFh, 83h, 0F8h, 20h, 7Fh
    db 25h, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 51h, 01h, 83h, 0FAh, 20h, 75h, 0Bh, 8Bh, 45h, 0FCh
    db 83h, 0C0h, 02h, 89h, 45h, 0E4h, 0EBh, 09h, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h, 4Dh
    db 0E4h, 8Bh, 45h, 0E4h, 0EBh, 0Ch, 0E9h, 7Ah, 0FFh, 0FFh, 0FFh, 0E9h, 18h, 0FFh, 0FFh, 0FFh
    db 33h, 0C0h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ebca0@@YAXXZ ENDP

; ghidra: FUN_00bebe20  retail @ 0x007EBE20 size 218
public ?d_007ebe20@@YAXXZ
?d_007ebe20@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 10h, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0F0h, 0FEh, 0FFh, 0FFh
    db 0B9h, 44h, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 0C7h, 85h, 0F0h, 0FEh, 0FFh, 0FFh, 00h, 00h, 00h, 00h, 83h, 7Dh
    db 0Ch, 00h, 75h, 18h, 8Bh, 45h, 10h, 50h, 8Bh, 4Dh, 08h, 51h, 0E8h, 3Fh, 0FEh, 0FFh
    db 0FFh, 83h, 0C4h, 08h, 89h, 85h, 0F0h, 0FEh, 0FFh, 0FFh, 0EBh, 5Dh, 83h, 7Dh, 10h, 00h
    db 75h, 18h, 8Bh, 55h, 0Ch, 52h, 8Bh, 45h, 08h, 50h, 0E8h, 21h, 0FEh, 0FFh, 0FFh, 83h
    db 0C4h, 08h, 89h, 85h, 0F0h, 0FEh, 0FFh, 0FFh, 0EBh, 3Fh, 8Bh, 4Dh, 0Ch, 51h, 8Dh, 95h
    db 0F8h, 0FEh, 0FFh, 0FFh, 52h, 0E8h, 24h, 0B7h, 20h, 00h, 83h, 0C4h, 08h, 8Bh, 45h, 10h
    db 50h, 8Dh, 8Dh, 0F8h, 0FEh, 0FFh, 0FFh, 51h, 0E8h, 1Dh, 0B7h, 20h, 00h, 83h, 0C4h, 08h
    db 8Dh, 95h, 0F8h, 0FEh, 0FFh, 0FFh, 52h, 8Bh, 45h, 08h, 50h, 0E8h, 0E0h, 0FDh, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 89h, 85h, 0F0h, 0FEh, 0FFh, 0FFh, 8Bh, 85h, 0F0h, 0FEh, 0FFh, 0FFh, 52h
    db 8Bh, 0CDh, 50h, 8Dh, 15h, 0FAh, 0BEh, 0BEh, 00h, 0E8h, 47h, 0B6h, 20h, 00h, 58h, 5Ah
    db 8Bh, 4Dh, 0FCh, 0E8h, 0Ch, 0B6h, 20h, 00h, 5Fh, 81h, 0C4h, 10h, 01h, 00h, 00h, 3Bh
    db 0ECh, 0E8h, 0Ch, 0B6h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ebe20@@YAXXZ ENDP

; ghidra: FUN_00bebf20  retail @ 0x007EBF20 size 126
public ?d_007ebf20@@YAXXZ
?d_007ebf20@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 0Ch, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0F4h, 0FEh, 0FFh, 0FFh
    db 0B9h, 43h, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 8Bh, 45h, 10h, 50h, 8Bh, 4Dh, 0Ch, 51h, 68h, 20h, 39h, 2Ch
    db 01h, 8Dh, 95h, 0F8h, 0FEh, 0FFh, 0FFh, 52h, 0E8h, 85h, 0AEh, 20h, 00h, 83h, 0C4h, 10h
    db 8Dh, 85h, 0F8h, 0FEh, 0FFh, 0FFh, 50h, 8Bh, 4Dh, 08h, 51h, 0E8h, 30h, 0FDh, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 52h, 8Bh, 0CDh, 50h, 8Dh, 15h, 9Eh, 0BFh, 0BEh, 00h, 0E8h, 0A3h, 0B5h
    db 20h, 00h, 58h, 5Ah, 8Bh, 4Dh, 0FCh, 0E8h, 68h, 0B5h, 20h, 00h, 5Fh, 81h, 0C4h, 0Ch
    db 01h, 00h, 00h, 3Bh, 0ECh, 0E8h, 68h, 0B5h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ebf20@@YAXXZ ENDP

; ghidra: FUN_00bebfc0  retail @ 0x007EBFC0 size 103
public ?d_007ebfc0@@YAXXZ
?d_007ebfc0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 51h, 0C7h, 45h, 0FCh, 0CCh, 0CCh, 0CCh, 0CCh, 68h, 28h, 39h, 2Ch, 01h
    db 8Bh, 45h, 08h, 50h, 0E8h, 0C7h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 45h, 0FCh, 83h
    db 7Dh, 0FCh, 00h, 74h, 31h, 8Bh, 4Dh, 0FCh, 0Fh, 0B6h, 11h, 85h, 0D2h, 74h, 16h, 8Bh
    db 45h, 0FCh, 0Fh, 0B6h, 08h, 83h, 0F9h, 20h, 7Fh, 0Bh, 8Bh, 55h, 0FCh, 83h, 0C2h, 01h
    db 89h, 55h, 0FCh, 0EBh, 0E0h, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 08h, 85h, 0C9h, 75h, 07h, 0C7h
    db 45h, 0FCh, 00h, 00h, 00h, 00h, 8Bh, 45h, 0FCh, 83h, 0C4h, 04h, 3Bh, 0ECh, 0E8h, 0DFh
    db 0B4h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ebfc0@@YAXXZ ENDP

; ghidra: FUN_00bec030  retail @ 0x007EC030 size 256
public ?d_007ec030@@YAXXZ
?d_007ec030@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 10h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0F0h, 89h, 45h
    db 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh, 8Bh, 45h, 08h, 89h, 45h, 0F0h, 8Bh, 4Dh, 0Ch
    db 51h, 8Bh, 55h, 0F0h, 52h, 0E8h, 46h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 45h, 0FCh
    db 83h, 7Dh, 0FCh, 00h, 75h, 08h, 83h, 0C8h, 0FFh, 0E9h, 0B4h, 00h, 00h, 00h, 8Bh, 45h
    db 0FCh, 89h, 45h, 0F8h, 0EBh, 09h, 8Bh, 4Dh, 0F8h, 83h, 0E9h, 01h, 89h, 4Dh, 0F8h, 8Bh
    db 55h, 0F8h, 3Bh, 55h, 0F0h, 74h, 0Eh, 8Bh, 45h, 0F8h, 0Fh, 0B6h, 48h, 0FFh, 83h, 0F9h
    db 20h, 7Eh, 02h, 0EBh, 0E1h, 8Bh, 55h, 0FCh, 89h, 55h, 0F4h, 0EBh, 09h, 8Bh, 45h, 0F4h
    db 83h, 0C0h, 01h, 89h, 45h, 0F4h, 8Bh, 4Dh, 0F4h, 0Fh, 0B6h, 11h, 83h, 0FAh, 20h, 7Ch
    db 02h, 0EBh, 0EAh, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 08h, 85h, 0C9h, 7Eh, 16h, 8Bh, 55h, 0F4h
    db 0Fh, 0B6h, 02h, 83h, 0F8h, 20h, 7Dh, 0Bh, 8Bh, 4Dh, 0F4h, 83h, 0C1h, 01h, 89h, 4Dh
    db 0F4h, 0EBh, 0E0h, 8Bh, 55h, 0F4h, 0Fh, 0B6h, 02h, 85h, 0C0h, 74h, 1Eh, 8Bh, 4Dh, 0F8h
    db 8Bh, 55h, 0F4h, 8Ah, 02h, 88h, 01h, 8Bh, 4Dh, 0F8h, 83h, 0C1h, 01h, 89h, 4Dh, 0F8h
    db 8Bh, 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 0EBh, 0D8h, 8Bh, 45h, 0F8h, 3Bh, 45h
    db 0F0h, 74h, 17h, 8Bh, 4Dh, 0F8h, 0Fh, 0B6h, 51h, 0FFh, 83h, 0FAh, 20h, 7Fh, 0Bh, 8Bh
    db 45h, 0F8h, 83h, 0E8h, 01h, 89h, 45h, 0F8h, 0EBh, 0E1h, 8Bh, 4Dh, 0F8h, 0C6h, 01h, 00h
    db 33h, 0C0h, 83h, 0C4h, 10h, 3Bh, 0ECh, 0E8h, 0D6h, 0B3h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec030@@YAXXZ ENDP

; ghidra: FUN_00bec130  retail @ 0x007EC130 size 336
public ?d_007ec130@@YAXXZ
?d_007ec130@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 14h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0ECh, 89h, 45h
    db 0F0h, 89h, 45h, 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh, 8Bh, 45h, 08h, 89h, 45h, 0ECh
    db 8Bh, 4Dh, 10h, 51h, 8Bh, 55h, 0ECh, 52h, 0E8h, 43h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 08h
    db 89h, 45h, 0F8h, 83h, 7Dh, 0F8h, 00h, 75h, 08h, 83h, 0C8h, 0FFh, 0E9h, 01h, 01h, 00h
    db 00h, 8Bh, 45h, 0F8h, 0Fh, 0B6h, 48h, 0FFh, 83h, 0F9h, 20h, 75h, 09h, 8Bh, 55h, 0F8h
    db 83h, 0EAh, 01h, 89h, 55h, 0F8h, 8Bh, 45h, 0F8h, 83h, 0E8h, 01h, 89h, 45h, 0F8h, 8Bh
    db 4Dh, 0F8h, 89h, 4Dh, 0F4h, 0EBh, 09h, 8Bh, 55h, 0F4h, 83h, 0EAh, 01h, 89h, 55h, 0F4h
    db 8Bh, 45h, 0F4h, 3Bh, 45h, 0ECh, 74h, 0Eh, 8Bh, 4Dh, 0F4h, 0Fh, 0B6h, 51h, 0FFh, 83h
    db 0FAh, 20h, 7Eh, 02h, 0EBh, 0E1h, 8Bh, 45h, 14h, 50h, 0E8h, 11h, 0B4h, 20h, 00h, 83h
    db 0C4h, 04h, 8Bh, 4Dh, 0F8h, 2Bh, 4Dh, 0F4h, 2Bh, 0C1h, 89h, 45h, 0FCh, 79h, 1Fh, 8Bh
    db 55h, 0F8h, 0Fh, 0B6h, 02h, 85h, 0C0h, 74h, 0Fh, 8Bh, 4Dh, 0F8h, 03h, 4Dh, 0FCh, 8Bh
    db 55h, 0F8h, 8Ah, 02h, 88h, 01h, 0EBh, 0E7h, 8Bh, 4Dh, 0F8h, 0C6h, 01h, 00h, 83h, 7Dh
    db 0FCh, 00h, 7Eh, 54h, 8Bh, 55h, 0F8h, 89h, 55h, 0F0h, 0EBh, 09h, 8Bh, 45h, 0F0h, 83h
    db 0C0h, 01h, 89h, 45h, 0F0h, 8Bh, 4Dh, 0F0h, 0Fh, 0B6h, 11h, 85h, 0D2h, 74h, 02h, 0EBh
    db 0EBh, 8Bh, 45h, 0F0h, 2Bh, 45h, 0ECh, 8Bh, 4Dh, 0Ch, 2Bh, 4Dh, 0FCh, 3Bh, 0C1h, 7Dh
    db 05h, 83h, 0C8h, 0FFh, 0EBh, 4Ch, 0EBh, 09h, 8Bh, 55h, 0F0h, 83h, 0EAh, 01h, 89h, 55h
    db 0F0h, 8Bh, 45h, 0F0h, 3Bh, 45h, 0F8h, 74h, 0Fh, 8Bh, 4Dh, 0F0h, 03h, 4Dh, 0FCh, 8Bh
    db 55h, 0F0h, 8Ah, 02h, 88h, 01h, 0EBh, 0E0h, 8Bh, 4Dh, 14h, 0Fh, 0BEh, 11h, 85h, 0D2h
    db 74h, 1Eh, 8Bh, 45h, 0F4h, 8Bh, 4Dh, 14h, 8Ah, 11h, 88h, 10h, 8Bh, 45h, 0F4h, 83h
    db 0C0h, 01h, 89h, 45h, 0F4h, 8Bh, 4Dh, 14h, 83h, 0C1h, 01h, 89h, 4Dh, 14h, 0EBh, 0D8h
    db 33h, 0C0h, 83h, 0C4h, 14h, 3Bh, 0ECh, 0E8h, 86h, 0B2h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec130@@YAXXZ ENDP

; ghidra: FUN_00bec280  retail @ 0x007EC280 size 96
public ?d_007ec280@@YAXXZ
?d_007ec280@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 51h, 0C7h, 45h, 0FCh, 0CCh, 0CCh, 0CCh, 0CCh, 8Bh, 45h, 0Ch, 89h, 45h
    db 0FCh, 0EBh, 09h, 8Bh, 4Dh, 0FCh, 83h, 0E9h, 01h, 89h, 4Dh, 0FCh, 83h, 7Dh, 0FCh, 01h
    db 7Eh, 28h, 8Bh, 55h, 10h, 0Fh, 0BEh, 02h, 85h, 0C0h, 74h, 1Eh, 8Bh, 4Dh, 08h, 8Bh
    db 55h, 10h, 8Ah, 02h, 88h, 01h, 8Bh, 4Dh, 08h, 83h, 0C1h, 01h, 89h, 4Dh, 08h, 8Bh
    db 55h, 10h, 83h, 0C2h, 01h, 89h, 55h, 10h, 0EBh, 0C9h, 83h, 7Dh, 0FCh, 00h, 7Eh, 06h
    db 8Bh, 45h, 08h, 0C6h, 00h, 00h, 8Bh, 45h, 0Ch, 2Bh, 45h, 0FCh, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec280@@YAXXZ ENDP

; ghidra: FUN_00bec2e0  retail @ 0x007EC2E0 size 259
public ?d_007ec2e0@@YAXXZ
?d_007ec2e0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 10h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0F0h, 89h, 45h
    db 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh, 0C7h, 45h, 0FCh, 00h, 00h, 00h, 00h, 8Bh, 45h
    db 08h, 89h, 45h, 0F0h, 83h, 7Dh, 10h, 00h, 7Eh, 06h, 8Bh, 4Dh, 0Ch, 0C6h, 01h, 00h
    db 83h, 7Dh, 0F0h, 00h, 74h, 0Ah, 8Bh, 55h, 0F0h, 0Fh, 0B6h, 02h, 85h, 0C0h, 75h, 07h
    db 33h, 0C0h, 0E9h, 0B8h, 00h, 00h, 00h, 8Bh, 4Dh, 0F0h, 89h, 4Dh, 0F8h, 0EBh, 09h, 8Bh
    db 55h, 0F8h, 83h, 0C2h, 01h, 89h, 55h, 0F8h, 8Bh, 45h, 0F8h, 0Fh, 0B6h, 08h, 85h, 0C9h
    db 0Fh, 84h, 96h, 00h, 00h, 00h, 8Bh, 55h, 0F8h, 0Fh, 0B6h, 02h, 83h, 0F8h, 3Dh, 74h
    db 0Dh, 8Bh, 4Dh, 0F8h, 0Fh, 0B6h, 11h, 83h, 0FAh, 3Ah, 74h, 02h, 0EBh, 0D1h, 8Bh, 45h
    db 0F8h, 0Fh, 0B6h, 48h, 01h, 83h, 0F9h, 20h, 7Dh, 0Eh, 8Bh, 55h, 0F8h, 0Fh, 0B6h, 42h
    db 0FFh, 83h, 0F8h, 20h, 7Fh, 02h, 0EBh, 64h, 8Bh, 4Dh, 0F8h, 89h, 4Dh, 0F4h, 0EBh, 09h
    db 8Bh, 55h, 0F4h, 83h, 0EAh, 01h, 89h, 55h, 0F4h, 8Bh, 45h, 0F4h, 3Bh, 45h, 0F0h, 74h
    db 0Eh, 8Bh, 4Dh, 0F4h, 0Fh, 0B6h, 51h, 0FFh, 83h, 0FAh, 20h, 7Eh, 02h, 0EBh, 0E1h, 8Bh
    db 45h, 0F4h, 3Bh, 45h, 0F8h, 74h, 2Ch, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 3Bh, 4Dh, 10h
    db 7Dh, 21h, 8Bh, 55h, 0Ch, 03h, 55h, 0FCh, 8Bh, 45h, 0F4h, 8Ah, 08h, 88h, 0Ah, 8Bh
    db 55h, 0FCh, 83h, 0C2h, 01h, 89h, 55h, 0FCh, 8Bh, 45h, 0F4h, 83h, 0C0h, 01h, 89h, 45h
    db 0F4h, 0EBh, 0CCh, 8Bh, 4Dh, 0Ch, 03h, 4Dh, 0FCh, 0C6h, 01h, 00h, 8Bh, 45h, 0FCh, 8Bh
    db 0E5h, 5Dh, 0C3h
?d_007ec2e0@@YAXXZ ENDP

; ghidra: FUN_00bec3f0  retail @ 0x007EC3F0 size 220
public ?d_007ec3f0@@YAXXZ
?d_007ec3f0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 08h, 0C7h, 45h, 0F8h, 0CCh, 0CCh, 0CCh, 0CCh, 0C7h, 45h, 0FCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 8Bh, 45h, 08h, 89h, 45h, 0FCh, 0EBh, 09h, 8Bh, 4Dh, 0FCh, 83h
    db 0C1h, 01h, 89h, 4Dh, 0FCh, 8Bh, 55h, 0FCh, 0Fh, 0B6h, 02h, 85h, 0C0h, 74h, 26h, 8Bh
    db 4Dh, 0FCh, 0Fh, 0B6h, 11h, 83h, 0FAh, 3Dh, 74h, 0Bh, 8Bh, 45h, 0FCh, 0Fh, 0B6h, 08h
    db 83h, 0F9h, 3Ah, 75h, 0Eh, 8Bh, 55h, 0FCh, 0Fh, 0B6h, 42h, 01h, 83h, 0F8h, 20h, 7Dh
    db 02h, 0EBh, 02h, 0EBh, 0C7h, 8Bh, 4Dh, 0FCh, 0C6h, 01h, 00h, 83h, 7Dh, 10h, 00h, 75h
    db 04h, 33h, 0C0h, 0EBh, 73h, 8Bh, 55h, 0Ch, 8Bh, 45h, 08h, 8Dh, 4Ch, 10h, 0FFh, 89h
    db 4Dh, 0F8h, 8Bh, 55h, 0F8h, 2Bh, 55h, 0FCh, 83h, 0FAh, 05h, 7Dh, 05h, 83h, 0C8h, 0FFh
    db 0EBh, 56h, 8Bh, 45h, 0FCh, 0C6h, 00h, 3Dh, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h, 4Dh
    db 0FCh, 8Bh, 55h, 0FCh, 0C6h, 02h, 0Ah, 8Bh, 45h, 0FCh, 83h, 0C0h, 01h, 89h, 45h, 0FCh
    db 8Bh, 4Dh, 10h, 0Fh, 0BEh, 11h, 85h, 0D2h, 74h, 26h, 8Bh, 45h, 0FCh, 3Bh, 45h, 0F8h
    db 74h, 1Eh, 8Bh, 4Dh, 0FCh, 8Bh, 55h, 10h, 8Ah, 02h, 88h, 01h, 8Bh, 4Dh, 0FCh, 83h
    db 0C1h, 01h, 89h, 4Dh, 0FCh, 8Bh, 55h, 10h, 83h, 0C2h, 01h, 89h, 55h, 10h, 0EBh, 0D0h
    db 8Bh, 45h, 0FCh, 0C6h, 00h, 00h, 33h, 0C0h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec3f0@@YAXXZ ENDP

; ghidra: FUN_00bec4d0  retail @ 0x007EC4D0 size 238
public ?d_007ec4d0@@YAXXZ
?d_007ec4d0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 10h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0F0h, 89h, 45h
    db 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh, 0C7h, 45h, 0F8h, 0FFh, 0FFh, 0FFh, 0FFh, 0C7h, 45h
    db 0F4h, 2Ch, 39h, 2Ch, 01h, 8Bh, 45h, 08h, 89h, 45h, 0F0h, 0C7h, 45h, 0FCh, 00h, 00h
    db 00h, 00h, 0EBh, 09h, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h, 4Dh, 0FCh, 8Bh, 55h, 0F0h
    db 03h, 55h, 0FCh, 0Fh, 0B6h, 02h, 85h, 0C0h, 74h, 02h, 0EBh, 0E8h, 83h, 7Dh, 0FCh, 00h
    db 7Eh, 4Fh, 8Bh, 4Dh, 0F0h, 03h, 4Dh, 0FCh, 0Fh, 0B6h, 51h, 0FFh, 83h, 0FAh, 20h, 7Ch
    db 40h, 8Bh, 45h, 0F0h, 03h, 45h, 0FCh, 0Fh, 0B6h, 48h, 0FFh, 0Fh, 0BEh, 15h, 1Ch, 39h
    db 2Ch, 01h, 3Bh, 0CAh, 74h, 2Bh, 8Bh, 45h, 0Ch, 83h, 0E8h, 01h, 39h, 45h, 0FCh, 7Dh
    db 20h, 8Bh, 4Dh, 0F0h, 03h, 4Dh, 0FCh, 8Ah, 15h, 1Ch, 39h, 2Ch, 01h, 88h, 11h, 8Bh
    db 45h, 0FCh, 83h, 0C0h, 01h, 89h, 45h, 0FCh, 8Bh, 4Dh, 0F0h, 03h, 4Dh, 0FCh, 0C6h, 01h
    db 00h, 8Bh, 55h, 0FCh, 83h, 0C2h, 04h, 3Bh, 55h, 0Ch, 7Dh, 3Bh, 8Bh, 45h, 0F4h, 0Fh
    db 0BEh, 08h, 85h, 0C9h, 74h, 21h, 8Bh, 55h, 0F0h, 03h, 55h, 0FCh, 8Bh, 45h, 0F4h, 8Ah
    db 08h, 88h, 0Ah, 8Bh, 55h, 0FCh, 83h, 0C2h, 01h, 89h, 55h, 0FCh, 8Bh, 45h, 0F4h, 83h
    db 0C0h, 01h, 89h, 45h, 0F4h, 0EBh, 0D5h, 8Bh, 4Dh, 0F0h, 03h, 4Dh, 0FCh, 0C6h, 01h, 00h
    db 0C7h, 45h, 0F8h, 00h, 00h, 00h, 00h, 8Bh, 45h, 0F8h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec4d0@@YAXXZ ENDP

; ghidra: FUN_00bec5c0  retail @ 0x007EC5C0 size 330
public ?d_007ec5c0@@YAXXZ
?d_007ec5c0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 38h, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0C8h, 0FEh, 0FFh, 0FFh
    db 0B9h, 4Eh, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 8Bh, 45h, 10h, 50h, 8Dh, 8Dh, 0D0h, 0FEh, 0FFh, 0FFh, 51h, 8Bh
    db 55h, 08h, 52h, 0E8h, 38h, 01h, 00h, 00h, 83h, 0C4h, 0Ch, 89h, 45h, 0F8h, 83h, 7Dh
    db 14h, 00h, 7Dh, 1Ch, 8Bh, 45h, 0F8h, 0C6h, 00h, 2Dh, 8Bh, 4Dh, 0F8h, 83h, 0C1h, 01h
    db 89h, 4Dh, 0F8h, 8Bh, 55h, 14h, 0F7h, 0DAh, 89h, 95h, 0C8h, 0FEh, 0FFh, 0FFh, 0EBh, 09h
    db 8Bh, 45h, 14h, 89h, 85h, 0C8h, 0FEh, 0FFh, 0FFh, 8Bh, 4Dh, 0F8h, 83h, 0C1h, 20h, 89h
    db 4Dh, 0F4h, 8Bh, 55h, 0F4h, 83h, 0EAh, 01h, 89h, 55h, 0F4h, 8Bh, 45h, 0F4h, 0C6h, 00h
    db 00h, 83h, 0BDh, 0C8h, 0FEh, 0FFh, 0FFh, 00h, 76h, 37h, 8Bh, 4Dh, 0F4h, 83h, 0E9h, 01h
    db 89h, 4Dh, 0F4h, 8Bh, 85h, 0C8h, 0FEh, 0FFh, 0FFh, 33h, 0D2h, 0B9h, 0Ah, 00h, 00h, 00h
    db 0F7h, 0F1h, 83h, 0C2h, 30h, 8Bh, 45h, 0F4h, 88h, 10h, 8Bh, 85h, 0C8h, 0FEh, 0FFh, 0FFh
    db 33h, 0D2h, 0B9h, 0Ah, 00h, 00h, 00h, 0F7h, 0F1h, 89h, 85h, 0C8h, 0FEh, 0FFh, 0FFh, 0EBh
    db 0C0h, 8Bh, 55h, 0F4h, 0Fh, 0B6h, 02h, 85h, 0C0h, 75h, 0Fh, 8Bh, 4Dh, 0F4h, 83h, 0E9h
    db 01h, 89h, 4Dh, 0F4h, 8Bh, 55h, 0F4h, 0C6h, 02h, 30h, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 08h
    db 85h, 0C9h, 74h, 1Eh, 8Bh, 55h, 0F8h, 8Bh, 45h, 0F4h, 8Ah, 08h, 88h, 0Ah, 8Bh, 55h
    db 0F8h, 83h, 0C2h, 01h, 89h, 55h, 0F8h, 8Bh, 45h, 0F4h, 83h, 0C0h, 01h, 89h, 45h, 0F4h
    db 0EBh, 0D8h, 8Bh, 4Dh, 0F8h, 0C6h, 01h, 00h, 8Dh, 95h, 0D0h, 0FEh, 0FFh, 0FFh, 52h, 8Bh
    db 45h, 0Ch, 50h, 8Bh, 4Dh, 08h, 51h, 0E8h, 0A4h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 52h
    db 8Bh, 0CDh, 50h, 8Dh, 15h, 0Ah, 0C7h, 0BEh, 00h, 0E8h, 37h, 0AEh, 20h, 00h, 58h, 5Ah
    db 8Bh, 4Dh, 0FCh, 0E8h, 0FCh, 0ADh, 20h, 00h, 5Fh, 81h, 0C4h, 38h, 01h, 00h, 00h, 3Bh
    db 0ECh, 0E8h, 0FCh, 0ADh, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec5c0@@YAXXZ ENDP

; ghidra: FUN_00bec730  retail @ 0x007EC730 size 77
public ?d_007ec730@@YAXXZ
?d_007ec730@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 7Dh, 10h, 00h, 75h, 08h, 8Bh, 45h, 08h, 0C6h, 00h, 00h, 0EBh
    db 37h, 8Bh, 4Dh, 10h, 0Fh, 0BEh, 11h, 85h, 0D2h, 74h, 1Eh, 8Bh, 45h, 0Ch, 8Bh, 4Dh
    db 10h, 8Ah, 11h, 88h, 10h, 8Bh, 45h, 0Ch, 83h, 0C0h, 01h, 89h, 45h, 0Ch, 8Bh, 4Dh
    db 10h, 83h, 0C1h, 01h, 89h, 4Dh, 10h, 0EBh, 0D8h, 8Bh, 55h, 0Ch, 0C6h, 02h, 3Dh, 8Bh
    db 45h, 0Ch, 83h, 0C0h, 01h, 89h, 45h, 0Ch, 8Bh, 45h, 0Ch, 5Dh, 0C3h
?d_007ec730@@YAXXZ ENDP

; ghidra: FUN_00bec780  retail @ 0x007EC780 size 879
public ?d_007ec780@@YAXXZ
?d_007ec780@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 1Ch, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 89h, 45h, 0E4h, 89h, 45h
    db 0E8h, 89h, 45h, 0ECh, 89h, 45h, 0F0h, 89h, 45h, 0F4h, 89h, 45h, 0F8h, 89h, 45h, 0FCh
    db 8Bh, 45h, 08h, 89h, 45h, 0E4h, 83h, 7Dh, 0E4h, 00h, 75h, 08h, 83h, 0C8h, 0FFh, 0E9h
    db 2Dh, 03h, 00h, 00h, 83h, 7Dh, 10h, 00h, 74h, 0Bh, 8Bh, 4Dh, 10h, 0Fh, 0BEh, 11h
    db 83h, 0FAh, 20h, 77h, 08h, 83h, 0C8h, 0FFh, 0E9h, 14h, 03h, 00h, 00h, 8Bh, 45h, 10h
    db 0Fh, 0BEh, 08h, 83h, 0F9h, 7Eh, 75h, 7Dh, 8Bh, 55h, 0E4h, 89h, 55h, 0F4h, 0EBh, 09h
    db 8Bh, 45h, 0F4h, 83h, 0C0h, 01h, 89h, 45h, 0F4h, 8Bh, 4Dh, 0F4h, 0Fh, 0B6h, 11h, 85h
    db 0D2h, 74h, 02h, 0EBh, 0EBh, 8Bh, 45h, 0F4h, 3Bh, 45h, 0E4h, 74h, 47h, 8Bh, 4Dh, 0F4h
    db 0Fh, 0B6h, 51h, 0FFh, 83h, 0FAh, 20h, 7Ch, 3Bh, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 48h, 0FFh
    db 0Fh, 0BEh, 15h, 1Ch, 39h, 2Ch, 01h, 3Bh, 0CAh, 74h, 29h, 8Bh, 45h, 0Ch, 8Bh, 4Dh
    db 0E4h, 8Dh, 54h, 01h, 0FFh, 39h, 55h, 0F4h, 73h, 1Ah, 8Bh, 45h, 0F4h, 8Ah, 0Dh, 1Ch
    db 39h, 2Ch, 01h, 88h, 08h, 8Bh, 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 8Bh, 45h
    db 0F4h, 0C6h, 00h, 00h, 8Bh, 4Dh, 0F4h, 89h, 4Dh, 0ECh, 8Bh, 55h, 0ECh, 89h, 55h, 0F0h
    db 0E9h, 59h, 01h, 00h, 00h, 8Bh, 45h, 0E4h, 89h, 45h, 0F4h, 8Bh, 4Dh, 0F4h, 0Fh, 0B6h
    db 11h, 85h, 0D2h, 75h, 60h, 8Bh, 45h, 0F4h, 3Bh, 45h, 0E4h, 74h, 47h, 8Bh, 4Dh, 0F4h
    db 0Fh, 0B6h, 51h, 0FFh, 83h, 0FAh, 20h, 7Ch, 3Bh, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 48h, 0FFh
    db 0Fh, 0BEh, 15h, 1Ch, 39h, 2Ch, 01h, 3Bh, 0CAh, 74h, 29h, 8Bh, 45h, 0Ch, 8Bh, 4Dh
    db 0E4h, 8Dh, 54h, 01h, 0FFh, 39h, 55h, 0F4h, 73h, 1Ah, 8Bh, 45h, 0F4h, 8Ah, 0Dh, 1Ch
    db 39h, 2Ch, 01h, 88h, 08h, 8Bh, 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 8Bh, 45h
    db 0F4h, 0C6h, 00h, 00h, 8Bh, 4Dh, 0F4h, 89h, 4Dh, 0ECh, 8Bh, 55h, 0ECh, 89h, 55h, 0F0h
    db 0E9h, 0E9h, 00h, 00h, 00h, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 08h, 83h, 0F9h, 20h, 7Fh, 0Bh
    db 8Bh, 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 0EBh, 80h, 8Bh, 45h, 0F4h, 0Fh, 0B6h
    db 08h, 0Fh, 0B6h, 91h, 10h, 0A3h, 12h, 01h, 83h, 0FAh, 01h, 75h, 11h, 8Bh, 45h, 0F4h
    db 89h, 45h, 0ECh, 8Bh, 4Dh, 0ECh, 89h, 4Dh, 0F0h, 0E9h, 0B0h, 00h, 00h, 00h, 0C7h, 45h
    db 0FCh, 00h, 00h, 00h, 00h, 0EBh, 09h, 8Bh, 55h, 0FCh, 83h, 0C2h, 01h, 89h, 55h, 0FCh
    db 8Bh, 45h, 0F4h, 03h, 45h, 0FCh, 0Fh, 0B6h, 08h, 8Ah, 91h, 10h, 0A3h, 12h, 01h, 88h
    db 55h, 0EBh, 8Bh, 45h, 10h, 03h, 45h, 0FCh, 0Fh, 0BEh, 08h, 8Ah, 91h, 10h, 0A3h, 12h
    db 01h, 88h, 55h, 0EAh, 0Fh, 0B6h, 45h, 0EBh, 0Fh, 0B6h, 4Dh, 0EAh, 3Bh, 0C1h, 75h, 09h
    db 0Fh, 0B6h, 55h, 0EBh, 83h, 0FAh, 02h, 7Dh, 02h, 0EBh, 02h, 0EBh, 0BAh, 0Fh, 0B6h, 45h
    db 0EBh, 0Fh, 0B6h, 4Dh, 0EAh, 03h, 0C1h, 83h, 0F8h, 02h, 75h, 39h, 8Bh, 55h, 0F4h, 89h
    db 55h, 0ECh, 8Bh, 45h, 0ECh, 89h, 45h, 0F0h, 0EBh, 09h, 8Bh, 4Dh, 0ECh, 83h, 0C1h, 01h
    db 89h, 4Dh, 0ECh, 8Bh, 55h, 0ECh, 0Fh, 0B6h, 02h, 83h, 0F8h, 20h, 7Ch, 02h, 0EBh, 0EAh
    db 8Bh, 4Dh, 0ECh, 0Fh, 0B6h, 11h, 85h, 0D2h, 7Eh, 09h, 8Bh, 45h, 0ECh, 83h, 0C0h, 01h
    db 89h, 45h, 0ECh, 0EBh, 19h, 8Bh, 4Dh, 0F4h, 83h, 0C1h, 01h, 89h, 4Dh, 0F4h, 8Bh, 55h
    db 0F4h, 0Fh, 0B6h, 02h, 83h, 0F8h, 20h, 7Dh, 0ECh, 0E9h, 0ADh, 0FEh, 0FFh, 0FFh, 0C7h, 45h
    db 0FCh, 00h, 00h, 00h, 00h, 0EBh, 09h, 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h, 4Dh, 0FCh
    db 8Bh, 55h, 10h, 03h, 55h, 0FCh, 0Fh, 0BEh, 02h, 83h, 0F8h, 20h, 72h, 02h, 0EBh, 0E7h
    db 8Bh, 4Dh, 0FCh, 83h, 0C1h, 01h, 89h, 4Dh, 0FCh, 8Bh, 55h, 0ECh, 2Bh, 55h, 0F0h, 8Bh
    db 45h, 0FCh, 2Bh, 0C2h, 89h, 45h, 0F8h, 8Bh, 4Dh, 0ECh, 89h, 4Dh, 0F4h, 0EBh, 09h, 8Bh
    db 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 8Bh, 45h, 0F4h, 0Fh, 0B6h, 08h, 85h, 0C9h
    db 74h, 02h, 0EBh, 0EBh, 8Bh, 55h, 0F4h, 83h, 0C2h, 01h, 89h, 55h, 0F4h, 83h, 7Dh, 0F8h
    db 00h, 7Eh, 16h, 8Bh, 45h, 0E4h, 03h, 45h, 0Ch, 2Bh, 45h, 0F4h, 3Bh, 45h, 0F8h, 7Dh
    db 08h, 83h, 0C8h, 0FFh, 0E9h, 0B8h, 00h, 00h, 00h, 83h, 7Dh, 0F8h, 00h, 75h, 1Fh, 8Bh
    db 4Dh, 0FCh, 51h, 8Bh, 55h, 10h, 52h, 8Bh, 45h, 0F0h, 50h, 0E8h, 96h, 0ABh, 20h, 00h
    db 83h, 0C4h, 0Ch, 85h, 0C0h, 75h, 07h, 33h, 0C0h, 0E9h, 93h, 00h, 00h, 00h, 83h, 7Dh
    db 0F8h, 00h, 7Eh, 1Ah, 8Bh, 4Dh, 0F4h, 2Bh, 4Dh, 0ECh, 51h, 8Bh, 55h, 0ECh, 52h, 8Bh
    db 45h, 0ECh, 03h, 45h, 0F8h, 50h, 0E8h, 5Bh, 0A4h, 20h, 00h, 83h, 0C4h, 0Ch, 83h, 7Dh
    db 0F8h, 00h, 7Dh, 1Fh, 8Bh, 4Dh, 0F0h, 2Bh, 4Dh, 0F8h, 8Bh, 55h, 0F4h, 2Bh, 0D1h, 52h
    db 8Bh, 45h, 0F0h, 2Bh, 45h, 0F8h, 50h, 8Bh, 4Dh, 0F0h, 51h, 0E8h, 36h, 0A4h, 20h, 00h
    db 83h, 0C4h, 0Ch, 8Bh, 55h, 0FCh, 52h, 8Bh, 45h, 10h, 50h, 8Bh, 4Dh, 0F0h, 51h, 0E8h
    db 14h, 0ABh, 20h, 00h, 83h, 0C4h, 0Ch, 8Bh, 55h, 0F0h, 03h, 55h, 0FCh, 0Fh, 0B6h, 02h
    db 85h, 0C0h, 75h, 18h, 0Fh, 0BEh, 0Dh, 1Ch, 39h, 2Ch, 01h, 83h, 0F9h, 0Ah, 74h, 0Ch
    db 8Bh, 55h, 0F0h, 03h, 55h, 0FCh, 0C6h, 42h, 0FFh, 00h, 0EBh, 0Fh, 8Bh, 45h, 0F0h, 03h
    db 45h, 0FCh, 8Ah, 0Dh, 1Ch, 39h, 2Ch, 01h, 88h, 48h, 0FFh, 8Bh, 45h, 0FCh, 83h, 0E8h
    db 01h, 83h, 0C4h, 1Ch, 3Bh, 0ECh, 0E8h, 17h, 0AAh, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ec780@@YAXXZ ENDP

; ghidra: FUN_00becaf0  retail @ 0x007ECAF0 size 205
public ?d_007ecaf0@@YAXXZ
?d_007ecaf0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 34h, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0CCh, 0FEh, 0FFh, 0FFh
    db 0B9h, 4Dh, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 8Bh, 45h, 10h, 50h, 8Dh, 8Dh, 0D0h, 0FEh, 0FFh, 0FFh, 51h, 8Bh
    db 55h, 08h, 52h, 0E8h, 08h, 0FCh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 89h, 45h, 0F8h, 0C7h, 45h
    db 0F4h, 10h, 0A4h, 12h, 01h, 0EBh, 11h, 8Bh, 45h, 14h, 0D1h, 0F8h, 89h, 45h, 14h, 8Bh
    db 4Dh, 0F4h, 83h, 0C1h, 01h, 89h, 4Dh, 0F4h, 83h, 7Dh, 14h, 00h, 74h, 27h, 8Bh, 55h
    db 0F4h, 0Fh, 0BEh, 02h, 85h, 0C0h, 74h, 1Dh, 8Bh, 4Dh, 14h, 83h, 0E1h, 01h, 74h, 13h
    db 8Bh, 55h, 0F8h, 8Bh, 45h, 0F4h, 8Ah, 08h, 88h, 0Ah, 8Bh, 55h, 0F8h, 83h, 0C2h, 01h
    db 89h, 55h, 0F8h, 0EBh, 0C2h, 8Bh, 45h, 0F8h, 0C6h, 00h, 00h, 8Dh, 8Dh, 0D0h, 0FEh, 0FFh
    db 0FFh, 51h, 8Bh, 55h, 0Ch, 52h, 8Bh, 45h, 08h, 50h, 0E8h, 0F1h, 0FBh, 0FFh, 0FFh, 83h
    db 0C4h, 0Ch, 52h, 8Bh, 0CDh, 50h, 8Dh, 15h, 0BDh, 0CBh, 0BEh, 00h, 0E8h, 84h, 0A9h, 20h
    db 00h, 58h, 5Ah, 8Bh, 4Dh, 0FCh, 0E8h, 49h, 0A9h, 20h, 00h, 5Fh, 81h, 0C4h, 34h, 01h
    db 00h, 00h, 3Bh, 0ECh, 0E8h, 49h, 0A9h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ecaf0@@YAXXZ ENDP

; ghidra: FUN_00becbe0  retail @ 0x007ECBE0 size 376
public ?d_007ecbe0@@YAXXZ
?d_007ecbe0@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 44h, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0BCh, 0FEh, 0FFh, 0FFh
    db 0B9h, 51h, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 8Bh, 45h, 10h, 50h, 8Dh, 8Dh, 0C0h, 0FEh, 0FFh, 0FFh, 51h, 8Bh
    db 55h, 08h, 52h, 0E8h, 18h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 89h, 45h, 0F0h, 8Ah, 45h
    db 14h, 88h, 45h, 0EBh, 8Bh, 4Dh, 14h, 0C1h, 0E9h, 08h, 89h, 4Dh, 14h, 8Ah, 55h, 14h
    db 88h, 55h, 0EAh, 8Bh, 45h, 14h, 0C1h, 0E8h, 08h, 89h, 45h, 14h, 8Ah, 4Dh, 14h, 88h
    db 4Dh, 0E9h, 8Bh, 55h, 14h, 0C1h, 0EAh, 08h, 89h, 55h, 14h, 8Ah, 45h, 14h, 88h, 45h
    db 0E8h, 0C7h, 45h, 0F8h, 00h, 00h, 00h, 00h, 0EBh, 09h, 8Bh, 4Dh, 0F8h, 83h, 0C1h, 01h
    db 89h, 4Dh, 0F8h, 83h, 7Dh, 0F8h, 04h, 0Fh, 8Dh, 0A3h, 00h, 00h, 00h, 8Bh, 55h, 0F8h
    db 8Ah, 44h, 15h, 0E8h, 88h, 45h, 0F7h, 83h, 7Dh, 0F8h, 00h, 7Eh, 0Fh, 8Bh, 4Dh, 0F0h
    db 0C6h, 01h, 2Eh, 8Bh, 55h, 0F0h, 83h, 0C2h, 01h, 89h, 55h, 0F0h, 0Fh, 0B6h, 45h, 0F7h
    db 83h, 0F8h, 09h, 7Eh, 61h, 0Fh, 0B6h, 4Dh, 0F7h, 83h, 0F9h, 63h, 7Eh, 2Ch, 0Fh, 0B6h
    db 45h, 0F7h, 99h, 0B9h, 64h, 00h, 00h, 00h, 0F7h, 0F9h, 83h, 0C0h, 30h, 8Bh, 55h, 0F0h
    db 88h, 02h, 8Bh, 45h, 0F0h, 83h, 0C0h, 01h, 89h, 45h, 0F0h, 0Fh, 0B6h, 45h, 0F7h, 99h
    db 0B9h, 64h, 00h, 00h, 00h, 0F7h, 0F9h, 88h, 55h, 0F7h, 0Fh, 0B6h, 45h, 0F7h, 99h, 0B9h
    db 0Ah, 00h, 00h, 00h, 0F7h, 0F9h, 83h, 0C0h, 30h, 8Bh, 55h, 0F0h, 88h, 02h, 8Bh, 45h
    db 0F0h, 83h, 0C0h, 01h, 89h, 45h, 0F0h, 0Fh, 0B6h, 45h, 0F7h, 99h, 0B9h, 0Ah, 00h, 00h
    db 00h, 0F7h, 0F9h, 88h, 55h, 0F7h, 0Fh, 0B6h, 55h, 0F7h, 83h, 0C2h, 30h, 8Bh, 45h, 0F0h
    db 88h, 10h, 8Bh, 4Dh, 0F0h, 83h, 0C1h, 01h, 89h, 4Dh, 0F0h, 0E9h, 4Ah, 0FFh, 0FFh, 0FFh
    db 8Bh, 55h, 0F0h, 0C6h, 02h, 00h, 8Dh, 85h, 0C0h, 0FEh, 0FFh, 0FFh, 50h, 8Bh, 4Dh, 0Ch
    db 51h, 8Bh, 55h, 08h, 52h, 0E8h, 56h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 52h, 8Bh, 0CDh
    db 50h, 8Dh, 15h, 58h, 0CDh, 0BEh, 00h, 0E8h, 0E9h, 0A7h, 20h, 00h, 58h, 5Ah, 8Bh, 4Dh
    db 0FCh, 0E8h, 0AEh, 0A7h, 20h, 00h, 5Fh, 81h, 0C4h, 44h, 01h, 00h, 00h, 3Bh, 0ECh, 0E8h
    db 0AEh, 0A7h, 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ecbe0@@YAXXZ ENDP

; ghidra: FUN_00becd90  retail @ 0x007ECD90 size 182
public ?d_007ecd90@@YAXXZ
?d_007ecd90@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 81h, 0ECh, 30h, 01h, 00h, 00h, 57h, 8Dh, 0BDh, 0D0h, 0FEh, 0FFh, 0FFh
    db 0B9h, 4Ch, 00h, 00h, 00h, 0B8h, 0CCh, 0CCh, 0CCh, 0CCh, 0F3h, 0ABh, 0A1h, 0B0h, 0BDh, 2Dh
    db 01h, 89h, 45h, 0FCh, 8Bh, 45h, 10h, 50h, 8Dh, 8Dh, 0D4h, 0FEh, 0FFh, 0FFh, 51h, 8Bh
    db 55h, 08h, 52h, 0E8h, 68h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 89h, 45h, 0F8h, 0EBh, 09h
    db 8Bh, 45h, 14h, 0C1h, 0E0h, 08h, 89h, 45h, 14h, 83h, 7Dh, 14h, 00h, 74h, 1Fh, 81h
    db 7Dh, 14h, 0FFh, 0FFh, 0FFh, 20h, 7Eh, 14h, 8Bh, 4Dh, 14h, 0C1h, 0F9h, 18h, 8Bh, 55h
    db 0F8h, 88h, 0Ah, 8Bh, 45h, 0F8h, 83h, 0C0h, 01h, 89h, 45h, 0F8h, 0EBh, 0D2h, 8Bh, 4Dh
    db 0F8h, 0C6h, 01h, 00h, 8Dh, 95h, 0D4h, 0FEh, 0FFh, 0FFh, 52h, 8Bh, 45h, 0Ch, 50h, 8Bh
    db 4Dh, 08h, 51h, 0E8h, 68h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 52h, 8Bh, 0CDh, 50h, 8Dh
    db 15h, 46h, 0CEh, 0BEh, 00h, 0E8h, 0FBh, 0A6h, 20h, 00h, 58h, 5Ah, 8Bh, 4Dh, 0FCh, 0E8h
    db 0C0h, 0A6h, 20h, 00h, 5Fh, 81h, 0C4h, 30h, 01h, 00h, 00h, 3Bh, 0ECh, 0E8h, 0C0h, 0A6h
    db 20h, 00h, 8Bh, 0E5h, 5Dh, 0C3h
?d_007ecd90@@YAXXZ ENDP
_TEXT ENDS
END
