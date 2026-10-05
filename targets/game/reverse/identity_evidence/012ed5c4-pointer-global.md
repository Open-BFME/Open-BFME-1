# TheCollisionManager at VA 0x012ED5C4

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `CollisionManager *` and its spelling is `?TheCollisionManager@@3PAVCollisionManager@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Retail VA 0x0078A30D calls the constructor at VA 0x00DA25B0, stores EAX at 0x0078A316 into this cell, initializes vslot +4 and pushes the EA literal TheCollisionManager at VA 0x010EB3C8 at 0x0078A326. The class/pool literal CollisionManager also exists at VA 0x011416A4. The existing CollisionManager singleton pin identifies that same constructor and vtable 0x01141680 update slot +0x14. GameState::init records this object as CHUNK_Collision. The WindowManager and BfmeB1086 spellings are local receiver views of this object; no different global cell is read at those matched call sites. No Zero Hour declaration of this BFME-specific singleton was found.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed5c4.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
