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
