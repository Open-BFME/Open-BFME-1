.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_7BfmeVolumetricShadowBufferOwner@@6B@:BYTE
EXTERN ??_U@YAPAXI@Z:NEAR
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?Get_Deformed_Vertices@BfmeShadowMesh@@QAEXPAVVector3@@@Z:NEAR
EXTERN ?Get_Model@MeshClass@@QAEPAVMeshModelClass@@XZ:NEAR
EXTERN ?Get_Position@RenderObjClass@@QBE?AVVector3@@XZ:NEAR
EXTERN ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVAABoxClass@@@Z:NEAR
EXTERN ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVSphereClass@@@Z:NEAR
EXTERN ?Rva00ED6848IdentityMatrix@@3VMatrix3D@@A:BYTE
EXTERN ?ShadowPoolA@@3UShadowPool@@A:BYTE
EXTERN ?ShadowPoolALimit@@3HA:BYTE
EXTERN ?TheAlpha@@3PAVGenAlpha@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?g_bfmeShadowPoolA@@3UBfmeShadowPoolFM@@A:BYTE
EXTERN ?g_bfmeStrStrVMZ@@3P6APADPBD0@ZA:BYTE
EXTERN ?g_pathfindDoubleCellSize@@3MB:BYTE
EXTERN ?j_0000af38@@YAXXZ:NEAR
EXTERN ?j_0000c392@@YAXXZ:NEAR
EXTERN ?j_0002a2f2@@YAXXZ:NEAR
EXTERN ?j_0003fc7e@@YAXXZ:NEAR
EXTERN ?shadowCameraFrustum@@3PBVFrustumClass@@B:BYTE
EXTERN g_Va01052DD0:NEAR
EXTERN g_Va01128748:BYTE
EXTERN g_Va01306F44:BYTE
EXTERN g_Va01307128:BYTE
EXTERN g_Va0130712C:BYTE
EXTERN g_Va01307130:BYTE
EXTERN g_Va01307134:BYTE
EXTERN g_Va01307138:BYTE
EXTERN g_Va0130713C:BYTE
EXTERN g_Va01307144:BYTE
EXTERN g_Va01307148:BYTE
EXTERN g_Va0130714C:BYTE
EXTERN g_Va01307150:BYTE
EXTERN g_Va01307158:BYTE
_TEXT SEGMENT

