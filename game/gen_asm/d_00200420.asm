.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Factory0040A260@@3PAVThingFactory@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA:BYTE
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_0000d990@@YAXXZ:NEAR
EXTERN ?j_0001011d@@YAXXZ:NEAR
EXTERN ?j_00010f91@@YAXXZ:NEAR
EXTERN ?j_0001336d@@YAXXZ:NEAR
EXTERN ?j_00014506@@YAXXZ:NEAR
EXTERN ?j_0001b94b@@YAXXZ:NEAR
EXTERN ?j_0001d0de@@YAXXZ:NEAR
EXTERN ?j_0001f253@@YAXXZ:NEAR
EXTERN ?j_0002191d@@YAXXZ:NEAR
EXTERN ?j_000245e6@@YAXXZ:NEAR
EXTERN ?j_00028560@@YAXXZ:NEAR
EXTERN ?j_0002a54a@@YAXXZ:NEAR
EXTERN ?j_0002a982@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00032dee@@YAXXZ:NEAR
EXTERN ?j_000357d8@@YAXXZ:NEAR
EXTERN ?j_0003a1a7@@YAXXZ:NEAR
EXTERN ?j_0003e126@@YAXXZ:NEAR
EXTERN ?j_00040246@@YAXXZ:NEAR
EXTERN ?j_0004494a@@YAXXZ:NEAR
EXTERN ?j_00048135@@YAXXZ:NEAR
EXTERN ?j_0004a327@@YAXXZ:NEAR
EXTERN __real@43fa0000:BYTE
EXTERN __real@4f800000:BYTE
EXTERN g_Va0100C30B:NEAR
_TEXT SEGMENT

; ghidra: FUN_00600420  retail @ 0x00200420 size 824
public ?d_00200420@@YAXXZ
?d_00200420@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 55h, 8Bh, 0E9h, 56h, 8Bh, 75h, 0F8h, 8Bh, 06h, 8Bh, 9Eh, 04h
    db 02h, 00h, 00h, 57h, 8Bh, 0BEh, 00h, 02h, 00h, 00h, 8Bh, 0CEh, 0FFh, 50h, 28h, 85h
    db 0DBh, 8Bh, 4Dh, 0F4h, 89h, 44h, 24h, 10h, 89h, 4Ch, 24h, 14h, 0Fh, 84h, 0F9h, 02h
    db 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0F1h, 02h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 0E9h, 02h
    db 00h, 00h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 10h, 0D9h, 5Ch, 24h, 18h, 8Bh, 45h, 10h
    db 85h, 0C0h, 0Fh, 9Fh, 0C1h, 84h, 0C9h, 0Fh, 84h, 0D3h, 00h, 00h, 00h, 48h, 85h, 0C0h
    db 89h, 45h, 10h, 7Eh, 1Bh, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 75h, 12h, 8Bh, 03h
    db 8Bh, 0CBh, 0FFh, 90h, 80h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 9Fh, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 10h, 0F6h, 81h, 64h, 02h, 00h, 00h, 04h, 0Fh, 84h, 87h, 00h, 00h
    db 00h, 0F6h, 86h, 24h, 01h, 00h, 00h, 04h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h
    db 83h, 0E0h, 0FBh, 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 4Dh, 14h, 0E2h, 0FFh
    db 0F6h, 86h, 24h, 01h, 00h, 00h, 08h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h
    db 0E0h, 0F7h, 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 2Eh, 14h, 0E2h, 0FFh, 0F6h
    db 86h, 24h, 01h, 00h, 00h, 10h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h
    db 0EFh, 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 0Fh, 14h, 0E2h, 0FFh, 0F6h, 86h
    db 24h, 01h, 00h, 00h, 20h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0DFh
    db 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 0F0h, 13h, 0E2h, 0FFh, 8Bh, 4Ch, 24h
    db 10h, 6Ah, 00h, 0E8h, 01h, 0CFh, 0E2h, 0FFh, 0C7h, 45h, 10h, 00h, 00h, 00h, 00h, 8Bh
    db 7Ch, 24h, 14h, 8Ah, 47h, 20h, 84h, 0C0h, 0Fh, 84h, 0E8h, 01h, 00h, 00h, 0EBh, 04h
    db 8Bh, 7Ch, 24h, 14h, 8Bh, 13h, 8Bh, 0CBh, 0FFh, 92h, 80h, 01h, 00h, 00h, 84h, 0C0h
    db 75h, 0Bh, 8Ah, 47h, 21h, 84h, 0C0h, 0Fh, 84h, 0C9h, 01h, 00h, 00h, 0D9h, 44h, 24h
    db 18h, 0D8h, 5Dh, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 0B7h, 01h, 00h, 00h, 8Bh
    db 5Ch, 24h, 10h, 8Dh, 8Bh, 50h, 02h, 00h, 00h, 68h, 0A2h, 00h, 00h, 00h, 89h, 4Ch
    db 24h, 20h, 0E8h, 0D6h, 60h, 0E0h, 0FFh, 84h, 0C0h, 0Fh, 84h, 85h, 00h, 00h, 00h, 0F6h
    db 86h, 24h, 01h, 00h, 00h, 04h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h
    db 0FBh, 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 5Fh, 13h, 0E2h, 0FFh, 0F6h, 86h
    db 24h, 01h, 00h, 00h, 08h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0F7h
    db 8Bh, 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 40h, 13h, 0E2h, 0FFh, 0F6h, 86h, 24h
    db 01h, 00h, 00h, 10h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0EFh, 8Bh
    db 0CEh, 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 21h, 13h, 0E2h, 0FFh, 0F6h, 86h, 24h, 01h
    db 00h, 00h, 20h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0DFh, 8Bh, 0CEh
    db 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 02h, 13h, 0E2h, 0FFh, 6Ah, 00h, 8Bh, 0CBh, 0E8h
    db 15h, 0CEh, 0E2h, 0FFh, 0D9h, 45h, 14h, 0D8h, 64h, 24h, 18h, 0D8h, 57h, 1Ch, 0DFh, 0E0h
    db 0F6h, 0C4h, 01h, 75h, 09h, 0DDh, 0D8h, 0BFh, 02h, 00h, 00h, 00h, 0EBh, 23h, 0D8h, 57h
    db 18h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 75h, 09h, 0DDh, 0D8h, 0BFh, 01h, 00h, 00h, 00h, 0EBh
    db 10h, 0D8h, 5Fh, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 0Fh, 85h, 0D7h, 00h, 00h, 00h, 33h
    db 0FFh, 8Bh, 5Ch, 24h, 14h, 8Bh, 44h, 0BBh, 08h, 85h, 0C0h, 89h, 45h, 10h, 0Fh, 8Eh
    db 0C2h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 1Ch, 68h, 0A2h, 00h, 00h, 00h, 0E8h, 0EBh, 5Fh
    db 0E0h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0ACh, 00h, 00h, 00h, 0F6h, 86h, 24h, 01h, 00h, 00h
    db 04h, 75h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0C8h, 04h, 8Bh, 0CEh, 89h, 86h
    db 24h, 01h, 00h, 00h, 0E8h, 74h, 12h, 0E2h, 0FFh, 83h, 0EFh, 00h, 74h, 2Eh, 4Fh, 74h
    db 17h, 4Fh, 75h, 47h, 0F6h, 86h, 24h, 01h, 00h, 00h, 20h, 75h, 3Eh, 8Bh, 86h, 24h
    db 01h, 00h, 00h, 83h, 0C8h, 20h, 0EBh, 26h, 0F6h, 86h, 24h, 01h, 00h, 00h, 10h, 75h
    db 2Ah, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0C8h, 10h, 0EBh, 12h, 0F6h, 86h, 24h, 01h
    db 00h, 00h, 08h, 75h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0C8h, 08h, 8Bh, 0CEh
    db 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 22h, 12h, 0E2h, 0FFh, 8Bh, 0CEh, 0E8h, 0E2h, 0F1h
    db 0E0h, 0FFh, 85h, 0C0h, 74h, 09h, 8Bh, 10h, 6Ah, 00h, 8Bh, 0C8h, 0FFh, 52h, 08h, 8Ah
    db 43h, 21h, 84h, 0C0h, 74h, 15h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 48h, 3Ch, 03h, 4Dh
    db 10h, 51h, 6Ah, 04h, 8Bh, 0CEh, 0E8h, 1Fh, 2Fh, 0E3h, 0FFh, 8Bh, 4Ch, 24h, 10h, 6Ah
    db 00h, 0E8h, 03h, 0CDh, 0E2h, 0FFh, 8Bh, 54h, 24h, 18h, 89h, 55h, 14h, 0F6h, 86h, 44h
    db 03h, 00h, 00h, 01h, 0B8h, 01h, 00h, 00h, 00h, 74h, 05h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh
    db 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 10h, 0C3h
?d_00200420@@YAXXZ ENDP

; ghidra: FUN_00600840  retail @ 0x00200840 size 25
public ?d_00200840@@YAXXZ
?d_00200840@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ECh, 4Ch, 0Ah, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0FAh, 73h, 0E4h, 0FFh
?d_00200840@@YAXXZ ENDP

; ghidra: FUN_00600870  retail @ 0x00200870 size 25
public ?d_00200870@@YAXXZ
?d_00200870@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ECh, 4Ch, 0Ah, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0CAh, 73h, 0E4h, 0FFh
?d_00200870@@YAXXZ ENDP

; ghidra: FUN_00601270  retail @ 0x00201270 size 265
public ?d_00201270@@YAXXZ
?d_00201270@@YAXXZ PROC
    db 51h, 55h, 8Bh, 0E9h, 8Bh, 45h, 04h, 56h, 2Bh, 45h, 00h, 57h, 8Bh, 7Ch, 24h, 20h
    db 0C1h, 0F8h, 02h, 3Bh, 0C7h, 89h, 44h, 24h, 0Ch, 8Dh, 4Ch, 24h, 20h, 72h, 04h, 8Dh
    db 4Ch, 24h, 0Ch, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 0Ch, 74h, 2Bh, 8Dh, 04h, 8Dh
    db 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h, 7Fh, 0Ch, 68h
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 20h, 0EBh, 16h, 0E8h, 81h, 0D2h, 62h, 00h, 83h
    db 0C4h, 04h, 89h, 44h, 24h, 20h, 0EBh, 08h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h
    db 8Bh, 45h, 00h, 53h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0D8h, 75h, 06h, 8Bh, 44h, 24h, 24h
    db 0EBh, 16h, 8Bh, 0F3h, 2Bh, 0F0h, 56h, 50h, 8Bh, 44h, 24h, 2Ch, 50h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C6h, 85h, 0FFh, 76h, 10h, 8Bh, 54h, 24h, 1Ch
    db 8Bh, 0CFh, 8Bh, 32h, 89h, 30h, 83h, 0C0h, 04h, 49h, 75h, 0F6h, 8Ah, 4Ch, 24h, 28h
    db 84h, 0C9h, 8Bh, 0F8h, 75h, 19h, 8Bh, 75h, 04h, 3Bh, 0F3h, 74h, 12h, 2Bh, 0F3h, 56h
    db 53h, 50h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 8Bh, 0F8h, 83h, 0C4h, 0Ch, 03h, 0FEh, 8Bh
    db 4Dh, 00h, 85h, 0C9h, 5Bh, 74h, 27h, 8Bh, 45h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h
    db 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 61h, 0Bh, 68h, 00h, 83h
    db 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 95h, 0D2h, 62h, 00h, 83h, 0C4h, 08h, 8Bh, 44h
    db 24h, 20h, 8Bh, 4Ch, 24h, 0Ch, 89h, 7Dh, 04h, 5Fh, 8Dh, 14h, 88h, 5Eh, 89h, 45h
    db 00h, 89h, 55h, 08h, 5Dh, 59h, 0C2h, 14h, 00h
?d_00201270@@YAXXZ ENDP

; ghidra: FUN_00601590  retail @ 0x00201590 size 143
public ?d_00201590@@YAXXZ
?d_00201590@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 0B8h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 8Bh
    db 46h, 04h, 8Bh, 0Eh, 8Dh, 54h, 24h, 07h, 52h, 50h, 51h, 0C7h, 44h, 24h, 20h, 00h
    db 00h, 00h, 00h, 0E8h, 21h, 32h, 0E2h, 0FFh, 8Bh, 06h, 83h, 0C4h, 0Ch, 85h, 0C0h, 0C7h
    db 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 36h, 8Bh, 76h, 08h, 2Bh, 0F0h, 0C1h, 0FEh
    db 02h, 0C1h, 0E6h, 02h, 81h, 0FEh, 80h, 00h, 00h, 00h, 76h, 19h, 50h, 0E8h, 0BEh, 08h
    db 68h, 00h, 83h, 0C4h, 04h, 5Eh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 14h, 0C3h, 56h, 50h, 0E8h, 0E4h, 0CFh, 62h, 00h, 83h, 0C4h, 08h, 8Bh
    db 4Ch, 24h, 0Ch, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_00201590@@YAXXZ ENDP

; ghidra: FUN_00601ae0  retail @ 0x00201AE0 size 25
public ?d_00201ae0@@YAXXZ
?d_00201ae0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 5Ah, 61h, 0E4h, 0FFh
?d_00201ae0@@YAXXZ ENDP

; ghidra: FUN_00601c30  retail @ 0x00201C30 size 104
public ?d_00201c30@@YAXXZ
?d_00201c30@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 20h, 0F8h, 2Eh, 01h, 6Ah, 0FFh, 68h, 0DEh
    db 0B8h, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 20h, 0F8h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 68h, 0Bh, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 65h, 91h
    db 0E3h, 0FFh, 0A3h, 1Ch, 0F8h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 1Ch, 0F8h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_00201c30@@YAXXZ ENDP

; ghidra: FUN_00601d70  retail @ 0x00201D70 size 283
_TEXT ENDS
_TEXT$d00601d70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00601D70 size 283
public ?d_00201d70@@YAXXZ
?d_00201d70@@YAXXZ PROC
    db 051h, 053h, 056h, 08Bh, 0F1h, 08Bh, 05Eh, 0F4h, 057h, 08Bh, 07Eh, 0F8h, 08Bh, 087h, 028h, 001h
    db 000h, 000h, 0F6h, 0C4h, 010h, 00Fh, 084h, 0CCh, 000h, 000h, 000h, 08Ah, 046h, 010h, 084h, 0C0h
    db 055h, 075h, 02Eh, 08Bh, 0EFh, 0F6h, 085h, 094h, 000h, 000h, 000h, 020h, 075h, 01Fh, 08Bh, 085h
    db 004h, 002h, 000h, 000h, 085h, 0C0h, 074h, 015h, 06Ah, 002h, 06Ah, 000h, 08Dh, 048h, 020h
    call ?j_0001336d@@YAXXZ
    db 06Ah, 000h, 08Bh, 0CDh
    call ?j_0003e126@@YAXXZ
    db 0C6h, 046h, 010h, 001h, 08Bh, 043h, 008h, 085h, 0C0h, 075h, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 085h, 0C0h, 089h, 044h, 024h, 010h, 0DBh, 044h, 024h, 010h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 03Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 06Eh, 014h, 0D9h, 056h, 014h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 04Ah, 0C7h, 046h, 014h, 000h, 000h, 000h, 000h, 08Bh, 047h
    db 078h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0E8h, 085h, 0EDh, 074h, 020h, 06Ah, 06Ch, 08Bh, 0CDh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 013h, 08Bh, 08Dh, 0FCh, 001h, 000h, 000h, 08Bh, 011h, 0FFh, 052h, 068h, 08Bh
    db 010h, 057h, 08Bh, 0C8h, 0FFh, 052h, 034h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 057h
    call ?j_0001d0de@@YAXXZ
    db 0EBh, 014h, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 028h, 085h, 0C0h, 074h, 009h, 08Bh, 04Eh, 014h
    db 089h, 088h, 0B0h, 000h, 000h, 000h, 05Dh, 08Bh, 076h, 0F8h, 0F6h, 086h, 044h, 003h, 000h, 000h
    db 001h, 074h, 00Ah, 05Fh, 05Eh, 0B8h, 0FFh, 0FFh, 0FFh, 03Fh, 05Bh, 059h, 0C3h, 085h, 0F6h, 074h
    db 010h, 08Bh, 086h, 028h, 001h, 000h, 000h, 0F6h, 0C4h, 010h, 0B8h, 001h, 000h, 000h, 000h, 075h
    db 005h, 0B8h, 005h, 000h, 000h, 000h, 05Fh, 05Eh, 05Bh, 059h, 0C3h
?d_00201d70@@YAXXZ ENDP
_TEXT$d00601d70 ENDS
_TEXT SEGMENT

; ghidra: FUN_006023c0  retail @ 0x002023C0 size 157
public ?d_002023c0@@YAXXZ
?d_002023c0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 0F4h, 57h, 8Bh, 7Eh, 0F8h, 8Bh, 0CFh, 0E8h, 07h, 2Eh
    db 0E3h, 0FFh, 85h, 0C0h, 74h, 14h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 28h, 84h, 0C0h, 74h
    db 12h, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 0C3h, 0F6h, 87h, 90h, 00h, 00h, 00h
    db 04h, 75h, 61h, 0F6h, 87h, 44h, 03h, 00h, 00h, 01h, 74h, 09h, 5Fh, 5Eh, 0B8h, 0FFh
    db 0FFh, 0FFh, 3Fh, 5Bh, 0C3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 78h, 3Ch, 8Bh, 56h, 10h
    db 8Bh, 43h, 10h, 8Bh, 0CFh, 2Bh, 0CAh, 3Bh, 0C8h, 72h, 0Ch, 8Bh, 56h, 0F0h, 8Dh, 4Eh
    db 0F0h, 0FFh, 52h, 2Ch, 89h, 7Eh, 10h, 8Bh, 46h, 14h, 8Bh, 38h, 3Bh, 0F8h, 74h, 24h
    db 8Bh, 47h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 14h, 0CEh, 0E1h, 0FFh, 85h
    db 0C0h, 74h, 0Ah, 8Bh, 56h, 0F0h, 8Dh, 4Eh, 0F0h, 50h, 0FFh, 52h, 30h, 8Bh, 3Fh, 3Bh
    db 7Eh, 14h, 75h, 0DCh, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 0C3h
?d_002023c0@@YAXXZ ENDP

