.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0Rva008A9B00@@QAE@XZ:NEAR
EXTERN ??0Rva008B2EF0@@QAE@II@Z:NEAR
EXTERN ??_7AptInteger@@6B@:BYTE
EXTERN ??_7AptValue@@6B@:BYTE
EXTERN ?IsMantissaZero@@YAHPAG@Z:NEAR
EXTERN ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA:BYTE
EXTERN ?Rva008930C0AptLookup@@YAPAVBfmeNestedBE@@H@Z:NEAR
EXTERN ?Rva00897640@@YAPAXI@Z:NEAR
EXTERN ?Rva00897FD0@@YAPBUR4Word@@PBDI@Z:NEAR
EXTERN ?Rva008A5380Holder@@3PADA:BYTE
EXTERN ?Rva008A90F0@@YAPAXI@Z:NEAR
EXTERN ?Rva008B2AE0@@YAPAXI@Z:NEAR
EXTERN ?Rva008B2B40@@YAPAXI@Z:NEAR
EXTERN ?Rva008C3B60Head@@3PAURva008C3B60Node@@A:BYTE
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva008D29C0Head@@3PAURva008D29C0Node@@A:BYTE
EXTERN ?Rva008D5DC0@@YAPBUR4Word@@PBDI@Z:NEAR
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?ShiftMantLeft1@@YAXPAG0@Z:NEAR
EXTERN ?ShiftMantRight1@@YAXPAG0@Z:NEAR
EXTERN ?StickyShiftRightMant@@YAXPAUInternalFPF@@H@Z:NEAR
EXTERN ?append@Rva008B2EA0Node@@QAEXPAX@Z:NEAR
EXTERN ?aptQueryBool@@YAPAVAptValue@@PAURva008B2E60Value@@H@Z:NEAR
EXTERN ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z:NEAR
EXTERN ?bfmeGo1030C@BfmeC1030@@QAEPAV1@XZ:NEAR
EXTERN ?bfmeGo911F@BfmeThing911F@@QAEPAV1@HPAX@Z:NEAR
EXTERN ?bfmeInsert@BfmeJ1017@@QAEXI@Z:NEAR
EXTERN ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA:BYTE
EXTERN ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z:NEAR
EXTERN ?bfmeTheCBC@@3HA:BYTE
EXTERN ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z:NEAR
EXTERN ?bfmeValue@Gen_008C41D0@@QBEHXZ:NEAR
EXTERN ?choose_nan@@YAXPAUInternalFPF@@00H@Z:NEAR
EXTERN ?d_00892a70@@YAXXZ:NEAR
EXTERN ?d_008941a0@@YAXXZ:NEAR
EXTERN ?d_00896710@@YAXXZ:NEAR
EXTERN ?d_0089cef0@@YAXXZ:NEAR
EXTERN ?d_0089d890@@YAXXZ:NEAR
EXTERN ?d_009f74f4@@YAXXZ:NEAR
EXTERN ?g_Rva01337A20@@3PAVRva00898D60Target@@A:BYTE
EXTERN ?g_Va013387D8@@3PAURva00899C20Registry@@A:BYTE
EXTERN ?g_bfme1017I@@3HA:BYTE
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?g_bfmeJ1017Cb@@3PAXA:BYTE
EXTERN ?g_bfmeJ1017Fn@@3P6AXPAXH@ZA:BYTE
EXTERN ?g_bfmeJ1017Other@@3PAXA:BYTE
EXTERN ?g_bfmeMap1024@@3PAUBfmeMap1024@@A:BYTE
EXTERN ?g_bfmeSlot06VB@@3P6AXXZA:BYTE
EXTERN ?g_bfmeTracker4310@@3PAVBfmeTracker4310@@A:BYTE
EXTERN ?g_rva008B2BD0_0@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2BD0_1@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2BD0_2@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2BD0_3@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2BD0_4@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2BD0_5@@3PAVRva008B2BD0Item@@A:BYTE
EXTERN ?g_rva008B2EA0Base@@3PAXA:BYTE
EXTERN ?ji_009f6de2@@YAXXZ:NEAR
EXTERN ?ji_009f6dee@@YAXXZ:NEAR
EXTERN ?rva00899C20@Rva00899C20Node@@QAEHXZ:NEAR
EXTERN ?rva008B2EA0Walk@@YAPAXPAVRva008B2EA0Obj@@@Z:NEAR
EXTERN ?rva008B8E10@BfmeN1242@@QAEXHPAVBfmeE1242@@@Z:NEAR
EXTERN ___security_cookie:BYTE
EXTERN g_Va00CB2DB0:NEAR
EXTERN g_Va00CB2DC0:NEAR
EXTERN g_Va00CB2DD0:NEAR
EXTERN g_Va00CB2DE0:NEAR
EXTERN g_Va01056F08:NEAR
EXTERN g_Va01058BA7:NEAR
EXTERN g_Va01135DA8:BYTE
EXTERN g_Va013377E0:BYTE
EXTERN g_Va013377E4:BYTE
EXTERN g_Va013377EC:BYTE
EXTERN g_Va013377F0:BYTE
EXTERN g_Va013379AC:BYTE
EXTERN g_Va013379B4:BYTE
EXTERN g_Va013379F0:BYTE
EXTERN g_Va013379FC:BYTE
EXTERN g_Va01337A00:BYTE
EXTERN g_Va01338760:BYTE
EXTERN g_Va01338768:BYTE
EXTERN g_Va01338778:BYTE
EXTERN g_Va01338780:BYTE
_TEXT SEGMENT

; retail @ 0x0084DE40 size 433
public ?d_0084de40@@YAXXZ
?d_0084de40@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 80h, 39h, 00h, 0B8h, 48h, 0C2h, 30h, 01h, 0Fh, 84h, 26h, 01h
    db 00h, 00h, 53h, 0B3h, 79h, 56h, 8Ah, 11h, 0Fh, 0BEh, 0F2h, 83h, 0C6h, 0DBh, 83h, 0FEh
    db 54h, 0Fh, 87h, 0FBh, 00h, 00h, 00h, 0Fh, 0B6h, 0B6h, 9Ch, 0DFh, 0C4h, 00h, 0FFh, 24h
    db 0B5h, 84h, 0DFh, 0C4h, 00h, 80h, 79h, 01h, 64h, 75h, 38h, 80h, 79h, 02h, 64h, 75h
    db 24h, 8Ah, 51h, 03h, 0C6h, 00h, 25h, 40h, 80h, 0FAh, 64h, 75h, 0Ch, 0C6h, 00h, 41h
    db 40h, 83h, 0C1h, 03h, 0E9h, 0CCh, 00h, 00h, 00h, 0C6h, 00h, 61h, 40h, 83h, 0C1h, 02h
    db 0E9h, 0C0h, 00h, 00h, 00h, 0C6h, 00h, 25h, 40h, 0C6h, 00h, 64h, 40h, 41h, 0E9h, 0B2h
    db 00h, 00h, 00h, 0C6h, 00h, 25h, 40h, 0C6h, 00h, 23h, 40h, 0C6h, 00h, 64h, 0E9h, 0A1h
    db 00h, 00h, 00h, 80h, 79h, 01h, 4Dh, 75h, 32h, 80h, 79h, 02h, 4Dh, 75h, 21h, 8Ah
    db 51h, 03h, 0C6h, 00h, 25h, 40h, 80h, 0FAh, 4Dh, 75h, 0Ch, 0C6h, 00h, 42h, 40h, 83h
    db 0C1h, 03h, 0E9h, 7Eh, 00h, 00h, 00h, 0C6h, 00h, 62h, 40h, 83h, 0C1h, 02h, 0EBh, 75h
    db 0C6h, 00h, 25h, 40h, 0C6h, 00h, 6Dh, 40h, 41h, 0EBh, 6Ah, 0C6h, 00h, 25h, 40h, 0C6h
    db 00h, 23h, 40h, 0C6h, 00h, 6Dh, 0EBh, 5Ch, 38h, 59h, 01h, 75h, 21h, 38h, 59h, 02h
    db 75h, 12h, 38h, 59h, 03h, 75h, 0Dh, 0C6h, 00h, 25h, 40h, 0C6h, 00h, 59h, 40h, 83h
    db 0C1h, 03h, 0EBh, 41h, 0C6h, 00h, 25h, 40h, 88h, 18h, 40h, 41h, 0EBh, 37h, 0C6h, 00h
    db 25h, 40h, 0C6h, 00h, 23h, 40h, 88h, 18h, 0EBh, 2Ah, 0C6h, 00h, 25h, 40h, 0C6h, 00h
    db 25h, 0EBh, 21h, 8Ah, 51h, 01h, 41h, 80h, 0FAh, 27h, 74h, 19h, 8Dh, 64h, 24h, 00h
    db 84h, 0D2h, 74h, 22h, 88h, 10h, 8Ah, 51h, 01h, 40h, 41h, 80h, 0FAh, 27h, 75h, 0F0h
    db 0EBh, 03h, 88h, 10h, 40h, 80h, 39h, 00h, 74h, 0Ch, 8Ah, 51h, 01h, 41h, 84h, 0D2h
    db 0Fh, 85h, 0E0h, 0FEh, 0FFh, 0FFh, 5Eh, 5Bh, 0C6h, 00h, 00h, 0B8h, 48h, 0C2h, 30h, 01h
    db 0C3h, 8Dh, 49h, 00h, 3Ah, 0DFh, 0C4h, 00h, 43h, 0DFh, 0C4h, 00h, 0C3h, 0DEh, 0C4h, 00h
    db 75h, 0DEh, 0C4h, 00h, 08h, 0DFh, 0C4h, 00h, 62h, 0DFh, 0C4h, 00h, 00h, 05h, 01h, 05h
    db 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h
    db 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h
    db 05h, 05h, 05h, 05h, 02h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h
    db 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 03h, 05h, 05h, 05h, 05h
    db 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h, 05h
    db 04h
?d_0084de40@@YAXXZ ENDP

