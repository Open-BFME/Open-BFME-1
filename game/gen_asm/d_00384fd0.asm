.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??_7Rva007F01B0@@6B@:BYTE
EXTERN ?AssetSubsystem0059A3D0@@3PAXA:BYTE
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeTheMapObjectListHolder@@3PAUMapObjectList@@A:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?EngineGlobal007629F0@@3PAUEngine007629F0@@A:BYTE
EXTERN ?Factory0040A260@@3PAVThingFactory@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?PlayerList005999B0@@3PAUPlayers005999B0@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Rva0090F050@@YAXXZ:NEAR
EXTERN ?Rva009EBAC0@@YAXH@Z:NEAR
EXTERN ?Rva012ED5AC@@3PAVOptionPreferences@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?Rva012ef4cc@@3PAVRva0041D290Client@@A:BYTE
EXTERN ?Rva0134CB48FileSystem@@3PAVFileSystem@@A:BYTE
EXTERN ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A:BYTE
EXTERN ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A:BYTE
EXTERN ?TheGameText@@3PAVBfmeGameText@@A:BYTE
EXTERN ?TheKey_originalOwner@@3VStaticNameKey@@B:BYTE
EXTERN ?TheScriptActions@@3PAVScriptActionsInterface@@A:BYTE
EXTERN ?allocate@__new_alloc@_STL@@SAPAXI@Z:NEAR
EXTERN ?bfmeTakeEC@BfmeThingEC@@QAEHPAH@Z:NEAR
EXTERN ?createMemoryReadFile@@YAPAVFile@@PADH@Z:NEAR
EXTERN ?d_009d9d90@@YAXXZ:NEAR
EXTERN ?forcedCRCFrame@@3HA:BYTE
EXTERN ?format@AsciiString@@QAAXV1@ZZ:NEAR
EXTERN ?forward@Rva0002FF6DStringPresenceThunk@@QBE?AVAsciiString@@HPA_N@Z:NEAR
EXTERN ?g_binaryDeepCRC@@3DA:BYTE
EXTERN ?g_flag12ED4E8@@3_NA:BYTE
EXTERN ?j_000019f1@@YAXXZ:NEAR
EXTERN ?j_000032d8@@YAXXZ:NEAR
EXTERN ?j_000050c9@@YAXXZ:NEAR
EXTERN ?j_000057e5@@YAXXZ:NEAR
EXTERN ?j_000076cb@@YAXXZ:NEAR
EXTERN ?j_00009304@@YAXXZ:NEAR
EXTERN ?j_0000991c@@YAXXZ:NEAR
EXTERN ?j_0000b81b@@YAXXZ:NEAR
EXTERN ?j_0000d9b8@@YAXXZ:NEAR
EXTERN ?j_00012814@@YAXXZ:NEAR
EXTERN ?j_0001325a@@YAXXZ:NEAR
EXTERN ?j_00015d7a@@YAXXZ:NEAR
EXTERN ?j_00017a12@@YAXXZ:NEAR
EXTERN ?j_000184b2@@YAXXZ:NEAR
EXTERN ?j_0001be82@@YAXXZ:NEAR
EXTERN ?j_0001c549@@YAXXZ:NEAR
EXTERN ?j_0001c675@@YAXXZ:NEAR
EXTERN ?j_00020b21@@YAXXZ:NEAR
EXTERN ?j_000267c9@@YAXXZ:NEAR
EXTERN ?j_00028560@@YAXXZ:NEAR
EXTERN ?j_00028bb9@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_00035e0e@@YAXXZ:NEAR
EXTERN ?j_000361ce@@YAXXZ:NEAR
EXTERN ?j_000364ad@@YAXXZ:NEAR
EXTERN ?j_000365d4@@YAXXZ:NEAR
EXTERN ?j_00037f83@@YAXXZ:NEAR
EXTERN ?j_000399A5@@YAXXZ:NEAR
EXTERN ?j_0003a1a7@@YAXXZ:NEAR
EXTERN ?j_0003a855@@YAXXZ:NEAR
EXTERN ?j_00043072@@YAXXZ:NEAR
EXTERN ?j_00043a1d@@YAXXZ:NEAR
EXTERN ?j_00043eeb@@YAXXZ:NEAR
EXTERN ?j_000441b1@@YAXXZ:NEAR
EXTERN ?j_0004494a@@YAXXZ:NEAR
EXTERN ?j_0004a7a5@@YAXXZ:NEAR
EXTERN ?openFile@FileSystem@@QAEPAVFile@@PBDH@Z:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@G@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN __imp__GetComputerNameA@8:BYTE
EXTERN __imp__Sleep@4:BYTE
EXTERN __imp__free:BYTE
EXTERN __imp__strncmp:BYTE
EXTERN g_Va0101BC42:NEAR
EXTERN g_Va0101C096:NEAR
EXTERN g_Va0101C0C0:NEAR
EXTERN g_Va01080294:BYTE
EXTERN g_Va010EB0E8:BYTE
EXTERN g_Va010EB104:BYTE
EXTERN g_Va010EB120:BYTE
EXTERN g_Va010EB168:BYTE
EXTERN g_Va010EB204:BYTE
EXTERN g_Va010EB218:BYTE
EXTERN g_Va010EB2A8:BYTE
EXTERN g_Va010EB320:BYTE
EXTERN g_Va010EB334:BYTE
EXTERN g_Va010EB34C:BYTE
EXTERN g_Va010EB358:BYTE
EXTERN g_Va010EB364:BYTE
EXTERN g_Va010EB378:BYTE
EXTERN g_Va010EB5BC:BYTE
EXTERN g_Va012A7800:BYTE
EXTERN g_Va012A7910:BYTE
EXTERN g_Va012F4C68:BYTE
_TEXT SEGMENT

; ghidra: FUN_00784fd0  retail @ 0x00384FD0 size 120
public ?d_00384fd0@@YAXXZ
?d_00384fd0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 53h, 56h, 8Bh, 74h, 24h, 14h, 57h, 8Bh, 7Ch, 24h, 14h, 8Bh
    db 0CFh, 2Bh, 0C8h, 0C1h, 0F9h, 04h, 85h, 0C9h, 7Eh, 30h, 8Bh, 16h, 8Dh, 64h, 24h, 00h
    db 39h, 10h, 74h, 50h, 8Bh, 58h, 04h, 83h, 0C0h, 04h, 3Bh, 0DAh, 74h, 46h, 8Bh, 58h
    db 04h, 83h, 0C0h, 04h, 3Bh, 0DAh, 74h, 3Ch, 8Bh, 58h, 04h, 83h, 0C0h, 04h, 3Bh, 0DAh
    db 74h, 32h, 83h, 0C0h, 04h, 49h, 85h, 0C9h, 7Fh, 0D6h, 8Bh, 0CFh, 2Bh, 0C8h, 0C1h, 0F9h
    db 02h, 49h, 74h, 18h, 49h, 74h, 0Ch, 49h, 75h, 18h, 8Bh, 08h, 3Bh, 0Eh, 74h, 14h
    db 83h, 0C0h, 04h, 8Bh, 10h, 3Bh, 16h, 74h, 0Bh, 83h, 0C0h, 04h, 8Bh, 08h, 3Bh, 0Eh
    db 74h, 02h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_00384fd0@@YAXXZ ENDP

; ghidra: FUN_00785180  retail @ 0x00385180 size 26
public ?d_00385180@@YAXXZ
?d_00385180@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 4Eh, 04h, 0E8h, 00h, 2Bh, 50h, 00h
    db 33h, 0C0h, 89h, 46h, 08h, 89h, 46h, 0Ch, 5Eh, 0C3h
?d_00385180@@YAXXZ ENDP

; ghidra: FUN_007851b0  retail @ 0x003851B0 size 31
public ?d_003851b0@@YAXXZ
?d_003851b0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 58h, 0ADh, 0Eh, 01h, 74h, 09h
    db 56h, 0E8h, 0EAh, 0CCh, 4Fh, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_003851b0@@YAXXZ ENDP

; ghidra: FUN_007851e0  retail @ 0x003851E0 size 468
public ?d_003851e0@@YAXXZ
?d_003851e0@@YAXXZ PROC
    db 81h, 0ECh, 24h, 02h, 00h, 00h, 53h, 55h, 33h, 0DBh, 53h, 8Bh, 0E9h, 0E8h, 0Eh, 6Ah
    db 66h, 00h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 88h, 98h, 0F4h, 0Ch, 00h, 00h, 8Bh, 0Dh, 0C8h
    db 0D5h, 2Eh, 01h, 88h, 59h, 1Eh, 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 88h, 5Ah, 64h, 0A1h
    db 0C8h, 0D5h, 2Eh, 01h, 88h, 58h, 65h, 0E8h, 74h, 44h, 50h, 00h, 6Ah, 01h, 0E8h, 24h
    db 0D6h, 0C7h, 0FFh, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 8Bh, 51h, 08h, 83h, 0C4h, 08h, 8Dh
    db 44h, 24h, 14h, 50h, 89h, 55h, 10h, 0C6h, 45h, 14h, 01h, 88h, 5Dh, 0Ch, 0FFh, 15h
    db 0B8h, 8Dh, 35h, 01h, 68h, 04h, 01h, 00h, 00h, 8Dh, 4Ch, 24h, 28h, 51h, 53h, 8Dh
    db 54h, 24h, 20h, 52h, 6Ah, 01h, 68h, 00h, 08h, 00h, 00h, 0FFh, 15h, 80h, 8Dh, 35h
    db 01h, 8Dh, 44h, 24h, 24h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 2Bh
    db 0C2h, 0C6h, 44h, 04h, 24h, 2Dh, 40h, 0BAh, 04h, 01h, 00h, 00h, 2Bh, 0D0h, 52h, 8Dh
    db 4Ch, 04h, 28h, 51h, 53h, 8Dh, 44h, 24h, 20h, 50h, 6Ah, 02h, 68h, 00h, 08h, 00h
    db 00h, 88h, 19h, 0FFh, 15h, 10h, 8Eh, 35h, 01h, 38h, 5Ch, 24h, 24h, 74h, 19h, 8Dh
    db 4Ch, 24h, 24h, 8Ah, 01h, 3Ch, 2Fh, 74h, 04h, 3Ch, 3Ah, 75h, 03h, 0C6h, 01h, 5Fh
    db 8Ah, 41h, 01h, 41h, 3Ah, 0C3h, 75h, 0EBh, 66h, 0A1h, 2Ch, 0AEh, 0Eh, 01h, 8Bh, 15h
    db 28h, 0AEh, 0Eh, 01h, 8Bh, 0Dh, 24h, 0AEh, 0Eh, 01h, 66h, 89h, 84h, 24h, 30h, 01h
    db 00h, 00h, 8Dh, 44h, 24h, 24h, 89h, 94h, 24h, 2Ch, 01h, 00h, 00h, 89h, 8Ch, 24h
    db 28h, 01h, 00h, 00h, 8Bh, 0D0h, 8Ah, 08h, 40h, 3Ah, 0CBh, 75h, 0F9h, 57h, 8Dh, 0BCh
    db 24h, 2Ch, 01h, 00h, 00h, 2Bh, 0C2h, 4Fh, 8Ah, 4Fh, 01h, 47h, 3Ah, 0CBh, 75h, 0F8h
    db 56h, 8Bh, 0C8h, 0C1h, 0E9h, 02h, 8Bh, 0F2h, 0F3h, 0A5h, 8Bh, 0C8h, 83h, 0E1h, 03h, 0F3h
    db 0A4h, 8Dh, 0BCh, 24h, 30h, 01h, 00h, 00h, 4Fh, 5Eh, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 47h, 01h, 47h, 3Ah, 0C3h, 75h, 0F8h, 8Bh, 0Dh, 1Ch, 0AEh, 0Eh, 01h, 8Ah, 15h
    db 20h, 0AEh, 0Eh, 01h, 8Dh, 84h, 24h, 2Ch, 01h, 00h, 00h, 89h, 0Fh, 68h, 0F8h, 6Dh
    db 07h, 01h, 50h, 88h, 57h, 04h, 0FFh, 15h, 0BCh, 93h, 35h, 01h, 83h, 0C4h, 08h, 3Bh
    db 0C3h, 89h, 45h, 18h, 5Fh, 74h, 19h, 50h, 68h, 68h, 0ADh, 0Eh, 01h, 0FFh, 15h, 0C8h
    db 93h, 35h, 01h, 8Bh, 4Dh, 18h, 51h, 0FFh, 15h, 0A8h, 93h, 35h, 01h, 83h, 0C4h, 0Ch
    db 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 88h, 5Ah, 64h, 8Bh, 0Dh, 00h, 16h, 2Fh, 01h, 8Dh
    db 54h, 24h, 08h, 0C7h, 44h, 24h, 08h, 00h, 00h, 48h, 42h, 0C7h, 44h, 24h, 0Ch, 00h
    db 00h, 48h, 42h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 8Bh, 01h, 52h, 0FFh, 50h
    db 54h, 89h, 5Dh, 24h, 89h, 5Dh, 4Ch, 0C6h, 45h, 28h, 01h, 5Dh, 5Bh, 81h, 0C4h, 24h
    db 02h, 00h, 00h, 0C3h
?d_003851e0@@YAXXZ ENDP

; ghidra: FUN_00785430  retail @ 0x00385430 size 108
public ?d_00385430@@YAXXZ
?d_00385430@@YAXXZ PROC
    db 83h, 0ECh, 3Ch, 68h, 73h, 05h, 00h, 00h, 68h, 48h, 0AEh, 0Eh, 01h, 6Ah, 15h, 6Ah
    db 01h, 0E8h, 66h, 26h, 0CAh, 0FFh, 83h, 0C4h, 10h, 83h, 0F8h, 01h, 73h, 07h, 0B8h, 01h
    db 00h, 00h, 00h, 0EBh, 0Ah, 83h, 0F8h, 15h, 76h, 05h, 0B8h, 15h, 00h, 00h, 00h, 50h
    db 8Dh, 44h, 24h, 04h, 68h, 30h, 0AEh, 0Eh, 01h, 50h, 0FFh, 15h, 8Ch, 94h, 35h, 01h
    db 8Dh, 44h, 24h, 0Ch, 83h, 0C4h, 0Ch, 8Dh, 50h, 01h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 50h, 8Dh, 4Ch, 24h, 04h, 51h, 8Bh
    db 4Ch, 24h, 48h, 0E8h, 88h, 28h, 50h, 00h, 83h, 0C4h, 3Ch, 0C3h
?d_00385430@@YAXXZ ENDP

; ghidra: FUN_007854c0  retail @ 0x003854C0 size 54
public ?d_003854c0@@YAXXZ
?d_003854c0@@YAXXZ PROC
    db 56h, 8Bh, 0B1h, 0A8h, 00h, 00h, 00h, 85h, 0F6h, 57h, 8Bh, 7Ch, 24h, 0Ch, 74h, 12h
    db 57h, 8Bh, 0CEh, 0E8h, 4Dh, 5Eh, 0C8h, 0FFh, 8Bh, 0B6h, 88h, 00h, 00h, 00h, 85h, 0F6h
    db 75h, 0EEh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 57h, 0FFh, 90h, 68h, 01h, 00h
    db 00h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_003854c0@@YAXXZ ENDP

; ghidra: FUN_00785570  retail @ 0x00385570 size 54
public ?d_00385570@@YAXXZ
?d_00385570@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 57h, 8Bh, 0F9h, 7Ch, 25h, 83h, 0FEh, 08h, 7Dh
    db 20h, 8Ah, 8Ch, 3Eh, 20h, 01h, 00h, 00h, 0B0h, 01h, 3Ah, 0C8h, 74h, 13h, 88h, 84h
    db 3Eh, 20h, 01h, 00h, 00h, 0E8h, 4Ah, 2Ch, 0CCh, 0FFh, 89h, 84h, 0B7h, 28h, 01h, 00h
    db 00h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00385570@@YAXXZ ENDP

; ghidra: FUN_007855c0  retail @ 0x003855C0 size 35
public ?d_003855c0@@YAXXZ
?d_003855c0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 8Eh, 74h, 01h, 00h, 00h, 0E8h, 0BDh
    db 26h, 50h, 00h, 33h, 0C0h, 89h, 86h, 78h, 01h, 00h, 00h, 89h, 86h, 7Ch, 01h, 00h
    db 00h, 5Eh, 0C3h
?d_003855c0@@YAXXZ ENDP

; ghidra: FUN_007855f0  retail @ 0x003855F0 size 117
public ?d_003855f0@@YAXXZ
?d_003855f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Dh, 0BEh, 70h, 01h, 00h, 00h, 8Bh, 0CFh, 0E8h, 0F8h, 72h, 0CAh
    db 0FFh, 8Bh, 86h, 0A8h, 00h, 00h, 00h, 50h, 8Bh, 0CFh, 0E8h, 04h, 0BDh, 0CAh, 0FFh, 8Bh
    db 0Dh, 6Ch, 70h, 2Fh, 01h, 0E8h, 0D7h, 0C9h, 0CBh, 0FFh, 84h, 0C0h, 74h, 1Ah, 8Bh, 0Dh
    db 48h, 70h, 2Fh, 01h, 8Ah, 41h, 08h, 84h, 0C0h, 75h, 0Dh, 8Bh, 0Dh, 6Ch, 70h, 2Fh
    db 01h, 5Fh, 5Eh, 0E9h, 30h, 2Ah, 0CCh, 0FFh, 6Ah, 00h, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 2Ah
    db 6Eh, 0C9h, 0FFh, 8Bh, 0CFh, 0E8h, 0Eh, 8Eh, 0C8h, 0FFh, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h
    db 0E8h, 20h, 66h, 0C9h, 0FFh, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 6Ah, 00h, 0E8h, 0F5h, 3Ch
    db 0CAh, 0FFh, 5Fh, 5Eh, 0C3h
?d_003855f0@@YAXXZ ENDP

; ghidra: FUN_007859b0  retail @ 0x003859B0 size 216
public ?d_003859b0@@YAXXZ
?d_003859b0@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0BDh, 59h
    db 78h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 0C8h, 0B2h, 0C8h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 11h, 6Eh, 0CAh, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 01h, 6Eh, 0CAh, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 57h, 33h
    db 0C8h, 0FFh, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 6Ah, 01h
    db 6Ah, 05h, 0E8h, 0FDh, 37h, 0CCh, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h, 31h, 0C0h, 74h
    db 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h, 00h, 31h, 0C0h
    db 40h, 74h, 06h, 8Bh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 74h, 08h, 8Bh, 45h, 0F8h
    db 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 0B6h, 0FCh, 0C9h, 0FFh
    db 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0BDh, 59h, 78h, 00h
    db 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh, 0CDh, 0CEh, 58h
    db 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_003859b0@@YAXXZ ENDP

; ghidra: FUN_00785ae0  retail @ 0x00385AE0 size 216
public ?d_00385ae0@@YAXXZ
?d_00385ae0@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0EDh, 5Ah
    db 78h, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 98h, 0B1h, 0C8h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 0E1h, 6Ch, 0CAh, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 0D1h, 6Ch, 0CAh, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 5Eh, 80h
    db 0CAh, 0FFh, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 6Ah, 0Dh
    db 6Ah, 05h, 0E8h, 0CDh, 36h, 0CCh, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h, 31h, 0C0h, 74h
    db 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h, 00h, 31h, 0C0h
    db 74h, 06h, 8Bh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 40h, 74h, 08h, 8Bh, 45h, 0F8h
    db 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 86h, 0FBh, 0C9h, 0FFh
    db 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0EDh, 5Ah, 78h, 00h
    db 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh, 0CDh, 0CEh, 58h
    db 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_00385ae0@@YAXXZ ENDP

; ghidra: FUN_00785f20  retail @ 0x00385F20 size 35
public ?d_00385f20@@YAXXZ
?d_00385f20@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 81h, 0C1h, 18h, 04h, 00h, 00h, 51h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 08h, 00h, 00h, 00h, 00h, 0E8h, 0C4h, 24h, 50h, 00h, 8Bh, 0C6h, 5Eh, 59h
    db 0C2h, 04h, 00h
?d_00385f20@@YAXXZ ENDP

