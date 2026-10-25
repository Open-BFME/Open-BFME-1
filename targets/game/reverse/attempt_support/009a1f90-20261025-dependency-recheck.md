# 009A1F90 dependency and missing exact-source recheck

BFME 1 base `5d6792fa0e`; fork-only work under the user-approved claim
exception. No upstream claim was advertised at the start. `callees.py`
confirms no direct calls. Retail `RET +5C / INT3 +5D` proves 93 bytes;
the matched 125-byte destructor at `009A2030` independently proves thiscall
with no explicit arguments. Read all previous verdicts and both immutable
attempt-history records before probing.

The generated caller `0007B420` that prevented the earlier exact source from
landing now has real C++ at
`game/GameEngine/Source/Common/Rva0007B420EngineTeardown.cpp`. Its old dump
remains physically in `game/gen_asm/d_0006bc3e.asm` and still references the
old helper name. Whether the current dependency gate selects that inactive
body is unknown: this session has no exact helper to submit to that gate.
No compatibility pin, generated edit or verifier workaround was attempted.

The previously reported exact private artifacts `build/c4_009a1f90_exact.cpp`
and `build/shape_search/6ae97bb8f29d4fe2b429f880f7f7f868/000-0d9c7d0c4386.cpp`
are absent on this host. Neither tracked attempt-history record contains
that exact source. The surviving preferred source reproduces its known
93-byte/59-difference shape. The old converted verdict alone is insufficient
to recreate or promote its lost implementation.

Private MSVC 7.1 probes tested an outer container guard, native STLport pair
construction (two zeros, default construction, make_pair), native clear vs
erase, GX vs EHsc, implicit custom-pair copy via assignment/memcpy/std::copy/
fill_n, and prefix vs postfix reverse iteration. Native-pair combinations
all emit 98 bytes; the custom-pair forms remain non-exact. These do not
recover the original separate EBX/EBP zeros without an extra destination
induction register. The target's erase tail is understood; reproducing its
reverse-loop allocation remains the source prerequisite.

Logs: `build/009a1f90-20261025-*.log`; finite result manifests are
`build/shape_search/010ed6d93bb74f96abe948b7ed78514e/result.json` and
`build/shape_search/2432bc8f15b949df8dc000d70d02869a/result.json`.
No production source or ledger changes, no new bank, no byte/link gain.
Preserve the existing bank. BFME 2 `3252f8ec` has no reviewed same-identity
source in its corresponding subsystem units; no donor name was transferred.
