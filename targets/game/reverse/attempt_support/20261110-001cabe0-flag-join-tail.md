# 0x001CABE0 (376 B) `?bfmeAskBIC@BfmeSubBIC@@QAEHXZ`: EXACT

Best candidate: `build/wf/001cabe0/best.cpp`. Flags `/DNDEBUG /MD /EHsc`, the bank's own flags, unchanged.
`probe.py best.cpp '?bfmeAskBIC@BfmeSubBIC@@QAEHXZ' 0x001CABE0 --size 376` gives
`size ours=376 retail=376 relocs=22` and `result EXACT (modulo relocation slots)`. `--all` shows 0 differing rows.

## Baseline

The bank `targets/game/reverse/attempts/0x001cabe0.cpp` reproduces as logged: 376/376 bytes, 22 relocations and 4 differences.

- +0xD7: retail has `mov esi,[esi+0x34]`; the bank has `mov edx,...`.
- +0xE0: `push esi`; the bank has `push edx`.
- +0xFC/+0xFF: the vtable temporary is EDX; the bank uses EAX.

## Diagnosis

The two residues have one cause. In retail, the disguise index is a *variable* that the global allocator coalesces into the dying stealth register (ESI). It is not a scratch expression temporary. Because the index does not use a scratch-rotation step, the later contain vtable temporary lands on EDX (see docs/shape_levers.md "Scratch registers rotate").

The ZH accessor `getDisguisedPlayerIndex()` produces that variable. Earlier sessions measured the cost: in the bank's structure, the accessor flips the stealth and controller callee-saved registers. Stealth+index takes EDI, controller/player takes ESI, giving 21 diffs.

## Fix (ZH `Radar::addObject` colour-selection shape)

Three changes are needed together:

1. Read the index with `stealth->getDisguisedPlayerIndex()`. This is an in-class inline on the StealthUpdate view, spelled as in ZH StealthUpdate.h. The matched sibling `ObjectQueryRva001CF9F0.cpp` already uses the same accessor.
2. Use ZH Radar's tail. The contain result sets `colorPlayer` and clears `useDefaultColor`. Then `if (useDefaultColor || colorPlayer == 0) { inline getIndicatorColor }` is followed by `return colorPlayer->getPlayerColor();`. The bank used early `return`s after the contain call and the disguise.
3. Keep separate `controller` and `colorPlayer = controller` locals, as the bank does. A single ZH-style `player` variable swaps ESI and EDI.

Measured over a 128-variant factorial (`gen.py`, results in `results/`): every combination with (1)+(2)+(3) is EXACT. The orthogonal spellings do not matter. They include a getTemplate inline or the manual override walk, a getControllingPlayer inline or the ternary, isDisguised() or the field, and a getIndicatorColor inline or the expanded form.

- Without the accessor, the ZH-tail form gives 29 diffs.
- With the accessor but a single player variable, it gives 21.
- With the accessor and the bank's early-return tail, it gives 21.
- An inline `isKindOf` bit test (B1/B2) or a `getStealth()` inline that holds the static key (F1) changes the code by 212 to 225 bytes.

## Prior hypotheses (from the logs and handoffs; not repeated)

- Index locals, value or reference snapshots, and the native getter alone: 21.
- Volatile reads: 4.
- PlayerList PHI receiver (BFME 2 `BfmeSubBICRva00290FC9.cpp`): 4.
- Assignment-in-condition: 0.939.
- Visible callees: 4 or 21.
- Override, kindof and relationship switches: no improvement.
- `/EHs-c-`, `/Ob1`, `/GB`, `/Oy-`: no improvement.
- Fastcall vtable adapters: grow to 378.
- Declaration order of the stealth local in this session: inert, still 21.

None of these combined the accessor with the ZH tail.

## Landing notes (read-only checks; nothing landed)

**(a) ILT oracle.** `ilt_oracle.py check '?bfmeAskBIC@BfmeSubBIC@@QAEHXZ' 0x001CABE0` returns CONTRADICTED. So do the two other names pinned at ILT 0x0002CA61 (`?value@ObjectAttemptDamageFlagHook@@QAEHXZ`, `?bfmeValueZD@BfmeItemZD@@QAEHXZ`). No address-derived pin exists at that ILT. `?bfmeAskBIC@BfmeSubBIC@@QAEHXZ` is an existing `pin` row (symbols.csv, 0x0002CA61). It is a Bfme* stand-in, which ilt_guard exempts as an honest placeholder. Keep that name; do not adopt a guessed EA name.

