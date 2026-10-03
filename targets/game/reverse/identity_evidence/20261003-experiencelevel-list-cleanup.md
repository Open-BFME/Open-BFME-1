# ExperienceLevel list destructor and cleanup

The retail parent at RVA `003820A0` is the already matched native STLport
`hash_map<int, list<ExperienceLevel> >::operator[]` in
`game/GameEngine/Source/Common/ExperienceLevelSystemMapOperator.cpp`.
Its identity is independently anchored by the matched `00382210` caller,
the map at member offset 8, and the typed `00381E80` list assignment. The
source documents the D8-byte ExperienceLevel and E0-byte list nodes.

The parent's prologue pushes handler `00C1B7B2`. That handler loads FuncInfo
`00E0BBD0`, whose unwind map at `00E0BBC0` maps state 0, predecessor -1,
to `00C1B780`. This is ownership evidence, not an adjacency inference.
The action tests mask 2 at EBP-18, clears it, and passes the address EBP+4
to ILT `00037D12`, which jumps to `0037E920`. The action returns at
`00C1B798`, proving its 25-byte extent.

The native parent's corresponding compiler action `$L10460` has the same
21 concrete bytes and calls
`??1?$list@VExperienceLevel@@V?$allocator@VExperienceLevel@@@_STL@@@_STL@@QAE@XZ`.
The typed native parent and independently proven unwind ownership identify
the destroyed temporary as that list. The destructor is emitted by the
same existing native STLport source, with no added adapter or body.

Retail `0037E920` calls `0004278A -> 0037DCA0`, loads its sentinel pointer,
conditionally calls operator delete at `00881EB0`, and returns at
`0037E938`, followed by seven INT3 bytes. The native destructor has exactly
these 25 bytes modulo its two call relocations. The existing canonical pin
for `_List_base<ExperienceLevel>::clear` at `0037DCA0` independently records
typed virtual destruction at node+8 and resetting both sentinel links.
Retail disassembly confirms that operation. The other relocation is the
existing operator-delete binding; no new symbol pin is needed.

Replace the old opaque `?bfmeGoELAb@BfmeThingELAb@@QAEXXZ` ledger claim at
`0037E920` with this native list destructor, preserving one identity at the
address. Its old source is not used as naming evidence. Ghidra byte reads
at VA `0077E920`, `0101B780`, and `0120BBC0` agree with the unpacked retail
image. Strict source verification checks both call targets, not just the
relocation-masked instruction sequence.