; retail @ 0x00879C80 size 725
_TEXT ENDS
_TEXT$d00c79c80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C79C80 size 725
public ?d_00879c80@@YAXXZ
?d_00879c80@@YAXXZ PROC
    db 083h, 0ECh, 01Ch, 0A1h
    dd ___security_cookie
    db 089h, 044h, 024h, 018h, 00Fh, 0B6h, 007h, 053h, 08Bh, 0D9h, 00Fh, 0B6h, 00Bh, 08Dh, 004h, 080h
    db 003h, 0C1h, 083h, 0F8h, 018h, 00Fh, 087h, 025h, 002h, 000h, 000h, 00Fh, 0B6h, 090h
    dd ?d_00879c80@@YAXXZ + 02BCh
    db 0FFh, 024h, 095h
    dd ?d_00879c80@@YAXXZ + 02A0h
    db 06Ah, 00Ch, 056h, 057h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 08Ah, 043h, 001h, 08Ah, 04Eh, 001h, 083h, 0C4h, 00Ch, 032h, 0C8h, 088h, 04Eh, 001h, 0E9h, 0FAh
    db 001h, 000h, 000h, 06Ah, 00Ch, 056h, 053h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 08Ah, 04Fh, 001h, 08Ah, 046h, 001h, 083h, 0C4h, 00Ch, 032h, 0C1h, 088h, 046h, 001h, 0E9h, 0DDh
    db 001h, 000h, 000h, 0C6h, 006h, 004h, 066h, 0C7h, 046h, 002h, 0FFh, 07Fh, 0C6h, 046h, 001h, 001h
    db 066h, 0C7h, 046h, 004h, 000h, 040h, 033h, 0D2h, 089h, 056h, 006h, 066h, 089h, 056h, 00Ah, 0E9h
    db 0BCh, 001h, 000h, 000h, 06Ah, 00Ch, 056h, 057h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 0E9h, 0AAh, 001h, 000h, 000h, 06Ah, 00Ch, 056h, 053h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 0E9h, 09Bh, 001h, 000h, 000h, 06Ah, 00Ch, 08Dh, 044h, 024h, 014h, 053h, 050h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 00Fh, 0B7h, 057h, 004h, 00Fh, 0B7h, 04Fh, 008h, 00Fh, 0B7h, 047h, 006h, 00Bh, 0CAh, 00Fh, 0B7h
    db 057h, 00Ah, 00Bh, 0C8h, 083h, 0C4h, 00Ch, 00Bh, 0CAh, 089h, 04Ch, 024h, 004h, 074h, 00Ch, 08Dh
    db 043h, 004h
    call ?IsMantissaZero@@YAHPAG@Z
    db 085h, 0C0h, 074h, 015h, 0C6h, 006h, 003h, 0C6h, 046h, 001h, 000h, 066h, 0C7h, 046h, 002h, 001h
    db 080h, 033h, 0C0h, 089h, 046h, 004h, 089h, 046h, 008h, 080h, 03Fh, 001h, 074h, 00Ah, 080h, 03Bh
    db 001h, 074h, 005h, 0C6h, 006h, 002h, 0EBh, 003h, 0C6h, 006h, 001h, 08Ah, 053h, 001h, 08Ah, 04Fh
    db 001h, 032h, 0CAh, 088h, 04Eh, 001h, 066h, 08Bh, 057h, 002h, 066h, 003h, 053h, 002h, 08Dh, 05Eh
    db 004h, 066h, 089h, 056h, 002h, 033h, 0C0h, 033h, 0C9h, 08Bh, 0D3h, 089h, 044h, 024h, 008h, 089h
    db 00Ah, 055h, 089h, 044h, 024h, 010h, 089h, 04Ah, 004h, 0BDh, 040h, 000h, 000h, 000h, 08Dh, 049h
    db 000h, 08Dh, 044h, 024h, 018h, 08Dh, 04Ch, 024h, 008h, 0C7h, 044h, 024h, 008h, 000h, 000h, 000h
    db 000h
    call ?ShiftMantRight1@@YAXPAG0@Z
    db 066h, 083h, 07Ch, 024h, 008h, 000h, 074h, 05Eh, 00Fh, 0B7h, 047h, 00Ah, 00Fh, 0B7h, 04Eh, 00Ah
    db 003h, 0C1h, 00Fh, 0B7h, 04Eh, 008h, 066h, 089h, 046h, 00Ah, 00Fh, 0B7h, 057h, 008h, 0C1h, 0E8h
    db 010h, 083h, 0E0h, 001h, 003h, 0C2h, 003h, 0C1h, 00Fh, 0B7h, 04Eh, 006h, 066h, 089h, 046h, 008h
    db 00Fh, 0B7h, 057h, 006h, 0C1h, 0E8h, 010h, 083h, 0E0h, 001h, 003h, 0C2h, 003h, 0C1h, 00Fh, 0B7h
    db 04Eh, 004h, 066h, 089h, 046h, 006h, 00Fh, 0B7h, 057h, 004h, 0C1h, 0E8h, 010h, 083h, 0E0h, 001h
    db 003h, 0C2h, 003h, 0C1h, 08Bh, 0D0h, 0C1h, 0EAh, 010h, 083h, 0E2h, 001h, 089h, 054h, 024h, 008h
    db 066h, 089h, 046h, 004h, 0EBh, 008h, 0C7h, 044h, 024h, 008h, 000h, 000h, 000h, 000h, 08Bh, 0C3h
    db 08Dh, 04Ch, 024h, 008h
    call ?ShiftMantRight1@@YAXPAG0@Z
    db 08Dh, 044h, 024h, 00Ch, 08Dh, 04Ch, 024h, 008h
    call ?ShiftMantRight1@@YAXPAG0@Z
    db 04Dh, 00Fh, 085h, 05Eh, 0FFh, 0FFh, 0FFh, 0F6h, 043h, 001h, 080h, 05Dh, 075h, 02Dh, 08Dh, 0A4h
    db 024h, 000h, 000h, 000h, 000h, 08Dh, 044h, 024h, 008h, 08Dh, 04Ch, 024h, 004h, 0C7h, 044h, 024h
    db 004h, 000h, 000h, 000h, 000h
    call ?ShiftMantLeft1@@YAXPAG0@Z
    db 08Bh, 0C3h
    call ?ShiftMantLeft1@@YAXPAG0@Z
    db 066h, 0FFh, 04Eh, 002h, 0F6h, 043h, 001h, 080h, 074h, 0DAh, 00Fh, 0B7h, 04Ch, 024h, 00Ch, 00Fh
    db 0B7h, 044h, 024h, 008h, 00Fh, 0B7h, 054h, 024h, 00Ah, 00Bh, 0C1h, 00Fh, 0B7h, 04Ch, 024h, 00Eh
    db 00Bh, 0C2h, 00Bh, 0C1h, 089h, 044h, 024h, 004h, 075h, 012h, 080h, 04Eh, 00Ah, 001h, 0EBh, 00Ch
    db 06Ah, 000h, 056h, 057h
    call ?choose_nan@@YAXPAUInternalFPF@@00H@Z
    db 083h, 0C4h, 00Ch, 08Ah, 006h, 03Ch, 002h, 05Bh, 074h, 004h, 03Ch, 001h, 075h, 040h, 066h, 08Bh
    db 04Eh, 002h, 00Fh, 0BFh, 0C1h, 005h, 0FFh, 07Fh, 000h, 000h, 079h, 029h, 0F7h, 0D8h, 083h, 0F8h
    db 040h, 07Ch, 013h, 0C6h, 006h, 000h, 066h, 0C7h, 046h, 002h, 001h, 080h, 033h, 0D2h, 089h, 056h
    db 004h, 089h, 056h, 008h, 0EBh, 00Fh, 003h, 0C8h, 066h, 089h, 04Eh, 002h, 08Bh, 0D0h, 08Bh, 0CEh
    call ?StickyShiftRightMant@@YAXPAUInternalFPF@@H@Z
    db 080h, 03Eh, 000h, 074h, 004h, 080h, 066h, 00Ah, 0F8h, 08Bh, 04Ch, 024h, 018h
    call ?d_009f74f4@@YAXXZ
    db 083h, 0C4h, 01Ch, 0C3h
    dd ?d_00879c80@@YAXXZ + 031h
    dd ?d_00879c80@@YAXXZ + 06Bh
    dd ?d_00879c80@@YAXXZ + 09Bh
    dd ?d_00879c80@@YAXXZ + 04Eh
    dd ?d_00879c80@@YAXXZ + 0AAh
    dd ?d_00879c80@@YAXXZ + 08Ch
    dd ?d_00879c80@@YAXXZ + 023Ch
    db 000h, 000h, 000h, 001h, 002h, 003h, 004h, 004h, 003h, 002h, 003h, 004h, 004h, 003h, 002h, 001h
    db 000h, 000h, 000h, 002h, 005h, 005h, 005h, 005h, 006h
?d_00879c80@@YAXXZ ENDP
_TEXT$d00c79c80 ENDS
_TEXT SEGMENT

; retail @ 0x00894380 size 728
_TEXT ENDS
_TEXT$d00c94380 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C94380 size 728
public ?d_00894380@@YAXXZ
?d_00894380@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01056F08
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 030h, 053h, 057h, 08Bh, 03Dh
    dd g_Va013377EC
    db 08Dh, 047h, 001h, 089h, 044h, 024h, 00Ch, 0A1h
    dd ?g_bfme1017I@@3HA
    db 033h, 0DBh, 03Bh, 0C3h, 00Fh, 084h, 080h, 002h, 000h, 000h, 055h, 083h, 0CDh, 0FFh, 056h, 0EBh
    db 003h, 08Dh, 049h, 000h, 03Bh, 07Ch, 024h, 014h, 00Fh, 084h, 06Ah, 002h, 000h, 000h, 08Bh, 035h
    dd g_Va013377F0
    db 08Bh, 04Eh, 008h, 08Bh, 016h, 0C1h, 0E2h, 003h, 08Bh, 0C1h, 003h, 0C2h, 03Bh, 0C8h, 074h, 01Dh
    db 08Bh, 041h, 004h, 083h, 0F8h, 004h, 074h, 009h, 083h, 0F8h, 002h, 00Fh, 085h, 008h, 001h, 000h
    db 000h, 08Bh, 046h, 008h, 083h, 0C1h, 008h, 003h, 0C2h, 03Bh, 0C8h, 075h, 0E3h, 08Bh, 00Dh
    dd g_Va013377E0
    db 039h, 039h, 00Fh, 087h, 0F4h, 000h, 000h, 000h, 0EBh, 003h, 08Dh, 049h, 000h, 083h, 0C1h, 004h
    db 033h, 0C0h, 089h, 00Dh
    dd g_Va013377E0
    db 08Ah, 001h, 083h, 0E0h, 003h, 083h, 0F8h, 003h, 00Fh, 087h, 0C0h, 000h, 000h, 000h, 0FFh, 024h
    db 085h
    dd ?d_00894380@@YAXXZ + 02C8h
    db 08Bh, 001h, 083h, 0C1h, 004h, 089h, 00Dh
    dd g_Va013377E0
    db 08Bh, 00Dh
    dd ?Rva008A5380Holder@@3PADA
    db 050h
    call ?bfmeInsert@BfmeJ1017@@QAEXI@Z
    db 0E9h, 091h, 000h, 000h, 000h, 041h, 08Bh, 0F1h, 08Bh, 0C6h, 089h, 00Dh
    dd g_Va013377E0
    db 08Dh, 078h, 001h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Ah, 010h, 040h, 03Ah, 0D3h, 075h, 0F9h
    db 02Bh, 0C7h, 08Dh, 04Ch, 001h, 001h, 089h, 00Dh
    dd g_Va013377E0
    db 056h, 08Dh, 04Ch, 024h, 014h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 00Dh
    dd g_Va013377F0
    db 08Dh, 054h, 024h, 010h, 052h, 089h, 05Ch, 024h, 04Ch
    call ?d_008941a0@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 066h, 0FFh, 008h, 066h, 039h, 018h, 089h, 06Ch, 024h, 048h, 075h, 03Ch
    db 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 0EBh, 02Eh, 0A1h
    dd ?g_bfmeJ1017Cb@@3PAXA
    db 041h, 03Bh, 0C3h, 089h, 00Dh
    dd g_Va013377E0
    db 075h, 02Ah, 057h, 08Dh, 04Ch, 024h, 024h, 068h
    dd g_Va01135DA8
    db 051h
    call ?ji_009f6de2@@YAXXZ
    db 08Dh, 054h, 024h, 02Ch, 052h, 0FFh, 015h
    dd ?g_bfmeSlot06VB@@3P6AXXZA
    db 083h, 0C4h, 010h, 08Bh, 00Dh
    dd g_Va013377E0
    db 08Bh, 035h
    dd g_Va013377F0
    db 08Bh, 03Dh
    dd g_Va013377EC
    db 039h, 039h, 00Fh, 086h, 019h, 0FFh, 0FFh, 0FFh, 0EBh, 006h, 08Bh, 00Dh
    dd g_Va013377E0
    db 08Bh, 015h
    dd ?g_bfme1017I@@3HA
    db 0A1h
    dd g_Va013377E4
    db 02Bh, 0CAh, 03Bh, 0C8h, 00Fh, 08Dh, 0E8h, 000h, 000h, 000h, 08Bh, 046h, 008h, 08Bh, 016h, 0C1h
    db 0E2h, 003h, 08Bh, 0C8h, 003h, 0CAh, 03Bh, 0C1h, 074h, 01Dh, 08Bh, 048h, 004h, 083h, 0F9h, 004h
    db 074h, 009h, 083h, 0F9h, 002h, 00Fh, 085h, 0F4h, 000h, 000h, 000h, 08Bh, 04Eh, 008h, 083h, 0C0h
    db 008h, 003h, 0CAh, 03Bh, 0C1h, 075h, 0E3h, 08Bh, 015h
    dd ?Rva008A5380Holder@@3PADA
    db 08Bh, 082h, 02Ch, 012h, 000h, 000h, 08Bh, 008h, 08Bh, 041h, 058h, 03Bh, 0C3h, 00Fh, 084h, 0CFh
    db 000h, 000h, 000h, 08Bh, 040h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h, 0FAh, 012h, 00Fh, 085h
    db 0BEh, 000h, 000h, 000h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 00Fh, 085h, 0B1h, 000h, 000h
    db 000h, 0B8h, 001h, 000h, 000h, 000h
    call ?d_00892a70@@YAXXZ
    db 085h, 0C0h, 074h, 049h, 039h, 01Dh
    dd ?g_bfmeJ1017Cb@@3PAXA
    db 074h, 041h, 0A1h
    dd ?g_bfmeJ1017Other@@3PAXA
    db 050h, 08Dh, 04Ch, 024h, 034h, 068h
    dd g_Va01135DA8
    db 051h
    call ?ji_009f6de2@@YAXXZ
    db 08Dh, 054h, 024h, 03Ch, 052h, 0FFh, 015h
    dd ?g_bfmeSlot06VB@@3P6AXXZA
    db 0A1h
    dd ?g_bfmeJ1017Other@@3PAXA
    db 08Dh, 04Ch, 024h, 028h, 06Ah, 005h, 051h, 089h, 044h, 024h, 030h, 0C7h, 044h, 024h, 034h, 003h
    db 000h, 000h, 000h, 0FFh, 015h
    dd ?g_bfmeJ1017Fn@@3P6AXPAXH@ZA
    db 083h, 0C4h, 018h, 08Bh, 03Dh
    dd g_Va013377EC
    db 0A1h
    dd ?g_bfme1017I@@3HA
    db 047h, 03Bh, 0C3h, 089h, 03Dh
    dd g_Va013377EC
    db 00Fh, 085h, 0D7h, 0FDh, 0FFh, 0FFh, 05Eh, 05Dh, 05Fh, 05Bh, 08Bh, 04Ch, 024h, 030h, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 03Ch, 0C3h, 039h, 01Dh
    dd ?g_bfmeJ1017Cb@@3PAXA
    db 089h, 01Dh
    dd ?g_bfme1017I@@3HA
    db 089h, 01Dh
    dd g_Va013377E0
    db 074h, 024h, 05Eh, 05Dh, 05Fh, 089h, 01Dh
    dd ?g_bfmeJ1017Cb@@3PAXA
    db 05Bh, 08Bh, 04Ch, 024h, 030h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 03Ch, 0C3h
    db 08Bh, 00Dh
    dd ?g_bfmeTracker4310@@3PAVBfmeTracker4310@@A
    call ?d_00896710@@YAXXZ
    db 05Eh, 05Dh, 08Bh, 04Ch, 024h, 038h, 05Fh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 03Ch, 0C3h, 090h
    dd ?d_00894380@@YAXXZ + 0B0h
    dd ?d_00894380@@YAXXZ + 0B0h
    dd ?d_00894380@@YAXXZ + 0CCh
    dd ?d_00894380@@YAXXZ + 012Fh
