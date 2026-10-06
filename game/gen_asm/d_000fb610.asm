.386
.model flat
; db bodies made symbolic by tools/dump_apply.py (tools/dump_relocs.py + retail .reloc)
EXTERN ??3@YAXPAX@Z:NEAR
EXTERN ??_7BfmeBaseS@@6B@:BYTE
EXTERN ??_7PartitionFilterWouldCollide@@6B@:BYTE
EXTERN ?BfmeBoundaryZero3D@@3MB:BYTE
EXTERN ?KINDOFMASK_NONE@@3UKindOfMaskType@@B:BYTE
EXTERN ?TheControlBar@@3PAURva002AD380ControlBar@@A:BYTE
EXTERN ?ThePartitionManager@@3PAVBfmeWideForwardC@@A:BYTE
EXTERN ?TheTerrainVisual@@3PAVRva001A8820TerrainVisual@@A:BYTE
EXTERN ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z:NEAR
EXTERN ?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHHH@Z:NEAR
EXTERN ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ:NEAR
EXTERN ?boxMinorRadius@BfmeGeometryInfo@@QBEMXZ:NEAR
EXTERN ?d_0087f2f0@@YAXXZ:NEAR
EXTERN ?g_bfmeADL@@3MA:BYTE
EXTERN ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z:NEAR
EXTERN ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z:NEAR
EXTERN ?j_00002135@@YAXXZ:NEAR
EXTERN ?j_000022bb@@YAXXZ:NEAR
EXTERN ?j_000032d8@@YAXXZ:NEAR
EXTERN ?j_00003b52@@YAXXZ:NEAR
EXTERN ?j_00003f80@@YAXXZ:NEAR
EXTERN ?j_00007b4e@@YAXXZ:NEAR
EXTERN ?j_0000ba37@@YAXXZ:NEAR
EXTERN ?j_0000da8a@@YAXXZ:NEAR
EXTERN ?j_00015460@@YAXXZ:NEAR
EXTERN ?j_0001f780@@YAXXZ:NEAR
EXTERN ?j_000205cc@@YAXXZ:NEAR
EXTERN ?j_00020824@@YAXXZ:NEAR
EXTERN ?j_000220c5@@YAXXZ:NEAR
EXTERN ?j_00022336@@YAXXZ:NEAR
EXTERN ?j_000235bf@@YAXXZ:NEAR
EXTERN ?j_000237d1@@YAXXZ:NEAR
EXTERN ?j_00029dc0@@YAXXZ:NEAR
EXTERN ?j_0002b355@@YAXXZ:NEAR
EXTERN ?j_0002c471@@YAXXZ:NEAR
EXTERN ?j_0002ca2f@@YAXXZ:NEAR
EXTERN ?j_000309f4@@YAXXZ:NEAR
EXTERN ?j_0003251f@@YAXXZ:NEAR
EXTERN ?j_000382fd@@YAXXZ:NEAR
EXTERN ?j_0003e80b@@YAXXZ:NEAR
EXTERN ?j_000424b5@@YAXXZ:NEAR
EXTERN ?j_00048cca@@YAXXZ:NEAR
EXTERN ?j_00048d15@@YAXXZ:NEAR
EXTERN ?j_00048d79@@YAXXZ:NEAR
EXTERN ?releaseBuffer@?$StringBase@D@@AAEXXZ:NEAR
EXTERN ?rva000fc2a0Tally@@YAHPAUBfmeThingEJ@@PAURva000FC2A0Tally@@@Z:NEAR
EXTERN ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z:NEAR
EXTERN ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ:NEAR
EXTERN ?value@BfmeReportWeightScaleHolder@@2MB:BYTE
EXTERN __real@3f8ccccd:BYTE
EXTERN g_Va00FFC795:NEAR
_TEXT SEGMENT

; ghidra: FUN_004fb610  retail @ 0x000FB610 size 477
public ?d_000fb610@@YAXXZ
?d_000fb610@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 2Ch, 0C4h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 7Ch, 53h, 56h, 8Bh, 0D9h, 57h, 8Bh, 0BCh, 24h
    db 98h, 00h, 00h, 00h, 8Bh, 07h, 8Dh, 4Ch, 24h, 14h, 51h, 8Bh, 0CFh, 0C6h, 44h, 24h
    db 18h, 01h, 0C6h, 44h, 24h, 19h, 01h, 0FFh, 50h, 28h, 8Bh, 53h, 04h, 8Bh, 4Bh, 08h
    db 8Dh, 73h, 04h, 2Bh, 0CAh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah, 0F7h, 0E9h, 0C1h, 0FAh, 04h, 8Bh
    db 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Bh, 17h, 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 10h
    db 50h, 8Bh, 0CFh, 0FFh, 52h, 74h, 8Bh, 17h, 8Bh, 0CFh, 0FFh, 52h, 08h, 84h, 0C0h, 74h
    db 51h, 8Bh, 36h, 3Bh, 73h, 08h, 74h, 12h, 57h, 8Bh, 0CEh, 0E8h, 4Bh, 0A2h, 0F4h, 0FFh
    db 8Bh, 43h, 08h, 83h, 0C6h, 60h, 3Bh, 0F0h, 75h, 0EEh, 8Bh, 43h, 10h, 85h, 0C0h, 74h
    db 18h, 8Bh, 40h, 24h, 8Bh, 17h, 89h, 44h, 24h, 18h, 8Dh, 44h, 24h, 18h, 50h, 8Bh
    db 0CFh, 0FFh, 52h, 78h, 0E9h, 1Ah, 01h, 00h, 00h, 8Bh, 17h, 8Dh, 44h, 24h, 18h, 50h
    db 8Bh, 0CFh, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 52h, 78h, 0E9h, 01h, 01h
    db 00h, 00h, 8Bh, 46h, 04h, 8Bh, 0Eh, 55h, 50h, 51h, 8Bh, 0CEh, 0E8h, 5Ch, 1Fh, 0F2h
    db 0FFh, 8Bh, 44h, 24h, 14h, 33h, 0EDh, 85h, 0C0h, 0Fh, 86h, 0B6h, 00h, 00h, 00h, 8Dh
    db 4Ch, 24h, 70h, 89h, 4Ch, 24h, 1Ch, 8Dh, 4Ch, 24h, 2Ch, 0E8h, 35h, 6Bh, 0F4h, 0FFh
    db 57h, 8Dh, 4Ch, 24h, 30h, 0C7h, 84h, 24h, 98h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0E8h, 0C6h, 0A1h, 0F4h, 0FFh, 8Bh, 46h, 04h, 3Bh, 46h, 08h, 74h, 26h, 89h, 44h, 24h
    db 24h, 89h, 44h, 24h, 28h, 85h, 0C0h, 0C6h, 84h, 24h, 94h, 00h, 00h, 00h, 01h, 74h
    db 0Ch, 8Dh, 54h, 24h, 2Ch, 52h, 8Bh, 0C8h, 0E8h, 22h, 0CDh, 0F4h, 0FFh, 83h, 46h, 04h
    db 60h, 0EBh, 16h, 6Ah, 01h, 6Ah, 01h, 8Dh, 4Ch, 24h, 1Bh, 51h, 8Dh, 54h, 24h, 38h
    db 52h, 50h, 8Bh, 0CEh, 0E8h, 8Ah, 0AFh, 0F2h, 0FFh, 8Dh, 8Ch, 24h, 88h, 00h, 00h, 00h
    db 0C7h, 84h, 24h, 94h, 00h, 00h, 00h, 03h, 00h, 00h, 00h, 0E8h, 0D0h, 0C1h, 78h, 00h
    db 8Dh, 8Ch, 24h, 84h, 00h, 00h, 00h, 0C6h, 84h, 24h, 94h, 00h, 00h, 00h, 02h, 0E8h
    db 4Ch, 0CAh, 78h, 00h, 8Dh, 4Ch, 24h, 2Ch, 0C7h, 84h, 24h, 94h, 00h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0A8h, 0C1h, 78h, 00h, 8Bh, 44h, 24h, 14h, 45h, 3Bh, 0E8h, 0Fh
    db 82h, 52h, 0FFh, 0FFh, 0FFh, 8Bh, 07h, 8Dh, 4Ch, 24h, 20h, 51h, 8Bh, 0CFh, 0FFh, 50h
    db 78h, 8Bh, 44h, 24h, 20h, 83h, 0F8h, 0FFh, 5Dh, 74h, 11h, 8Bh, 0Dh, 48h, 0D7h, 2Eh
    db 01h, 50h, 0E8h, 69h, 97h, 0F4h, 0FFh, 89h, 43h, 10h, 0EBh, 07h, 0C7h, 43h, 10h, 00h
    db 00h, 00h, 00h, 8Bh, 8Ch, 24h, 88h, 00h, 00h, 00h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 81h, 0C4h, 88h, 00h, 00h, 00h, 0C2h, 04h, 00h
?d_000fb610@@YAXXZ ENDP

; ghidra: FUN_004fbcb0  retail @ 0x000FBCB0 size 60
public ?d_000fbcb0@@YAXXZ
?d_000fbcb0@@YAXXZ PROC
    db 8Bh, 0C1h, 8Bh, 4Ch, 24h, 04h, 0C7h, 40h, 04h, 00h, 00h, 00h, 00h, 0C7h, 00h, 0A0h
    db 60h, 08h, 01h, 8Bh, 11h, 89h, 50h, 08h, 8Bh, 51h, 04h, 89h, 50h, 0Ch, 8Bh, 49h
    db 08h, 8Bh, 54h, 24h, 08h, 89h, 48h, 10h, 8Bh, 4Ch, 24h, 0Ch, 89h, 50h, 14h, 8Ah
    db 54h, 24h, 10h, 89h, 48h, 18h, 88h, 50h, 1Ch, 0C2h, 10h, 00h
?d_000fbcb0@@YAXXZ ENDP

; ghidra: FUN_004fc010  retail @ 0x000FC010 size 519
public ?d_000fc010@@YAXXZ
?d_000fc010@@YAXXZ PROC
    db 64h, 0A1h, 00h, 00h, 00h, 00h, 6Ah, 0FFh, 68h, 5Bh, 0C4h, 0FFh, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 1Ch, 53h, 8Bh, 5Ch, 24h, 38h, 85h, 0DBh, 56h
    db 8Bh, 0F1h, 0Fh, 84h, 0CAh, 01h, 00h, 00h, 8Bh, 44h, 24h, 40h, 85h, 0C0h, 0Fh, 84h
    db 0BEh, 01h, 00h, 00h, 8Bh, 4Eh, 0Ch, 55h, 8Bh, 6Ch, 24h, 4Ch, 3Bh, 0E9h, 57h, 7Eh
    db 70h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 1Dh, 8Bh, 48h, 0FCh, 8Dh, 78h, 0FCh, 68h, 4Ch
    db 36h, 41h, 00h, 51h, 6Ah, 0Ch, 50h, 0E8h, 0Ah, 0ADh, 8Fh, 00h, 57h, 0E8h, 7Eh, 5Eh
    db 78h, 00h, 83h, 0C4h, 04h, 8Dh, 54h, 6Dh, 00h, 8Dh, 04h, 95h, 04h, 00h, 00h, 00h
    db 50h, 0E8h, 0EAh, 5Eh, 78h, 00h, 83h, 0C4h, 04h, 89h, 44h, 24h, 44h, 33h, 0FFh, 3Bh
    db 0C7h, 89h, 7Ch, 24h, 34h, 74h, 18h, 68h, 4Ch, 36h, 41h, 00h, 68h, 93h, 6Ch, 41h
    db 00h, 55h, 8Dh, 78h, 04h, 6Ah, 0Ch, 57h, 89h, 28h, 0E8h, 35h, 0AEh, 8Fh, 00h, 8Bh
    db 44h, 24h, 48h, 0C7h, 44h, 24h, 34h, 0FFh, 0FFh, 0FFh, 0FFh, 89h, 7Eh, 08h, 89h, 6Eh
    db 0Ch, 0D9h, 00h, 8Bh, 4Eh, 08h, 0D8h, 23h, 89h, 4Ch, 24h, 44h, 0D9h, 40h, 04h, 0D8h
    db 63h, 04h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh, 0D8h, 74h
    db 24h, 4Ch, 0E8h, 51h, 0ADh, 8Fh, 00h, 8Bh, 0F8h, 47h, 3Bh, 0FDh, 7Eh, 02h, 8Bh, 0FDh
    db 8Bh, 44h, 24h, 44h, 0D9h, 0C9h, 8Bh, 0D3h, 0D9h, 5Ch, 24h, 20h, 8Bh, 0Ah, 89h, 08h
    db 0D9h, 5Ch, 24h, 24h, 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 0BDh, 01h, 00h
    db 00h, 00h, 8Dh, 4Ch, 24h, 20h, 89h, 50h, 08h, 89h, 6Ch, 24h, 48h, 0C7h, 44h, 24h
    db 28h, 00h, 00h, 00h, 00h, 0E8h, 58h, 0FCh, 0F2h, 0FFh, 3Bh, 0FDh, 89h, 6Ch, 24h, 50h
    db 0Fh, 8Eh, 9Fh, 00h, 00h, 00h, 8Bh, 44h, 24h, 44h, 83h, 0C0h, 0Ch, 89h, 44h, 24h
    db 10h, 0DBh, 44h, 24h, 50h, 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 6Ah, 00h, 0D8h, 4Ch, 24h
    db 50h, 0D9h, 44h, 24h, 24h, 0D8h, 0C9h, 0D8h, 03h, 0D9h, 5Ch, 24h, 18h, 0D8h, 4Ch, 24h
    db 28h, 0D8h, 43h, 04h, 0D9h, 5Ch, 24h, 1Ch, 8Bh, 44h, 24h, 1Ch, 8Bh, 11h, 50h, 8Bh
    db 44h, 24h, 1Ch, 50h, 0FFh, 52h, 18h, 0D9h, 5Ch, 24h, 1Ch, 8Bh, 44h, 24h, 54h, 8Bh
    db 4Ch, 24h, 40h, 8Bh, 16h, 6Ah, 00h, 50h, 8Bh, 44h, 24h, 44h, 6Ah, 1Fh, 51h, 50h
    db 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0CEh, 0FFh, 52h, 28h, 85h, 0C0h, 75h, 37h, 8Bh, 44h
    db 24h, 10h, 8Bh, 4Ch, 24h, 14h, 8Bh, 0D0h, 89h, 0Ah, 8Bh, 4Ch, 24h, 18h, 89h, 4Ah
    db 04h, 8Bh, 4Ch, 24h, 1Ch, 89h, 4Ah, 08h, 8Bh, 4Ch, 24h, 48h, 41h, 45h, 83h, 0C0h
    db 0Ch, 3Bh, 0EFh, 89h, 4Ch, 24h, 48h, 89h, 6Ch, 24h, 50h, 89h, 44h, 24h, 10h, 0Fh
    db 8Ch, 6Ch, 0FFh, 0FFh, 0FFh, 8Bh, 44h, 24h, 44h, 8Bh, 54h, 24h, 48h, 5Fh, 5Dh, 5Eh
    db 0A3h, 44h, 0D8h, 2Eh, 01h, 89h, 15h, 40h, 0D8h, 2Eh, 01h, 0B8h, 40h, 0D8h, 2Eh, 01h
    db 5Bh, 8Bh, 4Ch, 24h, 1Ch, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 28h, 0C2h
    db 1Ch, 00h, 8Bh, 4Ch, 24h, 24h, 5Eh, 33h, 0C0h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h
    db 00h, 83h, 0C4h, 28h, 0C2h, 1Ch, 00h
?d_000fc010@@YAXXZ ENDP

; ghidra: FUN_004fc5d0  retail @ 0x000FC5D0 size 85
public ?d_000fc5d0@@YAXXZ
?d_000fc5d0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 08h, 2Bh, 0C7h, 0C1h, 0F8h, 04h, 85h, 0C0h
    db 7Eh, 3Dh, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 0D8h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 0C7h, 8Bh, 10h, 8Bh, 0CEh, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h, 8Bh, 40h
    db 08h, 89h, 41h, 08h, 8Dh, 4Fh, 0Ch, 51h, 8Dh, 4Eh, 0Ch, 0E8h, 80h, 0B6h, 78h, 00h
    db 83h, 0C7h, 10h, 83h, 0C6h, 10h, 4Bh, 75h, 0D7h, 8Bh, 0C6h, 5Eh, 5Bh, 5Fh, 0C3h, 8Bh
    db 44h, 24h, 10h, 5Fh, 0C3h
?d_000fc5d0@@YAXXZ ENDP

; ghidra: FUN_004fc640  retail @ 0x000FC640 size 77
public ?d_000fc640@@YAXXZ
?d_000fc640@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 89h, 06h, 8Bh, 4Fh, 04h, 89h
    db 4Eh, 04h, 8Bh, 57h, 08h, 89h, 56h, 08h, 8Bh, 47h, 0Ch, 89h, 46h, 0Ch, 8Dh, 4Fh
    db 10h, 8Bh, 01h, 8Dh, 56h, 10h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h, 8Bh, 49h
    db 08h, 89h, 4Ah, 08h, 8Dh, 57h, 1Ch, 52h, 8Dh, 4Eh, 1Ch, 0E8h, 10h, 0B6h, 78h, 00h
    db 8Ah, 47h, 20h, 88h, 46h, 20h, 5Fh, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_000fc640@@YAXXZ ENDP

; ghidra: FUN_004fc780  retail @ 0x000FC780 size 612
public ?d_000fc780@@YAXXZ
?d_000fc780@@YAXXZ PROC
    db 83h, 0ECh, 5Ch, 57h, 8Bh, 7Ch, 24h, 64h, 85h, 0FFh, 0Fh, 84h, 4Dh, 02h, 00h, 00h
    db 8Bh, 44h, 24h, 6Ch, 85h, 0C0h, 0Fh, 84h, 41h, 02h, 00h, 00h, 55h, 8Bh, 6Ch, 24h
    db 78h, 85h, 0EDh, 0Fh, 84h, 33h, 02h, 00h, 00h, 0D9h, 40h, 04h, 56h, 0D9h, 00h, 8Dh
    db 77h, 60h, 0D9h, 5Ch, 24h, 44h, 8Bh, 0CEh, 0D9h, 5Ch, 24h, 54h, 0D9h, 44h, 24h, 70h
    db 0D9h, 0FFh, 0D9h, 5Ch, 24h, 6Ch, 0D9h, 44h, 24h, 70h, 0D9h, 0FEh, 0D9h, 05h, 50h, 53h
    db 07h, 01h, 0D8h, 0C9h, 0D9h, 44h, 24h, 6Ch, 0D9h, 0C0h, 0D8h, 0C2h, 0D9h, 5Ch, 24h, 38h
    db 0D9h, 44h, 24h, 6Ch, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 0C0h, 0D8h, 0E4h, 0D9h, 5Ch
    db 24h, 3Ch, 0D9h, 0CBh, 0D8h, 0C3h, 0D9h, 5Ch, 24h, 48h, 0DDh, 0DAh, 0D9h, 0C9h, 0D8h, 0E1h
    db 0D9h, 5Ch, 24h, 4Ch, 0DDh, 0D8h, 0E8h, 0C5h, 20h, 78h, 00h, 84h, 0C0h, 74h, 18h, 8Bh
    db 0CEh, 0E8h, 1Ah, 14h, 78h, 00h, 0D9h, 5Ch, 24h, 0Ch, 8Bh, 0CEh, 0E8h, 0FFh, 13h, 78h
    db 00h, 0D9h, 5Ch, 24h, 7Ch, 0EBh, 0Dh, 8Bh, 47h, 70h, 8Bh, 0C8h, 89h, 44h, 24h, 0Ch
    db 89h, 4Ch, 24h, 7Ch, 0D9h, 44h, 24h, 0Ch, 0D9h, 0E0h, 0D9h, 5Ch, 24h, 6Ch, 0D9h, 44h
    db 24h, 0Ch, 0D8h, 44h, 24h, 78h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 6Ch, 0D8h, 5Ch
    db 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 7Eh, 01h, 00h, 00h, 0D9h, 44h, 24h
    db 7Ch, 53h, 8Bh, 9Ch, 24h, 84h, 00h, 00h, 00h, 0D9h, 0E0h, 0D9h, 5Ch, 24h, 1Ch, 0D9h
    db 84h, 24h, 80h, 00h, 00h, 00h, 0D8h, 44h, 24h, 7Ch, 0D9h, 5Ch, 24h, 14h, 8Bh, 0FFh
    db 0D9h, 44h, 24h, 70h, 0D8h, 5Ch, 24h, 10h, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 08h, 8Bh
    db 54h, 24h, 10h, 89h, 54h, 24h, 70h, 8Bh, 44h, 24h, 1Ch, 89h, 44h, 24h, 74h, 0D9h
    db 44h, 24h, 74h, 0D8h, 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Ah, 0Dh, 01h
    db 00h, 00h, 0D9h, 44h, 24h, 40h, 8Bh, 7Ch, 24h, 70h, 0D8h, 4Ch, 24h, 70h, 0D9h, 9Ch
    db 24h, 84h, 00h, 00h, 00h, 0D9h, 44h, 24h, 50h, 0D8h, 4Ch, 24h, 70h, 0D9h, 5Ch, 24h
    db 20h, 0D9h, 44h, 24h, 74h, 0D8h, 9Ch, 24h, 80h, 00h, 00h, 00h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 0Bh, 8Bh, 8Ch, 24h, 80h, 00h, 00h, 00h, 89h, 4Ch, 24h, 74h, 8Bh, 0Dh
    db 0CCh, 0F4h, 2Eh, 01h, 8Bh, 44h, 24h, 74h, 8Bh, 11h, 6Ah, 00h, 57h, 50h, 0FFh, 52h
    db 18h, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0D9h, 44h, 24h, 3Ch, 8Bh, 0CEh, 0D8h, 4Ch, 24h
    db 74h, 0D8h, 84h, 24h, 84h, 00h, 00h, 00h, 0D8h, 0C1h, 0D8h, 44h, 24h, 48h, 0D9h, 5Ch
    db 24h, 24h, 0D9h, 44h, 24h, 4Ch, 0D8h, 4Ch, 24h, 74h, 0D8h, 44h, 24h, 20h, 0D8h, 0C1h
    db 0D8h, 44h, 24h, 58h, 0D9h, 5Ch, 24h, 28h, 0DDh, 0D8h, 0E8h, 91h, 1Fh, 78h, 00h, 84h
    db 0C0h, 75h, 2Fh, 8Bh, 44h, 24h, 78h, 0D9h, 44h, 24h, 24h, 0D8h, 20h, 0D9h, 44h, 24h
    db 28h, 0D8h, 60h, 04h, 0D9h, 0C0h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0CBh, 0DEh, 0C1h, 0D9h, 0FAh
    db 0DDh, 0DAh, 0DDh, 0D8h, 0D8h, 9Ch, 24h, 80h, 00h, 00h, 00h, 0DFh, 0E0h, 0F6h, 0C4h, 41h
    db 74h, 32h, 8Bh, 54h, 24h, 28h, 8Bh, 4Ch, 24h, 24h, 6Ah, 00h, 89h, 4Ch, 24h, 34h
    db 8Bh, 0Dh, 0CCh, 0F4h, 2Eh, 01h, 89h, 54h, 24h, 38h, 8Bh, 01h, 52h, 8Bh, 54h, 24h
    db 2Ch, 52h, 0FFh, 50h, 18h, 0D9h, 5Ch, 24h, 38h, 8Dh, 44h, 24h, 30h, 53h, 50h, 0FFh
    db 0D5h, 83h, 0C4h, 08h, 0D9h, 44h, 24h, 74h, 0D8h, 44h, 24h, 7Ch, 0D9h, 54h, 24h, 74h
    db 0D8h, 5Ch, 24h, 14h, 0DFh, 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Bh, 12h, 0FFh, 0FFh, 0FFh, 0D9h
    db 44h, 24h, 70h, 0D8h, 44h, 24h, 7Ch, 0D9h, 54h, 24h, 70h, 0D8h, 5Ch, 24h, 18h, 0DFh
    db 0E0h, 0F6h, 0C4h, 05h, 0Fh, 8Bh, 0A6h, 0FEh, 0FFh, 0FFh, 5Bh, 5Eh, 5Dh, 5Fh, 83h, 0C4h
    db 5Ch, 0C2h, 18h, 00h
