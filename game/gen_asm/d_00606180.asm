.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0INIException@@QAA@HPBDZZ:NEAR
EXTERN ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?g_INIExceptionThrowInfo@@3HA:BYTE
EXTERN ?g_lookup@@3P6APAXPAX0@ZA:BYTE
EXTERN ?getNextSubToken@INI@@QAEPBDPBD@Z:NEAR
EXTERN ?getNextToken@INI@@QAEPBDPBD@Z:NEAR
EXTERN ?getNextTokenOrNull@INI@@QAEPBDPBD@Z:NEAR
EXTERN ?j_00008fd5@@YAXXZ:NEAR
EXTERN ?j_0000aab5@@YAXXZ:NEAR
EXTERN ?j_000190f1@@YAXXZ:NEAR
EXTERN ?j_000362ff@@YAXXZ:NEAR
EXTERN ?ji_009f6d00@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?scanReal@INI@@SAMPBD@Z:NEAR
EXTERN __imp__InterlockedDecrement@4:BYTE
EXTERN g_Va0103D701:NEAR
EXTERN g_Va010A4FAC:BYTE
EXTERN g_Va010A4FB0:BYTE
EXTERN g_Va010FD09C:BYTE
EXTERN g_Va010FD0A0:BYTE
EXTERN g_Va010FD0A4:BYTE
EXTERN g_Va0110D4C8:BYTE
EXTERN g_Va0110D4CC:BYTE
EXTERN g_Va0110D4CE:BYTE
EXTERN g_Va01115634:BYTE
EXTERN g_Va01115670:BYTE
EXTERN g_Va01115680:BYTE
EXTERN g_Va011156CC:BYTE
EXTERN g_Va011156FC:BYTE
EXTERN g_Va01115734:BYTE
EXTERN g_Va01115738:BYTE
EXTERN g_Va0111573C:BYTE
EXTERN g_Va0111573E:BYTE
EXTERN g_Va01115744:BYTE
EXTERN g_Va01115748:BYTE
EXTERN g_Va0111574C:BYTE
EXTERN g_Va0111574E:BYTE
_TEXT SEGMENT

