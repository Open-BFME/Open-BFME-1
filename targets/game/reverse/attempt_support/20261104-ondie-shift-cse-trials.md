# Object::onDie: shift forms separate the shared mask, but do not match

Queue #16, census aafdf413e9, claim 0xFA7F81B3. BFME1 starting revision
77a8439ee4bde1c902f2059f5d77ff4ed307c4b7. Read the existing
001cefc0-object-ondie-misnamed-lift.md and all linked trials first. This is
new compiler evidence; no recovered function or linked-byte gain is claimed.

BFME1 identity and extent remain the witnessed ILT 0x3369F -> 0x1CEFC0,
thiscall ret4, 1493B. Native callees were regenerated at the full extent.
The latest e497fe529385012dc0ab2552f153369fe31d2432960c0feca9f34bd1fac0e542
attempt-history source is newer than the preferred bank, whose score is zero.
Use that history source when reproducing this result. Its includes resolve to
BFME1 game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h.

Donor context: BFME2 59e3f8f825b698775df9e1728265fe962a5d0c02,
Code/GameEngine/Source/GameLogic/Object/ObjectOnDie.cpp. Its purpose and caller
relationships remain useful; its 798B body, bit offsets, extra hooks and
/G7 /arch:SSE context differ. No donor layout, body, or name was imported.
The existing donor reference/header/ownership history supplies no direct fix
for this BFME1 mask-allocation mismatch.

Private probes used MSVC7.1, /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB,
STLport and _STLP_NO_EXCEPTIONS=1. Every object was an isolated
experiment_store output; none was installed in build/match. Both default
baseline and variants compiled with identical mapped includes. Dependency
inventory reported unreadable/search-directory changes and refused reuse;
these are diagnostic results only, never verification receipts.

All variants replace only `m_status94 & 0x20000000` in the influence branch:

| Expression | Bytes | Result |
|---|---:|---|
| Original mask | 1482 | first mismatch +0x77; EBP holds common mask; shape0.986 |
| `(int)(m_status94 << 2) < 0` | 1493 | no global EBP mask; status uses load/shl/test/jge; later flag pair locally caches mask in ECX; shape0.974 |
| `(__int64)((unsigned __int64)m_status94 << 34) < 0` | 1497 | no global EBP mask; compiler emits a wide compare cascade; shape0.967 |
| `(m_status94 & (1u << 29)) == (1u << 29)` | 1482 | instruction/relocation-identical to baseline |
| `(m_status94 / 0x20000000u) % 2` | 1482 | instruction/relocation-identical to baseline |

The 32-bit signed-shift result is new evidence that an equivalent source
operation can stop the global mask hoist without modifying any retail constant.
Its exact total size is incidental: it still has333 nonrelocation differences,
14 displaced relocation sites, wrong status-test instructions and a locally
cached flag mask. The baseline has1044 raw nonrelocation differences and51
displaced sites because its missing11B shifts most following instructions;
these raw counts are not byte-match scores. The newer baseline is1482B here,
not the1483B quoted in the previous handoff, so reproduce under this context
before comparing totals.

Unresolved: emit retail's immediate-memory test at +0x8E and immediate
model-flag test/or while keeping EBP for the spawner, then resolve the two
remaining global-load schedules. The shift source is not a better bank and
has not replaced any existing bank. Production source remains unchanged.
Normal consumer gates and census-only linking are recorded in the commit.
