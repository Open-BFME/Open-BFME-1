# Handoff: ?Render@DX8TextureCategoryClass@@QAEXXZ (0x00948BD0, 4397B)

Date: 2026-10-28. Bank `targets/game/reverse/attempts/0x00948bd0.cpp`
(0.9918) re-verified this session: 4397/4397B, 36 non-reloc diffs in the
sorted-render argument preparation (+0x683..+0x6CA), its join jump (+0x6D3),
and the task reload (+0xFD9..+0xFE9). Shape 0.996.

## Donor lever found and tested (required reference check)

- `../Open-BFME-2` rev 64ea363549,
  `Code/Libraries/Source/WWVegas/WW3D2/DX8PolygonRendererClass_Render_Sorted.cpp`:
  BFME2's own byte-exact Render_Sorted keeps `vertex_range`, `min_vertex`,
  `polygon_count = IndexCount/3`, `index_offset` live as named locals in
  right-to-left argument evaluation order, which reproduces BFME2 retail's
  ECX/ESI/EBX allocation.
- Port attempt 1 (all four locals, build/scratch_948bd0_v2.cpp): REFUTED —
  4373B (24B short), 2732 diffs, frame shift. The donor TU context
  (out-of-line, ScopedRenderEvent) does not transfer to BFME1's inline.
- Port attempt 2 (single local `unsigned polygon_count = field18/3`,
  build/scratch_948bd0_v3.cpp): LATERAL — still 36 diffs, but the
  `mul [ebx+0x18]` divide site now matches structurally; residue is the
  EBX/ESI task-pointer allocation in +0x683..+0x6CA plus the task reload.
  Reproduce with the one-line hoist in the TU-local `Render_Sorted`.
- Port attempt 3 (v3 + swap `renderer`/`mesh` declaration order, v4):
  no help, same 36 diffs.

## Remaining mismatch (v3 basis)

- Retail keeps the task/renderer pointer in EBX (`mov ebx,[esp+0x14]`,
  `mul [ebx+0x18]`, `mov ebp,eax`, `xor ecx,ecx`); ours uses ESI/EDX/EAX
  (`mov esi,[esp+0x14]`, `movzx edx,...`, `mov ecx,eax`, `xor eax,eax`).
- Stash header notes the TU-local views that may matter: category/texture
  device slot +0x10C, task pool lock at +0x10, skin-transform pointer pair
  at mesh +0x314 with inverse transform.

## Next leads (untried)

- Vary the loop-pointer declarations at stash lines 269-274 (`prt`,
  `last_prt`, `renderer`, `mesh` order/lifetimes) to push the task pointer
  into EBX across the sorted region.
- Compare BFME2's `dx8renderer.cpp` Render loop (same rev) for the task
  loop spelling; only Render_Sorted was ported so far.
- `/FAsc` comparison of the +0x683 region register homes.
