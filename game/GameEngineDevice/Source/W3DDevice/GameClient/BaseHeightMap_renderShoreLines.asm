.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??0BoxDynamicVBAccessClass@@QAE@IIGI@Z:NEAR
EXTERN ??0DynamicIBAccessClass@@QAE@GG@Z:NEAR
EXTERN ??0WriteLockClass@BoxDynamicVBAccessClass@@QAE@PAV1@@Z:NEAR
EXTERN ??0WriteLockClass@DynamicIBAccessClass@@QAE@PAV1@@Z:NEAR
EXTERN ??1BoxDynamicVBAccessClass@@QAE@XZ:NEAR
EXTERN ??1DynamicIBAccessClass@@QAE@XZ:NEAR
EXTERN ??1WriteLockClass@BoxDynamicVBAccessClass@@QAE@XZ:NEAR
EXTERN ??1WriteLockClass@DynamicIBAccessClass@@QAE@XZ:NEAR
EXTERN ?BaseHeightMapScorchSetZBias@@YAXH@Z:NEAR
EXTERN ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z:NEAR
EXTERN ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z:NEAR
EXTERN ?Free_String@StringClass@@AAEXXZ:NEAR
EXTERN ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z:NEAR
EXTERN ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z:NEAR
EXTERN ?Get_Preset@VertexMaterialClass@@SAPAV1@W4PresetType@1@@Z:NEAR
EXTERN ?Get_String@StringClass@@AAEXH_N@Z:NEAR
EXTERN ?Rva00903060Get@@YAHXZ:NEAR
EXTERN ?Set_Index_Buffer@DX8Wrapper@@SAXABVDynamicIBAccessClass@@G@Z:NEAR
EXTERN ?Set_Vertex_Buffer@DX8Wrapper@@SAXABVDynamicVBAccessClass@@@Z:NEAR
EXTERN ?j_000489a5@@YAXXZ:NEAR
EXTERN __ftol2:NEAR
EXTERN g_0104A23C:NEAR
EXTERN g_01075350:BYTE
EXTERN g_01075C74:BYTE
EXTERN g_010F653C:BYTE
EXTERN g_012D6DFC:BYTE
EXTERN g_012D6E1C:BYTE
EXTERN g_012D9124:BYTE
EXTERN g_012ED5C8:BYTE
EXTERN g_0133F451:BYTE
EXTERN g_0133F49C:BYTE
EXTERN g_0133FA0C:BYTE
EXTERN g_013403A0:BYTE
EXTERN g_01340534:BYTE
EXTERN g_01340564:BYTE
EXTERN g_01340568:BYTE
EXTERN g_01340594:BYTE
EXTERN g_01340EC0:BYTE
EXTERN g_01340EC4:BYTE
EXTERN g_0134108C:BYTE
EXTERN g_01341090:BYTE
EXTERN g_01341094:BYTE
EXTERN g_01341098:BYTE
EXTERN g_0134109C:BYTE
EXTERN g_013410A0:BYTE
EXTERN g_013410A4:BYTE
EXTERN g_013410A8:BYTE
EXTERN g_013410AC:BYTE
EXTERN g_013410B0:BYTE
EXTERN g_013410B4:BYTE
EXTERN g_013410B8:BYTE
EXTERN g_013410BC:BYTE
EXTERN g_013410C0:BYTE
EXTERN g_013410C4:BYTE
EXTERN g_013410C8:BYTE
EXTERN g_0134ECC8:BYTE