?d_000fc780@@YAXXZ ENDP

; ghidra: FUN_004fcd80  retail @ 0x000FCD80 size 85
public ?d_000fcd80@@YAXXZ
?d_000fcd80@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 08h, 2Bh, 0C7h, 0C1h, 0F8h, 04h, 85h, 0C0h
    db 7Eh, 3Dh, 53h, 56h, 8Bh, 74h, 24h, 18h, 8Bh, 0D8h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 0C7h, 8Bh, 10h, 8Bh, 0CEh, 89h, 11h, 8Bh, 50h, 04h, 89h, 51h, 04h, 8Bh, 40h
    db 08h, 89h, 41h, 08h, 8Dh, 4Fh, 0Ch, 51h, 8Dh, 4Eh, 0Ch, 0E8h, 0D0h, 0AEh, 78h, 00h
    db 83h, 0C7h, 10h, 83h, 0C6h, 10h, 4Bh, 75h, 0D7h, 8Bh, 0C6h, 5Eh, 5Bh, 5Fh, 0C3h, 8Bh
    db 44h, 24h, 10h, 5Fh, 0C3h
?d_000fcd80@@YAXXZ ENDP

; ghidra: FUN_004fced0  retail @ 0x000FCED0 size 73
public ?d_000fced0@@YAXXZ
?d_000fced0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Bh, 07h, 89h, 06h, 8Bh, 4Fh, 04h, 89h
    db 4Eh, 04h, 8Bh, 57h, 08h, 89h, 56h, 08h, 8Bh, 47h, 0Ch, 89h, 46h, 0Ch, 8Bh, 4Fh
    db 10h, 89h, 4Eh, 10h, 8Bh, 57h, 14h, 8Dh, 4Fh, 1Ch, 89h, 56h, 14h, 8Bh, 47h, 18h
    db 51h, 8Dh, 4Eh, 1Ch, 89h, 46h, 18h, 0E8h, 54h, 0ACh, 78h, 00h, 8Ah, 57h, 20h, 5Fh
    db 88h, 56h, 20h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_000fced0@@YAXXZ ENDP

; ghidra: FUN_004fcf70  retail @ 0x000FCF70 size 123
public ?d_000fcf70@@YAXXZ
?d_000fcf70@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 08h, 56h, 8Bh, 74h, 24h, 08h, 2Bh, 0CEh, 0B8h, 39h, 8Eh, 0E3h, 38h
    db 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 85h, 0C0h, 7Eh, 55h
    db 53h, 57h, 8Bh, 7Ch, 24h, 18h, 8Bh, 0D8h, 8Bh, 06h, 89h, 07h, 8Bh, 4Eh, 04h, 89h
    db 4Fh, 04h, 8Bh, 56h, 08h, 89h, 57h, 08h, 8Bh, 46h, 0Ch, 89h, 47h, 0Ch, 8Dh, 4Eh
    db 10h, 8Bh, 01h, 8Dh, 57h, 10h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h, 8Bh, 49h
    db 08h, 89h, 4Ah, 08h, 8Dh, 56h, 1Ch, 52h, 8Dh, 4Fh, 1Ch, 0E8h, 0C0h, 0ACh, 78h, 00h
    db 8Ah, 46h, 20h, 88h, 47h, 20h, 83h, 0C6h, 24h, 83h, 0C7h, 24h, 4Bh, 75h, 0B9h, 8Bh
    db 0C7h, 5Fh, 5Bh, 5Eh, 0C3h, 8Bh, 44h, 24h, 10h, 5Eh, 0C3h
?d_000fcf70@@YAXXZ ENDP

; ghidra: FUN_004fd010  retail @ 0x000FD010 size 8
public ?d_000fd010@@YAXXZ
?d_000fd010@@YAXXZ PROC
    db 83h, 0C1h, 1Ch, 0E9h, 28h, 0A9h, 78h, 00h
?d_000fd010@@YAXXZ ENDP

; ghidra: FUN_004fd020  retail @ 0x000FD020 size 8
public ?d_000fd020@@YAXXZ
?d_000fd020@@YAXXZ PROC
    db 83h, 0C1h, 0Ch, 0E9h, 18h, 0A9h, 78h, 00h
?d_000fd020@@YAXXZ ENDP

; ghidra: FUN_004fd030  retail @ 0x000FD030 size 45
public ?d_000fd030@@YAXXZ
?d_000fd030@@YAXXZ PROC
    db 8Bh, 41h, 2Ch, 8Bh, 51h, 30h, 2Bh, 0D0h, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0EAh, 0C1h
    db 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 74h, 0Ah, 8Bh, 51h, 2Ch, 8Bh, 44h
    db 24h, 04h, 89h, 42h, 08h, 0E8h, 06h, 1Eh, 78h, 00h, 0C2h, 04h, 00h
?d_000fd030@@YAXXZ ENDP

; ghidra: FUN_004fd070  retail @ 0x000FD070 size 45
public ?d_000fd070@@YAXXZ
?d_000fd070@@YAXXZ PROC
    db 8Bh, 41h, 2Ch, 8Bh, 51h, 30h, 2Bh, 0D0h, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0EAh, 0C1h
    db 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 74h, 0Ah, 8Bh, 51h, 2Ch, 8Bh, 44h
    db 24h, 04h, 89h, 42h, 0Ch, 0E8h, 0C6h, 1Dh, 78h, 00h, 0C2h, 04h, 00h
?d_000fd070@@YAXXZ ENDP

; ghidra: FUN_004fd0b0  retail @ 0x000FD0B0 size 134
public ?d_000fd0b0@@YAXXZ
?d_000fd0b0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 10h, 57h, 8Bh, 38h, 3Bh, 0F8h, 74h, 17h, 8Dh, 49h, 00h
    db 8Bh, 4Fh, 08h, 85h, 0C9h, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 8Bh, 3Fh, 3Bh
    db 7Eh, 10h, 75h, 0ECh, 8Bh, 46h, 10h, 8Bh, 38h, 3Bh, 0F8h, 74h, 19h, 8Dh, 49h, 00h
    db 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h, 04h, 15h, 73h, 00h, 8Bh, 46h, 10h, 83h
    db 0C4h, 08h, 3Bh, 0F8h, 75h, 0EAh, 8Bh, 46h, 10h, 89h, 00h, 8Bh, 46h, 10h, 89h, 40h
    db 04h, 8Bh, 46h, 08h, 85h, 0C0h, 74h, 2Bh, 8Bh, 48h, 0FCh, 8Dh, 78h, 0FCh, 68h, 4Ch
    db 36h, 41h, 00h, 51h, 6Ah, 0Ch, 50h, 0E8h, 5Ah, 9Ch, 8Fh, 00h, 57h, 0E8h, 0CEh, 4Dh
    db 78h, 00h, 83h, 0C4h, 04h, 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 0C7h, 46h, 0Ch, 00h
    db 00h, 00h, 00h, 5Fh, 5Eh, 0C3h
?d_000fd0b0@@YAXXZ ENDP

; ghidra: FUN_004fd230  retail @ 0x000FD230 size 100
public ?d_000fd230@@YAXXZ
?d_000fd230@@YAXXZ PROC
    db 8Bh, 44h, 24h, 08h, 53h, 56h, 8Bh, 0F1h, 57h, 6Ah, 00h, 8Dh, 5Eh, 08h, 50h, 8Bh
    db 0CBh, 0C7h, 06h, 00h, 00h, 00h, 00h, 0C7h, 46h, 04h, 00h, 00h, 00h, 00h, 0E8h, 4Ah
    db 99h, 0F2h, 0FFh, 8Bh, 7Ch, 24h, 10h, 85h, 0FFh, 74h, 22h, 8Dh, 04h, 0FFh, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ah, 0E8h, 0C2h, 4Ch, 78h, 00h, 83h, 0C4h
    db 04h, 0EBh, 0Ch, 0E8h, 0C8h, 12h, 73h, 00h, 83h, 0C4h, 04h, 0EBh, 02h, 33h, 0C0h, 8Dh
    db 0Ch, 0FFh, 89h, 06h, 89h, 46h, 04h, 8Dh, 14h, 88h, 5Fh, 8Bh, 0C6h, 5Eh, 89h, 13h
    db 5Bh, 0C2h, 08h, 00h
?d_000fd230@@YAXXZ ENDP

; ghidra: FUN_004fd390  retail @ 0x000FD390 size 65
public ?d_000fd390@@YAXXZ
?d_000fd390@@YAXXZ PROC
    db 56h, 8Bh, 31h, 85h, 0F6h, 74h, 38h, 8Bh, 49h, 08h, 2Bh, 0CEh, 0B8h, 39h, 8Eh, 0E3h
    db 38h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 0C0h
    db 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 56h, 0E8h, 0F0h, 4Ah, 78h, 00h
    db 83h, 0C4h, 04h, 5Eh, 0C3h, 50h, 56h, 0E8h, 24h, 12h, 73h, 00h, 83h, 0C4h, 08h, 5Eh
    db 0C3h
?d_000fd390@@YAXXZ ENDP

; ghidra: FUN_004fd650  retail @ 0x000FD650 size 88
public ?d_000fd650@@YAXXZ
?d_000fd650@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B1h, 0C4h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 8Bh, 44h, 24h, 14h, 89h, 04h, 24h, 85h, 0C0h, 0C7h
    db 44h, 24h, 0Ch, 00h, 00h, 00h, 00h, 74h, 20h, 8Bh, 4Ch, 24h, 18h, 8Bh, 11h, 89h
    db 10h, 8Bh, 51h, 04h, 89h, 50h, 04h, 8Bh, 51h, 08h, 83h, 0C1h, 0Ch, 51h, 8Dh, 48h
    db 0Ch, 89h, 50h, 08h, 0E8h, 0C7h, 0A4h, 78h, 00h, 8Bh, 4Ch, 24h, 04h, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000fd650@@YAXXZ ENDP

; ghidra: FUN_004fd8e0  retail @ 0x000FD8E0 size 45
public ?d_000fd8e0@@YAXXZ
?d_000fd8e0@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 3Bh, 0F3h, 57h, 8Bh, 7Ch, 24h
    db 18h, 74h, 14h, 56h, 57h, 0E8h, 8Fh, 0F7h, 0F1h, 0FFh, 83h, 0C6h, 24h, 83h, 0C4h, 08h
    db 83h, 0C7h, 24h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_000fd8e0@@YAXXZ ENDP

; ghidra: FUN_004fd920  retail @ 0x000FD920 size 45
public ?d_000fd920@@YAXXZ
?d_000fd920@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 0Ch, 56h, 8Bh, 74h, 24h, 0Ch, 3Bh, 0F3h, 57h, 8Bh, 7Ch, 24h
    db 18h, 74h, 14h, 56h, 57h, 0E8h, 32h, 1Fh, 0F1h, 0FFh, 83h, 0C6h, 10h, 83h, 0C4h, 08h
    db 83h, 0C7h, 10h, 3Bh, 0F3h, 75h, 0ECh, 8Bh, 0C7h, 5Fh, 5Eh, 5Bh, 0C3h
?d_000fd920@@YAXXZ ENDP

; ghidra: FUN_004fd960  retail @ 0x000FD960 size 97
public ?d_000fd960@@YAXXZ
?d_000fd960@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 26h, 8Dh, 04h, 0C0h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 0B2h, 45h, 78h, 00h, 83h, 0C4h
    db 04h, 8Bh, 0E8h, 0EBh, 0Eh, 0E8h, 0B6h, 0Bh, 73h, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh
    db 02h, 33h, 0EDh, 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h
    db 8Bh, 0FDh, 2Bh, 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 0DBh, 0F6h, 0F1h, 0FFh, 83h, 0C6h
    db 24h, 83h, 0C4h, 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch
    db 00h
?d_000fd960@@YAXXZ ENDP

; ghidra: FUN_004fd9e0  retail @ 0x000FD9E0 size 94
public ?d_000fd9e0@@YAXXZ
?d_000fd9e0@@YAXXZ PROC
    db 8Bh, 44h, 24h, 04h, 85h, 0C0h, 53h, 55h, 56h, 74h, 23h, 0C1h, 0E0h, 04h, 3Dh, 80h
    db 00h, 00h, 00h, 50h, 76h, 0Ch, 0E8h, 35h, 45h, 78h, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h
    db 0EBh, 0Eh, 0E8h, 39h, 0Bh, 73h, 00h, 83h, 0C4h, 04h, 8Bh, 0E8h, 0EBh, 02h, 33h, 0EDh
    db 8Bh, 74h, 24h, 14h, 8Bh, 5Ch, 24h, 18h, 3Bh, 0F3h, 74h, 1Ah, 57h, 8Bh, 0FDh, 2Bh
    db 0FEh, 8Dh, 04h, 37h, 56h, 50h, 0E8h, 41h, 1Eh, 0F1h, 0FFh, 83h, 0C6h, 10h, 83h, 0C4h
    db 08h, 3Bh, 0F3h, 75h, 0ECh, 5Fh, 5Eh, 8Bh, 0C5h, 5Dh, 5Bh, 0C2h, 0Ch, 00h
?d_000fd9e0@@YAXXZ ENDP

; ghidra: FUN_004fda80  retail @ 0x000FDA80 size 140
public ?d_000fda80@@YAXXZ
?d_000fda80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0E3h, 0C4h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 0E8h, 8Dh
    db 3Fh, 8Ah, 00h, 33h, 0FFh, 0C7h, 06h, 0D8h, 60h, 08h, 01h, 6Ah, 0Ch, 89h, 7Ch, 24h
    db 18h, 89h, 7Eh, 10h, 0E8h, 87h, 0Ah, 73h, 00h, 89h, 00h, 89h, 40h, 04h, 83h, 0C4h
    db 04h, 89h, 46h, 10h, 89h, 7Eh, 08h, 89h, 7Eh, 0Ch, 8Bh, 46h, 10h, 8Bh, 38h, 3Bh
    db 0F8h, 0C6h, 44h, 24h, 14h, 01h, 74h, 16h, 8Bh, 0C7h, 8Bh, 3Fh, 6Ah, 0Ch, 50h, 0E8h
    db 0Ch, 0Bh, 73h, 00h, 8Bh, 46h, 10h, 83h, 0C4h, 08h, 3Bh, 0F8h, 75h, 0EAh, 8Bh, 46h
    db 10h, 8Bh, 4Ch, 24h, 0Ch, 89h, 00h, 8Bh, 46h, 10h, 89h, 40h, 04h, 5Fh, 8Bh, 0C6h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000fda80@@YAXXZ ENDP

; ghidra: FUN_004fdb40  retail @ 0x000FDB40 size 139
public ?d_000fdb40@@YAXXZ
?d_000fdb40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 13h, 0C5h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 0D8h
    db 60h, 08h, 01h, 8Bh, 46h, 08h, 85h, 0C0h, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h
    db 74h, 2Dh, 8Bh, 48h, 0FCh, 57h, 8Dh, 78h, 0FCh, 68h, 4Ch, 36h, 41h, 00h, 51h, 6Ah
    db 0Ch, 50h, 0E8h, 0EFh, 91h, 8Fh, 00h, 57h, 0E8h, 63h, 43h, 78h, 00h, 83h, 0C4h, 04h
    db 0C7h, 46h, 08h, 00h, 00h, 00h, 00h, 0C7h, 46h, 0Ch, 00h, 00h, 00h, 00h, 5Fh, 8Dh
    db 4Eh, 10h, 0C6h, 44h, 24h, 10h, 00h, 0E8h, 0FEh, 7Bh, 0F4h, 0FFh, 8Bh, 0CEh, 0C7h, 44h
    db 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 85h, 3Eh, 8Ah, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000fdb40@@YAXXZ ENDP

; ghidra: FUN_004fdbf0  retail @ 0x000FDBF0 size 444
_TEXT ENDS
_TEXT$d004fdbf0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x004FDBF0 size 444
public ?d_000fdbf0@@YAXXZ
?d_000fdbf0@@YAXXZ PROC
    db 083h, 0ECh, 008h, 055h, 08Bh, 06Ch, 024h, 010h, 085h, 0EDh, 075h, 009h, 032h, 0C0h, 05Dh, 083h
    db 0C4h, 008h, 0C2h, 00Ch, 000h, 057h, 08Bh, 07Ch, 024h, 018h, 083h, 0C8h, 0FFh, 085h, 0FFh, 075h
    db 010h, 039h, 044h, 024h, 01Ch, 075h, 00Ah, 05Fh, 032h, 0C0h, 05Dh, 083h, 0C4h, 008h, 0C2h, 00Ch
    db 000h, 039h, 044h, 024h, 01Ch, 053h, 00Fh, 095h, 044h, 024h, 00Eh, 085h, 0FFh, 056h, 074h, 055h
    db 08Bh, 0B5h, 0F0h, 001h, 000h, 000h, 08Bh, 006h, 085h, 0C0h, 074h, 049h, 08Dh, 064h, 024h, 000h
    db 08Dh, 048h, 00Ch, 08Bh, 001h, 0FFh, 050h, 028h, 085h, 0C0h, 074h, 02Fh, 08Bh, 010h, 08Dh, 04Ch
    db 024h, 014h, 051h, 08Bh, 0C8h, 0FFh, 012h, 08Dh, 057h, 020h, 052h, 08Bh, 0C8h
    call ?j_000220c5@@YAXXZ
    db 08Bh, 0D8h, 0F7h, 0DBh, 01Ah, 0DBh, 08Dh, 04Ch, 024h, 014h, 0FEh, 0C3h
    call ?releaseBuffer@?$StringBase@D@@AAEXXZ
    db 084h, 0DBh, 00Fh, 085h, 025h, 001h, 000h, 000h, 08Bh, 046h, 004h, 083h, 0C6h, 004h, 085h, 0C0h
    db 075h, 0BBh, 08Bh, 0CDh
    call ?j_00029dc0@@YAXXZ
    db 08Bh, 00Dh
    dd ?TheControlBar@@3PAURva002AD380ControlBar@@A
    db 050h
    call ?j_00048cca@@YAXXZ
    db 08Bh, 0D8h, 085h, 0DBh, 00Fh, 084h, 0A0h, 000h, 000h, 000h, 033h, 0EDh, 033h, 0FFh, 057h, 08Bh
    db 0CBh
    call ?j_00003f80@@YAXXZ
    db 08Bh, 0F0h, 085h, 0F6h, 00Fh, 084h, 0BEh, 000h, 000h, 000h, 08Ah, 044h, 024h, 012h, 084h, 0C0h
    db 00Fh, 085h, 0A5h, 000h, 000h, 000h, 08Bh, 046h, 010h, 083h, 0F8h, 003h, 074h, 009h, 083h, 0F8h
    db 001h, 00Fh, 085h, 0A1h, 000h, 000h, 000h, 08Bh, 044h, 024h, 020h, 050h, 08Bh, 0CEh
    call ?j_000205cc@@YAXXZ
    db 08Bh, 0C8h
    call ?j_0003e80b@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 086h, 000h, 000h, 000h, 08Bh, 04Eh, 018h, 0C1h, 0E9h, 006h, 080h, 0E1h
    db 001h, 088h, 04Ch, 024h, 013h, 074h, 01Dh, 08Bh, 046h, 024h, 085h, 0C0h, 074h, 070h, 08Bh, 048h
    db 004h, 083h, 0F9h, 001h, 075h, 040h, 08Bh, 04Ch, 024h, 01Ch, 050h
    call ?j_0000ba37@@YAXXZ
    db 084h, 0C0h, 074h, 05Ah, 08Bh, 04Ch, 024h, 01Ch
    call ?j_00020824@@YAXXZ
    db 08Bh, 0F8h, 08Ah, 044h, 024h, 012h, 084h, 0C0h, 075h, 05Dh, 08Bh, 0CEh
    call ?j_000205cc@@YAXXZ
    db 050h, 08Bh, 0CFh
    call ?j_00007b4e@@YAXXZ
    db 084h, 0C0h, 075h, 05Eh, 05Eh, 05Bh, 05Fh, 032h, 0C0h, 05Dh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h
    db 085h, 0C9h, 075h, 024h, 08Bh, 04Ch, 024h, 01Ch, 050h
    call ?j_00020824@@YAXXZ
    db 08Bh, 0C8h
    call ?j_000235bf@@YAXXZ
    db 084h, 0C0h, 075h, 0B5h, 0EBh, 00Dh, 083h, 07Eh, 010h, 02Ch, 075h, 007h, 03Bh, 06Ch, 024h, 024h
    db 074h, 0A7h, 045h, 047h, 083h, 0FFh, 014h, 00Fh, 08Ch, 026h, 0FFh, 0FFh, 0FFh, 05Eh, 05Bh, 05Fh
    db 032h, 0C0h, 05Dh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h, 08Bh, 054h, 024h, 024h, 052h, 08Dh, 08Fh
    db 084h, 006h, 000h, 000h
    call ?j_0001f780@@YAXXZ
    db 084h, 0C0h, 074h, 0E0h, 05Eh, 05Bh, 05Fh, 0B0h, 001h, 05Dh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h
