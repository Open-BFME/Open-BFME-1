.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0Rva008A9B00@@QAE@XZ:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA:BYTE
EXTERN ?Rva008A5380Holder@@3PADA:BYTE
EXTERN ?Rva008AE770TheStack@@3URva008AE770Stack@@A:BYTE
EXTERN ?Rva008C3B60Head@@3PAURva008C3B60Node@@A:BYTE
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?append@Rva008B2EA0Node@@QAEXPAX@Z:NEAR
EXTERN ?bfmeActivate1236@BfmeNode1236@@QAEXXZ:NEAR
EXTERN ?bfmeAdvance@Gen_008BD1D0@@QBEPAVBfmeNodeDB@@H@Z:NEAR
EXTERN ?bfmeAt@Gen_008A0C90@@QBEPAVBfmeSlotLD@@H@Z:NEAR
EXTERN ?bfmeCheckGC@@YAPAVBfmeItemGC@@PAV1@@Z:NEAR
EXTERN ?bfmeLine1226@BfmeR1226@@QAEXPAD@Z:NEAR
EXTERN ?bfmePop1232@BfmeA1232@@QAEXH@Z:NEAR
EXTERN ?bfmeTheCBC@@3HA:BYTE
EXTERN ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z:NEAR
EXTERN ?count@Rva008BD1B0Node@@QBEHXZ:NEAR
EXTERN ?d_008cf740@@YAXXZ:NEAR
EXTERN ?d_008d3050@@YAXXZ:NEAR
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?g_bfmeArgBase@@3PAPAVAptValue@@A:BYTE
EXTERN ?isKind13@Rva008A0F20Header@@QBEHXZ:NEAR
EXTERN ?ji_009f6ec6@@YAXXZ:NEAR
EXTERN ?keyValuePairs00898D80@KeyValuePairs00898D80@@QAE?AVRva8CD130String@@XZ:NEAR
EXTERN ?releaseAll@Rva008A0FF0ValueStack@@QAEXXZ:NEAR
EXTERN g_Va01057E97:NEAR
EXTERN g_Va01057EF7:NEAR
EXTERN g_Va01136440:BYTE
_TEXT SEGMENT

; ghidra: FUN_00ca0830  retail @ 0x008A0830 size 95
public ?d_008a0830@@YAXXZ
?d_008a0830@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 0B0h, 12h, 00h, 00h, 8Bh, 4Eh, 08h, 8Bh, 16h, 8Dh, 04h
    db 80h, 57h, 8Dh, 79h, 14h, 8Dh, 04h, 82h, 3Bh, 0F8h, 75h, 02h, 8Bh, 0FAh, 3Bh, 7Eh
    db 04h, 74h, 37h, 0C7h, 01h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 8Bh, 51h, 50h
    db 8Bh, 52h, 28h, 8Bh, 46h, 08h, 89h, 50h, 08h, 8Bh, 46h, 08h, 8Bh, 54h, 24h, 0Ch
    db 89h, 50h, 0Ch, 8Bh, 46h, 08h, 89h, 48h, 10h, 8Bh, 11h, 0FFh, 12h, 8Bh, 46h, 08h
    db 8Bh, 4Ch, 24h, 14h, 89h, 48h, 04h, 89h, 7Eh, 08h, 5Fh, 5Eh, 0C2h, 0Ch, 00h
?d_008a0830@@YAXXZ ENDP

; ghidra: FUN_00ca0890  retail @ 0x008A0890 size 92
public ?d_008a0890@@YAXXZ
?d_008a0890@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 0Eh, 83h, 0E8h, 14h, 3Bh, 0C1h, 73h, 0Dh, 8Bh
    db 86h, 0B0h, 12h, 00h, 00h, 8Dh, 04h, 80h, 8Dh, 44h, 81h, 0ECh, 3Bh, 46h, 08h, 74h
    db 37h, 8Bh, 4Ch, 24h, 0Ch, 89h, 46h, 04h, 8Bh, 51h, 50h, 8Bh, 52h, 28h, 89h, 50h
    db 08h, 8Bh, 46h, 04h, 0C7h, 00h, 00h, 00h, 00h, 00h, 8Bh, 56h, 04h, 8Bh, 44h, 24h
    db 08h, 89h, 42h, 0Ch, 8Bh, 56h, 04h, 89h, 4Ah, 10h, 8Bh, 01h, 0FFh, 10h, 8Bh, 4Eh
    db 04h, 8Bh, 54h, 24h, 10h, 89h, 51h, 04h, 5Eh, 0C2h, 0Ch, 00h
?d_008a0890@@YAXXZ ENDP

; ghidra: FUN_00ca08f0  retail @ 0x008A08F0 size 109
public ?d_008a08f0@@YAXXZ
?d_008a08f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 0B0h, 12h, 00h, 00h, 8Bh, 4Eh, 08h, 8Bh, 16h, 8Dh, 04h
    db 80h, 57h, 8Dh, 79h, 14h, 8Dh, 04h, 82h, 3Bh, 0F8h, 75h, 02h, 8Bh, 0FAh, 3Bh, 7Eh
    db 04h, 74h, 45h, 8Bh, 54h, 24h, 18h, 0C7h, 01h, 01h, 00h, 00h, 00h, 8Bh, 4Eh, 08h
    db 89h, 51h, 04h, 8Bh, 46h, 08h, 8Bh, 4Ch, 24h, 0Ch, 89h, 48h, 08h, 8Bh, 56h, 08h
    db 8Bh, 4Ah, 08h, 8Bh, 01h, 0FFh, 10h, 8Bh, 4Eh, 08h, 8Bh, 54h, 24h, 10h, 89h, 51h
    db 0Ch, 8Bh, 46h, 08h, 8Bh, 48h, 0Ch, 8Bh, 11h, 0FFh, 12h, 8Bh, 46h, 08h, 8Bh, 4Ch
    db 24h, 14h, 89h, 48h, 10h, 89h, 7Eh, 08h, 5Fh, 5Eh, 0C2h, 10h, 00h
?d_008a08f0@@YAXXZ ENDP

; ghidra: FUN_00ca0960  retail @ 0x008A0960 size 106
public ?d_008a0960@@YAXXZ
?d_008a0960@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 0Eh, 83h, 0E8h, 14h, 3Bh, 0C1h, 73h, 0Dh, 8Bh
    db 86h, 0B0h, 12h, 00h, 00h, 8Dh, 04h, 80h, 8Dh, 44h, 81h, 0ECh, 3Bh, 46h, 08h, 74h
    db 45h, 8Bh, 54h, 24h, 14h, 89h, 46h, 04h, 0C7h, 00h, 01h, 00h, 00h, 00h, 8Bh, 4Eh
    db 04h, 89h, 51h, 04h, 8Bh, 46h, 04h, 8Bh, 4Ch, 24h, 08h, 89h, 48h, 08h, 8Bh, 56h
    db 04h, 8Bh, 4Ah, 08h, 8Bh, 01h, 0FFh, 10h, 8Bh, 4Eh, 04h, 8Bh, 54h, 24h, 0Ch, 89h
    db 51h, 0Ch, 8Bh, 46h, 04h, 8Bh, 48h, 0Ch, 8Bh, 11h, 0FFh, 12h, 8Bh, 46h, 04h, 8Bh
    db 4Ch, 24h, 10h, 89h, 48h, 10h, 5Eh, 0C2h, 10h, 00h
?d_008a0960@@YAXXZ ENDP

; ghidra: FUN_00ca09d0  retail @ 0x008A09D0 size 291
_TEXT ENDS
_TEXT$d00ca09d0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA09D0 size 291
public ?d_008a09d0@@YAXXZ
?d_008a09d0@@YAXXZ PROC
    db 053h, 055h, 056h, 08Bh, 0F1h, 08Bh, 05Eh, 004h, 08Bh, 06Eh, 008h, 057h, 08Bh, 0FBh, 03Bh, 0FDh
    db 00Fh, 084h, 006h, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 014h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 083h, 03Fh, 000h, 075h, 013h, 039h, 04Fh, 010h, 075h, 00Eh, 03Bh, 0FDh, 072h, 02Dh, 03Bh, 0FBh
    db 077h, 07Dh, 00Fh, 084h, 0CAh, 000h, 000h, 000h, 08Bh, 086h, 0B0h, 012h, 000h, 000h, 08Bh, 016h
    db 08Dh, 004h, 080h, 083h, 0C7h, 014h, 08Dh, 004h, 082h, 03Bh, 0F8h, 075h, 002h, 08Bh, 0FAh, 03Bh
    db 07Eh, 008h, 075h, 0CCh, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 004h, 000h, 08Bh, 011h, 0FFh, 052h, 004h
    db 08Bh, 04Eh, 008h, 02Bh, 0CFh, 0B8h, 067h, 066h, 066h, 066h, 0F7h, 0E9h, 0C1h, 0FAh, 003h, 08Bh
    db 0C2h, 0C1h, 0E8h, 01Fh, 08Dh, 044h, 002h, 0FFh, 08Dh, 00Ch, 080h, 0C1h, 0E1h, 002h, 051h, 08Dh
    db 057h, 014h, 052h, 057h
    call ?ji_009f6ec6@@YAXXZ
    db 08Bh, 046h, 008h, 08Bh, 00Eh, 083h, 0E8h, 014h, 083h, 0C4h, 00Ch, 03Bh, 0C1h, 073h, 00Dh, 08Bh
    db 086h, 0B0h, 012h, 000h, 000h, 08Dh, 004h, 080h, 08Dh, 044h, 081h, 0ECh, 05Fh, 089h, 046h, 008h
    db 05Eh, 05Dh, 05Bh, 0C2h, 004h, 000h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 04Eh, 004h, 02Bh, 0F9h
    db 0B8h, 067h, 066h, 066h, 066h, 0F7h, 0EFh, 0C1h, 0FAh, 003h, 08Bh, 0C2h, 0C1h, 0E8h, 01Fh, 003h
    db 0C2h, 08Dh, 004h, 080h, 0C1h, 0E0h, 002h, 050h, 051h, 083h, 0C1h, 014h, 051h
    call ?ji_009f6ec6@@YAXXZ
    db 08Bh, 08Eh, 0B0h, 012h, 000h, 000h, 08Bh, 046h, 004h, 08Bh, 016h, 08Dh, 00Ch, 089h, 083h, 0C0h
    db 014h, 08Dh, 00Ch, 08Ah, 083h, 0C4h, 00Ch, 03Bh, 0C1h, 075h, 002h, 08Bh, 0C2h, 05Fh, 089h, 046h
    db 004h, 05Eh, 05Dh, 05Bh, 0C2h, 004h, 000h, 08Bh, 086h, 0B0h, 012h, 000h, 000h, 08Bh, 016h, 08Dh
    db 004h, 080h, 08Dh, 04Bh, 014h, 08Dh, 004h, 082h, 03Bh, 0C8h, 075h, 002h, 08Bh, 0CAh, 089h, 04Eh
    db 004h, 05Fh, 05Eh, 05Dh, 05Bh, 0C2h, 004h, 000h
?d_008a09d0@@YAXXZ ENDP
_TEXT$d00ca09d0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca0b00  retail @ 0x008A0B00 size 61
public ?d_008a0b00@@YAXXZ
?d_008a0b00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 18h, 08h, 00h, 00h, 57h, 33h, 0FFh, 85h, 0C0h, 7Eh, 20h
    db 53h, 33h, 0DBh, 8Bh, 86h, 1Ch, 08h, 00h, 00h, 8Bh, 0Ch, 03h, 8Bh, 11h, 0FFh, 52h
    db 04h, 8Bh, 86h, 18h, 08h, 00h, 00h, 47h, 83h, 0C3h, 1Ch, 3Bh, 0F8h, 7Ch, 0E4h, 5Bh
    db 5Fh, 0C7h, 86h, 18h, 08h, 00h, 00h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_008a0b00@@YAXXZ ENDP

; ghidra: FUN_00ca0b40  retail @ 0x008A0B40 size 96
public ?d_008a0b40@@YAXXZ
?d_008a0b40@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 18h, 08h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 6Bh, 0C0h, 1Ch
    db 8Bh, 96h, 1Ch, 08h, 00h, 00h, 89h, 0Ch, 10h, 8Bh, 01h, 0FFh, 10h, 8Bh, 8Eh, 18h
    db 08h, 00h, 00h, 8Bh, 96h, 1Ch, 08h, 00h, 00h, 6Bh, 0C9h, 1Ch, 8Dh, 44h, 11h, 04h
    db 8Bh, 4Ch, 24h, 0Ch, 8Bh, 11h, 89h, 10h, 8Bh, 51h, 04h, 89h, 50h, 04h, 8Bh, 51h
    db 08h, 89h, 50h, 08h, 8Bh, 51h, 0Ch, 89h, 50h, 0Ch, 8Bh, 51h, 10h, 89h, 50h, 10h
    db 8Bh, 49h, 14h, 89h, 48h, 14h, 0FFh, 86h, 18h, 08h, 00h, 00h, 5Eh, 0C2h, 08h, 00h
?d_008a0b40@@YAXXZ ENDP

; ghidra: FUN_00ca0ba0  retail @ 0x008A0BA0 size 112
public ?d_008a0ba0@@YAXXZ
?d_008a0ba0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 86h, 18h, 08h, 00h, 00h, 33h, 0DBh, 48h, 78h, 63h, 55h
    db 8Bh, 6Ch, 24h, 10h, 57h, 33h, 0FFh, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 8Eh, 1Ch, 08h, 00h, 00h, 3Bh, 2Ch, 0Fh, 75h, 36h, 8Bh, 55h, 00h, 8Bh, 0CDh
    db 0FFh, 52h, 04h, 8Bh, 8Eh, 18h, 08h, 00h, 00h, 8Bh, 86h, 1Ch, 08h, 00h, 00h, 2Bh
    db 0CBh, 6Bh, 0C9h, 1Ch, 03h, 0C7h, 51h, 8Dh, 50h, 1Ch, 52h, 50h, 0E8h, 0D5h, 62h, 15h
    db 00h, 8Bh, 86h, 18h, 08h, 00h, 00h, 83h, 0C4h, 0Ch, 48h, 89h, 86h, 18h, 08h, 00h
    db 00h, 8Bh, 86h, 18h, 08h, 00h, 00h, 43h, 83h, 0C7h, 1Ch, 48h, 3Bh, 0D8h, 7Eh, 0B0h
?d_008a0ba0@@YAXXZ ENDP

; ghidra: FUN_00ca0c30  retail @ 0x008A0C30 size 39
public ?d_008a0c30@@YAXXZ
?d_008a0c30@@YAXXZ PROC
    db 8Bh, 89h, 9Ch, 12h, 00h, 00h, 85h, 0C9h, 74h, 18h, 8Bh, 44h, 24h, 04h, 85h, 0C0h
    db 74h, 0Bh, 3Bh, 0C1h, 74h, 0Ch, 8Bh, 40h, 4Ch, 85h, 0C0h, 75h, 0F5h, 0B0h, 01h, 0C2h
    db 04h, 00h, 32h, 0C0h, 0C2h, 04h, 00h
?d_008a0c30@@YAXXZ ENDP

; ghidra: FUN_00ca0c90  retail @ 0x008A0C90 size 70
public ?d_008a0c90@@YAXXZ
?d_008a0c90@@YAXXZ PROC
    db 56h, 8Bh, 31h, 57h, 8Bh, 0B9h, 0B0h, 12h, 00h, 00h, 8Bh, 49h, 04h, 2Bh, 0CEh, 0B8h
    db 67h, 66h, 66h, 66h, 0F7h, 0E9h, 8Bh, 4Ch, 24h, 0Ch, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h
    db 0E8h, 1Fh, 03h, 0C2h, 03h, 0C1h, 99h, 0F7h, 0FFh, 85h, 0D2h, 7Ch, 0Bh, 8Dh, 04h, 92h
    db 5Fh, 8Dh, 04h, 86h, 5Eh, 0C2h, 04h, 00h, 8Dh, 04h, 17h, 8Dh, 0Ch, 80h, 5Fh, 8Dh
    db 04h, 8Eh, 5Eh, 0C2h, 04h, 00h
?d_008a0c90@@YAXXZ ENDP

; ghidra: FUN_00ca0cf0  retail @ 0x008A0CF0 size 61
public ?d_008a0cf0@@YAXXZ
?d_008a0cf0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 0BFh, 01h, 00h, 00h, 00h, 3Bh, 0DFh, 8Bh, 0F1h
    db 7Ch, 1Fh, 8Bh, 06h, 8Bh, 4Eh, 08h, 2Bh, 0C7h, 8Bh, 0Ch, 81h, 8Bh, 51h, 04h, 0C1h
    db 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 47h, 3Bh, 0FBh, 7Eh
    db 0E1h, 8Bh, 06h, 2Bh, 0C3h, 5Fh, 89h, 06h, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_008a0cf0@@YAXXZ ENDP

; ghidra: FUN_00ca0d60  retail @ 0x008A0D60 size 25
public ?d_008a0d60@@YAXXZ
?d_008a0d60@@YAXXZ PROC
    db 8Bh, 41h, 08h, 85h, 0C0h, 74h, 11h, 8Bh, 49h, 04h, 0C1h, 0E1h, 02h, 51h, 50h, 0FFh
    db 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 0C3h
?d_008a0d60@@YAXXZ ENDP

; ghidra: FUN_00ca0da0  retail @ 0x008A0DA0 size 21
public ?d_008a0da0@@YAXXZ
?d_008a0da0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 8Bh, 4Eh, 08h, 8Bh, 4Ch, 81h, 0FCh, 8Bh, 11h, 0FFh, 52h
    db 04h, 0FFh, 0Eh, 5Eh, 0C3h
?d_008a0da0@@YAXXZ ENDP

; ghidra: FUN_00ca0dc0  retail @ 0x008A0DC0 size 48
public ?d_008a0dc0@@YAXXZ
?d_008a0dc0@@YAXXZ PROC
    db 53h, 8Bh, 19h, 56h, 57h, 33h, 0FFh, 8Dh, 71h, 04h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 0Ah, 8Bh, 0C8h, 8Bh, 01h, 0FFh, 50h, 04h, 4Bh, 74h, 0Ch
    db 47h, 83h, 0C6h, 04h, 81h, 0FFh, 00h, 02h, 00h, 00h, 7Ch, 0E4h, 5Fh, 5Eh, 5Bh, 0C3h
?d_008a0dc0@@YAXXZ ENDP

; ghidra: FUN_00ca0e00  retail @ 0x008A0E00 size 104
public ?d_008a0e00@@YAXXZ
?d_008a0e00@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 4Ch, 24h, 0Ch, 33h, 0F6h, 8Dh, 47h, 08h, 8Dh, 49h, 00h
    db 39h, 48h, 0FCh, 74h, 2Eh, 39h, 08h, 74h, 1Fh, 39h, 48h, 04h, 74h, 1Dh, 39h, 48h
    db 08h, 74h, 1Dh, 83h, 0C6h, 04h, 83h, 0C0h, 10h, 81h, 0FEh, 00h, 02h, 00h, 00h, 7Ch
    db 0DFh, 5Fh, 33h, 0C0h, 5Eh, 0C2h, 04h, 00h, 46h, 0EBh, 08h, 83h, 0C6h, 02h, 0EBh, 03h
    db 83h, 0C6h, 03h, 81h, 0FEh, 00h, 02h, 00h, 00h, 7Dh, 0E6h, 0FFh, 0Fh, 8Bh, 4Ch, 0B7h
    db 04h, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h, 44h, 0B7h, 04h, 00h, 00h, 00h, 00h, 5Fh, 0B8h
    db 01h, 00h, 00h, 00h, 5Eh, 0C2h, 04h, 00h
