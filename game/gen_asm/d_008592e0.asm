.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0Rva00899F00Base@@QAE@IH@Z:NEAR
EXTERN ?ConnectToServer@Rva00884Ftp@@QAEJPBD@Z:NEAR
EXTERN ?GetNextFileBlock@Cftp@@QAEJPBDPAH@Z:NEAR
EXTERN ?LoginToServer@Cftp@@QAEJPBD0@Z:NEAR
EXTERN ?Rva00897640@@YAPAXI@Z:NEAR
EXTERN ?Rva008C5D70Alloc@@3P6APAXI@ZA:BYTE
EXTERN ?Rva012D5298Empty@@3URva00893410Block@@A:BYTE
EXTERN ?aptApplyChannels008B4480@@YAPAVAptValue@@PAUOwner008B4480@@H@Z:NEAR
EXTERN ?aptGetChannels008B4700@@YAPAVRva00899F00Base@@PAUOwner008B4700@@H@Z:NEAR
EXTERN ?aptPackedChannels008B4420@@YAPAVAptValue@@PAURva008B4420Owner@@H@Z:NEAR
EXTERN ?aptSetPackedChannels008B4370@@YAPAVAptValue@@PAURva008B4370Owner@@H@Z:NEAR
EXTERN ?bfmeFirst1285@BfmeIteratorList1285@@QAEPAUBfmeIterator1285@@XZ:NEAR
EXTERN ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z:NEAR
EXTERN ?bfmeNext1285@BfmeIteratorList1285@@QAEPAUBfmeIterator1285@@PAU2@@Z:NEAR
EXTERN ?bfmePush@@YAXPAVBfmeItemDX@@@Z:NEAR
EXTERN ?d_00886020@@YAXXZ:NEAR
EXTERN ?d_00886a20@Rva00886A20Class@@QAEHPBDH@Z:NEAR
EXTERN ?g_bfme1211@@3PAVBfmeG1211@@A:BYTE
EXTERN ?g_bfmeS1082_4@@3PAVBfmeS1082@@A:BYTE
EXTERN ?g_bfmeS1082_5@@3PAVBfmeS1082@@A:BYTE
EXTERN ?g_bfmeS1082_6@@3PAVBfmeS1082@@A:BYTE
EXTERN ?g_bfmeS1082_7@@3PAVBfmeS1082@@A:BYTE
EXTERN ?ji_009f6fa0@@YAXXZ:NEAR
EXTERN __imp_?i_009f6ec0@@YAXXZ:BYTE
EXTERN __imp__EnterCriticalSection@4:BYTE
EXTERN __imp__GetProcessHeap@0:BYTE
EXTERN __imp__HeapAlloc@12:BYTE
EXTERN __imp__HeapFree@12:BYTE
EXTERN __imp__LeaveCriticalSection@4:BYTE
EXTERN __imp___stat:BYTE
EXTERN __imp___strnicmp:BYTE
EXTERN __imp__timeGetTime@0:BYTE
EXTERN _bfmeVft1029A:BYTE
EXTERN g_Va01058D3C:NEAR
EXTERN g_Va010FE3C8:BYTE
EXTERN g_Va01336CEC:BYTE
EXTERN g_Va01338594:BYTE
EXTERN g_Va013385A4:BYTE
EXTERN g_Va013386A0:BYTE
EXTERN g_Va013386AC:BYTE
EXTERN g_Va01358E9C:BYTE
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x008592E0 size 189
public ?d_008592e0@@YAXXZ
?d_008592e0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 56h, 0E8h, 24h, 5Eh, 00h, 00h, 8Bh, 0F8h, 8Bh, 46h
    db 48h, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 9Eh, 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h
    db 14h, 85h, 0DBh, 55h, 74h, 05h, 80h, 3Bh, 00h, 75h, 03h, 8Dh, 5Eh, 04h, 8Bh, 6Ch
    db 24h, 28h, 8Bh, 44h, 24h, 24h, 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 1Ch, 57h, 55h
    db 50h, 51h, 52h, 53h, 56h, 0E8h, 06h, 6Bh, 00h, 00h, 83h, 0C4h, 1Ch, 85h, 0C0h, 75h
    db 19h, 8Bh, 44h, 24h, 24h, 57h, 55h, 50h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 53h, 6Ah
    db 00h, 56h, 0E8h, 0E9h, 59h, 00h, 00h, 83h, 0C4h, 24h, 8Bh, 44h, 24h, 2Ch, 85h, 0C0h
    db 5Dh, 5Bh, 74h, 46h, 6Ah, 01h, 0E8h, 15h, 0B0h, 0FFh, 0FFh, 57h, 0E8h, 0Fh, 0E0h, 0FFh
    db 0FFh, 57h, 56h, 0E8h, 0D8h, 5Ch, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 74h, 0E5h, 57h
    db 56h, 0E8h, 8Ah, 4Eh, 00h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0D7h, 8Bh, 86h, 08h
    db 1Fh, 00h, 00h, 85h, 0C0h, 74h, 13h, 8Bh, 86h, 24h, 18h, 00h, 00h, 85h, 0C0h, 75h
    db 09h, 56h, 0E8h, 0B9h, 0F0h, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Fh, 5Eh, 0C3h
?d_008592e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008596A0 size 240
public ?d_008596a0@@YAXXZ
?d_008596a0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 56h, 0E8h, 63h, 5Ah, 00h, 00h, 8Bh, 5Ch, 24h
    db 28h, 8Bh, 0F8h, 8Bh, 46h, 48h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 6Dh, 8Bh, 46h, 44h
    db 85h, 0C0h, 75h, 66h, 8Ah, 46h, 60h, 84h, 0C0h, 74h, 5Fh, 55h, 8Bh, 6Ch, 24h, 18h
    db 6Ah, 40h, 8Dh, 46h, 04h, 55h, 50h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0FFh, 15h, 0C0h
    db 94h, 35h, 01h, 8Bh, 4Ch, 24h, 2Ch, 57h, 8Bh, 54h, 24h, 2Ch, 53h, 33h, 0C0h, 89h
    db 4Eh, 4Ch, 8Bh, 4Ch, 24h, 38h, 51h, 50h, 50h, 50h, 50h, 50h, 50h, 50h, 55h, 50h
    db 56h, 0C6h, 46h, 43h, 00h, 89h, 46h, 48h, 0C7h, 46h, 44h, 01h, 00h, 00h, 00h, 89h
    db 56h, 5Ch, 89h, 86h, 04h, 1Fh, 00h, 00h, 0E8h, 0D3h, 5Bh, 00h, 00h, 83h, 0C4h, 40h
    db 85h, 0C0h, 5Dh, 75h, 19h, 0E8h, 0B6h, 0DBh, 0FFh, 0FFh, 8Bh, 54h, 24h, 20h, 57h, 53h
    db 52h, 6Ah, 00h, 6Ah, 00h, 56h, 0E8h, 0B5h, 4Bh, 00h, 00h, 83h, 0C4h, 18h, 8Bh, 44h
    db 24h, 28h, 85h, 0C0h, 74h, 46h, 6Ah, 01h, 0E8h, 23h, 0ACh, 0FFh, 0FFh, 57h, 0E8h, 1Dh
    db 0DCh, 0FFh, 0FFh, 57h, 56h, 0E8h, 0E6h, 58h, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 74h
    db 0E5h, 57h, 56h, 0E8h, 98h, 4Ah, 00h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0D7h, 8Bh
    db 86h, 08h, 1Fh, 00h, 00h, 85h, 0C0h, 74h, 13h, 8Bh, 86h, 24h, 18h, 00h, 00h, 85h
    db 0C0h, 75h, 09h, 56h, 0E8h, 0C7h, 0ECh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 0C3h
?d_008596a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00859970 size 83
public ?d_00859970@@YAXXZ
?d_00859970@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 86h, 24h, 18h, 00h, 00h, 85h, 0C0h, 7Eh, 0Ch, 0C7h
    db 86h, 04h, 1Fh, 00h, 00h, 01h, 00h, 00h, 00h, 0EBh, 19h, 0C7h, 86h, 0B0h, 0Ah, 00h
    db 00h, 00h, 00h, 00h, 00h, 0E8h, 46h, 0D9h, 0FFh, 0FFh, 6Ah, 0FFh, 0E8h, 0CFh, 0D9h, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 8Bh, 86h, 08h, 1Fh, 00h, 00h, 85h, 0C0h, 74h, 13h, 8Bh, 86h
    db 24h, 18h, 00h, 00h, 85h, 0C0h, 75h, 09h, 56h, 0E8h, 92h, 0EAh, 0FFh, 0FFh, 83h, 0C4h
    db 04h, 5Eh, 0C3h
?d_00859970@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00859C80 size 98
public ?d_00859c80@@YAXXZ
?d_00859c80@@YAXXZ PROC
    db 81h, 0ECh, 88h, 00h, 00h, 00h, 8Bh, 84h, 24h, 90h, 00h, 00h, 00h, 8Bh, 8Ch, 24h
    db 94h, 00h, 00h, 00h, 50h, 51h, 8Dh, 54h, 24h, 10h, 68h, 00h, 06h, 08h, 01h, 52h
    db 0FFh, 15h, 8Ch, 94h, 35h, 01h, 8Bh, 94h, 24h, 9Ch, 00h, 00h, 00h, 8Dh, 44h, 24h
    db 18h, 8Dh, 4Ch, 24h, 10h, 89h, 44h, 24h, 10h, 8Bh, 42h, 18h, 51h, 50h, 0E8h, 6Dh
    db 0D2h, 00h, 00h, 83h, 0C4h, 18h, 85h, 0C0h, 75h, 0Eh, 8Bh, 84h, 24h, 98h, 00h, 00h
    db 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h, 8Bh, 40h, 04h, 81h, 0C4h, 88h, 00h, 00h
    db 00h, 0C3h
?d_00859c80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00859CF0 size 112
public ?d_00859cf0@@YAXXZ
?d_00859cf0@@YAXXZ PROC
    db 81h, 0ECh, 88h, 00h, 00h, 00h, 8Bh, 84h, 24h, 90h, 00h, 00h, 00h, 8Bh, 8Ch, 24h
    db 94h, 00h, 00h, 00h, 50h, 51h, 8Dh, 54h, 24h, 10h, 68h, 00h, 06h, 08h, 01h, 52h
    db 0FFh, 15h, 8Ch, 94h, 35h, 01h, 8Bh, 94h, 24h, 9Ch, 00h, 00h, 00h, 8Dh, 44h, 24h
    db 18h, 8Dh, 4Ch, 24h, 10h, 89h, 44h, 24h, 10h, 8Bh, 42h, 18h, 51h, 50h, 0E8h, 0FDh
    db 0D1h, 00h, 00h, 83h, 0C4h, 18h, 85h, 0C0h, 74h, 07h, 8Bh, 40h, 04h, 85h, 0C0h, 75h
    db 0Eh, 0DDh, 84h, 24h, 98h, 00h, 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h, 50h
    db 0FFh, 15h, 80h, 93h, 35h, 01h, 83h, 0C4h, 04h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h
?d_00859cf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00859DD0 size 112
public ?d_00859dd0@@YAXXZ
?d_00859dd0@@YAXXZ PROC
    db 81h, 0ECh, 88h, 00h, 00h, 00h, 8Bh, 84h, 24h, 90h, 00h, 00h, 00h, 8Bh, 8Ch, 24h
    db 94h, 00h, 00h, 00h, 50h, 51h, 8Dh, 54h, 24h, 10h, 68h, 80h, 0Bh, 13h, 01h, 52h
    db 0FFh, 15h, 8Ch, 94h, 35h, 01h, 8Bh, 94h, 24h, 9Ch, 00h, 00h, 00h, 8Dh, 44h, 24h
    db 18h, 8Dh, 4Ch, 24h, 10h, 89h, 44h, 24h, 10h, 8Bh, 42h, 18h, 51h, 50h, 0E8h, 1Dh
    db 0D1h, 00h, 00h, 83h, 0C4h, 18h, 85h, 0C0h, 74h, 07h, 8Bh, 40h, 04h, 85h, 0C0h, 75h
    db 0Eh, 0DDh, 84h, 24h, 98h, 00h, 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h, 50h
    db 0FFh, 15h, 80h, 93h, 35h, 01h, 83h, 0C4h, 04h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C3h
?d_00859dd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085B940 size 32
public ?d_0085b940@@YAXXZ
?d_0085b940@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Dh, 46h, 48h, 50h, 0E8h, 12h, 0C2h, 00h, 00h, 56h, 0E8h
    db 0ACh, 0DFh, 00h, 00h, 56h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h, 0Ch, 5Eh, 0C3h
?d_0085b940@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085BA40 size 25
public ?d_0085ba40@@YAXXZ
?d_0085ba40@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 56h, 0E8h, 0C5h, 0E2h, 00h, 00h, 83h, 0C6h, 48h, 56h, 0E8h
    db 0FCh, 0D5h, 00h, 00h, 83h, 0C4h, 08h, 5Eh, 0C3h
?d_0085ba40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085BA60 size 25
public ?d_0085ba60@@YAXXZ
?d_0085ba60@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Dh, 46h, 48h, 50h, 0E8h, 92h, 0C0h, 00h, 00h, 56h, 0E8h
    db 6Ch, 0DEh, 00h, 00h, 83h, 0C4h, 08h, 5Eh, 0C3h
?d_0085ba60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085BA80 size 33
public ?d_0085ba80@@YAXXZ
?d_0085ba80@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Dh, 77h, 48h, 56h, 0E8h, 71h, 0C0h, 00h, 00h, 57h
    db 0E8h, 4Bh, 0DEh, 00h, 00h, 56h, 0E8h, 0F5h, 0BAh, 00h, 00h, 83h, 0C4h, 0Ch, 5Fh, 5Eh
    db 0C3h
?d_0085ba80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C600 size 18
public ?d_0085c600@@YAXXZ
?d_0085c600@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 08h, 8Bh, 54h, 24h, 04h, 89h, 0Ah, 0B8h, 01h, 00h, 00h
    db 00h, 0C3h
?d_0085c600@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C630 size 30
public ?d_0085c630@@YAXXZ
?d_0085c630@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 0Ch, 8Bh, 50h, 10h, 51h, 8Bh, 0Ah, 8Bh, 50h, 04h
    db 51h, 8Bh, 4Ch, 24h, 0Ch, 52h, 51h, 0FFh, 50h, 08h, 83h, 0C4h, 10h, 0C3h
?d_0085c630@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C680 size 34
public ?d_0085c680@@YAXXZ
?d_0085c680@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 50h, 0Ch, 8Bh, 48h, 10h, 52h, 8Bh, 51h, 04h, 8Bh, 09h
    db 52h, 8Bh, 50h, 04h, 51h, 8Bh, 4Ch, 24h, 10h, 52h, 51h, 0FFh, 50h, 08h, 83h, 0C4h
    db 14h, 0C3h
?d_0085c680@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C6B0 size 92
public ?d_0085c6b0@@YAXXZ
?d_0085c6b0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 8Bh, 7Ch, 24h, 0Ch, 89h, 07h, 8Bh, 4Eh
    db 04h, 89h, 4Fh, 04h, 8Bh, 56h, 0Ch, 89h, 57h, 0Ch, 8Bh, 46h, 10h, 89h, 47h, 10h
    db 8Bh, 4Eh, 14h, 89h, 4Fh, 14h, 8Bh, 56h, 18h, 89h, 57h, 18h, 8Bh, 46h, 08h, 85h
    db 0C0h, 74h, 1Ah, 50h, 0E8h, 0C7h, 7Ch, 0FFh, 0FFh, 89h, 47h, 08h, 8Bh, 4Eh, 08h, 83h
    db 0C4h, 04h, 85h, 0C9h, 74h, 0Eh, 85h, 0C0h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 47h, 08h
    db 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085c6b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C710 size 17
public ?d_0085c710@@YAXXZ
?d_0085c710@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085c710@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C730 size 54
public ?d_0085c730@@YAXXZ
?d_0085c730@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 18h, 52h, 8Bh
    db 50h, 14h, 52h, 8Bh, 50h, 10h, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh, 50h, 08h, 52h, 8Bh
    db 50h, 04h, 8Bh, 00h, 52h, 8Bh, 51h, 04h, 50h, 8Bh, 44h, 24h, 24h, 52h, 50h, 0FFh
    db 51h, 08h, 83h, 0C4h, 28h, 0C3h
?d_0085c730@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C770 size 79
public ?d_0085c770@@YAXXZ
?d_0085c770@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 85h, 0C0h, 74h, 1Bh, 50h, 0E8h, 2Fh, 7Ch, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 0Ch, 89h, 01h, 8Bh, 16h, 83h, 0C4h, 04h, 85h, 0D2h, 74h, 10h
    db 85h, 0C0h, 75h, 0Ch, 5Eh, 0C3h, 8Bh, 4Ch, 24h, 08h, 0C7h, 01h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 08h, 89h, 41h, 08h, 8Bh, 56h, 04h, 89h, 51h, 04h, 8Bh, 46h, 0Ch, 89h
    db 41h, 0Ch, 8Bh, 56h, 10h, 89h, 51h, 10h, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085c770@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C860 size 304
public ?d_0085c860@@YAXXZ
?d_0085c860@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 6Ch, 24h, 14h, 56h, 8Bh, 74h, 24h, 14h, 33h, 0C0h, 8Bh, 0CEh
    db 89h, 01h, 89h, 41h, 04h, 89h, 41h, 08h, 89h, 41h, 0Ch, 8Bh, 5Dh, 08h, 89h, 5Eh
    db 08h, 8Bh, 55h, 00h, 89h, 16h, 8Bh, 45h, 04h, 85h, 0C0h, 57h, 0BFh, 01h, 00h, 00h
    db 00h, 89h, 7Ch, 24h, 10h, 89h, 5Ch, 24h, 18h, 74h, 19h, 50h, 0E8h, 0Fh, 7Bh, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 04h, 75h, 10h, 89h, 44h, 24h, 10h, 0E9h
    db 96h, 00h, 00h, 00h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 85h, 0DBh, 0Fh, 84h, 0C5h
    db 00h, 00h, 00h, 8Bh, 45h, 0Ch, 85h, 0C0h, 0Fh, 84h, 0BAh, 00h, 00h, 00h, 0C1h, 0E3h
    db 02h, 53h, 0FFh, 15h, 4Ch, 94h, 35h, 01h, 8Bh, 0F8h, 83h, 0C4h, 04h, 85h, 0FFh, 89h
    db 7Eh, 0Ch, 75h, 06h, 89h, 44h, 24h, 10h, 0EBh, 12h, 8Bh, 0CBh, 8Bh, 0D1h, 0C1h, 0E9h
    db 02h, 33h, 0C0h, 0F3h, 0ABh, 8Bh, 0CAh, 83h, 0E1h, 03h, 0F3h, 0AAh, 8Bh, 44h, 24h, 10h
    db 33h, 0FFh, 85h, 0C0h, 74h, 40h, 3Bh, 7Ch, 24h, 18h, 7Dh, 32h, 8Bh, 45h, 0Ch, 8Bh
    db 0Ch, 0B8h, 51h, 0E8h, 98h, 7Ah, 0FFh, 0FFh, 8Bh, 56h, 0Ch, 89h, 04h, 0BAh, 8Bh, 46h
    db 0Ch, 8Bh, 0Ch, 0B8h, 83h, 0C4h, 04h, 85h, 0C9h, 75h, 08h, 0C7h, 44h, 24h, 10h, 00h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 47h, 85h, 0C0h, 75h, 0CAh, 0EBh, 08h, 8Bh, 44h
    db 24h, 10h, 85h, 0C0h, 75h, 38h, 8Bh, 5Ch, 24h, 18h, 8Bh, 4Eh, 04h, 8Bh, 2Dh, 0D4h
    db 93h, 35h, 01h, 51h, 0FFh, 0D5h, 83h, 0C4h, 04h, 33h, 0FFh, 85h, 0DBh, 7Eh, 16h, 90h
    db 8Bh, 46h, 0Ch, 85h, 0C0h, 74h, 09h, 8Bh, 14h, 0B8h, 52h, 0FFh, 0D5h, 83h, 0C4h, 04h
    db 47h, 3Bh, 0FBh, 7Ch, 0EBh, 8Bh, 46h, 0Ch, 50h, 0FFh, 0D5h, 83h, 0C4h, 04h, 8Bh, 44h
    db 24h, 10h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h
?d_0085c860@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085C9E0 size 38
public ?d_0085c9e0@@YAXXZ
?d_0085c9e0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 54h, 24h, 14h, 50h, 52h, 0FFh
    db 51h, 08h, 83h, 0C4h, 18h, 0C3h
?d_0085c9e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CA10 size 74
public ?d_0085ca10@@YAXXZ
?d_0085ca10@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 8Bh, 7Ch, 24h, 0Ch, 89h, 07h, 8Bh, 4Eh
    db 04h, 89h, 4Fh, 04h, 8Bh, 56h, 0Ch, 89h, 57h, 0Ch, 8Bh, 46h, 08h, 85h, 0C0h, 74h
    db 1Ah, 50h, 0E8h, 79h, 79h, 0FFh, 0FFh, 89h, 47h, 08h, 8Bh, 4Eh, 08h, 83h, 0C4h, 04h
    db 85h, 0C9h, 74h, 0Eh, 85h, 0C0h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 47h, 08h, 00h, 00h
    db 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085ca10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CA60 size 17
public ?d_0085ca60@@YAXXZ
?d_0085ca60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085ca60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CA80 size 42
public ?d_0085ca80@@YAXXZ
?d_0085ca80@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 51h, 04h, 50h, 8Bh, 44h, 24h
    db 18h, 52h, 50h, 0FFh, 51h, 08h, 83h, 0C4h, 1Ch, 0C3h
?d_0085ca80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CAB0 size 61
public ?d_0085cab0@@YAXXZ
?d_0085cab0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 85h, 0C0h, 74h, 15h, 50h, 0E8h, 0EFh, 78h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 0Ch, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 01h, 75h, 0Ch, 5Eh, 0C3h
    db 8Bh, 4Ch, 24h, 08h, 0C7h, 01h, 00h, 00h, 00h, 00h, 8Bh, 46h, 04h, 89h, 41h, 04h
    db 8Bh, 56h, 08h, 89h, 51h, 08h, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085cab0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CB30 size 55
