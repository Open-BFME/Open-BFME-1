.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0Rva008A9B00@@QAE@XZ:NEAR
EXTERN ??0Rva89ACB0Holder@@QAE@PAVBfmeHeld99CB0@@@Z:NEAR
EXTERN ??0Rva8CBC80Derived@@QAE@XZ:NEAR
EXTERN ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA:BYTE
EXTERN ?Rva008A30A0ReleasePtr@@3P6AXPAX@ZA:BYTE
EXTERN ?Rva008A5380Holder@@3PADA:BYTE
EXTERN ?Rva008C3B60Head@@3PAURva008C3B60Node@@A:BYTE
EXTERN ?Rva008C4890@@YAPAXI@Z:NEAR
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?append@Rva008B2EA0Node@@QAEXPAX@Z:NEAR
EXTERN ?bfmeAt@Gen_008B8E50@@QBEHH@Z:NEAR
EXTERN ?bfmeGo937E@BfmeThing937E@@QAEXPAVBfmeItem937E@@@Z:NEAR
EXTERN ?bfmePop1232@BfmeA1232@@QAEXH@Z:NEAR
EXTERN ?bfmePopN@BfmeStackBB@@QAEXH@Z:NEAR
EXTERN ?bfmePush@@YAXPAVBfmeItemDX@@@Z:NEAR
EXTERN ?bfmeQuery1279@BfmeQuery1279@@QAEXPAXHPAPAX1@Z:NEAR
EXTERN ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z:NEAR
EXTERN ?bfmeSubmit1283@BfmeSubmitter1283@@QAEXHHHHHHHPAMHHHH@Z:NEAR
EXTERN ?bfmeTheCBC@@3HA:BYTE
EXTERN ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z:NEAR
EXTERN ?bfmeValue@Gen_008C41D0@@QBEHXZ:NEAR
EXTERN ?d_0089c290@@YAXXZ:NEAR
EXTERN ?d_0089cef0@@YAXXZ:NEAR
EXTERN ?d_0089d890@@YAXXZ:NEAR
EXTERN ?d_008a18c0@@YAXXZ:NEAR
EXTERN ?d_008a30c0@@YAXXZ:NEAR
EXTERN ?d_008c6460@@YAXXZ:NEAR
EXTERN ?g_Va01338710String@@3VBfmeStrVKI@@A:BYTE
EXTERN ?g_Va013387D8@@3PAURva00899C20Registry@@A:BYTE
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?g_bfmeSlot13VB@@3P6AXXZA:BYTE
EXTERN ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z:NEAR
EXTERN ?isKind13@Rva008A0F20Header@@QBEHXZ:NEAR
EXTERN ?ji_009f6fa0@@YAXXZ:NEAR
EXTERN ?rva00899C20@Rva00899C20Node@@QAEHXZ:NEAR
EXTERN ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z:NEAR
EXTERN ?rva8CCCE0ResolveValue@@YAXPAX0PAVRva8CCCE0Value@@PAPAV1@@Z:NEAR
EXTERN ?toInteger@AptValue@@QBEHXZ:NEAR
EXTERN g_Va0105A138:NEAR
EXTERN g_Va0105A167:NEAR
EXTERN g_Va0105A287:NEAR
EXTERN g_Va0105A427:NEAR
EXTERN g_Va0105A498:NEAR
EXTERN g_Va0105A50E:NEAR
EXTERN g_Va0105A628:NEAR
EXTERN g_Va0105A698:NEAR
EXTERN g_Va01132714:BYTE
EXTERN g_Va01135E30:BYTE
EXTERN g_Va01135EB4:BYTE
EXTERN g_Va01135EC4:BYTE
EXTERN g_Va01136D44:BYTE
EXTERN g_Va01136D54:BYTE
EXTERN g_Va0113730C:BYTE
EXTERN g_Va01137314:BYTE
EXTERN g_Va012D5A68:BYTE
EXTERN g_Va013378C4:BYTE
EXTERN g_Va013379C0:BYTE
EXTERN g_Va013379F4:BYTE
EXTERN g_Va01338700:BYTE
_TEXT SEGMENT

; ghidra: FUN_00ccb600  retail @ 0x008CB600 size 101
public ?d_008cb600@@YAXXZ
?d_008cb600@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 50h, 04h, 81h, 0E2h, 08h, 80h, 00h, 0F0h, 53h, 81h, 0CAh, 08h, 80h
    db 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h, 89h, 50h, 04h, 56h, 8Bh, 35h, 10h, 78h
    db 33h, 01h, 8Bh, 1Eh, 8Dh, 4Eh, 04h, 57h, 8Bh, 39h, 3Bh, 0FBh, 7Ch, 1Ch, 8Bh, 4Ch
    db 24h, 10h, 5Fh, 81h, 0E2h, 0FFh, 0FFh, 0FFh, 0BFh, 5Eh, 89h, 50h, 04h, 0C7h, 00h, 40h
    db 71h, 13h, 01h, 89h, 48h, 08h, 5Bh, 0C2h, 04h, 00h, 8Bh, 56h, 08h, 89h, 04h, 0BAh
    db 0FFh, 01h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 0C7h, 00h, 40h, 71h, 13h, 01h, 89h, 48h
    db 08h, 5Bh, 0C2h, 04h, 00h
?d_008cb600@@YAXXZ ENDP

; ghidra: FUN_00ccb690  retail @ 0x008CB690 size 33
public ?d_008cb690@@YAXXZ
?d_008cb690@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 0Ch, 6Ah
    db 0Ch, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh, 0C2h, 04h
    db 00h
?d_008cb690@@YAXXZ ENDP

; ghidra: FUN_00ccb6d0  retail @ 0x008CB6D0 size 87
public ?d_008cb6d0@@YAXXZ
?d_008cb6d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 9Fh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 6Ah, 08h, 8Bh, 0F1h, 6Ah, 2Ah, 89h, 74h
    db 24h, 10h, 0E8h, 09h, 0E8h, 0FCh, 0FFh, 8Bh, 7Ch, 24h, 1Ch, 0C7h, 06h, 80h, 71h, 13h
    db 01h, 8Bh, 07h, 8Bh, 0CFh, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0FFh, 10h, 8Bh
    db 4Ch, 24h, 0Ch, 89h, 7Eh, 20h, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_008cb6d0@@YAXXZ ENDP

; ghidra: FUN_00ccb730  retail @ 0x008CB730 size 42
public ?d_008cb730@@YAXXZ
?d_008cb730@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 8Bh, 0F1h, 8Bh, 4Eh, 20h
    db 8Bh, 01h, 57h, 53h, 0FFh, 50h, 28h, 85h, 0C0h, 75h, 09h, 57h, 53h, 8Bh, 0CEh, 0E8h
    db 4Ch, 91h, 0FDh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 08h, 00h
?d_008cb730@@YAXXZ ENDP

; ghidra: FUN_00ccb760  retail @ 0x008CB760 size 42
public ?d_008cb760@@YAXXZ
?d_008cb760@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 0BBh, 0BBh, 0FCh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 2Ch, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008cb760@@YAXXZ ENDP

; ghidra: FUN_00ccb790  retail @ 0x008CB790 size 129
public ?d_008cb790@@YAXXZ
?d_008cb790@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0EBh, 9Fh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 80h
    db 71h, 13h, 01h, 8Bh, 4Eh, 20h, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 74h, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h, 46h, 20h, 00h, 00h, 00h, 00h, 0C7h, 06h
    db 58h, 60h, 13h, 01h, 6Ah, 00h, 6Ah, 00h, 8Bh, 0CEh, 0C7h, 44h, 24h, 18h, 02h, 00h
    db 00h, 00h, 0E8h, 0E9h, 0BDh, 0FCh, 0FFh, 8Dh, 4Eh, 08h, 0C7h, 46h, 18h, 00h, 00h, 00h
    db 00h, 0C6h, 44h, 24h, 10h, 01h, 0E8h, 75h, 14h, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h
    db 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C3h
?d_008cb790@@YAXXZ ENDP

; ghidra: FUN_00ccb820  retail @ 0x008CB820 size 145
public ?d_008cb820@@YAXXZ
?d_008cb820@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 08h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 08h, 8Bh, 0F1h, 6Ah, 24h, 89h, 74h, 24h
    db 0Ch, 0E8h, 0BAh, 0E6h, 0FCh, 0FFh, 8Bh, 44h, 24h, 48h, 8Bh, 4Ch, 24h, 44h, 8Bh, 54h
    db 24h, 40h, 50h, 8Bh, 44h, 24h, 40h, 51h, 8Bh, 4Ch, 24h, 40h, 52h, 8Bh, 54h, 24h
    db 40h, 50h, 8Bh, 44h, 24h, 40h, 51h, 8Bh, 4Ch, 24h, 40h, 52h, 8Bh, 54h, 24h, 40h
    db 50h, 8Bh, 44h, 24h, 40h, 51h, 8Bh, 4Ch, 24h, 40h, 52h, 8Bh, 54h, 24h, 40h, 50h
    db 8Bh, 44h, 24h, 40h, 51h, 52h, 50h, 8Dh, 4Eh, 20h, 0C7h, 44h, 24h, 44h, 00h, 00h
    db 00h, 00h, 0E8h, 69h, 18h, 0FEh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 69h, 13h
    db 01h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 34h
    db 00h
?d_008cb820@@YAXXZ ENDP

; ghidra: FUN_00ccb8c0  retail @ 0x008CB8C0 size 304
public ?d_008cb8c0@@YAXXZ
?d_008cb8c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 28h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 6Ah, 08h, 8Bh, 0F1h, 6Ah, 1Dh, 89h
    db 74h, 24h, 14h, 0E8h, 18h, 0E6h, 0FCh, 0FFh, 8Dh, 5Eh, 20h, 6Ah, 01h, 53h, 0C7h, 44h
    db 24h, 20h, 00h, 00h, 00h, 00h, 0C7h, 06h, 0D0h, 71h, 13h, 01h, 0C7h, 46h, 60h, 00h
    db 00h, 00h, 00h, 0FFh, 15h, 0B4h, 78h, 33h, 01h, 8Dh, 6Eh, 40h, 6Ah, 00h, 55h, 0FFh
    db 15h, 0B4h, 78h, 33h, 01h, 8Bh, 4Eh, 30h, 8Bh, 46h, 50h, 83h, 0C4h, 10h, 3Bh, 0C8h
    db 7Fh, 2Eh, 75h, 08h, 8Bh, 56h, 28h, 3Bh, 56h, 48h, 7Fh, 20h, 3Bh, 0C8h, 7Ch, 0Eh
    db 75h, 35h, 8Bh, 56h, 28h, 3Bh, 56h, 48h, 7Dh, 2Dh, 3Bh, 0C8h, 7Dh, 20h, 8Bh, 46h
    db 28h, 2Bh, 46h, 48h, 83h, 0E8h, 18h, 89h, 46h, 60h, 0EBh, 1Bh, 3Bh, 0C8h, 7Eh, 0Eh
    db 8Bh, 46h, 28h, 2Bh, 46h, 48h, 83h, 0C0h, 18h, 89h, 46h, 60h, 0EBh, 09h, 8Bh, 56h
    db 28h, 2Bh, 56h, 48h, 89h, 56h, 60h, 8Bh, 44h, 24h, 20h, 83h, 0F8h, 0FFh, 75h, 03h
    db 8Bh, 46h, 38h, 89h, 46h, 38h, 8Bh, 44h, 24h, 24h, 83h, 0F8h, 0FFh, 75h, 03h, 8Bh
    db 46h, 34h, 89h, 46h, 34h, 8Bh, 44h, 24h, 28h, 83h, 0F8h, 0FFh, 74h, 02h, 8Bh, 0C8h
    db 8Bh, 44h, 24h, 2Ch, 83h, 0F8h, 0FFh, 89h, 4Eh, 30h, 75h, 03h, 8Bh, 46h, 28h, 89h
    db 46h, 28h, 8Bh, 44h, 24h, 30h, 83h, 0F8h, 0FFh, 75h, 03h, 8Bh, 46h, 24h, 89h, 46h
    db 24h, 8Bh, 44h, 24h, 34h, 83h, 0F8h, 0FFh, 75h, 02h, 8Bh, 03h, 89h, 03h, 8Bh, 44h
    db 24h, 38h, 83h, 0F8h, 0FFh, 75h, 03h, 8Bh, 46h, 3Ch, 89h, 46h, 3Ch, 8Bh, 46h, 60h
    db 50h, 55h, 53h, 8Bh, 0CEh, 0E8h, 06h, 0ACh, 0FEh, 0FFh, 8Bh, 4Ch, 24h, 10h, 8Bh, 0C6h
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 1Ch, 00h
?d_008cb8c0@@YAXXZ ENDP

; ghidra: FUN_00ccb9f0  retail @ 0x008CB9F0 size 42
public ?d_008cb9f0@@YAXXZ
?d_008cb9f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 2Bh, 0B9h, 0FCh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 6Ch, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008cb9f0@@YAXXZ ENDP

; ghidra: FUN_00ccba20  retail @ 0x008CBA20 size 94
public ?d_008cba20@@YAXXZ
?d_008cba20@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 53h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 58h
    db 60h, 13h, 01h, 6Ah, 00h, 6Ah, 00h, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 0E8h
    db 7Ch, 0BBh, 0FCh, 0FFh, 8Dh, 4Eh, 08h, 0C7h, 46h, 18h, 00h, 00h, 00h, 00h, 0C6h, 44h
    db 24h, 10h, 00h, 0E8h, 08h, 12h, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh
    db 13h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cba20@@YAXXZ ENDP

; ghidra: FUN_00ccba80  retail @ 0x008CBA80 size 22
public ?d_008cba80@@YAXXZ
?d_008cba80@@YAXXZ PROC
    db 56h, 6Ah, 08h, 6Ah, 1Eh, 8Bh, 0F1h, 0E8h, 74h, 0E4h, 0FCh, 0FFh, 0C7h, 06h, 20h, 72h
    db 13h, 01h, 8Bh, 0C6h, 5Eh, 0C3h
?d_008cba80@@YAXXZ ENDP

; ghidra: FUN_00ccbaa0  retail @ 0x008CBAA0 size 42
public ?d_008cbaa0@@YAXXZ
?d_008cbaa0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 7Bh, 0B8h, 0FCh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 28h, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008cbaa0@@YAXXZ ENDP

; ghidra: FUN_00ccbad0  retail @ 0x008CBAD0 size 94
public ?d_008cbad0@@YAXXZ
?d_008cbad0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 73h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 58h
    db 60h, 13h, 01h, 6Ah, 00h, 6Ah, 00h, 0C7h, 44h, 24h, 18h, 01h, 00h, 00h, 00h, 0E8h
    db 0CCh, 0BAh, 0FCh, 0FFh, 8Dh, 4Eh, 08h, 0C7h, 46h, 18h, 00h, 00h, 00h, 00h, 0C6h, 44h
    db 24h, 10h, 00h, 0E8h, 58h, 11h, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh
    db 13h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cbad0@@YAXXZ ENDP

; ghidra: FUN_00ccbb30  retail @ 0x008CBB30 size 29
public ?d_008cbb30@@YAXXZ
?d_008cbb30@@YAXXZ PROC
    db 56h, 6Ah, 08h, 6Ah, 23h, 8Bh, 0F1h, 0E8h, 0C4h, 0E3h, 0FCh, 0FFh, 0C7h, 06h, 70h, 72h
    db 13h, 01h, 0C7h, 46h, 20h, 00h, 00h, 00h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_008cbb30@@YAXXZ ENDP

; ghidra: FUN_00ccbb50  retail @ 0x008CBB50 size 42
public ?d_008cbb50@@YAXXZ
?d_008cbb50@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 0A8h, 99h, 0FDh, 0FFh, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 0CBh, 0B7h, 0FCh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 2Ch, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008cbb50@@YAXXZ ENDP

; ghidra: FUN_00ccbb80  retail @ 0x008CBB80 size 101
public ?d_008cbb80@@YAXXZ
?d_008cbb80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 93h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 08h, 8Bh, 0F1h, 6Ah, 29h, 89h, 74h, 24h
    db 0Ch, 0E8h, 5Ah, 0E3h, 0FCh, 0FFh, 8Dh, 4Eh, 20h, 68h, 0B4h, 6Fh, 13h, 01h, 0C7h, 44h
    db 24h, 14h, 00h, 00h, 00h, 00h, 0C7h, 06h, 0E0h, 66h, 13h, 01h, 0E8h, 0BFh, 2Ah, 0FDh
    db 0FFh, 68h, 0B4h, 6Fh, 13h, 01h, 8Dh, 4Eh, 24h, 0C6h, 44h, 24h, 14h, 01h, 0E8h, 0ADh
    db 2Ah, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
?d_008cbb80@@YAXXZ ENDP

; ghidra: FUN_00ccbbf0  retail @ 0x008CBBF0 size 131
public ?d_008cbbf0@@YAXXZ
?d_008cbbf0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BBh, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 08h, 6Ah, 08h
    db 6Ah, 29h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 0E1h, 0E2h, 0FCh, 0FFh, 8Bh
    db 74h, 24h, 1Ch, 0C7h, 07h, 0E0h, 66h, 13h, 01h, 89h, 77h, 20h, 66h, 0FFh, 06h, 8Dh
    db 4Fh, 24h, 68h, 0B4h, 6Fh, 13h, 01h, 0C6h, 44h, 24h, 18h, 02h, 0E8h, 3Fh, 2Ah, 0FDh
    db 0FFh, 66h, 0FFh, 0Eh, 66h, 83h, 3Eh, 00h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh
    db 75h, 0Ch, 0A1h, 30h, 7Ah, 33h, 01h, 56h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch
    db 24h, 0Ch, 8Bh, 0C7h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C2h, 04h, 00h
?d_008cbbf0@@YAXXZ ENDP

; ghidra: FUN_00ccbc80  retail @ 0x008CBC80 size 132
public ?d_008cbc80@@YAXXZ
?d_008cbc80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 25h, 14h, 80h
    db 00h, 0F0h, 0Dh, 14h, 80h, 00h, 40h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 89h, 46h, 04h
    db 8Bh, 15h, 10h, 78h, 33h, 01h, 8Bh, 1Ah, 8Dh, 4Ah, 04h, 57h, 8Bh, 39h, 3Bh, 0FBh
    db 89h, 74h, 24h, 0Ch, 7Ch, 0Ah, 25h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 46h, 04h, 0EBh, 08h
    db 8Bh, 42h, 08h, 89h, 34h, 0B8h, 0FFh, 01h, 6Ah, 04h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h
    db 1Ch, 00h, 00h, 00h, 00h, 0C7h, 06h, 0C0h, 72h, 13h, 01h, 0E8h, 70h, 0Bh, 0FDh, 0FFh
    db 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_008cbc80@@YAXXZ ENDP

; ghidra: FUN_00ccbd70  retail @ 0x008CBD70 size 42
public ?d_008cbd70@@YAXXZ
?d_008cbd70@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 28h, 00h, 00h, 00h, 0F6h, 44h, 24h, 08h, 01h, 74h, 15h, 56h
    db 0E8h, 0ABh, 0B5h, 0FCh, 0FFh, 8Dh, 46h, 0F8h, 6Ah, 20h, 50h, 0FFh, 15h, 30h, 78h, 33h
    db 01h, 83h, 0C4h, 0Ch, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008cbd70@@YAXXZ ENDP

; ghidra: FUN_00ccbda0  retail @ 0x008CBDA0 size 73
public ?d_008cbda0@@YAXXZ
?d_008cbda0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 0A0h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0C0h
    db 72h, 13h, 01h, 8Dh, 4Eh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 9Dh
    db 0Eh, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cbda0@@YAXXZ ENDP

