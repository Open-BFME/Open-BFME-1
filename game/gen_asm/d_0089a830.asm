.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0EAStringC@@QAE@I@Z:NEAR
EXTERN ??0Rva00899F00Base@@QAE@IH@Z:NEAR
EXTERN ??_7Rva00899EB0Object@@6B@:BYTE
EXTERN ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z:NEAR
EXTERN ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA:BYTE
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?SetAt@AptNativeHash@@QAEXHPAVBfmeHeldC680@@@Z:NEAR
EXTERN ?bfmeInit929G@BfmeThing929G@@QAEXXZ:NEAR
EXTERN ?bfmePush@@YAXPAVBfmeItemDX@@@Z:NEAR
EXTERN ?bfmePutC6E0@BfmeStoreC6E0@@QAEXHPAVBfmeHeldC6E0@@@Z:NEAR
EXTERN ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z:NEAR
EXTERN ?d_0089d180@@YAXXZ:NEAR
EXTERN ?d_0089d890@@YAXXZ:NEAR
EXTERN ?d_008a30c0@@YAXXZ:NEAR
EXTERN ?g_Va013385F8@@3EA:BYTE
EXTERN ?g_Va013387D8@@3PAURva00899C20Registry@@A:BYTE
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?g_bfmeRegisterClass1015@@3HA:BYTE
EXTERN ?g_rva008C8350Builtin86F4@@3PADA:BYTE
EXTERN ?g_rva8D0D80CreateTag@@3DA:BYTE
EXTERN ?initialize@Rva0089C860State@@QAEPAV1@H@Z:NEAR
EXTERN ?ji_009f6ec0@@YAXXZ:NEAR
EXTERN ?ji_009f6fa0@@YAXXZ:NEAR
EXTERN ?rva00899800@@YAPAVAptValue@@PAXH@Z:NEAR
EXTERN _bfmeVft1029A:BYTE
EXTERN g_Va00C98D10:NEAR
EXTERN g_Va0105790A:NEAR
EXTERN g_Va01057A99:NEAR
EXTERN g_Va01057AB8:NEAR
EXTERN g_Va01057AE9:NEAR
EXTERN g_Va01136034:BYTE
EXTERN g_Va01136040:BYTE
EXTERN g_Va013379C0:BYTE
EXTERN g_Va013379F4:BYTE
EXTERN g_Va01338504:BYTE
EXTERN g_Va01338530:BYTE
EXTERN g_Va01338544:BYTE
EXTERN g_Va01338548:BYTE
EXTERN g_Va013385E8:BYTE
EXTERN g_Va013386E4:BYTE
EXTERN g_Va0133870C:BYTE
EXTERN g_Va0133873C:BYTE
_TEXT SEGMENT

; ghidra: FUN_00c9a830  retail @ 0x0089A830 size 73
public ?d_0089a830@@YAXXZ
?d_0089a830@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 76h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0C8h
    db 62h, 13h, 01h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0Dh
    db 24h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0089a830@@YAXXZ ENDP

; ghidra: FUN_00c9a880  retail @ 0x0089A880 size 150
public ?d_0089a880@@YAXXZ
?d_0089a880@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 68h, 76h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 25h, 26h, 80h
    db 00h, 0F0h, 0Dh, 26h, 80h, 00h, 40h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 89h, 46h, 04h
    db 8Bh, 15h, 10h, 78h, 33h, 01h, 8Bh, 1Ah, 8Dh, 4Ah, 04h, 57h, 8Bh, 39h, 3Bh, 0FBh
    db 89h, 74h, 24h, 0Ch, 7Ch, 0Ah, 25h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 46h, 04h, 0EBh, 08h
    db 8Bh, 42h, 08h, 89h, 34h, 0B8h, 0FFh, 01h, 6Ah, 08h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h
    db 1Ch, 00h, 00h, 00h, 00h, 0C7h, 06h, 08h, 63h, 13h, 01h, 0E8h, 70h, 1Fh, 00h, 00h
    db 8Bh, 4Eh, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 81h, 0C9h, 40h, 00h, 0FFh, 0Fh, 89h
    db 4Eh, 04h, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0089a880@@YAXXZ ENDP

; ghidra: FUN_00c9a9a0  retail @ 0x0089A9A0 size 42
public ?d_0089a9a0@@YAXXZ
?d_0089a9a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 7Bh, 0C9h, 0FFh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 20h, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0089a9a0@@YAXXZ ENDP

; ghidra: FUN_00c9a9d0  retail @ 0x0089A9D0 size 73
public ?d_0089a9d0@@YAXXZ
?d_0089a9d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 88h, 76h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 08h
    db 63h, 13h, 01h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 6Dh
    db 22h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0089a9d0@@YAXXZ ENDP

; ghidra: FUN_00c9aa20  retail @ 0x0089AA20 size 150
public ?d_0089aa20@@YAXXZ
?d_0089aa20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 76h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 25h, 27h, 80h
    db 00h, 0F0h, 0Dh, 27h, 80h, 00h, 40h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 89h, 46h, 04h
    db 8Bh, 15h, 10h, 78h, 33h, 01h, 8Bh, 1Ah, 8Dh, 4Ah, 04h, 57h, 8Bh, 39h, 3Bh, 0FBh
    db 89h, 74h, 24h, 0Ch, 7Ch, 0Ah, 25h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 46h, 04h, 0EBh, 08h
    db 8Bh, 42h, 08h, 89h, 34h, 0B8h, 0FFh, 01h, 6Ah, 08h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h
    db 1Ch, 00h, 00h, 00h, 00h, 0C7h, 06h, 48h, 63h, 13h, 01h, 0E8h, 0D0h, 1Dh, 00h, 00h
    db 8Bh, 4Eh, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 81h, 0C9h, 40h, 00h, 0FFh, 0Fh, 89h
    db 4Eh, 04h, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0089aa20@@YAXXZ ENDP

; ghidra: FUN_00c9ab40  retail @ 0x0089AB40 size 42
public ?d_0089ab40@@YAXXZ
?d_0089ab40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 0DBh, 0C7h, 0FFh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 20h, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0089ab40@@YAXXZ ENDP

; ghidra: FUN_00c9ab70  retail @ 0x0089AB70 size 73
public ?d_0089ab70@@YAXXZ
?d_0089ab70@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C8h, 76h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 48h
    db 63h, 13h, 01h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0CDh
    db 20h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_0089ab70@@YAXXZ ENDP

; ghidra: FUN_00c9abc0  retail @ 0x0089ABC0 size 4137
_TEXT ENDS
_TEXT$d00c9abc0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9ABC0 size 4137
public ?d_0089abc0@@YAXXZ
?d_0089abc0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105790A
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 008h, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 053h, 055h, 056h, 057h
    call ?d_008a30c0@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 033h, 0EDh, 03Bh, 0F5h, 089h, 06Ch, 024h, 020h, 0BFh
    dd g_Va00C98D10
    db 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 083h, 0CBh, 0FFh, 068h
    dd ?g_rva8D0D80CreateTag@@3DA
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 001h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va01338504
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 002h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va013386E4
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 003h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va01338530
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 004h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va01338544
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 005h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va0133870C
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 006h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd ?g_Va013385F8@@3EA
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 007h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va0133873C
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 008h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va013385E8
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 009h, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd g_Va01338548
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 00Ah, 000h, 000h
    db 000h, 074h, 016h, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 089h, 07Eh, 020h, 0EBh, 002h, 033h, 0F6h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 056h, 068h
    dd ?g_rva008C8350Builtin86F4@@3PADA
    db 083h, 0C1h, 008h, 089h, 05Ch, 024h, 028h
    call ?d_0089d890@@YAXXZ
    db 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd ?g_rva8D0D80CreateTag@@3DA
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0F8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 03Bh, 0F5h, 0C7h, 044h, 024h, 020h, 00Bh, 000h, 000h
    db 000h, 074h, 02Ah, 08Bh, 046h, 004h, 025h, 01Ch, 080h, 000h, 0B0h, 00Dh, 01Ch, 080h, 000h, 000h
    db 089h, 046h, 004h, 06Ah, 008h, 08Dh, 04Eh, 008h, 0C6h, 044h, 024h, 024h, 00Ch, 0C7h, 006h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 089h, 06Eh, 018h, 0EBh, 002h, 033h, 0F6h, 08Bh, 017h, 08Bh, 0CFh, 089h, 05Ch, 024h, 020h, 0FFh
    db 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h, 0E0h, 0FEh, 085h, 0F6h, 08Bh, 0D8h, 074h, 006h
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0DBh, 074h, 007h, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h
    db 004h, 085h, 0F6h, 075h, 005h, 089h, 075h, 00Ch, 0EBh, 013h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0DEh
    db 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CBh, 001h, 089h, 05Dh, 00Ch, 089h, 035h
    dd g_Va013379F4
    db 08Bh, 04Fh, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 04Fh, 004h, 08Bh
    db 056h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 056h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va01338504
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 00Eh, 000h, 000h
    db 000h, 074h, 02Eh, 08Bh, 047h, 004h, 025h, 01Ch, 080h, 000h, 0B0h, 00Dh, 01Ch, 080h, 000h, 000h
    db 089h, 047h, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 00Fh, 0C7h, 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va013386E4
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 011h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 012h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va01338530
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 014h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 015h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va01338544
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 017h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 018h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va0133870C
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 01Ah, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 01Bh, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd ?g_Va013385F8@@3EA
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 01Dh, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 01Eh, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 089h, 03Dh
    dd g_Va013379C0
    db 08Bh, 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh
    db 047h, 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 013h, 08Bh
    db 0CBh, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h
    db 00Ch, 083h, 0E0h, 0FEh, 089h, 044h, 024h, 010h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h
    db 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 007h, 08Bh
    db 0CFh, 089h, 07Ch, 024h, 014h, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 005h, 083h, 0CFh, 001h, 0EBh
    db 004h, 08Bh, 07Ch, 024h, 014h, 089h, 07Dh, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 08Bh
    db 0F8h, 08Bh, 047h, 008h, 083h, 0E0h, 0FEh, 08Bh, 0D8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h
    db 0DBh, 074h, 007h, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0DEh
    db 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CBh, 001h, 089h, 05Fh, 008h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va0133873C
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 020h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 021h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va013385E8
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 023h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 024h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd g_Va01338548
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 026h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 027h, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 00Ch, 083h
    db 0E0h, 0FEh, 085h, 0FFh, 089h, 06Ch, 024h, 014h, 089h, 044h, 024h, 010h, 074h, 006h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh, 011h
    db 0FFh, 052h, 004h, 085h, 0FFh, 075h, 005h, 089h, 07Dh, 00Ch, 0EBh, 017h, 08Bh, 007h, 08Bh, 0CFh
    db 08Bh, 0EFh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h
    db 089h, 069h, 00Ch, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 089h, 044h, 024h, 014h, 08Bh, 040h
    db 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h
    db 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 08Bh, 0EEh, 0FFh, 050h
    db 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 04Ch, 024h, 014h, 089h, 069h, 008h, 08Bh
    db 053h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 089h, 053h, 004h, 08Bh, 047h
    db 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 047h, 004h, 08Bh, 00Dh
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 068h
    dd ?g_rva008C8350Builtin86F4@@3PADA
    db 083h, 0C1h, 008h
    call ?d_0089cef0@@YAXXZ
    db 06Ah, 024h, 08Bh, 0D8h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 078h, 008h, 057h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 07Ch, 024h, 014h, 085h, 0FFh, 0C7h, 044h, 024h, 020h, 029h, 000h, 000h
    db 000h, 074h, 030h, 08Bh, 04Fh, 004h, 081h, 0E1h, 01Ch, 080h, 000h, 0B0h, 081h, 0C9h, 01Ch, 080h
    db 000h, 000h, 089h, 04Fh, 004h, 06Ah, 008h, 08Dh, 04Fh, 008h, 0C6h, 044h, 024h, 024h, 02Ah, 0C7h
    db 007h
    dd ??_7Rva00899EB0Object@@6B@
    call ?initialize@Rva0089C860State@@QAEPAV1@H@Z
    db 0C7h, 047h, 018h, 000h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0FFh, 08Bh, 013h, 08Bh, 0CBh, 0C7h
    db 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 052h, 018h, 089h, 044h, 024h, 010h, 08Bh, 040h
    db 00Ch, 083h, 0E0h, 0FEh, 085h, 0FFh, 08Bh, 0E8h, 074h, 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h
    db 085h, 0EDh, 074h, 008h, 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 004h, 085h, 0FFh, 075h, 009h
    db 08Bh, 044h, 024h, 010h, 089h, 078h, 00Ch, 0EBh, 017h, 08Bh, 017h, 08Bh, 0CFh, 08Bh, 0EFh, 0FFh
    db 052h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CDh, 001h, 08Bh, 044h, 024h, 010h, 089h, 068h, 00Ch
    db 08Bh, 013h, 08Bh, 0CBh, 0FFh, 052h, 018h, 08Bh, 0E8h, 08Bh, 045h, 008h, 083h, 0E0h, 0FEh, 089h
    db 044h, 024h, 010h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h
    db 007h, 08Bh, 0C8h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 006h, 08Bh, 0CEh, 089h, 074h, 024h, 014h
    db 0FFh, 050h, 014h, 03Ch, 001h, 075h, 005h, 083h, 0CEh, 001h, 0EBh, 004h, 08Bh, 074h, 024h, 014h
    db 089h, 075h, 008h, 08Bh, 04Bh, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h
    db 04Bh, 004h, 08Bh, 057h, 004h, 081h, 0E2h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0CAh, 040h, 06Ah, 02Ch
    db 089h, 057h, 004h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 014h, 085h, 0F6h, 0C7h, 044h, 024h, 020h, 02Ch, 000h, 000h
    db 000h, 074h, 01Ah, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 0C7h, 046h, 020h
    dd ?rva00899800@@YAPAVAptValue@@PAXH@Z
    db 0EBh, 002h, 033h, 0F6h, 089h, 035h
    dd ?g_bfmeRegisterClass1015@@3HA
    db 08Bh, 046h, 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 046h, 004h, 08Bh, 00Dh
    dd ?g_bfmeRegisterClass1015@@3HA
    db 08Bh, 011h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    call ?d_008a30c0@@YAXXZ
    db 08Bh, 04Ch, 024h, 018h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 014h, 0C3h
