# 0x006DC0D0 road-buffer render helper — retail layout map + upgraded draft

Task-5 dependency of `?d_006dc970@@YAXXZ` (0x006DC970, 5761 B). The helper's
only caller passes `(mesh, camera, index, set-iterator)` with ret 16; ABI
`?rva006DC0D0@Rva006DED60RoadBuffer@@QAEXPAVMeshClass@@PAURva006DC0D0RenderView@@HAAU?$_Rb_tree_iterator@...`
(receiver `Rva006DED60RoadBuffer`, proven by ctor 0x006DED60/dtor 0x006DEA80).

## Retail-derived layout facts (from `dis_retail.py`, new this pass)

- Mesh view: model pointer at **mesh+0xC8** (prior draft used +0xD8).
  Retail reloads `[edi+0xC8]` before each model access (+007d/+0094/+00c6).
- Model fields: positions array at **+0x30** (`[ecx+0xC]` = data),
  indices array at **+0x2C**, nverts scalar at **+0x28** (kept in ebp across
  the UV/color calls, spilled to `[esp+0x50]`), ntris scalar at **+0x24**
  (spilled to `[esp+0x5c]`), materials at **+0x9C**.
- `Rva006DED60RoadBuffer::sets[index]` (sets base +0x94, 12 B per set):
  retail takes its address once (`lea` + store to `[esp+0x18]`) and reuses it
  for the end-check, both `size()` calls and the traversal. Draft now holds
  `Rva006DC0D0Set &set = sets[index];`.
- Call sequence (all verified against retail bytes): null guards →
  `Get_UV_Array_By_Index(0,false)` (ILT 0x0001D179) → uv to `[esp+0x88]` →
  `Get_Color_Array(0,false)` (ILT 0x0002F8E2) → colors to `[esp+0x8c]` →
  `materialInfo()` = mesh vftable slot 84 (`call [eax+0x150]`) →
  `Get_Emissive(&emissive)` with emissive zeroed at `[esp+0x6c/70/74]` →
  refcount release → light = emissive.
- Prologue/frame: retail `sub esp,0x10C`, saves ebx+esi(+edi/ebp later),
  `this` in esi, zero in ebx. Ours: `sub esp,0x104`, `this` in edi.

## Probes this pass (all vs 1758 B retail, 23 relocs)

- Bank re-verified: 1645 B / 1455 non-reloc diffs / shape 0.793.
- iter1 (+0xC8 model, `&set` local): 1642 B / 1455 diffs / shape 0.801.
- iter2 (split MeshView/RenderView types): identical 1642 / 1455 / 0.801 —
  codegen-neutral, kept for clarity. Banked as preferred stash (byte score
  unchanged at 0.17; shape +0.008 with corrected offsets).

## Residue and next leads (not tried)

- The whole-body register/frame allocation: retail's esi/ebx choice and the
  8-byte frame gap persist through every spelling tried. The first decision
  point is the prologue; `shape_family_levers.py --families register,frame`
  + `shape_search.py` is the mechanical next step, then `/FAsc` listing
  comparison of the prologue live ranges.
- Unverified: `Rva006DC0D0RenderView` bytes above +0xC8 (gap48 now 0x70 is a
  lower bound from the model pointer, not a witnessed extent); the
  `position()` vptr[20] and `materialInfo()` vptr[84] slots (kept from the
  prior draft, consistent with `call [eax+0x150]`).
- Raw trials under `build/rd970/` (untracked scratch, safe to delete).