; ghidra: FUN_00ccbdf0  retail @ 0x008CBDF0 size 1757
public ?d_008cbdf0@@YAXXZ
?d_008cbdf0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 8Bh, 54h, 24h, 18h, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 33h, 0C0h, 85h
    db 0D2h, 0Fh, 94h, 0C0h, 55h, 56h, 8Bh, 0F0h, 89h, 74h, 24h, 10h, 0E8h, 0AFh, 72h, 0FDh
    db 0FFh, 8Bh, 4Ch, 24h, 18h, 0Fh, 0B6h, 01h, 85h, 0C0h, 8Dh, 69h, 01h, 0Fh, 84h, 0A4h
    db 06h, 00h, 00h, 53h, 57h, 0EBh, 04h, 8Bh, 74h, 24h, 18h, 8Bh, 7Ch, 24h, 24h, 05h
    db 7Fh, 0FFh, 0FFh, 0FFh, 83h, 0F8h, 37h, 0BBh, 78h, 56h, 34h, 12h, 0Fh, 87h, 6Bh, 06h
    db 00h, 00h, 0Fh, 0B6h, 88h, 00h, 0C5h, 0CCh, 00h, 0FFh, 24h, 8Dh, 0D0h, 0C4h, 0CCh, 00h
    db 45h, 0E9h, 57h, 06h, 00h, 00h, 83h, 0C5h, 02h, 0E9h, 4Fh, 06h, 00h, 00h, 83h, 0C5h
    db 03h, 83h, 0E5h, 0FCh, 8Bh, 0DDh, 83h, 0C5h, 08h, 85h, 0F6h, 89h, 5Ch, 24h, 20h, 0Fh
    db 85h, 81h, 00h, 00h, 00h, 8Bh, 43h, 04h, 85h, 0C0h, 74h, 05h, 03h, 0C7h, 89h, 43h
    db 04h, 83h, 3Bh, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0Fh, 8Eh, 1Bh, 06h
    db 00h, 00h, 8Bh, 7Ch, 24h, 28h, 8Bh, 4Bh, 04h, 8Bh, 54h, 24h, 10h, 8Bh, 34h, 91h
    db 8Bh, 44h, 24h, 2Ch, 0FFh, 00h, 8Bh, 47h, 1Ch, 8Bh, 0Ch, 0F0h, 8Dh, 14h, 0F0h, 33h
    db 0C0h, 83h, 0F9h, 01h, 0Fh, 85h, 0C9h, 00h, 00h, 00h, 8Bh, 42h, 04h, 85h, 0C0h, 74h
    db 09h, 8Bh, 4Fh, 1Ch, 8Dh, 44h, 0F1h, 04h, 01h, 38h, 8Bh, 57h, 1Ch, 8Bh, 44h, 0F2h
    db 04h, 50h, 0E8h, 29h, 7Dh, 0FFh, 0FFh, 8Bh, 4Fh, 1Ch, 8Bh, 54h, 0F1h, 04h, 83h, 0C4h
    db 04h, 85h, 0D2h, 0Fh, 84h, 9Bh, 03h, 00h, 00h, 8Bh, 0D1h, 8Dh, 4Ch, 0F2h, 04h, 29h
    db 39h, 0E9h, 8Eh, 03h, 00h, 00h, 8Bh, 03h, 33h, 0FFh, 85h, 0C0h, 7Eh, 6Eh, 8Bh, 0FFh
    db 8Bh, 53h, 04h, 8Bh, 0Ch, 0BAh, 8Bh, 71h, 04h, 8Bh, 0C6h, 83h, 0E0h, 3Fh, 83h, 0F8h
    db 01h, 74h, 05h, 83h, 0F8h, 2Ah, 75h, 1Fh, 8Bh, 0D6h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h
    db 0C2h, 01h, 75h, 13h, 83h, 0F8h, 01h, 74h, 03h, 8Bh, 49h, 20h, 51h, 0E8h, 0BEh, 7Bh
    db 0FFh, 0FFh, 83h, 0C4h, 04h, 0EBh, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 44h, 24h, 2Ch
    db 8Bh, 10h, 8Bh, 4Bh, 04h, 89h, 14h, 0B9h, 0FFh, 00h, 8Bh, 0C7h, 25h, 0Fh, 00h, 00h
    db 80h, 79h, 05h, 48h, 83h, 0C8h, 0F0h, 40h, 75h, 0Bh, 8Bh, 0Dh, 10h, 78h, 33h, 01h
    db 0E8h, 5Bh, 71h, 0FDh, 0FFh, 8Bh, 03h, 47h, 3Bh, 0F8h, 7Ch, 94h, 8Bh, 43h, 04h, 85h
    db 0C0h, 0Fh, 84h, 36h, 05h, 00h, 00h, 2Bh, 44h, 24h, 24h, 89h, 43h, 04h, 0E9h, 2Ah
    db 05h, 00h, 00h, 83h, 0F9h, 06h, 0Fh, 85h, 0D2h, 00h, 00h, 00h, 8Bh, 42h, 04h, 89h
    db 44h, 24h, 14h, 0A1h, 0CCh, 87h, 33h, 01h, 85h, 0C0h, 74h, 40h, 8Bh, 48h, 08h, 8Bh
    db 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0CCh, 87h, 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h
    db 8Dh, 4Ah, 04h, 7Ch, 13h, 81h, 60h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 8Bh, 4Ch, 24h, 14h
    db 89h, 48h, 08h, 0E9h, 0BCh, 02h, 00h, 00h, 8Bh, 52h, 08h, 89h, 04h, 0B2h, 0FFh, 01h
    db 8Bh, 4Ch, 24h, 14h, 89h, 48h, 08h, 0E9h, 0A8h, 02h, 00h, 00h, 6Ah, 0Ch, 0FFh, 15h
    db 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 68h, 8Bh, 48h, 04h, 81h, 0E1h
    db 06h, 80h, 00h, 0F0h, 81h, 0C9h, 06h, 80h, 00h, 40h, 0C7h, 00h, 68h, 5Dh, 13h, 01h
    db 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h, 3Bh, 3Eh, 8Dh, 56h
    db 04h, 7Ch, 1Fh, 8Bh, 54h, 24h, 14h, 8Bh, 7Ch, 24h, 28h, 81h, 0E1h, 0FFh, 0FFh, 0FFh
    db 0BFh, 89h, 48h, 04h, 0C7h, 00h, 98h, 66h, 13h, 01h, 89h, 50h, 08h, 0E9h, 52h, 02h
    db 00h, 00h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 8Bh, 0Ah, 8Bh, 7Ch, 24h, 28h, 41h, 89h
    db 0Ah, 8Bh, 54h, 24h, 14h, 0C7h, 00h, 98h, 66h, 13h, 01h, 89h, 50h, 08h, 0E9h, 31h
    db 02h, 00h, 00h, 8Bh, 7Ch, 24h, 28h, 33h, 0C0h, 0E9h, 26h, 02h, 00h, 00h, 83h, 0F9h
    db 07h, 0Fh, 85h, 0DFh, 00h, 00h, 00h, 0A1h, 0D0h, 87h, 33h, 01h, 85h, 0C0h, 8Bh, 5Ah
    db 04h, 74h, 4Dh, 8Bh, 48h, 08h, 8Bh, 15h, 10h, 78h, 33h, 01h, 89h, 0Dh, 0D0h, 87h
    db 33h, 01h, 8Bh, 72h, 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Ch, 8Bh, 48h, 04h, 8Bh
    db 7Ch, 24h, 28h, 81h, 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 89h, 58h, 08h, 8Bh, 5Ch, 24h, 20h
    db 89h, 48h, 04h, 0E9h, 0DCh, 01h, 00h, 00h, 8Bh, 52h, 08h, 8Bh, 7Ch, 24h, 28h, 89h
    db 04h, 0B2h, 0FFh, 01h, 89h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 0E9h, 0C4h, 01h, 00h, 00h
    db 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 68h, 8Bh
    db 48h, 04h, 81h, 0E1h, 07h, 80h, 00h, 0F0h, 81h, 0C9h, 07h, 80h, 00h, 40h, 0C7h, 00h
    db 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h
    db 3Bh, 3Eh, 8Dh, 56h, 04h, 7Ch, 1Fh, 8Bh, 7Ch, 24h, 28h, 81h, 0E1h, 0FFh, 0FFh, 0FFh
    db 0BFh, 89h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 89h, 48h, 04h, 0C7h, 00h, 00h, 64h, 13h
    db 01h, 0E9h, 6Eh, 01h, 00h, 00h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 8Bh, 0Ah, 8Bh, 7Ch
    db 24h, 28h, 41h, 89h, 0Ah, 89h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 0C7h, 00h, 00h, 64h
    db 13h, 01h, 0E9h, 4Dh, 01h, 00h, 00h, 8Bh, 5Ch, 24h, 20h, 8Bh, 7Ch, 24h, 28h, 33h
    db 0C0h, 0E9h, 3Eh, 01h, 00h, 00h, 83h, 0F9h, 08h, 75h, 2Ah, 6Ah, 0Ch, 0FFh, 15h, 28h
    db 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 14h, 8Bh, 57h, 1Ch, 8Bh, 4Ch, 0F2h
    db 04h, 51h, 8Bh, 0C8h, 0E8h, 97h, 0F4h, 0FFh, 0FFh, 0E9h, 16h, 01h, 00h, 00h, 33h, 0C0h
    db 0E9h, 0Fh, 01h, 00h, 00h, 83h, 0F9h, 05h, 0Fh, 85h, 0D3h, 00h, 00h, 00h, 8Bh, 72h
    db 04h, 0A1h, 0D4h, 87h, 33h, 01h, 85h, 0F6h, 0Fh, 95h, 0C3h, 85h, 0C0h, 74h, 4Dh, 8Bh
    db 50h, 08h, 89h, 15h, 0D4h, 87h, 33h, 01h, 8Bh, 15h, 10h, 78h, 33h, 01h, 8Bh, 72h
    db 04h, 3Bh, 32h, 8Dh, 4Ah, 04h, 7Ch, 1Ch, 8Bh, 48h, 04h, 8Bh, 7Ch, 24h, 28h, 81h
    db 0E1h, 0FFh, 0FFh, 0FFh, 0BFh, 88h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 89h, 48h, 04h, 0E9h
    db 0C0h, 00h, 00h, 00h, 8Bh, 52h, 08h, 8Bh, 7Ch, 24h, 28h, 89h, 04h, 0B2h, 0FFh, 01h
    db 88h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 0E9h, 0A8h, 00h, 00h, 00h, 6Ah, 0Ch, 0FFh, 15h
    db 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 48h, 0FFh, 0FFh, 0FFh, 8Bh
    db 48h, 04h, 81h, 0E1h, 05h, 80h, 00h, 0F0h, 81h, 0C9h, 05h, 80h, 00h, 40h, 0C7h, 00h
    db 68h, 5Dh, 13h, 01h, 89h, 48h, 04h, 8Bh, 35h, 10h, 78h, 33h, 01h, 8Bh, 7Eh, 04h
    db 3Bh, 3Eh, 8Dh, 56h, 04h, 7Ch, 1Ch, 8Bh, 7Ch, 24h, 28h, 81h, 0E1h, 0FFh, 0FFh, 0FFh
    db 0BFh, 88h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 89h, 48h, 04h, 0C7h, 00h, 0A8h, 60h, 13h
    db 01h, 0EBh, 51h, 8Bh, 4Eh, 08h, 89h, 04h, 0B9h, 8Bh, 0Ah, 8Bh, 7Ch, 24h, 28h, 41h
    db 89h, 0Ah, 88h, 58h, 08h, 8Bh, 5Ch, 24h, 20h, 0C7h, 00h, 0A8h, 60h, 13h, 01h, 0EBh
    db 33h, 83h, 0F9h, 04h, 75h, 24h, 6Ah, 0Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h
    db 04h, 85h, 0C0h, 0Fh, 84h, 05h, 0FFh, 0FFh, 0FFh, 8Bh, 57h, 1Ch, 8Bh, 4Ch, 0F2h, 04h
    db 51h, 8Bh, 0C8h, 0E8h, 0B8h, 0F2h, 0FFh, 0FFh, 0EBh, 0Ah, 83h, 0F9h, 03h, 75h, 05h, 0A1h
    db 0BCh, 79h, 33h, 01h, 8Bh, 53h, 04h, 8Bh, 74h, 24h, 10h, 89h, 04h, 0B2h, 8Bh, 50h
    db 04h, 8Bh, 0CAh, 83h, 0E1h, 3Fh, 83h, 0F9h, 01h, 74h, 05h, 83h, 0F9h, 2Ah, 75h, 0Ah
    db 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 74h, 06h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 12h
    db 8Bh, 0C6h, 25h, 0Fh, 00h, 00h, 80h, 79h, 05h, 48h, 83h, 0C8h, 0F0h, 40h, 75h, 0Bh
    db 8Bh, 0Dh, 10h, 78h, 33h, 01h, 0E8h, 0F5h, 6Dh, 0FDh, 0FFh, 8Bh, 03h, 46h, 3Bh, 0F0h
    db 89h, 74h, 24h, 10h, 0Fh, 8Ch, 0BCh, 0FBh, 0FFh, 0FFh, 0E9h, 0CEh, 01h, 00h, 00h, 83h
    db 0C5h, 03h, 83h, 0E5h, 0FCh, 8Bh, 0C5h, 8Bh, 08h, 83h, 0C5h, 08h, 85h, 0F6h, 74h, 1Dh
    db 85h, 0C9h, 74h, 04h, 2Bh, 0CFh, 89h, 08h, 8Bh, 48h, 04h, 85h, 0C9h, 0Fh, 84h, 0AAh
    db 01h, 00h, 00h, 2Bh, 0CFh, 89h, 48h, 04h, 0E9h, 0A0h, 01h, 00h, 00h, 85h, 0C9h, 74h
    db 04h, 03h, 0CFh, 89h, 08h, 8Bh, 48h, 04h, 85h, 0C9h, 0Fh, 84h, 8Dh, 01h, 00h, 00h
    db 03h, 0CFh, 89h, 48h, 04h, 0E9h, 83h, 01h, 00h, 00h, 83h, 0C5h, 03h, 83h, 0E5h, 0FCh
    db 8Bh, 0C5h, 8Bh, 08h, 83h, 0C5h, 04h, 85h, 0F6h, 74h, 11h, 85h, 0C9h, 0Fh, 84h, 6Ah
    db 01h, 00h, 00h, 2Bh, 0CFh, 89h, 08h, 0E9h, 61h, 01h, 00h, 00h, 85h, 0C9h, 0Fh, 84h
    db 59h, 01h, 00h, 00h, 03h, 0CFh, 89h, 08h, 0E9h, 50h, 01h, 00h, 00h, 83h, 0C5h, 03h
    db 83h, 0E5h, 0FCh, 8Bh, 0C5h, 8Bh, 08h, 83h, 0C5h, 18h, 85h, 0F6h, 74h, 0Ah, 85h, 0C9h
    db 74h, 1Ah, 2Bh, 0CFh, 89h, 08h, 0EBh, 14h, 85h, 0C9h, 74h, 04h, 03h, 0CFh, 89h, 08h
    db 8Bh, 48h, 08h, 85h, 0C9h, 74h, 05h, 03h, 0CFh, 89h, 48h, 08h, 8Bh, 48h, 04h, 33h
    db 0D2h, 85h, 0C9h, 7Eh, 22h, 85h, 0F6h, 8Bh, 48h, 08h, 8Dh, 0Ch, 91h, 74h, 09h, 83h
    db 39h, 00h, 74h, 0Bh, 29h, 39h, 0EBh, 07h, 83h, 39h, 00h, 74h, 02h, 01h, 39h, 8Bh
    db 48h, 04h, 42h, 3Bh, 0D1h, 7Ch, 0DEh, 85h, 0F6h, 0Fh, 84h, 0EEh, 00h, 00h, 00h, 8Bh
    db 48h, 08h, 85h, 0C9h, 74h, 05h, 2Bh, 0CFh, 89h, 48h, 08h, 0C7h, 40h, 10h, 32h, 54h
    db 76h, 98h, 89h, 58h, 14h, 0E9h, 0D3h, 00h, 00h, 00h, 83h, 0C5h, 03h, 83h, 0E5h, 0FCh
    db 83h, 0C5h, 04h, 0E9h, 0C5h, 00h, 00h, 00h, 83h, 0C5h, 03h, 83h, 0E5h, 0FCh, 8Bh, 0C5h
    db 8Bh, 08h, 83h, 0C5h, 04h, 85h, 0F6h, 74h, 09h, 2Bh, 0CDh, 89h, 08h, 0E9h, 0ABh, 00h
    db 00h, 00h, 03h, 0CDh, 89h, 08h, 0E9h, 0A2h, 00h, 00h, 00h, 83h, 0C5h, 03h, 83h, 0E5h
    db 0FCh, 8Bh, 0C5h, 8Bh, 08h, 83h, 0C5h, 1Ch, 85h, 0F6h, 74h, 0Ah, 85h, 0C9h, 74h, 1Ah
    db 2Bh, 0CFh, 89h, 08h, 0EBh, 14h, 85h, 0C9h, 74h, 04h, 03h, 0CFh, 89h, 08h, 8Bh, 48h
    db 0Ch, 85h, 0C9h, 74h, 05h, 03h, 0CFh, 89h, 48h, 0Ch, 8Bh, 48h, 04h, 33h, 0D2h, 85h
    db 0C9h, 7Eh, 23h, 85h, 0F6h, 8Bh, 48h, 0Ch, 8Dh, 4Ch, 0D1h, 04h, 74h, 09h, 83h, 39h
    db 00h, 74h, 0Bh, 29h, 39h, 0EBh, 07h, 83h, 39h, 00h, 74h, 02h, 01h, 39h, 8Bh, 48h
    db 04h, 42h, 3Bh, 0D1h, 7Ch, 0DDh, 85h, 0F6h, 74h, 43h, 8Bh, 48h, 0Ch, 85h, 0C9h, 74h
    db 05h, 2Bh, 0CFh, 89h, 48h, 0Ch, 0C7h, 40h, 14h, 32h, 54h, 76h, 98h, 89h, 58h, 18h
    db 0EBh, 2Bh, 83h, 0C5h, 03h, 83h, 0E5h, 0FCh, 8Bh, 0C5h, 8Ah, 48h, 0Ch, 83h, 0C5h, 14h
    db 0F6h, 0C1h, 04h, 75h, 18h, 85h, 0F6h, 8Bh, 48h, 10h, 74h, 08h, 85h, 0C9h, 74h, 0Dh
    db 2Bh, 0CFh, 0EBh, 06h, 85h, 0C9h, 74h, 05h, 03h, 0CFh, 89h, 48h, 10h, 8Bh, 0Dh, 10h
    db 78h, 33h, 01h, 0E8h, 08h, 6Ch, 0FDh, 0FFh, 0Fh, 0B6h, 45h, 00h, 45h, 85h, 0C0h, 0Fh
    db 85h, 62h, 0F9h, 0FFh, 0FFh, 5Fh, 5Bh, 5Eh, 5Dh, 83h, 0C4h, 0Ch, 0C3h
?d_008cbdf0@@YAXXZ ENDP

; ghidra: FUN_00ccc540  retail @ 0x008CC540 size 26
public ?d_008cc540@@YAXXZ
?d_008cc540@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 08h, 8Bh, 54h, 24h, 04h, 50h, 6Ah, 00h, 51h
    db 52h, 0E8h, 9Ah, 0F8h, 0FFh, 0FFh, 83h, 0C4h, 10h, 0C3h
?d_008cc540@@YAXXZ ENDP