; ghidra: FUN_00602490  retail @ 0x00202490 size 539
public ?d_00202490@@YAXXZ
?d_00202490@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 88h, 0B9h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 5Ch, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 8Bh
    db 4Eh, 08h, 8Bh, 6Eh, 04h, 57h, 8Bh, 38h, 3Bh, 0F8h, 89h, 4Ch, 24h, 0Ch, 74h, 1Ah
    db 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h, 24h, 0C1h, 62h, 00h, 8Bh, 46h, 24h, 83h
    db 0C4h, 08h, 3Bh, 0F8h, 75h, 0EAh, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 46h, 24h, 89h, 00h, 8Bh
    db 46h, 24h, 89h, 40h, 04h, 33h, 0FFh, 89h, 7Ch, 24h, 2Ch, 0C7h, 44h, 24h, 28h, 0C0h
    db 5Dh, 08h, 01h, 89h, 4Ch, 24h, 30h, 0C7h, 44h, 24h, 34h, 04h, 00h, 00h, 00h, 0C6h
    db 44h, 24h, 38h, 00h, 89h, 7Ch, 24h, 70h, 89h, 7Ch, 24h, 18h, 0C7h, 44h, 24h, 14h
    db 80h, 3Bh, 08h, 01h, 89h, 7Ch, 24h, 20h, 0C7h, 44h, 24h, 1Ch, 0D0h, 5Dh, 08h, 01h
    db 89h, 4Ch, 24h, 24h, 0C6h, 44h, 24h, 70h, 02h, 0E8h, 0F6h, 0E2h, 0E1h, 0FFh, 8Dh, 4Dh
    db 20h, 89h, 7Ch, 24h, 40h, 0C7h, 44h, 24h, 3Ch, 58h, 51h, 0Ah, 01h, 89h, 4Ch, 24h
    db 44h, 89h, 44h, 24h, 48h, 0C6h, 44h, 24h, 4Ch, 01h, 8Dh, 54h, 24h, 14h, 52h, 8Dh
    db 4Ch, 24h, 2Ch, 0C6h, 44h, 24h, 74h, 03h, 0E8h, 83h, 05h, 7Fh, 00h, 8Dh, 44h, 24h
    db 1Ch, 50h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 75h, 05h, 7Fh, 00h, 8Dh, 4Ch, 24h, 3Ch, 51h
    db 8Dh, 4Ch, 24h, 2Ch, 0E8h, 67h, 05h, 7Fh, 00h, 8Bh, 45h, 08h, 8Bh, 4Ch, 24h, 0Ch
    db 6Ah, 01h, 8Dh, 54h, 24h, 2Ch, 52h, 57h, 50h, 83h, 0C1h, 38h, 51h, 8Bh, 0Dh, 0B8h
    db 0D5h, 2Eh, 01h, 8Dh, 54h, 24h, 24h, 52h, 0E8h, 0C3h, 03h, 7Fh, 00h, 0C6h, 44h, 24h
    db 70h, 04h, 8Bh, 44h, 24h, 10h, 8Bh, 48h, 04h, 8Bh, 50h, 0Ch, 3Bh, 0D1h, 0Fh, 84h
    db 9Ah, 00h, 00h, 00h, 8Bh, 0CAh, 8Bh, 39h, 83h, 0C1h, 08h, 85h, 0FFh, 89h, 48h, 0Ch
    db 0Fh, 84h, 84h, 00h, 00h, 00h, 3Bh, 7Ch, 24h, 0Ch, 74h, 0D6h, 33h, 0D2h, 89h, 54h
    db 24h, 50h, 8Bh, 0C2h, 89h, 54h, 24h, 58h, 89h, 54h, 24h, 5Ch, 8Bh, 0CAh, 0Dh, 00h
    db 80h, 00h, 00h, 81h, 0C9h, 00h, 00h, 40h, 00h, 89h, 44h, 24h, 54h, 8Dh, 44h, 24h
    db 50h, 89h, 4Ch, 24h, 60h, 50h, 8Bh, 0CFh, 89h, 54h, 24h, 68h, 0E8h, 09h, 0FFh, 0E3h
    db 0FFh, 84h, 0C0h, 75h, 9Dh, 8Bh, 4Eh, 24h, 8Bh, 01h, 3Bh, 0C1h, 8Bh, 7Fh, 74h, 74h
    db 0Fh, 39h, 78h, 08h, 74h, 06h, 8Bh, 00h, 3Bh, 0C1h, 75h, 0F5h, 3Bh, 0C1h, 75h, 82h
    db 8Bh, 4Eh, 24h, 8Bh, 29h, 6Ah, 0Ch, 0E8h, 14h, 0BFh, 62h, 00h, 8Dh, 48h, 08h, 83h
    db 0C4h, 04h, 85h, 0C9h, 74h, 02h, 89h, 39h, 8Bh, 4Dh, 04h, 89h, 28h, 89h, 48h, 04h
    db 89h, 01h, 89h, 45h, 04h, 0E9h, 58h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 0FFh, 48h
    db 10h, 8Bh, 44h, 24h, 10h, 8Bh, 48h, 10h, 85h, 0C9h, 0C6h, 44h, 24h, 70h, 03h, 75h
    db 38h, 8Bh, 08h, 85h, 0C9h, 8Bh, 0F0h, 74h, 27h, 8Bh, 40h, 08h, 2Bh, 0C1h, 0C1h, 0F8h
    db 03h, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 2Fh, 0F8h, 67h
    db 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 63h, 0BFh, 62h, 00h, 83h, 0C4h, 08h
    db 56h, 0E8h, 1Ah, 0F8h, 67h, 00h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 68h, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 5Dh, 83h, 0C4h, 68h, 0C3h
?d_00202490@@YAXXZ ENDP

; ghidra: FUN_006028e0  retail @ 0x002028E0 size 32
public ?d_002028e0@@YAXXZ
?d_002028e0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0A4h, 53h, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 53h, 53h, 0E4h, 0FFh
?d_002028e0@@YAXXZ ENDP

; ghidra: FUN_006029d0  retail @ 0x002029D0 size 17
public ?d_002029d0@@YAXXZ
?d_002029d0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 3Ch, 54h, 0Ah, 01h, 0E8h, 40h, 0DFh, 64h, 00h
    db 0C3h
?d_002029d0@@YAXXZ ENDP

; ghidra: FUN_006029f0  retail @ 0x002029F0 size 164
public ?d_002029f0@@YAXXZ
?d_002029f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 18h, 0BAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 18h, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 0Ch, 0E8h, 0C6h, 46h, 0E1h, 0FFh, 0C7h, 46h
    db 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh, 09h, 01h, 83h, 0C9h, 0FFh, 33h
    db 0C0h, 89h, 46h, 14h, 89h, 4Eh, 18h, 89h, 4Eh, 1Ch, 0C7h, 46h, 20h, 0FCh, 1Bh, 0Ah
    db 01h, 8Bh, 56h, 08h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 18h
    db 0C7h, 06h, 4Ch, 55h, 0Ah, 01h, 0C7h, 46h, 0Ch, 88h, 54h, 0Ah, 01h, 0C7h, 46h, 10h
    db 78h, 54h, 0Ah, 01h, 0C7h, 46h, 20h, 0A4h, 53h, 0Ah, 01h, 89h, 46h, 24h, 89h, 46h
    db 28h, 89h, 46h, 2Ch, 0C7h, 46h, 30h, 05h, 00h, 00h, 00h, 0E8h, 5Ah, 2Dh, 0E1h, 0FFh
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 08h, 00h
?d_002029f0@@YAXXZ ENDP

; ghidra: FUN_00602df0  retail @ 0x00202DF0 size 70
public ?d_00202df0@@YAXXZ
?d_00202df0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 0E8h, 8Dh, 77h, 0E0h, 0C7h, 46h, 24h, 00h, 00h, 00h
    db 00h, 0C7h, 46h, 28h, 00h, 00h, 00h, 00h, 0C7h, 46h, 2Ch, 00h, 00h, 00h, 00h, 8Bh
    db 01h, 0FFh, 50h, 28h, 85h, 0C0h, 74h, 09h, 6Ah, 04h, 8Bh, 0C8h, 0E8h, 6Dh, 0Eh, 0E4h
    db 0FFh, 8Bh, 4Fh, 0E8h, 68h, 0FFh, 0FFh, 0FFh, 3Fh, 51h, 8Bh, 0CEh, 0E8h, 0A9h, 29h, 0E1h
    db 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00202df0@@YAXXZ ENDP

; ghidra: FUN_00602e80  retail @ 0x00202E80 size 32
public ?d_00202e80@@YAXXZ
?d_00202e80@@YAXXZ PROC
    db 0C7h, 41h, 20h, 84h, 55h, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0B3h, 4Dh, 0E4h, 0FFh
?d_00202e80@@YAXXZ ENDP

; ghidra: FUN_00602ef0  retail @ 0x00202EF0 size 31
public ?d_00202ef0@@YAXXZ
?d_00202ef0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 80h, 55h, 0Ah, 01h, 74h, 09h
    db 56h, 0E8h, 0AAh, 0EFh, 67h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00202ef0@@YAXXZ ENDP

; ghidra: FUN_00602f40  retail @ 0x00202F40 size 154
public ?d_00202f40@@YAXXZ
?d_00202f40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0BAh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 18h, 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h
    db 18h, 50h, 51h, 8Bh, 0CEh, 89h, 74h, 24h, 0Ch, 0E8h, 76h, 41h, 0E1h, 0FFh, 0C7h, 46h
    db 0Ch, 0D0h, 0C9h, 09h, 01h, 0C7h, 46h, 10h, 0A0h, 0CBh, 09h, 01h, 83h, 0C9h, 0FFh, 33h
    db 0C0h, 89h, 46h, 14h, 89h, 4Eh, 18h, 89h, 4Eh, 1Ch, 0C7h, 46h, 20h, 7Ch, 25h, 0Ah
    db 01h, 8Bh, 56h, 08h, 6Ah, 01h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 18h, 0C7h, 06h, 6Ch
    db 57h, 0Ah, 01h, 0C7h, 46h, 0Ch, 0A8h, 56h, 0Ah, 01h, 0C7h, 46h, 10h, 9Ch, 56h, 0Ah
    db 01h, 0C7h, 46h, 20h, 84h, 55h, 0Ah, 01h, 89h, 46h, 24h, 89h, 46h, 28h, 89h, 46h
    db 2Ch, 0E8h, 14h, 28h, 0E1h, 0FFh, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 08h, 00h
?d_00202f40@@YAXXZ ENDP

; ghidra: FUN_00603110  retail @ 0x00203110 size 26
public ?d_00203110@@YAXXZ
?d_00203110@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 8Bh, 0Dh, 88h, 0F1h, 2Eh, 01h, 83h, 0C0h, 18h, 50h
    db 0E8h, 35h, 0C8h, 0E2h, 0FFh, 89h, 46h, 2Ch, 5Eh, 0C3h
?d_00203110@@YAXXZ ENDP

; ghidra: FUN_00603130  retail @ 0x00203130 size 62
public ?d_00203130@@YAXXZ
?d_00203130@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 3Bh, 41h, 14h
    db 75h, 1Bh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 2Ch, 8Bh, 46h, 08h, 68h, 0FFh, 0FFh, 0FFh
    db 3Fh, 50h, 8Bh, 0CEh, 0E8h, 81h, 26h, 0E1h, 0FFh, 5Eh, 0C2h, 08h, 00h, 8Bh, 4Eh, 08h
    db 6Ah, 01h, 51h, 8Bh, 0CEh, 0E8h, 70h, 26h, 0E1h, 0FFh, 5Eh, 0C2h, 08h, 00h
?d_00203130@@YAXXZ ENDP

; ghidra: FUN_00603440  retail @ 0x00203440 size 48
public ?d_00203440@@YAXXZ
?d_00203440@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 0B0h, 57h, 0Ah, 01h, 89h, 48h, 18h, 0C7h, 40h, 08h
    db 00h, 00h, 48h, 43h, 0C7h, 40h, 0Ch, 0Fh, 00h, 00h, 00h, 0C7h, 40h, 10h, 0Ah, 0D7h
    db 23h, 3Ch, 0C7h, 40h, 1Ch, 0Ah, 0D7h, 0A3h, 3Ch, 89h, 48h, 14h, 89h, 48h, 20h, 0C3h
?d_00203440@@YAXXZ ENDP

; ghidra: FUN_00603bc0  retail @ 0x00203BC0 size 25
public ?d_00203bc0@@YAXXZ
?d_00203bc0@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 7Ah, 40h, 0E4h, 0FFh
?d_00203bc0@@YAXXZ ENDP

; ghidra: FUN_00603db0  retail @ 0x00203DB0 size 44
public ?d_00203db0@@YAXXZ
?d_00203db0@@YAXXZ PROC
    db 56h, 8Bh, 71h, 04h, 8Bh, 46h, 28h, 85h, 0C0h, 75h, 04h, 0B0h, 01h, 5Eh, 0C3h, 8Bh
    db 41h, 08h, 8Bh, 4Eh, 24h, 6Ah, 20h, 51h, 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 50h, 0E8h
    db 0D8h, 0B6h, 0E0h, 0FFh, 3Bh, 46h, 28h, 0Fh, 9Dh, 0C0h, 5Eh, 0C3h
?d_00203db0@@YAXXZ ENDP

; ghidra: FUN_00603df0  retail @ 0x00203DF0 size 78
public ?d_00203df0@@YAXXZ
?d_00203df0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 56h
    db 8Bh, 0CFh, 0E8h, 0AAh, 06h, 0E0h, 0FFh, 8Bh, 16h, 8Dh, 47h, 20h, 50h, 8Bh, 0CEh, 0FFh
    db 52h, 6Ch, 8Bh, 16h, 8Dh, 47h, 24h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 83h
    db 0C7h, 28h, 57h, 8Bh, 0CEh, 0FFh, 52h, 78h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00203df0@@YAXXZ ENDP

; ghidra: FUN_00603f90  retail @ 0x00203F90 size 759
public ?d_00203f90@@YAXXZ
?d_00203f90@@YAXXZ PROC
    db 83h, 0ECh, 14h, 53h, 55h, 8Bh, 0E9h, 56h, 8Bh, 75h, 0F8h, 8Bh, 9Eh, 04h, 02h, 00h
    db 00h, 8Bh, 06h, 57h, 8Bh, 0BEh, 00h, 02h, 00h, 00h, 8Bh, 0CEh, 89h, 5Ch, 24h, 10h
    db 89h, 7Ch, 24h, 18h, 0FFh, 50h, 28h, 85h, 0FFh, 89h, 44h, 24h, 1Ch, 0Fh, 84h, 0B7h
    db 02h, 00h, 00h, 85h, 0DBh, 0Fh, 84h, 0AFh, 02h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0A7h
    db 02h, 00h, 00h, 8Bh, 5Dh, 0F4h, 8Bh, 7Bh, 08h, 3Bh, 7Bh, 0Ch, 74h, 28h, 8Bh, 0FFh
    db 8Bh, 0Dh, 88h, 0F1h, 2Eh, 01h, 57h, 0E8h, 6Eh, 0B9h, 0E2h, 0FFh, 50h, 8Bh, 0CEh, 0E8h
    db 43h, 7Ah, 0E0h, 0FFh, 84h, 0C0h, 0Fh, 84h, 71h, 02h, 00h, 00h, 8Bh, 43h, 0Ch, 83h
    db 0C7h, 04h, 3Bh, 0F8h, 75h, 0DAh, 8Bh, 7Ch, 24h, 18h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h
    db 10h, 0D9h, 5Ch, 24h, 14h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 18h, 0D9h, 5Ch, 24h, 18h
    db 0D9h, 05h, 34h, 53h, 07h, 01h, 0C7h, 44h, 24h, 20h, 00h, 00h, 80h, 3Fh, 0D8h, 5Ch
    db 24h, 18h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 8Dh, 44h, 24h, 20h, 74h, 04h, 8Dh, 44h, 24h
    db 18h, 0D9h, 44h, 24h, 14h, 0D8h, 30h, 8Bh, 45h, 14h, 85h, 0C0h, 0Fh, 8Eh, 90h, 00h
    db 00h, 00h, 48h, 0DDh, 0D8h, 85h, 0C0h, 89h, 45h, 14h, 7Eh, 18h, 0F6h, 86h, 44h, 03h
    db 00h, 00h, 01h, 75h, 0Fh, 8Bh, 0CEh, 0E8h, 0DEh, 0A4h, 0E3h, 0FFh, 84h, 0C0h, 0Fh, 84h
    db 0E3h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 7Fh, 0C9h, 0E1h, 0FFh, 8Bh, 08h, 0F6h, 0C5h, 01h
    db 74h, 09h, 6Ah, 08h, 8Bh, 0CEh, 0E8h, 20h, 0E2h, 0E0h, 0FFh, 0F6h, 86h, 44h, 03h, 00h
    db 00h, 01h, 75h, 19h, 8Bh, 0CEh, 0E8h, 0AFh, 0A4h, 0E3h, 0FFh, 84h, 0C0h, 75h, 0Eh, 8Bh
    db 4Ch, 24h, 10h, 6Ah, 02h, 83h, 0C1h, 20h, 0E8h, 0C3h, 0Ch, 0E2h, 0FFh, 8Bh, 4Bh, 20h
    db 89h, 4Dh, 18h, 0C7h, 45h, 14h, 00h, 00h, 00h, 00h, 8Bh, 86h, 20h, 01h, 00h, 00h
    db 0A9h, 00h, 00h, 00h, 01h, 0Fh, 84h, 81h, 01h, 00h, 00h, 25h, 0FFh, 0FFh, 0FFh, 0FEh
    db 8Bh, 0CEh, 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 40h, 0D8h, 0E1h, 0FFh, 0E9h, 6Ah, 01h
    db 00h, 00h, 0D8h, 5Bh, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 67h, 01h, 00h, 00h
    db 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 5Ah, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h
    db 0F6h, 0C8h, 0E1h, 0FFh, 8Bh, 08h, 0F6h, 0C5h, 01h, 0Fh, 85h, 48h, 01h, 00h, 00h, 0D9h
    db 44h, 24h, 14h, 0D8h, 5Dh, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 36h, 01h, 00h
    db 00h, 8Bh, 45h, 18h, 85h, 0C0h, 0Fh, 85h, 2Bh, 01h, 00h, 00h, 8Dh, 4Dh, 0F0h, 0E8h
    db 0FFh, 09h, 0E0h, 0FFh, 84h, 0C0h, 74h, 31h, 6Ah, 07h, 8Bh, 0CEh, 0E8h, 6Ah, 0E1h, 0E0h
    db 0FFh, 6Ah, 08h, 8Bh, 0CEh, 0E8h, 0A2h, 07h, 0E3h, 0FFh, 8Bh, 4Ch, 24h, 10h, 6Ah, 02h
    db 68h, 0FEh, 0FFh, 0FFh, 0Fh, 8Dh, 56h, 38h, 52h, 83h, 0C1h, 20h, 0E8h, 60h, 0C3h, 0E3h
    db 0FFh, 8Bh, 43h, 18h, 89h, 45h, 14h, 0EBh, 34h, 8Bh, 8Eh, 20h, 01h, 00h, 00h, 0B8h
    db 00h, 00h, 00h, 01h, 85h, 0C8h, 75h, 0Fh, 0Bh, 0C8h, 89h, 8Eh, 20h, 01h, 00h, 00h
    db 8Bh, 0CEh, 0E8h, 96h, 0D7h, 0E1h, 0FFh, 8Bh, 4Ch, 24h, 10h, 6Ah, 02h, 6Ah, 00h, 83h
    db 0C1h, 20h, 0E8h, 0D6h, 0F1h, 0E0h, 0FFh, 8Bh, 4Bh, 1Ch, 89h, 4Dh, 14h, 8Bh, 86h, 20h
    db 01h, 00h, 00h, 0A9h, 00h, 00h, 40h, 00h, 74h, 12h, 25h, 0FFh, 0FFh, 0BFh, 0FFh, 8Bh
    db 0CEh, 89h, 86h, 20h, 01h, 00h, 00h, 0E8h, 61h, 0D7h, 0E1h, 0FFh, 0F6h, 86h, 24h, 01h
    db 00h, 00h, 04h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0FBh, 8Bh, 0CEh
    db 89h, 86h, 24h, 01h, 00h, 00h, 0E8h, 42h, 0D7h, 0E1h, 0FFh, 0F6h, 86h, 24h, 01h, 00h
    db 00h, 08h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0F7h, 8Bh, 0CEh, 89h
    db 86h, 24h, 01h, 00h, 00h, 0E8h, 23h, 0D7h, 0E1h, 0FFh, 0F6h, 86h, 24h, 01h, 00h, 00h
    db 10h, 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0EFh, 8Bh, 0CEh, 89h, 86h
    db 24h, 01h, 00h, 00h, 0E8h, 04h, 0D7h, 0E1h, 0FFh, 0F6h, 86h, 24h, 01h, 00h, 00h, 20h
    db 74h, 16h, 8Bh, 86h, 24h, 01h, 00h, 00h, 83h, 0E0h, 0DFh, 8Bh, 0CEh, 89h, 86h, 24h
    db 01h, 00h, 00h, 0E8h, 0E5h, 0D6h, 0E1h, 0FFh, 8Bh, 0CEh, 0E8h, 0A5h, 0B6h, 0E0h, 0FFh, 85h
    db 0C0h, 74h, 09h, 8Bh, 10h, 6Ah, 00h, 8Bh, 0C8h, 0FFh, 52h, 08h, 8Bh, 4Ch, 24h, 1Ch
    db 6Ah, 00h, 0E8h, 0E2h, 91h, 0E2h, 0FFh, 8Bh, 45h, 18h, 85h, 0C0h, 7Eh, 0Fh, 48h, 85h
    db 0C0h, 89h, 45h, 18h, 7Fh, 07h, 8Bh, 44h, 24h, 14h, 89h, 45h, 10h, 5Fh, 5Eh, 5Dh
    db 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 14h, 0C3h, 5Fh, 5Eh, 5Dh, 0B8h, 0FFh, 0FFh
    db 0FFh, 3Fh, 5Bh, 83h, 0C4h, 14h, 0C3h
?d_00203f90@@YAXXZ ENDP

; ghidra: FUN_006043a0  retail @ 0x002043A0 size 32
public ?d_002043a0@@YAXXZ
?d_002043a0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0C0h, 5Ah, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 93h, 38h, 0E4h, 0FFh
?d_002043a0@@YAXXZ ENDP

; ghidra: FUN_006043f0  retail @ 0x002043F0 size 17
public ?d_002043f0@@YAXXZ
?d_002043f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 13h, 1Ah, 0E1h, 0FFh, 8Dh, 4Eh, 20h, 5Eh, 0E9h, 5Ah, 9Bh, 0E2h
    db 0FFh
?d_002043f0@@YAXXZ ENDP

; ghidra: FUN_00604430  retail @ 0x00204430 size 15
public ?d_00204430@@YAXXZ
?d_00204430@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 6Ah, 01h, 50h, 83h, 0C1h, 0E0h, 0E8h, 9Ch, 13h, 0E1h, 0FFh, 0C3h
?d_00204430@@YAXXZ ENDP

; ghidra: FUN_00604460  retail @ 0x00204460 size 16
public ?d_00204460@@YAXXZ
?d_00204460@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 0E0h, 0A6h, 0E2h, 0FFh, 0C3h
?d_00204460@@YAXXZ ENDP

; ghidra: FUN_00604490  retail @ 0x00204490 size 16
public ?d_00204490@@YAXXZ
?d_00204490@@YAXXZ PROC
    db 8Bh, 41h, 0E8h, 8Bh, 49h, 0E4h, 50h, 83h, 0C1h, 08h, 0E8h, 81h, 9Eh, 0E2h, 0FFh, 0C3h
