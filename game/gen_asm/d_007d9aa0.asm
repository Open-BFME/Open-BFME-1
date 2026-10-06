.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0BoxDynamicVBAccessClass@@QAE@IIGI@Z:NEAR
EXTERN ??0DynamicIBAccessClass@@QAE@GG@Z:NEAR
EXTERN ??1BoxDynamicVBAccessClass@@QAE@XZ:NEAR
EXTERN ??1DynamicIBAccessClass@@QAE@XZ:NEAR
EXTERN ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ:NEAR
EXTERN ?BaseHeightMapScorchStageChanges@@3IA:BYTE
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?BfmeCameraGlobal12BB214@@3MA:BYTE
EXTERN ?BfmeShadowScale@@3MB:BYTE
EXTERN ?BfmeSubdualCapERD@@3MB:BYTE
EXTERN ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z:NEAR
EXTERN ?D3DCallCount@DX8Wrapper@@0IA:BYTE
EXTERN ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A:BYTE
EXTERN ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z:NEAR
EXTERN ?FadeTacticalView@@3PAVFadeView@@A:BYTE
EXTERN ?Free_String@StringClass@@AAEXXZ:NEAR
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z:NEAR
EXTERN ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z:NEAR
EXTERN ?Get_String@StringClass@@AAEXH_N@Z:NEAR
EXTERN ?HighlightRendering@@3_NA:BYTE
EXTERN ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ:NEAR
EXTERN ?R3FieldSlope1096CF4@@3MA:BYTE
EXTERN ?Rva00064680NegativeScale@@3MB:BYTE
EXTERN ?Rva007EB810Get@@YAPAURva007EB810Diag@@XZ:NEAR
EXTERN ?Rva0133F451Snapshot@@3_NA:BYTE
EXTERN ?ScreenRenderStateChanges@@3IA:BYTE
EXTERN ?Set_Index_Buffer@DX8Wrapper@@SAXABVDynamicIBAccessClass@@G@Z:NEAR
EXTERN ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z:NEAR
EXTERN ?Set_Vertex_Buffer@DX8Wrapper@@SAXABVDynamicVBAccessClass@@@Z:NEAR
EXTERN ?bfmeGoVFD@@YGXPAUBfmeThingVFD@@@Z:NEAR
EXTERN ?g_Va013073B4@@3IA:BYTE
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?g_bfmeCh1035@@3DA:BYTE
EXTERN ?g_bfmeK1266A@@3MB:BYTE
EXTERN ?j_00007ac2@@YAXXZ:NEAR
EXTERN ?j_0000ae5c@@YAXXZ:NEAR
EXTERN ?j_0000d7a6@@YAXXZ:NEAR
EXTERN ?j_0000e3d1@@YAXXZ:NEAR
EXTERN ?j_0001321e@@YAXXZ:NEAR
EXTERN ?j_00023f97@@YAXXZ:NEAR
EXTERN ?j_0003f242@@YAXXZ:NEAR
EXTERN ?m_EmptyString@StringClass@@0PADA:BYTE
EXTERN __ftol2:NEAR
EXTERN __imp__floor:BYTE
EXTERN __real@3c4ccccd:BYTE
EXTERN __real@3ca3d70a:BYTE
EXTERN __real@40c00000:BYTE
EXTERN __real@41500000:BYTE
EXTERN g_Va01053DBF:NEAR
EXTERN g_Va01128AAC:BYTE
EXTERN g_Va01128AB0:BYTE
EXTERN g_Va01128ABC:BYTE
EXTERN g_Va0112B7E0:BYTE
EXTERN g_Va012BC294:BYTE
EXTERN g_Va012BC2C3:BYTE
EXTERN g_Va013073B1:BYTE
EXTERN g_Va013073B8:BYTE
EXTERN g_Va0133F9E4:BYTE
EXTERN g_Va0133F9E8:BYTE
EXTERN g_Va0133F9EC:BYTE
EXTERN g_Va0133F9F0:BYTE
EXTERN g_Va0133F9F4:BYTE
EXTERN g_Va0133F9F8:BYTE
EXTERN g_Va0133FA0C:BYTE
EXTERN g_Va0134014C:BYTE
EXTERN g_Va01340150:BYTE
EXTERN g_Va0134016C:BYTE
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x007D9AA0 size 4005
_TEXT ENDS
_TEXT$d00bd9aa0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BD9AA0 size 4005
public ?d_007d9aa0@@YAXXZ
?d_007d9aa0@@YAXXZ PROC
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 06Ah, 0FFh, 068h
    dd g_Va01053DBF
    db 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh, 038h, 001h, 000h, 000h, 053h, 057h
    db 0BBh, 001h, 000h, 000h, 000h, 053h, 06Ah, 000h, 08Bh, 0F9h
    call ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z
    db 08Bh, 08Ch, 024h, 058h, 001h, 000h, 000h, 08Bh, 007h, 083h, 0C4h, 008h, 051h, 08Bh, 0CFh, 0FFh
    db 050h, 014h, 085h, 0C0h, 075h, 007h, 032h, 0C0h, 0E9h, 043h, 00Fh, 000h, 000h, 08Bh, 094h, 024h
    db 058h, 001h, 000h, 000h, 0F6h, 005h
    dd ?g_Va013073B4@@3IA
    db 001h, 056h, 0C6h, 002h, 000h, 08Bh, 035h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 075h, 02Bh, 009h, 01Dh
    dd ?g_Va013073B4@@3IA
    db 0C7h, 084h, 024h, 04Ch, 001h, 000h, 000h, 000h, 000h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 039h, 058h, 058h, 00Fh, 09Fh, 005h
    dd g_Va013073B1
    db 0C7h, 084h, 024h, 04Ch, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 0A0h
    dd g_Va013073B1
    db 084h, 0C0h, 074h, 026h, 08Bh, 047h, 050h, 08Bh, 04Fh, 044h, 08Bh, 057h, 04Ch, 050h, 08Bh, 047h
    db 018h, 051h, 052h, 050h, 068h, 000h, 001h, 000h, 000h, 08Dh, 04Fh, 02Ch, 051h, 068h, 0CDh, 0CCh
    db 04Ch, 03Fh
    call ?j_0003f242@@YAXXZ
    db 083h, 0C4h, 01Ch
    call ?j_0000d7a6@@YAXXZ
    db 039h, 058h, 05Ch, 07Eh, 026h, 08Bh, 057h, 01Ch, 08Bh, 047h, 044h, 08Bh, 04Fh, 04Ch, 052h, 08Bh
    db 057h, 018h, 050h, 051h, 052h, 068h, 000h, 001h, 000h, 000h, 08Dh, 047h, 038h, 050h, 068h, 000h
    db 000h, 080h, 03Fh
    call ?j_0003f242@@YAXXZ
    db 083h, 0C4h, 01Ch, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 011h, 055h, 08Dh, 044h, 024h, 044h, 050h, 08Dh, 044h, 024h, 04Ch, 050h, 0FFh, 052h, 04Ch
    db 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 011h, 0FFh, 052h, 03Ch, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 0E8h, 08Bh, 001h, 089h, 06Ch, 024h, 050h, 0FFh, 050h, 044h, 0D9h, 047h, 024h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 0D8h, 089h, 05Ch, 024h, 030h, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ch, 0D9h, 047h, 024h
    db 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 024h, 0D9h, 047h, 020h, 0D8h, 01Dh
    dd ?BfmeShadowScale@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ch, 0D9h, 047h, 020h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 020h, 0D9h, 047h, 028h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ch, 0D9h, 047h, 028h, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 028h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 04Ch, 0D8h, 00Dh
    dd ?Rva00064680NegativeScale@@3MB
    db 08Bh, 04Fh, 020h, 089h, 04Ch, 024h, 038h, 0D8h, 047h, 024h, 0D9h, 05Fh, 024h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 04Ch, 0D8h, 00Dh
    dd g_Va01128ABC
    db 0D8h, 06Ch, 024h, 038h, 0D9h, 05Fh, 020h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 050h, 0DCh, 00Dh
    dd g_Va01128AB0
    db 0D8h, 047h, 028h, 0D9h, 05Fh, 028h, 0D9h, 005h
    dd ?BfmeCameraGlobal12BB214@@3MA
    db 0D8h, 00Dh
    dd __real@3c4ccccd
    db 0D9h, 054h, 024h, 010h, 0D8h, 01Dh
    dd __real@40c00000
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ah, 0C7h, 044h, 024h, 010h, 000h, 000h, 0C0h, 040h, 0EBh
    db 019h, 0D9h, 044h, 024h, 010h, 0D8h, 01Dh
    dd ?R3FieldSlope1096CF4@@3MA
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 010h, 09Ah, 099h, 019h, 03Fh
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 044h, 024h, 010h, 0D8h, 048h, 054h, 08Bh, 054h, 024h, 044h, 08Bh, 044h, 024h, 048h, 003h
    db 0DAh, 0D9h, 05Ch, 024h, 038h, 089h, 05Ch, 024h, 02Ch, 0DBh, 044h, 024h, 02Ch, 003h, 0E8h, 089h
    db 06Ch, 024h, 02Ch, 08Bh, 0ACh, 024h, 064h, 001h, 000h, 000h, 0D9h, 054h, 024h, 024h, 0C7h, 044h
    db 024h, 01Ch, 000h, 000h, 000h, 000h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 08Bh, 044h, 024h, 01Ch, 0C7h, 044h, 024h, 020h, 000h, 000h, 080h, 03Fh, 089h, 084h, 024h, 088h
    db 000h, 000h, 000h, 0D9h, 0C0h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 0DBh, 044h, 024h
    db 02Ch, 0D9h, 054h, 024h, 034h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 0D9h, 054h, 024h, 014h, 08Bh, 04Ch, 024h, 014h, 0D9h, 0C9h, 089h, 08Ch, 024h, 080h, 000h, 000h
    db 000h, 0D9h, 05Ch, 024h, 018h, 08Bh, 054h, 024h, 018h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 08Bh, 04Ch, 024h, 020h, 0D8h, 075h, 000h, 089h, 094h, 024h, 084h, 000h, 000h, 000h, 089h, 08Ch
    db 024h, 08Ch, 000h, 000h, 000h, 0C7h, 044h, 024h, 020h, 000h, 000h, 080h, 03Fh, 0D9h, 054h, 024h
    db 02Ch, 0D8h, 04Ch, 024h, 034h, 0D9h, 054h, 024h, 03Ch, 0D9h, 09Ch, 024h, 094h, 000h, 000h, 000h
    db 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 075h, 004h, 0D9h, 054h, 024h, 034h, 0D8h, 04Ch, 024h, 024h, 0D9h, 054h, 024h, 040h, 0D9h
    db 09Ch, 024h, 098h, 000h, 000h, 000h, 0DBh, 044h, 024h, 044h, 0D9h, 054h, 024h, 024h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 0D9h, 054h, 024h, 028h, 0D9h, 05Ch, 024h, 04Ch, 08Bh, 054h, 024h, 04Ch, 0D9h, 05Ch, 024h, 014h
    db 08Bh, 044h, 024h, 014h, 0D9h, 044h, 024h, 024h, 08Bh, 0CAh, 0D8h, 04Ch, 024h, 034h, 089h, 054h
    db 024h, 018h, 08Bh, 054h, 024h, 01Ch, 089h, 084h, 024h, 0ACh, 000h, 000h, 000h, 08Bh, 044h, 024h
    db 020h, 0D9h, 094h, 024h, 0C4h, 000h, 000h, 000h, 0DBh, 044h, 024h, 048h, 089h, 08Ch, 024h, 0B0h
    db 000h, 000h, 000h, 08Bh, 04Ch, 024h, 03Ch, 089h, 094h, 024h, 0B4h, 000h, 000h, 000h, 0D9h, 054h
    db 024h, 024h, 089h, 084h, 024h, 0B8h, 000h, 000h, 000h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 089h, 08Ch, 024h, 0C0h, 000h, 000h, 000h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 08Bh
    db 04Ch, 024h, 01Ch, 0D9h, 054h, 024h, 014h, 08Bh, 054h, 024h, 014h, 0D9h, 0CAh, 0C7h, 044h, 024h
    db 020h, 000h, 000h, 080h, 03Fh, 0D9h, 05Ch, 024h, 018h, 08Bh, 044h, 024h, 018h, 089h, 094h, 024h
    db 0D8h, 000h, 000h, 000h, 08Bh, 054h, 024h, 020h, 089h, 084h, 024h, 0DCh, 000h, 000h, 000h, 089h
    db 08Ch, 024h, 0E0h, 000h, 000h, 000h, 0D9h, 044h, 024h, 024h, 08Bh, 044h, 024h, 040h, 0D8h, 04Ch
    db 024h, 02Ch, 08Bh, 04Ch, 024h, 028h, 089h, 04Ch, 024h, 028h, 089h, 094h, 024h, 0E4h, 000h, 000h
    db 000h, 0D9h, 054h, 024h, 03Ch, 08Bh, 0D1h, 0D9h, 09Ch, 024h, 0ECh, 000h, 000h, 000h, 089h, 054h
    db 024h, 018h, 0D9h, 0C9h, 0C7h, 044h, 024h, 01Ch, 000h, 000h, 000h, 000h, 0D9h, 05Ch, 024h, 014h
    db 08Bh, 054h, 024h, 01Ch, 089h, 084h, 024h, 0F0h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 01Ch, 001h
    db 000h, 000h, 08Bh, 044h, 024h, 014h, 0D9h, 044h, 024h, 038h, 089h, 094h, 024h, 00Ch, 001h, 000h
    db 000h, 0DCh, 0C0h, 089h, 084h, 024h, 004h, 001h, 000h, 000h, 0C7h, 044h, 024h, 020h, 000h, 000h
    db 080h, 03Fh, 08Bh, 044h, 024h, 020h, 0D8h, 047h, 020h, 089h, 08Ch, 024h, 008h, 001h, 000h, 000h
    db 08Bh, 04Ch, 024h, 03Ch, 089h, 084h, 024h, 010h, 001h, 000h, 000h, 0D9h, 094h, 024h, 09Ch, 000h
    db 000h, 000h, 0B8h, 0FFh, 0FFh, 0FFh, 064h, 0D9h, 044h, 024h, 038h, 089h, 08Ch, 024h, 018h, 001h
    db 000h, 000h, 0D8h, 047h, 024h, 089h, 084h, 024h, 090h, 000h, 000h, 000h, 089h, 084h, 024h, 0BCh
    db 000h, 000h, 000h, 089h, 084h, 024h, 0E8h, 000h, 000h, 000h, 0D9h, 094h, 024h, 0A0h, 000h, 000h
    db 000h, 089h, 084h, 024h, 014h, 001h, 000h, 000h, 0D9h, 084h, 024h, 09Ch, 000h, 000h, 000h, 0D8h
    db 047h, 028h, 0D9h, 084h, 024h, 0A0h, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 0A8h
    db 000h, 000h, 000h, 0D9h, 0C0h, 0D8h, 067h, 028h, 0D9h, 09Ch, 024h, 0A4h, 000h, 000h, 000h, 0D8h
    db 047h, 028h, 0D9h, 09Ch, 024h, 09Ch, 000h, 000h, 000h, 0D9h, 047h, 024h, 0D9h, 054h, 024h, 040h
    db 0D9h, 09Ch, 024h, 0CCh, 000h, 000h, 000h, 08Bh, 054h, 024h, 040h, 0D9h, 0C9h, 089h, 094h, 024h
    db 024h, 001h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 084h, 024h, 0CCh, 000h, 000h, 000h, 0D8h, 047h
    db 028h, 0D9h, 09Ch, 024h, 0D4h, 000h, 000h, 000h, 0D9h, 0C0h, 0D8h, 067h, 028h, 0D9h, 09Ch, 024h
    db 0D0h, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 0C8h, 000h, 000h, 000h, 0D9h, 047h
    db 020h, 0D9h, 054h, 024h, 028h, 0D9h, 09Ch, 024h, 0F4h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0F8h
    db 000h, 000h, 000h, 0D9h, 084h, 024h, 0F4h, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 084h, 024h
    db 0F8h, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 000h, 001h, 000h, 000h, 0D9h, 0C0h
    db 0D8h, 067h, 028h, 0D9h, 09Ch, 024h, 0FCh, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h
    db 0F4h, 000h, 000h, 000h, 0D9h, 044h, 024h, 028h, 0D8h, 047h, 028h, 0D9h, 084h, 024h, 024h, 001h
    db 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 02Ch, 001h, 000h, 000h, 0D9h, 0C0h, 068h, 044h
    db 003h, 000h, 000h, 0D8h, 067h, 028h, 056h, 0D9h, 09Ch, 024h, 030h, 001h, 000h, 000h, 0D8h, 047h
    db 028h, 0D9h, 09Ch, 024h, 028h, 001h, 000h, 000h, 08Bh, 006h, 0FFh, 090h, 064h, 001h, 000h, 000h
    db 08Bh, 00Eh, 06Ah, 001h, 08Dh, 054h, 024h, 018h, 052h, 033h, 0DBh, 053h, 056h, 0C7h, 044h, 024h
    db 024h, 09Ah, 099h, 099h, 03Eh, 0C7h, 044h, 024h, 028h, 03Dh, 00Ah, 017h, 03Fh, 0C7h, 044h, 024h
    db 02Ch, 0AEh, 047h, 0E1h, 03Dh, 0C7h, 044h, 024h, 030h, 000h, 000h, 080h, 03Fh, 0FFh, 091h, 0B4h
    db 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 083h, 0C0h, 014h, 08Bh, 008h, 08Bh, 050h, 004h, 08Bh, 040h, 008h, 089h, 054h, 024h, 064h, 06Ah
    db 001h, 089h, 054h, 024h, 01Ch, 08Dh, 054h, 024h, 064h, 052h, 06Ah, 001h, 089h, 04Ch, 024h, 020h
    db 089h, 04Ch, 024h, 06Ch, 089h, 044h, 024h, 074h, 0C7h, 044h, 024h, 078h, 000h, 000h, 080h, 03Fh
    db 08Bh, 00Eh, 056h, 089h, 044h, 024h, 02Ch, 0FFh, 091h, 0B4h, 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 083h, 0C0h, 008h, 08Bh, 008h, 08Bh, 050h, 004h, 08Bh, 040h, 008h, 089h, 054h, 024h, 074h, 06Ah
    db 001h, 089h, 054h, 024h, 01Ch, 08Dh, 054h, 024h, 074h, 052h, 06Ah, 002h, 089h, 04Ch, 024h, 020h
    db 089h, 04Ch, 024h, 07Ch, 089h, 084h, 024h, 084h, 000h, 000h, 000h, 0C7h, 084h, 024h, 088h, 000h
    db 000h, 000h, 000h, 000h, 080h, 03Fh, 08Bh, 00Eh, 056h, 089h, 044h, 024h, 02Ch, 0FFh, 091h, 0B4h
    db 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 020h, 08Bh, 006h, 0D9h, 054h, 024h, 014h, 06Ah, 001h, 0D9h, 054h, 024h, 01Ch, 08Dh
    db 04Ch, 024h, 018h, 0D9h, 054h, 024h, 020h, 051h, 0D9h, 05Ch, 024h, 028h, 06Ah, 003h, 056h, 0FFh
    db 090h, 0B4h, 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 044h, 024h, 010h, 0D8h, 00Dh
    dd g_Va01128AAC
    db 0C7h, 044h, 024h, 020h, 000h, 000h, 080h, 03Fh, 0D8h, 038h, 0D9h, 054h, 024h, 014h, 0D9h, 054h
    db 024h, 018h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 016h, 06Ah, 001h, 08Dh, 044h, 024h, 018h, 050h, 06Ah
    db 004h, 056h, 0FFh, 092h, 0B4h, 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 004h, 08Bh, 00Eh, 0D9h, 054h, 024h, 014h, 06Ah, 001h, 0D9h, 054h, 024h, 01Ch, 08Dh
    db 054h, 024h, 018h, 0D9h, 054h, 024h, 020h, 052h, 0D9h, 054h, 024h, 030h, 06Ah, 005h, 0D9h, 05Ch
    db 024h, 02Ch, 056h, 0FFh, 091h, 0B4h, 001h, 000h, 000h
    call ?j_0000d7a6@@YAXXZ
    db 0D9h, 040h, 024h, 08Bh, 006h, 0D9h, 054h, 024h, 014h, 06Ah, 001h, 0D9h, 054h, 024h, 01Ch, 08Dh
    db 04Ch, 024h, 018h, 0D9h, 054h, 024h, 020h, 051h, 0D9h, 05Ch, 024h, 028h, 06Ah, 006h, 056h, 0FFh
    db 090h, 0B4h, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 001h, 08Dh, 044h, 024h, 018h, 050h, 06Ah, 007h
    db 056h, 0C7h, 044h, 024h, 024h, 0CDh, 0CCh, 00Ch, 03Fh, 0C7h, 044h, 024h, 028h, 066h, 066h, 0E6h
    db 03Eh, 0C7h, 044h, 024h, 02Ch, 000h, 000h, 000h, 03Fh, 0C7h, 044h, 024h, 030h, 000h, 000h, 000h
    db 03Fh, 0FFh, 092h, 0B4h, 001h, 000h, 000h, 039h, 01Dh
    dd g_Va0134016C
    db 00Fh, 084h, 089h, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 00Dh
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 089h, 04Ch, 024h, 014h, 053h, 08Dh, 04Ch, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 08Ah, 015h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 044h, 024h, 010h, 088h, 010h, 053h, 08Dh, 04Ch, 024h, 014h, 06Ah, 01Bh, 051h, 0C7h, 084h
    db 024h, 05Ch, 001h, 000h, 000h, 001h, 000h, 000h, 000h
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 053h, 06Ah, 01Bh, 089h, 01Dh
    dd g_Va0134016C
    db 08Bh, 010h, 050h, 0FFh, 092h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?ScreenRenderStateChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?ScreenRenderStateChanges@@3IA
    call ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ
    db 08Bh, 04Fh, 018h, 08Bh, 006h, 051h, 053h, 056h, 0FFh, 090h, 004h, 001h, 000h, 000h, 08Bh, 016h
    db 053h, 06Ah, 001h, 056h, 0FFh, 092h, 004h, 001h, 000h, 000h, 083h, 03Dh
    dd g_Va0133F9E8
    db 002h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 0A1h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 044h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 08Ah, 00Dh
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 054h, 024h, 010h, 088h, 00Ah, 06Ah, 002h, 08Dh, 044h, 024h, 014h, 06Ah, 002h, 050h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 002h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 002h, 06Ah, 002h, 053h, 0C7h, 005h
    dd g_Va0133F9E8
    db 002h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 083h, 03Dh
    dd g_Va0133F9EC
    db 001h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 001h, 08Dh, 054h, 024h, 014h, 06Ah, 003h, 052h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 003h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 001h, 06Ah, 003h, 053h, 0C7h, 005h
    dd g_Va0133F9EC
    db 001h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 083h, 03Dh
    dd g_Va0133F9E4
    db 002h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 002h, 08Dh, 054h, 024h, 014h, 06Ah, 001h, 052h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 004h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 002h, 06Ah, 001h, 053h, 0C7h, 005h
    dd g_Va0133F9E4
    db 002h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 083h, 03Dh
    dd g_Va0133F9F4
    db 002h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 002h, 08Dh, 054h, 024h, 014h, 06Ah, 005h, 052h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 005h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 002h, 06Ah, 005h, 053h, 0C7h, 005h
    dd g_Va0133F9F4
    db 002h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 083h, 03Dh
    dd g_Va0133F9F8
    db 001h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 001h, 08Dh, 054h, 024h, 014h, 06Ah, 006h, 052h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 006h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 001h, 06Ah, 006h, 053h, 0C7h, 005h
    dd g_Va0133F9F8
    db 001h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 083h, 03Dh
    dd g_Va0133F9F0
    db 002h, 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 051h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 002h, 08Dh, 054h, 024h, 014h, 06Ah, 004h, 052h, 0C7h
    db 084h, 024h, 05Ch, 001h, 000h, 000h, 007h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 06Ah, 002h, 06Ah, 004h, 053h, 0C7h, 005h
    dd g_Va0133F9F0
    db 002h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 039h, 01Dh
    dd g_Va0133FA0C
    db 00Fh, 084h, 089h, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 050h, 08Bh, 015h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 053h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 053h, 08Dh, 054h, 024h, 014h, 06Ah, 00Bh, 052h, 0C7h, 084h
    db 024h, 05Ch, 001h, 000h, 000h, 008h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 050h, 001h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 053h, 06Ah, 00Bh, 053h, 089h, 01Dh
    dd g_Va0133FA0C
    db 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?BaseHeightMapScorchStageChanges@@3IA
    db 08Bh, 047h, 00Ch, 08Bh, 016h, 050h, 056h, 0FFh, 092h, 0ACh, 001h, 000h, 000h, 08Bh, 00Eh, 053h
    db 056h, 0FFh, 091h, 070h, 001h, 000h, 000h, 08Bh, 016h, 068h, 044h, 003h, 000h, 000h, 056h, 0FFh
    db 092h, 064h, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 02Ch, 08Dh, 08Ch, 024h, 084h, 000h, 000h, 000h
    db 051h, 06Ah, 002h, 06Ah, 005h, 056h, 0FFh, 090h, 04Ch, 001h, 000h, 000h, 068h, 05Eh, 002h, 000h
    db 000h, 06Ah, 002h, 08Dh, 04Ch, 024h, 05Ch
    call ??0DynamicIBAccessClass@@QAE@GG@Z
    db 053h, 068h, 0CAh, 000h, 000h, 000h, 06Ah, 00Eh, 06Ah, 002h, 08Dh, 08Ch, 024h, 040h, 001h, 000h
    db 000h, 0C7h, 084h, 024h, 060h, 001h, 000h, 000h, 009h, 000h, 000h, 000h
    call ??0BoxDynamicVBAccessClass@@QAE@IIGI@Z
    db 0DBh, 044h, 024h, 030h, 055h, 083h, 0ECh, 010h, 0D9h, 05Ch, 024h, 00Ch, 0BBh, 00Ah, 000h, 000h
    db 000h, 0DBh, 044h, 024h, 064h, 08Dh, 094h, 024h, 044h, 001h, 000h, 000h, 08Dh, 044h, 024h, 068h
    db 08Bh, 0CFh, 0D9h, 05Ch, 024h, 008h, 088h, 09Ch, 024h, 064h, 001h, 000h, 000h, 0DBh, 044h, 024h
    db 058h, 0D9h, 05Ch, 024h, 004h, 0DBh, 044h, 024h, 05Ch, 0D9h, 01Ch, 024h, 053h, 053h, 068h, 0CAh
    db 000h, 000h, 000h, 052h, 068h, 05Eh, 002h, 000h, 000h, 050h
    call ?j_00023f97@@YAXXZ
    db 08Dh, 04Ch, 024h, 054h, 06Ah, 000h, 051h
    call ?Set_Index_Buffer@DX8Wrapper@@SAXABVDynamicIBAccessClass@@G@Z
    db 08Dh, 094h, 024h, 038h, 001h, 000h, 000h, 052h
    call ?Set_Vertex_Buffer@DX8Wrapper@@SAXABVDynamicVBAccessClass@@@Z
    db 083h, 0C4h, 00Ch
    call ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ
    db 0A0h
    dd g_Va013073B1
    db 084h, 0C0h, 074h, 020h, 08Bh, 04Fh, 048h, 08Bh, 006h, 051h, 06Ah, 003h, 056h, 0FFh, 090h, 004h
    db 001h, 000h, 000h, 08Bh, 047h, 048h, 08Bh, 016h, 050h, 06Ah, 004h, 056h, 0FFh, 092h, 004h, 001h
    db 000h, 000h, 0EBh, 01Eh, 08Bh, 057h, 018h, 08Bh, 00Eh, 052h, 06Ah, 003h, 056h, 0FFh, 091h, 004h
    db 001h, 000h, 000h, 08Bh, 04Fh, 018h, 08Bh, 006h, 051h, 06Ah, 004h, 056h, 0FFh, 090h, 004h, 001h
    db 000h, 000h, 08Bh, 02Eh, 08Dh, 04Fh, 010h
    call ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ
    db 050h, 06Ah, 001h, 056h, 0FFh, 095h, 004h, 001h, 000h, 000h, 08Bh, 02Eh, 08Dh, 04Fh, 014h
    call ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ
    db 050h, 06Ah, 002h, 056h, 0FFh, 095h, 004h, 001h, 000h, 000h, 08Bh, 016h, 0BDh, 003h, 000h, 000h
    db 000h, 055h, 06Ah, 001h, 06Ah, 000h, 056h, 0FFh, 092h, 014h, 001h, 000h, 000h, 08Bh, 006h, 055h
    db 06Ah, 002h, 06Ah, 000h, 056h, 0FFh, 090h, 014h, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 001h, 06Ah
    db 001h, 06Ah, 001h, 056h, 0FFh, 091h, 014h, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 001h, 06Ah, 002h
    db 06Ah, 001h, 056h, 0FFh, 092h, 014h, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 001h, 06Ah, 001h, 06Ah
    db 002h, 056h, 0FFh, 090h, 014h, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 001h, 06Ah, 002h, 06Ah, 002h
    db 056h, 0FFh, 091h, 014h, 001h, 000h, 000h, 08Bh, 016h, 055h, 06Ah, 001h, 055h, 056h, 0FFh, 092h
    db 014h, 001h, 000h, 000h, 08Bh, 006h, 055h, 06Ah, 002h, 055h, 056h, 0FFh, 090h, 014h, 001h, 000h
    db 000h, 08Bh, 00Eh, 055h, 06Ah, 001h, 06Ah, 004h, 056h, 0FFh, 091h, 014h, 001h, 000h, 000h, 08Bh
    db 016h, 055h, 06Ah, 002h, 06Ah, 004h, 056h, 0FFh, 092h, 014h, 001h, 000h, 000h, 08Bh, 006h, 06Ah
    db 001h, 06Ah, 01Bh, 056h, 0FFh, 090h, 0E4h, 000h, 000h, 000h, 039h, 02Dh
    dd g_Va0134014C
    db 00Fh, 084h, 083h, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 04Bh, 08Bh, 00Dh
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 089h, 04Ch, 024h, 014h, 06Ah, 000h, 08Dh, 04Ch, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 08Ah, 015h
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 044h, 024h, 010h, 088h, 010h, 055h, 08Dh, 04Ch, 024h, 014h, 06Ah, 013h, 051h, 0C6h, 084h
    db 024h, 05Ch, 001h, 000h, 000h, 00Bh
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 088h, 09Ch, 024h, 050h, 001h, 000h, 000h
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 055h, 06Ah, 013h, 089h, 02Dh
    dd g_Va0134014C
    db 08Bh, 010h, 050h, 0FFh, 092h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?ScreenRenderStateChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?ScreenRenderStateChanges@@3IA
    db 0A1h
    dd g_Va01340150
    db 0BDh, 004h, 000h, 000h, 000h, 03Bh, 0C5h, 00Fh, 084h, 082h, 000h, 000h, 000h, 0A0h
    dd ?Rva0133F451Snapshot@@3_NA
    db 084h, 0C0h, 074h, 04Ah, 0A1h
    dd ?m_EmptyString@StringClass@@0PADA
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 04Ch, 024h, 038h, 089h, 044h, 024h, 038h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 08Ah, 00Dh
    dd ?g_bfmeCh1035@@3DA
    db 08Bh, 054h, 024h, 030h, 088h, 00Ah, 055h, 08Dh, 044h, 024h, 034h, 06Ah, 014h, 050h, 0C6h, 084h
    db 024h, 05Ch, 001h, 000h, 000h, 00Ch
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 030h, 088h, 09Ch, 024h, 050h, 001h, 000h, 000h
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 055h, 06Ah, 014h, 089h, 02Dh
    dd g_Va01340150
    db 08Bh, 008h, 050h, 0FFh, 091h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A1h
    dd ?ScreenRenderStateChanges@@3IA
    db 041h, 040h, 089h, 00Dh
    dd ?D3DCallCount@DX8Wrapper@@0IA
    db 0A3h
    dd ?ScreenRenderStateChanges@@3IA
    db 08Bh, 047h, 008h, 08Bh, 016h, 050h, 056h, 0FFh, 092h, 0ACh, 001h, 000h, 000h, 06Ah, 001h, 06Ah
    db 000h
    call ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z
    db 0D9h, 044h, 024h, 030h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 083h, 0C4h, 008h, 05Dh, 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 046h, 08Bh, 00Eh, 068h, 044h, 004h
    db 000h, 000h, 056h, 0FFh, 091h, 064h, 001h, 000h, 000h, 0A0h
    dd g_Va012BC294
    db 084h, 0C0h, 074h, 018h, 068h, 0CAh, 000h, 000h, 000h, 06Ah, 000h, 068h, 0C8h, 000h, 000h, 000h
    db 06Ah, 000h
    call ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z
    db 083h, 0C4h, 010h, 0EBh, 017h, 08Bh, 016h, 06Ah, 02Ch, 08Dh, 084h, 024h, 080h, 000h, 000h, 000h
    db 050h, 06Ah, 002h, 06Ah, 005h, 056h, 0FFh, 092h, 04Ch, 001h, 000h, 000h, 08Bh, 017h, 08Bh, 0CFh
    db 0FFh, 052h, 018h, 08Dh, 08Ch, 024h, 02Ch, 001h, 000h, 000h, 0C6h, 084h, 024h, 04Ch, 001h, 000h
    db 000h, 009h
    call ??1BoxDynamicVBAccessClass@@QAE@XZ
    db 08Dh, 04Ch, 024h, 050h, 0C7h, 084h, 024h, 04Ch, 001h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ??1DynamicIBAccessClass@@QAE@XZ
    db 0B0h, 001h, 05Eh, 08Bh, 08Ch, 024h, 040h, 001h, 000h, 000h, 05Fh, 05Bh, 064h, 089h, 00Dh, 000h
    db 000h, 000h, 000h, 081h, 0C4h, 044h, 001h, 000h, 000h, 0C2h, 010h, 000h
