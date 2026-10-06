.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0?$StringBase@D@@AAE@ABV0@@Z:NEAR
EXTERN ??0?$StringBase@D@@AAE@PBD@Z:NEAR
EXTERN ??0Gen_009D83D0@@QAE@XZ:NEAR
EXTERN ??1Gen_009D83D0@@UAE@XZ:NEAR
EXTERN ??_7Rva007F01B0@@6B@:BYTE
EXTERN ?BfmeDefeatScreenTable@@3PAEA:BYTE
EXTERN ?Campaign00598950@@3PAXA:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Glo012F1028@@3PAVGlo012F1028Type@@A:BYTE
EXTERN ?Glo012F7048@@3PAVGlo012F7048CampaignGateMode@@A:BYTE
EXTERN ?Rva006A16B0Empty@@3PADA:BYTE
EXTERN ?TheBfmeGlobal012F706C@@3PAVBfmeGlobal012F706C@@A:BYTE
EXTERN ?bfmeClose@Gen009D6DD0@@QAEXXZ:NEAR
EXTERN ?bfmeMake_009CB5F0@@YAPAVBfmeMade_009CB5F0@@PAX@Z:NEAR
EXTERN ?bfmeTakeEC@BfmeThingEC@@QAEHPAH@Z:NEAR
EXTERN ?bfmeTryActivate@Gen009D6300@@QAE_NPAVBfmeActivationStream@@H_N@Z:NEAR
EXTERN ?format@AsciiString@@QAAXV1@ZZ:NEAR
EXTERN ?j_000012f3@@YAXXZ:NEAR
EXTERN ?j_00002e46@@YAXXZ:NEAR
EXTERN ?j_00006fb9@@YAXXZ:NEAR
EXTERN ?j_0000a87b@@YAXXZ:NEAR
EXTERN ?j_0000bb81@@YAXXZ:NEAR
EXTERN ?j_000191e1@@YAXXZ:NEAR
EXTERN ?j_0001b5db@@YAXXZ:NEAR
EXTERN ?j_00020379@@YAXXZ:NEAR
EXTERN ?j_0002615c@@YAXXZ:NEAR
EXTERN ?j_00028bb9@@YAXXZ:NEAR
EXTERN ?j_0002bf0d@@YAXXZ:NEAR
EXTERN ?j_00032a56@@YAXXZ:NEAR
EXTERN ?j_0003ac9c@@YAXXZ:NEAR
EXTERN ?j_00043275@@YAXXZ:NEAR
EXTERN ?j_00045b88@@YAXXZ:NEAR
EXTERN ?j_0004704b@@YAXXZ:NEAR
EXTERN ?j_0004958a@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?set@?$StringBase@D@@QAEXABV1@@Z:NEAR
EXTERN __imp__free:BYTE
EXTERN g_Va0101EC20:NEAR
EXTERN g_Va0101EED8:NEAR
EXTERN g_Va0101F070:NEAR
EXTERN g_Va0101F2F8:NEAR
EXTERN g_Va010EDC1C:BYTE
EXTERN g_Va010EE048:BYTE
EXTERN g_Va012F7090:BYTE
_TEXT SEGMENT

; ghidra: FUN_007c2100  retail @ 0x003C2100 size 300
_TEXT ENDS
_TEXT$d007c2100 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007C2100 size 300
public ?d_003c2100@@YAXXZ
?d_003c2100@@YAXXZ PROC
    db 055h, 08Bh, 0ECh, 083h, 0E4h, 0F8h, 06Ah, 0FFh, 068h
    dd g_Va0101EC20
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 020h, 053h, 056h, 057h, 08Bh, 07Dh, 008h, 08Bh, 087h, 0D4h, 000h, 000h, 000h, 08Bh, 097h, 0D8h
    db 000h, 000h, 000h, 02Bh, 0D0h, 08Bh, 0F1h, 033h, 0DBh, 0C1h, 0FAh, 002h, 033h, 0C9h, 085h, 0D2h
    db 089h, 074h, 024h, 014h, 089h, 05Ch, 024h, 010h, 00Fh, 086h, 0CDh, 000h, 000h, 000h, 0EBh, 006h
    db 08Bh, 074h, 024h, 014h, 033h, 0C9h, 089h, 04Ch, 024h, 00Ch, 089h, 04Ch, 024h, 034h, 08Dh, 04Ch
    db 024h, 00Ch, 051h, 08Dh, 014h, 098h, 052h, 08Bh, 0CEh
    call ?j_000012f3@@YAXXZ
    db 084h, 0C0h, 088h, 044h, 024h, 018h, 074h, 007h, 08Dh, 044h, 024h, 00Ch, 050h, 0EBh, 00Ah, 08Bh
    db 087h, 0D4h, 000h, 000h, 000h, 08Dh, 00Ch, 098h, 051h, 08Bh, 0CEh
    call ?j_00032a56@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 074h, 058h, 08Dh, 054h, 024h, 020h, 052h, 08Bh, 0CEh
    call ?j_00043275@@YAXXZ
    db 08Bh, 04Ch, 024h, 018h, 050h, 057h
    call ?j_00006fb9@@YAXXZ
    db 08Bh, 0D8h, 083h, 0FBh, 0FFh, 074h, 036h, 08Dh, 044h, 024h, 01Ch, 050h, 08Bh, 0CEh
    call ?j_0004958a@@YAXXZ
    db 08Bh, 04Ch, 024h, 018h, 051h, 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Dh, 054h, 024h, 024h, 052h, 053h, 050h, 0C6h, 044h, 024h, 044h, 001h
    call ?j_000191e1@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 044h, 024h, 034h, 000h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 05Ch, 024h, 010h, 08Dh, 04Ch, 024h, 00Ch, 0C7h, 044h, 024h, 034h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 087h, 0D4h, 000h, 000h, 000h, 08Bh, 08Fh, 0D8h, 000h, 000h, 000h, 02Bh, 0C8h, 043h, 0C1h
    db 0F9h, 002h, 03Bh, 0D9h, 089h, 05Ch, 024h, 010h, 00Fh, 082h, 035h, 0FFh, 0FFh, 0FFh, 08Bh, 04Ch
    db 024h, 02Ch, 05Fh, 05Eh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 08Bh, 0E5h, 05Dh, 0C2h
    db 004h, 000h
?d_003c2100@@YAXXZ ENDP
_TEXT$d007c2100 ENDS
_TEXT SEGMENT

; ghidra: FUN_007c2280  retail @ 0x003C2280 size 67
public ?d_003c2280@@YAXXZ
?d_003c2280@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Ah, 42h, 08h, 84h, 0C0h, 89h, 54h, 24h, 04h, 74h, 05h, 83h
    db 0C1h, 5Ch, 0EBh, 03h, 83h, 0C1h, 50h, 8Bh, 41h, 04h, 3Bh, 41h, 08h, 74h, 0Dh, 85h
    db 0C0h, 74h, 02h, 89h, 10h, 83h, 41h, 04h, 04h, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h
    db 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 54h, 24h, 10h, 52h, 50h, 0E8h, 0D6h, 5Bh, 0C4h, 0FFh
    db 0C2h, 04h, 00h
?d_003c2280@@YAXXZ ENDP

; ghidra: FUN_007c22e0  retail @ 0x003C22E0 size 473
public ?d_003c22e0@@YAXXZ
?d_003c22e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 0ECh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 18h, 53h, 55h, 57h, 8Bh, 0F9h, 33h, 0C9h, 33h
    db 0DBh, 33h, 0D2h, 33h, 0EDh, 89h, 4Ch, 24h, 18h, 89h, 5Ch, 24h, 1Ch, 89h, 54h, 24h
    db 20h, 0A1h, 48h, 70h, 2Fh, 01h, 8Bh, 40h, 04h, 83h, 0F8h, 01h, 89h, 6Ch, 24h, 2Ch
    db 0Fh, 85h, 81h, 01h, 00h, 00h, 0A1h, 6Ch, 70h, 2Fh, 01h, 38h, 90h, 88h, 02h, 00h
    db 00h, 0Fh, 85h, 70h, 01h, 00h, 00h, 8Ah, 47h, 78h, 84h, 0C0h, 74h, 23h, 8Dh, 4Ch
    db 24h, 18h, 0C7h, 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D4h, 9Eh, 0C6h, 0FFh, 5Fh
    db 5Dh, 5Bh, 8Bh, 4Ch, 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h
    db 0C3h, 8Bh, 47h, 54h, 56h, 2Bh, 47h, 50h, 0C1h, 0F8h, 02h, 85h, 0C0h, 0Fh, 86h, 82h
    db 00h, 00h, 00h, 8Bh, 47h, 50h, 8Bh, 34h, 0A8h, 8Bh, 46h, 04h, 85h, 0C0h, 89h, 74h
    db 24h, 14h, 74h, 16h, 8Bh, 0CEh, 0E8h, 0A6h, 74h, 0C4h, 0FFh, 85h, 0C0h, 75h, 0Bh, 8Bh
    db 16h, 8Bh, 0CEh, 0FFh, 52h, 10h, 84h, 0C0h, 75h, 14h, 8Bh, 46h, 04h, 8Bh, 16h, 85h
    db 0C0h, 0Fh, 94h, 0C0h, 8Bh, 0CEh, 50h, 0FFh, 52h, 14h, 84h, 0C0h, 74h, 31h, 3Bh, 5Ch
    db 24h, 24h, 74h, 0Fh, 85h, 0DBh, 74h, 02h, 89h, 33h, 83h, 0C3h, 04h, 89h, 5Ch, 24h
    db 20h, 0EBh, 1Ch, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 1Bh, 51h, 8Dh, 54h, 24h, 20h
    db 52h, 53h, 8Dh, 4Ch, 24h, 30h, 0E8h, 0BBh, 5Ah, 0C4h, 0FFh, 8Bh, 5Ch, 24h, 20h, 8Bh
    db 47h, 54h, 2Bh, 47h, 50h, 45h, 0C1h, 0F8h, 02h, 3Bh, 0E8h, 72h, 86h, 8Bh, 4Ch, 24h
    db 1Ch, 8Bh, 54h, 24h, 24h, 2Bh, 0D9h, 0C1h, 0FBh, 02h, 33h, 0EDh, 85h, 0DBh, 89h, 5Ch
    db 24h, 18h, 76h, 60h, 8Bh, 0Ch, 0A9h, 8Bh, 5Fh, 54h, 8Bh, 47h, 50h, 8Dh, 54h, 24h
    db 13h, 52h, 89h, 4Ch, 24h, 18h, 8Dh, 4Ch, 24h, 18h, 51h, 53h, 50h, 0E8h, 0B7h, 0B2h
    db 0C4h, 0FFh, 8Bh, 0F0h, 83h, 0C4h, 10h, 3Bh, 0F3h, 74h, 28h, 8Bh, 0Eh, 85h, 0C9h, 74h
    db 06h, 8Bh, 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 47h, 54h, 8Dh, 4Eh, 04h, 3Bh, 0C1h, 74h
    db 0Eh, 2Bh, 0C1h, 50h, 51h, 56h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 83h
    db 47h, 54h, 0FCh, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch, 24h, 1Ch, 45h, 3Bh, 0E8h, 72h, 0A4h
    db 8Bh, 54h, 24h, 24h, 85h, 0C9h, 0C7h, 44h, 24h, 30h, 0FFh, 0FFh, 0FFh, 0FFh, 5Eh, 74h
    db 36h, 2Bh, 0D1h, 0C1h, 0FAh, 02h, 0C1h, 0E2h, 02h, 8Bh, 0C2h, 3Dh, 80h, 00h, 00h, 00h
    db 76h, 1Bh, 51h, 0E8h, 28h, 0FAh, 4Bh, 00h, 83h, 0C4h, 04h, 5Fh, 5Dh, 5Bh, 8Bh, 4Ch
    db 24h, 18h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C3h, 50h, 51h, 0E8h
    db 4Ch, 0C1h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 24h, 5Fh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 24h, 0C3h
?d_003c22e0@@YAXXZ ENDP

; ghidra: FUN_007c2530  retail @ 0x003C2530 size 160
public ?d_003c2530@@YAXXZ
?d_003c2530@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 2Ch, 84h, 0C0h, 0Fh, 84h, 90h, 00h, 00h, 00h, 8Bh, 0Dh
    db 58h, 4Bh, 2Fh, 01h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 14h, 8Bh, 0Dh, 98h
    db 08h, 2Fh, 01h, 0E8h, 3Eh, 07h, 0C6h, 0FFh, 84h, 0C0h, 75h, 72h, 8Bh, 0CEh, 0E8h, 82h
    db 0FDh, 0C6h, 0FFh, 8Ah, 46h, 2Dh, 84h, 0C0h, 74h, 64h, 57h, 8Bh, 3Dh, 98h, 08h, 2Fh
    db 01h, 8Bh, 87h, 0A0h, 01h, 00h, 00h, 81h, 0C7h, 0A0h, 01h, 00h, 00h, 85h, 0C0h, 75h
    db 05h, 0E8h, 3Ah, 9Fh, 53h, 00h, 0FFh, 07h, 8Bh, 4Eh, 28h, 85h, 0C9h, 5Fh, 74h, 05h
    db 0E8h, 73h, 67h, 0C6h, 0FFh, 8Bh, 0CEh, 0E8h, 0B0h, 0F8h, 0C3h, 0FFh, 8Bh, 0CEh, 0E8h, 20h
    db 0CEh, 0C7h, 0FFh, 8Bh, 0CEh, 0E8h, 0A4h, 80h, 0C6h, 0FFh, 8Bh, 0CEh, 0E8h, 0D7h, 0B0h, 0C5h
    db 0FFh, 8Bh, 0CEh, 0E8h, 0FEh, 66h, 0C8h, 0FFh, 8Bh, 0Dh, 6Ch, 70h, 2Fh, 01h, 8Bh, 11h
    db 0FFh, 52h, 14h, 0A1h, 98h, 08h, 2Fh, 01h, 0FFh, 88h, 0A0h, 01h, 00h, 00h, 5Eh, 0C3h
?d_003c2530@@YAXXZ ENDP

; ghidra: FUN_007c2720  retail @ 0x003C2720 size 134
public ?d_003c2720@@YAXXZ
?d_003c2720@@YAXXZ PROC
    db 8Bh, 91h, 94h, 00h, 00h, 00h, 53h, 56h, 8Dh, 0B1h, 94h, 00h, 00h, 00h, 8Bh, 4Eh
    db 04h, 8Bh, 0C1h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 85h, 0C0h, 57h, 7Eh, 10h, 8Dh, 49h, 00h
    db 8Bh, 39h, 89h, 3Ah, 83h, 0C1h, 04h, 83h, 0C2h, 04h, 48h, 75h, 0F3h, 8Bh, 5Ch, 24h
    db 10h, 89h, 56h, 04h, 8Bh, 03h, 8Bh, 4Bh, 04h, 2Bh, 0C8h, 0C1h, 0F9h, 02h, 33h, 0FFh
    db 85h, 0C9h, 76h, 3Ch, 8Bh, 56h, 08h, 8Dh, 0Ch, 0B8h, 8Bh, 46h, 04h, 3Bh, 0C2h, 74h
    db 0Eh, 85h, 0C0h, 74h, 04h, 8Bh, 11h, 89h, 10h, 83h, 46h, 04h, 04h, 0EBh, 12h, 6Ah
    db 01h, 6Ah, 01h, 8Dh, 54h, 24h, 18h, 52h, 51h, 50h, 8Bh, 0CEh, 0E8h, 0F7h, 0Dh, 0C6h
    db 0FFh, 8Bh, 03h, 8Bh, 4Bh, 04h, 2Bh, 0C8h, 47h, 0C1h, 0F9h, 02h, 3Bh, 0F9h, 72h, 0C4h
    db 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_003c2720@@YAXXZ ENDP

; ghidra: FUN_007c2830  retail @ 0x003C2830 size 326
public ?d_003c2830@@YAXXZ
?d_003c2830@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 06h, 57h, 8Dh, 4Ch, 24h, 0Ch
    db 0BBh, 01h, 00h, 00h, 00h, 51h, 8Bh, 0CEh, 88h, 5Ch, 24h, 10h, 88h, 5Ch, 24h, 11h
    db 0FFh, 50h, 28h, 8Bh, 7Ch, 24h, 20h, 8Bh, 0Fh, 8Bh, 57h, 04h, 8Bh, 06h, 2Bh, 0D1h
    db 8Dh, 4Ch, 24h, 20h, 0D1h, 0FAh, 51h, 8Bh, 0CEh, 89h, 54h, 24h, 20h, 0C7h, 44h, 24h
    db 24h, 48h, 55h, 07h, 01h, 0FFh, 50h, 2Ch, 8Bh, 10h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh
    db 0C8h, 0FFh, 52h, 74h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 08h, 84h, 0C0h, 74h, 3Ah, 8Bh
    db 5Fh, 04h, 8Bh, 3Fh, 3Bh, 0FBh, 0Fh, 84h, 0D1h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 8Bh, 06h, 57h, 8Bh, 0CEh, 0FFh, 90h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 47h, 01h
    db 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 83h, 0C7h, 02h, 3Bh, 0FBh, 75h, 0E0h
    db 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h, 8Bh, 0Fh, 3Bh, 4Fh, 04h, 74h, 23h
    db 68h, 24h, 55h, 07h, 01h, 8Dh, 54h, 24h, 14h, 6Ah, 04h, 52h, 0E8h, 3Fh, 39h, 61h
    db 00h, 83h, 0C4h, 0Ch, 68h, 5Ch, 0FEh, 1Dh, 01h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 0Dh
    db 44h, 63h, 00h, 8Bh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CFh, 0E8h, 0ADh, 9Eh, 0C4h, 0FFh, 8Bh
    db 44h, 24h, 1Ch, 85h, 0C0h, 88h, 5Ch, 24h, 20h, 0C6h, 44h, 24h, 21h, 00h, 74h, 5Dh
    db 8Bh, 54h, 24h, 1Ch, 4Ah, 8Dh, 44h, 24h, 20h, 89h, 54h, 24h, 1Ch, 8Bh, 16h, 50h
    db 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 21h, 50h, 8Bh
    db 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 47h, 04h, 3Bh, 47h, 08h, 74h, 12h, 85h
    db 0C0h, 74h, 08h, 66h, 8Bh, 4Ch, 24h, 20h, 66h, 89h, 08h, 83h, 47h, 04h, 02h, 0EBh
    db 14h, 53h, 53h, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 4Ch, 24h, 2Ch, 51h, 50h, 8Bh, 0CFh
    db 0E8h, 0B9h, 4Fh, 0C4h, 0FFh, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 75h, 0A3h, 5Fh, 8Bh, 0C6h
    db 5Eh, 5Bh, 83h, 0C4h, 0Ch, 0C3h
?d_003c2830@@YAXXZ ENDP

; ghidra: FUN_007c29d0  retail @ 0x003C29D0 size 402
public ?d_003c29d0@@YAXXZ
?d_003c29d0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 58h, 0ECh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 74h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 28h, 85h, 0C9h
    db 0Fh, 84h, 57h, 01h, 00h, 00h, 57h, 8Bh, 0BCh, 24h, 8Ch, 00h, 00h, 00h, 85h, 0FFh
    db 0Fh, 8Ch, 46h, 01h, 00h, 00h, 8Dh, 46h, 30h, 50h, 0E8h, 0FEh, 94h, 0C6h, 0FFh, 85h
    db 0C0h, 0Fh, 84h, 35h, 01h, 00h, 00h, 8Bh, 8Eh, 88h, 00h, 00h, 00h, 8Bh, 96h, 84h
    db 00h, 00h, 00h, 81h, 0C6h, 84h, 00h, 00h, 00h, 2Bh, 0CAh, 0D1h, 0F9h, 3Bh, 0F9h, 55h
    db 72h, 74h, 8Bh, 68h, 60h, 8Bh, 50h, 64h, 8Bh, 48h, 58h, 2Bh, 0D5h, 2Bh, 48h, 54h
    db 0C1h, 0FAh, 02h, 0C1h, 0F9h, 02h, 03h, 0D1h, 3Bh, 0FAh, 0Fh, 83h, 0FBh, 00h, 00h, 00h
    db 8Bh, 56h, 04h, 2Bh, 16h, 0D1h, 0FAh, 3Bh, 0D7h, 77h, 4Bh, 0C6h, 44h, 24h, 0Eh, 01h
    db 0C6h, 44h, 24h, 0Fh, 00h, 66h, 8Bh, 6Ch, 24h, 0Eh, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 46h, 04h, 3Bh, 46h, 08h, 74h, 0Dh, 85h, 0C0h, 74h, 03h, 66h, 89h, 28h, 83h
    db 46h, 04h, 02h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 16h, 51h, 8Dh, 54h
    db 24h, 1Ah, 52h, 50h, 8Bh, 0CEh, 0E8h, 83h, 4Eh, 0C4h, 0FFh, 8Bh, 46h, 04h, 2Bh, 06h
    db 0D1h, 0F8h, 3Bh, 0C7h, 76h, 0CAh, 8Bh, 36h, 8Ah, 8Ch, 24h, 94h, 00h, 00h, 00h, 8Ah
    db 04h, 7Eh, 88h, 0Ch, 7Eh, 8Bh, 15h, 68h, 0D6h, 2Eh, 01h, 85h, 0D2h, 0Fh, 84h, 88h
    db 00h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 80h, 00h, 00h, 00h, 84h, 0C9h, 74h, 7Ch, 8Bh
    db 0Dh, 48h, 0D7h, 2Eh, 01h, 8Bh, 41h, 0Ch, 85h, 0C0h, 74h, 6Fh, 8Bh, 50h, 04h, 85h
    db 0D2h, 74h, 68h, 8Bh, 0C2h, 8Bh, 90h, 04h, 01h, 00h, 00h, 85h, 0D2h, 74h, 5Ch, 8Bh
    db 41h, 0Ch, 8Bh, 40h, 04h, 6Ah, 02h, 05h, 04h, 01h, 00h, 00h, 50h, 8Dh, 4Ch, 24h
    db 18h, 0E8h, 0Dh, 0C1h, 0C5h, 0FFh, 8Bh, 0Dh, 48h, 0D7h, 2Eh, 01h, 8Bh, 41h, 0Ch, 8Bh
    db 40h, 24h, 50h, 8Dh, 4Ch, 24h, 14h, 0C7h, 84h, 24h, 8Ch, 00h, 00h, 00h, 00h, 00h
    db 00h, 00h, 0E8h, 61h, 81h, 0C7h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 11h, 8Dh
    db 44h, 24h, 10h, 50h, 0FFh, 52h, 44h, 8Dh, 4Ch, 24h, 10h, 0C7h, 84h, 24h, 88h, 00h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0EAh, 43h, 0C6h, 0FFh, 5Dh, 5Fh, 8Bh, 4Ch, 24h
    db 78h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 80h, 00h, 00h, 00h, 0C2h
    db 08h, 00h