?d_00204490@@YAXXZ ENDP

; ghidra: FUN_00604650  retail @ 0x00204650 size 104
public ?d_00204650@@YAXXZ
?d_00204650@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 48h, 0F8h, 2Eh, 01h, 6Ah, 0FFh, 68h, 0AEh
    db 0BBh, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 48h, 0F8h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 0ECh, 08h, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 45h, 67h
    db 0E3h, 0FFh, 0A3h, 44h, 0F8h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 44h, 0F8h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_00204650@@YAXXZ ENDP

; ghidra: FUN_00604710  retail @ 0x00204710 size 54
public ?d_00204710@@YAXXZ
?d_00204710@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 56h
    db 8Bh, 0CFh, 0E8h, 8Ah, 0FDh, 0DFh, 0FFh, 56h, 8Dh, 4Fh, 20h, 0E8h, 6Ch, 56h, 0E2h, 0FFh
    db 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00204710@@YAXXZ ENDP

; ghidra: FUN_00604770  retail @ 0x00204770 size 441
public ?d_00204770@@YAXXZ
?d_00204770@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 68h, 0D8h, 36h, 07h, 01h, 57h, 8Bh
    db 0F1h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 49h, 8Bh, 44h
    db 24h, 18h, 80h, 38h, 00h, 75h, 1Dh, 8Bh, 4Ch, 24h, 1Ch, 80h, 39h, 00h, 75h, 14h
    db 33h, 0D2h, 89h, 16h, 89h, 56h, 04h, 5Fh, 89h, 56h, 08h, 32h, 0C0h, 5Eh, 83h, 0C4h
    db 08h, 0C2h, 0Ch, 00h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh, 44h, 24h, 0Ch, 6Ah, 02h, 50h
    db 0E8h, 3Bh, 0BEh, 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h
    db 0Ch, 51h, 0E8h, 29h, 25h, 7Fh, 00h, 8Ah, 07h, 3Ch, 2Bh, 75h, 67h, 8Bh, 54h, 24h
    db 18h, 80h, 3Ah, 00h, 74h, 23h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh, 44h, 24h, 0Ch, 6Ah
    db 02h, 50h, 0E8h, 09h, 0BEh, 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 0E8h, 0F7h, 24h, 7Fh, 00h, 68h, 70h, 66h, 2Ah, 01h, 47h, 57h
    db 0E8h, 0CBh, 0C1h, 64h, 00h, 8Bh, 0C8h, 8Bh, 0D0h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 0B8h
    db 01h, 00h, 00h, 00h, 0D3h, 0E0h, 8Bh, 0Ch, 96h, 8Dh, 14h, 96h, 83h, 0C4h, 08h, 0Bh
    db 0C8h, 89h, 0Ah, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 0C6h, 01h, 01h, 0B0h, 01h, 5Eh, 83h, 0C4h
    db 08h, 0C2h, 0Ch, 00h, 3Ch, 2Dh, 75h, 69h, 8Bh, 54h, 24h, 18h, 80h, 3Ah, 00h, 74h
    db 23h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh, 44h, 24h, 0Ch, 6Ah, 02h, 50h, 0E8h, 9Eh, 0BDh
    db 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h
    db 8Ch, 24h, 7Fh, 00h, 68h, 70h, 66h, 2Ah, 01h, 47h, 57h, 0E8h, 60h, 0C1h, 64h, 00h
    db 8Bh, 0C8h, 8Bh, 0D0h, 83h, 0E1h, 1Fh, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 0C1h, 0EAh
    db 05h, 8Bh, 0Ch, 96h, 8Dh, 14h, 96h, 83h, 0C4h, 08h, 0F7h, 0D0h, 23h, 0C8h, 89h, 0Ah
    db 8Bh, 4Ch, 24h, 1Ch, 5Fh, 0C6h, 01h, 01h, 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch
    db 00h, 8Bh, 54h, 24h, 1Ch, 80h, 3Ah, 00h, 74h, 23h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh
    db 44h, 24h, 0Ch, 6Ah, 02h, 50h, 0E8h, 35h, 0BDh, 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h
    db 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h, 23h, 24h, 7Fh, 00h, 53h, 8Bh, 5Ch
    db 24h, 1Ch, 80h, 3Bh, 00h, 75h, 0Ch, 33h, 0D2h, 8Bh, 0C6h, 89h, 10h, 89h, 50h, 04h
    db 89h, 50h, 08h, 68h, 70h, 66h, 2Ah, 01h, 57h, 0E8h, 0E2h, 0C0h, 64h, 00h, 8Bh, 0C8h
    db 0C1h, 0E9h, 05h, 8Dh, 14h, 8Eh, 8Bh, 0C8h, 83h, 0E1h, 1Fh, 0B8h, 01h, 00h, 00h, 00h
    db 0D3h, 0E0h, 8Bh, 0Ah, 83h, 0C4h, 08h, 0Bh, 0C8h, 89h, 0Ah, 0C6h, 03h, 01h, 5Bh, 5Fh
    db 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_00204770@@YAXXZ ENDP

; ghidra: FUN_00604a80  retail @ 0x00204A80 size 166
public ?d_00204a80@@YAXXZ
?d_00204a80@@YAXXZ PROC
    db 83h, 0ECh, 08h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 89h, 4Ch, 24h, 10h
    db 74h, 07h, 8Bh, 0CFh, 0E8h, 0A7h, 2Eh, 68h, 00h, 8Bh, 6Ch, 24h, 18h, 6Ah, 00h, 8Bh
    db 0CDh, 0C6h, 44h, 24h, 13h, 00h, 0C6h, 44h, 24h, 20h, 00h, 0E8h, 10h, 0BFh, 64h, 00h
    db 8Bh, 0F0h, 85h, 0F6h, 74h, 67h, 85h, 0FFh, 74h, 3Ch, 8Bh, 07h, 85h, 0C0h, 74h, 15h
    db 66h, 83h, 78h, 04h, 00h, 74h, 0Eh, 6Ah, 01h, 68h, 1Ch, 0EDh, 08h, 01h, 8Bh, 0CFh
    db 0E8h, 8Bh, 32h, 68h, 00h, 85h, 0F6h, 74h, 12h, 8Bh, 0C6h, 8Dh, 50h, 01h, 8Bh, 0FFh
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 0EBh, 02h, 33h, 0C0h, 50h, 56h, 8Bh
    db 0CFh, 0E8h, 6Ah, 32h, 68h, 00h, 8Dh, 44h, 24h, 1Ch, 50h, 8Dh, 4Ch, 24h, 13h, 51h
    db 8Bh, 4Ch, 24h, 18h, 56h, 0E8h, 81h, 8Bh, 0E3h, 0FFh, 84h, 0C0h, 74h, 0Fh, 6Ah, 00h
    db 8Bh, 0CDh, 0E8h, 0A9h, 0BEh, 64h, 00h, 8Bh, 0F0h, 85h, 0F6h, 75h, 99h, 5Fh, 5Eh, 5Dh
    db 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_00204a80@@YAXXZ ENDP

; ghidra: FUN_00604e70  retail @ 0x00204E70 size 73
public ?d_00204e70@@YAXXZ
?d_00204e70@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 6Ah, 00h, 8Bh, 0CEh, 0C6h, 44h, 24h, 0Bh, 00h, 0C6h
    db 44h, 24h, 0Ah, 00h, 0E8h, 37h, 0BBh, 64h, 00h, 85h, 0C0h, 74h, 29h, 57h, 8Bh, 7Ch
    db 24h, 18h, 8Dh, 4Ch, 24h, 0Ah, 51h, 8Dh, 54h, 24h, 0Fh, 52h, 50h, 8Bh, 0CFh, 0E8h
    db 0E7h, 87h, 0E3h, 0FFh, 84h, 0C0h, 74h, 0Dh, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0Fh, 0BBh, 64h
    db 00h, 85h, 0C0h, 75h, 0DDh, 5Fh, 5Eh, 59h, 0C3h
?d_00204e70@@YAXXZ ENDP

; ghidra: FUN_00604ed0  retail @ 0x00204ED0 size 69
public ?d_00204ed0@@YAXXZ
?d_00204ed0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Dh, 4Eh, 08h, 0C7h, 06h, 78h, 5Ch, 0Ah, 01h, 0E8h, 0C5h, 0A1h, 0E0h
    db 0FFh, 33h, 0C0h, 8Dh, 4Eh, 7Ch, 89h, 01h, 89h, 41h, 04h, 89h, 41h, 08h, 88h, 86h
    db 8Ch, 00h, 00h, 00h, 89h, 46h, 74h, 89h, 46h, 78h, 88h, 86h, 8Dh, 00h, 00h, 00h
    db 0C7h, 86h, 88h, 00h, 00h, 00h, 05h, 00h, 00h, 00h, 0C7h, 46h, 70h, 00h, 00h, 0C8h
    db 42h, 8Bh, 0C6h, 5Eh, 0C3h
?d_00204ed0@@YAXXZ ENDP

; ghidra: FUN_00604f90  retail @ 0x00204F90 size 67
public ?d_00204f90@@YAXXZ
?d_00204f90@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D8h, 0BCh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0C0h, 69h, 0E1h, 0FFh, 8Bh, 4Ch, 24h
    db 08h, 0C7h, 06h, 44h, 37h, 07h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_00204f90@@YAXXZ ENDP

; ghidra: FUN_00605000  retail @ 0x00205000 size 25
public ?d_00205000@@YAXXZ
?d_00205000@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0Ch, 5Eh, 0Ah, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 3Ah, 2Ch, 0E4h, 0FFh
?d_00205000@@YAXXZ ENDP

; ghidra: FUN_006050e0  retail @ 0x002050E0 size 104
public ?d_002050e0@@YAXXZ
?d_002050e0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 58h, 0F8h, 2Eh, 01h, 6Ah, 0FFh, 68h, 0FEh
    db 0BCh, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 58h, 0F8h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 08h, 09h, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0B5h, 5Ch
    db 0E3h, 0FFh, 0A3h, 54h, 0F8h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 54h, 0F8h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_002050e0@@YAXXZ ENDP

; ghidra: FUN_00605200  retail @ 0x00205200 size 219
public ?d_00205200@@YAXXZ
?d_00205200@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 0BDh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 9Ch, 00h, 00h, 00h, 8Bh, 84h, 24h, 0B0h, 00h
    db 00h, 00h, 56h, 50h, 8Bh, 0F1h, 6Ah, 38h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 73h, 0BCh, 0E2h
    db 0FFh, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h, 00h, 8Bh, 11h, 8Bh, 41h, 04h, 8Bh, 49h, 08h
    db 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 04h, 89h, 54h, 24h, 0Ch, 8Bh, 16h, 89h, 4Ch
    db 24h, 14h, 50h, 8Bh, 0CEh, 0C7h, 84h, 24h, 0ACh, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0FFh, 12h, 8Bh, 74h, 24h, 24h, 85h, 0F6h, 0C7h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 74h, 4Eh, 8Bh, 4Ch, 24h, 2Ch, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 21h, 56h, 0E8h, 12h, 0CCh, 67h, 00h, 83h, 0C4h
    db 04h, 5Eh, 8Bh, 8Ch, 24h, 9Ch, 00h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h, 50h, 56h, 0E8h, 30h, 93h, 62h, 00h
    db 83h, 0C4h, 08h, 8Bh, 8Ch, 24h, 0A0h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h
?d_00205200@@YAXXZ ENDP

; ghidra: FUN_00605320  retail @ 0x00205320 size 219
public ?d_00205320@@YAXXZ
?d_00205320@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Bh, 0BDh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 9Ch, 00h, 00h, 00h, 8Bh, 84h, 24h, 0B0h, 00h
    db 00h, 00h, 56h, 50h, 8Bh, 0F1h, 6Ah, 41h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 53h, 0BBh, 0E2h
    db 0FFh, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h, 00h, 8Bh, 11h, 8Bh, 41h, 04h, 8Bh, 49h, 08h
    db 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 04h, 89h, 54h, 24h, 0Ch, 8Bh, 16h, 89h, 4Ch
    db 24h, 14h, 50h, 8Bh, 0CEh, 0C7h, 84h, 24h, 0ACh, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0FFh, 12h, 8Bh, 74h, 24h, 24h, 85h, 0F6h, 0C7h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 74h, 4Eh, 8Bh, 4Ch, 24h, 2Ch, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 21h, 56h, 0E8h, 0F2h, 0CAh, 67h, 00h, 83h, 0C4h
    db 04h, 5Eh, 8Bh, 8Ch, 24h, 9Ch, 00h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h, 50h, 56h, 0E8h, 10h, 92h, 62h, 00h
    db 83h, 0C4h, 08h, 8Bh, 8Ch, 24h, 0A0h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h
?d_00205320@@YAXXZ ENDP

; ghidra: FUN_00605440  retail @ 0x00205440 size 354
_TEXT ENDS
_TEXT$d00605440 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00605440 size 354
public ?d_00205440@@YAXXZ
?d_00205440@@YAXXZ PROC
    db 083h, 0ECh, 01Ch, 053h, 056h, 08Bh, 071h, 0F8h, 08Bh, 09Eh, 004h, 002h, 000h, 000h, 085h, 0DBh
    db 057h, 00Fh, 084h, 044h, 001h, 000h, 000h, 08Bh, 079h, 0F4h, 085h, 0FFh, 00Fh, 084h, 039h, 001h
    db 000h, 000h, 051h, 08Dh, 047h, 014h, 089h, 064h, 024h, 010h, 08Bh, 0CCh, 050h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 0FFh, 052h, 07Ch, 085h, 0C0h, 074h, 019h, 083h, 0C0h, 00Ch, 08Bh, 008h, 089h, 04Ch
    db 024h, 010h, 08Bh, 050h, 004h, 089h, 054h, 024h, 014h, 08Bh, 040h, 008h, 089h, 044h, 024h, 018h
    db 0EBh, 049h, 08Bh, 0CEh
    call ?j_00040246@@YAXXZ
    db 0D9h, 040h, 004h, 0D9h, 000h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 0D8h, 00Dh
    dd __real@43fa0000
    db 06Ah, 000h, 0D9h, 05Ch, 024h, 020h, 0D8h, 00Dh
    dd __real@43fa0000
    db 0D9h, 044h, 024h, 020h, 0D8h, 046h, 038h, 0D9h, 05Ch, 024h, 014h, 0D8h, 046h, 03Ch, 0D9h, 05Ch
    db 024h, 018h, 08Bh, 044h, 024h, 018h, 08Bh, 011h, 050h, 08Bh, 044h, 024h, 018h, 050h, 0FFh, 052h
    db 018h, 0D9h, 05Ch, 024h, 018h, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 06Ah, 000h, 08Dh, 054h, 024h, 014h, 052h, 08Dh, 046h, 038h, 050h, 056h
    call ?j_0004a327@@YAXXZ
    db 084h, 0C0h, 075h, 04Dh, 08Bh, 08Eh, 000h, 002h, 000h, 000h, 08Bh, 011h, 0FFh, 052h, 03Ch, 085h
    db 0C0h, 074h, 010h, 08Bh, 08Eh, 000h, 002h, 000h, 000h, 08Bh, 001h, 0FFh, 050h, 03Ch, 08Bh, 040h
    db 008h, 0EBh, 002h, 033h, 0C0h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 074h, 00Ah, 06Ah, 001h, 056h, 08Bh, 0C8h
    call ?j_0001b94b@@YAXXZ
    db 06Ah, 000h, 06Ah, 008h, 08Bh, 0CEh
    call ?j_00014506@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 01Ch, 0C3h, 080h, 07Fh, 018h, 001h, 06Ah, 002h, 075h, 00Fh, 08Dh
    db 04Ch, 024h, 014h, 051h, 08Dh, 04Bh, 020h
    call ?j_00010f91@@YAXXZ
    db 0EBh, 00Dh, 08Dh, 054h, 024h, 014h, 052h, 08Dh, 04Bh, 020h
    call ?j_000245e6@@YAXXZ
    db 06Ah, 001h, 06Ah, 031h, 08Bh, 0CEh
    call ?j_00032dee@@YAXXZ
    db 08Bh, 08Eh, 02Ch, 001h, 000h, 000h, 0B8h, 000h, 000h, 002h, 000h, 085h, 0C8h, 075h, 00Fh, 00Bh
    db 0C8h, 089h, 08Eh, 02Ch, 001h, 000h, 000h, 08Bh, 0CEh
    call ?j_0002191d@@YAXXZ
    db 05Fh, 05Eh, 05Bh, 083h, 0C4h, 01Ch, 0C3h
?d_00205440@@YAXXZ ENDP
_TEXT$d00605440 ENDS
_TEXT SEGMENT

; ghidra: FUN_00605610  retail @ 0x00205610 size 47
public ?d_00205610@@YAXXZ
?d_00205610@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0B0h, 0F0h, 01h, 00h, 00h, 8Bh, 06h, 85h, 0C0h, 74h
    db 1Ah, 8Bh, 50h, 0Ch, 8Dh, 48h, 0Ch, 0FFh, 92h, 98h, 00h, 00h, 00h, 85h, 0C0h, 75h
    db 0Ch, 8Bh, 46h, 04h, 83h, 0C6h, 04h, 85h, 0C0h, 75h, 0E6h, 33h, 0C0h, 5Eh, 0C3h
?d_00205610@@YAXXZ ENDP

; ghidra: FUN_00605660  retail @ 0x00205660 size 32
public ?d_00205660@@YAXXZ
?d_00205660@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0C0h, 5Fh, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0D3h, 25h, 0E4h, 0FFh
?d_00205660@@YAXXZ ENDP

; ghidra: FUN_00605a20  retail @ 0x00205A20 size 126
public ?d_00205a20@@YAXXZ
?d_00205a20@@YAXXZ PROC
    db 8Bh, 49h, 04h, 8Bh, 41h, 0Ch, 83h, 0ECh, 0Ch, 3Dh, 00h, 00h, 80h, 3Fh, 75h, 62h
    db 8Bh, 44h, 24h, 14h, 0D9h, 40h, 38h, 0D9h, 40h, 3Ch, 8Bh, 40h, 40h, 89h, 44h, 24h
    db 08h, 0D9h, 0C9h, 8Bh, 44h, 24h, 10h, 0D8h, 20h, 0D9h, 1Ch, 24h, 0D8h, 60h, 04h, 0D9h
    db 44h, 24h, 08h, 0D8h, 60h, 08h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h
    db 0D9h, 04h, 24h, 0D8h, 0Ch, 24h, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 71h
    db 08h, 0D8h, 2Dh, 34h, 53h, 07h, 01h, 0D8h, 15h, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 01h, 74h, 14h, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 83h, 0C4h, 0Ch, 0C2h
    db 08h, 00h, 0D9h, 05h, 34h, 53h, 07h, 01h, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_00205a20@@YAXXZ ENDP

; ghidra: FUN_00605f80  retail @ 0x00205F80 size 17
public ?d_00205f80@@YAXXZ
?d_00205f80@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 44h, 62h, 0Ah, 01h, 0E8h, 90h, 0A9h, 64h, 00h
    db 0C3h
?d_00205f80@@YAXXZ ENDP

; ghidra: FUN_006060b0  retail @ 0x002060B0 size 61
public ?d_002060b0@@YAXXZ
?d_002060b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 7Ch, 18h, 8Bh, 51h, 28h, 2Bh, 51h, 24h, 0C1h, 0FAh
    db 02h, 3Bh, 0C2h, 73h, 0Bh, 8Bh, 49h, 24h, 8Bh, 0Ch, 81h, 83h, 0C1h, 08h, 0EBh, 06h
    db 8Bh, 49h, 08h, 83h, 0C1h, 38h, 8Bh, 11h, 8Bh, 44h, 24h, 04h, 89h, 10h, 8Bh, 51h
    db 04h, 89h, 50h, 04h, 8Bh, 49h, 08h, 89h, 48h, 08h, 0C2h, 08h, 00h
?d_002060b0@@YAXXZ ENDP

; ghidra: FUN_00606100  retail @ 0x00206100 size 61
public ?d_00206100@@YAXXZ
?d_00206100@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 7Ch, 18h, 8Bh, 51h, 28h, 2Bh, 51h, 24h, 0C1h, 0FAh
    db 02h, 3Bh, 0C2h, 73h, 0Bh, 8Bh, 49h, 24h, 8Bh, 0Ch, 81h, 83h, 0C1h, 14h, 0EBh, 06h
    db 8Bh, 49h, 08h, 83h, 0C1h, 38h, 8Bh, 11h, 8Bh, 44h, 24h, 04h, 89h, 10h, 8Bh, 51h
    db 04h, 89h, 50h, 04h, 8Bh, 49h, 08h, 89h, 48h, 08h, 0C2h, 08h, 00h
?d_00206100@@YAXXZ ENDP