; ghidra: FUN_00ccc570  retail @ 0x008CC570 size 280
public ?d_008cc570@@YAXXZ
?d_008cc570@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 18h, 0A1h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 04h, 24h
    db 98h, 52h, 2Dh, 01h, 8Bh, 44h, 24h, 1Ch, 8Bh, 08h, 66h, 83h, 79h, 02h, 00h, 0C7h
    db 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 75h, 35h, 66h, 0FFh, 0Dh, 98h, 52h, 2Dh, 01h
    db 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 11h, 8Bh, 15h, 30h, 7Ah, 33h, 01h
    db 68h, 98h, 52h, 2Dh, 01h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 44h, 24h, 14h, 8Bh
    db 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 56h, 8Bh
    db 74h, 24h, 1Ch, 8Dh, 4Ch, 24h, 04h, 51h, 8Dh, 54h, 24h, 24h, 52h, 50h, 8Bh, 44h
    db 24h, 24h, 56h, 50h, 0E8h, 27h, 9Dh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 34h, 83h, 0C4h, 14h
    db 85h, 0C9h, 74h, 50h, 56h, 8Dh, 54h, 24h, 08h, 52h, 0E8h, 81h, 0FCh, 0FCh, 0FFh, 8Bh
    db 0F0h, 85h, 0F6h, 74h, 3Fh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 24h, 84h, 0C0h, 74h, 34h
    db 8Bh, 44h, 24h, 04h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h, 10h, 0FFh
    db 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h
    db 0C4h, 04h, 8Bh, 0C6h, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h, 8Bh, 44h, 24h, 04h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h
    db 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h
    db 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 33h, 0C0h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cc570@@YAXXZ ENDP

; ghidra: FUN_00ccc690  retail @ 0x008CC690 size 687
_TEXT ENDS
_TEXT$d00ccc690 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCC690 size 687
public ?d_008cc690@@YAXXZ
?d_008cc690@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A138
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 066h
    db 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 053h, 055h, 056h, 057h, 08Bh, 0F9h, 0C7h, 044h, 024h, 010h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Bh, 044h, 024h, 03Ch, 085h, 0C0h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 075h, 02Bh
    db 08Bh, 054h, 024h, 02Ch, 08Dh, 044h, 024h, 010h, 050h, 08Bh, 044h, 024h, 02Ch, 08Dh, 04Ch, 024h
    db 028h, 051h, 08Bh, 04Ch, 024h, 02Ch, 052h, 050h, 051h
    call ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
    db 08Bh, 06Ch, 024h, 024h, 08Bh, 074h, 024h, 038h, 083h, 0C4h, 014h, 0EBh, 02Dh, 08Bh, 05Ch, 024h
    db 02Ch, 08Bh, 003h, 066h, 0FFh, 000h, 08Bh, 044h, 024h, 010h, 066h, 0FFh, 008h, 066h, 083h, 038h
    db 000h, 08Bh, 074h, 024h, 024h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 02Bh, 089h, 06Ch, 024h, 010h, 085h, 0F6h, 074h
    db 023h, 08Bh, 04Eh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch, 04Ch, 083h, 0F8h
    db 013h, 07Fh, 047h, 08Bh, 0D1h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 075h, 03Bh, 083h
    db 0F8h, 00Ch, 075h, 036h, 066h, 0FFh, 04Dh, 000h, 066h, 083h, 07Dh, 000h, 000h, 0C7h, 044h, 024h
    db 01Ch, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Ch, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 055h, 0FFh, 050h, 004h, 083h, 0C4h, 004h, 05Fh, 05Eh, 05Dh, 032h, 0C0h, 05Bh, 08Bh, 04Ch, 024h
    db 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 01Ch, 000h, 08Bh, 06Ch
    db 024h, 030h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 03Ah, 08Bh, 016h, 055h, 08Dh
    db 044h, 024h, 014h, 050h, 056h, 08Bh, 0CEh, 0FFh, 052h, 02Ch, 084h, 0C0h, 074h, 028h, 08Bh, 044h
    db 024h, 010h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 00Fh, 085h, 06Fh, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 0E9h, 05Dh, 001h, 000h, 000h, 08Bh, 044h, 024h, 034h, 085h, 0C0h, 00Fh
    db 084h, 0E6h, 000h, 000h, 000h, 08Bh, 044h, 024h, 038h, 085h, 0C0h, 074h, 025h, 08Bh, 047h, 00Ch
    db 085h, 0C0h, 07Eh, 01Eh, 08Bh, 0D0h, 08Bh, 047h, 014h, 08Bh, 044h, 090h, 0FCh, 08Dh, 04Ch, 024h
    db 010h, 051h, 08Dh, 048h, 008h
    call ?d_0089cef0@@YAXXZ
    db 085h, 0C0h, 00Fh, 085h, 0C0h, 000h, 000h, 000h, 085h, 0EDh, 075h, 007h, 0BFh, 001h, 000h, 000h
    db 000h, 0EBh, 00Dh, 08Bh, 045h, 004h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 083h, 0E0h, 001h, 08Bh, 0F8h
    db 08Dh, 05Ch, 024h, 010h
    call ?d_008c6460@@YAXXZ
    db 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 018h, 085h, 0C0h, 074h, 062h, 055h, 08Bh, 0CBh, 051h, 08Bh
    db 0C8h
    call ?d_0089d890@@YAXXZ
    db 03Bh, 035h
    dd g_Va013379F4
    db 00Fh, 085h, 0C2h, 000h, 000h, 000h, 08Bh, 045h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h, 0FAh
    db 00Ah, 00Fh, 085h, 0B1h, 000h, 000h, 000h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 00Fh, 085h
    db 0A4h, 000h, 000h, 000h, 08Bh, 045h, 000h, 08Bh, 0CDh, 0FFh, 050h, 018h, 08Bh, 048h, 00Ch, 083h
    db 0E1h, 0FEh, 08Bh, 011h, 0FFh, 052h, 018h, 08Bh, 0F0h, 08Bh, 046h, 008h, 083h, 0E0h, 0FEh, 074h
    db 007h, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 052h, 004h, 0C7h, 046h, 008h, 000h, 000h, 000h, 000h, 0EBh
    db 077h, 08Bh, 04Eh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch, 06Ah, 083h, 0F8h
    db 013h, 07Fh, 065h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 05Bh, 083h, 0F8h, 00Eh
    db 075h, 056h, 08Bh, 04Eh, 04Ch
    call ?bfmeValue@Gen_008C41D0@@QBEHXZ
    db 0EBh, 03Bh, 08Bh, 047h, 00Ch, 085h, 0C0h, 07Eh, 015h, 08Bh, 057h, 00Ch, 08Bh, 047h, 014h, 08Bh
    db 044h, 090h, 0FCh, 08Dh, 04Ch, 024h, 010h, 055h, 051h, 08Dh, 048h, 008h, 0EBh, 02Bh, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 033h, 0D2h, 03Bh, 0EFh, 00Fh, 094h, 0C2h, 08Dh, 05Ch, 024h, 010h, 08Bh, 0FAh
    call ?d_008c6460@@YAXXZ
    db 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 018h, 085h, 0C0h, 074h, 00Dh, 08Dh, 04Ch, 024h, 010h, 055h
    db 051h, 08Bh, 0C8h
    call ?d_0089d890@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 01Ch, 0FFh
    db 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 014h, 05Fh, 05Eh, 05Dh, 0B0h, 001h
    db 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 01Ch, 000h
?d_008cc690@@YAXXZ ENDP
_TEXT$d00ccc690 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ccc940  retail @ 0x008CC940 size 917
_TEXT ENDS
_TEXT$d00ccc940 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCC940 size 917
public ?d_008cc940@@YAXXZ
?d_008cc940@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A167
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 008h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 053h, 056h, 057h, 08Bh, 0F9h, 0C7h, 044h, 024h, 010h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Bh, 05Ch, 024h, 02Ch, 08Bh, 003h, 080h, 078h, 008h, 024h, 0C7h, 044h, 024h, 01Ch, 000h, 000h
    db 000h, 000h, 00Fh, 085h, 0CEh, 000h, 000h, 000h, 08Bh, 035h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 085h, 0F6h, 074h, 03Fh, 08Bh, 046h, 00Ch, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 0A3h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 03Bh, 011h, 08Dh, 041h, 004h, 07Ch, 009h, 081h, 066h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 034h, 091h, 0FFh, 000h, 08Bh, 046h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Eh, 008h, 074h, 033h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 02Ah, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 02Ch, 085h, 0C0h, 0C6h, 044h, 024h, 01Ch, 001h, 074h, 009h
    db 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C6h, 044h, 024h, 01Ch, 000h, 08Bh, 0F0h, 08Bh, 003h, 066h, 0FFh, 000h
    db 08Bh, 046h, 008h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 003h, 089h, 046h, 008h, 08Bh, 044h, 024h, 010h
    db 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh, 0FFh, 075h
    db 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 08Bh, 04Ch, 024h, 008h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C2h, 018h, 000h, 08Bh, 04Ch, 024h
    db 038h, 085h, 0C9h, 055h, 08Bh, 06Ch, 024h, 028h, 0C6h, 044h, 024h, 013h, 000h, 075h, 025h, 08Dh
    db 054h, 024h, 014h, 052h, 08Dh, 044h, 024h, 02Ch, 050h, 053h, 08Bh, 05Ch, 024h, 038h, 053h, 055h
    call ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
    db 08Bh, 074h, 024h, 03Ch, 08Ah, 0C8h, 08Bh, 044h, 024h, 028h, 083h, 0C4h, 014h, 0EBh, 02Dh, 066h
    db 0FFh, 000h, 08Bh, 044h, 024h, 014h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 08Bh, 0F5h, 075h
    db 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 003h, 08Bh, 05Ch, 024h, 02Ch, 08Ah, 04Ch, 024h
    db 013h, 089h, 044h, 024h, 014h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 075h, 033h, 085h, 0F6h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 074h, 01Ch, 066h, 0FFh
    db 008h, 066h, 083h, 038h, 000h, 00Fh, 085h, 0E8h, 001h, 000h, 000h, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 0E9h, 0D6h, 001h, 000h, 000h, 08Bh, 035h
    dd ?bfmeTheCBC@@3HA
    db 0E9h, 096h, 001h, 000h, 000h, 080h, 0F9h, 001h, 075h, 058h, 085h, 0F6h, 074h, 054h, 053h, 08Dh
    db 04Ch, 024h, 018h, 051h, 08Bh, 0CEh
    call ?d_0089c290@@YAXXZ
    db 08Bh, 0C8h, 085h, 0C9h, 08Bh, 044h, 024h, 014h, 089h, 04Ch, 024h, 028h, 074h, 039h, 066h, 0FFh
    db 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 011h, 08Bh
    db 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 08Bh, 04Ch, 024h, 02Ch, 083h, 0C4h, 004h, 05Dh, 05Fh, 05Eh, 08Bh, 0C1h
    db 05Bh, 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C2h
    db 018h, 000h, 08Bh, 04Ch, 024h, 038h, 085h, 0C9h, 074h, 05Fh, 08Bh, 04Fh, 00Ch, 085h, 0C9h, 07Eh
    db 058h, 08Bh, 0C1h, 08Bh, 04Fh, 014h, 08Bh, 044h, 081h, 0FCh, 08Dh, 054h, 024h, 014h, 052h, 08Dh
    db 048h, 008h
    call ?d_0089cef0@@YAXXZ
    db 08Bh, 0D8h, 085h, 0DBh, 08Bh, 044h, 024h, 014h, 074h, 034h, 066h, 0FFh, 008h, 066h, 083h, 038h
    db 000h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 05Dh, 05Fh, 05Eh, 08Bh, 0C3h, 05Bh, 08Bh, 04Ch, 024h, 008h
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C2h, 018h, 000h, 08Bh, 05Ch, 024h
    db 02Ch, 085h, 0F6h, 00Fh, 084h, 0A0h, 000h, 000h, 000h, 08Bh, 04Eh, 004h, 0C1h, 0E9h, 00Fh, 0F6h
    db 0D1h, 0F6h, 0C1h, 001h, 00Fh, 085h, 08Fh, 000h, 000h, 000h, 08Bh, 016h, 08Dh, 044h, 024h, 014h
    db 050h, 056h, 08Bh, 0CEh, 0FFh, 052h, 028h, 08Bh, 0C8h, 085h, 0C9h, 089h, 04Ch, 024h, 028h, 074h
    db 041h, 08Bh, 044h, 024h, 014h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 020h
    db 0FFh, 0FFh, 0FFh, 0FFh, 00Fh, 085h, 039h, 0FFh, 0FFh, 0FFh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 08Bh, 04Ch, 024h, 02Ch, 083h, 0C4h, 004h, 05Dh, 05Fh, 05Eh, 08Bh, 0C1h
    db 05Bh, 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C2h
    db 018h, 000h, 053h, 08Dh, 054h, 024h, 018h, 052h, 08Bh, 0CEh
    call ?d_0089c290@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 075h, 042h, 085h, 0DBh, 075h, 024h, 0A1h
    dd g_Va013378C4
    db 085h, 0C0h, 074h, 00Fh, 08Bh, 04Ch, 024h, 030h, 08Bh, 011h, 083h, 0C2h, 008h, 052h, 0FFh, 0D0h
    db 083h, 0C4h, 004h, 08Bh, 035h
    dd ?bfmeTheCBC@@3HA
    db 0EBh, 01Eh, 085h, 0DBh, 074h, 03Ah, 08Bh, 04Ch, 024h, 034h, 08Bh, 054h, 024h, 030h, 06Ah, 000h
    db 06Ah, 001h, 051h, 052h, 06Ah, 000h, 055h, 08Bh, 0CFh, 0E8h, 0C8h, 0FCh, 0FFh, 0FFh, 08Bh, 0F0h
    db 08Bh, 044h, 024h, 014h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 066h, 0FFh, 008h, 066h
    db 083h, 038h, 000h, 075h, 02Fh, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 0EBh, 021h, 08Bh, 035h
    dd ?bfmeTheCBC@@3HA
    db 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 075h
    db 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 018h, 05Dh, 05Fh, 08Bh, 0C6h, 05Eh
    db 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 014h, 0C2h, 018h, 000h
?d_008cc940@@YAXXZ ENDP
_TEXT$d00ccc940 ENDS
_TEXT SEGMENT

; ghidra: FUN_00cccce0  retail @ 0x008CCCE0 size 118
public ?d_008ccce0@@YAXXZ
?d_008ccce0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 10h, 8Bh, 4Eh, 04h, 8Bh, 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h, 0Ch
    db 7Ch, 0Fh, 83h, 0F8h, 13h, 7Fh, 0Ah, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 74h
    db 4Dh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 24h, 84h, 0C0h, 75h, 42h, 8Bh, 4Eh, 04h, 8Bh
    db 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 74h, 05h, 83h, 0F8h, 2Ah, 75h, 36h, 0C1h, 0E9h
    db 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 75h, 2Ch, 83h, 0F8h, 01h, 74h, 03h, 8Bh, 76h, 20h
    db 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h, 24h, 08h, 83h, 0C6h, 08h, 56h, 51h, 52h, 0E8h, 2Dh
    db 0F8h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 20h, 83h, 0C4h, 0Ch, 89h, 01h, 5Eh, 0C3h, 8Bh, 54h
    db 24h, 14h, 89h, 32h, 5Eh, 0C3h
?d_008ccce0@@YAXXZ ENDP

; ghidra: FUN_00cccd60  retail @ 0x008CCD60 size 363
public ?d_008ccd60@@YAXXZ
?d_008ccd60@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0D9h, 8Bh, 03h, 8Bh, 4Bh, 08h, 56h, 57h, 8Bh, 7Ch, 81h, 0FCh
    db 8Bh, 77h, 04h, 8Bh, 0C6h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 89h, 7Ch, 24h, 10h, 74h
    db 05h, 83h, 0F8h, 2Ah, 75h, 35h, 8Bh, 0D6h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h
    db 75h, 29h, 83h, 0F8h, 01h, 8Bh, 0C7h, 74h, 03h, 8Bh, 47h, 20h, 8Bh, 4Ch, 24h, 18h
    db 6Ah, 00h, 6Ah, 01h, 6Ah, 01h, 83h, 0C0h, 08h, 50h, 8Bh, 44h, 24h, 2Ch, 50h, 51h
    db 8Bh, 0CBh, 0E8h, 89h, 0FBh, 0FFh, 0FFh, 89h, 44h, 24h, 10h, 8Bh, 7Ch, 24h, 10h, 8Bh
    db 17h, 8Bh, 0CFh, 0FFh, 12h, 8Bh, 03h, 8Bh, 4Bh, 08h, 8Bh, 4Ch, 81h, 0FCh, 8Bh, 51h
    db 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 03h
    db 8Bh, 53h, 08h, 48h, 89h, 03h, 8Bh, 0Dh, 0BCh, 79h, 33h, 01h, 89h, 0Ch, 82h, 0FFh
    db 03h, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh, 0A8h, 01h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 8Bh
    db 07h, 8Bh, 0CFh, 0FFh, 50h, 18h, 8Bh, 0E8h, 85h, 0EDh, 0Fh, 84h, 0ACh, 00h, 00h, 00h
    db 8Bh, 0CDh, 0E8h, 0E9h, 02h, 0FDh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 84h, 00h, 00h
    db 00h, 8Bh, 0Eh, 83h, 0C1h, 08h, 68h, 40h, 60h, 13h, 01h, 51h, 0E8h, 6Fh, 0A1h, 12h
    db 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 5Bh, 8Bh, 16h, 83h, 0C2h, 08h, 68h, 34h, 60h
    db 13h, 01h, 52h, 0E8h, 58h, 0A1h, 12h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 44h, 0E8h
    db 0ECh, 5Ah, 0FCh, 0FFh, 8Bh, 0F8h, 8Bh, 06h, 66h, 0FFh, 00h, 8Bh, 47h, 08h, 66h, 0FFh
    db 08h, 66h, 83h, 38h, 00h, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h
    db 83h, 0C4h, 04h, 8Bh, 0Eh, 89h, 4Fh, 08h, 8Bh, 13h, 8Bh, 43h, 08h, 89h, 3Ch, 90h
    db 0FFh, 03h, 8Bh, 4Fh, 04h, 0C1h, 0E9h, 1Eh, 0F6h, 0C1h, 01h, 75h, 06h, 8Bh, 17h, 8Bh
    db 0CFh, 0FFh, 12h, 56h, 8Bh, 0CDh, 0E8h, 0A5h, 02h, 0FDh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 75h
    db 80h, 8Bh, 7Ch, 24h, 10h, 8Bh, 4Dh, 08h, 83h, 0E1h, 0FEh, 74h, 0Fh, 8Bh, 01h, 0FFh
    db 50h, 18h, 8Bh, 0E8h, 85h, 0EDh, 0Fh, 85h, 54h, 0FFh, 0FFh, 0FFh, 8Bh, 17h, 8Bh, 0CFh
    db 0FFh, 52h, 04h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 08h, 00h
?d_008ccd60@@YAXXZ ENDP

