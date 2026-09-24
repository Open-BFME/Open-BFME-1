# `Object`: the layout the retail image and 998 TU-local copies agree on

`Object` has no header. 1,001 translation units declare their own partial
copy (`grep -rlE '^(class|struct) Object( *[:{]|$)' Code --include=*.cpp`),
each padded out to the fields one body touches. Verdicts citing layout drift
name `Object` more than any other class (88 KB of dump bodies, see
`docs/analysis/remaining-30pct-blockers-2026-09-24.md`). This page collects
what is proven so a header can be written once, from evidence.

Two sources, both independent of any one author's guess:

* **The retail image.** Constructors, vftables and vbtables are read directly
  (`tools/dis_retail.py`, raw dwords). These fix the class shape.
* **The census.** `python3 tools/layout_census.py --class Object` compiles
  every TU-local copy again with a probe appended, and MSVC 7.1 reports each
  member's offset and size. Every copy belongs to a byte-verified TU, so its
  offsets are witnessed by matched code. 998 of 1,001 copies probed (three
  compiles timed out under Wine); results in `build/layout_census/Object.jsonl`.

## Class shape (retail)

`??0Object` at 0x001D29A0 and `??0Thing` at 0x001328C0:

| offset | what | evidence |
|---|---|---|
| +0x00 | primary vfptr, `Thing` then `Object` | `Thing` ctor stores 0x01090DE0 (8 slots); `Object` ctor +0x7E stores 0x0109EE58 |
| +0x04..+0x5F | `Thing` data | `Thing` ctor zero/identity-fills exactly +0x04..+0x5C; `name_oracle --class Thing` witnesses every field |
| +0x60, +0x64, +0x6C, +0x70 | secondary vfptrs | `Object` ctor stores 0x0109EE44, 0x0109EE28, 0x0109EE00, 0x0109EDD0 |
| +0x68 | vbptr of the subobject at +0x64 | stored only when constructing the most-derived object; vbtable 0x00C9EEE0 = {-4, 0x358} |
| +0x3BC | vtordisp for the virtual base | ctor stores `vbase_off - 0x358` at `[this+0x64+vbase_off]` |
| +0x3C0 | virtual base (interface, 5 slots) | 0x68 + 0x358; initial vftable 0x00C9CDD8 is all `_purecall`, then 0x0109EDB8 (vtordisp thunks) |

`sizeof(Object)` is at least 0x3C4. No pool-name string exists in retail to
confirm the exact size.

**Primary vftable 0x00C9EE58 (28 slots).** Slots 0-7 are `Thing`'s (7 is the
scalar-deleting destructor, `??_GObject` 0x001D5CF0). `Object` adds slots 8-27:
9 `onDestroy`, 10 `getDrawable() const` (30 copies call +0x28), 12
`reactToTurretChange`, 13 and 14 `attemptDamage`, 15 `updatePendingDamage`,
16 `attemptHealing`, 19 `restoreOriginalTeam`, 20 `setTeam`, 21
`setTemporaryTeam`. The census copies that name slots put `attemptDamage` at
13, `attemptHealing` at 16 and `setTeam` at 20. `??_7Object@@6B@` was pinned
at 0x00C9EE74 (slot 7) until 975963cdd.

## Field consensus (census)

Copies that name a field at the offset; pads (`char`/`unsigned char` arrays)
are excluded. "oracle" = `tools/name_oracle.py` agrees at confidence >= 0.9.
The copies never place a field at a different offset from each other: after
excluding sub-field splits (`m_y` inside `m_cachedPos`) no two byte-verified
copies overlap a pointer with a different field.

| offset | size | name | copies naming it | oracle | notes |
|---|---:|---|---:|---|---|
| +0x04 | 4 | `m_template` | 67 of 84 | Thing | `ThingTemplate *`; ZH's `OVERRIDE<>` is one pointer |
| +0x08 | 48 | `m_transform` | 3 | Thing | `Matrix3D` |
| +0x38 | 12 | `m_cachedPos` | 126 call it `m_position` | Thing | `Coord3D` |
| +0x44 | 4 | `m_cachedAngle` | 8 call it `m_orientation` | Thing | `Real` |
| +0x48..+0x5C | | `m_cachedDirVector`, `m_cachedAltitudeAboveTerrain`, `...OrWater`, `m_cacheFlags` | | Thing | ZH order, witnessed |
| +0x74 | 4 | `m_id` | 110 | yes | `ObjectID` in 59 |
| +0x78 | 4 | `m_producerID` | 12 | yes | |
| +0x7C | 4 | `m_builderID` | | yes | |
| +0x80 | 4 | `m_drawable` | 12 | yes | |
| +0x84 | 4 | `m_name` | 2 | yes | `AsciiString` |
| +0x88 / +0x8C | 4 / 4 | `m_next` / `m_prev` | 14 | yes | |
| +0x90 | 12 | `m_status` | 36 | yes | 3 words: the `BitFlags<45>` spelled in some pins is ZH's size |
| +0xAC | 92 | `m_geometryInfo` | 12 | | `GeometryInfo` |
| +0x110 | 40 | `m_modelConditionFlags` | 21 (+13 `m_conditionFlags`) | | `BitFlags<320>`; 8 copies stop at 36 B |
| +0x1A4 | 4 | `m_disabledMask` | 15 | yes | |
| +0x1A8 | 44 | `m_disabledTillFrame` | 2 | | `[DISABLED_COUNT]` = 11 |
| +0x1EC | 4 | `m_firingTracker` | 2 | | |
| +0x1F0 | 4 | `m_behaviors` | 9 | 0.94 | `BehaviorModule **` |
| +0x1FC | 4 | `m_contain` | 76 | yes | |
| +0x200 | 4 | `m_body` | 23 | | |
| +0x204 | 4 | `m_ai` | 153 | 0.67 | the most-read field |
| +0x208 | 4 | `m_physics` | 4 | | |
| +0x20C | 4 | `m_radarData` | 3 | | |
| +0x210 | 4 | `m_experienceTracker` | 10 | | |
| +0x214 | 4 | `m_containedBy` | 31 | | |
| +0x21C | 4 | `m_containedByFrame` | 3 | | |
| +0x224 | 24 | `m_objectUpgradesCompleted` | 4 | | 6 words |
| +0x23C | 4 | `m_team` | 31 | yes | |
| +0x240 | 4 | `m_originalTeamName` | 3 | | `AsciiString` |
| +0x264 | | `m_weaponSet` | | yes | embedded; `Weapon *m_weapons[4]` at +0x26C (5 copies) |
| +0x2A0 | 4 | `m_weaponBonusCondition` | 4 | | |
| +0x344 | 1 | `m_privateStatus` | 30 | yes | |
| +0x3B0 | 4 | `m_partitionData` | 5 | 0.74 | |