?d_00894380@@YAXXZ ENDP
_TEXT$d00c94380 ENDS
_TEXT SEGMENT

; retail @ 0x0089C290 size 929
_TEXT ENDS
_TEXT$d00c9c290 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9C290 size 929
public ?d_0089c290@@YAXXZ
?d_0089c290@@YAXXZ PROC
    db 053h, 055h, 056h, 057h, 08Bh, 07Ch, 024h, 018h, 085h, 0FFh, 08Bh, 0E9h, 075h, 002h, 08Bh, 0FDh
    db 08Bh, 05Ch, 024h, 014h, 08Bh, 033h, 00Fh, 0B7h, 046h, 002h, 050h, 08Dh, 04Eh, 008h, 051h
    call ?Rva00897FD0@@YAPBUR4Word@@PBDI@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 085h, 002h, 000h, 000h, 08Bh, 040h, 004h, 048h, 083h
    db 0F8h, 024h, 00Fh, 087h, 056h, 002h, 000h, 000h, 00Fh, 0B6h, 090h
    dd ?d_0089c290@@YAXXZ + 037Ch
    db 0FFh, 024h, 095h
    dd ?d_0089c290@@YAXXZ + 0348h
    db 0A1h
    dd g_Va01338780
    db 08Bh, 00Dh
    dd g_Va01338778
    db 08Bh, 07Ch, 088h, 0FCh, 03Bh, 0FDh, 075h, 009h, 05Fh, 05Eh, 08Bh, 0C5h, 05Dh, 05Bh, 0C2h, 008h
    db 000h, 0A1h
    dd g_Va01338760
    db 085h, 0C0h, 07Eh, 046h, 08Bh, 015h
    dd g_Va01338768
    db 08Bh, 074h, 082h, 0FCh, 08Bh, 046h, 004h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 030h
    db 03Bh, 0FEh, 075h, 009h, 08Bh, 0C7h, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 08Bh, 016h, 08Bh
    db 0CEh, 0FFh, 052h, 018h, 085h, 0C0h, 074h, 018h, 08Dh, 049h, 000h, 08Bh, 048h, 008h, 083h, 0E1h
    db 0FEh, 074h, 00Dh, 03Bh, 0CFh, 074h, 041h, 08Bh, 001h, 0FFh, 050h, 018h, 085h, 0C0h, 075h, 0EBh
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 018h, 085h, 0C0h, 074h, 015h, 08Bh, 048h, 008h, 083h
    db 0E1h, 0FEh, 074h, 00Dh, 03Bh, 0CFh, 074h, 090h, 08Bh, 001h, 0FFh, 050h, 018h, 085h, 0C0h, 075h
    db 0EBh, 08Bh, 00Dh
    dd g_Va01338780
    db 08Bh, 015h
    dd g_Va01338778
    db 08Bh, 044h, 091h, 0FCh, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 05Fh, 08Bh, 0C6h, 05Eh, 05Dh
    db 05Bh, 0C2h, 008h, 000h, 08Bh, 04Fh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 00Fh
    db 08Ch, 08Bh, 001h, 000h, 000h, 083h, 0F8h, 013h, 00Fh, 08Fh, 082h, 001h, 000h, 000h, 0C1h, 0E9h
    db 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 00Fh, 085h, 074h, 001h, 000h, 000h, 08Bh, 04Fh, 04Ch, 085h
    db 0C9h, 08Bh, 0C7h, 00Fh, 084h, 016h, 002h, 000h, 000h, 0EBh, 003h, 08Dh, 049h, 000h, 08Bh, 0C1h
    db 08Bh, 048h, 04Ch, 085h, 0C9h, 075h, 0F7h, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd g_Va013379FC
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd g_Va013379AC
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd g_Va013379B4
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd g_Va013379F0
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd g_Va01337A00
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 0A1h
    dd ?g_Rva01337A20@@3PAVRva00898D60Target@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 08Bh, 00Dh
    dd g_Va01338778
    db 0A1h
    dd g_Va01338780
    db 08Bh, 07Ch, 088h, 0FCh, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 018h, 085h, 0C0h, 00Fh, 084h, 0AEh
    db 000h, 000h, 000h, 08Bh, 070h, 008h, 083h, 0E6h, 0FEh, 00Fh, 084h, 0A2h, 000h, 000h, 000h, 03Bh
    db 0FDh, 074h, 06Ah, 08Bh, 0CFh
    call ?rva00899C20@Rva00899C20Node@@QAEHXZ
    db 085h, 0C0h, 074h, 05Fh, 08Bh, 04Fh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch
    db 011h, 083h, 0F8h, 013h, 07Fh, 00Ch, 08Bh, 0D1h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h
    db 074h, 041h, 083h, 0F8h, 01Bh, 00Fh, 085h, 0F9h, 0FEh, 0FFh, 0FFh, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h
    db 0F6h, 0C1h, 001h, 00Fh, 085h, 0EBh, 0FEh, 0FFh, 0FFh, 08Bh, 047h, 01Ch, 0F6h, 0C4h, 002h, 00Fh
    db 084h, 0DFh, 0FEh, 0FFh, 0FFh, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 018h, 085h, 0C0h, 00Fh, 084h
    db 0D0h, 0FEh, 0FFh, 0FFh, 08Bh, 070h, 008h, 083h, 0E6h, 0FEh, 05Fh, 08Bh, 0C6h, 05Eh, 05Dh, 05Bh
    db 0C2h, 008h, 000h, 08Bh, 07Fh, 004h, 08Bh, 0CFh, 083h, 0E1h, 03Fh, 080h, 0F9h, 01Ch, 075h, 010h
    db 08Bh, 0D7h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 00Fh, 084h, 0A4h, 0FEh, 0FFh, 0FFh
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 018h, 085h, 0C0h, 074h, 00Ch, 08Bh, 040h, 008h, 083h, 0E0h
    db 0FEh, 00Fh, 085h, 0E1h, 000h, 000h, 000h, 0A1h
    dd ?bfmeTheCBC@@3HA
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 08Bh, 04Fh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h
    db 0F8h, 00Ch, 07Ch, 019h, 083h, 0F8h, 013h, 07Fh, 014h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h
    db 001h, 075h, 00Ah, 08Bh, 047h, 04Ch, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 05Fh, 05Eh, 05Dh
    db 033h, 0C0h, 05Bh, 0C2h, 008h, 000h, 083h, 0C6h, 00Eh, 056h
    call ?ji_009f6dee@@YAXXZ
    db 050h
    call ?Rva008930C0AptLookup@@YAPAVBfmeNestedBE@@H@Z
    db 083h, 0C4h, 008h, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h, 08Bh, 04Fh, 004h, 0C1h, 0E9h, 00Fh
    db 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 0D1h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 018h, 08Bh, 0F0h
    db 085h, 0F6h, 075h, 032h, 08Bh, 04Fh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch
    db 044h, 083h, 0F8h, 013h, 07Fh, 03Fh, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 035h
    db 083h, 0F8h, 00Eh, 075h, 030h, 08Bh, 04Fh, 04Ch
    call ?bfmeValue@Gen_008C41D0@@QBEHXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 022h, 08Dh, 049h, 000h, 053h, 08Bh, 0CEh
    call ?d_0089cef0@@YAXXZ
    db 085h, 0C0h, 075h, 035h, 08Bh, 04Eh, 008h, 083h, 0E1h, 0FEh, 074h, 00Bh, 08Bh, 001h, 0FFh, 050h
    db 018h, 08Bh, 0F0h, 085h, 0F6h, 075h, 0E1h, 08Bh, 00Dh
    dd ?g_bfmeMap1024@@3PAUBfmeMap1024@@A
    db 053h, 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 085h, 0C0h, 075h, 00Fh, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 053h, 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 008h, 000h
    dd ?d_0089c290@@YAXXZ + 0292h
    dd ?d_0089c290@@YAXXZ + 04Ah
    dd ?d_0089c290@@YAXXZ + 0F6h
    dd ?d_0089c290@@YAXXZ + 014Ch
    dd ?d_0089c290@@YAXXZ + 0164h
    dd ?d_0089c290@@YAXXZ + 029Bh
    dd ?d_0089c290@@YAXXZ + 026Ch
    dd ?d_0089c290@@YAXXZ + 0188h
    dd ?d_0089c290@@YAXXZ + 0194h
    dd ?d_0089c290@@YAXXZ + 0140h
    dd ?d_0089c290@@YAXXZ + 0158h
    dd ?d_0089c290@@YAXXZ + 0170h
    dd ?d_0089c290@@YAXXZ + 017Ch
    db 000h, 001h, 002h, 003h, 004h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 006h
    db 007h, 008h, 009h, 00Ah, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h, 005h
    db 005h, 005h, 005h, 00Bh, 00Ch
?d_0089c290@@YAXXZ ENDP
_TEXT$d00c9c290 ENDS
_TEXT SEGMENT