; ghidra: FUN_00ccced0  retail @ 0x008CCED0 size 375
_TEXT ENDS
_TEXT$d00ccced0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCCED0 size 375
public ?d_008cced0@@YAXXZ
?d_008cced0@@YAXXZ PROC
    db 08Bh, 044h, 024h, 00Ch, 083h, 0ECh, 018h, 083h, 0F8h, 0FFh, 053h, 055h, 056h, 057h, 08Bh, 07Ch
    db 024h, 030h, 08Bh, 0F1h, 075h, 012h, 08Bh, 046h, 030h, 08Bh, 04Eh, 038h, 089h, 03Ch, 081h, 0FFh
    db 046h, 030h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 012h, 08Bh, 06Ch, 024h, 02Ch, 033h, 0DBh, 053h, 06Ah
    db 001h, 06Ah, 001h, 068h
    dd g_Va01338700
    db 053h, 057h, 08Bh, 0CEh, 089h, 07Ch, 024h, 02Ch, 089h, 05Ch, 024h, 030h, 089h, 06Ch, 024h, 028h
    db 089h, 05Ch, 024h, 034h
    call ?d_008cc940@@YAXXZ
    db 08Bh, 00Eh, 089h, 044h, 024h, 020h, 08Bh, 086h, 080h, 000h, 000h, 000h, 089h, 044h, 024h, 030h
    db 039h, 05Eh, 07Ch, 088h, 05Ch, 024h, 024h, 089h, 08Eh, 080h, 000h, 000h, 000h, 075h, 05Ch, 08Bh
    db 044h, 024h, 01Ch, 03Bh, 0C3h, 074h, 017h, 039h, 044h, 024h, 010h, 075h, 011h, 08Bh, 04Ch, 024h
    db 018h, 08Bh, 011h, 0FFh, 052h, 004h, 089h, 05Ch, 024h, 018h, 089h, 05Ch, 024h, 01Ch, 08Bh, 04Ch
    db 024h, 010h, 00Fh, 0B6h, 001h, 08Ah, 054h, 024h, 024h, 08Bh, 07Ch, 024h, 034h, 041h, 03Ah, 0D3h
    db 089h, 04Ch, 024h, 010h, 075h, 029h, 03Bh, 0FBh, 07Ch, 006h, 02Bh, 0CDh, 03Bh, 0CFh, 07Fh, 038h
    db 03Bh, 0C3h, 074h, 030h, 08Dh, 04Ch, 024h, 010h, 051h, 056h, 0FFh, 014h, 085h
    dd g_Va012D5A68
    db 08Bh, 046h, 07Ch, 083h, 0C4h, 008h, 03Bh, 0C3h, 074h, 0A4h, 08Bh, 07Ch, 024h, 034h, 03Bh, 0FBh
    db 08Bh, 006h, 07Ch, 034h, 08Bh, 08Eh, 080h, 000h, 000h, 000h, 03Bh, 0C1h, 07Eh, 02Ah, 02Bh, 0C1h
    db 048h, 0EBh, 031h, 03Bh, 0FBh, 07Ch, 0E7h, 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 016h, 08Bh, 046h, 008h, 089h, 00Ch, 090h, 0FFh, 006h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh
    db 0F6h, 0C2h, 001h, 075h, 0CCh, 08Bh, 001h, 0FFh, 010h, 0EBh, 0C6h, 08Bh, 08Eh, 080h, 000h, 000h
    db 000h, 03Bh, 0C1h, 07Eh, 00Ah, 02Bh, 0C1h, 08Bh, 0CEh, 050h
    call ?bfmePop1232@BfmeA1232@@QAEXH@Z
    db 083h, 0FFh, 0FFh, 08Bh, 04Ch, 024h, 030h, 089h, 08Eh, 080h, 000h, 000h, 000h, 075h, 012h, 08Bh
    db 056h, 030h, 08Bh, 046h, 038h, 08Bh, 04Ch, 090h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 0FFh, 04Eh
    db 030h, 08Bh, 006h, 03Bh, 0C3h, 074h, 014h, 083h, 0F8h, 001h, 075h, 01Fh, 08Bh, 04Eh, 008h, 08Bh
    db 054h, 081h, 0FCh, 03Bh, 015h
    dd ?bfmeTheCBC@@3HA
    db 075h, 010h, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 039h, 059h, 004h, 074h, 005h
    call ?d_008a30c0@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 018h, 0C2h, 00Ch, 000h
?d_008cced0@@YAXXZ ENDP
_TEXT$d00ccced0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ccd130  retail @ 0x008CD130 size 224
public ?d_008cd130@@YAXXZ
?d_008cd130@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 0A1h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 56h, 57h, 0C7h
    db 44h, 24h, 08h, 98h, 52h, 2Dh, 01h, 8Bh, 74h, 24h, 1Ch, 8Bh, 06h, 8Bh, 4Eh, 08h
    db 8Bh, 7Ch, 81h, 0FCh, 8Bh, 4Ch, 81h, 0F8h, 8Dh, 44h, 24h, 08h, 50h, 0C7h, 44h, 24h
    db 18h, 00h, 00h, 00h, 00h, 0E8h, 46h, 0B4h, 0FCh, 0FFh, 8Bh, 44h, 24h, 20h, 8Bh, 50h
    db 08h, 8Bh, 40h, 04h, 6Ah, 00h, 6Ah, 01h, 6Ah, 01h, 57h, 8Dh, 4Ch, 24h, 18h, 51h
    db 52h, 50h, 8Bh, 0CEh, 0E8h, 0F7h, 0F4h, 0FFh, 0FFh, 0BFh, 01h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 0Eh, 8Bh, 56h, 08h, 2Bh, 0CFh, 8Bh, 0Ch, 8Ah, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh
    db 0A8h, 01h, 75h, 05h, 8Bh, 11h, 0FFh, 52h, 04h, 47h, 83h, 0FFh, 02h, 7Eh, 0E1h, 8Bh
    db 0Eh, 83h, 0C1h, 0FEh, 89h, 0Eh, 8Bh, 0F1h, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 8Bh, 41h
    db 04h, 85h, 0C0h, 74h, 09h, 85h, 0F6h, 75h, 05h, 0E8h, 0E2h, 5Eh, 0FDh, 0FFh, 8Bh, 44h
    db 24h, 08h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 5Fh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 5Eh, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h
    db 04h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cd130@@YAXXZ ENDP

; ghidra: FUN_00ccd3f0  retail @ 0x008CD3F0 size 155
public ?d_008cd3f0@@YAXXZ
?d_008cd3f0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 74h, 24h, 10h, 8Bh, 4Eh, 08h, 8Bh, 06h, 8Bh, 6Ch, 81h, 0FCh
    db 8Bh, 5Ch, 81h, 0F8h, 8Bh, 44h, 81h, 0F4h, 57h, 8Bh, 7Ch, 24h, 18h, 8Bh, 4Fh, 08h
    db 8Dh, 54h, 24h, 14h, 52h, 8Bh, 57h, 04h, 50h, 51h, 52h, 0E8h, 0C0h, 0F8h, 0FFh, 0FFh
    db 83h, 0C4h, 10h, 8Bh, 0CBh, 0E8h, 0D6h, 0AEh, 0FCh, 0FFh, 8Bh, 4Ch, 24h, 14h, 85h, 0C9h
    db 74h, 22h, 8Bh, 04h, 85h, 10h, 5Ah, 2Dh, 01h, 6Ah, 00h, 6Ah, 01h, 6Ah, 01h, 55h
    db 8Dh, 14h, 85h, 80h, 84h, 33h, 01h, 8Bh, 47h, 08h, 52h, 50h, 51h, 8Bh, 0CEh, 0E8h
    db 3Ch, 0F2h, 0FFh, 0FFh, 0BFh, 01h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Eh, 8Bh, 56h, 08h, 2Bh, 0CFh, 8Bh, 0Ch, 8Ah, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh
    db 0A8h, 01h, 75h, 05h, 8Bh, 11h, 0FFh, 52h, 04h, 47h, 83h, 0FFh, 03h, 7Eh, 0E1h, 8Bh
    db 06h, 5Fh, 83h, 0C0h, 0FDh, 89h, 06h, 5Eh, 5Dh, 5Bh, 0C3h
?d_008cd3f0@@YAXXZ ENDP

; ghidra: FUN_00ccd490  retail @ 0x008CD490 size 133
public ?d_008cd490@@YAXXZ
?d_008cd490@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 8Bh, 4Eh, 08h, 8Bh, 44h, 81h, 0FCh, 8Bh, 50h
    db 04h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 4Dh, 8Dh, 4Ch, 24h, 08h, 51h
    db 50h, 8Bh, 44h, 24h, 14h, 8Bh, 50h, 08h, 8Bh, 40h, 04h, 52h, 50h, 0E8h, 1Eh, 0F8h
    db 0FFh, 0FFh, 8Bh, 54h, 24h, 18h, 83h, 0C4h, 10h, 85h, 0D2h, 74h, 2Bh, 8Bh, 4Ah, 04h
    db 8Bh, 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h, 0Ch, 7Ch, 1Eh, 83h, 0F8h, 13h, 7Fh, 19h, 0C1h
    db 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 75h, 0Fh, 8Bh, 4Ah, 4Ch, 8Bh, 49h, 50h, 52h
    db 83h, 0C1h, 24h, 0E8h, 98h, 0FFh, 0FEh, 0FFh, 8Bh, 16h, 8Bh, 46h, 08h, 8Bh, 4Ch, 90h
    db 0FCh, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h
    db 04h, 0FFh, 0Eh, 5Eh, 0C3h
?d_008cd490@@YAXXZ ENDP

; ghidra: FUN_00ccd520  retail @ 0x008CD520 size 541
public ?d_008cd520@@YAXXZ
?d_008cd520@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 0A1h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 55h, 56h, 8Bh, 74h, 24h, 1Ch, 8Bh, 06h, 8Bh, 4Eh
    db 08h, 57h, 8Bh, 7Ch, 81h, 0FCh, 8Bh, 4Fh, 04h, 8Bh, 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h
    db 01h, 74h, 09h, 83h, 0F8h, 2Ah, 0Fh, 85h, 95h, 00h, 00h, 00h, 0C1h, 0E9h, 0Fh, 0F6h
    db 0D1h, 0F6h, 0C1h, 01h, 0Fh, 85h, 87h, 00h, 00h, 00h, 33h, 0EDh, 66h, 0FFh, 05h, 98h
    db 52h, 2Dh, 01h, 89h, 6Ch, 24h, 0Ch, 0C7h, 44h, 24h, 20h, 98h, 52h, 2Dh, 01h, 8Bh
    db 47h, 04h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 89h, 6Ch, 24h, 18h, 74h, 03h, 8Bh, 7Fh
    db 20h, 53h, 8Bh, 5Ch, 24h, 28h, 8Bh, 4Bh, 08h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 53h
    db 04h, 8Dh, 44h, 24h, 14h, 50h, 83h, 0C7h, 08h, 57h, 51h, 52h, 0E8h, 6Fh, 8Dh, 0FFh
    db 0FFh, 8Bh, 4Bh, 08h, 8Bh, 54h, 24h, 24h, 83h, 0C4h, 14h, 55h, 6Ah, 01h, 6Ah, 01h
    db 8Dh, 44h, 24h, 30h, 50h, 51h, 52h, 8Bh, 0CEh, 0E8h, 72h, 0F3h, 0FFh, 0FFh, 8Bh, 0F8h
    db 8Bh, 44h, 24h, 24h, 66h, 0FFh, 08h, 66h, 39h, 28h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh
    db 0FFh, 0FFh, 5Bh, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h
    db 04h, 8Bh, 17h, 8Bh, 0CFh, 0BDh, 03h, 00h, 00h, 00h, 0FFh, 12h, 0A1h, 0D8h, 77h, 33h
    db 01h, 89h, 0B8h, 40h, 12h, 00h, 00h, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 33h, 0C0h, 89h
    db 81h, 54h, 12h, 00h, 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h, 89h, 82h, 58h, 12h, 00h
    db 00h, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 0B8h, 00h, 3Ch, 1Ch, 0C6h, 89h, 81h, 44h, 12h
    db 00h, 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h, 89h, 82h, 48h, 12h, 00h, 00h, 8Bh, 0Dh
    db 0D8h, 77h, 33h, 01h, 89h, 81h, 4Ch, 12h, 00h, 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h
    db 89h, 82h, 50h, 12h, 00h, 00h, 8Bh, 06h, 8Bh, 4Eh, 08h, 8Bh, 44h, 81h, 0F8h, 8Bh
    db 40h, 04h, 8Bh, 0D0h, 83h, 0E2h, 3Fh, 80h, 0FAh, 07h, 75h, 09h, 0C1h, 0E8h, 0Fh, 0F6h
    db 0D0h, 0A8h, 01h, 74h, 28h, 0A1h, 0D8h, 77h, 33h, 01h, 0DBh, 80h, 74h, 12h, 00h, 00h
    db 0D8h, 67h, 20h, 0D9h, 98h, 54h, 12h, 00h, 00h, 0A1h, 0D8h, 77h, 33h, 01h, 0DBh, 80h
    db 78h, 12h, 00h, 00h, 0D8h, 67h, 24h, 0D9h, 98h, 58h, 12h, 00h, 00h, 8Bh, 06h, 8Bh
    db 4Eh, 08h, 8Bh, 54h, 81h, 0F4h, 8Bh, 7Ah, 04h, 8Bh, 0D7h, 83h, 0E2h, 3Fh, 80h, 0FAh
    db 07h, 75h, 70h, 8Bh, 0D7h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 64h, 8Bh
    db 4Ch, 81h, 0F0h, 0BDh, 07h, 00h, 00h, 00h, 0E8h, 03h, 0ADh, 0FCh, 0FFh, 0A1h, 0D8h, 77h
    db 33h, 01h, 0D9h, 98h, 50h, 12h, 00h, 00h, 8Bh, 0Eh, 8Bh, 56h, 08h, 8Bh, 4Ch, 8Ah
    db 0ECh, 0E8h, 0EAh, 0ACh, 0FCh, 0FFh, 0A1h, 0D8h, 77h, 33h, 01h, 0D9h, 98h, 4Ch, 12h, 00h
    db 00h, 8Bh, 0Eh, 8Bh, 56h, 08h, 8Bh, 4Ch, 8Ah, 0E8h, 0E8h, 0D1h, 0ACh, 0FCh, 0FFh, 0A1h
    db 0D8h, 77h, 33h, 01h, 0D9h, 98h, 48h, 12h, 00h, 00h, 8Bh, 0Eh, 8Bh, 56h, 08h, 8Bh
    db 4Ch, 8Ah, 0E4h, 0E8h, 0B8h, 0ACh, 0FCh, 0FFh, 0A1h, 0D8h, 77h, 33h, 01h, 0D9h, 98h, 44h
    db 12h, 00h, 00h, 55h, 8Bh, 0CEh, 0E8h, 0C5h, 35h, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Fh
    db 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cd520@@YAXXZ ENDP

; ghidra: FUN_00ccda60  retail @ 0x008CDA60 size 109
public ?d_008cda60@@YAXXZ
?d_008cda60@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 4Eh, 08h, 8Bh, 06h, 8Bh, 54h, 81h, 0FCh, 8Bh, 44h
    db 81h, 0F8h, 8Bh, 48h, 04h, 80h, 0E1h, 3Fh, 80h, 0F9h, 01h, 57h, 74h, 03h, 8Bh, 40h
    db 20h, 6Ah, 00h, 6Ah, 01h, 6Ah, 00h, 52h, 83h, 0C0h, 08h, 50h, 8Bh, 44h, 24h, 24h
    db 8Bh, 50h, 08h, 8Bh, 40h, 04h, 52h, 50h, 8Bh, 0CEh, 0E8h, 0F1h, 0EBh, 0FFh, 0FFh, 0BFh
    db 01h, 00h, 00h, 00h, 8Bh, 0Eh, 8Bh, 56h, 08h, 2Bh, 0CFh, 8Bh, 0Ch, 8Ah, 8Bh, 41h
    db 04h, 0C1h, 0E8h, 1Eh, 0A8h, 01h, 75h, 05h, 8Bh, 11h, 0FFh, 52h, 04h, 47h, 83h, 0FFh
    db 02h, 7Eh, 0E1h, 8Bh, 06h, 83h, 0C0h, 0FEh, 5Fh, 89h, 06h, 5Eh, 0C3h
?d_008cda60@@YAXXZ ENDP

; ghidra: FUN_00ccdc00  retail @ 0x008CDC00 size 552
public ?d_008cdc00@@YAXXZ
?d_008cdc00@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Fh, 0A2h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 55h, 56h, 57h
    db 0C7h, 44h, 24h, 0Ch, 98h, 52h, 2Dh, 01h, 8Bh, 74h, 24h, 20h, 8Bh, 4Eh, 08h, 8Bh
    db 06h, 8Bh, 44h, 81h, 0FCh, 8Dh, 54h, 24h, 20h, 52h, 50h, 8Bh, 44h, 24h, 2Ch, 8Bh
    db 48h, 08h, 8Bh, 50h, 04h, 51h, 52h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h, 00h, 0E8h
    db 8Ch, 0F0h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 30h, 83h, 0C4h, 10h, 85h, 0C9h, 0Fh, 84h, 57h
    db 01h, 00h, 00h, 8Bh, 51h, 04h, 8Bh, 0C2h, 83h, 0E0h, 3Fh, 83h, 0F8h, 0Ch, 7Ch, 1Fh
    db 83h, 0F8h, 13h, 7Fh, 1Ah, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 10h, 8Dh
    db 44h, 24h, 0Ch, 50h, 51h, 0E8h, 36h, 76h, 0FFh, 0FFh, 83h, 0C4h, 08h, 0EBh, 57h, 68h
    db 1Ch, 30h, 07h, 01h, 8Dh, 4Ch, 24h, 24h, 0E8h, 0E3h, 09h, 0FDh, 0FFh, 8Bh, 44h, 24h
    db 20h, 66h, 0FFh, 00h, 8Bh, 44h, 24h, 0Ch, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C6h
    db 44h, 24h, 18h, 01h, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h
    db 83h, 0C4h, 04h, 8Bh, 44h, 24h, 20h, 89h, 44h, 24h, 0Ch, 66h, 0FFh, 08h, 66h, 83h
    db 38h, 00h, 0C6h, 44h, 24h, 18h, 00h, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h
    db 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 3Dh, 78h, 84h, 33h, 01h, 85h, 0FFh, 74h, 3Fh
    db 8Bh, 47h, 0Ch, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 0A3h, 78h, 84h, 33h, 01h, 8Bh, 51h
    db 04h, 3Bh, 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 67h, 04h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh
    db 08h, 8Bh, 49h, 08h, 89h, 3Ch, 91h, 0FFh, 00h, 8Bh, 47h, 08h, 3Dh, 98h, 52h, 2Dh
    db 01h, 8Dh, 4Fh, 08h, 74h, 33h, 6Ah, 00h, 0E8h, 23h, 0Fh, 0FDh, 0FFh, 0EBh, 2Ah, 6Ah
    db 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h, 24h, 85h, 0C0h
    db 0C6h, 44h, 24h, 18h, 02h, 74h, 09h, 8Bh, 0C8h, 0E8h, 0B2h, 0BDh, 0FDh, 0FFh, 0EBh, 02h
    db 33h, 0C0h, 0C6h, 44h, 24h, 18h, 00h, 8Bh, 0F8h, 8Bh, 44h, 24h, 0Ch, 66h, 0FFh, 00h
    db 8Bh, 47h, 08h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah
    db 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 44h, 24h, 0Ch, 89h, 47h, 08h
    db 8Bh, 0Eh, 8Bh, 56h, 08h, 8Bh, 4Ch, 8Ah, 0FCh, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh, 0A8h
    db 01h, 75h, 05h, 8Bh, 11h, 0FFh, 52h, 04h, 8Bh, 2Eh, 8Bh, 4Eh, 08h, 4Dh, 89h, 2Eh
    db 8Bh, 0C5h, 89h, 3Ch, 81h, 0FFh, 06h, 8Bh, 57h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h
    db 75h, 43h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 10h, 0EBh, 3Bh, 8Bh, 0Eh, 8Bh, 56h, 08h, 8Bh
    db 4Ch, 8Ah, 0FCh, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh, 0A8h, 01h, 75h, 05h, 8Bh, 11h, 0FFh
    db 52h, 04h, 8Bh, 2Eh, 8Bh, 56h, 08h, 4Dh, 89h, 2Eh, 8Bh, 0Dh, 0BCh, 79h, 33h, 01h
    db 8Bh, 0C5h, 89h, 0Ch, 82h, 0FFh, 06h, 8Bh, 41h, 04h, 0C1h, 0E8h, 1Eh, 0A8h, 01h, 75h
    db 04h, 8Bh, 11h, 0FFh, 12h, 8Bh, 44h, 24h, 0Ch, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h
    db 5Fh, 5Eh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 5Dh, 75h, 0Ch, 50h, 0A1h, 30h
    db 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cdc00@@YAXXZ ENDP