?d_0089abc0@@YAXXZ ENDP
_TEXT$d00c9abc0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9bbf0  retail @ 0x0089BBF0 size 1684
public ?d_0089bbf0@@YAXXZ
?d_0089bbf0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 04h, 7Ah, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 6Ah, 08h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h
    db 04h, 85h, 0C0h, 74h, 09h, 8Bh, 0C8h, 0E8h, 54h, 0E4h, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h
    db 68h, 0C0h, 03h, 00h, 00h, 0A3h, 0BCh, 79h, 33h, 01h, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 09h, 8Bh, 0C8h, 0E8h, 0C7h, 6Eh, 03h, 00h, 0EBh, 02h, 33h, 0C0h, 56h, 57h, 83h
    db 0CFh, 0FFh, 6Ah, 08h, 89h, 7Ch, 24h, 18h, 0A3h, 04h, 7Ah, 33h, 01h, 0FFh, 15h, 28h
    db 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0DFh, 0E4h, 0FFh
    db 0FFh, 0EBh, 02h, 33h, 0C0h, 6Ah, 20h, 0A3h, 20h, 7Ah, 33h, 01h, 0FFh, 15h, 28h, 78h
    db 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 75h, 0B6h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h
    db 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0CEh
    db 0E8h, 1Bh, 0E6h, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 6Ah, 28h, 89h, 7Ch, 24h, 18h, 0A3h
    db 0B4h, 79h, 33h, 01h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 3Dh
    db 0B6h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h
    db 02h, 00h, 00h, 00h, 74h, 23h, 6Ah, 08h, 6Ah, 18h, 8Bh, 0CEh, 0E8h, 1Fh, 0E2h, 0FFh
    db 0FFh, 8Bh, 46h, 04h, 25h, 7Fh, 0C0h, 0FFh, 0FFh, 0Dh, 40h, 00h, 0FFh, 0Fh, 0C7h, 06h
    db 38h, 62h, 13h, 01h, 89h, 46h, 04h, 0EBh, 02h, 33h, 0F6h, 6Ah, 20h, 89h, 7Ch, 24h
    db 18h, 89h, 35h, 0FCh, 79h, 33h, 01h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h
    db 56h, 0E8h, 0EAh, 0B5h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h
    db 44h, 24h, 14h, 03h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0CEh, 0E8h, 10h, 0E8h, 0FFh, 0FFh
    db 0EBh, 02h, 33h, 0C0h, 6Ah, 20h, 89h, 7Ch, 24h, 18h, 0A3h, 0ACh, 79h, 33h, 01h, 0FFh
    db 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 0B2h, 0B5h, 0FFh, 0FFh, 83h, 0C4h
    db 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h, 04h, 00h, 00h, 00h, 74h
    db 09h, 8Bh, 0CEh, 0E8h, 78h, 0E9h, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 6Ah, 20h, 89h, 7Ch
    db 24h, 18h, 0A3h, 0D8h, 87h, 33h, 01h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h
    db 56h, 0E8h, 7Ah, 0B5h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h
    db 44h, 24h, 14h, 05h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0CEh, 0E8h, 0E0h, 0EAh, 0FFh, 0FFh
    db 0EBh, 02h, 33h, 0C0h, 6Ah, 20h, 89h, 7Ch, 24h, 18h, 0A3h, 6Ch, 84h, 33h, 01h, 0FFh
    db 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 42h, 0B5h, 0FFh, 0FFh, 83h, 0C4h
    db 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h, 06h, 00h, 00h, 00h, 74h
    db 09h, 8Bh, 0CEh, 0E8h, 48h, 0ECh, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 8Bh, 35h, 78h, 84h
    db 33h, 01h, 85h, 0F6h, 89h, 7Ch, 24h, 14h, 0A3h, 00h, 7Ah, 33h, 01h, 74h, 46h, 8Bh
    db 4Eh, 0Ch, 89h, 0Dh, 78h, 84h, 33h, 01h, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 8Bh, 51h
    db 04h, 55h, 8Bh, 29h, 8Dh, 41h, 04h, 3Bh, 0D5h, 5Dh, 7Ch, 09h, 81h, 66h, 04h, 0FFh
    db 0FFh, 0FFh, 0BFh, 0EBh, 08h, 8Bh, 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h, 08h
    db 3Dh, 98h, 52h, 2Dh, 01h, 8Dh, 4Eh, 08h, 74h, 07h, 6Ah, 00h, 0E8h, 1Fh, 2Eh, 00h
    db 00h, 8Bh, 0C6h, 0EBh, 2Ah, 6Ah, 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 08h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 07h, 00h, 00h, 00h, 74h, 09h
    db 8Bh, 0C8h, 0E8h, 0A9h, 0DCh, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 89h, 7Ch, 24h, 14h, 0A3h
    db 0F0h, 79h, 33h, 01h, 8Bh, 50h, 04h, 81h, 0E2h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0CAh, 40h
    db 89h, 50h, 04h, 8Bh, 0Dh, 0F0h, 79h, 33h, 01h, 8Bh, 01h, 0FFh, 10h, 0C7h, 05h, 28h
    db 7Ah, 33h, 01h, 00h, 00h, 00h, 00h, 0E8h, 34h, 0EDh, 0FFh, 0FFh, 6Ah, 2Ch, 0C7h, 05h
    db 0CCh, 79h, 33h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 0D0h, 79h, 33h, 01h, 00h, 00h
    db 80h, 3Fh, 0C7h, 05h, 0D4h, 79h, 33h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 0D8h, 79h
    db 33h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 0DCh, 79h, 33h, 01h, 00h, 00h, 00h, 00h
    db 0C7h, 05h, 0E0h, 79h, 33h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0E4h, 79h, 33h, 01h
    db 00h, 00h, 00h, 00h, 0C7h, 05h, 0E8h, 79h, 33h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h
    db 08h, 7Ah, 33h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 0Ch, 7Ah, 33h, 01h, 00h, 00h
    db 00h, 00h, 0C7h, 05h, 10h, 7Ah, 33h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 14h, 7Ah
    db 33h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 18h, 7Ah, 33h, 01h, 00h, 00h, 00h, 00h
    db 0C7h, 05h, 1Ch, 7Ah, 33h, 01h, 00h, 00h, 00h, 00h, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 8Dh, 70h, 08h, 56h, 0E8h, 0D7h, 0B3h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h
    db 85h, 0F6h, 0C7h, 44h, 24h, 14h, 08h, 00h, 00h, 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h
    db 8Bh, 0CEh, 0E8h, 0B9h, 0DFh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h, 01h, 0C7h, 46h, 20h
    db 0C0h, 64h, 0CCh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h, 0ECh, 79h, 33h, 01h, 8Bh, 4Eh
    db 04h, 81h, 0E1h, 0FFh, 0FFh, 64h, 0F0h, 81h, 0C9h, 00h, 00h, 64h, 00h, 89h, 4Eh, 04h
    db 0A1h, 0ECh, 79h, 33h, 01h, 8Bh, 50h, 04h, 83h, 0C0h, 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh
    db 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h, 89h, 10h, 6Ah, 2Ch, 89h, 7Ch, 24h, 18h, 89h, 08h
    db 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 61h, 0B3h, 0FFh, 0FFh, 83h
    db 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h, 09h, 00h, 00h, 00h
    db 74h, 1Ah, 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 43h, 0DFh, 0FFh, 0FFh, 0C7h, 06h, 28h
    db 61h, 13h, 01h, 0C7h, 46h, 20h, 0A0h, 66h, 0CCh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h
    db 0C4h, 79h, 33h, 01h, 8Bh, 56h, 04h, 81h, 0E2h, 0FFh, 0FFh, 64h, 0F0h, 81h, 0CAh, 00h
    db 00h, 64h, 00h, 89h, 56h, 04h, 0A1h, 0C4h, 79h, 33h, 01h, 8Bh, 50h, 04h, 83h, 0C0h
    db 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh, 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h, 89h, 10h, 6Ah, 2Ch
    db 89h, 7Ch, 24h, 18h, 89h, 08h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h
    db 0E8h, 0EBh, 0B2h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h
    db 24h, 14h, 0Ah, 00h, 00h, 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 0CDh
    db 0DEh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h, 01h, 0C7h, 46h, 20h, 00h, 68h, 0CCh, 00h
    db 0EBh, 02h, 33h, 0F6h, 89h, 35h, 0C8h, 79h, 33h, 01h, 8Bh, 46h, 04h, 25h, 0FFh, 0FFh
    db 64h, 0F0h, 0Dh, 00h, 00h, 64h, 00h, 89h, 46h, 04h, 0A1h, 0C8h, 79h, 33h, 01h, 8Bh
    db 50h, 04h, 83h, 0C0h, 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh, 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h
    db 89h, 10h, 6Ah, 2Ch, 89h, 7Ch, 24h, 18h, 89h, 08h, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 8Dh, 70h, 08h, 56h, 0E8h, 77h, 0B2h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h
    db 85h, 0F6h, 0C7h, 44h, 24h, 14h, 0Bh, 00h, 00h, 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h
    db 8Bh, 0CEh, 0E8h, 59h, 0DEh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h, 01h, 0C7h, 46h, 20h
    db 40h, 68h, 0CCh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h, 0F8h, 79h, 33h, 01h, 8Bh, 4Eh
    db 04h, 81h, 0E1h, 0FFh, 0FFh, 64h, 0F0h, 81h, 0C9h, 00h, 00h, 64h, 00h, 89h, 4Eh, 04h
    db 0A1h, 0F8h, 79h, 33h, 01h, 8Bh, 50h, 04h, 83h, 0C0h, 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh
    db 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h, 89h, 10h, 6Ah, 2Ch, 89h, 7Ch, 24h, 18h, 89h, 08h
    db 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 01h, 0B2h, 0FFh, 0FFh, 83h
    db 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h, 24h, 14h, 0Ch, 00h, 00h, 00h
    db 74h, 1Ah, 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 0E3h, 0DDh, 0FFh, 0FFh, 0C7h, 06h, 28h
    db 61h, 13h, 01h, 0C7h, 46h, 20h, 90h, 69h, 0CCh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h
    db 0B8h, 79h, 33h, 01h, 8Bh, 56h, 04h, 81h, 0E2h, 0FFh, 0FFh, 64h, 0F0h, 81h, 0CAh, 00h
    db 00h, 64h, 00h, 89h, 56h, 04h, 0A1h, 0B8h, 79h, 33h, 01h, 8Bh, 50h, 04h, 83h, 0C0h
    db 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh, 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h, 89h, 10h, 6Ah, 2Ch
    db 89h, 7Ch, 24h, 18h, 89h, 08h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h
    db 0E8h, 8Bh, 0B1h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h, 85h, 0F6h, 0C7h, 44h
    db 24h, 14h, 0Dh, 00h, 00h, 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 6Dh
    db 0DDh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h, 01h, 0C7h, 46h, 20h, 0D0h, 6Ah, 0CCh, 00h
    db 0EBh, 02h, 33h, 0F6h, 89h, 35h, 0B0h, 79h, 33h, 01h, 8Bh, 46h, 04h, 25h, 0FFh, 0FFh
    db 64h, 0F0h, 0Dh, 00h, 00h, 64h, 00h, 89h, 46h, 04h, 0A1h, 0B0h, 79h, 33h, 01h, 8Bh
    db 50h, 04h, 83h, 0C0h, 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh, 0FFh, 8Bh, 0CAh, 83h, 0C9h, 40h
    db 89h, 10h, 6Ah, 2Ch, 89h, 7Ch, 24h, 18h, 89h, 08h, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 8Dh, 70h, 08h, 56h, 0E8h, 17h, 0B1h, 0FFh, 0FFh, 83h, 0C4h, 08h, 89h, 74h, 24h, 08h
    db 85h, 0F6h, 0C7h, 44h, 24h, 14h, 0Eh, 00h, 00h, 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h
    db 8Bh, 0CEh, 0E8h, 0F9h, 0DCh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h, 01h, 0C7h, 46h, 20h
    db 90h, 4Fh, 0CCh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h, 2Ch, 7Ah, 33h, 01h, 8Bh, 4Eh
    db 04h, 81h, 0E1h, 0FFh, 0FFh, 64h, 0F0h, 81h, 0C9h, 00h, 00h, 64h, 00h, 89h, 4Eh, 04h
    db 0A1h, 2Ch, 7Ah, 33h, 01h, 8Bh, 50h, 04h, 83h, 0C0h, 04h, 81h, 0E2h, 3Fh, 0C0h, 0FFh
    db 0FFh, 89h, 10h, 8Bh, 0CAh, 83h, 0C9h, 40h, 89h, 08h, 8Bh, 0Dh, 10h, 78h, 33h, 01h
    db 33h, 0D2h, 89h, 15h, 0B0h, 87h, 33h, 01h, 89h, 15h, 0B4h, 87h, 33h, 01h, 89h, 15h
    db 0B8h, 87h, 33h, 01h, 89h, 7Ch, 24h, 14h, 89h, 15h, 0BCh, 87h, 33h, 01h, 0E8h, 4Dh
    db 6Eh, 00h, 00h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_0089bbf0@@YAXXZ ENDP

; ghidra: FUN_00c9c680  retail @ 0x0089C680 size 83
public ?d_0089c680@@YAXXZ
?d_0089c680@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 0Ch, 8Bh, 0D9h, 8Bh, 43h, 04h, 56h, 8Bh, 74h, 24h, 14h
    db 8Bh, 16h, 57h, 8Bh, 7Ch, 0E8h, 04h, 8Bh, 0CEh, 83h, 0E7h, 0FEh, 0FFh, 12h, 85h, 0FFh
    db 74h, 07h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 04h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 14h
    db 3Ch, 01h, 75h, 11h, 8Bh, 43h, 04h, 83h, 0CEh, 01h, 5Fh, 89h, 74h, 0E8h, 04h, 5Eh
    db 5Dh, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Bh, 04h, 5Fh, 89h, 74h, 0E9h, 04h, 5Eh, 5Dh, 5Bh
    db 0C2h, 08h, 00h
?d_0089c680@@YAXXZ ENDP

; ghidra: FUN_00c9c6e0  retail @ 0x0089C6E0 size 60
public ?d_0089c6e0@@YAXXZ
?d_0089c6e0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 8Bh, 0F9h, 8Bh, 0CEh, 0FFh, 10h, 8Bh, 16h
    db 8Bh, 0CEh, 0FFh, 52h, 14h, 3Ch, 01h, 75h, 13h, 8Bh, 47h, 04h, 8Bh, 4Ch, 24h, 0Ch
    db 83h, 0CEh, 01h, 5Fh, 89h, 74h, 0C8h, 04h, 5Eh, 0C2h, 08h, 00h, 8Bh, 57h, 04h, 8Bh
    db 44h, 24h, 0Ch, 5Fh, 89h, 74h, 0C2h, 04h, 5Eh, 0C2h, 08h, 00h
?d_0089c6e0@@YAXXZ ENDP

; ghidra: FUN_00c9c750  retail @ 0x0089C750 size 27
public ?d_0089c750@@YAXXZ
?d_0089c750@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 0Fh, 83h, 0E1h, 0FEh, 8Bh, 01h, 0FFh
    db 50h, 04h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0089c750@@YAXXZ ENDP

; ghidra: FUN_00c9c780  retail @ 0x0089C780 size 27
public ?d_0089c780@@YAXXZ
?d_0089c780@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 0Ch, 85h, 0C9h, 74h, 0Fh, 83h, 0E1h, 0FEh, 8Bh, 01h, 0FFh
    db 50h, 04h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0089c780@@YAXXZ ENDP

; ghidra: FUN_00c9c7f0  retail @ 0x0089C7F0 size 33
public ?d_0089c7f0@@YAXXZ
?d_0089c7f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 66h, 0FFh, 08h, 66h, 8Bh, 08h, 75h, 0Ch, 50h, 0A1h, 30h
    db 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 0C7h, 06h, 00h, 00h, 00h, 00h, 5Eh
    db 0C3h
?d_0089c7f0@@YAXXZ ENDP

; ghidra: FUN_00c9c830  retail @ 0x0089C830 size 33
public ?d_0089c830@@YAXXZ
?d_0089c830@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 66h, 83h, 78h, 06h, 00h, 75h, 0Dh, 0E8h, 0BFh, 1Eh, 00h
    db 00h, 8Bh, 0Eh, 66h, 8Bh, 41h, 06h, 5Eh, 0C3h, 8Bh, 16h, 66h, 8Bh, 42h, 06h, 5Eh
    db 0C3h
?d_0089c830@@YAXXZ ENDP

; ghidra: FUN_00c9c860  retail @ 0x0089C860 size 22
public ?d_0089c860@@YAXXZ
?d_0089c860@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 04h, 89h, 08h, 33h, 0C9h, 89h, 48h, 04h, 89h, 48h, 08h
    db 89h, 48h, 0Ch, 0C2h, 04h, 00h
?d_0089c860@@YAXXZ ENDP

; ghidra: FUN_00c9c880  retail @ 0x0089C880 size 124
public ?d_0089c880@@YAXXZ
?d_0089c880@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 0Ch, 33h, 0DBh, 3Bh, 0C3h, 74h, 11h, 0A8h, 01h, 74h
    db 0Dh, 83h, 0E0h, 0FEh, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 04h, 89h, 5Eh, 0Ch, 8Bh, 46h
    db 08h, 3Bh, 0C3h, 74h, 11h, 0A8h, 01h, 74h, 0Dh, 83h, 0E0h, 0FEh, 8Bh, 10h, 8Bh, 0C8h
    db 0FFh, 52h, 04h, 89h, 5Eh, 08h, 39h, 5Eh, 04h, 74h, 3Eh, 8Bh, 06h, 57h, 33h, 0FFh
    db 3Bh, 0C3h, 7Eh, 34h, 8Bh, 46h, 04h, 8Bh, 0Ch, 0F8h, 3Bh, 0CBh, 8Dh, 04h, 0F8h, 74h
    db 20h, 81h, 0F9h, 98h, 52h, 2Dh, 01h, 74h, 18h, 8Bh, 40h, 04h, 0A8h, 01h, 74h, 11h
    db 83h, 0E0h, 0FEh, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 04h, 8Bh, 46h, 04h, 89h, 5Ch, 0F8h
    db 04h, 8Bh, 06h, 47h, 3Bh, 0F8h, 7Ch, 0CCh, 5Fh, 5Eh, 5Bh, 0C3h
?d_0089c880@@YAXXZ ENDP