?d_000fdbf0@@YAXXZ ENDP
_TEXT$d004fdbf0 ENDS
_TEXT SEGMENT

; ghidra: FUN_004fde20  retail @ 0x000FDE20 size 45
public ?d_000fde20@@YAXXZ
?d_000fde20@@YAXXZ PROC
    db 56h, 8Bh, 31h, 6Ah, 0Ch, 0E8h, 16h, 07h, 73h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h
    db 85h, 0C9h, 74h, 08h, 8Bh, 54h, 24h, 08h, 8Bh, 12h, 89h, 11h, 8Bh, 4Eh, 04h, 89h
    db 30h, 89h, 48h, 04h, 89h, 01h, 89h, 46h, 04h, 5Eh, 0C2h, 04h, 00h
?d_000fde20@@YAXXZ ENDP

; ghidra: FUN_004fde60  retail @ 0x000FDE60 size 233
public ?d_000fde60@@YAXXZ
?d_000fde60@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 49h, 0C5h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 8Bh, 7Ch, 24h, 28h
    db 8Bh, 0F1h, 8Dh, 44h, 24h, 28h, 50h, 8Bh, 0CFh, 89h, 74h, 24h, 14h, 0E8h, 6Dh, 75h
    db 0F3h, 0FFh, 8Bh, 17h, 8Bh, 4Fh, 04h, 2Bh, 0CAh, 50h, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h
    db 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0CAh, 0C1h, 0E9h, 1Fh, 03h, 0CAh, 51h, 8Bh, 0CEh, 0E8h, 55h
    db 9Ch, 0F0h, 0FFh, 8Bh, 5Fh, 04h, 8Bh, 2Fh, 3Bh, 0EBh, 8Bh, 36h, 0C7h, 44h, 24h, 20h
    db 00h, 00h, 00h, 00h, 89h, 74h, 24h, 28h, 74h, 63h, 8Dh, 7Dh, 18h, 8Dh, 49h, 00h
    db 89h, 74h, 24h, 14h, 85h, 0F6h, 0C6h, 44h, 24h, 20h, 01h, 74h, 3Ah, 8Bh, 55h, 00h
    db 89h, 16h, 8Bh, 47h, 0ECh, 89h, 46h, 04h, 8Bh, 4Fh, 0F0h, 89h, 4Eh, 08h, 8Bh, 57h
    db 0F4h, 89h, 56h, 0Ch, 8Bh, 47h, 0F8h, 89h, 46h, 10h, 8Bh, 4Fh, 0FCh, 89h, 4Eh, 14h
    db 8Bh, 17h, 8Dh, 47h, 04h, 8Dh, 4Eh, 1Ch, 50h, 89h, 56h, 18h, 0E8h, 4Fh, 9Ch, 78h
    db 00h, 8Ah, 4Fh, 08h, 88h, 4Eh, 20h, 83h, 0C5h, 24h, 83h, 0C6h, 24h, 83h, 0C7h, 24h
    db 3Bh, 0EBh, 0C6h, 44h, 24h, 20h, 00h, 89h, 74h, 24h, 28h, 75h, 0A3h, 8Bh, 44h, 24h
    db 10h, 8Bh, 4Ch, 24h, 18h, 5Fh, 89h, 70h, 04h, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?d_000fde60@@YAXXZ ENDP

; ghidra: FUN_004fe3c0  retail @ 0x000FE3C0 size 411
_TEXT ENDS
_TEXT$d004fe3c0 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x004FE3C0 size 411
public ?d_000fe3c0@@YAXXZ
?d_000fe3c0@@YAXXZ PROC
    db 083h, 0ECh, 008h, 056h, 08Bh, 074h, 024h, 010h, 085h, 0F6h, 075h, 00Ch, 0B8h, 001h, 000h, 000h
    db 000h, 05Eh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h, 08Bh, 054h, 024h, 014h, 085h, 0D2h, 057h, 08Bh
    db 07Ch, 024h, 01Ch, 075h, 012h, 083h, 0FFh, 0FFh, 075h, 00Dh, 05Fh, 0B8h, 001h, 000h, 000h, 000h
    db 05Eh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h, 08Ah, 086h, 043h, 003h, 000h, 000h, 083h, 0FFh, 0FFh
    db 053h, 00Fh, 095h, 0C3h, 0A8h, 003h, 00Fh, 085h, 041h, 001h, 000h, 000h, 08Bh, 001h, 057h, 052h
    db 056h, 0FFh, 050h, 044h, 084h, 0C0h, 075h, 00Eh, 05Bh, 05Fh, 0B8h, 001h, 000h, 000h, 000h, 05Eh
    db 083h, 0C4h, 008h, 0C2h, 00Ch, 000h, 08Bh, 0CEh
    call ?j_00003b52@@YAXXZ
    db 085h, 0C0h, 074h, 00Eh, 08Bh, 010h, 08Bh, 0C8h, 0FFh, 012h, 085h, 0C0h, 00Fh, 085h, 013h, 001h
    db 000h, 000h, 08Bh, 0CEh
    call ?j_00020824@@YAXXZ
    db 084h, 0DBh, 08Bh, 0F0h, 074h, 04Ah, 055h, 08Bh, 06Eh, 04Ch, 08Dh, 09Eh, 084h, 006h, 000h, 000h
    db 057h, 08Bh, 0CBh
    call ?j_000237d1@@YAXXZ
    db 03Bh, 0C5h, 05Dh, 076h, 00Eh, 05Bh, 05Fh, 0B8h, 002h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 008h
    db 0C2h, 00Ch, 000h, 06Ah, 001h, 057h, 08Bh, 0CBh
    call ?j_00002135@@YAXXZ
    db 050h, 08Dh, 04Eh, 030h
    call ?j_00022336@@YAXXZ
    db 084h, 0C0h, 075h, 03Ch, 05Bh, 05Fh, 0B8h, 007h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 008h, 0C2h
    db 00Ch, 000h, 08Bh, 07Ch, 024h, 01Ch, 068h, 09Ch, 000h, 000h, 000h, 08Bh, 0CFh
    call ?j_000032d8@@YAXXZ
    db 084h, 0C0h, 075h, 015h, 08Bh, 05Eh, 04Ch, 06Ah, 0FFh, 056h, 08Bh, 0CFh
    call ?j_0000da8a@@YAXXZ
    db 03Bh, 0C3h, 077h, 0A8h, 08Bh, 07Ch, 024h, 01Ch, 06Ah, 001h, 057h, 0EBh, 0B8h, 08Bh, 044h, 024h
    db 01Ch, 085h, 0C0h, 074h, 076h, 066h, 083h, 0B8h, 080h, 004h, 000h, 000h, 000h, 074h, 06Ch, 06Ah
    db 000h, 08Dh, 044h, 024h, 01Ch, 050h, 06Ah, 001h, 08Dh, 04Ch, 024h, 028h, 051h, 06Ah, 001h, 08Bh
    db 0CEh
    call ?j_00048d79@@YAXXZ
    db 08Bh, 044h, 024h, 01Ch, 00Fh, 0B7h, 090h, 080h, 004h, 000h, 000h, 039h, 054h, 024h, 018h, 072h
    db 00Eh, 05Bh, 05Fh, 0B8h, 006h, 000h, 000h, 000h, 05Eh, 083h, 0C4h, 008h, 0C2h, 00Ch, 000h, 089h
    db 044h, 024h, 010h, 08Dh, 044h, 024h, 00Ch, 050h, 068h
    dd ?rva000fc2a0Tally@@YAHPAUBfmeThingEJ@@PAURva000FC2A0Tally@@@Z
    db 08Bh, 0CEh, 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h
    call ?iterateObjects@Player@@QBEXP6AXPAVObject@@PAX@Z1@Z
    db 08Bh, 04Ch, 024h, 01Ch, 00Fh, 0B7h, 091h, 080h, 004h, 000h, 000h, 08Bh, 044h, 024h, 018h, 08Bh
    db 04Ch, 024h, 00Ch, 003h, 0C8h, 03Bh, 0CAh, 073h, 0BCh, 05Bh, 05Fh, 033h, 0C0h, 05Eh, 083h, 0C4h
    db 008h, 0C2h, 00Ch, 000h, 0B8h, 003h, 000h, 000h, 000h, 05Bh, 05Fh, 05Eh, 083h, 0C4h, 008h, 0C2h
    db 00Ch, 000h
?d_000fe3c0@@YAXXZ ENDP
_TEXT$d004fe3c0 ENDS
_TEXT SEGMENT

; ghidra: FUN_004fe5d0  retail @ 0x000FE5D0 size 90
public ?d_000fe5d0@@YAXXZ
?d_000fe5d0@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 85h, 0F6h, 75h, 06h, 32h, 0C0h, 5Eh, 0C2h, 04h, 00h, 8Bh
    db 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0C9h, 3Ch
    db 0F0h, 0FFh, 0F7h, 80h, 0D0h, 00h, 00h, 00h, 00h, 00h, 00h, 01h, 75h, 0DBh, 6Ah, 06h
    db 8Bh, 0CEh, 0E8h, 18h, 3Fh, 0F3h, 0FFh, 84h, 0C0h, 74h, 06h, 0B0h, 01h, 5Eh, 0C2h, 04h
    db 00h, 6Ah, 32h, 8Bh, 0CEh, 0E8h, 05h, 3Fh, 0F3h, 0FFh, 84h, 0C0h, 75h, 0EDh, 8Ah, 86h
    db 44h, 03h, 00h, 00h, 24h, 01h, 5Eh, 0C2h, 04h, 00h
?d_000fe5d0@@YAXXZ ENDP

; ghidra: FUN_004fe640  retail @ 0x000FE640 size 695
public ?d_000fe640@@YAXXZ
?d_000fe640@@YAXXZ PROC
    db 83h, 0ECh, 34h, 53h, 56h, 8Bh, 74h, 24h, 40h, 8Bh, 46h, 04h, 85h, 0C0h, 8Bh, 0D9h
    db 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 5Dh, 3Ch, 0F0h, 0FFh, 0F7h, 80h
    db 0D0h, 00h, 00h, 00h, 00h, 00h, 00h, 01h, 0Fh, 85h, 7Fh, 02h, 00h, 00h, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 3Ah, 3Ch, 0F0h
    db 0FFh, 0F6h, 80h, 0D8h, 00h, 00h, 00h, 20h, 0Fh, 85h, 5Fh, 02h, 00h, 00h, 6Ah, 67h
    db 8Bh, 0CEh, 0E8h, 88h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 4Eh, 02h, 00h, 00h, 6Ah
    db 3Bh, 8Bh, 0CEh, 0E8h, 77h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 3Dh, 02h, 00h, 00h
    db 6Ah, 02h, 8Bh, 0CEh, 0E8h, 66h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 2Ch, 02h, 00h
    db 00h, 6Ah, 39h, 8Bh, 0CEh, 0E8h, 55h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 1Bh, 02h
    db 00h, 00h, 6Ah, 06h, 8Bh, 0CEh, 0E8h, 44h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0Ah
    db 02h, 00h, 00h, 6Ah, 32h, 8Bh, 0CEh, 0E8h, 33h, 3Eh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h
    db 0F9h, 01h, 00h, 00h, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 0ECh, 01h, 00h
    db 00h, 57h, 8Bh, 0BEh, 04h, 02h, 00h, 00h, 85h, 0FFh, 0Fh, 84h, 0D2h, 01h, 00h, 00h
    db 8Bh, 87h, 40h, 01h, 00h, 00h, 85h, 0C0h, 0Fh, 84h, 0C4h, 01h, 00h, 00h, 8Bh, 0CEh
    db 0E8h, 52h, 0D7h, 0F2h, 0FFh, 85h, 0C0h, 74h, 12h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 92h, 0A0h
    db 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 0A7h, 01h, 00h, 00h, 8Bh, 46h, 38h, 8Bh, 4Eh
    db 3Ch, 8Bh, 56h, 40h, 89h, 44h, 24h, 1Ch, 8Bh, 87h, 40h, 01h, 00h, 00h, 8Bh, 40h
    db 08h, 89h, 4Ch, 24h, 20h, 8Bh, 48h, 0Ch, 83h, 0C0h, 0Ch, 89h, 54h, 24h, 24h, 8Bh
    db 50h, 04h, 8Bh, 40h, 08h, 89h, 44h, 24h, 3Ch, 8Bh, 43h, 08h, 0D9h, 00h, 89h, 4Ch
    db 24h, 34h, 0D9h, 40h, 04h, 8Bh, 48h, 08h, 0D9h, 0C9h, 89h, 4Ch, 24h, 18h, 0D8h, 64h
    db 24h, 1Ch, 89h, 54h, 24h, 38h, 8Dh, 4Ch, 24h, 28h, 0D9h, 5Ch, 24h, 10h, 0D8h, 64h
    db 24h, 20h, 0D9h, 5Ch, 24h, 14h, 0D9h, 44h, 24h, 18h, 0D8h, 64h, 24h, 24h, 0D9h, 5Ch
    db 24h, 18h, 0D9h, 44h, 24h, 34h, 0D8h, 64h, 24h, 1Ch, 0D9h, 5Ch, 24h, 28h, 0D9h, 44h
    db 24h, 38h, 0D8h, 64h, 24h, 20h, 0D9h, 5Ch, 24h, 2Ch, 0D9h, 44h, 24h, 3Ch, 0D8h, 64h
    db 24h, 24h, 0D9h, 5Ch, 24h, 30h, 0E8h, 49h, 07h, 0F3h, 0FFh, 8Dh, 4Ch, 24h, 28h, 0D9h
    db 5Ch, 24h, 0Ch, 0E8h, 0E2h, 0F8h, 0F1h, 0FFh, 0DDh, 0D8h, 0D9h, 44h, 24h, 30h, 0D8h, 4Ch
    db 24h, 18h, 0D9h, 44h, 24h, 2Ch, 0D8h, 4Ch, 24h, 14h, 0DEh, 0C1h, 0D9h, 44h, 24h, 28h
    db 0D8h, 4Ch, 24h, 10h, 0DEh, 0C1h, 0D9h, 54h, 24h, 44h, 0D8h, 1Dh, 50h, 53h, 07h, 01h
    db 0DFh, 0E0h, 0F6h, 0C4h, 05h, 7Ah, 1Ah, 8Bh, 54h, 24h, 1Ch, 8Bh, 44h, 24h, 20h, 8Bh
    db 4Ch, 24h, 24h, 89h, 54h, 24h, 10h, 89h, 44h, 24h, 14h, 89h, 4Ch, 24h, 18h, 0EBh
    db 7Bh, 0D9h, 44h, 24h, 44h, 0D8h, 5Ch, 24h, 0Ch, 0DFh, 0E0h, 0F6h, 0C4h, 41h, 75h, 1Ah
    db 8Bh, 54h, 24h, 34h, 8Bh, 44h, 24h, 38h, 8Bh, 4Ch, 24h, 3Ch, 89h, 54h, 24h, 10h
    db 89h, 44h, 24h, 14h, 89h, 4Ch, 24h, 18h, 0EBh, 52h, 8Bh, 54h, 24h, 28h, 8Bh, 44h
    db 24h, 2Ch, 8Bh, 4Ch, 24h, 30h, 89h, 54h, 24h, 10h, 0D9h, 44h, 24h, 10h, 0D8h, 4Ch
    db 24h, 44h, 89h, 44h, 24h, 14h, 0D9h, 44h, 24h, 14h, 89h, 4Ch, 24h, 18h, 0D8h, 4Ch
    db 24h, 44h, 0D9h, 44h, 24h, 18h, 0D8h, 4Ch, 24h, 44h, 0D9h, 5Ch, 24h, 18h, 0D9h, 0C9h
    db 0D8h, 44h, 24h, 1Ch, 0D9h, 5Ch, 24h, 10h, 0D8h, 44h, 24h, 20h, 0D9h, 5Ch, 24h, 14h
    db 0D9h, 44h, 24h, 18h, 0D8h, 44h, 24h, 24h, 0D9h, 5Ch, 24h, 18h, 8Bh, 43h, 08h, 0D9h
    db 44h, 24h, 10h, 0D8h, 20h, 0D9h, 44h, 24h, 14h, 0D8h, 60h, 04h, 0D9h, 44h, 24h, 18h
    db 0D8h, 60h, 08h, 0D9h, 43h, 0Ch, 0D9h, 0C1h, 0D8h, 0CAh, 0D9h, 0C3h, 0D8h, 0CCh, 0DEh, 0C1h
    db 0D9h, 0C4h, 0D8h, 0CDh, 0DEh, 0C1h, 0D9h, 0C1h, 0D8h, 0CAh, 0DEh, 0D9h, 0DDh, 0D8h, 0DDh, 0D8h
    db 0DFh, 0E0h, 0DDh, 0D8h, 0F6h, 0C4h, 05h, 0DDh, 0D8h, 7Bh, 07h, 8Bh, 0CFh, 0E8h, 0FFh, 7Ch
    db 0F0h, 0FFh, 5Fh, 5Eh, 32h, 0C0h, 5Bh, 83h, 0C4h, 34h, 0C2h, 04h, 00h, 5Eh, 32h, 0C0h
    db 5Bh, 83h, 0C4h, 34h, 0C2h, 04h, 00h
?d_000fe640@@YAXXZ ENDP

; ghidra: FUN_004fea90  retail @ 0x000FEA90 size 33
public ?d_000fea90@@YAXXZ
?d_000fea90@@YAXXZ PROC
    db 56h, 8Bh, 74h, 24h, 08h, 57h, 8Bh, 7Ch, 24h, 10h, 3Bh, 0F7h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 12h, 28h, 0F3h, 0FFh, 83h, 0C6h, 24h, 3Bh, 0F7h, 75h, 0F2h, 5Fh, 5Eh
    db 0C3h
?d_000fea90@@YAXXZ ENDP

; ghidra: FUN_004feaf0  retail @ 0x000FEAF0 size 98
public ?d_000feaf0@@YAXXZ
?d_000feaf0@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 0F9h, 8Bh, 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 74h, 10h, 8Bh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0B2h, 27h, 0F3h, 0FFh, 83h, 0C6h, 24h, 3Bh, 0F3h, 75h, 0F2h, 8Bh, 37h
    db 85h, 0F6h, 74h, 3Ah, 8Bh, 4Fh, 08h, 2Bh, 0CEh, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0E9h
    db 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 0C0h, 0C1h, 0E0h, 02h
    db 3Dh, 80h, 00h, 00h, 00h, 76h, 0Dh, 56h, 0E8h, 73h, 33h, 78h, 00h, 83h, 0C4h, 04h
    db 5Fh, 5Eh, 5Bh, 0C3h, 50h, 56h, 0E8h, 0A5h, 0FAh, 72h, 00h, 83h, 0C4h, 08h, 5Fh, 5Eh
    db 5Bh, 0C3h
?d_000feaf0@@YAXXZ ENDP

