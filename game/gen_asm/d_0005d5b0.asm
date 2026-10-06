.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??2@YAPAXI@Z:NEAR
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_7Rva0005C110Surface@@6B@:BYTE
EXTERN ?EngineGlobal007629F0@@3PAUEngine007629F0@@A:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?GetSymbol@Signature@DebugStackwalk@@SAXIPADI@Z:NEAR
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?Shutdown@WW3D@@SA_NXZ:NEAR
EXTERN ?TheVersion@@3PAVVersion@@A:BYTE
EXTERN ?d_0005f2b0@@YAXXZ:NEAR
EXTERN ?g_count0134FB34@@3HA:BYTE
EXTERN ?g_lock0134FB1C@@3UCriticalSection@@A:BYTE
EXTERN ?g_lookup@@3P6APAXPAX0@ZA:BYTE
EXTERN ?j_00002f72@@YAXXZ:NEAR
EXTERN ?j_00007cb1@@YAXXZ:NEAR
EXTERN ?j_00009ef8@@YAXXZ:NEAR
EXTERN ?j_0000a425@@YAXXZ:NEAR
EXTERN ?j_000132af@@YAXXZ:NEAR
EXTERN ?j_000246ea@@YAXXZ:NEAR
EXTERN ?j_0002ad6a@@YAXXZ:NEAR
EXTERN ?j_0002f608@@YAXXZ:NEAR
EXTERN ?j_00031160@@YAXXZ:NEAR
EXTERN ?j_00033b54@@YAXXZ:NEAR
EXTERN ?j_000347c5@@YAXXZ:NEAR
EXTERN ?j_000476db@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN __imp__CloseHandle@4:BYTE
EXTERN __imp__EnterCriticalSection@4:BYTE
EXTERN __imp__FreeLibrary@4:BYTE
EXTERN __imp__GetLastError@0:BYTE
EXTERN __imp__GetModuleFileNameA@12:BYTE
EXTERN __imp__GetProcAddress@8:BYTE
EXTERN __imp__LeaveCriticalSection@4:BYTE
EXTERN __imp__LoadLibraryA@4:BYTE
EXTERN __imp__SetCurrentDirectoryA@4:BYTE
EXTERN __imp__ShowWindow@8:BYTE
EXTERN __imp__sprintf:BYTE
EXTERN __imp__strpbrk:BYTE
EXTERN __imp__strtoul:BYTE
EXTERN g_Va00FF277C:NEAR
EXTERN g_Va010737D0:BYTE
EXTERN g_Va010737F0:BYTE
EXTERN g_Va010738A0:BYTE
EXTERN g_Va010738AC:BYTE
EXTERN g_Va010738C0:BYTE
EXTERN g_Va010738CC:BYTE
EXTERN g_Va010738DC:BYTE
EXTERN g_Va010738EC:BYTE
EXTERN g_Va010738FC:BYTE
EXTERN g_Va01073900:BYTE
EXTERN g_Va01073910:BYTE
EXTERN g_Va01073918:BYTE
EXTERN g_Va012A6504:BYTE
EXTERN g_Va012ED23C:BYTE
EXTERN g_Va012ED24C:BYTE
EXTERN g_Va012ED264:BYTE
EXTERN g_Va012ED270:BYTE
EXTERN g_Va01358CF8:BYTE
EXTERN g_Va01358FE4:BYTE
EXTERN g_Va01359078:BYTE
_TEXT SEGMENT

; retail @ 0x0005D5B0 size 88
public ?d_0005d5b0@@YAXXZ
?d_0005d5b0@@YAXXZ PROC
    db 85h, 0C0h, 74h, 53h, 8Ah, 08h, 84h, 0C9h, 56h, 57h, 8Bh, 0F8h, 74h, 23h, 8Bh, 0FFh
    db 80h, 0F9h, 20h, 77h, 08h, 8Ah, 4Fh, 01h, 47h, 84h, 0C9h, 75h, 0F3h, 3Bh, 0F8h, 74h
    db 10h, 8Bh, 0F0h, 8Bh, 0CFh, 2Bh, 0F7h, 8Ah, 11h, 88h, 14h, 0Eh, 41h, 84h, 0D2h, 75h
    db 0F6h, 8Bh, 0C8h, 8Dh, 71h, 01h, 8Ah, 11h, 41h, 84h, 0D2h, 75h, 0F9h, 2Bh, 0CEh, 49h
    db 78h, 13h, 80h, 3Fh, 00h, 74h, 0Eh, 80h, 3Ch, 01h, 20h, 77h, 08h, 49h, 0C6h, 44h
    db 01h, 01h, 00h, 79h, 0EDh, 5Fh, 5Eh, 0C3h
?d_0005d5b0@@YAXXZ ENDP