**(b) Helper bodies emitted.** The object's emitted COMDATs are the in-class inlines `Player::getPlayerColor`, `Player::getDefaultTeam`, `PlayerList::getLocalPlayer`, `StealthUpdate::getDisguisedPlayerIndex` and `BfmeSubBIC::getContain`. None has a functions.csv or symbols.csv row, so there is no loser copy. `?isDisguised@StealthUpdate@@QBE_NXZ` has a ledger row at 0x002227D0 (+0x3C view), so the candidate does not use it; it reads `m_active` directly.

**(c) Call bindings.** Every call binds to an existing pin or ledger name:

- getFinalOverride@ThingTemplate (ILT 22BB)
- active@Rva000DF7F0Player (179BD)
- getControllingPlayer@Team (2369B)
- findModule@Object QBE W4NameKeyType (2AE23)
- nameToKey W4 (3ADD7)
- getRelationship@Player (3E77A)
- getNthPlayer@PlayerList (44F30)

**(c) Globals.**

- `?ThePlayerList@@3PAVPlayerList@@A`, VA 0x012ED748: data_rows.csv, matched.
- `?TheNameKeyGenerator@@3PAVNameKeyGenerator@@A`, 0x012ED600: dir32_addresses.csv.
- `??_C@_0O@JFMHDEPB@StealthUpdate?$AA@`, 0x0108403C: symbols.csv pin.
- The function-local static key (0x012EF590) and its guard (0x012EF594) are TU-local. The guard is also recorded as `?g_Va012EF594@@3IA` (GlobalFlagClearers_01.cpp). The EH cleanup 0x00C090C0 is already matched there as `Rva00C090C0ClearFlag`, and `eh_00c090ce` is a gen-ehstub. These are the same as the bank's, which earlier strict scoped gates passed (DIR32 and EH checks).

**(d) Home TU.** Use a GameLogic/Object TU next to `object.h`, for example a new `game/GameEngine/Source/GameLogic/Object/ObjectRva001CABE0.cpp`. Change the include to `#include "object.h"`. The ledger EA row names Object.cpp. No visible helper needs a particular TU. The replaced row is `?d_001cabe0@@YAXXZ` (gen-dump), so landing needs `--replace-rva 0x001CABE0`.

**Compliance.** The `// cl:` line is first. There is no volatile, asm or pragma. The bank's descriptive names (`localPlayer`, `controller`, `colorPlayer`, `useDefaultColor`, `stealth`, `thing`) are kept. The only addition is the inline accessor.

Reusable lever for shape_levers: when an index getter fixes a dying-register reuse but flips the ESI/EDI pairing, restore the reference source's flag-join tail before blaming the allocator.

## Landing attempt (2026-11-10): exact, blocked on a naming conflict

The candidate (banked as `targets/game/reverse/attempts/0x001cabe0.cpp`) passes `add_match` byte verification at 376/376 in a new `game/GameEngine/Source/GameLogic/Object/ObjectRva001CABE0.cpp`. The commit hooks refuse every row name, though, because two checks conflict.

symbols.csv pins three stand-in names at this body's ILT 0x0002CA61:
- `?value@ObjectAttemptDamageFlagHook@@QAEHXZ`, used by the matched Select0076B800.cpp, Object_attemptDamage_Thunk.cpp and Rva00271B40ShadowSync.cpp;
- `?bfmeAskBIC@BfmeSubBIC@@QAEHXZ`, used by BfmeConv470.cpp;
- `?bfmeValueZD@BfmeItemZD@@QAEHXZ`, unused.

`ilt_oracle` contradicts all three.

What each check refuses:

| Row name | Refused by | Reason |
|---|---|---|
| `bfmeAskBIC` | pin delta, `row-on-other-identity` | "the body already carries `?value@ObjectAttemptDamageFlagHook@@QAEHXZ`" |
| an address-derived name (`?rva001CABE0@BfmeSubBIC@@QAEHXZ`) | pin delta | same reason |
| `ObjectAttemptDamageFlagHook::value` | `ilt_guard` | the oracle contradicts it |

Converting the `ObjectAttemptDamageFlagHook` pin to an `abi-view=` row is not admissible either, because a view must respell the canonical's qualified name or spell its address.

Prerequisite: retire or rename the contradicted `?value@ObjectAttemptDamageFlagHook@@QAEHXZ` pin through the naming tools (name_lane.py / ilt_repair.py). That means repointing its three matched callers to the new row's name; their bytes are unchanged, since only the call target's name moves. Then land this body under its address-derived name, `?rva001CABE0@BfmeSubBIC@@QAEHXZ`, with `--replace-rva 0x001CABE0`.

The matched callers confirm the role: Select0076B800.cpp uses the return value as a draw colour.