; ghidra: FUN_004febe0  retail @ 0x000FEBE0 size 748
public ?d_000febe0@@YAXXZ
?d_000febe0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 98h, 0C5h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 24h, 8Bh, 41h, 10h, 53h, 55h, 89h, 4Ch, 24h
    db 18h, 8Bh, 08h, 3Bh, 0C8h, 56h, 57h, 0Fh, 84h, 0ACh, 02h, 00h, 00h, 33h, 0DBh, 0EBh
    db 04h, 8Bh, 4Ch, 24h, 1Ch, 8Bh, 41h, 08h, 8Bh, 70h, 04h, 3Bh, 0F3h, 8Bh, 0F9h, 8Bh
    db 09h, 89h, 44h, 24h, 14h, 89h, 7Ch, 24h, 18h, 89h, 4Ch, 24h, 1Ch, 74h, 5Ch, 8Bh
    db 0Dh, 98h, 08h, 2Fh, 01h, 8Bh, 81h, 0B4h, 00h, 00h, 00h, 8Bh, 0A9h, 0B8h, 00h, 00h
    db 00h, 2Bh, 0E8h, 0C1h, 0FDh, 02h, 33h, 0D2h, 8Bh, 0C6h, 0F7h, 0F5h, 8Bh, 89h, 0B4h, 00h
    db 00h, 00h, 8Bh, 04h, 91h, 3Bh, 0C3h, 74h, 2Eh, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 39h, 70h, 04h, 74h, 17h, 8Bh, 00h, 3Bh, 0C3h, 75h, 0F5h, 8Bh, 44h, 24h, 14h, 8Bh
    db 10h, 6Ah, 01h, 8Bh, 0C8h, 0FFh, 12h, 0E9h, 15h, 02h, 00h, 00h, 3Bh, 0C3h, 74h, 07h
    db 8Bh, 70h, 08h, 3Bh, 0F3h, 75h, 11h, 8Bh, 44h, 24h, 14h, 8Bh, 10h, 6Ah, 01h, 8Bh
    db 0C8h, 0FFh, 12h, 0E9h, 0F9h, 01h, 00h, 00h, 8Bh, 0CEh, 0E8h, 85h, 1Bh, 0F2h, 0FFh, 8Bh
    db 0E8h, 3Bh, 0EBh, 0Fh, 84h, 33h, 01h, 00h, 00h, 8Bh, 46h, 04h, 3Bh, 0C3h, 75h, 04h
    db 33h, 0C0h, 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CBh, 74h, 05h, 0E8h, 0FBh, 35h, 0F0h, 0FFh
    db 66h, 39h, 98h, 7Ch, 04h, 00h, 00h, 74h, 27h, 8Bh, 46h, 04h, 3Bh, 0C3h, 75h, 0Bh
    db 33h, 0C0h, 0Fh, 0B7h, 0B8h, 7Ch, 04h, 00h, 00h, 0EBh, 2Dh, 8Bh, 48h, 04h, 3Bh, 0CBh
    db 74h, 05h, 0E8h, 0D4h, 35h, 0F0h, 0FFh, 0Fh, 0B7h, 0B8h, 7Ch, 04h, 00h, 00h, 0EBh, 18h
    db 0A1h, 0C8h, 0D5h, 2Eh, 01h, 0D9h, 86h, 58h, 02h, 00h, 00h, 0D8h, 88h, 30h, 0Ch, 00h
    db 00h, 0E8h, 32h, 81h, 8Fh, 00h, 8Bh, 0F8h, 8Bh, 8Eh, 00h, 02h, 00h, 00h, 0D9h, 05h
    db 34h, 53h, 07h, 01h, 3Bh, 0CBh, 74h, 07h, 8Bh, 11h, 0DDh, 0D8h, 0FFh, 52h, 14h, 85h
    db 0FFh, 89h, 7Ch, 24h, 24h, 0DBh, 44h, 24h, 24h, 6Ah, 01h, 7Dh, 06h, 0D8h, 05h, 58h
    db 53h, 07h, 01h, 0D8h, 0C9h, 0E8h, 0FEh, 80h, 8Fh, 00h, 0DDh, 0D8h, 50h, 8Dh, 4Dh, 48h
    db 0E8h, 28h, 90h, 0F2h, 0FFh, 89h, 5Ch, 24h, 10h, 8Bh, 0Dh, 7Ch, 14h, 2Fh, 01h, 8Bh
    db 01h, 57h, 51h, 8Bh, 0D4h, 89h, 64h, 24h, 2Ch, 53h, 68h, 14h, 40h, 08h, 01h, 52h
    db 89h, 5Ch, 24h, 50h, 0FFh, 50h, 28h, 8Dh, 44h, 24h, 18h, 50h, 0E8h, 1Fh, 0A4h, 78h
    db 00h, 8Bh, 4Eh, 38h, 8Bh, 56h, 3Ch, 8Bh, 46h, 40h, 89h, 4Ch, 24h, 34h, 83h, 0C4h
    db 0Ch, 8Dh, 8Eh, 0ACh, 00h, 00h, 00h, 89h, 54h, 24h, 2Ch, 89h, 44h, 24h, 30h, 0E8h
    db 6Ch, 0F2h, 77h, 00h, 0D8h, 44h, 24h, 30h, 8Bh, 0CEh, 0D9h, 5Ch, 24h, 30h, 0E8h, 81h
    db 1Ah, 0F2h, 0FFh, 8Bh, 80h, 0C4h, 01h, 00h, 00h, 8Bh, 0Dh, 8Ch, 14h, 2Fh, 01h, 8Bh
    db 11h, 0Dh, 00h, 00h, 00h, 0E6h, 50h, 8Dh, 44h, 24h, 2Ch, 50h, 8Dh, 44h, 24h, 18h
    db 50h, 0FFh, 92h, 78h, 01h, 00h, 00h, 8Dh, 4Ch, 24h, 10h, 0C7h, 44h, 24h, 3Ch, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0F8h, 93h, 78h, 00h, 8Bh, 7Ch, 24h, 18h, 8Bh, 0CEh, 0E8h, 6Fh
    db 4Dh, 0F0h, 0FFh, 3Bh, 0C3h, 74h, 07h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 34h, 8Bh, 46h
    db 04h, 3Bh, 0C3h, 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CBh, 74h, 05h
    db 0E8h, 0B6h, 34h, 0F0h, 0FFh, 8Ah, 88h, 0C8h, 00h, 00h, 00h, 84h, 0C9h, 79h, 44h, 8Bh
    db 8Eh, 00h, 02h, 00h, 00h, 8Bh, 01h, 0FFh, 50h, 20h, 83h, 0F8h, 01h, 7Eh, 34h, 6Ah
    db 04h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Bh, 0CEh, 89h, 5Ch, 24h, 20h, 0E8h, 0A1h, 14h, 0F4h
    db 0FFh, 84h, 0C0h, 74h, 1Eh, 8Bh, 54h, 24h, 18h, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 52h
    db 0E8h, 0Eh, 04h, 0F2h, 0FFh, 3Bh, 0C3h, 74h, 0Ah, 6Ah, 01h, 56h, 8Bh, 0C8h, 0E8h, 0F8h
    db 0CAh, 0F1h, 0FFh, 8Bh, 46h, 04h, 3Bh, 0C3h, 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh, 48h
    db 04h, 3Bh, 0CBh, 74h, 05h, 0E8h, 51h, 34h, 0F0h, 0FFh, 0F7h, 80h, 0D8h, 00h, 00h, 00h
    db 00h, 00h, 20h, 00h, 8Bh, 0CEh, 74h, 07h, 0E8h, 03h, 3Ch, 0F1h, 0FFh, 0EBh, 08h, 53h
    db 6Ah, 08h, 0E8h, 7Fh, 56h, 0F1h, 0FFh, 8Bh, 4Ch, 24h, 14h, 8Bh, 01h, 6Ah, 01h, 0FFh
    db 10h, 8Bh, 07h, 8Bh, 4Fh, 04h, 6Ah, 0Ch, 89h, 01h, 57h, 89h, 48h, 04h, 0E8h, 4Dh
    db 0F7h, 72h, 00h, 8Bh, 54h, 24h, 28h, 8Bh, 4Ch, 24h, 24h, 8Bh, 42h, 10h, 83h, 0C4h
    db 08h, 3Bh, 0C8h, 0Fh, 85h, 58h, 0FDh, 0FFh, 0FFh, 8Bh, 4Ch, 24h, 34h, 5Fh, 5Eh, 5Dh
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 5Bh, 83h, 0C4h, 30h, 0C3h
?d_000febe0@@YAXXZ ENDP

; ghidra: FUN_004ff4d0  retail @ 0x000FF4D0 size 438
public ?d_000ff4d0@@YAXXZ
?d_000ff4d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 00h, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 20h, 8Bh, 44h, 24h, 34h, 8Bh, 08h, 8Bh, 50h
    db 04h, 89h, 4Ch, 24h, 08h, 8Bh, 48h, 08h, 89h, 4Ch, 24h, 10h, 8Bh, 4Ch, 24h, 30h
    db 89h, 54h, 24h, 0Ch, 8Dh, 51h, 60h, 89h, 54h, 24h, 14h, 8Bh, 54h, 24h, 38h, 0C7h
    db 44h, 24h, 04h, 00h, 00h, 00h, 00h, 0C7h, 04h, 24h, 0A0h, 60h, 08h, 01h, 89h, 54h
    db 24h, 18h, 0C6h, 44h, 24h, 1Ch, 01h, 0D9h, 41h, 74h, 0D8h, 0Dh, 34h, 61h, 08h, 01h
    db 6Ah, 00h, 8Dh, 4Ch, 24h, 04h, 51h, 6Ah, 03h, 51h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h
    db 0D9h, 1Ch, 24h, 50h, 8Dh, 54h, 24h, 48h, 52h, 0C7h, 44h, 24h, 40h, 00h, 00h, 00h
    db 00h, 0E8h, 0Ah, 34h, 8Fh, 00h, 0C6h, 44h, 24h, 28h, 02h, 0C7h, 04h, 24h, 5Ch, 3Bh
    db 08h, 01h, 56h, 8Bh, 44h, 24h, 38h, 8Bh, 48h, 04h, 8Bh, 50h, 0Ch, 3Bh, 0D1h, 0Fh
    db 84h, 0B1h, 00h, 00h, 00h, 8Bh, 0CAh, 8Bh, 31h, 83h, 0C1h, 08h, 85h, 0F6h, 89h, 48h
    db 0Ch, 0Fh, 84h, 9Bh, 00h, 00h, 00h, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h
    db 04h, 85h, 0C9h, 74h, 05h, 0E8h, 21h, 2Dh, 0F0h, 0FFh, 0F7h, 80h, 0D0h, 00h, 00h, 00h
    db 00h, 00h, 00h, 01h, 75h, 0BDh, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h
    db 85h, 0C9h, 74h, 05h, 0E8h, 02h, 2Dh, 0F0h, 0FFh, 0F6h, 80h, 0C8h, 00h, 00h, 00h, 40h
    db 75h, 2Ch, 8Bh, 46h, 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h
    db 0E8h, 0E6h, 2Ch, 0F0h, 0FFh, 0F7h, 80h, 0CCh, 00h, 00h, 00h, 00h, 00h, 04h, 00h, 75h
    db 0Dh, 0F6h, 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 84h, 75h, 0FFh, 0FFh, 0FFh, 8Bh, 46h
    db 04h, 85h, 0C0h, 74h, 0Ch, 8Bh, 48h, 04h, 85h, 0C9h, 74h, 05h, 0E8h, 0BAh, 2Ch, 0F0h
    db 0FFh, 0F7h, 80h, 0CCh, 00h, 00h, 00h, 00h, 00h, 00h, 02h, 0Fh, 85h, 52h, 0FFh, 0FFh
    db 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 56h, 0E8h, 0C1h, 0DAh, 0F1h, 0FFh, 0E9h, 41h, 0FFh
    db 0FFh, 0FFh, 8Bh, 44h, 24h, 38h, 0FFh, 48h, 10h, 8Bh, 44h, 24h, 38h, 8Bh, 48h, 10h
    db 85h, 0C9h, 0C7h, 44h, 24h, 2Ch, 0FFh, 0FFh, 0FFh, 0FFh, 75h, 38h, 8Bh, 08h, 85h, 0C9h
    db 8Bh, 0F0h, 74h, 27h, 8Bh, 40h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh
    db 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 54h, 28h, 78h, 00h, 83h, 0C4h, 04h, 0EBh
    db 0Ah, 50h, 51h, 0E8h, 88h, 0EFh, 72h, 00h, 83h, 0C4h, 08h, 56h, 0E8h, 3Fh, 28h, 78h
    db 00h, 83h, 0C4h, 04h, 8Bh, 4Ch, 24h, 24h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 83h, 0C4h, 2Ch, 0C2h, 0Ch, 00h
?d_000ff4d0@@YAXXZ ENDP

; ghidra: FUN_004ff700  retail @ 0x000FF700 size 167
public ?d_000ff700@@YAXXZ
?d_000ff700@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 18h, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 0Fh
    db 8Dh, 4Eh, 1Ch, 0E8h, 08h, 82h, 78h, 00h, 83h, 0C6h, 24h, 3Bh, 0F3h, 75h, 0F1h, 8Bh
    db 37h, 85h, 0F6h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 48h, 8Bh, 4Fh, 08h
    db 2Bh, 0CEh, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0E9h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h
    db 1Fh, 03h, 0C2h, 8Dh, 04h, 0C0h, 0C1h, 0E0h, 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Bh
    db 56h, 0E8h, 3Ah, 27h, 78h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 04h
    db 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h, 56h, 0E8h, 5Eh, 0EEh
    db 72h, 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h
    db 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000ff700@@YAXXZ ENDP

; ghidra: FUN_004ff7d0  retail @ 0x000FF7D0 size 150
public ?d_000ff7d0@@YAXXZ
?d_000ff7d0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 38h, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 0Ch, 8Bh
    db 5Fh, 04h, 8Bh, 37h, 3Bh, 0F3h, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h, 74h, 0Fh
    db 8Dh, 4Eh, 0Ch, 0E8h, 38h, 81h, 78h, 00h, 83h, 0C6h, 10h, 3Bh, 0F3h, 75h, 0F1h, 8Bh
    db 0Fh, 85h, 0C9h, 0C7h, 44h, 24h, 18h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 37h, 8Bh, 47h, 08h
    db 2Bh, 0C1h, 0C1h, 0F8h, 04h, 0C1h, 0E0h, 04h, 3Dh, 80h, 00h, 00h, 00h, 76h, 1Bh, 51h
    db 0E8h, 7Bh, 26h, 78h, 00h, 83h, 0C4h, 04h, 5Fh, 5Eh, 5Bh, 8Bh, 4Ch, 24h, 04h, 64h
    db 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h, 50h, 51h, 0E8h, 9Fh, 0EDh, 72h
    db 00h, 83h, 0C4h, 08h, 8Bh, 4Ch, 24h, 10h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000ff7d0@@YAXXZ ENDP

; ghidra: FUN_004ff8f0  retail @ 0x000FF8F0 size 294
public ?d_000ff8f0@@YAXXZ
?d_000ff8f0@@YAXXZ PROC
    db 55h, 8Bh, 6Ch, 24h, 08h, 56h, 8Bh, 0F1h, 3Bh, 0EEh, 0Fh, 84h, 0Fh, 01h, 00h, 00h
    db 8Bh, 55h, 04h, 8Bh, 4Dh, 00h, 89h, 54h, 24h, 0Ch, 2Bh, 0D1h, 0B8h, 39h, 8Eh, 0E3h
    db 38h, 0F7h, 0EAh, 0C1h, 0FAh, 03h, 53h, 8Bh, 1Eh, 57h, 8Bh, 0FAh, 0C1h, 0EFh, 1Fh, 03h
    db 0FAh, 8Bh, 56h, 08h, 2Bh, 0D3h, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0EAh, 0C1h, 0FAh, 03h
    db 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 3Bh, 0F8h, 76h, 36h, 8Bh, 54h, 24h, 14h, 52h
    db 51h, 57h, 8Bh, 0CEh, 0E8h, 1Bh, 8Bh, 0F4h, 0FFh, 8Bh, 0CEh, 8Bh, 0D8h, 0E8h, 0B4h, 50h
    db 0F1h, 0FFh, 8Dh, 04h, 0FFh, 8Dh, 0Ch, 83h, 89h, 4Eh, 08h, 8Dh, 04h, 0FFh, 8Bh, 0CBh
    db 5Fh, 89h, 1Eh, 8Dh, 14h, 81h, 5Bh, 89h, 56h, 04h, 8Bh, 0C6h, 5Eh, 5Dh, 0C2h, 04h
    db 00h, 8Bh, 56h, 04h, 2Bh, 0D3h, 0B8h, 39h, 8Eh, 0E3h, 38h, 0F7h, 0EAh, 0C1h, 0FAh, 03h
    db 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 3Bh, 0C7h, 6Ah, 00h, 8Dh, 54h, 24h, 18h, 52h
    db 53h, 72h, 2Ch, 8Bh, 44h, 24h, 20h, 50h, 51h, 0E8h, 42h, 88h, 0F3h, 0FFh, 8Bh, 4Eh
    db 04h, 51h, 50h, 0E8h, 49h, 81h, 0F3h, 0FFh, 8Bh, 0Eh, 83h, 0C4h, 1Ch, 8Dh, 04h, 0FFh
    db 5Fh, 8Dh, 14h, 81h, 5Bh, 89h, 56h, 04h, 8Bh, 0C6h, 5Eh, 5Dh, 0C2h, 04h, 00h, 8Dh
    db 04h, 0C0h, 8Dh, 14h, 81h, 52h, 51h, 0E8h, 14h, 88h, 0F3h, 0FFh, 8Bh, 46h, 04h, 8Bh
    db 55h, 04h, 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0Eh, 50h, 2Bh, 0C1h, 8Bh, 0C8h, 52h, 0B8h
    db 39h, 8Eh, 0E3h, 38h, 0F7h, 0E9h, 8Bh, 4Dh, 00h, 0C1h, 0FAh, 03h, 8Bh, 0C2h, 0C1h, 0E8h
    db 1Fh, 03h, 0C2h, 8Dh, 04h, 0C0h, 8Dh, 14h, 81h, 52h, 0E8h, 6Ah, 0D2h, 0F2h, 0FFh, 8Bh
    db 0Eh, 83h, 0C4h, 24h, 8Dh, 04h, 0FFh, 8Dh, 14h, 81h, 5Fh, 89h, 56h, 04h, 5Bh, 8Bh
    db 0C6h, 5Eh, 5Dh, 0C2h, 04h, 00h
?d_000ff8f0@@YAXXZ ENDP

; ghidra: FUN_004ffb80  retail @ 0x000FFB80 size 219
public ?d_000ffb80@@YAXXZ
?d_000ffb80@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Bh, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 9Ch, 00h, 00h, 00h, 8Bh, 84h, 24h, 0B0h, 00h
    db 00h, 00h, 56h, 50h, 8Bh, 0F1h, 6Ah, 36h, 8Dh, 4Ch, 24h, 0Ch, 0E8h, 0F3h, 12h, 0F3h
    db 0FFh, 8Bh, 8Ch, 24h, 0B0h, 00h, 00h, 00h, 8Bh, 11h, 8Bh, 41h, 04h, 8Bh, 49h, 08h
    db 89h, 44h, 24h, 10h, 8Dh, 44h, 24h, 04h, 89h, 54h, 24h, 0Ch, 8Bh, 16h, 89h, 4Ch
    db 24h, 14h, 50h, 8Bh, 0CEh, 0C7h, 84h, 24h, 0ACh, 00h, 00h, 00h, 00h, 00h, 00h, 00h
    db 0FFh, 12h, 8Bh, 74h, 24h, 24h, 85h, 0F6h, 0C7h, 84h, 24h, 0A8h, 00h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 74h, 4Eh, 8Bh, 4Ch, 24h, 2Ch, 2Bh, 0CEh, 0B8h, 0ABh, 0AAh, 0AAh, 2Ah
    db 0F7h, 0E9h, 0D1h, 0FAh, 8Bh, 0C2h, 0C1h, 0E8h, 1Fh, 03h, 0C2h, 8Dh, 04h, 40h, 0C1h, 0E0h
    db 02h, 3Dh, 80h, 00h, 00h, 00h, 76h, 21h, 56h, 0E8h, 92h, 22h, 78h, 00h, 83h, 0C4h
    db 04h, 5Eh, 8Bh, 8Ch, 24h, 9Ch, 00h, 00h, 00h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h
    db 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h, 50h, 56h, 0E8h, 0B0h, 0E9h, 72h, 00h
    db 83h, 0C4h, 08h, 8Bh, 8Ch, 24h, 0A0h, 00h, 00h, 00h, 5Eh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 81h, 0C4h, 0A8h, 00h, 00h, 00h, 0C2h, 08h, 00h
?d_000ffb80@@YAXXZ ENDP

; ghidra: FUN_004ffca0  retail @ 0x000FFCA0 size 80
public ?d_000ffca0@@YAXXZ
?d_000ffca0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 83h, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 8Dh, 4Eh, 38h
    db 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0E8h, 05h, 8Bh, 0F1h, 0FFh, 8Dh, 4Eh, 2Ch
    db 0C6h, 44h, 24h, 10h, 00h, 0E8h, 52h, 0AFh, 0F0h, 0FFh, 8Bh, 4Ch, 24h, 08h, 0C7h, 06h
    db 44h, 37h, 07h, 01h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_000ffca0@@YAXXZ ENDP

