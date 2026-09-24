# Matched rows that verify only a prefix (2026-09-24)

A `matched` row's `target_size` is the number of bytes the gate compares. When
that size stops short of the retail body, only the prefix is verified. The rest
of the body counts as unclaimed, and no queue offers it: its address already
has a matched row. The row looks finished and is not.

## How they were found

For each matched non-`.asm` row: Ghidra's function at the same RVA is more than
16 bytes longer, the byte after the row is not `int3`, and nothing else claims
it. That gives **34 rows / 8,456 missing bytes** on 4adaa6ee1. Then
`probe.py` over the Ghidra extent (row size temporarily widened, ledger
restored) sorts them:

* **Equal length, few differing bytes (15).** The source is right; the tail
  touches one field, vtable slot or constant that BFME moved. These are the
  best finishing work in the repository and nothing listed them.
* **Different length (18).** Real near-misses or partial reconstructions.
* **Wrong function (1).** `??0Player@@QAE@H@Z` @ 0x0022E820.

## Landed so far

| row | was | now | lever |
|---|---:|---:|---|
| `ParticleEmitterDefClass()` | 26 | 255 | ShaderClass cull mode is bit 20 in BFME (`shader.h`) |
| `parseListboxData` | 166 | 511 | BFME ListboxData has a 4-byte field at +0x10 (sweep `Gadget.h`) |
| `WorldHeightMap::ParseWorldDictDataChunk` | 44 | 141 | GlobalData `m_weather` +0x21C (INI witness), TU-local view |
| `W3DDisplay::updateAverageFPS` | 106 | 328 | `m_averageFPS` +0x17C (matched getter), TU-local view |
| `BridgeBehavior::getRandomSurfacePosition` | 24 | 277 | `#line` for retail `__LINE__`/`__FILE__` |
| `LocomotorSet::addLocomotor` | 52 | 138 | Locomotor/LocomotorTemplate offsets + one proven STL pin |
| `parseAngleFX` | 23 | 130 | module data shifted 0x14 (INI witness) + one proven STL pin |
| `NetPacket::write/readGameMessageArgument...` | 26/26 | 291/729 | BFME `ARGUMENTDATATYPE_SQUADID` at 6 (sweep `MessageStream.h`) |
| `??0Player@@QAE@H@Z` | 43 | retired | 0x0022E820 is a ContainModuleData ctor; Player::Player is 0x000DD980 |

## Still open (equal length unless noted)

| row | RVA | full | diffs | what differs |
|---|---|---:|---:|---|
| `WinInstanceData::getText` / `getTooltipText` | 0x00479B00 / 0x00479AB0 | 58 | 1 | DisplayString::getText is vtable +0x08 in BFME, +0x0C in ZH |
| `InGameUI::createGarrisonHint` | 0x0043ACA0 | 39 | 1 | GameClient::findDrawableByID +0x2C in BFME, +0x20 in ZH |
| `InGameUI::setMouseCursor` | 0x0043AA10 | 54 | 5 | Mouse vtable +0x38 vs +0x28; InGameUI fields +0x824/+0x828 vs +0x1940/+0x1944 |
| `TintEnvelope::play` | 0x004156D0 | 148 | 13 | not yet read |
| `canSelectedObjectsOverrideSpecialPowerDestination` | 0x0043ED60 | 136 vs 143 | 2 | length differs by 7 |
| `WeaponBonusSet::parseWeaponBonusSet` | 0x001E1C20 | 95 vs 101 | 16 | |
| others | | | 30+ | see `tools`-free reproduction below |

Two of these need a proven BFME vtable for a shared class (DisplayString,
GameClient); that is shim-header work with a full gate, like `MessageStream.h`.

## Two tool blind spots found on the way

* **`ctor_vtable.py` cannot see a truncated constructor.** It reads the bytes a
  row claims, and the 43-byte `??0Player` row stopped before its vftable store
  at +0x27. A prefix claim hides its own misidentification.
* **The build cache misses a new shadowing header.** An object's recorded
  dependencies name the header it found last time. Adding
  `reference/shims/sweep/Common/MessageStream.h`, which shadows Zero Hour's copy,
  left `NetPacket.obj` current until the object was deleted by hand. A
  full gate run after adding a new shim should start from an empty
  `build/match/`, or it can reuse stale objects.

## Reproduce

    # rows whose Ghidra extent is longer and whose tail is unclaimed
    # (see the query in this commit's history), then per row:
    python3 tools/probe.py <source> '<symbol>' <rva>   # with target_size widened
