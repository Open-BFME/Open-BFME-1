# 0x005C37E0 ParticleSystemManager::update (467 B): EXACT

Landed source: `game/GameEngine/Source/GameClient/System/ParticleSystemManagerUpdate.cpp` (scratch `build/wf/005c37e0/best.cpp`), probe `result EXACT (modulo relocation
slots)` at 467/467 B, 12 relocations. VC7.1 `/DNDEBUG /MD /EHsc` (the same flags
as the bank and the sibling ParticleSystemUpdate.cpp). Supersedes the 0.9807 bank
(`targets/game/reverse/attempts/0x005c37e0.cpp`, which reproduced at 9 B as logged).

## What fixed the start/end slot swap

Both changes are needed:

1. Timing written like the matched sibling ParticleSystem::update
   (`game/GameEngine/Source/GameClient/System/ParticleSystemUpdate.cpp`, retail
   0x005D1140): `__int64 frequency, start, end;` with QPC/QPF taking `__int64 *`,
   and `m_lastUpdateMilliseconds = (Real)(end - start) * 1000.0f / (Real)frequency;`
   with no store back into `start`. In the sibling's retail code the int64->fild
   temporary sits in `start`'s dead slot.
2. `~BfmeParticleSystemHandle()` is an **inline definition** with the unlink body,
   not an out-of-line `throw()` declaration. VC7.1 still does not inline it at the
   call site. It calls the COMDAT `??1BfmeParticleSystemHandle@@QAE@XZ`, which
   the same object emits and which probes EXACT against retail 0x001DA440
   (81 B, ILT 0x00013994; the ledger currently has it as gen-alias
   `?unlink@GenNode_006fa270@@QAEXXZ`). Because the body is visible, the compiler
   also omits the state -1 store, so the earlier `throw()` lever is not needed.

## Mechanism (measured)

- `&start` escapes into QueryPerformanceCounter. While `start` is in scope,
  VC7.1 treats it as live across any later opaque call, so the fild temporary
  cannot reuse its slot. That gives frame 0x30 and 42 B of differences. With no
  EH and nothing after the timing block, the temporary packs into `start`
  (d_noeh). A trailing opaque call blocks this (d_call, d_call2), but a trailing
  plain store does not (d_store). Putting the timing locals in a block that ends
  before the destructor packs the temporary, but the handle constructor then has
  to move above the QPC calls (v5, d_late).
- With an inline destructor body the trailing call no longer pins `start`, so the
  temporary packs into it. Slot order then matches retail: freq [24h], start
  [1Ch], end [14h], with the difference stored to [1Ch].
- The bank's store-back form (`start = end - start`) together with the inline
  destructor still gives 9 B (v9). The extra references make `start` heavier,
  which moves it to the lowest slot.
- `__forceinline` on the handle's `operator=` is still required. With plain
  `inline` the function is 322 B (v10).

## Trials this session (all build/wf/005c37e0/)

| file | change | result |
|---|---|---|
| base.cpp | bank | 467/467, 9 B (reproduces) |
| v1 | __int64 + temp form, out-of-line throw() dtor | 467, 42 B, temp gets own slot (frame 0x30) |
| v2 | v1, dtor without throw() | 475, 59 B |
| v3 | handle declared before timing locals | 471, 384 B |
| v4 | `end` declared after handle | 467, 42 B |
| v5 | timing locals in inner block, handle outer | packs, but ctor stores before QPC (387 B) |
| v6 | inline getPerformanceCounter() helpers (W3DDisplay style) | 499 B, copies |
| v7 | handle in inner block, timing locals outer | 42 B |
| d_late | v5 + uninitialised ctor, zeroing after QPC | 65 B (EH state store placement) |
| d_oa / d_ow | /Oa, /Ow (unjustified, diagnostic) | 395+ B |
| **v8 / best** | **v1 + inline dtor body** | **EXACT** |
| v9 | bank store-back form + inline dtor | 9 B |
| v10 | best with operator= plain inline | 322 B |

## Landing (2026-11-06)

- Landed as `?update005C37E0@ParticleSystemManager@@UAEXXZ`: the ILT guard
  contradicts `?update@ParticleSystemManager@@UAEXXZ` (slot 22795, window
  15031-15046), like every other ParticleSystemManager row, and a class-name
  search over the 59,580-word ilt_oracle dictionary found no class fitting two of
  update/reset/init/dtor/LoadPostProcess/GetSnapshotName/setOnScreenParticleCount.
  The address-derived method name follows doParticles006FA9B0. ParticleSys.cpp
  still carries the Zero Hour `update` body under its present-unmatched marker.
- Landed with `add_match.py --replace-rva 0x005C37E0`; `./build.sh` on the TU
  verified 1/1 rows, 7 DIR32 references and 1 float constant.
- The TU emits the COMDAT `??1BfmeParticleSystemHandle@@QAE@XZ` (body = retail
  0x001DA440). The call resolves through the existing symbols.csv pin of that
  name to ILT 0x00013994. `find_declared_unmatched.py` flags only the update
  body, so no destructor row or marker was added. The 0x001DA440 row stays the
  gen-alias it was; the several pins on ILT 0x00013994 are left for a later
  one-identity pass.
- No BFME 2 donor was checked in the attempt sandbox (the submodule was not
  initialised there); the Zero Hour GeneralsMD loop is the reference.