?d_007d9aa0@@YAXXZ ENDP
_TEXT$d00bd9aa0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x007DB1F0 size 1035
public ?d_007db1f0@@YAXXZ
?d_007db1f0@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 30h, 3Eh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 55h, 33h, 0EDh, 57h, 8Bh, 0F9h, 89h, 6Fh
    db 04h, 39h, 2Dh, 04h, 9Dh, 2Fh, 01h, 89h, 2Dh, 3Ch, 73h, 30h, 01h, 0Fh, 84h, 0C5h
    db 03h, 00h, 00h, 39h, 2Dh, 0Ch, 9Dh, 2Fh, 01h, 0Fh, 84h, 0B9h, 03h, 00h, 00h, 0E8h
    db 73h, 0B0h, 83h, 0FFh, 3Bh, 0C5h, 0Fh, 84h, 0ACh, 03h, 00h, 00h, 83h, 0F8h, 08h, 0Fh
    db 8Ch, 0A3h, 03h, 00h, 00h, 56h, 55h, 55h, 8Dh, 44h, 24h, 14h, 68h, 14h, 8Bh, 12h
    db 01h, 50h, 0E8h, 0B9h, 36h, 13h, 00h, 83h, 0C4h, 10h, 8Bh, 0F0h, 8Bh, 06h, 3Bh, 0C5h
    db 89h, 6Ch, 24h, 34h, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 4Fh, 10h, 3Bh, 0CDh, 74h
    db 05h, 0E8h, 2Ah, 05h, 21h, 00h, 8Bh, 0Eh, 89h, 4Fh, 10h, 8Bh, 4Ch, 24h, 0Ch, 53h
    db 83h, 0CBh, 0FFh, 3Bh, 0CDh, 89h, 5Ch, 24h, 38h, 74h, 05h, 0E8h, 10h, 05h, 21h, 00h
    db 55h, 55h, 8Dh, 54h, 24h, 1Ch, 68h, 04h, 8Bh, 12h, 01h, 52h, 0E8h, 6Fh, 36h, 13h
    db 00h, 83h, 0C4h, 10h, 8Bh, 0F0h, 8Bh, 06h, 85h, 0C0h, 0BDh, 01h, 00h, 00h, 00h, 89h
    db 6Ch, 24h, 38h, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 4Fh, 14h, 85h, 0C9h, 74h, 05h
    db 0E8h, 0DBh, 04h, 21h, 00h, 8Bh, 4Ch, 24h, 14h, 85h, 0C9h, 8Bh, 06h, 89h, 47h, 14h
    db 89h, 5Ch, 24h, 38h, 74h, 05h, 0E8h, 0C5h, 04h, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 8Bh, 08h, 6Ah, 00h, 8Dh, 77h, 18h, 56h, 6Ah, 00h, 6Ah, 15h, 55h, 55h, 68h, 00h
    db 02h, 00h, 00h, 68h, 00h, 02h, 00h, 00h, 50h, 32h, 0DBh, 0FFh, 51h, 5Ch, 85h, 0C0h
    db 7Ch, 14h, 8Bh, 36h, 8Bh, 16h, 8Dh, 47h, 1Ch, 50h, 6Ah, 00h, 56h, 0FFh, 52h, 48h
    db 85h, 0C0h, 7Dh, 02h, 0B3h, 01h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 00h, 8Dh
    db 77h, 44h, 56h, 6Ah, 00h, 6Ah, 15h, 55h, 55h, 68h, 00h, 02h, 00h, 00h, 68h, 00h
    db 02h, 00h, 00h, 50h, 0FFh, 51h, 5Ch, 85h, 0C0h, 7Ch, 14h, 8Bh, 36h, 8Bh, 16h, 8Dh
    db 47h, 4Ch, 50h, 6Ah, 00h, 56h, 0FFh, 52h, 48h, 85h, 0C0h, 7Dh, 02h, 0B3h, 01h, 0A1h
    db 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 00h, 8Dh, 77h, 48h, 56h, 6Ah, 00h, 6Ah, 15h
    db 55h, 55h, 68h, 00h, 02h, 00h, 00h, 68h, 00h, 02h, 00h, 00h, 50h, 0FFh, 51h, 5Ch
    db 85h, 0C0h, 7Ch, 16h, 8Bh, 36h, 8Bh, 16h, 8Dh, 47h, 50h, 50h, 6Ah, 00h, 56h, 0FFh
    db 52h, 48h, 85h, 0C0h, 0Fh, 8Ch, 42h, 02h, 00h, 00h, 84h, 0DBh, 0Fh, 85h, 3Ah, 02h
    db 00h, 00h, 8Bh, 47h, 50h, 85h, 0C0h, 0Fh, 84h, 2Fh, 02h, 00h, 00h, 8Bh, 47h, 4Ch
    db 85h, 0C0h, 0Fh, 84h, 24h, 02h, 00h, 00h, 8Bh, 47h, 1Ch, 85h, 0C0h, 0Fh, 84h, 19h
    db 02h, 00h, 00h, 8Dh, 47h, 04h, 50h, 68h, 0F0h, 8Ah, 12h, 01h, 0E8h, 0F5h, 0B8h, 83h
    db 0FFh, 8Dh, 4Fh, 08h, 51h, 68h, 0D8h, 8Ah, 12h, 01h, 0E8h, 0E7h, 0B8h, 83h, 0FFh, 8Dh
    db 57h, 0Ch, 52h, 68h, 0C0h, 8Ah, 12h, 01h, 0E8h, 0D9h, 0B8h, 83h, 0FFh, 0C7h, 05h, 0E8h
    db 9Ch, 2Fh, 01h, 48h, 73h, 30h, 01h, 89h, 6Ch, 24h, 30h, 0E8h, 0B6h, 23h, 83h, 0FFh
    db 8Bh, 40h, 58h, 8Dh, 4Ch, 24h, 30h, 51h, 8Dh, 77h, 2Ch, 56h, 89h, 44h, 24h, 3Ch
    db 0C7h, 44h, 24h, 44h, 8Fh, 0C2h, 75h, 3Dh, 0C7h, 44h, 24h, 4Ch, 0AEh, 47h, 0E1h, 3Dh
    db 0C7h, 44h, 24h, 40h, 0ECh, 51h, 38h, 3Eh, 0C7h, 44h, 24h, 48h, 00h, 00h, 90h, 40h
    db 0E8h, 3Fh, 22h, 85h, 0FFh, 0C7h, 44h, 24h, 38h, 02h, 00h, 00h, 00h, 0E8h, 74h, 23h
    db 83h, 0FFh, 8Bh, 50h, 58h, 8Dh, 44h, 24h, 38h, 50h, 83h, 0C7h, 38h, 57h, 89h, 54h
    db 24h, 44h, 0C7h, 44h, 24h, 4Ch, 8Fh, 0C2h, 75h, 3Dh, 0C7h, 44h, 24h, 54h, 0AEh, 47h
    db 0E1h, 3Dh, 0C7h, 44h, 24h, 48h, 0ECh, 51h, 38h, 3Eh, 0C7h, 44h, 24h, 50h, 00h, 00h
    db 90h, 40h, 0E8h, 0FDh, 21h, 85h, 0FFh, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Bh, 16h, 8Bh
    db 4Eh, 04h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0CAh, 0C1h
    db 0E9h, 1Fh, 83h, 0C4h, 28h, 33h, 0DBh, 03h, 0CAh, 74h, 26h, 8Bh, 16h, 8Bh, 4Eh, 04h
    db 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 8Bh, 06h, 0D1h, 0FAh, 8Bh, 0CAh, 0C1h
    db 0E9h, 1Fh, 03h, 0CAh, 83h, 0C0h, 08h, 0D8h, 00h, 43h, 83h, 0C0h, 0Ch, 3Bh, 0D9h, 72h
    db 0F6h, 0D9h, 05h, 34h, 53h, 07h, 01h, 8Bh, 16h, 8Bh, 4Eh, 04h, 0D8h, 0F1h, 2Bh, 0CAh
    db 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 33h, 0EDh, 0F7h, 0E9h, 0D9h, 5Ch, 24h, 10h, 0DDh, 0D8h, 0D1h
    db 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 74h, 35h, 33h, 0DBh, 8Dh, 64h, 24h, 00h
    db 8Bh, 0Eh, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 0Bh, 08h, 8Dh, 44h, 0Bh, 08h, 45h, 83h
    db 0C3h, 0Ch, 0D9h, 18h, 8Bh, 16h, 8Bh, 4Eh, 04h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 3Bh, 0E8h, 72h, 0D1h, 8Bh
    db 07h, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Bh, 4Fh, 04h, 2Bh, 0C8h, 0B8h, 0ABh, 0AAh, 0AAh
    db 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0CAh, 0C1h, 0E9h, 1Fh, 33h, 0F6h, 03h, 0CAh, 74h, 2Ah
    db 8Bh, 17h, 8Bh, 4Fh, 04h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 8Bh, 07h
    db 0D1h, 0FAh, 8Bh, 0CAh, 0C1h, 0E9h, 1Fh, 03h, 0CAh, 83h, 0C0h, 08h, 8Dh, 64h, 24h, 00h
    db 0D8h, 00h, 46h, 83h, 0C0h, 0Ch, 3Bh, 0F1h, 72h, 0F6h, 0D9h, 05h, 34h, 53h, 07h, 01h
    db 8Bh, 07h, 8Bh, 4Fh, 04h, 0D8h, 0F1h, 2Bh, 0C8h, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 33h, 0F6h
    db 0F7h, 0E9h, 0D9h, 5Ch, 24h, 10h, 0DDh, 0D8h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h
    db 0C2h, 74h, 31h, 33h, 0EDh, 8Bh, 0Fh, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 29h, 08h, 8Dh
    db 44h, 29h, 08h, 46h, 83h, 0C5h, 0Ch, 0D9h, 18h, 8Bh, 07h, 8Bh, 4Fh, 04h, 2Bh, 0C8h
    db 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h
    db 3Bh, 0F0h, 72h, 0D1h, 5Bh, 5Eh, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Dh, 8Bh, 4Ch, 24h
    db 20h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h, 8Bh, 17h, 8Bh, 0CFh
    db 0FFh, 52h, 04h, 5Bh, 5Eh, 5Fh, 33h, 0C0h, 5Dh, 8Bh, 4Ch, 24h, 20h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h, 8Bh, 4Ch, 24h, 28h, 5Fh, 33h, 0C0h, 5Dh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h
