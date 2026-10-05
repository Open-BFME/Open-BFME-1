# TheCommandList at VA 0x012ED5F0

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `CommandList *` and its spelling is `?TheCommandList@@3PAVCommandList@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Zero Hour Common/MessageStream.cpp:41 and Common/MessageStream.h:820 define and declare CommandList *TheCommandList. Retail RVA 0x00079060 constructs and writes this cell; RVA 0x0007B420 clears it. RVAs 0x0008ADF0, 0x0009BFE0, 0x006828D0 and 0x00682A90 walk its first message at +8 or append frame commands. The existing CommandList singleton pin documents those exact readers. The Rva0038DA10CommandList type is a local layout view of the same CommandList.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed5f0.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