public ?d_0085cb30@@YAXXZ
?d_0085cb30@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 85h, 0C0h, 74h, 15h, 50h, 0E8h, 6Fh, 78h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 0Ch, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 01h, 75h, 0Ch, 5Eh, 0C3h
    db 8Bh, 4Ch, 24h, 08h, 0C7h, 01h, 00h, 00h, 00h, 00h, 8Bh, 46h, 04h, 89h, 41h, 04h
    db 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085cb30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CB70 size 16
public ?d_0085cb70@@YAXXZ
?d_0085cb70@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h, 01h
?d_0085cb70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CBB0 size 51
public ?d_0085cbb0@@YAXXZ
?d_0085cbb0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 04h, 56h, 8Bh, 74h, 24h, 08h, 89h, 4Eh, 04h, 8Bh
    db 00h, 85h, 0C0h, 74h, 11h, 50h, 0E8h, 0E5h, 77h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 06h, 75h, 08h, 5Eh, 0C3h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0B8h, 01h, 00h, 00h
    db 00h, 5Eh, 0C3h
?d_0085cbb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CBF0 size 16
public ?d_0085cbf0@@YAXXZ
?d_0085cbf0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h, 01h
?d_0085cbf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CC30 size 109
public ?d_0085cc30@@YAXXZ
?d_0085cc30@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 4Fh
    db 0Ch, 89h, 4Eh, 0Ch, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 5Fh, 77h, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h
    db 04h, 00h, 00h, 00h, 00h, 8Bh, 7Fh, 08h, 85h, 0FFh, 74h, 22h, 57h, 0E8h, 3Eh, 77h
    db 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 56h, 04h, 52h
    db 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h
    db 08h, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085cc30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CCF0 size 165
public ?d_0085ccf0@@YAXXZ
?d_0085ccf0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 47h, 10h, 89h, 46h, 10h
    db 8Bh, 0Fh, 89h, 0Eh, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 9Fh, 76h, 0FFh
    db 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h
    db 04h, 00h, 00h, 00h, 00h, 8Bh, 47h, 08h, 85h, 0C0h, 74h, 22h, 50h, 0E8h, 7Eh, 76h
    db 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 56h, 04h, 52h
    db 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h
    db 08h, 00h, 00h, 00h, 00h, 8Bh, 7Fh, 0Ch, 85h, 0FFh, 74h, 2Ah, 57h, 0E8h, 4Eh, 76h
    db 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 0Ch, 75h, 21h, 8Bh, 46h, 04h, 8Bh
    db 3Dh, 0D4h, 93h, 35h, 01h, 50h, 0FFh, 0D7h, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D7h, 83h, 0C4h
    db 08h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h
    db 00h, 00h, 00h, 5Eh, 0C3h
?d_0085ccf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CDA0 size 36
public ?d_0085cda0@@YAXXZ
?d_0085cda0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D7h, 8Bh, 56h, 0Ch, 52h, 0FFh, 0D7h, 83h, 0C4h
    db 0Ch, 5Fh, 5Eh, 0C3h
?d_0085cda0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CDD0 size 42
public ?d_0085cdd0@@YAXXZ
?d_0085cdd0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 10h, 52h, 8Bh
    db 50h, 0Ch, 52h, 8Bh, 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 54h, 24h
    db 18h, 50h, 52h, 0FFh, 51h, 08h, 83h, 0C4h, 1Ch, 0C3h
?d_0085cdd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CE00 size 18
public ?d_0085ce00@@YAXXZ
?d_0085ce00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 08h, 8Bh, 54h, 24h, 04h, 89h, 0Ah, 0B8h, 01h, 00h, 00h
    db 00h, 0C3h
?d_0085ce00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CE30 size 26
public ?d_0085ce30@@YAXXZ
?d_0085ce30@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 0Ch, 8Bh, 50h, 10h, 51h, 8Bh, 0Ah, 8Bh, 54h, 24h
    db 08h, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 0Ch, 0C3h
?d_0085ce30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CE50 size 35
public ?d_0085ce50@@YAXXZ
?d_0085ce50@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 10h, 8Bh, 4Ch, 24h, 04h, 56h, 57h, 89h, 11h, 8Dh, 79h
    db 04h, 8Dh, 70h, 04h, 0B9h, 08h, 00h, 00h, 00h, 0F3h, 0A5h, 5Fh, 0B8h, 01h, 00h, 00h
    db 00h, 5Eh, 0C3h
?d_0085ce50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CE90 size 30
public ?d_0085ce90@@YAXXZ
?d_0085ce90@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 50h, 0Ch, 8Bh, 48h, 10h, 52h, 8Dh, 51h, 04h, 8Bh, 09h
    db 52h, 8Bh, 54h, 24h, 0Ch, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 10h, 0C3h
?d_0085ce90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CF20 size 29
public ?d_0085cf20@@YAXXZ
?d_0085cf20@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h, 0FFh
    db 0D7h, 8Bh, 4Eh, 04h, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085cf20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085CF70 size 156
public ?d_0085cf70@@YAXXZ
?d_0085cf70@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 47h, 0Ch, 89h, 46h, 0Ch
    db 8Bh, 07h, 85h, 0C0h, 74h, 12h, 50h, 0E8h, 24h, 74h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 06h, 75h, 09h, 5Fh, 5Eh, 0C3h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 21h, 50h, 0E8h, 05h, 74h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 18h, 8Bh, 0Eh, 51h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h
    db 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh, 47h, 08h
    db 85h, 0C0h, 74h, 29h, 50h, 0E8h, 0D6h, 73h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h
    db 46h, 08h, 75h, 20h, 8Bh, 16h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 52h, 0FFh, 0D7h, 8Bh
    db 46h, 04h, 50h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 08h
    db 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085cf70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D010 size 35
public ?d_0085d010@@YAXXZ
?d_0085d010@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h, 0FFh
    db 0D7h, 8Bh, 4Eh, 04h, 51h, 0FFh, 0D7h, 8Bh, 56h, 08h, 52h, 0FFh, 0D7h, 83h, 0C4h, 0Ch
    db 5Fh, 5Eh, 0C3h
?d_0085d010@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D040 size 38
public ?d_0085d040@@YAXXZ
?d_0085d040@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 54h, 24h, 14h, 50h, 52h, 0FFh
    db 51h, 08h, 83h, 0C4h, 18h, 0C3h
?d_0085d040@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D070 size 55
public ?d_0085d070@@YAXXZ
?d_0085d070@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 85h, 0C0h, 74h, 15h, 50h, 0E8h, 2Fh, 73h, 0FFh
    db 0FFh, 8Bh, 4Ch, 24h, 0Ch, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 01h, 75h, 0Ch, 5Eh, 0C3h
    db 8Bh, 4Ch, 24h, 08h, 0C7h, 01h, 00h, 00h, 00h, 00h, 8Bh, 46h, 04h, 89h, 41h, 04h
    db 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085d070@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D0B0 size 16
public ?d_0085d0b0@@YAXXZ
?d_0085d0b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h, 01h
?d_0085d0b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D120 size 17
public ?d_0085d120@@YAXXZ
?d_0085d120@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085d120@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D140 size 30
public ?d_0085d140@@YAXXZ
?d_0085d140@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 50h, 0Ch, 8Bh, 48h, 10h, 52h, 8Bh, 51h, 04h, 8Bh, 09h
    db 52h, 8Bh, 54h, 24h, 0Ch, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 10h, 0C3h
?d_0085d140@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D1A0 size 17
public ?d_0085d1a0@@YAXXZ
?d_0085d1a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085d1a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D1C0 size 30
public ?d_0085d1c0@@YAXXZ
?d_0085d1c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 50h, 0Ch, 8Bh, 48h, 10h, 52h, 8Bh, 51h, 04h, 8Bh, 09h
    db 52h, 8Bh, 54h, 24h, 0Ch, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 10h, 0C3h
?d_0085d1c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D250 size 30
public ?d_0085d250@@YAXXZ
?d_0085d250@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085d250@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D2A0 size 103
public ?d_0085d2a0@@YAXXZ
?d_0085d2a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 0F5h, 70h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 22h, 50h, 0E8h, 0D4h, 70h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 4Eh, 04h, 51h, 0FFh, 15h, 0D4h, 93h, 35h, 01h
    db 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Fh
    db 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085d2a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D310 size 30
public ?d_0085d310@@YAXXZ
?d_0085d310@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085d310@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D360 size 18
public ?d_0085d360@@YAXXZ
?d_0085d360@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 08h, 8Bh, 54h, 24h, 04h, 89h, 0Ah, 0B8h, 01h, 00h, 00h
    db 00h, 0C3h
?d_0085d360@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D390 size 26
public ?d_0085d390@@YAXXZ
?d_0085d390@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 0Ch, 8Bh, 50h, 10h, 51h, 8Bh, 0Ah, 8Bh, 54h, 24h
    db 08h, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 0Ch, 0C3h
?d_0085d390@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D3B0 size 103
public ?d_0085d3b0@@YAXXZ
?d_0085d3b0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 0E5h, 6Fh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 22h, 50h, 0E8h, 0C4h, 6Fh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 4Eh, 04h, 51h, 0FFh, 15h, 0D4h, 93h, 35h, 01h
    db 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Fh
    db 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085d3b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D420 size 30
public ?d_0085d420@@YAXXZ
?d_0085d420@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085d420@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D470 size 67
public ?d_0085d470@@YAXXZ
?d_0085d470@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 25h, 6Fh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 4Fh, 08h, 89h, 4Eh, 08h, 8Bh, 57h, 0Ch, 5Fh, 89h, 56h, 0Ch, 0B8h, 01h, 00h, 00h
    db 00h, 5Eh, 0C3h
?d_0085d470@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D4C0 size 17
public ?d_0085d4c0@@YAXXZ
?d_0085d4c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085d4c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D4E0 size 53
public ?d_0085d4e0@@YAXXZ
?d_0085d4e0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 10h, 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh
    db 0BCh, 96h, 90h, 03h, 00h, 00h, 85h, 0FFh, 74h, 18h, 8Bh, 79h, 0Ch, 57h, 8Bh, 78h
    db 0Ch, 57h, 8Bh, 78h, 08h, 8Bh, 40h, 04h, 57h, 50h, 52h, 56h, 0FFh, 51h, 08h, 83h
    db 0C4h, 18h, 5Fh, 5Eh, 0C3h
?d_0085d4e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D520 size 46
public ?d_0085d520@@YAXXZ
?d_0085d520@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 00h, 85h, 0C0h, 74h, 14h, 50h, 0E8h, 80h, 6Eh, 0FFh, 0FFh
    db 8Bh, 4Ch, 24h, 08h, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 01h, 75h, 0Bh, 0C3h, 8Bh, 54h
    db 24h, 04h, 0C7h, 02h, 00h, 00h, 00h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_0085d520@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D580 size 51
public ?d_0085d580@@YAXXZ
?d_0085d580@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 04h, 56h, 8Bh, 74h, 24h, 08h, 89h, 4Eh, 04h, 8Bh
    db 00h, 85h, 0C0h, 74h, 11h, 50h, 0E8h, 15h, 6Eh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 06h, 75h, 08h, 5Eh, 0C3h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0B8h, 01h, 00h, 00h
    db 00h, 5Eh, 0C3h
?d_0085d580@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D5C0 size 16
public ?d_0085d5c0@@YAXXZ
?d_0085d5c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 08h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h, 01h
?d_0085d5c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D660 size 29
public ?d_0085d660@@YAXXZ
?d_0085d660@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h, 0FFh
    db 0D7h, 8Bh, 4Eh, 04h, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085d660@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D6B0 size 100
public ?d_0085d6b0@@YAXXZ
?d_0085d6b0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 47h, 04h, 85h, 0C0h, 74h, 17h, 50h, 0E8h, 0EDh
    db 6Ch, 0FFh, 0FFh, 8Bh, 74h, 24h, 10h, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 46h, 04h, 75h
    db 0Eh, 5Fh, 5Eh, 0C3h, 8Bh, 74h, 24h, 0Ch, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 07h, 85h, 0C0h, 74h, 21h, 50h, 0E8h, 0C5h, 6Ch, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 06h, 75h, 18h, 8Bh, 46h, 04h, 50h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h
    db 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 06h, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h
    db 00h, 00h, 5Eh, 0C3h
?d_0085d6b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D720 size 29
public ?d_0085d720@@YAXXZ
?d_0085d720@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 0Eh, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0085d720@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D770 size 159
public ?d_0085d770@@YAXXZ
?d_0085d770@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 25h, 6Ch, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 22h, 50h, 0E8h, 04h, 6Ch, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 4Eh, 04h, 51h, 0FFh, 15h, 0D4h, 93h, 35h, 01h
    db 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 0Ch, 85h, 0C0h, 74h, 2Ah, 50h, 0E8h, 0D4h, 6Bh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 0Ch, 75h, 21h, 8Bh, 56h, 04h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 52h
    db 0FFh, 0D7h, 8Bh, 46h, 08h, 50h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
    db 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085d770@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D840 size 35
public ?d_0085d840@@YAXXZ
?d_0085d840@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 8Bh, 40h, 04h, 52h, 8Bh, 54h, 24h, 10h, 50h, 52h, 0FFh, 51h, 08h, 83h
    db 0C4h, 14h, 0C3h
?d_0085d840@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D870 size 159
public ?d_0085d870@@YAXXZ
?d_0085d870@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 89h, 06h, 8Bh, 47h
    db 04h, 85h, 0C0h, 74h, 13h, 50h, 0E8h, 25h, 6Bh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h
    db 89h, 46h, 04h, 75h, 0Ah, 5Fh, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 08h, 85h, 0C0h, 74h, 22h, 50h, 0E8h, 04h, 6Bh, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 08h, 75h, 19h, 8Bh, 4Eh, 04h, 51h, 0FFh, 15h, 0D4h, 93h, 35h, 01h
    db 83h, 0C4h, 04h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 8Bh
    db 47h, 0Ch, 85h, 0C0h, 74h, 2Ah, 50h, 0E8h, 0D4h, 6Ah, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 46h, 0Ch, 75h, 21h, 8Bh, 56h, 04h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 52h
    db 0FFh, 0D7h, 8Bh, 46h, 08h, 50h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 33h, 0C0h, 5Eh, 0C3h
    db 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0085d870@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D940 size 38
public ?d_0085d940@@YAXXZ
?d_0085d940@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 54h, 24h, 14h, 50h, 52h, 0FFh
    db 51h, 08h, 83h, 0C4h, 18h, 0C3h
?d_0085d940@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085D970 size 395
public ?d_0085d970@@YAXXZ
?d_0085d970@@YAXXZ PROC
    db 51h, 53h, 8Bh, 5Ch, 24h, 0Ch, 33h, 0C0h, 8Bh, 0CBh, 89h, 01h, 89h, 41h, 04h, 89h
    db 41h, 08h, 55h, 8Bh, 6Ch, 24h, 14h, 89h, 41h, 0Ch, 56h, 8Bh, 75h, 04h, 89h, 73h
    db 04h, 8Bh, 45h, 00h, 85h, 0C0h, 57h, 0BFh, 01h, 00h, 00h, 00h, 89h, 7Ch, 24h, 10h
    db 89h, 74h, 24h, 18h, 74h, 18h, 50h, 0E8h, 04h, 6Ah, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 89h, 03h, 75h, 0Fh, 89h, 44h, 24h, 10h, 0E9h, 0DFh, 00h, 00h, 00h, 0C7h, 03h
    db 00h, 00h, 00h, 00h, 85h, 0F6h, 0Fh, 84h, 27h, 01h, 00h, 00h, 0C1h, 0E6h, 02h, 56h
    db 0FFh, 15h, 4Ch, 94h, 35h, 01h, 8Bh, 0F8h, 83h, 0C4h, 04h, 85h, 0FFh, 89h, 7Bh, 08h
    db 75h, 09h, 89h, 44h, 24h, 10h, 0E9h, 0B2h, 00h, 00h, 00h, 8Bh, 0CEh, 8Bh, 0D1h, 0C1h
    db 0E9h, 02h, 33h, 0C0h, 0F3h, 0ABh, 8Bh, 0CAh, 83h, 0E1h, 03h, 0F3h, 0AAh, 8Bh, 45h, 0Ch
    db 33h, 0FFh, 3Bh, 0C7h, 0Fh, 84h, 0DFh, 00h, 00h, 00h, 56h, 0FFh, 15h, 4Ch, 94h, 35h
    db 01h, 8Bh, 0F8h, 83h, 0C4h, 04h, 85h, 0FFh, 89h, 7Bh, 0Ch, 75h, 06h, 89h, 44h, 24h
    db 10h, 0EBh, 7Ah, 8Bh, 0CEh, 8Bh, 0D1h, 0C1h, 0E9h, 02h, 33h, 0C0h, 0F3h, 0ABh, 8Bh, 0CAh
    db 83h, 0E1h, 03h, 0F3h, 0AAh, 8Bh, 45h, 0Ch, 33h, 0FFh, 3Bh, 0C7h, 0Fh, 84h, 0A7h, 00h
    db 00h, 00h, 33h, 0F6h, 3Bh, 74h, 24h, 18h, 7Dh, 4Dh, 8Bh, 45h, 08h, 8Bh, 0Ch, 0B0h
    db 51h, 0E8h, 5Ah, 69h, 0FFh, 0FFh, 8Bh, 53h, 08h, 89h, 04h, 0B2h, 8Bh, 43h, 08h, 8Bh
    db 0Ch, 0B0h, 83h, 0C4h, 04h, 3Bh, 0CFh, 74h, 1Fh, 8Bh, 4Dh, 0Ch, 8Bh, 14h, 0B1h, 52h
    db 0E8h, 3Bh, 69h, 0FFh, 0FFh, 8Bh, 4Bh, 0Ch, 89h, 04h, 0B1h, 8Bh, 53h, 0Ch, 8Bh, 04h
    db 0B2h, 83h, 0C4h, 04h, 3Bh, 0C7h, 75h, 04h, 89h, 7Ch, 24h, 10h, 8Bh, 44h, 24h, 10h
    db 46h, 3Bh, 0C7h, 75h, 0AFh, 0EBh, 06h, 39h, 7Ch, 24h, 10h, 75h, 4Ch, 8Bh, 03h, 8Bh
    db 3Dh, 0D4h, 93h, 35h, 01h, 50h, 0FFh, 0D7h, 8Bh, 6Ch, 24h, 1Ch, 83h, 0C4h, 04h, 33h
    db 0F6h, 85h, 0EDh, 7Eh, 25h, 8Bh, 43h, 08h, 85h, 0C0h, 74h, 09h, 8Bh, 0Ch, 0B0h, 51h
    db 0FFh, 0D7h, 83h, 0C4h, 04h, 8Bh, 43h, 0Ch, 85h, 0C0h, 74h, 09h, 8Bh, 14h, 0B0h, 52h
    db 0FFh, 0D7h, 83h, 0C4h, 04h, 46h, 3Bh, 0F5h, 7Ch, 0DBh, 8Bh, 43h, 08h, 50h, 0FFh, 0D7h
    db 8Bh, 4Bh, 0Ch, 51h, 0FFh, 0D7h, 83h, 0C4h, 08h, 8Bh, 44h, 24h, 10h, 5Fh, 5Eh, 5Dh
    db 5Bh, 59h, 0C3h, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C3h
?d_0085d970@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DB00 size 87
public ?d_0085db00@@YAXXZ
?d_0085db00@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0D4h, 93h, 35h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 50h
    db 0FFh, 0D3h, 8Bh, 46h, 04h, 83h, 0C4h, 04h, 33h, 0FFh, 85h, 0C0h, 7Eh, 26h, 8Bh, 0FFh
    db 8Bh, 4Eh, 08h, 8Bh, 14h, 0B9h, 52h, 0FFh, 0D3h, 8Bh, 46h, 0Ch, 83h, 0C4h, 04h, 85h
    db 0C0h, 74h, 09h, 8Bh, 04h, 0B8h, 50h, 0FFh, 0D3h, 83h, 0C4h, 04h, 8Bh, 46h, 04h, 47h
    db 3Bh, 0F8h, 7Ch, 0DCh, 8Bh, 4Eh, 08h, 51h, 0FFh, 0D3h, 8Bh, 56h, 0Ch, 52h, 0FFh, 0D3h
    db 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 0C3h
?d_0085db00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DB60 size 42
public ?d_0085db60@@YAXXZ
?d_0085db60@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 51h, 04h, 50h, 8Bh, 44h, 24h
    db 18h, 52h, 50h, 0FFh, 51h, 08h, 83h, 0C4h, 1Ch, 0C3h
?d_0085db60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DD40 size 87
public ?d_0085dd40@@YAXXZ
?d_0085dd40@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0D4h, 93h, 35h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 46h, 04h, 57h
    db 50h, 0FFh, 0D3h, 8Bh, 46h, 08h, 83h, 0C4h, 04h, 33h, 0FFh, 85h, 0C0h, 7Eh, 25h, 90h
    db 8Bh, 4Eh, 0Ch, 8Bh, 14h, 0B9h, 52h, 0FFh, 0D3h, 8Bh, 46h, 10h, 83h, 0C4h, 04h, 85h
    db 0C0h, 74h, 09h, 8Bh, 04h, 0B8h, 50h, 0FFh, 0D3h, 83h, 0C4h, 04h, 8Bh, 46h, 08h, 47h
    db 3Bh, 0F8h, 7Ch, 0DCh, 8Bh, 4Eh, 0Ch, 51h, 0FFh, 0D3h, 8Bh, 56h, 10h, 52h, 0FFh, 0D3h
    db 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 0C3h
?d_0085dd40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DDA0 size 46
public ?d_0085dda0@@YAXXZ
?d_0085dda0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 10h, 52h, 8Bh
    db 50h, 0Ch, 52h, 8Bh, 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 51h, 04h
    db 50h, 8Bh, 44h, 24h, 1Ch, 52h, 50h, 0FFh, 51h, 08h, 83h, 0C4h, 20h, 0C3h
?d_0085dda0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DE30 size 38
public ?d_0085de30@@YAXXZ
?d_0085de30@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 10h, 8Bh, 51h, 0Ch, 52h, 8Bh, 50h, 0Ch, 52h, 8Bh
    db 50h, 08h, 52h, 8Bh, 50h, 04h, 8Bh, 00h, 52h, 8Bh, 54h, 24h, 14h, 50h, 52h, 0FFh
    db 51h, 08h, 83h, 0C4h, 18h, 0C3h
