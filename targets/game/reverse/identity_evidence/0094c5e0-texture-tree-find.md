# 0x0094C5E0: the texture tree's own STLport find

Retail 0x0094C5E0..0x0094C626 (71 bytes, `ret 8`) is an unsigned-key
`_STL::_Rb_tree::find` body: ECX is the tree, the header node is loaded from
`[ecx]`, node keys are compared at +0x10 with JB/JAE, and the hidden iterator
result is written through the first stack argument.

## Facts from BFME 1 retail

- `Rva0094D1E0List::rva0094D250` (0x0094D250, matched in
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0094D1E0List_rva0094D250.cpp`)
  forms the tree at this+8 (`lea edi,[ebx+8]; mov ecx,edi`) and calls
  0x0094C5E0 directly (rel32 at +0x3A, no ILT) with the texture key.
- The same tree's `insert_unique` (0x0094CCF0) is reached through the same
  `_Rb_tree<unsigned, pair<const unsigned, Rva0094CCF0Value>, ...>` view in
  that TU, and its bytes already match.
- Retail was linked without identical-COMDAT folding (see AGENTS.md), so the
  body a TU's call lands on is that TU's own instantiation: 0x0094C5E0 is the
  find of the caller's tree type, not the StateMachine map's find (that one is
  0x000A0E20, `identity_evidence/000a0e20-state-tree-find.md`).

## Previous row

`?dup_0094c5e0@@YAXXZ` was a gen-alias home whose bytes came from
StateMachine.cpp's State-map find COMDAT (identical 71-byte shape). The caller
spelled the call `Rva0094C5E0Tree::find`, a name nothing defined (link queue
#60 unresolved).

## Name

The caller TU now instantiates real STLport
`_Rb_tree<unsigned, pair<const unsigned, Rva0094CCF0Value>, _Select1st<...>,
less<unsigned>, allocator<...> >::find<unsigned>`; the emitted COMDAT is byte
identical to 0x0094C5E0 and the caller row still matches. The mapped value
type keeps its address-derived TU view name (`Rva0094CCF0Value`, 16 bytes):
its real type is not established.