; ghidra: FUN_00c9c900  retail @ 0x0089C900 size 180
public ?d_0089c900@@YAXXZ
?d_0089c900@@YAXXZ PROC
    db 55h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 0Ch, 33h, 0EDh, 3Bh, 0CDh, 74h, 0Dh, 0F6h, 0C1h, 01h
    db 75h, 08h, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 6Fh, 0Ch, 8Bh, 4Fh, 08h, 3Bh, 0CDh, 74h
    db 0Dh, 0F6h, 0C1h, 01h, 75h, 08h, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 6Fh, 08h, 39h, 6Fh
    db 04h, 74h, 7Eh, 39h, 2Fh, 7Eh, 66h, 53h, 56h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 47h, 04h, 8Dh, 1Ch, 0EDh, 00h, 00h, 00h, 00h, 8Bh, 0Ch, 18h, 03h, 0C3h, 85h
    db 0C9h, 74h, 41h, 81h, 0F9h, 98h, 52h, 2Dh, 01h, 74h, 16h, 8Bh, 40h, 04h, 8Bh, 0C8h
    db 83h, 0E1h, 0FEh, 74h, 0Ch, 0A8h, 01h, 75h, 08h, 83h, 0E1h, 0FEh, 8Bh, 11h, 0FFh, 52h
    db 04h, 8Bh, 77h, 04h, 8Bh, 04h, 1Eh, 03h, 0F3h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h
    db 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 0C7h, 06h
    db 00h, 00h, 00h, 00h, 8Bh, 07h, 45h, 3Bh, 0E8h, 7Ch, 0A5h, 5Eh, 5Bh, 8Bh, 4Fh, 04h
    db 51h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 83h, 0C4h, 04h, 0C7h, 47h, 04h, 00h, 00h, 00h
    db 00h, 5Fh, 5Dh, 0C3h
?d_0089c900@@YAXXZ ENDP

; ghidra: FUN_00c9c9e0  retail @ 0x0089C9E0 size 48
public ?d_0089c9e0@@YAXXZ
?d_0089c9e0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0C1h, 0E0h, 03h, 57h, 50h, 0FFh, 15h, 28h, 78h, 33h, 01h
    db 8Bh, 0Eh, 0C1h, 0E1h, 03h, 8Bh, 0D1h, 8Bh, 0F8h, 0C1h, 0E9h, 02h, 89h, 7Eh, 04h, 33h
    db 0C0h, 0F3h, 0ABh, 8Bh, 0CAh, 83h, 0C4h, 04h, 83h, 0E1h, 03h, 0F3h, 0AAh, 5Fh, 5Eh, 0C3h
?d_0089c9e0@@YAXXZ ENDP

; ghidra: FUN_00c9cba0  retail @ 0x0089CBA0 size 107
public ?d_0089cba0@@YAXXZ
?d_0089cba0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 0D9h, 8Bh, 03h, 57h, 33h, 0FFh, 85h, 0C0h, 7Eh, 4Bh, 8Bh, 6Ch
    db 24h, 14h, 8Bh, 43h, 04h, 8Dh, 34h, 0F8h, 8Bh, 06h, 85h, 0C0h, 74h, 34h, 3Dh, 98h
    db 52h, 2Dh, 01h, 74h, 2Dh, 8Bh, 4Dh, 00h, 3Bh, 0C1h, 74h, 36h, 66h, 8Bh, 50h, 06h
    db 66h, 3Bh, 51h, 06h, 75h, 1Ch, 83h, 0C1h, 08h, 51h, 83h, 0C0h, 08h, 50h, 0E8h, 0BDh
    db 0A3h, 15h, 00h, 83h, 0C4h, 08h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 88h, 44h, 24h, 14h
    db 75h, 10h, 8Bh, 03h, 47h, 3Bh, 0F8h, 7Ch, 0B9h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 0C2h
    db 04h, 00h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h
?d_0089cba0@@YAXXZ ENDP

; ghidra: FUN_00c9cc10  retail @ 0x0089CC10 size 18
public ?d_0089cc10@@YAXXZ
?d_0089cc10@@YAXXZ PROC
    db 8Bh, 51h, 04h, 85h, 0D2h, 0B8h, 02h, 00h, 00h, 00h, 74h, 05h, 8Bh, 01h, 83h, 0C0h
    db 02h, 0C3h
?d_0089cc10@@YAXXZ ENDP

; ghidra: FUN_00c9cc30  retail @ 0x0089CC30 size 51
public ?d_0089cc30@@YAXXZ
?d_0089cc30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 05h, 8Bh, 49h, 08h, 0EBh, 15h, 83h, 0F8h, 01h
    db 75h, 05h, 8Bh, 49h, 0Ch, 0EBh, 0Bh, 8Bh, 49h, 04h, 85h, 0C9h, 74h, 10h, 8Bh, 4Ch
    db 0C1h, 0F4h, 8Bh, 0C1h, 83h, 0E0h, 0FEh, 74h, 07h, 0F6h, 0C1h, 01h, 75h, 02h, 33h, 0C0h
    db 0C2h, 04h, 00h
?d_0089cc30@@YAXXZ ENDP

; ghidra: FUN_00c9cc80  retail @ 0x0089CC80 size 617
_TEXT ENDS
_TEXT$d00c9cc80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9CC80 size 617
public ?d_0089cc80@@YAXXZ
?d_0089cc80@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 056h, 08Bh, 074h, 024h, 014h, 08Bh, 006h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 057h, 08Bh, 0F9h, 00Fh, 084h, 049h, 002h, 000h, 000h, 066h, 083h, 078h, 006h, 000h, 075h, 007h
    db 08Bh, 0CEh
    call ?bfmeInit929G@BfmeThing929G@@QAEXXZ
    db 08Bh, 016h, 08Bh, 047h, 004h, 085h, 0C0h, 053h, 055h, 066h, 08Bh, 06Ah, 006h, 00Fh, 0B7h, 0CDh
    db 089h, 04Ch, 024h, 018h, 00Fh, 084h, 054h, 001h, 000h, 000h, 08Bh, 037h, 04Eh, 023h, 0F1h, 08Dh
    db 01Ch, 0F5h, 000h, 000h, 000h, 000h, 08Bh, 00Ch, 003h, 085h, 0C9h, 00Fh, 084h, 035h, 001h, 000h
    db 000h, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 032h, 08Bh, 0C1h, 03Bh, 0C2h, 074h, 022h, 066h, 039h, 068h, 006h, 075h, 026h, 083h, 0C2h
    db 008h, 052h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 074h, 00Ah, 08Bh
    db 077h, 004h, 003h, 0F3h, 0E9h, 054h, 001h, 000h, 000h, 08Bh, 00Fh, 08Dh, 046h, 0F8h, 033h, 0D2h
    db 03Bh, 0C2h, 089h, 044h, 024h, 014h, 07Dh, 012h, 0B8h, 010h, 000h, 000h, 000h, 03Bh, 0C8h, 089h
    db 054h, 024h, 014h, 07Fh, 01Eh, 08Dh, 041h, 0FFh, 0EBh, 019h, 08Dh, 046h, 008h, 049h, 03Bh, 0C1h
    db 07Eh, 011h, 08Bh, 0C1h, 08Dh, 048h, 0F0h, 03Bh, 0CAh, 089h, 04Ch, 024h, 014h, 07Dh, 004h, 089h
    db 054h, 024h, 014h, 02Bh, 0C6h, 08Bh, 0DEh, 08Bh, 0E8h, 074h, 059h, 08Bh, 047h, 004h, 04Dh, 043h
    db 08Bh, 00Ch, 0D8h, 085h, 0C9h, 08Dh, 004h, 0D8h, 00Fh, 084h, 0A6h, 000h, 000h, 000h, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 03Ah, 08Bh, 0C1h, 08Bh, 04Ch, 024h, 020h, 08Bh, 009h, 03Bh, 0C1h, 00Fh, 084h, 0E1h, 000h
    db 000h, 000h, 066h, 08Bh, 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 020h, 083h, 0C1h, 008h, 051h
    db 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 00Fh, 085h, 0B7h
    db 000h, 000h, 000h, 085h, 0EDh, 075h, 0A7h, 08Bh, 044h, 024h, 014h, 08Bh, 0DEh, 02Bh, 0F0h, 089h
    db 074h, 024h, 014h, 074h, 052h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 04Fh, 004h, 04Bh, 08Dh
    db 004h, 0D9h, 08Bh, 008h, 04Eh, 085h, 0C9h, 074h, 03Eh, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 032h, 08Bh, 054h, 024h, 020h, 08Bh, 0C1h, 08Bh, 00Ah, 03Bh, 0C1h, 074h, 07Dh, 066h, 08Bh
    db 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 01Ch, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 075h, 057h, 085h
    db 0F6h, 075h, 0B4h, 08Bh, 074h, 024h, 020h, 08Bh, 04Ch, 024h, 018h, 081h, 0F9h, 099h, 006h, 000h
    db 000h, 00Fh, 085h, 08Ah, 000h, 000h, 000h, 08Bh, 006h, 083h, 0C0h, 008h, 068h
    dd g_Va01136034
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 0A4h, 000h, 000h, 000h, 08Bh, 04Fh, 00Ch, 085h, 0C9h
    db 00Fh, 084h, 099h, 000h, 000h, 000h, 083h, 0E1h, 0FEh, 08Bh, 011h, 0FFh, 052h, 004h, 05Dh, 05Bh
    db 0C7h, 047h, 00Ch, 000h, 000h, 000h, 000h, 05Fh, 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h, 08Bh
    db 047h, 004h, 08Dh, 034h, 0D8h, 085h, 0F6h, 074h, 0A3h, 08Bh, 006h, 066h, 0FFh, 008h, 066h, 083h
    db 038h, 000h, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 0C7h, 006h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Bh, 04Eh, 004h, 083h, 0E1h, 0FEh, 08Bh, 011h, 0FFh, 052h, 004h, 05Dh, 05Bh, 05Fh, 0C7h, 046h
    db 004h, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h, 081h, 0F9h, 0BDh, 06Bh
    db 000h, 000h, 075h, 02Dh, 08Bh, 006h, 083h, 0C0h, 008h, 068h
    dd g_Va01136040
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 016h, 08Bh, 04Fh, 008h, 085h, 0C9h, 074h, 00Fh, 083h, 0E1h
    db 0FEh, 08Bh, 011h, 0FFh, 052h, 004h, 0C7h, 047h, 008h, 000h, 000h, 000h, 000h, 05Dh, 05Bh, 05Fh
    db 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h
?d_0089cc80@@YAXXZ ENDP
_TEXT$d00c9cc80 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9cef0  retail @ 0x0089CEF0 size 520
_TEXT ENDS
_TEXT$d00c9cef0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9CEF0 size 520
public ?d_0089cef0@@YAXXZ
?d_0089cef0@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 053h, 055h, 056h, 08Bh, 074h, 024h, 01Ch, 08Bh, 006h, 066h, 083h, 078h, 006h
    db 000h, 057h, 08Bh, 0F9h, 075h, 007h, 08Bh, 0CEh
    call ?bfmeInit929G@BfmeThing929G@@QAEXXZ
    db 08Bh, 016h, 066h, 08Bh, 06Ah, 006h, 08Bh, 047h, 004h, 085h, 0C0h, 00Fh, 0B7h, 0CDh, 089h, 04Ch
    db 024h, 018h, 00Fh, 084h, 04Fh, 001h, 000h, 000h, 08Bh, 037h, 04Eh, 023h, 0F1h, 08Dh, 01Ch, 0F5h
    db 000h, 000h, 000h, 000h, 08Bh, 00Ch, 003h, 085h, 0C9h, 00Fh, 084h, 030h, 001h, 000h, 000h, 081h
    db 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 032h, 08Bh, 0C1h, 03Bh, 0C2h, 074h, 022h, 066h, 039h, 068h, 006h, 075h, 026h, 083h, 0C2h
    db 008h, 052h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 074h, 00Ah, 08Bh
    db 047h, 004h, 003h, 0C3h, 0E9h, 033h, 001h, 000h, 000h, 08Bh, 00Fh, 08Dh, 046h, 0F8h, 033h, 0D2h
    db 03Bh, 0C2h, 089h, 044h, 024h, 014h, 07Dh, 012h, 0B8h, 010h, 000h, 000h, 000h, 03Bh, 0C8h, 089h
    db 054h, 024h, 014h, 07Fh, 01Eh, 08Dh, 041h, 0FFh, 0EBh, 019h, 08Dh, 046h, 008h, 049h, 03Bh, 0C1h
    db 07Eh, 011h, 08Bh, 0C1h, 08Dh, 048h, 0F0h, 03Bh, 0CAh, 089h, 04Ch, 024h, 014h, 07Dh, 004h, 089h
    db 054h, 024h, 014h, 02Bh, 0C6h, 08Bh, 0DEh, 08Bh, 0E8h, 074h, 058h, 08Bh, 04Fh, 004h, 04Dh, 043h
    db 08Dh, 004h, 0D9h, 08Bh, 008h, 085h, 0C9h, 00Fh, 084h, 0A2h, 000h, 000h, 000h, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 03Ah, 08Bh, 054h, 024h, 020h, 08Bh, 0C1h, 08Bh, 00Ah, 03Bh, 0C1h, 00Fh, 084h, 0C1h, 000h
    db 000h, 000h, 066h, 08Bh, 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 020h, 083h, 0C1h, 008h, 051h
    db 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 00Fh, 085h, 097h
    db 000h, 000h, 000h, 085h, 0EDh, 075h, 0A8h, 08Bh, 044h, 024h, 014h, 08Bh, 0DEh, 02Bh, 0F0h, 089h
    db 074h, 024h, 014h, 074h, 04Eh, 08Bh, 0FFh, 08Bh, 04Fh, 004h, 04Bh, 08Dh, 004h, 0D9h, 08Bh, 008h
    db 04Eh, 085h, 0C9h, 074h, 03Eh, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 032h, 08Bh, 054h, 024h, 020h, 08Bh, 0C1h, 08Bh, 00Ah, 03Bh, 0C1h, 074h, 061h, 066h, 08Bh
    db 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 01Ch, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 075h, 03Bh, 085h
    db 0F6h, 075h, 0B4h, 08Bh, 04Ch, 024h, 018h, 08Bh, 074h, 024h, 020h, 081h, 0F9h, 099h, 006h, 000h
    db 000h, 075h, 041h, 08Bh, 00Eh, 083h, 0C1h, 008h, 068h
    dd g_Va01136034
    db 051h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 059h, 08Bh, 047h, 00Ch, 05Fh, 05Eh, 05Dh, 083h, 0E0h, 0FEh
    db 05Bh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h, 08Bh, 047h, 004h, 08Dh, 004h, 0D8h, 085h, 0C0h, 074h
    db 0BFh, 08Bh, 040h, 004h, 05Fh, 05Eh, 05Dh, 083h, 0E0h, 0FEh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 004h
    db 000h, 081h, 0F9h, 0BDh, 06Bh, 000h, 000h, 075h, 027h, 08Bh, 016h, 083h, 0C2h, 008h, 068h
    dd g_Va01136040
    db 052h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 010h, 08Bh, 047h, 008h, 05Fh, 05Eh, 05Dh, 083h, 0E0h, 0FEh
    db 05Bh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h, 05Fh, 05Eh, 05Dh, 033h, 0C0h, 05Bh, 083h, 0C4h, 00Ch
    db 0C2h, 004h, 000h
?d_0089cef0@@YAXXZ ENDP
_TEXT$d00c9cef0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9d100  retail @ 0x0089D100 size 55
public ?d_0089d100@@YAXXZ
?d_0089d100@@YAXXZ PROC
    db 57h, 8Bh, 79h, 04h, 85h, 0FFh, 75h, 04h, 33h, 0C0h, 5Fh, 0C3h, 56h, 8Bh, 31h, 33h
    db 0D2h, 85h, 0F6h, 7Eh, 17h, 8Bh, 0CFh, 8Bh, 01h, 85h, 0C0h, 74h, 07h, 3Dh, 98h, 52h
    db 2Dh, 01h, 75h, 0Dh, 42h, 83h, 0C1h, 08h, 3Bh, 0D6h, 7Ch, 0EBh, 5Eh, 33h, 0C0h, 5Fh
    db 0C3h, 5Eh, 8Dh, 04h, 0D7h, 5Fh, 0C3h
?d_0089d100@@YAXXZ ENDP

; ghidra: FUN_00c9d140  retail @ 0x0089D140 size 49
public ?d_0089d140@@YAXXZ
?d_0089d140@@YAXXZ PROC
    db 8Bh, 51h, 04h, 85h, 0D2h, 74h, 25h, 8Bh, 44h, 24h, 04h, 8Bh, 09h, 83h, 0C0h, 08h
    db 8Dh, 14h, 0CAh, 3Bh, 0C2h, 73h, 15h, 8Bh, 08h, 85h, 0C9h, 74h, 08h, 81h, 0F9h, 98h
    db 52h, 2Dh, 01h, 75h, 09h, 83h, 0C0h, 08h, 3Bh, 0C2h, 72h, 0EBh, 33h, 0C0h, 0C2h, 04h
    db 00h
