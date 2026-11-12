# 0x00948BD0 Render@DX8TextureCategoryClass — attempt 2026-11-12 (muse-spark)

Bank re-verified: ours=4397 retail=4397, 36 non-reloc diffs, first at +0x683.
Variants tried: (A) native DX8Wrapper::Set_Index_Buffer_Index_Offset — identical
36 diffs; (B) named sphere const-ref local — regressed to 4391B/1905 diffs
(frame shrink, do not repeat).

## New evidence (not in earlier verdicts)

Matched twin `?Render_Sorted@DX8PolygonRendererClass@@QAEXHABVSphereClass@@@Z`
at 0x00945740 (79B, in dx8renderer.cpp via dx8polygonrenderer.h inline) proves
the true source shape for the sorted block:

- global word at 0x0134112C = render_state.index_base_offset (+0x26C into
  DX8Wrapper::render_state @ 0x01340EC0); header already declares it
  `unsigned short` (dx8wrapper.h:202). No header change needed.
- `or dword ptr [0x133f49c],0x20000` DIRECT in the 79B twin vs mov/or/mov in
  the 0x00948BD0 inline expansion: same source, allocator-context codegen.
- Insert_Triangles is `SAXABVSphereClass@@GGGG` — G = unsigned short params,
  so dword fields index_offset/min_vertex/vertex_range compile to 16-bit
  loads (`xor eax,eax; mov ax,[reg+N]`). Fields stay `unsigned`; do NOT narrow
  them (matched Render 0x0092CB30 constrains the layout).
- 79B prologue picks EDX for the global word; the big-body inline picks ECX.
  Same source, different home register: pure inlining-context allocator
  choice. The downstream cascade (ebp-vs-ecx sphere home, ebx-vs-esi renderer
  home, mul-magic vs reordered word loads) all follows from that first pick.
- Native arg order confirmed: (sphere, index_offset, index_count/3,
  min_vertex_index, vertex_index_range) == retail ([ebx+0x10]w,
  [ebx+0x18]/3, [ebx+0x1c]w, [ebx+0x20]w) with renderer = ebx = [esp+0x14].

## Next leads (untried)

1. Shape lever "named count local" applied to `index_count/3` INSIDE the big
   body only (v3/v4 tried polygon_count hoist in the helper; try naming it at
   the Render_Sorted call site with the native statement order verbatim).
2. Copy the dx8polygonrenderer.h Render_Sorted inline VERBATIM (native class
   via header, native arg names) instead of the TU-local class+helper; the
   TU-local copies may perturb the allocator even when semantically identical.
   Requires reconciling native MeshClass view — check class_contract first.
3. Register-mirror lever: reorder local DEFINITIONS in Render() to retail's
   first-use order so the global word lands in ECX and sphere in EBP. The
   sphere home (ebp) is the tell: something in retail's flow keeps a
   callee-saved home alive across the block; find which stash temporary
   unnecessarily occupies ebp/ebx/si slots before +0x683.