; ghidra: FUN_006063c0  retail @ 0x002063C0 size 8
public ?d_002063c0@@YAXXZ
?d_002063c0@@YAXXZ PROC
    db 83h, 0E9h, 14h, 0E9h, 76h, 0CAh, 0E2h, 0FFh
?d_002063c0@@YAXXZ ENDP

; ghidra: FUN_00606710  retail @ 0x00206710 size 81
public ?d_00206710@@YAXXZ
?d_00206710@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 24h, 3Bh, 77h, 28h, 74h, 1Dh, 8Dh, 64h, 24h, 00h
    db 8Bh, 06h, 85h, 0C0h, 74h, 09h, 50h, 0E8h, 84h, 0B7h, 67h, 00h, 83h, 0C4h, 04h, 8Bh
    db 47h, 28h, 83h, 0C6h, 04h, 3Bh, 0F0h, 75h, 0E7h, 8Bh, 47h, 28h, 3Bh, 0C0h, 8Bh, 4Fh
    db 24h, 75h, 06h, 89h, 4Fh, 28h, 5Fh, 5Eh, 0C3h, 8Bh, 0F0h, 2Bh, 0F0h, 56h, 50h, 51h
    db 0FFh, 15h, 5Ch, 94h, 35h, 01h, 03h, 0C6h, 83h, 0C4h, 0Ch, 89h, 47h, 28h, 5Fh, 5Eh
    db 0C3h
?d_00206710@@YAXXZ ENDP

; ghidra: FUN_00606960  retail @ 0x00206960 size 383
public ?d_00206960@@YAXXZ
?d_00206960@@YAXXZ PROC
    db 83h, 0ECh, 20h, 8Bh, 44h, 24h, 24h, 55h, 56h, 8Bh, 0F1h, 8Bh, 0Dh, 98h, 08h, 2Fh
    db 01h, 50h, 89h, 74h, 24h, 10h, 0E8h, 0D8h, 88h, 0E1h, 0FFh, 8Bh, 0E8h, 85h, 0EDh, 75h
    db 0Ah, 5Eh, 32h, 0C0h, 5Dh, 83h, 0C4h, 20h, 0C2h, 08h, 00h, 8Bh, 56h, 04h, 53h, 8Bh
    db 5Eh, 08h, 2Bh, 0DAh, 0C1h, 0FBh, 02h, 85h, 0DBh, 75h, 0Bh, 5Bh, 5Eh, 32h, 0C0h, 5Dh
    db 83h, 0C4h, 20h, 0C2h, 08h, 00h, 57h, 33h, 0FFh, 85h, 0DBh, 0C7h, 44h, 24h, 10h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0C7h, 44h, 24h, 34h, 80h, 4Fh, 0C3h, 47h, 77h, 13h, 5Fh, 5Bh, 5Eh
    db 32h, 0C0h, 5Dh, 83h, 0C4h, 20h, 0C2h, 08h, 00h, 8Bh, 74h, 24h, 14h, 8Dh, 49h, 00h
    db 8Bh, 4Eh, 04h, 8Bh, 34h, 0B9h, 8Bh, 46h, 20h, 85h, 0C0h, 0Fh, 85h, 0DDh, 00h, 00h
    db 00h, 8Bh, 45h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 0C7h, 0B8h, 0DFh, 0FFh, 8Bh, 88h, 0D8h, 00h, 00h, 00h, 0F6h, 0C5h, 04h, 75h, 0Bh, 8Bh
    db 46h, 04h, 85h, 0C0h, 0Fh, 85h, 0B4h, 00h, 00h, 00h, 0D9h, 46h, 08h, 8Bh, 46h, 1Ch
    db 0D9h, 46h, 0Ch, 8Bh, 56h, 10h, 0D9h, 46h, 14h, 89h, 44h, 24h, 2Ch, 0D9h, 46h, 18h
    db 89h, 54h, 24h, 20h, 0D9h, 0C9h, 0D8h, 0Dh, 5Ch, 61h, 08h, 01h, 0D9h, 5Ch, 24h, 24h
    db 0D8h, 0Dh, 5Ch, 61h, 08h, 01h, 0D9h, 44h, 24h, 2Ch, 0D8h, 0Dh, 5Ch, 61h, 08h, 01h
    db 0D9h, 5Ch, 24h, 2Ch, 0D9h, 0CAh, 0D8h, 64h, 24h, 24h, 0D9h, 5Ch, 24h, 18h, 0D8h, 0E1h
    db 0D9h, 5Ch, 24h, 1Ch, 0DDh, 0D8h, 0D9h, 44h, 24h, 20h, 0D8h, 64h, 24h, 2Ch, 0D9h, 5Ch
    db 24h, 20h, 0D9h, 44h, 24h, 18h, 0D8h, 65h, 38h, 0D9h, 44h, 24h, 1Ch, 0D8h, 65h, 3Ch
    db 0D9h, 44h, 24h, 20h, 0D8h, 65h, 40h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh
    db 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DBh, 0DDh, 0D8h, 0DDh, 0D8h, 0D8h
    db 54h, 24h, 34h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 22h, 8Bh, 54h, 24h, 18h, 0D9h, 5Ch
    db 24h, 34h, 8Bh, 4Ch, 24h, 38h, 8Bh, 44h, 24h, 1Ch, 89h, 11h, 8Bh, 54h, 24h, 20h
    db 89h, 41h, 04h, 89h, 7Ch, 24h, 10h, 89h, 51h, 08h, 0EBh, 02h, 0DDh, 0D8h, 47h, 3Bh
    db 0FBh, 0Fh, 82h, 02h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 0Fh, 8Ch, 0EAh
    db 0FEh, 0FFh, 0FFh, 5Fh, 5Bh, 5Eh, 0B0h, 01h, 5Dh, 83h, 0C4h, 20h, 0C2h, 08h, 00h
?d_00206960@@YAXXZ ENDP

; ghidra: FUN_00606b40  retail @ 0x00206B40 size 295
_TEXT ENDS
_TEXT$d00606b40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00606B40 size 295
public ?d_00206b40@@YAXXZ
?d_00206b40@@YAXXZ PROC
    db 083h, 0ECh, 020h, 08Bh, 044h, 024h, 024h, 056h, 08Bh, 0F1h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 089h, 044h, 024h, 010h, 075h, 00Ah, 083h, 0C8h, 0FFh, 05Eh, 083h, 0C4h, 020h, 0C2h
    db 004h, 000h, 053h, 08Dh, 04Eh, 0E0h
    call ?j_0001011d@@YAXXZ
    db 08Bh, 05Eh, 008h, 08Bh, 056h, 004h, 02Bh, 0DAh, 0C1h, 0FBh, 002h, 083h, 0C8h, 0FFh, 085h, 0DBh
    db 00Fh, 084h, 0D8h, 000h, 000h, 000h, 055h, 033h, 0EDh, 085h, 0DBh, 089h, 044h, 024h, 014h, 0C7h
    db 044h, 024h, 00Ch, 080h, 04Fh, 0C3h, 047h, 00Fh, 086h, 0C0h, 000h, 000h, 000h, 08Bh, 0F2h, 089h
    db 074h, 024h, 01Ch, 089h, 074h, 024h, 010h, 057h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh
    db 03Eh, 08Bh, 047h, 020h, 085h, 0C0h, 075h, 07Ah, 08Bh, 074h, 024h, 01Ch, 08Bh, 046h, 004h, 085h
    db 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 088h, 0D8h, 000h, 000h, 000h, 0F6h, 0C5h, 004h, 075h, 007h, 08Bh, 047h, 004h, 085h, 0C0h
    db 075h, 051h, 0D9h, 047h, 008h, 08Bh, 04Fh, 010h, 0D9h, 047h, 00Ch, 089h, 04Ch, 024h, 02Ch, 0D9h
    db 0C9h, 0D8h, 066h, 038h, 0D9h, 05Ch, 024h, 024h, 0D8h, 066h, 03Ch, 0D9h, 044h, 024h, 02Ch, 0D8h
    db 066h, 040h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h
    db 0D8h, 04Ch, 024h, 024h, 0DEh, 0C1h, 0D9h, 0FAh, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 054h, 024h, 010h
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ah, 0D9h, 05Ch, 024h, 010h, 089h, 06Ch, 024h, 018h, 0EBh
    db 002h, 0DDh, 0D8h, 08Bh, 074h, 024h, 014h, 045h, 083h, 0C6h, 004h, 03Bh, 0EBh, 089h, 074h, 024h
    db 014h, 00Fh, 082h, 069h, 0FFh, 0FFh, 0FFh, 08Bh, 044h, 024h, 018h, 085h, 0C0h, 05Fh, 07Ch, 00Eh
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 00Ch, 082h, 08Bh, 054h, 024h, 030h, 089h, 051h, 020h, 05Dh, 05Bh
    db 05Eh, 083h, 0C4h, 020h, 0C2h, 004h, 000h
?d_00206b40@@YAXXZ ENDP
_TEXT$d00606b40 ENDS
_TEXT SEGMENT

; ghidra: FUN_00606cb0  retail @ 0x00206CB0 size 657
public ?d_00206cb0@@YAXXZ
?d_00206cb0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DCh, 0BEh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0E4h, 02h, 00h, 00h, 53h, 55h, 56h, 57h, 68h
    db 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h, 00h, 6Ah, 0Ah, 6Ah, 0Ch, 8Dh, 44h, 24h
    db 34h, 8Bh, 0F9h, 50h, 89h, 7Ch, 24h, 34h, 33h, 0EDh, 0E8h, 0F5h, 01h, 7Fh, 00h, 89h
    db 0ACh, 24h, 0FCh, 02h, 00h, 00h, 8Dh, 0B4h, 24h, 14h, 01h, 00h, 00h, 0BBh, 0Ah, 00h
    db 00h, 00h, 68h, 61h, 55h, 44h, 00h, 6Ah, 03h, 6Ah, 10h, 56h, 0E8h, 4Bh, 41h, 0E0h
    db 0FFh, 83h, 0C6h, 30h, 4Bh, 75h, 0EBh, 68h, 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h
    db 00h, 6Ah, 0Ah, 6Ah, 0Ch, 8Dh, 8Ch, 24h, 0ACh, 00h, 00h, 00h, 51h, 0E8h, 0B2h, 01h
    db 7Fh, 00h, 8Bh, 4Fh, 08h, 33h, 0DBh, 53h, 6Ah, 01h, 8Dh, 94h, 24h, 1Ch, 01h, 00h
    db 00h, 52h, 8Dh, 44h, 24h, 30h, 50h, 6Ah, 0Ah, 68h, 98h, 63h, 0Ah, 01h, 0C6h, 84h
    db 24h, 14h, 03h, 00h, 00h, 01h, 0E8h, 52h, 9Ah, 0E0h, 0FFh, 3Bh, 0C3h, 89h, 44h, 24h
    db 1Ch, 0Fh, 8Eh, 0A8h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 24h, 83h, 0C7h, 24h, 89h, 4Ch
    db 24h, 10h, 8Dh, 0B4h, 24h, 24h, 01h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 6Ah, 24h, 0E8h, 0A9h, 0B1h, 67h, 00h, 8Bh, 4Ch, 24h, 14h, 89h, 28h, 89h, 58h, 04h
    db 8Bh, 19h, 8Dh, 50h, 08h, 89h, 1Ah, 8Bh, 59h, 04h, 89h, 5Ah, 04h, 8Bh, 49h, 08h
    db 89h, 4Ah, 08h, 0D9h, 46h, 10h, 0D9h, 06h, 33h, 0DBh, 0D9h, 46h, 0F0h, 83h, 0C4h, 04h
    db 0D9h, 0E0h, 89h, 44h, 24h, 18h, 0D9h, 58h, 14h, 0D9h, 0E0h, 0D9h, 58h, 18h, 0D9h, 0E0h
    db 0D9h, 58h, 1Ch, 89h, 58h, 20h, 8Bh, 4Fh, 04h, 3Bh, 4Fh, 08h, 74h, 0Ch, 3Bh, 0CBh
    db 74h, 02h, 89h, 01h, 83h, 47h, 04h, 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h
    db 24h, 1Fh, 52h, 8Dh, 44h, 24h, 24h, 50h, 51h, 8Bh, 0CFh, 0E8h, 0A2h, 34h, 0E3h, 0FFh
    db 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h, 1Ch, 45h, 83h, 0C2h, 0Ch, 83h, 0C6h, 30h, 3Bh
    db 0E8h, 89h, 54h, 24h, 10h, 0Fh, 8Ch, 75h, 0FFh, 0FFh, 0FFh, 8Bh, 7Ch, 24h, 20h, 8Bh
    db 4Fh, 08h, 53h, 6Ah, 01h, 8Dh, 94h, 24h, 1Ch, 01h, 00h, 00h, 52h, 8Dh, 44h, 24h
    db 30h, 50h, 6Ah, 0Ah, 68h, 88h, 63h, 0Ah, 01h, 0E8h, 7Fh, 99h, 0E0h, 0FFh, 3Bh, 0C3h
    db 0Fh, 8Eh, 0B2h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 24h, 83h, 0C7h, 24h, 89h, 4Ch, 24h
    db 10h, 8Dh, 0B4h, 24h, 24h, 01h, 00h, 00h, 89h, 44h, 24h, 18h, 8Dh, 64h, 24h, 00h
    db 6Ah, 24h, 0E8h, 0D9h, 0B0h, 67h, 00h, 8Bh, 4Ch, 24h, 14h, 89h, 28h, 0C7h, 40h, 04h
    db 01h, 00h, 00h, 00h, 8Bh, 19h, 8Dh, 50h, 08h, 89h, 1Ah, 8Bh, 59h, 04h, 89h, 5Ah
    db 04h, 8Bh, 49h, 08h, 89h, 4Ah, 08h, 0D9h, 46h, 10h, 0D9h, 06h, 83h, 0C4h, 04h, 0D9h
    db 46h, 0F0h, 89h, 44h, 24h, 1Ch, 0D9h, 0E0h, 0D9h, 58h, 14h, 0D9h, 0E0h, 0D9h, 58h, 18h
    db 0D9h, 0E0h, 0D9h, 58h, 1Ch, 0C7h, 40h, 20h, 00h, 00h, 00h, 00h, 8Bh, 4Fh, 04h, 3Bh
    db 4Fh, 08h, 74h, 0Ch, 85h, 0C9h, 74h, 02h, 89h, 01h, 83h, 47h, 04h, 04h, 0EBh, 16h
    db 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 1Fh, 52h, 8Dh, 44h, 24h, 28h, 50h, 51h, 8Bh
    db 0CFh, 0E8h, 0CCh, 33h, 0E3h, 0FFh, 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h, 18h, 83h, 0C2h
    db 0Ch, 45h, 83h, 0C6h, 30h, 48h, 89h, 54h, 24h, 10h, 89h, 44h, 24h, 18h, 0Fh, 85h
    db 6Ch, 0FFh, 0FFh, 0FFh, 8Bh, 7Ch, 24h, 20h, 68h, 4Ch, 36h, 41h, 00h, 6Ah, 0Ah, 6Ah
    db 0Ch, 8Dh, 8Ch, 24h, 0A8h, 00h, 00h, 00h, 51h, 0C6h, 47h, 30h, 01h, 0C6h, 84h, 24h
    db 0Ch, 03h, 00h, 00h, 00h, 0E8h, 6Ch, 0FEh, 7Eh, 00h, 68h, 4Ch, 36h, 41h, 00h, 6Ah
    db 0Ah, 6Ah, 0Ch, 8Dh, 54h, 24h, 30h, 52h, 0C7h, 84h, 24h, 0Ch, 03h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 4Eh, 0FEh, 7Eh, 00h, 8Bh, 8Ch, 24h, 0F4h, 02h, 00h, 00h, 5Fh
    db 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0F0h, 02h, 00h, 00h
    db 0C3h
?d_00206cb0@@YAXXZ ENDP

; ghidra: FUN_00606ff0  retail @ 0x00206FF0 size 393
public ?d_00206ff0@@YAXXZ
?d_00206ff0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 55h, 56h, 8Bh, 74h, 24h, 14h, 8Bh, 06h, 8Bh, 0E9h, 57h, 8Dh, 4Ch
    db 24h, 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 0C6h, 44h, 24h, 11h, 01h, 0FFh
    db 50h, 28h, 56h, 8Bh, 0CDh, 0E8h, 0A7h, 0D4h, 0DFh, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h
    db 08h, 84h, 0C0h, 8Bh, 16h, 8Bh, 0CEh, 0Fh, 84h, 87h, 00h, 00h, 00h, 8Bh, 45h, 28h
    db 2Bh, 45h, 24h, 0C1h, 0F8h, 02h, 89h, 44h, 24h, 18h, 8Dh, 44h, 24h, 18h, 50h, 0FFh
    db 52h, 74h, 8Bh, 44h, 24h, 18h, 33h, 0FFh, 85h, 0C0h, 0Fh, 86h, 12h, 01h, 00h, 00h
    db 8Bh, 4Dh, 24h, 8Bh, 14h, 0B9h, 83h, 0C2h, 04h, 52h, 56h, 0E8h, 0A8h, 0B4h, 0E0h, 0FFh
    db 8Bh, 4Dh, 24h, 8Bh, 14h, 0B9h, 8Bh, 06h, 83h, 0C4h, 08h, 52h, 8Bh, 0CEh, 0FFh, 50h
    db 78h, 8Bh, 4Dh, 24h, 8Bh, 14h, 0B9h, 8Bh, 06h, 83h, 0C2h, 08h, 52h, 8Bh, 0CEh, 0FFh
    db 50h, 60h, 8Bh, 4Dh, 24h, 8Bh, 14h, 0B9h, 8Bh, 06h, 83h, 0C2h, 14h, 52h, 8Bh, 0CEh
    db 0FFh, 50h, 60h, 8Bh, 45h, 24h, 8Bh, 0Ch, 0B8h, 83h, 0C1h, 20h, 51h, 56h, 0E8h, 11h
    db 59h, 0E0h, 0FFh, 8Bh, 44h, 24h, 20h, 83h, 0C4h, 08h, 47h, 3Bh, 0F8h, 72h, 0A1h, 0E9h
    db 0AEh, 00h, 00h, 00h, 8Dh, 44h, 24h, 18h, 33h, 0FFh, 50h, 89h, 7Ch, 24h, 1Ch, 0FFh
    db 52h, 74h, 39h, 7Ch, 24h, 18h, 89h, 7Ch, 24h, 0Ch, 0Fh, 86h, 92h, 00h, 00h, 00h
    db 53h, 8Dh, 5Dh, 24h, 8Bh, 0CDh, 0E8h, 0AEh, 1Eh, 0E1h, 0FFh, 6Ah, 24h, 0E8h, 4Eh, 0AEh
    db 67h, 00h, 8Bh, 0F8h, 8Dh, 4Fh, 04h, 51h, 56h, 89h, 7Ch, 24h, 20h, 0E8h, 16h, 0B4h
    db 0E0h, 0FFh, 8Bh, 16h, 83h, 0C4h, 0Ch, 57h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 06h, 8Dh
    db 4Fh, 08h, 51h, 8Bh, 0CEh, 0FFh, 50h, 60h, 8Bh, 16h, 8Dh, 47h, 14h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 60h, 8Dh, 4Fh, 20h, 51h, 56h, 0E8h, 97h, 58h, 0E0h, 0FFh, 8Bh, 43h, 04h
    db 8Bh, 4Bh, 08h, 83h, 0C4h, 08h, 3Bh, 0C1h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 38h
    db 83h, 43h, 04h, 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 24h, 52h, 8Dh
    db 4Ch, 24h, 20h, 51h, 50h, 8Bh, 0CBh, 0E8h, 46h, 31h, 0E3h, 0FFh, 8Bh, 44h, 24h, 10h
    db 8Bh, 4Ch, 24h, 1Ch, 40h, 3Bh, 0C1h, 89h, 44h, 24h, 10h, 0Fh, 82h, 73h, 0FFh, 0FFh
    db 0FFh, 5Bh, 8Bh, 16h, 83h, 0C5h, 30h, 55h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h
    db 5Fh, 5Eh, 5Dh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_00206ff0@@YAXXZ ENDP

; ghidra: FUN_006071e0  retail @ 0x002071E0 size 16
public ?d_002071e0@@YAXXZ
?d_002071e0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 7Eh, 87h, 0E0h, 0FFh, 8Bh, 0CEh, 5Eh, 0E9h, 1Bh, 0ECh, 0E0h, 0FFh
?d_002071e0@@YAXXZ ENDP

; ghidra: FUN_00607230  retail @ 0x00207230 size 30
public ?d_00207230@@YAXXZ
?d_00207230@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 30h, 84h, 0C0h, 75h, 09h, 0E8h, 27h, 87h, 0E0h, 0FFh, 0C6h
    db 46h, 30h, 01h, 8Bh, 46h, 28h, 2Bh, 46h, 24h, 0C1h, 0F8h, 02h, 5Eh, 0C3h
?d_00207230@@YAXXZ ENDP

