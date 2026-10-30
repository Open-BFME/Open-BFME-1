# 0x002230A0 BfmeMemberIndexMap::find (71 B)

Facts from BFME 1 retail:
- 0x002230A0..0x002230E6: thiscall, hidden iterator return slot plus a
  `const int &` key (RET 8); STLport `_Rb_tree::find` over int keys: header at
  this+0, root at header+4, left/right at node+8/+0xC, key at node+0x10;
  returns the header (end) when the lower bound is the header or the key is
  smaller than its key.
- Matched Rva00242480MemberAttackPosition.cpp calls it as
  `?find@BfmeMemberIndexMap@@QAE?AUBfmeMemberIndexIterator@@ABH@Z` (its
  slotKey lookup); nothing defined that name (link queue #76, census
  1d5131d3f1).

The previous row `dup_2230a0` was a gen-alias to one of several byte-equal
int-key tree find instantiations (PeerDefs.cpp's
map<int,GameSpyStagingRoom*>), which the resolver binds elsewhere. The view
name is kept; the original container's element type is unproven.