?d_0085de30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DE60 size 52
public ?d_0085de60@@YAXXZ
?d_0085de60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 08h, 56h, 8Bh, 74h, 24h, 08h, 89h, 0Eh, 8Bh, 40h, 04h
    db 85h, 0C0h, 74h, 12h, 50h, 0E8h, 36h, 65h, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h
    db 46h, 04h, 75h, 09h, 5Eh, 0C3h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0B8h, 01h, 00h
    db 00h, 00h, 5Eh, 0C3h
?d_0085de60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DEA0 size 17
public ?d_0085dea0@@YAXXZ
?d_0085dea0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 48h, 04h, 89h, 4Ch, 24h, 04h, 0FFh, 25h, 0D4h, 93h, 35h
    db 01h
?d_0085dea0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DEC0 size 30
public ?d_0085dec0@@YAXXZ
?d_0085dec0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 50h, 0Ch, 8Bh, 48h, 10h, 52h, 8Bh, 51h, 04h, 8Bh, 09h
    db 52h, 8Bh, 54h, 24h, 0Ch, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 10h, 0C3h
?d_0085dec0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085DF10 size 26
public ?d_0085df10@@YAXXZ
?d_0085df10@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 48h, 0Ch, 8Bh, 50h, 10h, 51h, 8Bh, 0Ah, 8Bh, 54h, 24h
    db 08h, 51h, 52h, 0FFh, 50h, 08h, 83h, 0C4h, 0Ch, 0C3h
?d_0085df10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085F4F0 size 367
public ?d_0085f4f0@@YAXXZ
?d_0085f4f0@@YAXXZ PROC
    db 55h, 56h, 57h, 8Bh, 7Ch, 24h, 28h, 8Bh, 47h, 38h, 8Bh, 37h, 33h, 0EDh, 3Bh, 0C5h
    db 74h, 0Eh, 57h, 56h, 0E8h, 0C7h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Dh, 0C3h
    db 39h, 6Ch, 24h, 14h, 74h, 29h, 56h, 0E8h, 04h, 8Ch, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h
    db 0C0h, 75h, 75h, 8Bh, 4Fh, 2Ch, 33h, 0C0h, 66h, 8Bh, 47h, 30h, 50h, 51h, 56h, 0E8h
    db 0DCh, 5Eh, 00h, 00h, 83h, 0C4h, 0Ch, 85h, 0C0h, 75h, 43h, 89h, 6Ch, 24h, 14h, 55h
    db 6Ah, 02h, 56h, 0E8h, 98h, 49h, 00h, 00h, 83h, 0C4h, 0Ch, 8Bh, 57h, 0Ch, 8Bh, 47h
    db 18h, 8Bh, 4Fh, 10h, 52h, 50h, 8Bh, 44h, 24h, 1Ch, 33h, 0D2h, 3Bh, 0C5h, 0Fh, 95h
    db 0C2h, 51h, 6Ah, 02h, 4Ah, 83h, 0E2h, 0Ah, 52h, 50h, 56h, 0E8h, 0C0h, 0EDh, 0FFh, 0FFh
    db 57h, 56h, 0E8h, 59h, 0FAh, 0FFh, 0FFh, 83h, 0C4h, 24h, 5Fh, 5Eh, 5Dh, 0C3h, 39h, 6Fh
    db 34h, 74h, 1Fh, 89h, 6Fh, 34h, 8Bh, 96h, 0F0h, 0Ah, 00h, 00h, 0C7h, 82h, 0C4h, 00h
    db 00h, 00h, 01h, 00h, 00h, 00h, 0EBh, 0Ah, 0C7h, 86h, 40h, 0Bh, 00h, 00h, 01h, 00h
    db 00h, 00h, 8Bh, 47h, 20h, 53h, 50h, 6Ah, 02h, 56h, 0E8h, 0C1h, 48h, 00h, 00h, 83h
    db 0C4h, 0Ch, 8Bh, 44h, 24h, 20h, 3Bh, 0C5h, 7Eh, 30h, 8Bh, 5Ch, 24h, 24h, 8Bh, 6Ch
    db 24h, 28h, 2Bh, 0EBh, 89h, 44h, 24h, 2Ch, 8Bh, 0Ch, 2Bh, 8Bh, 13h, 51h, 6Ah, 02h
    db 52h, 56h, 0E8h, 0F9h, 42h, 00h, 00h, 8Bh, 44h, 24h, 3Ch, 83h, 0C4h, 10h, 83h, 0C3h
    db 04h, 48h, 89h, 44h, 24h, 2Ch, 75h, 0E0h, 33h, 0EDh, 8Bh, 47h, 20h, 8Bh, 5Ch, 24h
    db 1Ch, 8Bh, 0Eh, 50h, 53h, 51h, 0E8h, 0E5h, 14h, 00h, 00h, 8Bh, 86h, 48h, 0Bh, 00h
    db 00h, 83h, 0C4h, 0Ch, 3Bh, 0C5h, 74h, 0Dh, 8Bh, 16h, 50h, 53h, 52h, 0E8h, 1Eh, 19h
    db 00h, 00h, 83h, 0C4h, 0Ch, 39h, 6Fh, 34h, 5Bh, 0Fh, 84h, 2Ch, 0FFh, 0FFh, 0FFh, 56h
    db 0E8h, 0FBh, 8Ah, 0FFh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 0Fh, 84h, 1Bh, 0FFh, 0FFh, 0FFh
    db 8Bh, 86h, 0F0h, 1Eh, 00h, 00h, 8Bh, 4Fh, 2Ch, 89h, 48h, 2Ch, 8Bh, 96h, 0F0h, 1Eh
    db 00h, 00h, 66h, 8Bh, 47h, 30h, 66h, 89h, 42h, 30h, 8Bh, 8Eh, 0F0h, 1Eh, 00h, 00h
    db 0C7h, 41h, 34h, 01h, 00h, 00h, 00h, 89h, 6Fh, 34h, 0E9h, 0ECh, 0FEh, 0FFh, 0FFh
?d_0085f4f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085F8A0 size 185
public ?d_0085f8a0@@YAXXZ
?d_0085f8a0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 24h, 8Bh, 46h, 38h, 85h, 0C0h, 8Bh, 1Eh, 74h, 0Dh, 56h
    db 53h, 0E8h, 1Ah, 0F7h, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Eh, 5Bh, 0C3h, 57h, 8Bh, 7Ch, 24h
    db 14h, 85h, 0FFh, 74h, 54h, 8Bh, 46h, 1Ch, 68h, 1Ch, 30h, 07h, 01h, 50h, 53h, 0E8h
    db 9Ch, 45h, 00h, 00h, 8Bh, 44h, 24h, 28h, 83h, 0C4h, 0Ch, 85h, 0C0h, 7Eh, 49h, 8Bh
    db 7Ch, 24h, 20h, 55h, 8Bh, 6Ch, 24h, 28h, 2Bh, 0EFh, 89h, 44h, 24h, 2Ch, 8Bh, 0FFh
    db 8Bh, 0Ch, 2Fh, 8Bh, 56h, 1Ch, 8Bh, 07h, 51h, 52h, 50h, 53h, 0E8h, 0CFh, 3Fh, 00h
    db 00h, 8Bh, 44h, 24h, 3Ch, 83h, 0C4h, 10h, 83h, 0C7h, 04h, 48h, 89h, 44h, 24h, 2Ch
    db 75h, 0DEh, 8Bh, 7Ch, 24h, 18h, 5Dh, 0EBh, 0Fh, 8Bh, 4Eh, 1Ch, 6Ah, 00h, 51h, 53h
    db 0E8h, 0BBh, 45h, 00h, 00h, 83h, 0C4h, 0Ch, 8Bh, 56h, 0Ch, 8Bh, 46h, 18h, 8Bh, 4Eh
    db 10h, 52h, 8Bh, 56h, 1Ch, 50h, 33h, 0C0h, 85h, 0FFh, 0Fh, 95h, 0C0h, 51h, 52h, 48h
    db 83h, 0E0h, 0Ah, 50h, 57h, 53h, 0E8h, 0E5h, 0E9h, 0FFh, 0FFh, 56h, 53h, 0E8h, 7Eh, 0F6h
    db 0FFh, 0FFh, 83h, 0C4h, 24h, 5Fh, 5Eh, 5Bh, 0C3h
?d_0085f8a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085FD80 size 163
public ?d_0085fd80@@YAXXZ
?d_0085fd80@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 24h, 8Bh, 1Eh, 57h, 8Bh, 7Ch, 24h, 14h, 85h, 0FFh, 74h
    db 43h, 8Bh, 44h, 24h, 18h, 85h, 0C0h, 74h, 3Bh, 55h, 8Bh, 6Ch, 24h, 20h, 85h, 0EDh
    db 7Eh, 31h, 8Bh, 74h, 24h, 24h, 8Bh, 7Ch, 24h, 28h, 2Bh, 0FEh, 8Dh, 64h, 24h, 00h
    db 8Bh, 04h, 37h, 8Bh, 0Eh, 8Bh, 54h, 24h, 1Ch, 50h, 51h, 52h, 53h, 0E8h, 0DEh, 5Dh
    db 00h, 00h, 83h, 0C4h, 10h, 83h, 0C6h, 04h, 4Dh, 75h, 0E5h, 8Bh, 74h, 24h, 2Ch, 8Bh
    db 7Ch, 24h, 18h, 5Dh, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 27h, 8Bh, 4Eh, 0Ch, 8Bh, 56h
    db 18h, 51h, 8Bh, 4Ch, 24h, 24h, 52h, 8Bh, 54h, 24h, 24h, 50h, 8Bh, 44h, 24h, 30h
    db 50h, 8Bh, 44h, 24h, 28h, 51h, 52h, 50h, 57h, 53h, 0E8h, 31h, 0EFh, 0FFh, 0FFh, 83h
    db 0C4h, 24h, 85h, 0FFh, 74h, 0Fh, 8Bh, 44h, 24h, 18h, 85h, 0C0h, 74h, 07h, 8Bh, 46h
    db 28h, 85h, 0C0h, 75h, 0Ah, 56h, 53h, 0E8h, 0B4h, 0F1h, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh
    db 5Eh, 5Bh, 0C3h
?d_0085fd80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085FE30 size 120
public ?d_0085fe30@@YAXXZ
?d_0085fe30@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 0Ch, 85h, 0F6h, 74h, 6Bh, 80h, 3Eh, 00h, 74h, 66h, 57h, 8Bh
    db 7Ch, 24h, 14h, 85h, 0FFh, 7Fh, 05h, 5Fh, 33h, 0C0h, 5Eh, 0C3h, 8Bh, 44h, 24h, 24h
    db 8Bh, 4Ch, 24h, 20h, 8Bh, 54h, 24h, 1Ch, 53h, 8Bh, 5Ch, 24h, 10h, 50h, 51h, 52h
    db 6Ah, 00h, 6Ah, 0Ah, 0E8h, 0D7h, 0F2h, 0FFh, 0FFh, 83h, 0C4h, 14h, 85h, 0C0h, 75h, 04h
    db 5Bh, 5Fh, 5Eh, 0C3h, 8Ah, 16h, 33h, 0C9h, 6Ah, 00h, 50h, 80h, 0FAh, 23h, 8Bh, 54h
    db 24h, 24h, 0Fh, 94h, 0C1h, 68h, 80h, 0FDh, 0C5h, 00h, 52h, 57h, 56h, 89h, 48h, 28h
    db 8Bh, 03h, 50h, 0E8h, 0A8h, 1Ah, 00h, 00h, 83h, 0C4h, 1Ch, 5Bh, 5Fh, 0B8h, 01h, 00h
    db 00h, 00h, 5Eh, 0C3h, 33h, 0C0h, 5Eh, 0C3h
?d_0085fe30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0085FEB0 size 175
public ?d_0085feb0@@YAXXZ
?d_0085feb0@@YAXXZ PROC
    db 55h, 56h, 8Bh, 74h, 24h, 10h, 85h, 0F6h, 57h, 8Bh, 7Ch, 24h, 2Ch, 8Bh, 2Fh, 74h
    db 4Bh, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 74h, 43h, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 7Eh
    db 3Bh, 8Bh, 74h, 24h, 24h, 53h, 8Bh, 5Ch, 24h, 2Ch, 2Bh, 0DEh, 89h, 44h, 24h, 30h
    db 8Bh, 04h, 33h, 8Bh, 0Eh, 8Bh, 54h, 24h, 20h, 50h, 8Bh, 47h, 1Ch, 51h, 52h, 50h
    db 55h, 0E8h, 3Ah, 5Dh, 00h, 00h, 8Bh, 44h, 24h, 44h, 83h, 0C4h, 14h, 83h, 0C6h, 04h
    db 48h, 89h, 44h, 24h, 30h, 75h, 0D9h, 8Bh, 74h, 24h, 18h, 5Bh, 8Bh, 47h, 10h, 85h
    db 0C0h, 74h, 2Bh, 8Bh, 4Fh, 0Ch, 8Bh, 57h, 18h, 51h, 8Bh, 4Ch, 24h, 28h, 52h, 8Bh
    db 54h, 24h, 28h, 50h, 8Bh, 44h, 24h, 34h, 50h, 8Bh, 44h, 24h, 2Ch, 51h, 8Bh, 4Fh
    db 1Ch, 52h, 50h, 51h, 56h, 55h, 0E8h, 55h, 0EEh, 0FFh, 0FFh, 83h, 0C4h, 28h, 85h, 0F6h
    db 74h, 0Fh, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 74h, 07h, 8Bh, 47h, 28h, 85h, 0C0h, 75h
    db 0Ah, 57h, 55h, 0E8h, 78h, 0F0h, 0FFh, 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Dh, 0C3h
?d_0085feb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00860170 size 35
public ?d_00860170@@YAXXZ
?d_00860170@@YAXXZ PROC
    db 56h, 57h, 0E8h, 0C9h, 0C1h, 00h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 0Fh, 56h, 57h
    db 0E8h, 0ABh, 14h, 01h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 01h, 0C3h, 0B8h, 01h, 00h
    db 00h, 00h, 0C3h
?d_00860170@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00860380 size 108
public ?d_00860380@@YAXXZ
?d_00860380@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 83h, 3Eh, 00h, 75h, 60h, 57h, 8Bh, 7Ch, 24h, 14h, 85h
    db 0FFh, 75h, 1Ah, 8Bh, 46h, 14h, 85h, 0C0h, 89h, 7Eh, 04h, 74h, 4Ch, 8Bh, 4Eh, 18h
    db 51h, 6Ah, 01h, 57h, 56h, 0FFh, 0D0h, 83h, 0C4h, 10h, 5Fh, 5Eh, 0C3h, 8Bh, 44h, 24h
    db 18h, 85h, 0C0h, 75h, 05h, 0B8h, 1Ch, 30h, 07h, 01h, 8Bh, 54h, 24h, 10h, 50h, 57h
    db 52h, 8Dh, 46h, 1Ch, 68h, 0ECh, 0Fh, 13h, 01h, 50h, 0E8h, 0A1h, 0A9h, 0FFh, 0FFh, 6Ah
    db 40h, 8Dh, 8Eh, 10h, 05h, 00h, 00h, 57h, 51h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 83h
    db 0C4h, 20h, 0C6h, 86h, 4Fh, 05h, 00h, 00h, 00h, 5Fh, 5Eh, 0C3h
?d_00860380@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00860620 size 103
public ?d_00860620@@YAXXZ
?d_00860620@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 10h, 0Fh, 0BEh, 06h, 57h, 50h, 0FFh, 15h, 10h, 94h, 35h
    db 01h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 05h, 80h, 3Eh, 2Dh, 75h, 0Ah, 8Bh, 7Ch, 24h
    db 10h, 0C6h, 07h, 5Fh, 47h, 0EBh, 04h, 8Bh, 7Ch, 24h, 10h, 0Fh, 0BEh, 1Eh, 85h, 0DBh
    db 74h, 2Eh, 55h, 8Bh, 2Dh, 9Ch, 94h, 35h, 01h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 53h, 68h, 20h, 10h, 13h, 01h, 46h, 0FFh, 0D5h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 05h
    db 0BBh, 5Fh, 00h, 00h, 00h, 88h, 1Fh, 0Fh, 0BEh, 1Eh, 47h, 85h, 0DBh, 75h, 0E1h, 5Dh
    db 0C6h, 07h, 00h, 5Fh, 5Eh, 5Bh, 0C3h
?d_00860620@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00860690 size 83
public ?d_00860690@@YAXXZ
?d_00860690@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 8Bh, 0C3h, 57h, 8Dh, 50h, 01h, 8Dh, 64h, 24h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 8Bh, 7Ch, 24h, 14h, 2Bh, 0C2h, 8Bh, 0C8h, 8Bh
    db 0C7h, 8Dh, 70h, 01h, 8Ah, 10h, 40h, 84h, 0D2h, 75h, 0F9h, 2Bh, 0C6h, 3Bh, 0C1h, 7Dh
    db 1Ch, 2Bh, 0C8h, 8Dh, 34h, 19h, 57h, 56h, 0FFh, 15h, 3Ch, 93h, 35h, 01h, 83h, 0C4h
    db 08h, 85h, 0C0h, 75h, 08h, 5Fh, 88h, 06h, 5Eh, 8Bh, 0C3h, 5Bh, 0C3h, 5Fh, 5Eh, 33h
    db 0C0h, 5Bh, 0C3h
?d_00860690@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00860F80 size 108
public ?d_00860f80@@YAXXZ
?d_00860f80@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 61h, 83h, 3Eh, 00h, 74h, 5Ch, 57h, 8Bh
    db 7Ch, 24h, 10h, 57h, 8Dh, 46h, 1Ch, 68h, 84h, 11h, 13h, 01h, 50h, 0E8h, 0CEh, 9Dh
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 20h, 51h, 52h, 57h, 56h, 0E8h, 0BDh
    db 0B7h, 00h, 00h, 8Bh, 0F8h, 8Bh, 44h, 24h, 38h, 83h, 0C4h, 1Ch, 85h, 0C0h, 74h, 29h
    db 57h, 0E8h, 2Ah, 0F2h, 0FFh, 0FFh, 6Ah, 0Ah, 0E8h, 0A3h, 33h, 0FFh, 0FFh, 57h, 56h, 0E8h
    db 6Ch, 0B3h, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 75h, 0E5h, 57h, 56h, 0E8h, 4Eh, 06h
    db 01h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 0D7h, 5Fh, 5Eh, 0C3h
?d_00860f80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00861090 size 62
public ?d_00861090@@YAXXZ
?d_00861090@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 83h, 3Fh, 00h, 75h, 05h, 83h, 0C8h, 0FFh, 5Fh, 0C3h, 56h
    db 8Bh, 74h, 24h, 10h, 85h, 0F6h, 74h, 20h, 80h, 3Eh, 00h, 74h, 1Bh, 56h, 57h, 0E8h
    db 8Ch, 0Bh, 01h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0Dh, 56h, 57h, 0E8h, 6Eh, 0Fh
    db 01h, 00h, 83h, 0C4h, 08h, 5Eh, 5Fh, 0C3h, 5Eh, 83h, 0C8h, 0FFh, 5Fh, 0C3h
?d_00861090@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00861300 size 108
public ?d_00861300@@YAXXZ
?d_00861300@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 61h, 83h, 3Eh, 00h, 74h, 5Ch, 57h, 8Bh
    db 7Ch, 24h, 10h, 57h, 8Dh, 46h, 1Ch, 68h, 0CCh, 11h, 13h, 01h, 50h, 0E8h, 4Eh, 9Ah
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 20h, 51h, 52h, 57h, 56h, 0E8h, 0BDh
    db 0B2h, 00h, 00h, 8Bh, 0F8h, 8Bh, 44h, 24h, 38h, 83h, 0C4h, 1Ch, 85h, 0C0h, 74h, 29h
    db 57h, 0E8h, 0AAh, 0EEh, 0FFh, 0FFh, 6Ah, 0Ah, 0E8h, 23h, 30h, 0FFh, 0FFh, 57h, 56h, 0E8h
    db 0ECh, 0AFh, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 75h, 0E5h, 57h, 56h, 0E8h, 0CEh, 02h
    db 01h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 0D7h, 5Fh, 5Eh, 0C3h
?d_00861300@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00861470 size 108
public ?d_00861470@@YAXXZ
?d_00861470@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 61h, 83h, 3Eh, 00h, 74h, 5Ch, 57h, 8Bh
    db 7Ch, 24h, 10h, 57h, 8Dh, 46h, 1Ch, 68h, 0D8h, 11h, 13h, 01h, 50h, 0E8h, 0DEh, 98h
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 24h, 8Bh, 54h, 24h, 20h, 51h, 52h, 57h, 56h, 0E8h, 0DDh
    db 0B1h, 00h, 00h, 8Bh, 0F8h, 8Bh, 44h, 24h, 38h, 83h, 0C4h, 1Ch, 85h, 0C0h, 74h, 29h
    db 57h, 0E8h, 3Ah, 0EDh, 0FFh, 0FFh, 6Ah, 0Ah, 0E8h, 0B3h, 2Eh, 0FFh, 0FFh, 57h, 56h, 0E8h
    db 7Ch, 0AEh, 00h, 00h, 83h, 0C4h, 10h, 85h, 0C0h, 75h, 0E5h, 57h, 56h, 0E8h, 5Eh, 01h
    db 01h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 0D7h, 5Fh, 5Eh, 0C3h
?d_00861470@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00861550 size 52
public ?d_00861550@@YAXXZ
?d_00861550@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 29h, 83h, 3Eh, 00h, 74h, 24h, 57h, 8Bh
    db 7Ch, 24h, 14h, 57h, 8Dh, 46h, 1Ch, 68h, 0CCh, 11h, 13h, 01h, 50h, 0E8h, 0FEh, 97h
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 1Ch, 51h, 57h, 56h, 0E8h, 92h, 0B1h, 00h, 00h, 83h, 0C4h
    db 18h, 5Fh, 5Eh, 0C3h