; ghidra: FUN_004ffd10  retail @ 0x000FFD10 size 194
public ?d_000ffd10@@YAXXZ
?d_000ffd10@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0B3h, 0C6h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 08h, 8Bh, 7Ch
    db 24h, 1Ch, 0C7h, 06h, 38h, 61h, 08h, 01h, 8Ah, 47h, 04h, 88h, 46h, 04h, 8Bh, 4Fh
    db 08h, 89h, 4Eh, 08h, 8Bh, 57h, 0Ch, 89h, 56h, 0Ch, 8Bh, 47h, 10h, 89h, 46h, 10h
    db 8Bh, 4Fh, 14h, 89h, 4Eh, 14h, 8Bh, 57h, 18h, 89h, 56h, 18h, 8Bh, 47h, 1Ch, 89h
    db 46h, 1Ch, 8Bh, 4Fh, 20h, 89h, 4Eh, 20h, 8Bh, 57h, 24h, 8Dh, 4Fh, 2Ch, 89h, 56h
    db 24h, 8Bh, 47h, 28h, 51h, 8Dh, 4Eh, 2Ch, 0C7h, 44h, 24h, 18h, 00h, 00h, 00h, 00h
    db 89h, 46h, 28h, 0E8h, 0E8h, 77h, 0F2h, 0FFh, 8Dh, 57h, 38h, 52h, 8Dh, 4Eh, 38h, 0C6h
    db 44h, 24h, 18h, 01h, 0E8h, 45h, 4Ch, 0F1h, 0FFh, 8Bh, 47h, 44h, 89h, 46h, 44h, 8Bh
    db 4Fh, 48h, 89h, 4Eh, 48h, 8Bh, 57h, 4Ch, 89h, 56h, 4Ch, 8Bh, 47h, 50h, 89h, 46h
    db 50h, 8Bh, 4Fh, 54h, 89h, 4Eh, 54h, 8Bh, 57h, 58h, 8Bh, 4Ch, 24h, 0Ch, 89h, 56h
    db 58h, 5Fh, 8Bh, 0C6h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_000ffd10@@YAXXZ ENDP

; ghidra: FUN_00500300  retail @ 0x00100300 size 147
public ?d_00100300@@YAXXZ
?d_00100300@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 57h, 8Bh, 7Ch, 24h, 0Ch, 8Ah, 47h, 04h, 88h, 46h, 04h, 8Bh, 4Fh
    db 08h, 89h, 4Eh, 08h, 8Bh, 57h, 0Ch, 89h, 56h, 0Ch, 8Bh, 47h, 10h, 89h, 46h, 10h
    db 8Bh, 4Fh, 14h, 89h, 4Eh, 14h, 8Dh, 57h, 18h, 8Bh, 0Ah, 8Dh, 46h, 18h, 89h, 08h
    db 8Bh, 4Ah, 04h, 89h, 48h, 04h, 8Bh, 52h, 08h, 89h, 50h, 08h, 8Bh, 47h, 24h, 89h
    db 46h, 24h, 8Bh, 4Fh, 28h, 8Dh, 57h, 2Ch, 89h, 4Eh, 28h, 52h, 8Dh, 4Eh, 2Ch, 0E8h
    db 60h, 42h, 0F2h, 0FFh, 8Dh, 47h, 38h, 50h, 8Dh, 4Eh, 38h, 0E8h, 99h, 7Ch, 0F0h, 0FFh
    db 8Dh, 4Fh, 44h, 8Bh, 01h, 8Dh, 56h, 44h, 89h, 02h, 8Bh, 41h, 04h, 89h, 42h, 04h
    db 8Bh, 49h, 08h, 89h, 4Ah, 08h, 83h, 0C7h, 50h, 8Bh, 07h, 8Dh, 56h, 50h, 89h, 02h
    db 8Bh, 4Fh, 04h, 89h, 4Ah, 04h, 8Bh, 47h, 08h, 89h, 42h, 08h, 5Fh, 8Bh, 0C6h, 5Eh
    db 0C2h, 04h, 00h
?d_00100300@@YAXXZ ENDP

; ghidra: FUN_005003c0  retail @ 0x001003C0 size 344
public ?d_001003c0@@YAXXZ
?d_001003c0@@YAXXZ PROC
    db 83h, 0ECh, 0Ch, 53h, 55h, 56h, 8Bh, 74h, 24h, 1Ch, 33h, 0DBh, 3Bh, 0F3h, 57h, 8Bh
    db 0E9h, 0Fh, 84h, 37h, 01h, 00h, 00h, 8Bh, 46h, 04h, 3Bh, 0C3h, 75h, 04h, 33h, 0C0h
    db 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CBh, 74h, 05h, 0E8h, 0CDh, 1Eh, 0F0h, 0FFh, 8Ah, 88h
    db 0C8h, 00h, 00h, 00h, 84h, 0C9h, 0Fh, 89h, 12h, 01h, 00h, 00h, 68h, 99h, 00h, 00h
    db 00h, 8Bh, 0CEh, 0E8h, 17h, 21h, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 0FEh, 00h, 00h, 00h
    db 8Bh, 55h, 10h, 8Bh, 02h, 3Bh, 0C2h, 74h, 19h, 8Bh, 7Eh, 74h, 8Dh, 64h, 24h, 00h
    db 8Bh, 48h, 08h, 39h, 79h, 04h, 0Fh, 84h, 0E2h, 00h, 00h, 00h, 8Bh, 00h, 3Bh, 0C2h
    db 75h, 0EEh, 6Ah, 0Ch, 0C7h, 86h, 20h, 02h, 00h, 00h, 0CDh, 0CCh, 0C7h, 42h, 0E8h, 0EDh
    db 1Ah, 78h, 00h, 83h, 0C4h, 04h, 3Bh, 0C3h, 74h, 0Eh, 89h, 58h, 04h, 89h, 58h, 08h
    db 0C7h, 00h, 0C0h, 60h, 08h, 01h, 8Bh, 0D8h, 8Bh, 46h, 74h, 89h, 43h, 04h, 8Bh, 0Dh
    db 98h, 08h, 2Fh, 01h, 8Bh, 51h, 3Ch, 89h, 53h, 08h, 8Bh, 45h, 10h, 8Bh, 38h, 6Ah
    db 0Ch, 0E8h, 0CAh, 0E0h, 72h, 00h, 8Dh, 48h, 08h, 83h, 0C4h, 04h, 85h, 0C9h, 74h, 02h
    db 89h, 19h, 8Bh, 4Fh, 04h, 89h, 48h, 04h, 89h, 38h, 89h, 01h, 33h, 0C9h, 89h, 47h
    db 04h, 8Bh, 0C1h, 89h, 4Ch, 24h, 14h, 6Ah, 01h, 8Dh, 54h, 24h, 14h, 89h, 4Ch, 24h
    db 1Ch, 0Dh, 08h, 00h, 08h, 00h, 52h, 8Bh, 0CEh, 89h, 44h, 24h, 18h, 0E8h, 35h, 03h
    db 0F3h, 0FFh, 8Bh, 0Dh, 98h, 08h, 2Fh, 01h, 6Ah, 01h, 68h, 0FFh, 0FFh, 00h, 00h, 56h
    db 0E8h, 67h, 0E7h, 0F1h, 0FFh, 8Bh, 06h, 8Bh, 0CEh, 0FFh, 50h, 28h, 85h, 0C0h, 74h, 09h
    db 6Ah, 07h, 8Bh, 0C8h, 0E8h, 0F1h, 73h, 0F4h, 0FFh, 8Bh, 0CEh, 0E8h, 72h, 36h, 0F0h, 0FFh
    db 85h, 0C0h, 74h, 07h, 8Bh, 10h, 8Bh, 0C8h, 0FFh, 52h, 34h, 8Bh, 86h, 04h, 02h, 00h
    db 00h, 85h, 0C0h, 74h, 0Ah, 6Ah, 02h, 8Dh, 48h, 20h, 0E8h, 71h, 48h, 0F2h, 0FFh, 8Bh
    db 8Eh, 0FCh, 01h, 00h, 00h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 50h, 5Fh, 5Eh
    db 5Dh, 5Bh, 83h, 0C4h, 0Ch, 0C2h, 04h, 00h
?d_001003c0@@YAXXZ ENDP

; ghidra: FUN_00500580  retail @ 0x00100580 size 170
public ?d_00100580@@YAXXZ
?d_00100580@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Eh, 0C7h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 53h, 56h, 8Bh, 0F1h, 57h, 89h, 74h, 24h, 0Ch, 33h
    db 0DBh, 0C7h, 06h, 38h, 61h, 08h, 01h, 89h, 5Eh, 2Ch, 89h, 5Eh, 30h, 89h, 5Ch, 24h
    db 18h, 89h, 5Eh, 34h, 8Dh, 7Eh, 38h, 89h, 1Fh, 89h, 5Fh, 04h, 89h, 5Fh, 08h, 8Bh
    db 44h, 24h, 30h, 8Bh, 4Ch, 24h, 2Ch, 8Bh, 54h, 24h, 28h, 50h, 8Bh, 44h, 24h, 28h
    db 51h, 8Bh, 4Ch, 24h, 28h, 52h, 50h, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 2Ch, 02h, 89h
    db 5Eh, 08h, 89h, 5Eh, 0Ch, 0E8h, 0F6h, 0FEh, 77h, 00h, 0D9h, 44h, 24h, 28h, 0D8h, 0Dh
    db 3Ch, 53h, 07h, 01h, 89h, 5Eh, 44h, 89h, 5Eh, 48h, 8Bh, 0CFh, 0D9h, 5Eh, 4Ch, 89h
    db 5Eh, 50h, 89h, 5Eh, 54h, 89h, 5Eh, 58h, 8Bh, 57h, 04h, 8Bh, 07h, 52h, 50h, 0E8h
    db 24h, 0B7h, 0F1h, 0FFh, 8Bh, 4Ch, 24h, 10h, 5Fh, 8Bh, 0C6h, 5Eh, 5Bh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 14h, 00h
?d_00100580@@YAXXZ ENDP

; ghidra: FUN_00500690  retail @ 0x00100690 size 2483
_TEXT ENDS
_TEXT$d00500690 SEGMENT BYTE PUBLIC FLAT 'CODE'
; retail VA 0x00500690 size 2483
public ?d_00100690@@YAXXZ
?d_00100690@@YAXXZ PROC
    db 06Ah, 0FFh, 068h
    dd g_Va00FFC795
    db 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h, 025h, 000h, 000h, 000h, 000h, 081h, 0ECh
    db 024h, 002h, 000h, 000h, 053h, 055h, 08Bh, 0ACh, 024h, 040h, 002h, 000h, 000h, 056h, 057h, 08Bh
    db 0BCh, 024h, 044h, 002h, 000h, 000h, 08Bh, 007h, 08Bh, 057h, 004h, 089h, 04Ch, 024h, 068h, 08Bh
    db 08Ch, 024h, 054h, 002h, 000h, 000h, 089h, 044h, 024h, 074h, 08Bh, 047h, 008h, 083h, 0F9h, 020h
    db 00Fh, 094h, 044h, 024h, 013h, 089h, 054h, 024h, 078h, 08Bh, 094h, 024h, 04Ch, 002h, 000h, 000h
    db 089h, 044h, 024h, 07Ch, 08Dh, 045h, 060h, 033h, 0C9h, 089h, 04Ch, 024h, 070h, 0C7h, 044h, 024h
    db 06Ch
    dd ??_7PartitionFilterWouldCollide@@6B@
    db 089h, 044h, 024h, 020h, 089h, 084h, 024h, 080h, 000h, 000h, 000h, 089h, 094h, 024h, 084h, 000h
    db 000h, 000h, 0C6h, 084h, 024h, 088h, 000h, 000h, 000h, 001h, 0D9h, 045h, 074h, 0D8h, 00Dh
    dd __real@3f8ccccd
    db 051h, 08Dh, 044h, 024h, 070h, 050h, 06Ah, 003h, 051h, 0D9h, 01Ch, 024h, 089h, 08Ch, 024h, 04Ch
    db 002h, 000h, 000h, 057h, 08Dh, 04Ch, 024h, 028h, 051h, 08Bh, 00Dh
    dd ?ThePartitionManager@@3PAVBfmeWideForwardC@@A
    call ?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHHH@Z
    db 08Bh, 09Ch, 024h, 050h, 002h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 002h, 0C7h
    db 044h, 024h, 06Ch
    dd ??_7BfmeBaseS@@6B@
    db 08Dh, 09Bh, 000h, 000h, 000h, 000h, 08Bh, 044h, 024h, 014h, 08Bh, 048h, 004h, 08Bh, 050h, 00Ch
    db 03Bh, 0D1h, 00Fh, 084h, 0C4h, 001h, 000h, 000h, 08Bh, 0CAh, 08Bh, 031h, 083h, 0C1h, 008h, 085h
    db 0F6h, 089h, 048h, 00Ch, 00Fh, 084h, 0AEh, 001h, 000h, 000h, 08Bh, 046h, 004h, 085h, 0C0h, 074h
    db 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0D0h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 075h, 048h, 08Bh, 046h, 004h, 085h
    db 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F6h, 080h, 0C8h, 000h, 000h, 000h, 040h, 075h, 0A1h, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch
    db 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0CCh, 000h, 000h, 000h, 000h, 000h, 004h, 000h, 075h, 082h, 0F6h, 086h, 044h, 003h
    db 000h, 000h, 001h, 00Fh, 085h, 075h, 0FFh, 0FFh, 0FFh, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch
    db 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0D0h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 00Fh, 085h, 052h, 0FFh, 0FFh, 0FFh
    db 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Ah, 088h, 0D4h, 000h, 000h, 000h, 084h, 0C9h, 00Fh, 088h, 031h, 0FFh, 0FFh, 0FFh, 08Bh, 046h
    db 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F7h, 080h, 0CCh, 000h, 000h, 000h, 000h, 000h, 000h, 008h, 00Fh, 085h, 00Eh, 0FFh, 0FFh, 0FFh
    db 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 0F6h, 080h, 0C8h, 000h, 000h, 000h, 004h, 074h, 02Eh, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 074h
    db 014h, 085h, 0DBh, 074h, 010h, 056h, 08Bh, 0CBh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 085h, 0C0h, 00Fh, 085h, 0D6h, 0FEh, 0FFh, 0FFh, 08Bh, 00Dh
    dd ?TheTerrainVisual@@3PAVRva001A8820TerrainVisual@@A
    db 08Bh, 011h, 06Ah, 000h, 06Ah, 001h, 056h, 0FFh, 052h, 05Ch, 0EBh, 028h, 085h, 0DBh, 00Fh, 084h
    db 0BCh, 0FEh, 0FFh, 0FFh, 056h, 08Bh, 0CBh
    call ?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z
    db 085h, 0C0h, 00Fh, 085h, 0ACh, 0FEh, 0FFh, 0FFh, 08Bh, 00Dh
    dd ?TheTerrainVisual@@3PAVRva001A8820TerrainVisual@@A
    db 08Bh, 001h, 06Ah, 000h, 06Ah, 001h, 056h, 0FFh, 050h, 05Ch, 08Bh, 044h, 024h, 014h, 0FFh, 048h
    db 010h, 08Bh, 044h, 024h, 014h, 08Bh, 048h, 010h, 085h, 0C9h, 0C7h, 084h, 024h, 03Ch, 002h, 000h
    db 000h, 0FFh, 0FFh, 0FFh, 0FFh, 00Fh, 085h, 0DBh, 006h, 000h, 000h, 08Bh, 008h, 085h, 0C9h, 08Bh
    db 0F0h, 074h, 035h, 08Bh, 040h, 008h, 02Bh, 0C1h, 0C1h, 0F8h, 003h, 0C1h, 0E0h, 003h, 03Dh, 080h
    db 000h, 000h, 000h, 076h, 019h, 051h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 032h, 0C0h, 0E9h, 010h, 007h, 000h, 000h, 050h, 051h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 032h, 0C0h, 0E9h, 0F6h, 006h, 000h, 000h, 08Bh, 044h, 024h, 014h, 08Ah, 04Ch
    db 024h, 013h, 084h, 0C9h, 074h, 066h, 0FFh, 048h, 010h, 08Bh, 044h, 024h, 014h, 08Bh, 048h, 010h
    db 085h, 0C9h, 0C7h, 084h, 024h, 03Ch, 002h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 00Fh, 085h, 0CBh
    db 006h, 000h, 000h, 08Bh, 008h, 085h, 0C9h, 08Bh, 0F0h, 074h, 033h, 08Bh, 040h, 008h, 02Bh, 0C1h
    db 0C1h, 0F8h, 003h, 0C1h, 0E0h, 003h, 03Dh, 080h, 000h, 000h, 000h, 076h, 017h, 051h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0E9h, 09Ah, 006h, 000h, 000h, 050h, 051h
    call ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
    db 083h, 0C4h, 008h, 056h
    call ??3@YAXPAX@Z
    db 083h, 0C4h, 004h, 0E9h, 082h, 006h, 000h, 000h, 0D9h, 045h, 070h, 033h, 0C9h, 08Bh, 0C1h, 0DCh
    db 0C0h, 089h, 04Ch, 024h, 03Ch, 089h, 04Ch, 024h, 040h, 089h, 04Ch, 024h, 044h, 0D9h, 05Ch, 024h
    db 028h, 089h, 04Ch, 024h, 048h, 068h
    dd ?KINDOFMASK_NONE@@3UKindOfMaskType@@B
    db 08Dh, 054h, 024h, 03Ch, 089h, 04Ch, 024h, 050h, 00Dh, 080h, 000h, 000h, 000h, 052h, 08Dh, 08Ch
    db 024h, 004h, 002h, 000h, 000h, 089h, 044h, 024h, 040h
    call ?j_000382fd@@YAXXZ
    db 06Ah, 000h, 050h, 08Bh, 044h, 024h, 030h, 06Ah, 001h, 050h, 057h, 08Dh, 04Ch, 024h, 030h, 051h
    db 08Bh, 00Dh
    dd ?ThePartitionManager@@3PAVBfmeWideForwardC@@A
    db 0C6h, 084h, 024h, 054h, 002h, 000h, 000h, 003h
    call ?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHHH@Z
    db 08Bh, 08Ch, 024h, 058h, 002h, 000h, 000h, 085h, 0C9h, 08Bh, 095h, 0B4h, 003h, 000h, 000h, 08Bh
    db 085h, 0B8h, 003h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 005h, 0C7h, 084h, 024h
    db 0FCh, 001h, 000h, 000h
    dd ??_7BfmeBaseS@@6B@
    db 089h, 054h, 024h, 018h, 089h, 044h, 024h, 024h, 074h, 045h
    call ?j_00015460@@YAXXZ
    db 084h, 0C0h, 074h, 03Ch, 0D9h, 044h, 024h, 024h, 0D8h, 01Dh
    dd ?value@BfmeReportWeightScaleHolder@@2MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 02Bh, 0D9h, 044h, 024h, 018h, 0C7h, 044h, 024h, 024h, 000h
    db 000h, 0F0h, 041h, 0D8h, 025h
    dd ?value@BfmeReportWeightScaleHolder@@2MB
    db 0D9h, 054h, 024h, 018h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 005h, 07Ah, 008h, 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h, 08Bh
    db 074h, 024h, 020h, 056h, 08Dh, 08Ch, 024h, 0ECh, 000h, 000h, 000h, 0C6h, 044h, 024h, 017h, 000h
    call ?j_0002b355@@YAXXZ
    db 08Dh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 006h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 044h, 024h, 024h, 051h, 08Dh, 08Ch, 024h, 0ECh, 000h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?j_000424b5@@YAXXZ
    db 08Dh, 08Ch, 024h, 0E8h, 000h, 000h, 000h
    call ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
    db 084h, 0C0h, 08Dh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 075h, 030h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 051h, 08Dh, 08Ch, 024h, 0ECh, 000h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 051h, 0D9h, 01Ch, 024h, 068h, 000h, 000h, 020h, 042h, 06Ah, 000h, 06Ah, 002h, 08Dh, 08Ch, 024h
    db 0FCh, 000h, 000h, 000h
    call ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
    db 0EBh, 01Fh
    call ?boxMinorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 051h, 08Dh, 08Ch, 024h, 0ECh, 000h, 000h, 000h, 0D8h, 044h, 024h, 028h, 0D9h, 01Ch, 024h
    call ?j_0002ca2f@@YAXXZ
    db 056h, 08Dh, 08Ch, 024h, 0A4h, 001h, 000h, 000h
    call ?j_0002b355@@YAXXZ
    db 08Dh, 08Ch, 024h, 0A0h, 001h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 007h
    call ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
    db 084h, 0C0h, 075h, 022h, 08Dh, 08Ch, 024h, 0A0h, 001h, 000h, 000h
    call ?boxMinorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 051h, 08Dh, 08Ch, 024h, 0A4h, 001h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?j_0002ca2f@@YAXXZ
    db 0D9h, 044h, 024h, 018h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0D9h, 05Ch, 024h, 020h, 08Bh, 04Ch, 024h, 020h, 051h, 08Dh, 08Ch, 024h, 0A4h, 001h, 000h, 000h
    call ?j_000424b5@@YAXXZ
    db 0D9h, 044h, 024h, 018h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 058h, 0D9h, 084h, 024h, 04Ch, 002h, 000h, 000h, 08Bh, 017h
    db 0D9h, 0FFh, 08Bh, 047h, 004h, 08Bh, 04Fh, 008h, 089h, 04Ch, 024h, 034h, 08Bh, 0CEh, 089h, 054h
    db 024h, 02Ch, 089h, 044h, 024h, 030h, 0C6h, 044h, 024h, 013h, 001h, 0D9h, 05Ch, 024h, 028h, 0D9h
    db 084h, 024h, 04Ch, 002h, 000h, 000h, 0D9h, 0FEh, 0D9h, 05Ch, 024h, 018h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 044h, 024h, 020h, 0D9h, 044h, 024h, 028h, 0D8h, 0C9h, 0D8h, 044h, 024h, 02Ch, 0D9h, 05Ch
    db 024h, 02Ch, 0D8h, 04Ch, 024h, 018h, 0D8h, 044h, 024h, 030h, 0D9h, 05Ch, 024h, 030h, 08Bh, 044h
    db 024h, 01Ch, 08Bh, 008h, 08Bh, 0ACh, 024h, 04Ch, 002h, 000h, 000h, 089h, 048h, 00Ch, 08Bh, 04Ch
    db 024h, 01Ch, 08Bh, 041h, 004h, 08Bh, 051h, 00Ch, 03Bh, 0D0h, 00Fh, 084h, 0C6h, 003h, 000h, 000h
    db 08Bh, 0C2h, 08Bh, 030h, 083h, 0C0h, 008h, 085h, 0F6h, 089h, 041h, 00Ch, 00Fh, 084h, 0B4h, 003h
    db 000h, 000h, 08Bh, 04Ch, 024h, 068h, 056h
    call ?j_00048d15@@YAXXZ
    db 03Ch, 001h, 074h, 0CEh, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h
    db 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Ah, 088h, 0D4h, 000h, 000h, 000h, 084h, 0C9h, 078h, 0B1h, 06Ah, 03Bh, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 075h, 0A4h, 08Bh, 046h, 004h, 085h, 0C0h, 074h, 00Ch, 08Bh, 048h, 004h, 085h, 0C9h
    db 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 090h, 0B4h, 003h, 000h, 000h, 08Bh, 046h, 004h, 085h, 0C0h, 089h, 054h, 024h, 020h, 074h
    db 00Ch, 08Bh, 048h, 004h, 085h, 0C9h, 074h, 005h
    call ?j_000022bb@@YAXXZ
    db 08Bh, 080h, 0B8h, 003h, 000h, 000h, 08Dh, 0BEh, 0ACh, 000h, 000h, 000h, 057h, 08Dh, 08Ch, 024h
    db 090h, 000h, 000h, 000h, 089h, 044h, 024h, 02Ch, 032h, 0DBh
    call ?j_0002b355@@YAXXZ
    db 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 008h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 044h, 024h, 028h, 051h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?j_000424b5@@YAXXZ
    db 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h
    call ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
    db 084h, 0C0h, 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 075h, 030h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 051h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 051h, 0D9h, 01Ch, 024h, 068h, 000h, 000h, 020h, 042h, 06Ah, 000h, 06Ah, 002h, 08Dh, 08Ch, 024h
    db 0A0h, 000h, 000h, 000h
    call ?set@GeometryInfo@@QAEXW4GeometryType@@_NMMM@Z
    db 0EBh, 01Fh
    call ?boxMinorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 051h, 08Dh, 08Ch, 024h, 090h, 000h, 000h, 000h, 0D8h, 044h, 024h, 028h, 0D9h, 01Ch, 024h
    call ?j_0002ca2f@@YAXXZ
    db 057h, 08Dh, 08Ch, 024h, 048h, 001h, 000h, 000h
    call ?j_0002b355@@YAXXZ
    db 0D9h, 044h, 024h, 020h, 0D8h, 00Dh
    dd ?g_bfmeADL@@3MA
    db 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 009h, 0D9h, 05Ch, 024h, 018h, 08Bh, 04Ch, 024h, 018h
    db 051h, 08Dh, 08Ch, 024h, 048h, 001h, 000h, 000h
    call ?j_000424b5@@YAXXZ
    db 08Dh, 08Ch, 024h, 044h, 001h, 000h, 000h
    call ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
    db 084h, 0C0h, 075h, 017h, 08Bh, 0CFh
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 051h, 08Dh, 08Ch, 024h, 048h, 001h, 000h, 000h, 0D9h, 01Ch, 024h
    call ?j_0002ca2f@@YAXXZ
    db 0D9h, 044h, 024h, 020h, 0D8h, 01Dh
    dd ?BfmeBoundaryZero3D@@3MB
    db 0DFh, 0E0h, 0F6h, 0C4h, 041h, 075h, 050h, 0D9h, 046h, 044h, 08Dh, 056h, 038h, 0D9h, 0FFh, 08Bh
    db 002h, 08Bh, 04Ah, 004h, 08Bh, 052h, 008h, 089h, 04Ch, 024h, 03Ch, 08Bh, 0CFh, 089h, 044h, 024h
    db 038h, 089h, 054h, 024h, 040h, 0B3h, 001h, 0D9h, 05Ch, 024h, 060h, 0D9h, 046h, 044h, 0D9h, 0FEh
    db 0D9h, 05Ch, 024h, 054h
    call ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
    db 0D8h, 044h, 024h, 018h, 0D9h, 044h, 024h, 060h, 0D8h, 0C9h, 0D8h, 044h, 024h, 038h, 0D9h, 05Ch
    db 024h, 038h, 0D8h, 04Ch, 024h, 054h, 0D8h, 044h, 024h, 03Ch, 0D9h, 05Ch, 024h, 03Ch, 08Bh, 08Ch
    db 024h, 044h, 002h, 000h, 000h, 08Bh, 046h, 044h, 055h, 051h, 08Dh, 094h, 024h, 0F0h, 000h, 000h
    db 000h, 052h, 050h, 08Dh, 07Eh, 038h, 057h, 08Dh, 08Ch, 024h, 0A0h, 000h, 000h, 000h, 089h, 044h
    db 024h, 064h
    call ?d_0087f2f0@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 09Dh, 001h, 000h, 000h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 075h, 057h
    db 084h, 0DBh, 075h, 053h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 028h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 040h, 0D9h, 005h
    dd ?BfmeBoundaryZero3D@@3MB
    db 0D9h, 044h, 024h, 024h, 0DAh, 0E9h, 0DFh, 0E0h, 0F6h, 0C4h, 044h, 07Ah, 02Dh, 08Dh, 08Ch, 024h
    db 044h, 001h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 008h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 007h
    call ?j_000309f4@@YAXXZ
    db 0E9h, 07Bh, 0FDh, 0FFh, 0FFh, 06Ah, 002h, 08Bh, 0CEh
    call ?j_0003251f@@YAXXZ
    db 084h, 0C0h, 074h, 0C6h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 074h, 027h, 08Bh, 04Eh, 044h, 055h
    db 08Dh, 054h, 024h, 030h, 052h, 08Dh, 084h, 024h, 0A8h, 001h, 000h, 000h, 050h, 051h, 089h, 04Ch
    db 024h, 06Ch, 057h, 08Dh, 08Ch, 024h, 0A0h, 000h, 000h, 000h
    call ?d_0087f2f0@@YAXXZ
    db 084h, 0C0h, 075h, 079h, 084h, 0DBh, 074h, 032h, 08Bh, 084h, 024h, 044h, 002h, 000h, 000h, 08Bh
    db 056h, 044h, 055h, 050h, 08Dh, 08Ch, 024h, 0F0h, 000h, 000h, 000h, 051h, 052h, 08Dh, 044h, 024h
    db 048h, 050h, 08Dh, 08Ch, 024h, 058h, 001h, 000h, 000h, 089h, 054h, 024h, 078h
    call ?d_0087f2f0@@YAXXZ
    db 084h, 0C0h, 00Fh, 085h, 0CCh, 000h, 000h, 000h, 08Ah, 044h, 024h, 013h, 084h, 0C0h, 00Fh, 084h
    db 055h, 0FFh, 0FFh, 0FFh, 084h, 0DBh, 00Fh, 084h, 04Dh, 0FFh, 0FFh, 0FFh, 08Bh, 04Eh, 044h, 055h
    db 08Dh, 054h, 024h, 030h, 052h, 08Dh, 084h, 024h, 0A8h, 001h, 000h, 000h, 050h, 051h, 08Dh, 054h
    db 024h, 048h, 089h, 04Ch, 024h, 068h, 052h, 08Dh, 08Ch, 024h, 058h, 001h, 000h, 000h
    call ?d_0087f2f0@@YAXXZ
    db 084h, 0C0h, 00Fh, 084h, 01Eh, 0FFh, 0FFh, 0FFh, 08Bh, 00Dh
    dd ?TheTerrainVisual@@3PAVRva001A8820TerrainVisual@@A
    db 08Bh, 011h, 06Ah, 000h, 06Ah, 001h, 056h, 0FFh, 052h, 05Ch, 08Dh, 08Ch, 024h, 044h, 001h, 000h
    db 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 008h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 08Ch, 024h, 08Ch, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 007h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 08Ch, 024h, 0A0h, 001h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 006h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 005h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 002h
    call ?j_0002c471@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0C7h, 084h, 024h, 03Ch, 002h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_0002c471@@YAXXZ
    db 032h, 0C0h, 0EBh, 064h, 08Bh, 00Dh
    dd ?TheTerrainVisual@@3PAVRva001A8820TerrainVisual@@A
    db 08Bh, 001h, 06Ah, 000h, 06Ah, 001h, 056h, 0FFh, 050h, 05Ch, 0E9h, 072h, 0FFh, 0FFh, 0FFh, 08Dh
    db 08Ch, 024h, 0A0h, 001h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 006h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 08Ch, 024h, 0E8h, 000h, 000h, 000h, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 005h
    call ?j_000309f4@@YAXXZ
    db 08Dh, 04Ch, 024h, 01Ch, 0C6h, 084h, 024h, 03Ch, 002h, 000h, 000h, 002h
    call ?j_0002c471@@YAXXZ
    db 08Dh, 04Ch, 024h, 014h, 0C7h, 084h, 024h, 03Ch, 002h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
    call ?j_0002c471@@YAXXZ
    db 0B0h, 001h, 08Bh, 08Ch, 024h, 034h, 002h, 000h, 000h, 05Fh, 05Eh, 05Dh, 05Bh, 064h, 089h, 00Dh
    db 000h, 000h, 000h, 000h, 081h, 0C4h, 030h, 002h, 000h, 000h, 0C2h, 018h, 000h