?d_0089d140@@YAXXZ ENDP

; ghidra: FUN_00c9d4c0  retail @ 0x0089D4C0 size 238
public ?d_0089d4c0@@YAXXZ
?d_0089d4c0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 75h, 07h, 0B0h, 01h, 5Eh
    db 83h, 0C4h, 08h, 0C3h, 68h, 80h, 84h, 33h, 01h, 8Bh, 0CEh, 0E8h, 0C0h, 0F6h, 0FFh, 0FFh
    db 85h, 0C0h, 75h, 10h, 68h, 60h, 86h, 33h, 01h, 8Bh, 0CEh, 0E8h, 0B0h, 0F6h, 0FFh, 0FFh
    db 85h, 0C0h, 74h, 07h, 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C3h, 8Bh, 06h, 53h, 55h, 33h
    db 0EDh, 85h, 0C0h, 57h, 0Fh, 8Eh, 90h, 00h, 00h, 00h, 0BFh, 01h, 00h, 00h, 00h, 89h
    db 7Ch, 24h, 14h, 8Bh, 46h, 04h, 8Dh, 1Ch, 0E8h, 8Bh, 03h, 85h, 0C0h, 74h, 67h, 3Dh
    db 98h, 52h, 2Dh, 01h, 74h, 60h, 53h, 8Bh, 0CEh, 0E8h, 0C2h, 0F9h, 0FFh, 0FFh, 85h, 0C0h
    db 74h, 72h, 8Bh, 4Ch, 24h, 14h, 3Bh, 0Eh, 7Dh, 4Ch, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 56h, 04h, 8Dh, 04h, 0FAh, 8Bh, 00h, 85h, 0C0h, 74h, 3Ah, 3Dh, 98h, 52h, 2Dh
    db 01h, 74h, 2Ch, 8Bh, 0Bh, 3Bh, 0C1h, 74h, 4Bh, 66h, 8Bh, 50h, 06h, 66h, 3Bh, 51h
    db 06h, 75h, 1Ch, 83h, 0C1h, 08h, 51h, 83h, 0C0h, 08h, 50h, 0E8h, 30h, 9Ah, 15h, 00h
    db 83h, 0C4h, 08h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 88h, 44h, 24h, 13h, 75h, 25h, 8Bh
    db 06h, 47h, 3Bh, 0F8h, 7Ch, 0BAh, 8Bh, 7Ch, 24h, 14h, 8Bh, 06h, 45h, 47h, 3Bh, 0E8h
    db 89h, 7Ch, 24h, 14h, 0Fh, 8Ch, 79h, 0FFh, 0FFh, 0FFh, 5Fh, 5Dh, 5Bh, 0B0h, 01h, 5Eh
    db 83h, 0C4h, 08h, 0C3h, 5Fh, 5Dh, 5Bh, 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C3h
?d_0089d4c0@@YAXXZ ENDP

; ghidra: FUN_00c9d5b0  retail @ 0x0089D5B0 size 731
_TEXT ENDS
_TEXT$d00c9d5b0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9D5B0 size 731
public ?d_0089d5b0@@YAXXZ
?d_0089d5b0@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 08Bh, 044h, 024h, 010h, 08Bh, 000h, 053h, 066h, 08Bh, 058h, 006h, 055h, 056h
    db 057h, 08Bh, 0F9h, 08Bh, 037h, 08Bh, 057h, 004h, 00Fh, 0B7h, 0CBh, 04Eh, 023h, 0F1h, 08Dh, 00Ch
    db 0F2h, 08Bh, 011h, 033h, 0EDh, 03Bh, 0D5h, 0C7h, 044h, 024h, 014h, 0FFh, 0FFh, 0FFh, 0FFh, 00Fh
    db 084h, 09Fh, 001h, 000h, 000h, 0EBh, 009h, 033h, 0EDh, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 081h, 0FAh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 075h, 006h, 089h, 074h, 024h, 014h, 0EBh, 030h, 08Bh, 009h, 03Bh, 0C8h, 00Fh, 084h, 0BCh, 001h
    db 000h, 000h, 066h, 039h, 059h, 006h, 075h, 020h, 083h, 0C0h, 008h, 050h, 083h, 0C1h, 008h, 051h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 00Fh, 085h, 096h
    db 001h, 000h, 000h, 08Bh, 00Fh, 08Dh, 046h, 0F8h, 03Bh, 0C5h, 089h, 044h, 024h, 018h, 07Dh, 012h
    db 0B8h, 010h, 000h, 000h, 000h, 03Bh, 0C8h, 089h, 06Ch, 024h, 018h, 07Fh, 01Eh, 08Dh, 041h, 0FFh
    db 0EBh, 019h, 08Dh, 046h, 008h, 049h, 03Bh, 0C1h, 07Eh, 011h, 08Bh, 0C1h, 08Dh, 048h, 0F0h, 03Bh
    db 0CDh, 089h, 04Ch, 024h, 018h, 07Dh, 004h, 089h, 06Ch, 024h, 018h, 02Bh, 0C6h, 08Bh, 0DEh, 08Bh
    db 0E8h, 074h, 068h, 08Bh, 0FFh, 08Bh, 047h, 004h, 04Dh, 043h, 08Bh, 00Ch, 0D8h, 085h, 0C9h, 08Dh
    db 004h, 0D8h, 00Fh, 084h, 058h, 001h, 000h, 000h, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 075h, 00Dh, 083h, 07Ch, 024h, 014h, 0FFh, 074h, 040h, 089h, 05Ch, 024h, 014h, 0EBh, 03Ah, 08Bh
    db 04Ch, 024h, 020h, 08Bh, 000h, 08Bh, 009h, 03Bh, 0C1h, 00Fh, 084h, 049h, 001h, 000h, 000h, 066h
    db 08Bh, 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 020h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 00Fh, 085h, 01Fh
    db 001h, 000h, 000h, 085h, 0EDh, 075h, 09Ah, 08Bh, 044h, 024h, 018h, 08Bh, 0DEh, 02Bh, 0F0h, 089h
    db 074h, 024h, 018h, 074h, 066h, 08Bh, 047h, 004h, 04Bh, 08Bh, 00Ch, 0D8h, 08Dh, 004h, 0D8h, 04Eh
    db 085h, 0C9h, 00Fh, 084h, 011h, 001h, 000h, 000h, 081h, 0F9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 075h, 00Dh, 083h, 07Ch, 024h, 014h, 0FFh, 074h, 040h, 089h, 05Ch, 024h, 014h, 0EBh, 03Ah, 08Bh
    db 04Ch, 024h, 020h, 08Bh, 000h, 08Bh, 009h, 03Bh, 0C1h, 00Fh, 084h, 014h, 001h, 000h, 000h, 066h
    db 08Bh, 050h, 006h, 066h, 03Bh, 051h, 006h, 075h, 020h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 0F7h, 0D8h, 01Ah, 0C0h, 0FEh, 0C0h, 088h, 044h, 024h, 013h, 00Fh, 085h, 0EAh
    db 000h, 000h, 000h, 085h, 0F6h, 075h, 09Ah, 08Bh, 05Ch, 024h, 014h, 083h, 0FBh, 0FFh, 00Fh, 085h
    db 0F0h, 000h, 000h, 000h, 08Bh, 0CFh
    call ?d_0089d180@@YAXXZ
    db 08Bh, 044h, 024h, 020h, 08Bh, 000h, 08Bh, 037h, 08Bh, 057h, 004h, 089h, 05Ch, 024h, 014h, 066h
    db 08Bh, 058h, 006h, 00Fh, 0B7h, 0CBh, 04Eh, 023h, 0F1h, 08Dh, 00Ch, 0F2h, 08Bh, 011h, 085h, 0D2h
    db 00Fh, 085h, 063h, 0FEh, 0FFh, 0FFh, 08Bh, 047h, 004h, 08Bh, 04Ch, 024h, 020h, 08Bh, 009h, 08Dh
    db 01Ch, 0F5h, 000h, 000h, 000h, 000h, 08Bh, 074h, 024h, 024h, 003h, 0C3h, 089h, 008h, 066h, 0FFh
    db 001h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 012h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 014h, 03Ch, 001h
    db 075h, 003h, 083h, 0CEh, 001h, 08Bh, 04Fh, 004h, 05Fh, 089h, 074h, 019h, 004h, 05Eh, 05Dh, 05Bh
    db 083h, 0C4h, 00Ch, 0C2h, 008h, 000h, 08Bh, 054h, 024h, 024h, 052h, 056h, 08Bh, 0CFh
    call ?SetAt@AptNativeHash@@QAEXHPAVBfmeHeldC680@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 008h, 000h, 08Bh, 047h, 004h, 08Bh, 054h, 024h
    db 020h, 08Dh, 00Ch, 0D8h, 08Bh, 002h, 089h, 001h, 066h, 0FFh, 000h, 0E9h, 083h, 000h, 000h, 000h
    db 08Bh, 04Ch, 024h, 024h, 051h, 053h, 08Bh, 0CFh
    call ?SetAt@AptNativeHash@@QAEXHPAVBfmeHeldC680@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 008h, 000h, 08Bh, 057h, 004h, 08Bh, 044h, 024h
    db 020h, 08Bh, 000h, 08Dh, 00Ch, 0DAh, 089h, 001h, 08Bh, 04Ch, 024h, 024h, 066h, 0FFh, 000h, 051h
    db 08Bh, 0CFh, 053h
    call ?bfmePutC6E0@BfmeStoreC6E0@@QAEXHPAVBfmeHeldC6E0@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 008h, 000h, 08Bh, 054h, 024h, 024h, 052h, 053h
    db 08Bh, 0CFh
    call ?SetAt@AptNativeHash@@QAEXHPAVBfmeHeldC680@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 008h, 000h, 08Bh, 047h, 004h, 08Bh, 06Ch, 024h
    db 020h, 08Dh, 034h, 0D8h, 08Bh, 045h, 000h, 066h, 0FFh, 000h, 08Bh, 006h, 066h, 0FFh, 008h, 066h
    db 083h, 038h, 000h, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 055h, 000h, 089h, 016h, 08Bh, 044h, 024h, 024h
    db 050h, 08Bh, 0CFh, 053h
    call ?bfmePutC6E0@BfmeStoreC6E0@@QAEXHPAVBfmeHeldC6E0@@@Z
    db 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 008h, 000h
?d_0089d5b0@@YAXXZ ENDP
_TEXT$d00c9d5b0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9dfd0  retail @ 0x0089DFD0 size 93
public ?d_0089dfd0@@YAXXZ
?d_0089dfd0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 56h, 8Bh, 0F1h, 74h, 3Fh, 57h, 8Dh, 78h, 0Ch, 0A1h
    db 30h, 7Ah, 33h, 01h, 83h, 0E7h, 0FCh, 57h, 0FFh, 10h, 89h, 06h, 66h, 0C7h, 00h, 01h
    db 00h, 8Bh, 0Eh, 83h, 0C4h, 04h, 83h, 0C7h, 0F7h, 66h, 89h, 79h, 04h, 8Bh, 16h, 66h
    db 0C7h, 42h, 02h, 00h, 00h, 8Bh, 06h, 66h, 0C7h, 40h, 06h, 00h, 00h, 8Bh, 0Eh, 5Fh
    db 8Bh, 0C6h, 0C6h, 41h, 08h, 00h, 5Eh, 0C2h, 04h, 00h, 0C7h, 06h, 98h, 52h, 2Dh, 01h
    db 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0089dfd0@@YAXXZ ENDP

; ghidra: FUN_00c9e030  retail @ 0x0089E030 size 133
public ?d_0089e030@@YAXXZ
?d_0089e030@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 0Ch, 85h, 0EDh, 56h, 8Bh, 0F1h, 74h, 65h, 0A1h, 30h, 7Ah, 33h
    db 01h, 53h, 57h, 8Dh, 7Dh, 0Ch, 83h, 0E7h, 0FCh, 57h, 0FFh, 10h, 89h, 06h, 66h, 0C7h
    db 00h, 01h, 00h, 8Ah, 44h, 24h, 18h, 8Bh, 0Eh, 8Ah, 0D8h, 8Ah, 0FBh, 83h, 0C7h, 0F7h
    db 66h, 89h, 79h, 04h, 8Bh, 3Eh, 8Bh, 0CDh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 8Bh, 0C3h, 0C1h
    db 0E0h, 10h, 66h, 8Bh, 0C3h, 83h, 0C7h, 08h, 83h, 0C4h, 04h, 0F3h, 0ABh, 8Bh, 0CAh, 83h
    db 0E1h, 03h, 0F3h, 0AAh, 8Bh, 06h, 66h, 89h, 68h, 02h, 8Bh, 0Eh, 33h, 0C0h, 66h, 89h
    db 41h, 06h, 8Bh, 16h, 5Fh, 88h, 44h, 2Ah, 08h, 5Bh, 8Bh, 0C6h, 5Eh, 5Dh, 0C2h, 08h
    db 00h, 0C7h, 06h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 8Bh, 0C6h
    db 5Eh, 5Dh, 0C2h, 08h, 00h
?d_0089e030@@YAXXZ ENDP

; ghidra: FUN_00c9e0c0  retail @ 0x0089E0C0 size 287
public ?d_0089e0c0@@YAXXZ
?d_0089e0c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 49h, 7Ah, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 55h, 56h, 8Bh, 0F1h, 0C7h, 44h, 24h, 10h
    db 00h, 00h, 00h, 00h, 8Bh, 0Eh, 0Fh, 0B7h, 69h, 02h, 85h, 0EDh, 89h, 74h, 24h, 0Ch
    db 75h, 22h, 8Bh, 44h, 24h, 28h, 8Bh, 08h, 8Bh, 44h, 24h, 24h, 89h, 08h, 66h, 0FFh
    db 01h, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 18h, 0C2h, 08h, 00h, 8Bh, 54h, 24h, 28h, 8Bh, 02h, 53h, 0Fh, 0B7h, 58h, 02h, 85h
    db 0DBh, 75h, 1Dh, 8Bh, 44h, 24h, 28h, 5Bh, 5Eh, 89h, 08h, 66h, 0FFh, 01h, 5Dh, 8Bh
    db 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 08h, 00h
    db 57h, 8Dh, 0Ch, 2Bh, 51h, 8Dh, 4Ch, 24h, 14h, 0E8h, 82h, 0FEh, 0FFh, 0FFh, 8Bh, 36h
    db 8Bh, 44h, 24h, 10h, 83h, 0C6h, 08h, 8Bh, 0CDh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 8Dh, 78h
    db 08h, 0F3h, 0A5h, 8Bh, 0CAh, 8Bh, 54h, 24h, 30h, 83h, 0E1h, 03h, 0F3h, 0A4h, 8Bh, 32h
    db 83h, 0C6h, 08h, 8Bh, 0CBh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 8Dh, 7Ch, 28h, 08h, 0F3h, 0A5h
    db 8Bh, 0CAh, 8Bh, 54h, 24h, 14h, 83h, 0E1h, 03h, 0F3h, 0A4h, 8Bh, 74h, 24h, 2Ch, 8Dh
    db 4Ch, 18h, 08h, 0C6h, 04h, 29h, 00h, 03h, 0EBh, 66h, 89h, 68h, 02h, 8Bh, 0Ah, 66h
    db 0C7h, 41h, 06h, 00h, 00h, 89h, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 08h, 66h, 83h, 38h
    db 00h, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 5Fh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah
    db 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 18h, 5Bh, 8Bh, 0C6h
    db 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 08h, 00h
?d_0089e0c0@@YAXXZ ENDP

; ghidra: FUN_00c9e1e0  retail @ 0x0089E1E0 size 16
public ?d_0089e1e0@@YAXXZ
?d_0089e1e0@@YAXXZ PROC
    db 8Bh, 01h, 0Fh, 0B7h, 48h, 04h, 39h, 4Ch, 24h, 04h, 0Fh, 92h, 0C0h, 0C2h, 04h, 00h
?d_0089e1e0@@YAXXZ ENDP

; ghidra: FUN_00c9e1f0  retail @ 0x0089E1F0 size 61
public ?d_0089e1f0@@YAXXZ
?d_0089e1f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Eh, 0Fh, 0B7h, 51h, 02h, 3Bh, 0C2h, 7Dh
    db 25h, 85h, 0C0h, 7Dh, 02h, 33h, 0C0h, 8Bh, 54h, 24h, 08h, 52h, 8Dh, 44h, 01h, 08h
    db 50h, 0E8h, 86h, 8Eh, 15h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 09h, 2Bh, 06h, 83h
    db 0E8h, 08h, 5Eh, 0C2h, 08h, 00h, 83h, 0C8h, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_0089e1f0@@YAXXZ ENDP