; ghidra: FUN_00ccde50  retail @ 0x008CDE50 size 907
_TEXT ENDS
_TEXT$d00ccde50 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCDE50 size 907
public ?d_008cde50@@YAXXZ
?d_008cde50@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A287
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 053h
    db 055h, 056h, 08Bh, 074h, 024h, 020h, 08Bh, 006h, 08Bh, 056h, 008h, 08Bh, 05Ch, 082h, 0F8h, 08Bh
    db 04Ch, 082h, 0FCh, 08Bh, 06Bh, 004h, 08Bh, 0C5h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 057h
    db 00Fh, 085h, 0F1h, 002h, 000h, 000h, 08Bh, 079h, 004h, 08Bh, 0D7h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h
    db 0F6h, 0C2h, 001h, 00Fh, 085h, 0DEh, 002h, 000h, 000h, 083h, 0E5h, 03Fh, 083h, 0FDh, 016h, 00Fh
    db 085h, 07Dh, 000h, 000h, 000h, 08Bh, 0C7h, 083h, 0E0h, 03Fh, 083h, 0F8h, 007h, 074h, 005h, 083h
    db 0F8h, 006h, 075h, 06Eh
    call ?toInteger@AptValue@@QBEHXZ
    db 050h, 08Bh, 0CBh
    call ?bfmeAt@Gen_008B8E50@@QBEHH@Z
    db 08Bh, 0D8h, 0BFh, 001h, 000h, 000h, 000h, 090h, 08Bh, 006h, 08Bh, 04Eh, 008h, 02Bh, 0C7h, 08Bh
    db 00Ch, 081h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh
    db 050h, 004h, 047h, 083h, 0FFh, 002h, 07Eh, 0E0h, 08Bh, 03Eh, 08Bh, 04Eh, 008h, 083h, 0C7h, 0FEh
    db 089h, 03Eh, 08Bh, 0C7h, 089h, 01Ch, 081h, 0FFh, 006h, 08Bh, 053h, 004h, 0C1h, 0EAh, 01Eh, 0F6h
    db 0C2h, 001h, 00Fh, 085h, 0B8h, 002h, 000h, 000h, 08Bh, 003h, 08Bh, 0CBh, 0FFh, 010h, 05Fh, 05Eh
    db 05Dh, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h
    db 0C3h, 083h, 0FDh, 00Bh, 00Fh, 085h, 007h, 001h, 000h, 000h, 083h, 0E7h, 03Fh, 083h, 0FFh, 001h
    db 074h, 003h, 08Bh, 049h, 020h, 08Bh, 049h, 008h, 083h, 0C1h, 008h, 051h, 0FFh, 015h
    dd ?g_bfmeSlot13VB@@3P6AXXZA
    db 08Bh, 03Dh
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 083h, 0C4h, 004h, 085h, 0FFh, 08Bh, 0D8h, 074h, 040h, 08Bh, 00Dh
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 057h, 00Ch, 089h, 015h
    dd ?Rva008C3B60Head@@3PAURva008C3B60Node@@A
    db 08Bh, 051h, 004h, 03Bh, 011h, 08Dh, 041h, 004h, 07Ch, 009h, 081h, 067h, 004h, 0FFh, 0FFh, 0FFh
    db 0BFh, 0EBh, 008h, 08Bh, 049h, 008h, 089h, 03Ch, 091h, 0FFh, 000h, 08Bh, 047h, 008h, 03Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Fh, 008h, 074h, 039h, 06Ah, 000h
    call ?bfmeTruncVKK@BfmeStrVKK@@QAEXI@Z
    db 0EBh, 030h, 06Ah, 010h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 024h, 085h, 0C0h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva008A9B00@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 01Ch, 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 0F8h, 053h, 08Bh
    db 0CFh
    call ?append@Rva008B2EA0Node@@QAEXPAX@Z
    db 053h, 0FFh, 015h
    dd ?Rva008A30A0ReleasePtr@@3P6AXPAX@ZA
    db 083h, 0C4h, 004h, 0BBh, 001h, 000h, 000h, 000h, 08Bh, 016h, 08Bh, 046h, 008h, 02Bh, 0D3h, 08Bh
    db 00Ch, 090h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh
    db 050h, 004h, 043h, 083h, 0FBh, 002h, 07Eh, 0E0h, 08Bh, 01Eh, 08Bh, 04Eh, 008h, 083h, 0C3h, 0FEh
    db 089h, 01Eh, 08Bh, 0C3h, 089h, 03Ch, 081h, 0FFh, 006h, 08Bh, 057h, 004h, 0C1h, 0EAh, 01Eh, 0F6h
    db 0C2h, 001h, 00Fh, 085h, 0A8h, 001h, 000h, 000h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h, 05Fh, 05Eh
    db 05Dh, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h
    db 0C3h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0C7h, 044h, 024h, 024h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 054h, 024h, 024h, 052h, 0C7h, 044h, 024h, 020h, 001h, 000h, 000h, 000h
    call ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
    db 06Ah, 001h, 06Ah, 000h, 06Ah, 001h, 08Dh, 044h, 024h, 030h, 050h, 06Ah, 000h, 053h, 08Bh, 0CEh
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 04Fh, 004h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 00Fh, 084h, 080h
    db 000h, 000h, 000h, 08Bh, 046h, 018h, 085h, 0C0h, 074h, 079h, 08Bh, 0D0h, 08Bh, 046h, 020h, 08Bh
    db 044h, 090h, 0FCh, 08Bh, 048h, 004h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 063h
    db 08Bh, 046h, 020h, 08Bh, 06Ch, 090h, 0FCh, 08Bh, 055h, 000h, 08Bh, 0CDh, 089h, 06Ch, 024h, 010h
    db 0FFh, 052h, 024h, 084h, 0C0h, 074h, 04Ch, 08Bh, 045h, 000h, 08Bh, 0CDh, 0FFh, 050h, 018h, 085h
    db 0C0h, 074h, 040h, 08Bh, 040h, 008h, 083h, 0E0h, 0FEh, 08Bh, 0E8h, 074h, 036h, 03Bh, 0EBh, 075h
    db 026h, 08Bh, 054h, 024h, 010h, 06Ah, 001h, 06Ah, 000h, 06Ah, 000h, 08Dh, 04Ch, 024h, 030h, 051h
    db 052h, 053h, 08Bh, 0CEh
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 047h, 004h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 074h, 00Ch, 08Bh, 055h
    db 000h, 08Bh, 0CDh, 0FFh, 052h, 018h, 085h, 0C0h, 075h, 0C0h, 0BBh, 001h, 000h, 000h, 000h, 08Bh
    db 006h, 08Bh, 04Eh, 008h, 02Bh, 0C3h, 08Bh, 00Ch, 081h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h
    db 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h, 043h, 083h, 0FBh, 002h, 07Eh, 0E0h, 08Bh
    db 01Eh, 08Bh, 04Eh, 008h, 083h, 0C3h, 0FEh, 089h, 01Eh, 08Bh, 0C3h, 089h, 03Ch, 081h, 0FFh, 006h
    db 08Bh, 057h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh
    db 010h, 08Bh, 044h, 024h, 024h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 01Ch
    db 0FFh, 0FFh, 0FFh, 0FFh, 075h, 06Ah, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 05Fh, 05Eh, 05Dh, 05Bh, 08Bh, 04Ch, 024h, 004h, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C3h, 0BFh, 001h, 000h, 000h, 000h, 08Bh
    db 016h, 08Bh, 046h, 008h, 02Bh, 0D7h, 08Bh, 00Ch, 090h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h
    db 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h, 047h, 083h, 0FFh, 002h, 07Eh, 0E0h, 08Bh
    db 01Eh, 08Bh, 056h, 008h, 083h, 0C3h, 0FEh, 089h, 01Eh, 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 0C3h, 089h, 00Ch, 082h, 0FFh, 006h, 08Bh, 041h, 004h, 0C1h, 0E8h, 01Eh, 0A8h, 001h, 075h
    db 004h, 08Bh, 011h, 0FFh, 012h, 08Bh, 04Ch, 024h, 014h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C3h
?d_008cde50@@YAXXZ ENDP
_TEXT$d00ccde50 ENDS
_TEXT SEGMENT

; ghidra: FUN_00cce1e0  retail @ 0x008CE1E0 size 549
public ?d_008ce1e0@@YAXXZ
?d_008ce1e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B0h, 0A2h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 45h, 00h, 8Bh
    db 4Dh, 08h, 8Bh, 5Ch, 81h, 0F4h, 56h, 8Bh, 74h, 81h, 0F8h, 57h, 8Bh, 7Ch, 81h, 0FCh
    db 8Bh, 43h, 04h, 8Bh, 0C8h, 83h, 0E1h, 3Fh, 80h, 0F9h, 16h, 75h, 46h, 0C1h, 0E8h, 0Fh
    db 0F6h, 0D0h, 0A8h, 01h, 75h, 3Dh, 8Bh, 4Eh, 04h, 8Bh, 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h
    db 07h, 75h, 0Ch, 8Bh, 0D1h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 74h, 0Fh, 83h
    db 0F8h, 06h, 75h, 1Fh, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 75h, 15h, 57h, 8Bh
    db 0CEh, 0E8h, 0AAh, 0A0h, 0FCh, 0FFh, 50h, 8Bh, 0CBh, 0E8h, 0B2h, 0ABh, 0FEh, 0FFh, 0E9h, 49h
    db 01h, 00h, 00h, 8Bh, 03h, 8Bh, 0CBh, 0FFh, 50h, 24h, 84h, 0C0h, 0Fh, 85h, 8Ah, 00h
    db 00h, 00h, 8Bh, 4Bh, 04h, 8Bh, 0C1h, 83h, 0E0h, 3Fh, 83h, 0F8h, 0Ch, 7Ch, 11h, 83h
    db 0F8h, 13h, 7Fh, 0Ch, 8Bh, 0D1h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 74h, 6Ch
    db 83h, 0F8h, 0Bh, 0Fh, 85h, 13h, 01h, 00h, 00h, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h
    db 01h, 0Fh, 85h, 05h, 01h, 00h, 00h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h
    db 24h, 10h, 98h, 52h, 2Dh, 01h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CFh, 0C7h, 44h, 24h
    db 20h, 01h, 00h, 00h, 00h, 0E8h, 0F6h, 0A2h, 0FCh, 0FFh, 8Bh, 46h, 04h, 83h, 0E0h, 3Fh
    db 83h, 0F8h, 01h, 74h, 03h, 8Bh, 76h, 20h, 8Bh, 4Ch, 24h, 10h, 8Bh, 56h, 08h, 83h
    db 0C1h, 08h, 51h, 83h, 0C2h, 08h, 52h, 0FFh, 15h, 64h, 78h, 33h, 01h, 8Bh, 44h, 24h
    db 18h, 83h, 0C4h, 08h, 66h, 0FFh, 08h, 0E9h, 96h, 00h, 00h, 00h, 66h, 0FFh, 05h, 98h
    db 52h, 2Dh, 01h, 0C7h, 44h, 24h, 24h, 98h, 52h, 2Dh, 01h, 8Dh, 4Ch, 24h, 24h, 51h
    db 8Bh, 0CEh, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 0E8h, 0A1h, 0A2h, 0FCh, 0FFh, 8Bh
    db 44h, 24h, 28h, 8Bh, 48h, 08h, 6Ah, 01h, 6Ah, 00h, 6Ah, 01h, 57h, 8Dh, 54h, 24h
    db 34h, 52h, 51h, 53h, 8Bh, 0CDh, 0E8h, 55h, 0E3h, 0FFh, 0FFh, 8Bh, 54h, 24h, 24h, 0BFh
    db 40h, 60h, 13h, 01h, 8Dh, 72h, 08h, 0B9h, 0Ah, 00h, 00h, 00h, 33h, 0C0h, 0F3h, 0A6h
    db 75h, 3Bh, 8Bh, 73h, 04h, 8Bh, 0C6h, 83h, 0E0h, 3Fh, 83h, 0F8h, 1Bh, 75h, 0Ch, 8Bh
    db 0CEh, 0C1h, 0E9h, 0Fh, 0F6h, 0D1h, 0F6h, 0C1h, 01h, 74h, 15h, 83h, 0F8h, 0Ch, 7Ch, 1Dh
    db 83h, 0F8h, 13h, 7Fh, 18h, 8Bh, 0C6h, 0C1h, 0E8h, 0Fh, 0F6h, 0D0h, 0A8h, 01h, 75h, 0Dh
    db 8Bh, 13h, 6Ah, 01h, 8Bh, 0CBh, 0FFh, 52h, 20h, 8Bh, 54h, 24h, 24h, 66h, 0FFh, 0Ah
    db 8Bh, 0C2h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Ch
    db 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 0BEh, 01h, 00h, 00h
    db 00h, 8Bh, 4Dh, 00h, 8Bh, 55h, 08h, 2Bh, 0CEh, 8Bh, 0Ch, 8Ah, 8Bh, 41h, 04h, 0C1h
    db 0E8h, 1Eh, 0A8h, 01h, 75h, 05h, 8Bh, 11h, 0FFh, 52h, 04h, 46h, 83h, 0FEh, 03h, 7Eh
    db 0E0h, 8Bh, 4Dh, 00h, 83h, 0C1h, 0FDh, 89h, 4Dh, 00h, 8Bh, 0E9h, 8Bh, 0Dh, 10h, 78h
    db 33h, 01h, 8Bh, 41h, 04h, 85h, 0C0h, 74h, 09h, 85h, 0EDh, 75h, 05h, 0E8h, 0CEh, 4Ch
    db 0FDh, 0FFh, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
?d_008ce1e0@@YAXXZ ENDP

; ghidra: FUN_00cce5c0  retail @ 0x008CE5C0 size 383
public ?d_008ce5c0@@YAXXZ
?d_008ce5c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FFh, 0A2h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 8Bh, 6Ch, 24h, 20h, 56h, 8Bh, 75h, 00h
    db 83h, 0C6h, 03h, 83h, 0E6h, 0FCh, 8Dh, 46h, 18h, 89h, 45h, 00h, 8Bh, 4Eh, 0Ch, 03h
    db 0C8h, 89h, 4Dh, 00h, 57h, 8Bh, 7Ch, 24h, 24h, 8Bh, 57h, 5Ch, 89h, 56h, 10h, 8Bh
    db 47h, 60h, 89h, 46h, 14h, 8Bh, 06h, 50h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 6Fh, 00h, 0FDh
    db 0FFh, 8Bh, 4Fh, 0Ch, 33h, 0C0h, 3Bh, 0C8h, 89h, 44h, 24h, 1Ch, 7Eh, 11h, 8Bh, 57h
    db 14h, 8Bh, 4Ch, 8Ah, 0FCh, 8Bh, 01h, 89h, 4Ch, 24h, 24h, 0FFh, 10h, 0EBh, 04h, 89h
    db 44h, 24h, 24h, 6Ah, 3Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 58h, 08h, 53h, 0E8h
    db 0BCh, 8Ch, 0FCh, 0FFh, 83h, 0C4h, 08h, 89h, 5Ch, 24h, 10h, 85h, 0DBh, 0C6h, 44h, 24h
    db 1Ch, 01h, 74h, 1Fh, 8Bh, 45h, 04h, 8Bh, 48h, 50h, 8Bh, 49h, 0Ch, 8Bh, 51h, 04h
    db 50h, 8Bh, 44h, 24h, 28h, 52h, 50h, 56h, 8Bh, 0CBh, 0E8h, 21h, 7Ch, 00h, 00h, 8Bh
    db 0D8h, 0EBh, 02h, 33h, 0DBh, 8Bh, 36h, 80h, 3Eh, 00h, 0C6h, 44h, 24h, 1Ch, 00h, 75h
    db 1Ch, 8Bh, 0Fh, 8Bh, 57h, 08h, 89h, 1Ch, 8Ah, 0FFh, 07h, 8Bh, 43h, 04h, 0C1h, 0E8h
    db 1Eh, 0A8h, 01h, 75h, 75h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 12h, 0EBh, 6Dh, 56h, 8Dh, 4Ch
    db 24h, 28h, 0E8h, 0D9h, 0FFh, 0FCh, 0FFh, 8Bh, 44h, 24h, 24h, 66h, 0FFh, 00h, 8Bh, 44h
    db 24h, 28h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C6h, 44h, 24h, 1Ch, 02h, 75h, 0Ch
    db 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 44h, 24h, 24h
    db 89h, 44h, 24h, 28h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C6h, 44h, 24h, 1Ch, 00h
    db 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 8Bh
    db 45h, 08h, 8Bh, 4Dh, 04h, 6Ah, 00h, 6Ah, 01h, 6Ah, 01h, 53h, 8Dh, 54h, 24h, 38h
    db 52h, 50h, 51h, 8Bh, 0CFh, 0E8h, 86h, 0DFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 28h, 66h, 0FFh
    db 08h, 66h, 83h, 38h, 00h, 5Fh, 5Eh, 5Dh, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh
    db 5Bh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008ce5c0@@YAXXZ ENDP

; ghidra: FUN_00ccee00  retail @ 0x008CEE00 size 64
public ?d_008cee00@@YAXXZ
?d_008cee00@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 8Ah, 08h, 40h, 89h
    db 07h, 8Bh, 16h, 0Fh, 0B6h, 0C1h, 8Bh, 4Eh, 60h, 8Bh, 0Ch, 81h, 8Bh, 46h, 08h, 89h
    db 0Ch, 90h, 0FFh, 06h, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 04h, 8Bh
    db 01h, 0FFh, 10h, 57h, 56h, 0E8h, 16h, 0F0h, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_008cee00@@YAXXZ ENDP

