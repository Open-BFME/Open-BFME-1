# Eva::Eva is at 0x004271B0, not Radar::tryUnderAttackEvent

The ledger row at `0x004271B0` was a naked `__emit` lift filed under
`?tryUnderAttackEvent@Radar@@` (a truncated decoration of the Radar
declaration). That name is refuted by the body itself, on three independent
grounds, and the constructor identity is established instead.

## 1. It installs Eva's vtable pair

The body writes `0x010F1FA8` at `+0x00` and `0x010F1F94` at `+0x08` -- the same
pair, in the same order, that the byte-matched `??1Eva@@UAE@XZ` at `0x00426560`
(`EvaDestructor.cpp`) writes. `tools/vtable_lookup.py 0x010F1FA8` shows the
second constant is carried by exactly two `.text` bodies: that destructor and
this one.

The slots of `0x010F1FA8` are incremental-link thunks; resolving their `jmp`
targets names the class outright, because four of the targets are already
byte-matched:

| slot | thunk | target | matched row |
|------|-------|--------|-------------|
| +0x00 | `0x004364DA` | `0x00426BD0` | `??_GEva@@UAEPAXI@Z` (`EvaDestructor.cpp`, 30 B) |
| +0x04 | `0x00432F06` | `0x00426680` | `?init@Eva@@UAEXXZ` (`EvaInit.cpp`, 258 B) |
| +0x10 | `0x00423682` | `0x004267D0` | `?reset@Eva@@UAEXXZ` (`EvaReset.cpp`, 127 B) |
| +0x14 | `0x0042B431` | `0x00423B70` | `?update@Eva@@UAEXXZ` (`EvaUpdate.cpp`, 153 B) |

A matched caller or vtable slot outranks any other evidence, and this one is
four deep. The secondary table `0x010F1F94` slot +0x0C targets `0x00422C80`,
one instruction block from the matched `?setEvaEnabled@Eva@@QAEX_N@Z` at
`0x00422C30`.

The transient `0x01073744` written to `+0x08` before the two derived tables is
the compiler's own emission for the inline-empty second base, exactly as
`??1Eva@@UAE@XZ` restores it on the way out.

## 2. It runs the base constructors in the order the class declares them

`call 0x009A1A30` is the matched `??0SubsystemInterface@@QAE@XZ`
(`SubsystemInterface.cpp`); the body at that address is
`mov eax,ecx; mov [eax],0x01141640; mov [eax+4],0; ret` -- a constructor that
returns `this` in EAX, and the return-this ABI this body honours with
`mov eax,esi` before its own `ret`. Every other `Radar` method lives near
`0x00107000-0x00108000`; this body is adjacent to the matched Eva bodies.

## 3. It seeds the message-name table, and the offsets match matched Eva bodies

The loop walks a 17-iteration `unsigned` counter over the pointer table at
`0x010F1AF0`, and that table is, read straight out of the image, exactly
BFME's Eva message list:

    DefaultEvaEvent, BaseUnderAttack, AllyUnderAttack, BeaconDetected,
    GeneralLevelUp, UnitLevelUp, UpgradeComplete, CastleBreached,
    EnemyCampSighted, AllyDefeated, EnemyCampDestroyed, CampDestroyed,
    AllyCampDestroyed, BuildQueuePausedDueToCPLimit,
    CannotBuildDueToCPLimit, BuildingBeingStolen, BuildingStolen

(entry 17 is `"Side"`, the head of the next table -- so 17 is read off the
image, not guessed). The same body calls the two Eva member helpers
`0x00427130` and `0x00425E40` that `EvaReset.cpp` / `EvaInit.cpp` also call,
zeroes the four parsed-table containers at `+0x0C/+0x18/+0x24/+0x38` that the
matched destructor tears down, stamps `+0x58=1` and `+0x5C=1` with the same
values the matched `?reset@Eva@@` stamps, and defaults `+0x60/+0x64/+0x68` to
`1000.0f/15/35` -- the BFME-only `MiscEvaData` block that the matched
`?parseMiscEvaData@INI@@SAXPAV1@@Z` at `0x00422BD0` (`Eva.cpp`) parses at
`Eva+0x60`.

## Extent

The retail body is 379 bytes, `0x004271B0`-`0x0042732A`, terminating in `ret` at
`0x0042732A`; `0x0042732B` is `int3` padding ahead of a 16-aligned start. The
ledger's 373 came from the lift's copied Ghidra size and stopped short of the
`ret`. The conversion is byte-exact at 379.

## Conversion

`game/GameEngine/Source/GameClient/EvaConstructor.cpp` implements the body in
clean C++ against the retail BFME layout, in the directory that already holds
the matched `Eva` methods. The `+0x18` and `+0x4C` element types keep the
address-derived spellings the matched `resize` bodies already carry
(`Rva00427130Vector`, and the `EvaCheckVector` whose callee is the matched
`?resize@EvaCheckVecBase@@QAEXHUEvaCheck@@@Z`); the mapped payload type is
address-derived for the same reason, since the body only ever stores the loop
index into it.

## Two ledger pins this body needed, and why

The `+0x24` and `+0x38` members are `hash_map<AsciiString, Rva004240F0Value *>`,
the same address-derived payload spelling the matched
`?resize@?$hashtable@U?$pair@$$CBVAsciiString@@PAURva004240F0Value@@...` row at
`0x004240F0` already carries, so `resize` resolves by itself. The other two
members of that one map type had no row under this instantiation, and the
ledger's two address-derived payload names are **mutually inconsistent for a
single type**: it attributes `0x004240F0` to `resize@...Rva004240F0Value...` and
`0x00424D30` to `insert_unique_noresize@...Rva00424D30Value...`, while this
constructor's aligned call sites prove all three bodies belong to one map. Two
pins resolve that, each one name at one address decoded from the image rather
than from the desired byte shape, and each following the convention symbols.csv
already uses for these shared hashtable members (the `gen-tgrid payload member`
rows for `Rva...`-keyed instantiations of the same two members):

| member | address | how the address is known |
|--------|---------|--------------------------|
| `?_M_initialize_buckets@...Rva004240F0Value...` | `0x00424990` | two `call rel32` sites at `+0x75` and `+0x96`, each via ILT `0x0043301E`; the 106-byte body is the copy every retail hashtable instantiation gets, its body never touching the key type |
| `?insert_unique_noresize@...Rva004240F0Value...` | `0x00424D30` | one `call rel32` site at `+0x14D` via ILT `0x004382C6`; the 270-byte body is matched, and is the AsciiString key with the same `rts::hash` / `rts::equal_to`, the pointer payload never being dereferenced as a typed object |

Neither pin invents a semantic name, and each is the gated
one-name-many-addresses invariant's benign case (one address, one name).
`tools/pin_consistency.py --check` stays OK.