; ghidra: FUN_00c9e230  retail @ 0x0089E230 size 62
public ?d_0089e230@@YAXXZ
?d_0089e230@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Eh, 0Fh, 0B7h, 51h, 02h, 3Bh, 0C2h, 7Dh
    db 26h, 85h, 0C0h, 7Dh, 02h, 33h, 0C0h, 0Fh, 0BEh, 54h, 24h, 08h, 52h, 8Dh, 44h, 01h
    db 08h, 50h, 0E8h, 0A3h, 8Bh, 15h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 09h, 2Bh, 06h
    db 83h, 0E8h, 08h, 5Eh, 0C2h, 08h, 00h, 83h, 0C8h, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_0089e230@@YAXXZ ENDP

; ghidra: FUN_00c9e570  retail @ 0x0089E570 size 260
public ?d_0089e570@@YAXXZ
?d_0089e570@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 55h, 8Bh, 0E9h, 8Bh, 5Dh, 00h, 66h, 83h, 3Bh, 01h, 75h
    db 53h, 0Fh, 0B7h, 4Bh, 04h, 3Bh, 0C1h, 77h, 4Bh, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 74h
    db 16h, 8Bh, 54h, 24h, 14h, 52h, 8Dh, 44h, 03h, 08h, 50h, 83h, 0C3h, 08h, 53h, 0E8h
    db 22h, 89h, 15h, 00h, 83h, 0C4h, 0Ch, 8Bh, 4Dh, 00h, 8Bh, 44h, 24h, 1Ch, 66h, 89h
    db 41h, 02h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 8Bh, 55h, 00h, 66h, 0C7h, 42h, 06h, 00h
    db 00h, 0Fh, 84h, 0A8h, 00h, 00h, 00h, 8Bh, 4Dh, 00h, 5Dh, 0C6h, 44h, 01h, 08h, 00h
    db 5Bh, 0C2h, 14h, 00h, 85h, 0C0h, 74h, 73h, 8Bh, 0D0h, 56h, 0C1h, 0EAh, 03h, 8Dh, 74h
    db 02h, 0Ch, 0A1h, 30h, 7Ah, 33h, 01h, 57h, 83h, 0E6h, 0FCh, 56h, 0FFh, 10h, 89h, 45h
    db 00h, 66h, 0C7h, 00h, 01h, 00h, 8Bh, 4Dh, 00h, 8Bh, 44h, 24h, 28h, 83h, 0C6h, 0F7h
    db 66h, 89h, 71h, 04h, 8Bh, 55h, 00h, 66h, 89h, 42h, 02h, 8Bh, 4Dh, 00h, 8Bh, 54h
    db 24h, 1Ch, 66h, 0C7h, 41h, 06h, 00h, 00h, 8Bh, 4Ch, 24h, 20h, 8Bh, 7Dh, 00h, 8Dh
    db 74h, 13h, 08h, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 83h, 0C7h, 08h, 0F3h, 0A5h, 8Bh, 0CAh, 83h
    db 0E1h, 03h, 83h, 0C4h, 04h, 0F3h, 0A4h, 8Bh, 4Ch, 24h, 20h, 85h, 0C9h, 5Fh, 5Eh, 74h
    db 18h, 8Bh, 4Dh, 00h, 0C6h, 44h, 01h, 08h, 00h, 0EBh, 0Eh, 0C7h, 45h, 00h, 98h, 52h
    db 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 0Bh, 66h, 83h, 3Bh, 00h
    db 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 53h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 5Dh
    db 5Bh, 0C2h, 14h, 00h
?d_0089e570@@YAXXZ ENDP

; ghidra: FUN_00c9e680  retail @ 0x0089E680 size 125
public ?d_0089e680@@YAXXZ
?d_0089e680@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 80h, 3Eh, 00h, 57h, 8Bh, 0F9h, 75h, 12h, 0C7h, 07h, 98h
    db 52h, 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Fh, 5Eh, 0C2h, 04h, 00h, 8Bh
    db 0C6h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 53h, 2Bh, 0C2h, 55h, 8Bh
    db 0E8h, 0A1h, 30h, 7Ah, 33h, 01h, 8Dh, 5Dh, 0Ch, 83h, 0E3h, 0FCh, 53h, 0FFh, 10h, 89h
    db 07h, 66h, 0C7h, 00h, 01h, 00h, 8Bh, 0Fh, 83h, 0C3h, 0F7h, 66h, 89h, 59h, 04h, 8Bh
    db 17h, 66h, 89h, 6Ah, 02h, 8Bh, 07h, 66h, 0C7h, 40h, 06h, 00h, 00h, 8Bh, 3Fh, 8Dh
    db 4Dh, 01h, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 83h, 0C7h, 08h, 0F3h, 0A5h, 83h, 0C4h, 04h, 5Dh
    db 8Bh, 0CAh, 83h, 0E1h, 03h, 5Bh, 0F3h, 0A4h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_0089e680@@YAXXZ ENDP

; ghidra: FUN_00c9e700  retail @ 0x0089E700 size 72
public ?d_0089e700@@YAXXZ
?d_0089e700@@YAXXZ PROC
    db 56h, 8Bh, 31h, 0Fh, 0BEh, 46h, 08h, 85h, 0C0h, 8Dh, 4Eh, 08h, 0BAh, 0C5h, 9Dh, 1Ch
    db 81h, 74h, 2Fh, 41h, 83h, 0F8h, 5Ah, 7Fh, 08h, 83h, 0F8h, 41h, 7Ch, 03h, 83h, 0C0h
    db 20h, 33h, 0C2h, 69h, 0C0h, 93h, 01h, 00h, 01h, 8Bh, 0D0h, 0Fh, 0BEh, 01h, 85h, 0C0h
    db 75h, 0E1h, 66h, 85h, 0D2h, 75h, 0Bh, 0B8h, 67h, 45h, 00h, 00h, 66h, 89h, 46h, 06h
    db 5Eh, 0C3h, 66h, 89h, 56h, 06h, 5Eh, 0C3h
?d_0089e700@@YAXXZ ENDP

; ghidra: FUN_00c9e8a0  retail @ 0x0089E8A0 size 130
public ?d_0089e8a0@@YAXXZ
?d_0089e8a0@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 03h, 56h, 57h, 0Fh, 0B7h, 78h, 02h, 85h, 0FFh, 75h, 2Ch, 8Bh
    db 74h, 24h, 10h, 8Bh, 06h, 66h, 0FFh, 00h, 8Bh, 03h, 66h, 0FFh, 08h, 66h, 39h, 38h
    db 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh
    db 16h, 5Fh, 5Eh, 89h, 13h, 8Bh, 0C3h, 5Bh, 0C2h, 04h, 00h, 55h, 8Bh, 6Ch, 24h, 14h
    db 8Bh, 45h, 00h, 0Fh, 0B7h, 70h, 02h, 85h, 0F6h, 74h, 2Eh, 8Dh, 04h, 3Eh, 50h, 6Ah
    db 00h, 57h, 6Ah, 00h, 50h, 8Bh, 0CBh, 0E8h, 74h, 0FCh, 0FFh, 0FFh, 8Bh, 13h, 8Dh, 4Eh
    db 01h, 8Bh, 75h, 00h, 8Bh, 0C1h, 0C1h, 0E9h, 02h, 83h, 0C6h, 08h, 8Dh, 7Ch, 3Ah, 08h
    db 0F3h, 0A5h, 8Bh, 0C8h, 83h, 0E1h, 03h, 0F3h, 0A4h, 5Dh, 5Fh, 5Eh, 8Bh, 0C3h, 5Bh, 0C2h
    db 04h, 00h
?d_0089e8a0@@YAXXZ ENDP

; ghidra: FUN_00c9e930  retail @ 0x0089E930 size 290
_TEXT ENDS
_TEXT$d00c9e930 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9E930 size 290
public ?d_0089e930@@YAXXZ
?d_0089e930@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01057A99
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 00Ch, 055h, 056h, 08Bh, 0F1h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 08Bh, 00Eh, 00Fh
    db 0B7h, 069h, 002h, 085h, 0EDh, 089h, 074h, 024h, 00Ch, 075h, 025h, 08Bh, 044h, 024h, 028h, 08Bh
    db 074h, 024h, 024h, 050h, 08Bh, 0CEh
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 0C6h, 05Eh, 05Dh, 08Bh, 04Ch, 024h, 00Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 018h, 0C2h, 008h, 000h, 053h, 08Bh, 05Ch, 024h, 02Ch, 08Dh, 053h, 001h, 090h, 08Ah, 003h
    db 043h, 084h, 0C0h, 075h, 0F9h, 02Bh, 0DAh, 075h, 01Dh, 08Bh, 044h, 024h, 028h, 05Bh, 05Eh, 089h
    db 008h, 066h, 0FFh, 001h, 05Dh, 08Bh, 04Ch, 024h, 00Ch, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 018h, 0C2h, 008h, 000h, 057h, 08Dh, 00Ch, 02Bh, 051h, 08Dh, 04Ch, 024h, 014h
    call ??0EAStringC@@QAE@I@Z
    db 08Bh, 036h, 08Bh, 044h, 024h, 010h, 083h, 0C6h, 008h, 08Bh, 0CDh, 08Bh, 0D1h, 0C1h, 0E9h, 002h
    db 08Dh, 078h, 008h, 0F3h, 0A5h, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 074h, 024h, 030h
    db 08Bh, 0CBh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 08Dh, 07Ch, 028h, 008h, 0F3h, 0A5h, 08Bh, 0CAh, 08Bh
    db 054h, 024h, 014h, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 074h, 024h, 02Ch, 08Dh, 04Ch, 018h, 008h
    db 0C6h, 004h, 029h, 000h, 003h, 0EBh, 066h, 089h, 068h, 002h, 08Bh, 00Ah, 066h, 0C7h, 041h, 006h
    db 000h, 000h, 089h, 006h, 066h, 0FFh, 000h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h
    db 024h, 018h, 001h, 000h, 000h, 000h, 05Fh, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 018h, 05Bh, 08Bh, 0C6h, 05Eh, 05Dh
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 018h, 0C2h, 008h, 000h
?d_0089e930@@YAXXZ ENDP
_TEXT$d00c9e930 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9ea60  retail @ 0x0089EA60 size 204
_TEXT ENDS
_TEXT$d00c9ea60 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9EA60 size 204
public ?d_0089ea60@@YAXXZ
?d_0089ea60@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01057AB8
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 053h, 055h, 08Bh, 0D9h, 08Bh, 003h, 056h, 057h
    db 00Fh, 0B7h, 078h, 002h, 085h, 0FFh, 075h, 051h, 08Bh, 04Ch, 024h, 020h, 051h, 08Dh, 04Ch, 024h
    db 024h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 074h, 024h, 020h, 066h, 0FFh, 006h, 08Bh, 003h, 066h, 0FFh, 008h, 066h, 039h, 038h, 089h
    db 07Ch, 024h, 018h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 089h, 033h, 066h, 0FFh, 00Eh, 066h, 083h, 03Eh, 000h
    db 0C7h, 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 04Dh, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 056h, 0FFh, 050h, 004h, 083h, 0C4h, 004h, 0EBh, 03Fh, 08Bh, 074h, 024h, 020h, 08Bh, 0C6h, 08Dh
    db 050h, 001h, 090h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 02Bh, 0C2h, 08Bh, 0E8h, 074h, 028h
    db 08Dh, 004h, 02Fh, 050h, 06Ah, 000h, 057h, 06Ah, 000h, 050h, 08Bh, 0CBh
    call ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z
    db 08Bh, 013h, 08Dh, 04Dh, 001h, 08Bh, 0C1h, 0C1h, 0E9h, 002h, 08Dh, 07Ch, 03Ah, 008h, 0F3h, 0A5h
    db 08Bh, 0C8h, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 04Ch, 024h, 010h, 05Fh, 05Eh, 05Dh, 08Bh, 0C3h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h
?d_0089ea60@@YAXXZ ENDP
_TEXT$d00c9ea60 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9eb30  retail @ 0x0089EB30 size 285
_TEXT ENDS
_TEXT$d00c9eb30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9EB30 size 285
public ?d_0089eb30@@YAXXZ
?d_0089eb30@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01057AE9
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 008h, 08Bh, 044h, 024h, 020h, 0C7h, 044h, 024h, 004h, 000h, 000h, 000h, 000h, 08Bh, 008h, 053h
    db 00Fh, 0B7h, 059h, 002h, 085h, 0DBh, 056h, 075h, 023h, 08Bh, 04Ch, 024h, 024h, 08Bh, 074h, 024h
    db 020h, 051h, 08Bh, 0CEh
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 0C6h, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 014h, 0C3h, 08Bh, 074h, 024h, 024h, 055h, 08Bh, 0EEh, 08Dh, 055h, 001h, 08Dh, 049h, 000h
    db 08Ah, 045h, 000h, 045h, 084h, 0C0h, 075h, 0F8h, 02Bh, 0EAh, 075h, 01Bh, 08Bh, 044h, 024h, 024h
    db 05Dh, 05Eh, 089h, 008h, 066h, 0FFh, 001h, 05Bh, 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 083h, 0C4h, 014h, 0C3h, 057h, 08Dh, 014h, 02Bh, 052h, 08Dh, 04Ch, 024h, 014h
    call ??0EAStringC@@QAE@I@Z
    db 08Bh, 044h, 024h, 010h, 08Bh, 0CDh, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 08Dh, 078h, 008h, 0F3h, 0A5h
    db 08Bh, 0CAh, 08Bh, 054h, 024h, 030h, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 032h, 08Bh, 0CBh, 08Bh
    db 0D1h, 0C1h, 0E9h, 002h, 083h, 0C6h, 008h, 08Dh, 07Ch, 028h, 008h, 089h, 07Ch, 024h, 010h, 0F3h
    db 0A5h, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 04Ch, 024h, 010h, 08Bh, 074h, 024h, 028h
    db 0C6h, 004h, 019h, 000h, 003h, 0DDh, 066h, 089h, 058h, 002h, 066h, 0C7h, 040h, 006h, 000h, 000h
    db 089h, 006h, 066h, 0FFh, 000h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 014h
    db 001h, 000h, 000h, 000h, 05Fh, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 014h, 05Dh, 08Bh, 0C6h, 05Eh, 05Bh
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C3h
?d_0089eb30@@YAXXZ ENDP
_TEXT$d00c9eb30 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9ec50  retail @ 0x0089EC50 size 31
public ?d_0089ec50@@YAXXZ
?d_0089ec50@@YAXXZ PROC
    db 8Bh, 01h, 0Fh, 0B7h, 40h, 02h, 8Bh, 54h, 24h, 04h, 3Bh, 0C2h, 76h, 02h, 8Bh, 0C2h
    db 50h, 6Ah, 01h, 50h, 6Ah, 00h, 52h, 0E8h, 04h, 0F9h, 0FFh, 0FFh, 0C2h, 04h, 00h
?d_0089ec50@@YAXXZ ENDP

; ghidra: FUN_00c9ec70  retail @ 0x0089EC70 size 93
public ?d_0089ec70@@YAXXZ
?d_0089ec70@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 53h, 55h, 56h, 8Bh, 74h, 24h, 10h, 57h, 33h, 0FFh, 85h, 0C0h
    db 8Bh, 0D9h, 8Bh, 0EEh, 76h, 3Eh, 8Ah, 4Dh, 00h, 45h, 84h, 0C9h, 74h, 05h, 47h, 3Bh
    db 0F8h, 72h, 0F3h, 85h, 0FFh, 74h, 2Dh, 8Bh, 13h, 0Fh, 0B7h, 6Ah, 02h, 8Dh, 04h, 2Fh
    db 50h, 6Ah, 01h, 55h, 6Ah, 00h, 50h, 8Bh, 0CBh, 0E8h, 0C2h, 0F8h, 0FFh, 0FFh, 8Bh, 03h
    db 8Bh, 0CFh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 8Dh, 7Ch, 28h, 08h, 0F3h, 0A5h, 8Bh, 0CAh, 83h
    db 0E1h, 03h, 0F3h, 0A4h, 5Fh, 5Eh, 5Dh, 8Bh, 0C3h, 5Bh, 0C2h, 08h, 00h
?d_0089ec70@@YAXXZ ENDP