; ghidra: FUN_00ccf030  retail @ 0x008CF030 size 380
_TEXT ENDS
_TEXT$d00ccf030 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCF030 size 380
public ?d_008cf030@@YAXXZ
?d_008cf030@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A427
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 018h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 053h, 055h, 056h, 057h, 0C7h, 044h, 024h, 020h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Bh, 074h, 024h, 038h, 08Bh, 006h, 08Bh, 04Eh, 008h, 08Bh, 05Ch, 081h, 0FCh, 08Bh, 04Ch, 081h
    db 0F8h, 033h, 0EDh, 089h, 06Ch, 024h, 030h, 089h, 05Ch, 024h, 01Ch
    call ?toInteger@AptValue@@QBEHXZ
    db 08Bh, 0F8h, 08Dh, 004h, 0BDh, 000h, 000h, 000h, 000h, 050h, 089h, 07Ch, 024h, 018h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 083h, 0C4h, 004h, 03Bh, 0FDh, 089h, 044h, 024h, 018h, 089h, 06Ch, 024h, 010h, 00Fh, 08Eh, 0BDh
    db 000h, 000h, 000h, 08Bh, 00Eh, 08Bh, 056h, 008h, 02Bh, 0CDh, 08Bh, 07Ch, 08Ah, 0F4h, 08Bh, 007h
    db 08Bh, 0CFh, 0FFh, 050h, 018h, 08Bh, 040h, 00Ch, 083h, 0E0h, 0FEh, 08Bh, 0D8h, 00Fh, 085h, 07Fh
    db 000h, 000h, 000h, 06Ah, 024h, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 024h, 085h, 0F6h, 0C6h, 044h, 024h, 030h, 001h, 074h, 00Ch
    db 057h, 08Bh, 0CEh
    call ??0Rva89ACB0Holder@@QAE@PAVBfmeHeld99CB0@@@Z
    db 08Bh, 0F0h, 0EBh, 002h, 033h, 0F6h, 08Bh, 017h, 08Bh, 0CFh, 0C6h, 044h, 024h, 030h, 000h, 08Bh
    db 0DEh, 0FFh, 052h, 018h, 08Bh, 0F8h, 08Bh, 047h, 00Ch, 083h, 0E0h, 0FEh, 085h, 0F6h, 08Bh, 0E8h
    db 074h, 006h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 010h, 085h, 0EDh, 074h, 008h, 08Bh, 055h, 000h, 08Bh
    db 0CDh, 0FFh, 052h, 004h, 085h, 0F6h, 075h, 005h, 089h, 077h, 00Ch, 0EBh, 011h, 08Bh, 006h, 08Bh
    db 0CEh, 0FFh, 050h, 014h, 03Ch, 001h, 075h, 003h, 083h, 0CEh, 001h, 089h, 077h, 00Ch, 08Bh, 074h
    db 024h, 038h, 08Bh, 06Ch, 024h, 010h, 08Bh, 04Ch, 024h, 018h, 08Bh, 044h, 024h, 014h, 089h, 01Ch
    db 0A9h, 045h, 03Bh, 0E8h, 089h, 06Ch, 024h, 010h, 00Fh, 08Ch, 049h, 0FFh, 0FFh, 0FFh, 08Bh, 05Ch
    db 024h, 01Ch, 08Bh, 0F8h, 08Bh, 044h, 024h, 018h, 08Bh, 013h, 057h, 050h, 08Bh, 0CBh, 0FFh, 052h
    db 040h, 083h, 0C7h, 002h, 057h, 08Bh, 0CEh
    call ?bfmePop1232@BfmeA1232@@QAEXH@Z
    db 066h, 0FFh, 00Dh
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 05Fh, 05Eh, 05Dh, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh, 05Bh, 075h, 011h, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 068h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 018h, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 083h, 0C4h, 024h, 0C3h
?d_008cf030@@YAXXZ ENDP
_TEXT$d00ccf030 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ccf1b0  retail @ 0x008CF1B0 size 520
public ?d_008cf1b0@@YAXXZ
?d_008cf1b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 50h, 0A4h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 8Bh, 5Ch, 24h, 1Ch, 55h, 56h, 8Bh, 33h, 57h
    db 8Bh, 7Ch, 24h, 24h, 8Bh, 07h, 83h, 0C6h, 03h, 83h, 0E6h, 0FCh, 89h, 44h, 24h, 10h
    db 8Dh, 46h, 14h, 89h, 03h, 8Bh, 0Eh, 03h, 0C8h, 89h, 0Bh, 8Bh, 56h, 04h, 03h, 0CAh
    db 89h, 0Bh, 8Bh, 56h, 08h, 03h, 0D1h, 89h, 13h, 8Bh, 0Eh, 8Bh, 53h, 04h, 51h, 52h
    db 50h, 8Bh, 0CFh, 0E8h, 0C8h, 0DCh, 0FFh, 0FFh, 8Bh, 6Fh, 7Ch, 85h, 0EDh, 0Fh, 84h, 23h
    db 01h, 00h, 00h, 8Ah, 46h, 0Ch, 0A8h, 01h, 0Fh, 84h, 18h, 01h, 00h, 00h, 0A8h, 04h
    db 74h, 2Eh, 0Fh, 0B6h, 4Eh, 0Fh, 8Bh, 47h, 58h, 83h, 3Ch, 88h, 00h, 74h, 0Eh, 0Fh
    db 0B6h, 56h, 0Fh, 8Bh, 04h, 90h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 04h, 0Fh, 0B6h, 46h
    db 0Fh, 8Bh, 4Fh, 58h, 89h, 2Ch, 81h, 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 12h, 0EBh, 50h
    db 8Bh, 46h, 10h, 50h, 8Dh, 4Ch, 24h, 28h, 0E8h, 23h, 0F4h, 0FCh, 0FFh, 8Bh, 4Bh, 04h
    db 6Ah, 00h, 6Ah, 01h, 6Ah, 00h, 55h, 8Dh, 44h, 24h, 34h, 50h, 6Ah, 00h, 51h, 8Bh
    db 0CFh, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h, 0E8h, 12h, 0D4h, 0FFh, 0FFh, 8Bh, 44h
    db 24h, 24h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh
    db 0FFh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h
    db 8Bh, 4Fh, 7Ch, 8Bh, 01h, 0FFh, 50h, 04h, 0C7h, 47h, 7Ch, 00h, 00h, 00h, 00h, 8Bh
    db 4Eh, 04h, 8Bh, 53h, 04h, 8Bh, 06h, 51h, 8Dh, 4Ch, 30h, 14h, 52h, 51h, 8Bh, 0CFh
    db 0E8h, 0Bh, 0DCh, 0FFh, 0FFh, 0F6h, 46h, 0Ch, 04h, 74h, 1Ah, 0Fh, 0B6h, 56h, 0Fh, 8Bh
    db 0Dh, 0BCh, 79h, 33h, 01h, 8Bh, 47h, 58h, 89h, 0Ch, 90h, 8Bh, 55h, 00h, 8Bh, 0CDh
    db 0FFh, 52h, 04h, 0EBh, 51h, 8Bh, 46h, 10h, 50h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 8Eh, 0F3h
    db 0FCh, 0FFh, 8Bh, 4Bh, 04h, 6Ah, 00h, 6Ah, 01h, 6Ah, 00h, 6Ah, 00h, 8Dh, 44h, 24h
    db 38h, 50h, 6Ah, 00h, 51h, 8Bh, 0CFh, 0C7h, 44h, 24h, 38h, 01h, 00h, 00h, 00h, 0E8h
    db 7Ch, 0D3h, 0FFh, 0FFh, 8Bh, 44h, 24h, 28h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h
    db 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h
    db 0FFh, 52h, 04h, 83h, 0C4h, 04h, 0F6h, 46h, 0Ch, 02h, 74h, 55h, 8Bh, 6Fh, 7Ch, 85h
    db 0EDh, 74h, 16h, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 10h, 8Bh, 4Fh, 7Ch, 8Bh, 11h, 0FFh
    db 52h, 04h, 0C7h, 47h, 7Ch, 00h, 00h, 00h, 00h, 8Bh, 4Bh, 04h, 8Bh, 46h, 08h, 8Bh
    db 56h, 04h, 8Bh, 1Eh, 50h, 03h, 0D3h, 51h, 8Dh, 44h, 32h, 14h, 50h, 8Bh, 0CFh, 0E8h
    db 5Ch, 0DBh, 0FFh, 0FFh, 85h, 0EDh, 74h, 19h, 8Bh, 47h, 7Ch, 85h, 0C0h, 75h, 12h, 8Bh
    db 55h, 00h, 8Bh, 0CDh, 0FFh, 12h, 89h, 6Fh, 7Ch, 8Bh, 45h, 00h, 8Bh, 0CDh, 0FFh, 50h
    db 04h, 8Bh, 07h, 8Bh, 4Ch, 24h, 10h, 3Bh, 0C1h, 76h, 0Ah, 2Bh, 0C1h, 50h, 8Bh, 0CFh
    db 0E8h, 4Bh, 19h, 0FDh, 0FFh, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008cf1b0@@YAXXZ ENDP

; ghidra: FUN_00ccf3c0  retail @ 0x008CF3C0 size 469
public ?d_008cf3c0@@YAXXZ
?d_008cf3c0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 7Fh, 0A4h, 05h, 01h, 50h, 8Bh, 44h
    db 24h, 18h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 85h, 0C0h, 55h, 56h
    db 57h, 8Bh, 0F9h, 75h, 08h, 0FFh, 15h, 60h, 78h, 33h, 01h, 0EBh, 0Fh, 8Bh, 00h, 83h
    db 0C0h, 08h, 50h, 0FFh, 15h, 5Ch, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h, 10h
    db 66h, 0A1h, 98h, 52h, 2Dh, 01h, 0BEh, 98h, 52h, 2Dh, 01h, 89h, 74h, 24h, 0Ch, 66h
    db 40h, 66h, 40h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 89h, 74h, 24h, 30h, 66h
    db 0A3h, 98h, 52h, 2Dh, 01h, 8Bh, 44h, 24h, 10h, 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 54h
    db 24h, 10h, 52h, 50h, 8Bh, 0CFh, 0C6h, 44h, 24h, 2Ch, 01h, 0E8h, 70h, 61h, 0FFh, 0FFh
    db 8Bh, 0E8h, 85h, 0EDh, 0Fh, 84h, 0E9h, 00h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 74h, 24h, 0Ch, 0Fh, 84h, 0BDh, 00h, 00h, 00h, 8Bh, 35h, 78h, 84h, 33h, 01h
    db 85h, 0F6h, 74h, 40h, 8Bh, 4Eh, 0Ch, 89h, 0Dh, 78h, 84h, 33h, 01h, 8Bh, 0Dh, 10h
    db 78h, 33h, 01h, 8Bh, 51h, 04h, 3Bh, 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h, 04h
    db 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 08h, 8Bh, 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h
    db 08h, 3Dh, 98h, 52h, 2Dh, 01h, 8Dh, 4Eh, 08h, 74h, 33h, 6Ah, 00h, 0E8h, 0AEh, 0F7h
    db 0FCh, 0FFh, 0EBh, 2Ah, 6Ah, 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 14h, 85h, 0C0h, 0C6h, 44h, 24h, 20h, 02h, 74h, 09h, 8Bh, 0C8h, 0E8h, 3Dh
    db 0A6h, 0FDh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0C6h, 44h, 24h, 20h, 01h, 8Bh, 0F0h, 8Bh, 44h
    db 24h, 30h, 66h, 0FFh, 00h, 8Bh, 46h, 08h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h
    db 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 52h, 04h, 83h, 0C4h, 04h, 8Bh, 44h
    db 24h, 30h, 8Bh, 54h, 24h, 2Ch, 6Ah, 00h, 6Ah, 01h, 6Ah, 01h, 56h, 8Dh, 4Ch, 24h
    db 1Ch, 51h, 89h, 46h, 08h, 8Bh, 44h, 24h, 3Ch, 52h, 50h, 8Bh, 0CFh, 0E8h, 7Eh, 0D1h
    db 0FFh, 0FFh, 0BEh, 98h, 52h, 2Dh, 01h, 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 54h, 24h, 10h
    db 52h, 55h, 8Bh, 0CFh, 0E8h, 87h, 60h, 0FFh, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 0Fh, 85h, 1Dh
    db 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 50h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 8Bh, 44h
    db 24h, 34h, 83h, 0C4h, 04h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 5Fh, 5Eh, 0C6h, 44h
    db 24h, 18h, 00h, 5Dh, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h
    db 83h, 0C4h, 04h, 8Bh, 04h, 24h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h
    db 14h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh, 8Bh, 15h, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 52h
    db 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 18h, 0C2h, 0Ch, 00h
?d_008cf3c0@@YAXXZ ENDP

; ghidra: FUN_00ccf5a0  retail @ 0x008CF5A0 size 408
_TEXT ENDS
_TEXT$d00ccf5a0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCF5A0 size 408
public ?d_008cf5a0@@YAXXZ
?d_008cf5a0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A498
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 08Bh
    db 04Ch, 024h, 01Ch, 08Bh, 054h, 024h, 018h, 055h, 056h, 08Dh, 044h, 024h, 008h, 050h, 08Bh, 044h
    db 024h, 020h, 051h, 052h, 033h, 0EDh, 050h, 089h, 06Ch, 024h, 018h
    call ?rva8CCCE0ResolveValue@@YAXPAX0PAVRva8CCCE0Value@@PAPAV1@@Z
    db 083h, 0C4h, 010h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0C7h, 044h, 024h, 024h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Dh, 04Ch, 024h, 024h, 051h, 08Bh, 04Ch, 024h, 02Ch, 089h, 06Ch, 024h, 018h
    call ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
    db 08Bh, 074h, 024h, 008h, 03Bh, 0F5h, 00Fh, 084h, 0FDh, 000h, 000h, 000h, 039h, 06Eh, 04Ch, 00Fh
    db 084h, 0F4h, 000h, 000h, 000h, 08Bh, 046h, 004h, 08Bh, 0C8h, 083h, 0E1h, 03Fh, 083h, 0F9h, 011h
    db 075h, 018h, 08Bh, 0D0h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 075h, 00Ch, 08Bh, 056h
    db 050h, 08Bh, 052h, 018h, 089h, 054h, 024h, 020h, 0EBh, 008h, 0C7h, 044h, 024h, 020h, 000h, 000h
    db 000h, 000h, 083h, 0F9h, 00Dh, 053h, 057h, 075h, 00Ch, 08Bh, 0D0h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h
    db 0F6h, 0C2h, 001h, 074h, 00Eh, 083h, 0F9h, 012h, 075h, 011h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h
    db 001h, 075h, 008h, 08Bh, 046h, 050h, 08Bh, 078h, 020h, 0EBh, 002h, 033h, 0FFh, 08Bh, 05Ch, 024h
    db 038h, 08Bh, 046h, 04Ch, 08Bh, 050h, 050h, 08Bh, 04Eh, 050h, 08Bh, 049h, 00Ch, 053h, 08Bh, 05Ch
    db 024h, 02Ch, 053h, 057h, 08Dh, 07Eh, 010h, 057h, 08Dh, 07Eh, 028h, 057h, 08Bh, 07Ch, 024h, 048h
    db 06Ah, 0FFh, 0BBh, 001h, 000h, 000h, 000h, 053h, 050h, 08Dh, 044h, 024h, 04Ch, 050h, 051h, 057h
    db 055h, 08Dh, 04Ah, 024h
    call ?bfmeSubmit1283@BfmeSubmitter1283@@QAEXHHHHHHHPAMHHHH@Z
    db 08Bh, 046h, 050h, 039h, 058h, 02Ch, 075h, 04Bh, 08Bh, 056h, 04Ch, 089h, 06Ch, 024h, 028h, 089h
    db 06Ch, 024h, 024h, 08Bh, 042h, 050h, 08Dh, 04Ch, 024h, 028h, 051h, 08Dh, 054h, 024h, 028h, 052h
    db 08Dh, 04Ch, 024h, 034h, 051h, 08Bh, 048h, 024h, 057h
    call ?bfmeQuery1279@BfmeQuery1279@@QAEXPAXHPAPAX1@Z
    db 08Bh, 054h, 024h, 028h, 08Bh, 04Ah, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch
    db 014h, 083h, 0F8h, 013h, 07Fh, 00Fh, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 084h, 0CBh, 075h, 006h, 08Bh
    db 052h, 050h, 089h, 05Ah, 02Ch, 08Bh, 00Dh
    dd ?Rva008A5380Holder@@3PADA
    call ?d_008a18c0@@YAXXZ
    db 05Fh, 05Bh, 08Bh, 044h, 024h, 024h, 066h, 0FFh, 008h, 066h, 039h, 028h, 0C7h, 044h, 024h, 014h
    db 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 00Ch, 05Eh, 05Dh, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 018h, 000h
