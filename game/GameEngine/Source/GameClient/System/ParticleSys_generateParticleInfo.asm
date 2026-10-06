.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??_7Rva005EA080@@6BT4P0_Rva005E9AE0@@@:BYTE
EXTERN ??_7Rva005EB1F0@@6B@:BYTE
EXTERN ??_7Rva005EB1F0@@6BV3Slot0N@@@:BYTE
EXTERN ??_7Rva005EB1F0@@6BV3Slot1@@@:BYTE
EXTERN ??_7Rva005ECFA0@@6B@:BYTE
EXTERN ??_7Rva005ECFA0@@6BV3Slot0@@@:BYTE
EXTERN ??_7Rva005ECFA0@@6BV3Slot1@@@:BYTE
EXTERN ??_7Rva005ECFA0@@6BV3Slot2@@@:BYTE
EXTERN ?j_00001b18@@YAXXZ:NEAR
EXTERN ?j_000033eb@@YAXXZ:NEAR
EXTERN ?j_0000ba19@@YAXXZ:NEAR
EXTERN ?j_0000d7b5@@YAXXZ:NEAR
EXTERN ?j_00013994@@YAXXZ:NEAR
EXTERN ?j_0002a9f5@@YAXXZ:NEAR
EXTERN ?j_000438f6@@YAXXZ:NEAR
EXTERN g_0103CD4B:NEAR
EXTERN g_0103CD68:NEAR
EXTERN g_0110F9E8:BYTE
EXTERN g_0111089C:BYTE
EXTERN g_011126F8:BYTE
EXTERN g_0111270C:BYTE
EXTERN g_01112A98:BYTE
EXTERN g_01113188:BYTE
EXTERN g_0111318C:BYTE
EXTERN g_01113190:BYTE

