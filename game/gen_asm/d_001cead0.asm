.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A:BYTE
EXTERN ?Clock00200420@@3PAUFrame00200420@@A:BYTE
EXTERN ?Rva012ef214@@3PAVRva0041D290Manager@@A:BYTE
EXTERN ?g_bfmeScaleBC@@3MA:BYTE
EXTERN ?g_sentinel012ADC38@@3IA:BYTE
EXTERN ?j_0000b81b@@YAXXZ:NEAR
EXTERN ?j_00013d95@@YAXXZ:NEAR
EXTERN ?j_00019b00@@YAXXZ:NEAR
EXTERN ?j_00020c20@@YAXXZ:NEAR
EXTERN ?j_0002191d@@YAXXZ:NEAR
EXTERN ?j_0002bb0c@@YAXXZ:NEAR
EXTERN ?j_0002becc@@YAXXZ:NEAR
EXTERN ?j_000351d9@@YAXXZ:NEAR
EXTERN ?j_0003e5d6@@YAXXZ:NEAR
EXTERN ?j_00048d6a@@YAXXZ:NEAR
EXTERN ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z:NEAR
EXTERN __real@4f800000:BYTE
_TEXT SEGMENT

; retail @ 0x001CEAD0 size 664
public ?d_001cead0@@YAXXZ
?d_001cead0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 38h, 93h, 00h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 7Ch, 53h, 56h, 57h, 8Bh, 0F1h, 0E8h, 0DDh, 94h
    db 0E5h, 0FFh, 8Bh, 0BCh, 24h, 9Ch, 00h, 00h, 00h, 8Bh, 0Dh, 88h, 0F1h, 2Eh, 01h, 57h
    db 0E8h, 9Fh, 83h, 0E5h, 0FFh, 85h, 0C0h, 74h, 08h, 50h, 8Bh, 0CEh, 0E8h, 6Dh, 0BEh, 0E4h
    db 0FFh, 8Bh, 8Eh, 00h, 02h, 00h, 00h, 85h, 0C9h, 8Bh, 9Ch, 24h, 98h, 00h, 00h, 00h
    db 74h, 07h, 8Bh, 01h, 57h, 53h, 0FFh, 50h, 2Ch, 8Bh, 8Eh, 3Ch, 02h, 00h, 00h, 85h
    db 0C9h, 74h, 07h, 0E8h, 63h, 4Bh, 0E5h, 0FFh, 0EBh, 02h, 33h, 0C0h, 8Bh, 0Dh, 48h, 0D7h
    db 2Eh, 01h, 8Bh, 49h, 0Ch, 3Bh, 0C1h, 74h, 11h, 8Bh, 86h, 90h, 00h, 00h, 00h, 84h
    db 0E4h, 79h, 07h, 0A9h, 00h, 00h, 02h, 00h, 74h, 15h, 3Bh, 0FBh, 7Eh, 11h, 6Ah, 2Fh
    db 8Bh, 0CEh, 0E8h, 0B8h, 39h, 0E6h, 0FFh, 84h, 0C0h, 75h, 04h, 0B3h, 01h, 0EBh, 02h, 32h
    db 0DBh, 83h, 0FFh, 03h, 0Fh, 87h, 0CCh, 00h, 00h, 00h, 0FFh, 24h, 0BDh, 58h, 0EDh, 5Ch
    db 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 21h, 37h, 0E4h, 0FFh, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 18h
    db 37h, 0E4h, 0FFh, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 0Fh, 37h, 0E4h, 0FFh, 81h, 0A6h, 0A0h, 02h
    db 00h, 00h, 0FFh, 0F1h, 0FFh, 0FFh, 0E9h, 93h, 01h, 00h, 00h, 6Ah, 00h, 8Bh, 0CEh, 0E8h
    db 38h, 5Dh, 0E6h, 0FFh, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0EEh, 36h, 0E4h, 0FFh, 6Ah, 02h, 8Bh
    db 0CEh, 0E8h, 0E5h, 36h, 0E4h, 0FFh, 8Bh, 96h, 0A0h, 02h, 00h, 00h, 81h, 0E2h, 0FFh, 0F3h
    db 0FFh, 0FFh, 81h, 0CAh, 00h, 02h, 00h, 00h, 89h, 96h, 0A0h, 02h, 00h, 00h, 0EBh, 66h
    db 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0C2h, 36h, 0E4h, 0FFh, 6Ah, 01h, 8Bh, 0CEh, 0E8h, 0FAh, 5Ch
    db 0E6h, 0FFh, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 0B0h, 36h, 0E4h, 0FFh, 8Bh, 86h, 0A0h, 02h, 00h
    db 00h, 25h, 0FFh, 0F5h, 0FFh, 0FFh, 0Dh, 00h, 04h, 00h, 00h, 89h, 86h, 0A0h, 02h, 00h
    db 00h, 0EBh, 33h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 8Fh, 36h, 0E4h, 0FFh, 6Ah, 01h, 8Bh, 0CEh
    db 0E8h, 86h, 36h, 0E4h, 0FFh, 6Ah, 02h, 8Bh, 0CEh, 0E8h, 0BEh, 5Ch, 0E6h, 0FFh, 8Bh, 8Eh
    db 0A0h, 02h, 00h, 00h, 81h, 0E1h, 0FFh, 0F9h, 0FFh, 0FFh, 81h, 0C9h, 00h, 08h, 00h, 00h
    db 89h, 8Eh, 0A0h, 02h, 00h, 00h, 84h, 0DBh, 0Fh, 84h, 0F0h, 00h, 00h, 00h, 8Bh, 15h
    db 98h, 08h, 2Fh, 01h, 8Ah, 82h, 92h, 00h, 00h, 00h, 84h, 0C0h, 0Fh, 84h, 0DCh, 00h
    db 00h, 00h, 8Bh, 0Dh, 0A8h, 4Ch, 2Fh, 01h, 85h, 0C9h, 74h, 79h, 0A1h, 0C8h, 0D5h, 2Eh
    db 01h, 8Bh, 90h, 00h, 02h, 00h, 00h, 05h, 00h, 02h, 00h, 00h, 85h, 0D2h, 74h, 65h
    db 66h, 83h, 7Ah, 04h, 00h, 74h, 5Eh, 50h, 0E8h, 5Dh, 0D4h, 0E3h, 0FFh, 0D9h, 46h, 38h
    db 0D9h, 46h, 3Ch, 8Bh, 4Eh, 40h, 0D9h, 0C9h, 89h, 4Ch, 24h, 14h, 0D8h, 86h, 4Ch, 02h
    db 00h, 00h, 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 0D9h, 5Ch, 24h, 0Ch, 0D8h, 86h, 50h, 02h
    db 00h, 00h, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h, 14h, 0D8h, 86h, 54h, 02h, 00h, 00h
    db 0D9h, 5Ch, 24h, 14h, 8Bh, 91h, 08h, 02h, 00h, 00h, 8Bh, 89h, 04h, 02h, 00h, 00h
    db 52h, 51h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 6Ah, 01h, 8Dh, 54h, 24h, 18h, 52h, 50h
    db 0E8h, 00h, 52h, 0E3h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h, 8Bh, 01h, 0FFh, 90h, 24h
    db 01h, 00h, 00h, 05h, 80h, 0Ah, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 25h, 8Eh
    db 0E7h, 0FFh, 8Bh, 76h, 74h, 56h, 8Dh, 4Ch, 24h, 1Ch, 0C7h, 84h, 24h, 94h, 00h, 00h
    db 00h, 00h, 00h, 00h, 00h, 0E8h, 50h, 0ADh, 0E4h, 0FFh, 8Bh, 0Dh, 68h, 0D6h, 2Eh, 01h
    db 8Bh, 11h, 8Dh, 44h, 24h, 18h, 50h, 0FFh, 52h, 44h, 8Dh, 4Ch, 24h, 18h, 0C7h, 84h
    db 24h, 90h, 00h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0F7h, 81h, 0E5h, 0FFh, 8Bh, 8Ch
    db 24h, 88h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h
    db 0C4h, 88h, 00h, 00h, 00h, 0C2h, 08h, 00h, 81h, 0EBh, 5Ch, 00h, 0ABh, 0EBh, 5Ch, 00h
    db 0E0h, 0EBh, 5Ch, 00h, 13h, 0ECh, 5Ch, 00h