?d_008a0e00@@YAXXZ ENDP

; ghidra: FUN_00ca0e70  retail @ 0x008A0E70 size 45
public ?d_008a0e70@@YAXXZ
?d_008a0e70@@YAXXZ PROC
    db 53h, 8Bh, 19h, 56h, 57h, 33h, 0FFh, 8Dh, 71h, 04h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 0Ah, 8Bh, 0C8h, 8Bh, 01h, 0FFh, 50h, 04h, 4Bh, 74h, 09h
    db 47h, 83h, 0C6h, 04h, 83h, 0FFh, 40h, 7Ch, 0E7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_008a0e70@@YAXXZ ENDP

; ghidra: FUN_00ca0f20  retail @ 0x008A0F20 size 31
public ?d_008a0f20@@YAXXZ
?d_008a0f20@@YAXXZ PROC
    db 8Bh, 41h, 04h, 8Bh, 0C8h, 83h, 0E1h, 3Fh, 80h, 0F9h, 13h, 75h, 0Fh, 0C1h, 0E8h, 0Fh
    db 0F6h, 0D0h, 0A8h, 01h, 75h, 06h, 0B8h, 01h, 00h, 00h, 00h, 0C3h, 33h, 0C0h, 0C3h
?d_008a0f20@@YAXXZ ENDP

; ghidra: FUN_00ca0f40  retail @ 0x008A0F40 size 170
public ?d_008a0f40@@YAXXZ
?d_008a0f40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 48h, 7Ch, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 7Ch, 85h, 0C9h, 74h, 78h
    db 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 04h, 98h, 52h, 2Dh, 01h, 8Dh
    db 44h, 24h, 04h, 50h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0E8h, 3Fh, 76h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 18h, 51h, 68h, 0B8h, 63h, 13h, 01h, 0FFh, 15h, 3Ch, 78h, 33h
    db 01h, 8Bh, 54h, 24h, 0Ch, 83h, 0C2h, 08h, 52h, 68h, 88h, 63h, 13h, 01h, 0FFh, 15h
    db 3Ch, 78h, 33h, 01h, 8Bh, 4Eh, 7Ch, 8Bh, 01h, 83h, 0C4h, 10h, 0FFh, 50h, 04h, 8Bh
    db 44h, 24h, 04h, 0C7h, 46h, 7Ch, 00h, 00h, 00h, 00h, 66h, 0FFh, 08h, 66h, 83h, 38h
    db 00h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h
    db 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_008a0f40@@YAXXZ ENDP

; ghidra: FUN_00ca11a0  retail @ 0x008A11A0 size 33
public ?d_008a11a0@@YAXXZ
?d_008a11a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 0Ch, 6Ah
    db 0Ch, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_008a11a0@@YAXXZ ENDP

; ghidra: FUN_00ca11e0  retail @ 0x008A11E0 size 184
public ?d_008a11e0@@YAXXZ
?d_008a11e0@@YAXXZ PROC
    db 0A1h, 0D0h, 87h, 33h, 01h, 85h, 0C0h, 56h, 57h, 74h, 3Ch, 8Bh, 48h, 08h, 8Bh, 15h
    db 10h, 78h, 33h, 01h, 89h, 0Dh, 0D0h, 87h, 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh
    db 4Ah, 04h, 7Ch, 11h, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 8Bh, 4Ch, 24h, 0Ch, 5Fh
    db 89h, 48h, 08h, 5Eh, 0C3h, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh, 01h, 8Bh, 4Ch, 24h
    db 0Ch, 5Fh, 89h, 48h, 08h, 5Eh, 0C3h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h
    db 0C4h, 04h, 85h, 0C0h, 74h, 5Dh, 8Bh, 48h, 04h, 81h, 0E1h, 07h, 80h, 00h, 0F0h, 81h
    db 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh, 35h
    db 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 53h, 8Bh, 1Eh, 8Dh, 56h, 04h, 3Bh, 0FBh, 5Bh
    db 7Ch, 19h, 8Bh, 54h, 24h, 0Ch, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 5Fh, 89h, 48h, 04h
    db 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 50h, 08h, 5Eh, 0C3h, 8Bh, 4Eh, 08h, 89h, 04h
    db 0B9h, 0FFh, 02h, 8Bh, 54h, 24h, 0Ch, 5Fh, 0C7h, 00h, 00h, 64h, 13h, 01h, 89h, 50h
    db 08h, 5Eh, 0C3h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
?d_008a11e0@@YAXXZ ENDP

; ghidra: FUN_00ca12a0  retail @ 0x008A12A0 size 26
public ?d_008a12a0@@YAXXZ
?d_008a12a0@@YAXXZ PROC
    db 8Bh, 41h, 34h, 8Bh, 40h, 0Ch, 80h, 78h, 08h, 3Ah, 75h, 08h, 0Fh, 0BEh, 40h, 09h
    db 83h, 0E8h, 30h, 0C3h, 0B8h, 06h, 00h, 00h, 00h, 0C3h
?d_008a12a0@@YAXXZ ENDP

; ghidra: FUN_00ca12c0  retail @ 0x008A12C0 size 381
public ?d_008a12c0@@YAXXZ
?d_008a12c0@@YAXXZ PROC
    db 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 20h, 33h, 0DBh, 85h, 0C0h, 57h, 7Eh, 2Dh, 33h
    db 0FFh, 8Bh, 46h, 24h, 8Bh, 54h, 38h, 04h, 8Bh, 4Ch, 38h, 0Ch, 03h, 0C7h, 52h, 0E8h
    db 6Ch, 0FDh, 0FFh, 0FFh, 8Bh, 4Eh, 24h, 8Bh, 54h, 0Fh, 08h, 8Bh, 4Eh, 10h, 89h, 04h
    db 91h, 8Bh, 46h, 20h, 43h, 83h, 0C7h, 10h, 3Bh, 0D8h, 7Ch, 0D5h, 8Bh, 46h, 0Ch, 33h
    db 0DBh, 85h, 0C0h, 89h, 5Ch, 24h, 0Ch, 0Fh, 8Eh, 29h, 01h, 00h, 00h, 33h, 0FFh, 55h
    db 8Bh, 56h, 10h, 8Bh, 0Ch, 17h, 85h, 0C9h, 0Fh, 84h, 04h, 01h, 00h, 00h, 8Bh, 01h
    db 83h, 0C0h, 0FDh, 83h, 0F8h, 05h, 0Fh, 87h, 0F6h, 00h, 00h, 00h, 0FFh, 24h, 85h, 40h
    db 14h, 0CAh, 00h, 8Bh, 41h, 08h, 8Bh, 4Ch, 24h, 1Ch, 50h, 53h, 51h, 0FFh, 15h, 94h
    db 78h, 33h, 01h, 83h, 0C4h, 0Ch, 0E9h, 0D7h, 00h, 00h, 00h, 8Bh, 46h, 10h, 8Bh, 0Ch
    db 07h, 8Bh, 51h, 08h, 8Bh, 04h, 90h, 89h, 41h, 08h, 8Bh, 46h, 10h, 8Bh, 0Ch, 07h
    db 8Bh, 51h, 0Ch, 8Bh, 04h, 90h, 89h, 41h, 0Ch, 0E9h, 0B4h, 00h, 00h, 00h, 8Bh, 41h
    db 2Ch, 33h, 0D2h, 85h, 0C0h, 7Eh, 34h, 33h, 0DBh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 10h, 8Bh, 0Ch, 07h, 8Bh, 49h, 30h, 8Bh, 6Ch, 19h, 04h, 8Bh, 04h, 0A8h
    db 8Dh, 4Ch, 19h, 04h, 89h, 01h, 8Bh, 4Eh, 10h, 8Bh, 04h, 0Fh, 8Bh, 48h, 2Ch, 42h
    db 83h, 0C3h, 44h, 3Bh, 0D1h, 7Ch, 0D9h, 8Bh, 5Ch, 24h, 10h, 8Bh, 4Eh, 10h, 8Bh, 14h
    db 0Fh, 8Bh, 42h, 3Ch, 85h, 0C0h, 74h, 6Ah, 8Bh, 50h, 04h, 85h, 0D2h, 74h, 06h, 8Bh
    db 0Ch, 91h, 89h, 48h, 04h, 8Bh, 48h, 0Ch, 85h, 0C9h, 74h, 09h, 8Bh, 56h, 10h, 8Bh
    db 0Ch, 8Ah, 89h, 48h, 0Ch, 8Bh, 08h, 85h, 0C9h, 74h, 08h, 8Bh, 56h, 10h, 8Bh, 0Ch
    db 8Ah, 89h, 08h, 8Bh, 48h, 08h, 85h, 0C9h, 74h, 38h, 8Bh, 56h, 10h, 8Bh, 0Ch, 8Ah
    db 89h, 48h, 08h, 0EBh, 2Dh, 8Bh, 51h, 0Ch, 33h, 0C0h, 85h, 0D2h, 7Eh, 24h, 8Bh, 0FFh
    db 8Bh, 4Eh, 10h, 8Bh, 14h, 0Fh, 8Bh, 52h, 10h, 8Bh, 2Ch, 82h, 8Bh, 0Ch, 0A9h, 8Dh
    db 14h, 82h, 89h, 0Ah, 8Bh, 56h, 10h, 8Bh, 0Ch, 17h, 8Bh, 51h, 0Ch, 40h, 3Bh, 0C2h
    db 7Ch, 0DEh, 8Bh, 46h, 0Ch, 43h, 83h, 0C7h, 04h, 3Bh, 0D8h, 89h, 5Ch, 24h, 10h, 0Fh
    db 8Ch, 0DBh, 0FEh, 0FFh, 0FFh, 5Dh, 5Fh, 5Eh, 5Bh, 59h, 0C2h, 08h, 00h
?d_008a12c0@@YAXXZ ENDP

; ghidra: FUN_00ca15f0  retail @ 0x008A15F0 size 718
_TEXT ENDS
_TEXT$d00ca15f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA15F0 size 718
public ?d_008a15f0@@YAXXZ
?d_008a15f0@@YAXXZ PROC
    db 083h, 0ECh, 00Ch, 056h, 08Bh, 0F1h, 08Bh, 086h, 034h, 012h, 000h, 000h, 08Bh, 00Dh
    dd ?Rva008A5380Holder@@3PADA
    db 057h, 089h, 044h, 024h, 008h, 08Bh, 081h, 0A4h, 012h, 000h, 000h, 033h, 0FFh, 03Bh, 0C7h, 089h
    db 07Ch, 024h, 00Ch, 00Fh, 08Eh, 09Bh, 002h, 000h, 000h, 053h, 055h, 08Dh, 049h, 000h, 08Bh, 096h
    db 030h, 012h, 000h, 000h, 08Bh, 00Ch, 017h, 085h, 0C9h, 08Dh, 004h, 017h, 00Fh, 084h, 060h, 002h
    db 000h, 000h, 0DBh, 044h, 024h, 020h, 0D8h, 068h, 00Ch, 0D9h, 058h, 00Ch, 08Bh, 086h, 030h, 012h
    db 000h, 000h, 0D9h, 044h, 007h, 00Ch, 08Dh, 01Ch, 007h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Ah, 032h, 002h, 000h, 000h, 08Bh, 06Bh, 004h, 08Bh, 045h
    db 004h, 08Bh, 0C8h, 083h, 0E1h, 03Fh, 080h, 0F9h, 009h, 00Fh, 085h, 0CBh, 000h, 000h, 000h, 0C1h
    db 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 00Fh, 085h, 0BEh, 000h, 000h, 000h, 08Bh, 043h, 014h, 085h
    db 0C0h, 07Eh, 069h, 033h, 0DBh, 085h, 0C0h, 07Eh, 04Eh, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh
    db 096h, 030h, 012h, 000h, 000h, 08Bh, 04Ch, 017h, 014h, 08Dh, 044h, 017h, 014h, 08Bh, 050h, 008h
    db 0A1h
    dd ?g_bfmeArgBase@@3PAPAVAptValue@@A
    db 02Bh, 0CBh, 08Bh, 04Ch, 08Ah, 0FCh, 08Bh, 015h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 089h, 00Ch, 090h, 0FFh, 005h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 08Bh, 041h, 004h, 0C1h, 0E8h, 01Eh, 0A8h, 001h, 075h, 004h, 08Bh, 011h, 0FFh, 012h, 08Bh, 086h
    db 030h, 012h, 000h, 000h, 08Bh, 04Ch, 007h, 014h, 043h, 03Bh, 0D9h, 07Ch, 0B8h, 08Bh, 08Eh, 030h
    db 012h, 000h, 000h, 08Bh, 054h, 00Fh, 014h, 08Dh, 004h, 00Fh, 08Bh, 040h, 010h, 052h, 055h, 050h
    db 0EBh, 007h, 08Bh, 04Bh, 010h, 06Ah, 0FFh, 055h, 051h, 0B9h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    call ?d_008cf740@@YAXXZ
    db 08Bh, 015h
    dd ?g_bfmeArgBase@@3PAPAVAptValue@@A
    db 0A1h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 08Bh, 04Ch, 082h, 0FCh, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh
    db 001h, 0FFh, 050h, 004h, 0FFh, 00Dh
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 08Bh, 08Eh, 030h, 012h, 000h, 000h, 0D9h, 044h, 00Fh, 008h, 08Dh, 004h, 00Fh, 0D8h, 040h, 00Ch
    db 0D9h, 058h, 00Ch, 0E9h, 053h, 001h, 000h, 000h, 08Bh, 045h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh
    db 080h, 0FAh, 00Ah, 00Fh, 085h, 042h, 001h, 000h, 000h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h
    db 00Fh, 085h, 035h, 001h, 000h, 000h, 08Bh, 045h, 030h, 085h, 0C0h, 00Fh, 084h, 002h, 001h, 000h
    db 000h, 08Bh, 04Dh, 028h, 08Bh, 041h, 004h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 089h, 04Ch
    db 024h, 018h, 00Fh, 085h, 0EBh, 000h, 000h, 000h
    call ?isKind13@Rva008A0F20Header@@QBEHXZ
    db 084h, 0C0h, 00Fh, 085h, 0DEh, 000h, 000h, 000h, 08Bh, 043h, 014h, 085h, 0C0h, 00Fh, 08Eh, 07Eh
    db 000h, 000h, 000h, 033h, 0DBh, 085h, 0C0h, 07Eh, 050h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 08Bh, 08Eh, 030h, 012h, 000h, 000h, 08Bh, 054h, 00Fh, 014h, 08Dh, 044h, 00Fh, 014h, 08Bh, 040h
    db 008h, 02Bh, 0D3h, 08Bh, 04Ch, 090h, 0FCh, 08Bh, 015h
    dd ?g_bfmeArgBase@@3PAPAVAptValue@@A
    db 0A1h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 089h, 00Ch, 082h, 0FFh, 005h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 004h, 08Bh, 001h, 0FFh, 010h, 08Bh
    db 08Eh, 030h, 012h, 000h, 000h, 08Bh, 044h, 00Fh, 014h, 043h, 03Bh, 0D8h, 07Ch, 0B7h, 08Bh, 096h
    db 030h, 012h, 000h, 000h, 08Bh, 04Ch, 017h, 010h, 08Dh, 004h, 017h, 03Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 074h, 008h, 08Bh, 040h, 014h, 050h, 055h, 051h, 0EBh, 021h, 08Bh, 048h, 014h, 08Bh, 055h, 028h
    db 051h, 055h, 052h, 0EBh, 016h, 08Bh, 05Bh, 010h, 03Bh, 01Dh
    dd ?bfmeTheCBC@@3HA
    db 06Ah, 000h, 055h, 074h, 003h, 053h, 0EBh, 005h, 08Bh, 044h, 024h, 020h, 050h, 0B9h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    call ?d_008cf740@@YAXXZ
    db 068h
    dd g_Va01136440
    db 0B9h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    call ?bfmeLine1226@BfmeR1226@@QAEXPAD@Z
    db 08Bh, 00Dh
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    db 051h, 0B9h
    dd ?Rva008AE770TheStack@@3URva008AE770Stack@@A
    call ?bfmePop1232@BfmeA1232@@QAEXH@Z
    db 08Bh, 096h, 030h, 012h, 000h, 000h, 0D9h, 044h, 017h, 008h, 08Dh, 004h, 017h, 0D8h, 040h, 00Ch
    db 0D9h, 058h, 00Ch, 0EBh, 028h, 08Bh, 04Bh, 004h, 08Bh, 001h, 0FFh, 050h, 004h, 08Bh, 08Eh, 030h
    db 012h, 000h, 000h, 003h, 0CFh
    call ?releaseAll@Rva008A0FF0ValueStack@@QAEXXZ
    db 08Bh, 08Eh, 030h, 012h, 000h, 000h, 0C7h, 004h, 00Fh, 000h, 000h, 000h, 000h, 0FFh, 08Eh, 034h
    db 012h, 000h, 000h, 0FFh, 04Ch, 024h, 010h, 074h, 020h, 08Bh, 044h, 024h, 014h, 08Bh, 015h
    dd ?Rva008A5380Holder@@3PADA
    db 08Bh, 08Ah, 0A4h, 012h, 000h, 000h, 040h, 083h, 0C7h, 020h, 03Bh, 0C1h, 089h, 044h, 024h, 014h
    db 00Fh, 08Ch, 06Ch, 0FDh, 0FFh, 0FFh, 05Dh, 05Bh, 05Fh, 05Eh, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h
?d_008a15f0@@YAXXZ ENDP
_TEXT$d00ca15f0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca18c0  retail @ 0x008A18C0 size 128
_TEXT ENDS
_TEXT$d00ca18c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA18C0 size 128
public ?d_008a18c0@@YAXXZ
?d_008a18c0@@YAXXZ PROC
    db 056h, 08Bh, 0F1h, 08Bh, 046h, 010h, 057h, 033h, 0FFh, 085h, 0C0h, 07Eh, 069h, 08Dh, 049h, 000h
    db 08Bh, 046h, 00Ch, 08Bh, 00Ch, 0B8h, 08Bh, 041h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h, 0FAh
    db 00Eh, 075h, 01Ch, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 013h, 08Bh, 041h, 050h, 08Bh
    db 050h, 01Ch, 085h, 0D2h, 075h, 02Dh, 06Ah, 001h
    call ?d_008d3050@@YAXXZ
    db 0EBh, 024h, 08Bh, 041h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h, 0FAh, 00Dh, 075h, 017h, 0C1h
    db 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 00Eh, 08Bh, 041h, 050h, 083h, 078h, 018h, 0FFh, 075h
    db 005h
    call ?bfmeActivate1236@BfmeNode1236@@QAEXXZ
    db 08Bh, 04Eh, 00Ch, 08Bh, 00Ch, 0B9h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 046h, 010h, 047h, 03Bh
    db 0F8h, 07Ch, 09Ah, 05Fh, 0C7h, 046h, 010h, 000h, 000h, 000h, 000h, 05Eh, 0C3h