?d_007db1f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DB880 size 5
public ?d_007db880@@YAXXZ
?d_007db880@@YAXXZ PROC
    db 0B0h, 01h, 0C2h, 04h, 00h
?d_007db880@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DB890 size 231
public ?d_007db890@@YAXXZ
?d_007db890@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 83h, 0ECh, 24h, 0C6h, 00h, 00h, 8Bh, 44h, 24h, 2Ch, 56h, 8Bh
    db 0F1h, 83h, 38h, 00h, 74h, 09h, 32h, 0C0h, 5Eh, 83h, 0C4h, 24h, 0C2h, 08h, 00h, 0C7h
    db 00h, 06h, 00h, 00h, 00h, 8Bh, 46h, 18h, 89h, 44h, 24h, 2Ch, 0DBh, 44h, 24h, 2Ch
    db 8Dh, 0Ch, 00h, 8Dh, 54h, 24h, 10h, 52h, 0D8h, 3Dh, 38h, 8Ch, 12h, 01h, 8Dh, 46h
    db 34h, 50h, 0C7h, 44h, 24h, 18h, 02h, 00h, 00h, 00h, 89h, 4Ch, 24h, 1Ch, 0C7h, 44h
    db 24h, 20h, 0ECh, 51h, 38h, 3Eh, 0C7h, 44h, 24h, 28h, 00h, 00h, 90h, 40h, 0C7h, 46h
    db 14h, 0CDh, 0CCh, 4Ch, 3Fh, 0D9h, 05h, 34h, 8Ch, 12h, 01h, 0D8h, 0C9h, 0D9h, 5Ch, 24h
    db 24h, 0D8h, 0Dh, 30h, 8Ch, 12h, 01h, 0D9h, 5Ch, 24h, 2Ch, 0E8h, 54h, 1Dh, 85h, 0FFh
    db 8Bh, 0Dh, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 91h, 0BDh, 0Dh, 00h, 00h, 88h, 56h, 1Ch, 0A1h
    db 0C8h, 0D5h, 2Eh, 01h, 0C6h, 80h, 0BDh, 0Dh, 00h, 00h, 00h, 8Bh, 4Eh, 4Ch, 6Ah, 01h
    db 51h, 0E8h, 7Ah, 99h, 12h, 00h, 6Ah, 00h, 68h, 00h, 00h, 80h, 3Fh, 6Ah, 00h, 8Dh
    db 54h, 24h, 20h, 52h, 6Ah, 00h, 6Ah, 00h, 6Ah, 01h, 0C7h, 44h, 24h, 30h, 00h, 00h
    db 00h, 00h, 0C7h, 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 38h, 00h, 00h
    db 00h, 00h, 0E8h, 0E9h, 88h, 12h, 00h, 83h, 0C4h, 2Ch, 0C6h, 46h, 30h, 01h, 0B0h, 01h
    db 5Eh, 83h, 0C4h, 24h, 0C2h, 08h, 00h
?d_007db890@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DB9C0 size 5
public ?d_007db9c0@@YAXXZ
?d_007db9c0@@YAXXZ PROC
    db 0B0h, 01h, 0C2h, 04h, 00h
?d_007db9c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DBA00 size 654
public ?d_007dba00@@YAXXZ
?d_007dba00@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 90h, 3Eh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 56h, 8Bh, 0F1h, 0E8h, 87h, 0A8h, 83h, 0FFh
    db 83h, 0F8h, 03h, 7Ch, 12h, 0A1h, 04h, 9Dh, 2Fh, 01h, 85h, 0C0h, 74h, 09h, 0A1h, 0Ch
    db 9Dh, 2Fh, 01h, 85h, 0C0h, 75h, 12h, 33h, 0C0h, 5Eh, 8Bh, 4Ch, 24h, 20h, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h, 53h, 55h, 57h, 6Ah, 00h, 6Ah, 00h
    db 8Dh, 44h, 24h, 18h, 68h, 4Ch, 8Ch, 12h, 01h, 50h, 0E8h, 0B1h, 2Eh, 13h, 00h, 83h
    db 0C4h, 10h, 8Bh, 0F8h, 8Bh, 07h, 85h, 0C0h, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h, 00h
    db 8Dh, 6Eh, 58h, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 4Dh, 00h, 85h, 0C9h, 74h, 05h
    db 0E8h, 1Bh, 0FDh, 20h, 00h, 8Bh, 0Fh, 89h, 4Dh, 00h, 8Bh, 4Ch, 24h, 10h, 85h, 0C9h
    db 0C7h, 44h, 24h, 38h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 05h, 0E8h, 01h, 0FDh, 20h, 00h, 6Ah
    db 00h, 6Ah, 00h, 8Dh, 54h, 24h, 1Ch, 68h, 3Ch, 8Ch, 12h, 01h, 52h, 0E8h, 5Eh, 2Eh
    db 13h, 00h, 83h, 0C4h, 10h, 8Bh, 0D8h, 8Bh, 03h, 85h, 0C0h, 0C7h, 44h, 24h, 38h, 01h
    db 00h, 00h, 00h, 8Dh, 7Eh, 5Ch, 74h, 04h, 66h, 0FFh, 40h, 04h, 8Bh, 0Fh, 85h, 0C9h
    db 74h, 05h, 0E8h, 0C9h, 0FCh, 20h, 00h, 8Bh, 4Ch, 24h, 14h, 85h, 0C9h, 8Bh, 03h, 89h
    db 07h, 0C7h, 44h, 24h, 38h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 05h, 0E8h, 0B0h, 0FCh, 20h, 00h
    db 8Bh, 0CDh, 0E8h, 59h, 22h, 13h, 00h, 33h, 0DBh, 8Bh, 0CDh, 89h, 58h, 0Ch, 0E8h, 4Dh
    db 22h, 13h, 00h, 8Bh, 0CFh, 89h, 58h, 10h, 0E8h, 43h, 22h, 13h, 00h, 8Bh, 0CFh, 89h
    db 58h, 0Ch, 0E8h, 39h, 22h, 13h, 00h, 8Dh, 4Eh, 08h, 51h, 68h, 68h, 8Bh, 12h, 01h
    db 89h, 58h, 10h, 0E8h, 0A6h, 0BDh, 82h, 0FFh, 83h, 0C4h, 08h, 85h, 0C0h, 7Ch, 15h, 8Dh
    db 46h, 04h, 50h, 68h, 48h, 8Bh, 12h, 01h, 0E8h, 5Ch, 41h, 84h, 0FFh, 83h, 0C4h, 08h
    db 85h, 0C0h, 7Dh, 1Ch, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 04h, 5Fh, 5Dh, 5Bh, 33h, 0C0h
    db 5Eh, 8Bh, 4Ch, 24h, 20h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h
    db 0E8h, 6Ch, 28h, 83h, 0FFh, 8Bh, 40h, 0Ch, 53h, 8Dh, 7Eh, 40h, 57h, 53h, 6Ah, 15h
    db 6Ah, 01h, 6Ah, 01h, 50h, 89h, 46h, 2Ch, 8Bh, 0Dh, 34h, 05h, 34h, 01h, 8Bh, 11h
    db 50h, 51h, 0FFh, 52h, 5Ch, 85h, 0C0h, 7Ch, 4Ch, 8Bh, 07h, 8Bh, 08h, 8Dh, 5Eh, 4Ch
    db 53h, 6Ah, 00h, 50h, 0FFh, 51h, 48h, 85h, 0C0h, 74h, 18h, 8Bh, 07h, 85h, 0C0h, 74h
    db 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0C7h, 07h, 00h, 00h, 00h, 00h, 0C7h, 03h, 00h
    db 00h, 00h, 00h, 8Bh, 4Eh, 2Ch, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 00h, 8Dh
    db 7Eh, 44h, 57h, 6Ah, 00h, 6Ah, 15h, 6Ah, 01h, 6Ah, 01h, 51h, 51h, 50h, 0FFh, 52h
    db 5Ch, 85h, 0C0h, 7Dh, 1Ch, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 04h, 5Fh, 5Dh, 5Bh, 33h
    db 0C0h, 5Eh, 8Bh, 4Ch, 24h, 20h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch
    db 0C3h, 8Bh, 07h, 8Bh, 08h, 8Dh, 5Eh, 50h, 53h, 6Ah, 00h, 50h, 0FFh, 51h, 48h, 85h
    db 0C0h, 74h, 18h, 8Bh, 07h, 85h, 0C0h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 0C7h
    db 07h, 00h, 00h, 00h, 00h, 0C7h, 03h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 18h, 02h
    db 00h, 00h, 00h, 0E8h, 0A9h, 27h, 83h, 0FFh, 8Bh, 40h, 04h, 89h, 44h, 24h, 1Ch, 0E8h
    db 9Dh, 27h, 83h, 0FFh, 8Bh, 48h, 14h, 89h, 4Ch, 24h, 24h, 0E8h, 91h, 27h, 83h, 0FFh
    db 8Bh, 50h, 1Ch, 89h, 54h, 24h, 2Ch, 0E8h, 85h, 27h, 83h, 0FFh, 8Bh, 40h, 10h, 89h
    db 44h, 24h, 20h, 0E8h, 79h, 27h, 83h, 0FFh, 8Bh, 48h, 18h, 8Dh, 54h, 24h, 18h, 52h
    db 8Dh, 46h, 34h, 50h, 89h, 4Ch, 24h, 30h, 0E8h, 0F7h, 19h, 85h, 0FFh, 8Bh, 4Ch, 24h
    db 38h, 83h, 0C4h, 08h, 5Fh, 5Dh, 5Bh, 89h, 35h, 0E0h, 9Ch, 2Fh, 01h, 0B8h, 01h, 00h
    db 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 2Ch, 0C3h
?d_007dba00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DBD40 size 1911
_TEXT ENDS
_TEXT$d00bdbd40 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BDBD40 size 1911
public ?d_007dbd40@@YAXXZ
?d_007dbd40@@YAXXZ PROC
    db 081h, 0ECh, 018h, 001h, 000h, 000h, 057h, 08Bh, 0F9h, 08Ah, 047h, 01Ch, 08Bh, 00Dh
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 088h, 081h, 0BDh, 00Dh, 000h, 000h, 0C6h, 005h
    dd ?HighlightRendering@@3_NA
    db 000h, 08Ah, 047h, 030h, 084h, 0C0h, 074h, 02Dh, 06Ah, 001h, 06Ah, 000h
    call ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSurface8@@_N@Z
    db 08Bh, 017h, 083h, 0C4h, 008h, 08Bh, 0CFh, 0FFh, 052h, 018h, 08Bh, 084h, 024h, 028h, 001h, 000h
    db 000h, 0C6h, 000h, 001h, 0C6h, 047h, 030h, 000h, 0B0h, 001h, 05Fh, 081h, 0C4h, 018h, 001h, 000h
    db 000h, 0C2h, 010h, 000h, 08Bh, 084h, 024h, 020h, 001h, 000h, 000h, 08Bh, 017h, 050h, 08Bh, 0CFh
    db 0FFh, 052h, 014h, 085h, 0C0h, 075h, 00Ch, 032h, 0C0h, 05Fh, 081h, 0C4h, 018h, 001h, 000h, 000h
    db 0C2h, 010h, 000h, 0D9h, 005h
    dd g_Va01128AAC
    db 0B8h, 00Fh, 000h, 000h, 000h, 0D8h, 035h
    dd ?BfmeCameraGlobal12BB214@@3MA
    db 089h, 084h, 024h, 0E8h, 000h, 000h, 000h, 089h, 084h, 024h, 0F0h, 000h, 000h, 000h, 0B8h, 011h
    db 000h, 000h, 000h, 089h, 084h, 024h, 0F4h, 000h, 000h, 000h, 089h, 084h, 024h, 0FCh, 000h, 000h
    db 000h, 089h, 084h, 024h, 010h, 001h, 000h, 000h, 056h, 0BAh, 010h, 000h, 000h, 000h, 0B9h, 012h
    db 000h, 000h, 000h, 0BEh, 014h, 000h, 000h, 000h, 089h, 094h, 024h, 0F0h, 000h, 000h, 000h, 089h
    db 08Ch, 024h, 0FCh, 000h, 000h, 000h, 089h, 0B4h, 024h, 004h, 001h, 000h, 000h, 0C7h, 084h, 024h
    db 008h, 001h, 000h, 000h, 015h, 000h, 000h, 000h, 0C7h, 084h, 024h, 00Ch, 001h, 000h, 000h, 013h
    db 000h, 000h, 000h, 089h, 0B4h, 024h, 010h, 001h, 000h, 000h, 089h, 08Ch, 024h, 018h, 001h, 000h
    db 000h, 089h, 094h, 024h, 01Ch, 001h, 000h, 000h, 0D9h, 05Ch, 024h, 020h, 0D9h, 005h
    dd g_Va013073B8
    db 0D8h, 005h
    dd ?R3FieldSlope1096CF4@@3MA
    db 0D9h, 015h
    dd g_Va013073B8
    db 0D8h, 01Dh
    dd __real@41500000
    db 0DFh, 0E0h, 0F6h, 0C4h, 001h, 075h, 00Ah, 0C7h, 005h
    dd g_Va013073B8
    db 000h, 000h, 000h, 000h, 0D9h, 005h
    dd g_Va013073B8
    db 083h, 0ECh, 008h, 0DDh, 01Ch, 024h, 0FFh, 015h
    dd __imp__floor
    db 0D9h, 05Ch, 024h, 02Ch, 083h, 0C4h, 008h, 0D9h, 044h, 024h, 024h, 0DBh, 05Ch, 024h, 008h, 08Bh
    db 04Ch, 024h, 008h, 0DBh, 084h, 08Ch, 0ECh, 000h, 000h, 000h, 0D8h, 04Ch, 024h, 020h
    call __ftol2
    db 083h, 0F8h, 003h, 089h, 047h, 018h, 07Dh, 007h, 0C7h, 047h, 018h, 003h, 000h, 000h, 000h, 08Bh
    db 057h, 04Ch, 08Bh, 047h, 044h, 08Bh, 04Fh, 050h, 052h, 08Bh, 057h, 040h, 050h, 08Bh, 047h, 02Ch
    db 051h, 052h, 050h, 08Dh, 04Fh, 034h, 051h
    call ?j_0000e3d1@@YAXXZ
    db 08Bh, 050h, 008h, 052h
    call ?j_0003f242@@YAXXZ
    db 08Bh, 035h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 083h, 0C4h, 01Ch, 068h
    dd ?j_00007ac2@@YAXXZ
    db 06Ah, 004h, 06Ah, 02Ch, 08Dh, 044h, 024h, 048h, 050h
    call ?j_0000ae5c@@YAXXZ
    db 0D9h, 047h, 024h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ch, 0D9h, 047h, 024h, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 024h, 0D9h, 047h, 020h, 0D8h, 01Dh
    dd ?BfmeShadowScale@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 00Ch, 0D9h, 047h, 020h, 0D8h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 020h, 0D9h, 047h, 028h, 0D8h, 01Dh
    dd ?BfmeSubdualCapERD@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 00Ch, 0D9h, 047h, 028h, 0D8h, 025h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D9h, 05Fh, 028h, 0D9h, 047h, 024h, 08Bh, 057h, 040h, 0D8h, 005h
    dd ?Rva00064680NegativeScale@@3MB
    db 053h, 055h, 052h, 0D9h, 05Fh, 024h, 06Ah, 000h, 0D9h, 047h, 020h, 0D8h, 025h
    dd g_Va01128ABC
    db 0D9h, 05Fh, 020h, 0D9h, 047h, 028h, 0D8h, 005h
    dd __real@3ca3d70a
    db 0D9h, 05Fh, 028h, 0A1h
    dd ?D3DDevice@DX8Wrapper@@0PAUBfmeDevice@@A
    db 08Bh, 008h, 050h, 0FFh, 091h, 004h, 001h, 000h, 000h, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 001h, 08Dh, 054h, 024h, 03Ch, 052h, 08Dh, 054h, 024h, 03Ch, 052h, 0FFh, 050h, 04Ch, 08Bh
    db 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 001h, 0FFh, 050h, 03Ch, 08Bh, 00Dh
    dd ?FadeTacticalView@@3PAVFadeView@@A
    db 08Bh, 011h, 08Bh, 0D8h, 0FFh, 052h, 044h, 089h, 044h, 024h, 014h, 08Dh, 047h, 05Ch, 050h, 06Ah
    db 001h
    call ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z
    db 08Bh, 00Eh, 083h, 0C4h, 008h, 06Ah, 001h, 06Ah, 001h, 06Ah, 001h, 056h, 0FFh, 091h, 014h, 001h
    db 000h, 000h, 08Bh, 016h, 06Ah, 001h, 06Ah, 002h, 06Ah, 001h, 056h, 0FFh, 092h, 014h, 001h, 000h
    db 000h, 08Bh, 006h, 06Ah, 001h, 06Ah, 001h, 06Ah, 002h, 056h, 0FFh, 090h, 014h, 001h, 000h, 000h
    db 08Bh, 00Eh, 06Ah, 001h, 06Ah, 002h, 06Ah, 002h, 056h, 0FFh, 091h, 014h, 001h, 000h, 000h, 08Dh
    db 06Fh, 058h, 055h, 06Ah, 002h
    call ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z
    db 08Bh, 006h, 083h, 0C4h, 008h, 08Bh, 0CDh, 089h, 044h, 024h, 02Ch
    call ?Peek_D3D_Base_Texture@TextureBaseClass@@QBEPAUIDirect3DBaseTexture8@@XZ
    db 050h, 08Bh, 044h, 024h, 030h, 06Ah, 002h, 056h, 0FFh, 090h, 004h, 001h, 000h, 000h, 0D9h, 005h
    dd ?g_bfmeK1266A@@3MB
    db 0D8h, 074h, 024h, 028h, 08Bh, 054h, 024h, 038h, 003h, 0DAh, 0D9h, 05Ch, 024h, 02Ch, 08Bh, 04Ch
    db 024h, 014h, 08Bh, 044h, 024h, 03Ch, 003h, 0C8h, 089h, 05Ch, 024h, 010h, 0DBh, 044h, 024h, 010h
    db 089h, 04Ch, 024h, 010h, 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h, 0D9h, 054h, 024h, 028h
    db 08Bh, 04Ch, 024h, 020h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 0C7h, 044h, 024h, 024h, 000h, 000h, 080h, 03Fh, 089h, 04Ch, 024h, 04Ch, 0C7h, 044h, 024h, 020h
    db 000h, 000h, 000h, 000h, 0D9h, 054h, 024h, 018h, 08Bh, 054h, 024h, 018h, 0DBh, 044h, 024h, 010h
    db 089h, 054h, 024h, 044h, 08Bh, 054h, 024h, 024h, 089h, 054h, 024h, 050h, 0D9h, 054h, 024h, 014h
    db 08Bh, 054h, 024h, 020h, 0D8h, 025h
    dd ?g_bfmeADL@@3MA
    db 0C7h, 044h, 024h, 024h, 000h, 000h, 080h, 03Fh, 089h, 054h, 024h, 078h, 0C7h, 044h, 024h, 020h
    db 000h, 000h, 000h, 000h, 0D9h, 054h, 024h, 01Ch, 08Bh, 044h, 024h, 01Ch, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 089h, 044h, 024h, 048h, 08Bh, 084h, 024h, 038h, 001h, 000h, 000h, 0D8h, 030h, 0D9h, 054h, 024h
    db 010h, 0D8h, 04Ch, 024h, 028h, 0D9h, 054h, 024h, 058h, 0D9h, 005h
    dd ?BfmeSubdualCapERD@@3MB
    db 0D8h, 070h, 004h, 0D9h, 044h, 024h, 014h, 0D8h, 0C9h, 0D9h, 054h, 024h, 028h, 0D9h, 05Ch, 024h
    db 05Ch, 0D9h, 0CBh, 0D9h, 05Ch, 024h, 018h, 08Bh, 044h, 024h, 018h, 0DBh, 044h, 024h, 03Ch, 089h
    db 044h, 024h, 070h, 0D9h, 005h
    dd ?g_bfmeADL@@3MA
    db 08Bh, 044h, 024h, 024h, 089h, 044h, 024h, 07Ch, 0D8h, 0E9h, 08Bh, 044h, 024h, 020h, 0C7h, 044h
    db 024h, 024h, 000h, 000h, 080h, 03Fh, 089h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0D9h, 054h, 024h
    db 034h, 0D9h, 05Ch, 024h, 01Ch, 08Bh, 04Ch, 024h, 01Ch, 0D9h, 0C9h, 089h, 04Ch, 024h, 074h, 0D9h
    db 09Ch, 024h, 084h, 000h, 000h, 000h, 0D8h, 0CAh, 0D9h, 054h, 024h, 030h, 0DDh, 0DAh, 0D9h, 0C9h
    db 0D9h, 09Ch, 024h, 088h, 000h, 000h, 000h, 0DBh, 044h, 024h, 038h, 0D9h, 054h, 024h, 014h, 0D8h
    db 025h
    dd ?g_bfmeADL@@3MA
    db 0D9h, 054h, 024h, 040h, 08Bh, 044h, 024h, 040h, 0D9h, 05Ch, 024h, 018h, 08Bh, 04Ch, 024h, 018h
    db 0D9h, 05Ch, 024h, 01Ch, 08Bh, 054h, 024h, 01Ch, 0D9h, 044h, 024h, 014h, 089h, 08Ch, 024h, 09Ch
    db 000h, 000h, 000h, 0D8h, 04Ch, 024h, 010h, 08Bh, 04Ch, 024h, 024h, 089h, 094h, 024h, 0A0h, 000h
    db 000h, 000h, 08Bh, 054h, 024h, 028h, 0D9h, 094h, 024h, 0B0h, 000h, 000h, 000h, 089h, 08Ch, 024h
    db 0A8h, 000h, 000h, 000h, 089h, 094h, 024h, 0B4h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0DCh, 000h
    db 000h, 000h, 08Bh, 04Ch, 024h, 034h, 0D9h, 044h, 024h, 02Ch, 08Bh, 0D0h, 0DCh, 0C0h, 089h, 044h
    db 024h, 018h, 08Bh, 0C1h, 089h, 084h, 024h, 0CCh, 000h, 000h, 000h, 0D8h, 047h, 020h, 08Bh, 044h
    db 024h, 030h, 089h, 084h, 024h, 0E0h, 000h, 000h, 000h, 083h, 0C8h, 0FFh, 0D9h, 054h, 024h, 060h
    db 089h, 044h, 024h, 054h, 0D9h, 044h, 024h, 02Ch, 089h, 084h, 024h, 080h, 000h, 000h, 000h, 0D8h
    db 047h, 024h, 089h, 084h, 024h, 0ACh, 000h, 000h, 000h, 089h, 084h, 024h, 0D8h, 000h, 000h, 000h
    db 0A0h
    dd g_Va012BC2C3
    db 084h, 0C0h, 0D9h, 0C0h, 0D9h, 054h, 024h, 064h, 089h, 04Ch, 024h, 01Ch, 0D9h, 05Ch, 024h, 06Ch
    db 0C7h, 044h, 024h, 020h, 000h, 000h, 000h, 000h, 0D9h, 044h, 024h, 060h, 08Bh, 04Ch, 024h, 020h
    db 0D8h, 067h, 028h, 0C7h, 044h, 024h, 024h, 000h, 000h, 080h, 03Fh, 089h, 094h, 024h, 0C8h, 000h
    db 000h, 000h, 08Bh, 054h, 024h, 024h, 0D9h, 05Ch, 024h, 068h, 05Dh, 0D9h, 044h, 024h, 05Ch, 089h
    db 08Ch, 024h, 0CCh, 000h, 000h, 000h, 0D8h, 047h, 028h, 089h, 094h, 024h, 0D0h, 000h, 000h, 000h
    db 05Bh, 0D9h, 05Ch, 024h, 058h, 0D9h, 047h, 024h, 0D9h, 054h, 024h, 02Ch, 0D9h, 094h, 024h, 088h
    db 000h, 000h, 000h, 0D9h, 09Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 0C9h, 0D9h, 0C0h, 0D8h, 067h
    db 028h, 0D9h, 09Ch, 024h, 08Ch, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 084h, 000h
    db 000h, 000h, 0D9h, 047h, 020h, 0D9h, 054h, 024h, 028h, 0D9h, 09Ch, 024h, 0B0h, 000h, 000h, 000h
    db 0D9h, 094h, 024h, 0B4h, 000h, 000h, 000h, 0D9h, 09Ch, 024h, 0BCh, 000h, 000h, 000h, 0D9h, 084h
    db 024h, 0B0h, 000h, 000h, 000h, 0D8h, 067h, 028h, 0D9h, 09Ch, 024h, 0B8h, 000h, 000h, 000h, 0D9h
    db 084h, 024h, 0B0h, 000h, 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 0B0h, 000h, 000h, 000h
    db 0D9h, 044h, 024h, 028h, 0D9h, 044h, 024h, 02Ch, 0D9h, 094h, 024h, 0E0h, 000h, 000h, 000h, 0D9h
    db 09Ch, 024h, 0E8h, 000h, 000h, 000h, 0D9h, 0C0h, 0D8h, 067h, 028h, 0D9h, 09Ch, 024h, 0E4h, 000h
    db 000h, 000h, 0D8h, 047h, 028h, 0D9h, 09Ch, 024h, 0DCh, 000h, 000h, 000h, 074h, 00Dh, 06Ah, 002h
    db 06Ah, 013h
    call ?j_0001321e@@YAXXZ
    db 06Ah, 004h, 0EBh, 00Bh, 06Ah, 005h, 06Ah, 013h
    call ?j_0001321e@@YAXXZ
    db 06Ah, 006h, 06Ah, 014h
    call ?j_0001321e@@YAXXZ
    db 083h, 0C4h, 010h, 06Ah, 001h, 06Ah, 01Bh
    call ?j_0001321e@@YAXXZ
    db 083h, 0C4h, 008h
    call ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ
    db 08Bh, 00Eh, 06Ah, 001h, 06Ah, 01Bh, 056h, 0FFh, 091h, 0E4h, 000h, 000h, 000h, 08Bh, 016h, 06Ah
    db 000h, 056h, 0FFh, 092h, 070h, 001h, 000h, 000h, 08Bh, 006h, 068h, 044h, 003h, 000h, 000h, 056h
    db 0FFh, 090h, 064h, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 003h, 06Ah, 001h, 06Ah, 000h, 056h, 0FFh
    db 091h, 00Ch, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 000h, 06Ah, 00Bh, 06Ah, 000h, 056h, 0FFh, 092h
    db 00Ch, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 001h, 06Ah, 002h, 06Ah, 000h, 056h, 0FFh, 090h, 00Ch
    db 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 002h, 06Ah, 003h, 06Ah, 000h, 056h, 0FFh, 091h, 00Ch, 001h
    db 000h, 000h, 08Bh, 016h, 06Ah, 001h, 06Ah, 005h, 06Ah, 000h, 056h, 0FFh, 092h, 00Ch, 001h, 000h
    db 000h, 08Bh, 006h, 06Ah, 002h, 06Ah, 006h, 06Ah, 000h, 056h, 0FFh, 090h, 00Ch, 001h, 000h, 000h
    db 08Bh, 00Eh, 06Ah, 003h, 06Ah, 004h, 06Ah, 000h, 056h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh
    db 016h, 06Ah, 004h, 06Ah, 001h, 06Ah, 001h, 056h, 0FFh, 092h, 00Ch, 001h, 000h, 000h, 08Bh, 006h
    db 06Ah, 001h, 06Ah, 00Bh, 06Ah, 001h, 056h, 0FFh, 090h, 00Ch, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah
    db 001h, 06Ah, 002h, 06Ah, 001h, 056h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 002h
    db 06Ah, 003h, 06Ah, 001h, 056h, 0FFh, 092h, 00Ch, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 005h, 06Ah
    db 004h, 06Ah, 001h, 056h, 0FFh, 090h, 00Ch, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 001h, 06Ah, 005h
    db 06Ah, 001h, 056h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 002h, 06Ah, 006h, 06Ah
    db 001h, 056h, 0FFh, 092h, 00Ch, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 005h, 06Ah, 001h, 06Ah, 002h
    db 056h, 0FFh, 090h, 00Ch, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 000h, 06Ah, 018h, 06Ah, 002h, 056h
    db 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 016h, 06Ah, 002h, 06Ah, 00Bh, 06Ah, 002h, 056h, 0FFh
    db 092h, 00Ch, 001h, 000h, 000h, 08Bh, 006h, 06Ah, 001h, 06Ah, 002h, 06Ah, 002h, 056h, 0FFh, 090h
    db 00Ch, 001h, 000h, 000h, 08Bh, 00Eh, 06Ah, 002h, 06Ah, 003h, 06Ah, 002h, 056h, 0FFh, 091h, 00Ch
    db 001h, 000h, 000h, 08Bh, 016h, 06Ah, 005h, 06Ah, 004h, 06Ah, 002h, 056h, 0FFh, 092h, 00Ch, 001h
    db 000h, 000h, 08Bh, 006h, 06Ah, 001h, 06Ah, 005h, 06Ah, 002h, 056h, 0FFh, 090h, 00Ch, 001h, 000h
    db 000h, 08Bh, 00Eh, 06Ah, 002h, 06Ah, 006h, 06Ah, 002h, 056h, 0FFh, 091h, 00Ch, 001h, 000h, 000h
    db 08Bh, 016h, 06Ah, 02Ch, 08Dh, 044h, 024h, 040h, 050h, 06Ah, 002h, 06Ah, 005h, 056h, 0FFh, 092h
    db 04Ch, 001h, 000h, 000h, 08Bh, 017h, 08Bh, 0CFh, 0FFh, 052h, 018h, 05Eh, 0B0h, 001h, 05Fh, 081h
    db 0C4h, 018h, 001h, 000h, 000h, 0C2h, 010h, 000h