; ghidra: FUN_00607260  retail @ 0x00207260 size 41
public ?d_00207260@@YAXXZ
?d_00207260@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 20h, 84h, 0C0h, 8Dh, 4Eh, 0F0h, 75h, 10h, 0E8h, 0F4h, 86h
    db 0E0h, 0FFh, 0C6h, 46h, 20h, 01h, 0B8h, 05h, 00h, 00h, 00h, 5Eh, 0C3h, 0E8h, 9Bh, 8Eh
    db 0E0h, 0FFh, 0B8h, 05h, 00h, 00h, 00h, 5Eh, 0C3h
?d_00207260@@YAXXZ ENDP

; ghidra: FUN_00607450  retail @ 0x00207450 size 21
public ?d_00207450@@YAXXZ
?d_00207450@@YAXXZ PROC
    db 8Bh, 51h, 08h, 8Bh, 44h, 24h, 04h, 6Ah, 01h, 52h, 89h, 41h, 20h, 0E8h, 78h, 0E3h
    db 0E0h, 0FFh, 0C2h, 04h, 00h
?d_00207450@@YAXXZ ENDP

; ghidra: FUN_00607640  retail @ 0x00207640 size 127
public ?d_00207640@@YAXXZ
?d_00207640@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 85h, 0C0h, 8Bh, 5Eh, 0F4h, 57h, 8Bh, 7Eh, 0F8h
    db 74h, 64h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 0F5h, 7Bh, 0E1h, 0FFh, 85h, 0C0h
    db 74h, 54h, 0F6h, 80h, 44h, 03h, 00h, 00h, 01h, 74h, 4Bh, 8Bh, 0Dh, 88h, 0F1h, 2Eh
    db 01h, 55h, 8Dh, 43h, 0Ch, 50h, 0E8h, 0DFh, 82h, 0E2h, 0FFh, 8Bh, 0Dh, 88h, 0F1h, 2Eh
    db 01h, 83h, 0C3h, 08h, 53h, 8Bh, 0E8h, 0E8h, 0CEh, 82h, 0E2h, 0FFh, 55h, 8Bh, 0CFh, 8Bh
    db 0D8h, 0E8h, 79h, 18h, 0E3h, 0FFh, 53h, 8Bh, 0CFh, 0E8h, 0E0h, 32h, 0E1h, 0FFh, 8Bh, 0CFh
    db 0E8h, 2Ah, 09h, 0E2h, 0FFh, 5Dh, 5Fh, 0C7h, 46h, 10h, 00h, 00h, 00h, 00h, 5Eh, 0B8h
    db 0FFh, 0FFh, 0FFh, 3Fh, 5Bh, 0C3h, 5Fh, 5Eh, 0B8h, 05h, 00h, 00h, 00h, 5Bh, 0C3h
?d_00207640@@YAXXZ ENDP

; ghidra: FUN_006077a0  retail @ 0x002077A0 size 39
public ?d_002077a0@@YAXXZ
?d_002077a0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0B8h, 65h, 0Ah, 01h, 0C7h, 41h, 24h, 0A4h, 65h, 0Ah, 01h, 0C7h, 41h
    db 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh
    db 09h, 01h, 0E9h, 8Ch, 04h, 0E4h, 0FFh
?d_002077a0@@YAXXZ ENDP

; ghidra: FUN_006077d0  retail @ 0x002077D0 size 157
public ?d_002077d0@@YAXXZ
?d_002077d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 0E3h, 0CCh, 0DFh, 0FFh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 7Fh, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h
    db 0Ch, 88h, 44h, 24h, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh
    db 16h, 8Dh, 47h, 28h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 8Dh, 47h, 2Ch, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 8Dh, 47h, 30h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h
    db 8Bh, 16h, 8Dh, 47h, 34h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 8Dh, 47h, 38h
    db 50h, 8Bh, 0CEh, 0FFh, 52h, 6Ch, 8Bh, 16h, 8Dh, 47h, 3Ch, 50h, 8Bh, 0CEh, 0FFh, 52h
    db 74h, 8Bh, 16h, 8Dh, 47h, 48h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh
    db 16h, 8Dh, 47h, 4Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 83h, 0C7h, 40h, 57h
    db 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_002077d0@@YAXXZ ENDP

; ghidra: FUN_00608330  retail @ 0x00208330 size 20
public ?d_00208330@@YAXXZ
?d_00208330@@YAXXZ PROC
    db 33h, 0C0h, 83h, 3Ch, 81h, 00h, 75h, 09h, 40h, 83h, 0F8h, 0Ah, 72h, 0F4h, 32h, 0C0h
    db 0C3h, 0B0h, 01h, 0C3h
?d_00208330@@YAXXZ ENDP

; ghidra: FUN_00608350  retail @ 0x00208350 size 77
public ?d_00208350@@YAXXZ
?d_00208350@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 10h, 56h, 21h, 11h, 8Bh, 50h, 04h, 21h, 51h, 04h, 8Bh
    db 50h, 08h, 21h, 51h, 08h, 8Bh, 50h, 0Ch, 21h, 51h, 0Ch, 8Bh, 50h, 10h, 21h, 51h
    db 10h, 8Bh, 50h, 14h, 21h, 51h, 14h, 8Bh, 50h, 18h, 21h, 51h, 18h, 8Bh, 50h, 1Ch
    db 21h, 51h, 1Ch, 8Bh, 50h, 20h, 8Bh, 71h, 20h, 23h, 0F2h, 8Bh, 51h, 24h, 89h, 71h
    db 20h, 8Bh, 40h, 24h, 23h, 0D0h, 89h, 51h, 24h, 5Eh, 0C2h, 04h, 00h
?d_00208350@@YAXXZ ENDP

; ghidra: FUN_00608480  retail @ 0x00208480 size 150
public ?d_00208480@@YAXXZ
?d_00208480@@YAXXZ PROC
    db 83h, 0ECh, 28h, 56h, 8Bh, 0F1h, 57h, 0B9h, 0Ah, 00h, 00h, 00h, 8Dh, 7Ch, 24h, 08h
    db 0F3h, 0A5h, 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 0F7h, 0D0h
    db 89h, 44h, 24h, 08h, 8Bh, 44h, 24h, 14h, 0F7h, 0D0h, 0F7h, 0D1h, 89h, 44h, 24h, 14h
    db 8Bh, 44h, 24h, 20h, 89h, 4Ch, 24h, 0Ch, 8Bh, 4Ch, 24h, 18h, 0F7h, 0D2h, 89h, 54h
    db 24h, 10h, 8Bh, 54h, 24h, 1Ch, 0F7h, 0D0h, 0F7h, 0D1h, 89h, 44h, 24h, 20h, 8Bh, 44h
    db 24h, 2Ch, 89h, 4Ch, 24h, 18h, 8Bh, 4Ch, 24h, 24h, 0F7h, 0D2h, 89h, 54h, 24h, 1Ch
    db 8Bh, 54h, 24h, 28h, 0F7h, 0D0h, 0F7h, 0D1h, 89h, 44h, 24h, 2Ch, 8Bh, 44h, 24h, 34h
    db 89h, 4Ch, 24h, 24h, 0F7h, 0D2h, 0B9h, 0Ah, 00h, 00h, 00h, 8Dh, 74h, 24h, 08h, 8Bh
    db 0F8h, 89h, 54h, 24h, 28h, 66h, 0C7h, 44h, 24h, 2Eh, 00h, 00h, 0F3h, 0A5h, 5Fh, 5Eh
    db 83h, 0C4h, 28h, 0C2h, 04h, 00h
?d_00208480@@YAXXZ ENDP

; ghidra: FUN_00608600  retail @ 0x00208600 size 144
public ?d_00208600@@YAXXZ
?d_00208600@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 56h, 8Bh, 0D0h, 89h, 0Ah, 89h, 4Ah, 04h, 89h, 4Ah, 08h, 8Bh
    db 4Ch, 24h, 0Ch, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h
    db 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 10h, 8Bh, 0D1h, 83h, 0E1h, 1Fh
    db 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh
    db 4Ch, 24h, 14h, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h
    db 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh, 4Ch, 24h, 18h, 8Bh, 0D1h, 83h, 0E1h, 1Fh
    db 0C1h, 0EAh, 05h, 8Dh, 14h, 90h, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 09h, 32h, 8Bh
    db 4Ch, 24h, 1Ch, 8Bh, 0D1h, 83h, 0E1h, 1Fh, 0BEh, 01h, 00h, 00h, 00h, 0D3h, 0E6h, 0C1h
    db 0EAh, 05h, 8Bh, 0Ch, 90h, 8Dh, 14h, 90h, 0Bh, 0CEh, 89h, 0Ah, 5Eh, 0C2h, 18h, 00h
?d_00208600@@YAXXZ ENDP

; ghidra: FUN_00608810  retail @ 0x00208810 size 458
public ?d_00208810@@YAXXZ
?d_00208810@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 68h, 0D8h, 36h, 07h, 01h, 57h, 8Bh
    db 0F1h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 5Eh, 8Bh, 44h
    db 24h, 18h, 80h, 38h, 00h, 75h, 32h, 8Bh, 4Ch, 24h, 1Ch, 80h, 39h, 00h, 75h, 29h
    db 33h, 0D2h, 89h, 16h, 89h, 56h, 04h, 89h, 56h, 08h, 89h, 56h, 0Ch, 89h, 56h, 10h
    db 89h, 56h, 14h, 89h, 56h, 18h, 89h, 56h, 1Ch, 89h, 56h, 20h, 5Fh, 89h, 56h, 24h
    db 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh, 44h
    db 24h, 0Ch, 6Ah, 02h, 50h, 0E8h, 86h, 7Dh, 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh
    db 1Dh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h, 74h, 0E4h, 7Eh, 00h, 8Ah, 07h, 3Ch, 2Bh
    db 75h, 67h, 8Bh, 54h, 24h, 18h, 80h, 3Ah, 00h, 74h, 23h, 68h, 0A4h, 0EBh, 08h, 01h
    db 8Dh, 44h, 24h, 0Ch, 6Ah, 02h, 50h, 0E8h, 54h, 7Dh, 64h, 00h, 83h, 0C4h, 0Ch, 68h
    db 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h, 42h, 0E4h, 7Eh, 00h, 68h, 18h
    db 69h, 2Ah, 01h, 47h, 57h, 0E8h, 16h, 81h, 64h, 00h, 8Bh, 0C8h, 8Bh, 0D0h, 83h, 0E1h
    db 1Fh, 0C1h, 0EAh, 05h, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 8Bh, 0Ch, 96h, 8Dh, 14h
    db 96h, 83h, 0C4h, 08h, 0Bh, 0C8h, 89h, 0Ah, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 0C6h, 01h, 01h
    db 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 3Ch, 2Dh, 75h, 69h, 8Bh, 54h, 24h
    db 18h, 80h, 3Ah, 00h, 74h, 23h, 68h, 0A4h, 0EBh, 08h, 01h, 8Dh, 44h, 24h, 0Ch, 6Ah
    db 02h, 50h, 0E8h, 0E9h, 7Ch, 64h, 00h, 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh
    db 4Ch, 24h, 0Ch, 51h, 0E8h, 0D7h, 0E3h, 7Eh, 00h, 68h, 18h, 69h, 2Ah, 01h, 47h, 57h
    db 0E8h, 0ABh, 80h, 64h, 00h, 8Bh, 0C8h, 8Bh, 0D0h, 83h, 0E1h, 1Fh, 0B8h, 01h, 00h, 00h
    db 00h, 0D3h, 0E0h, 0C1h, 0EAh, 05h, 8Bh, 0Ch, 96h, 8Dh, 14h, 96h, 83h, 0C4h, 08h, 0F7h
    db 0D0h, 23h, 0C8h, 89h, 0Ah, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 0C6h, 01h, 01h, 0B0h, 01h, 5Eh
    db 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 8Bh, 54h, 24h, 1Ch, 80h, 3Ah, 00h, 74h, 23h, 68h
    db 0A4h, 0EBh, 08h, 01h, 8Dh, 44h, 24h, 0Ch, 6Ah, 02h, 50h, 0E8h, 80h, 7Ch, 64h, 00h
    db 83h, 0C4h, 0Ch, 68h, 30h, 0FCh, 1Dh, 01h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0E8h, 6Eh, 0E3h
    db 7Eh, 00h, 53h, 8Bh, 5Ch, 24h, 1Ch, 80h, 3Bh, 00h, 75h, 07h, 8Bh, 0CEh, 0E8h, 0A7h
    db 8Fh, 0E1h, 0FFh, 68h, 18h, 69h, 2Ah, 01h, 57h, 0E8h, 32h, 80h, 64h, 00h, 8Bh, 0C8h
    db 8Bh, 0D0h, 83h, 0E1h, 1Fh, 0C1h, 0EAh, 05h, 0B8h, 01h, 00h, 00h, 00h, 0D3h, 0E0h, 8Bh
    db 0Ch, 96h, 8Dh, 14h, 96h, 83h, 0C4h, 08h, 0Bh, 0C8h, 89h, 0Ah, 0C6h, 03h, 01h, 5Bh
    db 5Fh, 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h
?d_00208810@@YAXXZ ENDP

; ghidra: FUN_00608a50  retail @ 0x00208A50 size 1060
public ?d_00208a50@@YAXXZ
?d_00208a50@@YAXXZ PROC
    db 83h, 0ECh, 68h, 53h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 0F4h, 57h, 8Bh, 7Eh, 0F8h, 85h, 0FFh
    db 89h, 5Ch, 24h, 14h, 75h, 0Ch, 5Fh, 5Eh, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 5Bh, 83h, 0C4h
    db 68h, 0C3h, 0A1h, 0ACh, 0D5h, 2Eh, 01h, 0D9h, 05h, 34h, 53h, 07h, 01h, 8Bh, 88h, 0E0h
    db 16h, 00h, 00h, 89h, 4Ch, 24h, 0Ch, 0D9h, 44h, 24h, 0Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h
    db 0C4h, 44h, 0Fh, 8Bh, 0D8h, 00h, 00h, 00h, 81h, 7Eh, 28h, 00h, 00h, 80h, 3Fh, 0Fh
    db 85h, 0CBh, 00h, 00h, 00h, 0F6h, 83h, 0A4h, 01h, 00h, 00h, 06h, 0Fh, 85h, 0BEh, 00h
    db 00h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 0Ch, 0DAh, 0E9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 44h, 7Ah, 18h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 57h, 0E8h, 0Dh, 46h, 0E1h
    db 0FFh, 5Fh, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 68h, 0C3h, 8Bh, 56h, 18h
    db 0DBh, 46h, 18h, 85h, 0D2h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0D8h, 4Ch, 24h
    db 0Ch, 0E8h, 42h, 0E3h, 7Eh, 00h, 0DBh, 46h, 1Ch, 89h, 46h, 18h, 8Bh, 46h, 1Ch, 85h
    db 0C0h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h, 01h, 0D8h, 4Ch, 24h, 0Ch, 0E8h, 26h, 0E3h
    db 7Eh, 00h, 0DBh, 46h, 20h, 8Bh, 4Eh, 20h, 85h, 0C9h, 89h, 46h, 1Ch, 7Dh, 06h, 0D8h
    db 05h, 58h, 53h, 07h, 01h, 0D8h, 4Ch, 24h, 0Ch, 0E8h, 0Ah, 0E3h, 7Eh, 00h, 0DBh, 46h
    db 24h, 8Bh, 56h, 24h, 85h, 0D2h, 89h, 46h, 20h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h
    db 01h, 0D8h, 4Ch, 24h, 0Ch, 0E8h, 0EEh, 0E2h, 7Eh, 00h, 0DBh, 46h, 3Ch, 8Bh, 4Eh, 3Ch
    db 85h, 0C9h, 89h, 46h, 24h, 8Bh, 44h, 24h, 0Ch, 89h, 46h, 28h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 0D8h, 4Ch, 24h, 0Ch, 0E8h, 0CBh, 0E2h, 7Eh, 00h, 89h, 46h, 3Ch
    db 8Bh, 15h, 98h, 08h, 2Fh, 01h, 8Bh, 42h, 3Ch, 89h, 44h, 24h, 0Ch, 8Bh, 46h, 2Ch
    db 0A8h, 04h, 55h, 74h, 66h, 0A8h, 08h, 75h, 62h, 8Bh, 4Eh, 18h, 8Bh, 46h, 1Ch, 8Bh
    db 6Eh, 20h, 8Bh, 56h, 3Ch, 41h, 40h, 45h, 89h, 46h, 1Ch, 8Bh, 46h, 24h, 42h, 85h
    db 0C0h, 89h, 4Eh, 18h, 89h, 6Eh, 20h, 89h, 56h, 3Ch, 74h, 04h, 40h, 89h, 46h, 24h
    db 8Bh, 0CFh, 0E8h, 79h, 90h, 0DFh, 0FFh, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h
    db 0C4h, 41h, 74h, 27h, 6Ah, 72h, 6Ah, 00h, 8Dh, 4Ch, 24h, 30h, 0E8h, 53h, 48h, 0E3h
    db 0FFh, 50h, 6Ah, 71h, 6Ah, 00h, 8Dh, 4Ch, 24h, 5Ch, 0E8h, 45h, 48h, 0E3h, 0FFh, 50h
    db 8Bh, 0CFh, 0E8h, 06h, 0Ah, 0E0h, 0FFh, 83h, 4Eh, 2Ch, 08h, 8Ah, 46h, 30h, 84h, 0C0h
    db 0Fh, 84h, 0D7h, 00h, 00h, 00h, 0F6h, 87h, 10h, 01h, 00h, 00h, 20h, 74h, 16h, 8Bh
    db 87h, 10h, 01h, 00h, 00h, 83h, 0E0h, 0DFh, 8Bh, 0CFh, 89h, 87h, 10h, 01h, 00h, 00h
    db 0E8h, 08h, 8Dh, 0E1h, 0FFh, 8Bh, 0CFh, 0E8h, 14h, 90h, 0DFh, 0FFh, 0D8h, 1Dh, 34h, 53h
    db 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 0A0h, 00h, 00h, 00h, 6Ah, 03h, 8Dh
    db 4Eh, 0F0h, 0C6h, 46h, 30h, 00h, 0E8h, 0D3h, 30h, 0E3h, 0FFh, 0F6h, 87h, 10h, 01h, 00h
    db 00h, 20h, 75h, 16h, 8Bh, 87h, 10h, 01h, 00h, 00h, 83h, 0C8h, 20h, 8Bh, 0CFh, 89h
    db 87h, 10h, 01h, 00h, 00h, 0E8h, 0C3h, 8Ch, 0E1h, 0FFh, 8Bh, 4Eh, 0F8h, 8Bh, 89h, 0FCh
    db 01h, 00h, 00h, 85h, 0C9h, 74h, 05h, 8Bh, 11h, 0FFh, 52h, 20h, 8Bh, 4Eh, 0F8h, 8Bh
    db 01h, 0FFh, 50h, 28h, 85h, 0C0h, 89h, 44h, 24h, 14h, 74h, 51h, 8Bh, 8Bh, 64h, 01h
    db 00h, 00h, 2Bh, 8Bh, 60h, 01h, 00h, 00h, 0C1h, 0F9h, 02h, 33h, 0EDh, 85h, 0C9h, 76h
    db 3Ch, 0EBh, 0Dh, 8Bh, 44h, 24h, 14h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 93h, 60h, 01h, 00h, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 8Dh, 0Ch, 0AAh, 6Ah
    db 00h, 51h, 8Bh, 0C8h, 0E8h, 0Dh, 05h, 0E3h, 0FFh, 8Bh, 93h, 64h, 01h, 00h, 00h, 2Bh
    db 93h, 60h, 01h, 00h, 00h, 45h, 0C1h, 0FAh, 02h, 3Bh, 0EAh, 72h, 0C6h, 8Bh, 07h, 8Bh
    db 0CFh, 0FFh, 50h, 28h, 8Bh, 0E8h, 85h, 0EDh, 74h, 2Eh, 8Bh, 4Ch, 24h, 10h, 3Bh, 4Eh
    db 3Ch, 72h, 25h, 81h, 0BBh, 0A0h, 01h, 00h, 00h, 00h, 0DEh, 0CAh, 0FAh, 74h, 19h, 8Ah
    db 46h, 38h, 84h, 0C0h, 75h, 12h, 0C6h, 46h, 38h, 01h, 8Bh, 93h, 9Ch, 01h, 00h, 00h
    db 52h, 8Bh, 0CDh, 0E8h, 80h, 65h, 0E3h, 0FFh, 8Bh, 44h, 24h, 10h, 3Bh, 46h, 18h, 0Fh
    db 82h, 0F0h, 00h, 00h, 00h, 0D9h, 43h, 34h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 0Fh, 85h, 0DCh, 00h, 00h, 00h, 0F6h, 87h, 0A4h, 01h, 00h, 00h, 08h
    db 75h, 14h, 8Bh, 0CFh, 0E8h, 0B8h, 12h, 0E1h, 0FFh, 84h, 0C0h, 75h, 09h, 6Ah, 03h, 8Bh
    db 0CFh, 0E8h, 0BCh, 56h, 0E1h, 0FFh, 6Ah, 01h, 6Ah, 37h, 8Bh, 0CFh, 0E8h, 9Dh, 0A0h, 0E2h
    db 0FFh, 0D9h, 43h, 34h, 0D8h, 76h, 28h, 8Bh, 4Fh, 38h, 8Bh, 57h, 3Ch, 0A1h, 0CCh, 0F4h
    db 2Eh, 01h, 89h, 4Ch, 24h, 1Ch, 6Ah, 01h, 89h, 54h, 24h, 24h, 6Ah, 00h, 8Bh, 0CFh
    db 0D8h, 6Fh, 40h, 0D9h, 5Ch, 24h, 2Ch, 8Bh, 18h, 0E8h, 13h, 16h, 0E3h, 0FFh, 8Bh, 4Ch
    db 24h, 28h, 8Bh, 54h, 24h, 24h, 50h, 51h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 52h, 0FFh
    db 53h, 1Ch, 0D8h, 5Ch, 24h, 24h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 0Eh, 0D9h, 44h, 24h
    db 24h, 0D8h, 25h, 48h, 67h, 0Ah, 01h, 0D9h, 5Ch, 24h, 24h, 8Dh, 44h, 24h, 1Ch, 50h
    db 8Bh, 0CFh, 0E8h, 0F0h, 13h, 0E3h, 0FFh, 85h, 0EDh, 74h, 4Ah, 8Bh, 5Ch, 24h, 18h, 8Ah
    db 83h, 0A6h, 01h, 00h, 00h, 84h, 0C0h, 74h, 3Ch, 8Ah, 85h, 0E4h, 00h, 00h, 00h, 84h
    db 0C0h, 75h, 32h, 6Ah, 00h, 8Bh, 0CDh, 0E8h, 0BCh, 8Bh, 0E3h, 0FFh, 8Bh, 55h, 00h, 81h
    db 0C3h, 6Ch, 01h, 00h, 00h, 53h, 8Bh, 0CDh, 0FFh, 52h, 20h, 6Ah, 00h, 8Bh, 0CDh, 0C6h
    db 85h, 0E4h, 00h, 00h, 00h, 01h, 0E8h, 0CBh, 0B3h, 0E2h, 0FFh, 0C7h, 85h, 0F8h, 00h, 00h
    db 00h, 0A6h, 9Bh, 44h, 3Bh, 8Bh, 44h, 24h, 10h, 3Bh, 46h, 1Ch, 0BBh, 02h, 00h, 00h
    db 00h, 5Dh, 72h, 12h, 84h, 5Eh, 2Ch, 75h, 0Dh, 6Ah, 01h, 8Dh, 4Eh, 0F0h, 0E8h, 0EBh
    db 2Eh, 0E3h, 0FFh, 09h, 5Eh, 2Ch, 8Bh, 4Ch, 24h, 0Ch, 3Bh, 4Eh, 20h, 72h, 15h, 53h
    db 8Dh, 4Eh, 0F0h, 0E8h, 0D6h, 2Eh, 0E3h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 57h, 0E8h
    db 9Ah, 42h, 0E1h, 0FFh, 8Bh, 76h, 24h, 85h, 0F6h, 74h, 24h, 39h, 74h, 24h, 0Ch, 72h
    db 1Eh, 8Bh, 8Fh, 20h, 01h, 00h, 00h, 0B8h, 00h, 80h, 00h, 00h, 85h, 0C8h, 75h, 0Fh
    db 0Bh, 0C8h, 89h, 8Fh, 20h, 01h, 00h, 00h, 8Bh, 0CFh, 0E8h, 0AEh, 8Ah, 0E1h, 0FFh, 5Fh
    db 5Eh, 0B8h, 01h, 00h