?d_008a18c0@@YAXXZ ENDP
_TEXT$d00ca18c0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca1940  retail @ 0x008A1940 size 621
public ?d_008a1940@@YAXXZ
?d_008a1940@@YAXXZ PROC
    db 51h, 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 04h, 8Bh, 4Fh, 08h, 3Bh, 0F1h, 89h, 7Ch, 24h
    db 08h, 0Fh, 84h, 43h, 02h, 00h, 00h, 53h, 55h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 06h, 85h, 0C0h, 8Bh, 0E9h, 75h, 7Ch, 8Bh, 46h, 04h, 0A3h, 0ACh, 87h, 33h, 01h
    db 8Bh, 46h, 10h, 8Bh, 48h, 04h, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 0Fh, 85h
    db 0AAh, 01h, 00h, 00h, 8Bh, 48h, 04h, 8Bh, 0D1h, 83h, 0E2h, 3Fh, 80h, 0FAh, 13h, 75h
    db 0Eh, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 0Fh, 84h, 8Fh, 01h, 00h, 00h, 8Bh
    db 4Eh, 08h, 85h, 0C9h, 7Dh, 10h, 8Bh, 50h, 50h, 8Bh, 5Ah, 18h, 0F7h, 0D9h, 3Bh, 0CBh
    db 0Fh, 85h, 78h, 01h, 00h, 00h, 6Ah, 0FFh, 50h, 8Bh, 46h, 0Ch, 8Bh, 08h, 51h, 0B9h
    db 48h, 87h, 33h, 01h, 0E8h, 07h, 0B5h, 02h, 00h, 68h, 70h, 64h, 13h, 01h, 0B9h, 48h
    db 87h, 33h, 01h, 0E8h, 68h, 0F5h, 0FFh, 0FFh, 8Bh, 0CFh, 0E8h, 0E1h, 0FEh, 0FFh, 0FFh, 0E9h
    db 4Ah, 01h, 00h, 00h, 83h, 0F8h, 01h, 0Fh, 85h, 41h, 01h, 00h, 00h, 8Bh, 56h, 04h
    db 0A1h, 80h, 87h, 33h, 01h, 89h, 15h, 0ACh, 87h, 33h, 01h, 8Bh, 4Eh, 08h, 8Bh, 15h
    db 78h, 87h, 33h, 01h, 89h, 0Ch, 90h, 0FFh, 05h, 78h, 87h, 33h, 01h, 8Bh, 01h, 0FFh
    db 10h, 8Bh, 46h, 04h, 85h, 0C0h, 0Fh, 84h, 0A9h, 00h, 00h, 00h, 24h, 03h, 3Ch, 01h
    db 0Fh, 85h, 9Fh, 00h, 00h, 00h, 8Bh, 46h, 04h, 8Bh, 4Eh, 10h, 8Bh, 0D8h, 0C1h, 0EBh
    db 0Ah, 8Bh, 0F8h, 0C1h, 0EFh, 11h, 83h, 0E3h, 7Fh, 85h, 0C9h, 0Fh, 8Eh, 80h, 00h, 00h
    db 00h, 25h, 0FCh, 03h, 00h, 00h, 83h, 0F8h, 04h, 75h, 76h, 0F6h, 0C3h, 07h, 74h, 71h
    db 83h, 0F9h, 01h, 7Eh, 2Fh, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 8Bh, 89h, 68h, 12h, 00h
    db 00h, 8Bh, 15h, 48h, 87h, 33h, 01h, 0A1h, 50h, 87h, 33h, 01h, 89h, 0Ch, 90h, 0FFh
    db 05h, 48h, 87h, 33h, 01h, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 04h
    db 8Bh, 01h, 0FFh, 10h, 83h, 0FBh, 04h, 75h, 02h, 0F7h, 0DFh, 57h, 0E8h, 4Fh, 0F7h, 0FFh
    db 0FFh, 8Bh, 0Dh, 48h, 87h, 33h, 01h, 8Bh, 15h, 50h, 87h, 33h, 01h, 89h, 04h, 8Ah
    db 8Bh, 1Dh, 48h, 87h, 33h, 01h, 83h, 0C4h, 04h, 43h, 89h, 1Dh, 48h, 87h, 33h, 01h
    db 8Bh, 48h, 04h, 0C1h, 0E9h, 1Eh, 0F6h, 0C1h, 01h, 75h, 06h, 8Bh, 10h, 8Bh, 0C8h, 0FFh
    db 12h, 8Bh, 7Ch, 24h, 10h, 8Bh, 46h, 10h, 8Bh, 4Eh, 0Ch, 8Bh, 56h, 08h, 50h, 51h
    db 52h, 0B9h, 48h, 87h, 33h, 01h, 0E8h, 65h, 0DCh, 02h, 00h, 68h, 54h, 64h, 13h, 01h
    db 0B9h, 48h, 87h, 33h, 01h, 0E8h, 56h, 0F4h, 0FFh, 0FFh, 0A1h, 78h, 87h, 33h, 01h, 8Bh
    db 0Dh, 80h, 87h, 33h, 01h, 8Bh, 4Ch, 81h, 0FCh, 8Bh, 11h, 0FFh, 52h, 04h, 0A1h, 78h
    db 87h, 33h, 01h, 8Bh, 0Dh, 50h, 87h, 33h, 01h, 48h, 0A3h, 78h, 87h, 33h, 01h, 0A1h
    db 48h, 87h, 33h, 01h, 8Bh, 4Ch, 81h, 0FCh, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h
    db 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 0FFh, 0Dh, 48h, 87h, 33h, 01h, 0A1h, 48h
    db 87h, 33h, 01h, 85h, 0C0h, 7Eh, 20h, 8Bh, 0Dh, 50h, 87h, 33h, 01h, 8Bh, 4Ch, 81h
    db 0FCh, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h
    db 04h, 0FFh, 0Dh, 48h, 87h, 33h, 01h, 8Bh, 4Fh, 08h, 3Bh, 0E9h, 76h, 1Bh, 2Bh, 0E9h
    db 8Bh, 0D5h, 0B8h, 99h, 99h, 99h, 99h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h
    db 1Fh, 03h, 0C2h, 8Dh, 14h, 80h, 8Dh, 34h, 96h, 8Bh, 87h, 0B0h, 12h, 00h, 00h, 8Bh
    db 17h, 8Dh, 04h, 80h, 83h, 0C6h, 14h, 8Dh, 04h, 82h, 3Bh, 0F0h, 75h, 02h, 8Bh, 0F2h
    db 3Bh, 0F1h, 0Fh, 85h, 0C8h, 0FDh, 0FFh, 0FFh, 5Dh, 5Bh, 8Bh, 0CFh, 0E8h, 1Fh, 0FDh, 0FFh
    db 0FFh, 8Bh, 0CFh, 5Fh, 5Eh, 83h, 0C4h, 04h, 0E9h, 23h, 0ECh, 0FFh, 0FFh
?d_008a1940@@YAXXZ ENDP

; ghidra: FUN_00ca1c20  retail @ 0x008A1C20 size 196
_TEXT ENDS
_TEXT$d00ca1c20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA1C20 size 196
public ?d_008a1c20@@YAXXZ
?d_008a1c20@@YAXXZ PROC
    db 083h, 0ECh, 008h, 056h, 08Bh, 0F1h, 08Bh, 086h, 034h, 012h, 000h, 000h, 057h, 033h, 0FFh, 03Bh
    db 0C7h, 089h, 044h, 024h, 008h, 00Fh, 084h, 0A1h, 000h, 000h, 000h, 0A1h
    dd ?Rva008A5380Holder@@3PADA
    db 039h, 0B8h, 0A4h, 012h, 000h, 000h, 089h, 07Ch, 024h, 00Ch, 00Fh, 08Eh, 08Ch, 000h, 000h, 000h
    db 053h, 055h, 08Bh, 08Eh, 030h, 012h, 000h, 000h, 08Dh, 004h, 00Fh, 083h, 038h, 000h, 074h, 05Ah
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 052h, 050h, 085h, 0D2h, 074h, 049h, 08Bh, 068h, 004h, 08Bh, 04Dh
    db 004h, 08Bh, 0D9h, 083h, 0E3h, 03Fh, 080h, 0FBh, 00Ah, 075h, 039h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h
    db 0F6h, 0C1h, 001h, 075h, 02Fh, 08Bh, 04Dh, 024h, 03Bh, 04Ah, 00Ch, 075h, 027h, 08Bh, 0CDh, 08Bh
    db 011h, 0FFh, 052h, 004h, 08Bh, 08Eh, 030h, 012h, 000h, 000h, 003h, 0CFh
    call ?releaseAll@Rva008A0FF0ValueStack@@QAEXXZ
    db 08Bh, 086h, 030h, 012h, 000h, 000h, 0C7h, 004h, 007h, 000h, 000h, 000h, 000h, 0FFh, 08Eh, 034h
    db 012h, 000h, 000h, 0FFh, 04Ch, 024h, 010h, 074h, 020h, 08Bh, 044h, 024h, 014h, 08Bh, 00Dh
    dd ?Rva008A5380Holder@@3PADA
    db 08Bh, 091h, 0A4h, 012h, 000h, 000h, 040h, 083h, 0C7h, 020h, 03Bh, 0C2h, 089h, 044h, 024h, 014h
    db 00Fh, 08Ch, 078h, 0FFh, 0FFh, 0FFh, 05Dh, 05Bh, 05Fh, 05Eh, 083h, 0C4h, 008h, 0C2h, 004h, 000h
?d_008a1c20@@YAXXZ ENDP
_TEXT$d00ca1c20 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca1cf0  retail @ 0x008A1CF0 size 135
public ?d_008a1cf0@@YAXXZ
?d_008a1cf0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 8Bh, 49h, 24h, 0C1h, 0E0h, 04h, 8Bh, 54h, 08h, 0Ch, 03h
    db 0C1h, 8Bh, 4Ah, 10h, 8Bh, 51h, 30h, 53h, 55h, 56h, 33h, 0EDh, 85h, 0D2h, 57h, 7Eh
    db 4Bh, 8Bh, 49h, 34h, 8Bh, 40h, 04h, 89h, 4Ch, 24h, 10h, 89h, 44h, 24h, 18h, 8Bh
    db 0F9h, 8Bh, 37h, 8Bh, 44h, 24h, 18h, 8Ah, 18h, 8Ah, 0CBh, 3Ah, 1Eh, 75h, 1Ch, 84h
    db 0C9h, 74h, 14h, 8Ah, 58h, 01h, 8Ah, 0CBh, 3Ah, 5Eh, 01h, 75h, 0Eh, 83h, 0C0h, 02h
    db 83h, 0C6h, 02h, 84h, 0C9h, 75h, 0E0h, 33h, 0C0h, 0EBh, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh
    db 85h, 0C0h, 74h, 13h, 45h, 83h, 0C7h, 08h, 3Bh, 0EAh, 7Ch, 0C5h, 5Fh, 5Eh, 5Dh, 83h
    db 0C8h, 0FFh, 5Bh, 59h, 0C2h, 04h, 00h, 8Bh, 4Ch, 24h, 10h, 8Bh, 44h, 0E9h, 04h, 5Fh
    db 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_008a1cf0@@YAXXZ ENDP

; ghidra: FUN_00ca1d80  retail @ 0x008A1D80 size 102
public ?d_008a1d80@@YAXXZ
?d_008a1d80@@YAXXZ PROC
    db 8Bh, 49h, 04h, 8Bh, 11h, 33h, 0C0h, 85h, 0D2h, 7Eh, 58h, 53h, 8Bh, 5Ch, 24h, 0Ch
    db 57h, 8Bh, 79h, 04h, 8Bh, 0CFh, 56h, 8Bh, 31h, 83h, 3Eh, 08h, 75h, 05h, 39h, 5Eh
    db 04h, 74h, 0Eh, 40h, 83h, 0C1h, 04h, 3Bh, 0C2h, 7Ch, 0ECh, 5Eh, 5Fh, 5Bh, 0C2h, 08h
    db 00h, 8Bh, 4Ch, 24h, 10h, 8Bh, 14h, 87h, 8Bh, 42h, 08h, 6Ah, 0FFh, 51h, 50h, 0B9h
    db 48h, 87h, 33h, 01h, 0E8h, 07h, 0B1h, 02h, 00h, 68h, 8Ch, 64h, 13h, 01h, 0B9h, 48h
    db 87h, 33h, 01h, 0E8h, 68h, 0F1h, 0FFh, 0FFh, 8Bh, 4Eh, 04h, 0F7h, 0D9h, 89h, 4Eh, 04h
    db 5Eh, 5Fh, 5Bh, 0C2h, 08h, 00h
?d_008a1d80@@YAXXZ ENDP

; ghidra: FUN_00ca1df0  retail @ 0x008A1DF0 size 135
public ?d_008a1df0@@YAXXZ
?d_008a1df0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 8Bh, 4Eh, 08h, 2Bh, 0C8h, 0B8h, 67h, 66h
    db 66h, 66h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 57h, 78h
    db 04h, 8Bh, 0C8h, 0EBh, 08h, 8Bh, 8Eh, 0B0h, 12h, 00h, 00h, 03h, 0C8h, 8Bh, 86h, 18h
    db 08h, 00h, 00h, 8Bh, 56h, 10h, 8Dh, 0BCh, 48h, 82h, 04h, 00h, 00h, 8Bh, 8Eh, 2Ch
    db 12h, 00h, 00h, 03h, 0FAh, 0E8h, 76h, 0B3h, 01h, 00h, 8Bh, 8Eh, 0A4h, 12h, 00h, 00h
    db 8Bh, 96h, 34h, 12h, 00h, 00h, 03h, 0F8h, 33h, 0C0h, 85h, 0C9h, 7Eh, 24h, 8Bh, 0B6h
    db 30h, 12h, 00h, 00h, 53h, 83h, 3Eh, 00h, 74h, 0Ah, 4Ah, 8Bh, 5Eh, 14h, 8Dh, 7Ch
    db 1Fh, 01h, 74h, 08h, 40h, 83h, 0C6h, 20h, 3Bh, 0C1h, 7Ch, 0E9h, 5Bh, 8Bh, 0C7h, 5Fh
    db 5Eh, 0C3h, 8Bh, 0C7h, 5Fh, 5Eh, 0C3h
?d_008a1df0@@YAXXZ ENDP

; ghidra: FUN_00ca1e80  retail @ 0x008A1E80 size 483
_TEXT ENDS
_TEXT$d00ca1e80 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA1E80 size 483
public ?d_008a1e80@@YAXXZ
?d_008a1e80@@YAXXZ PROC
    db 053h, 08Bh, 05Ch, 024h, 00Ch, 085h, 0DBh, 075h, 00Ch, 08Bh, 044h, 024h, 008h, 08Bh, 080h, 06Ch
    db 012h, 000h, 000h, 05Bh, 0C3h, 083h, 0FBh, 001h, 075h, 00Ch, 08Bh, 04Ch, 024h, 008h, 08Bh, 081h
    db 09Ch, 012h, 000h, 000h, 05Bh, 0C3h, 056h, 057h, 08Bh, 07Ch, 024h, 010h, 08Bh, 057h, 004h, 08Bh
    db 04Fh, 008h, 02Bh, 0CAh, 0B8h, 067h, 066h, 066h, 066h, 0F7h, 0E9h, 0C1h, 0FAh, 003h, 08Bh, 0F2h
    db 0C1h, 0EEh, 01Fh, 083h, 0C3h, 0FEh, 003h, 0F2h, 078h, 004h, 08Bh, 0C6h, 0EBh, 008h, 08Bh, 087h
    db 0B0h, 012h, 000h, 000h, 003h, 0C6h, 08Dh, 014h, 000h, 03Bh, 0DAh, 07Dh, 047h, 08Bh, 0C3h, 099h
    db 02Bh, 0C2h, 0D1h, 0F8h, 050h, 08Bh, 0CFh
    call ?bfmeAt@Gen_008A0C90@@QBEPAVBfmeSlotLD@@H@Z
    db 08Bh, 008h, 085h, 0C9h, 075h, 012h, 0F6h, 0C3h, 001h, 074h, 007h, 08Bh, 040h, 010h, 05Fh, 05Eh
    db 05Bh, 0C3h, 05Fh, 05Eh, 033h, 0C0h, 05Bh, 0C3h, 083h, 0F9h, 001h, 075h, 01Bh, 084h, 0D9h, 074h
    db 007h, 08Bh, 040h, 008h, 05Fh, 05Eh, 05Bh, 0C3h, 08Bh, 040h, 00Ch, 050h
    call ?bfmeCheckGC@@YAPAVBfmeItemGC@@PAV1@@Z
    db 083h, 0C4h, 004h, 05Fh, 05Eh, 05Bh, 0C3h, 085h, 0F6h, 07Ch, 004h, 08Bh, 0C6h, 0EBh, 008h, 08Bh
    db 087h, 0B0h, 012h, 000h, 000h, 003h, 0C6h, 0F7h, 0D8h, 08Dh, 034h, 043h, 08Bh, 047h, 010h, 03Bh
    db 0F0h, 07Dh, 00Ah, 08Bh, 04Fh, 00Ch, 08Bh, 004h, 0B1h, 05Fh, 05Eh, 05Bh, 0C3h, 02Bh, 0F0h, 081h
    db 0FEh, 000h, 002h, 000h, 000h, 07Dh, 008h, 08Bh, 044h, 0B7h, 018h, 05Fh, 05Eh, 05Bh, 0C3h, 08Bh
    db 087h, 018h, 008h, 000h, 000h, 081h, 0EEh, 000h, 002h, 000h, 000h, 03Bh, 0F0h, 07Dh, 010h, 08Bh
    db 097h, 01Ch, 008h, 000h, 000h, 06Bh, 0F6h, 01Ch, 08Bh, 004h, 016h, 05Fh, 05Eh, 05Bh, 0C3h, 02Bh
    db 0F0h, 083h, 0FEh, 040h, 07Dh, 014h, 08Bh, 084h, 0B7h, 024h, 008h, 000h, 000h, 050h
    call ?bfmeCheckGC@@YAPAVBfmeItemGC@@PAV1@@Z
    db 083h, 0C4h, 004h, 05Fh, 05Eh, 05Bh, 0C3h, 083h, 0EEh, 040h, 083h, 0FEh, 040h, 07Dh, 014h, 08Bh
    db 08Ch, 0B7h, 028h, 009h, 000h, 000h, 051h
    call ?bfmeCheckGC@@YAPAVBfmeItemGC@@PAV1@@Z
    db 083h, 0C4h, 004h, 05Fh, 05Eh, 05Bh, 0C3h, 083h, 0EEh, 040h, 081h, 0FEh, 000h, 002h, 000h, 000h
    db 07Dh, 00Bh, 08Bh, 084h, 0B7h, 02Ch, 00Ah, 000h, 000h, 05Fh, 05Eh, 05Bh, 0C3h, 08Bh, 08Fh, 02Ch
    db 012h, 000h, 000h, 081h, 0EEh, 000h, 002h, 000h, 000h
    call ?count@Rva008BD1B0Node@@QBEHXZ
    db 03Bh, 0F0h, 08Bh, 08Fh, 02Ch, 012h, 000h, 000h, 07Dh, 00Ah, 056h
    call ?bfmeAdvance@Gen_008BD1D0@@QBEPAVBfmeNodeDB@@H@Z
    db 05Fh, 05Eh, 05Bh, 0C3h, 055h
    call ?count@Rva008BD1B0Node@@QBEHXZ
    db 08Bh, 09Fh, 0A4h, 012h, 000h, 000h, 08Bh, 0AFh, 034h, 012h, 000h, 000h, 02Bh, 0F0h, 033h, 0C0h
    db 085h, 0DBh, 07Eh, 026h, 08Bh, 0BFh, 030h, 012h, 000h, 000h, 08Bh, 0D7h, 083h, 03Ah, 000h, 074h
    db 011h, 085h, 0F6h, 074h, 01Ch, 08Bh, 04Ah, 014h, 04Eh, 03Bh, 0F1h, 07Ch, 020h, 02Bh, 0F1h, 04Dh
    db 074h, 008h, 040h, 083h, 0C2h, 020h, 03Bh, 0C3h, 07Ch, 0E2h, 05Dh, 05Fh, 05Eh, 033h, 0C0h, 05Bh
    db 0C3h, 05Dh, 0C1h, 0E0h, 005h, 08Bh, 044h, 038h, 004h, 05Fh, 05Eh, 05Bh, 0C3h, 0C1h, 0E0h, 005h
    db 08Bh, 054h, 038h, 014h, 08Dh, 044h, 038h, 014h, 08Bh, 040h, 008h, 02Bh, 0D6h, 08Bh, 044h, 090h
    db 0FCh, 050h
    call ?bfmeCheckGC@@YAPAVBfmeItemGC@@PAV1@@Z
    db 083h, 0C4h, 004h, 05Dh, 05Fh, 05Eh, 05Bh, 0C3h