?d_007dbd40@@YAXXZ ENDP
_TEXT$d00bdbd40 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x007DCAF0 size 138
public ?d_007dcaf0@@YAXXZ
?d_007dcaf0@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 46h, 04h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 06h, 8Bh, 08h
    db 50h, 0FFh, 51h, 08h, 8Bh, 46h, 08h, 3Bh, 0C7h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h
    db 08h, 57h, 89h, 7Eh, 04h, 89h, 7Eh, 08h, 8Bh, 4Eh, 34h, 8Bh, 46h, 38h, 8Dh, 54h
    db 24h, 0Fh, 52h, 51h, 50h, 50h, 0E8h, 0F0h, 0D0h, 85h, 0FFh, 89h, 46h, 38h, 8Bh, 46h
    db 4Ch, 83h, 0C4h, 14h, 3Bh, 0C7h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 46h
    db 40h, 3Bh, 0C7h, 89h, 7Eh, 4Ch, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 8Bh, 46h
    db 50h, 3Bh, 0C7h, 89h, 7Eh, 40h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 46h
    db 44h, 3Bh, 0C7h, 89h, 7Eh, 50h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 89h, 7Eh
    db 44h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 59h, 0C3h
?d_007dcaf0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DCBA0 size 21
public ?d_007dcba0@@YAXXZ
?d_007dcba0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 50h, 56h, 56h, 0E8h, 0FEh, 0E0h, 21h, 00h, 8Bh
    db 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007dcba0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DCBC0 size 7
public ?d_007dcbc0@@YAXXZ
?d_007dcbc0@@YAXXZ PROC
    db 8Ah, 81h, 6Ch, 30h, 00h, 00h, 0C3h
?d_007dcbc0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DCBD0 size 9
public ?d_007dcbd0@@YAXXZ
?d_007dcbd0@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 80h, 8Ch, 12h, 01h, 0C3h
?d_007dcbd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DCC60 size 91
public ?d_007dcc60@@YAXXZ
?d_007dcc60@@YAXXZ PROC
    db 0A1h, 34h, 05h, 34h, 01h, 6Ah, 00h, 6Ah, 00h, 0C6h, 05h, 0FCh, 6Dh, 2Dh, 01h, 01h
    db 8Bh, 08h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h
    db 6Ah, 00h, 6Ah, 01h, 50h, 0FFh, 92h, 04h, 01h, 00h, 00h, 6Ah, 00h, 6Ah, 18h, 6Ah
    db 00h, 0E8h, 4Dh, 95h, 84h, 0FFh, 6Ah, 00h, 6Ah, 0Bh, 6Ah, 00h, 0E8h, 42h, 95h, 84h
    db 0FFh, 6Ah, 00h, 6Ah, 18h, 6Ah, 01h, 0E8h, 37h, 95h, 84h, 0FFh, 6Ah, 01h, 6Ah, 0Bh
    db 6Ah, 01h, 0E8h, 2Ch, 95h, 84h, 0FFh, 83h, 0C4h, 30h, 0C3h
?d_007dcc60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007DD170 size 9
public ?d_007dd170@@YAXXZ
?d_007dd170@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 94h, 8Ch, 12h, 01h, 0C3h
?d_007dd170@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2020 size 187
public ?d_007e2020@@YAXXZ
?d_007e2020@@YAXXZ PROC
    db 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 00h, 6Ah, 02h, 50h, 0FFh, 91h, 04h, 01h
    db 00h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 00h, 6Ah, 03h, 50h, 0FFh, 92h
    db 04h, 01h, 00h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 00h, 50h, 0FFh, 91h
    db 0ACh, 01h, 00h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 00h, 6Ah, 00h, 50h
    db 0FFh, 92h, 04h, 01h, 00h, 00h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 00h, 6Ah
    db 01h, 50h, 0FFh, 91h, 04h, 01h, 00h, 00h, 6Ah, 00h, 6Ah, 18h, 6Ah, 00h, 0E8h, 60h
    db 41h, 84h, 0FFh, 6Ah, 00h, 6Ah, 0Bh, 6Ah, 00h, 0E8h, 55h, 41h, 84h, 0FFh, 6Ah, 00h
    db 6Ah, 18h, 6Ah, 01h, 0E8h, 4Ah, 41h, 84h, 0FFh, 6Ah, 01h, 6Ah, 0Bh, 6Ah, 01h, 0E8h
    db 3Fh, 41h, 84h, 0FFh, 6Ah, 00h, 6Ah, 18h, 6Ah, 02h, 0E8h, 34h, 41h, 84h, 0FFh, 6Ah
    db 02h, 6Ah, 0Bh, 6Ah, 02h, 0E8h, 29h, 41h, 84h, 0FFh, 83h, 0C4h, 48h, 6Ah, 00h, 6Ah
    db 18h, 6Ah, 03h, 0E8h, 1Bh, 41h, 84h, 0FFh, 6Ah, 03h, 6Ah, 0Bh, 6Ah, 03h, 0E8h, 10h
    db 41h, 84h, 0FFh, 83h, 0C4h, 18h, 0E9h, 75h, 1Bh, 12h, 00h
?d_007e2020@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2170 size 9
public ?d_007e2170@@YAXXZ
?d_007e2170@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 00h, 8Dh, 12h, 01h, 0C3h
?d_007e2170@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2E00 size 9
public ?d_007e2e00@@YAXXZ
?d_007e2e00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 01h, 0C2h, 04h, 00h
?d_007e2e00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2E10 size 10
public ?d_007e2e10@@YAXXZ
?d_007e2e10@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 04h, 0C2h, 04h, 00h
?d_007e2e10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2E20 size 28
public ?d_007e2e20@@YAXXZ
?d_007e2e20@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 8Bh, 06h, 85h, 0C0h, 74h, 0Fh, 50h, 0E8h, 0BFh, 0F0h, 09h
    db 00h, 83h, 0C4h, 04h, 0C7h, 06h, 00h, 00h, 00h, 00h, 5Eh, 0C3h
?d_007e2e20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E2EA0 size 10
public ?d_007e2ea0@@YAXXZ
?d_007e2ea0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 08h, 0C2h, 04h, 00h
?d_007e2ea0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3160 size 29
public ?d_007e3160@@YAXXZ
?d_007e3160@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 74h, 13h, 8Bh, 49h, 08h, 83h, 0F9h, 06h, 74h, 05h, 83h
    db 0F9h, 07h, 75h, 06h, 0B8h, 01h, 00h, 00h, 00h, 0C3h, 33h, 0C0h, 0C3h
?d_007e3160@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3190 size 45
public ?d_007e3190@@YAXXZ
?d_007e3190@@YAXXZ PROC
    db 83h, 79h, 08h, 07h, 75h, 22h, 8Bh, 49h, 04h, 8Bh, 11h, 56h, 8Bh, 74h, 24h, 08h
    db 8Bh, 46h, 04h, 50h, 56h, 0FFh, 52h, 10h, 8Bh, 56h, 04h, 33h, 0C9h, 3Bh, 0C2h, 0Fh
    db 94h, 0C1h, 8Ah, 0C1h, 5Eh, 0C2h, 04h, 00h, 32h, 0C0h, 0C2h, 04h, 00h
?d_007e3190@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E39B0 size 7
public ?d_007e39b0@@YAXXZ
?d_007e39b0@@YAXXZ PROC
    db 0C7h, 01h, 14h, 8Dh, 12h, 01h, 0C3h
?d_007e39b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E39C0 size 31
public ?d_007e39c0@@YAXXZ
?d_007e39c0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 14h, 8Dh, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0DAh, 0E4h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007e39c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3A10 size 10
public ?d_007e3a10@@YAXXZ
?d_007e3a10@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 20h, 0C2h, 04h, 00h
?d_007e3a10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3A20 size 16
public ?d_007e3a20@@YAXXZ
?d_007e3a20@@YAXXZ PROC
    db 8Bh, 0C1h, 32h, 0C9h, 88h, 08h, 88h, 48h, 01h, 88h, 88h, 05h, 01h, 00h, 00h, 0C3h
?d_007e3a20@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3A40 size 7
public ?d_007e3a40@@YAXXZ
?d_007e3a40@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0E8h, 08h, 0C3h
?d_007e3a40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3A50 size 7
public ?d_007e3a50@@YAXXZ
?d_007e3a50@@YAXXZ PROC
    db 8Bh, 49h, 2Ch, 8Bh, 01h, 0FFh, 20h
?d_007e3a50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3A70 size 9
public ?d_007e3a70@@YAXXZ
?d_007e3a70@@YAXXZ PROC
    db 8Bh, 0C1h, 0C7h, 00h, 14h, 8Dh, 12h, 01h, 0C3h
?d_007e3a70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3AB0 size 6
public ?d_007e3ab0@@YAXXZ
?d_007e3ab0@@YAXXZ PROC
    db 0B8h, 0D8h, 0CBh, 12h, 01h, 0C3h
?d_007e3ab0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3AC0 size 5
public ?d_007e3ac0@@YAXXZ
?d_007e3ac0@@YAXXZ PROC
    db 0C6h, 41h, 14h, 01h, 0C3h
?d_007e3ac0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3C10 size 8
public ?d_007e3c10@@YAXXZ
?d_007e3c10@@YAXXZ PROC
    db 8Bh, 41h, 40h, 99h, 0F7h, 79h, 44h, 0C3h