; ghidra: FUN_00c9edf0  retail @ 0x0089EDF0 size 256
_TEXT ENDS
_TEXT$d00c9edf0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9EDF0 size 256
public ?d_0089edf0@@YAXXZ
?d_0089edf0@@YAXXZ PROC
    db 051h, 08Bh, 044h, 024h, 00Ch, 08Dh, 050h, 001h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 053h
    db 055h, 08Bh, 06Ch, 024h, 010h, 056h, 02Bh, 0C2h, 057h, 08Dh, 03Ch, 085h, 000h, 000h, 000h, 000h
    db 089h, 07Ch, 024h, 010h, 08Bh, 05Dh, 000h, 066h, 083h, 03Bh, 001h, 075h, 017h, 00Fh, 0B7h, 043h
    db 004h, 03Bh, 0F8h, 077h, 00Fh, 033h, 0C0h, 066h, 089h, 043h, 002h, 08Bh, 04Dh, 000h, 066h, 089h
    db 041h, 006h, 0EBh, 072h, 085h, 0FFh, 08Dh, 073h, 008h, 074h, 047h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 08Bh, 0D7h, 0C1h, 0EAh, 003h, 08Dh, 07Ch, 03Ah, 00Ch, 083h, 0E7h, 0FCh, 057h, 0FFh, 010h, 089h
    db 045h, 000h, 066h, 0C7h, 000h, 001h, 000h, 08Bh, 04Dh, 000h, 083h, 0C7h, 0F7h, 066h, 089h, 079h
    db 004h, 08Bh, 055h, 000h, 033h, 0C0h, 066h, 089h, 042h, 002h, 08Bh, 04Dh, 000h, 066h, 089h, 041h
    db 006h, 08Bh, 07Dh, 000h, 083h, 0C4h, 004h, 033h, 0C9h, 083h, 0C7h, 008h, 08Bh, 07Ch, 024h, 010h
    db 0EBh, 00Eh, 0C7h, 045h, 000h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 00Bh, 066h, 083h, 03Bh, 000h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 053h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 045h, 000h, 08Bh, 054h, 024h, 01Ch, 08Dh, 070h
    db 008h, 00Fh, 0B7h, 040h, 004h, 08Dh, 04Ch, 024h, 020h, 051h, 052h, 050h, 056h
    call ?ji_009f6ec0@@YAXXZ
    db 083h, 0C4h, 010h, 085h, 0C0h, 07Dh, 00Eh, 08Dh, 00Ch, 03Fh, 089h, 04Ch, 024h, 010h, 08Bh, 0F9h
    db 0E9h, 03Eh, 0FFh, 0FFh, 0FFh, 0C6h, 004h, 030h, 000h, 08Bh, 055h, 000h, 05Fh, 066h, 089h, 042h
    db 002h, 08Bh, 045h, 000h, 05Eh, 05Dh, 066h, 0C7h, 040h, 006h, 000h, 000h, 05Bh, 059h, 0C3h
?d_0089edf0@@YAXXZ ENDP
_TEXT$d00c9edf0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00c9eef0  retail @ 0x0089EEF0 size 230
public ?d_0089eef0@@YAXXZ
?d_0089eef0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 53h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0D9h, 8Dh
    db 34h, 07h, 7Fh, 16h, 8Bh, 03h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 27h, 50h
    db 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 0EBh, 19h, 85h, 0F6h, 7Fh, 2Dh, 8Bh, 03h
    db 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h
    db 0FFh, 51h, 04h, 83h, 0C4h, 04h, 5Fh, 0C7h, 03h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h
    db 98h, 52h, 2Dh, 01h, 5Eh, 33h, 0C0h, 5Bh, 0C2h, 08h, 00h, 85h, 0FFh, 7Dh, 02h, 33h
    db 0FFh, 8Bh, 03h, 55h, 0Fh, 0B7h, 68h, 02h, 3Bh, 0F5h, 89h, 44h, 24h, 14h, 7Ch, 02h
    db 8Bh, 0F5h, 85h, 0FFh, 8Bh, 0CBh, 75h, 16h, 2Bh, 0EEh, 55h, 6Ah, 01h, 55h, 56h, 55h
    db 0E8h, 0FBh, 0F5h, 0FFh, 0FFh, 8Bh, 0C5h, 5Dh, 5Fh, 5Eh, 5Bh, 0C2h, 08h, 00h, 3Bh, 0F5h
    db 75h, 15h, 57h, 6Ah, 01h, 57h, 6Ah, 00h, 57h, 0E8h, 0E2h, 0F5h, 0FFh, 0FFh, 5Dh, 8Bh
    db 0C7h, 5Fh, 5Eh, 5Bh, 0C2h, 08h, 00h, 2Bh, 0EEh, 8Dh, 04h, 2Fh, 50h, 6Ah, 00h, 57h
    db 6Ah, 00h, 50h, 89h, 44h, 24h, 2Ch, 0E8h, 0C4h, 0F5h, 0FFh, 0FFh, 8Bh, 54h, 24h, 14h
    db 8Bh, 03h, 8Dh, 74h, 32h, 08h, 8Dh, 4Dh, 01h, 8Bh, 0D1h, 8Dh, 7Ch, 38h, 08h, 8Bh
    db 44h, 24h, 18h, 0C1h, 0E9h, 02h, 0F3h, 0A5h, 8Bh, 0CAh, 5Dh, 83h, 0E1h, 03h, 0F3h, 0A4h
    db 5Fh, 5Eh, 5Bh, 0C2h, 08h, 00h
?d_0089eef0@@YAXXZ ENDP

; ghidra: FUN_00c9f010  retail @ 0x0089F010 size 206
public ?d_0089f010@@YAXXZ
?d_0089f010@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 21h, 7Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 18h, 85h, 0C0h, 7Fh, 22h, 8Bh, 44h, 24h, 14h, 0C7h, 00h, 98h, 52h, 2Dh, 01h, 66h
    db 0FFh, 05h, 98h, 52h, 2Dh, 01h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h, 8Bh, 09h, 0Fh, 0B7h, 51h, 02h, 3Bh, 0C2h, 72h
    db 1Ah, 8Bh, 44h, 24h, 14h, 89h, 08h, 66h, 0FFh, 01h, 8Bh, 4Ch, 24h, 04h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h, 66h, 0FFh, 01h, 56h, 89h
    db 4Ch, 24h, 1Ch, 50h, 6Ah, 01h, 50h, 6Ah, 00h, 50h, 8Dh, 4Ch, 24h, 30h, 0C7h, 44h
    db 24h, 24h, 01h, 00h, 00h, 00h, 0E8h, 0D5h, 0F4h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 8Bh
    db 74h, 24h, 18h, 89h, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h
    db 44h, 24h, 04h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 10h, 00h, 75h, 0Ch, 50h, 0A1h
    db 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_0089f010@@YAXXZ ENDP

; ghidra: FUN_00c9f0e0  retail @ 0x0089F0E0 size 207
public ?d_0089f0e0@@YAXXZ
?d_0089f0e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 51h, 7Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 18h, 85h, 0C0h, 7Fh, 22h, 8Bh, 44h, 24h, 14h, 0C7h, 00h, 98h, 52h, 2Dh, 01h, 66h
    db 0FFh, 05h, 98h, 52h, 2Dh, 01h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h, 8Bh, 11h, 0Fh, 0B7h, 4Ah, 02h, 2Bh, 0C8h, 85h
    db 0C9h, 7Fh, 1Ah, 8Bh, 44h, 24h, 14h, 89h, 10h, 66h, 0FFh, 02h, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h, 66h, 0FFh, 02h
    db 56h, 89h, 54h, 24h, 1Ch, 50h, 6Ah, 01h, 50h, 51h, 50h, 8Dh, 4Ch, 24h, 30h, 0C7h
    db 44h, 24h, 24h, 01h, 00h, 00h, 00h, 0E8h, 04h, 0F4h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch
    db 8Bh, 74h, 24h, 18h, 89h, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h
    db 0C7h, 44h, 24h, 04h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 10h, 00h, 75h, 0Ch, 50h
    db 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 8Bh
    db 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_0089f0e0@@YAXXZ ENDP

; ghidra: FUN_00c9f1b0  retail @ 0x0089F1B0 size 207
public ?d_0089f1b0@@YAXXZ
?d_0089f1b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 81h, 7Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 8Bh, 54h, 24h
    db 18h, 85h, 0D2h, 8Bh, 09h, 7Fh, 1Ah, 8Bh, 44h, 24h, 14h, 89h, 08h, 66h, 0FFh, 01h
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h
    db 00h, 0Fh, 0B7h, 41h, 02h, 2Bh, 0C2h, 85h, 0C0h, 7Fh, 22h, 8Bh, 44h, 24h, 14h, 0C7h
    db 00h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h, 66h, 0FFh, 01h
    db 56h, 89h, 4Ch, 24h, 1Ch, 50h, 6Ah, 01h, 50h, 52h, 50h, 8Dh, 4Ch, 24h, 30h, 0C7h
    db 44h, 24h, 24h, 01h, 00h, 00h, 00h, 0E8h, 34h, 0F3h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch
    db 8Bh, 74h, 24h, 18h, 89h, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h
    db 0C7h, 44h, 24h, 04h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 10h, 00h, 75h, 0Ch, 50h
    db 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 8Bh
    db 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_0089f1b0@@YAXXZ ENDP

; ghidra: FUN_00c9f280  retail @ 0x0089F280 size 238
public ?d_0089f280@@YAXXZ
?d_0089f280@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B1h, 7Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 1Ch, 85h, 0D2h, 57h, 8Bh, 7Ch, 24h, 24h, 8Bh, 0F2h, 7Dh, 04h, 03h, 0FAh
    db 33h, 0F6h, 85h, 0FFh, 7Fh, 24h, 8Bh, 44h, 24h, 1Ch, 0C7h, 00h, 98h, 52h, 2Dh, 01h
    db 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 8Bh, 09h, 0Fh, 0B7h, 41h, 02h
    db 2Bh, 0C6h, 85h, 0C0h, 7Fh, 24h, 8Bh, 44h, 24h, 1Ch, 5Fh, 0C7h, 00h, 98h, 52h, 2Dh
    db 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 3Bh, 0F8h, 7Dh, 02h, 8Bh, 0C7h
    db 66h, 0FFh, 01h, 89h, 4Ch, 24h, 20h, 50h, 0BFh, 01h, 00h, 00h, 00h, 57h, 50h, 52h
    db 50h, 8Dh, 4Ch, 24h, 34h, 89h, 7Ch, 24h, 28h, 0E8h, 42h, 0F2h, 0FFh, 0FFh, 8Bh, 44h
    db 24h, 20h, 8Bh, 74h, 24h, 1Ch, 89h, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 08h, 66h, 83h
    db 38h, 00h, 89h, 7Ch, 24h, 08h, 0C6h, 44h, 24h, 14h, 00h, 75h, 0Ch, 50h, 0A1h, 30h
    db 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 8Bh, 0C6h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
?d_0089f280@@YAXXZ ENDP

; ghidra: FUN_00c9f370  retail @ 0x0089F370 size 39
public ?d_0089f370@@YAXXZ
?d_0089f370@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0Fh, 0B7h, 40h, 02h, 50h, 6Ah, 01h, 50h, 6Ah, 00h, 50h
    db 0E8h, 0EBh, 0F1h, 0FFh, 0FFh, 8Bh, 0Eh, 83h, 0C1h, 08h, 51h, 0E8h, 0EAh, 89h, 15h, 00h
    db 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C3h
?d_0089f370@@YAXXZ ENDP

; ghidra: FUN_00c9f3a0  retail @ 0x0089F3A0 size 39
public ?d_0089f3a0@@YAXXZ
?d_0089f3a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0Fh, 0B7h, 40h, 02h, 50h, 6Ah, 01h, 50h, 6Ah, 00h, 50h
    db 0E8h, 0BBh, 0F1h, 0FFh, 0FFh, 8Bh, 0Eh, 83h, 0C1h, 08h, 51h, 0E8h, 0D8h, 34h, 26h, 00h
    db 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C3h
?d_0089f3a0@@YAXXZ ENDP

; ghidra: FUN_00c9f3d0  retail @ 0x0089F3D0 size 75
public ?d_0089f3d0@@YAXXZ
?d_0089f3d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0Fh, 0B7h, 40h, 02h, 50h, 6Ah, 01h, 50h, 6Ah, 00h, 50h
    db 0E8h, 8Bh, 0F1h, 0FFh, 0FFh, 8Bh, 06h, 0Fh, 0B7h, 48h, 02h, 83h, 0F9h, 01h, 76h, 27h
    db 83h, 0C0h, 08h, 8Dh, 4Ch, 08h, 0FFh, 3Bh, 0C1h, 73h, 14h, 53h, 8Dh, 64h, 24h, 00h
    db 8Ah, 19h, 8Ah, 10h, 88h, 18h, 40h, 88h, 11h, 49h, 3Bh, 0C1h, 72h, 0F2h, 5Bh, 8Bh
    db 0Eh, 66h, 0C7h, 41h, 06h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_0089f3d0@@YAXXZ ENDP

; ghidra: FUN_00c9f530  retail @ 0x0089F530 size 270
public ?d_0089f530@@YAXXZ
?d_0089f530@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F0h, 7Bh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 07h, 0Fh, 0B7h
    db 70h, 02h, 33h, 0EDh, 85h, 0F6h, 8Dh, 5Ch, 30h, 07h, 76h, 21h, 8Dh, 64h, 24h, 00h
    db 8Ah, 03h, 8Bh, 4Ch, 24h, 24h, 0Fh, 0BEh, 0C0h, 50h, 51h, 4Bh, 0E8h, 89h, 78h, 15h
    db 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 05h, 45h, 3Bh, 0EEh, 72h, 0E3h, 66h, 0FFh, 05h
    db 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 24h, 98h, 52h, 2Dh, 01h, 2Bh, 0F5h, 56h, 8Dh
    db 54h, 24h, 14h, 52h, 8Bh, 0CFh, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0E8h, 6Dh
    db 0FAh, 0FFh, 0FFh, 8Bh, 0F0h, 8Bh, 06h, 66h, 0FFh, 00h, 66h, 0FFh, 0Dh, 98h, 52h, 2Dh
    db 01h, 0C6h, 44h, 24h, 1Ch, 01h, 75h, 10h, 0A1h, 30h, 7Ah, 33h, 01h, 68h, 98h, 52h
    db 2Dh, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 44h, 24h, 10h, 8Bh, 36h, 66h, 0FFh
    db 08h, 66h, 83h, 38h, 00h, 89h, 74h, 24h, 24h, 0C6h, 44h, 24h, 1Ch, 00h, 75h, 0Dh
    db 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 66h, 0FFh, 06h
    db 8Bh, 07h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h
    db 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 89h, 37h, 66h, 0FFh, 0Eh, 66h, 83h, 3Eh
    db 00h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Ch, 0A1h, 30h, 7Ah, 33h, 01h
    db 56h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 14h, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_0089f530@@YAXXZ ENDP

; ghidra: FUN_00c9f810  retail @ 0x0089F810 size 179
public ?d_0089f810@@YAXXZ
?d_0089f810@@YAXXZ PROC
    db 8Bh, 01h, 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 83h, 0C0h, 08h, 33h, 0F6h, 85h, 0FFh, 0Fh
    db 8Eh, 99h, 00h, 00h, 00h, 8Ah, 08h, 80h, 0F9h, 7Fh, 77h, 06h, 0Fh, 0B6h, 0C9h, 40h
    db 0EBh, 78h, 8Ah, 0D1h, 80h, 0E2h, 0E0h, 80h, 0FAh, 0C0h, 75h, 15h, 33h, 0D2h, 8Ah, 50h
    db 01h, 83h, 0E1h, 1Fh, 0C1h, 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 83h, 0C0h, 02h, 0EBh
    db 59h, 8Ah, 0D1h, 80h, 0E2h, 0F0h, 80h, 0FAh, 0E0h, 75h, 22h, 33h, 0D2h, 8Ah, 50h, 01h
    db 83h, 0E1h, 0Fh, 0C1h, 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 33h, 0D2h, 8Ah, 50h, 02h
    db 0C1h, 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 83h, 0C0h, 03h, 0EBh, 2Dh, 33h, 0D2h, 8Ah
    db 50h, 01h, 83h, 0E1h, 07h, 0C1h, 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 33h, 0D2h, 8Ah
    db 50h, 02h, 0C1h, 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 33h, 0D2h, 8Ah, 50h, 03h, 0C1h
    db 0E1h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0CAh, 83h, 0C0h, 04h, 85h, 0C9h, 74h, 0Eh, 46h, 3Bh
    db 0F7h, 0Fh, 8Ch, 6Eh, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h, 33h, 0C0h, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_0089f810@@YAXXZ ENDP