?d_008a1e80@@YAXXZ ENDP
_TEXT$d00ca1e80 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca2580  retail @ 0x008A2580 size 56
public ?d_008a2580@@YAXXZ
?d_008a2580@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 46h, 1Ch, 85h, 0C0h, 74h, 05h, 03h, 0C6h, 89h, 46h
    db 1Ch, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h, 08h, 50h, 56h, 52h, 0C7h, 41h, 30h, 00h
    db 00h, 00h, 00h, 0E8h, 88h, 0FBh, 0FFh, 0FFh, 8Bh, 46h, 1Ch, 85h, 0C0h, 74h, 05h, 2Bh
    db 0C6h, 89h, 46h, 1Ch, 5Eh, 0C2h, 0Ch, 00h
?d_008a2580@@YAXXZ ENDP

; ghidra: FUN_00ca25c0  retail @ 0x008A25C0 size 1454
public ?d_008a25c0@@YAXXZ
?d_008a25c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 7Ch, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Dh, 46h, 30h
    db 89h, 44h, 24h, 0Ch, 0C7h, 00h, 00h, 00h, 00h, 00h, 8Bh, 46h, 0Ch, 33h, 0EDh, 85h
    db 0C0h, 57h, 0Fh, 8Eh, 0Eh, 01h, 00h, 00h, 8Bh, 5Eh, 10h, 8Bh, 14h, 0ABh, 85h, 0D2h
    db 0Fh, 84h, 0F4h, 00h, 00h, 00h, 8Bh, 46h, 20h, 33h, 0C9h, 85h, 0C0h, 7Eh, 20h, 8Bh
    db 46h, 24h, 83h, 0C0h, 08h, 39h, 28h, 74h, 0Dh, 8Bh, 7Eh, 20h, 41h, 83h, 0C0h, 10h
    db 3Bh, 0CFh, 7Ch, 0F1h, 0EBh, 09h, 83h, 0F9h, 0FFh, 0Fh, 85h, 0CBh, 00h, 00h, 00h, 8Bh
    db 02h, 83h, 0F8h, 04h, 74h, 5Eh, 83h, 0F8h, 08h, 0Fh, 85h, 0BBh, 00h, 00h, 00h, 8Bh
    db 4Eh, 0Ch, 33h, 0C0h, 85h, 0C9h, 7Eh, 17h, 8Bh, 7Ah, 08h, 8Bh, 0CBh, 8Dh, 49h, 00h
    db 39h, 39h, 74h, 0Eh, 8Bh, 5Eh, 0Ch, 40h, 83h, 0C1h, 04h, 3Bh, 0C3h, 7Ch, 0F1h, 83h
    db 0C8h, 0FFh, 89h, 42h, 08h, 8Bh, 4Eh, 0Ch, 33h, 0C0h, 85h, 0C9h, 7Eh, 18h, 8Bh, 4Eh
    db 10h, 8Bh, 14h, 0A9h, 8Bh, 52h, 0Ch, 39h, 11h, 74h, 0Eh, 8Bh, 7Eh, 0Ch, 40h, 83h
    db 0C1h, 04h, 3Bh, 0C7h, 7Ch, 0F1h, 83h, 0C8h, 0FFh, 8Bh, 4Eh, 10h, 8Bh, 14h, 0A9h, 89h
    db 42h, 0Ch, 0EBh, 66h, 8Bh, 7Ah, 3Ch, 85h, 0FFh, 74h, 46h, 8Bh, 47h, 04h, 85h, 0C0h
    db 74h, 0Bh, 50h, 8Bh, 0CEh, 0E8h, 0E6h, 0DFh, 0FFh, 0FFh, 89h, 47h, 04h, 8Bh, 47h, 0Ch
    db 85h, 0C0h, 74h, 0Bh, 50h, 8Bh, 0CEh, 0E8h, 0D4h, 0DFh, 0FFh, 0FFh, 89h, 47h, 0Ch, 8Bh
    db 07h, 85h, 0C0h, 74h, 0Ah, 50h, 8Bh, 0CEh, 0E8h, 0C3h, 0DFh, 0FFh, 0FFh, 89h, 07h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 0Bh, 50h, 8Bh, 0CEh, 0E8h, 0B2h, 0DFh, 0FFh, 0FFh, 89h, 47h
    db 08h, 8Bh, 46h, 10h, 8Bh, 0Ch, 0A8h, 8Bh, 51h, 3Ch, 85h, 0D2h, 8Dh, 04h, 0A8h, 74h
    db 09h, 8Bh, 54h, 24h, 28h, 8Bh, 0C1h, 29h, 50h, 3Ch, 8Bh, 46h, 0Ch, 45h, 3Bh, 0E8h
    db 0Fh, 8Ch, 0F2h, 0FEh, 0FFh, 0FFh, 8Bh, 46h, 0Ch, 33h, 0EDh, 85h, 0C0h, 89h, 6Ch, 24h
    db 14h, 0Fh, 8Eh, 0FDh, 02h, 00h, 00h, 33h, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 10h, 8Dh, 1Ch, 07h, 8Bh, 03h, 85h, 0C0h, 0Fh, 84h, 0CDh, 02h, 00h, 00h
    db 8Bh, 4Eh, 20h, 33h, 0D2h, 85h, 0C9h, 7Eh, 1Fh, 8Bh, 4Eh, 24h, 83h, 0C1h, 08h, 90h
    db 39h, 29h, 74h, 0Bh, 42h, 83h, 0C1h, 10h, 3Bh, 56h, 20h, 7Ch, 0F3h, 0EBh, 09h, 83h
    db 0FAh, 0FFh, 0Fh, 85h, 0A5h, 02h, 00h, 00h, 8Bh, 08h, 49h, 83h, 0F9h, 09h, 0Fh, 87h
    db 99h, 02h, 00h, 00h, 0FFh, 24h, 8Dh, 70h, 2Bh, 0CAh, 00h, 8Bh, 4Ch, 24h, 10h, 8Bh
    db 54h, 24h, 28h, 51h, 52h, 8Dh, 48h, 08h, 0E8h, 93h, 0Eh, 03h, 00h, 0E9h, 7Bh, 02h
    db 00h, 00h, 8Bh, 40h, 18h, 50h, 0FFh, 15h, 9Ch, 78h, 33h, 01h, 8Bh, 4Eh, 10h, 8Bh
    db 14h, 0Fh, 83h, 0C4h, 04h, 89h, 6Ah, 18h, 0E9h, 60h, 02h, 00h, 00h, 8Bh, 48h, 24h
    db 85h, 0C9h, 74h, 0Eh, 8Bh, 03h, 8Bh, 50h, 24h, 8Bh, 4Ch, 24h, 28h, 2Bh, 0D1h, 89h
    db 50h, 24h, 8Bh, 56h, 10h, 8Bh, 0Ch, 17h, 8Dh, 04h, 17h, 8Bh, 51h, 28h, 85h, 0D2h
    db 74h, 09h, 8Bh, 54h, 24h, 28h, 8Bh, 0C1h, 29h, 50h, 28h, 8Bh, 46h, 10h, 8Bh, 0Ch
    db 07h, 8Bh, 41h, 2Ch, 33h, 0EDh, 85h, 0C0h, 7Eh, 4Ah, 33h, 0D2h, 8Dh, 64h, 24h, 00h
    db 8Bh, 46h, 0Ch, 33h, 0C9h, 85h, 0C0h, 7Eh, 1Ah, 8Bh, 46h, 10h, 8Bh, 1Ch, 38h, 8Bh
    db 5Bh, 30h, 8Bh, 5Ch, 13h, 04h, 39h, 18h, 74h, 0Ch, 41h, 83h, 0C0h, 04h, 3Bh, 4Eh
    db 0Ch, 7Ch, 0F3h, 83h, 0C9h, 0FFh, 8Bh, 46h, 10h, 8Bh, 04h, 07h, 8Bh, 40h, 30h, 89h
    db 4Ch, 10h, 04h, 8Bh, 4Eh, 10h, 8Bh, 04h, 0Fh, 8Bh, 48h, 2Ch, 45h, 83h, 0C2h, 44h
    db 3Bh, 0E9h, 7Ch, 0BCh, 8Bh, 4Eh, 10h, 8Bh, 14h, 0Fh, 8Dh, 04h, 0Fh, 8Bh, 4Ah, 30h
    db 85h, 0C9h, 74h, 09h, 8Bh, 4Ch, 24h, 28h, 8Bh, 0C2h, 29h, 48h, 30h, 8Bh, 56h, 10h
    db 8Bh, 04h, 17h, 8Bh, 48h, 34h, 33h, 0DBh, 85h, 0C9h, 7Eh, 4Ch, 8Bh, 6Ch, 24h, 28h
    db 8Bh, 56h, 10h, 8Bh, 4Ch, 24h, 10h, 8Bh, 04h, 17h, 51h, 8Bh, 48h, 38h, 8Bh, 54h
    db 0D9h, 04h, 55h, 52h, 0E8h, 0D7h, 9Ch, 02h, 00h, 8Bh, 46h, 10h, 8Bh, 0Ch, 38h, 8Bh
    db 51h, 38h, 8Bh, 4Ch, 0DAh, 04h, 03h, 0C7h, 83h, 0C4h, 0Ch, 85h, 0C9h, 74h, 0Bh, 8Bh
    db 00h, 8Bh, 48h, 38h, 8Dh, 44h, 0D9h, 04h, 29h, 28h, 8Bh, 56h, 10h, 8Bh, 04h, 17h
    db 8Bh, 48h, 34h, 43h, 3Bh, 0D9h, 7Ch, 0B8h, 8Bh, 4Eh, 10h, 8Bh, 14h, 0Fh, 8Dh, 04h
    db 0Fh, 8Bh, 4Ah, 38h, 85h, 0C9h, 0Fh, 84h, 51h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 28h
    db 8Bh, 0C2h, 29h, 48h, 38h, 0E9h, 43h, 01h, 00h, 00h, 8Bh, 48h, 08h, 85h, 0C9h, 74h
    db 0Eh, 8Bh, 03h, 8Bh, 48h, 08h, 8Bh, 54h, 24h, 28h, 2Bh, 0CAh, 89h, 48h, 08h, 8Bh
    db 46h, 10h, 8Bh, 0Ch, 07h, 8Bh, 41h, 0Ch, 33h, 0D2h, 85h, 0C0h, 7Eh, 43h, 8Bh, 0FFh
    db 8Bh, 46h, 0Ch, 33h, 0C9h, 85h, 0C0h, 7Eh, 1Bh, 8Bh, 46h, 10h, 8Bh, 1Ch, 38h, 8Bh
    db 5Bh, 10h, 8Bh, 1Ch, 93h, 39h, 18h, 74h, 0Eh, 8Bh, 6Eh, 0Ch, 41h, 83h, 0C0h, 04h
    db 3Bh, 0CDh, 7Ch, 0F1h, 83h, 0C9h, 0FFh, 8Bh, 46h, 10h, 8Bh, 04h, 07h, 8Bh, 40h, 10h
    db 89h, 0Ch, 90h, 8Bh, 4Eh, 10h, 8Bh, 04h, 0Fh, 8Bh, 48h, 0Ch, 42h, 3Bh, 0D1h, 7Ch
    db 0BFh, 8Bh, 4Eh, 10h, 8Bh, 14h, 0Fh, 8Dh, 04h, 0Fh, 8Bh, 4Ah, 10h, 85h, 0C9h, 0Fh
    db 84h, 0C8h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 28h, 8Bh, 0C2h, 29h, 48h, 10h, 0E9h, 0BAh
    db 00h, 00h, 00h, 8Bh, 50h, 08h, 52h, 0FFh, 15h, 80h, 78h, 33h, 01h, 8Bh, 46h, 10h
    db 8Bh, 0Ch, 07h, 83h, 0C4h, 04h, 89h, 69h, 08h, 0E9h, 9Fh, 00h, 00h, 00h, 8Bh, 48h
    db 34h, 85h, 0C9h, 74h, 0Eh, 8Bh, 03h, 8Bh, 48h, 34h, 8Bh, 54h, 24h, 28h, 2Bh, 0CAh
    db 89h, 48h, 34h, 8Bh, 46h, 10h, 8Bh, 0Ch, 38h, 8Bh, 51h, 38h, 03h, 0C7h, 85h, 0D2h
    db 74h, 7Bh, 8Bh, 54h, 24h, 28h, 8Bh, 0C1h, 29h, 50h, 38h, 0EBh, 70h, 8Bh, 40h, 08h
    db 50h, 0FFh, 15h, 90h, 78h, 33h, 01h, 8Bh, 4Eh, 10h, 8Bh, 14h, 0Fh, 83h, 0C4h, 04h
    db 89h, 6Ah, 08h, 0EBh, 58h, 8Bh, 48h, 30h, 8Bh, 5Ch, 24h, 28h, 33h, 0D2h, 85h, 0C9h
    db 7Eh, 36h, 33h, 0C0h, 8Bh, 4Eh, 10h, 8Bh, 2Ch, 39h, 8Bh, 6Dh, 34h, 03h, 0CFh, 83h
    db 7Ch, 28h, 34h, 00h, 74h, 11h, 8Bh, 09h, 8Bh, 49h, 34h, 8Bh, 6Ch, 01h, 34h, 8Dh
    db 4Ch, 01h, 34h, 2Bh, 0EBh, 89h, 29h, 8Bh, 4Eh, 10h, 8Bh, 0Ch, 0Fh, 8Bh, 69h, 30h
    db 42h, 83h, 0C0h, 38h, 3Bh, 0D5h, 7Ch, 0CCh, 8Bh, 56h, 10h, 8Bh, 0Ch, 17h, 8Dh, 04h
    db 17h, 8Bh, 51h, 34h, 85h, 0D2h, 74h, 05h, 8Bh, 0C1h, 29h, 58h, 34h, 8Bh, 6Ch, 24h
    db 14h, 8Bh, 46h, 0Ch, 45h, 83h, 0C7h, 04h, 3Bh, 0E8h, 89h, 6Ch, 24h, 14h, 0Fh, 8Ch
    db 0Ch, 0FDh, 0FFh, 0FFh, 8Bh, 46h, 20h, 33h, 0C9h, 33h, 0EDh, 3Bh, 0C1h, 7Eh, 5Bh, 89h
    db 4Ch, 24h, 14h, 33h, 0FFh, 8Bh, 56h, 24h, 8Dh, 5Ch, 17h, 0Ch, 8Dh, 44h, 24h, 14h
    db 3Bh, 0C3h, 89h, 4Ch, 24h, 20h, 74h, 22h, 8Bh, 03h, 3Bh, 0C1h, 74h, 18h, 50h, 0E8h
    db 4Ch, 23h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 0Bh, 8Bh, 0Bh, 51h, 0E8h, 0CDh
    db 28h, 0FFh, 0FFh, 83h, 0C4h, 04h, 33h, 0C9h, 89h, 0Bh, 8Bh, 56h, 24h, 8Bh, 44h, 17h
    db 08h, 8Bh, 56h, 10h, 89h, 0Ch, 82h, 8Bh, 46h, 20h, 45h, 83h, 0C7h, 10h, 3Bh, 0E8h
    db 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 7Ch, 0ABh, 39h, 4Eh, 0Ch, 8Bh, 7Ch, 24h
    db 28h, 7Eh, 2Bh, 0BAh, 43h, 65h, 87h, 09h, 8Bh, 46h, 10h, 8Bh, 04h, 88h, 85h, 0C0h
    db 74h, 14h, 89h, 50h, 04h, 8Bh, 46h, 10h, 8Bh, 1Ch, 88h, 85h, 0DBh, 8Dh, 04h, 88h
    db 74h, 04h, 2Bh, 0DFh, 89h, 18h, 8Bh, 46h, 0Ch, 41h, 3Bh, 0C8h, 7Ch, 0DAh, 8Bh, 46h
    db 10h, 85h, 0C0h, 74h, 05h, 2Bh, 0C7h, 89h, 46h, 10h, 8Bh, 46h, 20h, 33h, 0D2h, 85h
    db 0C0h, 7Eh, 30h, 33h, 0C9h, 8Bh, 46h, 24h, 8Bh, 1Ch, 08h, 03h, 0C1h, 85h, 0DBh, 74h
    db 04h, 2Bh, 0DFh, 89h, 18h, 8Bh, 46h, 24h, 8Bh, 5Ch, 01h, 04h, 85h, 0DBh, 8Dh, 44h
    db 01h, 04h, 74h, 04h, 2Bh, 0DFh, 89h, 18h, 8Bh, 46h, 20h, 42h, 83h, 0C1h, 10h, 3Bh
    db 0D0h, 7Ch, 0D2h, 8Bh, 46h, 28h, 33h, 0C9h, 85h, 0C0h, 7Eh, 1Ch, 8Dh, 64h, 24h, 00h
    db 8Bh, 56h, 2Ch, 8Dh, 04h, 0CAh, 8Bh, 10h, 85h, 0D2h, 74h, 04h, 2Bh, 0D7h, 89h, 10h
    db 8Bh, 46h, 28h, 41h, 3Bh, 0C8h, 7Ch, 0E8h, 8Bh, 46h, 24h, 85h, 0C0h, 74h, 05h, 2Bh
    db 0C7h, 89h, 46h, 24h, 8Bh, 46h, 2Ch, 85h, 0C0h, 74h, 24h, 2Bh, 0C7h, 5Fh, 89h, 46h
    db 2Ch, 8Bh, 44h, 24h, 0Ch, 5Eh, 5Dh, 0C7h, 00h, 00h, 00h, 00h, 00h, 5Bh, 8Bh, 4Ch
    db 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 10h, 5Fh, 5Eh, 0C7h, 01h, 00h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 10h, 5Dh
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_008a25c0@@YAXXZ ENDP