?d_003c29d0@@YAXXZ ENDP

; ghidra: FUN_007c2ee0  retail @ 0x003C2EE0 size 76
public ?d_003c2ee0@@YAXXZ
?d_003c2ee0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 39h, 8Bh, 0D0h, 2Bh, 0D7h, 0D1h
    db 0FAh, 3Bh, 0F2h, 73h, 24h, 8Bh, 0D0h, 2Bh, 0C2h, 0D1h, 0F8h, 85h, 0C0h, 8Dh, 34h, 77h
    db 7Eh, 0Fh, 66h, 8Bh, 3Ah, 66h, 89h, 3Eh, 83h, 0C2h, 02h, 83h, 0C6h, 02h, 48h, 75h
    db 0F1h, 5Fh, 89h, 71h, 04h, 5Eh, 0C2h, 08h, 00h, 8Dh, 7Ch, 24h, 10h, 57h, 2Bh, 0F2h
    db 56h, 50h, 0E8h, 0D2h, 0E8h, 0C7h, 0FFh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_003c2ee0@@YAXXZ ENDP

; ghidra: FUN_007c2f40  retail @ 0x003C2F40 size 100
public ?d_003c2f40@@YAXXZ
?d_003c2f40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0ECh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 33h, 0DBh
    db 0C7h, 06h, 08h, 0DAh, 0Eh, 01h, 6Ah, 2Ch, 89h, 5Ch, 24h, 18h, 89h, 5Eh, 0Ch, 0E8h
    db 0CCh, 0B5h, 46h, 00h, 8Bh, 4Ch, 24h, 10h, 89h, 46h, 0Ch, 89h, 5Eh, 10h, 88h, 18h
    db 8Bh, 46h, 0Ch, 89h, 58h, 04h, 8Bh, 46h, 0Ch, 89h, 40h, 08h, 8Bh, 46h, 0Ch, 83h
    db 0C4h, 04h, 89h, 40h, 0Ch, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 10h, 0C3h
?d_003c2f40@@YAXXZ ENDP

; ghidra: FUN_007c2fc0  retail @ 0x003C2FC0 size 394
public ?d_003c2fc0@@YAXXZ
?d_003c2fc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Ah, 0EDh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h
    db 0E8h, 4Bh, 0EAh, 5Dh, 00h, 33h, 0DBh, 89h, 5Ch, 24h, 18h, 0C7h, 46h, 08h, 44h, 37h
    db 07h, 01h, 0C7h, 06h, 0DCh, 0DBh, 0Eh, 01h, 0C7h, 46h, 08h, 0C8h, 0DBh, 0Eh, 01h, 89h
    db 5Eh, 0Ch, 89h, 5Eh, 10h, 89h, 5Eh, 14h, 89h, 5Eh, 18h, 88h, 5Eh, 1Ch, 89h, 5Eh
    db 20h, 89h, 5Eh, 24h, 0B8h, 01h, 00h, 00h, 00h, 88h, 5Eh, 2Ch, 88h, 46h, 2Dh, 89h
    db 5Eh, 30h, 89h, 5Eh, 34h, 89h, 5Eh, 38h, 89h, 5Eh, 3Ch, 89h, 5Eh, 40h, 88h, 5Eh
    db 44h, 88h, 5Eh, 45h, 89h, 5Eh, 48h, 88h, 5Eh, 4Ch, 88h, 5Eh, 4Dh, 88h, 5Eh, 4Eh
    db 89h, 5Eh, 50h, 89h, 5Eh, 54h, 89h, 5Eh, 58h, 89h, 5Eh, 5Ch, 89h, 5Eh, 60h, 89h
    db 5Eh, 64h, 89h, 5Eh, 68h, 89h, 5Eh, 6Ch, 89h, 5Eh, 70h, 89h, 46h, 74h, 88h, 5Eh
    db 78h, 89h, 5Eh, 7Ch, 88h, 9Eh, 80h, 00h, 00h, 00h, 89h, 9Eh, 84h, 00h, 00h, 00h
    db 89h, 9Eh, 88h, 00h, 00h, 00h, 89h, 9Eh, 8Ch, 00h, 00h, 00h, 89h, 86h, 90h, 00h
    db 00h, 00h, 89h, 9Eh, 94h, 00h, 00h, 00h, 89h, 9Eh, 98h, 00h, 00h, 00h, 89h, 9Eh
    db 9Ch, 00h, 00h, 00h, 89h, 86h, 0A0h, 00h, 00h, 00h, 89h, 9Eh, 0A4h, 00h, 00h, 00h
    db 33h, 0C0h, 89h, 86h, 0A8h, 00h, 00h, 00h, 89h, 86h, 0ACh, 00h, 00h, 00h, 89h, 86h
    db 0B0h, 00h, 00h, 00h, 89h, 86h, 0B4h, 00h, 00h, 00h, 89h, 86h, 0B8h, 00h, 00h, 00h
    db 53h, 8Dh, 8Eh, 0C0h, 00h, 00h, 00h, 0C6h, 44h, 24h, 1Ch, 09h, 89h, 86h, 0BCh, 00h
    db 00h, 00h, 0E8h, 28h, 0C3h, 0C7h, 0FFh, 0C6h, 44h, 24h, 18h, 0Ah, 89h, 9Eh, 0C4h, 00h
    db 00h, 00h, 88h, 9Eh, 0C8h, 00h, 00h, 00h, 89h, 9Eh, 0CCh, 00h, 00h, 00h, 89h, 9Eh
    db 0D0h, 00h, 00h, 00h, 89h, 9Eh, 0D4h, 00h, 00h, 00h, 6Ah, 48h, 89h, 9Eh, 0D8h, 00h
    db 00h, 00h, 0E8h, 29h, 0EEh, 4Bh, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 0Ch, 3Bh, 0C3h
    db 0C6h, 44h, 24h, 18h, 0Bh, 74h, 1Dh, 8Bh, 0C8h, 0E8h, 7Fh, 14h, 0C4h, 0FFh, 89h, 46h
    db 28h, 8Bh, 0C6h, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 14h, 0C3h, 8Bh, 4Ch, 24h, 10h, 89h, 5Eh, 28h, 8Bh, 0C6h, 5Eh, 5Bh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_003c2fc0@@YAXXZ ENDP

; ghidra: FUN_007c31d0  retail @ 0x003C31D0 size 544
public ?d_003c31d0@@YAXXZ
?d_003c31d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Bh, 0EEh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 0C7h
    db 06h, 0DCh, 0DBh, 0Eh, 01h, 0C7h, 46h, 08h, 0C8h, 0DBh, 0Eh, 01h, 0C7h, 44h, 24h, 14h
    db 0Ah, 00h, 00h, 00h, 0E8h, 2Ah, 81h, 0C5h, 0FFh, 8Bh, 0CEh, 0E8h, 65h, 16h, 0C6h, 0FFh
    db 8Bh, 0CEh, 0E8h, 0C9h, 0E2h, 0C5h, 0FFh, 8Bh, 4Eh, 28h, 85h, 0C9h, 74h, 06h, 8Bh, 01h
    db 6Ah, 01h, 0FFh, 10h, 8Bh, 8Eh, 0D4h, 00h, 00h, 00h, 57h, 51h, 0C7h, 46h, 28h, 00h
    db 00h, 00h, 00h, 0FFh, 15h, 0D4h, 93h, 35h, 01h, 8Dh, 0BEh, 0C0h, 00h, 00h, 00h, 83h
    db 0C4h, 04h, 8Bh, 0CFh, 0C7h, 86h, 0D4h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 86h
    db 0D8h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0C6h, 44h, 24h, 18h, 09h, 0E8h, 33h, 7Dh
    db 0C6h, 0FFh, 8Bh, 3Fh, 85h, 0FFh, 74h, 0Bh, 6Ah, 14h, 57h, 0E8h, 80h, 0B3h, 46h, 00h
    db 83h, 0C4h, 08h, 8Bh, 8Eh, 94h, 00h, 00h, 00h, 85h, 0C9h, 0C6h, 44h, 24h, 18h, 08h
    db 5Fh, 74h, 2Ah, 8Bh, 86h, 9Ch, 00h, 00h, 00h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 12h, 0ECh, 4Bh, 00h, 83h, 0C4h
    db 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 46h, 0B3h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 8Eh, 84h
    db 00h, 00h, 00h, 85h, 0C9h, 0C6h, 44h, 24h, 14h, 07h, 74h, 28h, 8Bh, 86h, 8Ch, 00h
    db 00h, 00h, 2Bh, 0C1h, 0D1h, 0F8h, 03h, 0C0h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h
    db 0E8h, 0DBh, 0EBh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0Fh, 0B3h, 46h
    db 00h, 83h, 0C4h, 08h, 8Dh, 4Eh, 68h, 0C6h, 44h, 24h, 14h, 06h, 0E8h, 90h, 6Dh, 0C6h
    db 0FFh, 8Bh, 4Eh, 5Ch, 85h, 0C9h, 0C6h, 44h, 24h, 14h, 05h, 74h, 27h, 8Bh, 46h, 64h
    db 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h
    db 0E8h, 9Bh, 0EBh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0CFh, 0B2h, 46h
    db 00h, 83h, 0C4h, 08h, 8Bh, 4Eh, 50h, 85h, 0C9h, 0C6h, 44h, 24h, 14h, 04h, 74h, 27h
    db 8Bh, 46h, 58h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h
    db 76h, 0Bh, 51h, 0E8h, 68h, 0EBh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h
    db 9Ch, 0B2h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 4Eh, 38h, 85h, 0C9h, 0C6h, 44h, 24h, 14h
    db 03h, 74h, 27h, 8Bh, 46h, 40h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h
    db 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 35h, 0EBh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah
    db 50h, 51h, 0E8h, 69h, 0B2h, 46h, 00h, 83h, 0C4h, 08h, 8Dh, 4Eh, 30h, 0C6h, 44h, 24h
    db 14h, 02h, 0E8h, 0A9h, 45h, 4Ch, 00h, 8Bh, 4Eh, 0Ch, 85h, 0C9h, 0C6h, 44h, 24h, 14h
    db 01h, 74h, 27h, 8Bh, 46h, 14h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h
    db 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0F5h, 0EAh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah
    db 50h, 51h, 0E8h, 29h, 0B2h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 0CEh, 0C7h, 46h, 08h, 44h
    db 37h, 07h, 01h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 60h, 0E6h, 5Dh, 00h
    db 8Bh, 4Ch, 24h, 0Ch, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C3h
?d_003c31d0@@YAXXZ ENDP

; ghidra: FUN_007c3480  retail @ 0x003C3480 size 477
public ?d_003c3480@@YAXXZ
?d_003c3480@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 4Bh, 0EEh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 55h, 56h, 8Bh, 74h, 24h, 24h, 8Bh, 2Eh
    db 8Bh, 46h, 04h, 2Bh, 0C5h, 8Bh, 6Ch, 24h, 20h, 8Bh, 55h, 00h, 0C1h, 0F8h, 02h, 89h
    db 44h, 24h, 24h, 57h, 8Dh, 44h, 24h, 28h, 50h, 8Bh, 0CDh, 0FFh, 52h, 78h, 8Bh, 55h
    db 00h, 8Bh, 0CDh, 0FFh, 52h, 04h, 33h, 0FFh, 84h, 0C0h, 8Bh, 44h, 24h, 28h, 0Fh, 84h
    db 35h, 01h, 00h, 00h, 3Bh, 0C7h, 89h, 7Ch, 24h, 24h, 0Fh, 8Eh, 69h, 01h, 00h, 00h
    db 53h, 8Bh, 45h, 00h, 6Ah, 04h, 8Dh, 4Ch, 24h, 14h, 51h, 68h, 8Ch, 0DAh, 0Eh, 01h
    db 8Bh, 0CDh, 0FFh, 90h, 90h, 00h, 00h, 00h, 8Bh, 44h, 24h, 10h, 48h, 83h, 0F8h, 07h
    db 0Fh, 87h, 0D9h, 00h, 00h, 00h, 0FFh, 24h, 85h, 60h, 36h, 7Ch, 00h, 6Ah, 10h, 0E8h
    db 1Ch, 0EAh, 4Bh, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 18h, 0C7h, 00h, 0C0h, 0D9h, 0Eh
    db 01h, 8Bh, 0D8h, 89h, 78h, 0Ch, 8Bh, 13h, 55h, 8Bh, 0CBh, 0FFh, 52h, 0Ch, 0E9h, 7Eh
    db 00h, 00h, 00h, 33h, 0DBh, 8Bh, 13h, 55h, 8Bh, 0CBh, 0FFh, 52h, 0Ch, 0EBh, 72h, 6Ah
    db 20h, 0E8h, 0EAh, 0E9h, 4Bh, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 5Ah, 0C7h, 00h, 38h
    db 0D9h, 0Eh, 01h, 8Bh, 0D8h, 0EBh, 52h, 6Ah, 1Ch, 0E8h, 0D2h, 0E9h, 4Bh, 00h, 83h, 0C4h
    db 04h, 89h, 44h, 24h, 14h, 3Bh, 0C7h, 89h, 7Ch, 24h, 20h, 74h, 13h, 8Bh, 0C8h, 0E8h
    db 0F9h, 79h, 0C6h, 0FFh, 8Bh, 0D8h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 29h
    db 33h, 0DBh, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0EBh, 1Dh, 6Ah, 10h, 0E8h, 9Dh
    db 0E9h, 4Bh, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 0Dh, 0C7h, 00h, 0F8h, 0D8h, 0Eh, 01h
    db 89h, 78h, 0Ch, 8Bh, 0D8h, 0EBh, 02h, 33h, 0DBh, 8Bh, 03h, 8Bh, 0CBh, 55h, 0FFh, 50h
    db 0Ch, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 89h, 5Ch, 24h, 14h, 74h, 0Ch, 3Bh, 0C7h, 74h
    db 02h, 89h, 18h, 83h, 46h, 04h, 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h
    db 34h, 51h, 8Dh, 54h, 24h, 20h, 52h, 8Bh, 0CEh, 50h, 0E8h, 0B7h, 48h, 0C4h, 0FFh, 8Bh
    db 44h, 24h, 28h, 8Bh, 4Ch, 24h, 2Ch, 40h, 3Bh, 0C1h, 89h, 44h, 24h, 28h, 0Fh, 8Ch
    db 0EDh, 0FEh, 0FFh, 0FFh, 5Bh, 5Fh, 5Eh, 5Dh, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h, 3Bh, 0C7h, 7Eh, 3Ch, 8Dh, 49h, 00h
    db 8Bh, 06h, 8Bh, 0Ch, 0B8h, 8Bh, 11h, 0FFh, 52h, 18h, 6Ah, 04h, 8Dh, 4Ch, 24h, 28h
    db 51h, 89h, 44h, 24h, 2Ch, 8Bh, 45h, 00h, 68h, 8Ch, 0DAh, 0Eh, 01h, 8Bh, 0CDh, 0FFh
    db 90h, 90h, 00h, 00h, 00h, 8Bh, 16h, 8Bh, 0Ch, 0BAh, 8Bh, 01h, 55h, 0FFh, 50h, 0Ch
    db 8Bh, 44h, 24h, 28h, 47h, 3Bh, 0F8h, 7Ch, 0C7h, 8Bh, 4Ch, 24h, 14h, 5Fh, 5Eh, 5Dh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h
?d_003c3480@@YAXXZ ENDP

; ghidra: FUN_007c3760  retail @ 0x003C3760 size 191
public ?d_003c3760@@YAXXZ
?d_003c3760@@YAXXZ PROC
    db 51h, 57h, 8Bh, 0F9h, 8Bh, 4Fh, 28h, 85h, 0C9h, 0Fh, 84h, 0ADh, 00h, 00h, 00h, 56h
    db 8Dh, 47h, 30h, 50h, 0E8h, 94h, 87h, 0C6h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 0Fh, 84h, 98h
    db 00h, 00h, 00h, 8Bh, 56h, 58h, 8Bh, 46h, 64h, 55h, 0C6h, 44h, 24h, 0Ch, 01h, 0C6h
    db 44h, 24h, 0Dh, 00h, 8Bh, 4Ch, 24h, 0Ch, 51h, 2Bh, 56h, 54h, 2Bh, 46h, 60h, 0C1h
    db 0FAh, 02h, 0C1h, 0F8h, 02h, 03h, 0D0h, 8Dh, 0AFh, 84h, 00h, 00h, 00h, 52h, 8Bh, 0CDh
    db 0E8h, 19h, 62h, 0C6h, 0FFh, 8Bh, 45h, 00h, 8Bh, 0BFh, 88h, 00h, 00h, 00h, 3Bh, 0C7h
    db 0C6h, 44h, 24h, 0Ch, 01h, 0C6h, 44h, 24h, 0Dh, 00h, 5Dh, 74h, 0Fh, 66h, 8Bh, 4Ch
    db 24h, 08h, 66h, 89h, 08h, 83h, 0C0h, 02h, 3Bh, 0C7h, 75h, 0F6h, 0A1h, 98h, 08h, 2Fh
    db 01h, 85h, 0C0h, 74h, 36h, 8Bh, 0CEh, 0E8h, 45h, 0D5h, 0C7h, 0FFh, 8Bh, 0Dh, 98h, 08h
    db 2Fh, 01h, 50h, 0E8h, 0D0h, 0D7h, 0C4h, 0FFh, 8Bh, 0CEh, 0E8h, 0B7h, 11h, 0C5h, 0FFh, 50h
    db 8Bh, 0CEh, 0E8h, 17h, 0BBh, 0C7h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 0F6h, 0Ch, 0C6h, 0FFh, 8Bh
    db 0Dh, 98h, 08h, 2Fh, 01h, 50h, 0E8h, 4Eh, 0DDh, 0C3h, 0FFh, 5Eh, 5Fh, 59h, 0C3h
?d_003c3760@@YAXXZ ENDP

; ghidra: FUN_007c3ac0  retail @ 0x003C3AC0 size 17
public ?d_003c3ac0@@YAXXZ
?d_003c3ac0@@YAXXZ PROC
    db 8Bh, 41h, 6Ch, 8Bh, 51h, 68h, 83h, 0C1h, 68h, 50h, 52h, 0E8h, 6Dh, 9Bh, 0C5h, 0FFh
    db 0C3h
?d_003c3ac0@@YAXXZ ENDP

; ghidra: FUN_007c3ae0  retail @ 0x003C3AE0 size 85
public ?d_003c3ae0@@YAXXZ
?d_003c3ae0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 8Bh, 4Eh, 28h, 57h, 0E8h, 59h, 0A6h, 0C6h
    db 0FFh, 85h, 0C0h, 8Bh, 0CEh, 74h, 0Bh, 50h, 0E8h, 0F8h, 12h, 0C8h, 0FFh, 5Fh, 5Eh, 0C2h
    db 04h, 00h, 57h, 0E8h, 49h, 00h, 0C5h, 0FFh, 8Bh, 0F8h, 85h, 0FFh, 74h, 22h, 8Bh, 0Dh
    db 98h, 4Bh, 2Fh, 01h, 68h, 5Dh, 69h, 43h, 00h, 8Dh, 47h, 0Ch, 50h, 0E8h, 29h, 03h
    db 0C8h, 0FFh, 8Ah, 4Fh, 14h, 88h, 4Eh, 44h, 57h, 8Bh, 0CEh, 0E8h, 2Ah, 0D6h, 0C7h, 0FFh
    db 5Fh, 5Eh, 0C2h, 04h, 00h
?d_003c3ae0@@YAXXZ ENDP

; ghidra: FUN_007c3b50  retail @ 0x003C3B50 size 61
public ?d_003c3b50@@YAXXZ
?d_003c3b50@@YAXXZ PROC
    db 8Bh, 41h, 6Ch, 56h, 8Dh, 71h, 68h, 3Bh, 46h, 08h, 8Bh, 4Ch, 24h, 08h, 74h, 17h
    db 51h, 50h, 0E8h, 54h, 0A8h, 0C6h, 0FFh, 8Bh, 46h, 04h, 83h, 0C4h, 08h, 83h, 0C0h, 60h
    db 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 10h, 52h
    db 51h, 50h, 8Bh, 0CEh, 0E8h, 5Ah, 2Bh, 0C6h, 0FFh, 5Eh, 0C2h, 04h, 00h
?d_003c3b50@@YAXXZ ENDP