?d_00100690@@YAXXZ ENDP
_TEXT$d00500690 ENDS
_TEXT SEGMENT

; ghidra: FUN_005012b0  retail @ 0x001012B0 size 1109
public ?d_001012b0@@YAXXZ
?d_001012b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Ah, 0C8h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 81h, 0ECh, 0Ch, 01h, 00h, 00h, 53h, 55h, 56h, 8Bh, 0B4h
    db 24h, 28h, 01h, 00h, 00h, 8Bh, 46h, 70h, 57h, 8Bh, 0D0h, 52h, 50h, 68h, 00h, 00h
    db 20h, 41h, 8Bh, 0C8h, 33h, 0EDh, 55h, 89h, 4Ch, 24h, 24h, 6Ah, 02h, 8Dh, 8Ch, 24h
    db 84h, 00h, 00h, 00h, 89h, 44h, 24h, 24h, 0E8h, 71h, 68h, 0F3h, 0FFh, 83h, 0C6h, 60h
    db 8Bh, 0CEh, 89h, 0ACh, 24h, 24h, 01h, 00h, 00h, 0E8h, 0C2h, 0D5h, 77h, 00h, 84h, 0C0h
    db 74h, 0Ah, 56h, 8Dh, 4Ch, 24h, 74h, 0E8h, 0Ch, 25h, 0F0h, 0FFh, 0D9h, 84h, 24h, 80h
    db 00h, 00h, 00h, 8Bh, 0BCh, 24h, 30h, 01h, 00h, 00h, 0D8h, 0Dh, 0ACh, 61h, 08h, 01h
    db 89h, 6Ch, 24h, 1Ch, 0C7h, 44h, 24h, 18h, 0C4h, 60h, 08h, 01h, 89h, 7Ch, 24h, 20h
    db 0D9h, 54h, 24h, 30h, 0D9h, 5Ch, 24h, 24h, 8Dh, 4Ch, 24h, 18h, 51h, 8Bh, 0Dh, 0B8h
    db 0D5h, 2Eh, 01h, 8Dh, 54h, 24h, 14h, 52h, 0C6h, 84h, 24h, 2Ch, 01h, 00h, 00h, 01h
    db 0E8h, 0DBh, 16h, 8Fh, 00h, 8Bh, 44h, 24h, 10h, 0FFh, 48h, 10h, 8Bh, 44h, 24h, 10h
    db 39h, 68h, 10h, 75h, 38h, 8Bh, 08h, 3Bh, 0CDh, 8Bh, 0F0h, 74h, 27h, 8Bh, 40h, 08h
    db 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh, 80h, 00h, 00h, 00h, 76h, 0Bh, 51h
    db 0E8h, 1Bh, 0Bh, 78h, 00h, 83h, 0C4h, 04h, 0EBh, 0Ah, 50h, 51h, 0E8h, 4Fh, 0D2h, 72h
    db 00h, 83h, 0C4h, 08h, 56h, 0E8h, 06h, 0Bh, 78h, 00h, 83h, 0C4h, 04h, 8Bh, 07h, 8Bh
    db 4Fh, 04h, 8Bh, 57h, 08h, 89h, 44h, 24h, 58h, 89h, 4Ch, 24h, 5Ch, 8Bh, 8Ch, 24h
    db 34h, 01h, 00h, 00h, 8Dh, 44h, 24h, 70h, 32h, 0DBh, 89h, 6Ch, 24h, 54h, 0C7h, 44h
    db 24h, 50h, 0A0h, 60h, 08h, 01h, 89h, 54h, 24h, 60h, 89h, 44h, 24h, 64h, 89h, 4Ch
    db 24h, 68h, 0C6h, 44h, 24h, 6Ch, 01h, 33h, 0D2h, 8Bh, 0C2h, 6Ah, 3Bh, 89h, 54h, 24h
    db 20h, 6Ah, 67h, 89h, 54h, 24h, 28h, 68h, 85h, 00h, 00h, 00h, 89h, 54h, 24h, 30h
    db 6Ah, 58h, 89h, 54h, 24h, 38h, 83h, 0C8h, 02h, 55h, 8Dh, 8Ch, 24h, 0E0h, 00h, 00h
    db 00h, 89h, 54h, 24h, 40h, 89h, 44h, 24h, 2Ch, 0E8h, 3Fh, 0FEh, 0EFh, 0FFh, 50h, 8Dh
    db 44h, 24h, 1Ch, 50h, 8Dh, 8Ch, 24h, 0ECh, 00h, 00h, 00h, 0E8h, 0CDh, 6Eh, 0F3h, 0FFh
    db 89h, 6Ch, 24h, 38h, 0C7h, 44h, 24h, 34h, 0B0h, 60h, 08h, 01h, 89h, 6Ch, 24h, 40h
    db 0C7h, 44h, 24h, 3Ch, 80h, 3Bh, 08h, 01h, 8Bh, 8Ch, 24h, 84h, 00h, 00h, 00h, 55h
    db 8Dh, 54h, 24h, 54h, 52h, 50h, 8Dh, 44h, 24h, 40h, 89h, 4Ch, 24h, 1Ch, 50h, 8Dh
    db 4Ch, 24h, 4Ch, 0C6h, 84h, 24h, 34h, 01h, 00h, 00h, 05h, 0E8h, 70h, 16h, 8Fh, 00h
    db 8Bh, 0C8h, 0E8h, 69h, 16h, 8Fh, 00h, 8Bh, 0C8h, 0E8h, 62h, 16h, 8Fh, 00h, 0D9h, 44h
    db 24h, 14h, 0D8h, 0Dh, 34h, 61h, 08h, 01h, 50h, 6Ah, 03h, 51h, 0D9h, 1Ch, 24h, 57h
    db 8Dh, 4Ch, 24h, 28h, 51h, 8Bh, 0Dh, 0B8h, 0D5h, 2Eh, 01h, 0E8h, 0C0h, 14h, 8Fh, 00h
    db 0B8h, 5Ch, 3Bh, 08h, 01h, 89h, 44h, 24h, 3Ch, 89h, 44h, 24h, 34h, 89h, 84h, 24h
    db 0E4h, 00h, 00h, 00h, 0C6h, 84h, 24h, 24h, 01h, 00h, 00h, 07h, 89h, 44h, 24h, 50h
    db 8Bh, 44h, 24h, 14h, 8Bh, 48h, 04h, 8Bh, 50h, 0Ch, 3Bh, 0D1h, 0Fh, 84h, 0ADh, 01h
    db 00h, 00h, 8Bh, 0CAh, 8Bh, 31h, 83h, 0C1h, 08h, 3Bh, 0F5h, 89h, 48h, 0Ch, 0Fh, 84h
    db 97h, 01h, 00h, 00h, 8Bh, 46h, 04h, 3Bh, 0C5h, 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh
    db 48h, 04h, 3Bh, 0CDh, 74h, 05h, 0E8h, 0C0h, 0Dh, 0F0h, 0FFh, 0F6h, 80h, 0C8h, 00h, 00h
    db 00h, 04h, 75h, 0BCh, 8Bh, 46h, 04h, 3Bh, 0C5h, 75h, 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh
    db 48h, 04h, 3Bh, 0CDh, 74h, 05h, 0E8h, 0A0h, 0Dh, 0F0h, 0FFh, 0F7h, 80h, 0CCh, 00h, 00h
    db 00h, 00h, 00h, 00h, 02h, 75h, 99h, 8Bh, 46h, 04h, 3Bh, 0C5h, 75h, 04h, 33h, 0C0h
    db 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CDh, 74h, 05h, 0E8h, 7Dh, 0Dh, 0F0h, 0FFh, 0F7h, 80h
    db 0D0h, 00h, 00h, 00h, 00h, 00h, 00h, 01h, 75h, 42h, 8Bh, 46h, 04h, 3Bh, 0C5h, 75h
    db 04h, 33h, 0C0h, 0EBh, 0Ch, 8Bh, 48h, 04h, 3Bh, 0CDh, 74h, 05h, 0E8h, 5Ah, 0Dh, 0F0h
    db 0FFh, 0F6h, 80h, 0C8h, 00h, 00h, 00h, 40h, 0Fh, 85h, 52h, 0FFh, 0FFh, 0FFh, 6Ah, 32h
    db 8Bh, 0CEh, 0E8h, 0A8h, 0Fh, 0F3h, 0FFh, 84h, 0C0h, 0Fh, 85h, 41h, 0FFh, 0FFh, 0FFh, 0F6h
    db 86h, 44h, 03h, 00h, 00h, 01h, 0Fh, 85h, 34h, 0FFh, 0FFh, 0FFh, 8Bh, 86h, 3Ch, 02h
    db 00h, 00h, 8Bh, 8Ch, 24h, 38h, 01h, 00h, 00h, 50h, 0E8h, 0DBh, 0D1h, 0F3h, 0FFh, 83h
    db 0F8h, 01h, 74h, 0Ch, 83h, 0F8h, 02h, 74h, 07h, 0B3h, 01h, 0E9h, 10h, 0FFh, 0FFh, 0FFh
    db 8Bh, 0CEh, 0E8h, 0C0h, 0A8h, 0F2h, 0FFh, 3Bh, 0C5h, 74h, 12h, 8Bh, 10h, 8Bh, 0C8h, 0FFh
    db 92h, 0A0h, 01h, 00h, 00h, 84h, 0C0h, 0Fh, 85h, 0F3h, 0FEh, 0FFh, 0FFh, 8Bh, 0B6h, 04h
    db 02h, 00h, 00h, 3Bh, 0F5h, 74h, 0D2h, 68h, 21h, 07h, 00h, 00h, 68h, 60h, 61h, 08h
    db 01h, 68h, 00h, 00h, 0C0h, 3Fh, 68h, 00h, 00h, 00h, 3Fh, 0E8h, 0B5h, 0B6h, 0F2h, 0FFh
    db 0D8h, 4Ch, 24h, 40h, 68h, 24h, 07h, 00h, 00h, 68h, 60h, 61h, 08h, 01h, 68h, 0DBh
    db 0Fh, 49h, 40h, 0D9h, 5Ch, 24h, 2Ch, 68h, 0DBh, 0Fh, 49h, 0C0h, 0E8h, 94h, 0B6h, 0F2h
    db 0FFh, 0D9h, 0C0h, 0D9h, 0FEh, 8Bh, 47h, 08h, 83h, 0C4h, 20h, 8Bh, 0CEh, 89h, 44h, 24h
    db 4Ch, 0D9h, 0C9h, 0D9h, 0FFh, 0D9h, 44h, 24h, 10h, 0D8h, 0C9h, 0D9h, 0C2h, 0D8h, 0Dh, 50h
    db 53h, 07h, 01h, 0DEh, 0E9h, 0D9h, 5Ch, 24h, 18h, 0D9h, 0C9h, 0D8h, 4Ch, 24h, 10h, 0D9h
    db 0C9h, 0D8h, 0Dh, 50h, 53h, 07h, 01h, 0DEh, 0C1h, 0D9h, 44h, 24h, 18h, 0D8h, 07h, 0D9h
    db 5Ch, 24h, 44h, 0D8h, 47h, 04h, 0D9h, 5Ch, 24h, 48h, 0E8h, 15h, 31h, 0F4h, 0FFh, 84h
    db 0C0h, 0Fh, 85h, 59h, 0FEh, 0FFh, 0FFh, 6Ah, 02h, 8Dh, 4Ch, 24h, 48h, 51h, 8Dh, 4Eh
    db 20h, 0E8h, 0B9h, 0F5h, 0F1h, 0FFh, 0E9h, 45h, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h, 14h, 8Bh
    db 50h, 10h, 84h, 0DBh, 0Fh, 94h, 0C3h, 4Ah, 89h, 50h, 10h, 8Bh, 44h, 24h, 14h, 39h
    db 68h, 10h, 0C6h, 84h, 24h, 24h, 01h, 00h, 00h, 00h, 75h, 38h, 8Bh, 08h, 3Bh, 0CDh
    db 8Bh, 0F0h, 74h, 27h, 8Bh, 40h, 08h, 2Bh, 0C1h, 0C1h, 0F8h, 03h, 0C1h, 0E0h, 03h, 3Dh
    db 80h, 00h, 00h, 00h, 76h, 0Bh, 51h, 0E8h, 0F4h, 07h, 78h, 00h, 83h, 0C4h, 04h, 0EBh
    db 0Ah, 50h, 51h, 0E8h, 28h, 0CFh, 72h, 00h, 83h, 0C4h, 08h, 56h, 0E8h, 0DFh, 07h, 78h
    db 00h, 83h, 0C4h, 04h, 8Dh, 4Ch, 24h, 70h, 0C7h, 84h, 24h, 24h, 01h, 00h, 00h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0Ch, 0F3h, 0F2h, 0FFh, 8Bh, 8Ch, 24h, 1Ch, 01h, 00h, 00h, 5Fh
    db 5Eh, 5Dh, 8Ah, 0C3h, 5Bh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 81h, 0C4h, 18h, 01h
    db 00h, 00h, 0C2h, 10h, 00h