; ghidra: FUN_00785f50  retail @ 0x00385F50 size 77
public ?d_00385f50@@YAXXZ
?d_00385f50@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0ABh, 0B8h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0C3h, 19h, 50h, 00h, 8Dh, 4Eh, 04h
    db 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0B3h, 19h, 50h, 00h, 8Bh, 4Ch, 24h
    db 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00385f50@@YAXXZ ENDP

; ghidra: FUN_00785fb0  retail @ 0x00385FB0 size 151
public ?d_00385fb0@@YAXXZ
?d_00385fb0@@YAXXZ PROC
    db 8Bh, 0C1h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 33h, 0C9h, 88h, 08h, 89h, 48h, 04h, 89h
    db 48h, 08h, 0DDh, 58h, 50h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 88h, 48h, 0Ch, 0DDh, 58h
    db 58h, 89h, 48h, 10h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 88h, 48h, 14h, 0DDh, 58h, 60h
    db 89h, 48h, 18h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 89h, 48h, 1Ch, 0DDh, 58h, 68h, 89h
    db 48h, 20h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 89h, 48h, 24h, 0DDh, 58h, 70h, 88h, 48h
    db 28h, 0DDh, 05h, 58h, 5Fh, 08h, 01h, 89h, 48h, 30h, 0DDh, 58h, 78h, 89h, 48h, 34h
    db 0DDh, 05h, 58h, 5Fh, 08h, 01h, 89h, 48h, 38h, 0DDh, 98h, 80h, 00h, 00h, 00h, 89h
    db 48h, 3Ch, 89h, 48h, 40h, 89h, 48h, 44h, 89h, 48h, 48h, 89h, 48h, 4Ch, 89h, 88h
    db 88h, 00h, 00h, 00h, 89h, 88h, 8Ch, 00h, 00h, 00h, 89h, 88h, 90h, 00h, 00h, 00h
    db 89h, 88h, 94h, 00h, 00h, 00h, 0C3h
?d_00385fb0@@YAXXZ ENDP

; ghidra: FUN_00786090  retail @ 0x00386090 size 65
public ?d_00386090@@YAXXZ
?d_00386090@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 02h, 85h, 0C0h, 74h, 28h, 66h, 83h, 78h, 04h, 00h, 74h
    db 21h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 53h, 8Ah, 98h, 7Dh, 0Ah, 00h, 00h, 84h, 0DBh, 5Bh
    db 75h, 10h, 0C6h, 41h, 6Dh, 01h, 89h, 54h, 24h, 04h, 83h, 0C1h, 70h, 0E9h, 0CEh, 1Bh
    db 50h, 00h, 0C6h, 41h, 6Dh, 00h, 83h, 0C1h, 70h, 0E8h, 72h, 18h, 50h, 00h, 0C2h, 04h
    db 00h
?d_00386090@@YAXXZ ENDP

; ghidra: FUN_007860f0  retail @ 0x003860F0 size 128
public ?d_003860f0@@YAXXZ
?d_003860f0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 08h, 8Bh, 01h, 85h, 0C0h, 74h, 4Ah, 66h, 83h, 78h
    db 04h, 00h, 74h, 43h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 90h, 7Dh, 0Ah, 00h, 00h, 84h
    db 0D2h, 75h, 34h, 51h, 8Dh, 8Eh, 80h, 00h, 00h, 00h, 0C6h, 46h, 6Dh, 01h, 0E8h, 6Dh
    db 1Bh, 50h, 00h, 8Bh, 4Ch, 24h, 0Ch, 51h, 8Dh, 8Eh, 84h, 00h, 00h, 00h, 0E8h, 5Dh
    db 1Bh, 50h, 00h, 8Bh, 54h, 24h, 10h, 52h, 8Dh, 8Eh, 88h, 00h, 00h, 00h, 0E8h, 4Dh
    db 1Bh, 50h, 00h, 5Eh, 0C2h, 0Ch, 00h, 8Dh, 8Eh, 80h, 00h, 00h, 00h, 0C6h, 46h, 6Dh
    db 00h, 0E8h, 0EAh, 17h, 50h, 00h, 8Dh, 8Eh, 84h, 00h, 00h, 00h, 0E8h, 0DFh, 17h, 50h
    db 00h, 8Dh, 8Eh, 88h, 00h, 00h, 00h, 0E8h, 0D4h, 17h, 50h, 00h, 5Eh, 0C2h, 0Ch, 00h
?d_003860f0@@YAXXZ ENDP

; ghidra: FUN_00786190  retail @ 0x00386190 size 689
public ?d_00386190@@YAXXZ
?d_00386190@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Bh, 0B9h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 8Bh, 86h, 0Ch, 01h, 00h, 00h, 83h
    db 0F8h, 07h, 0Fh, 87h, 75h, 02h, 00h, 00h, 0FFh, 24h, 85h, 44h, 64h, 78h, 00h, 0A1h
    db 0E8h, 19h, 2Fh, 01h, 8Bh, 88h, 0B8h, 01h, 00h, 00h, 85h, 0C9h, 74h, 37h, 6Ah, 10h
    db 0E8h, 5Bh, 0BDh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h
    db 24h, 10h, 00h, 00h, 00h, 00h, 0Fh, 84h, 41h, 02h, 00h, 00h, 8Bh, 0C8h, 0E8h, 56h
    db 66h, 0CBh, 0FFh, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C2h, 04h, 00h, 6Ah, 18h, 0E8h, 24h, 0BDh, 4Fh, 00h, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0Fh, 84h, 0Ah
    db 02h, 00h, 00h, 8Dh, 4Eh, 7Ch, 51h, 83h, 0C6h, 78h, 56h, 8Bh, 0C8h, 0E8h, 8Ah, 0E8h
    db 0CBh, 0FFh, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 10h, 0C2h, 04h, 00h, 8Ah, 4Ch, 24h, 18h, 84h, 0C9h, 75h, 51h, 83h, 0F8h, 03h, 74h
    db 4Ch, 6Ah, 24h, 0E8h, 0D8h, 0BCh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 85h
    db 0C0h, 0C7h, 44h, 24h, 10h, 04h, 00h, 00h, 00h, 0Fh, 84h, 0BEh, 01h, 00h, 00h, 8Dh
    db 96h, 88h, 00h, 00h, 00h, 52h, 8Dh, 8Eh, 84h, 00h, 00h, 00h, 51h, 81h, 0C6h, 80h
    db 00h, 00h, 00h, 56h, 8Bh, 0C8h, 0E8h, 56h, 35h, 0C8h, 0FFh, 5Eh, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 0C7h, 44h, 24h
    db 18h, 00h, 00h, 00h, 00h, 8Dh, 54h, 24h, 18h, 52h, 0C7h, 44h, 24h, 14h, 02h, 00h
    db 00h, 00h, 0E8h, 0BCh, 01h, 0C9h, 0FFh, 6Ah, 24h, 0E8h, 72h, 0BCh, 4Fh, 00h, 83h, 0C4h
    db 08h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C6h, 44h, 24h, 10h, 03h, 74h, 1Ah, 68h, 50h
    db 6Eh, 33h, 01h, 68h, 50h, 6Eh, 33h, 01h, 8Dh, 4Ch, 24h, 20h, 51h, 8Bh, 0C8h, 0E8h
    db 0FDh, 34h, 0C8h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Dh, 4Ch, 24h, 18h, 0C7h, 44h
    db 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 45h, 16h, 50h, 00h, 8Bh, 0C6h, 5Eh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 68h
    db 0A4h, 00h, 00h, 00h, 0E8h, 17h, 0BCh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h
    db 0C7h, 44h, 24h, 10h, 05h, 00h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0FDh, 00h, 00h, 00h
    db 8Bh, 96h, 0Ch, 01h, 00h, 00h, 52h, 8Bh, 0C8h, 0E8h, 41h, 93h, 0CBh, 0FFh, 5Eh, 8Bh
    db 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
    db 0A1h, 98h, 49h, 2Fh, 01h, 85h, 0C0h, 74h, 41h, 68h, 0A4h, 00h, 00h, 00h, 0E8h, 0CDh
    db 0BBh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h, 10h
    db 06h, 00h, 00h, 00h, 0Fh, 84h, 0B3h, 00h, 00h, 00h, 8Bh, 8Eh, 0Ch, 01h, 00h, 00h
    db 51h, 8Bh, 0C8h, 0E8h, 0F7h, 92h, 0CBh, 0FFh, 5Eh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 68h, 0B4h, 00h, 00h, 00h, 0E8h
    db 8Ch, 0BBh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h
    db 10h, 07h, 00h, 00h, 00h, 74h, 76h, 8Bh, 0C8h, 0E8h, 4Bh, 0A0h, 0CAh, 0FFh, 5Eh, 8Bh
    db 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
    db 0A1h, 0CCh, 4Ah, 2Fh, 01h, 85h, 0C0h, 74h, 1Eh, 68h, 0A4h, 00h, 00h, 00h, 0E8h, 4Dh
    db 0BBh, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 0C7h, 44h, 24h, 10h, 08h, 00h
    db 00h, 00h, 0E9h, 31h, 0FFh, 0FFh, 0FFh, 68h, 74h, 01h, 00h, 00h, 0E8h, 2Fh, 0BBh, 4Fh
    db 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 09h, 00h
    db 00h, 00h, 74h, 19h, 8Bh, 0C8h, 0E8h, 0BAh, 3Dh, 0CAh, 0FFh, 5Eh, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh, 4Ch, 24h
    db 08h, 33h, 0C0h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h
    db 00h
?d_00386190@@YAXXZ ENDP

; ghidra: FUN_00786de0  retail @ 0x00386DE0 size 425
public ?d_00386de0@@YAXXZ
?d_00386de0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 33h, 0BAh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 10h, 02h, 00h, 00h, 53h, 57h, 0A1h, 94h, 15h
    db 2Fh, 01h, 85h, 0C0h, 0C7h, 84h, 24h, 20h, 02h, 00h, 00h, 00h, 00h, 00h, 00h, 0Fh
    db 84h, 44h, 01h, 00h, 00h, 33h, 0C0h, 0B9h, 41h, 00h, 00h, 00h, 8Dh, 7Ch, 24h, 10h
    db 0F3h, 0ABh, 8Bh, 84h, 24h, 28h, 02h, 00h, 00h, 85h, 0C0h, 8Dh, 48h, 08h, 75h, 05h
    db 0B9h, 8Bh, 38h, 07h, 01h, 8Dh, 54h, 24h, 10h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Ah, 01h, 41h, 88h, 02h, 42h, 84h, 0C0h, 75h, 0F6h, 6Ah, 00h, 0FFh, 15h, 30h, 8Fh
    db 35h, 01h, 8Bh, 0Dh, 24h, 0D5h, 2Eh, 01h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h
    db 40h, 8Dh, 4Ch, 24h, 10h, 51h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 51h, 1Dh, 50h, 00h, 8Bh
    db 0Dh, 90h, 0F1h, 2Eh, 01h, 8Dh, 54h, 24h, 08h, 52h, 0C6h, 84h, 24h, 24h, 02h, 00h
    db 00h, 01h, 0E8h, 15h, 0D1h, 0C9h, 0FFh, 8Dh, 4Ch, 24h, 08h, 8Ah, 0D8h, 0C6h, 84h, 24h
    db 20h, 02h, 00h, 00h, 00h, 0E8h, 0A6h, 0Ah, 50h, 00h, 84h, 0DBh, 74h, 22h, 0A1h, 90h
    db 0F1h, 2Eh, 01h, 8Bh, 40h, 1Ch, 85h, 0C0h, 8Dh, 48h, 08h, 75h, 05h, 0B9h, 8Bh, 38h
    db 07h, 01h, 8Dh, 54h, 24h, 10h, 8Ah, 01h, 41h, 88h, 02h, 42h, 84h, 0C0h, 75h, 0F6h
    db 8Dh, 44h, 24h, 10h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h
    db 83h, 0F8h, 04h, 0Fh, 8Ch, 80h, 00h, 00h, 00h, 8Dh, 4Ch, 04h, 0Ch, 8Dh, 54h, 24h
    db 10h, 3Bh, 0CAh, 76h, 13h, 8Ah, 01h, 3Ch, 5Ch, 74h, 0Dh, 3Ch, 2Fh, 74h, 09h, 49h
    db 8Dh, 44h, 24h, 10h, 3Bh, 0C8h, 77h, 0EDh, 0C6h, 01h, 00h, 8Dh, 4Ch, 24h, 10h, 51h
    db 8Dh, 94h, 24h, 18h, 01h, 00h, 00h, 68h, 00h, 0AFh, 0Eh, 01h, 52h, 0FFh, 15h, 8Ch
    db 94h, 35h, 01h, 8Bh, 0Dh, 48h, 0CBh, 34h, 01h, 83h, 0C4h, 0Ch, 8Dh, 84h, 24h, 14h
    db 01h, 00h, 00h, 50h, 0E8h, 77h, 17h, 64h, 00h, 84h, 0C0h, 74h, 21h, 51h, 8Dh, 94h
    db 24h, 18h, 01h, 00h, 00h, 89h, 64h, 24h, 10h, 8Bh, 0CCh, 52h, 0E8h, 7Fh, 1Ch, 50h
    db 00h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 0E8h, 43h, 9Dh, 0C8h, 0FFh, 0EBh, 0Bh, 8Bh, 0Dh
    db 0CCh, 0F4h, 2Eh, 01h, 0E8h, 8Ch, 0BBh, 0C7h, 0FFh, 8Dh, 8Ch, 24h, 28h, 02h, 00h, 00h
    db 0C7h, 84h, 24h, 20h, 02h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D0h, 09h, 50h, 00h
    db 8Bh, 8Ch, 24h, 18h, 02h, 00h, 00h, 5Fh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh
    db 81h, 0C4h, 1Ch, 02h, 00h, 00h, 0C2h, 04h, 00h
?d_00386de0@@YAXXZ ENDP

; ghidra: FUN_007870f0  retail @ 0x003870F0 size 45
public ?d_003870f0@@YAXXZ
?d_003870f0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 50h, 81h, 0C1h, 70h, 01h, 00h, 00h, 0C7h, 44h, 24h
    db 08h, 00h, 00h, 00h, 00h, 0E8h, 39h, 0D8h, 0C8h, 0FFh, 8Bh, 74h, 24h, 0Ch, 50h, 8Bh
    db 0CEh, 0E8h, 4Ah, 0Ah, 50h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 08h, 00h
?d_003870f0@@YAXXZ ENDP

; ghidra: FUN_00787160  retail @ 0x00387160 size 38
public ?d_00387160@@YAXXZ
?d_00387160@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 50h, 56h, 81h, 0C1h, 70h, 01h
    db 00h, 00h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 8Eh, 39h, 0CAh, 0FFh, 8Bh
    db 0C6h, 5Eh, 59h, 0C2h, 08h, 00h
?d_00387160@@YAXXZ ENDP

; ghidra: FUN_00787190  retail @ 0x00387190 size 38
public ?d_00387190@@YAXXZ
?d_00387190@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 50h, 56h, 81h, 0C1h, 70h, 01h
    db 00h, 00h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 0E8h, 0Dh, 0EAh, 0C9h, 0FFh, 8Bh
    db 0C6h, 5Eh, 59h, 0C2h, 08h, 00h
?d_00387190@@YAXXZ ENDP

; ghidra: FUN_00787960  retail @ 0x00387960 size 75
public ?d_00387960@@YAXXZ
?d_00387960@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 78h, 0BAh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 8Dh, 44h, 24h, 10h, 83h, 0C1h, 1Ch, 50h, 0C7h, 44h, 24h
    db 0Ch, 00h, 00h, 00h, 00h, 0E8h, 06h, 03h, 50h, 00h, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h
    db 24h, 08h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0A5h, 0FFh, 4Fh, 00h, 8Bh, 0Ch, 24h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_00387960@@YAXXZ ENDP

; ghidra: FUN_007879c0  retail @ 0x003879C0 size 32
public ?d_003879c0@@YAXXZ
?d_003879c0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 83h, 0C1h, 28h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 08h
    db 00h, 00h, 00h, 00h, 0E8h, 27h, 0Ah, 50h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h, 00h
?d_003879c0@@YAXXZ ENDP

; ghidra: FUN_00787d90  retail @ 0x00387D90 size 148
public ?d_00387d90@@YAXXZ
?d_00387d90@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0BEh, 0BAh, 01h, 01h, 50h, 8Bh, 44h
    db 24h, 10h, 85h, 0C0h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 56h, 7Ch, 26h, 8Bh, 51h
    db 58h, 8Bh, 71h, 54h, 2Bh, 0D6h, 0C1h, 0FAh, 02h, 3Bh, 0C2h, 73h, 17h, 8Bh, 0CEh, 8Dh
    db 04h, 81h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h
    db 0Ch, 0C2h, 04h, 00h, 8Ah, 0Dh, 90h, 0Ah, 2Fh, 01h, 0B8h, 01h, 00h, 00h, 00h, 84h
    db 0C8h, 75h, 2Ah, 09h, 05h, 90h, 0Ah, 2Fh, 01h, 68h, 64h, 0B0h, 0Eh, 01h, 0B9h, 8Ch
    db 0Ah, 2Fh, 01h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0C0h, 0Dh, 50h, 00h
    db 68h, 60h, 0FEh, 06h, 01h, 0E8h, 1Ch, 0F0h, 66h, 00h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h
    db 04h, 0B8h, 8Ch, 0Ah, 2Fh, 01h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h
    db 0Ch, 0C2h, 04h, 00h
?d_00387d90@@YAXXZ ENDP

; ghidra: FUN_00787f20  retail @ 0x00387F20 size 45
public ?d_00387f20@@YAXXZ
?d_00387f20@@YAXXZ PROC
    db 56h, 8Bh, 31h, 6Ah, 0Ch, 0E8h, 16h, 66h, 4Ah, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h
    db 85h, 0C9h, 74h, 08h, 8Bh, 54h, 24h, 08h, 8Bh, 12h, 89h, 11h, 8Bh, 4Eh, 04h, 89h
    db 30h, 89h, 48h, 04h, 89h, 01h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h
?d_00387f20@@YAXXZ ENDP

; ghidra: FUN_007881e0  retail @ 0x003881E0 size 173
public ?d_003881e0@@YAXXZ
?d_003881e0@@YAXXZ PROC
    db 51h, 56h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0Fh, 31h, 89h, 44h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 04h, 95h, 6Ch, 44h, 2Bh, 01h, 8Bh, 14h
    db 95h, 80h, 44h, 2Bh, 01h, 89h, 11h, 8Bh, 54h, 24h, 0Ch, 0C7h, 41h, 04h, 81h, 12h
    db 8Ch, 40h, 0C7h, 41h, 08h, 85h, 12h, 8Ch, 40h, 0C7h, 41h, 0Ch, 81h, 12h, 8Ch, 40h
    db 8Bh, 12h, 89h, 51h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 51h, 14h, 8Bh, 0D0h
    db 0Fh, 0AFh, 0D0h, 81h, 0F2h, 81h, 12h, 8Ch, 40h, 89h, 51h, 04h, 0Fh, 0AFh, 0D0h, 81h
    db 0F2h, 85h, 12h, 8Ch, 40h, 8Bh, 71h, 10h, 89h, 51h, 08h, 0Fh, 0AFh, 0D0h, 81h, 0F2h
    db 81h, 12h, 8Ch, 40h, 89h, 51h, 0Ch, 0Fh, 0AFh, 0D0h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D0h, 89h, 71h, 10h, 8Bh, 71h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D0h, 89h, 71h
    db 14h, 8Bh, 71h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D0h, 8Bh, 41h, 1Ch, 33h, 0C2h
    db 89h, 71h, 18h, 89h, 41h, 1Ch, 8Bh, 0C1h, 5Eh, 59h, 0C2h, 08h, 00h
?d_003881e0@@YAXXZ ENDP