?d_007e3c10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E3E60 size 1804
public ?d_007e3e60@@YAXXZ
?d_007e3e60@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 2Bh, 45h, 05h, 01h, 50h, 0B8h, 98h
    db 10h, 00h, 00h, 64h, 89h, 25h, 00h, 00h, 00h, 00h, 0E8h, 0E1h, 2Dh, 21h, 00h, 55h
    db 8Bh, 0E9h, 8Bh, 45h, 2Ch, 85h, 0C0h, 89h, 6Ch, 24h, 30h, 0Fh, 84h, 0C5h, 06h, 00h
    db 00h, 8Bh, 45h, 14h, 85h, 0C0h, 0Fh, 84h, 0BAh, 06h, 00h, 00h, 8Ah, 45h, 38h, 84h
    db 0C0h, 74h, 0Bh, 8Bh, 45h, 18h, 85h, 0C0h, 0Fh, 84h, 0A8h, 06h, 00h, 00h, 0E8h, 0DDh
    db 0F1h, 11h, 00h, 8Bh, 4Dh, 2Ch, 8Bh, 41h, 24h, 83h, 0F8h, 05h, 0C7h, 84h, 24h, 0A4h
    db 10h, 00h, 00h, 00h, 00h, 00h, 00h, 74h, 2Bh, 83h, 0F8h, 02h, 74h, 26h, 0C7h, 84h
    db 24h, 0A4h, 10h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 32h, 1Ch, 12h, 00h, 5Dh, 8Bh
    db 8Ch, 24h, 98h, 10h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0A4h
    db 10h, 00h, 00h, 0C3h, 8Bh, 01h, 57h, 0FFh, 50h, 10h, 8Bh, 0F8h, 85h, 0FFh, 75h, 27h
    db 0C7h, 84h, 24h, 0A8h, 10h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 00h, 1Ch, 12h, 00h
    db 5Fh, 5Dh, 8Bh, 8Ch, 24h, 98h, 10h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0A4h, 10h, 00h, 00h, 0C3h, 8Bh, 45h, 2Ch, 8Bh, 48h, 1Ch, 89h, 4Ch, 24h
    db 10h, 8Ah, 4Dh, 38h, 84h, 0C9h, 53h, 56h, 0Fh, 84h, 58h, 03h, 00h, 00h, 83h, 78h
    db 24h, 05h, 0Fh, 85h, 4Eh, 03h, 00h, 00h, 8Bh, 45h, 14h, 8Dh, 54h, 24h, 48h, 52h
    db 50h, 0E8h, 4Ah, 12h, 1Ch, 00h, 8Bh, 55h, 18h, 8Dh, 8Ch, 24h, 88h, 00h, 00h, 00h
    db 51h, 52h, 0E8h, 39h, 12h, 1Ch, 00h, 8Bh, 4Dh, 30h, 8Bh, 45h, 34h, 8Bh, 0F1h, 89h
    db 4Ch, 24h, 58h, 89h, 8Ch, 24h, 90h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 60h, 0D1h, 0FEh
    db 8Bh, 0D8h, 0D1h, 0FBh, 89h, 84h, 24h, 94h, 00h, 00h, 00h, 83h, 0C4h, 10h, 89h, 44h
    db 24h, 4Ch, 48h, 0Fh, 0AFh, 0C1h, 8Bh, 0D3h, 89h, 9Ch, 24h, 90h, 00h, 00h, 00h, 03h
    db 44h, 24h, 60h, 8Bh, 0D8h, 2Bh, 0D9h, 8Dh, 4Ah, 0FFh, 89h, 4Ch, 24h, 28h, 0Fh, 0AFh
    db 4Ch, 24h, 5Ch, 89h, 54h, 24h, 58h, 8Bh, 54h, 24h, 64h, 03h, 0D1h, 89h, 54h, 24h
    db 30h, 8Bh, 54h, 24h, 68h, 03h, 0CAh, 8Bh, 94h, 24h, 84h, 00h, 00h, 00h, 89h, 4Ch
    db 24h, 20h, 8Bh, 8Ch, 24h, 88h, 00h, 00h, 00h, 4Ah, 0Fh, 0AFh, 0D1h, 89h, 74h, 24h
    db 54h, 89h, 0B4h, 24h, 8Ch, 00h, 00h, 00h, 03h, 94h, 24h, 98h, 00h, 00h, 00h, 8Bh
    db 0F2h, 2Bh, 0F1h, 8Bh, 4Ch, 24h, 18h, 03h, 0CFh, 89h, 4Ch, 24h, 34h, 8Dh, 8Ch, 24h
    db 0A8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 50h, 03h, 0C9h, 89h, 7Ch
    db 24h, 14h, 8Bh, 0F9h, 8Bh, 4Ch, 24h, 48h, 0F7h, 0D9h, 2Bh, 0CFh, 8Bh, 7Ch, 24h, 54h
    db 89h, 4Ch, 24h, 7Ch, 8Bh, 4Ch, 24h, 5Ch, 03h, 0CFh, 0F7h, 0D9h, 89h, 4Ch, 24h, 70h
    db 8Bh, 8Ch, 24h, 88h, 00h, 00h, 00h, 03h, 0C9h, 8Bh, 0F9h, 8Bh, 8Ch, 24h, 80h, 00h
    db 00h, 00h, 0F7h, 0D9h, 2Bh, 0CFh, 89h, 4Ch, 24h, 78h, 8Bh, 4Ch, 24h, 48h, 03h, 0C9h
    db 8Bh, 0F9h, 8Bh, 4Ch, 24h, 18h, 89h, 74h, 24h, 24h, 2Bh, 0CFh, 0D1h, 0E1h, 89h, 4Ch
    db 24h, 44h, 8Bh, 4Ch, 24h, 28h, 85h, 0C9h, 0Fh, 8Ch, 0C7h, 04h, 00h, 00h, 8Bh, 7Ch
    db 24h, 18h, 03h, 0FFh, 41h, 89h, 7Ch, 24h, 40h, 89h, 4Ch, 24h, 2Ch, 0EBh, 04h, 8Bh
    db 74h, 24h, 24h, 8Bh, 4Ch, 24h, 54h, 49h, 0Fh, 88h, 7Eh, 01h, 00h, 00h, 41h, 89h
    db 4Ch, 24h, 38h, 8Bh, 4Ch, 24h, 30h, 0Fh, 0B6h, 31h, 8Bh, 4Ch, 24h, 20h, 0Fh, 0B6h
    db 39h, 0C1h, 0E7h, 02h, 8Bh, 8Fh, 38h, 7Ch, 30h, 01h, 8Bh, 0BFh, 38h, 78h, 30h, 01h
    db 0C1h, 0E6h, 02h, 03h, 8Eh, 38h, 80h, 30h, 01h, 8Bh, 0AEh, 38h, 84h, 30h, 01h, 0FFh
    db 44h, 24h, 30h, 8Bh, 74h, 24h, 20h, 46h, 89h, 7Ch, 24h, 18h, 89h, 74h, 24h, 20h
    db 0Fh, 0B6h, 30h, 03h, 0FEh, 8Bh, 3Ch, 0BDh, 38h, 88h, 30h, 01h, 0C1h, 0E7h, 08h, 03h
    db 0F1h, 0Bh, 3Ch, 0B5h, 38h, 88h, 30h, 01h, 0Fh, 0B6h, 30h, 0C1h, 0E7h, 08h, 03h, 0F5h
    db 0Bh, 3Ch, 0B5h, 38h, 88h, 30h, 01h, 0Fh, 0B6h, 32h, 0Bh, 3Ch, 0B5h, 38h, 74h, 30h
    db 01h, 8Bh, 74h, 24h, 14h, 89h, 3Eh, 8Bh, 7Ch, 24h, 18h, 83h, 0C6h, 04h, 89h, 74h
    db 24h, 14h, 0Fh, 0B6h, 70h, 01h, 03h, 0FEh, 8Bh, 3Ch, 0BDh, 38h, 88h, 30h, 01h, 0C1h
    db 0E7h, 08h, 40h, 89h, 74h, 24h, 28h, 03h, 0F1h, 0Bh, 3Ch, 0B5h, 38h, 88h, 30h, 01h
    db 8Bh, 74h, 24h, 28h, 0C1h, 0E7h, 08h, 03h, 0F5h, 0Bh, 3Ch, 0B5h, 38h, 88h, 30h, 01h
    db 0Fh, 0B6h, 72h, 01h, 0Bh, 3Ch, 0B5h, 38h, 74h, 30h, 01h, 8Bh, 74h, 24h, 14h, 89h
    db 3Eh, 8Bh, 7Ch, 24h, 18h, 42h, 83h, 0C6h, 04h, 89h, 74h, 24h, 14h, 0Fh, 0B6h, 33h
    db 03h, 0FEh, 8Bh, 3Ch, 0BDh, 38h, 88h, 30h, 01h, 0C1h, 0E7h, 08h, 03h, 0F1h, 0Bh, 3Ch
    db 0B5h, 38h, 88h, 30h, 01h, 0Fh, 0B6h, 33h, 03h, 0F5h, 0C1h, 0E7h, 08h, 89h, 6Ch, 24h
    db 74h, 8Bh, 2Ch, 0B5h, 38h, 88h, 30h, 01h, 8Bh, 74h, 24h, 24h, 0Bh, 0FDh, 0Fh, 0B6h
    db 2Eh, 0Bh, 3Ch, 0ADh, 38h, 74h, 30h, 01h, 40h, 8Bh, 0EFh, 8Bh, 7Ch, 24h, 1Ch, 89h
    db 2Fh, 8Bh, 6Ch, 24h, 18h, 83h, 0C7h, 04h, 42h, 43h, 89h, 7Ch, 24h, 1Ch, 0Fh, 0B6h
    db 3Bh, 46h, 03h, 0EFh, 8Bh, 2Ch, 0ADh, 38h, 88h, 30h, 01h, 03h, 0CFh, 0C1h, 0E5h, 08h
    db 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h, 8Bh, 4Ch, 24h, 74h, 03h, 0F9h, 8Bh, 0Ch, 0BDh
    db 38h, 88h, 30h, 01h, 0C1h, 0E5h, 08h, 0Bh, 0E9h, 0Fh, 0B6h, 0Eh, 8Bh, 3Ch, 8Dh, 38h
    db 74h, 30h, 01h, 8Bh, 4Ch, 24h, 1Ch, 0Bh, 0EFh, 83h, 0C1h, 04h, 89h, 69h, 0FCh, 89h
    db 4Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 38h, 43h, 46h, 49h, 89h, 74h, 24h, 24h, 89h, 4Ch
    db 24h, 38h, 0Fh, 85h, 8Bh, 0FEh, 0FFh, 0FFh, 8Bh, 6Ch, 24h, 3Ch, 8Bh, 4Ch, 24h, 7Ch
    db 8Bh, 7Ch, 24h, 30h, 03h, 0C1h, 03h, 0D9h, 8Bh, 4Ch, 24h, 70h, 03h, 0F9h, 89h, 7Ch
    db 24h, 30h, 8Bh, 7Ch, 24h, 20h, 03h, 0F9h, 8Bh, 4Ch, 24h, 78h, 03h, 0F1h, 03h, 0D1h
    db 8Bh, 4Ch, 24h, 44h, 89h, 7Ch, 24h, 20h, 8Bh, 7Ch, 24h, 14h, 03h, 0F9h, 8Bh, 4Dh
    db 30h, 0C1h, 0E1h, 02h, 8Bh, 0E9h, 0C1h, 0E9h, 02h, 89h, 74h, 24h, 24h, 89h, 7Ch, 24h
    db 14h, 8Bh, 7Ch, 24h, 34h, 8Dh, 0B4h, 24h, 0A8h, 00h, 00h, 00h, 0F3h, 0A5h, 8Bh, 0CDh
    db 8Bh, 6Ch, 24h, 3Ch, 83h, 0E1h, 03h, 0F3h, 0A4h, 8Bh, 74h, 24h, 34h, 8Dh, 8Ch, 24h
    db 0A8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 40h, 03h, 0F1h, 8Bh, 4Ch
    db 24h, 2Ch, 49h, 89h, 74h, 24h, 34h, 89h, 4Ch, 24h, 2Ch, 0Fh, 85h, 0EEh, 0FDh, 0FFh
    db 0FFh, 0E9h, 9Fh, 02h, 00h, 00h, 8Bh, 45h, 14h, 8Dh, 54h, 24h, 48h, 52h, 50h, 0E8h
    db 0FCh, 0Eh, 1Ch, 00h, 8Bh, 45h, 30h, 8Bh, 4Dh, 34h, 8Bh, 5Ch, 24h, 68h, 8Bh, 0F0h
    db 8Bh, 0D1h, 0D1h, 0F8h, 0D1h, 0F9h, 89h, 44h, 24h, 5Ch, 8Bh, 44h, 24h, 58h, 89h, 54h
    db 24h, 54h, 83h, 0C4h, 08h, 4Ah, 0Fh, 0AFh, 0D0h, 03h, 0D3h, 8Bh, 0DAh, 2Bh, 0D8h, 8Dh
    db 41h, 0FFh, 89h, 44h, 24h, 2Ch, 0Fh, 0AFh, 44h, 24h, 5Ch, 89h, 4Ch, 24h, 58h, 8Bh
    db 4Ch, 24h, 64h, 03h, 0C8h, 89h, 4Ch, 24h, 1Ch, 8Bh, 4Ch, 24h, 68h, 03h, 0C1h, 89h
    db 44h, 24h, 20h, 8Bh, 44h, 24h, 18h, 03h, 0C7h, 89h, 44h, 24h, 24h, 8Bh, 44h, 24h
    db 50h, 8Dh, 8Ch, 24h, 0A8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 34h, 8Dh, 0Ch, 00h, 8Bh
    db 0C6h, 0F7h, 0D8h, 2Bh, 0C1h, 8Bh, 4Ch, 24h, 5Ch, 89h, 7Ch, 24h, 14h, 8Bh, 7Ch, 24h
    db 54h, 03h, 0F9h, 8Dh, 0Ch, 36h, 89h, 74h, 24h, 48h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 18h
    db 2Bh, 0CEh, 8Bh, 74h, 24h, 2Ch, 0F7h, 0DFh, 0D1h, 0E1h, 85h, 0F6h, 89h, 44h, 24h, 28h
    db 89h, 7Ch, 24h, 30h, 89h, 4Ch, 24h, 38h, 0Fh, 8Ch, 0E7h, 01h, 00h, 00h, 8Bh, 74h
    db 24h, 18h, 03h, 0F6h, 89h, 74h, 24h, 40h, 8Bh, 74h, 24h, 2Ch, 46h, 89h, 74h, 24h
    db 18h, 0EBh, 0Dh, 8Bh, 44h, 24h, 28h, 8Bh, 7Ch, 24h, 30h, 8Bh, 4Ch, 24h, 38h, 90h
    db 8Bh, 74h, 24h, 54h, 4Eh, 0Fh, 88h, 51h, 01h, 00h, 00h, 46h, 89h, 74h, 24h, 2Ch
    db 8Bh, 44h, 24h, 1Ch, 0Fh, 0B6h, 08h, 8Bh, 44h, 24h, 20h, 0Fh, 0B6h, 38h, 0C1h, 0E1h
    db 02h, 8Bh, 0A9h, 38h, 80h, 30h, 01h, 8Bh, 0B1h, 38h, 84h, 30h, 01h, 8Bh, 4Ch, 24h
    db 1Ch, 0C1h, 0E7h, 02h, 8Bh, 87h, 38h, 7Ch, 30h, 01h, 8Bh, 0BFh, 38h, 78h, 30h, 01h
    db 03h, 0C5h, 8Bh, 6Ch, 24h, 20h, 41h, 45h, 89h, 4Ch, 24h, 1Ch, 0Fh, 0B6h, 0Ah, 89h
    db 6Ch, 24h, 20h, 8Dh, 2Ch, 39h, 8Bh, 2Ch, 0ADh, 38h, 88h, 30h, 01h, 81h, 0CDh, 00h
    db 0FFh, 0FFh, 0FFh, 03h, 0C8h, 0C1h, 0E5h, 08h, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h, 0Fh
    db 0B6h, 0Ah, 0C1h, 0E5h, 08h, 03h, 0CEh, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h, 8Bh, 4Ch
    db 24h, 14h, 89h, 29h, 83h, 0C1h, 04h, 89h, 4Ch, 24h, 14h, 0Fh, 0B6h, 4Ah, 01h, 8Dh
    db 2Ch, 39h, 8Bh, 2Ch, 0ADh, 38h, 88h, 30h, 01h, 81h, 0CDh, 00h, 0FFh, 0FFh, 0FFh, 42h
    db 0C1h, 0E5h, 08h, 89h, 4Ch, 24h, 44h, 03h, 0C8h, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h
    db 8Bh, 4Ch, 24h, 44h, 0C1h, 0E5h, 08h, 03h, 0CEh, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h
    db 8Bh, 4Ch, 24h, 14h, 89h, 29h, 83h, 0C1h, 04h, 89h, 4Ch, 24h, 14h, 0Fh, 0B6h, 0Bh
    db 8Dh, 2Ch, 39h, 8Bh, 2Ch, 0ADh, 38h, 88h, 30h, 01h, 03h, 0C8h, 81h, 0CDh, 00h, 0FFh
    db 0FFh, 0FFh, 0C1h, 0E5h, 08h, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h, 0Fh, 0B6h, 0Bh, 03h
    db 0CEh, 0C1h, 0E5h, 08h, 0Bh, 2Ch, 8Dh, 38h, 88h, 30h, 01h, 8Bh, 4Ch, 24h, 34h, 89h
    db 29h, 0Fh, 0B6h, 6Bh, 01h, 83h, 0C1h, 04h, 42h, 43h, 03h, 0FDh, 8Bh, 3Ch, 0BDh, 38h
    db 88h, 30h, 01h, 81h, 0CFh, 00h, 0FFh, 0FFh, 0FFh, 03h, 0C5h, 0C1h, 0E7h, 08h, 0Bh, 3Ch
    db 85h, 38h, 88h, 30h, 01h, 03h, 0EEh, 8Bh, 04h, 0ADh, 38h, 88h, 30h, 01h, 0C1h, 0E7h
    db 08h, 0Bh, 0F8h, 8Bh, 44h, 24h, 2Ch, 89h, 39h, 83h, 0C1h, 04h, 89h, 4Ch, 24h, 34h
    db 43h, 48h, 89h, 44h, 24h, 2Ch, 0Fh, 85h, 0C4h, 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 38h
    db 8Bh, 7Ch, 24h, 30h, 8Bh, 44h, 24h, 28h, 8Bh, 6Ch, 24h, 3Ch, 8Bh, 74h, 24h, 1Ch
    db 03h, 0D0h, 03h, 0D8h, 8Bh, 44h, 24h, 20h, 03h, 0C7h, 03h, 0F7h, 8Bh, 7Ch, 24h, 14h
    db 03h, 0F9h, 8Bh, 4Dh, 30h, 0C1h, 0E1h, 02h, 89h, 44h, 24h, 20h, 8Bh, 0C1h, 0C1h, 0E9h
    db 02h, 89h, 74h, 24h, 1Ch, 89h, 7Ch, 24h, 14h, 8Bh, 7Ch, 24h, 24h, 8Dh, 0B4h, 24h
    db 0A8h, 00h, 00h, 00h, 0F3h, 0A5h, 8Bh, 0C8h, 8Bh, 44h, 24h, 40h, 83h, 0E1h, 03h, 0F3h
    db 0A4h, 8Dh, 8Ch, 24h, 0A8h, 00h, 00h, 00h, 89h, 4Ch, 24h, 34h, 8Bh, 4Ch, 24h, 24h
    db 03h, 0C8h, 8Bh, 44h, 24h, 18h, 48h, 89h, 4Ch, 24h, 24h, 89h, 44h, 24h, 18h, 0Fh
    db 85h, 2Eh, 0FEh, 0FFh, 0FFh, 8Bh, 4Dh, 2Ch, 8Bh, 11h, 0FFh, 52h, 14h, 8Bh, 45h, 48h
    db 89h, 45h, 4Ch, 0C7h, 84h, 24h, 0B0h, 10h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0BDh
    db 15h, 12h, 00h, 5Eh, 5Bh, 5Fh, 8Bh, 8Ch, 24h, 9Ch, 10h, 00h, 00h, 5Dh, 64h, 89h
    db 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 0A4h, 10h, 00h, 00h, 0C3h
?d_007e3e60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E4810 size 6
public ?d_007e4810@@YAXXZ
?d_007e4810@@YAXXZ PROC
    db 0FFh, 25h, 44h, 95h, 35h, 01h
?d_007e4810@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E4940 size 7
public ?d_007e4940@@YAXXZ
?d_007e4940@@YAXXZ PROC
    db 8Bh, 41h, 2Ch, 0D9h, 40h, 20h, 0C3h
?d_007e4940@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E4950 size 13
public ?d_007e4950@@YAXXZ
?d_007e4950@@YAXXZ PROC
    db 8Bh, 41h, 2Ch, 8Bh, 4Ch, 24h, 04h, 89h, 48h, 20h, 0C2h, 04h, 00h
?d_007e4950@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E4970 size 16
public ?d_007e4970@@YAXXZ
?d_007e4970@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 0E8h, 0F6h, 0D5h, 09h, 00h, 83h, 0C4h, 04h, 0C2h, 08h, 00h
?d_007e4970@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E4990 size 14
public ?d_007e4990@@YAXXZ
?d_007e4990@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 50h, 0E8h, 56h, 0D5h, 09h, 00h, 59h, 0C2h, 08h, 00h
?d_007e4990@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E49B0 size 6
public ?d_007e49b0@@YAXXZ
?d_007e49b0@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_007e49b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E49C0 size 6
public ?d_007e49c0@@YAXXZ
?d_007e49c0@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C3h
?d_007e49c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E5820 size 21
public ?d_007e5820@@YAXXZ
?d_007e5820@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 6Ah, 00h, 50h, 51h, 0FFh, 15h
    db 0BCh, 8Eh, 35h, 01h, 0C3h
?d_007e5820@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E5900 size 10
public ?d_007e5900@@YAXXZ
?d_007e5900@@YAXXZ PROC
    db 51h, 0FFh, 15h, 0Ch, 8Dh, 35h, 01h, 33h, 0C0h, 0C3h
?d_007e5900@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E5920 size 39
public ?d_007e5920@@YAXXZ
?d_007e5920@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 74h, 05h, 83h, 38h, 2Ch, 74h, 08h, 0B8h, 57h, 00h
    db 07h, 80h, 0C2h, 04h, 00h, 8Dh, 48h, 04h, 0C7h, 40h, 1Ch, 00h, 00h, 00h, 00h, 0E8h
    db 83h, 55h, 85h, 0FFh, 0C2h, 04h, 00h
?d_007e5920@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E7630 size 31
public ?d_007e7630@@YAXXZ
?d_007e7630@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 44h, 37h, 07h, 01h, 74h, 09h
    db 56h, 0E8h, 6Ah, 0A8h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007e7630@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E76B0 size 31
public ?d_007e76b0@@YAXXZ
?d_007e76b0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 58h, 92h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0EAh, 0A7h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007e76b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E76E0 size 83
public ?d_007e76e0@@YAXXZ
?d_007e76e0@@YAXXZ PROC
    db 53h, 8Ah, 5Ch, 24h, 08h, 0F6h, 0C3h, 02h, 56h, 8Bh, 0F1h, 74h, 2Bh, 8Bh, 46h, 0FCh
    db 57h, 68h, 2Ah, 8Dh, 43h, 00h, 8Dh, 7Eh, 0FCh, 50h, 6Ah, 04h, 56h, 0E8h, 74h, 0F6h
    db 20h, 00h, 0F6h, 0C3h, 01h, 74h, 09h, 57h, 0E8h, 0E3h, 0A7h, 09h, 00h, 83h, 0C4h, 04h
    db 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h, 0F6h, 0C3h, 01h, 0C7h, 06h, 58h, 92h, 12h
    db 01h, 74h, 09h, 56h, 0E8h, 87h, 0A7h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 5Bh
    db 0C2h, 04h, 00h
?d_007e76e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E7830 size 13
public ?d_007e7830@@YAXXZ
?d_007e7830@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 89h, 48h, 04h, 89h, 48h, 08h, 0C3h
?d_007e7830@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E78B0 size 23
public ?d_007e78b0@@YAXXZ
?d_007e78b0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 44h, 24h, 08h, 3Bh, 01h, 7Ch, 08h, 8Bh, 4Ch, 24h, 0Ch
    db 3Bh, 01h, 7Eh, 02h, 89h, 01h, 0C3h
?d_007e78b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E8530 size 13
public ?d_007e8530@@YAXXZ
?d_007e8530@@YAXXZ PROC
    db 0A1h, 4Ch, 0FBh, 34h, 01h, 50h, 51h, 0E8h, 0A4h, 0F1h, 85h, 0FFh, 0C3h
?d_007e8530@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E87C0 size 31
public ?d_007e87c0@@YAXXZ
?d_007e87c0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 58h, 93h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0DAh, 96h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007e87c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E9BB0 size 6
public ?d_007e9bb0@@YAXXZ
?d_007e9bb0@@YAXXZ PROC
    db 0FFh, 25h, 30h, 8Fh, 35h, 01h
?d_007e9bb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E9BC0 size 6
public ?d_007e9bc0@@YAXXZ
?d_007e9bc0@@YAXXZ PROC
    db 0FFh, 25h, 0Ch, 8Eh, 35h, 01h
?d_007e9bc0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E9BD0 size 34
public ?d_007e9bd0@@YAXXZ
?d_007e9bd0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 6Ah, 0FFh, 50h, 0FFh, 15h, 64h, 8Fh, 35h, 01h, 85h, 0C0h, 74h, 11h
    db 0E8h, 2Bh, 1Ch, 00h, 00h, 8Bh, 10h, 68h, 0B0h, 9Ah, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h
    db 04h, 0C3h
?d_007e9bd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007E9C00 size 32
public ?d_007e9c00@@YAXXZ
?d_007e9c00@@YAXXZ PROC
    db 8Bh, 41h, 04h, 50h, 0FFh, 15h, 0CCh, 8Eh, 35h, 01h, 85h, 0C0h, 75h, 11h, 0E8h, 0FDh
    db 1Bh, 00h, 00h, 8Bh, 10h, 68h, 0D4h, 9Ah, 12h, 01h, 8Bh, 0C8h, 0FFh, 52h, 04h, 0C3h