; retail @ 0x008A73E0 size 1252
public ?d_008a73e0@@YAXXZ
?d_008a73e0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 09h, 81h, 05h, 01h, 50h, 8Bh, 44h
    db 24h, 10h, 85h, 0C0h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 53h, 56h, 57h, 8Bh, 0F1h
    db 0Fh, 84h, 88h, 04h, 00h, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 00h, 0Fh, 0B7h, 48h, 02h
    db 51h, 83h, 0C0h, 08h, 50h, 0E8h, 86h, 0D0h, 0FFh, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 0Fh
    db 84h, 69h, 04h, 00h, 00h, 8Bh, 40h, 04h, 48h, 83h, 0F8h, 07h, 0Fh, 87h, 5Ch, 04h
    db 00h, 00h, 0FFh, 24h, 85h, 0A4h, 78h, 0CAh, 00h, 0A1h, 0A4h, 7Ah, 33h, 01h, 85h, 0C0h
    db 75h, 50h, 6Ah, 24h, 0E8h, 0F7h, 01h, 0FFh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch
    db 85h, 0C0h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h, 0Eh, 68h, 60h, 55h, 0CAh
    db 00h, 8Bh, 0C8h, 0E8h, 58h, 2Bh, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0A4h, 7Ah, 33h
    db 01h, 8Bh, 50h, 04h, 81h, 0E2h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0CAh, 40h, 89h, 50h, 04h
    db 8Bh, 0Dh, 0A4h, 7Ah, 33h, 01h, 8Bh, 01h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0FFh, 10h, 0A1h, 0A4h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0A8h, 7Ah, 33h, 01h
    db 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 85h, 01h, 0FFh, 0FFh, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 0Eh, 68h, 0C0h
    db 58h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 0E6h, 2Ah, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0A8h
    db 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h
    db 48h, 04h, 8Bh, 0Dh, 0A8h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0A8h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0ACh, 7Ah
    db 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 13h, 01h, 0FFh, 0FFh, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 02h, 00h, 00h, 00h, 74h, 0Eh
    db 68h, 0F0h, 5Bh, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 74h, 2Ah, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h
    db 0A3h, 0ACh, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h
    db 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0ACh, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0ACh, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h
    db 0B0h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0A1h, 00h, 0FFh, 0FFh, 83h
    db 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 03h, 00h, 00h, 00h
    db 74h, 0Eh, 68h, 0A0h, 60h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 02h, 2Ah, 0FFh, 0FFh, 0EBh, 02h
    db 33h, 0C0h, 0A3h, 0B0h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh
    db 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0B0h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h
    db 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0B0h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h
    db 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h
    db 00h, 0A1h, 0B4h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 2Fh, 00h, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 04h, 00h
    db 00h, 00h, 74h, 0Eh, 68h, 0D0h, 60h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 90h, 29h, 0FFh, 0FFh
    db 0EBh, 02h, 33h, 0C0h, 0A3h, 0B4h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h
    db 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0B4h, 7Ah, 33h, 01h, 8Bh, 11h
    db 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0B4h, 7Ah, 33h, 01h, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch
    db 0C2h, 08h, 00h, 8Bh, 56h, 20h, 0A1h, 0D4h, 87h, 33h, 01h, 85h, 0D2h, 0Fh, 95h, 0C3h
    db 85h, 0C0h, 74h, 56h, 8Bh, 48h, 08h, 8Bh, 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0D4h
    db 87h, 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Eh, 81h, 60h, 04h
    db 0FFh, 0FFh, 0FFh, 0BFh, 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 52h, 08h, 89h, 04h
    db 0B2h, 0FFh, 01h, 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h
    db 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 0A1h, 01h, 00h, 00h, 8Bh, 48h, 04h
    db 81h, 0E1h, 05h, 80h, 00h, 0F0h, 81h, 0C9h, 05h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh
    db 13h, 01h, 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 3Bh, 3Eh
    db 8Dh, 56h, 04h, 7Ch, 26h, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 48h, 04h, 0C7h, 00h
    db 0A8h, 60h, 13h, 01h, 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Eh, 08h, 89h, 04h
    db 0B9h, 0FFh, 02h, 0C7h, 00h, 0A8h, 60h, 13h, 01h, 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0A1h, 0B8h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0D0h, 0FEh, 0FEh, 0FFh
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 05h, 00h, 00h
    db 00h, 74h, 0Eh, 68h, 00h, 61h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 31h, 28h, 0FFh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0A3h, 0B8h, 7Ah, 33h, 01h, 8Bh, 50h, 04h, 81h, 0E2h, 7Fh, 0C0h, 0FFh
    db 0FFh, 83h, 0CAh, 40h, 89h, 50h, 04h, 8Bh, 0Dh, 0B8h, 7Ah, 33h, 01h, 8Bh, 01h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 10h, 0A1h, 0B8h, 7Ah, 33h, 01h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 8Bh, 35h, 78h, 84h, 33h, 01h, 85h, 0F6h, 74h, 60h, 8Bh, 4Eh, 0Ch, 89h
    db 0Dh, 78h, 84h, 33h, 01h, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 8Bh, 51h, 04h, 3Bh, 11h
    db 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 08h, 8Bh, 49h
    db 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h, 08h, 3Dh, 98h, 52h, 2Dh, 01h, 8Dh, 4Eh
    db 08h, 74h, 59h, 6Ah, 00h, 0E8h, 36h, 74h, 0FFh, 0FFh, 68h, 0E4h, 28h, 13h, 01h, 8Bh
    db 0CEh, 0E8h, 9Ah, 0AFh, 0FEh, 0FFh, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 6Ah, 10h, 0FFh, 15h
    db 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h
    db 14h, 06h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0A2h, 22h, 00h, 00h, 0EBh, 02h
    db 33h, 0C0h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0F0h, 68h, 0E4h, 28h, 13h
    db 01h, 8Bh, 0CEh, 0E8h, 48h, 0AFh, 0FEh, 0FFh, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Ch
    db 24h, 0Ch, 5Fh, 5Eh, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 08h, 00h, 39h, 74h, 0CAh, 00h, 0ABh, 74h, 0CAh, 00h, 1Dh, 75h, 0CAh, 00h
    db 8Fh, 75h, 0CAh, 00h, 01h, 76h, 0CAh, 00h, 73h, 76h, 0CAh, 00h, 60h, 77h, 0CAh, 00h
    db 0D2h, 77h, 0CAh, 00h
?d_008a73e0@@YAXXZ ENDP

; retail @ 0x008AB0E0 size 1788
public ?d_008ab0e0@@YAXXZ
?d_008ab0e0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 8Ch, 84h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 56h, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 57h, 0Fh, 84h
    db 8Eh, 06h, 00h, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 00h, 0Fh, 0B7h, 48h, 02h, 51h, 83h
    db 0C0h, 08h, 50h, 0E8h, 0F8h, 0E5h, 0FFh, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 0Fh, 84h, 6Fh
    db 06h, 00h, 00h, 8Bh, 40h, 04h, 48h, 83h, 0F8h, 0Ch, 0Fh, 87h, 62h, 06h, 00h, 00h
    db 0FFh, 24h, 85h, 0A8h, 0B7h, 0CAh, 00h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h
    db 24h, 1Ch, 98h, 52h, 2Dh, 01h, 8Dh, 54h, 24h, 1Ch, 52h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 18h, 00h, 00h, 00h, 00h, 0E8h, 66h, 0D4h, 0FEh, 0FFh, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 0BDh
    db 48h, 0FFh, 0FFh, 8Bh, 0D8h, 0A1h, 0D0h, 87h, 33h, 01h, 85h, 0C0h, 74h, 32h, 8Bh, 48h
    db 08h, 8Bh, 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0D0h, 87h, 33h, 01h, 8Bh, 72h, 04h
    db 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 0Ch, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 58h
    db 08h, 0EBh, 6Dh, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh, 01h, 89h, 58h, 08h, 0EBh, 60h
    db 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 4Fh, 8Bh
    db 48h, 04h, 81h, 0E1h, 07h, 80h, 00h, 0F0h, 81h, 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h
    db 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h
    db 3Bh, 3Eh, 8Dh, 56h, 04h, 7Ch, 14h, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 48h, 04h
    db 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 58h, 08h, 0EBh, 15h, 8Bh, 4Eh, 08h, 89h, 04h
    db 0B9h, 0FFh, 02h, 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 58h, 08h, 0EBh, 02h, 33h, 0C0h
    db 8Bh, 0F0h, 8Bh, 44h, 24h, 1Ch, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 52h
    db 04h, 83h, 0C4h, 04h, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0C8h, 7Ah, 33h, 01h, 85h
    db 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0F6h, 0C3h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 0Eh, 68h, 20h, 9Eh
    db 0CAh, 00h, 8Bh, 0C8h, 0E8h, 57h, 0EDh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0C8h, 7Ah
    db 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h
    db 04h, 8Bh, 0Dh, 0C8h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 12h, 0A1h, 0C8h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0CCh, 7Ah, 33h
    db 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 84h, 0C3h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 02h, 00h, 00h, 00h, 74h, 0Eh, 68h
    db 70h, 9Fh, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 0E5h, 0ECh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h
    db 0CCh, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h
    db 89h, 48h, 04h, 8Bh, 0Dh, 0CCh, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0CCh, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0D0h
    db 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 12h, 0C3h, 0FEh, 0FFh, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 03h, 00h, 00h, 00h, 74h
    db 0Eh, 68h, 30h, 0A1h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 73h, 0ECh, 0FEh, 0FFh, 0EBh, 02h, 33h
    db 0C0h, 0A3h, 0D0h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h
    db 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0D0h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0D0h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0A1h, 0D4h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0A0h, 0C2h, 0FEh, 0FFh
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 04h, 00h, 00h
    db 00h, 74h, 0Eh, 68h, 0B0h, 0A2h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 01h, 0ECh, 0FEh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0A3h, 0D4h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh
    db 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0D4h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0D4h, 7Ah, 33h, 01h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 0A1h, 0D8h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 2Eh, 0C2h
    db 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 05h
    db 00h, 00h, 00h, 74h, 0Eh, 68h, 30h, 9Ch, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 8Fh, 0EBh, 0FEh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0D8h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh
    db 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0D8h, 7Ah, 33h, 01h, 8Bh
    db 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0D8h, 7Ah, 33h, 01h
    db 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 08h, 00h, 0A1h, 0DCh, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h
    db 0BCh, 0C1h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h
    db 14h, 06h, 00h, 00h, 00h, 74h, 0Eh, 68h, 0C0h, 99h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 1Dh
    db 0EBh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0DCh, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h
    db 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0DCh, 7Ah, 33h
    db 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0DCh, 7Ah
    db 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0E0h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah
    db 24h, 0E8h, 4Ah, 0C1h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h
    db 44h, 24h, 14h, 07h, 00h, 00h, 00h, 74h, 0Eh, 68h, 20h, 0A4h, 0CAh, 00h, 8Bh, 0C8h
    db 0E8h, 0ABh, 0EAh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0E0h, 7Ah, 33h, 01h, 8Bh, 48h
    db 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0E0h
    db 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h
    db 0E0h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh
    db 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0E4h, 7Ah, 33h, 01h, 85h, 0C0h, 75h
    db 50h, 6Ah, 24h, 0E8h, 0D8h, 0C0h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h
    db 0C0h, 0C7h, 44h, 24h, 14h, 08h, 00h, 00h, 00h, 74h, 0Eh, 68h, 50h, 0A6h, 0CAh, 00h
    db 8Bh, 0C8h, 0E8h, 39h, 0EAh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0E4h, 7Ah, 33h, 01h
    db 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh
    db 0Dh, 0E4h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
    db 12h, 0A1h, 0E4h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0E8h, 7Ah, 33h, 01h, 85h
    db 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 66h, 0C0h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 09h, 00h, 00h, 00h, 74h, 0Eh, 68h, 20h, 0ABh
    db 0CAh, 00h, 8Bh, 0C8h, 0E8h, 0C7h, 0E9h, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0E8h, 7Ah
    db 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h
    db 04h, 8Bh, 0Dh, 0E8h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 12h, 0A1h, 0E8h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0ECh, 7Ah, 33h
    db 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0F4h, 0BFh, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 0Ah, 00h, 00h, 00h, 74h, 0Eh, 68h
    db 0F0h, 0ACh, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 55h, 0E9h, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h
    db 0ECh, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h
    db 89h, 48h, 04h, 8Bh, 0Dh, 0ECh, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0ECh, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 0F0h
    db 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 82h, 0BFh, 0FEh, 0FFh, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 0Bh, 00h, 00h, 00h, 74h
    db 0Eh, 68h, 0C0h, 0AEh, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 0E3h, 0E8h, 0FEh, 0FFh, 0EBh, 02h, 33h
    db 0C0h, 0A3h, 0F0h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h
    db 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0F0h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0F0h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0A1h, 0F4h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 10h, 0BFh, 0FEh, 0FFh
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 0Ch, 00h, 00h
    db 00h, 74h, 0Eh, 68h, 0D0h, 0AFh, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 71h, 0E8h, 0FEh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0A3h, 0F4h, 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh
    db 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 0F4h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0F4h, 7Ah, 33h, 01h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 37h, 0B1h, 0CAh, 00h, 3Ah, 0B2h, 0CAh, 00h
    db 0ACh, 0B2h, 0CAh, 00h, 1Eh, 0B3h, 0CAh, 00h, 90h, 0B3h, 0CAh, 00h, 02h, 0B4h, 0CAh, 00h
    db 74h, 0B4h, 0CAh, 00h, 0E6h, 0B4h, 0CAh, 00h, 58h, 0B5h, 0CAh, 00h, 0CAh, 0B5h, 0CAh, 00h
    db 3Ch, 0B6h, 0CAh, 00h, 0AEh, 0B6h, 0CAh, 00h, 20h, 0B7h, 0CAh, 00h