?d_00208a50@@YAXXZ ENDP

; ghidra: FUN_00608f90  retail @ 0x00208F90 size 324
public ?d_00208f90@@YAXXZ
?d_00208f90@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F8h, 0BFh, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 8Bh, 5Ch, 24h, 28h, 55h, 8Bh, 6Ch
    db 24h, 28h, 56h, 8Bh, 74h, 24h, 28h, 57h, 81h, 0C6h, 8Ch, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 10h, 04h, 00h, 00h, 00h, 8Bh, 7Eh, 0FCh, 3Bh, 3Eh, 74h, 19h, 8Dh, 49h, 00h
    db 8Bh, 0Fh, 85h, 0C9h, 74h, 07h, 53h, 55h, 0E8h, 35h, 74h, 0E3h, 0FFh, 8Bh, 06h, 83h
    db 0C7h, 04h, 3Bh, 0F8h, 75h, 0EAh, 8Bh, 7Eh, 0CCh, 3Bh, 7Eh, 0D0h, 74h, 19h, 8Bh, 0FFh
    db 8Bh, 0Fh, 85h, 0C9h, 74h, 07h, 53h, 55h, 0E8h, 89h, 9Dh, 0E1h, 0FFh, 8Bh, 46h, 0D0h
    db 83h, 0C7h, 04h, 3Bh, 0F8h, 75h, 0E9h, 8Bh, 7Eh, 2Ch, 3Bh, 7Eh, 30h, 74h, 18h, 90h
    db 8Bh, 0Fh, 85h, 0C9h, 74h, 07h, 53h, 55h, 0E8h, 1Fh, 83h, 0E1h, 0FFh, 8Bh, 46h, 30h
    db 83h, 0C7h, 04h, 3Bh, 0F8h, 75h, 0E9h, 8Bh, 44h, 24h, 10h, 83h, 0C6h, 0Ch, 48h, 89h
    db 44h, 24h, 10h, 75h, 91h, 8Bh, 44h, 24h, 2Ch, 8Bh, 88h, 6Ch, 01h, 00h, 00h, 05h
    db 6Ch, 01h, 00h, 00h, 85h, 0C9h, 74h, 79h, 66h, 83h, 79h, 04h, 00h, 74h, 72h, 68h
    db 6Ch, 41h, 09h, 01h, 51h, 89h, 64h, 24h, 34h, 8Bh, 0CCh, 50h, 0E8h, 0FFh, 0EAh, 67h
    db 00h, 8Dh, 44h, 24h, 18h, 50h, 0E8h, 0F2h, 0DBh, 0DFh, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 00h
    db 85h, 0C0h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh
    db 05h, 0B8h, 8Bh, 38h, 07h, 01h, 50h, 0E8h, 24h, 30h, 7Eh, 00h, 83h, 0C4h, 04h, 8Dh
    db 4Ch, 24h, 2Ch, 51h, 8Dh, 54h, 24h, 18h, 52h, 8Bh, 0CDh, 89h, 44h, 24h, 34h, 0E8h
    db 6Fh, 73h, 0E2h, 0FFh, 8Ah, 44h, 24h, 18h, 84h, 0C0h, 74h, 04h, 0C6h, 45h, 10h, 01h
    db 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 7Fh, 0E8h, 67h
    db 00h, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh
    db 83h, 0C4h, 18h, 0C3h
?d_00208f90@@YAXXZ ENDP

; ghidra: FUN_00609310  retail @ 0x00209310 size 178
public ?d_00209310@@YAXXZ
?d_00209310@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 20h, 0C0h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0F1h, 33h, 0DBh, 89h, 5Ch
    db 24h, 18h, 88h, 5Ch, 24h, 0Bh, 88h, 5Ch, 24h, 0Ah, 89h, 5Ch, 24h, 0Ch, 53h, 8Dh
    db 44h, 24h, 10h, 50h, 8Dh, 4Ch, 24h, 28h, 0C6h, 44h, 24h, 20h, 01h, 0E8h, 8Eh, 0EDh
    db 67h, 00h, 84h, 0C0h, 74h, 3Bh, 8Bh, 44h, 24h, 0Ch, 3Bh, 0C3h, 74h, 05h, 83h, 0C0h
    db 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Dh, 4Ch, 24h, 0Ah, 51h, 8Dh, 54h, 24h
    db 0Fh, 52h, 50h, 8Bh, 0CEh, 0E8h, 11h, 43h, 0E3h, 0FFh, 84h, 0C0h, 74h, 13h, 53h, 8Dh
    db 44h, 24h, 10h, 50h, 8Dh, 4Ch, 24h, 28h, 0E8h, 53h, 0EDh, 67h, 00h, 84h, 0C0h, 75h
    db 0C5h, 8Dh, 4Ch, 24h, 0Ch, 88h, 5Ch, 24h, 18h, 0E8h, 0A2h, 0E5h, 67h, 00h, 8Dh, 4Ch
    db 24h, 20h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 91h, 0E5h, 67h, 00h, 8Bh
    db 4Ch, 24h, 10h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h
    db 04h, 00h
?d_00209310@@YAXXZ ENDP

; ghidra: FUN_00609980  retail @ 0x00209980 size 444
public ?d_00209980@@YAXXZ
?d_00209980@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 88h, 0C1h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 8Bh, 1Dh, 0F4h, 0F8h, 2Eh, 01h, 0F6h, 0C3h, 01h
    db 56h, 57h, 75h, 2Eh, 68h, 0A7h, 00h, 00h, 00h, 68h, 8Eh, 00h, 00h, 00h, 68h, 8Dh
    db 00h, 00h, 00h, 68h, 8Ch, 00h, 00h, 00h, 68h, 8Bh, 00h, 00h, 00h, 83h, 0CBh, 01h
    db 6Ah, 00h, 0B9h, 0C4h, 0F8h, 2Eh, 01h, 89h, 1Dh, 0F4h, 0F8h, 2Eh, 01h, 0E8h, 3Ah, 41h
    db 0E0h, 0FFh, 0F6h, 0C3h, 02h, 75h, 18h, 83h, 0CBh, 02h, 68h, 94h, 0F8h, 2Eh, 01h, 0B9h
    db 0C4h, 0F8h, 2Eh, 01h, 89h, 1Dh, 0F4h, 0F8h, 2Eh, 01h, 0E8h, 0C7h, 0B8h, 0E1h, 0FFh, 8Bh
    db 7Ch, 24h, 24h, 8Dh, 0B7h, 28h, 01h, 00h, 00h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h
    db 00h, 8Bh, 4Ch, 24h, 20h, 8Dh, 44h, 24h, 0Ch, 50h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h
    db 20h, 00h, 00h, 00h, 00h, 0E8h, 19h, 9Ah, 0E2h, 0FFh, 8Bh, 15h, 0C4h, 0F8h, 2Eh, 01h
    db 8Bh, 1Eh, 8Bh, 4Eh, 04h, 23h, 0DAh, 89h, 1Eh, 0A1h, 0C8h, 0F8h, 2Eh, 01h, 8Bh, 5Eh
    db 0Ch, 23h, 0C8h, 8Bh, 46h, 08h, 89h, 4Eh, 04h, 8Bh, 0Dh, 0CCh, 0F8h, 2Eh, 01h, 23h
    db 0C1h, 8Bh, 4Eh, 10h, 89h, 46h, 08h, 8Bh, 15h, 0D0h, 0F8h, 2Eh, 01h, 23h, 0DAh, 89h
    db 5Eh, 0Ch, 0A1h, 0D4h, 0F8h, 2Eh, 01h, 8Bh, 5Eh, 18h, 23h, 0C8h, 8Bh, 46h, 14h, 89h
    db 4Eh, 10h, 8Bh, 0Dh, 0D8h, 0F8h, 2Eh, 01h, 23h, 0C1h, 8Bh, 4Eh, 1Ch, 89h, 46h, 14h
    db 8Bh, 15h, 0DCh, 0F8h, 2Eh, 01h, 23h, 0DAh, 89h, 5Eh, 18h, 0A1h, 0E0h, 0F8h, 2Eh, 01h
    db 8Bh, 5Eh, 24h, 23h, 0C8h, 8Bh, 46h, 20h, 89h, 4Eh, 1Ch, 8Bh, 0Dh, 0E4h, 0F8h, 2Eh
    db 01h, 23h, 0C1h, 89h, 46h, 20h, 8Bh, 15h, 0E8h, 0F8h, 2Eh, 01h, 51h, 8Dh, 44h, 24h
    db 10h, 23h, 0DAh, 89h, 64h, 24h, 28h, 8Bh, 0CCh, 50h, 89h, 5Eh, 24h, 0E8h, 0AEh, 0E0h
    db 67h, 00h, 8Dh, 0B7h, 50h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 90h, 15h, 0E1h, 0FFh, 8Ah
    db 0Dh, 0F4h, 0F8h, 2Eh, 01h, 0B8h, 04h, 00h, 00h, 00h, 84h, 0C8h, 75h, 24h, 8Bh, 0Dh
    db 0F4h, 0F8h, 2Eh, 01h, 6Ah, 22h, 6Ah, 21h, 6Ah, 20h, 6Ah, 1Fh, 0Bh, 0C8h, 6Ah, 1Eh
    db 89h, 0Dh, 0F4h, 0F8h, 2Eh, 01h, 6Ah, 00h, 0B9h, 84h, 0F8h, 2Eh, 01h, 0E8h, 0F6h, 0B1h
    db 0E2h, 0FFh, 8Bh, 0Dh, 84h, 0F8h, 2Eh, 01h, 8Bh, 1Eh, 8Bh, 7Eh, 04h, 23h, 0D9h, 8Bh
    db 4Eh, 08h, 89h, 1Eh, 8Bh, 15h, 88h, 0F8h, 2Eh, 01h, 23h, 0FAh, 89h, 7Eh, 04h, 0A1h
    db 8Ch, 0F8h, 2Eh, 01h, 23h, 0C8h, 89h, 4Eh, 08h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h
    db 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 16h, 0DEh, 67h, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 10h, 0C3h
?d_00209980@@YAXXZ ENDP

; ghidra: FUN_0060a7e0  retail @ 0x0020A7E0 size 17
public ?d_0020a7e0@@YAXXZ
?d_0020a7e0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 23h, 0B6h, 0E0h, 0FFh, 8Dh, 4Eh, 2Ch, 5Eh, 0E9h, 6Ah, 37h, 0E2h
    db 0FFh
?d_0020a7e0@@YAXXZ ENDP

; ghidra: FUN_0060a9e0  retail @ 0x0020A9E0 size 16
public ?d_0020a9e0@@YAXXZ
?d_0020a9e0@@YAXXZ PROC
    db 8Bh, 41h, 0DCh, 8Bh, 49h, 0D8h, 50h, 83h, 0C1h, 58h, 0E8h, 31h, 39h, 0E2h, 0FFh, 0C3h
?d_0020a9e0@@YAXXZ ENDP

; ghidra: FUN_0060ac40  retail @ 0x0020AC40 size 20
public ?d_0020ac40@@YAXXZ
?d_0020ac40@@YAXXZ PROC
    db 33h, 0C0h, 83h, 3Ch, 81h, 00h, 75h, 09h, 40h, 83h, 0F8h, 06h, 72h, 0F4h, 32h, 0C0h
    db 0C3h, 0B0h, 01h, 0C3h
?d_0020ac40@@YAXXZ ENDP

; ghidra: FUN_0060b340  retail @ 0x0020B340 size 298
_TEXT ENDS
_TEXT$d0060b340 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0060B340 size 298
public ?d_0020b340@@YAXXZ
?d_0020b340@@YAXXZ PROC
    db 083h, 0ECh, 008h, 056h, 08Bh, 0F1h, 08Bh, 04Ch, 024h, 010h, 08Bh, 046h, 0E4h, 057h, 08Bh, 07Eh
    db 0E0h, 051h, 050h, 08Dh, 04Fh, 02Ch, 089h, 074h, 024h, 010h, 089h, 07Ch, 024h, 014h
    call ?j_000357d8@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 0F7h, 000h, 000h, 000h, 08Bh, 046h, 024h, 053h, 08Bh, 018h, 03Bh, 0D8h
    db 055h, 08Bh, 02Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 074h, 066h, 08Dh, 064h, 024h, 000h, 08Bh, 053h, 008h, 052h, 08Bh, 0CDh
    call ?j_0001f253@@YAXXZ
    db 08Bh, 0F8h, 085h, 0FFh, 074h, 046h, 08Bh, 0B7h, 0F0h, 001h, 000h, 000h, 08Bh, 006h, 085h, 0C0h
    db 074h, 027h, 08Dh, 049h, 000h, 08Dh, 048h, 00Ch, 08Bh, 001h, 0FFh, 050h, 064h, 085h, 0C0h, 075h
    db 00Ch, 08Bh, 046h, 004h, 083h, 0C6h, 004h, 085h, 0C0h, 075h, 0EAh, 0EBh, 00Ch, 08Bh, 04Ch, 024h
    db 01Ch, 08Bh, 010h, 051h, 08Bh, 0C8h, 0FFh, 052h, 008h, 06Ah, 000h, 08Bh, 0CFh
    call ?j_0000d990@@YAXXZ
    db 08Bh, 02Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 074h, 024h, 010h, 08Bh, 01Bh, 03Bh, 05Eh, 024h, 075h, 0A2h, 08Bh, 07Ch, 024h, 014h, 08Ah
    db 047h, 018h, 084h, 0C0h, 074h, 077h, 08Bh, 046h, 024h, 08Bh, 030h, 03Bh, 0F0h, 074h, 06Eh, 0B3h
    db 001h, 08Bh, 04Eh, 008h, 085h, 0C9h, 074h, 03Fh, 08Bh, 085h, 0B4h, 000h, 000h, 000h, 08Bh, 0BDh
    db 0B8h, 000h, 000h, 000h, 02Bh, 0F8h, 033h, 0D2h, 0C1h, 0FFh, 002h, 08Bh, 0C1h, 0F7h, 0F7h, 08Bh
    db 085h, 0B4h, 000h, 000h, 000h, 08Bh, 014h, 090h, 085h, 0D2h, 074h, 014h, 090h, 039h, 04Ah, 004h
    db 074h, 00Ah, 08Bh, 012h, 085h, 0D2h, 075h, 0F5h, 033h, 0C9h, 0EBh, 00Bh, 085h, 0D2h, 075h, 004h
    db 033h, 0C9h, 0EBh, 003h, 08Bh, 04Ah, 008h, 085h, 0C9h, 08Bh, 036h, 074h, 017h, 084h, 099h, 044h
    db 003h, 000h, 000h, 075h, 00Fh, 06Ah, 000h, 06Ah, 008h
    call ?j_00014506@@YAXXZ
    db 08Bh, 02Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 04Ch, 024h, 010h, 03Bh, 071h, 024h, 075h, 094h, 05Dh, 05Bh, 05Fh, 05Eh, 083h, 0C4h, 008h
    db 0C2h, 004h, 000h
?d_0020b340@@YAXXZ ENDP
_TEXT$d0060b340 ENDS
_TEXT SEGMENT

; ghidra: FUN_0060b5b0  retail @ 0x0020B5B0 size 197
public ?d_0020b5b0@@YAXXZ
?d_0020b5b0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 41h, 28h, 53h, 55h, 56h, 8Bh, 30h, 3Bh, 0F0h, 57h, 89h, 4Ch
    db 24h, 14h, 0C6h, 44h, 24h, 13h, 00h, 0Fh, 84h, 9Ch, 00h, 00h, 00h, 8Bh, 7Ch, 24h
    db 24h, 8Bh, 6Ch, 24h, 20h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 6Bh, 0A1h, 98h, 08h, 2Fh
    db 01h, 8Bh, 90h, 0B4h, 00h, 00h, 00h, 8Bh, 98h, 0B8h, 00h, 00h, 00h, 2Bh, 0DAh, 33h
    db 0D2h, 0C1h, 0FBh, 02h, 8Bh, 0C1h, 0F7h, 0F3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 80h, 0B4h
    db 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 3Dh, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 2Ah, 85h, 0D2h, 74h
    db 26h, 8Bh, 4Ah, 08h, 85h, 0C9h, 74h, 1Fh, 8Bh, 54h, 24h, 1Ch, 57h, 55h, 52h, 0E8h
    db 5Fh, 96h, 0E2h, 0FFh, 83h, 0F8h, 01h, 74h, 09h, 7Eh, 0Ch, 83h, 0F8h, 03h, 7Eh, 2Bh
    db 0EBh, 05h, 0C6h, 44h, 24h, 13h, 01h, 8Bh, 44h, 24h, 14h, 8Bh, 36h, 3Bh, 70h, 28h
    db 75h, 83h, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 74h, 0Fh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h
    db 00h, 00h, 5Bh, 83h, 0C4h, 08h, 0C2h, 0Ch, 00h, 33h, 0C0h, 5Fh, 5Eh, 5Dh, 5Bh, 83h
    db 0C4h, 08h, 0C2h, 0Ch, 00h
?d_0020b5b0@@YAXXZ ENDP