; ghidra: FUN_00bbe000  retail @ 0x007BE000 size 3726
public ?d_007be000@@YAXXZ
?d_007be000@@YAXXZ PROC
    db 81h, 0ECh, 84h, 01h, 00h, 00h, 53h, 55h, 56h, 8Bh, 0B4h, 24h, 9Ch, 01h, 00h, 00h
    db 8Bh, 56h, 08h, 8Bh, 06h, 89h, 94h, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 56h, 14h, 57h
    db 8Bh, 0F9h, 8Bh, 4Eh, 04h, 89h, 8Ch, 24h, 0ACh, 00h, 00h, 00h, 8Bh, 4Eh, 10h, 89h
    db 94h, 24h, 0BCh, 00h, 00h, 00h, 8Bh, 56h, 20h, 89h, 84h, 24h, 0A8h, 00h, 00h, 00h
    db 8Bh, 46h, 0Ch, 89h, 8Ch, 24h, 0B8h, 00h, 00h, 00h, 8Bh, 4Eh, 1Ch, 89h, 94h, 24h
    db 0C8h, 00h, 00h, 00h, 8Bh, 56h, 2Ch, 89h, 84h, 24h, 0B4h, 00h, 00h, 00h, 8Bh, 46h
    db 18h, 89h, 8Ch, 24h, 0C4h, 00h, 00h, 00h, 8Bh, 4Eh, 28h, 89h, 94h, 24h, 0D4h, 00h
    db 00h, 00h, 89h, 84h, 24h, 0C0h, 00h, 00h, 00h, 8Bh, 46h, 24h, 89h, 8Ch, 24h, 0D0h
    db 00h, 00h, 00h, 8Bh, 8Ch, 24h, 9Ch, 01h, 00h, 00h, 89h, 84h, 24h, 0CCh, 00h, 00h
    db 00h, 8Bh, 84h, 24h, 98h, 01h, 00h, 00h, 8Dh, 14h, 89h, 0C1h, 0E2h, 05h, 8Dh, 1Ch
    db 02h, 6Bh, 0C0h, 34h, 8Dh, 53h, 66h, 0C1h, 0E2h, 06h, 8Dh, 2Ch, 3Ah, 8Bh, 57h, 6Ch
    db 0C7h, 84h, 24h, 0D8h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 0DCh, 00h
    db 00h, 00h, 00h, 00h, 00h, 00h, 0C7h, 84h, 24h, 0E0h, 00h, 00h, 00h, 00h, 00h, 00h
    db 00h, 0C7h, 84h, 24h, 0E4h, 00h, 00h, 00h, 00h, 00h, 80h, 3Fh, 80h, 7Ch, 10h, 44h
    db 00h, 0C6h, 44h, 24h, 1Fh, 00h, 0C6h, 44h, 24h, 33h, 00h, 0C7h, 84h, 24h, 0E8h, 00h
    db 00h, 00h, 00h, 00h, 00h, 00h, 89h, 84h, 24h, 0ECh, 00h, 00h, 00h, 74h, 10h, 0C7h
    db 84h, 24h, 0E8h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 0E9h, 93h, 00h, 00h, 00h, 0D9h
    db 84h, 24h, 0B0h, 00h, 00h, 00h, 0D8h, 4Dh, 08h, 0D9h, 84h, 24h, 0ACh, 00h, 00h, 00h
    db 0D8h, 4Dh, 04h, 0DEh, 0C1h, 0D9h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0D8h, 4Dh, 00h, 0DEh
    db 0C1h, 0D9h, 0E1h, 0D8h, 1Dh, 38h, 6Fh, 30h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 75h, 62h
    db 0D9h, 84h, 24h, 0C0h, 00h, 00h, 00h, 0D8h, 4Dh, 18h, 0D9h, 84h, 24h, 0BCh, 00h, 00h
    db 00h, 0D8h, 4Dh, 14h, 0DEh, 0C1h, 0D9h, 84h, 24h, 0B8h, 00h, 00h, 00h, 0D8h, 4Dh, 10h
    db 0DEh, 0C1h, 0D9h, 0E1h, 0D8h, 1Dh, 38h, 6Fh, 30h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 01h, 75h
    db 31h, 0D9h, 84h, 24h, 0D0h, 00h, 00h, 00h, 0D8h, 4Dh, 28h, 0D9h, 84h, 24h, 0CCh, 00h
    db 00h, 00h, 0D8h, 4Dh, 24h, 0DEh, 0C1h, 0D9h, 84h, 24h, 0C8h, 00h, 00h, 00h, 0D8h, 4Dh
    db 20h, 0DEh, 0C1h, 0D9h, 0E1h, 0D8h, 1Dh, 38h, 6Fh, 30h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 7Ah, 05h, 0C6h, 44h, 24h, 1Fh, 01h, 51h, 8Bh, 0Dh, 0ECh, 6Eh, 30h, 01h, 0E8h, 0FDh
    db 0DCh, 84h, 0FFh, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Bh, 08h, 0D9h, 47h, 74h, 8Bh, 50h
    db 04h, 0DAh, 0E9h, 8Bh, 40h, 08h, 89h, 44h, 24h, 40h, 8Bh, 46h, 2Ch, 89h, 84h, 24h
    db 90h, 00h, 00h, 00h, 0DFh, 0E0h, 89h, 4Ch, 24h, 38h, 0F6h, 0C4h, 44h, 8Bh, 4Eh, 0Ch
    db 89h, 54h, 24h, 3Ch, 8Bh, 56h, 1Ch, 89h, 8Ch, 24h, 88h, 00h, 00h, 00h, 89h, 94h
    db 24h, 8Ch, 00h, 00h, 00h, 7Bh, 2Ah, 0D9h, 44h, 24h, 3Ch, 0D8h, 4Ch, 24h, 3Ch, 0D9h
    db 44h, 24h, 38h, 0D8h, 4Ch, 24h, 38h, 0DEh, 0C1h, 0D9h, 0FAh, 0D8h, 4Fh, 74h, 0D8h, 54h
    db 24h, 40h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 5Ch, 24h, 40h, 0EBh, 02h, 0DDh
    db 0D8h, 8Dh, 8Ch, 5Bh, 80h, 04h, 00h, 00h, 0D9h, 04h, 8Fh, 8Dh, 34h, 8Fh, 0D9h, 44h
    db 24h, 38h, 89h, 0B4h, 24h, 0F0h, 00h, 00h, 00h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 7Ah, 24h, 0D9h, 46h, 04h, 0D9h, 44h, 24h, 3Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 7Ah, 14h, 0D9h, 46h, 08h, 0D9h, 44h, 24h, 40h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 0Fh, 8Bh, 0C7h, 04h, 00h, 00h, 0D9h, 84h, 24h, 88h, 00h, 00h, 00h, 0D8h, 64h, 24h
    db 38h, 0D9h, 5Ch, 24h, 20h, 8Bh, 54h, 24h, 20h, 0D9h, 84h, 24h, 8Ch, 00h, 00h, 00h
    db 89h, 54h, 24h, 4Ch, 0D8h, 64h, 24h, 3Ch, 0D9h, 5Ch, 24h, 24h, 8Bh, 44h, 24h, 24h
    db 0D9h, 84h, 24h, 90h, 00h, 00h, 00h, 89h, 44h, 24h, 50h, 0D8h, 64h, 24h, 40h, 0D9h
    db 5Ch, 24h, 28h, 8Bh, 4Ch, 24h, 28h, 0D9h, 44h, 24h, 28h, 89h, 4Ch, 24h, 54h, 0D8h
    db 4Ch, 24h, 28h, 0D9h, 44h, 24h, 24h, 0D8h, 4Ch, 24h, 24h, 0DEh, 0C1h, 0D9h, 44h, 24h
    db 20h, 0D8h, 4Ch, 24h, 20h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 58h, 0D9h, 05h, 50h, 53h, 07h
    db 01h, 0D9h, 44h, 24h, 58h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 2Ah, 8Bh, 54h
    db 24h, 58h, 52h, 0E8h, 5Bh, 97h, 86h, 0FFh, 0D9h, 44h, 24h, 20h, 0D8h, 0C9h, 0D9h, 5Ch
    db 24h, 4Ch, 0D9h, 44h, 24h, 24h, 0D8h, 0C9h, 0D9h, 5Ch, 24h, 50h, 0D9h, 44h, 24h, 28h
    db 0D8h, 0C9h, 0D9h, 5Ch, 24h, 54h, 0DDh, 0D8h, 0D9h, 84h, 24h, 88h, 00h, 00h, 00h, 0D8h
    db 26h, 0D9h, 5Ch, 24h, 20h, 0D9h, 84h, 24h, 8Ch, 00h, 00h, 00h, 0D8h, 66h, 04h, 0D9h
    db 5Ch, 24h, 24h, 0D9h, 84h, 24h, 90h, 00h, 00h, 00h, 0D8h, 66h, 08h, 0D9h, 5Ch, 24h
    db 28h, 0D9h, 44h, 24h, 20h, 0D9h, 44h, 24h, 24h, 0D9h, 44h, 24h, 28h, 0D9h, 44h, 24h
    db 28h, 0D8h, 4Ch, 24h, 28h, 0D9h, 44h, 24h, 24h, 0D8h, 4Ch, 24h, 24h, 0DEh, 0C1h, 0D9h
    db 44h, 24h, 20h, 0D8h, 4Ch, 24h, 20h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 58h, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 0D9h, 44h, 24h, 58h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 28h
    db 8Bh, 44h, 24h, 58h, 0DDh, 0D8h, 0DDh, 0D8h, 50h, 0DDh, 0D8h, 0E8h, 0C3h, 96h, 86h, 0FFh
    db 0D9h, 54h, 24h, 34h, 0D8h, 4Ch, 24h, 20h, 0D9h, 44h, 24h, 24h, 0D8h, 4Ch, 24h, 34h
    db 0D9h, 44h, 24h, 28h, 0D8h, 4Ch, 24h, 34h, 0D8h, 4Ch, 24h, 54h, 0D9h, 0C9h, 0D8h, 4Ch
    db 24h, 50h, 0DEh, 0C1h, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 4Ch, 0DEh, 0C1h, 0D9h, 0E1h, 0D8h, 1Dh
    db 38h, 6Fh, 30h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 8Bh, 03h, 00h, 00h, 0C6h
    db 44h, 24h, 33h, 01h, 8Dh, 8Ch, 24h, 0A8h, 00h, 00h, 00h, 51h, 8Dh, 54h, 24h, 4Ch
    db 52h, 8Dh, 84h, 24h, 5Ch, 01h, 00h, 00h, 50h, 0E8h, 43h, 0CFh, 23h, 00h, 0D9h, 84h
    db 24h, 5Ch, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 40h, 8Bh, 84h, 24h, 0A4h, 01h, 00h, 00h
    db 0D9h, 84h, 24h, 58h, 01h, 00h, 00h, 8Bh, 50h, 04h, 0D8h, 4Ch, 24h, 3Ch, 8Bh, 08h
    db 89h, 54h, 24h, 60h, 8Bh, 50h, 0Ch, 0DEh, 0C1h, 89h, 4Ch, 24h, 5Ch, 0D9h, 84h, 24h
    db 54h, 01h, 00h, 00h, 8Bh, 48h, 08h, 0D8h, 4Ch, 24h, 38h, 89h, 54h, 24h, 68h, 8Bh
    db 50h, 14h, 89h, 4Ch, 24h, 64h, 0DEh, 0C1h, 8Bh, 48h, 10h, 89h, 4Ch, 24h, 6Ch, 89h
    db 54h, 24h, 70h, 0D8h, 84h, 24h, 60h, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 9Ch, 00h, 00h
    db 00h, 0D9h, 84h, 24h, 6Ch, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 40h, 0D9h, 84h, 24h, 68h
    db 01h, 00h, 00h, 0D8h, 4Ch, 24h, 3Ch, 0DEh, 0C1h, 0D9h, 84h, 24h, 64h, 01h, 00h, 00h
    db 0D8h, 4Ch, 24h, 38h, 0DEh, 0C1h, 0D8h, 84h, 24h, 70h, 01h, 00h, 00h, 0D9h, 9Ch, 24h
    db 0A0h, 00h, 00h, 00h, 0D9h, 84h, 24h, 7Ch, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 40h, 0D9h
    db 84h, 24h, 78h, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 3Ch, 0DEh, 0C1h, 0D9h, 84h, 24h, 74h
    db 01h, 00h, 00h, 0D8h, 4Ch, 24h, 38h, 0DEh, 0C1h, 0D8h, 84h, 24h, 80h, 01h, 00h, 00h
    db 0D9h, 9Ch, 24h, 0A4h, 00h, 00h, 00h, 0D9h, 44h, 24h, 5Ch, 0D8h, 44h, 24h, 68h, 0D9h
    db 5Ch, 24h, 20h, 8Bh, 44h, 24h, 20h, 0D9h, 44h, 24h, 60h, 89h, 84h, 24h, 0F4h, 00h
    db 00h, 00h, 0D8h, 44h, 24h, 6Ch, 0D9h, 5Ch, 24h, 24h, 8Bh, 4Ch, 24h, 24h, 0D9h, 44h
    db 24h, 70h, 8Bh, 0C1h, 0D8h, 44h, 24h, 64h, 89h, 8Ch, 24h, 0F8h, 00h, 00h, 00h, 89h
    db 84h, 24h, 04h, 01h, 00h, 00h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 0D9h, 44h
    db 24h, 68h, 8Bh, 0CAh, 0DCh, 0C0h, 89h, 94h, 24h, 0FCh, 00h, 00h, 00h, 0D9h, 44h, 24h
    db 20h, 8Bh, 0C1h, 89h, 8Ch, 24h, 08h, 01h, 00h, 00h, 0D8h, 0E1h, 89h, 84h, 24h, 14h
    db 01h, 00h, 00h, 0D9h, 9Ch, 24h, 00h, 01h, 00h, 00h, 8Bh, 94h, 24h, 00h, 01h, 00h
    db 00h, 89h, 94h, 24h, 0Ch, 01h, 00h, 00h, 0D9h, 44h, 24h, 6Ch, 89h, 8Ch, 24h, 20h
    db 01h, 00h, 00h, 0DCh, 0C0h, 0D8h, 6Ch, 24h, 24h, 0D9h, 94h, 24h, 10h, 01h, 00h, 00h
    db 0D9h, 9Ch, 24h, 1Ch, 01h, 00h, 00h, 0D9h, 84h, 24h, 00h, 01h, 00h, 00h, 0D8h, 0C1h
    db 0D9h, 9Ch, 24h, 18h, 01h, 00h, 00h, 0DDh, 0D8h, 0D9h, 44h, 24h, 20h, 0D8h, 64h, 24h
    db 38h, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h, 24h, 0D8h, 64h, 24h, 3Ch, 0D9h, 94h, 24h
    db 98h, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 28h, 0D8h, 64h, 24h, 40h
    db 0D9h, 54h, 24h, 58h, 0D9h, 5Ch, 24h, 18h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h
    db 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 0DEh, 0C1h, 0D9h, 44h, 24h, 14h, 0D8h, 4Ch
    db 24h, 14h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 34h, 0D9h, 44h, 24h, 34h, 0D9h, 0FAh, 0D9h, 5Ch
    db 24h, 44h, 0D9h, 05h, 34h, 53h, 07h, 01h, 8Bh, 84h, 24h, 98h, 00h, 00h, 00h, 0D8h
    db 74h, 24h, 44h, 8Bh, 4Ch, 24h, 58h, 0D9h, 44h, 24h, 10h, 0D8h, 0C9h, 0D9h, 44h, 24h
    db 14h, 0D8h, 0CAh, 0D9h, 44h, 24h, 18h, 0D8h, 0CBh, 0D9h, 5Ch, 24h, 54h, 0D9h, 44h, 24h
    db 28h, 0D8h, 0A4h, 24h, 0A8h, 01h, 00h, 00h, 0D9h, 54h, 24h, 34h, 0D8h, 74h, 24h, 54h
    db 0D9h, 0E1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 10h
    db 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 54h, 0D8h, 4Ch, 24h, 2Ch
    db 0D9h, 44h, 24h, 10h, 0D8h, 44h, 24h, 20h, 0D9h, 44h, 24h, 14h, 0D8h, 44h, 24h, 24h
    db 89h, 44h, 24h, 14h, 0D9h, 0CAh, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h, 18h, 8Bh, 54h
    db 24h, 18h, 89h, 94h, 24h, 2Ch, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 24h, 01h, 00h, 00h
    db 0D9h, 9Ch, 24h, 28h, 01h, 00h, 00h, 0D9h, 44h, 24h, 2Ch, 0D8h, 0C9h, 0D9h, 5Ch, 24h
    db 44h, 0DDh, 0D8h, 0D9h, 84h, 24h, 00h, 01h, 00h, 00h, 0D8h, 64h, 24h, 38h, 0D9h, 54h
    db 24h, 74h, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h, 10h, 89h, 4Ch, 24h, 18h, 0D8h, 4Ch
    db 24h, 10h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 0DEh, 0C1h, 0D9h, 44h, 24h, 14h
    db 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 9Ch, 24h, 98h, 00h, 00h, 00h, 0D9h, 84h, 24h
    db 98h, 00h, 00h, 00h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 05h, 34h, 53h, 07h, 01h
    db 0D8h, 74h, 24h, 2Ch, 0D9h, 44h, 24h, 10h, 0D8h, 0C9h, 0D9h, 44h, 24h, 14h, 0D8h, 0CAh
    db 0D9h, 44h, 24h, 18h, 0D8h, 0CBh, 0D9h, 5Ch, 24h, 54h, 0D9h, 44h, 24h, 34h, 0D8h, 74h
    db 24h, 54h, 0D9h, 0E1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch
    db 24h, 10h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 2Ch, 0D8h, 4Ch
    db 24h, 54h, 0D9h, 44h, 24h, 10h, 0D8h, 84h, 24h, 00h, 01h, 00h, 00h, 0D9h, 44h, 24h
    db 14h, 0D8h, 44h, 24h, 24h, 0D9h, 0CAh, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h, 18h, 8Bh
    db 54h, 24h, 18h, 89h, 94h, 24h, 38h, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 30h, 01h, 00h
    db 00h, 0D9h, 9Ch, 24h, 34h, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 2Ch, 0D8h, 54h, 24h, 44h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 52h, 0D9h, 5Ch, 24h, 44h, 0EBh, 4Eh, 0D9h, 84h, 24h
    db 90h, 00h, 00h, 00h, 0D8h, 65h, 2Ch, 0D9h, 0E1h, 0D8h, 1Dh, 70h, 5Ch, 07h, 01h, 0DFh
    db 0E0h, 0F6h, 0C4h, 41h, 0Fh, 84h, 75h, 0FCh, 0FFh, 0FFh, 8Ah, 44h, 24h, 1Fh, 84h, 0C0h
    db 0Fh, 85h, 6Eh, 0FCh, 0FFh, 0FFh, 8Bh, 0BCh, 9Fh, 80h, 00h, 00h, 00h, 85h, 0FFh, 0Fh
    db 84h, 1Ch, 07h, 00h, 00h, 0C7h, 47h, 44h, 08h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 5Bh
    db 81h, 0C4h, 84h, 01h, 00h, 00h, 0C2h, 14h, 00h, 0DDh, 0D8h, 0D9h, 84h, 24h, 10h, 01h
    db 00h, 00h, 8Bh, 44h, 24h, 74h, 0D8h, 64h, 24h, 3Ch, 8Bh, 4Ch, 24h, 58h, 89h, 44h
    db 24h, 10h, 89h, 4Ch, 24h, 18h, 0D9h, 94h, 24h, 94h, 00h, 00h, 00h, 0D9h, 5Ch, 24h
    db 14h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch, 24h, 10h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h
    db 18h, 0DEh, 0C1h, 0D9h, 44h, 24h, 14h, 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 5Ch, 24h
    db 74h, 0D9h, 44h, 24h, 74h, 0D9h, 0FAh, 0D9h, 9Ch, 24h, 98h, 00h, 00h, 00h, 0D9h, 05h
    db 34h, 53h, 07h, 01h, 0D8h, 0B4h, 24h, 98h, 00h, 00h, 00h, 0D9h, 44h, 24h, 10h, 0D8h
    db 0C9h, 0D9h, 44h, 24h, 14h, 0D8h, 0CAh, 0D9h, 44h, 24h, 18h, 0D8h, 0CBh, 0D9h, 5Ch, 24h
    db 54h, 0D9h, 44h, 24h, 34h, 0D8h, 74h, 24h, 54h, 0D9h, 0E1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h
    db 0C9h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 10h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h
    db 14h, 0D9h, 44h, 24h, 54h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 44h, 24h, 10h, 0D8h, 84h, 24h
    db 00h, 01h, 00h, 00h, 0D9h, 44h, 24h, 14h, 0D8h, 84h, 24h, 10h, 01h, 00h, 00h, 0D9h
    db 0CAh, 0D8h, 44h, 24h, 28h, 0D9h, 5Ch, 24h, 18h, 8Bh, 54h, 24h, 18h, 89h, 94h, 24h
    db 44h, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 3Ch, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 40h, 01h
    db 00h, 00h, 0D8h, 4Ch, 24h, 2Ch, 0D8h, 54h, 24h, 44h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 06h, 0D9h, 5Ch, 24h, 44h, 0EBh, 02h, 0DDh, 0D8h, 0D9h, 84h, 24h, 18h, 01h, 00h, 00h
    db 8Bh, 4Ch, 24h, 58h, 0D8h, 64h, 24h, 38h, 8Bh, 84h, 24h, 94h, 00h, 00h, 00h, 89h
    db 4Ch, 24h, 18h, 89h, 44h, 24h, 14h, 0D9h, 5Ch, 24h, 10h, 0D9h, 44h, 24h, 10h, 0D8h
    db 4Ch, 24h, 10h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 0DEh, 0C1h, 0D9h, 44h, 24h
    db 14h, 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 9Ch, 24h, 94h, 00h, 00h, 00h, 0D9h, 84h
    db 24h, 94h, 00h, 00h, 00h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 74h, 0D9h, 05h, 34h, 53h, 07h
    db 01h, 0D8h, 74h, 24h, 74h, 0D9h, 44h, 24h, 10h, 0D8h, 0C9h, 0D9h, 44h, 24h, 14h, 0D8h
    db 0CAh, 0D9h, 44h, 24h, 18h, 0D8h, 0CBh, 0D9h, 5Ch, 24h, 54h, 0D9h, 44h, 24h, 34h, 0D8h
    db 74h, 24h, 54h, 0D9h, 0E1h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 2Ch, 0D9h
    db 5Ch, 24h, 10h, 0D8h, 4Ch, 24h, 2Ch, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 2Ch, 0D8h
    db 4Ch, 24h, 54h, 0D9h, 44h, 24h, 10h, 0D8h, 84h, 24h, 18h, 01h, 00h, 00h, 0D9h, 44h
    db 24h, 14h, 0D8h, 84h, 24h, 10h, 01h, 00h, 00h, 0D9h, 0CAh, 0D8h, 44h, 24h, 28h, 0D9h
    db 5Ch, 24h, 54h, 8Bh, 54h, 24h, 54h, 89h, 94h, 24h, 50h, 01h, 00h, 00h, 0D9h, 9Ch
    db 24h, 48h, 01h, 00h, 00h, 0D9h, 9Ch, 24h, 4Ch, 01h, 00h, 00h, 0D8h, 4Ch, 24h, 2Ch
    db 0D8h, 54h, 24h, 44h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 06h, 0D9h, 5Ch, 24h, 44h, 0EBh
    db 02h, 0DDh, 0D8h, 8Bh, 4Ch, 24h, 24h, 0D9h, 44h, 24h, 28h, 8Bh, 54h, 24h, 28h, 8Bh
    db 44h, 24h, 20h, 89h, 4Ch, 24h, 14h, 89h, 54h, 24h, 18h, 89h, 4Ch, 24h, 50h, 89h
    db 44h, 24h, 10h, 89h, 44h, 24h, 4Ch, 8Dh, 8Ch, 24h, 04h, 01h, 00h, 00h, 0BAh, 07h
    db 00h, 00h, 00h, 0D9h, 44h, 24h, 10h, 0D8h, 59h, 0FCh, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h
    db 07h, 8Bh, 41h, 0FCh, 89h, 44h, 24h, 10h, 0D9h, 44h, 24h, 14h, 0D8h, 19h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 06h, 8Bh, 01h, 89h, 44h, 24h, 14h, 0D9h, 44h, 24h, 18h, 0D8h
    db 59h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 07h, 8Bh, 41h, 04h, 89h, 44h, 24h, 18h
    db 0D9h, 44h, 24h, 4Ch, 0D8h, 59h, 0FCh, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 07h, 8Bh, 41h
    db 0FCh, 89h, 44h, 24h, 4Ch, 0D9h, 44h, 24h, 50h, 0D8h, 19h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 7Ah, 06h, 8Bh, 01h, 89h, 44h, 24h, 50h, 0D8h, 51h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 05h
    db 7Ah, 05h, 0DDh, 0D8h, 0D9h, 41h, 04h, 83h, 0C1h, 0Ch, 4Ah, 75h, 86h, 0D9h, 44h, 24h
    db 4Ch, 0D8h, 44h, 24h, 10h, 0D9h, 44h, 24h, 50h, 0D8h, 44h, 24h, 14h, 0D9h, 5Ch, 24h
    db 24h, 0D9h, 0C1h, 0D8h, 44h, 24h, 18h, 0D9h, 5Ch, 24h, 28h, 0D8h, 0Dh, 3Ch, 53h, 07h
    db 01h, 0D9h, 44h, 24h, 24h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 44h, 24h, 28h, 0D8h
    db 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 5Ch, 24h, 28h, 0D9h, 0C9h, 8Bh, 4Ch, 24h, 28h, 0D9h
    db 5Ch, 24h, 5Ch, 89h, 4Ch, 24h, 64h, 0D9h, 5Ch, 24h, 60h, 0D9h, 44h, 24h, 4Ch, 0D8h
    db 64h, 24h, 10h, 0D9h, 5Ch, 24h, 20h, 0D9h, 44h, 24h, 50h, 0D8h, 64h, 24h, 14h, 0D9h
    db 5Ch, 24h, 24h, 0D8h, 64h, 24h, 18h, 0D9h, 44h, 24h, 20h, 0D8h, 0Dh, 3Ch, 53h, 07h
    db 01h, 0D9h, 44h, 24h, 24h, 0D8h, 0Dh, 3Ch, 53h, 07h, 01h, 0D9h, 0CAh, 0D8h, 0Dh, 3Ch
    db 53h, 07h, 01h, 0D9h, 0C1h, 0D9h, 5Ch, 24h, 68h, 0D9h, 0C2h, 0D9h, 5Ch, 24h, 6Ch, 0D9h
    db 54h, 24h, 70h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 0C2h, 0D8h
    db 0CBh, 0DEh, 0C1h, 0D9h, 9Ch, 24h, 94h, 00h, 00h, 00h, 0DDh, 0D8h, 0DDh, 0D9h, 0DDh, 0D8h
    db 0D9h, 84h, 24h, 94h, 00h, 00h, 00h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 74h, 8Bh, 44h, 24h
    db 60h, 8Bh, 4Ch, 24h, 64h, 8Bh, 54h, 24h, 5Ch, 89h, 44h, 24h, 7Ch, 8Dh, 44h, 24h
    db 78h, 89h, 8Ch, 24h, 80h, 00h, 00h, 00h, 8Bh, 0Dh, 0E8h, 6Eh, 30h, 01h, 89h, 54h
    db 24h, 78h, 8Bh, 54h, 24h, 74h, 50h, 51h, 89h, 94h, 24h, 8Ch, 00h, 00h, 00h, 0E8h
    db 6Ch, 0C5h, 11h, 00h, 83h, 0C4h, 08h, 83h, 0F8h, 08h, 75h, 13h, 0A1h, 0E8h, 6Eh, 30h
    db 01h, 8Dh, 54h, 24h, 5Ch, 52h, 50h, 0E8h, 74h, 0C8h, 11h, 00h, 83h, 0C4h, 08h, 83h
    db 0F8h, 01h, 0Fh, 84h, 85h, 02h, 00h, 00h, 8Bh, 0B4h, 24h, 98h, 01h, 00h, 00h, 66h
    db 83h, 0BCh, 77h, 00h, 44h, 00h, 00h, 00h, 74h, 13h, 8Bh, 4Fh, 6Ch, 8Bh, 94h, 24h
    db 0ECh, 00h, 00h, 00h, 8Dh, 4Ch, 0Ah, 14h, 0E8h, 0B4h, 0E6h, 85h, 0FFh, 8Dh, 84h, 24h
    db 9Ch, 00h, 00h, 00h, 50h, 56h, 8Bh, 0CFh, 66h, 0C7h, 84h, 77h, 00h, 44h, 00h, 00h
    db 00h, 00h, 0E8h, 84h, 83h, 86h, 0FFh, 8Bh, 84h, 9Fh, 80h, 00h, 00h, 00h, 85h, 0C0h
    db 75h, 18h, 8Bh, 8Ch, 24h, 0E8h, 00h, 00h, 00h, 8Bh, 94h, 24h, 9Ch, 01h, 00h, 00h
    db 51h, 56h, 52h, 8Bh, 0CFh, 0E8h, 2Ch, 7Dh, 85h, 0FFh, 8Bh, 84h, 9Fh, 00h, 03h, 00h
    db 00h, 85h, 0C0h, 74h, 3Fh, 8Ah, 44h, 24h, 1Fh, 84h, 0C0h, 75h, 0Ah, 8Ah, 44h, 24h
    db 33h, 84h, 0C0h, 74h, 2Fh, 0EBh, 0Bh, 8Bh, 84h, 9Fh, 80h, 00h, 00h, 00h, 83h, 48h
    db 18h, 01h, 8Bh, 84h, 24h, 9Ch, 01h, 00h, 00h, 56h, 50h, 8Bh, 0CFh, 0E8h, 90h, 12h
    db 86h, 0FFh, 8Bh, 8Ch, 24h, 9Ch, 01h, 00h, 00h, 6Ah, 00h, 56h, 51h, 8Bh, 0CFh, 0E8h
    db 0E2h, 7Ch, 85h, 0FFh, 8Bh, 94h, 9Fh, 80h, 00h, 00h, 00h, 8Ah, 42h, 18h, 8Bh, 4Ch
    db 24h, 44h, 56h, 0A8h, 01h, 8Bh, 84h, 24h, 0A0h, 01h, 00h, 00h, 50h, 51h, 8Dh, 94h
    db 24h, 0A8h, 00h, 00h, 00h, 8Bh, 0CFh, 52h, 74h, 07h, 0E8h, 0CCh, 0D1h, 84h, 0FFh, 0EBh
    db 05h, 0E8h, 85h, 41h, 87h, 0FFh, 8Bh, 84h, 24h, 0A8h, 00h, 00h, 00h, 0D9h, 84h, 24h
    db 88h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 0ACh, 00h, 00h, 00h, 0D9h, 0E0h, 8Bh, 94h, 24h
    db 0B0h, 00h, 00h, 00h, 0D9h, 84h, 24h, 8Ch, 00h, 00h, 00h, 89h, 45h, 00h, 0D9h, 0E0h
    db 8Bh, 84h, 24h, 0B4h, 00h, 00h, 00h, 0D9h, 9Ch, 24h, 0A0h, 00h, 00h, 00h, 89h, 4Dh
    db 04h, 0D9h, 84h, 24h, 90h, 00h, 00h, 00h, 8Bh, 8Ch, 24h, 0B8h, 00h, 00h, 00h, 0D9h
    db 0E0h, 89h, 55h, 08h, 0D9h, 9Ch, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 94h, 24h, 0BCh, 00h
    db 00h, 00h, 0D8h, 44h, 24h, 5Ch, 89h, 45h, 0Ch, 8Bh, 84h, 24h, 0C0h, 00h, 00h, 00h
    db 0D9h, 84h, 24h, 0A0h, 00h, 00h, 00h, 0D8h, 44h, 24h, 60h, 89h, 4Dh, 10h, 8Bh, 8Ch
    db 24h, 0C4h, 00h, 00h, 00h, 89h, 55h, 14h, 8Bh, 94h, 24h, 0C8h, 00h, 00h, 00h, 0D9h
    db 5Ch, 24h, 60h, 89h, 45h, 18h, 0D9h, 84h, 24h, 0A4h, 00h, 00h, 00h, 8Bh, 84h, 24h
    db 0CCh, 00h, 00h, 00h, 0D8h, 44h, 24h, 64h, 89h, 4Dh, 1Ch, 8Bh, 8Ch, 24h, 0D0h, 00h
    db 00h, 00h, 89h, 55h, 20h, 0D9h, 5Ch, 24h, 64h, 8Bh, 94h, 24h, 0D4h, 00h, 00h, 00h
    db 89h, 45h, 24h, 8Bh, 84h, 24h, 0D8h, 00h, 00h, 00h, 89h, 4Dh, 28h, 8Bh, 8Ch, 24h
    db 0DCh, 00h, 00h, 00h, 89h, 55h, 2Ch, 8Bh, 94h, 24h, 0E0h, 00h, 00h, 00h, 89h, 45h
    db 30h, 8Bh, 84h, 24h, 0E4h, 00h, 00h, 00h, 89h, 4Dh, 34h, 8Bh, 4Ch, 24h, 38h, 89h
    db 55h, 38h, 8Bh, 54h, 24h, 3Ch, 89h, 45h, 3Ch, 8Bh, 84h, 24h, 0F0h, 00h, 00h, 00h
    db 89h, 08h, 8Bh, 4Ch, 24h, 40h, 89h, 50h, 04h, 89h, 48h, 08h, 8Bh, 84h, 9Fh, 80h
    db 00h, 00h, 00h, 0D9h, 58h, 1Ch, 8Bh, 54h, 24h, 60h, 89h, 50h, 20h, 8Bh, 4Ch, 24h
    db 64h, 83h, 0C0h, 1Ch, 89h, 48h, 08h, 8Bh, 54h, 24h, 68h, 89h, 50h, 0Ch, 8Bh, 4Ch
    db 24h, 6Ch, 89h, 48h, 10h, 8Bh, 54h, 24h, 70h, 89h, 50h, 14h, 0D9h, 44h, 24h, 78h
    db 0D8h, 0A4h, 24h, 88h, 00h, 00h, 00h, 8Bh, 84h, 9Fh, 80h, 00h, 00h, 00h, 0D9h, 44h
    db 24h, 7Ch, 83h, 0C0h, 34h, 0D8h, 0A4h, 24h, 8Ch, 00h, 00h, 00h, 0D9h, 5Ch, 24h, 7Ch
    db 0D9h, 84h, 24h, 80h, 00h, 00h, 00h, 0D8h, 0A4h, 24h, 90h, 00h, 00h, 00h, 0D9h, 9Ch
    db 24h, 80h, 00h, 00h, 00h, 0D9h, 18h, 8Bh, 4Ch, 24h, 7Ch, 89h, 48h, 04h, 8Bh, 94h
    db 24h, 80h, 00h, 00h, 00h, 89h, 50h, 08h, 8Bh, 8Ch, 24h, 84h, 00h, 00h, 00h, 89h
    db 48h, 0Ch, 8Bh, 94h, 9Fh, 80h, 00h, 00h, 00h, 5Fh, 5Eh, 5Dh, 0C7h, 42h, 44h, 02h
    db 00h, 00h, 00h, 5Bh, 81h, 0C4h, 84h, 01h, 00h, 00h, 0C2h, 14h, 00h, 8Bh, 84h, 9Fh
    db 80h, 00h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0D5h, 00h, 00h, 00h, 0D9h, 84h, 24h, 88h
    db 00h, 00h, 00h, 0D9h, 0E0h, 0D9h, 84h, 24h, 8Ch, 00h, 00h, 00h, 0D9h, 0E0h, 0D9h, 9Ch
    db 24h, 0A0h, 00h, 00h, 00h, 0D9h, 84h, 24h, 90h, 00h, 00h, 00h, 0D9h, 0E0h, 0D9h, 9Ch
    db 24h, 0A4h, 00h, 00h, 00h, 0D8h, 44h, 24h, 5Ch, 0D9h, 84h, 24h, 0A0h, 00h, 00h, 00h
    db 0D8h, 44h, 24h, 60h, 0D9h, 5Ch, 24h, 60h, 0D9h, 84h, 24h, 0A4h, 00h, 00h, 00h, 0D8h
    db 44h, 24h, 64h, 0D9h, 5Ch, 24h, 64h, 0D9h, 58h, 1Ch, 8Bh, 4Ch, 24h, 60h, 89h, 48h
    db 20h, 8Bh, 54h, 24h, 64h, 89h, 50h, 24h, 8Bh, 4Ch, 24h, 68h, 89h, 48h, 28h, 8Bh
    db 54h, 24h, 6Ch, 89h, 50h, 2Ch, 8Bh, 4Ch, 24h, 70h, 89h, 48h, 30h, 0D9h, 44h, 24h
    db 78h, 0D8h, 0A4h, 24h, 88h, 00h, 00h, 00h, 8Bh, 84h, 9Fh, 80h, 00h, 00h, 00h, 0D9h
    db 44h, 24h, 7Ch, 83h, 0C0h, 34h, 0D8h, 0A4h, 24h, 8Ch, 00h, 00h, 00h, 0D9h, 5Ch, 24h
    db 7Ch, 0D9h, 84h, 24h, 80h, 00h, 00h, 00h, 0D8h, 0A4h, 24h, 90h, 00h, 00h, 00h, 0D9h
    db 9Ch, 24h, 80h, 00h, 00h, 00h, 0D9h, 18h, 8Bh, 54h, 24h, 7Ch, 89h, 50h, 04h, 8Bh
    db 8Ch, 24h, 80h, 00h, 00h, 00h, 89h, 48h, 08h, 8Bh, 94h, 24h, 84h, 00h, 00h, 00h
    db 89h, 50h, 0Ch, 8Bh, 84h, 9Fh, 80h, 00h, 00h, 00h, 0C7h, 40h, 44h, 01h, 00h, 00h
    db 00h, 5Fh, 5Eh, 5Dh, 5Bh, 81h, 0C4h, 84h, 01h, 00h, 00h, 0C2h, 14h, 00h
