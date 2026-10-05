# TheShroudManager at VA 0x012ED5BC

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `ShroudManager *` and its spelling is `?TheShroudManager@@3PAVShroudManager@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Retail GameLogic::init stores its new object at VA 0x0078A2AC and immediately assigns the EA literal TheShroudManager from VA 0x010EB3E0. The adjacent partition and collision cells are distinct. Retail also contains the class/pool literal ShroudManager at VA 0x01138D3C. The existing ShroudManager-typed singleton pin documents the exact constructor tag. The old PartitionManager-typed spelling was a shared method/layout view, as its own pin explicitly states, and cannot be a second object at this cell. All declarations now name ShroudManager; old methods keep their TU-local receivers through casts. There is no Zero Hour ShroudManager singleton declaration, because that engine keeps shroud inside PartitionManager.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed5bc.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
