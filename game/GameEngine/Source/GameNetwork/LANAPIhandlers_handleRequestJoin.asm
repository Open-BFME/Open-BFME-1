.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0?$StringBase@G@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@G@@AAE@PBG@Z:NEAR
EXTERN ??0INI@@QAE@XZ:NEAR
EXTERN ??1INI@@QAE@XZ:NEAR
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?TheGameText@@3PAVBfmeGameText@@A:BYTE
EXTERN ?g_Rva01088AF4EmptyWideString@@3QBGB:BYTE
EXTERN ?g_bfmeAlphaScale1293@@3MA:BYTE
EXTERN ?j_0002fbd0@@YAXXZ:NEAR
EXTERN ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z:NEAR
EXTERN ?releaseBuffer@?$StringBase@G@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@G@@QAEXABV1@@Z:NEAR
EXTERN __ftol2:NEAR
EXTERN g_Va01038698:NEAR
EXTERN g_Va010386B8:NEAR
EXTERN g_Va0110D5F8:BYTE
EXTERN g_Va0110D610:BYTE

; ?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z
; Exact 1119 retail bytes @ 0x005A565D
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d009a565d SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x009A565D size 1119
public ?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z
?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z PROC
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 04Ch, 008h, 000h, 000h, 08Dh, 04Ch
    db 024h, 004h
    call ??0INI@@QAE@XZ
    db 06Ah, 000h, 06Ah, 001h, 051h, 089h, 064h, 024h, 00Ch, 08Bh, 0CCh, 068h
    dd g_Va0110D5F8
    db 0C7h, 084h, 024h, 064h, 008h, 000h, 000h, 000h, 000h, 000h, 000h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 010h
    call ?load@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z
    db 08Dh, 04Ch, 024h, 004h, 0C7h, 084h, 024h, 054h, 008h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1INI@@QAE@XZ
    db 08Bh, 08Ch, 024h, 04Ch, 008h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 081h, 0C4h
    db 058h, 008h, 000h, 000h, 0C3h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 064h
    db 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01038698
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 056h, 057h, 08Bh, 0F1h, 08Bh, 044h, 024h, 01Ch
    db 08Dh, 054h, 024h, 018h, 08Dh, 08Eh, 000h, 011h, 000h, 000h, 052h, 0C7h, 044h, 024h, 014h, 000h
    db 000h, 000h, 000h, 089h, 086h, 0D0h, 04Dh, 000h, 000h
    call ?set@?$StringBase@G@@QAEXABV1@@Z
    db 08Bh, 07Ch, 024h, 020h, 085h, 0FFh, 00Fh, 084h, 032h, 001h, 000h, 000h, 08Ah, 086h, 0E4h, 010h
    db 000h, 000h, 084h, 0C0h, 00Fh, 084h, 093h, 000h, 000h, 000h, 08Ah, 086h, 0E6h, 010h, 000h, 000h
    db 0D9h, 007h, 084h, 0C0h, 074h, 042h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 00Dh
    dd g_Va0110D610
    call __ftol2
    db 089h, 086h, 0E0h, 04Dh, 000h, 000h, 0D9h, 047h, 004h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 00Dh
    dd g_Va0110D610
    call __ftol2
    db 089h, 086h, 0E4h, 04Dh, 000h, 000h, 0D9h, 047h, 008h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 00Dh
    dd g_Va0110D610
    db 0EBh, 02Eh, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 089h, 086h, 0E0h, 04Dh, 000h, 000h, 0D9h, 047h, 004h, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 089h, 086h, 0E4h, 04Dh, 000h, 000h, 0D9h, 047h, 008h, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 089h, 086h, 0E8h, 04Dh, 000h, 000h, 08Bh, 086h, 09Ch, 010h, 000h, 000h, 089h, 086h, 0ECh, 04Dh
    db 000h, 000h, 08Ah, 086h, 0E5h, 010h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 0C7h, 000h, 000h, 000h
    db 08Ah, 086h, 0E6h, 010h, 000h, 000h, 0D9h, 007h, 084h, 0C0h, 074h, 030h, 0D8h, 00Dh
    dd g_Va0110D610
    call __ftol2
    db 089h, 086h, 0F0h, 04Dh, 000h, 000h, 0D9h, 047h, 004h, 0D8h, 00Dh
    dd g_Va0110D610
    call __ftol2
    db 089h, 086h, 0F4h, 04Dh, 000h, 000h, 0D9h, 047h, 008h, 0D8h, 00Dh
    dd g_Va0110D610
    db 0EBh, 02Eh, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 089h, 086h, 0F0h, 04Dh, 000h, 000h, 0D9h, 047h, 004h, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 089h, 086h, 0F4h, 04Dh, 000h, 000h, 0D9h, 047h, 008h, 0D8h, 00Dh
    dd ?g_bfmeAlphaScale1293@@3MA
    call __ftol2
    db 08Bh, 08Eh, 0CCh, 010h, 000h, 000h, 089h, 086h, 0F8h, 04Dh, 000h, 000h, 089h, 08Eh, 0FCh, 04Dh
    db 000h, 000h, 0EBh, 044h, 08Dh, 096h, 090h, 010h, 000h, 000h, 08Bh, 00Ah, 08Dh, 086h, 0E0h, 04Dh
    db 000h, 000h, 089h, 008h, 08Bh, 04Ah, 004h, 089h, 048h, 004h, 08Bh, 04Ah, 008h, 08Bh, 052h, 00Ch
    db 089h, 048h, 008h, 089h, 050h, 00Ch, 08Dh, 086h, 0C0h, 010h, 000h, 000h, 08Bh, 008h, 08Bh, 050h
    db 004h, 081h, 0C6h, 0F0h, 04Dh, 000h, 000h, 089h, 00Eh, 08Bh, 048h, 008h, 089h, 056h, 004h, 08Bh
    db 050h, 00Ch, 089h, 04Eh, 008h, 089h, 056h, 00Ch, 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 010h
    db 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 04Ch, 024h, 008h, 05Fh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch
    db 0C2h, 010h, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 06Ah, 0FFh, 068h
    dd g_Va010386B8
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 056h
    db 08Bh, 0F1h, 08Bh, 086h, 0ACh, 04Dh, 000h, 000h, 085h, 0C0h, 0C7h, 044h, 024h, 010h, 000h, 000h
    db 000h, 000h, 074h, 064h, 051h, 08Dh, 044h, 024h, 01Ch, 089h, 064h, 024h, 008h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 08Bh, 08Eh, 0ACh, 04Dh, 000h, 000h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 044h, 024h, 01Ch, 085h
    db 0C0h, 074h, 01Ch, 08Bh, 010h, 08Dh, 08Eh, 0B0h, 04Dh, 000h, 000h, 089h, 011h, 08Bh, 050h, 004h
    db 089h, 051h, 004h, 08Bh, 050h, 008h, 089h, 051h, 008h, 08Bh, 040h, 00Ch, 089h, 041h, 00Ch, 08Bh
    db 044h, 024h, 020h, 085h, 0C0h, 074h, 01Ch, 08Bh, 008h, 081h, 0C6h, 0C0h, 04Dh, 000h, 000h, 089h
    db 00Eh, 08Bh, 050h, 004h, 089h, 056h, 004h, 08Bh, 048h, 008h, 089h, 04Eh, 008h, 08Bh, 050h, 00Ch
    db 089h, 056h, 00Ch, 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 010h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 010h, 0C2h
    db 00Ch, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 08Bh, 044h, 024h, 004h, 056h, 08Bh, 0F1h, 039h, 086h, 0A8h, 04Dh, 000h, 000h, 057h, 074h, 077h
    db 08Bh, 08Eh, 0ACh, 04Dh, 000h, 000h, 085h, 0C9h, 074h, 06Dh, 06Bh, 0C0h, 054h, 08Bh, 04Ch, 030h
    db 00Ch, 085h, 0C9h, 08Dh, 044h, 030h, 008h, 074h, 042h, 066h, 083h, 079h, 004h, 000h, 074h, 03Bh
    db 08Dh, 048h, 018h, 08Dh, 050h, 008h, 08Bh, 040h, 004h, 085h, 0C0h, 051h, 052h, 074h, 005h, 083h
    db 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 051h, 08Bh, 0FCh, 089h, 064h, 024h, 018h, 06Ah, 000h, 050h, 057h, 0FFh, 052h, 028h
    db 08Bh, 0CEh
    call ?j_0002fbd0@@YAXXZ
    db 05Fh, 05Eh, 0C2h, 004h, 000h, 06Ah, 000h, 06Ah, 000h, 051h, 089h, 064h, 024h, 018h, 08Bh, 0CCh
    db 068h
    dd ?g_Rva01088AF4EmptyWideString@@3QBGB
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 08Bh, 0CEh
    call ?j_0002fbd0@@YAXXZ
    db 05Fh, 05Eh, 0C2h, 004h, 000h
?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z ENDP
_TEXT$d009a565d ENDS
_TEXT SEGMENT
_TEXT ENDS
END