; ghidra: FUN_00ca2ba0  retail @ 0x008A2BA0 size 186
public ?d_008a2ba0@@YAXXZ
?d_008a2ba0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 7Ch, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 44h, 24h, 18h, 00h, 00h, 00h, 00h, 0E8h, 24h, 0A8h, 00h, 00h, 8Dh, 7Eh, 34h, 0C7h
    db 06h, 0A4h, 64h, 13h, 01h, 0C7h, 07h, 00h, 00h, 00h, 00h, 8Bh, 5Ch, 24h, 20h, 8Dh
    db 44h, 24h, 20h, 3Bh, 0C7h, 0C6h, 44h, 24h, 18h, 02h, 0C7h, 46h, 30h, 00h, 00h, 00h
    db 00h, 74h, 2Dh, 8Bh, 07h, 85h, 0C0h, 74h, 18h, 50h, 0E8h, 91h, 21h, 0FFh, 0FFh, 83h
    db 0C4h, 04h, 85h, 0C0h, 75h, 0Bh, 8Bh, 0Fh, 51h, 0E8h, 12h, 27h, 0FFh, 0FFh, 83h, 0C4h
    db 04h, 85h, 0DBh, 89h, 1Fh, 74h, 09h, 53h, 0E8h, 63h, 21h, 0FFh, 0FFh, 83h, 0C4h, 04h
    db 8Bh, 43h, 10h, 53h, 89h, 46h, 0Ch, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 5Ch, 21h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 09h, 53h, 0E8h, 0DFh, 26h, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_008a2ba0@@YAXXZ ENDP

; ghidra: FUN_00ca2c60  retail @ 0x008A2C60 size 21
public ?d_008a2c60@@YAXXZ
?d_008a2c60@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 10h, 85h, 0C9h, 74h, 05h, 0E8h, 11h, 9Ch, 0FFh, 0FFh, 0C6h
    db 46h, 14h, 01h, 5Eh, 0C3h
?d_008a2c60@@YAXXZ ENDP

; ghidra: FUN_00ca2c80  retail @ 0x008A2C80 size 106
public ?d_008a2c80@@YAXXZ
?d_008a2c80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 7Ch, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0A4h
    db 64h, 13h, 01h, 8Bh, 46h, 34h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 19h, 50h, 0E8h, 0D8h, 20h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 0Ch, 8Bh
    db 46h, 34h, 50h, 0E8h, 58h, 26h, 0FFh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 46h, 99h, 00h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008a2c80@@YAXXZ ENDP

; ghidra: FUN_00ca2cf0  retail @ 0x008A2CF0 size 473
public ?d_008a2cf0@@YAXXZ
?d_008a2cf0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Eh, 7Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 8Bh, 0F1h, 57h, 33h, 0DBh, 0B9h, 00h
    db 02h, 00h, 00h, 33h, 0C0h, 8Dh, 7Eh, 18h, 89h, 5Eh, 14h, 89h, 74h, 24h, 10h, 0F3h
    db 0ABh, 0B9h, 40h, 00h, 00h, 00h, 8Dh, 0BEh, 24h, 08h, 00h, 00h, 89h, 9Eh, 20h, 08h
    db 00h, 00h, 89h, 5Ch, 24h, 1Ch, 0F3h, 0ABh, 0B9h, 40h, 00h, 00h, 00h, 8Dh, 0BEh, 28h
    db 09h, 00h, 00h, 89h, 9Eh, 24h, 09h, 00h, 00h, 0F3h, 0ABh, 0B9h, 00h, 02h, 00h, 00h
    db 8Dh, 0BEh, 2Ch, 0Ah, 00h, 00h, 89h, 9Eh, 28h, 0Ah, 00h, 00h, 0F3h, 0ABh, 8Dh, 8Eh
    db 2Ch, 12h, 00h, 00h, 0C6h, 44h, 24h, 1Ch, 03h, 0E8h, 0F2h, 0B8h, 01h, 00h, 8Bh, 44h
    db 24h, 24h, 8Bh, 48h, 18h, 89h, 8Eh, 0A0h, 12h, 00h, 00h, 8Bh, 50h, 10h, 89h, 96h
    db 0A4h, 12h, 00h, 00h, 8Bh, 48h, 1Ch, 89h, 8Eh, 0A8h, 12h, 00h, 00h, 8Bh, 50h, 14h
    db 8Bh, 8Eh, 0A0h, 12h, 00h, 00h, 89h, 96h, 0ACh, 12h, 00h, 00h, 8Bh, 40h, 0Ch, 0C1h
    db 0E1h, 02h, 51h, 0C6h, 44h, 24h, 20h, 04h, 89h, 86h, 0B0h, 12h, 00h, 00h, 0FFh, 15h
    db 28h, 78h, 33h, 01h, 89h, 46h, 0Ch, 8Bh, 86h, 0B0h, 12h, 00h, 00h, 8Dh, 04h, 80h
    db 0C1h, 0E0h, 02h, 50h, 0FFh, 15h, 28h, 78h, 33h, 01h, 89h, 06h, 8Bh, 86h, 0ACh, 12h
    db 00h, 00h, 6Bh, 0C0h, 1Ch, 50h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Bh, 0BEh, 0A4h, 12h
    db 00h, 00h, 8Bh, 0D7h, 0C1h, 0E2h, 05h, 83h, 0C2h, 04h, 52h, 89h, 86h, 1Ch, 08h, 00h
    db 00h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 10h, 89h, 44h, 24h, 24h, 3Bh, 0C3h
    db 0C6h, 44h, 24h, 1Ch, 05h, 74h, 1Ah, 68h, 0B0h, 20h, 0CAh, 00h, 68h, 0F0h, 0Fh, 0CAh
    db 00h, 57h, 8Dh, 68h, 04h, 6Ah, 20h, 55h, 89h, 38h, 0E8h, 0C5h, 40h, 15h, 00h, 0EBh
    db 02h, 33h, 0EDh, 8Bh, 86h, 0A8h, 12h, 00h, 00h, 0C1h, 0E0h, 02h, 50h, 0C6h, 44h, 24h
    db 20h, 04h, 89h, 0AEh, 30h, 12h, 00h, 00h, 0FFh, 15h, 28h, 78h, 33h, 01h, 89h, 86h
    db 3Ch, 12h, 00h, 00h, 8Bh, 06h, 83h, 0C4h, 04h, 8Bh, 0CEh, 89h, 46h, 08h, 89h, 46h
    db 04h, 89h, 5Eh, 10h, 0E8h, 77h, 0D9h, 0FFh, 0FFh, 89h, 9Eh, 38h, 12h, 00h, 00h, 89h
    db 9Eh, 6Ch, 12h, 00h, 00h, 89h, 9Eh, 70h, 12h, 00h, 00h, 89h, 9Eh, 74h, 12h, 00h
    db 00h, 89h, 9Eh, 78h, 12h, 00h, 00h, 89h, 9Eh, 18h, 08h, 00h, 00h, 89h, 9Eh, 34h
    db 12h, 00h, 00h, 89h, 9Eh, 9Ch, 12h, 00h, 00h, 8Bh, 0Dh, 0BCh, 79h, 33h, 01h, 89h
    db 8Eh, 40h, 12h, 00h, 00h, 8Bh, 15h, 0BCh, 79h, 33h, 01h, 8Bh, 4Ch, 24h, 14h, 89h
    db 96h, 5Ch, 12h, 00h, 00h, 0A1h, 0BCh, 79h, 33h, 01h, 89h, 86h, 60h, 12h, 00h, 00h
    db 5Fh, 88h, 9Eh, 64h, 12h, 00h, 00h, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_008a2cf0@@YAXXZ ENDP

; ghidra: FUN_00ca2f30  retail @ 0x008A2F30 size 246
public ?d_008a2f30@@YAXXZ
?d_008a2f30@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B3h, 7Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 86h, 0A8h
    db 12h, 00h, 00h, 8Bh, 8Eh, 3Ch, 12h, 00h, 00h, 0C1h, 0E0h, 02h, 50h, 51h, 0C7h, 44h
    db 24h, 18h, 04h, 00h, 00h, 00h, 0FFh, 15h, 30h, 78h, 33h, 01h, 8Bh, 86h, 30h, 12h
    db 00h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 20h, 8Bh, 50h, 0FCh, 57h, 8Dh, 78h, 0FCh
    db 68h, 0B0h, 20h, 0CAh, 00h, 52h, 6Ah, 20h, 50h, 0E8h, 0E8h, 3Dh, 15h, 00h, 57h, 0FFh
    db 15h, 2Ch, 78h, 33h, 01h, 83h, 0C4h, 04h, 5Fh, 8Bh, 86h, 1Ch, 08h, 00h, 00h, 50h
    db 0FFh, 15h, 2Ch, 78h, 33h, 01h, 8Bh, 06h, 50h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 8Bh
    db 86h, 0A0h, 12h, 00h, 00h, 8Bh, 4Eh, 0Ch, 0C1h, 0E0h, 02h, 50h, 51h, 0FFh, 15h, 30h
    db 78h, 33h, 01h, 83h, 0C4h, 10h, 8Dh, 8Eh, 2Ch, 12h, 00h, 00h, 0C6h, 44h, 24h, 10h
    db 03h, 0E8h, 0FAh, 0B6h, 01h, 00h, 8Dh, 8Eh, 28h, 0Ah, 00h, 00h, 0C6h, 44h, 24h, 10h
    db 02h, 0E8h, 0DAh, 0DDh, 0FFh, 0FFh, 8Dh, 8Eh, 24h, 09h, 00h, 00h, 0C6h, 44h, 24h, 10h
    db 01h, 0E8h, 7Ah, 0DEh, 0FFh, 0FFh, 8Dh, 8Eh, 20h, 08h, 00h, 00h, 0C6h, 44h, 24h, 10h
    db 00h, 0E8h, 6Ah, 0DEh, 0FFh, 0FFh, 8Dh, 4Eh, 14h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 0AAh, 0DDh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008a2f30@@YAXXZ ENDP

; ghidra: FUN_00ca3030  retail @ 0x008A3030 size 33
public ?d_008a3030@@YAXXZ
?d_008a3030@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 48h, 0FCh, 0FFh, 0FFh, 0F6h, 44h, 24h, 08h, 01h, 74h, 0Ch, 6Ah
    db 38h, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_008a3030@@YAXXZ ENDP

; ghidra: FUN_00ca3070  retail @ 0x008A3070 size 38
public ?d_008a3070@@YAXXZ
?d_008a3070@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 89h, 06h, 0C1h, 0E0h, 02h, 50h, 0C7h, 46h, 04h
    db 00h, 00h, 00h, 00h, 0FFh, 15h, 28h, 78h, 33h, 01h, 89h, 46h, 08h, 83h, 0C4h, 04h
    db 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008a3070@@YAXXZ ENDP

; ghidra: FUN_00ca30a0  retail @ 0x008A30A0 size 25
public ?d_008a30a0@@YAXXZ
?d_008a30a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 50h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 83h, 0C4h, 04h
    db 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_008a30a0@@YAXXZ ENDP

; ghidra: FUN_00ca30c0  retail @ 0x008A30C0 size 62
public ?d_008a30c0@@YAXXZ
?d_008a30c0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 30h, 8Bh, 0F8h, 8Dh, 49h, 00h
    db 8Bh, 46h, 04h, 8Bh, 4Eh, 08h, 48h, 89h, 46h, 04h, 8Bh, 0Ch, 81h, 8Bh, 41h, 04h
    db 0A9h, 00h, 00h, 0FFh, 0Fh, 76h, 0Ah, 25h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 41h, 04h, 0EBh
    db 05h, 8Bh, 11h, 0FFh, 52h, 08h, 4Fh, 75h, 0D7h, 0EBh, 0C9h, 5Fh, 5Eh, 0C3h
?d_008a30c0@@YAXXZ ENDP

; ghidra: FUN_00ca3130  retail @ 0x008A3130 size 33
public ?d_008a3130@@YAXXZ
?d_008a3130@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0C0h, 08h, 56h, 50h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Bh
    db 0F0h, 83h, 0C6h, 08h, 56h, 0E8h, 0B6h, 41h, 0FFh, 0FFh, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh
    db 0C3h
?d_008a3130@@YAXXZ ENDP

; ghidra: FUN_00ca3160  retail @ 0x008A3160 size 34
public ?d_008a3160@@YAXXZ
?d_008a3160@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 56h, 0E8h, 0C5h, 41h, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 83h
    db 0C0h, 08h, 50h, 83h, 0C6h, 0F8h, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 0Ch
    db 5Eh, 0C3h
?d_008a3160@@YAXXZ ENDP

; ghidra: FUN_00ca3790  retail @ 0x008A3790 size 99
public ?d_008a3790@@YAXXZ
?d_008a3790@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 10h, 83h, 0FFh, 12h, 77h, 53h, 83h, 0FFh, 02h, 72h, 4Eh
    db 8Bh, 74h, 24h, 0Ch, 57h, 56h, 0E8h, 0E5h, 0F9h, 0FFh, 0FFh, 83h, 0C4h, 08h, 83h, 0F8h
    db 31h, 7Fh, 3Bh, 85h, 0C0h, 7Ch, 37h, 0Fh, 0BEh, 80h, 94h, 53h, 2Dh, 01h, 85h, 0C0h
    db 7Ch, 2Ch, 0Fh, 0B6h, 88h, 78h, 53h, 2Dh, 01h, 3Bh, 0F9h, 75h, 21h, 8Bh, 14h, 0C5h
    db 0A8h, 52h, 2Dh, 01h, 8Ah, 0Eh, 8Dh, 04h, 0C5h, 0A8h, 52h, 2Dh, 01h, 3Ah, 0Ah, 75h
    db 0Dh, 8Dh, 4Fh, 0FFh, 8Dh, 7Ah, 01h, 46h, 33h, 0D2h, 0F3h, 0A6h, 74h, 02h, 33h, 0C0h
    db 5Fh, 5Eh, 0C3h
?d_008a3790@@YAXXZ ENDP