; retail @ 0x00606180 size 1417
_TEXT ENDS
_TEXT$d00a06180 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00A06180 size 1417
public ?d_00606180@@YAXXZ
?d_00606180@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va0103D701
    db 050h, 08Bh, 044h, 024h, 014h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 0FCh, 000h
    db 000h, 000h, 085h, 0C0h, 00Fh, 084h, 0CDh, 004h, 000h, 000h, 066h, 08Bh, 00Dh
    dd g_Va010A4FB0
    db 0A1h
    dd g_Va010A4FAC
    db 08Bh, 015h
    dd g_Va01115744
    db 066h, 089h, 04Ch, 024h, 048h, 066h, 08Bh, 00Dh
    dd g_Va0111574C
    db 089h, 044h, 024h, 044h, 0A1h
    dd g_Va01115748
    db 066h, 089h, 04Ch, 024h, 03Ch, 08Bh, 00Dh
    dd g_Va01115738
    db 089h, 054h, 024h, 034h, 08Ah, 015h
    dd g_Va0111574E
    db 089h, 044h, 024h, 038h, 0A1h
    dd g_Va01115734
    db 089h, 04Ch, 024h, 02Ch, 08Bh, 00Dh
    dd g_Va010FD09C
    db 088h, 054h, 024h, 03Eh, 066h, 08Bh, 015h
    dd g_Va0111573C
    db 089h, 044h, 024h, 028h, 0A0h
    dd g_Va0111573E
    db 089h, 04Ch, 024h, 018h, 08Bh, 00Dh
    dd g_Va0110D4C8
    db 066h, 089h, 054h, 024h, 030h, 08Bh, 015h
    dd g_Va010FD0A0
    db 088h, 044h, 024h, 032h, 066h, 0A1h
    dd g_Va010FD0A4
    db 089h, 04Ch, 024h, 010h, 057h, 08Bh, 0BCh, 024h, 010h, 001h, 000h, 000h, 08Dh, 04Ch, 024h, 048h
    db 089h, 054h, 024h, 020h, 066h, 08Bh, 015h
    dd g_Va0110D4CC
    db 066h, 089h, 044h, 024h, 024h, 0A0h
    dd g_Va0110D4CE
    db 051h, 08Bh, 0CFh, 066h, 089h, 054h, 024h, 01Ch, 088h, 044h, 024h, 01Eh
    call ?getNextSubToken@INI@@QAEPBDPBD@Z
    db 050h, 08Dh, 04Ch, 024h, 010h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 044h, 024h, 00Ch, 085h, 0C0h, 0C7h, 084h, 024h, 008h, 001h, 000h, 000h, 000h, 000h, 000h
    db 000h, 074h, 007h, 066h, 083h, 078h, 004h, 000h, 075h, 023h, 068h
    dd g_Va011156FC
    db 08Dh, 054h, 024h, 008h, 06Ah, 003h, 052h
    call ??0INIException@@QAA@HPBDZZ
    db 083h, 0C4h, 00Ch, 068h
    dd ?g_INIExceptionThrowInfo@@3HA
    db 08Dh, 044h, 024h, 008h, 050h
    call ?ji_009f6d00@@YAXXZ
    db 08Bh, 00Dh
    dd ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A
    db 08Bh, 011h, 08Dh, 044h, 024h, 00Ch, 050h, 08Dh, 044h, 024h, 014h, 050h, 0FFh, 092h, 018h, 001h
    db 000h, 000h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 0C6h, 084h, 024h, 008h, 001h, 000h, 000h, 001h
    db 075h, 036h, 08Bh, 044h, 024h, 00Ch, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 068h
    dd g_Va011156CC
    db 08Dh, 04Ch, 024h, 00Ch, 06Ah, 003h, 051h
    call ??0INIException@@QAA@HPBDZZ
    db 083h, 0C4h, 010h, 068h
    dd ?g_INIExceptionThrowInfo@@3HA
    db 08Dh, 054h, 024h, 008h, 052h
    call ?ji_009f6d00@@YAXXZ
    db 08Bh, 087h, 01Ch, 004h, 000h, 000h, 055h, 056h, 050h, 08Bh, 0CFh
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 02Dh
    dd ?g_lookup@@3P6APAXPAX0@ZA
    db 08Bh, 0F0h, 033h, 0C0h, 033h, 0C9h, 085h, 0F6h, 089h, 084h, 024h, 080h, 000h, 000h, 000h, 089h
    db 04Ch, 024h, 058h, 089h, 084h, 024h, 084h, 000h, 000h, 000h, 089h, 04Ch, 024h, 05Ch, 089h, 084h
    db 024h, 088h, 000h, 000h, 000h, 089h, 04Ch, 024h, 060h, 089h, 084h, 024h, 08Ch, 000h, 000h, 000h
    db 089h, 04Ch, 024h, 064h, 089h, 084h, 024h, 090h, 000h, 000h, 000h, 089h, 04Ch, 024h, 068h, 089h
    db 084h, 024h, 094h, 000h, 000h, 000h, 089h, 04Ch, 024h, 06Ch, 089h, 084h, 024h, 098h, 000h, 000h
    db 000h, 089h, 04Ch, 024h, 070h, 089h, 084h, 024h, 09Ch, 000h, 000h, 000h, 089h, 04Ch, 024h, 074h
    db 089h, 084h, 024h, 0A0h, 000h, 000h, 000h, 089h, 04Ch, 024h, 078h, 089h, 084h, 024h, 0A4h, 000h
    db 000h, 000h, 089h, 04Ch, 024h, 07Ch, 00Fh, 084h, 081h, 001h, 000h, 000h, 08Dh, 054h, 024h, 040h
    db 052h, 056h, 0FFh, 0D5h, 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 0BBh, 000h, 000h, 000h, 08Bh
    db 087h, 01Ch, 004h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?getNextToken@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 056h
    call ?j_000190f1@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 00Fh, 08Ch, 0B8h, 002h, 000h, 000h, 08Bh, 0C8h, 0C1h, 0E9h, 005h
    db 08Bh, 0B4h, 08Ch, 080h, 000h, 000h, 000h, 08Dh, 094h, 08Ch, 080h, 000h, 000h, 000h, 08Bh, 0C8h
    db 083h, 0E1h, 01Fh, 0B8h, 001h, 000h, 000h, 000h, 0D3h, 0E0h, 08Bh, 0CFh, 00Bh, 0F0h, 08Bh, 087h
    db 01Ch, 004h, 000h, 000h, 050h, 089h, 032h
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 00Bh, 001h, 000h, 000h, 08Dh, 04Ch, 024h, 040h, 051h, 056h
    db 0FFh, 0D5h, 083h, 0C4h, 008h, 085h, 0C0h, 075h, 010h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h
    db 08Bh, 0CFh
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 0E4h, 000h, 000h, 000h, 08Dh, 054h, 024h, 034h, 052h, 056h
    db 0FFh, 0D5h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 022h, 08Dh, 044h, 024h, 024h, 050h, 056h, 0FFh
    db 0D5h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 013h, 08Dh, 04Ch, 024h, 01Ch, 051h, 056h, 0FFh, 0D5h
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 05Ch, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 00Fh, 084h, 0ABh
    db 000h, 000h, 000h, 08Dh, 054h, 024h, 034h, 052h, 056h, 0FFh, 0D5h, 083h, 0C4h, 008h, 085h, 0C0h
    db 00Fh, 085h, 098h, 000h, 000h, 000h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?getNextToken@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 090h, 056h
    call ?j_000190f1@@YAXXZ
    db 083h, 0C4h, 004h, 085h, 0C0h, 00Fh, 08Ch, 011h, 002h, 000h, 000h, 08Bh, 0C8h, 0C1h, 0E9h, 005h
    db 08Bh, 074h, 08Ch, 058h, 08Dh, 054h, 08Ch, 058h, 08Bh, 0C8h, 083h, 0E1h, 01Fh, 0B8h, 001h, 000h
    db 000h, 000h, 0D3h, 0E0h, 08Bh, 0CFh, 00Bh, 0F0h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h, 089h
    db 032h
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 045h, 08Dh, 04Ch, 024h, 034h, 051h, 056h, 0FFh, 0D5h, 083h, 0C4h
    db 008h, 085h, 0C0h, 075h, 010h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 022h, 08Dh, 054h, 024h, 024h, 052h, 056h, 0FFh, 0D5h, 083h, 0C4h
    db 008h, 085h, 0C0h, 074h, 013h, 08Dh, 044h, 024h, 01Ch, 050h, 056h, 0FFh, 0D5h, 083h, 0C4h, 008h
    db 085h, 0C0h, 00Fh, 085h, 079h, 0FFh, 0FFh, 0FFh, 085h, 0F6h, 053h, 00Fh, 084h, 0BBh, 001h, 000h
    db 000h, 08Dh, 04Ch, 024h, 028h, 051h, 056h, 0FFh, 0D5h, 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h
    db 0ADh, 001h, 000h, 000h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?getNextToken@INI@@QAEPBDPBD@Z
    db 050h, 08Dh, 04Ch, 024h, 038h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 020h, 052h, 08Bh, 0CFh, 0C6h, 084h, 024h, 018h, 001h, 000h, 000h, 002h
    call ?getNextSubToken@INI@@QAEPBDPBD@Z
    db 08Bh, 09Ch, 024h, 020h, 001h, 000h, 000h, 08Bh, 0F0h, 083h, 0C3h, 008h, 0EBh, 003h, 08Dh, 049h
    db 000h, 056h
    call ?scanReal@INI@@SAMPBD@Z
    db 0D9h, 05Ch, 024h, 054h, 08Bh, 054h, 024h, 054h, 083h, 0C4h, 004h, 08Dh, 044h, 024h, 05Ch, 050h
    db 08Dh, 08Ch, 024h, 088h, 000h, 000h, 000h, 051h, 052h, 08Dh, 044h, 024h, 040h, 050h, 08Dh, 04Ch
    db 024h, 02Ch, 051h, 08Dh, 08Ch, 024h, 0C0h, 000h, 000h, 000h
    call ?j_00008fd5@@YAXXZ
    db 08Dh, 094h, 024h, 0ACh, 000h, 000h, 000h, 052h, 08Dh, 044h, 024h, 014h, 050h, 08Bh, 0CBh, 0C6h
    db 084h, 024h, 01Ch, 001h, 000h, 000h, 003h
    call ?j_0000aab5@@YAXXZ
    db 08Bh, 087h, 01Ch, 004h, 000h, 000h, 050h, 08Bh, 0CFh
    call ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
    db 08Bh, 0F0h, 08Bh, 084h, 024h, 0B0h, 000h, 000h, 000h, 085h, 0C0h, 0C6h, 084h, 024h, 014h, 001h
    db 000h, 000h, 004h, 074h, 023h, 08Bh, 0E8h, 083h, 0C0h, 004h, 050h, 0FFh, 015h
    dd __imp__InterlockedDecrement@4
    db 085h, 0C0h, 07Fh, 00Dh, 085h, 0EDh, 074h, 009h, 08Bh, 055h, 000h, 06Ah, 001h, 08Bh, 0CDh, 0FFh
    db 012h, 08Bh, 02Dh
    dd ?g_lookup@@3P6APAXPAX0@ZA
    db 08Dh, 08Ch, 024h, 0ACh, 000h, 000h, 000h, 0C6h, 084h, 024h, 014h, 001h, 000h, 000h, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 085h, 0F6h, 074h, 013h, 08Dh, 044h, 024h, 028h, 050h, 056h, 0FFh, 0D5h, 083h, 0C4h, 008h, 085h
    db 0C0h, 00Fh, 085h, 03Eh, 0FFh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 034h, 0C6h, 084h, 024h, 014h, 001h
    db 000h, 000h, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 085h, 0F6h, 00Fh, 085h, 0D5h, 0FEh, 0FFh, 0FFh, 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 014h
    db 001h, 000h, 000h, 000h
    call ?j_000362ff@@YAXXZ
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 084h, 024h, 014h, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 05Bh, 05Eh, 05Dh, 05Fh, 08Bh, 08Ch, 024h, 0FCh, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 081h, 0C4h, 008h, 001h, 000h, 000h, 0C3h, 08Dh, 054h, 024h, 040h, 052h, 056h, 068h
    dd g_Va01115680
    db 08Dh, 044h, 024h, 018h, 06Ah, 003h, 050h
    call ??0INIException@@QAA@HPBDZZ
    db 083h, 0C4h, 014h, 068h
    dd ?g_INIExceptionThrowInfo@@3HA
    db 08Dh, 04Ch, 024h, 010h, 051h
    call ?ji_009f6d00@@YAXXZ
    db 08Dh, 04Ch, 024h, 034h, 051h, 056h, 068h
    dd g_Va01115680
    db 08Dh, 054h, 024h, 018h, 06Ah, 003h, 052h
    call ??0INIException@@QAA@HPBDZZ
    db 083h, 0C4h, 014h, 068h
    dd ?g_INIExceptionThrowInfo@@3HA
    db 08Dh, 044h, 024h, 010h, 050h
    call ?ji_009f6d00@@YAXXZ
    db 0BEh
    dd g_Va01115670
    db 056h, 08Dh, 04Ch, 024h, 02Ch, 051h, 068h
    dd g_Va01115634
    db 08Dh, 054h, 024h, 01Ch, 06Ah, 003h, 052h
    call ??0INIException@@QAA@HPBDZZ
    db 083h, 0C4h, 014h, 068h
    dd ?g_INIExceptionThrowInfo@@3HA
    db 08Dh, 044h, 024h, 014h, 050h
    call ?ji_009f6d00@@YAXXZ
?d_00606180@@YAXXZ ENDP
_TEXT$d00a06180 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
