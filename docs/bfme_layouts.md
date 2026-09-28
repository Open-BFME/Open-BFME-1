# BFME class layouts, witnessed from the code

BFME moved most game-class members away from their Zero Hour offsets. These
regenerable artifacts record the moves, so no port has to rediscover them.

## What exists

| artifact | what it is | how it is made |
|---|---|---|
| `targets/game/reverse/zh_offsets.json` | ZH member offsets and `sizeof` per class | `python tools/zh_offsets.py --all` compiles `&((C*)0)->m` tables per header with the project's cl (MSVC 7.1 has no layout report flag) |
| `targets/game/reverse/bfme_layouts.json` | witnessed retail offsets per (class, member) | `python tools/layout_witness.py --compile` (reference TUs into `build/layout/ref/`, ~10 min), then `python tools/layout_witness.py` |
| `tools/bfme_layout.py` | reader: `bfme_layout.py Object`, `--grep Contain`, `--changed` | |
| brief context pack | "BFME layout of <class>" lines, when the body's class is known from its vtable or pin | `tools/fleet/context_pack.py` |

A rerun where reference compiles fail names fewer members. Compare member and
class counts before and after, and never commit a witness that names fewer.

## How a witness is made

Every function the ledger or a pin names, whose ZH source compiles, gives a
pair (ZH-compiled and retail body), aligned by opcode shape (difflib; pairs
under 70% alignment are dropped). Each `this`-relative memory operand whose
displacement differs is one witness, "ZH +zh is retail +bfme", named through
the ZH offset dump along the primary base chain. Witnesses are weighted by
alignment quality and summed per (owner class, member): `votes/total` is that
sum and its share, and `alts` are the dissenting offsets. Unchanged offsets
are recorded too; a witnessed "unchanged" is worth as much as a move when
laying out a shim.

## Reading it

    $ python tools/bfme_layout.py Object --changed
    Object  (39 witnessed members)
      m_group         zh +0xc8   -> bfme +0x188   6.0/6.0
      m_behaviors     zh +0x18c  -> bfme +0x1f0   15.0/16.0  alts 0x18cx1.0
      ...

## Known blind spots (read the `alts`)

- A method whose `this` is a non-primary base subobject (SubsystemInterface
  `update()` on TerrainLogic) reports subobject-relative offsets.
- Registers that alias `this` after the prologue are not tracked, so some
  accesses are missed (never misreported).
- Members of headers the dump could not compile (most declare no members)
  appear as `+0x..?` under the function's own class.
- A moved member read by several derived classes can collect dissenting votes
  from misaligned bodies. Trust `confidence >= 0.75` with `votes >= 2`.
- A body of 16 bytes or less matches every same-shape ZH getter, so several
  names fit it and only one is right (retail has no identical-COMDAT
  folding). An unshifted access in it only echoes the ZH layout, unless
  retail's export table names the body with the voter's own symbol. An echo
  counts toward a member's total but never wins: a member witnessed only by
  echoes is left out (`fns` lists only voters that can win), and
  `name_oracle.py --class` prints the ZH member as a labelled hint instead.