; ghidra: FUN_00ca3800  retail @ 0x008A3800 size 1466
public ?d_008a3800@@YAXXZ
?d_008a3800@@YAXXZ PROC
    db 81h, 0ECh, 00h, 01h, 00h, 00h, 0B0h, 32h, 0B2h, 05h, 88h, 04h, 24h, 88h, 44h, 24h
    db 01h, 88h, 44h, 24h, 02h, 88h, 44h, 24h, 03h, 88h, 44h, 24h, 04h, 88h, 44h, 24h
    db 05h, 88h, 44h, 24h, 06h, 88h, 44h, 24h, 07h, 88h, 44h, 24h, 08h, 88h, 44h, 24h
    db 09h, 88h, 44h, 24h, 0Ah, 88h, 44h, 24h, 0Bh, 88h, 44h, 24h, 0Ch, 88h, 44h, 24h
    db 0Dh, 88h, 44h, 24h, 0Eh, 88h, 44h, 24h, 0Fh, 88h, 44h, 24h, 10h, 88h, 44h, 24h
    db 11h, 88h, 44h, 24h, 12h, 88h, 44h, 24h, 13h, 88h, 44h, 24h, 14h, 88h, 44h, 24h
    db 15h, 88h, 44h, 24h, 16h, 88h, 44h, 24h, 17h, 88h, 44h, 24h, 18h, 88h, 44h, 24h
    db 19h, 88h, 44h, 24h, 1Ah, 88h, 44h, 24h, 1Bh, 88h, 44h, 24h, 1Ch, 88h, 44h, 24h
    db 1Dh, 88h, 44h, 24h, 1Eh, 88h, 44h, 24h, 1Fh, 88h, 44h, 24h, 20h, 88h, 44h, 24h
    db 21h, 88h, 44h, 24h, 22h, 88h, 44h, 24h, 23h, 88h, 44h, 24h, 24h, 88h, 44h, 24h
    db 25h, 88h, 44h, 24h, 26h, 88h, 44h, 24h, 27h, 88h, 44h, 24h, 28h, 88h, 44h, 24h
    db 29h, 88h, 44h, 24h, 2Ah, 88h, 44h, 24h, 2Bh, 88h, 44h, 24h, 2Ch, 88h, 44h, 24h
    db 2Dh, 88h, 44h, 24h, 2Eh, 88h, 44h, 24h, 2Fh, 88h, 44h, 24h, 30h, 88h, 44h, 24h
    db 31h, 88h, 54h, 24h, 32h, 88h, 44h, 24h, 33h, 88h, 44h, 24h, 34h, 88h, 44h, 24h
    db 35h, 88h, 44h, 24h, 36h, 88h, 44h, 24h, 37h, 88h, 44h, 24h, 38h, 88h, 44h, 24h
    db 39h, 88h, 44h, 24h, 3Ah, 88h, 44h, 24h, 3Bh, 88h, 44h, 24h, 3Ch, 88h, 44h, 24h
    db 3Dh, 88h, 44h, 24h, 3Eh, 88h, 44h, 24h, 3Fh, 88h, 44h, 24h, 40h, 88h, 44h, 24h
    db 41h, 88h, 44h, 24h, 42h, 88h, 44h, 24h, 43h, 88h, 44h, 24h, 44h, 88h, 44h, 24h
    db 45h, 88h, 44h, 24h, 46h, 88h, 44h, 24h, 47h, 88h, 44h, 24h, 48h, 88h, 44h, 24h
    db 49h, 88h, 44h, 24h, 4Ah, 88h, 44h, 24h, 4Bh, 88h, 44h, 24h, 4Ch, 88h, 44h, 24h
    db 4Dh, 88h, 44h, 24h, 4Eh, 32h, 0C9h, 88h, 44h, 24h, 4Fh, 88h, 44h, 24h, 50h, 88h
    db 44h, 24h, 51h, 88h, 44h, 24h, 52h, 88h, 44h, 24h, 53h, 88h, 44h, 24h, 54h, 88h
    db 44h, 24h, 55h, 88h, 44h, 24h, 56h, 88h, 44h, 24h, 57h, 88h, 44h, 24h, 58h, 88h
    db 44h, 24h, 59h, 88h, 44h, 24h, 5Ah, 88h, 44h, 24h, 5Bh, 88h, 44h, 24h, 5Ch, 88h
    db 44h, 24h, 5Dh, 88h, 44h, 24h, 5Eh, 88h, 44h, 24h, 5Fh, 88h, 44h, 24h, 60h, 0C6h
    db 44h, 24h, 61h, 14h, 88h, 44h, 24h, 62h, 88h, 54h, 24h, 63h, 88h, 54h, 24h, 64h
    db 0C6h, 44h, 24h, 65h, 0Ah, 88h, 4Ch, 24h, 66h, 0C6h, 44h, 24h, 67h, 1Eh, 88h, 44h
    db 24h, 68h, 88h, 44h, 24h, 69h, 88h, 44h, 24h, 6Ah, 88h, 44h, 24h, 6Bh, 88h, 4Ch
    db 24h, 6Ch, 0C6h, 44h, 24h, 6Dh, 0Ah, 0C6h, 44h, 24h, 6Eh, 19h, 88h, 44h, 24h, 6Fh
    db 88h, 4Ch, 24h, 70h, 88h, 44h, 24h, 71h, 88h, 4Ch, 24h, 72h, 88h, 4Ch, 24h, 73h
    db 0C6h, 44h, 24h, 74h, 0Fh, 88h, 44h, 24h, 75h, 88h, 44h, 24h, 76h, 88h, 4Ch, 24h
    db 77h, 88h, 54h, 24h, 78h, 88h, 44h, 24h, 79h, 88h, 44h, 24h, 7Ah, 88h, 44h, 24h
    db 7Bh, 88h, 44h, 24h, 7Ch, 88h, 44h, 24h, 7Dh, 88h, 44h, 24h, 7Eh, 88h, 44h, 24h
    db 7Fh, 88h, 84h, 24h, 80h, 00h, 00h, 00h, 88h, 84h, 24h, 81h, 00h, 00h, 00h, 88h
    db 84h, 24h, 82h, 00h, 00h, 00h, 88h, 84h, 24h, 83h, 00h, 00h, 00h, 88h, 84h, 24h
    db 84h, 00h, 00h, 00h, 88h, 84h, 24h, 85h, 00h, 00h, 00h, 88h, 84h, 24h, 86h, 00h
    db 00h, 00h, 88h, 84h, 24h, 87h, 00h, 00h, 00h, 88h, 84h, 24h, 88h, 00h, 00h, 00h
    db 88h, 84h, 24h, 89h, 00h, 00h, 00h, 88h, 84h, 24h, 8Ah, 00h, 00h, 00h, 88h, 84h
    db 24h, 8Bh, 00h, 00h, 00h, 88h, 84h, 24h, 8Ch, 00h, 00h, 00h, 88h, 84h, 24h, 8Dh
    db 00h, 00h, 00h, 88h, 84h, 24h, 8Eh, 00h, 00h, 00h, 88h, 84h, 24h, 8Fh, 00h, 00h
    db 00h, 88h, 84h, 24h, 90h, 00h, 00h, 00h, 88h, 84h, 24h, 91h, 00h, 00h, 00h, 88h
    db 84h, 24h, 92h, 00h, 00h, 00h, 88h, 84h, 24h, 93h, 00h, 00h, 00h, 88h, 84h, 24h
    db 94h, 00h, 00h, 00h, 88h, 84h, 24h, 95h, 00h, 00h, 00h, 88h, 84h, 24h, 96h, 00h
    db 00h, 00h, 88h, 84h, 24h, 97h, 00h, 00h, 00h, 88h, 84h, 24h, 98h, 00h, 00h, 00h
    db 88h, 84h, 24h, 99h, 00h, 00h, 00h, 88h, 84h, 24h, 9Ah, 00h, 00h, 00h, 88h, 84h
    db 24h, 9Bh, 00h, 00h, 00h, 88h, 84h, 24h, 9Ch, 00h, 00h, 00h, 88h, 84h, 24h, 9Dh
    db 00h, 00h, 00h, 88h, 84h, 24h, 9Eh, 00h, 00h, 00h, 88h, 84h, 24h, 9Fh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0A0h, 00h, 00h, 00h, 88h, 84h, 24h, 0A1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0A2h, 00h, 00h, 00h, 88h, 84h, 24h, 0A3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0A4h, 00h, 00h, 00h, 88h, 84h, 24h, 0A5h, 00h, 00h, 00h, 88h, 84h, 24h, 0A6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0A7h, 00h, 00h, 00h, 88h, 84h, 24h, 0A8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0A9h, 00h, 00h, 00h, 88h, 84h, 24h, 0AAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0ABh, 00h, 00h, 00h, 88h, 84h, 24h, 0ACh, 00h, 00h, 00h, 88h, 84h, 24h, 0ADh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0AEh, 00h, 00h, 00h, 88h, 84h, 24h, 0AFh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0B0h, 00h, 00h, 00h, 88h, 84h, 24h, 0B1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0B2h, 00h, 00h, 00h, 88h, 84h, 24h, 0B3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0B4h, 00h, 00h, 00h, 88h, 84h, 24h, 0B5h, 00h, 00h, 00h, 88h, 84h, 24h, 0B6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0B7h, 00h, 00h, 00h, 88h, 84h, 24h, 0B8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0B9h, 00h, 00h, 00h, 88h, 84h, 24h, 0BAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0BBh, 00h, 00h, 00h, 88h, 84h, 24h, 0BCh, 00h, 00h, 00h, 88h, 84h, 24h, 0BDh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0BEh, 00h, 00h, 00h, 88h, 84h, 24h, 0BFh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0C0h, 00h, 00h, 00h, 88h, 84h, 24h, 0C1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0C2h, 00h, 00h, 00h, 88h, 84h, 24h, 0C3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0C4h, 00h, 00h, 00h, 88h, 84h, 24h, 0C5h, 00h, 00h, 00h, 88h, 84h, 24h, 0C6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0C7h, 00h, 00h, 00h, 88h, 84h, 24h, 0C8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0C9h, 00h, 00h, 00h, 88h, 84h, 24h, 0CAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0CBh, 00h, 00h, 00h, 88h, 84h, 24h, 0CCh, 00h, 00h, 00h, 88h, 84h, 24h, 0CDh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0CEh, 00h, 00h, 00h, 88h, 84h, 24h, 0CFh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0D0h, 00h, 00h, 00h, 88h, 84h, 24h, 0D1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0D2h, 00h, 00h, 00h, 88h, 84h, 24h, 0D3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0D4h, 00h, 00h, 00h, 88h, 84h, 24h, 0D5h, 00h, 00h, 00h, 88h, 84h, 24h, 0D6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0D7h, 00h, 00h, 00h, 88h, 84h, 24h, 0D8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0D9h, 00h, 00h, 00h, 88h, 84h, 24h, 0DAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0DBh, 00h, 00h, 00h, 88h, 84h, 24h, 0DCh, 00h, 00h, 00h, 88h, 84h, 24h, 0DDh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0DEh, 00h, 00h, 00h, 88h, 84h, 24h, 0DFh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0E0h, 00h, 00h, 00h, 88h, 84h, 24h, 0E1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0E2h, 00h, 00h, 00h, 88h, 84h, 24h, 0E3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0E4h, 00h, 00h, 00h, 88h, 84h, 24h, 0E5h, 00h, 00h, 00h, 88h, 84h, 24h, 0E6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0E7h, 00h, 00h, 00h, 88h, 84h, 24h, 0E8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0E9h, 00h, 00h, 00h, 88h, 84h, 24h, 0EAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0EBh, 00h, 00h, 00h, 88h, 84h, 24h, 0ECh, 00h, 00h, 00h, 88h, 84h, 24h, 0EDh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0EEh, 00h, 00h, 00h, 88h, 84h, 24h, 0EFh, 00h, 00h
    db 00h, 8Bh, 8Ch, 24h, 08h, 01h, 00h, 00h, 88h, 84h, 24h, 0F0h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0F1h, 00h, 00h, 00h, 88h, 84h, 24h, 0F2h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0F3h, 00h, 00h, 00h, 88h, 84h, 24h, 0F4h, 00h, 00h, 00h, 88h, 84h, 24h, 0F5h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0F6h, 00h, 00h, 00h, 88h, 84h, 24h, 0F7h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0F8h, 00h, 00h, 00h, 88h, 84h, 24h, 0F9h, 00h, 00h, 00h, 88h, 84h
    db 24h, 0FAh, 00h, 00h, 00h, 88h, 84h, 24h, 0FBh, 00h, 00h, 00h, 88h, 84h, 24h, 0FCh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0FDh, 00h, 00h, 00h, 88h, 84h, 24h, 0FEh, 00h, 00h
    db 00h, 88h, 84h, 24h, 0FFh, 00h, 00h, 00h, 8Bh, 84h, 24h, 04h, 01h, 00h, 00h, 0Fh
    db 0B6h, 54h, 08h, 0FFh, 0Fh, 0B6h, 00h, 0Fh, 0B6h, 14h, 14h, 0Fh, 0B6h, 04h, 04h, 03h
    db 0D1h, 03h, 0C2h, 81h, 0C4h, 00h, 01h, 00h, 00h, 0C3h
?d_008a3800@@YAXXZ ENDP

; ghidra: FUN_00ca3dc0  retail @ 0x008A3DC0 size 273
public ?d_008a3dc0@@YAXXZ
?d_008a3dc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 83h, 0F8h, 06h, 53h, 55h, 56h, 57h, 0Fh, 87h, 0F9h, 00h, 00h
    db 00h, 83h, 0F8h, 03h, 0Fh, 82h, 0F0h, 00h, 00h, 00h, 8Bh, 5Ch, 24h, 14h, 50h, 53h
    db 0E8h, 1Bh, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 08h, 83h, 0F8h, 31h, 0Fh, 8Fh, 0D9h, 00h, 00h
    db 00h, 85h, 0C0h, 0Fh, 8Ch, 0D1h, 00h, 00h, 00h, 0Fh, 0BEh, 80h, 58h, 54h, 2Dh, 01h
    db 85h, 0C0h, 7Ch, 58h, 8Bh, 0Ch, 0C5h, 0C8h, 53h, 2Dh, 01h, 8Ah, 11h, 8Dh, 3Ch, 0C5h
    db 0C8h, 53h, 2Dh, 01h, 8Ah, 03h, 3Ah, 0C2h, 0Fh, 85h, 0ACh, 00h, 00h, 00h, 8Dh, 71h
    db 01h, 8Dh, 4Bh, 01h, 8Ah, 01h, 8Ah, 1Eh, 8Ah, 0D0h, 3Ah, 0C3h, 75h, 1Eh, 84h, 0D2h
    db 74h, 16h, 8Ah, 41h, 01h, 8Ah, 5Eh, 01h, 8Ah, 0D0h, 3Ah, 0C3h, 75h, 0Eh, 83h, 0C1h
    db 02h, 83h, 0C6h, 02h, 84h, 0D2h, 75h, 0DCh, 33h, 0C9h, 0EBh, 05h, 1Bh, 0C9h, 83h, 0D9h
    db 0FFh, 85h, 0C9h, 75h, 75h, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh, 5Bh, 0C3h, 83h, 0F8h, 0EEh, 7Dh
    db 69h, 0B9h, 0EDh, 0FFh, 0FFh, 0FFh, 2Bh, 0C8h, 0Fh, 0BEh, 0B9h, 58h, 54h, 2Dh, 01h, 0Fh
    db 0BEh, 89h, 59h, 54h, 2Dh, 01h, 8Dh, 3Ch, 0FDh, 58h, 54h, 2Dh, 01h, 0C1h, 0E1h, 03h
    db 8Bh, 0EFh, 2Bh, 0E9h, 3Bh, 0FDh, 73h, 42h, 8Bh, 0Fh, 8Ah, 03h, 3Ah, 01h, 75h, 33h
    db 8Dh, 71h, 01h, 8Dh, 4Bh, 01h, 8Ah, 01h, 8Ah, 0D0h, 3Ah, 06h, 75h, 1Ch, 84h, 0D2h
    db 74h, 14h, 8Ah, 41h, 01h, 8Ah, 0D0h, 3Ah, 46h, 01h, 75h, 0Eh, 83h, 0C1h, 02h, 83h
    db 0C6h, 02h, 84h, 0D2h, 75h, 0E0h, 33h, 0C9h, 0EBh, 05h, 1Bh, 0C9h, 83h, 0D9h, 0FFh, 85h
    db 0C9h, 74h, 92h, 83h, 0C7h, 08h, 3Bh, 0FDh, 72h, 0BEh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh
    db 0C3h
?d_008a3dc0@@YAXXZ ENDP

; ghidra: FUN_00ca3ee0  retail @ 0x008A3EE0 size 1459
public ?d_008a3ee0@@YAXXZ
?d_008a3ee0@@YAXXZ PROC
    db 81h, 0ECh, 00h, 01h, 00h, 00h, 0B0h, 11h, 88h, 04h, 24h, 88h, 44h, 24h, 01h, 88h
    db 44h, 24h, 02h, 88h, 44h, 24h, 03h, 88h, 44h, 24h, 04h, 88h, 44h, 24h, 05h, 88h
    db 44h, 24h, 06h, 88h, 44h, 24h, 07h, 88h, 44h, 24h, 08h, 88h, 44h, 24h, 09h, 88h
    db 44h, 24h, 0Ah, 88h, 44h, 24h, 0Bh, 88h, 44h, 24h, 0Ch, 88h, 44h, 24h, 0Dh, 88h
    db 44h, 24h, 0Eh, 88h, 44h, 24h, 0Fh, 88h, 44h, 24h, 10h, 88h, 44h, 24h, 11h, 88h
    db 44h, 24h, 12h, 88h, 44h, 24h, 13h, 88h, 44h, 24h, 14h, 88h, 44h, 24h, 15h, 88h
    db 44h, 24h, 16h, 88h, 44h, 24h, 17h, 88h, 44h, 24h, 18h, 88h, 44h, 24h, 19h, 88h
    db 44h, 24h, 1Ah, 88h, 44h, 24h, 1Bh, 88h, 44h, 24h, 1Ch, 88h, 44h, 24h, 1Dh, 88h
    db 44h, 24h, 1Eh, 88h, 44h, 24h, 1Fh, 88h, 44h, 24h, 20h, 88h, 44h, 24h, 21h, 88h
    db 44h, 24h, 22h, 88h, 44h, 24h, 23h, 88h, 44h, 24h, 24h, 88h, 44h, 24h, 25h, 88h
    db 44h, 24h, 26h, 88h, 44h, 24h, 27h, 88h, 44h, 24h, 28h, 88h, 44h, 24h, 29h, 88h
    db 44h, 24h, 2Ah, 88h, 44h, 24h, 2Bh, 88h, 44h, 24h, 2Ch, 88h, 44h, 24h, 2Dh, 88h
    db 44h, 24h, 2Eh, 88h, 44h, 24h, 2Fh, 88h, 44h, 24h, 30h, 88h, 44h, 24h, 31h, 88h
    db 44h, 24h, 32h, 88h, 44h, 24h, 33h, 88h, 44h, 24h, 34h, 88h, 44h, 24h, 35h, 88h
    db 44h, 24h, 36h, 88h, 44h, 24h, 37h, 88h, 44h, 24h, 38h, 88h, 44h, 24h, 39h, 88h
    db 44h, 24h, 3Ah, 88h, 44h, 24h, 3Bh, 88h, 44h, 24h, 3Ch, 88h, 44h, 24h, 3Dh, 88h
    db 44h, 24h, 3Eh, 88h, 44h, 24h, 3Fh, 88h, 44h, 24h, 40h, 88h, 44h, 24h, 41h, 88h
    db 44h, 24h, 42h, 88h, 44h, 24h, 43h, 88h, 44h, 24h, 44h, 88h, 44h, 24h, 45h, 88h
    db 44h, 24h, 46h, 88h, 44h, 24h, 47h, 88h, 44h, 24h, 48h, 88h, 44h, 24h, 49h, 88h
    db 44h, 24h, 4Ah, 88h, 44h, 24h, 4Bh, 88h, 44h, 24h, 4Ch, 88h, 44h, 24h, 4Dh, 88h
    db 44h, 24h, 4Eh, 88h, 44h, 24h, 4Fh, 32h, 0C9h, 88h, 44h, 24h, 50h, 88h, 44h, 24h
    db 51h, 88h, 44h, 24h, 52h, 88h, 44h, 24h, 53h, 88h, 44h, 24h, 54h, 88h, 44h, 24h
    db 55h, 88h, 44h, 24h, 56h, 88h, 44h, 24h, 57h, 88h, 44h, 24h, 58h, 88h, 44h, 24h
    db 59h, 88h, 44h, 24h, 5Ah, 88h, 44h, 24h, 5Bh, 88h, 44h, 24h, 5Ch, 88h, 44h, 24h
    db 5Dh, 88h, 44h, 24h, 5Eh, 88h, 44h, 24h, 5Fh, 88h, 44h, 24h, 60h, 88h, 44h, 24h
    db 61h, 88h, 44h, 24h, 62h, 88h, 4Ch, 24h, 63h, 88h, 4Ch, 24h, 64h, 88h, 4Ch, 24h
    db 65h, 88h, 44h, 24h, 66h, 88h, 4Ch, 24h, 67h, 88h, 44h, 24h, 68h, 88h, 44h, 24h
    db 69h, 88h, 44h, 24h, 6Ah, 88h, 44h, 24h, 6Bh, 88h, 4Ch, 24h, 6Ch, 88h, 44h, 24h
    db 6Dh, 88h, 44h, 24h, 6Eh, 88h, 44h, 24h, 6Fh, 88h, 44h, 24h, 70h, 88h, 44h, 24h
    db 71h, 88h, 44h, 24h, 72h, 0C6h, 44h, 24h, 73h, 05h, 88h, 4Ch, 24h, 74h, 88h, 44h
    db 24h, 75h, 88h, 44h, 24h, 76h, 88h, 44h, 24h, 77h, 88h, 44h, 24h, 78h, 88h, 44h
    db 24h, 79h, 88h, 44h, 24h, 7Ah, 88h, 44h, 24h, 7Bh, 88h, 44h, 24h, 7Ch, 88h, 44h
    db 24h, 7Dh, 88h, 44h, 24h, 7Eh, 88h, 44h, 24h, 7Fh, 88h, 84h, 24h, 80h, 00h, 00h
    db 00h, 88h, 84h, 24h, 81h, 00h, 00h, 00h, 88h, 84h, 24h, 82h, 00h, 00h, 00h, 88h
    db 84h, 24h, 83h, 00h, 00h, 00h, 88h, 84h, 24h, 84h, 00h, 00h, 00h, 88h, 84h, 24h
    db 85h, 00h, 00h, 00h, 88h, 84h, 24h, 86h, 00h, 00h, 00h, 88h, 84h, 24h, 87h, 00h
    db 00h, 00h, 88h, 84h, 24h, 88h, 00h, 00h, 00h, 88h, 84h, 24h, 89h, 00h, 00h, 00h
    db 88h, 84h, 24h, 8Ah, 00h, 00h, 00h, 88h, 84h, 24h, 8Bh, 00h, 00h, 00h, 88h, 84h
    db 24h, 8Ch, 00h, 00h, 00h, 88h, 84h, 24h, 8Dh, 00h, 00h, 00h, 88h, 84h, 24h, 8Eh
    db 00h, 00h, 00h, 88h, 84h, 24h, 8Fh, 00h, 00h, 00h, 88h, 84h, 24h, 90h, 00h, 00h
    db 00h, 88h, 84h, 24h, 91h, 00h, 00h, 00h, 88h, 84h, 24h, 92h, 00h, 00h, 00h, 88h
    db 84h, 24h, 93h, 00h, 00h, 00h, 88h, 84h, 24h, 94h, 00h, 00h, 00h, 88h, 84h, 24h
    db 95h, 00h, 00h, 00h, 88h, 84h, 24h, 96h, 00h, 00h, 00h, 88h, 84h, 24h, 97h, 00h
    db 00h, 00h, 88h, 84h, 24h, 98h, 00h, 00h, 00h, 88h, 84h, 24h, 99h, 00h, 00h, 00h
    db 88h, 84h, 24h, 9Ah, 00h, 00h, 00h, 88h, 84h, 24h, 9Bh, 00h, 00h, 00h, 88h, 84h
    db 24h, 9Ch, 00h, 00h, 00h, 88h, 84h, 24h, 9Dh, 00h, 00h, 00h, 88h, 84h, 24h, 9Eh
    db 00h, 00h, 00h, 88h, 84h, 24h, 9Fh, 00h, 00h, 00h, 88h, 84h, 24h, 0A0h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0A1h, 00h, 00h, 00h, 88h, 84h, 24h, 0A2h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0A3h, 00h, 00h, 00h, 88h, 84h, 24h, 0A4h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0A5h, 00h, 00h, 00h, 88h, 84h, 24h, 0A6h, 00h, 00h, 00h, 88h, 84h, 24h, 0A7h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0A8h, 00h, 00h, 00h, 88h, 84h, 24h, 0A9h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0AAh, 00h, 00h, 00h, 88h, 84h, 24h, 0ABh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0ACh, 00h, 00h, 00h, 88h, 84h, 24h, 0ADh, 00h, 00h, 00h, 88h, 84h, 24h, 0AEh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0AFh, 00h, 00h, 00h, 88h, 84h, 24h, 0B0h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0B1h, 00h, 00h, 00h, 88h, 84h, 24h, 0B2h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0B3h, 00h, 00h, 00h, 88h, 84h, 24h, 0B4h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0B5h, 00h, 00h, 00h, 88h, 84h, 24h, 0B6h, 00h, 00h, 00h, 88h, 84h, 24h, 0B7h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0B8h, 00h, 00h, 00h, 88h, 84h, 24h, 0B9h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0BAh, 00h, 00h, 00h, 88h, 84h, 24h, 0BBh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0BCh, 00h, 00h, 00h, 88h, 84h, 24h, 0BDh, 00h, 00h, 00h, 88h, 84h, 24h, 0BEh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0BFh, 00h, 00h, 00h, 88h, 84h, 24h, 0C0h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0C1h, 00h, 00h, 00h, 88h, 84h, 24h, 0C2h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0C3h, 00h, 00h, 00h, 88h, 84h, 24h, 0C4h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0C5h, 00h, 00h, 00h, 88h, 84h, 24h, 0C6h, 00h, 00h, 00h, 88h, 84h, 24h, 0C7h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0C8h, 00h, 00h, 00h, 88h, 84h, 24h, 0C9h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0CAh, 00h, 00h, 00h, 88h, 84h, 24h, 0CBh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0CCh, 00h, 00h, 00h, 88h, 84h, 24h, 0CDh, 00h, 00h, 00h, 88h, 84h, 24h, 0CEh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0CFh, 00h, 00h, 00h, 88h, 84h, 24h, 0D0h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0D1h, 00h, 00h, 00h, 88h, 84h, 24h, 0D2h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0D3h, 00h, 00h, 00h, 88h, 84h, 24h, 0D4h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0D5h, 00h, 00h, 00h, 88h, 84h, 24h, 0D6h, 00h, 00h, 00h, 88h, 84h, 24h, 0D7h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0D8h, 00h, 00h, 00h, 88h, 84h, 24h, 0D9h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0DAh, 00h, 00h, 00h, 88h, 84h, 24h, 0DBh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0DCh, 00h, 00h, 00h, 88h, 84h, 24h, 0DDh, 00h, 00h, 00h, 88h, 84h, 24h, 0DEh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0DFh, 00h, 00h, 00h, 88h, 84h, 24h, 0E0h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0E1h, 00h, 00h, 00h, 88h, 84h, 24h, 0E2h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0E3h, 00h, 00h, 00h, 88h, 84h, 24h, 0E4h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0E5h, 00h, 00h, 00h, 88h, 84h, 24h, 0E6h, 00h, 00h, 00h, 88h, 84h, 24h, 0E7h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0E8h, 00h, 00h, 00h, 88h, 84h, 24h, 0E9h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0EAh, 00h, 00h, 00h, 88h, 84h, 24h, 0EBh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0ECh, 00h, 00h, 00h, 88h, 84h, 24h, 0EDh, 00h, 00h, 00h, 88h, 84h, 24h, 0EEh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0EFh, 00h, 00h, 00h, 88h, 84h, 24h, 0F0h, 00h, 00h
    db 00h, 8Bh, 8Ch, 24h, 08h, 01h, 00h, 00h, 88h, 84h, 24h, 0F1h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0F2h, 00h, 00h, 00h, 88h, 84h, 24h, 0F3h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0F4h, 00h, 00h, 00h, 88h, 84h, 24h, 0F5h, 00h, 00h, 00h, 88h, 84h, 24h, 0F6h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0F7h, 00h, 00h, 00h, 88h, 84h, 24h, 0F8h, 00h, 00h, 00h
    db 88h, 84h, 24h, 0F9h, 00h, 00h, 00h, 88h, 84h, 24h, 0FAh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0FBh, 00h, 00h, 00h, 88h, 84h, 24h, 0FCh, 00h, 00h, 00h, 88h, 84h, 24h, 0FDh
    db 00h, 00h, 00h, 88h, 84h, 24h, 0FEh, 00h, 00h, 00h, 88h, 84h, 24h, 0FFh, 00h, 00h
    db 00h, 8Bh, 84h, 24h, 04h, 01h, 00h, 00h, 0Fh, 0B6h, 54h, 08h, 0FFh, 0Fh, 0B6h, 00h
    db 0Fh, 0B6h, 14h, 14h, 0Fh, 0B6h, 04h, 04h, 03h, 0D1h, 03h, 0C2h, 81h, 0C4h, 00h, 01h
    db 00h, 00h, 0C3h