?d_007be000@@YAXXZ ENDP

; ghidra: FUN_00bbf240  retail @ 0x007BF240 size 305
public ?d_007bf240@@YAXXZ
?d_007bf240@@YAXXZ PROC
    db 83h, 0ECh, 10h, 55h, 57h, 8Bh, 0E9h, 0E8h, 0F4h, 2Eh, 14h, 00h, 84h, 0C0h, 0Fh, 84h
    db 13h, 01h, 00h, 00h, 8Bh, 7Ch, 24h, 1Ch, 85h, 0FFh, 0Fh, 84h, 07h, 01h, 00h, 00h
    db 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 48h, 64h, 84h, 0C9h, 0Fh, 84h, 0F7h, 00h, 00h, 00h
    db 8Bh, 17h, 56h, 8Bh, 0CFh, 0FFh, 52h, 18h, 8Bh, 0F0h, 85h, 0F6h, 75h, 09h, 5Eh, 5Fh
    db 5Dh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 8Bh, 4Dh, 08h, 53h, 56h, 0E8h, 0CAh, 34h, 85h
    db 0FFh, 8Bh, 0D8h, 85h, 0DBh, 75h, 25h, 8Bh, 4Dh, 08h, 56h, 57h, 0E8h, 08h, 0BBh, 88h
    db 0FFh, 8Bh, 4Dh, 08h, 56h, 0E8h, 0B1h, 34h, 85h, 0FFh, 8Bh, 0D8h, 85h, 0DBh, 75h, 0Ch
    db 5Bh, 5Eh, 5Fh, 33h, 0C0h, 5Dh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 68h, 04h, 49h, 00h
    db 00h, 0E8h, 6Ah, 2Ch, 0Ch, 00h, 83h, 0C4h, 04h, 85h, 0C0h, 74h, 0E3h, 8Bh, 0C8h, 0E8h
    db 9Dh, 4Eh, 87h, 0FFh, 8Bh, 0F0h, 85h, 0F6h, 74h, 0D6h, 53h, 8Bh, 0CEh, 89h, 7Eh, 70h
    db 0E8h, 0A2h, 0B8h, 84h, 0FFh, 8Bh, 07h, 8Dh, 4Ch, 24h, 10h, 51h, 8Bh, 0CFh, 0FFh, 90h
    db 08h, 01h, 00h, 00h, 0D9h, 05h, 50h, 53h, 07h, 01h, 8Bh, 54h, 24h, 1Ch, 0D9h, 05h
    db 50h, 53h, 07h, 01h, 8Bh, 4Ch, 24h, 28h, 89h, 56h, 78h, 0D9h, 81h, 98h, 00h, 00h
    db 00h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 12h, 0DDh, 0D8h, 0D9h, 81h, 98h, 00h
    db 00h, 00h, 0D8h, 0Dh, 54h, 59h, 07h, 01h, 0D9h, 0F2h, 0DDh, 0D8h, 0D9h, 5Eh, 74h, 8Bh
    db 81h, 80h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 2Ch, 85h, 0C9h, 89h, 46h, 34h, 74h, 0Bh
    db 6Ah, 02h, 0E8h, 0D8h, 31h, 87h, 0FFh, 84h, 0C0h, 75h, 07h, 0C7h, 46h, 7Ch, 0CDh, 0CCh
    db 0CCh, 3Dh, 8Bh, 4Dh, 00h, 5Bh, 89h, 4Eh, 68h, 89h, 75h, 00h, 8Bh, 0C6h, 5Eh, 5Fh
    db 5Dh, 83h, 0C4h, 10h, 0C2h, 0Ch, 00h, 5Fh, 33h, 0C0h, 5Dh, 83h, 0C4h, 10h, 0C2h, 0Ch
    db 00h
?d_007bf240@@YAXXZ ENDP

; ghidra: FUN_00bbf3c0  retail @ 0x007BF3C0 size 824
_TEXT ENDS
_TEXT$d00bbf3c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BBF3C0 size 824
public ?d_007bf3c0@@YAXXZ
?d_007bf3c0@@YAXXZ PROC
    db 083h, 0ECh, 038h, 0A1h
    dd g_Va01307158
    db 0A8h, 001h, 053h, 055h, 056h, 08Bh, 0F1h, 08Bh, 06Eh, 070h, 089h, 06Ch, 024h, 01Ch, 075h, 008h
    db 083h, 0C8h, 001h, 0A3h
    dd g_Va01307158
    db 0A8h, 002h, 075h, 008h, 083h, 0C8h, 002h, 0A3h
    dd g_Va01307158
    db 08Bh, 04Eh, 070h, 08Bh, 001h, 0FFh, 090h, 07Ch, 001h, 000h, 000h, 085h, 0C0h, 08Bh, 046h, 06Ch
    db 08Bh, 088h, 094h, 020h, 000h, 000h, 00Fh, 095h, 044h, 024h, 00Fh, 033h, 0DBh, 085h, 0C9h, 00Fh
    db 08Eh, 0DEh, 002h, 000h, 000h, 057h, 033h, 0FFh, 089h, 07Ch, 024h, 01Ch, 0EBh, 006h, 08Bh, 06Ch
    db 024h, 020h, 08Bh, 0FFh, 08Bh, 044h, 007h, 020h, 085h, 0C0h, 07Ch, 012h, 08Bh, 055h, 000h, 050h
    db 06Ah, 000h, 08Bh, 0CDh, 0FFh, 092h, 02Ch, 002h, 000h, 000h, 08Bh, 0E8h, 0EBh, 003h, 08Bh, 06Eh
    db 070h, 085h, 0EDh, 00Fh, 084h, 08Ch, 002h, 000h, 000h, 08Bh, 045h, 000h, 08Bh, 0CDh, 0FFh, 090h
    db 080h, 001h, 000h, 000h, 085h, 0C0h, 00Fh, 084h, 079h, 002h, 000h, 000h, 08Bh, 04Eh, 06Ch, 08Bh
    db 045h, 000h, 08Dh, 054h, 00Fh, 014h, 08Bh, 0CDh, 089h, 054h, 024h, 014h, 0FFh, 050h, 050h, 08Bh
    db 04Ch, 024h, 014h, 08Ah, 041h, 030h, 084h, 0C0h, 08Dh, 07Dh, 018h, 0C7h, 044h, 024h, 018h, 000h
    db 000h, 000h, 000h, 074h, 06Fh, 08Bh, 055h, 000h, 08Bh, 0CDh, 0FFh, 052h, 00Ch, 085h, 0C0h, 075h
    db 063h, 08Bh, 07Ch, 024h, 014h, 08Bh, 047h, 018h, 039h, 005h
    dd g_Va01306F44
    db 07Dh, 023h, 06Ah, 000h, 050h, 0B9h
    dd ?ShadowPoolA@@3UShadowPool@@A
    call ?j_0003fc7e@@YAXXZ
    db 084h, 0C0h, 074h, 012h, 0A1h
    dd g_Va01306F44
    db 03Bh, 005h
    dd ?ShadowPoolALimit@@3HA
    db 07Dh, 005h, 0A3h
    dd ?ShadowPoolALimit@@3HA
    db 0A1h
    dd ?g_bfmeShadowPoolA@@3UBfmeShadowPoolFM@@A
    db 08Bh, 055h, 000h, 050h, 08Bh, 0CDh, 0FFh, 052h, 014h, 08Bh, 0C8h
    call ?Get_Deformed_Vertices@BfmeShadowMesh@@QAEXPAVVector3@@@Z
    db 0A1h
    dd ?g_bfmeShadowPoolA@@3UBfmeShadowPoolFM@@A
    db 089h, 047h, 008h, 0C7h, 047h, 010h, 000h, 000h, 000h, 000h, 0BFh
    dd ?Rva00ED6848IdentityMatrix@@3VMatrix3D@@A
    db 0C7h, 044h, 024h, 018h, 000h, 000h, 0C8h, 042h, 08Dh, 04Ch, 024h, 03Ch, 051h, 08Bh, 04Eh, 070h
    call ?Get_Position@RenderObjClass@@QBE?AVVector3@@XZ
    db 0D9h, 044h, 024h, 018h, 0D8h, 044h, 024h, 04Ch, 08Bh, 055h, 000h, 051h, 08Bh, 0CDh, 0D8h, 068h
    db 008h, 0D9h, 01Ch, 024h, 0FFh, 092h, 004h, 001h, 000h, 000h, 050h, 057h, 06Ah, 000h, 053h, 08Bh
    db 0CEh
    call ?j_0000c392@@YAXXZ
    db 08Bh, 084h, 09Eh, 080h, 000h, 000h, 000h, 085h, 0C0h, 00Fh, 084h, 09Fh, 001h, 000h, 000h, 083h
    db 078h, 044h, 008h, 00Fh, 085h, 045h, 001h, 000h, 000h, 08Ah, 04Ch, 024h, 013h, 084h, 0C9h, 074h
    db 00Ch, 0C7h, 040h, 044h, 002h, 000h, 000h, 000h, 0E9h, 031h, 001h, 000h, 000h, 08Bh, 048h, 034h
    db 089h, 00Dh
    dd g_Va01307144
    db 08Bh, 050h, 038h, 089h, 015h
    dd g_Va01307148
    db 08Bh, 048h, 03Ch, 089h, 00Dh
    dd g_Va0130714C
    db 08Bh, 050h, 040h, 08Bh, 00Dh
    dd ?shadowCameraFrustum@@3PBVFrustumClass@@B
    db 089h, 015h
    dd g_Va01307150
    db 0D9h, 047h, 00Ch, 0D9h, 047h, 01Ch, 08Bh, 047h, 02Ch, 0D9h, 0C9h, 089h, 044h, 024h, 02Ch, 0D8h
    db 005h
    dd g_Va01307144
    db 068h
    dd g_Va01307144
    db 051h, 0D9h, 01Dh
    dd g_Va01307144
    db 0D8h, 005h
    dd g_Va01307148
    db 0D9h, 01Dh
    dd g_Va01307148
    db 0D9h, 044h, 024h, 034h, 0D8h, 005h
    dd g_Va0130714C
    db 0D9h, 01Dh
    dd g_Va0130714C
    call ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVSphereClass@@@Z
    db 083h, 0C4h, 008h, 083h, 0F8h, 008h, 00Fh, 085h, 0AFh, 000h, 000h, 000h, 08Bh, 084h, 09Eh, 080h
    db 000h, 000h, 000h, 08Bh, 050h, 01Ch, 089h, 015h
    dd g_Va01307128
    db 08Bh, 048h, 020h, 083h, 0C0h, 01Ch, 089h, 00Dh
    dd g_Va0130712C
    db 08Bh, 050h, 008h, 089h, 015h
    dd g_Va01307130
    db 08Bh, 048h, 00Ch, 089h, 00Dh
    dd g_Va01307134
    db 08Bh, 050h, 010h, 089h, 015h
    dd g_Va01307138
    db 08Bh, 040h, 014h, 08Bh, 015h
    dd ?shadowCameraFrustum@@3PBVFrustumClass@@B
    db 0A3h
    dd g_Va0130713C
    db 0D9h, 047h, 00Ch, 0D9h, 047h, 01Ch, 08Bh, 04Fh, 02Ch, 0D9h, 0C9h, 089h, 04Ch, 024h, 038h, 0D8h
    db 005h
    dd g_Va01307128
    db 068h
    dd g_Va01307128
    db 052h, 0D9h, 01Dh
    dd g_Va01307128
    db 0D8h, 005h
    dd g_Va0130712C
    db 0D9h, 01Dh
    dd g_Va0130712C
    db 0D9h, 044h, 024h, 040h, 0D8h, 005h
    dd g_Va01307130
    db 0D9h, 01Dh
    dd g_Va01307130
    call ?Overlap_Test@CollisionMath@@SA?AW4OverlapType@1@ABVFrustumClass@@ABVAABoxClass@@@Z
    db 083h, 0C4h, 008h, 083h, 0F8h, 001h, 074h, 010h, 08Bh, 084h, 09Eh, 080h, 000h, 000h, 000h, 0C7h
    db 040h, 044h, 002h, 000h, 000h, 000h, 0EBh, 01Ah, 08Bh, 08Ch, 09Eh, 080h, 000h, 000h, 000h, 0C7h
    db 041h, 044h, 001h, 000h, 000h, 000h, 0EBh, 00Ah, 08Bh, 094h, 09Eh, 080h, 000h, 000h, 000h, 089h
    db 042h, 044h, 08Bh, 084h, 09Eh, 080h, 000h, 000h, 000h, 083h, 078h, 044h, 002h, 075h, 043h, 08Bh
    db 084h, 09Eh, 000h, 003h, 000h, 000h, 085h, 0C0h, 074h, 01Dh, 08Bh, 048h, 008h, 08Bh, 051h, 018h
    db 08Dh, 03Ch, 05Bh, 08Dh, 0BCh, 0BEh, 000h, 008h, 000h, 000h, 089h, 079h, 018h, 08Bh, 048h, 008h
    db 08Bh, 041h, 018h, 089h, 010h, 0EBh, 01Bh, 0A1h
    dd ?TheAlpha@@3PAVGenAlpha@@A
    db 08Bh, 048h, 004h, 083h, 0C0h, 004h, 08Dh, 014h, 05Bh, 08Dh, 094h, 096h, 000h, 008h, 000h, 000h
    db 089h, 010h, 08Bh, 0C2h, 089h, 008h, 08Bh, 07Ch, 024h, 01Ch, 08Bh, 046h, 06Ch, 08Bh, 088h, 094h
    db 020h, 000h, 000h, 043h, 083h, 0C7h, 034h, 03Bh, 0D9h, 089h, 07Ch, 024h, 01Ch, 00Fh, 08Ch, 02Ch
    db 0FDh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 038h, 0C2h, 004h, 000h
?d_007bf3c0@@YAXXZ ENDP
_TEXT$d00bbf3c0 ENDS
_TEXT SEGMENT

; ghidra: FUN_00bc0540  retail @ 0x007C0540 size 119
public ?d_007c0540@@YAXXZ
?d_007c0540@@YAXXZ PROC
    db 51h, 56h, 8Bh, 0F1h, 8Bh, 06h, 57h, 8Bh, 7Eh, 0Ch, 8Dh, 54h, 24h, 08h, 0C7h, 46h
    db 10h, 00h, 00h, 00h, 00h, 8Bh, 88h, 0C8h, 00h, 00h, 00h, 52h, 0E8h, 0BFh, 82h, 16h
    db 00h, 8Bh, 4Ch, 24h, 08h, 85h, 0C9h, 74h, 4Ah, 53h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 4Eh, 08h, 8Bh, 50h, 08h, 8Ah, 14h, 11h, 8Bh, 58h, 0Ch, 3Ah, 14h, 19h, 74h
    db 21h, 84h, 0D2h, 74h, 09h, 8Bh, 08h, 89h, 0Fh, 8Bh, 50h, 04h, 0EBh, 07h, 8Bh, 48h
    db 04h, 89h, 0Fh, 8Bh, 10h, 89h, 57h, 04h, 8Bh, 4Eh, 10h, 83h, 0C7h, 08h, 41h, 89h
    db 4Eh, 10h, 8Bh, 4Ch, 24h, 0Ch, 49h, 83h, 0C0h, 10h, 85h, 0C9h, 89h, 4Ch, 24h, 0Ch
    db 75h, 0BEh, 5Bh, 5Fh, 5Eh, 59h, 0C3h
?d_007c0540@@YAXXZ ENDP

; ghidra: FUN_00bc0ea0  retail @ 0x007C0EA0 size 142
public ?d_007c0ea0@@YAXXZ
?d_007c0ea0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 74h, 8Dh, 44h, 24h, 04h, 50h, 0E8h, 0Dh
    db 0F4h, 15h, 00h, 0D9h, 44h, 24h, 04h, 8Bh, 4Ch, 24h, 14h, 0D8h, 86h, 80h, 00h, 00h
    db 00h, 0D9h, 01h, 0D8h, 61h, 0Ch, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 56h, 0D9h
    db 44h, 24h, 04h, 0D8h, 0A6h, 80h, 00h, 00h, 00h, 0D9h, 41h, 0Ch, 0D8h, 01h, 0DEh, 0D9h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 3Eh, 0D9h, 44h, 24h, 08h, 0D8h, 86h, 80h, 00h, 00h
    db 00h, 0D9h, 41h, 04h, 0D8h, 61h, 10h, 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 25h
    db 0D9h, 44h, 24h, 08h, 0D8h, 0A6h, 80h, 00h, 00h, 00h, 0D9h, 41h, 10h, 0D8h, 41h, 04h
    db 0DEh, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 0Ch, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 83h
    db 0C4h, 0Ch, 0C2h, 04h, 00h, 33h, 0C0h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_007c0ea0@@YAXXZ ENDP

; ghidra: FUN_00bc0f60  retail @ 0x007C0F60 size 295
public ?d_007c0f60@@YAXXZ
?d_007c0f60@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 74h, 8Dh, 44h, 24h, 04h, 50h, 0E8h, 4Dh
    db 0F3h, 15h, 00h, 0D9h, 44h, 24h, 0Ch, 0D8h, 86h, 84h, 00h, 00h, 00h, 8Bh, 4Ch, 24h
    db 14h, 0D8h, 59h, 08h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 09h, 32h, 0C0h, 5Eh, 83h, 0C4h
    db 0Ch, 0C2h, 04h, 00h, 0D9h, 86h, 90h, 00h, 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0D9h, 86h, 90h, 00h, 00h, 00h, 0EBh, 06h, 0D9h
    db 05h, 50h, 53h, 07h, 01h, 0D8h, 86h, 80h, 00h, 00h, 00h, 0D8h, 44h, 24h, 04h, 0D8h
    db 19h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 0Fh, 85h, 0B2h, 00h, 00h, 00h, 0D9h, 86h, 90h, 00h
    db 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0D9h
    db 86h, 90h, 00h, 00h, 00h, 0EBh, 06h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h
    db 04h, 0D8h, 0A6h, 80h, 00h, 00h, 00h, 0D8h, 0C1h, 0D8h, 19h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h
    db 0C4h, 05h, 7Ah, 7Ah, 0D9h, 86h, 94h, 00h, 00h, 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 0D9h, 86h, 94h, 00h, 00h, 00h, 0EBh, 06h, 0D9h
    db 05h, 50h, 53h, 07h, 01h, 0D8h, 86h, 80h, 00h, 00h, 00h, 0D8h, 44h, 24h, 08h, 0D8h
    db 59h, 04h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 45h, 0D9h, 86h, 94h, 00h, 00h, 00h, 0D8h
    db 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 08h, 0D9h, 86h, 94h, 00h
    db 00h, 00h, 0EBh, 06h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 08h, 0D8h, 0A6h
    db 80h, 00h, 00h, 00h, 0D8h, 0C1h, 0D8h, 59h, 04h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 05h
    db 7Ah, 0Ch, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h, 33h, 0C0h
    db 5Eh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_007c0f60@@YAXXZ ENDP

; ghidra: FUN_00bc10d0  retail @ 0x007C10D0 size 25
public ?d_007c10d0@@YAXXZ
?d_007c10d0@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 89h, 08h, 89h, 48h, 04h, 89h, 48h, 08h, 89h, 48h, 0Ch, 89h
    db 48h, 10h, 89h, 48h, 14h, 89h, 48h, 18h, 0C3h
?d_007c10d0@@YAXXZ ENDP

; ghidra: FUN_00bc1120  retail @ 0x007C1120 size 25
public ?d_007c1120@@YAXXZ
?d_007c1120@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 4Eh, 08h, 85h, 0C9h, 74h, 0Dh, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h
    db 8Bh, 4Eh, 08h, 85h, 0C9h, 75h, 0F3h, 5Eh, 0C3h
?d_007c1120@@YAXXZ ENDP

; ghidra: FUN_00bc1140  retail @ 0x007C1140 size 49
public ?d_007c1140@@YAXXZ
?d_007c1140@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Eh, 85h, 0C9h, 74h, 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 01h
    db 0FFh, 10h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 4Eh, 04h, 85h, 0C9h, 74h, 10h, 0FFh
    db 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Eh
    db 0C3h
