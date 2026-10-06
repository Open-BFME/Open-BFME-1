.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0?$StringBase@G@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@G@@AAE@PBG@Z:NEAR
EXTERN ?BFMEEmptyString@@3QBGB:BYTE
EXTERN ?BFMEEmptyUnicodeString@@3GB:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva012F7194@@3PAVRva012F7194Slots@@A:BYTE
EXTERN ?TheGameSpyConfig@@3PAVGameSpyConfig@@A:BYTE
EXTERN ?TheGameText@@3PAVBfmeGameText@@A:BYTE
EXTERN ?TheLadderList@@3PAVLadderList@@A:BYTE
EXTERN ?TheMapCache@@3PAVMapCache@@A:BYTE
EXTERN ?TheMappedImageCollection@@3PAVImageCollection@@A:BYTE
EXTERN ?format@UnicodeString@@QAAXV1@ZZ:NEAR
EXTERN ?j_000019f6@@YAXXZ:NEAR
EXTERN ?j_000048f4@@YAXXZ:NEAR
EXTERN ?j_0001712a@@YAXXZ:NEAR
EXTERN ?j_00019880@@YAXXZ:NEAR
EXTERN ?j_0001b720@@YAXXZ:NEAR
EXTERN ?j_0001c666@@YAXXZ:NEAR
EXTERN ?j_0001d606@@YAXXZ:NEAR
EXTERN ?j_00022507@@YAXXZ:NEAR
EXTERN ?j_00024d43@@YAXXZ:NEAR
EXTERN ?j_0002c7b4@@YAXXZ:NEAR
EXTERN ?j_0002f28e@@YAXXZ:NEAR
EXTERN ?j_00035959@@YAXXZ:NEAR
EXTERN ?j_0003fe86@@YAXXZ:NEAR
EXTERN ?j_00049f30@@YAXXZ:NEAR
EXTERN ?j_0004b09c@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@G@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@G@@QAEXABV1@@Z:NEAR
EXTERN ?translate@UnicodeString@@QAEXABVAsciiString@@@Z:NEAR
EXTERN g_Va01040488:NEAR
EXTERN g_Va0109FD6C:BYTE
EXTERN g_Va010F9F60:BYTE
EXTERN g_Va010F9F68:BYTE
EXTERN g_Va010FFEC0:BYTE
EXTERN g_Va011184CC:BYTE
EXTERN g_Va011184D8:BYTE
EXTERN g_Va012B920C:BYTE
EXTERN g_Va012B9210:BYTE
EXTERN g_Va012B9214:BYTE
EXTERN g_Va012F713C:BYTE
EXTERN g_Va012F7140:BYTE
EXTERN g_Va012F7144:BYTE