?d_008cf5a0@@YAXXZ ENDP
_TEXT$d00ccf5a0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00ccf740  retail @ 0x008CF740 size 2353
_TEXT ENDS
_TEXT$d00ccf740 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CCF740 size 2353
public ?d_008cf740@@YAXXZ
?d_008cf740@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A50E
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 01Ch, 053h, 055h, 08Bh, 06Ch, 024h, 038h, 085h, 0EDh, 056h, 08Bh, 0F1h, 08Bh, 006h, 057h, 089h
    db 044h, 024h, 020h, 00Fh, 084h, 09Ch, 008h, 000h, 000h, 08Bh, 04Dh, 004h, 08Bh, 0C1h, 083h, 0E0h
    db 03Fh, 083h, 0F8h, 009h, 075h, 049h, 08Bh, 0D1h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h
    db 075h, 03Dh, 08Bh, 05Ch, 024h, 044h, 08Bh, 044h, 024h, 03Ch, 053h, 050h, 0FFh, 055h, 020h, 083h
    db 0C4h, 008h, 053h, 08Bh, 0CEh, 08Bh, 0F8h
    call ?bfmePopN@BfmeStackBB@@QAEXH@Z
    db 08Bh, 00Eh, 08Bh, 056h, 008h, 089h, 03Ch, 08Ah, 0FFh, 006h, 08Bh, 047h, 004h, 0C1h, 0E8h, 01Eh
    db 0A8h, 001h, 00Fh, 085h, 07Ch, 008h, 000h, 000h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 012h, 0E9h, 071h
    db 008h, 000h, 000h, 083h, 0F8h, 00Ah, 00Fh, 085h, 03Dh, 008h, 000h, 000h, 0C1h, 0E9h, 00Fh, 0F6h
    db 0D1h, 0F6h, 0C1h, 001h, 00Fh, 085h, 02Fh, 008h, 000h, 000h, 08Bh, 04Eh, 060h, 08Bh, 046h, 05Ch
    db 08Bh, 055h, 000h, 089h, 04Ch, 024h, 028h, 08Bh, 0CDh, 089h, 044h, 024h, 024h, 0FFh, 052h, 04Ch
    db 083h, 0F8h, 001h, 00Fh, 085h, 0A7h, 002h, 000h, 000h, 08Bh, 05Dh, 028h, 08Bh, 04Bh, 004h, 08Bh
    db 046h, 03Ch, 08Bh, 07Dh, 030h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 089h, 044h, 024h
    db 018h, 00Fh, 085h, 0F2h, 007h, 000h, 000h, 08Bh, 0CBh
    call ?isKind13@Rva008A0F20Header@@QBEHXZ
    db 084h, 0C0h, 074h, 00Dh, 0F7h, 043h, 060h, 000h, 000h, 00Ch, 000h, 00Fh, 084h, 0DAh, 007h, 000h
    db 000h, 08Bh, 053h, 060h, 081h, 0E2h, 000h, 000h, 00Ch, 000h, 081h, 0FAh, 000h, 000h, 008h, 000h
    db 00Fh, 084h, 0C5h, 007h, 000h, 000h, 08Bh, 047h, 010h, 089h, 046h, 05Ch, 08Bh, 04Fh, 014h, 089h
    db 04Eh, 060h, 08Bh, 045h, 020h, 085h, 0C0h, 075h, 02Dh, 06Ah, 018h
    call ?Rva008C4890@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 040h, 085h, 0C0h, 0C7h, 044h, 024h, 034h, 000h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva8CBC80Derived@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh, 08Dh, 04Eh, 00Ch, 050h
    call ?bfmeGo937E@BfmeThing937E@@QAEXPAVBfmeItem937E@@@Z
    db 08Bh, 047h, 004h, 08Bh, 04Ch, 024h, 044h, 03Bh, 0C1h, 089h, 044h, 024h, 040h, 07Ch, 004h, 089h
    db 04Ch, 024h, 040h, 033h, 0DBh, 085h, 0C0h, 00Fh, 08Eh, 083h, 000h, 000h, 000h, 08Dh, 049h, 000h
    db 03Bh, 05Ch, 024h, 040h, 07Dh, 011h, 08Bh, 016h, 08Bh, 046h, 008h, 02Bh, 0D3h, 08Bh, 04Ch, 090h
    db 0FCh, 089h, 04Ch, 024h, 010h, 0EBh, 00Ah, 08Bh, 015h
    dd ?bfmeTheCBC@@3HA
    db 089h, 054h, 024h, 010h, 08Bh, 047h, 008h, 08Bh, 004h, 098h, 050h, 08Dh, 04Ch, 024h, 018h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 045h, 028h, 06Ah, 000h, 06Ah, 001h, 06Ah, 000h, 051h, 08Dh, 054h
    db 024h, 024h, 052h, 06Ah, 000h, 050h, 08Bh, 0CEh, 0C7h, 044h, 024h, 050h, 001h, 000h, 000h, 000h
    call ?d_008cc690@@YAXXZ
    db 08Bh, 044h, 024h, 014h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 034h, 0FFh
    db 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 047h, 004h, 043h, 03Bh, 0D8h, 07Ch, 080h, 08Bh
    db 054h, 024h, 044h, 052h, 08Bh, 0CEh
    call ?bfmePopN@BfmeStackBB@@QAEXH@Z
    db 08Bh, 046h, 030h, 08Bh, 056h, 038h, 08Bh, 04Ch, 024h, 03Ch, 089h, 00Ch, 082h, 0FFh, 046h, 030h
    db 08Bh, 001h, 0FFh, 010h, 08Bh, 04Fh, 00Ch, 08Bh, 055h, 028h, 051h, 052h, 083h, 0C7h, 018h, 057h
    db 08Bh, 0CEh
    call ?d_008cced0@@YAXXZ
    db 08Bh, 046h, 030h, 08Bh, 04Eh, 038h, 08Bh, 04Ch, 081h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 0FFh
    db 04Eh, 030h, 08Bh, 046h, 03Ch, 085h, 0C0h, 00Fh, 08Eh, 0FAh, 000h, 000h, 000h, 08Bh, 04Ch, 024h
    db 018h, 03Bh, 0C1h, 00Fh, 084h, 0EEh, 000h, 000h, 000h, 02Bh, 0C1h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0B9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 089h, 04Ch, 024h, 03Ch, 085h, 0C0h, 0C7h, 044h, 024h, 034h, 002h, 000h, 000h, 000h, 00Fh, 08Eh
    db 0ADh, 000h, 000h, 000h, 08Bh, 0F8h, 0B3h, 003h, 08Bh, 046h, 03Ch, 08Bh, 04Eh, 044h, 08Bh, 04Ch
    db 081h, 0FCh, 08Bh, 041h, 004h, 083h, 0E0h, 03Fh, 083h, 0F8h, 001h, 074h, 003h, 08Bh, 049h, 020h
    db 08Bh, 041h, 008h, 083h, 0C0h, 008h, 050h, 08Dh, 04Ch, 024h, 044h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 044h, 024h, 040h, 066h, 0FFh, 000h, 08Bh, 044h, 024h, 03Ch, 066h, 0FFh, 008h, 066h, 083h
    db 038h, 000h, 088h, 05Ch, 024h, 034h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 040h, 089h, 044h, 024h, 03Ch, 066h
    db 0FFh, 008h, 066h, 083h, 038h, 000h, 0C6h, 044h, 024h, 034h, 002h, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 04Eh, 00Ch, 08Bh, 056h, 014h, 08Bh, 044h, 08Ah, 0FCh
    db 06Ah, 000h, 08Dh, 04Ch, 024h, 040h, 051h, 08Dh, 048h, 008h
    call ?d_0089d890@@YAXXZ
    db 08Bh, 056h, 03Ch, 08Bh, 046h, 044h, 08Bh, 04Ch, 090h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh
    db 04Eh, 03Ch, 049h, 04Fh, 089h, 04Eh, 03Ch, 00Fh, 085h, 05Bh, 0FFh, 0FFh, 0FFh, 08Bh, 04Ch, 024h
    db 03Ch, 066h, 0FFh, 009h, 08Bh, 0C1h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh
    db 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 04Eh, 00Ch, 08Bh, 056h, 014h, 08Bh, 04Ch, 08Ah, 0FCh
    db 08Bh, 001h, 0FFh, 050h, 004h, 08Bh, 046h, 00Ch, 08Bh, 04Ch, 024h, 024h, 08Bh, 054h, 024h, 028h
    db 048h, 089h, 046h, 00Ch, 089h, 04Eh, 05Ch, 089h, 056h, 060h, 0E9h, 094h, 005h, 000h, 000h, 08Bh
    db 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 04Ch, 083h, 0F8h, 002h, 00Fh, 085h, 083h, 005h, 000h, 000h
    db 08Bh, 07Dh, 028h, 08Bh, 04Fh, 004h, 08Bh, 05Dh, 030h, 08Bh, 046h, 03Ch, 0C1h, 0E9h, 00Fh, 0F6h
    db 0D1h, 0F6h, 0C1h, 001h, 089h, 05Ch, 024h, 040h, 089h, 044h, 024h, 018h, 00Fh, 085h, 00Ah, 005h
    db 000h, 000h, 08Bh, 0CFh
    call ?isKind13@Rva008A0F20Header@@QBEHXZ
    db 084h, 0C0h, 074h, 00Dh, 0F7h, 047h, 060h, 000h, 000h, 00Ch, 000h, 00Fh, 084h, 0F2h, 004h, 000h
    db 000h, 08Bh, 057h, 060h, 081h, 0E2h, 000h, 000h, 00Ch, 000h, 081h, 0FAh, 000h, 000h, 008h, 000h
    db 00Fh, 084h, 0DDh, 004h, 000h, 000h, 08Bh, 043h, 014h, 089h, 046h, 05Ch, 08Bh, 04Bh, 018h, 089h
    db 04Eh, 060h, 08Bh, 045h, 020h, 085h, 0C0h, 075h, 02Dh, 06Ah, 018h
    call ?Rva008C4890@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 01Ch, 085h, 0C0h, 0C7h, 044h, 024h, 034h, 004h, 000h, 000h
    db 000h, 074h, 009h, 08Bh, 0C8h
    call ??0Rva8CBC80Derived@@QAE@XZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh, 08Dh, 04Eh, 00Ch, 050h
    call ?bfmeGo937E@BfmeThing937E@@QAEXPAVBfmeItem937E@@@Z
    db 08Bh, 046h, 048h, 08Bh, 056h, 050h, 08Bh, 04Eh, 054h, 00Fh, 0AFh, 0D0h, 040h, 08Dh, 00Ch, 091h
    db 089h, 046h, 048h, 089h, 04Eh, 058h, 08Bh, 04Eh, 050h, 033h, 0C0h, 085h, 0C9h, 089h, 04Ch, 024h
    db 01Ch, 07Eh, 012h, 090h, 08Bh, 056h, 058h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 089h, 03Ch, 082h, 040h, 03Bh, 0C1h, 07Ch, 0EFh, 08Bh, 043h, 004h, 08Bh, 04Ch, 024h, 044h, 03Bh
    db 0C1h, 089h, 044h, 024h, 014h, 07Ch, 004h, 089h, 04Ch, 024h, 014h, 033h, 0DBh, 085h, 0C0h, 00Fh
    db 08Eh, 099h, 000h, 000h, 000h, 08Bh, 0FFh, 03Bh, 05Ch, 024h, 014h, 07Dh, 00Dh, 08Bh, 006h, 08Bh
    db 04Eh, 008h, 02Bh, 0C3h, 08Bh, 07Ch, 081h, 0FCh, 0EBh, 006h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 054h, 024h, 040h, 08Bh, 042h, 00Ch, 08Bh, 00Ch, 0D8h, 085h, 0C9h, 08Dh, 004h, 0D8h, 074h
    db 00Eh, 08Bh, 056h, 058h, 089h, 03Ch, 08Ah, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h, 0EBh, 04Fh, 08Bh
    db 040h, 004h, 050h, 08Dh, 04Ch, 024h, 014h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 055h, 028h, 06Ah, 000h, 06Ah, 001h, 06Ah, 000h, 057h, 08Dh, 04Ch, 024h, 020h, 051h, 06Ah
    db 000h, 052h, 08Bh, 0CEh, 0C7h, 044h, 024h, 050h, 005h, 000h, 000h, 000h
    call ?d_008cc690@@YAXXZ
    db 08Bh, 044h, 024h, 010h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 034h, 0FFh
    db 0FFh, 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 040h, 08Bh, 041h, 004h, 043h, 03Bh, 0D8h
    db 00Fh, 08Ch, 069h, 0FFh, 0FFh, 0FFh, 08Bh, 054h, 024h, 044h, 052h, 08Bh, 0CEh
    call ?bfmePopN@BfmeStackBB@@QAEXH@Z
    db 08Bh, 046h, 030h, 08Bh, 056h, 038h, 08Bh, 04Ch, 024h, 03Ch, 089h, 00Ch, 082h, 0FFh, 046h, 030h
    db 08Bh, 001h, 0FFh, 010h, 08Bh, 04Ch, 024h, 040h, 08Ah, 041h, 00Ah, 0BBh, 001h, 000h, 000h, 000h
    db 033h, 0FFh, 084h, 0C3h, 074h, 025h, 08Bh, 04Dh, 028h, 057h, 068h
    dd ?g_Va01338710String@@3VBfmeStrVKI@@A
    call ?d_0089c290@@YAXXZ
    db 08Bh, 056h, 058h, 08Bh, 0F8h, 085h, 0FFh, 089h, 07Ah, 004h, 0BBh, 002h, 000h, 000h, 000h, 074h
    db 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 010h, 08Bh, 04Ch, 024h, 040h, 0F6h, 041h, 00Ah, 004h, 074h
    db 017h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 056h, 058h, 089h, 03Ch, 09Ah, 043h, 085h, 0FFh, 074h, 006h, 08Bh, 007h, 08Bh, 0CFh, 0FFh
    db 010h, 08Bh, 04Ch, 024h, 040h, 0F6h, 041h, 00Ah, 010h, 074h, 048h, 08Bh, 054h, 024h, 03Ch, 06Ah
    db 000h, 06Ah, 001h, 06Ah, 001h, 068h
    dd g_Va01338700
    db 06Ah, 000h, 052h, 08Bh, 0CEh
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 007h, 08Bh, 047h, 004h, 084h, 0E4h, 078h, 011h, 08Bh, 04Dh, 028h
    db 06Ah, 000h, 068h
    dd g_Va01338700
    call ?d_0089c290@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 046h, 058h, 089h, 03Ch, 098h, 043h, 085h, 0FFh, 074h, 006h, 08Bh, 017h, 08Bh
    db 0CFh, 0FFh, 012h, 08Bh, 044h, 024h, 040h, 0F6h, 040h, 00Ah, 040h, 074h, 05Ah, 068h
    dd g_Va01135EC4
    db 08Dh, 04Ch, 024h, 040h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 06Ah, 000h, 08Dh, 04Ch, 024h, 040h, 051h, 08Bh, 04Dh, 028h, 0C7h, 044h, 024h, 03Ch, 006h, 000h
    db 000h, 000h
    call ?d_0089c290@@YAXXZ
    db 08Bh, 056h, 058h, 08Bh, 0F8h, 089h, 03Ch, 09Ah, 043h, 085h, 0FFh, 074h, 006h, 08Bh, 007h, 08Bh
    db 0CFh, 0FFh, 010h, 08Bh, 044h, 024h, 03Ch, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h
    db 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 054h, 024h, 040h, 08Ah, 042h, 00Ah, 084h, 0C0h
    db 079h, 063h, 068h
    dd g_Va01135EB4
    db 08Dh, 04Ch, 024h, 018h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 04Dh, 028h, 06Ah, 000h, 08Dh, 044h, 024h, 018h, 050h, 0C7h, 044h, 024h, 03Ch, 007h, 000h
    db 000h, 000h
    call ?d_0089c290@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 075h, 006h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 04Eh, 058h, 089h, 03Ch, 099h, 043h, 085h, 0FFh, 074h, 006h, 08Bh, 017h, 08Bh, 0CFh, 0FFh
    db 012h, 08Bh, 044h, 024h, 014h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 034h
    db 0FFh, 0FFh, 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 040h, 0F6h, 041h, 00Bh, 001h, 074h, 015h
    db 085h, 0FFh, 08Bh, 056h, 058h, 0A1h
    dd ?g_Va013387D8@@3PAURva00899C20Registry@@A
    db 089h, 004h, 09Ah, 074h, 006h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 012h, 08Bh, 05Ch, 024h, 040h, 08Bh
    db 043h, 010h, 08Bh, 04Dh, 028h, 050h, 051h, 08Dh, 053h, 01Ch, 052h, 08Bh, 0CEh
    call ?d_008cced0@@YAXXZ
    db 08Bh, 046h, 030h, 08Bh, 04Eh, 038h, 08Bh, 04Ch, 081h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 0FFh
    db 04Eh, 030h, 08Bh, 046h, 03Ch, 085h, 0C0h, 00Fh, 08Eh, 0F9h, 000h, 000h, 000h, 08Bh, 04Ch, 024h
    db 018h, 03Bh, 0C1h, 00Fh, 084h, 0EDh, 000h, 000h, 000h, 02Bh, 0C1h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0B9h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 089h, 04Ch, 024h, 040h, 085h, 0C0h, 0C7h, 044h, 024h, 034h, 008h, 000h, 000h, 000h, 00Fh, 08Eh
    db 0ACh, 000h, 000h, 000h, 08Bh, 0F8h, 08Bh, 046h, 03Ch, 08Bh, 04Eh, 044h, 08Bh, 04Ch, 081h, 0FCh
    db 08Bh, 041h, 004h, 083h, 0E0h, 03Fh, 083h, 0F8h, 001h, 074h, 003h, 08Bh, 049h, 020h, 08Bh, 041h
    db 008h, 083h, 0C0h, 008h, 050h, 08Dh, 04Ch, 024h, 01Ch
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 044h, 024h, 018h, 066h, 0FFh, 000h, 08Bh, 044h, 024h, 040h, 066h, 0FFh, 008h, 066h, 083h
    db 038h, 000h, 0C6h, 044h, 024h, 034h, 009h, 075h, 00Dh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 018h, 089h, 044h, 024h, 040h, 066h
    db 0FFh, 008h, 066h, 083h, 038h, 000h, 0C6h, 044h, 024h, 034h, 008h, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 04Eh, 00Ch, 08Bh, 056h, 014h, 08Bh, 044h, 08Ah, 0FCh
    db 06Ah, 000h, 08Dh, 04Ch, 024h, 044h, 051h, 08Dh, 048h, 008h
    call ?d_0089d890@@YAXXZ
    db 08Bh, 056h, 03Ch, 08Bh, 046h, 044h, 08Bh, 04Ch, 090h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh
    db 04Eh, 03Ch, 049h, 04Fh, 089h, 04Eh, 03Ch, 00Fh, 085h, 05Ah, 0FFh, 0FFh, 0FFh, 08Bh, 04Ch, 024h
    db 040h, 066h, 0FFh, 009h, 08Bh, 0C1h, 066h, 083h, 038h, 000h, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh
    db 0FFh, 0FFh, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 043h, 004h, 033h, 0FFh, 085h, 0C0h, 07Eh, 03Ah, 08Bh
    db 04Bh, 00Ch, 08Bh, 00Ch, 0F9h, 085h, 0C9h, 074h, 028h, 08Bh, 046h, 058h, 083h, 03Ch, 088h, 000h
    db 074h, 00Eh, 08Bh, 053h, 00Ch, 08Bh, 00Ch, 0FAh, 08Bh, 00Ch, 088h, 08Bh, 011h, 0FFh, 052h, 004h
    db 08Bh, 043h, 00Ch, 08Bh, 00Ch, 0F8h, 08Bh, 056h, 058h, 0A1h
    dd ?bfmeTheCBC@@3HA
    db 089h, 004h, 08Ah, 08Bh, 043h, 004h, 047h, 03Bh, 0F8h, 07Ch, 0C6h, 08Bh, 05Ch, 024h, 01Ch, 033h
    db 0FFh, 085h, 0DBh, 07Eh, 030h, 0BDh, 0FFh, 00Fh, 000h, 000h, 08Bh, 04Eh, 058h, 08Bh, 004h, 0B9h
    db 066h, 085h, 068h, 006h, 08Dh, 00Ch, 0B9h, 074h, 00Bh, 085h, 0C0h, 074h, 007h, 08Bh, 0C8h, 08Bh
    db 011h, 0FFh, 052h, 004h, 08Bh, 046h, 058h, 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 089h, 00Ch, 0B8h, 047h, 03Bh, 0FBh, 07Ch, 0D5h, 08Bh, 046h, 048h, 085h, 0C0h, 075h, 005h, 08Bh
    db 046h, 054h, 0EBh, 00Fh, 08Bh, 056h, 054h, 048h, 089h, 046h, 048h, 048h, 00Fh, 0AFh, 046h, 050h
    db 08Dh, 004h, 082h, 089h, 046h, 058h, 08Bh, 046h, 00Ch, 08Bh, 04Eh, 014h, 08Bh, 04Ch, 081h, 0FCh
    db 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 046h, 00Ch, 08Bh, 04Ch, 024h, 028h, 048h, 089h, 046h, 00Ch
    db 08Bh, 044h, 024h, 024h, 089h, 046h, 05Ch, 089h, 04Eh, 060h, 0EBh, 057h, 08Bh, 054h, 024h, 044h
    db 052h, 08Bh, 0CEh
    call ?bfmePopN@BfmeStackBB@@QAEXH@Z
    db 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 006h, 08Bh, 056h, 008h, 089h, 00Ch, 082h, 0FFh, 006h, 08Bh, 041h, 004h, 0C1h, 0E8h, 01Eh
    db 0A8h, 001h, 075h, 031h, 08Bh, 011h, 0FFh, 012h, 0EBh, 02Bh, 08Bh, 044h, 024h, 044h, 08Bh, 0CEh
    db 050h
    call ?bfmePopN@BfmeStackBB@@QAEXH@Z
    db 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 016h, 08Bh, 046h, 008h, 089h, 00Ch, 090h, 0FFh, 006h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh
    db 0F6h, 0C2h, 001h, 075h, 004h, 08Bh, 001h, 0FFh, 010h, 08Bh, 04Eh, 07Ch, 085h, 0C9h, 08Bh, 006h
    db 074h, 01Ch, 08Bh, 04Ch, 024h, 020h, 08Bh, 054h, 024h, 044h, 08Bh, 0F9h, 02Bh, 0FAh, 03Bh, 0C7h
    db 07Eh, 00Ch, 02Bh, 0C1h, 003h, 0C2h, 050h, 08Bh, 0CEh
    call ?bfmePop1232@BfmeA1232@@QAEXH@Z
    db 08Bh, 04Ch, 024h, 02Ch, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
    db 0C4h, 028h, 0C2h, 00Ch, 000h
?d_008cf740@@YAXXZ ENDP
_TEXT$d00ccf740 ENDS
_TEXT SEGMENT

; ghidra: FUN_00cd0b00  retail @ 0x008D0B00 size 352
_TEXT ENDS
_TEXT$d00cd0b00 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CD0B00 size 352
public ?d_008d0b00@@YAXXZ
?d_008d0b00@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A628
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 008h, 055h, 056h, 08Bh, 074h, 024h, 020h, 08Bh, 006h, 08Bh, 04Eh, 008h, 057h, 08Bh, 07Ch, 081h
    db 0FCh, 08Bh, 04Ch, 081h, 0F8h
    call ?toInteger@AptValue@@QBEHXZ
    db 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 089h, 044h, 024h, 010h, 0C7h, 044h, 024h, 024h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 08Bh, 047h, 004h, 08Bh, 0C8h, 033h, 0EDh, 083h, 0E1h, 03Fh, 080h, 0F9h, 016h, 089h, 06Ch, 024h
    db 01Ch, 089h, 06Ch, 024h, 00Ch, 075h, 013h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 00Ah
    db 055h, 08Bh, 0CFh
    call ?bfmeAt@Gen_008B8E50@@QBEHH@Z
    db 08Bh, 0F8h, 08Bh, 04Fh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 001h, 074h, 005h, 083h
    db 0F8h, 02Ah, 075h, 050h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 046h, 083h, 0F8h
    db 001h, 074h, 003h, 08Bh, 07Fh, 020h, 08Dh, 054h, 024h, 024h, 052h, 08Dh, 044h, 024h, 010h, 050h
    db 083h, 0C7h, 008h, 057h, 08Bh, 07Ch, 024h, 034h, 08Bh, 04Fh, 008h, 08Bh, 057h, 004h, 051h, 052h
    call ?rva008C6320@@YA_NPAVBfmeNode1220@@0PBVBfmeStrVKI@@PAPAV1@PAV2@@Z
    db 08Bh, 04Fh, 008h, 083h, 0C4h, 014h, 055h, 08Bh, 06Ch, 024h, 010h, 06Ah, 001h, 06Ah, 001h, 08Dh
    db 044h, 024h, 030h, 050h, 051h, 055h, 08Bh, 0CEh
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0F8h, 08Bh, 017h, 053h, 08Bh, 0CFh, 0FFh, 012h, 0BBh, 001h, 000h, 000h, 000h, 08Dh, 064h
    db 024h, 000h, 08Bh, 006h, 08Bh, 04Eh, 008h, 02Bh, 0C3h, 08Bh, 00Ch, 081h, 08Bh, 051h, 004h, 0C1h
    db 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h, 043h, 083h, 0FBh, 002h
    db 07Eh, 0E0h, 08Bh, 00Eh, 083h, 0C1h, 0FEh, 085h, 0EDh, 089h, 00Eh, 05Bh, 074h, 004h, 08Bh, 0C5h
    db 0EBh, 007h, 08Bh, 04Ch, 024h, 028h, 08Bh, 041h, 004h, 08Bh, 054h, 024h, 010h, 052h, 057h, 050h
    db 08Bh, 0CEh
    call ?d_008cf740@@YAXXZ
    db 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 004h, 08Bh, 044h, 024h, 024h, 066h, 0FFh, 008h, 066h, 083h
    db 038h, 000h, 05Fh, 05Eh, 0C7h, 044h, 024h, 014h, 0FFh, 0FFh, 0FFh, 0FFh, 05Dh, 075h, 00Dh, 08Bh
    db 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 008h, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 014h, 0C3h