?d_007c1140@@YAXXZ ENDP

; ghidra: FUN_00bc1180  retail @ 0x007C1180 size 179
public ?d_007c1180@@YAXXZ
?d_007c1180@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 56h, 2Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 83h, 3Eh, 00h, 75h, 3Ah, 6Ah, 20h
    db 0E8h, 8Bh, 0Dh, 0Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h
    db 24h, 10h, 00h, 00h, 00h, 00h, 74h, 14h, 6Ah, 00h, 6Ah, 01h, 68h, 30h, 75h, 00h
    db 00h, 6Ah, 02h, 8Bh, 0C8h, 0E8h, 26h, 0E1h, 15h, 00h, 0EBh, 02h, 33h, 0C0h, 0C7h, 44h
    db 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 06h, 8Bh, 46h, 04h, 85h, 0C0h, 75h, 42h, 6Ah
    db 18h, 0E8h, 4Ah, 0Dh, 0Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h
    db 44h, 24h, 10h, 01h, 00h, 00h, 00h, 74h, 23h, 6Ah, 01h, 68h, 30h, 75h, 00h, 00h
    db 8Bh, 0C8h, 0E8h, 99h, 0BEh, 15h, 00h, 89h, 46h, 04h, 0B0h, 01h, 5Eh, 8Bh, 4Ch, 24h
    db 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 33h, 0C0h, 89h, 46h
    db 04h, 8Bh, 4Ch, 24h, 08h, 0B0h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_007c1180@@YAXXZ ENDP

; ghidra: FUN_00bc1260  retail @ 0x007C1260 size 27
public ?d_007c1260@@YAXXZ
?d_007c1260@@YAXXZ PROC
    db 8Bh, 41h, 08h, 33h, 0C9h, 3Bh, 0C1h, 74h, 11h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 88h, 48h, 04h, 8Bh, 40h, 6Ch, 3Bh, 0C1h, 75h, 0F6h, 0C3h
?d_007c1260@@YAXXZ ENDP

; ghidra: FUN_00bc1290  retail @ 0x007C1290 size 27
public ?d_007c1290@@YAXXZ
?d_007c1290@@YAXXZ PROC
    db 8Bh, 41h, 08h, 85h, 0C0h, 74h, 13h, 0B1h, 01h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 88h, 48h, 04h, 8Bh, 40h, 6Ch, 85h, 0C0h, 75h, 0F6h, 0C3h
?d_007c1290@@YAXXZ ENDP

; ghidra: FUN_00bc12c0  retail @ 0x007C12C0 size 286
public ?d_007c12c0@@YAXXZ
?d_007c12c0@@YAXXZ PROC
    db 56h, 8Bh, 35h, 34h, 05h, 34h, 01h, 57h, 8Bh, 7Ch, 24h, 0Ch, 85h, 0FFh, 6Ah, 01h
    db 75h, 1Ah, 8Bh, 06h, 6Ah, 36h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah
    db 01h, 6Ah, 35h, 56h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 0EBh, 18h, 8Bh, 16h, 6Ah, 35h
    db 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h, 6Ah, 01h, 6Ah, 37h, 56h, 0FFh, 90h
    db 0E4h, 00h, 00h, 00h, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 8Bh, 81h, 90h, 00h, 00h, 00h
    db 0F6h, 0C4h, 01h, 0Fh, 84h, 0C0h, 00h, 00h, 00h, 8Bh, 16h, 6Ah, 01h, 68h, 0B9h, 00h
    db 00h, 00h, 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h, 6Ah, 01h, 6Ah, 16h, 56h
    db 0FFh, 90h, 0E4h, 00h, 00h, 00h, 85h, 0FFh, 75h, 52h, 8Bh, 0Eh, 6Ah, 08h, 6Ah, 37h
    db 56h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 8Bh, 16h, 6Ah, 01h, 68h, 0BBh, 00h, 00h, 00h
    db 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h, 6Ah, 01h, 68h, 0BAh, 00h, 00h, 00h
    db 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah, 07h, 68h, 0BCh, 00h, 00h, 00h
    db 56h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 8Bh, 16h, 6Ah, 08h, 68h, 0BDh, 00h, 00h, 00h
    db 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 5Fh, 5Eh, 0C2h, 04h, 00h, 8Bh, 06h, 6Ah, 07h
    db 6Ah, 36h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah, 01h, 68h, 0BAh, 00h
    db 00h, 00h, 56h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 8Bh, 16h, 6Ah, 01h, 68h, 0BCh, 00h
    db 00h, 00h, 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h, 6Ah, 08h, 68h, 0BBh, 00h
    db 00h, 00h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah, 08h, 68h, 0BDh, 00h
    db 00h, 00h, 56h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 5Fh, 5Eh, 0C2h, 04h, 00h
?d_007c12c0@@YAXXZ ENDP

; ghidra: FUN_00bc1430  retail @ 0x007C1430 size 157
public ?d_007c1430@@YAXXZ
?d_007c1430@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 86h, 2Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 6Ah, 08h, 8Bh, 0F1h, 0E8h, 0E0h, 0Ah, 0Ch, 00h
    db 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h
    db 00h, 74h, 11h, 8Bh, 0Eh, 68h, 00h, 28h, 00h, 00h, 51h, 8Bh, 0C8h, 0E8h, 0FEh, 0C8h
    db 15h, 00h, 0EBh, 02h, 33h, 0C0h, 6Ah, 08h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh
    db 89h, 46h, 0Ch, 0E8h, 0A8h, 0Ah, 0Ch, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 04h, 85h
    db 0C0h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 74h, 12h, 8Bh, 56h, 04h, 68h, 00h
    db 28h, 00h, 00h, 52h, 8Bh, 0C8h, 0E8h, 0A5h, 0B9h, 15h, 00h, 0EBh, 02h, 33h, 0C0h, 8Bh
    db 4Ch, 24h, 08h, 89h, 46h, 10h, 0B8h, 30h, 75h, 00h, 00h, 89h, 46h, 14h, 89h, 46h
    db 18h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_007c1430@@YAXXZ ENDP

; ghidra: FUN_00bc1660  retail @ 0x007C1660 size 191
public ?d_007c1660@@YAXXZ
?d_007c1660@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0A8h, 2Dh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 08h, 0C7h, 06h
    db 38h, 87h, 12h, 01h, 8Bh, 46h, 6Ch, 33h, 0DBh, 3Bh, 0C3h, 89h, 5Ch, 24h, 14h, 74h
    db 06h, 8Bh, 4Eh, 68h, 89h, 48h, 68h, 8Bh, 56h, 68h, 8Bh, 46h, 6Ch, 89h, 02h, 8Bh
    db 4Eh, 74h, 3Bh, 0CBh, 74h, 09h, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 39h
    db 5Eh, 78h, 7Eh, 48h, 57h, 33h, 0FFh, 8Bh, 46h, 7Ch, 8Bh, 0Ch, 07h, 0FFh, 49h, 04h
    db 75h, 04h, 8Bh, 11h, 0FFh, 12h, 8Bh, 46h, 7Ch, 8Bh, 4Ch, 07h, 04h, 51h, 0E8h, 1Dh
    db 08h, 0Ch, 00h, 8Bh, 56h, 7Ch, 8Bh, 44h, 17h, 08h, 50h, 0E8h, 10h, 08h, 0Ch, 00h
    db 8Bh, 4Eh, 7Ch, 8Bh, 54h, 0Fh, 0Ch, 52h, 0E8h, 03h, 08h, 0Ch, 00h, 8Bh, 46h, 78h
    db 83h, 0C4h, 0Ch, 43h, 83h, 0C7h, 18h, 3Bh, 0D8h, 7Ch, 0BCh, 5Fh, 8Bh, 46h, 7Ch, 50h
    db 0E8h, 0EBh, 07h, 0Ch, 00h, 8Bh, 4Ch, 24h, 10h, 83h, 0C4h, 04h, 0C7h, 06h, 0DCh, 83h
    db 12h, 01h, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_007c1660@@YAXXZ ENDP

; ghidra: FUN_00bc1760  retail @ 0x007C1760 size 452
public ?d_007c1760@@YAXXZ
?d_007c1760@@YAXXZ PROC
    db 83h, 0ECh, 14h, 56h, 8Bh, 0F1h, 8Bh, 4Eh, 74h, 8Dh, 44h, 24h, 0Ch, 50h, 0E8h, 4Dh
    db 0EBh, 15h, 00h, 8Bh, 4Ch, 24h, 0Ch, 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h, 14h, 89h
    db 8Eh, 90h, 00h, 00h, 00h, 89h, 96h, 94h, 00h, 00h, 00h, 89h, 86h, 98h, 00h, 00h
    db 00h, 8Bh, 0Dh, 0ECh, 6Eh, 30h, 01h, 6Ah, 00h, 0E8h, 12h, 0A7h, 84h, 0FFh, 0D9h, 86h
    db 90h, 00h, 00h, 00h, 0D8h, 20h, 0D9h, 9Eh, 90h, 00h, 00h, 00h, 0D9h, 86h, 94h, 00h
    db 00h, 00h, 0D8h, 60h, 04h, 0D9h, 9Eh, 94h, 00h, 00h, 00h, 0D9h, 86h, 98h, 00h, 00h
    db 00h, 0D8h, 60h, 08h, 0D9h, 9Eh, 98h, 00h, 00h, 00h, 0D9h, 86h, 98h, 00h, 00h, 00h
    db 0D9h, 86h, 94h, 00h, 00h, 00h, 0D9h, 86h, 90h, 00h, 00h, 00h, 0D9h, 0C0h, 0D8h, 0C9h
    db 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 04h
    db 0DDh, 0D8h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 04h
    db 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 32h, 8Bh, 4Ch, 24h, 04h, 51h, 0E8h, 30h
    db 62h, 86h, 0FFh, 0D9h, 0C0h, 0D8h, 8Eh, 90h, 00h, 00h, 00h, 0D9h, 9Eh, 90h, 00h, 00h
    db 00h, 0D9h, 0C0h, 0D8h, 8Eh, 94h, 00h, 00h, 00h, 0D9h, 9Eh, 94h, 00h, 00h, 00h, 0D8h
    db 8Eh, 98h, 00h, 00h, 00h, 0D9h, 9Eh, 98h, 00h, 00h, 00h, 0D9h, 86h, 88h, 00h, 00h
    db 00h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 4Bh, 0D9h, 86h
    db 94h, 00h, 00h, 00h, 0D9h, 86h, 90h, 00h, 00h, 00h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h
    db 0D8h, 0CBh, 0DEh, 0C1h, 0D8h, 8Eh, 88h, 00h, 00h, 00h, 0D8h, 8Eh, 88h, 00h, 00h, 00h
    db 0D9h, 54h, 24h, 04h, 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 9Eh, 98h, 00h, 00h, 00h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 14h, 0D9h, 44h, 24h, 04h, 0D9h, 0FAh, 0D9h, 5Ch, 24h, 08h, 8Bh
    db 54h, 24h, 08h, 89h, 96h, 98h, 00h, 00h, 00h, 0D9h, 86h, 98h, 00h, 00h, 00h, 0D8h
    db 1Dh, 0DCh, 0Ah, 0Fh, 01h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 74h, 73h, 8Bh, 54h, 24h, 10h
    db 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 85h, 0C9h, 6Ah, 00h, 52h, 8Bh, 54h, 24h, 14h, 52h
    db 74h, 07h, 8Bh, 01h, 0FFh, 50h, 18h, 0EBh, 0Eh, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 8Bh
    db 01h, 0FFh, 90h, 48h, 02h, 00h, 00h, 0D9h, 44h, 24h, 14h, 0D8h, 86h, 84h, 00h, 00h
    db 00h, 0DEh, 0E1h, 0D8h, 86h, 8Ch, 00h, 00h, 00h, 0D9h, 05h, 3Ch, 0BFh, 09h, 01h, 0D8h
    db 0B6h, 98h, 00h, 00h, 00h, 0DEh, 0C9h, 0D9h, 0C0h, 0D8h, 8Eh, 90h, 00h, 00h, 00h, 0D9h
    db 9Eh, 90h, 00h, 00h, 00h, 0D9h, 0C0h, 0D8h, 8Eh, 94h, 00h, 00h, 00h, 0D9h, 9Eh, 94h
    db 00h, 00h, 00h, 0D8h, 8Eh, 98h, 00h, 00h, 00h, 0D9h, 9Eh, 98h, 00h, 00h, 00h, 5Eh
    db 83h, 0C4h, 14h, 0C3h
?d_007c1760@@YAXXZ ENDP

; ghidra: FUN_00bc19a0  retail @ 0x007C19A0 size 49
public ?d_007c19a0@@YAXXZ
?d_007c19a0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 0Eh, 85h, 0C9h, 74h, 0Fh, 0FFh, 49h, 04h, 75h, 04h, 8Bh, 01h
    db 0FFh, 10h, 0C7h, 06h, 00h, 00h, 00h, 00h, 8Bh, 4Eh, 04h, 85h, 0C9h, 74h, 10h, 0FFh
    db 49h, 04h, 75h, 04h, 8Bh, 11h, 0FFh, 12h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 5Eh
    db 0C3h
?d_007c19a0@@YAXXZ ENDP

; ghidra: FUN_00bc19f0  retail @ 0x007C19F0 size 408
public ?d_007c19f0@@YAXXZ
?d_007c19f0@@YAXXZ PROC
    db 56h, 57h, 6Ah, 00h, 8Bh, 0F9h, 0E8h, 0C5h, 0F8h, 15h, 00h, 8Bh, 0F0h, 83h, 0C4h, 04h
    db 85h, 0F6h, 74h, 03h, 0FFh, 46h, 04h, 0A1h, 0C4h, 0Eh, 34h, 01h, 85h, 0C0h, 74h, 13h
    db 8Bh, 50h, 04h, 8Bh, 0C8h, 83h, 0C0h, 04h, 4Ah, 85h, 0D2h, 89h, 10h, 75h, 04h, 8Bh
    db 01h, 0FFh, 10h, 8Bh, 0Dh, 9Ch, 0F4h, 33h, 01h, 81h, 0C9h, 00h, 40h, 00h, 00h, 85h
    db 0F6h, 89h, 35h, 0C4h, 0Eh, 34h, 01h, 89h, 0Dh, 9Ch, 0F4h, 33h, 01h, 74h, 0Bh, 0FFh
    db 4Eh, 04h, 75h, 06h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h, 68h, 14h, 0BFh, 2Bh, 01h, 0E8h
    db 6Fh, 59h, 85h, 0FFh, 8Bh, 07h, 6Ah, 00h, 50h, 0E8h, 72h, 29h, 14h, 00h, 8Bh, 4Fh
    db 04h, 6Ah, 00h, 51h, 0E8h, 07h, 2Ah, 14h, 00h, 0A1h, 9Ch, 0F4h, 33h, 01h, 83h, 0C4h
    db 14h, 0A9h, 00h, 00h, 04h, 00h, 0Fh, 85h, 0AAh, 00h, 00h, 00h, 0Dh, 01h, 00h, 04h
    db 00h, 0C7h, 05h, 8Ch, 10h, 34h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 90h, 10h, 34h
    db 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 94h, 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h
    db 05h, 98h, 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 9Ch, 10h, 34h, 01h, 00h
    db 00h, 00h, 00h, 0C7h, 05h, 0A0h, 10h, 34h, 01h, 00h, 00h, 80h, 3Fh, 0C7h, 05h, 0A4h
    db 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0A8h, 10h, 34h, 01h, 00h, 00h, 00h
    db 00h, 0C7h, 05h, 0ACh, 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0B0h, 10h, 34h
    db 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0B4h, 10h, 34h, 01h, 00h, 00h, 80h, 3Fh, 0C7h
    db 05h, 0B8h, 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0BCh, 10h, 34h, 01h, 00h
    db 00h, 00h, 00h, 0C7h, 05h, 0C0h, 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0C4h
    db 10h, 34h, 01h, 00h, 00h, 00h, 00h, 0C7h, 05h, 0C8h, 10h, 34h, 01h, 00h, 00h, 80h
    db 3Fh, 0A3h, 9Ch, 0F4h, 33h, 01h, 0E8h, 65h, 2Dh, 14h, 00h, 8Bh, 35h, 34h, 05h, 34h
    db 01h, 8Bh, 16h, 6Ah, 01h, 6Ah, 34h, 56h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h
    db 6Ah, 08h, 6Ah, 38h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Dh, 0ECh, 6Eh, 30h
    db 01h, 8Bh, 16h, 8Bh, 79h, 08h, 6Ah, 0FFh, 6Ah, 3Ah, 56h, 0FFh, 92h, 0E4h, 00h, 00h
    db 00h, 8Bh, 06h, 0F7h, 0D7h, 57h, 6Ah, 3Bh, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh
    db 0Eh, 6Ah, 00h, 56h, 0FFh, 91h, 70h, 01h, 00h, 00h, 8Bh, 16h, 6Ah, 02h, 56h, 0FFh
    db 92h, 64h, 01h, 00h, 00h, 5Fh, 5Eh, 0C3h
?d_007c19f0@@YAXXZ ENDP

; ghidra: FUN_00bc1bf0  retail @ 0x007C1BF0 size 321
public ?d_007c1bf0@@YAXXZ
?d_007c1bf0@@YAXXZ PROC
    db 53h, 56h, 8Bh, 0F1h, 57h, 8Bh, 7Eh, 0Ch, 33h, 0DBh, 3Bh, 0FBh, 74h, 10h, 8Bh, 0CFh
    db 0E8h, 0Bh, 0C2h, 15h, 00h, 57h, 0E8h, 0A5h, 02h, 0Ch, 00h, 83h, 0C4h, 04h, 8Bh, 7Eh
    db 10h, 3Bh, 0FBh, 89h, 5Eh, 0Ch, 74h, 10h, 8Bh, 0CFh, 0E8h, 0D1h, 0B2h, 15h, 00h, 57h
    db 0E8h, 8Bh, 02h, 0Ch, 00h, 83h, 0C4h, 04h, 8Bh, 4Eh, 14h, 81h, 0F9h, 30h, 75h, 00h
    db 00h, 89h, 5Eh, 10h, 0Fh, 84h, 0F1h, 00h, 00h, 00h, 8Bh, 7Eh, 18h, 0BAh, 30h, 75h
    db 00h, 00h, 2Bh, 0D7h, 0B8h, 0ABh, 0AAh, 0AAh, 0AAh, 0F7h, 0E2h, 0BBh, 30h, 75h, 00h, 00h
    db 2Bh, 0D9h, 8Bh, 0FAh, 68h, 14h, 0BFh, 2Bh, 01h, 8Dh, 04h, 1Bh, 0D1h, 0EFh, 50h, 8Dh
    db 0Ch, 3Fh, 51h, 0E8h, 38h, 57h, 17h, 00h, 8Bh, 15h, 78h, 05h, 34h, 01h, 8Bh, 82h
    db 90h, 00h, 00h, 00h, 8Bh, 35h, 34h, 05h, 34h, 01h, 83h, 0C4h, 0Ch, 0F6h, 0C4h, 01h
    db 75h, 39h, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 6Ah, 02h, 6Ah, 16h, 56h, 75h, 17h, 8Bh
    db 06h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah, 07h, 6Ah, 37h, 56h, 0FFh, 91h
    db 0E4h, 00h, 00h, 00h, 0EBh, 15h, 8Bh, 16h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h
    db 6Ah, 07h, 6Ah, 36h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 57h, 6Ah, 00h
    db 53h, 6Ah, 00h, 6Ah, 00h, 6Ah, 04h, 56h, 0FFh, 91h, 48h, 01h, 00h, 00h, 8Bh, 15h
    db 78h, 05h, 34h, 01h, 8Bh, 82h, 90h, 00h, 00h, 00h, 0F6h, 0C4h, 01h, 75h, 4Ch, 8Bh
    db 44h, 24h, 10h, 85h, 0C0h, 6Ah, 03h, 6Ah, 16h, 56h, 75h, 17h, 8Bh, 06h, 0FFh, 90h
    db 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 6Ah, 08h, 6Ah, 37h, 56h, 0FFh, 91h, 0E4h, 00h, 00h
    db 00h, 0EBh, 15h, 8Bh, 16h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 8Bh, 06h, 6Ah, 08h, 6Ah
    db 36h, 56h, 0FFh, 90h, 0E4h, 00h, 00h, 00h, 8Bh, 0Eh, 57h, 6Ah, 00h, 53h, 6Ah, 00h
    db 6Ah, 00h, 6Ah, 04h, 56h, 0FFh, 91h, 48h, 01h, 00h, 00h, 5Fh, 5Eh, 5Bh, 0C2h, 04h
    db 00h
