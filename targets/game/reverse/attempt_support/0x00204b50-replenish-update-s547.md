# 0x00204B50 ReplenishUnitsBehavior::update (628 B): bank at shape 1.000, frame slots left

Session a1 s547 (2026-11-03), model claude-opus-5-5, VC7.1 `/DNDEBUG /MD /EHsc`.
Bank: `targets/game/reverse/attempts/0x00204b50.cpp` (supersedes the 0.35 bank and the
earlier `0x00204b50-replenish-update-realclass-v0.cpp.txt`).

Identity: ilt_oracle CONFIRMS `?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ`;
ea_evidence.csv names 0x00204B50 ReplenishUnitsBehavior::update (direct strong). The
ledger row is still the naked lift `??1ReplenishUnitsBehavior@@UAE@XZ` (ReplenishUnitsBehaviorDestructorThunk.cpp):
landing = `add_match --replace-rva 0x00204B50 --correct-identity ??1ReplenishUnitsBehavior@@UAE@XZ`
+ identity_evidence md + delete the lift TU + its hatch_baseline line (see a69c2c9767 for the recipe).

Probe: 631/628 B, `shape 1.000 identical once registers and constants are normalised`;
the only residue is the frame: ours `sub esp,0x9C`, retail `0x90`.

## What got it from 0.35 to shape 1.000 (each measured)

1. Real filter classes with dir32-recorded vtable names (Rva0025ED50ObjectFilter,
   Rva0025ED50RootFilter, PartitionFilterRelationship, Rva00204360VptrZeroObject,
   Rva0016A9F0FunctorValueWrapper, Rva001FC280VptrZeroBlockObject) and inline virtual dtors.
2. Both filter chains are TEMPORARIES in one full expression: retail zeroes a frame word at
   entry and stores 0xF into it before the first link = the EH destructor bitmask of four
   conditional temporaries (`radius == default || find(...) == 0`). 400 B -> 637 B.
3. Bool polarity: `Bool clear = radius == g_bfmeDefaultBR || find(...) == 0; if (!clear) return sleep;`
4. Prologue: call the +0x20 interface through the primary pointer
   (`static_cast<ReplenishUnitsBehavior *>(self)->isActive()`), giving retail's
   `lea eax,[ecx-0x10]; lea ecx,[eax+0x20]`.
5. Contain gate through a local (`ContainModuleInterface *c = object->m_contain;`).
6. Kind-of mask `xor edx,edx / mov eax,edx / or eax,0x20000`: a constructor doing
   `memset(m_bits,0,sizeof m_bits); m_bits[bit>>5] |= 1u << (bit&31);` (constant stores
   fold otherwise; loops/helpers fold too).
7. `throw()` on `Rva001FC280VptrZeroBlockObject`'s constructor removes the extra EH state 6
   store before its call (retail goes 4 -> 7).
8. Constructor argument order is `(data->m_kindOf, mask)` (retail pushes the mask first).

## Remaining: frame-slot packing

Retail frame (offset from esp after `sub esp,0x90`): f2 ObjectFilter and the kind-of mask
share 0x00; self 0x0C; root 0x10; bitmask 0x18; sameMap 0x1C; player 0x28; containFilter
0x34; f3 RootFilter 0x44; f4 Relationship 0x4C; f1 Rva001DCBB0Filter 0x60; kindOf 0x70.
Only the mask reuses a dead group-1 slot. Ours gives every temp its own slot (0x9C).
Inert: mask as named local before the call (computed too early), helper returning the
mask by value, group 1 or 2 inside inline helpers (427/432 B), group 2 as named locals
(595 B: drops the vptr resets), `if (!(...))` / `== false` / split Bool declaration.

## 2026-11-12 w1: packing rules tested against a corrected slot map

The slot map above mixes push depths. Recomputed with every retail `[esp+N]` taken at the
four-push depth (ebx, esi, edi, ebp saved; the EH record at 0xA0):

| retail esp | object | size |
|---|---|---|
| 0x10 | group-1 Rva0025ED50ObjectFilter **and** the group-2 kind-of mask | 12 |
| 0x1C | self | 4 |
| 0x20 | group-2 Rva0025ED50RootFilter | 8 |
| 0x28 | EH conditional bitmask (0 at entry, 0xF before group 1) | 4 |
| 0x2C | group-2 Rva0025ED50ObjectFilter | 12 |
| 0x38 | Rva0016A9F0FunctorValueWrapper | 12 |
| 0x44 | Rva00204360VptrZeroObject | 16 |
| 0x54 | group-1 Rva0025ED50RootFilter | 8 |
| 0x5C | PartitionFilterRelationship | 20 |
| 0x70 | Rva001DCBB0Filter | 16 |
| 0x80 | Rva001FC280VptrZeroBlockObject | 32 |

Ours (/FAsc, top down from the EH record):
- Block T1096, DCBB0 T1092, Relationship T1089, ObjectFilter1 T1091, mask T1097, VptrZero T1100, Root1 T1090
- Functor T1095, ObjectFilter2 T1099, Root2 T1098, bitmask T1101, self
- Nothing shares.

So the only sharing in retail is ObjectFilter1 with the mask. ObjectFilter1 also sits at the
bottom of retail's frame instead of next to the other group-1 temporaries.

What each rule says here:
- **Rule 2 (the last-created candidate never shares):** our last-created candidate is T1101, the
  conditional bitmask, which also sits alone in retail. The mask (T1097) is not last, so rule 2
  does not explain the missing join.
- **Rule 1 (size within a factor of two):** the mask (12) and ObjectFilter1 (12) satisfy it.
- **Rule 3 (address-taken function-scope local):** applies only to temporaries here. Putting
  group 1, group 2 or both in `{}` blocks leaves 631 B with an unchanged slot table
  (sub esp,0x9C).

The open question is therefore lifetime, not size or creation order. VC7.1 never treats our
group-1 conditional temporaries, whose destructors are guarded by the bitmask, as dead before
the mask is built. Retail does, and only for ObjectFilter1.

Retail's conditional cleanups at 0x00C0BBE0, with ebp = esp+0xAC, are mapped as follows:
- flag 1: Rva001DCBB0Filter at 0x70
- flag 2: ObjectFilter1 at 0x10
- flag 4: Root1 at 0x54
- flag 8: Relationship at 0x5C

So ObjectFilter1 IS a bitmask-guarded conditional temporary in retail, and it still donates its
slot to the mask. "Conditional temporaries never share" is therefore refuted as the explanation.
What differs is which group-1 temporary is packed last. Retail packs ObjectFilter1, the second
link built and flag 2, at the frame bottom. Ours keeps it beside the other group-1 temporaries.
Untested: argument evaluation orders that make ObjectFilter1 the first group-1 object constructed.
Retail constructs it right after the DCBB0 constructor call, before Root1 and Relationship, which
ours already reproduces in code order. The difference may therefore lie in $T numbering, not in
code order. t=40min model=claude-opus-5-5
