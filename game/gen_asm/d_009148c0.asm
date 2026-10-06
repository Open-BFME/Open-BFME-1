.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0KeyClass@?$PrimitiveAnimationChannelClass@VVector2@@@@QAE@XZ:NEAR
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?Get_Render_Target_Resolution@WW3D@@SAXAAH00AA_N@Z:NEAR
EXTERN ?Rva0133F49CChanged@@3IA:BYTE
EXTERN ?_QuadVertexLocationOrientationTable@PointGroupClass@@2PAY03VVector3@@A:BYTE
EXTERN ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A:BYTE
EXTERN ?j_0000ae5c@@YAXXZ:NEAR
EXTERN ?ji_009fb93b@@YAXXZ:NEAR
EXTERN ?render_state_view@DX8Wrapper@@0VMatrix4@@A:BYTE
EXTERN g_Va0113ACDC:BYTE
EXTERN g_Va012D6EE8:BYTE
EXTERN g_Va012D6EEC:BYTE
EXTERN g_Va012D6EF0:BYTE
EXTERN g_Va012D6EF4:BYTE
EXTERN g_Va012D6EF8:BYTE
EXTERN g_Va012D6EFC:BYTE
EXTERN g_Va012D6F00:BYTE
EXTERN g_Va012D6F04:BYTE
EXTERN g_Va012D6F08:BYTE
EXTERN g_Va012D6F0C:BYTE
EXTERN g_Va012D6F10:BYTE
EXTERN g_Va012D6F14:BYTE
EXTERN g_Va012D6F18:BYTE
EXTERN g_Va012D6F1C:BYTE
EXTERN g_Va012D6F20:BYTE
EXTERN g_Va012D6F24:BYTE
EXTERN g_Va012D6F28:BYTE
EXTERN g_Va012D6F2C:BYTE
EXTERN g_Va012D6F30:BYTE
EXTERN g_Va012D6F34:BYTE
EXTERN g_Va012D6F38:BYTE
EXTERN g_Va012D6F3C:BYTE
EXTERN g_Va012D6F40:BYTE
EXTERN g_Va012D6F44:BYTE
EXTERN g_Va013410D0:BYTE
EXTERN g_Va013410D4:BYTE
EXTERN g_Va013410DC:BYTE
EXTERN g_Va013410E0:BYTE
EXTERN g_Va013410E4:BYTE
EXTERN g_Va013410EC:BYTE
EXTERN g_Va013410F0:BYTE
EXTERN g_Va013410F4:BYTE
EXTERN g_Va013410FC:BYTE
EXTERN g_Va01341100:BYTE
EXTERN g_Va01341104:BYTE
EXTERN g_Va01341268:BYTE
EXTERN g_Va0134128C:BYTE
EXTERN g_Va01341290:BYTE
EXTERN g_Va01341294:BYTE
EXTERN g_Va01341298:BYTE
EXTERN g_Va0134129C:BYTE
EXTERN g_Va013412A0:BYTE
EXTERN g_Va013412A4:BYTE
EXTERN g_Va013412A8:BYTE
EXTERN g_Va013436BC:BYTE
EXTERN g_Va013436C0:BYTE
EXTERN g_Va013436C4:BYTE
EXTERN g_Va013436C8:BYTE
EXTERN g_Va013436CC:BYTE
EXTERN g_Va013436D0:BYTE
EXTERN g_Va013436D4:BYTE
EXTERN g_Va013436D8:BYTE
EXTERN g_Va013436DC:BYTE
EXTERN g_Va013436E0:BYTE
EXTERN g_Va013436E4:BYTE
_TEXT SEGMENT