; ghidra: FUN_007c3ba0  retail @ 0x003C3BA0 size 395
public ?d_003c3ba0@@YAXXZ
?d_003c3ba0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0ACh, 0EEh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 6Ch, 8Bh, 51h, 68h, 53h, 55h, 8Bh, 0ACh, 24h
    db 84h, 00h, 00h, 00h, 56h, 8Dh, 71h, 68h, 8Bh, 4Eh, 04h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh
    db 0AAh, 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 04h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Bh, 55h
    db 00h, 89h, 44h, 24h, 0Ch, 57h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CDh, 0FFh, 52h, 78h
    db 8Bh, 55h, 00h, 8Bh, 0CDh, 0FFh, 52h, 04h, 84h, 0C0h, 0Fh, 84h, 0EDh, 00h, 00h, 00h
    db 8Bh, 46h, 04h, 8Bh, 0Eh, 50h, 51h, 8Bh, 0CEh, 0E8h, 2Fh, 9Ah, 0C5h, 0FFh, 8Bh, 44h
    db 24h, 10h, 33h, 0FFh, 85h, 0C0h, 0Fh, 8Eh, 0FAh, 00h, 00h, 00h, 8Dh, 44h, 24h, 60h
    db 89h, 84h, 24h, 8Ch, 00h, 00h, 00h, 0BBh, 01h, 00h, 00h, 00h, 8Dh, 64h, 24h, 00h
    db 8Dh, 4Ch, 24h, 1Ch, 0E8h, 0FCh, 0E5h, 0C7h, 0FFh, 55h, 8Dh, 4Ch, 24h, 20h, 0C7h, 84h
    db 24h, 88h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 8Dh, 1Ch, 0C8h, 0FFh, 8Bh, 46h
    db 04h, 3Bh, 46h, 08h, 74h, 25h, 89h, 44h, 24h, 14h, 89h, 44h, 24h, 18h, 85h, 0C0h
    db 88h, 9Ch, 24h, 84h, 00h, 00h, 00h, 74h, 0Ch, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0C8h
    db 0E8h, 0EAh, 47h, 0C8h, 0FFh, 83h, 46h, 04h, 60h, 0EBh, 17h, 53h, 53h, 8Dh, 94h, 24h
    db 94h, 00h, 00h, 00h, 52h, 8Dh, 4Ch, 24h, 28h, 51h, 50h, 8Bh, 0CEh, 0E8h, 51h, 2Ah
    db 0C6h, 0FFh, 8Dh, 4Ch, 24h, 78h, 0C7h, 84h, 24h, 84h, 00h, 00h, 00h, 03h, 00h, 00h
    db 00h, 0E8h, 9Ah, 3Ch, 4Ch, 00h, 8Dh, 4Ch, 24h, 74h, 0C6h, 84h, 24h, 84h, 00h, 00h
    db 00h, 02h, 0E8h, 19h, 45h, 4Ch, 00h, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 84h, 24h, 84h, 00h
    db 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 75h, 3Ch, 4Ch, 00h, 8Bh, 44h, 24h, 10h, 47h
    db 3Bh, 0F8h, 0Fh, 8Ch, 58h, 0FFh, 0FFh, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 8Bh, 4Ch, 24h, 6Ch
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 78h, 0C2h, 04h, 00h, 8Bh, 44h, 24h
    db 10h, 33h, 0DBh, 85h, 0C0h, 7Eh, 1Fh, 33h, 0FFh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Eh, 55h, 03h, 0CFh, 0E8h, 0D1h, 1Bh, 0C8h, 0FFh, 8Bh, 44h, 24h, 10h, 43h, 83h
    db 0C7h, 60h, 3Bh, 0D8h, 7Ch, 0EAh, 8Bh, 4Ch, 24h, 7Ch, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 78h, 0C2h, 04h, 00h
?d_003c3ba0@@YAXXZ ENDP

; ghidra: FUN_007c3d90  retail @ 0x003C3D90 size 342
public ?d_003c3d90@@YAXXZ
?d_003c3d90@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 06h, 57h, 8Bh, 0F9h, 8Dh
    db 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 18h, 01h, 0C6h, 44h, 24h, 19h, 03h
    db 0FFh, 50h, 28h, 56h, 8Bh, 0CFh, 0E8h, 1Dh, 0EAh, 0C4h, 0FFh, 8Bh, 57h, 10h, 8Bh, 6Fh
    db 0Ch, 8Bh, 06h, 2Bh, 0D5h, 8Dh, 4Ch, 24h, 1Ch, 0C1h, 0FAh, 02h, 51h, 8Bh, 0CEh, 89h
    db 54h, 24h, 20h, 0FFh, 50h, 78h, 8Bh, 44h, 24h, 1Ch, 33h, 0DBh, 85h, 0C0h, 7Eh, 15h
    db 8Bh, 57h, 0Ch, 8Bh, 0Ch, 9Ah, 8Bh, 01h, 56h, 0FFh, 50h, 0Ch, 8Bh, 44h, 24h, 1Ch
    db 43h, 3Bh, 0D8h, 7Ch, 0EBh, 8Bh, 4Fh, 3Ch, 8Bh, 5Fh, 38h, 8Bh, 16h, 2Bh, 0CBh, 0C1h
    db 0F9h, 02h, 8Dh, 44h, 24h, 10h, 89h, 4Ch, 24h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h
    db 8Bh, 44h, 24h, 10h, 33h, 0EDh, 85h, 0C0h, 7Eh, 4Ch, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 38h, 8Bh, 1Ch, 0A9h, 8Bh, 16h, 53h, 8Bh, 0CEh, 0FFh, 52h, 50h, 8Bh, 06h
    db 8Dh, 4Bh, 08h, 51h, 8Bh, 0CEh, 0FFh, 50h, 78h, 8Bh, 16h, 8Dh, 43h, 0Ch, 50h, 8Bh
    db 0CEh, 0FFh, 52h, 68h, 8Bh, 16h, 8Dh, 43h, 10h, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh
    db 16h, 83h, 0C3h, 14h, 53h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h, 00h, 8Bh, 44h, 24h
    db 10h, 45h, 3Bh, 0E8h, 7Ch, 0BAh, 8Dh, 47h, 50h, 50h, 56h, 8Bh, 0CFh, 0E8h, 5Eh, 0EAh
    db 0C6h, 0FFh, 8Dh, 4Fh, 5Ch, 51h, 56h, 8Bh, 0CFh, 0E8h, 52h, 0EAh, 0C6h, 0FFh, 56h, 8Bh
    db 0CFh, 0E8h, 42h, 16h, 0C6h, 0FFh, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h, 74h
    db 2Bh, 8Bh, 87h, 88h, 00h, 00h, 00h, 8Bh, 97h, 84h, 00h, 00h, 00h, 8Bh, 0C8h, 2Bh
    db 0C8h, 0D1h, 0F9h, 85h, 0C9h, 7Eh, 0Fh, 66h, 8Bh, 18h, 66h, 89h, 1Ah, 83h, 0C0h, 02h
    db 83h, 0C2h, 02h, 49h, 75h, 0F1h, 89h, 97h, 88h, 00h, 00h, 00h, 8Dh, 87h, 84h, 00h
    db 00h, 00h, 50h, 56h, 0E8h, 36h, 0A3h, 0C5h, 0FFh, 8Ah, 44h, 24h, 1Dh, 83h, 0C4h, 08h
    db 3Ch, 02h, 72h, 08h, 56h, 8Bh, 0CFh, 0E8h, 35h, 2Dh, 0C5h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh
    db 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_003c3d90@@YAXXZ ENDP

; ghidra: FUN_007c3f40  retail @ 0x003C3F40 size 431
_TEXT ENDS
_TEXT$d007c3f40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007C3F40 size 431
public ?d_003c3f40@@YAXXZ
?d_003c3f40@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va0101EED8
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 060h, 055h, 056h, 08Bh, 0F1h, 08Bh
    db 086h, 0D4h, 000h, 000h, 000h, 057h, 050h, 0FFh, 015h
    dd __imp__free
    db 08Dh, 0AEh, 0D8h, 000h, 000h, 000h, 068h
    dd g_Va010EDC1C
    db 0C7h, 086h, 0D4h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0C7h, 045h, 000h, 000h, 000h, 000h
    db 000h
    call ?bfmeMake_009CB5F0@@YAPAVBfmeMade_009CB5F0@@PAX@Z
    db 08Bh, 0F8h, 083h, 0C4h, 008h, 085h, 0FFh, 00Fh, 084h, 045h, 001h, 000h, 000h, 08Dh, 04Ch, 024h
    db 02Ch
    call ??0Gen_009D83D0@@QAE@XZ
    db 06Ah, 000h, 06Ah, 000h, 057h, 08Dh, 04Ch, 024h, 038h, 0C7h, 084h, 024h, 080h, 000h, 000h, 000h
    db 000h, 000h, 000h, 000h
    call ?bfmeTryActivate@Gen009D6300@@QAE_NPAVBfmeActivationStream@@H_N@Z
    db 08Dh, 04Ch, 024h, 02Ch, 051h, 08Bh, 0CEh
    call ?j_0000a87b@@YAXXZ
    db 08Bh, 00Dh
    dd ?Campaign00598950@@3PAXA
    db 08Bh, 051h, 008h, 083h, 0C1h, 008h, 08Dh, 044h, 024h, 02Ch, 050h, 0FFh, 052h, 00Ch, 08Bh, 04Eh
    db 028h, 08Bh, 011h, 08Dh, 044h, 024h, 02Ch, 050h, 0FFh, 052h, 00Ch, 08Dh, 04Ch, 024h, 02Ch, 051h
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    call ?j_0002615c@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheBfmeGlobal012F706C@@3PAVBfmeGlobal012F706C@@A
    db 08Bh, 051h, 008h, 083h, 0C1h, 008h, 08Dh, 044h, 024h, 02Ch, 050h, 0FFh, 052h, 00Ch, 08Bh, 054h
    db 024h, 02Ch, 08Dh, 04Ch, 024h, 00Ch, 051h, 08Dh, 04Ch, 024h, 030h, 0C6h, 044h, 024h, 010h, 001h
    db 0C6h, 044h, 024h, 011h, 002h, 0FFh, 052h, 028h, 08Bh, 00Dh
    dd ?Glo012F7048@@3PAVGlo012F7048CampaignGateMode@@A
    db 08Dh, 054h, 024h, 014h, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 018h
    db 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 08Bh, 001h, 052h, 0FFh
    db 050h, 044h, 08Bh, 046h, 034h, 050h, 08Bh, 0CEh
    call ?j_00020379@@YAXXZ
    db 085h, 0C0h, 074h, 02Ah, 08Bh, 048h, 00Ch, 08Bh, 050h, 010h, 08Bh, 0C1h, 089h, 04Ch, 024h, 020h
    db 08Bh, 0CAh, 089h, 054h, 024h, 024h, 0C7h, 044h, 024h, 028h, 000h, 000h, 000h, 000h, 08Bh, 054h
    db 024h, 028h, 089h, 044h, 024h, 014h, 089h, 04Ch, 024h, 018h, 089h, 054h, 024h, 01Ch, 08Bh, 054h
    db 024h, 02Ch, 08Dh, 044h, 024h, 014h, 050h, 08Dh, 04Ch, 024h, 030h, 0FFh, 052h, 060h, 08Bh, 00Dh
    dd ?Glo012F7048@@3PAVGlo012F7048CampaignGateMode@@A
    db 08Bh, 001h, 0FFh, 050h, 03Ch, 0D9h, 05Ch, 024h, 010h, 08Bh, 054h, 024h, 02Ch, 08Dh, 04Ch, 024h
    db 010h, 051h, 08Dh, 04Ch, 024h, 030h, 0FFh, 052h, 06Ch, 055h, 08Bh, 0CFh
    call ?bfmeTakeEC@BfmeThingEC@@QAEHPAH@Z
    db 08Dh, 04Ch, 024h, 02Ch, 089h, 086h, 0D4h, 000h, 000h, 000h
    call ?bfmeClose@Gen009D6DD0@@QAEXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C7h, 044h, 024h, 074h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1Gen_009D83D0@@UAE@XZ
    db 08Bh, 04Ch, 024h, 06Ch, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h
    db 06Ch, 0C3h
?d_003c3f40@@YAXXZ ENDP
_TEXT$d007c3f40 ENDS
_TEXT SEGMENT

; ghidra: FUN_007c4160  retail @ 0x003C4160 size 647
public ?d_003c4160@@YAXXZ
?d_003c4160@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 0EEh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 14h, 53h, 55h, 56h, 8Bh, 74h, 24h, 30h, 8Bh
    db 06h, 8Bh, 0E9h, 57h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CEh, 89h, 6Ch, 24h, 24h, 0C6h
    db 44h, 24h, 14h, 01h, 0C6h, 44h, 24h, 15h, 03h, 0FFh, 50h, 28h, 8Bh, 55h, 00h, 8Bh
    db 0CDh, 0FFh, 52h, 04h, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 0E8h, 0CFh, 1Fh, 0C7h, 0FFh, 56h
    db 8Bh, 0CDh, 0E8h, 21h, 0E6h, 0C4h, 0FFh, 8Bh, 06h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh
    db 0FFh, 50h, 78h, 8Bh, 44h, 24h, 14h, 33h, 0FFh, 3Bh, 0C7h, 89h, 7Ch, 24h, 34h, 0Fh
    db 8Eh, 98h, 00h, 00h, 00h, 8Dh, 5Dh, 0Ch, 6Ah, 54h, 0E8h, 51h, 0DDh, 4Bh, 00h, 83h
    db 0C4h, 04h, 89h, 44h, 24h, 1Ch, 3Bh, 0C7h, 89h, 7Ch, 24h, 2Ch, 74h, 09h, 8Bh, 0C8h
    db 0E8h, 0E6h, 71h, 0C7h, 0FFh, 8Bh, 0F8h, 8Bh, 17h, 56h, 8Bh, 0CFh, 0C7h, 44h, 24h, 30h
    db 0FFh, 0FFh, 0FFh, 0FFh, 89h, 7Ch, 24h, 20h, 0FFh, 52h, 0Ch, 8Dh, 47h, 08h, 50h, 8Bh
    db 0CFh, 0E8h, 55h, 0C1h, 0C4h, 0FFh, 6Ah, 01h, 8Bh, 0CFh, 0E8h, 0EAh, 0C2h, 0C5h, 0FFh, 8Bh
    db 43h, 04h, 3Bh, 43h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 38h, 83h, 43h, 04h
    db 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 3Ch, 51h, 8Dh, 54h, 24h, 28h
    db 52h, 50h, 8Bh, 0CBh, 0E8h, 0BFh, 11h, 0C8h, 0FFh, 33h, 0C0h, 8Ah, 47h, 1Eh, 8Bh, 0CFh
    db 50h, 0E8h, 35h, 26h, 0C7h, 0FFh, 8Bh, 44h, 24h, 34h, 8Bh, 4Ch, 24h, 14h, 40h, 33h
    db 0FFh, 3Bh, 0C1h, 89h, 44h, 24h, 34h, 0Fh, 8Ch, 6Bh, 0FFh, 0FFh, 0FFh, 8Bh, 16h, 8Dh
    db 44h, 24h, 18h, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 39h, 7Ch, 24h, 18h, 89h, 7Ch, 24h
    db 34h, 0Fh, 8Eh, 0B1h, 00h, 00h, 00h, 8Dh, 5Dh, 38h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 6Ah, 18h, 0E8h, 99h, 0DCh, 4Bh, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 08h, 89h, 78h
    db 0Ch, 89h, 78h, 10h, 8Bh, 0F8h, 8Bh, 16h, 57h, 8Bh, 0CEh, 89h, 7Ch, 24h, 20h, 0FFh
    db 52h, 50h, 8Bh, 06h, 8Dh, 6Fh, 08h, 55h, 8Bh, 0CEh, 0FFh, 50h, 78h, 8Bh, 16h, 8Dh
    db 47h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 68h, 8Bh, 16h, 8Dh, 47h, 10h, 50h, 8Bh, 0CEh
    db 0FFh, 52h, 68h, 8Bh, 16h, 8Dh, 47h, 14h, 50h, 8Bh, 0CEh, 0FFh, 92h, 8Ch, 00h, 00h
    db 00h, 8Bh, 43h, 04h, 3Bh, 43h, 08h, 74h, 0Ch, 85h, 0C0h, 74h, 02h, 89h, 38h, 83h
    db 43h, 04h, 04h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 3Ch, 51h, 8Dh, 54h
    db 24h, 28h, 52h, 50h, 8Bh, 0CBh, 0E8h, 0B7h, 0Eh, 0C5h, 0FFh, 8Bh, 45h, 00h, 8Bh, 0Dh
    db 6Ch, 70h, 2Fh, 01h, 6Ah, 01h, 57h, 50h, 0E8h, 0E5h, 9Bh, 0C5h, 0FFh, 8Bh, 44h, 24h
    db 34h, 8Bh, 4Ch, 24h, 18h, 40h, 33h, 0FFh, 3Bh, 0C1h, 89h, 44h, 24h, 34h, 0Fh, 8Ch
    db 5Ch, 0FFh, 0FFh, 0FFh, 8Bh, 6Ch, 24h, 20h, 8Dh, 4Dh, 50h, 51h, 56h, 8Bh, 0CDh, 0E8h
    db 8Ch, 0E5h, 0C6h, 0FFh, 8Dh, 55h, 5Ch, 52h, 56h, 8Bh, 0CDh, 0E8h, 80h, 0E5h, 0C6h, 0FFh
    db 56h, 8Bh, 0CDh, 0E8h, 70h, 11h, 0C6h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 04h, 84h
    db 0C0h, 74h, 32h, 8Bh, 85h, 88h, 00h, 00h, 00h, 8Bh, 95h, 84h, 00h, 00h, 00h, 8Bh
    db 0C8h, 2Bh, 0C8h, 0D1h, 0F9h, 3Bh, 0CFh, 7Eh, 16h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 66h, 8Bh, 38h, 66h, 89h, 3Ah, 83h, 0C0h, 02h, 83h, 0C2h, 02h, 49h, 75h, 0F1h, 89h
    db 95h, 88h, 00h, 00h, 00h, 8Dh, 8Dh, 84h, 00h, 00h, 00h, 51h, 56h, 0E8h, 5Dh, 9Eh
    db 0C5h, 0FFh, 8Ah, 44h, 24h, 19h, 83h, 0C4h, 08h, 3Ch, 02h, 72h, 22h, 56h, 8Bh, 0CDh
    db 0E8h, 5Ch, 28h, 0C5h, 0FFh, 0Fh, 0B6h, 44h, 24h, 11h, 5Fh, 5Eh, 5Dh, 5Bh, 8Bh, 4Ch
    db 24h, 14h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 20h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 24h, 5Fh, 5Eh, 5Dh, 0Fh, 0B6h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 20h, 0C2h, 04h, 00h
?d_003c4160@@YAXXZ ENDP

; ghidra: FUN_007c4740  retail @ 0x003C4740 size 329
public ?d_003c4740@@YAXXZ
?d_003c4740@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 18h, 0EFh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 56h, 57h, 8Bh, 0F9h, 8Bh, 47h, 34h, 33h
    db 0F6h, 3Bh, 0C6h, 0Fh, 84h, 0Fh, 01h, 00h, 00h, 8Bh, 47h, 28h, 53h, 8Bh, 58h, 08h
    db 3Bh, 0DEh, 0Fh, 84h, 0FFh, 00h, 00h, 00h, 55h, 0E8h, 0E9h, 9Bh, 0C5h, 0FFh, 8Bh, 4Fh
    db 34h, 51h, 8Bh, 0CFh, 0E8h, 0F0h, 0BBh, 0C5h, 0FFh, 8Bh, 0E8h, 8Bh, 0CDh, 0E8h, 0E3h, 0EAh
    db 0C7h, 0FFh, 85h, 0C0h, 75h, 1Ch, 53h, 55h, 8Bh, 0CFh, 0E8h, 27h, 20h, 0C4h, 0FFh, 5Dh
    db 5Bh, 5Fh, 5Eh, 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h
    db 1Ch, 0C3h, 89h, 74h, 24h, 14h, 89h, 74h, 24h, 18h, 89h, 74h, 24h, 1Ch, 8Bh, 83h
    db 0ECh, 00h, 00h, 00h, 8Ah, 50h, 18h, 0C6h, 40h, 18h, 01h, 56h, 8Dh, 44h, 24h, 18h
    db 50h, 53h, 8Bh, 0CDh, 89h, 74h, 24h, 34h, 88h, 54h, 24h, 1Fh, 0E8h, 94h, 0EAh, 0C7h
    db 0FFh, 8Bh, 4Fh, 28h, 50h, 0E8h, 61h, 9Dh, 0C6h, 0FFh, 84h, 0C0h, 74h, 6Ah, 8Bh, 0CDh
    db 0E8h, 80h, 0EAh, 0C7h, 0FFh, 3Bh, 0C3h, 75h, 0Bh, 53h, 55h, 8Bh, 0CFh, 0E8h, 0C4h, 1Fh
    db 0C4h, 0FFh, 0EBh, 54h, 8Bh, 54h, 24h, 18h, 8Bh, 4Ch, 24h, 14h, 2Bh, 0D1h, 0BEh, 01h
    db 00h, 00h, 00h, 0C1h, 0FAh, 02h, 3Bh, 0D6h, 76h, 39h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Dh, 04h, 0B1h, 8Bh, 4Fh, 28h, 50h, 0E8h, 0E1h, 76h, 0C6h, 0FFh, 50h, 55h, 8Bh, 0CFh
    db 0E8h, 91h, 1Fh, 0C4h, 0FFh, 8Bh, 4Ch, 24h, 14h, 8Dh, 0Ch, 0B1h, 0E8h, 0FFh, 30h, 4Ch
    db 00h, 8Bh, 54h, 24h, 18h, 8Bh, 4Ch, 24h, 14h, 2Bh, 0D1h, 46h, 0C1h, 0FAh, 02h, 3Bh
    db 0F2h, 72h, 0CDh, 0E8h, 0E8h, 30h, 4Ch, 00h, 8Bh, 9Bh, 0ECh, 00h, 00h, 00h, 8Ah, 44h
    db 24h, 13h, 8Dh, 4Ch, 24h, 14h, 88h, 43h, 18h, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh, 0FFh
    db 0FFh, 0E8h, 3Ch, 22h, 0C6h, 0FFh, 5Dh, 5Bh, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_003c4740@@YAXXZ ENDP