?d_007e9c00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EA6D0 size 31
public ?d_007ea6d0@@YAXXZ
?d_007ea6d0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0F4h, 9Ah, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0CAh, 77h, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007ea6d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EB780 size 24
public ?d_007eb780@@YAXXZ
?d_007eb780@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 74h, 0Eh, 8Bh, 54h, 24h, 04h, 8Bh, 49h, 08h, 52h, 51h
    db 0FFh, 0D0h, 83h, 0C4h, 08h, 0C2h, 04h, 00h
?d_007eb780@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EB8B0 size 101
public ?d_007eb8b0@@YAXXZ
?d_007eb8b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 56h, 8Bh, 74h, 24h, 08h, 3Bh, 46h, 10h, 77h, 07h, 8Bh, 4Eh
    db 0Ch, 85h, 0C9h, 75h, 08h, 50h, 8Bh, 0CEh, 0E8h, 0D3h, 0FEh, 0FFh, 0FFh, 8Bh, 4Ch, 24h
    db 10h, 8Bh, 56h, 0Ch, 8Dh, 44h, 24h, 14h, 50h, 51h, 52h, 0E8h, 0CEh, 0B7h, 20h, 00h
    db 8Bh, 4Eh, 0Ch, 8Bh, 06h, 83h, 0C4h, 0Ch, 51h, 8Bh, 0CEh, 0FFh, 50h, 04h, 8Bh, 56h
    db 10h, 8Bh, 46h, 0Ch, 8Ah, 4Ch, 02h, 0FFh, 84h, 0C9h, 5Eh, 74h, 17h, 8Bh, 0Dh, 0A0h
    db 0A5h, 30h, 01h, 8Bh, 11h, 6Ah, 7Bh, 68h, 70h, 9Dh, 12h, 01h, 68h, 48h, 9Dh, 12h
    db 01h, 0FFh, 52h, 0Ch, 0C3h
?d_007eb8b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EB920 size 148
public ?d_007eb920@@YAXXZ
?d_007eb920@@YAXXZ PROC
    db 81h, 0ECh, 84h, 01h, 00h, 00h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 8Bh, 94h, 24h, 88h, 01h
    db 00h, 00h, 56h, 89h, 84h, 24h, 84h, 01h, 00h, 00h, 8Bh, 84h, 24h, 94h, 01h, 00h
    db 00h, 50h, 8Bh, 0F1h, 8Bh, 8Ch, 24h, 94h, 01h, 00h, 00h, 51h, 52h, 8Dh, 44h, 24h
    db 10h, 68h, 0C0h, 9Dh, 12h, 01h, 50h, 0E8h, 86h, 0B4h, 20h, 00h, 8Dh, 44h, 24h, 18h
    db 83h, 0C4h, 14h, 8Dh, 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 3Dh
    db 80h, 01h, 00h, 00h, 72h, 1Ah, 8Bh, 0Dh, 0A0h, 0A5h, 30h, 01h, 8Bh, 11h, 68h, 89h
    db 00h, 00h, 00h, 68h, 70h, 9Dh, 12h, 01h, 68h, 0A4h, 9Dh, 12h, 01h, 0FFh, 52h, 0Ch
    db 8Bh, 06h, 8Dh, 4Ch, 24h, 04h, 51h, 8Bh, 0CEh, 0FFh, 50h, 04h, 8Bh, 8Ch, 24h, 84h
    db 01h, 00h, 00h, 33h, 0C0h, 5Eh, 0E8h, 49h, 0BBh, 20h, 00h, 81h, 0C4h, 84h, 01h, 00h
    db 00h, 0C2h, 0Ch, 00h
?d_007eb920@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EB9C0 size 160
public ?d_007eb9c0@@YAXXZ
?d_007eb9c0@@YAXXZ PROC
    db 81h, 0ECh, 84h, 01h, 00h, 00h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 89h, 84h, 24h, 80h, 01h
    db 00h, 00h, 8Bh, 84h, 24h, 88h, 01h, 00h, 00h, 85h, 0C0h, 56h, 8Bh, 0F1h, 74h, 68h
    db 8Bh, 8Ch, 24h, 98h, 01h, 00h, 00h, 8Bh, 94h, 24h, 94h, 01h, 00h, 00h, 51h, 8Bh
    db 8Ch, 24h, 94h, 01h, 00h, 00h, 52h, 51h, 50h, 8Dh, 54h, 24h, 14h, 68h, 0E8h, 9Dh
    db 12h, 01h, 52h, 0E8h, 0DAh, 0B3h, 20h, 00h, 8Dh, 44h, 24h, 1Ch, 83h, 0C4h, 18h, 8Dh
    db 50h, 01h, 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 3Dh, 80h, 01h, 00h, 00h
    db 72h, 1Ah, 8Bh, 0Dh, 0A0h, 0A5h, 30h, 01h, 8Bh, 01h, 68h, 0A1h, 00h, 00h, 00h, 68h
    db 70h, 9Dh, 12h, 01h, 68h, 0A4h, 9Dh, 12h, 01h, 0FFh, 50h, 0Ch, 8Bh, 16h, 8Dh, 44h
    db 24h, 04h, 50h, 8Bh, 0CEh, 0FFh, 52h, 04h, 8Bh, 8Ch, 24h, 84h, 01h, 00h, 00h, 33h
    db 0C0h, 5Eh, 0E8h, 9Dh, 0BAh, 20h, 00h, 81h, 0C4h, 84h, 01h, 00h, 00h, 0C2h, 10h, 00h
?d_007eb9c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EFF40 size 10
public ?d_007eff40@@YAXXZ
?d_007eff40@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 04h, 0C2h, 04h, 00h
?d_007eff40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EFF50 size 10
public ?d_007eff50@@YAXXZ
?d_007eff50@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 08h, 0C2h, 04h, 00h
?d_007eff50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EFF60 size 28
public ?d_007eff60@@YAXXZ
?d_007eff60@@YAXXZ PROC
    db 8Bh, 41h, 04h, 85h, 0C0h, 75h, 03h, 0C2h, 08h, 00h, 8Bh, 4Ch, 24h, 08h, 8Bh, 54h
    db 24h, 04h, 51h, 52h, 0FFh, 0D0h, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_007eff60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007EFF80 size 29
public ?d_007eff80@@YAXXZ
?d_007eff80@@YAXXZ PROC
    db 8Bh, 41h, 08h, 85h, 0C0h, 74h, 13h, 8Bh, 4Ch, 24h, 04h, 85h, 0C9h, 74h, 0Bh, 8Bh
    db 54h, 24h, 08h, 52h, 51h, 0FFh, 0D0h, 83h, 0C4h, 08h, 0C2h, 08h, 00h
?d_007eff80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F0350 size 31
public ?d_007f0350@@YAXXZ
?d_007f0350@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0DCh, 0A5h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 4Ah, 1Bh, 09h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f0350@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F05A0 size 865
public ?d_007f05a0@@YAXXZ
?d_007f05a0@@YAXXZ PROC
    db 81h, 0ECh, 94h, 00h, 00h, 00h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 56h, 8Bh, 0F1h, 89h, 84h
    db 24h, 94h, 00h, 00h, 00h, 8Bh, 46h, 04h, 57h, 50h, 8Dh, 4Ch, 24h, 10h, 68h, 14h
    db 0A8h, 12h, 01h, 51h, 0E8h, 19h, 68h, 20h, 00h, 8Bh, 0Eh, 8Bh, 0BCh, 24h, 0ACh, 00h
    db 00h, 00h, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 6Ah, 0FFh, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 4Dh
    db 83h, 0FFh, 0FFh, 89h, 47h, 08h, 23h, 0C2h, 83h, 0F8h, 0FFh, 89h, 57h, 0Ch, 75h, 19h
    db 5Fh, 32h, 0C0h, 5Eh, 8Bh, 8Ch, 24h, 90h, 00h, 00h, 00h, 0E8h, 0F4h, 6Eh, 20h, 00h
    db 81h, 0C4h, 94h, 00h, 00h, 00h, 0C2h, 04h, 00h, 8Bh, 4Eh, 04h, 51h, 8Dh, 54h, 24h
    db 10h, 68h, 00h, 0A8h, 12h, 01h, 52h, 0E8h, 0C6h, 67h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h
    db 0Ch, 6Ah, 0FFh, 6Ah, 0FFh, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 01h, 83h, 0FFh, 0FFh, 89h
    db 57h, 14h, 89h, 47h, 10h, 8Bh, 4Eh, 04h, 51h, 8Dh, 54h, 24h, 10h, 68h, 0ECh, 0A7h
    db 12h, 01h, 52h, 0E8h, 9Ah, 67h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 68h
    db 0E0h, 0A7h, 12h, 01h, 0E8h, 0A7h, 82h, 0FFh, 0FFh, 89h, 47h, 18h, 8Bh, 46h, 04h, 50h
    db 8Dh, 4Ch, 24h, 10h, 68h, 0D0h, 0A7h, 12h, 01h, 51h, 0E8h, 73h, 67h, 20h, 00h, 8Bh
    db 0Eh, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 8Dh, 54h, 24h, 10h, 52h, 0E8h, 80h, 82h, 0FFh, 0FFh
    db 89h, 47h, 20h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 10h, 68h, 0BCh, 0A7h, 12h, 01h
    db 51h, 0E8h, 4Ch, 67h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 8Dh, 54h, 24h
    db 10h, 52h, 0E8h, 59h, 82h, 0FFh, 0FFh, 89h, 47h, 24h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch
    db 24h, 10h, 68h, 0ACh, 0A7h, 12h, 01h, 51h, 0E8h, 25h, 67h, 20h, 00h, 8Bh, 0Eh, 83h
    db 0C4h, 0Ch, 6Ah, 0FFh, 6Ah, 0FFh, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 60h, 82h, 0FFh, 0FFh
    db 89h, 47h, 28h, 89h, 57h, 2Ch, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 10h, 68h, 98h
    db 0A7h, 12h, 01h, 51h, 0C6h, 44h, 24h, 58h, 00h, 0E8h, 0F4h, 66h, 20h, 00h, 83h, 0C4h
    db 0Ch, 6Ah, 20h, 8Dh, 54h, 24h, 50h, 52h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0Eh, 0E8h
    db 7Ch, 83h, 0FFh, 0FFh, 8Dh, 4Ch, 24h, 4Ch, 51h, 8Dh, 4Fh, 30h, 0E8h, 1Fh, 0EEh, 00h
    db 00h, 8Bh, 56h, 04h, 52h, 8Dh, 44h, 24h, 10h, 68h, 84h, 0A7h, 12h, 01h, 50h, 0E8h
    db 0BEh, 66h, 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 20h, 8Dh, 4Ch, 24h, 50h, 51h, 8Bh, 0Eh
    db 68h, 78h, 0A7h, 12h, 01h, 0E8h, 46h, 83h, 0FFh, 0FFh, 8Dh, 54h, 24h, 4Ch, 52h, 8Dh
    db 4Fh, 3Ch, 0E8h, 0E9h, 0EDh, 00h, 00h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 10h, 68h
    db 64h, 0A7h, 12h, 01h, 51h, 0E8h, 88h, 66h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah
    db 20h, 8Dh, 57h, 48h, 52h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 11h, 83h, 0FFh, 0FFh, 8Bh
    db 4Eh, 04h, 51h, 8Dh, 54h, 24h, 10h, 68h, 54h, 0A7h, 12h, 01h, 52h, 0E8h, 60h, 66h
    db 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 20h, 8Dh, 47h, 68h, 50h, 8Dh, 4Ch, 24h, 14h, 51h
    db 8Bh, 0Eh, 0E8h, 0E9h, 82h, 0FFh, 0FFh, 8Bh, 56h, 04h, 52h, 8Dh, 44h, 24h, 10h, 68h
    db 3Ch, 0A7h, 12h, 01h, 50h, 0E8h, 38h, 66h, 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 0FFh, 8Dh
    db 4Ch, 24h, 10h, 51h, 8Bh, 0Eh, 0E8h, 45h, 81h, 0FFh, 0FFh, 89h, 87h, 88h, 00h, 00h
    db 00h, 8Bh, 56h, 04h, 52h, 8Dh, 44h, 24h, 10h, 68h, 2Ch, 0A7h, 12h, 01h, 50h, 0E8h
    db 0Eh, 66h, 20h, 00h, 83h, 0C4h, 0Ch, 6Ah, 40h, 8Dh, 4Ch, 24h, 5Ch, 51h, 8Bh, 0Eh
    db 8Dh, 54h, 24h, 14h, 52h, 0E8h, 96h, 82h, 0FFh, 0FFh, 8Dh, 44h, 24h, 08h, 50h, 68h
    db 4Ch, 2Fh, 08h, 01h, 8Dh, 4Ch, 24h, 60h, 51h, 0E8h, 0A8h, 67h, 20h, 00h, 8Bh, 54h
    db 24h, 14h, 89h, 97h, 8Ch, 00h, 00h, 00h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 1Ch
    db 68h, 14h, 0A7h, 12h, 01h, 51h, 0E8h, 0C7h, 65h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 18h
    db 6Ah, 0FFh, 8Dh, 54h, 24h, 10h, 52h, 0E8h, 0D4h, 80h, 0FFh, 0FFh, 89h, 87h, 90h, 00h
    db 00h, 00h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 10h, 68h, 00h, 0A7h, 12h, 01h, 51h
    db 0E8h, 9Dh, 65h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah, 20h, 8Dh, 97h, 94h, 00h
    db 00h, 00h, 52h, 8Dh, 44h, 24h, 14h, 50h, 0E8h, 23h, 82h, 0FFh, 0FFh, 8Bh, 4Eh, 04h
    db 51h, 8Dh, 54h, 24h, 10h, 68h, 0E4h, 0A6h, 12h, 01h, 52h, 0E8h, 72h, 65h, 20h, 00h
    db 83h, 0C4h, 0Ch, 6Ah, 50h, 8Dh, 87h, 0B4h, 00h, 00h, 00h, 50h, 8Dh, 4Ch, 24h, 14h
    db 51h, 8Bh, 0Eh, 0E8h, 0F8h, 81h, 0FFh, 0FFh, 8Bh, 56h, 04h, 52h, 8Dh, 44h, 24h, 10h
    db 68h, 0C8h, 0A6h, 12h, 01h, 50h, 0E8h, 47h, 65h, 20h, 00h, 83h, 0C4h, 0Ch, 68h, 0FFh
    db 00h, 00h, 00h, 8Dh, 8Fh, 04h, 01h, 00h, 00h, 51h, 8Bh, 0Eh, 8Dh, 54h, 24h, 14h
    db 52h, 0E8h, 0CAh, 81h, 0FFh, 0FFh, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch, 24h, 10h, 68h, 0B8h
    db 0A6h, 12h, 01h, 51h, 0E8h, 19h, 65h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah, 20h
    db 81h, 0C7h, 03h, 02h, 00h, 00h, 57h, 8Dh, 54h, 24h, 14h, 52h, 0E8h, 9Fh, 81h, 0FFh
    db 0FFh, 8Bh, 46h, 04h, 8Bh, 8Ch, 24h, 98h, 00h, 00h, 00h, 40h, 89h, 46h, 04h, 5Fh
    db 0B0h, 01h, 5Eh, 0E8h, 0FCh, 6Bh, 20h, 00h, 81h, 0C4h, 94h, 00h, 00h, 00h, 0C2h, 04h
    db 00h
?d_007f05a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F1150 size 15
public ?d_007f1150@@YAXXZ
?d_007f1150@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0C1h, 04h, 0FFh, 10h, 8Bh, 0C8h, 0E9h, 11h, 8Eh, 0FFh, 0FFh
?d_007f1150@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F16F0 size 105
public ?d_007f16f0@@YAXXZ
?d_007f16f0@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0Ch, 0A6h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 0BAh, 73h, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 62h, 6Fh, 6Ch, 62h, 0E8h, 0F6h, 72h, 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 8Bh, 4Ch
    db 24h, 14h, 50h, 51h, 68h, 5Ch, 0A6h, 12h, 01h, 8Bh, 0CEh, 0E8h, 60h, 77h, 0FFh, 0FFh
    db 8Bh, 54h, 24h, 20h, 8Bh, 44h, 24h, 1Ch, 52h, 50h, 56h, 8Bh, 0CFh, 0E8h, 0BEh, 0FCh
    db 0FFh, 0FFh, 8Bh, 4Ch, 24h, 24h, 51h, 68h, 48h, 0A8h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0BDh
    db 72h, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 18h, 00h
?d_007f16f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F1760 size 154
public ?d_007f1760@@YAXXZ
?d_007f1760@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0DCh, 0A5h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 4Ah, 73h, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 62h, 6Fh, 6Ch, 62h, 0E8h, 86h, 72h, 0FFh, 0FFh, 8Bh, 44h, 24h, 28h, 8Bh, 4Ch
    db 24h, 24h, 50h, 51h, 56h, 8Bh, 0CFh, 0E8h, 64h, 00h, 00h, 00h, 8Bh, 44h, 24h, 14h
    db 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 68h, 0A9h, 12h, 01h, 8Bh, 0CEh, 0E8h, 1Eh, 71h
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 5Ch, 0A9h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 08h, 71h, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 83h, 0F8h, 0FFh, 7Eh
    db 0Dh, 50h, 68h, 50h, 0A9h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0F2h, 70h, 0FFh, 0FFh, 8Bh, 44h
    db 24h, 20h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 44h, 0A9h, 12h, 01h, 8Bh, 0CEh, 0E8h
    db 0DCh, 70h, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 1Ch, 00h
?d_007f1760@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F1A90 size 171
public ?d_007f1a90@@YAXXZ
?d_007f1a90@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 18h, 0A6h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 1Ah, 70h, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 62h, 6Fh, 6Ch, 62h, 0E8h, 56h, 6Fh, 0FFh, 0FFh, 8Bh, 44h, 24h, 28h, 8Bh, 5Ch
    db 24h, 1Ch, 50h, 53h, 56h, 8Bh, 0CFh, 0E8h, 34h, 0FDh, 0FFh, 0FFh, 8Bh, 44h, 24h, 14h
    db 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 68h, 0A9h, 12h, 01h, 8Bh, 0CEh, 0E8h, 0EEh, 6Dh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 5Ch, 0A9h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 0D8h, 6Dh, 0FFh, 0FFh, 85h, 0DBh, 7Eh, 0Dh, 53h, 68h, 88h, 0AAh
    db 12h, 01h, 8Bh, 0CEh, 0E8h, 0C7h, 6Dh, 0FFh, 0FFh, 8Bh, 44h, 24h, 20h, 83h, 0F8h, 0FFh
    db 7Eh, 0Dh, 50h, 68h, 7Ch, 0AAh, 12h, 01h, 8Bh, 0CEh, 0E8h, 0B1h, 6Dh, 0FFh, 0FFh, 8Bh
    db 44h, 24h, 24h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 70h, 0AAh, 12h, 01h, 8Bh, 0CEh
    db 0E8h, 9Bh, 6Dh, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 1Ch, 00h
?d_007f1a90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F1B40 size 172
public ?d_007f1b40@@YAXXZ
?d_007f1b40@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0B8h, 0A5h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 6Ah, 6Fh, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 62h, 6Fh, 6Ch, 62h, 0E8h, 0A6h, 6Eh, 0FFh, 0FFh, 8Bh, 44h, 24h, 28h, 8Bh, 5Ch
    db 24h, 1Ch, 50h, 53h, 56h, 8Bh, 0CFh, 0E8h, 84h, 0FCh, 0FFh, 0FFh, 8Bh, 44h, 24h, 14h
    db 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 50h, 0A9h, 12h, 01h, 8Bh, 0CEh, 0E8h, 3Eh, 6Dh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 18h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 44h, 0A9h, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 28h, 6Dh, 0FFh, 0FFh, 83h, 0FBh, 0FFh, 7Eh, 0Dh, 53h, 68h, 88h
    db 0AAh, 12h, 01h, 8Bh, 0CEh, 0E8h, 16h, 6Dh, 0FFh, 0FFh, 8Bh, 44h, 24h, 20h, 83h, 0F8h
    db 0FFh, 7Eh, 0Dh, 50h, 68h, 7Ch, 0AAh, 12h, 01h, 8Bh, 0CEh, 0E8h, 00h, 6Dh, 0FFh, 0FFh
    db 8Bh, 44h, 24h, 24h, 83h, 0F8h, 0FFh, 7Eh, 0Dh, 50h, 68h, 70h, 0AAh, 12h, 01h, 8Bh
    db 0CEh, 0E8h, 0EAh, 6Ch, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 1Ch, 00h
?d_007f1b40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F1F60 size 174
public ?d_007f1f60@@YAXXZ
?d_007f1f60@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 3Ch, 0A6h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 4Ah, 6Bh, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 6Bh, 62h, 64h, 66h, 0E8h, 86h, 6Ah, 0FFh, 0FFh, 8Bh, 44h, 24h, 1Ch, 8Bh, 4Ch
    db 24h, 18h, 50h, 51h, 56h, 8Bh, 0CFh, 0E8h, 74h, 00h, 00h, 00h, 8Bh, 54h, 24h, 14h
    db 52h, 68h, 0E8h, 0ABh, 12h, 01h, 8Bh, 0CEh, 0E8h, 23h, 69h, 0FFh, 0FFh, 8Bh, 44h, 24h
    db 24h, 8Bh, 4Ch, 24h, 20h, 50h, 51h, 68h, 0D4h, 0ABh, 12h, 01h, 8Bh, 0CEh, 0E8h, 0CDh
    db 6Eh, 0FFh, 0FFh, 8Bh, 54h, 24h, 28h, 52h, 68h, 0CCh, 0ABh, 12h, 01h, 8Bh, 0CEh, 0E8h
    db 3Ch, 6Ah, 0FFh, 0FFh, 8Bh, 44h, 24h, 2Ch, 50h, 68h, 0BCh, 0ABh, 12h, 01h, 8Bh, 0CEh
    db 0E8h, 0EBh, 68h, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 34h, 8Bh, 54h, 24h, 30h, 51h, 52h, 56h
    db 8Bh, 0CFh, 0E8h, 89h, 00h, 00h, 00h, 8Bh, 44h, 24h, 38h, 50h, 68h, 0A8h, 0ABh, 12h
    db 01h, 8Bh, 0CEh, 0E8h, 08h, 6Ah, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 2Ch, 00h
