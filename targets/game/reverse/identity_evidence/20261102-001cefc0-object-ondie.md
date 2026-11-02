# Object::onDie is the 1493-byte body at 0x001CEFC0; row 7621 dtor is mis-anchored

Date: 2026-11-02. Link packet: `?onDie@Object@@QAEXPAVDamageInfo@@@Z`, kind
unresolved, consumers `InactiveBody.cpp` and `RespawnBodyInternalChangeHealth.cpp`.

## Claim

`?onDie@Object@@QAEXPAVDamageInfo@@@Z` lives at **0x001CEFC0, size 1493**.
The ledger row 7621 `??1InactiveBody@@UAE@XZ` at that address is mis-anchored:
the bytes are onDie's, not the destructor's. The real InactiveBody complete
destructor is the 25-byte `??1Rva00213B70NestedDtor@@UAE@XZ` at 0x00213B70
(row 8042).

## Evidence

1. Both consumer call sites reach one ILT slot. `InactiveBody::attemptDamage`
   (row 28217, 0x00213E40+0x3C) and `RespawnBody::internalChangeHealth`
   (row 172801, 0x002147E0+0x12A and +0x150) all `call` thunk `?j_0003369F`.
   `ilt_oracle.py check` on the slot returns CONFIRMED (exact, p=7.2e-4).
2. Thunk bytes verified in the retail baseline (`lotrbfme.exe`):
   `e9 1c b9 19 00` at RVA 0x3369F, target RVA
   0x3369F+5+0x19B91C = **0x1CEFC0**.
3. The deleting destructor at 0x00213E10 (row 12318) `call`s ILT 0x0003C867,
   whose thunk bytes target **0x00213B70** (row 8042, 25 bytes), not 0x1CEFC0.
   So the pin note claiming ILT 0x0003C867 "reaches matched cleanup body
   0x001CEFC0" is wrong, and with it row 7621's anchoring.
4. Corroboration: row 130195 (`VictorySystem` owner) notes its sole caller is
   0x001CEFC0 loading TheVictorySystem — onDie behavior, not destructor
   behavior. The 0x1CEFC0 prologue takes a pointer argument and installs an SEH
   frame consistent with the donor below.
5. Prior state: row 7621's TU (`InactiveBodyDestructorThunk.cpp`) is a naked
   `__emit` lift — a dump, not a conversion — so no verified C++ is lost by
   re-homing the address.

## Donor

BFME 2 `Code/GameEngine/Source/GameLogic/Object/ObjectOnDie.cpp`, donor
`?onDie@Object@@QAEXPAVDamageInfo@@@Z` at 0x00298517, 798 bytes, landed at
donor revision 961d0becd9. Same contract (behavior loop, VictorySystem,
container, drawable, Lua events, team notify, EVA) but BFME 1's body is 1493
bytes: expect extra EVA/kindOf/victory-grid logic and different inlining.
Zero Hour's `Object::onDie` (`GeneralsMD/.../Object/Object.cpp:4572`) is the
older ancestor (no Lua/emotion paths).

## What remains

Port the donor to `game/GameEngine/Source/GameLogic/Object/ObjectOnDie.cpp`
with BFME 1 layouts/flags from matched sibling TUs, probe against 0x1CEFC0,
and land with
`add_match.py ?onDie@Object@@QAEXPAVDamageInfo@@@Z 0x1CEFC0 1493 <src> --correct-identity ??1InactiveBody@@UAE@XZ --identity-evidence <this file> --model <model>`.
The naked lift TU must be emptied as part of the landing. The two consumer
TUs need no changes (their externs resolve once the body exists).