?d_008ab0e0@@YAXXZ ENDP

; retail @ 0x008AC190 size 716
public ?d_008ac190@@YAXXZ
?d_008ac190@@YAXXZ PROC
    db 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 18h, 33h, 0EDh, 3Dh, 0FFh, 0FFh, 0Fh, 00h, 73h, 05h
    db 5Eh, 33h, 0C0h, 5Dh, 0C3h, 8Bh, 0Eh, 49h, 83h, 0F9h, 0Bh, 57h, 0Fh, 87h, 71h, 02h
    db 00h, 00h, 0FFh, 24h, 8Dh, 2Ch, 0C4h, 0CAh, 00h, 8Bh, 46h, 08h, 3Dh, 00h, 00h, 01h
    db 00h, 0Fh, 82h, 5Ch, 02h, 00h, 00h, 0A8h, 03h, 0Fh, 85h, 54h, 02h, 00h, 00h, 8Bh
    db 46h, 0Ch, 3Dh, 00h, 00h, 01h, 00h, 0Fh, 8Fh, 46h, 02h, 00h, 00h, 33h, 0FFh, 85h
    db 0C0h, 0Fh, 8Eh, 36h, 02h, 00h, 00h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 10h, 8Bh, 0Ch, 0B8h, 81h, 0F9h, 00h, 00h, 01h, 00h, 0Fh, 82h, 21h, 02h
    db 00h, 00h, 0F6h, 46h, 08h, 03h, 0Fh, 85h, 17h, 02h, 00h, 00h, 0E8h, 7Fh, 0FFh, 0FFh
    db 0FFh, 03h, 0E8h, 8Bh, 46h, 0Ch, 47h, 3Bh, 0F8h, 7Ch, 0D5h, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh
    db 0C3h, 0D9h, 46h, 18h, 0D8h, 1Dh, 38h, 69h, 13h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh
    db 84h, 0EEh, 01h, 00h, 00h, 0D9h, 46h, 0Ch, 0D8h, 1Dh, 38h, 69h, 13h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 0Fh, 84h, 0DAh, 01h, 00h, 00h, 0D9h, 46h, 18h, 0D8h, 1Dh, 38h, 69h
    db 13h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 84h, 0C6h, 01h, 00h, 00h, 0D9h, 46h, 14h
    db 0D8h, 1Dh, 38h, 69h, 13h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 84h, 0B2h, 01h, 00h
    db 00h, 8Bh, 46h, 1Ch, 3Dh, 00h, 00h, 02h, 00h, 0Fh, 8Fh, 0A4h, 01h, 00h, 00h, 39h
    db 46h, 20h, 0Fh, 8Ch, 9Bh, 01h, 00h, 00h, 0F6h, 46h, 24h, 03h, 0Fh, 85h, 91h, 01h
    db 00h, 00h, 8Bh, 46h, 2Ch, 3Dh, 00h, 00h, 01h, 00h, 0Fh, 8Fh, 83h, 01h, 00h, 00h
    db 81h, 7Eh, 34h, 00h, 10h, 00h, 00h, 0Fh, 8Fh, 76h, 01h, 00h, 00h, 53h, 33h, 0DBh
    db 85h, 0C0h, 7Eh, 1Fh, 33h, 0FFh, 8Bh, 4Eh, 30h, 8Bh, 4Ch, 39h, 04h, 85h, 0C9h, 74h
    db 07h, 0E8h, 0CAh, 0FEh, 0FFh, 0FFh, 03h, 0E8h, 8Bh, 46h, 2Ch, 43h, 83h, 0C7h, 44h, 3Bh
    db 0D8h, 7Ch, 0E3h, 8Bh, 46h, 3Ch, 85h, 0C0h, 5Bh, 0Fh, 84h, 3Eh, 01h, 00h, 00h, 8Bh
    db 00h, 85h, 0C0h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0A4h, 0FEh, 0FFh, 0FFh, 03h, 0E8h, 8Bh, 56h
    db 3Ch, 8Bh, 4Ah, 04h, 85h, 0C9h, 74h, 07h, 0E8h, 93h, 0FEh, 0FFh, 0FFh, 03h, 0E8h, 8Bh
    db 46h, 3Ch, 8Bh, 48h, 08h, 85h, 0C9h, 74h, 07h, 0E8h, 82h, 0FEh, 0FFh, 0FFh, 03h, 0E8h
    db 8Bh, 4Eh, 3Ch, 8Bh, 49h, 0Ch, 85h, 0C9h, 0Fh, 84h, 0FFh, 00h, 00h, 00h, 0E8h, 6Dh
    db 0FEh, 0FFh, 0FFh, 5Fh, 03h, 0E8h, 5Eh, 8Bh, 0C5h, 5Dh, 0C3h, 8Bh, 46h, 08h, 3Dh, 00h
    db 20h, 00h, 00h, 0Fh, 8Fh, 0EAh, 00h, 00h, 00h, 85h, 0C0h, 0Fh, 8Ch, 0E2h, 00h, 00h
    db 00h, 8Bh, 4Eh, 10h, 0F6h, 0C1h, 03h, 0Fh, 85h, 0D6h, 00h, 00h, 00h, 0F6h, 46h, 0Ch
    db 03h, 0Fh, 85h, 0CCh, 00h, 00h, 00h, 85h, 0C9h, 0Fh, 84h, 0BEh, 00h, 00h, 00h, 0E8h
    db 0ACh, 08h, 0FFh, 0FFh, 5Fh, 5Eh, 8Bh, 0E8h, 5Dh, 0C3h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h
    db 0Ch, 81h, 0F9h, 00h, 00h, 01h, 00h, 0Fh, 82h, 0A6h, 00h, 00h, 00h, 8Bh, 46h, 0Ch
    db 85h, 0C0h, 74h, 0Bh, 3Dh, 00h, 00h, 01h, 00h, 0Fh, 82h, 94h, 00h, 00h, 00h, 0F6h
    db 0C1h, 03h, 0Fh, 85h, 8Bh, 00h, 00h, 00h, 0A8h, 03h, 0Fh, 85h, 83h, 00h, 00h, 00h
    db 85h, 0C9h, 74h, 07h, 0E8h, 0E7h, 0FDh, 0FFh, 0FFh, 8Bh, 0E8h, 8Bh, 4Eh, 0Ch, 85h, 0C9h
    db 74h, 6Bh, 0E8h, 0D9h, 0FDh, 0FFh, 0FFh, 5Fh, 03h, 0E8h, 5Eh, 8Bh, 0C5h, 5Dh, 0C3h, 3Dh
    db 00h, 00h, 01h, 00h, 72h, 5Dh, 0A8h, 03h, 75h, 59h, 8Bh, 4Eh, 14h, 81h, 0F9h, 00h
    db 00h, 01h, 00h, 7Fh, 4Eh, 8Bh, 7Eh, 28h, 0BAh, 00h, 10h, 00h, 00h, 3Bh, 0FAh, 7Fh
    db 42h, 39h, 56h, 30h, 7Fh, 3Dh, 8Bh, 7Eh, 1Ch, 0BAh, 00h, 80h, 00h, 00h, 3Bh, 0FAh
    db 77h, 31h, 39h, 56h, 20h, 77h, 2Ch, 3Dh, 0FFh, 0FFh, 0Fh, 00h, 76h, 1Fh, 33h, 0FFh
    db 85h, 0C9h, 7Eh, 19h, 8Bh, 56h, 18h, 8Bh, 0Ch, 0BAh, 3Bh, 0F1h, 74h, 0Fh, 0E8h, 7Dh
    db 0FDh, 0FFh, 0FFh, 03h, 0E8h, 8Bh, 46h, 14h, 47h, 3Bh, 0F8h, 7Ch, 0E7h, 5Fh, 5Eh, 8Bh
    db 0C5h, 5Dh, 0C3h, 5Fh, 5Eh, 33h, 0C0h, 5Dh, 0C3h, 8Dh, 49h, 00h, 1Dh, 0C4h, 0CAh, 00h
    db 1Dh, 0C4h, 0CAh, 00h, 0B9h, 0C1h, 0CAh, 00h, 21h, 0C2h, 0CAh, 00h, 2Bh, 0C3h, 0CAh, 00h
    db 1Dh, 0C4h, 0CAh, 00h, 1Dh, 0C4h, 0CAh, 00h, 6Ah, 0C3h, 0CAh, 00h, 0BFh, 0C3h, 0CAh, 00h
    db 1Dh, 0C4h, 0CAh, 00h, 1Dh, 0C4h, 0CAh, 00h, 1Dh, 0C4h, 0CAh, 00h
?d_008ac190@@YAXXZ ENDP

; retail @ 0x008AC460 size 440
public ?d_008ac460@@YAXXZ
?d_008ac460@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 55h, 56h, 8Bh, 0F1h, 8Bh, 06h, 83h, 0E8h, 03h, 83h, 0F8h
    db 06h, 57h, 0Fh, 87h, 7Ah, 01h, 00h, 00h, 0FFh, 24h, 85h, 0FCh, 0C5h, 0CAh, 00h, 33h
    db 0FFh, 3Bh, 7Eh, 0Ch, 0Fh, 8Dh, 68h, 01h, 00h, 00h, 8Bh, 46h, 10h, 8Bh, 0Ch, 0B8h
    db 0E8h, 0FBh, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Ch, 05h, 2Bh, 0D8h, 47h, 0EBh, 0E3h, 8Bh, 4Eh
    db 10h, 8Bh, 34h, 0B9h, 0E9h, 1Ah, 01h, 00h, 00h, 8Bh, 46h, 2Ch, 33h, 0FFh, 85h, 0C0h
    db 7Eh, 23h, 33h, 0EDh, 8Bh, 56h, 30h, 8Bh, 4Ch, 2Ah, 04h, 85h, 0C9h, 74h, 0Bh, 0E8h
    db 0CCh, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Ch, 31h, 2Bh, 0D8h, 8Bh, 46h, 2Ch, 47h, 83h, 0C5h
    db 44h, 3Bh, 0F8h, 7Ch, 0DFh, 8Bh, 46h, 3Ch, 85h, 0C0h, 0Fh, 84h, 12h, 01h, 00h, 00h
    db 8Bh, 08h, 85h, 0C9h, 74h, 24h, 0E8h, 0A5h, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Dh, 19h, 8Bh
    db 4Eh, 3Ch, 8Bh, 31h, 0E9h, 0CAh, 00h, 00h, 00h, 8Bh, 46h, 30h, 6Bh, 0FFh, 44h, 8Bh
    db 74h, 07h, 04h, 0E9h, 0BBh, 00h, 00h, 00h, 2Bh, 0D8h, 8Bh, 56h, 3Ch, 8Bh, 4Ah, 04h
    db 85h, 0C9h, 74h, 14h, 0E8h, 77h, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Dh, 0Bh, 8Bh, 46h, 3Ch
    db 8Bh, 70h, 04h, 0E9h, 9Bh, 00h, 00h, 00h, 8Bh, 4Eh, 3Ch, 8Bh, 49h, 08h, 85h, 0C9h
    db 74h, 14h, 0E8h, 59h, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Dh, 0Bh, 8Bh, 56h, 3Ch, 8Bh, 72h
    db 08h, 0E9h, 7Dh, 00h, 00h, 00h, 8Bh, 46h, 3Ch, 8Bh, 48h, 0Ch, 85h, 0C9h, 0Fh, 84h
    db 9Eh, 00h, 00h, 00h, 0E8h, 37h, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 0Fh, 8Dh, 91h, 00h, 00h
    db 00h, 8Bh, 4Eh, 3Ch, 8Bh, 71h, 0Ch, 0EBh, 5Ah, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 0Eh
    db 0E8h, 1Bh, 0FCh, 0FFh, 0FFh, 3Bh, 0D8h, 7Dh, 05h, 8Bh, 76h, 08h, 0EBh, 45h, 8Bh, 4Eh
    db 08h, 0E8h, 0Ah, 0FCh, 0FFh, 0FFh, 8Bh, 4Eh, 0Ch, 2Bh, 0D8h, 85h, 0C9h, 74h, 5Bh, 0E8h
    db 0FCh, 0FBh, 0FFh, 0FFh, 3Bh, 0D8h, 7Dh, 52h, 8Bh, 76h, 0Ch, 0EBh, 26h, 33h, 0FFh, 90h
    db 3Bh, 7Eh, 14h, 7Dh, 4Dh, 8Bh, 56h, 18h, 8Bh, 0Ch, 0BAh, 3Bh, 0F1h, 74h, 43h, 0E8h
    db 0DCh, 0FBh, 0FFh, 0FFh, 3Bh, 0D8h, 7Ch, 05h, 2Bh, 0D8h, 47h, 0EBh, 0E3h, 8Bh, 46h, 18h
    db 8Bh, 34h, 0B8h, 8Bh, 06h, 83h, 0E8h, 03h, 83h, 0F8h, 06h, 0Fh, 86h, 0A7h, 0FEh, 0FFh
    db 0FFh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 0C2h, 04h, 00h, 8Bh, 4Eh, 10h, 53h, 0E8h, 4Dh
    db 06h, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h, 8Bh, 4Eh, 0Ch, 0E8h, 9Eh, 0FBh
    db 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 0C2h, 04h, 00h, 90h, 7Fh, 0C4h, 0CAh, 00h
    db 0A9h, 0C4h, 0CAh, 00h, 0DAh, 0C5h, 0CAh, 00h, 0F2h, 0C5h, 0CAh, 00h, 0F2h, 0C5h, 0CAh, 00h
    db 69h, 0C5h, 0CAh, 00h, 9Dh, 0C5h, 0CAh, 00h
