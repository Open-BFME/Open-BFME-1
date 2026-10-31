# Path::computePointOnPath 0x003FD7D0 (940 B) — s512 bank

Link queue #5 blocker: `?computePointOnPath@Path@@QAEXPAVObject@@PAVRva001B7200Locomotor@@PAURva001B7200PathPoint@@_N@Z`
(ILT 0x8A9E) has no definition; the body is still the gen dump `?d_003fd7d0`. Landing a C++ body unblocks
RunReadyAction0027A7A0.cpp (and the locomotor resync TU).

Bank: `targets/game/reverse/attempts/0x003fd7d0.cpp` (s512, compiled with /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-).
Shape 0.953 (probe), 950 vs 940 B. Supersedes the 0.62 GPT-5 bank (different control flow).

## Facts from BFME 1 retail (dis_retail 0x3FD7D0 940)
- thiscall ret 0x10; Object* unused; out record 36 B {Real dist; Coord3D pos; Coord3D next; int layer; int waypoint}.
- Path layout +4 m_path, +8 m_pathTail, +0x10 cursor node, +0x14 cursor pos, +0x20 cursor dist (as PathAdvanceCachedPoint.cpp).
- distance = 40, or getPreferredHeight() clamped: `<= 0.1f` -> update ? 0.1f : 1.0f.
- Portal via TheTerrainLogic vslot +0x80(next->m_waypointID): type 1 -> `if (seg-t > d) d = seg-t-0.001` (double const),
  type 3 -> scale = seg/(fabs(dz)+1) clamped (>1 -> 1, <0.5 -> *0.85). Matches the BFME 2 PeekAlongPath donor shape
  (inputs/reference/open-bfme-2 Code/GameEngine/Source/GameLogic/Pathfinder/rva003642DFRva003642DFFarm.cpp); ea_evidence
  names 0x3FD7D0 `Path::PeekAlongPath` (wb2) — the ledger/pin name was kept because callers link against it.
- update block: cursor = node, dist = t, pos = out->pos, TheAI->(+0xc)->set(out->pos) (0x3D5C60).

## Levers found (each measured)
- `Coord3D *outPosition = &out->m_coord04` used for x,y,z in the found branch + tail + update gives retail's
  ebx=outPos / edi=this allocation and the [esp+24] this spill (0.855 -> 0.892).
- Tail: by-value `Coord3D delta(*outPosition)` with a user copy ctor + in-place `sub()` + inline `length()` reproduces the
  fld [ebx] / int-copied z / fld [ebx+4] forwarding.
- Retail's main loop is NOT rotated (back-edge jmps to `test ecx,ecx`, node reloaded from [esp+14]). Only a compound
  condition with a foldable first term (`searching && node`, `out && node`, `this && node`) un-rotates it; `node && x`,
  for(;;)+break, goto loops, continue, do/while, found-flag if/else all stay rotated. Un-rotation fixes every frame slot.
- Not effective: volatile along/segLen (fsubr order), /O1 /Os /Og-only, /G5 /G6 (no change), /G7 (drops loop alignment
  but uses `cmp byte ptr [ebp+14h],0`), tail-recursive forceinline helper (frame changes completely), Coord3D::zero().

## Remaining mismatch (h0 variant)
1. Constant 0 held in EDX from the out-record clear to the loop head (`cmp ecx,edx`, two extra `xor edx,edx`);
   retail clears with ECX and tests `test ecx,ecx`. Caused by the `&&` loop condition. Need another un-rotating form.
2. `lea ebx,[esi+4]` hoisted above the clear (retail after the z store).
3. Found branch: retail loads dir.y*d before storing x (fxch); ours sequential.
4. Final walk loop aligned (`lea esp,[esp]`); retail no alignment.