?d_001012b0@@YAXXZ ENDP

; ghidra: FUN_00501c10  retail @ 0x00101C10 size 18
public ?d_00101c10@@YAXXZ
?d_00101c10@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 0E8h, 18h, 0FEh, 89h, 00h, 0C7h, 06h, 0C8h, 61h, 08h, 01h, 8Bh, 0C6h
    db 5Eh, 0C3h
?d_00101c10@@YAXXZ ENDP

; ghidra: FUN_00502470  retail @ 0x00102470 size 31
public ?d_00102470@@YAXXZ
?d_00102470@@YAXXZ PROC
    db 0F6h, 44h, 24h, 04h, 01h, 56h, 8Bh, 0F1h, 0C7h, 06h, 18h, 63h, 08h, 01h, 74h, 09h
    db 56h, 0E8h, 2Ah, 0FAh, 77h, 00h, 83h, 0C4h, 04h, 8Bh, 0C6h, 5Eh, 0C2h, 04h, 00h
?d_00102470@@YAXXZ ENDP

; ghidra: FUN_005025f0  retail @ 0x001025F0 size 24
public ?d_001025f0@@YAXXZ
?d_001025f0@@YAXXZ PROC
    db 8Bh, 09h, 85h, 0C9h, 74h, 11h, 56h, 8Bh, 01h, 8Bh, 71h, 04h, 6Ah, 01h, 0FFh, 10h
    db 85h, 0F6h, 8Bh, 0CEh, 75h, 0F1h, 5Eh, 0C3h
?d_001025f0@@YAXXZ ENDP

; ghidra: FUN_00502610  retail @ 0x00102610 size 37
public ?d_00102610@@YAXXZ
?d_00102610@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 04h, 8Bh, 41h, 08h, 8Bh, 51h, 04h, 89h, 10h, 8Bh, 41h, 04h, 85h
    db 0C0h, 74h, 06h, 8Bh, 51h, 08h, 89h, 50h, 08h, 8Bh, 01h, 0C7h, 44h, 24h, 04h, 01h
    db 00h, 00h, 00h, 0FFh, 20h
?d_00102610@@YAXXZ ENDP

; ghidra: FUN_00502870  retail @ 0x00102870 size 65
public ?d_00102870@@YAXXZ
?d_00102870@@YAXXZ PROC
    db 56h, 57h, 6Ah, 00h, 8Bh, 0F1h, 0FFh, 15h, 30h, 8Fh, 35h, 01h, 8Bh, 0Dh, 24h, 0D5h
    db 2Eh, 01h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 40h, 8Bh, 7Ch, 24h, 10h, 8Bh
    db 0Eh, 8Bh, 44h, 24h, 0Ch, 8Bh, 11h, 57h, 50h, 0FFh, 12h, 8Bh, 46h, 1Ch, 85h, 0C0h
    db 74h, 0Ah, 29h, 78h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 5Fh, 5Eh, 0C2h, 08h
    db 00h
?d_00102870@@YAXXZ ENDP

; ghidra: FUN_005028d0  retail @ 0x001028D0 size 27
public ?d_001028d0@@YAXXZ
?d_001028d0@@YAXXZ PROC
    db 8Bh, 4Ch, 24h, 0Ch, 85h, 0C9h, 75h, 03h, 32h, 0C0h, 0C3h, 8Bh, 54h, 24h, 08h, 8Bh
    db 01h, 52h, 8Bh, 54h, 24h, 08h, 52h, 0FFh, 50h, 04h, 0C3h
?d_001028d0@@YAXXZ ENDP

; ghidra: FUN_00502910  retail @ 0x00102910 size 144
public ?d_00102910@@YAXXZ
?d_00102910@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0Bh, 0C9h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 57h, 8Bh, 0F9h, 89h, 7Ch, 24h, 08h, 8Bh, 4Fh
    db 1Ch, 85h, 0C9h, 0C7h, 44h, 24h, 14h, 00h, 00h, 00h, 00h, 74h, 12h, 8Dh, 49h, 00h
    db 8Bh, 01h, 8Bh, 71h, 04h, 6Ah, 01h, 0FFh, 10h, 85h, 0F6h, 8Bh, 0CEh, 75h, 0F1h, 8Bh
    db 4Fh, 18h, 85h, 0C9h, 0C7h, 47h, 1Ch, 00h, 00h, 00h, 00h, 74h, 12h, 8Dh, 49h, 00h
    db 8Bh, 11h, 8Bh, 71h, 04h, 6Ah, 01h, 0FFh, 12h, 85h, 0F6h, 8Bh, 0CEh, 75h, 0F1h, 8Bh
    db 4Fh, 04h, 85h, 0C9h, 0C7h, 44h, 24h, 14h, 0FFh, 0FFh, 0FFh, 0FFh, 74h, 11h, 8Bh, 0FFh
    db 8Bh, 01h, 8Bh, 71h, 04h, 6Ah, 01h, 0FFh, 10h, 85h, 0F6h, 8Bh, 0CEh, 75h, 0F1h, 8Bh
    db 4Ch, 24h, 0Ch, 5Fh, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C3h
?d_00102910@@YAXXZ ENDP

; ghidra: FUN_005029d0  retail @ 0x001029D0 size 81
public ?d_001029d0@@YAXXZ
?d_001029d0@@YAXXZ PROC
    db 56h, 8Bh, 0F1h, 8Bh, 46h, 1Ch, 85h, 0C0h, 74h, 45h, 8Bh, 48h, 18h, 85h, 0C9h, 7Eh
    db 2Bh, 8Bh, 0Eh, 57h, 8Bh, 39h, 0FFh, 57h, 04h, 8Bh, 4Eh, 1Ch, 8Bh, 51h, 18h, 8Bh
    db 0Eh, 03h, 0C2h, 50h, 0FFh, 57h, 08h, 8Bh, 46h, 1Ch, 85h, 0C0h, 8Bh, 48h, 18h, 74h
    db 0Ah, 29h, 48h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 5Fh, 8Bh, 4Eh, 1Ch, 85h
    db 0C9h, 8Bh, 51h, 04h, 89h, 56h, 1Ch, 74h, 06h, 8Bh, 01h, 6Ah, 01h, 0FFh, 10h, 5Eh
    db 0C3h
?d_001029d0@@YAXXZ ENDP

; ghidra: FUN_00502a40  retail @ 0x00102A40 size 20
public ?d_00102a40@@YAXXZ
?d_00102a40@@YAXXZ PROC
    db 8Bh, 0C1h, 33h, 0C9h, 0C7h, 00h, 04h, 63h, 08h, 01h, 89h, 48h, 04h, 89h, 48h, 08h
    db 89h, 48h, 0Ch, 0C3h
?d_00102a40@@YAXXZ ENDP

; ghidra: FUN_00502c80  retail @ 0x00102C80 size 97
public ?d_00102c80@@YAXXZ
?d_00102c80@@YAXXZ PROC
    db 53h, 56h, 57h, 8Bh, 7Ch, 24h, 10h, 8Bh, 07h, 85h, 0C0h, 8Bh, 0F1h, 74h, 0Ah, 0Fh
    db 0B7h, 40h, 04h, 89h, 44h, 24h, 10h, 0EBh, 08h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h
    db 00h, 8Bh, 4Eh, 04h, 8Bh, 1Dh, 0F4h, 93h, 35h, 01h, 51h, 6Ah, 01h, 8Dh, 54h, 24h
    db 18h, 6Ah, 02h, 52h, 0FFh, 0D3h, 8Bh, 07h, 83h, 0C4h, 10h, 85h, 0C0h, 74h, 05h, 83h
    db 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh, 38h, 07h, 01h, 8Bh, 4Eh, 04h, 0Fh, 0B7h, 54h, 24h
    db 10h, 51h, 6Ah, 01h, 52h, 50h, 0FFh, 0D3h, 83h, 0C4h, 10h, 5Fh, 5Eh, 5Bh, 0C2h, 04h
    db 00h
?d_00102c80@@YAXXZ ENDP

; ghidra: FUN_00502d00  retail @ 0x00102D00 size 108
public ?d_00102d00@@YAXXZ
?d_00102d00@@YAXXZ PROC
    db 51h, 8Bh, 44h, 24h, 08h, 85h, 0C0h, 56h, 57h, 8Bh, 0F1h, 74h, 0Ah, 0Fh, 0B7h, 40h
    db 04h, 89h, 44h, 24h, 08h, 0EBh, 08h, 0C7h, 44h, 24h, 08h, 00h, 00h, 00h, 00h, 8Bh
    db 4Eh, 04h, 8Bh, 3Dh, 0F4h, 93h, 35h, 01h, 51h, 6Ah, 01h, 8Dh, 54h, 24h, 10h, 6Ah
    db 02h, 52h, 0FFh, 0D7h, 8Bh, 44h, 24h, 20h, 83h, 0C4h, 10h, 85h, 0C0h, 74h, 05h, 83h
    db 0C0h, 08h, 0EBh, 05h, 0B8h, 8Ch, 38h, 07h, 01h, 8Bh, 4Eh, 04h, 0Fh, 0B7h, 54h, 24h
    db 08h, 51h, 6Ah, 01h, 0D1h, 0E2h, 52h, 50h, 0FFh, 0D7h, 83h, 0C4h, 10h, 8Dh, 4Ch, 24h
    db 10h, 0E8h, 6Ah, 54h, 78h, 00h, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00102d00@@YAXXZ ENDP

; ghidra: FUN_00502d90  retail @ 0x00102D90 size 77
public ?d_00102d90@@YAXXZ
?d_00102d90@@YAXXZ PROC
    db 51h, 8Bh, 01h, 85h, 0C0h, 56h, 0C7h, 44h, 24h, 04h, 00h, 00h, 00h, 00h, 74h, 10h
    db 8Bh, 4Ch, 24h, 10h, 39h, 48h, 0Ch, 74h, 1Eh, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F4h
    db 8Bh, 74h, 24h, 0Ch, 68h, 50h, 6Eh, 33h, 01h, 8Bh, 0CEh, 0E8h, 0A0h, 4Dh, 78h, 00h
    db 8Bh, 0C6h, 5Eh, 59h, 0C2h, 08h, 00h, 8Bh, 74h, 24h, 0Ch, 83h, 0C0h, 08h, 50h, 8Bh
    db 0CEh, 0E8h, 8Ah, 4Dh, 78h, 00h, 8Bh, 0C6h, 5Eh, 59h, 0C2h, 08h, 00h
?d_00102d90@@YAXXZ ENDP

; ghidra: FUN_00502e40  retail @ 0x00102E40 size 14
public ?d_00102e40@@YAXXZ
?d_00102e40@@YAXXZ PROC
    db 0C7h, 01h, 44h, 63h, 08h, 01h, 83h, 0C1h, 08h, 0E9h, 0F2h, 4Ah, 78h, 00h
?d_00102e40@@YAXXZ ENDP

; ghidra: FUN_00502e60  retail @ 0x00102E60 size 153
public ?d_00102e60@@YAXXZ
?d_00102e60@@YAXXZ PROC
    db 51h, 56h, 8Bh, 74h, 24h, 0Ch, 8Bh, 06h, 57h, 8Bh, 0F9h, 6Ah, 04h, 8Dh, 4Ch, 24h
    db 0Ch, 51h, 8Bh, 0CEh, 0C6h, 44h, 24h, 10h, 43h, 0C6h, 44h, 24h, 11h, 6Bh, 0C6h, 44h
    db 24h, 12h, 4Dh, 0C6h, 44h, 24h, 13h, 70h, 0FFh, 10h, 8Bh, 16h, 6Ah, 04h, 8Dh, 47h
    db 04h, 50h, 8Bh, 0CEh, 0FFh, 12h, 8Bh, 3Fh, 85h, 0FFh, 74h, 57h, 8Dh, 64h, 24h, 00h
    db 8Bh, 47h, 08h, 85h, 0C0h, 74h, 09h, 8Ah, 48h, 04h, 88h, 4Ch, 24h, 10h, 0EBh, 05h
    db 0C6h, 44h, 24h, 10h, 00h, 8Bh, 16h, 6Ah, 01h, 8Dh, 44h, 24h, 14h, 50h, 8Bh, 0CEh
    db 0FFh, 12h, 8Bh, 47h, 08h, 85h, 0C0h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 0Fh, 0B6h, 4Ch, 24h, 10h, 8Bh, 16h, 51h, 50h, 8Bh, 0CEh, 0FFh, 12h
    db 8Bh, 16h, 6Ah, 04h, 8Dh, 47h, 0Ch, 50h, 8Bh, 0CEh, 0FFh, 12h, 8Bh, 7Fh, 04h, 85h
    db 0FFh, 75h, 0ADh, 5Fh, 5Eh, 59h, 0C2h, 04h, 00h
?d_00102e60@@YAXXZ ENDP

; ghidra: FUN_00502f20  retail @ 0x00102F20 size 342
public ?d_00102f20@@YAXXZ
?d_00102f20@@YAXXZ PROC
    db 83h, 0ECh, 10h, 55h, 56h, 8Bh, 74h, 24h, 1Ch, 57h, 0B0h, 78h, 8Bh, 0E9h, 6Ah, 04h
    db 8Dh, 4Ch, 24h, 10h, 88h, 44h, 24h, 10h, 88h, 44h, 24h, 11h, 88h, 44h, 24h, 12h
    db 88h, 44h, 24h, 13h, 8Bh, 06h, 51h, 33h, 0FFh, 8Bh, 0CEh, 89h, 7Ch, 24h, 18h, 0FFh
    db 10h, 80h, 7Ch, 24h, 0Ch, 43h, 0Fh, 85h, 11h, 01h, 00h, 00h, 80h, 7Ch, 24h, 0Dh
    db 6Bh, 0Fh, 85h, 06h, 01h, 00h, 00h, 80h, 7Ch, 24h, 0Eh, 4Dh, 0Fh, 85h, 0FBh, 00h
    db 00h, 00h, 80h, 7Ch, 24h, 0Fh, 70h, 0Fh, 85h, 0F0h, 00h, 00h, 00h, 8Bh, 16h, 6Ah
    db 04h, 8Dh, 44h, 24h, 1Ch, 50h, 8Bh, 0CEh, 0FFh, 12h, 39h, 7Ch, 24h, 18h, 89h, 7Ch
    db 24h, 14h, 0Fh, 8Eh, 0B2h, 00h, 00h, 00h, 53h, 8Dh, 0A4h, 24h, 00h, 00h, 00h, 00h
    db 6Ah, 10h, 0E8h, 89h, 0EFh, 77h, 00h, 33h, 0FFh, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 0Bh
    db 0C7h, 00h, 44h, 63h, 08h, 01h, 89h, 78h, 08h, 8Bh, 0F8h, 8Bh, 16h, 6Ah, 01h, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CEh, 0FFh, 12h, 8Ah, 44h, 24h, 24h, 84h, 0C0h, 76h, 24h
    db 0Fh, 0B6h, 0C8h, 51h, 8Dh, 4Fh, 08h, 0E8h, 04h, 4Ch, 78h, 00h, 8Bh, 16h, 8Bh, 0D8h
    db 0Fh, 0B6h, 44h, 24h, 24h, 50h, 53h, 8Bh, 0CEh, 0FFh, 12h, 0Fh, 0B6h, 4Ch, 24h, 24h
    db 0C6h, 04h, 19h, 00h, 8Bh, 16h, 6Ah, 04h, 8Dh, 5Fh, 0Ch, 53h, 8Bh, 0CEh, 0FFh, 12h
    db 8Bh, 45h, 00h, 89h, 47h, 04h, 8Bh, 4Dh, 04h, 8Bh, 44h, 24h, 14h, 41h, 89h, 7Dh
    db 00h, 89h, 4Dh, 04h, 8Bh, 1Bh, 3Bh, 0D8h, 76h, 04h, 89h, 5Ch, 24h, 14h, 8Bh, 44h
    db 24h, 18h, 8Bh, 4Ch, 24h, 1Ch, 40h, 3Bh, 0C1h, 89h, 44h, 24h, 18h, 0Fh, 8Ch, 6Dh
    db 0FFh, 0FFh, 0FFh, 85h, 0C9h, 5Bh, 7Eh, 12h, 8Bh, 16h, 8Bh, 0CEh, 0FFh, 52h, 0Ch, 84h
    db 0C0h, 75h, 07h, 0B8h, 01h, 00h, 00h, 00h, 0EBh, 02h, 33h, 0C0h, 88h, 45h, 0Ch, 8Bh
    db 44h, 24h, 10h, 8Bh, 4Dh, 08h, 83h, 0C5h, 08h, 40h, 89h, 44h, 24h, 20h, 3Bh, 0C8h
    db 8Bh, 0C5h, 77h, 04h, 8Dh, 44h, 24h, 20h, 8Bh, 00h, 89h, 45h, 00h, 5Fh, 5Eh, 5Dh
    db 83h, 0C4h, 10h, 0C2h, 04h, 00h
?d_00102f20@@YAXXZ ENDP

; ghidra: FUN_005031b0  retail @ 0x001031B0 size 83
public ?d_001031b0@@YAXXZ
?d_001031b0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 9Bh, 0C9h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 56h, 8Bh, 0F1h, 89h, 74h, 24h, 04h, 0C7h, 06h, 48h
    db 63h, 08h, 01h, 8Dh, 4Eh, 14h, 0C7h, 44h, 24h, 10h, 00h, 00h, 00h, 00h, 0E8h, 5Dh
    db 47h, 78h, 00h, 8Dh, 4Eh, 10h, 0C7h, 44h, 24h, 10h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 4Dh
    db 47h, 78h, 00h, 8Bh, 4Ch, 24h, 08h, 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h
    db 0C4h, 10h, 0C3h
?d_001031b0@@YAXXZ ENDP

; ghidra: FUN_00503450  retail @ 0x00103450 size 238
public ?d_00103450@@YAXXZ
?d_00103450@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0F1h, 0C9h, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 0Ch, 56h, 57h, 6Ah, 00h, 8Bh, 0F1h, 0C7h, 44h
    db 24h, 14h, 00h, 00h, 00h, 00h, 0FFh, 15h, 30h, 8Fh, 35h, 01h, 8Bh, 0Dh, 24h, 0D5h
    db 2Eh, 01h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 40h, 8Bh, 0Eh, 8Bh, 11h, 6Ah
    db 02h, 8Dh, 44h, 24h, 0Ch, 50h, 0FFh, 12h, 8Bh, 46h, 1Ch, 85h, 0C0h, 74h, 0Fh, 0B9h
    db 0FEh, 0FFh, 0FFh, 0FFh, 01h, 48h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 0C7h, 44h
    db 24h, 0Ch, 00h, 00h, 00h, 00h, 66h, 8Bh, 44h, 24h, 08h, 66h, 85h, 0C0h, 0C7h, 44h
    db 24h, 1Ch, 01h, 00h, 00h, 00h, 76h, 3Bh, 0Fh, 0B7h, 0C8h, 51h, 8Dh, 4Ch, 24h, 10h
    db 0E8h, 0Bh, 47h, 78h, 00h, 8Bh, 0Eh, 8Bh, 11h, 8Bh, 0F8h, 0Fh, 0B7h, 44h, 24h, 08h
    db 50h, 57h, 0FFh, 12h, 8Bh, 46h, 1Ch, 85h, 0C0h, 0Fh, 0B7h, 4Ch, 24h, 08h, 74h, 0Ah
    db 29h, 48h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 0Fh, 0B7h, 4Ch, 24h, 08h, 0C6h
    db 04h, 39h, 00h, 8Bh, 74h, 24h, 24h, 8Dh, 54h, 24h, 0Ch, 52h, 8Bh, 0CEh, 0E8h, 4Dh
    db 46h, 78h, 00h, 8Dh, 4Ch, 24h, 0Ch, 0C7h, 44h, 24h, 10h, 01h, 00h, 00h, 00h, 0C6h
    db 44h, 24h, 1Ch, 00h, 0E8h, 17h, 44h, 78h, 00h, 8Bh, 4Ch, 24h, 14h, 5Fh, 8Bh, 0C6h
    db 5Eh, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 18h, 0C2h, 04h, 00h
