# 0x0089CEF0 BfmeTab1024::bfmeFind1024 (520 B) -- EXACT

Symbol: `?bfmeFind1024@BfmeTab1024@@QAEHH@Z`. Compiler: MSVC 7.1, `// cl: /O2 /DNDEBUG /MD`
(unchanged from the bank and from the matched out-of-line HashFindKey
0x0089CA10 in game/GameEngine/Source/Common/BfmeStringMap0089CA10.cpp).

Landed in `game/GameEngine/Source/Common/BfmeStringMap0089CA10.cpp`, next to the
out-of-line 0x0089CA10 find it inlines (scratch build/wf/0089cef0/best.cpp; probe: `result EXACT (modulo
relocation slots)`, 520/520 B, 11 relocs; callees per tools/callees.py:
`?bfmeInit929G@BfmeThing929G@@QAEXXZ` 0x0089E700, `_strcmpi` via ILT 0x009F6FA0).

## Prior residue (bank 0.9769, 12 diff bytes, reproduced)
At +0x3A retail `lea ebx,[esi*8]; mov ecx,[ebx+eax]; test ecx,ecx`, ours
`mov ecx,[eax+esi*8]; test ecx,ecx; lea ebx,[esi*8]`.

## Fix (lever)
In the __forceinline find, snapshot the table pointer in a local and use it
for the FIRST probe load and the first match argument, while the first-probe
return keeps reading the member:

    Bucket1024 *entries = m_entries;
    int bucket = (m_count - 1) & keyHash;
    BfmeStringData0089CA10 *data = entries[bucket].m_data;
    ...
    && matchEntry0089CA10(&entries[bucket], key))
        return &m_entries[bucket];

Effect: the load now uses the CSE'd `bucket*8` (lea ebx first, `[ebx+eax]`).
Using `entries` for the return too (`return &entries[bucket]`) is much worse
(516 B, 454 diffs).

## Trials this session (all against the 12-byte bank)
- no `data` local (re-read m_entries[bucket].m_data): inert, 12 B
- `m_entries + bucket` for match arg and return: inert
- `keyHash & (m_count-1)` operand order: inert
- nested if for empty/match: inert
- `else if` after the null return: inert
- named mask local `m_count - 1`: inert
- data-based inline match (no entry pointer): worse (516 B, 453)
- entries local for load+match+return: worse (516 B, 454)
- entries local for load+match, member for return: EXACT

Sibling note: 0x0089CC80 Unset has the same +0x45 lea/load order residue
(handoff 20261102-0089cc80-apt-hash-unset.md); the same snapshot lever is
worth trying there. BFME 2 submodule not initialized in this checkout; not
needed.

## Landing (2026-11-06)

Merged into the sibling TU instead of a second private view of
BfmeStringMap0089CA10: the class gains the `findInline` declaration and the
+0x08/+0x0C `__proto__`/`prototype` slots and its members become public. Both
rows probe EXACT in the merged TU (0x0089CA10 395/395, 0x0089CEF0 520/520), and
`add_match.py --replace-rva 0x0089CEF0` verified 2/2 rows, 2 string literals and
6 DIR32 references. The name is the existing symbols.csv pin that matched
callers (BfmeB1236Emit.cpp) already bind.
