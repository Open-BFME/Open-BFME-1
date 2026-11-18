# Reconcile the Apt string-builder call binding

The current link queue names the undefined `bfmeBuildString1284` member as the
only blocker for the value-string consumer. Its 1866-byte matched row at
0x008985C0 calls retail 0x008B8E70. `tools/callees.py` and the complete 267-byte
retail disassembly establish an ECX receiver, two stack arguments and `ret 8`.
The existing provider row names `?d_008b8e70@@YAXXZ`; no new name or pin is needed.

Two verified BFME1 callers, BfmeStringWriter1284.cpp and JoinArray008B94F0.cpp,
already use the target's typed thiscall bridge to this existing generated row.
The remaining consumer now uses that same source pattern. Narrow review of the
current BFME2 donor found no provider with the BFME1-specific placeholder name;
no BFME2 address, class layout, toolchain or body is imported. Target callers,
the existing ledger binding and full retail callee establish this repair.

An isolated original compile equals the actual original native object. The
candidate's complete ordinary code/data/relocation/directive/definition inventory
equals it after substituting only the independently proven callee-symbol name.
The actual adopted native object equals that private candidate. Normal checks
pass all three callers: 2436 existing function bytes, 18 string
literals, one floating constant and 49 DIR32 references; zero body-guard debt.

Before link_check: LINKED PREVIEW UNKNOWN (stale 45cda0e209 selection and 24
unavailable changed ledger objects), with the unresolved old member reported.
After bounded native hook preview: LINKED PREVIEW UNKNOWN (25-second timeout).
The census row is not edited and no linked-byte gain or game runtime is claimed.
The existing generated provider is not reconstructed or altered. Its old unused
placeholder pin remains untouched; no alias, escape hatch or verifier is added.

This independent caller repair counts zero of the 500 scalar-consumer tasks.
Local native logs, exact before/candidate snapshots and symbol-bound comparison
are retained in the current session diagnostics and private build directory.

The existing 267-byte generated callee was also independently rebuilt and
verified through the normal build selector `?d_008b8e70@@YAXXZ`. Its source and
ledger remain unchanged. Provider and all three consumers therefore have native
byte proof, while whole-image selection and runtime remain unverified.