; ?renderShoreLines@BaseHeightMapRenderObjClass@@IAEXPAVCameraClass@@@Z
; Exact 2268 retail bytes @ 0x006CCE70; queue 0x00935424 was INSIDE foreign body (not prologue).
; Identity: HeightMap::Render@0x6D3480 calls ILT 0x21463->here; soft-water+A8R8G8B8 guards;
; DynamicVB/IB batch 2048/3072 (DEFAULT_MAX_BATCH_SHORELINE_TILES); ret 4 CameraClass*.
; C++ blocked: class field-offset drift + ZH WorldBuilder branch absent in retail + many REL32.
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d00acce70 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00ACCE70 size 2268
public ?renderShoreLines@BaseHeightMapRenderObjClass@@IAEXPAVCameraClass@@@Z
?renderShoreLines@BaseHeightMapRenderObjClass@@IAEXPAVCameraClass@@@Z PROC
    db 055h, 08Bh, 0ECh, 083h, 0E4h, 0F8h, 06Ah, 0FFh, 068h
    dd g_0104A23C
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 08Ch, 000h, 000h, 000h, 0A1h
    dd g_012ED5C8
    db 053h, 055h, 056h, 057h, 08Bh, 0F9h, 08Ah, 088h, 08Ch, 000h, 000h, 000h, 084h, 0C9h, 089h, 07Ch
    db 024h, 01Ch, 00Fh, 084h, 089h, 007h, 000h, 000h, 0D9h, 005h
    dd g_01075350
    db 0D9h, 087h, 018h, 030h, 000h, 000h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 00Fh, 08Bh, 070h
    db 007h, 000h, 000h, 08Bh, 087h, 0C4h, 030h, 000h, 000h, 033h, 0EDh, 03Bh, 0C5h, 00Fh, 084h, 060h
    db 007h, 000h, 000h
    call ?Rva00903060Get@@YAHXZ
    db 083h, 0F8h, 015h, 00Fh, 085h, 052h, 007h, 000h, 000h, 08Bh, 087h, 0F4h, 02Fh, 000h, 000h, 08Bh
    db 048h, 008h, 08Bh, 050h, 010h, 08Bh, 007h, 089h, 04Ch, 024h, 028h, 08Dh, 04Ch, 024h, 070h, 051h
    db 08Bh, 0CFh, 089h, 06Ch, 024h, 024h, 089h, 06Ch, 024h, 028h, 089h, 054h, 024h, 034h, 0FFh, 090h
    db 038h, 002h, 000h, 000h, 0DBh, 044h, 024h, 078h
    call __ftol2
    db 0DBh, 044h, 024h, 07Ch, 089h, 044h, 024h, 060h
    call __ftol2
    db 0DBh, 044h, 024h, 070h, 089h, 044h, 024h, 040h
    call __ftol2
    db 0DBh, 044h, 024h, 074h, 089h, 044h, 024h, 058h
    call __ftol2
    db 08Bh, 097h, 0F4h, 02Fh, 000h, 000h, 08Ah, 00Dh
    dd g_012D6DFC
    db 08Bh, 05Ah, 024h, 089h, 044h, 024h, 034h, 0A1h
    dd g_012D6E1C
    db 083h, 0E0h, 0FBh, 083h, 0C8h, 003h, 084h, 0C9h, 089h, 05Ch, 024h, 03Ch, 089h, 06Ch, 024h, 018h
    db 075h, 008h, 03Bh, 005h
    dd g_01340EC0
    db 074h, 040h, 08Bh, 015h
    dd g_0133F49C
    db 0A3h
    dd g_01340EC0
    db 0A1h
    dd g_012D9124
    db 055h, 081h, 0CAh, 000h, 080h, 000h, 000h, 055h, 08Dh, 04Ch, 024h, 018h, 089h, 015h
    dd g_0133F49C
    db 089h, 044h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 08Ah, 00Dh
    dd g_0134ECC8
    db 08Bh, 054h, 024h, 010h, 088h, 00Ah, 08Dh, 04Ch, 024h, 010h
    call ?Free_String@StringClass@@AAEXXZ
    db 055h
    call ?Get_Preset@VertexMaterialClass@@SAPAV1@W4PresetType@1@@Z
    db 08Bh, 0F0h, 083h, 0C4h, 004h, 085h, 0F6h, 074h, 003h, 0FFh, 046h, 004h, 0A1h
    dd g_01340EC4
    db 085h, 0C0h, 074h, 013h, 08Bh, 050h, 004h, 08Bh, 0C8h, 083h, 0C0h, 004h, 04Ah, 085h, 0D2h, 089h
    db 010h, 075h, 004h, 08Bh, 001h, 0FFh, 010h, 08Bh, 00Dh
    dd g_0133F49C
    db 081h, 0C9h, 000h, 040h, 000h, 000h, 085h, 0F6h, 089h, 035h
    dd g_01340EC4
    db 089h, 00Dh
    dd g_0133F49C
    db 074h, 00Bh, 0FFh, 04Eh, 004h, 075h, 006h, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 012h, 08Dh, 087h, 090h
    db 030h, 000h, 000h, 050h, 06Ah, 000h
    call ?BoxSetTexture@@YAXIAAPAVTextureBaseClass@@@Z
    db 08Bh, 00Dh
    dd g_0133F49C
    db 0A1h
    dd g_013403A0
    db 081h, 0E1h, 0FFh, 0FFh, 0FBh, 0FFh, 083h, 0C9h, 001h, 0BEh, 008h, 000h, 000h, 000h, 083h, 0C4h
    db 008h, 03Bh, 0C6h, 0C7h, 005h
    dd g_0134108C
    db 000h, 000h, 080h, 03Fh, 0C7h, 005h
    dd g_01341090
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_01341094
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_01341098
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_0134109C
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410A0
    db 000h, 000h, 080h, 03Fh, 0C7h, 005h
    dd g_013410A4
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410A8
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410AC
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410B0
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410B4
    db 000h, 000h, 080h, 03Fh, 0C7h, 005h
    dd g_013410B8
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410BC
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410C0
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410C4
    db 000h, 000h, 000h, 000h, 0C7h, 005h
    dd g_013410C8
    db 000h, 000h, 080h, 03Fh, 089h, 00Dh
    dd g_0133F49C
    db 00Fh, 084h, 08Fh, 000h, 000h, 000h, 0A0h
    dd g_0133F451
    db 084h, 0C0h, 074h, 054h, 08Bh, 015h
    dd g_012D9124
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd g_0134ECC8
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 056h, 08Dh, 054h, 024h, 014h, 068h, 0A8h, 000h, 000h, 000h
    db 052h, 0C7h, 084h, 024h, 0B0h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd g_01340534
    db 056h, 068h, 0A8h, 000h, 000h, 000h, 089h, 035h
    dd g_013403A0
    db 08Bh, 008h, 050h, 0FFh, 091h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd g_01340594
    db 0A1h
    dd g_01340564
    db 041h, 040h, 089h, 00Dh
    dd g_01340594
    db 0A3h
    dd g_01340564
    db 06Ah, 001h
    call ?BaseHeightMapScorchSetZBias@@YAXH@Z
    db 0A1h
    dd g_0133FA0C
    db 083h, 0C4h, 004h, 085h, 0C0h, 00Fh, 084h, 091h, 000h, 000h, 000h, 0A0h
    dd g_0133F451
    db 084h, 0C0h, 074h, 052h, 08Bh, 015h
    dd g_012D9124
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 04Ch, 024h, 018h, 089h, 054h, 024h, 018h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd g_0134ECC8
    db 08Bh, 04Ch, 024h, 010h, 088h, 001h, 06Ah, 000h, 08Dh, 054h, 024h, 014h, 06Ah, 00Bh, 052h, 0C7h
    db 084h, 024h, 0B0h, 000h, 000h, 000h, 001h, 000h, 000h, 000h
    call ?Get_DX8_Texture_Stage_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 010h, 0C7h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd g_01340534
    db 06Ah, 000h, 06Ah, 00Bh, 06Ah, 000h, 0C7h, 005h
    dd g_0133FA0C
    db 000h, 000h, 000h, 000h, 08Bh, 008h, 050h, 0FFh, 091h, 00Ch, 001h, 000h, 000h, 08Bh, 00Dh
    dd g_01340594
    db 0A1h
    dd g_01340568
    db 041h, 040h, 089h, 00Dh
    dd g_01340594
    db 0A3h
    dd g_01340568
    db 08Bh, 087h, 0C4h, 030h, 000h, 000h, 085h, 0C0h, 00Fh, 084h, 065h, 003h, 000h, 000h, 06Ah, 000h
    db 068h, 000h, 008h, 000h, 000h, 06Ah, 005h, 06Ah, 002h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h
    call ??0BoxDynamicVBAccessClass@@QAE@IIGI@Z
    db 068h, 000h, 00Ch, 000h, 000h, 06Ah, 002h, 08Dh, 04Ch, 024h, 06Ch, 0C7h, 084h, 024h, 0ACh, 000h
    db 000h, 000h, 002h, 000h, 000h, 000h
    call ??0DynamicIBAccessClass@@QAE@GG@Z
    db 08Dh, 094h, 024h, 080h, 000h, 000h, 000h, 052h, 08Dh, 04Ch, 024h, 054h, 0C6h, 084h, 024h, 0A8h
    db 000h, 000h, 000h, 003h
    call ??0WriteLockClass@BoxDynamicVBAccessClass@@QAE@PAV1@@Z
    db 08Bh, 074h, 024h, 054h, 08Dh, 044h, 024h, 064h, 050h, 08Dh, 04Ch, 024h, 048h, 0C6h, 084h, 024h
    db 0A8h, 000h, 000h, 000h, 004h
    call ??0WriteLockClass@DynamicIBAccessClass@@QAE@PAV1@@Z
    db 08Bh, 044h, 024h, 048h, 085h, 0C0h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 005h, 00Fh, 084h
    db 0B2h, 003h, 000h, 000h, 085h, 0F6h, 00Fh, 084h, 0AAh, 003h, 000h, 000h, 08Bh, 04Ch, 024h, 018h
    db 03Bh, 08Fh, 0C4h, 030h, 000h, 000h, 00Fh, 08Dh, 02Ah, 002h, 000h, 000h, 083h, 0C0h, 004h, 089h
    db 044h, 024h, 010h, 08Dh, 004h, 089h, 0C1h, 0E0h, 002h, 089h, 044h, 024h, 02Ch, 0EBh, 008h, 08Dh
    db 0A4h, 024h, 000h, 000h, 000h, 000h, 090h, 081h, 0FDh, 000h, 008h, 000h, 000h, 00Fh, 08Dh, 003h
    db 002h, 000h, 000h, 08Bh, 08Fh, 0C0h, 030h, 000h, 000h, 08Bh, 03Ch, 001h, 003h, 0C8h, 08Bh, 0D7h
    db 081h, 0E2h, 0FFh, 0FFh, 000h, 000h, 0C1h, 0FFh, 010h, 03Bh, 054h, 024h, 058h, 00Fh, 08Ch, 0BFh
    db 001h, 000h, 000h, 03Bh, 054h, 024h, 060h, 00Fh, 08Dh, 0B5h, 001h, 000h, 000h, 03Bh, 07Ch, 024h
    db 034h, 00Fh, 08Ch, 0ABh, 001h, 000h, 000h, 03Bh, 07Ch, 024h, 040h, 00Fh, 08Dh, 0A1h, 001h, 000h
    db 000h, 08Bh, 0C7h, 00Fh, 0AFh, 044h, 024h, 028h, 003h, 0C2h, 00Fh, 0B7h, 02Ch, 043h, 089h, 06Ch
    db 024h, 014h, 00Fh, 0B7h, 06Ch, 043h, 002h, 0DBh, 044h, 024h, 014h, 089h, 06Ch, 024h, 014h, 08Bh
    db 06Ch, 024h, 028h, 0D8h, 00Dh
    dd g_010F653C
    db 003h, 0C5h, 0DBh, 044h, 024h, 014h, 08Dh, 004h, 043h, 00Fh, 0B7h, 058h, 002h, 0D8h, 00Dh
    dd g_010F653C
    db 00Fh, 0B7h, 000h, 08Bh, 06Ch, 024h, 030h, 089h, 05Ch, 024h, 014h, 08Bh, 05Ch, 024h, 030h, 083h
    db 0C6h, 02Ch, 0DBh, 044h, 024h, 014h, 089h, 044h, 024h, 014h, 08Bh, 0C2h, 02Bh, 0C5h, 0D8h, 00Dh
    dd g_010F653C
    db 08Bh, 0EFh, 02Bh, 0EBh, 083h, 0C6h, 02Ch, 0D9h, 05Ch, 024h, 04Ch, 083h, 0C6h, 02Ch, 0DBh, 044h
    db 024h, 014h, 089h, 044h, 024h, 014h, 0D8h, 00Dh
    dd g_010F653C
    db 0D9h, 05Ch, 024h, 038h, 0DBh, 044h, 024h, 014h, 089h, 06Ch, 024h, 014h, 0D8h, 00Dh
    dd g_01075C74
    db 0D9h, 054h, 024h, 05Ch, 0D9h, 09Eh, 07Ch, 0FFh, 0FFh, 0FFh, 0DBh, 044h, 024h, 014h, 0D8h, 00Dh
    dd g_01075C74
    db 0D9h, 056h, 080h, 0D9h, 0CAh, 0D9h, 05Eh, 084h, 08Bh, 059h, 004h, 089h, 05Eh, 098h, 033h, 0DBh
    db 089h, 05Eh, 09Ch, 040h, 089h, 044h, 024h, 014h, 0DBh, 044h, 024h, 014h, 045h, 083h, 0C6h, 02Ch
    db 0D8h, 00Dh
    dd g_01075C74
    db 0D9h, 054h, 024h, 014h, 0D9h, 09Eh, 07Ch, 0FFh, 0FFh, 0FFh, 0D9h, 0C9h, 0D9h, 05Eh, 080h, 0D9h
    db 05Eh, 084h, 08Bh, 041h, 008h, 089h, 046h, 098h, 08Bh, 044h, 024h, 014h, 089h, 05Eh, 09Ch, 089h
    db 046h, 0A8h, 08Bh, 044h, 024h, 04Ch, 089h, 06Ch, 024h, 014h, 0DBh, 044h, 024h, 014h, 089h, 046h
    db 0B0h, 0D8h, 00Dh
    dd g_01075C74
    db 0D9h, 056h, 0ACh, 08Bh, 041h, 00Ch, 089h, 046h, 0C4h, 08Bh, 044h, 024h, 05Ch, 089h, 05Eh, 0C8h
    db 0D9h, 05Eh, 0D8h, 089h, 046h, 0D4h, 08Bh, 044h, 024h, 038h, 089h, 046h, 0DCh, 08Bh, 049h, 010h
    db 089h, 04Eh, 0F0h, 089h, 05Eh, 0F4h, 057h, 052h, 08Bh, 054h, 024h, 024h, 08Bh, 08Ah, 0F4h, 02Fh
    db 000h, 000h
    call ?j_000489a5@@YAXXZ
    db 08Bh, 06Ch, 024h, 020h, 084h, 0C0h, 08Bh, 044h, 024h, 010h, 08Dh, 055h, 003h, 074h, 01Fh, 08Dh
    db 04Dh, 001h, 066h, 089h, 048h, 0FCh, 066h, 089h, 048h, 002h, 08Dh, 04Dh, 002h, 066h, 089h, 050h
    db 0FEh, 066h, 089h, 028h, 066h, 089h, 048h, 004h, 066h, 089h, 050h, 006h, 0EBh, 01Dh, 08Dh, 04Dh
    db 002h, 066h, 089h, 010h, 08Dh, 055h, 001h, 066h, 089h, 068h, 0FCh, 066h, 089h, 048h, 0FEh, 066h
    db 089h, 068h, 002h, 066h, 089h, 050h, 004h, 066h, 089h, 048h, 006h, 08Bh, 05Ch, 024h, 03Ch, 083h
    db 0C0h, 00Ch, 089h, 044h, 024h, 010h, 08Bh, 044h, 024h, 024h, 083h, 0C5h, 004h, 083h, 0C0h, 006h
    db 089h, 044h, 024h, 024h, 08Bh, 044h, 024h, 02Ch, 089h, 06Ch, 024h, 020h, 08Bh, 04Ch, 024h, 018h
    db 08Bh, 054h, 024h, 01Ch, 08Bh, 0BAh, 0C4h, 030h, 000h, 000h, 041h, 083h, 0C0h, 014h, 03Bh, 0CFh
    db 089h, 04Ch, 024h, 018h, 089h, 044h, 024h, 02Ch, 08Bh, 0FAh, 00Fh, 08Ch, 0F1h, 0FDh, 0FFh, 0FFh
    db 08Dh, 044h, 024h, 064h, 06Ah, 000h, 050h
    call ?Set_Index_Buffer@DX8Wrapper@@SAXABVDynamicIBAccessClass@@G@Z
    db 08Dh, 08Ch, 024h, 088h, 000h, 000h, 000h, 051h
    call ?Set_Vertex_Buffer@DX8Wrapper@@SAXABVDynamicVBAccessClass@@@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 044h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 004h
    call ??1WriteLockClass@DynamicIBAccessClass@@QAE@XZ
    db 08Dh, 04Ch, 024h, 050h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 003h
    call ??1WriteLockClass@BoxDynamicVBAccessClass@@QAE@XZ
    db 08Dh, 04Ch, 024h, 064h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 002h
    call ??1DynamicIBAccessClass@@QAE@XZ
    db 08Dh, 08Ch, 024h, 080h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ??1BoxDynamicVBAccessClass@@QAE@XZ
    db 08Bh, 04Ch, 024h, 024h, 085h, 0C9h, 07Eh, 020h, 085h, 0EDh, 07Eh, 01Ch, 0B8h, 056h, 055h, 055h
    db 055h, 0F7h, 0E9h, 08Bh, 0C2h, 055h, 0C1h, 0E8h, 01Fh, 06Ah, 000h, 003h, 0C2h, 050h, 06Ah, 000h
    call ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z
    db 083h, 0C4h, 010h, 08Bh, 04Ch, 024h, 018h, 08Bh, 087h, 0C4h, 030h, 000h, 000h, 033h, 0EDh, 03Bh
    db 0C8h, 089h, 06Ch, 024h, 020h, 089h, 06Ch, 024h, 024h, 00Fh, 085h, 09Bh, 0FCh, 0FFh, 0FFh, 0A1h
    dd g_013403A0
    db 0BEh, 007h, 000h, 000h, 000h, 03Bh, 0C6h, 00Fh, 084h, 08Bh, 000h, 000h, 000h, 0A0h
    dd g_0133F451
    db 084h, 0C0h, 074h, 050h, 08Bh, 015h
    dd g_012D9124
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 04Ch, 024h, 020h, 089h, 054h, 024h, 020h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd g_0134ECC8
    db 08Bh, 04Ch, 024h, 018h, 088h, 001h, 056h, 08Dh, 054h, 024h, 01Ch, 068h, 0A8h, 000h, 000h, 000h
    db 052h, 089h, 0B4h, 024h, 0B0h, 000h, 000h, 000h
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 018h, 0C7h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd g_01340534
    db 056h, 068h, 0A8h, 000h, 000h, 000h, 089h, 035h
    dd g_013403A0
    db 08Bh, 008h, 050h, 0FFh, 091h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd g_01340594
    db 0A1h
    dd g_01340564
    db 041h, 040h, 089h, 00Dh
    dd g_01340594
    db 0A3h
    dd g_01340564
    db 06Ah, 000h
    call ?BaseHeightMapScorchSetZBias@@YAXH@Z
    db 083h, 0C4h, 004h, 0C6h, 005h
    dd g_012D6DFC
    db 001h, 08Bh, 08Ch, 024h, 09Ch, 000h, 000h, 000h, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Fh
    db 05Eh, 05Dh, 05Bh, 08Bh, 0E5h, 05Dh, 0C2h, 004h, 000h, 0A1h
    dd g_013403A0
    db 0BEh, 007h, 000h, 000h, 000h, 03Bh, 0C6h, 00Fh, 084h, 089h, 000h, 000h, 000h, 0A0h
    dd g_0133F451
    db 084h, 0C0h, 074h, 04Eh, 08Bh, 015h
    dd g_012D9124
    db 06Ah, 001h, 06Ah, 000h, 08Dh, 04Ch, 024h, 020h, 089h, 054h, 024h, 020h
    call ?Get_String@StringClass@@AAEXH_N@Z
    db 0A0h
    dd g_0134ECC8
    db 08Bh, 04Ch, 024h, 018h, 088h, 001h, 056h, 08Dh, 054h, 024h, 01Ch, 068h, 0A8h, 000h, 000h, 000h
    db 052h, 0C6h, 084h, 024h, 0B0h, 000h, 000h, 000h, 006h
    call ?Get_DX8_Render_State_Value_Name@DX8Wrapper@@SAXAAVStringClass@@KI@Z
    db 083h, 0C4h, 00Ch, 08Dh, 04Ch, 024h, 018h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 005h
    call ?Free_String@StringClass@@AAEXXZ
    db 0A1h
    dd g_01340534
    db 056h, 068h, 0A8h, 000h, 000h, 000h, 089h, 035h
    dd g_013403A0
    db 08Bh, 008h, 050h, 0FFh, 091h, 0E4h, 000h, 000h, 000h, 08Bh, 00Dh
    dd g_01340594
    db 0A1h
    dd g_01340564
    db 041h, 040h, 089h, 00Dh
    dd g_01340594
    db 0A3h
    dd g_01340564
    db 08Dh, 04Ch, 024h, 044h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 004h
    call ??1WriteLockClass@DynamicIBAccessClass@@QAE@XZ
    db 08Dh, 04Ch, 024h, 050h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 003h
    call ??1WriteLockClass@BoxDynamicVBAccessClass@@QAE@XZ
    db 08Dh, 04Ch, 024h, 064h, 0C6h, 084h, 024h, 0A4h, 000h, 000h, 000h, 002h
    call ??1DynamicIBAccessClass@@QAE@XZ
    db 08Dh, 08Ch, 024h, 080h, 000h, 000h, 000h, 0C7h, 084h, 024h, 0A4h, 000h, 000h, 000h, 0FFh, 0FFh
    db 0FFh, 0FFh
    call ??1BoxDynamicVBAccessClass@@QAE@XZ
    db 08Bh, 08Ch, 024h, 09Ch, 000h, 000h, 000h, 05Fh, 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 05Eh
    db 05Dh, 05Bh, 08Bh, 0E5h, 05Dh, 0C2h, 004h, 000h
?renderShoreLines@BaseHeightMapRenderObjClass@@IAEXPAVCameraClass@@@Z ENDP
_TEXT$d00acce70 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