?d_001cead0@@YAXXZ ENDP

; retail @ 0x001FD970 size 1340
_TEXT ENDS
_TEXT$d005fd970 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x005FD970 size 1340
public ?d_001fd970@@YAXXZ
?d_001fd970@@YAXXZ PROC
    db 083h, 0ECh, 010h, 053h, 056h, 08Bh, 0F1h, 08Bh, 05Eh, 0F8h, 085h, 0DBh, 089h, 05Ch, 024h, 010h
    db 00Fh, 084h, 00Ah, 005h, 000h, 000h, 08Bh, 0CBh
    call ?j_000351d9@@YAXXZ
    db 085h, 0C0h, 074h, 00Eh, 08Bh, 0CBh
    call ?j_000351d9@@YAXXZ
    db 08Bh, 010h, 08Bh, 0C8h, 0FFh, 052h, 008h, 0F6h, 083h, 090h, 000h, 000h, 000h, 004h, 074h, 004h
    db 0C6h, 046h, 01Ch, 000h, 0F6h, 083h, 044h, 003h, 000h, 000h, 001h, 055h, 057h, 00Fh, 084h, 0D5h
    db 000h, 000h, 000h, 083h, 07Eh, 014h, 001h, 074h, 00Eh, 0C7h, 046h, 014h, 000h, 000h, 000h, 000h
    db 0C7h, 046h, 020h, 000h, 000h, 0C8h, 042h, 08Bh, 046h, 018h, 08Dh, 07Eh, 0ECh, 0BDh, 002h, 000h
    db 000h, 000h, 03Bh, 0C5h, 00Fh, 084h, 08Eh, 000h, 000h, 000h, 08Bh, 0CFh
    call ?j_00048d6a@@YAXXZ
    db 08Bh, 05Fh, 00Ch, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 053h, 089h, 05Ch, 024h, 01Ch
    call ?j_00013d95@@YAXXZ
    db 06Ah, 009h, 08Bh, 0CBh, 089h, 06Fh, 02Ch
    call ?j_0002bb0c@@YAXXZ
    db 08Bh, 06Fh, 008h, 08Bh, 07Dh, 028h, 08Bh, 045h, 02Ch, 081h, 0C3h, 0ACh, 000h, 000h, 000h, 03Bh
    db 0F8h, 074h, 017h, 08Dh, 049h, 000h, 06Ah, 001h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 02Ch, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Dh, 034h, 03Bh, 07Dh, 038h
    db 074h, 018h, 08Dh, 064h, 024h, 000h, 06Ah, 000h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 038h, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Ch, 024h, 018h, 06Ah, 001h
    db 08Bh, 0CFh
    call ?j_00020c20@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 057h
    call ?j_0000b81b@@YAXXZ
    db 08Bh, 00Dh
    dd ?AudioGlobal004092A0@@3PAUAudioView004092A0@@A
    db 08Bh, 046h, 030h, 08Bh, 011h, 050h, 0FFh, 052h, 04Ch, 05Fh, 05Dh, 0C6h, 046h, 01Ch, 000h, 05Eh
    db 0B8h, 001h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 010h, 0C3h, 08Bh, 046h, 02Ch, 085h, 0C0h, 08Bh
    db 06Eh, 0F4h, 089h, 06Ch, 024h, 014h, 07Ch, 03Ch, 08Bh, 056h, 0ECh, 08Dh, 07Eh, 0ECh, 08Bh, 0CFh
    db 0FFh, 052h, 028h, 084h, 0C0h, 074h, 02Dh, 08Bh, 007h, 08Bh, 0CFh, 0FFh, 050h, 018h, 00Fh, 0B6h
    db 0C8h, 08Bh, 046h, 02Ch, 033h, 0D2h, 085h, 0C0h, 00Fh, 09Fh, 0C2h, 03Bh, 0CAh, 074h, 015h, 08Bh
    db 007h, 08Bh, 0CFh, 0FFh, 050h, 024h, 08Bh, 046h, 02Ch, 085h, 0C0h, 075h, 007h, 0C7h, 046h, 02Ch
    db 0FFh, 0FFh, 0FFh, 0FFh, 08Bh, 046h, 014h, 083h, 0F8h, 003h, 00Fh, 087h, 09Bh, 003h, 000h, 000h
    db 0FFh, 024h, 085h
    dd ?d_001fd970@@YAXXZ + 052Ch
    db 08Bh, 00Dh
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 079h, 03Ch, 08Bh, 046h, 028h, 08Bh, 055h, 00Ch, 02Bh, 0F8h, 085h, 0D2h, 089h, 07Ch, 024h
    db 010h, 0DBh, 044h, 024h, 010h, 0DBh, 045h, 00Ch, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0DEh, 0F9h, 0D8h, 00Dh
    dd ?g_bfmeScaleBC@@3MA
    db 0D9h, 056h, 020h, 0D8h, 01Dh
    dd ?g_bfmeScaleBC@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 00Ah, 06Ah, 001h, 08Dh, 04Eh, 0ECh
    call ?j_0002becc@@YAXXZ
    db 08Bh, 045h, 010h, 0DBh, 045h, 010h, 085h, 0C0h, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 05Eh, 020h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 00Fh, 08Ah, 0A9h, 000h, 000h, 000h, 08Bh, 046h
    db 018h, 08Dh, 07Eh, 0ECh, 0BDh, 002h, 000h, 000h, 000h, 03Bh, 0C5h, 00Fh, 084h, 08Eh, 000h, 000h
    db 000h, 08Bh, 0CFh
    call ?j_00048d6a@@YAXXZ
    db 08Bh, 05Fh, 00Ch, 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 053h, 089h, 05Ch, 024h, 020h
    call ?j_00013d95@@YAXXZ
    db 06Ah, 009h, 08Bh, 0CBh, 089h, 06Fh, 02Ch
    call ?j_0002bb0c@@YAXXZ
    db 08Bh, 06Fh, 008h, 08Bh, 07Dh, 028h, 08Bh, 045h, 02Ch, 081h, 0C3h, 0ACh, 000h, 000h, 000h, 03Bh
    db 0F8h, 074h, 014h, 06Ah, 001h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 02Ch, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Dh, 034h, 03Bh, 07Dh, 038h
    db 074h, 016h, 08Bh, 0FFh, 06Ah, 000h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 038h, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Ch, 024h, 01Ch, 06Ah, 001h
    db 08Bh, 0CFh
    call ?j_00020c20@@YAXXZ
    db 08Bh, 015h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 04Ah, 00Ch, 057h
    call ?j_0000b81b@@YAXXZ
    db 08Bh, 05Ch, 024h, 018h, 08Bh, 06Ch, 024h, 014h, 08Bh, 07Ch, 024h, 010h, 08Bh, 045h, 040h, 03Bh
    db 005h
    dd ?g_sentinel012ADC38@@3IA
    db 075h, 005h, 08Bh, 06Dh, 00Ch, 0EBh, 002h, 08Bh, 0E8h, 03Bh, 0FDh, 076h, 00Fh, 08Ah, 046h, 034h
    db 084h, 0C0h, 075h, 008h, 08Dh, 04Eh, 0ECh
    call ?j_00019b00@@YAXXZ
    db 0C6h, 046h, 01Ch, 000h, 08Bh, 083h, 010h, 001h, 000h, 000h, 0A9h, 000h, 000h, 040h, 000h, 075h
    db 00Bh, 0A9h, 000h, 000h, 020h, 000h, 00Fh, 085h, 044h, 002h, 000h, 000h, 08Bh, 08Bh, 010h, 001h
    db 000h, 000h, 081h, 0E1h, 0FFh, 0FFh, 0BFh, 0FFh, 08Bh, 0C1h, 089h, 08Bh, 010h, 001h, 000h, 000h
    db 00Dh, 000h, 000h, 020h, 000h, 08Bh, 0CBh, 089h, 083h, 010h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0E9h, 019h, 002h, 000h, 000h, 0C7h, 046h, 020h, 000h, 000h, 0C8h, 042h, 0C6h, 046h, 01Ch, 001h
    db 08Bh, 083h, 010h, 001h, 000h, 000h, 0A9h, 000h, 000h, 040h, 000h, 075h, 007h, 0A9h, 000h, 000h
    db 020h, 000h, 075h, 026h, 08Bh, 08Bh, 010h, 001h, 000h, 000h, 081h, 0E1h, 0FFh, 0FFh, 0BFh, 0FFh
    db 08Bh, 0C1h, 089h, 08Bh, 010h, 001h, 000h, 000h, 00Dh, 000h, 000h, 020h, 000h, 08Bh, 0CBh, 089h
    db 083h, 010h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Bh, 046h, 018h, 08Dh, 07Eh, 0ECh, 0BDh, 002h, 000h, 000h, 000h, 03Bh, 0C5h, 00Fh, 084h, 0C1h
    db 001h, 000h, 000h, 08Bh, 0CFh
    call ?j_00048d6a@@YAXXZ
    db 08Bh, 05Fh, 00Ch, 0A1h
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 048h, 00Ch, 053h, 089h, 05Ch, 024h, 020h
    call ?j_00013d95@@YAXXZ
    db 06Ah, 009h, 08Bh, 0CBh, 089h, 06Fh, 02Ch
    call ?j_0002bb0c@@YAXXZ
    db 08Bh, 06Fh, 008h, 08Bh, 07Dh, 028h, 08Bh, 045h, 02Ch, 081h, 0C3h, 0ACh, 000h, 000h, 000h, 03Bh
    db 0F8h, 074h, 019h, 0EBh, 003h, 08Dh, 049h, 000h, 06Ah, 001h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 02Ch, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Dh, 034h, 03Bh, 07Dh, 038h
    db 074h, 018h, 08Dh, 064h, 024h, 000h, 06Ah, 000h, 057h, 08Bh, 0CBh
    call ?setFlag@BfmeObjF9@@QAEXABVBfmeStrF9@@D@Z
    db 08Bh, 045h, 038h, 083h, 0C7h, 004h, 03Bh, 0F8h, 075h, 0ECh, 08Bh, 07Ch, 024h, 01Ch, 06Ah, 001h
    db 08Bh, 0CFh
    call ?j_00020c20@@YAXXZ
    db 08Bh, 00Dh
    dd ?Rva012ef214@@3PAVRva0041D290Manager@@A
    db 08Bh, 049h, 00Ch, 057h
    call ?j_0000b81b@@YAXXZ
    db 08Bh, 05Ch, 024h, 018h, 0E9h, 028h, 001h, 000h, 000h, 08Bh, 015h
    dd ?Clock00200420@@3PAUFrame00200420@@A
    db 08Bh, 046h, 028h, 08Bh, 07Ah, 03Ch, 02Bh, 0F8h, 08Bh, 045h, 00Ch, 085h, 0C0h, 089h, 07Ch, 024h
    db 01Ch, 0DBh, 044h, 024h, 01Ch, 0DBh, 045h, 00Ch, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0DEh, 0F9h, 0D8h, 00Dh
    dd ?g_bfmeScaleBC@@3MA
    db 0D9h, 056h, 020h, 0D8h, 01Dh
    dd ?g_bfmeScaleBC@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 00Ah, 06Ah, 003h, 08Dh, 04Eh, 0ECh
    call ?j_0002becc@@YAXXZ
    db 08Bh, 045h, 010h, 0B9h, 064h, 000h, 000h, 000h, 02Bh, 0C8h, 085h, 0C9h, 089h, 04Ch, 024h, 01Ch
    db 0DBh, 044h, 024h, 01Ch, 07Dh, 006h, 0D8h, 005h
    dd __real@4f800000
    db 0D8h, 05Eh, 020h, 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 08Dh, 04Eh, 0ECh
    call ?j_0003e5d6@@YAXXZ
    db 08Bh, 045h, 044h, 03Bh, 005h
    dd ?g_sentinel012ADC38@@3IA
    db 075h, 005h, 08Bh, 06Dh, 00Ch, 0EBh, 002h, 08Bh, 0E8h, 03Bh, 0FDh, 076h, 00Fh, 08Ah, 046h, 034h
    db 084h, 0C0h, 075h, 008h, 08Dh, 04Eh, 0ECh
    call ?j_00019b00@@YAXXZ
    db 0C6h, 046h, 01Ch, 000h, 08Bh, 083h, 010h, 001h, 000h, 000h, 0A9h, 000h, 000h, 020h, 000h, 075h
    db 007h, 0A9h, 000h, 000h, 040h, 000h, 075h, 075h, 08Bh, 08Bh, 010h, 001h, 000h, 000h, 081h, 0E1h
    db 0FFh, 0FFh, 0DFh, 0FFh, 08Bh, 0C1h, 089h, 08Bh, 010h, 001h, 000h, 000h, 00Dh, 000h, 000h, 040h
    db 000h, 08Bh, 0CBh, 089h, 083h, 010h, 001h, 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 0EBh, 04Dh, 0C7h, 046h, 020h, 000h, 000h, 0C8h, 042h, 0C6h, 046h, 01Ch, 001h, 08Bh, 083h, 010h
    db 001h, 000h, 000h, 0A9h, 000h, 000h, 020h, 000h, 075h, 007h, 0A9h, 000h, 000h, 040h, 000h, 075h
    db 026h, 08Bh, 08Bh, 010h, 001h, 000h, 000h, 081h, 0E1h, 0FFh, 0FFh, 0DFh, 0FFh, 08Bh, 0C1h, 089h
    db 08Bh, 010h, 001h, 000h, 000h, 00Dh, 000h, 000h, 040h, 000h, 08Bh, 0CBh, 089h, 083h, 010h, 001h
    db 000h, 000h
    call ?j_0002191d@@YAXXZ
    db 08Dh, 04Eh, 0ECh
    call ?j_0003e5d6@@YAXXZ
    db 0F6h, 083h, 090h, 000h, 000h, 000h, 004h, 074h, 004h, 0C6h, 046h, 01Ch, 000h, 05Fh, 05Dh, 05Eh
    db 0B8h, 001h, 000h, 000h, 000h, 05Bh, 083h, 0C4h, 010h, 0C3h, 090h
    dd ?d_001fd970@@YAXXZ + 017Dh
    dd ?d_001fd970@@YAXXZ + 02F8h
    dd ?d_001fd970@@YAXXZ + 03E9h
    dd ?d_001fd970@@YAXXZ + 04C4h
