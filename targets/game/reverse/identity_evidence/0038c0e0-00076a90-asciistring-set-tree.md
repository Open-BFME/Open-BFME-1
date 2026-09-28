# set<AsciiString> tree: _M_find at 0x0038C0E0 and _M_erase at 0x00076A90

Both bodies were claimed under spellings that asserted no real value type:
0x0038C0E0 as `_Rb_tree<AsciiString, Rva0038C0E0Value, Rva0038C0E0KeyOfValue,
less<AsciiString>, ...>::_M_find<AsciiString>` (one of 19 identical AsciiString
_M_find bodies in RvaTreeFindAsciiString.cpp), and 0x00076A90 as the gen-tgrid
placeholder `_Rb_tree<Gen_t_00076a90_k4, _Identity, ...>::_M_erase`.

Evidence that both belong to `_Rb_tree<AsciiString, AsciiString,
_Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >`, the tree
of `_STL::set<AsciiString>`:

- 0x00076A90 frees each node with `__node_alloc::_M_deallocate(node, 0x14)`
  (16-byte node header plus a 4-byte value) after calling `??1AsciiString` on
  node+0x10 through ILT 0x0000D828: the value is exactly one AsciiString, so the
  value type is the key type and the key-of-value functor is `_Identity`.
- It recurses through ILT 0x00002900F, which jumps back to 0x00076A90; that ILT
  was already pinned under the set<AsciiString> `_M_erase` spelling.
- The matched set<AsciiString> destructor
  `??1?$_Rb_tree@VAsciiString@@V1@U?$_Identity...` at 0x000775F0 (PeerDefs.cpp)
  calls ILT 0x0002900F, i.e. this body. Retail was linked without identical-
  COMDAT folding, so one instantiation's `_M_erase` has one address.
- 0x0038C0E0 compares an AsciiString key stored at node+0x10 (inline
  StringBase<char>::compare in the descent, the same comparison as a call at the
  end). Matched callers of `_STL::set<AsciiString>::find` --
  PopulatePlayerTemplateComboBox 0x006247B0 and PopulateLobbyPlayerListbox
  0x004FB500 -- reach it through ILT 0x00003071, which was already pinned under
  the set<AsciiString> `_M_find<AsciiString>` spelling. The banked callers
  0x005294F0 and 0x005082D0 call the same two ILTs from their `set<AsciiString>`.

Bytes: the set<AsciiString> `_M_erase` emitted by PeerDefs.cpp and the
re-spelled `_M_find<AsciiString>` instantiation in RvaTreeFindAsciiString.cpp
both compile to the retail bodies (probe: 61/61 and 194/194, exact).