; ghidra: FUN_007882c0  retail @ 0x003882C0 size 173
public ?d_003882c0@@YAXXZ
?d_003882c0@@YAXXZ PROC
    db 51h, 56h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0Fh, 31h, 89h, 44h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 04h, 95h, 94h, 44h, 2Bh, 01h, 8Bh, 14h
    db 95h, 0A8h, 44h, 2Bh, 01h, 89h, 11h, 8Bh, 54h, 24h, 0Ch, 0C7h, 41h, 04h, 81h, 12h
    db 8Ch, 40h, 0C7h, 41h, 08h, 85h, 12h, 8Ch, 40h, 0C7h, 41h, 0Ch, 8Dh, 42h, 84h, 5Ch
    db 8Bh, 12h, 89h, 51h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 51h, 14h, 8Bh, 0D0h
    db 0Fh, 0AFh, 0D0h, 81h, 0F2h, 81h, 12h, 8Ch, 40h, 89h, 51h, 04h, 0Fh, 0AFh, 0D0h, 81h
    db 0F2h, 85h, 12h, 8Ch, 40h, 8Bh, 71h, 10h, 89h, 51h, 08h, 0Fh, 0AFh, 0D0h, 81h, 0F2h
    db 8Dh, 42h, 84h, 5Ch, 89h, 51h, 0Ch, 0Fh, 0AFh, 0D0h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D0h, 89h, 71h, 10h, 8Bh, 71h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D0h, 89h, 71h
    db 14h, 8Bh, 71h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D0h, 8Bh, 41h, 1Ch, 33h, 0C2h
    db 89h, 71h, 18h, 89h, 41h, 1Ch, 8Bh, 0C1h, 5Eh, 59h, 0C2h, 08h, 00h
?d_003882c0@@YAXXZ ENDP

; ghidra: FUN_007884b0  retail @ 0x003884B0 size 81
public ?d_003884b0@@YAXXZ
?d_003884b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E1h, 0BAh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 74h, 24h, 18h, 89h, 74h, 24h, 04h, 85h
    db 0F6h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 16h, 57h, 8Bh, 7Ch, 24h, 20h
    db 57h, 8Bh, 0CEh, 0E8h, 78h, 0F6h, 4Fh, 00h, 66h, 8Bh, 47h, 04h, 66h, 89h, 46h, 04h
    db 5Fh, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C3h
?d_003884b0@@YAXXZ ENDP

; ghidra: FUN_00788520  retail @ 0x00388520 size 41
public ?d_00388520@@YAXXZ
?d_00388520@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 56h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 08h, 8Bh, 0CCh, 50h
    db 0E8h, 2Bh, 0F6h, 4Fh, 00h, 8Bh, 0CEh, 0E8h, 55h, 67h, 0C8h, 0FFh, 33h, 0D2h, 0F7h, 74h
    db 24h, 10h, 5Eh, 8Bh, 0C2h, 59h, 0C2h, 08h, 00h
?d_00388520@@YAXXZ ENDP

; ghidra: FUN_00788560  retail @ 0x00388560 size 41
public ?d_00388560@@YAXXZ
?d_00388560@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 56h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 08h, 8Bh, 0CCh, 50h
    db 0E8h, 0EBh, 0F5h, 4Fh, 00h, 8Bh, 0CEh, 0E8h, 15h, 67h, 0C8h, 0FFh, 33h, 0D2h, 0F7h, 74h
    db 24h, 10h, 5Eh, 8Bh, 0C2h, 59h, 0C2h, 08h, 00h
?d_00388560@@YAXXZ ENDP

; ghidra: FUN_007886d0  retail @ 0x003886D0 size 77
public ?d_003886d0@@YAXXZ
?d_003886d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 68h, 0BBh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 33h, 0C0h, 89h, 74h, 24h, 04h, 89h
    db 46h, 04h, 89h, 44h, 24h, 10h, 8Bh, 44h, 24h, 18h, 50h, 8Dh, 4Eh, 08h, 0C7h, 06h
    db 74h, 0B0h, 0Eh, 01h, 0E8h, 57h, 0F4h, 4Fh, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 0C6h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_003886d0@@YAXXZ ENDP

; ghidra: FUN_00788770  retail @ 0x00388770 size 67
public ?d_00388770@@YAXXZ
?d_00388770@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 88h, 0BBh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 08h
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0A3h, 0F1h, 4Fh, 00h, 8Bh, 4Ch, 24h
    db 08h, 0C7h, 06h, 58h, 0ADh, 0Eh, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_00388770@@YAXXZ ENDP

; ghidra: FUN_007887d0  retail @ 0x003887D0 size 55
public ?d_003887d0@@YAXXZ
?d_003887d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 27h, 8Bh, 06h, 8Bh, 48h, 04h, 51h
    db 8Bh, 0CEh, 0E8h, 0FEh, 0D3h, 0C8h, 0FFh, 8Bh, 06h, 89h, 40h, 08h, 8Bh, 16h, 0C7h, 42h
    db 04h, 00h, 00h, 00h, 00h, 8Bh, 06h, 89h, 40h, 0Ch, 0C7h, 46h, 04h, 00h, 00h, 00h
    db 00h, 0C6h, 46h, 10h, 01h, 5Eh, 0C3h
?d_003887d0@@YAXXZ ENDP

; ghidra: FUN_00788820  retail @ 0x00388820 size 245
public ?d_00388820@@YAXXZ
?d_00388820@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 0BBh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 57h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h
    db 8Bh, 01h, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0FFh, 50h, 78h, 8Bh, 0E8h, 85h
    db 0EDh, 74h, 76h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CDh, 0E8h, 0Dh, 7Ah, 0C8h, 0FFh, 8Bh
    db 4Ch, 24h, 24h, 85h, 0C9h, 74h, 09h, 0Fh, 0B7h, 59h, 04h, 8Dh, 79h, 08h, 0EBh, 07h
    db 33h, 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h
    db 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 8Bh, 0F0h, 33h, 0C0h, 0F3h
    db 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 06h, 2Bh, 0D3h, 8Bh, 0C2h
    db 85h, 0C0h, 8Dh, 4Ch, 24h, 10h, 0Fh, 94h, 0C3h, 0E8h, 82h, 0F0h, 4Fh, 00h, 84h, 0DBh
    db 75h, 2Dh, 8Bh, 6Dh, 1Ch, 85h, 0EDh, 75h, 8Ah, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h, 24h
    db 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 66h, 0F0h, 4Fh, 00h, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 8Dh
    db 4Ch, 24h, 24h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 40h, 0F0h, 4Fh, 00h
    db 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 10h, 0C3h
?d_00388820@@YAXXZ ENDP

; ghidra: FUN_00788a90  retail @ 0x00388A90 size 34
public ?d_00388a90@@YAXXZ
?d_00388a90@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 17h, 8Bh, 40h, 74h, 8Dh, 54h, 24h, 04h, 52h
    db 81h, 0C1h, 0B0h, 00h, 00h, 00h, 89h, 44h, 24h, 08h, 0E8h, 33h, 72h, 0CBh, 0FFh, 0C2h
    db 04h, 00h
?d_00388a90@@YAXXZ ENDP

; ghidra: FUN_00788ac0  retail @ 0x00388AC0 size 222
public ?d_00388ac0@@YAXXZ
?d_00388ac0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E8h, 0BBh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 55h, 56h, 57h, 8Bh, 89h, 0ACh, 01h, 00h, 00h
    db 8Bh, 29h, 3Bh, 0E9h, 89h, 4Ch, 24h, 10h, 74h, 61h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 7Ch, 24h, 24h, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 5Fh, 04h, 83h, 0C7h, 08h, 0EBh
    db 07h, 33h, 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 45h, 08h, 85h, 0C0h, 74h, 06h, 0Fh
    db 0B7h, 50h, 04h, 0EBh, 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh
    db 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h
    db 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h
    db 74h, 31h, 8Bh, 6Dh, 00h, 3Bh, 6Ch, 24h, 10h, 75h, 0A5h, 8Dh, 4Ch, 24h, 24h, 0C7h
    db 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0E4h, 0EDh, 4Fh, 00h, 5Fh, 5Eh, 5Dh, 33h
    db 0C0h, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h
    db 0C2h, 04h, 00h, 8Dh, 4Ch, 24h, 24h, 8Dh, 75h, 08h, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 0B9h, 0EDh, 4Fh, 00h, 8Bh, 4Ch, 24h, 14h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh
    db 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00388ac0@@YAXXZ ENDP

; ghidra: FUN_00788be0  retail @ 0x00388BE0 size 33
public ?d_00388be0@@YAXXZ
?d_00388be0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 56h, 81h, 0C1h, 70h, 01h, 00h, 00h, 0C7h, 44h, 24h
    db 08h, 00h, 00h, 00h, 00h, 0E8h, 0Dh, 89h, 0CAh, 0FFh, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 04h
    db 00h
?d_00388be0@@YAXXZ ENDP

; ghidra: FUN_00788c10  retail @ 0x00388C10 size 1744
_TEXT ENDS
_TEXT$d00788c10 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00788C10 size 1744
public ?d_00388c10@@YAXXZ
?d_00388c10@@YAXXZ PROC
    db 06Ah, 0FFh, 064h, 0A1h, 000h, 000h, 000h, 000h, 068h
    dd g_Va0101BC42
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 028h, 001h, 000h, 000h, 053h, 055h
    db 08Bh, 0E9h, 0BBh, 001h, 000h, 000h, 000h, 056h, 088h, 05Dh, 06Ch, 0A0h
    dd ?g_flag12ED4E8@@3_NA
    db 057h, 033h, 0FFh, 084h, 0C0h, 074h, 00Eh, 0A1h
    dd ?forcedCRCFrame@@3HA
    db 03Bh, 045h, 03Ch, 00Fh, 085h, 073h, 006h, 000h, 000h, 08Ah, 085h, 0A8h, 001h, 000h, 000h, 084h
    db 0C0h, 00Fh, 085h, 0D6h, 000h, 000h, 000h, 088h, 09Dh, 0A8h, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A
    call ?j_000365d4@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheScriptActions@@3PAVScriptActionsInterface@@A
    db 08Bh, 011h, 053h, 0FFh, 052h, 028h, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A
    db 03Bh, 0CFh, 074h, 013h
    call ?j_00043eeb@@YAXXZ
    db 03Bh, 0C3h, 075h, 00Ah, 0A1h
    dd ?forcedCRCFrame@@3HA
    db 03Bh, 045h, 03Ch, 075h, 06Dh, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 057h, 068h
    dd g_Va010EB378
    db 08Dh, 044h, 024h, 02Ch, 050h, 0FFh, 052h, 028h, 08Bh, 0F0h, 08Bh, 00Dh
    dd ?TheGameText@@3PAVBfmeGameText@@A
    db 08Bh, 011h, 057h, 068h
    dd g_Va010EB364
    db 08Dh, 044h, 024h, 034h, 050h, 089h, 0BCh, 024h, 04Ch, 001h, 000h, 000h, 0FFh, 052h, 028h, 056h
    db 050h, 06Ah, 003h, 088h, 09Ch, 024h, 04Ch, 001h, 000h, 000h
    call ?j_00020b21@@YAXXZ
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 02Ch, 0C6h, 084h, 024h, 040h, 001h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 08Dh, 04Ch, 024h, 024h, 0C7h, 084h, 024h, 040h, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@G@@AAEXXZ
    db 089h, 0BDh, 0A4h, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A
    db 03Bh, 0CFh, 074h, 014h
    call ?j_00043eeb@@YAXXZ
    db 03Bh, 0C3h, 075h, 00Bh, 08Bh, 00Dh
    dd ?forcedCRCFrame@@3HA
    db 03Bh, 04Dh, 03Ch, 075h, 00Bh, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A
    db 08Bh, 011h, 0FFh, 052h, 030h, 08Bh, 09Ch, 024h, 048h, 001h, 000h, 000h, 03Bh, 0DFh, 00Fh, 084h
    db 080h, 005h, 000h, 000h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 08Bh, 040h, 008h, 03Bh, 0C7h, 08Dh, 048h, 008h, 075h, 024h, 0B9h
    dd ?Rva006A16B0Empty@@3PADA
    db 033h, 0C0h, 003h, 0C1h, 03Bh, 0C1h, 074h, 00Dh, 08Ah, 050h, 0FFh, 048h, 080h, 0FAh, 05Ch, 074h
    db 014h, 03Bh, 0C1h, 075h, 0F3h, 0C7h, 044h, 024h, 024h
    dd ??_7Rva007F01B0@@6B@
    db 0EBh, 00Bh, 00Fh, 0B7h, 040h, 004h, 0EBh, 0DDh, 040h, 089h, 044h, 024h, 024h, 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 041h, 00Ch, 083h, 0C0h, 01Ch, 050h, 08Dh, 04Ch, 024h, 01Ch
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 044h, 024h, 018h, 03Bh, 0C7h, 0C7h, 084h, 024h, 040h, 001h, 000h, 000h, 002h, 000h, 000h
    db 000h, 074h, 006h, 066h, 039h, 078h, 004h, 075h, 03Dh, 033h, 0C0h, 0C6h, 044h, 024h, 038h, 000h
    db 0B9h, 03Fh, 000h, 000h, 000h, 08Dh, 07Ch, 024h, 039h, 0F3h, 0ABh, 066h, 0ABh, 08Dh, 054h, 024h
    db 034h, 0AAh, 052h, 08Dh, 044h, 024h, 03Ch, 050h, 0C7h, 044h, 024h, 03Ch, 000h, 001h, 000h, 000h
    db 0FFh, 015h
    dd __imp__GetComputerNameA@8
    db 08Dh, 04Ch, 024h, 038h, 051h, 08Dh, 04Ch, 024h, 01Ch
    call ?j_00028bb9@@YAXXZ
    db 033h, 0FFh, 089h, 07Ch, 024h, 01Ch, 08Bh, 043h, 004h, 03Bh, 0C7h, 08Bh, 0B4h, 024h, 04Ch, 001h
    db 000h, 000h, 0C6h, 084h, 024h, 040h, 001h, 000h, 000h, 003h, 074h, 007h, 083h, 0C0h, 008h, 03Bh
    db 0C7h, 074h, 02Ah, 08Bh, 043h, 004h, 03Bh, 0C7h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 051h, 089h, 064h, 024h, 030h, 08Bh, 0CCh, 068h
    dd g_Va010EB358
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 024h, 052h, 0EBh, 017h, 056h, 051h, 089h, 064h, 024h, 030h, 08Bh, 0CCh, 068h
    dd g_Va010EB34C
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 024h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 00Ch, 089h, 07Ch, 024h, 014h, 03Bh, 0F7h, 08Bh, 044h, 024h, 018h, 0C6h, 084h, 024h
    db 040h, 001h, 000h, 000h, 004h, 076h, 047h, 03Bh, 0C7h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 04Ch, 024h, 024h, 050h, 08Bh, 044h, 024h, 020h, 03Bh, 0C7h, 051h, 074h, 005h, 083h, 0C0h
    db 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 051h, 089h, 064h, 024h, 038h, 08Bh, 0CCh, 068h
    dd g_Va010EB334
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 024h, 052h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 014h, 0EBh, 032h, 03Bh, 0C7h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 08Bh, 044h, 024h, 028h, 050h, 051h, 089h, 064h, 024h, 034h, 08Bh, 0CCh, 068h
    dd g_Va010EB320
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 020h, 051h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 010h, 08Bh, 044h, 024h, 014h, 03Bh, 0C7h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?Rva0134CB48FileSystem@@3PAVFileSystem@@A
    db 06Ah, 02Ah, 050h
    call ?openFile@FileSystem@@QAEPAVFile@@PBDH@Z
    db 08Bh, 0F0h, 03Bh, 0F7h, 00Fh, 084h, 07Fh, 003h, 000h, 000h, 08Dh, 054h, 024h, 030h, 052h, 08Bh
    db 0CBh
    call ?bfmeTakeEC@BfmeThingEC@@QAEHPAH@Z
    db 08Bh, 04Ch, 024h, 030h, 051h, 050h, 089h, 044h, 024h, 034h
    call ?createMemoryReadFile@@YAPAVFile@@PADH@Z
    db 083h, 0C4h, 008h, 03Bh, 0C7h, 089h, 044h, 024h, 028h, 00Fh, 084h, 055h, 003h, 000h, 000h, 089h
    db 07Ch, 024h, 010h, 08Bh, 09Ch, 024h, 04Ch, 001h, 000h, 000h, 03Bh, 0DFh, 0C6h, 084h, 024h, 040h
    db 001h, 000h, 000h, 005h, 00Fh, 086h, 08Fh, 000h, 000h, 000h, 0A0h
    dd g_Va012F4C68
    db 084h, 0C0h, 074h, 019h, 053h, 051h, 089h, 064h, 024h, 028h, 08Bh, 0CCh, 068h
    dd g_Va010EB2A8
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 054h, 024h, 018h, 052h, 0EBh, 044h, 08Bh, 045h, 03Ch, 039h, 005h
    dd ?forcedCRCFrame@@3HA
    db 075h, 022h, 050h, 053h, 051h, 089h, 064h, 024h, 02Ch, 08Bh, 0CCh, 068h
    dd g_Va010EB218
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 01Ch, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 010h, 0EBh, 01Fh, 053h, 051h, 089h, 064h, 024h, 028h, 08Bh, 0CCh, 068h
    dd g_Va010EB204
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 018h, 051h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 00Ch, 08Bh, 044h, 024h, 010h, 03Bh, 0C7h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h
    db 0C0h, 008h, 0EBh, 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Dh, 045h, 050h, 050h, 08Dh, 04Ch, 024h
    db 014h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 044h, 024h, 010h, 03Bh, 0C7h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h, 0C0h, 008h, 0EBh
    db 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Bh, 045h, 058h, 02Bh, 045h, 054h, 0C1h
    db 0F8h, 002h, 033h, 0FFh, 085h, 0C0h, 076h, 041h, 057h, 08Bh, 0CDh
    call ?j_00043072@@YAXXZ
    db 050h, 08Dh, 04Ch, 024h, 014h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h, 0C0h, 008h, 0EBh
    db 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Bh, 045h, 058h, 02Bh, 045h, 054h, 047h
    db 0C1h, 0F8h, 002h, 03Bh, 0F8h, 072h, 0BFh, 08Dh, 04Dh, 060h, 051h, 08Dh, 04Ch, 024h, 014h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h, 0C0h, 008h, 0EBh
    db 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 083h, 0C5h, 064h, 055h, 08Dh, 04Ch, 024h
    db 014h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 044h, 024h, 010h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h, 0C0h, 008h, 0EBh
    db 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 051h, 089h, 064h, 024h, 024h, 08Bh, 0CCh
    db 068h
    dd g_Va01080294
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 014h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 08Bh, 044h, 024h, 018h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h
    db 0C0h, 008h, 0EBh, 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 051h, 089h, 064h, 024h, 024h, 08Bh, 0CCh
    db 068h
    dd g_Va010EB168
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 014h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 08Bh, 044h, 024h, 018h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h
    db 0C0h, 008h, 0EBh, 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A
    db 053h, 056h
    call ?j_0000d9b8@@YAXXZ
    db 051h, 089h, 064h, 024h, 024h, 08Bh, 0CCh, 068h
    dd g_Va010EB120
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 014h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 08Bh, 044h, 024h, 018h, 083h, 0C4h, 008h, 085h, 0C0h, 074h, 009h, 00Fh, 0B7h, 048h, 004h, 083h
    db 0C0h, 008h, 0EBh, 007h, 033h, 0C9h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 016h, 051h, 050h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Bh, 07Ch, 024h, 028h, 056h, 057h
    call ?d_009d9d90@@YAXXZ
    db 08Bh, 007h, 083h, 0C4h, 008h, 08Bh, 0CFh, 0FFh, 050h, 008h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h
    db 008h, 0A0h
    dd ?g_binaryDeepCRC@@3DA
    db 084h, 0C0h, 00Fh, 084h, 0BFh, 000h, 000h, 000h, 085h, 0DBh, 08Bh, 044h, 024h, 018h, 076h, 047h
    db 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 08Bh, 044h, 024h, 028h, 050h, 08Bh, 044h, 024h, 024h, 085h, 0C0h, 074h, 005h, 083h, 0C0h
    db 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 051h, 089h, 064h, 024h, 030h, 08Bh, 0CCh, 068h
    dd g_Va010EB104
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 04Ch, 024h, 024h, 051h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 014h, 0EBh, 032h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 054h, 024h, 024h, 050h, 052h, 051h, 089h, 064h, 024h, 02Ch, 08Bh, 0CCh, 068h
    dd g_Va010EB0E8
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 020h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 010h, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h
    db 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 00Dh
    dd ?Rva0134CB48FileSystem@@3PAVFileSystem@@A
    db 06Ah, 042h, 050h
    call ?openFile@FileSystem@@QAEPAVFile@@PBDH@Z
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 026h, 08Bh, 044h, 024h, 030h, 08Bh, 04Ch, 024h, 02Ch, 08Bh, 016h
    db 050h, 051h, 08Bh, 0CEh, 0FFh, 052h, 010h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 008h, 08Bh, 044h
    db 024h, 02Ch, 050h, 0FFh, 015h
    dd __imp__free
    db 083h, 0C4h, 004h, 08Dh, 04Ch, 024h, 010h, 0C6h, 084h, 024h, 040h, 001h, 000h, 000h, 004h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 014h, 0C6h, 084h, 024h, 040h, 001h, 000h, 000h, 003h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 040h, 001h, 000h, 000h, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 018h, 0C7h, 084h, 024h, 040h, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 08Ch, 024h, 038h, 001h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 034h, 001h, 000h, 000h, 0C2h, 00Ch, 000h