; ghidra: FUN_00c9fa20  retail @ 0x0089FA20 size 151
public ?d_0089fa20@@YAXXZ
?d_0089fa20@@YAXXZ PROC
    db 8Bh, 11h, 56h, 33h, 0F6h, 83h, 0C2h, 08h, 8Ah, 0Ah, 80h, 0F9h, 7Fh, 77h, 06h, 0Fh
    db 0B6h, 0C9h, 42h, 0EBh, 74h, 8Ah, 0C1h, 24h, 0E0h, 3Ch, 0C0h, 75h, 15h, 33h, 0C0h, 8Ah
    db 42h, 01h, 83h, 0E1h, 1Fh, 0C1h, 0E1h, 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 83h, 0C2h, 02h
    db 0EBh, 57h, 8Ah, 0C1h, 24h, 0F0h, 3Ch, 0E0h, 75h, 22h, 33h, 0C0h, 8Ah, 42h, 01h, 83h
    db 0E1h, 0Fh, 0C1h, 0E1h, 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 33h, 0C0h, 8Ah, 42h, 02h, 0C1h
    db 0E1h, 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 83h, 0C2h, 03h, 0EBh, 2Dh, 33h, 0C0h, 8Ah, 42h
    db 01h, 83h, 0E1h, 07h, 0C1h, 0E1h, 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 33h, 0C0h, 8Ah, 42h
    db 02h, 0C1h, 0E1h, 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 33h, 0C0h, 8Ah, 42h, 03h, 0C1h, 0E1h
    db 06h, 83h, 0E0h, 3Fh, 0Bh, 0C8h, 83h, 0C2h, 04h, 85h, 0C9h, 74h, 06h, 46h, 0E9h, 75h
    db 0FFh, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh, 0C3h
?d_0089fa20@@YAXXZ ENDP

; ghidra: FUN_00c9fac0  retail @ 0x0089FAC0 size 245
public ?d_0089fac0@@YAXXZ
?d_0089fac0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 85h, 0C0h, 53h, 55h, 56h, 57h, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 8Bh, 0F8h, 7Dh, 02h, 33h, 0FFh, 8Bh, 31h, 83h, 0C6h, 08h, 33h, 0EDh
    db 85h, 0FFh, 8Bh, 0D6h, 0Fh, 8Eh, 97h, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 02h, 3Ch, 7Fh, 77h, 06h, 0Fh, 0B6h, 0C0h, 42h, 0EBh, 78h, 8Ah, 0D8h, 80h, 0E3h
    db 0E0h, 80h, 0FBh, 0C0h, 75h, 15h, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 1Fh, 0C1h, 0E0h
    db 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 83h, 0C2h, 02h, 0EBh, 59h, 8Ah, 0D8h, 80h, 0E3h, 0F0h
    db 80h, 0FBh, 0E0h, 75h, 22h, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 0Fh, 0C1h, 0E0h, 06h
    db 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 02h, 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh
    db 0Bh, 0C3h, 83h, 0C2h, 03h, 0EBh, 2Dh, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 07h, 0C1h
    db 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 02h, 0C1h, 0E0h, 06h, 83h
    db 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 03h, 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh
    db 0C3h, 83h, 0C2h, 04h, 85h, 0C0h, 74h, 0Dh, 45h, 3Bh, 0EFh, 0Fh, 8Ch, 6Fh, 0FFh, 0FFh
    db 0FFh, 85h, 0D2h, 75h, 19h, 8Bh, 44h, 24h, 18h, 5Fh, 5Eh, 5Dh, 0C7h, 00h, 98h, 52h
    db 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Bh, 59h, 0C2h, 08h, 00h, 2Bh, 0D6h
    db 8Bh, 74h, 24h, 18h, 52h, 56h, 0E8h, 05h, 0F6h, 0FFh, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh
    db 5Bh, 59h, 0C2h, 08h, 00h
?d_0089fac0@@YAXXZ ENDP

; ghidra: FUN_00c9fbc0  retail @ 0x0089FBC0 size 474
public ?d_0089fbc0@@YAXXZ
?d_0089fbc0@@YAXXZ PROC
    db 51h, 8Bh, 54h, 24h, 0Ch, 8Bh, 44h, 24h, 10h, 53h, 57h, 33h, 0FFh, 3Bh, 0D7h, 8Bh
    db 0D8h, 89h, 7Ch, 24h, 08h, 89h, 5Ch, 24h, 14h, 7Dh, 0Ah, 2Bh, 0C2h, 8Bh, 0D8h, 89h
    db 5Ch, 24h, 14h, 33h, 0D2h, 3Bh, 0DFh, 7Fh, 17h, 8Bh, 44h, 24h, 10h, 5Fh, 0C7h, 00h
    db 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Bh, 59h, 0C2h, 0Ch, 00h
    db 55h, 8Bh, 29h, 83h, 0C5h, 08h, 85h, 0D2h, 56h, 8Bh, 0F5h, 0Fh, 8Eh, 95h, 00h, 00h
    db 00h, 8Ah, 06h, 3Ch, 7Fh, 77h, 06h, 0Fh, 0B6h, 0C0h, 46h, 0EBh, 78h, 8Ah, 0D8h, 80h
    db 0E3h, 0E0h, 80h, 0FBh, 0C0h, 75h, 15h, 33h, 0DBh, 8Ah, 5Eh, 01h, 83h, 0E0h, 1Fh, 0C1h
    db 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 83h, 0C6h, 02h, 0EBh, 59h, 8Ah, 0D8h, 80h, 0E3h
    db 0F0h, 80h, 0FBh, 0E0h, 75h, 22h, 33h, 0DBh, 8Ah, 5Eh, 01h, 83h, 0E0h, 0Fh, 0C1h, 0E0h
    db 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Eh, 02h, 0C1h, 0E0h, 06h, 83h, 0E3h
    db 3Fh, 0Bh, 0C3h, 83h, 0C6h, 03h, 0EBh, 2Dh, 33h, 0DBh, 8Ah, 5Eh, 01h, 83h, 0E0h, 07h
    db 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Eh, 02h, 0C1h, 0E0h, 06h
    db 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Eh, 03h, 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh
    db 0Bh, 0C3h, 83h, 0C6h, 04h, 85h, 0C0h, 74h, 11h, 47h, 3Bh, 0FAh, 0Fh, 8Ch, 6Fh, 0FFh
    db 0FFh, 0FFh, 8Bh, 5Ch, 24h, 1Ch, 85h, 0F6h, 75h, 19h, 8Bh, 44h, 24h, 18h, 5Eh, 5Dh
    db 5Fh, 0C7h, 00h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 5Bh, 59h
    db 0C2h, 0Ch, 00h, 33h, 0FFh, 85h, 0DBh, 8Bh, 0D6h, 0Fh, 8Eh, 96h, 00h, 00h, 00h, 90h
    db 8Ah, 02h, 3Ch, 7Fh, 77h, 06h, 0Fh, 0B6h, 0C0h, 42h, 0EBh, 78h, 8Ah, 0D8h, 80h, 0E3h
    db 0E0h, 80h, 0FBh, 0C0h, 75h, 15h, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 1Fh, 0C1h, 0E0h
    db 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 83h, 0C2h, 02h, 0EBh, 59h, 8Ah, 0D8h, 80h, 0E3h, 0F0h
    db 80h, 0FBh, 0E0h, 75h, 22h, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 0Fh, 0C1h, 0E0h, 06h
    db 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 02h, 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh
    db 0Bh, 0C3h, 83h, 0C2h, 03h, 0EBh, 2Dh, 33h, 0DBh, 8Ah, 5Ah, 01h, 83h, 0E0h, 07h, 0C1h
    db 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 02h, 0C1h, 0E0h, 06h, 83h
    db 0E3h, 3Fh, 0Bh, 0C3h, 33h, 0DBh, 8Ah, 5Ah, 03h, 0C1h, 0E0h, 06h, 83h, 0E3h, 3Fh, 0Bh
    db 0C3h, 83h, 0C2h, 04h, 85h, 0C0h, 74h, 11h, 8Bh, 44h, 24h, 1Ch, 47h, 3Bh, 0F8h, 0Fh
    db 8Ch, 6Bh, 0FFh, 0FFh, 0FFh, 85h, 0D2h, 75h, 17h, 2Bh, 0F5h, 56h, 8Bh, 74h, 24h, 1Ch
    db 56h, 0E8h, 3Ah, 0F4h, 0FFh, 0FFh, 8Bh, 0C6h, 5Eh, 5Dh, 5Fh, 5Bh, 59h, 0C2h, 0Ch, 00h
    db 2Bh, 0D6h, 52h, 2Bh, 0F5h, 56h, 8Bh, 74h, 24h, 20h, 56h, 0E8h, 0F0h, 0F4h, 0FFh, 0FFh
    db 8Bh, 0C6h, 5Eh, 5Dh, 5Fh, 5Bh, 59h, 0C2h, 0Ch, 00h
?d_0089fbc0@@YAXXZ ENDP

; ghidra: FUN_00c9fda0  retail @ 0x0089FDA0 size 466
_TEXT ENDS
_TEXT$d00c9fda0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C9FDA0 size 466
public ?d_0089fda0@@YAXXZ
?d_0089fda0@@YAXXZ PROC
    db 08Bh, 044h, 024h, 004h, 083h, 0ECh, 00Ch, 053h, 056h, 057h, 08Bh, 07Ch, 024h, 020h, 033h, 0F6h
    db 085h, 0FFh, 08Bh, 0D9h, 08Bh, 0C8h, 00Fh, 08Eh, 099h, 000h, 000h, 000h, 08Dh, 064h, 024h, 000h
    db 08Ah, 001h, 03Ch, 07Fh, 077h, 006h, 00Fh, 0B6h, 0C0h, 041h, 0EBh, 078h, 08Ah, 0D0h, 080h, 0E2h
    db 0E0h, 080h, 0FAh, 0C0h, 075h, 015h, 033h, 0D2h, 08Ah, 051h, 001h, 083h, 0E0h, 01Fh, 0C1h, 0E0h
    db 006h, 083h, 0E2h, 03Fh, 00Bh, 0C2h, 083h, 0C1h, 002h, 0EBh, 059h, 08Ah, 0D0h, 080h, 0E2h, 0F0h
    db 080h, 0FAh, 0E0h, 075h, 022h, 033h, 0D2h, 08Ah, 051h, 001h, 083h, 0E0h, 00Fh, 0C1h, 0E0h, 006h
    db 083h, 0E2h, 03Fh, 00Bh, 0C2h, 033h, 0D2h, 08Ah, 051h, 002h, 0C1h, 0E0h, 006h, 083h, 0E2h, 03Fh
    db 00Bh, 0C2h, 083h, 0C1h, 003h, 0EBh, 02Dh, 033h, 0D2h, 08Ah, 051h, 001h, 083h, 0E0h, 007h, 0C1h
    db 0E0h, 006h, 083h, 0E2h, 03Fh, 00Bh, 0C2h, 033h, 0D2h, 08Ah, 051h, 002h, 0C1h, 0E0h, 006h, 083h
    db 0E2h, 03Fh, 00Bh, 0C2h, 033h, 0D2h, 08Ah, 051h, 003h, 0C1h, 0E0h, 006h, 083h, 0E2h, 03Fh, 00Bh
    db 0C2h, 083h, 0C1h, 004h, 085h, 0C0h, 074h, 009h, 046h, 03Bh, 0F7h, 00Fh, 08Ch, 06Fh, 0FFh, 0FFh
    db 0FFh, 08Bh, 044h, 024h, 01Ch, 033h, 0D2h, 02Bh, 0C8h, 08Bh, 0F8h, 089h, 054h, 024h, 020h, 08Bh
    db 0F1h, 00Fh, 084h, 000h, 001h, 000h, 000h, 08Ah, 007h, 047h, 084h, 0C0h, 074h, 005h, 042h, 03Bh
    db 0D6h, 072h, 0F4h, 085h, 0D2h, 089h, 054h, 024h, 020h, 00Fh, 084h, 0E8h, 000h, 000h, 000h, 08Bh
    db 003h, 066h, 083h, 038h, 001h, 00Fh, 0B7h, 070h, 002h, 055h, 089h, 044h, 024h, 014h, 089h, 074h
    db 024h, 018h, 08Dh, 02Ch, 016h, 075h, 020h, 00Fh, 0B7h, 048h, 004h, 03Bh, 0E9h, 077h, 018h, 066h
    db 089h, 068h, 002h, 08Bh, 003h, 066h, 0C7h, 040h, 006h, 000h, 000h, 08Bh, 00Bh, 0C6h, 044h, 029h
    db 008h, 000h, 0E9h, 091h, 000h, 000h, 000h, 085h, 0EDh, 08Dh, 048h, 008h, 089h, 04Ch, 024h, 010h
    db 074h, 05Fh, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 08Bh, 0D5h, 0C1h, 0EAh, 003h, 08Dh, 07Ch, 02Ah, 00Ch, 083h, 0E7h, 0FCh, 057h, 0FFh, 010h, 089h
    db 003h, 066h, 0C7h, 000h, 001h, 000h, 08Bh, 00Bh, 083h, 0C7h, 0F7h, 066h, 089h, 079h, 004h, 08Bh
    db 013h, 066h, 089h, 06Ah, 002h, 08Bh, 003h, 066h, 0C7h, 040h, 006h, 000h, 000h, 08Bh, 03Bh, 08Bh
    db 0CEh, 08Bh, 074h, 024h, 014h, 08Bh, 0D1h, 0C1h, 0E9h, 002h, 083h, 0C7h, 008h, 0F3h, 0A5h, 08Bh
    db 0CAh, 08Bh, 054h, 024h, 028h, 083h, 0C4h, 004h, 083h, 0E1h, 003h, 0F3h, 0A4h, 08Bh, 003h, 0C6h
    db 044h, 028h, 008h, 000h, 08Bh, 044h, 024h, 014h, 0EBh, 00Dh, 0C7h, 003h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 075h, 011h, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 08Bh, 054h, 024h, 028h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 018h, 08Bh
    db 074h, 024h, 020h, 08Bh, 0CAh, 08Bh, 013h, 08Dh, 07Ch, 002h, 008h, 08Bh, 0D1h, 0C1h, 0E9h, 002h
    db 0F3h, 0A5h, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0A4h, 05Dh, 05Fh, 05Eh, 08Bh, 0C3h, 05Bh, 083h
    db 0C4h, 00Ch, 0C2h, 008h, 000h
?d_0089fda0@@YAXXZ ENDP
_TEXT$d00c9fda0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca00c0  retail @ 0x008A00C0 size 304
public ?d_008a00c0@@YAXXZ
?d_008a00c0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 0E9h, 8Bh, 45h, 00h, 0Fh, 0B7h, 40h, 02h, 57h, 50h, 6Ah, 01h
    db 50h, 6Ah, 00h, 50h, 0E8h, 97h, 0E4h, 0FFh, 0FFh, 8Bh, 75h, 00h, 83h, 0C6h, 08h, 90h
    db 8Ah, 06h, 3Ch, 7Fh, 8Bh, 0DEh, 8Dh, 7Eh, 01h, 77h, 07h, 0Fh, 0B6h, 0C0h, 8Bh, 0F7h
    db 0EBh, 67h, 33h, 0D2h, 8Ah, 17h, 8Ah, 0C8h, 80h, 0E1h, 0E0h, 83h, 0E2h, 3Fh, 80h, 0F9h
    db 0C0h, 75h, 0Dh, 83h, 0E0h, 1Fh, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 83h, 0C6h, 02h, 0EBh, 49h
    db 8Ah, 0C8h, 80h, 0E1h, 0F0h, 80h, 0F9h, 0E0h, 75h, 1Ah, 33h, 0C9h, 8Ah, 4Eh, 02h, 83h
    db 0E0h, 0Fh, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 0C1h, 0E0h, 06h, 83h, 0E1h, 3Fh, 0Bh, 0C1h, 83h
    db 0C6h, 03h, 0EBh, 25h, 83h, 0E0h, 07h, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 33h, 0C9h, 8Ah, 4Eh
    db 02h, 33h, 0D2h, 8Ah, 56h, 03h, 0C1h, 0E0h, 06h, 83h, 0E1h, 3Fh, 0Bh, 0C1h, 0C1h, 0E0h
    db 06h, 83h, 0E2h, 3Fh, 0Bh, 0C2h, 83h, 0C6h, 04h, 85h, 0C0h, 0Fh, 84h, 88h, 00h, 00h
    db 00h, 50h, 0E8h, 33h, 6Eh, 15h, 00h, 83h, 0C4h, 04h, 3Dh, 80h, 00h, 00h, 00h, 7Dh
    db 07h, 88h, 03h, 0E9h, 68h, 0FFh, 0FFh, 0FFh, 3Dh, 00h, 08h, 00h, 00h, 8Bh, 0C8h, 7Dh
    db 13h, 0C1h, 0F9h, 06h, 80h, 0C9h, 0C0h, 24h, 3Fh, 0Ch, 80h, 88h, 0Bh, 88h, 07h, 0E9h
    db 4Ch, 0FFh, 0FFh, 0FFh, 3Dh, 00h, 00h, 01h, 00h, 8Bh, 0D0h, 7Dh, 1Fh, 0C1h, 0F9h, 06h
    db 0C1h, 0FAh, 0Ch, 80h, 0E1h, 3Fh, 80h, 0CAh, 0E0h, 80h, 0C9h, 80h, 24h, 3Fh, 0Ch, 80h
    db 88h, 13h, 88h, 0Fh, 88h, 43h, 02h, 0E9h, 24h, 0FFh, 0FFh, 0FFh, 0C1h, 0FAh, 12h, 80h
    db 0CAh, 0F0h, 88h, 13h, 8Bh, 0D0h, 0C1h, 0F9h, 0Ch, 0C1h, 0FAh, 06h, 80h, 0E1h, 3Fh, 80h
    db 0E2h, 3Fh, 80h, 0C9h, 80h, 80h, 0CAh, 80h, 24h, 3Fh, 0Ch, 80h, 88h, 0Fh, 88h, 53h
    db 02h, 88h, 43h, 03h, 0E9h, 0F7h, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C3h