?d_001fd970@@YAXXZ ENDP
_TEXT$d005fd970 ENDS
_TEXT SEGMENT

; retail @ 0x0020DEE0 size 136
public ?d_0020dee0@@YAXXZ
?d_0020dee0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0F8h, 03h, 56h, 8Bh, 0F1h, 77h, 5Ah, 0FFh, 24h, 85h, 58h
    db 0DFh, 60h, 00h, 0D9h, 46h, 10h, 8Bh, 06h, 0D8h, 66h, 08h, 6Ah, 00h, 51h, 8Bh, 0CEh
    db 0D9h, 1Ch, 24h, 0FFh, 90h, 80h, 00h, 00h, 00h, 0EBh, 3Bh, 0D9h, 46h, 14h, 0D8h, 4Eh
    db 10h, 0D8h, 66h, 08h, 0EBh, 20h, 0D9h, 46h, 18h, 8Bh, 06h, 0D8h, 4Eh, 10h, 6Ah, 00h
    db 51h, 8Bh, 0CEh, 0D8h, 66h, 08h, 0D9h, 1Ch, 24h, 0FFh, 90h, 80h, 00h, 00h, 00h, 0EBh
    db 15h, 0D9h, 46h, 08h, 0D9h, 0E0h, 8Bh, 16h, 6Ah, 00h, 51h, 8Bh, 0CEh, 0D9h, 1Ch, 24h
    db 0FFh, 92h, 80h, 00h, 00h, 00h, 8Bh, 46h, 0F0h, 8Dh, 4Eh, 0F0h, 5Eh, 0C7h, 44h, 24h
    db 04h, 00h, 00h, 00h, 00h, 0FFh, 60h, 48h, 0F3h, 0DEh, 60h, 00h, 0Bh, 0DFh, 60h, 00h
    db 16h, 0DFh, 60h, 00h, 31h, 0DFh, 60h, 00h
?d_0020dee0@@YAXXZ ENDP
_TEXT ENDS
END
