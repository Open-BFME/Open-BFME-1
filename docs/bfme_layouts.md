# BFME class layouts, witnessed from the code

BFME moved most game-class members away from their Zero Hour offsets, and until
now every port rediscovered the moves one body at a time (the attempts log
records "layout/offset" as the wall on ~1,350 bodies, ~430 KB). This is the
shared answer, derived mechanically and regenerable.

## What exists

| artifact | what it is | how it is made |
|---|---|---|
| `reverse/zh_offsets.json` | ZH member offsets: 1,488 classes, 9,539 members, plus `sizeof` | `python tools/zh_offsets.py --all` compiles `&((C*)0)->m` tables per header with the project's cl (MSVC 7.1 has no layout report flag) |
| `reverse/bfme_layouts.json` | witnessed retail offsets: 5,047 members over 930 classes, 1,530 moved, 595 of them high-confidence | `python tools/layout_witness.py --compile` (every reference TU -> `build/layout/ref/`, ~10 min) then `python tools/layout_witness.py` |
| `tools/bfme_layout.py` | reader: `bfme_layout.py Object`, `--grep Contain`, `--changed` | |
| brief context pack | "BFME layout of <class>" lines under the callee list, when the body's class is known from its vtable or pin | `tools/fleet/context_pack.py` |

## How a witness is made

Every function the ledger or a pin names, whose ZH source compiles, gives a
pair: the ZH-compiled body and the retail body. They are aligned instruction
by instruction on opcode shape (difflib; bodies under 70% alignment are
dropped). Each `this`-relative memory operand whose displacement differs is
one witness "ZH +zh is retail +bfme", named through the ZH offset dump by
walking the primary base chain. Witnesses are weighted by alignment quality
and summed per (owner class, member); `votes/total` is that sum and its share,
`alts` are the dissenting offsets.

A witnessed *unchanged* offset is recorded too; it is worth as much as a move
when laying out a shim.

## Reading it

    $ python tools/bfme_layout.py Object --changed
    Object  (39 witnessed members)
      m_group         zh +0xc8   -> bfme +0x188   6.0/6.0
      m_behaviors     zh +0x18c  -> bfme +0x1f0   15.0/16.0  alts 0x18cx1.0
      m_team          zh +0x1d0  -> bfme +0x23c   4.9/4.9
      ...

Three of today's hand-derived conversions were used as the check: Object
`m_body` 0x194 -> 0x200, TerrainLogic `m_bridgeDamageStatesChanged` 0x30 ->
0x38 and the UpdateModule growth all appear with the hand-found values.

## Known blind spots (read the `alts`)

- A method whose `this` is a non-primary base subobject (SubsystemInterface
  update() on TerrainLogic) reports subobject-relative offsets.
- Registers that alias `this` after the prologue are not tracked, so some
  accesses are missed (never misreported).
- Members the dump could not compile (350 headers failed, most because they
  declare no members) appear as `+0x..?` under the function's own class.
- A moved member read by several derived classes can collect dissenting votes
  from misaligned bodies; trust `confidence >= 0.75` with `votes >= 2`.

## Also fixed alongside

Briefs used to present a call through a 5-byte incremental-link thunk under the
thunk's placeholder pin (`?bfmeCur1094@...`) even when the body it jumps to is
named (`Object::getControllingPlayer`). 4,448 call sites inside dumps were in
that state and 467 dumps (182 KB) have every callee named once the thunk is
followed. The context pack now prints `=> jmp <target> <name>` for those.