?d_007c1bf0@@YAXXZ ENDP

; ghidra: FUN_00bc1dc0  retail @ 0x007C1DC0 size 289
public ?d_007c1dc0@@YAXXZ
?d_007c1dc0@@YAXXZ PROC
    db 81h, 0ECh, 80h, 00h, 00h, 00h, 56h, 57h, 8Bh, 0F9h, 8Bh, 37h, 8Bh, 86h, 0C8h, 00h
    db 00h, 00h, 8Bh, 48h, 18h, 0F6h, 0C5h, 04h, 74h, 14h, 8Bh, 4Fh, 04h, 51h, 8Bh, 0CEh
    db 0E8h, 0ABh, 0A5h, 16h, 00h, 5Fh, 5Eh, 81h, 0C4h, 80h, 00h, 00h, 00h, 0C3h, 8Bh, 16h
    db 8Bh, 0CEh, 0FFh, 52h, 50h, 0D9h, 46h, 18h, 8Bh, 46h, 20h, 0D9h, 46h, 1Ch, 8Bh, 4Eh
    db 24h, 0D9h, 46h, 28h, 8Bh, 56h, 2Ch, 0D9h, 46h, 38h, 89h, 54h, 24h, 5Ch, 0D9h, 0CBh
    db 8Bh, 56h, 3Ch, 89h, 44h, 24h, 50h, 8Bh, 46h, 30h, 89h, 54h, 24h, 6Ch, 89h, 4Ch
    db 24h, 54h, 8Bh, 4Eh, 34h, 89h, 44h, 24h, 60h, 8Bh, 46h, 40h, 89h, 4Ch, 24h, 64h
    db 8Bh, 4Eh, 44h, 89h, 44h, 24h, 70h, 8Bh, 07h, 8Bh, 90h, 0C8h, 00h, 00h, 00h, 89h
    db 4Ch, 24h, 74h, 8Bh, 4Ah, 28h, 0D9h, 5Ch, 24h, 08h, 8Bh, 54h, 24h, 5Ch, 89h, 54h
    db 24h, 1Ch, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 54h, 24h, 6Ch, 0D9h, 0C9h, 89h, 54h, 24h, 20h
    db 0D9h, 5Ch, 24h, 10h, 8Bh, 54h, 24h, 50h, 89h, 54h, 24h, 28h, 0D9h, 5Ch, 24h, 18h
    db 8Bh, 54h, 24h, 60h, 89h, 54h, 24h, 2Ch, 8Bh, 54h, 24h, 70h, 89h, 54h, 24h, 30h
    db 8Bh, 54h, 24h, 54h, 89h, 54h, 24h, 38h, 8Bh, 54h, 24h, 64h, 89h, 54h, 24h, 3Ch
    db 8Bh, 54h, 24h, 74h, 51h, 89h, 54h, 24h, 44h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 28h, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 38h, 00h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 48h, 00h, 00h, 80h, 3Fh, 8Bh, 90h, 0C8h, 00h, 00h, 00h, 8Bh
    db 42h, 30h, 8Bh, 57h, 04h, 8Dh, 4Ch, 24h, 0Ch, 51h, 8Bh, 48h, 0Ch, 6Ah, 0Ch, 51h
    db 6Ah, 0Ch, 52h, 0E8h, 76h, 85h, 23h, 00h, 5Fh, 5Eh, 81h, 0C4h, 80h, 00h, 00h, 00h
    db 0C3h
?d_007c1dc0@@YAXXZ ENDP

; ghidra: FUN_00bc1f30  retail @ 0x007C1F30 size 1089
_TEXT ENDS
_TEXT$d00bc1f30 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BC1F30 size 1089
public ?d_007c1f30@@YAXXZ
?d_007c1f30@@YAXXZ PROC
    db 083h, 0ECh, 020h, 08Bh, 001h, 08Bh, 080h, 0C8h, 000h, 000h, 000h, 08Bh, 050h, 02Ch, 08Bh, 040h
    db 024h, 083h, 0F8h, 004h, 08Bh, 052h, 00Ch, 053h, 055h, 056h, 08Bh, 071h, 008h, 089h, 074h, 024h
    db 00Ch, 08Bh, 074h, 024h, 030h, 057h, 00Fh, 08Ch, 02Bh, 003h, 000h, 000h, 08Dh, 078h, 0FCh, 0C1h
    db 0EFh, 002h, 047h, 089h, 07Ch, 024h, 034h, 0F7h, 0DFh, 08Dh, 004h, 0B8h, 089h, 044h, 024h, 014h
    db 00Fh, 0B7h, 002h, 08Bh, 079h, 004h, 00Fh, 0B7h, 06Ah, 004h, 08Dh, 004h, 040h, 08Dh, 01Ch, 087h
    db 00Fh, 0B7h, 042h, 002h, 08Dh, 004h, 040h, 08Dh, 004h, 087h, 08Dh, 06Ch, 06Dh, 000h, 08Dh, 03Ch
    db 0AFh, 0D9h, 000h, 08Bh, 068h, 008h, 0D9h, 040h, 004h, 089h, 06Ch, 024h, 02Ch, 08Bh, 028h, 0D9h
    db 0C9h, 0D8h, 027h, 089h, 06Ch, 024h, 018h, 08Bh, 068h, 004h, 08Bh, 040h, 008h, 0D9h, 05Ch, 024h
    db 024h, 089h, 06Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0D8h, 067h, 004h, 0D9h, 044h, 024h, 02Ch
    db 0D8h, 067h, 008h, 0D9h, 044h, 024h, 018h, 0D8h, 023h, 0D9h, 044h, 024h, 01Ch, 0D8h, 063h, 004h
    db 0D9h, 044h, 024h, 020h, 0D8h, 063h, 008h, 0D9h, 0C0h, 0D8h, 0CDh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh
    db 0E9h, 0D8h, 00Eh, 0D9h, 0C3h, 0D8h, 0CDh, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0DEh, 0E9h, 0D8h
    db 04Eh, 004h, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0D9h, 0CCh, 0D8h, 0CEh, 0DEh, 0ECh
    db 0D9h, 0CBh, 0D8h, 04Eh, 008h, 0DEh, 0C3h, 0D9h, 0CAh, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 0DDh, 0D8h, 07Ah, 007h, 0B8h
    db 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h, 08Bh, 07Ch, 024h, 010h, 088h, 007h, 00Fh, 0B7h
    db 042h, 006h, 08Bh, 079h, 004h, 00Fh, 0B7h, 06Ah, 00Ah, 08Dh, 004h, 040h, 08Dh, 01Ch, 087h, 00Fh
    db 0B7h, 042h, 008h, 08Dh, 004h, 040h, 08Dh, 004h, 087h, 08Dh, 06Ch, 06Dh, 000h, 08Dh, 03Ch, 0AFh
    db 0D9h, 000h, 08Bh, 068h, 008h, 0D9h, 040h, 004h, 089h, 06Ch, 024h, 02Ch, 08Bh, 028h, 0D9h, 0C9h
    db 0D8h, 027h, 089h, 06Ch, 024h, 018h, 08Bh, 068h, 004h, 08Bh, 040h, 008h, 0D9h, 05Ch, 024h, 024h
    db 089h, 06Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0D8h, 067h, 004h, 0D9h, 044h, 024h, 02Ch, 0D8h
    db 067h, 008h, 0D9h, 044h, 024h, 018h, 0D8h, 023h, 0D9h, 044h, 024h, 01Ch, 0D8h, 063h, 004h, 0D9h
    db 044h, 024h, 020h, 0D8h, 063h, 008h, 0D9h, 0C0h, 0D8h, 0CDh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh, 0E9h
    db 0D8h, 00Eh, 0D9h, 0C3h, 0D8h, 0CDh, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0DEh, 0E9h, 0D8h, 04Eh
    db 004h, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0D9h, 0CCh, 0D8h, 0CEh, 0DEh, 0ECh, 0D9h
    db 0CBh, 0D8h, 04Eh, 008h, 0DEh, 0C3h, 0D9h, 0CAh, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 0DDh, 0D8h, 07Ah, 007h, 0B8h
    db 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h, 08Bh, 07Ch, 024h, 010h, 088h, 047h, 001h, 00Fh
    db 0B7h, 042h, 00Ch, 08Bh, 079h, 004h, 00Fh, 0B7h, 06Ah, 010h, 08Dh, 004h, 040h, 08Dh, 01Ch, 087h
    db 00Fh, 0B7h, 042h, 00Eh, 08Dh, 004h, 040h, 08Dh, 004h, 087h, 08Dh, 06Ch, 06Dh, 000h, 08Dh, 03Ch
    db 0AFh, 0D9h, 000h, 08Bh, 068h, 008h, 0D9h, 040h, 004h, 089h, 06Ch, 024h, 02Ch, 08Bh, 028h, 0D9h
    db 0C9h, 0D8h, 027h, 089h, 06Ch, 024h, 018h, 08Bh, 068h, 004h, 08Bh, 040h, 008h, 0D9h, 05Ch, 024h
    db 024h, 089h, 06Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0D8h, 067h, 004h, 0D9h, 044h, 024h, 02Ch
    db 0D8h, 067h, 008h, 0D9h, 044h, 024h, 018h, 0D8h, 023h, 0D9h, 044h, 024h, 01Ch, 0D8h, 063h, 004h
    db 0D9h, 044h, 024h, 020h, 0D8h, 063h, 008h, 0D9h, 0C0h, 0D8h, 0CDh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh
    db 0E9h, 0D8h, 00Eh, 0D9h, 0C3h, 0D8h, 0CDh, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0DEh, 0E9h, 0D8h
    db 04Eh, 004h, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0D9h, 0CCh, 0D8h, 0CEh, 0DEh, 0ECh
    db 0D9h, 0CBh, 0D8h, 04Eh, 008h, 0DEh, 0C3h, 0D9h, 0CAh, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 0DDh, 0D8h, 07Ah, 007h, 0B8h
    db 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h, 08Bh, 07Ch, 024h, 010h, 088h, 047h, 002h, 00Fh
    db 0B7h, 042h, 012h, 08Bh, 079h, 004h, 00Fh, 0B7h, 06Ah, 016h, 08Dh, 004h, 040h, 08Dh, 01Ch, 087h
    db 00Fh, 0B7h, 042h, 014h, 08Dh, 004h, 040h, 08Dh, 004h, 087h, 08Dh, 06Ch, 06Dh, 000h, 08Dh, 03Ch
    db 0AFh, 0D9h, 000h, 08Bh, 068h, 008h, 0D9h, 040h, 004h, 089h, 06Ch, 024h, 02Ch, 08Bh, 028h, 0D9h
    db 0C9h, 0D8h, 027h, 089h, 06Ch, 024h, 018h, 08Bh, 068h, 004h, 08Bh, 040h, 008h, 0D9h, 05Ch, 024h
    db 024h, 089h, 06Ch, 024h, 01Ch, 089h, 044h, 024h, 020h, 0D8h, 067h, 004h, 0D9h, 044h, 024h, 02Ch
    db 0D8h, 067h, 008h, 0D9h, 044h, 024h, 018h, 0D8h, 023h, 0D9h, 044h, 024h, 01Ch, 0D8h, 063h, 004h
    db 0D9h, 044h, 024h, 020h, 0D8h, 063h, 008h, 0D9h, 0C0h, 0D8h, 0CDh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh
    db 0E9h, 0D8h, 00Eh, 0D9h, 0C3h, 0D8h, 0CDh, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0DEh, 0E9h, 0D8h
    db 04Eh, 004h, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h, 0D8h, 0CBh, 0D9h, 0CCh, 0D8h, 0CEh, 0DEh, 0ECh
    db 0D9h, 0CBh, 0D8h, 04Eh, 008h, 0DEh, 0C3h, 0D9h, 0CAh, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 0DDh, 0D8h, 07Ah, 007h, 0B8h
    db 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h, 08Bh, 07Ch, 024h, 010h, 088h, 047h, 003h, 08Bh
    db 044h, 024h, 034h, 083h, 0C7h, 004h, 083h, 0C2h, 018h, 048h, 089h, 07Ch, 024h, 010h, 089h, 044h
    db 024h, 034h, 00Fh, 085h, 0EDh, 0FCh, 0FFh, 0FFh, 08Bh, 044h, 024h, 014h, 085h, 0C0h, 00Fh, 08Eh
    db 0D8h, 000h, 000h, 000h, 089h, 044h, 024h, 034h, 00Fh, 0B7h, 002h, 08Bh, 079h, 004h, 00Fh, 0B7h
    db 06Ah, 004h, 08Dh, 004h, 040h, 08Dh, 01Ch, 087h, 00Fh, 0B7h, 042h, 002h, 08Dh, 004h, 040h, 08Dh
    db 004h, 087h, 08Dh, 06Ch, 06Dh, 000h, 08Dh, 03Ch, 0AFh, 0D9h, 000h, 08Bh, 068h, 008h, 0D9h, 040h
    db 004h, 089h, 06Ch, 024h, 02Ch, 08Bh, 028h, 0D9h, 0C9h, 0D8h, 027h, 089h, 06Ch, 024h, 018h, 08Bh
    db 068h, 004h, 08Bh, 040h, 008h, 0D9h, 05Ch, 024h, 024h, 089h, 06Ch, 024h, 01Ch, 089h, 044h, 024h
    db 020h, 0D8h, 067h, 004h, 0D9h, 044h, 024h, 02Ch, 0D8h, 067h, 008h, 0D9h, 044h, 024h, 018h, 0D8h
    db 023h, 0D9h, 044h, 024h, 01Ch, 0D8h, 063h, 004h, 0D9h, 044h, 024h, 020h, 0D8h, 063h, 008h, 0D9h
    db 0C0h, 0D8h, 0CDh, 0D9h, 0C2h, 0D8h, 0CDh, 0DEh, 0E9h, 0D8h, 00Eh, 0D9h, 0C3h, 0D8h, 0CDh, 0D9h
    db 044h, 024h, 024h, 0D8h, 0CBh, 0DEh, 0E9h, 0D8h, 04Eh, 004h, 0DEh, 0C1h, 0D9h, 044h, 024h, 024h
    db 0D8h, 0CBh, 0D9h, 0CCh, 0D8h, 0CEh, 0DEh, 0ECh, 0D9h, 0CBh, 0D8h, 04Eh, 008h, 0DEh, 0C3h, 0D9h
    db 0CAh, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DDh, 0D9h, 0DDh, 0D8h, 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 005h, 0DDh, 0D8h, 07Ah, 007h, 0B8h
    db 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h, 08Bh, 07Ch, 024h, 010h, 088h, 007h, 08Bh, 044h
    db 024h, 034h, 083h, 0C2h, 006h, 047h, 048h, 089h, 07Ch, 024h, 010h, 089h, 044h, 024h, 034h, 00Fh
    db 085h, 02Ch, 0FFh, 0FFh, 0FFh, 05Fh, 05Eh, 05Dh, 05Bh, 083h, 0C4h, 020h, 0C2h, 004h, 000h
?d_007c1f30@@YAXXZ ENDP
_TEXT$d00bc1f30 ENDS
_TEXT SEGMENT

