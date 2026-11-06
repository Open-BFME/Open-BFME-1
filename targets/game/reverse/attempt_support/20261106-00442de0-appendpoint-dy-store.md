# 0x00442DE0 appendPoint (397 B) — workflow handoff 2026-11-05

Symbol probed: `?appendPoint@Rva00442DE0Owner@@QAEXURva00442DE0Point@@@Z`
Toolchain: MSVC 7.1, bank cl line `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
/D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWMath` (probe adds /O2).
Best candidate: `build/wf/00442de0/base.cpp` (= banked
`targets/game/reverse/attempts/0x00442de0.cpp`), reproduces 397/397 B, 6
non-reloc diffs, all 7 relocs aligned. No improvement found this session.

## Residue (unchanged)
```
retail                              ours
+60 mov edx,ebx                     mov edx,ebx
+62 sub edx,eax                     sub edx,eax
+64 mov [esp+28],edx   (dy store)   fstp [esp+14]   (delta.x)
+68 fstp [esp+14]                   mov [esp+28],edx
+6c fild [esp+28]                   fild [esp+28]
```

## New observation (most useful lead)
In every scalarized spelling the dy store is glued directly before its
`fild` (it behaves like a post-scheduling spill). Retail's early store is what
VC7.1 emits when the y-difference is a *memory-homed* variable stored at its
definition. Reproduced that store order with
`Rva00442DE0Point difference = pt; difference.x -= lastX; difference.y -= lastY;`
(also `= pos`, ICoord2D copy-ctor `difference(pt)`, or `-= last.x`): the
aggregate copy of the by-value point keeps `difference` coalesced with the
`pos` argument slots [24]/[28], and `mov [28],edx` lands before `fstp [14]`.
But VC7.1 then reloads `difference.y` from `[esp+28]` (`mov edx,[esp+28]`,
hoisted to +4e) instead of `mov edx,ebx`: 399 B, shape 0.975, plus `mov ecx,
TheMouse`/`mul` shifted. x still comes from EDI. Variant: `build/wf/00442de0/v/s1.cpp`.
Next agent: find a spelling that memory-homes difference.y but sources it
from the pt.y register (EBX).

## Ruled out this session (all re-measured on the 6-diff bank)
- (b/c) difference forms: agg init, field assigns, scalars dx/dy, int[2],
  address-taken via pointer/reference/inline helper (const ref and pointer),
  ICoord2D with inline ctor(int,int)/default+fields (7, y temp back to [24]),
  operator- returning by value (15/19), dead `= pt` copy then plain assigns
  (6), param written in place `pos.x = pt.x - lastX` (6), `pos.x -= ...` (401).
- dx/dy reused for the clamp result (7) or difference reused (398).
- delta construction: int ctor, float ctor, set(), set via ctor, zero()+fields
  (393), `Coord3D(0,0,0)`+fields (393), copy-init from temporary (6),
  operator= from temporary (395), float temps in ctor (6).
- distance: y*y first (10, flips load order only), double root, sqrtf, lenSq
  local, +z*z term — all 6.
- tolerance: int local, unsigned local, `/3u`, real Mouse member view (6);
  placed before last/difference/ctor (frame changes, 94-117).
- lastX/lastY: declared together/after, at function scope (6); y-first (398).
- scope: difference/delta/lastX at function scope (6).
- normalize: undeclared body (38, z store moves before mul); non-noinline
  visible body (6).
- invisible-normalize model with z stored after tolerance (393/52).
- volatile diagnostics (not candidates): volatile dy keeps store before fstp
  but adds reload (405-413).
- flags (diagnostic only, no sibling justification): /G5 /G6 /GB /Ob1 /Ob2
  /Ot /Og /Oa /Ow /Ox /Gy /GX- /DWIN32 inert; /G7 /Op /Oy- /Oi- /QIfist
  /arch:SSE much worse.
- 30-combo random grid over last-access x difference x ctor x sqrt x tolerance
  spellings: best 6.
- s1-family follow-ups: copy before `last` (399), `w4` default+assign pt
  (399), re-reading `difference.y = pt.y` before `-=` (405), `pt = pos`
  after delta (401). The EBX-vs-[esp+28] source for dy stays unsolved.
