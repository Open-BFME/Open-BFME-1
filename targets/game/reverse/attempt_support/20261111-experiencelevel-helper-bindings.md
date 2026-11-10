# ExperienceLevel assignment: two helper bindings

Task began2026-11-10 22:58:40 UTC (local date becomes November11). Base31622442b1. Prior evidence20261024-experiencelevel-operator-callees.md and all relevant attempt-log entries reviewed.

## Native evidence and repair

The701-byte assignment at0x381690 calls ILT0x7554 ->0x620B0 at+0x142 and ILT0x3827B ->0x63700 at+0x162. The first takes two stack arguments and caller cleanup; the second uses ECX receiver and ret20. They are the existing sharing construction and vector overflow paths used by the attribute-modifier string vector. Existing generic helper homes disagree with those routes. No new template identity is inferred.

Retain the original vector and push_back source. Supply TU-local force-inline imported specializations forwarding these two calls to their existing thunk row names. The imported inline spelling suppresses competing out-of-line definitions; the compiled object has no new __imp_ references (only the existing memmove import). No name, pin, alias, ledger body or shared header changed.

## Trials

1. Raw three-pointer vector view with cached finish changes the caller shape.
2. Reloading finish after construction removes that difference but leaves register mirrors and an empty-tag initialization store.
3. Specializations preserving real STLport source still initialize the forwarded value-initialized empty tag, so the701-byte caller does not match.
4. Discard the unused incoming tag and pass a separately default-initialized __false_type local to the witnessed native helper. This removes the zero store and restores every701 parent byte, all13 relocation positions, and the original register allocation. Empty tag content is not read by the native helper.

## Verification

Normal provider5/5; both consumer units4/4; find_declared_unmatched clean; no funclet pins in the provider. Probe701/701 EXACT modulo relocation operands. Strict RetailTruth now judges assignment701B retail (previous wrong). A private build of the original source uses its own build/queue-retry/experience/original.obj; all masked parent bytes are identical and only relocation names at+0x143 and+0x163 change.

Whole-object truth comparison: wrong copies9 ->5; no retained previously-retail copy becomes wrong or unknown. The45B const-pointer uninitialized_copy also changes wrong ->retail; the wrong66B _Construct and wrong45B nonconst uninitialized_copy emissions disappear. The replaced268B overflow and23B _M_set copies disappear too; this is not new native coverage. Existing unrelated wrong/unknown COMDATs remain.

Current consumer linking checks return PREVIEW UNKNOWN:22,796 changed/missing ledger objects in this worktree. Do not claim the census599-byte estimate as current linked gain. Provider truth is independently verified, not merely ordinary caller bytes.

## Donor provenance

BFME2 pinned2bac16a6 and officialcfe11f2c reviewed at Code/GameEngine/Source/GameLogic/System/ExperienceLevelAssign.cpp, plus its original source/header context. That443B address-derived assignment uses declared out-of-line push_back specializations and different object layout/flags; its literal source cannot replace BFME1's701B assignment. The generic memberwise/vector semantics agree; BFME1 native calls, ABI and the existing linked-body evidence determine these bindings. No donor paths or flags imported.
