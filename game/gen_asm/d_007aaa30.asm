.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Add_To_Static_Sort_List@WW3D@@SAXPAVRenderObjClass@@I@Z:NEAR
EXTERN ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ:NEAR
EXTERN ?AreStaticSortListsEnabled@WW3D@@0_NA:BYTE
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?GenFallback0012ED5C8@@3PAVGenFallback@@A:BYTE
EXTERN ?HighlightRendering@@3_NA:BYTE
EXTERN ?Invalidate_Cached_Render_States@DX8Wrapper@@SAXXZ:NEAR
EXTERN ?Is_Backface_Culling_Inverted@ShaderClass@@SA_NXZ:NEAR
EXTERN ?TheBfmeGlobal_012f7fe0@@3PAVBfmeGlobal_012f7fe0@@A:BYTE
EXTERN ?forward@Rva00014C45WaterTracksFlushThunk@@QAEXAAVRenderInfoClass@@@Z:NEAR
EXTERN ?j_0001b897@@YAXXZ:NEAR
EXTERN ?j_000243b6@@YAXXZ:NEAR
EXTERN ?j_000364bc@@YAXXZ:NEAR
_TEXT SEGMENT

; retail @ 0x007AAA30 size 244
_TEXT ENDS
_TEXT$d00baaa30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BAAA30 size 244
public ?d_007aaa30@@YAXXZ
?d_007aaa30@@YAXXZ PROC
    db 0A0h
    dd ?HighlightRendering@@3_NA
    db 084h, 0C0h, 056h, 08Bh, 0F1h, 00Fh, 085h, 0CEh, 000h, 000h, 000h, 0A1h
    dd ?TheBfmeGlobal_012f7fe0@@3PAVBfmeGlobal_012f7fe0@@A
    db 085h, 0C0h, 074h, 00Eh, 08Bh, 088h, 0F4h, 02Fh, 000h, 000h, 085h, 0C9h, 00Fh, 084h, 0B7h, 000h
    db 000h, 000h
    call ?Is_Backface_Culling_Inverted@ShaderClass@@SA_NXZ
    db 084h, 0C0h, 00Fh, 085h, 0AAh, 000h, 000h, 000h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 074h, 001h
    db 000h, 000h, 08Ah, 00Dh
    dd ?AreStaticSortListsEnabled@WW3D@@0_NA
    db 084h, 0C9h, 074h, 01Bh, 085h, 0C0h, 074h, 017h, 08Dh, 04Eh, 0FCh, 0F7h, 0D9h, 01Bh, 0C9h, 023h
    db 0CEh, 050h, 051h
    call ?Add_To_Static_Sort_List@WW3D@@SAXPAVRenderObjClass@@I@Z
    db 083h, 0C4h, 008h, 05Eh, 0C2h, 004h, 000h, 08Bh, 086h, 018h, 001h, 000h, 000h, 083h, 0F8h, 003h
    db 057h, 08Bh, 07Ch, 024h, 00Ch, 077h, 026h, 0FFh, 024h, 085h
    dd ?d_007aaa30@@YAXXZ + 0E4h
    db 057h, 08Dh, 04Eh, 0FCh
    call ?j_000243b6@@YAXXZ
    db 0EBh, 014h, 057h, 08Dh, 04Eh, 0FCh
    call ?j_000364bc@@YAXXZ
    db 0EBh, 009h, 057h, 08Dh, 04Eh, 0FCh
    call ?j_0001b897@@YAXXZ
    db 0A1h
    dd ?GenFallback0012ED5C8@@3PAVGenFallback@@A
    db 085h, 0C0h, 074h, 021h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 080h, 080h, 001h, 000h, 000h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Bh, 00Ch, 08Bh
    db 08Eh, 04Ch, 002h, 000h, 000h, 08Bh, 011h, 057h, 0FFh, 052h, 030h
    call ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ
    call ?Invalidate_Cached_Render_States@DX8Wrapper@@SAXXZ
    db 08Bh, 08Eh, 050h, 002h, 000h, 000h, 085h, 0C9h, 074h, 006h, 057h
    call ?forward@Rva00014C45WaterTracksFlushThunk@@QAEXAAVRenderInfoClass@@@Z
    db 05Fh, 05Eh, 0C2h, 004h, 000h, 08Bh, 0FFh
    dd ?d_007aaa30@@YAXXZ + 07Ah
    dd ?d_007aaa30@@YAXXZ + 090h
    dd ?d_007aaa30@@YAXXZ + 085h
    dd ?d_007aaa30@@YAXXZ + 07Ah
?d_007aaa30@@YAXXZ ENDP
_TEXT$d00baaa30 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