; ?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z
; Exact 1487 retail bytes @ 0x0062DB90
; Identity: GUI:UnknownLadder/GUI:NoLadder/Password/Observer string anchors;
; SEH prologue; sits after matched GrabWindowInfo @ 0x62D810 size 713.
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d00a2db90 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00A2DB90 size 1487
public ?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z
?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01040488
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 014h, 053h, 055h, 08Bh, 06Ch, 024h, 02Ch, 056h, 057h, 08Bh, 0F9h
    call ?j_00022507@@YAXXZ
    db 08Bh, 01Dh
    dd g_Va012B920C
    db 08Bh, 0CFh
    call ?j_0001b720@@YAXXZ
    db 08Bh, 0CFh, 08Bh, 0F0h
    call ?j_0001c666@@YAXXZ
    db 03Bh, 0C6h, 074h, 00Ch, 08Bh, 0CFh
    call ?j_0004b09c@@YAXXZ
    db 083h, 0F8h, 008h, 075h, 006h, 08Bh, 01Dh
    dd g_Va012B9210
    db 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 080h, 0D0h, 00Bh, 000h, 000h, 08Bh, 0B7h, 030h, 004h, 000h, 000h, 050h, 050h
    call ?j_000019f6@@YAXXZ
    db 083h, 0C4h, 008h, 03Bh, 0F0h, 075h, 022h, 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 087h, 034h, 004h, 000h, 000h, 03Bh, 081h, 0C8h, 00Bh, 000h, 000h, 075h, 00Eh, 08Bh, 087h
    db 038h, 004h, 000h, 000h, 03Bh, 081h, 0D4h, 00Bh, 000h, 000h, 074h, 006h, 08Bh, 01Dh
    dd g_Va012B9214
    db 08Dh, 04Ch, 024h, 018h, 051h, 08Bh, 0CFh
    call ?j_0002c7b4@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012F7194@@3PAVRva012F7194Slots@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 02Ch, 000h, 000h, 000h, 000h, 0FFh, 092h, 0DCh, 000h, 000h, 000h
    db 084h, 0C0h, 00Fh, 084h, 0B1h, 000h, 000h, 000h, 08Bh, 044h, 024h, 018h, 085h, 0C0h, 074h, 009h
    db 00Fh, 0B7h, 048h, 004h, 08Dh, 050h, 008h, 0EBh, 007h, 0BAh
    dd ?BFMEEmptyUnicodeString@@3GB
    db 033h, 0C9h, 033h, 0C0h, 085h, 0C9h, 07Eh, 011h, 066h, 081h, 03Ch, 042h, 000h, 001h, 00Fh, 083h
    db 0D3h, 000h, 000h, 000h, 040h, 03Bh, 0C1h, 07Ch, 0EFh, 06Ah, 001h, 06Ah, 000h, 06Ah, 0FFh, 053h
    db 051h, 08Bh, 0CCh, 089h, 064h, 024h, 034h, 051h, 08Bh, 0CFh
    call ?j_0002c7b4@@YAXXZ
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 08Bh, 0F0h, 08Bh, 087h, 01Ch, 004h, 000h, 000h, 06Ah, 000h, 056h, 050h, 055h
    call ?j_00049f30@@YAXXZ
    db 033h, 0C0h, 083h, 0C4h, 028h, 089h, 044h, 024h, 014h, 08Ah, 04Ch, 024h, 038h, 084h, 0C9h, 0C6h
    db 044h, 024h, 02Ch, 001h, 00Fh, 084h, 01Fh, 002h, 000h, 000h, 089h, 044h, 024h, 01Ch, 051h, 08Bh
    db 0D4h, 089h, 064h, 024h, 024h, 052h, 08Bh, 0CFh, 0C6h, 044h, 024h, 034h, 002h
    call ?j_0002f28e@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheMapCache@@3PAVMapCache@@A
    call ?j_00019880@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 082h, 000h, 000h, 000h, 050h, 08Dh, 04Ch, 024h, 020h
    call ?set@?$StringBase@G@@QAEXABV1@@Z
    db 0E9h, 02Bh, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?Rva012F7194@@3PAVRva012F7194Slots@@A
    db 08Bh, 001h, 0FFh, 090h, 0E0h, 000h, 000h, 000h, 084h, 0C0h, 00Fh, 084h, 068h, 0FFh, 0FFh, 0FFh
    db 08Bh, 044h, 024h, 018h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 08Dh, 050h, 008h, 0EBh
    db 007h, 0BAh
    dd ?BFMEEmptyUnicodeString@@3GB
    db 033h, 0C9h, 033h, 0C0h, 085h, 0C9h, 07Eh, 018h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 066h
    db 081h, 03Ch, 042h, 000h, 001h, 00Fh, 083h, 037h, 0FFh, 0FFh, 0FFh, 040h, 03Bh, 0C1h, 07Ch, 0EFh
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 02Ch, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 083h, 0C8h, 0FFh, 08Bh, 04Ch, 024h, 024h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh, 05Eh
    db 05Dh, 05Bh, 083h, 0C4h, 020h, 0C3h, 08Dh, 044h, 024h, 020h, 050h, 08Bh, 0CFh
    call ?j_0002f28e@@YAXXZ
    db 08Bh, 000h, 085h, 0C0h, 08Dh, 048h, 008h, 075h, 03Ch, 0B9h
    dd ?Rva006A16B0Empty@@3PADA
    db 033h, 0C0h, 003h, 0C1h, 03Bh, 0C1h, 074h, 013h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Ah, 050h
    db 0FFh, 048h, 080h, 0FAh, 05Ch, 074h, 026h, 03Bh, 0C1h, 075h, 0F3h, 0C7h, 044h, 024h, 010h, 000h
    db 000h, 000h, 000h, 08Dh, 04Ch, 024h, 020h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 00Fh, 040h, 0EBh, 03Ch, 00Fh, 0B7h, 040h, 004h, 0EBh
    db 0C5h, 089h, 044h, 024h, 010h, 0EBh, 0E0h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CFh
    call ?j_0002f28e@@YAXXZ
    db 08Bh, 000h, 085h, 0C0h, 074h, 009h, 083h, 0C0h, 008h, 089h, 044h, 024h, 010h, 0EBh, 008h, 0C7h
    db 044h, 024h, 010h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Dh, 04Ch, 024h, 020h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 044h, 024h, 010h, 050h, 08Dh, 04Ch, 024h, 014h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 010h, 052h, 08Dh, 04Ch, 024h, 020h, 0C6h, 044h, 024h, 030h, 003h
    call ?translate@UnicodeString@@QAEXABVAsciiString@@@Z
    db 08Dh, 04Ch, 024h, 010h, 0C6h, 044h, 024h, 02Ch, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 06Ah, 001h, 06Ah, 001h, 056h, 053h, 051h, 08Dh, 044h, 024h, 030h, 089h, 064h, 024h, 034h, 08Bh
    db 0CCh, 050h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 083h, 0C4h, 018h, 08Dh, 04Ch, 024h, 020h, 051h, 08Bh, 0CFh
    call ?j_00024d43@@YAXXZ
    db 033h, 0C9h, 066h, 08Bh, 08Fh, 050h, 004h, 000h, 000h, 0C6h, 044h, 024h, 02Ch, 004h, 051h, 08Bh
    db 00Dh
    dd ?TheLadderList@@3PAVLadderList@@A
    db 050h
    call ?j_000048f4@@YAXXZ
    db 08Dh, 04Ch, 024h, 020h, 089h, 044h, 024h, 010h, 0C6h, 044h, 024h, 02Ch, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 06Ah, 001h, 06Ah, 002h, 056h, 053h, 074h, 00Fh, 051h, 089h
    db 064h, 024h, 034h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 0EBh, 02Bh, 066h, 083h, 0BFh, 050h, 004h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 051h, 089h, 064h, 024h, 034h, 08Bh, 0C4h, 06Ah, 000h, 074h, 007h, 068h
    dd g_Va011184D8
    db 0EBh, 005h, 068h
    dd g_Va010FFEC0
    db 050h, 0FFh, 052h, 028h, 055h
    call ?j_0003fe86@@YAXXZ
    db 083h, 0C4h, 018h, 08Dh, 04Ch, 024h, 01Ch, 0C6h, 044h, 024h, 02Ch, 001h
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 0EBh, 040h, 06Ah, 001h, 06Ah, 001h, 056h, 053h, 051h, 089h, 064h, 024h, 034h, 08Bh, 0CCh, 068h
    dd ?BFMEEmptyString@@3QBGB
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 083h, 0C4h, 018h, 06Ah, 001h, 06Ah, 002h, 056h, 053h, 051h, 089h, 064h, 024h, 034h, 08Bh, 0CCh
    db 068h
    dd ?BFMEEmptyString@@3QBGB
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 083h, 0C4h, 018h, 08Bh, 087h, 058h, 004h, 000h, 000h, 050h, 08Bh, 087h, 054h, 004h, 000h, 000h
    db 050h, 051h, 089h, 064h, 024h, 02Ch, 08Bh, 0CCh, 068h
    dd g_Va010F9F68
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 08Dh, 04Ch, 024h, 020h, 051h
    call ?format@UnicodeString@@QAAXV1@ZZ
    db 083h, 0C4h, 010h, 06Ah, 001h, 06Ah, 003h, 056h, 053h, 051h, 08Dh, 054h, 024h, 028h, 089h, 064h
    db 024h, 034h, 08Bh, 0CCh, 052h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 08Ah, 087h, 028h, 004h, 000h, 000h, 083h, 0C4h, 018h, 084h, 0C0h, 074h, 05Fh, 068h
    dd g_Va011184CC
    db 08Dh, 04Ch, 024h, 020h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 08Dh, 044h, 024h, 01Ch, 050h, 0C6h, 044h, 024h, 030h, 005h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0C6h, 044h, 024h, 02Ch, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 054h, 024h, 020h, 085h, 0D2h, 0B8h, 00Ah, 000h, 000h, 000h, 08Bh, 0C8h, 074h, 006h, 08Bh
    db 042h, 024h, 08Bh, 04Ah, 028h, 06Ah, 0FFh, 06Ah, 001h, 051h, 050h, 06Ah, 004h, 056h, 052h, 055h
    call ?j_0001712a@@YAXXZ
    db 083h, 0C4h, 020h, 0EBh, 020h, 06Ah, 001h, 06Ah, 004h, 056h, 053h, 051h, 089h, 064h, 024h, 034h
    db 08Bh, 0CCh, 068h
    dd ?BFMEEmptyString@@3QBGB
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 083h, 0C4h, 018h, 08Ah, 087h, 029h, 004h, 000h, 000h, 084h, 0C0h, 074h, 049h, 068h
    dd g_Va0109FD6C
    db 08Dh, 04Ch, 024h, 020h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 01Ch, 051h, 08Bh, 00Dh
    dd ?TheMappedImageCollection@@3PAVImageCollection@@A
    db 0C6h, 044h, 024h, 030h, 006h
    call ?j_0001d606@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0C6h, 044h, 024h, 02Ch, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 054h, 024h, 020h, 06Ah, 0FFh, 06Ah, 001h, 06Ah, 005h, 056h, 052h, 055h
    call ?j_00035959@@YAXXZ
    db 0EBh, 01Dh, 06Ah, 001h, 06Ah, 005h, 056h, 053h, 051h, 089h, 064h, 024h, 034h, 08Bh, 0CCh, 068h
    dd ?BFMEEmptyString@@3QBGB
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 08Bh, 087h, 04Ch, 004h, 000h, 000h, 083h, 0C4h, 018h, 050h, 051h, 089h, 064h, 024h, 028h, 08Bh
    db 0CCh, 068h
    dd g_Va010F9F60
    call ??0?$StringBase@G@@AAE@PBG@Z
    db 08Dh, 044h, 024h, 01Ch, 050h
    call ?format@UnicodeString@@QAAXV1@ZZ
    db 083h, 0C4h, 00Ch, 06Ah, 001h, 06Ah, 006h, 056h, 053h, 051h, 08Dh, 054h, 024h, 028h, 089h, 064h
    db 024h, 034h, 08Bh, 0CCh, 052h
    call ??0?$StringBase@G@@AAE@ABV0@@Z
    db 055h
    call ?j_0003fe86@@YAXXZ
    db 08Bh, 087h, 04Ch, 004h, 000h, 000h, 089h, 044h, 024h, 028h, 0A1h
    dd g_Va012F713C
    db 083h, 0C4h, 018h, 085h, 0C0h, 0BFh, 00Ah, 000h, 000h, 000h, 08Bh, 0DFh, 074h, 006h, 08Bh, 078h
    db 024h, 08Bh, 058h, 028h, 08Bh, 00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfig@@A
    db 08Bh, 011h, 0FFh, 052h, 010h, 039h, 044h, 024h, 010h, 07Dh, 011h, 0A1h
    dd g_Va012F713C
    db 06Ah, 0FFh, 06Ah, 001h, 053h, 057h, 06Ah, 006h, 056h, 050h, 0EBh, 029h, 08Bh, 00Dh
    dd ?TheGameSpyConfig@@3PAVGameSpyConfig@@A
    db 08Bh, 011h, 0FFh, 052h, 014h, 039h, 044h, 024h, 010h, 06Ah, 0FFh, 06Ah, 001h, 053h, 057h, 06Ah
    db 006h, 056h, 07Dh, 008h, 0A1h
    dd g_Va012F7140
    db 050h, 0EBh, 007h, 08Bh, 00Dh
    dd g_Va012F7144
    db 051h, 055h
    call ?j_0001712a@@YAXXZ
    db 083h, 0C4h, 020h, 08Dh, 04Ch, 024h, 014h, 0C6h, 044h, 024h, 02Ch, 000h
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 044h, 024h, 02Ch, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Bh, 04Ch, 024h, 024h, 05Fh, 08Bh, 0C6h, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 05Bh, 083h, 0C4h, 020h, 0C3h
?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z ENDP
_TEXT$d00a2db90 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