; retail @ 0x000600F0 size 1356
_TEXT ENDS
_TEXT$d004600f0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x004600F0 size 1356
public ?d_000600f0@@YAXXZ
?d_000600f0@@YAXXZ PROC
    db 055h, 08Bh, 0ECh, 06Ah, 0FFh, 068h
    dd g_Va00FF277C
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 098h, 003h, 000h, 000h, 053h, 056h, 057h, 089h, 065h, 0F0h, 068h
    dd g_Va010737F0
    db 0FFh, 015h
    dd __imp__LoadLibraryA@4
    db 08Bh, 0F0h, 033h, 0DBh, 03Bh, 0F3h, 074h, 01Bh, 068h
    dd g_Va010737D0
    db 056h, 0FFh, 015h
    dd __imp__GetProcAddress@8
    db 03Bh, 0C3h, 074h, 004h, 06Ah, 0FFh, 0FFh, 0D0h, 056h, 0FFh, 015h
    dd __imp__FreeLibrary@4
    db 08Bh, 045h, 010h, 0BAh
    dd g_Va012ED270
    db 02Bh, 0D0h, 08Dh, 064h, 024h, 000h, 08Ah, 008h, 088h, 00Ch, 002h, 040h, 03Ah, 0CBh, 075h, 0F6h
    db 068h, 004h, 001h, 000h, 000h, 08Dh, 085h, 060h, 0FEh, 0FFh, 0FFh, 050h, 053h, 089h, 05Dh, 0FCh
    db 0FFh, 015h
    dd __imp__GetModuleFileNameA@12
    db 08Dh, 085h, 060h, 0FEh, 0FFh, 0FFh, 08Dh, 050h, 001h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 08Ah, 008h, 040h, 03Ah, 0CBh, 075h, 0F9h, 02Bh, 0C2h, 08Dh, 084h, 005h, 060h, 0FEh, 0FFh, 0FFh
    db 08Dh, 08Dh, 060h, 0FEh, 0FFh, 0FFh, 03Bh, 0C1h, 074h, 007h, 080h, 038h, 05Ch, 075h, 05Eh, 088h
    db 018h, 08Dh, 095h, 060h, 0FEh, 0FFh, 0FFh, 052h, 0FFh, 015h
    dd __imp__SetCurrentDirectoryA@4
    db 068h
    dd g_Va01073918
    db 068h
    dd g_Va012ED270
    db 0C7h, 045h, 0ECh, 001h, 000h, 000h, 000h, 089h, 09Dh, 064h, 0FFh, 0FFh, 0FFh
    call ?j_000347c5@@YAXXZ
    db 083h, 0C4h, 008h, 08Bh, 0F0h, 090h, 08Bh, 045h, 0ECh, 083h, 0F8h, 014h, 00Fh, 08Dh, 008h, 001h
    db 000h, 000h, 03Bh, 0F3h, 00Fh, 084h, 000h, 001h, 000h, 000h, 080h, 03Eh, 096h, 075h, 003h, 0C6h
    db 006h, 02Dh, 08Bh, 0FEh, 08Bh, 0FFh, 08Ah, 007h, 03Ah, 0C3h, 074h, 00Ah, 03Ch, 020h, 077h, 006h
    db 047h, 0EBh, 0F3h, 048h, 0EBh, 090h, 03Bh, 0FEh, 074h, 00Eh, 08Bh, 0CFh, 08Bh, 0D6h, 08Ah, 001h
    db 041h, 088h, 002h, 042h, 03Ah, 0C3h, 075h, 0F6h, 08Bh, 0C6h, 08Dh, 050h, 001h, 08Ah, 008h, 040h
    db 03Ah, 0CBh, 075h, 0F9h, 02Bh, 0C2h, 048h, 03Bh, 0C3h, 07Ch, 00Fh, 038h, 01Fh, 074h, 00Bh, 080h
    db 03Ch, 030h, 020h, 077h, 005h, 088h, 01Ch, 030h, 0EBh, 0ECh, 08Bh, 045h, 0ECh, 08Bh, 03Dh
    dd ?g_lookup@@3P6APAXPAX0@ZA
    db 089h, 0B4h, 085h, 064h, 0FFh, 0FFh, 0FFh, 040h, 068h
    dd g_Va01073910
    db 056h, 089h, 045h, 0ECh, 0FFh, 0D7h, 083h, 0C4h, 008h, 085h, 0C0h, 075h, 007h, 0C6h, 005h
    dd g_Va012ED23C
    db 001h, 068h
    dd g_Va01073900
    db 056h, 0FFh, 0D7h, 08Bh, 035h
    dd g_Va012ED264
    db 083h, 0C4h, 008h, 03Bh, 0F3h, 075h, 007h, 033h, 0F6h, 0E9h, 056h, 0FFh, 0FFh, 0FFh, 08Bh, 03Dh
    dd __imp__strpbrk
    db 068h
    dd g_Va01073918
    db 056h, 0FFh, 0D7h, 083h, 0C4h, 008h, 03Bh, 0C6h, 088h, 05Dh, 012h, 088h, 05Dh, 013h, 075h, 01Ch
    db 08Ah, 006h, 088h, 045h, 012h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 038h, 006h, 075h, 003h, 046h
    db 0EBh, 0F9h, 03Ah, 0C3h, 074h, 006h, 08Dh, 045h, 012h, 050h, 0EBh, 005h, 068h
    dd g_Va01073918
    db 056h, 0FFh, 0D7h, 083h, 0C4h, 008h, 03Bh, 0C3h, 074h, 00Fh, 08Dh, 048h, 001h, 088h, 018h, 038h
    db 019h, 089h, 00Dh
    dd g_Va012ED264
    db 075h, 006h, 089h, 01Dh
    dd g_Va012ED264
    db 038h, 01Eh, 00Fh, 085h, 0F3h, 0FEh, 0FFh, 0FFh, 033h, 0F6h, 0E9h, 0ECh, 0FEh, 0FFh, 0FFh, 083h
    db 0F8h, 002h, 07Eh, 055h, 08Bh, 0B5h, 068h, 0FFh, 0FFh, 0FFh, 0BFh
    dd g_Va010738FC
    db 0B9h, 004h, 000h, 000h, 000h, 033h, 0D2h, 0F3h, 0A6h, 075h, 03Fh, 08Bh, 03Dh
    dd __imp__strtoul
    db 0BEh, 002h, 000h, 000h, 000h, 08Dh, 09Bh, 000h, 000h, 000h, 000h, 03Bh, 075h, 0ECh, 00Fh, 08Dh
    db 0BAh, 001h, 000h, 000h, 08Bh, 084h, 0B5h, 064h, 0FFh, 0FFh, 0FFh, 06Ah, 010h, 053h, 050h, 0FFh
    db 0D7h, 068h, 000h, 001h, 000h, 000h, 08Dh, 08Dh, 05Ch, 0FCh, 0FFh, 0FFh, 051h, 050h
    call ?GetSymbol@Signature@DebugStackwalk@@SAXIPADI@Z
    db 083h, 0C4h, 018h, 046h, 0EBh, 0D2h, 068h
    dd ?g_lock0134FB1C@@3UCriticalSection@@A
    db 0C7h, 045h, 0BCh
    dd ??_7Rva0005C110Surface@@6B@
    db 089h, 05Dh, 0C0h, 089h, 05Dh, 0C4h, 089h, 05Dh, 0C8h, 089h, 05Dh, 0CCh, 089h, 05Dh, 0D0h, 089h
    db 05Dh, 0D4h, 088h, 05Dh, 0D8h, 088h, 05Dh, 0D9h, 0C7h, 045h, 0DCh, 0FFh, 0FFh, 0FFh, 0FFh, 089h
    db 05Dh, 0E0h, 089h, 05Dh, 0E4h, 089h, 05Dh, 0E8h, 0FFh, 015h
    dd __imp__EnterCriticalSection@4
    db 0A1h
    dd ?g_count0134FB34@@3HA
    db 040h, 068h
    dd ?g_lock0134FB1C@@3UCriticalSection@@A
    db 0A3h
    dd ?g_count0134FB34@@3HA
    db 0FFh, 015h
    dd __imp__LeaveCriticalSection@4
    db 08Dh, 055h, 010h, 052h, 0C6h, 045h, 0FCh, 001h
    call ?j_000132af@@YAXXZ
    db 08Bh, 000h, 083h, 0C4h, 004h, 03Bh, 0C3h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 08Bh, 035h
    dd __imp__sprintf
    db 050h, 08Dh, 085h, 05Ch, 0FDh, 0FFh, 0FFh, 068h
    dd g_Va010738EC
    db 050h, 0FFh, 0D6h, 083h, 0C4h, 00Ch, 08Dh, 04Dh, 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 08Dh, 05Ch, 0FDh, 0FFh, 0FFh, 051h, 08Dh, 04Dh, 0BCh
    call ?j_000476db@@YAXXZ
    db 085h, 0C0h, 07Dh, 045h, 08Dh, 055h, 010h, 052h
    call ?j_000132af@@YAXXZ
    db 08Bh, 000h, 083h, 0C4h, 004h, 03Bh, 0C3h, 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 050h, 08Dh, 085h, 05Ch, 0FDh, 0FFh, 0FFh, 068h
    dd g_Va010738DC
    db 050h, 0FFh, 0D6h, 083h, 0C4h, 00Ch, 08Dh, 04Dh, 010h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 08Dh, 05Ch, 0FDh, 0FFh, 0FFh, 051h, 08Dh, 04Dh, 0BCh
    call ?j_000476db@@YAXXZ
    db 0A1h
    dd g_Va012A6504
    db 08Bh, 055h, 0C0h, 050h, 053h, 053h, 089h, 015h
    dd g_Va012ED24C
    db 0FFh, 015h
    dd g_Va01358CF8
    db 08Bh, 0F8h, 0FFh, 015h
    dd __imp__GetLastError@0
    db 03Dh, 0B7h, 000h, 000h, 000h, 00Fh, 085h, 098h, 000h, 000h, 000h, 08Bh, 00Dh
    dd g_Va012A6504
    db 053h, 051h, 0FFh, 015h
    dd g_Va01358FE4
    db 08Bh, 0F0h, 03Bh, 0F3h, 074h, 010h, 056h, 0FFh, 015h
    dd g_Va01359078
    db 06Ah, 009h, 056h, 0FFh, 015h
    dd __imp__ShowWindow@8
    db 03Bh, 0FBh, 074h, 007h, 057h, 0FFh, 015h
    dd __imp__CloseHandle@4
    db 08Bh, 035h
    dd ?TheVersion@@3PAVVersion@@A
    db 03Bh, 0F3h, 089h, 075h, 010h, 074h, 039h, 08Dh, 04Eh, 01Ch, 0C6h, 045h, 0FCh, 004h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Eh, 018h, 0C6h, 045h, 0FCh, 003h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Eh, 014h, 0C6h, 045h, 0FCh, 002h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Dh, 04Eh, 010h, 0C6h, 045h, 0FCh, 001h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 089h, 01Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 08Dh, 04Dh, 0BCh
    call ?j_00031160@@YAXXZ
    db 08Bh, 04Dh, 0F4h, 05Fh, 05Eh, 033h, 0C0h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 08Bh
    db 0E5h, 05Dh, 0C2h, 010h, 000h, 08Bh, 045h, 014h, 08Bh, 07Dh, 008h, 033h, 0D2h, 08Ah, 015h
    dd g_Va012ED23C
    db 052h, 050h
    call ?d_0005f2b0@@YAXXZ
    db 083h, 0C4h, 008h, 03Ah, 0C3h, 08Dh, 04Dh, 0BCh, 074h, 0C7h, 088h, 05Dh, 0FCh
    call ?j_00031160@@YAXXZ
    db 06Ah, 024h
    call ??2@YAPAXI@Z
    db 08Bh, 0C8h, 083h, 0C4h, 004h, 089h, 04Dh, 014h, 03Bh, 0CBh, 0C6h, 045h, 0FCh, 005h, 074h, 007h
    call ?j_0002ad6a@@YAXXZ
    db 0EBh, 002h, 033h, 0C0h, 051h, 089h, 065h, 014h, 08Bh, 0CCh, 068h
    dd g_Va010738CC
    db 088h, 05Dh, 0FCh, 0A3h
    dd ?TheVersion@@3PAVVersion@@A
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 051h, 089h, 065h, 008h, 08Bh, 0CCh, 068h
    dd g_Va010738C0
    db 0C6h, 045h, 0FCh, 006h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 051h, 089h, 065h, 0B4h, 08Bh, 0CCh, 068h
    dd g_Va010738AC
    db 0C6h, 045h, 0FCh, 007h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 051h, 089h, 065h, 0B8h, 08Bh, 0CCh, 068h
    dd g_Va010738A0
    db 0C6h, 045h, 0FCh, 008h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Bh, 00Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 06Ah, 00Dh, 053h, 06Ah, 003h, 06Ah, 001h, 088h, 05Dh, 0FCh
    call ?j_00009ef8@@YAXXZ
    call ?j_00033b54@@YAXXZ
    db 03Ah, 0C3h, 074h, 009h
    call ?j_00002f72@@YAXXZ
    db 03Ah, 0C3h, 075h, 025h, 08Bh, 00Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 03Bh, 0CBh, 08Bh, 0F1h, 074h, 00Eh
    call ?j_00007cb1@@YAXXZ
    db 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 089h, 01Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 0E9h, 004h, 0FFh, 0FFh, 0FFh, 08Bh, 055h, 0ECh, 08Dh, 08Dh, 064h, 0FFh, 0FFh, 0FFh, 051h, 052h
    call ?j_0000a425@@YAXXZ
    db 083h, 0C4h, 008h
    call ?j_000246ea@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 03Bh, 0CBh, 08Bh, 0F1h, 074h, 00Eh
    call ?j_00007cb1@@YAXXZ
    db 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 089h, 01Dh
    dd ?TheVersion@@3PAVVersion@@A
    db 038h, 098h, 004h, 00Dh, 000h, 000h, 074h, 01Eh, 08Bh, 00Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 03Bh, 0CBh, 00Fh, 084h, 0B1h, 0FEh, 0FFh, 0FFh
    call ?j_0002f608@@YAXXZ
    db 089h, 01Dh
    dd ?EngineGlobal007629F0@@3PAUEngine007629F0@@A
    db 0E9h, 0A1h, 0FEh, 0FFh, 0FFh
    call ?Shutdown@WW3D@@SA_NXZ
    db 0E9h, 097h, 0FEh, 0FFh, 0FFh
?d_000600f0@@YAXXZ ENDP
_TEXT$d004600f0 ENDS
_TEXT SEGMENT

; retail @ 0x00064020 size 31
public ?d_00064020@@YAXXZ
?d_00064020@@YAXXZ PROC
    db 51h, 85h, 0C0h, 89h, 04h, 24h, 0DBh, 04h, 24h, 7Dh, 06h, 0D8h, 05h, 58h, 53h, 07h
    db 01h, 0D8h, 0Dh, 54h, 53h, 07h, 01h, 83h, 0C4h, 04h, 0E9h, 0F9h, 2Dh, 99h, 00h
?d_00064020@@YAXXZ ENDP

