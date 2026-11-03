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
