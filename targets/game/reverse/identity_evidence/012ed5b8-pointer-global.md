# ThePartitionManager at VA 0x012ED5B8

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `PartitionManager *` and its spelling is `?ThePartitionManager@@3PAVPartitionManager@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Zero Hour GameLogic/PartitionManager.h:1598 declares extern PartitionManager *ThePartitionManager and GameLogic.cpp constructs it and assigns the same subsystem name. Retail GameLogic::init at RVA 0x0038A1F0 constructs its partition system and stores it in this cell, adjacent to the separate ShroudManager and CollisionManager cells. Retail partition queries, object iterators and update vslot +0x14 read this cell. The existing PartitionManager-typed singleton pin independently anchors its spelling; BfmeWideForwardC remains a use-site layout view.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed5b8.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