?d_00861550@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008624C0 size 119
public ?d_008624c0@@YAXXZ
?d_008624c0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 83h, 3Eh, 00h, 75h, 6Bh, 57h, 8Bh, 7Ch, 24h, 10h, 85h
    db 0FFh, 75h, 1Ah, 8Bh, 46h, 14h, 85h, 0C0h, 89h, 7Eh, 04h, 74h, 57h, 8Bh, 4Eh, 18h
    db 51h, 6Ah, 01h, 57h, 56h, 0FFh, 0D0h, 83h, 0C4h, 10h, 5Fh, 5Eh, 0C3h, 6Ah, 40h, 8Dh
    db 96h, 6Ch, 03h, 00h, 00h, 57h, 52h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 57h, 0C6h, 86h
    db 0ABh, 03h, 00h, 00h, 00h, 0E8h, 36h, 0F8h, 0FFh, 0FFh, 83h, 0C4h, 10h, 85h, 0C0h, 75h
    db 11h, 50h, 50h, 57h, 6Ah, 01h, 56h, 0E8h, 84h, 0F8h, 0FFh, 0FFh, 83h, 0C4h, 14h, 5Fh
    db 5Eh, 0C3h, 57h, 68h, 14h, 10h, 13h, 01h, 83h, 0C6h, 1Ch, 56h, 0E8h, 3Fh, 88h, 0FFh
    db 0FFh, 83h, 0C4h, 0Ch, 5Fh, 5Eh, 0C3h
?d_008624c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00863090 size 110
public ?d_00863090@@YAXXZ
?d_00863090@@YAXXZ PROC
    db 81h, 0ECh, 84h, 00h, 00h, 00h, 56h, 8Bh, 35h, 0C0h, 94h, 35h, 01h, 57h, 6Ah, 40h
    db 50h, 8Dh, 4Ch, 24h, 10h, 51h, 0FFh, 0D6h, 8Bh, 3Dh, 44h, 93h, 35h, 01h, 8Dh, 54h
    db 24h, 14h, 52h, 0C6h, 44h, 24h, 57h, 00h, 0FFh, 0D7h, 8Bh, 84h, 24h, 0A4h, 00h, 00h
    db 00h, 6Ah, 40h, 50h, 8Dh, 4Ch, 24h, 60h, 51h, 0FFh, 0D6h, 8Dh, 54h, 24h, 24h, 52h
    db 0C6h, 84h, 24h, 0A7h, 00h, 00h, 00h, 00h, 0FFh, 0D7h, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h
    db 00h, 8Bh, 91h, 0E8h, 0Ah, 00h, 00h, 8Dh, 44h, 24h, 28h, 50h, 52h, 0E8h, 3Eh, 3Eh
    db 00h, 00h, 83h, 0C4h, 28h, 5Fh, 5Eh, 81h, 0C4h, 84h, 00h, 00h, 00h, 0C3h
?d_00863090@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008631F0 size 57
public ?d_008631f0@@YAXXZ
?d_008631f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 88h, 0C8h, 0Ah, 00h, 00h, 85h, 0C9h, 74h, 16h, 8Bh, 4Ch
    db 24h, 0Ch, 51h, 50h, 8Bh, 44h, 24h, 10h, 0E8h, 83h, 0FEh, 0FFh, 0FFh, 83h, 0C4h, 08h
    db 85h, 0C0h, 75h, 03h, 33h, 0C0h, 0C3h, 8Bh, 90h, 80h, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 10h, 89h, 10h, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_008631f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008636C0 size 32
public ?d_008636c0@@YAXXZ
?d_008636c0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 07h, 8Bh, 48h, 48h, 85h, 0C9h, 75h, 03h, 33h
    db 0C0h, 0C3h, 8Bh, 40h, 64h, 83h, 0E0h, 30h, 2Ch, 30h, 0F6h, 0D8h, 1Bh, 0C0h, 40h, 0C3h
?d_008636c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00864E30 size 123
public ?d_00864e30@@YAXXZ
?d_00864e30@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 8Bh, 87h, 0A0h, 0Bh, 00h, 00h, 85h, 0C0h, 74h, 3Eh, 8Bh
    db 44h, 24h, 14h, 56h, 8Bh, 74h, 24h, 10h, 85h, 0C0h, 8Ah, 46h, 15h, 74h, 30h, 0A8h
    db 01h, 74h, 10h, 8Dh, 87h, 3Ch, 17h, 00h, 00h, 56h, 50h, 0E8h, 10h, 4Fh, 00h, 00h
    db 83h, 0C4h, 08h, 8Bh, 16h, 33h, 0C9h, 66h, 8Bh, 4Eh, 04h, 81h, 0C7h, 0A4h, 0Bh, 00h
    db 00h, 51h, 52h, 57h, 0E8h, 0C7h, 42h, 00h, 00h, 83h, 0C4h, 0Ch, 5Eh, 5Fh, 0C3h, 0A8h
    db 01h, 74h, 0E0h, 81h, 0C7h, 3Ch, 17h, 00h, 00h, 56h, 57h, 0E8h, 0E0h, 4Eh, 00h, 00h
    db 8Bh, 54h, 24h, 1Ch, 33h, 0C0h, 85h, 0D2h, 0Fh, 95h, 0C0h, 50h, 6Ah, 01h, 56h, 57h
    db 0E8h, 8Bh, 4Ah, 00h, 00h, 83h, 0C4h, 18h, 5Eh, 5Fh, 0C3h
?d_00864e30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00864FE0 size 661
public ?d_00864fe0@@YAXXZ
?d_00864fe0@@YAXXZ PROC
    db 81h, 0ECh, 20h, 02h, 00h, 00h, 53h, 8Bh, 9Ch, 24h, 28h, 02h, 00h, 00h, 8Bh, 83h
    db 0A0h, 0Bh, 00h, 00h, 85h, 0C0h, 75h, 0Ah, 33h, 0C0h, 5Bh, 81h, 0C4h, 20h, 02h, 00h
    db 00h, 0C3h, 56h, 8Dh, 0B3h, 0A4h, 0Bh, 00h, 00h, 56h, 0E8h, 0F1h, 2Ah, 00h, 00h, 8Dh
    db 83h, 3Ch, 17h, 00h, 00h, 50h, 0E8h, 0C5h, 48h, 00h, 00h, 6Ah, 03h, 53h, 0E8h, 1Dh
    db 92h, 0FFh, 0FFh, 56h, 0E8h, 67h, 25h, 00h, 00h, 8Bh, 83h, 0A8h, 09h, 00h, 00h, 83h
    db 0C4h, 14h, 85h, 0C0h, 74h, 16h, 50h, 8Dh, 44h, 24h, 0Ch, 68h, 48h, 13h, 13h, 01h
    db 50h, 0FFh, 15h, 8Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0EBh, 27h, 8Bh, 0Dh, 38h, 13h
    db 13h, 01h, 8Bh, 15h, 3Ch, 13h, 13h, 01h, 0A1h, 40h, 13h, 13h, 01h, 89h, 4Ch, 24h
    db 08h, 8Bh, 0Dh, 44h, 13h, 13h, 01h, 89h, 54h, 24h, 0Ch, 89h, 44h, 24h, 10h, 89h
    db 4Ch, 24h, 14h, 8Bh, 0B4h, 24h, 38h, 02h, 00h, 00h, 85h, 0F6h, 57h, 74h, 6Bh, 8Dh
    db 54h, 24h, 0Ch, 52h, 8Dh, 84h, 24h, 30h, 01h, 00h, 00h, 68h, 2Ch, 13h, 13h, 01h
    db 50h, 0FFh, 15h, 8Ch, 94h, 35h, 01h, 8Dh, 84h, 24h, 38h, 01h, 00h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 0B9h, 0FFh, 00h
    db 00h, 00h, 2Bh, 0C8h, 51h, 8Dh, 94h, 24h, 30h, 01h, 00h, 00h, 56h, 52h, 0FFh, 15h
    db 0B8h, 94h, 35h, 01h, 8Dh, 0BCh, 24h, 38h, 01h, 00h, 00h, 83h, 0C4h, 0Ch, 0C6h, 84h
    db 24h, 2Ah, 02h, 00h, 00h, 00h, 4Fh, 8Ah, 47h, 01h, 47h, 84h, 0C0h, 75h, 0F8h, 66h
    db 0A1h, 04h, 28h, 08h, 01h, 66h, 89h, 07h, 0EBh, 16h, 33h, 0C0h, 8Dh, 64h, 24h, 00h
    db 8Ah, 4Ch, 04h, 0Ch, 88h, 8Ch, 04h, 2Ch, 01h, 00h, 00h, 40h, 84h, 0C9h, 75h, 0F0h
    db 0C7h, 83h, 78h, 17h, 00h, 00h, 00h, 00h, 00h, 00h, 0A1h, 20h, 13h, 13h, 01h, 8Bh
    db 15h, 1Ch, 13h, 13h, 01h, 8Bh, 0Dh, 18h, 13h, 13h, 01h, 89h, 44h, 24h, 34h, 0A0h
    db 2Ah, 13h, 13h, 01h, 89h, 54h, 24h, 30h, 66h, 8Bh, 15h, 28h, 13h, 13h, 01h, 89h
    db 4Ch, 24h, 2Ch, 8Bh, 0Dh, 24h, 13h, 13h, 01h, 88h, 44h, 24h, 3Eh, 8Dh, 44h, 24h
    db 2Ch, 66h, 89h, 54h, 24h, 3Ch, 89h, 4Ch, 24h, 38h, 8Dh, 50h, 01h, 8Dh, 49h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 6Ah, 01h, 8Dh, 0B3h, 3Ch, 17h, 00h
    db 00h, 56h, 8Bh, 0F8h, 0E8h, 0E7h, 4Bh, 00h, 00h, 6Ah, 0Bh, 56h, 0E8h, 0DFh, 4Bh, 00h
    db 00h, 8Bh, 84h, 24h, 48h, 02h, 00h, 00h, 83h, 0C4h, 10h, 33h, 0F6h, 85h, 0C0h, 7Eh
    db 76h, 55h, 8Bh, 0ACh, 24h, 38h, 02h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0Fh, 0B6h, 0Ch, 2Eh, 8Bh, 0Ch, 8Dh, 0E8h, 84h, 2Ch, 01h, 8Bh, 0C1h, 8Dh, 58h, 01h
    db 8Ah, 10h, 40h, 84h, 0D2h, 75h, 0F9h, 2Bh, 0C3h, 8Dh, 54h, 38h, 01h, 81h, 0FAh, 00h
    db 01h, 00h, 00h, 7Dh, 3Ah, 51h, 8Dh, 44h, 3Ch, 34h, 68h, 60h, 0Ch, 13h, 01h, 50h
    db 0FFh, 15h, 8Ch, 94h, 35h, 01h, 33h, 0C9h, 8Ah, 0Ch, 2Eh, 03h, 0F8h, 8Bh, 84h, 24h
    db 40h, 02h, 00h, 00h, 05h, 3Ch, 17h, 00h, 00h, 51h, 50h, 0E8h, 70h, 4Bh, 00h, 00h
    db 8Bh, 84h, 24h, 50h, 02h, 00h, 00h, 83h, 0C4h, 14h, 46h, 3Bh, 0F0h, 7Ch, 0A1h, 8Bh
    db 9Ch, 24h, 34h, 02h, 00h, 00h, 5Dh, 6Ah, 00h, 6Ah, 04h, 8Dh, 94h, 24h, 34h, 01h
    db 00h, 00h, 52h, 8Dh, 44h, 24h, 38h, 50h, 8Dh, 0B3h, 0A4h, 0Bh, 00h, 00h, 56h, 0E8h
    db 0ECh, 38h, 00h, 00h, 83h, 0C4h, 14h, 85h, 0C0h, 5Fh, 74h, 32h, 8Bh, 83h, 0A0h, 0Bh
    db 00h, 00h, 85h, 0C0h, 74h, 1Dh, 56h, 0E8h, 0D4h, 28h, 00h, 00h, 8Dh, 83h, 3Ch, 17h
    db 00h, 00h, 50h, 0E8h, 0A8h, 46h, 00h, 00h, 6Ah, 03h, 53h, 0E8h, 00h, 90h, 0FFh, 0FFh
    db 83h, 0C4h, 10h, 5Eh, 33h, 0C0h, 5Bh, 81h, 0C4h, 20h, 02h, 00h, 00h, 0C3h, 6Ah, 03h
    db 6Ah, 00h, 6Ah, 01h, 53h, 0C7h, 83h, 8Ch, 17h, 00h, 00h, 01h, 00h, 00h, 00h, 0E8h
    db 0BCh, 91h, 0FFh, 0FFh, 83h, 0C4h, 10h, 5Eh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 81h, 0C4h
    db 20h, 02h, 00h, 00h, 0C3h
?d_00864fe0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00866BD0 size 25
public ?d_00866bd0@@YAXXZ
?d_00866bd0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 50h, 68h, 0E4h, 13h, 13h, 01h, 51h, 0FFh
    db 15h, 8Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 0C3h
?d_00866bd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0086A100 size 88
public ?d_0086a100@@YAXXZ
?d_0086a100@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 14h, 85h, 0C0h, 74h, 36h, 8Bh, 06h, 57h, 33h
    db 0FFh, 85h, 0C0h, 7Eh, 1Fh, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 11h, 8Bh, 4Eh, 08h, 8Bh
    db 56h, 14h, 0Fh, 0AFh, 0CFh, 03h, 0CAh, 51h, 0FFh, 0D0h, 83h, 0C4h, 04h, 8Bh, 06h, 47h
    db 3Bh, 0F8h, 7Ch, 0E1h, 8Bh, 56h, 14h, 52h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h
    db 04h, 5Fh, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 10h, 8Bh, 54h, 24h, 14h, 89h, 46h
    db 14h, 89h, 0Eh, 89h, 56h, 04h, 5Eh, 0C3h
?d_0086a100@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0086C5F0 size 92
public ?d_0086c5f0@@YAXXZ
?d_0086c5f0@@YAXXZ PROC
    db 56h, 6Ah, 14h, 0FFh, 15h, 4Ch, 94h, 35h, 01h, 8Bh, 0F0h, 83h, 0C4h, 04h, 33h, 0C0h
    db 85h, 0F6h, 74h, 46h, 8Bh, 54h, 24h, 14h, 53h, 8Bh, 5Ch, 24h, 0Ch, 57h, 8Bh, 7Ch
    db 24h, 14h, 8Bh, 0CEh, 89h, 01h, 89h, 41h, 04h, 56h, 89h, 41h, 08h, 52h, 89h, 41h
    db 0Ch, 50h, 89h, 41h, 10h, 8Bh, 44h, 24h, 24h, 50h, 6Ah, 00h, 6Ah, 04h, 0E8h, 6Dh
    db 0FDh, 0FFh, 0FFh, 8Bh, 0F8h, 83h, 0C4h, 18h, 85h, 0FFh, 75h, 0Ah, 56h, 0FFh, 15h, 0D4h
    db 93h, 35h, 01h, 83h, 0C4h, 04h, 8Bh, 0C7h, 5Fh, 5Bh, 5Eh, 0C3h
?d_0086c5f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0086C680 size 39
public ?d_0086c680@@YAXXZ
?d_0086c680@@YAXXZ PROC
    db 8Bh, 44h, 24h, 10h, 8Bh, 4Ch, 24h, 0Ch, 53h, 8Bh, 5Ch, 24h, 08h, 57h, 8Bh, 7Ch
    db 24h, 10h, 6Ah, 00h, 50h, 6Ah, 00h, 51h, 6Ah, 00h, 6Ah, 0Bh, 0E8h, 0FFh, 0FCh, 0FFh
    db 0FFh, 83h, 0C4h, 18h, 5Fh, 5Bh, 0C3h
?d_0086c680@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0086C710 size 90
public ?d_0086c710@@YAXXZ
?d_0086c710@@YAXXZ PROC
    db 56h, 6Ah, 04h, 0FFh, 15h, 4Ch, 94h, 35h, 01h, 8Bh, 0F0h, 83h, 0C4h, 04h, 85h, 0F6h
    db 74h, 23h, 8Bh, 44h, 24h, 10h, 50h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0E8h, 7Eh, 7Ch
    db 0FEh, 0FFh, 83h, 0C4h, 04h, 85h, 0C0h, 89h, 06h, 75h, 0Eh, 56h, 0FFh, 15h, 0D4h, 93h
    db 35h, 01h, 83h, 0C4h, 04h, 33h, 0C0h, 5Eh, 0C3h, 53h, 8Bh, 5Ch, 24h, 0Ch, 57h, 8Bh
    db 7Ch, 24h, 14h, 56h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 00h, 6Ah, 07h, 0E8h, 3Dh
    db 0FCh, 0FFh, 0FFh, 83h, 0C4h, 18h, 5Fh, 5Bh, 5Eh, 0C3h
?d_0086c710@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0086C770 size 62
public ?d_0086c770@@YAXXZ
?d_0086c770@@YAXXZ PROC
    db 6Ah, 08h, 0FFh, 15h, 4Ch, 94h, 35h, 01h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 01h, 0C3h
    db 53h, 8Bh, 5Ch, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 50h, 8Bh, 0D0h, 8Bh, 44h, 24h
    db 1Ch, 33h, 0C9h, 50h, 89h, 0Ah, 51h, 89h, 4Ah, 04h, 8Bh, 4Ch, 24h, 20h, 51h, 6Ah
    db 00h, 6Ah, 08h, 0E8h, 0F8h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 18h, 5Fh, 5Bh, 0C3h
?d_0086c770@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00871690 size 62
public ?d_00871690@@YAXXZ
?d_00871690@@YAXXZ PROC
    db 81h, 0ECh, 0E4h, 01h, 00h, 00h, 68h, 01h, 01h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 08h
    db 51h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 8Bh, 84h, 24h, 0F4h, 01h, 00h, 00h, 8Bh, 88h
    db 0Ch, 08h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h, 51h, 0C6h, 84h, 24h, 14h, 01h, 00h
    db 00h, 00h, 0E8h, 69h, 58h, 0FFh, 0FFh, 81h, 0C4h, 0F8h, 01h, 00h, 00h, 0C3h
?d_00871690@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00872030 size 101
public ?d_00872030@@YAXXZ
?d_00872030@@YAXXZ PROC
    db 81h, 0ECh, 0E4h, 01h, 00h, 00h, 8Bh, 84h, 24h, 0ECh, 01h, 00h, 00h, 68h, 01h, 01h
    db 00h, 00h, 50h, 8Dh, 4Ch, 24h, 08h, 51h, 0FFh, 15h, 0C0h, 94h, 35h, 01h, 8Bh, 84h
    db 24h, 0F4h, 01h, 00h, 00h, 8Bh, 88h, 0Ch, 08h, 00h, 00h, 8Dh, 54h, 24h, 0Ch, 52h
    db 51h, 0C6h, 84h, 24h, 14h, 01h, 00h, 00h, 00h, 0E8h, 0C2h, 4Eh, 0FFh, 0FFh, 83h, 0C4h
    db 14h, 85h, 0C0h, 75h, 0Ah, 83h, 0C8h, 0FFh, 81h, 0C4h, 0E4h, 01h, 00h, 00h, 0C3h, 8Bh
    db 90h, 34h, 01h, 00h, 00h, 52h, 0E8h, 0A5h, 4Dh, 0FFh, 0FFh, 83h, 0C4h, 04h, 81h, 0C4h
    db 0E4h, 01h, 00h, 00h, 0C3h
?d_00872030@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00872510 size 153
public ?d_00872510@@YAXXZ
?d_00872510@@YAXXZ PROC
    db 81h, 0ECh, 0C4h, 02h, 00h, 00h, 8Bh, 84h, 24h, 0CCh, 02h, 00h, 00h, 56h, 57h, 8Bh
    db 3Dh, 0C0h, 94h, 35h, 01h, 68h, 01h, 01h, 00h, 00h, 50h, 8Dh, 8Ch, 24h, 0F0h, 00h
    db 00h, 00h, 51h, 0FFh, 0D7h, 8Bh, 84h, 24h, 0DCh, 02h, 00h, 00h, 8Bh, 88h, 0Ch, 08h
    db 00h, 00h, 8Dh, 94h, 24h, 0F4h, 00h, 00h, 00h, 52h, 51h, 0C6h, 84h, 24h, 0FCh, 01h
    db 00h, 00h, 00h, 0E8h, 0D8h, 49h, 0FFh, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 14h, 85h, 0F6h, 75h
    db 09h, 5Fh, 5Eh, 81h, 0C4h, 0C4h, 02h, 00h, 00h, 0C3h, 8Bh, 94h, 24h, 0D8h, 02h, 00h
    db 00h, 68h, 80h, 00h, 00h, 00h, 52h, 8Dh, 44h, 24h, 10h, 50h, 0FFh, 0D7h, 8Dh, 4Ch
    db 24h, 14h, 0C6h, 84h, 24h, 93h, 00h, 00h, 00h, 00h, 8Bh, 96h, 34h, 01h, 00h, 00h
    db 51h, 52h, 0E8h, 99h, 49h, 0FFh, 0FFh, 83h, 0C4h, 14h, 0F7h, 0D8h, 1Bh, 0C0h, 5Fh, 0F7h
    db 0D8h, 5Eh, 81h, 0C4h, 0C4h, 02h, 00h, 00h, 0C3h
?d_00872510@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008725B0 size 160
public ?d_008725b0@@YAXXZ
?d_008725b0@@YAXXZ PROC
    db 81h, 0ECh, 0C4h, 02h, 00h, 00h, 8Bh, 84h, 24h, 0CCh, 02h, 00h, 00h, 56h, 57h, 8Bh
    db 3Dh, 0C0h, 94h, 35h, 01h, 68h, 01h, 01h, 00h, 00h, 50h, 8Dh, 8Ch, 24h, 0F0h, 00h
    db 00h, 00h, 51h, 0FFh, 0D7h, 8Bh, 84h, 24h, 0DCh, 02h, 00h, 00h, 8Bh, 88h, 0Ch, 08h
    db 00h, 00h, 8Dh, 94h, 24h, 0F4h, 00h, 00h, 00h, 52h, 51h, 0C6h, 84h, 24h, 0FCh, 01h
    db 00h, 00h, 00h, 0E8h, 38h, 49h, 0FFh, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 14h, 85h, 0F6h, 74h
    db 34h, 8Bh, 94h, 24h, 0D8h, 02h, 00h, 00h, 68h, 80h, 00h, 00h, 00h, 52h, 8Dh, 44h
    db 24h, 10h, 50h, 0FFh, 0D7h, 8Dh, 4Ch, 24h, 14h, 0C6h, 84h, 24h, 93h, 00h, 00h, 00h
    db 00h, 8Bh, 96h, 34h, 01h, 00h, 00h, 51h, 52h, 0E8h, 02h, 49h, 0FFh, 0FFh, 83h, 0C4h
    db 14h, 85h, 0C0h, 75h, 0Ch, 5Fh, 83h, 0C8h, 0FFh, 5Eh, 81h, 0C4h, 0C4h, 02h, 00h, 00h
    db 0C3h, 8Bh, 80h, 0DCh, 00h, 00h, 00h, 5Fh, 5Eh, 81h, 0C4h, 0C4h, 02h, 00h, 00h, 0C3h