; ghidra: FUN_0060b6b0  retail @ 0x0020B6B0 size 206
public ?d_0020b6b0@@YAXXZ
?d_0020b6b0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 41h, 28h, 53h, 55h, 56h, 8Bh, 30h, 3Bh, 0F0h, 57h, 89h, 4Ch
    db 24h, 14h, 0C6h, 44h, 24h, 13h, 00h, 0Fh, 84h, 0A5h, 00h, 00h, 00h, 8Bh, 7Ch, 24h
    db 28h, 8Bh, 6Ch, 24h, 24h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 70h, 0A1h, 98h, 08h, 2Fh
    db 01h, 8Bh, 90h, 0B4h, 00h, 00h, 00h, 8Bh, 98h, 0B8h, 00h, 00h, 00h, 2Bh, 0DAh, 33h
    db 0D2h, 0C1h, 0FBh, 02h, 8Bh, 0C1h, 0F7h, 0F3h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 80h, 0B4h
    db 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 42h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 2Fh, 85h, 0D2h, 74h
    db 2Bh, 8Bh, 4Ah, 08h, 85h, 0C9h, 74h, 24h, 8Bh, 54h, 24h, 20h, 8Bh, 44h, 24h, 1Ch
    db 57h, 55h, 52h, 50h, 0E8h, 07h, 0F2h, 0E2h, 0FFh, 83h, 0F8h, 01h, 74h, 09h, 7Eh, 0Ch
    db 83h, 0F8h, 03h, 7Eh, 2Fh, 0EBh, 05h, 0C6h, 44h, 24h, 13h, 01h, 8Bh, 4Ch, 24h, 14h
    db 8Bh, 36h, 3Bh, 71h, 28h, 0Fh, 85h, 7Ah, 0FFh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 84h
    db 0C0h, 74h, 0Fh, 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 08h, 0C2h
    db 10h, 00h, 33h, 0C0h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 10h, 00h
?d_0020b6b0@@YAXXZ ENDP

; ghidra: FUN_0060b860  retail @ 0x0020B860 size 325
public ?d_0020b860@@YAXXZ
?d_0020b860@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 0C2h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 53h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 57h
    db 89h, 74h, 24h, 10h, 0E8h, 9Bh, 4Fh, 0E1h, 0FFh, 8Bh, 7Eh, 04h, 33h, 0F6h, 68h, 1Ch
    db 30h, 07h, 01h, 8Dh, 4Ch, 24h, 10h, 89h, 44h, 24h, 18h, 89h, 7Ch, 24h, 1Ch, 89h
    db 74h, 24h, 20h, 89h, 74h, 24h, 24h, 89h, 74h, 24h, 28h, 0C7h, 44h, 24h, 2Ch, 20h
    db 0BCh, 0BEh, 4Ch, 0E8h, 08h, 0D3h, 67h, 00h, 8Bh, 5Fh, 20h, 8Bh, 47h, 24h, 3Bh, 0D8h
    db 89h, 74h, 24h, 34h, 0Fh, 84h, 0B2h, 00h, 00h, 00h, 55h, 0EBh, 03h, 33h, 0F6h, 90h
    db 8Bh, 03h, 3Bh, 0C6h, 74h, 06h, 0Fh, 0B7h, 68h, 04h, 0EBh, 02h, 33h, 0EDh, 3Bh, 0C6h
    db 8Dh, 78h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 44h, 24h, 10h, 3Bh, 0C6h
    db 74h, 09h, 0Fh, 0B7h, 50h, 04h, 8Dh, 70h, 08h, 0EBh, 07h, 33h, 0D2h, 0BEh, 8Bh, 38h
    db 07h, 01h, 3Bh, 0D5h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CDh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h
    db 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 50h, 2Bh, 0D5h, 8Bh, 0C2h, 85h, 0C0h, 75h
    db 48h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 53h, 0E8h, 33h, 0CCh, 0E1h, 0FFh, 89h, 44h, 24h
    db 20h, 8Bh, 44h, 24h, 14h, 8Bh, 48h, 08h, 8Dh, 54h, 24h, 20h, 52h, 89h, 4Ch, 24h
    db 28h, 8Bh, 4Ch, 24h, 1Ch, 68h, 0A0h, 0ABh, 60h, 00h, 0C7h, 44h, 24h, 30h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 34h, 20h, 0BCh, 0BEh, 4Ch, 0E8h, 6Ch, 38h, 0E2h, 0FFh, 53h
    db 8Dh, 4Ch, 24h, 14h, 0E8h, 27h, 0C3h, 67h, 00h, 8Bh, 44h, 24h, 1Ch, 8Bh, 48h, 24h
    db 83h, 0C3h, 04h, 3Bh, 0D9h, 0Fh, 85h, 52h, 0FFh, 0FFh, 0FFh, 5Dh, 8Bh, 74h, 24h, 24h
    db 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 34h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0AFh, 0BFh, 67h
    db 00h, 8Bh, 4Ch, 24h, 2Ch, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 2Ch, 0C3h
?d_0020b860@@YAXXZ ENDP

; ghidra: FUN_0060bae0  retail @ 0x0020BAE0 size 743
public ?d_0020bae0@@YAXXZ
?d_0020bae0@@YAXXZ PROC
    db 83h, 0ECh, 24h, 55h, 8Bh, 0E9h, 8Ah, 45h, 4Dh, 84h, 0C0h, 0Fh, 84h, 0D8h, 02h, 00h
    db 00h, 8Bh, 4Dh, 04h, 8Bh, 51h, 08h, 33h, 0C0h, 89h, 45h, 54h, 53h, 89h, 44h, 24h
    db 10h, 89h, 44h, 24h, 20h, 89h, 44h, 24h, 24h, 89h, 44h, 24h, 28h, 89h, 44h, 24h
    db 18h, 89h, 44h, 24h, 14h, 88h, 44h, 24h, 0Bh, 88h, 44h, 24h, 0Ah, 8Bh, 45h, 48h
    db 8Bh, 18h, 3Bh, 0D8h, 57h, 8Bh, 7Dh, 08h, 89h, 7Ch, 24h, 10h, 89h, 54h, 24h, 20h
    db 0Fh, 84h, 0E5h, 01h, 00h, 00h, 56h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 43h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 04h, 37h, 0E1h, 0FFh, 8Bh
    db 0F0h, 85h, 0F6h, 0Fh, 84h, 0A6h, 00h, 00h, 00h, 8Bh, 0BEh, 0F0h, 01h, 00h, 00h, 8Bh
    db 07h, 85h, 0C0h, 74h, 2Bh, 8Bh, 50h, 0Ch, 8Dh, 48h, 0Ch, 0FFh, 52h, 64h, 85h, 0C0h
    db 75h, 0Ch, 8Bh, 47h, 04h, 83h, 0C7h, 04h, 85h, 0C0h, 75h, 0E9h, 0EBh, 12h, 8Bh, 10h
    db 8Bh, 0C8h, 0FFh, 52h, 10h, 8Bh, 4Dh, 54h, 0Fh, 0B6h, 0C0h, 03h, 0C8h, 89h, 4Dh, 54h
    db 0D9h, 44h, 24h, 28h, 8Bh, 0BEh, 00h, 02h, 00h, 00h, 0D8h, 46h, 38h, 8Bh, 17h, 8Bh
    db 0CFh, 0D9h, 5Ch, 24h, 28h, 0D9h, 44h, 24h, 2Ch, 0D8h, 46h, 3Ch, 0D9h, 5Ch, 24h, 2Ch
    db 0D9h, 44h, 24h, 30h, 0D8h, 46h, 40h, 0D9h, 5Ch, 24h, 30h, 0FFh, 52h, 10h, 0D8h, 44h
    db 24h, 20h, 8Bh, 07h, 8Bh, 0CFh, 0D9h, 5Ch, 24h, 20h, 0FFh, 50h, 18h, 0D8h, 44h, 24h
    db 1Ch, 8Bh, 16h, 8Bh, 0CEh, 0D9h, 5Ch, 24h, 1Ch, 0FFh, 52h, 28h, 8Ah, 88h, 0ACh, 03h
    db 00h, 00h, 84h, 0C9h, 74h, 07h, 0C6h, 44h, 24h, 13h, 01h, 0EBh, 05h, 0C6h, 44h, 24h
    db 12h, 01h, 8Bh, 44h, 24h, 18h, 8Bh, 7Ch, 24h, 14h, 40h, 89h, 44h, 24h, 18h, 8Bh
    db 1Bh, 3Bh, 5Dh, 48h, 0Fh, 85h, 36h, 0FFh, 0FFh, 0FFh, 8Ah, 44h, 24h, 13h, 84h, 0C0h
    db 0Fh, 84h, 04h, 01h, 00h, 00h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 28h, 8Ah, 88h, 0ACh
    db 03h, 00h, 00h, 84h, 0C9h, 74h, 0Ch, 8Ah, 44h, 24h, 12h, 84h, 0C0h, 0Fh, 84h, 0E7h
    db 00h, 00h, 00h, 8Bh, 0Dh, 0ECh, 0D5h, 2Eh, 01h, 8Bh, 11h, 68h, 0E9h, 03h, 00h, 00h
    db 0FFh, 52h, 34h, 8Bh, 0F8h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 5Dh, 76h, 0DFh, 0FFh, 8Ah, 44h
    db 24h, 12h, 84h, 0C0h, 74h, 6Ah, 8Bh, 45h, 48h, 8Bh, 18h, 3Bh, 0D8h, 74h, 61h, 90h
    db 8Bh, 43h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 0E4h, 35h, 0E1h, 0FFh, 8Bh
    db 0F0h, 85h, 0F6h, 74h, 44h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Ah, 88h, 0ACh, 03h
    db 00h, 00h, 84h, 0C9h, 75h, 33h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 11h, 50h, 0FFh
    db 92h, 0E0h, 00h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 6Ah, 00h, 0FFh
    db 90h, 74h, 01h, 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0FDh, 75h, 0DFh, 0FFh, 8Bh, 4Eh
    db 74h, 51h, 8Bh, 0CFh, 0E8h, 33h, 00h, 0E2h, 0FFh, 8Bh, 1Bh, 3Bh, 5Dh, 48h, 75h, 0A0h
    db 8Bh, 4Ch, 24h, 14h, 8Bh, 11h, 0FFh, 52h, 28h, 8Ah, 88h, 0ACh, 03h, 00h, 00h, 84h
    db 0C9h, 75h, 43h, 8Bh, 74h, 24h, 14h, 0A1h, 8Ch, 14h, 2Fh, 01h, 8Bh, 16h, 8Bh, 18h
    db 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 50h, 0FFh, 93h, 0E0h, 00h
    db 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh, 01h, 6Ah, 00h, 0FFh, 90h, 74h, 01h
    db 00h, 00h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0A0h, 75h, 0DFh, 0FFh, 8Bh, 4Eh, 74h, 51h, 8Bh
    db 0CFh, 0E8h, 0D6h, 0FFh, 0E1h, 0FFh, 8Bh, 7Ch, 24h, 14h, 5Eh, 0DBh, 44h, 24h, 14h, 8Dh
    db 97h, 4Ch, 02h, 00h, 00h, 6Ah, 00h, 0D8h, 3Dh, 34h, 53h, 07h, 01h, 0D9h, 0C0h, 0D9h
    db 44h, 24h, 28h, 0D8h, 0C9h, 0D9h, 44h, 24h, 2Ch, 0D8h, 0CAh, 0D9h, 5Ch, 24h, 2Ch, 0D9h
    db 44h, 24h, 30h, 0D8h, 0CAh, 0D9h, 5Ch, 24h, 30h, 0D8h, 67h, 38h, 0D9h, 5Ch, 24h, 28h
    db 8Bh, 44h, 24h, 28h, 0DDh, 0D8h, 0D9h, 44h, 24h, 2Ch, 0D8h, 67h, 3Ch, 0D9h, 5Ch, 24h
    db 2Ch, 8Bh, 4Ch, 24h, 2Ch, 0D9h, 44h, 24h, 30h, 0D8h, 67h, 40h, 89h, 02h, 89h, 4Ah
    db 04h, 8Bh, 8Fh, 00h, 02h, 00h, 00h, 0D9h, 5Ch, 24h, 30h, 8Bh, 44h, 24h, 30h, 89h
    db 42h, 08h, 8Bh, 44h, 24h, 18h, 85h, 0C0h, 74h, 2Bh, 0D8h, 4Ch, 24h, 1Ch, 8Bh, 11h
    db 0DAh, 4Ch, 24h, 24h, 51h, 0D8h, 7Ch, 24h, 24h, 0D8h, 0Dh, 0C4h, 0FAh, 07h, 01h, 0D9h
    db 1Ch, 24h, 0FFh, 52h, 54h, 6Ah, 01h, 8Bh, 0CFh, 0E8h, 0BCh, 66h, 0E3h, 0FFh, 5Fh, 5Bh
    db 5Dh, 83h, 0C4h, 24h, 0C3h, 8Bh, 01h, 0DDh, 0D8h, 6Ah, 00h, 0FFh, 50h, 54h, 6Ah, 01h
    db 8Bh, 0CFh, 0E8h, 0A3h, 66h, 0E3h, 0FFh
?d_0020bae0@@YAXXZ ENDP

; ghidra: FUN_0060bed0  retail @ 0x0020BED0 size 268
public ?d_0020bed0@@YAXXZ
?d_0020bed0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 74h, 24h, 18h, 0B0h, 01h, 57h, 8Dh, 4Ch, 24h, 0Ch
    db 88h, 44h, 24h, 0Ch, 88h, 44h, 24h, 0Dh, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h
    db 8Bh, 5Ch, 24h, 20h, 8Bh, 0Bh, 8Bh, 01h, 33h, 0D2h, 3Bh, 0C1h, 74h, 09h, 8Bh, 0FFh
    db 8Bh, 00h, 42h, 3Bh, 0C1h, 75h, 0F9h, 8Dh, 44h, 24h, 20h, 89h, 54h, 24h, 1Ch, 8Bh
    db 16h, 50h, 8Bh, 0CEh, 0C7h, 44h, 24h, 24h, 44h, 3Eh, 08h, 01h, 0FFh, 52h, 2Ch, 8Bh
    db 10h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0C8h, 0FFh, 52h, 74h, 8Bh, 16h, 8Bh, 0CEh, 0FFh
    db 52h, 08h, 84h, 0C0h, 74h, 26h, 8Bh, 1Bh, 8Bh, 3Bh, 3Bh, 0FBh, 0Fh, 84h, 91h, 00h
    db 00h, 00h, 8Bh, 06h, 8Dh, 4Fh, 08h, 51h, 8Bh, 0CEh, 0FFh, 50h, 78h, 8Bh, 3Fh, 3Bh
    db 0FBh, 75h, 0EFh, 8Bh, 0C6h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 03h, 39h, 00h
    db 74h, 23h, 68h, 24h, 3Eh, 08h, 01h, 8Dh, 54h, 24h, 14h, 6Ah, 04h, 52h, 0E8h, 0ADh
    db 0A2h, 7Ch, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 44h, 24h, 14h, 50h
    db 0E8h, 7Bh, 0ADh, 7Eh, 00h, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 74h, 46h, 8Dh, 49h, 00h
    db 8Bh, 44h, 24h, 1Ch, 8Bh, 16h, 48h, 89h, 44h, 24h, 1Ch, 8Dh, 44h, 24h, 20h, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 3Bh, 6Ah, 0Ch, 0E8h, 92h, 25h, 62h, 00h, 8Dh, 48h
    db 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 06h, 8Bh, 54h, 24h, 20h, 89h, 11h, 8Bh, 4Fh
    db 04h, 89h, 38h, 89h, 48h, 04h, 89h, 01h, 89h, 47h, 04h, 8Bh, 44h, 24h, 1Ch, 85h
    db 0C0h, 75h, 0BDh, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_0020bed0@@YAXXZ ENDP

; ghidra: FUN_0060c050  retail @ 0x0020C050 size 186
public ?d_0020c050@@YAXXZ
?d_0020c050@@YAXXZ PROC
    db 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 28h, 8Bh, 30h, 3Bh, 0F0h, 0Fh, 84h, 0A0h
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 39h, 4Eh, 08h, 74h, 06h, 8Bh, 36h, 3Bh, 0F0h
    db 75h, 0F5h, 3Bh, 0F0h, 0Fh, 84h, 89h, 00h, 00h, 00h, 8Bh, 47h, 0E4h, 8Bh, 0Dh, 98h
    db 08h, 2Fh, 01h, 8Bh, 59h, 3Ch, 8Bh, 68h, 0Ch, 03h, 0EBh, 8Bh, 5Fh, 24h, 6Ah, 0Ch
    db 0E8h, 0ABh, 24h, 62h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 02h, 89h
    db 29h, 8Bh, 4Bh, 04h, 89h, 18h, 89h, 48h, 04h, 89h, 01h, 89h, 43h, 04h, 8Bh, 06h
    db 8Bh, 4Eh, 04h, 6Ah, 0Ch, 89h, 01h, 56h, 89h, 48h, 04h, 0E8h, 30h, 25h, 62h, 00h
    db 8Bh, 47h, 30h, 83h, 0C4h, 08h, 48h, 89h, 47h, 30h, 75h, 37h, 8Ah, 47h, 2Dh, 84h
    db 0C0h, 74h, 30h, 8Bh, 54h, 24h, 18h, 8Bh, 42h, 08h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h
    db 50h, 0E8h, 6Dh, 31h, 0E1h, 0FFh, 85h, 0C0h, 74h, 0Dh, 8Bh, 4Fh, 0E8h, 6Ah, 01h, 51h
    db 8Bh, 0C8h, 0E8h, 54h, 0F8h, 0E0h, 0FFh, 8Bh, 4Fh, 0E8h, 6Ah, 00h, 6Ah, 08h, 0E8h, 03h
    db 84h, 0E0h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 08h, 00h
?d_0020c050@@YAXXZ ENDP

; ghidra: FUN_0060c190  retail @ 0x0020C190 size 425
public ?d_0020c190@@YAXXZ
?d_0020c190@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C8h, 0C2h, 00h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 74h, 24h, 24h, 57h, 56h
    db 8Bh, 0F9h, 0E8h, 0FCh, 9Eh, 0E0h, 0FFh, 8Bh, 06h, 8Dh, 4Ch, 24h, 0Ch, 51h, 0B3h, 03h
    db 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 01h, 88h, 5Ch, 24h, 11h, 0FFh, 50h, 28h, 38h, 5Ch
    db 24h, 0Dh, 72h, 08h, 56h, 8Bh, 0CFh, 0E8h, 0E5h, 82h, 0DFh, 0FFh, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 52h, 10h, 84h, 0C0h, 0Fh, 85h, 3Ah, 01h, 00h, 00h, 8Bh, 06h, 8Dh, 4Fh, 4Eh
    db 51h, 8Bh, 0CEh, 0FFh, 90h, 8Ch, 00h, 00h, 00h, 80h, 7Ch, 24h, 0Dh, 02h, 72h, 14h
    db 56h, 8Dh, 4Fh, 2Ch, 0E8h, 0A3h, 0DBh, 0E1h, 0FFh, 8Bh, 16h, 8Dh, 47h, 58h, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 74h, 33h, 0DBh, 89h, 5Ch, 24h, 28h, 8Bh, 47h, 34h, 3Bh, 0C3h, 89h
    db 5Ch, 24h, 20h, 74h, 05h, 83h, 0C0h, 20h, 0EBh, 05h, 0B8h, 50h, 6Eh, 33h, 01h, 50h
    db 8Dh, 4Ch, 24h, 2Ch, 0E8h, 57h, 0BAh, 67h, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 28h, 50h
    db 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h, 47h
    db 8Bh, 44h, 24h, 28h, 3Bh, 0C3h, 89h, 5Fh, 34h, 74h, 3Ch, 66h, 39h, 58h, 04h, 74h
    db 36h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 8Dh, 44h, 24h, 28h, 50h, 0E8h, 0EFh, 0C2h, 0E1h
    db 0FFh, 3Bh, 0C3h, 89h, 47h, 34h, 75h, 1Fh, 53h, 8Dh, 4Ch, 24h, 14h, 6Ah, 05h, 51h
    db 0E8h, 9Bh, 9Fh, 7Ch, 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 54h, 24h
    db 14h, 52h, 0E8h, 69h, 0AAh, 7Eh, 00h, 8Bh, 06h, 8Dh, 4Fh, 38h, 51h, 8Bh, 0CEh, 0FFh
    db 50h, 78h, 8Bh, 16h, 8Dh, 47h, 3Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 8Dh
    db 47h, 40h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h
    db 0C0h, 74h, 08h, 8Dh, 4Fh, 44h, 0E8h, 13h, 56h, 0DFh, 0FFh, 8Dh, 47h, 44h, 50h, 56h
    db 0E8h, 0DFh, 1Eh, 0E1h, 0FFh, 8Dh, 4Fh, 48h, 51h, 56h, 0E8h, 03h, 3Dh, 0E0h, 0FFh, 8Bh
    db 16h, 83h, 0C4h, 10h, 8Dh, 47h, 4Ch, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h
    db 8Bh, 16h, 8Dh, 47h, 4Dh, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h
    db 8Dh, 47h, 50h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 16h, 83h, 0C7h, 54h, 57h, 8Bh
    db 0CEh, 0FFh, 52h, 74h, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 1Bh, 0B6h, 67h, 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_0020c190@@YAXXZ ENDP