?d_00388c10@@YAXXZ ENDP
_TEXT$d00788c10 ENDS
_TEXT SEGMENT

; ghidra: FUN_007897c0  retail @ 0x003897C0 size 100
public ?d_003897c0@@YAXXZ
?d_003897c0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 4Ch, 0C8h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 50h
    db 0C8h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 0D8h, 0C8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0D4h, 0C8h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 12h, 0F8h, 0C9h, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 32h, 0F8h, 0CBh, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_003897c0@@YAXXZ ENDP

; ghidra: FUN_00789840  retail @ 0x00389840 size 100
public ?d_00389840@@YAXXZ
?d_00389840@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 4Ch, 0C8h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 50h
    db 0C8h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 0D8h, 0C8h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 0D4h, 0C8h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 82h, 0E6h, 0C7h, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 97h, 29h, 0C9h, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_00389840@@YAXXZ ENDP

; ghidra: FUN_007898c0  retail @ 0x003898C0 size 281
public ?d_003898c0@@YAXXZ
?d_003898c0@@YAXXZ PROC
    db 83h, 0ECh, 18h, 8Bh, 44h, 24h, 1Ch, 53h, 8Bh, 59h, 04h, 56h, 8Bh, 71h, 08h, 57h
    db 8Dh, 79h, 04h, 2Bh, 0F3h, 0C1h, 0FEh, 02h, 3Bh, 0C6h, 89h, 74h, 24h, 14h, 0Fh, 86h
    db 0ECh, 00h, 00h, 00h, 6Ah, 00h, 89h, 44h, 24h, 2Ch, 8Bh, 44h, 24h, 2Ch, 50h, 8Dh
    db 4Ch, 24h, 30h, 51h, 68h, 0E0h, 58h, 07h, 01h, 68h, 70h, 58h, 07h, 01h, 0E8h, 56h
    db 0BDh, 0C8h, 0FFh, 83h, 0C4h, 14h, 3Dh, 0E0h, 58h, 07h, 01h, 0BBh, 0FBh, 0FFh, 0FFh, 0FFh
    db 74h, 02h, 8Bh, 18h, 3Bh, 0DEh, 89h, 5Ch, 24h, 0Ch, 0Fh, 86h, 0B0h, 00h, 00h, 00h
    db 55h, 8Dh, 54h, 24h, 2Ch, 52h, 8Bh, 0CFh, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h
    db 0E8h, 0F3h, 02h, 0C8h, 0FFh, 50h, 8Dh, 44h, 24h, 18h, 50h, 53h, 8Dh, 4Ch, 24h, 28h
    db 0E8h, 57h, 6Ah, 0C9h, 0FFh, 8Bh, 6Ch, 24h, 1Ch, 33h, 0DBh, 85h, 0F6h, 76h, 3Ch, 90h
    db 8Bh, 0Fh, 8Bh, 0Ch, 99h, 85h, 0C9h, 74h, 2Dh, 8Bh, 17h, 8Dh, 34h, 9Ah, 8Bh, 0FFh
    db 8Bh, 41h, 04h, 33h, 0D2h, 0F7h, 74h, 24h, 10h, 8Bh, 01h, 89h, 06h, 8Bh, 44h, 95h
    db 00h, 89h, 01h, 89h, 4Ch, 95h, 00h, 8Bh, 0Fh, 8Dh, 34h, 99h, 8Bh, 0Eh, 85h, 0C9h
    db 75h, 0DEh, 8Bh, 74h, 24h, 18h, 43h, 3Bh, 0DEh, 72h, 0C5h, 8Bh, 0Fh, 85h, 0C9h, 8Bh
    db 54h, 24h, 20h, 89h, 2Fh, 89h, 57h, 04h, 8Bh, 54h, 24h, 24h, 8Bh, 47h, 08h, 89h
    db 57h, 08h, 5Dh, 74h, 2Bh, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h
    db 00h, 00h, 76h, 12h, 51h, 0E8h, 0F6h, 84h, 4Fh, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 18h, 0C2h, 04h, 00h, 50h, 51h, 0E8h, 23h, 4Ch, 4Ah, 00h, 83h, 0C4h, 08h
    db 5Fh, 5Eh, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_003898c0@@YAXXZ ENDP

; ghidra: FUN_00789a20  retail @ 0x00389A20 size 111
public ?d_00389a20@@YAXXZ
?d_00389a20@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 57h, 40h, 50h, 0E8h, 0BFh, 72h, 0CBh
    db 0FFh, 8Bh, 5Eh, 04h, 8Bh, 4Eh, 08h, 8Bh, 54h, 24h, 18h, 8Bh, 02h, 2Bh, 0CBh, 0C1h
    db 0F9h, 02h, 33h, 0D2h, 0F7h, 0F1h, 8Bh, 46h, 04h, 6Ah, 0Ch, 8Bh, 0DAh, 8Bh, 0Ch, 98h
    db 89h, 4Ch, 24h, 14h, 0E8h, 0E7h, 4Ah, 4Ah, 00h, 8Bh, 54h, 24h, 1Ch, 8Bh, 0F8h, 52h
    db 8Dh, 6Fh, 04h, 55h, 0C7h, 07h, 00h, 00h, 00h, 00h, 0E8h, 05h, 36h, 0CAh, 0FFh, 8Bh
    db 44h, 24h, 1Ch, 89h, 07h, 8Bh, 4Eh, 04h, 89h, 3Ch, 99h, 8Bh, 46h, 10h, 83h, 0C4h
    db 0Ch, 40h, 5Fh, 89h, 46h, 10h, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_00389a20@@YAXXZ ENDP

; ghidra: FUN_0078a020  retail @ 0x0038A020 size 96
public ?d_0038a020@@YAXXZ
?d_0038a020@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0CBh, 0BCh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 0Ch, 8Bh, 0F1h, 0E8h, 0F0h, 7Eh, 4Fh, 00h
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h
    db 00h, 74h, 0Eh, 8Bh, 4Ch, 24h, 18h, 51h, 8Bh, 0C8h, 0E8h, 0D5h, 0C8h, 0CBh, 0FFh, 0EBh
    db 02h, 33h, 0C0h, 85h, 0C0h, 89h, 06h, 74h, 03h, 0FFh, 40h, 04h, 8Bh, 4Ch, 24h, 08h
    db 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_0038a020@@YAXXZ ENDP

; ghidra: FUN_0078a0c0  retail @ 0x0038A0C0 size 234
public ?d_0038a0c0@@YAXXZ
?d_0038a0c0@@YAXXZ PROC
    db 51h, 53h, 55h, 8Bh, 0E9h, 33h, 0C9h, 56h, 0B8h, 00h, 00h, 80h, 42h, 89h, 4Dh, 3Ch
    db 89h, 45h, 34h, 89h, 45h, 38h, 89h, 8Dh, 0A8h, 00h, 00h, 00h, 8Dh, 0B5h, 0C8h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 0Ch, 04h, 00h, 00h, 00h, 83h, 0CBh, 0FFh, 57h, 8Bh, 0FFh
    db 8Bh, 46h, 0FCh, 3Bh, 06h, 74h, 11h, 8Bh, 08h, 89h, 59h, 1Ch, 89h, 59h, 18h, 8Bh
    db 0Eh, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0EFh, 8Bh, 06h, 3Bh, 0C0h, 8Bh, 4Eh, 0FCh, 75h
    db 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch, 94h
    db 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 06h, 8Bh, 44h, 24h, 10h, 83h, 0C6h, 0Ch
    db 48h, 89h, 44h, 24h, 10h, 75h, 0B9h, 8Bh, 85h, 0F4h, 00h, 00h, 00h, 3Bh, 85h, 0F8h
    db 00h, 00h, 00h, 5Fh, 74h, 15h, 8Bh, 08h, 89h, 59h, 1Ch, 89h, 59h, 18h, 8Bh, 8Dh
    db 0F8h, 00h, 00h, 00h, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0EBh, 8Bh, 85h, 0F8h, 00h, 00h
    db 00h, 3Bh, 0C0h, 8Bh, 8Dh, 0F4h, 00h, 00h, 00h, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh
    db 0F0h, 2Bh, 0F0h, 56h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h
    db 0C6h, 89h, 85h, 0F8h, 00h, 00h, 00h, 8Ah, 44h, 24h, 14h, 84h, 0C0h, 0C7h, 85h, 00h
    db 01h, 00h, 00h, 00h, 00h, 00h, 00h, 75h, 0Ah, 0C7h, 85h, 08h, 01h, 00h, 00h, 01h
    db 00h, 00h, 00h, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_0038a0c0@@YAXXZ ENDP

; ghidra: FUN_0078a6f0  retail @ 0x0038A6F0 size 92
public ?d_0038a6f0@@YAXXZ
?d_0038a6f0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 0F9h, 8Bh, 0B7h, 5Ch, 01h, 00h, 00h, 3Bh, 0B7h, 60h, 01h, 00h, 00h
    db 74h, 16h, 8Bh, 0Eh, 6Ah, 01h, 0E8h, 9Dh, 3Dh, 0C8h, 0FFh, 8Bh, 87h, 60h, 01h, 00h
    db 00h, 83h, 0C6h, 04h, 3Bh, 0F0h, 75h, 0EAh, 8Bh, 87h, 60h, 01h, 00h, 00h, 3Bh, 0C0h
    db 8Bh, 8Fh, 5Ch, 01h, 00h, 00h, 75h, 09h, 89h, 8Fh, 60h, 01h, 00h, 00h, 5Fh, 5Eh
    db 0C3h, 8Bh, 0F0h, 2Bh, 0F0h, 56h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 03h, 0C6h
    db 83h, 0C4h, 0Ch, 89h, 87h, 60h, 01h, 00h, 00h, 5Fh, 5Eh, 0C3h
?d_0038a6f0@@YAXXZ ENDP

; ghidra: FUN_0078a9f0  retail @ 0x0038A9F0 size 737
public ?d_0038a9f0@@YAXXZ
?d_0038a9f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A0h, 0BDh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 48h, 8Bh, 44h, 24h, 5Ch, 8Bh, 40h, 10h, 53h
    db 55h, 8Bh, 6Ch, 24h, 68h, 56h, 33h, 0DBh, 57h, 89h, 5Ch, 24h, 10h, 8Dh, 70h, 01h
    db 56h, 51h, 89h, 64h, 24h, 74h, 8Bh, 0CCh, 68h, 0E4h, 32h, 08h, 01h, 89h, 5Ch, 24h
    db 6Ch, 0E8h, 8Ah, 0E1h, 4Fh, 00h, 8Dh, 4Ch, 24h, 18h, 51h, 0E8h, 0B0h, 0E5h, 4Fh, 00h
    db 83h, 0C4h, 0Ch, 89h, 5Ch, 24h, 6Ch, 56h, 51h, 89h, 64h, 24h, 20h, 8Bh, 0CCh, 68h
    db 10h, 0B4h, 0Eh, 01h, 0C6h, 44h, 24h, 6Ch, 01h, 0E8h, 62h, 0E1h, 4Fh, 00h, 8Dh, 54h
    db 24h, 74h, 52h, 0E8h, 88h, 0E5h, 4Fh, 00h, 83h, 0C4h, 08h, 8Dh, 44h, 24h, 14h, 89h
    db 64h, 24h, 1Ch, 8Bh, 0CCh, 50h, 0E8h, 0E5h, 0D0h, 4Fh, 00h, 0E8h, 0A0h, 0DDh, 0FFh, 0FFh
    db 8Dh, 54h, 24h, 70h, 89h, 64h, 24h, 1Ch, 8Bh, 0CCh, 52h, 8Bh, 0F0h, 0E8h, 0CEh, 0D0h
    db 4Fh, 00h, 0E8h, 89h, 0DDh, 0FFh, 0FFh, 83h, 0C4h, 04h, 3Bh, 0F3h, 8Bh, 0F8h, 0Fh, 84h
    db 0FCh, 01h, 00h, 00h, 8Bh, 46h, 0Ch, 89h, 44h, 24h, 20h, 8Bh, 4Eh, 10h, 89h, 4Ch
    db 24h, 24h, 8Bh, 56h, 14h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 89h, 54h, 24h, 28h, 8Bh
    db 54h, 24h, 24h, 8Bh, 01h, 53h, 52h, 8Bh, 54h, 24h, 28h, 52h, 0FFh, 50h, 18h, 0D9h
    db 5Ch, 24h, 28h, 8Bh, 44h, 24h, 74h, 83h, 0C0h, 34h, 50h, 8Dh, 4Ch, 24h, 18h, 0E8h
    db 7Ch, 0D0h, 4Fh, 00h, 8Bh, 44h, 24h, 14h, 3Bh, 0C3h, 0C6h, 44h, 24h, 60h, 02h, 0Fh
    db 84h, 9Dh, 01h, 00h, 00h, 66h, 39h, 58h, 04h, 0Fh, 84h, 93h, 01h, 00h, 00h, 8Dh
    db 4Ch, 24h, 20h, 51h, 51h, 8Dh, 54h, 24h, 1Ch, 89h, 64h, 24h, 20h, 8Bh, 0CCh, 52h
    db 0E8h, 4Bh, 0D0h, 4Fh, 00h, 8Bh, 0CDh, 0E8h, 54h, 0FCh, 0FFh, 0FFh, 8Bh, 0F0h, 83h, 0C4h
    db 08h, 3Bh, 0F3h, 0Fh, 84h, 69h, 01h, 00h, 00h, 56h, 53h, 8Bh, 0CDh, 0E8h, 5Dh, 0FFh
    db 0CAh, 0FFh, 53h, 56h, 53h, 8Bh, 0CDh, 0E8h, 0D7h, 0CEh, 0C7h, 0FFh, 0D9h, 86h, 0C0h, 00h
    db 00h, 00h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 53h, 0D8h
    db 6Ch, 24h, 28h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 8Bh, 01h, 52h, 8Bh, 54h
    db 24h, 28h, 52h, 0FFh, 50h, 18h, 0D9h, 5Ch, 24h, 28h, 3Bh, 0FBh, 74h, 29h, 83h, 0C7h
    db 0Ch, 8Bh, 07h, 89h, 44h, 24h, 20h, 8Bh, 57h, 04h, 89h, 54h, 24h, 24h, 8Bh, 4Fh
    db 08h, 53h, 89h, 4Ch, 24h, 2Ch, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 39h, 52h, 50h
    db 0FFh, 57h, 18h, 0D9h, 5Ch, 24h, 28h, 33h, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Ch, 24h, 74h, 57h, 0E8h, 84h, 79h, 0CAh, 0FFh, 50h, 8Dh, 4Ch, 24h, 1Ch, 0E8h
    db 0ACh, 0CFh, 4Fh, 00h, 8Bh, 44h, 24h, 18h, 3Bh, 0C3h, 0C6h, 44h, 24h, 60h, 03h, 0Fh
    db 84h, 0B5h, 00h, 00h, 00h, 66h, 39h, 58h, 04h, 0Fh, 84h, 0ABh, 00h, 00h, 00h, 0D9h
    db 86h, 0C0h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 28h, 0D8h, 0Dh, 6Ch, 5Ch, 07h, 01h, 8Bh
    db 54h, 24h, 20h, 8Bh, 44h, 24h, 24h, 89h, 4Ch, 24h, 34h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh
    db 01h, 0D9h, 5Ch, 24h, 3Ch, 0D9h, 86h, 0C0h, 00h, 00h, 00h, 89h, 54h, 24h, 2Ch, 0D8h
    db 0Dh, 0Ch, 0B4h, 0Eh, 01h, 89h, 44h, 24h, 30h, 89h, 5Ch, 24h, 38h, 0C7h, 44h, 24h
    db 44h, 0F3h, 4Fh, 0C3h, 0C7h, 0D9h, 5Ch, 24h, 40h, 0C7h, 44h, 24h, 48h, 0F9h, 02h, 15h
    db 50h, 89h, 5Ch, 24h, 4Ch, 89h, 5Ch, 24h, 50h, 89h, 5Ch, 24h, 54h, 8Bh, 11h, 0FFh
    db 52h, 14h, 8Dh, 44h, 24h, 2Ch, 50h, 8Dh, 4Ch, 24h, 3Ch, 51h, 8Dh, 54h, 24h, 28h
    db 52h, 0E8h, 06h, 0C0h, 0C9h, 0FFh, 83h, 0C4h, 0Ch, 3Ah, 0C3h, 74h, 2Dh, 8Dh, 44h, 24h
    db 2Ch, 50h, 51h, 8Dh, 54h, 24h, 20h, 89h, 64h, 24h, 24h, 8Bh, 0CCh, 52h, 0E8h, 0FDh
    db 0CEh, 4Fh, 00h, 8Bh, 0CDh, 0E8h, 06h, 0FBh, 0FFh, 0FFh, 83h, 0C4h, 08h, 3Bh, 0C3h, 74h
    db 09h, 50h, 53h, 8Bh, 0CDh, 0E8h, 0A1h, 0A2h, 0C7h, 0FFh, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h
    db 24h, 60h, 02h, 0E8h, 0B8h, 0CCh, 4Fh, 00h, 47h, 83h, 0FFh, 0Ah, 0Fh, 8Ch, 0Eh, 0FFh
    db 0FFh, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C6h, 44h, 24h, 60h, 01h, 0E8h, 0A0h, 0CCh, 4Fh, 00h
    db 8Dh, 4Ch, 24h, 6Ch, 88h, 5Ch, 24h, 60h, 0E8h, 93h, 0CCh, 4Fh, 00h, 8Dh, 4Ch, 24h
    db 10h, 0C7h, 44h, 24h, 60h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 82h, 0CCh, 4Fh, 00h, 8Bh, 4Ch
    db 24h, 58h, 5Fh, 5Eh, 5Dh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 54h
    db 0C3h
?d_0038a9f0@@YAXXZ ENDP

; ghidra: FUN_0078ad90  retail @ 0x0038AD90 size 92
public ?d_0038ad90@@YAXXZ
?d_0038ad90@@YAXXZ PROC
    db 56h, 8Bh, 0B1h, 0A8h, 00h, 00h, 00h, 85h, 0F6h, 74h, 4Dh, 53h, 8Bh, 5Ch, 24h, 0Ch
    db 84h, 0DBh, 75h, 1Fh, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h
    db 74h, 05h, 0E8h, 04h, 75h, 0C7h, 0FFh, 0F7h, 80h, 0D4h, 00h, 00h, 00h, 00h, 00h, 80h
    db 00h, 75h, 1Ah, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 28h, 85h, 0C0h, 74h, 0Fh, 53h, 8Bh
    db 0C8h, 0E8h, 1Fh, 0DFh, 0C8h, 0FFh, 8Bh, 0CEh, 0E8h, 0C8h, 0Bh, 0C9h, 0FFh, 8Bh, 0B6h, 88h
    db 00h, 00h, 00h, 85h, 0F6h, 75h, 0B9h, 5Bh, 5Eh, 0C2h, 04h, 00h
?d_0038ad90@@YAXXZ ENDP