; ghidra: FUN_00bc2490  retail @ 0x007C2490 size 1069
public ?d_007c2490@@YAXXZ
?d_007c2490@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 53h, 55h, 56h, 8Bh, 74h, 24h, 38h, 0D9h, 46h, 08h, 8Bh, 06h, 0D9h
    db 54h, 24h, 18h, 57h, 0D9h, 0C0h, 8Bh, 0F9h, 8Bh, 4Eh, 04h, 0D8h, 0C9h, 89h, 4Ch, 24h
    db 18h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 18h, 89h, 44h, 24h, 14h, 0DEh, 0C1h, 0D9h
    db 44h, 24h, 14h, 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 5Ch, 24h, 3Ch, 0D9h, 05h, 50h
    db 53h, 07h, 01h, 0D9h, 44h, 24h, 3Ch, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h, 7Bh, 24h
    db 8Bh, 54h, 24h, 3Ch, 0DDh, 0D8h, 52h, 0E8h, 57h, 55h, 86h, 0FFh, 0D9h, 44h, 24h, 14h
    db 0D8h, 0C9h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 18h, 0D8h, 0C9h, 0D9h, 5Ch, 24h, 18h
    db 0D8h, 4Ch, 24h, 1Ch, 0D9h, 44h, 24h, 14h, 8Bh, 07h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h
    db 8Bh, 88h, 0C8h, 00h, 00h, 00h, 8Bh, 69h, 28h, 8Bh, 44h, 24h, 30h, 0D9h, 5Ch, 24h
    db 14h, 33h, 0C9h, 83h, 0FDh, 04h, 0D9h, 44h, 24h, 18h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h
    db 89h, 6Ch, 24h, 3Ch, 0D9h, 5Ch, 24h, 18h, 0D8h, 0Dh, 70h, 5Ch, 07h, 01h, 0D9h, 5Ch
    db 24h, 1Ch, 0Fh, 8Ch, 0F3h, 00h, 00h, 00h, 83h, 0C5h, 0FCh, 0C1h, 0EDh, 02h, 33h, 0DBh
    db 45h, 8Dh, 14h, 0ADh, 00h, 00h, 00h, 00h, 8Dh, 48h, 14h, 89h, 6Ch, 24h, 30h, 89h
    db 54h, 24h, 10h, 8Bh, 57h, 04h, 0D9h, 44h, 24h, 14h, 0D8h, 04h, 1Ah, 03h, 0D3h, 0D9h
    db 44h, 24h, 18h, 8Dh, 6Bh, 24h, 0D8h, 42h, 04h, 83h, 0C0h, 30h, 0D9h, 44h, 24h, 1Ch
    db 83h, 0C1h, 30h, 0D8h, 42h, 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 89h, 51h
    db 0C4h, 0D9h, 0C9h, 0D9h, 58h, 0D0h, 0D9h, 59h, 0C0h, 8Bh, 57h, 04h, 0D9h, 44h, 24h, 14h
    db 8Dh, 54h, 13h, 0Ch, 0D8h, 02h, 83h, 0C3h, 30h, 0D9h, 44h, 24h, 18h, 0D8h, 42h, 04h
    db 0D9h, 44h, 24h, 1Ch, 0D8h, 42h, 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 89h
    db 51h, 0D0h, 0D9h, 0C9h, 0D9h, 59h, 0C8h, 0D9h, 59h, 0CCh, 8Bh, 57h, 04h, 0D9h, 44h, 24h
    db 14h, 8Dh, 54h, 2Ah, 0F4h, 0D8h, 02h, 0D9h, 44h, 24h, 18h, 0D8h, 42h, 04h, 0D9h, 44h
    db 24h, 1Ch, 0D8h, 42h, 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 89h, 51h, 0DCh
    db 0D9h, 0C9h, 0D9h, 59h, 0D4h, 0D9h, 59h, 0D8h, 8Bh, 57h, 04h, 0D9h, 44h, 24h, 14h, 03h
    db 0D5h, 0D8h, 02h, 0D9h, 44h, 24h, 18h, 0D8h, 42h, 04h, 0D9h, 44h, 24h, 1Ch, 0D8h, 42h
    db 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 54h, 24h, 28h, 0D9h, 0C9h, 89h, 51h, 0E8h, 8Bh, 54h
    db 24h, 30h, 0D9h, 59h, 0E0h, 4Ah, 0D9h, 59h, 0E4h, 89h, 54h, 24h, 30h, 0Fh, 85h, 30h
    db 0FFh, 0FFh, 0FFh, 8Bh, 6Ch, 24h, 3Ch, 8Bh, 4Ch, 24h, 10h, 3Bh, 0CDh, 7Dh, 47h, 8Dh
    db 14h, 49h, 8Bh, 0DDh, 0C1h, 0E2h, 02h, 2Bh, 0D9h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 04h, 0D9h, 44h, 24h, 14h, 0D8h, 04h, 11h, 03h, 0CAh, 0D9h, 44h, 24h, 18h
    db 83h, 0C0h, 0Ch, 0D8h, 41h, 04h, 83h, 0C2h, 0Ch, 4Bh, 0D9h, 44h, 24h, 1Ch, 0D8h, 41h
    db 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 4Ch, 24h, 28h, 0D9h, 0C9h, 89h, 48h, 0FCh, 0D9h, 58h
    db 0F4h, 0D9h, 58h, 0F8h, 75h, 0CAh, 33h, 0C9h, 83h, 0FDh, 04h, 0Fh, 8Ch, 0F6h, 00h, 00h
    db 00h, 83h, 0C5h, 0FCh, 0C1h, 0EDh, 02h, 33h, 0D2h, 45h, 8Dh, 0Ch, 0ADh, 00h, 00h, 00h
    db 00h, 89h, 6Ch, 24h, 30h, 89h, 4Ch, 24h, 10h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 04h, 0D9h, 04h, 11h, 03h, 0CAh, 0D8h, 06h, 8Bh, 0D8h, 0D9h, 41h, 04h, 83h
    db 0C0h, 0Ch, 0D8h, 46h, 04h, 8Dh, 6Ah, 24h, 0D9h, 41h, 08h, 0D8h, 46h, 08h, 0D9h, 5Ch
    db 24h, 28h, 8Bh, 4Ch, 24h, 28h, 89h, 4Bh, 08h, 0D9h, 0C9h, 0D9h, 1Bh, 8Bh, 0C8h, 83h
    db 0C0h, 0Ch, 0D9h, 5Bh, 04h, 8Bh, 5Fh, 04h, 0D9h, 44h, 13h, 0Ch, 8Dh, 5Ch, 13h, 0Ch
    db 0D8h, 06h, 83h, 0C2h, 30h, 0D9h, 43h, 04h, 0D8h, 46h, 04h, 0D9h, 43h, 08h, 0D8h, 46h
    db 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 5Ch, 24h, 28h, 89h, 59h, 08h, 0D9h, 0C9h, 0D9h, 19h
    db 0D9h, 59h, 04h, 8Bh, 5Fh, 04h, 0D9h, 44h, 2Bh, 0F4h, 8Dh, 5Ch, 2Bh, 0F4h, 0D8h, 06h
    db 8Bh, 0C8h, 0D9h, 43h, 04h, 83h, 0C0h, 0Ch, 0D8h, 46h, 04h, 0D9h, 43h, 08h, 0D8h, 46h
    db 08h, 0D9h, 5Ch, 24h, 28h, 8Bh, 5Ch, 24h, 28h, 89h, 59h, 08h, 0D9h, 0C9h, 0D9h, 19h
    db 8Bh, 0D8h, 83h, 0C0h, 0Ch, 0D9h, 59h, 04h, 8Bh, 4Fh, 04h, 0D9h, 04h, 29h, 03h, 0CDh
    db 0D8h, 06h, 0D9h, 41h, 04h, 0D8h, 46h, 04h, 0D9h, 41h, 08h, 0D8h, 46h, 08h, 0D9h, 5Ch
    db 24h, 28h, 8Bh, 4Ch, 24h, 28h, 89h, 4Bh, 08h, 0D9h, 0C9h, 8Bh, 4Ch, 24h, 30h, 0D9h
    db 1Bh, 49h, 0D9h, 5Bh, 04h, 89h, 4Ch, 24h, 30h, 0Fh, 85h, 31h, 0FFh, 0FFh, 0FFh, 8Bh
    db 4Ch, 24h, 10h, 8Bh, 6Ch, 24h, 3Ch, 3Bh, 0CDh, 7Dh, 50h, 8Dh, 1Ch, 49h, 8Bh, 0D5h
    db 0C1h, 0E3h, 02h, 2Bh, 0D1h, 89h, 54h, 24h, 30h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 8Bh, 4Fh, 04h, 0D9h, 04h, 19h, 03h, 0CBh, 0D8h, 06h, 8Bh, 0D0h, 0D9h, 41h, 04h, 83h
    db 0C0h, 0Ch, 0D8h, 46h, 04h, 83h, 0C3h, 0Ch, 0D9h, 41h, 08h, 0D8h, 46h, 08h, 0D9h, 5Ch
    db 24h, 28h, 8Bh, 4Ch, 24h, 28h, 89h, 4Ah, 08h, 0D9h, 0C9h, 8Bh, 4Ch, 24h, 30h, 0D9h
    db 1Ah, 49h, 0D9h, 5Ah, 04h, 89h, 4Ch, 24h, 30h, 75h, 0C5h, 8Bh, 77h, 10h, 85h, 0F6h
    db 8Bh, 57h, 0Ch, 8Bh, 4Ch, 24h, 34h, 8Bh, 44h, 24h, 38h, 7Eh, 59h, 8Dh, 49h, 00h
    db 33h, 0DBh, 66h, 8Bh, 1Ah, 66h, 03h, 0DDh, 83h, 0C2h, 08h, 83h, 0C0h, 0Ch, 03h, 0D9h
    db 66h, 89h, 58h, 0F4h, 66h, 8Bh, 5Ah, 0FCh, 66h, 03h, 0D9h, 66h, 89h, 58h, 0F6h, 66h
    db 8Bh, 5Ah, 0F8h, 66h, 03h, 0D9h, 66h, 89h, 58h, 0F8h, 66h, 8Bh, 5Ah, 0FCh, 66h, 03h
    db 0D9h, 66h, 89h, 58h, 0FAh, 33h, 0DBh, 66h, 8Bh, 5Ah, 0F8h, 66h, 03h, 0DDh, 03h, 0D9h
    db 66h, 89h, 58h, 0FCh, 33h, 0DBh, 66h, 8Bh, 5Ah, 0FCh, 66h, 03h, 0DDh, 03h, 0D9h, 4Eh
    db 66h, 89h, 58h, 0FEh, 75h, 0AAh, 8Bh, 17h, 8Bh, 0B2h, 0C8h, 00h, 00h, 00h, 8Bh, 56h
    db 2Ch, 8Bh, 76h, 24h, 85h, 0F6h, 8Bh, 5Fh, 08h, 8Bh, 52h, 0Ch, 7Eh, 55h, 8Bh, 0FFh
    db 80h, 3Bh, 00h, 74h, 1Dh, 66h, 8Bh, 3Ah, 66h, 03h, 0F9h, 66h, 89h, 38h, 66h, 8Bh
    db 7Ah, 02h, 66h, 03h, 0F9h, 66h, 89h, 78h, 02h, 66h, 8Bh, 7Ah, 04h, 66h, 03h, 0F9h
    db 0EBh, 23h, 8Dh, 3Ch, 29h, 66h, 03h, 3Ah, 66h, 89h, 38h, 33h, 0FFh, 66h, 8Bh, 7Ah
    db 02h, 66h, 03h, 0FDh, 03h, 0F9h, 66h, 89h, 78h, 02h, 33h, 0FFh, 66h, 8Bh, 7Ah, 04h
    db 66h, 03h, 0FDh, 03h, 0F9h, 66h, 89h, 78h, 04h, 83h, 0C0h, 06h, 43h, 83h, 0C2h, 06h
    db 4Eh, 75h, 0ADh, 5Fh, 5Eh, 5Dh, 5Bh, 83h, 0C4h, 1Ch, 0C2h, 10h, 00h
?d_007c2490@@YAXXZ ENDP

; ghidra: FUN_00bc2a00  retail @ 0x007C2A00 size 263
public ?d_007c2a00@@YAXXZ
?d_007c2a00@@YAXXZ PROC
    db 53h, 8Bh, 0D9h, 8Bh, 4Bh, 78h, 8Bh, 43h, 7Ch, 8Dh, 0Ch, 49h, 56h, 8Dh, 34h, 0C8h
    db 3Bh, 0F0h, 0Fh, 84h, 0ECh, 00h, 00h, 00h, 55h, 57h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 46h, 0FCh, 83h, 0EEh, 18h, 84h, 0C0h, 75h, 1Ch, 8Bh, 0Eh, 8Bh, 11h, 0FFh, 92h
    db 8Ch, 01h, 00h, 00h, 85h, 0C0h, 74h, 0Eh, 8Ah, 83h, 9Ch, 00h, 00h, 00h, 84h, 0C0h
    db 0Fh, 84h, 0B3h, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 0E3h, 0E5h, 85h, 0FFh, 8Dh, 0BBh, 90h
    db 00h, 00h, 00h, 57h, 8Bh, 0CEh, 0E8h, 8Eh, 21h, 87h, 0FFh, 0E8h, 9Eh, 6Ah, 88h, 0FFh
    db 8Bh, 46h, 10h, 8Dh, 04h, 40h, 0D1h, 0E0h, 3Dh, 30h, 75h, 00h, 00h, 0Fh, 8Fh, 86h
    db 00h, 00h, 00h, 8Bh, 0Dh, 78h, 71h, 30h, 01h, 8Bh, 51h, 0Ch, 85h, 0D2h, 74h, 12h
    db 39h, 41h, 18h, 73h, 0Dh, 6Ah, 00h, 0E8h, 0F7h, 30h, 88h, 0FFh, 8Bh, 0Dh, 78h, 71h
    db 30h, 01h, 8Bh, 41h, 0Ch, 85h, 0C0h, 75h, 0Bh, 0E8h, 0Ch, 61h, 86h, 0FFh, 8Bh, 0Dh
    db 78h, 71h, 30h, 01h, 8Bh, 41h, 10h, 8Bh, 40h, 04h, 8Bh, 69h, 18h, 8Bh, 51h, 0Ch
    db 8Bh, 52h, 04h, 57h, 0BFh, 30h, 75h, 00h, 00h, 2Bh, 0FDh, 8Dh, 04h, 78h, 8Bh, 79h
    db 14h, 50h, 33h, 0C0h, 66h, 0B8h, 30h, 75h, 66h, 2Bh, 41h, 14h, 50h, 0B8h, 30h, 75h
    db 00h, 00h, 2Bh, 0C7h, 8Dh, 0Ch, 40h, 8Dh, 14h, 8Ah, 52h, 8Bh, 0CEh, 0E8h, 5Bh, 2Ah
    db 84h, 0FFh, 8Bh, 0Dh, 78h, 71h, 30h, 01h, 29h, 41h, 14h, 8Bh, 4Eh, 10h, 0A1h, 78h
    db 71h, 30h, 01h, 6Bh, 0C9h, 0FAh, 01h, 48h, 18h, 3Bh, 73h, 7Ch, 0Fh, 85h, 1Eh, 0FFh
    db 0FFh, 0FFh, 5Fh, 5Dh, 5Eh, 5Bh, 0C3h
?d_007c2a00@@YAXXZ ENDP

; ghidra: FUN_00bc2b50  retail @ 0x007C2B50 size 305
public ?d_007c2b50@@YAXXZ
?d_007c2b50@@YAXXZ PROC
    db 55h, 8Bh, 0E9h, 8Bh, 4Dh, 78h, 8Bh, 45h, 7Ch, 8Dh, 0Ch, 49h, 56h, 8Dh, 34h, 0C8h
    db 3Bh, 0F0h, 0Fh, 84h, 16h, 01h, 00h, 00h, 53h, 57h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Ah, 46h, 0FCh, 83h, 0EEh, 18h, 84h, 0C0h, 75h, 1Ch, 8Bh, 0Eh, 8Bh, 11h, 0FFh, 92h
    db 8Ch, 01h, 00h, 00h, 85h, 0C0h, 74h, 0Eh, 8Ah, 85h, 9Ch, 00h, 00h, 00h, 84h, 0C0h
    db 0Fh, 84h, 0DDh, 00h, 00h, 00h, 8Bh, 0CEh, 0E8h, 93h, 0E4h, 85h, 0FFh, 8Dh, 9Dh, 90h
    db 00h, 00h, 00h, 53h, 8Bh, 0CEh, 0E8h, 3Eh, 20h, 87h, 0FFh, 0E8h, 4Eh, 69h, 88h, 0FFh
    db 8Bh, 06h, 8Bh, 88h, 0C8h, 00h, 00h, 00h, 8Bh, 79h, 24h, 8Bh, 56h, 10h, 8Dh, 04h
    db 57h, 8Dh, 04h, 40h, 3Dh, 30h, 75h, 00h, 00h, 0Fh, 8Fh, 0A4h, 00h, 00h, 00h, 8Bh
    db 0Dh, 78h, 71h, 30h, 01h, 8Bh, 51h, 0Ch, 85h, 0D2h, 74h, 12h, 39h, 41h, 18h, 73h
    db 0Dh, 6Ah, 01h, 0E8h, 9Bh, 2Fh, 88h, 0FFh, 8Bh, 0Dh, 78h, 71h, 30h, 01h, 8Bh, 41h
    db 0Ch, 85h, 0C0h, 75h, 0Bh, 0E8h, 0B0h, 5Fh, 86h, 0FFh, 8Bh, 0Dh, 78h, 71h, 30h, 01h
    db 8Bh, 51h, 10h, 8Bh, 52h, 04h, 53h, 8Bh, 59h, 18h, 0B8h, 30h, 75h, 00h, 00h, 2Bh
    db 0C3h, 8Dh, 04h, 42h, 33h, 0D2h, 66h, 0BAh, 30h, 75h, 66h, 2Bh, 51h, 14h, 50h, 0B8h
    db 30h, 75h, 00h, 00h, 52h, 8Bh, 51h, 14h, 8Bh, 49h, 0Ch, 2Bh, 0C2h, 8Bh, 51h, 04h
    db 8Dh, 04h, 40h, 8Dh, 04h, 82h, 50h, 8Bh, 0CEh, 0E8h, 15h, 0A6h, 87h, 0FFh, 8Bh, 0Eh
    db 8Bh, 91h, 0C8h, 00h, 00h, 00h, 8Bh, 4Ah, 28h, 0A1h, 78h, 71h, 30h, 01h, 8Bh, 50h
    db 14h, 0F7h, 0D9h, 0D1h, 0E1h, 03h, 0D1h, 89h, 50h, 14h, 8Bh, 56h, 10h, 0A1h, 78h, 71h
    db 30h, 01h, 0D1h, 0E2h, 0F7h, 0DFh, 2Bh, 0FAh, 8Bh, 50h, 18h, 8Dh, 0Ch, 7Fh, 03h, 0D1h
    db 89h, 50h, 18h, 3Bh, 75h, 7Ch, 0Fh, 85h, 0F4h, 0FEh, 0FFh, 0FFh, 5Fh, 5Bh, 5Eh, 5Dh
    db 0C3h
?d_007c2b50@@YAXXZ ENDP

; ghidra: FUN_00bc2cd0  retail @ 0x007C2CD0 size 300
public ?d_007c2cd0@@YAXXZ
?d_007c2cd0@@YAXXZ PROC
    db 83h, 0ECh, 1Ch, 57h, 6Ah, 01h, 8Bh, 0F9h, 8Bh, 0Dh, 0E8h, 6Eh, 30h, 01h, 8Dh, 44h
    db 24h, 0Ch, 50h, 51h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 0E8h, 0B8h, 1Fh, 87h, 0FFh, 8Bh
    db 15h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 42h, 64h, 84h, 0C0h, 0C6h, 44h, 24h, 07h, 00h, 0Fh
    db 84h, 0CCh, 00h, 00h, 00h, 53h, 55h, 56h, 8Bh, 77h, 08h, 33h, 0EDh, 32h, 0DBh, 85h
    db 0F6h, 74h, 6Dh, 8Ah, 46h, 04h, 84h, 0C0h, 74h, 5Fh, 8Ah, 46h, 05h, 84h, 0C0h, 75h
    db 58h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0E8h, 5Ch, 1Ah, 87h, 0FFh, 84h, 0C0h, 74h
    db 48h, 8Bh, 0CEh, 0E8h, 23h, 04h, 85h, 0FFh, 68h, 0F0h, 6Eh, 30h, 01h, 8Bh, 0CEh, 0E8h
    db 6Ah, 39h, 84h, 0FFh, 84h, 0C0h, 74h, 07h, 89h, 6Eh, 70h, 8Bh, 0EEh, 0EBh, 2Ah, 8Ah
    db 44h, 24h, 13h, 84h, 0C0h, 75h, 0Ch, 8Bh, 0CFh, 0C6h, 44h, 24h, 13h, 01h, 0E8h, 24h
    db 0B2h, 87h, 0FFh, 84h, 0DBh, 75h, 0Bh, 6Ah, 00h, 8Bh, 0CFh, 0B3h, 01h, 0E8h, 31h, 36h
    db 88h, 0FFh, 8Bh, 0CEh, 0E8h, 1Dh, 76h, 87h, 0FFh, 8Bh, 76h, 6Ch, 85h, 0F6h, 75h, 93h
    db 8Bh, 47h, 0Ch, 85h, 0C0h, 74h, 09h, 6Ah, 00h, 8Bh, 0CFh, 0E8h, 0F3h, 2Dh, 88h, 0FFh
    db 85h, 0EDh, 74h, 3Ah, 8Ah, 44h, 24h, 13h, 84h, 0C0h, 75h, 07h, 8Bh, 0CFh, 0E8h, 0E4h
    db 0B1h, 87h, 0FFh, 6Ah, 01h, 8Bh, 0CFh, 0E8h, 0F7h, 35h, 88h, 0FFh, 8Bh, 0F5h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 12h, 38h, 88h, 0FFh, 8Bh, 76h, 70h, 85h, 0F6h, 75h, 0F2h, 8Bh, 47h
    db 0Ch, 85h, 0C0h, 74h, 09h, 6Ah, 01h, 8Bh, 0CFh, 0E8h, 0B5h, 2Dh, 88h, 0FFh, 5Eh, 5Dh
    db 5Bh, 8Bh, 0Dh, 78h, 05h, 34h, 01h, 8Bh, 81h, 90h, 00h, 00h, 00h, 0F6h, 0C4h, 01h
    db 5Fh, 74h, 15h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 00h, 68h, 0B9h, 00h, 00h
    db 00h, 50h, 0FFh, 92h, 0E4h, 00h, 00h, 00h, 83h, 0C4h, 1Ch, 0C3h
?d_007c2cd0@@YAXXZ ENDP