?d_008ac460@@YAXXZ ENDP

; retail @ 0x008B2F50 size 2396
_TEXT ENDS
_TEXT$d00cb2f50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CB2F50 size 2396
public ?d_008b2f50@@YAXXZ
?d_008b2f50@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va01058BA7
    db 050h, 08Bh, 044h, 024h, 010h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 010h, 085h
    db 0C0h, 053h, 055h, 056h, 057h, 08Bh, 0D9h, 00Fh, 084h, 0DAh, 007h, 000h, 000h, 08Bh, 044h, 024h
    db 034h, 08Bh, 000h, 00Fh, 0B7h, 048h, 002h, 051h, 083h, 0C0h, 008h, 050h
    call ?Rva008D5DC0@@YAPBUR4Word@@PBDI@Z
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 084h, 0BBh, 007h, 000h, 000h, 08Bh, 040h, 004h, 048h, 083h
    db 0F8h, 00Fh, 00Fh, 087h, 0AEh, 007h, 000h, 000h, 0FFh, 024h, 085h
    dd ?d_008b2f50@@YAXXZ + 091Ch
    db 0A1h
    dd ?g_rva008B2BD0_0@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 000h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd g_Va00CB2DB0
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_0@@3PAVRva008B2BD0Item@@A
    db 08Bh, 050h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 050h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_0@@3PAVRva008B2BD0Item@@A
    db 08Bh, 001h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 010h, 0A1h
    dd ?g_rva008B2BD0_0@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 06Ah, 024h
    call ?Rva008B2B40@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 001h, 000h, 000h
    db 000h, 074h, 011h, 08Bh, 04Bh, 020h, 051h, 06Ah, 022h, 08Bh, 0C8h
    call ?bfmeGo911F@BfmeThing911F@@QAEPAV1@HPAX@Z
    db 08Bh, 0F8h, 0EBh, 002h, 033h, 0FFh, 08Bh, 043h, 020h, 083h, 0CDh, 0FFh, 085h, 0C0h, 089h, 06Ch
    db 024h, 028h, 00Fh, 084h, 016h, 001h, 000h, 000h, 08Bh, 0C8h, 08Bh, 011h, 08Dh, 044h, 024h, 010h
    db 050h, 0FFh, 052h, 008h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 00Fh, 084h, 0FEh, 000h, 000h, 000h
    db 0EBh, 007h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 00Fh
    db 084h, 0E9h, 000h, 000h, 000h, 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 040h, 08Bh, 04Eh, 00Ch, 089h, 00Dh
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 051h, 004h, 03Bh, 011h, 08Dh, 041h, 004h, 07Ch, 009h, 081h, 066h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh, 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 035h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 02Ch, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 034h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 002h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 089h, 06Ch, 024h, 028h, 08Bh, 0F0h, 08Bh, 054h, 024h, 014h, 052h, 08Bh
    db 0CEh
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 08Bh, 044h, 024h, 010h, 050h, 08Dh, 04Ch, 024h, 034h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 056h, 08Dh, 04Ch, 024h, 034h, 051h, 08Dh, 04Fh, 008h, 0C7h, 044h, 024h, 030h, 003h, 000h, 000h
    db 000h
    call ?d_0089d890@@YAXXZ
    db 08Bh, 04Bh, 020h, 08Bh, 011h, 08Dh, 044h, 024h, 018h, 050h, 0FFh, 052h, 00Ch, 08Bh, 008h, 089h
    db 04Ch, 024h, 010h, 08Bh, 050h, 004h, 08Bh, 044h, 024h, 030h, 089h, 054h, 024h, 014h, 066h, 0FFh
    db 008h, 066h, 083h, 038h, 000h, 089h, 06Ch, 024h, 028h, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 00Fh, 085h, 00Bh, 0FFh
    db 0FFh, 0FFh, 085h, 0FFh, 00Fh, 084h, 0EEh, 005h, 000h, 000h, 08Bh, 0C7h, 05Fh, 05Eh, 05Dh, 05Bh
    db 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h, 008h
    db 000h, 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 0CCh, 005h, 000h, 000h, 06Ah, 02Ch
    call ?Rva008A90F0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 004h, 000h, 000h
    db 000h, 074h, 00Bh, 08Bh, 0C8h
    call ?bfmeGo1030C@BfmeC1030@@QAEPAV1@XZ
    db 08Bh, 0E8h, 0EBh, 002h, 033h, 0EDh, 085h, 0EDh, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh
    db 00Fh, 084h, 07Eh, 005h, 000h, 000h, 08Bh, 04Bh, 020h, 08Bh, 011h, 0FFh, 052h, 014h, 08Bh, 0F0h
    db 033h, 0FFh, 085h, 0F6h, 074h, 048h, 06Ah, 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 005h, 000h, 000h
    db 000h, 074h, 00Ch, 056h, 06Ah, 020h, 08Bh, 0C8h
    call ??0Rva008B2EF0@@QAE@II@Z
    db 0EBh, 002h, 033h, 0C0h, 050h, 057h, 08Bh, 0CDh, 0C7h, 044h, 024h, 030h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?rva008B8E10@BfmeN1242@@QAEXHPAVBfmeE1242@@@Z
    db 08Bh, 04Bh, 020h, 08Bh, 001h, 047h, 0FFh, 050h, 018h, 08Bh, 0F0h, 085h, 0F6h, 075h, 0B8h, 05Fh
    db 05Eh, 08Bh, 0C5h, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 0A1h
    dd ?g_rva008B2BD0_1@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 006h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd g_Va00CB2DC0
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_1@@3PAVRva008B2BD0Item@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_1@@3PAVRva008B2BD0Item@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_rva008B2BD0_1@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 0A8h, 004h, 000h, 000h
    db 08Bh, 0C8h, 08Bh, 001h, 0FFh, 050h, 020h, 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 097h, 004h, 000h
    db 000h, 06Ah, 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 0C7h, 044h, 024h, 028h, 007h, 000h, 000h, 000h, 085h
    db 0C0h, 00Fh, 084h, 059h, 004h, 000h, 000h, 056h, 06Ah, 020h, 08Bh, 0C8h
    call ??0Rva008B2EF0@@QAE@II@Z
    db 0E9h, 04Ch, 004h, 000h, 000h, 0A1h
    dd ?g_rva008B2BD0_2@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 008h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd ?aptQueryBool@@YAPAVAptValue@@PAURva008B2E60Value@@H@Z
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_2@@3PAVRva008B2BD0Item@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_2@@3PAVRva008B2BD0Item@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_rva008B2BD0_2@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 0A1h
    dd ?g_rva008B2BD0_3@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 009h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd g_Va00CB2DD0
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_3@@3PAVRva008B2BD0Item@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_3@@3PAVRva008B2BD0Item@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_rva008B2BD0_3@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 079h, 003h, 000h, 000h
    db 08Bh, 0C8h, 08Bh, 001h, 0FFh, 050h, 02Ch, 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 068h, 003h, 000h
    db 000h, 06Ah, 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 0C7h, 044h, 024h, 028h, 00Ah, 000h, 000h, 000h, 0E9h
    db 0CCh, 0FEh, 0FFh, 0FFh, 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 042h, 003h, 000h, 000h, 08Bh
    db 0C8h, 08Bh, 011h, 0FFh, 052h, 030h, 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 031h, 003h, 000h, 000h
    db 06Ah, 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 0C7h, 044h, 024h, 028h, 00Bh, 000h, 000h, 000h, 0E9h
    db 095h, 0FEh, 0FFh, 0FFh, 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 03Fh, 08Bh, 046h, 00Ch, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 0A3h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 03Bh, 011h, 08Dh, 041h, 004h, 07Ch, 009h, 081h, 066h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh, 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 039h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 030h, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 00Ch, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 0F0h, 08Bh, 015h
    dd ?g_rva008B2EA0Base@@3PAXA
    db 083h, 0C2h, 008h, 052h, 08Bh, 0CEh
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 0B9h, 001h, 000h, 000h, 08Bh, 0C8h, 08Bh, 001h, 0FFh
    db 050h, 034h, 0E9h, 0A1h, 001h, 000h, 000h, 08Bh, 043h, 020h, 085h, 0C0h, 00Fh, 084h, 06Ah, 002h
    db 000h, 000h, 08Bh, 0C8h, 08Bh, 011h, 0FFh, 052h, 03Ch, 08Bh, 0D8h, 0A1h
    dd ?Rva008D29C0Head@@3PAURva008D29C0Node@@A
    db 085h, 0C0h, 074h, 060h, 08Bh, 048h, 008h, 08Bh, 015h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 089h, 00Dh
    dd ?Rva008D29C0Head@@3PAURva008D29C0Node@@A
    db 08Bh, 072h, 004h, 03Bh, 032h, 08Dh, 04Ah, 004h, 07Ch, 024h, 08Bh, 048h, 004h, 05Fh, 05Eh, 081h
    db 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 05Dh, 089h, 058h, 008h, 089h, 048h, 004h, 05Bh, 08Bh, 04Ch, 024h
    db 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Bh, 052h
    db 008h, 089h, 004h, 0B2h, 08Bh, 011h, 05Fh, 05Eh, 042h, 089h, 011h, 05Dh, 089h, 058h, 008h, 05Bh
    db 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h, 008h
    db 000h, 06Ah, 00Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 085h, 0C0h, 00Fh, 084h, 0CEh, 001h, 000h, 000h, 08Bh, 048h, 004h, 081h, 0E1h
    db 007h, 080h, 000h, 0F0h, 081h, 0C9h, 007h, 080h, 000h, 040h, 0C7h, 000h
    dd ??_7AptValue@@6B@
    db 089h, 048h, 004h, 08Bh, 035h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 07Eh, 004h, 03Bh, 03Eh, 08Dh, 056h, 004h, 07Ch, 027h, 05Fh, 05Eh, 081h, 0E1h, 0FFh, 0FFh
    db 0FFh, 0BFh, 05Dh, 089h, 058h, 008h, 089h, 048h, 004h, 0C7h, 000h
    dd ??_7AptInteger@@6B@
    db 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h
    db 008h, 000h, 08Bh, 04Eh, 008h, 089h, 004h, 0B9h, 08Bh, 00Ah, 05Fh, 05Eh, 041h, 089h, 00Ah, 05Dh
    db 089h, 058h, 008h, 0C7h, 000h
    dd ??_7AptInteger@@6B@
    db 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h
    db 008h, 000h, 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 040h, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 056h, 00Ch, 089h, 015h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 03Bh, 011h, 08Dh, 041h, 004h, 07Ch, 009h, 081h, 066h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh, 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 039h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 030h, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 00Dh, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 0F0h, 08Bh, 015h
    dd ?g_rva008B2EA0Base@@3PAXA
    db 083h, 0C2h, 008h, 052h, 08Bh, 0CEh
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 08Bh, 043h, 020h, 085h, 0C0h, 074h, 013h, 08Bh, 0C8h, 08Bh, 001h, 0FFh, 050h, 040h, 085h, 0C0h
    db 074h, 008h, 050h, 08Bh, 0CEh
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 05Fh, 08Bh, 0C6h, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 083h, 0C4h, 01Ch, 0C2h, 008h, 000h, 08Bh, 043h, 020h, 085h, 0C0h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 074h, 03Eh, 08Bh, 0C8h, 08Bh, 011h, 0FFh, 052h, 048h, 08Bh, 0F0h, 085h, 0F6h, 074h, 031h, 06Ah
    db 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 00Eh, 000h, 000h
    db 000h, 074h, 00Ch, 056h, 06Ah, 020h, 08Bh, 0C8h
    call ??0Rva008B2EF0@@QAE@II@Z
    db 0EBh, 002h, 033h, 0C0h, 08Bh, 048h, 004h, 084h, 0EDh, 08Bh, 0F8h, 078h, 051h, 08Bh, 0C7h, 05Fh
    db 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 01Ch, 0C2h, 008h, 000h, 08Bh, 043h, 020h, 085h, 0C0h, 074h, 048h, 08Bh, 0C8h, 08Bh, 001h, 0FFh
    db 050h, 04Ch, 08Bh, 0F0h, 085h, 0F6h, 074h, 03Bh, 06Ah, 028h
    call ?Rva008B2AE0@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 0C7h, 044h, 024h, 028h, 00Fh, 000h, 000h, 000h, 0E9h
    db 09Fh, 0FBh, 0FFh, 0FFh, 033h, 0C0h, 08Bh, 048h, 004h, 084h, 0EDh, 078h, 002h, 033h, 0C0h, 05Fh
    db 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 01Ch, 0C2h, 008h, 000h, 0A1h
    dd ?bfmeTheCBC@@3HA
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 0A1h
    dd ?g_rva008B2BD0_4@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 010h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd g_Va00CB2DE0
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_4@@3PAVRva008B2BD0Item@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_4@@3PAVRva008B2BD0Item@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_rva008B2BD0_4@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 010h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 01Ch, 0C2h, 008h, 000h, 0A1h
    dd ?g_rva008B2BD0_5@@3PAVRva008B2BD0Item@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 030h, 085h, 0C0h, 0C7h, 044h, 024h, 028h, 011h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd ?rva008B2EA0Walk@@YAPAXPAVRva008B2EA0Obj@@@Z
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_rva008B2BD0_5@@3PAVRva008B2BD0Item@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_rva008B2BD0_5@@3PAVRva008B2BD0Item@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 028h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 08Bh, 04Ch, 024h, 020h
    db 0A1h
    dd ?g_rva008B2BD0_5@@3PAVRva008B2BD0Item@@A
    db 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 01Ch, 0C2h, 008h
    db 000h, 090h
    dd ?d_008b2f50@@YAXXZ + 05Dh
    dd ?d_008b2f50@@YAXXZ + 0D0h
    dd ?d_008b2f50@@YAXXZ + 0244h
    dd ?d_008b2f50@@YAXXZ + 02F5h
    dd ?d_008b2f50@@YAXXZ + 0368h
    dd ?d_008b2f50@@YAXXZ + 03B1h
    dd ?d_008b2f50@@YAXXZ + 0424h
    dd ?d_008b2f50@@YAXXZ + 0497h
    dd ?d_008b2f50@@YAXXZ + 04CEh
    dd ?d_008b2f50@@YAXXZ + 0505h
    dd ?d_008b2f50@@YAXXZ + 05A6h
    dd ?d_008b2f50@@YAXXZ + 06AEh
    dd ?d_008b2f50@@YAXXZ + 076Ah
    dd ?d_008b2f50@@YAXXZ + 07CCh
    dd ?d_008b2f50@@YAXXZ + 0835h
    dd ?d_008b2f50@@YAXXZ + 08A8h
