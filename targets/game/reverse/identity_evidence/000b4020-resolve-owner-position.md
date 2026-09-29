# 0x000B4020 — identity and shape notes

## Identity

`?resolveOwnerPosition@AudioEventRTS@@QAEXPAUCoord3D@@PA_N@Z` (thiscall, two
stack args, `ret 8`).

Evidence (unchanged from earlier sessions, re-verified this pass):

* Eleven call sites, all through an ILT thunk, all inside `AudioEventRTS`
  constructor bodies. Five are named in the ledger and landed:
  `??0AudioEventRTS@@QAE@ABVAsciiString@@W4ObjectID@@@Z`,
  `??0AudioEventRTS@@QAE@ABUAudioEventInfoRef@@W4ObjectID@@@Z`,
  `??0AudioEventRTS@@QAE@ABVAsciiString@@W4DrawableID@@@Z`,
  `?thinDrawableIDCtor@AudioEventRTS@@QAE@ABVAsciiString@@W4DrawableID@@@Z`
  (`game/GameEngine/Source/Common/Audio/AudioEventRTSThinExtraCtor.cpp`) and
  `??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z`
  (`AudioEventRTSCopyAndLifetime.cpp`).
* Those constructors write `m_ownerType` = 2 (ObjectID), 1 (DrawableID) and
  5 (LivingWorldID) and then call this body with a `Coord3D` local plus a
  `bool` at `local+0x1C` — the two-argument `ret 8` shape this body has.
* The dispatch table at VA `0x4B4190` has six entries: 0, 1, 2 and 5 to four
  distinct bodies, 3 and 4 to the shared zero-fill tail at `+0x149`. That is
  exactly the set of `m_ownerType` values the matched constructors write.

No second real name is claimed for this address.

## Layout

`this+0x2C` owner ID, `+0x30` owner type, `+0x34..+0x3F` cached position,
`+0x40` a one-byte flag that the matched constructors set to 1.

## SOLVED

The body landed byte-exact. See
`targets/game/reverse/analysis/0x000b4020-levers-tried.md` for the shape notes
and the measurement trail. The two facts the earlier attempts missed:

* Each case's null path branches to **that case's own tail**, so the tail sits
  outside the null test in every arm (case 5's outer null test on `Glo012F1028`
  included). Putting it inside the `if` merges the tails and lands ~404 B.
* The position copy needs a **reference**-returning `getPosition()` on the
  inlined `Object` view — but case 1 must stay pointer-returning because its
  callee is the pinned retail ILT `0x0004B12D`.

The remainder of this file is the earlier shape analysis, kept as history.

## Earlier shape notes

**Retail keeps FOUR byte-identical 34-byte case tails** at `+0x19`, `+0x69`,
``+0xBF` and `+0x124`. MSVC 7.1 cross-jumps identical tails, and every clean
C++ shape that writes the same four exits collapses them into one, which is
where the missing ~80 bytes went in the earlier 288-byte bank.

Distinct barrier intrinsics immediately before each `return` keep the four
copies apart: `_WriteBarrier()` in the ObjectID (type 2) arm,
`_ReadWriteBarrier()` in the DrawableID (type 1) arm, and BOTH in the
LivingWorld (type 5) arm. Neither intrinsic emits an instruction or a
relocation. Measured: 404 bytes with 16 structural differences, versus 288
bytes with 13 for the merged form — the merged form's smaller byte count is
misleading, its instruction-level agreement is far worse.

Barriers placed at the TOP of an arm, or only in two arms, make MSVC merge
MORE tails (measured 300 and 304 bytes). They must sit on the last statement
before the `return`, and all three non-trivial arms need distinct barrier sets.

**Case 5's owner-position build.** The source-local `Coord3D` temporary must be
NON-volatile and filled through `set(x, y, z)` and then copied back. A
`volatile Coord3D` local forces an x87 `fld`/`fst`/`fstp` triple; retail uses
plain dword moves into and out of `[esp+4..0xF]`.

**Case 0's tail and the whole dispatch block are byte-exact** in the banked body.
The remaining divergence starts at the case-2 (`GameLogic::findObjectByID`)
position copy: retail emits `add eax,0x38` then `lea ecx,[esi+0x34]` and stores
through `ecx`, holding both the source and the destination pointer in
registers. Reproducing the `add eax,0x38` needs a reference-returning
`getPosition()` (a pointer-returning one folds the `+0x38` into each load),
but every spelling tried that produces the `add` also adds a `push edi` and a
`mov edx,ecx` the retailer does not have. That is the next thing to attack.

## Measurements this pass

| body | bytes | non-reloc diffs | shape |
|---|---|---|---|
| prior stash (all four tails merged) | 288 | 208 | 0.568 |
| distinct-spelling variant (`build/scratch/NN.cpp`) | 364 | 258 | 0.763 |
| barrier variant, banked (`RR`) | 404 | 221 | 0.794 |

Relocation-masked LCS byte score against the 367-byte retail body: prior stash
0.507, banked body 0.755.