; ghidra: FUN_00bc2f20  retail @ 0x007C2F20 size 662
_TEXT ENDS
_TEXT$d00bc2f20 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00BC2F20 size 662
public ?d_007c2f20@@YAXXZ
?d_007c2f20@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va01052DD0
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 083h, 0ECh
    db 028h, 056h, 08Bh, 0F1h, 057h, 089h, 074h, 024h, 008h
    call ?j_0000af38@@YAXXZ
    db 033h, 0FFh, 089h, 07Eh, 058h, 089h, 07Eh, 05Ch, 0C7h, 046h, 060h, 000h, 000h, 0A0h, 041h, 0C6h
    db 046h, 064h, 000h, 08Bh, 044h, 024h, 040h, 0C7h, 006h
    dd ??_7BfmeVolumetricShadowBufferOwner@@6B@
    db 089h, 046h, 068h, 08Bh, 010h, 08Dh, 04Eh, 06Ch, 089h, 011h, 08Bh, 054h, 024h, 044h, 089h, 056h
    db 074h, 08Bh, 011h, 03Bh, 0D7h, 089h, 07Ch, 024h, 038h, 089h, 0BEh, 088h, 000h, 000h, 000h, 089h
    db 0BEh, 08Ch, 000h, 000h, 000h, 074h, 003h, 089h, 04Ah, 068h, 089h, 030h, 08Bh, 046h, 074h, 0FFh
    db 040h, 004h, 053h, 055h, 089h, 07Ch, 024h, 014h, 089h, 07Ch, 024h, 018h, 089h, 07Ch, 024h, 01Ch
    db 08Bh, 046h, 074h, 050h, 08Dh, 04Ch, 024h, 018h, 051h, 08Bh, 0CEh, 0C6h, 044h, 024h, 048h, 001h
    call ?j_0002a2f2@@YAXXZ
    db 08Bh, 044h, 024h, 018h, 08Bh, 04Ch, 024h, 014h, 08Bh, 0D8h, 02Bh, 0D9h, 0C1h, 0FBh, 002h, 033h
    db 0D2h, 085h, 0DBh, 076h, 036h, 0BBh, 000h, 010h, 000h, 000h, 08Bh, 02Ch, 091h, 08Bh, 0ADh, 0C8h
    db 000h, 000h, 000h, 085h, 05Dh, 018h, 074h, 003h, 042h, 0EBh, 015h, 08Bh, 040h, 0FCh, 089h, 004h
    db 091h, 08Bh, 044h, 024h, 018h, 08Bh, 04Ch, 024h, 014h, 083h, 0E8h, 004h, 089h, 044h, 024h, 018h
    db 08Bh, 0E8h, 02Bh, 0E9h, 0C1h, 0FDh, 002h, 03Bh, 0D5h, 072h, 0CFh, 02Bh, 0C1h, 0C1h, 0F8h, 002h
    db 08Dh, 00Ch, 040h, 0C1h, 0E1h, 003h, 051h, 089h, 046h, 078h
    call ??_U@YAPAXI@Z
    db 089h, 046h, 07Ch, 08Bh, 046h, 078h, 083h, 0C4h, 004h, 033h, 0DBh, 03Bh, 0C7h, 00Fh, 08Eh, 0D0h
    db 000h, 000h, 000h, 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h, 08Bh, 044h, 024h, 014h, 08Bh, 00Ch
    db 098h, 08Bh, 056h, 07Ch, 089h, 00Ch, 017h, 08Bh, 056h, 07Ch, 08Bh, 004h, 017h, 0FFh, 040h, 004h
    db 08Bh, 046h, 07Ch, 08Bh, 00Ch, 007h
    call ?Get_Model@MeshClass@@QAEPAVMeshModelClass@@XZ
    db 08Bh, 0E8h, 08Bh, 045h, 028h, 08Dh, 00Ch, 040h, 0C1h, 0E1h, 002h, 051h
    call ??_U@YAPAXI@Z
    db 08Bh, 056h, 07Ch, 089h, 044h, 017h, 004h, 08Bh, 045h, 024h, 050h
    call ??_U@YAPAXI@Z
    db 08Bh, 04Eh, 07Ch, 089h, 044h, 00Fh, 008h, 08Bh, 045h, 024h, 08Dh, 014h, 040h, 0C1h, 0E2h, 002h
    db 052h
    call ??_U@YAPAXI@Z
    db 08Bh, 04Eh, 07Ch, 089h, 044h, 00Fh, 00Ch, 08Bh, 056h, 07Ch, 0C7h, 044h, 017h, 010h, 000h, 000h
    db 000h, 000h, 08Bh, 044h, 024h, 020h, 08Bh, 00Ch, 098h, 08Bh, 011h, 083h, 0C4h, 00Ch, 0FFh, 052h
    db 018h, 085h, 0C0h, 074h, 026h, 08Bh, 044h, 024h, 014h, 08Bh, 00Ch, 098h, 08Bh, 011h, 068h
    dd g_Va01128748
    db 0FFh, 052h, 018h, 050h, 0FFh, 015h
    dd ?g_bfmeStrStrVMZ@@3P6APADPBD0@ZA
    db 083h, 0C4h, 008h, 085h, 0C0h, 074h, 007h, 0B8h, 001h, 000h, 000h, 000h, 0EBh, 002h, 033h, 0C0h
    db 08Bh, 04Eh, 07Ch, 088h, 044h, 00Fh, 014h, 0FFh, 04Dh, 004h, 075h, 007h, 08Bh, 055h, 000h, 08Bh
    db 0CDh, 0FFh, 012h, 08Bh, 046h, 078h, 043h, 083h, 0C7h, 018h, 03Bh, 0D8h, 00Fh, 08Ch, 039h, 0FFh
    db 0FFh, 0FFh, 033h, 0FFh, 08Bh, 04Eh, 074h, 08Bh, 001h, 08Dh, 054h, 024h, 020h, 052h, 0FFh, 090h
    db 00Ch, 001h, 000h, 000h, 0D9h, 044h, 024h, 020h, 0D9h, 0E1h, 0D8h, 044h, 024h, 02Ch, 0D9h, 044h
    db 024h, 024h, 0D9h, 0E1h, 0D8h, 044h, 024h, 030h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh
    db 0DEh, 0C1h, 0D9h, 05Ch, 024h, 048h, 0DDh, 0D8h, 0DDh, 0D8h, 0D9h, 044h, 024h, 048h, 0D9h, 0FAh
    db 0D9h, 05Ch, 024h, 04Ch, 0D9h, 044h, 024h, 034h, 08Bh, 04Ch, 024h, 014h, 03Bh, 0CFh, 0D8h, 044h
    db 024h, 028h, 08Bh, 044h, 024h, 04Ch, 05Dh, 0D8h, 005h
    dd ?g_pathfindDoubleCellSize@@3MB
    db 089h, 086h, 080h, 000h, 000h, 000h, 0C6h, 044h, 024h, 03Ch, 000h, 05Bh, 0D9h, 09Eh, 084h, 000h
    db 000h, 000h, 074h, 03Bh, 08Bh, 044h, 024h, 014h, 02Bh, 0C1h, 0C1h, 0F8h, 002h, 0C1h, 0E0h, 002h
    db 03Dh, 080h, 000h, 000h, 000h, 076h, 01Eh, 051h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 05Fh, 08Bh, 0C6h, 05Eh, 08Bh, 04Ch, 024h, 028h, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 034h, 0C2h, 008h, 000h, 050h, 051h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 08Bh, 04Ch, 024h, 030h, 05Fh, 08Bh, 0C6h, 05Eh, 064h, 089h, 00Dh, 000h, 000h
    db 000h, 000h, 083h, 0C4h, 034h, 0C2h, 008h, 000h
?d_007c2f20@@YAXXZ ENDP
_TEXT$d00bc2f20 ENDS
_TEXT SEGMENT

; ghidra: FUN_00bc3260  retail @ 0x007C3260 size 239
public ?d_007c3260@@YAXXZ
?d_007c3260@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 0EBh, 2Dh, 05h, 01h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 56h, 57h, 8Bh, 0F9h, 0E8h, 0C2h, 0EEh, 13h, 00h, 84h, 0C0h
    db 0Fh, 84h, 0B4h, 00h, 00h, 00h, 8Bh, 74h, 24h, 18h, 85h, 0F6h, 0Fh, 84h, 0A8h, 00h
    db 00h, 00h, 0A1h, 0C8h, 0D5h, 2Eh, 01h, 8Ah, 48h, 64h, 84h, 0C9h, 0Fh, 84h, 98h, 00h
    db 00h, 00h, 68h, 0A0h, 00h, 00h, 00h, 0E8h, 84h, 0ECh, 0Bh, 00h, 83h, 0C4h, 04h, 89h
    db 44h, 24h, 18h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 74h, 10h, 56h
    db 83h, 0C7h, 08h, 57h, 8Bh, 0C8h, 0E8h, 0D4h, 8Ah, 87h, 0FFh, 8Bh, 0F0h, 0EBh, 02h, 33h
    db 0F6h, 8Bh, 4Ch, 24h, 1Ch, 0D9h, 05h, 50h, 53h, 07h, 01h, 0D9h, 81h, 98h, 00h, 00h
    db 00h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 44h
    db 7Bh, 16h, 0D9h, 81h, 98h, 00h, 00h, 00h, 0D8h, 0Dh, 0C0h, 0ECh, 09h, 01h, 0D9h, 0F2h
    db 0DDh, 0D8h, 0D9h, 9Eh, 88h, 00h, 00h, 00h, 8Bh, 4Ch, 24h, 20h, 85h, 0C9h, 74h, 0Bh
    db 6Ah, 02h, 0E8h, 08h, 0F2h, 86h, 0FFh, 84h, 0C0h, 75h, 0Ah, 0C7h, 86h, 8Ch, 00h, 00h
    db 00h, 0CDh, 0CCh, 0CCh, 3Dh, 8Bh, 0C6h, 8Bh, 4Ch, 24h, 08h, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 5Fh, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 0Ch, 00h, 8Bh, 4Ch, 24h, 08h, 5Fh, 33h
    db 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Eh, 83h, 0C4h, 0Ch, 0C2h, 0Ch, 00h
?d_007c3260@@YAXXZ ENDP

; ghidra: FUN_00bc34a0  retail @ 0x007C34A0 size 35
public ?d_007c34a0@@YAXXZ
?d_007c34a0@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 0Ch, 8Bh, 0Ch, 85h, 28h, 9Dh, 2Fh, 01h, 85h, 0C9h, 8Bh, 44h
    db 24h, 08h, 0C7h, 04h, 24h, 00h, 00h, 00h, 00h, 89h, 08h, 74h, 04h, 66h, 0FFh, 41h
    db 04h, 59h, 0C3h
?d_007c34a0@@YAXXZ ENDP

; ghidra: FUN_00bc34e0  retail @ 0x007C34E0 size 2117
public ?d_007c34e0@@YAXXZ
?d_007c34e0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 63h, 2Eh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 90h, 00h, 00h, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 56h, 57h, 8Dh, 54h, 24h, 18h, 52h, 6Ah, 02h, 89h, 4Ch, 24h, 14h, 8Bh, 08h, 50h
    db 0FFh, 91h, 0B4h, 00h, 00h, 00h, 8Bh, 3Dh, 94h, 05h, 34h, 01h, 8Dh, 44h, 24h, 18h
    db 50h, 8Dh, 4Ch, 24h, 18h, 51h, 8Dh, 54h, 24h, 60h, 47h, 52h, 89h, 3Dh, 94h, 05h
    db 34h, 01h, 0E8h, 0EAh, 7Dh, 23h, 00h, 8Bh, 0B4h, 24h, 0A8h, 00h, 00h, 00h, 85h, 0F6h
    db 75h, 58h, 0A0h, 0FCh, 6Dh, 2Dh, 01h, 84h, 0C0h, 0A1h, 60h, 6Eh, 2Dh, 01h, 75h, 08h
    db 3Bh, 05h, 0C0h, 0Eh, 34h, 01h, 74h, 42h, 8Bh, 15h, 9Ch, 0F4h, 33h, 01h, 0A3h, 0C0h
    db 0Eh, 34h, 01h, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 00h, 81h, 0CAh, 00h, 80h, 00h, 00h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 10h, 89h, 15h, 9Ch, 0F4h, 33h, 01h, 89h, 44h, 24h, 10h
    db 0E8h, 0Bh, 83h, 21h, 00h, 8Bh, 4Ch, 24h, 08h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h
    db 11h, 8Dh, 4Ch, 24h, 08h, 0E8h, 06h, 82h, 21h, 00h, 53h, 55h, 6Ah, 00h, 8Dh, 44h
    db 24h, 64h, 50h, 8Dh, 4Ch, 24h, 28h, 51h, 0B9h, 0E8h, 0C2h, 2Bh, 01h, 0E8h, 4Dh, 66h
    db 85h, 0FFh, 83h, 0CBh, 0FFh, 83h, 0FEh, 08h, 72h, 21h, 0A1h, 34h, 05h, 34h, 01h, 8Bh
    db 10h, 68h, 00h, 00h, 02h, 00h, 6Ah, 0Bh, 56h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h
    db 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0A5h, 00h, 00h, 00h, 8Bh, 0C6h, 0C1h, 0E0h, 07h
    db 8Dh, 0B8h, 0Ch, 0FAh, 33h, 01h, 81h, 3Fh, 00h, 00h, 02h, 00h, 0Fh, 84h, 8Eh, 00h
    db 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 51h, 8Bh, 0Dh, 24h, 91h, 2Dh
    db 01h, 6Ah, 01h, 89h, 4Ch, 24h, 14h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 0E8h, 7Eh, 82h
    db 21h, 00h, 8Bh, 54h, 24h, 10h, 0A0h, 0C8h, 0ECh, 34h, 01h, 88h, 02h, 68h, 00h, 00h
    db 02h, 00h, 8Dh, 4Ch, 24h, 14h, 6Ah, 0Bh, 51h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h
    db 00h, 00h, 00h, 00h, 0E8h, 0A7h, 39h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h
    db 89h, 9Ch, 24h, 0A8h, 00h, 00h, 00h, 0E8h, 54h, 81h, 21h, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 68h, 00h, 00h, 02h, 00h, 6Ah, 0Bh, 56h, 0C7h, 07h, 00h, 00h, 02h, 00h, 8Bh
    db 10h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 83h, 0FEh, 08h, 72h, 1Eh, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 02h, 6Ah, 18h
    db 56h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0A2h
    db 00h, 00h, 00h, 8Bh, 0D6h, 0C1h, 0E2h, 07h, 8Bh, 82h, 40h, 0FAh, 33h, 01h, 83h, 0F8h
    db 02h, 8Dh, 0BAh, 40h, 0FAh, 33h, 01h, 0Fh, 84h, 88h, 00h, 00h, 00h, 0A0h, 51h, 0F4h
    db 33h, 01h, 84h, 0C0h, 74h, 4Eh, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh
    db 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 0E8h, 0B4h, 81h, 21h, 00h, 8Bh, 4Ch, 24h, 10h
    db 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 6Ah, 02h, 8Dh, 44h, 24h, 14h, 6Ah, 18h
    db 50h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h, 01h, 00h, 00h, 00h, 0E8h, 0DFh, 38h, 14h
    db 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 9Ch, 24h, 0A8h, 00h, 00h, 00h, 0E8h
    db 8Ch, 80h, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 02h, 6Ah, 18h, 56h, 0C7h, 07h
    db 02h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h
    db 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h
    db 0A3h, 68h, 05h, 34h, 01h, 0A1h, 4Ch, 05h, 34h, 01h, 8Dh, 4Ch, 24h, 20h, 51h, 40h
    db 0A3h, 4Ch, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 8Dh, 4Eh, 10h, 51h
    db 50h, 0FFh, 92h, 0B0h, 00h, 00h, 00h, 8Bh, 2Dh, 94h, 05h, 34h, 01h, 0A1h, 34h, 05h
    db 34h, 01h, 6Ah, 02h, 6Ah, 06h, 45h, 56h, 89h, 2Dh, 94h, 05h, 34h, 01h, 8Bh, 10h
    db 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h
    db 34h, 01h, 41h, 6Ah, 02h, 40h, 6Ah, 05h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 34h, 05h
    db 34h, 01h, 56h, 89h, 0Dh, 94h, 05h, 34h, 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h
    db 00h, 00h, 8Bh, 3Dh, 94h, 05h, 34h, 01h, 8Bh, 15h, 68h, 05h, 34h, 01h, 0A1h, 34h
    db 05h, 34h, 01h, 6Ah, 01h, 6Ah, 01h, 47h, 42h, 56h, 89h, 3Dh, 94h, 05h, 34h, 01h
    db 89h, 15h, 68h, 05h, 34h, 01h, 8Bh, 10h, 50h, 0FFh, 92h, 14h, 01h, 00h, 00h, 0A1h
    db 94h, 05h, 34h, 01h, 8Bh, 2Dh, 68h, 05h, 34h, 01h, 6Ah, 01h, 40h, 6Ah, 02h, 0A3h
    db 94h, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 45h, 56h, 89h, 2Dh, 68h, 05h, 34h
    db 01h, 8Bh, 08h, 50h, 0FFh, 91h, 14h, 01h, 00h, 00h, 8Bh, 15h, 94h, 05h, 34h, 01h
    db 8Bh, 0Dh, 68h, 05h, 34h, 01h, 42h, 41h, 83h, 0FEh, 08h, 89h, 15h, 94h, 05h, 34h
    db 01h, 89h, 0Dh, 68h, 05h, 34h, 01h, 72h, 1Eh, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h
    db 6Ah, 02h, 6Ah, 02h, 56h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h
    db 34h, 01h, 0E9h, 9Ch, 00h, 00h, 00h, 8Bh, 0C6h, 0C1h, 0E0h, 07h, 8Dh, 0B8h, 0E8h, 0F9h
    db 33h, 01h, 83h, 3Fh, 02h, 0Fh, 84h, 88h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h
    db 84h, 0C0h, 74h, 4Eh, 8Bh, 0Dh, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 89h, 4Ch, 24h, 14h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 0E8h, 15h, 80h, 21h, 00h, 8Bh, 54h, 24h, 10h, 0A0h
    db 0C8h, 0ECh, 34h, 01h, 88h, 02h, 6Ah, 02h, 8Dh, 4Ch, 24h, 14h, 6Ah, 02h, 51h, 0C7h
    db 84h, 24h, 0B4h, 00h, 00h, 00h, 02h, 00h, 00h, 00h, 0E8h, 41h, 37h, 14h, 00h, 83h
    db 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 9Ch, 24h, 0A8h, 00h, 00h, 00h, 0E8h, 0EEh, 7Eh
    db 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 02h, 6Ah, 02h, 56h, 0C7h, 07h, 02h, 00h
    db 00h, 00h, 8Bh, 10h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h
    db 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h
    db 05h, 34h, 01h, 83h, 0FEh, 08h, 72h, 1Eh, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah
    db 01h, 6Ah, 03h, 56h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h
    db 01h, 0E9h, 0A2h, 00h, 00h, 00h, 8Bh, 0D6h, 0C1h, 0E2h, 07h, 8Bh, 82h, 0ECh, 0F9h, 33h
    db 01h, 83h, 0F8h, 01h, 8Dh, 0BAh, 0ECh, 0F9h, 33h, 01h, 0Fh, 84h, 88h, 00h, 00h, 00h
    db 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Eh, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 0E8h, 51h, 7Fh, 21h, 00h, 8Bh
    db 4Ch, 24h, 10h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 6Ah, 01h, 8Dh, 44h, 24h
    db 14h, 6Ah, 03h, 50h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h, 03h, 00h, 00h, 00h, 0E8h
    db 7Ch, 36h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 9Ch, 24h, 0A8h, 00h
    db 00h, 00h, 0E8h, 29h, 7Eh, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 01h, 6Ah, 03h
    db 56h, 0C7h, 07h, 01h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h
    db 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h
    db 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 0FEh, 08h, 72h, 1Eh, 0A1h, 34h, 05h
    db 34h, 01h, 8Bh, 10h, 6Ah, 04h, 6Ah, 01h, 56h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h
    db 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 9Ch, 00h, 00h, 00h, 8Bh, 0C6h, 0C1h, 0E0h, 07h
    db 8Dh, 0B8h, 0E4h, 0F9h, 33h, 01h, 83h, 3Fh, 04h, 0Fh, 84h, 88h, 00h, 00h, 00h, 0A0h
    db 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Eh, 8Bh, 0Dh, 24h, 91h, 2Dh, 01h, 6Ah, 01h
    db 89h, 4Ch, 24h, 14h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 0E8h, 91h, 7Eh, 21h, 00h, 8Bh
    db 54h, 24h, 10h, 0A0h, 0C8h, 0ECh, 34h, 01h, 88h, 02h, 6Ah, 04h, 8Dh, 4Ch, 24h, 14h
    db 6Ah, 01h, 51h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h, 04h, 00h, 00h, 00h, 0E8h, 0BDh
    db 35h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 9Ch, 24h, 0A8h, 00h, 00h
    db 00h, 0E8h, 6Ah, 7Dh, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah, 04h, 6Ah, 01h, 56h
    db 0C7h, 07h, 04h, 00h, 00h, 00h, 8Bh, 10h, 50h, 0FFh, 92h, 0Ch, 01h, 00h, 00h, 8Bh
    db 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h
    db 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 0FEh, 08h, 72h, 1Eh, 0A1h, 34h, 05h, 34h
    db 01h, 8Bh, 08h, 6Ah, 02h, 6Ah, 05h, 56h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 0FFh
    db 05h, 94h, 05h, 34h, 01h, 0E9h, 0A2h, 00h, 00h, 00h, 8Bh, 0D6h, 0C1h, 0E2h, 07h, 8Bh
    db 82h, 0F4h, 0F9h, 33h, 01h, 83h, 0F8h, 02h, 8Dh, 0BAh, 0F4h, 0F9h, 33h, 01h, 0Fh, 84h
    db 88h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Eh, 0A1h, 24h, 91h
    db 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 0E8h, 0CDh
    db 7Dh, 21h, 00h, 8Bh, 4Ch, 24h, 10h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 6Ah
    db 02h, 8Dh, 44h, 24h, 14h, 6Ah, 05h, 50h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h, 05h
    db 00h, 00h, 00h, 0E8h, 0F8h, 34h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h
    db 9Ch, 24h, 0A8h, 00h, 00h, 00h, 0E8h, 0A5h, 7Ch, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h
    db 6Ah, 02h, 6Ah, 05h, 56h, 0C7h, 07h, 02h, 00h, 00h, 00h, 8Bh, 08h, 50h, 0FFh, 91h
    db 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h
    db 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 0FEh, 08h, 72h
    db 1Eh, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 01h, 6Ah, 06h, 56h, 50h, 0FFh, 92h
    db 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 9Ch, 00h, 00h, 00h, 8Bh
    db 0C6h, 0C1h, 0E0h, 07h, 8Dh, 0B8h, 0F8h, 0F9h, 33h, 01h, 83h, 3Fh, 01h, 0Fh, 84h, 88h
    db 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Eh, 8Bh, 0Dh, 24h, 91h
    db 2Dh, 01h, 6Ah, 01h, 89h, 4Ch, 24h, 14h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 0E8h, 0Dh
    db 7Dh, 21h, 00h, 8Bh, 54h, 24h, 10h, 0A0h, 0C8h, 0ECh, 34h, 01h, 88h, 02h, 6Ah, 01h
    db 8Dh, 4Ch, 24h, 14h, 6Ah, 06h, 51h, 0C7h, 84h, 24h, 0B4h, 00h, 00h, 00h, 06h, 00h
    db 00h, 00h, 0E8h, 39h, 34h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 9Ch
    db 24h, 0A8h, 00h, 00h, 00h, 0E8h, 0E6h, 7Bh, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 6Ah
    db 01h, 6Ah, 06h, 56h, 0C7h, 07h, 01h, 00h, 00h, 00h, 8Bh, 10h, 50h, 0FFh, 92h, 0Ch
    db 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h, 41h, 40h
    db 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 0FEh, 08h, 72h, 1Eh
    db 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 6Ah, 03h, 6Ah, 04h, 56h, 50h, 0FFh, 91h, 0Ch
    db 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0A2h, 00h, 00h, 00h, 8Bh, 0D6h
    db 0C1h, 0E2h, 07h, 8Bh, 82h, 0F0h, 0F9h, 33h, 01h, 83h, 0F8h, 03h, 8Dh, 0BAh, 0F0h, 0F9h
    db 33h, 01h, 0Fh, 84h, 88h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h
    db 4Eh, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 89h, 44h
    db 24h, 18h, 0E8h, 49h, 7Ch, 21h, 00h, 8Bh, 4Ch, 24h, 10h, 8Ah, 15h, 0C8h, 0ECh, 34h
    db 01h, 88h, 11h, 6Ah, 03h, 8Dh, 44h, 24h, 14h, 6Ah, 04h, 50h, 0C7h, 84h, 24h, 0B4h
    db 00h, 00h, 00h, 07h, 00h, 00h, 00h, 0E8h, 74h, 33h, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh
    db 4Ch, 24h, 10h, 89h, 9Ch, 24h, 0A8h, 00h, 00h, 00h, 0E8h, 21h, 7Bh, 21h, 00h, 0A1h
    db 34h, 05h, 34h, 01h, 6Ah, 03h, 6Ah, 04h, 56h, 0C7h, 07h, 03h, 00h, 00h, 00h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h
    db 8Dh, 54h, 24h, 18h, 56h, 52h, 0E8h, 32h, 71h, 85h, 0FFh, 83h, 0C4h, 08h, 8Bh, 3Dh
    db 34h, 05h, 34h, 01h, 8Bh, 2Fh, 8Bh, 0C8h, 0C7h, 84h, 24h, 0A8h, 00h, 00h, 00h, 08h
    db 00h, 00h, 00h, 0E8h, 88h, 9Fh, 14h, 00h, 50h, 56h, 57h, 0FFh, 95h, 04h, 01h, 00h
    db 00h, 8Bh, 4Ch, 24h, 18h, 85h, 0C9h, 5Dh, 89h, 9Ch, 24h, 0A4h, 00h, 00h, 00h, 5Bh
    db 74h, 0Eh, 0E8h, 0A9h, 7Ah, 22h, 00h, 8Bh, 44h, 24h, 0Ch, 89h, 70h, 08h, 0EBh, 07h
    db 8Bh, 4Ch, 24h, 0Ch, 89h, 71h, 08h, 8Bh, 8Ch, 24h, 98h, 00h, 00h, 00h, 5Fh, 0B8h
    db 01h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 9Ch, 00h
    db 00h, 00h, 0C2h, 04h, 00h