; ?generateParticleInfo@ParticleSystem@@IAEPBVParticleInfo@@HH@Z
; Exact 1257 retail bytes @ 0x006008AF
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d00a008af SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00A008AF size 1257
public ?generateParticleInfo@ParticleSystem@@IAEPBVParticleInfo@@HH@Z
?generateParticleInfo@ParticleSystem@@IAEPBVParticleInfo@@HH@Z PROC
    db 056h, 08Dh, 04Fh, 00Ch
    call ?j_0000ba19@@YAXXZ
    db 05Fh, 05Eh, 059h, 0C2h, 004h, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 08Bh, 0C1h, 08Bh, 04Ch, 024h, 004h, 089h, 048h
    db 004h, 0C7h, 040h, 008h
    dd g_0110F9E8
    db 0C7h, 040h, 00Ch
    dd g_01112A98
    db 0C7h, 040h, 040h, 001h, 000h, 000h, 000h, 0B9h, 000h, 000h, 080h, 03Fh, 089h, 048h, 010h, 089h
    db 048h, 014h, 089h, 048h, 018h, 033h, 0C9h, 089h, 048h, 01Ch, 089h, 048h, 020h, 089h, 048h, 024h
    db 089h, 048h, 028h, 089h, 048h, 02Ch, 089h, 048h, 030h, 089h, 048h, 034h, 089h, 048h, 038h, 089h
    db 048h, 03Ch, 08Bh, 04Ch, 024h, 008h, 0C7h, 000h
    dd ??_7Rva005EB1F0@@6BV3Slot0N@@@
    db 0C7h, 040h, 008h
    dd ??_7Rva005EB1F0@@6BV3Slot1@@@
    db 0C7h, 040h, 00Ch
    dd ??_7Rva005EB1F0@@6B@
    db 08Bh, 051h, 00Ch, 089h, 050h, 010h, 08Bh, 051h, 010h, 089h, 050h, 014h, 08Bh, 051h, 014h, 089h
    db 050h, 018h, 08Bh, 051h, 018h, 089h, 050h, 01Ch, 08Bh, 051h, 01Ch, 089h, 050h, 020h, 08Bh, 051h
    db 020h, 089h, 050h, 024h, 08Bh, 051h, 024h, 089h, 050h, 028h, 08Bh, 051h, 028h, 089h, 050h, 02Ch
    db 08Bh, 051h, 02Ch, 089h, 050h, 030h, 08Bh, 051h, 030h, 089h, 050h, 034h, 08Bh, 051h, 034h, 089h
    db 050h, 038h, 08Bh, 051h, 038h, 089h, 050h, 03Ch, 08Bh, 049h, 03Ch, 089h, 048h, 040h, 0C2h, 008h
    db 000h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 06Ah
    db 0FFh, 068h
    dd g_0103CD4B
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 010h, 053h, 056h, 08Bh, 0F1h, 057h, 089h, 074h, 024h, 00Ch, 0C7h, 046h, 004h
    dd g_0110F9E8
    db 033h, 0DBh, 0B8h, 000h, 000h, 080h, 03Fh, 089h, 05Ch, 024h, 024h, 0C7h, 046h, 008h
    dd g_01112A98
    db 089h, 046h, 00Ch, 089h, 046h, 010h, 089h, 046h, 014h, 089h, 05Eh, 018h, 089h, 05Eh, 01Ch, 089h
    db 05Eh, 020h, 089h, 05Eh, 024h, 089h, 05Eh, 028h, 089h, 05Eh, 02Ch, 089h, 05Eh, 030h, 089h, 05Eh
    db 034h, 089h, 05Eh, 038h, 0C7h, 046h, 03Ch, 001h, 000h, 000h, 000h, 08Bh, 07Ch, 024h, 02Ch, 08Dh
    db 044h, 024h, 010h, 050h, 08Bh, 0CFh, 0C7h, 006h
    dd ??_7Rva005EA080@@6BT4P0_Rva005E9AE0@@@
    db 0C7h, 046h, 004h
    dd g_0111270C
    db 0C7h, 046h, 008h
    dd g_011126F8
    call ?j_000438f6@@YAXXZ
    db 08Dh, 04Fh, 020h, 0C6h, 044h, 024h, 024h, 002h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 00Ch, 08Bh, 044h, 024h, 010h, 03Bh, 0C3h, 075h, 005h
    call ?j_00001b18@@YAXXZ
    db 08Bh, 088h, 088h, 001h, 000h, 000h, 089h, 04Ch, 024h, 02Ch, 08Dh, 04Fh, 02Ch
    call ?j_0000d7b5@@YAXXZ
    db 0D8h, 04Ch, 024h, 02Ch, 08Dh, 04Fh, 038h, 0D9h, 05Eh, 010h
    call ?j_0000d7b5@@YAXXZ
    db 08Dh, 04Fh, 044h, 0D9h, 05Eh, 014h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 018h, 08Dh, 04Fh, 050h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 01Ch, 08Dh, 04Fh, 05Ch
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 020h, 08Dh, 04Fh, 068h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 024h, 08Dh, 04Fh, 074h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 028h, 08Dh, 08Fh, 080h, 000h, 000h, 000h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 02Ch, 08Bh, 04Ch, 024h, 010h, 03Bh, 0CBh, 075h, 00Bh
    call ?j_00001b18@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 0EBh, 002h, 08Bh, 0C1h, 03Bh, 0CBh, 0D9h, 080h, 084h, 001h, 000h, 000h
    db 0D8h, 046h, 00Ch, 0D9h, 05Eh, 00Ch, 075h, 00Bh
    call ?j_00001b18@@YAXXZ
    db 08Bh, 04Ch, 024h, 010h, 0EBh, 002h, 08Bh, 0C1h, 03Bh, 0CBh, 0D9h, 080h, 084h, 001h, 000h, 000h
    db 0D8h, 046h, 010h, 0D9h, 05Eh, 010h, 075h, 007h
    call ?j_00001b18@@YAXXZ
    db 0EBh, 002h, 08Bh, 0C1h, 0D9h, 080h, 084h, 001h, 000h, 000h, 08Dh, 08Fh, 08Ch, 000h, 000h, 000h
    db 0D8h, 046h, 014h, 0D9h, 05Eh, 014h
    call ?j_0000d7b5@@YAXXZ
    db 08Dh, 08Fh, 098h, 000h, 000h, 000h, 0D9h, 05Eh, 030h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 034h, 08Dh, 08Fh, 0A4h, 000h, 000h, 000h
    call ?j_0000d7b5@@YAXXZ
    db 0D9h, 05Eh, 038h, 08Bh, 097h, 0B0h, 000h, 000h, 000h, 08Dh, 04Ch, 024h, 010h, 089h, 056h, 03Ch
    call ?j_00013994@@YAXXZ
    db 08Bh, 04Ch, 024h, 01Ch, 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h
    db 083h, 0C4h, 01Ch, 0C2h, 004h, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
    db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 06Ah, 0FFh
    db 068h
    dd g_0103CD68
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 051h, 08Bh
    db 044h, 024h, 014h, 053h, 056h, 057h, 08Bh, 07Ch, 024h, 024h, 057h, 08Bh, 0F1h, 050h, 089h, 074h
    db 024h, 014h
    call ?j_0002a9f5@@YAXXZ
    db 0C7h, 046h, 014h
    dd g_0111089C
    db 0C7h, 046h, 018h
    dd g_0110F9E8
    db 0C7h, 006h
    dd g_01113190
    db 0C7h, 046h, 014h
    dd g_0111318C
    db 0C7h, 046h, 018h
    dd g_01113188
    db 08Dh, 05Eh, 01Ch, 08Bh, 0CBh, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h
    call ?j_000033eb@@YAXXZ
    db 0C7h, 006h
    dd ??_7Rva005ECFA0@@6BV3Slot0@@@
    db 0C7h, 046h, 014h
    dd ??_7Rva005ECFA0@@6BV3Slot1@@@
    db 0C7h, 046h, 018h
    dd ??_7Rva005ECFA0@@6BV3Slot2@@@
    db 0C7h, 003h
    dd ??_7Rva005ECFA0@@6B@
    db 08Dh, 04Fh, 00Ch, 08Bh, 001h, 08Dh, 056h, 020h, 089h, 002h, 08Bh, 041h, 004h, 089h, 042h, 004h
    db 08Bh, 049h, 008h, 089h, 04Ah, 008h, 08Dh, 057h, 018h, 08Bh, 00Ah, 08Dh, 046h, 02Ch, 089h, 008h
    db 08Bh, 04Ah, 004h, 089h, 048h, 004h, 08Bh, 052h, 008h, 089h, 050h, 008h, 08Dh, 047h, 024h, 08Bh
    db 010h, 08Dh, 04Eh, 038h, 089h, 011h, 08Bh, 050h, 004h, 089h, 051h, 004h, 08Bh, 040h, 008h, 089h
    db 041h, 008h, 08Dh, 04Fh, 030h, 08Bh, 001h, 08Dh, 056h, 044h, 089h, 002h, 08Bh, 041h, 004h, 089h
    db 042h, 004h, 08Bh, 049h, 008h, 089h, 04Ah, 008h, 08Dh, 057h, 03Ch, 08Bh, 00Ah, 08Dh, 046h, 050h
    db 089h, 008h, 08Bh, 04Ah, 004h, 089h, 048h, 004h, 08Bh, 052h, 008h, 089h, 050h, 008h, 08Dh, 047h
    db 048h, 08Bh, 010h, 08Dh, 04Eh, 05Ch, 089h, 011h, 08Bh, 050h, 004h, 089h, 051h, 004h, 08Bh, 040h
    db 008h, 089h, 041h, 008h, 08Dh, 04Fh, 054h, 08Bh, 001h, 08Dh, 056h, 068h, 089h, 002h, 08Bh, 041h
    db 004h, 089h, 042h, 004h, 08Bh, 049h, 008h, 089h, 04Ah, 008h, 08Dh, 057h, 060h, 08Bh, 00Ah, 08Dh
    db 046h, 074h, 089h, 008h, 08Bh, 04Ah, 004h, 089h, 048h, 004h, 08Bh, 052h, 008h, 089h, 050h, 008h
    db 08Dh, 047h, 06Ch, 08Bh, 010h, 08Dh, 08Eh, 080h, 000h, 000h, 000h, 089h, 011h, 08Bh, 050h, 004h
    db 089h, 051h, 004h, 08Bh, 040h, 008h, 089h, 041h, 008h, 08Dh, 04Fh, 078h, 08Bh, 001h, 08Dh, 096h
    db 08Ch, 000h, 000h, 000h, 089h, 002h, 08Bh, 041h, 004h, 089h, 042h, 004h, 08Bh, 049h, 008h, 089h
    db 04Ah, 008h, 08Dh, 097h, 084h, 000h, 000h, 000h, 08Bh, 00Ah, 08Dh, 086h, 098h, 000h, 000h, 000h
    db 089h, 008h, 08Bh, 04Ah, 004h, 089h, 048h, 004h, 08Bh, 052h, 008h, 089h, 050h, 008h, 08Dh, 087h
    db 090h, 000h, 000h, 000h, 08Bh, 010h, 08Dh, 08Eh, 0A4h, 000h, 000h, 000h, 089h, 011h, 08Bh, 050h
    db 004h, 089h, 051h, 004h, 08Bh, 040h, 008h, 089h, 041h, 008h, 08Bh, 08Fh, 09Ch, 000h, 000h, 000h
    db 089h, 08Eh, 0B0h, 000h, 000h, 000h, 08Bh, 04Ch, 024h, 010h, 05Fh, 08Bh, 0C6h, 05Eh, 05Bh, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 010h, 0C2h, 008h, 000h
?generateParticleInfo@ParticleSystem@@IAEPBVParticleInfo@@HH@Z ENDP
_TEXT$d00a008af ENDS
_TEXT SEGMENT
_TEXT ENDS
END