?d_007f1f60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F2350 size 333
public ?d_007f2350@@YAXXZ
?d_007f2350@@YAXXZ PROC
    db 81h, 0ECh, 88h, 00h, 00h, 00h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 53h, 55h, 56h, 57h, 8Bh
    db 0BCh, 24h, 9Ch, 00h, 00h, 00h, 89h, 84h, 24h, 94h, 00h, 00h, 00h, 33h, 0C0h, 8Bh
    db 0F1h, 8Dh, 6Fh, 10h, 8Dh, 5Fh, 54h, 0C6h, 45h, 00h, 00h, 0C6h, 47h, 30h, 00h, 89h
    db 47h, 50h, 88h, 03h, 89h, 87h, 54h, 01h, 00h, 00h, 8Bh, 46h, 04h, 50h, 8Dh, 4Ch
    db 24h, 18h, 68h, 0D0h, 0ACh, 12h, 01h, 51h, 0E8h, 45h, 4Ah, 20h, 00h, 8Bh, 0Eh, 83h
    db 0C4h, 0Ch, 6Ah, 40h, 8Dh, 54h, 24h, 58h, 52h, 8Dh, 44h, 24h, 1Ch, 50h, 0E8h, 0CDh
    db 66h, 0FFh, 0FFh, 84h, 0C0h, 0Fh, 84h, 0C9h, 00h, 00h, 00h, 8Dh, 4Ch, 24h, 10h, 51h
    db 8Dh, 54h, 24h, 58h, 68h, 4Ch, 2Fh, 08h, 01h, 52h, 0E8h, 0D7h, 4Bh, 20h, 00h, 8Bh
    db 44h, 24h, 1Ch, 89h, 47h, 50h, 8Bh, 4Eh, 04h, 51h, 8Dh, 54h, 24h, 24h, 68h, 0C0h
    db 0ACh, 12h, 01h, 52h, 0E8h, 0F9h, 49h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 18h, 6Ah, 00h
    db 8Dh, 44h, 24h, 18h, 50h, 0E8h, 06h, 65h, 0FFh, 0FFh, 89h, 87h, 54h, 01h, 00h, 00h
    db 8Bh, 4Eh, 04h, 51h, 8Dh, 54h, 24h, 18h, 68h, 00h, 0ADh, 12h, 01h, 52h, 0E8h, 0CFh
    db 49h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 6Ah, 00h, 6Ah, 00h, 8Dh, 44h, 24h, 1Ch
    db 50h, 0E8h, 0Ah, 65h, 0FFh, 0FFh, 89h, 57h, 04h, 89h, 07h, 8Bh, 4Eh, 04h, 51h, 8Dh
    db 54h, 24h, 18h, 68h, 0F0h, 0ACh, 12h, 01h, 52h, 0E8h, 0A4h, 49h, 20h, 00h, 8Bh, 0Eh
    db 83h, 0C4h, 0Ch, 6Ah, 20h, 55h, 8Dh, 44h, 24h, 1Ch, 50h, 0E8h, 30h, 66h, 0FFh, 0FFh
    db 8Bh, 4Eh, 04h, 51h, 8Dh, 54h, 24h, 18h, 68h, 0B0h, 0ACh, 12h, 01h, 52h, 0E8h, 7Fh
    db 49h, 20h, 00h, 8Bh, 0Eh, 83h, 0C4h, 0Ch, 68h, 0FFh, 00h, 00h, 00h, 53h, 8Dh, 44h
    db 24h, 1Ch, 50h, 0E8h, 08h, 66h, 0FFh, 0FFh, 0FFh, 46h, 04h, 0C7h, 46h, 08h, 00h, 00h
    db 00h, 00h, 0B0h, 01h, 8Bh, 8Ch, 24h, 94h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh, 0E8h
    db 60h, 50h, 20h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_007f2350@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F29F0 size 81
public ?d_007f29f0@@YAXXZ
?d_007f29f0@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 6Ch, 0A6h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 0BAh, 60h, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 6Bh, 6Eh, 61h, 72h, 0E8h, 0F6h, 5Fh, 0FFh, 0FFh, 8Bh, 44h, 24h, 24h, 8Bh, 4Ch
    db 24h, 20h, 8Bh, 54h, 24h, 1Ch, 50h, 8Bh, 44h, 24h, 1Ch, 51h, 8Bh, 4Ch, 24h, 1Ch
    db 52h, 50h, 51h, 56h, 8Bh, 0CFh, 0E8h, 15h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 0C2h, 18h
    db 00h
?d_007f29f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F2B10 size 81
public ?d_007f2b10@@YAXXZ
?d_007f2b10@@YAXXZ PROC
    db 53h, 8Bh, 1Dh, 0C0h, 0A6h, 30h, 01h, 56h, 8Bh, 74h, 24h, 0Ch, 57h, 8Bh, 0F9h, 8Bh
    db 0CEh, 0E8h, 9Ah, 5Fh, 0FFh, 0FFh, 53h, 68h, 0ACh, 98h, 12h, 01h, 8Bh, 0CEh, 0C7h, 46h
    db 1Ch, 6Bh, 6Eh, 61h, 72h, 0E8h, 0D6h, 5Eh, 0FFh, 0FFh, 8Bh, 44h, 24h, 24h, 8Bh, 4Ch
    db 24h, 20h, 8Bh, 54h, 24h, 1Ch, 50h, 8Bh, 44h, 24h, 1Ch, 51h, 8Bh, 4Ch, 24h, 1Ch
    db 52h, 50h, 51h, 56h, 8Bh, 0CFh, 0E8h, 0F5h, 0FEh, 0FFh, 0FFh, 5Fh, 5Eh, 5Bh, 0C2h, 18h
    db 00h
?d_007f2b10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F3FF0 size 15
public ?d_007f3ff0@@YAXXZ
?d_007f3ff0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0C1h, 04h, 0FFh, 10h, 8Bh, 0C8h, 0E9h, 71h, 5Fh, 0FFh, 0FFh
?d_007f3ff0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4370 size 15
public ?d_007f4370@@YAXXZ
?d_007f4370@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0C1h, 04h, 0FFh, 10h, 8Bh, 0C8h, 0E9h, 0F1h, 5Bh, 0FFh, 0FFh
?d_007f4370@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4440 size 215
public ?d_007f4440@@YAXXZ
?d_007f4440@@YAXXZ PROC
    db 81h, 0ECh, 38h, 01h, 00h, 00h, 0A1h, 0B0h, 0BDh, 2Dh, 01h, 89h, 84h, 24h, 34h, 01h
    db 00h, 00h, 83h, 0BCh, 24h, 3Ch, 01h, 00h, 00h, 03h, 57h, 8Bh, 0F9h, 0Fh, 85h, 9Eh
    db 00h, 00h, 00h, 53h, 56h, 68h, 00h, 01h, 00h, 00h, 8Dh, 44h, 24h, 44h, 50h, 8Dh
    db 4Ch, 24h, 14h, 0E8h, 0D8h, 43h, 0FFh, 0FFh, 8Bh, 57h, 0F8h, 8Dh, 4Fh, 0F8h, 0FFh, 12h
    db 8Bh, 0F0h, 8Bh, 0CEh, 0E8h, 0D7h, 61h, 0FFh, 0FFh, 80h, 38h, 00h, 75h, 04h, 33h, 0C0h
    db 0EBh, 07h, 8Bh, 0CEh, 0E8h, 0C7h, 61h, 0FFh, 0FFh, 8Bh, 5Fh, 0F4h, 83h, 0C7h, 0F4h, 50h
    db 8Bh, 0CEh, 0E8h, 0C9h, 61h, 0FFh, 0FFh, 50h, 0A1h, 18h, 3Ah, 2Ch, 01h, 50h, 8Bh, 0CEh
    db 0E8h, 0FBh, 61h, 0FFh, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 0E3h, 61h, 0FFh, 0FFh, 50h, 8Bh, 0CEh
    db 0E8h, 0CBh, 61h, 0FFh, 0FFh, 50h, 8Bh, 0CEh, 0E8h, 83h, 61h, 0FFh, 0FFh, 50h, 8Dh, 4Ch
    db 24h, 28h, 51h, 8Bh, 0CFh, 0FFh, 53h, 10h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 04h, 8Bh
    db 10h, 68h, 10h, 27h, 00h, 00h, 57h, 68h, 20h, 45h, 0BFh, 00h, 8Dh, 4Ch, 24h, 18h
    db 51h, 8Bh, 0C8h, 0FFh, 52h, 08h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0C1h, 41h, 0FFh, 0FFh, 5Eh
    db 5Bh, 8Bh, 8Ch, 24h, 38h, 01h, 00h, 00h, 5Fh, 0E8h, 0E6h, 2Fh, 20h, 00h, 81h, 0C4h
    db 38h, 01h, 00h, 00h, 0C2h, 0Ch, 00h
?d_007f4440@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F48D0 size 31
public ?d_007f48d0@@YAXXZ
?d_007f48d0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0E4h, 0B3h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0CAh, 0D5h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f48d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4930 size 31
public ?d_007f4930@@YAXXZ
?d_007f4930@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0ACh, 0B3h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 6Ah, 0D5h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f4930@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4980 size 51
public ?d_007f4980@@YAXXZ
?d_007f4980@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 85h, 0C0h, 7Ch, 10h, 83h, 0F8h, 02h, 7Dh, 0Bh, 8Bh, 54h, 24h
    db 04h, 89h, 54h, 81h, 08h, 0C2h, 08h, 00h, 0E8h, 73h, 6Eh, 0FFh, 0FFh, 8Bh, 10h, 6Ah
    db 4Ch, 68h, 18h, 0B4h, 12h, 01h, 68h, 0A0h, 0C2h, 11h, 01h, 8Bh, 0C8h, 0FFh, 52h, 0Ch
    db 0C2h, 08h, 00h
?d_007f4980@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F49C0 size 15
public ?d_007f49c0@@YAXXZ
?d_007f49c0@@YAXXZ PROC
    db 8Bh, 54h, 24h, 04h, 8Bh, 01h, 6Ah, 00h, 52h, 0FFh, 50h, 10h, 0C2h, 04h, 00h
?d_007f49c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4B60 size 10
public ?d_007f4b60@@YAXXZ
?d_007f4b60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 10h, 0C2h, 04h, 00h
?d_007f4b60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4B70 size 11
public ?d_007f4b70@@YAXXZ
?d_007f4b70@@YAXXZ PROC
    db 85h, 0C9h, 74h, 04h, 8Dh, 41h, 04h, 0C3h, 33h, 0C0h, 0C3h
?d_007f4b70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4B80 size 18
public ?d_007f4b80@@YAXXZ
?d_007f4b80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 08h, 2Bh, 41h, 10h, 0F7h, 0D8h, 1Bh, 0C0h, 40h, 0C2h
    db 0Ch, 00h
?d_007f4b80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4BA0 size 8
public ?d_007f4ba0@@YAXXZ
?d_007f4ba0@@YAXXZ PROC
    db 83h, 0E9h, 04h, 0E9h, 58h, 01h, 00h, 00h
?d_007f4ba0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F4EC0 size 27
public ?d_007f4ec0@@YAXXZ
?d_007f4ec0@@YAXXZ PROC
    db 56h, 6Ah, 00h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 0Ch, 68h, 0E8h, 0B4h, 12h, 01h, 0E8h, 2Dh
    db 3Ah, 0FFh, 0FFh, 89h, 06h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f4ec0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F52F0 size 55
public ?d_007f52f0@@YAXXZ
?d_007f52f0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 32h, 69h, 00h, 00h, 6Ah, 00h
    db 68h, 80h, 0B5h, 12h, 01h, 8Bh, 0CFh, 0E8h, 0F4h, 35h, 0FFh, 0FFh, 6Ah, 00h, 68h, 78h
    db 0B5h, 12h, 01h, 8Bh, 0CFh, 89h, 46h, 08h, 0E8h, 0E3h, 35h, 0FFh, 0FFh, 89h, 46h, 0Ch
    db 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f52f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5350 size 59
public ?d_007f5350@@YAXXZ
?d_007f5350@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 57h, 8Bh, 0F1h, 0E8h, 0D2h, 68h, 00h, 00h, 6Ah, 00h
    db 68h, 90h, 0B4h, 12h, 01h, 8Bh, 0CFh, 0E8h, 94h, 35h, 0FFh, 0FFh, 89h, 46h, 08h, 68h
    db 00h, 01h, 00h, 00h, 8Dh, 46h, 0Ch, 50h, 68h, 88h, 0B5h, 12h, 01h, 8Bh, 0CFh, 0E8h
    db 0FCh, 36h, 0FFh, 0FFh, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f5350@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5390 size 27
public ?d_007f5390@@YAXXZ
?d_007f5390@@YAXXZ PROC
    db 56h, 6Ah, 00h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 0Ch, 68h, 54h, 0B5h, 12h, 01h, 0E8h, 5Dh
    db 35h, 0FFh, 0FFh, 89h, 06h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f5390@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F53C0 size 27
public ?d_007f53c0@@YAXXZ
?d_007f53c0@@YAXXZ PROC
    db 56h, 6Ah, 00h, 8Bh, 0F1h, 8Bh, 4Ch, 24h, 0Ch, 68h, 54h, 0B5h, 12h, 01h, 0E8h, 2Dh
    db 35h, 0FFh, 0FFh, 89h, 06h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f53c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5630 size 12
public ?d_007f5630@@YAXXZ
?d_007f5630@@YAXXZ PROC
    db 8Bh, 49h, 24h, 8Bh, 44h, 24h, 04h, 89h, 08h, 0C2h, 04h, 00h
?d_007f5630@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5670 size 12
public ?d_007f5670@@YAXXZ
?d_007f5670@@YAXXZ PROC
    db 8Bh, 49h, 18h, 8Bh, 44h, 24h, 04h, 89h, 08h, 0C2h, 04h, 00h
?d_007f5670@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F56F0 size 10
public ?d_007f56f0@@YAXXZ
?d_007f56f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 1Ch, 0C2h, 04h, 00h
?d_007f56f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5700 size 17
public ?d_007f5700@@YAXXZ
?d_007f5700@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 28h, 0C7h, 41h, 2Ch, 00h, 00h, 00h, 00h, 0C2h, 04h
    db 00h
?d_007f5700@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F57C0 size 22
public ?d_007f57c0@@YAXXZ
?d_007f57c0@@YAXXZ PROC
    db 8Ah, 41h, 34h, 84h, 0C0h, 74h, 0Ch, 83h, 79h, 30h, 05h, 7Ch, 06h, 0B8h, 01h, 00h
    db 00h, 00h, 0C3h, 33h, 0C0h, 0C3h
?d_007f57c0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F57E0 size 22
public ?d_007f57e0@@YAXXZ
?d_007f57e0@@YAXXZ PROC
    db 8Ah, 41h, 35h, 84h, 0C0h, 74h, 0Ch, 83h, 79h, 30h, 03h, 7Ch, 06h, 0B8h, 01h, 00h
    db 00h, 00h, 0C3h, 33h, 0C0h, 0C3h
?d_007f57e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5800 size 22
public ?d_007f5800@@YAXXZ
?d_007f5800@@YAXXZ PROC
    db 8Ah, 41h, 35h, 84h, 0C0h, 74h, 0Ch, 83h, 79h, 30h, 05h, 7Ch, 06h, 0B8h, 01h, 00h
    db 00h, 00h, 0C3h, 33h, 0C0h, 0C3h
?d_007f5800@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5B00 size 58
public ?d_007f5b00@@YAXXZ
?d_007f5b00@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 8Bh, 0CFh, 0E8h, 91h, 2Dh, 0FFh, 0FFh, 84h
    db 0C0h, 74h, 15h, 8Bh, 0CFh, 0E8h, 96h, 2Dh, 0FFh, 0FFh, 8Bh, 4Eh, 1Ch, 8Bh, 11h, 5Fh
    db 5Eh, 89h, 44h, 24h, 04h, 0FFh, 62h, 48h, 8Bh, 4Eh, 1Ch, 8Bh, 01h, 5Fh, 5Eh, 0C7h
    db 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0FFh, 60h, 48h
?d_007f5b00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5B80 size 168
public ?d_007f5b80@@YAXXZ
?d_007f5b80@@YAXXZ PROC
    db 8Ah, 44h, 24h, 20h, 83h, 0ECh, 34h, 56h, 8Bh, 0F1h, 57h, 68h, 00h, 04h, 00h, 00h
    db 8Dh, 8Eh, 0DCh, 02h, 00h, 00h, 51h, 8Dh, 4Ch, 24h, 10h, 88h, 46h, 36h, 0E8h, 0ADh
    db 2Ch, 0FFh, 0FFh, 8Bh, 46h, 2Ch, 85h, 0C0h, 75h, 03h, 8Bh, 46h, 28h, 8Bh, 7Ch, 24h
    db 70h, 57h, 8Bh, 7Ch, 24h, 70h, 57h, 8Bh, 7Ch, 24h, 70h, 57h, 8Bh, 7Ch, 24h, 70h
    db 57h, 8Bh, 7Ch, 24h, 70h, 57h, 8Bh, 7Ch, 24h, 68h, 57h, 8Bh, 7Ch, 24h, 68h, 57h
    db 8Bh, 7Ch, 24h, 68h, 8Bh, 4Eh, 10h, 57h, 8Bh, 7Ch, 24h, 78h, 8Bh, 11h, 57h, 50h
    db 8Bh, 44h, 24h, 70h, 50h, 33h, 0C0h, 8Ah, 46h, 36h, 50h, 8Bh, 44h, 24h, 74h, 50h
    db 8Bh, 44h, 24h, 74h, 50h, 8Dh, 44h, 24h, 40h, 50h, 0FFh, 52h, 24h, 8Bh, 86h, 0DCh
    db 06h, 00h, 00h, 8Bh, 4Eh, 14h, 8Bh, 11h, 50h, 56h, 68h, 70h, 5Ah, 0BFh, 00h, 8Dh
    db 44h, 24h, 14h, 50h, 0FFh, 52h, 08h, 8Dh, 4Ch, 24h, 08h, 0E8h, 0A0h, 2Ah, 0FFh, 0FFh
    db 5Fh, 5Eh, 83h, 0C4h, 34h, 0C2h, 34h, 00h
?d_007f5b80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F5FB0 size 36
public ?d_007f5fb0@@YAXXZ
?d_007f5fb0@@YAXXZ PROC
    db 8Bh, 11h, 56h, 8Bh, 74h, 24h, 14h, 56h, 8Bh, 74h, 24h, 14h, 33h, 0C0h, 56h, 50h
    db 8Bh, 44h, 24h, 18h, 50h, 8Bh, 44h, 24h, 18h, 50h, 0FFh, 92h, 80h, 00h, 00h, 00h
    db 5Eh, 0C2h, 10h, 00h
?d_007f5fb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F6250 size 7
public ?d_007f6250@@YAXXZ
?d_007f6250@@YAXXZ PROC
    db 8Bh, 81h, 0D8h, 02h, 00h, 00h, 0C3h
?d_007f6250@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F63D0 size 25
public ?d_007f63d0@@YAXXZ
?d_007f63d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 75h, 0Eh, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 74h, 06h
    db 8Bh, 40h, 0Ch, 89h, 41h, 24h, 0C2h, 0Ch, 00h
?d_007f63d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F6E40 size 31
public ?d_007f6e40@@YAXXZ
?d_007f6e40@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 98h, 0B5h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 5Ah, 0B0h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f6e40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F70F0 size 25
public ?d_007f70f0@@YAXXZ
?d_007f70f0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 3Bh, 41h, 3Ch, 7Ch, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 51h
    db 38h, 6Bh, 0C0h, 1Ch, 03h, 0C2h, 0C2h, 04h, 00h
?d_007f70f0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F7110 size 36
public ?d_007f7110@@YAXXZ
?d_007f7110@@YAXXZ PROC
    db 8Bh, 41h, 38h, 8Bh, 49h, 3Ch, 6Bh, 0C9h, 1Ch, 03h, 0C8h, 3Bh, 0C1h, 73h, 10h, 8Bh
    db 54h, 24h, 04h, 39h, 50h, 08h, 74h, 09h, 83h, 0C0h, 1Ch, 3Bh, 0C1h, 72h, 0F4h, 33h
    db 0C0h, 0C2h, 04h, 00h
?d_007f7110@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F7160 size 25
public ?d_007f7160@@YAXXZ
?d_007f7160@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 3Bh, 41h, 4Ch, 7Ch, 05h, 33h, 0C0h, 0C2h, 04h, 00h, 8Bh, 51h
    db 48h, 0C1h, 0E0h, 06h, 03h, 0C2h, 0C2h, 04h, 00h
?d_007f7160@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F7180 size 36
public ?d_007f7180@@YAXXZ
?d_007f7180@@YAXXZ PROC
    db 8Bh, 41h, 48h, 8Bh, 49h, 4Ch, 0C1h, 0E1h, 06h, 03h, 0C8h, 3Bh, 0C1h, 73h, 10h, 8Bh
    db 54h, 24h, 04h, 39h, 50h, 08h, 74h, 09h, 83h, 0C0h, 40h, 3Bh, 0C1h, 72h, 0F4h, 33h
    db 0C0h, 0C2h, 04h, 00h
