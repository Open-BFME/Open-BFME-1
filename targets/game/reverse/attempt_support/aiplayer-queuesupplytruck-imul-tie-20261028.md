# Handoff: ?queueSupplyTruck@AIPlayer@@IAEX (0x00165D50, 2333B)

Date: 2026-10-28. Bank `targets/game/reverse/attempts/0x00165d50.cpp` (0.9957)
re-verified this session: 2333/2333B, 10 non-reloc diffs, single site at
+0x376, shape 0.998 (2 structural diffs).

## Remaining mismatch

Retail computes `availableCash` as `EDX = baseValue; EDX *= boxes`:

```
retail: mov ecx, [0x12ed5c8]      ; TheWritableGlobalData (BFME1 VA)
retail: mov edx, [ecx + 0xb24]    ; m_baseValuePerSupplyBox
retail: imul edx, [eax + 0x88]    ; warehouseModule->getBoxesStored()
retail: test edx, edx
```

Ours computes `ECX = boxes; ECX *= baseValue` (operands/registers swapped).
Everything else in the 2333B body matches.

## Hypotheses tested and refuted (all still 2333/2333, 10 diffs)

1. Donor/ZH operand order
   `warehouseModule->getBoxesStored() * TheWritableGlobalData->m_baseValuePerSupplyBox`
   (build/scratch_165d50/v2.cpp) — identical codegen.
2. Hoist boxes into a named local first (v3) — identical codegen.
3. Hoist price into a named local, donor order (v4) — identical codegen.
4. Global pointer into a named local `GlobalData *gdata` (v5) — identical codegen.

MSVC 7.1 insists on ECX for the result regardless of spelling tried.

## Donor evidence (required reference check)

- `../Open-BFME-2` rev 64ea363549,
  `Code/GameEngine/Source/GameLogic/AI/AIPlayerQueueSupplyTruck.cpp:1032`
  has the boxes-first order, confirming donor/ZH spelling. NOT adaptable to
  the regalloc tie on its own.
- Layout caveat: donor `m_baseValuePerSupplyBox` is at GlobalData +0xA5C
  (line 760); BFME1 retail uses +0xB24. Do not copy donor offsets.

## Next leads (untried)

- Vary the `availableCash <= 0` comparison form or what consumes the result
  (`getRelationship` call follows); the EDX-vs-ECX choice may be driven by
  the consumer, not the multiply.
- Inspect `getBoxesStored()` inline context (stash line 253): the TU-local
  view is `char p[0x88]; int m_boxesStored`. A different accessor spelling
  that keeps EAX free longer may flip the allocation.
- `/FAsc` frame/enregistration table comparison of the +0x376 region.
