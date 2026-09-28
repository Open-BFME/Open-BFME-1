# RVA 0x009A38E0 tree lookup

The retail body at RVA 0x009A38E0 spans 71 bytes. Its code reads the tree header and root. It compares each node's unsigned key at offset 0x10, then follows the left or right child pointer. It returns the matching iterator or the header iterator.

The 22-byte retail wrapper at RVA 0x009A3FF0 directly calls 0x009A38E0 and returns the iterator. `tools/callees.py 0x009A3FF0 22` reports the call target and an object symbol for a tree lookup with unsigned keys. These facts prove the lookup behavior and call signature. They leave the owning map type unknown.

The source uses the comparator `Rva009A38E0Less`, whose name carries this retail address, to give the compiler a unique symbol for the 71-byte body. The comparator orders unsigned keys. Its name leaves the retail owner unknown. The source replaces the prior `?dup_009a38e0` row in place and adds no pin.

The same source defines the wrapper on `Rva009A3FF0Tree`. The class name includes the caller's RVA and leaves its owner unknown. `tools/add_match.py` verifies the wrapper's 22-byte extent and direct call target at RVA 0x009A38E0.