; ghidra: FUN_0078b1b0  retail @ 0x0038B1B0 size 207
public ?d_0038b1b0@@YAXXZ
?d_0038b1b0@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 0D0h, 0BDh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 4Ch, 53h, 55h, 56h, 57h, 68h, 97h, 16h, 00h
    db 00h, 68h, 48h, 0AEh, 0Eh, 01h, 68h, 0E7h, 03h, 00h, 00h, 6Ah, 01h, 8Bh, 0D9h, 0E8h
    db 0CAh, 69h, 0C7h, 0FFh, 8Bh, 74h, 24h, 7Ch, 8Bh, 0E8h, 8Bh, 86h, 94h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 33h, 0FFh, 0A9h, 00h, 00h, 40h, 00h, 74h, 05h, 0BFh, 20h, 00h, 00h
    db 00h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h
    db 0A7h, 70h, 0C7h, 0FFh, 8Bh, 0Dh, 0D8h, 0F1h, 2Eh, 01h, 55h, 57h, 50h, 0E8h, 14h, 11h
    db 0CAh, 0FFh, 50h, 56h, 8Bh, 0CBh, 0E8h, 0CDh, 2Ah, 0CBh, 0FFh, 8Dh, 4Ch, 24h, 10h, 0E8h
    db 0C5h, 0EAh, 0C8h, 0FFh, 8Bh, 0Dh, 0Ch, 06h, 2Fh, 01h, 8Dh, 44h, 24h, 10h, 50h, 56h
    db 6Ah, 0Ch, 0C7h, 44h, 24h, 70h, 00h, 00h, 00h, 00h, 0E8h, 0FCh, 24h, 0C9h, 0FFh, 68h
    db 62h, 13h, 44h, 00h, 6Ah, 03h, 6Ah, 18h, 8Dh, 4Ch, 24h, 20h, 51h, 0C7h, 44h, 24h
    db 74h, 01h, 00h, 00h, 00h, 0E8h, 0Ch, 0BBh, 66h, 00h, 8Bh, 4Ch, 24h, 5Ch, 5Fh, 5Eh
    db 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 58h, 0C2h, 04h, 00h
?d_0038b1b0@@YAXXZ ENDP

; ghidra: FUN_0078b2c0  retail @ 0x0038B2C0 size 285
public ?d_0038b2c0@@YAXXZ
?d_0038b2c0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 0F9h, 8Bh, 0B7h, 0A8h, 00h, 00h, 00h, 85h, 0F6h, 0Fh
    db 84h, 06h, 01h, 00h, 00h, 53h, 55h, 0EBh, 07h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 04h, 85h, 0C0h, 8Bh, 9Eh, 88h, 00h, 00h, 00h, 89h, 5Ch, 24h, 14h, 74h
    db 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0BEh, 6Fh, 0C7h, 0FFh, 0F7h, 80h, 0C8h
    db 00h, 00h, 00h, 00h, 00h, 40h, 00h, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 8Bh, 0Dh, 0CCh
    db 0F4h, 2Eh, 01h, 8Bh, 01h, 83h, 0C6h, 38h, 56h, 0FFh, 90h, 98h, 00h, 00h, 00h, 8Bh
    db 0F0h, 8Bh, 4Eh, 60h, 83h, 0C6h, 0Ch, 51h, 8Bh, 0CFh, 0E8h, 24h, 3Fh, 0C9h, 0FFh, 89h
    db 44h, 24h, 10h, 83h, 0C6h, 58h, 0BBh, 04h, 00h, 00h, 00h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Bh, 0Eh, 85h, 0C9h, 74h, 4Ah, 8Bh, 87h, 0B4h, 00h, 00h, 00h, 8Bh, 0AFh, 0B8h, 00h
    db 00h, 00h, 2Bh, 0E8h, 33h, 0D2h, 0C1h, 0FDh, 02h, 8Bh, 0C1h, 0F7h, 0F5h, 8Bh, 87h, 0B4h
    db 00h, 00h, 00h, 8Bh, 14h, 90h, 85h, 0D2h, 74h, 26h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 39h, 4Ah, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h, 0F5h, 0EBh, 13h, 85h, 0D2h, 74h
    db 0Fh, 8Bh, 52h, 08h, 85h, 0D2h, 74h, 08h, 52h, 8Bh, 0CFh, 0E8h, 4Eh, 1Dh, 0C9h, 0FFh
    db 83h, 0C6h, 04h, 4Bh, 75h, 0AAh, 8Bh, 4Ch, 24h, 10h, 51h, 8Bh, 0CFh, 0E8h, 3Ch, 1Dh
    db 0C9h, 0FFh, 8Bh, 5Ch, 24h, 14h, 0EBh, 27h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh
    db 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 00h, 6Fh, 0C7h, 0FFh, 0F7h, 80h, 0CCh, 00h, 00h
    db 00h, 00h, 00h, 00h, 08h, 74h, 08h, 56h, 8Bh, 0CFh, 0E8h, 0Fh, 1Dh, 0C9h, 0FFh, 85h
    db 0DBh, 8Bh, 0F3h, 0Fh, 85h, 07h, 0FFh, 0FFh, 0FFh, 5Dh, 5Bh, 8Bh, 0CFh
?d_0038b2c0@@YAXXZ ENDP

; ghidra: FUN_0078b430  retail @ 0x0038B430 size 1078
public ?d_0038b430@@YAXXZ
?d_0038b430@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 57h, 8Bh, 0F9h, 8Bh, 77h, 44h, 33h, 0EDh, 85h, 0F6h, 89h, 6Ch
    db 24h, 10h, 75h, 0Ch, 8Bh, 5Ch, 24h, 20h, 0EBh, 1Dh, 8Bh, 6Ch, 24h, 10h, 8Bh, 0FFh
    db 8Bh, 5Ch, 24h, 20h, 3Bh, 1Eh, 76h, 0Fh, 89h, 74h, 24h, 10h, 8Bh, 76h, 14h, 85h
    db 0F6h, 75h, 0E7h, 8Bh, 6Ch, 24h, 10h, 8Ah, 54h, 24h, 28h, 84h, 0D2h, 8Bh, 0Dh, 38h
    db 6Fh, 2Ah, 01h, 0Fh, 85h, 0EAh, 00h, 00h, 00h, 3Bh, 4Fh, 3Ch, 0Fh, 84h, 0E1h, 00h
    db 00h, 00h, 85h, 0F6h, 74h, 08h, 3Bh, 1Eh, 0Fh, 84h, 0D5h, 00h, 00h, 00h, 8Bh, 4Ch
    db 24h, 24h, 85h, 0C9h, 74h, 07h, 6Ah, 00h, 0E8h, 0Eh, 7Eh, 0C7h, 0FFh, 6Ah, 18h, 0E8h
    db 8Ch, 6Ah, 4Fh, 00h, 8Bh, 0F0h, 33h, 0D2h, 83h, 0C4h, 04h, 3Bh, 0F2h, 0Fh, 84h, 0ABh
    db 03h, 00h, 00h, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 2Ch, 3Bh, 0CAh, 89h, 46h, 04h
    db 8Dh, 46h, 10h, 89h, 1Eh, 89h, 10h, 74h, 72h, 89h, 08h, 8Dh, 6Fh, 4Ch, 50h, 8Bh
    db 0CDh, 89h, 56h, 08h, 89h, 56h, 0Ch, 0E8h, 0E0h, 29h, 0C9h, 0FFh, 8Bh, 0CDh, 0E8h, 8Eh
    db 00h, 0CAh, 0FFh, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Bh, 91h, 0B4h, 0Ch, 00h, 00h, 83h
    db 0C2h, 03h, 3Bh, 0C2h, 76h, 2Ch, 8Bh, 45h, 00h, 8Bh, 00h, 89h, 47h, 48h, 8Bh, 40h
    db 08h, 85h, 0C0h, 74h, 16h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0C8h, 0E8h, 0DFh, 0FCh, 63h
    db 00h, 50h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 83h, 0C4h, 04h, 8Bh, 0CDh, 0E8h, 88h, 8Dh
    db 0C7h, 0FFh, 8Bh, 6Ch, 24h, 10h, 85h, 0EDh, 75h, 28h, 8Bh, 47h, 44h, 89h, 46h, 14h
    db 89h, 77h, 44h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 18h, 00h, 8Bh, 4Ch, 24h, 1Ch, 0BAh
    db 01h, 00h, 00h, 00h, 0D3h, 0E2h, 0C7h, 46h, 08h, 01h, 00h, 00h, 00h, 89h, 56h, 0Ch
    db 0EBh, 0D4h, 8Bh, 4Dh, 14h, 5Fh, 89h, 4Eh, 14h, 89h, 75h, 14h, 5Eh, 5Dh, 5Bh, 59h
    db 0C2h, 18h, 00h, 83h, 0F9h, 0FFh, 74h, 09h, 3Bh, 4Fh, 3Ch, 74h, 04h, 0B0h, 01h, 0EBh
    db 02h, 32h, 0C0h, 84h, 0D2h, 8Bh, 5Ch, 24h, 18h, 75h, 1Ah, 3Bh, 4Fh, 3Ch, 74h, 15h
    db 84h, 0C0h, 75h, 38h, 3Bh, 5Eh, 04h, 74h, 33h, 0A1h, 98h, 08h, 2Fh, 01h, 8Ah, 48h
    db 6Ch, 84h, 0C9h, 75h, 27h, 8Bh, 0CFh, 0E8h, 6Fh, 0EBh, 0CBh, 0FFh, 0A0h, 0E8h, 0D4h, 2Eh
    db 01h, 84h, 0C0h, 0Fh, 84h, 0D0h, 00h, 00h, 00h, 8Bh, 0Dh, 38h, 6Fh, 2Ah, 01h, 3Bh
    db 4Fh, 3Ch, 0Fh, 84h, 0C1h, 00h, 00h, 00h, 8Ah, 54h, 24h, 28h, 8Bh, 4Ch, 24h, 24h
    db 85h, 0C9h, 74h, 0Bh, 84h, 0D2h, 75h, 07h, 6Ah, 00h, 0E8h, 0DCh, 7Ch, 0C7h, 0FFh, 8Bh
    db 4Ch, 24h, 1Ch, 8Bh, 46h, 0Ch, 0BAh, 01h, 00h, 00h, 00h, 0D3h, 0E2h, 85h, 0C2h, 75h
    db 0Ch, 8Bh, 5Eh, 08h, 43h, 0Bh, 0C2h, 89h, 5Eh, 08h, 89h, 46h, 0Ch, 8Bh, 0Dh, 2Ch
    db 0D6h, 2Eh, 01h, 85h, 0C9h, 74h, 50h, 0E8h, 0EFh, 88h, 0CBh, 0FFh, 83h, 0F8h, 01h, 75h
    db 46h, 0A1h, 2Ch, 0D6h, 2Eh, 01h, 8Bh, 56h, 08h, 3Bh, 90h, 0A0h, 02h, 00h, 00h, 0Fh
    db 85h, 49h, 02h, 00h, 00h, 85h, 0EDh, 74h, 17h, 8Bh, 4Eh, 14h, 56h, 89h, 4Dh, 14h
    db 0E8h, 8Bh, 68h, 4Fh, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 18h, 00h
    db 8Bh, 56h, 14h, 56h, 89h, 57h, 44h, 0E8h, 74h, 68h, 4Fh, 00h, 83h, 0C4h, 04h, 5Fh
    db 5Eh, 5Dh, 5Bh, 59h, 0C2h, 18h, 00h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 8Bh, 01h, 0FFh
    db 90h, 94h, 00h, 00h, 00h, 39h, 46h, 08h, 0Fh, 85h, 00h, 02h, 00h, 00h, 85h, 0EDh
    db 74h, 0CEh, 8Bh, 4Eh, 14h, 56h, 89h, 4Dh, 14h, 0E8h, 42h, 68h, 4Fh, 00h, 83h, 0C4h
    db 04h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 18h, 00h, 8Bh, 47h, 4Ch, 8Bh, 08h, 3Bh, 0C8h
    db 89h, 4Fh, 48h, 0Fh, 84h, 0C3h, 01h, 00h, 00h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 85h
    db 0C9h, 0Fh, 84h, 0AFh, 00h, 00h, 00h, 8Ah, 47h, 6Ch, 84h, 0C0h, 0Fh, 85h, 88h, 00h
    db 00h, 00h, 8Ah, 44h, 24h, 28h, 84h, 0C0h, 74h, 12h, 8Bh, 01h, 0FFh, 90h, 8Ch, 00h
    db 00h, 00h, 84h, 0C0h, 74h, 74h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 8Bh, 11h, 0FFh, 92h
    db 8Ch, 00h, 00h, 00h, 84h, 0C0h, 74h, 4Bh, 8Ah, 44h, 24h, 28h, 84h, 0C0h, 74h, 43h
    db 8Bh, 0Dh, 0ECh, 0D5h, 2Eh, 01h, 8Bh, 01h, 68h, 49h, 04h, 00h, 00h, 0FFh, 50h, 34h
    db 8Bh, 0F0h, 53h, 8Bh, 0CEh, 0E8h, 86h, 5Ch, 0C7h, 0FFh, 8Bh, 4Fh, 3Ch, 51h, 8Bh, 0CEh
    db 0E8h, 63h, 1Eh, 0C8h, 0FFh, 8Bh, 0Dh, 2Ch, 0D6h, 2Eh, 01h, 0E8h, 0EBh, 87h, 0CBh, 0FFh
    db 48h, 0F7h, 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 8Bh, 0CEh, 50h, 0E8h, 9Ch, 7Bh, 0C7h, 0FFh, 8Bh
    db 0CEh, 0EBh, 10h, 8Bh, 4Ch, 24h, 24h, 85h, 0C9h, 74h, 0Fh, 8Ah, 44h, 24h, 28h, 84h
    db 0C0h, 75h, 07h, 6Ah, 01h, 0E8h, 81h, 7Bh, 0C7h, 0FFh, 8Bh, 0Dh, 0ECh, 0D5h, 2Eh, 01h
    db 0E8h, 61h, 0F7h, 0C9h, 0FFh, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 85h, 0C9h, 74h, 07h, 8Bh
    db 11h, 6Ah, 00h, 0FFh, 52h, 24h, 8Bh, 47h, 48h, 3Bh, 47h, 4Ch, 0Fh, 84h, 0A5h, 00h
    db 00h, 00h, 8Bh, 6Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 20h, 8Bh, 57h, 48h, 8Bh, 42h, 08h
    db 55h, 51h, 50h, 8Bh, 0CFh, 0E8h, 03h, 85h, 0C9h, 0FFh, 8Bh, 0Dh, 2Ch, 0D6h, 2Eh, 01h
    db 85h, 0C9h, 74h, 0Ah, 0E8h, 72h, 87h, 0CBh, 0FFh, 83h, 0F8h, 01h, 74h, 64h, 8Bh, 0Dh
    db 0ECh, 0D5h, 2Eh, 01h, 8Bh, 11h, 68h, 49h, 04h, 00h, 00h, 0FFh, 52h, 34h, 8Bh, 0F0h
    db 53h, 8Bh, 0CEh, 0E8h, 0D8h, 5Bh, 0C7h, 0FFh, 8Bh, 47h, 3Ch, 50h, 8Bh, 0CEh, 0E8h, 0B5h
    db 1Dh, 0C8h, 0FFh, 8Bh, 0Dh, 2Ch, 0D6h, 2Eh, 01h, 0E8h, 3Dh, 87h, 0CBh, 0FFh, 48h, 0F7h
    db 0D8h, 1Ah, 0C0h, 0FEh, 0C0h, 8Bh, 0CEh, 50h, 0E8h, 0EEh, 7Ah, 0C7h, 0FFh, 6Ah, 01h, 8Bh
    db 0CEh, 0E8h, 0E5h, 7Ah, 0C7h, 0FFh, 8Bh, 0Dh, 0ECh, 0D5h, 2Eh, 01h, 0E8h, 0C5h, 0F6h, 0C9h
    db 0FFh, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 85h, 0C9h, 74h, 07h, 8Bh, 11h, 6Ah, 00h, 0FFh
    db 52h, 24h, 8Bh, 47h, 48h, 8Bh, 08h, 89h, 4Fh, 48h, 8Bh, 47h, 4Ch, 8Bh, 0D1h, 3Bh
    db 0D0h, 0Fh, 85h, 5Fh, 0FFh, 0FFh, 0FFh, 8Bh, 47h, 4Ch, 8Bh, 30h, 3Bh, 0F0h, 74h, 16h
    db 8Bh, 0C6h, 8Bh, 36h, 6Ah, 0Ch, 50h, 0E8h, 0E4h, 2Dh, 4Ah, 00h, 8Bh, 47h, 4Ch, 83h
    db 0C4h, 08h, 3Bh, 0F0h, 75h, 0EAh, 8Bh, 47h, 4Ch, 89h, 00h, 8Bh, 7Fh, 4Ch, 89h, 7Fh
    db 04h, 8Bh, 0Dh, 2Ch, 0D6h, 2Eh, 01h, 85h, 0C9h, 74h, 0Ah, 0E8h, 0BBh, 86h, 0CBh, 0FFh
    db 83h, 0F8h, 01h, 74h, 29h, 8Bh, 0Dh, 14h, 77h, 2Fh, 01h, 85h, 0C9h, 74h, 1Fh, 8Bh
    db 01h, 0FFh, 50h, 78h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 18h, 00h, 8Bh, 4Ch, 24h, 1Ch
    db 8Bh, 56h, 10h, 51h, 6Ah, 00h, 52h, 8Bh, 0CFh, 0E8h, 0Fh, 84h, 0C9h, 0FFh, 5Fh, 5Eh
    db 5Dh, 5Bh, 59h, 0C2h, 18h, 00h
?d_0038b430@@YAXXZ ENDP

; ghidra: FUN_0078b980  retail @ 0x0038B980 size 99
public ?d_0038b980@@YAXXZ
?d_0038b980@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 08h, 56h, 8Bh, 30h, 8Bh, 41h, 04h, 57h, 8Bh, 79h
    db 08h, 2Bh, 0F8h, 33h, 0D2h, 0C1h, 0FFh, 02h, 8Bh, 0C6h, 0F7h, 0F7h, 8Bh, 41h, 04h, 8Bh
    db 14h, 90h, 85h, 0D2h, 74h, 11h, 39h, 72h, 04h, 74h, 08h, 8Bh, 12h, 85h, 0D2h, 75h
    db 0F5h, 0EBh, 04h, 85h, 0D2h, 75h, 21h, 8Dh, 54h, 24h, 08h, 52h, 89h, 74h, 24h, 0Ch
    db 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 0D8h, 0AFh, 0C8h, 0FFh, 5Fh, 83h, 0C0h
    db 04h, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h, 5Fh, 8Dh, 42h, 08h, 5Eh, 83h, 0C4h, 08h
    db 0C2h, 04h, 00h
?d_0038b980@@YAXXZ ENDP

; ghidra: FUN_0078bad0  retail @ 0x0038BAD0 size 306
public ?d_0038bad0@@YAXXZ
?d_0038bad0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 04h, 8Bh, 4Ch, 24h, 20h, 56h, 2Bh, 03h
    db 0C1h, 0F8h, 03h, 3Bh, 0C1h, 57h, 89h, 5Ch, 24h, 10h, 89h, 44h, 24h, 0Ch, 8Dh, 4Ch
    db 24h, 28h, 72h, 04h, 8Dh, 4Ch, 24h, 0Ch, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 14h
    db 74h, 2Bh, 8Dh, 04h, 0CDh, 00h, 00h, 00h, 00h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h
    db 0Eh, 0E8h, 1Ah, 64h, 4Fh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 0EBh, 16h, 0E8h
    db 1Ch, 2Ah, 4Ah, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 0EBh, 08h, 0C7h, 44h, 24h
    db 0Ch, 00h, 00h, 00h, 00h, 8Bh, 33h, 8Bh, 7Ch, 24h, 0Ch, 55h, 8Bh, 6Ch, 24h, 20h
    db 3Bh, 0F5h, 74h, 14h, 56h, 57h, 0E8h, 22h, 0EAh, 0C9h, 0FFh, 83h, 0C6h, 08h, 83h, 0C4h
    db 08h, 83h, 0C7h, 08h, 3Bh, 0F5h, 75h, 0ECh, 8Bh, 74h, 24h, 2Ch, 83h, 0FEh, 01h, 75h
    db 13h, 8Bh, 44h, 24h, 24h, 50h, 57h, 0E8h, 01h, 0EAh, 0C9h, 0FFh, 83h, 0C4h, 08h, 83h
    db 0C7h, 08h, 0EBh, 18h, 85h, 0F6h, 76h, 14h, 8Bh, 4Ch, 24h, 24h, 51h, 57h, 0E8h, 0EAh
    db 0E9h, 0C9h, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 08h, 4Eh, 75h, 0ECh, 8Ah, 44h, 24h, 30h
    db 84h, 0C0h, 75h, 24h, 8Bh, 5Bh, 04h, 3Bh, 0EBh, 74h, 19h, 8Bh, 0F5h, 8Dh, 49h, 00h
    db 56h, 57h, 0E8h, 0C6h, 0E9h, 0C9h, 0FFh, 83h, 0C6h, 08h, 83h, 0C4h, 08h, 83h, 0C7h, 08h
    db 3Bh, 0F3h, 75h, 0ECh, 8Bh, 5Ch, 24h, 14h, 8Bh, 0Bh, 85h, 0C9h, 5Dh, 74h, 27h, 8Bh
    db 43h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 0Bh, 51h, 0E8h, 0D9h, 62h, 4Fh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0Dh
    db 2Ah, 4Ah, 00h, 83h, 0C4h, 08h, 8Bh, 44h, 24h, 0Ch, 8Bh, 54h, 24h, 14h, 89h, 7Bh
    db 04h, 89h, 03h, 5Fh, 8Dh, 04h, 0D0h, 5Eh, 89h, 43h, 08h, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 14h, 00h