?d_007f7180@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F7CF0 size 167
_TEXT ENDS
_TEXT$d00bf7cf0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BF7CF0 size 167
public ?d_007f7cf0@@YAXXZ
?d_007f7cf0@@YAXXZ PROC
    db 051h, 053h, 056h, 08Bh, 074h, 024h, 014h, 085h, 0F6h, 08Bh, 0D9h, 00Fh, 084h, 090h, 000h, 000h
    db 000h, 083h, 07Eh, 008h, 004h, 00Fh, 085h, 086h, 000h, 000h, 000h, 055h, 08Bh, 06Ch, 024h, 014h
    db 085h, 0EDh, 074h, 068h, 057h
    call ?Rva007EB810Get@@YAPAURva007EB810Diag@@XZ
    db 08Bh, 008h, 055h, 068h
    dd g_Va0112B7E0
    db 06Ah, 000h, 050h, 0FFh, 051h, 008h, 08Bh, 016h, 083h, 0C4h, 010h, 08Dh, 044h, 024h, 018h, 050h
    db 08Bh, 0CEh, 08Dh, 07Bh, 0F8h, 0FFh, 052h, 004h, 08Bh, 016h, 089h, 044h, 024h, 01Ch, 08Dh, 044h
    db 024h, 010h, 050h, 08Bh, 0CEh, 0FFh, 052h, 008h, 08Bh, 04Ch, 024h, 01Ch, 08Bh, 009h, 08Bh, 000h
    db 08Bh, 017h, 051h, 050h, 08Bh, 0CFh, 0FFh, 052h, 05Ch, 0C7h, 046h, 008h, 000h, 000h, 000h, 000h
    db 08Bh, 04Bh, 014h, 08Bh, 011h, 055h, 056h, 0FFh, 052h, 02Ch, 056h, 08Bh, 0CFh
    call ?bfmeGoVFD@@YGXPAUBfmeThingVFD@@@Z
    db 05Fh, 05Dh, 05Eh, 05Bh, 059h, 0C2h, 008h, 000h, 0C7h, 046h, 008h, 005h, 000h, 000h, 000h, 08Bh
    db 05Bh, 014h, 08Bh, 003h, 06Ah, 000h, 056h, 08Bh, 0CBh, 0FFh, 050h, 02Ch, 05Dh, 05Eh, 05Bh, 059h
    db 0C2h, 008h, 000h
?d_007f7cf0@@YAXXZ ENDP
_TEXT$d00bf7cf0 ENDS
_TEXT SEGMENT

; ghidra: bounds-high  retail @ 0x007F8820 size 17
public ?d_007f8820@@YAXXZ
?d_007f8820@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 54h, 24h, 08h, 89h, 41h, 28h, 89h, 51h, 2Ch, 0C2h, 08h
    db 00h
?d_007f8820@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F89B0 size 31
public ?d_007f89b0@@YAXXZ
?d_007f89b0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 90h, 0B8h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0EAh, 94h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f89b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8DC0 size 15
public ?d_007f8dc0@@YAXXZ
?d_007f8dc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 20h, 25h, 0FFh, 0FFh, 0FFh, 00h, 0C2h, 04h, 00h
?d_007f8dc0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8DF0 size 29
public ?d_007f8df0@@YAXXZ
?d_007f8df0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 0Ch, 8Bh, 4Ch, 24h, 08h, 8Bh, 15h, 2Ch, 3Bh, 2Ch, 01h, 50h, 51h
    db 8Bh, 4Ch, 24h, 0Ch, 52h, 0E8h, 76h, 0FCh, 0FEh, 0FFh, 0C2h, 0Ch, 00h
?d_007f8df0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8EA0 size 33
public ?d_007f8ea0@@YAXXZ
?d_007f8ea0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 28h, 8Ah, 4Ch, 24h, 0Ch, 25h, 0FFh, 0FFh, 0FFh, 00h
    db 0Dh, 00h, 00h, 00h, 80h, 84h, 0C9h, 74h, 05h, 0Dh, 00h, 00h, 00h, 30h, 0C2h, 0Ch
    db 00h
?d_007f8ea0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8ED0 size 5
public ?d_007f8ed0@@YAXXZ
?d_007f8ed0@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_007f8ed0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8EE0 size 16
public ?d_007f8ee0@@YAXXZ
?d_007f8ee0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 20h, 0C1h, 0E8h, 1Dh, 83h, 0E0h, 01h, 0C2h, 04h, 00h
?d_007f8ee0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8F10 size 39
public ?d_007f8f10@@YAXXZ
?d_007f8f10@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 10h, 8Dh, 50h, 01h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 08h, 40h, 84h, 0C9h, 75h, 0F9h, 2Bh, 0C2h, 0B9h, 00h, 08h, 00h, 00h, 3Bh, 0C8h
    db 1Bh, 0C0h, 0F7h, 0D8h, 0C2h, 04h, 00h
?d_007f8f10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8F40 size 31
public ?d_007f8f40@@YAXXZ
?d_007f8f40@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 54h, 0B9h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 5Ah, 8Fh, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f8f40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8F70 size 5
public ?d_007f8f70@@YAXXZ
?d_007f8f70@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 0Ch, 00h
?d_007f8f70@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8F80 size 5
public ?d_007f8f80@@YAXXZ
?d_007f8f80@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_007f8f80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8F90 size 5
public ?d_007f8f90@@YAXXZ
?d_007f8f90@@YAXXZ PROC
    db 33h, 0C0h, 0C2h, 04h, 00h
?d_007f8f90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F8FA0 size 5
public ?d_007f8fa0@@YAXXZ
?d_007f8fa0@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_007f8fa0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007F96A0 size 31
public ?d_007f96a0@@YAXXZ
?d_007f96a0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0A8h, 0B9h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0FAh, 87h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007f96a0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FA340 size 134
public ?d_007fa340@@YAXXZ
?d_007fa340@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 0F1h, 8Bh, 4Eh, 14h, 8Bh, 01h, 57h, 0FFh, 50h
    db 08h, 8Bh, 46h, 10h, 85h, 0C0h, 74h, 0Dh, 3Bh, 0F8h, 72h, 09h, 57h, 8Dh, 4Eh, 0F8h
    db 0E8h, 0DBh, 0FEh, 0FFh, 0FFh, 8Bh, 86h, 0A4h, 06h, 00h, 00h, 85h, 0C0h, 8Dh, 0BEh, 0A4h
    db 06h, 00h, 00h, 74h, 4Ch, 53h, 55h, 8Bh, 0CFh, 0E8h, 62h, 62h, 00h, 00h, 8Bh, 0E8h
    db 0E8h, 8Bh, 14h, 0FFh, 0FFh, 8Bh, 4Eh, 14h, 68h, 0D6h, 02h, 00h, 00h, 68h, 50h, 0BAh
    db 12h, 01h, 68h, 98h, 0BBh, 12h, 01h, 51h, 8Bh, 0D8h, 8Bh, 03h, 68h, 94h, 0BBh, 12h
    db 01h, 55h, 89h, 44h, 24h, 2Ch, 0E8h, 35h, 0F0h, 0FFh, 0FFh, 83h, 0C4h, 0Ch, 50h, 8Bh
    db 44h, 24h, 24h, 8Bh, 0CBh, 0FFh, 50h, 10h, 8Bh, 0CFh, 0E8h, 31h, 62h, 00h, 00h, 5Dh
    db 5Bh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007fa340@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FA3D0 size 250
public ?d_007fa3d0@@YAXXZ
?d_007fa3d0@@YAXXZ PROC
    db 53h, 55h, 8Bh, 6Ch, 24h, 10h, 57h, 8Bh, 0F9h, 8Bh, 0CDh, 0E8h, 0E0h, 0E6h, 0FEh, 0FFh
    db 8Bh, 5Ch, 24h, 10h, 8Bh, 0CBh, 0E8h, 0B5h, 0E4h, 0FEh, 0FFh, 84h, 0C0h, 74h, 0Fh, 6Ah
    db 99h, 8Bh, 0CDh, 0E8h, 0C8h, 0E4h, 0FEh, 0FFh, 5Fh, 5Dh, 5Bh, 0C2h, 0Ch, 00h, 8Bh, 8Fh
    db 0A8h, 06h, 00h, 00h, 8Bh, 01h, 56h, 8Bh, 73h, 2Ch, 0FFh, 50h, 04h, 3Bh, 0F0h, 74h
    db 10h, 6Ah, 97h, 8Bh, 0CDh, 0E8h, 0A6h, 0E4h, 0FEh, 0FFh, 5Eh, 5Fh, 5Dh, 5Bh, 0C2h, 0Ch
    db 00h, 8Bh, 0CFh, 0E8h, 58h, 0F6h, 0FFh, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 75h, 10h, 6Ah, 9Bh
    db 8Bh, 0CDh, 0E8h, 89h, 0E4h, 0FEh, 0FFh, 5Eh, 5Fh, 5Dh, 5Bh, 0C2h, 0Ch, 00h, 8Bh, 47h
    db 14h, 85h, 0C0h, 74h, 10h, 6Ah, 93h, 8Bh, 0CDh, 0E8h, 72h, 0E4h, 0FEh, 0FFh, 5Eh, 5Fh
    db 5Dh, 5Bh, 0C2h, 0Ch, 00h, 8Bh, 4Ch, 24h, 1Ch, 51h, 56h, 8Bh, 0CFh, 89h, 6Eh, 08h
    db 0E8h, 3Bh, 0F1h, 0FFh, 0FFh, 8Bh, 06h, 8Bh, 4Fh, 24h, 8Bh, 11h, 50h, 53h, 0FFh, 12h
    db 8Bh, 0Eh, 89h, 4Bh, 28h, 6Ah, 00h, 0C7h, 46h, 04h, 01h, 00h, 00h, 00h, 8Bh, 4Fh
    db 24h, 8Bh, 11h, 6Ah, 01h, 53h, 0FFh, 52h, 14h, 68h, 0C0h, 0BBh, 12h, 01h, 53h, 8Bh
    db 0CFh, 89h, 43h, 20h, 0E8h, 27h, 0FEh, 0FFh, 0FFh, 0BBh, 02h, 00h, 00h, 00h, 8Bh, 0FFh
    db 8Bh, 4Fh, 20h, 0E8h, 38h, 01h, 0FFh, 0FFh, 0E8h, 0C3h, 0F6h, 0FEh, 0FFh, 8Bh, 10h, 6Ah
    db 0Ah, 8Bh, 0C8h, 0FFh, 52h, 04h, 39h, 5Eh, 04h, 75h, 0E5h, 56h, 8Bh, 0CFh, 0E8h, 0FDh
    db 0F5h, 0FFh, 0FFh, 5Eh, 5Fh, 5Dh, 5Bh, 0C2h, 0Ch, 00h
?d_007fa3d0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FA6B0 size 10
public ?d_007fa6b0@@YAXXZ
?d_007fa6b0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 89h, 41h, 04h, 0C2h, 04h, 00h
?d_007fa6b0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FA750 size 49
public ?d_007fa750@@YAXXZ
?d_007fa750@@YAXXZ PROC
    db 8Ah, 41h, 10h, 84h, 0C0h, 75h, 08h, 0B8h, 33h, 0FFh, 0FFh, 0FFh, 0C2h, 04h, 00h, 8Bh
    db 44h, 24h, 04h, 8Bh, 50h, 0Ch, 8Bh, 49h, 08h, 52h, 8Bh, 50h, 08h, 52h, 8Bh, 50h
    db 04h, 8Bh, 00h, 52h, 50h, 51h, 0E8h, 0F5h, 0CBh, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h
    db 00h
?d_007fa750@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FA8E0 size 31
public ?d_007fa8e0@@YAXXZ
?d_007fa8e0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0B8h, 0B3h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0BAh, 75h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007fa8e0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAA10 size 149
public ?d_007faa10@@YAXXZ
?d_007faa10@@YAXXZ PROC
    db 57h, 8Bh, 0F9h, 83h, 7Fh, 48h, 04h, 0Fh, 8Dh, 81h, 00h, 00h, 00h, 33h, 0C0h, 8Dh
    db 4Fh, 08h, 56h, 83h, 39h, 00h, 74h, 0Eh, 40h, 83h, 0C1h, 10h, 83h, 0F8h, 04h, 7Ch
    db 0F2h, 83h, 0CEh, 0FFh, 0EBh, 07h, 83h, 0F8h, 0FFh, 8Bh, 0F0h, 75h, 18h, 0E8h, 0CEh, 0Dh
    db 0FFh, 0FFh, 8Bh, 10h, 6Ah, 60h, 68h, 80h, 0BCh, 12h, 01h, 68h, 58h, 0BCh, 12h, 01h
    db 8Bh, 0C8h, 0FFh, 52h, 0Ch, 8Bh, 44h, 24h, 14h, 8Bh, 4Ch, 24h, 18h, 8Bh, 54h, 24h
    db 10h, 0C1h, 0E6h, 04h, 03h, 0F7h, 89h, 46h, 08h, 8Bh, 44h, 24h, 0Ch, 68h, 10h, 27h
    db 00h, 00h, 50h, 89h, 4Eh, 0Ch, 89h, 56h, 10h, 0E8h, 0A2h, 0CEh, 00h, 00h, 89h, 46h
    db 14h, 8Bh, 4Fh, 48h, 83h, 0C4h, 08h, 41h, 89h, 4Fh, 48h, 8Dh, 4Fh, 04h, 51h, 8Bh
    db 4Fh, 4Ch, 0E8h, 0B9h, 0FAh, 0FEh, 0FFh, 5Eh, 33h, 0C0h, 5Fh, 0C2h, 10h, 00h, 83h, 0C8h
    db 0FFh, 5Fh, 0C2h, 10h, 00h
?d_007faa10@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAC90 size 25
public ?d_007fac90@@YAXXZ
?d_007fac90@@YAXXZ PROC
    db 8Bh, 01h, 8Bh, 91h, 0D4h, 00h, 00h, 00h, 89h, 54h, 24h, 08h, 8Dh, 91h, 90h, 00h
    db 00h, 00h, 89h, 54h, 24h, 04h, 0FFh, 60h, 04h
?d_007fac90@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FACB0 size 22
public ?d_007facb0@@YAXXZ
?d_007facb0@@YAXXZ PROC
    db 8Bh, 01h, 8Bh, 91h, 0D0h, 00h, 00h, 00h, 89h, 54h, 24h, 08h, 8Dh, 51h, 50h, 89h
    db 54h, 24h, 04h, 0FFh, 60h, 04h
?d_007facb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FACD0 size 36
public ?d_007facd0@@YAXXZ
?d_007facd0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 6Ah, 40h, 50h, 8Dh, 4Eh, 50h, 51h, 0E8h, 0D7h
    db 0C3h, 1Fh, 00h, 8Bh, 54h, 24h, 18h, 83h, 0C4h, 0Ch, 89h, 96h, 0D0h, 00h, 00h, 00h
    db 5Eh, 0C2h, 08h, 00h
?d_007facd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAD00 size 39
public ?d_007fad00@@YAXXZ
?d_007fad00@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 56h, 8Bh, 0F1h, 6Ah, 40h, 50h, 8Dh, 8Eh, 90h, 00h, 00h, 00h
    db 51h, 0E8h, 0A4h, 0C3h, 1Fh, 00h, 8Bh, 54h, 24h, 18h, 83h, 0C4h, 0Ch, 89h, 96h, 0D4h
    db 00h, 00h, 00h, 5Eh, 0C2h, 08h, 00h
?d_007fad00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAD30 size 7
public ?d_007fad30@@YAXXZ
?d_007fad30@@YAXXZ PROC
    db 8Dh, 81h, 90h, 00h, 00h, 00h, 0C3h
?d_007fad30@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAD40 size 7
public ?d_007fad40@@YAXXZ
?d_007fad40@@YAXXZ PROC
    db 8Bh, 81h, 0D4h, 00h, 00h, 00h, 0C3h
?d_007fad40@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FAD50 size 31
public ?d_007fad50@@YAXXZ
?d_007fad50@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0Ch, 0BCh, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 4Ah, 71h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007fad50@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FADA0 size 36
public ?d_007fada0@@YAXXZ
?d_007fada0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0Ch, 0BCh, 12h, 01h, 74h, 0Eh
    db 68h, 0D8h, 00h, 00h, 00h, 56h, 0E8h, 0B5h, 53h, 0FFh, 0FFh, 83h, 0C4h, 08h, 8Bh, 0C6h
    db 5Eh, 0C2h, 04h, 00h
?d_007fada0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBAA0 size 15
public ?d_007fbaa0@@YAXXZ
?d_007fbaa0@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0C1h, 04h, 0FFh, 10h, 8Bh, 0C8h, 0E9h, 0D1h, 0E4h, 0FEh, 0FFh
?d_007fbaa0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBB60 size 24
public ?d_007fbb60@@YAXXZ
?d_007fbb60@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 0Dh, 0B8h, 3Bh, 2Ch, 01h, 50h, 51h, 8Bh, 4Ch, 24h, 0Ch
    db 0E8h, 5Bh, 0CDh, 0FEh, 0FFh, 0C2h, 08h, 00h
?d_007fbb60@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBB80 size 20
public ?d_007fbb80@@YAXXZ
?d_007fbb80@@YAXXZ PROC
    db 0A1h, 0B8h, 3Bh, 2Ch, 01h, 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 50h, 0E8h, 6Fh, 0CDh, 0FEh
    db 0FFh, 0C2h, 04h, 00h
?d_007fbb80@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBBA0 size 10
public ?d_007fbba0@@YAXXZ
?d_007fbba0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 20h, 0C2h, 04h, 00h
?d_007fbba0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBBB0 size 13
public ?d_007fbbb0@@YAXXZ
?d_007fbbb0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 80h, 80h, 02h, 00h, 00h, 0C2h, 08h, 00h
?d_007fbbb0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBBD0 size 5
public ?d_007fbbd0@@YAXXZ
?d_007fbbd0@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_007fbbd0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FBBE0 size 31
public ?d_007fbbe0@@YAXXZ
?d_007fbbe0@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 0B0h, 0BEh, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 0BAh, 62h, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007fbbe0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FCF00 size 15
public ?d_007fcf00@@YAXXZ
?d_007fcf00@@YAXXZ PROC
    db 8Bh, 41h, 04h, 83h, 0C1h, 04h, 0FFh, 10h, 8Bh, 0C8h, 0E9h, 81h, 0D0h, 0FEh, 0FFh
?d_007fcf00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FCFC0 size 24
public ?d_007fcfc0@@YAXXZ
?d_007fcfc0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 8Bh, 0Dh, 58h, 3Ch, 2Ch, 01h, 50h, 51h, 8Bh, 4Ch, 24h, 0Ch
    db 0E8h, 0FBh, 0B8h, 0FEh, 0FFh, 0C2h, 08h, 00h
?d_007fcfc0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FCFE0 size 20
public ?d_007fcfe0@@YAXXZ
?d_007fcfe0@@YAXXZ PROC
    db 0A1h, 58h, 3Ch, 2Ch, 01h, 8Bh, 4Ch, 24h, 04h, 6Ah, 00h, 50h, 0E8h, 0Fh, 0B9h, 0FEh
    db 0FFh, 0C2h, 04h, 00h
?d_007fcfe0@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FD000 size 10
public ?d_007fd000@@YAXXZ
?d_007fd000@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 40h, 20h, 0C2h, 04h, 00h
?d_007fd000@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FD010 size 13
public ?d_007fd010@@YAXXZ
?d_007fd010@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 8Bh, 80h, 9Ch, 02h, 00h, 00h, 0C2h, 08h, 00h
?d_007fd010@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FD030 size 5
public ?d_007fd030@@YAXXZ
?d_007fd030@@YAXXZ PROC
    db 32h, 0C0h, 0C2h, 04h, 00h
?d_007fd030@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x007FD040 size 31
public ?d_007fd040@@YAXXZ
?d_007fd040@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 48h, 0C1h, 12h, 01h, 74h, 09h
    db 56h, 0E8h, 5Ah, 4Eh, 08h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_007fd040@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00800880 size 49
public ?d_00800880@@YAXXZ
?d_00800880@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 33h, 0C0h, 8Dh, 91h, 0D4h, 00h, 00h, 00h, 8Dh, 49h, 00h
    db 39h, 32h, 74h, 0Fh, 40h, 83h, 0C2h, 24h, 83h, 0F8h, 08h, 7Ch, 0F3h, 33h, 0C0h, 5Eh
    db 0C2h, 04h, 00h, 8Dh, 04h, 0C0h, 8Dh, 84h, 81h, 0D4h, 00h, 00h, 00h, 5Eh, 0C2h, 04h
    db 00h
?d_00800880@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00800A00 size 53
public ?d_00800a00@@YAXXZ
?d_00800a00@@YAXXZ PROC
    db 56h, 33h, 0C0h, 57h, 0C7h, 01h, 08h, 0C3h, 12h, 01h, 0C7h, 41h, 04h, 04h, 0C3h, 12h
    db 01h, 89h, 41h, 08h, 89h, 41h, 0Ch, 89h, 41h, 10h, 8Dh, 0B1h, 04h, 02h, 00h, 00h
    db 0BFh, 08h, 00h, 00h, 00h, 83h, 0EEh, 24h, 8Bh, 0CEh, 0E8h, 91h, 7Ch, 0FEh, 0FFh, 4Fh
    db 75h, 0F3h, 5Fh, 5Eh, 0C3h
?d_00800a00@@YAXXZ ENDP

; ghidra: bounds-high  retail @ 0x00800CA0 size 38
public ?d_00800ca0@@YAXXZ
?d_00800ca0@@YAXXZ PROC
    db 56h, 57h, 8Bh, 7Ch, 24h, 0Ch, 6Ah, 00h, 8Bh, 0F1h, 68h, 44h, 0C1h, 12h, 01h, 8Bh
    db 0CFh, 0E8h, 4Ah, 7Ch, 0FEh, 0FFh, 50h, 57h, 6Ah, 00h, 8Bh, 0CEh, 0E8h, 0Fh, 0FFh, 0FFh
    db 0FFh, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_00800ca0@@YAXXZ ENDP
_TEXT ENDS
END
