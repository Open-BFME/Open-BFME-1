# Task 62: OpenContain ctor wrong_selected — naked-ctor phantom bytes

Queue rank 62: `??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z` (0x2277A0,
722 B), `wrong_selected` on `GarrisonContainCtor.cpp` (312 B) and
`OpenContainConstructorThunk.cpp`. The duplicate-emitter half was already
fixed (1091945d31, Oct 21: removed the ZH-layout ctor from OpenContain.cpp);
the fresh 2026-11-01 census still reports wrong_selected with the single
remaining definer. This investigation proves why, and why no link-lane edit
can fix it. Do not retry emitter removals or respells.

## Verdict chain (proven)

- Sole definer is the naked `__emit` dump in OpenContainConstructorThunk.cpp
  (row owner, 722 emits, byte-exact vs retail 0x2277A0 over the row extent).
- The emitted object section is 725 bytes: MSVC 7.1 appends `8b 45 fc`
  (`mov eax,[ebp-4]`) after the dump's trailing `ret 8`. Retail has `cc cc cc`
  there. Exact object-vs-retail diff: 0/722 in extent, 3/3 past it.
- The byte gate checks the 722-byte row extent: passes (`./build.sh` scoped
  1/1). The census judges the full 725-byte section with zero relocations
  (exact compare): wrong. Hence `comdat (retail: not retail's body)` +
  `selected` on a byte-exact dump.

## Mechanism (7 isolated experiments, default flags `-O2 -GR- -EHsc-`)

| case | emits | section |
|---|---|---|
| naked void member, 2 nops | 2 | 2 exact |
| naked void member, 722 nops | 722 | 722 exact |
| real 722 stream, naked void member | 722 | 722 exact |
| real 722 stream, naked ctor (Thing*, ModuleData*) | 722 | 725 (+`8b 45 fc`) |
| real 722 stream, naked param-less ctor | 722 | 725 (+`8b 45 fc`) |
| real 722 stream, naked dtor | 722 | 722 exact |
| real stream halves (361/361), junction, tail | — | all exact |

Content, size, params and SEH-pattern prefix are all ruled out; ctor-ness is
the trigger. Presumed cause: the ctor "return this" epilogue is emitted even
for naked. Recorded in docs/shape_levers.md.

Independently re-confirmed 2026-11-01 in a clean worktree via the repo's own
`compiler_command` helper with private outputs: 2 emits (`90 c3`) as a naked
ctor emit 5 bytes (`90 c3 8b 45 fc`), as a naked dtor or void member exactly
2; the real 722-emit thunk compiles to a 725-byte `.text` whose first 722
bytes equal retail at 0x2277A0 exactly.

Blast radius: 7 files hold all 19 naked-ctor definitions in `game/`
(GameResultsQueueCtorThunk, FireWeaponWhenDeadBehavior_ctor_Thunk,
CastleBehaviorCtorThunk, AIUpdateInterfaceCtorThunk,
GiantBirdAIUpdateCtorThunk, OpenContainConstructorThunk,
fx_particle_system_bulk with 8); naked dtors (31 definitions) are unaffected.
Note `fx_particle_system_bulk.cpp` mixes naked ctors with other functions in
one `.text`, so its phantom bytes sit between functions rather than at the
section tail — the per-symbol consequence there still needs measuring.

## Donor (checked, not ported)

BFME 2 has a matched real-C++ `??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z`
at 0x004649F8 but only 386 bytes vs BFME 1's 722
(`Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainCtor.cpp`,
donor 6584c197419be3fc15b423d5142c7de896336fc3, verified clean). BFME 1's ctor
builds 9 polymorphic subobjects (vptrs at +0x00, +0x0c, +0x10, +0x20..+0x34
per GarrisonContainCtor.cpp) plus EH states the donor lacks. A port is
substantial reconstruction, not a link repair.

## Unblocking conditions (lift/reconstruction lane, not link lane)

- Convert the 722-byte dump to real C++ in OpenContain.cpp (the TU its
  `// readable body of` comment names), land with `add_match --replace-existing`
  at the proven extent, delete the naked function (AGENTS.md lift lane).
- No spelling, pin, row move or emitter removal can clear this entry: any
  naked-ctor emission carries the 3 phantom bytes. Revisit only for the
  conversion; the donor ctor above is the structural starting point.

Re-logged as `blocked` on `??0OpenContain@@QAE@PAVThing@@PBVModuleData@@@Z`
0x2277A0. Worker t=45 model=muse-spark-1.3; independent confirmation t=20
model=muse-spark-1.3; blocker=toolchain.
