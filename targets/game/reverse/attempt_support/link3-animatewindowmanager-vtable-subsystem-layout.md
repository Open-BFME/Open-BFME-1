# Link queue #3 `??_7AnimateWindowManager@@6B@` (losers) — blocked on the shared SubsystemInterface layout

Session a1 s542 (2026-11-02), census d08539a550, no local census index.

Only one emitter: `game/GameEngine/Source/GameClient/GUI/AnimateWindowManager.cpp`.
Its vtable is wrong because the sweep shim `inputs/reference/shims/sweep/Common/SubsystemInterface.h`
keeps ZH's base layout.

Retail vtable RVA 0x00CF6F2C (installed by the matched ctor 0x0045D6B0 at +0x28), 9 slots:

| slot | ILT | body | name |
|---|---|---|---|
| 0 | 0x40C64 | 0x45DB20 | ??_GAnimateWindowManager |
| 1 | 0x30DA0 | 0x45DA80 | init |
| 2 | (direct) | 0x9A1A50 | SubsystemInterface::loadIniFilesFromLegend |
| 3 | 0x436B2 | 0x067930 | SubsystemInterface::postProcessLoad |
| 4 | 0x2848E | 0x45DAB0 | reset |
| 5 | 0x25D6F | 0x45D250 | update |
| 6 | 0x33497 | 0x067940 | `xor al,al; ret 4` (row ?d_00067940, object-symbol ?stdcall_false@@YG_NH@Z) |
| 7 | (direct) | 0x9A16C0 | ?method@Rva009A16C0 (empty) |
| 8 | (direct) | 0x9A16D0 | ?method@Rva009A16D0 (ret 4) |

Base vtable 0x01141640 has the same slots 2/3/6/7/8. The TU emits ZH's
[??_E, init, postProcessLoad, reset, update, draw] (??_E is a weak alias to ??_G,
not the problem).

Fix needs: SubsystemInterface (sweep shim) with slot 2 loadIniFilesFromLegend and
slots 6-8 in the base; slot 6's ledger identity is a free-function object symbol, so it
must first be re-homed as a SubsystemInterface member. GameWindowManager.h models
6-8 per class (bfme_gwm_6/7/8); the shim note says the Display branch differs. Not a
TU-local repair: shared header + full gate + every caller of base virtuals rechecked.