?d_008725b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00873120 size 75
public ?d_00873120@@YAXXZ
?d_00873120@@YAXXZ PROC
    db 56h, 8Bh, 0F2h, 66h, 8Bh, 50h, 02h, 66h, 83h, 0FAh, 01h, 57h, 8Bh, 7Ch, 24h, 0Ch
    db 75h, 0Ch, 50h, 0E8h, 78h, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Fh, 5Eh, 0C3h, 66h, 83h
    db 0FAh, 02h, 75h, 11h, 57h, 50h, 8Bh, 0C1h, 8Bh, 0FEh, 0E8h, 71h, 0FEh, 0FFh, 0FFh, 83h
    db 0C4h, 08h, 5Fh, 5Eh, 0C3h, 66h, 83h, 0FAh, 03h, 75h, 0Dh, 53h, 57h, 8Bh, 0DEh, 0E8h
    db 4Ch, 0FFh, 0FFh, 0FFh, 83h, 0C4h, 04h, 5Bh, 5Fh, 5Eh, 0C3h
?d_00873120@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00874530 size 40
public ?d_00874530@@YAXXZ
?d_00874530@@YAXXZ PROC
    db 57h, 8Bh, 0F8h, 85h, 0FFh, 74h, 1Fh, 53h, 8Bh, 0CAh, 83h, 0E1h, 1Fh, 8Bh, 0C2h, 0C1h
    db 0E8h, 05h, 0BBh, 01h, 00h, 00h, 00h, 0D3h, 0E3h, 8Bh, 0Ch, 86h, 33h, 0CBh, 42h, 4Fh
    db 89h, 0Ch, 86h, 75h, 0E3h, 5Bh, 5Fh, 0C3h
?d_00874530@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00874840 size 38
public ?d_00874840@@YAXXZ
?d_00874840@@YAXXZ PROC
    db 56h, 57h, 2Bh, 0D0h, 0BEh, 65h, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 0B9h, 65h, 00h, 00h, 00h, 8Bh, 3Ch, 02h, 89h, 38h, 83h, 0C0h, 04h, 49h, 75h, 0F5h
    db 4Eh, 75h, 0EDh, 5Fh, 5Eh, 0C3h
?d_00874840@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00875F90 size 53
public ?d_00875f90@@YAXXZ
?d_00875f90@@YAXXZ PROC
    db 57h, 33h, 0C0h, 0B9h, 30h, 02h, 00h, 00h, 0BFh, 20h, 35h, 35h, 01h, 0F3h, 0ABh, 0B9h
    db 30h, 02h, 00h, 00h, 0BFh, 60h, 4Eh, 35h, 01h, 0F3h, 0ABh, 0B9h, 80h, 00h, 00h, 00h
    db 0BFh, 00h, 4Ch, 35h, 01h, 0F3h, 0ABh, 0B9h, 80h, 00h, 00h, 00h, 0BFh, 0E0h, 49h, 35h
    db 01h, 0F3h, 0ABh, 5Fh, 0C3h
?d_00875f90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00876D90 size 70
public ?d_00876d90@@YAXXZ
?d_00876d90@@YAXXZ PROC
    db 81h, 0ECh, 98h, 01h, 00h, 00h, 8Dh, 04h, 24h, 50h, 8Dh, 4Ch, 24h, 08h, 51h, 56h
    db 57h, 0E8h, 0FAh, 0F7h, 0FFh, 0FFh, 83h, 0C4h, 10h, 85h, 0C0h, 75h, 07h, 81h, 0C4h, 98h
    db 01h, 00h, 00h, 0C3h, 8Dh, 54h, 24h, 04h, 52h, 8Bh, 94h, 24h, 0A0h, 01h, 00h, 00h
    db 56h, 57h, 0E8h, 0E9h, 0FDh, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 0B8h, 01h, 00h, 00h, 00h, 81h
    db 0C4h, 98h, 01h, 00h, 00h, 0C3h
?d_00876d90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00879810 size 81
public ?d_00879810@@YAXXZ
?d_00879810@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Ah, 06h, 3Ch, 02h, 74h, 04h, 3Ch, 01h, 75h, 40h, 66h
    db 8Bh, 4Eh, 02h, 0Fh, 0BFh, 0C1h, 05h, 0FFh, 7Fh, 00h, 00h, 79h, 29h, 0F7h, 0D8h, 83h
    db 0F8h, 40h, 7Ch, 13h, 0C6h, 06h, 00h, 66h, 0C7h, 46h, 02h, 01h, 80h, 33h, 0C0h, 89h
    db 46h, 04h, 89h, 46h, 08h, 0EBh, 0Fh, 03h, 0C8h, 66h, 89h, 4Eh, 02h, 8Bh, 0D0h, 8Bh
    db 0CEh, 0E8h, 0EAh, 0FEh, 0FFh, 0FFh, 80h, 3Eh, 00h, 74h, 04h, 80h, 66h, 0Ah, 0F8h, 5Eh
    db 0C3h
?d_00879810@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087AE50 size 89
public ?d_0087ae50@@YAXXZ
?d_0087ae50@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 85h, 0FFh, 75h, 04h, 33h, 0C0h, 5Fh, 0C3h, 56h, 8Bh, 74h
    db 24h, 10h, 85h, 0F6h, 74h, 3Eh, 80h, 3Eh, 00h, 74h, 39h, 8Bh, 54h, 24h, 14h, 85h
    db 0D2h, 74h, 31h, 80h, 3Ah, 00h, 74h, 2Ch, 8Bh, 44h, 24h, 18h, 85h, 0C0h, 74h, 05h
    db 80h, 38h, 00h, 75h, 02h, 8Bh, 0C2h, 8Bh, 4Ch, 24h, 1Ch, 85h, 0C9h, 75h, 05h, 0B9h
    db 0A0h, 27h, 13h, 01h, 51h, 50h, 52h, 56h, 57h, 0E8h, 42h, 1Dh, 00h, 00h, 83h, 0C4h
    db 14h, 5Eh, 5Fh, 0C3h, 5Eh, 33h, 0C0h, 5Fh, 0C3h
?d_0087ae50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087AEB0 size 84
public ?d_0087aeb0@@YAXXZ
?d_0087aeb0@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 85h, 0FFh, 75h, 04h, 33h, 0C0h, 5Fh, 0C3h, 56h, 8Bh, 74h
    db 24h, 10h, 85h, 0F6h, 74h, 39h, 80h, 3Eh, 00h, 74h, 34h, 8Bh, 4Ch, 24h, 18h, 85h
    db 0C9h, 7Ch, 2Ch, 8Bh, 54h, 24h, 14h, 75h, 04h, 85h, 0D2h, 74h, 22h, 8Bh, 44h, 24h
    db 20h, 85h, 0C0h, 75h, 05h, 0B8h, 0A0h, 27h, 13h, 01h, 50h, 8Bh, 44h, 24h, 20h, 50h
    db 51h, 52h, 56h, 57h, 0E8h, 0A7h, 1Dh, 00h, 00h, 83h, 0C4h, 18h, 5Eh, 5Fh, 0C3h, 5Eh
    db 33h, 0C0h, 5Fh, 0C3h
?d_0087aeb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087C610 size 31
public ?d_0087c610@@YAXXZ
?d_0087c610@@YAXXZ PROC
    db 56h, 6Ah, 18h, 0FFh, 15h, 4Ch, 94h, 35h, 01h, 8Bh, 0F0h, 83h, 0C4h, 04h, 85h, 0F6h
    db 75h, 02h, 5Eh, 0C3h, 56h, 0FFh, 15h, 4Ch, 8Eh, 35h, 01h, 8Bh, 0C6h, 5Eh, 0C3h
?d_0087c610@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087C9E0 size 91
public ?d_0087c9e0@@YAXXZ
?d_0087c9e0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 46h, 04h, 57h, 8Bh, 3Dh, 0D4h, 93h, 35h, 01h, 50h
    db 0FFh, 0D7h, 8Bh, 06h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 0Ch, 8Bh, 4Eh, 08h, 51h, 0FFh
    db 0D7h, 83h, 0C4h, 04h, 5Fh, 5Eh, 0C3h, 83h, 0F8h, 01h, 75h, 18h, 8Bh, 56h, 08h, 52h
    db 0FFh, 0D7h, 8Bh, 46h, 0Ch, 50h, 0FFh, 0D7h, 8Bh, 4Eh, 10h, 51h, 0FFh, 0D7h, 83h, 0C4h
    db 0Ch, 5Fh, 5Eh, 0C3h, 83h, 0F8h, 02h, 75h, 0Fh, 8Bh, 56h, 10h, 52h, 0FFh, 0D7h, 8Bh
    db 46h, 14h, 50h, 0FFh, 0D7h, 83h, 0C4h, 08h, 5Fh, 5Eh, 0C3h
?d_0087c9e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087D7A0 size 75
public ?d_0087d7a0@@YAXXZ
?d_0087d7a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 18h, 8Bh, 4Ch, 24h, 0Ch, 85h, 0C9h, 74h
    db 10h, 8Bh, 54h, 24h, 10h, 85h, 0D2h, 74h, 08h, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 7Fh
    db 04h, 33h, 0C0h, 5Eh, 0C3h, 89h, 41h, 08h, 0B8h, 01h, 00h, 00h, 00h, 89h, 31h, 89h
    db 51h, 04h, 0C7h, 41h, 0Ch, 00h, 00h, 00h, 00h, 0C7h, 41h, 14h, 00h, 00h, 00h, 00h
    db 89h, 41h, 18h, 89h, 41h, 1Ch, 0C6h, 02h, 00h, 5Eh, 0C3h
?d_0087d7a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087DAE0 size 16
public ?d_0087dae0@@YAXXZ
?d_0087dae0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 0Ch, 83h, 0C1h, 08h, 89h, 4Ch, 24h, 0Ch, 0E9h, 0F0h, 58h, 0FDh, 0FFh
?d_0087dae0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087F160 size 32
public ?d_0087f160@@YAXXZ
?d_0087f160@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 0E8h, 05h, 18h, 0FDh, 0FFh, 50h, 0E8h, 0DFh, 33h, 0FDh
    db 0FFh, 8Bh, 4Ch, 24h, 10h, 83h, 0C4h, 04h, 88h, 41h, 04h, 0E9h, 0E0h, 0FCh, 0FFh, 0FFh
?d_0087f160@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0087F220 size 68
public ?d_0087f220@@YAXXZ
?d_0087f220@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 10h, 8Bh, 56h, 2Ch, 8Bh, 4Eh, 30h, 2Bh, 0CAh, 0B8h, 39h, 8Eh
    db 0E3h, 38h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 74h, 1Ch
    db 8Bh, 4Ch, 24h, 08h, 57h, 8Bh, 7Eh, 30h, 6Ah, 00h, 0E8h, 21h, 17h, 0FDh, 0FFh, 50h
    db 0E8h, 8Bh, 34h, 0FDh, 0FFh, 0D9h, 5Fh, 0E8h, 83h, 0C4h, 04h, 5Fh, 8Bh, 0CEh, 5Eh, 0E9h
    db 0FCh, 0FBh, 0FFh, 0FFh
?d_0087f220@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00880480 size 95
public ?d_00880480@@YAXXZ
?d_00880480@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 53h, 56h, 57h, 68h, 0D8h, 4Ch, 2Dh, 01h, 33h, 0F6h, 56h, 0E8h
    db 0DCh, 04h, 0FDh, 0FFh, 50h, 0E8h, 46h, 05h, 0FDh, 0FFh, 8Bh, 5Ch, 24h, 20h, 83h, 0ECh
    db 1Ch, 0B9h, 00h, 00h, 80h, 3Fh, 8Bh, 0F8h, 8Bh, 0C4h, 89h, 30h, 89h, 48h, 04h, 89h
    db 48h, 08h, 89h, 48h, 0Ch, 89h, 70h, 10h, 89h, 70h, 14h, 89h, 70h, 18h, 89h, 70h
    db 1Ch, 8Dh, 73h, 2Ch, 6Ah, 01h, 8Bh, 0CEh, 0C6h, 40h, 20h, 01h, 0E8h, 8Fh, 0FDh, 0FFh
    db 0FFh, 8Bh, 06h, 89h, 38h, 8Bh, 0CBh, 5Fh, 5Eh, 5Bh, 0E9h, 81h, 0E9h, 0FFh, 0FFh
?d_00880480@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00880E00 size 8
public ?d_00880e00@@YAXXZ
?d_00880e00@@YAXXZ PROC
    db 8Bh, 49h, 0Ch, 0E9h, 0C8h, 03h, 00h, 00h
?d_00880e00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00880FB0 size 6
public ?d_00880fb0@@YAXXZ
?d_00880fb0@@YAXXZ PROC
    db 0B8h, 78h, 2Bh, 13h, 01h, 0C3h
?d_00880fb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00881040 size 46
public ?d_00881040@@YAXXZ
?d_00881040@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 0B0h, 01h, 8Dh, 4Ch, 24h, 08h, 88h
    db 44h, 24h, 08h, 88h, 44h, 24h, 09h, 8Bh, 06h, 51h, 8Bh, 0CEh, 0FFh, 50h, 28h, 8Bh
    db 4Fh, 04h, 56h, 0E8h, 38h, 05h, 00h, 00h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00881040@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008812D0 size 50
public ?d_008812d0@@YAXXZ
?d_008812d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 7Ch, 23h, 8Bh, 41h, 20h, 3Bh, 0F0h, 7Dh, 1Ch
    db 8Bh, 54h, 24h, 0Ch, 85h, 0D2h, 7Ch, 14h, 3Bh, 51h, 24h, 7Dh, 0Fh, 8Bh, 49h, 28h
    db 0Fh, 0AFh, 0C2h, 03h, 0C6h, 8Dh, 04h, 0C1h, 5Eh, 0C2h, 08h, 00h, 33h, 0C0h, 5Eh, 0C2h
    db 08h, 00h
?d_008812d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00881460 size 57
public ?d_00881460@@YAXXZ
?d_00881460@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 7Ch, 2Ah, 8Bh, 41h, 20h, 3Bh, 0F0h, 7Dh, 23h
    db 8Bh, 54h, 24h, 0Ch, 85h, 0D2h, 7Ch, 1Bh, 3Bh, 51h, 24h, 7Dh, 16h, 8Bh, 49h, 28h
    db 0Fh, 0AFh, 0C2h, 03h, 0C6h, 8Dh, 04h, 0C1h, 85h, 0C0h, 74h, 07h, 8Bh, 40h, 04h, 5Eh
    db 0C2h, 08h, 00h, 33h, 0C0h, 5Eh, 0C2h, 08h, 00h
?d_00881460@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00882E10 size 125
public ?d_00882e10@@YAXXZ
?d_00882e10@@YAXXZ PROC
    db 56h, 57h, 6Ah, 00h, 0FFh, 15h, 0C8h, 8Dh, 35h, 01h, 8Bh, 3Dh, 0D8h, 8Dh, 35h, 01h
    db 8Bh, 0F0h, 68h, 0ACh, 2Dh, 13h, 01h, 56h, 0FFh, 0D7h, 68h, 90h, 2Dh, 13h, 01h, 56h
    db 0A3h, 0A8h, 0E9h, 30h, 01h, 0FFh, 0D7h, 68h, 60h, 2Dh, 13h, 01h, 56h, 0A3h, 0A4h, 0E9h
    db 30h, 01h, 0FFh, 0D7h, 68h, 2Ch, 2Dh, 13h, 01h, 56h, 0A3h, 0B4h, 0E9h, 30h, 01h, 0FFh
    db 0D7h, 68h, 00h, 2Dh, 13h, 01h, 56h, 0A3h, 0A0h, 0E9h, 30h, 01h, 0FFh, 0D7h, 68h, 0D8h
    db 2Ch, 13h, 01h, 56h, 0A3h, 0ACh, 0E9h, 30h, 01h, 0FFh, 0D7h, 68h, 0B4h, 2Ch, 13h, 01h
    db 56h, 0A3h, 9Ch, 0E9h, 30h, 01h, 0FFh, 0D7h, 68h, 90h, 2Ch, 13h, 01h, 56h, 0A3h, 0B0h
    db 0E9h, 30h, 01h, 0FFh, 0D7h, 5Fh, 0A3h, 98h, 0E9h, 30h, 01h, 5Eh, 0C3h
?d_00882e10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00883160 size 161
public ?d_00883160@@YAXXZ
?d_00883160@@YAXXZ PROC
    db 81h, 0ECh, 00h, 02h, 00h, 00h, 53h, 8Bh, 9Ch, 24h, 0Ch, 02h, 00h, 00h, 8Bh, 03h
    db 85h, 0C0h, 56h, 74h, 5Eh, 33h, 0F6h, 85h, 0C0h, 76h, 76h, 57h, 8Bh, 0BCh, 24h, 10h
    db 02h, 00h, 00h, 8Bh, 4Bh, 04h, 8Bh, 14h, 0B1h, 68h, 00h, 02h, 00h, 00h, 8Dh, 44h
    db 24h, 10h, 50h, 52h, 0E8h, 47h, 95h, 00h, 00h, 8Bh, 07h, 83h, 0C4h, 0Ch, 68h, 0E8h
    db 2Dh, 13h, 01h, 8Bh, 0CFh, 0FFh, 50h, 38h, 8Bh, 10h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh
    db 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 68h, 94h, 02h, 08h, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h
    db 8Bh, 03h, 46h, 3Bh, 0F0h, 72h, 0BCh, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 81h, 0C4h, 00h, 02h
    db 00h, 00h, 0C3h, 8Bh, 0B4h, 24h, 0Ch, 02h, 00h, 00h, 8Bh, 06h, 68h, 0D8h, 2Dh, 13h
    db 01h, 8Bh, 0CEh, 0FFh, 50h, 38h, 8Bh, 0C6h, 5Eh, 5Bh, 81h, 0C4h, 00h, 02h, 00h, 00h
    db 0C3h, 8Bh, 84h, 24h, 0Ch, 02h, 00h, 00h, 5Eh, 5Bh, 81h, 0C4h, 00h, 02h, 00h, 00h
    db 0C3h
?d_00883160@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008835C0 size 294
_TEXT ENDS
_TEXT$d00c835c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C835C0 size 294
public ?d_008835c0@@YAXXZ
?d_008835c0@@YAXXZ PROC
    db 081h, 0ECh, 000h, 002h, 000h, 000h, 053h, 08Bh, 09Ch, 024h, 008h, 002h, 000h, 000h, 08Ah, 083h
    db 0C0h, 082h, 002h, 000h, 084h, 0C0h, 00Fh, 085h, 002h, 001h, 000h, 000h, 08Bh, 083h, 0C8h, 082h
    db 002h, 000h, 085h, 0C0h, 074h, 007h, 050h, 0FFh, 015h
    dd __imp__EnterCriticalSection@4
    db 056h, 08Bh, 0B4h, 024h, 010h, 002h, 000h, 000h, 033h, 0D2h, 0B9h, 07Bh, 02Bh, 000h, 000h, 08Bh
    db 0C6h, 0F7h, 0F1h, 08Bh, 044h, 093h, 00Ch, 085h, 0C0h, 08Dh, 04Ch, 093h, 00Ch, 074h, 011h, 08Dh
    db 064h, 024h, 000h, 039h, 070h, 008h, 074h, 008h, 08Bh, 0C8h, 08Bh, 001h, 085h, 0C0h, 075h, 0F3h
    db 057h, 08Bh, 039h, 085h, 0FFh, 00Fh, 084h, 0A3h, 000h, 000h, 000h, 08Bh, 087h, 09Ch, 000h, 000h
    db 000h, 085h, 0C0h, 00Fh, 08Dh, 095h, 000h, 000h, 000h, 08Bh, 047h, 014h, 085h, 0C0h, 055h, 08Bh
    db 02Dh
    dd __imp__GetProcessHeap@0
    db 074h, 00Ch, 050h, 06Ah, 004h, 0FFh, 0D5h, 050h, 0FFh, 015h
    dd __imp__HeapFree@12
    db 08Bh, 084h, 024h, 01Ch, 002h, 000h, 000h, 085h, 0C0h, 074h, 068h, 08Dh, 094h, 024h, 020h, 002h
    db 000h, 000h, 052h, 050h, 08Dh, 044h, 024h, 018h, 068h, 000h, 002h, 000h, 000h, 050h, 0FFh, 015h
    dd __imp_?i_009f6ec0@@YAXXZ
    db 083h, 0C4h, 010h, 085h, 0C0h, 07Dh, 008h, 0C6h, 084h, 024h, 00Fh, 002h, 000h, 000h, 000h, 08Dh
    db 044h, 024h, 010h, 08Dh, 050h, 001h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Ah, 008h, 040h, 084h
    db 0C9h, 075h, 0F9h, 02Bh, 0C2h, 08Dh, 070h, 001h, 056h, 06Ah, 004h, 0FFh, 0D5h, 050h, 0FFh, 015h
    dd __imp__HeapAlloc@12
    db 08Bh, 0CEh, 08Bh, 0D1h, 089h, 047h, 014h, 0C1h, 0E9h, 002h, 08Dh, 074h, 024h, 010h, 08Bh, 0F8h
    db 0F3h, 0A5h, 08Bh, 0CAh, 083h, 0E1h, 003h, 0F3h, 0A4h, 0EBh, 007h, 0C7h, 047h, 014h, 000h, 000h
    db 000h, 000h, 05Dh, 08Bh, 083h, 0C8h, 082h, 002h, 000h, 085h, 0C0h, 074h, 007h, 050h, 0FFh, 015h
    dd __imp__LeaveCriticalSection@4
    db 05Fh, 05Eh, 05Bh, 081h, 0C4h, 000h, 002h, 000h, 000h, 0C3h
