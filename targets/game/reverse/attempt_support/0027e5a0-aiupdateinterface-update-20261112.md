# 0x0027E5A0 AIUpdateInterface::update (843 B) -- 2026-11-12 handoff

Bank: `targets/game/reverse/attempts/0x0027e5a0.cpp` (meant to live at
`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceUpdate.cpp`,
`// cl: /DNDEBUG /MD /EHsc`). Probe: ours 845 B vs retail 843 B, 28 relocs,
normalized shape 0.992, 2 structural differences. t=~110 min, model=claude-opus-5-5.

## Identity (BFME 1 facts)
- `ilt_oracle check ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ 0x0027E5A0`
  -> CONFIRMED (exact); the lift name `??1AnimalAIUpdate@@UAE@XZ` -> CONTRADICTED.
- symbols.csv already pins the name at ILT 0x00028772; the matched
  DeployStyleAIUpdate::update (DeployStyleAIUpdate_update_BFME.cpp) calls
  `AIUpdateInterface::update()`. Receiver = +0x10 UpdateModuleInterface subobject.
- Boundary: ledger 843 B, `ret` at +0x34A.

## Donor (BFME 2 shape, not BFME 1 proof)
Open-BFME-2 76f0baefa6 `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceUpdate.cpp`
(BFME 2 0x0026E267, 850 B). Same skeleton: stored-command replay through
AICommandParms + AICommandParmsStorage::reconstitute + aiDoCommand, quick/main
update split, module-data +0x54 sync call, 0x0027BF60 sleep clamp, owner range
model condition + chooseLocomotorSet (vtable +0x1FC). BFME 1 drops the
orders-manager refresh, the EH status scope (status bit 71 is set/cleared by two
plain BitFlags<86> temporaries), the lone-unit/0x1BA logic and the script-tracker/team tail.

## Layout read from retail (structural names)
AIUpdateInterface: +0x04 moduleData (+0x4C range, +0x50 LocomotorSetType, +0x54 bool),
+0x08 object, +0x20 AICommandInterface, +0x30 state machine (vslot 12 bool),
+0x40 current victim ID, +0x140 Rva001B3FE0* (test()), +0x1D8 mode (2/3/4),
+0x27C AICommandParmsStorage, +0x31C bool pending. Object: +0x04 OVERRIDE template
(kind word +0xD4 bit 13), +0x90 status BitFlags<86> (bits 37, 71, 73), +0xAC
GeometryInfo (radius +0x10 of the copy), +0x110 model conditions (bit 277 at +0x130),
+0x1A4 flags & 0x100, +0x204 AI, +0x214 range owner.

## Levers found (each measured)
- Mask temporaries: ctor must zero with `memset` then `|=` the bit -> retail's
  `xor eax; mov; mov; or eax,0x80; mov` and no global zero register (loop init
  gave `xor ebx,ebx` + `cmp x,ebx` everywhere).
- Status/model-condition tests must return the raw masked word (not `!= 0`):
  gives `test byte [edi+0x94],0x20` / `test ah,2` instead of `shr; test cl,1`.
- Thing needs a vptr (virtual dtor) so Object fields land at retail offsets.
- `inRange = range * range < source->getDistanceSquared(victim);` reproduces
  retail's pre-call `fld; fld st0; fmul st1; fstp [esp+0x1c]; fstp st0` and
  `fcomp [esp+0x18]` (range *= range then `dist > range` defers the multiply).
- `throw()` on rva001E3E40 and Coord3D::GetLengthEstimate2D keeps the geometry
  copy out of the EH map (removing it from the estimate adds two state stores).

## Remaining residue
1. +0x21E: retail `fcompp`, ours `fcomp st(1)` ... `fstp st(0)` (+2 B) for
   `geom.getBoundingCircleRadius() * 2.0f > dist`. Inert (all keep fcomp/fstp):
   dist < 2r, ternary, if/else, reach local, radius local, r+r, 2.0f*r, 2.0 double,
   const Real, const Real &, double dist, nested block, inline member helper taking
   dist, call on the returned temporary. Worse: call inline in the compare
   (spills 2r, 849 B), call on the left (851 B), Q `>=` if/else (3 diffs).
2. Frame slots: retail entry mask at esp+0x2C (alone) and end mask at 0x20 shared
   with `offset`; ours (/FAsc) puts the entry temp on offset's slot and the end temp
   alone. Inert or worse: named entry mask (frame +0xC), named block-scoped entry
   and/or end masks, const-ref offset, by-value inline clearStatus (848 B),
   offset declared in outer blocks (865 B; there the end temp shares with the
   rva return temp, so temp/temp sharing exists).

## Dependencies for landing
Callees 0x00273F90 (main update) and 0x0027C250 (quick update) are gen dumps
with no pins; the bank calls them as `AIUpdateInterface::rva00273F90()` /
`rva0027C250()` (thiscall, no args, return UpdateSleepTime; ret with no
stack pop verified). Landing needs those two address-derived pins (ILT
0x0000DA80 / 0x00020FA9). All other 17 callees resolve to ledger names.
