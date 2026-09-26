# Distinct hinted tree insertion wrappers

Retail bodies 0x000EA360 and 0x001ABFA0 are each 31 bytes. Their calls route
through ILT 0x00007842 to 0x000E9CC0 and ILT 0x00046038 to 0x001AB2D0,
respectively (callees.py and decoded retail image). Each forwards the same
ECX receiver, a copied one-pointer iterator, a const value pointer and hidden
return storage. The wrapper returns that storage in EAX and pops 12 bytes.

Independently inspected complete 592-byte callees establish the ABI. Both
start with sub esp,8; push ebx; push esi. At +5 the iterator is read from
original ESP+8. After push edi, +0x1E reads the value pointer from original
ESP+12. At +0x31 the return storage is loaded from original ESP+4; +0x37
writes the node pointer to it. The path ends in ret 12 at +0x3D. Other return
paths likewise write one node pointer and pop 12 bytes. Comparisons use tree
header/root links and node keys; calls to the known _Rb_global increment
routine establish the tree-iterator operation independently of the wrappers.

The prior shared ThingTemplate-pointer/int map specialization names a
different callee. These two specializations must remain distinct. Neither the
value's complete layout nor its game-level identity is established here;
separate incomplete address-qualified value types deliberately preserve that
uncertainty. A nontrivial one-pointer iterator copy constructor reproduces the
observed by-value and hidden-return ABI. The tree member is at owner offset
zero because ECX is forwarded without adjustment. Body pins name the decoded
callees, not their ILT entries; the resolver derives the routing.

The existing address-based ledger identities and full extents are retained.
This repairs two existing failed relocation claims, not new byte coverage.
