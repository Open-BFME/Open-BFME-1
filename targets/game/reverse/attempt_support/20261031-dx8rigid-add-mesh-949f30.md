# DX8RigidFVFCategoryContainer::Add_Mesh 0x00949F30 (1008 B): s513 lead

Donor: open-bfme-2 b5a7b8290 `Code/Libraries/Source/WWVegas/WW3D2/DX8RendererAddMesh.cpp`, a
closure unit holding Add_Mesh plus every receiver of its local `Vertex_Split_Table` (ctor,
Peek_Texture/Shader/Material, Generate_Texture_Categories, Insert_To_Texture_Category,
DX8TextureCategoryClass::Add_Mesh). The donor records that Add_Mesh only schedules like
retail when all of them are visible in the same unit.

Measured: the donor unit, with its cl line replaced by
`/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
/Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep` and placed in
game/Libraries/Source/WWVegas/WW3D2/, probes `?Add_Mesh@DX8RigidFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z`
at 930/1008 B, shape 0.841 (old bank 0.25). /G6 or explicit /O flags change nothing.
`bfme2_sweep.py compile` aborts with "header dependency set changed during trial".

BFME 1 differences read from the retail body (fix these first):
- DX8FVFCategoryContainer fields are 8 bytes later than the donor's views: FVF +0xE0,
  sorting +0xEC, vertex_buffer +0xF0, used_vertices +0xF4.
- Buffers: `new SortingVertexBufferClass(vb_size)` (0x0091DFD0, ctor takes unsigned short) and
  `new DX8VertexBufferClass(FVF, vb_size, usage, 0)` (0x0091F2F0), not the donor's BfmeDynamic*VB.
  Caps global `BfmeCurrentCaps` 0x01340578 (+0x13B npatches), NPatches level 0x012D6D8C.
- The UV stage count is Zero Hour's `if ((FVF&D3DFVF_TEXn)==D3DFVF_TEXn) uvcount=n;` cascade for
  n = 1..8 (retail +0x29B..+0x330), not the donor's `(FVF>>8)&15`.

Landing then needs the merge the donor describes: BFME 1 matches those callees in separate units
(VertexSplitTableConstructorBFME.cpp, DX8FVFCategoryContainerGenerateTextureCategoriesBFME.cpp,
DX8FVFCategoryContainerInsertToTextureCategory.cpp, DX8TextureCategoryAddMesh.cpp, dx8renderer.cpp
Peek_*), so test first whether BFME 1 really needs them visible (declare-only probe) before
`bfme2_sweep.py rehome`.

## Second pass (same session)
`20261031-dx8rigid-add-mesh-949f30.cpp.txt` is the donor unit with the BFME 1 fixes above applied
(two container fields `unknown_D0`/`unknown_D4` before index_buffer as in
DX8FVFCategoryContainerGenerateTextureCategoriesBFME.cpp, SortingVertexBufferClass /
DX8VertexBufferClass constructors, the TEX1..TEX8 cascade with `int` uvcount/j). Copy it to
game/Libraries/Source/WWVegas/WW3D2/ to probe. Result: 1058/1008 B, shape 0.838. Remaining:
retail keeps uvcount in [esp+0x10] and stores each cascade value there (ours keeps EAX); retail
tests `byte [this+0xE0] & 0x80` directly (ours caches this in EDI and loads BL); about 50 bytes
more code in ours, not yet located. The visible-callee question is still untested.

## Third pass: shape 1.000
With MeshModelClass::CurMatDesc at +0x9C and MeshMatDescClass without the donor's +0x0C field
(UV[8] at +0x0C, UVSource +0x2C, ColorArray[2] +0x4C/+0x50; the UV getter has no create-flag
test), the `.cpp.txt` unit probes **1011/1008 B, shape 1.000** (allocation only).
Visibility measured by deleting bodies (build/a1s513/amvis.py in that session): every one of the
Vertex_Split_Table ctor, Peek_Texture, Peek_Shader, DX8TextureCategoryClass::Add_Mesh,
Insert_To_Texture_Category and Generate_Texture_Categories must stay defined in the unit (any
missing one: 1047 B, shape 0.910); DX8PolygonRendererClass::Set_Vertex_Index_Range is optional.
So landing needs those six rows rehomed into this unit (their current units:
VertexSplitTableConstructorBFME.cpp, dx8renderer.cpp, DX8TextureCategoryAddMesh.cpp,
DX8FVFCategoryContainerInsertToTextureCategory.cpp,
DX8FVFCategoryContainerGenerateTextureCategoriesBFME.cpp), verifying each moved row, plus the
3-byte frame-slot residue in Add_Mesh itself.