?d_0038bad0@@YAXXZ ENDP

; ghidra: FUN_0078bd90  retail @ 0x0038BD90 size 79
public ?d_0038bd90@@YAXXZ
?d_0038bd90@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0E8h, 0BDh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 8Bh, 0F1h, 8Dh, 44h, 24h, 14h, 50h, 0C7h, 44h, 24h
    db 10h, 00h, 00h, 00h, 00h, 0E8h, 0E6h, 0C5h, 0C7h, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h
    db 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 75h, 0BBh, 4Fh, 00h, 8Bh, 4Ch, 24h, 04h, 8Bh
    db 0C6h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_0038bd90@@YAXXZ ENDP

; ghidra: FUN_0078be40  retail @ 0x0038BE40 size 159
public ?d_0038be40@@YAXXZ
?d_0038be40@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 18h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 14h
    db 8Bh, 0CCh, 57h, 0E8h, 08h, 0BDh, 4Fh, 00h, 8Bh, 0CEh, 0E8h, 32h, 2Eh, 0C8h, 0FFh, 8Bh
    db 5Eh, 04h, 8Bh, 4Eh, 08h, 2Bh, 0CBh, 0C1h, 0F9h, 02h, 33h, 0D2h, 0F7h, 0F1h, 8Bh, 0C3h
    db 8Bh, 04h, 90h, 85h, 0C0h, 74h, 60h, 8Bh, 3Fh, 89h, 7Ch, 24h, 18h, 0EBh, 04h, 8Bh
    db 7Ch, 24h, 18h, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 57h, 04h, 83h, 0C7h, 08h, 0EBh, 07h
    db 33h, 0D2h, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 06h, 0Fh, 0B7h
    db 69h, 04h, 0EBh, 02h, 33h, 0EDh, 85h, 0C9h, 8Dh, 71h, 08h, 75h, 05h, 0BEh, 8Bh, 38h
    db 07h, 01h, 3Bh, 0EAh, 8Bh, 0CDh, 7Ch, 02h, 8Bh, 0CAh, 33h, 0DBh, 0F3h, 0A6h, 74h, 05h
    db 1Bh, 0DBh, 83h, 0DBh, 0FFh, 85h, 0DBh, 75h, 08h, 2Bh, 0EAh, 8Bh, 0DDh, 85h, 0DBh, 74h
    db 06h, 8Bh, 00h, 85h, 0C0h, 75h, 0A8h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_0038be40@@YAXXZ ENDP

; ghidra: FUN_0078bf10  retail @ 0x0038BF10 size 159
public ?d_0038bf10@@YAXXZ
?d_0038bf10@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 18h, 51h, 8Bh, 0F1h, 89h, 64h, 24h, 14h
    db 8Bh, 0CCh, 57h, 0E8h, 38h, 0BCh, 4Fh, 00h, 8Bh, 0CEh, 0E8h, 62h, 2Dh, 0C8h, 0FFh, 8Bh
    db 5Eh, 04h, 8Bh, 4Eh, 08h, 2Bh, 0CBh, 0C1h, 0F9h, 02h, 33h, 0D2h, 0F7h, 0F1h, 8Bh, 0C3h
    db 8Bh, 04h, 90h, 85h, 0C0h, 74h, 60h, 8Bh, 3Fh, 89h, 7Ch, 24h, 18h, 0EBh, 04h, 8Bh
    db 7Ch, 24h, 18h, 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 57h, 04h, 83h, 0C7h, 08h, 0EBh, 07h
    db 33h, 0D2h, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 06h, 0Fh, 0B7h
    db 69h, 04h, 0EBh, 02h, 33h, 0EDh, 85h, 0C9h, 8Dh, 71h, 08h, 75h, 05h, 0BEh, 8Bh, 38h
    db 07h, 01h, 3Bh, 0EAh, 8Bh, 0CDh, 7Ch, 02h, 8Bh, 0CAh, 33h, 0DBh, 0F3h, 0A6h, 74h, 05h
    db 1Bh, 0DBh, 83h, 0DBh, 0FFh, 85h, 0DBh, 75h, 08h, 2Bh, 0EAh, 8Bh, 0DDh, 85h, 0DBh, 74h
    db 06h, 8Bh, 00h, 85h, 0C0h, 75h, 0A8h, 5Fh, 5Eh, 5Dh, 5Bh, 59h, 0C2h, 04h, 00h
?d_0038bf10@@YAXXZ ENDP

; ghidra: FUN_0078bfe0  retail @ 0x0038BFE0 size 194
public ?d_0038bfe0@@YAXXZ
?d_0038bfe0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 31h, 8Bh, 5Eh, 04h, 85h, 0DBh, 57h, 8Bh, 0FEh, 89h
    db 74h, 24h, 14h, 89h, 7Ch, 24h, 0Ch, 74h, 7Eh, 8Bh, 44h, 24h, 1Ch, 8Bh, 38h, 55h
    db 89h, 7Ch, 24h, 14h, 0EBh, 0Ah, 8Bh, 7Ch, 24h, 14h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 6Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0EDh, 0BFh
    db 8Bh, 38h, 07h, 01h, 8Bh, 43h, 10h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh
    db 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh
    db 0D5h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CDh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h
    db 0D8h, 0FFh, 85h, 0C0h, 75h, 06h, 2Bh, 0D5h, 8Bh, 0C2h, 85h, 0C0h, 7Ch, 09h, 89h, 5Ch
    db 24h, 10h, 8Bh, 5Bh, 08h, 0EBh, 03h, 8Bh, 5Bh, 0Ch, 85h, 0DBh, 75h, 98h, 8Bh, 7Ch
    db 24h, 10h, 8Bh, 74h, 24h, 18h, 5Dh, 3Bh, 0FEh, 74h, 11h, 8Dh, 4Fh, 10h, 51h, 8Bh
    db 4Ch, 24h, 20h, 0E8h, 3Dh, 60h, 0C9h, 0FFh, 85h, 0C0h, 7Dh, 0Bh, 5Fh, 8Bh, 0C6h, 5Eh
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 04h, 00h
?d_0038bfe0@@YAXXZ ENDP

; ghidra: FUN_0078c0e0  retail @ 0x0038C0E0 size 194
public ?d_0038c0e0@@YAXXZ
?d_0038c0e0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 31h, 8Bh, 5Eh, 04h, 85h, 0DBh, 57h, 8Bh, 0FEh, 89h
    db 74h, 24h, 14h, 89h, 7Ch, 24h, 0Ch, 74h, 7Eh, 8Bh, 44h, 24h, 1Ch, 8Bh, 38h, 55h
    db 89h, 7Ch, 24h, 14h, 0EBh, 0Ah, 8Bh, 7Ch, 24h, 14h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 85h, 0FFh, 74h, 09h, 0Fh, 0B7h, 6Fh, 04h, 83h, 0C7h, 08h, 0EBh, 07h, 33h, 0EDh, 0BFh
    db 8Bh, 38h, 07h, 01h, 8Bh, 43h, 10h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 50h, 04h, 0EBh
    db 02h, 33h, 0D2h, 85h, 0C0h, 8Dh, 70h, 08h, 75h, 05h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh
    db 0D5h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CDh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h
    db 0D8h, 0FFh, 85h, 0C0h, 75h, 06h, 2Bh, 0D5h, 8Bh, 0C2h, 85h, 0C0h, 7Ch, 09h, 89h, 5Ch
    db 24h, 10h, 8Bh, 5Bh, 08h, 0EBh, 03h, 8Bh, 5Bh, 0Ch, 85h, 0DBh, 75h, 98h, 8Bh, 7Ch
    db 24h, 10h, 8Bh, 74h, 24h, 18h, 5Dh, 3Bh, 0FEh, 74h, 11h, 8Dh, 4Fh, 10h, 51h, 8Bh
    db 4Ch, 24h, 20h, 0E8h, 3Dh, 5Fh, 0C9h, 0FFh, 85h, 0C0h, 7Dh, 0Bh, 5Fh, 8Bh, 0C6h, 5Eh
    db 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C2h
    db 04h, 00h
?d_0038c0e0@@YAXXZ ENDP

; ghidra: FUN_0078d000  retail @ 0x0038D000 size 112
public ?d_0038d000@@YAXXZ
?d_0038d000@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 86h, 60h, 01h, 00h, 00h, 3Bh, 0C0h, 8Bh, 8Eh, 5Ch, 01h, 00h
    db 00h, 57h, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh
    db 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 86h, 60h, 01h, 00h, 00h
    db 8Bh, 86h, 0A8h, 00h, 00h, 00h, 85h, 0C0h, 74h, 1Ah, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 0B8h, 88h, 00h, 00h, 00h, 50h, 8Bh, 0CEh, 0E8h, 90h, 00h, 0C9h, 0FFh, 85h, 0FFh
    db 8Bh, 0C7h, 75h, 0ECh, 8Bh, 0CEh, 0E8h, 0CDh, 7Fh, 0C8h, 0FFh, 8Bh, 0Dh, 64h, 14h, 2Fh
    db 01h, 85h, 0C9h, 5Fh, 5Eh, 74h, 08h, 8Bh, 01h, 0FFh, 0A0h, 80h, 00h, 00h, 00h, 0C3h
?d_0038d000@@YAXXZ ENDP

; ghidra: FUN_0078d090  retail @ 0x0038D090 size 83
public ?d_0038d090@@YAXXZ
?d_0038d090@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 48h, 8Ah, 41h, 69h, 84h, 0C0h, 75h, 41h, 8Ah
    db 41h, 6Ah, 84h, 0C0h, 75h, 3Ah, 8Bh, 91h, 5Ch, 01h, 00h, 00h, 56h, 8Bh, 0B1h, 60h
    db 01h, 00h, 00h, 57h, 8Dh, 0B9h, 5Ch, 01h, 00h, 00h, 8Dh, 44h, 24h, 0Ch, 50h, 8Dh
    db 4Ch, 24h, 10h, 51h, 56h, 52h, 0E8h, 0C2h, 09h, 0CAh, 0FFh, 83h, 0C4h, 10h, 3Bh, 0C6h
    db 75h, 0Ch, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CFh, 0E8h, 92h, 0CDh, 0C8h, 0FFh, 5Fh, 5Eh
    db 0C2h, 04h, 00h
?d_0038d090@@YAXXZ ENDP

; ghidra: FUN_0078d870  retail @ 0x0038D870 size 329
public ?d_0038d870@@YAXXZ
?d_0038d870@@YAXXZ PROC
    db 51h, 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 40h, 3Ch, 56h, 8Bh, 0F1h, 8Bh, 8Eh, 00h, 01h
    db 00h, 00h, 57h, 8Bh, 7Ch, 24h, 14h, 3Bh, 0F9h, 0Fh, 84h, 0DEh, 00h, 00h, 00h, 8Bh
    db 4Fh, 14h, 53h, 8Bh, 5Ch, 24h, 1Ch, 3Bh, 0D9h, 0Fh, 84h, 0CDh, 00h, 00h, 00h, 85h
    db 0C0h, 76h, 0Dh, 3Bh, 0C8h, 75h, 09h, 40h, 3Bh, 0D8h, 0Fh, 84h, 0BCh, 00h, 00h, 00h
    db 8Bh, 4Fh, 1Ch, 55h, 8Bh, 6Fh, 18h, 8Dh, 96h, 0A8h, 00h, 00h, 00h, 89h, 4Ch, 24h
    db 10h, 8Bh, 4Ch, 24h, 18h, 52h, 0E8h, 2Dh, 64h, 0CAh, 0FFh, 84h, 0C0h, 0Fh, 84h, 0A0h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 7Dh, 7Eh, 81h, 0FBh, 0FFh, 0FFh, 0FFh
    db 3Fh, 73h, 76h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 28h, 8Bh, 8Eh, 0F8h, 00h, 00h, 00h
    db 2Bh, 8Eh, 0F4h, 00h, 00h, 00h, 0C1h, 0F9h, 02h, 49h, 3Bh, 0E9h, 8Bh, 0D8h, 7Dh, 25h
    db 8Bh, 96h, 0F8h, 00h, 00h, 00h, 8Bh, 86h, 0F4h, 00h, 00h, 00h, 8Bh, 4Ah, 0FCh, 89h
    db 0Ch, 0A8h, 8Bh, 96h, 0F4h, 00h, 00h, 00h, 8Bh, 04h, 0AAh, 0C7h, 40h, 1Ch, 0FFh, 0FFh
    db 0FFh, 0FFh, 89h, 68h, 18h, 83h, 86h, 0F8h, 00h, 00h, 00h, 0FCh, 8Dh, 04h, 5Bh, 8Bh
    db 0ACh, 86h, 0C4h, 00h, 00h, 00h, 8Dh, 8Ch, 86h, 0C4h, 00h, 00h, 00h, 8Bh, 71h, 04h
    db 8Dh, 54h, 24h, 1Ch, 2Bh, 0F5h, 52h, 0C1h, 0FEh, 02h, 0E8h, 0A3h, 0A3h, 0C7h, 0FFh, 89h
    db 5Fh, 1Ch, 8Bh, 5Ch, 24h, 20h, 89h, 77h, 18h, 81h, 0FBh, 0FFh, 0FFh, 0FFh, 3Fh, 8Bh
    db 0C3h, 76h, 05h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 89h, 47h, 14h, 5Dh, 5Bh, 5Fh, 5Eh, 59h
    db 0C2h, 0Ch, 00h, 83h, 0FDh, 0FFh, 74h, 0E1h, 6Ah, 01h, 0E8h, 21h, 0BDh, 4Fh, 00h, 8Bh
    db 0Dh, 5Ch, 6Eh, 33h, 01h, 8Bh, 01h, 83h, 0C4h, 04h, 0FFh, 50h, 60h, 8Bh, 0Dh, 5Ch
    db 6Eh, 33h, 01h, 8Bh, 11h, 6Ah, 00h, 6Ah, 00h, 0FFh, 52h, 6Ch, 8Bh, 10h, 68h, 20h
    db 0B5h, 0Eh, 01h, 8Bh, 0C8h, 0FFh, 52h, 38h, 8Bh, 10h, 6Ah, 01h, 8Bh, 0C8h, 0FFh, 52h
    db 4Ch, 5Dh, 5Bh, 5Fh, 5Eh, 59h, 0C2h, 0Ch, 00h
?d_0038d870@@YAXXZ ENDP

; ghidra: FUN_0078e490  retail @ 0x0038E490 size 38
public ?d_0038e490@@YAXXZ
?d_0038e490@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 19h, 8Bh, 46h, 74h, 8Dh, 54h, 24h, 08h
    db 52h, 81h, 0C1h, 0B0h, 00h, 00h, 00h, 89h, 44h, 24h, 0Ch, 0E8h, 61h, 79h, 0C7h, 0FFh
    db 89h, 30h, 5Eh, 0C2h, 04h, 00h
?d_0038e490@@YAXXZ ENDP

; ghidra: FUN_0078e4c0  retail @ 0x0038E4C0 size 298
public ?d_0038e4c0@@YAXXZ
?d_0038e4c0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 74h, 24h, 10h, 57h, 8Bh, 0F9h, 8Dh, 87h, 0ACh, 00h, 00h, 00h
    db 50h, 8Dh, 8Fh, 0A8h, 00h, 00h, 00h, 51h, 8Bh, 0CEh, 0E8h, 2Ch, 36h, 0CAh, 0FFh, 85h
    db 0F6h, 74h, 19h, 8Bh, 56h, 74h, 8Dh, 44h, 24h, 14h, 50h, 8Dh, 8Fh, 0B0h, 00h, 00h
    db 00h, 89h, 54h, 24h, 18h, 0E8h, 17h, 79h, 0C7h, 0FFh, 89h, 30h, 8Bh, 0Dh, 98h, 08h
    db 2Fh, 01h, 8Bh, 69h, 3Ch, 85h, 0EDh, 75h, 05h, 0BDh, 01h, 00h, 00h, 00h, 8Bh, 9Eh
    db 0F0h, 01h, 00h, 00h, 8Bh, 03h, 85h, 0C0h, 0Fh, 84h, 0C5h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 50h, 0Ch, 8Dh, 48h, 0Ch, 0FFh, 52h, 20h, 85h, 0C0h, 0Fh, 84h, 0A4h, 00h, 00h
    db 00h, 8Dh, 70h, 0F0h, 85h, 0F6h, 89h, 74h, 24h, 14h, 0Fh, 84h, 95h, 00h, 00h, 00h
    db 8Bh, 46h, 14h, 85h, 0C0h, 75h, 12h, 81h, 0FDh, 0FFh, 0FFh, 0FFh, 3Fh, 8Bh, 0C5h, 76h
    db 05h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 89h, 46h, 14h, 81h, 7Eh, 14h, 0FFh, 0FFh, 0FFh, 3Fh
    db 75h, 23h, 8Bh, 87h, 0F8h, 00h, 00h, 00h, 8Bh, 97h, 0F4h, 00h, 00h, 00h, 8Dh, 8Fh
    db 0F4h, 00h, 00h, 00h, 2Bh, 0C2h, 0C1h, 0F8h, 02h, 0C7h, 46h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh
    db 89h, 46h, 18h, 0EBh, 28h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 28h, 8Dh, 0Ch, 40h, 8Bh
    db 94h, 8Fh, 0C8h, 00h, 00h, 00h, 2Bh, 94h, 8Fh, 0C4h, 00h, 00h, 00h, 8Dh, 8Ch, 8Fh
    db 0C4h, 00h, 00h, 00h, 0C1h, 0FAh, 02h, 89h, 46h, 1Ch, 89h, 56h, 18h, 8Bh, 41h, 04h
    db 3Bh, 41h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 30h, 83h, 41h, 04h, 04h, 0EBh
    db 14h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 1Ch, 52h, 8Dh, 54h, 24h, 20h, 52h, 50h
    db 0E8h, 0A4h, 85h, 0CAh, 0FFh, 8Bh, 43h, 04h, 83h, 0C3h, 04h, 85h, 0C0h, 0Fh, 85h, 3Dh
    db 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h
?d_0038e4c0@@YAXXZ ENDP