; retail @ 0x00064F70 size 146
public ?d_00064f70@@YAXXZ
?d_00064f70@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 55h, 8Bh, 0E9h, 8Bh, 55h, 00h, 56h, 8Bh, 72h, 04h, 85h
    db 0F6h, 57h, 8Bh, 0FAh, 0B1h, 01h, 74h, 20h, 8Bh, 43h, 18h, 0EBh, 03h, 8Dh, 49h, 00h
    db 3Bh, 46h, 28h, 0Fh, 92h, 0C1h, 84h, 0C9h, 8Bh, 0FEh, 74h, 05h, 8Bh, 76h, 08h, 0EBh
    db 03h, 8Bh, 76h, 0Ch, 85h, 0F6h, 75h, 0E8h, 84h, 0C9h, 8Bh, 0C7h, 74h, 15h, 3Bh, 7Ah
    db 08h, 75h, 07h, 6Ah, 00h, 53h, 57h, 57h, 0EBh, 16h, 57h, 0E8h, 20h, 69h, 7Ch, 00h
    db 83h, 0C4h, 04h, 8Bh, 50h, 28h, 3Bh, 53h, 18h, 73h, 24h, 6Ah, 00h, 53h, 57h, 56h
    db 8Dh, 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0E8h, 4Fh, 59h, 0FEh, 0FFh, 8Bh, 08h, 8Bh, 44h
    db 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 08h, 0C6h, 40h, 04h, 01h, 5Bh, 0C2h, 08h, 00h, 8Bh
    db 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh, 89h, 01h, 0C6h, 41h, 04h, 00h, 8Bh, 0C1h, 5Bh, 0C2h
    db 08h, 00h
?d_00064f70@@YAXXZ ENDP

; retail @ 0x0006A1D0 size 308
public ?d_0006a1d0@@YAXXZ
?d_0006a1d0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 8Bh, 0D9h, 8Bh, 43h, 04h, 8Bh, 4Ch, 24h, 20h, 56h, 2Bh, 03h
    db 0C1h, 0F8h, 04h, 3Bh, 0C1h, 57h, 89h, 5Ch, 24h, 10h, 89h, 44h, 24h, 0Ch, 8Dh, 4Ch
    db 24h, 28h, 72h, 04h, 8Dh, 4Ch, 24h, 0Ch, 8Bh, 09h, 03h, 0C8h, 89h, 4Ch, 24h, 14h
    db 74h, 29h, 8Bh, 0C1h, 0C1h, 0E0h, 04h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Eh, 0E8h
    db 1Ch, 7Dh, 81h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 0EBh, 16h, 0E8h, 1Eh, 43h
    db 7Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 0EBh, 08h, 0C7h, 44h, 24h, 0Ch, 00h
    db 00h, 00h, 00h, 8Bh, 33h, 8Bh, 7Ch, 24h, 0Ch, 55h, 8Bh, 6Ch, 24h, 20h, 3Bh, 0F5h
    db 74h, 14h, 56h, 57h, 0E8h, 3Ch, 50h, 0FBh, 0FFh, 83h, 0C6h, 10h, 83h, 0C4h, 08h, 83h
    db 0C7h, 10h, 3Bh, 0F5h, 75h, 0ECh, 8Bh, 74h, 24h, 2Ch, 83h, 0FEh, 01h, 75h, 13h, 8Bh
    db 44h, 24h, 24h, 50h, 57h, 0E8h, 1Bh, 50h, 0FBh, 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 10h
    db 0EBh, 18h, 85h, 0F6h, 76h, 14h, 8Bh, 4Ch, 24h, 24h, 51h, 57h, 0E8h, 04h, 50h, 0FBh
    db 0FFh, 83h, 0C4h, 08h, 83h, 0C7h, 10h, 4Eh, 75h, 0ECh, 8Ah, 44h, 24h, 30h, 84h, 0C0h
    db 75h, 26h, 8Bh, 5Bh, 04h, 3Bh, 0EBh, 74h, 1Bh, 8Bh, 0F5h, 0EBh, 03h, 8Dh, 49h, 00h
    db 56h, 57h, 0E8h, 0DEh, 4Fh, 0FBh, 0FFh, 83h, 0C6h, 10h, 83h, 0C4h, 08h, 83h, 0C7h, 10h
    db 3Bh, 0F3h, 75h, 0ECh, 8Bh, 5Ch, 24h, 14h, 8Bh, 0Bh, 85h, 0C9h, 5Dh, 74h, 27h, 8Bh
    db 43h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 04h, 0C1h, 0E0h, 04h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 0Bh, 51h, 0E8h, 0D9h, 7Bh, 81h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0Dh
    db 43h, 7Ch, 00h, 83h, 0C4h, 08h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 0Ch, 89h, 7Bh
    db 04h, 0C1h, 0E0h, 04h, 5Fh, 03h, 0C1h, 5Eh, 89h, 0Bh, 89h, 43h, 08h, 5Bh, 83h, 0C4h
    db 0Ch, 0C2h, 14h, 00h
?d_0006a1d0@@YAXXZ ENDP