; ghidra: FUN_007c48e0  retail @ 0x003C48E0 size 421
public ?d_003c48e0@@YAXXZ
?d_003c48e0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 38h, 0EFh, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 38h, 53h, 56h, 8Bh, 0F1h, 8Bh, 8Eh, 0D4h, 00h
    db 00h, 00h, 85h, 0C9h, 57h, 0Fh, 84h, 68h, 01h, 00h, 00h, 8Bh, 86h, 0D8h, 00h, 00h
    db 00h, 85h, 0C0h, 0Fh, 84h, 5Ah, 01h, 00h, 00h, 50h, 51h, 0E8h, 50h, 6Bh, 60h, 00h
    db 8Bh, 0F8h, 83h, 0C4h, 08h, 85h, 0FFh, 0Fh, 84h, 46h, 01h, 00h, 00h, 6Ah, 00h, 6Ah
    db 00h, 6Ah, 00h, 8Dh, 4Ch, 24h, 30h, 0E8h, 64h, 43h, 61h, 00h, 8Dh, 44h, 24h, 10h
    db 50h, 57h, 8Dh, 4Ch, 24h, 2Ch, 0C7h, 44h, 24h, 54h, 00h, 00h, 00h, 00h, 0E8h, 8Dh
    db 40h, 61h, 00h, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0CEh, 0E8h, 55h, 0Ah, 0C7h, 0FFh, 8Bh
    db 0Dh, 24h, 10h, 2Fh, 01h, 8Bh, 51h, 08h, 8Bh, 0D8h, 83h, 0C1h, 08h, 8Dh, 44h, 24h
    db 24h, 50h, 0FFh, 52h, 0Ch, 8Bh, 4Eh, 28h, 8Bh, 11h, 8Dh, 44h, 24h, 24h, 50h, 0FFh
    db 52h, 0Ch, 8Dh, 4Ch, 24h, 24h, 51h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 0E8h, 0CAh, 17h
    db 0C6h, 0FFh, 8Bh, 0Dh, 6Ch, 70h, 2Fh, 01h, 8Bh, 51h, 08h, 83h, 0C1h, 08h, 8Dh, 44h
    db 24h, 24h, 50h, 0FFh, 52h, 0Ch, 83h, 0FBh, 03h, 0Fh, 8Ch, 8Ah, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 24h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Dh, 4Ch, 24h, 28h, 0C6h, 44h, 24h, 10h
    db 01h, 0C6h, 44h, 24h, 11h, 02h, 0FFh, 52h, 28h, 0Fh, 0B6h, 44h, 24h, 0Dh, 83h, 0F8h
    db 02h, 7Ch, 66h, 8Bh, 54h, 24h, 24h, 8Dh, 44h, 24h, 18h, 50h, 8Dh, 4Ch, 24h, 28h
    db 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h
    db 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0FFh, 52h, 60h, 8Bh, 54h, 24h, 24h, 8Dh
    db 44h, 24h, 0Ch, 50h, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h
    db 0FFh, 52h, 6Ch, 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 18h, 50h, 83h, 0ECh, 08h, 8Bh
    db 0C4h, 89h, 08h, 8Bh, 54h, 24h, 28h, 89h, 50h, 04h, 8Bh, 0Dh, 48h, 70h, 2Fh, 01h
    db 89h, 64h, 24h, 20h, 0E8h, 0BFh, 2Eh, 0C7h, 0FFh, 8Dh, 4Ch, 24h, 24h, 0E8h, 5Eh, 40h
    db 61h, 00h, 8Bh, 07h, 6Ah, 01h, 8Bh, 0CFh, 0FFh, 10h, 8Bh, 4Eh, 28h, 8Bh, 11h, 0FFh
    db 52h, 04h, 8Bh, 4Eh, 28h, 0E8h, 0BCh, 0B5h, 0C7h, 0FFh, 8Bh, 4Eh, 28h, 0E8h, 27h, 94h
    db 0C6h, 0FFh, 8Dh, 4Ch, 24h, 24h, 0C7h, 44h, 24h, 4Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 8Dh
    db 42h, 61h, 00h, 8Bh, 4Ch, 24h, 44h, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 5Bh, 83h, 0C4h, 44h, 0C3h
?d_003c48e0@@YAXXZ ENDP

; ghidra: FUN_007c4cb0  retail @ 0x003C4CB0 size 42
public ?d_003c4cb0@@YAXXZ
?d_003c4cb0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 44h, 24h, 0Ch, 0D9h, 40h, 14h, 0D9h, 40h, 10h, 0D8h, 61h, 10h
    db 0D9h, 1Ch, 24h, 0D8h, 61h, 14h, 0D9h, 0C0h, 0DEh, 0C9h, 0D9h, 04h, 24h, 0D8h, 0Ch, 24h
    db 0DEh, 0C1h, 0D9h, 0FAh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_003c4cb0@@YAXXZ ENDP

; ghidra: FUN_007c4ff0  retail @ 0x003C4FF0 size 99
public ?d_003c4ff0@@YAXXZ
?d_003c4ff0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 4Eh, 04h, 57h, 8Bh, 3Eh, 8Bh, 0D1h, 2Bh, 0D7h, 0C1h
    db 0FAh, 02h, 33h, 0C0h, 85h, 0D2h, 76h, 46h, 53h, 8Bh, 5Ch, 24h, 14h, 8Bh, 0D7h, 55h
    db 3Bh, 1Ah, 74h, 17h, 8Bh, 6Eh, 04h, 2Bh, 2Eh, 40h, 0C1h, 0FDh, 02h, 83h, 0C2h, 04h
    db 3Bh, 0C5h, 72h, 0ECh, 5Dh, 5Bh, 5Fh, 5Eh, 0C2h, 08h, 00h, 83h, 0F8h, 0FFh, 74h, 1Ch
    db 8Dh, 14h, 87h, 8Dh, 42h, 04h, 3Bh, 0C8h, 74h, 0Eh, 2Bh, 0C8h, 51h, 50h, 52h, 0FFh
    db 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 83h, 46h, 04h, 0FCh, 5Dh, 5Bh, 5Fh, 5Eh
    db 0C2h, 08h, 00h
?d_003c4ff0@@YAXXZ ENDP

; ghidra: FUN_007c5160  retail @ 0x003C5160 size 217
public ?d_003c5160@@YAXXZ
?d_003c5160@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 63h, 0EFh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Bh, 4Eh, 20h
    db 85h, 0C9h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 74h, 27h, 8Bh, 46h, 28h, 2Bh
    db 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h
    db 0Ch, 0CDh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 40h, 94h, 46h, 00h
    db 83h, 0C4h, 08h, 8Bh, 4Eh, 14h, 85h, 0C9h, 0C6h, 44h, 24h, 10h, 00h, 74h, 27h, 8Bh
    db 46h, 1Ch, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h
    db 0Bh, 51h, 0E8h, 0D9h, 0CCh, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0Dh
    db 94h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 0Eh, 85h, 0C9h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh
    db 0FFh, 0FFh, 74h, 35h, 8Bh, 46h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh
    db 80h, 00h, 00h, 00h, 76h, 19h, 51h, 0E8h, 0A4h, 0CCh, 4Bh, 00h, 83h, 0C4h, 04h, 5Eh
    db 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h
    db 51h, 0E8h, 0CAh, 93h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_003c5160@@YAXXZ ENDP

; ghidra: FUN_007c5270  retail @ 0x003C5270 size 181
_TEXT ENDS
_TEXT$d007c5270 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007C5270 size 181
public ?d_003c5270@@YAXXZ
?d_003c5270@@YAXXZ PROC
    db 051h, 08Bh, 054h, 024h, 008h, 08Bh, 00Ah, 08Bh, 042h, 004h, 053h, 02Bh, 0C1h, 055h, 0C1h, 0F8h
    db 002h, 085h, 0C0h, 056h, 057h, 0C7h, 044h, 024h, 010h, 000h, 000h, 000h, 000h, 076h, 07Fh, 08Bh
    db 054h, 024h, 01Ch, 08Bh, 032h, 089h, 074h, 024h, 01Ch, 089h, 04Ch, 024h, 018h, 0EBh, 004h, 08Bh
    db 074h, 024h, 01Ch, 08Bh, 04Ch, 024h, 018h, 08Bh, 009h, 08Bh, 009h, 085h, 0C9h, 074h, 006h, 00Fh
    db 0B7h, 069h, 004h, 0EBh, 002h, 033h, 0EDh, 085h, 0C9h, 08Dh, 079h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 085h, 0F6h, 074h, 009h, 00Fh, 0B7h, 05Eh, 004h, 083h, 0C6h, 008h, 0EBh, 007h, 033h, 0DBh, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0DDh, 08Bh, 0CBh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0D2h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0D2h
    db 083h, 0DAh, 0FFh, 085h, 0D2h, 075h, 008h, 02Bh, 0DDh, 08Bh, 0D3h, 085h, 0D2h, 074h, 023h, 08Bh
    db 04Ch, 024h, 010h, 08Bh, 074h, 024h, 018h, 041h, 083h, 0C6h, 004h, 03Bh, 0C8h, 089h, 04Ch, 024h
    db 010h, 089h, 074h, 024h, 018h, 072h, 091h, 05Fh, 05Eh, 05Dh, 083h, 0C8h, 0FFh, 05Bh, 059h, 0C2h
    db 008h, 000h, 08Bh, 044h, 024h, 010h, 05Fh, 05Eh, 05Dh, 05Bh, 059h, 0C2h, 008h, 000h
?d_003c5270@@YAXXZ ENDP
_TEXT$d007c5270 ENDS
_TEXT SEGMENT

; ghidra: FUN_007c5360  retail @ 0x003C5360 size 204
public ?d_003c5360@@YAXXZ
?d_003c5360@@YAXXZ PROC
    db 83h, 0ECh, 08h, 8Bh, 44h, 24h, 0Ch, 8Bh, 08h, 53h, 55h, 8Bh, 68h, 04h, 2Bh, 0E9h
    db 0C1h, 0FDh, 02h, 85h, 0EDh, 56h, 57h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h
    db 4Ch, 24h, 14h, 0Fh, 86h, 82h, 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 30h, 89h
    db 74h, 24h, 20h, 89h, 4Ch, 24h, 1Ch, 0EBh, 07h, 8Bh, 74h, 24h, 20h, 8Dh, 49h, 00h
    db 8Bh, 4Ch, 24h, 1Ch, 8Bh, 01h, 8Bh, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 58h, 04h
    db 0EBh, 02h, 33h, 0DBh, 85h, 0C0h, 8Dh, 78h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h
    db 85h, 0F6h, 74h, 09h, 0Fh, 0B7h, 56h, 04h, 83h, 0C6h, 08h, 0EBh, 07h, 33h, 0D2h, 0BEh
    db 8Bh, 38h, 07h, 01h, 3Bh, 0D3h, 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h
    db 74h, 05h, 1Bh, 0C0h, 83h, 0D8h, 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h
    db 0C0h, 74h, 24h, 8Bh, 44h, 24h, 10h, 8Bh, 54h, 24h, 1Ch, 40h, 83h, 0C2h, 04h, 3Bh
    db 0C5h, 89h, 44h, 24h, 10h, 89h, 54h, 24h, 1Ch, 72h, 8Eh, 5Fh, 5Eh, 5Dh, 33h, 0C0h
    db 5Bh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 8Bh, 54h, 24h, 14h, 8Bh, 44h, 24h, 10h, 8Bh
    db 04h, 82h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_003c5360@@YAXXZ ENDP

; ghidra: FUN_007c55f0  retail @ 0x003C55F0 size 148
public ?d_003c55f0@@YAXXZ
?d_003c55f0@@YAXXZ PROC
    db 33h, 0C0h, 53h, 8Bh, 1Dh, 5Ch, 94h, 35h, 01h, 56h, 8Bh, 0F1h, 89h, 06h, 89h, 46h
    db 04h, 89h, 46h, 08h, 89h, 46h, 0Ch, 89h, 46h, 10h, 89h, 46h, 14h, 89h, 46h, 18h
    db 89h, 46h, 1Ch, 89h, 46h, 20h, 89h, 46h, 24h, 89h, 46h, 28h, 8Bh, 46h, 04h, 3Bh
    db 0C0h, 8Bh, 0Eh, 57h, 75h, 04h, 8Bh, 0C1h, 0EBh, 0Eh, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h
    db 51h, 0FFh, 0D3h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 04h, 8Bh, 46h, 18h, 3Bh, 0C0h
    db 8Bh, 4Eh, 14h, 75h, 04h, 8Bh, 0C1h, 0EBh, 0Eh, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h
    db 0FFh, 0D3h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 18h, 8Bh, 46h, 24h, 3Bh, 0C0h, 8Bh
    db 4Eh, 20h, 75h, 09h, 5Fh, 89h, 4Eh, 24h, 8Bh, 0C6h, 5Eh, 5Bh, 0C3h, 8Bh, 0F8h, 2Bh
    db 0F8h, 57h, 50h, 51h, 0FFh, 0D3h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 24h, 5Fh, 8Bh
    db 0C6h, 5Eh, 5Bh, 0C3h
?d_003c55f0@@YAXXZ ENDP

; ghidra: FUN_007c56f0  retail @ 0x003C56F0 size 168
public ?d_003c56f0@@YAXXZ
?d_003c56f0@@YAXXZ PROC
    db 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 2Eh, 8Bh, 46h, 04h, 8Bh, 4Eh, 08h, 57h, 8Bh, 7Ch
    db 24h, 14h, 8Bh, 0DFh, 2Bh, 0DDh, 0C1h, 0FBh, 02h, 3Bh, 0C1h, 74h, 69h, 3Bh, 0F8h, 75h
    db 21h, 85h, 0C0h, 74h, 08h, 8Bh, 4Ch, 24h, 18h, 8Bh, 11h, 89h, 10h, 8Bh, 46h, 04h
    db 8Bh, 16h, 83h, 0C0h, 04h, 5Fh, 89h, 46h, 04h, 5Eh, 5Dh, 8Dh, 04h, 9Ah, 5Bh, 0C2h
    db 08h, 00h, 85h, 0C0h, 74h, 05h, 8Bh, 48h, 0FCh, 89h, 08h, 8Bh, 6Eh, 04h, 8Bh, 54h
    db 24h, 18h, 83h, 0C5h, 04h, 8Bh, 0CDh, 8Bh, 0C5h, 2Bh, 0C7h, 83h, 0E8h, 08h, 85h, 0C0h
    db 89h, 6Eh, 04h, 8Bh, 2Ah, 7Eh, 11h, 50h, 2Bh, 0C8h, 83h, 0E9h, 04h, 57h, 51h, 0FFh
    db 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 89h, 2Fh, 8Bh, 16h, 5Fh, 5Eh, 5Dh, 8Dh
    db 04h, 9Ah, 5Bh, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h, 18h, 6Ah, 00h, 6Ah, 01h, 8Dh, 44h
    db 24h, 20h, 50h, 51h, 57h, 8Bh, 0CEh, 0E8h, 4Bh, 0A9h, 0C4h, 0FFh, 8Bh, 16h, 5Fh, 5Eh
    db 5Dh, 8Dh, 04h, 9Ah, 5Bh, 0C2h, 08h, 00h
?d_003c56f0@@YAXXZ ENDP

; ghidra: FUN_007c5820  retail @ 0x003C5820 size 83
public ?d_003c5820@@YAXXZ
?d_003c5820@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 0F1h, 50h, 56h, 0E8h, 0EFh, 0A1h, 0C6h, 0FFh, 83h, 0F8h
    db 0FFh, 74h, 3Ch, 8Bh, 0Eh, 8Bh, 14h, 81h, 8Bh, 4Ch, 24h, 08h, 8Bh, 41h, 08h, 8Bh
    db 71h, 0Ch, 83h, 0C1h, 04h, 3Bh, 0C6h, 89h, 54h, 24h, 0Ch, 74h, 0Eh, 85h, 0C0h, 74h
    db 02h, 89h, 10h, 83h, 41h, 04h, 04h, 5Eh, 0C2h, 08h, 00h, 6Ah, 01h, 6Ah, 01h, 8Dh
    db 54h, 24h, 14h, 52h, 8Dh, 54h, 24h, 18h, 52h, 50h, 0E8h, 68h, 0A8h, 0C4h, 0FFh, 5Eh
    db 0C2h, 08h, 00h
?d_003c5820@@YAXXZ ENDP

; ghidra: FUN_007c5890  retail @ 0x003C5890 size 52
public ?d_003c5890@@YAXXZ
?d_003c5890@@YAXXZ PROC
    db 8Bh, 41h, 04h, 8Bh, 54h, 24h, 04h, 3Bh, 41h, 08h, 89h, 54h, 24h, 04h, 74h, 0Dh
    db 85h, 0C0h, 74h, 02h, 89h, 10h, 83h, 41h, 04h, 04h, 0C2h, 04h, 00h, 6Ah, 01h, 6Ah
    db 01h, 8Dh, 54h, 24h, 0Ch, 52h, 8Dh, 54h, 24h, 10h, 52h, 50h, 0E8h, 16h, 0A8h, 0C4h
    db 0FFh, 0C2h, 04h, 00h
?d_003c5890@@YAXXZ ENDP

; ghidra: FUN_007c58e0  retail @ 0x003C58E0 size 138
public ?d_003c58e0@@YAXXZ
?d_003c58e0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 53h, 8Bh, 19h, 55h, 8Bh, 6Ch, 24h, 10h, 56h, 8Bh, 71h, 04h
    db 8Bh, 0C6h, 2Bh, 0C3h, 0C1h, 0F8h, 02h, 33h, 0D2h, 85h, 0C0h, 57h, 76h, 21h, 8Bh, 0FBh
    db 8Bh, 07h, 0D9h, 45h, 24h, 0D8h, 58h, 24h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Bh, 2Bh, 8Bh
    db 41h, 04h, 2Bh, 01h, 42h, 0C1h, 0F8h, 02h, 83h, 0C7h, 04h, 3Bh, 0D0h, 72h, 0E1h, 3Bh
    db 71h, 08h, 74h, 2Bh, 85h, 0F6h, 74h, 02h, 89h, 2Eh, 8Bh, 41h, 04h, 5Fh, 5Eh, 83h
    db 0C0h, 04h, 5Dh, 89h, 41h, 04h, 5Bh, 0C2h, 08h, 00h, 8Dh, 44h, 24h, 18h, 50h, 8Dh
    db 14h, 93h, 52h, 0E8h, 0F5h, 9Eh, 0C6h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 08h, 00h, 6Ah
    db 01h, 6Ah, 01h, 8Dh, 44h, 24h, 20h, 50h, 8Dh, 54h, 24h, 24h, 52h, 56h, 0E8h, 74h
    db 0A7h, 0C4h, 0FFh, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 08h, 00h
?d_003c58e0@@YAXXZ ENDP

; ghidra: FUN_007c5990  retail @ 0x003C5990 size 276
public ?d_003c5990@@YAXXZ
?d_003c5990@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 8Bh, 43h, 04h, 8Bh, 53h, 08h, 2Bh, 0D0h
    db 57h, 8Bh, 0F9h, 33h, 0C9h, 0C1h, 0FAh, 02h, 85h, 0D2h, 89h, 4Ch, 24h, 0Ch, 0Fh, 86h
    db 0E8h, 00h, 00h, 00h, 55h, 56h, 8Bh, 34h, 88h, 8Ah, 46h, 18h, 84h, 0C0h, 75h, 0Ch
    db 8Ah, 44h, 24h, 20h, 84h, 0C0h, 0Fh, 84h, 0B2h, 00h, 00h, 00h, 56h, 8Bh, 0CBh, 0E8h
    db 34h, 2Eh, 0C6h, 0FFh, 0D8h, 43h, 1Ch, 8Bh, 57h, 14h, 8Bh, 47h, 18h, 8Dh, 6Fh, 14h
    db 0D9h, 5Ch, 24h, 10h, 2Bh, 0C2h, 0C1h, 0F8h, 02h, 33h, 0C9h, 85h, 0C0h, 76h, 1Dh, 90h
    db 39h, 32h, 74h, 0Ah, 41h, 83h, 0C2h, 04h, 3Bh, 0C8h, 72h, 0F4h, 0EBh, 0Eh, 0D9h, 46h
    db 1Ch, 0D8h, 5Ch, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 7Bh, 72h, 8Bh, 57h, 20h, 8Bh
    db 47h, 24h, 8Dh, 5Fh, 20h, 2Bh, 0C2h, 0C1h, 0F8h, 02h, 33h, 0C9h, 85h, 0C0h, 76h, 1Ch
    db 39h, 32h, 74h, 0Ah, 41h, 83h, 0C2h, 04h, 3Bh, 0C8h, 72h, 0F4h, 0EBh, 0Eh, 0D9h, 46h
    db 1Ch, 0D8h, 5Ch, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 7Bh, 3Eh, 56h, 55h, 8Bh, 0CFh
    db 0E8h, 33h, 6Dh, 0C6h, 0FFh, 56h, 53h, 8Bh, 0CFh, 0E8h, 2Ah, 6Dh, 0C6h, 0FFh, 8Bh, 44h
    db 24h, 1Ch, 8Bh, 4Ch, 24h, 10h, 89h, 4Eh, 1Ch, 89h, 46h, 28h, 8Bh, 57h, 10h, 52h
    db 8Bh, 0CEh, 0E8h, 0A1h, 2Dh, 0C6h, 0FFh, 0D9h, 56h, 20h, 0D8h, 44h, 24h, 10h, 56h, 55h
    db 8Bh, 0CFh, 0D9h, 5Eh, 24h, 0E8h, 0E3h, 86h, 0C7h, 0FFh, 8Bh, 5Ch, 24h, 1Ch, 8Bh, 43h
    db 04h, 8Bh, 53h, 08h, 8Bh, 4Ch, 24h, 14h, 2Bh, 0D0h, 41h, 0C1h, 0FAh, 02h, 3Bh, 0CAh
    db 89h, 4Ch, 24h, 14h, 0Fh, 82h, 1Ch, 0FFh, 0FFh, 0FFh, 5Eh, 5Dh, 5Fh, 5Bh, 83h, 0C4h
    db 08h, 0C2h, 08h, 00h