?d_008a3ee0@@YAXXZ ENDP

; ghidra: FUN_00ca44a0  retail @ 0x008A44A0 size 130
public ?d_008a44a0@@YAXXZ
?d_008a44a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 83h, 0F8h, 0Eh, 55h, 57h, 77h, 72h, 83h, 0F8h, 04h, 72h, 6Dh
    db 8Bh, 7Ch, 24h, 0Ch, 50h, 57h, 0E8h, 25h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 08h, 83h, 0F8h
    db 10h, 7Fh, 5Ah, 85h, 0C0h, 7Ch, 56h, 8Bh, 0Ch, 0C5h, 90h, 54h, 2Dh, 01h, 8Ah, 11h
    db 8Dh, 2Ch, 0C5h, 90h, 54h, 2Dh, 01h, 8Ah, 07h, 3Ah, 0C2h, 75h, 40h, 53h, 56h, 8Dh
    db 71h, 01h, 8Dh, 4Fh, 01h, 8Ah, 01h, 8Ah, 1Eh, 8Ah, 0D0h, 3Ah, 0C3h, 75h, 1Eh, 84h
    db 0D2h, 74h, 16h, 8Ah, 41h, 01h, 8Ah, 5Eh, 01h, 8Ah, 0D0h, 3Ah, 0C3h, 75h, 0Eh, 83h
    db 0C1h, 02h, 83h, 0C6h, 02h, 84h, 0D2h, 75h, 0DCh, 33h, 0C9h, 0EBh, 05h, 1Bh, 0C9h, 83h
    db 0D9h, 0FFh, 85h, 0C9h, 5Eh, 5Bh, 75h, 05h, 5Fh, 8Bh, 0C5h, 5Dh, 0C3h, 5Fh, 33h, 0C0h
    db 5Dh, 0C3h
?d_008a44a0@@YAXXZ ENDP

; ghidra: FUN_00ca4630  retail @ 0x008A4630 size 383
public ?d_008a4630@@YAXXZ
?d_008a4630@@YAXXZ PROC
    db 8Bh, 0Dh, 34h, 7Ah, 33h, 01h, 56h, 33h, 0F6h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh
    db 50h, 04h, 89h, 35h, 34h, 7Ah, 33h, 01h, 8Bh, 0Dh, 38h, 7Ah, 33h, 01h, 3Bh, 0CEh
    db 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 38h, 7Ah, 33h, 01h, 8Bh, 0Dh, 3Ch
    db 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 3Ch, 7Ah
    db 33h, 01h, 8Bh, 0Dh, 40h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h
    db 04h, 89h, 35h, 40h, 7Ah, 33h, 01h, 8Bh, 0Dh, 44h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h
    db 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 44h, 7Ah, 33h, 01h, 8Bh, 0Dh, 48h, 7Ah
    db 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 48h, 7Ah, 33h
    db 01h, 8Bh, 0Dh, 4Ch, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h
    db 89h, 35h, 4Ch, 7Ah, 33h, 01h, 8Bh, 0Dh, 50h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh
    db 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 50h, 7Ah, 33h, 01h, 8Bh, 0Dh, 54h, 7Ah, 33h
    db 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 54h, 7Ah, 33h, 01h
    db 8Bh, 0Dh, 58h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h
    db 35h, 58h, 7Ah, 33h, 01h, 8Bh, 0Dh, 5Ch, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh
    db 01h, 0FFh, 50h, 04h, 89h, 35h, 5Ch, 7Ah, 33h, 01h, 8Bh, 0Dh, 60h, 7Ah, 33h, 01h
    db 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 60h, 7Ah, 33h, 01h, 8Bh
    db 0Dh, 64h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h
    db 64h, 7Ah, 33h, 01h, 8Bh, 0Dh, 68h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h
    db 0FFh, 52h, 04h, 89h, 35h, 68h, 7Ah, 33h, 01h, 8Bh, 0Dh, 6Ch, 7Ah, 33h, 01h, 3Bh
    db 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 6Ch, 7Ah, 33h, 01h, 8Bh, 0Dh
    db 70h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 70h
    db 7Ah, 33h, 01h, 8Bh, 0Dh, 74h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh
    db 50h, 04h, 89h, 35h, 74h, 7Ah, 33h, 01h, 8Bh, 0Dh, 78h, 7Ah, 33h, 01h, 3Bh, 0CEh
    db 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 78h, 7Ah, 33h, 01h, 5Eh, 0C3h
?d_008a4630@@YAXXZ ENDP

; ghidra: FUN_00ca47b0  retail @ 0x008A47B0 size 173
public ?d_008a47b0@@YAXXZ
?d_008a47b0@@YAXXZ PROC
    db 8Bh, 0Dh, 7Ch, 7Ah, 33h, 01h, 56h, 33h, 0F6h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh
    db 50h, 04h, 89h, 35h, 7Ch, 7Ah, 33h, 01h, 8Bh, 0Dh, 80h, 7Ah, 33h, 01h, 3Bh, 0CEh
    db 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 80h, 7Ah, 33h, 01h, 8Bh, 0Dh, 84h
    db 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 84h, 7Ah
    db 33h, 01h, 8Bh, 0Dh, 8Ch, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h
    db 04h, 89h, 35h, 8Ch, 7Ah, 33h, 01h, 8Bh, 0Dh, 90h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h
    db 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 90h, 7Ah, 33h, 01h, 8Bh, 0Dh, 94h, 7Ah
    db 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 94h, 7Ah, 33h
    db 01h, 8Bh, 0Dh, 98h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h
    db 89h, 35h, 98h, 7Ah, 33h, 01h, 8Bh, 0Dh, 88h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh
    db 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 88h, 7Ah, 33h, 01h, 5Eh, 0C3h
?d_008a47b0@@YAXXZ ENDP

; ghidra: FUN_00ca4860  retail @ 0x008A4860 size 51
public ?d_008a4860@@YAXXZ
?d_008a4860@@YAXXZ PROC
    db 8Bh, 0Dh, 9Ch, 7Ah, 33h, 01h, 85h, 0C9h, 74h, 0Fh, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h
    db 05h, 9Ch, 7Ah, 33h, 01h, 00h, 00h, 00h, 00h, 8Bh, 0Dh, 0A0h, 7Ah, 33h, 01h, 85h
    db 0C9h, 74h, 0Fh, 8Bh, 11h, 0FFh, 52h, 04h, 0C7h, 05h, 0A0h, 7Ah, 33h, 01h, 00h, 00h
    db 00h, 00h, 0C3h
?d_008a4860@@YAXXZ ENDP

; ghidra: FUN_00ca48a0  retail @ 0x008A48A0 size 44
public ?d_008a48a0@@YAXXZ
?d_008a48a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 30h, 57h, 83h, 0C6h, 08h, 33h, 0D2h, 0BFh, 88h, 66h
    db 13h, 01h, 0B9h, 0Eh, 00h, 00h, 00h, 0F3h, 0A6h, 8Bh, 0Dh, 0A8h, 79h, 33h, 01h, 8Bh
    db 0C2h, 0Fh, 95h, 0C0h, 5Fh, 5Eh, 48h, 23h, 0C1h, 0C2h, 08h, 00h
?d_008a48a0@@YAXXZ ENDP

; ghidra: FUN_00ca48d0  retail @ 0x008A48D0 size 131
public ?d_008a48d0@@YAXXZ
?d_008a48d0@@YAXXZ PROC
    db 8Bh, 0Dh, 0A4h, 7Ah, 33h, 01h, 56h, 33h, 0F6h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh
    db 50h, 04h, 89h, 35h, 0A4h, 7Ah, 33h, 01h, 8Bh, 0Dh, 0A8h, 7Ah, 33h, 01h, 3Bh, 0CEh
    db 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 0A8h, 7Ah, 33h, 01h, 8Bh, 0Dh, 0ACh
    db 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 0ACh, 7Ah
    db 33h, 01h, 8Bh, 0Dh, 0B0h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h
    db 04h, 89h, 35h, 0B0h, 7Ah, 33h, 01h, 8Bh, 0Dh, 0B4h, 7Ah, 33h, 01h, 3Bh, 0CEh, 74h
    db 0Bh, 8Bh, 01h, 0FFh, 50h, 04h, 89h, 35h, 0B4h, 7Ah, 33h, 01h, 8Bh, 0Dh, 0B8h, 7Ah
    db 33h, 01h, 3Bh, 0CEh, 74h, 0Bh, 8Bh, 11h, 0FFh, 52h, 04h, 89h, 35h, 0B8h, 7Ah, 33h
    db 01h, 5Eh, 0C3h
?d_008a48d0@@YAXXZ ENDP

; ghidra: FUN_00ca4960  retail @ 0x008A4960 size 305
public ?d_008a4960@@YAXXZ
?d_008a4960@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D0h, 7Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 8Bh, 00h, 53h, 56h, 83h, 0C0h
    db 08h, 57h, 8Bh, 0D9h, 0BFh, 0CCh, 0ABh, 12h, 01h, 8Bh, 0F0h, 0B9h, 08h, 00h, 00h, 00h
    db 33h, 0D2h, 0F3h, 0A6h, 75h, 6Ah, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h
    db 24h, 98h, 52h, 2Dh, 01h, 8Bh, 4Ch, 24h, 28h, 8Dh, 44h, 24h, 24h, 50h, 89h, 54h
    db 24h, 1Ch, 0E8h, 09h, 3Ch, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 24h, 51h, 8Dh, 4Bh, 20h, 0E8h
    db 0BCh, 0BAh, 0FFh, 0FFh, 8Bh, 44h, 24h, 24h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h
    db 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0Fh, 85h, 88h, 00h, 00h, 00h, 8Bh, 15h, 30h
    db 7Ah, 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 5Fh, 5Eh, 0B0h, 01h, 5Bh, 8Bh
    db 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h
    db 8Bh, 0F0h, 0BFh, 0A0h, 95h, 11h, 01h, 0B9h, 05h, 00h, 00h, 00h, 33h, 0C0h, 0F3h, 0A6h
    db 75h, 69h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 0Ch, 98h, 52h, 2Dh
    db 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 4Ch, 24h, 2Ch, 0C7h, 44h, 24h, 1Ch, 01h, 00h
    db 00h, 00h, 0E8h, 89h, 3Bh, 0FFh, 0FFh, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 4Bh, 24h, 0E8h
    db 3Ch, 0BAh, 0FFh, 0FFh, 8Bh, 44h, 24h, 0Ch, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h
    db 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh
    db 50h, 04h, 83h, 0C4h, 04h, 5Fh, 5Eh, 0B0h, 01h, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh
    db 5Eh, 32h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 0Ch
    db 00h
?d_008a4960@@YAXXZ ENDP

; ghidra: FUN_00ca4aa0  retail @ 0x008A4AA0 size 26
public ?d_008a4aa0@@YAXXZ
?d_008a4aa0@@YAXXZ PROC
    db 8Bh, 0Dh, 0BCh, 7Ah, 33h, 01h, 85h, 0C9h, 74h, 0Fh, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h
    db 05h, 0BCh, 7Ah, 33h, 01h, 00h, 00h, 00h, 00h, 0C3h
?d_008a4aa0@@YAXXZ ENDP

; ghidra: FUN_00ca4b20  retail @ 0x008A4B20 size 51
public ?d_008a4b20@@YAXXZ
?d_008a4b20@@YAXXZ PROC
    db 8Bh, 01h, 40h, 89h, 01h, 8Bh, 54h, 81h, 04h, 85h, 0D2h, 74h, 15h, 8Dh, 49h, 00h
    db 83h, 0F8h, 3Fh, 7Dh, 03h, 40h, 0EBh, 02h, 33h, 0C0h, 8Bh, 54h, 81h, 04h, 85h, 0D2h
    db 75h, 0EEh, 8Bh, 54h, 24h, 04h, 89h, 54h, 81h, 04h, 8Bh, 02h, 8Bh, 0CAh, 0FFh, 10h
    db 0C2h, 04h, 00h
?d_008a4b20@@YAXXZ ENDP

; ghidra: FUN_00ca4b60  retail @ 0x008A4B60 size 98
public ?d_008a4b60@@YAXXZ
?d_008a4b60@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 4Ch, 24h, 0Ch, 33h, 0F6h, 8Dh, 47h, 08h, 8Dh, 49h, 00h
    db 39h, 48h, 0FCh, 74h, 2Bh, 39h, 08h, 74h, 1Ch, 39h, 48h, 04h, 74h, 1Ah, 39h, 48h
    db 08h, 74h, 1Ah, 83h, 0C6h, 04h, 83h, 0C0h, 10h, 83h, 0FEh, 40h, 7Ch, 0E2h, 5Fh, 33h
    db 0C0h, 5Eh, 0C2h, 04h, 00h, 46h, 0EBh, 08h, 83h, 0C6h, 02h, 0EBh, 03h, 83h, 0C6h, 03h
    db 83h, 0FEh, 40h, 7Dh, 0E9h, 0FFh, 0Fh, 8Bh, 4Ch, 0B7h, 04h, 8Bh, 01h, 0FFh, 50h, 04h
    db 0C7h, 44h, 0B7h, 04h, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C2h
    db 04h, 00h
?d_008a4b60@@YAXXZ ENDP

; ghidra: FUN_00ca4bd0  retail @ 0x008A4BD0 size 39
public ?d_008a4bd0@@YAXXZ
?d_008a4bd0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 33h, 0C0h, 83h, 0C1h, 04h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 39h, 11h, 74h, 0Eh, 40h, 83h, 0C1h, 04h, 83h, 0F8h, 40h, 7Ch, 0F3h, 32h, 0C0h, 0C2h
    db 04h, 00h, 0B0h, 01h, 0C2h, 04h, 00h
?d_008a4bd0@@YAXXZ ENDP

; ghidra: FUN_00ca4c90  retail @ 0x008A4C90 size 33
public ?d_008a4c90@@YAXXZ
?d_008a4c90@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 0Ch, 6Ah
    db 0Ch, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_008a4c90@@YAXXZ ENDP

; ghidra: FUN_00ca4cd0  retail @ 0x008A4CD0 size 184
public ?d_008a4cd0@@YAXXZ
?d_008a4cd0@@YAXXZ PROC
    db 0A1h, 0CCh, 87h, 33h, 01h, 85h, 0C0h, 56h, 57h, 74h, 3Ch, 8Bh, 48h, 08h, 8Bh, 15h
    db 10h, 78h, 33h, 01h, 89h, 0Dh, 0CCh, 87h, 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh
    db 4Ah, 04h, 7Ch, 11h, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 8Bh, 4Ch, 24h, 0Ch, 5Fh
    db 89h, 48h, 08h, 5Eh, 0C3h, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh, 01h, 8Bh, 4Ch, 24h
    db 0Ch, 5Fh, 89h, 48h, 08h, 5Eh, 0C3h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h
    db 0C4h, 04h, 85h, 0C0h, 74h, 5Dh, 8Bh, 48h, 04h, 81h, 0E1h, 06h, 80h, 00h, 0F0h, 81h
    db 0C9h, 06h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh, 35h
    db 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 53h, 8Bh, 1Eh, 8Dh, 56h, 04h, 3Bh, 0FBh, 5Bh
    db 7Ch, 19h, 8Bh, 54h, 24h, 0Ch, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 5Fh, 89h, 48h, 04h
    db 0C7h, 00h, 98h, 66h, 13h, 01h, 89h, 50h, 08h, 5Eh, 0C3h, 8Bh, 4Eh, 08h, 89h, 04h
    db 0B9h, 0FFh, 02h, 8Bh, 54h, 24h, 0Ch, 5Fh, 0C7h, 00h, 98h, 66h, 13h, 01h, 89h, 50h
    db 08h, 5Eh, 0C3h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
