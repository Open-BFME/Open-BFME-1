# TheMessageStream at VA 0x012ED5EC

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `MessageStream *` and its spelling is `?TheMessageStream@@3PAVMessageStream@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Zero Hour Common/MessageStream.cpp:40 and Common/MessageStream.h:815 define and declare MessageStream *TheMessageStream. Retail callers append input messages through this receiver, and RVA 0x0008ADF0 propagates its messages to the separate CommandList at 0x012ED5F0. Its first-message/list traversal and append virtual contract agree with the reference. singleton-pins.log independently pins the MessageStream-typed spelling and an append-message caller. The GameMessageDispatcher and other invented types are use-site views, not a different singleton.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed5ec.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