?d_003c5990@@YAXXZ ENDP

; ghidra: FUN_007c5c10  retail @ 0x003C5C10 size 39
public ?d_003c5c10@@YAXXZ
?d_003c5c10@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 1Ah, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0FFh
    db 8Bh, 07h, 56h, 50h, 8Bh, 0CFh, 0E8h, 5Ah, 51h, 0C4h, 0FFh, 8Bh, 76h, 28h, 85h, 0F6h
    db 75h, 0EEh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_003c5c10@@YAXXZ ENDP

; ghidra: FUN_007c5c40  retail @ 0x003C5C40 size 368
public ?d_003c5c40@@YAXXZ
?d_003c5c40@@YAXXZ PROC
    db 53h, 55h, 8Bh, 0D9h, 8Bh, 43h, 18h, 3Bh, 0C0h, 8Bh, 4Bh, 14h, 56h, 8Dh, 73h, 14h
    db 57h, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h
    db 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 04h, 8Bh, 43h, 24h, 3Bh
    db 0C0h, 8Bh, 4Bh, 20h, 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h
    db 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 8Bh, 4Ch, 24h, 1Ch
    db 85h, 0C9h, 89h, 43h, 24h, 74h, 0Ch, 8Bh, 41h, 04h, 8Bh, 11h, 50h, 52h, 0E8h, 74h
    db 0EFh, 0C5h, 0FFh, 8Bh, 44h, 24h, 14h, 50h, 53h, 8Bh, 0CBh, 0E8h, 35h, 0DAh, 0C6h, 0FFh
    db 8Bh, 4Ch, 24h, 18h, 51h, 8Bh, 0F8h, 8Dh, 6Bh, 0Ch, 53h, 8Bh, 0CBh, 89h, 7Dh, 00h
    db 0E8h, 20h, 0DAh, 0C6h, 0FFh, 33h, 0C9h, 3Bh, 0F9h, 89h, 43h, 10h, 0Fh, 84h, 0BBh, 00h
    db 00h, 00h, 3Bh, 0C1h, 0Fh, 84h, 0B3h, 00h, 00h, 00h, 89h, 4Fh, 1Ch, 89h, 4Fh, 20h
    db 89h, 4Fh, 24h, 8Bh, 55h, 00h, 89h, 4Ah, 28h, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 74h
    db 0Fh, 3Bh, 0C1h, 74h, 05h, 8Bh, 4Dh, 00h, 89h, 08h, 83h, 46h, 04h, 04h, 0EBh, 12h
    db 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 24h, 52h, 55h, 50h, 8Bh, 0CEh, 0E8h, 0C5h, 0A3h
    db 0C4h, 0FFh, 8Bh, 46h, 04h, 2Bh, 06h, 0A9h, 0FCh, 0FFh, 0FFh, 0FFh, 74h, 6Fh, 8Bh, 6Ch
    db 24h, 20h, 8Bh, 16h, 8Bh, 46h, 04h, 8Bh, 3Ah, 8Dh, 4Ah, 04h, 3Bh, 0C1h, 89h, 7Ch
    db 24h, 14h, 74h, 0Eh, 2Bh, 0C1h, 50h, 51h, 52h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h
    db 0C4h, 0Ch, 83h, 46h, 04h, 0FCh, 3Bh, 7Bh, 10h, 74h, 4Bh, 55h, 57h, 8Bh, 0CBh, 0E8h
    db 4Dh, 0A7h, 0C4h, 0FFh, 8Bh, 43h, 24h, 8Bh, 53h, 28h, 3Bh, 0C2h, 8Dh, 4Bh, 20h, 74h
    db 0Ch, 85h, 0C0h, 74h, 02h, 89h, 38h, 83h, 41h, 04h, 04h, 0EBh, 14h, 6Ah, 01h, 6Ah
    db 01h, 8Dh, 54h, 24h, 24h, 52h, 8Dh, 54h, 24h, 20h, 52h, 50h, 0E8h, 56h, 0A3h, 0C4h
    db 0FFh, 8Bh, 46h, 04h, 2Bh, 06h, 0A9h, 0FCh, 0FFh, 0FFh, 0FFh, 75h, 95h, 5Fh, 5Eh, 5Dh
    db 32h, 0C0h, 5Bh, 0C2h, 10h, 00h, 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 74h, 09h, 50h, 57h
    db 8Bh, 0CBh, 0E8h, 76h, 30h, 0C4h, 0FFh, 5Fh, 5Eh, 5Dh, 0B0h, 01h, 5Bh, 0C2h, 10h, 00h
?d_003c5c40@@YAXXZ ENDP

; ghidra: FUN_007c6120  retail @ 0x003C6120 size 60
public ?d_003c6120@@YAXXZ
?d_003c6120@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 24h, 33h, 0DBh, 3Bh, 0C3h, 74h, 26h, 57h, 8Bh, 0F8h
    db 3Bh, 0FBh, 74h, 15h, 8Bh, 07h, 8Bh, 0CFh, 0FFh, 50h, 40h, 0FFh, 4Fh, 04h, 75h, 06h
    db 8Bh, 17h, 8Bh, 0CFh, 0FFh, 12h, 89h, 5Eh, 24h, 5Fh, 89h, 5Eh, 24h, 89h, 5Eh, 04h
    db 5Eh, 5Bh, 0C3h, 89h, 5Eh, 24h, 89h, 5Eh, 04h, 5Eh, 5Bh, 0C3h
?d_003c6120@@YAXXZ ENDP

; ghidra: FUN_007c6200  retail @ 0x003C6200 size 104
public ?d_003c6200@@YAXXZ
?d_003c6200@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 8Bh, 0F1h, 75h, 1Eh, 8Bh, 46h, 40h, 85h
    db 0C0h, 74h, 50h, 8Bh, 0Dh, 98h, 4Bh, 2Fh, 01h, 57h, 0E8h, 7Ch, 04h, 0C8h, 0FFh, 89h
    db 7Eh, 40h, 89h, 7Eh, 44h, 5Fh, 5Eh, 0C2h, 08h, 00h, 8Ah, 44h, 24h, 10h, 84h, 0C0h
    db 75h, 0Ah, 8Ah, 87h, 0A8h, 00h, 00h, 00h, 84h, 0C0h, 74h, 27h, 39h, 7Eh, 40h, 74h
    db 09h, 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 0EBh, 03h, 0FFh, 46h, 44h, 8Bh, 46h, 44h
    db 85h, 0C0h, 75h, 0Ch, 8Bh, 0Dh, 98h, 4Bh, 2Fh, 01h, 57h, 0E8h, 3Bh, 04h, 0C8h, 0FFh
    db 89h, 7Eh, 40h, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_003c6200@@YAXXZ ENDP

; ghidra: FUN_007c6310  retail @ 0x003C6310 size 35
public ?d_003c6310@@YAXXZ
?d_003c6310@@YAXXZ PROC
    db 8Bh, 41h, 04h, 8Bh, 4Ch, 24h, 04h, 3Bh, 48h, 18h, 7Fh, 05h, 33h, 0C0h, 0C2h, 04h
    db 00h, 56h, 8Bh, 70h, 1Ch, 33h, 0D2h, 3Bh, 0CEh, 0Fh, 9Fh, 0C2h, 5Eh, 42h, 8Bh, 0C2h
    db 0C2h, 04h, 00h
?d_003c6310@@YAXXZ ENDP

; ghidra: FUN_007c6340  retail @ 0x003C6340 size 15
public ?d_003c6340@@YAXXZ
?d_003c6340@@YAXXZ PROC
    db 8Bh, 49h, 08h, 85h, 0C9h, 74h, 05h, 0E9h, 0C3h, 0FCh, 0C3h, 0FFh, 0C2h, 04h, 00h
?d_003c6340@@YAXXZ ENDP

; ghidra: FUN_007c6360  retail @ 0x003C6360 size 14
public ?d_003c6360@@YAXXZ
?d_003c6360@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 74h, 04h, 8Bh, 40h, 4Ch, 0C3h, 33h, 0C0h, 0C3h
?d_003c6360@@YAXXZ ENDP

; ghidra: FUN_007c6380  retail @ 0x003C6380 size 14
public ?d_003c6380@@YAXXZ
?d_003c6380@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 74h, 04h, 8Bh, 40h, 50h, 0C3h, 33h, 0C0h, 0C3h
?d_003c6380@@YAXXZ ENDP

; ghidra: FUN_007c63a0  retail @ 0x003C63A0 size 17
public ?d_003c63a0@@YAXXZ
?d_003c63a0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 74h, 04h, 83h, 0C0h, 54h, 0C3h, 0B8h, 50h, 6Eh, 33h, 01h
    db 0C3h
?d_003c63a0@@YAXXZ ENDP

; ghidra: FUN_007c6580  retail @ 0x003C6580 size 8
public ?d_003c6580@@YAXXZ
?d_003c6580@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 56h, 0CCh
?d_003c6580@@YAXXZ ENDP

; ghidra: FUN_007c6760  retail @ 0x003C6760 size 8
public ?d_003c6760@@YAXXZ
?d_003c6760@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 56h, 0CCh
?d_003c6760@@YAXXZ ENDP

; ghidra: FUN_007c6950  retail @ 0x003C6950 size 8
public ?d_003c6950@@YAXXZ
?d_003c6950@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 56h, 0CCh
?d_003c6950@@YAXXZ ENDP

; ghidra: FUN_007c6b30  retail @ 0x003C6B30 size 8
public ?d_003c6b30@@YAXXZ
?d_003c6b30@@YAXXZ PROC
    db 55h, 8Bh, 0ECh, 83h, 0ECh, 28h, 56h, 0CCh
?d_003c6b30@@YAXXZ ENDP

; ghidra: FUN_007c6f60  retail @ 0x003C6F60 size 18
public ?d_003c6f60@@YAXXZ
?d_003c6f60@@YAXXZ PROC
    db 8Bh, 51h, 6Ch, 8Bh, 44h, 24h, 04h, 89h, 10h, 8Bh, 49h, 70h, 89h, 48h, 04h, 0C2h
    db 04h, 00h
?d_003c6f60@@YAXXZ ENDP

; ghidra: FUN_007c7010  retail @ 0x003C7010 size 220
public ?d_003c7010@@YAXXZ
?d_003c7010@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B8h, 0EFh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 56h, 8Bh, 71h, 04h, 57h, 68h, 7Ch, 0DEh
    db 0Eh, 01h, 8Dh, 4Ch, 24h, 0Ch, 83h, 0C6h, 40h, 0E8h, 82h, 1Bh, 4Ch, 00h, 8Bh, 7Ch
    db 24h, 20h, 6Ah, 00h, 83h, 0C7h, 28h, 57h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CEh, 0C7h
    db 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0E8h, 0BAh, 42h, 0C4h, 0FFh, 8Dh, 4Ch, 24h, 08h
    db 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0D3h, 08h, 4Ch, 00h, 68h, 60h, 0DEh
    db 0Eh, 01h, 8Dh, 4Ch, 24h, 24h, 0E8h, 45h, 1Bh, 4Ch, 00h, 6Ah, 00h, 57h, 8Dh, 4Ch
    db 24h, 28h, 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 24h, 01h, 00h, 00h, 00h, 0E8h, 84h, 42h
    db 0C4h, 0FFh, 8Dh, 4Ch, 24h, 20h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 9Dh
    db 08h, 4Ch, 00h, 68h, 44h, 0DEh, 0Eh, 01h, 8Dh, 4Ch, 24h, 10h, 0E8h, 0Fh, 1Bh, 4Ch
    db 00h, 6Ah, 00h, 57h, 8Dh, 54h, 24h, 14h, 52h, 8Bh, 0CEh, 0C7h, 44h, 24h, 24h, 02h
    db 00h, 00h, 00h, 0E8h, 4Eh, 42h, 0C4h, 0FFh, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 18h
    db 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 67h, 08h, 4Ch, 00h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_003c7010@@YAXXZ ENDP

; ghidra: FUN_007c7130  retail @ 0x003C7130 size 296
public ?d_003c7130@@YAXXZ
?d_003c7130@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F0h, 0EFh, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 8Bh, 0F1h, 8Bh, 5Eh, 04h
    db 57h, 68h, 28h, 0DFh, 0Eh, 01h, 8Dh, 4Ch, 24h, 14h, 83h, 0C3h, 40h, 0E8h, 5Eh, 1Ah
    db 4Ch, 00h, 8Bh, 44h, 24h, 28h, 6Ah, 00h, 83h, 0C0h, 28h, 50h, 8Dh, 4Ch, 24h, 18h
    db 51h, 8Bh, 0CBh, 0C7h, 44h, 24h, 2Ch, 00h, 00h, 00h, 00h, 0E8h, 96h, 41h, 0C4h, 0FFh
    db 83h, 0CDh, 0FFh, 8Dh, 4Ch, 24h, 10h, 89h, 6Ch, 24h, 20h, 0E8h, 0B0h, 07h, 4Ch, 00h
    db 8Bh, 7Eh, 04h, 8Bh, 77h, 30h, 8Bh, 47h, 34h, 83h, 0C7h, 30h, 3Bh, 0F0h, 74h, 41h
    db 68h, 44h, 0DFh, 0Eh, 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 12h, 1Ah, 4Ch, 00h, 8Bh, 16h
    db 6Ah, 00h, 83h, 0C2h, 28h, 52h, 8Dh, 44h, 24h, 30h, 50h, 8Bh, 0CBh, 0C7h, 44h, 24h
    db 2Ch, 01h, 00h, 00h, 00h, 0E8h, 4Ch, 41h, 0C4h, 0FFh, 8Dh, 4Ch, 24h, 28h, 89h, 6Ch
    db 24h, 20h, 0E8h, 69h, 07h, 4Ch, 00h, 8Bh, 47h, 04h, 83h, 0C6h, 04h, 3Bh, 0F0h, 75h
    db 0BFh, 68h, 28h, 0DFh, 0Eh, 01h, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 0D1h, 19h, 4Ch, 00h, 6Ah
    db 01h, 8Dh, 4Ch, 24h, 2Ch, 51h, 8Bh, 0CBh, 0C7h, 44h, 24h, 28h, 02h, 00h, 00h, 00h
    db 0E8h, 0A9h, 0F9h, 0C3h, 0FFh, 8Dh, 4Ch, 24h, 28h, 89h, 6Ch, 24h, 20h, 0E8h, 2Eh, 07h
    db 4Ch, 00h, 68h, 44h, 0DFh, 0Eh, 01h, 8Dh, 4Ch, 24h, 18h, 0E8h, 0A0h, 19h, 4Ch, 00h
    db 6Ah, 01h, 8Dh, 54h, 24h, 18h, 52h, 8Bh, 0CBh, 0C7h, 44h, 24h, 28h, 03h, 00h, 00h
    db 00h, 0E8h, 78h, 0F9h, 0C3h, 0FFh, 8Dh, 4Ch, 24h, 14h, 89h, 6Ch, 24h, 20h, 0E8h, 0FDh
    db 06h, 4Ch, 00h, 8Bh, 4Ch, 24h, 18h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_003c7130@@YAXXZ ENDP

; ghidra: FUN_007c72f0  retail @ 0x003C72F0 size 76
public ?d_003c72f0@@YAXXZ
?d_003c72f0@@YAXXZ PROC
    db 8Bh, 51h, 18h, 53h, 8Bh, 59h, 14h, 2Bh, 0D3h, 0C1h, 0FAh, 02h, 56h, 33h, 0C0h, 85h
    db 0D2h, 57h, 76h, 27h, 8Bh, 7Ch, 24h, 10h, 8Bh, 0F3h, 8Bh, 0D3h, 8Dh, 64h, 24h, 00h
    db 8Bh, 1Ah, 39h, 0BBh, 0ACh, 00h, 00h, 00h, 74h, 19h, 8Bh, 59h, 18h, 2Bh, 59h, 14h
    db 40h, 0C1h, 0FBh, 02h, 83h, 0C2h, 04h, 3Bh, 0C3h, 72h, 0E5h, 5Fh, 5Eh, 33h, 0C0h, 5Bh
    db 0C2h, 04h, 00h, 8Bh, 04h, 86h, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h
?d_003c72f0@@YAXXZ ENDP

; ghidra: FUN_007c73a0  retail @ 0x003C73A0 size 93
public ?d_003c73a0@@YAXXZ
?d_003c73a0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 74h, 0Ah, 8Ah, 86h, 0E9h, 00h, 00h, 00h, 84h
    db 0C0h, 75h, 06h, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h, 8Bh, 41h, 14h, 8Bh, 51h, 18h, 3Bh
    db 0C2h, 74h, 34h, 57h, 8Bh, 79h, 14h, 2Bh, 0D7h, 0C1h, 0FAh, 02h, 33h, 0C0h, 85h, 0D2h
    db 76h, 17h, 8Bh, 0D7h, 39h, 32h, 74h, 18h, 8Bh, 79h, 18h, 2Bh, 79h, 14h, 40h, 0C1h
    db 0FFh, 02h, 83h, 0C2h, 04h, 3Bh, 0C7h, 72h, 0EBh, 5Fh, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h
    db 5Fh, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h, 0B0h, 01h, 5Eh, 0C2h, 04h, 00h
?d_003c73a0@@YAXXZ ENDP

; ghidra: FUN_007c7420  retail @ 0x003C7420 size 262
public ?d_003c7420@@YAXXZ
?d_003c7420@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 30h, 0F0h, 01h, 01h, 50h, 8Ah, 44h
    db 24h, 14h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 56h, 8Bh, 71h, 04h, 83h, 0C6h, 40h
    db 84h, 0C0h, 8Dh, 4Ch, 24h, 18h, 68h, 44h, 0DEh, 0Eh, 01h, 74h, 5Eh, 0E8h, 6Eh, 17h
    db 4Ch, 00h, 8Bh, 44h, 24h, 14h, 6Ah, 01h, 83h, 0C0h, 28h, 50h, 8Dh, 4Ch, 24h, 20h
    db 51h, 8Bh, 0CEh, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 0E8h, 0A6h, 3Eh, 0C4h, 0FFh
    db 8Dh, 4Ch, 24h, 18h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0BFh, 04h, 4Ch
    db 00h, 68h, 44h, 0DEh, 0Eh, 01h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 31h, 17h, 4Ch, 00h, 6Ah
    db 00h, 8Dh, 54h, 24h, 1Ch, 52h, 8Bh, 0CEh, 0C7h, 44h, 24h, 14h, 01h, 00h, 00h, 00h
    db 0E8h, 0E2h, 0FDh, 0C5h, 0FFh, 8Dh, 4Ch, 24h, 18h, 0EBh, 5Ch, 0E8h, 10h, 17h, 4Ch, 00h
    db 8Bh, 44h, 24h, 14h, 6Ah, 00h, 83h, 0C0h, 28h, 50h, 8Dh, 4Ch, 24h, 20h, 51h, 8Bh
    db 0CEh, 0C7h, 44h, 24h, 18h, 02h, 00h, 00h, 00h, 0E8h, 48h, 3Eh, 0C4h, 0FFh, 8Dh, 4Ch
    db 24h, 18h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 61h, 04h, 4Ch, 00h, 68h
    db 44h, 0DEh, 0Eh, 01h, 8Dh, 4Ch, 24h, 18h, 0E8h, 0D3h, 16h, 4Ch, 00h, 6Ah, 01h, 8Dh
    db 54h, 24h, 18h, 52h, 8Bh, 0CEh, 0C7h, 44h, 24h, 14h, 03h, 00h, 00h, 00h, 0E8h, 0ABh
    db 0F6h, 0C3h, 0FFh, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h, 0Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h
    db 2Ch, 04h, 4Ch, 00h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh
    db 83h, 0C4h, 0Ch, 0C2h, 08h, 00h
?d_003c7420@@YAXXZ ENDP

; ghidra: FUN_007c7570  retail @ 0x003C7570 size 27
public ?d_003c7570@@YAXXZ
?d_003c7570@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 0Fh, 6Ah, 00h, 50h, 0E8h, 91h, 7Eh
    db 0C7h, 0FFh, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_003c7570@@YAXXZ ENDP

; ghidra: FUN_007c75a0  retail @ 0x003C75A0 size 58
public ?d_003c75a0@@YAXXZ
?d_003c75a0@@YAXXZ PROC
    db 56h, 8Bh, 71h, 04h, 8Bh, 46h, 30h, 8Bh, 4Eh, 34h, 83h, 0C6h, 30h, 2Bh, 0C8h, 57h
    db 0C1h, 0F9h, 02h, 33h, 0FFh, 85h, 0C9h, 76h, 1Eh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 0Ch, 0B8h, 0E8h, 0C2h, 4Bh, 0C4h, 0FFh, 8Bh, 06h, 8Bh, 56h, 04h, 2Bh, 0D0h, 47h
    db 0C1h, 0FAh, 02h, 3Bh, 0FAh, 72h, 0E9h, 5Fh, 5Eh, 0C3h
?d_003c75a0@@YAXXZ ENDP

; ghidra: FUN_007c7780  retail @ 0x003C7780 size 216
public ?d_003c7780@@YAXXZ
?d_003c7780@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 8Dh, 77h
    db 7Ch, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 0F7h, 0B0h, 0C7h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 41h, 50h, 0C6h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 31h, 50h, 0C6h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 87h, 15h
    db 0C4h, 0FFh, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 6Ah, 01h
    db 6Ah, 05h, 0E8h, 2Dh, 1Ah, 0C8h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h, 31h, 0C0h, 74h
    db 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h, 00h, 31h, 0C0h
    db 40h, 74h, 06h, 8Bh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 74h, 08h, 8Bh, 45h, 0F8h
    db 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 0E6h, 0DEh, 0C5h, 0FFh
    db 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 8Dh, 77h, 7Ch, 00h
    db 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh, 0CDh, 0CEh, 58h
    db 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_003c7780@@YAXXZ ENDP