?d_008a4cd0@@YAXXZ ENDP

; ghidra: FUN_00ca5500  retail @ 0x008A5500 size 94
public ?d_008a5500@@YAXXZ
?d_008a5500@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F3h, 7Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 58h
    db 60h, 13h, 01h, 6Ah, 00h, 6Ah, 00h, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 0E8h
    db 9Ch, 20h, 0FFh, 0FFh, 8Dh, 4Eh, 08h, 0C7h, 46h, 18h, 00h, 00h, 00h, 00h, 0C6h, 44h
    db 24h, 10h, 00h, 0E8h, 28h, 77h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh
    db 13h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008a5500@@YAXXZ ENDP

; ghidra: FUN_00ca6100  retail @ 0x008A6100 size 235
_TEXT ENDS
_TEXT$d00ca6100 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA6100 size 235
public ?d_008a6100@@YAXXZ
?d_008a6100@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01057E97
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 056h
    db 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 043h, 08Bh, 046h, 00Ch, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 0A3h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 053h, 08Bh, 019h, 08Dh, 041h, 004h, 03Bh, 0D3h, 05Bh, 07Ch, 009h, 081h, 066h
    db 004h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh
    db 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 039h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 030h, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 004h, 085h, 0C0h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 010h, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 0F0h, 08Bh, 04Ch
    db 024h, 018h, 08Dh, 054h, 024h, 004h, 052h
    call ?keyValuePairs00898D80@KeyValuePairs00898D80@@QAE?AVRva8CD130String@@XZ
    db 08Bh, 000h, 083h, 0C0h, 008h, 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 014h, 001h, 000h, 000h, 000h
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 08Bh, 044h, 024h, 004h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 010h, 0FFh
    db 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 008h, 08Bh, 0C6h, 05Eh, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C3h
?d_008a6100@@YAXXZ ENDP
_TEXT$d00ca6100 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca61f0  retail @ 0x008A61F0 size 163
public ?d_008a61f0@@YAXXZ
?d_008a61f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D6h, 7Eh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0E0h
    db 66h, 13h, 01h, 8Bh, 46h, 24h, 66h, 0FFh, 08h, 66h, 8Bh, 08h, 0C7h, 44h, 24h, 10h
    db 01h, 00h, 00h, 00h, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h
    db 0C4h, 04h, 8Bh, 46h, 20h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C6h, 44h, 24h, 10h
    db 00h, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h
    db 0C7h, 06h, 58h, 60h, 13h, 01h, 6Ah, 00h, 6Ah, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 18h
    db 03h, 00h, 00h, 00h, 0E8h, 67h, 13h, 0FFh, 0FFh, 8Dh, 4Eh, 08h, 0C7h, 46h, 18h, 00h
    db 00h, 00h, 00h, 0C6h, 44h, 24h, 10h, 02h, 0E8h, 0F3h, 69h, 0FFh, 0FFh, 8Bh, 4Ch, 24h
    db 08h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_008a61f0@@YAXXZ ENDP

; ghidra: FUN_00ca62a0  retail @ 0x008A62A0 size 235
_TEXT ENDS
_TEXT$d00ca62a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CA62A0 size 235
public ?d_008a62a0@@YAXXZ
?d_008a62a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01057EF7
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 056h
    db 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 043h, 08Bh, 046h, 00Ch, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 0A3h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 053h, 08Bh, 019h, 08Dh, 041h, 004h, 03Bh, 0D3h, 05Bh, 07Ch, 009h, 081h, 066h
    db 004h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh
    db 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 039h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 030h, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 004h, 085h, 0C0h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 010h, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 0F0h, 08Bh, 04Ch
    db 024h, 018h, 08Dh, 054h, 024h, 004h, 052h
    call ?keyValuePairs00898D80@KeyValuePairs00898D80@@QAE?AVRva8CD130String@@XZ
    db 08Bh, 000h, 083h, 0C0h, 008h, 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 014h, 001h, 000h, 000h, 000h
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 08Bh, 044h, 024h, 004h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 010h, 0FFh
    db 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 008h, 08Bh, 0C6h, 05Eh, 064h, 089h
    db 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C3h
?d_008a62a0@@YAXXZ ENDP
_TEXT$d00ca62a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ca6410  retail @ 0x008A6410 size 42
public ?d_008a6410@@YAXXZ
?d_008a6410@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0D8h, 0FDh, 0FFh, 0FFh, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 0Bh, 0Fh, 0FFh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 30h, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008a6410@@YAXXZ ENDP

; ghidra: FUN_00ca90f0  retail @ 0x008A90F0 size 33
public ?d_008a90f0@@YAXXZ
?d_008a90f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0C0h, 08h, 56h, 50h, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Bh
    db 0F0h, 83h, 0C6h, 08h, 56h, 0E8h, 0F6h, 0E1h, 0FEh, 0FFh, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh
    db 0C3h
?d_008a90f0@@YAXXZ ENDP

; ghidra: FUN_00ca9120  retail @ 0x008A9120 size 34
public ?d_008a9120@@YAXXZ
?d_008a9120@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 56h, 0E8h, 05h, 0E2h, 0FEh, 0FFh, 8Bh, 44h, 24h, 10h, 83h
    db 0C0h, 08h, 50h, 83h, 0C6h, 0F8h, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 0Ch
    db 5Eh, 0C3h
?d_008a9120@@YAXXZ ENDP

; ghidra: FUN_00ca9150  retail @ 0x008A9150 size 1461
public ?d_008a9150@@YAXXZ
?d_008a9150@@YAXXZ PROC
    db 81h, 0ECh, 00h, 01h, 00h, 00h, 0B0h, 17h, 88h, 04h, 24h, 88h, 44h, 24h, 01h, 88h
    db 44h, 24h, 02h, 88h, 44h, 24h, 03h, 88h, 44h, 24h, 04h, 88h, 44h, 24h, 05h, 88h
    db 44h, 24h, 06h, 88h, 44h, 24h, 07h, 88h, 44h, 24h, 08h, 88h, 44h, 24h, 09h, 88h
    db 44h, 24h, 0Ah, 88h, 44h, 24h, 0Bh, 88h, 44h, 24h, 0Ch, 88h, 44h, 24h, 0Dh, 88h
    db 44h, 24h, 0Eh, 88h, 44h, 24h, 0Fh, 88h, 44h, 24h, 10h, 88h, 44h, 24h, 11h, 88h
    db 44h, 24h, 12h, 88h, 44h, 24h, 13h, 88h, 44h, 24h, 14h, 88h, 44h, 24h, 15h, 88h
    db 44h, 24h, 16h, 88h, 44h, 24h, 17h, 88h, 44h, 24h, 18h, 88h, 44h, 24h, 19h, 88h
    db 44h, 24h, 1Ah, 88h, 44h, 24h, 1Bh, 88h, 44h, 24h, 1Ch, 88h, 44h, 24h, 1Dh, 88h
    db 44h, 24h, 1Eh, 88h, 44h, 24h, 1Fh, 88h, 44h, 24h, 20h, 88h, 44h, 24h, 21h, 88h
    db 44h, 24h, 22h, 88h, 44h, 24h, 23h, 88h, 44h, 24h, 24h, 88h, 44h, 24h, 25h, 88h
    db 44h, 24h, 26h, 88h, 44h, 24h, 27h, 88h, 44h, 24h, 28h, 88h, 44h, 24h, 29h, 88h
    db 44h, 24h, 2Ah, 88h, 44h, 24h, 2Bh, 88h, 44h, 24h, 2Ch, 88h, 44h, 24h, 2Dh, 88h
    db 44h, 24h, 2Eh, 88h, 44h, 24h, 2Fh, 88h, 44h, 24h, 30h, 88h, 44h, 24h, 31h, 88h
    db 44h, 24h, 32h, 88h, 44h, 24h, 33h, 88h, 44h, 24h, 34h, 88h, 44h, 24h, 35h, 88h
    db 44h, 24h, 36h, 88h, 44h, 24h, 37h, 88h, 44h, 24h, 38h, 88h, 44h, 24h, 39h, 88h
    db 44h, 24h, 3Ah, 88h, 44h, 24h, 3Bh, 88h, 44h, 24h, 3Ch, 88h, 44h, 24h, 3Dh, 88h
    db 44h, 24h, 3Eh, 88h, 44h, 24h, 3Fh, 88h, 44h, 24h, 40h, 88h, 44h, 24h, 41h, 88h
    db 44h, 24h, 42h, 88h, 44h, 24h, 43h, 88h, 44h, 24h, 44h, 88h, 44h, 24h, 45h, 88h
    db 44h, 24h, 46h, 88h, 44h, 24h, 47h, 88h, 44h, 24h, 48h, 88h, 44h, 24h, 49h, 88h
    db 44h, 24h, 4Ah, 88h, 44h, 24h, 4Bh, 88h, 44h, 24h, 4Ch, 88h, 44h, 24h, 4Dh, 88h
    db 44h, 24h, 4Eh, 88h, 44h, 24h, 4Fh, 32h, 0C9h, 0B2h, 0Ah, 88h, 44h, 24h, 50h, 88h
    db 44h, 24h, 51h, 88h, 44h, 24h, 52h, 88h, 44h, 24h, 53h, 88h, 44h, 24h, 54h, 88h
    db 44h, 24h, 55h, 88h, 44h, 24h, 56h, 88h, 44h, 24h, 57h, 88h, 44h, 24h, 58h, 88h
    db 44h, 24h, 59h, 88h, 44h, 24h, 5Ah, 88h, 44h, 24h, 5Bh, 88h, 44h, 24h, 5Ch, 88h
    db 44h, 24h, 5Dh, 88h, 44h, 24h, 5Eh, 88h, 44h, 24h, 5Fh, 88h, 44h, 24h, 60h, 88h
    db 44h, 24h, 61h, 88h, 44h, 24h, 62h, 88h, 4Ch, 24h, 63h, 88h, 44h, 24h, 64h, 88h
    db 54h, 24h, 65h, 88h, 4Ch, 24h, 66h, 88h, 4Ch, 24h, 67h, 88h, 54h, 24h, 68h, 88h
    db 4Ch, 24h, 69h, 88h, 44h, 24h, 6Ah, 88h, 44h, 24h, 6Bh, 88h, 4Ch, 24h, 6Ch, 88h
    db 44h, 24h, 6Dh, 88h, 44h, 24h, 6Eh, 88h, 44h, 24h, 6Fh, 88h, 44h, 24h, 70h, 88h
    db 44h, 24h, 71h, 0C6h, 44h, 24h, 72h, 0Eh, 88h, 4Ch, 24h, 73h, 88h, 4Ch, 24h, 74h
    db 88h, 44h, 24h, 75h, 88h, 44h, 24h, 76h, 88h, 44h, 24h, 77h, 88h, 44h, 24h, 78h
    db 88h, 44h, 24h, 79h, 88h, 44h, 24h, 7Ah, 88h, 44h, 24h, 7Bh, 88h, 44h, 24h, 7Ch
    db 88h, 44h, 24h, 7Dh, 88h, 44h, 24h, 7Eh, 88h, 44h, 24h, 7Fh, 88h, 84h, 24h, 80h
    db 00h, 00h, 00h, 88h, 84h, 24h, 81h, 00h, 00h, 00h, 88h, 84h, 24h, 82h, 00h, 00h
    db 00h, 88h, 84h, 24h, 83h, 00h, 00h, 00h, 88h, 84h, 24h, 84h, 00h, 00h, 00h, 88h
    db 84h, 24h, 85h, 00h, 00h, 00h, 88h, 84h, 24h, 86h, 00h, 00h, 00h, 88h, 84h, 24h
    db 87h, 00h, 00h, 00h, 88h, 84h, 24h, 88h, 00h, 00h, 00h, 88h, 84h, 24h, 89h, 00h
    db 00h, 00h, 88h, 84h, 24h, 8Ah, 00h, 00h, 00h, 88h, 84h, 24h, 8Bh, 00h, 00h, 00h
    db 88h, 84h, 24h, 8Ch, 00h, 00h, 00h, 88h, 84h, 24h, 8Dh, 00h, 00h, 00h, 88h, 84h
    db 24h, 8Eh, 00h, 00h, 00h, 88h, 84h, 24h, 8Fh, 00h, 00h, 00h, 88h, 84h, 24h, 90h
    db 00h, 00h, 00h, 88h, 84h, 24h, 91h, 00h, 00h, 00h, 88h, 84h, 24h, 92h, 00h, 00h
    db 00h, 88h, 84h, 24h, 93h, 00h, 00h, 00h, 88h, 84h, 24h, 94h, 00h, 00h, 00h, 88h
    db 84h, 24h, 95h, 00h, 00h, 00h, 88h, 84h, 24h, 96h, 00h, 00h, 00h, 88h, 84h, 24h
    db 97h, 00h, 00h, 00h, 88h, 84h, 24h, 98h, 00h, 00h, 00h, 88h, 84h, 24h, 99h, 00h
    db 00h, 00h, 88h, 84h, 24h, 9Ah, 00h, 00h, 00h, 88h, 84h, 24h, 9Bh, 00h, 00h, 00h
    db 88h, 84h, 24h, 9Ch, 00h, 00h, 00h, 88h, 84h, 24h, 9Dh, 00h, 00h, 00h, 88h, 84h
    db 24h, 9Eh, 00h, 00h, 00h, 88h, 84h, 24h, 9Fh, 00h, 00h, 00h, 88h, 84h, 24h, 0A0h
    db 00h, 00h, 00h, 88h, 84h, 24h, 0A1h, 00h, 00h, 00h, 88h, 84h, 24h, 0A2h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0A3h, 00h, 00h, 00h, 88h, 84h, 24h, 0A4h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0A5h, 00h, 00h, 00h, 88h, 84h, 24h, 0A6h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0A7h, 00h, 00h, 00h, 88h, 84h, 24h, 0A8h, 00h, 00h, 00h, 88h, 84h, 24h, 0A9h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0AAh, 00h, 00h, 00h, 88h, 84h, 24h, 0ABh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0ACh, 00h, 00h, 00h, 88h, 84h, 24h, 0ADh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0AEh, 00h, 00h, 00h, 88h, 84h, 24h, 0AFh, 00h, 00h, 00h, 88h, 84h, 24h, 0B0h
    db 00h, 00h, 00h, 88h, 84h, 24h, 0B1h, 00h, 00h, 00h, 88h, 84h, 24h, 0B2h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0B3h, 00h, 00h, 00h, 88h, 84h, 24h, 0B4h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0B5h, 00h, 00h, 00h, 88h, 84h, 24h, 0B6h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0B7h, 00h, 00h, 00h, 88h, 84h, 24h, 0B8h, 00h, 00h, 00h, 88h, 84h, 24h, 0B9h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0BAh, 00h, 00h, 00h, 88h, 84h, 24h, 0BBh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0BCh, 00h, 00h, 00h, 88h, 84h, 24h, 0BDh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0BEh, 00h, 00h, 00h, 88h, 84h, 24h, 0BFh, 00h, 00h, 00h, 88h, 84h, 24h, 0C0h
    db 00h, 00h, 00h, 88h, 84h, 24h, 0C1h, 00h, 00h, 00h, 88h, 84h, 24h, 0C2h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0C3h, 00h, 00h, 00h, 88h, 84h, 24h, 0C4h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0C5h, 00h, 00h, 00h, 88h, 84h, 24h, 0C6h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0C7h, 00h, 00h, 00h, 88h, 84h, 24h, 0C8h, 00h, 00h, 00h, 88h, 84h, 24h, 0C9h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0CAh, 00h, 00h, 00h, 88h, 84h, 24h, 0CBh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0CCh, 00h, 00h, 00h, 88h, 84h, 24h, 0CDh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0CEh, 00h, 00h, 00h, 88h, 84h, 24h, 0CFh, 00h, 00h, 00h, 88h, 84h, 24h, 0D0h
    db 00h, 00h, 00h, 88h, 84h, 24h, 0D1h, 00h, 00h, 00h, 88h, 84h, 24h, 0D2h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0D3h, 00h, 00h, 00h, 88h, 84h, 24h, 0D4h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0D5h, 00h, 00h, 00h, 88h, 84h, 24h, 0D6h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0D7h, 00h, 00h, 00h, 88h, 84h, 24h, 0D8h, 00h, 00h, 00h, 88h, 84h, 24h, 0D9h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0DAh, 00h, 00h, 00h, 88h, 84h, 24h, 0DBh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0DCh, 00h, 00h, 00h, 88h, 84h, 24h, 0DDh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0DEh, 00h, 00h, 00h, 88h, 84h, 24h, 0DFh, 00h, 00h, 00h, 88h, 84h, 24h, 0E0h
    db 00h, 00h, 00h, 88h, 84h, 24h, 0E1h, 00h, 00h, 00h, 88h, 84h, 24h, 0E2h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0E3h, 00h, 00h, 00h, 88h, 84h, 24h, 0E4h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0E5h, 00h, 00h, 00h, 88h, 84h, 24h, 0E6h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0E7h, 00h, 00h, 00h, 88h, 84h, 24h, 0E8h, 00h, 00h, 00h, 88h, 84h, 24h, 0E9h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0EAh, 00h, 00h, 00h, 88h, 84h, 24h, 0EBh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0ECh, 00h, 00h, 00h, 88h, 84h, 24h, 0EDh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0EEh, 00h, 00h, 00h, 88h, 84h, 24h, 0EFh, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 08h
    db 01h, 00h, 00h, 88h, 84h, 24h, 0F0h, 00h, 00h, 00h, 88h, 84h, 24h, 0F1h, 00h, 00h
    db 00h, 88h, 84h, 24h, 0F2h, 00h, 00h, 00h, 88h, 84h, 24h, 0F3h, 00h, 00h, 00h, 88h
    db 84h, 24h, 0F4h, 00h, 00h, 00h, 88h, 84h, 24h, 0F5h, 00h, 00h, 00h, 88h, 84h, 24h
    db 0F6h, 00h, 00h, 00h, 88h, 84h, 24h, 0F7h, 00h, 00h, 00h, 88h, 84h, 24h, 0F8h, 00h
    db 00h, 00h, 88h, 84h, 24h, 0F9h, 00h, 00h, 00h, 88h, 84h, 24h, 0FAh, 00h, 00h, 00h
    db 88h, 84h, 24h, 0FBh, 00h, 00h, 00h, 88h, 84h, 24h, 0FCh, 00h, 00h, 00h, 88h, 84h
    db 24h, 0FDh, 00h, 00h, 00h, 88h, 84h, 24h, 0FEh, 00h, 00h, 00h, 88h, 84h, 24h, 0FFh
    db 00h, 00h, 00h, 8Bh, 84h, 24h, 04h, 01h, 00h, 00h, 0Fh, 0B6h, 54h, 08h, 0FFh, 0Fh
    db 0B6h, 00h, 0Fh, 0B6h, 14h, 14h, 0Fh, 0B6h, 04h, 04h, 03h, 0D1h, 03h, 0C2h, 81h, 0C4h
    db 00h, 01h, 00h, 00h, 0C3h
?d_008a9150@@YAXXZ ENDP
_TEXT ENDS
END