?d_007c34e0@@YAXXZ ENDP

; ghidra: FUN_00bc3f80  retail @ 0x007C3F80 size 21
public ?d_007c3f80@@YAXXZ
?d_007c3f80@@YAXXZ PROC
    db 0B8h, 01h, 00h, 00h, 00h, 0C7h, 05h, 9Ch, 9Ch, 2Fh, 01h, 84h, 0BFh, 2Bh, 01h, 0A3h
    db 54h, 9Ch, 2Fh, 01h, 0C3h
?d_007c3f80@@YAXXZ ENDP

; ghidra: FUN_00bc3fd0  retail @ 0x007C3FD0 size 1337
public ?d_007c3fd0@@YAXXZ
?d_007c3fd0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0C7h, 2Eh, 05h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0D8h, 01h, 00h, 00h, 53h, 55h, 56h, 57h, 8Bh
    db 0D9h, 6Ah, 00h, 89h, 5Ch, 24h, 24h, 0E8h, 0C4h, 0D2h, 15h, 00h, 8Bh, 0F0h, 83h, 0C4h
    db 04h, 85h, 0F6h, 74h, 03h, 0FFh, 46h, 04h, 0A1h, 0C4h, 0Eh, 34h, 01h, 85h, 0C0h, 74h
    db 15h, 8Bh, 78h, 04h, 8Bh, 0C8h, 83h, 0C0h, 04h, 4Fh, 8Bh, 0D7h, 85h, 0D2h, 89h, 38h
    db 75h, 04h, 8Bh, 01h, 0FFh, 10h, 8Bh, 0Dh, 9Ch, 0F4h, 33h, 01h, 81h, 0C9h, 00h, 40h
    db 00h, 00h, 85h, 0F6h, 89h, 35h, 0C4h, 0Eh, 34h, 01h, 89h, 0Dh, 9Ch, 0F4h, 33h, 01h
    db 74h, 0Bh, 0FFh, 4Eh, 04h, 75h, 06h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 12h, 8Dh, 44h, 24h
    db 14h, 6Ah, 00h, 50h, 0E8h, 94h, 6Dh, 85h, 0FFh, 8Bh, 0ACh, 24h, 00h, 02h, 00h, 00h
    db 50h, 55h, 0C7h, 84h, 24h, 00h, 02h, 00h, 00h, 00h, 00h, 00h, 00h, 0E8h, 4Eh, 1Ah
    db 14h, 00h, 8Bh, 4Ch, 24h, 24h, 83h, 0CFh, 0FFh, 83h, 0C4h, 10h, 85h, 0C9h, 89h, 0BCh
    db 24h, 0F0h, 01h, 00h, 00h, 74h, 05h, 0E8h, 14h, 77h, 22h, 00h, 85h, 0EDh, 75h, 58h
    db 0A0h, 0FCh, 6Dh, 2Dh, 01h, 84h, 0C0h, 0A1h, 60h, 6Eh, 2Dh, 01h, 75h, 08h, 3Bh, 05h
    db 0C0h, 0Eh, 34h, 01h, 74h, 42h, 8Bh, 15h, 9Ch, 0F4h, 33h, 01h, 8Bh, 0Dh, 24h, 91h
    db 2Dh, 01h, 6Ah, 00h, 81h, 0CAh, 00h, 80h, 00h, 00h, 89h, 4Ch, 24h, 14h, 6Ah, 00h
    db 8Dh, 4Ch, 24h, 18h, 0A3h, 0C0h, 0Eh, 34h, 01h, 89h, 15h, 9Ch, 0F4h, 33h, 01h, 0E8h
    db 0BCh, 77h, 21h, 00h, 8Bh, 54h, 24h, 10h, 0A0h, 0C8h, 0ECh, 34h, 01h, 8Dh, 4Ch, 24h
    db 10h, 88h, 02h, 0E8h, 0B8h, 76h, 21h, 00h, 0E8h, 0A3h, 07h, 14h, 00h, 83h, 0FDh, 08h
    db 72h, 21h, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 08h, 68h, 00h, 00h, 02h, 00h, 6Ah, 0Bh
    db 55h, 50h, 0FFh, 91h, 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 0AAh
    db 00h, 00h, 00h, 8Bh, 0D5h, 0C1h, 0E2h, 07h, 8Bh, 82h, 0Ch, 0FAh, 33h, 01h, 3Dh, 00h
    db 00h, 02h, 00h, 8Dh, 0B2h, 0Ch, 0FAh, 33h, 01h, 0Fh, 84h, 8Eh, 00h, 00h, 00h, 0A0h
    db 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 51h, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah
    db 00h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 0E8h, 42h, 77h, 21h, 00h, 8Bh, 4Ch
    db 24h, 10h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 68h, 00h, 00h, 02h, 00h, 8Dh
    db 44h, 24h, 14h, 6Ah, 0Bh, 50h, 0C7h, 84h, 24h, 0FCh, 01h, 00h, 00h, 01h, 00h, 00h
    db 00h, 0E8h, 6Ah, 2Eh, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 0BCh, 24h
    db 0F0h, 01h, 00h, 00h, 0E8h, 17h, 76h, 21h, 00h, 0A1h, 34h, 05h, 34h, 01h, 68h, 00h
    db 00h, 02h, 00h, 6Ah, 0Bh, 55h, 0C7h, 06h, 00h, 00h, 02h, 00h, 8Bh, 08h, 50h, 0FFh
    db 91h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h
    db 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 83h, 0FDh, 08h
    db 72h, 1Eh, 0A1h, 34h, 05h, 34h, 01h, 8Bh, 10h, 6Ah, 02h, 6Ah, 18h, 55h, 50h, 0FFh
    db 92h, 0Ch, 01h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 0E9h, 9Dh, 00h, 00h, 00h
    db 8Bh, 0C5h, 0C1h, 0E0h, 07h, 8Dh, 0B0h, 40h, 0FAh, 33h, 01h, 83h, 3Eh, 02h, 0Fh, 84h
    db 89h, 00h, 00h, 00h, 0A0h, 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 4Fh, 8Bh, 0Dh, 24h
    db 91h, 2Dh, 01h, 6Ah, 01h, 89h, 4Ch, 24h, 14h, 6Ah, 00h, 8Dh, 4Ch, 24h, 18h, 0E8h
    db 7Ch, 76h, 21h, 00h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 8Bh, 44h, 24h, 10h, 88h, 10h
    db 6Ah, 02h, 8Dh, 4Ch, 24h, 14h, 6Ah, 18h, 51h, 0C7h, 84h, 24h, 0FCh, 01h, 00h, 00h
    db 02h, 00h, 00h, 00h, 0E8h, 0A7h, 2Dh, 14h, 00h, 83h, 0C4h, 0Ch, 8Dh, 4Ch, 24h, 10h
    db 89h, 0BCh, 24h, 0F0h, 01h, 00h, 00h, 0E8h, 54h, 75h, 21h, 00h, 0A1h, 34h, 05h, 34h
    db 01h, 6Ah, 02h, 6Ah, 18h, 55h, 0C7h, 06h, 02h, 00h, 00h, 00h, 8Bh, 10h, 50h, 0FFh
    db 92h, 0Ch, 01h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 68h, 05h, 34h, 01h
    db 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 68h, 05h, 34h, 01h, 0A1h, 5Ch, 01h
    db 34h, 01h, 0BEh, 03h, 00h, 00h, 00h, 3Bh, 0C6h, 0Fh, 84h, 81h, 00h, 00h, 00h, 0A0h
    db 51h, 0F4h, 33h, 01h, 84h, 0C0h, 74h, 49h, 0A1h, 24h, 91h, 2Dh, 01h, 6Ah, 01h, 6Ah
    db 00h, 8Dh, 4Ch, 24h, 18h, 89h, 44h, 24h, 18h, 0E8h, 0E2h, 75h, 21h, 00h, 8Bh, 4Ch
    db 24h, 10h, 8Ah, 15h, 0C8h, 0ECh, 34h, 01h, 88h, 11h, 56h, 8Dh, 44h, 24h, 14h, 6Ah
    db 17h, 50h, 89h, 0B4h, 24h, 0FCh, 01h, 00h, 00h, 0E8h, 12h, 39h, 14h, 00h, 83h, 0C4h
    db 0Ch, 8Dh, 4Ch, 24h, 10h, 89h, 0BCh, 24h, 0F0h, 01h, 00h, 00h, 0E8h, 0BFh, 74h, 21h
    db 00h, 0A1h, 34h, 05h, 34h, 01h, 56h, 6Ah, 17h, 89h, 35h, 5Ch, 01h, 34h, 01h, 8Bh
    db 08h, 50h, 0FFh, 91h, 0E4h, 00h, 00h, 00h, 8Bh, 0Dh, 94h, 05h, 34h, 01h, 0A1h, 64h
    db 05h, 34h, 01h, 41h, 40h, 89h, 0Dh, 94h, 05h, 34h, 01h, 0A3h, 64h, 05h, 34h, 01h
    db 8Bh, 15h, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 0B2h, 0B8h, 30h, 00h, 00h, 85h, 0F6h, 0Fh, 84h
    db 0C2h, 01h, 00h, 00h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh, 0E8h, 8Fh, 0F8h, 84h, 0FFh
    db 83h, 38h, 00h, 8Bh, 4Ch, 24h, 14h, 0Fh, 95h, 0C3h, 85h, 0C9h, 74h, 05h, 0E8h, 5Dh
    db 74h, 22h, 00h, 84h, 0DBh, 74h, 47h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CEh, 0E8h, 6Ch
    db 0F8h, 84h, 0FFh, 8Bh, 3Dh, 34h, 05h, 34h, 01h, 8Bh, 1Fh, 8Bh, 0C8h, 0C7h, 84h, 24h
    db 0F0h, 01h, 00h, 00h, 04h, 00h, 00h, 00h, 0E8h, 0F3h, 98h, 14h, 00h, 50h, 55h, 57h
    db 0FFh, 93h, 04h, 01h, 00h, 00h, 8Bh, 4Ch, 24h, 14h, 85h, 0C9h, 0C7h, 84h, 24h, 0F0h
    db 01h, 00h, 00h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 05h, 0E8h, 12h, 74h, 22h, 00h, 0A1h, 34h
    db 05h, 34h, 01h, 8Bh, 10h, 8Dh, 4Ch, 24h, 28h, 51h, 6Ah, 02h, 50h, 0FFh, 92h, 0B4h
    db 00h, 00h, 00h, 0A1h, 94h, 05h, 34h, 01h, 40h, 8Dh, 54h, 24h, 28h, 0A3h, 94h, 05h
    db 34h, 01h, 52h, 8Dh, 44h, 24h, 28h, 50h, 8Dh, 8Ch, 24h, 0F0h, 00h, 00h, 00h, 51h
    db 0E8h, 5Ch, 6Fh, 23h, 00h, 8Bh, 46h, 14h, 8Bh, 0Dh, 0E0h, 7Fh, 2Fh, 01h, 8Bh, 56h
    db 10h, 89h, 44h, 24h, 18h, 8Bh, 81h, 0F4h, 2Fh, 00h, 00h, 85h, 0C0h, 0C7h, 44h, 24h
    db 1Ch, 00h, 00h, 00h, 00h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 89h, 54h, 24h
    db 14h, 74h, 16h, 0D9h, 44h, 24h, 14h, 0D8h, 66h, 2Ch, 0D9h, 5Ch, 24h, 1Ch, 0D9h, 44h
    db 24h, 18h, 0D8h, 66h, 30h, 0D9h, 5Ch, 24h, 10h, 8Bh, 54h, 24h, 10h, 8Bh, 44h, 24h
    db 1Ch, 6Ah, 00h, 52h, 50h, 8Dh, 8Ch, 24h, 74h, 01h, 00h, 00h, 51h, 0E8h, 62h, 73h
    db 23h, 00h, 0DBh, 46h, 24h, 68h, 00h, 00h, 80h, 3Fh, 83h, 0ECh, 08h, 0D8h, 4Ch, 24h
    db 24h, 8Dh, 94h, 24h, 0B4h, 00h, 00h, 00h, 0D8h, 3Dh, 34h, 53h, 07h, 01h, 0D9h, 5Ch
    db 24h, 04h, 0DBh, 46h, 20h, 0D8h, 4Ch, 24h, 20h, 0D8h, 3Dh, 34h, 53h, 07h, 01h, 0D9h
    db 1Ch, 24h, 52h, 0E8h, 9Ch, 72h, 23h, 00h, 8Dh, 84h, 24h, 68h, 01h, 00h, 00h, 50h
    db 8Dh, 8Ch, 24h, 0ECh, 00h, 00h, 00h, 51h, 8Dh, 54h, 24h, 70h, 52h, 0E8h, 3Bh, 68h
    db 23h, 00h, 0B9h, 10h, 00h, 00h, 00h, 8Dh, 74h, 24h, 68h, 8Dh, 0BCh, 24h, 28h, 01h
    db 00h, 00h, 8Dh, 84h, 24h, 0A8h, 00h, 00h, 00h, 0F3h, 0A5h, 50h, 8Dh, 8Ch, 24h, 2Ch
    db 01h, 00h, 00h, 51h, 8Dh, 94h, 24h, 0B0h, 01h, 00h, 00h, 52h, 0E8h, 0Ch, 68h, 23h
    db 00h, 8Bh, 1Dh, 4Ch, 05h, 34h, 01h, 0A1h, 34h, 05h, 34h, 01h, 8Dh, 54h, 24h, 28h
    db 52h, 8Dh, 55h, 10h, 0B9h, 10h, 00h, 00h, 00h, 8Dh, 0B4h, 24h, 0ACh, 01h, 00h, 00h
    db 8Dh, 7Ch, 24h, 2Ch, 43h, 52h, 0F3h, 0A5h, 89h, 1Dh, 4Ch, 05h, 34h, 01h, 8Bh, 08h
    db 50h, 0FFh, 91h, 0B0h, 00h, 00h, 00h, 0FFh, 05h, 94h, 05h, 34h, 01h, 8Bh, 44h, 24h
    db 20h, 89h, 68h, 08h, 0EBh, 03h, 89h, 6Bh, 08h, 8Bh, 8Ch, 24h, 0E8h, 01h, 00h, 00h
    db 5Fh, 5Eh, 5Dh, 0B8h, 01h, 00h, 00h, 00h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0E4h, 01h, 00h, 00h, 0C2h, 04h, 00h
?d_007c3fd0@@YAXXZ ENDP

; ghidra: FUN_00bc7d30  retail @ 0x007C7D30 size 110
public ?d_007c7d30@@YAXXZ
?d_007c7d30@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 08h, 57h, 33h, 0FFh, 3Bh, 0C7h, 74h, 06h, 8Bh, 08h, 50h
    db 0FFh, 51h, 08h, 8Bh, 46h, 18h, 3Bh, 0C7h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h
    db 8Bh, 46h, 1Ch, 3Bh, 0C7h, 74h, 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 46h, 14h
    db 3Bh, 0C7h, 74h, 06h, 8Bh, 10h, 50h, 0FFh, 52h, 08h, 8Bh, 46h, 0Ch, 3Bh, 0C7h, 74h
    db 06h, 8Bh, 08h, 50h, 0FFh, 51h, 08h, 8Bh, 46h, 10h, 3Bh, 0C7h, 74h, 06h, 8Bh, 10h
    db 50h, 0FFh, 52h, 08h, 89h, 7Eh, 08h, 89h, 7Eh, 18h, 89h, 7Eh, 1Ch, 89h, 7Eh, 14h
    db 89h, 7Eh, 0Ch, 89h, 7Eh, 10h, 5Fh, 0B8h, 01h, 00h, 00h, 00h, 5Eh, 0C3h
?d_007c7d30@@YAXXZ ENDP
_TEXT ENDS
END
