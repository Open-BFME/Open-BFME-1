# Handoff: ?d_001e9380@@YAXXZ (0x001E9380, 1519B) — fireWeaponTemplate regalloc tail

Date: 2026-11-04. Claim held during investigation, released after.

## Verified state (independent reprobe, model=muse-spark)

Bank `targets/game/reverse/attempts/0x001e9380.cpp` (`?rva001e9380@WeaponTemplate@@QAEX...`)
probes at **1520B vs retail 1519B, 34 relocs, 30 non-reloc diffs, shape 1.000**
(register/stack-slot allocation only). Confirms brief HISTORY #34 numbers.

## Root-cause narrowing (new this round)

- The 5 branch-target diffs (+0013/+0027/+0167/+0187/+0465, all `je/jnp 0x5e5`
  vs `0x5e6`) are pure consequences of a single +1 length delta, not control flow.
- The single length byte is the final-loop iterator load: retail `mov ebx,[ebx]`
  (2B, `8B 1B` at +05DB) vs bank `mov ebp,[ebp+0]` (3B, `8B 6D 00`).
- Register roles in retail tail (+0581..+05E3): EBX = list node, ESI = victimObj
  (live, never reloaded), EDI = nugget, EBP = firingWeapon **reloaded from
  [esp+0x84] every iteration**. The bank keeps firingWeapon in a register and
  puts the node in EBP instead.
- So the whole 30-diff residue plausibly collapses to one allocator decision:
  spill firingWeapon to its stack home across the final nugget loop so the
  induction stays in EBX.

## Tried this round (inert, do not repeat)

- `Weapon *loopWeapon = firingWeapon;` named local used for all six loop call
  args: byte-identical output (1520B, same 30 diffs, same first-at-+21).
  A rename/copy alone does not spill the weapon.

## Suggested next (untried)

- Raise register pressure inside the final loop with a *live-across-call* value
  (e.g. keep `damagePosition` partially in a register, or hoist the
  `m_nuggetList` end sentinel into a named local per the 2026-11-04
  "list-head register exchange" lever) so the allocator must evict the weapon.
- Alternatively sink a re-read: `firingWeapon->m_rangeFrame`-style field touch
  inside the loop body is wrong semantically; instead try passing
  `firingWeapon` through an opaque noinline-free inline accessor that the
  compiler cannot keep in EBX (risky, verify semantics).
- shape_search with families=register,copy,store over the final-loop region
  only, budget-capped; do not re-run the #35 variant set (shared
  iterator+nugget, raw node walk, donor contain test, (*node)-> receivers,
  else-if) — all inert.