; retail @ 0x00084510 size 4621
public ?d_00084510@@YAXXZ
?d_00084510@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F2h, 51h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 0B8h, 38h
    db 01h, 01h, 00h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 0E8h, 31h, 27h, 97h, 00h, 53h
    db 55h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 20h, 0E8h, 0F2h, 0D4h, 91h, 00h, 33h, 0DBh
    db 8Dh, 7Eh, 08h, 0C7h, 06h, 8Ch, 0C6h, 07h, 01h, 89h, 9Ch, 24h, 50h, 01h, 01h, 00h
    db 89h, 1Fh, 89h, 5Eh, 0Ch, 89h, 5Eh, 10h, 89h, 5Eh, 14h, 89h, 9Eh, 94h, 00h, 00h
    db 00h, 68h, 28h, 0D8h, 40h, 00h, 68h, 0D9h, 7Bh, 41h, 00h, 6Ah, 04h, 6Ah, 04h, 8Dh
    db 86h, 9Ch, 00h, 00h, 00h, 50h, 0C6h, 84h, 24h, 64h, 01h, 01h, 00h, 05h, 0E8h, 61h
    db 29h, 97h, 00h, 89h, 9Eh, 00h, 02h, 00h, 00h, 89h, 9Eh, 0Ch, 02h, 00h, 00h, 68h
    db 0FAh, 28h, 41h, 00h, 68h, 7Bh, 6Eh, 43h, 00h, 6Ah, 12h, 6Ah, 24h, 8Dh, 8Eh, 24h
    db 02h, 00h, 00h, 51h, 0C6h, 84h, 24h, 64h, 01h, 01h, 00h, 08h, 0E8h, 33h, 29h, 97h
    db 00h, 68h, 0FAh, 28h, 41h, 00h, 68h, 7Bh, 6Eh, 43h, 00h, 6Ah, 12h, 6Ah, 24h, 8Dh
    db 96h, 0ACh, 04h, 00h, 00h, 52h, 0C6h, 84h, 24h, 64h, 01h, 01h, 00h, 09h, 0E8h, 11h
    db 29h, 97h, 00h, 68h, 0FAh, 28h, 41h, 00h, 68h, 7Bh, 6Eh, 43h, 00h, 6Ah, 12h, 6Ah
    db 24h, 8Dh, 86h, 34h, 07h, 00h, 00h, 50h, 0C6h, 84h, 24h, 64h, 01h, 01h, 00h, 0Ah
    db 0E8h, 0EFh, 28h, 97h, 00h, 68h, 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h, 00h, 6Ah
    db 03h, 6Ah, 0Ch, 8Dh, 8Eh, 04h, 0Ah, 00h, 00h, 51h, 0C6h, 84h, 24h, 64h, 01h, 01h
    db 00h, 0Bh, 0E8h, 0CDh, 28h, 97h, 00h, 89h, 9Eh, 0A4h, 0Ah, 00h, 00h, 89h, 9Eh, 0A8h
    db 0Ah, 00h, 00h, 89h, 9Eh, 0B8h, 0Ah, 00h, 00h, 89h, 9Eh, 0BCh, 0Ah, 00h, 00h, 89h
    db 9Eh, 0C4h, 0Ah, 00h, 00h, 89h, 9Eh, 0C8h, 0Ah, 00h, 00h, 89h, 9Eh, 0D0h, 0Ah, 00h
    db 00h, 89h, 9Eh, 0D4h, 0Ah, 00h, 00h, 89h, 9Eh, 0DCh, 0Ah, 00h, 00h, 89h, 9Eh, 0E0h
    db 0Ah, 00h, 00h, 89h, 9Eh, 0E8h, 0Ah, 00h, 00h, 89h, 9Eh, 0ECh, 0Ah, 00h, 00h, 89h
    db 9Eh, 0F4h, 0Ah, 00h, 00h, 89h, 9Eh, 0F8h, 0Ah, 00h, 00h, 89h, 9Eh, 00h, 0Bh, 00h
    db 00h, 89h, 9Eh, 04h, 0Bh, 00h, 00h, 89h, 9Eh, 80h, 0Bh, 00h, 00h, 89h, 9Eh, 84h
    db 0Bh, 00h, 00h, 89h, 9Eh, 0B0h, 0Bh, 00h, 00h, 0C7h, 86h, 0D0h, 0Bh, 00h, 00h, 0AEh
    db 6Fh, 4Bh, 25h, 89h, 9Eh, 40h, 0Ch, 00h, 00h, 89h, 9Eh, 44h, 0Ch, 00h, 00h, 89h
    db 9Eh, 48h, 0Ch, 00h, 00h, 89h, 9Eh, 4Ch, 0Ch, 00h, 00h, 8Dh, 0AEh, 8Ch, 0Dh, 00h
    db 00h, 89h, 5Dh, 00h, 89h, 9Eh, 90h, 0Dh, 00h, 00h, 89h, 9Eh, 0B8h, 0Dh, 00h, 00h
    db 89h, 9Eh, 0C0h, 0Dh, 00h, 00h, 89h, 9Eh, 0C4h, 0Dh, 00h, 00h, 89h, 9Eh, 0D0h, 0Dh
    db 00h, 00h, 89h, 9Eh, 0D8h, 0Dh, 00h, 00h, 89h, 9Eh, 0DCh, 0Dh, 00h, 00h, 89h, 9Eh
    db 0E0h, 0Dh, 00h, 00h, 89h, 9Eh, 0ECh, 0Dh, 00h, 00h, 89h, 9Eh, 0F0h, 0Dh, 00h, 00h
    db 89h, 9Eh, 0F4h, 0Dh, 00h, 00h, 89h, 9Eh, 0F8h, 0Dh, 00h, 00h, 89h, 9Eh, 0FCh, 0Dh
    db 00h, 00h, 89h, 9Eh, 00h, 0Eh, 00h, 00h, 89h, 9Eh, 04h, 0Eh, 00h, 00h, 89h, 9Eh
    db 08h, 0Eh, 00h, 00h, 89h, 9Eh, 0Ch, 0Eh, 00h, 00h, 89h, 9Eh, 10h, 0Eh, 00h, 00h
    db 89h, 9Eh, 14h, 0Eh, 00h, 00h, 89h, 9Eh, 18h, 0Eh, 00h, 00h, 89h, 9Eh, 1Ch, 0Eh
    db 00h, 00h, 89h, 9Eh, 20h, 0Eh, 00h, 00h, 89h, 9Eh, 24h, 0Eh, 00h, 00h, 8Dh, 8Eh
    db 0DCh, 0Eh, 00h, 00h, 0C6h, 84h, 24h, 50h, 01h, 01h, 00h, 27h, 89h, 9Eh, 28h, 0Eh
    db 00h, 00h, 89h, 9Eh, 2Ch, 0Eh, 00h, 00h, 89h, 9Eh, 30h, 0Eh, 00h, 00h, 0E8h, 17h
    db 2Dh, 0FBh, 0FFh, 8Dh, 8Eh, 0E0h, 0Eh, 00h, 00h, 0E8h, 0D7h, 0C7h, 0F9h, 0FFh, 89h, 9Eh
    db 0E0h, 11h, 00h, 00h, 89h, 9Eh, 0E4h, 11h, 00h, 00h, 89h, 9Eh, 0E8h, 11h, 00h, 00h
    db 89h, 9Eh, 00h, 12h, 00h, 00h, 89h, 9Eh, 04h, 12h, 00h, 00h, 89h, 9Eh, 08h, 12h
    db 00h, 00h, 89h, 9Eh, 0Ch, 12h, 00h, 00h, 89h, 9Eh, 10h, 12h, 00h, 00h, 8Dh, 8Eh
    db 1Ch, 12h, 00h, 00h, 0C6h, 84h, 24h, 50h, 01h, 01h, 00h, 2Ch, 0E8h, 0C9h, 2Ch, 0FBh
    db 0FFh, 89h, 9Eh, 7Ch, 12h, 00h, 00h, 89h, 9Eh, 80h, 12h, 00h, 00h, 89h, 9Eh, 84h
    db 12h, 00h, 00h, 89h, 9Eh, 88h, 12h, 00h, 00h, 39h, 1Dh, 0CCh, 0D5h, 2Eh, 01h, 0C6h
    db 84h, 24h, 50h, 01h, 01h, 00h, 31h, 75h, 06h, 89h, 35h, 0CCh, 0D5h, 2Eh, 01h, 0B8h
    db 05h, 00h, 00h, 00h, 6Ah, 02h, 68h, 0E8h, 0C6h, 07h, 01h, 8Bh, 0CDh, 89h, 9Eh, 8Ch
    db 12h, 00h, 00h, 88h, 9Eh, 0F0h, 0Ch, 00h, 00h, 88h, 9Eh, 0F1h, 0Ch, 00h, 00h, 0C6h
    db 86h, 0F2h, 0Ch, 00h, 00h, 01h, 0C6h, 86h, 0F4h, 0Ch, 00h, 00h, 01h, 88h, 9Eh, 0F5h
    db 0Ch, 00h, 00h, 88h, 9Eh, 0B6h, 0Dh, 00h, 00h, 88h, 9Eh, 0F6h, 0Ch, 00h, 00h, 88h
    db 9Eh, 0F7h, 0Ch, 00h, 00h, 88h, 9Eh, 0F8h, 0Ch, 00h, 00h, 88h, 9Eh, 84h, 0Dh, 00h
    db 00h, 88h, 9Eh, 85h, 0Dh, 00h, 00h, 88h, 9Eh, 86h, 0Dh, 00h, 00h, 88h, 9Eh, 88h
    db 0Dh, 00h, 00h, 88h, 9Eh, 87h, 0Dh, 00h, 00h, 89h, 9Eh, 08h, 0Dh, 00h, 00h, 88h
    db 9Eh, 0Ch, 0Dh, 00h, 00h, 0C6h, 86h, 0F3h, 0Ch, 00h, 00h, 01h, 88h, 9Eh, 0Dh, 0Dh
    db 00h, 00h, 0C7h, 86h, 10h, 0Dh, 00h, 00h, 20h, 00h, 00h, 00h, 89h, 86h, 18h, 0Dh
    db 00h, 00h, 88h, 9Eh, 58h, 0Dh, 00h, 00h, 0C7h, 86h, 5Ch, 0Dh, 00h, 00h, 00h, 00h
    db 20h, 41h, 89h, 86h, 60h, 0Dh, 00h, 00h, 88h, 9Eh, 1Ch, 0Dh, 00h, 00h, 0C7h, 86h
    db 20h, 0Dh, 00h, 00h, 88h, 13h, 00h, 00h, 89h, 86h, 24h, 0Dh, 00h, 00h, 88h, 9Eh
    db 28h, 0Dh, 00h, 00h, 0C7h, 86h, 2Ch, 0Dh, 00h, 00h, 10h, 27h, 00h, 00h, 89h, 86h
    db 30h, 0Dh, 00h, 00h, 88h, 9Eh, 05h, 0Dh, 00h, 00h, 88h, 9Eh, 04h, 0Dh, 00h, 00h
    db 0C7h, 86h, 00h, 0Dh, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 88h, 9Eh, 0F9h, 0Ch, 00h, 00h
    db 88h, 9Eh, 0FAh, 0Ch, 00h, 00h, 88h, 9Eh, 0FBh, 0Ch, 00h, 00h, 88h, 9Eh, 0FCh, 0Ch
    db 00h, 00h, 89h, 9Eh, 94h, 0Dh, 00h, 00h, 89h, 9Eh, 98h, 0Dh, 00h, 00h, 89h, 9Eh
    db 9Ch, 0Dh, 00h, 00h, 89h, 9Eh, 0A0h, 0Dh, 00h, 00h, 89h, 9Eh, 0A4h, 0Dh, 00h, 00h
    db 89h, 9Eh, 0A8h, 0Dh, 00h, 00h, 0C6h, 86h, 0ACh, 0Dh, 00h, 00h, 01h, 88h, 9Eh, 89h
    db 0Dh, 00h, 00h, 88h, 9Eh, 8Ah, 0Dh, 00h, 00h, 88h, 9Eh, 8Bh, 0Dh, 00h, 00h, 0E8h
    db 0FCh, 33h, 80h, 00h, 6Ah, 08h, 68h, 0DCh, 0C6h, 07h, 01h, 8Dh, 8Eh, 90h, 0Dh, 00h
    db 00h, 0E8h, 0EAh, 33h, 80h, 00h, 0BDh, 00h, 00h, 80h, 3Fh, 8Dh, 8Eh, 94h, 00h, 00h
    db 00h, 0C7h, 86h, 0B0h, 0Dh, 00h, 00h, 5Ah, 00h, 00h, 00h, 0C6h, 86h, 0B4h, 0Dh, 00h
    db 00h, 01h, 0C6h, 86h, 0BCh, 0Dh, 00h, 00h, 01h, 88h, 9Eh, 0BDh, 0Dh, 00h, 00h, 89h
    db 0AEh, 0C8h, 0Dh, 00h, 00h, 88h, 9Eh, 0CCh, 0Dh, 00h, 00h, 88h, 9Eh, 0CDh, 0Dh, 00h
    db 00h, 88h, 9Eh, 0B5h, 0Dh, 00h, 00h, 0E8h, 0C4h, 2Fh, 80h, 00h, 8Bh, 0CFh, 88h, 9Eh
    db 8Fh, 00h, 00h, 00h, 0C6h, 86h, 8Eh, 00h, 00h, 00h, 01h, 88h, 9Eh, 90h, 00h, 00h
    db 00h, 0C7h, 86h, 0B4h, 0Eh, 00h, 00h, 00h, 00h, 20h, 41h, 0C7h, 86h, 0B0h, 0Eh, 00h
    db 00h, 02h, 00h, 00h, 00h, 0C7h, 86h, 0B8h, 0Eh, 00h, 00h, 0C8h, 00h, 00h, 00h, 0C7h
    db 86h, 0BCh, 0Eh, 00h, 00h, 58h, 02h, 00h, 00h, 0C7h, 86h, 0C0h, 0Eh, 00h, 00h, 0Ah
    db 00h, 00h, 00h, 0C7h, 86h, 0C4h, 0Eh, 00h, 00h, 00h, 00h, 80h, 40h, 88h, 9Eh, 7Ch
    db 0Ah, 00h, 00h, 0C7h, 86h, 0CCh, 0Ch, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 88h, 9Eh, 0C5h
    db 0Bh, 00h, 00h, 0E8h, 58h, 2Fh, 80h, 00h, 8Dh, 4Eh, 0Ch, 0E8h, 50h, 2Fh, 80h, 00h
    db 8Dh, 4Eh, 10h, 0E8h, 48h, 2Fh, 80h, 00h, 8Dh, 4Eh, 14h, 0E8h, 40h, 2Fh, 80h, 00h
    db 0C6h, 46h, 18h, 01h, 88h, 5Eh, 19h, 0C6h, 46h, 1Ah, 01h, 0C6h, 46h, 1Bh, 01h, 88h
    db 5Eh, 1Ch, 0C6h, 46h, 1Dh, 01h, 88h, 5Eh, 1Eh, 0C6h, 46h, 1Fh, 01h, 88h, 5Eh, 20h
    db 89h, 5Eh, 24h, 88h, 5Eh, 28h, 88h, 5Eh, 29h, 0C7h, 46h, 2Ch, 00h, 04h, 00h, 00h
    db 0C7h, 46h, 30h, 00h, 03h, 00h, 00h, 0C6h, 46h, 3Ah, 01h, 0C6h, 46h, 3Bh, 01h, 89h
    db 5Eh, 34h, 88h, 5Eh, 38h, 0C6h, 46h, 39h, 01h, 88h, 5Eh, 3Ch, 88h, 5Eh, 44h, 88h
    db 5Eh, 45h, 88h, 5Eh, 46h, 89h, 5Eh, 48h, 88h, 5Eh, 4Ch, 88h, 5Eh, 4Dh, 88h, 5Eh
    db 4Eh, 0B8h, 01h, 00h, 00h, 00h, 89h, 46h, 40h, 88h, 5Eh, 4Fh, 88h, 46h, 60h, 0C7h
    db 46h, 54h, 08h, 00h, 00h, 00h, 89h, 5Eh, 5Ch, 88h, 46h, 58h, 88h, 46h, 59h, 88h
    db 5Eh, 61h, 88h, 5Eh, 62h, 88h, 5Eh, 63h, 0C7h, 86h, 7Ch, 01h, 00h, 00h, 0C3h, 0F5h
    db 48h, 0BFh, 88h, 5Eh, 64h, 88h, 5Eh, 65h, 83h, 0C9h, 0FFh, 89h, 4Eh, 68h, 89h, 5Eh
    db 6Ch, 88h, 46h, 70h, 88h, 9Eh, 90h, 0Ah, 00h, 00h, 88h, 9Eh, 91h, 0Ah, 00h, 00h
    db 88h, 9Eh, 92h, 0Ah, 00h, 00h, 88h, 9Eh, 93h, 0Ah, 00h, 00h, 88h, 86h, 94h, 0Ah
    db 00h, 00h, 88h, 86h, 95h, 0Ah, 00h, 00h, 88h, 9Eh, 96h, 0Ah, 00h, 00h, 88h, 9Eh
    db 97h, 0Ah, 00h, 00h, 89h, 86h, 98h, 0Ah, 00h, 00h, 88h, 9Eh, 9Ch, 0Ah, 00h, 00h
    db 88h, 9Eh, 9Dh, 0Ah, 00h, 00h, 88h, 9Eh, 9Eh, 0Ah, 00h, 00h, 88h, 9Eh, 9Fh, 0Ah
    db 00h, 00h, 88h, 9Eh, 0A0h, 0Ah, 00h, 00h, 89h, 8Eh, 0B0h, 0Ah, 00h, 00h, 89h, 0AEh
    db 64h, 0Bh, 00h, 00h, 89h, 0AEh, 68h, 0Bh, 00h, 00h, 89h, 0AEh, 6Ch, 0Bh, 00h, 00h
    db 0C7h, 86h, 70h, 0Bh, 00h, 00h, 2Ch, 01h, 00h, 00h, 89h, 5Eh, 74h, 89h, 5Eh, 78h
    db 89h, 5Eh, 7Ch, 89h, 9Eh, 80h, 00h, 00h, 00h, 89h, 9Eh, 84h, 00h, 00h, 00h, 89h
    db 9Eh, 88h, 00h, 00h, 00h, 89h, 9Eh, 98h, 00h, 00h, 00h, 88h, 86h, 8Ch, 00h, 00h
    db 00h, 88h, 9Eh, 8Dh, 00h, 00h, 00h, 0C7h, 86h, 0D0h, 0Ch, 00h, 00h, 32h, 00h, 00h
    db 00h, 0C7h, 86h, 0D4h, 0Ch, 00h, 00h, 00h, 00h, 0F0h, 41h, 0C7h, 86h, 0D8h, 0Ch, 00h
    db 00h, 0Ah, 00h, 00h, 00h, 0C7h, 86h, 0DCh, 0Ch, 00h, 00h, 64h, 00h, 00h, 00h, 0C7h
    db 86h, 0E0h, 0Ch, 00h, 00h, 00h, 00h, 0A0h, 40h, 0C7h, 86h, 0E4h, 0Ch, 00h, 00h, 0CDh
    db 0CCh, 0CCh, 3Dh, 0C7h, 86h, 0E8h, 0Ch, 00h, 00h, 00h, 00h, 80h, 3Eh, 0C7h, 86h, 0ECh
    db 0Ch, 00h, 00h, 00h, 00h, 00h, 3Fh, 88h, 9Eh, 50h, 0Ch, 00h, 00h, 8Dh, 0BEh, 0BCh
    db 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 04h, 00h, 00h, 00h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Dh, 4Fh, 0E0h, 89h, 5Fh, 0F0h, 89h, 1Fh, 89h, 5Fh, 10h, 89h, 5Fh, 20h, 89h, 5Fh
    db 30h, 89h, 5Fh, 40h, 89h, 5Fh, 50h, 89h, 5Fh, 60h, 89h, 5Fh, 70h, 89h, 9Fh, 80h
    db 00h, 00h, 00h, 89h, 9Fh, 90h, 00h, 00h, 00h, 89h, 9Fh, 0A0h, 00h, 00h, 00h, 89h
    db 9Fh, 0B0h, 00h, 00h, 00h, 0E8h, 56h, 2Dh, 80h, 00h, 8Bh, 44h, 24h, 10h, 83h, 0C7h
    db 04h, 48h, 89h, 44h, 24h, 10h, 75h, 0B8h, 89h, 9Eh, 80h, 01h, 00h, 00h, 89h, 9Eh
    db 0F0h, 01h, 00h, 00h, 89h, 9Eh, 04h, 02h, 00h, 00h, 89h, 9Eh, 08h, 02h, 00h, 00h
    db 89h, 9Eh, 10h, 02h, 00h, 00h, 89h, 9Eh, 14h, 02h, 00h, 00h, 0C7h, 86h, 0F4h, 01h
    db 00h, 00h, 64h, 00h, 00h, 00h, 0C7h, 86h, 0F8h, 01h, 00h, 00h, 19h, 00h, 00h, 00h
    db 0C7h, 86h, 0FCh, 01h, 00h, 00h, 0E0h, 93h, 04h, 00h, 0C7h, 86h, 18h, 02h, 00h, 00h
    db 02h, 00h, 00h, 00h, 89h, 9Eh, 1Ch, 02h, 00h, 00h, 88h, 9Eh, 20h, 02h, 00h, 00h
    db 88h, 9Eh, 21h, 02h, 00h, 00h, 0C6h, 86h, 22h, 02h, 00h, 00h, 01h, 0C6h, 86h, 23h
    db 02h, 00h, 00h, 01h, 89h, 9Eh, 0BCh, 01h, 00h, 00h, 89h, 0AEh, 0E8h, 01h, 00h, 00h
    db 89h, 0AEh, 0ECh, 01h, 00h, 00h, 89h, 9Eh, 0C0h, 01h, 00h, 00h, 89h, 9Eh, 0C4h, 01h
    db 00h, 00h, 89h, 9Eh, 0C8h, 01h, 00h, 00h, 89h, 9Eh, 0CCh, 01h, 00h, 00h, 89h, 9Eh
    db 0D0h, 01h, 00h, 00h, 89h, 9Eh, 0D4h, 01h, 00h, 00h, 89h, 9Eh, 0DCh, 01h, 00h, 00h
    db 89h, 9Eh, 0D8h, 01h, 00h, 00h, 89h, 9Eh, 0E4h, 01h, 00h, 00h, 89h, 9Eh, 0E0h, 01h
    db 00h, 00h, 8Dh, 0BEh, 28h, 02h, 00h, 00h, 8Dh, 8Eh, 0C0h, 09h, 00h, 00h, 0C7h, 44h
    db 24h, 10h, 03h, 00h, 00h, 00h, 89h, 59h, 0FCh, 89h, 19h, 89h, 59h, 04h, 89h, 59h
    db 20h, 89h, 59h, 24h, 89h, 59h, 28h, 89h, 59h, 44h, 89h, 59h, 48h, 0C7h, 41h, 4Ch
    db 00h, 00h, 80h, 0BFh, 8Bh, 0C7h, 0BAh, 06h, 00h, 00h, 00h, 0EBh, 03h, 8Dh, 49h, 00h
    db 89h, 58h, 0FCh, 89h, 18h, 89h, 58h, 04h, 89h, 58h, 08h, 89h, 58h, 0Ch, 89h, 58h
    db 10h, 89h, 58h, 14h, 89h, 58h, 18h, 0C7h, 40h, 1Ch, 00h, 00h, 80h, 0BFh, 89h, 98h
    db 84h, 02h, 00h, 00h, 89h, 98h, 88h, 02h, 00h, 00h, 89h, 98h, 8Ch, 02h, 00h, 00h
    db 89h, 98h, 90h, 02h, 00h, 00h, 89h, 98h, 94h, 02h, 00h, 00h, 89h, 98h, 98h, 02h
    db 00h, 00h, 89h, 98h, 9Ch, 02h, 00h, 00h, 89h, 98h, 0A0h, 02h, 00h, 00h, 0C7h, 80h
    db 0A4h, 02h, 00h, 00h, 00h, 00h, 80h, 0BFh, 83h, 0C0h, 6Ch, 4Ah, 75h, 0A2h, 8Bh, 44h
    db 24h, 10h, 83h, 0C1h, 0Ch, 83h, 0C7h, 24h, 48h, 89h, 44h, 24h, 10h, 0Fh, 85h, 63h
    db 0FFh, 0FFh, 0FFh, 89h, 0AEh, 28h, 0Ah, 00h, 00h, 0C7h, 86h, 58h, 0Ah, 00h, 00h, 03h
    db 00h, 00h, 00h, 89h, 9Eh, 5Ch, 0Ah, 00h, 00h, 89h, 9Eh, 60h, 0Ah, 00h, 00h, 89h
    db 9Eh, 64h, 0Ah, 00h, 00h, 89h, 9Eh, 68h, 0Ah, 00h, 00h, 0C7h, 86h, 24h, 0Bh, 00h
    db 00h, 64h, 00h, 00h, 00h, 0C7h, 86h, 28h, 0Bh, 00h, 00h, 01h, 00h, 00h, 00h, 0C6h
    db 86h, 6Ch, 0Ah, 00h, 00h, 01h, 0C6h, 86h, 6Dh, 0Ah, 00h, 00h, 01h, 0C6h, 86h, 6Eh
    db 0Ah, 00h, 00h, 01h, 0C6h, 86h, 6Fh, 0Ah, 00h, 00h, 01h, 0C6h, 86h, 70h, 0Ah, 00h
    db 00h, 01h, 0C6h, 86h, 71h, 0Ah, 00h, 00h, 01h, 88h, 9Eh, 72h, 0Ah, 00h, 00h, 0C6h
    db 86h, 73h, 0Ah, 00h, 00h, 01h, 88h, 9Eh, 74h, 0Ah, 00h, 00h, 0C6h, 86h, 75h, 0Ah
    db 00h, 00h, 01h, 88h, 9Eh, 76h, 0Ah, 00h, 00h, 88h, 9Eh, 77h, 0Ah, 00h, 00h, 0C7h
    db 86h, 78h, 0Ah, 00h, 00h, 9Ah, 99h, 99h, 3Eh, 0B8h, 00h, 02h, 00h, 00h, 89h, 86h
    db 44h, 0Ah, 00h, 00h, 89h, 86h, 48h, 0Ah, 00h, 00h, 89h, 86h, 4Ch, 0Ah, 00h, 00h
    db 89h, 86h, 50h, 0Ah, 00h, 00h, 0BFh, 00h, 00h, 00h, 3Fh, 89h, 0BEh, 54h, 0Ah, 00h
    db 00h, 0C6h, 86h, 7Fh, 0Ah, 00h, 00h, 01h, 89h, 9Eh, 84h, 0Ah, 00h, 00h, 89h, 0AEh
    db 0B4h, 0Ah, 00h, 00h, 89h, 9Eh, 0C0h, 0Ah, 00h, 00h, 89h, 9Eh, 0CCh, 0Ah, 00h, 00h
    db 89h, 9Eh, 0D8h, 0Ah, 00h, 00h, 89h, 9Eh, 0E4h, 0Ah, 00h, 00h, 89h, 9Eh, 0F0h, 0Ah
    db 00h, 00h, 89h, 9Eh, 0FCh, 0Ah, 00h, 00h, 8Dh, 8Eh, 0B8h, 0Ah, 00h, 00h, 89h, 9Eh
    db 08h, 0Bh, 00h, 00h, 0E8h, 0D7h, 2Ah, 80h, 00h, 8Dh, 8Eh, 0C4h, 0Ah, 00h, 00h, 0E8h
    db 0CCh, 2Ah, 80h, 00h, 8Dh, 8Eh, 0D0h, 0Ah, 00h, 00h, 0E8h, 0C1h, 2Ah, 80h, 00h, 8Dh
    db 8Eh, 0DCh, 0Ah, 00h, 00h, 0E8h, 0B6h, 2Ah, 80h, 00h, 8Dh, 8Eh, 0E8h, 0Ah, 00h, 00h
    db 0E8h, 0ABh, 2Ah, 80h, 00h, 8Dh, 8Eh, 0F4h, 0Ah, 00h, 00h, 0E8h, 0A0h, 2Ah, 80h, 00h
    db 8Dh, 8Eh, 00h, 0Bh, 00h, 00h, 0E8h, 95h, 2Ah, 80h, 00h, 8Dh, 8Eh, 0BCh, 0Ah, 00h
    db 00h, 0E8h, 8Ah, 2Ah, 80h, 00h, 8Dh, 8Eh, 0C8h, 0Ah, 00h, 00h, 0E8h, 7Fh, 2Ah, 80h
    db 00h, 8Dh, 8Eh, 0D4h, 0Ah, 00h, 00h, 0E8h, 74h, 2Ah, 80h, 00h, 8Dh, 8Eh, 0E0h, 0Ah
    db 00h, 00h, 0E8h, 69h, 2Ah, 80h, 00h, 8Dh, 8Eh, 0ECh, 0Ah, 00h, 00h, 0E8h, 5Eh, 2Ah
    db 80h, 00h, 8Dh, 8Eh, 0F8h, 0Ah, 00h, 00h, 0E8h, 53h, 2Ah, 80h, 00h, 8Dh, 8Eh, 04h
    db 0Bh, 00h, 00h, 0E8h, 48h, 2Ah, 80h, 00h, 8Dh, 8Eh, 00h, 02h, 00h, 00h, 0E8h, 3Dh
    db 2Ah, 80h, 00h, 8Dh, 8Eh, 0Ch, 02h, 00h, 00h, 0E8h, 32h, 2Ah, 80h, 00h, 8Dh, 8Eh
    db 40h, 0Ch, 00h, 00h, 0E8h, 27h, 2Ah, 80h, 00h, 88h, 5Eh, 50h, 89h, 9Eh, 8Ch, 0Bh
    db 00h, 00h, 0C7h, 86h, 90h, 0Bh, 00h, 00h, 1Eh, 00h, 00h, 00h, 89h, 9Eh, 88h, 0Ah
    db 00h, 00h, 88h, 9Eh, 8Ch, 0Ah, 00h, 00h, 0C6h, 86h, 80h, 0Ah, 00h, 00h, 01h, 88h
    db 9Eh, 81h, 0Ah, 00h, 00h, 0C6h, 86h, 8Dh, 0Ah, 00h, 00h, 01h, 0C6h, 86h, 8Eh, 0Ah
    db 00h, 00h, 01h, 0C6h, 86h, 8Fh, 0Ah, 00h, 00h, 01h, 88h, 9Eh, 91h, 0Ah, 00h, 00h
    db 0C7h, 86h, 8Ch, 01h, 00h, 00h, 00h, 00h, 16h, 42h, 89h, 9Eh, 90h, 01h, 00h, 00h
    db 89h, 0AEh, 94h, 01h, 00h, 00h, 0C7h, 86h, 84h, 01h, 00h, 00h, 00h, 00h, 0C8h, 42h
    db 0C7h, 86h, 88h, 01h, 00h, 00h, 00h, 00h, 96h, 43h, 0C7h, 86h, 58h, 0Eh, 00h, 00h
    db 00h, 00h, 7Ah, 43h, 89h, 9Eh, 98h, 01h, 00h, 00h, 0C7h, 86h, 64h, 0Eh, 00h, 00h
    db 0CDh, 0CCh, 4Ch, 3Eh, 89h, 0BEh, 9Ch, 01h, 00h, 00h, 0C7h, 86h, 0A0h, 01h, 00h, 00h
    db 0CDh, 0CCh, 0CCh, 3Dh, 89h, 0BEh, 0A4h, 01h, 00h, 00h, 89h, 0BEh, 0A8h, 01h, 00h, 00h
    db 0C7h, 86h, 0ACh, 01h, 00h, 00h, 00h, 00h, 80h, 0BFh, 89h, 0BEh, 0B0h, 01h, 00h, 00h
    db 0C7h, 86h, 0B4h, 01h, 00h, 00h, 0Fh, 00h, 00h, 00h, 88h, 9Eh, 0B8h, 01h, 00h, 00h
    db 0C7h, 86h, 0Ch, 0Bh, 00h, 00h, 01h, 00h, 00h, 00h, 89h, 9Eh, 10h, 0Bh, 00h, 00h
    db 89h, 9Eh, 2Ch, 0Bh, 00h, 00h, 89h, 9Eh, 30h, 0Bh, 00h, 00h, 89h, 9Eh, 34h, 0Bh
    db 00h, 00h, 89h, 9Eh, 38h, 0Bh, 00h, 00h, 89h, 9Eh, 3Ch, 0Bh, 00h, 00h, 89h, 9Eh
    db 40h, 0Bh, 00h, 00h, 89h, 9Eh, 44h, 0Bh, 00h, 00h, 89h, 9Eh, 48h, 0Bh, 00h, 00h
    db 89h, 9Eh, 4Ch, 0Bh, 00h, 00h, 89h, 9Eh, 54h, 0Bh, 00h, 00h, 89h, 9Eh, 58h, 0Bh
    db 00h, 00h, 89h, 9Eh, 60h, 0Bh, 00h, 00h, 89h, 9Eh, 5Ch, 0Bh, 00h, 00h, 0C7h, 86h
    db 0DCh, 0Bh, 00h, 00h, 00h, 00h, 80h, 40h, 0B8h, 05h, 00h, 00h, 00h, 89h, 86h, 0E0h
    db 0Bh, 00h, 00h, 89h, 0BEh, 0E4h, 0Bh, 00h, 00h, 0C7h, 86h, 0E8h, 0Bh, 00h, 00h, 0Ah
    db 0D7h, 0A3h, 3Ch, 0C7h, 86h, 0ECh, 0Bh, 00h, 00h, 08h, 00h, 00h, 00h, 89h, 0BEh, 0F0h
    db 0Bh, 00h, 00h, 88h, 9Eh, 0F4h, 0Bh, 00h, 00h, 0C7h, 86h, 0F8h, 0Bh, 00h, 00h, 00h
    db 00h, 0FAh, 43h, 89h, 0AEh, 0FCh, 0Bh, 00h, 00h, 89h, 0BEh, 10h, 0Ch, 00h, 00h, 89h
    db 0AEh, 14h, 0Ch, 00h, 00h, 0C7h, 86h, 18h, 0Ch, 00h, 00h, 00h, 00h, 20h, 40h, 0C7h
    db 86h, 1Ch, 0Ch, 00h, 00h, 00h, 00h, 0A0h, 40h, 0C7h, 86h, 20h, 0Ch, 00h, 00h, 00h
    db 00h, 00h, 41h, 0C7h, 86h, 24h, 0Ch, 00h, 00h, 00h, 00h, 40h, 41h, 0C7h, 86h, 28h
    db 0Ch, 00h, 00h, 00h, 00h, 20h, 41h, 0C7h, 86h, 2Ch, 0Ch, 00h, 00h, 00h, 00h, 16h
    db 43h, 89h, 0AEh, 30h, 0Ch, 00h, 00h, 89h, 9Eh, 34h, 0Ch, 00h, 00h, 89h, 9Eh, 38h
    db 0Ch, 00h, 00h, 0C7h, 86h, 50h, 0Bh, 00h, 00h, 0Ah, 00h, 00h, 00h, 88h, 9Eh, 7Dh
    db 0Ah, 00h, 00h, 88h, 9Eh, 7Eh, 0Ah, 00h, 00h, 0C7h, 86h, 3Ch, 0Ch, 00h, 00h, 00h
    db 0FFh, 0FFh, 0FFh, 89h, 0AEh, 78h, 0Ch, 00h, 00h, 89h, 0AEh, 7Ch, 0Ch, 00h, 00h, 89h
    db 0AEh, 80h, 0Ch, 00h, 00h, 0C6h, 86h, 84h, 0Ch, 00h, 00h, 0FFh, 0C6h, 86h, 85h, 0Ch
    db 00h, 00h, 7Fh, 88h, 9Eh, 86h, 0Ch, 00h, 00h, 89h, 0AEh, 88h, 0Ch, 00h, 00h, 89h
    db 0AEh, 8Ch, 0Ch, 00h, 00h, 89h, 0AEh, 90h, 0Ch, 00h, 00h, 0C6h, 86h, 0A0h, 0Ch, 00h
    db 00h, 80h, 0C7h, 86h, 5Ch, 0Ch, 00h, 00h, 07h, 00h, 00h, 00h, 0C7h, 86h, 60h, 0Ch
    db 00h, 00h, 00h, 00h, 40h, 40h, 89h, 86h, 64h, 0Ch, 00h, 00h, 89h, 0AEh, 68h, 0Ch
    db 00h, 00h, 8Bh, 0BEh, 48h, 0Ch, 00h, 00h, 8Bh, 8Eh, 44h, 0Ch, 00h, 00h, 8Bh, 0C7h
    db 2Bh, 0C7h, 0C1h, 0F8h, 02h, 3Bh, 0C3h, 89h, 4Ch, 24h, 10h, 7Eh, 23h, 89h, 44h, 24h
    db 14h, 57h, 0E8h, 09h, 2Bh, 80h, 00h, 8Bh, 4Ch, 24h, 10h, 8Bh, 44h, 24h, 14h, 83h
    db 0C1h, 04h, 83h, 0C7h, 04h, 48h, 89h, 4Ch, 24h, 10h, 89h, 44h, 24h, 14h, 75h, 0E1h
    db 8Bh, 86h, 48h, 0Ch, 00h, 00h, 3Bh, 0C8h, 89h, 44h, 24h, 14h, 8Bh, 0F9h, 74h, 16h
    db 8Bh, 0CFh, 0E8h, 89h, 27h, 80h, 00h, 8Bh, 44h, 24h, 14h, 83h, 0C7h, 04h, 3Bh, 0F8h
    db 75h, 0EEh, 8Bh, 4Ch, 24h, 10h, 89h, 8Eh, 48h, 0Ch, 00h, 00h, 89h, 9Eh, 00h, 0Ch
    db 00h, 00h, 0C6h, 86h, 04h, 0Ch, 00h, 00h, 01h, 88h, 9Eh, 05h, 0Ch, 00h, 00h, 88h
    db 9Eh, 09h, 0Ch, 00h, 00h, 88h, 9Eh, 06h, 0Ch, 00h, 00h, 88h, 9Eh, 07h, 0Ch, 00h
    db 00h, 88h, 9Eh, 08h, 0Ch, 00h, 00h, 89h, 9Eh, 14h, 0Bh, 00h, 00h, 88h, 9Eh, 18h
    db 0Bh, 00h, 00h, 89h, 9Eh, 1Ch, 0Bh, 00h, 00h, 66h, 89h, 9Eh, 20h, 0Bh, 00h, 00h
    db 88h, 9Eh, 0Ah, 0Ch, 00h, 00h, 88h, 9Eh, 0Bh, 0Ch, 00h, 00h, 88h, 9Eh, 0Ch, 0Ch
    db 00h, 00h, 88h, 9Eh, 0Dh, 0Ch, 00h, 00h, 88h, 9Eh, 58h, 0Ch, 00h, 00h, 88h, 9Eh
    db 59h, 0Ch, 00h, 00h, 0B8h, 1Eh, 00h, 00h, 00h, 89h, 86h, 6Ch, 0Ch, 00h, 00h, 89h
    db 9Eh, 0CCh, 0Eh, 00h, 00h, 88h, 9Eh, 0D0h, 0Eh, 00h, 00h, 0C6h, 86h, 0D1h, 0Eh, 00h
    db 00h, 01h, 0C7h, 86h, 0D4h, 0Eh, 00h, 00h, 33h, 33h, 33h, 3Fh, 89h, 9Eh, 0D8h, 0Eh
    db 00h, 00h, 89h, 86h, 0A4h, 0Ch, 00h, 00h, 0C7h, 86h, 0A8h, 0Ch, 00h, 00h, 0C8h, 00h
    db 00h, 00h, 0C7h, 86h, 0ACh, 0Ch, 00h, 00h, 0F4h, 01h, 00h, 00h, 0B8h, 0Ah, 00h, 00h
    db 00h, 89h, 86h, 0B0h, 0Ch, 00h, 00h, 89h, 86h, 0B4h, 0Ch, 00h, 00h, 0C7h, 86h, 0B8h
    db 0Ch, 00h, 00h, 14h, 00h, 00h, 00h, 0C7h, 86h, 0BCh, 0Ch, 00h, 00h, 88h, 13h, 00h
    db 00h, 0C7h, 86h, 0C0h, 0Ch, 00h, 00h, 60h, 0EAh, 00h, 00h, 0C7h, 86h, 0C4h, 0Ch, 00h
    db 00h, 98h, 3Ah, 00h, 00h, 88h, 9Eh, 0BEh, 0Dh, 00h, 00h, 88h, 9Eh, 0BFh, 0Dh, 00h
    db 00h, 8Bh, 96h, 18h, 02h, 00h, 00h, 52h, 8Bh, 0CEh, 0E8h, 95h, 67h, 0F8h, 0FFh, 8Dh
    db 8Eh, 80h, 0Bh, 00h, 00h, 88h, 9Eh, 7Dh, 0Bh, 00h, 00h, 0E8h, 60h, 26h, 80h, 00h
    db 8Dh, 8Eh, 84h, 0Bh, 00h, 00h, 0E8h, 55h, 26h, 80h, 00h, 88h, 9Eh, 88h, 0Bh, 00h
    db 00h, 8Bh, 0C5h, 89h, 86h, 98h, 0Bh, 00h, 00h, 89h, 86h, 9Ch, 0Bh, 00h, 00h, 89h
    db 86h, 0A0h, 0Bh, 00h, 00h, 89h, 86h, 0A4h, 0Bh, 00h, 00h, 8Bh, 0CDh, 89h, 8Eh, 2Ch
    db 0Ah, 00h, 00h, 89h, 8Eh, 30h, 0Ah, 00h, 00h, 89h, 8Eh, 34h, 0Ah, 00h, 00h, 89h
    db 8Eh, 38h, 0Ah, 00h, 00h, 89h, 8Eh, 3Ch, 0Ah, 00h, 00h, 89h, 8Eh, 40h, 0Ah, 00h
    db 00h, 68h, 10h, 02h, 00h, 00h, 89h, 0AEh, 0A8h, 0Bh, 00h, 00h, 0E8h, 0EFh, 0CBh, 7Fh
    db 00h, 8Bh, 0D0h, 83h, 0C4h, 04h, 3Bh, 0D3h, 74h, 0Dh, 0B9h, 84h, 00h, 00h, 00h, 8Bh
    db 0C5h, 8Bh, 0FAh, 0F3h, 0ABh, 0EBh, 02h, 33h, 0D2h, 6Ah, 1Ch, 68h, 0B8h, 0C6h, 07h, 01h
    db 8Dh, 8Eh, 0B0h, 0Bh, 00h, 00h, 89h, 96h, 94h, 0Bh, 00h, 00h, 0E8h, 0AFh, 29h, 80h
    db 00h, 0C6h, 86h, 0B4h, 0Bh, 00h, 00h, 01h, 88h, 9Eh, 0B5h, 0Bh, 00h, 00h, 0C6h, 86h
    db 0B6h, 0Bh, 00h, 00h, 01h, 88h, 5Eh, 2Ah, 88h, 9Eh, 0B7h, 0Bh, 00h, 00h, 88h, 9Eh
    db 0B8h, 0Bh, 00h, 00h, 88h, 9Eh, 0B9h, 0Bh, 00h, 00h, 89h, 0AEh, 0BCh, 0Bh, 00h, 00h
    db 89h, 0AEh, 0C0h, 0Bh, 00h, 00h, 0C7h, 86h, 74h, 0Bh, 00h, 00h, 00h, 00h, 20h, 41h
    db 0C7h, 86h, 78h, 0Bh, 00h, 00h, 0CDh, 0CCh, 0CCh, 3Dh, 0C6h, 86h, 7Ch, 0Bh, 00h, 00h
    db 01h, 89h, 0AEh, 0ACh, 0Bh, 00h, 00h, 68h, 04h, 01h, 00h, 00h, 0C6h, 86h, 0C4h, 0Bh
    db 00h, 00h, 01h, 8Dh, 54h, 24h, 48h, 89h, 9Eh, 0C8h, 0Bh, 00h, 00h, 52h, 0C7h, 86h
    db 0D0h, 0Bh, 00h, 00h, 0AEh, 6Fh, 4Bh, 25h, 53h, 0C7h, 86h, 0D4h, 0Bh, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 89h, 5Ch, 24h, 1Ch, 0FFh, 15h, 0C0h, 8Dh, 35h, 01h, 8Bh, 0Dh, 48h
    db 0CBh, 34h, 01h, 6Ah, 41h, 8Dh, 44h, 24h, 48h, 50h, 0E8h, 51h, 34h, 94h, 00h, 8Bh
    db 0F8h, 3Bh, 0FBh, 74h, 54h, 8Bh, 17h, 68h, 00h, 00h, 01h, 00h, 8Dh, 84h, 24h, 4Ch
    db 01h, 00h, 00h, 50h, 8Bh, 0CFh, 0FFh, 52h, 0Ch, 3Bh, 0C3h, 7Eh, 35h, 8Dh, 49h, 00h
    db 8Bh, 4Ch, 24h, 10h, 51h, 50h, 8Dh, 94h, 24h, 50h, 01h, 00h, 00h, 52h, 0E8h, 41h
    db 55h, 0F8h, 0FFh, 83h, 0C4h, 0Ch, 68h, 00h, 00h, 01h, 00h, 8Dh, 8Ch, 24h, 4Ch, 01h
    db 00h, 00h, 89h, 44h, 24h, 14h, 8Bh, 07h, 51h, 8Bh, 0CFh, 0FFh, 50h, 0Ch, 3Bh, 0C3h
    db 7Fh, 0CEh, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 08h, 8Bh, 0Dh, 44h, 0D6h, 2Eh, 01h, 3Bh
    db 0CBh, 74h, 1Fh, 0E8h, 0F3h, 62h, 0F9h, 0FFh, 89h, 44h, 24h, 14h, 8Bh, 44h, 24h, 10h
    db 50h, 8Dh, 4Ch, 24h, 18h, 6Ah, 04h, 51h, 0E8h, 0F7h, 54h, 0F8h, 0FFh, 83h, 0C4h, 0Ch
    db 0EBh, 04h, 8Bh, 44h, 24h, 10h, 8Bh, 3Dh, 3Ch, 23h, 2Ch, 01h, 3Bh, 0FBh, 89h, 44h
    db 24h, 14h, 89h, 44h, 24h, 10h, 75h, 08h, 39h, 1Dh, 40h, 23h, 2Ch, 01h, 74h, 3Eh
    db 8Bh, 15h, 0C4h, 23h, 2Ch, 01h, 0A1h, 0C8h, 23h, 2Ch, 01h, 8Dh, 4Ch, 24h, 14h, 89h
    db 54h, 24h, 18h, 51h, 8Dh, 54h, 24h, 14h, 52h, 8Dh, 4Ch, 24h, 2Ch, 89h, 44h, 24h
    db 24h, 0E8h, 4Dh, 0A4h, 0FAh, 0FFh, 8Bh, 4Ch, 24h, 18h, 8Dh, 44h, 24h, 24h, 99h, 52h
    db 50h, 8Bh, 44h, 24h, 24h, 50h, 51h, 0FFh, 0D7h, 83h, 0C4h, 10h, 0EBh, 0Ah, 50h, 50h
    db 0E8h, 13h, 0A0h, 0FBh, 0FFh, 83h, 0C4h, 08h, 89h, 86h, 0D0h, 0Bh, 00h, 00h, 0C7h, 86h
    db 0D8h, 0Bh, 00h, 00h, 02h, 00h, 00h, 00h, 88h, 9Eh, 70h, 0Ch, 00h, 00h, 0FFh, 15h
    db 00h, 90h, 35h, 01h, 89h, 86h, 74h, 0Ch, 00h, 00h, 88h, 9Eh, 0ACh, 0Ah, 00h, 00h
    db 0C7h, 86h, 0C8h, 0Ch, 00h, 00h, 0CDh, 0CCh, 0CCh, 3Dh, 0BAh, 0Ah, 00h, 00h, 00h, 89h
    db 96h, 0D4h, 0Dh, 00h, 00h, 0C7h, 86h, 0E8h, 0Dh, 00h, 00h, 05h, 00h, 00h, 00h, 88h
    db 9Eh, 34h, 0Eh, 00h, 00h, 0C7h, 86h, 38h, 0Eh, 00h, 00h, 0FFh, 00h, 00h, 00h, 89h
    db 9Eh, 40h, 0Eh, 00h, 00h, 89h, 9Eh, 3Ch, 0Eh, 00h, 00h, 0C7h, 86h, 44h, 0Eh, 00h
    db 00h, 6Ah, 0FFh, 0FFh, 0FFh, 0C7h, 86h, 48h, 0Eh, 00h, 00h, 60h, 0FFh, 0FFh, 0FFh, 0B8h
    db 80h, 00h, 00h, 00h, 89h, 86h, 50h, 0Eh, 00h, 00h, 89h, 86h, 4Ch, 0Eh, 00h, 00h
    db 88h, 9Eh, 54h, 0Eh, 00h, 00h, 0C6h, 86h, 55h, 0Eh, 00h, 00h, 01h, 89h, 9Eh, 5Ch
    db 0Eh, 00h, 00h, 89h, 0AEh, 68h, 0Eh, 00h, 00h, 88h, 9Eh, 6Ch, 0Eh, 00h, 00h, 88h
    db 9Eh, 60h, 0Eh, 00h, 00h, 0B9h, 3Ch, 00h, 00h, 00h, 89h, 8Eh, 70h, 0Eh, 00h, 00h
    db 0C7h, 86h, 74h, 0Eh, 00h, 00h, 7Dh, 00h, 00h, 00h, 89h, 96h, 78h, 0Eh, 00h, 00h
    db 0C7h, 86h, 7Ch, 0Eh, 00h, 00h, 19h, 00h, 00h, 00h, 0BAh, 64h, 00h, 00h, 00h, 89h
    db 96h, 80h, 0Eh, 00h, 00h, 0B8h, 2Ch, 01h, 00h, 00h, 89h, 86h, 84h, 0Eh, 00h, 00h
    db 89h, 96h, 88h, 0Eh, 00h, 00h, 89h, 86h, 8Ch, 0Eh, 00h, 00h, 0B8h, 50h, 00h, 00h
    db 00h, 89h, 86h, 90h, 0Eh, 00h, 00h, 0C7h, 86h, 94h, 0Eh, 00h, 00h, 96h, 00h, 00h
    db 00h, 89h, 86h, 98h, 0Eh, 00h, 00h, 0C7h, 86h, 9Ch, 0Eh, 00h, 00h, 78h, 00h, 00h
    db 00h, 89h, 8Eh, 0A0h, 0Eh, 00h, 00h, 89h, 86h, 0A4h, 0Eh, 00h, 00h, 0C7h, 86h, 0A8h
    db 0Eh, 00h, 00h, 32h, 00h, 00h, 00h, 89h, 8Eh, 0ACh, 0Eh, 00h, 00h, 88h, 9Eh, 0C8h
    db 0Eh, 00h, 00h, 88h, 9Eh, 0ECh, 11h, 00h, 00h, 89h, 9Eh, 0F0h, 11h, 00h, 00h, 0C7h
    db 86h, 0F4h, 11h, 00h, 00h, 03h, 00h, 00h, 00h, 0C7h, 86h, 0F8h, 11h, 00h, 00h, 00h
    db 00h, 0A0h, 40h, 0C6h, 86h, 0FCh, 11h, 00h, 00h, 01h, 89h, 0AEh, 20h, 12h, 00h, 00h
    db 0C6h, 86h, 6Ch, 12h, 00h, 00h, 01h, 89h, 9Eh, 70h, 12h, 00h, 00h, 0C7h, 86h, 74h
    db 12h, 00h, 00h, 00h, 00h, 20h, 42h, 0BAh, 01h, 00h, 00h, 00h, 89h, 96h, 24h, 12h
    db 00h, 00h, 89h, 96h, 28h, 12h, 00h, 00h, 89h, 96h, 2Ch, 12h, 00h, 00h, 89h, 96h
    db 30h, 12h, 00h, 00h, 89h, 96h, 34h, 12h, 00h, 00h, 89h, 96h, 38h, 12h, 00h, 00h
    db 89h, 96h, 3Ch, 12h, 00h, 00h, 89h, 96h, 40h, 12h, 00h, 00h, 89h, 96h, 44h, 12h
    db 00h, 00h, 89h, 96h, 48h, 12h, 00h, 00h, 89h, 96h, 4Ch, 12h, 00h, 00h, 89h, 96h
    db 50h, 12h, 00h, 00h, 89h, 96h, 54h, 12h, 00h, 00h, 89h, 96h, 58h, 12h, 00h, 00h
    db 89h, 96h, 5Ch, 12h, 00h, 00h, 89h, 96h, 60h, 12h, 00h, 00h, 89h, 96h, 64h, 12h
    db 00h, 00h, 89h, 96h, 68h, 12h, 00h, 00h, 0C7h, 86h, 14h, 12h, 00h, 00h, 0F2h, 5Eh
    db 0Bh, 0FFh, 0C7h, 86h, 18h, 12h, 00h, 00h, 02h, 21h, 0D9h, 0FFh, 5Fh, 88h, 9Eh, 78h
    db 12h, 00h, 00h, 8Bh, 0C6h, 5Eh, 5Dh, 8Bh, 8Ch, 24h, 3Ch, 01h, 01h, 00h, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 44h, 01h, 01h, 00h, 0C3h
?d_00084510@@YAXXZ ENDP
_TEXT ENDS
END