; ghidra: FUN_007c78b0  retail @ 0x003C78B0 size 216
public ?d_003c78b0@@YAXXZ
?d_003c78b0@@YAXXZ PROC
    db 55h, 89h, 0E5h, 83h, 0ECh, 20h, 57h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0BDh, 78h
    db 7Ch, 00h, 0B8h, 01h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CCh, 0CDh, 0CEh
    db 0CFh, 58h, 83h, 65h, 0F4h, 00h, 0E8h, 0C7h, 0AFh, 0C7h, 0FFh, 89h, 45h, 0FCh, 0FFh, 75h
    db 08h, 0FFh, 75h, 0FCh, 0E8h, 11h, 4Fh, 0C6h, 0FFh, 59h, 59h, 89h, 45h, 0F8h, 0FFh, 75h
    db 0Ch, 0FFh, 75h, 0FCh, 0E8h, 01h, 4Fh, 0C6h, 0FFh, 59h, 59h, 89h, 45h, 0ECh, 31h, 0C0h
    db 8Dh, 7Dh, 0EBh, 0AAh, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 8Dh, 4Dh, 0EBh, 0E8h, 8Eh, 62h
    db 0C6h, 0FFh, 89h, 45h, 0F0h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0ECh, 0FFh, 75h, 0F8h, 6Ah, 0Dh
    db 6Ah, 05h, 0E8h, 0FDh, 18h, 0C8h, 0FFh, 83h, 0C4h, 14h, 89h, 45h, 0F0h, 31h, 0C0h, 74h
    db 0Dh, 83h, 7Dh, 0F8h, 01h, 75h, 07h, 8Bh, 45h, 0FCh, 83h, 60h, 18h, 00h, 31h, 0C0h
    db 74h, 06h, 8Bh, 45h, 0Ch, 89h, 45h, 0F0h, 31h, 0C0h, 40h, 74h, 08h, 8Bh, 45h, 0F8h
    db 89h, 45h, 0F4h, 0EBh, 10h, 0FFh, 75h, 0F0h, 0FFh, 75h, 0FCh, 0E8h, 0B6h, 0DDh, 0C5h, 0FFh
    db 59h, 59h, 89h, 45h, 0F4h, 50h, 0B8h, 0CCh, 0CDh, 0CEh, 0CFh, 0B8h, 0BDh, 78h, 7Ch, 00h
    db 0B8h, 00h, 00h, 00h, 00h, 0B8h, 00h, 00h, 00h, 00h, 0B8h, 0CBh, 0CCh, 0CDh, 0CEh, 58h
    db 8Bh, 45h, 0F4h, 5Fh, 89h, 0ECh, 5Dh, 0C3h
?d_003c78b0@@YAXXZ ENDP

; ghidra: FUN_007c7a40  retail @ 0x003C7A40 size 166
public ?d_003c7a40@@YAXXZ
?d_003c7a40@@YAXXZ PROC
    db 57h, 8Bh, 0F9h, 8Bh, 47h, 3Ch, 85h, 0C0h, 0Fh, 84h, 96h, 00h, 00h, 00h, 8Bh, 47h
    db 34h, 53h, 2Bh, 47h, 30h, 56h, 0C1h, 0F8h, 02h, 33h, 0F6h, 85h, 0C0h, 76h, 24h, 90h
    db 8Bh, 4Fh, 30h, 8Bh, 14h, 0B1h, 8Bh, 82h, 0ECh, 00h, 00h, 00h, 8Bh, 4Fh, 3Ch, 50h
    db 0E8h, 0Eh, 2Ch, 0C8h, 0FFh, 8Bh, 4Fh, 34h, 2Bh, 4Fh, 30h, 46h, 0C1h, 0F9h, 02h, 3Bh
    db 0F1h, 72h, 0DDh, 8Bh, 57h, 34h, 2Bh, 57h, 30h, 55h, 0C1h, 0FAh, 02h, 33h, 0EDh, 85h
    db 0D2h, 76h, 4Eh, 8Bh, 47h, 30h, 8Bh, 34h, 0A8h, 8Bh, 46h, 30h, 8Bh, 4Eh, 34h, 2Bh
    db 0C8h, 0C1h, 0F9h, 02h, 33h, 0DBh, 85h, 0C9h, 76h, 29h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 3Ch, 8Dh, 14h, 98h, 8Bh, 86h, 0ECh, 00h, 00h, 00h, 52h, 50h, 0E8h, 0DAh
    db 82h, 0C5h, 0FFh, 8Bh, 46h, 30h, 8Bh, 4Eh, 34h, 2Bh, 0C8h, 43h, 0C1h, 0F9h, 02h, 3Bh
    db 0D9h, 72h, 0DDh, 8Bh, 57h, 34h, 2Bh, 57h, 30h, 45h, 0C1h, 0FAh, 02h, 3Bh, 0EAh, 72h
    db 0B2h, 5Dh, 5Eh, 5Bh, 5Fh, 0C3h
?d_003c7a40@@YAXXZ ENDP

; ghidra: FUN_007c7b10  retail @ 0x003C7B10 size 53
public ?d_003c7b10@@YAXXZ
?d_003c7b10@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 8Bh, 46h, 34h, 2Bh, 46h, 30h, 57h, 0C1h, 0F8h, 02h, 33h, 0FFh
    db 85h, 0C0h, 76h, 1Dh, 8Dh, 5Eh, 04h, 8Bh, 4Eh, 30h, 8Bh, 0Ch, 0B9h, 53h, 0E8h, 0C7h
    db 09h, 0C8h, 0FFh, 8Bh, 56h, 34h, 2Bh, 56h, 30h, 47h, 0C1h, 0FAh, 02h, 3Bh, 0FAh, 72h
    db 0E6h, 5Fh, 5Eh, 5Bh, 0C3h
?d_003c7b10@@YAXXZ ENDP

; ghidra: FUN_007c7b60  retail @ 0x003C7B60 size 347
public ?d_003c7b60@@YAXXZ
?d_003c7b60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0F0h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 3Ch, 53h, 57h, 8Bh, 0F9h, 8Bh, 5Ch, 24h, 54h
    db 83h, 3Bh, 00h, 0C7h, 44h, 24h, 4Ch, 00h, 00h, 00h, 00h, 0Fh, 85h, 06h, 01h, 00h
    db 00h, 8Bh, 44h, 24h, 58h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 56h, 50h, 0E8h, 0E6h, 76h, 53h, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h, 85h
    db 0F6h, 0Fh, 84h, 0DDh, 00h, 00h, 00h, 8Ah, 44h, 24h, 64h, 84h, 0C0h, 74h, 0Bh, 6Ah
    db 00h, 56h, 0E8h, 0F9h, 13h, 0C5h, 0FFh, 83h, 0C4h, 08h, 8Bh, 06h, 8Bh, 0CEh, 0C7h, 44h
    db 24h, 18h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 20h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 24h, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 28h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 2Ch, 00h, 00h, 80h, 3Fh, 0C7h, 44h
    db 24h, 30h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 38h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 3Ch, 00h, 00h, 00h, 00h, 0C7h, 44h
    db 24h, 40h, 00h, 00h, 80h, 3Fh, 0C7h, 44h, 24h, 44h, 00h, 00h, 00h, 00h, 0FFh, 50h
    db 50h, 0D9h, 46h, 34h, 8Bh, 15h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 82h, 8Fh, 00h, 00h, 00h
    db 84h, 0C0h, 8Bh, 4Eh, 24h, 89h, 4Ch, 24h, 0Ch, 74h, 08h, 0D9h, 05h, 10h, 18h, 08h
    db 01h, 0EBh, 06h, 8Bh, 47h, 04h, 0D9h, 40h, 08h, 8Bh, 4Ch, 24h, 0Ch, 0D9h, 0C9h, 8Bh
    db 16h, 0D9h, 5Ch, 24h, 34h, 8Dh, 44h, 24h, 18h, 89h, 4Ch, 24h, 24h, 0D9h, 5Ch, 24h
    db 44h, 50h, 8Bh, 0CEh, 0FFh, 52h, 54h, 8Bh, 4Ch, 24h, 60h, 51h, 8Bh, 0Dh, 48h, 70h
    db 2Fh, 01h, 56h, 0E8h, 0DBh, 8Ch, 0C6h, 0FFh, 8Bh, 0Dh, 48h, 70h, 2Fh, 01h, 8Bh, 11h
    db 56h, 0FFh, 52h, 28h, 89h, 33h, 5Eh, 8Dh, 4Ch, 24h, 58h, 0C7h, 44h, 24h, 4Ch, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 98h, 0FCh, 4Bh, 00h, 8Bh, 4Ch, 24h, 44h, 5Fh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 48h, 0C2h, 10h, 00h
?d_003c7b60@@YAXXZ ENDP

; ghidra: FUN_007c7d20  retail @ 0x003C7D20 size 37
_TEXT ENDS
_TEXT$d007c7d20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007C7D20 size 37
public ?d_003c7d20@@YAXXZ
?d_003c7d20@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0101F070
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 08Bh, 00Ch
    db 024h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 00Ch, 0C2h, 004h, 000h
?d_003c7d20@@YAXXZ ENDP
_TEXT$d007c7d20 ENDS
_TEXT SEGMENT

; ghidra: FUN_007c7d50  retail @ 0x003C7D50 size 58
public ?d_003c7d50@@YAXXZ
?d_003c7d50@@YAXXZ PROC
    db 8Bh, 51h, 04h, 85h, 0D2h, 74h, 2Eh, 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 7Ch, 26h, 8Bh
    db 42h, 20h, 8Bh, 52h, 24h, 2Bh, 0D0h, 0C1h, 0FAh, 03h, 3Bh, 0CAh, 73h, 17h, 8Bh, 54h
    db 24h, 08h, 56h, 8Bh, 34h, 0C8h, 89h, 32h, 8Bh, 44h, 0C8h, 04h, 89h, 42h, 04h, 0B0h
    db 01h, 5Eh, 0C2h, 08h, 00h, 32h, 0C0h, 0C2h, 08h, 00h
?d_003c7d50@@YAXXZ ENDP

; ghidra: FUN_007c8160  retail @ 0x003C8160 size 332
public ?d_003c8160@@YAXXZ
?d_003c8160@@YAXXZ PROC
    db 6Ah, 0FFh, 64h, 0A1h, 00h, 00h, 00h, 00h, 68h, 0C8h, 0F0h, 01h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 0E9h, 8Bh, 5Dh, 04h, 8Bh
    db 43h, 30h, 8Bh, 4Bh, 34h, 83h, 0C3h, 30h, 2Bh, 0C8h, 56h, 57h, 0C1h, 0F9h, 02h, 33h
    db 0FFh, 85h, 0C9h, 0Fh, 86h, 0CFh, 00h, 00h, 00h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 14h, 0B8h, 8Bh, 45h, 04h, 83h, 0C2h, 28h, 52h, 51h, 89h, 64h, 24h, 20h, 8Bh
    db 0F4h, 68h, 4Ch, 1Dh, 08h, 01h, 51h, 89h, 64h, 24h, 28h, 8Bh, 0CCh, 50h, 0E8h, 9Dh
    db 0F9h, 4Bh, 00h, 56h, 0E8h, 94h, 0EAh, 0C3h, 0FFh, 8Dh, 44h, 24h, 28h, 83h, 0C4h, 0Ch
    db 50h, 0E8h, 7Ch, 7Ch, 0C4h, 0FFh, 83h, 0C4h, 0Ch, 8Bh, 44h, 24h, 14h, 85h, 0C0h, 0C7h
    db 44h, 24h, 24h, 00h, 00h, 00h, 00h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 8Bh, 4Dh, 24h, 8Bh, 11h, 6Ah, 00h, 50h, 0FFh, 52h, 7Ch, 8Bh, 0F0h
    db 85h, 0F6h, 74h, 40h, 8Bh, 44h, 24h, 2Ch, 0D9h, 40h, 04h, 6Ah, 01h, 0D9h, 00h, 6Ah
    db 01h, 6Ah, 00h, 83h, 0ECh, 08h, 8Bh, 0C4h, 0D9h, 18h, 89h, 64h, 24h, 2Ch, 56h, 0D9h
    db 58h, 04h, 8Bh, 0Dh, 48h, 70h, 2Fh, 01h, 0E8h, 0BFh, 9Ah, 0C5h, 0FFh, 88h, 44h, 24h
    db 13h, 0FFh, 4Eh, 04h, 75h, 06h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 10h, 8Ah, 44h, 24h, 13h
    db 84h, 0C0h, 75h, 3Bh, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0EBh, 0F6h, 4Bh, 00h, 8Bh, 03h, 8Bh, 4Bh, 04h, 2Bh, 0C8h, 47h, 0C1h, 0F9h, 02h
    db 3Bh, 0F9h, 0Fh, 82h, 38h, 0FFh, 0FFh, 0FFh, 33h, 0C0h, 8Bh, 4Ch, 24h, 1Ch, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h, 8Bh
    db 1Bh, 8Bh, 3Ch, 0BBh, 8Dh, 4Ch, 24h, 14h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh
    db 0E8h, 0ABh, 0F6h, 4Bh, 00h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 0C7h, 5Fh, 5Eh, 5Dh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_003c8160@@YAXXZ ENDP

; ghidra: FUN_007c8300  retail @ 0x003C8300 size 46
public ?d_003c8300@@YAXXZ
?d_003c8300@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Dh, 54h, 24h, 04h, 52h, 8Bh, 54h, 24h, 18h, 8Bh, 0F1h, 8Bh
    db 0Dh, 48h, 70h, 2Fh, 01h, 8Bh, 01h, 52h, 0FFh, 50h, 20h, 8Dh, 44h, 24h, 04h, 50h
    db 8Bh, 0CEh, 0E8h, 29h, 0DEh, 0C7h, 0FFh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_003c8300@@YAXXZ ENDP

; ghidra: FUN_007c8340  retail @ 0x003C8340 size 124
public ?d_003c8340@@YAXXZ
?d_003c8340@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Ah, 46h, 10h, 84h, 0C0h, 57h, 74h, 54h, 8Bh, 7Ch, 24h, 0Ch, 85h
    db 0FFh, 74h, 4Ch, 8Ah, 87h, 0A8h, 00h, 00h, 00h, 84h, 0C0h, 74h, 42h, 8Bh, 46h, 08h
    db 85h, 0C0h, 74h, 0Ch, 3Bh, 0C7h, 74h, 08h, 6Ah, 00h, 50h, 0E8h, 0A3h, 70h, 0C7h, 0FFh
    db 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 57h, 0E8h, 93h, 28h, 0C8h, 0FFh, 84h, 0C0h, 74h, 30h
    db 57h, 8Bh, 0CEh, 0E8h, 0Eh, 81h, 0C5h, 0FFh, 39h, 7Eh, 08h, 74h, 2Ah, 6Ah, 01h, 57h
    db 8Bh, 0CEh, 0E8h, 7Ch, 70h, 0C7h, 0FFh, 89h, 7Eh, 08h, 5Fh, 5Eh, 0C2h, 04h, 00h, 8Bh
    db 46h, 08h, 85h, 0C0h, 74h, 0Ah, 6Ah, 00h, 50h, 8Bh, 0CEh, 0E8h, 63h, 70h, 0C7h, 0FFh
    db 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_003c8340@@YAXXZ ENDP

; ghidra: FUN_007c83e0  retail @ 0x003C83E0 size 174
public ?d_003c83e0@@YAXXZ
?d_003c83e0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 8Bh, 0F1h, 8Bh, 0Dh, 48h, 70h, 2Fh, 01h, 0E8h, 5Ch, 08h, 0C8h
    db 0FFh, 84h, 0C0h, 0Fh, 85h, 8Eh, 00h, 00h, 00h, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 0E8h
    db 7Bh, 66h, 0C4h, 0FFh, 84h, 0C0h, 75h, 7Fh, 0A1h, 28h, 10h, 2Fh, 01h, 8Bh, 48h, 20h
    db 89h, 4Ch, 24h, 04h, 8Bh, 50h, 24h, 8Bh, 0Dh, 6Ch, 70h, 2Fh, 01h, 89h, 54h, 24h
    db 08h, 0E8h, 0ABh, 01h, 0C8h, 0FFh, 84h, 0C0h, 74h, 3Bh, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h
    db 0E8h, 42h, 0D6h, 0C5h, 0FFh, 84h, 0C0h, 74h, 2Ch, 0A1h, 28h, 10h, 2Fh, 01h, 8Ah, 48h
    db 1Ch, 84h, 0C9h, 74h, 42h, 8Bh, 4Ch, 24h, 10h, 51h, 8Dh, 54h, 24h, 08h, 52h, 8Bh
    db 0CEh, 0E8h, 0ABh, 13h, 0C7h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 60h, 3Fh, 0C5h, 0FFh, 5Eh, 83h
    db 0C4h, 08h, 0C2h, 04h, 00h, 8Bh, 46h, 40h, 85h, 0C0h, 74h, 1Bh, 8Bh, 0Dh, 98h, 4Bh
    db 2Fh, 01h, 6Ah, 00h, 0E8h, 22h, 0E2h, 0C7h, 0FFh, 0C7h, 46h, 40h, 00h, 00h, 00h, 00h
    db 0C7h, 46h, 44h, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_003c83e0@@YAXXZ ENDP

; ghidra: FUN_007c86c0  retail @ 0x003C86C0 size 171
public ?d_003c86c0@@YAXXZ
?d_003c86c0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 64h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 64h, 48h, 2Bh, 01h, 8Bh, 14h
    db 95h, 78h, 48h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 01h, 4Ah
    db 0Ch, 14h, 0C7h, 40h, 08h, 05h, 4Ah, 0Ch, 14h, 0C7h, 40h, 0Ch, 01h, 4Ah, 0Ch, 14h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 01h, 4Ah, 0Ch, 14h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 05h, 4Ah, 0Ch, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 01h, 4Ah, 0Ch, 14h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_003c86c0@@YAXXZ ENDP

; ghidra: FUN_007c87a0  retail @ 0x003C87A0 size 171
public ?d_003c87a0@@YAXXZ
?d_003c87a0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0C1h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 89h, 64h, 24h, 04h
    db 8Bh, 54h, 24h, 04h, 83h, 0E2h, 03h, 8Bh, 0Ch, 95h, 8Ch, 48h, 2Bh, 01h, 8Bh, 14h
    db 95h, 0A0h, 48h, 2Bh, 01h, 89h, 10h, 8Bh, 54h, 24h, 0Ch, 0C7h, 40h, 04h, 01h, 4Ah
    db 0Ch, 14h, 0C7h, 40h, 08h, 05h, 4Ah, 0Ch, 14h, 0C7h, 40h, 0Ch, 0CDh, 08h, 0A0h, 54h
    db 8Bh, 12h, 89h, 50h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 12h, 89h, 50h, 14h, 8Bh, 0D1h
    db 0Fh, 0AFh, 0D1h, 81h, 0F2h, 01h, 4Ah, 0Ch, 14h, 89h, 50h, 04h, 0Fh, 0AFh, 0D1h, 81h
    db 0F2h, 05h, 4Ah, 0Ch, 14h, 8Bh, 70h, 10h, 89h, 50h, 08h, 0Fh, 0AFh, 0D1h, 81h, 0F2h
    db 0CDh, 08h, 0A0h, 54h, 89h, 50h, 0Ch, 0Fh, 0AFh, 0D1h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh
    db 0D1h, 89h, 70h, 10h, 8Bh, 70h, 14h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 89h, 70h
    db 14h, 8Bh, 70h, 18h, 33h, 0F2h, 8Bh, 0D6h, 0Fh, 0AFh, 0D1h, 8Bh, 48h, 1Ch, 33h, 0CAh
    db 89h, 70h, 18h, 89h, 48h, 1Ch, 5Eh, 59h, 0C2h, 08h, 00h
?d_003c87a0@@YAXXZ ENDP

; ghidra: FUN_007c8880  retail @ 0x003C8880 size 63
public ?d_003c8880@@YAXXZ
?d_003c8880@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 10h, 0E0h, 0Eh, 01h, 89h, 48h, 04h, 89h, 48h, 08h
    db 89h, 48h, 0Ch, 0C6h, 40h, 10h, 01h, 89h, 48h, 14h, 89h, 48h, 18h, 89h, 48h, 1Ch
    db 89h, 48h, 20h, 89h, 48h, 24h, 89h, 48h, 28h, 89h, 48h, 2Ch, 89h, 48h, 30h, 89h
    db 48h, 34h, 89h, 48h, 38h, 89h, 48h, 3Ch, 89h, 48h, 40h, 89h, 48h, 44h, 0C3h
?d_003c8880@@YAXXZ ENDP