?d_008d0b00@@YAXXZ ENDP
_TEXT$d00cd0b00 ENDS
_TEXT SEGMENT

; ghidra: FUN_00cd0d80  retail @ 0x008D0D80 size 394
public ?d_008d0d80@@YAXXZ
?d_008d0d80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 68h, 0A6h, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 06h, 8Bh, 4Eh, 08h
    db 8Bh, 4Ch, 81h, 0FCh, 57h, 0E8h, 56h, 75h, 0FCh, 0FFh, 8Bh, 16h, 8Bh, 0F8h, 8Bh, 46h
    db 08h, 8Bh, 4Ch, 90h, 0FCh, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h
    db 8Bh, 01h, 0FFh, 50h, 04h, 8Bh, 16h, 8Bh, 44h, 24h, 20h, 6Ah, 01h, 4Ah, 6Ah, 00h
    db 89h, 16h, 8Bh, 48h, 08h, 8Bh, 50h, 04h, 68h, 10h, 86h, 33h, 01h, 51h, 52h, 8Bh
    db 0CEh, 0E8h, 9Ah, 0F2h, 0FFh, 0FFh, 8Bh, 0C8h, 85h, 0C9h, 89h, 4Ch, 24h, 08h, 0Fh, 84h
    db 0DBh, 00h, 00h, 00h, 85h, 0FFh, 0Fh, 8Eh, 0A0h, 00h, 00h, 00h, 53h, 8Dh, 59h, 08h
    db 89h, 7Ch, 24h, 24h, 8Bh, 06h, 8Bh, 4Eh, 08h, 8Bh, 7Ch, 81h, 0FCh, 8Bh, 4Ch, 81h
    db 0F8h, 66h, 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 20h, 98h, 52h, 2Dh, 01h
    db 8Dh, 44h, 24h, 20h, 50h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0E8h, 8Eh, 77h
    db 0FCh, 0FFh, 57h, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CBh, 0E8h, 51h, 0CAh, 0FCh, 0FFh, 0BFh
    db 01h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 46h, 08h, 2Bh, 0D7h, 8Bh, 0Ch, 90h, 8Bh, 51h
    db 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h, 05h, 8Bh, 01h, 0FFh, 50h, 04h, 47h, 83h
    db 0FFh, 02h, 7Eh, 0E0h, 8Bh, 3Eh, 8Bh, 44h, 24h, 20h, 83h, 0C7h, 0FEh, 89h, 3Eh, 66h
    db 0FFh, 08h, 66h, 83h, 38h, 00h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Dh
    db 8Bh, 0Dh, 30h, 7Ah, 33h, 01h, 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 0FFh, 4Ch, 24h
    db 24h, 0Fh, 85h, 6Dh, 0FFh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 5Bh, 8Bh, 16h, 8Bh, 46h
    db 08h, 89h, 0Ch, 90h, 0FFh, 06h, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh, 0F6h, 0C2h, 01h, 75h
    db 08h, 8Bh, 01h, 0FFh, 10h, 8Bh, 4Ch, 24h, 08h, 8Bh, 11h, 0FFh, 52h, 04h, 5Fh, 5Eh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Dh
    db 04h, 3Fh, 50h, 8Bh, 0CEh, 0E8h, 0D6h, 4Ch, 0FFh, 0FFh, 8Bh, 0Dh, 0BCh, 79h, 33h, 01h
    db 8Bh, 16h, 8Bh, 46h, 08h, 89h, 0Ch, 90h, 0FFh, 06h, 8Bh, 51h, 04h, 0C1h, 0EAh, 1Eh
    db 0F6h, 0C2h, 01h, 75h, 04h, 8Bh, 01h, 0FFh, 10h, 8Bh, 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_008d0d80@@YAXXZ ENDP

; ghidra: FUN_00cd0f10  retail @ 0x008D0F10 size 1579
_TEXT ENDS
_TEXT$d00cd0f10 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CD0F10 size 1579
public ?d_008d0f10@@YAXXZ
?d_008d0f10@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105A698
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 014h, 053h, 055h, 056h, 08Bh, 074h, 024h, 030h, 08Bh, 006h, 08Bh, 056h, 008h, 08Bh, 04Ch, 082h
    db 0FCh, 08Bh, 06Ch, 082h, 0F4h, 057h, 08Bh, 07Ch, 082h, 0F8h, 066h, 0FFh, 005h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0C7h, 044h, 024h, 018h
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 0A1h
    dd ?bfmeTheCBC@@3HA
    db 033h, 0DBh, 03Bh, 0C8h, 089h, 05Ch, 024h, 02Ch, 088h, 05Ch, 024h, 034h, 089h, 05Ch, 024h, 01Ch
    db 075h, 07Ch, 068h
    dd g_Va01135E30
    db 08Dh, 04Ch, 024h, 020h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 044h, 024h, 01Ch, 066h, 0FFh, 000h, 08Bh, 044h, 024h, 018h, 066h, 0FFh, 008h, 066h, 039h
    db 018h, 0C6h, 044h, 024h, 02Ch, 001h, 075h, 00Ch, 050h, 0A1h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 0FFh, 050h, 004h, 083h, 0C4h, 004h, 08Bh, 044h, 024h, 01Ch, 089h, 044h, 024h, 018h, 066h, 0FFh
    db 008h, 066h, 083h, 038h, 000h, 0C6h, 044h, 024h, 02Ch, 000h, 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 047h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h
    db 0FAh, 01Ch, 075h, 012h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 009h, 08Bh, 05Fh, 018h
    db 089h, 05Ch, 024h, 01Ch, 0EBh, 012h, 08Bh, 0DFh, 089h, 05Ch, 024h, 01Ch, 0EBh, 00Ah, 08Dh, 044h
    db 024h, 018h, 050h
    call ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
    db 08Bh, 0CDh
    call ?toInteger@AptValue@@QBEHXZ
    db 08Bh, 04Fh, 004h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 089h, 044h, 024h, 014h, 00Fh
    db 085h, 0CFh, 004h, 000h, 000h, 08Bh, 054h, 024h, 038h, 08Bh, 04Ah, 004h, 08Bh, 046h, 030h, 08Bh
    db 056h, 038h, 089h, 00Ch, 082h, 0FFh, 046h, 030h, 08Bh, 001h, 0FFh, 010h, 08Bh, 00Eh, 08Bh, 056h
    db 008h, 08Bh, 04Ch, 08Ah, 0FCh, 08Bh, 041h, 004h, 0C1h, 0E8h, 01Eh, 0A8h, 001h, 075h, 005h, 08Bh
    db 011h, 0FFh, 052h, 004h, 08Bh, 00Eh, 049h, 089h, 00Eh, 08Bh, 0C1h, 08Bh, 04Eh, 008h, 08Bh, 04Ch
    db 081h, 0FCh, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh
    db 050h, 004h, 08Bh, 00Eh, 049h, 089h, 00Eh, 08Bh, 0C1h, 08Bh, 04Eh, 008h, 08Bh, 04Ch, 081h, 0FCh
    db 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h
    db 08Bh, 00Eh, 049h, 085h, 0DBh, 089h, 00Eh, 074h, 008h, 03Bh, 01Dh
    dd ?bfmeTheCBC@@3HA
    db 075h, 01Bh, 06Ah, 000h, 06Ah, 001h, 06Ah, 001h, 08Dh, 04Ch, 024h, 024h, 051h, 06Ah, 000h, 057h
    db 08Bh, 0CEh
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0D8h, 089h, 05Ch, 024h, 01Ch, 085h, 0DBh, 074h, 011h, 08Bh, 053h, 004h, 0C1h, 0EAh, 00Fh
    db 0F6h, 0D2h, 0F6h, 0C2h, 001h, 00Fh, 084h, 0B0h, 001h, 000h, 000h, 08Bh, 044h, 024h, 018h, 083h
    db 0C0h, 008h, 068h
    dd g_Va01137314
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 01Dh, 08Bh, 04Ch, 024h, 018h, 083h, 0C1h, 008h, 068h
    dd g_Va0113730C
    db 051h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 07Ah, 001h, 000h, 000h, 08Bh, 04Dh, 004h, 08Bh, 0C1h
    db 083h, 0E0h, 03Fh, 083h, 0F8h, 007h, 089h, 07Ch, 024h, 01Ch, 075h, 010h, 08Bh, 0D1h, 0C1h, 0EAh
    db 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 00Fh, 084h, 080h, 000h, 000h, 000h, 083h, 0F8h, 006h, 075h
    db 00Ah, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 074h, 071h, 08Bh, 006h, 08Bh, 04Eh, 008h
    db 08Bh, 04Ch, 081h, 0FCh, 08Bh, 0FDh
    call ?toInteger@AptValue@@QBEHXZ
    db 08Bh, 0D8h, 083h, 0FBh, 001h, 089h, 05Ch, 024h, 014h, 07Eh, 039h, 08Bh, 00Eh, 08Bh, 06Eh, 008h
    db 08Bh, 044h, 08Dh, 0F8h, 085h, 0C0h, 074h, 00Fh, 08Bh, 050h, 004h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h
    db 0F6h, 0C2h, 001h, 075h, 002h, 08Bh, 0F8h, 08Bh, 04Ch, 08Dh, 0FCh, 08Bh, 041h, 004h, 0C1h, 0E8h
    db 01Eh, 0A8h, 001h, 075h, 005h, 08Bh, 011h, 0FFh, 052h, 004h, 08Bh, 00Eh, 049h, 04Bh, 089h, 00Eh
    db 089h, 05Ch, 024h, 014h, 08Bh, 006h, 08Bh, 04Eh, 008h, 08Bh, 04Ch, 081h, 0FCh, 08Bh, 051h, 004h
    db 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h, 0FFh, 00Eh, 0EBh
    db 04Fh, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 07Eh, 041h, 08Bh, 00Eh, 08Bh, 056h, 008h, 08Bh, 04Ch
    db 08Ah, 0FCh, 085h, 0C9h, 074h, 00Eh, 08Bh, 041h, 004h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h
    db 08Bh, 0F9h, 074h, 006h, 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h, 005h, 08Bh, 001h, 0FFh, 050h, 004h
    db 08Bh, 00Eh, 08Bh, 044h, 024h, 014h, 049h, 048h, 089h, 00Eh, 089h, 044h, 024h, 014h, 0EBh, 006h
    db 08Bh, 03Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 04Ch, 024h, 018h, 083h, 0C1h, 008h, 068h
    dd g_Va01137314
    db 051h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 071h, 08Bh, 046h, 008h, 08Bh, 016h, 08Bh, 06Ch, 090h, 0FCh
    db 08Bh, 045h, 004h, 08Bh, 0C8h, 083h, 0E1h, 03Fh, 080h, 0F9h, 016h, 075h, 05Bh, 0C1h, 0E8h, 00Fh
    db 0F6h, 0D0h, 0A8h, 001h, 075h, 052h, 08Bh, 055h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h
    db 008h, 08Bh, 045h, 000h, 08Bh, 0CDh, 0FFh, 050h, 004h, 0FFh, 00Eh, 08Bh, 045h, 028h, 08Bh, 04Ch
    db 024h, 014h, 08Dh, 058h, 0FFh, 085h, 0DBh, 08Dh, 054h, 001h, 0FFh, 089h, 054h, 024h, 014h, 07Ch
    db 027h, 08Bh, 0FFh, 08Bh, 045h, 020h, 08Bh, 00Ch, 098h, 08Bh, 016h, 08Bh, 046h, 008h, 083h, 0E1h
    db 0FEh, 089h, 00Ch, 090h, 0FFh, 006h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh, 0F6h, 0C2h, 001h, 075h
    db 004h, 08Bh, 001h, 0FFh, 010h, 04Bh, 079h, 0DBh, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 01Ch, 085h
    db 0C0h, 00Fh, 084h, 0E7h, 000h, 000h, 000h, 08Bh, 046h, 018h, 085h, 0C0h, 08Bh, 0DFh, 075h, 05Bh
    db 08Bh, 06Ch, 024h, 038h, 03Bh, 07Dh, 010h, 00Fh, 085h, 09Dh, 000h, 000h, 000h, 068h
    dd g_Va01132714
    db 08Dh, 04Ch, 024h, 024h
    call ?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z
    db 08Bh, 04Dh, 004h, 06Ah, 000h, 06Ah, 001h, 06Ah, 001h, 08Dh, 044h, 024h, 02Ch, 050h, 06Ah, 000h
    db 051h, 08Bh, 0CEh, 0C6h, 044h, 024h, 044h, 002h
    call ?d_008cc940@@YAXXZ
    db 08Bh, 0D8h, 08Bh, 044h, 024h, 020h, 066h, 0FFh, 008h, 066h, 083h, 038h, 000h, 0C6h, 044h, 024h
    db 02Ch, 000h, 075h, 05Eh, 08Bh, 015h
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 052h, 004h, 083h, 0C4h, 004h, 0EBh, 04Fh, 08Bh, 046h, 018h, 08Bh, 04Eh, 020h, 08Bh
    db 04Ch, 081h, 0FCh, 08Bh, 057h, 004h, 08Bh, 0C2h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Ch, 07Ch, 014h
    db 083h, 0F8h, 013h, 07Fh, 00Fh, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 075h, 005h, 039h
    db 04Fh, 04Ch, 074h, 024h, 03Bh, 0F9h, 074h, 020h, 08Bh, 011h, 0FFh, 052h, 018h, 085h, 0C0h, 074h
    db 017h, 08Bh, 040h, 008h, 083h, 0E0h, 0FEh, 074h, 00Fh, 03Bh, 0C7h, 074h, 03Fh, 08Bh, 010h, 08Bh
    db 0C8h, 0FFh, 052h, 018h, 085h, 0C0h, 075h, 0E9h, 08Bh, 043h, 004h, 08Bh, 0C8h, 083h, 0E1h, 03Fh
    db 080h, 0F9h, 01Bh, 0C6h, 044h, 024h, 034h, 001h, 075h, 010h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h
    db 001h, 075h, 007h, 081h, 04Bh, 01Ch, 000h, 002h, 000h, 000h, 08Bh, 056h, 018h, 08Bh, 046h, 020h
    db 089h, 01Ch, 090h, 0FFh, 046h, 018h, 08Bh, 013h, 08Bh, 0CBh, 0FFh, 012h, 033h, 0C0h, 066h, 08Bh
    db 047h, 006h, 0C6h, 044h, 024h, 013h, 000h, 025h, 0FFh, 00Fh, 000h, 000h, 083h, 0F8h, 001h, 075h
    db 00Bh, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 012h, 0C6h, 044h, 024h, 013h, 001h, 08Bh, 0CFh
    call ?rva00899C20@Rva00899C20Node@@QAEHXZ
    db 085h, 0C0h, 074h, 074h, 03Bh, 03Dh
    dd g_Va013379C0
    db 075h, 00Ah, 08Bh, 046h, 030h, 08Bh, 04Eh, 038h, 08Bh, 07Ch, 081h, 0F8h, 08Bh, 054h, 024h, 038h
    db 03Bh, 07Ah, 010h, 075h, 04Dh, 08Bh, 06Ch, 024h, 01Ch, 08Bh, 045h, 004h, 08Bh, 0C8h, 083h, 0E1h
    db 03Fh, 080h, 0F9h, 00Ah, 075h, 034h, 0C1h, 0E8h, 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 02Bh, 08Bh
    db 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 04Ch, 08Bh, 054h, 024h, 014h, 08Bh, 05Dh, 028h, 083h, 0F8h
    db 001h, 08Bh, 044h, 024h, 038h, 08Bh, 048h, 004h, 052h, 055h, 089h, 04Dh, 028h, 057h, 08Bh, 0CEh
    call ?d_008cf740@@YAXXZ
    db 089h, 05Dh, 028h, 0EBh, 026h, 08Bh, 044h, 024h, 014h, 050h, 055h, 0EBh, 016h, 08Bh, 04Ch, 024h
    db 014h, 08Bh, 054h, 024h, 01Ch, 051h, 052h, 0EBh, 00Ah, 08Bh, 044h, 024h, 014h, 08Bh, 04Ch, 024h
    db 01Ch, 050h, 051h, 08Bh, 0CEh, 057h
    call ?d_008cf740@@YAXXZ
    db 080h, 07Ch, 024h, 034h, 001h, 075h, 039h, 08Bh, 056h, 018h, 08Bh, 046h, 020h, 08Bh, 04Ch, 090h
    db 0FCh, 08Bh, 041h, 004h, 08Bh, 0D0h, 083h, 0E2h, 03Fh, 080h, 0FAh, 01Bh, 075h, 010h, 0C1h, 0E8h
    db 00Fh, 0F6h, 0D0h, 0A8h, 001h, 075h, 007h, 081h, 061h, 01Ch, 0FFh, 0FDh, 0FFh, 0FFh, 08Bh, 046h
    db 018h, 08Bh, 04Eh, 020h, 08Bh, 04Ch, 081h, 0FCh, 08Bh, 011h, 0FFh, 052h, 004h, 0FFh, 04Eh, 018h
    db 08Ah, 044h, 024h, 013h, 084h, 0C0h, 074h, 007h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 004h, 08Bh
    db 00Eh, 08Bh, 056h, 008h, 08Bh, 044h, 08Ah, 0FCh, 03Bh, 005h
    dd ?bfmeTheCBC@@3HA
    db 074h, 058h, 08Bh, 07Fh, 004h, 08Bh, 0C7h, 083h, 0E0h, 03Fh, 03Ch, 016h, 075h, 04Ch, 08Bh, 0CFh
    db 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 040h, 08Bh, 054h, 024h, 018h, 083h, 0C2h
    db 008h, 068h
    dd g_Va01136D54
    db 052h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 019h, 08Bh, 044h, 024h, 018h, 083h, 0C0h, 008h, 068h
    dd g_Va01136D44
    db 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 00Eh, 08Bh, 00Eh, 08Bh, 056h, 008h, 08Bh, 04Ch, 08Ah, 0FCh
    db 08Bh, 001h, 0FFh, 050h, 004h, 08Bh, 04Eh, 030h, 08Bh, 056h, 038h, 08Bh, 04Ch, 08Ah, 0FCh, 08Bh
    db 001h, 0FFh, 050h, 004h, 0FFh, 04Eh, 030h, 0EBh, 02Eh, 08Bh, 04Ch, 024h, 014h, 083h, 0C1h, 003h
    db 051h, 08Bh, 0CEh
    call ?bfmePop1232@BfmeA1232@@QAEXH@Z
    db 08Bh, 00Dh
    dd ?bfmeTheCBC@@3HA
    db 08Bh, 016h, 08Bh, 046h, 008h, 089h, 00Ch, 090h, 0FFh, 006h, 08Bh, 051h, 004h, 0C1h, 0EAh, 01Eh
    db 0F6h, 0C2h, 001h, 075h, 004h, 08Bh, 001h, 0FFh, 010h, 08Bh, 044h, 024h, 018h, 066h, 0FFh, 008h
    db 066h, 083h, 038h, 000h, 05Fh, 05Eh, 05Dh, 0C7h, 044h, 024h, 020h, 0FFh, 0FFh, 0FFh, 0FFh, 05Bh
    db 075h, 00Dh, 08Bh, 00Dh
    dd ?Rva00892ED0ReleaseTable@@3PAP6AXPAX@ZA
    db 050h, 0FFh, 051h, 004h, 083h, 0C4h, 004h, 08Bh, 04Ch, 024h, 014h, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 020h, 0C3h
?d_008d0f10@@YAXXZ ENDP
_TEXT$d00cd0f10 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