; ghidra: FUN_0078e6f0  retail @ 0x0038E6F0 size 469
public ?d_0038e6f0@@YAXXZ
?d_0038e6f0@@YAXXZ PROC
    db 83h, 0ECh, 10h, 53h, 55h, 8Bh, 2Dh, 5Ch, 94h, 35h, 01h, 56h, 8Bh, 0D1h, 57h, 89h
    db 54h, 24h, 14h, 8Dh, 0B2h, 0C0h, 00h, 00h, 00h, 0BBh, 04h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 46h, 0FCh, 3Bh, 06h, 74h, 14h, 8Bh, 08h, 83h, 0CFh, 0FFh, 89h, 79h, 1Ch, 89h
    db 79h, 18h, 8Bh, 0Eh, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0ECh, 8Bh, 06h, 3Bh, 0C0h, 8Bh
    db 4Eh, 0FCh, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh
    db 0D5h, 8Bh, 54h, 24h, 20h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 06h, 83h, 0C6h, 0Ch, 4Bh
    db 75h, 0BEh, 8Bh, 82h, 0ECh, 00h, 00h, 00h, 3Bh, 82h, 0F0h, 00h, 00h, 00h, 8Dh, 0BAh
    db 0ECh, 00h, 00h, 00h, 74h, 18h, 8Bh, 08h, 83h, 0CEh, 0FFh, 89h, 71h, 1Ch, 89h, 71h
    db 18h, 8Bh, 8Ah, 0F0h, 00h, 00h, 00h, 83h, 0C0h, 04h, 3Bh, 0C1h, 75h, 0E8h, 8Bh, 47h
    db 04h, 3Bh, 0C0h, 8Bh, 0Fh, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F0h, 2Bh, 0F0h, 56h
    db 50h, 51h, 0FFh, 0D5h, 8Bh, 54h, 24h, 20h, 83h, 0C4h, 0Ch, 03h, 0C6h, 89h, 47h, 04h
    db 0A1h, 98h, 08h, 2Fh, 01h, 8Bh, 68h, 3Ch, 85h, 0EDh, 75h, 05h, 0BDh, 01h, 00h, 00h
    db 00h, 8Bh, 92h, 0A0h, 00h, 00h, 00h, 85h, 0D2h, 89h, 54h, 24h, 18h, 0Fh, 84h, 0FAh
    db 00h, 00h, 00h, 8Bh, 4Ch, 24h, 18h, 8Bh, 99h, 0F0h, 01h, 00h, 00h, 8Bh, 03h, 85h
    db 0C0h, 0Fh, 84h, 0D0h, 00h, 00h, 00h, 8Bh, 50h, 0Ch, 8Dh, 48h, 0Ch, 0FFh, 52h, 20h
    db 85h, 0C0h, 0Fh, 84h, 0B1h, 00h, 00h, 00h, 8Dh, 70h, 0F0h, 85h, 0F6h, 89h, 74h, 24h
    db 1Ch, 0Fh, 84h, 0A2h, 00h, 00h, 00h, 8Bh, 46h, 14h, 85h, 0C0h, 75h, 12h, 81h, 0FDh
    db 0FFh, 0FFh, 0FFh, 3Fh, 8Bh, 0C5h, 76h, 05h, 0B8h, 0FFh, 0FFh, 0FFh, 3Fh, 89h, 46h, 14h
    db 81h, 7Eh, 14h, 0FFh, 0FFh, 0FFh, 3Fh, 75h, 35h, 8Bh, 0Fh, 8Bh, 47h, 04h, 2Bh, 0C1h
    db 0C1h, 0F8h, 02h, 0C7h, 46h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 46h, 18h, 8Bh, 47h, 04h
    db 3Bh, 47h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 30h, 83h, 47h, 04h, 04h, 0EBh
    db 58h, 6Ah, 01h, 8Dh, 4Ch, 24h, 17h, 6Ah, 01h, 51h, 8Bh, 0CFh, 0EBh, 40h, 8Bh, 06h
    db 8Bh, 0CEh, 0FFh, 50h, 28h, 8Bh, 54h, 24h, 14h, 8Dh, 0Ch, 40h, 8Dh, 8Ch, 8Ah, 0BCh
    db 00h, 00h, 00h, 8Bh, 51h, 04h, 2Bh, 11h, 89h, 46h, 1Ch, 0C1h, 0FAh, 02h, 89h, 56h
    db 18h, 8Bh, 41h, 04h, 3Bh, 41h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 30h, 83h
    db 41h, 04h, 04h, 0EBh, 14h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 1Bh, 52h, 8Dh, 54h
    db 24h, 28h, 52h, 50h, 0E8h, 0E0h, 82h, 0CAh, 0FFh, 8Bh, 43h, 04h, 83h, 0C3h, 04h, 85h
    db 0C0h, 0Fh, 85h, 30h, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 8Bh, 80h, 88h, 00h, 00h
    db 00h, 85h, 0C0h, 89h, 44h, 24h, 18h, 0Fh, 85h, 06h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh
    db 5Bh, 83h, 0C4h, 10h, 0C3h
?d_0038e6f0@@YAXXZ ENDP

; ghidra: FUN_0078ed80  retail @ 0x0038ED80 size 114
public ?d_0038ed80@@YAXXZ
?d_0038ed80@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 57h, 40h, 50h, 0E8h, 0A0h, 01h, 0CBh
    db 0FFh, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 8Bh, 54h, 24h, 18h, 2Bh, 0C8h, 0C1h, 0F9h, 02h
    db 51h, 52h, 8Bh, 0CEh, 0E8h, 9Ch, 8Dh, 0CBh, 0FFh, 8Bh, 0D8h, 8Bh, 46h, 04h, 8Bh, 0Ch
    db 98h, 6Ah, 0Ch, 89h, 4Ch, 24h, 14h, 0E8h, 84h, 0F7h, 49h, 00h, 8Bh, 54h, 24h, 1Ch
    db 8Bh, 0F8h, 52h, 8Dh, 6Fh, 04h, 55h, 0C7h, 07h, 00h, 00h, 00h, 00h, 0E8h, 2Dh, 32h
    db 0C7h, 0FFh, 8Bh, 44h, 24h, 1Ch, 89h, 07h, 8Bh, 4Eh, 04h, 89h, 3Ch, 99h, 8Bh, 46h
    db 10h, 83h, 0C4h, 0Ch, 40h, 5Fh, 89h, 46h, 10h, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_0038ed80@@YAXXZ ENDP

; ghidra: FUN_0078ee10  retail @ 0x0038EE10 size 114
public ?d_0038ee10@@YAXXZ
?d_0038ee10@@YAXXZ PROC
    db 51h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 57h, 40h, 50h, 0E8h, 68h, 14h, 0C9h
    db 0FFh, 8Bh, 4Eh, 08h, 8Bh, 46h, 04h, 8Bh, 54h, 24h, 18h, 2Bh, 0C8h, 0C1h, 0F9h, 02h
    db 51h, 52h, 8Bh, 0CEh, 0E8h, 9Dh, 0FEh, 0C8h, 0FFh, 8Bh, 0D8h, 8Bh, 46h, 04h, 8Bh, 0Ch
    db 98h, 6Ah, 0Ch, 89h, 4Ch, 24h, 14h, 0E8h, 0F4h, 0F6h, 49h, 00h, 8Bh, 54h, 24h, 1Ch
    db 8Bh, 0F8h, 52h, 8Dh, 6Fh, 04h, 55h, 0C7h, 07h, 00h, 00h, 00h, 00h, 0E8h, 0EFh, 41h
    db 0C9h, 0FFh, 8Bh, 44h, 24h, 1Ch, 89h, 07h, 8Bh, 4Eh, 04h, 89h, 3Ch, 99h, 8Bh, 46h
    db 10h, 83h, 0C4h, 0Ch, 40h, 5Fh, 89h, 46h, 10h, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 59h, 0C2h
    db 04h, 00h
?d_0038ee10@@YAXXZ ENDP

; ghidra: FUN_0078eea0  retail @ 0x0038EEA0 size 65
public ?d_0038eea0@@YAXXZ
?d_0038eea0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 8Bh, 51h, 04h, 8Bh, 41h, 08h, 2Bh, 0C2h, 8Bh, 16h
    db 0C1h, 0F8h, 02h, 50h, 83h, 0C2h, 04h, 52h, 0E8h, 88h, 8Ch, 0CBh, 0FFh, 8Bh, 76h, 04h
    db 8Bh, 4Eh, 08h, 8Bh, 0D0h, 2Bh, 4Eh, 04h, 0C1h, 0F9h, 02h, 33h, 0C0h, 8Dh, 49h, 00h
    db 42h, 3Bh, 0D1h, 73h, 0Ah, 8Bh, 46h, 04h, 8Bh, 04h, 90h, 85h, 0C0h, 74h, 0F1h, 5Eh
    db 0C3h
?d_0038eea0@@YAXXZ ENDP

; ghidra: FUN_0078ef00  retail @ 0x0038EF00 size 65
public ?d_0038ef00@@YAXXZ
?d_0038ef00@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 04h, 8Bh, 51h, 04h, 8Bh, 41h, 08h, 2Bh, 0C2h, 8Bh, 16h
    db 0C1h, 0F8h, 02h, 50h, 83h, 0C2h, 04h, 52h, 0E8h, 0B9h, 0FDh, 0C8h, 0FFh, 8Bh, 76h, 04h
    db 8Bh, 4Eh, 08h, 8Bh, 0D0h, 2Bh, 4Eh, 04h, 0C1h, 0F9h, 02h, 33h, 0C0h, 8Dh, 49h, 00h
    db 42h, 3Bh, 0D1h, 73h, 0Ah, 8Bh, 46h, 04h, 8Bh, 04h, 90h, 85h, 0C0h, 74h, 0F1h, 5Eh
    db 0C3h
?d_0038ef00@@YAXXZ ENDP

; ghidra: FUN_0078f4b0  retail @ 0x0038F4B0 size 608
public ?d_0038f4b0@@YAXXZ
?d_0038f4b0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 86h, 0A0h, 01h, 00h, 00h, 33h, 0DBh, 3Bh, 0C3h, 57h, 75h
    db 05h, 0E8h, 0FAh, 0CFh, 56h, 00h, 0FFh, 86h, 0A0h, 01h, 00h, 00h, 8Dh, 4Eh, 0Ch, 0E8h
    db 53h, 0CEh, 0C9h, 0FFh, 8Dh, 4Eh, 20h, 0E8h, 7Eh, 82h, 0C9h, 0FFh, 8Dh, 0BEh, 0B0h, 00h
    db 00h, 00h, 8Bh, 0CFh, 0E8h, 2Dh, 56h, 0CBh, 0FFh, 68h, 00h, 20h, 00h, 00h, 8Bh, 0CFh
    db 0E8h, 0FBh, 17h, 0CBh, 0FFh, 88h, 9Eh, 1Ch, 01h, 00h, 00h, 88h, 9Eh, 1Dh, 01h, 00h
    db 00h, 0C6h, 86h, 1Eh, 01h, 00h, 00h, 01h, 0C6h, 86h, 1Fh, 01h, 00h, 00h, 01h, 0C6h
    db 86h, 96h, 00h, 00h, 00h, 01h, 0E8h, 0A5h, 0CFh, 56h, 00h, 8Bh, 0CEh, 89h, 9Eh, 4Ch
    db 01h, 00h, 00h, 89h, 9Eh, 50h, 01h, 00h, 00h, 89h, 9Eh, 54h, 01h, 00h, 00h, 89h
    db 9Eh, 58h, 01h, 00h, 00h, 0E8h, 07h, 21h, 0CBh, 0FFh, 0C7h, 86h, 08h, 01h, 00h, 00h
    db 01h, 00h, 00h, 00h, 89h, 9Eh, 6Ch, 01h, 00h, 00h, 8Bh, 0Dh, 0FCh, 0F4h, 2Eh, 01h
    db 8Bh, 01h, 0FFh, 50h, 10h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h, 8Bh, 11h, 0FFh, 52h, 10h
    db 8Bh, 0Dh, 0BCh, 0D5h, 2Eh, 01h, 8Bh, 01h, 0FFh, 50h, 10h, 8Bh, 0Dh, 0C4h, 0D5h, 2Eh
    db 01h, 8Bh, 11h, 0FFh, 52h, 10h, 8Bh, 0Dh, 0C0h, 0D5h, 2Eh, 01h, 8Bh, 01h, 0FFh, 50h
    db 10h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 8Bh, 51h, 04h, 83h, 0C1h, 04h, 0FFh, 52h, 10h
    db 8Bh, 0Dh, 14h, 0F2h, 2Eh, 01h, 8Bh, 01h, 0FFh, 50h, 10h, 8Bh, 0Dh, 6Ch, 07h, 2Fh
    db 01h, 8Bh, 11h, 0FFh, 52h, 10h, 8Bh, 0Dh, 44h, 10h, 2Fh, 01h, 8Bh, 01h, 0FFh, 50h
    db 10h, 8Bh, 0Dh, 0F0h, 0F4h, 2Eh, 01h, 8Bh, 51h, 04h, 83h, 0C1h, 04h, 0FFh, 52h, 10h
    db 33h, 0C0h, 8Dh, 8Eh, 28h, 01h, 00h, 00h, 0EBh, 06h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 88h, 9Ch, 06h, 20h, 01h, 00h, 00h, 89h, 19h, 40h, 83h, 0C1h, 04h, 83h, 0F8h, 08h
    db 7Ch, 0EEh, 88h, 9Eh, 48h, 01h, 00h, 00h, 8Bh, 0Dh, 3Ch, 0D6h, 2Eh, 01h, 3Bh, 0CBh
    db 74h, 16h, 8Bh, 0F9h, 0E8h, 10h, 79h, 0C8h, 0FFh, 57h, 0E8h, 0B1h, 28h, 4Fh, 00h, 83h
    db 0C4h, 04h, 89h, 1Dh, 3Ch, 0D6h, 2Eh, 01h, 8Bh, 86h, 0ACh, 01h, 00h, 00h, 8Bh, 38h
    db 3Bh, 0F8h, 74h, 23h, 55h, 8Bh, 0EFh, 8Bh, 3Fh, 8Dh, 4Dh, 08h, 0E8h, 12h, 0ABh, 0CBh
    db 0FFh, 6Ah, 10h, 55h, 0E8h, 0C7h, 0EFh, 49h, 00h, 8Bh, 86h, 0ACh, 01h, 00h, 00h, 83h
    db 0C4h, 08h, 3Bh, 0F8h, 75h, 0DFh, 5Dh, 8Bh, 86h, 0ACh, 01h, 00h, 00h, 89h, 00h, 8Bh
    db 86h, 0ACh, 01h, 00h, 00h, 53h, 8Bh, 0CEh, 89h, 40h, 04h, 0E8h, 43h, 52h, 0C9h, 0FFh
    db 0C6h, 86h, 90h, 00h, 00h, 00h, 01h, 0C6h, 86h, 91h, 00h, 00h, 00h, 01h, 0C6h, 86h
    db 92h, 00h, 00h, 00h, 01h, 0C6h, 86h, 93h, 00h, 00h, 00h, 01h, 0C7h, 86h, 98h, 00h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0C7h, 86h, 9Ch, 00h, 00h, 00h, 01h, 00h, 00h, 00h
    db 8Bh, 3Dh, 0F0h, 18h, 2Fh, 01h, 38h, 5Fh, 08h, 74h, 0Ch, 8Bh, 07h, 6Ah, 01h, 8Bh
    db 0CFh, 0FFh, 10h, 33h, 0FFh, 0EBh, 0Fh, 8Bh, 4Fh, 04h, 3Bh, 0CBh, 74h, 08h, 0E8h, 79h
    db 36h, 0CAh, 0FFh, 89h, 47h, 04h, 89h, 3Dh, 0F0h, 18h, 2Fh, 01h, 8Bh, 3Dh, 0F8h, 15h
    db 2Fh, 01h, 38h, 5Fh, 08h, 74h, 0Ch, 8Bh, 17h, 6Ah, 01h, 8Bh, 0CFh, 0FFh, 12h, 33h
    db 0FFh, 0EBh, 0Fh, 8Bh, 4Fh, 04h, 3Bh, 0CBh, 74h, 08h, 0E8h, 4Dh, 36h, 0CAh, 0FFh, 89h
    db 47h, 04h, 89h, 3Dh, 0F8h, 15h, 2Fh, 01h, 8Bh, 0CEh, 89h, 9Eh, 8Ch, 00h, 00h, 00h
    db 89h, 9Eh, 68h, 01h, 00h, 00h, 0E8h, 61h, 3Bh, 0C7h, 0FFh, 8Bh, 0CEh, 88h, 5Eh, 6Ch
    db 0E8h, 91h, 3Dh, 0C7h, 0FFh, 8Bh, 86h, 0A0h, 01h, 00h, 00h, 48h, 5Fh, 88h, 5Eh, 40h
    db 89h, 5Eh, 3Ch, 0C7h, 86h, 90h, 02h, 00h, 00h, 02h, 00h, 00h, 00h, 89h, 86h, 0A0h
?d_0038f4b0@@YAXXZ ENDP