?d_008b2f50@@YAXXZ ENDP
_TEXT$d00cb2f50 ENDS
_TEXT SEGMENT

; retail @ 0x008B3AA0 size 1940
public ?d_008b3aa0@@YAXXZ
?d_008b3aa0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0E8h, 8Bh, 05h, 01h, 50h, 83h, 7Ch
    db 24h, 14h, 01h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 56h, 0Fh, 8Ch, 98h, 00h, 00h
    db 00h, 8Bh, 74h, 24h, 14h, 8Bh, 46h, 04h, 83h, 0E0h, 3Fh, 3Ch, 21h, 0Fh, 85h, 86h
    db 00h, 00h, 00h, 8Bh, 15h, 48h, 87h, 33h, 01h, 8Bh, 0Dh, 50h, 87h, 33h, 01h, 8Bh
    db 4Ch, 91h, 0FCh, 8Bh, 51h, 04h, 8Bh, 0C2h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 74h, 05h
    db 83h, 0F8h, 2Ah, 75h, 64h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 5Ah, 66h
    db 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 18h, 98h, 52h, 2Dh, 01h, 8Dh, 44h
    db 24h, 18h, 50h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0A0h, 4Ah, 0FEh, 0FFh
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 10h, 8Bh, 44h, 24h, 18h, 8Bh, 11h, 83h, 0C0h, 08h
    db 50h, 0FFh, 92h, 80h, 00h, 00h, 00h, 8Bh, 44h, 24h, 18h, 66h, 0FFh, 08h, 66h, 83h
    db 38h, 00h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah
    db 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 04h, 0A1h, 0BCh, 79h
    db 33h, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C3h, 0CCh, 0CCh
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 08h, 8Ch, 05h, 01h, 50h, 83h, 7Ch
    db 24h, 14h, 01h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 56h, 0Fh, 8Ch, 98h, 00h, 00h
    db 00h, 8Bh, 74h, 24h, 14h, 8Bh, 46h, 04h, 83h, 0E0h, 3Fh, 3Ch, 21h, 0Fh, 85h, 86h
    db 00h, 00h, 00h, 8Bh, 15h, 48h, 87h, 33h, 01h, 8Bh, 0Dh, 50h, 87h, 33h, 01h, 8Bh
    db 4Ch, 91h, 0FCh, 8Bh, 51h, 04h, 8Bh, 0C2h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 74h, 05h
    db 83h, 0F8h, 2Ah, 75h, 64h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 5Ah, 66h
    db 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 18h, 98h, 52h, 2Dh, 01h, 8Dh, 44h
    db 24h, 18h, 50h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0D0h, 49h, 0FEh, 0FFh
    db 8Bh, 4Eh, 20h, 85h, 0C9h, 74h, 10h, 8Bh, 44h, 24h, 18h, 8Bh, 11h, 83h, 0C0h, 08h
    db 50h, 0FFh, 92h, 88h, 00h, 00h, 00h, 8Bh, 44h, 24h, 18h, 66h, 0FFh, 08h, 66h, 83h
    db 38h, 00h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah
    db 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 04h, 0A1h, 0BCh, 79h
    db 33h, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C3h, 0CCh, 0CCh
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 7Ah, 8Ch, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 46h, 04h, 57h, 8Bh
    db 7Ch, 24h, 20h, 83h, 0E0h, 0E0h, 57h, 83h, 0C8h, 20h, 56h, 8Bh, 0D9h, 89h, 46h, 04h
    db 0E8h, 0DBh, 0F2h, 0FFh, 0FFh, 8Bh, 4Eh, 04h, 83h, 0E1h, 0E1h, 83h, 0C9h, 21h, 85h, 0C0h
    db 89h, 4Eh, 04h, 74h, 0Bh, 8Bh, 48h, 04h, 84h, 0EDh, 0Fh, 88h, 5Ch, 05h, 00h, 00h
    db 8Bh, 07h, 0Fh, 0B7h, 50h, 02h, 52h, 83h, 0C0h, 08h, 50h, 0E8h, 20h, 21h, 02h, 00h
    db 83h, 0C4h, 08h, 85h, 0C0h, 0Fh, 84h, 3Fh, 05h, 00h, 00h, 8Bh, 40h, 04h, 8Bh, 7Bh
    db 20h, 83h, 0C0h, 9Ch, 83h, 0F8h, 0Ch, 0Fh, 87h, 2Dh, 05h, 00h, 00h, 0FFh, 24h, 85h
    db 00h, 42h, 0CBh, 00h, 8Bh, 35h, 78h, 84h, 33h, 01h, 85h, 0F6h, 74h, 3Fh, 8Bh, 46h
    db 0Ch, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 0A3h, 78h, 84h, 33h, 01h, 8Bh, 51h, 04h, 3Bh
    db 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 08h, 8Bh
    db 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h, 08h, 3Dh, 98h, 52h, 2Dh, 01h, 8Dh
    db 4Eh, 08h, 74h, 39h, 6Ah, 00h, 0E8h, 45h, 0AFh, 0FEh, 0FFh, 0EBh, 30h, 6Ah, 10h, 0FFh
    db 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h
    db 24h, 14h, 00h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0D1h, 5Dh, 0FFh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0F0h, 8Bh, 15h, 08h
    db 86h, 33h, 01h, 83h, 0C2h, 08h, 52h, 8Bh, 0CEh, 0E8h, 72h, 0EAh, 0FDh, 0FFh, 8Bh, 43h
    db 20h, 85h, 0C0h, 0Fh, 84h, 0B1h, 00h, 00h, 00h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 58h
    db 0E9h, 99h, 00h, 00h, 00h, 8Bh, 35h, 78h, 84h, 33h, 01h, 85h, 0F6h, 74h, 40h, 8Bh
    db 4Eh, 0Ch, 89h, 0Dh, 78h, 84h, 33h, 01h, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 8Bh, 51h
    db 04h, 3Bh, 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh
    db 08h, 8Bh, 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h, 08h, 3Dh, 98h, 52h, 2Dh
    db 01h, 8Dh, 4Eh, 08h, 74h, 39h, 6Ah, 00h, 0E8h, 0A3h, 0AEh, 0FEh, 0FFh, 0EBh, 30h, 6Ah
    db 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h
    db 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0C8h, 0E8h, 2Fh, 5Dh, 0FFh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 8Bh, 0F0h, 8Bh
    db 15h, 08h, 86h, 33h, 01h, 83h, 0C2h, 08h, 52h, 8Bh, 0CEh, 0E8h, 0D0h, 0E9h, 0FDh, 0FFh
    db 8Bh, 43h, 20h, 85h, 0C0h, 74h, 13h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 68h, 85h, 0C0h
    db 74h, 08h, 50h, 8Bh, 0CEh, 0E8h, 0B6h, 0E9h, 0FDh, 0FFh, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0A1h, 78h, 83h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 10h, 38h, 0FEh, 0FFh
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 02h, 00h, 00h
    db 00h, 74h, 0Eh, 68h, 40h, 3Ah, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 71h, 61h, 0FEh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0A3h, 78h, 83h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh
    db 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 78h, 83h, 33h, 01h, 8Bh, 11h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 78h, 83h, 33h, 01h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 0A1h, 7Ch, 83h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 9Eh, 37h
    db 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 03h
    db 00h, 00h, 00h, 74h, 0Eh, 68h, 70h, 3Ah, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 0FFh, 60h, 0FEh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 7Ch, 83h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh
    db 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 7Ch, 83h, 33h, 01h, 8Bh
    db 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 7Ch, 83h, 33h, 01h
    db 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 08h, 00h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 7Ch, 85h, 0C0h, 0A1h, 0D4h, 87h
    db 33h, 01h, 0Fh, 95h, 0C3h, 85h, 0C0h, 0Fh, 85h, 0F3h, 00h, 00h, 00h, 6Ah, 0Ch, 0FFh
    db 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 0BAh, 02h, 00h, 00h
    db 0C7h, 00h, 68h, 5Dh, 13h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 05h, 80h, 00h, 0F0h, 81h
    db 0C9h, 05h, 80h, 00h, 40h, 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh
    db 04h, 3Bh, 3Eh, 8Dh, 56h, 04h, 0Fh, 8Ch, 0Ah, 01h, 00h, 00h, 81h, 0E1h, 0FFh, 0FFh
    db 0FFh, 0BFh, 89h, 48h, 04h, 0C7h, 00h, 0A8h, 60h, 13h, 01h, 88h, 58h, 08h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 0A1h, 80h, 83h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0AEh, 36h
    db 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 04h
    db 00h, 00h, 00h, 74h, 0Eh, 68h, 0A0h, 3Ah, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 0Fh, 60h, 0FEh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 80h, 83h, 33h, 01h, 8Bh, 50h, 04h, 81h, 0E2h, 7Fh
    db 0C0h, 0FFh, 0FFh, 83h, 0CAh, 40h, 89h, 50h, 04h, 8Bh, 0Dh, 80h, 83h, 33h, 01h, 8Bh
    db 01h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 10h, 0A1h, 80h, 83h, 33h, 01h
    db 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 08h, 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 92h, 84h, 00h, 00h, 00h, 85h, 0C0h
    db 0A1h, 0D4h, 87h, 33h, 01h, 0Fh, 95h, 0C3h, 85h, 0C0h, 0Fh, 84h, 0Dh, 0FFh, 0FFh, 0FFh
    db 8Bh, 48h, 08h, 8Bh, 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0D4h, 87h, 33h, 01h, 8Bh
    db 72h, 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Eh, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh
    db 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh, 01h, 88h
    db 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 0FFh, 02h, 0C7h, 00h
    db 0A8h, 60h, 13h, 01h, 88h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 84h, 83h, 33h, 01h
    db 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0A5h, 35h, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 1Ch, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 05h, 00h, 00h, 00h, 74h, 0Eh, 68h, 70h
    db 3Bh, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 06h, 5Fh, 0FEh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 84h
    db 83h, 33h, 01h, 8Bh, 50h, 04h, 81h, 0E2h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0CAh, 40h, 89h
    db 50h, 04h, 8Bh, 0Dh, 84h, 83h, 33h, 01h, 8Bh, 01h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0FFh, 10h, 0A1h, 84h, 83h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 17h, 8Bh
    db 0CFh, 0FFh, 92h, 94h, 00h, 00h, 00h, 8Bh, 0D8h, 0A1h, 0D0h, 87h, 33h, 01h, 85h, 0C0h
    db 74h, 56h, 8Bh, 48h, 08h, 8Bh, 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0D0h, 87h, 33h
    db 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Eh, 81h, 60h, 04h, 0FFh, 0FFh
    db 0FFh, 0BFh, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh
    db 01h, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh
    db 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 83h, 0C4h, 04h, 85h, 0C0h, 74h, 73h, 8Bh, 48h, 04h, 81h, 0E1h, 07h, 80h, 00h, 0F0h
    db 81h, 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh
    db 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 3Bh, 3Eh, 8Dh, 56h, 04h, 7Ch, 26h, 81h
    db 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 48h, 04h, 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 58h
    db 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h
    db 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 0FFh, 02h, 0C7h, 00h, 00h
    db 64h, 13h, 01h, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 33h, 0C0h, 8Bh, 4Ch, 24h, 0Ch
    db 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0C4h, 3Ch, 0CBh, 00h, 0EAh, 41h, 0CBh, 00h, 0EAh, 41h, 0CBh, 00h, 65h, 3Dh, 0CBh, 00h
    db 20h, 3Eh, 0CBh, 00h, 92h, 3Eh, 0CBh, 00h, 04h, 3Fh, 0CBh, 00h, 82h, 3Fh, 0CBh, 00h
    db 0F4h, 3Fh, 0CBh, 00h, 8Bh, 40h, 0CBh, 00h, 0EAh, 41h, 0CBh, 00h, 0EAh, 41h, 0CBh, 00h
    db 0FDh, 40h, 0CBh, 00h