From `m_firingTracker` to `m_team` the order is ZH's with `m_stealth` gone and
`m_partitionData` moved to +0x3B0.

## Where `bfme_layouts.json` is wrong

The census contradicts these witness rows, each with byte-verified copies:

| witness says | census says |
|---|---|
| `m_body` +0x194 | +0x200 (23 copies) |
| `m_physics` +0x1A0 | +0x208 (4) |
| `m_radarData` +0x1A8 | +0x20C (3); +0x1A8 is `m_disabledTillFrame` (2) |
| `m_containedBy` +0x1B0 | +0x214 (31) |
| `m_visionRange` +0x194 | shares +0x194 with `m_body` in the same file |
| `m_prev` +0x8C | 1 copy names +0x8C `m_next` |

The first four are ZH offsets carried over unshifted.

## The header

`Code/GameEngine/Source/GameLogic/Object/object.h` (with
`Code/GameEngine/Source/Common/Thing/thing.h`) is written from this page:

1. `class Thing` (+0x00..+0x5F) and `class Object : public Thing`, so the
   witnessed `Thing` names are inherited rather than restated.
2. A member is declared when at least two byte-verified copies agree on it, or
   one copy plus `name_oracle` at >= 0.9. The rest is opaque storage named by
   offset (`m_unmodelledXXX`). The +0x60..+0x73 vfptrs/vbptr and the
   +0x3BC/+0x3C0 vtordisp and virtual-base vfptr are compiler state in retail,
   kept as opaque members; the header never constructs or up-casts an Object.
3. A virtual slot is named only where an existing pin for that very body uses
   `Object`'s virtual mangling (`onDestroy`, `getDrawable`,
   `updatePendingDamage`, `setTeam`, `rva001cff30`); the rest carry slot and
   body address. That rule also keeps a TU's own declarations from colliding.
4. After each class, `BFME_LAYOUT_CHECK` asserts every named member's offset,
   and `sizeof(Thing) == 0x60`, `sizeof(Object) == 0x3C4`.
5. Nothing has to be included first. A member typed elsewhere takes the real
   type when the TU has it and is otherwise the same bytes under the same
   name: `m_transform` (Matrix3D once `matrix3d.h` is in), `m_cachedPos` /
   `m_cachedDirVector` (`BFME_HAVE_COORD3D`), `m_id` / `m_producerID` /
   `m_builderID` (`BFME_HAVE_OBJECTID`, else `Int`, MSVC's representation of
   the enum), `m_name` / `m_originalTeamName` (`BFME_HAVE_ASCIISTRING`),
   `m_modelConditionFlags` (`BFME_HAVE_MODELCONDITIONFLAGS`). Using one as the
   real type without it is a compile error, never a byte change.
6. Non-virtual methods stay with the TU until their signatures are settled
   (`clearAndSetModelConditionFlags` has five pinned spellings). Define
   `OBJECT_TU_MEMBERS` to the declarations a TU calls, with access labels;
   the hook opens `public:`. Member functions only.

Using it in a new body:

    #define BFME_HAVE_OBJECTID                // only if the TU has the enum
    #define OBJECT_TU_MEMBERS \
        Bool isKindOf(KindOfType kind) const;
    #include "../object.h"                    // relative to the TU

52 TUs moved onto it with one byte-verified swap each. The TUs that were not
moved fail for TU reasons, not layout: they carry their own `Thing`, type a
pointer field as a local shim class (`BfmeAIUpdate *` for `m_ai`), declare
`setTeam` non-virtually, or build the class body from macros.

## Reproduce

    python3 tools/layout_census.py --class Object            # ~25 min, 4 jobs
    python3 tools/layout_census.py --class Object --report   # re-read
    python3 tools/dis_retail.py 0x001D29A0 4246              # Object ctor
    python3 tools/dis_retail.py 0x001328C0 98                # Thing ctor

The same census works for any class: `--class Player`, `--class Drawable`.
