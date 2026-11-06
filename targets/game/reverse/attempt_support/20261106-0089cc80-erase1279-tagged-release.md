# 0x0089CC80 BfmeLookup1279::bfmeErase1279 (617 B): EXACT (2026-11-06)

Landed in `game/GameEngine/Source/Common/BfmeStringMap0089CA10.cpp` beside the
out-of-line 0x0089CA10 find and the 0x0089CEF0 bfmeFind1024 body. Both share
the same force-inlined probe. VC7.1 `/O2 /DNDEBUG /MD` (unchanged from the
bank and the TU).

Identity (unchanged, BFME 1 evidence): the symbols.csv pin decoded from the
0x008BD400 erase call, plus the matched BfmeQueryProcess1279 and
Rva008BDD70ResetList callers that store this body as their erase callback.
Retail `ret 4` at +0x266 and INT3 at +0x269 give the 617-byte extent. The
structure follows the BFME 2 donor `AptNativeHash::Unset` lead recorded in
20261102-0089cc80-apt-hash-unset.md.

## Starting point
Bank 0.964 (forceinline copy of HashFindKey): 636/617 B, 240 diffs.

## Levers, in order (each measured with tools/probe.py)
1. **Entries snapshot for the first probe** (the 0x0089CEF0 lever):
   `Entry *entries = m_entries;` used for the first load and match argument,
   with the first-probe return still `&m_entries[bucket]`. That fixes the +0x45
   lea/load order: 636 B, 228 diffs, shape 0.973.
2. **Masked tagged pointer in a local**: `((T *)(v & ~1u))->release()` made
   VC7.1 evaluate the mask twice (once for the vtable load, once for `this`:
   `mov edx,ecx; and edx,~1; ...; and ecx,~1`). A local
   `T *value = (T *)(v & ~1u); value->release();` masks once. 621 B, 146 diffs,
   shape 0.991.
3. **Prototype/__proto__ slots assigned in the condition**: with
   `&& map->m_prototype0c` as the test and a separate masked read, the slot
   loaded into EAX and was copied to ECX before the call (+2 B each). Writing
   `T *prototype; if (strcmpi(...) == 0 && (prototype = (T *)map->m_prototype0c) != 0)
   { prototype = (T *)((unsigned)prototype & ~1u); prototype->release(); ... }`
   keeps retail's `mov ecx,[edi+0Ch]; test ecx,ecx; je; and ecx,~1; mov edx,[ecx];
   call [edx+4]`: **EXACT** 617/617.

Inert or worse at step 3: a nested `unsigned int tagged` local (621, 146 diffs), and
the original inline expression form for the proto slots (631 B).

add_match verified 3/3 rows in the TU, 4 literals and 13 DIR32 references. An
address-only symbols.csv alias keeps `?d_0089cc80@@YAXXZ` resolving for the two
matched callers that store the dump name.