; ghidra: FUN_007c88e0  retail @ 0x003C88E0 size 283
_TEXT ENDS
_TEXT$d007c88e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007C88E0 size 283
public ?d_003c88e0@@YAXXZ
?d_003c88e0@@YAXXZ PROC
    db 083h, 0ECh, 008h, 053h, 08Bh, 0D9h, 08Bh, 043h, 02Ch, 056h, 08Bh, 073h, 028h, 02Bh, 0C6h, 0C1h
    db 0F8h, 002h, 085h, 0C0h, 0C7h, 044h, 024h, 008h, 000h, 000h, 000h, 000h, 00Fh, 086h, 0F1h, 000h
    db 000h, 000h, 08Bh, 04Ch, 024h, 014h, 08Bh, 0C6h, 08Bh, 031h, 055h, 057h, 089h, 074h, 024h, 014h
    db 089h, 044h, 024h, 01Ch, 0EBh, 00Ah, 08Bh, 074h, 024h, 014h, 08Dh, 09Bh, 000h, 000h, 000h, 000h
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 002h, 083h, 0C0h, 004h, 08Bh, 000h, 085h, 0C0h, 074h, 006h, 00Fh
    db 0B7h, 068h, 004h, 0EBh, 002h, 033h, 0EDh, 085h, 0C0h, 08Dh, 078h, 008h, 075h, 005h, 0BFh
    dd ?Rva006A16B0Empty@@3PADA
    db 085h, 0F6h, 074h, 009h, 00Fh, 0B7h, 056h, 004h, 083h, 0C6h, 008h, 0EBh, 007h, 033h, 0D2h, 0BEh
    dd ?Rva006A16B0Empty@@3PADA
    db 03Bh, 0D5h, 08Bh, 0CAh, 07Ch, 002h, 08Bh, 0CDh, 033h, 0C0h, 0F3h, 0A6h, 074h, 005h, 01Bh, 0C0h
    db 083h, 0D8h, 0FFh, 033h, 0FFh, 03Bh, 0C7h, 075h, 008h, 02Bh, 0D5h, 08Bh, 0C2h, 03Bh, 0C7h, 074h
    db 031h, 08Bh, 04Bh, 02Ch, 08Bh, 07Bh, 028h, 08Bh, 044h, 024h, 010h, 08Bh, 06Ch, 024h, 01Ch, 02Bh
    db 0CFh, 040h, 083h, 0C5h, 004h, 0C1h, 0F9h, 002h, 03Bh, 0C1h, 089h, 044h, 024h, 010h, 089h, 06Ch
    db 024h, 01Ch, 00Fh, 082h, 077h, 0FFh, 0FFh, 0FFh, 05Fh, 05Dh, 05Eh, 05Bh, 083h, 0C4h, 008h, 0C2h
    db 004h, 000h, 08Bh, 043h, 004h, 03Bh, 0C7h, 074h, 034h, 08Bh, 04Bh, 028h, 08Bh, 054h, 024h, 010h
    db 03Bh, 004h, 091h, 074h, 028h, 08Bh, 043h, 024h, 03Bh, 0C7h, 074h, 01Bh, 08Bh, 0F0h, 03Bh, 0F7h
    db 074h, 015h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 050h, 040h, 0FFh, 04Eh, 004h, 075h, 006h, 08Bh, 016h
    db 08Bh, 0CEh, 0FFh, 012h, 089h, 07Bh, 024h, 089h, 07Bh, 024h, 089h, 07Bh, 004h, 08Bh, 043h, 028h
    db 08Bh, 04Ch, 024h, 010h, 08Bh, 014h, 088h, 05Fh, 089h, 053h, 004h, 05Dh, 05Eh, 05Bh, 083h, 0C4h
    db 008h, 0C2h, 004h, 000h
?d_003c88e0@@YAXXZ ENDP
_TEXT$d007c88e0 ENDS
_TEXT SEGMENT

; ghidra: FUN_007c8a50  retail @ 0x003C8A50 size 214
public ?d_003c8a50@@YAXXZ
?d_003c8a50@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0ECh, 0Ch, 85h, 0C0h, 75h, 06h, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
    db 8Bh, 48h, 30h, 53h, 55h, 8Bh, 68h, 34h, 2Bh, 0E9h, 0C1h, 0FDh, 02h, 85h, 0EDh, 56h
    db 57h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h, 4Ch, 24h, 18h, 0Fh, 86h, 82h
    db 00h, 00h, 00h, 8Bh, 44h, 24h, 20h, 8Bh, 30h, 89h, 74h, 24h, 14h, 89h, 4Ch, 24h
    db 20h, 0EBh, 04h, 8Bh, 74h, 24h, 14h, 8Bh, 4Ch, 24h, 20h, 8Bh, 01h, 83h, 0C0h, 04h
    db 8Bh, 00h, 85h, 0C0h, 74h, 06h, 0Fh, 0B7h, 58h, 04h, 0EBh, 02h, 33h, 0DBh, 85h, 0C0h
    db 8Dh, 78h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h, 85h, 0F6h, 74h, 09h, 0Fh, 0B7h
    db 56h, 04h, 83h, 0C6h, 08h, 0EBh, 07h, 33h, 0D2h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0D3h
    db 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h
    db 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 74h, 24h, 8Bh, 44h, 24h
    db 10h, 8Bh, 54h, 24h, 20h, 40h, 83h, 0C2h, 04h, 3Bh, 0C5h, 89h, 44h, 24h, 10h, 89h
    db 54h, 24h, 20h, 72h, 8Eh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h
    db 00h, 8Bh, 54h, 24h, 18h, 8Bh, 44h, 24h, 10h, 8Bh, 04h, 82h, 5Fh, 5Eh, 5Dh, 5Bh
    db 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_003c8a50@@YAXXZ ENDP

; ghidra: FUN_007c8b60  retail @ 0x003C8B60 size 31
public ?d_003c8b60@@YAXXZ
?d_003c8b60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 0E8h, 0A3h, 33h, 0C6h, 0FFh, 85h, 0C0h, 75h, 05h, 32h, 0C0h
    db 0C2h, 08h, 00h, 0C6h, 80h, 0A8h, 00h, 00h, 00h, 01h, 0B0h, 01h, 0C2h, 08h, 00h
?d_003c8b60@@YAXXZ ENDP

; ghidra: FUN_007c8b90  retail @ 0x003C8B90 size 163
public ?d_003c8b90@@YAXXZ
?d_003c8b90@@YAXXZ PROC
    db 83h, 0ECh, 18h, 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 85h, 0C0h, 8Bh, 0Dh, 5Ch, 4Ch, 2Fh
    db 01h, 74h, 09h, 8Bh, 01h, 6Ah, 05h, 0FFh, 50h, 38h, 0EBh, 07h, 8Bh, 11h, 6Ah, 01h
    db 0FFh, 52h, 38h, 0A1h, 28h, 10h, 2Fh, 01h, 8Bh, 48h, 20h, 89h, 4Ch, 24h, 08h, 8Ah
    db 4Eh, 10h, 84h, 0C9h, 8Bh, 50h, 24h, 89h, 54h, 24h, 0Ch, 75h, 31h, 68h, 00h, 00h
    db 80h, 3Fh, 6Ah, 00h, 6Ah, 0FFh, 51h, 89h, 64h, 24h, 14h, 8Bh, 0CCh, 68h, 54h, 6Eh
    db 33h, 01h, 0E8h, 19h, 0F8h, 4Bh, 00h, 8Bh, 0Dh, 5Ch, 4Ch, 2Fh, 01h, 0E8h, 0F7h, 0BAh
    db 0C6h, 0FFh, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 18h, 0C3h, 8Ah, 48h
    db 1Ch, 84h, 0C9h, 74h, 29h, 8Bh, 0Dh, 48h, 70h, 2Fh, 01h, 8Bh, 01h, 8Dh, 54h, 24h
    db 10h, 52h, 8Dh, 54h, 24h, 0Ch, 52h, 0FFh, 50h, 20h, 8Dh, 44h, 24h, 10h, 50h, 8Bh
    db 0CEh, 0E8h, 2Ah, 0D5h, 0C7h, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 0F0h, 50h, 0C4h, 0FFh, 5Eh, 83h
    db 0C4h, 18h, 0C3h
?d_003c8b90@@YAXXZ ENDP

; ghidra: FUN_007c8c60  retail @ 0x003C8C60 size 190
public ?d_003c8c60@@YAXXZ
?d_003c8c60@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 68h, 44h, 0E0h, 0Eh, 01h, 8Bh, 0CFh, 0E8h
    db 0A6h, 23h, 0C8h, 0FFh, 85h, 0C0h, 75h, 6Bh, 8Bh, 76h, 04h, 8Bh, 46h, 30h, 8Bh, 4Eh
    db 34h, 83h, 0C6h, 30h, 2Bh, 0C8h, 0C1h, 0F9h, 02h, 33h, 0FFh, 85h, 0C9h, 0Fh, 86h, 86h
    db 00h, 00h, 00h, 53h, 8Bh, 5Ch, 24h, 20h, 55h, 8Bh, 6Ch, 24h, 20h, 8Dh, 49h, 00h
    db 8Bh, 0Ch, 0B8h, 8Ah, 81h, 0A8h, 00h, 00h, 00h, 84h, 0C0h, 74h, 20h, 8Bh, 54h, 24h
    db 30h, 8Bh, 44h, 24h, 2Ch, 52h, 8Bh, 54h, 24h, 2Ch, 50h, 8Bh, 44h, 24h, 24h, 52h
    db 8Bh, 54h, 24h, 24h, 53h, 55h, 50h, 52h, 0E8h, 0Fh, 77h, 0C6h, 0FFh, 8Bh, 06h, 8Bh
    db 4Eh, 04h, 2Bh, 0C8h, 47h, 0C1h, 0F9h, 02h, 3Bh, 0F9h, 72h, 0C4h, 5Dh, 5Bh, 5Fh, 5Eh
    db 0C2h, 20h, 00h, 57h, 8Bh, 0CEh, 0E8h, 22h, 32h, 0C6h, 0FFh, 85h, 0C0h, 74h, 2Ah, 8Bh
    db 54h, 24h, 28h, 8Bh, 4Ch, 24h, 24h, 52h, 8Bh, 54h, 24h, 24h, 51h, 8Bh, 4Ch, 24h
    db 24h, 52h, 8Bh, 54h, 24h, 24h, 51h, 8Bh, 4Ch, 24h, 24h, 52h, 8Bh, 54h, 24h, 24h
    db 51h, 52h, 8Bh, 0C8h, 0E8h, 0C3h, 76h, 0C6h, 0FFh, 5Fh, 5Eh, 0C2h, 20h, 00h
?d_003c8c60@@YAXXZ ENDP

; ghidra: FUN_007c9220  retail @ 0x003C9220 size 100
public ?d_003c9220@@YAXXZ
?d_003c9220@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 94h, 0E3h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 98h
    db 0E3h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 20h, 0E4h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 1Ch, 0E4h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 0B4h, 4Dh, 0C4h, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 0F4h, 0FEh, 0C7h, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_003c9220@@YAXXZ ENDP

; ghidra: FUN_007c92a0  retail @ 0x003C92A0 size 100
public ?d_003c92a0@@YAXXZ
?d_003c92a0@@YAXXZ PROC
    db 83h, 0ECh, 20h, 56h, 8Bh, 35h, 94h, 0E3h, 2Bh, 01h, 85h, 0F6h, 75h, 09h, 0A1h, 98h
    db 0E3h, 2Bh, 01h, 85h, 0C0h, 74h, 36h, 53h, 8Bh, 1Dh, 20h, 0E4h, 2Bh, 01h, 57h, 8Bh
    db 3Dh, 1Ch, 0E4h, 2Bh, 01h, 8Dh, 44h, 24h, 34h, 50h, 8Dh, 4Ch, 24h, 34h, 51h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 0F7h, 0D6h, 0C7h, 0FFh, 8Dh, 44h, 24h, 0Ch, 99h, 52h, 50h, 53h
    db 57h, 0FFh, 0D6h, 83h, 0C4h, 10h, 5Fh, 5Bh, 5Eh, 83h, 0C4h, 20h, 0C3h, 8Bh, 54h, 24h
    db 2Ch, 8Bh, 44h, 24h, 28h, 52h, 50h, 0E8h, 0C9h, 14h, 0C6h, 0FFh, 83h, 0C4h, 08h, 5Eh
    db 83h, 0C4h, 20h, 0C3h
?d_003c92a0@@YAXXZ ENDP

; ghidra: FUN_007c9470  retail @ 0x003C9470 size 153
public ?d_003c9470@@YAXXZ
?d_003c9470@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 08h, 56h, 50h, 8Bh, 0F1h, 0E8h, 8Dh, 2Ah, 0C6h, 0FFh
    db 85h, 0C0h, 74h, 4Ch, 8Ah, 48h, 74h, 84h, 0C9h, 74h, 23h, 8Dh, 4Ch, 24h, 04h, 51h
    db 8Bh, 0C8h, 0E8h, 0EBh, 0B4h, 0C6h, 0FFh, 8Bh, 10h, 8Bh, 4Ch, 24h, 14h, 89h, 11h, 8Bh
    db 40h, 04h, 89h, 41h, 04h, 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 8Bh, 40h
    db 28h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh
    db 4Eh, 24h, 8Bh, 11h, 6Ah, 00h, 50h, 0FFh, 52h, 7Ch, 8Bh, 0F0h, 85h, 0F6h, 75h, 09h
    db 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 90h, 04h
    db 01h, 00h, 00h, 0D9h, 40h, 04h, 0D9h, 00h, 8Bh, 44h, 24h, 14h, 0D9h, 18h, 0D9h, 58h
    db 04h, 8Bh, 46h, 04h, 48h, 89h, 46h, 04h, 75h, 06h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h
    db 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_003c9470@@YAXXZ ENDP

; ghidra: FUN_007c9530  retail @ 0x003C9530 size 98
public ?d_003c9530@@YAXXZ
?d_003c9530@@YAXXZ PROC
    db 83h, 0ECh, 08h, 56h, 57h, 8Bh, 7Ch, 24h, 14h, 57h, 8Bh, 0F1h, 0E8h, 0CCh, 29h, 0C6h
    db 0FFh, 85h, 0C0h, 75h, 0Ah, 5Fh, 32h, 0C0h, 5Eh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 8Ah
    db 88h, 8Ch, 00h, 00h, 00h, 84h, 0C9h, 74h, 24h, 8Dh, 4Ch, 24h, 08h, 51h, 8Bh, 0C8h
    db 0E8h, 95h, 0E8h, 0C4h, 0FFh, 8Bh, 10h, 8Bh, 4Ch, 24h, 18h, 89h, 11h, 8Bh, 40h, 04h
    db 5Fh, 89h, 41h, 04h, 0B0h, 01h, 5Eh, 83h, 0C4h, 08h, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h
    db 18h, 51h, 57h, 8Bh, 0CEh, 0E8h, 30h, 0A9h, 0C6h, 0FFh, 5Fh, 5Eh, 83h, 0C4h, 08h, 0C2h
    db 08h, 00h
?d_003c9530@@YAXXZ ENDP

; ghidra: FUN_007c97b0  retail @ 0x003C97B0 size 366
public ?d_003c97b0@@YAXXZ
?d_003c97b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Bh, 0F2h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 8Bh, 46h
    db 34h, 2Bh, 46h, 30h, 0C1h, 0F8h, 02h, 33h, 0FFh, 85h, 0C0h, 0C7h, 44h, 24h, 14h, 09h
    db 00h, 00h, 00h, 76h, 1Eh, 8Bh, 46h, 30h, 8Bh, 0Ch, 0B8h, 85h, 0C9h, 74h, 06h, 8Bh
    db 11h, 6Ah, 01h, 0FFh, 12h, 8Bh, 46h, 34h, 2Bh, 46h, 30h, 47h, 0C1h, 0F8h, 02h, 3Bh
    db 0F8h, 72h, 0E2h, 8Bh, 46h, 34h, 3Bh, 0C0h, 8Bh, 4Eh, 30h, 75h, 04h, 8Bh, 0C1h, 0EBh
    db 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch, 94h, 35h, 01h, 83h, 0C4h
    db 0Ch, 03h, 0C7h, 89h, 46h, 34h, 8Bh, 7Eh, 3Ch, 85h, 0FFh, 74h, 10h, 8Bh, 0CFh, 0E8h
    db 16h, 36h, 0C5h, 0FFh, 57h, 0E8h, 76h, 86h, 4Bh, 00h, 83h, 0C4h, 04h, 8Dh, 4Eh, 54h
    db 0C6h, 44h, 24h, 14h, 08h, 0E8h, 0F6h, 0E0h, 4Bh, 00h, 8Dh, 4Eh, 40h, 0C6h, 44h, 24h
    db 14h, 07h, 0E8h, 47h, 87h, 0C5h, 0FFh, 8Bh, 4Eh, 30h, 85h, 0C9h, 0C6h, 44h, 24h, 14h
    db 06h, 74h, 27h, 8Bh, 46h, 38h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h
    db 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 35h, 86h, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah
    db 50h, 51h, 0E8h, 69h, 4Dh, 46h, 00h, 83h, 0C4h, 08h, 8Dh, 4Eh, 2Ch, 0C6h, 44h, 24h
    db 14h, 05h, 0E8h, 0A9h, 0E0h, 4Bh, 00h, 8Bh, 4Eh, 20h, 85h, 0C9h, 0C6h, 44h, 24h, 14h
    db 04h, 74h, 27h, 8Bh, 46h, 28h, 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh, 80h
    db 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0F5h, 85h, 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah
    db 50h, 51h, 0E8h, 29h, 4Dh, 46h, 00h, 83h, 0C4h, 08h, 8Dh, 4Eh, 14h, 0C6h, 44h, 24h
    db 14h, 03h, 0E8h, 69h, 0E0h, 4Bh, 00h, 8Dh, 4Eh, 10h, 0C6h, 44h, 24h, 14h, 02h, 0E8h
    db 5Ch, 0E0h, 4Bh, 00h, 8Dh, 4Eh, 0Ch, 0C6h, 44h, 24h, 14h, 01h, 0E8h, 4Fh, 0E0h, 4Bh
    db 00h, 8Dh, 4Eh, 04h, 0C6h, 44h, 24h, 14h, 00h, 0E8h, 42h, 0E0h, 4Bh, 00h, 8Bh, 0CEh
    db 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 33h, 0E0h, 4Bh, 00h, 8Bh, 4Ch, 24h
    db 0Ch, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_003c97b0@@YAXXZ ENDP

; ghidra: FUN_007c9980  retail @ 0x003C9980 size 241
public ?d_003c9980@@YAXXZ
?d_003c9980@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 64h, 0F2h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 53h, 55h, 8Bh, 6Ch, 24h, 24h, 56h, 57h
    db 33h, 0DBh, 53h, 8Bh, 0CDh, 89h, 5Ch, 24h, 18h, 0E8h, 0C2h, 6Fh, 48h, 00h, 68h, 0F4h
    db 00h, 00h, 00h, 8Bh, 0F8h, 0E8h, 76h, 85h, 4Bh, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h, 89h
    db 74h, 24h, 18h, 85h, 0F6h, 89h, 5Ch, 24h, 24h, 74h, 28h, 57h, 8Dh, 4Ch, 24h, 14h
    db 0E8h, 0EBh, 0F1h, 4Bh, 00h, 8Dh, 44h, 24h, 10h, 0BBh, 01h, 00h, 00h, 00h, 50h, 8Bh
    db 0CEh, 0C6h, 44h, 24h, 28h, 01h, 89h, 5Ch, 24h, 18h, 0E8h, 0D5h, 0F2h, 0C3h, 0FFh, 8Bh
    db 0F0h, 0EBh, 02h, 33h, 0F6h, 0F6h, 0C3h, 01h, 89h, 74h, 24h, 14h, 0C7h, 44h, 24h, 24h
    db 0FFh, 0FFh, 0FFh, 0FFh, 74h, 09h, 8Dh, 4Ch, 24h, 10h, 0E8h, 31h, 0DFh, 4Bh, 00h, 55h
    db 8Bh, 0CEh, 0E8h, 86h, 0D5h, 0C6h, 0FFh, 8Bh, 4Ch, 24h, 30h, 8Bh, 41h, 34h, 8Bh, 51h
    db 38h, 83h, 0C1h, 30h, 3Bh, 0C2h, 74h, 22h, 85h, 0C0h, 74h, 02h, 89h, 30h, 8Bh, 41h
    db 04h, 5Fh, 5Eh, 83h, 0C0h, 04h, 5Dh, 89h, 41h, 04h, 5Bh, 8Bh, 4Ch, 24h, 0Ch, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C3h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h
    db 24h, 38h, 52h, 8Dh, 54h, 24h, 20h, 52h, 50h, 0E8h, 38h, 6Bh, 0C4h, 0FFh, 8Bh, 4Ch
    db 24h, 1Ch, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h
    db 0C3h
?d_003c9980@@YAXXZ ENDP

; ghidra: FUN_007c9b60  retail @ 0x003C9B60 size 261
public ?d_003c9b60@@YAXXZ
?d_003c9b60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A4h, 0F2h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 8Bh, 4Ch, 24h, 20h, 53h, 55h, 56h, 33h
    db 0DBh, 89h, 5Ch, 24h, 14h, 0A1h, 28h, 10h, 2Fh, 01h, 8Bh, 68h, 28h, 57h, 53h, 0E8h
    db 0DCh, 6Dh, 48h, 00h, 6Ah, 58h, 8Bh, 0F8h, 0E8h, 93h, 83h, 4Bh, 00h, 8Bh, 0F0h, 83h
    db 0C4h, 04h, 89h, 74h, 24h, 1Ch, 85h, 0F6h, 89h, 5Ch, 24h, 28h, 74h, 28h, 57h, 8Dh
    db 4Ch, 24h, 18h, 0E8h, 08h, 0F0h, 4Bh, 00h, 8Dh, 4Ch, 24h, 14h, 51h, 0BBh, 01h, 00h
    db 00h, 00h, 8Bh, 0CEh, 0C6h, 44h, 24h, 2Ch, 01h, 89h, 5Ch, 24h, 1Ch, 0E8h, 5Ch, 0C4h
    db 0C7h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 0F6h, 0C3h, 01h, 89h, 74h, 24h, 18h, 0C7h
    db 44h, 24h, 28h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 09h, 8Dh, 4Ch, 24h, 14h, 0E8h, 4Eh, 0DDh
    db 4Bh, 00h, 8Bh, 4Ch, 24h, 30h, 68h, 48h, 0DCh, 0Eh, 01h, 56h, 0E8h, 9Fh, 84h, 48h
    db 00h, 8Bh, 0CEh, 0E8h, 86h, 4Ch, 0C6h, 0FFh, 8Bh, 0CEh, 0E8h, 75h, 0FDh, 0C4h, 0FFh, 8Bh
    db 45h, 2Ch, 8Bh, 55h, 30h, 3Bh, 0C2h, 8Dh, 4Dh, 28h, 74h, 22h, 85h, 0C0h, 74h, 02h
    db 89h, 30h, 8Bh, 41h, 04h, 5Fh, 5Eh, 83h, 0C0h, 04h, 5Dh, 89h, 41h, 04h, 5Bh, 8Bh
    db 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C3h, 6Ah, 01h
    db 6Ah, 01h, 8Dh, 54h, 24h, 1Bh, 52h, 8Dh, 54h, 24h, 24h, 52h, 50h, 0E8h, 0ADh, 04h
    db 0C5h, 0FFh, 8Bh, 4Ch, 24h, 20h, 5Fh, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 1Ch, 0C3h