; ghidra: FUN_0060cb60  retail @ 0x0020CB60 size 131
public ?d_0020cb60@@YAXXZ
?d_0020cb60@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 43h, 28h, 57h, 8Bh, 38h, 3Bh, 0F8h, 74h, 71h, 55h, 56h, 8Bh
    db 35h, 98h, 08h, 2Fh, 01h, 8Bh, 4Fh, 08h, 85h, 0C9h, 74h, 59h, 8Bh, 86h, 0B4h, 00h
    db 00h, 00h, 8Bh, 0AEh, 0B8h, 00h, 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h, 8Bh
    db 0C1h, 0F7h, 0F5h, 8Bh, 86h, 0B4h, 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 35h
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 28h, 85h, 0D2h, 74h
    db 24h, 8Bh, 52h, 08h, 85h, 0D2h, 74h, 1Dh, 8Bh, 82h, 04h, 02h, 00h, 00h, 85h, 0C0h
    db 74h, 13h, 8Bh, 4Ch, 24h, 14h, 51h, 8Dh, 48h, 20h, 0E8h, 0A1h, 81h, 0E1h, 0FFh, 8Bh
    db 35h, 98h, 08h, 2Fh, 01h, 8Bh, 3Fh, 3Bh, 7Bh, 28h, 75h, 99h, 5Eh, 5Dh, 5Fh, 5Bh
    db 0C2h, 04h, 00h
?d_0020cb60@@YAXXZ ENDP

; ghidra: FUN_0060cc30  retail @ 0x0020CC30 size 25
public ?d_0020cc30@@YAXXZ
?d_0020cc30@@YAXXZ PROC
    db 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 0Ah, 0B0h, 0E3h, 0FFh
?d_0020cc30@@YAXXZ ENDP

; ghidra: FUN_0060ce30  retail @ 0x0020CE30 size 456
_TEXT ENDS
_TEXT$d0060ce30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0060CE30 size 456
public ?d_0020ce30@@YAXXZ
?d_0020ce30@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0100C30B
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 028h, 055h, 08Bh, 069h, 0F4h, 056h, 08Bh, 071h, 0F8h, 057h, 089h, 04Ch, 024h, 018h, 08Bh, 08Eh
    db 064h, 003h, 000h, 000h, 033h, 0FFh, 03Bh, 0CFh, 089h, 06Ch, 024h, 014h, 089h, 04Ch, 024h, 010h
    db 089h, 07Ch, 024h, 00Ch, 075h, 039h, 06Ah, 008h, 089h, 07Ch, 024h, 010h
    call ??2@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C7h, 089h, 07Ch, 024h, 03Ch, 074h, 009h, 08Bh
    db 0C8h
    call ?j_00048135@@YAXXZ
    db 0EBh, 002h, 033h, 0C0h, 0C7h, 044h, 024h, 03Ch, 0FFh, 0FFh, 0FFh, 0FFh, 089h, 044h, 024h, 010h
    db 089h, 086h, 064h, 003h, 000h, 000h, 0EBh, 075h, 053h, 06Ah, 001h
    call ?j_0002a982@@YAXXZ
    db 08Bh, 0D8h, 03Bh, 0DFh, 075h, 006h, 089h, 07Ch, 024h, 010h, 0EBh, 060h, 08Bh, 03Bh, 03Bh, 07Bh
    db 004h, 074h, 059h, 08Dh, 06Fh, 004h, 08Bh, 007h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 050h
    call ?j_0001f253@@YAXXZ
    db 085h, 0C0h, 075h, 008h, 083h, 0C7h, 004h, 083h, 0C5h, 004h, 0EBh, 033h, 0F6h, 080h, 044h, 003h
    db 000h, 000h, 001h, 074h, 01Bh, 08Bh, 043h, 004h, 03Bh, 0E8h, 074h, 00Eh, 02Bh, 0C5h, 050h, 055h
    db 057h, 0FFh, 015h
    dd ?bfmeMemCopy@@3P6APAXPAXPBXI@ZA
    db 083h, 0C4h, 00Ch, 083h, 043h, 004h, 0FCh, 0EBh, 00Fh, 08Bh, 044h, 024h, 010h, 083h, 0C7h, 004h
    db 083h, 0C5h, 004h, 040h, 089h, 044h, 024h, 010h, 03Bh, 07Bh, 004h, 075h, 0AEh, 08Bh, 06Ch, 024h
    db 018h, 05Bh, 08Bh, 04Dh, 00Ch, 02Bh, 04Ch, 024h, 00Ch, 085h, 0C9h, 00Fh, 08Eh, 09Ah, 000h, 000h
    db 000h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 08Dh, 055h, 008h, 052h
    call ?j_00028560@@YAXXZ
    db 085h, 0C0h, 00Fh, 084h, 083h, 000h, 000h, 000h, 033h, 0C9h, 089h, 04Ch, 024h, 01Ch, 089h, 04Ch
    db 024h, 020h, 06Ah, 000h, 089h, 04Ch, 024h, 028h, 08Bh, 08Eh, 03Ch, 002h, 000h, 000h, 08Dh, 054h
    db 024h, 020h, 052h, 051h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 050h
    call ?j_0004494a@@YAXXZ
    db 0D9h, 045h, 014h, 0D8h, 046h, 03Ch, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 06Ah, 000h, 083h, 0ECh, 008h, 0D9h, 05Ch, 024h, 004h, 08Bh, 0F8h, 0D9h, 046h, 038h, 08Bh, 001h
    db 0D8h, 045h, 010h, 0D9h, 01Ch, 024h, 0FFh, 050h, 018h, 0D8h, 046h, 040h, 08Dh, 04Ch, 024h, 028h
    db 0D9h, 046h, 038h, 051h, 0D8h, 045h, 010h, 08Bh, 0CFh, 0D9h, 05Ch, 024h, 02Ch, 0D9h, 045h, 014h
    db 0D8h, 046h, 03Ch, 0D9h, 05Ch, 024h, 030h, 0D9h, 05Ch, 024h, 034h
    call ?j_0003a1a7@@YAXXZ
    db 08Bh, 057h, 074h, 08Bh, 04Ch, 024h, 010h, 052h, 06Ah, 001h
    call ?j_0002a54a@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 08Bh, 040h, 0F4h, 085h, 0C0h, 05Fh, 05Eh, 05Dh, 074h, 012h, 08Bh, 040h
    db 018h, 08Bh, 04Ch, 024h, 028h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 034h, 0C3h
    db 08Bh, 04Ch, 024h, 028h, 0B8h, 01Eh, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 034h, 0C3h
?d_0020ce30@@YAXXZ ENDP
_TEXT$d0060ce30 ENDS
_TEXT SEGMENT

; ghidra: FUN_0060d090  retail @ 0x0020D090 size 32
public ?d_0020d090@@YAXXZ
?d_0020d090@@YAXXZ PROC
    db 0C7h, 41h, 20h, 0C0h, 6Eh, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 0A3h, 0ABh, 0E3h, 0FFh
?d_0020d090@@YAXXZ ENDP

; ghidra: FUN_0060d260  retail @ 0x0020D260 size 17
public ?d_0020d260@@YAXXZ
?d_0020d260@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 68h, 0E8h, 6Fh, 0Ah, 01h, 0E8h, 0B0h, 36h, 64h, 00h
    db 0C3h
?d_0020d260@@YAXXZ ENDP

; ghidra: FUN_0060d310  retail @ 0x0020D310 size 361
public ?d_0020d310@@YAXXZ
?d_0020d310@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 0E9h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 8Bh
    db 5Dh, 0F8h, 8Bh, 45h, 0F4h, 57h, 8Bh, 0CBh, 89h, 44h, 24h, 14h, 0E8h, 0F3h, 34h, 0E1h
    db 0FFh, 8Bh, 0F8h, 85h, 0FFh, 0B8h, 05h, 00h, 00h, 00h, 0Fh, 84h, 32h, 01h, 00h, 00h
    db 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 39h, 41h, 3Ch, 0Fh, 82h, 23h, 01h, 00h, 00h, 8Ah
    db 8Fh, 81h, 06h, 00h, 00h, 84h, 0C9h, 0Fh, 84h, 15h, 01h, 00h, 00h, 0F6h, 83h, 18h
    db 01h, 00h, 00h, 14h, 0Fh, 85h, 08h, 01h, 00h, 00h, 56h, 8Bh, 0CBh, 0E8h, 0E0h, 67h
    db 0DFh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 95h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh
    db 0FFh, 52h, 38h, 85h, 0C0h, 0Fh, 86h, 86h, 00h, 00h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh
    db 50h, 38h, 83h, 0F8h, 01h, 0Fh, 86h, 0D1h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0CEh, 0FFh
    db 52h, 48h, 8Bh, 78h, 08h, 85h, 0FFh, 89h, 44h, 24h, 18h, 74h, 29h, 8Bh, 45h, 10h
    db 8Dh, 4Dh, 10h, 8Dh, 54h, 24h, 14h, 52h, 0FFh, 10h, 50h, 83h, 0C7h, 20h, 57h, 0BBh
    db 01h, 00h, 00h, 00h, 0E8h, 0F0h, 85h, 0E1h, 0FFh, 83h, 0C4h, 08h, 84h, 0C0h, 74h, 0Ah
    db 88h, 5Ch, 24h, 13h, 0EBh, 09h, 8Ah, 5Ch, 24h, 14h, 0C6h, 44h, 24h, 13h, 00h, 0F6h
    db 0C3h, 01h, 74h, 09h, 8Dh, 4Ch, 24h, 14h, 0E8h, 53h, 0A5h, 67h, 00h, 8Ah, 44h, 24h
    db 13h, 84h, 0C0h, 74h, 77h, 8Bh, 4Ch, 24h, 18h, 8Bh, 51h, 10h, 8Bh, 06h, 52h, 8Bh
    db 0CEh, 0FFh, 50h, 20h, 5Eh, 5Fh, 5Dh, 0B8h, 05h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch
    db 0C3h, 83h, 0C7h, 30h, 74h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h
    db 8Dh, 46h, 08h, 50h, 0E8h, 37h, 0B1h, 0E1h, 0FFh, 85h, 0C0h, 74h, 3Fh, 6Ah, 00h, 50h
    db 8Bh, 0CFh, 0E8h, 0FFh, 4Eh, 0E1h, 0FFh, 84h, 0C0h, 74h, 31h, 8Dh, 4Eh, 0Ch, 51h, 8Bh
    db 0Dh, 0F8h, 33h, 2Fh, 01h, 0E8h, 53h, 0E1h, 0E2h, 0FFh, 8Ah, 4Eh, 1Ch, 84h, 0C9h, 74h
    db 07h, 8Ah, 4Dh, 14h, 84h, 0C9h, 74h, 14h, 85h, 0C0h, 74h, 0Ch, 6Ah, 00h, 6Ah, 02h
    db 50h, 8Bh, 0CBh, 0E8h, 67h, 8Fh, 0DFh, 0FFh, 0C6h, 45h, 14h, 00h, 0B8h, 05h, 00h, 00h
    db 00h, 5Eh, 5Fh, 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_0020d310@@YAXXZ ENDP

; ghidra: FUN_0060d4e0  retail @ 0x0020D4E0 size 32
public ?d_0020d4e0@@YAXXZ
?d_0020d4e0@@YAXXZ PROC
    db 0C7h, 41h, 20h, 34h, 70h, 0Ah, 01h, 0C7h, 41h, 10h, 0ACh, 0CBh, 09h, 01h, 0C7h, 01h
    db 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 53h, 0A7h, 0E3h, 0FFh
?d_0020d4e0@@YAXXZ ENDP

; ghidra: FUN_0060d770  retail @ 0x0020D770 size 47
public ?d_0020d770@@YAXXZ
?d_0020d770@@YAXXZ PROC
    db 0A1h, 98h, 08h, 2Fh, 01h, 53h, 8Bh, 58h, 3Ch, 56h, 8Bh, 0F1h, 8Bh, 56h, 0E0h, 57h
    db 8Dh, 7Eh, 0E0h, 8Bh, 0CFh, 0FFh, 52h, 2Ch, 8Bh, 46h, 04h, 8Bh, 4Eh, 0E8h, 2Bh, 0C3h
    db 50h, 51h, 8Bh, 0CFh, 0E8h, 41h, 80h, 0E0h, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_0020d770@@YAXXZ ENDP

; ghidra: FUN_0060d870  retail @ 0x0020D870 size 18
public ?d_0020d870@@YAXXZ
?d_0020d870@@YAXXZ PROC
    db 8Bh, 49h, 08h, 0E8h, 20h, 1Ch, 0E0h, 0FFh, 8Bh, 10h, 6Ah, 00h, 8Bh, 0C8h, 0FFh, 52h
    db 44h, 0C3h
?d_0020d870@@YAXXZ ENDP

; ghidra: FUN_0060d890  retail @ 0x0020D890 size 74
public ?d_0020d890@@YAXXZ
?d_0020d890@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 8Bh, 0F9h, 0E8h, 23h, 6Ch, 0DFh, 0FFh, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 10h, 84h, 0C0h, 75h, 2Ch, 8Bh, 16h, 0B0h, 01h, 88h, 44h, 24h
    db 0Ch, 88h, 44h, 24h, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 28h, 8Bh
    db 16h, 8Dh, 47h, 24h, 50h, 8Bh, 0CEh, 0FFh, 52h, 74h, 8Bh, 16h, 83h, 0C7h, 28h, 57h
    db 8Bh, 0CEh, 0FFh, 52h, 74h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_0020d890@@YAXXZ ENDP

; ghidra: FUN_0060d930  retail @ 0x0020D930 size 18
public ?d_0020d930@@YAXXZ
?d_0020d930@@YAXXZ PROC
    db 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch, 98h, 0CAh, 09h, 01h, 0E9h, 11h, 0A3h
    db 0E3h, 0FFh
?d_0020d930@@YAXXZ ENDP

; ghidra: FUN_0060d9d0  retail @ 0x0020D9D0 size 104
public ?d_0020d9d0@@YAXXZ
?d_0020d9d0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 8Ah, 0Dh, 24h, 0F9h, 2Eh, 01h, 6Ah, 0FFh, 68h, 8Eh
    db 0C3h, 00h, 01h, 50h, 0B8h, 01h, 00h, 00h, 00h, 84h, 0C8h, 64h, 89h, 25h, 00h, 00h
    db 00h, 00h, 75h, 31h, 09h, 05h, 24h, 0F9h, 2Eh, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h
    db 68h, 58h, 0Bh, 09h, 01h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0C5h, 0D3h
    db 0E2h, 0FFh, 0A3h, 20h, 0F9h, 2Eh, 01h, 8Bh, 0Ch, 24h, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Ch, 24h, 0A1h, 20h, 0F9h, 2Eh, 01h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C3h
?d_0020d9d0@@YAXXZ ENDP

; ghidra: FUN_0060dad0  retail @ 0x0020DAD0 size 43
public ?d_0020dad0@@YAXXZ
?d_0020dad0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 8Bh, 49h, 08h, 81h, 0C1h, 90h, 00h, 00h, 00h, 8Bh, 01h, 89h, 04h
    db 24h, 8Bh, 41h, 04h, 8Bh, 49h, 08h, 24h, 40h, 0F6h, 0D8h, 89h, 4Ch, 24h, 08h, 1Bh
    db 0C0h, 83h, 0E0h, 0Ah, 83h, 0C0h, 14h, 83h, 0C4h, 0Ch, 0C3h
?d_0020dad0@@YAXXZ ENDP

; ghidra: FUN_0060db20  retail @ 0x0020DB20 size 25
public ?d_0020db20@@YAXXZ
?d_0020db20@@YAXXZ PROC
    db 0C7h, 41h, 10h, 18h, 74h, 0Ah, 01h, 0C7h, 01h, 5Ch, 0CBh, 09h, 01h, 0C7h, 41h, 0Ch
    db 98h, 0CAh, 09h, 01h, 0E9h, 1Ah, 0A1h, 0E3h, 0FFh
?d_0020db20@@YAXXZ ENDP

; ghidra: FUN_0060dc80  retail @ 0x0020DC80 size 5
public ?d_0020dc80@@YAXXZ
?d_0020dc80@@YAXXZ PROC
    db 0B0h, 01h, 0C2h, 04h, 00h
?d_0020dc80@@YAXXZ ENDP

; ghidra: FUN_0060deb0  retail @ 0x0020DEB0 size 34
public ?d_0020deb0@@YAXXZ
?d_0020deb0@@YAXXZ PROC
    db 56h, 8Bh, 71h, 08h, 8Bh, 8Eh, 10h, 02h, 00h, 00h, 85h, 0C9h, 74h, 05h, 0E8h, 0B0h
    db 4Dh, 0E1h, 0FFh, 8Bh, 0CEh, 0E8h, 08h, 0Ch, 0E2h, 0FFh, 8Bh, 0CEh, 5Eh, 0E9h, 06h, 3Ch
    db 0E3h, 0FFh
?d_0020deb0@@YAXXZ ENDP

; ghidra: FUN_0060df90  retail @ 0x0020DF90 size 38
public ?d_0020df90@@YAXXZ
?d_0020df90@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 0F0h, 8Dh, 4Eh, 0F0h, 0FFh, 50h, 38h, 8Bh, 46h, 0F8h, 8Bh
    db 4Ch, 24h, 08h, 6Ah, 01h, 50h, 51h, 8Dh, 8Eh, 0C8h, 00h, 00h, 00h, 0E8h, 0C5h, 1Ah
    db 0E2h, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_0020df90@@YAXXZ ENDP

; ghidra: FUN_0060dfc0  retail @ 0x0020DFC0 size 18
public ?d_0020dfc0@@YAXXZ
?d_0020dfc0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 06h, 0FFh, 50h, 20h, 8Bh, 16h, 50h, 8Bh, 0CEh, 0FFh, 52h, 24h
    db 5Eh, 0C3h
?d_0020dfc0@@YAXXZ ENDP

; ghidra: FUN_0060e100  retail @ 0x0020E100 size 27
public ?d_0020e100@@YAXXZ
?d_0020e100@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 8Bh, 4Eh, 20h, 50h, 51h, 8Bh, 4Eh, 0F8h, 0E8h, 22h
    db 50h, 0E3h, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 5Eh, 0FFh, 62h, 28h
?d_0020e100@@YAXXZ ENDP

; ghidra: FUN_0060e150  retail @ 0x0020E150 size 30
public ?d_0020e150@@YAXXZ
?d_0020e150@@YAXXZ PROC
    db 0D9h, 41h, 10h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h
    db 0D9h, 41h, 08h, 0D8h, 71h, 10h, 0C3h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0C3h
?d_0020e150@@YAXXZ ENDP

; ghidra: FUN_0060e850  retail @ 0x0020E850 size 7
public ?d_0020e850@@YAXXZ
?d_0020e850@@YAXXZ PROC
    db 8Bh, 41h, 0F4h, 8Bh, 40h, 38h, 0C3h
?d_0020e850@@YAXXZ ENDP

; ghidra: FUN_0060e8d0  retail @ 0x0020E8D0 size 79
public ?d_0020e8d0@@YAXXZ
?d_0020e8d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 56h, 74h, 26h, 8Dh, 04h, 40h, 0C1h, 0E0h, 02h, 3Dh
    db 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 44h, 36h, 67h, 00h, 83h, 0C4h, 04h, 8Bh
    db 0F0h, 0EBh, 0Eh, 0E8h, 48h, 0FCh, 61h, 00h, 83h, 0C4h, 04h, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 0Ch, 8Dh, 44h, 24h, 08h, 50h, 56h, 51h
    db 52h, 0E8h, 12h, 5Ch, 0E1h, 0FFh, 83h, 0C4h, 10h, 8Bh, 0C6h, 5Eh, 0C2h, 0Ch, 00h
?d_0020e8d0@@YAXXZ ENDP

; ghidra: FUN_0060e9a0  retail @ 0x0020E9A0 size 83
public ?d_0020e9a0@@YAXXZ
?d_0020e9a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 83h, 0C0h, 04h, 8Bh, 00h, 85h, 0C0h, 75h, 04h, 33h
    db 0C9h, 0EBh, 0Eh, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0FCh, 38h, 0DFh, 0FFh, 8Bh
    db 0C8h, 8Dh, 86h, 0D0h, 00h, 00h, 00h, 50h, 0E8h, 0BCh, 0D0h, 0E2h, 0FFh, 85h, 0C0h, 74h
    db 20h, 3Bh, 86h, 0D4h, 00h, 00h, 00h, 74h, 18h, 8Bh, 48h, 04h, 89h, 8Eh, 0D8h, 00h
    db 00h, 00h, 8Bh, 48h, 08h, 89h, 8Eh, 0DCh, 00h, 00h, 00h, 89h, 86h, 0D4h, 00h, 00h
    db 00h, 5Eh, 0C3h
?d_0020e9a0@@YAXXZ ENDP
_TEXT ENDS
END