?d_008835c0@@YAXXZ ENDP
_TEXT$d00c835c0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x008838F0 size 181
public ?d_008838f0@@YAXXZ
?d_008838f0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 10h, 85h, 0EDh, 57h, 8Bh, 0D9h, 0Fh, 84h, 9Ch, 00h, 00h
    db 00h, 8Bh, 7Ch, 24h, 18h, 85h, 0FFh, 0Fh, 84h, 90h, 00h, 00h, 00h, 8Ah, 83h, 0C0h
    db 82h, 02h, 00h, 84h, 0C0h, 0Fh, 85h, 82h, 00h, 00h, 00h, 8Bh, 83h, 0C8h, 82h, 02h
    db 00h, 85h, 0C0h, 74h, 07h, 50h, 0FFh, 15h, 18h, 8Dh, 35h, 01h, 56h, 8Bh, 74h, 24h
    db 14h, 33h, 0D2h, 0B9h, 7Bh, 2Bh, 00h, 00h, 8Bh, 0C6h, 0F7h, 0F1h, 8Bh, 44h, 93h, 0Ch
    db 85h, 0C0h, 8Dh, 4Ch, 93h, 0Ch, 74h, 0Dh, 39h, 70h, 08h, 74h, 08h, 8Bh, 0C8h, 8Bh
    db 01h, 85h, 0C0h, 75h, 0F3h, 8Bh, 09h, 85h, 0C9h, 75h, 09h, 5Eh, 5Fh, 5Dh, 33h, 0C0h
    db 5Bh, 0C2h, 0Ch, 00h, 33h, 0F6h, 85h, 0FFh, 76h, 19h, 8Dh, 41h, 1Ch, 8Dh, 49h, 00h
    db 3Bh, 71h, 18h, 73h, 0Eh, 8Bh, 10h, 89h, 54h, 0B5h, 00h, 46h, 83h, 0C0h, 04h, 3Bh
    db 0F7h, 72h, 0EDh, 8Bh, 83h, 0C8h, 82h, 02h, 00h, 85h, 0C0h, 74h, 07h, 50h, 0FFh, 15h
    db 74h, 8Eh, 35h, 01h, 8Bh, 0C6h, 5Eh, 5Fh, 5Dh, 5Bh, 0C2h, 0Ch, 00h, 5Fh, 5Dh, 33h
    db 0C0h, 5Bh, 0C2h, 0Ch, 00h
?d_008838f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00884EC0 size 1065
_TEXT ENDS
_TEXT$d00c84ec0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C84EC0 size 1065
public ?d_00884ec0@@YAXXZ
?d_00884ec0@@YAXXZ PROC
    db 0A1h
    dd g_Va01336CEC
    db 083h, 0ECh, 028h, 056h, 057h, 033h, 0FFh, 03Bh, 0C7h, 08Bh, 0F1h, 074h, 00Bh, 05Fh, 0B8h, 004h
    db 000h, 004h, 080h, 05Eh, 083h, 0C4h, 028h, 0C3h, 08Bh, 08Eh, 084h, 005h, 000h, 000h, 0B8h, 001h
    db 000h, 000h, 000h, 03Bh, 0C8h, 0A3h
    dd g_Va01336CEC
    db 075h, 017h, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h, 08Bh, 001h, 06Ah, 002h, 0FFh, 050h, 010h, 0C7h
    db 086h, 084h, 005h, 000h, 000h, 002h, 000h, 000h, 000h, 08Bh, 096h, 084h, 005h, 000h, 000h, 083h
    db 0FAh, 002h, 075h, 051h, 08Dh, 04Eh, 004h, 051h, 08Bh, 08Eh, 0C0h, 005h, 000h, 000h
    call ?ConnectToServer@Rva00884Ftp@@QAEJPBD@Z
    db 03Bh, 0C7h, 075h, 018h, 0C7h, 086h, 084h, 005h, 000h, 000h, 003h, 000h, 000h, 000h, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 033h, 0C0h, 05Eh, 083h, 0C4h, 028h, 0C3h, 03Dh, 001h, 000h, 004h, 080h, 075h, 0EBh, 08Bh
    db 0B6h, 0C4h, 005h, 000h, 000h, 08Bh, 016h, 06Ah, 002h, 08Bh, 0CEh, 0FFh, 012h, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 0B8h, 003h, 000h, 004h, 080h, 05Eh, 083h, 0C4h, 028h, 0C3h, 083h, 0FAh, 003h, 075h, 06Ch
    db 08Dh, 086h, 044h, 001h, 000h, 000h, 050h, 08Dh, 08Eh, 004h, 001h, 000h, 000h, 051h, 08Bh, 08Eh
    db 0C0h, 005h, 000h, 000h
    call ?LoginToServer@Cftp@@QAEJPBD0@Z
    db 03Bh, 0C7h, 075h, 025h, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h, 08Bh, 011h, 06Ah, 004h, 0FFh, 052h
    db 010h, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 0C7h, 086h, 084h, 005h, 000h, 000h, 004h, 000h, 000h, 000h, 033h, 0C0h, 05Eh, 083h, 0C4h
    db 028h, 0C3h, 03Dh, 001h, 000h, 004h, 080h, 00Fh, 085h, 07Ah, 0FFh, 0FFh, 0FFh, 08Bh, 0B6h, 0C4h
    db 005h, 000h, 000h, 08Bh, 006h, 06Ah, 003h, 08Bh, 0CEh, 0FFh, 010h, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 0B8h, 003h, 000h, 004h, 080h, 05Eh, 083h, 0C4h, 028h, 0C3h, 083h, 0FAh, 004h, 053h, 055h
    db 00Fh, 085h, 069h, 001h, 000h, 000h, 08Dh, 086h, 084h, 001h, 000h, 000h, 08Dh, 058h, 001h, 08Dh
    db 0A4h, 024h, 000h, 000h, 000h, 000h, 08Ah, 008h, 040h, 084h, 0C9h, 075h, 0F9h, 02Bh, 0C3h, 089h
    db 044h, 024h, 010h, 00Fh, 084h, 046h, 001h, 000h, 000h, 08Bh, 08Eh, 0C0h, 005h, 000h, 000h, 08Dh
    db 0AEh, 090h, 005h, 000h, 000h, 055h, 08Dh, 086h, 084h, 001h, 000h, 000h, 050h
    call ?d_00886020@@YAXXZ
    db 03Dh, 001h, 000h, 004h, 080h, 075h, 021h, 08Bh, 0B6h, 0C4h, 005h, 000h, 000h, 08Bh, 016h, 06Ah
    db 004h, 08Bh, 0CEh, 0FFh, 012h, 05Dh, 05Bh, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 0B8h, 004h, 000h, 004h, 080h, 05Eh, 083h, 0C4h, 028h, 0C3h, 039h, 07Dh, 000h, 00Fh, 08Eh
    db 08Ch, 002h, 000h, 000h, 08Dh, 044h, 024h, 014h, 050h, 08Dh, 0BEh, 084h, 002h, 000h, 000h, 057h
    db 0FFh, 015h
    dd __imp___stat
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 062h, 08Bh, 04Ch, 024h, 028h, 03Bh, 04Dh, 000h, 075h, 059h
    db 06Ah, 008h, 068h
    dd g_Va010FE3C8
    db 057h, 0FFh, 015h
    dd __imp___strnicmp
    db 083h, 0C4h, 00Ch, 085h, 0C0h, 075h, 044h, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h, 033h, 0DBh, 0C7h
    db 086h, 084h, 005h, 000h, 000h, 004h, 000h, 000h, 000h, 089h, 09Eh, 088h, 005h, 000h, 000h, 089h
    db 09Eh, 08Ch, 005h, 000h, 000h, 089h, 05Dh, 000h, 089h, 09Eh, 094h, 005h, 000h, 000h, 088h, 09Eh
    db 084h, 001h, 000h, 000h, 088h, 01Fh, 08Bh, 011h, 0FFh, 052h, 004h, 05Dh, 089h, 01Dh
    dd g_Va01336CEC
    db 05Bh, 05Fh, 033h, 0C0h, 05Eh, 083h, 0C4h, 028h, 0C3h, 08Ah, 086h, 098h, 005h, 000h, 000h, 084h
    db 0C0h, 075h, 00Ch, 0C7h, 086h, 08Ch, 005h, 000h, 000h, 000h, 000h, 000h, 000h, 0EBh, 040h, 08Bh
    db 08Eh, 0C0h, 005h, 000h, 000h, 08Dh, 086h, 084h, 004h, 000h, 000h, 050h, 057h
    call ?d_00886a20@Rva00886A20Class@@QAEHPBDH@Z
    db 085h, 0C0h, 089h, 086h, 08Ch, 005h, 000h, 000h, 074h, 023h, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h
    db 08Bh, 011h, 0FFh, 052h, 008h, 03Dh, 006h, 000h, 004h, 080h, 075h, 011h, 08Bh, 08Eh, 0C0h, 005h
    db 000h, 000h, 033h, 0C0h, 089h, 041h, 02Ch, 089h, 086h, 08Ch, 005h, 000h, 000h, 0C7h, 086h, 084h
    db 005h, 000h, 000h, 006h, 000h, 000h, 000h, 08Bh, 0B6h, 0C4h, 005h, 000h, 000h, 08Bh, 016h, 06Ah
    db 006h, 08Bh, 0CEh, 0FFh, 052h, 010h, 05Dh, 033h, 0FFh, 05Bh, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 033h, 0C0h, 05Eh, 083h, 0C4h, 028h, 0C3h, 083h, 0FAh, 006h, 00Fh, 085h, 037h, 001h, 000h
    db 000h, 08Bh, 08Eh, 0C0h, 005h, 000h, 000h, 08Dh, 09Eh, 094h, 005h, 000h, 000h, 053h, 08Dh, 086h
    db 084h, 002h, 000h, 000h, 050h
    call ?GetNextFileBlock@Cftp@@QAEJPBDPAH@Z
    db 08Bh, 0E8h, 039h, 0BEh, 088h, 005h, 000h, 000h, 08Bh, 03Dh
    dd __imp__timeGetTime@0
    db 075h, 008h, 0FFh, 0D7h, 089h, 086h, 088h, 005h, 000h, 000h, 085h, 0EDh, 00Fh, 085h, 0B2h, 000h
    db 000h, 000h, 0C7h, 086h, 084h, 005h, 000h, 000h, 008h, 000h, 000h, 000h, 0FFh, 0D7h, 08Bh, 096h
    db 088h, 005h, 000h, 000h, 08Bh, 0BEh, 08Ch, 005h, 000h, 000h, 08Bh, 0C8h, 02Bh, 0CAh, 0B8h, 0D3h
    db 04Dh, 062h, 010h, 0F7h, 0E1h, 08Bh, 0EAh, 08Bh, 013h, 08Bh, 0C2h, 02Bh, 0C7h, 0C1h, 0EDh, 006h
    db 085h, 0C0h, 00Fh, 08Eh, 0ABh, 000h, 000h, 000h, 08Bh, 08Eh, 09Ch, 005h, 000h, 000h, 050h, 08Bh
    db 086h, 090h, 005h, 000h, 000h, 08Bh, 0F9h, 02Bh, 0C2h, 050h, 083h, 0E7h, 007h, 041h, 055h, 089h
    db 08Eh, 09Ch, 005h, 000h, 000h, 0FFh, 015h
    dd g_Va01358E9C
    db 089h, 084h, 0BEh, 0A0h, 005h, 000h, 000h, 083h, 0BEh, 09Ch, 005h, 000h, 000h, 008h, 07Eh, 078h
    db 08Bh, 096h, 0B8h, 005h, 000h, 000h, 08Bh, 086h, 0BCh, 005h, 000h, 000h, 08Bh, 08Eh, 0B4h, 005h
    db 000h, 000h, 08Bh, 0BEh, 0B0h, 005h, 000h, 000h, 003h, 0C2h, 08Bh, 096h, 0ACh, 005h, 000h, 000h
    db 003h, 0C1h, 08Bh, 08Eh, 0A8h, 005h, 000h, 000h, 003h, 0C7h, 08Bh, 0BEh, 0A4h, 005h, 000h, 000h
    db 003h, 0C2h, 08Bh, 096h, 0A0h, 005h, 000h, 000h, 003h, 0C1h, 003h, 0C7h, 003h, 0C2h, 099h, 083h
    db 0E2h, 007h, 003h, 0C2h, 0C1h, 0F8h, 003h, 0EBh, 032h, 081h, 0FDh, 001h, 000h, 004h, 080h, 00Fh
    db 085h, 04Ch, 0FFh, 0FFh, 0FFh, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h, 08Bh, 011h, 06Ah, 006h, 0FFh
    db 012h, 05Dh, 05Bh, 05Fh, 0C7h, 005h
    dd g_Va01336CEC
    db 000h, 000h, 000h, 000h, 0B8h, 003h, 000h, 004h, 080h, 05Eh, 083h, 0C4h, 028h, 0C3h, 083h, 0C8h
    db 0FFh, 08Bh, 08Eh, 0C4h, 005h, 000h, 000h, 08Bh, 011h, 040h, 050h, 08Bh, 086h, 090h, 005h, 000h
    db 000h, 055h, 050h, 08Bh, 003h, 050h, 0FFh, 052h, 00Ch, 033h, 0FFh, 083h, 0BEh, 084h, 005h, 000h
    db 000h, 008h, 075h, 047h, 08Bh, 08Eh, 0C0h, 005h, 000h, 000h, 08Bh, 051h, 004h, 08Bh, 08Eh, 0C4h
    db 005h, 000h, 000h, 0F7h, 0DAh, 01Bh, 0D2h, 083h, 0E2h, 004h, 089h, 096h, 084h, 005h, 000h, 000h
    db 089h, 0BEh, 088h, 005h, 000h, 000h, 089h, 0BEh, 08Ch, 005h, 000h, 000h, 089h, 0BEh, 090h, 005h
    db 000h, 000h, 089h, 0BEh, 094h, 005h, 000h, 000h, 0C6h, 086h, 084h, 001h, 000h, 000h, 000h, 0C6h
    db 086h, 084h, 002h, 000h, 000h, 000h, 08Bh, 001h, 0FFh, 050h, 004h, 05Dh, 05Bh, 089h, 03Dh
    dd g_Va01336CEC
    db 05Fh, 033h, 0C0h, 05Eh, 083h, 0C4h, 028h, 0C3h
?d_00884ec0@@YAXXZ ENDP
_TEXT$d00c84ec0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x00887260 size 42
public ?d_00887260@@YAXXZ
?d_00887260@@YAXXZ PROC
    db 56h, 8Bh, 0F0h, 8Ah, 06h, 84h, 0C0h, 74h, 1Dh, 57h, 8Bh, 3Dh, 20h, 94h, 35h, 01h
    db 0Fh, 0BEh, 0C0h, 50h, 0FFh, 0D7h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 08h, 8Ah, 46h, 01h
    db 46h, 84h, 0C0h, 75h, 0EBh, 5Fh, 8Bh, 0C6h, 5Eh, 0C3h
?d_00887260@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00889250 size 31
public ?d_00889250@@YAXXZ
?d_00889250@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 34h, 30h, 13h, 01h, 74h, 09h
    db 56h, 0E8h, 4Ah, 8Ch, 0FFh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00889250@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00889290 size 50
public ?d_00889290@@YAXXZ
?d_00889290@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 33h, 0D2h, 8Bh, 0C6h, 0BFh, 17h, 27h, 00h, 00h, 0F7h
    db 0F7h, 8Bh, 44h, 91h, 18h, 85h, 0C0h, 74h, 12h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 39h, 70h, 04h, 74h, 08h, 8Bh, 00h, 85h, 0C0h, 75h, 0F5h, 33h, 0C0h, 5Fh, 5Eh, 0C2h
    db 04h, 00h
?d_00889290@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008896E0 size 27
public ?d_008896e0@@YAXXZ
?d_008896e0@@YAXXZ PROC
    db 81h, 0C1h, 0F8h, 9Dh, 00h, 00h, 51h, 0FFh, 15h, 5Ch, 8Eh, 35h, 01h, 68h, 60h, 6Eh
    db 33h, 01h, 0FFh, 15h, 18h, 8Dh, 35h, 01h, 32h, 0C0h, 0C3h
?d_008896e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00889BE0 size 7
public ?d_00889be0@@YAXXZ
?d_00889be0@@YAXXZ PROC
    db 8Ah, 81h, 58h, 9Fh, 00h, 00h, 0C3h
?d_00889be0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0088F930 size 31
public ?d_0088f930@@YAXXZ
?d_0088f930@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 44h, 50h, 13h, 01h, 74h, 09h
    db 56h, 0E8h, 6Ah, 25h, 0FFh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_0088f930@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0088F9E0 size 5
public ?d_0088f9e0@@YAXXZ
?d_0088f9e0@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 08h, 00h
?d_0088f9e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00890410 size 5
public ?d_00890410@@YAXXZ
?d_00890410@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 08h, 00h
?d_00890410@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00890F70 size 9
public ?d_00890f70@@YAXXZ
?d_00890f70@@YAXXZ PROC
    db 8Ah, 41h, 04h, 84h, 0C0h, 0Fh, 95h, 0C0h, 0C3h
?d_00890f70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00891880 size 5
public ?d_00891880@@YAXXZ
?d_00891880@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 08h, 00h
?d_00891880@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00891890 size 5
public ?d_00891890@@YAXXZ
?d_00891890@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 0Ch, 00h
?d_00891890@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008918A0 size 12
public ?d_008918a0@@YAXXZ
?d_008918a0@@YAXXZ PROC
    db 85h, 0C9h, 74h, 07h, 8Bh, 01h, 6Ah, 01h, 0FFh, 50h, 34h, 0C3h
?d_008918a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00891BA0 size 47
public ?d_00891ba0@@YAXXZ
?d_00891ba0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 66h, 0FFh, 00h, 8Bh, 0F1h, 8Bh, 06h, 66h
    db 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h, 01h, 0FFh, 50h
    db 04h, 83h, 0C4h, 04h, 8Bh, 0Fh, 5Fh, 89h, 0Eh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00891ba0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00892500 size 18
public ?d_00892500@@YAXXZ
?d_00892500@@YAXXZ PROC
    db 56h, 8Bh, 71h, 08h, 8Dh, 41h, 0Ch, 33h, 0D2h, 3Bh, 0F0h, 0Fh, 94h, 0C2h, 8Ah, 0C2h
    db 5Eh, 0C3h
?d_00892500@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00892550 size 18
public ?d_00892550@@YAXXZ
?d_00892550@@YAXXZ PROC
    db 56h, 8Bh, 71h, 08h, 8Dh, 41h, 0Ch, 33h, 0D2h, 3Bh, 0F0h, 0Fh, 94h, 0C2h, 8Ah, 0C2h
    db 5Eh, 0C3h
?d_00892550@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008928B0 size 31
public ?d_008928b0@@YAXXZ
?d_008928b0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 68h, 5Dh, 13h, 01h, 74h, 09h
    db 56h, 0E8h, 0EAh, 0F5h, 0FEh, 0FFh, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_008928b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00892CD0 size 111
public ?d_00892cd0@@YAXXZ
?d_00892cd0@@YAXXZ PROC
    db 53h, 8Ah, 5Ch, 24h, 08h, 0F6h, 0C3h, 02h, 56h, 8Bh, 0F1h, 74h, 2Ch, 8Bh, 46h, 0FCh
    db 57h, 68h, 0ADh, 63h, 44h, 00h, 8Dh, 7Eh, 0FCh, 50h, 6Ah, 04h, 56h, 0E8h, 84h, 40h
    db 16h, 00h, 0F6h, 0C3h, 01h, 74h, 0Ah, 57h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 83h, 0C4h
    db 04h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h, 8Bh, 06h, 85h, 0C0h, 74h, 18h, 50h
    db 0E8h, 7Bh, 20h, 00h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 0Bh, 8Bh, 0Eh, 51h, 0E8h
    db 0FCh, 25h, 00h, 00h, 83h, 0C4h, 04h, 0F6h, 0C3h, 01h, 74h, 0Ch, 6Ah, 04h, 56h, 0FFh
    db 15h, 30h, 78h, 33h, 01h, 83h, 0C4h, 08h, 8Bh, 0C6h, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_00892cd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00892E90 size 32
public ?d_00892e90@@YAXXZ
?d_00892e90@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 33h, 0C0h, 85h, 0D2h, 8Bh, 51h, 60h, 0Fh, 95h, 0C0h, 0C1h, 0E0h
    db 11h, 33h, 0C2h, 25h, 00h, 00h, 02h, 00h, 33h, 0D0h, 89h, 51h, 60h, 0C2h, 04h, 00h
?d_00892e90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00893230 size 53
public ?d_00893230@@YAXXZ
?d_00893230@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 85h, 0F6h, 74h, 0Ah, 83h, 7Eh, 08h, 04h, 75h, 04h
    db 0B3h, 01h, 0EBh, 02h, 32h, 0DBh, 85h, 0F6h, 74h, 16h, 56h, 0E8h, 40h, 1Bh, 00h, 00h
    db 83h, 0C4h, 04h, 85h, 0C0h, 75h, 09h, 56h, 0E8h, 0C3h, 20h, 00h, 00h, 83h, 0C4h, 04h
    db 5Eh, 8Ah, 0C3h, 5Bh, 0C3h
?d_00893230@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008940E0 size 46
public ?d_008940e0@@YAXXZ
?d_008940e0@@YAXXZ PROC
    db 56h, 68h, 90h, 28h, 0C9h, 00h, 68h, 70h, 28h, 0C9h, 00h, 8Bh, 0F1h, 6Ah, 02h, 8Dh
    db 46h, 0Ch, 6Ah, 08h, 50h, 0C7h, 06h, 00h, 00h, 00h, 00h, 0C7h, 46h, 04h, 00h, 00h
    db 00h, 00h, 89h, 46h, 08h, 0E8h, 0DAh, 2Dh, 16h, 00h, 8Bh, 0C6h, 5Eh, 0C3h
?d_008940e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00894FB0 size 57
public ?d_00894fb0@@YAXXZ
?d_00894fb0@@YAXXZ PROC
    db 56h, 6Ah, 08h, 8Bh, 0F1h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 85h, 0C0h
    db 74h, 1Ah, 8Bh, 4Ch, 24h, 08h, 8Bh, 11h, 89h, 10h, 0C7h, 40h, 04h, 00h, 00h, 00h
    db 00h, 8Bh, 0Eh, 89h, 48h, 04h, 89h, 06h, 5Eh, 0C2h, 04h, 00h, 8Bh, 0Eh, 33h, 0C0h
    db 89h, 48h, 04h, 89h, 06h, 5Eh, 0C2h, 04h, 00h
