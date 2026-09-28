# RVA 0x009A38E0 tree lookup

The retail body at RVA 0x009A38E0 spans 71 bytes. Its code reads the tree header and root. It compares each node's unsigned key at offset 0x10, then follows the left or right child pointer. It returns the matching iterator or the header iterator.

The 22-byte retail wrapper at RVA 0x009A3FF0 directly calls 0x009A38E0 and returns the iterator. `tools/callees.py 0x009A3FF0 22` reports the call target and an unsigned-key tree-find object symbol. These facts prove the lookup behavior and call signature. They leave the owning map type unknown.

The source uses the address-derived `Rva009A38E0Less` comparator to give the compiler a unique symbol for this 71-byte body. The comparator orders unsigned keys. Its name makes no claim about the retail owner. The existing address-derived row changes in place, and the source adds no pin.
