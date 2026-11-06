# 0x00289E50 tail tie — exact 6-byte map, status-local lever refuted

Bank unchanged: 806/806 B, 6 non-reloc diffs, score 0.9926 (re-probed this
pass; reproduces exactly).

## The 6 bytes (retail | ours)

- `+02B6 mov esi,[ecx+0x24]` | `mov edi,[ecx+0x24]` — return value
  (`m_moduleData->m_sleepTime`) homed in ESI vs EDI.
- `+02D7 mov edi,eax` | `mov esi,eax` — release payload homed in the other.
- `+0302 push edi` | `push esi` — payload passed to `operator delete`.
- `+0312 pop edi; +0313 mov eax,esi` | `mov eax,edi; +0314 pop edi` — return.

Tail semantics (new this pass): after the iterator loop, retail decrements a
refcount at `[eax+0x10]` (eax from `[esp+0x10]`), runs a capacity check
(`sub/sar/shl`, `cmp eax,0x80`, conditional realloc calls), deletes the
payload, then returns sleepTime. The two values have fully overlapping live
ranges, so this is a pure allocator tie-break; everything else in the 806 B
body is already exact.

## Refuted this pass

Named status local (`unsigned statusBits = target->m_status[0];` tested
before the two bit-tests, per "A list-head register exchange fixed by a
named count local"): 814 B / 393 diffs — frame grows 0x98→0x9C and the whole
tail reshuffles. The payload-side live range must NOT be extended. Scratch:
`build/rd970/stealth_iter1.cpp` (untracked, safe to delete).

## Untried (for next)

- The `[esp+0x10]` payload root: identify which source object it is (likely
  the `BfmeWideResult iter` buffer or a filter-chain root saved at +0034).
  A named local for THAT object shorter than its current range — not longer —
  is the remaining direction.
- `shape_family_levers.py --families register` + `shape_search.py` over the
  tail only (6 bytes, finite choice set); the byte gate decides.
- Do NOT repeat: return-via-named-local, top-declared return local,
  UpdateSleepTime-typed field, split decrement, dtor spellings, release()
  member, getModuleData accessor, volatile/early-return/static-helper
  variants, const-ref, `<1` test, md local (all inert per history).