?d_00894fb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008991E0 size 120
_TEXT ENDS
_TEXT$d00c991e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00C991E0 size 120
public ?d_008991e0@@YAXXZ
?d_008991e0@@YAXXZ PROC
    db 033h, 0C0h, 066h, 08Bh, 041h, 006h, 056h, 025h, 0FFh, 00Fh, 000h, 000h, 048h, 03Dh, 0FFh, 00Fh
    db 000h, 000h, 08Bh, 0F0h, 076h, 005h, 0BEh, 0FFh, 00Fh, 000h, 000h, 08Bh, 051h, 004h, 081h, 0E2h
    db 0FFh, 0FFh, 000h, 0F0h, 0C1h, 0E6h, 010h, 00Bh, 0D6h, 085h, 0C0h, 089h, 051h, 004h, 075h, 02Fh
    db 08Bh, 0C2h, 0C1h, 0E8h, 01Eh, 0A8h, 001h, 075h, 026h, 081h, 0CAh, 000h, 000h, 000h, 040h, 089h
    db 051h, 004h, 0A1h
    dd ?g_bfme1211@@3PAVBfmeG1211@@A
    db 08Bh, 070h, 004h, 057h, 08Bh, 038h, 03Bh, 0F7h, 07Dh, 020h, 03Bh, 0F7h, 07Ch, 00Ch, 081h, 0E2h
    db 0FFh, 0FFh, 0FFh, 0BFh, 089h, 051h, 004h, 05Fh, 05Eh, 0C3h, 08Bh, 050h, 008h, 089h, 00Ch, 0B2h
    db 08Bh, 048h, 004h, 041h, 05Fh, 089h, 048h, 004h, 05Eh, 0C3h, 08Bh, 001h, 05Fh, 05Eh, 0FFh, 060h
    db 008h
?d_008991e0@@YAXXZ ENDP
_TEXT$d00c991e0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x008994B0 size 20
public ?d_008994b0@@YAXXZ
?d_008994b0@@YAXXZ PROC
    db 8Bh, 41h, 1Ch, 8Bh, 54h, 24h, 04h, 25h, 0FFh, 00h, 00h, 00h, 89h, 02h, 8Bh, 41h
    db 18h, 0C2h, 04h, 00h
?d_008994b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008994D0 size 45
public ?d_008994d0@@YAXXZ
?d_008994d0@@YAXXZ PROC
    db 8Bh, 51h, 1Ch, 56h, 33h, 0C0h, 81h, 0E2h, 0FFh, 00h, 00h, 00h, 76h, 13h, 8Bh, 49h
    db 18h, 8Bh, 74h, 24h, 08h, 39h, 31h, 74h, 0Eh, 40h, 83h, 0C1h, 04h, 3Bh, 0C2h, 72h
    db 0F4h, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_008994d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00899660 size 5
public ?d_00899660@@YAXXZ
?d_00899660@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_00899660@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00899D70 size 10
public ?d_00899d70@@YAXXZ
?d_00899d70@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E8h, 98h, 2Eh, 00h, 00h, 40h, 0C3h
?d_00899d70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00899D80 size 27
public ?d_00899d80@@YAXXZ
?d_00899d80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 06h, 8Bh, 41h, 18h, 0C2h, 04h, 00h, 48h, 89h
    db 44h, 24h, 04h, 83h, 0C1h, 08h, 0E9h, 95h, 2Eh, 00h, 00h
?d_00899d80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A100 size 5
public ?d_0089a100@@YAXXZ
?d_0089a100@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_0089a100@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A1E0 size 5
public ?d_0089a1e0@@YAXXZ
?d_0089a1e0@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_0089a1e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A380 size 8
public ?d_0089a380@@YAXXZ
?d_0089a380@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0F8h, 24h, 00h, 00h
?d_0089a380@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A3C0 size 8
public ?d_0089a3c0@@YAXXZ
?d_0089a3c0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 48h, 28h, 00h, 00h
?d_0089a3c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A3D0 size 8
public ?d_0089a3d0@@YAXXZ
?d_0089a3d0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 58h, 28h, 00h, 00h
?d_0089a3d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A460 size 38
public ?d_0089a460@@YAXXZ
?d_0089a460@@YAXXZ PROC
    db 56h, 6Ah, 08h, 6Ah, 18h, 8Bh, 0F1h, 0E8h, 94h, 0FAh, 0FFh, 0FFh, 8Bh, 46h, 04h, 25h
    db 7Fh, 0C0h, 0FFh, 0FFh, 0Dh, 40h, 00h, 0FFh, 0Fh, 89h, 46h, 04h, 0C7h, 06h, 38h, 62h
    db 13h, 01h, 8Bh, 0C6h, 5Eh, 0C3h
?d_0089a460@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A600 size 8
public ?d_0089a600@@YAXXZ
?d_0089a600@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 78h, 22h, 00h, 00h
?d_0089a600@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A640 size 8
public ?d_0089a640@@YAXXZ
?d_0089a640@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0C8h, 25h, 00h, 00h
?d_0089a640@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A650 size 8
public ?d_0089a650@@YAXXZ
?d_0089a650@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0D8h, 25h, 00h, 00h
?d_0089a650@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A7A0 size 8
public ?d_0089a7a0@@YAXXZ
?d_0089a7a0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0D8h, 20h, 00h, 00h
?d_0089a7a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A7E0 size 8
public ?d_0089a7e0@@YAXXZ
?d_0089a7e0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 28h, 24h, 00h, 00h
?d_0089a7e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A7F0 size 8
public ?d_0089a7f0@@YAXXZ
?d_0089a7f0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 38h, 24h, 00h, 00h
?d_0089a7f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A940 size 8
public ?d_0089a940@@YAXXZ
?d_0089a940@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 38h, 1Fh, 00h, 00h
?d_0089a940@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A980 size 8
public ?d_0089a980@@YAXXZ
?d_0089a980@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 88h, 22h, 00h, 00h
?d_0089a980@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089A990 size 8
public ?d_0089a990@@YAXXZ
?d_0089a990@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 98h, 22h, 00h, 00h
?d_0089a990@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089AAE0 size 8
public ?d_0089aae0@@YAXXZ
?d_0089aae0@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 98h, 1Dh, 00h, 00h
?d_0089aae0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089AB20 size 8
public ?d_0089ab20@@YAXXZ
?d_0089ab20@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0E8h, 20h, 00h, 00h
?d_0089ab20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089AB30 size 8
public ?d_0089ab30@@YAXXZ
?d_0089ab30@@YAXXZ PROC
    db 83h, 0C1h, 08h, 0E9h, 0F8h, 20h, 00h, 00h
?d_0089ab30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089C720 size 25
public ?d_0089c720@@YAXXZ
?d_0089c720@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 4Eh, 04h, 83h, 0E1h, 0FEh, 8Bh, 01h, 0FFh, 50h, 04h
    db 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_0089c720@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x0089F8D0 size 324
public ?d_0089f8d0@@YAXXZ
?d_0089f8d0@@YAXXZ PROC
    db 57h, 8Bh, 7Ch, 24h, 08h, 85h, 0FFh, 7Dh, 07h, 83h, 0C8h, 0FFh, 5Fh, 0C2h, 04h, 00h
    db 8Bh, 09h, 56h, 83h, 0C1h, 08h, 33h, 0F6h, 85h, 0FFh, 0Fh, 8Eh, 91h, 00h, 00h, 00h
    db 8Ah, 01h, 3Ch, 7Fh, 77h, 06h, 0Fh, 0B6h, 0C0h, 41h, 0EBh, 78h, 8Ah, 0D0h, 80h, 0E2h
    db 0E0h, 80h, 0FAh, 0C0h, 75h, 15h, 33h, 0D2h, 8Ah, 51h, 01h, 83h, 0E0h, 1Fh, 0C1h, 0E0h
    db 06h, 83h, 0E2h, 3Fh, 0Bh, 0C2h, 83h, 0C1h, 02h, 0EBh, 59h, 8Ah, 0D0h, 80h, 0E2h, 0F0h
    db 80h, 0FAh, 0E0h, 75h, 22h, 33h, 0D2h, 8Ah, 51h, 01h, 83h, 0E0h, 0Fh, 0C1h, 0E0h, 06h
    db 83h, 0E2h, 3Fh, 0Bh, 0C2h, 33h, 0D2h, 8Ah, 51h, 02h, 0C1h, 0E0h, 06h, 83h, 0E2h, 3Fh
    db 0Bh, 0C2h, 83h, 0C1h, 03h, 0EBh, 2Dh, 33h, 0D2h, 8Ah, 51h, 01h, 83h, 0E0h, 07h, 0C1h
    db 0E0h, 06h, 83h, 0E2h, 3Fh, 0Bh, 0C2h, 33h, 0D2h, 8Ah, 51h, 02h, 0C1h, 0E0h, 06h, 83h
    db 0E2h, 3Fh, 0Bh, 0C2h, 33h, 0D2h, 8Ah, 51h, 03h, 0C1h, 0E0h, 06h, 83h, 0E2h, 3Fh, 0Bh
    db 0C2h, 83h, 0C1h, 04h, 85h, 0C0h, 74h, 0Dh, 46h, 3Bh, 0F7h, 0Fh, 8Ch, 6Fh, 0FFh, 0FFh
    db 0FFh, 85h, 0C9h, 75h, 08h, 5Eh, 83h, 0C8h, 0FFh, 5Fh, 0C2h, 04h, 00h, 8Ah, 01h, 3Ch
    db 7Fh, 77h, 08h, 5Eh, 0Fh, 0B6h, 0C0h, 5Fh, 0C2h, 04h, 00h, 8Ah, 0D0h, 80h, 0E2h, 0E0h
    db 80h, 0FAh, 0C0h, 75h, 14h, 0Fh, 0B6h, 49h, 01h, 83h, 0E0h, 1Fh, 0C1h, 0E0h, 06h, 83h
    db 0E1h, 3Fh, 5Eh, 0Bh, 0C1h, 5Fh, 0C2h, 04h, 00h, 8Ah, 0D0h, 80h, 0E2h, 0F0h, 80h, 0FAh
    db 0E0h, 75h, 21h, 33h, 0D2h, 8Ah, 51h, 01h, 0Fh, 0B6h, 49h, 02h, 83h, 0E0h, 0Fh, 0C1h
    db 0E0h, 06h, 83h, 0E1h, 3Fh, 83h, 0E2h, 3Fh, 0Bh, 0C2h, 0C1h, 0E0h, 06h, 5Eh, 0Bh, 0C1h
    db 5Fh, 0C2h, 04h, 00h, 33h, 0D2h, 8Ah, 51h, 01h, 83h, 0E0h, 07h, 0C1h, 0E0h, 06h, 5Eh
    db 5Fh, 83h, 0E2h, 3Fh, 0Bh, 0D0h, 33h, 0C0h, 8Ah, 41h, 02h, 0Fh, 0B6h, 49h, 03h, 0C1h
    db 0E2h, 06h, 83h, 0E1h, 3Fh, 83h, 0E0h, 3Fh, 0Bh, 0D0h, 0C1h, 0E2h, 06h, 0Bh, 0D1h, 8Bh
    db 0C2h, 0C2h, 04h, 00h
?d_0089f8d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A06F0 size 11
public ?d_008a06f0@@YAXXZ
?d_008a06f0@@YAXXZ PROC
    db 6Ah, 00h, 83h, 0C1h, 24h, 0E8h, 76h, 0D6h, 01h, 00h, 0C3h
?d_008a06f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A0C20 size 13
public ?d_008a0c20@@YAXXZ
?d_008a0c20@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 81h, 9Ch, 12h, 00h, 00h, 0C2h, 04h, 00h
?d_008a0c20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A1190 size 5
public ?d_008a1190@@YAXXZ
?d_008a1190@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_008a1190@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A1BB0 size 101
public ?d_008a1bb0@@YAXXZ
?d_008a1bb0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 10h, 3Dh, 0F5h, 01h, 00h, 00h, 8Ah, 54h, 24h, 0Ch, 56h, 75h, 1Ch
    db 8Bh, 74h, 24h, 08h, 89h, 0B1h, 7Ch, 12h, 00h, 00h, 8Bh, 74h, 24h, 0Ch, 89h, 0B1h
    db 80h, 12h, 00h, 00h, 88h, 91h, 84h, 12h, 00h, 00h, 0EBh, 21h, 3Dh, 0F6h, 01h, 00h
    db 00h, 75h, 1Ah, 8Bh, 74h, 24h, 08h, 89h, 0B1h, 8Ch, 12h, 00h, 00h, 8Bh, 74h, 24h
    db 0Ch, 89h, 0B1h, 90h, 12h, 00h, 00h, 88h, 91h, 94h, 12h, 00h, 00h, 0C1h, 0E0h, 0Fh
    db 0Fh, 0B6h, 0D2h, 0Bh, 0C2h, 0C1h, 0E0h, 02h, 83h, 0C8h, 01h, 50h, 0E8h, 0EFh, 0EAh, 0FFh
    db 0FFh, 5Eh, 0C2h, 10h, 00h
?d_008a1bb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A2ED0 size 88
public ?d_008a2ed0@@YAXXZ
?d_008a2ed0@@YAXXZ PROC
    db 53h, 8Ah, 5Ch, 24h, 08h, 0F6h, 0C3h, 02h, 56h, 8Bh, 0F1h, 74h, 2Ch, 8Bh, 46h, 0FCh
    db 57h, 68h, 0B0h, 20h, 0CAh, 00h, 8Dh, 7Eh, 0FCh, 50h, 6Ah, 20h, 56h, 0E8h, 84h, 3Eh
    db 15h, 00h, 0F6h, 0C3h, 01h, 74h, 0Ah, 57h, 0FFh, 15h, 2Ch, 78h, 33h, 01h, 83h, 0C4h
    db 04h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h, 8Bh, 0CEh, 0E8h, 0A0h, 0F1h, 0FFh, 0FFh
    db 0F6h, 0C3h, 01h, 74h, 0Ch, 6Ah, 20h, 56h, 0FFh, 15h, 30h, 78h, 33h, 01h, 83h, 0C4h
    db 08h, 8Bh, 0C6h, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_008a2ed0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A4C80 size 5
public ?d_008a4c80@@YAXXZ
?d_008a4c80@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_008a4c80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A7270 size 368
public ?d_008a7270@@YAXXZ
?d_008a7270@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 8Eh, 80h, 05h, 01h, 50h, 8Bh, 44h
    db 24h, 14h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 8Bh, 00h, 56h, 83h, 0C0h, 08h, 57h
    db 0BFh, 88h, 65h, 13h, 01h, 8Bh, 0F0h, 0B9h, 0Ch, 00h, 00h, 00h, 33h, 0D2h, 0F3h, 0A6h
    db 0Fh, 85h, 87h, 00h, 00h, 00h, 0A1h, 9Ch, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 66h, 6Ah
    db 2Ch, 0FFh, 15h, 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 40h, 00h, 0FFh, 0FFh
    db 83h, 0C4h, 08h, 89h, 74h, 24h, 1Ch, 85h, 0F6h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h
    db 00h, 74h, 1Ah, 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 22h, 2Ch, 0FFh, 0FFh, 0C7h, 06h
    db 28h, 61h, 13h, 01h, 0C7h, 46h, 20h, 40h, 54h, 0CAh, 00h, 0EBh, 02h, 33h, 0F6h, 89h
    db 35h, 9Ch, 7Ah, 33h, 01h, 8Bh, 46h, 04h, 25h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C8h, 40h
    db 89h, 46h, 04h, 8Bh, 0Dh, 9Ch, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 10h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0FFh, 12h, 0A1h, 9Ch, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 08h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 0F0h, 0BFh
    db 60h, 65h, 13h, 01h, 0B9h, 0Fh, 00h, 00h, 00h, 33h, 0C0h, 0F3h, 0A6h, 0Fh, 85h, 88h
    db 00h, 00h, 00h, 0A1h, 0A0h, 7Ah, 33h, 01h, 85h, 0C0h, 75h, 67h, 6Ah, 2Ch, 0FFh, 15h
    db 28h, 78h, 33h, 01h, 8Dh, 70h, 08h, 56h, 0E8h, 0A3h, 0FFh, 0FEh, 0FFh, 83h, 0C4h, 08h
    db 89h, 74h, 24h, 1Ch, 85h, 0F6h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 74h, 1Ah
    db 6Ah, 08h, 6Ah, 09h, 8Bh, 0CEh, 0E8h, 85h, 2Bh, 0FFh, 0FFh, 0C7h, 06h, 28h, 61h, 13h
    db 01h, 0C7h, 46h, 20h, 90h, 54h, 0CAh, 00h, 0EBh, 02h, 33h, 0F6h, 89h, 35h, 0A0h, 7Ah
    db 33h, 01h, 8Bh, 4Eh, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h, 4Eh
    db 04h, 8Bh, 0Dh, 0A0h, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0FFh, 12h, 0A1h, 0A0h, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h, 08h, 5Fh
    db 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_008a7270@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A78D0 size 547
public ?d_008a78d0@@YAXXZ
?d_008a78d0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 4Dh, 81h, 05h, 01h, 50h, 8Bh, 44h
    db 24h, 14h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 8Bh, 00h, 53h, 56h, 83h, 0C0h, 08h
    db 57h, 8Bh, 0D9h, 0BFh, 0CCh, 0ABh, 12h, 01h, 8Bh, 0F0h, 0B9h, 08h, 00h, 00h, 00h, 33h
    db 0D2h, 0F3h, 0A6h, 0Fh, 85h, 9Dh, 00h, 00h, 00h, 8Bh, 35h, 78h, 84h, 33h, 01h, 85h
    db 0F6h, 74h, 3Fh, 8Bh, 46h, 0Ch, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 0A3h, 78h, 84h, 33h
    db 01h, 8Bh, 51h, 04h, 3Bh, 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h, 04h, 0FFh, 0FFh
    db 0FFh, 0BFh, 0EBh, 08h, 8Bh, 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh, 46h, 08h, 3Dh
    db 98h, 52h, 2Dh, 01h, 8Dh, 4Eh, 08h, 74h, 39h, 6Ah, 00h, 0E8h, 00h, 73h, 0FFh, 0FFh
    db 0EBh, 30h, 6Ah, 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h, 89h, 44h, 24h
    db 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h, 09h, 8Bh, 0C8h, 0E8h
    db 8Ch, 21h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh
    db 8Bh, 0F0h, 8Bh, 53h, 20h, 83h, 0C2h, 08h, 52h, 8Bh, 0CEh, 0E8h, 30h, 0AEh, 0FEh, 0FFh
    db 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 0BFh, 0A0h, 95h, 11h, 01h, 8Bh, 0F0h, 0B9h, 05h, 00h
    db 00h, 00h, 33h, 0D2h, 0F3h, 0A6h, 0Fh, 85h, 9Dh, 00h, 00h, 00h, 8Bh, 35h, 78h, 84h
    db 33h, 01h, 85h, 0F6h, 74h, 3Fh, 8Bh, 46h, 0Ch, 8Bh, 0Dh, 10h, 78h, 33h, 01h, 0A3h
    db 78h, 84h, 33h, 01h, 8Bh, 51h, 04h, 3Bh, 11h, 8Dh, 41h, 04h, 7Ch, 09h, 81h, 66h
    db 04h, 0FFh, 0FFh, 0FFh, 0BFh, 0EBh, 08h, 8Bh, 49h, 08h, 89h, 34h, 91h, 0FFh, 00h, 8Bh
    db 46h, 08h, 3Dh, 98h, 52h, 2Dh, 01h, 8Dh, 4Eh, 08h, 74h, 39h, 6Ah, 00h, 0E8h, 4Dh
    db 72h, 0FFh, 0FFh, 0EBh, 30h, 6Ah, 10h, 0FFh, 15h, 28h, 78h, 33h, 01h, 83h, 0C4h, 04h
    db 89h, 44h, 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 74h, 09h
    db 8Bh, 0C8h, 0E8h, 0D9h, 20h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 0C7h, 44h, 24h, 14h, 0FFh
    db 0FFh, 0FFh, 0FFh, 8Bh, 0F0h, 8Bh, 53h, 24h, 83h, 0C2h, 08h, 52h, 8Bh, 0CEh, 0E8h, 7Dh
    db 0ADh, 0FEh, 0FFh, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 0F0h, 0BFh, 6Ch, 66h, 13h, 01h
    db 0B9h, 09h, 00h, 00h, 00h, 33h, 0C0h, 0F3h, 0A6h, 75h, 72h, 0A1h, 0BCh, 7Ah, 33h, 01h
    db 85h, 0C0h, 75h, 50h, 6Ah, 24h, 0E8h, 0C5h, 0FBh, 0FEh, 0FFh, 83h, 0C4h, 04h, 89h, 44h
    db 24h, 20h, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 02h, 00h, 00h, 00h, 74h, 0Eh, 68h, 0A0h
    db 62h, 0CAh, 00h, 8Bh, 0C8h, 0E8h, 26h, 25h, 0FFh, 0FFh, 0EBh, 02h, 33h, 0C0h, 0A3h, 0BCh
    db 7Ah, 33h, 01h, 8Bh, 48h, 04h, 81h, 0E1h, 7Fh, 0C0h, 0FFh, 0FFh, 83h, 0C9h, 40h, 89h
    db 48h, 04h, 8Bh, 0Dh, 0BCh, 7Ah, 33h, 01h, 8Bh, 11h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0FFh, 12h, 0A1h, 0BCh, 7Ah, 33h, 01h, 8Bh, 4Ch, 24h, 0Ch, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h
    db 0Ch, 5Fh, 5Eh, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 0Ch
    db 0C2h, 08h, 00h
?d_008a78d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A98A0 size 5
public ?d_008a98a0@@YAXXZ
?d_008a98a0@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_008a98a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A9B90 size 70
public ?d_008a9b90@@YAXXZ
?d_008a9b90@@YAXXZ PROC
    db 0A1h, 78h, 84h, 33h, 01h, 56h, 89h, 41h, 0Ch, 8Dh, 71h, 08h, 89h, 0Dh, 78h, 84h
    db 33h, 01h, 6Ah, 21h, 8Bh, 0CEh, 0E8h, 35h, 46h, 0FFh, 0FFh, 84h, 0C0h, 74h, 25h, 8Bh
    db 06h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h
    db 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 0C7h, 06h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h
    db 98h, 52h, 2Dh, 01h, 5Eh, 0C3h
