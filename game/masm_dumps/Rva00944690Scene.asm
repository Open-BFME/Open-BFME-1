.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ?Internal_Add@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@_N@Z:NEAR
EXTERN ?Internal_Remove_List_Head@GenericMultiListClass@@IAEPAVMultiListObjectClass@@XZ:NEAR
EXTERN ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVSphereClass@@@Z:NEAR
EXTERN ?Update_Frustum@CameraClass@@IBEXXZ:NEAR
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?first@Gen_00943CF0@@AAEXPAXPAH11@Z:NEAR
EXTERN ?j_00009165@@YAXXZ:NEAR
EXTERN ?rva00944430@Rva00944430@@AAEXPAPAXPAVCameraClass@@PBM@Z:NEAR
EXTERN ?second@Gen_00943CF0@@AAEXPAX000@Z:NEAR
EXTERN ?unlink@Gen_00943CF0@@AAEXPAX@Z:NEAR
EXTERN g_Va0105DA98:NEAR

; Boundary repair of the pre-existing 0x009446F0/1075B ASM span.
; This still-unconverted whole function is 0x00944690/552B.
; Its five adjacent bodies are now separate C++ claims.
; Evidence: targets/game/reverse/identity_evidence/009446f0.md
_TEXT SEGMENT
_TEXT ENDS
_TEXT$d00d44690 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00D44690 size 552
public ?method@Rva00944690Scene@@UAEXPAVCameraClass@@@Z
?method@Rva00944690Scene@@UAEXPAVCameraClass@@@Z PROC
    db 06Ah, 0FFh, 068h
    dd g_Va0105DA98
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 020h, 053h, 08Bh, 0D9h, 08Bh, 083h, 0C4h, 000h, 000h, 000h, 055h, 08Dh, 08Bh, 0C0h, 000h, 000h
    db 000h, 03Bh, 0C1h, 056h, 057h, 089h, 05Ch, 024h, 010h, 089h, 044h, 024h, 02Ch, 089h, 04Ch, 024h
    db 024h, 00Fh, 084h, 088h, 000h, 000h, 000h, 0EBh, 004h, 08Bh, 044h, 024h, 02Ch, 08Bh, 070h, 00Ch
    db 085h, 0F6h, 074h, 005h, 083h, 0C6h, 0F8h, 0EBh, 002h, 033h, 0F6h, 08Dh, 044h, 024h, 018h, 050h
    db 08Dh, 04Ch, 024h, 020h, 051h, 08Dh, 054h, 024h, 028h, 052h, 056h, 08Dh, 04Bh, 034h
    call ?first@Gen_00943CF0@@AAEXPAXPAH11@Z
    db 08Bh, 08Eh, 094h, 000h, 000h, 000h, 085h, 0C9h, 08Bh, 07Ch, 024h, 018h, 08Bh, 05Ch, 024h, 01Ch
    db 08Bh, 06Ch, 024h, 020h, 07Ch, 01Dh, 08Bh, 0C5h, 0C1h, 0E0h, 00Ah, 00Bh, 0C3h, 0C1h, 0E0h, 00Ah
    db 00Bh, 0C7h, 03Bh, 0C1h, 074h, 01Dh, 08Bh, 04Ch, 024h, 010h, 056h, 083h, 0C1h, 034h
    call ?unlink@Gen_00943CF0@@AAEXPAX@Z
    db 08Bh, 04Ch, 024h, 010h, 057h, 053h, 055h, 056h, 083h, 0C1h, 034h
    call ?second@Gen_00943CF0@@AAEXPAX000@Z
    db 08Bh, 044h, 024h, 02Ch, 08Bh, 040h, 004h, 03Bh, 044h, 024h, 024h, 08Bh, 05Ch, 024h, 010h, 089h
    db 044h, 024h, 02Ch, 00Fh, 085h, 07Ah, 0FFh, 0FFh, 0FFh, 08Dh, 0B3h, 0BCh, 000h, 000h, 000h, 08Dh
    db 07Eh, 004h, 090h, 08Bh, 046h, 008h, 03Bh, 0C7h, 074h, 015h, 08Bh, 040h, 00Ch, 085h, 0C0h, 074h
    db 00Eh, 083h, 0C0h, 0F8h, 074h, 009h, 08Bh, 0CEh
    call ?Internal_Remove_List_Head@GenericMultiListClass@@IAEPAVMultiListObjectClass@@XZ
    db 0EBh, 0E4h, 08Bh, 083h, 004h, 001h, 000h, 000h, 08Dh, 0BBh, 0ECh, 000h, 000h, 000h, 040h, 08Bh
    db 0CFh, 089h, 083h, 004h, 001h, 000h, 000h, 089h, 07Ch, 024h, 010h
    call ?j_00009165@@YAXXZ
    db 033h, 0C0h, 089h, 044h, 024h, 014h, 08Bh, 06Ch, 024h, 040h, 050h, 055h, 08Dh, 04Ch, 024h, 01Ch
    db 051h, 08Dh, 04Bh, 034h, 089h, 044h, 024h, 044h
    call ?rva00944430@Rva00944430@@AAEXPAPAXPAVCameraClass@@PBM@Z
    db 08Bh, 074h, 024h, 014h, 085h, 0F6h, 089h, 074h, 024h, 040h, 074h, 079h, 08Bh, 054h, 024h, 040h
    db 08Bh, 072h, 004h, 08Bh, 006h, 08Bh, 0CEh, 0FFh, 090h, 09Ch, 001h, 000h, 000h, 085h, 0C0h, 075h
    db 02Ch, 08Bh, 016h, 08Bh, 0CEh, 0FFh, 092h, 000h, 001h, 000h, 000h, 08Bh, 0CDh, 08Bh, 0F8h
    call ?Update_Frustum@CameraClass@@IBEXXZ
    db 08Dh, 085h, 004h, 001h, 000h, 000h, 057h, 050h
    call ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVSphereClass@@@Z
    db 08Bh, 07Ch, 024h, 018h, 083h, 0C4h, 008h, 083h, 0F8h, 001h, 074h, 026h, 06Ah, 001h, 08Dh, 046h
    db 008h, 050h, 08Bh, 0CFh
    call ?Internal_Add@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@_N@Z
    db 03Ch, 001h, 075h, 003h, 0FFh, 046h, 004h, 08Bh, 083h, 004h, 001h, 000h, 000h, 08Bh, 016h, 050h
    db 053h, 08Bh, 0CEh, 0FFh, 092h, 088h, 001h, 000h, 000h, 08Bh, 04Ch, 024h, 040h, 08Bh, 001h, 085h
    db 0C0h, 089h, 044h, 024h, 040h, 075h, 08Bh, 08Bh, 074h, 024h, 014h, 08Bh, 0ABh, 0DCh, 000h, 000h
    db 000h, 081h, 0C3h, 0D8h, 000h, 000h, 000h, 03Bh, 0EBh, 074h, 037h, 08Dh, 064h, 024h, 000h, 08Bh
    db 045h, 00Ch, 085h, 0C0h, 074h, 00Ch, 08Dh, 070h, 0F8h, 085h, 0F6h, 074h, 007h, 08Dh, 046h, 008h
    db 0EBh, 004h, 033h, 0F6h, 033h, 0C0h, 06Ah, 001h, 050h, 08Bh, 0CFh
    call ?Internal_Add@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@_N@Z
    db 03Ch, 001h, 075h, 003h, 0FFh, 046h, 004h, 08Bh, 06Dh, 004h, 03Bh, 0EBh, 075h, 0D1h, 08Bh, 074h
    db 024h, 014h, 085h, 0F6h, 0C7h, 044h, 024h, 038h, 0FFh, 0FFh, 0FFh, 0FFh, 074h, 014h, 090h, 08Bh
    db 0C6h, 08Bh, 036h, 06Ah, 008h, 050h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 085h, 0F6h, 075h, 0EDh, 08Bh, 04Ch, 024h, 030h, 05Fh, 05Eh, 05Dh, 05Bh, 064h
    db 089h, 00Dh, 000h, 000h, 000h, 000h, 083h, 0C4h, 02Ch, 0C2h, 004h, 000h
?method@Rva00944690Scene@@UAEXPAVCameraClass@@@Z ENDP
_TEXT$d00d44690 ENDS
_TEXT SEGMENT
_TEXT ENDS
END