?d_008b3aa0@@YAXXZ ENDP

; retail @ 0x008BA0B0 size 1824
public ?d_008ba0b0@@YAXXZ
?d_008ba0b0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 14h, 92h, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h, 14h, 85h, 0DBh, 56h, 8Bh, 74h, 24h
    db 1Ch, 57h, 8Bh, 0F9h, 0Fh, 84h, 44h, 06h, 00h, 00h, 8Bh, 06h, 0Fh, 0B7h, 48h, 02h
    db 51h, 83h, 0C0h, 08h, 50h, 0E8h, 0E6h, 0E9h, 0FFh, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 0Fh
    db 84h, 29h, 06h, 00h, 00h, 8Bh, 40h, 04h, 48h, 83h, 0F8h, 0Ch, 0Fh, 87h, 1Ch, 06h
    db 00h, 00h, 0FFh, 24h, 85h, 9Ch, 0A7h, 0CBh, 00h, 0A1h, 0D0h, 87h, 33h, 01h, 85h, 0C0h
    db 8Bh, 5Fh, 28h, 74h, 56h, 8Bh, 50h, 08h, 89h, 15h, 0D0h, 87h, 33h, 01h, 8Bh, 15h
    db 10h, 78h, 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Eh, 81h, 60h
    db 04h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 52h, 08h, 89h
    db 04h, 0B2h, 0FFh, 01h, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 6Ah, 0Ch, 0FFh, 15h, 28h
    db 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 73h, 8Bh, 48h, 04h, 81h, 0E1h, 07h
    db 80h, 00h, 0F0h, 81h, 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h
    db 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 3Bh, 3Eh, 8Dh, 56h, 04h
    db 7Ch, 26h, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 48h, 04h, 0C7h, 00h, 00h, 64h, 13h
    db 01h, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh
    db 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 0FFh, 02h
    db 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 58h, 08h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 33h, 0C0h, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch
    db 0C2h, 08h, 00h, 0A1h, 38h, 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 2Dh
    db 0D4h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h
    db 00h, 00h, 00h, 00h, 74h, 0Eh, 68h, 0C0h, 9Ch, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 8Eh, 0FDh
    db 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 38h, 84h, 33h, 01h, 8Bh, 50h, 04h, 81h, 0E2h
    db 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0CAh, 40h, 89h, 50h, 04h, 8Bh, 0Dh, 38h, 84h, 33h, 01h
    db 8Bh, 01h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 10h, 0A1h, 38h, 84h, 33h
    db 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h
    db 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 3Ch, 84h, 33h, 01h, 85h, 0C0h, 0Fh, 85h, 81h, 00h
    db 00h, 00h, 6Ah, 24h, 0E8h, 0B7h, 0D3h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h
    db 85h, 0C0h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 3Fh, 68h, 0F0h, 94h, 0CBh
    db 00h, 8Bh, 0C8h, 0E8h, 18h, 0FDh, 0FDh, 0FFh, 0EBh, 33h, 0A1h, 3Ch, 84h, 33h, 01h, 85h
    db 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 86h, 0D3h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 02h, 00h, 00h, 00h, 74h, 0Eh, 68h, 0F0h, 94h
    db 0CBh, 00h, 8Bh, 0C8h, 0E8h, 0E7h, 0FCh, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 3Ch, 84h
    db 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h
    db 04h, 8Bh, 0Dh, 3Ch, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 12h, 0A1h, 3Ch, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 40h, 84h, 33h
    db 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 14h, 0D3h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 03h, 00h, 00h, 00h, 74h, 0Eh, 68h
    db 20h, 90h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 75h, 0FCh, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h
    db 40h, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h
    db 89h, 48h, 04h, 8Bh, 0Dh, 40h, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 40h, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 44h
    db 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0A2h, 0D2h, 0FDh, 0FFh, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 04h, 00h, 00h, 00h, 74h
    db 0Eh, 68h, 0A0h, 96h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 03h, 0FCh, 0FDh, 0FFh, 0EBh, 02h, 33h
    db 0C0h, 0A3h, 44h, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h
    db 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 44h, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 44h, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
    db 0A1h, 48h, 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 30h, 0D2h, 0FDh, 0FFh
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 05h, 00h, 00h
    db 00h, 74h, 0Eh, 68h, 80h, 90h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 91h, 0FBh, 0FDh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 0A3h, 48h, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh
    db 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 48h, 84h, 33h, 01h, 8Bh, 11h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 48h, 84h, 33h, 01h, 8Bh, 4Ch
    db 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 0A1h, 4Ch, 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0BEh, 0D1h
    db 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 06h
    db 00h, 00h, 00h, 74h, 0Eh, 68h, 80h, 97h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 1Fh, 0FBh, 0FDh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 4Ch, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh
    db 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 4Ch, 84h, 33h, 01h, 8Bh
    db 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 4Ch, 84h, 33h, 01h
    db 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 08h, 00h, 0A1h, 60h, 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h
    db 4Ch, 0D1h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h
    db 14h, 07h, 00h, 00h, 00h, 74h, 0Eh, 68h, 30h, 93h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 0ADh
    db 0FAh, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 60h, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h
    db 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 60h, 84h, 33h
    db 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 60h, 84h
    db 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 58h, 84h, 33h, 01h, 85h, 0C0h, 75h, 50h, 6Ah
    db 24h, 0E8h, 0DAh, 0D0h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h
    db 44h, 24h, 14h, 08h, 00h, 00h, 00h, 74h, 0Eh, 68h, 30h, 99h, 0CBh, 00h, 8Bh, 0C8h
    db 0E8h, 3Bh, 0FAh, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 58h, 84h, 33h, 01h, 8Bh, 48h
    db 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh, 0Dh, 58h
    db 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h
    db 58h, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh
    db 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 64h, 84h, 33h, 01h, 85h, 0C0h, 75h
    db 50h, 6Ah, 24h, 0E8h, 68h, 0D0h, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 85h
    db 0C0h, 0C7h, 44h, 24h, 14h, 09h, 00h, 00h, 00h, 74h, 0Eh, 68h, 40h, 9Ah, 0CBh, 00h
    db 8Bh, 0C8h, 0E8h, 0C9h, 0F9h, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 64h, 84h, 33h, 01h
    db 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h, 04h, 8Bh
    db 0Dh, 64h, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
    db 12h, 0A1h, 64h, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 68h, 84h, 33h, 01h, 85h
    db 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0F6h, 0CFh, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 0Ah, 00h, 00h, 00h, 74h, 0Eh, 68h, 30h, 9Fh
    db 0CBh, 00h, 8Bh, 0C8h, 0E8h, 57h, 0F9h, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 68h, 84h
    db 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 48h
    db 04h, 8Bh, 0Dh, 68h, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 12h, 0A1h, 68h, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0A1h, 5Ch, 84h, 33h
    db 01h, 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 84h, 0CFh, 0FDh, 0FFh, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 0Bh, 00h, 00h, 00h, 74h, 0Eh, 68h
    db 0B0h, 99h, 0CBh, 00h, 8Bh, 0C8h, 0E8h, 0E5h, 0F8h, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h
    db 5Ch, 84h, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h
    db 89h, 48h, 04h, 8Bh, 0Dh, 5Ch, 84h, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 5Ch, 84h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 0Eh
    db 6Ah, 0Ah, 8Dh, 44h, 24h, 20h, 50h, 83h, 0C1h, 08h, 51h, 0C7h, 44h, 24h, 28h, 00h
    db 00h, 00h, 00h, 0E8h, 94h, 0CAh, 13h, 00h, 8Bh, 0Eh, 0Fh, 0B7h, 51h, 02h, 83h, 0C4h
    db 0Ch, 85h, 0D2h, 7Eh, 37h, 8Dh, 54h, 11h, 08h, 39h, 54h, 24h, 1Ch, 75h, 2Dh, 85h
    db 0C0h, 7Ch, 10h, 3Bh, 43h, 28h, 7Dh, 0Bh, 8Bh, 4Bh, 20h, 8Bh, 04h, 81h, 83h, 0E0h
    db 0FEh, 75h, 22h, 0A1h, 0BCh, 79h, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 56h, 8Dh, 4Fh, 08h
    db 0E8h, 6Bh, 27h, 0FEh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Dh, 49h, 00h, 09h, 0A1h, 0CBh, 00h
    db 03h, 0A2h, 0CBh, 00h, 75h, 0A2h, 0CBh, 00h, 1Ch, 0A3h, 0CBh, 00h, 8Eh, 0A3h, 0CBh, 00h
    db 00h, 0A4h, 0CBh, 00h, 72h, 0A4h, 0CBh, 00h, 0E4h, 0A4h, 0CBh, 00h, 56h, 0A5h, 0CBh, 00h
    db 0C8h, 0A5h, 0CBh, 00h, 3Ah, 0A6h, 0CBh, 00h, 0ACh, 0A6h, 0CBh, 00h, 0AAh, 0A2h, 0CBh, 00h
?d_008ba0b0@@YAXXZ ENDP
_TEXT ENDS
END