?d_008a9b90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008A9BE0 size 70
public ?d_008a9be0@@YAXXZ
?d_008a9be0@@YAXXZ PROC
    db 0A1h, 78h, 84h, 33h, 01h, 56h, 89h, 41h, 0Ch, 8Dh, 71h, 08h, 89h, 0Dh, 78h, 84h
    db 33h, 01h, 6Ah, 21h, 8Bh, 0CEh, 0E8h, 0E5h, 45h, 0FFh, 0FFh, 84h, 0C0h, 74h, 25h, 8Bh
    db 06h, 66h, 0FFh, 08h, 66h, 83h, 38h, 00h, 75h, 0Dh, 8Bh, 0Dh, 30h, 7Ah, 33h, 01h
    db 50h, 0FFh, 51h, 04h, 83h, 0C4h, 04h, 0C7h, 06h, 98h, 52h, 2Dh, 01h, 66h, 0FFh, 05h
    db 98h, 52h, 2Dh, 01h, 5Eh, 0C3h
?d_008a9be0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008AC0E0 size 72
public ?d_008ac0e0@@YAXXZ
?d_008ac0e0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 8Bh, 74h, 24h, 14h, 85h, 0F6h, 57h, 8Bh, 0F9h, 74h
    db 0Fh, 8Bh, 0CBh, 0E8h, 88h, 6Bh, 02h, 00h, 56h, 8Bh, 0CBh, 0E8h, 00h, 6Dh, 02h, 00h
    db 8Bh, 07h, 48h, 75h, 12h, 8Bh, 44h, 24h, 14h, 8Bh, 4Fh, 18h, 50h, 51h, 0FFh, 15h
    db 0A8h, 78h, 33h, 01h, 83h, 0C4h, 08h, 85h, 0F6h, 74h, 07h, 8Bh, 0CBh, 0E8h, 9Eh, 6Bh
    db 02h, 00h, 5Fh, 5Eh, 5Bh, 0C2h, 0Ch, 00h
?d_008ac0e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008AC6B0 size 8
public ?d_008ac6b0@@YAXXZ
?d_008ac6b0@@YAXXZ PROC
    db 83h, 0C1h, 24h, 0E9h, 68h, 17h, 01h, 00h
?d_008ac6b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008AED50 size 366
public ?d_008aed50@@YAXXZ
?d_008aed50@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 8Bh, 0CEh, 0FFh, 10h, 8Bh, 0Dh, 0D8h
    db 77h, 33h, 01h, 8Bh, 7Ch, 24h, 14h, 89h, 0B1h, 40h, 12h, 00h, 00h, 8Bh, 15h, 0D8h
    db 77h, 33h, 01h, 33h, 0DBh, 3Bh, 0FBh, 89h, 9Ah, 54h, 12h, 00h, 00h, 0A1h, 0D8h, 77h
    db 33h, 01h, 89h, 98h, 58h, 12h, 00h, 00h, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 0B8h, 00h
    db 3Ch, 1Ch, 0C6h, 89h, 81h, 44h, 12h, 00h, 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h, 89h
    db 82h, 48h, 12h, 00h, 00h, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 89h, 81h, 4Ch, 12h, 00h
    db 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h, 89h, 82h, 50h, 12h, 00h, 00h, 74h, 18h, 0A1h
    db 50h, 87h, 33h, 01h, 8Bh, 0Dh, 48h, 87h, 33h, 01h, 8Bh, 4Ch, 88h, 0FCh, 0E8h, 2Dh
    db 95h, 0FEh, 0FFh, 85h, 0C0h, 75h, 28h, 0A1h, 0D8h, 77h, 33h, 01h, 0DBh, 80h, 74h, 12h
    db 00h, 00h, 0D8h, 66h, 20h, 0D9h, 98h, 54h, 12h, 00h, 00h, 0A1h, 0D8h, 77h, 33h, 01h
    db 0DBh, 80h, 78h, 12h, 00h, 00h, 0D8h, 66h, 24h, 0D9h, 98h, 58h, 12h, 00h, 00h, 3Bh
    db 0FBh, 7Eh, 43h, 8Bh, 15h, 50h, 87h, 33h, 01h, 0A1h, 48h, 87h, 33h, 01h, 8Bh, 4Ch
    db 82h, 0F8h, 0E8h, 0B9h, 95h, 0FEh, 0FFh, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 0D9h, 99h, 44h
    db 12h, 00h, 00h, 8Bh, 15h, 0D8h, 77h, 33h, 01h, 89h, 9Ah, 48h, 12h, 00h, 00h, 0A1h
    db 0D8h, 77h, 33h, 01h, 89h, 98h, 4Ch, 12h, 00h, 00h, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h
    db 89h, 99h, 50h, 12h, 00h, 00h, 83h, 0FFh, 01h, 7Eh, 20h, 8Bh, 15h, 50h, 87h, 33h
    db 01h, 0A1h, 48h, 87h, 33h, 01h, 8Bh, 4Ch, 82h, 0F4h, 0E8h, 71h, 95h, 0FEh, 0FFh, 8Bh
    db 0Dh, 0D8h, 77h, 33h, 01h, 0D9h, 99h, 48h, 12h, 00h, 00h, 83h, 0FFh, 02h, 7Eh, 20h
    db 8Bh, 15h, 50h, 87h, 33h, 01h, 0A1h, 48h, 87h, 33h, 01h, 8Bh, 4Ch, 82h, 0F0h, 0E8h
    db 4Ch, 95h, 0FEh, 0FFh, 8Bh, 0Dh, 0D8h, 77h, 33h, 01h, 0D9h, 99h, 4Ch, 12h, 00h, 00h
    db 83h, 0FFh, 03h, 5Fh, 5Eh, 5Bh, 7Eh, 20h, 8Bh, 15h, 50h, 87h, 33h, 01h, 0A1h, 48h
    db 87h, 33h, 01h, 8Bh, 4Ch, 82h, 0ECh, 0E8h, 24h, 95h, 0FEh, 0FFh, 8Bh, 0Dh, 0D8h, 77h
    db 33h, 01h, 0D9h, 99h, 50h, 12h, 00h, 00h, 0A1h, 0BCh, 79h, 33h, 01h, 0C3h
?d_008aed50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008B2C60 size 332
public ?d_008b2c60@@YAXXZ
?d_008b2c60@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 70h, 8Ah, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 8Bh, 74h, 24h, 14h, 8Bh, 46h, 04h, 24h, 3Fh, 3Ch
    db 20h, 57h, 0Fh, 85h, 0Fh, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 1Ch, 8Bh, 0Fh, 83h, 0C1h
    db 08h, 68h, 0E0h, 69h, 13h, 01h, 51h, 0E8h, 04h, 43h, 14h, 00h, 83h, 0C4h, 08h, 85h
    db 0C0h, 75h, 65h, 8Bh, 4Ch, 24h, 20h, 8Bh, 51h, 04h, 8Bh, 0C2h, 83h, 0E0h, 3Fh, 83h
    db 0F8h, 01h, 74h, 09h, 83h, 0F8h, 2Ah, 0Fh, 85h, 0DAh, 00h, 00h, 00h, 0C1h, 0EAh, 0Fh
    db 0F6h, 0D2h, 0F6h, 0C2h, 01h, 0Fh, 85h, 0CCh, 00h, 00h, 00h, 66h, 0FFh, 05h, 98h, 52h
    db 2Dh, 01h, 0C7h, 44h, 24h, 20h, 98h, 52h, 2Dh, 01h, 8Dh, 54h, 24h, 20h, 52h, 0C7h
    db 44h, 24h, 14h, 00h, 00h, 00h, 00h, 0E8h, 0D4h, 58h, 0FEh, 0FFh, 8Bh, 46h, 20h, 85h
    db 0C0h, 74h, 0Fh, 8Bh, 54h, 24h, 20h, 8Bh, 0C8h, 8Bh, 01h, 83h, 0C2h, 08h, 52h, 0FFh
    db 50h, 38h, 8Bh, 44h, 24h, 20h, 0EBh, 72h, 8Bh, 0Fh, 83h, 0C1h, 08h, 68h, 0D4h, 69h
    db 13h, 01h, 51h, 0E8h, 88h, 42h, 14h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 75h, 78h, 8Bh
    db 4Ch, 24h, 20h, 8Bh, 51h, 04h, 8Bh, 0C2h, 83h, 0E0h, 3Fh, 83h, 0F8h, 01h, 74h, 05h
    db 83h, 0F8h, 2Ah, 75h, 62h, 0C1h, 0EAh, 0Fh, 0F6h, 0D2h, 0F6h, 0C2h, 01h, 75h, 58h, 66h
    db 0FFh, 05h, 98h, 52h, 2Dh, 01h, 0C7h, 44h, 24h, 18h, 98h, 52h, 2Dh, 01h, 8Dh, 54h
    db 24h, 18h, 52h, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h, 0E8h, 60h, 58h, 0FEh, 0FFh
    db 8Bh, 46h, 20h, 85h, 0C0h, 74h, 0Fh, 8Bh, 54h, 24h, 18h, 8Bh, 0C8h, 8Bh, 01h, 83h
    db 0C2h, 08h, 52h, 0FFh, 50h, 44h, 8Bh, 44h, 24h, 18h, 66h, 0FFh, 08h, 66h, 83h, 38h
    db 00h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 0Ch, 50h, 0A1h, 30h, 7Ah, 33h
    db 01h, 0FFh, 50h, 04h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 08h, 5Fh, 0B0h, 01h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 0Ch, 00h
?d_008b2c60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008B4DA0 size 674
_TEXT ENDS
_TEXT$d00cb4da0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CB4DA0 size 674
public ?d_008b4da0@@YAXXZ
?d_008b4da0@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 08Bh, 00Dh
    dd g_Va013386A0
    db 06Ah, 0FFh, 068h
    dd g_Va01058D3C
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 056h, 08Bh, 074h, 024h, 018h, 08Bh, 006h, 03Bh
    db 0C1h, 074h, 018h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 086h, 000h, 000h, 000h, 0A1h
    dd ?g_bfmeS1082_4@@3PAVBfmeS1082@@A
    db 085h, 0C0h, 075h, 066h, 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 018h, 085h, 0F6h, 0C7h, 044h, 024h, 00Ch, 000h, 000h, 000h
    db 000h, 074h, 01Ah, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 0C7h, 046h, 020h
    dd ?aptSetPackedChannels008B4370@@YAPAVAptValue@@PAURva008B4370Owner@@H@Z
    db 0EBh, 002h, 033h, 0F6h, 089h, 035h
    dd ?g_bfmeS1082_4@@3PAVBfmeS1082@@A
    db 08Bh, 046h, 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 046h, 004h, 08Bh, 00Dh
    dd ?g_bfmeS1082_4@@3PAVBfmeS1082@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 00Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_bfmeS1082_4@@3PAVBfmeS1082@@A
    db 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h
    db 008h, 000h, 08Bh, 006h, 08Bh, 00Dh
    dd g_Va01338594
    db 03Bh, 0C1h, 074h, 018h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 00Fh, 085h, 086h, 000h, 000h, 000h, 0A1h
    dd ?g_bfmeS1082_5@@3PAVBfmeS1082@@A
    db 085h, 0C0h, 075h, 066h, 06Ah, 02Ch, 0FFh, 015h
    dd ?Rva008C5D70Alloc@@3P6APAXI@ZA
    db 08Dh, 070h, 008h, 056h
    call ?bfmePush@@YAXPAVBfmeItemDX@@@Z
    db 083h, 0C4h, 008h, 089h, 074h, 024h, 018h, 085h, 0F6h, 0C7h, 044h, 024h, 00Ch, 001h, 000h, 000h
    db 000h, 074h, 01Ah, 06Ah, 008h, 06Ah, 009h, 08Bh, 0CEh
    call ??0Rva00899F00Base@@QAE@IH@Z
    db 0C7h, 006h
    dd _bfmeVft1029A
    db 0C7h, 046h, 020h
    dd ?aptPackedChannels008B4420@@YAPAVAptValue@@PAURva008B4420Owner@@H@Z
    db 0EBh, 002h, 033h, 0F6h, 089h, 035h
    dd ?g_bfmeS1082_5@@3PAVBfmeS1082@@A
    db 08Bh, 046h, 004h, 025h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C8h, 040h, 089h, 046h, 004h, 08Bh, 00Dh
    dd ?g_bfmeS1082_5@@3PAVBfmeS1082@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 00Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_bfmeS1082_5@@3PAVBfmeS1082@@A
    db 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h
    db 008h, 000h, 08Bh, 006h, 08Bh, 00Dh
    dd g_Va013385A4
    db 03Bh, 0C1h, 074h, 014h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 070h, 0A1h
    dd ?g_bfmeS1082_6@@3PAVBfmeS1082@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 018h, 085h, 0C0h, 0C7h, 044h, 024h, 00Ch, 002h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd ?aptGetChannels008B4700@@YAPAVRva00899F00Base@@PAUOwner008B4700@@H@Z
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_bfmeS1082_6@@3PAVBfmeS1082@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_bfmeS1082_6@@3PAVBfmeS1082@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 00Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_bfmeS1082_6@@3PAVBfmeS1082@@A
    db 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h
    db 008h, 000h, 08Bh, 006h, 08Bh, 00Dh
    dd g_Va013386AC
    db 03Bh, 0C1h, 074h, 014h, 083h, 0C1h, 008h, 051h, 083h, 0C0h, 008h, 050h
    call ?ji_009f6fa0@@YAXXZ
    db 083h, 0C4h, 008h, 085h, 0C0h, 075h, 070h, 0A1h
    dd ?g_bfmeS1082_7@@3PAVBfmeS1082@@A
    db 085h, 0C0h, 075h, 050h, 06Ah, 024h
    call ?Rva00897640@@YAPAXI@Z
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 018h, 085h, 0C0h, 0C7h, 044h, 024h, 00Ch, 003h, 000h, 000h
    db 000h, 074h, 00Eh, 068h
    dd ?aptApplyChannels008B4480@@YAPAVAptValue@@PAUOwner008B4480@@H@Z
    db 08Bh, 0C8h
    call ?bfmeGo1029A@BfmeA1029@@QAEPAV1@H@Z
    db 0EBh, 002h, 033h, 0C0h, 0A3h
    dd ?g_bfmeS1082_7@@3PAVBfmeS1082@@A
    db 08Bh, 048h, 004h, 081h, 0E1h, 07Fh, 0C0h, 0FFh, 0FFh, 083h, 0C9h, 040h, 089h, 048h, 004h, 08Bh
    db 00Dh
    dd ?g_bfmeS1082_7@@3PAVBfmeS1082@@A
    db 08Bh, 011h, 0C7h, 044h, 024h, 00Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 012h, 0A1h
    dd ?g_bfmeS1082_7@@3PAVBfmeS1082@@A
    db 08Bh, 04Ch, 024h, 004h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 00Ch, 0C2h
    db 008h, 000h, 08Bh, 04Ch, 024h, 004h, 033h, 0C0h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh
    db 083h, 0C4h, 00Ch, 0C2h, 008h, 000h
?d_008b4da0@@YAXXZ ENDP
_TEXT$d00cb4da0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x008B8D00 size 83
public ?d_008b8d00@@YAXXZ
?d_008b8d00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 71h, 28h, 3Bh, 0C6h, 7Dh, 1Fh, 8Bh, 51h, 20h, 85h
    db 0D2h, 74h, 18h, 8Bh, 04h, 82h, 85h, 0C0h, 74h, 0Ah, 0A8h, 01h, 75h, 06h, 33h, 0C0h
    db 5Eh, 0C2h, 04h, 00h, 83h, 0E0h, 0FEh, 5Eh, 0C2h, 04h, 00h, 8Bh, 51h, 1Ch, 2Bh, 0C6h
    db 81h, 0E2h, 0FFh, 00h, 00h, 00h, 3Bh, 0C2h, 7Dh, 0Ah, 8Bh, 49h, 18h, 8Bh, 04h, 81h
    db 5Eh, 0C2h, 04h, 00h, 2Bh, 0C2h, 5Eh, 89h, 44h, 24h, 04h, 83h, 0C1h, 08h, 0E9h, 0DDh
    db 3Eh, 0FEh, 0FFh
?d_008b8d00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008B8F80 size 26
public ?d_008b8f80@@YAXXZ
?d_008b8f80@@YAXXZ PROC
    db 56h, 0E8h, 68h, 0DEh, 13h, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 07h, 80h, 3Eh, 30h
    db 0Fh, 94h, 0C0h, 0C3h, 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_008b8f80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008B8FA0 size 117
public ?d_008b8fa0@@YAXXZ
?d_008b8fa0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 37h, 83h, 0C6h, 08h, 56h, 0E8h, 3Dh, 0DEh, 13h
    db 00h, 83h, 0C4h, 04h, 85h, 0C0h, 75h, 05h, 80h, 3Eh, 30h, 75h, 51h, 8Bh, 07h, 83h
    db 0C0h, 08h, 55h, 50h, 0E8h, 25h, 0DEh, 13h, 00h, 8Bh, 6Ch, 24h, 1Ch, 83h, 0C4h, 04h
    db 85h, 0EDh, 8Bh, 0F8h, 75h, 06h, 8Bh, 2Dh, 0BCh, 79h, 33h, 01h, 85h, 0FFh, 7Ch, 26h
    db 53h, 8Bh, 5Ch, 24h, 14h, 8Dh, 77h, 01h, 56h, 8Bh, 0CBh, 0E8h, 70h, 0FDh, 0FFh, 0FFh
    db 55h, 57h, 8Bh, 0CBh, 0E8h, 0C7h, 0F4h, 0FFh, 0FFh, 8Bh, 43h, 28h, 3Bh, 0F0h, 7Eh, 02h
    db 8Bh, 0C6h, 89h, 43h, 28h, 5Bh, 5Dh, 5Fh, 0B0h, 01h, 5Eh, 0C2h, 0Ch, 00h, 5Fh, 32h
    db 0C0h, 5Eh, 0C2h, 0Ch, 00h
?d_008b8fa0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008BE2C0 size 230
_TEXT ENDS
_TEXT$d00cbe2c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00CBE2C0 size 230
public ?d_008be2c0@@YAXXZ
?d_008be2c0@@YAXXZ PROC
    db 08Bh, 001h, 08Bh, 008h, 055h, 08Bh, 069h, 058h, 085h, 0EDh, 00Fh, 084h, 0D2h, 000h, 000h, 000h
    db 053h, 056h, 057h, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 00Fh, 084h, 081h, 000h, 000h, 000h, 081h
    db 07Dh, 00Ch
    dd ?Rva012D5298Empty@@3URva00893410Block@@A
    db 074h, 078h, 08Bh, 055h, 004h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 075h, 06Bh, 08Bh
    db 05Dh, 04Ch, 08Bh, 043h, 050h, 08Bh, 048h, 010h
    call ?bfmeFirst1285@BfmeIteratorList1285@@QAEPAUBfmeIterator1285@@XZ
    db 085h, 0C0h, 074h, 059h, 08Bh, 050h, 004h, 083h, 0E2h, 0FEh, 08Bh, 072h, 004h, 08Bh, 0CEh, 083h
    db 0E1h, 03Fh, 083h, 0F9h, 00Ch, 07Ch, 036h, 083h, 0F9h, 013h, 07Fh, 031h, 08Bh, 0CEh, 0C1h, 0E9h
    db 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 025h, 03Bh, 0D5h, 074h, 031h, 08Bh, 010h, 08Bh, 075h
    db 00Ch, 00Fh, 0B7h, 04Ah, 002h, 00Fh, 0B7h, 07Eh, 002h, 03Bh, 0CFh, 075h, 010h, 03Bh, 0D6h, 074h
    db 01Ch, 08Dh, 07Eh, 008h, 08Dh, 072h, 008h, 033h, 0D2h, 0F3h, 0A6h, 074h, 010h, 08Bh, 04Bh, 050h
    db 08Bh, 049h, 010h, 050h
    call ?bfmeNext1285@BfmeIteratorList1285@@QAEPAUBfmeIterator1285@@PAU2@@Z
    db 085h, 0C0h, 075h, 0A7h, 08Bh, 04Dh, 004h, 08Bh, 0C1h, 083h, 0E0h, 03Fh, 083h, 0F8h, 00Dh, 075h
    db 00Ch, 08Bh, 0D1h, 0C1h, 0EAh, 00Fh, 0F6h, 0D2h, 0F6h, 0C2h, 001h, 074h, 00Fh, 083h, 0F8h, 012h
    db 075h, 016h, 0C1h, 0E9h, 00Fh, 0F6h, 0D1h, 0F6h, 0C1h, 001h, 075h, 00Ch, 08Bh, 04Dh, 050h, 055h
    db 083h, 0C1h, 024h, 0E8h, 02Ch, 0FFh, 0FFh, 0FFh, 08Bh, 06Dh, 058h, 085h, 0EDh, 00Fh, 085h, 034h
    db 0FFh, 0FFh, 0FFh, 05Fh, 05Eh, 05Bh, 05Dh, 0C2h, 004h, 000h
?d_008be2c0@@YAXXZ ENDP
_TEXT$d00cbe2c0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x008C3A90 size 90
public ?d_008c3a90@@YAXXZ
?d_008c3a90@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 8Bh, 0C3h, 57h, 8Dh, 50h, 01h, 8Dh, 64h, 24h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 8Bh, 0F8h, 33h, 0F6h, 8Dh, 49h, 00h
    db 8Bh, 04h, 0B5h, 80h, 84h, 33h, 01h, 0Fh, 0B7h, 48h, 02h, 3Bh, 0CFh, 75h, 11h, 83h
    db 0C0h, 08h, 53h, 50h, 0E8h, 0D7h, 34h, 13h, 00h, 83h, 0C4h, 08h, 85h, 0C0h, 74h, 0Fh
    db 46h, 81h, 0FEh, 0B2h, 00h, 00h, 00h, 7Ch, 0D7h, 5Fh, 5Eh, 33h, 0C0h, 5Bh, 0C3h, 5Fh
    db 8Dh, 04h, 0B5h, 80h, 84h, 33h, 01h, 5Eh, 5Bh, 0C3h
?d_008c3a90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008C3E10 size 14
public ?d_008c3e10@@YAXXZ
?d_008c3e10@@YAXXZ PROC
    db 8Bh, 41h, 50h, 85h, 0C0h, 74h, 06h, 8Bh, 0C8h, 8Bh, 01h, 0FFh, 20h, 0C3h
?d_008c3e10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x008C3E50 size 21
public ?d_008c3e50@@YAXXZ
?d_008c3e50@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 50h, 51h, 0E8h, 81h, 0D0h, 0FEh, 0FFh, 83h
    db 0C4h, 08h, 0C2h, 08h, 00h
?d_008c3e50@@YAXXZ ENDP
_TEXT ENDS
END