?d_008a00c0@@YAXXZ ENDP

; ghidra: FUN_00ca01f0  retail @ 0x008A01F0 size 304
public ?d_008a01f0@@YAXXZ
?d_008a01f0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 0E9h, 8Bh, 45h, 00h, 0Fh, 0B7h, 40h, 02h, 57h, 50h, 6Ah, 01h
    db 50h, 6Ah, 00h, 50h, 0E8h, 67h, 0E3h, 0FFh, 0FFh, 8Bh, 75h, 00h, 83h, 0C6h, 08h, 90h
    db 8Ah, 06h, 3Ch, 7Fh, 8Bh, 0DEh, 8Dh, 7Eh, 01h, 77h, 07h, 0Fh, 0B6h, 0C0h, 8Bh, 0F7h
    db 0EBh, 67h, 33h, 0D2h, 8Ah, 17h, 8Ah, 0C8h, 80h, 0E1h, 0E0h, 83h, 0E2h, 3Fh, 80h, 0F9h
    db 0C0h, 75h, 0Dh, 83h, 0E0h, 1Fh, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 83h, 0C6h, 02h, 0EBh, 49h
    db 8Ah, 0C8h, 80h, 0E1h, 0F0h, 80h, 0F9h, 0E0h, 75h, 1Ah, 33h, 0C9h, 8Ah, 4Eh, 02h, 83h
    db 0E0h, 0Fh, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 0C1h, 0E0h, 06h, 83h, 0E1h, 3Fh, 0Bh, 0C1h, 83h
    db 0C6h, 03h, 0EBh, 25h, 83h, 0E0h, 07h, 0C1h, 0E0h, 06h, 0Bh, 0C2h, 33h, 0C9h, 8Ah, 4Eh
    db 02h, 33h, 0D2h, 8Ah, 56h, 03h, 0C1h, 0E0h, 06h, 83h, 0E1h, 3Fh, 0Bh, 0C1h, 0C1h, 0E0h
    db 06h, 83h, 0E2h, 3Fh, 0Bh, 0C2h, 83h, 0C6h, 04h, 85h, 0C0h, 0Fh, 84h, 88h, 00h, 00h
    db 00h, 50h, 0E8h, 11h, 6Eh, 15h, 00h, 83h, 0C4h, 04h, 3Dh, 80h, 00h, 00h, 00h, 7Dh
    db 07h, 88h, 03h, 0E9h, 68h, 0FFh, 0FFh, 0FFh, 3Dh, 00h, 08h, 00h, 00h, 8Bh, 0C8h, 7Dh
    db 13h, 0C1h, 0F9h, 06h, 80h, 0C9h, 0C0h, 24h, 3Fh, 0Ch, 80h, 88h, 0Bh, 88h, 07h, 0E9h
    db 4Ch, 0FFh, 0FFh, 0FFh, 3Dh, 00h, 00h, 01h, 00h, 8Bh, 0D0h, 7Dh, 1Fh, 0C1h, 0F9h, 06h
    db 0C1h, 0FAh, 0Ch, 80h, 0E1h, 3Fh, 80h, 0CAh, 0E0h, 80h, 0C9h, 80h, 24h, 3Fh, 0Ch, 80h
    db 88h, 13h, 88h, 0Fh, 88h, 43h, 02h, 0E9h, 24h, 0FFh, 0FFh, 0FFh, 0C1h, 0FAh, 12h, 80h
    db 0CAh, 0F0h, 88h, 13h, 8Bh, 0D0h, 0C1h, 0F9h, 0Ch, 0C1h, 0FAh, 06h, 80h, 0E1h, 3Fh, 80h
    db 0E2h, 3Fh, 80h, 0C9h, 80h, 80h, 0CAh, 80h, 24h, 3Fh, 0Ch, 80h, 88h, 0Fh, 88h, 53h
    db 02h, 88h, 43h, 03h, 0E9h, 0F7h, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C3h
?d_008a01f0@@YAXXZ ENDP

; ghidra: FUN_00ca0320  retail @ 0x008A0320 size 345
_TEXT ENDS
_TEXT$d00ca0320 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA0320 size 345
public ?d_008a0320@@YAXXZ
?d_008a0320@@YAXXZ PROC
    db 053h, 056h, 08Bh, 0F1h, 08Bh, 006h, 066h, 0FFh, 008h, 066h, 08Bh, 008h, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 05Ch, 024h, 00Ch, 0C7h, 006h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 081h, 0FBh, 080h, 000h, 000h, 000h, 07Dh, 007h, 0B9h, 001h, 000h, 000h, 000h, 0EBh, 01Dh, 081h
    db 0FBh, 000h, 008h, 000h, 000h, 07Dh, 007h, 0B9h, 002h, 000h, 000h, 000h, 0EBh, 00Eh, 033h, 0C9h
    db 081h, 0FBh, 000h, 000h, 001h, 000h, 00Fh, 09Dh, 0C1h, 083h, 0C1h, 003h, 08Bh, 016h, 00Fh, 0B7h
    db 042h, 002h, 03Bh, 0C1h, 076h, 002h, 08Bh, 0C1h, 050h, 06Ah, 001h, 050h, 06Ah, 000h, 051h, 08Bh
    db 0CEh
    call ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z
    db 08Bh, 006h, 083h, 0C0h, 008h, 081h, 0FBh, 080h, 000h, 000h, 000h, 07Dh, 01Dh, 088h, 018h, 0C6h
    db 040h, 001h, 000h, 08Bh, 006h, 066h, 0C7h, 040h, 002h, 001h, 000h, 08Bh, 006h, 066h, 0C7h, 040h
    db 006h, 000h, 000h, 08Bh, 0C6h, 05Eh, 05Bh, 0C2h, 004h, 000h, 081h, 0FBh, 000h, 008h, 000h, 000h
    db 08Bh, 0CBh, 07Dh, 02Ch, 0C1h, 0F9h, 006h, 080h, 0E3h, 03Fh, 080h, 0C9h, 0C0h, 088h, 008h, 0C6h
    db 040h, 002h, 000h, 080h, 0CBh, 080h, 088h, 058h, 001h, 08Bh, 016h, 066h, 0C7h, 042h, 002h, 002h
    db 000h, 08Bh, 006h, 066h, 0C7h, 040h, 006h, 000h, 000h, 08Bh, 0C6h, 05Eh, 05Bh, 0C2h, 004h, 000h
    db 081h, 0FBh, 000h, 000h, 001h, 000h, 08Bh, 0D3h, 07Dh, 038h, 0C1h, 0FAh, 006h, 0C1h, 0F9h, 00Ch
    db 080h, 0E2h, 03Fh, 080h, 0E3h, 03Fh, 080h, 0C9h, 0E0h, 088h, 008h, 080h, 0CAh, 080h, 088h, 050h
    db 001h, 0C6h, 040h, 003h, 000h, 080h, 0CBh, 080h, 088h, 058h, 002h, 08Bh, 006h, 066h, 0C7h, 040h
    db 002h, 003h, 000h, 08Bh, 006h, 066h, 0C7h, 040h, 006h, 000h, 000h, 08Bh, 0C6h, 05Eh, 05Bh, 0C2h
    db 004h, 000h, 0C1h, 0F9h, 012h, 080h, 0C9h, 0F0h, 088h, 008h, 08Bh, 0CBh, 0C1h, 0FAh, 00Ch, 0C1h
    db 0F9h, 006h, 080h, 0E2h, 03Fh, 080h, 0E3h, 03Fh, 080h, 0E1h, 03Fh, 0C6h, 040h, 004h, 000h, 080h
    db 0CAh, 080h, 088h, 050h, 001h, 080h, 0CBh, 080h, 088h, 058h, 003h, 080h, 0C9h, 080h, 088h, 048h
    db 002h, 08Bh, 016h, 066h, 0C7h, 042h, 002h, 004h, 000h, 08Bh, 006h, 066h, 0C7h, 040h, 006h, 000h
    db 000h, 08Bh, 0C6h, 05Eh, 05Bh, 0C2h, 004h, 000h
?d_008a0320@@YAXXZ ENDP
_TEXT$d00ca0320 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca0480  retail @ 0x008A0480 size 105
public ?d_008a0480@@YAXXZ
?d_008a0480@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 74h, 24h, 10h, 8Bh, 06h, 0Fh, 0B7h, 68h, 02h, 8Bh, 0D9h, 8Bh
    db 0Bh, 0Fh, 0B7h, 41h, 02h, 3Bh, 0C5h, 57h, 76h, 02h, 8Bh, 0C5h, 50h, 6Ah, 01h, 50h
    db 6Ah, 00h, 55h, 8Bh, 0CBh, 0E8h, 0C6h, 0E0h, 0FFh, 0FFh, 8Bh, 03h, 8Bh, 36h, 83h, 0C0h
    db 08h, 8Bh, 0CDh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 8Bh, 0F8h, 83h, 0C6h, 08h, 0F3h, 0A5h, 8Bh
    db 0CAh, 83h, 0E1h, 03h, 0F3h, 0A4h, 8Bh, 4Ch, 24h, 14h, 0C6h, 04h, 28h, 00h, 8Bh, 03h
    db 66h, 89h, 68h, 02h, 8Bh, 11h, 8Bh, 03h, 66h, 8Bh, 4Ah, 06h, 5Fh, 5Eh, 66h, 89h
    db 48h, 06h, 5Dh, 8Bh, 0C3h, 5Bh, 0C2h, 04h, 00h
?d_008a0480@@YAXXZ ENDP

; ghidra: FUN_00ca0570  retail @ 0x008A0570 size 20
public ?d_008a0570@@YAXXZ
?d_008a0570@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 7Ch, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h, 46h, 7Ch, 00h, 00h
    db 00h, 00h, 5Eh, 0C3h
?d_008a0570@@YAXXZ ENDP

; ghidra: FUN_00ca0690  retail @ 0x008A0690 size 36
public ?d_008a0690@@YAXXZ
?d_008a0690@@YAXXZ PROC
    db 8Bh, 51h, 0Ch, 56h, 33h, 0C0h, 85h, 0D2h, 7Eh, 13h, 8Bh, 49h, 10h, 8Bh, 74h, 24h
    db 08h, 39h, 31h, 74h, 0Bh, 40h, 83h, 0C1h, 04h, 3Bh, 0C2h, 7Ch, 0F4h, 83h, 0C8h, 0FFh
    db 5Eh, 0C2h, 04h, 00h
?d_008a0690@@YAXXZ ENDP

; ghidra: FUN_00ca06c0  retail @ 0x008A06C0 size 39
public ?d_008a06c0@@YAXXZ
?d_008a06c0@@YAXXZ PROC
    db 8Bh, 51h, 20h, 56h, 33h, 0C0h, 85h, 0D2h, 7Eh, 16h, 8Bh, 49h, 24h, 8Bh, 74h, 24h
    db 08h, 83h, 0C1h, 08h, 39h, 31h, 74h, 0Bh, 40h, 83h, 0C1h, 10h, 3Bh, 0C2h, 7Ch, 0F4h
    db 83h, 0C8h, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_008a06c0@@YAXXZ ENDP

; ghidra: FUN_00ca0700  retail @ 0x008A0700 size 100
public ?d_008a0700@@YAXXZ
?d_008a0700@@YAXXZ PROC
    db 8Bh, 81h, 38h, 12h, 00h, 00h, 8Bh, 91h, 0A8h, 12h, 00h, 00h, 83h, 0ECh, 08h, 3Bh
    db 0C2h, 7Dh, 4Bh, 85h, 0C0h, 8Bh, 54h, 24h, 0Ch, 56h, 7Eh, 0Ch, 8Bh, 0B1h, 3Ch, 12h
    db 00h, 00h, 39h, 54h, 86h, 0FCh, 74h, 35h, 8Bh, 0B1h, 3Ch, 12h, 00h, 00h, 89h, 14h
    db 86h, 0FFh, 81h, 38h, 12h, 00h, 00h, 0A1h, 08h, 78h, 33h, 01h, 85h, 0C0h, 74h, 1Dh
    db 0A1h, 0F4h, 77h, 33h, 01h, 8Dh, 4Ch, 24h, 04h, 6Ah, 08h, 51h, 89h, 44h, 24h, 0Ch
    db 89h, 54h, 24h, 10h, 0FFh, 15h, 40h, 78h, 33h, 01h, 83h, 0C4h, 08h, 5Eh, 83h, 0C4h
    db 08h, 0C2h, 04h, 00h
?d_008a0700@@YAXXZ ENDP

; ghidra: FUN_00ca0770  retail @ 0x008A0770 size 46
public ?d_008a0770@@YAXXZ
?d_008a0770@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 54h, 24h, 04h, 83h, 0E0h, 7Fh, 0C1h, 0E2h, 07h, 0Bh, 0C2h
    db 8Bh, 54h, 24h, 0Ch, 0C1h, 0E0h, 08h, 81h, 0E2h, 0FFh, 00h, 00h, 00h, 0Bh, 0C2h, 0C1h
    db 0E0h, 02h, 83h, 0C8h, 01h, 50h, 0E8h, 65h, 0FFh, 0FFh, 0FFh, 0C2h, 0Ch, 00h
?d_008a0770@@YAXXZ ENDP

; ghidra: FUN_00ca07a0  retail @ 0x008A07A0 size 40
public ?d_008a07a0@@YAXXZ
?d_008a07a0@@YAXXZ PROC
    db 0A0h, 1Ch, 78h, 33h, 01h, 84h, 0C0h, 74h, 1Ch, 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h
    db 08h, 0C1h, 0E0h, 0Fh, 81h, 0E2h, 0FFh, 7Fh, 00h, 00h, 0Bh, 0C2h, 0C1h, 0E0h, 02h, 50h
    db 0E8h, 3Bh, 0FFh, 0FFh, 0FFh, 0C2h, 08h, 00h
?d_008a07a0@@YAXXZ ENDP

; ghidra: FUN_00ca07d0  retail @ 0x008A07D0 size 87
public ?d_008a07d0@@YAXXZ
?d_008a07d0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 04h, 3Bh, 77h, 08h, 74h, 40h, 8Dh, 64h, 24h, 00h
    db 8Bh, 06h, 85h, 0C0h, 75h, 05h, 8Bh, 4Eh, 10h, 0EBh, 10h, 83h, 0F8h, 01h, 75h, 10h
    db 8Bh, 4Eh, 08h, 8Bh, 11h, 0FFh, 52h, 04h, 8Bh, 4Eh, 0Ch, 8Bh, 01h, 0FFh, 50h, 04h
    db 8Bh, 87h, 0B0h, 12h, 00h, 00h, 8Bh, 0Fh, 8Dh, 14h, 80h, 83h, 0C6h, 14h, 8Dh, 04h
    db 91h, 3Bh, 0F0h, 75h, 02h, 8Bh, 0F1h, 3Bh, 77h, 08h, 75h, 0C4h, 8Bh, 07h, 89h, 47h
    db 08h, 89h, 47h, 04h, 5Fh, 5Eh, 0C3h
?d_008a07d0@@YAXXZ ENDP
_TEXT ENDS
END