; ghidra: FUN_0078f7b0  retail @ 0x0038F7B0 size 2335
_TEXT ENDS
_TEXT$d0078f7b0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x0078F7B0 size 2335
public ?d_0038f7b0@@YAXXZ
?d_0038f7b0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0101C096
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 0F8h, 000h, 000h, 000h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 040h, 014h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 053h, 055h, 056h, 057h, 005h, 0D8h, 000h, 000h, 000h, 050h, 0C6h, 044h, 024h, 017h, 001h
    call ?j_00028560@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 089h, 044h, 024h, 024h, 08Bh, 041h, 014h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 005h, 0DCh, 000h, 000h, 000h, 050h
    call ?j_00028560@@YAXXZ
    db 08Bh, 0F0h, 033h, 0EDh, 03Bh, 0F5h, 089h, 074h, 024h, 050h, 075h, 004h, 089h, 06Ch, 024h, 024h
    db 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 042h, 014h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 005h, 0E0h, 000h, 000h, 000h, 050h
    call ?j_00028560@@YAXXZ
    db 08Bh, 0F8h, 03Bh, 0FDh, 089h, 07Ch, 024h, 04Ch, 075h, 004h, 089h, 06Ch, 024h, 024h, 08Bh, 00Dh
    dd ?TheBfmeGlobal_012ed62c@@3PAVBfmeGlobal_012ed62c@@A
    db 0C6h, 044h, 024h, 014h, 000h
    call ?j_0004a7a5@@YAXXZ
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 089h, 00Ch, 001h, 000h, 000h, 083h, 0F9h, 006h, 075h, 002h, 032h, 0C0h, 083h, 0F9h, 002h
    db 074h, 004h, 084h, 0C0h, 075h, 063h, 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 042h, 014h, 08Ah, 088h, 0D4h, 000h, 000h, 000h, 084h, 0C9h, 074h, 03Ah, 0A1h
    dd ?Rva012ED5AC@@3PAVOptionPreferences@@A
    db 083h, 0B8h, 0C4h, 016h, 000h, 000h, 001h, 07Fh, 02Ch, 08Bh, 04Ch, 024h, 024h, 03Bh, 0CDh, 074h
    db 024h, 0C6h, 044h, 024h, 014h, 001h
    call ?j_000267c9@@YAXXZ
    db 08Bh, 0CEh, 089h, 044h, 024h, 024h
    call ?j_000267c9@@YAXXZ
    db 08Bh, 0CFh, 089h, 044h, 024h, 050h
    call ?j_000267c9@@YAXXZ
    db 089h, 044h, 024h, 04Ch, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 041h, 014h, 08Ah, 088h, 0E8h, 000h, 000h, 000h, 084h, 0C9h, 00Fh, 094h, 044h, 024h, 013h
    db 06Ah, 014h, 089h, 06Ch, 024h, 03Ch
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 089h, 044h, 024h, 03Ch, 089h, 06Ch, 024h, 040h, 0C6h, 000h, 000h, 08Bh, 054h, 024h, 03Ch, 089h
    db 06Ah, 004h, 08Bh, 044h, 024h, 03Ch, 089h, 040h, 008h, 08Bh, 044h, 024h, 03Ch, 089h, 040h, 00Ch
    db 083h, 0C4h, 004h, 089h, 06Ch, 024h, 044h, 0C6h, 044h, 024h, 048h, 001h, 0A1h
    dd ?BfmeTheMapObjectListHolder@@3PAUMapObjectList@@A
    db 08Bh, 018h, 03Bh, 0DDh, 089h, 0ACh, 024h, 010h, 001h, 000h, 000h, 089h, 06Ch, 024h, 018h, 00Fh
    db 084h, 070h, 007h, 000h, 000h, 08Bh, 00Dh
    dd ?AssetSubsystem0059A3D0@@3PAXA
    db 08Bh, 011h, 0FFh, 052h, 014h
    call ?Rva0090F050@@YAXXZ
    db 08Bh, 035h
    dd __imp__Sleep@4
    db 055h, 0FFh, 0D6h, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 03Bh, 0CDh, 074h, 005h, 08Bh, 001h, 0FFh, 050h, 040h, 0F6h, 043h, 020h, 036h, 00Fh, 085h, 033h
    db 007h, 000h, 000h, 055h, 0FFh, 0D6h, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 03Bh, 0CDh, 074h, 005h, 08Bh, 011h, 0FFh, 052h, 040h, 053h
    call ?j_0001c549@@YAXXZ
    db 083h, 0C4h, 004h, 08Bh, 0CBh
    call ?j_00012814@@YAXXZ
    db 08Bh, 0F0h, 03Bh, 0F5h, 00Fh, 084h, 007h, 007h, 000h, 000h, 08Ah, 086h, 085h, 004h, 000h, 000h
    db 084h, 0C0h, 00Fh, 085h, 0F9h, 006h, 000h, 000h, 08Bh, 084h, 024h, 01Ch, 001h, 000h, 000h, 03Bh
    db 0C5h, 074h, 020h, 08Bh, 008h, 08Bh, 0C1h, 083h, 0E1h, 01Fh, 0BAh, 001h, 000h, 000h, 000h, 0C1h
    db 0E8h, 005h, 08Bh, 084h, 086h, 0C8h, 000h, 000h, 000h, 0D3h, 0E2h, 085h, 0D0h, 00Fh, 085h, 0CEh
    db 006h, 000h, 000h, 08Bh, 084h, 024h, 020h, 001h, 000h, 000h, 03Bh, 0C5h, 074h, 020h, 08Bh, 008h
    db 08Bh, 0C1h, 083h, 0E1h, 01Fh, 0BAh, 001h, 000h, 000h, 000h, 0C1h, 0E8h, 005h, 08Bh, 084h, 086h
    db 0C8h, 000h, 000h, 000h, 0D3h, 0E2h, 085h, 0D0h, 00Fh, 084h, 0A3h, 006h, 000h, 000h, 0F6h, 086h
    db 0C8h, 000h, 000h, 000h, 040h, 074h, 00Ch, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 00Fh, 084h, 08Eh
    db 006h, 000h, 000h, 08Bh, 0CBh
    call ?j_0001325a@@YAXXZ
    db 08Bh, 008h, 089h, 04Ch, 024h, 028h, 08Bh, 050h, 004h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 089h, 054h, 024h, 02Ch, 08Bh, 040h, 008h, 089h, 044h, 024h, 030h, 08Bh, 044h, 024h, 02Ch, 08Bh
    db 011h, 055h, 050h, 08Bh, 044h, 024h, 030h, 050h, 0FFh, 052h, 018h, 0D8h, 044h, 024h, 030h, 08Bh
    db 04Bh, 01Ch, 08Bh, 0D1h, 052h, 0D9h, 05Ch, 024h, 034h, 089h, 08Ch, 024h, 08Ch, 000h, 000h, 000h
    call ?j_0000991c@@YAXXZ
    db 0D9h, 05Ch, 024h, 038h, 08Bh, 08Eh, 0D4h, 000h, 000h, 000h, 08Bh, 086h, 0CCh, 000h, 000h, 000h
    db 0C1h, 0E9h, 003h, 083h, 0C4h, 004h, 080h, 0E1h, 001h, 0A9h, 000h, 000h, 004h, 000h, 074h, 019h
    db 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 086h, 098h, 003h, 000h, 000h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 00Fh, 08Bh, 04Ch
    db 003h, 000h, 000h, 084h, 0C9h, 00Fh, 085h, 044h, 003h, 000h, 000h, 0F7h, 086h, 0D0h, 000h, 000h
    db 000h, 000h, 000h, 000h, 020h, 00Fh, 085h, 034h, 003h, 000h, 000h, 06Ah, 05Eh, 08Bh, 0CEh
    call ?j_000032d8@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 023h, 003h, 000h, 000h, 055h, 0B9h
    dd ?TheKey_originalOwner@@3VStaticNameKey@@B
    db 08Dh, 07Bh, 024h
    call ?j_00009304@@YAXXZ
    db 050h, 08Dh, 044h, 024h, 028h, 050h, 08Bh, 0CFh
    call ?forward@Rva0002FF6DStringPresenceThunk@@QBE?AVAsciiString@@HPA_N@Z
    db 053h, 051h, 08Dh, 054h, 024h, 028h, 089h, 064h, 024h, 05Ch, 08Bh, 0CCh, 052h, 0C6h, 084h, 024h
    db 01Ch, 001h, 000h, 000h, 001h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    call ?j_0001be82@@YAXXZ
    db 08Bh, 0E8h, 0A1h
    dd ?PlayerList005999B0@@3PAUPlayers005999B0@@A
    db 08Bh, 040h, 014h, 039h, 0A8h, 030h, 002h, 000h, 000h, 075h, 03Eh, 08Bh, 044h, 024h, 020h, 085h
    db 0C0h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 06Ah, 007h, 050h, 068h
    dd g_Va010EB5BC
    db 0FFh, 015h
    dd __imp__strncmp
    db 083h, 0C4h, 00Ch, 085h, 0C0h, 075h, 017h, 08Dh, 04Ch, 024h, 020h, 088h, 084h, 024h, 010h, 001h
    db 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0EDh, 0E9h, 051h, 005h, 000h, 000h, 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 051h, 08Dh
    db 054h, 024h, 03Ch, 052h, 08Bh, 0CEh, 0C6h, 084h, 024h, 094h, 000h, 000h, 000h, 000h
    call ?j_00017a12@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 040h, 083h, 0F8h, 014h, 089h, 044h, 024h, 018h, 075h, 01Eh, 08Dh, 044h
    db 024h, 038h, 050h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h
    call ?Rva009EBAC0@@YAXH@Z
    db 083h, 0C4h, 004h, 08Dh, 04Ch, 024h, 038h
    call ?j_000076cb@@YAXXZ
    db 08Ah, 084h, 024h, 024h, 001h, 000h, 000h, 084h, 0C0h, 074h, 018h, 08Dh, 04Ch, 024h, 020h, 0C6h
    db 084h, 024h, 010h, 001h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0EDh, 0E9h, 0E6h, 004h, 000h, 000h, 033h, 0C9h, 089h, 08Ch, 024h, 0A8h, 000h, 000h, 000h
    db 089h, 08Ch, 024h, 0ACh, 000h, 000h, 000h, 051h, 08Dh, 094h, 024h, 0ACh, 000h, 000h, 000h, 052h
    db 055h, 089h, 08Ch, 024h, 0BCh, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?Factory0040A260@@3PAVThingFactory@@A
    db 056h
    call ?j_0004494a@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 0D9h, 001h, 000h, 000h, 0F6h, 043h, 020h, 001h, 075h, 00Dh
    db 06Ah, 005h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 012h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 028h, 085h, 0C0h, 074h, 007h, 083h
    db 088h, 010h, 001h, 000h, 000h, 001h, 08Dh, 04Ch, 024h, 017h, 051h, 0B9h
    dd g_Va012A7910
    call ?j_00009304@@YAXXZ
    db 050h, 08Bh, 0CFh
    call ?j_00043a1d@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 082h, 000h, 000h, 000h, 08Ah, 044h, 024h, 017h, 084h, 0C0h, 074h, 07Ah
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 06Ah, 001h, 08Dh, 084h, 024h, 0C4h, 000h, 000h, 000h, 050h, 08Bh, 044h, 024h, 034h, 06Ah, 001h
    db 050h, 08Bh, 044h, 024h, 038h, 0C7h, 084h, 024h, 0ACh, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    db 0C7h, 084h, 024h, 0B0h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0B4h, 000h
    db 000h, 000h, 000h, 000h, 000h, 000h, 08Bh, 011h, 050h, 0FFh, 052h, 01Ch, 0DDh, 0D8h, 08Dh, 08Ch
    db 024h, 0D8h, 000h, 000h, 000h, 051h, 08Bh, 04Ch, 024h, 038h, 08Dh, 094h, 024h, 0C4h, 000h, 000h
    db 000h, 052h, 08Dh, 084h, 024h, 0A4h, 000h, 000h, 000h, 050h, 051h
    call ?j_000019f1@@YAXXZ
    db 083h, 0C4h, 010h, 08Dh, 094h, 024h, 0D8h, 000h, 000h, 000h, 052h, 08Bh, 0CEh
    call ?j_000361ce@@YAXXZ
    db 0EBh, 00Ch, 08Bh, 044h, 024h, 034h, 050h, 08Bh, 0CEh
    call ?j_000399A5@@YAXXZ
    db 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 0CEh
    call ?j_0003a1a7@@YAXXZ
    db 057h, 08Bh, 0CEh
    call ?j_000441b1@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Dh, 054h, 024h, 028h, 052h, 056h
    call ?j_0001c675@@YAXXZ
    db 050h, 08Bh, 0CEh
    call ?j_00035e0e@@YAXXZ
    db 06Ah, 000h, 0FFh, 015h
    dd __imp__Sleep@4
    db 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 085h, 0C9h, 074h, 005h, 08Bh, 001h, 0FFh, 050h, 040h, 08Bh, 00Dh
    dd ?AssetSubsystem0059A3D0@@3PAXA
    db 08Bh, 011h, 0FFh, 052h, 014h
    call ?Rva0090F050@@YAXXZ
    db 08Bh, 0BEh, 0F0h, 001h, 000h, 000h, 083h, 03Fh, 000h, 074h, 03Dh, 08Dh, 09Bh, 000h, 000h, 000h
    db 000h, 06Ah, 000h, 0FFh, 015h
    dd __imp__Sleep@4
    db 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 085h, 0C9h, 074h, 005h, 08Bh, 001h, 0FFh, 050h, 040h, 08Bh, 007h, 08Bh, 050h, 00Ch, 08Dh, 048h
    db 00Ch, 0FFh, 052h, 00Ch, 085h, 0C0h, 074h, 007h, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 052h, 004h, 08Bh
    db 047h, 004h, 083h, 0C7h, 004h, 085h, 0C0h, 075h, 0C9h, 08Ah, 045h, 031h, 084h, 0C0h, 075h, 008h
    db 0C6h, 045h, 032h, 001h, 0C6h, 045h, 031h, 001h, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 056h
    call ?j_0000b81b@@YAXXZ
    db 08Bh, 03Dh
    dd __imp__Sleep@4
    db 06Ah, 000h, 0FFh, 0D7h, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 085h, 0C9h, 074h, 005h, 08Bh, 011h, 0FFh, 052h, 040h, 08Bh, 08Ch, 024h, 018h, 001h, 000h, 000h
    db 08Dh, 084h, 024h, 094h, 000h, 000h, 000h, 050h, 089h, 0B4h, 024h, 098h, 000h, 000h, 000h, 089h
    db 09Ch, 024h, 09Ch, 000h, 000h, 000h
    call ?j_0003a855@@YAXXZ
    db 06Ah, 000h, 0FFh, 0D7h, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 085h, 0C9h, 074h, 005h, 08Bh, 011h, 0FFh, 052h, 040h, 08Dh, 04Ch, 024h, 020h, 0C6h, 084h, 024h
    db 010h, 001h, 000h, 000h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 033h, 0EDh, 0E9h, 0BEh, 002h, 000h, 000h, 08Dh, 044h, 024h, 016h, 050h, 0B9h
    dd g_Va012A7800
    db 08Dh, 07Bh, 024h
    call ?j_00009304@@YAXXZ
    db 050h, 08Bh, 0CFh
    call ?j_000184b2@@YAXXZ
    db 0D9h, 05Ch, 024h, 054h, 08Dh, 04Ch, 024h, 015h, 051h, 0B9h
    dd g_Va012A7910
    db 0C7h, 044h, 024h, 05Ch, 000h, 000h, 080h, 03Fh, 0C7h, 044h, 024h, 060h, 000h, 000h, 000h, 000h
    db 0C7h, 044h, 024h, 064h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 068h, 000h, 000h, 000h, 000h
    db 0C7h, 044h, 024h, 06Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 070h, 000h, 000h, 080h, 03Fh
    db 0C7h, 044h, 024h, 074h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 078h, 000h, 000h, 000h, 000h
    db 0C7h, 044h, 024h, 07Ch, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h, 000h
    db 000h, 000h, 000h, 0C7h, 084h, 024h, 084h, 000h, 000h, 000h, 000h, 000h, 080h, 03Fh, 0C7h, 084h
    db 024h, 088h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    call ?j_00009304@@YAXXZ
    db 050h, 08Bh, 0CFh
    call ?j_00043a1d@@YAXXZ
    db 084h, 0C0h, 074h, 073h, 08Ah, 044h, 024h, 015h, 084h, 0C0h, 074h, 06Bh, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 08Bh, 011h, 06Ah, 001h, 08Dh, 084h, 024h, 0D0h, 000h, 000h, 000h, 050h, 08Bh, 044h, 024h, 034h
    db 06Ah, 001h, 050h, 08Bh, 044h, 024h, 038h, 050h, 0FFh, 052h, 01Ch, 0DDh, 0D8h, 08Dh, 04Ch, 024h
    db 058h, 051h, 08Bh, 04Ch, 024h, 038h, 08Dh, 094h, 024h, 0D0h, 000h, 000h, 000h, 052h, 08Dh, 084h
    db 024h, 0BCh, 000h, 000h, 000h, 050h, 051h, 0C7h, 084h, 024h, 0C4h, 000h, 000h, 000h, 000h, 000h
    db 000h, 000h, 0C7h, 084h, 024h, 0C8h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 084h, 024h
    db 0CCh, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    call ?j_000019f1@@YAXXZ
    db 083h, 0C4h, 010h, 0E9h, 087h, 000h, 000h, 000h, 0D9h, 043h, 01Ch, 0D9h, 0C0h, 0D9h, 0FFh, 0D9h
    db 0C9h, 0D9h, 0FEh, 0D9h, 044h, 024h, 058h, 0D9h, 044h, 024h, 05Ch, 0D8h, 0CAh, 0D9h, 044h, 024h
    db 058h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 058h, 0D9h, 044h, 024h, 05Ch, 0D8h, 0CBh, 0D9h
    db 0C2h, 0D8h, 0CAh, 0DEh, 0E9h, 0D9h, 05Ch, 024h, 05Ch, 0DDh, 0D8h, 0D9h, 044h, 024h, 068h, 0D9h
    db 044h, 024h, 06Ch, 0D8h, 0CAh, 0D9h, 044h, 024h, 068h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h
    db 068h, 0D9h, 044h, 024h, 06Ch, 0D8h, 0CBh, 0D9h, 0C2h, 0D8h, 0CAh, 0DEh, 0E9h, 0D9h, 05Ch, 024h
    db 06Ch, 0DDh, 0D8h, 0D9h, 044h, 024h, 078h, 0D9h, 044h, 024h, 07Ch, 0D8h, 0CAh, 0D9h, 044h, 024h
    db 078h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 05Ch, 024h, 078h, 0D9h, 044h, 024h, 07Ch, 0D8h, 0CBh, 0D9h
    db 0CAh, 0D8h, 0C9h, 0DEh, 0EAh, 0D9h, 0C9h, 0D9h, 05Ch, 024h, 07Ch, 0DDh, 0D8h, 0DDh, 0D8h, 08Ah
    db 044h, 024h, 016h, 084h, 0C0h, 08Bh, 096h, 0C0h, 003h, 000h, 000h, 089h, 054h, 024h, 01Ch, 074h
    db 00Ch, 0D9h, 044h, 024h, 01Ch, 0D8h, 04Ch, 024h, 054h, 0D9h, 05Ch, 024h, 01Ch, 08Dh, 084h, 024h
    db 090h, 000h, 000h, 000h, 050h, 08Dh, 04Ch, 024h, 03Ch, 051h, 08Bh, 0CEh, 0C6h, 084h, 024h, 098h
    db 000h, 000h, 000h, 000h
    call ?j_00017a12@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 040h, 083h, 0F8h, 014h, 089h, 044h, 024h, 018h, 075h, 01Ah, 08Dh, 054h
    db 024h, 038h, 052h, 089h, 06Ch, 024h, 01Ch
    call ?Rva009EBAC0@@YAXH@Z
    db 083h, 0C4h, 004h, 08Dh, 04Ch, 024h, 038h
    call ?j_000076cb@@YAXXZ
    db 08Ah, 084h, 024h, 024h, 001h, 000h, 000h, 084h, 0C0h, 00Fh, 085h, 0B1h, 000h, 000h, 000h, 06Ah
    db 05Dh, 08Bh, 0CEh
    call ?j_000032d8@@YAXXZ
    db 084h, 0C0h, 074h, 075h, 08Bh, 04Ch, 024h, 024h, 03Bh, 0CDh, 074h, 048h, 08Ah, 044h, 024h, 014h
    db 084h, 0C0h, 074h, 040h, 08Ah, 086h, 08Bh, 004h, 000h, 000h, 084h, 0C0h, 074h, 012h, 08Ah, 096h
    db 08Ch, 004h, 000h, 000h, 084h, 0D2h, 074h, 004h, 08Bh, 0F1h, 0EBh, 016h, 084h, 0C0h, 075h, 00Eh
    db 08Ah, 086h, 08Ch, 004h, 000h, 000h, 084h, 0C0h, 08Bh, 074h, 024h, 050h, 075h, 004h, 08Bh, 074h
    db 024h, 04Ch, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 040h, 014h, 08Bh, 088h, 0E4h, 000h, 000h, 000h, 089h, 04Ch, 024h, 01Ch, 08Ah, 044h, 024h
    db 013h, 084h, 0C0h, 074h, 04Ch, 08Bh, 054h, 024h, 01Ch, 052h, 08Dh, 044h, 024h, 05Ch, 050h, 08Dh
    db 04Ch, 024h, 030h, 051h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 056h
    call ?j_000364ad@@YAXXZ
    db 0EBh, 02Fh, 06Ah, 05Eh, 08Bh, 0CEh
    call ?j_000032d8@@YAXXZ
    db 08Bh, 054h, 024h, 01Ch, 052h, 084h, 0C0h, 08Dh, 044h, 024h, 05Ch, 08Dh, 04Ch, 024h, 02Ch, 050h
    db 051h, 08Bh, 00Dh
    dd ?Rva012ef4cc@@3PAVRva0041D290Client@@A
    db 056h, 074h, 007h
    call ?j_000050c9@@YAXXZ
    db 0EBh, 005h
    call ?j_00037f83@@YAXXZ
    db 08Bh, 05Bh, 004h, 03Bh, 0DDh, 00Fh, 085h, 090h, 0F8h, 0FFh, 0FFh, 08Dh, 054h, 024h, 038h, 052h
    call ?Rva009EBAC0@@YAXH@Z
    db 083h, 0C4h, 004h, 08Dh, 04Ch, 024h, 038h, 0C7h, 084h, 024h, 010h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?j_00015d7a@@YAXXZ
    db 08Bh, 08Ch, 024h, 008h, 001h, 000h, 000h, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h
    db 000h, 05Bh, 081h, 0C4h, 004h, 001h, 000h, 000h, 0C2h, 010h, 000h
?d_0038f7b0@@YAXXZ ENDP
_TEXT$d0078f7b0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00790320  retail @ 0x00390320 size 168
_TEXT ENDS
_TEXT$d00790320 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00790320 size 168
public ?d_00390320@@YAXXZ
?d_00390320@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0101C0C0
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 008h, 056h, 057h, 08Bh, 0F1h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h
    db 008h, 000h, 000h, 000h, 000h, 08Dh, 044h, 024h, 020h, 050h, 08Dh, 04Ch, 024h, 00Ch, 0C6h, 044h
    db 024h, 01Ch, 001h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 066h, 08Bh, 04Ch, 024h, 024h, 08Bh, 0BEh, 0ACh, 001h, 000h, 000h, 06Ah, 010h, 066h, 089h, 04Ch
    db 024h, 010h
    call ?allocate@__new_alloc@_STL@@SAPAXI@Z
    db 08Bh, 0F0h, 08Dh, 054h, 024h, 00Ch, 052h, 08Dh, 046h, 008h, 050h
    call ?j_000057e5@@YAXXZ
    db 08Bh, 047h, 004h, 089h, 03Eh, 089h, 046h, 004h, 089h, 030h, 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h
    db 008h, 089h, 077h, 004h, 0C6h, 044h, 024h, 018h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Ch, 024h, 020h, 0C7h, 044h, 024h, 018h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 010h, 05Fh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 014h
    db 0C2h, 008h, 000h
?d_00390320@@YAXXZ ENDP
_TEXT$d00790320 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