; retail @ 0x009148C0 size 9232
_TEXT ENDS
_TEXT$d00d148c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00D148C0 size 9232
public ?d_009148c0@@YAXXZ
?d_009148c0@@YAXXZ PROC
    db 0A1h
    dd g_Va01341268
    db 081h, 0ECh, 0F0h, 000h, 000h, 000h, 053h, 08Bh, 09Ch, 024h, 000h, 001h, 000h, 000h, 055h, 056h
    db 08Bh, 0E9h, 033h, 0C9h, 057h, 08Bh, 0BCh, 024h, 008h, 001h, 000h, 000h, 085h, 0FFh, 00Fh, 095h
    db 0C1h, 08Bh, 0D3h, 0F7h, 0DAh, 01Bh, 0D2h, 083h, 0E2h, 002h, 08Bh, 0F0h, 003h, 0CAh, 08Bh, 055h
    db 02Ch, 08Dh, 00Ch, 091h, 083h, 0F9h, 00Bh, 00Fh, 087h, 091h, 023h, 000h, 000h, 0FFh, 024h, 08Dh
    dd ?d_009148c0@@YAXXZ + 023E0h
    db 068h
    dd ??0KeyClass@?$PrimitiveAnimationChannelClass@VVector2@@@@QAE@XZ
    db 06Ah, 003h, 06Ah, 00Ch, 08Dh, 044h, 024h, 05Ch, 050h
    call ?j_0000ae5c@@YAXXZ
    db 0D9h, 045h, 034h, 00Fh, 0B6h, 045h, 048h, 0D9h, 0C0h, 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 08Bh
    db 094h, 024h, 010h, 001h, 000h, 000h, 033h, 0FFh, 083h, 0FAh, 004h, 0D8h, 088h
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va0134128C
    db 0D9h, 05Ch, 024h, 020h, 0D8h, 088h
    dd g_Va01341290
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 045h, 034h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va01341294
    db 0D9h, 05Ch, 024h, 03Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va01341298
    db 0D9h, 05Ch, 024h, 040h, 0D8h, 088h
    dd g_Va0134129C
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 045h, 034h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013412A0
    db 0D9h, 05Ch, 024h, 02Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013412A4
    db 0D9h, 05Ch, 024h, 030h, 0D8h, 088h
    dd g_Va013412A8
    db 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 034h, 00Fh, 08Ch, 086h, 001h, 000h
    db 000h, 08Dh, 04Ah, 0FCh, 0C1h, 0E9h, 002h, 041h, 08Dh, 03Ch, 08Dh, 000h, 000h, 000h, 000h, 08Dh
    db 064h, 024h, 000h, 0D9h, 044h, 024h, 01Ch, 0D8h, 000h, 0D9h, 01Eh, 0D9h, 044h, 024h, 020h, 0D8h
    db 040h, 004h, 0D9h, 05Eh, 004h, 0D9h, 044h, 024h, 024h, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h, 0D9h
    db 044h, 024h, 03Ch, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 004h, 0D9h
    db 05Eh, 010h, 0D9h, 044h, 024h, 044h, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 0D9h, 044h, 024h, 02Ch
    db 0D8h, 000h, 0D9h, 05Eh, 018h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch, 0D9h
    db 044h, 024h, 034h, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h, 00Ch
    db 0D9h, 05Eh, 024h, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 010h, 0D9h, 05Eh, 028h, 0D9h, 044h, 024h
    db 024h, 0D8h, 040h, 014h, 0D9h, 05Eh, 02Ch, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 00Ch, 0D9h, 05Eh
    db 030h, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 010h, 0D9h, 05Eh, 034h, 0D9h, 044h, 024h, 044h, 0D8h
    db 040h, 014h, 0D9h, 05Eh, 038h, 0D9h, 044h, 024h, 02Ch, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch, 0D9h
    db 044h, 024h, 030h, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 014h
    db 0D9h, 05Eh, 044h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h, 018h, 0D9h, 05Eh, 048h, 0D9h, 044h, 024h
    db 020h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 04Ch, 0D9h, 044h, 024h, 024h, 0D8h, 040h, 020h, 0D9h, 05Eh
    db 050h, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 018h, 0D9h, 05Eh, 054h, 0D9h, 044h, 024h, 040h, 0D8h
    db 040h, 01Ch, 0D9h, 05Eh, 058h, 0D9h, 044h, 024h, 044h, 0D8h, 040h, 020h, 0D9h, 05Eh, 05Ch, 0D9h
    db 044h, 024h, 02Ch, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 01Ch
    db 0D9h, 05Eh, 064h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 0D9h, 044h, 024h
    db 01Ch, 083h, 0C0h, 030h, 0D8h, 040h, 0F4h, 081h, 0C6h, 090h, 000h, 000h, 000h, 049h, 0D9h, 05Eh
    db 0DCh, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 044h, 024h, 024h, 0D8h
    db 040h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 0D9h
    db 044h, 024h, 040h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h, 044h, 0D8h, 040h, 0FCh
    db 0D9h, 05Eh, 0F0h, 0D9h, 044h, 024h, 02Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 0D9h, 044h, 024h
    db 030h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh
    db 0FCh, 00Fh, 085h, 08Ch, 0FEh, 0FFh, 0FFh, 03Bh, 0FAh, 00Fh, 08Dh, 057h, 021h, 000h, 000h, 02Bh
    db 0D7h, 08Bh, 0FFh, 0D9h, 044h, 024h, 01Ch, 083h, 0C0h, 00Ch, 0D8h, 040h, 0F4h, 083h, 0C6h, 024h
    db 04Ah, 0D9h, 05Eh, 0DCh, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 044h
    db 024h, 024h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 0F4h, 0D9h
    db 05Eh, 0E8h, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h, 044h
    db 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 0D9h, 044h, 024h, 02Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h
    db 0D9h, 044h, 024h, 030h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 044h, 024h, 034h, 0D8h, 040h
    db 0FCh, 0D9h, 05Eh, 0FCh, 075h, 09Dh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h
    db 0C2h, 010h, 000h, 08Bh, 09Ch, 024h, 010h, 001h, 000h, 000h, 08Bh, 084h, 024h, 004h, 001h, 000h
    db 000h, 033h, 0C9h, 083h, 0FBh, 004h, 00Fh, 08Ch, 05Dh, 003h, 000h, 000h, 08Dh, 053h, 0FCh, 0C1h
    db 0EAh, 002h, 042h, 08Dh, 00Ch, 095h, 000h, 000h, 000h, 000h, 089h, 04Ch, 024h, 018h, 0EBh, 003h
    db 08Dh, 049h, 000h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 01Eh, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 004h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va01341298
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 010h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 05Eh, 018h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va013412A4
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 024h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 028h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 02Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 030h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 034h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 038h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 044h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 048h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 04Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 050h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 054h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 058h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 05Ch, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 064h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 083h, 0C0h, 030h, 083h, 0C7h, 010h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 081h, 0C6h, 090h, 000h, 000h, 000h, 04Ah, 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh
    db 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 0BEh, 0FCh, 0FFh, 0FFh, 08Bh
    db 04Ch, 024h, 018h, 03Bh, 0CBh, 00Fh, 08Dh, 065h, 01Dh, 000h, 000h, 02Bh, 0D9h, 08Bh, 0D3h, 00Fh
    db 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h, 083h, 0C0h, 00Ch, 083h, 0C7h, 004h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 083h, 0C6h, 024h, 04Ah, 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh, 00Fh, 0B6h, 04Dh
    db 048h, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Dh, 048h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 021h, 0FFh, 0FFh, 0FFh, 05Fh
    db 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h, 0C2h, 010h, 000h, 08Bh, 0BCh, 024h, 010h
    db 001h, 000h, 000h, 033h, 0C9h, 083h, 0FFh, 004h, 00Fh, 08Ch, 068h, 003h, 000h, 000h, 08Dh, 057h
    db 0FCh, 0C1h, 0EAh, 002h, 042h, 08Dh, 004h, 095h, 000h, 000h, 000h, 000h, 089h, 044h, 024h, 018h
    db 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 00Fh, 0B6h
    db 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Dh, 034h, 0D8h, 000h, 0D9h, 01Eh, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 004h, 0D9h, 05Eh, 004h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Dh, 034h, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va01341298
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 004h, 0D9h, 05Eh, 010h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Dh, 034h, 0D8h, 000h, 0D9h, 05Eh, 018h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va013412A4
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 024h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 010h, 0D9h, 05Eh, 028h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 014h, 0D9h, 05Eh, 02Ch, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 030h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 010h, 0D9h, 05Eh, 034h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 014h, 0D9h, 05Eh, 038h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 014h, 0D9h, 05Eh, 044h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 018h, 0D9h, 05Eh, 048h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 04Ch, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 020h, 0D9h, 05Eh, 050h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 018h, 0D9h, 05Eh, 054h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 058h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 020h, 0D9h, 05Eh, 05Ch, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 064h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 00Fh, 0B6h, 04Bh, 003h, 08Dh, 00Ch, 0C9h
    db 083h, 0C0h, 030h, 083h, 0C3h, 004h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 081h, 0C6h, 090h, 000h, 000h, 000h, 04Ah, 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh
    db 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 0BEh, 0FCh, 0FFh, 0FFh, 08Bh
    db 04Ch, 024h, 018h, 0EBh, 007h, 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 03Bh, 0CFh, 00Fh, 08Dh
    db 0ECh, 018h, 000h, 000h, 02Bh, 0F9h, 08Bh, 0D7h, 0EBh, 003h, 08Dh, 049h, 000h, 00Fh, 0B6h, 00Bh
    db 08Dh, 00Ch, 0C9h, 083h, 0C0h, 00Ch, 043h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 083h, 0C6h, 024h, 04Ah, 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh, 00Fh, 0B6h, 04Bh
    db 0FFh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Dh, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 024h, 0FFh, 0FFh, 0FFh, 05Fh
    db 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h, 0C2h, 010h, 000h, 08Bh, 0ACh, 024h, 010h
    db 001h, 000h, 000h, 033h, 0C9h, 083h, 0FDh, 004h, 00Fh, 08Ch, 067h, 003h, 000h, 000h, 08Dh, 055h
    db 0FCh, 0C1h, 0EAh, 002h, 042h, 08Dh, 004h, 095h, 000h, 000h, 000h, 000h, 089h, 044h, 024h, 018h
    db 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 0EBh, 00Ah, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h
    db 08Dh, 049h, 000h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 01Eh, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 004h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va01341290
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va01341294
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 010h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va0134129C
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va013412A0
    db 0D8h, 00Fh, 0D8h, 000h, 0D9h, 05Eh, 018h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 00Fh, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 0D9h, 004h
    db 08Dh
    dd g_Va013412A8
    db 0D8h, 00Fh, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h, 0D9h
    db 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 024h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 028h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 02Ch, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 030h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 034h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 038h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h, 00Fh, 0B6h, 04Bh, 001h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 004h, 0D8h, 040h, 014h, 0D9h, 05Eh, 044h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 048h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 04Ch, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 050h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 054h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 058h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 05Ch, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 064h, 00Fh, 0B6h, 04Bh, 002h, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 008h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 00Fh, 0B6h, 04Bh, 003h, 08Dh, 00Ch, 0C9h
    db 083h, 0C0h, 030h, 083h, 0C7h, 010h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 083h, 0C3h, 004h, 0D8h, 04Fh, 0FCh, 081h, 0C6h, 090h, 000h, 000h, 000h, 04Ah, 0D8h, 040h, 0F4h
    db 0D9h, 05Eh, 0DCh, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 0C4h, 0FCh, 0FFh, 0FFh, 08Bh
    db 04Ch, 024h, 018h, 0EBh, 007h, 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 03Bh, 0CDh, 00Fh, 08Dh
    db 072h, 014h, 000h, 000h, 02Bh, 0E9h, 08Bh, 0D5h, 00Fh, 0B6h, 00Bh, 08Dh, 00Ch, 0C9h, 083h, 0C0h
    db 00Ch, 083h, 0C7h, 004h, 0D9h, 004h, 08Dh
    dd ?_TriVertexLocationOrientationTable@PointGroupClass@@2PAY02VVector3@@A
    db 043h, 0D8h, 04Fh, 0FCh, 083h, 0C6h, 024h, 04Ah, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh, 00Fh, 0B6h
    db 04Bh, 0FFh, 08Dh, 00Ch, 0C9h, 0D9h, 004h, 08Dh
    dd g_Va0134128C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341290
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341294
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va01341298
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va0134129C
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A0
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A4
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 00Fh, 0B6h, 04Bh, 0FFh, 08Dh, 00Ch, 0C9h
    db 0D9h, 004h, 08Dh
    dd g_Va013412A8
    db 0D8h, 04Fh, 0FCh, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 021h, 0FFh, 0FFh, 0FFh, 05Fh
    db 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h, 0C2h, 010h, 000h, 068h
    dd ??0KeyClass@?$PrimitiveAnimationChannelClass@VVector2@@@@QAE@XZ
    db 06Ah, 004h, 06Ah, 00Ch, 08Dh, 054h, 024h, 05Ch, 052h
    call ?j_0000ae5c@@YAXXZ
    db 0D9h, 045h, 034h, 0D9h, 0C0h, 00Fh, 0B6h, 045h, 048h, 08Dh, 004h, 040h, 0C1h, 0E0h, 004h, 08Bh
    db 094h, 024h, 010h, 001h, 000h, 000h, 033h, 0FFh, 083h, 0FAh, 004h, 0D8h, 088h
    dd ?_QuadVertexLocationOrientationTable@PointGroupClass@@2PAY03VVector3@@A
    db 0D9h, 05Ch, 024h, 02Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436BC
    db 0D9h, 05Ch, 024h, 030h, 0D8h, 088h
    dd g_Va013436C0
    db 0D9h, 05Ch, 024h, 034h, 0D9h, 045h, 034h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436C4
    db 0D9h, 05Ch, 024h, 03Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436C8
    db 0D9h, 05Ch, 024h, 040h, 0D8h, 088h
    dd g_Va013436CC
    db 0D9h, 05Ch, 024h, 044h, 0D9h, 045h, 034h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436D0
    db 0D9h, 05Ch, 024h, 01Ch, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436D4
    db 0D9h, 05Ch, 024h, 020h, 0D8h, 088h
    dd g_Va013436D8
    db 0D9h, 05Ch, 024h, 024h, 0D9h, 045h, 034h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436DC
    db 0D9h, 09Ch, 024h, 094h, 000h, 000h, 000h, 0D9h, 0C0h, 0D8h, 088h
    dd g_Va013436E0
    db 0D9h, 09Ch, 024h, 098h, 000h, 000h, 000h, 0D8h, 088h
    dd g_Va013436E4
    db 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 0D9h, 09Ch, 024h, 09Ch, 000h, 000h, 000h, 00Fh, 08Ch
    db 01Dh, 002h, 000h, 000h, 08Dh, 04Ah, 0FCh, 0C1h, 0E9h, 002h, 041h, 08Dh, 03Ch, 08Dh, 000h, 000h
    db 000h, 000h, 0D9h, 044h, 024h, 02Ch, 0D8h, 000h, 0D9h, 01Eh, 0D9h, 044h, 024h, 030h, 0D8h, 040h
    db 004h, 0D9h, 05Eh, 004h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h, 0D9h, 044h
    db 024h, 03Ch, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 004h, 0D9h, 05Eh
    db 010h, 0D9h, 044h, 024h, 044h, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 0D9h, 044h, 024h, 01Ch, 0D8h
    db 000h, 0D9h, 05Eh, 018h, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch, 0D9h, 044h
    db 024h, 024h, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h
    db 000h, 0D9h, 05Eh, 024h, 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 040h, 004h, 0D9h, 05Eh
    db 028h, 0D9h, 084h, 024h, 09Ch, 000h, 000h, 000h, 0D8h, 040h, 008h, 0D9h, 05Eh, 02Ch, 0D9h, 044h
    db 024h, 02Ch, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 030h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 010h, 0D9h
    db 05Eh, 034h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 014h, 0D9h, 05Eh, 038h, 0D9h, 044h, 024h, 03Ch
    db 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h
    db 0D9h, 044h, 024h, 044h, 0D8h, 040h, 014h, 0D9h, 05Eh, 044h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h
    db 00Ch, 0D9h, 05Eh, 048h, 0D9h, 044h, 024h, 020h, 0D8h, 040h, 010h, 0D9h, 05Eh, 04Ch, 0D9h, 044h
    db 024h, 024h, 0D8h, 040h, 014h, 0D9h, 05Eh, 050h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h
    db 040h, 00Ch, 0D9h, 05Eh, 054h, 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 040h, 010h, 0D9h
    db 05Eh, 058h, 0D9h, 084h, 024h, 09Ch, 000h, 000h, 000h, 0D8h, 040h, 014h, 0D9h, 05Eh, 05Ch, 0D9h
    db 044h, 024h, 02Ch, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 01Ch
    db 0D9h, 05Eh, 064h, 0D9h, 044h, 024h, 034h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 0D9h, 044h, 024h
    db 03Ch, 083h, 0C0h, 030h, 0D8h, 040h, 0E8h, 081h, 0C6h, 0C0h, 000h, 000h, 000h, 049h, 0D9h, 05Eh
    db 0ACh, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 0ECh, 0D9h, 05Eh, 0B0h, 0D9h, 044h, 024h, 044h, 0D8h
    db 040h, 0F0h, 0D9h, 05Eh, 0B4h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h, 0E8h, 0D9h, 05Eh, 0B8h, 0D9h
    db 044h, 024h, 020h, 0D8h, 040h, 0ECh, 0D9h, 05Eh, 0BCh, 0D9h, 044h, 024h, 024h, 0D8h, 040h, 0F0h
    db 0D9h, 05Eh, 0C0h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 040h, 0E8h, 0D9h, 05Eh, 0C4h
    db 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 040h, 0ECh, 0D9h, 05Eh, 0C8h, 0D9h, 084h, 024h
    db 09Ch, 000h, 000h, 000h, 0D8h, 040h, 0F0h, 0D9h, 05Eh, 0CCh, 0D9h, 044h, 024h, 02Ch, 0D8h, 040h
    db 0F4h, 0D9h, 05Eh, 0D0h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0D4h, 0D9h, 044h
    db 024h, 034h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0D8h, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 0F4h, 0D9h
    db 05Eh, 0DCh, 0D9h, 044h, 024h, 040h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 044h, 024h, 044h
    db 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h
    db 0D9h, 044h, 024h, 020h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h, 024h, 0D8h, 040h
    db 0FCh, 0D9h, 05Eh, 0F0h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 040h, 0F4h, 0D9h, 05Eh
    db 0F4h, 0D9h, 084h, 024h, 098h, 000h, 000h, 000h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 084h
    db 024h, 09Ch, 000h, 000h, 000h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 0F1h, 0FDh, 0FFh
    db 0FFh, 03Bh, 0FAh, 00Fh, 08Dh, 08Ah, 010h, 000h, 000h, 02Bh, 0D7h, 0EBh, 003h, 08Dh, 049h, 000h
    db 0D9h, 044h, 024h, 02Ch, 083h, 0C0h, 00Ch, 0D8h, 040h, 0F4h, 083h, 0C6h, 030h, 04Ah, 0D9h, 05Eh
    db 0D0h, 0D9h, 044h, 024h, 030h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0D4h, 0D9h, 044h, 024h, 034h, 0D8h
    db 040h, 0FCh, 0D9h, 05Eh, 0D8h, 0D9h, 044h, 024h, 03Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0DCh, 0D9h
    db 044h, 024h, 040h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 044h, 024h, 044h, 0D8h, 040h, 0FCh
    db 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 01Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h, 0D9h, 044h, 024h
    db 020h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h, 024h, 0D8h, 040h, 0FCh, 0D9h, 05Eh
    db 0F0h, 0D9h, 084h, 024h, 094h, 000h, 000h, 000h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 0D9h, 084h
    db 024h, 098h, 000h, 000h, 000h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 084h, 024h, 09Ch, 000h
    db 000h, 000h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 072h, 0FFh, 0FFh, 0FFh, 05Fh, 05Eh
    db 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h, 0C2h, 010h, 000h, 08Bh, 0B4h, 024h, 010h, 001h
    db 000h, 000h, 085h, 0F6h, 00Fh, 08Eh, 0D9h, 00Fh, 000h, 000h, 08Bh, 08Ch, 024h, 004h, 001h, 000h
    db 000h, 083h, 0C0h, 008h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h, 0D9h, 082h
    dd ?_QuadVertexLocationOrientationTable@PointGroupClass@@2PAY03VVector3@@A
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 0F8h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436BC
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 0FCh, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436C0
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 018h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436C4
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 004h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436C8
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 008h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436CC
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 058h, 00Ch, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436D0
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 010h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436D4
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 014h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436D8
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 058h, 018h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436DC
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 01Ch, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436E0
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 020h, 00Fh, 0B6h, 055h, 048h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436E4
    db 0D8h, 00Fh, 083h, 0C0h, 030h, 083h, 0C1h, 00Ch, 083h, 0C7h, 004h, 04Eh, 0D8h, 041h, 0FCh, 0D9h
    db 058h, 0F4h, 00Fh, 085h, 0D5h, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h
    db 000h, 000h, 0C2h, 010h, 000h, 08Bh, 0B4h, 024h, 010h, 001h, 000h, 000h, 085h, 0F6h, 00Fh, 08Eh
    db 088h, 00Eh, 000h, 000h, 08Bh, 08Ch, 024h, 004h, 001h, 000h, 000h, 083h, 0C0h, 008h, 00Fh, 0B6h
    db 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h, 0D9h, 082h
    dd ?_QuadVertexLocationOrientationTable@PointGroupClass@@2PAY03VVector3@@A
    db 0D8h, 04Dh, 034h, 0D8h, 001h, 0D9h, 058h, 0F8h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436BC
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 004h, 0D9h, 058h, 0FCh, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436C0
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 008h, 0D9h, 018h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436C4
    db 0D8h, 04Dh, 034h, 0D8h, 001h, 0D9h, 058h, 004h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436C8
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 004h, 0D9h, 058h, 008h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436CC
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 008h, 0D9h, 058h, 00Ch, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436D0
    db 0D8h, 04Dh, 034h, 0D8h, 001h, 0D9h, 058h, 010h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436D4
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 004h, 0D9h, 058h, 014h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436D8
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 008h, 0D9h, 058h, 018h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436DC
    db 0D8h, 04Dh, 034h, 0D8h, 001h, 0D9h, 058h, 01Ch, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436E0
    db 0D8h, 04Dh, 034h, 0D8h, 041h, 004h, 0D9h, 058h, 020h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h
    db 0E2h, 004h, 0D9h, 082h
    dd g_Va013436E4
    db 0D8h, 04Dh, 034h, 083h, 0C0h, 030h, 083h, 0C1h, 00Ch, 043h, 04Eh, 0D8h, 041h, 0FCh, 0D9h, 058h
    db 0F4h, 00Fh, 085h, 0D7h, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h
    db 000h, 0C2h, 010h, 000h, 0F6h, 045h, 030h, 002h, 00Fh, 085h, 057h, 004h, 000h, 000h, 0F7h, 005h
    dd ?Rva0133F49CChanged@@3IA
    db 000h, 000h, 008h, 000h, 074h, 062h, 0C7h, 044h, 024h, 050h, 000h, 000h, 080h, 03Fh, 0C7h, 044h
    db 024h, 054h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 058h, 000h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 05Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 060h, 000h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 064h, 000h, 000h, 080h, 03Fh, 0C7h, 044h, 024h, 068h, 000h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 06Ch, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 070h, 000h, 000h, 000h, 000h, 0C7h, 044h
    db 024h, 074h, 000h, 000h, 000h, 000h, 0C7h, 044h, 024h, 078h, 000h, 000h, 080h, 03Fh, 0C7h, 044h
    db 024h, 07Ch, 000h, 000h, 000h, 000h, 0EBh, 078h, 08Bh, 00Dh
    dd ?render_state_view@DX8Wrapper@@0VMatrix4@@A
    db 08Bh, 015h
    dd g_Va013410DC
    db 089h, 04Ch, 024h, 050h, 08Bh, 00Dh
    dd g_Va013410EC
    db 089h, 054h, 024h, 054h, 08Bh, 015h
    dd g_Va013410FC
    db 089h, 04Ch, 024h, 058h, 08Bh, 00Dh
    dd g_Va013410D0
    db 089h, 054h, 024h, 05Ch, 08Bh, 015h
    dd g_Va013410E0
    db 089h, 04Ch, 024h, 060h, 08Bh, 00Dh
    dd g_Va013410F0
    db 089h, 054h, 024h, 064h, 08Bh, 015h
    dd g_Va01341100
    db 089h, 04Ch, 024h, 068h, 08Bh, 00Dh
    dd g_Va013410D4
    db 089h, 054h, 024h, 06Ch, 08Bh, 015h
    dd g_Va013410E4
    db 089h, 04Ch, 024h, 070h, 08Bh, 00Dh
    dd g_Va013410F4
    db 089h, 054h, 024h, 074h, 08Bh, 015h
    dd g_Va01341104
    db 089h, 04Ch, 024h, 078h, 089h, 054h, 024h, 07Ch, 08Bh, 08Ch, 024h, 010h, 001h, 000h, 000h, 085h
    db 0C9h, 00Fh, 08Eh, 049h, 00Ch, 000h, 000h, 08Bh, 0ACh, 024h, 004h, 001h, 000h, 000h, 08Dh, 070h
    db 010h, 089h, 04Ch, 024h, 018h, 00Fh, 0B6h, 003h, 089h, 044h, 024h, 04Ch, 051h, 0DBh, 044h, 024h
    db 050h, 08Dh, 08Ch, 024h, 0A8h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va0113ACDC
    db 0D9h, 01Ch, 024h, 051h
    call ?ji_009fb93b@@YAXXZ
    db 0D9h, 084h, 024h, 0ACh, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F38
    db 0D9h, 084h, 024h, 0A8h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F34
    db 0DEh, 0C1h, 0D9h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F30
    db 0DEh, 0C1h, 0D8h, 084h, 024h, 0B0h, 000h, 000h, 000h, 0D9h, 084h, 024h, 0BCh, 000h, 000h, 000h
    db 0D8h, 00Dh
    dd g_Va012D6F38
    db 0D9h, 084h, 024h, 0B8h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F34
    db 0DEh, 0C1h, 0D9h, 084h, 024h, 0B4h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F30
    db 0DEh, 0C1h, 0D8h, 084h, 024h, 0C0h, 000h, 000h, 000h, 0D9h, 084h, 024h, 0ACh, 000h, 000h, 000h
    db 0D8h, 00Dh
    dd g_Va012D6F44
    db 0D9h, 084h, 024h, 0A8h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F40
    db 0DEh, 0C1h, 0D9h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F3C
    db 0DEh, 0C1h, 0D8h, 084h, 024h, 0B0h, 000h, 000h, 000h, 0D9h, 084h, 024h, 0BCh, 000h, 000h, 000h
    db 0D8h, 00Dh
    dd g_Va012D6F44
    db 0D9h, 084h, 024h, 0B8h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F40
    db 0DEh, 0C1h, 0D9h, 084h, 024h, 0B4h, 000h, 000h, 000h, 0D8h, 00Dh
    dd g_Va012D6F3C
    db 0DEh, 0C1h, 0D8h, 084h, 024h, 0C0h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 098h, 000h, 000h, 000h
    db 0D9h, 0C0h, 0D8h, 0C3h, 0D8h, 00Fh, 0D9h, 05Ch, 024h, 014h, 0D9h, 084h, 024h, 098h, 000h, 000h
    db 000h, 0D8h, 0C2h, 0D8h, 00Fh, 0D9h, 05Ch, 024h, 010h, 0D9h, 0CAh, 0D8h, 0E2h, 0D8h, 00Fh, 0D9h
    db 05Ch, 024h, 04Ch, 0DDh, 0D9h, 0D8h, 0A4h, 024h, 098h, 000h, 000h, 000h, 0D8h, 00Fh, 0D9h, 044h
    db 024h, 014h, 0D8h, 045h, 000h, 0D9h, 05Eh, 0F0h, 0D9h, 044h, 024h, 010h, 0D8h, 045h, 004h, 0D9h
    db 05Eh, 0F4h, 08Bh, 055h, 008h, 0D9h, 044h, 024h, 04Ch, 089h, 056h, 0F8h, 0D8h, 045h, 000h, 0D9h
    db 05Eh, 0FCh, 0D9h, 0C0h, 0D8h, 045h, 004h, 0D9h, 01Eh, 08Bh, 045h, 008h, 089h, 046h, 004h, 0D9h
    db 045h, 000h, 0D8h, 064h, 024h, 014h, 0D9h, 05Eh, 008h, 0D9h, 045h, 004h, 0D8h, 064h, 024h, 010h
    db 0D9h, 05Eh, 00Ch, 08Bh, 04Dh, 008h, 089h, 04Eh, 010h, 0D9h, 045h, 000h, 0D8h, 064h, 024h, 04Ch
    db 0D9h, 05Eh, 014h, 0D9h, 045h, 004h, 0D8h, 0E1h, 0D9h, 05Eh, 018h, 08Bh, 055h, 008h, 089h, 056h
    db 01Ch, 0DDh, 0D8h, 0D9h, 044h, 024h, 058h, 0D8h, 04Eh, 0F8h, 0D9h, 044h, 024h, 054h, 0D8h, 04Eh
    db 0F4h, 0DEh, 0C1h, 0D9h, 044h, 024h, 050h, 0D8h, 04Eh, 0F0h, 0DEh, 0C1h, 0D8h, 044h, 024h, 05Ch
    db 0D9h, 044h, 024h, 068h, 0D8h, 04Eh, 0F8h, 0D9h, 044h, 024h, 064h, 0D8h, 04Eh, 0F4h, 0DEh, 0C1h
    db 0D9h, 044h, 024h, 060h, 0D8h, 04Eh, 0F0h, 0DEh, 0C1h, 0D8h, 044h, 024h, 06Ch, 0D9h, 044h, 024h
    db 078h, 0D8h, 04Eh, 0F8h, 0D9h, 044h, 024h, 074h, 0D8h, 04Eh, 0F4h, 0DEh, 0C1h, 0D9h, 044h, 024h
    db 070h, 0D8h, 04Eh, 0F0h, 0DEh, 0C1h, 0D8h, 044h, 024h, 07Ch, 0D9h, 05Ch, 024h, 034h, 08Bh, 044h
    db 024h, 034h, 0D9h, 0C9h, 089h, 046h, 0F8h, 0D9h, 05Eh, 0F0h, 0D9h, 05Eh, 0F4h, 0D9h, 044h, 024h
    db 054h, 0D8h, 00Eh, 0D9h, 044h, 024h, 050h, 0D8h, 04Eh, 0FCh, 0DEh, 0C1h, 0D9h, 044h, 024h, 058h
    db 0D8h, 04Eh, 004h, 0DEh, 0C1h, 0D8h, 044h, 024h, 05Ch, 0D9h, 044h, 024h, 064h, 0D8h, 00Eh, 0D9h
    db 044h, 024h, 060h, 0D8h, 04Eh, 0FCh, 0DEh, 0C1h, 0D9h, 044h, 024h, 068h, 0D8h, 04Eh, 004h, 0DEh
    db 0C1h, 0D8h, 044h, 024h, 06Ch, 0D9h, 044h, 024h, 074h, 0D8h, 00Eh, 0D9h, 044h, 024h, 070h, 0D8h
    db 04Eh, 0FCh, 0DEh, 0C1h, 0D9h, 044h, 024h, 078h, 0D8h, 04Eh, 004h, 0DEh, 0C1h, 0D8h, 044h, 024h
    db 07Ch, 0D9h, 05Ch, 024h, 044h, 0D9h, 0C9h, 0D9h, 05Eh, 0FCh, 0D9h, 01Eh, 08Bh, 04Ch, 024h, 044h
    db 0D9h, 044h, 024h, 058h, 089h, 04Eh, 004h, 0D8h, 04Eh, 010h, 0D9h, 044h, 024h, 054h, 083h, 0C6h
    db 030h, 0D8h, 04Eh, 0DCh, 083h, 0C5h, 00Ch, 043h, 083h, 0C7h, 004h, 0DEh, 0C1h, 0D9h, 044h, 024h
    db 050h, 0D8h, 04Eh, 0D8h, 0DEh, 0C1h, 0D8h, 044h, 024h, 05Ch, 0D9h, 044h, 024h, 060h, 0D8h, 04Eh
    db 0D8h, 0D9h, 044h, 024h, 064h, 0D8h, 04Eh, 0DCh, 0DEh, 0C1h, 0D9h, 044h, 024h, 068h, 0D8h, 04Eh
    db 0E0h, 0DEh, 0C1h, 0D8h, 044h, 024h, 06Ch, 0D9h, 044h, 024h, 070h, 0D8h, 04Eh, 0D8h, 0D9h, 044h
    db 024h, 074h, 0D8h, 04Eh, 0DCh, 0DEh, 0C1h, 0D9h, 044h, 024h, 078h, 0D8h, 04Eh, 0E0h, 0DEh, 0C1h
    db 0D8h, 044h, 024h, 07Ch, 0D9h, 05Ch, 024h, 024h, 08Bh, 054h, 024h, 024h, 0D9h, 0C9h, 089h, 056h
    db 0E0h, 0D9h, 05Eh, 0D8h, 0D9h, 05Eh, 0DCh, 0D9h, 044h, 024h, 050h, 0D8h, 04Eh, 0E4h, 0D9h, 044h
    db 024h, 058h, 0D8h, 04Eh, 0ECh, 0DEh, 0C1h, 0D9h, 044h, 024h, 054h, 0D8h, 04Eh, 0E8h, 0DEh, 0C1h
    db 0D8h, 044h, 024h, 05Ch, 0D9h, 044h, 024h, 060h, 0D8h, 04Eh, 0E4h, 0D9h, 044h, 024h, 064h, 0D8h
    db 04Eh, 0E8h, 0DEh, 0C1h, 0D9h, 044h, 024h, 068h, 0D8h, 04Eh, 0ECh, 0DEh, 0C1h, 0D8h, 044h, 024h
    db 06Ch, 0D9h, 044h, 024h, 070h, 0D8h, 04Eh, 0E4h, 0D9h, 044h, 024h, 074h, 0D8h, 04Eh, 0E8h, 0DEh
    db 0C1h, 0D9h, 044h, 024h, 078h, 0D8h, 04Eh, 0ECh, 0DEh, 0C1h, 0D8h, 044h, 024h, 07Ch, 0D9h, 09Ch
    db 024h, 0F8h, 000h, 000h, 000h, 08Bh, 084h, 024h, 0F8h, 000h, 000h, 000h, 0D9h, 0C9h, 089h, 046h
    db 0ECh, 08Bh, 044h, 024h, 018h, 0D9h, 05Eh, 0E4h, 048h, 0D9h, 05Eh, 0E8h, 089h, 044h, 024h, 018h
    db 00Fh, 085h, 0B9h, 0FCh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h, 000h
    db 0C2h, 010h, 000h, 08Bh, 0B4h, 024h, 010h, 001h, 000h, 000h, 085h, 0F6h, 00Fh, 08Eh, 0D8h, 008h
    db 000h, 000h, 08Bh, 08Ch, 024h, 004h, 001h, 000h, 000h, 083h, 0C0h, 008h, 00Fh, 0B6h, 013h, 08Dh
    db 014h, 052h, 0C1h, 0E2h, 004h, 0D9h, 082h
    dd ?_QuadVertexLocationOrientationTable@PointGroupClass@@2PAY03VVector3@@A
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 0F8h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h
    db 0D9h, 082h
    dd g_Va013436BC
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 0FCh, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436C0
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 018h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h
    db 0D9h, 082h
    dd g_Va013436C4
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 004h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h
    db 0D9h, 082h
    dd g_Va013436C8
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 008h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436CC
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 058h, 00Ch, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436D0
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 010h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h
    db 0D9h, 082h
    dd g_Va013436D4
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 014h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436D8
    db 0D8h, 00Fh, 0D8h, 041h, 008h, 0D9h, 058h, 018h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436DC
    db 0D8h, 00Fh, 0D8h, 001h, 0D9h, 058h, 01Ch, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h, 004h
    db 0D9h, 082h
    dd g_Va013436E0
    db 0D8h, 00Fh, 0D8h, 041h, 004h, 0D9h, 058h, 020h, 00Fh, 0B6h, 013h, 08Dh, 014h, 052h, 0C1h, 0E2h
    db 004h, 0D9h, 082h
    dd g_Va013436E4
    db 0D8h, 00Fh, 083h, 0C0h, 030h, 083h, 0C1h, 00Ch, 043h, 0D8h, 041h, 0FCh, 083h, 0C7h, 004h, 04Eh
    db 0D9h, 058h, 0F4h, 00Fh, 085h, 0E0h, 0FEh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h
    db 000h, 000h, 000h, 0C2h, 010h, 000h, 08Dh, 084h, 024h, 093h, 000h, 000h, 000h, 050h, 08Dh, 08Ch
    db 024h, 0F0h, 000h, 000h, 000h, 051h, 08Dh, 054h, 024h, 054h, 052h, 08Dh, 044h, 024h, 024h, 050h
    call ?Get_Render_Target_Resolution@WW3D@@SAXAAH00AA_N@Z
    db 0D9h, 045h, 054h, 0D8h, 065h, 04Ch, 083h, 0C4h, 010h, 0DAh, 074h, 024h, 018h, 0D9h, 05Ch, 024h
    db 014h, 0D9h, 045h, 058h, 0D8h, 065h, 050h, 0DAh, 074h, 024h, 04Ch, 0D9h, 05Ch, 024h, 010h, 0D9h
    db 045h, 034h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0FFh, 0EBh, 005h, 0BFh, 001h, 000h, 000h, 000h
    db 068h
    dd ??0KeyClass@?$PrimitiveAnimationChannelClass@VVector2@@@@QAE@XZ
    db 06Ah, 003h, 06Ah, 00Ch, 08Dh, 04Ch, 024h, 05Ch, 051h
    call ?j_0000ae5c@@YAXXZ
    db 0D9h, 044h, 024h, 014h, 08Dh, 004h, 0FFh, 0C1h, 0E0h, 002h, 0D8h, 088h
    dd g_Va012D6EE8
    db 08Bh, 090h
    dd g_Va012D6EF0
    db 08Bh, 088h
    dd g_Va012D6EFC
    db 089h, 054h, 024h, 058h, 0D9h, 05Ch, 024h, 050h, 08Bh, 090h
    dd g_Va012D6F08
    db 0D9h, 044h, 024h, 010h, 089h, 054h, 024h, 070h, 0D8h, 088h
    dd g_Va012D6EEC
    db 08Bh, 094h, 024h, 010h, 001h, 000h, 000h, 033h, 0FFh, 083h, 0FAh, 004h, 0D9h, 05Ch, 024h, 054h
    db 089h, 04Ch, 024h, 064h, 0D9h, 044h, 024h, 014h, 0D8h, 088h
    dd g_Va012D6EF4
    db 0D9h, 05Ch, 024h, 05Ch, 0D9h, 044h, 024h, 010h, 0D8h, 088h
    dd g_Va012D6EF8
    db 0D9h, 05Ch, 024h, 060h, 0D9h, 044h, 024h, 014h, 0D8h, 088h
    dd g_Va012D6F00
    db 0D9h, 05Ch, 024h, 068h, 0D9h, 044h, 024h, 010h, 0D8h, 088h
    dd g_Va012D6F04
    db 08Bh, 084h, 024h, 004h, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 06Ch, 00Fh, 08Ch, 087h, 001h, 000h
    db 000h, 08Dh, 04Ah, 0FCh, 0C1h, 0E9h, 002h, 041h, 08Dh, 03Ch, 08Dh, 000h, 000h, 000h, 000h, 0EBh
    db 003h, 08Dh, 049h, 000h, 0D9h, 044h, 024h, 050h, 0D8h, 000h, 0D9h, 01Eh, 0D9h, 044h, 024h, 054h
    db 0D8h, 040h, 004h, 0D9h, 05Eh, 004h, 0D9h, 044h, 024h, 058h, 0D8h, 040h, 008h, 0D9h, 05Eh, 008h
    db 0D9h, 044h, 024h, 05Ch, 0D8h, 000h, 0D9h, 05Eh, 00Ch, 0D9h, 044h, 024h, 060h, 0D8h, 040h, 004h
    db 0D9h, 05Eh, 010h, 0D9h, 044h, 024h, 064h, 0D8h, 040h, 008h, 0D9h, 05Eh, 014h, 0D9h, 044h, 024h
    db 068h, 0D8h, 000h, 0D9h, 05Eh, 018h, 0D9h, 044h, 024h, 06Ch, 0D8h, 040h, 004h, 0D9h, 05Eh, 01Ch
    db 0D9h, 044h, 024h, 070h, 0D8h, 040h, 008h, 0D9h, 05Eh, 020h, 0D9h, 044h, 024h, 050h, 0D8h, 040h
    db 00Ch, 0D9h, 05Eh, 024h, 0D9h, 044h, 024h, 054h, 0D8h, 040h, 010h, 0D9h, 05Eh, 028h, 0D9h, 044h
    db 024h, 058h, 0D8h, 040h, 014h, 0D9h, 05Eh, 02Ch, 0D9h, 044h, 024h, 05Ch, 0D8h, 040h, 00Ch, 0D9h
    db 05Eh, 030h, 0D9h, 044h, 024h, 060h, 0D8h, 040h, 010h, 0D9h, 05Eh, 034h, 0D9h, 044h, 024h, 064h
    db 0D8h, 040h, 014h, 0D9h, 05Eh, 038h, 0D9h, 044h, 024h, 068h, 0D8h, 040h, 00Ch, 0D9h, 05Eh, 03Ch
    db 0D9h, 044h, 024h, 06Ch, 0D8h, 040h, 010h, 0D9h, 05Eh, 040h, 0D9h, 044h, 024h, 070h, 0D8h, 040h
    db 014h, 0D9h, 05Eh, 044h, 0D9h, 044h, 024h, 050h, 0D8h, 040h, 018h, 0D9h, 05Eh, 048h, 0D9h, 044h
    db 024h, 054h, 0D8h, 040h, 01Ch, 0D9h, 05Eh, 04Ch, 0D9h, 044h, 024h, 058h, 0D8h, 040h, 020h, 0D9h
    db 05Eh, 050h, 0D9h, 044h, 024h, 05Ch, 0D8h, 040h, 018h, 0D9h, 05Eh, 054h, 0D9h, 044h, 024h, 060h
    db 0D8h, 040h, 01Ch, 0D9h, 05Eh, 058h, 0D9h, 044h, 024h, 064h, 0D8h, 040h, 020h, 0D9h, 05Eh, 05Ch
    db 0D9h, 044h, 024h, 068h, 0D8h, 040h, 018h, 0D9h, 05Eh, 060h, 0D9h, 044h, 024h, 06Ch, 0D8h, 040h
    db 01Ch, 0D9h, 05Eh, 064h, 0D9h, 044h, 024h, 070h, 0D8h, 040h, 020h, 0D9h, 05Eh, 068h, 0D9h, 044h
    db 024h, 050h, 083h, 0C0h, 030h, 0D8h, 040h, 0F4h, 081h, 0C6h, 090h, 000h, 000h, 000h, 049h, 0D9h
    db 05Eh, 0DCh, 0D9h, 044h, 024h, 054h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 044h, 024h, 058h
    db 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 05Ch, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0E8h
    db 0D9h, 044h, 024h, 060h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h, 064h, 0D8h, 040h
    db 0FCh, 0D9h, 05Eh, 0F0h, 0D9h, 044h, 024h, 068h, 0D8h, 040h, 0F4h, 0D9h, 05Eh, 0F4h, 0D9h, 044h
    db 024h, 06Ch, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 044h, 024h, 070h, 0D8h, 040h, 0FCh, 0D9h
    db 05Eh, 0FCh, 00Fh, 085h, 08Ch, 0FEh, 0FFh, 0FFh, 03Bh, 0FAh, 00Fh, 08Dh, 017h, 005h, 000h, 000h
    db 02Bh, 0D7h, 08Bh, 0FFh, 0D9h, 044h, 024h, 050h, 083h, 0C0h, 00Ch, 0D8h, 040h, 0F4h, 083h, 0C6h
    db 024h, 04Ah, 0D9h, 05Eh, 0DCh, 0D9h, 044h, 024h, 054h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h
    db 044h, 024h, 058h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 044h, 024h, 05Ch, 0D8h, 040h, 0F4h
    db 0D9h, 05Eh, 0E8h, 0D9h, 044h, 024h, 060h, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 044h, 024h
    db 064h, 0D8h, 040h, 0FCh, 0D9h, 05Eh, 0F0h, 0D9h, 044h, 024h, 068h, 0D8h, 040h, 0F4h, 0D9h, 05Eh
    db 0F4h, 0D9h, 044h, 024h, 06Ch, 0D8h, 040h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 044h, 024h, 070h, 0D8h
    db 040h, 0FCh, 0D9h, 05Eh, 0FCh, 075h, 09Dh, 05Fh, 05Eh, 05Dh, 05Bh, 081h, 0C4h, 0F0h, 000h, 000h
    db 000h, 0C2h, 010h, 000h, 08Dh, 084h, 024h, 093h, 000h, 000h, 000h, 050h, 08Dh, 08Ch, 024h, 0F0h
    db 000h, 000h, 000h, 051h, 08Dh, 054h, 024h, 054h, 052h, 08Dh, 044h, 024h, 024h, 050h
    call ?Get_Render_Target_Resolution@WW3D@@SAXAAH00AA_N@Z
    db 0D9h, 045h, 054h, 0D8h, 065h, 04Ch, 083h, 0C4h, 010h, 0DAh, 074h, 024h, 018h, 068h
    dd ??0KeyClass@?$PrimitiveAnimationChannelClass@VVector2@@@@QAE@XZ
    db 06Ah, 006h, 06Ah, 00Ch, 08Dh, 08Ch, 024h, 0B0h, 000h, 000h, 000h, 051h, 0D9h, 05Ch, 024h, 020h
    db 0D9h, 045h, 058h, 0D8h, 065h, 050h, 0DAh, 074h, 024h, 05Ch, 0D9h, 05Ch, 024h, 024h
    call ?j_0000ae5c@@YAXXZ
    db 0D9h, 005h
    dd g_Va012D6EE8
    db 0D8h, 04Ch, 024h, 010h, 08Bh, 015h
    dd g_Va012D6EF0
    db 08Bh, 00Dh
    dd g_Va012D6F08
    db 0A1h
    dd g_Va012D6EFC
    db 089h, 094h, 024h, 0ACh, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0A4h, 000h, 000h, 000h, 08Bh, 015h
    dd g_Va012D6F14
    db 0D9h, 005h
    dd g_Va012D6EEC
    db 089h, 08Ch, 024h, 0C4h, 000h, 000h, 000h, 0D8h, 04Ch, 024h, 014h, 08Bh, 00Dh
    dd g_Va012D6F2C
    db 089h, 094h, 024h, 0D0h, 000h, 000h, 000h, 08Bh, 094h, 024h, 010h, 001h, 000h, 000h, 0D9h, 09Ch
    db 024h, 0A8h, 000h, 000h, 000h, 089h, 084h, 024h, 0B8h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6EF4
    db 0A1h
    dd g_Va012D6F20
    db 0D8h, 04Ch, 024h, 010h, 033h, 0EDh, 083h, 0FAh, 004h, 089h, 08Ch, 024h, 0E8h, 000h, 000h, 000h
    db 0D9h, 09Ch, 024h, 0B0h, 000h, 000h, 000h, 08Bh, 08Ch, 024h, 004h, 001h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6EF8
    db 089h, 084h, 024h, 0DCh, 000h, 000h, 000h, 0D8h, 04Ch, 024h, 014h, 0D9h, 09Ch, 024h, 0B4h, 000h
    db 000h, 000h, 0D9h, 005h
    dd g_Va012D6F00
    db 0D8h, 04Ch, 024h, 010h, 0D9h, 09Ch, 024h, 0BCh, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F04
    db 0D8h, 04Ch, 024h, 014h, 0D9h, 09Ch, 024h, 0C0h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F0C
    db 0D8h, 04Ch, 024h, 010h, 0D9h, 09Ch, 024h, 0C8h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F10
    db 0D8h, 04Ch, 024h, 014h, 0D9h, 09Ch, 024h, 0CCh, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F18
    db 0D8h, 04Ch, 024h, 010h, 0D9h, 09Ch, 024h, 0D4h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F1C
    db 0D8h, 04Ch, 024h, 014h, 0D9h, 09Ch, 024h, 0D8h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F24
    db 0D8h, 04Ch, 024h, 010h, 0D9h, 09Ch, 024h, 0E0h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va012D6F28
    db 0D8h, 04Ch, 024h, 014h, 0D9h, 09Ch, 024h, 0E4h, 000h, 000h, 000h, 00Fh, 08Ch, 06Ch, 002h, 000h
    db 000h, 08Dh, 05Ah, 0FCh, 0C1h, 0EBh, 002h, 043h, 08Dh, 02Ch, 09Dh, 000h, 000h, 000h, 000h, 0D9h
    db 007h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0C0h, 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 0D9h, 084h, 004h, 0A4h, 000h, 000h, 000h, 0D8h, 001h, 0D9h
    db 01Eh, 0D9h, 084h, 004h, 0A8h, 000h, 000h, 000h, 0D8h, 041h, 004h, 0D9h, 05Eh, 004h, 0D9h, 084h
    db 004h, 0ACh, 000h, 000h, 000h, 0D8h, 041h, 008h, 0D9h, 05Eh, 008h, 0D9h, 084h, 004h, 0B0h, 000h
    db 000h, 000h, 0D8h, 001h, 0D9h, 05Eh, 00Ch, 0D9h, 084h, 004h, 0B4h, 000h, 000h, 000h, 0D8h, 041h
    db 004h, 0D9h, 05Eh, 010h, 0D9h, 084h, 004h, 0B8h, 000h, 000h, 000h, 0D8h, 041h, 008h, 0D9h, 05Eh
    db 014h, 0D9h, 084h, 004h, 0BCh, 000h, 000h, 000h, 0D8h, 001h, 0D9h, 05Eh, 018h, 0D9h, 084h, 004h
    db 0C0h, 000h, 000h, 000h, 0D8h, 041h, 004h, 0D9h, 05Eh, 01Ch, 0D9h, 084h, 004h, 0C4h, 000h, 000h
    db 000h, 0D8h, 041h, 008h, 0D9h, 05Eh, 020h, 0D9h, 047h, 004h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0C0h, 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 0D9h, 084h, 004h, 0A4h, 000h, 000h, 000h, 0D8h, 041h, 00Ch
    db 0D9h, 05Eh, 024h, 0D9h, 084h, 004h, 0A8h, 000h, 000h, 000h, 0D8h, 041h, 010h, 0D9h, 05Eh, 028h
    db 0D9h, 084h, 004h, 0ACh, 000h, 000h, 000h, 0D8h, 041h, 014h, 0D9h, 05Eh, 02Ch, 0D9h, 084h, 004h
    db 0B0h, 000h, 000h, 000h, 0D8h, 041h, 00Ch, 0D9h, 05Eh, 030h, 0D9h, 084h, 004h, 0B4h, 000h, 000h
    db 000h, 0D8h, 041h, 010h, 0D9h, 05Eh, 034h, 0D9h, 084h, 004h, 0B8h, 000h, 000h, 000h, 0D8h, 041h
    db 014h, 0D9h, 05Eh, 038h, 0D9h, 084h, 004h, 0BCh, 000h, 000h, 000h, 0D8h, 041h, 00Ch, 0D9h, 05Eh
    db 03Ch, 0D9h, 084h, 004h, 0C0h, 000h, 000h, 000h, 0D8h, 041h, 010h, 0D9h, 05Eh, 040h, 0D9h, 084h
    db 004h, 0C4h, 000h, 000h, 000h, 0D8h, 041h, 014h, 0D9h, 05Eh, 044h, 0D9h, 047h, 008h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0C0h, 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 0D9h, 084h, 004h, 0A4h, 000h, 000h, 000h, 0D8h, 041h, 018h
    db 0D9h, 05Eh, 048h, 0D9h, 084h, 004h, 0A8h, 000h, 000h, 000h, 0D8h, 041h, 01Ch, 0D9h, 05Eh, 04Ch
    db 0D9h, 084h, 004h, 0ACh, 000h, 000h, 000h, 0D8h, 041h, 020h, 0D9h, 05Eh, 050h, 0D9h, 084h, 004h
    db 0B0h, 000h, 000h, 000h, 0D8h, 041h, 018h, 0D9h, 05Eh, 054h, 0D9h, 084h, 004h, 0B4h, 000h, 000h
    db 000h, 0D8h, 041h, 01Ch, 0D9h, 05Eh, 058h, 0D9h, 084h, 004h, 0B8h, 000h, 000h, 000h, 0D8h, 041h
    db 020h, 0D9h, 05Eh, 05Ch, 0D9h, 084h, 004h, 0BCh, 000h, 000h, 000h, 0D8h, 041h, 018h, 0D9h, 05Eh
    db 060h, 0D9h, 084h, 004h, 0C0h, 000h, 000h, 000h, 0D8h, 041h, 01Ch, 0D9h, 05Eh, 064h, 0D9h, 084h
    db 004h, 0C4h, 000h, 000h, 000h, 0D8h, 041h, 020h, 0D9h, 05Eh, 068h, 0D9h, 047h, 00Ch, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0C0h, 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 0D9h, 084h, 004h, 0A4h, 000h, 000h, 000h, 083h, 0C1h, 030h
    db 0D8h, 041h, 0F4h, 083h, 0C7h, 010h, 081h, 0C6h, 090h, 000h, 000h, 000h, 04Bh, 0D9h, 05Eh, 0DCh
    db 0D9h, 084h, 004h, 0A8h, 000h, 000h, 000h, 0D8h, 041h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 084h, 004h
    db 0ACh, 000h, 000h, 000h, 0D8h, 041h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 084h, 004h, 0B0h, 000h, 000h
    db 000h, 0D8h, 041h, 0F4h, 0D9h, 05Eh, 0E8h, 0D9h, 084h, 004h, 0B4h, 000h, 000h, 000h, 0D8h, 041h
    db 0F8h, 0D9h, 05Eh, 0ECh, 0D9h, 084h, 004h, 0B8h, 000h, 000h, 000h, 0D8h, 041h, 0FCh, 0D9h, 05Eh
    db 0F0h, 0D9h, 084h, 004h, 0BCh, 000h, 000h, 000h, 0D8h, 041h, 0F4h, 0D9h, 05Eh, 0F4h, 0D9h, 084h
    db 004h, 0C0h, 000h, 000h, 000h, 0D8h, 041h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 084h, 004h, 0C4h, 000h
    db 000h, 000h, 0D8h, 041h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 0A2h, 0FDh, 0FFh, 0FFh, 03Bh, 0EAh
    db 00Fh, 08Dh, 0AAh, 000h, 000h, 000h, 02Bh, 0D5h, 0EBh, 003h, 08Dh, 049h, 000h, 0D9h, 007h, 0D8h
    db 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 07Ah, 004h, 033h, 0C0h, 0EBh, 005h, 0B8h, 001h, 000h, 000h, 000h
    db 08Dh, 004h, 0C0h, 0C1h, 0E0h, 002h, 0D9h, 084h, 004h, 0A4h, 000h, 000h, 000h, 083h, 0C1h, 00Ch
    db 0D8h, 041h, 0F4h, 083h, 0C7h, 004h, 083h, 0C6h, 024h, 04Ah, 0D9h, 05Eh, 0DCh, 0D9h, 084h, 004h
    db 0A8h, 000h, 000h, 000h, 0D8h, 041h, 0F8h, 0D9h, 05Eh, 0E0h, 0D9h, 084h, 004h, 0ACh, 000h, 000h
    db 000h, 0D8h, 041h, 0FCh, 0D9h, 05Eh, 0E4h, 0D9h, 084h, 004h, 0B0h, 000h, 000h, 000h, 0D8h, 041h
    db 0F4h, 0D9h, 05Eh, 0E8h, 0D9h, 084h, 004h, 0B4h, 000h, 000h, 000h, 0D8h, 041h, 0F8h, 0D9h, 05Eh
    db 0ECh, 0D9h, 084h, 004h, 0B8h, 000h, 000h, 000h, 0D8h, 041h, 0FCh, 0D9h, 05Eh, 0F0h, 0D9h, 084h
    db 004h, 0BCh, 000h, 000h, 000h, 0D8h, 041h, 0F4h, 0D9h, 05Eh, 0F4h, 0D9h, 084h, 004h, 0C0h, 000h
    db 000h, 000h, 0D8h, 041h, 0F8h, 0D9h, 05Eh, 0F8h, 0D9h, 084h, 004h, 0C4h, 000h, 000h, 000h, 0D8h
    db 041h, 0FCh, 0D9h, 05Eh, 0FCh, 00Fh, 085h, 05Dh, 0FFh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 081h
    db 0C4h, 0F0h, 000h, 000h, 000h, 0C2h, 010h, 000h
    dd ?d_009148c0@@YAXXZ + 049h
    dd ?d_009148c0@@YAXXZ + 02F0h
    dd ?d_009148c0@@YAXXZ + 075Eh
    dd ?d_009148c0@@YAXXZ + 0BD9h
    dd ?d_009148c0@@YAXXZ + 01051h
    dd ?d_009148c0@@YAXXZ + 013EBh
    dd ?d_009148c0@@YAXXZ + 0153Ch
    dd ?d_009148c0@@YAXXZ + 0168Bh
    dd ?d_009148c0@@YAXXZ + 01C32h
    dd ?d_009148c0@@YAXXZ + 01F30h
    dd ?d_009148c0@@YAXXZ + 01C32h
    dd ?d_009148c0@@YAXXZ + 01F30h
?d_009148c0@@YAXXZ ENDP
_TEXT$d00d148c0 ENDS
_TEXT SEGMENT

; retail @ 0x0091B6A0 size 58
public ?d_0091b6a0@@YAXXZ
?d_0091b6a0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0C0h, 0BAh, 83h, 0F8h, 0Dh, 77h, 13h, 0Fh, 0B6h, 80h, 0CCh
    db 0B6h, 0D1h, 00h, 0FFh, 24h, 85h, 0C4h, 0B6h, 0D1h, 00h, 0B0h, 01h, 0C2h, 04h, 00h, 32h
    db 0C0h, 0C2h, 04h, 00h, 0BAh, 0B6h, 0D1h, 00h, 0BFh, 0B6h, 0D1h, 00h, 00h, 00h, 01h, 00h
    db 01h, 00h, 01h, 00h, 01h, 00h, 00h, 01h, 00h, 00h
?d_0091b6a0@@YAXXZ ENDP
_TEXT ENDS
END
