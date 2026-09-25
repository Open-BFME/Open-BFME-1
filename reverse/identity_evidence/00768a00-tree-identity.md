# Four-byte identity tree insertion, not either pair-valued map

The complete145-byte caller at00768A00 compares a signed key at value+0 with
node+0x10, follows left/right tree links, performs a predecessor check and
returns an iterator plus insertion flag. The insertion call at+0x66 routes
through ILT0004A52F to the complete179-byte body00765440. The predecessor is
the independently named STLport _Rb_global decrement helper.

The full insertion callee independently fixes the value layout. At+0x28 it
allocates20 bytes, comprising16-byte tree links and one4-byte value. At+0x39
it reads one DWORD from the incoming value reference and stores it at node+16.
Its other insertion branch does the same. There is no second value DWORD.
It compares signed at+0x26, links/rebalances the node and increments tree+4.
It reads two node pointers, a const value reference and a fourth node pointer
from its four explicit arguments; hidden iterator return storage is the first
physical stack argument. At+0xA7 it recovers that storage, writes the new node
pointer and returns with ret20. This establishes the helper ABI independently
of the caller's desired byte shape.

All three prior claims (map<int,unsigned>, map<int,GameSpyStagingRoom*> and
map<NameKeyType,float>) require
8-byte pair values and are refuted by this20-byte node. The canonical STLport
identity tree with address-derived signed32-bit Rva00768A00Key reproduces the
caller. Its new helper body pin uses exactly the witnessed4-byte contract;
the original game-level key identity remains unknown. It does not reuse an
unrelated old map pin or infer semantics from a generated enum label.

All three old rows cover the same145 bytes. The PeerDefs and PlayerTemplate
duplicates are separately tombstoned and the GameLogicDispatch row is corrected to the emitted identity
tree. Coverage is unchanged and surplus identity count drops by two. This
repairs a failed existing claim, with zero net byte gain.