?d_00103450@@YAXXZ ENDP

; ghidra: FUN_00503840  retail @ 0x00103840 size 113
public ?d_00103840@@YAXXZ
?d_00103840@@YAXXZ PROC
    db 56h, 57h, 6Ah, 1Ch, 8Bh, 0F9h, 0E8h, 0E5h, 0E6h, 77h, 00h, 83h, 0C4h, 04h, 85h, 0C0h
    db 74h, 18h, 0C7h, 00h, 48h, 63h, 08h, 01h, 0C7h, 40h, 10h, 00h, 00h, 00h, 00h, 0C7h
    db 40h, 14h, 00h, 00h, 00h, 00h, 8Bh, 0F0h, 0EBh, 02h, 33h, 0F6h, 8Bh, 44h, 24h, 0Ch
    db 50h, 8Dh, 4Eh, 10h, 0E8h, 17h, 44h, 78h, 00h, 8Bh, 4Ch, 24h, 10h, 51h, 8Dh, 4Eh
    db 14h, 0E8h, 0Ah, 44h, 78h, 00h, 8Bh, 54h, 24h, 14h, 8Bh, 44h, 24h, 18h, 89h, 56h
    db 0Ch, 8Dh, 4Fh, 18h, 89h, 46h, 18h, 8Bh, 01h, 85h, 0C0h, 8Dh, 56h, 04h, 89h, 02h
    db 74h, 03h, 89h, 50h, 08h, 89h, 4Eh, 08h, 5Fh, 89h, 31h, 8Bh, 0C6h, 5Eh, 0C2h, 10h
    db 00h
?d_00103840@@YAXXZ ENDP

; ghidra: FUN_005039c0  retail @ 0x001039C0 size 561
public ?d_001039c0@@YAXXZ
?d_001039c0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0D9h, 0CAh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 28h, 55h, 56h, 57h, 6Ah, 00h, 8Bh, 0F9h, 0C7h
    db 44h, 24h, 34h, 00h, 00h, 00h, 00h, 0FFh, 15h, 30h, 8Fh, 35h, 01h, 8Bh, 0Dh, 24h
    db 0D5h, 2Eh, 01h, 85h, 0C9h, 74h, 05h, 8Bh, 01h, 0FFh, 50h, 40h, 8Bh, 0Fh, 8Bh, 11h
    db 6Ah, 02h, 8Dh, 44h, 24h, 14h, 50h, 0FFh, 12h, 8Bh, 47h, 1Ch, 85h, 0C0h, 74h, 0Fh
    db 0B9h, 0FEh, 0FFh, 0FFh, 0FFh, 01h, 48h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 0Fh
    db 0B7h, 4Ch, 24h, 10h, 51h, 8Dh, 4Ch, 24h, 18h, 0E8h, 9Fh, 0F4h, 0EFh, 0FFh, 66h, 83h
    db 7Ch, 24h, 10h, 00h, 0C7h, 44h, 24h, 3Ch, 01h, 00h, 00h, 00h, 0C7h, 44h, 24h, 1Ch
    db 00h, 00h, 00h, 00h, 0Fh, 86h, 53h, 01h, 00h, 00h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 0Fh, 8Bh, 11h, 6Ah, 04h, 8Dh, 44h, 24h, 24h, 50h, 0FFh, 12h, 8Bh, 47h, 1Ch
    db 85h, 0C0h, 74h, 0Bh, 83h, 40h, 18h, 0FCh, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F5h, 8Bh
    db 44h, 24h, 20h, 8Bh, 0F0h, 0C1h, 0F8h, 08h, 50h, 8Dh, 4Ch, 24h, 1Ch, 51h, 8Dh, 4Fh
    db 04h, 81h, 0E6h, 0FFh, 00h, 00h, 00h, 0E8h, 0DEh, 06h, 0F0h, 0FFh, 8Bh, 44h, 24h, 18h
    db 85h, 0C0h, 0C6h, 44h, 24h, 3Ch, 02h, 74h, 05h, 83h, 0C0h, 08h, 0EBh, 05h, 0B8h, 8Bh
    db 38h, 07h, 01h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 50h, 0E8h, 28h, 73h, 0F3h, 0FFh, 83h
    db 0FEh, 04h, 8Bh, 0E8h, 0Fh, 87h, 20h, 01h, 00h, 00h, 0FFh, 24h, 0B5h, 0F4h, 3Bh, 50h
    db 00h, 8Bh, 0Fh, 8Bh, 11h, 6Ah, 01h, 8Dh, 44h, 24h, 13h, 50h, 0FFh, 12h, 8Bh, 47h
    db 1Ch, 85h, 0C0h, 74h, 0Ah, 0FFh, 48h, 18h, 8Bh, 40h, 04h, 85h, 0C0h, 75h, 0F6h, 8Ah
    db 44h, 24h, 0Fh, 84h, 0C0h, 0Fh, 95h, 0C1h, 51h, 55h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 71h
    db 34h, 0F0h, 0FFh, 0E9h, 81h, 00h, 00h, 00h, 8Bh, 0CFh, 0E8h, 06h, 6Dh, 0F3h, 0FFh, 50h
    db 55h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 00h, 0CFh, 0F0h, 0FFh, 0EBh, 6Dh, 8Bh, 0CFh, 0E8h, 0CEh
    db 0AAh, 0F2h, 0FFh, 51h, 0D9h, 1Ch, 24h, 55h, 8Dh, 4Ch, 24h, 1Ch, 0E8h, 83h, 54h, 0F4h
    db 0FFh, 0EBh, 56h, 8Dh, 54h, 24h, 24h, 52h, 8Bh, 0CFh, 0E8h, 9Ah, 06h, 0F0h, 0FFh, 50h
    db 55h, 8Dh, 4Ch, 24h, 1Ch, 0C6h, 44h, 24h, 44h, 03h, 0E8h, 51h, 74h, 0F2h, 0FFh, 8Dh
    db 4Ch, 24h, 24h, 0C6h, 44h, 24h, 3Ch, 02h, 0E8h, 0F3h, 3Dh, 78h, 00h, 0EBh, 2Ah, 8Dh
    db 44h, 24h, 28h, 50h, 8Bh, 0CFh, 0E8h, 32h, 81h, 0F2h, 0FFh, 50h, 55h, 8Dh, 4Ch, 24h
    db 1Ch, 0C6h, 44h, 24h, 44h, 04h, 0E8h, 1Ch, 46h, 0F2h, 0FFh, 8Dh, 4Ch, 24h, 28h, 0C6h
    db 44h, 24h, 3Ch, 02h, 0E8h, 57h, 46h, 78h, 00h, 8Dh, 4Ch, 24h, 18h, 0C6h, 44h, 24h
    db 3Ch, 01h, 0E8h, 0B9h, 3Dh, 78h, 00h, 8Bh, 44h, 24h, 1Ch, 0Fh, 0B7h, 4Ch, 24h, 10h
    db 40h, 3Bh, 0C1h, 89h, 44h, 24h, 1Ch, 0Fh, 8Ch, 0B3h, 0FEh, 0FFh, 0FFh, 8Bh, 44h, 24h
    db 14h, 85h, 0C0h, 8Bh, 74h, 24h, 44h, 89h, 06h, 74h, 03h, 66h, 0FFh, 00h, 8Dh, 4Ch
    db 24h, 14h, 0C7h, 44h, 24h, 30h, 01h, 00h, 00h, 00h, 0C6h, 44h, 24h, 3Ch, 00h, 0E8h
    db 0B1h, 08h, 0F1h, 0FFh, 8Bh, 4Ch, 24h, 34h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 64h, 89h, 0Dh
    db 00h, 00h, 00h, 00h, 83h, 0C4h, 34h, 0C2h, 04h, 00h, 68h, 04h, 00h, 1Eh, 01h, 8Dh
    db 54h, 24h, 30h, 52h, 0C7h, 44h, 24h, 34h, 05h, 00h, 0ADh, 0DEh, 0E8h, 0Fh, 31h, 8Fh
    db 00h
?d_001039c0@@YAXXZ ENDP

; ghidra: FUN_00503ca0  retail @ 0x00103CA0 size 126
public ?d_00103ca0@@YAXXZ
?d_00103ca0@@YAXXZ PROC
    db 8Bh, 01h, 85h, 0C0h, 53h, 55h, 56h, 57h, 74h, 6Bh, 8Bh, 4Ch, 24h, 14h, 8Bh, 31h
    db 89h, 74h, 24h, 14h, 0EBh, 0Ah, 8Bh, 74h, 24h, 14h, 8Dh, 9Bh, 00h, 00h, 00h, 00h
    db 8Bh, 48h, 08h, 85h, 0C9h, 74h, 06h, 0Fh, 0B7h, 69h, 04h, 0EBh, 02h, 33h, 0EDh, 85h
    db 0C9h, 8Dh, 79h, 08h, 75h, 05h, 0BFh, 8Bh, 38h, 07h, 01h, 85h, 0F6h, 74h, 09h, 0Fh
    db 0B7h, 5Eh, 04h, 83h, 0C6h, 08h, 0EBh, 07h, 33h, 0DBh, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh
    db 0DDh, 8Bh, 0CBh, 7Ch, 02h, 8Bh, 0CDh, 33h, 0D2h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0D2h, 83h
    db 0DAh, 0FFh, 85h, 0D2h, 75h, 08h, 2Bh, 0DDh, 8Bh, 0D3h, 85h, 0D2h, 74h, 09h, 8Bh, 40h
    db 04h, 85h, 0C0h, 75h, 0A1h, 33h, 0C0h, 5Fh, 5Eh, 5Dh, 5Bh, 0C2h, 04h, 00h
?d_00103ca0@@YAXXZ ENDP

; ghidra: FUN_00503d60  retail @ 0x00103D60 size 100
public ?d_00103d60@@YAXXZ
?d_00103d60@@YAXXZ PROC
    db 53h, 8Bh, 5Ch, 24h, 08h, 56h, 57h, 53h, 8Bh, 0F1h, 0E8h, 0Bh, 1Bh, 0F1h, 0FFh, 33h
    db 0FFh, 3Bh, 0C7h, 74h, 09h, 8Bh, 40h, 0Ch, 5Fh, 5Eh, 5Bh, 0C2h, 04h, 00h, 6Ah, 10h
    db 0E8h, 0ABh, 0E1h, 77h, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h, 0Bh, 0C7h, 00h, 44h, 63h
    db 08h, 01h, 89h, 78h, 08h, 8Bh, 0F8h, 8Bh, 46h, 08h, 89h, 47h, 0Ch, 8Bh, 56h, 08h
    db 42h, 53h, 8Dh, 4Fh, 08h, 89h, 56h, 08h, 0E8h, 0E3h, 3Eh, 78h, 00h, 8Bh, 0Eh, 89h
    db 4Fh, 04h, 8Bh, 46h, 04h, 40h, 89h, 3Eh, 89h, 46h, 04h, 8Bh, 47h, 0Ch, 5Fh, 5Eh
    db 5Bh, 0C2h, 04h, 00h
?d_00103d60@@YAXXZ ENDP

; ghidra: FUN_005041f0  retail @ 0x001041F0 size 216
public ?d_001041f0@@YAXXZ
?d_001041f0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 58h, 0CBh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 8Bh, 44h, 24h, 18h, 53h, 56h, 57h, 8Bh
    db 0F1h, 50h, 8Dh, 4Ch, 24h, 28h, 0E8h, 0A5h, 49h, 78h, 00h, 8Dh, 4Ch, 24h, 24h, 51h
    db 33h, 0FFh, 8Dh, 4Eh, 08h, 89h, 7Ch, 24h, 20h, 0E8h, 76h, 0A8h, 0F3h, 0FFh, 8Dh, 4Ch
    db 24h, 24h, 89h, 44h, 24h, 0Ch, 0C7h, 44h, 24h, 1Ch, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0FDh
    db 36h, 78h, 00h, 6Ah, 10h, 0E8h, 0E6h, 0DCh, 77h, 00h, 83h, 0C4h, 04h, 3Bh, 0C7h, 74h
    db 08h, 0C7h, 00h, 18h, 63h, 08h, 01h, 8Bh, 0F8h, 8Bh, 56h, 18h, 8Bh, 1Dh, 0F4h, 93h
    db 35h, 01h, 89h, 57h, 04h, 8Bh, 44h, 24h, 0Ch, 89h, 7Eh, 18h, 89h, 47h, 08h, 8Bh
    db 4Eh, 04h, 51h, 6Ah, 01h, 8Dh, 54h, 24h, 14h, 6Ah, 04h, 52h, 0FFh, 0D3h, 8Bh, 46h
    db 04h, 50h, 6Ah, 01h, 8Dh, 4Ch, 24h, 40h, 6Ah, 02h, 51h, 0FFh, 0D3h, 8Bh, 56h, 04h
    db 52h, 0FFh, 15h, 0ECh, 93h, 35h, 01h, 89h, 47h, 0Ch, 8Bh, 46h, 04h, 50h, 6Ah, 01h
    db 8Dh, 4Ch, 24h, 3Ch, 6Ah, 04h, 51h, 0C7h, 44h, 24h, 44h, 0FFh, 0FFh, 00h, 00h, 0FFh
    db 0D3h, 8Bh, 4Ch, 24h, 48h, 83h, 0C4h, 34h, 5Fh, 5Eh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 14h, 0C2h, 08h, 00h
?d_001041f0@@YAXXZ ENDP

; ghidra: FUN_00504750  retail @ 0x00104750 size 11
public ?d_00104750@@YAXXZ
?d_00104750@@YAXXZ PROC
    db 0C7h, 05h, 5Ch, 0D8h, 2Eh, 01h, 0FFh, 07h, 00h, 00h, 0C3h
?d_00104750@@YAXXZ ENDP

; ghidra: FUN_005048c0  retail @ 0x001048C0 size 381
public ?d_001048c0@@YAXXZ
?d_001048c0@@YAXXZ PROC
    db 51h, 8Bh, 41h, 24h, 83h, 0F8h, 04h, 0Fh, 87h, 60h, 01h, 00h, 00h, 0FFh, 24h, 85h
    db 40h, 4Ah, 50h, 00h, 8Bh, 41h, 0Ch, 8Dh, 50h, 01h, 89h, 51h, 0Ch, 3Bh, 41h, 10h
    db 8Bh, 44h, 24h, 0Ch, 72h, 12h, 0C7h, 41h, 24h, 01h, 00h, 00h, 00h, 0C7h, 41h, 0Ch
    db 00h, 00h, 00h, 00h, 8Bh, 09h, 89h, 08h, 0C7h, 00h, 00h, 00h, 00h, 00h, 0B0h, 01h
    db 59h, 0C2h, 08h, 00h, 8Bh, 51h, 14h, 0DBh, 41h, 14h, 85h, 0D2h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D9h, 41h, 04h, 8Bh, 54h
    db 24h, 0Ch, 0D8h, 21h, 0DEh, 0F1h, 0D8h, 02h, 0D9h, 12h, 0D8h, 59h, 04h, 0DFh, 0E0h, 0F6h
    db 0C4h, 01h, 75h, 0Ch, 8Bh, 41h, 04h, 89h, 02h, 0C7h, 41h, 24h, 02h, 00h, 00h, 00h
    db 0B0h, 01h, 59h, 0C2h, 08h, 00h, 8Bh, 51h, 18h, 0DBh, 41h, 18h, 85h, 0D2h, 7Dh, 06h
    db 0D8h, 05h, 58h, 53h, 07h, 01h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 0D9h, 0DFh, 0E0h
    db 0F6h, 0C4h, 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D9h, 41h, 04h
    db 8Bh, 54h, 24h, 0Ch, 0D8h, 61h, 08h, 0DEh, 0F1h, 0D8h, 2Ah, 0D9h, 12h, 0D8h, 59h, 08h
    db 0DFh, 0E0h, 0F6h, 0C4h, 41h, 7Ah, 13h, 8Bh, 41h, 08h, 89h, 02h, 0C7h, 41h, 24h, 03h
    db 00h, 00h, 00h, 0C7h, 41h, 0Ch, 00h, 00h, 00h, 00h, 0B0h, 01h, 59h, 0C2h, 08h, 00h
    db 8Bh, 41h, 0Ch, 8Dh, 50h, 01h, 89h, 51h, 0Ch, 3Bh, 41h, 1Ch, 72h, 07h, 0C7h, 41h
    db 24h, 04h, 00h, 00h, 00h, 8Bh, 41h, 08h, 8Bh, 4Ch, 24h, 0Ch, 89h, 01h, 0B0h, 01h
    db 59h, 0C2h, 08h, 00h, 8Bh, 51h, 20h, 0DBh, 41h, 20h, 85h, 0D2h, 7Dh, 06h, 0D8h, 05h
    db 58h, 53h, 07h, 01h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 0D9h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 75h, 08h, 0DDh, 0D8h, 0D9h, 05h, 34h, 53h, 07h, 01h, 0D8h, 79h, 08h, 8Bh, 54h
    db 24h, 0Ch, 0D8h, 2Ah, 0D9h, 12h, 0D8h, 1Dh, 50h, 53h, 07h, 01h, 0DFh, 0E0h, 0F6h, 0C4h
    db 41h, 7Ah, 14h, 0C7h, 02h, 00h, 00h, 00h, 00h, 0C7h, 41h, 24h, 05h, 00h, 00h, 00h
    db 0C7h, 41h, 0Ch, 00h, 00h, 00h, 00h, 0B0h, 01h, 59h, 0C2h, 08h, 00h, 8Bh, 44h, 24h
    db 0Ch, 0C7h, 00h, 00h, 00h, 00h, 00h, 32h, 0C0h, 59h, 0C2h, 08h, 00h
?d_001048c0@@YAXXZ ENDP

; ghidra: FUN_00504ac0  retail @ 0x00104AC0 size 98
public ?d_00104ac0@@YAXXZ
?d_00104ac0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0BBh, 0CBh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 58h, 02h, 00h, 00h, 0E8h, 50h, 0D4h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 6Eh, 50h, 0F3h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104ac0@@YAXXZ ENDP

; ghidra: FUN_00504b40  retail @ 0x00104B40 size 98
public ?d_00104b40@@YAXXZ
?d_00104b40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0DBh, 0CBh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 0DCh, 03h, 00h, 00h, 0E8h, 0D0h, 0D3h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 24h, 0B2h, 0F1h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104b40@@YAXXZ ENDP

; ghidra: FUN_00504bc0  retail @ 0x00104BC0 size 98
public ?d_00104bc0@@YAXXZ
?d_00104bc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 0FBh, 0CBh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 80h, 02h, 00h, 00h, 0E8h, 50h, 0D3h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 3Fh, 5Bh, 0F3h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104bc0@@YAXXZ ENDP

; ghidra: FUN_00504c40  retail @ 0x00104C40 size 98
public ?d_00104c40@@YAXXZ
?d_00104c40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 1Bh, 0CCh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 80h, 02h, 00h, 00h, 0E8h, 0D0h, 0D2h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 23h, 0F2h, 0F2h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104c40@@YAXXZ ENDP

; ghidra: FUN_00504cc0  retail @ 0x00104CC0 size 98
public ?d_00104cc0@@YAXXZ
?d_00104cc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 3Bh, 0CCh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 10h, 03h, 00h, 00h, 0E8h, 50h, 0D2h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 5Bh, 73h, 0F0h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104cc0@@YAXXZ ENDP

; ghidra: FUN_00504d40  retail @ 0x00104D40 size 98
public ?d_00104d40@@YAXXZ
?d_00104d40@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 5Bh, 0CCh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 6Ch, 02h, 00h, 00h, 0E8h, 0D0h, 0D1h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 3Bh, 72h, 0F0h, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104d40@@YAXXZ ENDP

; ghidra: FUN_00504dc0  retail @ 0x00104DC0 size 98
public ?d_00104dc0@@YAXXZ
?d_00104dc0@@YAXXZ PROC
    db 6Ah, 0FFh, 68h, 7Bh, 0CCh, 0FFh, 00h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 51h, 68h, 88h, 02h, 00h, 00h, 0E8h, 50h, 0D1h, 77h, 00h
    db 83h, 0C4h, 04h, 89h, 04h, 24h, 85h, 0C0h, 0C7h, 44h, 24h, 0Ch, 00h, 00h, 00h, 00h
    db 74h, 1Dh, 8Bh, 4Ch, 24h, 14h, 51h, 8Bh, 0C8h, 0E8h, 0D2h, 0ECh, 0EFh, 0FFh, 8Bh, 4Ch
    db 24h, 04h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h, 04h, 00h, 8Bh
    db 4Ch, 24h, 04h, 33h, 0C0h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 10h, 0C2h
    db 04h, 00h
?d_00104dc0@@YAXXZ ENDP
_TEXT ENDS
END