?d_003c9b60@@YAXXZ ENDP

; ghidra: FUN_007c9cb0  retail @ 0x003C9CB0 size 230
public ?d_003c9cb0@@YAXXZ
?d_003c9cb0@@YAXXZ PROC
    db 83h, 0ECh, 08h, 53h, 8Bh, 5Ch, 24h, 10h, 56h, 57h, 53h, 8Bh, 0F9h, 0E8h, 4Bh, 22h
    db 0C6h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 89h, 74h, 24h, 18h, 0Fh, 84h, 0BDh, 00h, 00h, 00h
    db 8Bh, 44h, 24h, 1Ch, 85h, 0C0h, 8Dh, 8Eh, 0B8h, 00h, 00h, 00h, 74h, 08h, 50h, 0E8h
    db 0ACh, 0DFh, 4Bh, 00h, 0EBh, 05h, 0E8h, 55h, 0DCh, 4Bh, 00h, 8Bh, 44h, 24h, 24h, 85h
    db 0C0h, 74h, 11h, 8Bh, 08h, 89h, 8Eh, 0BCh, 00h, 00h, 00h, 8Bh, 50h, 04h, 89h, 96h
    db 0C0h, 00h, 00h, 00h, 8Bh, 47h, 18h, 8Bh, 57h, 1Ch, 3Bh, 0C2h, 8Dh, 4Fh, 14h, 74h
    db 0Ch, 85h, 0C0h, 74h, 02h, 89h, 30h, 83h, 41h, 04h, 04h, 0EBh, 14h, 6Ah, 01h, 6Ah
    db 01h, 8Dh, 54h, 24h, 20h, 52h, 8Dh, 54h, 24h, 24h, 52h, 50h, 0E8h, 65h, 68h, 0C4h
    db 0FFh, 8Bh, 44h, 24h, 20h, 85h, 0C0h, 74h, 0Fh, 8Bh, 08h, 8Bh, 50h, 04h, 89h, 4Ch
    db 24h, 0Ch, 89h, 54h, 24h, 10h, 0EBh, 0Dh, 8Dh, 44h, 24h, 0Ch, 50h, 53h, 8Bh, 0CFh
    db 0E8h, 65h, 0A1h, 0C6h, 0FFh, 8Bh, 4Ch, 24h, 0Ch, 89h, 8Eh, 0E0h, 00h, 00h, 00h, 8Bh
    db 54h, 24h, 10h, 89h, 96h, 0E4h, 00h, 00h, 00h, 8Bh, 5Fh, 20h, 43h, 89h, 5Fh, 20h
    db 6Ah, 00h, 8Dh, 44h, 24h, 10h, 50h, 8Bh, 0CBh, 8Bh, 0FBh, 89h, 0BEh, 0ACh, 00h, 00h
    db 00h, 51h, 8Bh, 0Dh, 6Ch, 70h, 2Fh, 01h, 0E8h, 75h, 41h, 0C5h, 0FFh, 5Fh, 5Eh, 5Bh
    db 83h, 0C4h, 08h, 0C2h, 10h, 00h
?d_003c9cb0@@YAXXZ ENDP

; ghidra: FUN_007c9dd0  retail @ 0x003C9DD0 size 208
public ?d_003c9dd0@@YAXXZ
?d_003c9dd0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 46h, 04h, 3Bh, 0C0h, 8Bh, 0D9h, 8Bh, 0Eh, 57h
    db 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 04h, 8Ah, 43h, 10h, 84h, 0C0h
    db 75h, 08h, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 0C2h, 04h, 00h, 8Bh, 5Bh, 04h, 8Bh, 43h, 30h
    db 8Bh, 4Bh, 34h, 83h, 0C3h, 30h, 2Bh, 0C8h, 55h, 0C1h, 0F9h, 02h, 33h, 0EDh, 85h, 0C9h
    db 76h, 71h, 0EBh, 0Ch, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h, 0EBh, 03h, 8Dh, 49h, 00h
    db 8Dh, 3Ch, 0ADh, 00h, 00h, 00h, 00h, 8Bh, 14h, 07h, 8Ah, 8Ah, 0A8h, 00h, 00h, 00h
    db 84h, 0C9h, 74h, 40h, 8Bh, 0Dh, 28h, 10h, 2Fh, 01h, 8Bh, 0C2h, 50h, 0E8h, 0BDh, 0Dh
    db 0C8h, 0FFh, 84h, 0C0h, 74h, 2Eh, 8Bh, 03h, 8Bh, 4Eh, 04h, 8Bh, 56h, 08h, 03h, 0C7h
    db 3Bh, 0CAh, 74h, 0Eh, 85h, 0C9h, 74h, 04h, 8Bh, 10h, 89h, 11h, 83h, 46h, 04h, 04h
    db 0EBh, 12h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 1Ch, 52h, 50h, 51h, 8Bh, 0CEh, 0E8h
    db 12h, 67h, 0C4h, 0FFh, 8Bh, 03h, 8Bh, 4Bh, 04h, 2Bh, 0C8h, 45h, 0C1h, 0F9h, 02h, 3Bh
    db 0E9h, 72h, 9Dh, 8Bh, 1Eh, 8Bh, 56h, 04h, 2Bh, 0D3h, 33h, 0C0h, 5Dh, 0C1h, 0FAh, 02h
?d_003c9dd0@@YAXXZ ENDP

; ghidra: FUN_007c9ef0  retail @ 0x003C9EF0 size 395
public ?d_003c9ef0@@YAXXZ
?d_003c9ef0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D0h, 0F2h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 10h, 53h, 56h, 8Bh, 74h, 24h, 28h, 8Bh, 06h
    db 8Bh, 0D9h, 57h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 14h, 01h, 0C6h
    db 44h, 24h, 15h, 01h, 0FFh, 50h, 28h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 84h, 0C0h
    db 0Fh, 84h, 0CBh, 00h, 00h, 00h, 8Bh, 06h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0FFh
    db 50h, 78h, 8Bh, 44h, 24h, 14h, 33h, 0FFh, 3Bh, 0C7h, 89h, 7Ch, 24h, 10h, 0Fh, 8Eh
    db 13h, 01h, 00h, 00h, 55h, 89h, 7Ch, 24h, 30h, 8Bh, 16h, 8Dh, 44h, 24h, 30h, 50h
    db 8Bh, 0CEh, 89h, 7Ch, 24h, 2Ch, 0FFh, 52h, 68h, 8Dh, 4Ch, 24h, 30h, 51h, 8Bh, 0CBh
    db 0E8h, 98h, 1Fh, 0C6h, 0FFh, 8Bh, 0E8h, 3Bh, 0EFh, 89h, 6Ch, 24h, 1Ch, 74h, 47h, 8Bh
    db 85h, 0ACh, 00h, 00h, 00h, 8Bh, 0Dh, 6Ch, 70h, 2Fh, 01h, 57h, 8Dh, 95h, 0E0h, 00h
    db 00h, 00h, 52h, 50h, 0E8h, 69h, 3Fh, 0C5h, 0FFh, 8Bh, 43h, 18h, 8Bh, 53h, 1Ch, 3Bh
    db 0C2h, 8Dh, 4Bh, 14h, 74h, 0Ch, 3Bh, 0C7h, 74h, 02h, 89h, 28h, 83h, 41h, 04h, 04h
    db 0EBh, 14h, 6Ah, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 38h, 52h, 8Dh, 54h, 24h, 28h, 52h
    db 50h, 0E8h, 0D0h, 65h, 0C4h, 0FFh, 8Dh, 4Ch, 24h, 30h, 0C7h, 44h, 24h, 28h, 0FFh, 0FFh
    db 0FFh, 0FFh, 0E8h, 69h, 0D9h, 4Bh, 00h, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 18h, 40h
    db 3Bh, 0C1h, 89h, 44h, 24h, 14h, 0Fh, 8Ch, 69h, 0FFh, 0FFh, 0FFh, 5Dh, 5Fh, 5Eh, 5Bh
    db 8Bh, 4Ch, 24h, 10h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h
    db 00h, 8Bh, 43h, 18h, 8Bh, 7Bh, 14h, 8Bh, 16h, 2Bh, 0C7h, 0C1h, 0F8h, 02h, 89h, 44h
    db 24h, 0Ch, 8Dh, 44h, 24h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 52h, 78h, 8Bh, 44h, 24h, 0Ch
    db 33h, 0FFh, 3Bh, 0C7h, 7Eh, 41h, 8Bh, 43h, 14h, 8Bh, 04h, 0B8h, 83h, 0C0h, 04h, 50h
    db 8Dh, 4Ch, 24h, 1Ch, 0E8h, 27h, 0DBh, 4Bh, 00h, 8Bh, 16h, 8Dh, 44h, 24h, 18h, 50h
    db 8Bh, 0CEh, 0C7h, 44h, 24h, 28h, 01h, 00h, 00h, 00h, 0FFh, 52h, 68h, 8Dh, 4Ch, 24h
    db 18h, 0C7h, 44h, 24h, 24h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0E2h, 0D8h, 4Bh, 00h, 8Bh, 44h
    db 24h, 0Ch, 47h, 3Bh, 0F8h, 7Ch, 0BFh, 8Bh, 4Ch, 24h, 1Ch, 5Fh, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C2h, 04h, 00h
?d_003c9ef0@@YAXXZ ENDP

; ghidra: FUN_007ca0e0  retail @ 0x003CA0E0 size 685
_TEXT ENDS
_TEXT$d007ca0e0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x007CA0E0 size 685
public ?d_003ca0e0@@YAXXZ
?d_003ca0e0@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0101F2F8
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 00Ch, 053h, 055h, 056h, 08Bh, 074h, 024h, 028h, 08Bh, 006h, 057h, 08Bh, 0F9h, 08Dh, 04Ch, 024h
    db 010h, 051h, 08Bh, 0CEh, 0C6h, 044h, 024h, 014h, 001h, 0C6h, 044h, 024h, 015h, 002h, 0FFh, 050h
    db 028h, 08Bh, 016h, 08Dh, 06Fh, 010h, 055h, 08Bh, 0CEh, 0FFh, 092h, 08Ch, 000h, 000h, 000h, 08Bh
    db 006h, 08Dh, 04Fh, 020h, 051h, 08Bh, 0CEh, 0FFh, 050h, 078h, 08Ah, 044h, 024h, 011h, 033h, 0DBh
    db 03Ch, 002h, 072h, 024h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 052h, 004h, 084h, 0C0h, 074h, 019h, 08Bh
    db 00Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 03Bh, 0CBh, 074h, 00Fh, 08Ah, 041h, 02Ch, 03Ah, 0C3h, 074h, 008h, 038h, 059h, 02Dh, 075h, 003h
    db 088h, 05Dh, 000h, 089h, 05Ch, 024h, 02Ch, 08Bh, 006h, 08Bh, 0CEh, 089h, 05Ch, 024h, 024h, 0FFh
    db 050h, 004h, 084h, 0C0h, 074h, 01Dh, 08Dh, 044h, 024h, 02Ch, 089h, 05Fh, 004h, 08Bh, 016h, 050h
    db 08Bh, 0CEh, 0FFh, 052h, 068h, 08Dh, 04Ch, 024h, 02Ch, 051h, 08Bh, 0CFh
    call ?j_00045b88@@YAXXZ
    db 0EBh, 01Ch, 08Bh, 047h, 004h, 083h, 0C0h, 004h, 050h, 08Dh, 04Ch, 024h, 030h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Bh, 016h, 08Dh, 044h, 024h, 02Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 08Bh, 016h, 08Bh, 0CEh
    db 0FFh, 052h, 004h, 084h, 0C0h, 08Bh, 006h, 00Fh, 084h, 066h, 001h, 000h, 000h, 08Dh, 04Ch, 024h
    db 02Ch, 051h, 08Bh, 0CEh, 0FFh, 050h, 068h, 08Dh, 054h, 024h, 02Ch, 052h, 08Bh, 0CFh
    call ?j_0002bf0d@@YAXXZ
    db 080h, 07Ch, 024h, 011h, 002h, 089h, 047h, 008h, 072h, 03Ah, 03Bh, 0C3h, 075h, 036h, 08Bh, 02Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 03Bh, 0EBh, 074h, 02Ch, 038h, 05Dh, 02Ch, 074h, 027h, 08Bh, 0CDh
    call ?j_0000bb81@@YAXXZ
    db 084h, 0C0h, 075h, 01Ch, 08Dh, 045h, 030h, 050h, 08Dh, 04Ch, 024h, 030h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 08Dh, 044h, 024h, 02Ch, 050h, 08Bh, 0CFh
    call ?j_0002bf0d@@YAXXZ
    db 089h, 047h, 008h, 056h, 08Bh, 0CFh
    call ?j_0003ac9c@@YAXXZ
    db 08Bh, 06Fh, 008h, 03Bh, 0EBh, 00Fh, 084h, 036h, 001h, 000h, 000h, 08Bh, 095h, 09Ch, 000h, 000h
    db 000h, 08Bh, 08Dh, 0A0h, 000h, 000h, 000h, 02Bh, 0CAh, 0B8h, 039h, 08Eh, 0E3h, 038h, 0F7h, 0E9h
    db 0C1h, 0FAh, 003h, 08Bh, 0CAh, 0C1h, 0E9h, 01Fh, 003h, 0CAh, 074h, 056h, 08Bh, 00Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 03Bh, 0CBh, 074h, 04Ch, 038h, 059h, 02Ch, 074h, 047h
    call ?j_0000bb81@@YAXXZ
    db 084h, 0C0h, 075h, 03Eh, 08Dh, 085h, 0B8h, 000h, 000h, 000h, 050h, 08Dh, 04Ch, 024h, 018h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd ?Glo012F1028@@3PAVGlo012F1028Type@@A
    db 08Dh, 054h, 024h, 014h, 052h, 0C6h, 044h, 024h, 028h, 001h
    call ?j_00032a56@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 08Bh, 0E8h, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 03Bh, 0EBh, 074h, 006h, 083h, 0C5h, 040h, 055h, 0EBh, 005h, 068h
    dd ?BfmeDefeatScreenTable@@3PAEA
    db 08Bh, 04Fh, 008h
    call ?j_00002e46@@YAXXZ
    db 039h, 01Dh
    dd g_Va012F7090
    db 00Fh, 084h, 0A6h, 000h, 000h, 000h, 08Bh, 047h, 008h, 083h, 0C0h, 008h, 08Bh, 000h, 03Bh, 0C3h
    db 074h, 005h, 083h, 0C0h, 008h, 0EBh, 005h, 0B8h
    dd ?Rva006A16B0Empty@@3PADA
    db 089h, 05Ch, 024h, 014h, 050h, 050h, 051h, 089h, 064h, 024h, 024h, 08Bh, 0CCh, 068h
    dd g_Va010EE048
    db 0C6h, 044h, 024h, 034h, 002h
    call ??0?$StringBase@D@@AAE@PBD@Z
    db 08Dh, 044h, 024h, 020h, 050h
    call ?format@AsciiString@@QAAXV1@ZZ
    db 083h, 0C4h, 00Ch, 08Dh, 054h, 024h, 018h, 089h, 064h, 024h, 01Ch, 08Bh, 0CCh, 052h
    call ??0?$StringBase@D@@AAE@ABV0@@Z
    db 08Bh, 00Dh
    dd g_Va012F7090
    call ?j_0001b5db@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 088h, 05Ch, 024h, 024h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 0EBh, 03Dh, 08Bh, 0CEh, 0FFh, 050h, 008h, 084h, 0C0h, 074h, 034h, 08Bh, 047h, 008h, 03Bh, 0C3h
    db 08Dh, 04Ch, 024h, 02Ch, 074h, 00Bh, 083h, 0C0h, 004h, 050h
    call ?set@?$StringBase@D@@QAEXABV1@@Z
    db 0EBh, 00Ah, 068h
    dd ??_7Rva007F01B0@@6B@
    call ?j_00028bb9@@YAXXZ
    db 08Bh, 016h, 08Dh, 044h, 024h, 02Ch, 050h, 08Bh, 0CEh, 0FFh, 052h, 068h, 056h, 08Bh, 0CFh
    call ?j_0003ac9c@@YAXXZ
    db 056h, 08Bh, 0CFh
    call ?j_0004704b@@YAXXZ
    db 08Dh, 04Ch, 024h, 02Ch, 0C7h, 044h, 024h, 024h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 08Bh, 04Ch, 024h, 01Ch, 05Fh, 05Eh, 05Dh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Bh, 083h
    db 0C4h, 018h, 0C2h, 004h, 000h
?d_003ca0e0@@YAXXZ ENDP
_TEXT$d007ca0e0 ENDS
_TEXT SEGMENT

; ghidra: FUN_007ca480  retail @ 0x003CA480 size 265
public ?d_003ca480@@YAXXZ
?d_003ca480@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Eh, 0F3h, 01h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 0C7h
    db 06h, 10h, 0E0h, 0Eh, 01h, 8Bh, 46h, 2Ch, 2Bh, 46h, 28h, 0C1h, 0F8h, 02h, 33h, 0DBh
    db 85h, 0C0h, 0C7h, 44h, 24h, 18h, 02h, 00h, 00h, 00h, 76h, 2Ch, 8Dh, 64h, 24h, 00h
    db 8Bh, 46h, 28h, 8Bh, 3Ch, 98h, 85h, 0FFh, 74h, 10h, 8Bh, 0CFh, 0E8h, 5Eh, 0E5h, 0C4h
    db 0FFh, 57h, 0E8h, 0D9h, 79h, 4Bh, 00h, 83h, 0C4h, 04h, 8Bh, 4Eh, 2Ch, 2Bh, 4Eh, 28h
    db 43h, 0C1h, 0F9h, 02h, 3Bh, 0D9h, 72h, 0D8h, 8Bh, 46h, 2Ch, 3Bh, 0C0h, 8Bh, 4Eh, 28h
    db 75h, 04h, 8Bh, 0C1h, 0EBh, 12h, 8Bh, 0F8h, 2Bh, 0F8h, 57h, 50h, 51h, 0FFh, 15h, 5Ch
    db 94h, 35h, 01h, 83h, 0C4h, 0Ch, 03h, 0C7h, 89h, 46h, 2Ch, 8Bh, 4Eh, 28h, 85h, 0C9h
    db 0C6h, 44h, 24h, 18h, 01h, 74h, 27h, 8Bh, 46h, 30h, 2Bh, 0C1h, 0C1h, 0F8h, 02h, 0C1h
    db 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 81h, 79h, 4Bh, 00h, 83h
    db 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 0B5h, 40h, 46h, 00h, 83h, 0C4h, 08h, 8Bh, 4Eh
    db 14h, 85h, 0C9h, 0C6h, 44h, 24h, 18h, 00h, 74h, 27h, 8Bh, 46h, 1Ch, 2Bh, 0C1h, 0C1h
    db 0F8h, 02h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 4Eh, 79h
    db 4Bh, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 82h, 40h, 46h, 00h, 83h, 0C4h
    db 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 0C7h, 06h, 44h, 37h, 07h, 01h, 5Eh, 5Bh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_003ca480@@YAXXZ ENDP

; ghidra: FUN_007ca710  retail @ 0x003CA710 size 140
public ?d_003ca710@@YAXXZ
?d_003ca710@@YAXXZ PROC
    db 56h, 57h, 8Bh, 79h, 04h, 8Bh, 47h, 30h, 8Bh, 4Fh, 34h, 83h, 0C7h, 30h, 2Bh, 0C8h
    db 0C1h, 0F9h, 02h, 33h, 0F6h, 85h, 0C9h, 76h, 6Eh, 53h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 4Ch, 24h, 10h, 32h, 0DBh, 84h, 0C9h, 74h, 1Dh, 8Bh, 04h, 0B0h, 8Ah, 88h, 0A8h
    db 00h, 00h, 00h, 84h, 0C9h, 74h, 32h, 8Ah, 4Ch, 24h, 14h, 84h, 0C9h, 74h, 28h, 8Bh
    db 80h, 0B4h, 00h, 00h, 00h, 0EBh, 11h, 8Ah, 4Ch, 24h, 14h, 84h, 0C9h, 74h, 18h, 8Bh
    db 14h, 0B0h, 8Bh, 82h, 0B4h, 00h, 00h, 00h, 50h, 50h, 0E8h, 0F5h, 69h, 0C7h, 0FFh, 83h
    db 0C4h, 08h, 83h, 0F8h, 01h, 75h, 02h, 0B3h, 01h, 8Bh, 07h, 8Bh, 0Ch, 0B0h, 8Bh, 91h
    db 0ECh, 00h, 00h, 00h, 88h, 5Ah, 18h, 8Bh, 07h, 8Bh, 4Fh, 04h, 2Bh, 0C8h, 46h, 0C1h
    db 0F9h, 02h, 3Bh, 0F1h, 72h, 9Ah, 5Bh, 5Fh, 5Eh, 0C2h, 08h, 00h
?d_003ca710@@YAXXZ ENDP
_TEXT ENDS
END
