# RVA 00BF298B and placement delete RVA 000607F0

The cleanup entry remains opaque. Existing native CRCParameterCheckLog.cpp
emits the parent `_bfmeRetailCritterDesyncLog` at RVA 00065C80 exactly.
No parent source or shared declaration is changed.

## Ownership, extent, and ABI

Retail parent 00065C80 installs handler VA 00FF29A2 at +8. The handler loads
FuncInfo VA 011DFEB0, whose two-state unwind map starts at VA 011DFEA0.
Entry 1 at VA 011DFEA8 is `{0, 00FF298B}`. Thus this action belongs to that
parent and state, independently of adjacency or a suggested semantic name.

The action is exactly 23 bytes: load EBP-3FC and push; load EBP-3F8 and push;
call ILT RVA 0002AAA9; add ESP,8; RET at RVA 00BF29A1. The next byte begins
the parent handler, not padding. Ghidra read_memory agrees with retail:
`8b8504fcffff508b8d08fcffff51e80b8143ff83c408c3`.

The native STLport vector push_back performs placement construction of the
AsciiString element. Its generated exception action `$L5538` has 19 concrete
bytes and one REL32 naming `??3@YAXPAX0@Z`, the standard cdecl
`operator delete(void*, void*)`. Both pointer slots and the 8-byte caller
cleanup match retail. ILT 0002AAA9 reaches 000607F0, which consists of RET
followed by fifteen INT3 bytes. The identical canonical operator is emitted
by this existing parent TU from the original compiler header `<new>`.
This is native caller/lifetime identity evidence, not generic RET equality.
The unrelated generated ret-void member name has no supported owner identity.

The previous independently reviewed proposal in commit 953785e601 reaches
the same conclusion through a different native parent (00365880). That
proposal remained unlanded because its normal affected-caller gate queued
past the session deadline. This attempt must complete that normal gate
before claiming the provider and dependent action as converted.

## Verification

The unmodified parent passes strict verification. Initial cleanup promotion
fails specifically on unresolved `??3@YAXPAX0@Z` and is restored by add_match.
The provider claim was refused because another worker holds 000607F0.
No provider repair was attempted. The action remains blocked on that held
dependency; no new pin, alias, header, source, or ledger row is introduced.
